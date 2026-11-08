/* gm_m_mtx.c - mLib's matrix and vector helpers: mMtx_c (rotation matrices from s16 angles,
 * concatenated rotations, toRot, multVecZero, zero, the constructor and Identity) and mVec3_c
 * (normalize, normalizeRS, rotX / rotY and the unit vectors). Track B (gm.h, docs/DECOMP.md),
 * instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_mtx.cpp, m_vec.cpp) and checked against the
 * recompiled USA rev 2 code (0x8016EBA0-0x8016F1E8, 0x80170980-0x80170C44). The angle goes to
 * nw4r's SinFIdx / CosFIdx as the compiler does it: stored as an s16 on the stack and read back
 * with a quantised paired-single load (psq_l, GQR 3), times 1/256. Every float step is rounded to
 * single as the recompiled code rounds it (fmuls / fadds / fdivs: frsp, both halves). The
 * non-volatile registers are mirrored around nested calls (gm_nv.h). */
#include "gm.h"
#include "gm_nv.h"
#include <math.h>

#define F_COS_IDX   0x80237C40u          /* nw4r::math::CosFIdx */
#define F_SIN_IDX   0x80237BD0u          /* nw4r::math::SinFIdx */
#define F_FRSQRT    0x80237BA0u          /* nw4r::math::FrSqrt */
#define F_ATAN2S    0x801611C0u          /* cM::atan2s */
#define F_CONCAT    0x801C0540u          /* PSMTXConcat */
#define F_VEC_MAG   0x801C14C0u          /* PSVECMag */
#define F_MTX_CT    0x8016EBA0u          /* mMtx_c::mMtx_c(12 floats) */
#define MTX_IDENTITY 0x80377C58u         /* mMtx_c::Identity */
#define VEC_ZERO    0x80377DC8u          /* mVec3_c::Zero, Ex, Ey, Ez (12 bytes each) */

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f
static inline double fl(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }   /* (lfs / fmuls ...: both halves) */

/* cos and sin of the angle at ang_p (an s16), each through the stack at f+10 / f+8; the cosine
   is kept in f31 across the sine call. k: the 1/256 scale's small-data offset. */
static double sin_cos(GM_CTX, gptr f, gptr ang_p, uint32_t k, double *pcos) {
    gm_set_u16(f + 10, (uint16_t)(int16_t)gm_s16(ang_p));
    psq_l(ctx, base, 1, f + 10, 1, 3);
    double s = fl(ctx, 0, R2F(k));
    fl(ctx, 1, frsp(s * ctx->f[1].d));
    GM_CALL(F_COS_IDX, 0);
    double c = ctx->f[1].d;
    gm_set_u16(f + 8, (uint16_t)(int16_t)gm_s16(ang_p));
    ctx->f[31].u = ctx->f[1].u;
    psq_l(ctx, base, 1, f + 8, 1, 3);
    s = fl(ctx, 0, R2F(k));
    fl(ctx, 1, frsp(s * ctx->f[1].d));
    GM_CALL(F_SIN_IDX, 0);
    *pcos = c;
    return ctx->f[1].d;
}

