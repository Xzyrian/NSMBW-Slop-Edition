/* gm_s_lib.c - sLib's small helpers: the smoothing / chasing functions every actor uses
 * (sLib::addCalc, addCalcAngle, chase for s16 / int / long / float, chaseAngle,
 * chaseAngleByRotDir), the phase list (sPhase_c: setup, callMethod) and cCounter_c::clear.
 * Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/sLib/s_lib.cpp, s_Phase.cpp, cLib/c_counter.cpp)
 * and checked against the recompiled USA rev 2 code (0x8015F140-0x8015F6C4, 0x8015FE40). These are
 * leaves called from everywhere, so they leave every register as the PowerPC code does - CR0 / CR1
 * of the last compare, r0 / r5 / r7-r9 and the float temporaries (RT_GM_VERIFY_REGS=1 checks it):
 * a later variadic callee or mfcr can spill those into the stack. Floats: lfs and the single
 * arithmetic set both paired-single halves, fmr / fneg only ps0 (fb / f0 below).
 *
 * Not here (still recompiled): the 4-byte wrappers that only sign-extend or branch (chase(int)'s
 * 0x8015F3B0 ...), sCrc::calcCRC32 (a branch to OSCalcCRC32), the vprintf pointer helpers. */
#include "gm.h"
#include "gm_nv.h"

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define ZERO_F   21640                   /* (r2 - 21640: 0.0f) */
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }   /* lfs / fadds ...: both halves */
static inline double f0_(ppc_context *ctx, int n, double v) { ctx->f[n].d = v; return v; }             /* fmr / fneg: ps0 only */
#define FB(n, v) fb(ctx, (n), (v))
#define F0(n, v) f0_(ctx, (n), (v))
#define S16X(v) ((uint32_t)(int32_t)(int16_t)(v))                                                        /* extsh */
/* a signed / unsigned compare into CR field n, returning the result (-1, 0, 1) */
static inline int cmps(ppc_context *ctx, int n, int32_t a, int32_t b) { cr_cmp_s(ctx, n, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, int n, uint32_t a, uint32_t b) { cr_cmp_u(ctx, n, a, b); return (a > b) - (a < b); }

/* ================================================================== sLib::addCalc
   *value moves by smoothing * (target - *value), clamped to [minStep, maxStep]; returns |target - *value| */
static double s_addCalc(GM_CTX, gptr value, double target, double smooth, double max_step, double min_step) {
    double v = FB(5, LF(value));
    if (v != target) {
        double dist = FB(0, frsp(target - v));
        double step = FB(6, frsp(smooth * dist));
        double neg_min = 0;
        int big = step > min_step || step == min_step;
        if (!big) { neg_min = F0(2, -min_step); big = step < neg_min || step == neg_min; }
        if (big) {                                          /* a full step, clamped to +-maxStep */
            if (step > max_step) step = F0(6, ctx->f[3].d);
            double neg_max = F0(0, -max_step);
            if (step < neg_max) step = F0(6, neg_max);
            SF(value, FB(0, frsp(LF(value) + step)));
        } else if (step > FB(0, R2F(ZERO_F))) {             /* a small step up: minStep, not past the target */
            if (step < min_step) {
                double n = FB(0, frsp(v + min_step));
                SF(value, n);
                if (n > target) SF(value, target);
            }
        } else if (step > neg_min) {                        /* a small step down */
            double n = FB(0, frsp(v + neg_min));
            SF(value, n);
            if (n < target) SF(value, target);
        }
    }
    double now = FB(2, LF(value));
    double zero = FB(0, R2F(ZERO_F));
    double d = FB(1, frsp(target - now));
    cr_fcmp(ctx, 0, d, zero);
    if (!(d > zero)) F0(1, -d);
    return ctx->f[1].d;
}

/* ================================================================== sLib::addCalcAngle (5 arguments)
   (arguments already sign-extended: 0x8015F200 extends them first). Returns target - *value. */
static uint32_t s_addCalcAngle(GM_CTX, gptr value, int32_t target, int32_t smooth, int32_t max_step, int32_t min_step) {
    int32_t v = (int16_t)gm_s16(value);
    ctx->r[8] = (uint32_t)v;
    int c = cmps(ctx, 0, v, target);
    ctx->r[0] = (uint32_t)target - (uint32_t)v;
    int32_t dist = (int16_t)ctx->r[0];
    ctx->r[9] = (uint32_t)dist;
    if (c != 0) {
        ctx->r[0] = divw(dist, smooth);
        int32_t step = (int16_t)ctx->r[0];
        ctx->r[5] = (uint32_t)step;
        int big = cmps(ctx, 0, step, min_step) > 0;
        if (!big) { ctx->r[0] = (uint32_t)-min_step; big = cmps(ctx, 0, step, (int32_t)ctx->r[0]) < 0; }
        if (big) {                                          /* a full step, clamped to +-maxStep */
            if (cmps(ctx, 0, step, max_step) > 0) step = max_step;
            else { ctx->r[0] = (uint32_t)-max_step; if (cmps(ctx, 0, step, (int32_t)ctx->r[0]) < 0) step = (int16_t)ctx->r[0]; }
            ctx->r[5] = (uint32_t)step;
            ctx->r[0] = (uint32_t)(int16_t)gm_s16(value) + (uint32_t)step;
            gm_set_u16(value, (uint16_t)ctx->r[0]);
        } else if (cmps(ctx, 0, dist, 0) >= 0) {            /* minStep up, not past the target */
            ctx->r[0] = (uint32_t)v + (uint32_t)min_step;
            gm_set_u16(value, (uint16_t)ctx->r[0]);
            ctx->r[0] = S16X((uint32_t)target - S16X(ctx->r[0]));
            if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) <= 0) gm_set_u16(value, (uint16_t)target);
        } else {                                            /* minStep down */
            ctx->r[0] = (uint32_t)v - (uint32_t)min_step;
            gm_set_u16(value, (uint16_t)ctx->r[0]);
            ctx->r[0] = S16X((uint32_t)target - S16X(ctx->r[0]));
            if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) >= 0) gm_set_u16(value, (uint16_t)target);
        }
    }
    ctx->r[0] = (uint32_t)target - S16X(gm_u16(value));
    return S16X(ctx->r[0]);
}

