/* gm_d_lytbuild.c - the rest of LytBase_c (m2d::EmbedLayout_c in the symbol map): ctor / dtor,
 * build (d2d::Multi_c::build, the 511-character string buffers, the tag processor),
 * allocStringBuffer, ReadResourceEx / ReadResource / ReadResource2 ("Layout/<name>", localised
 * through dGameCom::AreaLanguageFolder, or "EU/Layout/<name>"), the pane registers (N / W / P / T
 * and TPaneNameRegister), AnimeResRegister / GroupRegister (with m2d::AnmResV2_c's and
 * m2d::AnmGroup_c's array constructors / destructors), SetScissorMask and doDelete. Track B
 * (gm.h, docs/DECOMP.md), instance 1. The animations are gm_d_lytbase.c.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_lytbase.cpp) and checked against the
 * recompiled USA rev 2 code (0x800C8950-0x800C926C, 0x800C9680-0x800C9A0C). Register-exact
 * (R(n)); SetScissorMask keeps the PowerPC code's float order, stack temporaries (the copied
 * matrix, the 0x43300000 conversions) and its two dead stores after the restores.
 *
 * LytBase_c (a d2d::Multi_c): +132 the resource accessor, +172 the ResAccMultLoader_c, +384 the
 * AnmResV2_c array (28 bytes each), +388 the AnmGroup_c array (40), +392 the enabled flags, +396 /
 * +400 their counts. */
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

#define F_MULTI_CT       0x80006CD0u    /* d2d::Multi_c::Multi_c */
#define F_MULTI_DT       0x80006E30u
#define F_MULTI_BUILD    0x80007230u    /* d2d::Multi_c::build */
#define F_ROOT_PANE      0x80007220u    /* d2d::Multi_c::getRootPane */
#define F_LOADER_CT      0x80006AA0u    /* d2d::ResAccMultLoader_c::ResAccMultLoader_c */
#define F_LOADER_DT      0x80006AF0u
#define F_LOADER_REQ     0x80006B60u    /* ::requestEx(path, allocDir) */
#define F_LOADER_REMOVE  0x80006BF0u
#define F_ALLOC_STRBUF   0x800C8AA0u
#define F_READ_RES_EX    0x800C8BB0u
#define F_FIND_TEXTBOX   0x800C8A90u
#define F_SET_MESSAGE_V  0x800C9A60u    /* LytTextBox_c::setMessage(..., ...) */
#define F_MES_RES        0x800CDC60u    /* dMessage_c::getMesRes */
#define F_ANMRES_CREATE  0x80163E60u    /* m2d::AnmResV2_c::create */
#define F_ANMRES_REMOVE  0x80163FB0u    /* m2d::AnmResV2_c::remove */
#define F_ANMGRP_CREATE  0x801643B0u    /* m2d::AnmGroup_c::create */
#define F_ANIMRES_CT     0x802B5AF0u    /* nw4r::lyt::AnimResource::AnimResource */
#define F_AREA_LANG      0x800B4650u    /* dGameCom::AreaLanguageFolder */
#define F_STRNCAT        0x802E1A68u
#define F_MEMSET         0x800046B4u
#define F_NEW_ARR        0x802B9250u
#define F_OP_DELETE      0x802B9280u
#define F_DELETE_ARR     0x802B9290u
#define F_CONSTRUCT_ARR  0x802DC7E0u
#define F_DESTROY_ARR    0x802DCB10u
#define F_GX_GET_SCISSOR 0x801C9CD0u
#define ANMRES_CT        0x800C9060u
#define ANMRES_DT        0x800C90B0u
#define ANMGRP_CT        0x800C91B0u
#define ANMGRP_DT        0x800C9230u
#define SDA_TI_TEXTBOX   18600          /* (r13 - : nw4r::lyt::TextBox's type info) */
#define SDA_LAYOUT_DIR   31368          /* "Layout/" */
#define SDA_EU_DIR       31360          /* "EU/" */
#define SDA_VIDEO        20992          /* mVideo::m_video */

