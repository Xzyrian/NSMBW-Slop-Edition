/* gm_d_cc.c - dCc_c (old name ActivePhysics), the actor collision checker: the list every
 * collider is entered into, the per-frame check of every pair (execute / checkCollision: kind and
 * attack masks, the shape's hit check, the result flags, the callbacks), the box / loop / circle
 * hit checks and the collider's edges. Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_cc.cpp) and checked against the recompiled
 * USA rev 2 code (0x8008C200-0x8008CF74). Not here (still recompiled): the trapezoid hit checks
 * (_hitCheckDaikeiUD / LR and their _R / line checks).
 * Every float step is rounded to single as the recompiled code rounds it; the non-volatile
 * registers are mirrored around nested calls (gm_nv.h) and calls carry the PowerPC return
 * address (GM_CALLR).
 *
 * dCc_c: +0 vtable, +4 owner (dActor_c: +172 pos.x, +176 pos.y), +8 friend actor, +16 next,
 * +20 prev, +28 sCcDatNewF (36 bytes: +28 offset x / y, +36 size x / y, +44 kind, +45 attack,
 * +48 vs kind, +52 vs damage, +56 status (u16), +60 callback), +80 offsets x [8], +112 offsets
 * y [8], +144 hit position, +152 collided-with, +154 attacks sent, +156 attacks received,
 * +158 shape, +159 ami line, +160 layer, +161 info, +162 linked. */
#include "gm.h"
#include "gm_nv.h"
#include <math.h>

#define SDA 0x8042F680u
#define ENTRY_N     (SDA - 22560)        /* dCc_c::mEntryN / mEntryB */
#define ENTRY_B     (SDA - 22556)
#define LOOP_TYPE   (SDA - 21624)        /* dScStage_c::m_loopType */
#define BG_P        (SDA - 22704)        /* dBg_c::m_bg_p (+0x8FEA0: mLoopOffset) */
#define VT_CC       0x80310DF0u
#define HIT_CHECK   0x80310DB0u          /* dCc_c::_hitCheck[4][4] */
#define HIT_CHECK_DEFAULT 0x802F00E8u    /* (reset's table: normal, loop, loop) */
#define F_DELETE    0x802B9280u
#define F_SQRT      0x802BE470u          /* EGG::Math<float>::sqrt */
#define F_ATAN2S    0x801611C0u          /* cM::atan2s */
#define F_COS_IDX   0x80237C40u
#define F_SIN_IDX   0x80237BD0u
#define F_LOOP_POS_X 0x80101AA0u         /* dScStage_c::getLoopPosX */
#define F_NORMALISE 0x802BE640u          /* EGG::Vector2f::normalise */

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f
static inline double fl(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }

/* the collider's centre and edges (leaves: getCenterPosX / Y, getLeft / Right / Top / UnderPos) */
static inline uint32_t slw1(uint32_t k) { k &= 63; return k > 31 ? 0 : 1u << k; }   /* (1 << k as slw does it) */
static inline double cx(GM_CTX, gptr c) { return frsp(LF(c + 28) + LF(gm_u32(c + 4) + 172)); }
static inline double cy(GM_CTX, gptr c) { return frsp(LF(c + 32) + LF(gm_u32(c + 4) + 176)); }

/* ================================================================== the list */
static void cc_clear(GM_CTX, gptr c) {
    double z = fl(ctx, 0, R2F(28800));
    gm_set_u16(c + 152, 0); gm_set_u16(c + 154, 0); gm_set_u16(c + 156, 0);
    gm_set_u8(c + 161, gm_u8(c + 161) & 0xFD);                            /* (CC_NO_HIT off) */
    for (int i = 0; i < 8; i++) { SF(c + 80 + 4 * i, z); SF(c + 112 + 4 * i, z); }
}
static void cc_release(GM_CTX, gptr c) {
    if (!gm_u8(c + 162)) return;
    gptr n = gm_u32(c + 16), p;
    if (n) gm_set_u32(n + 20, gm_u32(c + 20)); else gm_set_u32(ENTRY_B, gm_u32(c + 20));
    p = gm_u32(c + 20);
    if (p) gm_set_u32(p + 16, gm_u32(c + 16)); else gm_set_u32(ENTRY_N, gm_u32(c + 16));
    gm_set_u32(c + 16, 0); gm_set_u32(c + 20, 0); gm_set_u8(c + 162, 0);
}
static void cc_set(GM_CTX, gptr c, gptr actor, gptr d) {
    gm_set_u32(c + 4, actor);
    for (int i = 0; i < 4; i++) { double v = LF(d + 4 * i); SF(c + 28 + 4 * i, v); }
    gm_set_u8(c + 44, gm_u8(d + 16)); gm_set_u8(c + 45, gm_u8(d + 17));
    gm_set_u32(c + 48, gm_u32(d + 20)); gm_set_u32(c + 52, gm_u32(d + 24));
    gm_set_u16(c + 56, gm_u16(d + 28)); gm_set_u32(c + 60, gm_u32(d + 32));
    gm_set_u8(c + 161, 0);
}

