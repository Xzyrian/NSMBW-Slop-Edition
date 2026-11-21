/* gm_d_staff_credit.c - dStaffCreditScore_c: eight-player coin totals,
 * high-score presentation and winner-animation coordination in the credits. */
#include "gm_i2.h"
RT_STATE_FILE

#define SCS_FRAME   (0x81860000u - 300)
#define SCS_ACTIVE  (0x81860000u - 5828)
#define SCS_RES     0x81850000u
#define SCS_END     (0x80990000u + 22440)

static uint32_t scs_classInit(GM_CTX) {
    I2_FN(0x8181E968u);
    R(3) = 800; BL(0x8181E980u, hle_AllocateMemoryBlock);
    NV_R(30, R(3)); BL(0x8181E988u, fn_2_40360_807ADB10);
    R(3) = R(30); return R(3);
}

static uint32_t scs_createLayout(GM_CTX, gptr self) {
    I2_FN(0x8181E9A0u);
    NV_R(25, 0x81860000u); NV_R(28, self); NV_R(30, self + 112);
    R(3) = gm_u32(R(25) - 300); gm_set_u32(gm_frame_sp + 112, R(3));
    NV_R(27, SCS_RES - 7736);
    R(3) = R(30); R(4) = R(27) + 374; R(5) = 0; BL(0x8181E9F0u, hle_loadArc__Q23m2d13EmbedLayout_cFPCcb);
    NV_R(29, R(3)); CMPU(R(3), 0);
    if (R(3) != 0) {
        R(3) = R(30); R(4) = R(27) + 353; R(5) = 0; BL(0x8181EA0Cu, hle_fn_800C8A10);
        NV_R(26, gm_frame_sp + 8); R(3) = R(26); R(4) = SCS_RES + 11648; R(5) = 20;
        BL(0x8181EA24u, mod_memcpy_81844C38);
        R(3) = R(30); R(4) = R(26); R(5) = 5; BL(0x8181EA34u, hle_loadAnimations__Q23m2d13EmbedLayout_cFPPCci);
        R(3) = R(26); R(4) = SCS_RES + 11668; R(5) = 104; BL(0x8181EA4Cu, mod_memcpy_81844C38);
        R(3) = R(30); R(4) = R(26); R(5) = R(27); R(6) = 26;
        BL(0x8181EA60u, hle_loadGroups__Q23m2d13EmbedLayout_cFPPCcPCii);
        R(3) = R(30); BL(0x8181EA68u, CBGetBytesAvailableForRead_80007220);
        gm_set_u32(self + 580, R(3));
        R(3) = R(30); R(4) = SCS_RES + 11772; R(5) = self + 696; R(6) = 8; NV_R(27, 8);
        BL(0x8181EA88u, hle_getTextBoxes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7TextBoxi);
        R(3) = R(30); R(4) = SCS_RES + 11804; R(5) = self + 600; R(6) = 2;
        BL(0x8181EAA0u, hle_getTextBoxes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7TextBoxi);
        BL(0x8181EAA4u, hle_getMesRes__10dMessage_cFv);
        R(4) = R(3); R(3) = gm_u32(self + 604); R(5) = 305; R(6) = 1; R(7) = 0;
        CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
        BL(0x8181EAC0u, hle_WriteBMGToTextBox__FPQ34nw4r3lyt7TextBoxPQ27dScript5Res_ciiie);
        R(3) = R(30); R(4) = SCS_RES + 11812; R(5) = self + 608; R(6) = 6;
        BL(0x8181EAD8u, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
        NV_R(28, 17);
        do {
            R(3) = R(30); R(4) = R(28); R(5) = 0; BL(0x8181EAECu, hle_resetAnim__Q23m2d13EmbedLayout_cFib);
            NV_R(27, R(27) - 1); CMPU(R(27), 0); NV_R(28, R(28) + 1);
            if (R(27)) GM_LOOP(); else break;
        } while (1);
    }
    R(3) = gm_u32(R(25) - 300); R(4) = gm_u32(gm_frame_sp + 112); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x8181EB3Cu, mfn_81844FCC);
    R(3) = R(29); return R(3);
}

static void scs_setCoinCount(GM_CTX, gptr self, uint32_t player) {
    I2_FN(0x8181EB3Cu);
    NV_R(30, 0x81860000u); R(5) = gm_u32(R(30) - 300); gm_set_u32(gm_frame_sp + 20, R(5));
    R(4) = i2_rotl(player, 2) & 0xFFFFFFFCu; R(5) = gm_u32(SCS_ACTIVE + R(4));
    R(6) = self + R(4) + 728; R(4) = 3; gm_set_u32(gm_frame_sp + 16, R(4));
    R(4) = i2_rotl(R(5), 2) & 0xFFFFFFFCu; R(3) = self + R(4); R(5) = gm_u32(R(3) + 696);
    R(3) = R(6); R(4) = gm_frame_sp + 16; R(6) = 1;
    BL(0x8181EB94u, LayoutDispNumber__8dGameComFRCiRCiP12LytTextBox_cb_800B3B60);
    R(3) = gm_u32(R(30) - 300); R(4) = gm_u32(gm_frame_sp + 20); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x8181EBBCu, mfn_81844FCC);
}

