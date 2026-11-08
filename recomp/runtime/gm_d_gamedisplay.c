/* gm_d_gamedisplay.c - dGameDisplay_c, the in-game HUD (the 8-player module's version).
 * Track B (gm_i2.h, docs/DECOMP.md), instance 2.
 *
 * The small main-game / pause / goal-end state methods, the module's empty setPlayNum replacement,
 * the time / score displays and the rest-coin animation helpers, checked against the recompiled
 * module code (0x81831BC8-0x81832FAC). Framed functions replay their PowerPC frames and nested
 * calls with I2_FN / BL; the simple state methods are leaves. Register and CR0 results are exact.
 *
 * The field names below describe only the behavior established from the PowerPC code. The rest
 * of the HUD remains recompiled and continues to access the object in guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define GD_STATE_MANAGER      936        /* dStateMgr_c */
#define GD_TIME_VALUE         992        /* s32: the time currently shown */
#define GD_SCORE_VALUE        1000       /* s32: the score currently shown */
#define GD_GOAL_ELAPSED       1024       /* s32: incremented until it reaches GD_GOAL_LIMIT */
#define GD_GOAL_LIMIT         1032       /* s32 */
#define GD_SCORE_DELAY        1076       /* s32: positive when a score display update is allowed */
#define GD_MAIN_PAUSE_VALUE   1080       /* s32: cleared when entering pause */
#define GD_MAIN_GAME_VALUE    1084       /* s32: 0 in main game, 1 in pause */
#define GD_PAUSE_ANIM_VALUE   1088       /* s32: cleared when leaving pause */
#define GD_GOAL_END_VALUE     1092       /* s32: cleared once the goal counter reaches its limit */
#define GD_REST_COIN_REQUEST  1097       /* u8 */
#define GD_REST_COIN_ACTIVE   1098       /* u8: the request halfword's high byte */
#define GD_MAIN_GAME_EXEC_FLAG 1100      /* u8: selects a state change when set to 1 */
#define GD_MAIN_GAME_FLAG     1105       /* u8: cleared on entry, set on exit */
#define GD_GOAL_SETTLE_FLAG   1107       /* u8: cleared when entering the main-game state */
#define GD_TIME_TEXT          1248       /* LytTextBox_c* */
#define GD_SCORE_TEXT         1252       /* LytTextBox_c* */
#define GD_SIZE               1256
#define GD_REST_COIN_GLOBAL   0x80429FE2u /* u8: RestCoinAnimeSetup writes its request only for 1 */
#define GD_STAGE_C4_INSTANCE  0x80429FD8u /* StageC4::instance; +29 is set after the coin animation */
#define GD_STACK_GUARD        0x8185FED4u /* u32: checked on return from the display setters */

static void dGameDisplay_initializeState_ProcMainGame(GM_CTX, gptr self) {
    R(4) = 0;
    gm_set_u32(self + GD_MAIN_GAME_VALUE, R(4));
    gm_set_u8(self + GD_MAIN_GAME_FLAG, R(4));
    gm_set_u8(self + GD_GOAL_SETTLE_FLAG, R(4));
}

static void dGameDisplay_executeState_ProcMainGame(GM_CTX, gptr self) {
    I2_FN(0x818322BCu);
    R(4) = gm_u32(self + GD_MAIN_PAUSE_VALUE);
    if (CMPU(R(4), 1) == 0) {
        R(4) = 0;
        gm_set_u32(self + GD_PAUSE_ANIM_VALUE, R(4));
        R(4) = 0x80370000u;
        R(4) += 28856;
    } else {
        R(4) = gm_u8(self + GD_MAIN_GAME_EXEC_FLAG);
        if (CMPU(R(4), 1) != 0) return;
        R(4) = 0x80370000u;
        R(4) += 28920;
    }
    R(3) = self + GD_STATE_MANAGER;
    BL(0x81832304u, mod_fn_8015FC10_81838420);
}

static void dGameDisplay_finalizeState_ProcMainGame(GM_CTX, gptr self) {
    R(4) = 1;
    gm_set_u8(self + GD_MAIN_GAME_FLAG, R(4));
}