/* ================================================================== hit checks */
/* _hitCheckSquare(c1, c2, &pos1, &pos2): the boxes overlap; the overlap's half goes into both
   colliders' offsets (a leaf) */
static uint32_t hit_square(GM_CTX, gptr c1, gptr c2, gptr p1, gptr p2) {
    double dx = frsp(LF(p1) - LF(p2)), sx = frsp(LF(c1 + 36) + LF(c2 + 36));
    double dy = frsp(LF(p1 + 4) - LF(p2 + 4)), sy = frsp(LF(c1 + 40) + LF(c2 + 40));
    if (!(frsp(fabs(dx)) < sx)) return 0;
    if (!(frsp(fabs(dy)) < sy)) return 0;
    SF(c1 + 144, LF(p1)); SF(c1 + 148, LF(p1 + 4));
    SF(c2 + 144, LF(p2)); SF(c2 + 148, LF(p2 + 4));
    if (((gm_u16(c1 + 56) & 1) || (gm_u16(c2 + 56) & 1)) && gm_u8(c1 + 44) != 8 && gm_u8(c2 + 44) != 8)
        return 1;                                                          /* (NO_REVISION, not the goal pole) */
    double z = R2F(28800), half = R2F(28792);
    double ox = frsp(frsp(sx - frsp(fabs(dx))) * half);
    if (dx < z) ox = -ox;
    double oy = frsp(frsp(sy - frsp(fabs(dy))) * half);
    if (dy < z) oy = -oy;
    SF(c1 + 80 + 4 * gm_u8(c2 + 44), ox);
    SF(c1 + 112 + 4 * gm_u8(c2 + 44), oy);
    SF(c2 + 80 + 4 * gm_u8(c1 + 44), -ox);
    SF(c2 + 112 + 4 * gm_u8(c1 + 44), -oy);
    return 1;
}
/* the two centres into the stack as the compiler leaves them: (x1, y1) at s1, (x2, y2) at s2,
   with f31 holding y across the calls; returns nothing, fills the slots */
static uint32_t hit_normal(GM_CTX, gptr c1, gptr c2) {
    FN(0x8008CBA0); GM_NV_KEEP;
    NV_R(31, c2); NV_R(30, c1);
    double y1 = cy(GM_PASS, c1); ctx->f[31].d = y1;
    double x1 = cx(GM_PASS, c1);
    SF(f + 32, x1); SF(f + 36, y1);
    double y2 = cy(GM_PASS, c2); ctx->f[31].d = y2;
    double x2 = cx(GM_PASS, c2);
    SF(f + 24, x2); SF(f + 28, y2);
    SF(f + 16, LF(f + 32)); SF(f + 20, LF(f + 36));
    SF(f + 8, x2); SF(f + 12, y2);
    return hit_square(GM_PASS, c1, c2, f + 16, f + 8);
}
static uint32_t hit_loop(GM_CTX, gptr c1, gptr c2) {
    FN(0x8008CC50); GM_NV_KEEP;
    NV_R(31, c2); NV_R(30, c1);
    double y1 = cy(GM_PASS, c1); ctx->f[31].d = y1;
    fl(ctx, 1, cx(GM_PASS, c1));
    GM_CALLR(0x8008CC88u, F_LOOP_POS_X, 0);
    SF(f + 48, ctx->f[1].d); SF(f + 52, y1);
    double y2 = cy(GM_PASS, c2); ctx->f[31].d = y2;
    fl(ctx, 1, cx(GM_PASS, c2));
    GM_CALLR(0x8008CCA8u, F_LOOP_POS_X, 0);
    double x2 = ctx->f[1].d;
    SF(f + 40, x2); SF(f + 44, y2);
    SF(f + 32, LF(f + 48)); SF(f + 36, LF(f + 52));
    SF(f + 24, x2); SF(f + 28, y2);
    if (hit_square(GM_PASS, c1, c2, f + 32, f + 24)) return 1;
    double a = LF(f + 48), b = LF(f + 40), off = LF(gm_u32(BG_P) + 0x8FEA0u);
    if (a < b) SF(f + 48, frsp(a + off)); else SF(f + 40, frsp(b + off));
    SF(f + 16, LF(f + 48)); SF(f + 20, LF(f + 52));
    SF(f + 8, LF(f + 40)); SF(f + 12, LF(f + 44));
    return hit_square(GM_PASS, c1, c2, f + 16, f + 8);
}
/* _hitCheckCircle: the distance between the centres against the mean of the summed sizes; the
   push-out goes along the angle (cM::atan2s, then nw4r's cos / sin of it) */
