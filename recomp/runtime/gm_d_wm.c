/* gm_d_wm.c - the world map's actor base dWmActor_c and the world map's CSV data getters
 * (dCsvData_c). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_wm_actor.cpp, d_wm_csvdata.cpp) and checked
 * against the recompiled USA rev 2 code (0x800F2710-0x800F2A58, 0x800F56B0-0x800F5A88). Written
 * register-exact (R(n)): the calls with their real return addresses, the callees' volatile
 * registers left as they leave them.
 *
 * dWmActor_c (a dActor_c): +8 the profile (u16), +172 the position, +296 the clip sphere's centre,
 * +308 its radius. preExecute / preDraw: the dBase_c ones, then not while the game is stopped
 * (preExecute) or outside the view (preDraw: a radius > 0 sphere against dWCamera_c's view clip),
 * and on the world select (dInfo_c, +916) only the course select's sequence manager, the island
 * and the director (profiles 0x26D / 0x29A / 0x298) run.
 *
 * dCsvData_c: per world (448 bytes from +0; the sub-tables for the two kinds, r4 == 0 or not) and
 * per course point (24 bytes from +0x10000 + 20504). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define LF(a) ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

#define SDA(o) (R(13) - (o))
#define SDA_INFO     22276        /* dInfo_c::m_instance (+916 mIsWorldSelect) */
#define SDA_WCAMERA  21500        /* dWCamera_c::m_instance (+1272 the view clip) */
#define R2_ZERO      24908        /* (r2 - 24908: 0.0f) */
#define F_BASE_PRE_CREATE   0x8006C870u
#define F_BASE_POST_CREATE  0x8006C8A0u
#define F_BASE_PRE_DELETE   0x8006C8B0u
#define F_BASE_POST_DELETE  0x8006C8E0u
#define F_BASE_PRE_EXECUTE  0x8006C8F0u
#define F_BASE_POST_EXECUTE 0x8006C980u
#define F_BASE_PRE_DRAW     0x8006C9F0u
#define F_BASE_POST_DRAW    0x8006CA40u
#define F_BASE_DRAW_8006CA80 0x8006CA80u
#define F_CREATE_CHILD      0x8006CBA0u  /* CreateChildObjects(...) */
#define F_ACTOR_CT          0x8006C6D0u
#define F_ACTOR_DT          0x8006C7F0u
#define F_FREE_GAME_HEAP1   0x80162920u
#define F_IS_GAME_STOP      0x800B3B50u  /* dGameCom::isGameStop(flags) */
#define F_CHECK_CLIP        0x800FE040u  /* dWmViewClip_c::CheckClipSphere */
#define WM_VTABLE           0x8031BC60u