static void dGameDisplay_initializeState_ProcMainPause(GM_CTX, gptr self) {
    R(4) = 1;
    gm_set_u32(self + GD_MAIN_GAME_VALUE, R(4));
    R(4) = 0;
    gm_set_u32(self + GD_MAIN_PAUSE_VALUE, R(4));
}

static void dGameDisplay_executeState_ProcMainPause(GM_CTX, gptr self) {
    I2_FN(0x81832358u);
    R(4) = gm_u32(self + GD_PAUSE_ANIM_VALUE);
    if (CMPU(R(4), 1) != 0) return;
    R(4) = 0x80370000u;
    R(3) = self + GD_STATE_MANAGER;
    R(4) += 28792;
    BL(0x81832380u, mod_fn_8015FC10_81838420);
}

static void dGameDisplay_finalizeState_ProcMainPause(GM_CTX, gptr self) {
    R(4) = 0;
    gm_set_u32(self + GD_PAUSE_ANIM_VALUE, R(4));
}

static void dGameDisplay_executeState_ProcGoalEnd(GM_CTX, gptr self) {
    R(4) = gm_u32(self + GD_GOAL_ELAPSED);
    R(5) = gm_u32(self + GD_GOAL_LIMIT);
    if (CMPS(R(4), R(5)) < 0) {
        R(4)++;
        gm_set_u32(self + GD_GOAL_ELAPSED, R(4));
    } else {
        R(4) = 0;
        gm_set_u32(self + GD_GOAL_END_VALUE, R(4));
    }
}

static void dGameDisplay_setPlayNum(GM_CTX, gptr self) {
    /* The module intentionally disables the original HUD player-count update. */
    (void)self;
}

static void dGameDisplay_RestCoinAnimeCheck(GM_CTX, gptr self) {
    I2_FN(0x81831E04u);
    R(4) = gm_u8(self + GD_REST_COIN_ACTIVE);
    if (CMPU(R(4), 0) == 0) {
        R(4) = gm_u8(self + GD_REST_COIN_REQUEST);
        if (CMPU(R(4), 0) != 0) {
            R(30) = 1;
            gm_set_u16(self + GD_REST_COIN_REQUEST, R(30));
            R(3) = self + 112;
            R(4) = 0;
            R(5) = 0;
            BL(0x81831E44u, hle_enableNonLoopAnim__Q23m2d13EmbedLayout_cFib);
            R(3) = 0x80430000u;
            R(3) = gm_u32(R(3) - 25272);
            R(3) = gm_u8(R(3) + 3020);
            if (CMPU(R(3), 1) == 0) {
                R(3) = 0x80430000u;
                R(3) = gm_u32(R(3) - 24616);
                gm_set_u8(R(3) + 29, R(30));
            }
            return;
        }
    }
    R(4) = 0;
    gm_set_u8(self + GD_REST_COIN_REQUEST, R(4));
}

static void dGameDisplay_setTime(GM_CTX, gptr self, uint32_t time) {
    I2_FN(0x81832C40u);
    R(6) = R(3);
    R(30) = 0x81860000u;
    R(5) = gm_u32(R(30) - 300);
    gm_set_u32(R(1) + 20, R(5));
    R(5) = gm_u32(R(6) + GD_TIME_VALUE);
    R(6) += GD_TIME_VALUE;
    if (CMPU(R(5), R(4)) != 0) {
        R(5) = gm_u32(self + GD_TIME_TEXT);
        gm_set_u32(self + GD_TIME_VALUE, R(4));
        R(4) = 3;
        gm_set_u32(R(1) + 16, R(4));
        R(4) = R(1) + 16;
        R(3) = R(6);
        R(6) = 1;
        BL(0x81832C8Cu, LayoutDispNumber__8dGameComFRCiRCiP12LytTextBox_cb_800B3B60);
    }
    (void)time;
    R(3) = gm_u32(R(30) - 300);
    R(4) = gm_u32(R(1) + 20);
    if (CMPU(R(3), R(4)) != 0) BL(0x81832CB4u, mfn_81844FCC);
}

