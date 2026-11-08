/* gm_d_lytbase.c - LytBase_c's animations (m2d::EmbedLayout_c in the symbol map), the layout base
 * every 2D screen uses: AnimeStartBaseSetup / AnimeStartSetup / LoopAnimeStartSetup /
 * ReverseAnimeStartSetup, AnimeEndSetup / AllAnimeEndSetup, AnimePlay (every layout, every frame),
 * isAnime / isAllAnime. Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_lytbase.cpp) and checked against the
 * recompiled USA rev 2 code (0x800C9270-0x800C967C). Its build / resource / pane-register /
 * scissor / delete functions stay recompiled for now. Written register-exact (R(n)). The m2d
 * calls (AnmGroup_c::setAnmEnable / updateFrame / play, FrameCtrl_c::setFrame / isStop) are
 * instance 1's natives already (gm_m_2d.c).
 *
 * LytBase_c: +388 the animation groups (m2d::AnmGroup_c, 40 bytes: +0 its FrameCtrl_c - +4 the
 * end frame, +20 flags: 1 no loop, 2 reverse), +392 enabled (bool per group), +400 the group
 * count, +404 the last started. */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define LF(a) ldfs(base, (a))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }

#define F_SET_ENABLE  0x80164460u        /* m2d::AnmGroup_c::setAnmEnable(bool) */
#define F_UPDATE      0x801644D0u        /* ::updateFrame */
#define F_PLAY        0x801636C0u        /* m2d::FrameCtrl_c::play */
#define F_SET_FRAME   0x801637D0u        /* ::setFrame(f1) */
#define F_IS_STOP     0x801637F0u        /* ::isStop */
#define K_ZERO   26504                    /* (r2 - 26504: 0.0f) */
#define K_ONE    26492                    /* (r2 - 26492: 1.0f, AnimeStartSetup's last frame) */
#define K_REV    26500                    /* (r2 - 26500: ReverseAnimeStartSetup's) */