/* ================================================================== dWmActor_c */
static void wa_ctor(GM_CTX) {
    GM_FN(0x800F2710); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x800F2728u, F_ACTOR_CT, 0);
    R(3) = WM_VTABLE; R(5) = 0x80370000u;
    gm_set_u32(R(31) + 96, R(3));
    FB(0, LF(R(2) - 24912));
    R(3) = R(31);
    R(5) = 0x80370000u + 32200u; R(4) = gm_u32(R(5));                         /* (lwzu) */
    R(0) = gm_u32(R(5) + 4); gm_set_u32(R(31) + 300, R(0));
    gm_set_u32(R(31) + 296, R(4));
    R(0) = gm_u32(R(5) + 8); gm_set_u32(R(31) + 304, R(0));
    SF(R(31) + 308, ctx->f[0].d);
    R(0) = lr;
}
static void wa_dtor(GM_CTX) {
    GM_FN(0x800F2770); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(4) = 0;
        GM_CALLV(0x800F279Cu, F_ACTOR_DT, 0);
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x800F27ACu, F_FREE_GAME_HEAP1, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
/* preCreate / preDelete: the dBase_c one, as a bool (neg / or / srwi) */
#define WA_BOOL_OF(name, addr, fn) static void name(GM_CTX) { \
    GM_FN(addr); GM_NV_KEEP; GM_LR_KEEP; \
    uint32_t lr = ctx->lr; \
    GM_CALLV(addr##u + 0x10, fn, 0); \
    R(0) = (uint32_t)-(int32_t)R(3); R(0) |= R(3); \
    R(3) = R(0) >> 31; \
    R(0) = lr; }
WA_BOOL_OF(wa_pre_create, 0x800F27D0, F_BASE_PRE_CREATE)   /* FNADDR */
WA_BOOL_OF(wa_pre_delete, 0x800F2810, F_BASE_PRE_DELETE)   /* FNADDR */
/* the world select: only these run */
static int wa_select_ok(GM_CTX) {
    R(3) = gm_u32(SDA(SDA_INFO));
    R(0) = gm_u8(R(3) + 916);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) return 1;
    R(0) = gm_u16(R(31) + 8);
    if (cmpu(ctx, R(0), 0x26D) == 0) return 1;
    if (cmpu(ctx, R(0), 0x29A) == 0) return 1;
    if (cmpu(ctx, R(0), 0x298) == 0) return 1;
    return 0;
}
static void wa_pre_execute(GM_CTX) {
    GM_FN(0x800F2850); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x800F2868u, F_BASE_PRE_EXECUTE, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
    R(3) = (uint32_t)-1;
    GM_CALLV(0x800F2880u, F_IS_GAME_STOP, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) { R(3) = 0; goto out; }
    if (!wa_select_ok(GM_PASS)) { R(3) = 0; goto out; }
    FB(2, LF(R(31) + 172));
    R(3) = 1;
    FB(1, LF(R(31) + 176));
    FB(0, LF(R(31) + 180));
    SF(R(31) + 296, ctx->f[2].d); SF(R(31) + 300, ctx->f[1].d); SF(R(31) + 304, ctx->f[0].d);
out:
    R(0) = lr;
}
static void wa_pre_draw(GM_CTX) {
    GM_FN(0x800F2910); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x800F2928u, F_BASE_PRE_DRAW, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
    FB(0, LF(R(31) + 308));
    FB(3, LF(R(31) + 172));
    ctx->f[4].u = ctx->f[0].u & ~0x8000000000000000ull;                     /* fabs (ps0 only) */
    FB(2, LF(R(31) + 176));
    FB(1, LF(R(31) + 180));
    FB(0, LF(R(2) - R2_ZERO));
    ctx->f[4].d = frsp(ctx->f[4].d);
    SF(R(31) + 296, ctx->f[3].d); SF(R(31) + 300, ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    SF(R(31) + 304, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));                    /* (cror: <= 0) */
    R(0) = ctx->cr;
    R(0) = rotl32(R(0), 3) & 1;
    CR0(ctx, R(0));
    if (!CR_BIT(ctx, 2)) {                                                   /* |r| <= 0: not tested */
    } else {
        R(3) = gm_u32(SDA(SDA_WCAMERA));
        R(4) = R(31) + 296;
        R(3) = R(3) + 1272;
        GM_CALLV(0x800F2984u, F_CHECK_CLIP, 0);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
    }
    R(3) = wa_select_ok(GM_PASS) ? 1 : 0;
out:
    R(0) = lr;
}

