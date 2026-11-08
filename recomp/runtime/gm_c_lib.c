/* gm_c_lib.c - cLib's helpers: vector chasing (cLib::addCalcPos, chasePos, targetAngleY / X),
 * the math (cM::rad2s, atan2s and its table lookup, the game random number generator: initRnd,
 * rnd, rndInt, rndF), cRandom_c (ranqd1: getRandom, getRandomF, getRandomF2), cM3d_calcInDivPos1 / 2
 * and cOwnerSetMg_c (add, remove, clear). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/cLib/c_lib.cpp, c_math.cpp, c_random.cpp, c_m3d.cpp,
 * c_owner_set.cpp) and checked against the recompiled USA rev 2 code (0x80160AE0-0x80160F04,
 * 0x80161060-0x80161524, 0x80161740-0x80161918). Like gm_s_lib.c these leave every register as the
 * PowerPC code does (RT_GM_VERIFY_REGS=1): the last compare's CR0 and FPSCR class bits, XER[CA] of
 * the carry arithmetic, the volatile temporaries, and the float steps rounded and paired as the
 * recompiled code has them (lfs / fadds ...: both halves; fmr / fneg / fabs / frsp / lfd: ps0).
 * Guest calls that end a function's work (PSVECMag, EGG::Math::sqrt, fmod, the PSVEC helpers) are
 * GM_CALLV: their registers are the result.
 *
 * Not here (still recompiled): cLib::memSet (a branch to memset), the static constructor that
 * seeds the two generators. */
#include "gm.h"
#include "gm_nv.h"

