/* gm_d_multi_course.c - dMultiCourseSelect_c: extra eight-player layout panes,
 * player positions, favorite-course display setup and rank-star finalization. */
#include "gm_i2.h"
RT_STATE_FILE

#define MCS_FRAME      (0x81860000u - 300)
#define MCS_RES        0x81850000u
#define MCS_ACTIVE     (0x81860000u - 5828)
#define MCS_INFO       (0x80430000u - 24708)
#define MCS_GAME_FLAG  (0x80430000u - 24704)
#define MCS_SAVE       (0x80430000u - 24512)
#define MCS_POS_TABLE  (0x81850000u - 10880)

static uint32_t mcs_classInit(GM_CTX) {
    I2_FN(0x8181B370u);
    R(3) = 1524; BL(0x8181B388u, hle_AllocateMemoryBlock);
    NV_R(30, R(3)); BL(0x8181B390u, fn_2_2B1E0_80798990);
    R(3) = R(30); return R(3);
}

static uint32_t mcs_createLayoutExtra(GM_CTX, gptr self) {
    I2_FN(0x8181B3A8u);
    NV_R(29, self); BL(0x8181B3C8u, ext_fn_2_2B960_81845408);
    NV_R(30, R(3)); CMPU(R(3), 0);
    if (R(3) != 0) {
        NV_R(28, self + 112); R(3) = MCS_RES; R(5) = self + 1316; R(4) = R(3) + 10824;
        R(3) = R(28); R(6) = 44; BL(0x8181B3F0u, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
        R(3) = MCS_RES; R(5) = self + 1492; R(4) = R(3) + 11000; R(3) = R(28); R(6) = 8;
        NV_R(28, 8); BL(0x8181B40Cu, hle_getTextBoxes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7TextBoxi);
        R(3) = MCS_GAME_FLAG; R(4) = gm_u8(R(3) + 3); R(3) = self + 1312;
        ctx->ctr = R(28); R(4) = i2_rotl(R(4), 26) & 1;
        do {
            R(3) += 4; R(5) = gm_u32(R(3)); R(6) = gm_u8(R(5) + 187);
            R(6) = (R(4) & 1) | (R(6) & ~1u); gm_set_u8(R(5) + 187, R(6));
            if (--ctx->ctr) GM_LOOP(); else break;
        } while (1);
    }
    R(3) = R(30); return R(3);
}

static void mcs_setPlayerPos(GM_CTX, gptr self) {
    I2_FN(0x8181B458u);
    NV_R(27, 8); NV_R(28, 0); NV_R(29, 0); NV_R(30, self);
    R(3) = gm_u32(MCS_FRAME); NV_R(26, self + 1312); gm_set_u32(gm_frame_sp + 16, R(3));
    do {
        R(3) = R(29); BL(0x8181B4B4u, hle_mod_getPlayerIndex__9daPyMng_cF13PLAYER_TYPE_e);
        BL(0x8181B4B8u, hle_mod_PlayerEnterCheck__8dGameComFi);
        R(26) += 4; R(4) = gm_u32(R(26)); NV_R(27, R(27) - 1); NV_R(28, R(28) + R(3));
        CMPU(R(27), 0); R(5) = gm_u8(R(4) + 187); NV_R(29, R(29) + 1);
        R(5) = (R(3) & 1) | (R(5) & ~1u); gm_set_u8(R(4) + 187, R(5));
        if (R(27)) GM_LOOP(); else break;
    } while (1);

    R(4) = MCS_POS_TABLE; R(3) = i2_rotl(R(28), 5) & 0xFFFFFFE0u;
    R(3) = R(4) + R(3); NV_R(27, self + 1316); NV_R(23, self + 1312);
    NV_R(26, 8); NV_R(25, 0); NV_R(24, R(3) - 32); NV_R(29, 0);
    do {
        R(3) = i2_rotl(R(25), 2) & 0xFFFFFFFCu; R(3) = gm_u32(R(24) + R(3));
        NV_R(22, R(23)); NV_R(21, 44); CMPU(R(3), 0); if (R(3) != 0) NV_R(21, R(3));
        R(3) = R(29); NV_R(23, R(22) + 4);
        BL(0x8181B52Cu, hle_mod_getPlayerIndex__9daPyMng_cF13PLAYER_TYPE_e);
        BL(0x8181B530u, hle_mod_PlayerEnterCheck__8dGameComFi); CMPU(R(3), 0);
        if (R(3) != 0) {
            CMPU(R(21), 44);
            if (R(21) != 44) {
                R(3) = i2_rotl(R(21), 2) & 0xFFFFFFFCu; R(3) = gm_u32(R(27) + R(3));
                NV_R(25, R(25) + 1); R(4) = gm_u32(R(22) + 4);
                R(5) = gm_u32(R(3) + 52); gm_set_u32(R(4) + 52, R(5));
                R(5) = gm_u32(R(3) + 48); gm_set_u32(R(4) + 48, R(5));
                R(3) = gm_u32(R(3) + 44); gm_set_u32(R(4) + 44, R(3));
            }
        }
        NV_R(26, R(26) - 1); CMPU(R(26), 0); NV_R(29, R(29) + 1);
        if (R(26)) GM_LOOP(); else break;
    } while (1);

    CMPU(R(28), 5);
    if (R(28) > 5) {
        R(4) = MCS_RES; R(3) = self + 112; R(5) = gm_frame_sp + 12; R(4) += 11032; R(6) = 1;
        BL(0x8181B598u, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
        R(3) = gm_u32(gm_frame_sp + 12); R(4) = 0xC3540000u; gm_set_u32(R(3) + 48, R(4));
    }
    R(3) = gm_u32(MCS_FRAME); R(4) = gm_u32(gm_frame_sp + 16); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x8181B5F4u, mfn_81844FCC);
}

static void mcs_initializeDispWait(GM_CTX, gptr self) {
    uint32_t frame_size = 1888 + (ctx->r[1] & 31);
    GM_FRAME(frame_size); GM_NV_KEEP;
    i2_epi_t i2_epi_ __attribute__((cleanup(i2_epi_end))) = { ctx, ctx->lr };
    gptr oldsp = gm_frame_sp + frame_size;
    gm_set_u32(oldsp + 4, i2_epi_.lr);
    for (uint32_t r = 22; r <= 29; r++) gm_set_u32(oldsp - 40 + 4 * (r - 22), R(r));
    NV_R(29, self); R(3) = gm_u32(MCS_FRAME); NV_R(28, self + 112);
    gm_set_u32(gm_frame_sp + 1844, R(3));
    R(3) = R(28); BL(0x8181B654u, hle_disableAllAnimations__Q23m2d13EmbedLayout_cFv);
    static const uint8_t reverse[] = { 3, 4, 5, 6, 1, 0, 28 };
    static const uint32_t return_addr[] = { 0x8181B664u, 0x8181B674u, 0x8181B684u, 0x8181B694u,
                                           0x8181B6A4u, 0x8181B6B4u, 0x8181B6C4u };
    for (uint32_t i = 0; i < 7; i++) {
        R(3) = R(28); R(4) = reverse[i]; R(5) = 0;
        BL(return_addr[i], hle_resetAnim__Q23m2d13EmbedLayout_cFib);
    }
    R(3) = R(28); R(4) = 30; BL(0x8181B6D0u, hle_enableLoopAnim__Q23m2d13EmbedLayout_cFi);

    R(3) = gm_frame_sp + 1812; R(4) = 0; R(5) = 32; BL(0x8181B6E0u, mod_memset_81844D68);
    R(4) = 8; ctx->ctr = R(4); R(4) = MCS_ACTIVE - 4; R(3) = gm_frame_sp + 1808;
    do {
        R(4) += 4; R(5) = gm_u32(R(4)); R(3) += 4; gm_set_u32(R(3), R(5));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    NV_R(28, gm_u32(MCS_SAVE)); R(3) = gm_u8(R(28) + 38); NV_R(27, (uint32_t)(int8_t)R(3));
    R(3) = R(28); R(4) = R(27); BL(0x8181B720u, hle_mod_getSaveGame__10dSaveMng_cFSc);
    BL(0x8181B724u, hle_mod_fn_800CDED0);
    R(3) = R(28); R(4) = R(27); BL(0x8181B730u, hle_mod_fn_800E1840);
    R(4) = 8; ctx->ctr = R(4); R(4) = MCS_ACTIVE - 4; R(3) = gm_frame_sp + 1808;
    do {
        R(3) += 4; R(5) = gm_u32(R(3)); R(4) += 4; gm_set_u32(R(4), R(5));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);

    R(3) = self + 1072; R(4) = 10; R(5) = 42; R(6) = 0; ctx->ctr = R(4);
    do {
        R(3) += 16; gm_set_u32(R(3), R(4)); gm_set_u32(R(3) + 4, R(5)); gm_set_u16(R(3) + 8, R(6));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    NV_R(24, gm_u32(MCS_INFO)); R(3) = gm_u32(MCS_SAVE); NV_R(28, gm_frame_sp + 96);
    R(4) = gm_u32(R(24) + 996); R(5) = gm_u32(R(24) + 1000);
    gm_set_u32(self + 1280, R(4)); R(4) = R(3) + 32; gm_set_u32(self + 1268, R(5));
    R(3) = R(28); R(5) = 1696; BL(0x8181B7ACu, mod_memcpy_81844C38);

    NV_R(27, 0); NV_R(23, MCS_GAME_FLAG);
    do {
        NV_R(22, 38); NV_R(26, R(27) & 0xFF); NV_R(25, 0);
        do {
            R(3) = gm_u8(R(23) + 3); R(5) = R(25) & 0xFF; R(4) = R(26); R(3) &= 0x20;
            CR0(ctx, R(3)); R(3) = R(28);
            if (CR_BIT(ctx, 2)) BL(0x8181B7E0u, hle_mod_fn_800CE640);
            else BL(0x8181B7E8u, hle_mod_fn_800CE600);
            R(6) = R(3); CMPU(R(3), 0);
            if (R(3) != 0) {
                R(3) = self; R(4) = R(27); R(5) = R(25); BL(0x8181B804u, fn_2_2C680_80799E30);
            }
            NV_R(22, R(22) - 1); CMPU(R(22), 0); NV_R(25, R(25) + 1);
            if (R(22)) GM_LOOP(); else break;
        } while (1);
        NV_R(27, R(27) + 1); CMPU(R(27), 9);
        if (R(27) != 9) GM_LOOP(); else break;
    } while (1);

    R(3) = gm_frame_sp + 16; R(4) = 0; R(5) = 80; NV_R(28, 0); BL(0x8181B834u, mod_memset_81844D68);
    R(3) = gm_u32(MCS_GAME_FLAG); R(5) = gm_u32(self + 1280); R(3) &= 0x40; CR0(ctx, R(3));
    R(3) = gm_u32(self + 1268); uint32_t coin_battle = !CR_BIT(ctx, 2);
    if (!coin_battle) {
        R(4) = (uint32_t)((int32_t)R(5) * 80); R(3) = i2_rotl(R(3), 3) & 0xFFFFFFF8u;
        R(4) = R(24) + R(4) + R(3); R(3) = gm_u8(R(4) + 1904); R(4) = gm_u8(R(4) + 1905);
        R(6) = R(24) + 2696; R(7) = gm_frame_sp + 8; R(8) = 10; ctx->ctr = R(8); R(8) = 2602;
        do {
            R(6) += 8; R(9) = gm_u16(R(6)); R(7) += 8; gm_set_u16(R(7), R(9));
            R(9) = gm_u32(R(6) + 4); gm_set_u16(R(6), R(8)); gm_set_u32(R(7) + 4, R(9));
            gm_set_u32(R(6) + 4, R(28)); if (--ctx->ctr) GM_LOOP(); else break;
        } while (1);
    } else {
        R(4) = (uint32_t)((int32_t)R(5) * 80); R(3) = i2_rotl(R(3), 3) & 0xFFFFFFF8u;
        R(4) = R(24) + R(4) + R(3); R(3) = gm_u8(R(4) + 1024); R(4) = gm_u8(R(4) + 1025);
        R(6) = gm_frame_sp + 8; R(7) = R(24) + 1816; R(8) = 10; ctx->ctr = R(8); R(8) = 2602;
        do {
            R(7) += 8; R(9) = gm_u16(R(7)); R(6) += 8; gm_set_u16(R(6), R(9));
            R(9) = gm_u32(R(7) + 4); gm_set_u16(R(7), R(8)); gm_set_u32(R(6) + 4, R(9));
            gm_set_u32(R(7) + 4, R(28)); if (--ctx->ctr) GM_LOOP(); else break;
        } while (1);
    }

    if (R(5) == 10) {
        R(6) = 10; R(5) = self + 1072; ctx->ctr = R(6); R(6) = 0;
        do {
            R(5) += 16; R(7) = gm_u32(R(5));
            if (R(7) == R(3)) {
                R(7) = gm_u32(R(5) + 4);
                if (R(7) == R(4)) gm_set_u32(self + 1268, R(6));
            }
            R(6)++; if (--ctx->ctr) GM_LOOP(); else break;
        } while (1);
    }

    R(3) = self + 1088; R(4) = 0; R(5) = gm_frame_sp + 8; R(6) = 10; R(7) = 0;
    do {
        R(9) = i2_rotl(R(7), 4) & 0xFFFFFFF0u; R(8) = R(3) + R(9);
        R(9) = gm_u32(R(8)); R(11) = R(5); R(10) = gm_u32(R(8) + 4); gm_set_u32(R(8) + 12, R(4));
        ctx->ctr = R(6);
        do {
            R(11) += 8; R(12) = gm_u8(R(11));
            if (R(9) == R(12)) {
                R(12) = gm_u8(R(11) + 1);
                if (R(10) == R(12)) {
                    R(12) = gm_u32(R(11) + 4); gm_set_u32(R(8) + 12, R(12));
                }
            }
            if (--ctx->ctr) GM_LOOP(); else break;
        } while (1);
        R(7)++; if (R(7) < 10) GM_LOOP(); else break;
    } while (1);

    R(4) = R(24) + (coin_battle ? 1024 : 1904); R(3) = self + 1072; R(4) -= 8; R(5) = 10; ctx->ctr = R(5);
    do {
        R(3) += 16; R(5) = gm_u32(R(3)); R(4) += 8; gm_set_u8(R(4), R(5));
        R(5) = gm_u32(R(3) + 4); R(6) = gm_u32(R(3) + 12);
        gm_set_u8(R(4) + 1, R(5)); gm_set_u32(R(4) + 4, R(6));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    R(3) = self; R(4) = 0; R(5) = 20; BL(0x8181B9C4u, fn_2_2C710_80799EC0);
    R(3) = gm_u32(MCS_FRAME); R(4) = gm_u32(gm_frame_sp + 1844); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x8181BA1Cu, mfn_81844FCC);
}

static void mcs_finalizeDispWait(GM_CTX, gptr self) {
    I2_FN(0x8181BA1Cu);
    NV_R(27, 0); NV_R(28, 8); NV_R(29, gm_frame_sp + 12); NV_R(30, self);
    R(3) = gm_u32(MCS_FRAME); NV_R(26, self + 1488); gm_set_u32(gm_frame_sp + 16, R(3));
    R(3) = gm_u32(MCS_INFO); NV_R(25, R(3) + 3000);
    do {
        CMPU(R(27), 4); R(3) = R(27) < 4 ? R(25) - 1996 : R(25); R(3) = gm_u32(R(3));
        R(5) = 0; R(26) += 4; R(4) = gm_u32(R(26)); gm_set_u32(gm_frame_sp + 12, R(3));
        R(3) = R(29); BL(0x8181BA98u, InsertIntIntoTextBox1_800B3BE0);
        NV_R(28, R(28) - 1); NV_R(27, R(27) + 1); CMPU(R(28), 0); NV_R(25, R(25) + 4);
        if (R(28)) GM_LOOP(); else break;
    } while (1);
    R(3) = self; R(4) = 0; R(5) = 20; BL(0x8181BABCu, fn_2_2C710_80799EC0);
    R(3) = gm_u32(MCS_FRAME); R(4) = gm_u32(gm_frame_sp + 16); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x8181BAFCu, mfn_81844FCC);
}

GM_HLE_VERIFIED_(mod_fn_2_2B1B0, GMV_IGNORE_POLLS, 0, 0) { R(3) = mcs_classInit(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_2_2B960, GMV_IGNORE_POLLS, 0, 0) { R(3) = mcs_createLayoutExtra(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_2BFC0, GMV_IGNORE_POLLS, 0, 0) { mcs_setPlayerPos(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_2C7F0, GMV_IGNORE_POLLS, 0, 0) { mcs_initializeDispWait(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_2D030, GMV_IGNORE_POLLS, 0, 0) { mcs_finalizeDispWait(GM_PASS, GM_ARG(0)); }