/* ================================================================== mMtx_c */
/* XrotS / YrotS / ZrotS(angle): the rotation matrix alone */
static void rot_s(GM_CTX, int axis, gptr m, gptr ang_p) {
    static const uint32_t addr[3] = { 0x8016EBF0u, 0x8016ED10u, 0x8016EE30u };   /* FNADDR */
    FN(addr[axis]); GM_NV_KEEP;
    NV_R(31, ang_p); NV_R(30, m);
    double c, s = sin_cos(GM_PASS, f, ang_p, 21344, &c);
    double one = R2F(21340), z = R2F(21336);
    if (axis == 0) {
        SF(m + 0, one); SF(m + 4, z); SF(m + 8, z); SF(m + 12, z);
        SF(m + 16, z); SF(m + 20, c); SF(m + 24, -s); SF(m + 28, z);
        SF(m + 32, z); SF(m + 36, s); SF(m + 40, c); SF(m + 44, z);
    } else if (axis == 1) {
        SF(m + 0, c); SF(m + 4, z); SF(m + 8, s); SF(m + 12, z);
        SF(m + 16, z); SF(m + 20, one); SF(m + 24, z); SF(m + 28, z);
        SF(m + 32, -s); SF(m + 36, z); SF(m + 40, c); SF(m + 44, z);
    } else {
        SF(m + 0, c); SF(m + 8, z); SF(m + 4, -s); SF(m + 12, z);
        SF(m + 16, s); SF(m + 20, c); SF(m + 24, z); SF(m + 28, z);
        SF(m + 32, z); SF(m + 36, z); SF(m + 40, one); SF(m + 44, z);
    }
}
/* XrotM / YrotM / ZrotM(angle): this = this * rotation, unless the angle is 0 */
static void rot_m(GM_CTX, int axis, gptr m, gptr ang_p) {
    static const uint32_t addr[3] = { 0x8016ECB0u, 0x8016EDD0u, 0x8016EEF0u };   /* FNADDR */
    static const uint32_t ra[3] = { 0x8016ECE4u, 0x8016EE04u, 0x8016EF24u };
    FN(addr[axis]); GM_NV_KEEP;
    NV_R(31, m);
    if (!gm_s16(ang_p)) return;
    gm_set_u16(f + 8, gm_u16(ang_p));
    NCALL(ra[axis], rot_s(GM_PASS, axis, f + 16, f + 8));
    GM_CALL(F_CONCAT, 3, m, f + 16, m);
}
/* ZXYrotM(x, y, z): Y, then X, then Z; XYZrotM(x, y, z): Z, Y, X (the angles passed by value:
   copied to the stack) */
static void rot_zxy(GM_CTX, gptr m, gptr x, gptr y, gptr z) {
    FN(0x8016EF50); GM_NV_KEEP;
    NV_R(31, z); NV_R(30, x); NV_R(29, m);
    gm_set_u16(f + 16, gm_u16(y)); NCALL(0x8016EF84u, rot_m(GM_PASS, 1, m, f + 16));
    gm_set_u16(f + 12, gm_u16(x)); NCALL(0x8016EF98u, rot_m(GM_PASS, 0, m, f + 12));
    gm_set_u16(f + 8, gm_u16(z));  NCALL(0x8016EFACu, rot_m(GM_PASS, 2, m, f + 8));
}
static void rot_xyz(GM_CTX, gptr m, gptr x, gptr y, gptr z) {
    FN(0x8016EFD0); GM_NV_KEEP;
    NV_R(31, y); NV_R(30, x); NV_R(29, m);
    gm_set_u16(f + 16, gm_u16(z)); NCALL(0x8016F004u, rot_m(GM_PASS, 2, m, f + 16));
    gm_set_u16(f + 12, gm_u16(y)); NCALL(0x8016F018u, rot_m(GM_PASS, 1, m, f + 12));
    gm_set_u16(f + 8, gm_u16(x));  NCALL(0x8016F02Cu, rot_m(GM_PASS, 0, m, f + 8));
}
/* toRot(out): the three angles of a rotation matrix (cM::atan2s) */
static void to_rot(GM_CTX, gptr m, gptr out) {
    FN(0x8016F050); GM_NV_KEEP;
    double m22 = fl(ctx, 0, LF(m + 40));
    m22 = fl(ctx, 0, frsp(m22 * m22));
    double cs = fl(ctx, 2, R2F(21336));
    double sq = fl(ctx, 31, LF(m + 8));
    NV_R(31, out); NV_R(30, m);
    sq = fl(ctx, 31, frsp(sq * sq));
    sq = fl(ctx, 31, frsp(sq + m22));
    if (!(sq < cs || sq == cs)) {
        ctx->f[1].u = ctx->f[31].u;
        GM_CALLR(0x8016F0A4u, F_FRSQRT, 0);
        cs = fl(ctx, 2, frsp(sq * ctx->f[1].d));
    }
    /* (the y argument: fneg of the loaded word, ps0 only) */
    double v = fl(ctx, 0, LF(m + 24));
    ctx->f[1].u = ctx->f[0].u ^ 0x8000000000000000ull;
    ctx->f[2].d = cs; (void)v;
    uint32_t rx = GM_CALLR(0x8016F0B4u, F_ATAN2S, 0);
    gm_set_u16(out, (uint16_t)rx);
    int16_t x = (int16_t)rx;
    if (x == 0x4000 || x == -0x4000) {
        fl(ctx, 0, LF(m + 32));
        gm_set_u16(out + 4, 0);
        ctx->f[1].u = ctx->f[0].u ^ 0x8000000000000000ull;
        fl(ctx, 2, LF(m + 0));
        gm_set_u16(out + 2, (uint16_t)GM_CALLR(0x8016F0E4u, F_ATAN2S, 0));
    } else {
        fl(ctx, 1, LF(m + 8)); fl(ctx, 2, LF(m + 40));
        gm_set_u16(out + 2, (uint16_t)GM_CALLR(0x8016F0F8u, F_ATAN2S, 0));
        fl(ctx, 1, LF(m + 16)); fl(ctx, 2, LF(m + 20));
        gm_set_u16(out + 4, (uint16_t)GM_CALLR(0x8016F108u, F_ATAN2S, 0));
    }
}
/* Identity (a static initialiser): the constructor with 1 0 0 0 / 0 1 0 0 / 0 0 1 0, the last
   four arguments on the stack */
