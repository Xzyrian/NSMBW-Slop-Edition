/* gm_m_2d.c - mLib's 2D layout layer (m2d): the draw list of layouts (entry, draw / drawBefore /
 * drawAfter / drawBtween), FrameCtrl_c (an animation's frame counter), ResAccIf_c, Simple_c
 * (calc, build, patrolPane), AnmResV2_c (the group animations: per-pane / per-material links,
 * frames, enable) and AnmGroupBase_c. Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_2d.cpp) and checked against the recompiled
 * USA rev 2 code (0x80163170-0x801644F0; the slice's offsets drift by 0x140 here). Not here
 * (still recompiled): m2d::create, Layout_c::bindAnimationAuto, Simple_c's constructor and draw,
 * AnmResV2_c::create. The nw4r lyt objects stay recompiled and are called through their vtables
 * (Pane: +88 FindAnimationLinkSelf, +92 SetAnimationEnable, +100 GetMaterialNum, +108
 * GetMaterial; Material: +36 FindAnimationLink; Layout: +12 Build, +48 CalculateMtx, +52 Draw,
 * +56 Animate). Calls carry the PowerPC return address (GM_CALLR); the non-volatile registers are
 * mirrored around them (gm_nv.h).
 *
 * Base_c: +0 list link, +8 vtable (+12 draw, +16 calc), +12 draw order. FrameCtrl_c: +4 end frame,
 * +8 frame, +12 previous frame, +16 rate, +20 flags (1 no loop, 2 reverse). Simple_c: +16 Layout_c
 * (+32 root pane), +48 DrawInfo (+52 view matrix, +100 view rect), +132 ResAccIf_c, +136 position,
 * +148 flags. AnmResV2_c: +4 AnimResource, +20 group array (8 bytes each: group, transform),
 * +24 group count. AnmGroupBase_c: +0 FrameCtrl_c, +4 AnmResV2_c, +8 group entry, +12 flags. */
#include "gm.h"
#include "gm_nv.h"

#define SDA 0x8042F680u
#define L_LIST      0x80377AB0u          /* m2d::l_list (nw4r::ut::List) */
#define L_ALLOCATOR (SDA - 21184)        /* m2d::l_allocator */
#define F_LIST_INIT 0x80228DD0u          /* nw4r::ut::List_Init / Append / Insert / GetNext */
#define F_LIST_APPEND 0x80228DF0u
#define F_LIST_INSERT 0x80228E60u
#define F_LIST_NEXT 0x80228FF0u
#define F_LIST_ERASE 0x80229190u         /* nw4r::ut::detail::LinkListImpl::Erase */
#define F_CREATE_ANIM 0x802AD080u        /* nw4r::lyt::Layout::CreateAnimTransform(binary, accessor) */
#define F_ARC_ATTACH 0x802B6680u         /* nw4r::lyt::ArcResourceAccessor::Attach / Detach */
#define F_ARC_DETACH 0x802B6700u
#define F_LAYOUT_RECT 0x802AD520u        /* nw4r::lyt::Layout::GetLayoutRect */
#define F_MTX_IDENTITY 0x801C04D0u
#define F_MTX_TRANS_APPLY 0x801C0C10u
#define F_CULL_MODE 0x801C5860u          /* GXSetCullMode / GXSetZMode / GXSetFog */
#define F_Z_MODE    0x801C8E70u
#define F_FOG       0x801C8920u
#define F_DELETEA   0x802B9290u
#define F_STRCMP    0x802E1AB4u
#define F_IS_LOOP   0x802B50B0u          /* nw4r::lyt::AnimTransform::IsLoopData / GetFrameSize */
#define F_FRAME_SIZE 0x802B50A0u

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f
#define V(o, off) gm_u32(gm_u32(o) + (off))
static inline double fl(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }

