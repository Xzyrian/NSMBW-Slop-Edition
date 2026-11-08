/* gm_d_wipe.c - the layout wipes (the scene transitions drawn with a layout: dWipeCircle_c, the
 * circle that closes on the player; dWipeDokan_c, the pipe; dWipeKuppa_c, Bowser; dWipeMario_c,
 * Mario's face) - their per-frame calc / draw, the open / close set-ups and the end check,
 * setStatus and fadeIn / fadeOut - and mLib's mWipeFader_c (setTexture, setStatus, calc: written,
 * off - no test reaches it). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_wipe_circle.cpp, d_wipe_dokan.cpp,
 * d_wipe_kuppa.cpp, d_wipe_mario.cpp, source/dol/mLib/m_wipe_fader.cpp) and checked against the
 * recompiled USA rev 2 code (0x8001B3A0-0x8001CBAC, 0x80170C50-0x80170F3C). The four wipes are one
 * class each with the same code (one table of addresses below: wipe_t); dWipeCircle_c also keeps a
 * centre position and moves the layout there (CenterPosSet, left recompiled), dWipeDokan_c picks
 * the pipe's direction from the player (left recompiled). Their constructors, destructors and
 * createLayout stay recompiled too (once per scene).
 *
 * Written register-exact: the PowerPC registers are the variables (R(n)), r31 = the wipe, LR / CTR
 * / r12 as the calls leave them, r0 = the entry LR at the end (the epilogue's reload).
 *
 * A wipe (mFaderBase_c, gm_m_fader.c): +0 vtable (+16 getStatus), +4 status, +8 flags (1 fade-in
 * complete, 2 fade-out complete), +20 m2d::EmbedLayout_c (+28 its vtable: +16 calc; +32 the draw
 * order), +428 the root pane (+187 flags: bit 0 visible), +432 the window / picture (+184 alpha);
 * dWipeCircle_c: +436 / +440 the centre, +444 the action, +448 created, +449 / +450 has a target /
 * use the centre; the others: +436 the action, +440 created. Actions: 0 open set-up, 1 wait for
 * the animation, 2 close set-up, 3 idle (a pointer-to-member table of the first three). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }

#define F_PTMF_SCALL  0x802DCBFCu
#define F_EXEC_ANIM   0x800C9560u        /* m2d::EmbedLayout_c::execAnimations */
#define F_DISABLE_ALL 0x800C9500u        /* ::disableAllAnimations */
#define F_ENABLE_ANIM 0x800C92F0u        /* ::enableNonLoopAnim(index, reverse) */
#define F_RESET_ANIM  0x800C93D0u        /* ::resetAnim(index, reverse) */
#define F_IS_ANIM_ON  0x800C9610u        /* ::isAnimOn(index: -1 any) */
#define F_LYT_ENTRY   0x80006EA0u        /* m2d::Base_c::entry */
#define F_FADE_IN     0x8016DD20u        /* mFaderBase_c::fadeIn */
#define F_FADE_OUT    0x8016DD50u        /* mFaderBase_c::fadeOut */

enum { W_CIRCLE, W_DOKAN, W_KUPPA, W_MARIO };
typedef struct {
    uint32_t calc, draw, open, end, close, set, fin, fout;
    uint32_t procs;                      /* the action table (pointer-to-members, 12 bytes each) */
    uint32_t extra;                      /* circle: CenterPosSet; dokan: the direction check */
    uint16_t act, made;                  /* the action / created offsets */
} wipe_t;
static const wipe_t WIPES[4] = {
    { 0x8001B580u, 0x8001B600u, 0x8001B8D0u, 0x8001B920u, 0x8001B9D0u, 0x8001BA20u, 0x8001BB10u, 0x8001BB50u,   /* FNADDR */
      0x802EE038u, 0x8001B620u, 444, 448 },
    { 0x8001BD70u, 0x8001BDF0u, 0x8001BE10u, 0x8001BE80u, 0x8001BF90u, 0x8001C000u, 0x8001C0F0u, 0x8001C130u,   /* FNADDR */
      0x802EE070u, 0x8001BF20u, 436, 440 },
    { 0x8001C340u, 0x8001C3C0u, 0x8001C3E0u, 0x8001C430u, 0x8001C4D0u, 0x8001C520u, 0x8001C610u, 0x8001C650u,   /* FNADDR */
      0x802EE098u, 0, 436, 440 },
    { 0x8001C860u, 0x8001C8E0u, 0x8001C900u, 0x8001C950u, 0x8001C9F0u, 0x8001CA40u, 0x8001CB30u, 0x8001CB70u,   /* FNADDR */
      0x802EE0C0u, 0, 436, 440 },
};

