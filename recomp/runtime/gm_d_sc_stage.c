/* gm_d_sc_stage.c - dScStage_c course-scene transitions and saved-state restoration.
 * Ported from the 8-player module's v0.6.5 source and checked against its USA rev 2
 * recompiled bodies. The original guest calls and loop back-edge polls are retained. */
#include "gm_i2.h"
RT_STATE_FILE

#define ST_INSTANCE    0x8042A1C8u
#define ST_CD_INSTANCE 0x80429E98u
#define ST_LOOP_TYPE   0x8042A208u
#define ST_TITLE_COUNT 0x8042A1F8u
#define ST_INFO        0x80429F7Cu
#define ST_SAVE_MNG    0x8042A040u
#define ST_GOAL_TYPE   0x8042A1FCu
#define ST_MINI_GAME   0x8042A220u
#define ST_AUTOBOOT    0x8185F8D9u
#define ST_START_INFO  0x8185EB84u
#define ST_PLAYER_TYPE 0x8185E93Cu
#define ST_REST        0x81851D8Cu
#define ST_MODE        0x8185E890u
#define ST_ENTRY       0x8185E99Cu
#define ST_COIN        0x8185E97Cu
#define ST_CREATE_ITEM 0x8185E95Cu
#define ST_COINS       0x803741B0u
#define ST_COIN_FLAGS  0x8184EF20u

static void stage_setLoopType(GM_CTX) {
    I2_FN(0x818154A4u);
    R(5) = gm_u32(ST_INSTANCE);
    R(3) = gm_u32(ST_CD_INSTANCE);
    R(0) = gm_u8(R(5) + 4622);
    R(0) = (uint32_t)((int32_t)R(0) * 944);
    R(3) += R(0);
    R(0) = gm_u32(R(3) + 44);
    CMPS(R(0), 0);
    if (R(0) == 0) R(3) = 0;
    R(0) = 0;
    gm_set_u32(ST_LOOP_TYPE, R(0));
    R(4) = gm_u32(R(3) + 12);
    R(0) = gm_u16(R(4) + 8) & 1;
    CMPU(R(0), 0);
    if (R(0) == 0) return;
    R(4) = gm_u8(R(5) + 4623);
    BL(0x81815504u, hle_fn_8008E740);
    R(3) &= 0xFFFFu;
    R(0) = 0x43300000u;
    R(3) ^= 0x80000000u;
    gm_set_u32(gm_frame_sp + 12, R(3));
    R(4) = 0x8042D128u;
    ctx->f[3].u = ld64(base, R(4));
    gm_set_u32(gm_frame_sp + 8, R(0));
    ctx->f[1].d = ctx->ps1[1] = ldfs(base, R(4) - 4);
    ctx->f[2].u = ld64(base, gm_frame_sp + 8);
    ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(4) - 8);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    st64(base, gm_frame_sp + 16, ctx->f[0].u);
    R(0) = gm_u32(gm_frame_sp + 20);
    R(4) = 0x80430000u;
    CMPS(R(0), 26);
    if (R(0) == 26 || R(0) == 32 || R(0) == 35 || R(0) == 37) {
        R(0) = 1;
    } else {
        R(0) = 2;
    }
    gm_set_u32(R(4) - 24056, R(0));
}