static void dGameDisplay_setScore(GM_CTX, gptr self, uint32_t score) {
    I2_FN(0x81832EE4u);
    R(6) = R(3);
    R(30) = 0x81860000u;
    R(5) = gm_u32(R(30) - 300);
    gm_set_u32(R(1) + 20, R(5));
    R(5) = gm_u32(R(6) + GD_SCORE_VALUE);
    R(6) += GD_SCORE_VALUE;
    if (CMPU(R(5), R(4)) == 0) goto check_guard;
    R(7) = 0x05F50000u;
    R(7) |= 0xE0CDu;                     /* 99,999,949 */
    if (CMPS(R(5), R(7)) > 0) goto check_guard;
    R(5) = gm_u32(self + GD_SCORE_DELAY);
    R(7) = R(5) + 1;
    gm_set_u32(self + GD_SCORE_DELAY, R(7));
    if (CMPS(R(5), 0) <= 0) goto check_guard;
    R(5) = 0x05F50000u;
    R(5) |= 0xE0CEu;                     /* 99,999,950 */
    R(7) = 0;
    gm_set_u32(self + GD_SCORE_DELAY, R(7));
    if (CMPS(R(4), R(5)) >= 0) R(4) = R(5);
    R(5) = gm_u32(self + GD_SCORE_TEXT);
    gm_set_u32(self + GD_SCORE_VALUE, R(4));
    R(4) = 8;
    gm_set_u32(R(1) + 16, R(4));
    R(4) = R(1) + 16;
    R(3) = R(6);
    R(6) = 1;
    BL(0x81832F70u, LayoutDispNumber__8dGameComFRCiRCiP12LytTextBox_cb_800B3B60);
check_guard:
    (void)score;
    R(3) = gm_u32(R(30) - 300);
    R(4) = gm_u32(R(1) + 20);
    if (CMPU(R(3), R(4)) != 0) BL(0x81832F94u, mfn_81844FCC);
}

static void dGameDisplay_RestCoinAnimeSetup(GM_CTX, gptr self) {
    R(4) = 0x80430000u;
    R(4) = gm_u8(R(4) - 24606);
    if (CMPU(R(4), 1) != 0) return;
    R(4) = 1;
    gm_set_u8(self + GD_REST_COIN_REQUEST, R(4));
}

static void dGameDisplay_initializeState_ProcGoalSettleUp(GM_CTX, gptr self) {
    I2_FN(0x8183239Cu);
    R(5) = 10;
    R(4) = 1;
    gm_set_u32(self + 1036, R(5));             /* score unit */
    R(5) = 50;
    gm_set_u32(self + 1040, R(5));             /* score multiplier */
    R(5) = 0x80430000u;
    R(5) = gm_u32(R(5) - 24464);               /* remaining course time */
    R(6) = 0x80430000u;
    gm_set_u32(self + GD_GOAL_ELAPSED, R(4));
    R(5) = gm_u32(R(5) + 4);
    gm_set_u32(self + GD_GOAL_END_VALUE, R(4));
    R(6) = gm_u8(R(6) - 24606);                /* assist mode */
    R(5) += 4095;
    gm_set_u8(self + GD_GOAL_SETTLE_FLAG, R(4));
    R(4) = 0x80430000u;
    R(4) = gm_u32(R(4) - 24656);               /* rounded time-bonus destination */
    int32_t rounded = (int32_t)R(5);
    ctx->xer_ca = rounded < 0 && ((uint32_t)rounded & 0xFFFu) != 0;
    R(5) = (uint32_t)(rounded >> 12);
    uint64_t sum = (uint64_t)R(5) + ctx->xer_ca;
    R(5) = (uint32_t)sum;
    ctx->xer_ca = (uint32_t)(sum >> 32);
    CMPU(R(6), 1);
    R(5) = (uint32_t)(int16_t)R(5);
    gm_set_u32(R(4) + 4, R(5));
    if (CR_BIT(ctx, 2)) BL(0x81832404u, fn_80159630);
}

