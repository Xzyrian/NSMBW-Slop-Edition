/* snes_ppu.c - the SNES picture, a row at a time (snes_cpu.c draws screen row V-1 when line V's
 * hblank comes, so changes mid-frame - SMW's status bar IRQ, HDMA windows and gradients - land
 * on the right rows).
 *
 * Done: registers $2100-$213F (VRAM / OAM / CGRAM ports, scroll latches, VRAM remapping),
 * background modes 0 and 1 (2 / 4 bpp, 8 and 16 pixel tiles, 32 / 64 maps, mosaic), mode 7 (no
 * EXTBG), sprites (all sizes, both name tables, priority rotation, 32 a line), the two windows with
 * their logic for each layer and the colour window, main / sub screens, colour math (add / sub,
 * half, fixed colour, clip to black), brightness and force blank. Not done: hi-res modes 5-6,
 * offset-per-tile (2, 4, 6: drawn as mode 1), interlace, direct colour. */
#include "snes_ppu.h"
#include <string.h>
#include <stdlib.h>

uint32_t sppu_fb[256 * 224];
int sppu_overscan;
static uint16_t vram[0x8000], cgram[256];
static uint8_t oam[544];
static uint8_t inidisp = 0x80, objsel, bgmode, mosaic, bgsc[4], bgnba[2], vmain, setini;
static uint16_t hofs[4], vofs[4], m7hofs, m7vofs; static uint8_t ofs_latch, m7_latch;
static int16_t m7[6];                       /* a b c d x y */
static uint8_t m7sel;
static uint16_t vaddr, vprefetch;
static uint16_t oamaddr, oam_reload; static uint8_t oam_latch, oam_prio;
static uint8_t cgaddr, cg_latch; static int cg_high;
static uint8_t wsel[3], wpos[4], wlog[2], tm, ts, tmw, tsw, cgwsel, cgadsub, fixr, fixg, fixb;
static uint16_t hlatch, vlatch; static int hv_flip_h, hv_flip_v, latched;
static uint8_t mdr;
static int mosaic_line0;

void sppu_reset(void) {
    memset(vram, 0, sizeof vram); memset(cgram, 0, sizeof cgram); memset(oam, 0, sizeof oam);
    inidisp = 0x80; objsel = bgmode = mosaic = vmain = setini = 0; memset(bgsc, 0, 4); bgnba[0] = bgnba[1] = 0;
    memset(hofs, 0, sizeof hofs); memset(vofs, 0, sizeof vofs); ofs_latch = m7_latch = 0; memset(m7, 0, sizeof m7); m7sel = 0;
    vaddr = vprefetch = 0; oamaddr = oam_reload = 0; oam_latch = oam_prio = 0; cgaddr = 0; cg_latch = 0; cg_high = 0;
    memset(wsel, 0, 3); memset(wpos, 0, 4); wlog[0] = wlog[1] = 0; tm = ts = tmw = tsw = cgwsel = cgadsub = 0; fixr = fixg = fixb = 0;
    latched = 0; memset(sppu_fb, 0, sizeof sppu_fb);
}
void sppu_frame_begin(void) { oamaddr = oam_reload; mosaic_line0 = 1; }

