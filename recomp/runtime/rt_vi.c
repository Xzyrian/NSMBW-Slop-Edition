/* rt_vi.c - the video interface (VI), native (track A2 of docs/NATIVE_ROADMAP.md).
 *
 * On a Wii the VI library programs the video timing registers, takes a "retrace" interrupt every
 * field (60 Hz) and talks to the AV encoder over I2C. On the PC none of that hardware exists: the
 * picture is presented by the renderer when the game copies its frame (GXCopyDisp), so what the
 * game needs from VI is only its *software* side - the retrace count, the pre/post-retrace
 * callbacks (the game's frame pacing hangs on them), the thread queue VIWaitForRetrace sleeps on,
 * and the bookkeeping VIConfigure/VIFlush read back (HorVer, the current timing).
 *
 * Replaced here (decompiled from the USA rev 2 SDK code, minus the registers):
 *   VIInit (fn_801BC7A0)          - the library state for an NTSC 480i display, no registers
 *   the retrace interrupt handler  - vi_retrace(), a native event every field (rt_hw.c's field clock)
 *   VIGetCurrentLine / VIGetNextField / VIGetDTVStatus / __OSGetDTV (fn_801B00A0) - from the clock
 *   the AV encoder I2C write (fn_801BE860) and its microsecond delay (fn_801BE480) - no encoder
 * Everything else in the VI library (VIConfigure, VIFlush, VISetNextFrameBuffer, VISetBlack, the
 * __VISet* encoder settings) stays recompiled: it only updates memory now.
 *
 * Small-data (r13) variables of vi.c used here, by offset from r13 = 0x8042F680: */
#include "rt.h"
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */

#define SDA 0x8042F680u
enum {
    V_INITIALIZED   = -0x4ec0, V_RETRACE_COUNT = -0x4e14, V_RETRACE_QUEUE = -0x4e38,
    V_PRE_CB        = -0x4e40, V_POST_CB       = -0x4e44,
    V_CHANGED       = -0x4e18, V_CHANGE_MASK_HI = -0x4e78, V_CHANGE_MASK_LO = -0x4e74,
    V_TIMING_CHANGE = -0x4e80, V_CUR_TIMING    = -0x4e4c, V_CUR_TV = -0x4e50,
    V_NEXT_FB       = -0x4e54, V_CUR_FB        = -0x4e58,
    V_ENC_PENDING   = -0x4e1c, V_ENC_MASK      = -0x4e08,
    V_DISP_OFF_H    = -0x4e94, V_DISP_OFF_V    = -0x4e92,      /* (s16) */
    V_DIM_MODE      = -0x4e28, V_DIM_TIME      = -0x4eac, V_DIM_LEFT = -0x4eb0, V_DVD_STOP_TIME = -0x4ea8,
    V_DIM_COUNT     = -0x4ea4, V_DVD_COUNT     = -0x4ea0, V_DIM_FORCE = -0x4eb4, V_DIM_STATE = -0x4e9c,
    V_DIM_ENABLE    = -0x4e20, V_DVD_ENABLE    = -0x4e24,
    V_LAST_DTV      = -0x6110, V_LAST_TVCLASS  = -0x610c,
};
#define S(o) (SDA + (uint32_t)(int32_t)(o))
#define HV      0x8038FAE0u                     /* HorVer: the display / framebuffer geometry */
#define VI_REGS 0x8038F9F0u                     /* (the shadow register array; +0x7A = DCR copy) */
/* guest functions called */
#define F_OSRegisterVersion    0x801AB1C0u
#define F_SCGetDisplayOffsetH  0x801DD230u
#define F_getTiming            0x801BC480u
#define F_OSInitThreadQueue    0x801B4B20u
#define F_OSRegisterShutdown   0x801B32D0u
#define F_SCGetScreenSaverMode 0x801DD3F0u
#define F_EncoderInit          0x801C0020u
#define F_OSWakeupThread       0x801B5D80u
#define F_SetSamplingRate      0x801BB920u     /* SISetSamplingRate(the current rate): SI timing follows VI */
#define F_SetDTV               0x801BEDA0u
#define F_SetFilter4EURGB60    0x801BEE40u
#define VI_RETRACE_FN          0x80001F20u     /* guest address of vi_retrace (rt_register_native) */

