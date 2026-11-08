/* gm_d_smallscore.c - the score pop-ups and two small 2D helpers they share the frame with:
 * dSmallScore_c (execute: its state through the pointer-to-member table, the position, the
 * layout's calc; draw; PosSet: the pop-up rising from its world position, put on the layout),
 * dSmallScoreManager_c (execute / draw over its 30 pop-ups and 4 goal scores),
 * dSelectCursor_c's execute / draw (0x8010C380 / 0x8010C420 - "the five-slot layout manager"
 * until part 63 named it: per cursor PosSet, the animations, the layout's calc / entry; the rest
 * of the class is gm_d_selectcursor.c) and the GX state keeper of the 2D drawing (0x80014330: save the parts
 * named by a mask - the current matrix, the projection, the viewport, the cull mode, the scissor,
 * the colour / alpha / dither updates - and put them back). Track B (gm.h, docs/DECOMP.md),
 * instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_SmallScore.cpp, d_SmallScoreManager.cpp)
 * and checked against the recompiled USA rev 2 code; the GX state keeper has no decomp source (from the recompiled code). Picked by the call profile of part 49:
 * dSmallScore_c::execute / draw are the hottest game functions still recompiled in the tests
 * (every pop-up of the pool runs every frame, shown or not). Their create / setup functions stay
 * recompiled. Written register-exact (R(n): r31 / r30 ... as the PowerPC code keeps them).
 *
 * dSmallScore_c (548 bytes): +4 m2d::EmbedLayout_c (+12 its vtable: +16 calc), +412 / +416 the
 * position x / y, +424 the rise left, +432 the rise per frame, +440 the rise so far, +468 the
 * root pane (+44 / +48 / +52 its translation; +187 bit 0 visible), +500 the top limit, +504 the
 * state (4 = none; a table of 4 pointer-to-members at 0x802EDDA0).
 * dSmallScoreManager_c: +328 the 30 pop-ups, +16768 the 4 goal scores, +18964 an index.
 * The GX state keeper: +0 the saved mask, +4 the current matrix slot, +436 a position matrix,
 * +652 the projection (7 floats), +680 the viewport (6 floats), +704 the scissor (4 u32), +720 the
 * cull mode, +724 / +725 / +726 the colour / alpha / dither update flags (from EGG's StateGX). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define LF(a) ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int rec0(ppc_context *ctx, uint32_t v) { cr_cmp_s(ctx, 0, (int32_t)v, 0); return v != 0; }   /* andi. */

#define F_PTMF_SCALL   0x802DCBFCu
#define F_LYT_ENTRY    0x80006EA0u      /* m2d::Base_c::entry */
#define F_EXEC_ANIM    0x800C9560u      /* m2d::EmbedLayout_c::execAnimations */
#define F_GLB_TO_LYT   0x800B33D0u      /* dGameCom::getGlbPosToLyt(mVec3_c &) */
#define F_IS_GAME_STOP 0x800B3B50u      /* dGameCom::isGameStop(flags) */
#define SS_PROCS       0x802EDDA0u      /* dSmallScore_c's state table */
#define SS_ZERO        32472            /* (r2 - 32472: 0.0f) */
#define STATE_GX       (0x80420000u + 18624u)   /* EGG::StateGX's flags (+12 / +13 / +14 colour / alpha / dither update) */