static uint32_t hit_circle(GM_CTX, gptr c1, gptr c2) {
    FN(0x8008CDA0); GM_NV_KEEP;
    NV_R(30, c2); NV_R(29, c1);
    double y1 = cy(GM_PASS, c1); ctx->f[31].d = y1;
    double x1 = cx(GM_PASS, c1);
    SF(f + 32, x1); SF(f + 36, y1);
    double y2 = cy(GM_PASS, c2); ctx->f[31].d = y2;
    double x2 = cx(GM_PASS, c2);
    double dy = frsp(y2 - LF(f + 36)), dx = frsp(x2 - LF(f + 32));
    double ssx = frsp(LF(c1 + 36) + LF(c2 + 36)), ssy = frsp(LF(c1 + 40) + LF(c2 + 40));
    double half = R2F(28792);
    SF(f + 24, x2);
    double sum = frsp(ssx + ssy);
    SF(f + 28, y2);
    double len2 = frsp(frsp(dx * dx) + frsp(dy * dy));
    double rad = frsp(sum * half);
    fl(ctx, 31, rad);
    SF(f + 16, dx); SF(f + 20, dy);
    fl(ctx, 1, len2);
    GM_CALLR(0x8008CE58u, F_SQRT, 0);
    if (!(ctx->f[1].d < rad || ctx->f[1].d == rad)) return 0;
    double ddx = LF(f + 16), ddy = LF(f + 20);
    fl(ctx, 1, frsp(frsp(ddx * ddx) + frsp(ddy * ddy)));
    GM_CALLR(0x8008CE7Cu, F_SQRT, 0);
    double dist = fl(ctx, 31, frsp(rad - ctx->f[1].d));
    fl(ctx, 1, LF(f + 20));
    ctx->f[2].d = frsp(fabs(LF(f + 16)));
    uint32_t ang = GM_CALLR(0x8008CE94u, F_ATAN2S, 0);
    gm_set_u16(f + 10, (uint16_t)ang);
    NV_R(31, ang);
    psq_l(ctx, base, 1, f + 10, 1, 3);
    double k = R2F(28796);
    fl(ctx, 1, frsp(k * ctx->f[1].d));
    GM_CALLR(0x8008CEB0u, F_COS_IDX, 0);
    gm_set_u16(f + 8, (uint16_t)ang);
    double ox = fl(ctx, 30, frsp(dist * ctx->f[1].d));
    psq_l(ctx, base, 1, f + 8, 1, 3);
    fl(ctx, 1, frsp(k * ctx->f[1].d));
    GM_CALLR(0x8008CECCu, F_SIN_IDX, 0);
    double oy = frsp(-dist * ctx->f[1].d);
    SF(c1 + 80 + 4 * gm_u8(c2 + 44), ox);
    SF(c1 + 112 + 4 * gm_u8(c2 + 44), oy);
    SF(c1 + 144, LF(f + 32)); SF(c1 + 148, LF(f + 36));
    SF(c2 + 80 + 4 * gm_u8(c1 + 44), -ox);
    SF(c2 + 112 + 4 * gm_u8(c1 + 44), -oy);
    SF(c2 + 144, LF(f + 24)); SF(c2 + 148, LF(f + 28));
    return 1;
}