/* ================================================================== sLib::addCalcAngle (4 arguments) */
static void s_addCalcAngle4(GM_CTX, gptr value, int32_t target, int32_t smooth, int32_t max_step) {
    int32_t v = (int16_t)gm_s16(value);
    ctx->r[7] = (uint32_t)v;
    ctx->r[0] = divw((int16_t)((uint32_t)target - (uint32_t)v), smooth);
    int32_t step = (int16_t)ctx->r[0];
    ctx->r[4] = (uint32_t)step;
    if (cmps(ctx, 0, step, max_step) > 0) ctx->r[0] = (uint32_t)v + (uint32_t)max_step;
    else {
        ctx->r[0] = (uint32_t)-max_step;
        if (cmps(ctx, 0, step, (int32_t)ctx->r[0]) < 0) ctx->r[0] = (uint32_t)v - (uint32_t)max_step;
        else ctx->r[0] = (uint32_t)v + (uint32_t)step;
    }
    gm_set_u16(value, (uint16_t)ctx->r[0]);
}

/* ================================================================== sLib::chase
   *value steps towards target; TRUE once it is there. The s16 version (sign-extended arguments,
   0x8015F340 extends them) and the int / long ones (the same code) compare in CR1 first. */
static uint32_t s_chase_s16(GM_CTX, gptr value, int32_t target, int32_t step) {
    int32_t v = (int16_t)gm_s16(value);
    ctx->r[0] = (uint32_t)v;
    int c = cmps(ctx, 1, v, target);
    if (c == 0) return 1;
    if (cmps(ctx, 0, step, 0) == 0) return 0;
    if (c > 0) { ctx->r[0] = (uint32_t)-step; step = (int16_t)ctx->r[0]; ctx->r[5] = (uint32_t)step; }
    ctx->r[0] = (uint32_t)(int16_t)gm_s16(value) + (uint32_t)step;
    gm_set_u16(value, (uint16_t)ctx->r[0]);
    ctx->r[0] = (uint32_t)step * (S16X(ctx->r[0]) - (uint32_t)target);
    if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) < 0) return 0;
    gm_set_u16(value, (uint16_t)target);
    return 1;
}
static uint32_t s_chase_s32(GM_CTX, gptr value, int32_t target, int32_t step) {
    int32_t v = gm_s32(value);
    ctx->r[0] = (uint32_t)v;
    int c = cmps(ctx, 1, v, target);
    if (c == 0) return 1;
    if (cmps(ctx, 0, step, 0) == 0) return 0;
    if (c > 0) { step = -step; ctx->r[5] = (uint32_t)step; }
    ctx->r[0] = gm_u32(value) + (uint32_t)step;
    gm_set_u32(value, ctx->r[0]);
    ctx->r[0] = (uint32_t)step * (ctx->r[0] - (uint32_t)target);
    if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) < 0) return 0;
    gm_set_u32(value, (uint32_t)target);
    return 1;
}
static uint32_t s_chase_f(GM_CTX, gptr value, double target, double step) {
    double v = FB(3, LF(value));
    cr_fcmp(ctx, 0, v, target);
    if (v == target) return 1;
    double zero = FB(0, R2F(ZERO_F));
    cr_fcmp(ctx, 0, step, zero);
    if (step == zero) return 0;
    if (v > target) step = F0(2, -step);
    v = FB(3, LF(value));
    zero = FB(0, R2F(ZERO_F));
    v = FB(3, frsp(v + step));
    SF(value, v);
    double over = FB(2, frsp(step * FB(3, frsp(v - target))));
    cr_fcmp(ctx, 0, over, zero);
    CR_SETBIT(ctx, 2, CR_BIT(ctx, 1) | CR_BIT(ctx, 2));      /* (cror: >= in the eq bit) */
    if (!CR_BIT(ctx, 2)) return 0;
    SF(value, target);
    return 1;
}

