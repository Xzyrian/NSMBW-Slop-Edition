/* gm_info.c - dInfo_c, the game's session info (track B, gm.h, docs/DECOMP.md): the 8-player
 * module's versions of its functions (nsmbw-project v0.6.5, wiimj2d/d_static/d_info.cpp).
 *
 * dInfo_c holds what lasts between scenes: the checkpoint (dCyuukan_c), the world map's state,
 * the Free Mode / Coin Battle records. The module moved the player arrays to its own, 8 long, and
 * appended fields for players 5-8 at the end of the class (offsets below from its compiled code).
 * Functions the module doesn't replace stay the game's. */
#include "gm_i2.h"
RT_STATE_FILE                                   /* (game code: its variables are part of a save state) */

/* ---- dInfo_c (the instance, dInfo_c::m_instance) ---- */
#define INFO_CYUUKAN            0x008   /* dCyuukan_c: the checkpoint */
#define INFO_CYUUKAN_INDEX      0x00C   /*   s32 mIndex (the checkpoint taken, -1 none) */
#define INFO_CYUUKAN_COIN       0x028   /*   s32 mCollectionCoin[3]: who took each Star Coin */
#define INFO_LAST_CLEAR_TYPE    0x060   /* u32 mLastClearStageType */
#define INFO_ZOROME_TIME        0x064   /* u32 m_zoromeTime (the timer's matching digits) */
#define INFO_FIREWORKS          0x068   /* u32 m_fireworksKind */
#define INFO_KINOPIO_IN_CHUKAN  0x06C   /* bool m_isKinopioInChukan */
#define INFO_SWITCH_ON          0x380   /* bool mSwitchOn (the world map switch) */
#define INFO_CONNECT_STAGE      0x384   /* u32 [4] mPlyConnectStage, players 1-4 */
#define INFO_COIN_BATTLE_WIN    0x3EC   /* u32 [4] mCoinBattleWin, players 1-4 */
#define INFO_COIN_COURSE        0x404   /* [10 worlds][10] { u32 mClearState; u32 } */
#define INFO_FREE_COURSE        0x774   /* [10][10] the same for Free Mode */
#define INFO_COIN_FAVORITE      0x720   /* [10] { u8 world, u8 level, u16 -, u32 mClearState } */
#define INFO_FREE_FAVORITE      0xA90   /* [10] the same */
#define INFO_CYUUKAN_STAGE      0xAF4   /* s32 mCyuukanIndex (the checkpoint, -1 none or a house) */
#define INFO_CONNECT_STAGE_EX   0xB5C   /* u32 [4] mPlyConnectStage, players 5-8 (the module's) */
#define INFO_COIN_BATTLE_WIN_EX 0xBC8   /* u32 [4] mExCoinBattleWin, players 5-8 (the module's) */

/* ---- dStartInfo_c dInfo_c::m_startInfo (the module's, 8 characters): what a stage starts from */
#define M_START_INFO            0x8185EB84u
#define SI_CYUUKAN              0x000   /* dCyuukan_c (copied field by field: 0x04..0x34) */
#define SI_SWITCH_ON            0x034
#define SI_SCORE                0x044
#define SI_PLAYER_INDEX         0x048   /* s32 [8 characters]: the player playing it */
#define SI_PLAYER_MODE          0x068   /* s32 [8] */
#define SI_IS_ENTRY             0x088   /* bool [8] */
#define SI_COIN                 0x090   /* s32 [8] */
#define SI_REST                 0x0B0   /* s32 [8] */
#define SI_CREATE_ITEM          0x0D0   /* s32 [8] */
#define SI_SIZE                 0x0F0