/* the int-to-float the compiler does: the int with its sign flipped, under 0x43300000, as a
   double on the stack (at slot) minus the magic double at r2 - 28776 */
static double i2f(GM_CTX, gptr slot, uint32_t v) {
    gm_set_u32(slot + 4, v ^ 0x80000000u);
    union { uint64_t u; double d; } a, m;
    a.u = ld64(base, slot); m.u = ld64(base, ctx->r[2] - 28776);
    return frsp(a.d - m.d);
}
/* _hitCheckBoxCircle: the circle's centre against the box's nearer edges (pushed apart along x
   or y), else against the nearer corner (EGG::Vector2f::normalise) */
static uint32_t hit_box_circle(GM_CTX, gptr c1, gptr c2) {
    FN(0x8008CF80); GM_NV_KEEP;
    gm_set_u32(f + 56, 0x43300000u); gm_set_u32(f + 64, 0x43300000u);
    gptr box, cir;
    if (gm_u8(c1 + 158) == 0) { box = c1; cir = c2; } else { box = c2; cir = c1; }
    NV_R(31, box); NV_R(30, cir);
    double v = cy(GM_PASS, cir); ctx->f[30].d = v;
    SF(f + 48, cx(GM_PASS, cir)); SF(f + 52, v);
    v = cy(GM_PASS, box); ctx->f[30].d = v;
    SF(f + 40, cx(GM_PASS, box));
    double rad = fl(ctx, 31, LF(cir + 36));
    SF(f + 44, v);
    v = cx(GM_PASS, cir); ctx->f[30].d = v;
    uint32_t sx = cx(GM_PASS, box) < v ? 0 : 1;
    NV_R(29, sx);
    v = cy(GM_PASS, cir); ctx->f[30].d = v;
    uint32_t sy = cy(GM_PASS, box) < v ? 0 : 1;
    NV_R(28, sy);
    SF(f + 32, frsp(LF(box + 36) + cx(GM_PASS, box)));
    SF(f + 36, frsp(cx(GM_PASS, box) - LF(box + 36)));
    SF(f + 24, frsp(LF(box + 40) + cy(GM_PASS, box)));
    double bot = frsp(cy(GM_PASS, box) - LF(box + 40));
    SF(f + 28, bot);
    double two = R2F(28784), one = R2F(28788), half = R2F(28792), zero = R2F(28800);
    uint32_t ck = gm_u8(cir + 44), bk = gm_u8(box + 44);
    double py = LF(f + 52), px = LF(f + 48);
    if (bot < py && py < LF(f + 24)) {                                    /* within the box's y range */
        double sc = frsp(one - frsp(two * i2f(GM_PASS, f + 56, sx)));
        double d = frsp(sc * frsp(px - LF(f + 32 + 4 * sx)));
        if (d < rad) {
            double sc2 = frsp(one - frsp(two * i2f(GM_PASS, f + 64, sx)));
            double o = frsp(frsp(sc2 * frsp(rad - d)) * half);
            SF(cir + 80 + 4 * ck, o); SF(cir + 112 + 4 * ck, zero);
            SF(cir + 144, px); SF(cir + 148, py);
            SF(box + 80 + 4 * ck, -LF(cir + 80 + 4 * ck)); SF(box + 112 + 4 * ck, zero);
            SF(box + 144, LF(f + 40)); SF(box + 148, LF(f + 44));
            return 1;
        }
    }
    if (LF(f + 36) < px && px < LF(f + 32)) {                             /* within its x range */
        double sc = frsp(one - frsp(two * i2f(GM_PASS, f + 56, sy)));
        double d = frsp(sc * frsp(py - LF(f + 24 + 4 * sy)));
        if (d < rad) {
            double sc2 = frsp(one - frsp(two * i2f(GM_PASS, f + 64, sy)));
            double o = frsp(frsp(sc2 * frsp(rad - d)) * half);
            SF(cir + 80 + 4 * ck, zero); SF(cir + 112 + 4 * ck, o);
            SF(cir + 144, px); SF(cir + 148, py);
            SF(box + 80 + 4 * ck, zero); SF(box + 112 + 4 * ck, -LF(cir + 112 + 4 * ck));
            SF(box + 144, LF(f + 40)); SF(box + 148, LF(f + 44));
            return 1;
        }
    }
    double ey = LF(f + 24 + 4 * sy), ex = LF(f + 32 + 4 * sx);             /* the nearer corner */
    SF(f + 16, ex); SF(f + 20, ey);
    SF(f + 8, frsp(px - ex)); SF(f + 12, frsp(py - ey));
    GM_CALLR(0x8008D2E8u, F_NORMALISE, 1, f + 8);
    double len = ctx->f[1].d;
    if (!(len < rad)) return 0;
    double o = frsp(frsp(rad - len) * half);
    SF(cir + 80 + 4 * ck, frsp(LF(f + 8) * o));
    SF(cir + 112 + 4 * ck, frsp(LF(f + 12) * o));
    SF(cir + 144, LF(f + 48)); SF(cir + 148, LF(f + 52));
    SF(box + 80 + 4 * bk, -LF(cir + 80 + 4 * ck));
    SF(box + 112 + 4 * bk, -LF(cir + 112 + 4 * ck));
    SF(box + 144, LF(f + 40)); SF(box + 148, LF(f + 44));
    return 1;
}