static uint32_t gcall(ppc_context *ctx, uint32_t fn, uint32_t a0, uint32_t a1) {
    uint32_t lr = ctx->lr;
    ctx->r[3] = a0; ctx->r[4] = a1;
    ppc_call_indirect(ctx, g_base, fn);
    ctx->lr = lr;
    return ctx->r[3];
}
/* the Wii's "display class" of a TV format (vi.c: NTSC/MPAL/EURGB60 -> 0, PAL -> 1, DEBUG(_PAL) -> as is) */
static uint32_t tv_class(uint32_t tv) {
    static const int8_t c[9] = {0, 1, -1, 0, 1, -1, 0, 0, 0};
    return tv > 8 ? tv : c[tv] < 0 ? tv : (uint32_t)c[tv];
}

/* ------------------------------------------------------------------ VIInit */
#define DCR_AT_INIT 1u        /* display control after the (skipped) __VIInit(NTSC): enabled, interlaced, NTSC */
static void vi_init(ppc_context *ctx);
void orig_fn_801BC7A0(ppc_context *ctx, uint8_t *base);
void hle_fn_801BC7A0(ppc_context *ctx, uint8_t *base) {
    if (getenv("RT_VI_VERIFY") && !R32(S(V_INITIALIZED))) {   /* testing: native vs the SDK's code, memory compared */
        size_t n = 0x01800000; uint8_t *a = malloc(n), *b = malloc(n);
        ppc_context c0 = *ctx;
        memcpy(a, base, n); vi_init(ctx); memcpy(b, base, n);
        memcpy(base, a, n); *ctx = c0; orig_fn_801BC7A0(ctx, base);
        int diffs = 0;
        for (size_t i = 0; i < n; i++) if (b[i] != base[i] && diffs++ < 40)
            rt_log("vi", "VIInit verify: %08X native %02X sdk %02X", (uint32_t)(0x80000000u + i), b[i], base[i]);
        rt_log("vi", "VIInit verify: %d bytes differ", diffs);
        free(a); free(b); return;
    }
    vi_init(ctx);
}
static void vi_init(ppc_context *ctx) {
    if (R32(S(V_INITIALIZED))) return;
    gcall(ctx, F_OSRegisterVersion, R32(S(-0x6118)), 0);
    W32(S(V_INITIALIZED), 1);
    W32(0x800000CC, 0);                                   /* (__VIInit: the video mode the "IPL" left: NTSC) */
    W32(S(V_RETRACE_COUNT), 0);
    W32(S(-0x4e84), 0); W32(S(-0x4e88), 0); W32(S(V_CHANGE_MASK_LO), 0); W32(S(V_CHANGE_MASK_HI), 0);
    W32(S(-0x4e90), 0); W32(S(V_TIMING_CHANGE), 0); W32(S(V_CHANGED), 0); W32(S(V_ENC_PENDING), 0);
    W16(S(V_DISP_OFF_H), (uint16_t)(int16_t)(int8_t)gcall(ctx, F_SCGetDisplayOffsetH, 0, 0));
    W16(S(V_DISP_OFF_V), 0);

    uint32_t dcr = DCR_AT_INIT, mode = R32(0x800000CC);
    uint32_t non_inter = (dcr >> 2) & 1, tv = (dcr >> 8) & 3;
    W32(HV + 0x24, non_inter);
    W32(HV + 0x28, tv);
    if (mode == 5 || (mode == 1 && tv == 0)) W32(HV + 0x28, tv = 5);
    uint32_t T = gcall(ctx, F_getTiming, (tv == 3 ? 0 : tv) * 4 + non_inter, 0);
    uint32_t nhl = R16(T + 2);                             /* (half-lines per field) */
    W16(VI_REGS + 0x7A, (uint16_t)dcr);
    W32(HV + 0x54, T); W32(S(V_CUR_TIMING), T); W32(S(V_CUR_TV), R32(HV + 0x28));
    W16(HV + 0x04, 640);                                   /* DispSizeX */
    W16(HV + 0x06, (uint16_t)(nhl * 2));                   /* DispSizeY */
    W16(HV + 0x00, (720 - 640) / 2);                       /* DispPosX */
    W16(HV + 0x02, 0);                                     /* DispPosY */
    /* AdjustedDispPos/Size: the position moved by the console's display offset, clipped to the screen */
    int32_t off_v = (int16_t)R16(S(V_DISP_OFF_V));
    int32_t x = (720 - 640) / 2 + (int16_t)R16(S(V_DISP_OFF_H));
    W16(HV + 0x08, (uint16_t)(x > 80 ? 80 : x < 0 ? 0 : x));
    int32_t fieldf = R32(HV + 0x20) == 0 ? 2 : 1;          /* (FBMode: field or frame) */
    int32_t pos_y = (int16_t)R16(HV + 0x02), odd = pos_y & 1;
    int32_t y = pos_y + off_v;
    W16(HV + 0x0A, (uint16_t)(y > odd ? y : odd));
    int32_t size_y = (int16_t)R16(HV + 0x06);
    int32_t top = pos_y + off_v - odd;                     /* (<0: cut at the top) */
    int32_t bottom = size_y + pos_y + off_v - (int32_t)(nhl * 2 - odd);   /* (>0: cut at the bottom) */
    int32_t cut_top = top < 0 ? top : 0, cut_bot = bottom > 0 ? bottom : 0;
    W16(HV + 0x0C, (uint16_t)(size_y + cut_top - cut_bot));
    W16(HV + 0x0E, (uint16_t)((int32_t)R16(HV + 0x18) - cut_top / fieldf));
    W16(HV + 0x10, (uint16_t)((int32_t)R16(HV + 0x1C) + cut_top / fieldf - cut_bot / fieldf));
    W16(HV + 0x12, 640);
    W16(HV + 0x14, (uint16_t)(nhl * 2));
    W16(HV + 0x16, 0); W16(HV + 0x18, 0); W16(HV + 0x1A, 640); W16(HV + 0x1C, (uint16_t)(nhl * 2));
    W32(HV + 0x20, 0);
    W8(HV + 0x2C, 40); W8(HV + 0x2D, 40); W8(HV + 0x2E, 40);
    W8(HV + 0x3C, 0); W32(HV + 0x40, 1); W32(HV + 0x44, 0);
    gcall(ctx, F_OSInitThreadQueue, S(V_RETRACE_QUEUE), 0);
    W32(S(V_PRE_CB), 0); W32(S(V_POST_CB), 0);
    /* (no retrace interrupt handler: vi_retrace runs from the field clock) */
    gcall(ctx, F_OSRegisterShutdown, 0x80340340u, 0);
    /* screen dimming / disc motor timers (kept as data; nothing on the PC acts on them) */
    if (tv_class(R32(S(V_CUR_TV))) == 1) { W32(S(V_DIM_LEFT), 15000); W32(S(V_DIM_TIME), 15000); W32(S(V_DVD_STOP_TIME), 90000); }
    else { W32(S(V_DIM_LEFT), 18000); W32(S(V_DIM_TIME), 18000); W32(S(V_DVD_STOP_TIME), 108000); }
    W32(S(V_DIM_COUNT), 0); W32(S(V_DVD_COUNT), 0); W32(S(V_DIM_MODE), 0); W32(S(V_DIM_FORCE), 1); W32(S(V_DIM_STATE), 0);
    W32(S(V_DIM_ENABLE), (gcall(ctx, F_SCGetScreenSaverMode, 0, 0) & 0xFF) ? 1 : 0);
    uint32_t enc = R32(S(V_DVD_ENABLE)); W32(S(V_DVD_ENABLE), 0);
    gcall(ctx, F_EncoderInit, enc, 0);                     /* (encoder settings: state only, the I2C writes are no-ops) */
    LOG("vi", "VIInit (native): timing %08X, %u half-lines", T, nhl);
}

