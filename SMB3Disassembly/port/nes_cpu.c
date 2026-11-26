/* nes_cpu.c - the machine under the recompiled SMB3: memory map, MMC3, the 6502 call model,
 * interrupts and frame timing. The recompiled code (out/smb3_bNN.c) runs in a coroutine;
 * nes_run_frame() resumes it until the next vblank.
 *
 * Calls. JSR pushes its return address (the 6502 stack in RAM is the truth) and calls nes_call(),
 * which runs the target until an RTS/RTI comes back. Each call is a frame: the address it expects
 * and S before the push. An RTS returns to the frame whose address is the one pulled and whose S
 * is the S after the pull; any other RTS (an address pushed by hand) is a jump. A frame whose
 * return address was pulled without an RTS (DynJump, PLA PLA) is stale: the next jump in it
 * leaves its C frame and goes on in the caller's (NES_STALE), so the C stack stays as deep as the
 * 6502 one.
 *
 * Time. Every instruction adds its cycles. Events (nes_ev): each visible line at dot 260 (the
 * line is drawn, the MMC3 counter clocks), vblank (the coroutine yields: the frame is done; then
 * NMI), the pre-render line, the end of the frame. Interrupts are taken where the code checks
 * (backward branches, jumps, after calls) - between instructions, as on the NES. */
#include "nes.h"
#include "nes_gen.h"
#include "nes_ppu.h"
#include "nes_apu.h"
void rt_log(const char *tag, const char *fmt, ...);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

nes_cpu nes_R;
uint8_t nes_ram[0x800], nes_wram[0x2000];
uint8_t nes_map[4];
uint64_t nes_cyc, nes_ev;

static uint8_t *rom; static uint32_t prg_size, chr_size; static uint8_t *prg, *chr;
static char err[256];
static void (*log_fn)(const char *);
static void nlog(const char *fmt, ...) {
    char b[512]; va_list ap; va_start(ap, fmt); vsnprintf(b, sizeof b, fmt, ap); va_end(ap);
    if (log_fn) log_fn(b); else fprintf(stderr, "[nes] %s\n", b);
}
void nes_set_log(void (*fn)(const char *)) { log_fn = fn; }

/* ------------------------------------------------------------------ the coroutine */
static void game_main(void);
static int failed, running;
#ifdef _WIN32
#include <windows.h>
static LPVOID host_fiber, game_fiber;
static void WINAPI game_entry(LPVOID p) { (void)p; game_main(); }
static void coro_new(void) { if (game_fiber) DeleteFiber(game_fiber); game_fiber = CreateFiber(4 << 20, game_entry, NULL); }
static void to_game(void) { host_fiber = IsThreadAFiber() ? GetCurrentFiber() : ConvertThreadToFiber(NULL); SwitchToFiber(game_fiber); }
static void to_host(void) { SwitchToFiber(host_fiber); }
#else
#include <ucontext.h>
static ucontext_t host_ctx, game_ctx; static char *game_stack;
static void coro_new(void) {
    if (!game_stack) game_stack = malloc(4 << 20);
    getcontext(&game_ctx); game_ctx.uc_stack.ss_sp = game_stack; game_ctx.uc_stack.ss_size = 4 << 20; game_ctx.uc_link = NULL;
    makecontext(&game_ctx, game_main, 0);
}
static void to_game(void) { swapcontext(&host_ctx, &game_ctx); }
static void to_host(void) { swapcontext(&game_ctx, &host_ctx); }
#endif
static void fatal(const char *fmt, ...) {
    va_list ap; va_start(ap, fmt); vsnprintf(err, sizeof err, fmt, ap); va_end(ap);
    nlog("stopped: %s", err);
    failed = 1;
    for (;;) to_host();                                 /* never resumed */
}

