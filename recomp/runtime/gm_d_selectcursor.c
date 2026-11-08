/* gm_d_selectcursor.c - dSelectCursor_c, the menus' selection cursor (five cursor layouts over
 * select_cursor_04.brlyt): the profile's create, ctor / dtor, its Layout_c ctor / dtor, create
 * (the archive, then per layout build / animation / pane registers, hidden, its draw order, the
 * loop animation), doDelete, PosSet (the cursor and its four corners around the pane, the fade
 * out), Cancel, SetPane, SetAlpha. Track B (gm.h, docs/DECOMP.md), instance 1. execute / draw
 * are in gm_d_smallscore.c (named there in part 63).
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_SelectCursor.cpp) and checked against the
 * recompiled USA rev 2 code (0x8010C020-0x8010C37C, 0x8010C490-0x8010C9CC). Register-exact
 * (R(n)): PosSet keeps the PowerPC code's two-corners-per-iteration loop, its fneg / frsp pairs
 * (ps0 only) and stack temporaries; SetPane its mulhw divisions by 3 and the copied matrix.
 *
 * dSelectCursor_c: +112 the ResAccMultLoader_c, +324 five Layout_c of 612 bytes (each a
 * LytBase_c, +336 its draw order; +408 root pane (+732 from the class), +412 / 4 pictures
 * (+736), +428 / 5 null panes (+752), +448 on (+772), +449 the pane name (+773), +552 / 556 the
 * pane size (+876 / 880), +560 / 564 the pane offset (+884 / 888), +568 / 572 scale (+892 /
 * 896), +576 / 580 translation (+900 / 904), +588 / 592 root offset (+912 / 916), +596 (+920),
 * +600 / 601 base position H / V (+924 / 925), +604 alpha (+928), +608 fade (+932)), +3384 the
 * layout loaded; m_instance r13 - 21432. */
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
/* fneg then frsp: ps0 only (the PowerPC code's -(a * b) rounded) */
static inline void fneg_rsp(ppc_context *ctx, int n) { ctx->f[n].u ^= 0x8000000000000000ull; ctx->f[n].d = frsp(ctx->f[n].d); }

#define SDA_INSTANCE     21432
#define SDA_EMPTY        25696          /* "" */
#define SDA_ANM_NAMES    25736          /* AnmNameTbl */
#define SDA_GROUP_NAMES  25732          /* GROUP_NAME_DT */
#define STRS             (0x80320000u + 9936u)   /* +112 PPANE names, +140 NPANE names, +160 the archive, +200 the brlyt */
#define F_ALLOC_BLOCK    0x801628C0u    /* (the profile's allocation) */
#define F_FREE_HEAP1     0x80162920u
#define F_BASE_CT        0x8006C420u    /* dBase_c::dBase_c */
#define F_BASE_DT        0x8006C490u
#define F_LOADER_CT      0x80006AA0u
#define F_LOADER_DT      0x80006AF0u
#define F_LOADER_REQ     0x80006BE0u    /* d2d::ResAccMultLoader_c::request */
#define F_LOADER_REMOVE  0x80006BF0u
#define F_ROOT_PANE      0x80007220u
#define F_LYT_CT         0x800C8950u    /* LytBase_c::LytBase_c */
#define F_LYT_DT         0x800C89A0u
#define F_LYT_ANIME_RES  0x800C8FB0u
#define F_LYT_GROUPS     0x800C90F0u
#define F_LYT_PPANES     0x800C8E40u
#define F_LYT_NPANES     0x800C8D60u
#define F_LYT_LOOP_ANIM  0x800C9380u
#define F_LYT_DELETE     0x800C9930u
#define F_STRCPY         0x802E1938u
#define F_CONSTRUCT_ARR  0x802DC9A0u
#define F_DESTROY_ARR    0x802DCA98u
#define F_OP_DELETE      0x802B9280u
#define F_CANCEL         0x8010C780u
#define LAYOUT_CT        0x8010C0C0u
#define LAYOUT_DT        0x8010C110u