static void mtx_sinit(GM_CTX) {
    FN(0x8016F190);
    double z = fl(ctx, 2, R2F(21336));
    double one = fl(ctx, 1, R2F(21340));
    ctx->f[3].u = ctx->f[2].u; SF(f + 8, z);
    ctx->f[4].u = ctx->f[2].u; ctx->f[5].u = ctx->f[2].u; SF(f + 12, z);
    ctx->f[6].u = ctx->f[1].u; ctx->f[7].u = ctx->f[2].u; SF(f + 16, one);
    ctx->f[8].u = ctx->f[2].u; SF(f + 20, z);
    GM_CALLR(0x8016F1D8u, F_MTX_CT, 1, MTX_IDENTITY);
}

/* ================================================================== mVec3_c */
/* normalize: the length; the vector scaled by 1 / length unless the length is ~0 */
static int vec_normalize(GM_CTX, uint32_t addr, gptr v) {
    FN(addr); GM_NV_KEEP;
    NV_R(31, v);
    GM_CALL(F_VEC_MAG, 1, v);
    double mag = ctx->f[1].d;
    double a = frsp(fabs(mag)), eps = R2F(21292);
    if (a < eps || a == eps) return 0;
    double inv = frsp(R2F(21288) / mag);
    double x = frsp(LF(v + 0) * inv), y = frsp(LF(v + 4) * inv), z = frsp(LF(v + 8) * inv);
    SF(v + 0, x); SF(v + 4, y); SF(v + 8, z);
    return 1;
}
static void vec_rot(GM_CTX, int axis, gptr v, gptr ang_p) {
    FN(axis ? 0x80170B40u : 0x80170A90u); GM_NV_KEEP;
    NV_R(31, ang_p); NV_R(30, v);
    double c, s = sin_cos(GM_PASS, f, ang_p, 21296, &c);
    if (axis == 0) {                                                       /* rotX */
        double y = LF(v + 4), z = LF(v + 8);
        double a = frsp(c * y), b = frsp(s * z), d = frsp(s * y), e = frsp(c * z);
        SF(v + 4, frsp(a - b)); SF(v + 8, frsp(d + e));
    } else {                                                               /* rotY */
        double z = LF(v + 8), x = LF(v + 0);
        double a = frsp(c * z), b = frsp(s * z), d = frsp(-s * x), e = frsp(c * x);
        SF(v + 8, frsp(d + a)); SF(v + 0, frsp(e + b));
    }
}

