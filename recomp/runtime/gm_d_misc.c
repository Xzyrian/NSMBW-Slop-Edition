/* gm_d_misc.c - small game classes: dCoin_c::execute (the coins' shared spin / pattern timers,
 * every frame in a course), dCurtainMng_c::CurtainInfoAllClear, dDvd (create, loader_c ctor /
 * dtor / request - every archive load of the game's 2D and message code). Track B (gm.h,
 * docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_coin.cpp, d_curtain_mng.cpp; dDvd from
 * the recompiled code - no decomp source) and checked against the recompiled USA rev 2 code
 * (0x8008DED0-0x8008DFD8, 0x8008ECC0-0x8008ED6C, 0x8008F110-0x8008F2A4). Register-exact (R(n)).
 *
 * dCoin_c (r13 -): 22528 m_shapeAngle, 22520 m_h_shapeAngle, 22514 m_frame, 22513 m_ptn_no,
 * 22512 m_h_ptn_no, 22511 m_h_ptn_time, 22510 m_b_ptn_no, 22509 m_b_ptn_time; the block times
 * r2 - 28768 / 28764. dDvd::loader_c: +4 the size (-1), +8 the toMainRam command, +12 the heap,
 * +16 the data; its load callback r13 - 22488. */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d
#define LF(a) ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

#define SDA(o) (R(13) - (o))
#define C_SHAPE    22528
#define C_H_SHAPE  22520
#define C_FRAME    22514
#define C_PTN      22513
#define C_H_PTN    22512
#define C_H_TIME   22511
#define C_B_PTN    22510
#define C_B_TIME   22509

/* ================================================================== dCoin_c */
static void coin_execute(GM_CTX) {
    R(5) = gm_u8(SDA(C_FRAME));
    R(3) = (R(5) >> 3) & 0xFF;
    gm_set_u8(SDA(C_PTN), (uint8_t)R(3));                                    /* m_ptn_no = m_frame / 8 */
    if (cmpu(ctx, R(3), 4) >= 0) { R(0) = R(3) - 4; gm_set_u8(SDA(C_PTN), (uint8_t)R(0)); }
    R(3) = gm_u8(SDA(C_FRAME));
    R(4) = SDA(C_SHAPE);
    R(0) = (R(5) << 10) & 0x3FC00u;
    gm_set_u16(R(4) + 2, (uint16_t)R(0));                                    /* m_shapeAngle.y = frame * 0x400 */
    R(3) = R(3) + 1;
    R(0) = R(3) & 0xFF;
    gm_set_u8(SDA(C_FRAME), (uint8_t)R(3));
    if (cmpu(ctx, R(0), 0x40) >= 0) { R(0) = 0; gm_set_u8(SDA(C_FRAME), 0); }
    R(3) = gm_u8(SDA(C_H_TIME));
    R(0) = R(3) - 1;
    gm_set_u8(SDA(C_H_TIME), (uint8_t)R(0));
    R(0) = R(0) & 0xFF;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(3) = gm_u8(SDA(C_H_PTN));
        R(5) = R(3) + 1;
        gm_set_u8(SDA(C_H_PTN), (uint8_t)R(5));
        R(0) = R(5) & 0xFF;
        if (cmpu(ctx, R(0), 4) >= 0) {
            R(4) = SDA(C_H_SHAPE);
            R(5) = 0;
            R(3) = (uint32_t)(int16_t)gm_u16(R(4) + 2);
            gm_set_u8(SDA(C_H_PTN), 0);
            R(0) = R(3) + 16383;
            R(0) = R(0) & 0xC000;
            gm_set_u16(R(4) + 2, (uint16_t)R(0));                            /* snapped to a quarter turn */
        }
        R(0) = R(5) & 0xFF;
        R(3) = R(2) - 28768;
        R(0) = gm_u8(R(3) + R(0));
        gm_set_u8(SDA(C_H_TIME), (uint8_t)R(0));
    }
    R(0) = gm_u8(SDA(C_H_PTN));
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(4) = SDA(C_H_SHAPE);
        R(3) = (uint32_t)(int16_t)gm_u16(R(4) + 2);
        R(0) = R(3) + 682;
        gm_set_u16(R(4) + 2, (uint16_t)R(0));
    }
    R(3) = gm_u8(SDA(C_B_TIME));
    R(0) = R(3) - 1;
    gm_set_u8(SDA(C_B_TIME), (uint8_t)R(0));
    R(0) = R(0) & 0xFF;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(3) = gm_u8(SDA(C_B_PTN));
        R(3) = R(3) + 1;
        gm_set_u8(SDA(C_B_PTN), (uint8_t)R(3));
        R(0) = R(3) & 0xFF;
        if (cmpu(ctx, R(0), 4) >= 0) { R(3) = 0; gm_set_u8(SDA(C_B_PTN), 0); }
        R(0) = R(3) & 0xFF;
        R(3) = R(2) - 28764;
        R(0) = gm_u8(R(3) + R(0));
        gm_set_u8(SDA(C_B_TIME), (uint8_t)R(0));
    }
    R(3) = 1;
}