/* ------------------------------------------------------------------ registers */
static uint16_t vremap(uint16_t a) {
    switch ((vmain >> 2) & 3) {
    case 1: return (uint16_t)((a & 0xFF00) | (a << 3 & 0xF8) | (a >> 5 & 7));
    case 2: return (uint16_t)((a & 0xFE00) | (a << 3 & 0x1F8) | (a >> 6 & 7));
    case 3: return (uint16_t)((a & 0xFC00) | (a << 3 & 0x3F8) | (a >> 7 & 7));
    }
    return a;
}
static int vinc(void) { static const int s[4] = {1, 32, 128, 128}; return s[vmain & 3]; }
void sppu_latch_counters(int h, int v) { hlatch = (uint16_t)h; vlatch = (uint16_t)v; latched = 1; }
void sppu_write(uint8_t r, uint8_t v) {
    switch (r) {
    case 0x00: inidisp = v; break;
    case 0x01: objsel = v; break;
    case 0x02: oam_reload = (uint16_t)((oam_reload & 0x200) | v << 1); oamaddr = oam_reload; break;
    case 0x03: oam_reload = (uint16_t)((oam_reload & 0x1FE) | (v & 1) << 9); oam_prio = v & 0x80; oamaddr = oam_reload; break;
    case 0x04:
        if (oamaddr >= 512) oam[512 + (oamaddr & 31)] = v;
        else if (!(oamaddr & 1)) oam_latch = v;
        else { oam[oamaddr - 1] = oam_latch; oam[oamaddr] = v; }
        oamaddr = (uint16_t)((oamaddr + 1) & 0x3FF);
        break;
    case 0x05: bgmode = v; break;
    case 0x06: mosaic = v; break;
    case 0x07: case 0x08: case 0x09: case 0x0A: bgsc[r - 7] = v; break;
    case 0x0B: case 0x0C: bgnba[r - 0x0B] = v; break;
    case 0x0D: m7hofs = (uint16_t)(v << 8 | m7_latch); m7_latch = v; /* fall through to BG1 */
    case 0x0F: case 0x11: case 0x13: {
        int n = (r - 0x0D) >> 1;
        hofs[n] = (uint16_t)((v << 8) | (ofs_latch & ~7) | ((hofs[n] >> 8) & 7));   /* (all 16 bits kept: the next write takes bits 8-10; drawn & 0x3FF) */
        ofs_latch = v; break; }
    case 0x0E: m7vofs = (uint16_t)(v << 8 | m7_latch); m7_latch = v; /* fall through */
    case 0x10: case 0x12: case 0x14: {
        int n = (r - 0x0E) >> 1;
        vofs[n] = (uint16_t)((v << 8) | ofs_latch);
        ofs_latch = v; break; }
    case 0x15: vmain = v; break;
    case 0x16: vaddr = (uint16_t)((vaddr & 0xFF00) | v); vprefetch = vram[vremap(vaddr) & 0x7FFF]; break;
    case 0x17: vaddr = (uint16_t)((vaddr & 0x00FF) | v << 8); vprefetch = vram[vremap(vaddr) & 0x7FFF];
        { static int lg = -1; if (lg < 0) lg = getenv("SNES_VRAM_LOG") != NULL; if (lg) snes_log("vram: address %04X (vmain %02X)", vaddr, vmain); }
        break;
    case 0x18: { uint16_t a = vremap(vaddr) & 0x7FFF; vram[a] = (uint16_t)((vram[a] & 0xFF00) | v); if (!(vmain & 0x80)) vaddr = (uint16_t)(vaddr + vinc()); break; }
    case 0x19: { uint16_t a = vremap(vaddr) & 0x7FFF; vram[a] = (uint16_t)((vram[a] & 0x00FF) | v << 8); if (vmain & 0x80) vaddr = (uint16_t)(vaddr + vinc()); break; }
    case 0x1A: m7sel = v; break;
    case 0x1B: case 0x1C: case 0x1D: case 0x1E: case 0x1F: case 0x20:
        m7[r - 0x1B] = (int16_t)(v << 8 | m7_latch); m7_latch = v; break;
    case 0x21: cgaddr = v; cg_high = 0; break;
    case 0x22:
        if (!cg_high) { cg_latch = v; cg_high = 1; }
        else { cgram[cgaddr] = (uint16_t)(((v & 0x7F) << 8) | cg_latch); cgaddr++; cg_high = 0; }
        break;
    case 0x23: case 0x24: case 0x25: wsel[r - 0x23] = v; break;
    case 0x26: case 0x27: case 0x28: case 0x29: wpos[r - 0x26] = v; break;
    case 0x2A: case 0x2B: wlog[r - 0x2A] = v; break;
    case 0x2C: tm = v; break;
    case 0x2D: ts = v; break;
    case 0x2E: tmw = v; break;
    case 0x2F: tsw = v; break;
    case 0x30: cgwsel = v; break;
    case 0x31: cgadsub = v; break;
    case 0x32:
        if (v & 0x20) fixr = v & 31;
        if (v & 0x40) fixg = v & 31;
        if (v & 0x80) fixb = v & 31;
        break;
    case 0x33: setini = v; sppu_overscan = (v >> 2) & 1; break;
    }
}
uint8_t sppu_read(uint8_t r) {
    switch (r) {
    case 0x34: case 0x35: case 0x36: {
        int32_t p = (int32_t)m7[0] * (int8_t)(m7[1] >> 8);
        return mdr = (uint8_t)(p >> ((r - 0x34) * 8)); }
    case 0x37: sppu_latch_counters(0, 0); return mdr;
    case 0x38: {
        uint8_t v = oamaddr >= 512 ? oam[512 + (oamaddr & 31)] : oam[oamaddr];
        oamaddr = (uint16_t)((oamaddr + 1) & 0x3FF); return mdr = v; }
    case 0x39: { uint8_t v = (uint8_t)vprefetch; if (!(vmain & 0x80)) { vprefetch = vram[vremap(vaddr) & 0x7FFF]; vaddr = (uint16_t)(vaddr + vinc()); } return mdr = v; }
    case 0x3A: { uint8_t v = (uint8_t)(vprefetch >> 8); if (vmain & 0x80) { vprefetch = vram[vremap(vaddr) & 0x7FFF]; vaddr = (uint16_t)(vaddr + vinc()); } return mdr = v; }
    case 0x3B: { uint8_t v = cg_high ? (uint8_t)(cgram[cgaddr] >> 8) : (uint8_t)cgram[cgaddr]; if (cg_high) cgaddr++; cg_high ^= 1; return mdr = v; }
    case 0x3C: { uint8_t v = hv_flip_h ? (uint8_t)(hlatch >> 8 & 1) : (uint8_t)hlatch; hv_flip_h ^= 1; return v; }
    case 0x3D: { uint8_t v = hv_flip_v ? (uint8_t)(vlatch >> 8 & 1) : (uint8_t)vlatch; hv_flip_v ^= 1; return v; }
    case 0x3E: return 0x01;
    case 0x3F: { uint8_t v = (uint8_t)(0x03 | (latched ? 0x40 : 0)); latched = 0; hv_flip_h = hv_flip_v = 0; return v; }
    }
    return mdr;
}

