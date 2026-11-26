/* nes_ppu.c - the NES picture: registers (v/t/x/w scrolling as the 2C02 has them), name tables,
 * palette, sprites; drawn a line at a time when the CPU's time passes it (ppu_catch_up), so
 * register changes in the middle of the frame (SMB3's status bar, from the MMC3 IRQ) land on
 * the right line. Output: ppu_fb, 256 x 240, 0xAARRGGBB. */
#include "nes_ppu.h"
#include <string.h>

const uint8_t *ppu_chr_slot[8];
int ppu_mirror_h;
uint32_t ppu_fb[256 * 240];
static uint8_t ctrl, mask, status, oam_addr, w_latch, fine_x, rbuf;
static uint16_t v, t;
static uint8_t vram[0x800], pal[32], oam[256];
static int next_line;

static const uint8_t NES_RGB[64][3] = {
    {84,84,84},{0,30,116},{8,16,144},{48,0,136},{68,0,100},{92,0,48},{84,4,0},{60,24,0},{32,42,0},{8,58,0},{0,64,0},{0,60,0},{0,50,60},{0,0,0},{0,0,0},{0,0,0},
    {152,150,152},{8,76,196},{48,50,236},{92,30,228},{136,20,176},{160,20,100},{152,34,32},{120,60,0},{84,90,0},{40,114,0},{8,124,0},{0,118,40},{0,102,120},{0,0,0},{0,0,0},{0,0,0},
    {236,238,236},{76,154,236},{120,124,236},{176,98,236},{228,84,236},{236,88,180},{236,106,100},{212,136,32},{160,170,0},{116,196,0},{76,208,32},{56,204,108},{56,180,204},{60,60,60},{0,0,0},{0,0,0},
    {236,238,236},{168,204,236},{188,188,236},{212,178,236},{236,174,236},{236,174,212},{236,180,176},{228,196,144},{204,210,120},{180,222,120},{168,226,144},{152,226,180},{160,214,228},{160,162,160},{0,0,0},{0,0,0}};
static uint32_t rgba[64];

static inline uint8_t chr_rd(uint16_t a) { return ppu_chr_slot[(a >> 10) & 7][a & 0x3FF]; }
static inline uint16_t nt_index(uint16_t a) {          /* $2000-$2FFF -> vram */
    a &= 0x0FFF;
    return ppu_mirror_h ? (uint16_t)(((a >> 1) & 0x400) | (a & 0x3FF)) : (uint16_t)(a & 0x7FF);
}
static inline int pal_index(uint16_t a) { a &= 0x1F; if ((a & 0x13) == 0x10) a &= 0x0F; return a; }

void ppu_reset(void) {
    ctrl = mask = status = oam_addr = w_latch = fine_x = rbuf = 0; v = t = 0;
    memset(vram, 0, sizeof vram); memset(pal, 0, sizeof pal); memset(oam, 0xFF, sizeof oam);
    for (int i = 0; i < 64; i++) rgba[i] = 0xFF000000u | (uint32_t)NES_RGB[i][0] << 16 | NES_RGB[i][1] << 8 | NES_RGB[i][2];   /* 0xAARRGGBB */
    next_line = 0;
}
int ppu_nmi_on(void) { return ctrl >> 7; }
int ppu_next_line(void) { return next_line; }
void ppu_vblank(void) { status |= 0x80; }
static int rendering(void) { return (mask & 0x18) != 0; }
void ppu_prerender(void) {
    status &= 0x1F;
    if (rendering()) {
        v = (uint16_t)((v & ~0x041F) | (t & 0x041F));
        v = (uint16_t)((v & 0x841F) | (t & 0x7BE0));
        nes_mmc3_clock();
    }
}
void ppu_frame_start(void) { next_line = 0; }

/* a snapshot of the pattern tables as mapped on one line (SMB3's status bar has its own banks,
   set by the MMC3 IRQ in the middle of the frame) */
static int cap_line = -1; static uint8_t cap_chr[0x2000], cap_ctrl;
void ppu_capture_at(int y) { cap_line = y; }
const uint8_t *ppu_captured_chr(void) { return cap_chr; }
uint8_t ppu_captured_ctrl(void) { return cap_ctrl; }
uint8_t ppu_peek_nt(uint16_t a) { return vram[nt_index(a)]; }