/* ================================================================== checkCollision / execute */
static uint32_t check_collision(GM_CTX, gptr c1, gptr c2, uint32_t active) {
    FN(0x8008C6E0); GM_NV_KEEP;
    NV_R(23, c1); NV_R(24, c2); NV_R(25, active);
    if (c2 == c1) return 0;
    gptr o1 = gm_u32(c1 + 4), o2 = gm_u32(c2 + 4);
    if (o2 == o1) return 0;
    if (o2 == gm_u32(c1 + 8) || o1 == gm_u32(c2 + 8)) return 0;
    if ((gm_u8(c1 + 161) & 2) || (gm_u8(c2 + 161) & 2)) return 0;
    if (!(gm_u8(c1 + 159) & gm_u8(c2 + 159))) return 0;
    if (gm_u8(c1 + 160) != gm_u8(c2 + 160)) return 0;
    /* the two sCcDatNewF copies: c1's at f+44, c2's at f+8 */
    for (int i = 0; i < 9; i++) { gm_set_u32(f + 44 + 4 * i, gm_u32(c1 + 28 + 4 * i)); gm_set_u32(f + 8 + 4 * i, gm_u32(c2 + 28 + 4 * i)); }
    uint32_t vs1 = gm_u32(f + 64), vs2 = gm_u32(f + 28), vd1 = gm_u32(f + 68), vd2 = gm_u32(f + 32);
    uint32_t k2 = gm_u8(f + 24), k1 = gm_u8(f + 60);
    uint32_t m2 = slw1(k2), m1 = slw1(k1);
    uint32_t r19 = vs1 & m2;
    NV_R(19, r19); NV_R(20, gm_u32(c1 + 28)); NV_R(21, gm_u32(c1 + 32)); NV_R(22, gm_u32(c1 + 36));
    NV_R(26, vs1); NV_R(27, gm_u32(c1 + 40)); NV_R(28, m1); NV_R(29, m2); NV_R(30, vd1); NV_R(31, vd2);
    if (r19 && (vs2 & m1)) {
        uint32_t a1 = gm_u8(f + 61), a2 = gm_u8(f + 25);
        uint32_t am1 = slw1(a1), am2 = slw1(a2);
        NV_R(27, am1); NV_R(26, am2);
        if ((r19 & 2) && !(am2 & vd1)) return 0;
        if ((vs2 & m1 & 2) && !(am1 & vd2)) return 0;
        uint32_t fn = gm_u32(HIT_CHECK + gm_u8(c2 + 158) * 16 + gm_u8(c1 + 158) * 4);
        if (GM_CALLR(0x8008C8B4u, fn, 2, c1, c2)) {
            if (!active) return 1;
            uint32_t st2 = gm_u16(f + 36) & 4;
            if (!st2) {
                gm_set_u16(c1 + 152, gm_u16(c1 + 152) | (m2 & 0xFFFF));
                if (vd1 & am2) gm_set_u16(c1 + 156, gm_u16(c1 + 156) | ((vd1 & am2) & 0xFFFF));
                if (am1 & vd2) gm_set_u16(c1 + 154, gm_u16(c1 + 154) | ((am1 & vd2) & 0xFFFF));
            }
            uint32_t st1 = gm_u16(f + 72) & 4;
            NV_R(29, st1);
            if (!st1) {
                gm_set_u16(c2 + 152, gm_u16(c2 + 152) | (m1 & 0xFFFF));
                if (vd1 & am2) gm_set_u16(c2 + 154, gm_u16(c2 + 154) | ((vd1 & am2) & 0xFFFF));
                if (am1 & vd2) gm_set_u16(c2 + 156, gm_u16(c2 + 156) | ((am1 & vd2) & 0xFFFF));
            }
            gptr cb;
            if (!st2 && (cb = gm_u32(f + 76))) GM_CALLR(0x8008C988u, cb, 2, c1, c2);
            if (!st1 && (cb = gm_u32(f + 40))) GM_CALLR(0x8008C9ACu, cb, 2, c2, c1);
        }
    }
    return gm_u16(c1 + 152) != 0;
}
static void cc_execute(GM_CTX) {
    FN(0x8008C9E0); GM_NV_KEEP;
    for (gptr c1 = gm_u32(ENTRY_N); c1; c1 = gm_u32(c1 + 16)) {
        GM_LOOP();
        NV_R(31, c1);
        for (gptr c2 = gm_u32(c1 + 16); c2; c2 = gm_u32(c2 + 16)) {
            GM_LOOP();
            NV_R(30, c2);
            NCALL(0x8008CA14u, check_collision(GM_PASS, c1, c2, 1));
        }
    }
}