/* ---- other classes' statics */
#define DSAVEMNG_INSTANCE       0x8042A040u /* dSaveMng_c::m_instance */
#define DAPYMNG_PLAYER_ENTRY    0x8185E890u /* daPyMng_c::mPlayerEntry[8] (s32; the module's) */
#define DAPYMNG_PLAYER_TYPE     0x8185E93Cu /* daPyMng_c::mPlayerType[8]: player -> character */
#define DAPYMNG_PLAYER_MODE     0x8185E95Cu /* daPyMng_c::mPlayerMode[8 characters] */
#define DAPYMNG_CREATE_ITEM     0x8185E97Cu /* daPyMng_c::mCreateItem[8 characters] */
#define DAPYMNG_COIN            0x8185E99Cu /* daPyMng_c::mCoin[8 characters] */
#define DAPYMNG_REST            0x81851D8Cu /* daPyMng_c::mRest[8 characters] (initialised data) */
#define DAPYMNG_SCORE           0x80429CC0u /* daPyMng_c::mScore */
#define DEFAULT_PLAYER_TYPES    0x81849BE4u /* dMj2dGame_c::scDefaultPlayerTypes[8] */
#define START_GAME_INFO_STAGE   (0x80315B90u + 13)   /* dInfo_c::m_startGameInfo.stage1.stage (u8) */
#define DSCSTAGE_GOAL_TYPE      0x8042A1FCu /* dScStage_c::m_goalType */
#define UNDEF_8042A458          0x8042A178u /* two pairs of bytes the stage start copies (unnamed; PAL 8042A458) */
#define UNDEF_8042A460          0x8042A180u

/* ---- functions not decompiled yet */
#define A_CYUUKAN_COURSE_IN     0x8008EE00u /* dCyuukan_c::courseIN() */
#define A_SET_COLLECTION_COIN   0x80101FD0u /* dScStage_c::setCollectionCoin(int coin, PLAYER_TYPE_e) */
#define SCSTAGE_COLLECTION_COIN 0x803741B0u /* dScStage_c's Star Coin owners [3] (what setCollectionCoin sets) */

#define STAGE_STAFFROLL 41
#define STAGE_KINOKO_HOUSE 25           /* .. KINOKO_HOUSE_4 = 28 */
#define STAGE_PEACH_CASTLE 40
#define PLAYER_TYPE_COUNT 8             /* (no player) */
#define COLLECTION_COIN_COUNT 3

/* Register-exact (gm_i2.h): the functions leave the registers the PowerPC code leaves, and call
   other natives as its bl does (hle_ entries, the arguments in r3..). */
gptr dSaveMng_getSaveGame(gptr self, int32_t slot);   /* gm_save_mng.c */

/* PlayerStateInit: the default characters, every player's connection stage OFF */
void dInfo_PlayerStateInit(GM_CTX, gptr self) {
    R(4) = 0; R(7) = 0;
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        R(6) = DEFAULT_PLAYER_TYPES + 4 * p; R(8) = gm_u32(R(6));
        R(5) = DAPYMNG_PLAYER_TYPE + 4 * p;
        gm_set_u32(R(5), R(8));
        R(3) = self + INFO_CONNECT_STAGE_EX - 16 + 4 * p;              /* (r3 walks the module's array; players 1-4 are 0x7C8 below) */
        R(8) = CMPU(p, 4) < 0 ? R(3) - 1992 : R(3);
        R(7) = p + 1; R(3) += 4;
        gm_set_u32(R(8), 0);                                            /* OFF */
        if (--ctx->ctr) GM_LOOP();
    }
}
/* the stock items (the inventory) live in the slot in play: one more / one less (a signed byte,
   clamped by setStockItem), or how many - framed, through getSaveGame and setStockItem */
static void dInfo_stockItem(GM_CTX, uint32_t fn, uint32_t item, int delta) {
    NV_R(30, item);
    R(3) = gm_u32(DSAVEMNG_INSTANCE); R(4) = (uint32_t)-1;
    BL(fn + 0x24, hle_mod_getSaveGame__10dSaveMng_cFSc);
    gptr save = R(3);
    if (delta == 0) { R(3) = save + item; R(3) = gm_u8(R(3) + 8); return; }
    R(4) = save + item; R(4) = gm_u8(R(4) + 8) + (uint32_t)delta;
    R(5) = (uint32_t)(int32_t)(int8_t)R(4);
    R(4) = item; R(3) = save;
    BL(fn + 0x3C, hle_mod_fn_800CE330);                                /* dMj2dGame_c::setStockItem */
}
void dInfo_addStockItem(GM_CTX, uint32_t item) { I2_FN(0x8180C06Cu); dInfo_stockItem(GM_PASS, 0x8180C06Cu, item, 1); }
void dInfo_subStockItem(GM_CTX, uint32_t item) { I2_FN(0x8180C0BCu); dInfo_stockItem(GM_PASS, 0x8180C0BCu, item, -1); }
int  dInfo_getStockItem(GM_CTX, uint32_t item) { I2_FN(0x8180C10Cu); dInfo_stockItem(GM_PASS, 0x8180C10Cu, item, 0); return (int)R(3); }