/* ================================================================== dSmallScore_c */
/* PosSet(): rise until the rise is used up, keep below the top limit, world -> layout */
static void ss_posset(GM_CTX) {
    GM_FN(0x80015C10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(31) = R(3);
    R(4) = gm_u32(R(3) + 468);
    R(0) = gm_u8(R(4) + 187) & 1;
    if (rec0(ctx, R(0))) {
        FB(2, LF(R(3) + 424));
        FB(0, LF(R(2) - SS_ZERO));
        cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
        CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
        if (CR_BIT(ctx, 2)) SF(R(3) + 424, ctx->f[0].d);
        else {
            FB(1, LF(R(3) + 440));
            FB(0, LF(R(3) + 432));
            FB(1, frsp(ctx->f[1].d + ctx->f[2].d));
            FB(0, frsp(ctx->f[2].d - ctx->f[0].d));
            SF(R(3) + 440, ctx->f[1].d);
            SF(R(3) + 424, ctx->f[0].d);
        }
        FB(0, LF(R(3) + 412));
        SF(f + 28, ctx->f[0].d);
        FB(1, LF(R(3) + 416));
        FB(0, LF(R(3) + 440));
        FB(1, frsp(ctx->f[1].d + ctx->f[0].d));
        SF(f + 32, ctx->f[1].d);
        FB(0, LF(R(3) + 500));
        cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
        CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
        if (CR_BIT(ctx, 2)) SF(f + 32, ctx->f[0].d);
        R(3) = f + 28;
        GM_CALLV(0x80015C9Cu, F_GLB_TO_LYT, 0);
        FB(1, LF(f + 32));
        FB(2, LF(f + 28));
        R(3) = gm_u32(R(31) + 468);
        FB(0, LF(R(2) - SS_ZERO));
        SF(R(3) + 44, ctx->f[2].d);
        SF(R(3) + 48, ctx->f[1].d);
        SF(f + 8, ctx->f[2].d);  SF(f + 12, ctx->f[1].d);                   /* (the mVec3_c temporaries) */
        SF(f + 16, ctx->f[2].d); SF(f + 20, ctx->f[1].d); SF(f + 24, ctx->f[0].d);
        SF(R(3) + 52, ctx->f[0].d);
    }
    R(0) = lr;
}
/* execute(): the state, the position, the layout's calc */
static void ss_execute(GM_CTX) {
    GM_FN(0x80015160); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    R(0) = gm_u32(R(3) + 504);
    if (cmps(ctx, (int32_t)R(0), 4) != 0) {
        R(0) = (uint32_t)((int32_t)R(0) * 12);
        R(4) = SS_PROCS;
        R(12) = R(4) + R(0);
        GM_CALLV(0x80015194u, F_PTMF_SCALL, 0);
        R(3) = R(31);
        GM_CALLV(0x800151A0u, 0x80015C10u, 0);                              /* PosSet() */
        R(12) = gm_u32(R(31) + 12);
        R(3) = R(31) + 4;
        R(12) = gm_u32(R(12) + 16);
        ctx->ctr = R(12);
        GM_CALLV(0x800151B4u, R(12), 0);
    }
    R(0) = lr;
}
/* draw(): the layout, while the state shows it */
static void ss_draw(GM_CTX) {
    R(0) = gm_u32(R(3) + 504);
    if (cmps(ctx, (int32_t)R(0), 4) == 0) return;
    if (cmps(ctx, (int32_t)R(0), 0) <= 0) return;
    R(3) = R(3) + 4;
    GM_TAIL(F_LYT_ENTRY, 0);
}

/* ================================================================== dSmallScoreManager_c */
static void ssm_execute(GM_CTX) {
    GM_FN(0x8010CCD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(29) = R(3);
    R(3) = (uint32_t)-1;
    GM_CALLV(0x8010CCF4u, F_IS_GAME_STOP, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) {
        R(31) = R(29) + 328; R(30) = 0;
        for (;;) {
            R(3) = R(31);
            GM_CALLV(0x8010CD14u, 0x80015160u, 0);                          /* dSmallScore_c::execute */
            R(30) = R(30) + 1; R(31) = R(31) + 548;
            if (cmps(ctx, (int32_t)R(30), 30) >= 0) break;
            GM_LOOP();
        }
        R(31) = R(29) + 16768; R(30) = 0;
        for (;;) {
            R(3) = R(31);
            GM_CALLV(0x8010CD34u, 0x80015160u, 0);                          /* (the goal scores) */
            R(30) = R(30) + 1; R(31) = R(31) + 548;
            if (cmps(ctx, (int32_t)R(30), 4) >= 0) break;
            GM_LOOP();
        }
        R(0) = 0;
        gm_set_u32(R(29) + 18964, 0);
    }
    R(3) = 1;
    R(0) = lr;
}
static void ssm_draw(GM_CTX) {
    GM_FN(0x8010CD70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3) + 328; R(30) = 0; R(29) = R(3);
    for (;;) {
        R(3) = R(31);
        GM_CALLV(0x8010CD9Cu, 0x800151D0u, 0);                              /* dSmallScore_c::draw */
        R(30) = R(30) + 1; R(31) = R(31) + 548;
        if (cmps(ctx, (int32_t)R(30), 30) >= 0) break;
        GM_LOOP();
    }
    R(31) = R(29) + 16768; R(30) = 0;
    for (;;) {
        R(3) = R(31);
        GM_CALLV(0x8010CDBCu, 0x800151D0u, 0);
        R(30) = R(30) + 1; R(31) = R(31) + 548;
        if (cmps(ctx, (int32_t)R(30), 4) >= 0) break;
        GM_LOOP();
    }
    R(3) = 1;
    R(0) = lr;
}

/* ================================================================== dSelectCursor_c (d_SelectCursor.cpp)
   execute (0x8010C380): five cursor layouts of 612 bytes from +324, +772 per cursor "on" (u8) */
static void five_execute(GM_CTX) {
    GM_FN(0x8010C380); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3) + 324; R(29) = 0; R(28) = R(3); R(31) = R(28);
    for (;;) {
        R(0) = gm_u8(R(31) + 772);
        if (cmps(ctx, (int32_t)R(0), 0) != 0) {
            R(3) = R(28); R(4) = R(29);
            GM_CALLV(0x8010C3C4u, 0x8010C510u, 0);                          /* (the slot's update) */
            R(3) = R(30);
            GM_CALLV(0x8010C3CCu, F_EXEC_ANIM, 0);
            R(12) = gm_u32(R(30) + 8);
            R(3) = R(30);
            R(12) = gm_u32(R(12) + 16);
            ctx->ctr = R(12);
            GM_CALLV(0x8010C3E0u, R(12), 0);
        }
        R(29) = R(29) + 1; R(30) = R(30) + 612;
        int c = cmps(ctx, (int32_t)R(29), 5);
        R(31) = R(31) + 612;
        if (c >= 0) break;
        GM_LOOP();
    }
    R(3) = 1;
    R(0) = lr;
}
static void five_draw(GM_CTX) {
    GM_FN(0x8010C420); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3); R(30) = R(3) + 324; R(29) = 0;
    for (;;) {
        R(0) = gm_u8(R(31) + 772);
        if (cmps(ctx, (int32_t)R(0), 0) != 0) {
            R(3) = R(30);
            GM_CALLV(0x8010C458u, F_LYT_ENTRY, 0);
        }
        R(29) = R(29) + 1; R(30) = R(30) + 612;
        int c = cmps(ctx, (int32_t)R(29), 5);
        R(31) = R(31) + 612;
        if (c >= 0) break;
        GM_LOOP();
    }
    R(3) = 1;
    R(0) = lr;
}

