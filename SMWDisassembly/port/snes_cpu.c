/* snes_cpu.c - the machine under the recompiled SMW: the bus (LoROM), the CPU's registers
 * ($4200-$421F: interrupts, multiply / divide, the joypads), DMA and HDMA, the 65816 call model,
 * interrupts and the frame's time. The recompiled code (out/smw_bNN.c) runs in a coroutine;
 * snes_run_frame() resumes it until the next vblank. The same model as SMB3's nes_cpu.c.
 *
 * Calls. JSR / JSL push their return address (the stack in WRAM is the truth) and call
 * snes_call() / snes_call_long(), which run the target until an RTS / RTL / RTI comes back. Each
 * call is a frame: the address it expects and S before the push. A return to the frame whose
 * address is the one pulled, with S as it was, comes back; any other (an address pushed by hand)
 * is a jump. A frame whose return address was pulled some other way (ExecutePtr pulls its
 * caller's to read the table after the JSL) is stale: the next jump in it leaves its C frame.
 *
 * Time. Every instruction adds its cycles (about 8 master clocks each: 170 a line, 262 lines).
 * Line V is drawn as screen row V-1 when its hblank comes (the PPU as set then); HDMA runs at
 * each hblank for the next line; vblank at line 225 (the coroutine yields: the frame is done;
 * then NMI); the IRQ at VTIME (/ HTIME). Interrupts are taken between instructions. */
#include "snes.h"
#include "snes_gen.h"
#include "snes_ppu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

snes_cpu snes_R;
uint8_t snes_wram[0x20000];
const uint8_t *snes_rom; uint32_t snes_rom_mask;
uint64_t snes_cyc, snes_ev;
static uint8_t *rom_copy; static uint32_t rom_size;
static uint8_t sram[0x800];
static char err[256];
static void (*log_fn)(const char *);
void snes_log(const char *fmt, ...) {
    char b[512]; va_list ap; va_start(ap, fmt); vsnprintf(b, sizeof b, fmt, ap); va_end(ap);
    if (log_fn) log_fn(b); else fprintf(stderr, "[snes] %s\n", b);
}
void snes_set_log(void (*fn)(const char *)) { log_fn = fn; }

/* ------------------------------------------------------------------ the coroutine */
static void game_main(void);
static int failed, running;
#ifdef _WIN32
#include <windows.h>
static LPVOID host_fiber, game_fiber;
static void WINAPI game_entry(LPVOID p) { (void)p; game_main(); }
static void coro_new(void) { if (game_fiber) DeleteFiber(game_fiber); game_fiber = CreateFiber(8 << 20, game_entry, NULL); }
static void to_game(void) { host_fiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(NULL); SwitchToFiber(game_fiber); }
static void to_host(void) { SwitchToFiber(host_fiber); }
#else
#include <ucontext.h>
static ucontext_t host_ctx, game_ctx; static char *game_stack;
static void coro_new(void) {
    if (!game_stack) game_stack = malloc(8 << 20);
    getcontext(&game_ctx); game_ctx.uc_stack.ss_sp = game_stack; game_ctx.uc_stack.ss_size = 8 << 20; game_ctx.uc_link = NULL;
    makecontext(&game_ctx, game_main, 0);
}
static void to_game(void) { swapcontext(&host_ctx, &game_ctx); }
static void to_host(void) { swapcontext(&game_ctx, &host_ctx); }
#endif
static void fatal(const char *fmt, ...) {
    va_list ap; va_start(ap, fmt); vsnprintf(err, sizeof err, fmt, ap); va_end(ap);
    snes_log("stopped: %s", err);
    failed = 1;
    for (;;) to_host();                                 /* never resumed */
}

