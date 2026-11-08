/* gm_egg.c - EGG library pieces: EGG::ColorFader (ctor, setFrame, setColor, setStatus, fadeIn,
 * fadeOut, calc - the screen fades' alpha ramp). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/lib/egg/core/eggColorFader.cpp) and checked against
 * the recompiled USA rev 2 code (0x802BB030-0x802BB538). Register-exact (R(n)); calc's subfic
 * sets XER[CA] as the PowerPC instruction does; draw writes its quad straight into the write-gather
 * pipe as the PowerPC code does.
 *
 * ColorFader: +0 vtable, +4 status (0 opaque, 1 hidden, 2 fading in, 3 fading out), +8 flags
 * (1 signal on fade in, 2 on fade out), +10 frame count (u16), +12 frame (u16), +16 colour
 * (r, g, b, a), +20 the rectangle (left, top, right, bottom). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

#define F_SET_COLOR 0x802BB0F0u

/* ColorFader(x, y, w, h, color, status) */
static void cf_ctor(GM_CTX) {
    GM_FN(0x802BB030); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(8) = 0x80350000u;
    FB(3, frsp(F(1) + F(3)));                                                /* right */
    FB(0, frsp(F(2) + F(4)));                                                /* bottom */
    R(7) = 0;
    R(8) = R(8) - 296;
    R(6) = 20; R(0) = (uint32_t)-1;
    R(30) = R(3); R(31) = R(5);
    gm_set_u32(R(3), R(8));                                                  /* the vtable */
    gm_set_u8(R(3) + 8, 0);
    gm_set_u16(R(3) + 10, 20);
    gm_set_u16(R(3) + 12, 0);
    gm_set_u32(R(3) + 16, R(0));
    SF(R(3) + 20, F(1)); SF(R(3) + 24, F(2)); SF(R(3) + 28, F(3)); SF(R(3) + 32, F(0));
    R(0) = gm_u32(R(4));
    R(4) = f + 8;
    gm_set_u32(f + 8, R(0));                                                 /* (the colour by value) */
    GM_CALLV(0x802BB09Cu, F_SET_COLOR, 0);
    R(12) = gm_u32(R(30)); R(3) = R(30); R(4) = R(31);
    R(12) = gm_u32(R(12) + 8); ctx->ctr = R(12);
    GM_CALLV(0x802BB0B4u, R(12), 0);                                         /* setStatus */
    R(0) = gm_u8(R(30) + 8);
    R(3) = R(30);
    R(0) = R(0) | 2;
    gm_set_u8(R(30) + 8, (uint8_t)R(0));                                     /* signal on fade out */
    R(0) = lr;
}
static void cf_set_status(GM_CTX) {
    if (cmps(ctx, (int32_t)R(4), 0) == 0) {
        R(4) = 0; R(0) = 255;
        gm_set_u32(R(3) + 4, 0); gm_set_u8(R(3) + 19, 255);
        return;
    }
    if (cmps(ctx, (int32_t)R(4), 1) != 0) return;
    R(4) = 1; R(0) = 0;
    gm_set_u32(R(3) + 4, 1); gm_set_u8(R(3) + 19, 0);
}
/* fadeIn / fadeOut: from opaque / hidden to fading (cntlzw: status == want) */
static void cf_fade(GM_CTX, uint32_t want, uint32_t to) {
    if (want) { R(4) = gm_u32(R(3) + 4); R(0) = R(4) - want; }
    else R(0) = gm_u32(R(3) + 4);
    R(0) = cntlzw(R(0));
    R(5) = R(0) >> 5;
    CR0(ctx, R(5));
    if (!CR_BIT(ctx, 2)) {
        R(4) = to; R(0) = 0;
        gm_set_u32(R(3) + 4, to); gm_set_u16(R(3) + 12, 0);
    }
    R(3) = R(5);
}
/* calc(): the alpha for the status; true when a fade ends with its signal bit */
static void cf_calc(GM_CTX) {
    R(0) = gm_u32(R(3) + 4);
    R(6) = 0;
    if (cmps(ctx, (int32_t)R(0), 1) == 0) { R(0) = 0; gm_set_u8(R(3) + 19, 0); goto out; }
    if (cmps(ctx, (int32_t)R(0), 0) == 0) { R(0) = 255; gm_set_u8(R(3) + 19, 255); goto out; }
    if (cmps(ctx, (int32_t)R(0), 2) == 0) {
        R(4) = gm_u16(R(3) + 12);
        R(5) = gm_u16(R(3) + 10);
        R(0) = R(4) + 1;
        gm_set_u16(R(3) + 12, (uint16_t)R(0));
        if (cmpu(ctx, R(4), R(5)) > 0) {
            R(0) = gm_u8(R(3) + 8);
            R(4) = 1;
            gm_set_u32(R(3) + 4, 1);                                         /* hidden */
            R(4) = R(5);
            R(6) = R(0) & 1;
        }
        R(5) = R(4) & 0xFFFF;
        R(4) = (R(4) << 8) & 0xFFFF00u;
        R(0) = gm_u16(R(3) + 10);
        R(4) = R(4) - R(5);                                                  /* frame * 255 */
        R(0) = divw((int32_t)R(4), (int32_t)R(0));
        { uint32_t a_ = R(0); R(0) = 0xFFu - a_; ctx->xer_ca = 0xFFu >= a_; }   /* (subfic) */
        gm_set_u8(R(3) + 19, (uint8_t)R(0));
        goto out;
    }
    if (cmps(ctx, (int32_t)R(0), 3) != 0) goto out;
    R(7) = gm_u16(R(3) + 12);
    R(5) = gm_u16(R(3) + 10);
    R(0) = R(7) + 1;
    gm_set_u16(R(3) + 12, (uint16_t)R(0));
    if (cmpu(ctx, R(7), R(5)) > 0) {
        R(0) = R(5) + 1;
        if (cmps(ctx, (int32_t)R(7), (int32_t)R(0)) > 0) {
            R(0) = gm_u8(R(3) + 8);
            R(4) = 0;
            gm_set_u32(R(3) + 4, 0);                                         /* opaque */
            R(6) = (R(0) >> 1) & 1;
        }
        R(5) = gm_u16(R(3) + 10);
        R(7) = R(5);
    }
    R(4) = R(7) & 0xFFFF;
    R(0) = (R(7) << 8) & 0xFFFF00u;
    R(0) = R(0) - R(4);
    R(0) = divw((int32_t)R(0), (int32_t)R(5));
    gm_set_u8(R(3) + 19, (uint8_t)R(0));
out:
    R(3) = R(6);
}

