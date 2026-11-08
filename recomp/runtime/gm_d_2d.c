/* gm_d_2d.c - d2d: the game's 2D layer over mLib m2d - the draw-list wrappers, d2d::Multi_c (the
 * game's layouts: calc, draw with the 4:3 / 16:9 orthographic screen and the scissor, build, the
 * find-by-name helpers with their DynamicCast), d2d::ResAccMult_c's getResource / GetFont / creater.
 * Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_2d.cpp) and checked against the recompiled
 * USA rev 2 code (0x800067A0-0x8000760F). Register-exact (R(n)); draw keeps the PowerPC code's
 * stack temporaries (the 0x43300000 int -> double conversions, the scale vector) and its
 * __cvt_fp2unsigned calls. The ArcResourceAccessor pieces the mod replaces (0x80006930,
 * 0x80006A50) and the constructors stay recompiled.
 *
 * Multi_c: +16 nw4r::lyt::Layout (+16 +16 its root pane), +48 the DrawInfo (+52 its view matrix,
 * +100 the view rect), +132 the resource accessor, +136 / +140 the position, +144 the scissor
 * (x, y, w, h floats), +160 scissor on, +164 flags (1: Animate's option). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define LF(a) ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

#define F_M2D_DRAW        0x80163280u
#define F_M2D_BEFORE      0x80163300u
#define F_M2D_AFTER       0x80163390u
#define F_M2D_BETWEEN     0x80163420u
#define F_M2D_ENTRY       0x80163850u   /* m2d::Base_c::entry */
#define F_M3D_PROC_SETUP  0x80164FD0u
#define F_MTX_IDENTITY    0x801C04D0u
#define F_MTX_TRANS_APPLY 0x801C0C10u
#define F_LAYOUT_RECT     0x802AD520u   /* nw4r::lyt::Layout::GetLayoutRect */
#define F_SCREEN_CT       0x802D0CC0u   /* EGG::Screen::Screen */
#define F_ASPECT          0x800B54B0u   /* dGameCom::GetAspectRatio */
#define F_RESET_ORTHO     0x802C6AE0u   /* EGG::Frustum::ResetOrthographic */
#define F_SET_PROJ_GX     0x802D0F40u   /* EGG::Screen::SetProjectionGX */
#define F_GX_GET_SCISSOR  0x801C9CD0u
#define F_GX_SET_SCISSOR  0x801C9C60u
#define F_CVT_FP2U        0x802DCC4Cu   /* __cvt_fp2unsigned */
#define F_OP_DELETE       0x802B9280u
#define F_FONT_INDEX      0x800B1410u   /* dFontMng_c::getResFontIndex */
#define F_FONT_GET        0x800B1310u   /* dFontMng_c::getFont */
#define F_FIND_PANE       0x80007300u
#define SDA_TI_TEXTBOX    18600         /* (r13 - : nw4r::lyt::TextBox's type info) */
#define SDA_TI_PICTURE    18608
#define SDA_TI_WINDOW     18592

/* a virtual call: r12 = (*this)[off], CTR = r12 */
static inline void vcall(GM_CTX, uint32_t ra, uint32_t self, uint32_t off) {
    R(12) = gm_u32(self); R(12) = gm_u32(R(12) + off); ctx->ctr = R(12);
    GM_CALLV(ra, R(12), 0);
}