/* ------------------------------------------------------------------ MMC3 */
static uint8_t mmc_sel, mmc_r[8], mmc_irq_latch, mmc_irq_count, mmc_irq_reload, mmc_irq_on, irq_line;
static void mmc_update(void) {
    int last = (int)(prg_size / 0x2000) - 1;
    uint8_t r6 = mmc_r[6] & last, r7 = mmc_r[7] & last;
    if (mmc_sel & 0x40) { nes_map[0] = (uint8_t)(last - 1); nes_map[2] = r6; }
    else { nes_map[0] = r6; nes_map[2] = (uint8_t)(last - 1); }
    nes_map[1] = r7; nes_map[3] = (uint8_t)last;
    int c[8], n = chr_size / 0x400 - 1;
    c[0] = mmc_r[0] & 0xFE; c[1] = mmc_r[0] | 1; c[2] = mmc_r[1] & 0xFE; c[3] = mmc_r[1] | 1;
    c[4] = mmc_r[2]; c[5] = mmc_r[3]; c[6] = mmc_r[4]; c[7] = mmc_r[5];
    for (int i = 0; i < 8; i++) {
        int slot = (mmc_sel & 0x80) ? (i ^ 4) : i;
        ppu_chr_slot[slot] = chr + (size_t)(c[i] & n) * 0x400;
    }
}
void nes_mmc3_clock(void) {                            /* (nes_ppu.c: once per rendered line) */
    if (mmc_irq_count == 0 || mmc_irq_reload) { mmc_irq_count = mmc_irq_latch; mmc_irq_reload = 0; }
    else mmc_irq_count--;
    if (mmc_irq_count == 0 && mmc_irq_on) irq_line = 1;
}
static void mmc_write(uint16_t a, uint8_t v) {
    switch (a & 0xE001) {
    case 0x8000: ppu_catch_up_now(); mmc_sel = v; mmc_update(); break;
    case 0x8001: ppu_catch_up_now(); mmc_r[mmc_sel & 7] = v; mmc_update(); break;
    case 0xA000: ppu_catch_up_now(); ppu_mirror_h = v & 1; break;
    case 0xA001: break;
    case 0xC000: mmc_irq_latch = v; break;
    case 0xC001: mmc_irq_count = 0; mmc_irq_reload = 1; break;
    case 0xE000: mmc_irq_on = 0; irq_line = 0; break;
    case 0xE001: mmc_irq_on = 1; break;
    }
}

/* ------------------------------------------------------------------ memory */
static uint8_t pad[2], pad_shift[2], strobe;
void nes_set_buttons(int p, uint8_t b) { if (p >= 0 && p < 2) pad[p] = b; }
uint8_t nes_rd(uint16_t a) {
    if (a >= 0x8000) return prg[(size_t)nes_map[(a >> 13) & 3] * 0x2000 + (a & 0x1FFF)];
    if (a < 0x2000) return nes_ram[a & 0x7FF];
    if (a < 0x4000) return ppu_read(a & 7);
    if (a == 0x4016 || a == 0x4017) {
        int p = a & 1; uint8_t r = pad_shift[p] & 1;
        if (!strobe) pad_shift[p] = (uint8_t)(pad_shift[p] >> 1 | 0x80);
        return (uint8_t)(0x40 | r);
    }
    if (a == 0x4015) return apu_status();
    if (a >= 0x6000) return nes_wram[a - 0x6000];
    return 0;
}
void nes_wr(uint16_t a, uint8_t v) {
    if (a >= 0x8000) { mmc_write(a, v); return; }
    if (a < 0x2000) { nes_ram[a & 0x7FF] = v; return; }
    if (a < 0x4000) { ppu_write(a & 7, v); return; }
    if (a == 0x4014) {                                    /* OAM DMA */
        uint8_t page[256]; for (int i = 0; i < 256; i++) page[i] = RD((uint16_t)(v << 8 | i));
        ppu_oam_dma(page); nes_cyc += 513; return;
    }
    if (a == 0x4016) { strobe = v & 1; if (strobe) { pad_shift[0] = pad[0]; pad_shift[1] = pad[1]; } return; }
    if (a >= 0x6000) { nes_wram[a - 0x6000] = v; return; }
    if (a >= 0x4000 && a <= 0x4017) apu_write(a, v);    /* the sound (nes_apu.c) */
}
uint8_t *nes_ram_ptr(void) { return nes_ram; }
uint8_t *nes_wram_ptr(void) { return nes_wram; }

