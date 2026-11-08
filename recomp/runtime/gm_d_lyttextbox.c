/* gm_d_lyttextbox.c - LytTextBox_c, the game's text box: setMessage (a BMG message into the box:
 * its font, the shadow user data, the tag-processed text, then the character width fitted to the
 * box - measured once with and once without the character spacing), setText (the tag processor
 * into a 512-character buffer). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_lyttextbox.cpp) and checked against the
 * recompiled USA rev 2 code (0x800C9A60-0x800C9F0C). Register-exact (R(n)): the varargs entries
 * save f1-f8 only when CR6 says there are float arguments (as the PowerPC code does) and build
 * their va_list in the frame; setMessage keeps its float temporaries and the 0x43300000 int ->
 * float conversions on the stack.
 *
 * nw4r::lyt::TextBox: +76 / +80 the size, +232 / +236 the font size, +244 the character space.
 * dInfo_c (r13 - 22276): +976 / +980 the message group / ID, +986 the shadow flag. LytBase_c::
 * s_TagPrc is 0x80358770 (+196 the font index); its buffer 0x80359538. */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d
#define LF(a) ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }

#define SDA_INFO        22276            /* dInfo_c::m_instance */
#define SDA_ZERO_WIDTH  21944            /* TagProcessor_c::isZeroWidthSpace */
#define SDA_SHADOW_NAME 31352            /* "shadow" */
#define TAGPRC          (0x80360000u - 27536u)
#define TEXT_BUF        (0x80360000u - 27336u)
#define F_SET_MESSAGE   0x800C9B50u
#define F_EXT_SETUP     0x800C9B00u
#define F_SET_TEXT_VA   0x800C9E80u
#define F_FIND_EXT_DATA 0x802AC480u      /* nw4r::lyt::Pane::FindExtUserDataByName */
#define F_EXT_DATA_NUM  0x802AC460u      /* ::GetExtUserDataNum */
#define F_MSG_FONT      0x800CE7D0u      /* MsgRes_c::getFont */
#define F_MSG_SCALE     0x800CE7A0u      /* MsgRes_c::getScale */
#define F_MSG_GET       0x802D7860u      /* EGG::MsgRes::getMsg */
#define F_FONT_GET      0x800B1310u      /* dFontMng_c::getFont */
#define F_SET_FONT      0x802AF080u      /* nw4r::lyt::TextBox::SetFont */
#define F_GET_FONT      0x802AF070u      /* ::GetFont */
#define F_DRAW_RECT     0x802AF240u      /* ::GetTextDrawRect(writer) */
#define F_WRITER_CT     0x80230780u      /* nw4r::ut::TextWriterBase<wchar_t>::TextWriterBase */
#define F_WRITER_DT     0x802307E0u
#define F_PREPROCESS    0x800E71C0u      /* TagProcessor_c::preProcess */

/* the varargs entries: f1-f8 into the frame when CR6 is set (float arguments) */
static inline void va_floats(GM_CTX, gptr f) {
    if (CR_BIT(ctx, 6))
        for (int i = 0; i < 8; i++) st64(base, f + 40 + 8 * i, ctx->f[1 + i].u);
}