/* calc(): the action, then the layout's animations and calc */
static void wipe_calc(GM_CTX, const wipe_t *w) {
    GM_FN(w->calc); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr, a = w->calc;
    R(31) = R(3);
    R(0) = gm_u8(R(3) + w->made);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(0) = gm_u32(R(3) + w->act);
        if (cmps(ctx, (int32_t)R(0), 3) != 0) {
            R(0) = (uint32_t)((int32_t)R(0) * 12);
            R(4) = w->procs;
            R(12) = R(4) + R(0);
            GM_CALLV(a + 0x48, F_PTMF_SCALL, 0);             /* (this->*Proc_tbl[mAction])() */
            R(3) = R(31) + 20;
            GM_CALLV(a + 0x54, F_EXEC_ANIM, 0);
            R(12) = gm_u32(R(31) + 28);
            R(3) = R(31) + 20;
            R(12) = gm_u32(R(12) + 16);
            ctx->ctr = R(12);
            GM_CALLV(a + 0x68, R(12), 0);                    /* mLyt.calc() */
        }
    }
    R(3) = 1;
    R(0) = lr;
}
/* draw(): the layout's entry (a tail call), once it's built */
static void wipe_draw(GM_CTX, const wipe_t *w) {
    R(0) = gm_u8(R(3) + w->made);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) return;
    R(3) = R(3) + 20;
    GM_TAIL(F_LYT_ENTRY, 0);
}
/* OpenSetup() / CloseSetup(): start the window's animation (open: outWindow, close: inWindow;
   the pipe picks one of two by the player's height on screen), then wait for it */
static void wipe_setup(GM_CTX, const wipe_t *w, int kind, int close) {
    uint32_t a = close ? w->close : w->open;
    GM_FN(a); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    R(3) = R(3) + 20;
    GM_CALLV(a + 0x1C, F_DISABLE_ALL, 0);
    if (kind == W_DOKAN) {
        R(3) = R(31);
        GM_CALLV(a + 0x24, w->extra, 0);
        int up = cmps(ctx, (int32_t)R(3), 0) != 0;
        R(3) = R(31) + 20; R(4) = close ? (up ? 3 : 0) : (up ? 2 : 1); R(5) = 0;
        GM_CALLV(a + (up ? 0x3C : 0x50), F_ENABLE_ANIM, 0);
    } else {
        R(3) = R(31) + 20; R(4) = close ? 0 : 1; R(5) = 0;
        GM_CALLV(a + 0x2C, F_ENABLE_ANIM, 0);
    }
    R(0) = 1;
    gm_set_u32(R(31) + w->act, 1);
    if (kind == W_CIRCLE) {
        R(3) = R(31);
        GM_CALLV(a + 0x3C, w->extra, 0);                     /* CenterPosSet() */
    }
    R(0) = lr;
}
/* AnimeEndCheck(): when the animation is done, the fade is complete */
static void wipe_end(GM_CTX, const wipe_t *w, int kind) {
    GM_FN(w->end); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr, a = w->end;
    R(4) = (uint32_t)-1;
    R(31) = R(3);
    R(3) = R(3) + 20;
    GM_CALLV(a + 0x20, F_IS_ANIM_ON, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) {
        R(12) = gm_u32(R(31));
        R(3) = R(31);
        R(12) = gm_u32(R(12) + 16);
        ctx->ctr = R(12);
        GM_CALLV(a + 0x3C, R(12), 0);                        /* getStatus() */
        if (cmps(ctx, (int32_t)R(3), 2) == 0) {              /* FADE_IN: hidden, the root pane off */
            R(0) = gm_u8(R(31) + 8);
            R(3) = 1;
            gm_set_u32(R(31) + 4, R(3));
            R(0) = R(0) | 1;
            R(3) = gm_u32(R(31) + 428);
            gm_set_u8(R(31) + 8, (uint8_t)R(0));
            R(0) = gm_u8(R(3) + 187) & 0xFEu;
            gm_set_u8(R(3) + 187, (uint8_t)R(0));
        } else {                                             /* FADE_OUT: opaque */
            R(0) = gm_u8(R(31) + 8);
            R(3) = 0;
            gm_set_u32(R(31) + 4, R(3));
            R(0) = R(0) | 2;
            gm_set_u8(R(31) + 8, (uint8_t)R(0));
        }
        if (kind == W_CIRCLE) {                              /* mCenterPos = 0 */
            uint32_t z = gm_u32(R(2) - 32400);
            ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(2) - 32400);
            gm_set_u32(R(31) + 436, z); gm_set_u32(R(31) + 440, z);
        }
        R(0) = 3;
        gm_set_u32(R(31) + w->act, 3);
    }
    R(0) = lr;
}
/* setStatus(status): opaque / hidden at once - the window's alpha, the animation run backwards,
   the root pane on, the layout's animations and calc */