#define F_VEC_MAG   0x801C14C0u          /* PSVECMag */
#define F_VEC_SCALE 0x801C1450u          /* PSVECScale */
#define F_VEC_ADD   0x801C13F0u          /* PSVECAdd */
#define F_VEC_SUB   0x801C1420u          /* PSVECSubtract */
#define F_SQRT      0x802BE470u          /* EGG::Math<float>::sqrt */
#define F_FMOD      0x802E8614u          /* fmod */
#define ATAN_TABLE  (0x80330000u - 29880u) /* atntable (1025 u16) */
/* small data (r2 - n): floats unless noted */
#define K_EPS_POS   21632                /* cLib::isZero's epsilon (addCalcPos, chasePos) */
#define K_ZERO_CP   21628                /* 0.0 (chasePos) */
#define K_TWO_PI    21624                /* (double) 2 pi */
#define K_CIRCLE    21616                /* 65536 / 2 pi */
#define K_ATAN_N    21612                /* 1024.0 */
#define K_EPS_ATAN  21608                /* cLib::isZero's epsilon (atan2s) */
#define K_ZERO_AT   21604                /* 0.0 (atan2s) */
#define K_I2F       21600                /* (double) 2^52 + 2^31: int to float */
#define K_ONE       21592                /* 1.0 */
#define K_ONE_HALF  21588                /* 1.5 */
/* r13 - n */
#define RND_SEED    21232                /* s_rnd.mSeed (s_rnd2: - 21228) */
#define RND_MUL     25144                /* cRandom::l_RANDOM_MUL (0x19660D), l_RANDOM_ADD (0x3C6EF35F) at - 25140 */

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }   /* both halves */
static inline double f0_(ppc_context *ctx, int n, double v) { ctx->f[n].d = v; return v; }             /* ps0 only */
#define FB(n, v) fb(ctx, (n), (v))
#define F0(n, v) f0_(ctx, (n), (v))
#define FR(n) (ctx->f[n].d)
#define FMR(d, s) (ctx->f[d].u = ctx->f[s].u)
#define FABS(d, s) (ctx->f[d].u = ctx->f[s].u & ~0x8000000000000000ull)
#define FNEG(d, s) (ctx->f[d].u = ctx->f[s].u ^ 0x8000000000000000ull)
static inline int cmps(ppc_context *ctx, int n, int32_t a, int32_t b) { cr_cmp_s(ctx, n, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, int n, uint32_t a, uint32_t b) { cr_cmp_u(ctx, n, a, b); return (a > b) - (a < b); }
/* fcmpu into CR0 (and FPSCR's class bits); returns the CR field (8 lt, 4 gt, 2 eq, 1 unordered) */
static inline uint32_t fcmp(ppc_context *ctx, double a, double b) { cr_fcmp(ctx, 0, a, b); return ctx->cr >> 28; }
/* ">=" as compiled: cror puts gt | eq into CR0's eq bit, which the branch then tests */
static inline int ge_cr(ppc_context *ctx, uint32_t c) { int v = (c & 6) != 0; CR_SETBIT(ctx, 2, v); return v; }
#define GE(c) ge_cr(ctx, (c))
/* cLib::isZero(x) as compiled: fabs, frsp, fcmpu against the epsilon, the lt bit into r0 with a
   record form (CR0 = r0 against 0); the fabs'd value is left in fd */
static int is_zero(GM_CTX, int fd, int fs, int fe) {
    FABS(fd, fs);
    F0(fd, frsp(FR(fd)));
    fcmp(ctx, FR(fd), FR(fe));
    ctx->r[0] = ctx->cr >> 31;
    cr_cmp_s(ctx, 0, (int32_t)ctx->r[0], 0);
    return ctx->r[0] != 0;
}
/* a vector's three floats into f2, f1, f0 (lfs) and stored to dst - "*dst = src" as compiled */
static void vec_copy(GM_CTX, gptr dst, gptr src) {
    FB(2, LF(src)); FB(1, LF(src + 4)); FB(0, LF(src + 8));
    SF(dst, FR(2)); SF(dst + 4, FR(1)); SF(dst + 8, FR(0));
}
/* *a != *b, as the inlined operator compiles it: f1 / f0 hold the last pair compared (x in f4 / f0) */
static int vec_ne(GM_CTX, gptr a, gptr b, int fx) {
    double bx = FB(0, LF(b)), ax = FB(fx, LF(a));
    if (fcmp(ctx, ax, bx) != 2) return 1;
    if (fcmp(ctx, FB(1, LF(a + 4)), FB(0, LF(b + 4))) != 2) return 1;
    if (fcmp(ctx, FB(1, LF(a + 8)), FB(0, LF(b + 8))) != 2) return 1;
    return 0;
}

/* ================================================================== cM: the random numbers
   ranqd1: seed = seed * 0x19660D + 0x3C6EF35F, as mulhwu / mullw / addc / adde (the carry left
   in XER[CA]); the high word of that 64-bit sum is dropped by adde's add of the high product. */
static uint32_t ranqd_step(GM_CTX, uint32_t x, uint32_t *hi_out, uint32_t *mul, uint32_t *add) {
    *mul = gm_u32(ctx->r[13] - RND_MUL); *add = gm_u32(ctx->r[13] - RND_MUL + 4);
    uint32_t hi = (uint32_t)(((uint64_t)x * *mul) >> 32), lo = x * *mul;
    uint64_t t = (uint64_t)lo + *add; lo = (uint32_t)t; ctx->xer_ca = (uint32_t)(t >> 32);
    t = (uint64_t)lo + hi + ctx->xer_ca; ctx->xer_ca = (uint32_t)(t >> 32);
    *hi_out = hi;
    return (uint32_t)t;
}
/* cRandom_c::getRandom(max): a number in [0, max) */
static uint32_t cRandom_getRandom(GM_CTX, gptr rnd, uint32_t max) {
    uint32_t hi, mul, add, s = ranqd_step(GM_PASS, gm_u32(rnd), &hi, &mul, &add);
    ctx->r[5] = mul; ctx->r[6] = add; ctx->r[7] = hi; ctx->r[0] = s;
    gm_set_u32(rnd, s);
    return (uint32_t)(((uint64_t)s * max) >> 32);
}
/* cRandom_c::getRandomF() / getRandomF2(): 23 bits of the seed as a float in [1, 2), minus 1 / 1.5 -
   built in a stack word (the 16-byte frame) and read back with lfs */
static double cRandom_getRandomF(GM_CTX, gptr rnd, uint32_t k_sub) {
    GM_FRAME(16);
    uint32_t hi, mul, add, s = ranqd_step(GM_PASS, gm_u32(rnd), &hi, &mul, &add);
    ctx->r[0] = mul; ctx->r[5] = add; ctx->r[6] = hi; ctx->r[4] = s;
    double sub = FB(0, R2F(k_sub));
    ctx->r[0] = ((s >> 9) & 0x7FFFFFu) | 0x3F800000u;
    gm_set_u32(rnd, s);
    gm_set_u32(gm_frame_sp + 8, ctx->r[0]);
    return FB(1, frsp(FB(1, LF(gm_frame_sp + 8)) - sub));
}
/* cM::initRnd(seed) / rnd() (s_rnd) / rndInt(max) / rndF(max) */
static void cM_initRnd(GM_CTX, uint32_t seed) { gm_set_u32(ctx->r[13] - RND_SEED, seed); }
static double cM_rnd(GM_CTX) {
    ctx->r[3] = ctx->r[13] - RND_SEED;
    return cRandom_getRandomF(GM_PASS, ctx->r[3], K_ONE);
}
static uint32_t cM_rndInt(GM_CTX, int32_t max) {
    FN(0x801613A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, max);
    NCALL(0x801613B8u, cM_rnd(GM_PASS));
    ctx->r[3] = (uint32_t)max ^ 0x80000000u;                /* (int to float through the stack) */
    ctx->r[0] = 0x43300000u;
    gm_set_u32(f + 12, ctx->r[3]);
    ctx->f[2].u = ld64(base, ctx->r[2] - K_I2F);
    gm_set_u32(f + 8, ctx->r[0]);
    ctx->f[0].u = ld64(base, f + 8);
    ctx->r[0] = lr;
    FB(0, frsp(FR(0) - FR(2)));
    FB(0, frsp(FR(0) * FR(1)));
    ctx->f[0].u = fctiw_bits(FR(0), 1);
    st64(base, f + 16, ctx->f[0].u);
    return gm_u32(f + 20);
}
static double cM_rndF(GM_CTX, double max) {
    FN(0x80161400); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_F(31, max);
    NCALL(0x8016141Cu, cM_rnd(GM_PASS));
    FB(1, frsp(FR(31) * FR(1)));
    ctx->r[0] = lr;
    return FR(1);
}

/* ================================================================== cM: angles */
/* rad2s(rad): fmod by 2 pi, to a 16-bit angle */
static uint32_t cM_rad2s(GM_CTX, double rad) {
    FN(0x80161120); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    (void)rad;
    ctx->f[2].u = ld64(base, ctx->r[2] - K_TWO_PI);
    GM_CALLV(0x80161134u, F_FMOD, 0);
    F0(1, frsp(FR(1)));
    FB(0, R2F(K_CIRCLE));
    FB(0, frsp(FR(1) * FR(0)));
    ctx->f[0].u = fctiw_bits(FR(0), 1);
    st64(base, f + 8, ctx->f[0].u);
    int32_t m = gm_s32(f + 12);
    if (cmps(ctx, 0, m, -32768) < 0) m += 0x10000;
    else if (cmps(ctx, 0, m, 32767) > 0) m -= 0x10000;
    ctx->r[0] = lr;
    return (uint32_t)(int32_t)(int16_t)m;
}
/* U_GetAtanTable(sin, cos): atntable[sin / cos * 1024] (a leaf with a 16-byte frame for the
   float-to-int conversion) */
static uint32_t U_GetAtanTable(GM_CTX) {
    FB(1, frsp(FR(1) / FR(2)));
    FB(0, R2F(K_ATAN_N));
    GM_FRAME(16);
    ctx->r[3] = ATAN_TABLE;
    FB(0, frsp(FR(0) * FR(1)));
    ctx->f[0].u = fctiw_bits(FR(0), 1);
    st64(base, gm_frame_sp + 8, ctx->f[0].u);
    ctx->r[0] = gm_u32(gm_frame_sp + 12) << 1;
    return ctx->r[3] = gm_u16(ctx->r[3] + ctx->r[0]);
}
/* atan2s(sin, cos): the angle of (cos, sin) as a 16-bit angle, from the 0-45 degree table and
   the octant (cM::atan2i inlined) */
static uint32_t cM_atan2s(GM_CTX) {
    FN(0x801611C0); GM_LR_KEEP;
    uint32_t lr = ctx->lr, r;
    double s = FR(1), c = FR(2);
#define U(ra) (NCALL((ra), U_GetAtanTable(GM_PASS)) & 0xFFFFu)
    FB(0, R2F(K_EPS_ATAN));
    FMR(4, 1);                                              /* (f4: sin, for the swapped calls) */
    if (is_zero(GM_PASS, 3, 1, 0)) {                        /* 0 or 180 degrees */
        r = GE(fcmp(ctx, c, FB(0, R2F(K_ZERO_AT)))) ? 0 : 0x8000;
    } else if (is_zero(GM_PASS, 3, 2, 0)) {                 /* 90 or 270 */
        r = GE(fcmp(ctx, s, FB(0, R2F(K_ZERO_AT)))) ? 0x4000 : 0xC000;
    } else if (GE(fcmp(ctx, s, FB(0, R2F(K_ZERO_AT))))) {
        if (GE(fcmp(ctx, c, FR(0)))) {                      /* 0-90: the table or its complement */
            if (GE(fcmp(ctx, c, s))) r = U(0x80161278u);
            else { FMR(1, 2); FMR(2, 4); ctx->r[0] = U(0x8016128Cu); ctx->xer_ca = 0x4000u >= ctx->r[0]; r = 0x4000u - ctx->r[0]; }
        } else {                                            /* 90-180 */
            FNEG(2, 2);
            if (fcmp(ctx, FR(2), s) & 8) { FMR(1, 2); FMR(2, 4); r = U(0x801612B0u) + 0x4000u; }
            else { r = U(0x801612C0u); ctx->r[4] = 0x10000u; ctx->r[0] = 0x8000u; r = 0x8000u - r; }
        }
    } else if (fcmp(ctx, c, FR(0)) & 8) {                   /* 180-270 */
        FNEG(2, 2); FNEG(0, 1);
        if (GE(fcmp(ctx, FR(2), FR(0)))) { FMR(1, 0); r = U(0x801612F8u) + 0x8000u; }
        else { FMR(1, 2); FMR(2, 0); r = U(0x80161314u); ctx->r[4] = 0x10000u; ctx->r[0] = 0xC000u; r = 0xC000u - r; }
    } else {                                                /* 270-360 */
        FNEG(0, 1);
        if (fcmp(ctx, c, FR(0)) & 8) { FMR(1, 2); FMR(2, 0); r = U(0x80161340u) + 0xC000u; }
        else { FMR(1, 0); ctx->r[0] = U(0x80161358u); r = (uint32_t)-(int32_t)ctx->r[0]; }
    }
#undef U
    ctx->r[0] = lr;
    return (uint32_t)(int32_t)(int16_t)r;
}

/* ================================================================== cLib: vectors */
/* addCalcPos(cur, target, ratio, maxStep, minStep): cur moves by ratio of the way, the step
   clamped to [minStep, maxStep] (snaps when closer than minStep); returns the distance left */
static double cLib_addCalcPos(GM_CTX, gptr cur, gptr tgt, double ratio, double max_step, double min_step) {
    FN(0x80160AE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_F(31, min_step); NV_F(30, max_step); NV_F(29, ratio); NV_R(31, tgt); NV_R(30, cur);
    ctx->r[0] = 0;
    if (vec_ne(GM_PASS, cur, tgt, 4)) ctx->r[0] = 1;
    if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) != 0) {
        /* stepVector = *cur - target (the operator's temporary at f+8, the copy at f+20) */
        FB(3, LF(cur + 8)); FB(1, LF(tgt + 8)); FB(2, LF(cur + 4));
        FB(3, frsp(FR(3) - FR(1)));
        FB(1, LF(cur)); FB(0, LF(tgt + 4));
        ctx->r[3] = f + 20;
        SF(f + 16, FR(3));
        FB(2, frsp(FR(2) - FR(0)));
        FB(0, LF(tgt));
        SF(f + 12, FR(2));
        FB(0, frsp(FR(1) - FR(0)));
        SF(f + 24, FR(2)); SF(f + 8, FR(0)); SF(f + 20, FR(0)); SF(f + 28, FR(3));
        double dist = (GM_CALLV(0x80160BA4u, F_VEC_MAG, 1, f + 20), FR(1));
        if (fcmp(ctx, dist, FR(31)) & 8) vec_copy(GM_PASS, cur, tgt);           /* closer than minStep */
        else {
            double step = FB(6, frsp(dist * FR(29)));
            FB(1, LF(f + 28)); FB(0, LF(f + 24));
            FB(3, frsp(FR(1) * FR(29)));
            FB(2, LF(f + 20));
            FABS(5, 6);
            FB(4, frsp(FR(0) * FR(29)));
            FB(0, R2F(K_EPS_POS));
            FB(2, frsp(FR(2) * FR(29)));
            F0(1, frsp(FR(5)));
            SF(f + 24, FR(4)); SF(f + 20, FR(2));
            fcmp(ctx, FR(1), FR(0));
            SF(f + 28, FR(3));
            ctx->r[0] = ctx->cr >> 31;
            cr_cmp_s(ctx, 0, (int32_t)ctx->r[0], 0);
            if (ctx->r[0]) vec_copy(GM_PASS, cur, tgt);                            /* isZero(step) */
            else {
                int scale = 0;
                if (fcmp(ctx, step, FR(30)) & 4) { FB(0, frsp(FR(30) / step)); scale = 1; }
                else if (fcmp(ctx, step, FR(31)) & 8) { FB(0, frsp(FR(31) / step)); scale = 1; }
                if (scale) {
                    FB(2, frsp(FR(2) * FR(0))); FB(1, frsp(FR(4) * FR(0))); FB(0, frsp(FR(3) * FR(0)));
                    SF(f + 20, FR(2)); SF(f + 24, FR(1)); SF(f + 28, FR(0));
                }
                FB(1, LF(cur)); FB(0, LF(f + 20)); FB(2, LF(cur + 4));
                FB(0, frsp(FR(1) - FR(0)));
                FB(1, LF(cur + 8));
                SF(cur, FR(0));
                FB(0, LF(f + 24)); FB(0, frsp(FR(2) - FR(0))); SF(cur + 4, FR(0));
                FB(0, LF(f + 28)); FB(0, frsp(FR(1) - FR(0))); SF(cur + 8, FR(0));
            }
        }
    }
    /* the distance left: sqrt(dx^2 + dy^2 + dz^2) */
    FB(3, LF(cur)); FB(2, LF(tgt)); FB(1, LF(cur + 4));
    FB(4, frsp(FR(3) - FR(2)));
    FB(0, LF(tgt + 4)); FB(2, LF(cur + 8));
    FB(3, frsp(FR(1) - FR(0)));
    FB(0, LF(tgt + 8));
    FB(1, frsp(FR(4) * FR(4)));
    FB(2, frsp(FR(2) - FR(0)));
    FB(0, frsp(FR(3) * FR(3)));
    FB(2, frsp(FR(2) * FR(2)));
    FB(0, frsp(FR(1) + FR(0)));
    FB(1, frsp(FR(2) + FR(0)));
    GM_CALLV(0x80160CE0u, F_SQRT, 0);
    ctx->r[0] = lr;
    return FR(1);
}
/* chasePos(cur, target, step): cur moves step towards target; true once it is there */
static uint32_t cLib_chasePos(GM_CTX, gptr cur, gptr tgt, double step) {
    FN(0x80160D10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr, res;
    FB(0, R2F(K_ZERO_CP));
    uint32_t c0 = fcmp(ctx, step, FR(0));
    NV_F(31, step); NV_R(31, tgt); NV_R(30, cur);
    if (c0 != 2) {
        FB(1, LF(cur + 8)); FB(0, LF(tgt + 8)); FB(3, LF(cur + 4));
        FB(4, frsp(FR(1) - FR(0)));
        FB(1, LF(cur)); FB(2, LF(tgt + 4));
        ctx->r[3] = f + 20;
        FB(0, LF(tgt));
        FB(2, frsp(FR(3) - FR(2)));
        FB(0, frsp(FR(1) - FR(0)));
        SF(f + 28, FR(4)); SF(f + 24, FR(2)); SF(f + 20, FR(0));
        double dist = (GM_CALLV(0x80160D7Cu, F_VEC_MAG, 1, f + 20), FR(1));
        FB(0, R2F(K_EPS_POS));                              /* (isZero: f2 = |dist| against f0) */
        int snap = is_zero(GM_PASS, 2, 1, 0);
        if (!snap) {
            fcmp(ctx, dist, FR(31));
            CR_SETBIT(ctx, 2, CR_BIT(ctx, 0) | CR_BIT(ctx, 2));
            snap = CR_BIT(ctx, 2);
        }
        if (snap) { ctx->r[3] = 1; vec_copy(GM_PASS, cur, tgt); res = 1; }
        else {                                              /* *cur -= step / dist * offset (the product at f+8) */
            FB(5, frsp(FR(31) / dist));
            FB(4, LF(f + 28)); FB(0, LF(f + 24)); FB(3, LF(f + 20));
            FB(2, LF(cur)); FB(1, LF(cur + 4));
            FB(6, frsp(FR(0) * FR(5)));
            FB(0, LF(cur + 8));
            FB(4, frsp(FR(4) * FR(5)));
            FB(3, frsp(FR(3) * FR(5)));
            SF(f + 12, FR(6));
            FB(1, frsp(FR(1) - FR(6)));
            FB(0, frsp(FR(0) - FR(4)));
            SF(f + 8, FR(3));
            FB(2, frsp(FR(2) - FR(3)));
            SF(f + 16, FR(4));
            SF(cur, FR(2)); SF(cur + 4, FR(1)); SF(cur + 8, FR(0));
            res = 0;
        }
    } else {                                                /* no step: true if already there */
        ctx->r[0] = 0;
        FB(1, LF(cur)); FB(0, LF(tgt));
        if (fcmp(ctx, FR(1), FR(0)) == 2) {
            FB(1, LF(cur + 4)); FB(0, LF(tgt + 4));
            if (fcmp(ctx, FR(1), FR(0)) == 2) {
                FB(1, LF(cur + 8)); FB(0, LF(tgt + 8));
                if (fcmp(ctx, FR(1), FR(0)) == 2) ctx->r[0] = 1;
            }
        }
        res = cmps(ctx, 0, (int32_t)ctx->r[0], 0) != 0;
    }
    ctx->r[0] = lr;
    return res;
}
/* targetAngleY(from, to): atan2s(dx, dz) - a tail call */
static uint32_t cLib_targetAngleY(GM_CTX, gptr a, gptr b) {
    FB(3, LF(b)); FB(1, LF(a)); FB(2, LF(b + 8)); FB(0, LF(a + 8));
    FB(1, frsp(FR(3) - FR(1)));
    FB(2, frsp(FR(2) - FR(0)));
    return cM_atan2s(GM_PASS);
}
/* targetAngleX(from, to): atan2s(dy, the horizontal distance); the difference vector at f+8 */
static uint32_t cLib_targetAngleX(GM_CTX, gptr a, gptr b) {
    FN(0x80160EA0); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    FB(2, LF(b + 8)); FB(0, LF(a + 8)); FB(1, LF(b));
    FB(3, frsp(FR(2) - FR(0)));
    FB(0, LF(a)); FB(2, LF(b + 4));
    FB(4, frsp(FR(1) - FR(0)));
    FB(1, LF(a + 4));
    FB(0, frsp(FR(3) * FR(3)));
    FB(2, frsp(FR(2) - FR(1)));
    FB(1, frsp(FR(4) * FR(4)));
    SF(f + 8, FR(4));
    FB(1, frsp(FR(1) + FR(0)));
    SF(f + 12, FR(2)); SF(f + 16, FR(3));
    GM_CALLV(0x80160EECu, F_SQRT, 0);
    FMR(2, 1);
    FB(1, LF(f + 12));
    uint32_t r = NCALL(0x80160EF8u, cM_atan2s(GM_PASS));
    ctx->r[0] = lr;
    return r;
}

/* ================================================================== cM3d */
/* cM3d_calcInDivPos1(start, dir, scale, pos): pos = start + dir * scale */
static void cM3d_calcInDivPos1(GM_CTX, gptr start, gptr dir, gptr pos) {
    FN(0x80161060); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, pos); NV_R(30, start);
    GM_CALLV(0x80161088u, F_VEC_SCALE, 2, dir, f + 8);
    GM_CALLV(0x80161098u, F_VEC_ADD, 3, f + 8, start, pos);
    ctx->r[0] = lr;
}
/* cM3d_calcInDivPos2(a, b, scale, pos): pos = a + (b - a) * scale */
static void cM3d_calcInDivPos2(GM_CTX, gptr a, gptr b, gptr pos, double scale) {
    FN(0x801610B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_F(31, scale); NV_R(31, pos); NV_R(30, a);
    GM_CALLV(0x801610E4u, F_VEC_SUB, 3, b, a, f + 8);
    FMR(1, 31);
    ctx->r[3] = a; ctx->r[5] = pos; ctx->r[4] = f + 8;
    NCALL(0x801610F8u, cM3d_calcInDivPos1(GM_PASS, a, f + 8, pos));
    ctx->r[0] = lr;
}

/* ================================================================== cOwnerSetMg_c
   +0 the first node; a node: +0 its owner, +4 the next node. (A null argument calls an empty
   function first - a stripped assert: nothing to do here.) */
#define OS_OWNER 0
#define OS_NEXT  4
static void cOwnerSet_add(GM_CTX, gptr mg, gptr nd, gptr owner) {
    FN(0x80161750); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, owner); NV_R(30, nd); NV_R(29, mg);
    if (cmps(ctx, 0, (int32_t)mg, 0) != 0 && cmps(ctx, 0, (int32_t)nd, 0) != 0) cmps(ctx, 0, (int32_t)owner, 0);
    if (cmps(ctx, 0, (int32_t)nd, 0) != 0) {
        gptr cur = ctx->r[3] = gm_ptr(mg);
        int dup = 0;
        if (cmps(ctx, 0, (int32_t)cur, 0) == 0) gm_set_ptr(mg, nd);
        else {
            for (int first = 1;; first = 0) {
                if (!first) {
                    if (cmpu(ctx, 0, ctx->r[0], nd) == 0) { dup = 1; break; }
                    cur = ctx->r[3] = ctx->r[0];
                }
                ctx->r[0] = gm_ptr(cur + OS_NEXT);
                if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) == 0) break;
                GM_LOOP();
            }
            if (!dup) gm_set_ptr(cur + OS_NEXT, nd);
        }
        if (!dup) { ctx->r[0] = 0; gm_set_ptr(nd + OS_OWNER, owner); gm_set_ptr(nd + OS_NEXT, 0); }
    }
    ctx->r[0] = lr;
}
static void cOwnerSet_remove(GM_CTX, gptr mg, gptr nd, gptr owner) {
    FN(0x80161800); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, owner); NV_R(30, nd); NV_R(29, mg);
    if (cmps(ctx, 0, (int32_t)mg, 0) != 0 && cmps(ctx, 0, (int32_t)nd, 0) != 0) cmps(ctx, 0, (int32_t)owner, 0);
    if (cmps(ctx, 0, (int32_t)nd, 0) != 0) {
        ctx->r[0] = gm_ptr(nd + OS_OWNER);
        if (cmpu(ctx, 0, ctx->r[0], owner) == 0) {
            gptr cur = ctx->r[3] = gm_ptr(mg);
            int found = 1;
            if (cmpu(ctx, 0, cur, nd) == 0) { ctx->r[0] = gm_ptr(nd + OS_NEXT); gm_set_ptr(mg, ctx->r[0]); }
            else {
                for (int first = 1;; first = 0) {
                    if (!first) {
                        if (cmps(ctx, 0, (int32_t)ctx->r[0], 0) == 0) { found = 0; break; }
                        cur = ctx->r[3] = ctx->r[0];
                    }
                    ctx->r[0] = gm_ptr(cur + OS_NEXT);
                    if (cmpu(ctx, 0, ctx->r[0], nd) == 0) break;
                    GM_LOOP();
                }
                if (found) { ctx->r[0] = gm_ptr(nd + OS_NEXT); gm_set_ptr(cur + OS_NEXT, ctx->r[0]); }
            }
            if (found) { ctx->r[0] = 0; gm_set_ptr(nd + OS_OWNER, 0); gm_set_ptr(nd + OS_NEXT, 0); }
        }
    }
    ctx->r[0] = lr;
}
static void cOwnerSet_clear(GM_CTX, gptr mg) {
    FN(0x801618C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, mg);
    cmps(ctx, 0, (int32_t)mg, 0);
    gptr cur = ctx->r[3] = gm_ptr(mg);
    ctx->r[0] = 0;
    gm_set_ptr(mg, 0);
    for (int first = 1;; first = 0) {
        if (!first) {
            ctx->r[4] = gm_ptr(cur + OS_NEXT);
            gm_set_ptr(cur + OS_OWNER, 0); gm_set_ptr(cur + OS_NEXT, 0);
            cur = ctx->r[3] = ctx->r[4];
        }
        if (cmps(ctx, 0, (int32_t)cur, 0) == 0) break;
        GM_LOOP();
    }
    ctx->r[0] = lr;
}