/* ================================================================== the draw list */
static void default_set(GM_CTX) {
    FN(0x80163220);
    GM_CALLR(0x80163234u, F_CULL_MODE, 1, 0);
    GM_CALLR(0x80163244u, F_Z_MODE, 3, 0, 7, 0);
    double z = fl(ctx, 1, R2F(21584));
    gm_set_u32(f + 8, gm_u32(ctx->r[2] - 13424));                          /* (l_clearColor) */
    ctx->f[2].d = z; ctx->f[3].d = z; ctx->f[4].d = z;
    GM_CALLR(0x80163268u, F_FOG, 2, 0, f + 8);
}
static inline void base_draw(GM_CTX, uint32_t ra, gptr b) { GM_CALLR(ra, V(b + 8, 12), 1, b); }
static void m2d_draw(GM_CTX) {
    FN(0x80163280); GM_NV_KEEP;
    NCALL(0x80163298u, default_set(GM_PASS));
    NV_R(31, 0x80370000u);
    gptr n = GM_CALLR(0x801632A8u, F_LIST_NEXT, 2, L_LIST, 0);
    NV_R(30, n);
    while (n) {
        GM_LOOP();
        base_draw(GM_PASS, 0x801632C4u, n);
        n = GM_CALLR(0x801632D0u, F_LIST_NEXT, 2, L_LIST, n);
        NV_R(30, n);
    }
    GM_CALLR(0x801632E0u, F_LIST_INIT, 2, L_LIST, 0);                     /* (reset: a tail call) */
}
static void draw_before(GM_CTX, uint32_t order) {
    FN(0x80163300); GM_NV_KEEP;
    NV_R(31, 0x80370000u); NV_R(29, order);
    gptr n = GM_CALLR(0x8016332Cu, F_LIST_NEXT, 2, L_LIST, 0);
    NV_R(30, n);
    while (n) {
        GM_LOOP();
        if (!(gm_u8(n + 12) < order)) break;
        base_draw(GM_PASS, 0x80163354u, n);
        n = GM_CALLR(0x80163360u, F_LIST_NEXT, 2, L_LIST, n);
        NV_R(30, n);
    }
}
static void draw_after(GM_CTX, uint32_t order) {
    FN(0x80163390); GM_NV_KEEP;
    NV_R(31, 0x80370000u); NV_R(29, order);
    gptr n = GM_CALLR(0x801633BCu, F_LIST_NEXT, 2, L_LIST, 0);
    NV_R(30, n);
    while (n) {
        GM_LOOP();
        if (gm_u8(n + 12) > order) base_draw(GM_PASS, 0x801633E4u, n);
        n = GM_CALLR(0x801633F0u, F_LIST_NEXT, 2, L_LIST, n);
        NV_R(30, n);
    }
}
static void draw_between(GM_CTX, uint32_t lo, uint32_t hi) {
    FN(0x80163420); GM_NV_KEEP;
    NV_R(31, 0x80370000u); NV_R(29, hi); NV_R(28, lo);
    gptr n = GM_CALLR(0x80163454u, F_LIST_NEXT, 2, L_LIST, 0);
    NV_R(30, n);
    while (n) {
        GM_LOOP();
        uint32_t o = gm_u8(n + 12);
        if (o > hi) break;
        if (!(o < lo)) base_draw(GM_PASS, 0x80163484u, n);
        n = GM_CALLR(0x80163490u, F_LIST_NEXT, 2, L_LIST, n);
        NV_R(30, n);
    }
}
/* Base_c::entry: into the list before the first with a higher draw order */
static void base_entry(GM_CTX, gptr self) {
    FN(0x80163850); GM_NV_KEEP;
    NV_R(31, 0x80370000u); NV_R(30, self);
    gptr n = GM_CALLR(0x80163878u, F_LIST_NEXT, 2, L_LIST, 0);
    while (n) {
        GM_LOOP();
        if (gm_u8(n + 12) > gm_u8(self + 12)) { GM_CALLR(0x801638A0u, F_LIST_INSERT, 3, L_LIST, n, self); return; }
        n = GM_CALLR(0x801638ACu, F_LIST_NEXT, 2, L_LIST, n);
    }
    GM_CALLR(0x801638C8u, F_LIST_APPEND, 2, L_LIST, self);
}