/* ------------------------------------------------------------------ time */
#define CYC_LINE 170
#define HBLANK_AT 137                                  /* (cycles into a line: H 274) */
#define LINES 262
static uint64_t frame_c0;                              /* the frame's first cycle (V 0) */
static int hb_line;                                    /* the next line whose hblank is due */
static int vbl_done, nmi_pending, irq_line, irq_done, nmi_flag, timeup, hdma_inited;
static uint64_t frames;
static uint32_t ints_taken;
static uint8_t nmitimen, wrio = 0xFF, mdmaen, hdmaen;
static uint16_t htime = 0x1FF, vtime = 0x1FF;
static uint64_t irq_from;                              /* (when the IRQ's setting last changed: it fires when the beam reaches it after that, not at once) */
static int cur_line(void) { return (int)((snes_cyc - frame_c0) / CYC_LINE); }
static int cur_h(void) { return (int)((snes_cyc - frame_c0) % CYC_LINE); }

/* ------------------------------------------------------------------ the joypads, multiply / divide */
static uint16_t pad[2], joy[4];
static uint32_t pad_shift[2]; static uint8_t strobe;
void snes_set_buttons(int p, uint16_t b) { if (p >= 0 && p < 2) pad[p] = b; }
static uint8_t wrmpya = 0xFF, wrdivb; static uint16_t wrdiv = 0xFFFF, rddiv, rdmpy;
static uint32_t wram_port;

/* ------------------------------------------------------------------ DMA / HDMA */
static uint8_t dma[8][16];                             /* $43x0-$43xF */
static const uint8_t TRANSFER[8][4] = {{0,0,0,0},{0,1,0,1},{0,0,0,0},{0,0,1,1},{0,1,2,3},{0,1,0,1},{0,0,0,0},{0,0,1,1}};
static const int TLEN[8] = {1, 2, 2, 4, 4, 4, 2, 4};
static void bbus_wr(uint8_t reg, uint8_t v) {
    if (reg <= 0x3F) { snes_ppu_catch_up(); sppu_write(reg, v); }
    else if (reg <= 0x7F) sapu_port_wr(reg & 3, v);
    else if (reg == 0x80) { snes_wram[wram_port] = v; wram_port = (wram_port + 1) & 0x1FFFF; }
}
static uint8_t bbus_rd(uint8_t reg) {
    if (reg <= 0x3F) return sppu_read(reg);
    if (reg <= 0x7F) return sapu_port_rd(reg & 3);
    if (reg == 0x80) { uint8_t v = snes_wram[wram_port]; wram_port = (wram_port + 1) & 0x1FFFF; return v; }
    return 0;
}
static void dma_run(uint8_t mask) {
    for (int c = 0; c < 8; c++) {
        if (!(mask & 1 << c)) continue;
        uint8_t *d = dma[c], ctl = d[0], b = d[1];
        uint16_t a = (uint16_t)(d[2] | d[3] << 8); uint8_t bank = d[4];
        uint32_t n = (uint32_t)(d[5] | d[6] << 8); if (!n) n = 0x10000;
        int step = (ctl & 0x08) ? 0 : (ctl & 0x10) ? -1 : 1, mode = ctl & 7, k = 0;
        { static int lg = -1; if (lg < 0) lg = getenv("SNES_DMA_LOG") != NULL;
          if (lg) snes_log("dma %d: ctl %02X $21%02X %s $%02X:%04X, %u bytes", c, ctl, b, ctl & 0x80 ? "->" : "<-", bank, a, n); }
        while (n--) {
            uint8_t reg = (uint8_t)(b + TRANSFER[mode][k & 3]); k++;
            uint32_t ad = (uint32_t)bank << 16 | a;
            if (ctl & 0x80) WR8(ad, bbus_rd(reg)); else bbus_wr(reg, RD8(ad));
            a = (uint16_t)(a + step);
            snes_cyc += 1;                             /* (8 master clocks a byte) */
        }
        d[2] = (uint8_t)a; d[3] = (uint8_t)(a >> 8); d[5] = d[6] = 0;
    }
}
/* HDMA: at the frame's start each channel on reloads; at each line's hblank its line counter
   decides whether it writes, for the next line. d[8..9] the table, d[10] the line counter,
   d[5..6] (indirect) the data address, d[7] its bank. */