/* ------------------------------------------------------------------ a row */
/* layer ids: 0-3 BG1-4, 4 OBJ, 5 backdrop */
static uint8_t lpix[5][256];                /* the colour (CGRAM index; 0 transparent) */
static uint8_t lpri[5][256];
static uint8_t objpal[256];                 /* (the sprite's palette: colour math only for 4-7) */
static uint8_t win[6][256];                 /* 1 = inside the layer's window area (after its logic); [5] the colour window */

static void windows(void) {
    for (int l = 0; l < 6; l++) {
        uint8_t s = l < 4 ? (uint8_t)(wsel[l >> 1] >> ((l & 1) * 4)) : l == 4 ? wsel[2] : (uint8_t)(wsel[2] >> 4);
        int lg = l < 4 ? (wlog[0] >> (l * 2)) & 3 : l == 4 ? wlog[1] & 3 : (wlog[1] >> 2) & 3;
        int e1 = s & 2, i1 = s & 1, e2 = s & 8, i2 = s & 4;
        for (int x = 0; x < 256; x++) {
            int a = (x >= wpos[0] && x <= wpos[1]) ^ (i1 != 0), b = (x >= wpos[2] && x <= wpos[3]) ^ (i2 != 0), v;
            if (e1 && e2) v = lg == 0 ? (a | b) : lg == 1 ? (a & b) : lg == 2 ? (a ^ b) : !(a ^ b);
            else if (e1) v = a; else if (e2) v = b; else v = 0;
            win[l][x] = (uint8_t)v;
        }
    }
}
static void bg_row(int n, int bpp, int V, int pal_base) {
    uint8_t *px = lpix[n], *pr = lpri[n];
    memset(px, 0, 256);
    int big = (bgmode >> (4 + n)) & 1, ts = big ? 16 : 8;
    uint16_t base = (uint16_t)((bgsc[n] & 0xFC) << 8);
    int wide = bgsc[n] & 1, tall = (bgsc[n] >> 1) & 1;
    uint16_t cbase = (uint16_t)(((bgnba[n >> 1] >> ((n & 1) * 4)) & 15) << 12);
    int mos = (mosaic >> n) & 1 ? (mosaic >> 4) + 1 : 1;
    int line = V; if (mos > 1) line = V - (V - 1) % mos;
    int ty = (line + (vofs[n] & 0x3FF)) & 0x3FF;
    int words = bpp * 4;
    for (int x = 0; x < 256; x++) {
        int sx = mos > 1 ? x - x % mos : x;
        int tx = (sx + (hofs[n] & 0x3FF)) & 0x3FF;
        int mx = tx / ts, my = ty / ts;
        uint16_t scr = (uint16_t)(((mx >> 5) & wide ? 0x400 : 0) + ((my >> 5) & tall ? (wide ? 0x800 : 0x400) : 0));
        uint16_t e = vram[(uint16_t)(base + scr + (my & 31) * 32 + (mx & 31)) & 0x7FFF];
        int t = e & 0x3FF, pal = (e >> 10) & 7, pri = (e >> 13) & 1;
        int fx = tx % ts, fy = ty % ts;
        if (e & 0x4000) fx = ts - 1 - fx;
        if (e & 0x8000) fy = ts - 1 - fy;
        if (big) { t += (fx >> 3) + ((fy >> 3) << 4); fx &= 7; fy &= 7; }
        uint16_t a = (uint16_t)(cbase + (t & 0x3FF) * words + fy);
        int bit = 7 - fx, c = 0;
        uint16_t w0 = vram[a & 0x7FFF];
        c = ((w0 >> bit) & 1) | ((w0 >> (bit + 8)) & 1) << 1;
        if (bpp >= 4) { uint16_t w1 = vram[(a + 8) & 0x7FFF]; c |= ((w1 >> bit) & 1) << 2 | ((w1 >> (bit + 8)) & 1) << 3; }
        if (bpp == 8) { uint16_t w2 = vram[(a + 16) & 0x7FFF], w3 = vram[(a + 24) & 0x7FFF];
            c |= ((w2 >> bit) & 1) << 4 | ((w2 >> (bit + 8)) & 1) << 5 | ((w3 >> bit) & 1) << 6 | ((w3 >> (bit + 8)) & 1) << 7; }
        if (!c) continue;
        px[x] = (uint8_t)(pal_base + (bpp == 8 ? c : pal * (1 << bpp) + c));
        pr[x] = (uint8_t)pri;
    }
}
static void m7_row(int V) {
    uint8_t *px = lpix[0], *pr = lpri[0];
    memset(px, 0, 256);
    int a = m7[0], b = m7[1], c = m7[2], d = m7[3];
    int cx = ((int)(m7[4] << 3)) >> 3, cy = ((int)(m7[5] << 3)) >> 3;
    int hs = ((int)(m7hofs << 3) << 16) >> 19, vs = ((int)(m7vofs << 3) << 16) >> 19;
    int y = (m7sel & 2) ? 255 - V : V;
    for (int x = 0; x < 256; x++) {
        int sx = (m7sel & 1) ? 255 - x : x;
        int X = (a * (sx + hs - cx) + b * (y + vs - cy)) / 256 + cx;   /* (approximately as the hardware's fixed point) */
        int Y = (c * (sx + hs - cx) + d * (y + vs - cy)) / 256 + cy;
        int out = (X & ~1023) || (Y & ~1023);
        if (out && (m7sel & 0xC0) == 0x80) continue;
        int tile = out && (m7sel & 0xC0) == 0xC0 ? 0 : vram[((Y >> 3) & 127) * 128 + ((X >> 3) & 127)] & 0xFF;
        uint8_t col = (uint8_t)(vram[tile * 64 + (Y & 7) * 8 + (X & 7)] >> 8);
        if (!col) continue;
        px[x] = col; pr[x] = 0;
    }
}
static const int OBJSZ[8][2][2] = {
    {{8, 8}, {16, 16}}, {{8, 8}, {32, 32}}, {{8, 8}, {64, 64}}, {{16, 16}, {32, 32}},
    {{16, 16}, {64, 64}}, {{32, 32}, {64, 64}}, {{16, 32}, {32, 64}}, {{16, 32}, {32, 32}}};