/* ================================================================== sLib::chaseAngle (s16, the shorter way not taken) */
static uint32_t s_chaseAngle(GM_CTX, gptr value, int32_t target, int32_t step) {
    int32_t v = (int16_t)gm_s16(value);
    ctx->r[0] = (uint32_t)v;
    if (cmps(ctx, 0, v, target) == 0) return 1;
    if (cmps(ctx, 0, step, 0) == 0) return 0;
    ctx->r[0] = S16X((uint32_t)v - (uint32_t)target);
    if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) > 0) { ctx->r[0] = (uint32_t)-step; step = (int16_t)ctx->r[0]; ctx->r[5] = (uint32_t)step; }
    ctx->r[0] = (uint32_t)(int16_t)gm_s16(value) + (uint32_t)step;
    gm_set_u16(value, (uint16_t)ctx->r[0]);
    ctx->r[0] = (uint32_t)step * S16X(S16X(ctx->r[0]) - (uint32_t)target);
    if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) < 0) return 0;
    gm_set_u16(value, (uint16_t)target);
    return 1;
}

/* ================================================================== sLib::chaseAngleByRotDir
   steps by `step` (its sign is the direction); the overshoot check only when that direction
   points at the target */
static uint32_t s_chaseAngleByRotDir(GM_CTX, gptr value, int32_t target, int32_t step) {
    int32_t v = (int16_t)gm_s16(value);
    ctx->r[7] = (uint32_t)v;
    if (cmps(ctx, 0, v, target) == 0) return 1;
    int c = cmps(ctx, 0, step, 0);
    if (c == 0) return 0;
    uint32_t inc = (uint32_t)step;
    ctx->r[8] = inc;
    if (c < 0) {                                            /* |step| (0x8000: 0x7FFF - never on a sign-extended step) */
        ctx->r[0] = (uint32_t)step;
        ctx->r[6] = 32767;
        if (cmpu(ctx, 0, ctx->r[0], 0x8000u) != 0) { ctx->r[0] = (uint32_t)-step; ctx->r[6] = S16X(ctx->r[0]); }
        step = (int32_t)ctx->r[6];
        ctx->r[5] = (uint32_t)step;
    }
    ctx->r[0] = S16X((uint32_t)v - (uint32_t)target);
    if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) > 0) { ctx->r[0] = (uint32_t)-step; step = (int16_t)ctx->r[0]; ctx->r[5] = (uint32_t)step; }
    ctx->r[0] = S16X((uint32_t)step);
    ctx->r[6] = S16X(inc);
    ctx->r[0] = ctx->r[6] * ctx->r[0];
    int dir = cmps(ctx, 0, (int32_t)ctx->r[0], 0);
    ctx->r[5] = (uint32_t)(int16_t)gm_s16(value) + inc;
    gm_set_u16(value, (uint16_t)ctx->r[5]);
    if (dir <= 0) return 0;
    ctx->r[0] = ctx->r[6] * S16X(S16X(ctx->r[5]) - (uint32_t)target);
    if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) < 0) return 0;
    gm_set_u16(value, (uint16_t)target);
    return 1;
}