/* ================================================================== life */
static void lb_ctor(GM_CTX) {
    GM_FN(0x800C8950); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x800C8968u, F_MULTI_CT, 0);
    R(4) = 0x80310000u; R(3) = R(31) + 172;
    R(4) = R(4) + 29752;
    gm_set_u32(R(31) + 8, R(4));                                             /* the vtable */
    GM_CALLV(0x800C897Cu, F_LOADER_CT, 0);
    R(0) = 0;
    gm_set_u32(R(31) + 396, 0);
    R(3) = R(31);
    gm_set_u32(R(31) + 400, 0);
    R(0) = lr;
}
static void lb_dtor(GM_CTX) {
    GM_FN(0x800C89A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(4) = (uint32_t)-1; R(3) = R(3) + 172;
        GM_CALLV(0x800C89D0u, F_LOADER_DT, 0);
        R(3) = R(30); R(4) = 0;
        GM_CALLV(0x800C89DCu, F_MULTI_DT, 0);
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x800C89ECu, F_OP_DELETE, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
/* build(name, resAcc): Multi_c::build, then the string buffers and the tag processor */
static void lb_build(GM_CTX) {
    GM_FN(0x800C8A10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3);
    GM_CALLV(0x800C8A2Cu, F_MULTI_BUILD, 0);
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(3);
    if (c != 0) {
        R(3) = R(30);
        GM_CALLV(0x800C8A40u, F_ROOT_PANE, 0);
        R(4) = R(3); R(3) = R(30);
        GM_CALLV(0x800C8A4Cu, F_ALLOC_STRBUF, 0);
        R(12) = gm_u32(R(30) + 16);
        R(4) = 0x80360000u;
        R(3) = R(30) + 16;
        R(12) = gm_u32(R(12) + 60);
        R(4) = R(4) - 27536;                                                 /* &s_TagPrc */
        ctx->ctr = R(12);
        GM_CALLV(0x800C8A68u, R(12), 0);                                     /* mLayout.SetTagProcessor */
    }
    R(3) = R(31);
    R(0) = lr;
}
/* allocStringBuffer(pane): a text box gets a 511-character buffer (its old string kept); then
   every child */
static void lb_alloc_strbuf(GM_CTX) {
    GM_FN(0x800C8AA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(4), 0);
    R(30) = R(13) - SDA_TI_TEXTBOX;
    R(29) = R(4); R(28) = R(3);
    if (c != 0) {
        R(12) = gm_u32(R(29)); R(3) = R(29);
        R(12) = gm_u32(R(12) + 12); ctx->ctr = R(12);
        GM_CALLV(0x800C8AE4u, R(12), 0);                                     /* GetRuntimeTypeInfo */
        R(0) = 0;
        if (cmps(ctx, (int32_t)R(3), 0) != 0) {
            for (;;) {
                GM_LOOP();
                if (cmpu(ctx, R(3), R(30)) == 0) { R(0) = 1; break; }
                R(3) = gm_u32(R(3));
                if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(0) = 0; break; }
            }
        }
        if (cmps(ctx, (int32_t)R(0), 0) != 0) R(30) = R(29); else R(30) = 0;
    } else R(30) = 0;
    if (cmps(ctx, (int32_t)R(30), 0) != 0) {
        R(12) = gm_u32(R(30)); R(3) = R(30);
        R(31) = gm_u32(R(30) + 216);                                         /* the old string */
        R(4) = 511;
        R(12) = gm_u32(R(12) + 116); ctx->ctr = R(12);
        GM_CALLV(0x800C8B40u, R(12), 0);                                     /* AllocStringBuffer */
        if (cmps(ctx, (int32_t)R(31), 0) != 0) {
            R(12) = gm_u32(R(30)); R(3) = R(30); R(4) = R(31); R(5) = 0;
            R(12) = gm_u32(R(12) + 124); ctx->ctr = R(12);
            GM_CALLV(0x800C8B64u, R(12), 0);                                 /* SetString(old, 0) */
        }
    }
    R(31) = gm_u32(R(29) + 20);
    R(30) = R(29) + 20;
    goto test;
body:
    R(3) = R(28); R(4) = R(31) - 4;
    GM_CALLV(0x800C8B7Cu, F_ALLOC_STRBUF, 0);
    R(31) = gm_u32(R(31));
test:
    if (cmpu(ctx, R(31), R(30)) != 0) { GM_LOOP(); goto body; }
    R(0) = lr;
}

/* ================================================================== resources */
/* the loader's request, then the accessor (r29: this) */
static void lb_request(GM_CTX, uint32_t self, uint32_t ra) {
    GM_CALLV(ra, F_LOADER_REQ, 0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) R(3) = 0;
    else { R(0) = self + 172; gm_set_u32(self + 132, R(0)); R(3) = 1; }
}
/* ReadResourceEx(name, allocDir, localised) */
static void lb_read_res_ex(GM_CTX) {
    GM_FN(0x800C8BB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    int c = cmps(ctx, (int32_t)R(6), 0);
    R(31) = R(5); R(30) = R(4); R(29) = R(3);
    if (c != 0) {
        R(3) = 0x802F0000u; R(0) = 12;
        R(3) = R(3) + 4120;                                                  /* "Layout/" padded to 100 */
        R(5) = f + 4;
        R(4) = R(3) - 4;
        ctx->ctr = R(0);
        for (;;) {
            R(3) = gm_u32(R(4) + 4);
            R(4) = R(4) + 8; R(0) = gm_u32(R(4));                            /* (lwzu) */
            gm_set_u32(R(5) + 4, R(3));
            R(5) = R(5) + 8; gm_set_u32(R(5), R(0));                         /* (stwu) */
            if (--ctx->ctr == 0) break;
            GM_LOOP();
        }
        R(0) = gm_u32(R(4) + 4);
        R(4) = R(30);
        gm_set_u32(R(5) + 4, R(0));
        R(3) = f + 8; R(5) = 99;
        GM_CALLV(0x800C8C24u, F_STRNCAT, 0);
        R(3) = f + 8; R(4) = f + 108;
        GM_CALLV(0x800C8C30u, F_AREA_LANG, 0);
    } else {
        R(3) = f + 108; R(4) = 0; R(5) = 100;
        GM_CALLV(0x800C8C44u, F_MEMSET, 0);
        R(3) = f + 108; R(4) = R(13) - SDA_LAYOUT_DIR; R(5) = 99;
        GM_CALLV(0x800C8C54u, F_STRNCAT, 0);
        R(4) = R(30); R(3) = f + 108; R(5) = 99;
        GM_CALLV(0x800C8C64u, F_STRNCAT, 0);
    }
    R(5) = R(31); R(3) = R(29) + 172; R(4) = f + 108;
    lb_request(GM_PASS, R(29), 0x800C8C74u);
    R(0) = lr;
}
/* ReadResource2(name): "EU/Layout/<name>" */
static void lb_read_res2(GM_CTX) {
    GM_FN(0x800C8CC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(5) = 100;
    R(31) = R(4); R(4) = 0; R(30) = R(3);
    R(3) = f + 8;
    GM_CALLV(0x800C8CECu, F_MEMSET, 0);
    R(3) = f + 8; R(4) = R(13) - SDA_EU_DIR; R(5) = 99;
    GM_CALLV(0x800C8CFCu, F_STRNCAT, 0);
    R(3) = f + 8; R(4) = R(13) - SDA_LAYOUT_DIR; R(5) = 99;
    GM_CALLV(0x800C8D0Cu, F_STRNCAT, 0);
    R(4) = R(31); R(3) = f + 8; R(5) = 99;
    GM_CALLV(0x800C8D1Cu, F_STRNCAT, 0);
    R(3) = R(30) + 172; R(4) = f + 8; R(5) = 0;
    lb_request(GM_PASS, R(30), 0x800C8D2Cu);
    R(0) = lr;
}

/* ================================================================== pane registers */
/* N / W / P / T PaneRegister(names, panes, n): panes[i] = find(names[i]) */
static void lb_register(GM_CTX, uint32_t a, uint32_t find) {
    GM_FN(a); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 32;
    R(27) = R(3); R(31) = R(4); R(30) = R(5); R(28) = R(6);
    R(29) = 0;
    goto test;
body:
    R(4) = gm_u32(R(31)); R(3) = R(27);
    GM_CALLV(a + 0x38, find, 0);
    gm_set_u32(R(30), R(3));
    R(31) = R(31) + 4; R(30) = R(30) + 4; R(29) = R(29) + 1;
test:
    if (cmps(ctx, (int32_t)R(29), (int32_t)R(28)) < 0) { GM_LOOP(); goto body; }
    R(11) = f + 32;
    R(0) = lr;
}
/* TPaneNameRegister(names, ids, group, n): each box gets its message */
static void lb_tpane_names(GM_CTX) {
    GM_FN(0x800C8F20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 48;
    R(25) = R(3); R(26) = R(4); R(27) = R(5); R(28) = R(6); R(29) = R(7);
    GM_CALLV(0x800C8F4Cu, F_MES_RES, 0);
    R(31) = R(3);
    R(30) = 0;
    goto test;
body:
    R(4) = gm_u32(R(26)); R(3) = R(25);
    GM_CALLV(0x800C8F64u, F_FIND_TEXTBOX, 0);
    R(6) = gm_u32(R(27));
    R(4) = R(31); R(5) = R(28); R(7) = 0;
    CR_SETBIT(ctx, 6, 0);
    GM_CALLV(0x800C8F7Cu, F_SET_MESSAGE_V, 0);
    R(26) = R(26) + 4; R(27) = R(27) + 4; R(30) = R(30) + 1;
test:
    if (cmps(ctx, (int32_t)R(30), (int32_t)R(29)) < 0) { GM_LOOP(); goto body; }
    R(11) = f + 48;
    R(0) = lr;
}

/* ================================================================== animations' resources */
/* AnimeResRegister(names, n): new AnmResV2_c[n], each created from its brlan */
static void lb_anime_res(GM_CTX) {
    GM_FN(0x800C8FB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 32;
    R(6) = (uint32_t)((int32_t)R(5) * 28);
    R(30) = gm_u32(R(3) + 132);
    R(26) = R(3); R(28) = R(5); R(27) = R(4);
    R(3) = R(6) + 16;
    GM_CALLV(0x800C8FE0u, F_NEW_ARR, 0);
    R(4) = ANMRES_CT; R(5) = ANMRES_DT; R(7) = R(28); R(6) = 28;
    GM_CALLV(0x800C8FFCu, F_CONSTRUCT_ARR, 0);
    gm_set_u32(R(26) + 384, R(3));
    R(29) = 0; R(31) = 0;
    gm_set_u32(R(26) + 396, R(28));
    goto test;
body:
    R(0) = gm_u32(R(26) + 384);
    R(5) = R(30);
    R(4) = gm_u32(R(27));
    R(6) = R(26) + 16;
    R(3) = R(0) + R(31);
    R(7) = 1;
    GM_CALLV(0x800C902Cu, F_ANMRES_CREATE, 0);
    R(27) = R(27) + 4; R(31) = R(31) + 28; R(29) = R(29) + 1;
test:
    if (cmps(ctx, (int32_t)R(29), (int32_t)R(28)) < 0) { GM_LOOP(); goto body; }
    R(11) = f + 32;
    R(0) = lr;
}
/* GroupRegister(names, animeIdxs, n): new AnmGroup_c[n] and the flags, each group on its resource */
static void lb_groups(GM_CTX) {
    GM_FN(0x800C90F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 32;
    R(7) = (uint32_t)((int32_t)R(6) * 40);
    R(26) = R(3); R(29) = R(6); R(27) = R(4); R(28) = R(5);
    R(3) = R(7) + 16;
    GM_CALLV(0x800C9120u, F_NEW_ARR, 0);
    R(4) = ANMGRP_CT; R(5) = ANMGRP_DT; R(7) = R(29); R(6) = 40;
    GM_CALLV(0x800C913Cu, F_CONSTRUCT_ARR, 0);
    gm_set_u32(R(26) + 388, R(3));
    R(3) = R(29);
    GM_CALLV(0x800C9148u, F_NEW_ARR, 0);
    gm_set_u32(R(26) + 392, R(3));
    R(30) = 0; R(31) = 0;
    gm_set_u32(R(26) + 400, R(29));
    goto test;
body:
    R(0) = gm_u32(R(28));
    R(3) = gm_u32(R(26) + 388);
    R(0) = (uint32_t)((int32_t)R(0) * 28);
    R(4) = gm_u32(R(26) + 384);
    R(5) = gm_u32(R(27));
    R(3) = R(3) + R(31);
    R(4) = R(4) + R(0);
    GM_CALLV(0x800C917Cu, F_ANMGRP_CREATE, 0);
    R(27) = R(27) + 4; R(28) = R(28) + 4; R(31) = R(31) + 40; R(30) = R(30) + 1;
test:
    if (cmps(ctx, (int32_t)R(30), (int32_t)R(29)) < 0) { GM_LOOP(); goto body; }
    R(11) = f + 32;
    R(0) = lr;
}
/* m2d::AnmResV2_c::AnmResV2_c */
static void anmres_ctor(GM_CTX) {
    GM_FN(0x800C9060); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(4) = 0x80310000u;
    R(4) = R(4) + 29776;
    R(31) = R(3);
    gm_set_u32(R(3), R(4));
    R(3) = R(3) + 4;
    GM_CALLV(0x800C9088u, F_ANIMRES_CT, 0);
    R(0) = 0;
    gm_set_u32(R(31) + 20, 0);
    R(3) = R(31);
    gm_set_u32(R(31) + 24, 0);
    R(0) = lr;
}
/* m2d::AnmGroup_c::AnmGroup_c (its FrameCtrl_c inline: 0, 0, 0, end 1) */
static void anmgrp_ctor(GM_CTX) {
    FB(1, LF(R(2) - 26504));
    R(4) = 0x80310000u;
    R(0) = 0;
    FB(0, LF(R(2) - 26500));
    R(5) = R(3) + 16;
    R(4) = R(4) + 29788;
    gm_set_u32(R(3), R(5)); gm_set_u32(R(3) + 4, 0); gm_set_u32(R(3) + 8, 0);
    gm_set_u8(R(3) + 12, 0);
    gm_set_u32(R(3) + 16, R(4));
    SF(R(3) + 20, F(1)); SF(R(3) + 24, F(1)); SF(R(3) + 28, F(1)); SF(R(3) + 32, F(0));
}
/* the element destructors the arrays use (they only free) */
static void elem_dtor(GM_CTX, uint32_t a) {
    GM_FN(a); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(3);
    if (c != 0 && cmps(ctx, (int32_t)R(4), 0) > 0) GM_CALLV(a + 0x28, F_OP_DELETE, 0);
    R(3) = R(31);
    R(0) = lr;
}

/* ================================================================== scissor / delete */
/* SetScissorMask(pane, mask): the pane's box in screen pixels, around the current scissor's
   centre, scaled by the view rect against the video size (the location adjust taken out) */
static void lb_scissor(GM_CTX) {
    GM_FN(0x800C9680); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    FB(0, LF(R(2) - 26488));                                                 /* 1e-6f */
    R(0) = 0x43300000u;
    R(31) = R(5);
    FB(6, LF(R(3) + 120)); FB(4, LF(R(3) + 100)); FB(3, LF(R(3) + 104));
    cr_fcmp(ctx, 0, F(6), F(0));
    FB(2, LF(R(3) + 108)); FB(1, LF(R(3) + 112)); FB(5, LF(R(3) + 116));
    gm_set_u32(f + 120, R(0)); gm_set_u32(f + 128, R(0));
    SF(f + 56, F(4)); SF(f + 60, F(3)); SF(f + 64, F(2)); SF(f + 68, F(1));
    SF(f + 24, F(5)); SF(f + 28, F(6));
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if (CR_BIT(ctx, 2)) ctx->f[6].u = ctx->f[0].u;                           /* scale.y <= 1e-6 */
    FB(1, LF(f + 68)); FB(0, LF(f + 60)); FB(3, LF(f + 24));
    FB(1, frsp(F(1) - F(0)));
    FB(0, LF(R(2) - 26488));
    cr_fcmp(ctx, 0, F(3), F(0));
    FB(6, frsp(F(1) / F(6)));                                                /* height */
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if (CR_BIT(ctx, 2)) ctx->f[3].u = ctx->f[0].u;
    FB(2, LF(f + 64)); FB(1, LF(f + 56)); FB(0, LF(R(2) - 26504));
    FB(1, frsp(F(2) - F(1)));
    FB(7, frsp(F(1) / F(3)));                                                /* width */
    cr_fcmp(ctx, 0, F(7), F(0));
    if (CR_BIT(ctx, 0)) { FB(0, LF(R(2) - 26484)); FB(7, frsp(F(7) * F(0))); }
    FB(0, LF(R(2) - 26504));
    cr_fcmp(ctx, 0, F(6), F(0));
    if (CR_BIT(ctx, 0)) { FB(0, LF(R(2) - 26484)); FB(6, frsp(F(6) * F(0))); }
    R(6) = gm_u32(R(13) - SDA_VIDEO);
    R(3) = f + 20;
    R(0) = gm_u32(R(4) + 144);
    R(5) = f + 12;
    R(8) = gm_u32(R(6));
    R(6) = f + 8;
    gm_set_u32(f + 84, R(0));
    R(7) = gm_u16(R(8) + 4); R(0) = gm_u16(R(8) + 6);                         /* the video width / height */
    gm_set_u32(f + 124, R(7));
    ctx->f[2].u = ld64(base, R(2) - 26480);
    gm_set_u32(f + 132, R(0));
    ctx->f[0].u = ld64(base, f + 120);
    ctx->f[1].u = ld64(base, f + 128);
    FB(5, frsp(F(0) - F(2)));
    FB(0, LF(f + 84));
    FB(2, frsp(F(1) - F(2)));
    R(0) = gm_u32(R(4) + 160);
    FB(31, frsp(F(0) / F(3)));
    gm_set_u32(f + 100, R(0));
    R(0) = gm_u32(R(4) + 152);
    FB(4, LF(R(4) + 76)); FB(3, LF(R(4) + 80));                              /* the pane's size */
    gm_set_u32(f + 92, R(0));
    FB(5, frsp(F(5) / F(7)));                                                /* ratioX */
    FB(1, LF(R(2) - 26484));
    FB(0, LF(f + 100));
    R(29) = gm_u32(R(4) + 132); R(30) = gm_u32(R(4) + 136); R(12) = gm_u32(R(4) + 140);
    FB(6, frsp(F(2) / F(6)));                                                /* ratioY */
    R(11) = gm_u32(R(4) + 148); R(10) = gm_u32(R(4) + 156); R(9) = gm_u32(R(4) + 164);
    R(8) = gm_u32(R(4) + 168); R(7) = gm_u32(R(4) + 172);
    FB(30, frsp(F(1) * F(0)));
    R(0) = gm_u32(R(4) + 176);
    FB(2, frsp(F(4) * F(5)));
    FB(1, LF(f + 92));
    FB(0, frsp(F(3) * F(6)));
    gm_set_u32(f + 72, R(29));
    FB(29, frsp(F(1) * F(2)));                                               /* trueSizeX */
    gm_set_u32(f + 76, R(30));
    FB(28, frsp(F(1) * F(0)));                                               /* trueSizeY */
    R(4) = f + 16;
    FB(31, frsp(F(31) * F(5)));
    gm_set_u32(f + 80, R(12));
    FB(30, frsp(F(30) * F(6)));
    gm_set_u32(f + 88, R(11)); gm_set_u32(f + 96, R(10)); gm_set_u32(f + 104, R(9));
    gm_set_u32(f + 108, R(8)); gm_set_u32(f + 112, R(7)); gm_set_u32(f + 116, R(0));
    SF(f + 48, F(4)); SF(f + 52, F(3));
    GM_CALLV(0x800C9854u, F_GX_GET_SCISSOR, 0);
    R(3) = gm_u32(f + 12);
    R(0) = 1;
    gm_set_u32(f + 132, R(3));
    FB(7, LF(R(2) - 26496));                                                 /* 0.5f */
    R(3) = gm_u32(f + 20);
    gm_set_u32(f + 124, R(3));
    FB(3, frsp(F(7) * F(29)));
    ctx->f[4].u = ld64(base, f + 128);
    FB(2, frsp(F(7) * F(28)));
    R(3) = gm_u32(f + 8);
    FB(1, frsp(F(7) + F(29)));
    R(4) = gm_u32(f + 16);
    ctx->f[8].u = ld64(base, f + 120);
    FB(5, frsp(F(31) - F(3)));
    ctx->f[9].u = ld64(base, R(2) - 26480);
    FB(0, frsp(F(7) + F(28)));
    gm_set_u32(f + 132, R(3));
    FB(2, frsp(F(30) - F(2)));
    FB(6, frsp(F(4) - F(9)));
    ctx->f[3].u = ld64(base, f + 128);
    FB(8, frsp(F(8) - F(9)));
    gm_set_u32(f + 124, R(4));
    FB(3, frsp(F(3) - F(9)));
    ctx->f[4].u = ld64(base, f + 120);
    FB(6, frsp(F(7) * F(6)));
    SF(f + 32, F(1));
    FB(4, frsp(F(4) - F(9)));
    FB(3, frsp(F(7) * F(3)));
    SF(R(31) + 8, F(1));
    FB(6, frsp(F(8) + F(6)));
    SF(f + 36, F(0));
    FB(1, frsp(F(4) + F(3)));
    FB(3, frsp(F(6) + F(5)));
    SF(R(31) + 12, F(0));
    FB(0, frsp(F(1) + F(2)));
    SF(R(31) + 0, F(3)); SF(R(31) + 4, F(0));
    gm_set_u8(R(31) + 16, 1);                                                /* mEnabled */
    SF(f + 40, F(3)); SF(f + 44, F(0));                                      /* (the PowerPC code's dead stores) */
    R(0) = lr;
}
/* doDelete(): the animation resources (false while one cannot go yet), the groups, the archive */
static void lb_delete(GM_CTX) {
    GM_FN(0x800C9930); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(29) = R(3);
    R(0) = gm_u32(R(3) + 396);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(30) = 0; R(31) = 0;
        goto test;
    body:
        R(0) = gm_u32(R(29) + 384);
        R(3) = R(0) + R(31);
        GM_CALLV(0x800C9970u, F_ANMRES_REMOVE, 0);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
        R(31) = R(31) + 28; R(30) = R(30) + 1;
    test:
        R(0) = gm_u32(R(29) + 396);
        if (cmps(ctx, (int32_t)R(30), (int32_t)R(0)) < 0) { GM_LOOP(); goto body; }
        R(4) = ANMRES_DT;
        R(3) = gm_u32(R(29) + 384);
        GM_CALLV(0x800C99A4u, F_DESTROY_ARR, 0);
        R(0) = 0; gm_set_u32(R(29) + 396, 0);
    }
    R(0) = gm_u32(R(29) + 400);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(4) = ANMGRP_DT;
        R(3) = gm_u32(R(29) + 388);
        GM_CALLV(0x800C99C8u, F_DESTROY_ARR, 0);
        R(3) = gm_u32(R(29) + 392);
        GM_CALLV(0x800C99D0u, F_DELETE_ARR, 0);
        R(0) = 0; gm_set_u32(R(29) + 400, 0);
    }
    R(3) = R(29) + 172;
    GM_CALLV(0x800C99E0u, F_LOADER_REMOVE, 0);
    R(3) = cmps(ctx, (int32_t)R(3), 0) == 0 ? 0 : 1;
out:
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_LB_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_LB_COUNT)    /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(__ct__Q23m2d13EmbedLayout_cFv, 404) { lb_ctor(GM_PASS); }                        /* LytBase_c::LytBase_c */
E(__dt__Q23m2d13EmbedLayout_cFv, 404) { lb_dtor(GM_PASS); }                        /* ::~LytBase_c */
E(fn_800C8A10, 404) { lb_build(GM_PASS); }                                         /* ::build */
E(fn_800C8A90, 4)   { GM_TAIL(0x80007320u, 0); }                                   /* ::findTextBox */
E(fn_800C8AA0, 4)   { lb_alloc_strbuf(GM_PASS); }                                  /* ::allocStringBuffer */
E(fn_800C8BB0, 404) { lb_read_res_ex(GM_PASS); }                                   /* ::ReadResourceEx */
E(loadArc__Q23m2d13EmbedLayout_cFPCcb, 404) { R(6) = R(5); R(5) = 0; GM_TAIL(F_READ_RES_EX, 0); }   /* ::ReadResource */
E(fn_800C8CC0, 404) { lb_read_res2(GM_PASS); }                                     /* ::ReadResource2 */
E(getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei, 4)       { lb_register(GM_PASS, 0x800C8D60u, 0x80007300u); }   /* ::NPaneRegister   FNADDR */
E(getWindows__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt6Windowi, 4)   { lb_register(GM_PASS, 0x800C8DD0u, 0x80007470u); }   /* ::WPaneRegister   FNADDR */
E(getPictures__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7Picturei, 4) { lb_register(GM_PASS, 0x800C8E40u, 0x800073D0u); }   /* ::PPaneRegister   FNADDR */
E(getTextBoxes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7TextBoxi, 4) { lb_register(GM_PASS, 0x800C8EB0u, 0x800C8A90u); }  /* ::TPaneRegister   FNADDR */
E(setLangStrings__Q23m2d13EmbedLayout_cFPPCcPCiii, 4) { lb_tpane_names(GM_PASS); }  /* ::TPaneNameRegister */
E(loadAnimations__Q23m2d13EmbedLayout_cFPPCci, 404)  { lb_anime_res(GM_PASS); }     /* ::AnimeResRegister */
E(loadGroups__Q23m2d13EmbedLayout_cFPPCcPCii, 404)   { lb_groups(GM_PASS); }        /* ::GroupRegister */
E(fn_800C9060, 28)  { anmres_ctor(GM_PASS); }                                      /* m2d::AnmResV2_c::AnmResV2_c */
E(fn_800C90B0, 4)   { elem_dtor(GM_PASS, 0x800C90B0u); }                           /* (its element destructor)   FNADDR */
E(fn_800C91B0, 40)  { anmgrp_ctor(GM_PASS); }                                      /* m2d::AnmGroup_c::AnmGroup_c */
GM_HLE(fn_800C91F0) { elem_dtor(GM_PASS, 0x800C91F0u); }                           /* (written but off: never called by the tests)   FNADDR */
E(fn_800C9230, 4)   { elem_dtor(GM_PASS, 0x800C9230u); }                           /* (its element destructor)   FNADDR */
E(fn_800C9680, 4)   { lb_scissor(GM_PASS); }                                       /* ::SetScissorMask */
E(free__Q23m2d13EmbedLayout_cFv, 404) { lb_delete(GM_PASS); }                      /* ::doDelete */