/* ================================================================== hle entry points
   On (16): reached by the test runs, all checked with RT_GM_VERIFY_REGS=1 (0 differences in 1-1,
   4-1 and the title demos) but the owner set's three (plain: the list they walk isn't one memory
   range; A/B checked). Written but off (not reached): cM3d_calcInDivPos1 / 2, cM::rad2s. */
#define A(i) GM_ARG(i)
#define FA(i) GM_FARG(i)
#define RND_RANGE ctx->r[13] - RND_SEED, 4
GM_HLE_VOID(fn_80160AE0, A(0), 12) { cLib_addCalcPos(GM_PASS, A(0), A(1), FA(0), FA(1), FA(2)); }                 /* cLib::addCalcPos */
GM_HLE_INT(fn_80160D10, A(0), 12) { GM_RET(cLib_chasePos(GM_PASS, A(0), A(1), FA(0))); }                          /* ::chasePos */
GM_HLE_INT(targetAngleY__4cLibFRC7mVec3_cRC7mVec3_c, 0, 0) { GM_RET(cLib_targetAngleY(GM_PASS, A(0), A(1))); }    /* ::targetAngleY */
GM_HLE_INT(fn_80160EA0, 0, 0) { GM_RET(cLib_targetAngleX(GM_PASS, A(0), A(1))); }                                 /* ::targetAngleX */
GM_HLE(fn_80161060) { cM3d_calcInDivPos1(GM_PASS, A(0), A(1), A(2)); }                             /* cM3d_calcInDivPos1 */
GM_HLE(fn_801610B0) { cM3d_calcInDivPos2(GM_PASS, A(0), A(1), A(2), FA(0)); }                      /* cM3d_calcInDivPos2 */
GM_HLE(fn_80161120) { GM_RET(cM_rad2s(GM_PASS, FA(0))); }                                               /* cM::rad2s */
GM_HLE_INT(fn_80161180, 0, 0) { U_GetAtanTable(GM_PASS); }                                                        /* U_GetAtanTable */
GM_HLE_INT(fn_801611C0, 0, 0) { GM_RET(cM_atan2s(GM_PASS)); }                                                     /* cM::atan2s */
GM_HLE_VOID(fn_80161380, RND_RANGE) { cM_initRnd(GM_PASS, A(0)); }                                               /* ::initRnd */
GM_HLE_VOID(fn_80161390, RND_RANGE) { cM_rnd(GM_PASS); }                                                          /* ::rnd */
GM_HLE_INT(MakeRandomNumberForTiles__Fi, RND_RANGE) { GM_RET(cM_rndInt(GM_PASS, (int32_t)A(0))); }               /* ::rndInt */
GM_HLE_VOID(fn_80161400, RND_RANGE) { cM_rndF(GM_PASS, FA(0)); }                                                  /* ::rndF */
GM_HLE_INT(fn_80161460, A(0), 4) { GM_RET(cRandom_getRandom(GM_PASS, A(0), A(1))); }                              /* cRandom_c::getRandom */
GM_HLE_VOID(fn_80161490, A(0), 4) { cRandom_getRandomF(GM_PASS, A(0), K_ONE); }                                   /* ::getRandomF */
GM_HLE_VOID(fn_801614E0, A(0), 4) { cRandom_getRandomF(GM_PASS, A(0), K_ONE_HALF); }                              /* ::getRandomF2 */
GM_HLE(fn_80161750) { cOwnerSet_add(GM_PASS, A(0), A(1), A(2)); }   /* cOwnerSetMg_c::add */
GM_HLE(fn_80161800) { cOwnerSet_remove(GM_PASS, A(0), A(1), A(2)); }   /* ::remove */
GM_HLE(fn_801618C0) { cOwnerSet_clear(GM_PASS, A(0)); }                            /* ::clear */