static void obj_row(int V) {
    uint8_t *px = lpix[4], *pr = lpri[4];
    memset(px, 0, 256);
    int first = oam_prio ? (oamaddr >> 2) & 0x7F : 0;
    int list[32], n = 0;
    for (int k = 0; k < 128 && n < 32; k++) {
        int i = (first + k) & 0x7F;
        uint8_t *o = &oam[i * 4];
        int hi = (oam[512 + i / 4] >> ((i & 3) * 2)) & 3;
        int big = hi >> 1, w = OBJSZ[objsel >> 5][big][0], h = OBJSZ[objsel >> 5][big][1];
        int x = o[0] | (hi & 1) << 8; if (x >= 256) x -= 512;
        int dy = (V - o[1]) & 0xFF;
        if (dy >= h || x <= -w) continue;
        list[n++] = i;
    }
    uint16_t base = (uint16_t)((objsel & 7) << 13), gap = (uint16_t)((((objsel >> 3) & 3) + 1) << 12);
    for (int j = n - 1; j >= 0; j--) {                  /* (the first in the list ends up in front) */
        int i = list[j]; uint8_t *o = &oam[i * 4];
        int hi = (oam[512 + i / 4] >> ((i & 3) * 2)) & 3;
        int big = hi >> 1, w = OBJSZ[objsel >> 5][big][0], h = OBJSZ[objsel >> 5][big][1];
        int x = o[0] | (hi & 1) << 8; if (x >= 256) x -= 512;
        int dy = (V - o[1]) & 0xFF;
        uint8_t at = o[3];
        if (at & 0x80) dy = h - 1 - dy;
        int pal = (at >> 1) & 7, pri = (at >> 4) & 3;
        for (int dx = 0; dx < w; dx++) {
            int sx = x + dx; if (sx < 0 || sx > 255) continue;
            int fx = (at & 0x40) ? w - 1 - dx : dx;
            int t = o[2], col = ((t & 15) + (fx >> 3)) & 15, row = ((t >> 4) + (dy >> 3)) & 15;
            uint16_t a = (uint16_t)(base + ((at & 1) ? gap : 0) + (row * 16 + col) * 16 + (dy & 7));
            int bit = 7 - (fx & 7);
            uint16_t w0 = vram[a & 0x7FFF], w1 = vram[(a + 8) & 0x7FFF];
            int c = ((w0 >> bit) & 1) | ((w0 >> (bit + 8)) & 1) << 1 | ((w1 >> bit) & 1) << 2 | ((w1 >> (bit + 8)) & 1) << 3;
            if (!c) continue;
            px[sx] = (uint8_t)(128 + pal * 16 + c); pr[sx] = (uint8_t)pri; objpal[sx] = (uint8_t)pal;
        }
    }
}
/* the layers front to back for the mode: (layer, priority) */
typedef struct { int8_t l, p; } lp_t;
static const lp_t ORDER0[] = {{4,3},{0,1},{1,1},{4,2},{0,0},{1,0},{4,1},{2,1},{3,1},{4,0},{2,0},{3,0},{-1,0}};
static const lp_t ORDER1[] = {{4,3},{0,1},{1,1},{4,2},{0,0},{1,0},{4,1},{2,1},{4,0},{2,0},{-1,0}};
static const lp_t ORDER1H[] = {{2,1},{4,3},{0,1},{1,1},{4,2},{0,0},{1,0},{4,1},{4,0},{2,0},{-1,0}};
static const lp_t ORDER7[] = {{4,3},{4,2},{4,1},{0,0},{4,0},{-1,0}};
static int pick(const lp_t *ord, uint8_t on, uint8_t wmask, int x, int *layer) {
    for (; ord->l >= 0; ord++) {
        int l = ord->l;
        if (!(on & 1 << l) || !lpix[l][x] || lpri[l][x] != ord->p) continue;
        if ((wmask & 1 << l) && win[l][x]) continue;
        *layer = l; return lpix[l][x];
    }
    *layer = 5; return 0;
}
static inline int region(int mode, int inside) { return mode == 0 ? 0 : mode == 1 ? !inside : mode == 2 ? inside : 1; }
void sppu_render_row(int row) {
    if (row < 0 || row >= 224) return;
    uint32_t *out = &sppu_fb[row * 256];
    if (inidisp & 0x80) { for (int x = 0; x < 256; x++) out[x] = 0xFF000000u; return; }
    int V = row + 1, mode = bgmode & 7;
    const lp_t *ord;
    if (mode == 0) { bg_row(0, 2, V, 0); bg_row(1, 2, V, 32); bg_row(2, 2, V, 64); bg_row(3, 2, V, 96); ord = ORDER0; }
    else if (mode == 7) { m7_row(V); memset(lpix[1], 0, 256); memset(lpix[2], 0, 256); memset(lpix[3], 0, 256); ord = ORDER7; }
    else {
        bg_row(0, mode == 3 || mode == 4 ? 8 : 4, V, 0);
        bg_row(1, mode == 3 ? 4 : mode == 4 ? 2 : 4, V, 0);
        if (mode == 1) bg_row(2, 2, V, 0); else memset(lpix[2], 0, 256);
        memset(lpix[3], 0, 256);
        ord = (mode == 1 && (bgmode & 8)) ? ORDER1H : ORDER1;
    }
    obj_row(V);
    windows();
    int bright = inidisp & 15;
    static int lmask = -2; if (lmask == -2) { const char *e = getenv("SNES_LAYERS"); lmask = e ? (int)strtol(e, 0, 16) : -1; }   /* (testing: only these layers) */
    uint8_t tm_ = tm, ts_ = ts; if (lmask >= 0) { tm &= (uint8_t)lmask; ts &= (uint8_t)lmask; }
    for (int x = 0; x < 256; x++) {
        int ml, sl;
        int mc = pick(ord, tm, tmw, x, &ml);
        int sc = pick(ord, ts, tsw, x, &sl);
        uint16_t main_c = cgram[mc], sub_c;
        int sub_fixed = 0;
        if (!(cgwsel & 2) || sl == 5) { sub_c = (uint16_t)(fixr | fixg << 5 | fixb << 10); sub_fixed = (cgwsel & 2) != 0; }
        else sub_c = cgram[sc];
        int inw = win[5][x];
        int black = region((cgwsel >> 6) & 3, inw), nomath = region((cgwsel >> 4) & 3, inw);
        int r = main_c & 31, g = (main_c >> 5) & 31, b = (main_c >> 10) & 31;
        if (black) r = g = b = 0;
        int math_on = (cgadsub >> ml) & 1;
        if (ml == 4 && objpal[x] < 4) math_on = 0;
        if (math_on && !nomath) {
            int sr = sub_c & 31, sg = (sub_c >> 5) & 31, sb = (sub_c >> 10) & 31;
            int half = (cgadsub & 0x40) && !black && !sub_fixed;
            if (cgadsub & 0x80) { r -= sr; g -= sg; b -= sb; if (half) { r >>= 1; g >>= 1; b >>= 1; } if (r < 0) r = 0; if (g < 0) g = 0; if (b < 0) b = 0; }
            else { r += sr; g += sg; b += sb; if (half) { r >>= 1; g >>= 1; b >>= 1; } if (r > 31) r = 31; if (g > 31) g = 31; if (b > 31) b = 31; }
        }
        r = r * bright / 15; g = g * bright / 15; b = b * bright / 15;
        out[x] = 0xFF000000u | (uint32_t)(r << 3 | r >> 2) << 16 | (uint32_t)(g << 3 | g >> 2) << 8 | (uint32_t)(b << 3 | b >> 2);
    }
    tm = tm_; ts = ts_;
}
/* (testing) the PPU's state in words */
#include <stdio.h>
void sppu_debug(char *out, int n) {
    snprintf(out, n, "inidisp %02X mode %02X mosaic %02X sc %02X %02X %02X %02X nba %02X %02X ofs BG1 %d,%d BG2 %d,%d BG3 %d,%d tm %02X ts %02X tmw %02X tsw %02X cgwsel %02X cgadsub %02X objsel %02X w %02X %02X %02X pos %d-%d %d-%d vmain %02X",
             inidisp, bgmode, mosaic, bgsc[0], bgsc[1], bgsc[2], bgsc[3], bgnba[0], bgnba[1], hofs[0] & 0x3FF, vofs[0] & 0x3FF, hofs[1] & 0x3FF, vofs[1] & 0x3FF, hofs[2] & 0x3FF, vofs[2] & 0x3FF,
             tm, ts, tmw, tsw, cgwsel, cgadsub, objsel, wsel[0], wsel[1], wsel[2], wpos[0], wpos[1], wpos[2], wpos[3], vmain);
}
const uint16_t *sppu_vram(void) { return vram; }
/* the PPU's state as other code reads it (smw_stage.c: the level's pictures) */
const uint16_t *sppu_cgram(void) { return cgram; }
void sppu_bg(int n, uint8_t *sc, uint8_t *nba, uint16_t *hofs_, uint16_t *vofs_, uint8_t *mode) {
    *sc = bgsc[n & 3]; *nba = (uint8_t)((bgnba[(n & 3) >> 1] >> (((n & 3) & 1) * 4)) & 15);
    *hofs_ = hofs[n & 3] & 0x3FF; *vofs_ = vofs[n & 3] & 0x3FF; *mode = bgmode;
}