/* ================================================================== sPhase_c
   +0 the method list, +4 its length (u16), +6 the current method (u16) */
#define PH_LIST 0
#define PH_LEN  4
#define PH_CUR  6
enum { PH_OK = 1, PH_DONE = 2 };
static void sPhase_setup(GM_CTX, gptr ph, gptr list, uint32_t n) {
    ctx->r[0] = 0;
    gm_set_ptr(ph + PH_LIST, list); gm_set_u16(ph + PH_LEN, (uint16_t)n); gm_set_u16(ph + PH_CUR, 0);
}
/* callMethod(owner): runs the methods from the current one while they return OK */
static uint32_t sPhase_callMethod(GM_CTX, gptr ph, gptr owner) {
    GM_FN(0x8015F620); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, owner); NV_R(30, ph);
    ctx->r[5] = gm_u16(ph + PH_CUR); ctx->r[0] = gm_u16(ph + PH_LEN);
    uint32_t res = PH_DONE;
    if (cmpu(ctx, 0, ctx->r[5], ctx->r[0]) < 0) {
        res = PH_OK;
        while (cmps(ctx, 0, (int32_t)res, PH_OK) == 0) {
            GM_LOOP();
            ctx->r[0] = (uint32_t)gm_u16(ph + PH_CUR) << 2;
            ctx->r[4] = gm_ptr(ph + PH_LIST);
            ctx->r[12] = ctx->ctr = gm_ptr(ctx->r[4] + ctx->r[0]);
            res = GM_CALLV(0x8015F678u, ctx->r[12], 1, owner);
            if (cmps(ctx, 0, (int32_t)res, PH_OK) != 0) continue;       /* (checked again: the loop ends) */
            ctx->r[4] = gm_u16(ph + PH_CUR) + 1u;
            gm_set_u16(ph + PH_CUR, (uint16_t)ctx->r[4]);
            ctx->r[0] = gm_u16(ph + PH_LEN);
            ctx->r[4] &= 0xFFFFu;
            if (cmpu(ctx, 0, ctx->r[4], ctx->r[0]) >= 0) { res = PH_DONE; break; }
        }
    }
    ctx->r[0] = lr;
    return res;
}

