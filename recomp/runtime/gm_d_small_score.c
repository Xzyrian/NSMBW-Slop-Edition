/* gm_d_small_score.c - dSmallScore_c popup colors and display-wait completion.
 * Register-exact against the 8-player module's USA rev 2 replacements. */
#include "gm_i2.h"
RT_STATE_FILE

#define DSS_COLOR_0  (0x81850000u - 31251)
#define DSS_COLOR_2  (0x81850000u - 31215)
#define DSS_COLOR_100 (0x81850000u - 31179)
#define DSS_INFO     (0x80430000u - 24708)

static void dss_setPlayer1000Color(GM_CTX, gptr self, uint32_t player) {
    I2_FN(0x81800A9Cu);
    NV_R(28, 0x81860000u); NV_R(30, self);
    R(3) = gm_u32(R(28) - 300); gm_set_u32(gm_frame_sp + 24, R(3));
    R(3) = 8; CMPS(R(4), 7);
    if ((int32_t)R(4) <= 7) { R(3) = R(4); BL(0x81800ADCu, mfn_81806AB8); }
    NV_R(27, i2_rotl(R(3), 2) & 0xFFFFFFFCu);
    R(3) = DSS_COLOR_0; R(4) = gm_u32(R(3) + R(27)); NV_R(29, gm_frame_sp + 8);
    R(3) = gm_u32(R(30) + 476); gm_set_u32(gm_frame_sp + 20, R(4));
    R(5) = gm_u32(R(3)); R(5) = gm_u32(R(5) + 40); gm_set_u32(gm_frame_sp + 8, R(4));
    R(4) = 0; ctx->ctr = R(5); R(5) = R(29); ctx->lr = 0x81800B14u;
    ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = DSS_COLOR_2; R(4) = gm_u32(R(3) + R(27)); R(3) = gm_u32(R(30) + 476);
    gm_set_u32(gm_frame_sp + 16, R(4)); R(5) = gm_u32(R(3)); R(5) = gm_u32(R(5) + 40);
    gm_set_u32(gm_frame_sp + 8, R(4)); R(4) = 2; ctx->ctr = R(5); R(5) = R(29);
    ctx->lr = 0x81800B44u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = gm_u32(R(28) - 300); R(4) = gm_u32(gm_frame_sp + 24); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x81800B78u, mfn_81844FCC);
}

static void dss_setPlayer100Color(GM_CTX, gptr self, uint32_t player) {
    I2_FN(0x81800B78u);
    CMPS(R(4), 7); NV_R(29, self); NV_R(30, 8);
    if ((int32_t)R(4) <= 7) { R(3) = R(4); BL(0x81800BA4u, mfn_81806AB8); NV_R(30, R(3)); }
    R(3) = gm_u32(R(29) + 472); R(4) = gm_u32(R(3)); R(4) = gm_u32(R(4) + 104);
    ctx->ctr = R(4); ctx->lr = 0x81800BBCu; ppc_call_indirect(ctx, base, ctx->ctr);
    R(5) = DSS_COLOR_100; R(4) = i2_rotl(R(30), 2) & 0xFFFFFFFCu; R(5) += R(4);
    R(4) = gm_u8(R(5)); R(7) = 255; R(6) = gm_u8(R(5) + 2); R(5) = gm_u8(R(5) + 1);
    R(6) = i2_rotl(R(6), 16) & 0xFFFF0000u;
    R(7) = (R(6) & 0xFFFFFF00u) | (R(7) & 0xFFu);
    R(5) = (i2_rotl(R(4), 16) & 0xFFFF0000u) | (R(5) & 0xFFFFu);
    gm_set_u32(R(3) + 28, R(7)); gm_set_u32(R(3) + 24, R(5));
}

static void dss_chgColor(GM_CTX, gptr self) {
    I2_FN(0x81800C04u);
    NV_R(30, self); R(3) = gm_u8(R(3) + 542); CMPU(R(3), 1);
    if (R(3) != 1) return;
    R(3) = gm_u32(R(30) + 524); R(4) = R(3) + 1; CMPS(R(3), 9);
    gm_set_u32(R(30) + 524, R(4));
    if ((int32_t)R(3) < 9) return;
    R(3) = 0; NV_R(29, gm_u32(R(30) + 528)); gm_set_u32(R(30) + 524, R(3));
    R(3) = gm_u32(DSS_INFO); CMPS(R(29), 7); R(4) = R(29);
    if ((int32_t)R(29) <= 7) R(4) = 7;
    R(5) = i2_rotl(R(29), 2) & 0xFFFFFFFCu; R(4) -= R(29); R(3) += R(5);
    R(4)++; R(3) += 2896; ctx->ctr = R(4);
    for (;;) {
        if (--ctx->ctr == 0) { R(29) = 0; break; }
        NV_R(29, R(29) + 1); CMPU(R(29), 4);
        R(4) = R(29) < 4 ? R(3) - 1992 : R(3);
        R(4) = gm_u32(R(4)); R(3) += 4; CMPU(R(4), 3);
        if (R(4) == 3) break;
        GM_LOOP();
    }
    R(3) = R(30); R(4) = R(29); BL(0x81800CB8u, fn_80015200);
    gm_set_u32(R(30) + 528, R(29));
}

static void dss_dispWait(GM_CTX, gptr self) {
    I2_FN(0x81800CD4u);
    NV_R(30, self); R(3) = gm_u8(R(3) + 543); CMPU(R(3), 1);
    if (R(3) == 1) { R(3) = R(30); BL(0x81800CFCu, fn_80015780); }
    R(3) = R(30); ctx->lr = 0x81800D04u; dss_chgColor(GM_PASS, R(30));
    R(3) = gm_u32(R(30) + 512); R(5) = gm_u32(R(30) + 520); R(4) = R(3) + 1;
    gm_set_u32(R(30) + 512, R(4)); CMPU(R(5), 8);
    if (R(5) == 8) {
        CMPS(R(3), 59);
        if ((int32_t)R(3) < 59) return;
    } else {
        R(3) = gm_u32(R(30) + 516); CMPS(R(4), R(3));
        if ((int32_t)R(4) < (int32_t)R(3)) return;
    }
    R(4) = 0; gm_set_u32(R(30) + 512, R(4));
    for (uint32_t off = 468; off <= 496; off += 4) {
        R(3) = gm_u32(R(30) + off); R(5) = gm_u8(R(3) + 187) & 0xFEu;
        gm_set_u8(R(3) + 187, R(5));
    }
    R(3) = gm_u32(R(30) + 536); gm_set_u8(R(30) + 543, R(4));
    R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(3) += R(30);
    R(4) = gm_u32(R(30) + 448); R(3) = gm_u32(R(3) + 472); R(5) = gm_u32(R(30) + 444);
    gm_set_u32(R(3) + 72, R(4)); gm_set_u32(R(3) + 68, R(5));
    R(3) = 4; gm_set_u32(R(30) + 504, R(3));
}

GM_HLE_VERIFIED_(mod_fn_80015210, GMV_IGNORE_POLLS, 0, 0) { dss_setPlayer1000Color(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_800153B0, GMV_IGNORE_POLLS, 0, 0) { dss_setPlayer100Color(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_800154E0, GMV_IGNORE_POLLS, 0, 0) { dss_chgColor(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_80015AD0, GMV_IGNORE_POLLS, 0, 0) { dss_dispWait(GM_PASS, GM_ARG(0)); }
