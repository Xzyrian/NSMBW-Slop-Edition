/* gm_m_fader.c - mLib's screen faders: mFader_c (the current fader: draw, setFader),
 * mFaderBase_c (status, frame count, fadeIn / fadeOut / calc) and mColorFader_c (a coloured
 * full-screen fade: constructor, setStatus, calc - its draw stays recompiled: it writes the GX
 * FIFO). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_fader.cpp, m_fader_base.cpp,
 * m_color_fader.cpp) and checked against the recompiled USA rev 2 code (0x8016AB90-0x8016AD2C,
 * 0x8016DAA0-0x8016DDFC). mFaderBase_c: +0 vtable (+12 setStatus, +16 getStatus, +32 draw),
 * +4 status (0 opaque, 1 hidden, 2 fading in, 3 fading out), +8 flags, +10 frame count,
 * +12 current frame, +16 colour (+19 alpha); mColorFader_c: +20 aspect ratio. */
#include "gm.h"
#include "gm_nv.h"

#define SDA 0x8042F680u
#define CUR_FADER   (SDA - 21056)        /* mFader_c::mFader */
#define VT_FADER_BASE 0x80329AD8u
#define VT_COLOR_FADER 0x80329700u
#define F_G3D_INVALIDATE 0x8024D5E0u     /* nw4r::g3d::G3DState::Invalidate */
#define F_RESET_MATERIAL 0x80164F50u     /* m3d::resetMaterial */
#define F_ASPECT    0x801DD1D0u          /* SCGetAspectRatio */
#define F_DELETE    0x802B9280u

#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f
#define V(o, off) gm_u32(gm_u32(o) + (off))

/* ================================================================== mFaderBase_c */
static gptr base_ctor(GM_CTX, gptr self, gptr color, uint32_t status) {
    FN(0x8016DC00); GM_NV_KEEP;
    NV_R(31, 0); NV_R(30, status); NV_R(29, self);
    gm_set_u32(self, VT_FADER_BASE);
    gm_set_u8(self + 8, 0); gm_set_u16(self + 10, 20); gm_set_u16(self + 12, 0);
    gm_set_u32(self + 16, 0xFFFFFFFFu);
    gm_set_u8(self + 16, gm_u8(color)); gm_set_u8(self + 17, gm_u8(color + 1)); gm_set_u8(self + 18, gm_u8(color + 2));   /* (setColor: a leaf) */
    gm_set_u8(self + 8, gm_u8(self + 8) | 2);                              /* FADE_OUT_COMPLETE */
    if (status == 0) gm_set_u32(self + 4, 0);
    else if (status == 1) gm_set_u32(self + 4, 1);
    return self;
}
static gptr base_dtor(GM_CTX, gptr self, int32_t flags) {
    FN(0x8016DCA0); GM_NV_KEEP;
    NV_R(31, self);
    if (self && flags > 0) GM_CALLR(0x8016DCC8u, F_DELETE, 1, self);
    return self;
}
static uint32_t base_calc(GM_CTX, gptr self) {
    uint32_t s = gm_u32(self + 4), r = 0;
    if (s == 2) {
        uint32_t c = gm_u16(self + 12), n = gm_u16(self + 10);
        gm_set_u16(self + 12, (uint16_t)(c + 1));
        if (c > n) { gm_set_u32(self + 4, 1); r = gm_u8(self + 8) & 1; }
    } else if (s == 3) {
        uint32_t c = gm_u16(self + 12), n = gm_u16(self + 10);
        uint32_t c1 = (c + 1) & 0xFFFF;
        gm_set_u16(self + 12, (uint16_t)c1);
        if ((int32_t)c1 > (int32_t)(n + 1)) { gm_set_u32(self + 4, 0); r = (gm_u8(self + 8) >> 1) & 1; }
    }
    return r;
}

/* ================================================================== mColorFader_c */
static uint32_t color_calc(GM_CTX, gptr self) {
    FN(0x8016AC80); GM_NV_KEEP;
    NV_R(31, self);
    uint32_t r = base_calc(GM_PASS, self);
    uint32_t cur = gm_u16(self + 12), end = gm_u16(self + 10);
    if (cur > end) cur = end;
    switch (gm_u32(self + 4)) {
    case 1: gm_set_u8(self + 19, 0); break;
    case 0: gm_set_u8(self + 19, 255); break;
    case 2: gm_set_u8(self + 19, (uint8_t)(0xFFu - divw((int32_t)(((cur << 8) & 0xFFFF00u) - cur), (int32_t)end))); break;
    case 3: gm_set_u8(self + 19, (uint8_t)divw((int32_t)(((cur << 8) & 0xFFFF00u) - cur), (int32_t)end)); break;
    }
    return r;
}

/* ================================================================== hle entry points
   On (12): reached by the test runs or run inside them (setColor, mFaderBase_c::calc). Written but
   off (not reached): the two destructors. */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