/* ------------------------------------------------------------------ calls and returns */
#define MAXF 1024
static uint16_t f_pc[MAXF]; static uint16_t f_s[MAXF]; static int depth;
#define NES_STALE(pc) (0x30000 | (pc))
static const char *label_of(int bank, uint16_t pc) {
    static char b[96]; const nes_label *best = NULL;
    for (const nes_label *l = smb3_labels; l->name; l++) if (l->bank == bank && l->addr <= pc && (!best || l->addr > best->addr)) best = l;
    if (best) snprintf(b, sizeof b, "%s+%X", best->name, pc - best->addr); else snprintf(b, sizeof b, "?");
    return b;
}
static int exec(uint16_t pc, int frame) {
    for (;;) {
        int b = nes_map[(pc >> 13) & 3];
        if (pc < 0x8000) fatal("code at $%04X (RAM)", pc);
        if (!smb3_banks[b] || smb3_bank_base[b] != (pc & 0xE000)) fatal("no code at $%04X (bank %d in that window)", pc, b);
        int r = smb3_banks[b](pc);
        if ((r >> 16) == 1) return r;
        pc = (uint16_t)r;
        if (frame >= 0 && R.s >= f_s[frame]) return NES_STALE(pc);
    }
}
static int frame_push(uint16_t expect, uint16_t s) {
    if (depth >= MAXF) fatal("calls nested too deep");
    f_pc[depth] = expect; f_s[depth] = s; return depth++;
}
int nes_call(uint16_t target, uint16_t expect) {
    int k = frame_push(expect, (uint16_t)(R.s + 2));
    int r = exec(target, k);
    depth = k;
    return r == NES_RET(k) ? expect : r;
}
/* after an RTS/RTI (a plain address), or a result from a call that wasn't ours */
int nes_unwind(int v) {
    if (v >= 0x10000) return (v >> 16) == 3 ? NES_JUMP(v & 0xFFFF) : v;
    for (int k = depth - 1; k >= 0; k--) {
        if (f_s[k] < R.s) continue;                       /* stale: its address was pulled already */
        if (f_s[k] > R.s) break;
        if (f_pc[k] == v) return NES_RET(k);
    }
    return NES_JUMP(v);                                   /* an RTS to a pushed address: a jump */
}
static int interrupt(uint16_t vector, uint16_t pc, int brk) {
    int k = frame_push(pc, R.s);
    PUSH16(pc); PUSH((uint8_t)(GETP() | 0x20 | (brk ? 0x10 : 0))); R.i = 1;
    nes_cyc += 7;
    uint16_t to = (uint16_t)(nes_rd(vector) | nes_rd((uint16_t)(vector + 1)) << 8);
    int r = exec(to, k);
    depth = k;
    return r == NES_RET(k) ? -1 : r;                      /* -1: back where it was */
}
int nes_brk(uint16_t ret) { int r = interrupt(0xFFFE, ret, 1); return r == -1 ? NES_JUMP(ret) : nes_unwind(r); }
int nes_bad_pc(uint16_t pc, int bank) { fatal("bank %d: no instruction at $%04X (%s)", bank, pc, label_of(bank, pc)); return 0; }