/* ================================================================== the GX state keeper */
static void gxs_save(GM_CTX) {
    GM_FN(0x80014380); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(0) = R(4) & 1u;
    int b = rec0(ctx, R(0));
    R(31) = R(3); R(30) = R(4);
    if (b) { R(3) = R(3) + 436; GM_CALLV(0x800143ACu, 0x801C3FE0u, 0); }
    if (rec0(ctx, R(0) = R(30) & 0x2u)) { R(4) = R(31) + 4; R(3) = 0; GM_CALLV(0x800143C0u, 0x801C4700u, 0); }
    if (rec0(ctx, R(0) = R(30) & 0x4u)) { R(3) = R(31) + 652; GM_CALLV(0x800143D0u, 0x801C9900u, 0); }   /* GXGetProjectionv */
    if (rec0(ctx, R(0) = R(30) & 0x8u)) { R(3) = R(31) + 680; GM_CALLV(0x800143E0u, 0x801C9C40u, 0); }   /* GXGetViewportv */
    if (rec0(ctx, R(0) = R(30) & 0x10u)) { R(3) = R(31) + 720; GM_CALLV(0x800143F0u, 0x801C5890u, 0); }  /* (the cull mode) */
    if (rec0(ctx, R(0) = R(30) & 0x20u)) {                                                               /* (the scissor) */
        R(3) = R(31) + 704; R(4) = R(31) + 708; R(5) = R(31) + 712; R(6) = R(31) + 716;
        GM_CALLV(0x8001440Cu, 0x802D3260u, 0);
    }
    if (rec0(ctx, R(0) = R(30) & 0x40u)) { R(3) = STATE_GX; R(0) = gm_u8(R(3) + 12); gm_set_u8(R(31) + 724, (uint8_t)R(0)); }
    if (rec0(ctx, R(0) = R(30) & 0x80u)) { R(3) = STATE_GX; R(0) = gm_u8(R(3) + 13); gm_set_u8(R(31) + 725, (uint8_t)R(0)); }
    if (rec0(ctx, R(0) = R(30) & 0x100u)) { R(3) = STATE_GX; R(0) = gm_u8(R(3) + 14); gm_set_u8(R(31) + 726, (uint8_t)R(0)); }
    R(0) = gm_u32(R(31)) | R(30);
    gm_set_u32(R(31), R(0));
    R(0) = lr;
}
static inline uint32_t gxs_bit(GM_CTX, uint32_t m) { R(0) = gm_u32(R(31)) & m; return (uint32_t)rec0(ctx, R(0)); }
static inline uint32_t gxs_bool(GM_CTX, uint32_t off) {                 /* (neg / or / srwi: != 0) */
    R(3) = gm_u8(R(31) + off); R(0) = (uint32_t)-(int32_t)R(3); R(0) = R(0) | R(3); return R(3) = R(0) >> 31;
}
static void gxs_restore(GM_CTX) {
    GM_FN(0x80014480); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    if (gxs_bit(GM_PASS, 0x1)) { R(3) = R(31) + 436; GM_CALLV(0x800144A8u, 0x801C3A30u, 0); }
    if (gxs_bit(GM_PASS, 0x2)) { R(4) = R(31) + 4; R(3) = 0; GM_CALLV(0x800144C0u, 0x801C4250u, 0); }
    if (gxs_bit(GM_PASS, 0x10)) { R(3) = gm_u32(R(31) + 720); GM_CALLV(0x800144D4u, 0x801C5860u, 0); }  /* GXSetCullMode */
    if (gxs_bit(GM_PASS, 0x4)) { R(3) = R(31) + 652; GM_CALLV(0x800144E8u, 0x802D31D0u, 0); }
    if (gxs_bit(GM_PASS, 0x8)) {
        for (int i = 0; i < 6; i++) FB(1 + i, LF(R(31) + 680 + 4 * i));
        GM_CALLV(0x80014510u, 0x802D3200u, 0);
    }
    if (gxs_bit(GM_PASS, 0x20)) {
        R(3) = gm_u32(R(31) + 704); R(4) = gm_u32(R(31) + 708); R(5) = gm_u32(R(31) + 712); R(6) = gm_u32(R(31) + 716);
        GM_CALLV(0x80014530u, 0x802D3230u, 0);
    }
    if (gxs_bit(GM_PASS, 0x40)) { gxs_bool(GM_PASS, 724); GM_CALLV(0x80014550u, 0x802D2F20u, 0); }       /* ChangeColorUpdate */
    if (gxs_bit(GM_PASS, 0x80)) { gxs_bool(GM_PASS, 725); GM_CALLV(0x80014570u, 0x802D2F80u, 0); }       /* ChangeAlphaUpdate */
    if (gxs_bit(GM_PASS, 0x100)) { gxs_bool(GM_PASS, 726); GM_CALLV(0x80014590u, 0x802D2FE0u, 0); }      /* (the dither) */
    R(0) = 0;
    gm_set_u32(R(31), 0);
    R(0) = lr;
}