/* ================================================================== hle entry points
   On (13): reached by the test runs, or the same code as a reached one but for a constant (XrotS,
   normalizeRS). Written but off (not reached): XYZrotM, toRot, zero, mVec3_c::rotX / rotY. */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
E(fn_8016EBA0) {                                                                                /* mMtx_c::mMtx_c(12 floats) */
    gptr m = A(0), sp = ctx->r[1];
    double a = LF(sp + 8), b = LF(sp + 12), c = LF(sp + 16), d = LF(sp + 20);
    fl(ctx, 11, a); fl(ctx, 10, b); fl(ctx, 9, c); fl(ctx, 0, d);
    for (int i = 0; i < 8; i++) SF(m + 4 * i, ctx->f[1 + i].d);
    SF(m + 32, a); SF(m + 36, b); SF(m + 40, c); SF(m + 44, d);
}
E(rotationX__4mMtxFPs) { rot_s(GM_PASS, 0, A(0), A(1)); }                                      /* ::XrotS */
E(rotationY__4mMtxFPs) { rot_s(GM_PASS, 1, A(0), A(1)); }                                      /* ::YrotS */
E(rotationZ__4mMtxFPs) { rot_s(GM_PASS, 2, A(0), A(1)); }                                      /* ::ZrotS */
E(applyRotationX__4mMtxFPs) { GM_LR_KEEP; rot_m(GM_PASS, 0, A(0), A(1)); }                     /* ::XrotM */
E(applyRotationY__4mMtxFPs) { GM_LR_KEEP; rot_m(GM_PASS, 1, A(0), A(1)); }                     /* ::YrotM */
E(applyRotationZ__4mMtxFPs) { GM_LR_KEEP; rot_m(GM_PASS, 2, A(0), A(1)); }                     /* ::ZrotM */
E(applyRotationYXZ__4mMtxFPsPsPs) { GM_LR_KEEP; rot_zxy(GM_PASS, A(0), A(1), A(2), A(3)); }    /* ::ZXYrotM */
E(applyRotationZYX__4mMtxFPsPsPs) { GM_LR_KEEP; rot_xyz(GM_PASS, A(0), A(1), A(2), A(3)); }    /* ::XYZrotM */
E(fn_8016F050) { to_rot(GM_PASS, A(0), A(1)); }                                                 /* ::toRot */
E(fn_8016F130) {                                                                                /* ::multVecZero */
    gptr m = A(0), o = A(1);
    double x = fl(ctx, 2, LF(m + 12)), y = fl(ctx, 1, LF(m + 28)), z = fl(ctx, 0, LF(m + 44));
    SF(o + 0, x); SF(o + 4, y); SF(o + 8, z);
}
E(zero__4mMtxFv) { double z = fl(ctx, 0, R2F(21336)); for (int i = 0; i < 12; i++) SF(A(0) + 4 * i, z); }   /* ::zero */
E(fn_8016F190) { mtx_sinit(GM_PASS); }                                                          /* (mMtx_c::Identity) */
E(fn_80170980) { vec_normalize(GM_PASS, 0x80170980u, A(0)); }   /* FNADDR */                                   /* mVec3_c::normalize (returns the length in f1) */
E(fn_80170A00) { GM_RET(vec_normalize(GM_PASS, 0x80170A00u, A(0))); }   /* FNADDR */                           /* ::normalizeRS */
E(fn_80170A90) { vec_rot(GM_PASS, 0, A(0), A(1)); }                                             /* ::rotX */
E(fn_80170B40) { vec_rot(GM_PASS, 1, A(0), A(1)); }                                             /* ::rotY */
E(fn_80170BF0) {                                                                                /* (Zero, Ex, Ey, Ez) */
    double z = fl(ctx, 1, R2F(21284)), one = fl(ctx, 0, R2F(21288));
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++) SF(VEC_ZERO + 12 * i + 4 * j, (i && j == i - 1) ? one : z);
}