static void wipe_set(GM_CTX, const wipe_t *w) {
    GM_FN(w->set); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr, a = w->set;
    int c = cmps(ctx, (int32_t)R(4), 0);
    R(31) = R(3);
    int k = -1;
    if (c == 0) k = 0;
    else if (cmps(ctx, (int32_t)R(4), 1) == 0) k = 1;
    if (k >= 0) {
        uint32_t o = k ? 0x60 : 0;                           /* (the second copy of the code) */
        R(5) = gm_u32(R(3) + 432);
        R(0) = (uint32_t)k;
        gm_set_u32(R(3) + 4, R(0));
        R(0) = k ? 0 : 255;
        R(4) = k ? 0 : 1;
        R(3) = R(3) + 20;
        gm_set_u8(R(5) + 184, (uint8_t)R(0));
        R(5) = 0;
        GM_CALLV(a + 0x40 + o, F_RESET_ANIM, 0);
        R(4) = gm_u32(R(31) + 428);
        R(3) = R(31) + 20;
        R(0) = gm_u8(R(4) + 187);
        R(0) = R(0) & 0xFEu;
        R(0) = R(0) | 1;
        gm_set_u8(R(4) + 187, (uint8_t)R(0));
        GM_CALLV(a + 0x5C + o, F_EXEC_ANIM, 0);
        R(12) = gm_u32(R(31) + 28);
        R(3) = R(31) + 20;
        R(12) = gm_u32(R(12) + 16);
        ctx->ctr = R(12);
        GM_CALLV(a + 0x70 + o, R(12), 0);
    }
    R(0) = lr;
}
/* fadeIn() / fadeOut(): mFaderBase_c's, then the open / close set-up as the next action */
static void wipe_fade(GM_CTX, const wipe_t *w, int out) {
    uint32_t a = out ? w->fout : w->fin;
    GM_FN(a); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(a + 0x18, out ? F_FADE_OUT : F_FADE_IN, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) { R(0) = out ? 2 : 0; gm_set_u32(R(31) + w->act, R(0)); }
    R(0) = lr;
}

/* ================================================================== mWipeFader_c
   +20 the texture matrix (3x4), +68 the progress (u8), +72 the aspect ratio factor, +76 the
   texture, +80 / +84 its width / height. Its calcMtx and draw stay recompiled (draw writes the
   GX FIFO). */