static uint8_t hdma_done, hdma_do;
static void hdma_load(int c) {
    uint8_t *d = dma[c]; uint32_t t = (uint32_t)d[4] << 16 | (uint16_t)(d[8] | d[9] << 8);
    uint8_t lc = RD8(t); t = (t & 0xFF0000) | (uint16_t)(t + 1);
    d[10] = lc;
    if (!lc) { hdma_done |= (uint8_t)(1 << c); }
    if (d[0] & 0x40) { d[5] = RD8(t); t = (t & 0xFF0000) | (uint16_t)(t + 1); d[6] = RD8(t); t = (t & 0xFF0000) | (uint16_t)(t + 1); }
    d[8] = (uint8_t)t; d[9] = (uint8_t)(t >> 8);
    hdma_do |= (uint8_t)(1 << c);
}
static void hdma_init(void) {
    hdma_done = 0; hdma_do = 0;
    for (int c = 0; c < 8; c++) {
        if (!(hdmaen & 1 << c)) continue;
        dma[c][8] = dma[c][2]; dma[c][9] = dma[c][3];
        hdma_load(c);
    }
}
static void hdma_run(void) {
    for (int c = 0; c < 8; c++) {
        uint8_t bit = (uint8_t)(1 << c);
        if (!(hdmaen & bit) || (hdma_done & bit)) continue;
        uint8_t *d = dma[c];
        if (hdma_do & bit) {
            int mode = d[0] & 7;
            for (int k = 0; k < TLEN[mode]; k++) {
                uint32_t src;
                if (d[0] & 0x40) { src = (uint32_t)d[7] << 16 | (uint16_t)(d[5] | d[6] << 8); uint16_t x = (uint16_t)(d[5] | d[6] << 8) + 1; d[5] = (uint8_t)x; d[6] = (uint8_t)(x >> 8); }
                else { src = (uint32_t)d[4] << 16 | (uint16_t)(d[8] | d[9] << 8); uint16_t x = (uint16_t)(d[8] | d[9] << 8) + 1; d[8] = (uint8_t)x; d[9] = (uint8_t)(x >> 8); }
                uint8_t reg = (uint8_t)(d[1] + TRANSFER[mode][k]);
                if (d[0] & 0x80) WR8(src, bbus_rd(reg)); else bbus_wr(reg, RD8(src));
            }
            snes_cyc += (uint64_t)TLEN[mode];
        }
        d[10]--;
        hdma_do &= (uint8_t)~bit;
        if (!(d[10] & 0x7F)) hdma_load(c);            /* (the next entry) */
        else if (d[10] & 0x80) hdma_do |= bit;        /* (repeat: a write every line) */
    }
}