/* ================================================================== FrameCtrl_c */
static void fc_play(GM_CTX, gptr fc) {
    uint32_t fg = gm_u8(fc + 20);
    double fr = LF(fc + 8);
    SF(fc + 12, fr);
    if (fg & 2) {                                                          /* REVERSE */
        double rate = LF(fc + 16);
        if (fr > rate || fr == rate) fr = frsp(fr - rate);
        else if (fg & 1) fr = R2F(21584);
        else fr = frsp(fr + frsp(LF(fc + 4) - rate));
    } else {
        fr = frsp(fr + LF(fc + 16));
        if (fg & 1) {                                                      /* NO_LOOP */
            double last = frsp(LF(fc + 4) - R2F(21580));
            if (fr > last) fr = last;
        } else {
            double end = LF(fc + 4);
            if (fr > end || fr == end) fr = frsp(fr - end);
        }
    }
    SF(fc + 8, fr);
}
/* set(end frame, flags, rate, frame) */
static void fc_set(GM_CTX, gptr fc, double end, uint32_t fg, double rate, double cur) {
    FN(0x80163760);
    double z = R2F(21584);
    if (cur < z) cur = z;
    SF(fc + 4, end);
    SF(fc + 8, cur);
    SF(fc + 16, rate);                                                     /* (setRate: a leaf) */
    double fr = LF(fc + 8);
    gm_set_u8(fc + 20, (uint8_t)fg);
    SF(fc + 12, fr);
}
static uint32_t fc_is_stop(GM_CTX, gptr fc) {
    switch (gm_u8(fc + 20)) {
    case 1: { double l = frsp(LF(fc + 4) - R2F(21580)), c = LF(fc + 8); return c > l || c == l; }
    case 3: { double c = LF(fc + 8), z = R2F(21584); return c < z || c == z; }
    default: return 0;
    }
}

/* ================================================================== Simple_c */
static void simple_calc_before(GM_CTX, gptr self) {
    uint32_t opt = (gm_u32(self + 148) & 1) ? 1 : 0;                       /* SKIP_INVISIBLE */
    GM_CALLR(ctx->lr, V(self + 16, 56), 2, self + 16, opt);                /* Layout::Animate (a tail call) */
}
static void simple_calc_after(GM_CTX, gptr self) {
    FN(0x80163A90); GM_NV_KEEP;
    NV_R(31, self);
    GM_CALLR(0x80163AB0u, F_LAYOUT_RECT, 2, f + 8, self + 16);
    for (int i = 0; i < 4; i++) SF(self + 100 + 4 * i, LF(f + 8 + 4 * i));
    GM_CALLR(0x80163AE8u, V(self + 16, 48), 2, self + 16, self + 48);    /* CalculateMtx */
}
static void simple_calc(GM_CTX, gptr self) {
    FN(0x801639A0); GM_NV_KEEP;
    NV_R(31, self);
    NCALL(0x801639B8u, simple_calc_before(GM_PASS, self));
    GM_CALLR(0x801639C0u, F_MTX_IDENTITY, 1, f + 24);
    double z = fl(ctx, 3, LF(self + 144)), y = fl(ctx, 2, LF(self + 140)), x = fl(ctx, 1, LF(self + 136));
    SF(f + 8, x); SF(f + 12, y); SF(f + 16, z);
    GM_CALLR(0x801639E4u, F_MTX_TRANS_APPLY, 2, f + 24, f + 24);
    for (int i = 0; i < 12; i++) gm_set_u32(self + 52 + 4 * i, gm_u32(f + 24 + 4 * i));   /* (SetViewMtx) */
    NCALL(0x80163A4Cu, simple_calc_after(GM_PASS, self));
}
static gptr res_get(GM_CTX, gptr acc, uint32_t type, gptr name) {          /* ResAccIf_c::getResource */
    gptr a = gm_u32(acc + 4);
    return GM_CALLR(ctx->lr, V(a, 12), 4, a, type, name, 0);
}
static uint32_t simple_build(GM_CTX, gptr self, gptr name, gptr acc) {
    FN(0x80163C70); GM_NV_KEEP;
    NV_R(31, acc); NV_R(30, self);
    if (gm_u32(self + 32)) return 1;
    if (!acc) { acc = gm_u32(self + 132); NV_R(31, acc); if (!acc) return 0; }
    gptr res = NCALL(0x80163CCCu, res_get(GM_PASS, acc, 0, name));
    if (!res) return 0;
    uint32_t r = GM_CALLR(0x80163CF8u, V(self + 16, 12), 3, self + 16, res, gm_u32(acc + 4));   /* Build */
    NV_R(31, r);
    if (r) GM_CALLR(0x80163D18u, V(self + 8, 16), 1, self);                /* calc */
    return r;
}
/* patrolPane_local(pane, func1, func2, arg): func1 on the pane (if func2 lets it), then on the
   children, last first; stops at the first non-zero result */