/* ================================================================== dCsvData_c */
#define W(i) (R(3) + (uint32_t)((int32_t)R(i) * 448))
static inline void w0(GM_CTX, int i) { R(0) = (uint32_t)((int32_t)R(i) * 448); R(3) = R(3) + R(0); }
static inline void p0(GM_CTX) { R(0) = (uint32_t)((int32_t)R(4) * 24); R(3) = R(3) + 0x10000u; R(3) = R(3) + R(0); }
/* (kind, world, i): world + i*5 + 29 / 209 */
static void cv_56c0(GM_CTX) {
    int k = cmps(ctx, (int32_t)R(4), 0);
    R(4) = (uint32_t)((int32_t)R(5) * 448);
    R(0) = R(6) << 2; R(0) = R(0) + R(6);
    R(3) = R(3) + R(4); R(3) = R(3) + R(0);
    R(3) = R(3) + (k == 0 ? 209 : 29);
}
/* (kind, world, i): world + i*10 + a / b */
static void cv_ten(GM_CTX, uint32_t a, uint32_t b) {
    int k = cmps(ctx, (int32_t)R(4), 0);
    R(4) = (uint32_t)((int32_t)R(5) * 448);
    R(0) = (uint32_t)((int32_t)R(6) * 10);
    R(3) = R(3) + R(4); R(3) = R(3) + R(0);
    R(3) = R(3) + (k == 0 ? b : a);
}
/* (kind, world): the word at a / b */
static void cv_kword(GM_CTX, uint32_t a, uint32_t b) {
    int k = cmps(ctx, (int32_t)R(4), 0);
    w0(GM_PASS, 5);
    R(3) = gm_u32(R(3) + (k == 0 ? b : a));
}
static void cv_5810(GM_CTX) {
    R(4) = (uint32_t)((int32_t)R(4) * 24);
    R(3) = R(3) + 0x10000u;
    R(0) = R(5) << 2;
    R(3) = R(3) + R(4);
    R(0) = R(0) + R(5);
    R(3) = gm_u32(R(3) + 24356);
    R(3) = R(3) + R(0);
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
/* (plain GM_HLE below: written but off - no test reaches it; not in hle_funcs.txt) */
#ifdef GM_WM_VERIFY          /* (testing, as GM_WIPE_VERIFY in gm_d_wipe.c: the calls run twice) */
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_WM_COUNT)    /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_800F2710, 320) { wa_ctor(GM_PASS); }                                          /* dWmActor_c::dWmActor_c */
E(fn_800F2770, 320) { wa_dtor(GM_PASS); }                                          /* ::~dWmActor_c */
E(fn_800F27D0, 320) { wa_pre_create(GM_PASS); }       /* ::preCreate */
E(fn_800F2800, 320) { GM_TAIL(F_BASE_POST_CREATE, 0); }                            /* ::postCreate */
E(fn_800F2810, 320) { wa_pre_delete(GM_PASS); }       /* ::preDelete */
E(fn_800F2840, 320) { GM_TAIL(F_BASE_POST_DELETE, 0); }                            /* ::postDelete */
E(fn_800F2850, 320) { wa_pre_execute(GM_PASS); }                                   /* ::preExecute */
E(fn_800F2900, 320) { GM_TAIL(F_BASE_POST_EXECUTE, 0); }                           /* ::postExecute */
E(fn_800F2910, 320) { wa_pre_draw(GM_PASS); }                                      /* ::preDraw */
E(fn_800F29E0, 320) { GM_TAIL(F_BASE_POST_DRAW, 0); }                              /* ::postDraw */
E(fn_800F29F0, 320) { GM_TAIL(F_BASE_DRAW_8006CA80, 0); }
E(fn_800F2A00, 320) { GM_TAIL(F_CREATE_CHILD, 0); }                                /* ::construct */
GM_HLE(fn_800F2A10) { R(4) = 0; GM_TAIL(0x800B3F50u, 0); }                         /* ::setSoftLight_Map */
E(fn_800F2A20, 320) { R(4) = 0; GM_TAIL(0x800B42B0u, 0); }                         /* ::setSoftLight_MapObj */
E(fn_800F2A30, 320) { R(4) = 0; GM_TAIL(0x800B4170u, 0); }                         /* ::setSoftLight_Enemy */
E(fn_800F2A40, 320) { R(4) = 0; GM_TAIL(0x800B4050u, 0); }                         /* ::setSoftLight_Boss */
GM_HLE(fn_800F2A50) { R(3) = 0; }                                                  /* ::GetActorType */

E(fn_800F56B0, 4) { w0(GM_PASS, 4); R(3) = R(3) + 24; }
E(fn_800F56C0, 4) { cv_56c0(GM_PASS); }
E(fn_800F5700, 4) { cv_kword(GM_PASS, 392, 404); }
E(fn_800F5730, 4) { cv_ten(GM_PASS, 49, 229); }
E(fn_800F5770, 4) { cv_kword(GM_PASS, 396, 400); }
E(fn_800F57A0, 4) { w0(GM_PASS, 4); R(0) = gm_u32(R(3) + 456); R(3) = R(5) & R(0); }
GM_HLE(fn_800F57C0) { w0(GM_PASS, 4); R(0) = gm_u32(R(3) + 464); R(3) = R(5) & R(0); }
GM_HLE(fn_800F57E0) { w0(GM_PASS, 4); R(3) = gm_u8(R(3) + 460); }
E(fn_800F57F0, 4) { p0(GM_PASS); R(3) = R(3) + 24344; }
E(fn_800F5810, 4) { cv_5810(GM_PASS); }
E(fn_800F5830, 4) { p0(GM_PASS); R(3) = R(3) + 20504; }
E(fn_800F5930, 4) { p0(GM_PASS); R(3) = gm_u32(R(3) + 24360); }
GM_HLE(fn_800F5950) { p0(GM_PASS); R(3) = gm_u8(R(3) + 20524); }
GM_HLE(fn_800F5970) { cv_kword(GM_PASS, 448, 452); }
GM_HLE(fn_800F59A0) { cv_ten(GM_PASS, 408, 428); }
E(fn_800F5A80, 4) { R(3) = gm_u32(R(3) + 12); GM_TAIL(0x802B9290u, 0); }       /* (a delete[] of +12) */