/* draw(): a quad over the rectangle in the colour (skipped at alpha 0): the ortho projection,
   viewport and scissor of the rectangle, one channel / TEV stage passing the colour, blending
   unless opaque; the vertices straight into the write-gather pipe (0xCC008000) */
#define LF(a) ldfs(base, (a))
#define WGP 0xCC008000u
static void cf_draw(GM_CTX) {
    GM_FN(0x802BB2A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(28) = R(3);
    R(0) = gm_u8(R(3) + 19);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) goto out;
    FB(1, LF(R(28) + 24)); R(3) = f + 64;
    FB(2, LF(R(28) + 32)); FB(3, LF(R(28) + 20)); FB(4, LF(R(28) + 28));
    FB(5, LF(R(2) - 16208)); FB(6, LF(R(2) - 16204));                        /* 0.0f, 1.0f */
    GM_CALLV(0x802BB2F4u, 0x801C1350u, 0);                                   /* C_MTXOrtho */
    R(3) = f + 64; R(4) = 1;
    GM_CALLV(0x802BB300u, 0x801C9840u, 0);                                   /* GXSetProjection */
    FB(3, LF(R(28) + 32)); FB(1, LF(R(28) + 24)); FB(2, LF(R(28) + 28));
    FB(4, frsp(F(3) - F(1)));
    FB(0, LF(R(28) + 20)); FB(1, LF(R(28) + 20));
    FB(3, frsp(F(2) - F(0)));
    FB(2, LF(R(28) + 24));
    FB(5, LF(R(2) - 16208)); FB(6, LF(R(2) - 16204));
    GM_CALLV(0x802BB32Cu, 0x801C9C10u, 0);                                   /* GXSetViewport */
    FB(1, LF(R(28) + 32)); FB(0, LF(R(28) + 24)); FB(2, LF(R(28) + 28));
    FB(1, frsp(F(1) - F(0)));
    FB(0, LF(R(28) + 20));
    FB(31, frsp(F(2) - F(0)));
    GM_CALLV(0x802BB348u, 0x802DCC4Cu, 0);                                   /* __cvt_fp2unsigned */
    ctx->f[1].u = ctx->f[31].u;
    R(29) = R(3);
    GM_CALLV(0x802BB354u, 0x802DCC4Cu, 0);
    FB(1, LF(R(28) + 24)); R(30) = R(3);
    GM_CALLV(0x802BB360u, 0x802DCC4Cu, 0);
    FB(1, LF(R(28) + 20)); R(31) = R(3);
    GM_CALLV(0x802BB36Cu, 0x802DCC4Cu, 0);
    R(4) = R(31); R(5) = R(30); R(6) = R(29);
    GM_CALLV(0x802BB37Cu, 0x801C9C60u, 0);                                   /* GXSetScissor */
    R(3) = f + 16;
    GM_CALLV(0x802BB384u, 0x801C04D0u, 0);                                   /* PSMTXIdentity */
    R(3) = f + 16; R(4) = 0;
    GM_CALLV(0x802BB390u, 0x801C9940u, 0);                                   /* GXLoadPosMtxImm */
    R(3) = 0;
    GM_CALLV(0x802BB398u, 0x801C9A60u, 0);                                   /* GXSetCurrentMtx */
    GM_CALLV(0x802BB39Cu, 0x801C4070u, 0);                                   /* GXClearVtxDesc */
    GM_CALLV(0x802BB3A0u, 0x801C47C0u, 0);                                   /* GXInvalidateVtxCache */
    R(3) = 9; R(4) = 1;
    GM_CALLV(0x802BB3ACu, 0x801C37C0u, 0);                                   /* GXSetVtxDesc(POS, DIRECT) */
    R(3) = 0; R(4) = 9; R(5) = 1; R(6) = 4; R(7) = 0;
    GM_CALLV(0x802BB3C4u, 0x801C40B0u, 0);                                   /* GXSetVtxAttrFmt */
    R(3) = 1;
    GM_CALLV(0x802BB3CCu, 0x801C6AC0u, 0);                                   /* GXSetNumChans */
    R(0) = gm_u32(R(28) + 16);
    R(4) = f + 8;
    gm_set_u32(f + 8, R(0));
    R(3) = 4;
    GM_CALLV(0x802BB3E0u, 0x801C69E0u, 0);                                   /* GXSetChanMatColor */
    R(3) = 4; R(4) = 0; R(5) = 0; R(6) = 0; R(7) = 0; R(8) = 0; R(9) = 2;
    GM_CALLV(0x802BB400u, 0x801C6AF0u, 0);                                   /* GXSetChanCtrl */
    R(3) = 0; GM_CALLV(0x802BB408u, 0x801C4A20u, 0);                         /* GXSetNumTexGens */
    R(3) = 0; GM_CALLV(0x802BB410u, 0x801C8110u, 0);                         /* GXSetNumIndStages */
    R(3) = 0; GM_CALLV(0x802BB418u, 0x801C81F0u, 0);                         /* __GXSetIndirectMask */
    R(3) = 1; GM_CALLV(0x802BB420u, 0x801C88F0u, 0);                         /* GXSetNumTevStages */
    R(3) = 0; R(4) = 4; GM_CALLV(0x802BB42Cu, 0x801C8250u, 0);               /* GXSetTevOp(PASSCLR) */
    R(3) = 0; R(4) = 255; R(5) = 255; R(6) = 4;
    GM_CALLV(0x802BB440u, 0x801C8790u, 0);                                   /* GXSetTevOrder */
    R(0) = gm_u8(R(28) + 19);
    if (cmpu(ctx, R(0), 0xFF) == 0) { R(3) = 0; R(4) = 1; R(5) = 0; R(6) = 15; GM_CALLV(0x802BB460u, 0x801C8DC0u, 0); }
    else { R(3) = 1; R(4) = 4; R(5) = 5; R(6) = 15; GM_CALLV(0x802BB478u, 0x801C8DC0u, 0); }   /* GXSetBlendMode */
    R(3) = 1; GM_CALLV(0x802BB480u, 0x801C8E10u, 0);                         /* GXSetColorUpdate */
    R(3) = 1; GM_CALLV(0x802BB488u, 0x801C8E40u, 0);                         /* GXSetAlphaUpdate */
    R(3) = 0; R(4) = 0; R(5) = 0; GM_CALLV(0x802BB498u, 0x801C8E70u, 0);     /* GXSetZMode */
    R(3) = 2; GM_CALLV(0x802BB4A0u, 0x801C5860u, 0);                         /* GXSetCullMode */
    R(3) = 128; R(4) = 0; R(5) = 4;
    GM_CALLV(0x802BB4B0u, 0x801C5570u, 0);                                   /* GXBegin(QUADS, 0, 4) */
    static const uint8_t vx[4][2] = { { 20, 24 }, { 28, 24 }, { 28, 32 }, { 20, 32 } };
    R(3) = 0xCC010000u;
    for (int i = 0; i < 4; i++) {
        FB(1, LF(R(28) + vx[i][1])); FB(0, LF(R(28) + vx[i][0]));
        SF(WGP, F(0)); SF(WGP, F(1));
        FB(0, LF(R(2) - 16208)); SF(WGP, F(0));
    }
out:
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
/* (plain GM_HLE below: written but off - no test reaches it; not in hle_funcs.txt) */
#ifdef GM_EGG_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_EGG_COUNT)   /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_802BB030, 36) { cf_ctor(GM_PASS); }                                           /* EGG::ColorFader::ColorFader */
GM_HLE(fn_802BB0E0) { gm_set_u16(R(3) + 10, (uint16_t)R(4)); }                      /* ::setFrame */
E(fn_802BB0F0, 36) {                                                               /* ::setColor (not alpha) */
    R(0) = gm_u8(R(4)); gm_set_u8(R(3) + 16, (uint8_t)R(0));
    R(0) = gm_u8(R(4) + 1); gm_set_u8(R(3) + 17, (uint8_t)R(0));
    R(0) = gm_u8(R(4) + 2); gm_set_u8(R(3) + 18, (uint8_t)R(0));
}
E(fn_802BB110, 36) { cf_set_status(GM_PASS); }                                     /* ::setStatus */
GM_HLE(fn_802BB150) { cf_fade(GM_PASS, 0, 2); }                                     /* ::fadeIn */
GM_HLE(fn_802BB180) { cf_fade(GM_PASS, 1, 3); }                                     /* ::fadeOut */
E(fn_802BB1B0, 36) { cf_calc(GM_PASS); }                                           /* ::calc */
E(fn_802BB2A0, 36) { cf_draw(GM_PASS); }                                           /* ::draw */