/* ================================================================== hle entry points
   On (19): reached by the test runs, run inside them (checkCollision from execute, _hitCheckSquare)
   or the same code as a reached one but for an offset (getLeftPos / getRightPos). Written but off
   (not reached): isHit, isHitAtDmg, isInside, _hitCheckCircle, _hitCheckBoxCircle. */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
E(__ct__13ActivePhysicsFv) {                                                                   /* dCc_c::dCc_c */
    FN(0x8008C200); GM_NV_KEEP;
    gptr c = A(0);
    NV_R(31, c);
    gm_set_u32(c, VT_CC); gm_set_u32(c + 16, 0); gm_set_u32(c + 20, 0); gm_set_u8(c + 162, 0);
    gm_set_u32(c + 8, 0); gm_set_u8(c + 159, 1); gm_set_u8(c + 160, 0);
    cc_clear(GM_PASS, c);                                                  /* (a leaf) */
    GM_RET(c);
}
E(__dt__13ActivePhysicsFv) {                                                                   /* ::~dCc_c */
    FN(0x8008C260); GM_NV_KEEP;
    gptr c = A(0); int32_t flags = (int32_t)A(1);
    NV_R(31, flags); NV_R(30, c);
    if (c) {
        gm_set_u32(c, VT_CC);
        cc_release(GM_PASS, c);
        if (flags > 0) GM_CALLR(0x8008C2A4u, F_DELETE, 1, c);
    }
    GM_RET(c);
}
E(clear__13ActivePhysicsFv) { cc_clear(GM_PASS, A(0)); }                                       /* ::clear */
E(ActivePhysics_AddToList) {                                                                   /* ::entry */
    gptr c = A(0);
    if (gm_u8(c + 162)) return;
    gptr n = gm_u32(ENTRY_N);
    gm_set_u32(c + 16, n);
    gm_set_u32(ENTRY_N, c);
    if (!n) { gm_set_u32(c + 20, gm_u32(ENTRY_B)); gm_set_u32(ENTRY_B, c); }
    else { gm_set_u32(c + 20, gm_u32(n + 20)); gm_set_u32(n + 20, c); }
    gm_set_u8(c + 162, 1);
}
E(removeFromList__13ActivePhysicsFv) { cc_release(GM_PASS, A(0)); }                            /* ::release */
E(ActivePhysics_InitWithStruct) { cc_set(GM_PASS, A(0), A(1), A(2)); }                         /* ::set(actor, data) */
E(fn_8008C440) {                                                                               /* ::set(actor, data, ami line) */
    FN(0x8008C440); GM_NV_KEEP;
    gptr c = A(0); uint32_t ami = A(3);
    NV_R(31, ami); NV_R(30, c);
    cc_set(GM_PASS, c, A(1), A(2));
    gm_set_u8(c + 159, (uint8_t)ami);
}
E(fn_8008C480) {                                                                               /* ::reset */
    gm_set_u32(ENTRY_N, 0); gm_set_u32(ENTRY_B, 0);
    gm_set_u32(HIT_CHECK, gm_u32(HIT_CHECK_DEFAULT + (gm_u32(LOOP_TYPE) << 2)));
}
E(fn_8008C4B0) { GM_RET(gm_u16(A(0) + 152) & A(1)); }                                          /* ::isHit */
E(fn_8008C4C0) { GM_RET(gm_u16(A(0) + 156) & A(1)); }                                          /* ::isHitAtDmg */
E(fn_8008C4D0) { gptr c = A(0); fl(ctx, 1, frsp(LF(c + 40) + cy(GM_PASS, c))); }              /* ::getTopPos */
E(bottom__13ActivePhysicsFv) { gptr c = A(0); fl(ctx, 1, frsp(cy(GM_PASS, c) - LF(c + 40))); } /* ::getUnderPos */
E(fn_8008C510) { fl(ctx, 1, cy(GM_PASS, A(0))); }                                              /* ::getCenterPosY */
E(fn_8008C530) { gptr c = A(0); fl(ctx, 1, frsp(LF(c + 36) + cx(GM_PASS, c))); }              /* ::getRightPos */
E(fn_8008C550) { gptr c = A(0); fl(ctx, 1, frsp(cx(GM_PASS, c) - LF(c + 36))); }              /* ::getLeftPos */
E(fn_8008C570) { fl(ctx, 1, cx(GM_PASS, A(0))); }                                              /* ::getCenterPosX */
E(fn_8008C590) {                                                                               /* ::isInside(other) */
    FN(0x8008C590); GM_NV_KEEP;
    gptr c = A(0), o = A(1);
    NV_R(31, o); NV_R(30, c);
    if (gm_u8(c + 158) == 1) {                                             /* (a circle: always inside) */
        double y1 = cy(GM_PASS, c); ctx->f[31].d = y1;
        double x1 = cx(GM_PASS, c);
        SF(f + 24, x1); SF(f + 28, y1);
        double y2 = cy(GM_PASS, o); ctx->f[31].d = y2;
        double x2 = cx(GM_PASS, o);
        double dy = frsp(LF(f + 28) - y2), dx = frsp(LF(f + 24) - x2);
        SF(f + 16, x2); SF(f + 20, y2); SF(f + 8, dx); SF(f + 12, dy);
        fl(ctx, 1, frsp(frsp(dx * dx) + frsp(dy * dy)));
        GM_CALLR(0x8008C624u, F_SQRT, 0);
        GM_RET(1); return;
    }
    double x2 = cx(GM_PASS, o); ctx->f[31].d = x2;
    double d = frsp(cx(GM_PASS, c) - x2), s = frsp(LF(c + 36) - LF(o + 36));
    if (frsp(fabs(d)) > frsp(fabs(s))) { GM_RET(0); return; }
    double y2 = cy(GM_PASS, o); ctx->f[31].d = y2;
    d = frsp(cy(GM_PASS, c) - y2); s = frsp(LF(c + 40) - LF(o + 40));
    GM_RET(!(frsp(fabs(d)) > frsp(fabs(s))));
}
E(fn_8008C6E0) { GM_LR_KEEP; GM_RET(check_collision(GM_PASS, A(0), A(1), A(2))); }             /* ::checkCollision */
E(fn_8008C9E0) { GM_LR_KEEP; cc_execute(GM_PASS); }                                            /* ::execute */
E(fn_8008CA50) { GM_RET(hit_square(GM_PASS, A(0), A(1), A(2), A(3))); }                        /* ::_hitCheckSquare */
E(fn_8008CBA0) { GM_RET(hit_normal(GM_PASS, A(0), A(1))); }                                    /* ::_hitCheckNormal */
E(fn_8008CC50) { GM_RET(hit_loop(GM_PASS, A(0), A(1))); }                                      /* ::_hitCheckLoop */
E(fn_8008CDA0) { GM_RET(hit_circle(GM_PASS, A(0), A(1))); }                                    /* ::_hitCheckCircle */
E(fn_8008CF80) { GM_RET(hit_box_circle(GM_PASS, A(0), A(1))); }                                /* ::_hitCheckBoxCircle */