/* ================================================================== Multi_c */
/* calcBefore(): mLayout.Animate(flags & 1) (a tail call) */
static void mu_calc_before(GM_CTX) {
    R(0) = gm_u32(R(3) + 164);
    R(4) = 0;
    R(0) = R(0) & 1;
    if (cmps(ctx, (int32_t)R(0), 0) != 0) R(4) = 1;
    R(3) = R(3) + 16; R(12) = gm_u32(R(3));
    R(12) = gm_u32(R(12) + 56); ctx->ctr = R(12);
    GM_TAIL(R(12), 0);
}
/* calcAfter(): the view rect from the layout, then mLayout.CalculateMtx(mDrawInfo) */
static void mu_calc_after(GM_CTX) {
    GM_FN(0x80006FA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(31) = R(3);
    R(3) = f + 8; R(4) = R(31) + 16;
    GM_CALLV(0x80006FC0u, F_LAYOUT_RECT, 0);
    FB(0, LF(f + 8));  R(3) = R(31) + 16; SF(R(31) + 100, ctx->f[0].d);
    R(4) = R(31) + 48;
    FB(0, LF(f + 12)); SF(R(31) + 104, ctx->f[0].d);
    FB(0, LF(f + 16)); SF(R(31) + 108, ctx->f[0].d);
    FB(0, LF(f + 20)); SF(R(31) + 112, ctx->f[0].d);
    R(12) = gm_u32(R(31) + 16); R(12) = gm_u32(R(12) + 48); ctx->ctr = R(12);
    GM_CALLV(0x80006FF8u, R(12), 0);
    R(0) = lr;
}
/* calc(): calcBefore, the view matrix (a translation by the position), calcAfter */
static void mu_calc(GM_CTX) {
    GM_FN(0x80006EB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(31) = R(3);
    GM_CALLV(0x80006EC8u, 0x80006F70u, 0);
    R(3) = f + 24;
    GM_CALLV(0x80006ED0u, F_MTX_IDENTITY, 0);
    FB(2, LF(R(31) + 140));
    R(3) = f + 24;
    FB(1, LF(R(31) + 136));
    R(4) = R(3);
    FB(3, LF(R(2) - 32768));
    SF(f + 8, ctx->f[1].d); SF(f + 12, ctx->f[2].d); SF(f + 16, ctx->f[3].d);
    GM_CALLV(0x80006EF4u, F_MTX_TRANS_APPLY, 0);
    for (int i = 0; i < 6; i++) {                                            /* the 3x4 matrix into the DrawInfo */
        R(4) = gm_u32(f + 24 + 8 * i);
        if (i == 0) R(3) = R(31);
        R(0) = gm_u32(f + 28 + 8 * i);
        gm_set_u32(R(31) + 56 + 8 * i, R(0));
        gm_set_u32(R(31) + 52 + 8 * i, R(4));
    }
    GM_CALLV(0x80006F5Cu, 0x80006FA0u, 0);
    R(0) = lr;
}
/* draw(): the orthographic screen over the layout rect (16:9: the x range widened, the scale
   narrowed back), then the layout, inside the scissor if it is on */
static void mu_draw(GM_CTX) {
    GM_FN(0x80007010); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(28) = R(3);
    R(3) = f + 40; R(4) = R(28) + 16;
    GM_CALLV(0x8000705Cu, F_LAYOUT_RECT, 0);
    FB(31, LF(R(2) - 32768));
    R(3) = f + 56;
    FB(30, LF(R(2) - 32756));
    GM_CALLV(0x8000706Cu, F_SCREEN_CT, 0);
    GM_CALLV(0x80007070u, F_ASPECT, 0);
    R(6) = 0x80350000u; R(4) = 0x43300000u;
    R(5) = R(6) + 1248;
    R(0) = gm_u16(R(6) + 1248);                                              /* sTVModeInfo[0].width */
    R(5) = gm_u16(R(5) + 12);                                                /* sTVModeInfo[1].width */
    R(3) = R(3) & 0xFF;
    gm_set_u32(f + 196, R(5));
    R(3) = R(3) - 1;
    R(3) = cntlzw(R(3));
    ctx->f[1].u = ld64(base, R(2) - 32752);                                      /* lfd: ps0 only */
    gm_set_u32(f + 192, R(4));
    R(29) = R(3) >> 5;                                                       /* wide */
    CR0(ctx, R(29));
    ctx->f[0].u = ld64(base, f + 192);
    gm_set_u32(f + 204, R(0));
    FB(29, frsp(ctx->f[0].d - ctx->f[1].d));
    gm_set_u32(f + 200, R(4));
    ctx->f[0].u = ld64(base, f + 200);
    FB(28, frsp(ctx->f[0].d - ctx->f[1].d));
    if (CR_BIT(ctx, 2)) FB(3, LF(f + 40));
    else { FB(0, LF(f + 40)); FB(0, frsp(ctx->f[29].d * ctx->f[0].d)); FB(3, frsp(ctx->f[0].d / ctx->f[28].d)); }
    if (cmps(ctx, (int32_t)R(29), 0) == 0) FB(4, LF(f + 48));
    else { FB(0, LF(f + 48)); FB(0, frsp(ctx->f[29].d * ctx->f[0].d)); FB(4, frsp(ctx->f[0].d / ctx->f[28].d)); }
    ctx->f[5].u = ctx->f[31].u;
    R(0) = 0;
    ctx->f[6].u = ctx->f[30].u;
    gm_set_u32(f + 56, 0);                                                   /* mProjType = ortho */
    FB(1, LF(f + 44));
    R(3) = f + 56;
    FB(2, LF(f + 52));
    GM_CALLV(0x8000710Cu, F_RESET_ORTHO, 0);
    if (cmps(ctx, (int32_t)R(29), 0) != 0) {
        FB(1, frsp(ctx->f[28].d / ctx->f[29].d));
        FB(0, LF(R(2) - 32760));
        SF(f + 28, ctx->f[0].d); SF(f + 32, ctx->f[0].d);
        SF(f + 100, ctx->f[0].d); SF(f + 104, ctx->f[0].d);
        SF(f + 24, ctx->f[1].d); SF(f + 96, ctx->f[1].d);
    }
    R(3) = f + 56;
    GM_CALLV(0x8000713Cu, F_SET_PROJ_GX, 0);
    R(0) = gm_u8(R(28) + 160);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(3) = f + 20; R(4) = f + 16; R(5) = f + 12; R(6) = f + 8;
        GM_CALLV(0x8000715Cu, F_GX_GET_SCISSOR, 0);
        FB(1, LF(R(28) + 156)); GM_CALLV(0x80007164u, F_CVT_FP2U, 0);
        FB(1, LF(R(28) + 152)); R(29) = R(3); GM_CALLV(0x80007170u, F_CVT_FP2U, 0);
        FB(1, LF(R(28) + 148)); R(30) = R(3); GM_CALLV(0x8000717Cu, F_CVT_FP2U, 0);
        FB(1, LF(R(28) + 144)); R(31) = R(3); GM_CALLV(0x80007188u, F_CVT_FP2U, 0);
        R(4) = R(31); R(5) = R(30); R(6) = R(29);
        GM_CALLV(0x80007198u, F_GX_SET_SCISSOR, 0);
        R(12) = gm_u32(R(28) + 16); R(3) = R(28) + 16; R(4) = R(28) + 48;
        R(12) = gm_u32(R(12) + 52); ctx->ctr = R(12);
        GM_CALLV(0x800071B0u, R(12), 0);                                     /* mLayout.Draw(mDrawInfo) */
        R(3) = gm_u32(f + 20); R(4) = gm_u32(f + 16); R(5) = gm_u32(f + 12); R(6) = gm_u32(f + 8);
        GM_CALLV(0x800071C4u, F_GX_SET_SCISSOR, 0);
    } else {
        R(12) = gm_u32(R(28) + 16); R(3) = R(28) + 16; R(4) = R(28) + 48;
        R(12) = gm_u32(R(12) + 52); ctx->ctr = R(12);
        GM_CALLV(0x800071E0u, R(12), 0);
    }
    R(0) = lr;
}
/* findPaneByName(name): the root pane's FindPaneByName(name, true) (a tail call) */
static void mu_find_pane(GM_CTX) {
    R(3) = gm_u32(R(3) + 32);
    R(5) = 1;
    R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 60); ctx->ctr = R(12);
    GM_TAIL(R(12), 0);
}
/* find<T>ByName: the pane if its runtime type is T or derives from it (the type info's parent
   chain, polled on its back-edge) */