/* ================================================================== dCurtainMng_c */
/* CurtainInfoAllClear(): 4 x 4 infos of 36 bytes: 0xFFFF, eight 0.0f */
static void curtain_clear(GM_CTX) {
    R(4) = 0x10000u; R(0) = 4;
    FB(0, LF(R(2) - 28744));
    R(4) = R(4) - 1;
    ctx->ctr = R(0);
    for (;;) {
        for (int j = 0; j < 4; j++) {
            gm_set_u16(R(3) + 36 * j, (uint16_t)R(4));
            for (int k = 0; k < 8; k++) SF(R(3) + 36 * j + 4 + 4 * k, F(0));
        }
        R(3) = R(3) + 144;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
}

/* ================================================================== dDvd */
static void dvd_create(GM_CTX) {                                            /* dDvd::create(prio, heaps) */
    GM_FN(0x8008F110); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(6) = 0;
    GM_CALLV(0x8008F124u, 0x8016B220u, 0);                                   /* mDvd::create */
    GM_CALLV(0x8008F128u, 0x8016B0A0u, 0);
    R(3) = 1;
    GM_CALLV(0x8008F130u, 0x8016BC10u, 0);
    R(0) = lr;
}
static void loader_ctor(GM_CTX) {
    R(5) = 0x80310000u; R(4) = 0;
    R(5) = R(5) + 3648;
    R(0) = (uint32_t)-1;
    gm_set_u32(R(3), R(5)); gm_set_u32(R(3) + 8, 0); gm_set_u32(R(3) + 4, R(0));
    gm_set_u32(R(3) + 12, 0); gm_set_u32(R(3) + 16, 0);
}
static void loader_dtor(GM_CTX) {
    GM_FN(0x8008F170); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(3);
    if (c != 0 && cmps(ctx, (int32_t)R(4), 0) > 0) GM_CALLV(0x8008F198u, 0x802B9280u, 0);
    R(3) = R(31);
    R(0) = lr;
}
/* request(path, dir, heap): the data once loaded; else start (or poll) a toMainRam command */
static void loader_request(GM_CTX) {
    GM_FN(0x8008F1B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(5); R(30) = R(4); R(29) = R(3);
    R(0) = gm_u32(R(3) + 16);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(3) = R(0); goto out; }
    R(0) = gm_u32(R(3) + 8);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        int c = cmps(ctx, (int32_t)R(6), 0);
        R(0) = (uint32_t)-1;
        gm_set_u32(R(3) + 4, R(0));
        if (c == 0) { GM_CALLV(0x8008F20Cu, 0x8016B180u, 0); R(6) = R(3); }  /* the current heap */
        gm_set_u32(R(29) + 12, R(6));
        R(3) = R(30); R(4) = R(31); R(5) = R(6);
        GM_CALLV(0x8008F224u, 0x8016BF70u, 0);                               /* mDvd_toMainRam_c::create */
        gm_set_u32(R(29) + 8, R(3));
    }
    R(3) = gm_u32(R(29) + 8);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
    R(0) = gm_u8(R(3) + 8);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) { R(3) = 0; goto out; }            /* not done yet */
    R(0) = gm_u32(R(3) + 16);
    R(31) = 0;
    gm_set_u32(R(29) + 16, R(0));
    R(0) = gm_u32(R(3) + 20);
    gm_set_u32(R(29) + 4, R(0));
    gm_set_u32(R(3) + 16, 0);
    R(3) = gm_u32(R(29) + 8);
    GM_CALLV(0x8008F260u, 0x8016B7E0u, 0);                                   /* mDvd_command_c::destroy */
    gm_set_u32(R(29) + 8, 0);
    R(12) = gm_u32(SDA(22488));
    if (cmps(ctx, (int32_t)R(12), 0) != 0) {
        R(3) = R(30); R(4) = gm_u32(R(29) + 12); ctx->ctr = R(12);
        GM_CALLV(0x8008F280u, R(12), 0);                                     /* the load callback */
    }
    R(3) = gm_u32(R(29) + 16);
out:
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_MISC_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_MISC_COUNT)  /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_8008DED0, 4)   { coin_execute(GM_PASS); }                                     /* dCoin_c::execute */
E(fn_8008DFE0, 4)   { }                                                            /* (dCoin_c: an empty one) */
E(fn_8008ECC0, 576) { curtain_clear(GM_PASS); }                                    /* dCurtainMng_c::CurtainInfoAllClear */
E(create__4dDvdFlPQ23EGG4HeapPQ23EGG4Heap, 4) { dvd_create(GM_PASS); }             /* dDvd::create */
E(__ct__Q24dDvd8loader_cFv, 20) { loader_ctor(GM_PASS); }                          /* dDvd::loader_c::loader_c */
E(__dt__Q24dDvd8loader_cFv, 20) { loader_dtor(GM_PASS); }                          /* ::~loader_c */
E(request__Q24dDvd8loader_cFPCcUcPQ23EGG4Heap, 20) { loader_request(GM_PASS); }    /* ::request */