/* initMultiMode: the Coin Battle wins, the Free Mode / Coin Battle clear states and favourites */
void dInfo_initMultiMode(GM_CTX, gptr self) {
    R(4) = 0; R(6) = 0;
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {                                  /* the win counts */
        R(5) = self + INFO_COIN_BATTLE_WIN_EX - 16 + 4 * p;
        R(7) = CMPU(p, 4) < 0 ? R(5) - 1996 : R(5);
        R(6) = p + 1; R(5) += 4;
        gm_set_u32(R(7), 0);
        if (--ctx->ctr) GM_LOOP();
    }
    R(4) = self + 1908; R(5) = 0; R(6) = 10;
    for (uint32_t w = 0;;) {                                            /* the clear states */
        ctx->ctr = 10;
        for (uint32_t c = 0; c < 10; c++) {
            R(8) = self + INFO_COIN_COURSE + w * 80 + c * 8;
            gm_set_u32(R(8), 0);
            gm_set_u32(R(8) + 880, 0);                                  /* (Free Mode's) */
            if (--ctx->ctr) GM_LOOP();
        }
        w++; R(7) = w; R(4) += 80;
        if (CMPU(w, 10) == 0) break;
        GM_LOOP();
    }
    R(4) = 10 << 8 | 42; R(5) = 0;                                      /* the favourites: none (world 10, stage 42) */
    ctx->ctr = 10;
    for (uint32_t i = 0; i < 10; i++) {
        R(3) = self + INFO_COIN_FAVORITE + 8 * i;
        gm_set_u16(R(3), (uint16_t)R(4)); gm_set_u32(R(3) + 4, 0);
        gm_set_u16(R(3) + 880, (uint16_t)R(4)); gm_set_u32(R(3) + 884, 0);
        if (--ctx->ctr) GM_LOOP();
    }
}