/* ------------------------------------------------------------------ the retrace (every field) */
uint64_t g_vi_retraces RT_LOCAL;
static void vi_retrace(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t n = R32(S(V_RETRACE_COUNT)) + 1;
    W32(S(V_RETRACE_COUNT), n);
    g_vi_retraces++;
    uint32_t cb = R32(S(V_PRE_CB));
    if (cb) gcall(ctx, cb, n, 0);
    if (R32(S(V_CHANGED))) {                               /* VIFlush'ed settings take effect */
        W32(S(V_CHANGE_MASK_HI), 0); W32(S(V_CHANGE_MASK_LO), 0);       /* (the registers they'd go to: none) */
        W32(S(V_TIMING_CHANGE), 0);
        W32(S(V_CUR_TIMING), R32(HV + 0x54)); W32(S(V_CUR_TV), R32(HV + 0x28));
        W32(S(V_CUR_FB), R32(S(V_NEXT_FB)));
        W32(S(V_CHANGED), 0);
        gcall(ctx, F_SetSamplingRate, 0, 0);
    }
    if (R32(S(V_LAST_DTV)) != 0) { gcall(ctx, F_SetDTV, 0, 0); W32(S(V_LAST_DTV), 0); }   /* (no digital TV cable) */
    uint32_t tc = tv_class(R32(S(V_CUR_TV)));
    if (tc != R32(S(V_LAST_TVCLASS))) {
        gcall(ctx, F_SetFilter4EURGB60, tc == 5, 0);
        uint32_t m = R32(S(V_DIM_MODE));
        if (tc == 1) { W32(S(V_DIM_TIME), m == 1 ? 30000 : m == 2 ? 0xAFC8 : 15000); W32(S(V_DVD_STOP_TIME), 90000); }
        else         { W32(S(V_DIM_TIME), m == 1 ? 0x8CA0 : m == 2 ? 0xD2F0 : 18000); W32(S(V_DVD_STOP_TIME), 108000); }
        W32(S(V_DIM_COUNT), 0); W32(S(V_DVD_COUNT), 0);
    }
    W32(S(V_LAST_TVCLASS), tc);
    if (R32(S(V_ENC_PENDING))) { W32(S(V_ENC_MASK), 0); W32(S(V_ENC_PENDING), 0); }   /* (encoder settings: no encoder) */
    cb = R32(S(V_POST_CB));
    if (cb) gcall(ctx, cb, R32(S(V_RETRACE_COUNT)), 0);
    gcall(ctx, F_OSWakeupThread, S(V_RETRACE_QUEUE), 0);
    /* (the Wii's dimming / disc-motor-off after minutes without input: not on a PC) */
}
/* rt_hw.c's field clock: a new field began */
void vi_field_start(void) {
    static int reg; if (!reg) { reg = 1; rt_register_native(VI_RETRACE_FN, vi_retrace); }
    if (R32(S(V_INITIALIZED))) rt_post_callback(VI_RETRACE_FN, 0, 0);
}

