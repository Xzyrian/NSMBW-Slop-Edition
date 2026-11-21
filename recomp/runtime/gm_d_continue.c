/* gm_d_continue.c - dContinue_c: continue-menu layout, counters, card layout,
 * effects and terminal menu states (track B, gm_i2.h). */
#include "gm_i2.h"
RT_STATE_FILE

/* Calls between methods enter through their generated HLE entry points. */
#define mod_fn_2_A260_81818B74 hle_mod_fn_2_A260
#define mod_fn_2_A750_81818D68 hle_mod_fn_2_A750
#define mod_fn_2_A630_81818E88 hle_mod_fn_2_A630
#define mod_fn_2_A6C0_81819000 hle_mod_fn_2_A6C0
#define mod_fn_2_A860_81819080 hle_mod_fn_2_A860

#define CONT_FRAME         (0x81860000u - 300)
#define CONT_RES           (0x81850000u - 15160)
#define CONT_SOUND_MANAGER (0x80430000u - 23416)
#define CONT_SAVE_MANAGER  (0x80430000u - 24512)
#define CONT_STATE(n)      (0x80990000u + (n))

static uint32_t cont_createLayout(GM_CTX, gptr self) {
    I2_FN(0x81818B74u);
    R(5) = 0; NV_R(26, 0x81860000u); NV_R(29, self); NV_R(28, self + 112);
    R(3) = gm_u32(R(26) - 300); gm_set_u32(gm_frame_sp + 48, R(3));
    R(3) = 0x81850000u; NV_R(25, R(3) - 15160);
    R(4) = R(25) + 1017; R(3) = R(28); BL(0x81818BC4u, hle_loadArc__Q23m2d13EmbedLayout_cFPCcb);
    NV_R(30, R(3)); CMPU(R(3), 0);
    if (R(3) != 0) {
        R(4) = R(25) + 999; R(3) = R(28); R(5) = 0; BL(0x81818BE0u, hle_fn_800C8A10);
        R(3) = 0x81850000u; NV_R(27, gm_frame_sp + 16); R(4) = R(3) + 9576; R(3) = R(27); R(5) = 28;
        BL(0x81818BF8u, mod_memcpy_81844C38);
        R(3) = R(28); R(4) = R(27); R(5) = 7; BL(0x81818C08u, hle_loadAnimations__Q23m2d13EmbedLayout_cFPPCci);
        R(3) = 0x81850000u; NV_R(27, gm_frame_sp + 16); R(4) = R(3) + 9604; R(3) = R(27); R(5) = 28;
        BL(0x81818C20u, mod_memcpy_81844C38);
        R(5) = R(25) + 32; R(3) = R(28); R(4) = R(27); R(6) = 7;
        BL(0x81818C34u, hle_loadGroups__Q23m2d13EmbedLayout_cFPPCcPCii);
        R(3) = R(28); BL(0x81818C3Cu, CBGetBytesAvailableForRead_80007220); gm_set_u32(R(29) + 580, R(3));
        R(3) = 0x81850000u; NV_R(27, gm_frame_sp + 16); R(4) = R(3) + 9632; R(3) = R(27); R(5) = 32;
        BL(0x81818C58u, mod_memcpy_81844C38);
        R(5) = R(25) + 92; R(3) = R(28); R(4) = R(27); R(6) = 6; R(7) = 8;
        BL(0x81818C70u, hle_setLangStrings__Q23m2d13EmbedLayout_cFPPCcPCiii);
        R(3) = 0x81850000u; R(5) = R(29) + 584; R(4) = R(3) + 9664; R(3) = R(28); R(6) = 1;
        BL(0x81818C88u, hle_getPictures__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7Picturei);
        R(3) = 0x81850000u; NV_R(27, gm_frame_sp + 16); R(4) = R(3) + 9668; R(3) = R(27); R(5) = 32;
        BL(0x81818CA0u, mod_memcpy_81844C38);
        R(5) = R(25) + 60; R(3) = R(28); R(4) = R(27); R(6) = 6; R(7) = 8;
        BL(0x81818CB8u, hle_setLangStrings__Q23m2d13EmbedLayout_cFPPCcPCiii);
        R(3) = 0x81850000u; R(5) = R(29) + 740; R(4) = R(3) + 9700; R(3) = R(28); R(6) = 26;
        BL(0x81818CD0u, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
        R(3) = 0x81850000u; R(5) = R(29) + 844; R(4) = R(3) + 9804; R(3) = R(28); R(6) = 16;
        BL(0x81818CE8u, hle_getTextBoxes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7TextBoxi);
        BL(0x81818CECu, hle_GetAspectRatio__8dGameComFv); CMPU(R(3), 0);
        if (R(3) == 0) {
            R(3) = 0x3F590000u; NV_R(27, R(3) | 0x999Au); R(3) = R(28);
            BL(0x81818D04u, CBGetBytesAvailableForRead_80007220);
            R(4) = R(29) + 736; gm_set_u32(R(3) + 68, R(27)); gm_set_u32(R(3) + 72, R(27));
            R(3) = 18; ctx->ctr = R(3);
            do {
                R(4) += 4; R(3) = gm_u32(R(4)); gm_set_u32(R(3) + 68, R(27)); gm_set_u32(R(3) + 72, R(27));
                ctx->ctr--; if (ctx->ctr) GM_LOOP(); else break;
            } while (1);
        }
    }
    R(3) = gm_u32(R(26) - 300); R(4) = gm_u32(gm_frame_sp + 48); CMPU(R(3), R(4));
    if (R(3) == R(4)) { R(3) = R(30); return R(3); }
    BL(0x81818D68u, mfn_81844FCC); return R(3);
}

static uint32_t cont_create(GM_CTX, gptr self) {
    I2_FN(0x81818A68u);
    NV_R(30, self); R(3) = gm_u8(self + 724); CMPU(R(3), 0);
    int alreadyCreated = R(3) != 0; R(3) = 1;
    if (!alreadyCreated) {
        R(3) = R(30); BL(0x81818AA4u, mod_fn_2_A260_81818B74); CMPU(R(3), 0);
        int failed = R(3) == 0; R(3) = 0;
        if (!failed) {
            NV_R(28, R(30) + 904); NV_R(27, 8); NV_R(29, 0); NV_R(26, 0x80430000u);
            do {
                R(3) = gm_u32(R(26) - 24512); R(4) = (uint32_t)-1;
                BL(0x81818ACCu, hle_mod_getSaveGame__10dSaveMng_cFSc);
                R(4) = R(29); BL(0x81818AD4u, hle_mod_fn_800CE320);
                NV_R(27, R(27) - 1); R(28) += 4; gm_set_u32(R(28), R(3)); CMPU(R(27), 0); NV_R(29, R(29) + 1);
                if (R(27)) GM_LOOP(); else break;
            } while (1);
            R(3) = R(30); BL(0x81818AF0u, mod_fn_2_A750_81818D68);
            R(3) = R(30); BL(0x81818AF8u, mod_fn_2_A630_81818E88);
            NV_R(29, R(30) + 112); R(3) = 145; gm_set_u8(R(30) + 124, R(3));
            R(3) = R(29); BL(0x81818B0Cu, hle_disableAllAnimations__Q23m2d13EmbedLayout_cFv);
            R(3) = R(29); R(4) = 3; R(5) = 0; NV_R(28, 0); BL(0x81818B20u, hle_resetAnim__Q23m2d13EmbedLayout_cFib);
            R(3) = R(29); R(4) = 0; R(5) = 0; BL(0x81818B30u, hle_resetAnim__Q23m2d13EmbedLayout_cFib);
            R(3) = R(29); BL(0x81818B38u, hle_execAnimations__Q23m2d13EmbedLayout_cFv);
            R(3) = R(29); BL(0x81818B40u, hle_fn_80006EB0);
            R(3) = 256; gm_set_u16(R(30) + 724, R(3)); R(3) = 1; gm_set_u8(R(30) + 736, R(28));
        }
    }
    return R(3);
}

static void cont_setPlayerInfo(GM_CTX, gptr self) {
    I2_FN(0x81818D68u);
    R(4) = 0x81850000u; NV_R(30, self); R(3) = 0x81860000u;
    NV_R(22, R(30) + 971); NV_R(23, R(4) + 7564); NV_R(24, R(3) - 5828);
    NV_R(25, R(30) + 936); NV_R(26, 1); NV_R(27, 8); NV_R(28, 0); NV_R(29, 0);
    gm_set_u32(R(30) + 676, R(28));
    do {
        R(3) = R(29); NV_R(21, R(22) + 1); BL(0x81818DD8u, hle_mod_getPlayerIndex__9daPyMng_cF13PLAYER_TYPE_e);
        R(4) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(4) = gm_u32(R(24) + R(4));
        R(4) = i2_rotl(R(4), 2) & 0xFFFFFFFCu; R(4) = gm_u32(R(23) + R(4));
        R(25) += 4; gm_set_u32(R(25), R(4)); BL(0x81818DF0u, hle_mod_PlayerEnterCheck__8dGameComFi);
        CMPU(R(3), 0); R(3) = gm_u32(R(25) - 128);
        if (R(3) && !CR_BIT(ctx, 2)) {
            R(4) = gm_u32(R(25)); CMPS(R(4), 0);
            if (!CR_BIT(ctx, 1)) {
                R(4) = gm_u8(R(3) + 187) | 1; gm_set_u8(R(3) + 187, R(4));
                R(3) = gm_u32(R(30) + 676); gm_set_u8(R(22) + 1, R(26));
                R(3)++; gm_set_u32(R(30) + 676, R(3)); GM_LOOP(); goto next;
            }
        }
        R(4) = gm_u8(R(3) + 187) & 0xFE; gm_set_u8(R(3) + 187, R(4)); gm_set_u8(R(22) + 1, R(28));
next:
        NV_R(27, R(27) - 1); CMPU(R(27), 0); NV_R(29, R(29) + 1); NV_R(22, R(21));
        if (R(27)) GM_LOOP(); else break;
    } while (1);
}

static void cont_setContinue(GM_CTX, gptr self) {
    I2_FN(0x81818E88u);
    NV_R(28, self + 971); NV_R(29, 8); NV_R(30, self + 908); R(3) = self + 840;
    do {
        R(28)++; R(4) = gm_u8(R(28)); NV_R(27, R(3) + 4); CMPU(R(4), 1);
        if (R(4) == 1) {
            R(4) = gm_u32(R(3) + 4); R(3) = R(30); R(5) = 0; BL(0x81818ED4u, InsertIntIntoTextBox1_800B3BE0);
        }
        NV_R(29, R(29) - 1); CMPU(R(29), 0); NV_R(30, R(30) + 4); R(3) = R(27);
        if (R(29)) GM_LOOP(); else break;
    } while (1);
}

static uint32_t cont_getPaneIdx(GM_CTX, gptr self, uint32_t index) {
    I2_FN(0x81818F08u);
    R(3) = gm_u32(self + 676); R(5) = 0x81850000u - 15416;
    R(4) = i2_rotl(index, 2) & 0xFFFFFFFCu; R(3) = i2_rotl(R(3), 5) & 0xFFFFFFE0u;
    R(3) = R(5) + R(3); R(3) += R(4); R(3) = gm_u32(R(3) - 32); return R(3);
}

static void cont_setCardPosition(GM_CTX, gptr self) {
    I2_FN(0x81818F2Cu);
    R(9) = 0x81860000u; R(8) = 8; R(10) = 0x81850000u; R(9) -= 5828;
    R(4) = 0; R(5) = self + 740; R(6) = self + 971; R(7) = self + 808; ctx->ctr = R(8);
    R(8) = R(10) - 15416; R(9) -= 4; R(10) = 0;
    do {
        R(9) += 4; R(0) = gm_u32(R(9)); R(11) = R(7); R(12) = R(6); R(7) += 4;
        CMPU(R(0), 7); R(6)++;
        if (!CR_BIT(ctx, 1)) {
            R(0) = gm_u32(R(3) + 676); NV_R(30, i2_rotl(R(10), 2) & 0xFFFFFFFCu);
            NV_R(30, R(8) + R(30)); R(0) = i2_rotl(R(0), 5) & 0xFFFFFFE0u; NV_R(30, R(30) + R(0));
            R(0) = gm_u32(R(30) - 32); CMPU(R(0), 18);
            if (R(0) != 18) {
                R(12) = gm_u8(R(12) + 1) & 1; CR0(ctx, R(12));
                if (R(12)) {
                    R(12) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; NV_R(30, gm_u32(R(5) + R(12)));
                    R(10)++; NV_R(29, gm_u32(R(11) + 4)); R(0) = gm_u32(R(30) + 144); NV_R(30, gm_u32(R(30) + 160));
                    gm_set_u32(R(29) + 52, R(4)); gm_set_u32(R(29) + 44, R(0)); gm_set_u32(R(29) + 48, R(30));
                    R(12) = gm_u32(R(5) + R(12)); R(11) = gm_u32(R(11) + 4);
                    R(0) = gm_u32(R(12) + 72); R(12) = gm_u32(R(12) + 68);
                    gm_set_u32(R(11) + 72, R(0)); gm_set_u32(R(11) + 68, R(12));
                }
            }
        }
        ctx->ctr--; if (ctx->ctr) GM_LOOP(); else break;
    } while (1);
}

static void cont_setRest(GM_CTX, gptr self) {
    I2_FN(0x81819000u);
    NV_R(28, self + 971); NV_R(29, 8); NV_R(30, self + 940); R(3) = self + 872;
    do {
        R(28)++; R(4) = gm_u8(R(28)); NV_R(27, R(3) + 4); CMPU(R(4), 1);
        if (R(4) == 1) {
            R(4) = gm_u32(R(3) + 4); R(3) = R(30); R(5) = 0; BL(0x8181904Cu, InsertIntIntoTextBox1_800B3BE0);
        }
        NV_R(29, R(29) - 1); CMPU(R(29), 0); NV_R(30, R(30) + 4); R(3) = R(27);
        if (R(29)) GM_LOOP(); else break;
    } while (1);
}

static void cont_effectContinueInc(GM_CTX, gptr self, uint32_t index, uint32_t value) {
    I2_FN(0x81819080u);
    R(6) = 0x81860000u; R(4) = i2_rotl(index, 2) & 0xFFFFFFFCu; R(6) = gm_u32(R(6) - 300);
    R(3) = self + R(4); R(4) = 0x81850000u; ctx->f[1].d = ctx->ps1[1] = ldfs(base, R(4) - 31040);
    R(4) = 0x43300000u; gm_set_u32(gm_frame_sp + 52, R(6)); R(7) = 0x81850000u; R(3) = gm_u32(R(3) + 844);
    ctx->f[0].u = ld64(base, R(7) - 30552); ctx->f[2].d = ctx->ps1[2] = ldfs(base, R(3) + 76);
    gm_set_u32(gm_frame_sp + 16, R(4)); R(4) = value ^ 0x80000000u; gm_set_u32(gm_frame_sp + 20, R(4));
    ctx->f[0].d *= ctx->f[2].d; R(4) = gm_u32(R(3) + 160); ctx->f[3].u = ld64(base, gm_frame_sp + 16);
    gm_set_u32(gm_frame_sp + 44, R(4)); R(4) = 0x81850000u; ctx->f[1].d = ctx->f[3].d - ctx->f[1].d;
    ctx->f[2].d = ctx->ps1[2] = ldfs(base, R(4) - 31028); ctx->f[0].d *= ctx->f[1].d;
    ctx->f[1].d = ctx->ps1[1] = ldfs(base, R(3) + 144); R(3) = 0x80430000u; R(3) = gm_u16(R(3) - 30926);
    ctx->f[0].d *= ctx->f[2].d; R(4) = 0; ctx->f[0].d = frsp(ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d); CMPU(R(3), 3);
    stfs(base, gm_frame_sp + 40, ctx->f[0].d); gm_set_u32(gm_frame_sp + 48, R(4));
    if (R(3) == 3) {
        NV_R(30, gm_frame_sp + 28); R(4) = gm_frame_sp + 40; R(3) = R(30);
        BL(0x81819128u, CrapUpPositions__FP7Point3dPC7Point3d_800B32E0);
        R(3) = CONT_RES; R(4) = R(3) + 142; R(3) = 0; R(5) = 0; R(6) = R(30); R(7) = 0; R(8) = 0;
        BL(0x8181914Cu, hle_createPlayerEffect__3dEfFiPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
    } else {
        NV_R(30, gm_frame_sp + 40); R(3) = R(30); BL(0x8181915Cu, GetPosForLayoutEffect__FP7Point3db_800B37E0);
        R(3) = CONT_RES + 142; R(4) = 0; R(5) = R(30); R(6) = 0; R(7) = 0;
        BL(0x8181917Cu, hle_createEffect__3mEfFPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
    }
    R(3) = gm_u32(CONT_FRAME); R(4) = gm_u32(gm_frame_sp + 52); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x818191A8u, mfn_81844FCC);
}

static void cont_executeContinueCountUp(GM_CTX, gptr self) {
    I2_FN(0x818191A8u);
    NV_R(30, self); R(3) = 0xCCCC0000u; NV_R(25, R(3) | 0xCCCDu);
    NV_R(26, R(30) + 908); NV_R(27, R(30) + 972); NV_R(28, 8); NV_R(29, 0);
    do {
        R(3) = gm_u8(R(27) + R(29)); CMPU(R(3), 1);
        if (R(3) == 1) {
            R(4) = i2_rotl(R(29), 2) & 0xFFFFFFFCu; R(5) = gm_u32(R(26) + R(4)); CMPS(R(5), 98); R(3) = R(5);
            if ((int32_t)R(5) >= 98) R(3) = 98;
            R(3)++; CMPS(R(5), 9); R(5) = 1; gm_set_u32(R(26) + R(4), R(3));
            if (!CR_BIT(ctx, 0)) {
                do {
                    R(4) = (uint32_t)(((uint64_t)R(3) * R(25)) >> 32); CMPU(R(3), 99);
                    R(3) = i2_rotl(R(4), 29) & 0x1FFFFFFFu; R(5)++;
                    if (CR_BIT(ctx, 1)) { GM_LOOP(); } else break;
                } while (1);
            }
            R(3) = R(30); R(4) = R(29); BL(0x81819240u, mod_fn_2_A860_81819080);
        }
        NV_R(28, R(28) - 1); CMPU(R(28), 0); NV_R(29, R(29) + 1);
        if (R(28)) GM_LOOP(); else break;
    } while (1);
    R(3) = R(30); BL(0x81819258u, mod_fn_2_A630_81818E88);
    R(3) = gm_u32(CONT_SOUND_MANAGER); R(4) = 165; R(5) = 1; BL(0x8181926Cu, hle_startSystemSe__11SndAudioMgrFUiUl);
    R(3) = R(30) + 112; R(4) = 1; R(5) = 0; BL(0x8181927Cu, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
}

static void cont_executeRestCountUp(GM_CTX, gptr self) {
    I2_FN(0x818192A4u);
    R(4) = 2; NV_R(30, self + 112); NV_R(29, self); R(3) = R(30);
    BL(0x818192CCu, hle_isAnimOn__Q23m2d13EmbedLayout_cFi); CMPU(R(3), 0);
    if (R(3) == 0) {
        R(3) = gm_u32(R(29) + 712); CMPS(R(3), 4);
        if ((int32_t)R(3) >= 4) {
            R(4) = CONT_STATE(5032); R(3) = R(29) + 544; BL(0x81819360u, mod_fn_8015FC10_81838420);
        } else {
            R(3) = gm_u32(CONT_SOUND_MANAGER); R(4) = 164; R(5) = 1; BL(0x818192F4u, hle_startSystemSe__11SndAudioMgrFUiUl);
            R(3) = R(29) + 971; R(4) = R(29) + 936; R(5) = 8; ctx->ctr = R(5);
            do {
                R(3)++; R(5) = gm_u8(R(3)); CMPU(R(5), 1); R(5) = R(4) + 4;
                if (CR_BIT(ctx, 2)) { R(6) = gm_u32(R(4) + 4) + 1; gm_set_u32(R(4) + 4, R(6)); }
                R(4) = R(5); ctx->ctr--; if (ctx->ctr) GM_LOOP(); else break;
            } while (1);
            R(3) = R(29); BL(0x81819330u, mod_fn_2_A6C0_81819000);
            R(3) = gm_u32(R(29) + 712) + 1; gm_set_u32(R(29) + 712, R(3));
            R(3) = R(30); R(4) = 2; R(5) = 0; BL(0x8181934Cu, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
        }
    }
}

static void cont_finalizeRestCountUp(GM_CTX, gptr self) {
    I2_FN(0x81819378u);
    R(4) = 0x81850000u; R(5) = 0x81850000u; R(6) = 0x81860000u; R(7) = 0x81860000u;
    NV_R(26, self + 971); R(3) = R(4) + 7564; R(4) = R(5) - 15160; NV_R(22, R(3) - 4); R(4) -= 4;
    NV_R(24, R(7) - 5796); NV_R(25, R(6) - 5764); NV_R(27, 5); NV_R(28, 0x80430000u);
    NV_R(29, 0); NV_R(30, 8); NV_R(23, 0);
    do {
        R(26)++; R(3) = gm_u8(R(26)); NV_R(21, R(4) + 4); CMPU(R(3), 1);
        if (R(3) == 1) {
            R(3) = gm_u32(R(28) - 23416); R(5) = 1; R(4) = gm_u32(R(4) + 4);
            BL(0x8181940Cu, hle_startSystemSe__11SndAudioMgrFUiUl);
        }
        NV_R(30, R(30) - 1); gm_set_u32(R(22) + 4, R(27)); NV_R(22, R(22) + 4);
        gm_set_u32(R(25) + R(23), R(29)); CMPU(R(30), 0); gm_set_u32(R(24) + R(23), R(29));
        NV_R(23, R(23) + 4); R(4) = R(21); if (R(30)) GM_LOOP(); else break;
    } while (1);
}

static void cont_executeEndWait(GM_CTX, gptr self) {
    I2_FN(0x81819468u);
    NV_R(30, self); R(3) = gm_u32(self + 720); CMPU(R(3), 0);
    if (R(3)) {
        R(4) = gm_u32(R(30) + 716); R(3)--; gm_set_u32(R(30) + 720, R(3)); R(3) = R(4) - 1;
        gm_set_u32(R(30) + 716, R(3)); return;
    }
    R(3) = gm_u32(0x80430000u - 23448); R(4) = gm_u32(R(3)); R(4) = gm_u32(R(4) + 32);
    ctx->ctr = R(4); R(4) = 2304; ctx->lr = 0x818194E4u; ppc_call_indirect(ctx, base, ctx->ctr);
    CMPU(R(3), 0); int menuResult = R(3); R(3) = gm_u32(R(30) + 716); CMPU(R(3), 0);
    if (R(3)) {
        if (!menuResult) { R(3)--; GM_LOOP(); gm_set_u32(R(30) + 716, R(3)); return; }
        R(3) = 0; gm_set_u32(R(30) + 716, R(3));
    }
    R(3) = CONT_RES; NV_R(29, 8); NV_R(28, R(3) - 4); NV_R(27, 0x80430000u);
    do {
        R(28) += 4; R(4) = gm_u32(R(28)); R(3) = gm_u32(R(27) - 23416); BL(0x81819534u, CheckIfPlayingSound_80196600);
        CMPU(R(3), 0); if (R(3)) return;
        NV_R(29, R(29) - 1); CMPU(R(29), 0); if (R(29)) GM_LOOP(); else break;
    } while (1);
    R(3) = gm_u8(R(30) + 736); CMPU(R(3), 0);
    if (R(3)) {
        R(3) = 1; R(4) = 0x80990000u; gm_set_u8(R(30) + 727, R(3)); R(3) = R(30) + 544; R(4) += 4584;
    } else {
        R(4) = 0x80990000u; R(3) = R(30) + 544; R(4) += 5160;
    }
    BL(0x8181957Cu, mod_fn_8015FC10_81838420); GM_LOOP();
}

static void cont_finalizeEndWait(GM_CTX, gptr self) {
    I2_FN(0x81819580u);
    R(4) = (uint32_t)-1; NV_R(29, self); R(3) = gm_u32(CONT_SAVE_MANAGER);
    BL(0x818195B0u, hle_mod_getSaveGame__10dSaveMng_cFSc); NV_R(30, R(3));
    R(3) = R(29) + 904; NV_R(28, 8); NV_R(29, 0);
    do {
        R(4) = gm_u8(R(3) + 7); NV_R(27, R(3) + 4); R(3) = R(30); R(5) = (uint32_t)(int8_t)R(4); R(4) = R(29);
        BL(0x818195D8u, hle_mod_fn_800CE310);
        NV_R(28, R(28) - 1); CMPU(R(28), 0); NV_R(29, R(29) + 1); R(3) = R(27);
        if (R(28)) GM_LOOP(); else break;
    } while (1);
}

GM_HLE_VERIFIED_(mod_fn_2_A130, GMV_IGNORE_POLLS, 0, 0) { R(3) = cont_create(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_A260, GMV_IGNORE_POLLS, 0, 0) { R(3) = cont_createLayout(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_A750, GMV_IGNORE_POLLS, 0, 0) { cont_setPlayerInfo(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_A630, GMV_IGNORE_POLLS, 0, 0) { cont_setContinue(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_A4B0, GMV_IGNORE_POLLS, 0, 0) { R(3) = cont_getPaneIdx(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_2_A4E0, GMV_IGNORE_POLLS, 0, 0) { cont_setCardPosition(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_A6C0, GMV_IGNORE_POLLS, 0, 0) { cont_setRest(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_A860, GMV_IGNORE_POLLS, 0, 0) { cont_effectContinueInc(GM_PASS, GM_ARG(0), GM_ARG(1), GM_ARG(2)); }
GM_HLE_VERIFIED_(mod_fn_2_AC70, GMV_IGNORE_POLLS, 0, 0) { cont_executeContinueCountUp(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_AE30, GMV_IGNORE_POLLS, 0, 0) { cont_executeRestCountUp(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_AF30, GMV_IGNORE_POLLS, 0, 0) { cont_finalizeRestCountUp(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_B0F0, GMV_IGNORE_POLLS, 0, 0) { cont_executeEndWait(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_B240, GMV_IGNORE_POLLS, 0, 0) { cont_finalizeEndWait(GM_PASS, GM_ARG(0)); }