static void scs_updateCoinCounts(GM_CTX, gptr self) {
    I2_FN(0x8181EBBCu);
    NV_R(26, self + 756); NV_R(27, self + 696); R(3) = SCS_ACTIVE;
    NV_R(29, 8); NV_R(28, 3); R(6) = gm_u32(SCS_FRAME);
    R(4) = R(3) - 4; NV_R(30, gm_frame_sp + 12); gm_set_u32(gm_frame_sp + 16, R(6));
    do {
        R(26) += 4; R(6) = gm_u32(R(26)); NV_R(25, R(4) + 4);
        R(3) = R(26) - 32; R(5) = gm_u32(R(3)); CMPU(R(6), R(5));
        if (R(6) != R(5)) {
            R(4) = gm_u32(R(4) + 4); R(6) = 1; gm_set_u32(R(26), R(5));
            R(4) = i2_rotl(R(4), 2) & 0xFFFFFFFCu; R(5) = gm_u32(R(27) + R(4));
            R(4) = R(30); gm_set_u32(gm_frame_sp + 12, R(28));
            BL(0x8181EC44u, LayoutDispNumber__8dGameComFRCiRCiP12LytTextBox_cb_800B3B60);
        }
        NV_R(29, R(29) - 1); CMPU(R(29), 0); R(4) = R(25);
        if (R(29)) GM_LOOP(); else break;
    } while (1);
    R(3) = gm_u32(SCS_FRAME); R(4) = gm_u32(gm_frame_sp + 16); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x8181EC94u, mfn_81844FCC);
}