#define WF_CALC_MTX_VT 40                /* (the vtable slot calc() calls: calcMtx) */
static void wf_calc(GM_CTX) {
    GM_FN(0x80170D80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3);
    GM_CALLV(0x80170D9Cu, 0x8016DD80u, 0);                   /* mFaderBase_c::calc */
    R(5) = gm_u16(R(30) + 12);
    R(31) = R(3);
    R(4) = gm_u16(R(30) + 10);
    cr_cmp_u(ctx, 0, R(5), R(4));
    if (R(5) > R(4)) R(5) = R(4);
    R(0) = gm_u32(R(30) + 4);
    int st = (int32_t)R(0);
    if (cmps(ctx, st, 0) == 0) { R(0) = 255; gm_set_u8(R(30) + 68, 255); }
    else if (cmps(ctx, st, 1) == 0) { R(0) = 0; gm_set_u8(R(30) + 68, 0); }
    else if (cmps(ctx, st, 2) == 0 || cmps(ctx, st, 3) == 0) {
        R(3) = R(5) & 0xFFFFu;
        R(0) = (R(5) << 8) & 0xFFFF00u;
        R(0) = R(0) - R(3);
        R(0) = divw((int32_t)R(0), (int32_t)R(4));
        if (st == 2) { uint32_t v = R(0); R(0) = 0xFFu - v; ctx->xer_ca = 0xFFu >= v; }
        gm_set_u8(R(30) + 68, (uint8_t)R(0));
    }
    R(12) = gm_u32(R(30));
    R(3) = R(30);
    R(12) = gm_u32(R(12) + WF_CALC_MTX_VT);
    ctx->ctr = R(12);
    GM_CALLV(0x80170E38u, R(12), 0);                         /* calcMtx() */
    R(3) = R(31);
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_WIPE_VERIFY        /* (testing: RT_GM_VERIFY_REGS on these - their layout calls run twice then) */
#define E(name) GM_HLE_INT(name, A(0), 452)
#else
#define E(name) GM_HLE(name)
#endif
#define WIPE_ENTRIES(k, calc, draw, open, end, close, set, fin, fout) \
    E(calc)  { wipe_calc(GM_PASS, &WIPES[k]); } \
    E(draw)  { wipe_draw(GM_PASS, &WIPES[k]); } \
    E(open)  { wipe_setup(GM_PASS, &WIPES[k], k, 0); } \
    E(end)   { wipe_end(GM_PASS, &WIPES[k], k); } \
    E(close) { wipe_setup(GM_PASS, &WIPES[k], k, 1); } \
    E(set)   { wipe_set(GM_PASS, &WIPES[k]); } \
    E(fin)   { wipe_fade(GM_PASS, &WIPES[k], 0); } \
    E(fout)  { wipe_fade(GM_PASS, &WIPES[k], 1); }
WIPE_ENTRIES(W_CIRCLE, fn_8001B580, fn_8001B600, fn_8001B8D0, fn_8001B920, fn_8001B9D0, fn_8001BA20, fn_8001BB10, fn_8001BB50)   /* dWipeCircle_c */
WIPE_ENTRIES(W_DOKAN,  fn_8001BD70, fn_8001BDF0, fn_8001BE10, fn_8001BE80, fn_8001BF90, fn_8001C000, fn_8001C0F0, fn_8001C130)   /* dWipeDokan_c */
WIPE_ENTRIES(W_KUPPA,  fn_8001C340, fn_8001C3C0, fn_8001C3E0, fn_8001C430, fn_8001C4D0, fn_8001C520, fn_8001C610, fn_8001C650)   /* dWipeKuppa_c */
WIPE_ENTRIES(W_MARIO,  fn_8001C860, fn_8001C8E0, fn_8001C900, fn_8001C950, fn_8001C9F0, fn_8001CA40, fn_8001CB30, fn_8001CB70)   /* dWipeMario_c */

/* mWipeFader_c (off: hle_funcs.txt) */
GM_HLE(fn_80170D30) { gm_set_u32(A(0) + 76, A(1)); gm_set_u32(A(0) + 80, A(2)); gm_set_u32(A(0) + 84, A(3)); }   /* ::setTexture */
GM_HLE(fn_80170D40) {                                                                               /* ::setStatus */
    int c = cmps(ctx, (int32_t)R(4), 0);
    if (c == 0) { R(4) = 0; R(0) = 255; gm_set_u32(R(3) + 4, 0); gm_set_u8(R(3) + 68, 255); return; }
    if (cmps(ctx, (int32_t)R(4), 1) != 0) return;
    R(4) = 1; R(0) = 0; gm_set_u32(R(3) + 4, 1); gm_set_u8(R(3) + 68, 0);
}
GM_HLE(fn_80170D80) { wf_calc(GM_PASS); }                                                           /* ::calc */