static void stage_setNextScene(GM_CTX) {
    I2_FN(0x8181558Cu);
    R(11) = gm_frame_sp + 32;
    BL(0x818155A0u, __save_gpr_entry_802DCD74);
    NV_R(29, R(3));
    NV_R(28, R(4));
    NV_R(27, R(5));
    R(3) = R(6);
    BL(0x818155B4u, setFader__8dFader_cFQ28dFader_c12fader_type_e_800B0DB0);
    R(4) = gm_u32(R(13) - 21628);
    R(0) = R(4) - 2;
    CMPU(R(0), 1);
    if (R(0) <= 1) {
        CMPU(R(29), 10);
        R(0) = 2;
        gm_set_u32(R(13) - 26228, R(0));
        if (R(29) == 10 || R(29) == 8) {
            R(3) = R(29); R(4) = R(28); R(5) = 0;
            BL(0x818155FCu, hle_DoSceneChange__FUsUiUi);
        } else {
            R(3) = 0; R(4) = 0;
            BL(0x818155E8u, mod_startTitle__17dScRestartCrsin_cFUcb_818151B4);
        }
        goto done;
    }

    R(0) = gm_u32(R(13) - 22272) & 0x10;
    CMPU(R(0), 0);
    if (R(0) != 0) {
        NV_R(29, gm_u32(R(13) - 22224));
        CMPS(R(29), 0);
        if (R(29) != 0) {
            NV_R(30, 0x8185E93Cu);
            NV_R(31, 0x81851D8Cu);
            NV_R(28, 0);
            do {
                R(0) = gm_u32(R(30));
                R(3) = R(29); R(5) = R(28);
                R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
                R(4) = gm_u32(R(31) + R(0));
                BL(0x81815644u, fn_800CE940);
                NV_R(28, R(28) + 1);
                NV_R(30, R(30) + 4);
                CMPS(R(28), 8);
                if ((int32_t)R(28) < 8) GM_LOOP();
                else break;
            } while (1);
        }
        CMPS(R(27), 0);
        R(0) = 2;
        gm_set_u32(R(13) - 26228, R(0));
        if (R(27) == 0) {
            R(3) = 711; R(4) = 0; R(5) = 0;
            BL(0x81815674u, hle_DoSceneChange__FUsUiUi);
        } else {
            BL(0x8181567Cu, fn_800B5040);
            R(0) = gm_u32(R(13) - 22272) & 0x20;
            CMPU(R(0), 0);
            if (R(0) != 0) {
                R(3) = 9; R(4) = 0; R(5) = 0;
                BL(0x81815698u, hle_DoSceneChange__FUsUiUi);
            } else {
                CMPS(R(29), 0);
                if (R(29) != 0) {
                    R(3) = R(29);
                    BL(0x818156ACu, fn_800CEB80);
                }
                R(3) = 711; R(4) = 0; R(5) = 0;
                BL(0x818156BCu, hle_DoSceneChange__FUsUiUi);
            }
        }
        goto done;
    }

    R(3) = 0x80315B90u;
    R(0) = gm_u32(R(3) + 8);
    CMPS(R(0), 4);
    if (R(0) == 4) {
        R(0) = 2;
        gm_set_u32(R(13) - 26228, R(0));
        BL(0x818156E0u, fn_801018C0);
        goto done;
    }
    CMPS(R(4), 1);
    uint32_t game_mode_is_1 = R(4) == 1;
    gm_set_u32(R(13) - 26228, R(27));
    R(4) = gm_u32(ST_INSTANCE);
    R(3) = gm_u8(R(4) + 4620);
    R(0) = gm_u8(R(4) + 4621);
    if (game_mode_is_1 && R(27) == 1 && R(3) == 7 && R(0) == 23) {
        R(3) = 8; R(4) = 2; R(5) = 0;
        BL(0x81815728u, hle_DoSceneChange__FUsUiUi);
        goto done;
    }
    CMPU(R(29), 3);
    if (R(29) != 3) {
        R(3) = R(29); R(4) = R(28); R(5) = 0;
        BL(0x81815794u, hle_DoSceneChange__FUsUiUi);
        goto done;
    }
    if (R(0) == 35 && R(27) == 0) {
        R(4) = 0x802F49F0u;
        R(0) = i2_rotl(R(3), 2) & 0x3FCu;
        R(4) = gm_u32(R(4) + R(0));
        CMPS(R(4), 10);
        if (R(4) != 10) {
            R(5) = gm_u32(R(13) - 22276);
            R(0) = 3;
            R(3) = R(4) & 0xFF;
            R(4) = 0;
            gm_set_u32(R(5) + 880, R(0));
            R(5) = 0;
            BL(0x81815778u, setNextWorldScene__9dScWMap_cFUcUcUc_80102690);
            goto done;
        }
    }
    BL(0x81815780u, mfn_81815EC8);
done:
    R(11) = gm_frame_sp + 32;
    BL(0x8181579Cu, __restore_gpr_entry_802DCDC0);
}

static void stage_calcTitleCount(GM_CTX) {
    R(3) = gm_u8(ST_AUTOBOOT);
    CMPU(R(3), 0);
    if (R(3) != 0) return;
    R(3) = 0x80430000u;
    R(4) = gm_u32(R(3) - 24072) + 1;
    R(5) = 0x88888889u;
    R(5) = (uint32_t)(((int64_t)(int32_t)R(4) * (int32_t)R(5)) >> 32);
    R(5) += R(4);
    R(6) = i2_rotl(R(5), 1) & 1;
    {
        int32_t v = (int32_t)R(5);
        ctx->xer_ca = v < 0 && ((uint32_t)v & 7) != 0;
        R(5) = (uint32_t)(v >> 3);
    }
    R(5) += R(6);
    R(5) = (uint32_t)((int32_t)R(5) * 15);
    R(4) -= R(5);
    gm_set_u32(R(3) - 24072, R(4));                                     /* (the counter itself, not 0x80430000) */
}