/* ------------------------------------------------------------------ the bus: I/O, SRAM */
uint8_t snes_io_rd(uint32_t a) {
    uint8_t b = (uint8_t)(a >> 16); uint16_t o = (uint16_t)a;
    if (b >= 0x70 && b <= 0x7D && o < 0x8000) return sram[o & 0x7FF];
    if (b & 0x40) return 0;                            /* (nothing else there in LoROM) */
    if (o >= 0x2100 && o <= 0x21FF) {
        if (o >= 0x2134 && o <= 0x213F) snes_ppu_catch_up();
        return bbus_rd((uint8_t)o);
    }
    if (o == 0x4016 || o == 0x4017) {
        int p = o & 1; uint8_t r = (uint8_t)(pad_shift[p] >> 15 & 1);
        if (!strobe) pad_shift[p] = pad_shift[p] << 1 | 1;
        return r;
    }
    switch (o) {
    case 0x4210: { uint8_t r = (uint8_t)(nmi_flag << 7 | 0x02); nmi_flag = 0; return r; }
    case 0x4211: { uint8_t r = (uint8_t)(timeup << 7); timeup = 0; irq_line = 0; return r; }
    case 0x4212: {
        int v = cur_line(), h = cur_h();
        return (uint8_t)((v >= 225 ? 0x80 : 0) | (h >= HBLANK_AT || h < 4 ? 0x40 : 0));
    }
    case 0x4213: return wrio;
    case 0x4214: return (uint8_t)rddiv; case 0x4215: return (uint8_t)(rddiv >> 8);
    case 0x4216: return (uint8_t)rdmpy; case 0x4217: return (uint8_t)(rdmpy >> 8);
    }
    if (o >= 0x4218 && o <= 0x421F) { uint16_t j = joy[(o - 0x4218) >> 1]; return (o & 1) ? (uint8_t)(j >> 8) : (uint8_t)j; }
    if (o >= 0x4300 && o <= 0x437F) return dma[(o >> 4) & 7][o & 15];
    return 0;
}
void snes_io_wr(uint32_t a, uint8_t v) {
    uint8_t b = (uint8_t)(a >> 16); uint16_t o = (uint16_t)a;
    if (b >= 0x70 && b <= 0x7D && o < 0x8000) { sram[o & 0x7FF] = v; return; }
    if (b & 0x40) return;
    if (o >= 0x2100 && o <= 0x21FF) {
        if (o == 0x2181) wram_port = (wram_port & 0x1FF00) | v;
        else if (o == 0x2182) wram_port = (wram_port & 0x100FF) | (uint32_t)v << 8;
        else if (o == 0x2183) wram_port = (wram_port & 0x0FFFF) | (uint32_t)(v & 1) << 16;
        else bbus_wr((uint8_t)o, v);
        return;
    }
    if (o == 0x4016) { strobe = v & 1; if (strobe) { pad_shift[0] = pad[0]; pad_shift[1] = pad[1]; } return; }
    switch (o) {
    case 0x4200:
        if ((v & 0x80) && !(nmitimen & 0x80) && nmi_flag) { nmi_pending = 1; snes_ev = snes_cyc; }
        if ((v & 0x30) != (nmitimen & 0x30)) irq_from = snes_cyc;
        nmitimen = v; if (!(v & 0x30)) { irq_line = 0; timeup = 0; }
        snes_ev = snes_cyc; return;
    case 0x4201: if ((wrio & 0x80) && !(v & 0x80)) sppu_latch_counters(cur_h() * 2, cur_line()); wrio = v; return;
    case 0x4202: wrmpya = v; return;
    case 0x4203: rdmpy = (uint16_t)(wrmpya * v); rddiv = v; return;
    case 0x4204: wrdiv = (uint16_t)((wrdiv & 0xFF00) | v); return;
    case 0x4205: wrdiv = (uint16_t)((wrdiv & 0x00FF) | v << 8); return;
    case 0x4206: wrdivb = v; if (v) { rddiv = (uint16_t)(wrdiv / v); rdmpy = (uint16_t)(wrdiv % v); } else { rddiv = 0xFFFF; rdmpy = wrdiv; } return;
    case 0x4207: htime = (uint16_t)((htime & 0x100) | v); irq_from = snes_cyc; snes_ev = snes_cyc; return;
    case 0x4208: htime = (uint16_t)((htime & 0xFF) | (v & 1) << 8); irq_from = snes_cyc; snes_ev = snes_cyc; return;
    case 0x4209: vtime = (uint16_t)((vtime & 0x100) | v); irq_from = snes_cyc; snes_ev = snes_cyc; return;
    case 0x420A: vtime = (uint16_t)((vtime & 0xFF) | (v & 1) << 8); irq_from = snes_cyc; snes_ev = snes_cyc; return;
    case 0x420B: mdmaen = v; snes_ppu_catch_up(); dma_run(v); return;
    case 0x420C: hdmaen = v; return;
    case 0x420D: return;                               /* (FastROM: SMW is slow ROM) */
    }
    if (o >= 0x4300 && o <= 0x437F) { dma[(o >> 4) & 7][o & 15] = v; return; }
}
uint8_t *snes_wram_ptr(void) { return snes_wram; }
uint8_t *snes_sram_ptr(void) { return sram; }
uint32_t snes_sram_size(void) { return sizeof sram; }

