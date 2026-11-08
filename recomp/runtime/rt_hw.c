/* rt_hw.c - what is left of the Wii hardware: nothing but the clock and the write-gather pipe.
 *
 * Track A (docs/NATIVE_ROADMAP.md) replaced every SDK device library with native code: GX's
 * registers (rt_gx.c), IOS/disc (rt_ios.c, rt_dvd.c), VI (rt_vi.c), SI (rt_si.c), EXI (rt_exi.c),
 * audio (rt_audio.c), the OS interrupt controller (rt_os.c) and the Wii Remotes' WUD layer
 * (rt_wiimote.c). No hardware register is read or written by the game any more, and no
 * interrupt is raised: completions are native events (rt_core.c rt_post_callback).
 *
 * What remains here:
 *   - the field clock (60 Hz NTSC fields): the VI retrace event, SI polling, per-field checks
 *     (deterministic mode), and the per-poll audio / remote updates;
 *   - the write-gather pipe (0xCC008000): the GX command stream the game writes with stores -
 *     the SDK's GXPosition/GXColor/... are inline stores compiled into every caller (rt_gx.c);
 *   - anything else is unexpected: logged (RT_MMIO_STRICT=1: fatal) and reads give 0.
 *   - RT_MMIO_INVENTORY=file lists every (guest function, register) that reaches this file. */
#include "rt.h"
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */

/* ------------------------------------------------------------------ the field clock */
static uint64_t vi_t0, vi_field;
#define VI_FIELD_NS 16683333ull                 /* NTSC field */
uint32_t hw_vi_line(void) {                     /* the line the "beam" is on in this field (1-based): VIGetCurrentLine */
    uint64_t t = (rt_emu_ns() - vi_t0) % VI_FIELD_NS;
    return 1 + (uint32_t)(t * 263 / VI_FIELD_NS);
}
void vi_field_start(void);                      /* rt_vi.c */
void audio_tick(void);                          /* rt_audio.c */
uint64_t audio_next_event_ns(uint64_t next);
uint64_t g_vi_fields;
void hw_update(void) {                          /* every poll point */
    uint64_t f = (rt_emu_ns() - vi_t0) / VI_FIELD_NS;
    if (f != vi_field) {
        vi_field = f; g_vi_fields++;
        if (g_det) det_field();                 /* (inputs for this field; checks) */
        plat_pump(); { extern void rt_funcstat_tick(void); rt_funcstat_tick(); }
        vi_field_start();                       /* the retrace (rt_vi.c) */
        si_tick();                              /* GameCube controller polling (rt_si.c) */
    }
    audio_tick();
    ios_update();                               /* (the remotes: rt_wiimote.c) */
}
/* when the next timed event is due (field, audio block, DSP mail): the idle loop sleeps until then */
uint64_t hw_next_event_ns(void) {
    uint64_t next = vi_t0 + (vi_field + 1) * VI_FIELD_NS;
    return audio_next_event_ns(next);
}
void hw_init(void) { vi_t0 = rt_emu_ns(); }

/* ------------------------------------------------------------------ registers: none */
/* RT_MMIO_INVENTORY=file (testing, track A of docs/NATIVE_ROADMAP.md): every distinct
   (guest function, hardware block, read/write) that touches a hardware register is written to
   the file when the game exits - the list of what still talks to the emulated hardware. The
   guest function is found from the host return address (the recompiled function's code). */
static int inv_on = -1; static FILE *inv_f;
static struct { const void *fn; uint32_t addr; } *inv_fns; static int inv_nfns;
static uint32_t inv_seen[4096]; static int inv_nseen;
static int inv_cmp(const void *a, const void *b) { const char *x = *(const char *const *)a, *y = *(const char *const *)b; return x < y ? -1 : x > y; }
static void inv_init(void) {
    const char *f = getenv("RT_MMIO_INVENTORY"); inv_on = f != NULL;
    if (!inv_on) return;
    inv_f = fopen(f, "w");
    inv_fns = malloc(sizeof *inv_fns * ppc_func_count);
    for (uint32_t i = 0; i < ppc_func_count; i++) { inv_fns[i].fn = (const void *)ppc_func_table[i].fn; inv_fns[i].addr = ppc_func_table[i].addr; }
    inv_nfns = (int)ppc_func_count;
    qsort(inv_fns, inv_nfns, sizeof *inv_fns, inv_cmp);
}
static void inv_note(uint32_t p, int write, const void *ra) {
    if (inv_on < 0) inv_init();
    if (!inv_on || !inv_f) return;
    int lo = 0, hi = inv_nfns;
    while (lo < hi) { int m = (lo + hi) / 2; if ((const char *)inv_fns[m].fn <= (const char *)ra) lo = m + 1; else hi = m; }
    uint32_t g = lo ? inv_fns[lo - 1].addr : 0;
    uint32_t blk = (p & 0x0FFFFC00u) | (uint32_t)write;
    uint32_t key = g ^ (blk * 2654435761u);
    for (int i = 0; i < inv_nseen; i++) if (inv_seen[i] == key) return;
    if (inv_nseen < 4096) inv_seen[inv_nseen++] = key;
    fprintf(inv_f, "%08X %s %s %08X\n", g, rt_func_name(g, NULL), write ? "W" : "R", p);
    fflush(inv_f);
}

static void unexpected(const char *what, uint32_t p, uint32_t v, int size) {
    static int strict = -1, n; if (strict < 0) strict = getenv("RT_MMIO_STRICT") != NULL;
    if (strict) rt_fatal("hardware register %s %08X (%d bytes) - track A: nothing should touch hardware", what, p, size);
    if (n++ < 20) rt_log("hw", "unexpected hardware register %s %08X (%d bytes) %08X (lr: see RT_MMIO_INVENTORY)", what, p, size, v);
}
uint32_t mmio_read(uint32_t p, int size) {
    if (inv_on) inv_note(p, 0, __builtin_return_address(0));
    if (g_det) g_vt_ns += 50;                   /* (a loop reading a counter with interrupts off still gets there) */
    unexpected("read", p, 0, size);
    return 0;
}
void mmio_write(uint32_t p, uint32_t v, int size) {
    if (inv_on) inv_note(p, 1, __builtin_return_address(0));
    if (p < 0x0D000000 && (p & 0xF000) == 0x8000) { gx_fifo_write(v, size); return; }   /* write-gather pipe */
    unexpected("write", p, v, size);
}