static void dGameDisplay_executeState_ProcGoalSettleUp(GM_CTX, gptr self) {
    I2_FN(0x81832414u);
    R(30) = self;
    R(3) = gm_u32(self + GD_GOAL_ELAPSED);
    R(4) = gm_u32(self + 1028);                /* delay before settling the time bonus */
    if (CMPS(R(3), R(4)) < 0) {
        R(3)++;
        gm_set_u32(self + GD_GOAL_ELAPSED, R(3));
        return;
    }
    R(3) = 0x80430000u;
    R(3) = gm_u8(R(3) - 24606);
    if (CMPU(R(3), 1) == 0) {
        R(3) = R(30);
        BL(0x8183245Cu, mod_fn_80158D00_8183217C);
        if (CMPU(R(3), 0) == 0) return;
        R(3) = 0;
        gm_set_u32(R(30) + GD_GOAL_ELAPSED, R(3));
    } else {
        R(3) = R(30);
        BL(0x81832478u, mod_fn_80158C50_818320B8);
        if (CMPU(R(3), 0) == 0) return;
        R(3) = 0x80430000u;
        R(3) = gm_u8(R(3) - 24704 + 3);
        R(3) &= 0x40u;
        CR0(ctx, R(3));
        R(3) = 0;
        gm_set_u32(R(30) + GD_GOAL_ELAPSED, R(3));
        if (CR_BIT(ctx, 2)) goto change_state;
    }
    R(3) = 0x80430000u;
    R(3) = gm_u32(R(3) - 23416);
    R(4) = 146;
    R(5) = 1;
    BL(0x818324B0u, hle_startSystemSe__11SndAudioMgrFUiUl);
change_state:
    R(4) = 0x80370000u;
    R(3) = R(30) + GD_STATE_MANAGER;
    R(4) += 28984;
    BL(0x818324C0u, mod_fn_8015FC10_81838420);
}

/* ================================================================== entry points */
#define SELF GM_ARG(0)
#define GD_MEM SELF, GD_SIZE, GD_REST_COIN_GLOBAL, 1, GD_STACK_GUARD, 4
static void gd_selftest(GM_CTX, gptr self);