static uint32_t patrol_local(GM_CTX, gptr self, gptr pane, gptr f1, gptr f2, gptr arg) {
    FN(0x80163D40); GM_NV_KEEP;
    NV_R(25, self); NV_R(26, pane); NV_R(27, f1); NV_R(28, f2); NV_R(29, arg); NV_R(30, 0);
    uint32_t ret = 0;
    if (!f2 || GM_CALLR(0x80163D84u, f2, 1, pane) == 1) {
        ret = GM_CALLR(0x80163DA0u, f1, 2, pane, arg);
        NV_R(30, ret);
        if (ret) return ret;
    }
    gptr it = pane + 20;
    while (it != gm_u32(pane + 20)) {
        GM_LOOP();
        NV_R(31, it);
        ret = NCALL(0x80163DD4u, patrol_local(GM_PASS, self, gm_u32(it + 4) - 4, f1, f2, arg));
        NV_R(30, ret);
        if (ret) return ret;
        it = gm_u32(it + 4);
    }
    return ret;
}

/* ================================================================== AnmResV2_c */
static gptr anm_group(GM_CTX, gptr self, gptr name) {                      /* getGroupAnimTransform */
    FN(0x80163FF0); GM_NV_KEEP;
    int32_t n = (int32_t)gm_u32(self + 24);
    NV_R(30, n); NV_R(25, self); NV_R(26, name); NV_R(28, 0); NV_R(27, 0); NV_R(31, 0);
    for (int32_t i = 0; i < n; i++) {
        GM_LOOP();
        gptr arr = gm_u32(self + 20);
        NV_R(29, arr);
        if (!GM_CALLR(0x80164034u, F_STRCMP, 2, name, gm_u32(arr + 8 * i) + 24)) return arr + 8 * i;
        NV_R(31, 8 * (i + 1)); NV_R(27, i + 1);
    }
    return 0;
}
static gptr find_link(GM_CTX, gptr self, gptr pane, uint32_t rec) {
    FN(0x801641B0); GM_NV_KEEP;
    NV_R(28, pane); NV_R(27, self); NV_R(29, rec);
    gptr r = GM_CALLR(0x801641E8u, V(pane, 88), 2, pane, self + 4);       /* FindAnimationLinkSelf */
    if (r) return r;
    uint32_t n = GM_CALLR(0x80164208u, V(pane, 100), 1, pane) & 0xFF;     /* GetMaterialNum */
    NV_R(30, n); NV_R(31, 0);
    for (uint32_t i = 0; (i & 0xFF) < n; i++) {
        GM_LOOP();
        NV_R(31, i);
        gptr m = GM_CALLR(0x8016422Cu, V(pane, 108), 2, pane, i & 0xFF);  /* GetMaterial */
        r = GM_CALLR(0x80164240u, V(m, 36), 2, m, self + 4);              /* FindAnimationLink */
        if (r) return r;
    }
    if (!rec) return 0;
    gptr it = gm_u32(pane + 20);
    NV_R(31, it); NV_R(30, pane + 20);
    while (it != pane + 20) {
        GM_LOOP();
        NV_R(31, it);
        r = NCALL(0x80164280u, find_link(GM_PASS, self, it - 4, 1));
        if (r) return r;
        it = gm_u32(it);
    }
    return 0;
}
static void set_anm_frame(GM_CTX, gptr self, gptr pane, double frame) {
    FN(0x801642C0); GM_NV_KEEP;
    NV_F(31, frame); NV_R(29, pane); NV_R(28, self);
    gptr r = GM_CALLR(0x80164304u, V(pane, 88), 2, pane, self + 4);
    if (r) SF(gm_u32(r + 8) + 16, frame);
    uint32_t n = GM_CALLR(0x80164328u, V(pane, 100), 1, pane) & 0xFF;
    NV_R(31, n); NV_R(30, 0);
    for (uint32_t i = 0; (i & 0xFF) < n; i++) {
        GM_LOOP();
        NV_R(30, i);
        gptr m = GM_CALLR(0x8016434Cu, V(pane, 108), 2, pane, i & 0xFF);
        r = GM_CALLR(0x80164360u, V(m, 36), 2, m, self + 4);
        if (r) SF(gm_u32(r + 8) + 16, frame);
    }
}
static void anm_set_enable(GM_CTX, gptr self, gptr group, uint32_t en) {
    FN(0x80164080); GM_NV_KEEP;
    gptr head = group + 16, it = gm_u32(group + 16);
    NV_R(30, head); NV_R(29, en); NV_R(28, self); NV_R(31, it);
    while (it != head) {
        GM_LOOP();
        gptr l = NCALL(0x801640C0u, find_link(GM_PASS, self, gm_u32(it + 8), 0));
        if (l) { gptr p = gm_u32(it + 8); GM_CALLR(0x801640ECu, V(p, 92), 4, p, gm_u32(l + 8), en, 0); }   /* SetAnimationEnable */
        it = gm_u32(it); NV_R(31, it);
    }
}
static void anm_update_frame(GM_CTX, gptr self, gptr group, double frame) {
    FN(0x80164120); GM_NV_KEEP;
    gptr head = group + 16, it = gm_u32(group + 16);
    NV_F(31, frame); NV_R(30, head); NV_R(28, self); NV_R(31, it);
    while (it != head) {
        GM_LOOP();
        gptr p = gm_u32(it + 8);
        NV_R(29, p);
        if (NCALL(0x80164168u, find_link(GM_PASS, self, p, 0))) {
            ctx->f[1].d = frame;
            NCALL(0x80164180u, set_anm_frame(GM_PASS, self, p, frame));
        }
        it = gm_u32(it); NV_R(31, it);
    }
}