/* mFader_c */
E(fn_8016DAA0) {                                                                               /* mFader_c::draw */
    FN(0x8016DAA0);
    GM_CALLR(0x8016DAB4u, F_G3D_INVALIDATE, 1, 2047);
    GM_CALLR(0x8016DAB8u, F_RESET_MATERIAL, 0);
    gptr fd = gm_u32(CUR_FADER);
    GM_CALLR(0x8016DACCu, V(fd, 32), 1, fd);
}
E(fn_8016DAE0) {                                                                               /* ::setFader(fader) */
    FN(0x8016DAE0); GM_NV_KEEP;
    gptr fader = A(0);
    NV_R(30, fader);
    gptr cur = gm_u32(CUR_FADER);
    if (cur) {
        NV_R(31, 1);
        if (GM_CALLR(0x8016DB1Cu, V(cur, 16), 1, cur) == 2) { GM_RET(0); return; }     /* (fading: can't) */
        cur = gm_u32(CUR_FADER);
        if (GM_CALLR(0x8016DB40u, V(cur, 16), 1, cur) == 3) { GM_RET(0); return; }
        NV_R(31, 0);
    }
    cur = gm_u32(CUR_FADER);
    uint32_t st = cur ? GM_CALLR(0x8016DB80u, V(cur, 16), 1, cur) : GM_CALLR(0x8016DB98u, V(fader, 16), 1, fader);
    gm_set_u32(CUR_FADER, fader);
    if (st == 0) GM_CALLR(0x8016DBC8u, V(fader, 12), 2, fader, 0);
    else if (st == 1) GM_CALLR(0x8016DBE4u, V(fader, 12), 2, fader, 1);
    GM_RET(1);
}
/* mFaderBase_c */
E(fn_8016DC00) { GM_RET(base_ctor(GM_PASS, A(0), A(1), A(2))); }                               /* ::mFaderBase_c(colour, status) */
E(fn_8016DCA0) { GM_RET(base_dtor(GM_PASS, A(0), (int32_t)A(1))); }                            /* ::~mFaderBase_c */
E(fn_8016DCE0) { gm_set_u16(A(0) + 10, (uint16_t)A(1)); }                                      /* ::setFrame */
E(fn_8016DCF0) { gptr c = A(1); gm_set_u8(A(0) + 16, gm_u8(c)); gm_set_u8(A(0) + 17, gm_u8(c + 1)); gm_set_u8(A(0) + 18, gm_u8(c + 2)); }   /* ::setColor */
E(fn_8016DD10) { GM_RET(gm_u32(A(0) + 4)); }                                                   /* ::getStatus */
E(fn_8016DD20) {                                                                               /* ::fadeIn */
    uint32_t r = gm_u32(A(0) + 4) == 0;
    if (r) { gm_set_u32(A(0) + 4, 2); gm_set_u16(A(0) + 12, 0); }
    GM_RET(r);
}
E(fn_8016DD50) {                                                                               /* ::fadeOut */
    uint32_t r = gm_u32(A(0) + 4) == 1;
    if (r) { gm_set_u32(A(0) + 4, 3); gm_set_u16(A(0) + 12, 0); }
    GM_RET(r);
}
E(fn_8016DD80) { GM_RET(base_calc(GM_PASS, A(0))); }                                           /* ::calc */
/* mColorFader_c */
E(fn_8016AB90) {                                                                               /* ::mColorFader_c(colour, status) */
    GM_LR_KEEP; FN(0x8016AB90); GM_NV_KEEP;
    gptr self = A(0);
    NV_R(31, self);
    NCALL(0x8016ABA8u, base_ctor(GM_PASS, self, A(1), A(2)));
    gm_set_u32(self, VT_COLOR_FADER);
    gm_set_u8(self + 20, (uint8_t)GM_CALLR(0x8016ABB8u, F_ASPECT, 0));
    GM_RET(self);
}
E(fn_8016ABE0) {                                                                               /* ::~mColorFader_c */
    GM_LR_KEEP; FN(0x8016ABE0); GM_NV_KEEP;
    gptr self = A(0); int32_t flags = (int32_t)A(1);
    NV_R(31, flags); NV_R(30, self);
    if (self) {
        NCALL(0x8016AC0Cu, base_dtor(GM_PASS, self, 0));
        if (flags > 0) GM_CALLR(0x8016AC1Cu, F_DELETE, 1, self);
    }
    GM_RET(self);
}
E(fn_8016AC40) {                                                                               /* ::setStatus */
    gptr s = A(0);
    if (A(1) == 0) { gm_set_u32(s + 4, 0); gm_set_u8(s + 19, 255); }
    else if (A(1) == 1) { gm_set_u32(s + 4, 1); gm_set_u8(s + 19, 0); }
}
E(fn_8016AC80) { GM_RET(color_calc(GM_PASS, A(0))); }                                          /* ::calc */