/* setMessage(bmg, group, id, param, ...) */
static void tb_set_message_v(GM_CTX) {
    GM_FN(0x800C9A60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    va_floats(GM_PASS, f);
    gm_set_u32(f + 8, R(3));
    R(31) = f + 104;
    R(30) = gm_u32(R(13) - SDA_INFO);
    R(11) = f + 136;
    gm_set_u32(f + 28, R(8));
    R(0) = f + 8;
    R(12) = 0x05000000u;                                                     /* (the va_list: 5 GPRs used) */
    R(8) = R(31);
    gm_set_u32(f + 12, R(4)); gm_set_u32(f + 24, R(7)); gm_set_u32(f + 20, R(6));
    gm_set_u32(f + 32, R(9)); gm_set_u32(f + 36, R(10)); gm_set_u32(f + 16, R(5));
    gm_set_u32(R(30) + 976, R(5));
    gm_set_u32(R(30) + 980, R(6));
    gm_set_u32(f + 104, R(12)); gm_set_u32(f + 108, R(11)); gm_set_u32(f + 112, R(0));
    GM_CALLV(0x800C9AE8u, F_SET_MESSAGE, 0);
    R(0) = lr;
}
/* ExtensionUserDataSetup(): a non-zero "shadow" user data sets dInfo's shadow flag */
static void tb_ext_setup(GM_CTX) {
    GM_FN(0x800C9B00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(4) = R(13) - SDA_SHADOW_NAME;
    R(31) = gm_u32(R(13) - SDA_INFO);
    GM_CALLV(0x800C9B1Cu, F_FIND_EXT_DATA, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        R(0) = gm_u32(R(3) + 4);
        R(0) = gm_u32(R(3) + R(0));
        if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(0) = 1; gm_set_u8(R(31) + 986, 1); }
    }
    R(0) = lr;
}
/* the font's width (r3: the box): GetFont()->GetWidth() as a double through the stack */
static void tb_font_width(GM_CTX, gptr f, uint32_t ra) {
    GM_CALLV(ra, F_GET_FONT, 0);
    R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 12); ctx->ctr = R(12);
    GM_CALLV(ra + 0x10, R(12), 0);                                           /* Font::GetWidth */
    R(0) = R(3) ^ 0x80000000u;
    gm_set_u32(f + 180, R(0));
}
/* setMessage(bmg, group, id, param, va_list *) */
static void tb_set_message(GM_CTX) {
    GM_FN(0x800C9B50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 224;
    FB(1, LF(R(3) + 232));
    R(25) = R(4);
    FB(0, LF(R(3) + 236));
    R(26) = R(5); R(27) = R(6); R(24) = R(3);
    SF(f + 24, F(1));
    R(28) = R(7); R(29) = R(8);
    R(3) = R(25);
    SF(f + 28, F(0));
    R(4) = R(26); R(5) = R(27);
    GM_CALLV(0x800C9BACu, F_MSG_FONT, 0);
    R(31) = R(3);
    R(3) = R(3) & 0xFF;
    GM_CALLV(0x800C9BB8u, F_FONT_GET, 0);
    R(4) = R(3); R(3) = R(24);
    GM_CALLV(0x800C9BC4u, F_SET_FONT, 0);
    R(3) = 0x80360000u;
    R(30) = gm_u32(R(13) - SDA_INFO);
    R(3) = R(3) - 27536;
    R(0) = 0;
    gm_set_u8(R(3) + 196, (uint8_t)R(31));                                   /* s_TagPrc.mFontIndex */
    R(3) = R(24);
    gm_set_u8(R(30) + 986, 0);
    GM_CALLV(0x800C9BE4u, F_EXT_DATA_NUM, 0);
    R(0) = R(3) & 0xFFFF;
    if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(3) = R(24); GM_CALLV(0x800C9BF4u, F_EXT_SETUP, 0); }
    gm_set_u32(R(30) + 976, R(26));
    R(3) = R(25); R(4) = R(26); R(5) = R(27);
    gm_set_u32(R(30) + 980, R(27));
    GM_CALLV(0x800C9C0Cu, F_MSG_GET, 0);
    R(4) = R(3); R(3) = R(24); R(5) = R(28); R(6) = R(29); R(7) = R(25);
    GM_CALLV(0x800C9C24u, F_SET_TEXT_VA, 0);
    R(3) = R(25); R(4) = R(26); R(5) = R(27);
    GM_CALLV(0x800C9C34u, F_MSG_SCALE, 0);
    R(0) = R(3) & 0xFFFF;
    R(31) = 0x43300000u;
    gm_set_u32(f + 172, R(0));
    R(3) = R(24);
    ctx->f[2].u = ld64(base, R(2) - 26456);
    gm_set_u32(f + 168, R(31));
    FB(0, LF(R(2) - 26472));                                                 /* 0.01f */
    ctx->f[1].u = ld64(base, f + 168);
    FB(1, frsp(F(1) - F(2)));
    FB(31, frsp(F(0) * F(1)));                                               /* charWScale */
    tb_font_width(GM_PASS, f, 0x800C9C60u);
    FB(1, LF(R(24) + 80));
    R(3) = f + 64;
    gm_set_u32(f + 176, R(31));
    ctx->f[3].u = ld64(base, R(2) - 26448);
    ctx->f[0].u = ld64(base, f + 176);
    FB(2, LF(R(24) + 76));
    FB(4, frsp(F(0) - F(3)));
    FB(3, LF(f + 28));
    SF(R(24) + 236, F(3));
    FB(0, LF(R(2) - 26468));                                                 /* 1024.0f */
    FB(3, frsp(F(31) * F(4)));
    SF(f + 16, F(2)); SF(f + 24, F(3)); SF(R(24) + 232, F(3));
    SF(f + 20, F(1)); SF(f + 12, F(1)); SF(f + 8, F(0));
    SF(R(24) + 76, F(0)); SF(R(24) + 80, F(1));
    GM_CALLV(0x800C9CC8u, F_WRITER_CT, 0);
    FB(30, LF(R(24) + 244));
    R(4) = R(24); R(3) = f + 48; R(5) = f + 64;
    GM_CALLV(0x800C9CDCu, F_DRAW_RECT, 0);                                   /* with the spacing */
    FB(0, LF(R(2) - 26464));
    R(0) = 1;
    SF(R(24) + 244, F(0));
    R(4) = R(24); R(3) = f + 32; R(5) = f + 64;
    gm_set_u8(R(13) - SDA_ZERO_WIDTH, 1);
    GM_CALLV(0x800C9CFCu, F_DRAW_RECT, 0);                                   /* without */
    R(0) = 0;
    gm_set_u8(R(13) - SDA_ZERO_WIDTH, 0);
    FB(2, LF(f + 16)); FB(0, LF(f + 20));
    SF(R(24) + 244, F(30));
    FB(1, LF(f + 16));
    SF(R(24) + 76, F(2)); SF(R(24) + 80, F(0));
    FB(4, LF(f + 40)); FB(3, LF(f + 32)); FB(2, LF(f + 56)); FB(0, LF(f + 48));
    FB(3, frsp(F(4) - F(3)));                                                /* widthNoSpace */
    FB(0, frsp(F(2) - F(0)));                                                /* widthWithSpace */
    cr_fcmp(ctx, 0, F(1), F(0));
    FB(2, frsp(F(0) - F(3)));                                                /* widthDiff */
    if (CR_BIT(ctx, 0)) {
        FB(0, LF(R(2) - 26464));
        cr_fcmp(ctx, 0, F(3), F(0));
        if (CR_BIT(ctx, 1)) {
            FB(1, frsp(F(1) - F(2)));
            FB(0, LF(R(2) - 26460));                                         /* 4.0f */
            ctx->f[2].u = ctx->f[31].u;
            FB(0, frsp(F(1) - F(0)));
            FB(0, frsp(F(0) / F(3)));
            FB(31, frsp(F(31) * F(0)));
            cr_fcmp(ctx, 0, F(31), F(2));
            if (CR_BIT(ctx, 0)) {
                R(3) = R(24);
                tb_font_width(GM_PASS, f, 0x800C9D74u);
                FB(0, LF(f + 28));
                gm_set_u32(f + 176, R(31));
                ctx->f[2].u = ld64(base, R(2) - 26448);
                ctx->f[1].u = ld64(base, f + 176);
                SF(R(24) + 236, F(0));
                FB(0, frsp(F(1) - F(2)));
                FB(0, frsp(F(31) * F(0)));
                SF(f + 24, F(0)); SF(R(24) + 232, F(0));
            }
        }
    }
    R(3) = f + 64; R(4) = (uint32_t)-1;
    GM_CALLV(0x800C9DBCu, F_WRITER_DT, 0);
    R(11) = f + 224;
    R(0) = lr;
}
/* setText(text, count, ...) */
static void tb_set_text_v(GM_CTX) {
    GM_FN(0x800C9DF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    va_floats(GM_PASS, f);
    R(11) = f + 136;
    R(0) = f + 8;
    R(12) = 0x03000000u;
    gm_set_u32(f + 24, R(7));
    R(31) = f + 104;
    R(7) = 0;
    gm_set_u32(f + 20, R(6));
    R(6) = R(31);
    gm_set_u32(f + 8, R(3)); gm_set_u32(f + 12, R(4)); gm_set_u32(f + 16, R(5));
    gm_set_u32(f + 28, R(8)); gm_set_u32(f + 32, R(9)); gm_set_u32(f + 36, R(10));
    gm_set_u32(f + 104, R(12)); gm_set_u32(f + 108, R(11)); gm_set_u32(f + 112, R(0));
    GM_CALLV(0x800C9E6Cu, F_SET_TEXT_VA, 0);
    R(0) = lr;
}
/* setText(text, count, va_list *, bmg): preProcess into the buffer, SetString(buffer, 0, n) */
static void tb_set_text(GM_CTX) {
    GM_FN(0x800C9E80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(9) = R(6); R(10) = R(7);
    R(0) = 0;
    R(6) = 0x80360000u;
    R(8) = R(5);
    R(31) = 0x80360000u;
    R(7) = f + 8;
    R(30) = R(3);
    R(3) = R(6) - 27536;
    R(5) = R(31) - 27336;
    gm_set_u32(f + 8, 0);
    R(6) = 512;
    GM_CALLV(0x800C9EC8u, F_PREPROCESS, 0);
    R(12) = gm_u32(R(30));
    R(3) = R(30);
    R(0) = gm_u32(f + 8);
    R(4) = R(31) - 27336;
    R(12) = gm_u32(R(12) + 128);
    R(5) = 0;
    R(6) = R(0) & 0xFFFF;
    ctx->ctr = R(12);
    GM_CALLV(0x800C9EECu, R(12), 0);                                         /* SetString */
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_TB_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_TB_COUNT)    /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(WriteBMGToTextBox__FPQ34nw4r3lyt7TextBoxPQ27dScript5Res_ciiie, 4) { tb_set_message_v(GM_PASS); }   /* LytTextBox_c::setMessage(..., ...) */
E(fn_800C9B00, 4) { tb_ext_setup(GM_PASS); }                                       /* ::ExtensionUserDataSetup */
E(fn_800C9B50, 4) { tb_set_message(GM_PASS); }                                     /* ::setMessage(..., va_list *) */
E(fn_800C9DF0, 4) { tb_set_text_v(GM_PASS); }                                      /* ::setText(text, n, ...) */
E(fn_800C9E80, 4) { tb_set_text(GM_PASS); }                                        /* ::setText(text, n, va_list *, bmg) */