static void mu_find_cast(GM_CTX, uint32_t a, uint32_t sda_ti) {
    GM_FN(a); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(a + 0x18, F_FIND_PANE, 0);
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(30) = R(3);
    if (c == 0) { R(3) = 0; goto out; }
    R(31) = R(13) - sda_ti;
    R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 12); ctx->ctr = R(12);
    GM_CALLV(a + 0x3C, R(12), 0);                                            /* GetRuntimeTypeInfo */
    R(0) = 0;
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        for (;;) {
            GM_LOOP();
            if (cmpu(ctx, R(3), R(31)) == 0) { R(0) = 1; break; }
            R(3) = gm_u32(R(3));
            if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(0) = 0; break; }
        }
    }
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(30) = 0;
    R(3) = R(30);
out:
    R(0) = lr;
}
/* a destructor that only frees (0x800075D0) */
static void mu_dtor_free(GM_CTX) {
    GM_FN(0x800075D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(3);
    if (c != 0 && cmps(ctx, (int32_t)R(4), 0) > 0) GM_CALLV(0x800075F8u, F_OP_DELETE, 0);
    R(3) = R(31);
    R(0) = lr;
}

/* ================================================================== ResAccMult_c */
/* InternalAccessor::GetFont(name): dFontMng_c::getFont(getResFontIndex(name)) */
static void ra_get_font(GM_CTX) {
    GM_FN(0x80006A70); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(3) = R(4);
    GM_CALLV(0x80006A84u, F_FONT_INDEX, 0);
    R(3) = R(3) & 0xFF;
    GM_CALLV(0x80006A8Cu, F_FONT_GET, 0);
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
/* (plain GM_HLE below: written but off - no test reaches it; not in hle_funcs.txt) */
#ifdef GM_D2D_VERIFY          /* (testing, as GM_WIPE_VERIFY in gm_d_wipe.c: the calls run twice) */
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_D2D_COUNT)    /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(RenderAllLayouts__Fv, 4) { GM_TAIL(F_M2D_DRAW, 0); }                              /* d2d::draw */
E(fn_800067B0, 4)  { R(3) = 129; GM_TAIL(F_M2D_BEFORE, 0); }                        /* d2d::drawBefore */
E(fn_800067C0, 4)  { R(3) = 128; GM_TAIL(F_M2D_AFTER, 0); }                         /* d2d::drawAfter */
GM_HLE(fn_800067D0)  { GM_TAIL(F_M2D_BETWEEN, 0); }                                   /* d2d::drawBtween */
E(fn_80006A20, 4)  { R(3) = R(3) + 12; R(12) = gm_u32(R(3)); R(6) = 0;              /* ResAccMult_c::getResource */
                     R(12) = gm_u32(R(12) + 12); ctx->ctr = R(12); GM_TAIL(R(12), 0); }
E(fn_80006A40, 8)  { R(0) = R(3) + 12; gm_set_u32(R(3) + 4, R(0)); }                /* ResAccMult_c::creater */
E(fn_80006A70, 4)  { ra_get_font(GM_PASS); }                                        /* InternalAccessor::GetFont */
E(fn_80006EA0, 4)  { GM_TAIL(F_M2D_ENTRY, 0); }                                     /* Multi_c::entry */
E(fn_80006EB0, 168) { mu_calc(GM_PASS); }                                           /* Multi_c::calc */
E(fn_80006F70, 168) { mu_calc_before(GM_PASS); }                                    /* Multi_c::calcBefore */
E(fn_80006FA0, 168) { mu_calc_after(GM_PASS); }                                     /* Multi_c::calcAfter */
E(fn_80007010, 168) { mu_draw(GM_PASS); }                                           /* Multi_c::draw */
E(findPaneByName__Q23m2d17EmbedLayoutBase_cCFPCc, 4) { mu_find_pane(GM_PASS); }
E(findTextBoxByName__Q23m2d17EmbedLayoutBase_cCFPCc, 4) { mu_find_cast(GM_PASS, 0x80007320u, SDA_TI_TEXTBOX); }   /* FNADDR */
E(findPictureByName__Q23m2d17EmbedLayoutBase_cCFPCc, 4) { mu_find_cast(GM_PASS, 0x800073D0u, SDA_TI_PICTURE); }   /* FNADDR */
E(findWindowByName__Q23m2d17EmbedLayoutBase_cCFPCc, 4)  { mu_find_cast(GM_PASS, 0x80007470u, SDA_TI_WINDOW); }   /* FNADDR */
E(fn_800073C0, 4)  { R(3) = R(13) - 18624; }
E(fn_80007510, 4)  { GM_TAIL(F_M3D_PROC_SETUP, 0); }
E(fn_800075D0, 4)  { mu_dtor_free(GM_PASS); }