/* ================================================================== life */
static void sc_profile(GM_CTX) {                                            /* the profile: new dSelectCursor_c */
    GM_FN(0x8010C020); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(3) = 3388;
    GM_CALLV(0x8010C034u, F_ALLOC_BLOCK, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) GM_CALLV(0x8010C040u, 0x8010C050u, 0);
    R(0) = lr;
}
static void sc_ctor(GM_CTX) {
    GM_FN(0x8010C050); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x8010C068u, F_BASE_CT, 0);
    R(4) = 0x80320000u; R(3) = R(31) + 112;
    R(4) = R(4) + 10160;
    gm_set_u32(R(31) + 96, R(4));                                            /* the vtable */
    GM_CALLV(0x8010C07Cu, F_LOADER_CT, 0);
    R(4) = LAYOUT_CT; R(5) = LAYOUT_DT;
    R(3) = R(31) + 324; R(6) = 612; R(7) = 5;
    GM_CALLV(0x8010C09Cu, F_CONSTRUCT_ARR, 0);
    gm_set_u32(R(13) - SDA_INSTANCE, R(31));
    R(0) = 0; R(3) = R(31);
    gm_set_u8(R(31) + 3384, 0);
    R(0) = lr;
}
static void sc_layout_ctor(GM_CTX) {
    GM_FN(0x8010C0C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x8010C0D8u, F_LYT_CT, 0);
    FB(0, LF(R(2) - 23928));                                                 /* 0.0f */
    R(3) = R(31);
    SF(R(31) + 552, F(0)); SF(R(31) + 556, F(0)); SF(R(31) + 560, F(0)); SF(R(31) + 564, F(0));
    R(0) = lr;
}
static void sc_layout_dtor(GM_CTX) {
    GM_FN(0x8010C110); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(4) = (uint32_t)-1;
        GM_CALLV(0x8010C13Cu, F_LYT_DT, 0);
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x8010C14Cu, F_OP_DELETE, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
static void sc_dtor(GM_CTX) {
    GM_FN(0x8010C170); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(0) = 0;
        R(4) = LAYOUT_DT;
        gm_set_u32(R(13) - SDA_INSTANCE, 0);
        R(5) = 612; R(6) = 5;
        R(3) = R(3) + 324;
        GM_CALLV(0x8010C1B4u, F_DESTROY_ARR, 0);
        R(3) = R(30) + 112; R(4) = (uint32_t)-1;
        GM_CALLV(0x8010C1C0u, F_LOADER_DT, 0);
        R(3) = R(30); R(4) = 0;
        GM_CALLV(0x8010C1CCu, F_BASE_DT, 0);
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x8010C1DCu, F_FREE_HEAP1, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
/* create(): once the archive is in, the five layouts */
static void sc_create(GM_CTX) {
    GM_FN(0x8010C200); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 48;
    R(0) = gm_u8(R(3) + 3384);
    R(29) = 0x80320000u;
    R(23) = R(3);
    {
        int c = cmps(ctx, (int32_t)R(0), 0);
        R(29) = R(29) + 9936;
        if (c != 0) { R(3) = 1; goto out; }
    }
    R(3) = R(3) + 112; R(4) = R(29) + 160;
    GM_CALLV(0x8010C240u, F_LOADER_REQ, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
    R(0) = R(23) + 112;
    gm_set_u32(R(23) + 456, R(0));                                           /* each layout's accessor */
    R(27) = R(23); R(28) = R(23) + 324;
    gm_set_u32(R(23) + 1068, R(0));
    R(26) = R(23) + 736; R(25) = R(23) + 752; R(24) = 0;
    gm_set_u32(R(23) + 1680, R(0));
    R(31) = 147; R(30) = 14;
    gm_set_u32(R(23) + 2292, R(0)); gm_set_u32(R(23) + 2904, R(0));
    for (;;) {
        R(12) = gm_u32(R(28) + 8); R(3) = R(28); R(4) = R(29) + 200; R(5) = 0;
        R(12) = gm_u32(R(12) + 20); ctx->ctr = R(12);
        GM_CALLV(0x8010C2A0u, R(12), 0);                                     /* build("select_cursor_04.brlyt") */
        R(3) = R(28); R(4) = R(13) - SDA_ANM_NAMES; R(5) = 1;
        GM_CALLV(0x8010C2B0u, F_LYT_ANIME_RES, 0);
        R(3) = R(28); R(4) = R(13) - SDA_GROUP_NAMES; R(5) = R(2) - 13448; R(6) = 1;
        GM_CALLV(0x8010C2C4u, F_LYT_GROUPS, 0);
        R(3) = R(28);
        GM_CALLV(0x8010C2CCu, F_ROOT_PANE, 0);
        gm_set_u32(R(27) + 732, R(3));
        R(3) = R(28); R(5) = R(26); R(4) = R(29) + 112; R(6) = 4;
        GM_CALLV(0x8010C2E4u, F_LYT_PPANES, 0);
        R(3) = R(28); R(5) = R(25); R(4) = R(29) + 140; R(6) = 5;
        GM_CALLV(0x8010C2F8u, F_LYT_NPANES, 0);
        R(5) = gm_u32(R(27) + 732);
        R(3) = R(23); R(4) = R(24);
        R(0) = gm_u8(R(5) + 187) & 0xFE;
        gm_set_u8(R(5) + 187, (uint8_t)R(0));                                /* hidden */
        GM_CALLV(0x8010C314u, F_CANCEL, 0);
        if (cmps(ctx, (int32_t)R(24), 4) == 0) gm_set_u8(R(27) + 336, (uint8_t)R(30));
        else gm_set_u8(R(27) + 336, (uint8_t)R(31));
        R(3) = R(28); R(4) = 0;
        GM_CALLV(0x8010C334u, F_LYT_LOOP_ANIM, 0);
        R(24) = R(24) + 1;
        R(27) = R(27) + 612;
        int c = cmps(ctx, (int32_t)R(24), 5);
        R(26) = R(26) + 612; R(25) = R(25) + 612; R(28) = R(28) + 612;
        if (c >= 0) break;
        GM_LOOP();
    }
    R(0) = 1;
    gm_set_u8(R(23) + 3384, 1);
    R(3) = 1;
out:
    R(11) = f + 48;
    R(0) = lr;
}
/* doDelete(): the archive, then each layout */
static void sc_delete(GM_CTX) {
    GM_FN(0x8010C490); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3);
    R(3) = R(3) + 112;
    GM_CALLV(0x8010C4B0u, F_LOADER_REMOVE, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
    R(31) = R(30) + 324; R(30) = 0;
    for (;;) {
        R(3) = R(31);
        GM_CALLV(0x8010C4D0u, F_LYT_DELETE, 0);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
        R(30) = R(30) + 1; R(31) = R(31) + 612;
        if (cmps(ctx, (int32_t)R(30), 5) >= 0) break;
        GM_LOOP();
    }
    R(3) = 1;
out:
    R(0) = lr;
}

/* ================================================================== PosSet */
/* one corner (r9 its number): x = -(halfW * sx) - h or halfW * sx + h; y = halfH * sy + v or
   -(halfH * sy) - v; xneg already decided by the caller's compares */
static void sc_corner(GM_CTX, gptr f, int xneg) {
    FB(4, frsp(F(0) * F(2)));
    if (xneg) { fneg_rsp(ctx, 4); FB(4, frsp(F(4) - F(6))); }
    else FB(4, frsp(F(4) + F(6)));
    SF(f + 28, F(4));
    R(0) = R(9) - 1;
    if (cmpu(ctx, R(0), 1) > 0) { FB(4, frsp(F(1) * F(3))); fneg_rsp(ctx, 4); FB(4, frsp(F(4) - F(7))); }
    else { FB(4, frsp(F(1) * F(3))); FB(4, frsp(F(4) + F(7))); }
    SF(f + 32, F(4));
}
/* PosSet(i): the cursor shown, put on the pane's centre (by its base position), the corners
   around it; the fade out (26 a frame, then Cancel) */
static void sc_posset(GM_CTX) {
    GM_FN(0x8010C510); GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(8) = (uint32_t)((int32_t)R(4) * 612);
    FB(3, LF(R(2) - 23924));                                                 /* 0.5f */
    R(6) = R(3) + R(8);
    R(5) = gm_u32(R(6) + 732);
    R(0) = gm_u8(R(5) + 187) & 0xFE; R(0) = R(0) | 1;
    gm_set_u8(R(5) + 187, (uint8_t)R(0));                                    /* SetVisible(true) */
    R(0) = gm_u8(R(6) + 924);
    FB(1, LF(R(6) + 900)); FB(0, LF(R(6) + 912));
    int c = cmps(ctx, (int32_t)R(0), 0);
    FB(4, LF(R(6) + 876));
    FB(5, frsp(F(1) + F(0)));
    FB(2, LF(R(6) + 880));
    FB(0, frsp(F(4) * F(3)));                                                /* halfW */
    FB(1, frsp(F(2) * F(3)));                                                /* halfH */
    SF(f + 8, F(5));
    FB(2, LF(R(6) + 892)); FB(3, LF(R(6) + 896));                            /* scale x / y */
    if (c == 0) { FB(4, frsp(F(0) * F(2))); FB(4, frsp(F(5) + F(4))); SF(f + 8, F(4)); }
    else if (cmpu(ctx, R(0), 2) == 0) { FB(4, frsp(F(0) * F(2))); FB(4, frsp(F(5) - F(4))); SF(f + 8, F(4)); }
    R(5) = R(3) + R(8);
    FB(5, LF(R(5) + 904)); FB(4, LF(R(5) + 916));
    R(0) = gm_u8(R(5) + 925);
    FB(5, frsp(F(5) + F(4)));
    c = cmps(ctx, (int32_t)R(0), 0);
    SF(f + 12, F(5));
    if (c == 0) { FB(4, frsp(F(1) * F(3))); FB(4, frsp(F(5) - F(4))); SF(f + 12, F(4)); }
    else if (cmpu(ctx, R(0), 2) == 0) { FB(4, frsp(F(1) * F(3))); FB(4, frsp(F(5) + F(4))); SF(f + 12, F(4)); }
    R(6) = gm_u32(R(6) + 732);
    R(5) = R(3) + R(8);
    FB(6, LF(f + 8));
    R(0) = 2;
    SF(R(6) + 44, F(6));                                                     /* the root's translation */
    R(7) = R(5) + 4;
    FB(4, LF(f + 12));
    R(9) = 1;
    SF(R(6) + 48, F(4));
    FB(5, LF(R(2) - 23928));                                                 /* 0.0f */
    SF(R(6) + 52, F(5));
    SF(f + 16, F(6));
    FB(6, LF(R(5) + 884));                                                   /* h offset */
    SF(f + 20, F(4));
    FB(7, LF(R(5) + 888));                                                   /* v offset */
    SF(f + 24, F(5));
    ctx->ctr = R(0);
    for (;;) {
        int xneg = cmps(ctx, (int32_t)R(9), 1) == 0 || cmps(ctx, (int32_t)R(9), 3) == 0;
        sc_corner(GM_PASS, f, xneg);
        R(5) = gm_u32(R(7) + 752);
        R(9) = R(9) + 1;
        FB(4, LF(f + 28));
        int c1 = cmps(ctx, (int32_t)R(9), 1);
        SF(R(5) + 44, F(4));
        FB(4, LF(f + 32));
        SF(R(5) + 48, F(4));
        SF(f + 36, F(5)); SF(R(5) + 52, F(5));
        xneg = c1 == 0 || cmps(ctx, (int32_t)R(9), 3) == 0;
        sc_corner(GM_PASS, f, xneg);
        R(5) = gm_u32(R(7) + 756);
        R(7) = R(7) + 8;
        FB(4, LF(f + 28));
        R(9) = R(9) + 1;
        SF(R(5) + 44, F(4));
        FB(4, LF(f + 32));
        SF(R(5) + 48, F(4));
        SF(f + 36, F(5)); SF(R(5) + 52, F(5));
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    R(6) = R(3) + R(8);
    R(0) = gm_u8(R(6) + 932);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(5) = gm_u32(R(6) + 928);
        R(0) = R(5) - 26;
        gm_set_u32(R(6) + 928, R(0));
        R(5) = gm_u32(R(6) + 752);
        gm_set_u8(R(5) + 184, (uint8_t)R(0));                                /* the cursor pane's alpha */
        R(0) = gm_u32(R(6) + 928);
        if (cmps(ctx, (int32_t)R(0), 0) < 0) {
            R(0) = 0;
            gm_set_u32(R(6) + 928, 0); gm_set_u8(R(6) + 932, 0);
            GM_CALLV(0x8010C770u, F_CANCEL, 0);
        }
    }
    R(0) = lr;
}
/* Cancel(i): off, no pane name, hidden */
static void sc_cancel(GM_CTX) {
    GM_FN(0x8010C780); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = (uint32_t)((int32_t)R(4) * 612);
    R(30) = R(3);
    R(3) = R(3) + R(31);
    R(0) = gm_u8(R(3) + 772);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(0) = 0;
        gm_set_u8(R(3) + 772, 0);
        R(3) = R(3) + 773; R(4) = R(13) - SDA_EMPTY;
        GM_CALLV(0x8010C7C0u, F_STRCPY, 0);
        R(3) = R(30) + R(31);
        R(3) = gm_u32(R(3) + 732);
        R(0) = gm_u8(R(3) + 187) & 0xFE;
        gm_set_u8(R(3) + 187, (uint8_t)R(0));
    }
    R(0) = lr;
}
/* SetPane(pane, i, forceTop): the cursor on the pane - its name, size, global matrix, base
   position (H / V = basePosition % 3 / basePosition / 3), offsets 0, alpha 255; the draw orders */
static void sc_set_pane(GM_CTX) {
    GM_FN(0x8010C7F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 80;
    R(26) = (uint32_t)((int32_t)R(5) * 612);
    R(30) = R(3); R(31) = R(4);
    R(0) = 1;
    R(3) = R(3) + R(26);
    R(27) = R(6);
    gm_set_u8(R(3) + 772, 1);
    R(3) = R(3) + 773; R(4) = R(4) + 188;
    GM_CALLV(0x8010C82Cu, F_STRCPY, 0);
    R(3) = R(30) + R(26);
    FB(0, LF(R(31) + 76));
    SF(R(3) + 876, F(0));
    R(4) = 0x55550000u;
    R(6) = R(4) + 21846;                                                     /* 0x55555556: / 3 */
    int c = cmps(ctx, (int32_t)R(27), 0);
    FB(1, LF(R(31) + 80));
    R(4) = 255;
    SF(R(3) + 880, F(1));
    R(0) = 0;
    FB(0, LF(R(2) - 23928));
    R(5) = gm_u32(R(31) + 144);
    gm_set_u32(f + 20, R(5));
    R(8) = gm_u32(R(31) + 132); R(26) = gm_u32(R(31) + 136); R(27) = gm_u32(R(31) + 140);
    R(28) = gm_u32(R(31) + 148); R(7) = gm_u32(R(31) + 152); R(29) = gm_u32(R(31) + 156);
    R(5) = gm_u32(R(31) + 160); R(12) = gm_u32(R(31) + 164); R(11) = gm_u32(R(31) + 168);
    R(10) = gm_u32(R(31) + 172); R(9) = gm_u32(R(31) + 176);
    gm_set_u32(f + 36, R(5));
    FB(1, LF(f + 20)); SF(R(3) + 900, F(1));
    FB(2, LF(f + 36));
    gm_set_u32(f + 8, R(8));
    SF(R(3) + 904, F(2));
    FB(1, LF(f + 8));
    gm_set_u32(f + 28, R(7));
    SF(R(3) + 892, F(1));
    FB(1, LF(f + 28));
    SF(R(3) + 896, F(1));
    R(8) = gm_u8(R(31) + 186);                                               /* the base position */
    gm_set_u32(f + 12, R(26));
    R(7) = (uint32_t)(((int64_t)(int32_t)R(6) * (int32_t)R(8)) >> 32);
    gm_set_u32(f + 16, R(27)); gm_set_u32(f + 24, R(28));
    R(5) = R(7) >> 31;
    gm_set_u32(f + 32, R(29));
    R(5) = R(7) + R(5);
    R(5) = (uint32_t)((int32_t)R(5) * 3);
    gm_set_u32(f + 40, R(12)); gm_set_u32(f + 44, R(11));
    R(5) = R(8) - R(5);
    gm_set_u8(R(3) + 924, (uint8_t)R(5));
    R(5) = gm_u8(R(31) + 186);
    gm_set_u32(f + 48, R(10));
    R(6) = (uint32_t)(((int64_t)(int32_t)R(6) * (int32_t)R(5)) >> 32);
    gm_set_u32(f + 52, R(9));
    R(5) = R(6) >> 31;
    R(5) = R(6) + R(5);
    gm_set_u8(R(3) + 925, (uint8_t)R(5));
    SF(R(3) + 884, F(0)); SF(R(3) + 888, F(0)); SF(R(3) + 912, F(0)); SF(R(3) + 916, F(0)); SF(R(3) + 920, F(0));
    gm_set_u32(R(3) + 928, R(4));
    gm_set_u8(R(3) + 932, 0);
    if (c != 0) { R(0) = 152; gm_set_u8(R(3) + 336, 152); }
    else {
        R(0) = 147; R(3) = 14;
        gm_set_u8(R(30) + 336, 147); gm_set_u8(R(30) + 948, 147); gm_set_u8(R(30) + 1560, 147);
        gm_set_u8(R(30) + 2172, 147); gm_set_u8(R(30) + 2784, 14);
    }
    R(11) = f + 80;
    R(0) = lr;
}
/* SetAlpha(pane, i): the pane's global alpha on the four pictures */
static void sc_set_alpha(GM_CTX) {
    R(0) = (uint32_t)((int32_t)R(5) * 612);
    R(5) = gm_u8(R(4) + 185);
    R(4) = R(3) + R(0);
    for (int i = 0; i < 4; i++) { R(3) = gm_u32(R(4) + 736 + 4 * i); gm_set_u8(R(3) + 184, (uint8_t)R(5)); }
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_SC_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_SC_COUNT)    /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_8010C020, 4)    { sc_profile(GM_PASS); }                                      /* the profile's create */
E(fn_8010C050, 3388) { sc_ctor(GM_PASS); }                                         /* dSelectCursor_c::dSelectCursor_c */
E(fn_8010C0C0, 612)  { sc_layout_ctor(GM_PASS); }                                  /* ::Layout_c::Layout_c */
E(fn_8010C110, 612)  { sc_layout_dtor(GM_PASS); }                                  /* ::Layout_c::~Layout_c */
E(fn_8010C170, 3388) { sc_dtor(GM_PASS); }                                         /* ::~dSelectCursor_c */
E(fn_8010C200, 3388) { sc_create(GM_PASS); }                                       /* ::create */
E(fn_8010C490, 3388) { sc_delete(GM_PASS); }                                       /* ::doDelete */
E(fn_8010C510, 3388) { sc_posset(GM_PASS); }                                       /* ::PosSet */
E(HideSelectCursor, 3388) { sc_cancel(GM_PASS); }                                  /* ::Cancel */
E(fn_8010C7F0, 3388) { sc_set_pane(GM_PASS); }                                     /* ::SetPane */
E(fn_8010C9A0, 4)    { sc_set_alpha(GM_PASS); }                                    /* ::SetAlpha */