/* ------------------------------------------------------------------ testing: tracing (interpreted) */
int snes_trace_on; static uint32_t trace_pcs[16]; static int ntrace;
void snes_trace(uint32_t pc) {
    for (int i = 0; i < ntrace; i++) if (trace_pcs[i] == pc || trace_pcs[i] == 0xFFFFFFFFu)
        snes_log("trace $%06X: A %04X X %04X Y %04X S %04X D %04X DB %02X P %02X (line %d)", pc, R.a, R.x, R.y, R.s, R.d, R.db, GETP(), cur_line());
}

/* ------------------------------------------------------------------ calls and returns */
#define MAXF 2048
static uint32_t f_pc[MAXF]; static uint16_t f_s[MAXF]; static int depth;
static const char *label_of(uint32_t pc) {
    static char b[96]; const snes_label *best = NULL;
    for (const snes_label *l = smw_labels; l->name; l++)
        if (l->bank == (int)(pc >> 16) && l->addr <= (pc & 0xFFFF) && (!best || l->addr > best->addr)) best = l;
    if (best) snprintf(b, sizeof b, "%s+%X", best->name, (unsigned)((pc & 0xFFFF) - best->addr)); else snprintf(b, sizeof b, "?");
    return b;
}
static int exec(uint32_t pc, int frame) {
    for (;;) {
        uint8_t bank = (uint8_t)(pc >> 16);
        R.pb = bank;
        int r;
        static int all = -1; if (all < 0) all = getenv("SNES_INTERP_ALL") != NULL;   /* (testing: every instruction interpreted) */
        if (bank < 16 && smw_banks[bank] && !all) r = smw_banks[bank]((uint16_t)pc);
        else r = SNES_INTERP(pc);
        if ((r >> 24) == 4) {
            pc = (uint32_t)r & 0xFFFFFF;
            if (all) ;
            else if ((pc & 0x408000) == 0x8000 || (pc >> 16) >= 0x80) {   /* (ROM code the source didn't map: worth knowing) */
                static int warned; if (warned++ < 20) snes_log("interpreting ROM code at $%06X (%s)", pc, label_of(pc));
            } else { static int seen; if (getenv("SNES_INTERP_LOG") && seen++ < 50) snes_log("interpreting RAM code at $%06X (A %04X X %04X Y %04X S %04X P %02X DB %02X)", pc, R.a, R.x, R.y, R.s, GETP(), R.db); }
            r = snes_interp(pc);
        }
        if ((r >> 24) == 2) return r;
        pc = (uint32_t)r & 0xFFFFFF;
        if (frame >= 0 && R.s >= f_s[frame]) return SNES_STALE(pc);
    }
}
static int frame_push(uint32_t expect, uint16_t s) {
    if (depth >= MAXF) fatal("calls nested too deep");
    f_pc[depth] = expect; f_s[depth] = s; return depth++;
}
static int call_n(uint32_t target, uint32_t expect, int pushed) {
    int k = frame_push(expect, (uint16_t)(R.s + pushed));
    int r = exec(target, k);
    depth = k;
    return r == SNES_RET(k) ? (int)expect : r;
}
int snes_call(uint32_t target, uint32_t expect) { return call_n(target, expect, 2); }
int snes_call_long(uint32_t target, uint32_t expect) { return call_n(target, expect, 3); }
int snes_unwind(int v) {
    if (v >= 0x1000000) return (v >> 24) == 3 ? SNES_JUMP(v) : v;
    for (int k = depth - 1; k >= 0; k--) {
        if (f_s[k] < R.s) continue;                       /* stale: its address was pulled already */
        if (f_s[k] > R.s) break;
        if (f_pc[k] == (uint32_t)v) return SNES_RET(k);
    }
    return SNES_JUMP(v);                                  /* a return to a pushed address: a jump */
}
static int interrupt(uint16_t vector, uint32_t pc) {
    int k = frame_push(pc, R.s);
    if (!R.e) PUSH8((uint8_t)(pc >> 16));
    PUSH16((uint16_t)pc); PUSH8(GETP());
    R.i = 1; R.dm = 0; ints_taken++;
    snes_cyc += 8;
    uint32_t to = RD16(vector);
    int r = exec(to, k);
    depth = k;
    return r == SNES_RET(k) ? -1 : r;                     /* -1: back where it was */
}
int snes_brk(uint32_t ret, int cop) {
    {   static int n; if (n++ < 3) {
            snes_log("%s at $%06X (%s), S %04X; calls:", cop ? "COP" : "BRK", (ret - 2) & 0xFFFFFF, label_of((ret - 2) & 0xFFFFFF), R.s);
            for (int k = depth - 1; k >= 0 && k >= depth - 12; k--) snes_log("   frame %d: back to $%06X (%s) S %04X", k, f_pc[k], label_of(f_pc[k]), f_s[k]);
        }
        if (n > 100) fatal("%s at $%06X: the game ran into data", cop ? "COP" : "BRK", (ret - 2) & 0xFFFFFF);
    }
    int r = interrupt(R.e ? 0xFFFE : cop ? 0xFFE4 : 0xFFE6, ret);
    return r == -1 ? SNES_JUMP(ret) : snes_unwind(r);
}
int snes_stp(uint32_t pc) { fatal("STP at $%06X (%s)", pc, label_of(pc)); return 0; }

