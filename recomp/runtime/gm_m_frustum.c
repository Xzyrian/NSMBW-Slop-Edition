/* gm_m_frustum.c - mLib's view frustum (mFrustum_c): the sphere and box tests models / actors are
 * culled with. Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_frustum.cpp) and checked against the
 * recompiled USA rev 2 code (0x8016DE00-0x8016E4AC): the two set()s (the planes, the corners
 * box, the near / far planes - USA adds those two) and the two tests. Every float step is rounded as the recompiled code rounds it (no fused multiply-add:
 * the compiler emitted separate fmuls / fadds; the box test's paired-single sum is transcribed
 * from the recompiled ps_mul / ps_madd / ps_sum0 on the same registers).
 *
 * mFrustum_c: +0 camera matrix (3x4), +48 / +64 / +80 / +96 the left / right / top / bottom planes
 * in view space (normal x, y, z, d), +112 near z, +116 far z, +120 the box (min, max), +144 the six
 * world planes (16 bytes each). */
#include "gm.h"
#include "gm_nv.h"

#define F_AABB_HIT  0x80239710u          /* nw4r::math::IntersectionAABB */

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f

/* intersectSphere(sphere): the centre into view space one axis at a time, with early outs */
static uint32_t frustum_sphere(GM_CTX, gptr m, gptr s) {
    GM_FRAME(32); gptr f = gm_frame_sp;              /* (made after the loads: not in the prologue - until part 57 the
                                                        temporaries went into the caller's frame) */
    double cx = LF(s), cy = LF(s + 4), cz = LF(s + 8), r = LF(s + 12);
    double z = frsp(LF(m + 44) + frsp(frsp(LF(m + 40) * cz) + frsp(frsp(LF(m + 32) * cx) + frsp(LF(m + 36) * cy))));
    SF(f + 16, z);
    if (frsp(z - r) > LF(m + 112)) return 0;
    if (frsp(z + r) < LF(m + 116)) return 0;
    double x = frsp(LF(m + 12) + frsp(frsp(LF(m + 8) * cz) + frsp(frsp(LF(m + 0) * cx) + frsp(LF(m + 4) * cy))));
    SF(f + 8, x);
    if (frsp(frsp(x * LF(m + 48)) + frsp(z * LF(m + 56))) > r) return 0;
    if (frsp(frsp(x * LF(m + 64)) + frsp(z * LF(m + 72))) > r) return 0;
    double y = frsp(LF(m + 28) + frsp(frsp(LF(m + 24) * cz) + frsp(frsp(LF(m + 16) * cx) + frsp(LF(m + 20) * cy))));
    SF(f + 12, y);
    if (frsp(frsp(y * LF(m + 84)) + frsp(z * LF(m + 88))) > r) return 0;
    return !(frsp(frsp(y * LF(m + 100)) + frsp(z * LF(m + 104))) > r);
}
/* intersectAABB(box): the boxes overlap, then the box's nearest corner is inside every plane */
static uint32_t frustum_aabb(GM_CTX, gptr m, gptr b) {
    FN(0x8016E3A0); GM_NV_KEEP;
    NV_R(31, b); NV_R(30, m);
    if (!GM_CALLR(0x8016E3C8u, F_AABB_HIT, 2, b, m + 120)) return 0;
    double z = R2F(21348);
    ctx->f[1].d = ctx->ps1[1] = z;
    for (int i = 0; i < 6; i++) {
        if (i) GM_LOOP();
        gptr p = m + 144 + 16 * i;
        SF(f + 8, LF(p) > z || LF(p) == z ? LF(b + 0) : LF(b + 12));
        SF(f + 12, LF(p + 4) > z || LF(p + 4) == z ? LF(b + 4) : LF(b + 16));
        SF(f + 16, LF(p + 8) > z || LF(p + 8) == z ? LF(b + 8) : LF(b + 20));
        psq_l(ctx, base, 2, p + 4, 0, 0);
        psq_l(ctx, base, 3, f + 12, 0, 0);
        psq_l(ctx, base, 4, p + 0, 1, 0);
        { double a_ = frsp(ctx->f[2].d * ctx->f[3].d), b_ = frsp(ctx->ps1[2] * ctx->ps1[3]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
        psq_l(ctx, base, 3, f + 8, 1, 0);
        ctx->f[0].d = ctx->ps1[0] = LF(p + 12);
        { double a_ = frsp(ctx->f[4].d * ctx->f[3].d + ctx->f[2].d), b_ = frsp(ctx->ps1[4] * ctx->ps1[3] + ctx->ps1[2]); ctx->f[3].d = a_; ctx->ps1[3] = b_; }
        { double a_ = frsp(ctx->f[3].d + ctx->ps1[2]), b_ = frsp(ctx->ps1[2]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
        ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
        if (ctx->f[0].d > z) return 0;
    }
    return 1;
}


/* ================================================================== set()
   The view-space planes from the frustum's corners, then the world ones after the corners went
   through the inverse camera matrix. Frame: +8 the eye (perspective), +24 the inverse camera
   matrix, +72 the eight corners (near TL, TR, BR, BL, far TL, TR, BR, BL; 12 bytes each). The
   calls' registers are the result (GM_CALLV), so the volatile registers end as the PowerPC
   code leaves them. */
#define F_TAN       0x802E8590u          /* tan */
#define F_MTX_INV   0x801C07A0u          /* PSMTXInverse */
#define F_MTX_COPY  0x801C0500u          /* PSMTXCopy */
#define F_MTX_VEC   0x801C1160u          /* PSMTXMultVec */
#define F_PLANE_SET 0x802385D0u          /* nw4r::math::PLANE::Set(p0, p1, p2) */
#define F_AABB_SET  0x80238690u          /* nw4r::math::AABB::Set(points, n) */
#define FR(n) (ctx->f[n].d)
#define FNEG(d, s_) (ctx->f[d].u = ctx->f[s_].u ^ 0x8000000000000000ull)
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
/* set(top, bottom, left, right, near, far, cameraMtx, orthographic) */
static void frustum_set(GM_CTX, gptr m, gptr cam, uint32_t ortho) {
    FN(0x8016DEC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    for (int i = 0; i < 6; i++) ctx->f[26 + i].u = ctx->f[1 + i].u;    /* f26 top, f27 bottom, f28 left, f29 right, f30 near, f31 far */
    NV_R(31, cam); NV_R(30, ortho); NV_R(29, m);
    gptr pt = f + 72, inv = f + 24, eye = f + 8;
#define P(i) (pt + 12 * (i))
#define PLANE(ra, off, a, b, c) GM_CALLV((ra), F_PLANE_SET, 4, m + (off), (a), (b), (c))
    GM_CALLV(0x8016DF38u, F_MTX_INV, 2, cam, inv);
    GM_CALLV(0x8016DF44u, F_MTX_COPY, 2, cam, m);
    FNEG(5, 30);
    cr_cmp_s(ctx, 0, (int32_t)ortho, 0);
    FNEG(4, 31);
    double nz = FR(5), fz = FR(4);
    SF(m + 112, nz); SF(m + 116, fz);
    SF(P(0), FR(28)); SF(P(0) + 4, FR(26)); SF(P(0) + 8, nz);
    SF(P(1), FR(29)); SF(P(1) + 4, FR(26)); SF(P(1) + 8, nz);
    SF(P(2), FR(29)); SF(P(2) + 4, FR(27)); SF(P(2) + 8, nz);
    SF(P(3), FR(28)); SF(P(3) + 4, FR(27)); SF(P(3) + 8, nz);
    for (int i = 4; i < 8; i++) SF(P(i) + 8, fz);
    if (ortho) {
        SF(P(4), FR(28)); SF(P(4) + 4, FR(26)); SF(P(5), FR(29)); SF(P(5) + 4, FR(26));
        SF(P(6), FR(29)); SF(P(6) + 4, FR(27)); SF(P(7), FR(28)); SF(P(7) + 4, FR(27));
        PLANE(0x8016DFD0u, 48, P(3), P(7), P(0));
        PLANE(0x8016DFE4u, 64, P(1), P(5), P(2));
        PLANE(0x8016DFF8u, 80, P(0), P(4), P(1));
        PLANE(0x8016E00Cu, 96, P(2), P(6), P(3));
    } else {
        double ratio = FB(6, frsp(FR(31) / FR(30)));
        double zero = FB(0, R2F(21348));
        SF(eye, zero);
        FB(3, frsp(ratio * FR(28)));
        SF(eye + 4, zero);
        FB(2, frsp(ratio * FR(26)));
        FB(1, frsp(ratio * FR(29)));
        SF(eye + 8, zero);
        FB(0, frsp(ratio * FR(27)));
        SF(P(4), FR(3)); SF(P(4) + 4, FR(2)); SF(P(5), FR(1)); SF(P(5) + 4, FR(2));
        SF(P(6), FR(1)); SF(P(6) + 4, FR(0)); SF(P(7), FR(3)); SF(P(7) + 4, FR(0));
        SF(m + 112, FR(5)); SF(m + 116, FR(4));
        PLANE(0x8016E0E8u, 48, eye, P(3), P(0));
        PLANE(0x8016E0FCu, 64, eye, P(1), P(2));
        PLANE(0x8016E110u, 80, eye, P(0), P(1));
        PLANE(0x8016E124u, 96, eye, P(2), P(3));
    }
    /* the corners (and the eye) to world space */
    NV_R(31, pt); NV_R(30, 0);
    for (int i = 0; i < 8; i++) {
        if (i) GM_LOOP();
        GM_CALLV(ortho ? 0x8016E024u : 0x8016E13Cu, F_MTX_VEC, 3, inv, ctx->r[31], ctx->r[31]);
        NV_R(30, ctx->r[30] + 1); NV_R(31, ctx->r[31] + 12);
        cr_cmp_s(ctx, 0, (int32_t)ctx->r[30], 8);
    }
    if (ortho) {
        PLANE(0x8016E048u, 144, P(3), P(7), P(0));
        PLANE(0x8016E05Cu, 160, P(1), P(5), P(2));
        PLANE(0x8016E070u, 208, P(0), P(4), P(1));
        PLANE(0x8016E084u, 224, P(2), P(6), P(3));
    } else {
        GM_CALLV(0x8016E15Cu, F_MTX_VEC, 3, inv, eye, eye);
        PLANE(0x8016E170u, 144, eye, P(3), P(0));
        PLANE(0x8016E184u, 160, eye, P(1), P(2));
        PLANE(0x8016E198u, 208, eye, P(0), P(1));
        PLANE(0x8016E1ACu, 224, eye, P(2), P(3));
    }
    /* the box around the corners, the near and far planes */
    GM_CALLV(0x8016E1BCu, F_AABB_SET, 3, m + 120, pt, 8);
    PLANE(0x8016E1D0u, 176, P(0), P(1), P(2));
    PLANE(0x8016E1E4u, 192, P(4), P(7), P(6));
#undef P
#undef PLANE
    ctx->r[0] = lr;
}
/* set(fovy, aspect, near, far, cameraMtx): a perspective frustum from the field of view */
static void frustum_set_fov(GM_CTX, gptr m, gptr cam) {
    FN(0x8016DE00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    double fovy = FR(1);
    FB(0, R2F(21352));
    FB(1, frsp(FR(0) * fovy));                                     /* fovy * 0.5 */
    FB(0, R2F(21360));
    ctx->f[31].u = ctx->f[4].u; ctx->f[30].u = ctx->f[3].u; ctx->f[29].u = ctx->f[2].u;   /* far, near, aspect */
    FB(2, R2F(21356));
    NV_R(31, cam);
    FB(1, frsp(FR(2) * FR(1)));                                    /* to a nw4r angle index */
    NV_R(30, m);
    FB(1, frsp(FR(0) * FR(1)));                                    /* ... to radians */
    GM_CALLV(0x8016DE5Cu, F_TAN, 0);
    ctx->f[0].d = frsp(FR(1));
    ctx->r[3] = m;
    ctx->f[5].u = ctx->f[30].u;
    ctx->r[4] = cam;
    ctx->f[6].u = ctx->f[31].u;
    ctx->r[5] = 0;
    FB(1, frsp(FR(0) * FR(30)));                                   /* top = tan * near */
    FB(4, frsp(FR(1) * FR(29)));                                   /* right = top * aspect */
    FNEG(2, 1); FNEG(3, 4);                                        /* bottom, left */
    NCALL(0x8016DE88u, frustum_set(GM_PASS, m, cam, 0));
    ctx->r[0] = lr;
}

/* ================================================================== hle entry points
   Both reached by the test runs: on. */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
E(fn_8016E230) { GM_RET(frustum_sphere(GM_PASS, A(0), A(1))); }                               /* mFrustum_c::intersectSphere */
E(fn_8016E3A0) { GM_RET(frustum_aabb(GM_PASS, A(0), A(1))); }                                 /* ::intersectAABB */
GM_HLE_VOID(fn_8016DE00, A(0), 240) { frustum_set_fov(GM_PASS, A(0), A(1)); }                                       /* ::set(fovy, aspect, near, far, mtx) */
GM_HLE_VOID(fn_8016DEC0, A(0), 240) { frustum_set(GM_PASS, A(0), A(1), A(2)); }                              /* ::set(top ... far, mtx, ortho) */