static uint32_t stage_createdLayouts(GM_CTX, gptr self) {
    I2_FN(0x8182B77Cu);
    NV_R(30, self);
    BL(0x8182B794u, hle_hasUninitialisedProcesses__7fBase_cFv);
    CMPU(R(3), 0);
    uint32_t uninitialised = R(3) != 0;
    R(3) = 0;
    if (uninitialised) goto done;
    R(4) = gm_u32(R(30) + 4584);
    CMPU(R(4), 0);
    if (R(4) != 0) {
        R(4) = gm_u8(R(4) + 728);
        CMPU(R(4), 1);
        if (R(4) != 1) goto done;
    }
    R(4) = gm_u32(R(30) + 4588);
    CMPU(R(4), 0);
    if (R(4) != 0) {
        R(4) = gm_u8(R(4) + 888);
        CMPU(R(4), 1);
        if (R(4) != 1) goto done;
    }
    R(4) = gm_u32(R(30) + 4592);
    CMPU(R(4), 0);
    if (R(4) != 0) {
        R(4) = gm_u8(R(4) + 2684);
        CMPU(R(4), 1);
        if (R(4) != 1) goto done;
    }
    R(4) = gm_u32(R(30) + 4596);
    CMPU(R(4), 0);
    if (R(4) != 0) {
        R(4) = gm_u8(R(4) + 596);
        CMPU(R(4), 1);
        if (R(4) != 1) goto done;
    }
    R(3) = gm_u32(R(30) + 4604);
    CMPU(R(3), 0);
    if (R(3) != 0) R(3) = gm_u8(R(3) + 632);
    else R(3) = 1;
done:
    R(3) &= 1;
    return R(3);
}

static void stage_exitRestore(GM_CTX) {
    GM_FN(0x8182BA94u); GM_NV_KEEP;
    R(4) = 0x81860000u;
    R(3) = ST_INFO;
    R(5) = ST_START_INFO;
    R(3) = gm_u32(R(3));
    R(10) = 0x81860000u;
    R(4) = gm_u32(R(5) + 4);
    R(12) = 0x81860000u;
    R(6) = gm_u32(R(5) + 8);
    R(0) = 8;
    gm_set_u32(R(3) + 12, R(4));
    gm_set_u32(R(3) + 16, R(6));
    R(4) = gm_u32(R(5) + 12);
    R(6) = gm_u32(R(5) + 16);
    gm_set_u32(R(3) + 20, R(4));
    gm_set_u32(R(3) + 24, R(6));
    R(7) = gm_u16(R(5) + 25);
    R(4) = gm_u32(R(5) + 20);
    R(6) = gm_u8(R(5) + 24);
    gm_set_u16(R(3) + 33, R(7));
    gm_set_u32(R(3) + 28, R(4));
    R(4) = gm_u32(R(5) + 32);
    gm_set_u8(R(3) + 32, R(6));
    R(6) = gm_u32(R(5) + 36);
    gm_set_u32(R(3) + 40, R(4));
    R(4) = 0;
    gm_set_u32(R(3) + 44, R(6));
    R(6) = gm_u32(R(5) + 40);
    R(11) = gm_u32(R(5) + 44);
    R(9) = gm_u8(R(5) + 28);
    R(8) = gm_u8(R(5) + 27);
    R(7) = gm_u8(R(5) + 52);
    gm_set_u32(R(3) + 48, R(6));
    gm_set_u32(R(3) + 52, R(11));
    R(11) = gm_u32(R(5) + 48);
    gm_set_u8(R(3) + 36, R(9));
    R(9) = 0x81860000u;
    NV_R(29, 0x8185E95Cu);
    NV_R(30, 0x81850000u);
    gm_set_u8(R(3) + 35, R(8));
    R(8) = 0x81860000u;
    gm_set_u8(R(3) + 896, R(7));
    R(7) = 0x81860000u;
    NV_R(28, 0);
    R(6) = 0x8185E97Cu;
    R(7) = 0x8185E93Cu;
    R(8) = 0x8185E890u;
    R(9) = 0x8185E99Cu;
    R(10) = 0x81851D8Cu;
    gm_set_u32(R(3) + 56, R(11));
    R(11) = R(5) + 135;
    R(12) = R(29) - 4;
    R(5) += 68;
    NV_R(30, 0);
    ctx->ctr = R(0);
    do {
        R(5) += 4; R(0) = gm_u32(R(5));
        R(11) += 1; NV_R(29, gm_u8(R(11)));
        NV_R(28, gm_u32(R(5) + 32));
        R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
        gm_set_u32(R(8) + R(0), R(29));
        NV_R(29, gm_u32(R(5) + 72));
        gm_set_u32(R(7) + R(0), R(30));
        NV_R(30, R(30) + 1);
        R(0) = gm_u32(R(5) + 104);
        R(12) += 4; gm_set_u32(R(12), R(28));
        NV_R(28, gm_u32(R(5) + 136));
        gm_set_u32(R(9) + R(4), R(29));
        gm_set_u32(R(10) + R(4), R(0));
        R(4) += 4;
        gm_set_u32(R(6), R(28));
        R(6) += 4;
        ctx->ctr--;
        if (ctx->ctr) GM_LOOP();
        else break;
    } while (1);
    R(4) = gm_u8(0x8042A179u);
    R(6) = 0x80430000u;
    R(5) = ST_START_INFO;
    gm_set_u8(R(6) - 24200, R(4));
    R(4) = gm_u8(0x8042A181u);
    R(6) = 0x80430000u;
    R(5) = gm_u32(R(5) + 68);
    gm_set_u8(R(6) - 24192, R(4));
    R(4) = 0x80430000u;
    gm_set_u32(R(4) - 25408, R(5));
    R(4) = 0;
    gm_set_u8(R(3) + 108, R(4));
}