GM_HLE_VOID(mod_fn_80158890, GD_MEM, gm_u32(GD_STAGE_C4_INSTANCE) + 29, 1) { dGameDisplay_RestCoinAnimeCheck(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80158E10, GD_MEM) { gd_selftest(GM_PASS, SELF); dGameDisplay_initializeState_ProcMainGame(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80158E30, GD_MEM) { dGameDisplay_executeState_ProcMainGame(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80158EA0, GD_MEM) { dGameDisplay_finalizeState_ProcMainGame(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80158EB0, GD_MEM) { dGameDisplay_initializeState_ProcMainPause(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80158ED0, GD_MEM) { dGameDisplay_executeState_ProcMainPause(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80158F00, GD_MEM) { dGameDisplay_finalizeState_ProcMainPause(GM_PASS, SELF); }
/* Restore every normal-mode timer / score write before the native invocation. Sound calls can
 * change poll counts on the second invocation, so ignore polls only; memory and registers stay strict. */
GM_HLE_VOID(mod_fn_80158F10, GD_MEM, gm_u32(0x8042A050u) + 4, 4) { dGameDisplay_initializeState_ProcGoalSettleUp(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_80158F70, GMV_IGNORE_POLLS, GD_MEM, gm_u32(0x8042A050u), 12, 0x80429CC0u, 4) { dGameDisplay_executeState_ProcGoalSettleUp(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80159070, GD_MEM) { dGameDisplay_executeState_ProcGoalEnd(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80159880, GD_MEM) { dGameDisplay_setPlayNum(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80159AC0, GD_MEM) { dGameDisplay_setTime(GM_PASS, SELF, GM_ARG(1)); }
/* LayoutDispNumber mutates its text box outside GD_MEM. Its second invocation during verification
 * can skip text-processing loops; keep comparing all declared memory and registers, not those polls. */
GM_HLE_VERIFIED_(mod_fn_80159CB0, GMV_IGNORE_POLLS, GD_MEM) { dGameDisplay_setScore(GM_PASS, SELF, GM_ARG(1)); }
GM_HLE_VOID(mod_fn_80159D20, GD_MEM) { dGameDisplay_RestCoinAnimeSetup(GM_PASS, SELF); }

/* ================================================================== self-test (RT_GM_SELFTEST=game_display)
 * Random object contents, plus directed goal-counter / score cases and both RestCoinAnimeSetup
 * global values. Functions with nested calls are constrained to paths that do not call through
 * random state-manager or layout contents. Live HUD execution checks those call-taking paths. */
static const gm_test_t gd_tests[] = {
    GM_TEST(mod_fn_80158890, 0, ""),
    GM_TEST(mod_fn_80158E10, 0, ""),
    GM_TEST(mod_fn_80158E30, 0, ""),
    GM_TEST(mod_fn_80158EA0, 0, ""),
    GM_TEST(mod_fn_80158EB0, 0, ""),
    GM_TEST(mod_fn_80158ED0, 0, ""),
    GM_TEST(mod_fn_80158F00, 0, ""),
    GM_TEST(mod_fn_80159070, 0, ""),
    GM_TEST(mod_fn_80159880, 0, ""),
    GM_TEST(mod_fn_80159AC0, 0, "T"),
    GM_TEST(mod_fn_80159CB0, 0, "T"),
    GM_TEST(mod_fn_80159D20, 0, ""),
};
static gptr gd_test_self;
static uint32_t gd_arg(char kind) {
    return kind == 'T' ? 123 : 0xDEADBEEFu;
}
static void gd_randomize(GM_CTX, int round) {
    (void)ctx;
    for (uint32_t a = 0; a < GD_SIZE; a += 4) gm_set_u32(gd_test_self + a, gm_rand());
    uint32_t elapsed = gm_rand();
    uint32_t limit = round % 3 == 0 ? elapsed : round % 3 == 1 ? elapsed + 1 : elapsed - 1;
    gm_set_u32(gd_test_self + GD_GOAL_ELAPSED, elapsed);
    gm_set_u32(gd_test_self + GD_GOAL_LIMIT, limit);
    gm_set_u32(gd_test_self + GD_MAIN_PAUSE_VALUE, gm_rand() & ~1u);
    gm_set_u32(gd_test_self + GD_PAUSE_ANIM_VALUE, gm_rand() & ~1u);
    gm_set_u8(gd_test_self + GD_MAIN_GAME_EXEC_FLAG, gm_rand() & 0xFE);
    gm_set_u8(GD_REST_COIN_GLOBAL, gm_rand() & 1);
    gm_set_u8(gd_test_self + GD_REST_COIN_REQUEST, 0);
    gm_set_u8(gd_test_self + GD_REST_COIN_ACTIVE, round & 1);
    gm_set_u32(gd_test_self + GD_TIME_VALUE, 123);
    if (round % 3 == 0) {                         /* equal score: immediate exit */
        gm_set_u32(gd_test_self + GD_SCORE_VALUE, 123);
        gm_set_u32(gd_test_self + GD_SCORE_DELAY, gm_rand());
    } else if (round % 3 == 1) {                  /* above 99,999,949: immediate exit */
        gm_set_u32(gd_test_self + GD_SCORE_VALUE, 99999950u + (gm_rand() & 0xFF));
        gm_set_u32(gd_test_self + GD_SCORE_DELAY, gm_rand());
    } else {                                      /* ordinary score: increment a zero delay, no layout call */
        gm_set_u32(gd_test_self + GD_SCORE_VALUE, 0);
        gm_set_u32(gd_test_self + GD_SCORE_DELAY, 0);
    }
    gm_set_u32(GD_STACK_GUARD, gm_rand());
}
static void gd_selftest(GM_CTX, gptr self) {
    if (!gm_selftest_wanted("game_display")) return;
    gd_test_self = self;
    const gptr ranges[] = { GD_MEM };
    const gm_selftest_t t = { "game_display", gd_tests, (int)(sizeof gd_tests / sizeof *gd_tests), 400,
                              ranges, (int)(sizeof ranges / sizeof *ranges) / 2, gd_randomize, gd_arg };
    gm_selftest(GM_PASS, &t);
}
