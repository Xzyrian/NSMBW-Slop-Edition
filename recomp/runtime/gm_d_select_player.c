/* gm_d_select_player.c - dSelectPlayer_c: player-select layout, cursor,
 * animation states and start-member input dispatch (track B, gm_i2.h). */
#include "gm_i2.h"
RT_STATE_FILE

#define SP_FRAME        (0x81860000u - 300)
#define SP_RES          (0x81850000u - 8748)
#define SP_STATE(n)     (0x80990000u + (n))
#define SP_SOUND_MANAGER (0x80430000u - 23416)

static uint32_t sp_createLayout(GM_CTX, gptr self) {
    I2_FN(0x8181E22Cu);
    NV_R(26, 0x81860000u); NV_R(30, self); R(4) = gm_u32(SP_FRAME);
    gm_set_u32(gm_frame_sp + 172, R(4)); R(3) = gm_u8(self + 616); CMPU(R(3), 0);
    if (R(3) == 0) {
        NV_R(29, self + 172); NV_R(28, SP_RES);
        R(4) = R(28) + 730; R(3) = R(29); R(5) = 0; NV_R(25, 0);
        BL(0x8181E290u, hle_loadArc__Q23m2d13EmbedLayout_cFPCcb);
        R(4) = R(28) + 633; R(3) = R(29); R(5) = 0; BL(0x8181E2A0u, hle_fn_800C8A10);
        NV_R(27, gm_frame_sp + 20); R(4) = 0x81850000u + 11352; R(3) = R(27); R(5) = 32;
        BL(0x8181E2B8u, mod_memcpy_81844C38);
        R(3) = R(29); R(4) = R(27); R(5) = 8; NV_R(24, 8);
        BL(0x8181E2CCu, hle_loadAnimations__Q23m2d13EmbedLayout_cFPPCci);
        NV_R(27, gm_frame_sp + 20); R(4) = 0x81850000u + 11384; R(3) = R(27); R(5) = 152;
        BL(0x8181E2E4u, mod_memcpy_81844C38);
        R(5) = R(28) + 72; R(3) = R(29); R(4) = R(27); R(6) = 38;
        BL(0x8181E2F8u, hle_loadGroups__Q23m2d13EmbedLayout_cFPPCcPCii);
        NV_R(27, gm_frame_sp + 20); R(4) = 0x81850000u + 11536; R(3) = R(27); R(5) = 44;
        BL(0x8181E310u, mod_memcpy_81844C38);
        R(5) = R(30) + 640; R(3) = R(29); R(4) = R(27); R(6) = 11;
        BL(0x8181E324u, hle_getPictures__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7Picturei);
        R(3) = R(28) + 586; gm_set_u32(gm_frame_sp + 20, R(3));
        R(3) = R(28) + 616; gm_set_u32(gm_frame_sp + 24, R(3));
        R(5) = R(30) + 608; R(4) = gm_frame_sp + 20; R(3) = R(29); R(6) = 2;
        BL(0x8181E348u, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
        NV_R(27, gm_frame_sp + 20); R(4) = 0x81850000u + 11580; R(3) = R(27); R(5) = 40;
        BL(0x8181E360u, mod_memcpy_81844C38);
        R(5) = R(28) + 32; R(3) = R(29); R(4) = R(27); R(6) = 107; R(7) = 10;
        BL(0x8181E378u, hle_setLangStrings__Q23m2d13EmbedLayout_cFPPCcPCiii);
        NV_R(27, gm_frame_sp + 20); R(4) = 0x81850000u + 11620; R(3) = R(27); R(5) = 28;
        BL(0x8181E390u, mod_memcpy_81844C38);
        R(5) = R(28) + 4; R(3) = R(29); R(4) = R(27); R(6) = 108; R(7) = 7;
        BL(0x8181E3A8u, hle_setLangStrings__Q23m2d13EmbedLayout_cFPPCcPCiii);
        R(3) = R(28) + 378; gm_set_u32(gm_frame_sp + 20, R(3));
        R(4) = gm_frame_sp + 20; R(3) = R(29); R(5) = R(28); R(6) = 2; R(7) = 1;
        BL(0x8181E3C8u, hle_setLangStrings__Q23m2d13EmbedLayout_cFPPCcPCiii);
        gm_set_u8(R(30) + 184, R(24)); gm_set_u8(R(30) + 684, R(25));
    }
    R(3) = gm_u32(SP_FRAME); R(4) = gm_u32(gm_frame_sp + 172); CMPU(R(3), R(4));
    if (R(3) == R(4)) return 1;
    BL(0x8181E414u, mfn_81844FCC); return R(3);
}

static void sp_startWait(GM_CTX, gptr self) {
    I2_FN(0x8181E414u);
    R(4) = gm_u8(self + 618); CMPU(R(4), 0);
    if (R(4) != 0) {
        R(4) = gm_u32(self + 608); R(6) = 0; gm_set_u16(self + 618, 0); gm_set_u32(self + 624, 0);
        R(5) = gm_u8(self + 684) ^ 1; R(6) = gm_u8(R(4) + 187) & 0xFE;
        gm_set_u8(R(4) + 187, R(6) | (R(5) & 1));
        R(4) = gm_u32(self + 612); R(6) = gm_u8(self + 684); R(5) = gm_u8(R(4) + 187) & 0xFE;
        gm_set_u8(R(4) + 187, R(5) | (R(6) & 1));
        R(4) = gm_u8(self + 684); CMPU(R(4), 1);
        if (R(4) == 1) {
            R(4) = gm_u32(self + 620); CMPU(R(4), 0);
            if (R(4) == 0) { R(4) = 1; gm_set_u32(self + 620, R(4)); }
        }
        R(4) = SP_STATE(21512); R(3) = self + 136; BL(0x8181E49Cu, mod_fn_8015FC10_81838420);
    }
}

static void sp_initializeOnStage(GM_CTX, gptr self) {
    I2_FN(0x8181E4ACu);
    NV_R(30, self + 172); R(3) = R(30); BL(0x8181E4D0u, hle_disableAllAnimations__Q23m2d13EmbedLayout_cFv);
    NV_R(28, 13); NV_R(29, 0);
    do {
        R(3) = R(30); R(4) = R(29); R(5) = 0; BL(0x8181E4E8u, hle_resetAnim__Q23m2d13EmbedLayout_cFib);
        NV_R(28, R(28) - 1); CMPU(R(28), 0); NV_R(29, R(29) + 1);
        if (R(28)) GM_LOOP(); else break;
    } while (1);
    R(3) = R(30); R(4) = 0; R(5) = 0; BL(0x8181E508u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
}

static void sp_initializeButtonChange(GM_CTX, gptr self) {
    I2_FN(0x8181E524u);
    NV_R(30, self); R(3) = gm_u32(self + 628); NV_R(29, self + 172);
    CMPS(R(3), 0); gm_set_u32(self + 632, R(3));
    if ((int32_t)R(3) >= 0) {
        R(4) = R(3) + 22; R(3) = R(29); R(5) = 0; gm_set_u32(R(30) + 632, R(4));
        BL(0x8181E564u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
        R(3) = gm_u32(SP_SOUND_MANAGER); R(4) = 120; R(5) = 1;
        BL(0x8181E578u, hle_startSystemSe__11SndAudioMgrFUiUl);
    }
    R(4) = gm_u8(R(30) + 684); R(3) = gm_u32(R(30) + 620); CMPU(R(4), 0); R(4) = 9;
    if (CR_BIT(ctx, 2)) R(4) = 2;
    CMPS(R(3), 4); if ((int32_t)R(3) >= 4) R(4) = 2;
    R(4) += R(3); R(3) = R(29); R(5) = 0; gm_set_u32(R(30) + 628, R(4));
    BL(0x8181E5B0u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
}

static void sp_executeButtonChange(GM_CTX, gptr self) {
    I2_FN(0x8181E5C8u);
    R(4) = (uint32_t)-1; NV_R(30, self); R(3) = self + 172;
    BL(0x8181E5E8u, hle_isAnimOn__Q23m2d13EmbedLayout_cFi); CMPU(R(3), 0);
    if (R(3)) {
        R(3) = gm_u8(R(30) + 684); CMPU(R(3), 0);
        R(4) = SP_STATE(R(3) ? 21704 : 21768); R(3) = R(30) + 136;
        BL(0x8181E618u, mod_fn_8015FC10_81838420);
    }
}

static void sp_initializeStartMember(GM_CTX, gptr self) {
    I2_FN(0x8181E62Cu);
    R(5) = 0; R(4) = gm_u32(self + 620); R(4) = i2_rotl(R(4), 2) & 0xFFFFFFFCu;
    R(3) = gm_u32(self + R(4) + 640); R(4) = 0;
    BL(0x8181E654u, SelectCursorSetup__8dGameComFPQ34nw4r3lyt4Paneib_800B44D0);
}

static void sp_executeStartMember(GM_CTX, gptr self) {
    I2_FN(0x8181E664u);
    NV_R(30, self); R(4) = gm_u32(0x80430000u - 23452); R(5) = gm_u32(0x80430000u - 24752);
    R(4) = i2_rotl(R(4), 2) & 0xFFFFFFFCu; R(3) = gm_u32(self + 620);
    R(5) = gm_u32(R(5) + R(4) + 4); R(4) = 7; cr_cmp_s(ctx, 1, R(3), 3);
    if (!CR_BIT(ctx, 5)) R(4) = 3;
    R(5) = gm_u32(R(5) + 28); R(6) = R(5) & 8; CR0(ctx, R(6));
    if (!R(6)) {
        R(6) = R(5) & 4; CR0(ctx, R(6));
        if (R(6)) {
            CMPS(R(3), R(4)); if ((int32_t)R(3) < (int32_t)R(4)) R(4) = R(3) + 1;
        } else {
            if (CR_BIT(ctx, 5)) goto pageCheck;
            R(4) = R(5) & 1; CR0(ctx, R(4));
            if (CR_BIT(ctx, 2)) goto pageCheck;
            R(4) = R(3) + 4; goto store;
        }
    } else {
        R(4) = CR_BIT(ctx, 5) ? 1 : 0; R(4) = i2_rotl(R(4), 2) & 0xFFFFFFFCu;
        CMPS(R(3), R(4)); if ((int32_t)R(3) > (int32_t)R(4)) R(4) = R(3) - 1;
    }
    CMPU(R(4), R(3)); if (R(4) != R(3)) goto store;
    goto confirm;

pageCheck:
    CMPS(R(3), 4);
    if ((int32_t)R(3) < 4) { GM_LOOP(); goto confirm; }
    R(4) = R(5) & 2; CR0(ctx, R(4)); R(4) = R(3);
    if (!CR_BIT(ctx, 2)) R(4) = R(3) - 4;
    GM_LOOP(); CMPU(R(4), R(3)); if (R(4) != R(3)) goto store;

confirm:
    R(3) = gm_u32(0x80430000u - 23448); R(4) = gm_u32(R(3)); R(4) = gm_u32(R(4) + 24);
    ctx->ctr = R(4); R(4) = 2304; ctx->lr = 0x8181E720u; ppc_call_indirect(ctx, base, ctx->ctr);
    CMPU(R(3), 0);
    if (R(3)) {
        R(3) = 1; gm_set_u32(R(30) + 624, R(3)); R(4) = SP_STATE(21832);
    } else {
        R(3) = 0; BL(0x8181E76Cu, mod__Z47CheckIfMenuShouldBeCancelledForSpecifiedWiimotei_8180B0C8);
        CMPU(R(3), 0);
        if (R(3) == 0) { GM_LOOP(); return; }
        R(3) = (uint32_t)-1; gm_set_u32(R(30) + 624, R(3));
        R(3) = gm_u32(SP_SOUND_MANAGER); R(4) = 122; R(5) = 1;
        BL(0x8181E790u, hle_startSystemSe__11SndAudioMgrFUiUl);
        R(4) = SP_STATE(21896); GM_LOOP();
    }
    R(3) = R(30) + 136; BL(0x8181E750u, mod_fn_8015FC10_81838420);
    return;

store:
    gm_set_u32(R(30) + 620, R(4)); R(4) = SP_STATE(21640); R(3) = R(30) + 136;
    BL(0x8181E750u, mod_fn_8015FC10_81838420);
}

static void sp_initializeMultiStartMember(GM_CTX, gptr self) {
    I2_FN(0x8181E7B8u);
    R(4) = gm_u32(self + 620); R(5) = i2_rotl(R(4), 2) & 0xFFFFFFFCu;
    CMPS(R(4), 4); R(3) = self + R(5) + ((int32_t)R(4) > 4 ? 640 : 672);
    R(3) = gm_u32(R(3)); R(4) = 0; R(5) = 0;
    BL(0x8181E7F4u, SelectCursorSetup__8dGameComFPQ34nw4r3lyt4Paneib_800B44D0);
}

static void sp_initializeStartMemberButton(GM_CTX, gptr self) {
    I2_FN(0x8181E804u);
    NV_R(30, self); R(3) = gm_u32(SP_SOUND_MANAGER); R(4) = 121; R(5) = 1;
    BL(0x8181E82Cu, hle_startSystemSe__11SndAudioMgrFUiUl);
    R(3) = gm_u32(0x80430000u - 23864); R(4) = 0; BL(0x8181E83Cu, hle_HideSelectCursor);
    R(3) = gm_u8(R(30) + 684); R(5) = 21; R(4) = gm_u32(R(30) + 620); CMPU(R(3), 0);
    if (R(3) == 0) R(5) = 13;
    CMPS(R(4), 4); R(3) = R(30) + 172; if ((int32_t)R(4) >= 4) R(5) = 13;
    R(4) += R(5); R(5) = 0; BL(0x8181E870u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
}

static void sp_initializeExit(GM_CTX, gptr self) {
    I2_FN(0x8181E884u);
    NV_R(30, self + 172); NV_R(29, self); R(3) = R(30); R(4) = 35; R(5) = 0;
    BL(0x8181E8B0u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
    R(3) = gm_u32(R(29) + 624); R(4) = 36; CMPU(R(3), 1); if (R(3) != 1) R(4) = 37;
    R(3) = R(30); R(5) = 0; BL(0x8181E8D0u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
}

static void sp_executeExit(GM_CTX, gptr self) {
    I2_FN(0x8181E8E8u);
    NV_R(29, self + 172); NV_R(30, self); R(3) = R(29); R(4) = 35;
    BL(0x8181E910u, hle_isAnimOn__Q23m2d13EmbedLayout_cFi); CMPU(R(3), 0);
    if (!R(3)) return;
    R(3) = R(29); R(4) = 36; BL(0x8181E924u, hle_isAnimOn__Q23m2d13EmbedLayout_cFi); CMPU(R(3), 0);
    if (!R(3)) return;
    R(3) = R(29); R(4) = 37; BL(0x8181E938u, hle_isAnimOn__Q23m2d13EmbedLayout_cFi); CMPU(R(3), 0);
    if (!R(3)) return;
    R(4) = SP_STATE(21448); R(3) = R(30) + 136; BL(0x8181E950u, mod_fn_8015FC10_81838420);
}

GM_HLE_VERIFIED_(mod_fn_2_3E9D0, GMV_IGNORE_POLLS, 0, 0) { R(3) = sp_createLayout(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3EC30, GMV_IGNORE_POLLS, 0, 0) { sp_startWait(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3ED00, GMV_IGNORE_POLLS, 0, 0) { sp_initializeOnStage(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3EE70, GMV_IGNORE_POLLS, 0, 0) { sp_initializeButtonChange(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3EF40, GMV_IGNORE_POLLS, 0, 0) { sp_executeButtonChange(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3EFE0, GMV_IGNORE_POLLS, 0, 0) { sp_initializeStartMember(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3F000, GMV_IGNORE_POLLS, 0, 0) { sp_executeStartMember(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3F1C0, GMV_IGNORE_POLLS, 0, 0) { sp_initializeMultiStartMember(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3F330, GMV_IGNORE_POLLS, 0, 0) { sp_initializeStartMemberButton(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3F430, GMV_IGNORE_POLLS, 0, 0) { sp_initializeExit(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_3F4A0, GMV_IGNORE_POLLS, 0, 0) { sp_executeExit(GM_PASS, GM_ARG(0)); }