/* ------------------------------------------------------------------ the frame's events */
static uint64_t irq_time(void) {                          /* this frame's IRQ, or never */
    int mode = (nmitimen >> 4) & 3;
    if (!mode || irq_done) return ~0ull;
    if (mode == 2 || mode == 3) {
        if (vtime >= LINES) return ~0ull;
        uint64_t t = frame_c0 + (uint64_t)vtime * CYC_LINE + (mode == 3 ? (htime > 339 ? 339 : htime) / 2 : 0);
        return t < irq_from ? ~0ull : t;                   /* (that line has gone by this frame) */
    }
    return ~0ull;                                          /* (H only: every line - SMW doesn't) */
}
static void set_next_event(void) {
    uint64_t next = frame_c0 + (uint64_t)LINES * CYC_LINE;
    if (hb_line <= 224) { uint64_t t = frame_c0 + (uint64_t)hb_line * CYC_LINE + HBLANK_AT; if (t < next) next = t; }
    if (!vbl_done) { uint64_t t = frame_c0 + 225ull * CYC_LINE; if (t < next) next = t; }
    uint64_t it = irq_time(); if (it < next) next = it;
    snes_ev = next;
    if (nmi_pending || (irq_line && !R.i)) snes_ev = snes_cyc;
}
static void hblank(int v);
static int in_hblank;
void snes_ppu_catch_up(void) {                            /* (a PPU change: the rows whose hblank has passed are drawn first) */
    if (in_hblank) return;
    while (hb_line <= 224 && snes_cyc >= frame_c0 + (uint64_t)hb_line * CYC_LINE + HBLANK_AT) {
        if (!hdma_inited) { hdma_init(); hdma_inited = 1; }
        hb_line++; hblank(hb_line - 1);
    }
}
static void hblank(int v) {                               /* (hb_line is already past v) */
    in_hblank = 1;
    if (v >= 1) sppu_render_row(v - 1);
    if (v < 224) hdma_run();                              /* (its writes are for the next row: no catching up) */
    in_hblank = 0;
}
static void auto_joypad(void) {
    if (!(nmitimen & 1)) return;
    joy[0] = pad[0]; joy[1] = pad[1]; joy[2] = joy[3] = 0;
}
/* events up to now; interrupts. -1: go on where it was; else a result to return */
static int events(uint32_t pc) {
    for (;;) {
        if (!hdma_inited && hdmaen) { hdma_init(); hdma_inited = 1; }
        uint64_t now = snes_cyc;
        while (hb_line <= 224 && now >= frame_c0 + (uint64_t)hb_line * CYC_LINE + HBLANK_AT) {
            if (!hdma_inited) { hdma_init(); hdma_inited = 1; }
            hb_line++; hblank(hb_line - 1);
        }
        if (!vbl_done && now >= frame_c0 + 225ull * CYC_LINE) {
            while (hb_line <= 224) { hb_line++; hblank(hb_line - 1); }
            vbl_done = 1; frames++; nmi_flag = 1; auto_joypad();
            to_host();                                    /* the frame is done; the host comes back for the next */
            if (nmitimen & 0x80) nmi_pending = 1;
        }
        if (now >= irq_time()) { irq_done = 1; timeup = 1; irq_line = 1; }
        if (now >= frame_c0 + (uint64_t)LINES * CYC_LINE) {
            frame_c0 += (uint64_t)LINES * CYC_LINE; vbl_done = 0; hb_line = 0; irq_done = 0; nmi_flag = 0; hdma_inited = 0;
            sppu_frame_begin();
            continue;
        }
        if (nmi_pending) { nmi_pending = 0; int r = interrupt(0xFFEA, pc); if (r != -1) return r; continue; }
        if (irq_line && !R.i) {
            { static int lg = -1; if (lg < 0) lg = getenv("SNES_IRQ_LOG") != NULL; if (lg) snes_log("irq: frame %llu line %d h %d (vtime %d htime %d, nmitimen %02X)", (unsigned long long)frames, cur_line(), cur_h(), vtime, htime, nmitimen); }
            int r = interrupt(0xFFEE, pc); if (r != -1) return r; continue; }
        break;
    }
    set_next_event();
    return -1;
}
int snes_check(uint32_t pc) {
    int r = events(pc);
    return r != -1 ? snes_unwind(r) : 0;
}
int snes_wai(uint32_t pc) {                               /* to the next interrupt */
    uint32_t n = ints_taken;
    while (ints_taken == n && !failed) {
        if (snes_cyc < snes_ev) snes_cyc = snes_ev;
        int r = events(pc); if (r != -1) return snes_unwind(r);
    }
    return 0;
}