static void stage_exitClear(GM_CTX) {
    I2_FN(0x8182B880u);
    R(3) = gm_u32(ST_INSTANCE);
    NV_R(30, gm_u8(R(3) + 4620));
    CMPU(R(30), 9);
    if (R(30) > 9) return;                      /* (bgt: was >= 9) */
    NV_R(29, gm_u8(R(3) + 4621));
    CMPU(R(29), 41);
    if (R(29) > 41) return;                     /* (bgt: was >= 41) */
    R(3) = gm_u32(ST_MINI_GAME);
    R(4) = 0x80430000u;
    NV_R(27, gm_u32(ST_INFO));
    CMPU(R(3), 0);
    if (R(3) == 0) {
        R(3) = 8; ctx->ctr = R(3);
        R(3) = 0x81860000u;
        R(4) = 0x8185E97Cu;
        R(5) = ST_START_INFO;
        R(3) = R(4) - 4;
        R(4) = R(5) + 204;
        do {
            R(4) += 4; R(5) = gm_u32(R(4)) & 0xFFFFFFFEu;
            R(3) += 4; gm_set_u32(R(3), R(5));
            ctx->ctr--;
            if (ctx->ctr) GM_LOOP();
            else break;
        } while (1);
    }
    R(3) = gm_u32(ST_SAVE_MNG);
    R(4) = (uint32_t)-1;
    BL(0x8182B91Cu, hle_mod_getSaveGame__10dSaveMng_cFSc);
    R(4) = 0x80315B90u;
    R(5) = gm_u32(R(4) + 8);
    CMPU(R(5), 0);
    if (R(5) != 0) {
        R(3) = gm_u32(ST_GOAL_TYPE) ^ 1;
        R(3) = cntlzw(R(3));
        R(3) = i2_rotl(R(3), 27) & 0x7FFFFFFu;
        goto proc_clear;
    }
    NV_R(28, R(3));
    R(3) = gm_u8(R(4) + 13);
    R(4) = R(3) - 25;
    CMPU(R(4), 7);
    if (R(4) >= 7) {                            /* (bge to 0x8182BA80: was > 7; only this path polls) */
        CMPU(R(3), 40);
        if (R(3) != 40) {
            R(3) = R(27) + 8;
            BL(0x8182BA90u, mod_fn_8008EDB0_81809958);
        }
        GM_LOOP();
    }
    BL(0x8182B960u, hle_mod_getEntryNum__9daPyMng_cFv);
    CMPU(R(3), 1);
    if (R(3) == 1) {
        R(6) = gm_u8(R(27) + 896);
        R(3) = R(28); R(4) = R(30); R(5) = R(29); R(7) = 0;
        BL(0x8182B980u, hle_mod_fn_800CE260);
    }
    R(3) = ST_COIN_FLAGS;
    R(4) = ST_COINS;
    NV_R(27, 3);
    R(3) -= 4;
    NV_R(26, R(4) - 4);
    do {
        NV_R(26, R(26) + 4);
        R(4) = gm_u32(R(26));
        NV_R(25, R(3) + 4);
        CMPU(R(4), 8);
        if (R(4) != 8) {
            R(6) = gm_u32(R(3) + 4);
            R(3) = R(28); R(4) = R(30); R(5) = R(29);
            BL(0x8182B9C0u, fn_800CE180);
        }
        NV_R(27, R(27) - 1);
        CMPU(R(27), 0);
        R(3) = R(25);
        if (R(27) != 0) GM_LOOP();
        else break;
    } while (1);
    R(3) = 0x80430000u; R(4) = 0;
    gm_set_u8(R(3) - 24200, R(4));
    R(3) = gm_u32(ST_GOAL_TYPE);
    R(5) = gm_u32(0x80315B90u + 8);
    R(6) = 0x80430000u;
    R(3) ^= 1; R(3) = cntlzw(R(3));
    CMPU(R(5), 0);
    R(3) = i2_rotl(R(3), 27) & 0x7FFFFFFu;
    gm_set_u8(R(6) - 24192, R(4));
    if (R(5) != 0) {                            /* (beq skips it: was inverted) */
proc_clear:
        R(4) = R(30) ^ 2;
        R(6) = R(29) ^ 3;
        R(4) = (R(4) | R(6)) & 0xFF;
        R(5) ^= 1;
        R(4) = cntlzw(R(4));
        R(5) = cntlzw(R(5));
        R(4) = i2_rotl(R(4), 27) & 0x7FFFFFFu;
        R(3) &= R(4);
        R(4) = i2_rotl(R(5), 27) & 0x7FFFFFFu;
    }
    R(5) = R(30); R(6) = R(29);
    BL(0x8182BA40u, fn_800FB9E0);
    R(3) = gm_u32(0x80315B90u + 8);
    CMPU(R(3), 0);
    if (R(3) != 0) {
        ctx->lr = 0x8182BA58u;
        stage_exitRestore(GM_PASS);
    }
}