/* ================================================================== AnmGroupBase_c */
static void grp_update_frame(GM_CTX, gptr self) {                          /* (a leaf: tail call) */
    double fr = fl(ctx, 1, LF(gm_u32(self) + 8));
    anm_update_frame(GM_PASS, gm_u32(self + 4), gm_u32(gm_u32(self + 8)), fr);
}
static uint32_t grp_create(GM_CTX, gptr self, gptr res, gptr name) {
    FN(0x801643B0); GM_NV_KEEP;
    NV_R(30, self);
    gm_set_u32(self + 4, res);
    gptr g = NCALL(0x801643DCu, anm_group(GM_PASS, res, name));
    gm_set_u32(self + 8, g);
    if (!g) return 1;
    uint32_t fg = 1;
    NV_R(31, 1);
    if (GM_CALLR(0x801643F4u, F_IS_LOOP, 1, gm_u32(g + 4))) fg = 0;
    NV_R(31, fg);
    uint32_t sz = GM_CALLR(0x8016440Cu, F_FRAME_SIZE, 1, gm_u32(gm_u32(self + 8) + 4)) & 0xFFFF;
    gm_set_u32(f + 12, sz); gm_set_u32(f + 8, 0x43300000u);
    union { uint64_t u; double d; } a, m;
    a.u = ld64(base, f + 8); m.u = ld64(base, ctx->r[2] - 21568);
    double end = frsp(a.d - m.d), rate = fl(ctx, 2, R2F(21580)), cur = fl(ctx, 3, R2F(21576));
    fl(ctx, 1, end);
    NCALL(0x8016443Cu, fc_set(GM_PASS, gm_u32(self), end, fg, rate, cur));
    ctx->lr = 0x80164444u;
    grp_update_frame(GM_PASS, self);
    return 1;
}

