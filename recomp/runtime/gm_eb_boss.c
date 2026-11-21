/* gm_eb_boss.c - instance 2 (track B): the boss module d_en_bossNP (fn_4_*, linked at
 * 0x80B1CA50-0x80B74000) - the castle / tower / airship bosses and their parts. Transliterated by
 * tools/gm_conv.py from the recompiled bodies (statement for statement in the natives' macros);
 * only functions the A/B inputs (tools/ab_inputs/) reach are on, the gate is the strict A/B
 * (against the previous build and against the build with no natives, CHANGELOG (115)).
 * Functions another runtime file defines or calls by symbol are left to their owners.
 * Names are owed (eb_m_<addr>).
 * Build flags (testing): -DGM_EB_COUNT logs each native's first call, -DGM_EB_VERIFY makes them
 * switchable (RT_GM_VERIFY=orig:<names>). */

#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d

/* fn_4_110 (fn_4_110, 64 bytes) */
static void eb_m_1cb60(GM_CTX) {
    GM_FN(0x80B1CB60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80B1CB88; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80B1CB88; }
    GM_CALLV(0x80B1CB88u, 0x802B9280u, 0);
L_80B1CB88:;
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_4_2E10 (fn_4_2E10, 8 bytes) */
static void eb_m_1f860(GM_CTX) {
    R(3) = (R(3) + 909);
}

/* fn_4_2E60 (fn_4_2E60, 8 bytes) */
static void eb_m_1f8b0(GM_CTX) {
    R(3) = (R(3) + 1124);
    GM_TAIL(0x8009EA50u, 0); return;
}

/* fn_4_3100 (fn_4_3100, 92 bytes) */
static void eb_m_1fb50(GM_CTX) {
    GM_FN(0x80B1FB50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 1528));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B1FB98; }
    R(3) = (0 + 8);
    GM_CALLV(0x80B1FB78u, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B1FB94; }
    R(0) = (0 + 18);
    st32(base, (R(3) + 4), R(0));
    R(4) = (0 + 0x80B70000u);
    R(4) = (R(4) + 25864);
    st32(base, (R(3) + 0), R(4));
L_80B1FB94:;
    st32(base, (R(31) + 1528), R(3));
L_80B1FB98:;
    R(0) = lr;
}

/* fn_4_3200 (fn_4_3200, 4 bytes) */
static void eb_m_1fc50(GM_CTX) {

}

/* fn_4_3280 (fn_4_3280, 32 bytes) */
static void eb_m_1fcd0(GM_CTX) {
    R(12) = ld32(base, (R(3) + 1348));
    R(4) = (0 + 1288);
    R(5) = (int16_t)ld16(base, (R(3) + 1520));
    R(6) = (0 + 0);
    R(12) = ld32(base, (R(12) + 48));
    ctx->ctr = R(12);
    R(3) = (R(3) + 1348);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_4_32A0 (fn_4_32A0, 32 bytes) */
static void eb_m_1fcf0(GM_CTX) {
    R(12) = ld32(base, (R(3) + 1348));
    R(4) = (0 + 1286);
    R(5) = (int16_t)ld16(base, (R(3) + 1520));
    R(6) = (0 + 0);
    R(12) = ld32(base, (R(12) + 48));
    ctx->ctr = R(12);
    R(3) = (R(3) + 1348);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_4_3370 (fn_4_3370, 12 bytes) */
static void eb_m_1fdc0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 1940));
    R(3) = R(0) & 0x2u;
}

/* fn_4_3380 (fn_4_3380, 32 bytes) */
static void eb_m_1fdd0(GM_CTX) {
    R(5) = (0 + 0x80B70000u);
    R(4) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(5) + 15192); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 15308); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_4_33A0 (fn_4_33A0, 20 bytes) */
static void eb_m_1fdf0(GM_CTX) {
    { uint32_t ea_ = (R(4) + 1928); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 1924); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[1].d); }
}

/* fn_4_3640 (fn_4_3640, 44 bytes) */
static void eb_m_20090(GM_CTX) {
    R(4) = ld32(base, (R(3) + 4));
    R(3) = (0 + 0x2AAB0000u);
    R(5) = (R(3) + -21845);
    R(0) = (R(4) + -1);
    R(3) = (0 + 1);
    R(4) = (((int64_t)(int32_t)R(5) * (int32_t)R(0)) >> 32);
    R(0) = rotl32(R(4), 1) & 0x1u;
    R(0) = R(4) + R(0);
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(3), (R(0) & 31)) & 0x1u;
}

/* fn_4_36A0 (fn_4_36A0, 52 bytes) */
static void eb_m_200f0(GM_CTX) {
    R(4) = ld32(base, (R(3) + 4));
    R(3) = (0 + 0x2AAB0000u);
    R(3) = (R(3) + -21845);
    R(0) = (R(4) + -1);
    R(3) = (((int64_t)(int32_t)R(3) * (int32_t)R(0)) >> 32);
    R(0) = rotl32(R(3), 1) & 0x1u;
    R(4) = R(3) + R(0);
    R(0) = R(4) ^ 0x1u;
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0x1u) != 0; R(3) = (v_ >> 1); }
    R(0) = R(0) &R(4);
    R(0) = R(3) - R(0);
    R(3) = rotl32(R(0), 1) & 0x1u;
}

/* fn_4_3730 (fn_4_3730, 4 bytes) */
static void eb_m_20180(GM_CTX) {

}

/* fn_4_3740 (fn_4_3740, 4 bytes) */
static void eb_m_20190(GM_CTX) {

}

/* fn_4_3790 (fn_4_3790, 3660 bytes) */
static void eb_m_201e0(GM_CTX) {
    GM_FN(0x80B201E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 704);
    R(27) = (0 + 0x80B70000u);
    R(26) = (0 + 0x80B90000u);
    R(27) = (R(27) + 23784);
    R(3) = (R(27) + 2256);
    R(23) = ld32(base, (R(27) + 2256));
    R(6) = (R(27) + 2268);
    R(5) = (R(27) + 2280);
    R(12) = ld32(base, (R(3) + 4));
    R(26) = (R(26) + -25896);
    R(11) = ld32(base, (R(3) + 8));
    R(4) = (R(27) + 2904);
    R(10) = ld32(base, (R(27) + 2268));
    R(3) = (R(26) + 16);
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2280));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 620), R(23));
    st32(base, (f + 624), R(12));
    st32(base, (f + 628), R(11));
    st32(base, (f + 632), R(10));
    st32(base, (f + 636), R(9));
    st32(base, (f + 640), R(8));
    st32(base, (f + 644), R(7));
    st32(base, (f + 648), R(6));
    st32(base, (f + 652), R(0));
    GM_CALLV(0x80B20264u, 0x8015F7C0u, 0);
    R(28) = (0 + 0x80B70000u);
    R(3) = (R(26) + 16);
    R(23) = ld32(base, (f + 644));
    R(28) = (R(28) + 27488);
    R(12) = ld32(base, (f + 648));
    R(29) = (0 + 0x80B20000u);
    R(11) = ld32(base, (f + 652));
    R(4) = (R(29) + 4144);
    R(10) = ld32(base, (f + 632));
    R(5) = (R(26) + 0);
    R(9) = ld32(base, (f + 636));
    R(8) = ld32(base, (f + 640));
    R(7) = ld32(base, (f + 620));
    R(6) = ld32(base, (f + 624));
    R(0) = ld32(base, (f + 628));
    st32(base, (R(26) + 16), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B202CCu, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2292);
    R(6) = (R(27) + 2304);
    R(5) = (R(27) + 2316);
    R(23) = ld32(base, (R(27) + 2292));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2948);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 80);
    R(10) = ld32(base, (R(27) + 2304));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2316));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 584), R(23));
    st32(base, (f + 588), R(12));
    st32(base, (f + 592), R(11));
    st32(base, (f + 596), R(10));
    st32(base, (f + 600), R(9));
    st32(base, (f + 604), R(8));
    st32(base, (f + 608), R(7));
    st32(base, (f + 612), R(6));
    st32(base, (f + 616), R(0));
    GM_CALLV(0x80B2032Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 80);
    R(23) = ld32(base, (f + 608));
    R(12) = ld32(base, (f + 612));
    R(4) = (R(29) + 4144);
    R(11) = ld32(base, (f + 616));
    R(5) = (R(26) + 64);
    R(10) = ld32(base, (f + 596));
    R(9) = ld32(base, (f + 600));
    R(8) = ld32(base, (f + 604));
    R(7) = ld32(base, (f + 584));
    R(6) = ld32(base, (f + 588));
    R(0) = ld32(base, (f + 592));
    st32(base, (R(26) + 80), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B20388u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2328);
    R(6) = (R(27) + 2340);
    R(5) = (R(27) + 2352);
    R(23) = ld32(base, (R(27) + 2328));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2988);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 144);
    R(10) = ld32(base, (R(27) + 2340));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2352));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 548), R(23));
    st32(base, (f + 552), R(12));
    st32(base, (f + 556), R(11));
    st32(base, (f + 560), R(10));
    st32(base, (f + 564), R(9));
    st32(base, (f + 568), R(8));
    st32(base, (f + 572), R(7));
    st32(base, (f + 576), R(6));
    st32(base, (f + 580), R(0));
    GM_CALLV(0x80B203E8u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 144);
    R(23) = ld32(base, (f + 572));
    R(12) = ld32(base, (f + 576));
    R(4) = (R(29) + 4144);
    R(11) = ld32(base, (f + 580));
    R(5) = (R(26) + 128);
    R(10) = ld32(base, (f + 560));
    R(9) = ld32(base, (f + 564));
    R(8) = ld32(base, (f + 568));
    R(7) = ld32(base, (f + 548));
    R(6) = ld32(base, (f + 552));
    R(0) = ld32(base, (f + 556));
    st32(base, (R(26) + 144), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B20444u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2364);
    R(6) = (R(27) + 2376);
    R(5) = (R(27) + 2388);
    R(23) = ld32(base, (R(27) + 2364));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 3032);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 208);
    R(10) = ld32(base, (R(27) + 2376));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2388));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 512), R(23));
    st32(base, (f + 516), R(12));
    st32(base, (f + 520), R(11));
    st32(base, (f + 524), R(10));
    st32(base, (f + 528), R(9));
    st32(base, (f + 532), R(8));
    st32(base, (f + 536), R(7));
    st32(base, (f + 540), R(6));
    st32(base, (f + 544), R(0));
    GM_CALLV(0x80B204A4u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 208);
    R(23) = ld32(base, (f + 536));
    R(12) = ld32(base, (f + 540));
    R(4) = (R(29) + 4144);
    R(11) = ld32(base, (f + 544));
    R(5) = (R(26) + 192);
    R(10) = ld32(base, (f + 524));
    R(9) = ld32(base, (f + 528));
    R(8) = ld32(base, (f + 532));
    R(7) = ld32(base, (f + 512));
    R(6) = ld32(base, (f + 516));
    R(0) = ld32(base, (f + 520));
    st32(base, (R(26) + 208), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B20500u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2400);
    R(6) = (R(27) + 2412);
    R(5) = (R(27) + 2424);
    R(23) = ld32(base, (R(27) + 2400));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 3072);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 272);
    R(10) = ld32(base, (R(27) + 2412));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2424));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 476), R(23));
    st32(base, (f + 480), R(12));
    st32(base, (f + 484), R(11));
    st32(base, (f + 488), R(10));
    st32(base, (f + 492), R(9));
    st32(base, (f + 496), R(8));
    st32(base, (f + 500), R(7));
    st32(base, (f + 504), R(6));
    st32(base, (f + 508), R(0));
    GM_CALLV(0x80B20560u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 272);
    R(23) = ld32(base, (f + 500));
    R(12) = ld32(base, (f + 504));
    R(4) = (R(29) + 4144);
    R(11) = ld32(base, (f + 508));
    R(5) = (R(26) + 256);
    R(10) = ld32(base, (f + 488));
    R(9) = ld32(base, (f + 492));
    R(8) = ld32(base, (f + 496));
    R(7) = ld32(base, (f + 476));
    R(6) = ld32(base, (f + 480));
    R(0) = ld32(base, (f + 484));
    st32(base, (R(26) + 272), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B205BCu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2436);
    R(4) = (R(27) + 2448);
    R(3) = (R(27) + 2460);
    R(11) = ld32(base, (R(27) + 2436));
    R(10) = ld32(base, (R(5) + 4));
    R(30) = (R(27) + 3116);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2448));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2460));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 440), R(11));
    st32(base, (f + 444), R(10));
    st32(base, (f + 448), R(9));
    st32(base, (f + 452), R(8));
    st32(base, (f + 456), R(7));
    st32(base, (f + 460), R(6));
    st32(base, (f + 464), R(5));
    st32(base, (f + 468), R(4));
    st32(base, (f + 472), R(0));
    GM_CALLV(0x80B20618u, 0x80B211A0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(30) |R(30);
    R(3) = (R(26) + 332);
    GM_CALLV(0x80B20628u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 332);
    R(23) = ld32(base, (f + 464));
    R(12) = ld32(base, (f + 468));
    R(30) = (0 + 0x80B70000u);
    R(11) = ld32(base, (f + 472));
    R(30) = (R(30) + 27436);
    R(10) = ld32(base, (f + 452));
    R(31) = (0 + 0x80B20000u);
    R(9) = ld32(base, (f + 456));
    R(4) = (R(31) + 4240);
    R(8) = ld32(base, (f + 460));
    R(5) = (R(26) + 320);
    R(7) = ld32(base, (f + 440));
    R(6) = ld32(base, (f + 444));
    R(0) = ld32(base, (f + 448));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 332), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B20694u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2472);
    R(4) = (R(27) + 2484);
    R(3) = (R(27) + 2496);
    R(11) = ld32(base, (R(27) + 2472));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3160);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2484));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2496));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 404), R(11));
    st32(base, (f + 408), R(10));
    st32(base, (f + 412), R(9));
    st32(base, (f + 416), R(8));
    st32(base, (f + 420), R(7));
    st32(base, (f + 424), R(6));
    st32(base, (f + 428), R(5));
    st32(base, (f + 432), R(4));
    st32(base, (f + 436), R(0));
    GM_CALLV(0x80B206F0u, 0x80B21190u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 396);
    GM_CALLV(0x80B20700u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 396);
    R(23) = ld32(base, (f + 428));
    R(12) = ld32(base, (f + 432));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 436));
    R(5) = (R(26) + 384);
    R(10) = ld32(base, (f + 416));
    R(9) = ld32(base, (f + 420));
    R(8) = ld32(base, (f + 424));
    R(7) = ld32(base, (f + 404));
    R(6) = ld32(base, (f + 408));
    R(0) = ld32(base, (f + 412));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 396), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B20760u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2508);
    R(4) = (R(27) + 2520);
    R(3) = (R(27) + 2532);
    R(11) = ld32(base, (R(27) + 2508));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3204);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2520));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2532));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 368), R(11));
    st32(base, (f + 372), R(10));
    st32(base, (f + 376), R(9));
    st32(base, (f + 380), R(8));
    st32(base, (f + 384), R(7));
    st32(base, (f + 388), R(6));
    st32(base, (f + 392), R(5));
    st32(base, (f + 396), R(4));
    st32(base, (f + 400), R(0));
    GM_CALLV(0x80B207BCu, 0x80B21180u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 460);
    GM_CALLV(0x80B207CCu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 460);
    R(23) = ld32(base, (f + 392));
    R(12) = ld32(base, (f + 396));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 400));
    R(5) = (R(26) + 448);
    R(10) = ld32(base, (f + 380));
    R(9) = ld32(base, (f + 384));
    R(8) = ld32(base, (f + 388));
    R(7) = ld32(base, (f + 368));
    R(6) = ld32(base, (f + 372));
    R(0) = ld32(base, (f + 376));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 460), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2082Cu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2544);
    R(4) = (R(27) + 2556);
    R(3) = (R(27) + 2568);
    R(11) = ld32(base, (R(27) + 2544));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3248);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2556));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2568));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 332), R(11));
    st32(base, (f + 336), R(10));
    st32(base, (f + 340), R(9));
    st32(base, (f + 344), R(8));
    st32(base, (f + 348), R(7));
    st32(base, (f + 352), R(6));
    st32(base, (f + 356), R(5));
    st32(base, (f + 360), R(4));
    st32(base, (f + 364), R(0));
    GM_CALLV(0x80B20888u, 0x80B21170u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 524);
    GM_CALLV(0x80B20898u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 524);
    R(23) = ld32(base, (f + 356));
    R(12) = ld32(base, (f + 360));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 364));
    R(5) = (R(26) + 512);
    R(10) = ld32(base, (f + 344));
    R(9) = ld32(base, (f + 348));
    R(8) = ld32(base, (f + 352));
    R(7) = ld32(base, (f + 332));
    R(6) = ld32(base, (f + 336));
    R(0) = ld32(base, (f + 340));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 524), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B208F8u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2580);
    R(4) = (R(27) + 2592);
    R(3) = (R(27) + 2604);
    R(11) = ld32(base, (R(27) + 2580));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3288);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2592));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2604));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 296), R(11));
    st32(base, (f + 300), R(10));
    st32(base, (f + 304), R(9));
    st32(base, (f + 308), R(8));
    st32(base, (f + 312), R(7));
    st32(base, (f + 316), R(6));
    st32(base, (f + 320), R(5));
    st32(base, (f + 324), R(4));
    st32(base, (f + 328), R(0));
    GM_CALLV(0x80B20954u, 0x80B21160u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 588);
    GM_CALLV(0x80B20964u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 588);
    R(23) = ld32(base, (f + 320));
    R(12) = ld32(base, (f + 324));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 328));
    R(5) = (R(26) + 576);
    R(10) = ld32(base, (f + 308));
    R(9) = ld32(base, (f + 312));
    R(8) = ld32(base, (f + 316));
    R(7) = ld32(base, (f + 296));
    R(6) = ld32(base, (f + 300));
    R(0) = ld32(base, (f + 304));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 588), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B209C4u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2616);
    R(4) = (R(27) + 2628);
    R(3) = (R(27) + 2640);
    R(11) = ld32(base, (R(27) + 2616));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3328);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2628));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2640));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 260), R(11));
    st32(base, (f + 264), R(10));
    st32(base, (f + 268), R(9));
    st32(base, (f + 272), R(8));
    st32(base, (f + 276), R(7));
    st32(base, (f + 280), R(6));
    st32(base, (f + 284), R(5));
    st32(base, (f + 288), R(4));
    st32(base, (f + 292), R(0));
    GM_CALLV(0x80B20A20u, 0x80B21150u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 652);
    GM_CALLV(0x80B20A30u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 652);
    R(23) = ld32(base, (f + 284));
    R(12) = ld32(base, (f + 288));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 292));
    R(5) = (R(26) + 640);
    R(10) = ld32(base, (f + 272));
    R(9) = ld32(base, (f + 276));
    R(8) = ld32(base, (f + 280));
    R(7) = ld32(base, (f + 260));
    R(6) = ld32(base, (f + 264));
    R(0) = ld32(base, (f + 268));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 652), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B20A90u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2652);
    R(4) = (R(27) + 2664);
    R(3) = (R(27) + 2676);
    R(11) = ld32(base, (R(27) + 2652));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3368);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2664));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2676));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 224), R(11));
    st32(base, (f + 228), R(10));
    st32(base, (f + 232), R(9));
    st32(base, (f + 236), R(8));
    st32(base, (f + 240), R(7));
    st32(base, (f + 244), R(6));
    st32(base, (f + 248), R(5));
    st32(base, (f + 252), R(4));
    st32(base, (f + 256), R(0));
    GM_CALLV(0x80B20AECu, 0x80B21140u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 716);
    GM_CALLV(0x80B20AFCu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 716);
    R(23) = ld32(base, (f + 248));
    R(12) = ld32(base, (f + 252));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 256));
    R(5) = (R(26) + 704);
    R(10) = ld32(base, (f + 236));
    R(9) = ld32(base, (f + 240));
    R(8) = ld32(base, (f + 244));
    R(7) = ld32(base, (f + 224));
    R(6) = ld32(base, (f + 228));
    R(0) = ld32(base, (f + 232));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 716), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B20B5Cu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2688);
    R(4) = (R(27) + 2700);
    R(3) = (R(27) + 2712);
    R(11) = ld32(base, (R(27) + 2688));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3408);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2700));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2712));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 188), R(11));
    st32(base, (f + 192), R(10));
    st32(base, (f + 196), R(9));
    st32(base, (f + 200), R(8));
    st32(base, (f + 204), R(7));
    st32(base, (f + 208), R(6));
    st32(base, (f + 212), R(5));
    st32(base, (f + 216), R(4));
    st32(base, (f + 220), R(0));
    GM_CALLV(0x80B20BB8u, 0x80B21130u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 780);
    GM_CALLV(0x80B20BC8u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 780);
    R(23) = ld32(base, (f + 212));
    R(12) = ld32(base, (f + 216));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 220));
    R(5) = (R(26) + 768);
    R(10) = ld32(base, (f + 200));
    R(9) = ld32(base, (f + 204));
    R(8) = ld32(base, (f + 208));
    R(7) = ld32(base, (f + 188));
    R(6) = ld32(base, (f + 192));
    R(0) = ld32(base, (f + 196));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 780), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B20C28u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2724);
    R(4) = (R(27) + 2736);
    R(3) = (R(27) + 2748);
    R(11) = ld32(base, (R(27) + 2724));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3448);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2736));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2748));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 152), R(11));
    st32(base, (f + 156), R(10));
    st32(base, (f + 160), R(9));
    st32(base, (f + 164), R(8));
    st32(base, (f + 168), R(7));
    st32(base, (f + 172), R(6));
    st32(base, (f + 176), R(5));
    st32(base, (f + 180), R(4));
    st32(base, (f + 184), R(0));
    GM_CALLV(0x80B20C84u, 0x80B21120u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 844);
    GM_CALLV(0x80B20C94u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 844);
    R(23) = ld32(base, (f + 176));
    R(12) = ld32(base, (f + 180));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 184));
    R(5) = (R(26) + 832);
    R(10) = ld32(base, (f + 164));
    R(9) = ld32(base, (f + 168));
    R(8) = ld32(base, (f + 172));
    R(7) = ld32(base, (f + 152));
    R(6) = ld32(base, (f + 156));
    R(0) = ld32(base, (f + 160));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 844), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B20CF4u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2760);
    R(4) = (R(27) + 2772);
    R(3) = (R(27) + 2784);
    R(11) = ld32(base, (R(27) + 2760));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3488);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2772));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2784));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 116), R(11));
    st32(base, (f + 120), R(10));
    st32(base, (f + 124), R(9));
    st32(base, (f + 128), R(8));
    st32(base, (f + 132), R(7));
    st32(base, (f + 136), R(6));
    st32(base, (f + 140), R(5));
    st32(base, (f + 144), R(4));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x80B20D50u, 0x80B21110u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 908);
    GM_CALLV(0x80B20D60u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 908);
    R(23) = ld32(base, (f + 140));
    R(12) = ld32(base, (f + 144));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 148));
    R(5) = (R(26) + 896);
    R(10) = ld32(base, (f + 128));
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 908), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B20DC0u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2796);
    R(4) = (R(27) + 2808);
    R(3) = (R(27) + 2820);
    R(11) = ld32(base, (R(27) + 2796));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3528);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2808));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2820));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 80), R(11));
    st32(base, (f + 84), R(10));
    st32(base, (f + 88), R(9));
    st32(base, (f + 92), R(8));
    st32(base, (f + 96), R(7));
    st32(base, (f + 100), R(6));
    st32(base, (f + 104), R(5));
    st32(base, (f + 108), R(4));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x80B20E1Cu, 0x80B21100u, 0);
    R(23) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 972);
    GM_CALLV(0x80B20E2Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 972);
    R(24) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(26) + 960);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 972), R(30));
    st32(base, (R(3) + 48), R(23));
    GM_CALLV(0x80B20E8Cu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2832);
    R(4) = (R(27) + 2844);
    R(3) = (R(27) + 2856);
    R(11) = ld32(base, (R(27) + 2832));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3568);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2844));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2856));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 44), R(11));
    st32(base, (f + 48), R(10));
    st32(base, (f + 52), R(9));
    st32(base, (f + 56), R(8));
    st32(base, (f + 60), R(7));
    st32(base, (f + 64), R(6));
    st32(base, (f + 68), R(5));
    st32(base, (f + 72), R(4));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x80B20EE8u, 0x80B210F0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 1036);
    GM_CALLV(0x80B20EF8u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 1036);
    R(25) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(31) + 4240);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(26) + 1024);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 1036), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B20F58u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2868);
    R(6) = (R(27) + 2880);
    R(5) = (R(27) + 2892);
    R(25) = ld32(base, (R(27) + 2868));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 3608);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 1104);
    R(10) = ld32(base, (R(27) + 2880));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2892));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 8), R(25));
    st32(base, (f + 12), R(12));
    st32(base, (f + 16), R(11));
    st32(base, (f + 20), R(10));
    st32(base, (f + 24), R(9));
    st32(base, (f + 28), R(8));
    st32(base, (f + 32), R(7));
    st32(base, (f + 36), R(6));
    st32(base, (f + 40), R(0));
    GM_CALLV(0x80B20FB8u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 1104);
    R(25) = ld32(base, (f + 32));
    R(12) = ld32(base, (f + 36));
    R(4) = (R(29) + 4144);
    R(11) = ld32(base, (f + 40));
    R(5) = (R(26) + 1088);
    R(10) = ld32(base, (f + 20));
    R(9) = ld32(base, (f + 24));
    R(8) = ld32(base, (f + 28));
    R(7) = ld32(base, (f + 8));
    R(6) = ld32(base, (f + 12));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(26) + 1104), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B21014u, 0x80B1CAC0u, 0);
    R(11) = (f + 704);
    R(0) = lr;
}

/* fn_4_46A0 (fn_4_46A0, 12 bytes) */
static void eb_m_210f0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_46B0 (fn_4_46B0, 12 bytes) */
static void eb_m_21100(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31036);
}

/* fn_4_46C0 (fn_4_46C0, 12 bytes) */
static void eb_m_21110(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_46D0 (fn_4_46D0, 12 bytes) */
static void eb_m_21120(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31804);
}

/* fn_4_46E0 (fn_4_46E0, 12 bytes) */
static void eb_m_21130(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31612);
}

/* fn_4_46F0 (fn_4_46F0, 12 bytes) */
static void eb_m_21140(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31676);
}

/* fn_4_4700 (fn_4_4700, 12 bytes) */
static void eb_m_21150(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31740);
}

/* fn_4_4710 (fn_4_4710, 12 bytes) */
static void eb_m_21160(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31868);
}

/* fn_4_4720 (fn_4_4720, 12 bytes) */
static void eb_m_21170(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31932);
}

/* fn_4_4730 (fn_4_4730, 12 bytes) */
static void eb_m_21180(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31996);
}

/* fn_4_4740 (fn_4_4740, 12 bytes) */
static void eb_m_21190(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32060);
}

/* fn_4_4750 (fn_4_4750, 12 bytes) */
static void eb_m_211a0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32124);
}

/* fn_4_4B20 (fn_4_4B20, 88 bytes) */
static void eb_m_21570(GM_CTX) {
    GM_FN(0x80B21570); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80B215AC; }
    R(4) = (0 + 0);
    GM_CALLV(0x80B2159Cu, 0x800A8B10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80B215AC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80B215ACu, 0x80162920u, 0);
L_80B215AC:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_4_4B80 (fn_4_4B80, 4 bytes) */
static void eb_m_215d0(GM_CTX) {

}

/* fn_4_5DD0 (fn_4_5DD0, 24 bytes) */
static void eb_m_22820(GM_CTX) {
    { uint32_t ea_ = R(3) + 1348; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(4) = (0 + 1313);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_4_5E40 (fn_4_5E40, 12 bytes) */
static void eb_m_22890(GM_CTX) {
    R(3) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(3) + 15480); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_4_5E90 (fn_4_5E90, 8 bytes) */
static void eb_m_228e0(GM_CTX) {
    R(3) = (0 + 0);
}

/* fn_4_5EA0 (fn_4_5EA0, 12 bytes) */
static void eb_m_228f0(GM_CTX) {
    R(3) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(3) + 15500); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_4_5EB0 (fn_4_5EB0, 12 bytes) */
static void eb_m_22900(GM_CTX) {
    R(3) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(3) + 15504); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_4_5F80 (fn_4_5F80, 1772 bytes) */
static void eb_m_229d0(GM_CTX) {
    GM_FN(0x80B229D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 352);
    R(28) = (0 + 0x80B70000u);
    R(27) = (0 + 0x80B90000u);
    R(28) = (R(28) + 27544);
    R(29) = (0 + 0x80B70000u);
    R(5) = (R(28) + 2000);
    R(11) = ld32(base, (R(28) + 2000));
    R(4) = (R(28) + 2012);
    R(3) = (R(28) + 2024);
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(27) + -24744);
    R(9) = ld32(base, (R(5) + 8));
    R(29) = (R(29) + 15416);
    R(8) = ld32(base, (R(28) + 2012));
    R(24) = (R(28) + 2288);
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2024));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 272), R(11));
    st32(base, (f + 276), R(10));
    st32(base, (f + 280), R(9));
    st32(base, (f + 284), R(8));
    st32(base, (f + 288), R(7));
    st32(base, (f + 292), R(6));
    st32(base, (f + 296), R(5));
    st32(base, (f + 300), R(4));
    st32(base, (f + 304), R(0));
    GM_CALLV(0x80B22A58u, 0x80B231F0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(24) |R(24);
    R(3) = (R(27) + 12);
    GM_CALLV(0x80B22A68u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 12);
    R(24) = ld32(base, (f + 296));
    R(12) = ld32(base, (f + 300));
    R(30) = (0 + 0x80B70000u);
    R(11) = ld32(base, (f + 304));
    R(30) = (R(30) + 30164);
    R(10) = ld32(base, (f + 284));
    R(31) = (0 + 0x80B20000u);
    R(9) = ld32(base, (f + 288));
    R(4) = (R(31) + 12576);
    R(8) = ld32(base, (f + 292));
    R(5) = (R(27) + 0);
    R(7) = ld32(base, (f + 272));
    R(6) = ld32(base, (f + 276));
    R(0) = ld32(base, (f + 280));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 12), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B22AD4u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2036);
    R(4) = (R(28) + 2048);
    R(3) = (R(28) + 2060);
    R(11) = ld32(base, (R(28) + 2036));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2328);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2048));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2060));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 236), R(11));
    st32(base, (f + 240), R(10));
    st32(base, (f + 244), R(9));
    st32(base, (f + 248), R(8));
    st32(base, (f + 252), R(7));
    st32(base, (f + 256), R(6));
    st32(base, (f + 260), R(5));
    st32(base, (f + 264), R(4));
    st32(base, (f + 268), R(0));
    GM_CALLV(0x80B22B30u, 0x80B231E0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 76);
    GM_CALLV(0x80B22B40u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 76);
    R(24) = ld32(base, (f + 260));
    R(12) = ld32(base, (f + 264));
    R(4) = (R(31) + 12576);
    R(11) = ld32(base, (f + 268));
    R(5) = (R(27) + 64);
    R(10) = ld32(base, (f + 248));
    R(9) = ld32(base, (f + 252));
    R(8) = ld32(base, (f + 256));
    R(7) = ld32(base, (f + 236));
    R(6) = ld32(base, (f + 240));
    R(0) = ld32(base, (f + 244));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 76), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B22BA0u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2072);
    R(4) = (R(28) + 2084);
    R(3) = (R(28) + 2096);
    R(11) = ld32(base, (R(28) + 2072));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2372);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2084));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2096));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 200), R(11));
    st32(base, (f + 204), R(10));
    st32(base, (f + 208), R(9));
    st32(base, (f + 212), R(8));
    st32(base, (f + 216), R(7));
    st32(base, (f + 220), R(6));
    st32(base, (f + 224), R(5));
    st32(base, (f + 228), R(4));
    st32(base, (f + 232), R(0));
    GM_CALLV(0x80B22BFCu, 0x80B231D0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 140);
    GM_CALLV(0x80B22C0Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 140);
    R(24) = ld32(base, (f + 224));
    R(12) = ld32(base, (f + 228));
    R(4) = (R(31) + 12576);
    R(11) = ld32(base, (f + 232));
    R(5) = (R(27) + 128);
    R(10) = ld32(base, (f + 212));
    R(9) = ld32(base, (f + 216));
    R(8) = ld32(base, (f + 220));
    R(7) = ld32(base, (f + 200));
    R(6) = ld32(base, (f + 204));
    R(0) = ld32(base, (f + 208));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 140), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B22C6Cu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2108);
    R(4) = (R(28) + 2120);
    R(3) = (R(28) + 2132);
    R(11) = ld32(base, (R(28) + 2108));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2420);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2120));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2132));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 164), R(11));
    st32(base, (f + 168), R(10));
    st32(base, (f + 172), R(9));
    st32(base, (f + 176), R(8));
    st32(base, (f + 180), R(7));
    st32(base, (f + 184), R(6));
    st32(base, (f + 188), R(5));
    st32(base, (f + 192), R(4));
    st32(base, (f + 196), R(0));
    GM_CALLV(0x80B22CC8u, 0x80B231C0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 204);
    GM_CALLV(0x80B22CD8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 204);
    R(24) = ld32(base, (f + 188));
    R(12) = ld32(base, (f + 192));
    R(4) = (R(31) + 12576);
    R(11) = ld32(base, (f + 196));
    R(5) = (R(27) + 192);
    R(10) = ld32(base, (f + 176));
    R(9) = ld32(base, (f + 180));
    R(8) = ld32(base, (f + 184));
    R(7) = ld32(base, (f + 164));
    R(6) = ld32(base, (f + 168));
    R(0) = ld32(base, (f + 172));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 204), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B22D38u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2144);
    R(4) = (R(28) + 2156);
    R(3) = (R(28) + 2168);
    R(11) = ld32(base, (R(28) + 2144));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2456);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2156));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2168));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 128), R(11));
    st32(base, (f + 132), R(10));
    st32(base, (f + 136), R(9));
    st32(base, (f + 140), R(8));
    st32(base, (f + 144), R(7));
    st32(base, (f + 148), R(6));
    st32(base, (f + 152), R(5));
    st32(base, (f + 156), R(4));
    st32(base, (f + 160), R(0));
    GM_CALLV(0x80B22D94u, 0x80B231B0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 268);
    GM_CALLV(0x80B22DA4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 268);
    R(24) = ld32(base, (f + 152));
    R(12) = ld32(base, (f + 156));
    R(4) = (R(31) + 12576);
    R(11) = ld32(base, (f + 160));
    R(5) = (R(27) + 256);
    R(10) = ld32(base, (f + 140));
    R(9) = ld32(base, (f + 144));
    R(8) = ld32(base, (f + 148));
    R(7) = ld32(base, (f + 128));
    R(6) = ld32(base, (f + 132));
    R(0) = ld32(base, (f + 136));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 268), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B22E04u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2180);
    R(4) = (R(28) + 2192);
    R(3) = (R(28) + 2204);
    R(11) = ld32(base, (R(28) + 2180));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2496);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2192));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2204));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 92), R(11));
    st32(base, (f + 96), R(10));
    st32(base, (f + 100), R(9));
    st32(base, (f + 104), R(8));
    st32(base, (f + 108), R(7));
    st32(base, (f + 112), R(6));
    st32(base, (f + 116), R(5));
    st32(base, (f + 120), R(4));
    st32(base, (f + 124), R(0));
    GM_CALLV(0x80B22E60u, 0x80B231A0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 332);
    GM_CALLV(0x80B22E70u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 332);
    R(24) = ld32(base, (f + 116));
    R(12) = ld32(base, (f + 120));
    R(4) = (R(31) + 12576);
    R(11) = ld32(base, (f + 124));
    R(5) = (R(27) + 320);
    R(10) = ld32(base, (f + 104));
    R(9) = ld32(base, (f + 108));
    R(8) = ld32(base, (f + 112));
    R(7) = ld32(base, (f + 92));
    R(6) = ld32(base, (f + 96));
    R(0) = ld32(base, (f + 100));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 332), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B22ED0u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2216);
    R(4) = (R(28) + 2228);
    R(3) = (R(28) + 2240);
    R(11) = ld32(base, (R(28) + 2216));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2536);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2228));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2240));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 56), R(11));
    st32(base, (f + 60), R(10));
    st32(base, (f + 64), R(9));
    st32(base, (f + 68), R(8));
    st32(base, (f + 72), R(7));
    st32(base, (f + 76), R(6));
    st32(base, (f + 80), R(5));
    st32(base, (f + 84), R(4));
    st32(base, (f + 88), R(0));
    GM_CALLV(0x80B22F2Cu, 0x80B23190u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 396);
    GM_CALLV(0x80B22F3Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 396);
    R(25) = ld32(base, (f + 80));
    R(12) = ld32(base, (f + 84));
    R(4) = (R(31) + 12576);
    R(11) = ld32(base, (f + 88));
    R(5) = (R(27) + 384);
    R(10) = ld32(base, (f + 68));
    R(9) = ld32(base, (f + 72));
    R(8) = ld32(base, (f + 76));
    R(7) = ld32(base, (f + 56));
    R(6) = ld32(base, (f + 60));
    R(0) = ld32(base, (f + 64));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 396), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B22F9Cu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2252);
    R(4) = (R(28) + 2264);
    R(3) = (R(28) + 2276);
    R(11) = ld32(base, (R(28) + 2252));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2580);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2264));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2276));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 20), R(11));
    st32(base, (f + 24), R(10));
    st32(base, (f + 28), R(9));
    st32(base, (f + 32), R(8));
    st32(base, (f + 36), R(7));
    st32(base, (f + 40), R(6));
    st32(base, (f + 44), R(5));
    st32(base, (f + 48), R(4));
    st32(base, (f + 52), R(0));
    GM_CALLV(0x80B22FF8u, 0x80B23180u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 460);
    GM_CALLV(0x80B23008u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 460);
    R(26) = ld32(base, (f + 44));
    R(12) = ld32(base, (f + 48));
    R(4) = (R(31) + 12576);
    R(11) = ld32(base, (f + 52));
    R(5) = (R(27) + 448);
    R(10) = ld32(base, (f + 32));
    R(9) = ld32(base, (f + 36));
    R(8) = ld32(base, (f + 40));
    R(7) = ld32(base, (f + 20));
    R(6) = ld32(base, (f + 24));
    R(0) = ld32(base, (f + 28));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 460), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B23068u, 0x80B1CAC0u, 0);
    R(0) = ld8(base, (R(27) + 512));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B230A4; }
    { uint32_t ea_ = (R(29) + 92); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(28) + 12);
    { uint32_t ea_ = (R(29) + 96); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(29) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(27) + 512), R(0));
L_80B230A4:;
    R(11) = (f + 352);
    R(0) = lr;
}

/* fn_4_6730 (fn_4_6730, 12 bytes) */
static void eb_m_23180(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -13892);
}

/* fn_4_6740 (fn_4_6740, 12 bytes) */
static void eb_m_23190(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -13444);
}

/* fn_4_6750 (fn_4_6750, 12 bytes) */
static void eb_m_231a0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -13508);
}

/* fn_4_6760 (fn_4_6760, 12 bytes) */
static void eb_m_231b0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32252);
}

/* fn_4_6770 (fn_4_6770, 12 bytes) */
static void eb_m_231c0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32380);
}

/* fn_4_6780 (fn_4_6780, 12 bytes) */
static void eb_m_231d0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30908);
}

/* fn_4_6790 (fn_4_6790, 12 bytes) */
static void eb_m_231e0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_67A0 (fn_4_67A0, 12 bytes) */
static void eb_m_231f0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31036);
}

/* fn_4_90E0 (fn_4_90E0, 84 bytes) */
static void eb_m_25b30(GM_CTX) {
    GM_FN(0x80B25B30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 1200));
    ctx->ctr = R(12);
    GM_CALLV(0x80B25B54u, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80360000u);
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 212));
    R(4) = (R(4) + -32060);
    ctx->ctr = R(12);
    GM_CALLV(0x80B25B70u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_4_9330 (fn_4_9330, 2196 bytes) */
static void eb_m_25d80(GM_CTX) {
    GM_FN(0x80B25D80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 448);
    R(26) = (0 + 0x80B90000u);
    R(27) = (0 + 0x80B70000u);
    R(26) = (R(26) + -24224);
    R(4) = (0 + 0x80B70000u);
    R(0) = ld8(base, (R(26) + 640));
    R(27) = (R(27) + 30272);
    R(4) = (R(4) + 15592);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B25E1C; }
    { uint32_t ea_ = (R(4) + 8); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(3) = (R(27) + 16);
    { uint32_t ea_ = (R(4) + 120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(4) + 64); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 116); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 92); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 124); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 64); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 68); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 72); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 76); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 80); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 84); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 88); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[2].d); }
    st8(base, (R(26) + 640), R(0));
L_80B25E1C:;
    R(3) = (R(27) + 2008);
    R(6) = (R(27) + 2020);
    R(5) = (R(27) + 2032);
    R(23) = ld32(base, (R(27) + 2008));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2368);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 16);
    R(10) = ld32(base, (R(27) + 2020));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2032));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 364), R(23));
    st32(base, (f + 368), R(12));
    st32(base, (f + 372), R(11));
    st32(base, (f + 376), R(10));
    st32(base, (f + 380), R(9));
    st32(base, (f + 384), R(8));
    st32(base, (f + 388), R(7));
    st32(base, (f + 392), R(6));
    st32(base, (f + 396), R(0));
    GM_CALLV(0x80B25E7Cu, 0x8015F7C0u, 0);
    R(28) = (0 + 0x80B80000u);
    R(3) = (R(26) + 16);
    R(23) = ld32(base, (f + 388));
    R(28) = (R(28) + -32428);
    R(12) = ld32(base, (f + 392));
    R(29) = (0 + 0x80B20000u);
    R(11) = ld32(base, (f + 396));
    R(4) = (R(29) + 26144);
    R(10) = ld32(base, (f + 376));
    R(5) = (R(26) + 0);
    R(9) = ld32(base, (f + 380));
    R(8) = ld32(base, (f + 384));
    R(7) = ld32(base, (f + 364));
    R(6) = ld32(base, (f + 368));
    R(0) = ld32(base, (f + 372));
    st32(base, (R(26) + 16), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B25EE4u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2044);
    R(6) = (R(27) + 2056);
    R(5) = (R(27) + 2068);
    R(23) = ld32(base, (R(27) + 2044));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2408);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 80);
    R(10) = ld32(base, (R(27) + 2056));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2068));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 328), R(23));
    st32(base, (f + 332), R(12));
    st32(base, (f + 336), R(11));
    st32(base, (f + 340), R(10));
    st32(base, (f + 344), R(9));
    st32(base, (f + 348), R(8));
    st32(base, (f + 352), R(7));
    st32(base, (f + 356), R(6));
    st32(base, (f + 360), R(0));
    GM_CALLV(0x80B25F44u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 80);
    R(23) = ld32(base, (f + 352));
    R(12) = ld32(base, (f + 356));
    R(4) = (R(29) + 26144);
    R(11) = ld32(base, (f + 360));
    R(5) = (R(26) + 64);
    R(10) = ld32(base, (f + 340));
    R(9) = ld32(base, (f + 344));
    R(8) = ld32(base, (f + 348));
    R(7) = ld32(base, (f + 328));
    R(6) = ld32(base, (f + 332));
    R(0) = ld32(base, (f + 336));
    st32(base, (R(26) + 80), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B25FA0u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2080);
    R(4) = (R(27) + 2092);
    R(3) = (R(27) + 2104);
    R(11) = ld32(base, (R(27) + 2080));
    R(10) = ld32(base, (R(5) + 4));
    R(30) = (R(27) + 2456);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2092));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2104));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 292), R(11));
    st32(base, (f + 296), R(10));
    st32(base, (f + 300), R(9));
    st32(base, (f + 304), R(8));
    st32(base, (f + 308), R(7));
    st32(base, (f + 312), R(6));
    st32(base, (f + 316), R(5));
    st32(base, (f + 320), R(4));
    st32(base, (f + 324), R(0));
    GM_CALLV(0x80B25FFCu, 0x80B26740u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(30) |R(30);
    R(3) = (R(26) + 140);
    GM_CALLV(0x80B2600Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 140);
    R(23) = ld32(base, (f + 316));
    R(12) = ld32(base, (f + 320));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 324));
    R(30) = (R(30) + -32480);
    R(10) = ld32(base, (f + 304));
    R(31) = (0 + 0x80B20000u);
    R(9) = ld32(base, (f + 308));
    R(4) = (R(31) + 26240);
    R(8) = ld32(base, (f + 312));
    R(5) = (R(26) + 128);
    R(7) = ld32(base, (f + 292));
    R(6) = ld32(base, (f + 296));
    R(0) = ld32(base, (f + 300));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 140), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B26078u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2116);
    R(4) = (R(27) + 2128);
    R(3) = (R(27) + 2140);
    R(11) = ld32(base, (R(27) + 2116));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2496);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2128));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2140));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 256), R(11));
    st32(base, (f + 260), R(10));
    st32(base, (f + 264), R(9));
    st32(base, (f + 268), R(8));
    st32(base, (f + 272), R(7));
    st32(base, (f + 276), R(6));
    st32(base, (f + 280), R(5));
    st32(base, (f + 284), R(4));
    st32(base, (f + 288), R(0));
    GM_CALLV(0x80B260D4u, 0x80B26730u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 204);
    GM_CALLV(0x80B260E4u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 204);
    R(23) = ld32(base, (f + 280));
    R(12) = ld32(base, (f + 284));
    R(4) = (R(31) + 26240);
    R(11) = ld32(base, (f + 288));
    R(5) = (R(26) + 192);
    R(10) = ld32(base, (f + 268));
    R(9) = ld32(base, (f + 272));
    R(8) = ld32(base, (f + 276));
    R(7) = ld32(base, (f + 256));
    R(6) = ld32(base, (f + 260));
    R(0) = ld32(base, (f + 264));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 204), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B26144u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2152);
    R(4) = (R(27) + 2164);
    R(3) = (R(27) + 2176);
    R(11) = ld32(base, (R(27) + 2152));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2536);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2164));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2176));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 220), R(11));
    st32(base, (f + 224), R(10));
    st32(base, (f + 228), R(9));
    st32(base, (f + 232), R(8));
    st32(base, (f + 236), R(7));
    st32(base, (f + 240), R(6));
    st32(base, (f + 244), R(5));
    st32(base, (f + 248), R(4));
    st32(base, (f + 252), R(0));
    GM_CALLV(0x80B261A0u, 0x80B26720u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 268);
    GM_CALLV(0x80B261B0u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 268);
    R(23) = ld32(base, (f + 244));
    R(12) = ld32(base, (f + 248));
    R(4) = (R(31) + 26240);
    R(11) = ld32(base, (f + 252));
    R(5) = (R(26) + 256);
    R(10) = ld32(base, (f + 232));
    R(9) = ld32(base, (f + 236));
    R(8) = ld32(base, (f + 240));
    R(7) = ld32(base, (f + 220));
    R(6) = ld32(base, (f + 224));
    R(0) = ld32(base, (f + 228));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 268), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B26210u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2188);
    R(4) = (R(27) + 2200);
    R(3) = (R(27) + 2212);
    R(11) = ld32(base, (R(27) + 2188));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2576);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2200));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2212));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 184), R(11));
    st32(base, (f + 188), R(10));
    st32(base, (f + 192), R(9));
    st32(base, (f + 196), R(8));
    st32(base, (f + 200), R(7));
    st32(base, (f + 204), R(6));
    st32(base, (f + 208), R(5));
    st32(base, (f + 212), R(4));
    st32(base, (f + 216), R(0));
    GM_CALLV(0x80B2626Cu, 0x80B26710u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 332);
    GM_CALLV(0x80B2627Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 332);
    R(23) = ld32(base, (f + 208));
    R(12) = ld32(base, (f + 212));
    R(4) = (R(31) + 26240);
    R(11) = ld32(base, (f + 216));
    R(5) = (R(26) + 320);
    R(10) = ld32(base, (f + 196));
    R(9) = ld32(base, (f + 200));
    R(8) = ld32(base, (f + 204));
    R(7) = ld32(base, (f + 184));
    R(6) = ld32(base, (f + 188));
    R(0) = ld32(base, (f + 192));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 332), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B262DCu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2224);
    R(4) = (R(27) + 2236);
    R(3) = (R(27) + 2248);
    R(11) = ld32(base, (R(27) + 2224));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2616);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2236));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2248));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 148), R(11));
    st32(base, (f + 152), R(10));
    st32(base, (f + 156), R(9));
    st32(base, (f + 160), R(8));
    st32(base, (f + 164), R(7));
    st32(base, (f + 168), R(6));
    st32(base, (f + 172), R(5));
    st32(base, (f + 176), R(4));
    st32(base, (f + 180), R(0));
    GM_CALLV(0x80B26338u, 0x80B26700u, 0);
    R(23) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 396);
    GM_CALLV(0x80B26348u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 396);
    R(24) = ld32(base, (f + 172));
    R(12) = ld32(base, (f + 176));
    R(4) = (R(31) + 26240);
    R(11) = ld32(base, (f + 180));
    R(5) = (R(26) + 384);
    R(10) = ld32(base, (f + 160));
    R(9) = ld32(base, (f + 164));
    R(8) = ld32(base, (f + 168));
    R(7) = ld32(base, (f + 148));
    R(6) = ld32(base, (f + 152));
    R(0) = ld32(base, (f + 156));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 396), R(30));
    st32(base, (R(3) + 48), R(23));
    GM_CALLV(0x80B263A8u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2260);
    R(4) = (R(27) + 2272);
    R(3) = (R(27) + 2284);
    R(11) = ld32(base, (R(27) + 2260));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2656);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2272));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2284));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 112), R(11));
    st32(base, (f + 116), R(10));
    st32(base, (f + 120), R(9));
    st32(base, (f + 124), R(8));
    st32(base, (f + 128), R(7));
    st32(base, (f + 132), R(6));
    st32(base, (f + 136), R(5));
    st32(base, (f + 140), R(4));
    st32(base, (f + 144), R(0));
    GM_CALLV(0x80B26404u, 0x80B266F0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 460);
    GM_CALLV(0x80B26414u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 460);
    R(25) = ld32(base, (f + 136));
    R(12) = ld32(base, (f + 140));
    R(4) = (R(31) + 26240);
    R(11) = ld32(base, (f + 144));
    R(5) = (R(26) + 448);
    R(10) = ld32(base, (f + 124));
    R(9) = ld32(base, (f + 128));
    R(8) = ld32(base, (f + 132));
    R(7) = ld32(base, (f + 112));
    R(6) = ld32(base, (f + 116));
    R(0) = ld32(base, (f + 120));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 460), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B26474u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2296);
    R(6) = (R(27) + 2308);
    R(5) = (R(27) + 2320);
    R(25) = ld32(base, (R(27) + 2296));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2700);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 528);
    R(10) = ld32(base, (R(27) + 2308));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2320));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 76), R(25));
    st32(base, (f + 80), R(12));
    st32(base, (f + 84), R(11));
    st32(base, (f + 88), R(10));
    st32(base, (f + 92), R(9));
    st32(base, (f + 96), R(8));
    st32(base, (f + 100), R(7));
    st32(base, (f + 104), R(6));
    st32(base, (f + 108), R(0));
    GM_CALLV(0x80B264D4u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 528);
    R(25) = ld32(base, (f + 100));
    R(12) = ld32(base, (f + 104));
    R(4) = (R(29) + 26144);
    R(11) = ld32(base, (f + 108));
    R(5) = (R(26) + 512);
    R(10) = ld32(base, (f + 88));
    R(9) = ld32(base, (f + 92));
    R(8) = ld32(base, (f + 96));
    R(7) = ld32(base, (f + 76));
    R(6) = ld32(base, (f + 80));
    R(0) = ld32(base, (f + 84));
    st32(base, (R(26) + 528), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B26530u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2332);
    R(4) = (R(27) + 2344);
    R(3) = (R(27) + 2356);
    R(11) = ld32(base, (R(27) + 2332));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2744);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2344));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2356));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 40), R(11));
    st32(base, (f + 44), R(10));
    st32(base, (f + 48), R(9));
    st32(base, (f + 52), R(8));
    st32(base, (f + 56), R(7));
    st32(base, (f + 60), R(6));
    st32(base, (f + 64), R(5));
    st32(base, (f + 68), R(4));
    st32(base, (f + 72), R(0));
    GM_CALLV(0x80B2658Cu, 0x80B266E0u, 0);
    R(27) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 588);
    GM_CALLV(0x80B2659Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 588);
    R(25) = ld32(base, (f + 64));
    R(12) = ld32(base, (f + 68));
    R(4) = (R(31) + 26240);
    R(11) = ld32(base, (f + 72));
    R(5) = (R(26) + 576);
    R(10) = ld32(base, (f + 52));
    R(9) = ld32(base, (f + 56));
    R(8) = ld32(base, (f + 60));
    R(7) = ld32(base, (f + 40));
    R(6) = ld32(base, (f + 44));
    R(0) = ld32(base, (f + 48));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 588), R(30));
    st32(base, (R(3) + 48), R(27));
    GM_CALLV(0x80B265FCu, 0x80B1CAC0u, 0);
    R(11) = (f + 448);
    R(0) = lr;
}

/* fn_4_9C90 (fn_4_9C90, 12 bytes) */
static void eb_m_266e0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -12668);
}

/* fn_4_9CA0 (fn_4_9CA0, 12 bytes) */
static void eb_m_266f0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -12540);
}

/* fn_4_9CB0 (fn_4_9CB0, 12 bytes) */
static void eb_m_26700(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -12604);
}

/* fn_4_9CC0 (fn_4_9CC0, 12 bytes) */
static void eb_m_26710(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -12732);
}

/* fn_4_9CD0 (fn_4_9CD0, 12 bytes) */
static void eb_m_26720(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -13244);
}

/* fn_4_9CE0 (fn_4_9CE0, 12 bytes) */
static void eb_m_26730(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -13308);
}

/* fn_4_9CF0 (fn_4_9CF0, 12 bytes) */
static void eb_m_26740(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -13372);
}

/* fn_4_D290 (fn_4_D290, 2976 bytes) */
static void eb_m_29ce0(GM_CTX) {
    GM_FN(0x80B29CE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 592);
    R(26) = (0 + 0x80B90000u);
    R(27) = (0 + 0x80B80000u);
    R(26) = (R(26) + -23576);
    R(4) = (0 + 0x80B70000u);
    R(0) = ld8(base, (R(26) + 896));
    R(27) = (R(27) + -32376);
    R(4) = (R(4) + 15808);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B29D78; }
    { uint32_t ea_ = (R(4) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(27) + 16);
    { uint32_t ea_ = (R(4) + 20); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(4) + 164); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 168); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 144); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 160); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 164); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 184); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 188); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(26) + 896), R(0));
L_80B29D78:;
    R(5) = (R(27) + 2228);
    R(4) = (R(27) + 2240);
    R(3) = (R(27) + 2252);
    R(11) = ld32(base, (R(27) + 2228));
    R(10) = ld32(base, (R(5) + 4));
    R(23) = (R(27) + 2736);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2240));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2252));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 508), R(11));
    st32(base, (f + 512), R(10));
    st32(base, (f + 516), R(9));
    st32(base, (f + 520), R(8));
    st32(base, (f + 524), R(7));
    st32(base, (f + 528), R(6));
    st32(base, (f + 532), R(5));
    st32(base, (f + 536), R(4));
    st32(base, (f + 540), R(0));
    GM_CALLV(0x80B29DD4u, 0x80B2A9C0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(23) |R(23);
    R(3) = (R(26) + 12);
    GM_CALLV(0x80B29DE4u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 12);
    R(23) = ld32(base, (f + 532));
    R(12) = ld32(base, (f + 536));
    R(29) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 540));
    R(29) = (R(29) + -29024);
    R(10) = ld32(base, (f + 520));
    R(28) = (0 + 0x80B80000u);
    R(9) = ld32(base, (f + 524));
    R(30) = (0 + 0x80B30000u);
    R(8) = ld32(base, (f + 528));
    R(28) = (R(28) + -28972);
    R(7) = ld32(base, (f + 508));
    R(4) = (R(30) + -22304);
    R(6) = ld32(base, (f + 512));
    R(5) = (R(26) + 0);
    R(0) = ld32(base, (f + 516));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 12), R(29));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B29E58u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2264);
    R(6) = (R(27) + 2276);
    R(5) = (R(27) + 2288);
    R(23) = ld32(base, (R(27) + 2264));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2776);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 80);
    R(10) = ld32(base, (R(27) + 2276));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2288));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 472), R(23));
    st32(base, (f + 476), R(12));
    st32(base, (f + 480), R(11));
    st32(base, (f + 484), R(10));
    st32(base, (f + 488), R(9));
    st32(base, (f + 492), R(8));
    st32(base, (f + 496), R(7));
    st32(base, (f + 500), R(6));
    st32(base, (f + 504), R(0));
    GM_CALLV(0x80B29EB8u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 80);
    R(23) = ld32(base, (f + 496));
    R(12) = ld32(base, (f + 500));
    R(31) = (0 + 0x80B30000u);
    R(11) = ld32(base, (f + 504));
    R(4) = (R(31) + -22400);
    R(10) = ld32(base, (f + 484));
    R(5) = (R(26) + 64);
    R(9) = ld32(base, (f + 488));
    R(8) = ld32(base, (f + 492));
    R(7) = ld32(base, (f + 472));
    R(6) = ld32(base, (f + 476));
    R(0) = ld32(base, (f + 480));
    st32(base, (R(26) + 80), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B29F18u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2300);
    R(4) = (R(27) + 2312);
    R(3) = (R(27) + 2324);
    R(11) = ld32(base, (R(27) + 2300));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2820);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2312));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2324));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 436), R(11));
    st32(base, (f + 440), R(10));
    st32(base, (f + 444), R(9));
    st32(base, (f + 448), R(8));
    st32(base, (f + 452), R(7));
    st32(base, (f + 456), R(6));
    st32(base, (f + 460), R(5));
    st32(base, (f + 464), R(4));
    st32(base, (f + 468), R(0));
    GM_CALLV(0x80B29F74u, 0x80B2A9B0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 140);
    GM_CALLV(0x80B29F84u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 140);
    R(23) = ld32(base, (f + 460));
    R(12) = ld32(base, (f + 464));
    R(4) = (R(30) + -22304);
    R(11) = ld32(base, (f + 468));
    R(5) = (R(26) + 128);
    R(10) = ld32(base, (f + 448));
    R(9) = ld32(base, (f + 452));
    R(8) = ld32(base, (f + 456));
    R(7) = ld32(base, (f + 436));
    R(6) = ld32(base, (f + 440));
    R(0) = ld32(base, (f + 444));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 140), R(29));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B29FE4u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2336);
    R(6) = (R(27) + 2348);
    R(5) = (R(27) + 2360);
    R(23) = ld32(base, (R(27) + 2336));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2864);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 208);
    R(10) = ld32(base, (R(27) + 2348));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2360));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 400), R(23));
    st32(base, (f + 404), R(12));
    st32(base, (f + 408), R(11));
    st32(base, (f + 412), R(10));
    st32(base, (f + 416), R(9));
    st32(base, (f + 420), R(8));
    st32(base, (f + 424), R(7));
    st32(base, (f + 428), R(6));
    st32(base, (f + 432), R(0));
    GM_CALLV(0x80B2A044u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 208);
    R(23) = ld32(base, (f + 424));
    R(12) = ld32(base, (f + 428));
    R(4) = (R(31) + -22400);
    R(11) = ld32(base, (f + 432));
    R(5) = (R(26) + 192);
    R(10) = ld32(base, (f + 412));
    R(9) = ld32(base, (f + 416));
    R(8) = ld32(base, (f + 420));
    R(7) = ld32(base, (f + 400));
    R(6) = ld32(base, (f + 404));
    R(0) = ld32(base, (f + 408));
    st32(base, (R(26) + 208), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B2A0A0u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2372);
    R(6) = (R(27) + 2384);
    R(5) = (R(27) + 2396);
    R(23) = ld32(base, (R(27) + 2372));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2912);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 272);
    R(10) = ld32(base, (R(27) + 2384));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2396));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 364), R(23));
    st32(base, (f + 368), R(12));
    st32(base, (f + 372), R(11));
    st32(base, (f + 376), R(10));
    st32(base, (f + 380), R(9));
    st32(base, (f + 384), R(8));
    st32(base, (f + 388), R(7));
    st32(base, (f + 392), R(6));
    st32(base, (f + 396), R(0));
    GM_CALLV(0x80B2A100u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 272);
    R(23) = ld32(base, (f + 388));
    R(12) = ld32(base, (f + 392));
    R(4) = (R(31) + -22400);
    R(11) = ld32(base, (f + 396));
    R(5) = (R(26) + 256);
    R(10) = ld32(base, (f + 376));
    R(9) = ld32(base, (f + 380));
    R(8) = ld32(base, (f + 384));
    R(7) = ld32(base, (f + 364));
    R(6) = ld32(base, (f + 368));
    R(0) = ld32(base, (f + 372));
    st32(base, (R(26) + 272), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B2A15Cu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2408);
    R(4) = (R(27) + 2420);
    R(3) = (R(27) + 2432);
    R(11) = ld32(base, (R(27) + 2408));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2960);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2420));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2432));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 328), R(11));
    st32(base, (f + 332), R(10));
    st32(base, (f + 336), R(9));
    st32(base, (f + 340), R(8));
    st32(base, (f + 344), R(7));
    st32(base, (f + 348), R(6));
    st32(base, (f + 352), R(5));
    st32(base, (f + 356), R(4));
    st32(base, (f + 360), R(0));
    GM_CALLV(0x80B2A1B8u, 0x80B2A9A0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 332);
    GM_CALLV(0x80B2A1C8u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 332);
    R(23) = ld32(base, (f + 352));
    R(12) = ld32(base, (f + 356));
    R(4) = (R(30) + -22304);
    R(11) = ld32(base, (f + 360));
    R(5) = (R(26) + 320);
    R(10) = ld32(base, (f + 340));
    R(9) = ld32(base, (f + 344));
    R(8) = ld32(base, (f + 348));
    R(7) = ld32(base, (f + 328));
    R(6) = ld32(base, (f + 332));
    R(0) = ld32(base, (f + 336));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 332), R(29));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2A228u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2444);
    R(4) = (R(27) + 2456);
    R(3) = (R(27) + 2468);
    R(11) = ld32(base, (R(27) + 2444));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3000);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2456));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2468));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 292), R(11));
    st32(base, (f + 296), R(10));
    st32(base, (f + 300), R(9));
    st32(base, (f + 304), R(8));
    st32(base, (f + 308), R(7));
    st32(base, (f + 312), R(6));
    st32(base, (f + 316), R(5));
    st32(base, (f + 320), R(4));
    st32(base, (f + 324), R(0));
    GM_CALLV(0x80B2A284u, 0x80B2A990u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 396);
    GM_CALLV(0x80B2A294u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 396);
    R(23) = ld32(base, (f + 316));
    R(12) = ld32(base, (f + 320));
    R(4) = (R(30) + -22304);
    R(11) = ld32(base, (f + 324));
    R(5) = (R(26) + 384);
    R(10) = ld32(base, (f + 304));
    R(9) = ld32(base, (f + 308));
    R(8) = ld32(base, (f + 312));
    R(7) = ld32(base, (f + 292));
    R(6) = ld32(base, (f + 296));
    R(0) = ld32(base, (f + 300));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 396), R(29));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2A2F4u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2480);
    R(6) = (R(27) + 2492);
    R(5) = (R(27) + 2504);
    R(23) = ld32(base, (R(27) + 2480));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 3044);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 464);
    R(10) = ld32(base, (R(27) + 2492));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2504));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 256), R(23));
    st32(base, (f + 260), R(12));
    st32(base, (f + 264), R(11));
    st32(base, (f + 268), R(10));
    st32(base, (f + 272), R(9));
    st32(base, (f + 276), R(8));
    st32(base, (f + 280), R(7));
    st32(base, (f + 284), R(6));
    st32(base, (f + 288), R(0));
    GM_CALLV(0x80B2A354u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 464);
    R(23) = ld32(base, (f + 280));
    R(12) = ld32(base, (f + 284));
    R(4) = (R(31) + -22400);
    R(11) = ld32(base, (f + 288));
    R(5) = (R(26) + 448);
    R(10) = ld32(base, (f + 268));
    R(9) = ld32(base, (f + 272));
    R(8) = ld32(base, (f + 276));
    R(7) = ld32(base, (f + 256));
    R(6) = ld32(base, (f + 260));
    R(0) = ld32(base, (f + 264));
    st32(base, (R(26) + 464), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B2A3B0u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2516);
    R(4) = (R(27) + 2528);
    R(3) = (R(27) + 2540);
    R(11) = ld32(base, (R(27) + 2516));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3088);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2528));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2540));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 220), R(11));
    st32(base, (f + 224), R(10));
    st32(base, (f + 228), R(9));
    st32(base, (f + 232), R(8));
    st32(base, (f + 236), R(7));
    st32(base, (f + 240), R(6));
    st32(base, (f + 244), R(5));
    st32(base, (f + 248), R(4));
    st32(base, (f + 252), R(0));
    GM_CALLV(0x80B2A40Cu, 0x80B2A980u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 524);
    GM_CALLV(0x80B2A41Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 524);
    R(23) = ld32(base, (f + 244));
    R(12) = ld32(base, (f + 248));
    R(4) = (R(30) + -22304);
    R(11) = ld32(base, (f + 252));
    R(5) = (R(26) + 512);
    R(10) = ld32(base, (f + 232));
    R(9) = ld32(base, (f + 236));
    R(8) = ld32(base, (f + 240));
    R(7) = ld32(base, (f + 220));
    R(6) = ld32(base, (f + 224));
    R(0) = ld32(base, (f + 228));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 524), R(29));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2A47Cu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2552);
    R(4) = (R(27) + 2564);
    R(3) = (R(27) + 2576);
    R(11) = ld32(base, (R(27) + 2552));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3128);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2564));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2576));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 184), R(11));
    st32(base, (f + 188), R(10));
    st32(base, (f + 192), R(9));
    st32(base, (f + 196), R(8));
    st32(base, (f + 200), R(7));
    st32(base, (f + 204), R(6));
    st32(base, (f + 208), R(5));
    st32(base, (f + 212), R(4));
    st32(base, (f + 216), R(0));
    GM_CALLV(0x80B2A4D8u, 0x80B2A970u, 0);
    R(23) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 588);
    GM_CALLV(0x80B2A4E8u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 588);
    R(24) = ld32(base, (f + 208));
    R(12) = ld32(base, (f + 212));
    R(4) = (R(30) + -22304);
    R(11) = ld32(base, (f + 216));
    R(5) = (R(26) + 576);
    R(10) = ld32(base, (f + 196));
    R(9) = ld32(base, (f + 200));
    R(8) = ld32(base, (f + 204));
    R(7) = ld32(base, (f + 184));
    R(6) = ld32(base, (f + 188));
    R(0) = ld32(base, (f + 192));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 588), R(29));
    st32(base, (R(3) + 48), R(23));
    GM_CALLV(0x80B2A548u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2588);
    R(4) = (R(27) + 2600);
    R(3) = (R(27) + 2612);
    R(11) = ld32(base, (R(27) + 2588));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3172);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2600));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2612));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 148), R(11));
    st32(base, (f + 152), R(10));
    st32(base, (f + 156), R(9));
    st32(base, (f + 160), R(8));
    st32(base, (f + 164), R(7));
    st32(base, (f + 168), R(6));
    st32(base, (f + 172), R(5));
    st32(base, (f + 176), R(4));
    st32(base, (f + 180), R(0));
    GM_CALLV(0x80B2A5A4u, 0x80B2A960u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 652);
    GM_CALLV(0x80B2A5B4u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 652);
    R(25) = ld32(base, (f + 172));
    R(12) = ld32(base, (f + 176));
    R(4) = (R(30) + -22304);
    R(11) = ld32(base, (f + 180));
    R(5) = (R(26) + 640);
    R(10) = ld32(base, (f + 160));
    R(9) = ld32(base, (f + 164));
    R(8) = ld32(base, (f + 168));
    R(7) = ld32(base, (f + 148));
    R(6) = ld32(base, (f + 152));
    R(0) = ld32(base, (f + 156));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 652), R(29));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2A614u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2624);
    R(6) = (R(27) + 2636);
    R(5) = (R(27) + 2648);
    R(25) = ld32(base, (R(27) + 2624));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 3216);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 720);
    R(10) = ld32(base, (R(27) + 2636));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2648));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 112), R(25));
    st32(base, (f + 116), R(12));
    st32(base, (f + 120), R(11));
    st32(base, (f + 124), R(10));
    st32(base, (f + 128), R(9));
    st32(base, (f + 132), R(8));
    st32(base, (f + 136), R(7));
    st32(base, (f + 140), R(6));
    st32(base, (f + 144), R(0));
    GM_CALLV(0x80B2A674u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 720);
    R(25) = ld32(base, (f + 136));
    R(12) = ld32(base, (f + 140));
    R(4) = (R(31) + -22400);
    R(11) = ld32(base, (f + 144));
    R(5) = (R(26) + 704);
    R(10) = ld32(base, (f + 124));
    R(9) = ld32(base, (f + 128));
    R(8) = ld32(base, (f + 132));
    R(7) = ld32(base, (f + 112));
    R(6) = ld32(base, (f + 116));
    R(0) = ld32(base, (f + 120));
    st32(base, (R(26) + 720), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B2A6D0u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2660);
    R(4) = (R(27) + 2672);
    R(3) = (R(27) + 2684);
    R(11) = ld32(base, (R(27) + 2660));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3264);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2672));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2684));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 76), R(11));
    st32(base, (f + 80), R(10));
    st32(base, (f + 84), R(9));
    st32(base, (f + 88), R(8));
    st32(base, (f + 92), R(7));
    st32(base, (f + 96), R(6));
    st32(base, (f + 100), R(5));
    st32(base, (f + 104), R(4));
    st32(base, (f + 108), R(0));
    GM_CALLV(0x80B2A72Cu, 0x80B2A950u, 0);
    R(28) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 780);
    GM_CALLV(0x80B2A73Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 780);
    R(25) = ld32(base, (f + 100));
    R(12) = ld32(base, (f + 104));
    R(4) = (R(30) + -22304);
    R(11) = ld32(base, (f + 108));
    R(5) = (R(26) + 768);
    R(10) = ld32(base, (f + 88));
    R(9) = ld32(base, (f + 92));
    R(8) = ld32(base, (f + 96));
    R(7) = ld32(base, (f + 76));
    R(6) = ld32(base, (f + 80));
    R(0) = ld32(base, (f + 84));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 780), R(29));
    st32(base, (R(3) + 48), R(28));
    GM_CALLV(0x80B2A79Cu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2696);
    R(4) = (R(27) + 2708);
    R(3) = (R(27) + 2720);
    R(11) = ld32(base, (R(27) + 2696));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 3312);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2708));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2720));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 40), R(11));
    st32(base, (f + 44), R(10));
    st32(base, (f + 48), R(9));
    st32(base, (f + 52), R(8));
    st32(base, (f + 56), R(7));
    st32(base, (f + 60), R(6));
    st32(base, (f + 64), R(5));
    st32(base, (f + 68), R(4));
    st32(base, (f + 72), R(0));
    GM_CALLV(0x80B2A7F8u, 0x80B2A940u, 0);
    R(27) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 844);
    GM_CALLV(0x80B2A808u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 844);
    R(25) = ld32(base, (f + 64));
    R(12) = ld32(base, (f + 68));
    R(4) = (R(30) + -22304);
    R(11) = ld32(base, (f + 72));
    R(5) = (R(26) + 832);
    R(10) = ld32(base, (f + 52));
    R(9) = ld32(base, (f + 56));
    R(8) = ld32(base, (f + 60));
    R(7) = ld32(base, (f + 40));
    R(6) = ld32(base, (f + 44));
    R(0) = ld32(base, (f + 48));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 844), R(29));
    st32(base, (R(3) + 48), R(27));
    GM_CALLV(0x80B2A868u, 0x80B1CAC0u, 0);
    R(11) = (f + 592);
    R(0) = lr;
}

/* fn_4_DEF0 (fn_4_DEF0, 12 bytes) */
static void eb_m_2a940(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -11188);
}

/* fn_4_DF00 (fn_4_DF00, 12 bytes) */
static void eb_m_2a950(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -11252);
}

/* fn_4_DF10 (fn_4_DF10, 12 bytes) */
static void eb_m_2a960(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_DF20 (fn_4_DF20, 12 bytes) */
static void eb_m_2a970(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31036);
}

/* fn_4_DF30 (fn_4_DF30, 12 bytes) */
static void eb_m_2a980(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -11316);
}

/* fn_4_DF40 (fn_4_DF40, 12 bytes) */
static void eb_m_2a990(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31356);
}

/* fn_4_DF50 (fn_4_DF50, 12 bytes) */
static void eb_m_2a9a0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31804);
}

/* fn_4_DF60 (fn_4_DF60, 12 bytes) */
static void eb_m_2a9b0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -11444);
}

/* fn_4_DF70 (fn_4_DF70, 12 bytes) */
static void eb_m_2a9c0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -11892);
}

/* fn_4_10AE0 (fn_4_10AE0, 3160 bytes) */
static void eb_m_2d530(GM_CTX) {
    GM_FN(0x80B2D530); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 624);
    R(27) = (0 + 0x80B80000u);
    R(3) = (0 + 0x80B70000u);
    R(27) = (R(27) + -28920);
    R(26) = (0 + 0x80B90000u);
    R(3) = (R(3) + 16096);
    R(23) = ld32(base, (R(27) + 1936));
    { uint32_t ea_ = (R(3) + 268); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(24) = (R(27) + 56);
    R(7) = (R(27) + 1936);
    R(6) = (R(27) + 1948);
    { uint32_t ea_ = (R(3) + 284); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(5) = (R(27) + 1960);
    { uint32_t ea_ = (R(3) + 344); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(26) = (R(26) + -22672);
    { uint32_t ea_ = (R(3) + 388); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (R(27) + 2476);
    { uint32_t ea_ = (R(3) + 392); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(26) + 16);
    R(12) = ld32(base, (R(7) + 4));
    R(11) = ld32(base, (R(7) + 8));
    R(10) = ld32(base, (R(27) + 1948));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1960));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(24) + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(24) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(24) + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(24) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(24) + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(24) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(24) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(24) + 48); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (f + 544), R(23));
    st32(base, (f + 548), R(12));
    st32(base, (f + 552), R(11));
    st32(base, (f + 556), R(10));
    st32(base, (f + 560), R(9));
    st32(base, (f + 564), R(8));
    st32(base, (f + 568), R(7));
    st32(base, (f + 572), R(6));
    st32(base, (f + 576), R(0));
    GM_CALLV(0x80B2D614u, 0x8015F7C0u, 0);
    R(28) = (0 + 0x80B80000u);
    R(3) = (R(26) + 16);
    R(23) = ld32(base, (f + 568));
    R(28) = (R(28) + -25752);
    R(12) = ld32(base, (f + 572));
    R(29) = (0 + 0x80B30000u);
    R(11) = ld32(base, (f + 576));
    R(4) = (R(29) + -7792);
    R(10) = ld32(base, (f + 556));
    R(5) = (R(26) + 0);
    R(9) = ld32(base, (f + 560));
    R(8) = ld32(base, (f + 564));
    R(7) = ld32(base, (f + 544));
    R(6) = ld32(base, (f + 548));
    R(0) = ld32(base, (f + 552));
    st32(base, (R(26) + 16), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B2D67Cu, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 1972);
    R(6) = (R(27) + 1984);
    R(5) = (R(27) + 1996);
    R(23) = ld32(base, (R(27) + 1972));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2520);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 80);
    R(10) = ld32(base, (R(27) + 1984));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1996));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 508), R(23));
    st32(base, (f + 512), R(12));
    st32(base, (f + 516), R(11));
    st32(base, (f + 520), R(10));
    st32(base, (f + 524), R(9));
    st32(base, (f + 528), R(8));
    st32(base, (f + 532), R(7));
    st32(base, (f + 536), R(6));
    st32(base, (f + 540), R(0));
    GM_CALLV(0x80B2D6DCu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 80);
    R(23) = ld32(base, (f + 532));
    R(12) = ld32(base, (f + 536));
    R(4) = (R(29) + -7792);
    R(11) = ld32(base, (f + 540));
    R(5) = (R(26) + 64);
    R(10) = ld32(base, (f + 520));
    R(9) = ld32(base, (f + 524));
    R(8) = ld32(base, (f + 528));
    R(7) = ld32(base, (f + 508));
    R(6) = ld32(base, (f + 512));
    R(0) = ld32(base, (f + 516));
    st32(base, (R(26) + 80), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B2D738u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2008);
    R(4) = (R(27) + 2020);
    R(3) = (R(27) + 2032);
    R(11) = ld32(base, (R(27) + 2008));
    R(10) = ld32(base, (R(5) + 4));
    R(30) = (R(27) + 2560);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2020));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2032));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 472), R(11));
    st32(base, (f + 476), R(10));
    st32(base, (f + 480), R(9));
    st32(base, (f + 484), R(8));
    st32(base, (f + 488), R(7));
    st32(base, (f + 492), R(6));
    st32(base, (f + 496), R(5));
    st32(base, (f + 500), R(4));
    st32(base, (f + 504), R(0));
    GM_CALLV(0x80B2D794u, 0x80B2E2E0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(30) |R(30);
    R(3) = (R(26) + 140);
    GM_CALLV(0x80B2D7A4u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 140);
    R(23) = ld32(base, (f + 496));
    R(12) = ld32(base, (f + 500));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 504));
    R(30) = (R(30) + -25804);
    R(10) = ld32(base, (f + 484));
    R(31) = (0 + 0x80B30000u);
    R(9) = ld32(base, (f + 488));
    R(4) = (R(31) + -7696);
    R(8) = ld32(base, (f + 492));
    R(5) = (R(26) + 128);
    R(7) = ld32(base, (f + 472));
    R(6) = ld32(base, (f + 476));
    R(0) = ld32(base, (f + 480));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 140), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2D810u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2044);
    R(4) = (R(27) + 2056);
    R(3) = (R(27) + 2068);
    R(11) = ld32(base, (R(27) + 2044));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2600);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2056));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2068));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 436), R(11));
    st32(base, (f + 440), R(10));
    st32(base, (f + 444), R(9));
    st32(base, (f + 448), R(8));
    st32(base, (f + 452), R(7));
    st32(base, (f + 456), R(6));
    st32(base, (f + 460), R(5));
    st32(base, (f + 464), R(4));
    st32(base, (f + 468), R(0));
    GM_CALLV(0x80B2D86Cu, 0x80B2E2D0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 204);
    GM_CALLV(0x80B2D87Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 204);
    R(23) = ld32(base, (f + 460));
    R(12) = ld32(base, (f + 464));
    R(4) = (R(31) + -7696);
    R(11) = ld32(base, (f + 468));
    R(5) = (R(26) + 192);
    R(10) = ld32(base, (f + 448));
    R(9) = ld32(base, (f + 452));
    R(8) = ld32(base, (f + 456));
    R(7) = ld32(base, (f + 436));
    R(6) = ld32(base, (f + 440));
    R(0) = ld32(base, (f + 444));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 204), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2D8DCu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2080);
    R(4) = (R(27) + 2092);
    R(3) = (R(27) + 2104);
    R(11) = ld32(base, (R(27) + 2080));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2640);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2092));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2104));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 400), R(11));
    st32(base, (f + 404), R(10));
    st32(base, (f + 408), R(9));
    st32(base, (f + 412), R(8));
    st32(base, (f + 416), R(7));
    st32(base, (f + 420), R(6));
    st32(base, (f + 424), R(5));
    st32(base, (f + 428), R(4));
    st32(base, (f + 432), R(0));
    GM_CALLV(0x80B2D938u, 0x80B2E2C0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 268);
    GM_CALLV(0x80B2D948u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 268);
    R(23) = ld32(base, (f + 424));
    R(12) = ld32(base, (f + 428));
    R(4) = (R(31) + -7696);
    R(11) = ld32(base, (f + 432));
    R(5) = (R(26) + 256);
    R(10) = ld32(base, (f + 412));
    R(9) = ld32(base, (f + 416));
    R(8) = ld32(base, (f + 420));
    R(7) = ld32(base, (f + 400));
    R(6) = ld32(base, (f + 404));
    R(0) = ld32(base, (f + 408));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 268), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2D9A8u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2116);
    R(4) = (R(27) + 2128);
    R(3) = (R(27) + 2140);
    R(11) = ld32(base, (R(27) + 2116));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2680);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2128));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2140));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 364), R(11));
    st32(base, (f + 368), R(10));
    st32(base, (f + 372), R(9));
    st32(base, (f + 376), R(8));
    st32(base, (f + 380), R(7));
    st32(base, (f + 384), R(6));
    st32(base, (f + 388), R(5));
    st32(base, (f + 392), R(4));
    st32(base, (f + 396), R(0));
    GM_CALLV(0x80B2DA04u, 0x80B2E2B0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 332);
    GM_CALLV(0x80B2DA14u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 332);
    R(23) = ld32(base, (f + 388));
    R(12) = ld32(base, (f + 392));
    R(4) = (R(31) + -7696);
    R(11) = ld32(base, (f + 396));
    R(5) = (R(26) + 320);
    R(10) = ld32(base, (f + 376));
    R(9) = ld32(base, (f + 380));
    R(8) = ld32(base, (f + 384));
    R(7) = ld32(base, (f + 364));
    R(6) = ld32(base, (f + 368));
    R(0) = ld32(base, (f + 372));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 332), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2DA74u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2152);
    R(4) = (R(27) + 2164);
    R(3) = (R(27) + 2176);
    R(11) = ld32(base, (R(27) + 2152));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2720);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2164));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2176));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 328), R(11));
    st32(base, (f + 332), R(10));
    st32(base, (f + 336), R(9));
    st32(base, (f + 340), R(8));
    st32(base, (f + 344), R(7));
    st32(base, (f + 348), R(6));
    st32(base, (f + 352), R(5));
    st32(base, (f + 356), R(4));
    st32(base, (f + 360), R(0));
    GM_CALLV(0x80B2DAD0u, 0x80B2E2A0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 396);
    GM_CALLV(0x80B2DAE0u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 396);
    R(23) = ld32(base, (f + 352));
    R(12) = ld32(base, (f + 356));
    R(4) = (R(31) + -7696);
    R(11) = ld32(base, (f + 360));
    R(5) = (R(26) + 384);
    R(10) = ld32(base, (f + 340));
    R(9) = ld32(base, (f + 344));
    R(8) = ld32(base, (f + 348));
    R(7) = ld32(base, (f + 328));
    R(6) = ld32(base, (f + 332));
    R(0) = ld32(base, (f + 336));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 396), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2DB40u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2188);
    R(6) = (R(27) + 2200);
    R(5) = (R(27) + 2212);
    R(23) = ld32(base, (R(27) + 2188));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 2764);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 464);
    R(10) = ld32(base, (R(27) + 2200));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2212));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 292), R(23));
    st32(base, (f + 296), R(12));
    st32(base, (f + 300), R(11));
    st32(base, (f + 304), R(10));
    st32(base, (f + 308), R(9));
    st32(base, (f + 312), R(8));
    st32(base, (f + 316), R(7));
    st32(base, (f + 320), R(6));
    st32(base, (f + 324), R(0));
    GM_CALLV(0x80B2DBA0u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 464);
    R(23) = ld32(base, (f + 316));
    R(12) = ld32(base, (f + 320));
    R(4) = (R(29) + -7792);
    R(11) = ld32(base, (f + 324));
    R(5) = (R(26) + 448);
    R(10) = ld32(base, (f + 304));
    R(9) = ld32(base, (f + 308));
    R(8) = ld32(base, (f + 312));
    R(7) = ld32(base, (f + 292));
    R(6) = ld32(base, (f + 296));
    R(0) = ld32(base, (f + 300));
    st32(base, (R(26) + 464), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B2DBFCu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2224);
    R(4) = (R(27) + 2236);
    R(3) = (R(27) + 2248);
    R(11) = ld32(base, (R(27) + 2224));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2812);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2236));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2248));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 256), R(11));
    st32(base, (f + 260), R(10));
    st32(base, (f + 264), R(9));
    st32(base, (f + 268), R(8));
    st32(base, (f + 272), R(7));
    st32(base, (f + 276), R(6));
    st32(base, (f + 280), R(5));
    st32(base, (f + 284), R(4));
    st32(base, (f + 288), R(0));
    GM_CALLV(0x80B2DC58u, 0x80B2E290u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 524);
    GM_CALLV(0x80B2DC68u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 524);
    R(23) = ld32(base, (f + 280));
    R(12) = ld32(base, (f + 284));
    R(4) = (R(31) + -7696);
    R(11) = ld32(base, (f + 288));
    R(5) = (R(26) + 512);
    R(10) = ld32(base, (f + 268));
    R(9) = ld32(base, (f + 272));
    R(8) = ld32(base, (f + 276));
    R(7) = ld32(base, (f + 256));
    R(6) = ld32(base, (f + 260));
    R(0) = ld32(base, (f + 264));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 524), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2DCC8u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2260);
    R(4) = (R(27) + 2272);
    R(3) = (R(27) + 2284);
    R(11) = ld32(base, (R(27) + 2260));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2856);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2272));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2284));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 220), R(11));
    st32(base, (f + 224), R(10));
    st32(base, (f + 228), R(9));
    st32(base, (f + 232), R(8));
    st32(base, (f + 236), R(7));
    st32(base, (f + 240), R(6));
    st32(base, (f + 244), R(5));
    st32(base, (f + 248), R(4));
    st32(base, (f + 252), R(0));
    GM_CALLV(0x80B2DD24u, 0x80B2E280u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 588);
    GM_CALLV(0x80B2DD34u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 588);
    R(23) = ld32(base, (f + 244));
    R(12) = ld32(base, (f + 248));
    R(4) = (R(31) + -7696);
    R(11) = ld32(base, (f + 252));
    R(5) = (R(26) + 576);
    R(10) = ld32(base, (f + 232));
    R(9) = ld32(base, (f + 236));
    R(8) = ld32(base, (f + 240));
    R(7) = ld32(base, (f + 220));
    R(6) = ld32(base, (f + 224));
    R(0) = ld32(base, (f + 228));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 588), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2DD94u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2296);
    R(4) = (R(27) + 2308);
    R(3) = (R(27) + 2320);
    R(11) = ld32(base, (R(27) + 2296));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2896);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2308));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2320));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 184), R(11));
    st32(base, (f + 188), R(10));
    st32(base, (f + 192), R(9));
    st32(base, (f + 196), R(8));
    st32(base, (f + 200), R(7));
    st32(base, (f + 204), R(6));
    st32(base, (f + 208), R(5));
    st32(base, (f + 212), R(4));
    st32(base, (f + 216), R(0));
    GM_CALLV(0x80B2DDF0u, 0x80B2E270u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 652);
    GM_CALLV(0x80B2DE00u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 652);
    R(23) = ld32(base, (f + 208));
    R(12) = ld32(base, (f + 212));
    R(4) = (R(31) + -7696);
    R(11) = ld32(base, (f + 216));
    R(5) = (R(26) + 640);
    R(10) = ld32(base, (f + 196));
    R(9) = ld32(base, (f + 200));
    R(8) = ld32(base, (f + 204));
    R(7) = ld32(base, (f + 184));
    R(6) = ld32(base, (f + 188));
    R(0) = ld32(base, (f + 192));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 652), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2DE60u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2332);
    R(4) = (R(27) + 2344);
    R(3) = (R(27) + 2356);
    R(11) = ld32(base, (R(27) + 2332));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2936);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2344));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2356));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 148), R(11));
    st32(base, (f + 152), R(10));
    st32(base, (f + 156), R(9));
    st32(base, (f + 160), R(8));
    st32(base, (f + 164), R(7));
    st32(base, (f + 168), R(6));
    st32(base, (f + 172), R(5));
    st32(base, (f + 176), R(4));
    st32(base, (f + 180), R(0));
    GM_CALLV(0x80B2DEBCu, 0x80B2E260u, 0);
    R(23) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 716);
    GM_CALLV(0x80B2DECCu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 716);
    R(24) = ld32(base, (f + 172));
    R(12) = ld32(base, (f + 176));
    R(4) = (R(31) + -7696);
    R(11) = ld32(base, (f + 180));
    R(5) = (R(26) + 704);
    R(10) = ld32(base, (f + 160));
    R(9) = ld32(base, (f + 164));
    R(8) = ld32(base, (f + 168));
    R(7) = ld32(base, (f + 148));
    R(6) = ld32(base, (f + 152));
    R(0) = ld32(base, (f + 156));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 716), R(30));
    st32(base, (R(3) + 48), R(23));
    GM_CALLV(0x80B2DF2Cu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 2368);
    R(4) = (R(27) + 2380);
    R(3) = (R(27) + 2392);
    R(11) = ld32(base, (R(27) + 2368));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(27) + 2980);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 2380));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 2392));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 112), R(11));
    st32(base, (f + 116), R(10));
    st32(base, (f + 120), R(9));
    st32(base, (f + 124), R(8));
    st32(base, (f + 128), R(7));
    st32(base, (f + 132), R(6));
    st32(base, (f + 136), R(5));
    st32(base, (f + 140), R(4));
    st32(base, (f + 144), R(0));
    GM_CALLV(0x80B2DF88u, 0x80B2E250u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(26) + 780);
    GM_CALLV(0x80B2DF98u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 780);
    R(25) = ld32(base, (f + 136));
    R(12) = ld32(base, (f + 140));
    R(4) = (R(31) + -7696);
    R(11) = ld32(base, (f + 144));
    R(5) = (R(26) + 768);
    R(10) = ld32(base, (f + 124));
    R(9) = ld32(base, (f + 128));
    R(8) = ld32(base, (f + 132));
    R(7) = ld32(base, (f + 112));
    R(6) = ld32(base, (f + 116));
    R(0) = ld32(base, (f + 120));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 780), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B2DFF8u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2404);
    R(6) = (R(27) + 2416);
    R(5) = (R(27) + 2428);
    R(25) = ld32(base, (R(27) + 2404));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 3024);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 848);
    R(10) = ld32(base, (R(27) + 2416));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2428));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 76), R(25));
    st32(base, (f + 80), R(12));
    st32(base, (f + 84), R(11));
    st32(base, (f + 88), R(10));
    st32(base, (f + 92), R(9));
    st32(base, (f + 96), R(8));
    st32(base, (f + 100), R(7));
    st32(base, (f + 104), R(6));
    st32(base, (f + 108), R(0));
    GM_CALLV(0x80B2E058u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 848);
    R(25) = ld32(base, (f + 100));
    R(12) = ld32(base, (f + 104));
    R(4) = (R(29) + -7792);
    R(11) = ld32(base, (f + 108));
    R(5) = (R(26) + 832);
    R(10) = ld32(base, (f + 88));
    R(9) = ld32(base, (f + 92));
    R(8) = ld32(base, (f + 96));
    R(7) = ld32(base, (f + 76));
    R(6) = ld32(base, (f + 80));
    R(0) = ld32(base, (f + 84));
    st32(base, (R(26) + 848), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B2E0B4u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 2440);
    R(6) = (R(27) + 2452);
    R(5) = (R(27) + 2464);
    R(25) = ld32(base, (R(27) + 2440));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 3072);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 912);
    R(10) = ld32(base, (R(27) + 2452));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 2464));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 40), R(25));
    st32(base, (f + 44), R(12));
    st32(base, (f + 48), R(11));
    st32(base, (f + 52), R(10));
    st32(base, (f + 56), R(9));
    st32(base, (f + 60), R(8));
    st32(base, (f + 64), R(7));
    st32(base, (f + 68), R(6));
    st32(base, (f + 72), R(0));
    GM_CALLV(0x80B2E114u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 912);
    R(25) = ld32(base, (f + 64));
    R(12) = ld32(base, (f + 68));
    R(4) = (R(29) + -7792);
    R(11) = ld32(base, (f + 72));
    R(5) = (R(26) + 896);
    R(10) = ld32(base, (f + 52));
    R(9) = ld32(base, (f + 56));
    R(8) = ld32(base, (f + 60));
    R(7) = ld32(base, (f + 40));
    R(6) = ld32(base, (f + 44));
    R(0) = ld32(base, (f + 48));
    st32(base, (R(26) + 912), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B2E170u, 0x80B1CAC0u, 0);
    R(11) = (f + 624);
    R(0) = lr;
}

/* fn_4_11800 (fn_4_11800, 12 bytes) */
static void eb_m_2e250(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_11810 (fn_4_11810, 12 bytes) */
static void eb_m_2e260(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31036);
}

/* fn_4_11820 (fn_4_11820, 12 bytes) */
static void eb_m_2e270(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31740);
}

/* fn_4_11830 (fn_4_11830, 12 bytes) */
static void eb_m_2e280(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31804);
}

/* fn_4_11840 (fn_4_11840, 12 bytes) */
static void eb_m_2e290(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -10028);
}

/* fn_4_11850 (fn_4_11850, 12 bytes) */
static void eb_m_2e2a0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31420);
}

/* fn_4_11860 (fn_4_11860, 12 bytes) */
static void eb_m_2e2b0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32188);
}

/* fn_4_11870 (fn_4_11870, 12 bytes) */
static void eb_m_2e2c0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -10092);
}

/* fn_4_11880 (fn_4_11880, 12 bytes) */
static void eb_m_2e2d0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_11890 (fn_4_11890, 12 bytes) */
static void eb_m_2e2e0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -10476);
}

/* fn_4_11D00 (fn_4_11D00, 12 bytes) */
static void eb_m_2e750(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_11D10 (fn_4_11D10, 12 bytes) */
static void eb_m_2e760(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_11D20 (fn_4_11D20, 12 bytes) */
static void eb_m_2e770(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_11D30 (fn_4_11D30, 12 bytes) */
static void eb_m_2e780(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_11D40 (fn_4_11D40, 12 bytes) */
static void eb_m_2e790(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_11D50 (fn_4_11D50, 12 bytes) */
static void eb_m_2e7a0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_11D60 (fn_4_11D60, 12 bytes) */
static void eb_m_2e7b0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_11D70 (fn_4_11D70, 12 bytes) */
static void eb_m_2e7c0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_145C0 (fn_4_145C0, 4368 bytes) */
static void eb_m_31010(GM_CTX) {
    GM_FN(0x80B31010); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 832);
    R(28) = (0 + 0x80B80000u);
    R(29) = (0 + 0x80B70000u);
    R(28) = (R(28) + -25696);
    R(27) = (0 + 0x80B90000u);
    R(29) = (R(29) + 16592);
    R(11) = ld32(base, (R(28) + 2424));
    { uint32_t ea_ = (R(29) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = (R(28) + 48);
    { uint32_t ea_ = (R(29) + 80); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (R(28) + 2424);
    R(4) = (R(28) + 2436);
    R(3) = (R(28) + 2448);
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(27) + -21712);
    R(9) = ld32(base, (R(5) + 8));
    R(24) = (R(28) + 3144);
    R(8) = ld32(base, (R(28) + 2436));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2448));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(12) + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(12) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(12) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(12) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(12) + 36); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(12) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(12) + 44); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(12) + 48); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (f + 764), R(11));
    st32(base, (f + 768), R(10));
    st32(base, (f + 772), R(9));
    st32(base, (f + 776), R(8));
    st32(base, (f + 780), R(7));
    st32(base, (f + 784), R(6));
    st32(base, (f + 788), R(5));
    st32(base, (f + 792), R(4));
    st32(base, (f + 796), R(0));
    GM_CALLV(0x80B310E4u, 0x80B32290u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(24) |R(24);
    R(3) = (R(27) + 12);
    GM_CALLV(0x80B310F4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 12);
    R(24) = ld32(base, (f + 788));
    R(12) = ld32(base, (f + 792));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 796));
    R(30) = (R(30) + -21764);
    R(10) = ld32(base, (f + 776));
    R(31) = (0 + 0x80B30000u);
    R(9) = ld32(base, (f + 780));
    R(4) = (R(31) + 8576);
    R(8) = ld32(base, (f + 784));
    R(5) = (R(27) + 0);
    R(7) = ld32(base, (f + 764));
    R(6) = ld32(base, (f + 768));
    R(0) = ld32(base, (f + 772));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 12), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31160u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2460);
    R(4) = (R(28) + 2472);
    R(3) = (R(28) + 2484);
    R(11) = ld32(base, (R(28) + 2460));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3184);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2472));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2484));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 728), R(11));
    st32(base, (f + 732), R(10));
    st32(base, (f + 736), R(9));
    st32(base, (f + 740), R(8));
    st32(base, (f + 744), R(7));
    st32(base, (f + 748), R(6));
    st32(base, (f + 752), R(5));
    st32(base, (f + 756), R(4));
    st32(base, (f + 760), R(0));
    GM_CALLV(0x80B311BCu, 0x80B32280u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 76);
    GM_CALLV(0x80B311CCu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 76);
    R(24) = ld32(base, (f + 752));
    R(12) = ld32(base, (f + 756));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 760));
    R(5) = (R(27) + 64);
    R(10) = ld32(base, (f + 740));
    R(9) = ld32(base, (f + 744));
    R(8) = ld32(base, (f + 748));
    R(7) = ld32(base, (f + 728));
    R(6) = ld32(base, (f + 732));
    R(0) = ld32(base, (f + 736));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 76), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3122Cu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2496);
    R(4) = (R(28) + 2508);
    R(3) = (R(28) + 2520);
    R(11) = ld32(base, (R(28) + 2496));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3224);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2508));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2520));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 692), R(11));
    st32(base, (f + 696), R(10));
    st32(base, (f + 700), R(9));
    st32(base, (f + 704), R(8));
    st32(base, (f + 708), R(7));
    st32(base, (f + 712), R(6));
    st32(base, (f + 716), R(5));
    st32(base, (f + 720), R(4));
    st32(base, (f + 724), R(0));
    GM_CALLV(0x80B31288u, 0x80B32270u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 140);
    GM_CALLV(0x80B31298u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 140);
    R(24) = ld32(base, (f + 716));
    R(12) = ld32(base, (f + 720));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 724));
    R(5) = (R(27) + 128);
    R(10) = ld32(base, (f + 704));
    R(9) = ld32(base, (f + 708));
    R(8) = ld32(base, (f + 712));
    R(7) = ld32(base, (f + 692));
    R(6) = ld32(base, (f + 696));
    R(0) = ld32(base, (f + 700));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 140), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B312F8u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2532);
    R(4) = (R(28) + 2544);
    R(3) = (R(28) + 2556);
    R(11) = ld32(base, (R(28) + 2532));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3272);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2544));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2556));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 656), R(11));
    st32(base, (f + 660), R(10));
    st32(base, (f + 664), R(9));
    st32(base, (f + 668), R(8));
    st32(base, (f + 672), R(7));
    st32(base, (f + 676), R(6));
    st32(base, (f + 680), R(5));
    st32(base, (f + 684), R(4));
    st32(base, (f + 688), R(0));
    GM_CALLV(0x80B31354u, 0x80B32260u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 204);
    GM_CALLV(0x80B31364u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 204);
    R(24) = ld32(base, (f + 680));
    R(12) = ld32(base, (f + 684));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 688));
    R(5) = (R(27) + 192);
    R(10) = ld32(base, (f + 668));
    R(9) = ld32(base, (f + 672));
    R(8) = ld32(base, (f + 676));
    R(7) = ld32(base, (f + 656));
    R(6) = ld32(base, (f + 660));
    R(0) = ld32(base, (f + 664));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 204), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B313C4u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2568);
    R(4) = (R(28) + 2580);
    R(3) = (R(28) + 2592);
    R(11) = ld32(base, (R(28) + 2568));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3312);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2580));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2592));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 620), R(11));
    st32(base, (f + 624), R(10));
    st32(base, (f + 628), R(9));
    st32(base, (f + 632), R(8));
    st32(base, (f + 636), R(7));
    st32(base, (f + 640), R(6));
    st32(base, (f + 644), R(5));
    st32(base, (f + 648), R(4));
    st32(base, (f + 652), R(0));
    GM_CALLV(0x80B31420u, 0x80B32250u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 268);
    GM_CALLV(0x80B31430u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 268);
    R(24) = ld32(base, (f + 644));
    R(12) = ld32(base, (f + 648));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 652));
    R(5) = (R(27) + 256);
    R(10) = ld32(base, (f + 632));
    R(9) = ld32(base, (f + 636));
    R(8) = ld32(base, (f + 640));
    R(7) = ld32(base, (f + 620));
    R(6) = ld32(base, (f + 624));
    R(0) = ld32(base, (f + 628));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 268), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31490u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2604);
    R(4) = (R(28) + 2616);
    R(3) = (R(28) + 2628);
    R(11) = ld32(base, (R(28) + 2604));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3352);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2616));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2628));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 584), R(11));
    st32(base, (f + 588), R(10));
    st32(base, (f + 592), R(9));
    st32(base, (f + 596), R(8));
    st32(base, (f + 600), R(7));
    st32(base, (f + 604), R(6));
    st32(base, (f + 608), R(5));
    st32(base, (f + 612), R(4));
    st32(base, (f + 616), R(0));
    GM_CALLV(0x80B314ECu, 0x80B2E750u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 332);
    GM_CALLV(0x80B314FCu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 332);
    R(24) = ld32(base, (f + 608));
    R(12) = ld32(base, (f + 612));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 616));
    R(5) = (R(27) + 320);
    R(10) = ld32(base, (f + 596));
    R(9) = ld32(base, (f + 600));
    R(8) = ld32(base, (f + 604));
    R(7) = ld32(base, (f + 584));
    R(6) = ld32(base, (f + 588));
    R(0) = ld32(base, (f + 592));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 332), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3155Cu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2640);
    R(4) = (R(28) + 2652);
    R(3) = (R(28) + 2664);
    R(11) = ld32(base, (R(28) + 2640));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3388);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2652));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2664));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 548), R(11));
    st32(base, (f + 552), R(10));
    st32(base, (f + 556), R(9));
    st32(base, (f + 560), R(8));
    st32(base, (f + 564), R(7));
    st32(base, (f + 568), R(6));
    st32(base, (f + 572), R(5));
    st32(base, (f + 576), R(4));
    st32(base, (f + 580), R(0));
    GM_CALLV(0x80B315B8u, 0x80B2E760u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 396);
    GM_CALLV(0x80B315C8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 396);
    R(24) = ld32(base, (f + 572));
    R(12) = ld32(base, (f + 576));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 580));
    R(5) = (R(27) + 384);
    R(10) = ld32(base, (f + 560));
    R(9) = ld32(base, (f + 564));
    R(8) = ld32(base, (f + 568));
    R(7) = ld32(base, (f + 548));
    R(6) = ld32(base, (f + 552));
    R(0) = ld32(base, (f + 556));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 396), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31628u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2676);
    R(4) = (R(28) + 2688);
    R(3) = (R(28) + 2700);
    R(11) = ld32(base, (R(28) + 2676));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3424);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2688));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2700));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 512), R(11));
    st32(base, (f + 516), R(10));
    st32(base, (f + 520), R(9));
    st32(base, (f + 524), R(8));
    st32(base, (f + 528), R(7));
    st32(base, (f + 532), R(6));
    st32(base, (f + 536), R(5));
    st32(base, (f + 540), R(4));
    st32(base, (f + 544), R(0));
    GM_CALLV(0x80B31684u, 0x80B2E770u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 460);
    GM_CALLV(0x80B31694u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 460);
    R(24) = ld32(base, (f + 536));
    R(12) = ld32(base, (f + 540));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 544));
    R(5) = (R(27) + 448);
    R(10) = ld32(base, (f + 524));
    R(9) = ld32(base, (f + 528));
    R(8) = ld32(base, (f + 532));
    R(7) = ld32(base, (f + 512));
    R(6) = ld32(base, (f + 516));
    R(0) = ld32(base, (f + 520));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 460), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B316F4u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2712);
    R(4) = (R(28) + 2724);
    R(3) = (R(28) + 2736);
    R(11) = ld32(base, (R(28) + 2712));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3460);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2724));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2736));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 476), R(11));
    st32(base, (f + 480), R(10));
    st32(base, (f + 484), R(9));
    st32(base, (f + 488), R(8));
    st32(base, (f + 492), R(7));
    st32(base, (f + 496), R(6));
    st32(base, (f + 500), R(5));
    st32(base, (f + 504), R(4));
    st32(base, (f + 508), R(0));
    GM_CALLV(0x80B31750u, 0x80B2E780u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 524);
    GM_CALLV(0x80B31760u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 524);
    R(24) = ld32(base, (f + 500));
    R(12) = ld32(base, (f + 504));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 508));
    R(5) = (R(27) + 512);
    R(10) = ld32(base, (f + 488));
    R(9) = ld32(base, (f + 492));
    R(8) = ld32(base, (f + 496));
    R(7) = ld32(base, (f + 476));
    R(6) = ld32(base, (f + 480));
    R(0) = ld32(base, (f + 484));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 524), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B317C0u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2748);
    R(4) = (R(28) + 2760);
    R(3) = (R(28) + 2772);
    R(11) = ld32(base, (R(28) + 2748));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3500);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2760));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2772));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 440), R(11));
    st32(base, (f + 444), R(10));
    st32(base, (f + 448), R(9));
    st32(base, (f + 452), R(8));
    st32(base, (f + 456), R(7));
    st32(base, (f + 460), R(6));
    st32(base, (f + 464), R(5));
    st32(base, (f + 468), R(4));
    st32(base, (f + 472), R(0));
    GM_CALLV(0x80B3181Cu, 0x80B2E790u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 588);
    GM_CALLV(0x80B3182Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 588);
    R(24) = ld32(base, (f + 464));
    R(12) = ld32(base, (f + 468));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 472));
    R(5) = (R(27) + 576);
    R(10) = ld32(base, (f + 452));
    R(9) = ld32(base, (f + 456));
    R(8) = ld32(base, (f + 460));
    R(7) = ld32(base, (f + 440));
    R(6) = ld32(base, (f + 444));
    R(0) = ld32(base, (f + 448));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 588), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3188Cu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2784);
    R(4) = (R(28) + 2796);
    R(3) = (R(28) + 2808);
    R(11) = ld32(base, (R(28) + 2784));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3536);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2796));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2808));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 404), R(11));
    st32(base, (f + 408), R(10));
    st32(base, (f + 412), R(9));
    st32(base, (f + 416), R(8));
    st32(base, (f + 420), R(7));
    st32(base, (f + 424), R(6));
    st32(base, (f + 428), R(5));
    st32(base, (f + 432), R(4));
    st32(base, (f + 436), R(0));
    GM_CALLV(0x80B318E8u, 0x80B2E7A0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 652);
    GM_CALLV(0x80B318F8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 652);
    R(24) = ld32(base, (f + 428));
    R(12) = ld32(base, (f + 432));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 436));
    R(5) = (R(27) + 640);
    R(10) = ld32(base, (f + 416));
    R(9) = ld32(base, (f + 420));
    R(8) = ld32(base, (f + 424));
    R(7) = ld32(base, (f + 404));
    R(6) = ld32(base, (f + 408));
    R(0) = ld32(base, (f + 412));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 652), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31958u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2820);
    R(4) = (R(28) + 2832);
    R(3) = (R(28) + 2844);
    R(11) = ld32(base, (R(28) + 2820));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3572);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2832));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2844));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 368), R(11));
    st32(base, (f + 372), R(10));
    st32(base, (f + 376), R(9));
    st32(base, (f + 380), R(8));
    st32(base, (f + 384), R(7));
    st32(base, (f + 388), R(6));
    st32(base, (f + 392), R(5));
    st32(base, (f + 396), R(4));
    st32(base, (f + 400), R(0));
    GM_CALLV(0x80B319B4u, 0x80B2E7B0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 716);
    GM_CALLV(0x80B319C4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 716);
    R(24) = ld32(base, (f + 392));
    R(12) = ld32(base, (f + 396));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 400));
    R(5) = (R(27) + 704);
    R(10) = ld32(base, (f + 380));
    R(9) = ld32(base, (f + 384));
    R(8) = ld32(base, (f + 388));
    R(7) = ld32(base, (f + 368));
    R(6) = ld32(base, (f + 372));
    R(0) = ld32(base, (f + 376));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 716), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31A24u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2856);
    R(4) = (R(28) + 2868);
    R(3) = (R(28) + 2880);
    R(11) = ld32(base, (R(28) + 2856));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3608);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2868));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2880));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 332), R(11));
    st32(base, (f + 336), R(10));
    st32(base, (f + 340), R(9));
    st32(base, (f + 344), R(8));
    st32(base, (f + 348), R(7));
    st32(base, (f + 352), R(6));
    st32(base, (f + 356), R(5));
    st32(base, (f + 360), R(4));
    st32(base, (f + 364), R(0));
    GM_CALLV(0x80B31A80u, 0x80B32240u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 780);
    GM_CALLV(0x80B31A90u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 780);
    R(24) = ld32(base, (f + 356));
    R(12) = ld32(base, (f + 360));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 364));
    R(5) = (R(27) + 768);
    R(10) = ld32(base, (f + 344));
    R(9) = ld32(base, (f + 348));
    R(8) = ld32(base, (f + 352));
    R(7) = ld32(base, (f + 332));
    R(6) = ld32(base, (f + 336));
    R(0) = ld32(base, (f + 340));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 780), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31AF0u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2892);
    R(4) = (R(28) + 2904);
    R(3) = (R(28) + 2916);
    R(11) = ld32(base, (R(28) + 2892));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3644);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2904));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2916));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 296), R(11));
    st32(base, (f + 300), R(10));
    st32(base, (f + 304), R(9));
    st32(base, (f + 308), R(8));
    st32(base, (f + 312), R(7));
    st32(base, (f + 316), R(6));
    st32(base, (f + 320), R(5));
    st32(base, (f + 324), R(4));
    st32(base, (f + 328), R(0));
    GM_CALLV(0x80B31B4Cu, 0x80B32230u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 844);
    GM_CALLV(0x80B31B5Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 844);
    R(24) = ld32(base, (f + 320));
    R(12) = ld32(base, (f + 324));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 328));
    R(5) = (R(27) + 832);
    R(10) = ld32(base, (f + 308));
    R(9) = ld32(base, (f + 312));
    R(8) = ld32(base, (f + 316));
    R(7) = ld32(base, (f + 296));
    R(6) = ld32(base, (f + 300));
    R(0) = ld32(base, (f + 304));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 844), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31BBCu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2928);
    R(4) = (R(28) + 2940);
    R(3) = (R(28) + 2952);
    R(11) = ld32(base, (R(28) + 2928));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3688);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2940));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2952));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 260), R(11));
    st32(base, (f + 264), R(10));
    st32(base, (f + 268), R(9));
    st32(base, (f + 272), R(8));
    st32(base, (f + 276), R(7));
    st32(base, (f + 280), R(6));
    st32(base, (f + 284), R(5));
    st32(base, (f + 288), R(4));
    st32(base, (f + 292), R(0));
    GM_CALLV(0x80B31C18u, 0x80B32220u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 908);
    GM_CALLV(0x80B31C28u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 908);
    R(24) = ld32(base, (f + 284));
    R(12) = ld32(base, (f + 288));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 292));
    R(5) = (R(27) + 896);
    R(10) = ld32(base, (f + 272));
    R(9) = ld32(base, (f + 276));
    R(8) = ld32(base, (f + 280));
    R(7) = ld32(base, (f + 260));
    R(6) = ld32(base, (f + 264));
    R(0) = ld32(base, (f + 268));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 908), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31C88u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2964);
    R(4) = (R(28) + 2976);
    R(3) = (R(28) + 2988);
    R(11) = ld32(base, (R(28) + 2964));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3728);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2976));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2988));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 224), R(11));
    st32(base, (f + 228), R(10));
    st32(base, (f + 232), R(9));
    st32(base, (f + 236), R(8));
    st32(base, (f + 240), R(7));
    st32(base, (f + 244), R(6));
    st32(base, (f + 248), R(5));
    st32(base, (f + 252), R(4));
    st32(base, (f + 256), R(0));
    GM_CALLV(0x80B31CE4u, 0x80B2E7C0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 972);
    GM_CALLV(0x80B31CF4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 972);
    R(24) = ld32(base, (f + 248));
    R(12) = ld32(base, (f + 252));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 256));
    R(5) = (R(27) + 960);
    R(10) = ld32(base, (f + 236));
    R(9) = ld32(base, (f + 240));
    R(8) = ld32(base, (f + 244));
    R(7) = ld32(base, (f + 224));
    R(6) = ld32(base, (f + 228));
    R(0) = ld32(base, (f + 232));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 972), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31D54u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 3000);
    R(4) = (R(28) + 3012);
    R(3) = (R(28) + 3024);
    R(11) = ld32(base, (R(28) + 3000));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3772);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 3012));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 3024));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 188), R(11));
    st32(base, (f + 192), R(10));
    st32(base, (f + 196), R(9));
    st32(base, (f + 200), R(8));
    st32(base, (f + 204), R(7));
    st32(base, (f + 208), R(6));
    st32(base, (f + 212), R(5));
    st32(base, (f + 216), R(4));
    st32(base, (f + 220), R(0));
    GM_CALLV(0x80B31DB0u, 0x80B32210u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1036);
    GM_CALLV(0x80B31DC0u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1036);
    R(24) = ld32(base, (f + 212));
    R(12) = ld32(base, (f + 216));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 220));
    R(5) = (R(27) + 1024);
    R(10) = ld32(base, (f + 200));
    R(9) = ld32(base, (f + 204));
    R(8) = ld32(base, (f + 208));
    R(7) = ld32(base, (f + 188));
    R(6) = ld32(base, (f + 192));
    R(0) = ld32(base, (f + 196));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1036), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31E20u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 3036);
    R(4) = (R(28) + 3048);
    R(3) = (R(28) + 3060);
    R(11) = ld32(base, (R(28) + 3036));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3812);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 3048));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 3060));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 152), R(11));
    st32(base, (f + 156), R(10));
    st32(base, (f + 160), R(9));
    st32(base, (f + 164), R(8));
    st32(base, (f + 168), R(7));
    st32(base, (f + 172), R(6));
    st32(base, (f + 176), R(5));
    st32(base, (f + 180), R(4));
    st32(base, (f + 184), R(0));
    GM_CALLV(0x80B31E7Cu, 0x80B32200u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1100);
    GM_CALLV(0x80B31E8Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1100);
    R(24) = ld32(base, (f + 176));
    R(12) = ld32(base, (f + 180));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 184));
    R(5) = (R(27) + 1088);
    R(10) = ld32(base, (f + 164));
    R(9) = ld32(base, (f + 168));
    R(8) = ld32(base, (f + 172));
    R(7) = ld32(base, (f + 152));
    R(6) = ld32(base, (f + 156));
    R(0) = ld32(base, (f + 160));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1100), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B31EECu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 3072);
    R(4) = (R(28) + 3084);
    R(3) = (R(28) + 3096);
    R(11) = ld32(base, (R(28) + 3072));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3852);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 3084));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 3096));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 116), R(11));
    st32(base, (f + 120), R(10));
    st32(base, (f + 124), R(9));
    st32(base, (f + 128), R(8));
    st32(base, (f + 132), R(7));
    st32(base, (f + 136), R(6));
    st32(base, (f + 140), R(5));
    st32(base, (f + 144), R(4));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x80B31F48u, 0x80B321F0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1164);
    GM_CALLV(0x80B31F58u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1164);
    R(25) = ld32(base, (f + 140));
    R(12) = ld32(base, (f + 144));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 148));
    R(5) = (R(27) + 1152);
    R(10) = ld32(base, (f + 128));
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1164), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B31FB8u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 3108);
    R(4) = (R(28) + 3120);
    R(3) = (R(28) + 3132);
    R(11) = ld32(base, (R(28) + 3108));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 3892);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 3120));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 3132));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 80), R(11));
    st32(base, (f + 84), R(10));
    st32(base, (f + 88), R(9));
    st32(base, (f + 92), R(8));
    st32(base, (f + 96), R(7));
    st32(base, (f + 100), R(6));
    st32(base, (f + 104), R(5));
    st32(base, (f + 108), R(4));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x80B32014u, 0x80B321E0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1228);
    GM_CALLV(0x80B32024u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1228);
    R(26) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(31) + 8576);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(27) + 1216);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1228), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B32084u, 0x80B1CAC0u, 0);
    R(0) = ld8(base, (R(27) + 1280));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B32108; }
    { uint32_t ea_ = (R(29) + 0); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    R(3) = (R(28) + 216);
    { uint32_t ea_ = (R(29) + 104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(29) + 84); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 88); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 92); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 96); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 100); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 88); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 112); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 132); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(27) + 1280), R(0));
L_80B32108:;
    R(11) = (f + 832);
    R(0) = lr;
}

/* fn_4_15790 (fn_4_15790, 12 bytes) */
static void eb_m_321e0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -9388);
}

/* fn_4_157A0 (fn_4_157A0, 12 bytes) */
static void eb_m_321f0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31740);
}

/* fn_4_157B0 (fn_4_157B0, 12 bytes) */
static void eb_m_32200(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31804);
}

/* fn_4_157C0 (fn_4_157C0, 12 bytes) */
static void eb_m_32210(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31292);
}

/* fn_4_157D0 (fn_4_157D0, 12 bytes) */
static void eb_m_32220(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -8684);
}

/* fn_4_157E0 (fn_4_157E0, 12 bytes) */
static void eb_m_32230(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31420);
}

/* fn_4_157F0 (fn_4_157F0, 12 bytes) */
static void eb_m_32240(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32188);
}

/* fn_4_15800 (fn_4_15800, 12 bytes) */
static void eb_m_32250(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -9324);
}

/* fn_4_15810 (fn_4_15810, 12 bytes) */
static void eb_m_32260(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32316);
}

/* fn_4_15820 (fn_4_15820, 12 bytes) */
static void eb_m_32270(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30908);
}

/* fn_4_15830 (fn_4_15830, 12 bytes) */
static void eb_m_32280(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_15840 (fn_4_15840, 12 bytes) */
static void eb_m_32290(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31036);
}

/* fn_4_17970 (fn_4_17970, 1804 bytes) */
static void eb_m_343c0(GM_CTX) {
    GM_FN(0x80B343C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 352);
    R(28) = (0 + 0x80B80000u);
    R(27) = (0 + 0x80B90000u);
    R(28) = (R(28) + -21640);
    R(29) = (0 + 0x80B70000u);
    R(5) = (R(28) + 2264);
    R(11) = ld32(base, (R(28) + 2264));
    R(4) = (R(28) + 2276);
    R(3) = (R(28) + 2288);
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(27) + -20424);
    R(9) = ld32(base, (R(5) + 8));
    R(29) = (R(29) + 16792);
    R(8) = ld32(base, (R(28) + 2276));
    R(24) = (R(28) + 2552);
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2288));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 284), R(11));
    st32(base, (f + 288), R(10));
    st32(base, (f + 292), R(9));
    st32(base, (f + 296), R(8));
    st32(base, (f + 300), R(7));
    st32(base, (f + 304), R(6));
    st32(base, (f + 308), R(5));
    st32(base, (f + 312), R(4));
    st32(base, (f + 316), R(0));
    GM_CALLV(0x80B34448u, 0x80B34C00u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(24) |R(24);
    R(3) = (R(27) + 12);
    GM_CALLV(0x80B34458u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 12);
    R(24) = ld32(base, (f + 308));
    R(12) = ld32(base, (f + 312));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 316));
    R(30) = (R(30) + -18756);
    R(10) = ld32(base, (f + 296));
    R(31) = (0 + 0x80B30000u);
    R(9) = ld32(base, (f + 300));
    R(4) = (R(31) + 19248);
    R(8) = ld32(base, (f + 304));
    R(5) = (R(27) + 0);
    R(7) = ld32(base, (f + 284));
    R(6) = ld32(base, (f + 288));
    R(0) = ld32(base, (f + 292));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 12), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B344C4u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2300);
    R(4) = (R(28) + 2312);
    R(3) = (R(28) + 2324);
    R(11) = ld32(base, (R(28) + 2300));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2592);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2312));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2324));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 248), R(11));
    st32(base, (f + 252), R(10));
    st32(base, (f + 256), R(9));
    st32(base, (f + 260), R(8));
    st32(base, (f + 264), R(7));
    st32(base, (f + 268), R(6));
    st32(base, (f + 272), R(5));
    st32(base, (f + 276), R(4));
    st32(base, (f + 280), R(0));
    GM_CALLV(0x80B34520u, 0x80B34BF0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 76);
    GM_CALLV(0x80B34530u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 76);
    R(24) = ld32(base, (f + 272));
    R(12) = ld32(base, (f + 276));
    R(4) = (R(31) + 19248);
    R(11) = ld32(base, (f + 280));
    R(5) = (R(27) + 64);
    R(10) = ld32(base, (f + 260));
    R(9) = ld32(base, (f + 264));
    R(8) = ld32(base, (f + 268));
    R(7) = ld32(base, (f + 248));
    R(6) = ld32(base, (f + 252));
    R(0) = ld32(base, (f + 256));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 76), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B34590u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2336);
    R(4) = (R(28) + 2348);
    R(3) = (R(28) + 2360);
    R(11) = ld32(base, (R(28) + 2336));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2636);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2348));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2360));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 212), R(11));
    st32(base, (f + 216), R(10));
    st32(base, (f + 220), R(9));
    st32(base, (f + 224), R(8));
    st32(base, (f + 228), R(7));
    st32(base, (f + 232), R(6));
    st32(base, (f + 236), R(5));
    st32(base, (f + 240), R(4));
    st32(base, (f + 244), R(0));
    GM_CALLV(0x80B345ECu, 0x80B34BE0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 140);
    GM_CALLV(0x80B345FCu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 140);
    R(24) = ld32(base, (f + 236));
    R(12) = ld32(base, (f + 240));
    R(4) = (R(31) + 19248);
    R(11) = ld32(base, (f + 244));
    R(5) = (R(27) + 128);
    R(10) = ld32(base, (f + 224));
    R(9) = ld32(base, (f + 228));
    R(8) = ld32(base, (f + 232));
    R(7) = ld32(base, (f + 212));
    R(6) = ld32(base, (f + 216));
    R(0) = ld32(base, (f + 220));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 140), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3465Cu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2372);
    R(4) = (R(28) + 2384);
    R(3) = (R(28) + 2396);
    R(11) = ld32(base, (R(28) + 2372));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2684);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2384));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2396));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 176), R(11));
    st32(base, (f + 180), R(10));
    st32(base, (f + 184), R(9));
    st32(base, (f + 188), R(8));
    st32(base, (f + 192), R(7));
    st32(base, (f + 196), R(6));
    st32(base, (f + 200), R(5));
    st32(base, (f + 204), R(4));
    st32(base, (f + 208), R(0));
    GM_CALLV(0x80B346B8u, 0x80B34BD0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 204);
    GM_CALLV(0x80B346C8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 204);
    R(24) = ld32(base, (f + 200));
    R(12) = ld32(base, (f + 204));
    R(4) = (R(31) + 19248);
    R(11) = ld32(base, (f + 208));
    R(5) = (R(27) + 192);
    R(10) = ld32(base, (f + 188));
    R(9) = ld32(base, (f + 192));
    R(8) = ld32(base, (f + 196));
    R(7) = ld32(base, (f + 176));
    R(6) = ld32(base, (f + 180));
    R(0) = ld32(base, (f + 184));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 204), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B34728u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2408);
    R(4) = (R(28) + 2420);
    R(3) = (R(28) + 2432);
    R(11) = ld32(base, (R(28) + 2408));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2728);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2420));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2432));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 140), R(11));
    st32(base, (f + 144), R(10));
    st32(base, (f + 148), R(9));
    st32(base, (f + 152), R(8));
    st32(base, (f + 156), R(7));
    st32(base, (f + 160), R(6));
    st32(base, (f + 164), R(5));
    st32(base, (f + 168), R(4));
    st32(base, (f + 172), R(0));
    GM_CALLV(0x80B34784u, 0x80B34BC0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 268);
    GM_CALLV(0x80B34794u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 268);
    R(24) = ld32(base, (f + 164));
    R(12) = ld32(base, (f + 168));
    R(4) = (R(31) + 19248);
    R(11) = ld32(base, (f + 172));
    R(5) = (R(27) + 256);
    R(10) = ld32(base, (f + 152));
    R(9) = ld32(base, (f + 156));
    R(8) = ld32(base, (f + 160));
    R(7) = ld32(base, (f + 140));
    R(6) = ld32(base, (f + 144));
    R(0) = ld32(base, (f + 148));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 268), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B347F4u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2444);
    R(4) = (R(28) + 2456);
    R(3) = (R(28) + 2468);
    R(11) = ld32(base, (R(28) + 2444));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2768);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2456));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2468));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 104), R(11));
    st32(base, (f + 108), R(10));
    st32(base, (f + 112), R(9));
    st32(base, (f + 116), R(8));
    st32(base, (f + 120), R(7));
    st32(base, (f + 124), R(6));
    st32(base, (f + 128), R(5));
    st32(base, (f + 132), R(4));
    st32(base, (f + 136), R(0));
    GM_CALLV(0x80B34850u, 0x80B34BB0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 332);
    GM_CALLV(0x80B34860u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 332);
    R(24) = ld32(base, (f + 128));
    R(12) = ld32(base, (f + 132));
    R(4) = (R(31) + 19248);
    R(11) = ld32(base, (f + 136));
    R(5) = (R(27) + 320);
    R(10) = ld32(base, (f + 116));
    R(9) = ld32(base, (f + 120));
    R(8) = ld32(base, (f + 124));
    R(7) = ld32(base, (f + 104));
    R(6) = ld32(base, (f + 108));
    R(0) = ld32(base, (f + 112));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 332), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B348C0u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2480);
    R(4) = (R(28) + 2492);
    R(3) = (R(28) + 2504);
    R(11) = ld32(base, (R(28) + 2480));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2804);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2492));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2504));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 68), R(11));
    st32(base, (f + 72), R(10));
    st32(base, (f + 76), R(9));
    st32(base, (f + 80), R(8));
    st32(base, (f + 84), R(7));
    st32(base, (f + 88), R(6));
    st32(base, (f + 92), R(5));
    st32(base, (f + 96), R(4));
    st32(base, (f + 100), R(0));
    GM_CALLV(0x80B3491Cu, 0x80B34BA0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 396);
    GM_CALLV(0x80B3492Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 396);
    R(25) = ld32(base, (f + 92));
    R(12) = ld32(base, (f + 96));
    R(4) = (R(31) + 19248);
    R(11) = ld32(base, (f + 100));
    R(5) = (R(27) + 384);
    R(10) = ld32(base, (f + 80));
    R(9) = ld32(base, (f + 84));
    R(8) = ld32(base, (f + 88));
    R(7) = ld32(base, (f + 68));
    R(6) = ld32(base, (f + 72));
    R(0) = ld32(base, (f + 76));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 396), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B3498Cu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 2516);
    R(4) = (R(28) + 2528);
    R(3) = (R(28) + 2540);
    R(11) = ld32(base, (R(28) + 2516));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 2844);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 2528));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 2540));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 32), R(11));
    st32(base, (f + 36), R(10));
    st32(base, (f + 40), R(9));
    st32(base, (f + 44), R(8));
    st32(base, (f + 48), R(7));
    st32(base, (f + 52), R(6));
    st32(base, (f + 56), R(5));
    st32(base, (f + 60), R(4));
    st32(base, (f + 64), R(0));
    GM_CALLV(0x80B349E8u, 0x80B34B90u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 460);
    GM_CALLV(0x80B349F8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 460);
    R(26) = ld32(base, (f + 56));
    R(12) = ld32(base, (f + 60));
    R(4) = (R(31) + 19248);
    R(11) = ld32(base, (f + 64));
    R(5) = (R(27) + 448);
    R(10) = ld32(base, (f + 44));
    R(9) = ld32(base, (f + 48));
    R(8) = ld32(base, (f + 52));
    R(7) = ld32(base, (f + 32));
    R(6) = ld32(base, (f + 36));
    R(0) = ld32(base, (f + 40));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 460), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B34A58u, 0x80B1CAC0u, 0);
    R(0) = ld8(base, (R(27) + 512));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B34AB4; }
    { uint32_t ea_ = (R(29) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(28) + 144);
    { uint32_t ea_ = (R(29) + 76); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(29) + 80); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 84); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 88); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 112); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 148); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 156); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(27) + 512), R(0));
L_80B34AB4:;
    R(11) = (f + 352);
    R(0) = lr;
}

/* fn_4_18140 (fn_4_18140, 12 bytes) */
static void eb_m_34b90(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -8548);
}

/* fn_4_18150 (fn_4_18150, 12 bytes) */
static void eb_m_34ba0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -8292);
}

/* fn_4_18160 (fn_4_18160, 12 bytes) */
static void eb_m_34bb0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -8356);
}

/* fn_4_18170 (fn_4_18170, 12 bytes) */
static void eb_m_34bc0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -7588);
}

/* fn_4_18180 (fn_4_18180, 12 bytes) */
static void eb_m_34bd0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -7652);
}

/* fn_4_18190 (fn_4_18190, 12 bytes) */
static void eb_m_34be0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -8164);
}

/* fn_4_181A0 (fn_4_181A0, 12 bytes) */
static void eb_m_34bf0(GM_CTX) {
    R(3) = (0 + 0x80B90000u);
    R(3) = (R(3) + -8228);
}

/* fn_4_181B0 (fn_4_181B0, 12 bytes) */
static void eb_m_34c00(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31036);
}

/* fn_4_18500 (fn_4_18500, 12 bytes) */
static void eb_m_34f50(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_18510 (fn_4_18510, 12 bytes) */
static void eb_m_34f60(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_18520 (fn_4_18520, 12 bytes) */
static void eb_m_34f70(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_18530 (fn_4_18530, 12 bytes) */
static void eb_m_34f80(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_18540 (fn_4_18540, 12 bytes) */
static void eb_m_34f90(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_1B1B0 (fn_4_1B1B0, 3964 bytes) */
static void eb_m_37c00(GM_CTX) {
    GM_FN(0x80B37C00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 768);
    R(31) = (0 + 0x80B80000u);
    R(6) = (0 + 0x80B70000u);
    R(31) = (R(31) + -18648);
    R(30) = (0 + 0x80B90000u);
    R(6) = (R(6) + 16968);
    R(11) = ld32(base, (R(31) + 2848));
    { uint32_t ea_ = (R(6) + 304); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (R(31) + 72);
    R(5) = (R(31) + 2848);
    { uint32_t ea_ = (R(6) + 512); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 388); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (R(31) + 2860);
    { uint32_t ea_ = (R(6) + 516); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = (R(31) + 2872);
    { uint32_t ea_ = (R(6) + 520); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(15) = (0 + 1190);
    R(10) = ld32(base, (R(5) + 4));
    R(17) = (R(31) + 816);
    R(9) = ld32(base, (R(5) + 8));
    R(16) = (0 + 1191);
    R(8) = ld32(base, (R(31) + 2860));
    R(18) = (0 + 1097);
    R(7) = ld32(base, (R(4) + 4));
    R(19) = (0 + 1193);
    R(6) = ld32(base, (R(4) + 8));
    R(20) = (0 + 1194);
    R(5) = ld32(base, (R(31) + 2872));
    R(21) = (0 + 1195);
    R(4) = ld32(base, (R(12) + 4));
    R(22) = (0 + 1176);
    R(0) = ld32(base, (R(12) + 8));
    R(23) = (0 + 1178);
    R(24) = (0 + 1182);
    R(25) = (0 + 1183);
    R(26) = (0 + 1184);
    R(27) = (0 + 1185);
    R(28) = (0 + 1186);
    R(12) = (0 + 1187);
    R(14) = (0 + 1188);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    R(30) = (R(30) + -19904);
    R(29) = (R(31) + 3496);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 816), R(15));
    st32(base, (R(17) + 8), R(16));
    st32(base, (R(17) + 16), R(18));
    st32(base, (R(17) + 24), R(19));
    st32(base, (R(17) + 32), R(20));
    st32(base, (R(17) + 40), R(21));
    st32(base, (R(17) + 48), R(22));
    st32(base, (R(17) + 56), R(23));
    st32(base, (R(17) + 64), R(24));
    st32(base, (R(17) + 72), R(25));
    st32(base, (R(17) + 80), R(26));
    st32(base, (R(17) + 88), R(27));
    st32(base, (R(17) + 96), R(28));
    st32(base, (R(17) + 104), R(12));
    st32(base, (R(17) + 112), R(14));
    st32(base, (f + 652), R(11));
    st32(base, (f + 656), R(10));
    st32(base, (f + 660), R(9));
    st32(base, (f + 664), R(8));
    st32(base, (f + 668), R(7));
    st32(base, (f + 672), R(6));
    st32(base, (f + 676), R(5));
    st32(base, (f + 680), R(4));
    st32(base, (f + 684), R(0));
    GM_CALLV(0x80B37D5Cu, 0x80B38D00u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(29) |R(29);
    R(3) = (R(30) + 12);
    GM_CALLV(0x80B37D6Cu, 0x8015F7C0u, 0);
    R(3) = (R(30) + 12);
    R(16) = ld32(base, (f + 676));
    R(12) = ld32(base, (f + 680));
    R(15) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 684));
    R(15) = (R(15) + -14488);
    R(10) = ld32(base, (f + 664));
    R(14) = (0 + 0x80B40000u);
    R(9) = ld32(base, (f + 668));
    R(4) = (R(14) + -29728);
    R(8) = ld32(base, (f + 672));
    R(5) = (R(30) + 0);
    R(7) = ld32(base, (f + 652));
    R(6) = ld32(base, (f + 656));
    R(0) = ld32(base, (f + 660));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 12), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B37DD8u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 2884);
    R(4) = (R(31) + 2896);
    R(3) = (R(31) + 2908);
    R(11) = ld32(base, (R(31) + 2884));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3528);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 2896));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 2908));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 616), R(11));
    st32(base, (f + 620), R(10));
    st32(base, (f + 624), R(9));
    st32(base, (f + 628), R(8));
    st32(base, (f + 632), R(7));
    st32(base, (f + 636), R(6));
    st32(base, (f + 640), R(5));
    st32(base, (f + 644), R(4));
    st32(base, (f + 648), R(0));
    GM_CALLV(0x80B37E34u, 0x80B38CF0u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 76);
    GM_CALLV(0x80B37E44u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 76);
    R(16) = ld32(base, (f + 640));
    R(12) = ld32(base, (f + 644));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 648));
    R(5) = (R(30) + 64);
    R(10) = ld32(base, (f + 628));
    R(9) = ld32(base, (f + 632));
    R(8) = ld32(base, (f + 636));
    R(7) = ld32(base, (f + 616));
    R(6) = ld32(base, (f + 620));
    R(0) = ld32(base, (f + 624));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 76), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B37EA4u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 2920);
    R(4) = (R(31) + 2932);
    R(3) = (R(31) + 2944);
    R(11) = ld32(base, (R(31) + 2920));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3560);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 2932));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 2944));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 580), R(11));
    st32(base, (f + 584), R(10));
    st32(base, (f + 588), R(9));
    st32(base, (f + 592), R(8));
    st32(base, (f + 596), R(7));
    st32(base, (f + 600), R(6));
    st32(base, (f + 604), R(5));
    st32(base, (f + 608), R(4));
    st32(base, (f + 612), R(0));
    GM_CALLV(0x80B37F00u, 0x80B38CE0u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 140);
    GM_CALLV(0x80B37F10u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 140);
    R(16) = ld32(base, (f + 604));
    R(12) = ld32(base, (f + 608));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 612));
    R(5) = (R(30) + 128);
    R(10) = ld32(base, (f + 592));
    R(9) = ld32(base, (f + 596));
    R(8) = ld32(base, (f + 600));
    R(7) = ld32(base, (f + 580));
    R(6) = ld32(base, (f + 584));
    R(0) = ld32(base, (f + 588));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 140), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B37F70u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 2956);
    R(4) = (R(31) + 2968);
    R(3) = (R(31) + 2980);
    R(11) = ld32(base, (R(31) + 2956));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3600);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 2968));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 2980));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 544), R(11));
    st32(base, (f + 548), R(10));
    st32(base, (f + 552), R(9));
    st32(base, (f + 556), R(8));
    st32(base, (f + 560), R(7));
    st32(base, (f + 564), R(6));
    st32(base, (f + 568), R(5));
    st32(base, (f + 572), R(4));
    st32(base, (f + 576), R(0));
    GM_CALLV(0x80B37FCCu, 0x80B38CD0u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 204);
    GM_CALLV(0x80B37FDCu, 0x8015F7C0u, 0);
    R(3) = (R(30) + 204);
    R(16) = ld32(base, (f + 568));
    R(12) = ld32(base, (f + 572));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 576));
    R(5) = (R(30) + 192);
    R(10) = ld32(base, (f + 556));
    R(9) = ld32(base, (f + 560));
    R(8) = ld32(base, (f + 564));
    R(7) = ld32(base, (f + 544));
    R(6) = ld32(base, (f + 548));
    R(0) = ld32(base, (f + 552));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 204), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B3803Cu, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 2992);
    R(4) = (R(31) + 3004);
    R(3) = (R(31) + 3016);
    R(11) = ld32(base, (R(31) + 2992));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3636);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3004));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3016));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 508), R(11));
    st32(base, (f + 512), R(10));
    st32(base, (f + 516), R(9));
    st32(base, (f + 520), R(8));
    st32(base, (f + 524), R(7));
    st32(base, (f + 528), R(6));
    st32(base, (f + 532), R(5));
    st32(base, (f + 536), R(4));
    st32(base, (f + 540), R(0));
    GM_CALLV(0x80B38098u, 0x80B34F50u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 268);
    GM_CALLV(0x80B380A8u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 268);
    R(16) = ld32(base, (f + 532));
    R(12) = ld32(base, (f + 536));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 540));
    R(5) = (R(30) + 256);
    R(10) = ld32(base, (f + 520));
    R(9) = ld32(base, (f + 524));
    R(8) = ld32(base, (f + 528));
    R(7) = ld32(base, (f + 508));
    R(6) = ld32(base, (f + 512));
    R(0) = ld32(base, (f + 516));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 268), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B38108u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3028);
    R(4) = (R(31) + 3040);
    R(3) = (R(31) + 3052);
    R(11) = ld32(base, (R(31) + 3028));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3672);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3040));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3052));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 472), R(11));
    st32(base, (f + 476), R(10));
    st32(base, (f + 480), R(9));
    st32(base, (f + 484), R(8));
    st32(base, (f + 488), R(7));
    st32(base, (f + 492), R(6));
    st32(base, (f + 496), R(5));
    st32(base, (f + 500), R(4));
    st32(base, (f + 504), R(0));
    GM_CALLV(0x80B38164u, 0x80B38CC0u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 332);
    GM_CALLV(0x80B38174u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 332);
    R(16) = ld32(base, (f + 496));
    R(12) = ld32(base, (f + 500));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 504));
    R(5) = (R(30) + 320);
    R(10) = ld32(base, (f + 484));
    R(9) = ld32(base, (f + 488));
    R(8) = ld32(base, (f + 492));
    R(7) = ld32(base, (f + 472));
    R(6) = ld32(base, (f + 476));
    R(0) = ld32(base, (f + 480));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 332), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B381D4u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3064);
    R(4) = (R(31) + 3076);
    R(3) = (R(31) + 3088);
    R(11) = ld32(base, (R(31) + 3064));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3704);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3076));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3088));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 436), R(11));
    st32(base, (f + 440), R(10));
    st32(base, (f + 444), R(9));
    st32(base, (f + 448), R(8));
    st32(base, (f + 452), R(7));
    st32(base, (f + 456), R(6));
    st32(base, (f + 460), R(5));
    st32(base, (f + 464), R(4));
    st32(base, (f + 468), R(0));
    GM_CALLV(0x80B38230u, 0x80B38CB0u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 396);
    GM_CALLV(0x80B38240u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 396);
    R(16) = ld32(base, (f + 460));
    R(12) = ld32(base, (f + 464));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 468));
    R(5) = (R(30) + 384);
    R(10) = ld32(base, (f + 448));
    R(9) = ld32(base, (f + 452));
    R(8) = ld32(base, (f + 456));
    R(7) = ld32(base, (f + 436));
    R(6) = ld32(base, (f + 440));
    R(0) = ld32(base, (f + 444));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 396), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B382A0u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3100);
    R(4) = (R(31) + 3112);
    R(3) = (R(31) + 3124);
    R(11) = ld32(base, (R(31) + 3100));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3736);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3112));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3124));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 400), R(11));
    st32(base, (f + 404), R(10));
    st32(base, (f + 408), R(9));
    st32(base, (f + 412), R(8));
    st32(base, (f + 416), R(7));
    st32(base, (f + 420), R(6));
    st32(base, (f + 424), R(5));
    st32(base, (f + 428), R(4));
    st32(base, (f + 432), R(0));
    GM_CALLV(0x80B382FCu, 0x80B38CA0u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 460);
    GM_CALLV(0x80B3830Cu, 0x8015F7C0u, 0);
    R(3) = (R(30) + 460);
    R(16) = ld32(base, (f + 424));
    R(12) = ld32(base, (f + 428));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 432));
    R(5) = (R(30) + 448);
    R(10) = ld32(base, (f + 412));
    R(9) = ld32(base, (f + 416));
    R(8) = ld32(base, (f + 420));
    R(7) = ld32(base, (f + 400));
    R(6) = ld32(base, (f + 404));
    R(0) = ld32(base, (f + 408));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 460), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B3836Cu, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3136);
    R(4) = (R(31) + 3148);
    R(3) = (R(31) + 3160);
    R(11) = ld32(base, (R(31) + 3136));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3776);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3148));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3160));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 364), R(11));
    st32(base, (f + 368), R(10));
    st32(base, (f + 372), R(9));
    st32(base, (f + 376), R(8));
    st32(base, (f + 380), R(7));
    st32(base, (f + 384), R(6));
    st32(base, (f + 388), R(5));
    st32(base, (f + 392), R(4));
    st32(base, (f + 396), R(0));
    GM_CALLV(0x80B383C8u, 0x80B38C90u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 524);
    GM_CALLV(0x80B383D8u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 524);
    R(16) = ld32(base, (f + 388));
    R(12) = ld32(base, (f + 392));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 396));
    R(5) = (R(30) + 512);
    R(10) = ld32(base, (f + 376));
    R(9) = ld32(base, (f + 380));
    R(8) = ld32(base, (f + 384));
    R(7) = ld32(base, (f + 364));
    R(6) = ld32(base, (f + 368));
    R(0) = ld32(base, (f + 372));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 524), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B38438u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3172);
    R(4) = (R(31) + 3184);
    R(3) = (R(31) + 3196);
    R(11) = ld32(base, (R(31) + 3172));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3808);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3184));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3196));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 328), R(11));
    st32(base, (f + 332), R(10));
    st32(base, (f + 336), R(9));
    st32(base, (f + 340), R(8));
    st32(base, (f + 344), R(7));
    st32(base, (f + 348), R(6));
    st32(base, (f + 352), R(5));
    st32(base, (f + 356), R(4));
    st32(base, (f + 360), R(0));
    GM_CALLV(0x80B38494u, 0x80B38C80u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 588);
    GM_CALLV(0x80B384A4u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 588);
    R(16) = ld32(base, (f + 352));
    R(12) = ld32(base, (f + 356));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 360));
    R(5) = (R(30) + 576);
    R(10) = ld32(base, (f + 340));
    R(9) = ld32(base, (f + 344));
    R(8) = ld32(base, (f + 348));
    R(7) = ld32(base, (f + 328));
    R(6) = ld32(base, (f + 332));
    R(0) = ld32(base, (f + 336));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 588), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B38504u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3208);
    R(4) = (R(31) + 3220);
    R(3) = (R(31) + 3232);
    R(11) = ld32(base, (R(31) + 3208));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3844);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3220));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3232));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 292), R(11));
    st32(base, (f + 296), R(10));
    st32(base, (f + 300), R(9));
    st32(base, (f + 304), R(8));
    st32(base, (f + 308), R(7));
    st32(base, (f + 312), R(6));
    st32(base, (f + 316), R(5));
    st32(base, (f + 320), R(4));
    st32(base, (f + 324), R(0));
    GM_CALLV(0x80B38560u, 0x80B38C70u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 652);
    GM_CALLV(0x80B38570u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 652);
    R(16) = ld32(base, (f + 316));
    R(12) = ld32(base, (f + 320));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 324));
    R(5) = (R(30) + 640);
    R(10) = ld32(base, (f + 304));
    R(9) = ld32(base, (f + 308));
    R(8) = ld32(base, (f + 312));
    R(7) = ld32(base, (f + 292));
    R(6) = ld32(base, (f + 296));
    R(0) = ld32(base, (f + 300));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 652), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B385D0u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3244);
    R(4) = (R(31) + 3256);
    R(3) = (R(31) + 3268);
    R(11) = ld32(base, (R(31) + 3244));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3884);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3256));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3268));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 256), R(11));
    st32(base, (f + 260), R(10));
    st32(base, (f + 264), R(9));
    st32(base, (f + 268), R(8));
    st32(base, (f + 272), R(7));
    st32(base, (f + 276), R(6));
    st32(base, (f + 280), R(5));
    st32(base, (f + 284), R(4));
    st32(base, (f + 288), R(0));
    GM_CALLV(0x80B3862Cu, 0x80B38C60u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 716);
    GM_CALLV(0x80B3863Cu, 0x8015F7C0u, 0);
    R(3) = (R(30) + 716);
    R(16) = ld32(base, (f + 280));
    R(12) = ld32(base, (f + 284));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 288));
    R(5) = (R(30) + 704);
    R(10) = ld32(base, (f + 268));
    R(9) = ld32(base, (f + 272));
    R(8) = ld32(base, (f + 276));
    R(7) = ld32(base, (f + 256));
    R(6) = ld32(base, (f + 260));
    R(0) = ld32(base, (f + 264));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 716), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B3869Cu, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3280);
    R(4) = (R(31) + 3292);
    R(3) = (R(31) + 3304);
    R(11) = ld32(base, (R(31) + 3280));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3920);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3292));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3304));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 220), R(11));
    st32(base, (f + 224), R(10));
    st32(base, (f + 228), R(9));
    st32(base, (f + 232), R(8));
    st32(base, (f + 236), R(7));
    st32(base, (f + 240), R(6));
    st32(base, (f + 244), R(5));
    st32(base, (f + 248), R(4));
    st32(base, (f + 252), R(0));
    GM_CALLV(0x80B386F8u, 0x80B38C50u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 780);
    GM_CALLV(0x80B38708u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 780);
    R(16) = ld32(base, (f + 244));
    R(12) = ld32(base, (f + 248));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 252));
    R(5) = (R(30) + 768);
    R(10) = ld32(base, (f + 232));
    R(9) = ld32(base, (f + 236));
    R(8) = ld32(base, (f + 240));
    R(7) = ld32(base, (f + 220));
    R(6) = ld32(base, (f + 224));
    R(0) = ld32(base, (f + 228));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 780), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B38768u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3316);
    R(4) = (R(31) + 3328);
    R(3) = (R(31) + 3340);
    R(11) = ld32(base, (R(31) + 3316));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3960);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3328));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3340));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 184), R(11));
    st32(base, (f + 188), R(10));
    st32(base, (f + 192), R(9));
    st32(base, (f + 196), R(8));
    st32(base, (f + 200), R(7));
    st32(base, (f + 204), R(6));
    st32(base, (f + 208), R(5));
    st32(base, (f + 212), R(4));
    st32(base, (f + 216), R(0));
    GM_CALLV(0x80B387C4u, 0x80B34F60u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 844);
    GM_CALLV(0x80B387D4u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 844);
    R(16) = ld32(base, (f + 208));
    R(12) = ld32(base, (f + 212));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 216));
    R(5) = (R(30) + 832);
    R(10) = ld32(base, (f + 196));
    R(9) = ld32(base, (f + 200));
    R(8) = ld32(base, (f + 204));
    R(7) = ld32(base, (f + 184));
    R(6) = ld32(base, (f + 188));
    R(0) = ld32(base, (f + 192));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 844), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B38834u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3352);
    R(4) = (R(31) + 3364);
    R(3) = (R(31) + 3376);
    R(11) = ld32(base, (R(31) + 3352));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 3996);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3364));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3376));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 148), R(11));
    st32(base, (f + 152), R(10));
    st32(base, (f + 156), R(9));
    st32(base, (f + 160), R(8));
    st32(base, (f + 164), R(7));
    st32(base, (f + 168), R(6));
    st32(base, (f + 172), R(5));
    st32(base, (f + 176), R(4));
    st32(base, (f + 180), R(0));
    GM_CALLV(0x80B38890u, 0x80B34F70u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 908);
    GM_CALLV(0x80B388A0u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 908);
    R(16) = ld32(base, (f + 172));
    R(12) = ld32(base, (f + 176));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 180));
    R(5) = (R(30) + 896);
    R(10) = ld32(base, (f + 160));
    R(9) = ld32(base, (f + 164));
    R(8) = ld32(base, (f + 168));
    R(7) = ld32(base, (f + 148));
    R(6) = ld32(base, (f + 152));
    R(0) = ld32(base, (f + 156));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 908), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B38900u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3388);
    R(4) = (R(31) + 3400);
    R(3) = (R(31) + 3412);
    R(11) = ld32(base, (R(31) + 3388));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 4032);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3400));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3412));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 112), R(11));
    st32(base, (f + 116), R(10));
    st32(base, (f + 120), R(9));
    st32(base, (f + 124), R(8));
    st32(base, (f + 128), R(7));
    st32(base, (f + 132), R(6));
    st32(base, (f + 136), R(5));
    st32(base, (f + 140), R(4));
    st32(base, (f + 144), R(0));
    GM_CALLV(0x80B3895Cu, 0x80B38C40u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 972);
    GM_CALLV(0x80B3896Cu, 0x8015F7C0u, 0);
    R(3) = (R(30) + 972);
    R(16) = ld32(base, (f + 136));
    R(12) = ld32(base, (f + 140));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 144));
    R(5) = (R(30) + 960);
    R(10) = ld32(base, (f + 124));
    R(9) = ld32(base, (f + 128));
    R(8) = ld32(base, (f + 132));
    R(7) = ld32(base, (f + 112));
    R(6) = ld32(base, (f + 116));
    R(0) = ld32(base, (f + 120));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 972), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B389CCu, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3424);
    R(4) = (R(31) + 3436);
    R(3) = (R(31) + 3448);
    R(11) = ld32(base, (R(31) + 3424));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 4072);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3436));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3448));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 76), R(11));
    st32(base, (f + 80), R(10));
    st32(base, (f + 84), R(9));
    st32(base, (f + 88), R(8));
    st32(base, (f + 92), R(7));
    st32(base, (f + 96), R(6));
    st32(base, (f + 100), R(5));
    st32(base, (f + 104), R(4));
    st32(base, (f + 108), R(0));
    GM_CALLV(0x80B38A28u, 0x80B34F80u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 1036);
    GM_CALLV(0x80B38A38u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 1036);
    R(16) = ld32(base, (f + 100));
    R(12) = ld32(base, (f + 104));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 108));
    R(5) = (R(30) + 1024);
    R(10) = ld32(base, (f + 88));
    R(9) = ld32(base, (f + 92));
    R(8) = ld32(base, (f + 96));
    R(7) = ld32(base, (f + 76));
    R(6) = ld32(base, (f + 80));
    R(0) = ld32(base, (f + 84));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 1036), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B38A98u, 0x80B1CAC0u, 0);
    R(5) = (R(31) + 3460);
    R(4) = (R(31) + 3472);
    R(3) = (R(31) + 3484);
    R(11) = ld32(base, (R(31) + 3460));
    R(10) = ld32(base, (R(5) + 4));
    R(16) = (R(31) + 4120);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(31) + 3472));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(31) + 3484));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 40), R(11));
    st32(base, (f + 44), R(10));
    st32(base, (f + 48), R(9));
    st32(base, (f + 52), R(8));
    st32(base, (f + 56), R(7));
    st32(base, (f + 60), R(6));
    st32(base, (f + 64), R(5));
    st32(base, (f + 68), R(4));
    st32(base, (f + 72), R(0));
    GM_CALLV(0x80B38AF4u, 0x80B34F90u, 0);
    R(17) = R(3) |R(3);
    R(4) = R(16) |R(16);
    R(3) = (R(30) + 1100);
    GM_CALLV(0x80B38B04u, 0x8015F7C0u, 0);
    R(3) = (R(30) + 1100);
    R(16) = ld32(base, (f + 64));
    R(12) = ld32(base, (f + 68));
    R(4) = (R(14) + -29728);
    R(11) = ld32(base, (f + 72));
    R(5) = (R(30) + 1088);
    R(10) = ld32(base, (f + 52));
    R(9) = ld32(base, (f + 56));
    R(8) = ld32(base, (f + 60));
    R(7) = ld32(base, (f + 40));
    R(6) = ld32(base, (f + 44));
    R(0) = ld32(base, (f + 48));
    st32(base, (R(3) + 12), R(16));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(30) + 1100), R(15));
    st32(base, (R(3) + 48), R(17));
    GM_CALLV(0x80B38B64u, 0x80B1CAC0u, 0);
    R(11) = (f + 768);
    R(0) = lr;
}

/* fn_4_1C1F0 (fn_4_1C1F0, 12 bytes) */
static void eb_m_38c40(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30716);
}

/* fn_4_1C200 (fn_4_1C200, 12 bytes) */
static void eb_m_38c50(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30780);
}

/* fn_4_1C210 (fn_4_1C210, 12 bytes) */
static void eb_m_38c60(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30844);
}

/* fn_4_1C220 (fn_4_1C220, 12 bytes) */
static void eb_m_38c70(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30908);
}

/* fn_4_1C230 (fn_4_1C230, 12 bytes) */
static void eb_m_38c80(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_1C240 (fn_4_1C240, 12 bytes) */
static void eb_m_38c90(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32252);
}

/* fn_4_1C250 (fn_4_1C250, 12 bytes) */
static void eb_m_38ca0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32316);
}

/* fn_4_1C260 (fn_4_1C260, 12 bytes) */
static void eb_m_38cb0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32380);
}

/* fn_4_1C270 (fn_4_1C270, 12 bytes) */
static void eb_m_38cc0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32444);
}

/* fn_4_1C280 (fn_4_1C280, 12 bytes) */
static void eb_m_38cd0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31356);
}

/* fn_4_1C290 (fn_4_1C290, 12 bytes) */
static void eb_m_38ce0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31996);
}

/* fn_4_1C2A0 (fn_4_1C2A0, 12 bytes) */
static void eb_m_38cf0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31932);
}

/* fn_4_1C2B0 (fn_4_1C2B0, 12 bytes) */
static void eb_m_38d00(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_1C5D0 (fn_4_1C5D0, 12 bytes) */
static void eb_m_39020(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_1C5E0 (fn_4_1C5E0, 12 bytes) */
static void eb_m_39030(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_1C5F0 (fn_4_1C5F0, 12 bytes) */
static void eb_m_39040(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_1C600 (fn_4_1C600, 12 bytes) */
static void eb_m_39050(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_1C610 (fn_4_1C610, 12 bytes) */
static void eb_m_39060(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_1C620 (fn_4_1C620, 12 bytes) */
static void eb_m_39070(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_1C630 (fn_4_1C630, 12 bytes) */
static void eb_m_39080(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_1C640 (fn_4_1C640, 12 bytes) */
static void eb_m_39090(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_1FA40 (fn_4_1FA40, 5612 bytes) */
static void eb_m_3c490(GM_CTX) {
    GM_FN(0x80B3C490); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 1056);
    R(29) = (0 + 0x80B80000u);
    R(27) = (0 + 0x80B90000u);
    R(29) = (R(29) + -14384);
    R(28) = (0 + 0x80B70000u);
    R(5) = (R(29) + 2848);
    R(27) = (R(27) + -18752);
    R(4) = (R(29) + 2860);
    R(3) = (R(29) + 2872);
    R(11) = ld32(base, (R(29) + 2848));
    R(26) = (0 + 1097);
    R(25) = (R(27) + 16);
    R(10) = ld32(base, (R(5) + 4));
    R(9) = ld32(base, (R(5) + 8));
    R(24) = (0 + 1243);
    R(8) = ld32(base, (R(29) + 2860));
    R(12) = (0 + 1245);
    R(7) = ld32(base, (R(4) + 4));
    R(28) = (R(28) + 17664);
    R(6) = ld32(base, (R(4) + 8));
    R(30) = (R(29) + 3712);
    R(5) = ld32(base, (R(29) + 2872));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (R(27) + 16), R(26));
    st32(base, (R(25) + 8), R(26));
    st32(base, (R(25) + 16), R(26));
    st32(base, (R(25) + 24), R(26));
    st32(base, (R(25) + 32), R(26));
    st32(base, (R(25) + 40), R(26));
    st32(base, (R(25) + 48), R(26));
    st32(base, (R(25) + 56), R(26));
    st32(base, (R(25) + 64), R(26));
    st32(base, (R(25) + 72), R(24));
    st32(base, (R(25) + 80), R(12));
    st32(base, (R(25) + 88), R(26));
    st32(base, (R(25) + 96), R(26));
    st32(base, (R(25) + 104), R(26));
    st32(base, (R(25) + 112), R(26));
    st32(base, (f + 976), R(11));
    st32(base, (f + 980), R(10));
    st32(base, (f + 984), R(9));
    st32(base, (f + 988), R(8));
    st32(base, (f + 992), R(7));
    st32(base, (f + 996), R(6));
    st32(base, (f + 1000), R(5));
    st32(base, (f + 1004), R(4));
    st32(base, (f + 1008), R(0));
    GM_CALLV(0x80B3C5B4u, 0x80B3DC30u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(30) |R(30);
    R(3) = (R(27) + 148);
    GM_CALLV(0x80B3C5C4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 148);
    R(24) = ld32(base, (f + 1000));
    R(12) = ld32(base, (f + 1004));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 1008));
    R(30) = (R(30) + -9760);
    R(10) = ld32(base, (f + 988));
    R(31) = (0 + 0x80B40000u);
    R(9) = ld32(base, (f + 992));
    R(4) = (R(31) + -9504);
    R(8) = ld32(base, (f + 996));
    R(5) = (R(27) + 136);
    R(7) = ld32(base, (f + 976));
    R(6) = ld32(base, (f + 980));
    R(0) = ld32(base, (f + 984));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 148), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3C630u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 2884);
    R(4) = (R(29) + 2896);
    R(3) = (R(29) + 2908);
    R(11) = ld32(base, (R(29) + 2884));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 3748);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 2896));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 2908));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 940), R(11));
    st32(base, (f + 944), R(10));
    st32(base, (f + 948), R(9));
    st32(base, (f + 952), R(8));
    st32(base, (f + 956), R(7));
    st32(base, (f + 960), R(6));
    st32(base, (f + 964), R(5));
    st32(base, (f + 968), R(4));
    st32(base, (f + 972), R(0));
    GM_CALLV(0x80B3C68Cu, 0x80B3DC20u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 212);
    GM_CALLV(0x80B3C69Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 212);
    R(24) = ld32(base, (f + 964));
    R(12) = ld32(base, (f + 968));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 972));
    R(5) = (R(27) + 200);
    R(10) = ld32(base, (f + 952));
    R(9) = ld32(base, (f + 956));
    R(8) = ld32(base, (f + 960));
    R(7) = ld32(base, (f + 940));
    R(6) = ld32(base, (f + 944));
    R(0) = ld32(base, (f + 948));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 212), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3C6FCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 2920);
    R(4) = (R(29) + 2932);
    R(3) = (R(29) + 2944);
    R(11) = ld32(base, (R(29) + 2920));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 3784);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 2932));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 2944));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 904), R(11));
    st32(base, (f + 908), R(10));
    st32(base, (f + 912), R(9));
    st32(base, (f + 916), R(8));
    st32(base, (f + 920), R(7));
    st32(base, (f + 924), R(6));
    st32(base, (f + 928), R(5));
    st32(base, (f + 932), R(4));
    st32(base, (f + 936), R(0));
    GM_CALLV(0x80B3C758u, 0x80B3DC10u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 276);
    GM_CALLV(0x80B3C768u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 276);
    R(24) = ld32(base, (f + 928));
    R(12) = ld32(base, (f + 932));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 936));
    R(5) = (R(27) + 264);
    R(10) = ld32(base, (f + 916));
    R(9) = ld32(base, (f + 920));
    R(8) = ld32(base, (f + 924));
    R(7) = ld32(base, (f + 904));
    R(6) = ld32(base, (f + 908));
    R(0) = ld32(base, (f + 912));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 276), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3C7C8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 2956);
    R(4) = (R(29) + 2968);
    R(3) = (R(29) + 2980);
    R(11) = ld32(base, (R(29) + 2956));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 3828);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 2968));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 2980));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 868), R(11));
    st32(base, (f + 872), R(10));
    st32(base, (f + 876), R(9));
    st32(base, (f + 880), R(8));
    st32(base, (f + 884), R(7));
    st32(base, (f + 888), R(6));
    st32(base, (f + 892), R(5));
    st32(base, (f + 896), R(4));
    st32(base, (f + 900), R(0));
    GM_CALLV(0x80B3C824u, 0x80B39020u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 340);
    GM_CALLV(0x80B3C834u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 340);
    R(24) = ld32(base, (f + 892));
    R(12) = ld32(base, (f + 896));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 900));
    R(5) = (R(27) + 328);
    R(10) = ld32(base, (f + 880));
    R(9) = ld32(base, (f + 884));
    R(8) = ld32(base, (f + 888));
    R(7) = ld32(base, (f + 868));
    R(6) = ld32(base, (f + 872));
    R(0) = ld32(base, (f + 876));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 340), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3C894u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 2992);
    R(4) = (R(29) + 3004);
    R(3) = (R(29) + 3016);
    R(11) = ld32(base, (R(29) + 2992));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 3868);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3004));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3016));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 832), R(11));
    st32(base, (f + 836), R(10));
    st32(base, (f + 840), R(9));
    st32(base, (f + 844), R(8));
    st32(base, (f + 848), R(7));
    st32(base, (f + 852), R(6));
    st32(base, (f + 856), R(5));
    st32(base, (f + 860), R(4));
    st32(base, (f + 864), R(0));
    GM_CALLV(0x80B3C8F0u, 0x80B39030u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 404);
    GM_CALLV(0x80B3C900u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 404);
    R(24) = ld32(base, (f + 856));
    R(12) = ld32(base, (f + 860));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 864));
    R(5) = (R(27) + 392);
    R(10) = ld32(base, (f + 844));
    R(9) = ld32(base, (f + 848));
    R(8) = ld32(base, (f + 852));
    R(7) = ld32(base, (f + 832));
    R(6) = ld32(base, (f + 836));
    R(0) = ld32(base, (f + 840));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 404), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3C960u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3028);
    R(4) = (R(29) + 3040);
    R(3) = (R(29) + 3052);
    R(11) = ld32(base, (R(29) + 3028));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 3904);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3040));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3052));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 796), R(11));
    st32(base, (f + 800), R(10));
    st32(base, (f + 804), R(9));
    st32(base, (f + 808), R(8));
    st32(base, (f + 812), R(7));
    st32(base, (f + 816), R(6));
    st32(base, (f + 820), R(5));
    st32(base, (f + 824), R(4));
    st32(base, (f + 828), R(0));
    GM_CALLV(0x80B3C9BCu, 0x80B39040u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 468);
    GM_CALLV(0x80B3C9CCu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 468);
    R(24) = ld32(base, (f + 820));
    R(12) = ld32(base, (f + 824));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 828));
    R(5) = (R(27) + 456);
    R(10) = ld32(base, (f + 808));
    R(9) = ld32(base, (f + 812));
    R(8) = ld32(base, (f + 816));
    R(7) = ld32(base, (f + 796));
    R(6) = ld32(base, (f + 800));
    R(0) = ld32(base, (f + 804));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 468), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3CA2Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3064);
    R(4) = (R(29) + 3076);
    R(3) = (R(29) + 3088);
    R(11) = ld32(base, (R(29) + 3064));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 3940);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3076));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3088));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 760), R(11));
    st32(base, (f + 764), R(10));
    st32(base, (f + 768), R(9));
    st32(base, (f + 772), R(8));
    st32(base, (f + 776), R(7));
    st32(base, (f + 780), R(6));
    st32(base, (f + 784), R(5));
    st32(base, (f + 788), R(4));
    st32(base, (f + 792), R(0));
    GM_CALLV(0x80B3CA88u, 0x80B39050u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 532);
    GM_CALLV(0x80B3CA98u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 532);
    R(24) = ld32(base, (f + 784));
    R(12) = ld32(base, (f + 788));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 792));
    R(5) = (R(27) + 520);
    R(10) = ld32(base, (f + 772));
    R(9) = ld32(base, (f + 776));
    R(8) = ld32(base, (f + 780));
    R(7) = ld32(base, (f + 760));
    R(6) = ld32(base, (f + 764));
    R(0) = ld32(base, (f + 768));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 532), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3CAF8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3100);
    R(4) = (R(29) + 3112);
    R(3) = (R(29) + 3124);
    R(11) = ld32(base, (R(29) + 3100));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 3976);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3112));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3124));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 724), R(11));
    st32(base, (f + 728), R(10));
    st32(base, (f + 732), R(9));
    st32(base, (f + 736), R(8));
    st32(base, (f + 740), R(7));
    st32(base, (f + 744), R(6));
    st32(base, (f + 748), R(5));
    st32(base, (f + 752), R(4));
    st32(base, (f + 756), R(0));
    GM_CALLV(0x80B3CB54u, 0x80B3DC00u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 596);
    GM_CALLV(0x80B3CB64u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 596);
    R(24) = ld32(base, (f + 748));
    R(12) = ld32(base, (f + 752));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 756));
    R(5) = (R(27) + 584);
    R(10) = ld32(base, (f + 736));
    R(9) = ld32(base, (f + 740));
    R(8) = ld32(base, (f + 744));
    R(7) = ld32(base, (f + 724));
    R(6) = ld32(base, (f + 728));
    R(0) = ld32(base, (f + 732));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 596), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3CBC4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3136);
    R(4) = (R(29) + 3148);
    R(3) = (R(29) + 3160);
    R(11) = ld32(base, (R(29) + 3136));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4016);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3148));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3160));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 688), R(11));
    st32(base, (f + 692), R(10));
    st32(base, (f + 696), R(9));
    st32(base, (f + 700), R(8));
    st32(base, (f + 704), R(7));
    st32(base, (f + 708), R(6));
    st32(base, (f + 712), R(5));
    st32(base, (f + 716), R(4));
    st32(base, (f + 720), R(0));
    GM_CALLV(0x80B3CC20u, 0x80B3DBF0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 660);
    GM_CALLV(0x80B3CC30u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 660);
    R(24) = ld32(base, (f + 712));
    R(12) = ld32(base, (f + 716));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 720));
    R(5) = (R(27) + 648);
    R(10) = ld32(base, (f + 700));
    R(9) = ld32(base, (f + 704));
    R(8) = ld32(base, (f + 708));
    R(7) = ld32(base, (f + 688));
    R(6) = ld32(base, (f + 692));
    R(0) = ld32(base, (f + 696));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 660), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3CC90u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3172);
    R(4) = (R(29) + 3184);
    R(3) = (R(29) + 3196);
    R(11) = ld32(base, (R(29) + 3172));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4052);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3184));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3196));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 652), R(11));
    st32(base, (f + 656), R(10));
    st32(base, (f + 660), R(9));
    st32(base, (f + 664), R(8));
    st32(base, (f + 668), R(7));
    st32(base, (f + 672), R(6));
    st32(base, (f + 676), R(5));
    st32(base, (f + 680), R(4));
    st32(base, (f + 684), R(0));
    GM_CALLV(0x80B3CCECu, 0x80B3DBE0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 724);
    GM_CALLV(0x80B3CCFCu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 724);
    R(24) = ld32(base, (f + 676));
    R(12) = ld32(base, (f + 680));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 684));
    R(5) = (R(27) + 712);
    R(10) = ld32(base, (f + 664));
    R(9) = ld32(base, (f + 668));
    R(8) = ld32(base, (f + 672));
    R(7) = ld32(base, (f + 652));
    R(6) = ld32(base, (f + 656));
    R(0) = ld32(base, (f + 660));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 724), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3CD5Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3208);
    R(4) = (R(29) + 3220);
    R(3) = (R(29) + 3232);
    R(11) = ld32(base, (R(29) + 3208));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4088);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3220));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3232));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 616), R(11));
    st32(base, (f + 620), R(10));
    st32(base, (f + 624), R(9));
    st32(base, (f + 628), R(8));
    st32(base, (f + 632), R(7));
    st32(base, (f + 636), R(6));
    st32(base, (f + 640), R(5));
    st32(base, (f + 644), R(4));
    st32(base, (f + 648), R(0));
    GM_CALLV(0x80B3CDB8u, 0x80B3DBD0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 788);
    GM_CALLV(0x80B3CDC8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 788);
    R(24) = ld32(base, (f + 640));
    R(12) = ld32(base, (f + 644));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 648));
    R(5) = (R(27) + 776);
    R(10) = ld32(base, (f + 628));
    R(9) = ld32(base, (f + 632));
    R(8) = ld32(base, (f + 636));
    R(7) = ld32(base, (f + 616));
    R(6) = ld32(base, (f + 620));
    R(0) = ld32(base, (f + 624));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 788), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3CE28u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3244);
    R(4) = (R(29) + 3256);
    R(3) = (R(29) + 3268);
    R(11) = ld32(base, (R(29) + 3244));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4124);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3256));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3268));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 580), R(11));
    st32(base, (f + 584), R(10));
    st32(base, (f + 588), R(9));
    st32(base, (f + 592), R(8));
    st32(base, (f + 596), R(7));
    st32(base, (f + 600), R(6));
    st32(base, (f + 604), R(5));
    st32(base, (f + 608), R(4));
    st32(base, (f + 612), R(0));
    GM_CALLV(0x80B3CE84u, 0x80B3DBC0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 852);
    GM_CALLV(0x80B3CE94u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 852);
    R(24) = ld32(base, (f + 604));
    R(12) = ld32(base, (f + 608));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 612));
    R(5) = (R(27) + 840);
    R(10) = ld32(base, (f + 592));
    R(9) = ld32(base, (f + 596));
    R(8) = ld32(base, (f + 600));
    R(7) = ld32(base, (f + 580));
    R(6) = ld32(base, (f + 584));
    R(0) = ld32(base, (f + 588));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 852), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3CEF4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3280);
    R(4) = (R(29) + 3292);
    R(3) = (R(29) + 3304);
    R(11) = ld32(base, (R(29) + 3280));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4160);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3292));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3304));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 544), R(11));
    st32(base, (f + 548), R(10));
    st32(base, (f + 552), R(9));
    st32(base, (f + 556), R(8));
    st32(base, (f + 560), R(7));
    st32(base, (f + 564), R(6));
    st32(base, (f + 568), R(5));
    st32(base, (f + 572), R(4));
    st32(base, (f + 576), R(0));
    GM_CALLV(0x80B3CF50u, 0x80B3DBB0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 916);
    GM_CALLV(0x80B3CF60u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 916);
    R(24) = ld32(base, (f + 568));
    R(12) = ld32(base, (f + 572));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 576));
    R(5) = (R(27) + 904);
    R(10) = ld32(base, (f + 556));
    R(9) = ld32(base, (f + 560));
    R(8) = ld32(base, (f + 564));
    R(7) = ld32(base, (f + 544));
    R(6) = ld32(base, (f + 548));
    R(0) = ld32(base, (f + 552));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 916), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3CFC0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3316);
    R(4) = (R(29) + 3328);
    R(3) = (R(29) + 3340);
    R(11) = ld32(base, (R(29) + 3316));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4196);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3328));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3340));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 508), R(11));
    st32(base, (f + 512), R(10));
    st32(base, (f + 516), R(9));
    st32(base, (f + 520), R(8));
    st32(base, (f + 524), R(7));
    st32(base, (f + 528), R(6));
    st32(base, (f + 532), R(5));
    st32(base, (f + 536), R(4));
    st32(base, (f + 540), R(0));
    GM_CALLV(0x80B3D01Cu, 0x80B3DBA0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 980);
    GM_CALLV(0x80B3D02Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 980);
    R(24) = ld32(base, (f + 532));
    R(12) = ld32(base, (f + 536));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 540));
    R(5) = (R(27) + 968);
    R(10) = ld32(base, (f + 520));
    R(9) = ld32(base, (f + 524));
    R(8) = ld32(base, (f + 528));
    R(7) = ld32(base, (f + 508));
    R(6) = ld32(base, (f + 512));
    R(0) = ld32(base, (f + 516));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 980), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D08Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3352);
    R(4) = (R(29) + 3364);
    R(3) = (R(29) + 3376);
    R(11) = ld32(base, (R(29) + 3352));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4232);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3364));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3376));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 472), R(11));
    st32(base, (f + 476), R(10));
    st32(base, (f + 480), R(9));
    st32(base, (f + 484), R(8));
    st32(base, (f + 488), R(7));
    st32(base, (f + 492), R(6));
    st32(base, (f + 496), R(5));
    st32(base, (f + 500), R(4));
    st32(base, (f + 504), R(0));
    GM_CALLV(0x80B3D0E8u, 0x80B3DB90u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1044);
    GM_CALLV(0x80B3D0F8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1044);
    R(24) = ld32(base, (f + 496));
    R(12) = ld32(base, (f + 500));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 504));
    R(5) = (R(27) + 1032);
    R(10) = ld32(base, (f + 484));
    R(9) = ld32(base, (f + 488));
    R(8) = ld32(base, (f + 492));
    R(7) = ld32(base, (f + 472));
    R(6) = ld32(base, (f + 476));
    R(0) = ld32(base, (f + 480));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1044), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D158u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3388);
    R(4) = (R(29) + 3400);
    R(3) = (R(29) + 3412);
    R(11) = ld32(base, (R(29) + 3388));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4268);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3400));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3412));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 436), R(11));
    st32(base, (f + 440), R(10));
    st32(base, (f + 444), R(9));
    st32(base, (f + 448), R(8));
    st32(base, (f + 452), R(7));
    st32(base, (f + 456), R(6));
    st32(base, (f + 460), R(5));
    st32(base, (f + 464), R(4));
    st32(base, (f + 468), R(0));
    GM_CALLV(0x80B3D1B4u, 0x80B3DB80u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1108);
    GM_CALLV(0x80B3D1C4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1108);
    R(24) = ld32(base, (f + 460));
    R(12) = ld32(base, (f + 464));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 468));
    R(5) = (R(27) + 1096);
    R(10) = ld32(base, (f + 448));
    R(9) = ld32(base, (f + 452));
    R(8) = ld32(base, (f + 456));
    R(7) = ld32(base, (f + 436));
    R(6) = ld32(base, (f + 440));
    R(0) = ld32(base, (f + 444));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1108), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D224u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3424);
    R(4) = (R(29) + 3436);
    R(3) = (R(29) + 3448);
    R(11) = ld32(base, (R(29) + 3424));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4304);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3436));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3448));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 400), R(11));
    st32(base, (f + 404), R(10));
    st32(base, (f + 408), R(9));
    st32(base, (f + 412), R(8));
    st32(base, (f + 416), R(7));
    st32(base, (f + 420), R(6));
    st32(base, (f + 424), R(5));
    st32(base, (f + 428), R(4));
    st32(base, (f + 432), R(0));
    GM_CALLV(0x80B3D280u, 0x80B3DB70u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1172);
    GM_CALLV(0x80B3D290u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1172);
    R(24) = ld32(base, (f + 424));
    R(12) = ld32(base, (f + 428));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 432));
    R(5) = (R(27) + 1160);
    R(10) = ld32(base, (f + 412));
    R(9) = ld32(base, (f + 416));
    R(8) = ld32(base, (f + 420));
    R(7) = ld32(base, (f + 400));
    R(6) = ld32(base, (f + 404));
    R(0) = ld32(base, (f + 408));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1172), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D2F0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3460);
    R(4) = (R(29) + 3472);
    R(3) = (R(29) + 3484);
    R(11) = ld32(base, (R(29) + 3460));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4340);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3472));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3484));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 364), R(11));
    st32(base, (f + 368), R(10));
    st32(base, (f + 372), R(9));
    st32(base, (f + 376), R(8));
    st32(base, (f + 380), R(7));
    st32(base, (f + 384), R(6));
    st32(base, (f + 388), R(5));
    st32(base, (f + 392), R(4));
    st32(base, (f + 396), R(0));
    GM_CALLV(0x80B3D34Cu, 0x80B3DB60u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1236);
    GM_CALLV(0x80B3D35Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1236);
    R(24) = ld32(base, (f + 388));
    R(12) = ld32(base, (f + 392));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 396));
    R(5) = (R(27) + 1224);
    R(10) = ld32(base, (f + 376));
    R(9) = ld32(base, (f + 380));
    R(8) = ld32(base, (f + 384));
    R(7) = ld32(base, (f + 364));
    R(6) = ld32(base, (f + 368));
    R(0) = ld32(base, (f + 372));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1236), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D3BCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3496);
    R(4) = (R(29) + 3508);
    R(3) = (R(29) + 3520);
    R(11) = ld32(base, (R(29) + 3496));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4380);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3508));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3520));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 328), R(11));
    st32(base, (f + 332), R(10));
    st32(base, (f + 336), R(9));
    st32(base, (f + 340), R(8));
    st32(base, (f + 344), R(7));
    st32(base, (f + 348), R(6));
    st32(base, (f + 352), R(5));
    st32(base, (f + 356), R(4));
    st32(base, (f + 360), R(0));
    GM_CALLV(0x80B3D418u, 0x80B3DB50u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1300);
    GM_CALLV(0x80B3D428u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1300);
    R(24) = ld32(base, (f + 352));
    R(12) = ld32(base, (f + 356));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 360));
    R(5) = (R(27) + 1288);
    R(10) = ld32(base, (f + 340));
    R(9) = ld32(base, (f + 344));
    R(8) = ld32(base, (f + 348));
    R(7) = ld32(base, (f + 328));
    R(6) = ld32(base, (f + 332));
    R(0) = ld32(base, (f + 336));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1300), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D488u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3532);
    R(4) = (R(29) + 3544);
    R(3) = (R(29) + 3556);
    R(11) = ld32(base, (R(29) + 3532));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4416);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3544));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3556));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 292), R(11));
    st32(base, (f + 296), R(10));
    st32(base, (f + 300), R(9));
    st32(base, (f + 304), R(8));
    st32(base, (f + 308), R(7));
    st32(base, (f + 312), R(6));
    st32(base, (f + 316), R(5));
    st32(base, (f + 320), R(4));
    st32(base, (f + 324), R(0));
    GM_CALLV(0x80B3D4E4u, 0x80B39060u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1364);
    GM_CALLV(0x80B3D4F4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1364);
    R(24) = ld32(base, (f + 316));
    R(12) = ld32(base, (f + 320));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 324));
    R(5) = (R(27) + 1352);
    R(10) = ld32(base, (f + 304));
    R(9) = ld32(base, (f + 308));
    R(8) = ld32(base, (f + 312));
    R(7) = ld32(base, (f + 292));
    R(6) = ld32(base, (f + 296));
    R(0) = ld32(base, (f + 300));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1364), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D554u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3568);
    R(4) = (R(29) + 3580);
    R(3) = (R(29) + 3592);
    R(11) = ld32(base, (R(29) + 3568));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4452);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3580));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3592));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 256), R(11));
    st32(base, (f + 260), R(10));
    st32(base, (f + 264), R(9));
    st32(base, (f + 268), R(8));
    st32(base, (f + 272), R(7));
    st32(base, (f + 276), R(6));
    st32(base, (f + 280), R(5));
    st32(base, (f + 284), R(4));
    st32(base, (f + 288), R(0));
    GM_CALLV(0x80B3D5B0u, 0x80B39070u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1428);
    GM_CALLV(0x80B3D5C0u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1428);
    R(24) = ld32(base, (f + 280));
    R(12) = ld32(base, (f + 284));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 288));
    R(5) = (R(27) + 1416);
    R(10) = ld32(base, (f + 268));
    R(9) = ld32(base, (f + 272));
    R(8) = ld32(base, (f + 276));
    R(7) = ld32(base, (f + 256));
    R(6) = ld32(base, (f + 260));
    R(0) = ld32(base, (f + 264));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1428), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D620u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3604);
    R(4) = (R(29) + 3616);
    R(3) = (R(29) + 3628);
    R(11) = ld32(base, (R(29) + 3604));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4496);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3616));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3628));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 220), R(11));
    st32(base, (f + 224), R(10));
    st32(base, (f + 228), R(9));
    st32(base, (f + 232), R(8));
    st32(base, (f + 236), R(7));
    st32(base, (f + 240), R(6));
    st32(base, (f + 244), R(5));
    st32(base, (f + 248), R(4));
    st32(base, (f + 252), R(0));
    GM_CALLV(0x80B3D67Cu, 0x80B3DB40u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1492);
    GM_CALLV(0x80B3D68Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1492);
    R(24) = ld32(base, (f + 244));
    R(12) = ld32(base, (f + 248));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 252));
    R(5) = (R(27) + 1480);
    R(10) = ld32(base, (f + 232));
    R(9) = ld32(base, (f + 236));
    R(8) = ld32(base, (f + 240));
    R(7) = ld32(base, (f + 220));
    R(6) = ld32(base, (f + 224));
    R(0) = ld32(base, (f + 228));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1492), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D6ECu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3640);
    R(4) = (R(29) + 3652);
    R(3) = (R(29) + 3664);
    R(11) = ld32(base, (R(29) + 3640));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4536);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3652));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3664));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 184), R(11));
    st32(base, (f + 188), R(10));
    st32(base, (f + 192), R(9));
    st32(base, (f + 196), R(8));
    st32(base, (f + 200), R(7));
    st32(base, (f + 204), R(6));
    st32(base, (f + 208), R(5));
    st32(base, (f + 212), R(4));
    st32(base, (f + 216), R(0));
    GM_CALLV(0x80B3D748u, 0x80B39080u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1556);
    GM_CALLV(0x80B3D758u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1556);
    R(25) = ld32(base, (f + 208));
    R(12) = ld32(base, (f + 212));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 216));
    R(5) = (R(27) + 1544);
    R(10) = ld32(base, (f + 196));
    R(9) = ld32(base, (f + 200));
    R(8) = ld32(base, (f + 204));
    R(7) = ld32(base, (f + 184));
    R(6) = ld32(base, (f + 188));
    R(0) = ld32(base, (f + 192));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1556), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B3D7B8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3676);
    R(4) = (R(29) + 3688);
    R(3) = (R(29) + 3700);
    R(11) = ld32(base, (R(29) + 3676));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 4580);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3688));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3700));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 148), R(11));
    st32(base, (f + 152), R(10));
    st32(base, (f + 156), R(9));
    st32(base, (f + 160), R(8));
    st32(base, (f + 164), R(7));
    st32(base, (f + 168), R(6));
    st32(base, (f + 172), R(5));
    st32(base, (f + 176), R(4));
    st32(base, (f + 180), R(0));
    GM_CALLV(0x80B3D814u, 0x80B39090u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1620);
    GM_CALLV(0x80B3D824u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1620);
    R(26) = ld32(base, (f + 172));
    R(12) = ld32(base, (f + 176));
    R(4) = (R(31) + -9504);
    R(11) = ld32(base, (f + 180));
    R(5) = (R(27) + 1608);
    R(10) = ld32(base, (f + 160));
    R(9) = ld32(base, (f + 164));
    R(8) = ld32(base, (f + 168));
    R(7) = ld32(base, (f + 148));
    R(6) = ld32(base, (f + 152));
    R(0) = ld32(base, (f + 156));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1620), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B3D884u, 0x80B1CAC0u, 0);
    R(0) = ld8(base, (R(27) + 1672));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B3DA14; }
    { uint32_t ea_ = (R(28) + 76); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    R(3) = (R(29) + 592);
    { uint32_t ea_ = (R(28) + 140); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(28) + 168); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 192); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 200); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 208); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 92); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 216); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 144); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 148); ctx->f[24].d = ctx->ps1[24] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 152); ctx->f[25].d = ctx->ps1[25] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 156); ctx->f[26].d = ctx->ps1[26] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 160); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 164); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 136); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 172); ctx->f[13].d = ctx->ps1[13] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 176); ctx->f[12].d = ctx->ps1[12] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 180); ctx->f[11].d = ctx->ps1[11] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 184); ctx->f[10].d = ctx->ps1[10] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 188); ctx->f[9].d = ctx->ps1[9] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 196); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 204); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 212); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 84); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 136); stfs(base, ea_, ctx->f[22].d); }
    { uint32_t ea_ = (f + 140); stfs(base, ea_, ctx->f[23].d); }
    { uint32_t ea_ = (f + 144); stfs(base, ea_, ctx->f[22].d); }
    { uint32_t ea_ = (R(3) + 24); stfs(base, ea_, ctx->f[22].d); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[23].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[22].d); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[24].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[25].d); }
    { uint32_t ea_ = (R(3) + 68); stfs(base, ea_, ctx->f[24].d); }
    { uint32_t ea_ = (R(3) + 72); stfs(base, ea_, ctx->f[25].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[26].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (R(3) + 76); stfs(base, ea_, ctx->f[26].d); }
    { uint32_t ea_ = (R(3) + 80); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (f + 124); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (f + 128); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (f + 132); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(3) + 100); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(3) + 132); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(3) + 140); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[13].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[12].d); }
    { uint32_t ea_ = (R(3) + 144); stfs(base, ea_, ctx->f[13].d); }
    { uint32_t ea_ = (R(3) + 148); stfs(base, ea_, ctx->f[12].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (R(3) + 156); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(3) + 160); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(3) + 164); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 184); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 188); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(3) + 196); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(3) + 200); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 204); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 232); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 236); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 252); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(3) + 256); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 260); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 264); stfs(base, ea_, ctx->f[4].d); }
    st8(base, (R(27) + 1672), R(0));
L_80B3DA14:;
    R(11) = (f + 1056);
    R(0) = lr;
}

/* fn_4_210F0 (fn_4_210F0, 12 bytes) */
static void eb_m_3db40(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30716);
}

/* fn_4_21100 (fn_4_21100, 12 bytes) */
static void eb_m_3db50(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_21110 (fn_4_21110, 12 bytes) */
static void eb_m_3db60(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31228);
}

/* fn_4_21120 (fn_4_21120, 12 bytes) */
static void eb_m_3db70(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30708);
}

/* fn_4_21130 (fn_4_21130, 12 bytes) */
static void eb_m_3db80(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30644);
}

/* fn_4_21140 (fn_4_21140, 12 bytes) */
static void eb_m_3db90(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30516);
}

/* fn_4_21150 (fn_4_21150, 12 bytes) */
static void eb_m_3dba0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31484);
}

/* fn_4_21160 (fn_4_21160, 12 bytes) */
static void eb_m_3dbb0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31676);
}

/* fn_4_21170 (fn_4_21170, 12 bytes) */
static void eb_m_3dbc0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31740);
}

/* fn_4_21180 (fn_4_21180, 12 bytes) */
static void eb_m_3dbd0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31804);
}

/* fn_4_21190 (fn_4_21190, 12 bytes) */
static void eb_m_3dbe0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31868);
}

/* fn_4_211A0 (fn_4_211A0, 12 bytes) */
static void eb_m_3dbf0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31932);
}

/* fn_4_211B0 (fn_4_211B0, 12 bytes) */
static void eb_m_3dc00(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31996);
}

/* fn_4_211C0 (fn_4_211C0, 12 bytes) */
static void eb_m_3dc10(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30908);
}

/* fn_4_211D0 (fn_4_211D0, 12 bytes) */
static void eb_m_3dc20(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_211E0 (fn_4_211E0, 12 bytes) */
static void eb_m_3dc30(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31036);
}

/* fn_4_217E0 (fn_4_217E0, 12 bytes) */
static void eb_m_3e230(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_217F0 (fn_4_217F0, 12 bytes) */
static void eb_m_3e240(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21800 (fn_4_21800, 12 bytes) */
static void eb_m_3e250(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21810 (fn_4_21810, 12 bytes) */
static void eb_m_3e260(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21820 (fn_4_21820, 12 bytes) */
static void eb_m_3e270(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21830 (fn_4_21830, 12 bytes) */
static void eb_m_3e280(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21840 (fn_4_21840, 12 bytes) */
static void eb_m_3e290(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21850 (fn_4_21850, 12 bytes) */
static void eb_m_3e2a0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21860 (fn_4_21860, 12 bytes) */
static void eb_m_3e2b0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21870 (fn_4_21870, 12 bytes) */
static void eb_m_3e2c0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21880 (fn_4_21880, 12 bytes) */
static void eb_m_3e2d0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_21890 (fn_4_21890, 12 bytes) */
static void eb_m_3e2e0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_218A0 (fn_4_218A0, 12 bytes) */
static void eb_m_3e2f0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_218B0 (fn_4_218B0, 12 bytes) */
static void eb_m_3e300(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_218C0 (fn_4_218C0, 12 bytes) */
static void eb_m_3e310(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_218D0 (fn_4_218D0, 12 bytes) */
static void eb_m_3e320(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_28160 (fn_4_28160, 4024 bytes) */
static void eb_m_44bb0(GM_CTX) {
    GM_FN(0x80B44BB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 800);
    R(29) = (0 + 0x80B80000u);
    R(27) = (0 + 0x80B90000u);
    R(29) = (R(29) + -9656);
    R(28) = (0 + 0x80B70000u);
    R(5) = (R(29) + 4768);
    R(11) = ld32(base, (R(29) + 4768));
    R(4) = (R(29) + 4780);
    R(3) = (R(29) + 4792);
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(27) + -17072);
    R(9) = ld32(base, (R(5) + 8));
    R(28) = (R(28) + 17992);
    R(8) = ld32(base, (R(29) + 4780));
    R(24) = (R(29) + 5380);
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 4792));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 724), R(11));
    st32(base, (f + 728), R(10));
    st32(base, (f + 732), R(9));
    st32(base, (f + 736), R(8));
    st32(base, (f + 740), R(7));
    st32(base, (f + 744), R(6));
    st32(base, (f + 748), R(5));
    st32(base, (f + 752), R(4));
    st32(base, (f + 756), R(0));
    GM_CALLV(0x80B44C60u, 0x80B45C30u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(24) |R(24);
    R(3) = (R(27) + 12);
    GM_CALLV(0x80B44C70u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 12);
    R(24) = ld32(base, (f + 748));
    R(12) = ld32(base, (f + 752));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 756));
    R(30) = (R(30) + -3712);
    R(10) = ld32(base, (f + 736));
    R(31) = (0 + 0x80B40000u);
    R(9) = ld32(base, (f + 740));
    R(4) = (R(31) + 23504);
    R(8) = ld32(base, (f + 744));
    R(5) = (R(27) + 0);
    R(7) = ld32(base, (f + 724));
    R(6) = ld32(base, (f + 728));
    R(0) = ld32(base, (f + 732));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 12), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B44CDCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 4804);
    R(4) = (R(29) + 4816);
    R(3) = (R(29) + 4828);
    R(11) = ld32(base, (R(29) + 4804));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5416);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 4816));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 4828));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 688), R(11));
    st32(base, (f + 692), R(10));
    st32(base, (f + 696), R(9));
    st32(base, (f + 700), R(8));
    st32(base, (f + 704), R(7));
    st32(base, (f + 708), R(6));
    st32(base, (f + 712), R(5));
    st32(base, (f + 716), R(4));
    st32(base, (f + 720), R(0));
    GM_CALLV(0x80B44D38u, 0x80B3E230u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 76);
    GM_CALLV(0x80B44D48u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 76);
    R(24) = ld32(base, (f + 712));
    R(12) = ld32(base, (f + 716));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 720));
    R(5) = (R(27) + 64);
    R(10) = ld32(base, (f + 700));
    R(9) = ld32(base, (f + 704));
    R(8) = ld32(base, (f + 708));
    R(7) = ld32(base, (f + 688));
    R(6) = ld32(base, (f + 692));
    R(0) = ld32(base, (f + 696));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 76), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B44DA8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 4840);
    R(4) = (R(29) + 4852);
    R(3) = (R(29) + 4864);
    R(11) = ld32(base, (R(29) + 4840));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5448);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 4852));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 4864));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 652), R(11));
    st32(base, (f + 656), R(10));
    st32(base, (f + 660), R(9));
    st32(base, (f + 664), R(8));
    st32(base, (f + 668), R(7));
    st32(base, (f + 672), R(6));
    st32(base, (f + 676), R(5));
    st32(base, (f + 680), R(4));
    st32(base, (f + 684), R(0));
    GM_CALLV(0x80B44E04u, 0x80B3E240u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 140);
    GM_CALLV(0x80B44E14u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 140);
    R(24) = ld32(base, (f + 676));
    R(12) = ld32(base, (f + 680));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 684));
    R(5) = (R(27) + 128);
    R(10) = ld32(base, (f + 664));
    R(9) = ld32(base, (f + 668));
    R(8) = ld32(base, (f + 672));
    R(7) = ld32(base, (f + 652));
    R(6) = ld32(base, (f + 656));
    R(0) = ld32(base, (f + 660));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 140), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B44E74u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 4876);
    R(4) = (R(29) + 4888);
    R(3) = (R(29) + 4900);
    R(11) = ld32(base, (R(29) + 4876));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5480);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 4888));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 4900));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 616), R(11));
    st32(base, (f + 620), R(10));
    st32(base, (f + 624), R(9));
    st32(base, (f + 628), R(8));
    st32(base, (f + 632), R(7));
    st32(base, (f + 636), R(6));
    st32(base, (f + 640), R(5));
    st32(base, (f + 644), R(4));
    st32(base, (f + 648), R(0));
    GM_CALLV(0x80B44ED0u, 0x80B3E250u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 204);
    GM_CALLV(0x80B44EE0u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 204);
    R(24) = ld32(base, (f + 640));
    R(12) = ld32(base, (f + 644));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 648));
    R(5) = (R(27) + 192);
    R(10) = ld32(base, (f + 628));
    R(9) = ld32(base, (f + 632));
    R(8) = ld32(base, (f + 636));
    R(7) = ld32(base, (f + 616));
    R(6) = ld32(base, (f + 620));
    R(0) = ld32(base, (f + 624));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 204), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B44F40u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 4912);
    R(4) = (R(29) + 4924);
    R(3) = (R(29) + 4936);
    R(11) = ld32(base, (R(29) + 4912));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5512);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 4924));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 4936));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 580), R(11));
    st32(base, (f + 584), R(10));
    st32(base, (f + 588), R(9));
    st32(base, (f + 592), R(8));
    st32(base, (f + 596), R(7));
    st32(base, (f + 600), R(6));
    st32(base, (f + 604), R(5));
    st32(base, (f + 608), R(4));
    st32(base, (f + 612), R(0));
    GM_CALLV(0x80B44F9Cu, 0x80B3E260u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 268);
    GM_CALLV(0x80B44FACu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 268);
    R(24) = ld32(base, (f + 604));
    R(12) = ld32(base, (f + 608));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 612));
    R(5) = (R(27) + 256);
    R(10) = ld32(base, (f + 592));
    R(9) = ld32(base, (f + 596));
    R(8) = ld32(base, (f + 600));
    R(7) = ld32(base, (f + 580));
    R(6) = ld32(base, (f + 584));
    R(0) = ld32(base, (f + 588));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 268), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B4500Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 4948);
    R(4) = (R(29) + 4960);
    R(3) = (R(29) + 4972);
    R(11) = ld32(base, (R(29) + 4948));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5544);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 4960));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 4972));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 544), R(11));
    st32(base, (f + 548), R(10));
    st32(base, (f + 552), R(9));
    st32(base, (f + 556), R(8));
    st32(base, (f + 560), R(7));
    st32(base, (f + 564), R(6));
    st32(base, (f + 568), R(5));
    st32(base, (f + 572), R(4));
    st32(base, (f + 576), R(0));
    GM_CALLV(0x80B45068u, 0x80B3E270u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 332);
    GM_CALLV(0x80B45078u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 332);
    R(24) = ld32(base, (f + 568));
    R(12) = ld32(base, (f + 572));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 576));
    R(5) = (R(27) + 320);
    R(10) = ld32(base, (f + 556));
    R(9) = ld32(base, (f + 560));
    R(8) = ld32(base, (f + 564));
    R(7) = ld32(base, (f + 544));
    R(6) = ld32(base, (f + 548));
    R(0) = ld32(base, (f + 552));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 332), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B450D8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 4984);
    R(4) = (R(29) + 4996);
    R(3) = (R(29) + 5008);
    R(11) = ld32(base, (R(29) + 4984));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5576);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 4996));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5008));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 508), R(11));
    st32(base, (f + 512), R(10));
    st32(base, (f + 516), R(9));
    st32(base, (f + 520), R(8));
    st32(base, (f + 524), R(7));
    st32(base, (f + 528), R(6));
    st32(base, (f + 532), R(5));
    st32(base, (f + 536), R(4));
    st32(base, (f + 540), R(0));
    GM_CALLV(0x80B45134u, 0x80B3E280u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 396);
    GM_CALLV(0x80B45144u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 396);
    R(24) = ld32(base, (f + 532));
    R(12) = ld32(base, (f + 536));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 540));
    R(5) = (R(27) + 384);
    R(10) = ld32(base, (f + 520));
    R(9) = ld32(base, (f + 524));
    R(8) = ld32(base, (f + 528));
    R(7) = ld32(base, (f + 508));
    R(6) = ld32(base, (f + 512));
    R(0) = ld32(base, (f + 516));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 396), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B451A4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5020);
    R(4) = (R(29) + 5032);
    R(3) = (R(29) + 5044);
    R(11) = ld32(base, (R(29) + 5020));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5612);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5032));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5044));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 472), R(11));
    st32(base, (f + 476), R(10));
    st32(base, (f + 480), R(9));
    st32(base, (f + 484), R(8));
    st32(base, (f + 488), R(7));
    st32(base, (f + 492), R(6));
    st32(base, (f + 496), R(5));
    st32(base, (f + 500), R(4));
    st32(base, (f + 504), R(0));
    GM_CALLV(0x80B45200u, 0x80B3E290u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 460);
    GM_CALLV(0x80B45210u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 460);
    R(24) = ld32(base, (f + 496));
    R(12) = ld32(base, (f + 500));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 504));
    R(5) = (R(27) + 448);
    R(10) = ld32(base, (f + 484));
    R(9) = ld32(base, (f + 488));
    R(8) = ld32(base, (f + 492));
    R(7) = ld32(base, (f + 472));
    R(6) = ld32(base, (f + 476));
    R(0) = ld32(base, (f + 480));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 460), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B45270u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5056);
    R(4) = (R(29) + 5068);
    R(3) = (R(29) + 5080);
    R(11) = ld32(base, (R(29) + 5056));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5644);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5068));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5080));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 436), R(11));
    st32(base, (f + 440), R(10));
    st32(base, (f + 444), R(9));
    st32(base, (f + 448), R(8));
    st32(base, (f + 452), R(7));
    st32(base, (f + 456), R(6));
    st32(base, (f + 460), R(5));
    st32(base, (f + 464), R(4));
    st32(base, (f + 468), R(0));
    GM_CALLV(0x80B452CCu, 0x80B3E2A0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 524);
    GM_CALLV(0x80B452DCu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 524);
    R(24) = ld32(base, (f + 460));
    R(12) = ld32(base, (f + 464));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 468));
    R(5) = (R(27) + 512);
    R(10) = ld32(base, (f + 448));
    R(9) = ld32(base, (f + 452));
    R(8) = ld32(base, (f + 456));
    R(7) = ld32(base, (f + 436));
    R(6) = ld32(base, (f + 440));
    R(0) = ld32(base, (f + 444));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 524), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B4533Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5092);
    R(4) = (R(29) + 5104);
    R(3) = (R(29) + 5116);
    R(11) = ld32(base, (R(29) + 5092));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5676);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5104));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5116));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 400), R(11));
    st32(base, (f + 404), R(10));
    st32(base, (f + 408), R(9));
    st32(base, (f + 412), R(8));
    st32(base, (f + 416), R(7));
    st32(base, (f + 420), R(6));
    st32(base, (f + 424), R(5));
    st32(base, (f + 428), R(4));
    st32(base, (f + 432), R(0));
    GM_CALLV(0x80B45398u, 0x80B3E2B0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 588);
    GM_CALLV(0x80B453A8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 588);
    R(24) = ld32(base, (f + 424));
    R(12) = ld32(base, (f + 428));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 432));
    R(5) = (R(27) + 576);
    R(10) = ld32(base, (f + 412));
    R(9) = ld32(base, (f + 416));
    R(8) = ld32(base, (f + 420));
    R(7) = ld32(base, (f + 400));
    R(6) = ld32(base, (f + 404));
    R(0) = ld32(base, (f + 408));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 588), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B45408u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5128);
    R(4) = (R(29) + 5140);
    R(3) = (R(29) + 5152);
    R(11) = ld32(base, (R(29) + 5128));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5712);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5140));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5152));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 364), R(11));
    st32(base, (f + 368), R(10));
    st32(base, (f + 372), R(9));
    st32(base, (f + 376), R(8));
    st32(base, (f + 380), R(7));
    st32(base, (f + 384), R(6));
    st32(base, (f + 388), R(5));
    st32(base, (f + 392), R(4));
    st32(base, (f + 396), R(0));
    GM_CALLV(0x80B45464u, 0x80B3E2C0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 652);
    GM_CALLV(0x80B45474u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 652);
    R(24) = ld32(base, (f + 388));
    R(12) = ld32(base, (f + 392));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 396));
    R(5) = (R(27) + 640);
    R(10) = ld32(base, (f + 376));
    R(9) = ld32(base, (f + 380));
    R(8) = ld32(base, (f + 384));
    R(7) = ld32(base, (f + 364));
    R(6) = ld32(base, (f + 368));
    R(0) = ld32(base, (f + 372));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 652), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B454D4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5164);
    R(4) = (R(29) + 5176);
    R(3) = (R(29) + 5188);
    R(11) = ld32(base, (R(29) + 5164));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5744);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5176));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5188));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 328), R(11));
    st32(base, (f + 332), R(10));
    st32(base, (f + 336), R(9));
    st32(base, (f + 340), R(8));
    st32(base, (f + 344), R(7));
    st32(base, (f + 348), R(6));
    st32(base, (f + 352), R(5));
    st32(base, (f + 356), R(4));
    st32(base, (f + 360), R(0));
    GM_CALLV(0x80B45530u, 0x80B3E2D0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 716);
    GM_CALLV(0x80B45540u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 716);
    R(24) = ld32(base, (f + 352));
    R(12) = ld32(base, (f + 356));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 360));
    R(5) = (R(27) + 704);
    R(10) = ld32(base, (f + 340));
    R(9) = ld32(base, (f + 344));
    R(8) = ld32(base, (f + 348));
    R(7) = ld32(base, (f + 328));
    R(6) = ld32(base, (f + 332));
    R(0) = ld32(base, (f + 336));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 716), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B455A0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5200);
    R(4) = (R(29) + 5212);
    R(3) = (R(29) + 5224);
    R(11) = ld32(base, (R(29) + 5200));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5776);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5212));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5224));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 292), R(11));
    st32(base, (f + 296), R(10));
    st32(base, (f + 300), R(9));
    st32(base, (f + 304), R(8));
    st32(base, (f + 308), R(7));
    st32(base, (f + 312), R(6));
    st32(base, (f + 316), R(5));
    st32(base, (f + 320), R(4));
    st32(base, (f + 324), R(0));
    GM_CALLV(0x80B455FCu, 0x80B3E2E0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 780);
    GM_CALLV(0x80B4560Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 780);
    R(24) = ld32(base, (f + 316));
    R(12) = ld32(base, (f + 320));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 324));
    R(5) = (R(27) + 768);
    R(10) = ld32(base, (f + 304));
    R(9) = ld32(base, (f + 308));
    R(8) = ld32(base, (f + 312));
    R(7) = ld32(base, (f + 292));
    R(6) = ld32(base, (f + 296));
    R(0) = ld32(base, (f + 300));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 780), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B4566Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5236);
    R(4) = (R(29) + 5248);
    R(3) = (R(29) + 5260);
    R(11) = ld32(base, (R(29) + 5236));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5808);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5248));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5260));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 256), R(11));
    st32(base, (f + 260), R(10));
    st32(base, (f + 264), R(9));
    st32(base, (f + 268), R(8));
    st32(base, (f + 272), R(7));
    st32(base, (f + 276), R(6));
    st32(base, (f + 280), R(5));
    st32(base, (f + 284), R(4));
    st32(base, (f + 288), R(0));
    GM_CALLV(0x80B456C8u, 0x80B3E2F0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 844);
    GM_CALLV(0x80B456D8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 844);
    R(24) = ld32(base, (f + 280));
    R(12) = ld32(base, (f + 284));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 288));
    R(5) = (R(27) + 832);
    R(10) = ld32(base, (f + 268));
    R(9) = ld32(base, (f + 272));
    R(8) = ld32(base, (f + 276));
    R(7) = ld32(base, (f + 256));
    R(6) = ld32(base, (f + 260));
    R(0) = ld32(base, (f + 264));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 844), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B45738u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5272);
    R(4) = (R(29) + 5284);
    R(3) = (R(29) + 5296);
    R(11) = ld32(base, (R(29) + 5272));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5844);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5284));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5296));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 220), R(11));
    st32(base, (f + 224), R(10));
    st32(base, (f + 228), R(9));
    st32(base, (f + 232), R(8));
    st32(base, (f + 236), R(7));
    st32(base, (f + 240), R(6));
    st32(base, (f + 244), R(5));
    st32(base, (f + 248), R(4));
    st32(base, (f + 252), R(0));
    GM_CALLV(0x80B45794u, 0x80B3E300u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 908);
    GM_CALLV(0x80B457A4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 908);
    R(24) = ld32(base, (f + 244));
    R(12) = ld32(base, (f + 248));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 252));
    R(5) = (R(27) + 896);
    R(10) = ld32(base, (f + 232));
    R(9) = ld32(base, (f + 236));
    R(8) = ld32(base, (f + 240));
    R(7) = ld32(base, (f + 220));
    R(6) = ld32(base, (f + 224));
    R(0) = ld32(base, (f + 228));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 908), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B45804u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5308);
    R(4) = (R(29) + 5320);
    R(3) = (R(29) + 5332);
    R(11) = ld32(base, (R(29) + 5308));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5876);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5320));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5332));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 184), R(11));
    st32(base, (f + 188), R(10));
    st32(base, (f + 192), R(9));
    st32(base, (f + 196), R(8));
    st32(base, (f + 200), R(7));
    st32(base, (f + 204), R(6));
    st32(base, (f + 208), R(5));
    st32(base, (f + 212), R(4));
    st32(base, (f + 216), R(0));
    GM_CALLV(0x80B45860u, 0x80B3E310u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 972);
    GM_CALLV(0x80B45870u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 972);
    R(25) = ld32(base, (f + 208));
    R(12) = ld32(base, (f + 212));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 216));
    R(5) = (R(27) + 960);
    R(10) = ld32(base, (f + 196));
    R(9) = ld32(base, (f + 200));
    R(8) = ld32(base, (f + 204));
    R(7) = ld32(base, (f + 184));
    R(6) = ld32(base, (f + 188));
    R(0) = ld32(base, (f + 192));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 972), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B458D0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 5344);
    R(4) = (R(29) + 5356);
    R(3) = (R(29) + 5368);
    R(11) = ld32(base, (R(29) + 5344));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 5912);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 5356));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 5368));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 148), R(11));
    st32(base, (f + 152), R(10));
    st32(base, (f + 156), R(9));
    st32(base, (f + 160), R(8));
    st32(base, (f + 164), R(7));
    st32(base, (f + 168), R(6));
    st32(base, (f + 172), R(5));
    st32(base, (f + 176), R(4));
    st32(base, (f + 180), R(0));
    GM_CALLV(0x80B4592Cu, 0x80B3E320u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 1036);
    GM_CALLV(0x80B4593Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1036);
    R(26) = ld32(base, (f + 172));
    R(12) = ld32(base, (f + 176));
    R(4) = (R(31) + 23504);
    R(11) = ld32(base, (f + 180));
    R(5) = (R(27) + 1024);
    R(10) = ld32(base, (f + 160));
    R(9) = ld32(base, (f + 164));
    R(8) = ld32(base, (f + 168));
    R(7) = ld32(base, (f + 148));
    R(6) = ld32(base, (f + 152));
    R(0) = ld32(base, (f + 156));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 1036), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B4599Cu, 0x80B1CAC0u, 0);
    R(0) = ld8(base, (R(27) + 1088));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B45B28; }
    { uint32_t ea_ = (R(28) + 0); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(5) = (R(29) + 752);
    { uint32_t ea_ = (R(28) + 164); ctx->f[9].d = ctx->ps1[9] = ldfs(base, ea_); }
    R(4) = (0 + 1277);
    { uint32_t ea_ = (R(28) + 24); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(3) = (0 + 1278);
    { uint32_t ea_ = (R(28) + 136); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(28) + 104); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 140); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 144); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 148); ctx->f[13].d = ctx->ps1[13] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 152); ctx->f[12].d = ctx->ps1[12] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 156); ctx->f[11].d = ctx->ps1[11] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 160); ctx->f[10].d = ctx->ps1[10] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 168); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 172); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 176); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 180); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 184); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 188); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 192); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 196); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (R(5) + 16); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (R(5) + 20); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (f + 136); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (f + 140); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (f + 144); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(5) + 84); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(5) + 88); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (R(5) + 92); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 124); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 128); stfs(base, ea_, ctx->f[13].d); }
    { uint32_t ea_ = (f + 132); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(5) + 1980); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(5) + 1984); stfs(base, ea_, ctx->f[13].d); }
    { uint32_t ea_ = (R(5) + 1988); stfs(base, ea_, ctx->f[30].d); }
    st32(base, (R(5) + 2036), R(4));
    st32(base, (R(5) + 2040), R(3));
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[12].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (R(5) + 2088); stfs(base, ea_, ctx->f[12].d); }
    { uint32_t ea_ = (R(5) + 2092); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(5) + 2168); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (R(5) + 2172); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (R(5) + 2176); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(5) + 2180); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(5) + 2196); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (R(5) + 2200); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(5) + 2204); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(5) + 2224); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(5) + 2228); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(5) + 2232); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(5) + 2400); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(5) + 2404); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(5) + 2408); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(5) + 2412); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(5) + 2416); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(5) + 2420); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(5) + 2424); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(5) + 2428); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(5) + 2432); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(5) + 2440); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(5) + 2444); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(5) + 2448); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 2484); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(5) + 2488); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(5) + 2492); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(27) + 1088), R(0));
L_80B45B28:;
    R(11) = (f + 800);
    R(0) = lr;
}

/* fn_4_291E0 (fn_4_291E0, 12 bytes) */
static void eb_m_45c30(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30388);
}

/* fn_4_29560 (fn_4_29560, 12 bytes) */
static void eb_m_45fb0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_29570 (fn_4_29570, 12 bytes) */
static void eb_m_45fc0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_29580 (fn_4_29580, 12 bytes) */
static void eb_m_45fd0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_29BD0 (fn_4_29BD0, 812 bytes) */
static void eb_m_46620(GM_CTX) {
    GM_FN(0x80B46620); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 192);
    R(28) = (0 + 0x80B80000u);
    R(27) = (0 + 0x80B90000u);
    R(28) = (R(28) + -3608);
    R(29) = (0 + 0x80B70000u);
    R(5) = (R(28) + 824);
    R(11) = ld32(base, (R(28) + 824));
    R(4) = (R(28) + 836);
    R(3) = (R(28) + 848);
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(27) + -15976);
    R(9) = ld32(base, (R(5) + 8));
    R(29) = (R(29) + 18344);
    R(8) = ld32(base, (R(28) + 836));
    R(24) = (R(28) + 932);
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 848));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 116), R(11));
    st32(base, (f + 120), R(10));
    st32(base, (f + 124), R(9));
    st32(base, (f + 128), R(8));
    st32(base, (f + 132), R(7));
    st32(base, (f + 136), R(6));
    st32(base, (f + 140), R(5));
    st32(base, (f + 144), R(4));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x80B466A8u, 0x80B45FB0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(24) |R(24);
    R(3) = (R(27) + 12);
    GM_CALLV(0x80B466B8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 12);
    R(24) = ld32(base, (f + 140));
    R(12) = ld32(base, (f + 144));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 148));
    R(30) = (R(30) + -2556);
    R(10) = ld32(base, (f + 128));
    R(31) = (0 + 0x80B40000u);
    R(9) = ld32(base, (f + 132));
    R(4) = (R(31) + 27056);
    R(8) = ld32(base, (f + 136));
    R(5) = (R(27) + 0);
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 12), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B46724u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 860);
    R(4) = (R(28) + 872);
    R(3) = (R(28) + 884);
    R(11) = ld32(base, (R(28) + 860));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 972);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 872));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 884));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 80), R(11));
    st32(base, (f + 84), R(10));
    st32(base, (f + 88), R(9));
    st32(base, (f + 92), R(8));
    st32(base, (f + 96), R(7));
    st32(base, (f + 100), R(6));
    st32(base, (f + 104), R(5));
    st32(base, (f + 108), R(4));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x80B46780u, 0x80B45FC0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 76);
    GM_CALLV(0x80B46790u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 76);
    R(25) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(31) + 27056);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(27) + 64);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 76), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B467F0u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 896);
    R(4) = (R(28) + 908);
    R(3) = (R(28) + 920);
    R(11) = ld32(base, (R(28) + 896));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(28) + 1012);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 908));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 920));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 44), R(11));
    st32(base, (f + 48), R(10));
    st32(base, (f + 52), R(9));
    st32(base, (f + 56), R(8));
    st32(base, (f + 60), R(7));
    st32(base, (f + 64), R(6));
    st32(base, (f + 68), R(5));
    st32(base, (f + 72), R(4));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x80B4684Cu, 0x80B45FD0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 140);
    GM_CALLV(0x80B4685Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 140);
    R(26) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(31) + 27056);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(27) + 128);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 140), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B468BCu, 0x80B1CAC0u, 0);
    R(0) = ld8(base, (R(27) + 192));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B46934; }
    { uint32_t ea_ = (R(29) + 4); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(3) = (R(28) + 76);
    { uint32_t ea_ = (R(29) + 16); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(29) + 20); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(27) + 192), R(0));
L_80B46934:;
    R(11) = (f + 192);
    R(0) = lr;
}

/* fn_4_2A3B0 (fn_4_2A3B0, 12 bytes) */
static void eb_m_46e00(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2A3C0 (fn_4_2A3C0, 12 bytes) */
static void eb_m_46e10(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2A3D0 (fn_4_2A3D0, 12 bytes) */
static void eb_m_46e20(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2A3E0 (fn_4_2A3E0, 12 bytes) */
static void eb_m_46e30(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2BA80 (fn_4_2BA80, 1076 bytes) */
static void eb_m_484d0(GM_CTX) {
    GM_FN(0x80B484D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 256);
    R(29) = (0 + 0x80B80000u);
    R(27) = (0 + 0x80B90000u);
    R(29) = (R(29) + -2448);
    R(28) = (0 + 0x80B70000u);
    R(5) = (R(29) + 1320);
    R(11) = ld32(base, (R(29) + 1320));
    R(4) = (R(29) + 1332);
    R(3) = (R(29) + 1344);
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(27) + -15776);
    R(9) = ld32(base, (R(5) + 8));
    R(28) = (R(28) + 18384);
    R(8) = ld32(base, (R(29) + 1332));
    R(24) = (R(29) + 1464);
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1344));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 176), R(11));
    st32(base, (f + 180), R(10));
    st32(base, (f + 184), R(9));
    st32(base, (f + 188), R(8));
    st32(base, (f + 192), R(7));
    st32(base, (f + 196), R(6));
    st32(base, (f + 200), R(5));
    st32(base, (f + 204), R(4));
    st32(base, (f + 208), R(0));
    GM_CALLV(0x80B48558u, 0x80B46E00u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(24) |R(24);
    R(3) = (R(27) + 12);
    GM_CALLV(0x80B48568u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 12);
    R(24) = ld32(base, (f + 200));
    R(12) = ld32(base, (f + 204));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 208));
    R(30) = (R(30) + -816);
    R(10) = ld32(base, (f + 188));
    R(31) = (0 + 0x80B50000u);
    R(9) = ld32(base, (f + 192));
    R(4) = (R(31) + -30352);
    R(8) = ld32(base, (f + 196));
    R(5) = (R(27) + 0);
    R(7) = ld32(base, (f + 176));
    R(6) = ld32(base, (f + 180));
    R(0) = ld32(base, (f + 184));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 12), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B485D4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 1356);
    R(4) = (R(29) + 1368);
    R(3) = (R(29) + 1380);
    R(11) = ld32(base, (R(29) + 1356));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 1504);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 1368));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1380));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 140), R(11));
    st32(base, (f + 144), R(10));
    st32(base, (f + 148), R(9));
    st32(base, (f + 152), R(8));
    st32(base, (f + 156), R(7));
    st32(base, (f + 160), R(6));
    st32(base, (f + 164), R(5));
    st32(base, (f + 168), R(4));
    st32(base, (f + 172), R(0));
    GM_CALLV(0x80B48630u, 0x80B46E10u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 76);
    GM_CALLV(0x80B48640u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 76);
    R(24) = ld32(base, (f + 164));
    R(12) = ld32(base, (f + 168));
    R(4) = (R(31) + -30352);
    R(11) = ld32(base, (f + 172));
    R(5) = (R(27) + 64);
    R(10) = ld32(base, (f + 152));
    R(9) = ld32(base, (f + 156));
    R(8) = ld32(base, (f + 160));
    R(7) = ld32(base, (f + 140));
    R(6) = ld32(base, (f + 144));
    R(0) = ld32(base, (f + 148));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 76), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B486A0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 1392);
    R(4) = (R(29) + 1404);
    R(3) = (R(29) + 1416);
    R(11) = ld32(base, (R(29) + 1392));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 1544);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 1404));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1416));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 104), R(11));
    st32(base, (f + 108), R(10));
    st32(base, (f + 112), R(9));
    st32(base, (f + 116), R(8));
    st32(base, (f + 120), R(7));
    st32(base, (f + 124), R(6));
    st32(base, (f + 128), R(5));
    st32(base, (f + 132), R(4));
    st32(base, (f + 136), R(0));
    GM_CALLV(0x80B486FCu, 0x80B46E20u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 140);
    GM_CALLV(0x80B4870Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 140);
    R(25) = ld32(base, (f + 128));
    R(12) = ld32(base, (f + 132));
    R(4) = (R(31) + -30352);
    R(11) = ld32(base, (f + 136));
    R(5) = (R(27) + 128);
    R(10) = ld32(base, (f + 116));
    R(9) = ld32(base, (f + 120));
    R(8) = ld32(base, (f + 124));
    R(7) = ld32(base, (f + 104));
    R(6) = ld32(base, (f + 108));
    R(0) = ld32(base, (f + 112));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 140), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B4876Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 1428);
    R(4) = (R(29) + 1440);
    R(3) = (R(29) + 1452);
    R(11) = ld32(base, (R(29) + 1428));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 1592);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 1440));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1452));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 68), R(11));
    st32(base, (f + 72), R(10));
    st32(base, (f + 76), R(9));
    st32(base, (f + 80), R(8));
    st32(base, (f + 84), R(7));
    st32(base, (f + 88), R(6));
    st32(base, (f + 92), R(5));
    st32(base, (f + 96), R(4));
    st32(base, (f + 100), R(0));
    GM_CALLV(0x80B487C8u, 0x80B46E30u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 204);
    GM_CALLV(0x80B487D8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 204);
    R(26) = ld32(base, (f + 92));
    R(12) = ld32(base, (f + 96));
    R(4) = (R(31) + -30352);
    R(11) = ld32(base, (f + 100));
    R(5) = (R(27) + 192);
    R(10) = ld32(base, (f + 80));
    R(9) = ld32(base, (f + 84));
    R(8) = ld32(base, (f + 88));
    R(7) = ld32(base, (f + 68));
    R(6) = ld32(base, (f + 72));
    R(0) = ld32(base, (f + 76));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 204), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B48838u, 0x80B1CAC0u, 0);
    R(0) = ld8(base, (R(27) + 256));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B488EC; }
    { uint32_t ea_ = (R(28) + 4); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    R(3) = (R(29) + 460);
    { uint32_t ea_ = (R(28) + 24); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(28) + 36); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 28); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 32); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 40); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 44); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 60); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 132); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[8].d); }
    st8(base, (R(27) + 256), R(0));
L_80B488EC:;
    R(11) = (f + 256);
    R(0) = lr;
}

/* fn_4_2C340 (fn_4_2C340, 12 bytes) */
static void eb_m_48d90(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2C350 (fn_4_2C350, 12 bytes) */
static void eb_m_48da0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2C360 (fn_4_2C360, 12 bytes) */
static void eb_m_48db0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2C370 (fn_4_2C370, 12 bytes) */
static void eb_m_48dc0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2C380 (fn_4_2C380, 12 bytes) */
static void eb_m_48dd0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2C390 (fn_4_2C390, 12 bytes) */
static void eb_m_48de0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_2DA80 (fn_4_2DA80, 1400 bytes) */
static void eb_m_4a4d0(GM_CTX) {
    GM_FN(0x80B4A4D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 288);
    R(29) = (0 + 0x80B80000u);
    R(27) = (0 + 0x80B90000u);
    R(29) = (R(29) + -704);
    R(28) = (0 + 0x80B70000u);
    R(5) = (R(29) + 1000);
    R(11) = ld32(base, (R(29) + 1000));
    R(4) = (R(29) + 1012);
    R(3) = (R(29) + 1024);
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(27) + -15512);
    R(9) = ld32(base, (R(5) + 8));
    R(28) = (R(28) + 18464);
    R(8) = ld32(base, (R(29) + 1012));
    R(24) = (R(29) + 1216);
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1024));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 216), R(11));
    st32(base, (f + 220), R(10));
    st32(base, (f + 224), R(9));
    st32(base, (f + 228), R(8));
    st32(base, (f + 232), R(7));
    st32(base, (f + 236), R(6));
    st32(base, (f + 240), R(5));
    st32(base, (f + 244), R(4));
    st32(base, (f + 248), R(0));
    GM_CALLV(0x80B4A558u, 0x80B48D90u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(24) |R(24);
    R(3) = (R(27) + 24);
    GM_CALLV(0x80B4A568u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 24);
    R(24) = ld32(base, (f + 240));
    R(12) = ld32(base, (f + 244));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 248));
    R(30) = (R(30) + 760);
    R(10) = ld32(base, (f + 228));
    R(31) = (0 + 0x80B50000u);
    R(9) = ld32(base, (f + 232));
    R(4) = (R(31) + -21840);
    R(8) = ld32(base, (f + 236));
    R(5) = (R(27) + 12);
    R(7) = ld32(base, (f + 216));
    R(6) = ld32(base, (f + 220));
    R(0) = ld32(base, (f + 224));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 24), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B4A5D4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 1036);
    R(4) = (R(29) + 1048);
    R(3) = (R(29) + 1060);
    R(11) = ld32(base, (R(29) + 1036));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 1256);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 1048));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1060));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 180), R(11));
    st32(base, (f + 184), R(10));
    st32(base, (f + 188), R(9));
    st32(base, (f + 192), R(8));
    st32(base, (f + 196), R(7));
    st32(base, (f + 200), R(6));
    st32(base, (f + 204), R(5));
    st32(base, (f + 208), R(4));
    st32(base, (f + 212), R(0));
    GM_CALLV(0x80B4A630u, 0x80B48DA0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 88);
    GM_CALLV(0x80B4A640u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 88);
    R(24) = ld32(base, (f + 204));
    R(12) = ld32(base, (f + 208));
    R(4) = (R(31) + -21840);
    R(11) = ld32(base, (f + 212));
    R(5) = (R(27) + 76);
    R(10) = ld32(base, (f + 192));
    R(9) = ld32(base, (f + 196));
    R(8) = ld32(base, (f + 200));
    R(7) = ld32(base, (f + 180));
    R(6) = ld32(base, (f + 184));
    R(0) = ld32(base, (f + 188));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 88), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B4A6A0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 1072);
    R(4) = (R(29) + 1084);
    R(3) = (R(29) + 1096);
    R(11) = ld32(base, (R(29) + 1072));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 1296);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 1084));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1096));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 144), R(11));
    st32(base, (f + 148), R(10));
    st32(base, (f + 152), R(9));
    st32(base, (f + 156), R(8));
    st32(base, (f + 160), R(7));
    st32(base, (f + 164), R(6));
    st32(base, (f + 168), R(5));
    st32(base, (f + 172), R(4));
    st32(base, (f + 176), R(0));
    GM_CALLV(0x80B4A6FCu, 0x80B48DB0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 152);
    GM_CALLV(0x80B4A70Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 152);
    R(24) = ld32(base, (f + 168));
    R(12) = ld32(base, (f + 172));
    R(4) = (R(31) + -21840);
    R(11) = ld32(base, (f + 176));
    R(5) = (R(27) + 140);
    R(10) = ld32(base, (f + 156));
    R(9) = ld32(base, (f + 160));
    R(8) = ld32(base, (f + 164));
    R(7) = ld32(base, (f + 144));
    R(6) = ld32(base, (f + 148));
    R(0) = ld32(base, (f + 152));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 152), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B4A76Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 1108);
    R(4) = (R(29) + 1120);
    R(3) = (R(29) + 1132);
    R(11) = ld32(base, (R(29) + 1108));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 1336);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 1120));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1132));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 108), R(11));
    st32(base, (f + 112), R(10));
    st32(base, (f + 116), R(9));
    st32(base, (f + 120), R(8));
    st32(base, (f + 124), R(7));
    st32(base, (f + 128), R(6));
    st32(base, (f + 132), R(5));
    st32(base, (f + 136), R(4));
    st32(base, (f + 140), R(0));
    GM_CALLV(0x80B4A7C8u, 0x80B48DC0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 216);
    GM_CALLV(0x80B4A7D8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 216);
    R(24) = ld32(base, (f + 132));
    R(12) = ld32(base, (f + 136));
    R(4) = (R(31) + -21840);
    R(11) = ld32(base, (f + 140));
    R(5) = (R(27) + 204);
    R(10) = ld32(base, (f + 120));
    R(9) = ld32(base, (f + 124));
    R(8) = ld32(base, (f + 128));
    R(7) = ld32(base, (f + 108));
    R(6) = ld32(base, (f + 112));
    R(0) = ld32(base, (f + 116));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 216), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B4A838u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 1144);
    R(4) = (R(29) + 1156);
    R(3) = (R(29) + 1168);
    R(11) = ld32(base, (R(29) + 1144));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 1376);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 1156));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1168));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 72), R(11));
    st32(base, (f + 76), R(10));
    st32(base, (f + 80), R(9));
    st32(base, (f + 84), R(8));
    st32(base, (f + 88), R(7));
    st32(base, (f + 92), R(6));
    st32(base, (f + 96), R(5));
    st32(base, (f + 100), R(4));
    st32(base, (f + 104), R(0));
    GM_CALLV(0x80B4A894u, 0x80B48DD0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 280);
    GM_CALLV(0x80B4A8A4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 280);
    R(25) = ld32(base, (f + 96));
    R(12) = ld32(base, (f + 100));
    R(4) = (R(31) + -21840);
    R(11) = ld32(base, (f + 104));
    R(5) = (R(27) + 268);
    R(10) = ld32(base, (f + 84));
    R(9) = ld32(base, (f + 88));
    R(8) = ld32(base, (f + 92));
    R(7) = ld32(base, (f + 72));
    R(6) = ld32(base, (f + 76));
    R(0) = ld32(base, (f + 80));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 280), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B4A904u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 1180);
    R(4) = (R(29) + 1192);
    R(3) = (R(29) + 1204);
    R(11) = ld32(base, (R(29) + 1180));
    R(10) = ld32(base, (R(5) + 4));
    R(26) = (R(29) + 1424);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 1192));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 1204));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 36), R(11));
    st32(base, (f + 40), R(10));
    st32(base, (f + 44), R(9));
    st32(base, (f + 48), R(8));
    st32(base, (f + 52), R(7));
    st32(base, (f + 56), R(6));
    st32(base, (f + 60), R(5));
    st32(base, (f + 64), R(4));
    st32(base, (f + 68), R(0));
    GM_CALLV(0x80B4A960u, 0x80B48DE0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(26) |R(26);
    R(3) = (R(27) + 344);
    GM_CALLV(0x80B4A970u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 344);
    R(26) = ld32(base, (f + 60));
    R(12) = ld32(base, (f + 64));
    R(4) = (R(31) + -21840);
    R(11) = ld32(base, (f + 68));
    R(5) = (R(27) + 332);
    R(10) = ld32(base, (f + 48));
    R(9) = ld32(base, (f + 52));
    R(8) = ld32(base, (f + 56));
    R(7) = ld32(base, (f + 36));
    R(6) = ld32(base, (f + 40));
    R(0) = ld32(base, (f + 44));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 344), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B4A9D0u, 0x80B1CAC0u, 0);
    R(0) = ld8(base, (R(27) + 396));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B4AA30; }
    { uint32_t ea_ = (R(28) + 0); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (R(29) + 196);
    { uint32_t ea_ = (R(28) + 20); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(28) + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(27) + 396), R(0));
L_80B4AA30:;
    R(11) = (f + 288);
    R(0) = lr;
}

/* fn_4_2F890 (fn_4_2F890, 868 bytes) */
static void eb_m_4c2e0(GM_CTX) {
    GM_FN(0x80B4C2E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 192);
    R(27) = (0 + 0x80B80000u);
    R(26) = (0 + 0x80B90000u);
    R(27) = (R(27) + 872);
    R(3) = (R(27) + 1408);
    R(24) = ld32(base, (R(27) + 1408));
    R(6) = (R(27) + 1420);
    R(5) = (R(27) + 1432);
    R(12) = ld32(base, (R(3) + 4));
    R(26) = (R(26) + -15112);
    R(11) = ld32(base, (R(3) + 8));
    R(4) = (R(27) + 1552);
    R(10) = ld32(base, (R(27) + 1420));
    R(3) = (R(26) + 16);
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1432));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 116), R(24));
    st32(base, (f + 120), R(12));
    st32(base, (f + 124), R(11));
    st32(base, (f + 128), R(10));
    st32(base, (f + 132), R(9));
    st32(base, (f + 136), R(8));
    st32(base, (f + 140), R(7));
    st32(base, (f + 144), R(6));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x80B4C364u, 0x8015F7C0u, 0);
    R(28) = (0 + 0x80B80000u);
    R(3) = (R(26) + 16);
    R(24) = ld32(base, (f + 140));
    R(28) = (R(28) + 2624);
    R(12) = ld32(base, (f + 144));
    R(29) = (0 + 0x80B50000u);
    R(11) = ld32(base, (f + 148));
    R(4) = (R(29) + -14768);
    R(10) = ld32(base, (f + 128));
    R(5) = (R(26) + 0);
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(26) + 16), R(28));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B4C3CCu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 1444);
    R(4) = (R(27) + 1456);
    R(3) = (R(27) + 1468);
    R(11) = ld32(base, (R(27) + 1444));
    R(10) = ld32(base, (R(5) + 4));
    R(30) = (R(27) + 1588);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 1456));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 1468));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 80), R(11));
    st32(base, (f + 84), R(10));
    st32(base, (f + 88), R(9));
    st32(base, (f + 92), R(8));
    st32(base, (f + 96), R(7));
    st32(base, (f + 100), R(6));
    st32(base, (f + 104), R(5));
    st32(base, (f + 108), R(4));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x80B4C428u, 0x80B4C720u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(30) |R(30);
    R(3) = (R(26) + 76);
    GM_CALLV(0x80B4C438u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 76);
    R(25) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 112));
    R(30) = (R(30) + 2572);
    R(10) = ld32(base, (f + 92));
    R(31) = (0 + 0x80B50000u);
    R(9) = ld32(base, (f + 96));
    R(4) = (R(31) + -14672);
    R(8) = ld32(base, (f + 100));
    R(5) = (R(26) + 64);
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 76), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B4C4A4u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 1480);
    R(6) = (R(27) + 1492);
    R(5) = (R(27) + 1504);
    R(25) = ld32(base, (R(27) + 1480));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 1628);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 144);
    R(10) = ld32(base, (R(27) + 1492));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1504));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 44), R(25));
    st32(base, (f + 48), R(12));
    st32(base, (f + 52), R(11));
    st32(base, (f + 56), R(10));
    st32(base, (f + 60), R(9));
    st32(base, (f + 64), R(8));
    st32(base, (f + 68), R(7));
    st32(base, (f + 72), R(6));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x80B4C504u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 144);
    R(25) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(29) + -14768);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(26) + 128);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(26) + 144), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B4C560u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 1516);
    R(4) = (R(27) + 1528);
    R(3) = (R(27) + 1540);
    R(11) = ld32(base, (R(27) + 1516));
    R(10) = ld32(base, (R(5) + 4));
    R(28) = (R(27) + 1664);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 1528));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 1540));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 8), R(11));
    st32(base, (f + 12), R(10));
    st32(base, (f + 16), R(9));
    st32(base, (f + 20), R(8));
    st32(base, (f + 24), R(7));
    st32(base, (f + 28), R(6));
    st32(base, (f + 32), R(5));
    st32(base, (f + 36), R(4));
    st32(base, (f + 40), R(0));
    GM_CALLV(0x80B4C5BCu, 0x80B4C710u, 0);
    R(29) = R(3) |R(3);
    R(4) = R(28) |R(28);
    R(3) = (R(26) + 204);
    GM_CALLV(0x80B4C5CCu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 204);
    R(27) = ld32(base, (f + 32));
    R(12) = ld32(base, (f + 36));
    R(4) = (R(31) + -14672);
    R(11) = ld32(base, (f + 40));
    R(5) = (R(26) + 192);
    R(10) = ld32(base, (f + 20));
    R(9) = ld32(base, (f + 24));
    R(8) = ld32(base, (f + 28));
    R(7) = ld32(base, (f + 8));
    R(6) = ld32(base, (f + 12));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 204), R(30));
    st32(base, (R(3) + 48), R(29));
    GM_CALLV(0x80B4C62Cu, 0x80B1CAC0u, 0);
    R(11) = (f + 192);
    R(0) = lr;
}

/* fn_4_2FCC0 (fn_4_2FCC0, 12 bytes) */
static void eb_m_4c710(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 31412);
}

/* fn_4_2FCD0 (fn_4_2FCD0, 12 bytes) */
static void eb_m_4c720(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30900);
}

/* fn_4_31840 (fn_4_31840, 1620 bytes) */
static void eb_m_4e290(GM_CTX) {
    GM_FN(0x80B4E290); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 336);
    R(27) = (0 + 0x80B80000u);
    R(26) = (0 + 0x80B90000u);
    R(27) = (R(27) + 2680);
    R(3) = (R(27) + 1400);
    R(24) = ld32(base, (R(27) + 1400));
    R(6) = (R(27) + 1412);
    R(5) = (R(27) + 1424);
    R(12) = ld32(base, (R(3) + 4));
    R(26) = (R(26) + -14800);
    R(11) = ld32(base, (R(3) + 8));
    R(4) = (R(27) + 1688);
    R(10) = ld32(base, (R(27) + 1412));
    R(3) = (R(26) + 16);
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1424));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 260), R(24));
    st32(base, (f + 264), R(12));
    st32(base, (f + 268), R(11));
    st32(base, (f + 272), R(10));
    st32(base, (f + 276), R(9));
    st32(base, (f + 280), R(8));
    st32(base, (f + 284), R(7));
    st32(base, (f + 288), R(6));
    st32(base, (f + 292), R(0));
    GM_CALLV(0x80B4E314u, 0x8015F7C0u, 0);
    R(28) = (0 + 0x80B80000u);
    R(3) = (R(26) + 16);
    R(24) = ld32(base, (f + 284));
    R(28) = (R(28) + 4740);
    R(12) = ld32(base, (f + 288));
    R(29) = (0 + 0x80B50000u);
    R(11) = ld32(base, (f + 292));
    R(4) = (R(29) + -5904);
    R(10) = ld32(base, (f + 272));
    R(5) = (R(26) + 0);
    R(9) = ld32(base, (f + 276));
    R(8) = ld32(base, (f + 280));
    R(7) = ld32(base, (f + 260));
    R(6) = ld32(base, (f + 264));
    R(0) = ld32(base, (f + 268));
    st32(base, (R(26) + 16), R(28));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B4E37Cu, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 1436);
    R(4) = (R(27) + 1448);
    R(3) = (R(27) + 1460);
    R(11) = ld32(base, (R(27) + 1436));
    R(10) = ld32(base, (R(5) + 4));
    R(30) = (R(27) + 1724);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 1448));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 1460));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 224), R(11));
    st32(base, (f + 228), R(10));
    st32(base, (f + 232), R(9));
    st32(base, (f + 236), R(8));
    st32(base, (f + 240), R(7));
    st32(base, (f + 244), R(6));
    st32(base, (f + 248), R(5));
    st32(base, (f + 252), R(4));
    st32(base, (f + 256), R(0));
    GM_CALLV(0x80B4E3D8u, 0x80B4E9C0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(30) |R(30);
    R(3) = (R(26) + 76);
    GM_CALLV(0x80B4E3E8u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 76);
    R(25) = ld32(base, (f + 248));
    R(12) = ld32(base, (f + 252));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 256));
    R(30) = (R(30) + 4688);
    R(10) = ld32(base, (f + 236));
    R(31) = (0 + 0x80B50000u);
    R(9) = ld32(base, (f + 240));
    R(4) = (R(31) + -5808);
    R(8) = ld32(base, (f + 244));
    R(5) = (R(26) + 64);
    R(7) = ld32(base, (f + 224));
    R(6) = ld32(base, (f + 228));
    R(0) = ld32(base, (f + 232));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 76), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80B4E454u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 1472);
    R(6) = (R(27) + 1484);
    R(5) = (R(27) + 1496);
    R(25) = ld32(base, (R(27) + 1472));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 1764);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 144);
    R(10) = ld32(base, (R(27) + 1484));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1496));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 188), R(25));
    st32(base, (f + 192), R(12));
    st32(base, (f + 196), R(11));
    st32(base, (f + 200), R(10));
    st32(base, (f + 204), R(9));
    st32(base, (f + 208), R(8));
    st32(base, (f + 212), R(7));
    st32(base, (f + 216), R(6));
    st32(base, (f + 220), R(0));
    GM_CALLV(0x80B4E4B4u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 144);
    R(25) = ld32(base, (f + 212));
    R(12) = ld32(base, (f + 216));
    R(4) = (R(29) + -5904);
    R(11) = ld32(base, (f + 220));
    R(5) = (R(26) + 128);
    R(10) = ld32(base, (f + 200));
    R(9) = ld32(base, (f + 204));
    R(8) = ld32(base, (f + 208));
    R(7) = ld32(base, (f + 188));
    R(6) = ld32(base, (f + 192));
    R(0) = ld32(base, (f + 196));
    st32(base, (R(26) + 144), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B4E510u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 1508);
    R(6) = (R(27) + 1520);
    R(5) = (R(27) + 1532);
    R(25) = ld32(base, (R(27) + 1508));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 1800);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 208);
    R(10) = ld32(base, (R(27) + 1520));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1532));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 152), R(25));
    st32(base, (f + 156), R(12));
    st32(base, (f + 160), R(11));
    st32(base, (f + 164), R(10));
    st32(base, (f + 168), R(9));
    st32(base, (f + 172), R(8));
    st32(base, (f + 176), R(7));
    st32(base, (f + 180), R(6));
    st32(base, (f + 184), R(0));
    GM_CALLV(0x80B4E570u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 208);
    R(25) = ld32(base, (f + 176));
    R(12) = ld32(base, (f + 180));
    R(4) = (R(29) + -5904);
    R(11) = ld32(base, (f + 184));
    R(5) = (R(26) + 192);
    R(10) = ld32(base, (f + 164));
    R(9) = ld32(base, (f + 168));
    R(8) = ld32(base, (f + 172));
    R(7) = ld32(base, (f + 152));
    R(6) = ld32(base, (f + 156));
    R(0) = ld32(base, (f + 160));
    st32(base, (R(26) + 208), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B4E5CCu, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 1544);
    R(6) = (R(27) + 1556);
    R(5) = (R(27) + 1568);
    R(25) = ld32(base, (R(27) + 1544));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 1836);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 272);
    R(10) = ld32(base, (R(27) + 1556));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1568));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 116), R(25));
    st32(base, (f + 120), R(12));
    st32(base, (f + 124), R(11));
    st32(base, (f + 128), R(10));
    st32(base, (f + 132), R(9));
    st32(base, (f + 136), R(8));
    st32(base, (f + 140), R(7));
    st32(base, (f + 144), R(6));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x80B4E62Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 272);
    R(25) = ld32(base, (f + 140));
    R(12) = ld32(base, (f + 144));
    R(4) = (R(29) + -5904);
    R(11) = ld32(base, (f + 148));
    R(5) = (R(26) + 256);
    R(10) = ld32(base, (f + 128));
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(26) + 272), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B4E688u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 1580);
    R(6) = (R(27) + 1592);
    R(5) = (R(27) + 1604);
    R(25) = ld32(base, (R(27) + 1580));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 1880);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 336);
    R(10) = ld32(base, (R(27) + 1592));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1604));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 80), R(25));
    st32(base, (f + 84), R(12));
    st32(base, (f + 88), R(11));
    st32(base, (f + 92), R(10));
    st32(base, (f + 96), R(9));
    st32(base, (f + 100), R(8));
    st32(base, (f + 104), R(7));
    st32(base, (f + 108), R(6));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x80B4E6E8u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 336);
    R(25) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(29) + -5904);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(26) + 320);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(26) + 336), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B4E744u, 0x80B1CAC0u, 0);
    R(3) = (R(27) + 1616);
    R(6) = (R(27) + 1628);
    R(5) = (R(27) + 1640);
    R(25) = ld32(base, (R(27) + 1616));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(27) + 1928);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(26) + 400);
    R(10) = ld32(base, (R(27) + 1628));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(27) + 1640));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 44), R(25));
    st32(base, (f + 48), R(12));
    st32(base, (f + 52), R(11));
    st32(base, (f + 56), R(10));
    st32(base, (f + 60), R(9));
    st32(base, (f + 64), R(8));
    st32(base, (f + 68), R(7));
    st32(base, (f + 72), R(6));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x80B4E7A4u, 0x8015F7C0u, 0);
    R(3) = (R(26) + 400);
    R(25) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(29) + -5904);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(26) + 384);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(26) + 400), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B4E800u, 0x80B1CAC0u, 0);
    R(5) = (R(27) + 1652);
    R(4) = (R(27) + 1664);
    R(3) = (R(27) + 1676);
    R(11) = ld32(base, (R(27) + 1652));
    R(10) = ld32(base, (R(5) + 4));
    R(28) = (R(27) + 1972);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(27) + 1664));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(27) + 1676));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 8), R(11));
    st32(base, (f + 12), R(10));
    st32(base, (f + 16), R(9));
    st32(base, (f + 20), R(8));
    st32(base, (f + 24), R(7));
    st32(base, (f + 28), R(6));
    st32(base, (f + 32), R(5));
    st32(base, (f + 36), R(4));
    st32(base, (f + 40), R(0));
    GM_CALLV(0x80B4E85Cu, 0x80B4E9B0u, 0);
    R(29) = R(3) |R(3);
    R(4) = R(28) |R(28);
    R(3) = (R(26) + 460);
    GM_CALLV(0x80B4E86Cu, 0x8015F7C0u, 0);
    R(3) = (R(26) + 460);
    R(27) = ld32(base, (f + 32));
    R(12) = ld32(base, (f + 36));
    R(4) = (R(31) + -5808);
    R(11) = ld32(base, (f + 40));
    R(5) = (R(26) + 448);
    R(10) = ld32(base, (f + 20));
    R(9) = ld32(base, (f + 24));
    R(8) = ld32(base, (f + 28));
    R(7) = ld32(base, (f + 8));
    R(6) = ld32(base, (f + 12));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(26) + 460), R(30));
    st32(base, (R(3) + 48), R(29));
    GM_CALLV(0x80B4E8CCu, 0x80B1CAC0u, 0);
    R(11) = (f + 336);
    R(0) = lr;
}

/* fn_4_31F60 (fn_4_31F60, 12 bytes) */
static void eb_m_4e9b0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 31412);
}

/* fn_4_31F70 (fn_4_31F70, 12 bytes) */
static void eb_m_4e9c0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30900);
}

/* fn_4_343C0 (fn_4_343C0, 1088 bytes) */
static void eb_m_50e10(GM_CTX) {
    GM_FN(0x80B50E10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 224);
    R(28) = (0 + 0x80B80000u);
    R(27) = (0 + 0x80B90000u);
    R(28) = (R(28) + 4792);
    R(5) = (R(28) + 1324);
    R(11) = ld32(base, (R(28) + 1324));
    R(4) = (R(28) + 1336);
    R(3) = (R(28) + 1348);
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(27) + -14288);
    R(9) = ld32(base, (R(5) + 8));
    R(25) = (R(28) + 1504);
    R(8) = ld32(base, (R(28) + 1336));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 1348));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 152), R(11));
    st32(base, (f + 156), R(10));
    st32(base, (f + 160), R(9));
    st32(base, (f + 164), R(8));
    st32(base, (f + 168), R(7));
    st32(base, (f + 172), R(6));
    st32(base, (f + 176), R(5));
    st32(base, (f + 180), R(4));
    st32(base, (f + 184), R(0));
    GM_CALLV(0x80B50E90u, 0x80B51340u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 12);
    GM_CALLV(0x80B50EA0u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 12);
    R(25) = ld32(base, (f + 176));
    R(12) = ld32(base, (f + 180));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 184));
    R(30) = (R(30) + 6488);
    R(10) = ld32(base, (f + 164));
    R(29) = (0 + 0x80B80000u);
    R(9) = ld32(base, (f + 168));
    R(31) = (0 + 0x80B50000u);
    R(8) = ld32(base, (f + 172));
    R(29) = (R(29) + 6540);
    R(7) = ld32(base, (f + 152));
    R(4) = (R(31) + 4784);
    R(6) = ld32(base, (f + 156));
    R(5) = (R(27) + 0);
    R(0) = ld32(base, (f + 160));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 12), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B50F14u, 0x80B1CAC0u, 0);
    R(3) = (R(28) + 1360);
    R(6) = (R(28) + 1372);
    R(5) = (R(28) + 1384);
    R(25) = ld32(base, (R(28) + 1360));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1544);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(27) + 80);
    R(10) = ld32(base, (R(28) + 1372));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1384));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 116), R(25));
    st32(base, (f + 120), R(12));
    st32(base, (f + 124), R(11));
    st32(base, (f + 128), R(10));
    st32(base, (f + 132), R(9));
    st32(base, (f + 136), R(8));
    st32(base, (f + 140), R(7));
    st32(base, (f + 144), R(6));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x80B50F74u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 80);
    R(25) = ld32(base, (f + 140));
    R(12) = ld32(base, (f + 144));
    R(4) = (0 + 0x80B50000u);
    R(11) = ld32(base, (f + 148));
    R(4) = (R(4) + 4688);
    R(10) = ld32(base, (f + 128));
    R(5) = (R(27) + 64);
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(27) + 80), R(29));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80B50FD4u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 1396);
    R(4) = (R(28) + 1408);
    R(3) = (R(28) + 1420);
    R(11) = ld32(base, (R(28) + 1396));
    R(10) = ld32(base, (R(5) + 4));
    R(29) = (R(28) + 1580);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 1408));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 1420));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 80), R(11));
    st32(base, (f + 84), R(10));
    st32(base, (f + 88), R(9));
    st32(base, (f + 92), R(8));
    st32(base, (f + 96), R(7));
    st32(base, (f + 100), R(6));
    st32(base, (f + 104), R(5));
    st32(base, (f + 108), R(4));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x80B51030u, 0x80B51330u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(29) |R(29);
    R(3) = (R(27) + 140);
    GM_CALLV(0x80B51040u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 140);
    R(25) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(31) + 4784);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(27) + 128);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 140), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B510A0u, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 1432);
    R(4) = (R(28) + 1444);
    R(3) = (R(28) + 1456);
    R(11) = ld32(base, (R(28) + 1432));
    R(10) = ld32(base, (R(5) + 4));
    R(29) = (R(28) + 1620);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 1444));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 1456));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 44), R(11));
    st32(base, (f + 48), R(10));
    st32(base, (f + 52), R(9));
    st32(base, (f + 56), R(8));
    st32(base, (f + 60), R(7));
    st32(base, (f + 64), R(6));
    st32(base, (f + 68), R(5));
    st32(base, (f + 72), R(4));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x80B510FCu, 0x80B51320u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(29) |R(29);
    R(3) = (R(27) + 204);
    GM_CALLV(0x80B5110Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 204);
    R(26) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(31) + 4784);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(27) + 192);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 204), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B5116Cu, 0x80B1CAC0u, 0);
    R(5) = (R(28) + 1468);
    R(4) = (R(28) + 1480);
    R(3) = (R(28) + 1492);
    R(11) = ld32(base, (R(28) + 1468));
    R(10) = ld32(base, (R(5) + 4));
    R(29) = (R(28) + 1660);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(28) + 1480));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(28) + 1492));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 8), R(11));
    st32(base, (f + 12), R(10));
    st32(base, (f + 16), R(9));
    st32(base, (f + 20), R(8));
    st32(base, (f + 24), R(7));
    st32(base, (f + 28), R(6));
    st32(base, (f + 32), R(5));
    st32(base, (f + 36), R(4));
    st32(base, (f + 40), R(0));
    GM_CALLV(0x80B511C8u, 0x80B51310u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(29) |R(29);
    R(3) = (R(27) + 268);
    GM_CALLV(0x80B511D8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 268);
    R(28) = ld32(base, (f + 32));
    R(12) = ld32(base, (f + 36));
    R(4) = (R(31) + 4784);
    R(11) = ld32(base, (f + 40));
    R(5) = (R(27) + 256);
    R(10) = ld32(base, (f + 20));
    R(9) = ld32(base, (f + 24));
    R(8) = ld32(base, (f + 28));
    R(7) = ld32(base, (f + 8));
    R(6) = ld32(base, (f + 12));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(3) + 12), R(28));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 268), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B51238u, 0x80B1CAC0u, 0);
    R(11) = (f + 224);
    R(0) = lr;
}

/* fn_4_348C0 (fn_4_348C0, 12 bytes) */
static void eb_m_51310(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 31412);
}

/* fn_4_348D0 (fn_4_348D0, 12 bytes) */
static void eb_m_51320(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 31092);
}

/* fn_4_348E0 (fn_4_348E0, 12 bytes) */
static void eb_m_51330(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30900);
}

/* fn_4_348F0 (fn_4_348F0, 12 bytes) */
static void eb_m_51340(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30836);
}

/* fn_4_34BE0 (fn_4_34BE0, 92 bytes) */
static void eb_m_51630(GM_CTX) {
    GM_FN(0x80B51630); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 3736);
    GM_CALLV(0x80B51648u, 0x801628C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80B51674; }
    GM_CALLV(0x80B51658u, 0x800A88A0u, 0);
    R(4) = (0 + 0x80B80000u);
    R(3) = (0 + 0x80B80000u);
    R(4) = (R(4) + 7828);
    st32(base, (R(31) + 96), R(4));
    R(3) = (R(3) + 9416);
    st32(base, (R(31) + 3700), R(3));
    st32(base, (R(31) + 3704), R(31));
L_80B51674:;
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_4_34C40 (fn_4_34C40, 12 bytes) */
static void eb_m_51690(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_34C50 (fn_4_34C50, 12 bytes) */
static void eb_m_516a0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_34C60 (fn_4_34C60, 12 bytes) */
static void eb_m_516b0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_34C70 (fn_4_34C70, 12 bytes) */
static void eb_m_516c0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_34C80 (fn_4_34C80, 12 bytes) */
static void eb_m_516d0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_34C90 (fn_4_34C90, 12 bytes) */
static void eb_m_516e0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_34CA0 (fn_4_34CA0, 384 bytes) */
static void eb_m_516f0(GM_CTX) {
    GM_FN(0x80B516F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80B70000u);
    R(31) = (R(31) + 19432);
    R(30) = (0 + 0x80B80000u);
    R(30) = (R(30) + 6592);
    R(29) = R(3) |R(3);
    R(3) = (R(3) + 1540);
    R(4) = (R(29) + 3700);
    GM_CALLV(0x80B51728u, 0x8016A000u, 0);
    { uint32_t ea_ = (R(31) + 188); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = R(29) |R(29);
    { uint32_t ea_ = (R(31) + 192); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(4) = (R(29) + 172);
    { uint32_t ea_ = (R(31) + 200); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 196); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 204); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 220); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(29) + 224); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(29) + 228); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(29) + 800); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(29) + 804); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(29) + 792); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 796); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 208); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(29) + 212); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 216); stfs(base, ea_, ctx->f[3].d); }
    GM_CALLV(0x80B51770u, 0x80096240u, 0);
    st8(base, (R(29) + 840), R(3));
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(29) + 96));
    R(12) = ld32(base, (R(12) + 1312));
    ctx->ctr = R(12);
    GM_CALLV(0x80B51788u, ctx->ctr, 0);
    R(4) = (0 + 0x80430000u);
    R(0) = ld8(base, (R(29) + 840));
    R(4) = (R(4) + -15968);
    R(0) = ld8(base, (R(4) + R(0)));
    R(0) = (int8_t)R(0);
    R(0) = ((int32_t)R(0) * (int32_t)R(3));
    st16(base, (R(29) + 258), R(0));
    GM_CALLV(0x80B517A8u, 0x800B30C0u, 0);
    { uint32_t ea_ = (R(31) + 208); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(31) + 212); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(12) = (R(30) + 32);
    R(11) = (R(30) + 72);
    R(10) = (R(30) + 188);
    R(9) = (R(30) + 288);
    R(8) = (R(30) + 440);
    R(7) = (R(31) + 112);
    R(6) = (R(30) + 816);
    { uint32_t ea_ = (R(29) + 2112); stfs(base, ea_, ctx->f[1].d); }
    R(4) = R(29) |R(29);
    R(3) = (R(29) + 328);
    R(5) = (R(31) + 76);
    { uint32_t ea_ = (R(29) + 2116); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(29) + 1872), R(12));
    st32(base, (R(29) + 1876), R(11));
    st32(base, (R(29) + 1880), R(10));
    st32(base, (R(29) + 1884), R(9));
    st32(base, (R(29) + 1888), R(8));
    st32(base, (R(29) + 2800), R(7));
    st32(base, (R(29) + 3692), R(6));
    st32(base, (R(29) + 2772), R(0));
    st32(base, (R(29) + 2768), R(0));
    GM_CALLV(0x80B5180Cu, 0x8008C3E0u, 0);
    R(4) = (R(30) + 936);
    R(3) = (R(29) + 328);
    { uint32_t ea_ = (R(4) + 100); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 356); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 360); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + 108); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 364); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 368); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x80B51838u, 0x8008C330u, 0);
    R(4) = R(29) |R(29);
    R(3) = (R(29) + 492);
    R(5) = (R(31) + 12);
    R(6) = (R(31) + 0);
    R(7) = (R(31) + 24);
    GM_CALLV(0x80B51850u, 0x8006D090u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_4_34E20 (fn_4_34E20, 464 bytes) */
static void eb_m_51870(GM_CTX) {
    GM_FN(0x80B51870); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(30) = (0 + 0x80B80000u);
    R(30) = (R(30) + 6592);
    R(29) = R(3) |R(3);
    R(5) = (R(30) + 1072);
    R(6) = ld32(base, (R(4) + -24520));
    R(4) = (R(30) + 1088);
    R(3) = (R(6) + 4);
    GM_CALLV(0x80B518ACu, 0x800DF180u, 0);
    st32(base, (R(29) + 1536), R(3));
    R(3) = (R(29) + 1536);
    R(4) = (R(30) + 1088);
    GM_CALLV(0x80B518BCu, 0x80239E30u, 0);
    st32(base, (f + 44), R(3));
    R(31) = R(3) |R(3);
    R(3) = (R(29) + 1540);
    R(4) = (f + 44);
    R(5) = (R(29) + 1316);
    R(6) = (0 + 299);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x80B518E0u, 0x80169D90u, 0);
    R(3) = (R(29) + 1540);
    GM_CALLV(0x80B518E8u, 0x80064C00u, 0);
    R(3) = (R(29) + 1536);
    R(4) = (R(30) + 1096);
    GM_CALLV(0x80B518F4u, 0x8023A0B0u, 0);
    st32(base, (f + 36), R(3));
    R(3) = (R(29) + 1604);
    R(4) = (f + 40);
    R(5) = (f + 36);
    st32(base, (f + 40), R(31));
    R(6) = (R(29) + 1316);
    R(7) = (0 + 0);
    GM_CALLV(0x80B51914u, 0x801650D0u, 0);
    R(3) = (R(29) + 1536);
    R(4) = (R(30) + 1104);
    GM_CALLV(0x80B51920u, 0x8023A200u, 0);
    st32(base, (R(29) + 1704), R(3));
    R(4) = (f + 32);
    R(5) = (f + 28);
    R(6) = (R(29) + 1316);
    st32(base, (f + 28), R(3));
    R(3) = (R(29) + 1708);
    R(7) = (0 + 0);
    R(8) = (0 + 1);
    st32(base, (f + 32), R(31));
    GM_CALLV(0x80B51948u, 0x80166830u, 0);
    R(0) = ld32(base, (R(29) + 1704));
    R(3) = (R(29) + 1708);
    st32(base, (f + 48), R(0));
    R(4) = (R(29) + 1540);
    R(5) = (f + 48);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x80B51968u, 0x80166BD0u, 0);
    R(3) = (R(29) + 1536);
    R(4) = (R(30) + 1112);
    GM_CALLV(0x80B51974u, 0x8023A190u, 0);
    st32(base, (f + 20), R(3));
    R(3) = (R(29) + 1660);
    R(4) = (f + 24);
    R(5) = (f + 20);
    st32(base, (f + 24), R(31));
    R(6) = (R(29) + 1316);
    R(7) = (0 + 0);
    R(8) = (0 + 2);
    GM_CALLV(0x80B51998u, 0x80165C30u, 0);
    R(12) = ld32(base, (R(29) + 1540));
    R(3) = (R(29) + 1540);
    R(4) = (R(29) + 1660);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x80B519B0u, ctx->ctr, 0);
    R(3) = (R(29) + 1660);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x80B519C0u, 0x80166340u, 0);
    R(3) = (R(29) + 1536);
    R(4) = (R(30) + 1120);
    GM_CALLV(0x80B519CCu, 0x80239E30u, 0);
    st32(base, (f + 16), R(3));
    R(31) = R(3) |R(3);
    R(3) = (R(29) + 1752);
    R(4) = (f + 16);
    R(5) = (R(29) + 1316);
    R(6) = (0 + 32);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x80B519F0u, 0x80169D90u, 0);
    R(3) = (R(29) + 1752);
    GM_CALLV(0x80B519F8u, 0x80064C00u, 0);
    R(3) = (R(29) + 1536);
    R(4) = (R(30) + 1132);
    GM_CALLV(0x80B51A04u, 0x8023A0B0u, 0);
    st32(base, (f + 8), R(3));
    R(3) = (R(29) + 1816);
    R(4) = (f + 12);
    R(5) = (f + 8);
    st32(base, (f + 12), R(31));
    R(6) = (R(29) + 1316);
    R(7) = (0 + 0);
    GM_CALLV(0x80B51A24u, 0x801650D0u, 0);
    R(0) = lr;
}

/* fn_4_34FF0 (fn_4_34FF0, 76 bytes) */
static void eb_m_51a40(GM_CTX) {
    GM_FN(0x80B51A40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 916));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    R(3) = (R(3) + 916);
    GM_CALLV(0x80B51A68u, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x80B51A74u, 0x80064F50u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_4_35040 (fn_4_35040, 4 bytes) */
static void eb_m_51a90(GM_CTX) {

}

/* fn_4_35050 (fn_4_35050, 8 bytes) */
static void eb_m_51aa0(GM_CTX) {
    R(3) = (0 + 1);
}

/* fn_4_35060 (fn_4_35060, 308 bytes) */
static void eb_m_51ab0(GM_CTX) {
    GM_FN(0x80B51AB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 1);
    R(4) = (f + 20);
    R(31) = (0 + 0x80B70000u);
    R(31) = (R(31) + 19432);
    R(30) = R(3) |R(3);
    { uint32_t ea_ = (R(3) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    R(0) = (int16_t)ld16(base, (R(3) + 256));
    st16(base, (f + 20), R(0));
    R(0) = (int16_t)ld16(base, (R(3) + 258));
    st16(base, (f + 22), R(0));
    R(0) = (int16_t)ld16(base, (R(3) + 260));
    R(3) = (f + 28);
    st16(base, (f + 24), R(0));
    GM_CALLV(0x80B51B10u, 0x80064AF0u, 0);
    { uint32_t ea_ = (f + 36); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (R(30) + 124);
    { uint32_t ea_ = (f + 32); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x80B51B24u, 0x801C0BD0u, 0);
    R(0) = ld16(base, (f + 22));
    R(3) = (R(30) + 124);
    st16(base, (f + 16), R(0));
    R(4) = (f + 16);
    GM_CALLV(0x80B51B38u, 0x8016EDD0u, 0);
    { uint32_t ea_ = (R(31) + 192); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 88);
    { uint32_t ea_ = (R(31) + 204); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[1].u;
    GM_CALLV(0x80B51B4Cu, 0x801C0BD0u, 0);
    R(3) = (R(30) + 124);
    R(4) = (f + 88);
    R(5) = R(3) |R(3);
    GM_CALLV(0x80B51B5Cu, 0x801C0540u, 0);
    R(0) = ld16(base, (f + 20));
    R(3) = (R(30) + 124);
    st16(base, (f + 12), R(0));
    R(4) = (f + 12);
    GM_CALLV(0x80B51B70u, 0x8016ECB0u, 0);
    { uint32_t ea_ = (R(31) + 192); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 40);
    { uint32_t ea_ = (R(31) + 216); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[1].u;
    GM_CALLV(0x80B51B84u, 0x801C0BD0u, 0);
    R(3) = (R(30) + 124);
    R(4) = (f + 40);
    R(5) = R(3) |R(3);
    GM_CALLV(0x80B51B94u, 0x801C0540u, 0);
    R(0) = ld16(base, (f + 24));
    R(3) = (R(30) + 124);
    st16(base, (f + 8), R(0));
    R(4) = (f + 8);
    GM_CALLV(0x80B51BA8u, 0x8016EEF0u, 0);
    R(3) = (R(30) + 1540);
    R(4) = (R(30) + 124);
    GM_CALLV(0x80B51BB4u, 0x8016A170u, 0);
    R(3) = (R(30) + 1540);
    R(4) = (R(30) + 220);
    GM_CALLV(0x80B51BC0u, 0x8016A150u, 0);
    R(3) = (R(30) + 1540);
    R(4) = (0 + 0);
    GM_CALLV(0x80B51BCCu, 0x8016A1A0u, 0);
    R(0) = lr;
}

/* fn_4_352E0 (fn_4_352E0, 16 bytes) */
static void eb_m_51d30(GM_CTX) {
    { uint32_t ea_ = R(3) + 1540; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_4_35300 (fn_4_35300, 88 bytes) */
static void eb_m_51d50(GM_CTX) {
    GM_FN(0x80B51D50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = (R(4) + 1540);
    GM_CALLV(0x80B51D74u, 0x80168400u, 0);
    R(3) = (R(31) + 1540);
    R(5) = (f + 8);
    R(4) = (0 + 17);
    GM_CALLV(0x80B51D84u, 0x80168180u, 0);
    R(4) = R(30) |R(30);
    R(3) = (f + 8);
    GM_CALLV(0x80B51D90u, 0x8016F130u, 0);
    R(0) = lr;
}

/* fn_4_35360 (fn_4_35360, 148 bytes) */
static void eb_m_51db0(GM_CTX) {
    GM_FN(0x80B51DB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = (R(3) + 1540);
    GM_CALLV(0x80B51DCCu, 0x80168400u, 0);
    R(3) = (R(31) + 1540);
    R(5) = (f + 24);
    R(4) = (0 + 8);
    GM_CALLV(0x80B51DDCu, 0x80168180u, 0);
    R(3) = (f + 24);
    R(4) = (f + 8);
    GM_CALLV(0x80B51DE8u, 0x8016F130u, 0);
    R(3) = (0 + 0x80B80000u);
    { uint32_t ea_ = (f + 12); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (R(3) + 7528);
    { uint32_t ea_ = (f + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 100); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d + ctx->f[2].d);
    { uint32_t ea_ = (R(31) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 360); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 356); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 108); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 364); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 368); stfs(base, ea_, ctx->f[1].d); }
    R(0) = lr;
}

/* fn_4_35400 (fn_4_35400, 116 bytes) */
static void eb_m_51e50(GM_CTX) {
    R(6) = ld32(base, (R(3) + 1876));
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) return;
    R(4) = (0 + 0x80B80000u);
    { uint32_t ea_ = (R(4) + 7528); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (R(4) + 7528);
    { uint32_t ea_ = (R(6) + 20); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld32(base, (R(3) + 1876));
    { uint32_t ea_ = (R(5) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 24); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld32(base, (R(3) + 1876));
    { uint32_t ea_ = (R(5) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 28); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld32(base, (R(3) + 1876));
    { uint32_t ea_ = (R(5) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 32); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld32(base, (R(3) + 1876));
    { uint32_t ea_ = (R(5) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 36); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld32(base, (R(3) + 1876));
    { uint32_t ea_ = (R(5) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 40); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld32(base, (R(3) + 1876));
    { uint32_t ea_ = (R(5) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[0].d); }
    R(3) = ld32(base, (R(3) + 1876));
    { uint32_t ea_ = (R(5) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_4_35480 (fn_4_35480, 100 bytes) */
static void eb_m_51ed0(GM_CTX) {
    GM_FN(0x80B51ED0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = R(3) |R(3);
    R(7) = (0 + 0);
    R(6) = (f + 8);
    R(8) = (0 + 0);
    R(5) = ld32(base, (R(3) + 1892));
    { uint32_t ea_ = (R(3) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (0 + 262);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B51F10u, 0x80064680u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B51F20; }
    R(3) = (0 + 0);
    goto L_80B51F24;
L_80B51F20:;
    R(3) = ld32(base, (R(3) + 0));
L_80B51F24:;
    R(0) = lr;
}

/* fn_4_354F0 (fn_4_354F0, 76 bytes) */
static void eb_m_51f40(GM_CTX) {
    GM_FN(0x80B51F40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(3) + 1904));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B51F60; }
    R(3) = (0 + 0);
    goto L_80B51F64;
L_80B51F60:;
    GM_CALLV(0x80B51F64u, 0x80162D00u, 0);
L_80B51F64:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B51F7C; }
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 284));
    ctx->ctr = R(12);
    GM_CALLV(0x80B51F7Cu, ctx->ctr, 0);
L_80B51F7C:;
    R(0) = lr;
}

/* fn_4_35540 (fn_4_35540, 16 bytes) */
static void eb_m_51f90(GM_CTX) {
    R(3) = (0 + 0x80B80000u);
    R(3) = (R(3) + 7528);
    { uint32_t ea_ = (R(3) + 48); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_4_35550 (fn_4_35550, 140 bytes) */
static void eb_m_51fa0(GM_CTX) {
    GM_FN(0x80B51FA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 1892));
    GM_CALLV(0x80B51FC0u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80B52014; }
    R(3) = ld32(base, (R(31) + 1904));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B51FE0; }
    R(31) = (0 + 0);
    goto L_80B51FE8;
L_80B51FE0:;
    GM_CALLV(0x80B51FE4u, 0x80162D00u, 0);
    R(31) = R(3) |R(3);
L_80B51FE8:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B52014; }
    R(4) = R(30) |R(30);
    R(3) = (f + 8);
    GM_CALLV(0x80B51FFCu, 0x8006CED0u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = (f + 8);
    R(12) = ld32(base, (R(12) + 296));
    ctx->ctr = R(12);
    GM_CALLV(0x80B52014u, ctx->ctr, 0);
L_80B52014:;
    R(0) = lr;
}

/* fn_4_35680 (fn_4_35680, 52 bytes) */
static void eb_m_520d0(GM_CTX) {
    R(0) = ld8(base, (R(3) + 840));
    R(5) = (0 + 0x80B70000u);
    R(5) = (R(5) + 19432);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(5) + 240); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (R(5) + 232);
    { uint32_t ea_ = (R(5) + 244); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + R(0)); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1976); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 1980); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 1984); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 1988); stfs(base, ea_, ctx->f[1].d); }
}

/* fn_4_356C0 (fn_4_356C0, 148 bytes) */
static void eb_m_52110(GM_CTX) {
    GM_FN(0x80B52110); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 1);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 1528));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 12));
    ctx->ctr = R(12);
    GM_CALLV(0x80B52140u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B52168; }
    R(3) = ld32(base, (R(30) + 1528));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x80B5215Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B52168; }
    R(31) = (0 + 0);
L_80B52168:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B52180; }
    R(3) = (0 + 0x80B80000u);
    R(3) = (R(3) + 7528);
    R(3) = (int16_t)ld16(base, (R(3) + 42));
    goto L_80B5218C;
L_80B52180:;
    R(3) = (0 + 0x80B80000u);
    R(3) = (R(3) + 7528);
    R(3) = (int16_t)ld16(base, (R(3) + 44));
L_80B5218C:;
    R(0) = lr;
}

/* fn_4_35760 (fn_4_35760, 16 bytes) */
static void eb_m_521b0(GM_CTX) {
    R(3) = (0 + 0x80B80000u);
    R(3) = (R(3) + 7528);
    R(3) = (int16_t)ld16(base, (R(3) + 40));
}

/* fn_4_35770 (fn_4_35770, 16 bytes) */
static void eb_m_521c0(GM_CTX) {
    R(3) = (0 + 0x80B80000u);
    R(3) = (R(3) + 7528);
    { uint32_t ea_ = (R(3) + 68); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_4_357B0 (fn_4_357B0, 148 bytes) */
static void eb_m_52200(GM_CTX) {
    GM_FN(0x80B52200); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 1);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 1528));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 12));
    ctx->ctr = R(12);
    GM_CALLV(0x80B52230u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B52258; }
    R(3) = ld32(base, (R(30) + 1528));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x80B5224Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B52258; }
    R(31) = (0 + 0);
L_80B52258:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B52270; }
    R(3) = (0 + 0x80B80000u);
    R(3) = (R(3) + 7528);
    { uint32_t ea_ = (R(3) + 32); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_80B5227C;
L_80B52270:;
    R(3) = (0 + 0x80B80000u);
    R(3) = (R(3) + 7528);
    { uint32_t ea_ = (R(3) + 36); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_80B5227C:;
    R(0) = lr;
}

/* fn_4_35890 (fn_4_35890, 16 bytes) */
static void eb_m_522e0(GM_CTX) {
    R(3) = (0 + 0x80B80000u);
    R(3) = (R(3) + 7528);
    R(3) = (int16_t)ld16(base, (R(3) + 76));
}

/* fn_4_358A0 (fn_4_358A0, 236 bytes) */
static void eb_m_522f0(GM_CTX) {
    GM_FN(0x80B522F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80B70000u);
    R(31) = (R(31) + 19432);
    R(30) = R(3) |R(3);
    { uint32_t ea_ = (R(31) + 240); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 1604);
    GM_CALLV(0x80B5231Cu, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B5234C; }
    { uint32_t ea_ = (R(31) + 248); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 1604);
    GM_CALLV(0x80B52330u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B5234C; }
    { uint32_t ea_ = (R(31) + 252); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 1604);
    GM_CALLV(0x80B52344u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B5236C; }
L_80B5234C:;
    R(12) = ld32(base, (R(30) + 1348));
    R(3) = (R(30) + 1348);
    R(4) = (0 + 1314);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 36));
    ctx->ctr = R(12);
    GM_CALLV(0x80B52368u, ctx->ctr, 0);
    goto L_80B523C4;
L_80B5236C:;
    { uint32_t ea_ = (R(31) + 256); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 1604);
    GM_CALLV(0x80B52378u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B523A8; }
    { uint32_t ea_ = (R(31) + 260); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 1604);
    GM_CALLV(0x80B5238Cu, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B523A8; }
    { uint32_t ea_ = (R(31) + 264); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 1604);
    GM_CALLV(0x80B523A0u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B523C4; }
L_80B523A8:;
    R(12) = ld32(base, (R(30) + 1348));
    R(3) = (R(30) + 1348);
    R(4) = (0 + 1288);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 36));
    ctx->ctr = R(12);
    GM_CALLV(0x80B523C4u, ctx->ctr, 0);
L_80B523C4:;
    R(0) = lr;
}

/* fn_4_35990 (fn_4_35990, 92 bytes) */
static void eb_m_523e0(GM_CTX) {
    GM_FN(0x80B523E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80B80000u);
    R(5) = (0 + 0);
    R(4) = (R(4) + 7740);
    R(6) = (f + 8);
    R(7) = (0 + 0);
    { uint32_t ea_ = (R(3) + 2776); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(8) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 2780); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 2784); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = R(3) + 2804; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 160));
    ctx->ctr = R(12);
    GM_CALLV(0x80B5242Cu, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_4_36E70 (fn_4_36E70, 208 bytes) */
static void eb_m_538c0(GM_CTX) {
    GM_FN(0x80B538C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(3) |R(3);
    R(3) = R(6) |R(6);
    GM_CALLV(0x80B538ECu, 0x8023B300u, 0);
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B53900; }
    R(3) = R(3) + R(0);
    goto L_80B53904;
L_80B53900:;
    R(3) = (0 + 0);
L_80B53904:;
    R(4) = (0 + 0x80B80000u);
    R(4) = (R(4) + 7820);
    GM_CALLV(0x80B53910u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B53970; }
    R(3) = ld32(base, (R(30) + 4));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 24), R(0));
    R(4) = (0 + 0x80B70000u);
    R(0) = (int16_t)ld16(base, (R(3) + 1936));
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 19712); ctx->f[1].u = ld64(base, ea_); }
    R(4) = (f + 8);
    R(0) = ((int32_t)R(0) * 90);
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0x3FFFu) != 0; R(0) = (v_ >> 14); }
    { uint64_t t_ = (uint64_t)(R(0)) + (0) + ctx->xer_ca; R(0) = t_; ctx->xer_ca = (t_ >> 32); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 28), R(0));
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[0].d - ctx->f[1].d);
    GM_CALLV(0x80B53958u, 0x80241710u, 0);
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    R(4) = (f + 8);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[31].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B53970u, 0x80241AA0u, 0);
L_80B53970:;
    R(0) = lr;
}

/* fn_4_36F40 (fn_4_36F40, 2216 bytes) */
static void eb_m_53990(GM_CTX) {
    GM_FN(0x80B53990); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 432);
    R(28) = (0 + 0x80B90000u);
    R(29) = (0 + 0x80B80000u);
    R(28) = (R(28) + -13968);
    R(26) = (0 + 0x80B70000u);
    R(0) = ld8(base, (R(28) + 576));
    R(26) = (R(26) + 19432);
    { uint32_t ea_ = (R(26) + 188); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(29) = (R(29) + 6592);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    { uint32_t ea_ = (R(26) + 416); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(25) = (R(29) + 72);
    { uint32_t ea_ = (R(26) + 272); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(26) + 420); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = (0 + 1104);
    { uint32_t ea_ = (R(26) + 424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(10) = (R(29) + 816);
    R(9) = (0 + 1097);
    R(11) = (0 + 1105);
    R(8) = (0 + 1106);
    R(7) = (0 + 1107);
    R(6) = (0 + 1098);
    R(5) = (0 + 1099);
    R(4) = (0 + 1100);
    R(3) = (0 + 1101);
    R(0) = (0 + 1102);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(25) + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(25) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(25) + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(25) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(25) + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(25) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(25) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(25) + 48); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(29) + 816), R(12));
    st32(base, (R(10) + 8), R(11));
    st32(base, (R(10) + 16), R(9));
    st32(base, (R(10) + 24), R(8));
    st32(base, (R(10) + 32), R(9));
    st32(base, (R(10) + 40), R(7));
    st32(base, (R(10) + 48), R(6));
    st32(base, (R(10) + 56), R(5));
    st32(base, (R(10) + 64), R(4));
    st32(base, (R(10) + 72), R(3));
    st32(base, (R(10) + 80), R(9));
    st32(base, (R(10) + 88), R(0));
    st32(base, (R(10) + 96), R(9));
    st32(base, (R(10) + 104), R(9));
    st32(base, (R(10) + 112), R(9));
    if ((!CR_BIT(ctx, 2))) { goto L_80B53AE8; }
    { uint32_t ea_ = (R(26) + 240); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(29) + 936);
    { uint32_t ea_ = (R(26) + 192); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(26) + 428); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(26) + 412); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(26) + 432); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 100); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 112); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(28) + 576), R(0));
L_80B53AE8:;
    R(5) = (R(29) + 3000);
    R(4) = (R(29) + 3012);
    R(3) = (R(29) + 3024);
    R(11) = ld32(base, (R(29) + 3000));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(29) + 3324);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3012));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3024));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 360), R(11));
    st32(base, (f + 364), R(10));
    st32(base, (f + 368), R(9));
    st32(base, (f + 372), R(8));
    st32(base, (f + 376), R(7));
    st32(base, (f + 380), R(6));
    st32(base, (f + 384), R(5));
    st32(base, (f + 388), R(4));
    st32(base, (f + 392), R(0));
    GM_CALLV(0x80B53B44u, 0x80B51690u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(28) + 12);
    GM_CALLV(0x80B53B54u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 12);
    R(25) = ld32(base, (f + 384));
    R(12) = ld32(base, (f + 388));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 392));
    R(30) = (R(30) + 10260);
    R(10) = ld32(base, (f + 372));
    R(31) = (0 + 0x80B50000u);
    R(9) = ld32(base, (f + 376));
    R(4) = (R(31) + 17056);
    R(8) = ld32(base, (f + 380));
    R(5) = (R(28) + 0);
    R(7) = ld32(base, (f + 360));
    R(6) = ld32(base, (f + 364));
    R(0) = ld32(base, (f + 368));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 12), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B53BC0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3036);
    R(4) = (R(29) + 3048);
    R(3) = (R(29) + 3060);
    R(11) = ld32(base, (R(29) + 3036));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3356);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3048));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3060));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 324), R(11));
    st32(base, (f + 328), R(10));
    st32(base, (f + 332), R(9));
    st32(base, (f + 336), R(8));
    st32(base, (f + 340), R(7));
    st32(base, (f + 344), R(6));
    st32(base, (f + 348), R(5));
    st32(base, (f + 352), R(4));
    st32(base, (f + 356), R(0));
    GM_CALLV(0x80B53C1Cu, 0x80B54320u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 76);
    GM_CALLV(0x80B53C2Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 76);
    R(25) = ld32(base, (f + 348));
    R(12) = ld32(base, (f + 352));
    R(4) = (R(31) + 17056);
    R(11) = ld32(base, (f + 356));
    R(5) = (R(28) + 64);
    R(10) = ld32(base, (f + 336));
    R(9) = ld32(base, (f + 340));
    R(8) = ld32(base, (f + 344));
    R(7) = ld32(base, (f + 324));
    R(6) = ld32(base, (f + 328));
    R(0) = ld32(base, (f + 332));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 76), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B53C8Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3072);
    R(4) = (R(29) + 3084);
    R(3) = (R(29) + 3096);
    R(11) = ld32(base, (R(29) + 3072));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3392);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3084));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3096));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 288), R(11));
    st32(base, (f + 292), R(10));
    st32(base, (f + 296), R(9));
    st32(base, (f + 300), R(8));
    st32(base, (f + 304), R(7));
    st32(base, (f + 308), R(6));
    st32(base, (f + 312), R(5));
    st32(base, (f + 316), R(4));
    st32(base, (f + 320), R(0));
    GM_CALLV(0x80B53CE8u, 0x80B516A0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 140);
    GM_CALLV(0x80B53CF8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 140);
    R(25) = ld32(base, (f + 312));
    R(12) = ld32(base, (f + 316));
    R(4) = (R(31) + 17056);
    R(11) = ld32(base, (f + 320));
    R(5) = (R(28) + 128);
    R(10) = ld32(base, (f + 300));
    R(9) = ld32(base, (f + 304));
    R(8) = ld32(base, (f + 308));
    R(7) = ld32(base, (f + 288));
    R(6) = ld32(base, (f + 292));
    R(0) = ld32(base, (f + 296));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 140), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B53D58u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3108);
    R(4) = (R(29) + 3120);
    R(3) = (R(29) + 3132);
    R(11) = ld32(base, (R(29) + 3108));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3428);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3120));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3132));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 252), R(11));
    st32(base, (f + 256), R(10));
    st32(base, (f + 260), R(9));
    st32(base, (f + 264), R(8));
    st32(base, (f + 268), R(7));
    st32(base, (f + 272), R(6));
    st32(base, (f + 276), R(5));
    st32(base, (f + 280), R(4));
    st32(base, (f + 284), R(0));
    GM_CALLV(0x80B53DB4u, 0x80B516B0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 204);
    GM_CALLV(0x80B53DC4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 204);
    R(25) = ld32(base, (f + 276));
    R(12) = ld32(base, (f + 280));
    R(4) = (R(31) + 17056);
    R(11) = ld32(base, (f + 284));
    R(5) = (R(28) + 192);
    R(10) = ld32(base, (f + 264));
    R(9) = ld32(base, (f + 268));
    R(8) = ld32(base, (f + 272));
    R(7) = ld32(base, (f + 252));
    R(6) = ld32(base, (f + 256));
    R(0) = ld32(base, (f + 260));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 204), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B53E24u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3144);
    R(4) = (R(29) + 3156);
    R(3) = (R(29) + 3168);
    R(11) = ld32(base, (R(29) + 3144));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3464);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3156));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3168));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 216), R(11));
    st32(base, (f + 220), R(10));
    st32(base, (f + 224), R(9));
    st32(base, (f + 228), R(8));
    st32(base, (f + 232), R(7));
    st32(base, (f + 236), R(6));
    st32(base, (f + 240), R(5));
    st32(base, (f + 244), R(4));
    st32(base, (f + 248), R(0));
    GM_CALLV(0x80B53E80u, 0x80B54310u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 268);
    GM_CALLV(0x80B53E90u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 268);
    R(25) = ld32(base, (f + 240));
    R(12) = ld32(base, (f + 244));
    R(4) = (R(31) + 17056);
    R(11) = ld32(base, (f + 248));
    R(5) = (R(28) + 256);
    R(10) = ld32(base, (f + 228));
    R(9) = ld32(base, (f + 232));
    R(8) = ld32(base, (f + 236));
    R(7) = ld32(base, (f + 216));
    R(6) = ld32(base, (f + 220));
    R(0) = ld32(base, (f + 224));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 268), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B53EF0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3180);
    R(4) = (R(29) + 3192);
    R(3) = (R(29) + 3204);
    R(11) = ld32(base, (R(29) + 3180));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3504);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3192));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3204));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 180), R(11));
    st32(base, (f + 184), R(10));
    st32(base, (f + 188), R(9));
    st32(base, (f + 192), R(8));
    st32(base, (f + 196), R(7));
    st32(base, (f + 200), R(6));
    st32(base, (f + 204), R(5));
    st32(base, (f + 208), R(4));
    st32(base, (f + 212), R(0));
    GM_CALLV(0x80B53F4Cu, 0x80B516C0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 332);
    GM_CALLV(0x80B53F5Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 332);
    R(25) = ld32(base, (f + 204));
    R(12) = ld32(base, (f + 208));
    R(4) = (R(31) + 17056);
    R(11) = ld32(base, (f + 212));
    R(5) = (R(28) + 320);
    R(10) = ld32(base, (f + 192));
    R(9) = ld32(base, (f + 196));
    R(8) = ld32(base, (f + 200));
    R(7) = ld32(base, (f + 180));
    R(6) = ld32(base, (f + 184));
    R(0) = ld32(base, (f + 188));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 332), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B53FBCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3216);
    R(4) = (R(29) + 3228);
    R(3) = (R(29) + 3240);
    R(11) = ld32(base, (R(29) + 3216));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3548);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3228));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3240));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 144), R(11));
    st32(base, (f + 148), R(10));
    st32(base, (f + 152), R(9));
    st32(base, (f + 156), R(8));
    st32(base, (f + 160), R(7));
    st32(base, (f + 164), R(6));
    st32(base, (f + 168), R(5));
    st32(base, (f + 172), R(4));
    st32(base, (f + 176), R(0));
    GM_CALLV(0x80B54018u, 0x80B516D0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 396);
    GM_CALLV(0x80B54028u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 396);
    R(26) = ld32(base, (f + 168));
    R(12) = ld32(base, (f + 172));
    R(4) = (R(31) + 17056);
    R(11) = ld32(base, (f + 176));
    R(5) = (R(28) + 384);
    R(10) = ld32(base, (f + 156));
    R(9) = ld32(base, (f + 160));
    R(8) = ld32(base, (f + 164));
    R(7) = ld32(base, (f + 144));
    R(6) = ld32(base, (f + 148));
    R(0) = ld32(base, (f + 152));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 396), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B54088u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3252);
    R(4) = (R(29) + 3264);
    R(3) = (R(29) + 3276);
    R(11) = ld32(base, (R(29) + 3252));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3592);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3264));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3276));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 108), R(11));
    st32(base, (f + 112), R(10));
    st32(base, (f + 116), R(9));
    st32(base, (f + 120), R(8));
    st32(base, (f + 124), R(7));
    st32(base, (f + 128), R(6));
    st32(base, (f + 132), R(5));
    st32(base, (f + 136), R(4));
    st32(base, (f + 140), R(0));
    GM_CALLV(0x80B540E4u, 0x80B54300u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 460);
    GM_CALLV(0x80B540F4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 460);
    R(27) = ld32(base, (f + 132));
    R(12) = ld32(base, (f + 136));
    R(4) = (R(31) + 17056);
    R(11) = ld32(base, (f + 140));
    R(5) = (R(28) + 448);
    R(10) = ld32(base, (f + 120));
    R(9) = ld32(base, (f + 124));
    R(8) = ld32(base, (f + 128));
    R(7) = ld32(base, (f + 108));
    R(6) = ld32(base, (f + 112));
    R(0) = ld32(base, (f + 116));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 460), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B54154u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3288);
    R(4) = (R(29) + 3300);
    R(3) = (R(29) + 3312);
    R(11) = ld32(base, (R(29) + 3288));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3628);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3300));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3312));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 72), R(11));
    st32(base, (f + 76), R(10));
    st32(base, (f + 80), R(9));
    st32(base, (f + 84), R(8));
    st32(base, (f + 88), R(7));
    st32(base, (f + 92), R(6));
    st32(base, (f + 96), R(5));
    st32(base, (f + 100), R(4));
    st32(base, (f + 104), R(0));
    GM_CALLV(0x80B541B0u, 0x80B516E0u, 0);
    R(29) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 524);
    GM_CALLV(0x80B541C0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 524);
    R(27) = ld32(base, (f + 96));
    R(12) = ld32(base, (f + 100));
    R(4) = (R(31) + 17056);
    R(11) = ld32(base, (f + 104));
    R(5) = (R(28) + 512);
    R(10) = ld32(base, (f + 84));
    R(9) = ld32(base, (f + 88));
    R(8) = ld32(base, (f + 92));
    R(7) = ld32(base, (f + 72));
    R(6) = ld32(base, (f + 76));
    R(0) = ld32(base, (f + 80));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 524), R(30));
    st32(base, (R(3) + 48), R(29));
    GM_CALLV(0x80B54220u, 0x80B1CAC0u, 0);
    R(11) = (f + 432);
    R(0) = lr;
}

/* fn_4_378B0 (fn_4_378B0, 12 bytes) */
static void eb_m_54300(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31356);
}

/* fn_4_378C0 (fn_4_378C0, 12 bytes) */
static void eb_m_54310(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30716);
}

/* fn_4_378D0 (fn_4_378D0, 12 bytes) */
static void eb_m_54320(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_37C70 (fn_4_37C70, 12 bytes) */
static void eb_m_546c0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_37C80 (fn_4_37C80, 12 bytes) */
static void eb_m_546d0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_37C90 (fn_4_37C90, 12 bytes) */
static void eb_m_546e0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_37CA0 (fn_4_37CA0, 12 bytes) */
static void eb_m_546f0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_37CB0 (fn_4_37CB0, 12 bytes) */
static void eb_m_54700(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_37CC0 (fn_4_37CC0, 12 bytes) */
static void eb_m_54710(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_37CD0 (fn_4_37CD0, 12 bytes) */
static void eb_m_54720(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_37CE0 (fn_4_37CE0, 12 bytes) */
static void eb_m_54730(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_37CF0 (fn_4_37CF0, 12 bytes) */
static void eb_m_54740(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3BD30 (fn_4_3BD30, 4872 bytes) */
static void eb_m_58780(GM_CTX) {
    GM_FN(0x80B58780); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 896);
    R(28) = (0 + 0x80B90000u);
    R(29) = (0 + 0x80B80000u);
    R(28) = (R(28) + -13384);
    R(27) = (0 + 0x80B70000u);
    R(0) = ld8(base, (R(28) + 1408));
    R(27) = (R(27) + 20000);
    { uint32_t ea_ = (R(27) + 224); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(29) = (R(29) + 10368);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    { uint32_t ea_ = (R(27) + 332); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(26) = (R(29) + 64);
    { uint32_t ea_ = (R(27) + 316); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 464); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(25) = (0 + 1145);
    { uint32_t ea_ = (R(27) + 468); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(11) = (R(29) + 792);
    R(8) = (0 + 1097);
    R(12) = (0 + 1146);
    R(10) = (0 + 1147);
    R(9) = (0 + 1148);
    R(7) = (0 + 1149);
    R(6) = (0 + 1136);
    R(5) = (0 + 1139);
    R(4) = (0 + 1141);
    R(3) = (0 + 1142);
    R(0) = (0 + 1143);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(26) + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(26) + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(26) + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(26) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 48); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(29) + 792), R(25));
    st32(base, (R(11) + 8), R(12));
    st32(base, (R(11) + 16), R(10));
    st32(base, (R(11) + 24), R(9));
    st32(base, (R(11) + 32), R(8));
    st32(base, (R(11) + 40), R(7));
    st32(base, (R(11) + 48), R(6));
    st32(base, (R(11) + 56), R(5));
    st32(base, (R(11) + 64), R(4));
    st32(base, (R(11) + 72), R(3));
    st32(base, (R(11) + 80), R(8));
    st32(base, (R(11) + 88), R(0));
    st32(base, (R(11) + 96), R(8));
    st32(base, (R(11) + 104), R(8));
    st32(base, (R(11) + 112), R(8));
    if ((!CR_BIT(ctx, 2))) { goto L_80B588DC; }
    { uint32_t ea_ = (R(27) + 220); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (R(29) + 912);
    { uint32_t ea_ = (R(27) + 436); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(27) + 268); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 472); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 232); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 132); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 140); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 144); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 148); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(28) + 1408), R(0));
L_80B588DC:;
    R(5) = (R(29) + 3040);
    R(4) = (R(29) + 3052);
    R(3) = (R(29) + 3064);
    R(11) = ld32(base, (R(29) + 3040));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(29) + 3832);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3052));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3064));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 828), R(11));
    st32(base, (f + 832), R(10));
    st32(base, (f + 836), R(9));
    st32(base, (f + 840), R(8));
    st32(base, (f + 844), R(7));
    st32(base, (f + 848), R(6));
    st32(base, (f + 852), R(5));
    st32(base, (f + 856), R(4));
    st32(base, (f + 860), R(0));
    GM_CALLV(0x80B58938u, 0x80B546C0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(28) + 12);
    GM_CALLV(0x80B58948u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 12);
    R(25) = ld32(base, (f + 852));
    R(12) = ld32(base, (f + 856));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 860));
    R(30) = (R(30) + 15024);
    R(10) = ld32(base, (f + 840));
    R(31) = (0 + 0x80B60000u);
    R(9) = ld32(base, (f + 844));
    R(4) = (R(31) + -25872);
    R(8) = ld32(base, (f + 848));
    R(5) = (R(28) + 0);
    R(7) = ld32(base, (f + 828));
    R(6) = ld32(base, (f + 832));
    R(0) = ld32(base, (f + 836));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 12), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B589B4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3076);
    R(4) = (R(29) + 3088);
    R(3) = (R(29) + 3100);
    R(11) = ld32(base, (R(29) + 3076));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3868);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3088));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3100));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 792), R(11));
    st32(base, (f + 796), R(10));
    st32(base, (f + 800), R(9));
    st32(base, (f + 804), R(8));
    st32(base, (f + 808), R(7));
    st32(base, (f + 812), R(6));
    st32(base, (f + 816), R(5));
    st32(base, (f + 820), R(4));
    st32(base, (f + 824), R(0));
    GM_CALLV(0x80B58A10u, 0x80B546D0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 76);
    GM_CALLV(0x80B58A20u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 76);
    R(25) = ld32(base, (f + 816));
    R(12) = ld32(base, (f + 820));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 824));
    R(5) = (R(28) + 64);
    R(10) = ld32(base, (f + 804));
    R(9) = ld32(base, (f + 808));
    R(8) = ld32(base, (f + 812));
    R(7) = ld32(base, (f + 792));
    R(6) = ld32(base, (f + 796));
    R(0) = ld32(base, (f + 800));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 76), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B58A80u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3112);
    R(4) = (R(29) + 3124);
    R(3) = (R(29) + 3136);
    R(11) = ld32(base, (R(29) + 3112));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3900);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3124));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3136));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 756), R(11));
    st32(base, (f + 760), R(10));
    st32(base, (f + 764), R(9));
    st32(base, (f + 768), R(8));
    st32(base, (f + 772), R(7));
    st32(base, (f + 776), R(6));
    st32(base, (f + 780), R(5));
    st32(base, (f + 784), R(4));
    st32(base, (f + 788), R(0));
    GM_CALLV(0x80B58ADCu, 0x80B546E0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 140);
    GM_CALLV(0x80B58AECu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 140);
    R(25) = ld32(base, (f + 780));
    R(12) = ld32(base, (f + 784));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 788));
    R(5) = (R(28) + 128);
    R(10) = ld32(base, (f + 768));
    R(9) = ld32(base, (f + 772));
    R(8) = ld32(base, (f + 776));
    R(7) = ld32(base, (f + 756));
    R(6) = ld32(base, (f + 760));
    R(0) = ld32(base, (f + 764));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 140), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B58B4Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3148);
    R(4) = (R(29) + 3160);
    R(3) = (R(29) + 3172);
    R(11) = ld32(base, (R(29) + 3148));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3936);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3160));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3172));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 720), R(11));
    st32(base, (f + 724), R(10));
    st32(base, (f + 728), R(9));
    st32(base, (f + 732), R(8));
    st32(base, (f + 736), R(7));
    st32(base, (f + 740), R(6));
    st32(base, (f + 744), R(5));
    st32(base, (f + 748), R(4));
    st32(base, (f + 752), R(0));
    GM_CALLV(0x80B58BA8u, 0x80B546F0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 204);
    GM_CALLV(0x80B58BB8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 204);
    R(25) = ld32(base, (f + 744));
    R(12) = ld32(base, (f + 748));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 752));
    R(5) = (R(28) + 192);
    R(10) = ld32(base, (f + 732));
    R(9) = ld32(base, (f + 736));
    R(8) = ld32(base, (f + 740));
    R(7) = ld32(base, (f + 720));
    R(6) = ld32(base, (f + 724));
    R(0) = ld32(base, (f + 728));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 204), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B58C18u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3184);
    R(4) = (R(29) + 3196);
    R(3) = (R(29) + 3208);
    R(11) = ld32(base, (R(29) + 3184));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3968);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3196));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3208));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 684), R(11));
    st32(base, (f + 688), R(10));
    st32(base, (f + 692), R(9));
    st32(base, (f + 696), R(8));
    st32(base, (f + 700), R(7));
    st32(base, (f + 704), R(6));
    st32(base, (f + 708), R(5));
    st32(base, (f + 712), R(4));
    st32(base, (f + 716), R(0));
    GM_CALLV(0x80B58C74u, 0x80B59C10u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 268);
    GM_CALLV(0x80B58C84u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 268);
    R(25) = ld32(base, (f + 708));
    R(12) = ld32(base, (f + 712));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 716));
    R(5) = (R(28) + 256);
    R(10) = ld32(base, (f + 696));
    R(9) = ld32(base, (f + 700));
    R(8) = ld32(base, (f + 704));
    R(7) = ld32(base, (f + 684));
    R(6) = ld32(base, (f + 688));
    R(0) = ld32(base, (f + 692));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 268), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B58CE4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3220);
    R(4) = (R(29) + 3232);
    R(3) = (R(29) + 3244);
    R(11) = ld32(base, (R(29) + 3220));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4008);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3232));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3244));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 648), R(11));
    st32(base, (f + 652), R(10));
    st32(base, (f + 656), R(9));
    st32(base, (f + 660), R(8));
    st32(base, (f + 664), R(7));
    st32(base, (f + 668), R(6));
    st32(base, (f + 672), R(5));
    st32(base, (f + 676), R(4));
    st32(base, (f + 680), R(0));
    GM_CALLV(0x80B58D40u, 0x80B59C00u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 332);
    GM_CALLV(0x80B58D50u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 332);
    R(25) = ld32(base, (f + 672));
    R(12) = ld32(base, (f + 676));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 680));
    R(5) = (R(28) + 320);
    R(10) = ld32(base, (f + 660));
    R(9) = ld32(base, (f + 664));
    R(8) = ld32(base, (f + 668));
    R(7) = ld32(base, (f + 648));
    R(6) = ld32(base, (f + 652));
    R(0) = ld32(base, (f + 656));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 332), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B58DB0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3256);
    R(4) = (R(29) + 3268);
    R(3) = (R(29) + 3280);
    R(11) = ld32(base, (R(29) + 3256));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4048);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3268));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3280));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 612), R(11));
    st32(base, (f + 616), R(10));
    st32(base, (f + 620), R(9));
    st32(base, (f + 624), R(8));
    st32(base, (f + 628), R(7));
    st32(base, (f + 632), R(6));
    st32(base, (f + 636), R(5));
    st32(base, (f + 640), R(4));
    st32(base, (f + 644), R(0));
    GM_CALLV(0x80B58E0Cu, 0x80B59BF0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 396);
    GM_CALLV(0x80B58E1Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 396);
    R(25) = ld32(base, (f + 636));
    R(12) = ld32(base, (f + 640));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 644));
    R(5) = (R(28) + 384);
    R(10) = ld32(base, (f + 624));
    R(9) = ld32(base, (f + 628));
    R(8) = ld32(base, (f + 632));
    R(7) = ld32(base, (f + 612));
    R(6) = ld32(base, (f + 616));
    R(0) = ld32(base, (f + 620));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 396), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B58E7Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3292);
    R(4) = (R(29) + 3304);
    R(3) = (R(29) + 3316);
    R(11) = ld32(base, (R(29) + 3292));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4080);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3304));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3316));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 576), R(11));
    st32(base, (f + 580), R(10));
    st32(base, (f + 584), R(9));
    st32(base, (f + 588), R(8));
    st32(base, (f + 592), R(7));
    st32(base, (f + 596), R(6));
    st32(base, (f + 600), R(5));
    st32(base, (f + 604), R(4));
    st32(base, (f + 608), R(0));
    GM_CALLV(0x80B58ED8u, 0x80B59BE0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 460);
    GM_CALLV(0x80B58EE8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 460);
    R(25) = ld32(base, (f + 600));
    R(12) = ld32(base, (f + 604));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 608));
    R(5) = (R(28) + 448);
    R(10) = ld32(base, (f + 588));
    R(9) = ld32(base, (f + 592));
    R(8) = ld32(base, (f + 596));
    R(7) = ld32(base, (f + 576));
    R(6) = ld32(base, (f + 580));
    R(0) = ld32(base, (f + 584));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 460), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B58F48u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3328);
    R(4) = (R(29) + 3340);
    R(3) = (R(29) + 3352);
    R(11) = ld32(base, (R(29) + 3328));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4116);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3340));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3352));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 540), R(11));
    st32(base, (f + 544), R(10));
    st32(base, (f + 548), R(9));
    st32(base, (f + 552), R(8));
    st32(base, (f + 556), R(7));
    st32(base, (f + 560), R(6));
    st32(base, (f + 564), R(5));
    st32(base, (f + 568), R(4));
    st32(base, (f + 572), R(0));
    GM_CALLV(0x80B58FA4u, 0x80B59BD0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 524);
    GM_CALLV(0x80B58FB4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 524);
    R(25) = ld32(base, (f + 564));
    R(12) = ld32(base, (f + 568));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 572));
    R(5) = (R(28) + 512);
    R(10) = ld32(base, (f + 552));
    R(9) = ld32(base, (f + 556));
    R(8) = ld32(base, (f + 560));
    R(7) = ld32(base, (f + 540));
    R(6) = ld32(base, (f + 544));
    R(0) = ld32(base, (f + 548));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 524), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B59014u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3364);
    R(4) = (R(29) + 3376);
    R(3) = (R(29) + 3388);
    R(11) = ld32(base, (R(29) + 3364));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4152);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3376));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3388));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 504), R(11));
    st32(base, (f + 508), R(10));
    st32(base, (f + 512), R(9));
    st32(base, (f + 516), R(8));
    st32(base, (f + 520), R(7));
    st32(base, (f + 524), R(6));
    st32(base, (f + 528), R(5));
    st32(base, (f + 532), R(4));
    st32(base, (f + 536), R(0));
    GM_CALLV(0x80B59070u, 0x80B54700u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 588);
    GM_CALLV(0x80B59080u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 588);
    R(25) = ld32(base, (f + 528));
    R(12) = ld32(base, (f + 532));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 536));
    R(5) = (R(28) + 576);
    R(10) = ld32(base, (f + 516));
    R(9) = ld32(base, (f + 520));
    R(8) = ld32(base, (f + 524));
    R(7) = ld32(base, (f + 504));
    R(6) = ld32(base, (f + 508));
    R(0) = ld32(base, (f + 512));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 588), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B590E0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3400);
    R(4) = (R(29) + 3412);
    R(3) = (R(29) + 3424);
    R(11) = ld32(base, (R(29) + 3400));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4192);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3412));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3424));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 468), R(11));
    st32(base, (f + 472), R(10));
    st32(base, (f + 476), R(9));
    st32(base, (f + 480), R(8));
    st32(base, (f + 484), R(7));
    st32(base, (f + 488), R(6));
    st32(base, (f + 492), R(5));
    st32(base, (f + 496), R(4));
    st32(base, (f + 500), R(0));
    GM_CALLV(0x80B5913Cu, 0x80B59BC0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 652);
    GM_CALLV(0x80B5914Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 652);
    R(25) = ld32(base, (f + 492));
    R(12) = ld32(base, (f + 496));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 500));
    R(5) = (R(28) + 640);
    R(10) = ld32(base, (f + 480));
    R(9) = ld32(base, (f + 484));
    R(8) = ld32(base, (f + 488));
    R(7) = ld32(base, (f + 468));
    R(6) = ld32(base, (f + 472));
    R(0) = ld32(base, (f + 476));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 652), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B591ACu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3436);
    R(4) = (R(29) + 3448);
    R(3) = (R(29) + 3460);
    R(11) = ld32(base, (R(29) + 3436));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4228);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3448));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3460));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 432), R(11));
    st32(base, (f + 436), R(10));
    st32(base, (f + 440), R(9));
    st32(base, (f + 444), R(8));
    st32(base, (f + 448), R(7));
    st32(base, (f + 452), R(6));
    st32(base, (f + 456), R(5));
    st32(base, (f + 460), R(4));
    st32(base, (f + 464), R(0));
    GM_CALLV(0x80B59208u, 0x80B59BB0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 716);
    GM_CALLV(0x80B59218u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 716);
    R(25) = ld32(base, (f + 456));
    R(12) = ld32(base, (f + 460));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 464));
    R(5) = (R(28) + 704);
    R(10) = ld32(base, (f + 444));
    R(9) = ld32(base, (f + 448));
    R(8) = ld32(base, (f + 452));
    R(7) = ld32(base, (f + 432));
    R(6) = ld32(base, (f + 436));
    R(0) = ld32(base, (f + 440));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 716), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B59278u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3472);
    R(4) = (R(29) + 3484);
    R(3) = (R(29) + 3496);
    R(11) = ld32(base, (R(29) + 3472));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4264);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3484));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3496));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 396), R(11));
    st32(base, (f + 400), R(10));
    st32(base, (f + 404), R(9));
    st32(base, (f + 408), R(8));
    st32(base, (f + 412), R(7));
    st32(base, (f + 416), R(6));
    st32(base, (f + 420), R(5));
    st32(base, (f + 424), R(4));
    st32(base, (f + 428), R(0));
    GM_CALLV(0x80B592D4u, 0x80B59BA0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 780);
    GM_CALLV(0x80B592E4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 780);
    R(25) = ld32(base, (f + 420));
    R(12) = ld32(base, (f + 424));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 428));
    R(5) = (R(28) + 768);
    R(10) = ld32(base, (f + 408));
    R(9) = ld32(base, (f + 412));
    R(8) = ld32(base, (f + 416));
    R(7) = ld32(base, (f + 396));
    R(6) = ld32(base, (f + 400));
    R(0) = ld32(base, (f + 404));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 780), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B59344u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3508);
    R(4) = (R(29) + 3520);
    R(3) = (R(29) + 3532);
    R(11) = ld32(base, (R(29) + 3508));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4300);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3520));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3532));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 360), R(11));
    st32(base, (f + 364), R(10));
    st32(base, (f + 368), R(9));
    st32(base, (f + 372), R(8));
    st32(base, (f + 376), R(7));
    st32(base, (f + 380), R(6));
    st32(base, (f + 384), R(5));
    st32(base, (f + 388), R(4));
    st32(base, (f + 392), R(0));
    GM_CALLV(0x80B593A0u, 0x80B59B90u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 844);
    GM_CALLV(0x80B593B0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 844);
    R(25) = ld32(base, (f + 384));
    R(12) = ld32(base, (f + 388));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 392));
    R(5) = (R(28) + 832);
    R(10) = ld32(base, (f + 372));
    R(9) = ld32(base, (f + 376));
    R(8) = ld32(base, (f + 380));
    R(7) = ld32(base, (f + 360));
    R(6) = ld32(base, (f + 364));
    R(0) = ld32(base, (f + 368));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 844), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B59410u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3544);
    R(4) = (R(29) + 3556);
    R(3) = (R(29) + 3568);
    R(11) = ld32(base, (R(29) + 3544));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4336);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3556));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3568));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 324), R(11));
    st32(base, (f + 328), R(10));
    st32(base, (f + 332), R(9));
    st32(base, (f + 336), R(8));
    st32(base, (f + 340), R(7));
    st32(base, (f + 344), R(6));
    st32(base, (f + 348), R(5));
    st32(base, (f + 352), R(4));
    st32(base, (f + 356), R(0));
    GM_CALLV(0x80B5946Cu, 0x80B59B80u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 908);
    GM_CALLV(0x80B5947Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 908);
    R(25) = ld32(base, (f + 348));
    R(12) = ld32(base, (f + 352));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 356));
    R(5) = (R(28) + 896);
    R(10) = ld32(base, (f + 336));
    R(9) = ld32(base, (f + 340));
    R(8) = ld32(base, (f + 344));
    R(7) = ld32(base, (f + 324));
    R(6) = ld32(base, (f + 328));
    R(0) = ld32(base, (f + 332));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 908), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B594DCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3580);
    R(4) = (R(29) + 3592);
    R(3) = (R(29) + 3604);
    R(11) = ld32(base, (R(29) + 3580));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4376);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3592));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3604));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 288), R(11));
    st32(base, (f + 292), R(10));
    st32(base, (f + 296), R(9));
    st32(base, (f + 300), R(8));
    st32(base, (f + 304), R(7));
    st32(base, (f + 308), R(6));
    st32(base, (f + 312), R(5));
    st32(base, (f + 316), R(4));
    st32(base, (f + 320), R(0));
    GM_CALLV(0x80B59538u, 0x80B59B70u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 972);
    GM_CALLV(0x80B59548u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 972);
    R(25) = ld32(base, (f + 312));
    R(12) = ld32(base, (f + 316));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 320));
    R(5) = (R(28) + 960);
    R(10) = ld32(base, (f + 300));
    R(9) = ld32(base, (f + 304));
    R(8) = ld32(base, (f + 308));
    R(7) = ld32(base, (f + 288));
    R(6) = ld32(base, (f + 292));
    R(0) = ld32(base, (f + 296));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 972), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B595A8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3616);
    R(4) = (R(29) + 3628);
    R(3) = (R(29) + 3640);
    R(11) = ld32(base, (R(29) + 3616));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4416);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3628));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3640));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 252), R(11));
    st32(base, (f + 256), R(10));
    st32(base, (f + 260), R(9));
    st32(base, (f + 264), R(8));
    st32(base, (f + 268), R(7));
    st32(base, (f + 272), R(6));
    st32(base, (f + 276), R(5));
    st32(base, (f + 280), R(4));
    st32(base, (f + 284), R(0));
    GM_CALLV(0x80B59604u, 0x80B59B60u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1036);
    GM_CALLV(0x80B59614u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1036);
    R(25) = ld32(base, (f + 276));
    R(12) = ld32(base, (f + 280));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 284));
    R(5) = (R(28) + 1024);
    R(10) = ld32(base, (f + 264));
    R(9) = ld32(base, (f + 268));
    R(8) = ld32(base, (f + 272));
    R(7) = ld32(base, (f + 252));
    R(6) = ld32(base, (f + 256));
    R(0) = ld32(base, (f + 260));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1036), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B59674u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3652);
    R(4) = (R(29) + 3664);
    R(3) = (R(29) + 3676);
    R(11) = ld32(base, (R(29) + 3652));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4456);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3664));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3676));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 216), R(11));
    st32(base, (f + 220), R(10));
    st32(base, (f + 224), R(9));
    st32(base, (f + 228), R(8));
    st32(base, (f + 232), R(7));
    st32(base, (f + 236), R(6));
    st32(base, (f + 240), R(5));
    st32(base, (f + 244), R(4));
    st32(base, (f + 248), R(0));
    GM_CALLV(0x80B596D0u, 0x80B54710u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1100);
    GM_CALLV(0x80B596E0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1100);
    R(25) = ld32(base, (f + 240));
    R(12) = ld32(base, (f + 244));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 248));
    R(5) = (R(28) + 1088);
    R(10) = ld32(base, (f + 228));
    R(9) = ld32(base, (f + 232));
    R(8) = ld32(base, (f + 236));
    R(7) = ld32(base, (f + 216));
    R(6) = ld32(base, (f + 220));
    R(0) = ld32(base, (f + 224));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1100), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B59740u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3688);
    R(4) = (R(29) + 3700);
    R(3) = (R(29) + 3712);
    R(11) = ld32(base, (R(29) + 3688));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4492);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3700));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3712));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 180), R(11));
    st32(base, (f + 184), R(10));
    st32(base, (f + 188), R(9));
    st32(base, (f + 192), R(8));
    st32(base, (f + 196), R(7));
    st32(base, (f + 200), R(6));
    st32(base, (f + 204), R(5));
    st32(base, (f + 208), R(4));
    st32(base, (f + 212), R(0));
    GM_CALLV(0x80B5979Cu, 0x80B54720u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1164);
    GM_CALLV(0x80B597ACu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1164);
    R(25) = ld32(base, (f + 204));
    R(12) = ld32(base, (f + 208));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 212));
    R(5) = (R(28) + 1152);
    R(10) = ld32(base, (f + 192));
    R(9) = ld32(base, (f + 196));
    R(8) = ld32(base, (f + 200));
    R(7) = ld32(base, (f + 180));
    R(6) = ld32(base, (f + 184));
    R(0) = ld32(base, (f + 188));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1164), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5980Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3724);
    R(4) = (R(29) + 3736);
    R(3) = (R(29) + 3748);
    R(11) = ld32(base, (R(29) + 3724));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4528);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3736));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3748));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 144), R(11));
    st32(base, (f + 148), R(10));
    st32(base, (f + 152), R(9));
    st32(base, (f + 156), R(8));
    st32(base, (f + 160), R(7));
    st32(base, (f + 164), R(6));
    st32(base, (f + 168), R(5));
    st32(base, (f + 172), R(4));
    st32(base, (f + 176), R(0));
    GM_CALLV(0x80B59868u, 0x80B59B50u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1228);
    GM_CALLV(0x80B59878u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1228);
    R(26) = ld32(base, (f + 168));
    R(12) = ld32(base, (f + 172));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 176));
    R(5) = (R(28) + 1216);
    R(10) = ld32(base, (f + 156));
    R(9) = ld32(base, (f + 160));
    R(8) = ld32(base, (f + 164));
    R(7) = ld32(base, (f + 144));
    R(6) = ld32(base, (f + 148));
    R(0) = ld32(base, (f + 152));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1228), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B598D8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3760);
    R(4) = (R(29) + 3772);
    R(3) = (R(29) + 3784);
    R(11) = ld32(base, (R(29) + 3760));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4568);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3772));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3784));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 108), R(11));
    st32(base, (f + 112), R(10));
    st32(base, (f + 116), R(9));
    st32(base, (f + 120), R(8));
    st32(base, (f + 124), R(7));
    st32(base, (f + 128), R(6));
    st32(base, (f + 132), R(5));
    st32(base, (f + 136), R(4));
    st32(base, (f + 140), R(0));
    GM_CALLV(0x80B59934u, 0x80B54730u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1292);
    GM_CALLV(0x80B59944u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1292);
    R(27) = ld32(base, (f + 132));
    R(12) = ld32(base, (f + 136));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 140));
    R(5) = (R(28) + 1280);
    R(10) = ld32(base, (f + 120));
    R(9) = ld32(base, (f + 124));
    R(8) = ld32(base, (f + 128));
    R(7) = ld32(base, (f + 108));
    R(6) = ld32(base, (f + 112));
    R(0) = ld32(base, (f + 116));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1292), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B599A4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3796);
    R(4) = (R(29) + 3808);
    R(3) = (R(29) + 3820);
    R(11) = ld32(base, (R(29) + 3796));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4612);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3808));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3820));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 72), R(11));
    st32(base, (f + 76), R(10));
    st32(base, (f + 80), R(9));
    st32(base, (f + 84), R(8));
    st32(base, (f + 88), R(7));
    st32(base, (f + 92), R(6));
    st32(base, (f + 96), R(5));
    st32(base, (f + 100), R(4));
    st32(base, (f + 104), R(0));
    GM_CALLV(0x80B59A00u, 0x80B54740u, 0);
    R(29) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1356);
    GM_CALLV(0x80B59A10u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1356);
    R(27) = ld32(base, (f + 96));
    R(12) = ld32(base, (f + 100));
    R(4) = (R(31) + -25872);
    R(11) = ld32(base, (f + 104));
    R(5) = (R(28) + 1344);
    R(10) = ld32(base, (f + 84));
    R(9) = ld32(base, (f + 88));
    R(8) = ld32(base, (f + 92));
    R(7) = ld32(base, (f + 72));
    R(6) = ld32(base, (f + 76));
    R(0) = ld32(base, (f + 80));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1356), R(30));
    st32(base, (R(3) + 48), R(29));
    GM_CALLV(0x80B59A70u, 0x80B1CAC0u, 0);
    R(11) = (f + 896);
    R(0) = lr;
}

/* fn_4_3D100 (fn_4_3D100, 12 bytes) */
static void eb_m_59b50(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30716);
}

/* fn_4_3D110 (fn_4_3D110, 12 bytes) */
static void eb_m_59b60(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30780);
}

/* fn_4_3D120 (fn_4_3D120, 12 bytes) */
static void eb_m_59b70(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30844);
}

/* fn_4_3D130 (fn_4_3D130, 12 bytes) */
static void eb_m_59b80(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30908);
}

/* fn_4_3D140 (fn_4_3D140, 12 bytes) */
static void eb_m_59b90(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_3D150 (fn_4_3D150, 12 bytes) */
static void eb_m_59ba0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31036);
}

/* fn_4_3D160 (fn_4_3D160, 12 bytes) */
static void eb_m_59bb0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_3D170 (fn_4_3D170, 12 bytes) */
static void eb_m_59bc0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31292);
}

/* fn_4_3D180 (fn_4_3D180, 12 bytes) */
static void eb_m_59bd0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31356);
}

/* fn_4_3D190 (fn_4_3D190, 12 bytes) */
static void eb_m_59be0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31868);
}

/* fn_4_3D1A0 (fn_4_3D1A0, 12 bytes) */
static void eb_m_59bf0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31932);
}

/* fn_4_3D1B0 (fn_4_3D1B0, 12 bytes) */
static void eb_m_59c00(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31996);
}

/* fn_4_3D1C0 (fn_4_3D1C0, 12 bytes) */
static void eb_m_59c10(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32060);
}

/* fn_4_3D530 (fn_4_3D530, 12 bytes) */
static void eb_m_59f80(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D540 (fn_4_3D540, 12 bytes) */
static void eb_m_59f90(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D550 (fn_4_3D550, 12 bytes) */
static void eb_m_59fa0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D560 (fn_4_3D560, 12 bytes) */
static void eb_m_59fb0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D570 (fn_4_3D570, 12 bytes) */
static void eb_m_59fc0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D580 (fn_4_3D580, 12 bytes) */
static void eb_m_59fd0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D590 (fn_4_3D590, 12 bytes) */
static void eb_m_59fe0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D5A0 (fn_4_3D5A0, 12 bytes) */
static void eb_m_59ff0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D5B0 (fn_4_3D5B0, 12 bytes) */
static void eb_m_5a000(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D5C0 (fn_4_3D5C0, 12 bytes) */
static void eb_m_5a010(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D5D0 (fn_4_3D5D0, 12 bytes) */
static void eb_m_5a020(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D5E0 (fn_4_3D5E0, 12 bytes) */
static void eb_m_5a030(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D5F0 (fn_4_3D5F0, 12 bytes) */
static void eb_m_5a040(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D600 (fn_4_3D600, 12 bytes) */
static void eb_m_5a050(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D610 (fn_4_3D610, 12 bytes) */
static void eb_m_5a060(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D620 (fn_4_3D620, 12 bytes) */
static void eb_m_5a070(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_3D630 (fn_4_3D630, 12 bytes) */
static void eb_m_5a080(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_41490 (fn_4_41490, 4872 bytes) */
static void eb_m_5dee0(GM_CTX) {
    GM_FN(0x80B5DEE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 896);
    R(28) = (0 + 0x80B90000u);
    R(29) = (0 + 0x80B80000u);
    R(28) = (R(28) + -11968);
    R(27) = (0 + 0x80B70000u);
    R(0) = ld8(base, (R(28) + 1408));
    R(27) = (R(27) + 20648);
    { uint32_t ea_ = (R(27) + 216); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(29) = (R(29) + 15128);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    { uint32_t ea_ = (R(27) + 452); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(26) = (R(29) + 72);
    { uint32_t ea_ = (R(27) + 332); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 456); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(25) = (0 + 1231);
    { uint32_t ea_ = (R(27) + 460); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(11) = (R(29) + 800);
    R(8) = (0 + 1097);
    R(12) = (0 + 1232);
    R(10) = (0 + 1233);
    R(9) = (0 + 1234);
    R(7) = (0 + 1235);
    R(6) = (0 + 1221);
    R(5) = (0 + 1225);
    R(4) = (0 + 1227);
    R(3) = (0 + 1228);
    R(0) = (0 + 1229);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(26) + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(26) + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(26) + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(26) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 48); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(29) + 800), R(25));
    st32(base, (R(11) + 8), R(12));
    st32(base, (R(11) + 16), R(10));
    st32(base, (R(11) + 24), R(9));
    st32(base, (R(11) + 32), R(8));
    st32(base, (R(11) + 40), R(7));
    st32(base, (R(11) + 48), R(6));
    st32(base, (R(11) + 56), R(5));
    st32(base, (R(11) + 64), R(4));
    st32(base, (R(11) + 72), R(3));
    st32(base, (R(11) + 80), R(8));
    st32(base, (R(11) + 88), R(0));
    st32(base, (R(11) + 96), R(8));
    st32(base, (R(11) + 104), R(8));
    st32(base, (R(11) + 112), R(8));
    if ((!CR_BIT(ctx, 2))) { goto L_80B5E03C; }
    { uint32_t ea_ = (R(27) + 228); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(29) + 920);
    { uint32_t ea_ = (R(27) + 220); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(27) + 464); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 436); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 428); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 100); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 112); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(28) + 1408), R(0));
L_80B5E03C:;
    R(5) = (R(29) + 3184);
    R(4) = (R(29) + 3196);
    R(3) = (R(29) + 3208);
    R(11) = ld32(base, (R(29) + 3184));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(29) + 3976);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3196));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3208));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 828), R(11));
    st32(base, (f + 832), R(10));
    st32(base, (f + 836), R(9));
    st32(base, (f + 840), R(8));
    st32(base, (f + 844), R(7));
    st32(base, (f + 848), R(6));
    st32(base, (f + 852), R(5));
    st32(base, (f + 856), R(4));
    st32(base, (f + 860), R(0));
    GM_CALLV(0x80B5E098u, 0x80B59F80u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(28) + 12);
    GM_CALLV(0x80B5E0A8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 12);
    R(25) = ld32(base, (f + 852));
    R(12) = ld32(base, (f + 856));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 860));
    R(30) = (R(30) + 19940);
    R(10) = ld32(base, (f + 840));
    R(31) = (0 + 0x80B60000u);
    R(9) = ld32(base, (f + 844));
    R(4) = (R(31) + -3504);
    R(8) = ld32(base, (f + 848));
    R(5) = (R(28) + 0);
    R(7) = ld32(base, (f + 828));
    R(6) = ld32(base, (f + 832));
    R(0) = ld32(base, (f + 836));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 12), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E114u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3220);
    R(4) = (R(29) + 3232);
    R(3) = (R(29) + 3244);
    R(11) = ld32(base, (R(29) + 3220));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4012);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3232));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3244));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 792), R(11));
    st32(base, (f + 796), R(10));
    st32(base, (f + 800), R(9));
    st32(base, (f + 804), R(8));
    st32(base, (f + 808), R(7));
    st32(base, (f + 812), R(6));
    st32(base, (f + 816), R(5));
    st32(base, (f + 820), R(4));
    st32(base, (f + 824), R(0));
    GM_CALLV(0x80B5E170u, 0x80B59F90u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 76);
    GM_CALLV(0x80B5E180u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 76);
    R(25) = ld32(base, (f + 816));
    R(12) = ld32(base, (f + 820));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 824));
    R(5) = (R(28) + 64);
    R(10) = ld32(base, (f + 804));
    R(9) = ld32(base, (f + 808));
    R(8) = ld32(base, (f + 812));
    R(7) = ld32(base, (f + 792));
    R(6) = ld32(base, (f + 796));
    R(0) = ld32(base, (f + 800));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 76), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E1E0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3256);
    R(4) = (R(29) + 3268);
    R(3) = (R(29) + 3280);
    R(11) = ld32(base, (R(29) + 3256));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4048);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3268));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3280));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 756), R(11));
    st32(base, (f + 760), R(10));
    st32(base, (f + 764), R(9));
    st32(base, (f + 768), R(8));
    st32(base, (f + 772), R(7));
    st32(base, (f + 776), R(6));
    st32(base, (f + 780), R(5));
    st32(base, (f + 784), R(4));
    st32(base, (f + 788), R(0));
    GM_CALLV(0x80B5E23Cu, 0x80B59FA0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 140);
    GM_CALLV(0x80B5E24Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 140);
    R(25) = ld32(base, (f + 780));
    R(12) = ld32(base, (f + 784));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 788));
    R(5) = (R(28) + 128);
    R(10) = ld32(base, (f + 768));
    R(9) = ld32(base, (f + 772));
    R(8) = ld32(base, (f + 776));
    R(7) = ld32(base, (f + 756));
    R(6) = ld32(base, (f + 760));
    R(0) = ld32(base, (f + 764));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 140), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E2ACu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3292);
    R(4) = (R(29) + 3304);
    R(3) = (R(29) + 3316);
    R(11) = ld32(base, (R(29) + 3292));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4088);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3304));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3316));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 720), R(11));
    st32(base, (f + 724), R(10));
    st32(base, (f + 728), R(9));
    st32(base, (f + 732), R(8));
    st32(base, (f + 736), R(7));
    st32(base, (f + 740), R(6));
    st32(base, (f + 744), R(5));
    st32(base, (f + 748), R(4));
    st32(base, (f + 752), R(0));
    GM_CALLV(0x80B5E308u, 0x80B59FB0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 204);
    GM_CALLV(0x80B5E318u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 204);
    R(25) = ld32(base, (f + 744));
    R(12) = ld32(base, (f + 748));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 752));
    R(5) = (R(28) + 192);
    R(10) = ld32(base, (f + 732));
    R(9) = ld32(base, (f + 736));
    R(8) = ld32(base, (f + 740));
    R(7) = ld32(base, (f + 720));
    R(6) = ld32(base, (f + 724));
    R(0) = ld32(base, (f + 728));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 204), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E378u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3328);
    R(4) = (R(29) + 3340);
    R(3) = (R(29) + 3352);
    R(11) = ld32(base, (R(29) + 3328));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4124);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3340));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3352));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 684), R(11));
    st32(base, (f + 688), R(10));
    st32(base, (f + 692), R(9));
    st32(base, (f + 696), R(8));
    st32(base, (f + 700), R(7));
    st32(base, (f + 704), R(6));
    st32(base, (f + 708), R(5));
    st32(base, (f + 712), R(4));
    st32(base, (f + 716), R(0));
    GM_CALLV(0x80B5E3D4u, 0x80B59FC0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 268);
    GM_CALLV(0x80B5E3E4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 268);
    R(25) = ld32(base, (f + 708));
    R(12) = ld32(base, (f + 712));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 716));
    R(5) = (R(28) + 256);
    R(10) = ld32(base, (f + 696));
    R(9) = ld32(base, (f + 700));
    R(8) = ld32(base, (f + 704));
    R(7) = ld32(base, (f + 684));
    R(6) = ld32(base, (f + 688));
    R(0) = ld32(base, (f + 692));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 268), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E444u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3364);
    R(4) = (R(29) + 3376);
    R(3) = (R(29) + 3388);
    R(11) = ld32(base, (R(29) + 3364));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4160);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3376));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3388));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 648), R(11));
    st32(base, (f + 652), R(10));
    st32(base, (f + 656), R(9));
    st32(base, (f + 660), R(8));
    st32(base, (f + 664), R(7));
    st32(base, (f + 668), R(6));
    st32(base, (f + 672), R(5));
    st32(base, (f + 676), R(4));
    st32(base, (f + 680), R(0));
    GM_CALLV(0x80B5E4A0u, 0x80B59FD0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 332);
    GM_CALLV(0x80B5E4B0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 332);
    R(25) = ld32(base, (f + 672));
    R(12) = ld32(base, (f + 676));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 680));
    R(5) = (R(28) + 320);
    R(10) = ld32(base, (f + 660));
    R(9) = ld32(base, (f + 664));
    R(8) = ld32(base, (f + 668));
    R(7) = ld32(base, (f + 648));
    R(6) = ld32(base, (f + 652));
    R(0) = ld32(base, (f + 656));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 332), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E510u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3400);
    R(4) = (R(29) + 3412);
    R(3) = (R(29) + 3424);
    R(11) = ld32(base, (R(29) + 3400));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4192);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3412));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3424));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 612), R(11));
    st32(base, (f + 616), R(10));
    st32(base, (f + 620), R(9));
    st32(base, (f + 624), R(8));
    st32(base, (f + 628), R(7));
    st32(base, (f + 632), R(6));
    st32(base, (f + 636), R(5));
    st32(base, (f + 640), R(4));
    st32(base, (f + 644), R(0));
    GM_CALLV(0x80B5E56Cu, 0x80B59FE0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 396);
    GM_CALLV(0x80B5E57Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 396);
    R(25) = ld32(base, (f + 636));
    R(12) = ld32(base, (f + 640));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 644));
    R(5) = (R(28) + 384);
    R(10) = ld32(base, (f + 624));
    R(9) = ld32(base, (f + 628));
    R(8) = ld32(base, (f + 632));
    R(7) = ld32(base, (f + 612));
    R(6) = ld32(base, (f + 616));
    R(0) = ld32(base, (f + 620));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 396), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E5DCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3436);
    R(4) = (R(29) + 3448);
    R(3) = (R(29) + 3460);
    R(11) = ld32(base, (R(29) + 3436));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4228);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3448));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3460));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 576), R(11));
    st32(base, (f + 580), R(10));
    st32(base, (f + 584), R(9));
    st32(base, (f + 588), R(8));
    st32(base, (f + 592), R(7));
    st32(base, (f + 596), R(6));
    st32(base, (f + 600), R(5));
    st32(base, (f + 604), R(4));
    st32(base, (f + 608), R(0));
    GM_CALLV(0x80B5E638u, 0x80B59FF0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 460);
    GM_CALLV(0x80B5E648u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 460);
    R(25) = ld32(base, (f + 600));
    R(12) = ld32(base, (f + 604));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 608));
    R(5) = (R(28) + 448);
    R(10) = ld32(base, (f + 588));
    R(9) = ld32(base, (f + 592));
    R(8) = ld32(base, (f + 596));
    R(7) = ld32(base, (f + 576));
    R(6) = ld32(base, (f + 580));
    R(0) = ld32(base, (f + 584));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 460), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E6A8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3472);
    R(4) = (R(29) + 3484);
    R(3) = (R(29) + 3496);
    R(11) = ld32(base, (R(29) + 3472));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4264);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3484));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3496));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 540), R(11));
    st32(base, (f + 544), R(10));
    st32(base, (f + 548), R(9));
    st32(base, (f + 552), R(8));
    st32(base, (f + 556), R(7));
    st32(base, (f + 560), R(6));
    st32(base, (f + 564), R(5));
    st32(base, (f + 568), R(4));
    st32(base, (f + 572), R(0));
    GM_CALLV(0x80B5E704u, 0x80B5A000u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 524);
    GM_CALLV(0x80B5E714u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 524);
    R(25) = ld32(base, (f + 564));
    R(12) = ld32(base, (f + 568));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 572));
    R(5) = (R(28) + 512);
    R(10) = ld32(base, (f + 552));
    R(9) = ld32(base, (f + 556));
    R(8) = ld32(base, (f + 560));
    R(7) = ld32(base, (f + 540));
    R(6) = ld32(base, (f + 544));
    R(0) = ld32(base, (f + 548));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 524), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E774u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3508);
    R(4) = (R(29) + 3520);
    R(3) = (R(29) + 3532);
    R(11) = ld32(base, (R(29) + 3508));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4300);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3520));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3532));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 504), R(11));
    st32(base, (f + 508), R(10));
    st32(base, (f + 512), R(9));
    st32(base, (f + 516), R(8));
    st32(base, (f + 520), R(7));
    st32(base, (f + 524), R(6));
    st32(base, (f + 528), R(5));
    st32(base, (f + 532), R(4));
    st32(base, (f + 536), R(0));
    GM_CALLV(0x80B5E7D0u, 0x80B5F2F0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 588);
    GM_CALLV(0x80B5E7E0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 588);
    R(25) = ld32(base, (f + 528));
    R(12) = ld32(base, (f + 532));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 536));
    R(5) = (R(28) + 576);
    R(10) = ld32(base, (f + 516));
    R(9) = ld32(base, (f + 520));
    R(8) = ld32(base, (f + 524));
    R(7) = ld32(base, (f + 504));
    R(6) = ld32(base, (f + 508));
    R(0) = ld32(base, (f + 512));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 588), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E840u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3544);
    R(4) = (R(29) + 3556);
    R(3) = (R(29) + 3568);
    R(11) = ld32(base, (R(29) + 3544));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4336);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3556));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3568));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 468), R(11));
    st32(base, (f + 472), R(10));
    st32(base, (f + 476), R(9));
    st32(base, (f + 480), R(8));
    st32(base, (f + 484), R(7));
    st32(base, (f + 488), R(6));
    st32(base, (f + 492), R(5));
    st32(base, (f + 496), R(4));
    st32(base, (f + 500), R(0));
    GM_CALLV(0x80B5E89Cu, 0x80B5F2E0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 652);
    GM_CALLV(0x80B5E8ACu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 652);
    R(25) = ld32(base, (f + 492));
    R(12) = ld32(base, (f + 496));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 500));
    R(5) = (R(28) + 640);
    R(10) = ld32(base, (f + 480));
    R(9) = ld32(base, (f + 484));
    R(8) = ld32(base, (f + 488));
    R(7) = ld32(base, (f + 468));
    R(6) = ld32(base, (f + 472));
    R(0) = ld32(base, (f + 476));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 652), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E90Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3580);
    R(4) = (R(29) + 3592);
    R(3) = (R(29) + 3604);
    R(11) = ld32(base, (R(29) + 3580));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4372);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3592));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3604));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 432), R(11));
    st32(base, (f + 436), R(10));
    st32(base, (f + 440), R(9));
    st32(base, (f + 444), R(8));
    st32(base, (f + 448), R(7));
    st32(base, (f + 452), R(6));
    st32(base, (f + 456), R(5));
    st32(base, (f + 460), R(4));
    st32(base, (f + 464), R(0));
    GM_CALLV(0x80B5E968u, 0x80B5F2D0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 716);
    GM_CALLV(0x80B5E978u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 716);
    R(25) = ld32(base, (f + 456));
    R(12) = ld32(base, (f + 460));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 464));
    R(5) = (R(28) + 704);
    R(10) = ld32(base, (f + 444));
    R(9) = ld32(base, (f + 448));
    R(8) = ld32(base, (f + 452));
    R(7) = ld32(base, (f + 432));
    R(6) = ld32(base, (f + 436));
    R(0) = ld32(base, (f + 440));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 716), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5E9D8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3616);
    R(4) = (R(29) + 3628);
    R(3) = (R(29) + 3640);
    R(11) = ld32(base, (R(29) + 3616));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4412);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3628));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3640));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 396), R(11));
    st32(base, (f + 400), R(10));
    st32(base, (f + 404), R(9));
    st32(base, (f + 408), R(8));
    st32(base, (f + 412), R(7));
    st32(base, (f + 416), R(6));
    st32(base, (f + 420), R(5));
    st32(base, (f + 424), R(4));
    st32(base, (f + 428), R(0));
    GM_CALLV(0x80B5EA34u, 0x80B5F2C0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 780);
    GM_CALLV(0x80B5EA44u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 780);
    R(25) = ld32(base, (f + 420));
    R(12) = ld32(base, (f + 424));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 428));
    R(5) = (R(28) + 768);
    R(10) = ld32(base, (f + 408));
    R(9) = ld32(base, (f + 412));
    R(8) = ld32(base, (f + 416));
    R(7) = ld32(base, (f + 396));
    R(6) = ld32(base, (f + 400));
    R(0) = ld32(base, (f + 404));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 780), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5EAA4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3652);
    R(4) = (R(29) + 3664);
    R(3) = (R(29) + 3676);
    R(11) = ld32(base, (R(29) + 3652));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4448);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3664));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3676));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 360), R(11));
    st32(base, (f + 364), R(10));
    st32(base, (f + 368), R(9));
    st32(base, (f + 372), R(8));
    st32(base, (f + 376), R(7));
    st32(base, (f + 380), R(6));
    st32(base, (f + 384), R(5));
    st32(base, (f + 388), R(4));
    st32(base, (f + 392), R(0));
    GM_CALLV(0x80B5EB00u, 0x80B5A010u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 844);
    GM_CALLV(0x80B5EB10u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 844);
    R(25) = ld32(base, (f + 384));
    R(12) = ld32(base, (f + 388));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 392));
    R(5) = (R(28) + 832);
    R(10) = ld32(base, (f + 372));
    R(9) = ld32(base, (f + 376));
    R(8) = ld32(base, (f + 380));
    R(7) = ld32(base, (f + 360));
    R(6) = ld32(base, (f + 364));
    R(0) = ld32(base, (f + 368));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 844), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5EB70u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3688);
    R(4) = (R(29) + 3700);
    R(3) = (R(29) + 3712);
    R(11) = ld32(base, (R(29) + 3688));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4488);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3700));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3712));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 324), R(11));
    st32(base, (f + 328), R(10));
    st32(base, (f + 332), R(9));
    st32(base, (f + 336), R(8));
    st32(base, (f + 340), R(7));
    st32(base, (f + 344), R(6));
    st32(base, (f + 348), R(5));
    st32(base, (f + 352), R(4));
    st32(base, (f + 356), R(0));
    GM_CALLV(0x80B5EBCCu, 0x80B5A020u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 908);
    GM_CALLV(0x80B5EBDCu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 908);
    R(25) = ld32(base, (f + 348));
    R(12) = ld32(base, (f + 352));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 356));
    R(5) = (R(28) + 896);
    R(10) = ld32(base, (f + 336));
    R(9) = ld32(base, (f + 340));
    R(8) = ld32(base, (f + 344));
    R(7) = ld32(base, (f + 324));
    R(6) = ld32(base, (f + 328));
    R(0) = ld32(base, (f + 332));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 908), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5EC3Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3724);
    R(4) = (R(29) + 3736);
    R(3) = (R(29) + 3748);
    R(11) = ld32(base, (R(29) + 3724));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4528);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3736));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3748));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 288), R(11));
    st32(base, (f + 292), R(10));
    st32(base, (f + 296), R(9));
    st32(base, (f + 300), R(8));
    st32(base, (f + 304), R(7));
    st32(base, (f + 308), R(6));
    st32(base, (f + 312), R(5));
    st32(base, (f + 316), R(4));
    st32(base, (f + 320), R(0));
    GM_CALLV(0x80B5EC98u, 0x80B5A030u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 972);
    GM_CALLV(0x80B5ECA8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 972);
    R(25) = ld32(base, (f + 312));
    R(12) = ld32(base, (f + 316));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 320));
    R(5) = (R(28) + 960);
    R(10) = ld32(base, (f + 300));
    R(9) = ld32(base, (f + 304));
    R(8) = ld32(base, (f + 308));
    R(7) = ld32(base, (f + 288));
    R(6) = ld32(base, (f + 292));
    R(0) = ld32(base, (f + 296));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 972), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5ED08u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3760);
    R(4) = (R(29) + 3772);
    R(3) = (R(29) + 3784);
    R(11) = ld32(base, (R(29) + 3760));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4564);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3772));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3784));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 252), R(11));
    st32(base, (f + 256), R(10));
    st32(base, (f + 260), R(9));
    st32(base, (f + 264), R(8));
    st32(base, (f + 268), R(7));
    st32(base, (f + 272), R(6));
    st32(base, (f + 276), R(5));
    st32(base, (f + 280), R(4));
    st32(base, (f + 284), R(0));
    GM_CALLV(0x80B5ED64u, 0x80B5A040u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1036);
    GM_CALLV(0x80B5ED74u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1036);
    R(25) = ld32(base, (f + 276));
    R(12) = ld32(base, (f + 280));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 284));
    R(5) = (R(28) + 1024);
    R(10) = ld32(base, (f + 264));
    R(9) = ld32(base, (f + 268));
    R(8) = ld32(base, (f + 272));
    R(7) = ld32(base, (f + 252));
    R(6) = ld32(base, (f + 256));
    R(0) = ld32(base, (f + 260));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1036), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5EDD4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3796);
    R(4) = (R(29) + 3808);
    R(3) = (R(29) + 3820);
    R(11) = ld32(base, (R(29) + 3796));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4608);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3808));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3820));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 216), R(11));
    st32(base, (f + 220), R(10));
    st32(base, (f + 224), R(9));
    st32(base, (f + 228), R(8));
    st32(base, (f + 232), R(7));
    st32(base, (f + 236), R(6));
    st32(base, (f + 240), R(5));
    st32(base, (f + 244), R(4));
    st32(base, (f + 248), R(0));
    GM_CALLV(0x80B5EE30u, 0x80B5A050u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1100);
    GM_CALLV(0x80B5EE40u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1100);
    R(25) = ld32(base, (f + 240));
    R(12) = ld32(base, (f + 244));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 248));
    R(5) = (R(28) + 1088);
    R(10) = ld32(base, (f + 228));
    R(9) = ld32(base, (f + 232));
    R(8) = ld32(base, (f + 236));
    R(7) = ld32(base, (f + 216));
    R(6) = ld32(base, (f + 220));
    R(0) = ld32(base, (f + 224));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1100), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5EEA0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3832);
    R(4) = (R(29) + 3844);
    R(3) = (R(29) + 3856);
    R(11) = ld32(base, (R(29) + 3832));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4648);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3844));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3856));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 180), R(11));
    st32(base, (f + 184), R(10));
    st32(base, (f + 188), R(9));
    st32(base, (f + 192), R(8));
    st32(base, (f + 196), R(7));
    st32(base, (f + 200), R(6));
    st32(base, (f + 204), R(5));
    st32(base, (f + 208), R(4));
    st32(base, (f + 212), R(0));
    GM_CALLV(0x80B5EEFCu, 0x80B5A060u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1164);
    GM_CALLV(0x80B5EF0Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1164);
    R(25) = ld32(base, (f + 204));
    R(12) = ld32(base, (f + 208));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 212));
    R(5) = (R(28) + 1152);
    R(10) = ld32(base, (f + 192));
    R(9) = ld32(base, (f + 196));
    R(8) = ld32(base, (f + 200));
    R(7) = ld32(base, (f + 180));
    R(6) = ld32(base, (f + 184));
    R(0) = ld32(base, (f + 188));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1164), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5EF6Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3868);
    R(4) = (R(29) + 3880);
    R(3) = (R(29) + 3892);
    R(11) = ld32(base, (R(29) + 3868));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4692);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3880));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3892));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 144), R(11));
    st32(base, (f + 148), R(10));
    st32(base, (f + 152), R(9));
    st32(base, (f + 156), R(8));
    st32(base, (f + 160), R(7));
    st32(base, (f + 164), R(6));
    st32(base, (f + 168), R(5));
    st32(base, (f + 172), R(4));
    st32(base, (f + 176), R(0));
    GM_CALLV(0x80B5EFC8u, 0x80B5A070u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1228);
    GM_CALLV(0x80B5EFD8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1228);
    R(26) = ld32(base, (f + 168));
    R(12) = ld32(base, (f + 172));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 176));
    R(5) = (R(28) + 1216);
    R(10) = ld32(base, (f + 156));
    R(9) = ld32(base, (f + 160));
    R(8) = ld32(base, (f + 164));
    R(7) = ld32(base, (f + 144));
    R(6) = ld32(base, (f + 148));
    R(0) = ld32(base, (f + 152));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1228), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B5F038u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3904);
    R(4) = (R(29) + 3916);
    R(3) = (R(29) + 3928);
    R(11) = ld32(base, (R(29) + 3904));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4736);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3916));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3928));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 108), R(11));
    st32(base, (f + 112), R(10));
    st32(base, (f + 116), R(9));
    st32(base, (f + 120), R(8));
    st32(base, (f + 124), R(7));
    st32(base, (f + 128), R(6));
    st32(base, (f + 132), R(5));
    st32(base, (f + 136), R(4));
    st32(base, (f + 140), R(0));
    GM_CALLV(0x80B5F094u, 0x80B5F2B0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1292);
    GM_CALLV(0x80B5F0A4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1292);
    R(27) = ld32(base, (f + 132));
    R(12) = ld32(base, (f + 136));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 140));
    R(5) = (R(28) + 1280);
    R(10) = ld32(base, (f + 120));
    R(9) = ld32(base, (f + 124));
    R(8) = ld32(base, (f + 128));
    R(7) = ld32(base, (f + 108));
    R(6) = ld32(base, (f + 112));
    R(0) = ld32(base, (f + 116));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1292), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B5F104u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3940);
    R(4) = (R(29) + 3952);
    R(3) = (R(29) + 3964);
    R(11) = ld32(base, (R(29) + 3940));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4772);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3952));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3964));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 72), R(11));
    st32(base, (f + 76), R(10));
    st32(base, (f + 80), R(9));
    st32(base, (f + 84), R(8));
    st32(base, (f + 88), R(7));
    st32(base, (f + 92), R(6));
    st32(base, (f + 96), R(5));
    st32(base, (f + 100), R(4));
    st32(base, (f + 104), R(0));
    GM_CALLV(0x80B5F160u, 0x80B5A080u, 0);
    R(29) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1356);
    GM_CALLV(0x80B5F170u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1356);
    R(27) = ld32(base, (f + 96));
    R(12) = ld32(base, (f + 100));
    R(4) = (R(31) + -3504);
    R(11) = ld32(base, (f + 104));
    R(5) = (R(28) + 1344);
    R(10) = ld32(base, (f + 84));
    R(9) = ld32(base, (f + 88));
    R(8) = ld32(base, (f + 92));
    R(7) = ld32(base, (f + 72));
    R(6) = ld32(base, (f + 76));
    R(0) = ld32(base, (f + 80));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1356), R(30));
    st32(base, (R(3) + 48), R(29));
    GM_CALLV(0x80B5F1D0u, 0x80B1CAC0u, 0);
    R(11) = (f + 896);
    R(0) = lr;
}

/* fn_4_42860 (fn_4_42860, 12 bytes) */
static void eb_m_5f2b0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31356);
}

/* fn_4_42870 (fn_4_42870, 12 bytes) */
static void eb_m_5f2c0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31932);
}

/* fn_4_42880 (fn_4_42880, 12 bytes) */
static void eb_m_5f2d0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31996);
}

/* fn_4_42890 (fn_4_42890, 12 bytes) */
static void eb_m_5f2e0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_428A0 (fn_4_428A0, 12 bytes) */
static void eb_m_5f2f0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32188);
}

/* fn_4_42BF0 (fn_4_42BF0, 12 bytes) */
static void eb_m_5f640(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_42C00 (fn_4_42C00, 12 bytes) */
static void eb_m_5f650(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_42C10 (fn_4_42C10, 12 bytes) */
static void eb_m_5f660(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_42C20 (fn_4_42C20, 12 bytes) */
static void eb_m_5f670(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_42C30 (fn_4_42C30, 12 bytes) */
static void eb_m_5f680(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_42C40 (fn_4_42C40, 12 bytes) */
static void eb_m_5f690(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_42C50 (fn_4_42C50, 12 bytes) */
static void eb_m_5f6a0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_42C60 (fn_4_42C60, 12 bytes) */
static void eb_m_5f6b0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_42C70 (fn_4_42C70, 12 bytes) */
static void eb_m_5f6c0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_45720 (fn_4_45720, 3132 bytes) */
static void eb_m_62170(GM_CTX) {
    GM_FN(0x80B62170); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 608);
    R(29) = (0 + 0x80B80000u);
    R(7) = (0 + 0x80B70000u);
    R(29) = (R(29) + 20048);
    R(28) = (0 + 0x80B90000u);
    R(7) = (R(7) + 21264);
    R(12) = ld32(base, (R(29) + 2984));
    { uint32_t ea_ = (R(7) + 332); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (R(29) + 80);
    R(6) = (R(29) + 2984);
    { uint32_t ea_ = (R(7) + 524); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(7) + 528); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(29) + 2996);
    { uint32_t ea_ = (R(7) + 532); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (R(29) + 3008);
    { uint32_t ea_ = (R(7) + 536); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(18) = (0 + 1211);
    R(11) = ld32(base, (R(6) + 4));
    R(20) = (R(29) + 824);
    R(21) = (0 + 1097);
    R(10) = ld32(base, (R(6) + 8));
    R(9) = ld32(base, (R(29) + 2996));
    R(19) = (0 + 1212);
    R(8) = ld32(base, (R(5) + 4));
    R(22) = (0 + 1213);
    R(7) = ld32(base, (R(5) + 8));
    R(23) = (0 + 1214);
    R(6) = ld32(base, (R(29) + 3008));
    R(24) = (0 + 1202);
    R(5) = ld32(base, (R(4) + 4));
    R(31) = (0 + 1204);
    R(0) = ld32(base, (R(4) + 8));
    R(27) = (0 + 1206);
    R(26) = (0 + 1207);
    R(25) = (0 + 1208);
    R(4) = (0 + 1209);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    R(28) = (R(28) + -10552);
    R(30) = (R(29) + 3488);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(29) + 824), R(18));
    st32(base, (R(20) + 8), R(19));
    st32(base, (R(20) + 16), R(21));
    st32(base, (R(20) + 24), R(22));
    st32(base, (R(20) + 32), R(21));
    st32(base, (R(20) + 40), R(23));
    st32(base, (R(20) + 48), R(24));
    st32(base, (R(20) + 56), R(31));
    st32(base, (R(20) + 64), R(27));
    st32(base, (R(20) + 72), R(26));
    st32(base, (R(20) + 80), R(21));
    st32(base, (R(20) + 88), R(25));
    st32(base, (R(20) + 96), R(4));
    st32(base, (R(20) + 104), R(21));
    st32(base, (R(20) + 112), R(21));
    st32(base, (f + 508), R(12));
    st32(base, (f + 512), R(11));
    st32(base, (f + 516), R(10));
    st32(base, (f + 520), R(9));
    st32(base, (f + 524), R(8));
    st32(base, (f + 528), R(7));
    st32(base, (f + 532), R(6));
    st32(base, (f + 536), R(5));
    st32(base, (f + 540), R(0));
    GM_CALLV(0x80B622BCu, 0x80B5F640u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(30) |R(30);
    R(3) = (R(28) + 12);
    GM_CALLV(0x80B622CCu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 12);
    R(25) = ld32(base, (f + 532));
    R(12) = ld32(base, (f + 536));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 540));
    R(30) = (R(30) + 24064);
    R(10) = ld32(base, (f + 520));
    R(31) = (0 + 0x80B60000u);
    R(9) = ld32(base, (f + 524));
    R(4) = (R(31) + 11792);
    R(8) = ld32(base, (f + 528));
    R(5) = (R(28) + 0);
    R(7) = ld32(base, (f + 508));
    R(6) = ld32(base, (f + 512));
    R(0) = ld32(base, (f + 516));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 12), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B62338u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3020);
    R(4) = (R(29) + 3032);
    R(3) = (R(29) + 3044);
    R(11) = ld32(base, (R(29) + 3020));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3524);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3032));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3044));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 472), R(11));
    st32(base, (f + 476), R(10));
    st32(base, (f + 480), R(9));
    st32(base, (f + 484), R(8));
    st32(base, (f + 488), R(7));
    st32(base, (f + 492), R(6));
    st32(base, (f + 496), R(5));
    st32(base, (f + 500), R(4));
    st32(base, (f + 504), R(0));
    GM_CALLV(0x80B62394u, 0x80B5F650u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 76);
    GM_CALLV(0x80B623A4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 76);
    R(25) = ld32(base, (f + 496));
    R(12) = ld32(base, (f + 500));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 504));
    R(5) = (R(28) + 64);
    R(10) = ld32(base, (f + 484));
    R(9) = ld32(base, (f + 488));
    R(8) = ld32(base, (f + 492));
    R(7) = ld32(base, (f + 472));
    R(6) = ld32(base, (f + 476));
    R(0) = ld32(base, (f + 480));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 76), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B62404u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3056);
    R(4) = (R(29) + 3068);
    R(3) = (R(29) + 3080);
    R(11) = ld32(base, (R(29) + 3056));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3560);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3068));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3080));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 436), R(11));
    st32(base, (f + 440), R(10));
    st32(base, (f + 444), R(9));
    st32(base, (f + 448), R(8));
    st32(base, (f + 452), R(7));
    st32(base, (f + 456), R(6));
    st32(base, (f + 460), R(5));
    st32(base, (f + 464), R(4));
    st32(base, (f + 468), R(0));
    GM_CALLV(0x80B62460u, 0x80B5F660u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 140);
    GM_CALLV(0x80B62470u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 140);
    R(25) = ld32(base, (f + 460));
    R(12) = ld32(base, (f + 464));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 468));
    R(5) = (R(28) + 128);
    R(10) = ld32(base, (f + 448));
    R(9) = ld32(base, (f + 452));
    R(8) = ld32(base, (f + 456));
    R(7) = ld32(base, (f + 436));
    R(6) = ld32(base, (f + 440));
    R(0) = ld32(base, (f + 444));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 140), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B624D0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3092);
    R(4) = (R(29) + 3104);
    R(3) = (R(29) + 3116);
    R(11) = ld32(base, (R(29) + 3092));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3600);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3104));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3116));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 400), R(11));
    st32(base, (f + 404), R(10));
    st32(base, (f + 408), R(9));
    st32(base, (f + 412), R(8));
    st32(base, (f + 416), R(7));
    st32(base, (f + 420), R(6));
    st32(base, (f + 424), R(5));
    st32(base, (f + 428), R(4));
    st32(base, (f + 432), R(0));
    GM_CALLV(0x80B6252Cu, 0x80B5F670u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 204);
    GM_CALLV(0x80B6253Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 204);
    R(25) = ld32(base, (f + 424));
    R(12) = ld32(base, (f + 428));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 432));
    R(5) = (R(28) + 192);
    R(10) = ld32(base, (f + 412));
    R(9) = ld32(base, (f + 416));
    R(8) = ld32(base, (f + 420));
    R(7) = ld32(base, (f + 400));
    R(6) = ld32(base, (f + 404));
    R(0) = ld32(base, (f + 408));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 204), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6259Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3128);
    R(4) = (R(29) + 3140);
    R(3) = (R(29) + 3152);
    R(11) = ld32(base, (R(29) + 3128));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3632);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3140));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3152));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 364), R(11));
    st32(base, (f + 368), R(10));
    st32(base, (f + 372), R(9));
    st32(base, (f + 376), R(8));
    st32(base, (f + 380), R(7));
    st32(base, (f + 384), R(6));
    st32(base, (f + 388), R(5));
    st32(base, (f + 392), R(4));
    st32(base, (f + 396), R(0));
    GM_CALLV(0x80B625F8u, 0x80B5F680u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 268);
    GM_CALLV(0x80B62608u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 268);
    R(25) = ld32(base, (f + 388));
    R(12) = ld32(base, (f + 392));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 396));
    R(5) = (R(28) + 256);
    R(10) = ld32(base, (f + 376));
    R(9) = ld32(base, (f + 380));
    R(8) = ld32(base, (f + 384));
    R(7) = ld32(base, (f + 364));
    R(6) = ld32(base, (f + 368));
    R(0) = ld32(base, (f + 372));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 268), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B62668u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3164);
    R(4) = (R(29) + 3176);
    R(3) = (R(29) + 3188);
    R(11) = ld32(base, (R(29) + 3164));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3672);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3176));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3188));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 328), R(11));
    st32(base, (f + 332), R(10));
    st32(base, (f + 336), R(9));
    st32(base, (f + 340), R(8));
    st32(base, (f + 344), R(7));
    st32(base, (f + 348), R(6));
    st32(base, (f + 352), R(5));
    st32(base, (f + 356), R(4));
    st32(base, (f + 360), R(0));
    GM_CALLV(0x80B626C4u, 0x80B62EB0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 332);
    GM_CALLV(0x80B626D4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 332);
    R(25) = ld32(base, (f + 352));
    R(12) = ld32(base, (f + 356));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 360));
    R(5) = (R(28) + 320);
    R(10) = ld32(base, (f + 340));
    R(9) = ld32(base, (f + 344));
    R(8) = ld32(base, (f + 348));
    R(7) = ld32(base, (f + 328));
    R(6) = ld32(base, (f + 332));
    R(0) = ld32(base, (f + 336));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 332), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B62734u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3200);
    R(4) = (R(29) + 3212);
    R(3) = (R(29) + 3224);
    R(11) = ld32(base, (R(29) + 3200));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3708);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3212));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3224));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 292), R(11));
    st32(base, (f + 296), R(10));
    st32(base, (f + 300), R(9));
    st32(base, (f + 304), R(8));
    st32(base, (f + 308), R(7));
    st32(base, (f + 312), R(6));
    st32(base, (f + 316), R(5));
    st32(base, (f + 320), R(4));
    st32(base, (f + 324), R(0));
    GM_CALLV(0x80B62790u, 0x80B62EA0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 396);
    GM_CALLV(0x80B627A0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 396);
    R(25) = ld32(base, (f + 316));
    R(12) = ld32(base, (f + 320));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 324));
    R(5) = (R(28) + 384);
    R(10) = ld32(base, (f + 304));
    R(9) = ld32(base, (f + 308));
    R(8) = ld32(base, (f + 312));
    R(7) = ld32(base, (f + 292));
    R(6) = ld32(base, (f + 296));
    R(0) = ld32(base, (f + 300));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 396), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B62800u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3236);
    R(4) = (R(29) + 3248);
    R(3) = (R(29) + 3260);
    R(11) = ld32(base, (R(29) + 3236));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3740);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3248));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3260));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 256), R(11));
    st32(base, (f + 260), R(10));
    st32(base, (f + 264), R(9));
    st32(base, (f + 268), R(8));
    st32(base, (f + 272), R(7));
    st32(base, (f + 276), R(6));
    st32(base, (f + 280), R(5));
    st32(base, (f + 284), R(4));
    st32(base, (f + 288), R(0));
    GM_CALLV(0x80B6285Cu, 0x80B62E90u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 460);
    GM_CALLV(0x80B6286Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 460);
    R(25) = ld32(base, (f + 280));
    R(12) = ld32(base, (f + 284));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 288));
    R(5) = (R(28) + 448);
    R(10) = ld32(base, (f + 268));
    R(9) = ld32(base, (f + 272));
    R(8) = ld32(base, (f + 276));
    R(7) = ld32(base, (f + 256));
    R(6) = ld32(base, (f + 260));
    R(0) = ld32(base, (f + 264));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 460), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B628CCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3272);
    R(4) = (R(29) + 3284);
    R(3) = (R(29) + 3296);
    R(11) = ld32(base, (R(29) + 3272));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3776);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3284));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3296));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 220), R(11));
    st32(base, (f + 224), R(10));
    st32(base, (f + 228), R(9));
    st32(base, (f + 232), R(8));
    st32(base, (f + 236), R(7));
    st32(base, (f + 240), R(6));
    st32(base, (f + 244), R(5));
    st32(base, (f + 248), R(4));
    st32(base, (f + 252), R(0));
    GM_CALLV(0x80B62928u, 0x80B62E80u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 524);
    GM_CALLV(0x80B62938u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 524);
    R(25) = ld32(base, (f + 244));
    R(12) = ld32(base, (f + 248));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 252));
    R(5) = (R(28) + 512);
    R(10) = ld32(base, (f + 232));
    R(9) = ld32(base, (f + 236));
    R(8) = ld32(base, (f + 240));
    R(7) = ld32(base, (f + 220));
    R(6) = ld32(base, (f + 224));
    R(0) = ld32(base, (f + 228));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 524), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B62998u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3308);
    R(4) = (R(29) + 3320);
    R(3) = (R(29) + 3332);
    R(11) = ld32(base, (R(29) + 3308));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3812);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3320));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3332));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 184), R(11));
    st32(base, (f + 188), R(10));
    st32(base, (f + 192), R(9));
    st32(base, (f + 196), R(8));
    st32(base, (f + 200), R(7));
    st32(base, (f + 204), R(6));
    st32(base, (f + 208), R(5));
    st32(base, (f + 212), R(4));
    st32(base, (f + 216), R(0));
    GM_CALLV(0x80B629F4u, 0x80B5F690u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 588);
    GM_CALLV(0x80B62A04u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 588);
    R(25) = ld32(base, (f + 208));
    R(12) = ld32(base, (f + 212));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 216));
    R(5) = (R(28) + 576);
    R(10) = ld32(base, (f + 196));
    R(9) = ld32(base, (f + 200));
    R(8) = ld32(base, (f + 204));
    R(7) = ld32(base, (f + 184));
    R(6) = ld32(base, (f + 188));
    R(0) = ld32(base, (f + 192));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 588), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B62A64u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3344);
    R(4) = (R(29) + 3356);
    R(3) = (R(29) + 3368);
    R(11) = ld32(base, (R(29) + 3344));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3848);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3356));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3368));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 148), R(11));
    st32(base, (f + 152), R(10));
    st32(base, (f + 156), R(9));
    st32(base, (f + 160), R(8));
    st32(base, (f + 164), R(7));
    st32(base, (f + 168), R(6));
    st32(base, (f + 172), R(5));
    st32(base, (f + 176), R(4));
    st32(base, (f + 180), R(0));
    GM_CALLV(0x80B62AC0u, 0x80B5F6A0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 652);
    GM_CALLV(0x80B62AD0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 652);
    R(25) = ld32(base, (f + 172));
    R(12) = ld32(base, (f + 176));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 180));
    R(5) = (R(28) + 640);
    R(10) = ld32(base, (f + 160));
    R(9) = ld32(base, (f + 164));
    R(8) = ld32(base, (f + 168));
    R(7) = ld32(base, (f + 148));
    R(6) = ld32(base, (f + 152));
    R(0) = ld32(base, (f + 156));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 652), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B62B30u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3380);
    R(4) = (R(29) + 3392);
    R(3) = (R(29) + 3404);
    R(11) = ld32(base, (R(29) + 3380));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3888);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3392));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3404));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 112), R(11));
    st32(base, (f + 116), R(10));
    st32(base, (f + 120), R(9));
    st32(base, (f + 124), R(8));
    st32(base, (f + 128), R(7));
    st32(base, (f + 132), R(6));
    st32(base, (f + 136), R(5));
    st32(base, (f + 140), R(4));
    st32(base, (f + 144), R(0));
    GM_CALLV(0x80B62B8Cu, 0x80B62E70u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 716);
    GM_CALLV(0x80B62B9Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 716);
    R(26) = ld32(base, (f + 136));
    R(12) = ld32(base, (f + 140));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 144));
    R(5) = (R(28) + 704);
    R(10) = ld32(base, (f + 124));
    R(9) = ld32(base, (f + 128));
    R(8) = ld32(base, (f + 132));
    R(7) = ld32(base, (f + 112));
    R(6) = ld32(base, (f + 116));
    R(0) = ld32(base, (f + 120));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 716), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B62BFCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3416);
    R(4) = (R(29) + 3428);
    R(3) = (R(29) + 3440);
    R(11) = ld32(base, (R(29) + 3416));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3928);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3428));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3440));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 76), R(11));
    st32(base, (f + 80), R(10));
    st32(base, (f + 84), R(9));
    st32(base, (f + 88), R(8));
    st32(base, (f + 92), R(7));
    st32(base, (f + 96), R(6));
    st32(base, (f + 100), R(5));
    st32(base, (f + 104), R(4));
    st32(base, (f + 108), R(0));
    GM_CALLV(0x80B62C58u, 0x80B5F6B0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 780);
    GM_CALLV(0x80B62C68u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 780);
    R(27) = ld32(base, (f + 100));
    R(12) = ld32(base, (f + 104));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 108));
    R(5) = (R(28) + 768);
    R(10) = ld32(base, (f + 88));
    R(9) = ld32(base, (f + 92));
    R(8) = ld32(base, (f + 96));
    R(7) = ld32(base, (f + 76));
    R(6) = ld32(base, (f + 80));
    R(0) = ld32(base, (f + 84));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 780), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B62CC8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3452);
    R(4) = (R(29) + 3464);
    R(3) = (R(29) + 3476);
    R(11) = ld32(base, (R(29) + 3452));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3972);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3464));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3476));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 40), R(11));
    st32(base, (f + 44), R(10));
    st32(base, (f + 48), R(9));
    st32(base, (f + 52), R(8));
    st32(base, (f + 56), R(7));
    st32(base, (f + 60), R(6));
    st32(base, (f + 64), R(5));
    st32(base, (f + 68), R(4));
    st32(base, (f + 72), R(0));
    GM_CALLV(0x80B62D24u, 0x80B5F6C0u, 0);
    R(29) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 844);
    GM_CALLV(0x80B62D34u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 844);
    R(27) = ld32(base, (f + 64));
    R(12) = ld32(base, (f + 68));
    R(4) = (R(31) + 11792);
    R(11) = ld32(base, (f + 72));
    R(5) = (R(28) + 832);
    R(10) = ld32(base, (f + 52));
    R(9) = ld32(base, (f + 56));
    R(8) = ld32(base, (f + 60));
    R(7) = ld32(base, (f + 40));
    R(6) = ld32(base, (f + 44));
    R(0) = ld32(base, (f + 48));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 844), R(30));
    st32(base, (R(3) + 48), R(29));
    GM_CALLV(0x80B62D94u, 0x80B1CAC0u, 0);
    R(11) = (f + 608);
    R(0) = lr;
}

/* fn_4_46420 (fn_4_46420, 12 bytes) */
static void eb_m_62e70(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30716);
}

/* fn_4_46430 (fn_4_46430, 12 bytes) */
static void eb_m_62e80(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31356);
}

/* fn_4_46440 (fn_4_46440, 12 bytes) */
static void eb_m_62e90(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32252);
}

/* fn_4_46450 (fn_4_46450, 12 bytes) */
static void eb_m_62ea0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32380);
}

/* fn_4_46460 (fn_4_46460, 12 bytes) */
static void eb_m_62eb0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_467F0 (fn_4_467F0, 12 bytes) */
static void eb_m_63240(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_46800 (fn_4_46800, 12 bytes) */
static void eb_m_63250(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_46810 (fn_4_46810, 12 bytes) */
static void eb_m_63260(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_46820 (fn_4_46820, 12 bytes) */
static void eb_m_63270(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_46830 (fn_4_46830, 12 bytes) */
static void eb_m_63280(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_46840 (fn_4_46840, 12 bytes) */
static void eb_m_63290(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_46850 (fn_4_46850, 12 bytes) */
static void eb_m_632a0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_46860 (fn_4_46860, 12 bytes) */
static void eb_m_632b0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_46870 (fn_4_46870, 12 bytes) */
static void eb_m_632c0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_49450 (fn_4_49450, 3852 bytes) */
static void eb_m_65ea0(GM_CTX) {
    GM_FN(0x80B65EA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 720);
    R(28) = (0 + 0x80B90000u);
    R(29) = (0 + 0x80B80000u);
    R(28) = (R(28) + -9656);
    R(27) = (0 + 0x80B70000u);
    R(0) = ld8(base, (R(28) + 1088));
    R(27) = (R(27) + 21960);
    { uint32_t ea_ = (R(27) + 200); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(29) = (R(29) + 24168);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    { uint32_t ea_ = (R(27) + 408); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(26) = (R(29) + 80);
    { uint32_t ea_ = (R(27) + 260); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 412); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(25) = (0 + 1126);
    { uint32_t ea_ = (R(27) + 416); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(11) = (R(29) + 824);
    R(10) = (0 + 1097);
    R(12) = (0 + 1127);
    R(9) = (0 + 1128);
    R(8) = (0 + 1129);
    R(7) = (0 + 1114);
    R(6) = (0 + 1116);
    R(5) = (0 + 1121);
    R(4) = (0 + 1122);
    R(3) = (0 + 1123);
    R(0) = (0 + 1124);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(26) + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(26) + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(26) + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(26) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(26) + 48); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(29) + 824), R(25));
    st32(base, (R(11) + 8), R(12));
    st32(base, (R(11) + 16), R(10));
    st32(base, (R(11) + 24), R(9));
    st32(base, (R(11) + 32), R(10));
    st32(base, (R(11) + 40), R(8));
    st32(base, (R(11) + 48), R(7));
    st32(base, (R(11) + 56), R(6));
    st32(base, (R(11) + 64), R(5));
    st32(base, (R(11) + 72), R(4));
    st32(base, (R(11) + 80), R(10));
    st32(base, (R(11) + 88), R(3));
    st32(base, (R(11) + 96), R(0));
    st32(base, (R(11) + 104), R(10));
    st32(base, (R(11) + 112), R(10));
    if ((!CR_BIT(ctx, 2))) { goto L_80B65FFC; }
    { uint32_t ea_ = (R(27) + 424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(29) + 944);
    { uint32_t ea_ = (R(27) + 204); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(27) + 420); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 392); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 428); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 100); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 112); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(28) + 1088), R(0));
L_80B65FFC:;
    R(5) = (R(29) + 3256);
    R(4) = (R(29) + 3268);
    R(3) = (R(29) + 3280);
    R(11) = ld32(base, (R(29) + 3256));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(29) + 3868);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3268));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3280));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 648), R(11));
    st32(base, (f + 652), R(10));
    st32(base, (f + 656), R(9));
    st32(base, (f + 660), R(8));
    st32(base, (f + 664), R(7));
    st32(base, (f + 668), R(6));
    st32(base, (f + 672), R(5));
    st32(base, (f + 676), R(4));
    st32(base, (f + 680), R(0));
    GM_CALLV(0x80B66058u, 0x80B63240u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(28) + 12);
    GM_CALLV(0x80B66068u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 12);
    R(25) = ld32(base, (f + 672));
    R(12) = ld32(base, (f + 676));
    R(30) = (0 + 0x80B80000u);
    R(11) = ld32(base, (f + 680));
    R(30) = (R(30) + 28644);
    R(10) = ld32(base, (f + 660));
    R(31) = (0 + 0x80B60000u);
    R(9) = ld32(base, (f + 664));
    R(4) = (R(31) + 28176);
    R(8) = ld32(base, (f + 668));
    R(5) = (R(28) + 0);
    R(7) = ld32(base, (f + 648));
    R(6) = ld32(base, (f + 652));
    R(0) = ld32(base, (f + 656));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 12), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B660D4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3292);
    R(4) = (R(29) + 3304);
    R(3) = (R(29) + 3316);
    R(11) = ld32(base, (R(29) + 3292));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3900);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3304));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3316));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 612), R(11));
    st32(base, (f + 616), R(10));
    st32(base, (f + 620), R(9));
    st32(base, (f + 624), R(8));
    st32(base, (f + 628), R(7));
    st32(base, (f + 632), R(6));
    st32(base, (f + 636), R(5));
    st32(base, (f + 640), R(4));
    st32(base, (f + 644), R(0));
    GM_CALLV(0x80B66130u, 0x80B63250u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 76);
    GM_CALLV(0x80B66140u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 76);
    R(25) = ld32(base, (f + 636));
    R(12) = ld32(base, (f + 640));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 644));
    R(5) = (R(28) + 64);
    R(10) = ld32(base, (f + 624));
    R(9) = ld32(base, (f + 628));
    R(8) = ld32(base, (f + 632));
    R(7) = ld32(base, (f + 612));
    R(6) = ld32(base, (f + 616));
    R(0) = ld32(base, (f + 620));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 76), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B661A0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3328);
    R(4) = (R(29) + 3340);
    R(3) = (R(29) + 3352);
    R(11) = ld32(base, (R(29) + 3328));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3932);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3340));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3352));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 576), R(11));
    st32(base, (f + 580), R(10));
    st32(base, (f + 584), R(9));
    st32(base, (f + 588), R(8));
    st32(base, (f + 592), R(7));
    st32(base, (f + 596), R(6));
    st32(base, (f + 600), R(5));
    st32(base, (f + 604), R(4));
    st32(base, (f + 608), R(0));
    GM_CALLV(0x80B661FCu, 0x80B63260u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 140);
    GM_CALLV(0x80B6620Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 140);
    R(25) = ld32(base, (f + 600));
    R(12) = ld32(base, (f + 604));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 608));
    R(5) = (R(28) + 128);
    R(10) = ld32(base, (f + 588));
    R(9) = ld32(base, (f + 592));
    R(8) = ld32(base, (f + 596));
    R(7) = ld32(base, (f + 576));
    R(6) = ld32(base, (f + 580));
    R(0) = ld32(base, (f + 584));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 140), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6626Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3364);
    R(4) = (R(29) + 3376);
    R(3) = (R(29) + 3388);
    R(11) = ld32(base, (R(29) + 3364));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3968);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3376));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3388));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 540), R(11));
    st32(base, (f + 544), R(10));
    st32(base, (f + 548), R(9));
    st32(base, (f + 552), R(8));
    st32(base, (f + 556), R(7));
    st32(base, (f + 560), R(6));
    st32(base, (f + 564), R(5));
    st32(base, (f + 568), R(4));
    st32(base, (f + 572), R(0));
    GM_CALLV(0x80B662C8u, 0x80B63270u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 204);
    GM_CALLV(0x80B662D8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 204);
    R(25) = ld32(base, (f + 564));
    R(12) = ld32(base, (f + 568));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 572));
    R(5) = (R(28) + 192);
    R(10) = ld32(base, (f + 552));
    R(9) = ld32(base, (f + 556));
    R(8) = ld32(base, (f + 560));
    R(7) = ld32(base, (f + 540));
    R(6) = ld32(base, (f + 544));
    R(0) = ld32(base, (f + 548));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 204), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B66338u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3400);
    R(4) = (R(29) + 3412);
    R(3) = (R(29) + 3424);
    R(11) = ld32(base, (R(29) + 3400));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4000);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3412));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3424));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 504), R(11));
    st32(base, (f + 508), R(10));
    st32(base, (f + 512), R(9));
    st32(base, (f + 516), R(8));
    st32(base, (f + 520), R(7));
    st32(base, (f + 524), R(6));
    st32(base, (f + 528), R(5));
    st32(base, (f + 532), R(4));
    st32(base, (f + 536), R(0));
    GM_CALLV(0x80B66394u, 0x80B66EE0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 268);
    GM_CALLV(0x80B663A4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 268);
    R(25) = ld32(base, (f + 528));
    R(12) = ld32(base, (f + 532));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 536));
    R(5) = (R(28) + 256);
    R(10) = ld32(base, (f + 516));
    R(9) = ld32(base, (f + 520));
    R(8) = ld32(base, (f + 524));
    R(7) = ld32(base, (f + 504));
    R(6) = ld32(base, (f + 508));
    R(0) = ld32(base, (f + 512));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 268), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B66404u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3436);
    R(4) = (R(29) + 3448);
    R(3) = (R(29) + 3460);
    R(11) = ld32(base, (R(29) + 3436));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4032);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3448));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3460));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 468), R(11));
    st32(base, (f + 472), R(10));
    st32(base, (f + 476), R(9));
    st32(base, (f + 480), R(8));
    st32(base, (f + 484), R(7));
    st32(base, (f + 488), R(6));
    st32(base, (f + 492), R(5));
    st32(base, (f + 496), R(4));
    st32(base, (f + 500), R(0));
    GM_CALLV(0x80B66460u, 0x80B66ED0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 332);
    GM_CALLV(0x80B66470u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 332);
    R(25) = ld32(base, (f + 492));
    R(12) = ld32(base, (f + 496));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 500));
    R(5) = (R(28) + 320);
    R(10) = ld32(base, (f + 480));
    R(9) = ld32(base, (f + 484));
    R(8) = ld32(base, (f + 488));
    R(7) = ld32(base, (f + 468));
    R(6) = ld32(base, (f + 472));
    R(0) = ld32(base, (f + 476));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 332), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B664D0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3472);
    R(4) = (R(29) + 3484);
    R(3) = (R(29) + 3496);
    R(11) = ld32(base, (R(29) + 3472));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4064);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3484));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3496));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 432), R(11));
    st32(base, (f + 436), R(10));
    st32(base, (f + 440), R(9));
    st32(base, (f + 444), R(8));
    st32(base, (f + 448), R(7));
    st32(base, (f + 452), R(6));
    st32(base, (f + 456), R(5));
    st32(base, (f + 460), R(4));
    st32(base, (f + 464), R(0));
    GM_CALLV(0x80B6652Cu, 0x80B66EC0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 396);
    GM_CALLV(0x80B6653Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 396);
    R(25) = ld32(base, (f + 456));
    R(12) = ld32(base, (f + 460));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 464));
    R(5) = (R(28) + 384);
    R(10) = ld32(base, (f + 444));
    R(9) = ld32(base, (f + 448));
    R(8) = ld32(base, (f + 452));
    R(7) = ld32(base, (f + 432));
    R(6) = ld32(base, (f + 436));
    R(0) = ld32(base, (f + 440));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 396), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6659Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3508);
    R(4) = (R(29) + 3520);
    R(3) = (R(29) + 3532);
    R(11) = ld32(base, (R(29) + 3508));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4100);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3520));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3532));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 396), R(11));
    st32(base, (f + 400), R(10));
    st32(base, (f + 404), R(9));
    st32(base, (f + 408), R(8));
    st32(base, (f + 412), R(7));
    st32(base, (f + 416), R(6));
    st32(base, (f + 420), R(5));
    st32(base, (f + 424), R(4));
    st32(base, (f + 428), R(0));
    GM_CALLV(0x80B665F8u, 0x80B66EB0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 460);
    GM_CALLV(0x80B66608u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 460);
    R(25) = ld32(base, (f + 420));
    R(12) = ld32(base, (f + 424));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 428));
    R(5) = (R(28) + 448);
    R(10) = ld32(base, (f + 408));
    R(9) = ld32(base, (f + 412));
    R(8) = ld32(base, (f + 416));
    R(7) = ld32(base, (f + 396));
    R(6) = ld32(base, (f + 400));
    R(0) = ld32(base, (f + 404));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 460), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B66668u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3544);
    R(4) = (R(29) + 3556);
    R(3) = (R(29) + 3568);
    R(11) = ld32(base, (R(29) + 3544));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4140);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3556));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3568));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 360), R(11));
    st32(base, (f + 364), R(10));
    st32(base, (f + 368), R(9));
    st32(base, (f + 372), R(8));
    st32(base, (f + 376), R(7));
    st32(base, (f + 380), R(6));
    st32(base, (f + 384), R(5));
    st32(base, (f + 388), R(4));
    st32(base, (f + 392), R(0));
    GM_CALLV(0x80B666C4u, 0x80B66EA0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 524);
    GM_CALLV(0x80B666D4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 524);
    R(25) = ld32(base, (f + 384));
    R(12) = ld32(base, (f + 388));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 392));
    R(5) = (R(28) + 512);
    R(10) = ld32(base, (f + 372));
    R(9) = ld32(base, (f + 376));
    R(8) = ld32(base, (f + 380));
    R(7) = ld32(base, (f + 360));
    R(6) = ld32(base, (f + 364));
    R(0) = ld32(base, (f + 368));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 524), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B66734u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3580);
    R(4) = (R(29) + 3592);
    R(3) = (R(29) + 3604);
    R(11) = ld32(base, (R(29) + 3580));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4176);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3592));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3604));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 324), R(11));
    st32(base, (f + 328), R(10));
    st32(base, (f + 332), R(9));
    st32(base, (f + 336), R(8));
    st32(base, (f + 340), R(7));
    st32(base, (f + 344), R(6));
    st32(base, (f + 348), R(5));
    st32(base, (f + 352), R(4));
    st32(base, (f + 356), R(0));
    GM_CALLV(0x80B66790u, 0x80B66E90u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 588);
    GM_CALLV(0x80B667A0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 588);
    R(25) = ld32(base, (f + 348));
    R(12) = ld32(base, (f + 352));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 356));
    R(5) = (R(28) + 576);
    R(10) = ld32(base, (f + 336));
    R(9) = ld32(base, (f + 340));
    R(8) = ld32(base, (f + 344));
    R(7) = ld32(base, (f + 324));
    R(6) = ld32(base, (f + 328));
    R(0) = ld32(base, (f + 332));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 588), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B66800u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3616);
    R(4) = (R(29) + 3628);
    R(3) = (R(29) + 3640);
    R(11) = ld32(base, (R(29) + 3616));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4216);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3628));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3640));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 288), R(11));
    st32(base, (f + 292), R(10));
    st32(base, (f + 296), R(9));
    st32(base, (f + 300), R(8));
    st32(base, (f + 304), R(7));
    st32(base, (f + 308), R(6));
    st32(base, (f + 312), R(5));
    st32(base, (f + 316), R(4));
    st32(base, (f + 320), R(0));
    GM_CALLV(0x80B6685Cu, 0x80B63280u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 652);
    GM_CALLV(0x80B6686Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 652);
    R(25) = ld32(base, (f + 312));
    R(12) = ld32(base, (f + 316));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 320));
    R(5) = (R(28) + 640);
    R(10) = ld32(base, (f + 300));
    R(9) = ld32(base, (f + 304));
    R(8) = ld32(base, (f + 308));
    R(7) = ld32(base, (f + 288));
    R(6) = ld32(base, (f + 292));
    R(0) = ld32(base, (f + 296));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 652), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B668CCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3652);
    R(4) = (R(29) + 3664);
    R(3) = (R(29) + 3676);
    R(11) = ld32(base, (R(29) + 3652));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4248);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3664));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3676));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 252), R(11));
    st32(base, (f + 256), R(10));
    st32(base, (f + 260), R(9));
    st32(base, (f + 264), R(8));
    st32(base, (f + 268), R(7));
    st32(base, (f + 272), R(6));
    st32(base, (f + 276), R(5));
    st32(base, (f + 280), R(4));
    st32(base, (f + 284), R(0));
    GM_CALLV(0x80B66928u, 0x80B63290u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 716);
    GM_CALLV(0x80B66938u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 716);
    R(25) = ld32(base, (f + 276));
    R(12) = ld32(base, (f + 280));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 284));
    R(5) = (R(28) + 704);
    R(10) = ld32(base, (f + 264));
    R(9) = ld32(base, (f + 268));
    R(8) = ld32(base, (f + 272));
    R(7) = ld32(base, (f + 252));
    R(6) = ld32(base, (f + 256));
    R(0) = ld32(base, (f + 260));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 716), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B66998u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3688);
    R(4) = (R(29) + 3700);
    R(3) = (R(29) + 3712);
    R(11) = ld32(base, (R(29) + 3688));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4284);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3700));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3712));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 216), R(11));
    st32(base, (f + 220), R(10));
    st32(base, (f + 224), R(9));
    st32(base, (f + 228), R(8));
    st32(base, (f + 232), R(7));
    st32(base, (f + 236), R(6));
    st32(base, (f + 240), R(5));
    st32(base, (f + 244), R(4));
    st32(base, (f + 248), R(0));
    GM_CALLV(0x80B669F4u, 0x80B66E80u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 780);
    GM_CALLV(0x80B66A04u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 780);
    R(25) = ld32(base, (f + 240));
    R(12) = ld32(base, (f + 244));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 248));
    R(5) = (R(28) + 768);
    R(10) = ld32(base, (f + 228));
    R(9) = ld32(base, (f + 232));
    R(8) = ld32(base, (f + 236));
    R(7) = ld32(base, (f + 216));
    R(6) = ld32(base, (f + 220));
    R(0) = ld32(base, (f + 224));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 780), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B66A64u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3724);
    R(4) = (R(29) + 3736);
    R(3) = (R(29) + 3748);
    R(11) = ld32(base, (R(29) + 3724));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4328);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3736));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3748));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 180), R(11));
    st32(base, (f + 184), R(10));
    st32(base, (f + 188), R(9));
    st32(base, (f + 192), R(8));
    st32(base, (f + 196), R(7));
    st32(base, (f + 200), R(6));
    st32(base, (f + 204), R(5));
    st32(base, (f + 208), R(4));
    st32(base, (f + 212), R(0));
    GM_CALLV(0x80B66AC0u, 0x80B632A0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 844);
    GM_CALLV(0x80B66AD0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 844);
    R(25) = ld32(base, (f + 204));
    R(12) = ld32(base, (f + 208));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 212));
    R(5) = (R(28) + 832);
    R(10) = ld32(base, (f + 192));
    R(9) = ld32(base, (f + 196));
    R(8) = ld32(base, (f + 200));
    R(7) = ld32(base, (f + 180));
    R(6) = ld32(base, (f + 184));
    R(0) = ld32(base, (f + 188));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 844), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B66B30u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3760);
    R(4) = (R(29) + 3772);
    R(3) = (R(29) + 3784);
    R(11) = ld32(base, (R(29) + 3760));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4368);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3772));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3784));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 144), R(11));
    st32(base, (f + 148), R(10));
    st32(base, (f + 152), R(9));
    st32(base, (f + 156), R(8));
    st32(base, (f + 160), R(7));
    st32(base, (f + 164), R(6));
    st32(base, (f + 168), R(5));
    st32(base, (f + 172), R(4));
    st32(base, (f + 176), R(0));
    GM_CALLV(0x80B66B8Cu, 0x80B632B0u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 908);
    GM_CALLV(0x80B66B9Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 908);
    R(26) = ld32(base, (f + 168));
    R(12) = ld32(base, (f + 172));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 176));
    R(5) = (R(28) + 896);
    R(10) = ld32(base, (f + 156));
    R(9) = ld32(base, (f + 160));
    R(8) = ld32(base, (f + 164));
    R(7) = ld32(base, (f + 144));
    R(6) = ld32(base, (f + 148));
    R(0) = ld32(base, (f + 152));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 908), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B66BFCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3796);
    R(4) = (R(29) + 3808);
    R(3) = (R(29) + 3820);
    R(11) = ld32(base, (R(29) + 3796));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4408);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3808));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3820));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 108), R(11));
    st32(base, (f + 112), R(10));
    st32(base, (f + 116), R(9));
    st32(base, (f + 120), R(8));
    st32(base, (f + 124), R(7));
    st32(base, (f + 128), R(6));
    st32(base, (f + 132), R(5));
    st32(base, (f + 136), R(4));
    st32(base, (f + 140), R(0));
    GM_CALLV(0x80B66C58u, 0x80B66E70u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 972);
    GM_CALLV(0x80B66C68u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 972);
    R(27) = ld32(base, (f + 132));
    R(12) = ld32(base, (f + 136));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 140));
    R(5) = (R(28) + 960);
    R(10) = ld32(base, (f + 120));
    R(9) = ld32(base, (f + 124));
    R(8) = ld32(base, (f + 128));
    R(7) = ld32(base, (f + 108));
    R(6) = ld32(base, (f + 112));
    R(0) = ld32(base, (f + 116));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 972), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B66CC8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3832);
    R(4) = (R(29) + 3844);
    R(3) = (R(29) + 3856);
    R(11) = ld32(base, (R(29) + 3832));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4440);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3844));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3856));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 72), R(11));
    st32(base, (f + 76), R(10));
    st32(base, (f + 80), R(9));
    st32(base, (f + 84), R(8));
    st32(base, (f + 88), R(7));
    st32(base, (f + 92), R(6));
    st32(base, (f + 96), R(5));
    st32(base, (f + 100), R(4));
    st32(base, (f + 104), R(0));
    GM_CALLV(0x80B66D24u, 0x80B632C0u, 0);
    R(29) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1036);
    GM_CALLV(0x80B66D34u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1036);
    R(27) = ld32(base, (f + 96));
    R(12) = ld32(base, (f + 100));
    R(4) = (R(31) + 28176);
    R(11) = ld32(base, (f + 104));
    R(5) = (R(28) + 1024);
    R(10) = ld32(base, (f + 84));
    R(9) = ld32(base, (f + 88));
    R(8) = ld32(base, (f + 92));
    R(7) = ld32(base, (f + 72));
    R(6) = ld32(base, (f + 76));
    R(0) = ld32(base, (f + 80));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1036), R(30));
    st32(base, (R(3) + 48), R(29));
    GM_CALLV(0x80B66D94u, 0x80B1CAC0u, 0);
    R(11) = (f + 720);
    R(0) = lr;
}

/* fn_4_4A420 (fn_4_4A420, 12 bytes) */
static void eb_m_66e70(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31356);
}

/* fn_4_4A430 (fn_4_4A430, 12 bytes) */
static void eb_m_66e80(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30716);
}

/* fn_4_4A440 (fn_4_4A440, 12 bytes) */
static void eb_m_66e90(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30780);
}

/* fn_4_4A450 (fn_4_4A450, 12 bytes) */
static void eb_m_66ea0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30844);
}

/* fn_4_4A460 (fn_4_4A460, 12 bytes) */
static void eb_m_66eb0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30908);
}

/* fn_4_4A470 (fn_4_4A470, 12 bytes) */
static void eb_m_66ec0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_4A480 (fn_4_4A480, 12 bytes) */
static void eb_m_66ed0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32252);
}

/* fn_4_4A490 (fn_4_4A490, 12 bytes) */
static void eb_m_66ee0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_4A800 (fn_4_4A800, 12 bytes) */
static void eb_m_67250(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_4A810 (fn_4_4A810, 12 bytes) */
static void eb_m_67260(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_4A820 (fn_4_4A820, 12 bytes) */
static void eb_m_67270(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_4A830 (fn_4_4A830, 12 bytes) */
static void eb_m_67280(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_4A840 (fn_4_4A840, 12 bytes) */
static void eb_m_67290(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 31236);
}

/* fn_4_4DF20 (fn_4_4DF20, 3880 bytes) */
static void eb_m_6a970(GM_CTX) {
    GM_FN(0x80B6A970); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 736);
    R(28) = (0 + 0x80B90000u);
    R(29) = (0 + 0x80B80000u);
    R(28) = (R(28) + -8560);
    R(30) = (0 + 0x80B70000u);
    R(0) = ld8(base, (R(28) + 1088));
    R(30) = (R(30) + 22544);
    { uint32_t ea_ = (R(30) + 196); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(29) = (R(29) + 28768);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    { uint32_t ea_ = (R(30) + 312); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(27) = (R(29) + 72);
    { uint32_t ea_ = (R(30) + 320); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 432); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(26) = (0 + 1163);
    { uint32_t ea_ = (R(30) + 436); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(12) = (R(29) + 816);
    R(9) = (0 + 1097);
    R(25) = (0 + 1164);
    R(11) = (0 + 1165);
    R(10) = (0 + 1166);
    R(8) = (0 + 1167);
    R(7) = (0 + 1156);
    R(6) = (0 + 1157);
    R(5) = (0 + 1158);
    R(4) = (0 + 1159);
    R(3) = (0 + 1160);
    R(0) = (0 + 1161);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(27) + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(27) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(27) + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(27) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(27) + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(27) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(27) + 48); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(29) + 816), R(26));
    st32(base, (R(12) + 8), R(25));
    st32(base, (R(12) + 16), R(11));
    st32(base, (R(12) + 24), R(10));
    st32(base, (R(12) + 32), R(9));
    st32(base, (R(12) + 40), R(8));
    st32(base, (R(12) + 48), R(7));
    st32(base, (R(12) + 56), R(6));
    st32(base, (R(12) + 64), R(5));
    st32(base, (R(12) + 72), R(4));
    st32(base, (R(12) + 80), R(9));
    st32(base, (R(12) + 88), R(3));
    st32(base, (R(12) + 96), R(0));
    st32(base, (R(12) + 104), R(9));
    st32(base, (R(12) + 112), R(9));
    if ((!CR_BIT(ctx, 2))) { goto L_80B6AAE8; }
    { uint32_t ea_ = (R(30) + 200); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (R(29) + 936);
    { uint32_t ea_ = (R(30) + 344); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(30) + 440); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 240); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 204); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 88); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 100); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 112); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 684); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 688); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 692); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(28) + 1088), R(0));
L_80B6AAE8:;
    R(5) = (R(29) + 3264);
    R(4) = (R(29) + 3276);
    R(3) = (R(29) + 3288);
    R(11) = ld32(base, (R(29) + 3264));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(29) + 3876);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3276));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3288));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 648), R(11));
    st32(base, (f + 652), R(10));
    st32(base, (f + 656), R(9));
    st32(base, (f + 660), R(8));
    st32(base, (f + 664), R(7));
    st32(base, (f + 668), R(6));
    st32(base, (f + 672), R(5));
    st32(base, (f + 676), R(4));
    st32(base, (f + 680), R(0));
    GM_CALLV(0x80B6AB44u, 0x80B6BA10u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(28) + 12);
    GM_CALLV(0x80B6AB54u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 12);
    R(25) = ld32(base, (f + 672));
    R(12) = ld32(base, (f + 676));
    R(30) = (0 + 0x80B90000u);
    R(11) = ld32(base, (f + 680));
    R(30) = (R(30) + -32244);
    R(10) = ld32(base, (f + 660));
    R(31) = (0 + 0x80B70000u);
    R(9) = ld32(base, (f + 664));
    R(4) = (R(31) + -18176);
    R(8) = ld32(base, (f + 668));
    R(5) = (R(28) + 0);
    R(7) = ld32(base, (f + 648));
    R(6) = ld32(base, (f + 652));
    R(0) = ld32(base, (f + 656));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 12), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6ABC0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3300);
    R(4) = (R(29) + 3312);
    R(3) = (R(29) + 3324);
    R(11) = ld32(base, (R(29) + 3300));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3912);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3312));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3324));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 612), R(11));
    st32(base, (f + 616), R(10));
    st32(base, (f + 620), R(9));
    st32(base, (f + 624), R(8));
    st32(base, (f + 628), R(7));
    st32(base, (f + 632), R(6));
    st32(base, (f + 636), R(5));
    st32(base, (f + 640), R(4));
    st32(base, (f + 644), R(0));
    GM_CALLV(0x80B6AC1Cu, 0x80B6BA00u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 76);
    GM_CALLV(0x80B6AC2Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 76);
    R(25) = ld32(base, (f + 636));
    R(12) = ld32(base, (f + 640));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 644));
    R(5) = (R(28) + 64);
    R(10) = ld32(base, (f + 624));
    R(9) = ld32(base, (f + 628));
    R(8) = ld32(base, (f + 632));
    R(7) = ld32(base, (f + 612));
    R(6) = ld32(base, (f + 616));
    R(0) = ld32(base, (f + 620));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 76), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6AC8Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3336);
    R(4) = (R(29) + 3348);
    R(3) = (R(29) + 3360);
    R(11) = ld32(base, (R(29) + 3336));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3952);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3348));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3360));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 576), R(11));
    st32(base, (f + 580), R(10));
    st32(base, (f + 584), R(9));
    st32(base, (f + 588), R(8));
    st32(base, (f + 592), R(7));
    st32(base, (f + 596), R(6));
    st32(base, (f + 600), R(5));
    st32(base, (f + 604), R(4));
    st32(base, (f + 608), R(0));
    GM_CALLV(0x80B6ACE8u, 0x80B6B9F0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 140);
    GM_CALLV(0x80B6ACF8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 140);
    R(25) = ld32(base, (f + 600));
    R(12) = ld32(base, (f + 604));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 608));
    R(5) = (R(28) + 128);
    R(10) = ld32(base, (f + 588));
    R(9) = ld32(base, (f + 592));
    R(8) = ld32(base, (f + 596));
    R(7) = ld32(base, (f + 576));
    R(6) = ld32(base, (f + 580));
    R(0) = ld32(base, (f + 584));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 140), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6AD58u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3372);
    R(4) = (R(29) + 3384);
    R(3) = (R(29) + 3396);
    R(11) = ld32(base, (R(29) + 3372));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 3984);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3384));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3396));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 540), R(11));
    st32(base, (f + 544), R(10));
    st32(base, (f + 548), R(9));
    st32(base, (f + 552), R(8));
    st32(base, (f + 556), R(7));
    st32(base, (f + 560), R(6));
    st32(base, (f + 564), R(5));
    st32(base, (f + 568), R(4));
    st32(base, (f + 572), R(0));
    GM_CALLV(0x80B6ADB4u, 0x80B6B9E0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 204);
    GM_CALLV(0x80B6ADC4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 204);
    R(25) = ld32(base, (f + 564));
    R(12) = ld32(base, (f + 568));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 572));
    R(5) = (R(28) + 192);
    R(10) = ld32(base, (f + 552));
    R(9) = ld32(base, (f + 556));
    R(8) = ld32(base, (f + 560));
    R(7) = ld32(base, (f + 540));
    R(6) = ld32(base, (f + 544));
    R(0) = ld32(base, (f + 548));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 204), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6AE24u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3408);
    R(4) = (R(29) + 3420);
    R(3) = (R(29) + 3432);
    R(11) = ld32(base, (R(29) + 3408));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4016);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3420));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3432));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 504), R(11));
    st32(base, (f + 508), R(10));
    st32(base, (f + 512), R(9));
    st32(base, (f + 516), R(8));
    st32(base, (f + 520), R(7));
    st32(base, (f + 524), R(6));
    st32(base, (f + 528), R(5));
    st32(base, (f + 532), R(4));
    st32(base, (f + 536), R(0));
    GM_CALLV(0x80B6AE80u, 0x80B6B9D0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 268);
    GM_CALLV(0x80B6AE90u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 268);
    R(25) = ld32(base, (f + 528));
    R(12) = ld32(base, (f + 532));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 536));
    R(5) = (R(28) + 256);
    R(10) = ld32(base, (f + 516));
    R(9) = ld32(base, (f + 520));
    R(8) = ld32(base, (f + 524));
    R(7) = ld32(base, (f + 504));
    R(6) = ld32(base, (f + 508));
    R(0) = ld32(base, (f + 512));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 268), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6AEF0u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3444);
    R(4) = (R(29) + 3456);
    R(3) = (R(29) + 3468);
    R(11) = ld32(base, (R(29) + 3444));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4052);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3456));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3468));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 468), R(11));
    st32(base, (f + 472), R(10));
    st32(base, (f + 476), R(9));
    st32(base, (f + 480), R(8));
    st32(base, (f + 484), R(7));
    st32(base, (f + 488), R(6));
    st32(base, (f + 492), R(5));
    st32(base, (f + 496), R(4));
    st32(base, (f + 500), R(0));
    GM_CALLV(0x80B6AF4Cu, 0x80B6B9C0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 332);
    GM_CALLV(0x80B6AF5Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 332);
    R(25) = ld32(base, (f + 492));
    R(12) = ld32(base, (f + 496));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 500));
    R(5) = (R(28) + 320);
    R(10) = ld32(base, (f + 480));
    R(9) = ld32(base, (f + 484));
    R(8) = ld32(base, (f + 488));
    R(7) = ld32(base, (f + 468));
    R(6) = ld32(base, (f + 472));
    R(0) = ld32(base, (f + 476));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 332), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6AFBCu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3480);
    R(4) = (R(29) + 3492);
    R(3) = (R(29) + 3504);
    R(11) = ld32(base, (R(29) + 3480));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4088);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3492));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3504));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 432), R(11));
    st32(base, (f + 436), R(10));
    st32(base, (f + 440), R(9));
    st32(base, (f + 444), R(8));
    st32(base, (f + 448), R(7));
    st32(base, (f + 452), R(6));
    st32(base, (f + 456), R(5));
    st32(base, (f + 460), R(4));
    st32(base, (f + 464), R(0));
    GM_CALLV(0x80B6B018u, 0x80B6B9B0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 396);
    GM_CALLV(0x80B6B028u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 396);
    R(25) = ld32(base, (f + 456));
    R(12) = ld32(base, (f + 460));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 464));
    R(5) = (R(28) + 384);
    R(10) = ld32(base, (f + 444));
    R(9) = ld32(base, (f + 448));
    R(8) = ld32(base, (f + 452));
    R(7) = ld32(base, (f + 432));
    R(6) = ld32(base, (f + 436));
    R(0) = ld32(base, (f + 440));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 396), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6B088u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3516);
    R(4) = (R(29) + 3528);
    R(3) = (R(29) + 3540);
    R(11) = ld32(base, (R(29) + 3516));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4128);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3528));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3540));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 396), R(11));
    st32(base, (f + 400), R(10));
    st32(base, (f + 404), R(9));
    st32(base, (f + 408), R(8));
    st32(base, (f + 412), R(7));
    st32(base, (f + 416), R(6));
    st32(base, (f + 420), R(5));
    st32(base, (f + 424), R(4));
    st32(base, (f + 428), R(0));
    GM_CALLV(0x80B6B0E4u, 0x80B6B9A0u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 460);
    GM_CALLV(0x80B6B0F4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 460);
    R(25) = ld32(base, (f + 420));
    R(12) = ld32(base, (f + 424));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 428));
    R(5) = (R(28) + 448);
    R(10) = ld32(base, (f + 408));
    R(9) = ld32(base, (f + 412));
    R(8) = ld32(base, (f + 416));
    R(7) = ld32(base, (f + 396));
    R(6) = ld32(base, (f + 400));
    R(0) = ld32(base, (f + 404));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 460), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6B154u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3552);
    R(4) = (R(29) + 3564);
    R(3) = (R(29) + 3576);
    R(11) = ld32(base, (R(29) + 3552));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4168);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3564));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3576));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 360), R(11));
    st32(base, (f + 364), R(10));
    st32(base, (f + 368), R(9));
    st32(base, (f + 372), R(8));
    st32(base, (f + 376), R(7));
    st32(base, (f + 380), R(6));
    st32(base, (f + 384), R(5));
    st32(base, (f + 388), R(4));
    st32(base, (f + 392), R(0));
    GM_CALLV(0x80B6B1B0u, 0x80B6B990u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 524);
    GM_CALLV(0x80B6B1C0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 524);
    R(25) = ld32(base, (f + 384));
    R(12) = ld32(base, (f + 388));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 392));
    R(5) = (R(28) + 512);
    R(10) = ld32(base, (f + 372));
    R(9) = ld32(base, (f + 376));
    R(8) = ld32(base, (f + 380));
    R(7) = ld32(base, (f + 360));
    R(6) = ld32(base, (f + 364));
    R(0) = ld32(base, (f + 368));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 524), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6B220u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3588);
    R(4) = (R(29) + 3600);
    R(3) = (R(29) + 3612);
    R(11) = ld32(base, (R(29) + 3588));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4208);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3600));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3612));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 324), R(11));
    st32(base, (f + 328), R(10));
    st32(base, (f + 332), R(9));
    st32(base, (f + 336), R(8));
    st32(base, (f + 340), R(7));
    st32(base, (f + 344), R(6));
    st32(base, (f + 348), R(5));
    st32(base, (f + 352), R(4));
    st32(base, (f + 356), R(0));
    GM_CALLV(0x80B6B27Cu, 0x80B67250u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 588);
    GM_CALLV(0x80B6B28Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 588);
    R(25) = ld32(base, (f + 348));
    R(12) = ld32(base, (f + 352));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 356));
    R(5) = (R(28) + 576);
    R(10) = ld32(base, (f + 336));
    R(9) = ld32(base, (f + 340));
    R(8) = ld32(base, (f + 344));
    R(7) = ld32(base, (f + 324));
    R(6) = ld32(base, (f + 328));
    R(0) = ld32(base, (f + 332));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 588), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6B2ECu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3624);
    R(4) = (R(29) + 3636);
    R(3) = (R(29) + 3648);
    R(11) = ld32(base, (R(29) + 3624));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4244);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3636));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3648));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 288), R(11));
    st32(base, (f + 292), R(10));
    st32(base, (f + 296), R(9));
    st32(base, (f + 300), R(8));
    st32(base, (f + 304), R(7));
    st32(base, (f + 308), R(6));
    st32(base, (f + 312), R(5));
    st32(base, (f + 316), R(4));
    st32(base, (f + 320), R(0));
    GM_CALLV(0x80B6B348u, 0x80B67260u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 652);
    GM_CALLV(0x80B6B358u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 652);
    R(25) = ld32(base, (f + 312));
    R(12) = ld32(base, (f + 316));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 320));
    R(5) = (R(28) + 640);
    R(10) = ld32(base, (f + 300));
    R(9) = ld32(base, (f + 304));
    R(8) = ld32(base, (f + 308));
    R(7) = ld32(base, (f + 288));
    R(6) = ld32(base, (f + 292));
    R(0) = ld32(base, (f + 296));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 652), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6B3B8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3660);
    R(4) = (R(29) + 3672);
    R(3) = (R(29) + 3684);
    R(11) = ld32(base, (R(29) + 3660));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4280);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3672));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3684));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 252), R(11));
    st32(base, (f + 256), R(10));
    st32(base, (f + 260), R(9));
    st32(base, (f + 264), R(8));
    st32(base, (f + 268), R(7));
    st32(base, (f + 272), R(6));
    st32(base, (f + 276), R(5));
    st32(base, (f + 280), R(4));
    st32(base, (f + 284), R(0));
    GM_CALLV(0x80B6B414u, 0x80B6B980u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 716);
    GM_CALLV(0x80B6B424u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 716);
    R(25) = ld32(base, (f + 276));
    R(12) = ld32(base, (f + 280));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 284));
    R(5) = (R(28) + 704);
    R(10) = ld32(base, (f + 264));
    R(9) = ld32(base, (f + 268));
    R(8) = ld32(base, (f + 272));
    R(7) = ld32(base, (f + 252));
    R(6) = ld32(base, (f + 256));
    R(0) = ld32(base, (f + 260));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 716), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6B484u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3696);
    R(4) = (R(29) + 3708);
    R(3) = (R(29) + 3720);
    R(11) = ld32(base, (R(29) + 3696));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4320);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3708));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3720));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 216), R(11));
    st32(base, (f + 220), R(10));
    st32(base, (f + 224), R(9));
    st32(base, (f + 228), R(8));
    st32(base, (f + 232), R(7));
    st32(base, (f + 236), R(6));
    st32(base, (f + 240), R(5));
    st32(base, (f + 244), R(4));
    st32(base, (f + 248), R(0));
    GM_CALLV(0x80B6B4E0u, 0x80B67270u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 780);
    GM_CALLV(0x80B6B4F0u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 780);
    R(25) = ld32(base, (f + 240));
    R(12) = ld32(base, (f + 244));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 248));
    R(5) = (R(28) + 768);
    R(10) = ld32(base, (f + 228));
    R(9) = ld32(base, (f + 232));
    R(8) = ld32(base, (f + 236));
    R(7) = ld32(base, (f + 216));
    R(6) = ld32(base, (f + 220));
    R(0) = ld32(base, (f + 224));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 780), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6B550u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3732);
    R(4) = (R(29) + 3744);
    R(3) = (R(29) + 3756);
    R(11) = ld32(base, (R(29) + 3732));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4364);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3744));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3756));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 180), R(11));
    st32(base, (f + 184), R(10));
    st32(base, (f + 188), R(9));
    st32(base, (f + 192), R(8));
    st32(base, (f + 196), R(7));
    st32(base, (f + 200), R(6));
    st32(base, (f + 204), R(5));
    st32(base, (f + 208), R(4));
    st32(base, (f + 212), R(0));
    GM_CALLV(0x80B6B5ACu, 0x80B67280u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 844);
    GM_CALLV(0x80B6B5BCu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 844);
    R(25) = ld32(base, (f + 204));
    R(12) = ld32(base, (f + 208));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 212));
    R(5) = (R(28) + 832);
    R(10) = ld32(base, (f + 192));
    R(9) = ld32(base, (f + 196));
    R(8) = ld32(base, (f + 200));
    R(7) = ld32(base, (f + 180));
    R(6) = ld32(base, (f + 184));
    R(0) = ld32(base, (f + 188));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 844), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6B61Cu, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3768);
    R(4) = (R(29) + 3780);
    R(3) = (R(29) + 3792);
    R(11) = ld32(base, (R(29) + 3768));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4408);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3780));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3792));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 144), R(11));
    st32(base, (f + 148), R(10));
    st32(base, (f + 152), R(9));
    st32(base, (f + 156), R(8));
    st32(base, (f + 160), R(7));
    st32(base, (f + 164), R(6));
    st32(base, (f + 168), R(5));
    st32(base, (f + 172), R(4));
    st32(base, (f + 176), R(0));
    GM_CALLV(0x80B6B678u, 0x80B6B970u, 0);
    R(25) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 908);
    GM_CALLV(0x80B6B688u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 908);
    R(26) = ld32(base, (f + 168));
    R(12) = ld32(base, (f + 172));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 176));
    R(5) = (R(28) + 896);
    R(10) = ld32(base, (f + 156));
    R(9) = ld32(base, (f + 160));
    R(8) = ld32(base, (f + 164));
    R(7) = ld32(base, (f + 144));
    R(6) = ld32(base, (f + 148));
    R(0) = ld32(base, (f + 152));
    st32(base, (R(3) + 12), R(26));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 908), R(30));
    st32(base, (R(3) + 48), R(25));
    GM_CALLV(0x80B6B6E8u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3804);
    R(4) = (R(29) + 3816);
    R(3) = (R(29) + 3828);
    R(11) = ld32(base, (R(29) + 3804));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4448);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3816));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3828));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 108), R(11));
    st32(base, (f + 112), R(10));
    st32(base, (f + 116), R(9));
    st32(base, (f + 120), R(8));
    st32(base, (f + 124), R(7));
    st32(base, (f + 128), R(6));
    st32(base, (f + 132), R(5));
    st32(base, (f + 136), R(4));
    st32(base, (f + 140), R(0));
    GM_CALLV(0x80B6B744u, 0x80B6B960u, 0);
    R(26) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 972);
    GM_CALLV(0x80B6B754u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 972);
    R(27) = ld32(base, (f + 132));
    R(12) = ld32(base, (f + 136));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 140));
    R(5) = (R(28) + 960);
    R(10) = ld32(base, (f + 120));
    R(9) = ld32(base, (f + 124));
    R(8) = ld32(base, (f + 128));
    R(7) = ld32(base, (f + 108));
    R(6) = ld32(base, (f + 112));
    R(0) = ld32(base, (f + 116));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 972), R(30));
    st32(base, (R(3) + 48), R(26));
    GM_CALLV(0x80B6B7B4u, 0x80B1CAC0u, 0);
    R(5) = (R(29) + 3840);
    R(4) = (R(29) + 3852);
    R(3) = (R(29) + 3864);
    R(11) = ld32(base, (R(29) + 3840));
    R(10) = ld32(base, (R(5) + 4));
    R(27) = (R(29) + 4484);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(29) + 3852));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(29) + 3864));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 72), R(11));
    st32(base, (f + 76), R(10));
    st32(base, (f + 80), R(9));
    st32(base, (f + 84), R(8));
    st32(base, (f + 88), R(7));
    st32(base, (f + 92), R(6));
    st32(base, (f + 96), R(5));
    st32(base, (f + 100), R(4));
    st32(base, (f + 104), R(0));
    GM_CALLV(0x80B6B810u, 0x80B67290u, 0);
    R(29) = R(3) |R(3);
    R(4) = R(27) |R(27);
    R(3) = (R(28) + 1036);
    GM_CALLV(0x80B6B820u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 1036);
    R(27) = ld32(base, (f + 96));
    R(12) = ld32(base, (f + 100));
    R(4) = (R(31) + -18176);
    R(11) = ld32(base, (f + 104));
    R(5) = (R(28) + 1024);
    R(10) = ld32(base, (f + 84));
    R(9) = ld32(base, (f + 88));
    R(8) = ld32(base, (f + 92));
    R(7) = ld32(base, (f + 72));
    R(6) = ld32(base, (f + 76));
    R(0) = ld32(base, (f + 80));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(28) + 1036), R(30));
    st32(base, (R(3) + 48), R(29));
    GM_CALLV(0x80B6B880u, 0x80B1CAC0u, 0);
    R(11) = (f + 736);
    R(0) = lr;
}

/* fn_4_4EF10 (fn_4_4EF10, 12 bytes) */
static void eb_m_6b960(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31356);
}

/* fn_4_4EF20 (fn_4_4EF20, 12 bytes) */
static void eb_m_6b970(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31420);
}

/* fn_4_4EF30 (fn_4_4EF30, 12 bytes) */
static void eb_m_6b980(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30716);
}

/* fn_4_4EF40 (fn_4_4EF40, 12 bytes) */
static void eb_m_6b990(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30780);
}

/* fn_4_4EF50 (fn_4_4EF50, 12 bytes) */
static void eb_m_6b9a0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30844);
}

/* fn_4_4EF60 (fn_4_4EF60, 12 bytes) */
static void eb_m_6b9b0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30908);
}

/* fn_4_4EF70 (fn_4_4EF70, 12 bytes) */
static void eb_m_6b9c0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -30972);
}

/* fn_4_4EF80 (fn_4_4EF80, 12 bytes) */
static void eb_m_6b9d0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32252);
}

/* fn_4_4EF90 (fn_4_4EF90, 12 bytes) */
static void eb_m_6b9e0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -32380);
}

/* fn_4_4EFA0 (fn_4_4EFA0, 12 bytes) */
static void eb_m_6b9f0(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31932);
}

/* fn_4_4EFB0 (fn_4_4EFB0, 12 bytes) */
static void eb_m_6ba00(GM_CTX) {
    R(3) = (0 + 0x80360000u);
    R(3) = (R(3) + -31292);
}

/* fn_4_4EFC0 (fn_4_4EFC0, 12 bytes) */
static void eb_m_6ba10(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 30452);
}

/* fn_4_4F3C0 (fn_4_4F3C0, 612 bytes) */
static void eb_m_6be10(GM_CTX) {
    GM_FN(0x80B6BE10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(30) = R(3) |R(3);
    GM_CALLV(0x80B6BE2Cu, 0x800CDC60u, 0);
    R(4) = (0 + 0x80310000u);
    R(5) = (0 + 0x80430000u);
    R(4) = (R(4) + 23440);
    R(29) = ld32(base, (R(5) + -24708));
    R(27) = ld8(base, (R(4) + 12));
    R(31) = R(3) |R(3);
    R(28) = ld8(base, (R(4) + 13));
    cr_cmp_u(ctx, 0, R(27), 0x9u);
    if ((CR_BIT(ctx, 0))) { goto L_80B6BE54; }
    R(27) = (0 + 9);
L_80B6BE54:;
    R(0) = rotl32(R(27), 2) & 0x3FCu;
    R(4) = R(31) |R(31);
    R(3) = R(30) + R(0);
    R(5) = (0 + 102);
    R(3) = ld32(base, (R(3) + 524));
    R(6) = (0 + 31);
    R(7) = (0 + 0);
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(30) + 416));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80B6BE8Cu, 0x800C9A60u, 0);
    R(3) = R(27) & 0xFFu;
    R(4) = R(31) |R(31);
    R(0) = (R(3) + 1);
    st32(base, (R(29) + 948), R(0));
    R(5) = (0 + 102);
    R(6) = (0 + 32);
    R(3) = ld32(base, (R(30) + 420));
    R(7) = (0 + 0);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80B6BEB4u, 0x800C9A60u, 0);
    R(3) = ld32(base, (R(30) + 412));
    R(4) = R(31) |R(31);
    R(5) = (0 + 102);
    R(6) = (0 + 41);
    R(7) = (0 + 0);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80B6BED0u, 0x800C9A60u, 0);
    R(0) = (R(28) + -20);
    cr_cmp_u(ctx, 0, R(0), 0x14u);
    if ((CR_BIT(ctx, 1))) { goto L_80B6BFD4; }
    R(3) = (0 + 0x80B90000u);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = (R(3) + -32084);
    R(3) = ld32(base, (R(3) + R(0)));
    ctx->ctr = R(3);
    { switch (ctx->ctr) { case 0x80B6BEF4u: goto L_80B6BEF4; case 0x80B6BEFCu: goto L_80B6BEFC; case 0x80B6BF04u: goto L_80B6BF04; case 0x80B6BF20u: goto L_80B6BF20; case 0x80B6BF68u: goto L_80B6BF68; case 0x80B6BF98u: goto L_80B6BF98; case 0x80B6BFA0u: goto L_80B6BFA0; case 0x80B6BFA8u: goto L_80B6BFA8; case 0x80B6BFB0u: goto L_80B6BFB0; case 0x80B6BFB8u: goto L_80B6BFB8; case 0x80B6BFD4u: goto L_80B6BFD4; default: rt_fatal("80B6BE10: jump table target %08X", ctx->ctr); return; } }
L_80B6BEF4:;
    R(6) = (0 + 36);
    goto L_80B6C020;
L_80B6BEFC:;
    R(6) = (0 + 35);
    goto L_80B6C020;
L_80B6BF04:;
    R(0) = R(27) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x7u);
    if ((CR_BIT(ctx, 2))) { goto L_80B6BF18; }
    R(6) = (0 + 34);
    goto L_80B6C020;
L_80B6BF18:;
    R(6) = (0 + 26);
    goto L_80B6C020;
L_80B6BF20:;
    R(4) = R(28) |R(28);
    R(3) = R(27) & 0xFFu;
    R(5) = (0 + 128);
    GM_CALLV(0x80B6BF30u, 0x80102750u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B6BF40; }
    R(6) = (0 + 24);
    goto L_80B6C020;
L_80B6BF40:;
    R(4) = R(28) |R(28);
    R(3) = R(27) & 0xFFu;
    R(5) = (0 + 512);
    GM_CALLV(0x80B6BF50u, 0x80102750u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B6BF60; }
    R(6) = (0 + 25);
    goto L_80B6C020;
L_80B6BF60:;
    R(6) = (0 + 39);
    goto L_80B6C020;
L_80B6BF68:;
    GM_CALLV(0x80B6BF6Cu, 0x800FB3C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B6BF7C; }
    R(6) = (0 + 25);
    goto L_80B6C020;
L_80B6BF7C:;
    GM_CALLV(0x80B6BF80u, 0x800FB460u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B6BF90; }
    R(6) = (0 + 39);
    goto L_80B6C020;
L_80B6BF90:;
    R(6) = (0 + 24);
    goto L_80B6C020;
L_80B6BF98:;
    R(6) = (0 + 27);
    goto L_80B6C020;
L_80B6BFA0:;
    R(6) = (0 + 37);
    goto L_80B6C020;
L_80B6BFA8:;
    R(6) = (0 + 23);
    goto L_80B6C020;
L_80B6BFB0:;
    R(6) = (0 + 38);
    goto L_80B6C020;
L_80B6BFB8:;
    GM_CALLV(0x80B6BFBCu, 0x800FBFF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B6BFCC; }
    R(6) = (0 + 28);
    goto L_80B6C020;
L_80B6BFCC:;
    R(6) = (0 + 38);
    goto L_80B6C020;
L_80B6BFD4:;
    R(0) = (R(28) + 1);
    st32(base, (R(29) + 952), R(0));
    R(4) = R(31) |R(31);
    R(5) = (0 + 102);
    R(3) = ld32(base, (R(30) + 428));
    R(6) = (0 + 33);
    R(7) = (0 + 0);
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(30) + 428));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80B6C00Cu, 0x800C9A60u, 0);
    R(3) = ld32(base, (R(30) + 424));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    goto L_80B6C05C;
L_80B6C020:;
    R(3) = ld32(base, (R(30) + 428));
    R(4) = R(31) |R(31);
    R(5) = (0 + 102);
    R(7) = (0 + 0);
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(30) + 424));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(30) + 424));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80B6C05Cu, 0x800C9A60u, 0);
L_80B6C05C:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_4_4FA80 (fn_4_4FA80, 204 bytes) */
static void eb_m_6c4d0(GM_CTX) {
    GM_FN(0x80B6C4D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld8(base, (R(3) + 736));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C4FC; }
    R(0) = ld8(base, (R(3) + 738));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B6C588; }
L_80B6C4FC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x80B6C504u, 0x80B6C5D0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C588; }
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 23440);
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C568; }
    R(0) = ld8(base, (R(31) + 739));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C568; }
    R(4) = ld32(base, (R(31) + 388));
    R(3) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(3) + 23376); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(4) + 40));
    { uint32_t ea_ = (R(3) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C568; }
    R(3) = (0 + 0x80430000u);
    R(4) = (0 + 939);
    R(3) = ld32(base, (R(3) + -23416));
    R(5) = (0 + 1);
    GM_CALLV(0x80B6C560u, 0x80195380u, 0);
    R(0) = (0 + 1);
    st8(base, (R(31) + 739), R(0));
L_80B6C568:;
    R(0) = ld32(base, (R(31) + 740));
    R(4) = (0 + 0x80B70000u);
    R(4) = (R(4) + 23280);
    R(3) = R(31) |R(31);
    R(0) = ((int32_t)R(0) * 12);
    R(12) = R(4) + R(0);
    GM_CALLV(0x80B6C584u, 0x802DCBFCu, 0);
    R(0) = R(0) | 0x0u;
L_80B6C588:;
    R(0) = lr;
}

/* fn_4_4FB50 (fn_4_4FB50, 28 bytes) */
static void eb_m_6c5a0(GM_CTX) {
    R(0) = ld8(base, (R(3) + 736));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) return;
    R(0) = ld8(base, (R(3) + 738));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) return;
    GM_TAIL(0x80006EA0u, 0); return;
}

/* fn_4_4FB70 (fn_4_4FB70, 4 bytes) */
static void eb_m_6c5c0(GM_CTX) {
    GM_TAIL(0x800C9930u, 0); return;
}

/* fn_4_4FB80 (fn_4_4FB80, 360 bytes) */
static void eb_m_6c5d0(GM_CTX) {
    GM_FN(0x80B6C5D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = (0 + 0x80310000u);
    R(30) = (R(30) + 23440);
    R(0) = ld32(base, (R(30) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C608; }
    R(3) = (0 + 0);
    goto L_80B6C718;
L_80B6C608:;
    R(0) = ld32(base, (R(3) + 740));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C61C; }
    R(3) = (0 + 0);
    goto L_80B6C718;
L_80B6C61C:;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23488));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x80B6C634u, ctx->ctr, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C64C; }
    R(3) = (0 + 0);
    goto L_80B6C718;
L_80B6C64C:;
    R(3) = (0 + 0x80430000u);
    R(0) = ld16(base, (R(3) + -30928));
    cr_cmp_u(ctx, 0, R(0), 0x2EEu);
    if ((CR_BIT(ctx, 2))) { goto L_80B6C664; }
    R(3) = (0 + 0);
    goto L_80B6C718;
L_80B6C664:;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24704));
    R(0) = R(3) & 0x40000000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C714; }
    R(0) = R(3) & 0x80000000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C714; }
    R(0) = ld32(base, (R(30) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C714; }
    R(0) = ld8(base, (R(30) + 13));
    cr_cmp_u(ctx, 0, R(0), 0x29u);
    if ((CR_BIT(ctx, 2))) { goto L_80B6C714; }
    R(28) = (0 + 0);
    R(29) = (0 + 0);
    R(30) = (0 + 0x80430000u);
    R(31) = (0 + 0x80370000u);
L_80B6C6A4:;
    R(0) = ld32(base, (R(30) + -24536));
    R(3) = R(0) + R(29);
    R(3) = ld32(base, (R(3) + 4));
    { uint32_t ea_ = R(3) + 92; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x80B6C6C0u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (R(31) + 6256);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x80B6C6D4u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6C704; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x80B6C6E4u, 0x800B4710u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B6C704; }
    R(3) = (0 + 0x80430000u);
    R(4) = R(28) |R(28);
    R(3) = ld32(base, (R(3) + -23848));
    GM_CALLV(0x80B6C6FCu, 0x8010E600u, 0);
    R(3) = (0 + 1);
    goto L_80B6C718;
L_80B6C704:;
    R(28) = (R(28) + 1);
    R(29) = (R(29) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80B6C6A4; }
L_80B6C714:;
    R(3) = (0 + 0);
L_80B6C718:;
    R(0) = lr;
}

/* fn_4_4FCF0 (fn_4_4FCF0, 16 bytes) */
static void eb_m_6c740(GM_CTX) {
    R(0) = (0 + 0);
    st8(base, (R(3) + 737), R(0));
    R(3) = (0 + 0);
    GM_TAIL(0x8016F640u, 0); return;
}

/* fn_4_50370 (fn_4_50370, 128 bytes) */
static void eb_m_6cdc0(GM_CTX) {
    GM_FN(0x80B6CDC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0);
    R(31) = R(3) |R(3);
    GM_CALLV(0x80B6CDDCu, 0x800C9610u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6CE2C; }
    R(0) = (0 + -1);
    R(3) = (0 + 0x80310000u);
    st32(base, (R(31) + 756), R(0));
    R(3) = (R(3) + 23440);
    st32(base, (R(31) + 760), R(0));
    st32(base, (R(31) + 764), R(0));
    st32(base, (R(31) + 768), R(0));
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6CE24; }
    R(0) = ld8(base, (R(3) + 13));
    cr_cmp_u(ctx, 0, R(0), 0x29u);
    if ((CR_BIT(ctx, 2))) { goto L_80B6CE24; }
    R(0) = (0 + 3);
    st32(base, (R(31) + 740), R(0));
    goto L_80B6CE2C;
L_80B6CE24:;
    R(0) = (0 + 6);
    st32(base, (R(31) + 740), R(0));
L_80B6CE2C:;
    R(0) = lr;
}

/* fn_4_506B0 (fn_4_506B0, 4 bytes) */
static void eb_m_6d100(GM_CTX) {

}

/* fn_4_506C0 (fn_4_506C0, 132 bytes) */
static void eb_m_6d110(GM_CTX) {
    GM_FN(0x80B6D110); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80B70000u);
    R(6) = (0 + 0x80B90000u);
    R(5) = (R(5) + 23144);
    R(3) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(5) + 380); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -32120);
    { uint32_t ea_ = (R(5) + 384); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 388); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x80B70000u);
    R(0) = ld32(base, (R(3) + -12436));
    R(5) = (0 + 0x80B90000u);
    st32(base, (R(6) + 12), R(0));
    R(4) = (R(4) + -11872);
    R(5) = (R(5) + -7464);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B6D174u, 0x80B1CAC0u, 0);
    R(4) = (0 + 0x80430000u);
    R(3) = (0 + 0x80B90000u);
    R(0) = ld32(base, (R(4) + -12412));
    st32(base, (R(3) + -7452), R(0));
    R(0) = lr;
}

/* fn_4_507B0 (fn_4_507B0, 80 bytes) */
static void eb_m_6d200(GM_CTX) {
    R(4) = (0 + 0x80B70000u);
    GM_FRAME(32); gptr f = gm_frame_sp;
    { uint32_t ea_ = (R(4) + 23544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + 41), R(0));
}

/* fn_4_50800 (fn_4_50800, 108 bytes) */
static void eb_m_6d250(GM_CTX) {
    GM_FRAME(32); gptr f = gm_frame_sp;
    R(0) = ld8(base, (R(3) + 41));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B6D2B4; }
    R(4) = (0 + 0x80B70000u);
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(4) + 23544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[4].d); }
    st8(base, (R(3) + 41), R(0));
L_80B6D2B4:;
}

/* fn_4_508C0 (fn_4_508C0, 232 bytes) */
static void eb_m_6d310(GM_CTX) {
    GM_FN(0x80B6D310); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = R(31) |R(31);
    { uint32_t ea_ = (R(3) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 16); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 48); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 52); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (R(3) + 12);
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B6D354u, 0x80160AE0u, 0);
    { uint32_t ea_ = (R(31) + 20); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 8);
    { uint32_t ea_ = (f + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[2].d - ctx->f[1].d);
    { uint32_t ea_ = (R(31) + 16); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 36); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[3].d - ctx->f[1].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    { uint32_t ea_ = (R(31) + 28); stfs(base, ea_, ctx->f[5].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[6].d); }
    GM_CALLV(0x80B6D3BCu, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(31) + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    R(0) = ctx->cr;
    R(0) = rotl32(R(0), 3) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B6D3E4; }
    R(0) = (0 + 0);
    st8(base, (R(31) + 40), R(0));
L_80B6D3E4:;
    R(0) = lr;
}

/* fn_4_51750 (fn_4_51750, 1140 bytes) */
static void eb_m_6e1a0(GM_CTX) {
    GM_FN(0x80B6E1A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80B90000u);
    R(4) = (0 + 0x80B70000u);
    R(3) = (0 + 0x80430000u);
    R(0) = ld32(base, (R(3) + -12436));
    R(6) = (R(6) + -30000);
    R(31) = (0 + 0x80B70000u);
    R(31) = (R(31) + 23552);
    R(4) = (R(4) + -6624);
    R(30) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(31) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(30) = (R(30) + -7448);
    { uint32_t ea_ = (R(31) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (R(30) + 0);
    { uint32_t ea_ = (R(31) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0);
    st32(base, (R(6) + 12), R(0));
    { uint32_t ea_ = (f + 488); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 492); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 496); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B6E210u, 0x80B1CAC0u, 0);
    R(0) = ld8(base, (R(30) + 25));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -12412));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    st32(base, (R(30) + 12), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_80B6E5FC; }
    R(3) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(31) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(3) + -29964);
    { uint32_t ea_ = (f + 476); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 480); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 484); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 464); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 468); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 472); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 452); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 456); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 460); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 60); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 440); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 444); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 448); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 64); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 68); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 72); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 428); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 432); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 436); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 76); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 80); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 84); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 416); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 420); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 424); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 88); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 404); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 408); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 412); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 100); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 392); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 396); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 400); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 112); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 380); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 384); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 388); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 132); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 368); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 372); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 376); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 140); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 144); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 356); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 360); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 364); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 148); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 156); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 344); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 348); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 352); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 160); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 164); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 332); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 336); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 340); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 320); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 324); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 328); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 184); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 188); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 192); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 308); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 312); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 316); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 196); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 200); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 204); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 304); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 208); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 212); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 216); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 292); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 220); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 224); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 228); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 272); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 276); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 280); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 232); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 236); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 240); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 260); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 264); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 268); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 244); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 248); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 252); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 248); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 252); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 256); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 256); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 260); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 264); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 236); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 240); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 244); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 268); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 272); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 276); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 224); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 228); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 232); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 280); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 212); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 216); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 220); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 292); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 200); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 204); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 208); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 304); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 308); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 312); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 188); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 192); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 196); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 316); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 320); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 324); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 176); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 180); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 184); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 328); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 332); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 336); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 164); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 168); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 172); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 340); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 344); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 348); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 152); stfs(base, ea_, ctx->f[0].d); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (f + 156); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 160); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 352); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 356); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 360); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 140); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 144); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 148); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 364); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 368); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 372); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 128); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 132); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 136); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 376); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 380); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 384); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 124); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 388); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 392); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 396); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 400); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 404); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 408); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 412); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 416); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 420); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 424); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 428); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 432); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 436); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 440); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 444); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 448); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 452); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 456); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 460); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 464); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 468); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 472); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 476); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 480); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 484); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 488); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 492); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 496); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 500); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 504); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(30) + 25), R(0));
L_80B6E5FC:;
    R(0) = lr;
}

/* fn_4_536D0 (fn_4_536D0, 64 bytes) */
static void eb_m_70120(GM_CTX) {
    GM_FN(0x80B70120); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 2);
    R(31) = R(3) |R(3);
    GM_CALLV(0x80B7013Cu, 0x80B72710u, 0);
    R(4) = (0 + 0x80B90000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + -28752);
    st32(base, (R(31) + 4), R(4));
    R(0) = lr;
}

/* fn_4_53710 (fn_4_53710, 88 bytes) */
static void eb_m_70160(GM_CTX) {
    GM_FN(0x80B70160); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80B7019C; }
    R(4) = (0 + 0);
    GM_CALLV(0x80B7018Cu, 0x80B72890u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80B7019C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80B7019Cu, 0x802B9280u, 0);
L_80B7019C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_4_53770 (fn_4_53770, 1024 bytes) */
static void eb_m_701c0(GM_CTX) {
    GM_FN(0x80B701C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 128);
    R(5) = (0 + 0x80430000u);
    R(4) = (0 + 0x80430000u);
    R(30) = ld32(base, (R(5) + -24180));
    R(27) = R(3) |R(3);
    R(29) = ld32(base, (R(4) + -24708));
    R(4) = (R(27) + 60);
    R(0) = ld32(base, (R(30) + 13196));
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B70200u, 0x800F1040u, 0);
    R(0) = ld32(base, (R(30) + 13196));
    R(4) = (R(27) + 72);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B70218u, 0x800F1160u, 0);
    R(5) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(27) + 60); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    R(4) = (R(5) + 23608);
    { uint32_t ea_ = (R(27) + 64); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 68); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(5) + 23608); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(28) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(27) + 80); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 4);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[4].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 72); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(27) + 76); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 84); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(27) + 88); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(27) + 92); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(27) + 96); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(27) + 100); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(27) + 104); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 36); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(27) + 40); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(27) + 44); stfs(base, ea_, ctx->f[4].d); }
    R(5) = ld32(base, (R(3) + -24160));
    { uint32_t ea_ = (R(5) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[2].d); }
    st32(base, (R(28) + -28292), R(0));
    R(0) = ld32(base, (R(29) + 96));
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_80B70550; }
    R(3) = (0 + 0x10000u);
    R(4) = ld32(base, (R(30) + 13196));
    R(0) = (R(3) + 25880);
    R(31) = ld32(base, (R(5) + 556));
    R(0) = ((int32_t)R(4) * (int32_t)R(0));
    R(29) = (0 + 5);
    R(4) = R(31) |R(31);
    R(28) = (0 + 0);
    R(5) = (0 + 4);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x80B702D4u, 0x800F57A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B70324; }
    R(0) = ld32(base, (R(30) + 13196));
    R(4) = (0 + 0);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B702F4u, 0x800F10B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B7031C; }
    R(0) = ld32(base, (R(30) + 13196));
    R(4) = (0 + 1);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B70314u, 0x800F10B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B70324; }
L_80B7031C:;
    R(29) = (0 + 0);
    goto L_80B7041C;
L_80B70324:;
    R(3) = (0 + 0x10000u);
    R(5) = ld32(base, (R(30) + 13196));
    R(0) = (R(3) + 25880);
    R(4) = R(31) |R(31);
    R(0) = ((int32_t)R(5) * (int32_t)R(0));
    R(5) = (0 + 8);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x80B70348u, 0x800F57A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B70378; }
    R(0) = ld32(base, (R(30) + 13196));
    R(4) = (0 + 2);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B70368u, 0x800F10B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B70378; }
    R(29) = (0 + 2);
    goto L_80B7041C;
L_80B70378:;
    R(3) = (0 + 0x10000u);
    R(5) = ld32(base, (R(30) + 13196));
    R(0) = (R(3) + 25880);
    R(4) = R(31) |R(31);
    R(0) = ((int32_t)R(5) * (int32_t)R(0));
    R(5) = (0 + 16);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x80B7039Cu, 0x800F57A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B703CC; }
    R(0) = ld32(base, (R(30) + 13196));
    R(4) = (0 + 3);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B703BCu, 0x800F10B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B703CC; }
    R(29) = (0 + 3);
    goto L_80B7041C;
L_80B703CC:;
    R(3) = (0 + 0x10000u);
    R(5) = ld32(base, (R(30) + 13196));
    R(0) = (R(3) + 25880);
    R(4) = R(31) |R(31);
    R(0) = ((int32_t)R(5) * (int32_t)R(0));
    R(5) = (0 + 32);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x80B703F0u, 0x800F57A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B7041C; }
    R(0) = ld32(base, (R(30) + 13196));
    R(4) = (0 + 4);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B70410u, 0x800F10B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B7041C; }
    R(29) = (0 + 4);
L_80B7041C:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 5);
    if ((CR_BIT(ctx, 2))) { goto L_80B70470; }
    R(0) = ld32(base, (R(30) + 13196));
    R(4) = R(29) |R(29);
    R(5) = (f + 68);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B70440u, 0x800F10D0u, 0);
    { uint32_t ea_ = (f + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(27) + 36); stfs(base, ea_, ctx->f[0].d); }
    R(28) = (0 + 1);
    { uint32_t ea_ = (f + 72); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 44); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(27) + 4));
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x80B70470u, ctx->ctr, 0);
L_80B70470:;
    R(29) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(29) + -24160));
    GM_CALLV(0x80B7047Cu, 0x809079E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B704E4; }
    R(3) = (0 + 0x80B70000u);
    R(9) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(3) + 23576); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(7) = (0 + 0x80B90000u);
    R(5) = (0 + 0x80B90000u);
    R(8) = (R(9) + -7384);
    R(6) = (R(7) + -7372);
    R(3) = (0 + 0x80B90000u);
    R(4) = (R(5) + -7360);
    R(0) = (0 + 5);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(9) + -7384); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(8) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(8) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(7) + -7372); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + -7360); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(3) + -28292), R(0));
    goto L_80B70588;
L_80B704E4:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B70588; }
    R(3) = ld32(base, (R(29) + -24160));
    R(4) = R(31) |R(31);
    GM_CALLV(0x80B704F8u, 0x80907B40u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B7051C; }
    { uint32_t ea_ = (R(27) + 60); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 36); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(27) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(27) + 44); stfs(base, ea_, ctx->f[0].d); }
    goto L_80B70588;
L_80B7051C:;
    R(12) = ld32(base, (R(27) + 4));
    R(4) = R(27) |R(27);
    R(3) = (f + 56);
    R(12) = ld32(base, (R(12) + 120));
    ctx->ctr = R(12);
    GM_CALLV(0x80B70534u, ctx->ctr, 0);
    { uint32_t ea_ = (f + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 44); stfs(base, ea_, ctx->f[0].d); }
    goto L_80B70588;
L_80B70550:;
    R(12) = ld32(base, (R(27) + 4));
    R(4) = R(27) |R(27);
    R(3) = (f + 44);
    R(12) = ld32(base, (R(12) + 120));
    ctx->ctr = R(12);
    GM_CALLV(0x80B70568u, ctx->ctr, 0);
    { uint32_t ea_ = (f + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 6);
    { uint32_t ea_ = (R(27) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 52); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 44); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(28) + -28292), R(0));
L_80B70588:;
    R(4) = (0 + 0x80B70000u);
    R(3) = (R(27) + 124);
    R(4) = (R(4) + 23608);
    { uint32_t ea_ = (R(4) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 16); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 20); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x80B705A8u, 0x80B6D250u, 0);
    R(11) = (f + 128);
    R(0) = lr;
}

/* fn_4_53B70 (fn_4_53B70, 356 bytes) */
static void eb_m_705c0(GM_CTX) {
    GM_FN(0x80B705C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(0) = (0 + 0);
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(4) + -24160));
    { uint32_t ea_ = (R(3) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 180); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 40); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[4].d);
    { uint32_t ea_ = (R(3) + 36); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 176); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[4].d); }
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80B70634; }
    { uint32_t ea_ = (R(3) + 92); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80B70634; }
    R(0) = (0 + 1);
L_80B70634:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B70678; }
    { uint32_t ea_ = (f + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 192); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 60); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(4) + 188); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[2].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 184); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[3].d);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[4].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[0].d); }
L_80B70678:;
    R(12) = ld32(base, (R(31) + 4));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 128));
    ctx->ctr = R(12);
    GM_CALLV(0x80B7068Cu, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 4));
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 84));
    ctx->ctr = R(12);
    GM_CALLV(0x80B706A4u, ctx->ctr, 0);
    R(3) = (R(31) + 124);
    GM_CALLV(0x80B706ACu, 0x80B6D310u, 0);
    { uint32_t ea_ = (R(31) + 156); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(31) + 152); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(4) = (0 + 1);
    { uint32_t ea_ = (R(31) + 148); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[4].d);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[5].d);
    R(5) = ld8(base, (R(31) + 164));
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(31) + 36); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 44); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B706F8u, 0x80B72BA0u, 0);
    { uint32_t ea_ = (R(31) + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 20); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_4_53D90 (fn_4_53D90, 64 bytes) */
static void eb_m_707e0(GM_CTX) {
    { uint32_t ea_ = (R(5) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80B70808; }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
L_80B70808:;
    { uint32_t ea_ = (R(3) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 80); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) return;
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_4_53DD0 (fn_4_53DD0, 120 bytes) */
static void eb_m_70820(GM_CTX) {
    GM_FRAME(48); gptr f = gm_frame_sp;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24160));
    R(0) = ld32(base, (R(3) + 576));
    { uint32_t ea_ = (R(3) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    { uint32_t ea_ = (R(3) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_80B7085C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((CR_BIT(ctx, 2))) { goto L_80B70874; }
    goto L_80B7088C;
L_80B7085C:;
    R(3) = (0 + 0x80B90000u);
    R(0) = ld32(base, (R(3) + -28292));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((CR_BIT(ctx, 2))) { goto L_80B7088C; }
    R(3) = (0 + 4);
    goto L_80B70890;
L_80B70874:;
    R(3) = (0 + 0x80B90000u);
    R(0) = ld32(base, (R(3) + -28292));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    if ((CR_BIT(ctx, 2))) { goto L_80B7088C; }
    R(3) = (0 + 5);
    goto L_80B70890;
L_80B7088C:;
    R(3) = (0 + 6);
L_80B70890:;
}

/* fn_4_549C0 (fn_4_549C0, 132 bytes) */
static void eb_m_71410(GM_CTX) {
    GM_FN(0x80B71410); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80430000u);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(5) + -24160));
    R(5) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(5) + -24180));
    R(5) = ld32(base, (R(3) + 556));
    R(3) = (f + 8);
    GM_CALLV(0x80B71448u, 0x80100200u, 0);
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = R(31) |R(31);
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (f + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (f + 20);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(31) + 4));
    R(12) = ld32(base, (R(12) + 124));
    ctx->ctr = R(12);
    GM_CALLV(0x80B7147Cu, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_4_54A50 (fn_4_54A50, 120 bytes) */
static void eb_m_714a0(GM_CTX) {
    R(7) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(5) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(6) = (R(7) + -7384);
    { uint32_t ea_ = (R(7) + -7384); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 80); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80B714EC; }
    { uint32_t ea_ = (R(4) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80B714EC; }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[1].d); }
    return;
L_80B714EC:;
    { uint32_t ea_ = (R(5) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 80); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80B71504; }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    return;
L_80B71504:;
    { uint32_t ea_ = (R(4) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) return;
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_4_54AD0 (fn_4_54AD0, 664 bytes) */
static void eb_m_71520(GM_CTX) {
    GM_FN(0x80B71520); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80430000u);
    R(30) = (0 + 0);
    R(29) = R(3) |R(3);
    R(5) = ld32(base, (R(5) + -24160));
    { uint32_t ea_ = (R(3) + 92); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 180); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    { uint32_t ea_ = (R(5) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[1].d); }
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80B7158C; }
    { uint32_t ea_ = (R(3) + 104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80B7158C; }
    R(30) = (0 + 1);
L_80B7158C:;
    R(0) = ld32(base, (R(3) + 120));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B71794; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 4);
    if ((CR_BIT(ctx, 2))) { goto L_80B715AC; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 5);
    if ((CR_BIT(ctx, 2))) { goto L_80B716A4; }
    goto L_80B71794;
L_80B715AC:;
    R(4) = (0 + 0x80B70000u);
    { uint32_t ea_ = (f + 112); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (R(4) + 23608);
    { uint32_t ea_ = (R(3) + 68); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80B715D8; }
    goto L_80B715DC;
L_80B715D8:;
    ctx->f[2].u = ctx->f[0].u;
L_80B715DC:;
    { uint32_t ea_ = (R(3) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(31) + 23576); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 144); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 140); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[31].d - ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 132); stfs(base, ea_, ctx->f[31].d); }
    st8(base, (R(3) + 164), R(0));
    R(3) = (f + 20);
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x80B71638u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(31) + 23576); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(29) + 160); stfs(base, ea_, ctx->f[1].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    R(3) = (R(4) + -7372);
    { uint32_t ea_ = (R(29) + 136); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 140); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 144); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(4) + -7372); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[31].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_80B71694; }
    { uint32_t ea_ = (R(29) + 136); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 140); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 144); stfs(base, ea_, ctx->f[0].d); }
L_80B71694:;
    R(3) = (0 + 0x80B90000u);
    R(0) = (0 + 4);
    st32(base, (R(3) + -28292), R(0));
    goto L_80B71794;
L_80B716A4:;
    R(4) = (0 + 0x80B70000u);
    { uint32_t ea_ = (f + 112); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 23608); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 80); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80B716CC; }
    goto L_80B716D0;
L_80B716CC:;
    ctx->f[2].u = ctx->f[0].u;
L_80B716D0:;
    { uint32_t ea_ = (R(3) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(31) + 23576); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 144); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 140); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[31].d - ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 132); stfs(base, ea_, ctx->f[31].d); }
    st8(base, (R(3) + 164), R(0));
    R(3) = (f + 8);
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x80B7172Cu, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(31) + 23576); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(29) + 160); stfs(base, ea_, ctx->f[1].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    R(3) = (R(4) + -7372);
    { uint32_t ea_ = (R(29) + 136); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 140); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 144); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(4) + -7372); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[31].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_80B71788; }
    { uint32_t ea_ = (R(29) + 136); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 140); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 144); stfs(base, ea_, ctx->f[0].d); }
L_80B71788:;
    R(3) = (0 + 0x80B90000u);
    R(0) = (0 + 5);
    st32(base, (R(3) + -28292), R(0));
L_80B71794:;
    R(0) = lr;
}

/* fn_4_54D70 (fn_4_54D70, 796 bytes) */
static void eb_m_717c0(GM_CTX) {
    GM_FN(0x80B717C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 160);
    R(6) = (0 + 0x80430000u);
    R(29) = R(4) |R(4);
    R(31) = ld32(base, (R(6) + -24180));
    R(28) = R(3) |R(3);
    R(30) = R(5) |R(5);
    R(4) = (f + 104);
    R(0) = ld32(base, (R(31) + 13196));
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(31) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B71800u, 0x800F1040u, 0);
    R(0) = ld32(base, (R(31) + 13196));
    R(4) = (f + 92);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(31) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x80B71818u, 0x800F1160u, 0);
    { uint32_t ea_ = (f + 104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(26) = (0 + 0);
    { uint32_t ea_ = (R(28) + 0); stfs(base, ea_, ctx->f[0].d); }
    R(27) = (0 + 0);
    { uint32_t ea_ = (f + 108); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 112); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 8); stfs(base, ea_, ctx->f[0].d); }
    goto L_80B719B0;
L_80B7183C:;
    R(0) = ld32(base, (R(30) + 12));
    R(3) = R(31) |R(31);
    R(4) = R(0) + R(27);
    GM_CALLV(0x80B7184Cu, 0x801002C0u, 0);
    R(4) = (R(26) + 1);
    R(25) = R(3) |R(3);
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(5) = ld32(base, (R(30) + 12));
    R(0) = R(0) + R(4);
    R(3) = R(31) |R(31);
    R(4) = R(5) + R(0);
    GM_CALLV(0x80B7186Cu, 0x801002C0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(31) |R(31);
    R(5) = R(25) |R(25);
    R(3) = (f + 56);
    GM_CALLV(0x80B71880u, 0x80100200u, 0);
    { uint32_t ea_ = (f + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = R(31) |R(31);
    { uint32_t ea_ = (f + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = R(24) |R(24);
    { uint32_t ea_ = (f + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 44);
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B718A8u, 0x80100200u, 0);
    { uint32_t ea_ = (f + 52); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 88); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 48); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (R(28) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 44); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[4].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(28) + 8); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(29) + 8));
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[2].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_80B718F4; }
    { uint32_t ea_ = (f + 84); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(28) + 4); stfs(base, ea_, ctx->f[0].d); }
L_80B718F4:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = R(26) |R(26);
    R(6) = (0 + 128);
    GM_CALLV(0x80B71908u, 0x80B73820u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B71940; }
    { uint32_t ea_ = (f + 68); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 80); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 72); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 84); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (R(28) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(28) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(28) + 0); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(28) + 4); stfs(base, ea_, ctx->f[0].d); }
L_80B71940:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = R(26) |R(26);
    R(6) = (0 + 0x400000u);
    GM_CALLV(0x80B71954u, 0x80B73820u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B71974; }
    { uint32_t ea_ = (f + 72); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 84); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(28) + 4); stfs(base, ea_, ctx->f[0].d); }
L_80B71974:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = R(26) |R(26);
    R(6) = (0 + 0x80000000u);
    GM_CALLV(0x80B71988u, 0x80B73820u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B719A8; }
    { uint32_t ea_ = (f + 68); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 80); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(28) + 0); stfs(base, ea_, ctx->f[0].d); }
L_80B719A8:;
    R(27) = (R(27) + 5);
    R(26) = (R(26) + 1);
L_80B719B0:;
    R(3) = ld32(base, (R(30) + 16));
    R(3) = (R(3) + -1);
    cr_cmp_s(ctx, 0, (int32_t)R(26), (int32_t)R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80B7183C; }
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(30) + 12));
    R(0) = R(0) + R(3);
    R(3) = R(31) |R(31);
    R(4) = R(4) + R(0);
    GM_CALLV(0x80B719D8u, 0x801002C0u, 0);
    R(4) = (0 + 0x10000u);
    R(5) = ld32(base, (R(31) + 13196));
    R(0) = (R(4) + 25880);
    R(0) = ((int32_t)R(5) * (int32_t)R(0));
    R(4) = R(3) |R(3);
    R(5) = (0 + 16384);
    R(3) = R(31) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x80B719FCu, 0x800F57A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B71A94; }
    R(31) = (0 + 0x80B70000u);
    R(30) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(30) + 23576); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(31) + 23728); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (f + 8);
    { uint32_t ea_ = (R(29) + 360); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 356); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 352); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d - ctx->f[2].d);
    { uint32_t ea_ = (R(29) + 340); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(29) + 344); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(29) + 348); stfs(base, ea_, ctx->f[4].d); }
    st8(base, (R(29) + 380), R(0));
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x80B71A60u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(30) + 23576); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(29) |R(29);
    { uint32_t ea_ = (R(31) + 23728); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (0 + 2);
    { uint32_t ea_ = (R(29) + 376); stfs(base, ea_, ctx->f[1].d); }
    R(5) = (0 + 1);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(29) + 352); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 356); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 360); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x80B71A94u, 0x80B72B40u, 0);
L_80B71A94:;
    R(3) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(29) + 68); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(3) + 23608);
    { uint32_t ea_ = (R(28) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(28) + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 100); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80B71AC4; }
    { uint32_t ea_ = (R(28) + 8); stfs(base, ea_, ctx->f[0].d); }
L_80B71AC4:;
    R(11) = (f + 160);
    R(0) = lr;
}

/* fn_4_55090 (fn_4_55090, 160 bytes) */
static void eb_m_71ae0(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(4), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_80B71AF8; }
    R(5) = (0 + 0x80B90000u);
    R(0) = ld32(base, (R(5) + -28292));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((CR_BIT(ctx, 2))) { goto L_80B71B28; }
L_80B71AF8:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_80B71B10; }
    R(5) = (0 + 0x80B90000u);
    R(0) = ld32(base, (R(5) + -28292));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    if ((CR_BIT(ctx, 2))) { goto L_80B71B28; }
L_80B71B10:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 4);
    if ((CR_BIT(ctx, 2))) { goto L_80B71B28; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 5);
    if ((CR_BIT(ctx, 2))) { goto L_80B71B28; }
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_80B71B30; }
L_80B71B28:;
    R(3) = (0 + 1);
    return;
L_80B71B30:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_80B71B54; }
    { uint32_t ea_ = (R(3) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80B71B78; }
    R(3) = (0 + 1);
    return;
L_80B71B54:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_80B71B78; }
    { uint32_t ea_ = (R(3) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 80); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80B71B78; }
    R(3) = (0 + 1);
    return;
L_80B71B78:;
    R(3) = (0 + 0);
}

/* fn_4_554D0 (fn_4_554D0, 68 bytes) */
static void eb_m_71f20(GM_CTX) {
    GM_FN(0x80B71F20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x80B71F38u, 0x80B70120u, 0);
    R(3) = (0 + 0x80B90000u);
    R(0) = (0 + 4);
    R(3) = (R(3) + -29160);
    st32(base, (R(31) + 4), R(3));
    R(3) = R(31) |R(31);
    st32(base, (R(31) + 8), R(0));
    R(0) = lr;
}

/* fn_4_55520 (fn_4_55520, 88 bytes) */
static void eb_m_71f70(GM_CTX) {
    GM_FN(0x80B71F70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80B71FAC; }
    R(4) = (0 + 0);
    GM_CALLV(0x80B71F9Cu, 0x80B70160u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80B71FAC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80B71FACu, 0x802B9280u, 0);
L_80B71FAC:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_4_55580 (fn_4_55580, 536 bytes) */
static void eb_m_71fd0(GM_CTX) {
    GM_FN(0x80B71FD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = R(3) |R(3);
    GM_CALLV(0x80B71FF4u, 0x80B701C0u, 0);
    R(3) = (0 + 7);
    R(4) = (0 + 37);
    R(5) = (0 + -1);
    GM_CALLV(0x80B72004u, 0x800FAE80u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B720A8; }
    R(30) = (0 + 0x80B70000u);
    R(29) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(30) + 23608); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(29) + 23576); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 20);
    ctx->f[4].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(28) + 140); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[3].d - ctx->f[1].d);
    { uint32_t ea_ = (R(28) + 144); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = frsp(ctx->f[4].d);
    { uint32_t ea_ = (R(28) + 124); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(28) + 128); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d - ctx->f[2].d);
    { uint32_t ea_ = (R(28) + 132); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(28) + 164), R(0));
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x80B72070u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(30) + 23608); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(29) + 23576); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 5);
    ctx->f[3].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(28) + 160); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(28) + 136); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[0].d = frsp(ctx->f[3].d);
    { uint32_t ea_ = (R(28) + 140); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(28) + 144); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[3].d); }
    st32(base, (R(3) + -28292), R(0));
L_80B720A8:;
    R(29) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(29) + -24160));
    GM_CALLV(0x80B720B4u, 0x80906C30u, 0);
    GM_CALLV(0x80B720B8u, 0x800F9840u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_80B721A4; }
    R(30) = (0 + 0x80B70000u);
    R(31) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(30) + 23608); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(31) + 23576); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 8);
    ctx->f[4].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(28) + 140); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[3].d - ctx->f[1].d);
    { uint32_t ea_ = (R(28) + 144); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = frsp(ctx->f[4].d);
    { uint32_t ea_ = (R(28) + 124); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(28) + 128); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d - ctx->f[2].d);
    { uint32_t ea_ = (R(28) + 132); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(28) + 164), R(0));
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x80B72124u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(30) + 23608); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(31) + 23576); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = (0 + 5);
    ctx->f[4].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(28) + 160); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(28) + 136); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = frsp(ctx->f[4].d);
    { uint32_t ea_ = (R(28) + 140); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(28) + 144); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(3) + -28292), R(0));
    R(3) = ld32(base, (R(29) + -24160));
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[3].d); }
    R(0) = ld32(base, (R(3) + 556));
    st32(base, (R(3) + 560), R(0));
    { uint32_t ea_ = (R(28) + 144); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 140); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 136); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[5].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[6].d);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[7].d);
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (R(28) + 36); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(28) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(28) + 44); stfs(base, ea_, ctx->f[0].d); }
L_80B721A4:;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24160));
    { uint32_t ea_ = (R(3) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 40); stfs(base, ea_, ctx->f[1].d); }
    R(0) = lr;
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_4_557A0 (fn_4_557A0, 76 bytes) */
static void eb_m_721f0(GM_CTX) {
    GM_FN(0x80B721F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 32);
    R(5) = (0 + 0);
    R(31) = R(3) |R(3);
    GM_CALLV(0x80B72210u, 0x80B72BD0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80B72218u, 0x80B72A10u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 32);
    R(5) = (0 + 1);
    GM_CALLV(0x80B72228u, 0x80B72BD0u, 0);
    R(0) = lr;
}

/* fn_4_557F0 (fn_4_557F0, 148 bytes) */
static void eb_m_72240(GM_CTX) {
    GM_FN(0x80B72240); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80430000u);
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(31) + -24160));
    { uint32_t ea_ = (R(4) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B7227Cu, 0x80B705C0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x80B72284u, 0x80B72CF0u, 0);
    { uint32_t ea_ = (R(30) + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 40); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B72294u, 0x80100900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B722BC; }
    R(5) = ld32(base, (R(31) + -24160));
    R(3) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(3) + -24180));
    R(3) = (f + 32);
    R(5) = ld32(base, (R(5) + 556));
    GM_CALLV(0x80B722B4u, 0x80100200u, 0);
    { uint32_t ea_ = (f + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 40); stfs(base, ea_, ctx->f[0].d); }
L_80B722BC:;
    R(0) = lr;
}

/* fn_4_55890 (fn_4_55890, 116 bytes) */
static void eb_m_722e0(GM_CTX) {
    GM_FN(0x80B722E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(31) + 4));
    R(5) = (R(31) + 36);
    { uint32_t ea_ = (R(3) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 112));
    { uint32_t ea_ = (R(3) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 32);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    ctx->ctr = R(12);
    GM_CALLV(0x80B72328u, ctx->ctr, 0);
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 44); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_4_55910 (fn_4_55910, 144 bytes) */
static void eb_m_72360(GM_CTX) {
    GM_FN(0x80B72360); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    { uint32_t ea_ = (R(5) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (f + 8);
    GM_CALLV(0x80B7239Cu, 0x80B707E0u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80B723C4; }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[0].d); }
L_80B723C4:;
    { uint32_t ea_ = (R(30) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80B723D8; }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[0].d); }
L_80B723D8:;
    R(0) = lr;
}

/* fn_4_55C10 (fn_4_55C10, 132 bytes) */
static void eb_m_72660(GM_CTX) {
    GM_FN(0x80B72660); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80B70000u);
    R(6) = (0 + 0x80B90000u);
    R(5) = (R(5) + 23576);
    R(3) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(5) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -29200);
    { uint32_t ea_ = (R(5) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x80B70000u);
    R(0) = ld32(base, (R(3) + -12436));
    R(5) = (0 + 0x80B90000u);
    st32(base, (R(6) + 12), R(0));
    R(4) = (R(4) + 9968);
    R(5) = (R(5) + -7416);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B726C4u, 0x80B1CAC0u, 0);
    R(4) = (0 + 0x80430000u);
    R(3) = (0 + 0x80B90000u);
    R(0) = ld32(base, (R(4) + -12412));
    st32(base, (R(3) + -7404), R(0));
    R(0) = lr;
}

/* fn_4_55CC0 (fn_4_55CC0, 380 bytes) */
static void eb_m_72710(GM_CTX) {
    GM_FN(0x80B72710); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80B90000u);
    R(0) = (0 + 0);
    R(5) = (R(5) + -28288);
    R(29) = (0 + 0x80B70000u);
    R(29) = (R(29) + 23648);
    R(28) = R(3) |R(3);
    { uint32_t ea_ = (R(29) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (R(3) + 4), R(5));
    st32(base, (R(3) + 8), R(4));
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(3) + 112), R(0));
    st32(base, (R(3) + 116), R(0));
    st32(base, (R(3) + 120), R(0));
    R(3) = (R(3) + 124);
    GM_CALLV(0x80B72794u, 0x80B6D200u, 0);
    { uint32_t ea_ = (R(29) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(28) + 208);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 184); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 188); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 192); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 196); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 200); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 204); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B727D0u, 0x80B6D200u, 0);
    { uint32_t ea_ = (R(29) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(28) + 340);
    { uint32_t ea_ = (R(28) + 280); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 292); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B727F8u, 0x80B6D200u, 0);
    { uint32_t ea_ = (R(29) + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(30) = (0 + 0x80B20000u);
    R(31) = (0 + 0x80B20000u);
    { uint32_t ea_ = (R(28) + 400); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (R(28) + 444);
    R(4) = (R(30) + 5584);
    R(5) = (R(31) + -13472);
    R(6) = (0 + 12);
    R(7) = (0 + 8);
    GM_CALLV(0x80B72820u, 0x802DC9A0u, 0);
    R(3) = (R(28) + 540);
    R(4) = (R(30) + 5584);
    R(5) = (R(31) + -13472);
    R(6) = (0 + 12);
    R(7) = (0 + 8);
    GM_CALLV(0x80B72838u, 0x802DC9A0u, 0);
    { uint32_t ea_ = (R(29) + 52); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(28) + 340);
    { uint32_t ea_ = (R(29) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 60); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 44); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x80B72850u, 0x80B6D250u, 0);
    { uint32_t ea_ = (R(29) + 52); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(28) + 208);
    { uint32_t ea_ = (R(29) + 64); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 60); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 44); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x80B72868u, 0x80B6D250u, 0);
    R(3) = R(28) |R(28);
    R(0) = lr;
}

/* fn_4_55E40 (fn_4_55E40, 132 bytes) */
static void eb_m_72890(GM_CTX) {
    GM_FN(0x80B72890); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80B728F4; }
    R(31) = (0 + 0x80B20000u);
    R(5) = (0 + 12);
    R(4) = (R(31) + -13472);
    R(6) = (0 + 8);
    R(3) = (R(3) + 540);
    GM_CALLV(0x80B728D0u, 0x802DCA98u, 0);
    R(3) = (R(29) + 444);
    R(4) = (R(31) + -13472);
    R(5) = (0 + 12);
    R(6) = (0 + 8);
    GM_CALLV(0x80B728E4u, 0x802DCA98u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80B728F4; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x80B728F4u, 0x802B9280u, 0);
L_80B728F4:;
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* fn_4_55ED0 (fn_4_55ED0, 216 bytes) */
static void eb_m_72920(GM_CTX) {
    GM_FN(0x80B72920); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x80B72938u, 0x80B73760u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 32);
    R(5) = (0 + 1);
    GM_CALLV(0x80B72948u, 0x80B72BD0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 16);
    R(5) = (0 + 1);
    GM_CALLV(0x80B72958u, 0x80B72BD0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 1);
    R(5) = (0 + 1);
    GM_CALLV(0x80B72968u, 0x80B72BD0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 2);
    R(5) = (0 + 1);
    GM_CALLV(0x80B72978u, 0x80B72BD0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 4);
    R(5) = (0 + 1);
    GM_CALLV(0x80B72988u, 0x80B72BD0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 8);
    R(5) = (0 + 0);
    GM_CALLV(0x80B72998u, 0x80B72BD0u, 0);
    R(12) = ld32(base, (R(31) + 4));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 60));
    ctx->ctr = R(12);
    GM_CALLV(0x80B729ACu, ctx->ctr, 0);
    { uint32_t ea_ = (R(31) + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(31) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 48); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 56); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(31) + 4));
    R(12) = ld32(base, (R(12) + 64));
    ctx->ctr = R(12);
    GM_CALLV(0x80B729E4u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_4_55FC0 (fn_4_55FC0, 120 bytes) */
static void eb_m_72a10(GM_CTX) {
    GM_FN(0x80B72A10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 120));
    R(0) = R(0) & 0x10u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B72A74; }
    R(0) = ld32(base, (R(3) + 112));
    R(0) = R(0) & 0x40u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B72A74; }
    R(12) = ld32(base, (R(3) + 4));
    R(12) = ld32(base, (R(12) + 100));
    ctx->ctr = R(12);
    GM_CALLV(0x80B72A4Cu, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 4));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 68));
    ctx->ctr = R(12);
    GM_CALLV(0x80B72A60u, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 4));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 104));
    ctx->ctr = R(12);
    GM_CALLV(0x80B72A74u, ctx->ctr, 0);
L_80B72A74:;
    R(0) = lr;
}

/* fn_4_56050 (fn_4_56050, 28 bytes) */
static void eb_m_72aa0(GM_CTX) {
    { uint32_t ea_ = (R(3) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_4_56070 (fn_4_56070, 128 bytes) */
static void eb_m_72ac0(GM_CTX) {
    GM_FN(0x80B72AC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x80B72AD8u, 0x80B72C00u, 0);
    R(0) = ld32(base, (R(31) + 120));
    R(0) = R(0) & 0x2u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B72AEC; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80B72AECu, 0x80B73080u, 0);
L_80B72AEC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x80B72AF4u, 0x80B73270u, 0);
    R(0) = ld32(base, (R(31) + 120));
    R(0) = R(0) & 0x4u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B72B08; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80B72B08u, 0x80B731D0u, 0);
L_80B72B08:;
    R(12) = ld32(base, (R(31) + 4));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x80B72B1Cu, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80B72B24u, 0x80B732B0u, 0);
    R(0) = (0 + 0);
    st8(base, (R(31) + 108), R(0));
    R(0) = lr;
}

/* fn_4_560F0 (fn_4_560F0, 84 bytes) */
static void eb_m_72b40(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_80B72B6C; }
    R(0) = ld32(base, (R(3) + 112));
    R(6) = (0 + 0);
    st32(base, (R(3) + 336), R(6));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B72B6C; }
    cr_cmp_u(ctx, 0, R(5), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_80B72B6C; }
    R(0) = (0 + 1);
    st32(base, (R(3) + 336), R(0));
L_80B72B6C:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B72B84; }
    R(0) = ld32(base, (R(3) + 112));
    R(0) = R(0) |R(4);
    st32(base, (R(3) + 112), R(0));
    return;
L_80B72B84:;
    R(0) = ld32(base, (R(3) + 112));
    R(0) = R(0) & ~R(4);
    st32(base, (R(3) + 112), R(0));
}

/* fn_4_56150 (fn_4_56150, 40 bytes) */
static void eb_m_72ba0(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B72BB8; }
    R(0) = ld32(base, (R(3) + 116));
    R(0) = R(0) |R(4);
    st32(base, (R(3) + 116), R(0));
    return;
L_80B72BB8:;
    R(0) = ld32(base, (R(3) + 116));
    R(0) = R(0) & ~R(4);
    st32(base, (R(3) + 116), R(0));
}

/* fn_4_56180 (fn_4_56180, 40 bytes) */
static void eb_m_72bd0(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B72BE8; }
    R(0) = ld32(base, (R(3) + 120));
    R(0) = R(0) |R(4);
    st32(base, (R(3) + 120), R(0));
    return;
L_80B72BE8:;
    R(0) = ld32(base, (R(3) + 120));
    R(0) = R(0) & ~R(4);
    st32(base, (R(3) + 120), R(0));
}

/* fn_4_561B0 (fn_4_561B0, 148 bytes) */
static void eb_m_72c00(GM_CTX) {
    GM_FN(0x80B72C00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(5) = ld32(base, (R(3) + 112));
    R(0) = R(5) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B72C28; }
    R(0) = R(5) & 0x80u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B72C60; }
L_80B72C28:;
    R(4) = ld32(base, (R(3) + 336));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B72C40; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 336), R(0));
    goto L_80B72C60;
L_80B72C40:;
    R(12) = ld32(base, (R(31) + 4));
    R(0) = R(5) & 0x80u;
    R(0) = cntlzw(R(0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 72));
    R(4) = rotl32(R(0), 27) & 0x7FFFFFFu;
    ctx->ctr = R(12);
    GM_CALLV(0x80B72C60u, ctx->ctr, 0);
L_80B72C60:;
    R(0) = ld32(base, (R(31) + 112));
    R(0) = R(0) & 0x10u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B72C80; }
    R(12) = ld32(base, (R(31) + 4));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 76));
    ctx->ctr = R(12);
    GM_CALLV(0x80B72C80u, ctx->ctr, 0);
L_80B72C80:;
    R(0) = lr;
}

/* fn_4_562A0 (fn_4_562A0, 516 bytes) */
static void eb_m_72cf0(GM_CTX) {
    GM_FN(0x80B72CF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80430000u);
    R(30) = (0 + 0x80430000u);
    R(28) = R(3) |R(3);
    R(29) = ld32(base, (R(30) + -24160));
    R(3) = ld32(base, (R(31) + -24148));
    GM_CALLV(0x80B72D2Cu, 0x80915610u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B72D44; }
    R(3) = ld32(base, (R(31) + -24148));
    GM_CALLV(0x80B72D3Cu, 0x801015E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 68);
    if ((!CR_BIT(ctx, 2))) { goto L_80B72DD0; }
L_80B72D44:;
    R(0) = ld32(base, (R(29) + 560));
    R(5) = ld32(base, (R(29) + 556));
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B72D60; }
    R(3) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(3) + 23692); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_80B72ECC;
L_80B72D60:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 0))) { goto L_80B72D70; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_80B72D7C; }
L_80B72D70:;
    R(3) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(3) + 23692); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_80B72ECC;
L_80B72D7C:;
    R(31) = (0 + 0x80430000u);
    R(3) = (f + 20);
    R(4) = ld32(base, (R(31) + -24180));
    GM_CALLV(0x80B72D8Cu, 0x80100200u, 0);
    { uint32_t ea_ = (f + 20); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 8);
    { uint32_t ea_ = (f + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[2].d); }
    R(4) = ld32(base, (R(31) + -24180));
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[1].d); }
    R(5) = ld32(base, (R(29) + 560));
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B72DB4u, 0x80100200u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[0].d); }
    goto L_80B72E20;
L_80B72DD0:;
    R(3) = (0 + 0x80B70000u);
    R(4) = ld32(base, (R(30) + -24160));
    { uint32_t ea_ = (R(3) + 23696); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 400); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 612); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 616); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    { uint32_t ea_ = (R(4) + 620); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 508); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 512); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 516); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[1].d); }
    if ((CR_BIT(ctx, 2))) { goto L_80B72E20; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[5].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[0].d); }
L_80B72E20:;
    R(31) = (0 + 0x80B70000u);
    { uint32_t ea_ = (f + 100); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 23692); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 68);
    { uint32_t ea_ = (f + 92); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (f + 56);
    { uint32_t ea_ = (f + 88); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 80); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 180); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 192); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 184); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B72E84u, 0x801C1650u, 0);
    GM_CALLV(0x80B72E88u, 0x802BE470u, 0);
    ctx->f[31].u = ctx->f[1].u;
    R(3) = (f + 44);
    R(4) = (f + 32);
    GM_CALLV(0x80B72E98u, 0x801C1650u, 0);
    GM_CALLV(0x80B72E9Cu, 0x802BE470u, 0);
    { uint32_t ea_ = (R(31) + 23692); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[31].d);
    if ((!CR_BIT(ctx, 2))) { goto L_80B72EB8; }
    { uint32_t ea_ = (R(29) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 188); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    goto L_80B72ECC;
L_80B72EB8:;
    { uint32_t ea_ = (f + 84); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d / ctx->f[31].d);
L_80B72ECC:;
    R(0) = lr;
}

/* fn_4_564B0 (fn_4_564B0, 84 bytes) */
static void eb_m_72f00(GM_CTX) {
    R(6) = R(3) + R(4);
    R(0) = ld8(base, (R(6) + 636));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) return;
    R(4) = ((int32_t)R(4) * 12);
    { uint32_t ea_ = (R(5) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(5) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = R(3) + R(4);
    { uint32_t ea_ = (R(4) + 444); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 448); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + 452); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 540); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 544); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 548); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 636), R(0));
}

/* fn_4_56510 (fn_4_56510, 232 bytes) */
static void eb_m_72f60(GM_CTX) {
    GM_FN(0x80B72F60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(8) = R(5) |R(5);
    R(31) = R(3) + R(4);
    R(30) = R(3) |R(3);
    R(3) = R(4) |R(4);
    R(0) = ld8(base, (R(31) + 636));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B73030; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B72FA0; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 7);
    if ((!CR_BIT(ctx, 2))) { goto L_80B72FE8; }
L_80B72FA0:;
    R(0) = ((int32_t)R(4) * 12);
    R(12) = ld32(base, (R(30) + 4));
    R(5) = R(3) |R(3);
    R(12) = ld32(base, (R(12) + 80));
    R(4) = R(30) |R(30);
    R(7) = R(30) + R(0);
    R(6) = (R(7) + 540);
    R(3) = (f + 20);
    R(7) = (R(7) + 444);
    ctx->ctr = R(12);
    GM_CALLV(0x80B72FCCu, ctx->ctr, 0);
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 44); stfs(base, ea_, ctx->f[0].d); }
    goto L_80B73028;
L_80B72FE8:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_80B73028; }
    R(0) = ((int32_t)R(4) * 12);
    R(4) = R(30) |R(30);
    R(7) = R(8) |R(8);
    R(3) = (f + 8);
    R(6) = R(30) + R(0);
    R(5) = (R(6) + 540);
    R(6) = (R(6) + 444);
    GM_CALLV(0x80B73010u, 0x80B73050u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 44); stfs(base, ea_, ctx->f[0].d); }
L_80B73028:;
    R(0) = (0 + 0);
    st8(base, (R(31) + 636), R(0));
L_80B73030:;
    R(0) = lr;
}

/* fn_4_56600 (fn_4_56600, 44 bytes) */
static void eb_m_73050(GM_CTX) {
    { uint32_t ea_ = (R(7) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(4) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 36); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_4_56630 (fn_4_56630, 324 bytes) */
static void eb_m_73080(GM_CTX) {
    GM_FN(0x80B73080); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 112));
    R(0) = R(0) & 0x2u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B73104; }
    R(5) = (0 + 0x80B70000u);
    R(4) = (0 + 0x80B70000u);
    { uint32_t ea_ = (R(4) + 23692); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(5) + 23728); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 360); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 356); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 352); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d - ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 340); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 344); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 348); stfs(base, ea_, ctx->f[4].d); }
    st8(base, (R(3) + 380), R(0));
    R(3) = (f + 20);
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x80B730FCu, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(31) + 376); stfs(base, ea_, ctx->f[1].d); }
    goto L_80B7315C;
L_80B73104:;
    R(4) = (0 + 0x80B70000u);
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(4) + 23692); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 360); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 356); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 352); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 340); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 344); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 348); stfs(base, ea_, ctx->f[3].d); }
    st8(base, (R(3) + 380), R(0));
    R(3) = (f + 8);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x80B73158u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(31) + 376); stfs(base, ea_, ctx->f[1].d); }
L_80B7315C:;
    R(3) = (R(31) + 340);
    GM_CALLV(0x80B73164u, 0x80B6D310u, 0);
    R(5) = ld8(base, (R(31) + 380));
    R(3) = R(31) |R(31);
    R(4) = (0 + 2);
    GM_CALLV(0x80B73174u, 0x80B72BA0u, 0);
    { uint32_t ea_ = (R(31) + 360); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 356); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 352); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[4].d);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[5].d);
    { uint32_t ea_ = (R(31) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 20); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[5].d); }
}

/* fn_4_56780 (fn_4_56780, 156 bytes) */
static void eb_m_731d0(GM_CTX) {
    GM_FN(0x80B731D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 4);
    R(31) = R(3) |R(3);
    R(5) = ld8(base, (R(3) + 248));
    GM_CALLV(0x80B731F0u, 0x80B72BA0u, 0);
    R(3) = (R(31) + 208);
    GM_CALLV(0x80B731F8u, 0x80B6D310u, 0);
    { uint32_t ea_ = (R(31) + 240); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 236); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 232); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 204); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 200); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[5].d + ctx->f[2].d);
    { uint32_t ea_ = (R(31) + 196); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[4].d + ctx->f[1].d);
    { uint32_t ea_ = (R(31) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[3].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[7].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[8].d);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[6].d);
    { uint32_t ea_ = (R(31) + 36); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 44); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[6].d); }
}

/* fn_4_56820 (fn_4_56820, 52 bytes) */
static void eb_m_73270(GM_CTX) {
    R(0) = ld32(base, (R(3) + 112));
    R(0) = R(0) & 0x4u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B73284; }
    { uint32_t ea_ = (R(3) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
L_80B73284:;
    R(0) = ld32(base, (R(3) + 112));
    R(0) = R(0) & 0x8u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) return;
    { uint32_t ea_ = (R(3) + 32); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_4_56860 (fn_4_56860, 180 bytes) */
static void eb_m_732b0(GM_CTX) {
    GM_FRAME(48); gptr f = gm_frame_sp;
    R(0) = ld32(base, (R(3) + 120));
    R(0) = R(0) & 0x20u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B73344; }
    R(5) = (0 + 0x80B70000u);
    R(4) = (0 + 0x80B70000u);
    R(5) = (R(5) + 23728);
    { uint32_t ea_ = (R(4) + 23708); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 36); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[1].d - ctx->f[4].d);
    { uint32_t ea_ = (R(3) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[0].d * ctx->f[4].d);
    { uint32_t ea_ = (R(3) + 52); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 48); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[1].d * ctx->f[5].d);
    { uint32_t ea_ = (R(3) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d * ctx->f[5].d);
    { uint32_t ea_ = (R(3) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[5].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[4].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[4].d);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[6].d + ctx->f[7].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[3].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[4].d); }
L_80B73344:;
    { uint32_t ea_ = (R(3) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_4_56920 (fn_4_56920, 124 bytes) */
static void eb_m_73370(GM_CTX) {
    GM_FN(0x80B73370); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    GM_CALLV(0x80B73390u, 0x80B73760u, 0);
    R(12) = ld32(base, (R(30) + 4));
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    R(3) = (f + 8);
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x80B733ACu, ctx->ctr, 0);
    R(5) = (0 + 0x80B90000u);
    { uint32_t ea_ = (f + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (R(5) + -7384);
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (R(5) + -7384); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + 8); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B733D4u, 0x80B72A10u, 0);
    R(0) = lr;
}

/* fn_4_56A30 (fn_4_56A30, 108 bytes) */
static void eb_m_73480(GM_CTX) {
    R(0) = (R(4) + 0xE0000000u);
    cr_cmp_u(ctx, 0, R(0), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_80B734BC; }
    R(0) = (R(4) + 0xC0000000u);
    cr_cmp_u(ctx, 0, R(0), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_80B734C4; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 128);
    if ((CR_BIT(ctx, 2))) { goto L_80B734CC; }
    R(0) = (R(4) + 0xFFC00000u);
    cr_cmp_u(ctx, 0, R(0), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_80B734D4; }
    R(0) = (R(4) + 0x80000000u);
    cr_cmp_u(ctx, 0, R(0), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_80B734DC; }
    goto L_80B734E4;
L_80B734BC:;
    R(3) = (0 + 64);
    return;
L_80B734C4:;
    R(3) = (0 + 32);
    return;
L_80B734CC:;
    R(3) = (0 + 1);
    return;
L_80B734D4:;
    R(3) = (0 + 16);
    return;
L_80B734DC:;
    R(3) = (0 + 128);
    return;
L_80B734E4:;
    R(3) = (0 + 256);
}

/* fn_4_56AA0 (fn_4_56AA0, 232 bytes) */
static void eb_m_734f0(GM_CTX) {
    GM_FN(0x80B734F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x80B73500u, 0x80B73480u, 0);
    R(0) = (0 + 0);
    R(4) = (0 + 1);
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B7351C; }
    R(3) = (0 + 0);
    goto L_80B735C8;
L_80B7351C:;
    R(0) = (0 + 1);
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B73534; }
    R(3) = (0 + 1);
    goto L_80B735C8;
L_80B73534:;
    R(0) = (0 + 2);
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B7354C; }
    R(3) = (0 + 2);
    goto L_80B735C8;
L_80B7354C:;
    R(0) = (0 + 3);
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B73564; }
    R(3) = (0 + 3);
    goto L_80B735C8;
L_80B73564:;
    R(0) = (0 + 4);
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B7357C; }
    R(3) = (0 + 4);
    goto L_80B735C8;
L_80B7357C:;
    R(0) = (0 + 5);
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B73594; }
    R(3) = (0 + 5);
    goto L_80B735C8;
L_80B73594:;
    R(0) = (0 + 6);
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B735AC; }
    R(3) = (0 + 6);
    goto L_80B735C8;
L_80B735AC:;
    R(0) = (0 + 7);
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80B735C4; }
    R(3) = (0 + 7);
    goto L_80B735C8;
L_80B735C4:;
    R(3) = (0 + 8);
L_80B735C8:;
    R(0) = lr;
}

/* fn_4_56B90 (fn_4_56B90, 16 bytes) */
static void eb_m_735e0(GM_CTX) {
    R(12) = ld32(base, (R(3) + 4));
    R(12) = ld32(base, (R(12) + 88));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_4_56D10 (fn_4_56D10, 188 bytes) */
static void eb_m_73760(GM_CTX) {
    R(5) = (0 + 0x80370000u);
    R(0) = (0 + 4);
    R(11) = (0 + 0);
    R(8) = R(3) |R(3);
    R(9) = R(3) |R(3);
    R(4) = (R(5) + 32200);
    R(7) = (0 + -1);
    R(6) = (0 + 0);
    ctx->ctr = R(0);
L_80B73784:;
    st32(base, (R(8) + 404), R(7));
    R(10) = R(3) + R(11);
    R(11) = (R(11) + 1);
    st8(base, (R(10) + 436), R(6));
    { uint32_t ea_ = (R(5) + 32200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 444); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 448); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 452); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 32200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 540); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 544); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 548); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(10) + 636), R(6));
    R(10) = R(3) + R(11);
    R(11) = (R(11) + 1);
    st32(base, (R(8) + 408), R(7));
    R(8) = (R(8) + 8);
    st8(base, (R(10) + 436), R(6));
    { uint32_t ea_ = (R(5) + 32200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 456); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 460); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 464); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 32200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 552); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 556); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(9) + 560); stfs(base, ea_, ctx->f[0].d); }
    R(9) = (R(9) + 24);
    st8(base, (R(10) + 636), R(6));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80B73784; }
}

/* fn_4_56DD0 (fn_4_56DD0, 352 bytes) */
static void eb_m_73820(GM_CTX) {
    GM_FN(0x80B73820); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(7) = (0 + 0x80430000u);
    R(27) = R(6) |R(6);
    R(29) = ld32(base, (R(7) + -24180));
    R(26) = R(4) |R(4);
    R(25) = R(3) |R(3);
    R(28) = R(5) |R(5);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80B73854u, 0x80B73480u, 0);
    R(3) = R(25) |R(25);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80B73860u, 0x80B734F0u, 0);
    R(0) = rotl32(R(28), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(26) + 12));
    R(0) = R(0) + R(28);
    R(31) = R(3) |R(3);
    R(3) = R(29) |R(29);
    R(4) = R(4) + R(0);
    GM_CALLV(0x80B7387Cu, 0x801002C0u, 0);
    R(0) = rotl32(R(31), 2) & 0xFFFFFFFCu;
    R(30) = R(25) + R(0);
    R(0) = ld32(base, (R(30) + 404));
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80B7389C; }
    R(4) = R(25) + R(31);
    R(0) = (0 + 0);
    st8(base, (R(4) + 436), R(0));
L_80B7389C:;
    R(31) = R(25) + R(31);
    R(0) = ld8(base, (R(31) + 436));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80B73964; }
    R(4) = (0 + 0x10000u);
    R(5) = ld32(base, (R(29) + 13196));
    R(0) = (R(4) + 25880);
    R(0) = ((int32_t)R(5) * (int32_t)R(0));
    R(4) = R(3) |R(3);
    R(5) = R(27) |R(27);
    R(3) = R(29) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x80B738D0u, 0x800F57A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B73964; }
    R(28) = (R(28) + 1);
    R(0) = rotl32(R(28), 2) & 0xFFFFFFFCu;
    R(25) = R(0) + R(28);
    goto L_80B73958;
L_80B738E8:;
    R(0) = ld32(base, (R(26) + 12));
    R(3) = R(0) + R(25);
    GM_CALLV(0x80B738F4u, 0x800F9970u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_80B73950; }
    R(0) = rotl32(R(28), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(26) + 12));
    R(0) = R(0) + R(28);
    R(3) = R(29) |R(29);
    R(4) = R(4) + R(0);
    GM_CALLV(0x80B73914u, 0x801002C0u, 0);
    R(4) = (0 + 0x10000u);
    R(5) = ld32(base, (R(29) + 13196));
    R(0) = (R(4) + 25880);
    R(0) = ((int32_t)R(5) * (int32_t)R(0));
    R(4) = R(3) |R(3);
    R(5) = R(27) |R(27);
    R(3) = R(29) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x80B73938u, 0x800F57A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80B73964; }
    R(0) = (0 + 1);
    st8(base, (R(31) + 436), R(0));
    st32(base, (R(30) + 404), R(28));
    goto L_80B73964;
L_80B73950:;
    R(25) = (R(25) + 5);
    R(28) = (R(28) + 1);
L_80B73958:;
    R(0) = ld32(base, (R(26) + 16));
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80B738E8; }
L_80B73964:;
    R(11) = (f + 48);
    R(3) = ld8(base, (R(31) + 436));
    R(0) = lr;
}

/* fn_4_56F40 (fn_4_56F40, 200 bytes) */
static void eb_m_73990(GM_CTX) {
    GM_FN(0x80B73990); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80B90000u);
    R(4) = (0 + 0x80B70000u);
    R(3) = (0 + 0x80430000u);
    R(0) = ld32(base, (R(3) + -12436));
    R(6) = (R(6) + -28328);
    R(31) = (0 + 0x80B70000u);
    R(31) = (R(31) + 23648);
    R(4) = (R(4) + 14944);
    R(30) = (0 + 0x80B90000u);
    { uint32_t ea_ = (R(31) + 124); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(30) = (R(30) + -7400);
    { uint32_t ea_ = (R(31) + 128); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (R(30) + 0);
    { uint32_t ea_ = (R(31) + 132); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0);
    st32(base, (R(6) + 12), R(0));
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80B73A00u, 0x80B1CAC0u, 0);
    { uint32_t ea_ = (R(31) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (R(30) + 16);
    R(4) = (R(30) + 28);
    R(3) = (R(30) + 40);
    R(6) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(30) + 16); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(6) + -12412));
    { uint32_t ea_ = (R(5) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(30) + 12), R(0));
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_EB_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_EB_COUNT)
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_4_110, 4) { eb_m_1cb60(GM_PASS); }
E(fn_4_2E10, 4) { eb_m_1f860(GM_PASS); }
E(fn_4_2E60, 4) { eb_m_1f8b0(GM_PASS); }
E(fn_4_3100, 4) { eb_m_1fb50(GM_PASS); }
E(fn_4_3200, 4) { eb_m_1fc50(GM_PASS); }
E(fn_4_3280, 4) { eb_m_1fcd0(GM_PASS); }
E(fn_4_32A0, 4) { eb_m_1fcf0(GM_PASS); }
E(fn_4_3370, 4) { eb_m_1fdc0(GM_PASS); }
E(fn_4_3380, 4) { eb_m_1fdd0(GM_PASS); }
E(fn_4_33A0, 4) { eb_m_1fdf0(GM_PASS); }
E(fn_4_3640, 4) { eb_m_20090(GM_PASS); }
E(fn_4_36A0, 4) { eb_m_200f0(GM_PASS); }
E(fn_4_3730, 4) { eb_m_20180(GM_PASS); }
E(fn_4_3740, 4) { eb_m_20190(GM_PASS); }
E(fn_4_3790, 4) { eb_m_201e0(GM_PASS); }
E(fn_4_46A0, 4) { eb_m_210f0(GM_PASS); }
E(fn_4_46B0, 4) { eb_m_21100(GM_PASS); }
E(fn_4_46C0, 4) { eb_m_21110(GM_PASS); }
E(fn_4_46D0, 4) { eb_m_21120(GM_PASS); }
E(fn_4_46E0, 4) { eb_m_21130(GM_PASS); }
E(fn_4_46F0, 4) { eb_m_21140(GM_PASS); }
E(fn_4_4700, 4) { eb_m_21150(GM_PASS); }
E(fn_4_4710, 4) { eb_m_21160(GM_PASS); }
E(fn_4_4720, 4) { eb_m_21170(GM_PASS); }
E(fn_4_4730, 4) { eb_m_21180(GM_PASS); }
E(fn_4_4740, 4) { eb_m_21190(GM_PASS); }
E(fn_4_4750, 4) { eb_m_211a0(GM_PASS); }
E(fn_4_4B20, 4) { eb_m_21570(GM_PASS); }
E(fn_4_4B80, 4) { eb_m_215d0(GM_PASS); }
E(fn_4_5DD0, 4) { eb_m_22820(GM_PASS); }
E(fn_4_5E40, 4) { eb_m_22890(GM_PASS); }
E(fn_4_5E90, 4) { eb_m_228e0(GM_PASS); }
E(fn_4_5EA0, 4) { eb_m_228f0(GM_PASS); }
E(fn_4_5EB0, 4) { eb_m_22900(GM_PASS); }
E(fn_4_5F80, 4) { eb_m_229d0(GM_PASS); }
E(fn_4_6730, 4) { eb_m_23180(GM_PASS); }
E(fn_4_6740, 4) { eb_m_23190(GM_PASS); }
E(fn_4_6750, 4) { eb_m_231a0(GM_PASS); }
E(fn_4_6760, 4) { eb_m_231b0(GM_PASS); }
E(fn_4_6770, 4) { eb_m_231c0(GM_PASS); }
E(fn_4_6780, 4) { eb_m_231d0(GM_PASS); }
E(fn_4_6790, 4) { eb_m_231e0(GM_PASS); }
E(fn_4_67A0, 4) { eb_m_231f0(GM_PASS); }
E(fn_4_90E0, 4) { eb_m_25b30(GM_PASS); }
E(fn_4_9330, 4) { eb_m_25d80(GM_PASS); }
E(fn_4_9C90, 4) { eb_m_266e0(GM_PASS); }
E(fn_4_9CA0, 4) { eb_m_266f0(GM_PASS); }
E(fn_4_9CB0, 4) { eb_m_26700(GM_PASS); }
E(fn_4_9CC0, 4) { eb_m_26710(GM_PASS); }
E(fn_4_9CD0, 4) { eb_m_26720(GM_PASS); }
E(fn_4_9CE0, 4) { eb_m_26730(GM_PASS); }
E(fn_4_9CF0, 4) { eb_m_26740(GM_PASS); }
E(fn_4_D290, 4) { eb_m_29ce0(GM_PASS); }
E(fn_4_DEF0, 4) { eb_m_2a940(GM_PASS); }
E(fn_4_DF00, 4) { eb_m_2a950(GM_PASS); }
E(fn_4_DF10, 4) { eb_m_2a960(GM_PASS); }
E(fn_4_DF20, 4) { eb_m_2a970(GM_PASS); }
E(fn_4_DF30, 4) { eb_m_2a980(GM_PASS); }
E(fn_4_DF40, 4) { eb_m_2a990(GM_PASS); }
E(fn_4_DF50, 4) { eb_m_2a9a0(GM_PASS); }
E(fn_4_DF60, 4) { eb_m_2a9b0(GM_PASS); }
E(fn_4_DF70, 4) { eb_m_2a9c0(GM_PASS); }
E(fn_4_10AE0, 4) { eb_m_2d530(GM_PASS); }
E(fn_4_11800, 4) { eb_m_2e250(GM_PASS); }
E(fn_4_11810, 4) { eb_m_2e260(GM_PASS); }
E(fn_4_11820, 4) { eb_m_2e270(GM_PASS); }
E(fn_4_11830, 4) { eb_m_2e280(GM_PASS); }
E(fn_4_11840, 4) { eb_m_2e290(GM_PASS); }
E(fn_4_11850, 4) { eb_m_2e2a0(GM_PASS); }
E(fn_4_11860, 4) { eb_m_2e2b0(GM_PASS); }
E(fn_4_11870, 4) { eb_m_2e2c0(GM_PASS); }
E(fn_4_11880, 4) { eb_m_2e2d0(GM_PASS); }
E(fn_4_11890, 4) { eb_m_2e2e0(GM_PASS); }
E(fn_4_11D00, 4) { eb_m_2e750(GM_PASS); }
E(fn_4_11D10, 4) { eb_m_2e760(GM_PASS); }
E(fn_4_11D20, 4) { eb_m_2e770(GM_PASS); }
E(fn_4_11D30, 4) { eb_m_2e780(GM_PASS); }
E(fn_4_11D40, 4) { eb_m_2e790(GM_PASS); }
E(fn_4_11D50, 4) { eb_m_2e7a0(GM_PASS); }
E(fn_4_11D60, 4) { eb_m_2e7b0(GM_PASS); }
E(fn_4_11D70, 4) { eb_m_2e7c0(GM_PASS); }
E(fn_4_145C0, 4) { eb_m_31010(GM_PASS); }
E(fn_4_15790, 4) { eb_m_321e0(GM_PASS); }
E(fn_4_157A0, 4) { eb_m_321f0(GM_PASS); }
E(fn_4_157B0, 4) { eb_m_32200(GM_PASS); }
E(fn_4_157C0, 4) { eb_m_32210(GM_PASS); }
E(fn_4_157D0, 4) { eb_m_32220(GM_PASS); }
E(fn_4_157E0, 4) { eb_m_32230(GM_PASS); }
E(fn_4_157F0, 4) { eb_m_32240(GM_PASS); }
E(fn_4_15800, 4) { eb_m_32250(GM_PASS); }
E(fn_4_15810, 4) { eb_m_32260(GM_PASS); }
E(fn_4_15820, 4) { eb_m_32270(GM_PASS); }
E(fn_4_15830, 4) { eb_m_32280(GM_PASS); }
E(fn_4_15840, 4) { eb_m_32290(GM_PASS); }
E(fn_4_17970, 4) { eb_m_343c0(GM_PASS); }
E(fn_4_18140, 4) { eb_m_34b90(GM_PASS); }
E(fn_4_18150, 4) { eb_m_34ba0(GM_PASS); }
E(fn_4_18160, 4) { eb_m_34bb0(GM_PASS); }
E(fn_4_18170, 4) { eb_m_34bc0(GM_PASS); }
E(fn_4_18180, 4) { eb_m_34bd0(GM_PASS); }
E(fn_4_18190, 4) { eb_m_34be0(GM_PASS); }
E(fn_4_181A0, 4) { eb_m_34bf0(GM_PASS); }
E(fn_4_181B0, 4) { eb_m_34c00(GM_PASS); }
E(fn_4_18500, 4) { eb_m_34f50(GM_PASS); }
E(fn_4_18510, 4) { eb_m_34f60(GM_PASS); }
E(fn_4_18520, 4) { eb_m_34f70(GM_PASS); }
E(fn_4_18530, 4) { eb_m_34f80(GM_PASS); }
E(fn_4_18540, 4) { eb_m_34f90(GM_PASS); }
E(fn_4_1B1B0, 4) { eb_m_37c00(GM_PASS); }
E(fn_4_1C1F0, 4) { eb_m_38c40(GM_PASS); }
E(fn_4_1C200, 4) { eb_m_38c50(GM_PASS); }
E(fn_4_1C210, 4) { eb_m_38c60(GM_PASS); }
E(fn_4_1C220, 4) { eb_m_38c70(GM_PASS); }
E(fn_4_1C230, 4) { eb_m_38c80(GM_PASS); }
E(fn_4_1C240, 4) { eb_m_38c90(GM_PASS); }
E(fn_4_1C250, 4) { eb_m_38ca0(GM_PASS); }
E(fn_4_1C260, 4) { eb_m_38cb0(GM_PASS); }
E(fn_4_1C270, 4) { eb_m_38cc0(GM_PASS); }
E(fn_4_1C280, 4) { eb_m_38cd0(GM_PASS); }
E(fn_4_1C290, 4) { eb_m_38ce0(GM_PASS); }
E(fn_4_1C2A0, 4) { eb_m_38cf0(GM_PASS); }
E(fn_4_1C2B0, 4) { eb_m_38d00(GM_PASS); }
E(fn_4_1C5D0, 4) { eb_m_39020(GM_PASS); }
E(fn_4_1C5E0, 4) { eb_m_39030(GM_PASS); }
E(fn_4_1C5F0, 4) { eb_m_39040(GM_PASS); }
E(fn_4_1C600, 4) { eb_m_39050(GM_PASS); }
E(fn_4_1C610, 4) { eb_m_39060(GM_PASS); }
E(fn_4_1C620, 4) { eb_m_39070(GM_PASS); }
E(fn_4_1C630, 4) { eb_m_39080(GM_PASS); }
E(fn_4_1C640, 4) { eb_m_39090(GM_PASS); }
E(fn_4_1FA40, 4) { eb_m_3c490(GM_PASS); }
E(fn_4_210F0, 4) { eb_m_3db40(GM_PASS); }
E(fn_4_21100, 4) { eb_m_3db50(GM_PASS); }
E(fn_4_21110, 4) { eb_m_3db60(GM_PASS); }
E(fn_4_21120, 4) { eb_m_3db70(GM_PASS); }
E(fn_4_21130, 4) { eb_m_3db80(GM_PASS); }
E(fn_4_21140, 4) { eb_m_3db90(GM_PASS); }
E(fn_4_21150, 4) { eb_m_3dba0(GM_PASS); }
E(fn_4_21160, 4) { eb_m_3dbb0(GM_PASS); }
E(fn_4_21170, 4) { eb_m_3dbc0(GM_PASS); }
E(fn_4_21180, 4) { eb_m_3dbd0(GM_PASS); }
E(fn_4_21190, 4) { eb_m_3dbe0(GM_PASS); }
E(fn_4_211A0, 4) { eb_m_3dbf0(GM_PASS); }
E(fn_4_211B0, 4) { eb_m_3dc00(GM_PASS); }
E(fn_4_211C0, 4) { eb_m_3dc10(GM_PASS); }
E(fn_4_211D0, 4) { eb_m_3dc20(GM_PASS); }
E(fn_4_211E0, 4) { eb_m_3dc30(GM_PASS); }
E(fn_4_217E0, 4) { eb_m_3e230(GM_PASS); }
E(fn_4_217F0, 4) { eb_m_3e240(GM_PASS); }
E(fn_4_21800, 4) { eb_m_3e250(GM_PASS); }
E(fn_4_21810, 4) { eb_m_3e260(GM_PASS); }
E(fn_4_21820, 4) { eb_m_3e270(GM_PASS); }
E(fn_4_21830, 4) { eb_m_3e280(GM_PASS); }
E(fn_4_21840, 4) { eb_m_3e290(GM_PASS); }
E(fn_4_21850, 4) { eb_m_3e2a0(GM_PASS); }
E(fn_4_21860, 4) { eb_m_3e2b0(GM_PASS); }
E(fn_4_21870, 4) { eb_m_3e2c0(GM_PASS); }
E(fn_4_21880, 4) { eb_m_3e2d0(GM_PASS); }
E(fn_4_21890, 4) { eb_m_3e2e0(GM_PASS); }
E(fn_4_218A0, 4) { eb_m_3e2f0(GM_PASS); }
E(fn_4_218B0, 4) { eb_m_3e300(GM_PASS); }
E(fn_4_218C0, 4) { eb_m_3e310(GM_PASS); }
E(fn_4_218D0, 4) { eb_m_3e320(GM_PASS); }
E(fn_4_28160, 4) { eb_m_44bb0(GM_PASS); }
E(fn_4_291E0, 4) { eb_m_45c30(GM_PASS); }
E(fn_4_29560, 4) { eb_m_45fb0(GM_PASS); }
E(fn_4_29570, 4) { eb_m_45fc0(GM_PASS); }
E(fn_4_29580, 4) { eb_m_45fd0(GM_PASS); }
E(fn_4_29BD0, 4) { eb_m_46620(GM_PASS); }
E(fn_4_2A3B0, 4) { eb_m_46e00(GM_PASS); }
E(fn_4_2A3C0, 4) { eb_m_46e10(GM_PASS); }
E(fn_4_2A3D0, 4) { eb_m_46e20(GM_PASS); }
E(fn_4_2A3E0, 4) { eb_m_46e30(GM_PASS); }
E(fn_4_2BA80, 4) { eb_m_484d0(GM_PASS); }
E(fn_4_2C340, 4) { eb_m_48d90(GM_PASS); }
E(fn_4_2C350, 4) { eb_m_48da0(GM_PASS); }
E(fn_4_2C360, 4) { eb_m_48db0(GM_PASS); }
E(fn_4_2C370, 4) { eb_m_48dc0(GM_PASS); }
E(fn_4_2C380, 4) { eb_m_48dd0(GM_PASS); }
E(fn_4_2C390, 4) { eb_m_48de0(GM_PASS); }
E(fn_4_2DA80, 4) { eb_m_4a4d0(GM_PASS); }
E(fn_4_2F890, 4) { eb_m_4c2e0(GM_PASS); }
E(fn_4_2FCC0, 4) { eb_m_4c710(GM_PASS); }
E(fn_4_2FCD0, 4) { eb_m_4c720(GM_PASS); }
E(fn_4_31840, 4) { eb_m_4e290(GM_PASS); }
E(fn_4_31F60, 4) { eb_m_4e9b0(GM_PASS); }
E(fn_4_31F70, 4) { eb_m_4e9c0(GM_PASS); }
E(fn_4_343C0, 4) { eb_m_50e10(GM_PASS); }
E(fn_4_348C0, 4) { eb_m_51310(GM_PASS); }
E(fn_4_348D0, 4) { eb_m_51320(GM_PASS); }
E(fn_4_348E0, 4) { eb_m_51330(GM_PASS); }
E(fn_4_348F0, 4) { eb_m_51340(GM_PASS); }
E(fn_4_34BE0, 4) { eb_m_51630(GM_PASS); }
E(fn_4_34C40, 4) { eb_m_51690(GM_PASS); }
E(fn_4_34C50, 4) { eb_m_516a0(GM_PASS); }
E(fn_4_34C60, 4) { eb_m_516b0(GM_PASS); }
E(fn_4_34C70, 4) { eb_m_516c0(GM_PASS); }
E(fn_4_34C80, 4) { eb_m_516d0(GM_PASS); }
E(fn_4_34C90, 4) { eb_m_516e0(GM_PASS); }
E(fn_4_34CA0, 4) { eb_m_516f0(GM_PASS); }
E(fn_4_34E20, 4) { eb_m_51870(GM_PASS); }
E(fn_4_34FF0, 4) { eb_m_51a40(GM_PASS); }
E(fn_4_35040, 4) { eb_m_51a90(GM_PASS); }
E(fn_4_35050, 4) { eb_m_51aa0(GM_PASS); }
E(fn_4_35060, 4) { eb_m_51ab0(GM_PASS); }
E(fn_4_352E0, 4) { eb_m_51d30(GM_PASS); }
E(fn_4_35300, 4) { eb_m_51d50(GM_PASS); }
E(fn_4_35360, 4) { eb_m_51db0(GM_PASS); }
E(fn_4_35400, 4) { eb_m_51e50(GM_PASS); }
E(fn_4_35480, 4) { eb_m_51ed0(GM_PASS); }
E(fn_4_354F0, 4) { eb_m_51f40(GM_PASS); }
E(fn_4_35540, 4) { eb_m_51f90(GM_PASS); }
E(fn_4_35550, 4) { eb_m_51fa0(GM_PASS); }
E(fn_4_35680, 4) { eb_m_520d0(GM_PASS); }
E(fn_4_356C0, 4) { eb_m_52110(GM_PASS); }
E(fn_4_35760, 4) { eb_m_521b0(GM_PASS); }
E(fn_4_35770, 4) { eb_m_521c0(GM_PASS); }
E(fn_4_357B0, 4) { eb_m_52200(GM_PASS); }
E(fn_4_35890, 4) { eb_m_522e0(GM_PASS); }
E(fn_4_358A0, 4) { eb_m_522f0(GM_PASS); }
E(fn_4_35990, 4) { eb_m_523e0(GM_PASS); }
E(fn_4_36E70, 4) { eb_m_538c0(GM_PASS); }
E(fn_4_36F40, 4) { eb_m_53990(GM_PASS); }
E(fn_4_378B0, 4) { eb_m_54300(GM_PASS); }
E(fn_4_378C0, 4) { eb_m_54310(GM_PASS); }
E(fn_4_378D0, 4) { eb_m_54320(GM_PASS); }
E(fn_4_37C70, 4) { eb_m_546c0(GM_PASS); }
E(fn_4_37C80, 4) { eb_m_546d0(GM_PASS); }
E(fn_4_37C90, 4) { eb_m_546e0(GM_PASS); }
E(fn_4_37CA0, 4) { eb_m_546f0(GM_PASS); }
E(fn_4_37CB0, 4) { eb_m_54700(GM_PASS); }
E(fn_4_37CC0, 4) { eb_m_54710(GM_PASS); }
E(fn_4_37CD0, 4) { eb_m_54720(GM_PASS); }
E(fn_4_37CE0, 4) { eb_m_54730(GM_PASS); }
E(fn_4_37CF0, 4) { eb_m_54740(GM_PASS); }
E(fn_4_3BD30, 4) { eb_m_58780(GM_PASS); }
E(fn_4_3D100, 4) { eb_m_59b50(GM_PASS); }
E(fn_4_3D110, 4) { eb_m_59b60(GM_PASS); }
E(fn_4_3D120, 4) { eb_m_59b70(GM_PASS); }
E(fn_4_3D130, 4) { eb_m_59b80(GM_PASS); }
E(fn_4_3D140, 4) { eb_m_59b90(GM_PASS); }
E(fn_4_3D150, 4) { eb_m_59ba0(GM_PASS); }
E(fn_4_3D160, 4) { eb_m_59bb0(GM_PASS); }
E(fn_4_3D170, 4) { eb_m_59bc0(GM_PASS); }
E(fn_4_3D180, 4) { eb_m_59bd0(GM_PASS); }
E(fn_4_3D190, 4) { eb_m_59be0(GM_PASS); }
E(fn_4_3D1A0, 4) { eb_m_59bf0(GM_PASS); }
E(fn_4_3D1B0, 4) { eb_m_59c00(GM_PASS); }
E(fn_4_3D1C0, 4) { eb_m_59c10(GM_PASS); }
E(fn_4_3D530, 4) { eb_m_59f80(GM_PASS); }
E(fn_4_3D540, 4) { eb_m_59f90(GM_PASS); }
E(fn_4_3D550, 4) { eb_m_59fa0(GM_PASS); }
E(fn_4_3D560, 4) { eb_m_59fb0(GM_PASS); }
E(fn_4_3D570, 4) { eb_m_59fc0(GM_PASS); }
E(fn_4_3D580, 4) { eb_m_59fd0(GM_PASS); }
E(fn_4_3D590, 4) { eb_m_59fe0(GM_PASS); }
E(fn_4_3D5A0, 4) { eb_m_59ff0(GM_PASS); }
E(fn_4_3D5B0, 4) { eb_m_5a000(GM_PASS); }
E(fn_4_3D5C0, 4) { eb_m_5a010(GM_PASS); }
E(fn_4_3D5D0, 4) { eb_m_5a020(GM_PASS); }
E(fn_4_3D5E0, 4) { eb_m_5a030(GM_PASS); }
E(fn_4_3D5F0, 4) { eb_m_5a040(GM_PASS); }
E(fn_4_3D600, 4) { eb_m_5a050(GM_PASS); }
E(fn_4_3D610, 4) { eb_m_5a060(GM_PASS); }
E(fn_4_3D620, 4) { eb_m_5a070(GM_PASS); }
E(fn_4_3D630, 4) { eb_m_5a080(GM_PASS); }
E(fn_4_41490, 4) { eb_m_5dee0(GM_PASS); }
E(fn_4_42860, 4) { eb_m_5f2b0(GM_PASS); }
E(fn_4_42870, 4) { eb_m_5f2c0(GM_PASS); }
E(fn_4_42880, 4) { eb_m_5f2d0(GM_PASS); }
E(fn_4_42890, 4) { eb_m_5f2e0(GM_PASS); }
E(fn_4_428A0, 4) { eb_m_5f2f0(GM_PASS); }
E(fn_4_42BF0, 4) { eb_m_5f640(GM_PASS); }
E(fn_4_42C00, 4) { eb_m_5f650(GM_PASS); }
E(fn_4_42C10, 4) { eb_m_5f660(GM_PASS); }
E(fn_4_42C20, 4) { eb_m_5f670(GM_PASS); }
E(fn_4_42C30, 4) { eb_m_5f680(GM_PASS); }
E(fn_4_42C40, 4) { eb_m_5f690(GM_PASS); }
E(fn_4_42C50, 4) { eb_m_5f6a0(GM_PASS); }
E(fn_4_42C60, 4) { eb_m_5f6b0(GM_PASS); }
E(fn_4_42C70, 4) { eb_m_5f6c0(GM_PASS); }
E(fn_4_45720, 4) { eb_m_62170(GM_PASS); }
E(fn_4_46420, 4) { eb_m_62e70(GM_PASS); }
E(fn_4_46430, 4) { eb_m_62e80(GM_PASS); }
E(fn_4_46440, 4) { eb_m_62e90(GM_PASS); }
E(fn_4_46450, 4) { eb_m_62ea0(GM_PASS); }
E(fn_4_46460, 4) { eb_m_62eb0(GM_PASS); }
E(fn_4_467F0, 4) { eb_m_63240(GM_PASS); }
E(fn_4_46800, 4) { eb_m_63250(GM_PASS); }
E(fn_4_46810, 4) { eb_m_63260(GM_PASS); }
E(fn_4_46820, 4) { eb_m_63270(GM_PASS); }
E(fn_4_46830, 4) { eb_m_63280(GM_PASS); }
E(fn_4_46840, 4) { eb_m_63290(GM_PASS); }
E(fn_4_46850, 4) { eb_m_632a0(GM_PASS); }
E(fn_4_46860, 4) { eb_m_632b0(GM_PASS); }
E(fn_4_46870, 4) { eb_m_632c0(GM_PASS); }
E(fn_4_49450, 4) { eb_m_65ea0(GM_PASS); }
E(fn_4_4A420, 4) { eb_m_66e70(GM_PASS); }
E(fn_4_4A430, 4) { eb_m_66e80(GM_PASS); }
E(fn_4_4A440, 4) { eb_m_66e90(GM_PASS); }
E(fn_4_4A450, 4) { eb_m_66ea0(GM_PASS); }
E(fn_4_4A460, 4) { eb_m_66eb0(GM_PASS); }
E(fn_4_4A470, 4) { eb_m_66ec0(GM_PASS); }
E(fn_4_4A480, 4) { eb_m_66ed0(GM_PASS); }
E(fn_4_4A490, 4) { eb_m_66ee0(GM_PASS); }
E(fn_4_4A800, 4) { eb_m_67250(GM_PASS); }
E(fn_4_4A810, 4) { eb_m_67260(GM_PASS); }
E(fn_4_4A820, 4) { eb_m_67270(GM_PASS); }
E(fn_4_4A830, 4) { eb_m_67280(GM_PASS); }
E(fn_4_4A840, 4) { eb_m_67290(GM_PASS); }
E(fn_4_4DF20, 4) { eb_m_6a970(GM_PASS); }
E(fn_4_4EF10, 4) { eb_m_6b960(GM_PASS); }
E(fn_4_4EF20, 4) { eb_m_6b970(GM_PASS); }
E(fn_4_4EF30, 4) { eb_m_6b980(GM_PASS); }
E(fn_4_4EF40, 4) { eb_m_6b990(GM_PASS); }
E(fn_4_4EF50, 4) { eb_m_6b9a0(GM_PASS); }
E(fn_4_4EF60, 4) { eb_m_6b9b0(GM_PASS); }
E(fn_4_4EF70, 4) { eb_m_6b9c0(GM_PASS); }
E(fn_4_4EF80, 4) { eb_m_6b9d0(GM_PASS); }
E(fn_4_4EF90, 4) { eb_m_6b9e0(GM_PASS); }
E(fn_4_4EFA0, 4) { eb_m_6b9f0(GM_PASS); }
E(fn_4_4EFB0, 4) { eb_m_6ba00(GM_PASS); }
E(fn_4_4EFC0, 4) { eb_m_6ba10(GM_PASS); }
E(fn_4_4F3C0, 4) { eb_m_6be10(GM_PASS); }
E(fn_4_4FA80, 4) { eb_m_6c4d0(GM_PASS); }
E(fn_4_4FB50, 4) { eb_m_6c5a0(GM_PASS); }
E(fn_4_4FB70, 4) { eb_m_6c5c0(GM_PASS); }
E(fn_4_4FB80, 4) { eb_m_6c5d0(GM_PASS); }
E(fn_4_4FCF0, 4) { eb_m_6c740(GM_PASS); }
E(fn_4_50370, 4) { eb_m_6cdc0(GM_PASS); }
E(fn_4_506B0, 4) { eb_m_6d100(GM_PASS); }
E(fn_4_506C0, 4) { eb_m_6d110(GM_PASS); }
E(fn_4_507B0, 4) { eb_m_6d200(GM_PASS); }
E(fn_4_50800, 4) { eb_m_6d250(GM_PASS); }
E(fn_4_508C0, 4) { eb_m_6d310(GM_PASS); }
E(fn_4_51750, 4) { eb_m_6e1a0(GM_PASS); }
E(fn_4_536D0, 4) { eb_m_70120(GM_PASS); }
E(fn_4_53710, 4) { eb_m_70160(GM_PASS); }
E(fn_4_53770, 4) { eb_m_701c0(GM_PASS); }
E(fn_4_53B70, 4) { eb_m_705c0(GM_PASS); }
E(fn_4_53D90, 4) { eb_m_707e0(GM_PASS); }
E(fn_4_53DD0, 4) { eb_m_70820(GM_PASS); }
E(fn_4_549C0, 4) { eb_m_71410(GM_PASS); }
E(fn_4_54A50, 4) { eb_m_714a0(GM_PASS); }
E(fn_4_54AD0, 4) { eb_m_71520(GM_PASS); }
E(fn_4_54D70, 4) { eb_m_717c0(GM_PASS); }
E(fn_4_55090, 4) { eb_m_71ae0(GM_PASS); }
E(fn_4_554D0, 4) { eb_m_71f20(GM_PASS); }
E(fn_4_55520, 4) { eb_m_71f70(GM_PASS); }
E(fn_4_55580, 4) { eb_m_71fd0(GM_PASS); }
E(fn_4_557A0, 4) { eb_m_721f0(GM_PASS); }
E(fn_4_557F0, 4) { eb_m_72240(GM_PASS); }
E(fn_4_55890, 4) { eb_m_722e0(GM_PASS); }
E(fn_4_55910, 4) { eb_m_72360(GM_PASS); }
E(fn_4_55C10, 4) { eb_m_72660(GM_PASS); }
E(fn_4_55CC0, 4) { eb_m_72710(GM_PASS); }
E(fn_4_55E40, 4) { eb_m_72890(GM_PASS); }
E(fn_4_55ED0, 4) { eb_m_72920(GM_PASS); }
E(fn_4_55FC0, 4) { eb_m_72a10(GM_PASS); }
E(fn_4_56050, 4) { eb_m_72aa0(GM_PASS); }
E(fn_4_56070, 4) { eb_m_72ac0(GM_PASS); }
E(fn_4_560F0, 4) { eb_m_72b40(GM_PASS); }
E(fn_4_56150, 4) { eb_m_72ba0(GM_PASS); }
E(fn_4_56180, 4) { eb_m_72bd0(GM_PASS); }
E(fn_4_561B0, 4) { eb_m_72c00(GM_PASS); }
E(fn_4_562A0, 4) { eb_m_72cf0(GM_PASS); }
E(fn_4_564B0, 4) { eb_m_72f00(GM_PASS); }
E(fn_4_56510, 4) { eb_m_72f60(GM_PASS); }
E(fn_4_56600, 4) { eb_m_73050(GM_PASS); }
E(fn_4_56630, 4) { eb_m_73080(GM_PASS); }
E(fn_4_56780, 4) { eb_m_731d0(GM_PASS); }
E(fn_4_56820, 4) { eb_m_73270(GM_PASS); }
E(fn_4_56860, 4) { eb_m_732b0(GM_PASS); }
E(fn_4_56920, 4) { eb_m_73370(GM_PASS); }
E(fn_4_56A30, 4) { eb_m_73480(GM_PASS); }
E(fn_4_56AA0, 4) { eb_m_734f0(GM_PASS); }
E(fn_4_56B90, 4) { eb_m_735e0(GM_PASS); }
E(fn_4_56D10, 4) { eb_m_73760(GM_PASS); }
E(fn_4_56DD0, 4) { eb_m_73820(GM_PASS); }
E(fn_4_56F40, 4) { eb_m_73990(GM_PASS); }