/* ================================================================== cCounter_c::clear */
#define CNT_GAME_FRAME 21272                 /* (r13 - 21272: m_gameFrame, - 21268: m_exeFrame) */
static void cCounter_clear(GM_CTX) {
    ctx->r[0] = 0;
    gm_set_u32(ctx->r[13] - CNT_GAME_FRAME, 0); gm_set_u32(ctx->r[13] - CNT_GAME_FRAME + 4, 0);
}

/* ================================================================== hle entry points
   On (13): reached by the test runs, checked with RT_GM_VERIFY_REGS=1 (0 differences in 1-1, 4-1
   and the title demos) but sPhase_c::callMethod (plain: it calls the phase methods; A/B checked).
   Written but off (not reached): chaseAngleByRotDir. */
#define A(i) GM_ARG(i)
#define FA(i) GM_FARG(i)
#define S(i) ((int32_t)GM_ARG(i))
GM_HLE_VOID(fn_8015F140, A(0), 4) { s_addCalc(GM_PASS, A(0), FA(0), FA(1), FA(2), FA(3)); }                         /* sLib::addCalc */
GM_HLE_INT(fn_8015F200, A(0), 2) {                                                                                  /* ::addCalcAngle(5) */
    for (int i = 4; i <= 7; i++) ctx->r[i] = S16X(ctx->r[i]);
    GM_RET(s_addCalcAngle(GM_PASS, A(0), S(1), S(2), S(3), S(4)));
}
GM_HLE_INT(fn_8015F220, A(0), 2) { GM_RET(s_addCalcAngle(GM_PASS, A(0), S(1), S(2), S(3), S(4))); }                /* (extended) */
GM_HLE_VOID(fn_8015F2E0, A(0), 2) {                                                                                 /* ::addCalcAngle(4) */
    for (int i = 4; i <= 6; i++) ctx->r[i] = S16X(ctx->r[i]);
    s_addCalcAngle4(GM_PASS, A(0), S(1), S(2), S(3));
}
GM_HLE_INT(fn_8015F340, A(0), 2) { ctx->r[4] = S16X(ctx->r[4]); ctx->r[5] = S16X(ctx->r[5]); GM_RET(s_chase_s16(GM_PASS, A(0), S(1), S(2))); }   /* ::chase(s16) */
GM_HLE_INT(fn_8015F350, A(0), 2) { GM_RET(s_chase_s16(GM_PASS, A(0), S(1), S(2))); }                              /* (extended) */
GM_HLE_INT(fn_8015F3C0, A(0), 4) { GM_RET(s_chase_s32(GM_PASS, A(0), S(1), S(2))); }                              /* ::chase(int) */
GM_HLE_INT(fn_8015F420, A(0), 4) { GM_RET(s_chase_s32(GM_PASS, A(0), S(1), S(2))); }                              /* ::chase(long) */
GM_HLE_INT(fn_8015F480, A(0), 4) { GM_RET(s_chase_f(GM_PASS, A(0), FA(0), FA(1))); }                              /* ::chase(float) */
GM_HLE_INT(SmoothRotation__FPsss, A(0), 2) { GM_RET(s_chaseAngle(GM_PASS, A(0), S(1), S(2))); }                   /* ::chaseAngle */
GM_HLE(fn_8015F560) { GM_RET(s_chaseAngleByRotDir(GM_PASS, A(0), S(1), S(2))); }                     /* ::chaseAngleByRotDir */
GM_HLE_VOID(setup__13FunctionChainFPPFPv_bUs, A(0), 8) { sPhase_setup(GM_PASS, A(0), A(1), A(2)); }               /* sPhase_c::sPhase_c */
GM_HLE(fn_8015F620) { GM_RET(sPhase_callMethod(GM_PASS, A(0), A(1))); }                                           /* ::callMethod */
GM_HLE_VOID(fn_8015FE40, ctx->r[13] - CNT_GAME_FRAME, 8) { cCounter_clear(GM_PASS); }                             /* cCounter_c::clear */