/* ------------------------------------------------------------------ time */
#define DOTS_LINE 341
#define DOTS_FRAME (341 * 262)
static uint64_t frame_dot0;                               /* the frame's first dot (CPU cycles x 3) */
static int vbl_done, pre_done, nmi_pending;
static uint64_t frames;
static int frame_dot(void) { return (int)(nes_cyc * 3 - frame_dot0); }
void ppu_catch_up_now(void) { ppu_catch_up(frame_dot()); }
void nes_nmi_edge(void) { nmi_pending = 1; nes_ev = nes_cyc; }   /* (nes_ppu.c: NMI switched on during vblank) */
static void set_next_event(void) {
    int next = DOTS_FRAME;
    int l = ppu_next_line();
    if (l < 240) next = l * DOTS_LINE + 260;
    else if (!vbl_done) next = 241 * DOTS_LINE + 1;
    else if (!pre_done) next = 261 * DOTS_LINE + 1;
    nes_ev = (frame_dot0 + (uint64_t)next + 2) / 3;
    if (nmi_pending || (irq_line && !R.i)) nes_ev = nes_cyc;
}
/* events up to now; interrupts. -1: go on where it was; else a result to return */
static int events(uint16_t pc) {
    for (;;) {
        int dot = frame_dot();
        ppu_catch_up(dot);
        if (!vbl_done && dot >= 241 * DOTS_LINE + 1) {
            vbl_done = 1; ppu_vblank(); frames++; apu_catch_up();
            to_host();                                    /* the frame is done; the host comes back for the next */
            if (ppu_nmi_on()) nmi_pending = 1;
        }
        if (!pre_done && dot >= 261 * DOTS_LINE + 1) { pre_done = 1; ppu_prerender(); }
        if (dot >= DOTS_FRAME) { frame_dot0 += DOTS_FRAME; vbl_done = pre_done = 0; ppu_frame_start(); continue; }
        if (nmi_pending) { nmi_pending = 0; int d0 = frame_dot(); int r = interrupt(0xFFFA, pc, 0);
            {   static int lg = -1; if (lg < 0) lg = getenv("NES_IRQLOG") != NULL;
                if (lg) { int d1 = frame_dot(); rt_log("nes", "nmi: frame %llu from dot %d (line %d) to dot %d (line %d)%s", (unsigned long long)frames, d0, d0 / DOTS_LINE, d1, d1 / DOTS_LINE, r != -1 ? " (no RTI)" : ""); } }
            if (r != -1) return r; continue; }
        if (irq_line && !R.i) {
            {   static int lg = -1; if (lg < 0) lg = getenv("NES_IRQLOG") != NULL;
                if (lg) rt_log("nes", "irq: frame %llu line %d dot %d (latch %u) pc %04X", (unsigned long long)frames, ppu_next_line(), dot - ppu_next_line() * DOTS_LINE, mmc_irq_latch, pc); }
            int r = interrupt(0xFFFE, pc, 0); if (r != -1) return r; continue; }
        break;
    }
    set_next_event();
    return -1;
}
int nes_check(uint16_t pc, int win, int bank) {
    int r = events(pc);
    if (r != -1) return nes_unwind(r);
    if (bank >= 0 && nes_map[win] != bank) return NES_JUMP(pc);
    return 0;
}

/* ------------------------------------------------------------------ running */
static void game_main(void) {
    uint16_t pc = (uint16_t)(nes_rd(0xFFFC) | nes_rd(0xFFFD) << 8);
    nlog("reset at $%04X", pc);
    int r = exec(pc, -1);
    fatal("the game's top level returned (%X)", r);
}
int nes_load(const uint8_t *ines, uint32_t size) {
    if (size < 16 || memcmp(ines, "NES\x1A", 4)) return 0;
    prg_size = ines[4] * 0x4000u; chr_size = ines[5] * 0x2000u;
    if (size < 16 + prg_size + chr_size || (ines[6] >> 4 | (ines[7] & 0xF0)) != 4) return 0;
    free(rom); rom = malloc(size); memcpy(rom, ines, size);
    prg = rom + 16; chr = prg + prg_size;
    return 1;
}
void nes_reset(void) {
    memset(&nes_R, 0, sizeof nes_R); R.s = 0xFD; R.i = 1;
    memset(nes_ram, 0, sizeof nes_ram); memset(nes_wram, 0, sizeof nes_wram);
    memset(mmc_r, 0, sizeof mmc_r); mmc_sel = 0; mmc_r[6] = 0; mmc_r[7] = 1;
    mmc_irq_latch = mmc_irq_count = mmc_irq_reload = mmc_irq_on = irq_line = 0;
    ppu_reset(); mmc_update();
    nes_cyc = 0; apu_reset(); frame_dot0 = 0; vbl_done = pre_done = nmi_pending = 0; frames = 0; depth = 0;
    failed = 0; err[0] = 0; running = 1;
    set_next_event();
    coro_new();
}
void nes_run_frame(void) { if (running && !failed) to_game(); }
const char *nes_error(void) { return failed ? err : NULL; }
uint64_t nes_frame_count(void) { return frames; }
const uint32_t *nes_framebuffer(void) { return ppu_fb; }