/* AnimeStartBaseSetup(i): enable the group, frame 0, enabled, the last started */
static void ly_start_base(GM_CTX) {
    GM_FN(0x800C9270); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = (uint32_t)((int32_t)R(4) * 40); R(30) = R(4); R(4) = 1; R(29) = R(3);
    R(0) = gm_u32(R(3) + 388); R(3) = R(0) + R(31);
    GM_CALLV(0x800C92A4u, F_SET_ENABLE, 0);
    R(0) = gm_u32(R(29) + 388);
    FB(1, LF(R(2) - K_ZERO));
    R(31) = R(31) + R(0); R(3) = gm_u32(R(31));             /* (lwzux) */
    GM_CALLV(0x800C92B4u, F_SET_FRAME, 0);
    R(3) = R(31);
    GM_CALLV(0x800C92BCu, F_UPDATE, 0);
    R(3) = gm_u32(R(29) + 392); R(0) = 1;
    gm_set_u8(R(3) + R(30), 1);
    gm_set_u32(R(29) + 404, R(30));
    R(0) = lr;
}
/* the group's frame to f1, then updateFrame (r31 = the group) */
static inline void set_frame(GM_CTX, uint32_t ra1, uint32_t ra2) {
    GM_CALLV(ra1, F_SET_FRAME, 0);
    R(3) = R(31);
    GM_CALLV(ra2, F_UPDATE, 0);
}
/* AnimeStartSetup(i, atEnd): no loop, from the start or the last frame */
static void ly_start(GM_CTX) {
    GM_FN(0x800C92F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(5); R(30) = R(4); R(29) = R(3);
    GM_CALLV(0x800C9318u, 0x800C9270u, 0);
    if (cmps(ctx, (int32_t)R(31), 0) != 0) {                 /* setLast() */
        R(0) = (uint32_t)((int32_t)R(30) * 40);
        R(3) = gm_u32(R(29) + 388);
        FB(0, LF(R(2) - K_ONE));
        R(31) = R(3) + R(0); R(3) = gm_u32(R(3) + R(0));
        FB(1, LF(R(3) + 4)); FB(1, frsp(ctx->f[1].d - ctx->f[0].d));
        set_frame(GM_PASS, 0x800C9340u, 0x800C9348u);
    }
    R(0) = (uint32_t)((int32_t)R(30) * 40);
    R(3) = gm_u32(R(29) + 388); R(4) = 1;
    R(3) = gm_u32(R(3) + R(0));
    gm_set_u8(R(3) + 20, 1);
    R(0) = lr;
}
static void ly_loop(GM_CTX) {                                /* LoopAnimeStartSetup(i) */
    GM_FN(0x800C9380); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(4); R(30) = R(3);
    GM_CALLV(0x800C93A0u, 0x800C9270u, 0);
    R(0) = (uint32_t)((int32_t)R(31) * 40);
    R(3) = gm_u32(R(30) + 388); R(4) = 0;
    R(3) = gm_u32(R(3) + R(0));
    gm_set_u8(R(3) + 20, 0);
    R(0) = lr;
}
static void ly_reverse(GM_CTX) {                             /* ReverseAnimeStartSetup(i, atEnd) */
    GM_FN(0x800C93D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(4); R(30) = R(5); R(29) = R(3);
    GM_CALLV(0x800C93F8u, 0x800C9270u, 0);
    if (cmps(ctx, (int32_t)R(30), 0) != 0) {
        R(30) = (uint32_t)((int32_t)R(31) * 40);
        R(3) = gm_u32(R(29) + 388); R(0) = 1;
        FB(0, LF(R(2) - K_REV));
        R(3) = gm_u32(R(3) + R(30));
        gm_set_u8(R(3) + 20, 1);
        R(0) = gm_u32(R(29) + 388);
        R(3) = gm_u32(R(30) + R(0)); R(31) = R(0) + R(30);
        FB(1, LF(R(3) + 4)); FB(1, frsp(ctx->f[1].d - ctx->f[0].d));
        set_frame(GM_PASS, 0x800C9430u, 0x800C9438u);
    } else {
        R(30) = (uint32_t)((int32_t)R(31) * 40);
        R(0) = gm_u32(R(29) + 388);
        FB(1, LF(R(2) - K_REV));
        R(3) = gm_u32(R(30) + R(0)); R(31) = R(0) + R(30);
        set_frame(GM_PASS, 0x800C9454u, 0x800C945Cu);
    }
    R(3) = gm_u32(R(29) + 388); R(0) = 3;
    R(3) = gm_u32(R(3) + R(30));
    gm_set_u8(R(3) + 20, 3);
    R(0) = lr;
}
static void ly_end(GM_CTX) {                                 /* AnimeEndSetup(i) */
    GM_FN(0x800C9490); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(4); R(30) = R(3);
    R(5) = gm_u32(R(3) + 392);
    R(0) = gm_u8(R(5) + R(4));
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(0) = (uint32_t)((int32_t)R(4) * 40);
        R(3) = gm_u32(R(3) + 388); R(4) = 0; R(3) = R(3) + R(0);
        GM_CALLV(0x800C94D0u, F_SET_ENABLE, 0);
        R(3) = gm_u32(R(30) + 392); R(0) = 0;
        gm_set_u8(R(3) + R(31), 0);
    }
    R(0) = lr;
}
static void ly_all_end(GM_CTX) {                             /* AllAnimeEndSetup() */
    GM_FN(0x800C9500); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = 0; R(30) = R(3);
    for (;;) {
        R(0) = gm_u32(R(30) + 400);
        if (cmps(ctx, (int32_t)R(31), (int32_t)R(0)) >= 0) break;
        GM_LOOP();
        R(3) = R(30); R(4) = R(31);
        GM_CALLV(0x800C952Cu, 0x800C9490u, 0);
        R(31) = R(31) + 1;
    }
    gm_set_u32(R(30) + 404, R(0));
    R(0) = lr;
}
static void ly_play(GM_CTX) {                                /* AnimePlay() */
    GM_FN(0x800C9560); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = 0; R(29) = 0; R(28) = R(3);
    for (;;) {
        R(0) = gm_u32(R(28) + 400);
        if (cmps(ctx, (int32_t)R(29), (int32_t)R(0)) >= 0) break;
        GM_LOOP();
        R(3) = gm_u32(R(28) + 392);
        R(0) = gm_u8(R(3) + R(29));
        if (cmps(ctx, (int32_t)R(0), 0) != 0) {
            R(3) = gm_u32(R(28) + 388); R(3) = gm_u32(R(3) + R(30));
            GM_CALLV(0x800C95A8u, F_IS_STOP, 0);
            if (cmps(ctx, (int32_t)R(3), 0) != 0) {
                R(3) = R(28); R(4) = R(29);
                GM_CALLV(0x800C95BCu, 0x800C9490u, 0);       /* AnimeEndSetup(i) */
            } else {
                R(0) = gm_u32(R(28) + 388);
                R(3) = gm_u32(R(30) + R(0)); R(31) = R(0) + R(30);
                GM_CALLV(0x800C95D0u, F_PLAY, 0);
                R(3) = R(31);
                GM_CALLV(0x800C95D8u, F_UPDATE, 0);
            }
        }
        R(30) = R(30) + 40; R(29) = R(29) + 1;
    }
    R(0) = lr;
}

#define A(i) GM_ARG(i)
#define LY_MEM A(0), 408, gm_u32(A(0) + 392), gm_u32(A(0) + 400)   /* (the layout, its enabled flags) */
GM_HLE_VOID(fn_800C9270, LY_MEM) { ly_start_base(GM_PASS); }                                  /* LytBase_c::AnimeStartBaseSetup */
GM_HLE_VOID(enableNonLoopAnim__Q23m2d13EmbedLayout_cFib, LY_MEM) { ly_start(GM_PASS); }       /* ::AnimeStartSetup */
GM_HLE_VOID(enableLoopAnim__Q23m2d13EmbedLayout_cFi, LY_MEM) { ly_loop(GM_PASS); }            /* ::LoopAnimeStartSetup */
GM_HLE_VOID(resetAnim__Q23m2d13EmbedLayout_cFib, LY_MEM) { ly_reverse(GM_PASS); }             /* ::ReverseAnimeStartSetup */
GM_HLE_VOID(fn_800C9490, LY_MEM) { ly_end(GM_PASS); }                                         /* ::AnimeEndSetup */
GM_HLE_VOID(disableAllAnimations__Q23m2d13EmbedLayout_cFv, LY_MEM) { ly_all_end(GM_PASS); }   /* ::AllAnimeEndSetup */
GM_HLE(execAnimations__Q23m2d13EmbedLayout_cFv) { ly_play(GM_PASS); }                         /* ::AnimePlay (its play() isn't repeatable: not verified) */
GM_HLE_INT(isAnimOn__Q23m2d13EmbedLayout_cFi, 0, 0) {                                          /* ::isAnime(i: -1 the last started) */
    if (cmps(ctx, (int32_t)R(4), 0) < 0) { R(4) = gm_u32(R(3) + 392); R(0) = gm_u32(R(3) + 404); R(3) = gm_u8(R(4) + R(0)); }
    else { R(3) = gm_u32(R(3) + 392); R(3) = gm_u8(R(3) + R(4)); }
}
GM_HLE_INT(isAnyAnimOn__Q23m2d13EmbedLayout_cFv, 0, 0) {                                       /* ::isAllAnime */
    R(0) = gm_u32(R(3) + 400); R(5) = 0; ctx->ctr = R(0);
    if (cmps(ctx, (int32_t)R(0), 0) > 0) {
        for (;;) {
            R(4) = gm_u32(R(3) + 392); R(0) = gm_u8(R(4) + R(5));
            if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(3) = 1; return; }
            R(5) = R(5) + 1;
            if (--ctx->ctr == 0) break;
            GM_LOOP();
        }
    }
    R(3) = 0;
}