static void draw_line(int y) {
    uint32_t *out = ppu_fb + y * 256;
    if (y == cap_line) { for (int i = 0; i < 0x2000; i++) cap_chr[i] = chr_rd((uint16_t)i); cap_ctrl = ctrl; }
    uint8_t bg[256 + 16]; memset(bg, 0, sizeof bg);
    if (mask & 0x08) {                                   /* background */
        uint16_t vv = v; uint16_t base = (ctrl & 0x10) ? 0x1000 : 0;
        for (int tile = 0; tile < 33; tile++) {
            uint8_t idx = vram[nt_index((uint16_t)(0x2000 | (vv & 0x0FFF)))];
            uint8_t at = vram[nt_index((uint16_t)(0x23C0 | (vv & 0x0C00) | ((vv >> 4) & 0x38) | ((vv >> 2) & 0x07)))];
            int pbits = (at >> (((vv >> 4) & 4) | (vv & 2))) & 3;
            int fy = (vv >> 12) & 7;
            uint8_t lo = chr_rd((uint16_t)(base + idx * 16 + fy)), hi = chr_rd((uint16_t)(base + idx * 16 + fy + 8));
            for (int b = 0; b < 8; b++) {
                int px = tile * 8 + b - fine_x;
                if (px < 0 || px >= 256) continue;
                int p = ((lo >> (7 - b)) & 1) | (((hi >> (7 - b)) & 1) << 1);
                bg[px] = p ? (uint8_t)(pbits << 2 | p) : 0;
            }
            if ((vv & 0x1F) == 31) { vv &= ~0x1F; vv ^= 0x400; } else vv++;
        }
        if (!(mask & 0x02)) memset(bg, 0, 8);
    }
    uint8_t sp[256], sprio[256], s0[256]; memset(sp, 0, sizeof sp); memset(s0, 0, sizeof s0);
    if (mask & 0x10) {                                   /* sprites: the lowest number wins */
        int h = (ctrl & 0x20) ? 16 : 8;
        for (int i = 63; i >= 0; i--) {
            int row = y - (oam[i * 4] + 1);
            if (row < 0 || row >= h) continue;
            uint8_t tile = oam[i * 4 + 1], attr = oam[i * 4 + 2]; int sx = oam[i * 4 + 3];
            if (attr & 0x80) row = h - 1 - row;
            uint16_t addr;
            if (h == 16) { addr = (uint16_t)(((tile & 1) ? 0x1000 : 0) + (tile & 0xFE) * 16); if (row >= 8) { addr += 16; row -= 8; } }
            else addr = (uint16_t)(((ctrl & 0x08) ? 0x1000 : 0) + tile * 16);
            uint8_t lo = chr_rd((uint16_t)(addr + row)), hi = chr_rd((uint16_t)(addr + row + 8));
            for (int c = 0; c < 8; c++) {
                int x = sx + c; if (x >= 256) break;
                int bit = (attr & 0x40) ? c : 7 - c;
                int p = ((lo >> bit) & 1) | (((hi >> bit) & 1) << 1);
                if (!p) continue;
                sp[x] = (uint8_t)(0x10 | (attr & 3) << 2 | p); sprio[x] = attr & 0x20; s0[x] = i == 0;
            }
        }
        if (!(mask & 0x04)) memset(sp, 0, 8);
    }
    for (int x = 0; x < 256; x++) {
        int bp = bg[x] & 3, c;
        if (s0[x] && bp && sp[x] && x != 255) status |= 0x40;
        if (sp[x] && (!sprio[x] || !bp)) c = pal[pal_index(sp[x])];
        else if (bp) c = pal[bg[x]];
        else c = pal[0];
        out[x] = rgba[c & 0x3F];
    }
}
void ppu_catch_up(int dot) {
    while (next_line < 240 && next_line * 341 + 260 <= dot) {
        int y = next_line++;
        if (!rendering()) { uint32_t c = rgba[pal[0] & 0x3F]; for (int x = 0; x < 256; x++) ppu_fb[y * 256 + x] = c; continue; }
        draw_line(y);
        /* the end of the line: down one row, back to the left (t's horizontal bits) */
        if ((v & 0x7000) != 0x7000) v += 0x1000;
        else {
            v &= ~0x7000; int cy = (v & 0x3E0) >> 5;
            if (cy == 29) { cy = 0; v ^= 0x800; } else if (cy == 31) cy = 0; else cy++;
            v = (uint16_t)((v & ~0x3E0) | (cy << 5));
        }
        v = (uint16_t)((v & ~0x041F) | (t & 0x041F));
        nes_mmc3_clock();
    }
}

uint8_t ppu_read(int reg) {
    switch (reg) {
    case 2: { ppu_catch_up_now(); uint8_t r = (uint8_t)(status & 0xE0); status &= 0x7F; w_latch = 0; return r; }
    case 4: return oam[oam_addr];
    case 7: {
        uint16_t a = v & 0x3FFF; uint8_t r;
        if (a >= 0x3F00) { r = pal[pal_index(a)]; rbuf = vram[nt_index(a)]; }
        else { r = rbuf; rbuf = a < 0x2000 ? chr_rd(a) : vram[nt_index(a)]; }
        v = (uint16_t)(v + ((ctrl & 4) ? 32 : 1));
        return r;
    }
    }
    return 0;
}
void ppu_write(int reg, uint8_t d) {
    if (reg != 4 && reg != 3) ppu_catch_up_now();
    switch (reg) {
    case 0: { uint8_t old = ctrl; ctrl = d; t = (uint16_t)((t & 0xF3FF) | (d & 3) << 10);
              if (!(old & 0x80) && (d & 0x80) && (status & 0x80)) nes_nmi_edge(); break; }
    case 1: mask = d; break;
    case 3: oam_addr = d; break;
    case 4: oam[oam_addr++] = d; break;
    case 5: if (!w_latch) { t = (uint16_t)((t & 0xFFE0) | d >> 3); fine_x = d & 7; w_latch = 1; }
            else { t = (uint16_t)((t & 0x8C1F) | (d & 7) << 12 | (d & 0xF8) << 2); w_latch = 0; }
            break;
    case 6: if (!w_latch) { t = (uint16_t)((t & 0x00FF) | (d & 0x3F) << 8); w_latch = 1; }
            else { t = (uint16_t)((t & 0xFF00) | d); v = t; w_latch = 0; }
            break;
    case 7: {
        uint16_t a = v & 0x3FFF;
        if (a >= 0x3F00) pal[pal_index(a)] = d & 0x3F;
        else if (a >= 0x2000) vram[nt_index(a)] = d;
        v = (uint16_t)(v + ((ctrl & 4) ? 32 : 1));
        break;
    }
    }
}
void ppu_oam_dma(const uint8_t *page) { for (int i = 0; i < 256; i++) oam[(oam_addr + i) & 0xFF] = page[i]; }
uint8_t ppu_peek_chr(uint16_t a) { return chr_rd((uint16_t)(a & 0x1FFF)); }
uint8_t ppu_peek_pal(int i) { return pal[pal_index((uint16_t)i)]; }
uint8_t ppu_peek_ctrl(void) { return ctrl; }
uint32_t ppu_rgb(int c) { return rgba[c & 0x3F]; }