/* ================================================================== hle entry points
   On (25): reached by the test runs or run inside them (FrameCtrl_c::set, getGroupAnimTransform,
   AnmResV2_c::setAnmEnable / updateFrame / setAnmFrame). Written but off (not reached):
   drawBtween, Layout_c::CreateAnimTransform, Simple_c::calc / calcBefore / calcAfter / build,
   patrolPane / patrolPane_local. */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
E(ClearLayoutDrawList__Fv) { GM_RET(GM_CALLR(ctx->lr, F_LIST_INIT, 2, L_LIST, 0)); }            /* m2d::reset */
E(SetupLYTDrawing__Fv) { default_set(GM_PASS); }                                               /* ::defaultSet */
E(fn_80163280) { GM_LR_KEEP; m2d_draw(GM_PASS); }                                              /* ::draw */
E(DrawAllLayoutsBeforeX__Fi) { draw_before(GM_PASS, A(0) & 0xFF); }                            /* ::drawBefore */
E(DrawAllLayoutsAfterX__Fi) { draw_after(GM_PASS, A(0) & 0xFF); }                              /* ::drawAfter */
E(DrawAllLayoutsAfterXandBeforeY__Fii) { draw_between(GM_PASS, A(0) & 0xFF, A(1) & 0xFF); }   /* ::drawBtween */
E(fn_801634C0) { GM_RET(gm_u32(L_ALLOCATOR)); }                                                /* ::getAllocator */
E(fn_801634D0) {                                                                               /* Layout_c::CreateAnimTransform */
    FN(0x801634D0); GM_NV_KEEP;
    gptr self = A(0);
    NV_R(30, self);
    gptr t = GM_CALLR(0x801634ECu, F_CREATE_ANIM, 3, self, A(1), A(2));
    NV_R(31, t);
    if (t) GM_CALLR(0x80163504u, F_LIST_ERASE, 2, self + 4, t + 4);
    GM_RET(t);
}
E(attachArc__Q23m2d8ResAcc_cFPvPCc) {                                                          /* ResAccIf_c::attach */
    gptr s = A(0);
    if (gm_u32(s + 8)) { GM_RET(0); return; }
    gm_set_u32(s + 8, A(1));
    GM_RET(GM_CALLR(ctx->lr, F_ARC_ATTACH, 3, gm_u32(s + 4), A(1), A(2)));
}
E(fn_80163690) { gm_set_u32(A(0) + 8, 0); GM_RET(GM_CALLR(ctx->lr, F_ARC_DETACH, 1, gm_u32(A(0) + 4))); }   /* ::detach */
E(fn_801636A0) { GM_RET(res_get(GM_PASS, A(0), A(1), A(2))); }                                 /* ::getResource */
E(fn_801636C0) { fc_play(GM_PASS, A(0)); }                                                     /* FrameCtrl_c::play */
E(fn_80163760) { fc_set(GM_PASS, A(0), ctx->f[1].d, A(1), ctx->f[2].d, ctx->f[3].d); }         /* ::set */
E(fn_801637D0) { SF(A(0) + 8, ctx->f[1].d); SF(A(0) + 12, ctx->f[1].d); }                       /* ::setFrame */
E(setSpeed__Q23m2d11FrameCtrl_cFf) { SF(A(0) + 16, ctx->f[1].d); }                             /* ::setRate */
E(fn_801637F0) { GM_RET(fc_is_stop(GM_PASS, A(0))); }                                          /* ::isStop */
E(scheduleForDrawing__Q23m2d6Base_cFv) { base_entry(GM_PASS, A(0)); }                          /* Base_c::entry */
E(fn_801639A0) { GM_LR_KEEP; simple_calc(GM_PASS, A(0)); }                                     /* Simple_c::calc */
E(fn_80163A60) { simple_calc_before(GM_PASS, A(0)); }                                          /* ::calcBefore */
E(fn_80163A90) { simple_calc_after(GM_PASS, A(0)); }                                           /* ::calcAfter */
E(fn_80163C70) { GM_LR_KEEP; GM_RET(simple_build(GM_PASS, A(0), A(1), A(2))); }                /* ::build */
E(fn_80163D40) { GM_LR_KEEP; GM_RET(patrol_local(GM_PASS, A(0), A(1), A(2), A(3), A(4))); }    /* ::patrolPane_local */
E(fn_80163E10) {                                                                               /* ::patrolPane */
    GM_LR_KEEP; FN(0x80163E10);
    uint32_t r = NCALL(0x80163E38u, patrol_local(GM_PASS, A(0), gm_u32(A(0) + 32), A(1), A(2), A(3)));
    GM_RET(r != 2);
}
E(_Z16NSMBWBrlan__FreePv) {                                                                    /* AnmResV2_c::remove */
    FN(0x80163FB0); GM_NV_KEEP;
    gptr s = A(0);
    NV_R(31, s);
    GM_CALLR(0x80163FCCu, F_DELETEA, 1, gm_u32(s + 20));
    gm_set_u32(s + 20, 0);
    GM_RET(1);
}
E(fn_80163FF0) { GM_RET(anm_group(GM_PASS, A(0), A(1))); }                                     /* ::getGroupAnimTransform */
E(fn_80164080) { GM_LR_KEEP; anm_set_enable(GM_PASS, A(0), A(1), A(2)); }                       /* ::setAnmEnable */
E(fn_80164120) { GM_LR_KEEP; anm_update_frame(GM_PASS, A(0), A(1), ctx->f[1].d); }              /* ::updateFrame */
E(fn_801641B0) { GM_LR_KEEP; GM_RET(find_link(GM_PASS, A(0), A(1), A(2))); }                    /* ::findAnmLink */
E(fn_801642C0) { set_anm_frame(GM_PASS, A(0), A(1), ctx->f[1].d); }                             /* ::setAnmFrame */
E(m2d__Anm_c__Load) { GM_LR_KEEP; GM_RET(grp_create(GM_PASS, A(0), A(1), A(2))); }              /* AnmGroupBase_c::create */
E(fn_80164460) {                                                                               /* ::setAnmEnable */
    GM_LR_KEEP; FN(0x80164460); GM_NV_KEEP;
    gptr s = A(0); uint32_t en = A(1);
    NV_R(31, en); NV_R(30, s);
    NCALL(0x80164490u, anm_set_enable(GM_PASS, gm_u32(s + 4), gm_u32(gm_u32(s + 8)), en));
    gm_set_u8(s + 12, en ? (gm_u8(s + 12) | 1) : (gm_u8(s + 12) & 0xFE));
}
E(fn_801644D0) { grp_update_frame(GM_PASS, A(0)); }                                            /* ::updateFrame */
E(fn_801644F0) { }