/* initStage: what a stage (re)starts from; the checkpoint; the Star Coins taken before it */
void dInfo_initStage(GM_CTX, gptr self) {
    I2_FN(0x8180C1ECu);
    NV_R(30, self);
    /* the checkpoint and the switch, for a restart */
    for (uint32_t o = 0x04; o <= 0x30; o += 4)
        if (o == 0x1C) gm_set_u8(M_START_INFO + SI_CYUUKAN + o, gm_u8(self + INFO_CYUUKAN + o));   /* (a bool) */
        else gm_set_u32(M_START_INFO + SI_CYUUKAN + o, gm_u32(self + INFO_CYUUKAN + o));
    gm_set_u8(M_START_INFO + SI_SWITCH_ON, gm_u8(self + INFO_SWITCH_ON));
    /* each character: who plays it, and how it starts */
    R(3) = M_START_INFO; R(5) = DAPYMNG_PLAYER_MODE; R(6) = DAPYMNG_COIN; R(7) = DAPYMNG_REST; R(10) = DAPYMNG_CREATE_ITEM;
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        R(8) = DAPYMNG_PLAYER_ENTRY + 4 * p; R(9) = DAPYMNG_PLAYER_TYPE + 4 * p;
        uint32_t t = gm_u32(R(9));
        NONZERO(29, 12, gm_u32(R(8)));                                  /* (the entry as a bool, through r29) */
        R(0) = t << 2; R(11) = M_START_INFO + t;
        NV_R(28, gm_u32(DAPYMNG_PLAYER_MODE + R(0))); NV_R(27, M_START_INFO + R(0)); NV_R(29, gm_u32(DAPYMNG_COIN + R(0)));
        gm_set_u8(R(11) + SI_IS_ENTRY, (uint8_t)R(12));
        R(11) = gm_u32(DAPYMNG_REST + R(0)); R(12) = gm_u32(DAPYMNG_CREATE_ITEM + R(0));
        gm_set_u32(R(27) + SI_PLAYER_INDEX, p); R(4) = p + 1;
        gm_set_u32(R(27) + SI_PLAYER_MODE, R(28));
        gm_set_u32(R(27) + SI_COIN, R(29));
        gm_set_u32(R(27) + SI_REST, R(11));
        gm_set_u32(R(27) + SI_CREATE_ITEM, R(12));
        if (--ctx->ctr) GM_LOOP();
    }
    NV_R(29, START_GAME_INFO_STAGE - 13);
    R(3) = gm_u32(DAPYMNG_SCORE); R(5) = M_START_INFO;
    R(4) = gm_u8(START_GAME_INFO_STAGE);
    gm_set_u32(M_START_INFO + SI_SCORE, R(3));
    R(3) = self + INFO_CYUUKAN;
    if (CMPU(R(4), STAGE_STAFFROLL) != 0) { R(4) = 0; gm_set_u32(self + INFO_LAST_CLEAR_TYPE, 0); }
    R(4) = 0; R(5) = 0x80430000u;
    gm_set_u32(self + INFO_ZOROME_TIME, 0);
    gm_set_u32(self + INFO_FIREWORKS, 0);
    gm_set_u8(self + INFO_KINOPIO_IN_CHUKAN, 0);
    gm_set_u32(DSCSTAGE_GOAL_TYPE, 0);
    BL(0x8180C35Cu, fn_8008EE00);                                       /* dCyuukan_c::courseIN() */
    /* the checkpoint counts unless this is a Toad house or Peach's castle; with one, the Star
       Coins taken before it stay taken. (The PowerPC code's jumps back poll: GM_LOOP below.) */
    R(3) = gm_u8(START_GAME_INFO_STAGE);
    R(4) = R(3) - STAGE_KINOKO_HOUSE;
    int cyuukan = -1;
    if (CMPU(R(4), 4) < 0 || CMPU(R(3), STAGE_PEACH_CASTLE) == 0) {
        R(3) = (uint32_t)-1; gm_set_u32(self + INFO_CYUUKAN_STAGE, R(3));
    } else {
        R(3) = gm_u32(self + INFO_CYUUKAN_INDEX);
        cyuukan = CMPS(R(3), 0) < 0 ? -1 : (int)R(3);
        gm_set_u32(self + INFO_CYUUKAN_STAGE, R(3));
        if (cyuukan < 0) GM_LOOP();
    }
    if (cyuukan < 0) {                                                  /* no checkpoint: nobody's coins */
        for (uint32_t c = 0;; ) {
            NV_R(30, c);
            R(3) = c; R(4) = PLAYER_TYPE_COUNT;
            BL(0x8180C38Cu, bta_sys_register_80101FD0);                 /* dScStage_c::setCollectionCoin */
            c++; NV_R(30, c);
            if (CMPU(c, COLLECTION_COIN_COUNT) == 0) break;
            GM_LOOP();
        }
    } else {                                                            /* the coins as the checkpoint saw them */
        NV_R(29, self + INFO_CYUUKAN_COIN - 4); NV_R(28, COLLECTION_COIN_COUNT); NV_R(30, 0);
        for (uint32_t c = 0;; ) {
            NV_R(29, self + INFO_CYUUKAN_COIN + 4 * c);
            R(4) = gm_u32(R(29)); R(3) = c;
            BL(0x8180C400u, bta_sys_register_80101FD0);
            NV_R(28, R(28) - 1);
            int more = CMPU(R(28), 0) > 0;
            c++; NV_R(30, c);
            if (!more) break;
            GM_LOOP();
        }
        GM_LOOP();
    }
    R(3) = gm_u8(UNDEF_8042A458); R(4) = gm_u8(UNDEF_8042A460); R(5) = 0x80430000u;
    gm_set_u8(UNDEF_8042A458 + 1, (uint8_t)R(3));
    R(3) = 0x80430000u;
    gm_set_u8(UNDEF_8042A460 + 1, (uint8_t)R(4));
}