static void stage_procExitMode(GM_CTX) {
    I2_FN(0x8182B830u);
    R(4) = gm_u32(0x80430000u - 28660);
    CMPU(R(4), 4);
    if (R(4) == 4) return;
    CMPU(R(4), 1);
    if (R(4) == 1) {
        BL(0x8182B868u, fn_2_1B7E10_809255C0);
        return;
    }
    CMPU(R(4), 0);
    if (R(4) == 0) {
        ctx->lr = 0x8182B860u;
        stage_exitClear(GM_PASS);
    } else {
        ctx->lr = 0x8182B870u;
        stage_exitRestore(GM_PASS);
    }
}

static void mod_fn_801025A0_native(GM_CTX);

static const gm_test_t stage_tests[] = {
    GM_TEST(mod_fn_801025A0, 0, "!"),
};

static void stage_selftest(GM_CTX) {
    static const gptr ranges[] = { ST_TITLE_COUNT, 4, ST_AUTOBOOT, 1 };
    const gm_selftest_t t = { "sc_stage", stage_tests,
        (int)(sizeof stage_tests / sizeof *stage_tests), 300, ranges, 2, NULL, NULL };
    gm_selftest(ctx, base, &t);
}

GM_HLE_VERIFIED_(mod_fn_80101990, GMV_IGNORE_POLLS, 0, 0) { stage_selftest(GM_PASS); stage_setLoopType(GM_PASS); }
GM_HLE_VERIFIED_(mod_setNextScene__10dScStage_cFUsiQ210dScStage_c6Exit_eQ28dFader_c12fader_type_e, GMV_IGNORE_POLLS, 0, 0) { stage_setNextScene(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_801025A0, GMV_IGNORE_POLLS, ST_TITLE_COUNT, 4) { stage_calcTitleCount(GM_PASS); }
GM_HLE_INT(mod_fn_2_1B71B0, GM_ARG(0), 0x120C) { GM_RET(stage_createdLayouts(GM_PASS, GM_ARG(0))); }
GM_HLE_VERIFIED_(mod_fn_2_1B7A20, GMV_IGNORE_POLLS, 0, 0) { stage_procExitMode(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_2_1B7A50, GMV_IGNORE_POLLS, 0, 0) { stage_exitClear(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_2_1B7C40, GMV_IGNORE_POLLS, 0, 0) { stage_exitRestore(GM_PASS); }