/* ================================================================== dSmallScoreManager_c's life */
static void ssm_profile(GM_CTX) {                                           /* the profile: new dSmallScoreManager_c */
    GM_FN(0x8010C9D0); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(3) = 18968;
    GM_CALLV(0x8010C9E4u, 0x801628C0u, 0);                                   /* (the profile's allocation) */
    if (cmps(ctx, (int32_t)R(3), 0) != 0) GM_CALLV(0x8010C9F0u, 0x8010CA00u, 0);
    R(0) = lr;
}
/* the ctor: dBase_c, the loader, 30 pop-ups from +328 and 4 goal scores from +16768 (548 bytes) */
static void ssm_ctor(GM_CTX) {
    GM_FN(0x8010CA00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(29) = R(3);
    GM_CALLV(0x8010CA20u, 0x8006C420u, 0);                                   /* dBase_c::dBase_c */
    R(4) = 0x80320000u; R(3) = R(29) + 116;
    R(4) = R(4) + 10288;
    gm_set_u32(R(29) + 96, R(4));
    GM_CALLV(0x8010CA34u, 0x80006AA0u, 0);                                   /* d2d::ResAccMultLoader_c */
    R(30) = 0x80010000u; R(31) = 0x80010000u;
    R(3) = R(29) + 328; R(6) = 548;
    R(4) = R(30) + 20240; R(5) = R(31) + 20352;                              /* dSmallScore_c ctor / dtor */
    R(7) = 30;
    GM_CALLV(0x8010CA54u, 0x802DC9A0u, 0);                                   /* __construct_array */
    R(3) = R(29) + 16768;
    R(4) = R(30) + 20240; R(5) = R(31) + 20352;
    R(6) = 548; R(7) = 4;
    GM_CALLV(0x8010CA6Cu, 0x802DC9A0u, 0);
    gm_set_u32(R(13) - 21424, R(29));                                        /* m_instance */
    R(3) = R(29);
    R(0) = lr;
}
static void ssm_dtor(GM_CTX) {
    GM_FN(0x8010CA90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(30) = R(4); R(29) = R(3);
    if (c != 0) {
        R(0) = 0;
        R(31) = 0x80010000u;
        gm_set_u32(R(13) - 21424, 0);
        R(4) = R(31) + 20352; R(5) = 548; R(6) = 4;
        R(3) = R(3) + 16768;
        GM_CALLV(0x8010CAD8u, 0x802DCA98u, 0);                               /* __destroy_arr */
        R(3) = R(29) + 328; R(4) = R(31) + 20352; R(5) = 548; R(6) = 30;
        GM_CALLV(0x8010CAECu, 0x802DCA98u, 0);
        R(3) = R(29) + 116; R(4) = (uint32_t)-1;
        GM_CALLV(0x8010CAF8u, 0x80006AF0u, 0);
        R(3) = R(29); R(4) = 0;
        GM_CALLV(0x8010CB04u, 0x8006C490u, 0);                               /* dBase_c::~dBase_c */
        if (cmps(ctx, (int32_t)R(30), 0) > 0) { R(3) = R(29); GM_CALLV(0x8010CB14u, 0x80162920u, 0); }
    }
    R(3) = R(29);
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_SS_VERIFY          /* (testing, as GM_WIPE_VERIFY in gm_d_wipe.c: the calls run twice) */
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_SS_COUNT)    /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_80015160, 548)   { ss_execute(GM_PASS); }                                     /* dSmallScore_c::execute */
E(fn_800151D0, 548)   { ss_draw(GM_PASS); }                                        /* ::draw */
E(fn_80015C10, 548)   { ss_posset(GM_PASS); }                                      /* ::PosSet */
E(fn_8010CCD0, 18968) { ssm_execute(GM_PASS); }                                    /* dSmallScoreManager_c::execute */
E(fn_8010CD70, 18968) { ssm_draw(GM_PASS); }                                       /* ::draw */
E(fn_8010C380, 3384)  { five_execute(GM_PASS); }                                   /* dSelectCursor_c::execute */
E(fn_8010C420, 3384)  { five_draw(GM_PASS); }                                      /* dSelectCursor_c::draw */
E(fn_80014330, 728)   { R(0) = 0; gm_set_u32(R(3), 0); }                           /* the GX state keeper: ctor */
E(fn_80014380, 728)   { gxs_save(GM_PASS); }                                       /* ... save(mask) */
E(fn_80014480, 728)   { gxs_restore(GM_PASS); }                                    /* ... restore */
E(fn_8010C9D0, 4)     { ssm_profile(GM_PASS); }                                     /* dSmallScoreManager_c: the profile's create */
E(fn_8010CA00, 18968) { ssm_ctor(GM_PASS); }                                        /* ::dSmallScoreManager_c */
E(fn_8010CA90, 18968) { ssm_dtor(GM_PASS); }                                        /* ::~dSmallScoreManager_c */
