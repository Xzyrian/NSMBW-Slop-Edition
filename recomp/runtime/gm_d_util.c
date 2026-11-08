/* gm_d_util.c - Util::FrameCounter_c, a float frame counter (one-time, looping or oscillating
 * between a start and an end frame): ctor / dtor, init, both play, calc. Track B (gm.h,
 * docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_util_frame_counter.cpp) and checked
 * against the recompiled USA rev 2 code (0x800E8130-0x800E82FC). All written but off: no test
 * calls a FrameCounter_c (plain GM_HLE, not in hle_funcs.txt). Register-exact (R(n)); calc's
 * float compares go through cror as the PowerPC code's do.
 *
 * FrameCounter_c: +0 frame, +4 start, +8 end, +12 rate, +16 finished, +20 type (0 one time,
 * 1 loop, 2 oscillating). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d
#define LF(a) ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }

#define K_ZERO    25392                  /* (r2 - 25392: 0.0f) */
#define K_NEG_ONE 25388                  /* (r2 - 25388: -1.0f) */

static void fc_ctor(GM_CTX) {
    FB(0, LF(R(2) - K_ZERO));
    R(4) = 0; R(0) = 1;
    SF(R(3), F(0)); SF(R(3) + 4, F(0)); SF(R(3) + 8, F(0)); SF(R(3) + 12, F(0));
    gm_set_u32(R(3) + 20, 0);
    gm_set_u8(R(3) + 16, 1);
}
static void fc_dtor(GM_CTX) {
    GM_FN(0x800E8160); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(3);
    if (c != 0 && cmps(ctx, (int32_t)R(4), 0) > 0) GM_CALLV(0x800E8188u, 0x802B9280u, 0);
    R(3) = R(31);
    R(0) = lr;
}
/* play(rate, type): from the start */
static void fc_play(GM_CTX) {
    FB(0, LF(R(3) + 4));
    SF(R(3) + 12, F(1));
    gm_set_u32(R(3) + 20, R(4));
    SF(R(3), F(0));
}
/* the end reached (r4 = type; f2 the end, f1 the frame) */
static void fc_wrap(GM_CTX, uint32_t edge_off, uint32_t other_off, int at_end) {
    R(4) = gm_u32(R(3) + 20);
    R(0) = 1;
    gm_set_u8(R(3) + 16, 1);
    if (cmps(ctx, (int32_t)R(4), 0) == 0) { SF(R(3), F(2)); return; }
    if (cmps(ctx, (int32_t)R(4), 1) == 0) {
        FB(1, frsp((at_end ? F(1) : F(0)) - F(2)));
        FB(0, LF(R(3) + other_off));
        FB(0, frsp(F(0) + F(1)));
        SF(R(3), F(0));
        return;
    }
    if (cmps(ctx, (int32_t)R(4), 2) == 0) {
        FB(1, frsp((at_end ? F(1) : F(0)) - F(2)));
        FB(0, LF(R(2) - K_NEG_ONE));
        FB(0, frsp(F(3) * F(0)));
        FB(1, frsp(F(2) - F(1)));
        SF(R(3) + 12, F(0));
        SF(R(3), F(1));
    }
    (void)edge_off;
}
/* calc(): advance; at the end (rate >= 0) or the start (rate <= 0) finish by the type */
static void fc_calc(GM_CTX) {
    FB(1, LF(R(3)));
    R(0) = 0;
    FB(3, LF(R(3) + 12));
    FB(0, LF(R(2) - K_ZERO));
    FB(1, frsp(F(1) + F(3)));
    gm_set_u8(R(3) + 16, 0);
    cr_fcmp(ctx, 0, F(3), F(0));
    SF(R(3), F(1));
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));                    /* rate >= 0 */
    if (CR_BIT(ctx, 2)) {
        FB(2, LF(R(3) + 8));
        cr_fcmp(ctx, 0, F(1), F(2));
        CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));                /* frame >= end */
        if (CR_BIT(ctx, 2)) fc_wrap(GM_PASS, 8, 4, 1);
    }
    FB(3, LF(R(3) + 12));
    FB(0, LF(R(2) - K_ZERO));
    cr_fcmp(ctx, 0, F(3), F(0));
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));                    /* rate <= 0 */
    if (!CR_BIT(ctx, 2)) return;
    FB(0, LF(R(3)));
    FB(2, LF(R(3) + 4));
    cr_fcmp(ctx, 0, F(0), F(2));
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));                    /* frame <= start */
    if (!CR_BIT(ctx, 2)) return;
    fc_wrap(GM_PASS, 4, 8, 0);
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_UTIL_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_UTIL_COUNT)  /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
GM_HLE(fn_800E8130) { fc_ctor(GM_PASS); }                                           /* Util::FrameCounter_c::FrameCounter_c */
GM_HLE(fn_800E8160) { fc_dtor(GM_PASS); }                                           /* ::~FrameCounter_c */
GM_HLE(fn_800E81A0) { SF(R(3) + 4, F(1)); SF(R(3) + 8, F(2)); SF(R(3), F(1)); }     /* ::init(start, end) */
GM_HLE(fn_800E81B0) { SF(R(3) + 4, F(2)); SF(R(3) + 8, F(3)); fc_play(GM_PASS); }   /* ::play(rate, type, start, end) */
GM_HLE(fn_800E81C0) { fc_play(GM_PASS); }                                           /* ::play(rate, type) */
GM_HLE(fn_800E81E0) { fc_calc(GM_PASS); }                                           /* ::calc */