/* ------------------------------------------------------------------ running */
static void game_main(void) {
    uint32_t pc = RD16(0xFFFC);
    snes_log("reset at $%04X", pc);
    int r = exec(pc, -1);
    fatal("the game's top level returned (%X)", r);
}
int snes_load(const uint8_t *data, uint32_t size) {
    if (size % 0x8000 == 512) { data += 512; size -= 512; }
    if (size < 0x8000 || size % 0x8000) return 0;
    free(rom_copy); rom_copy = malloc(size); memcpy(rom_copy, data, size); rom_size = size;
    snes_rom = rom_copy;
    uint32_t m = 1; while (m < size) m <<= 1; snes_rom_mask = m - 1;
    return 1;
}
void snes_reset(void) {
    memset(&snes_R, 0, sizeof snes_R); R.s = 0x1FF; R.i = 1; R.e = 1; R.mf = R.xf = 1;
    memset(snes_wram, 0x55, sizeof snes_wram);
    memset(dma, 0xFF, sizeof dma);
    nmitimen = 0; wrio = 0xFF; hdmaen = mdmaen = 0; htime = vtime = 0x1FF; wram_port = 0; irq_from = 0;
    sppu_reset(); sapu_reset();
    snes_cyc = 0; frame_c0 = 0; hb_line = 0; vbl_done = nmi_pending = irq_line = irq_done = nmi_flag = timeup = hdma_inited = 0;
    frames = 0; depth = 0; ints_taken = 0;
    failed = 0; err[0] = 0; running = 1;
    set_next_event();
    coro_new();
    ntrace = 0; snes_trace_on = 0;
    if (getenv("SNES_TRACE")) { const char *e = getenv("SNES_TRACE"); while (*e && ntrace < 16) { trace_pcs[ntrace++] = (uint32_t)strtoul(e, (char **)&e, 16); if (*e == ',') e++; else break; } snes_trace_on = 1; }
}
void snes_run_frame(void) { if (running && !failed) to_game(); }
const char *snes_error(void) { return failed ? err : NULL; }
uint64_t snes_frame_count(void) { return frames; }
const uint32_t *snes_framebuffer(void) { return sppu_fb; }