static void scs_onStageWait(GM_CTX, gptr self) {
    I2_FN(0x8181EC94u);
    NV_R(30, self); R(3) = self + 112; BL(0x8181ECB0u, hle_disableAllAnimations__Q23m2d13EmbedLayout_cFv);
    R(4) = gm_u32(self + 580); R(5) = gm_u8(R(4) + 187) & 0xFEu; gm_set_u8(R(4) + 187, R(5));
    R(3) = self + 724; ctx->ctr = 8;
    do {
        R(3) += 4; gm_set_u32(R(3), 0); gm_set_u32(R(3) + 32, 0xFFFFFFFFu);
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    R(3) = self; BL(0x8181ECE8u, hle_mod_fn_2_40A20);
    gm_set_u16(self + 638, 0);
}

static void scs_onStageAnimeEndWait(GM_CTX, gptr self) {
    I2_FN(0x8181ED04u);
    NV_R(27, 8); NV_R(28, 0); NV_R(29, self + 112); NV_R(30, self);
    do {
        R(3) = R(29); R(4) = R(28); R(5) = 0; BL(0x8181ED40u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
        NV_R(27, R(27) - 1); CMPU(R(27), 0); NV_R(28, R(28) + 1);
        if (R(27)) GM_LOOP(); else break;
    } while (1);
    R(3) = R(29); R(4) = 16; R(5) = 0; BL(0x8181ED60u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
    R(3) = gm_u32(self + 580); R(4) = gm_u8(R(3) + 187) | 1; gm_set_u8(R(3) + 187, R(4));
}

static void scs_highScoreCheck(GM_CTX, gptr self) {
    I2_FN(0x8181ED90u);
    NV_R(30, self); R(3) = gm_u32(0x80430000u - 25452); BL(0x8181EDC8u, hle_mod_fn_8005CB70);
    R(3) = gm_u32(self + 688); gm_set_u8(self + 645, 1);
    R(4) = self + 791; R(5) = self + 724; R(7) = 0xFFFFFFFFu; R(8) = 0; ctx->ctr = 8;
    do {
        R(5) += 4; R(9) = gm_u32(R(5)); R(4)++; gm_set_u8(R(4), 0);
        CMPS(R(3), R(9));
        if ((int32_t)R(3) <= (int32_t)R(9)) {
            R(3) = R(9); R(7) = R(8); gm_set_u32(self + 688, R(9));
        }
        R(8)++; if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    CMPS(R(7), 0); gm_set_u32(self + 692, R(7));
    if ((int32_t)R(7) >= 0) {
        NV_R(29, self + 112); NV_R(28, self + 724); NV_R(26, self + 791);
        NV_R(27, 8); NV_R(24, SCS_ACTIVE - 4); NV_R(25, 1);
        do {
            R(28) += 4; R(6) = gm_u32(R(28)); R(3) = R(24); R(4) = gm_u32(self + 688);
            R(5) = R(26); NV_R(24, R(24) + 4); NV_R(26, R(26) + 1); CMPU(R(4), R(6));
            if (R(4) == R(6)) {
                CMPU(R(4), 0); gm_set_u8(R(5) + 1, R(25));
                if (R(4) != 0) {
                    R(3) = gm_u32(R(3) + 4); R(5) = 0; R(4) = R(3) + 17; R(3) = R(29);
                    BL(0x8181EE80u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
                }
            }
            NV_R(27, R(27) - 1); CMPU(R(27), 0);
            if (R(27)) GM_LOOP(); else break;
        } while (1);
        R(3) = gm_u32(0x80430000u - 23384); BL(0x8181EE98u, fn_8019C4D0);
        R(3) = gm_u32(self + 688);
    }
    R(4) = gm_u32(self + 684); CMPS(R(4), R(3));
    if ((int32_t)R(4) < (int32_t)R(3)) gm_set_u32(self + 684, R(3));
}

static void scs_highScoreAnimeEndWait(GM_CTX, gptr self) {
    I2_FN(0x8181EED8u);
    NV_R(29, 0x81860000u); NV_R(30, self); R(4) = gm_u32(R(29) - 300);
    gm_set_u32(gm_frame_sp + 16, R(4)); R(3) = gm_u32(self + 692); CMPS(R(3), 0);
    if ((int32_t)R(3) >= 0) {
        R(3) = gm_u32(self + 688); CMPU(R(3), 0);
        if (R(3) != 0) {
            R(5) = gm_u32(self + 600); R(3) = 3; gm_set_u32(gm_frame_sp + 12, R(3));
            R(3) = self + 684; R(4) = gm_frame_sp + 12; R(6) = 1;
            BL(0x8181EF30u, LayoutDispNumber__8dGameComFRCiRCiP12LytTextBox_cb_800B3B60);
            R(3) = self + 112; R(4) = 25; R(5) = 0; BL(0x8181EF40u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
        }
    }
    R(3) = gm_u32(R(29) - 300); R(4) = gm_u32(gm_frame_sp + 16); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x8181EF6Cu, mfn_81844FCC);
}

static void scs_no1PlayerKiMeInit(GM_CTX, gptr self) {
    I2_FN(0x8181EF6Cu);
    R(4) = gm_u32(self + 692); CMPS(R(4), 0);
    if ((int32_t)R(4) >= 0) {
        NV_R(29, self + 791); NV_R(28, 8); NV_R(30, 0);
        do {
            R(3) = R(30); BL(0x8181EFA4u, hle_getPlayer__9daPyMng_cFi);
            R(29)++; R(4) = gm_u8(R(29)); CMPU(R(3), 0);
            if (R(3) != 0) {
                R(4) &= 1; CR0(ctx, R(4));
                if (R(4) != 0) { R(4) = 2; BL(0x8181EFC0u, setAnimePlayStandardType__10daPlBase_cFi_80052290); }
            }
            NV_R(28, R(28) - 1); CMPU(R(28), 0); NV_R(30, R(30) + 1);
            if (R(28)) GM_LOOP(); else break;
        } while (1);
    }
}

static void scs_no1PlayerKiMeExecute(GM_CTX, gptr self) {
    I2_FN(0x8181EFECu);
    NV_R(30, self); R(3) = gm_u32(self + 692); CMPS(R(3), 0); NV_R(27, 0);
    if ((int32_t)R(3) >= 0) {
        NV_R(28, self + 791); NV_R(26, 8); NV_R(29, 0);
        do {
            R(3) = R(29); BL(0x8181F034u, hle_getPlayer__9daPyMng_cFi);
            R(28)++; R(4) = gm_u8(R(28)); CMPU(R(3), 0);
            if (R(3) != 0) {
                R(4) &= 1; CR0(ctx, R(4));
                if (R(4) != 0) {
                    R(3) = gm_u32(R(3) + 10852); R(3) = gm_u32(R(3) + 340);
                    NONZERO(4, 3, R(3)); NV_R(27, R(3) | R(27));
                }
            }
            NV_R(26, R(26) - 1); CMPU(R(26), 0); NV_R(29, R(29) + 1);
            if (R(26)) GM_LOOP(); else break;
        } while (1);
        R(3) = R(27) & 1; CR0(ctx, R(3));
    }
    if (R(27) == 0) {
        R(3) = self + 544; R(4) = SCS_END; BL(0x8181F084u, mod_fn_8015FC10_81838420);
    }
}

GM_HLE_VERIFIED_(mod_fn_2_40330, GMV_IGNORE_POLLS, 0, 0) { R(3) = scs_classInit(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_2_40770, GMV_IGNORE_POLLS, 0, 0) { R(3) = scs_createLayout(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_409A0, GMV_IGNORE_POLLS, 0, 0) { scs_setCoinCount(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_2_40A20, GMV_IGNORE_POLLS, 0, 0) { scs_updateCoinCounts(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_40A90, GMV_IGNORE_POLLS, 0, 0) { scs_onStageWait(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_40B60, GMV_IGNORE_POLLS, 0, 0) { scs_onStageAnimeEndWait(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_40D80, GMV_IGNORE_POLLS, 0, 0) { scs_highScoreCheck(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_40FB0, GMV_IGNORE_POLLS, 0, 0) { scs_highScoreAnimeEndWait(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_41160, GMV_IGNORE_POLLS, 0, 0) { scs_no1PlayerKiMeInit(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_411E0, GMV_IGNORE_POLLS, 0, 0) { scs_no1PlayerKiMeExecute(GM_PASS, GM_ARG(0)); }
