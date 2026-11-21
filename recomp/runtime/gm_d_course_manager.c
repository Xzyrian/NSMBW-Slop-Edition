/* gm_d_course_manager.c - dCourseSelectManager_c: course-select execution gate,
 * continue handling, key dispatch, save / pairing states and power-up queries.
 * Objects and state machines remain in big-endian guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define CSM_ACTIVE       (0x81860000u - 5828)
#define CSM_REST_VALUES  (0x81850000u + 7564)
#define CSM_STATE_BASE   (0x809A0000u + 9096)
#define CSM_STATE_END    (0x809A0000u + 9320)
#define CSM_SOUND_MANAGER (0x80430000u - 23416)
#define CSM_SOUND_GLOBAL  (0x80430000u - 23384)

static void csm_state(GM_CTX, gptr layout, uint32_t state, uint32_t ra) {
    R(3) = layout; R(4) = state; R(12) = gm_u32(layout);
    R(12) = gm_u32(R(12) + 24); ctx->ctr = R(12); ctx->lr = ra;
    ppc_call_indirect(ctx, base, ctx->ctr);
}

static uint32_t csm_preExecute(GM_CTX, gptr self) {
    I2_FN(0x8181493Cu);
    NV_R(30, self); BL(0x81814954u, hle_beforeExecute__7dBase_cFv);
    CMPU(R(3), 0); R(3) = 0;
    if (CR_BIT(ctx, 2)) return R(3);
    R(4) = gm_u32(0x80430000u - 24160); CMPU(R(4), 0);
    if (CR_BIT(ctx, 2)) return R(3);
    R(4) = self + 1388; ctx->ctr = 8;
    do {
        R(4) += 4; R(5) = gm_u32(R(4)); CMPU(R(5), 0);
        if (CR_BIT(ctx, 2)) return R(3);
        R(5) = gm_u8(R(5) + 608); CMPU(R(5), 0);
        if (CR_BIT(ctx, 2)) return R(3);
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    R(3) = (uint32_t)-1; BL(0x818149A0u, isGameStop__8dGameComFUl_800B3B50);
    R(3) ^= 1; return R(3);
}

static void csm_continueCheck(GM_CTX, gptr self) {
    I2_FN(0x818149B8u);
    R(4) = CSM_REST_VALUES - 4; ctx->ctr = 8;
    for (;;) {
        R(4) += 4; R(5) = gm_u32(R(4)); CMPU(R(5), 0);
        if (R(5) == 0) { R(4) = CSM_STATE_BASE + 160; break; }
        if (--ctx->ctr) GM_LOOP();
        else {
            R(4) = 0; gm_set_u8(self + 1345, R(4)); R(4) = CSM_STATE_END;
            break;
        }
    }
    R(3) = self + 136; BL(0x81814A0Cu, mod_fn_8015FC10_81838420);
}

static void csm_continueEndWait(GM_CTX, gptr self) {
    I2_FN(0x81814A1Cu);
    NV_R(30, self); R(3) = gm_u32(self + 1324); R(4) = gm_u8(R(3) + 727);
    CMPU(R(4), 1);
    if (R(4) == 1) {
        NV_R(29, 0); gm_set_u16(R(3) + 725, 0); R(4) = 0; gm_set_u8(R(3) + 736, 0);
        R(3) += 112; R(5) = 0; BL(0x81814A70u, hle_resetAnim__Q23m2d13EmbedLayout_cFib);
        NV_R(28, 8); NV_R(27, 940); NV_R(26, CSM_ACTIVE); NV_R(25, CSM_REST_VALUES);
        do {
            R(3) = R(29); BL(0x81814A90u, hle_mod_getPlayerIndex__9daPyMng_cF13PLAYER_TYPE_e);
            R(4) = gm_u32(R(30) + 1324); R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu;
            R(3) = gm_u32(R(26) + R(3)); NV_R(28, R(28) - 1);
            R(4) = gm_u32(R(4) + R(27)); NV_R(29, R(29) + 1); CMPU(R(28), 0);
            R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; NV_R(27, R(27) + 4);
            gm_set_u32(R(25) + R(3), R(4));
            if (R(28)) GM_LOOP(); else break;
        } while (1);
        R(4) = CSM_STATE_END; R(3) = R(30) + 136;
        BL(0x81814ACCu, mod_fn_8015FC10_81838420);
        R(3) = 1; gm_set_u8(R(30) + 1302, R(3));
    }
}

static void csm_keyWait(GM_CTX, gptr self) {
    I2_FN(0x81814AFCu);
    R(11) = gm_frame_sp + 32; BL(0x81814B10u, __save_gpr_entry_802DCD70);
    R(0) = gm_u8(self + 1345); NV_R(31, CSM_STATE_BASE); NV_R(30, self); CMPS(R(0), 0);
    if (R(0) != 0) {
        csm_state(GM_PASS, self + 112, CSM_STATE_BASE + 96, 0x81814B3Cu);
    } else {
        R(0) = gm_u8(self + 1346); CMPS(R(0), 0);
        if (R(0) != 0) {
            R(0) = 0; gm_set_u8(self + 1341, R(0)); R(3) = gm_u32(CSM_SOUND_GLOBAL); R(4) = 1;
            BL(0x81814B64u, fn_8019CA00);
            csm_state(GM_PASS, R(30) + 112, CSM_STATE_BASE + 608, 0x81814B7Cu);
        } else {
            R(0) = gm_u8(self + 1348); CMPS(R(0), 0);
            if (R(0) != 0) {
                csm_state(GM_PASS, self + 112, CSM_STATE_BASE + 1824, 0x81814BA0u);
            } else {
                R(0) = gm_u8(self + 1342); CMPS(R(0), 0);
                if (R(0) != 0) {
                    R(4) = gm_u32(self + 172); R(5) = 1; R(0) = 0;
                    gm_set_u8(R(4) + 625, R(5)); R(4) = 124; R(5) = 1;
                    R(7) = gm_u32(self + 172); R(8) = gm_u32(self + 1360);
                    gm_set_u32(R(7) + 616, R(8)); R(3) = gm_u32(self + 172);
                    gm_set_u8(R(3) + 627, R(0)); R(3) = gm_u32(CSM_SOUND_MANAGER);
                    BL(0x81814BE8u, hle_startSystemSe__11SndAudioMgrFUiUl);
                    R(3) = gm_u32(CSM_SOUND_GLOBAL); R(4) = 2; BL(0x81814BF8u, fn_8019CA00);
                    R(3) = R(30); BL(0x81814C00u, fn_2_1C39D0_80931180);
                    R(3) = R(30); BL(0x81814C08u, fn_2_1C3950_80931100);
                    csm_state(GM_PASS, R(30) + 112, CSM_STATE_BASE + 288, 0x81814C20u);
                } else {
                    R(0) = gm_u8(self + 1343); CMPS(R(0), 0);
                    if (R(0) != 0) {
                        csm_state(GM_PASS, self + 112, CSM_STATE_BASE + 1376, 0x81814C44u);
                    } else {
                        R(0) = gm_u8(self + 1351); CMPS(R(0), 0);
                        if (R(0) != 0) {
                            csm_state(GM_PASS, self + 112, CSM_STATE_BASE + 2016, 0x81814C68u);
                        } else {
                            R(0) = gm_u8(self + 1352); CMPS(R(0), 0);
                            if (R(0) != 0) {
                                csm_state(GM_PASS, self + 112, CSM_STATE_BASE + 416, 0x81814C8Cu);
                            } else {
                                R(0) = gm_u8(self + 1357); CMPS(R(0), 0);
                                if (R(0) != 0) {
                                    csm_state(GM_PASS, self + 112, CSM_STATE_BASE + 2208, 0x81814CB0u);
                                } else {
                                    NV_R(28, CSM_ACTIVE); NV_R(31, CSM_ACTIVE + 32);
                                    NV_R(27, self); NV_R(26, 0); NV_R(29, 0);
                                    do {
                                        R(3) = R(30) + R(26); R(0) = gm_u8(R(3) + 1353); CMPS(R(0), 0);
                                        if (R(0) != 0) {
                                            gm_set_u8(R(3) + 1353, R(29)); R(3) = R(26);
                                            BL(0x81814CECu, hle_mod_PlayerEnterCheck__8dGameComFi); CMPS(R(3), 0);
                                            if ((int32_t)R(3) != 0) {
                                                R(0) = gm_u32(R(28)); R(4) = gm_u32(R(27) + 1424);
                                                R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
                                                gm_set_u32(R(31) + R(0), R(4)); R(3) = gm_u32(R(30) + R(0) + 1392);
                                                BL(0x81814D10u, fn_2_159650_808C6E00);
                                            }
                                        }
                                        NV_R(26, R(26) + 1); NV_R(27, R(27) + 4); CMPS(R(26), 8);
                                        NV_R(28, R(28) + 4);
                                        if ((int32_t)R(26) < 8) GM_LOOP(); else break;
                                    } while (1);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    R(11) = gm_frame_sp + 32; BL(0x81814D2Cu, __restore_gpr_entry_802DCDBC);
}

static void csm_stockItemSelectWait(GM_CTX, gptr self) {
    I2_FN(0x81814D3Cu);
    R(4) = gm_u32(self + 180); R(4) = gm_u8(R(4) + 2269); CMPU(R(4), 0);
    if (R(4) == 0) {
        R(4) = self + 1388; ctx->ctr = 8; R(5) = 1;
        do {
            R(4) += 4; R(6) = gm_u32(R(4)); gm_set_u8(R(6) + 617, R(5));
            if (--ctx->ctr) GM_LOOP(); else break;
        } while (1);
        R(4) = gm_u32(self + 172); R(5) = 0; R(3) = self + 136;
        gm_set_u8(R(4) + 627, R(5)); R(4) = CSM_STATE_END;
        BL(0x81814D90u, mod_fn_8015FC10_81838420);
    }
}

static void csm_initializeInterruptSave(GM_CTX, gptr self) {
    I2_FN(0x81814DA0u); R(3) = self; BL(0x81814DB0u, fn_2_1C2850_80930000);
}

static void csm_executeInterruptSave(GM_CTX, gptr self) {
    I2_FN(0x81814DC0u); R(3) = self; BL(0x81814DD0u, fn_2_1C2890_80930040);
}

static void csm_finalizeInterruptSave(GM_CTX, gptr self) {
    I2_FN(0x81814DE0u); R(3) = self; BL(0x81814DF0u, fn_2_1C28C0_80930070);
}

static void csm_initializeEasyPairing(GM_CTX, gptr self) {
    I2_FN(0x81814E00u);
    NV_R(30, self); R(3) = gm_u32(self + 176); R(4) = 1; NV_R(29, 1);
    BL(0x81814E28u, mfn_8181CCAC); R(3) = gm_u32(R(30) + 1320); gm_set_u8(R(3) + 633, R(29));
}

static void csm_finalizeEasyPairing(GM_CTX, gptr self) {
    I2_FN(0x81814E48u);
    R(4) = 0; R(3) = gm_u32(self + 176); BL(0x81814E60u, mfn_8181CCAC);
}

static uint32_t csm_getPlayerPowerup(GM_CTX, gptr self, uint32_t player) {
    R(5) = self; R(3) = CSM_ACTIVE; R(4) = i2_rotl(player, 2) & 0xFFFFFFFCu;
    R(4) = gm_u32(R(3) + R(4)); R(3) = 0; CMPU(R(4), 7);
    if (R(4) > 7) return R(3);
    R(4) = i2_rotl(R(4), 2) & 0xFFFFFFFCu; R(4) = gm_u32(R(5) + R(4) + 1392); CMPU(R(4), 0);
    if (R(4) == 0) return R(3);
    R(3) = gm_u32(R(4) + 568); return R(3);
}

GM_HLE_VERIFIED_(mod_fn_2_1C1C30, GMV_IGNORE_POLLS, 0, 0) { R(3) = csm_preExecute(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C1FD0, GMV_IGNORE_POLLS, 0, 0) { csm_continueCheck(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C2090, GMV_IGNORE_POLLS, 0, 0) { csm_continueEndWait(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C21A0, GMV_IGNORE_POLLS, 0, 0) { csm_keyWait(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C2650, GMV_IGNORE_POLLS, 0, 0) { csm_stockItemSelectWait(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C2C90, GMV_IGNORE_POLLS, 0, 0) { csm_initializeInterruptSave(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C2CE0, GMV_IGNORE_POLLS, 0, 0) { csm_executeInterruptSave(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C2D10, GMV_IGNORE_POLLS, 0, 0) { csm_finalizeInterruptSave(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C31C0, GMV_IGNORE_POLLS, 0, 0) { csm_initializeEasyPairing(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C3270, GMV_IGNORE_POLLS, 0, 0) { csm_finalizeEasyPairing(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1C3A40, GMV_IGNORE_POLLS, 0, 0) { R(3) = csm_getPlayerPowerup(GM_PASS, GM_ARG(0), GM_ARG(1)); }