/* ================================================================== hle entry points */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
#define INFO_SIZE 0xBD8                  /* (as far as the module's fields go) */
#define CUR_SAVE  dSaveMng_getSaveGame(gm_ptr(DSAVEMNG_INSTANCE), -1)
static void info_selftest(GM_CTX, gptr self);
GM_HLE_VOID(mod_fn_800BB130, SELF, INFO_SIZE, DAPYMNG_PLAYER_TYPE, 32) { info_selftest(GM_PASS, SELF); dInfo_PlayerStateInit(GM_PASS, SELF); }
GM_HLE_VOID(mod_AddStockPowerup, CUR_SAVE, 0x10) { dInfo_addStockItem(GM_PASS, A(1)); }
GM_HLE_VOID(mod_fn_800BB330, CUR_SAVE, 0x10)     { dInfo_subStockItem(GM_PASS, A(1)); }
GM_HLE_INT (mod_fn_800BB380, 0, 0)               { dInfo_getStockItem(GM_PASS, A(1)); }
GM_HLE_VOID(mod_fn_800BB560, SELF, INFO_SIZE)    { info_selftest(GM_PASS, SELF); dInfo_initMultiMode(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_800BB8F0, SELF, INFO_SIZE, M_START_INFO, SI_SIZE, DSCSTAGE_GOAL_TYPE, 4, UNDEF_8042A458, 0x10,
            SCSTAGE_COLLECTION_COIN, 12) { info_selftest(GM_PASS, SELF); dInfo_initStage(GM_PASS, SELF); }

/* ================================================================== self-test (RT_GM_SELFTEST=info)
   Random dInfo_c, player arrays, start info and the stage being started; the stock items work
   on the slot in play (its stock: random too). */
static const gm_test_t info_tests[] = {
    GM_TEST(mod_fn_800BB130, 0, ""),
    GM_TEST(mod_AddStockPowerup, 0, "i"),
    GM_TEST(mod_fn_800BB330, 0, "i"),
    GM_TEST(mod_fn_800BB380, GMV_RET, "i"),
    GM_TEST(mod_fn_800BB560, 0, ""),
    GM_TEST(mod_fn_800BB8F0, 0, ""),
};
static gptr info_test_self, info_test_save;
static void info_randomize(GM_CTX, int round) {
    (void)round;
    for (uint32_t i = 0; i < INFO_SIZE; i += 4) gm_set_u32(info_test_self + i, gm_rand() & gm_rand());
    gm_set_u32(info_test_self + INFO_CYUUKAN_INDEX, gm_rand() % 4 - 1);  /* (a checkpoint or none) */
    for (uint32_t p = 0; p < 8; p++) {
        gm_set_u32(DAPYMNG_PLAYER_TYPE + 4 * p, (p + gm_rand()) % 8);     /* (characters 0-7; repeats are fine) */
        gm_set_u32(DAPYMNG_PLAYER_ENTRY + 4 * p, gm_rand() % 3 == 0 ? 0 : gm_rand());
        gm_set_u32(DAPYMNG_PLAYER_MODE + 4 * p, gm_rand() % 7);
        gm_set_u32(DAPYMNG_COIN + 4 * p, gm_rand() % 100);
        gm_set_u32(DAPYMNG_REST + 4 * p, gm_rand() % 100);
        gm_set_u32(DAPYMNG_CREATE_ITEM + 4 * p, gm_rand() & 1);
    }
    gm_set_u32(DAPYMNG_SCORE, gm_rand());
    gm_set_u8(START_GAME_INFO_STAGE, gm_rand() % 2 ? gm_rand() % 42 : 24 + gm_rand() % 18);   /* (houses, castle, staff roll) */
    gm_set_u8(UNDEF_8042A458, gm_rand()); gm_set_u8(UNDEF_8042A460, gm_rand()); gm_set_u32(DSCSTAGE_GOAL_TYPE, gm_rand());
    for (uint32_t i = 0; i < 7; i++) gm_set_u8(info_test_save + 8 + i, gm_rand() % 2 ? gm_rand() % 100 : gm_rand());
}
static void info_selftest(GM_CTX, gptr self) {
    if (!gm_selftest_wanted("info") || !gm_ptr(DSAVEMNG_INSTANCE)) return;
    info_test_self = self; info_test_save = CUR_SAVE;
    const gptr ranges[] = { self, INFO_SIZE, M_START_INFO, SI_SIZE, DSCSTAGE_GOAL_TYPE, 4, UNDEF_8042A458, 0x10,
                            SCSTAGE_COLLECTION_COIN, 12, DAPYMNG_PLAYER_ENTRY, 0x130, DAPYMNG_REST, 32,
                            DAPYMNG_SCORE, 4, START_GAME_INFO_STAGE, 1, info_test_save + 8, 8 };
    const gm_selftest_t t = { "info", info_tests, (int)(sizeof info_tests / sizeof *info_tests), 300,
                              ranges, (int)(sizeof ranges / sizeof *ranges) / 2, info_randomize, NULL };
    gm_selftest(GM_PASS, &t);
}