/* ------------------------------------------------------------------ position queries */
uint32_t hw_vi_line(void);                                /* rt_hw.c: the line the "beam" is on in this field (1-based) */
static uint32_t vi_halfline(void) {                       /* (vct - 1) * 2 + (hct - 1) / hlw, hct = 1 */
    return (hw_vi_line() - 1) * 2;
}
void hle_VIGetCurrentLine(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t T = R32(S(V_CUR_TIMING)), hl = vi_halfline(), nhl = R16(T + 0x18);
    if (hl >= nhl) hl -= nhl;
    ctx->r[3] = hl >> 1;
}
void hle_VIGetNextField(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t T = R32(S(V_CUR_TIMING)), hl = vi_halfline(), nhl = R16(T + 0x18);
    uint32_t field = nhl > hl ? 0 : 1;                    /* (0: in the first field) */
    ctx->r[3] = field ^ (R16(HV + 0x0A) & 1);
}
void hle_VIGetDTVStatus(ppc_context *ctx, uint8_t *base) { (void)base; ctx->r[3] = 0; }   /* (no component / digital cable) */
/* __OSGetDTV-like (fn_801B00A0): caches the "progressive capable" bit, 0 here */
void hle_fn_801B00A0(ppc_context *ctx, uint8_t *base) {
    (void)base;
    if (R16(S(-0x6158)) == 0xFFFF) W16(S(-0x6158), 0);
    W32(S(-0x4fc8), 0x801B05A0u);
    ctx->r[3] = R16(S(-0x6158));
}

/* ------------------------------------------------------------------ the AV encoder */
void hle_fn_801BE860(ppc_context *ctx, uint8_t *base) { (void)base; ctx->r[3] = 1; }   /* I2C write: done */
void hle_fn_801BE480(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }       /* (wait n microseconds for the encoder) */
