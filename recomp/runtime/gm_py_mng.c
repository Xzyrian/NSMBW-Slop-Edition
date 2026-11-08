/* gm_py_mng.c - daPyMng_c, the player manager (track B, gm.h, docs/DECOMP.md), instance 2.
 *
 * The 8-player module's version (nsmbw-project v0.6.5, wiimj2d/d_static/d_a_player/
 * d_a_player_manager.cpp): who takes part (mPlayerEntry), which character each player plays
 * (mPlayerType), each character's lives / coins / power-up / item (mRest, mCoin, mPlayerMode,
 * mCreateItem), the players and Yoshis by fBase_c ID, the score, the star / Yoshi music.
 * Arrays the module made 8 long live in its own memory; the scalars stay the game's.
 *
 * Register-exact (RT_GM_VERIFY_REGS=1): every function leaves r0-r12, CR0, CTR and XER[CA] as
 * the PowerPC code does - the residue a later variadic callee or a saved CR can spill. Framed
 * functions push the PowerPC frame (GM_FN, prologue replayed), keep the non-volatile registers
 * as the PowerPC code holds them at each call (NV, for the callees' saves) and end with r0 = LR.
 * The comments name the PowerPC instruction a residue comes from when it isn't obvious.
 *
 * Still recompiled: createCourseInit (TODO, CHANGELOG). */
#include "gm_i2.h"
RT_STATE_FILE                                   /* (game code: its variables are part of a save state) */


/* ---- the module's arrays (its .bss / .data) */
#define PY_ACT_INFO         0x8185E888u /* u64 mActPlayerInfo: a bit per player in play (high word, low word at +4) */
#define PY_ENTRY            0x8185E890u /* s32 mPlayerEntry[8]: the player takes part */
#define PY_PLAYER_ID        0x8185E8B4u /* fBaseID_e m_playerID[8] */
#define PY_YOSHI_ID         0x8185E8D4u /* fBaseID_e m_yoshiID[8] */
#define PY_COURSE_IN_LIST   0x8185E8F4u /* s32 mCourseInList[8] */
#define PY_YOSHI_COLOR      0x8185E914u /* u8 m_yoshiColor[8]: the Yoshi a player brings into the next course */
#define PY_YOSHI_FRUIT      0x8185E91Cu /* s32 m_yoshiFruit[8] */
#define PY_TYPE             0x8185E93Cu /* PLAYER_TYPE_e mPlayerType[8]: player -> character */
#define PY_MODE             0x8185E95Cu /* PLAYER_MODE_e mPlayerMode[8 characters]: power-up */
#define PY_CREATE_ITEM      0x8185E97Cu /* PLAYER_CREATE_ITEM_e mCreateItem[8 characters] (bit 4 bubble, 8 Toad rescue ...) */
#define PY_COIN             0x8185E99Cu /* s32 mCoin[8 characters] */
#define GAME_RULE           0x8185FE04u /* dGameRule_s::current (the module's game rules) */
#define GR_INFINITE_LIVES   5           /*   bool infinite_lives */
#define PY_DEATH_COUNT      0x8185EAF0u /* s32 mDeathCount[8 characters] (with infinite lives: deaths instead of lives) */
#define PY_STAR_COUNT       0x8185EAD0u /* u16 m_star_count[8] */
#define PY_STAR_TIME        0x8185EAE0u /* u16 m_star_time[8] */
#define PY_QUAKE_TIMER      0x8185E9BCu /* s32 m_quakeTimer[8] */
#define PY_QUAKE_EFFECT     0x8185E9DCu /* s32 m_quakeEffectFlag[8] */
#define PY_REST             0x81851D8Cu /* s32 mRest[8 characters]: lives (initialised data: 5 each) */
#define PY_DEFAULT_TYPES    0x81849BE4u /* dMj2dGame_c::scDefaultPlayerTypes[8] */
#define PY_MODEL_TYPES      0x818494E4u /* the course-in model per character (a table of 8 s32) */
#define PY_PANIC_STRINGS    0x818494E4u /* (the same block: the file name at +84, format at +125 / +167) */
/* ---- the game's scalars (.sdata) */
#define PY_NUM              0x80429CA0u /* s32 mNum: players in play */
#define PY_CTRL_PLR_NO      0x80429CA4u /* s32 mCtrlPlrNo: the player whose view leads */
#define PY_OLD_ACT_INFO     0x80429CA8u /* u8 mOldActPlayerInfo */
#define PY_SCORE            0x80429CC0u /* s32 mScore */
#define PY_KINOPIO_MODE     0x80429CC4u /* PLAYER_MODE_e mKinopioMode: the rescued Toad's power-up */
#define PY_BGM_STATE        0x80429CE4u /* u32 mBgmState: 1 star music, 2 Yoshi drums */
#define PY_BONUS_NO_CAP     0x80429CE8u /* s32 mBonusNoCap */
#define PY_KINOPIO_CARRY    0x80429CECu /* s32 mKinopioCarryCount */
#define SND_SCENE_MGR       0x8042A4A8u /* SndSceneMgr::sInstance (a pointer) */
#define SCORE_MAX           999999999

/* ---- other classes: guest functions and their natives */
void hle_getPlayer__9daPyMng_cFi(ppc_context *ctx, uint8_t *base);      /* daPyMng_c::getPlayer (rt_aspect.c) */
void hle_search__7fBase_cFUi(ppc_context *ctx, uint8_t *base);          /* fManager_c::searchBaseByID (gm_f_manager.c) */
void hle_create__13dStageActor_cF6ActorsUiP7Point3dP6S16VecUc(ppc_context *ctx, uint8_t *base);   /* dActor_c::construct (gm_d_actor.c) */
#define A_SET_STAR_HALF     0x80060460u /* (a player's star music: which half) */
#define A_SND_ON            0x8019BC50u /* SndSceneMgr::onSoundFlag(flags) */
#define A_SND_OFF           0x8019BD20u /* SndSceneMgr::offSoundFlag(flags) */
#define A_TEST_FLAG         0x80056CF0u /* daPlBase_c::testFlag(flag) */
#define A_OSPANIC           0x818380F8u
#define PL_STAR_TIMER       4208        /* dAcPy_c: the star's frames left (s32) */
#define PL_BALLOON          5436        /* dAcPy_c: 1 = in a bubble */
#define VT_YOSHI_PLR_NO     108         /* (virtual: the Yoshi's rider number, a pointer to an s8) */
#define VT_IS_ALIVE         224         /* (virtual: the player can play on) */
#define VT_EXECUTE_LAST     216         /* (virtual: the last step of the frame) */
#define VT_EXECUTE_LAST_ALL 220
#define FLAG_YOSHI_RIDE     75

/* (gm_i2.h's helpers under this file's names) */
#define nonzero(p_, t, d, v) i2_nonzero(ctx, (t), (d), (v))
#define bit(n) i2_bit(n)
#define vcall(p_, ra, obj, slot) i2_vcall(ctx, base, (ra), (obj), (slot), 4)
#define vcall_t(p_, ra, obj, slot, t) i2_vcall(ctx, base, (ra), (obj), (slot), (t))
#define PY_FN(a) I2_FN(a)

/* ================================================================== counts and sums */
/* getEntryNum: how many players take part */
static uint32_t py_getEntryNum(GM_CTX) {
    uint32_t n = 0;
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        R(4) = PY_ENTRY + 4 * p;
        n += nonzero(GM_PASS, 6, 5, gm_u32(R(4)));
        R(3) = n;
        if (--ctx->ctr) GM_LOOP();
    }
    return n;
}
/* getNumInGame: players taking part who have lives left */
static uint32_t py_getNumInGame(GM_CTX) {
    uint32_t n = 0;
    R(8) = 0x81850000u; R(5) = PY_REST;
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        R(4) = PY_ENTRY + 4 * p;
        R(6) = gm_u32(R(4));
        int in = CMPU(R(6), 0) != 0;
        R(6) = PY_TYPE + 4 * p;
        if (in) {
            R(7) = gm_u32(PY_REST + 4 * gm_u32(PY_TYPE + 4 * p));
            if (CMPS(R(7), 0) > 0) n++;
            R(7) = n; R(3) = n;
        }
        R(7) = R(6);
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    R(3) = n;
    return n;
}
/* getCoinAll: the coins of all characters */
static uint32_t py_getCoinAll(GM_CTX) {
    uint32_t n = 0;
    ctx->ctr = 8;
    for (uint32_t c = 0; c < 8; c++) {
        R(4) = PY_COIN + 4 * c; R(5) = gm_u32(R(4));
        n += R(5); R(3) = n;
        if (--ctx->ctr) GM_LOOP();
    }
    return n;
}
/* getPlayerIndex (findPlayerWithType): the player playing a character, else -1 */
static int32_t py_findPlayerWithType(GM_CTX, uint32_t type) {
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        R(4) = p; R(5) = PY_TYPE + 4 * p; R(6) = gm_u32(R(5));
        if (CMPU(R(6), type) == 0) { R(3) = p; return (int32_t)p; }
        R(4) = p + 1;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    R(4) = (uint32_t)-1; R(3) = R(4);
    return -1;
}

/* ================================================================== start of a game / a stage */
/* setDefaultParam: 5 lives and no coins for each character, no player / Yoshi IDs, no score */
static void py_setDefaultParam(GM_CTX) {
    R(3) = 0; R(4) = 5; R(5) = PY_REST; R(9) = PY_COIN;
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        uint32_t t = gm_u32(PY_TYPE + 4 * p);
        gm_set_u32(PY_YOSHI_ID + 4 * p, 0);
        gm_set_u32(PY_PLAYER_ID + 4 * p, 0);
        gm_set_u32(PY_REST + 4 * t, 5);
        gm_set_u32(PY_COIN + 4 * t, 0);
        R(6) = PY_YOSHI_ID + 4 * p; R(7) = PY_PLAYER_ID + 4 * p; R(8) = PY_TYPE + 4 * p; R(10) = t << 2;
        if (--ctx->ctr) GM_LOOP();
    }
    gm_set_u32(PY_SCORE, 0);
    R(3) = 0x80430000u; R(4) = 0;
}
/* initGame: player 1 in play, the default characters, nobody taking part, no power-ups / items */
static void py_initGame(GM_CTX) {
    PY_FN(0x8180574Cu);
    gm_set_u8(PY_OLD_ACT_INFO, gm_u8(PY_OLD_ACT_INFO) | 1);
    gm_set_u32(PY_ACT_INFO + 4, gm_u32(PY_ACT_INFO + 4) | 1);
    for (uint32_t p = 0; p < 8; p++) {
        uint32_t t = gm_u32(PY_DEFAULT_TYPES + 4 * p);
        gm_set_u32(PY_ENTRY + 4 * p, 0);
        gm_set_u32(PY_TYPE + 4 * p, t);
        gm_set_u32(PY_MODE + 4 * t, 0);
        gm_set_u32(PY_CREATE_ITEM + 4 * t, 0);
        if (p < 7) GM_LOOP();
    }
    ctx->lr = 0x818057DCu; py_setDefaultParam(GM_PASS);
    gm_set_u32(PY_BONUS_NO_CAP, 0);
    gm_set_u32(PY_KINOPIO_CARRY, 0);
    R(3) = 0x80430000u; R(4) = 0;
}
/* checkCorrectCreateInfo: clamp what a save or a mod may have left out of range - characters
   (0-7), power-ups (0-6), lives (99 at most), all coins (over 99 between them: none), the score */
static void py_checkCorrectCreateInfo(GM_CTX) {
    R(3) = 0; R(4) = PY_MODE; R(5) = PY_REST; R(7) = 5;
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        R(6) = PY_TYPE + 4 * p;
        R(8) = gm_u32(R(6));
        if (CMPU(R(8), 8) >= 0) { R(8) = 0; gm_set_u32(R(6), 0); }   /* (an unknown character: Mario) */
        R(8) <<= 2;
        R(9) = PY_MODE + R(8); R(10) = gm_u32(R(9));
        if (CMPU(R(10), 7) >= 0) gm_set_u32(R(9), 0);                 /* (power-up: none) */
        R(9) = PY_REST + R(8); R(8) = gm_u32(R(9));
        if (CMPU(R(8), 100) >= 0) gm_set_u32(R(9), 5);               /* (lives: 5) */
        if (--ctx->ctr) GM_LOOP();
    }
    R(3) = 0; ctx->ctr = 8;
    for (uint32_t c = 0; c < 8; c++) {
        R(4) = PY_COIN + 4 * c; R(5) = gm_u32(R(4)); R(3) += R(5);
        if (--ctx->ctr) GM_LOOP();
    }
    if (CMPU(R(3), 100) >= 0) {
        R(4) = 0; ctx->ctr = 8;
        for (uint32_t c = 0; c < 8; c++) {
            R(3) = PY_COIN + 4 * c; gm_set_u32(R(3), 0);
            if (--ctx->ctr) GM_LOOP();
        }
    }
    R(3) = 0x80430000u; R(5) = gm_u32(PY_SCORE); R(4) = SCORE_MAX;
    if (CMPS(R(5), R(4)) > 0) gm_set_u32(PY_SCORE, SCORE_MAX);
}
/* checkBonusNoCap: no extra-life cap while Mario has 99 lives */
static void py_checkBonusNoCap(GM_CTX) {
    R(3) = gm_u32(PY_REST);
    int over = CMPS(R(3), 98) > 0;
    R(3) = over; R(4) = 0x80430000u;
    gm_set_u32(PY_BONUS_NO_CAP, R(3));
}
/* decideCtrlPlrNo: the first player in play leads the view (none in play: unchanged) */
static void py_decideCtrlPlrNo(GM_CTX) {
    R(3) = PY_ACT_INFO;                                  /* (lwzu r4, -6008(r3)) */
    R(5) = 8;
    R(4) = gm_u32(PY_ACT_INFO + 4);
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        R(3) = p;
        R(5) = (p > 31 ? 0 : R(4) >> p) & 1; CR0(ctx, R(5));
        if (R(5)) { R(4) = 0x80430000u; gm_set_u32(PY_CTRL_PLR_NO, p); return; }
        R(3) = p + 1;
        if (--ctx->ctr == 0) return;
        GM_LOOP();
    }
}
/* initKinopioPlayer(mode, player): the rescued Toad joins as that player */
static void py_initKinopioPlayer(GM_CTX, uint32_t mode, uint32_t p) {
    R(7) = 0x80430000u;
    R(5) = 1; R(10) = p << 2;
    uint32_t b = bit(p); R(4) = b;
    R(9) = gm_u8(PY_OLD_ACT_INFO) | b;
    R(6) = 0x81860000u; R(8) = PY_ENTRY;
    gm_set_u8(PY_OLD_ACT_INFO, (uint8_t)R(9));
    R(7) = 8;
    R(9) = gm_u32(PY_ACT_INFO); R(6) = PY_ACT_INFO;      /* (lwzu) */
    gm_set_u32(PY_ENTRY + R(10), 1);
    R(8) = gm_u32(PY_TYPE + R(10));
    R(10) = (uint32_t)((int32_t)b >> 31); ctx->xer_ca = (int32_t)b < 0 && (b & 0x7FFFFFFFu);   /* (srawi: the high word of 1 << p) */
    R(9) |= R(10);
    R(10) = gm_u32(PY_ACT_INFO + 4);
    R(5) = PY_CREATE_ITEM;
    R(8) <<= 2;
    R(4) = R(10) | b;
    gm_set_u32(PY_ACT_INFO + 4, R(4));
    R(4) = 0x80430000u;
    gm_set_u32(PY_ACT_INFO, R(9));
    gm_set_u32(PY_CREATE_ITEM + R(8), 8);                /* (PLAYER_CREATE_ITEM_e::RESCUE_TOAD) */
    gm_set_u32(PY_KINOPIO_MODE, mode);
}

/* ================================================================== players in play */
/* addNum(player): the player comes into play (once); returns its number (bit index) */
static uint32_t py_addNum(GM_CTX, uint32_t p) {
    PY_FN(0x81805BE8u);
    uint32_t b = bit(p);
    R(4) = PY_ACT_INFO; R(6) = gm_u32(PY_ACT_INFO); R(5) = b;
    R(7) = (uint32_t)((int32_t)b >> 31); ctx->xer_ca = (int32_t)b < 0 && (b & 0x7FFFFFFFu);
    R(4) = gm_u32(PY_ACT_INFO + 4);
    R(8) = R(6) & R(7);
    R(9) = R(4) & R(5);
    uint32_t was = R(9) | R(8);                          /* (already in play: the bits it has) */
    CR0(ctx, was);
    R(8) = 0x81860000u;
    if (was == 0) {
        R(9) = 0x80430000u;
        R(10) = gm_u8(PY_OLD_ACT_INFO);
        R(6) |= R(7); R(8) = PY_ACT_INFO;
        gm_set_u32(PY_ACT_INFO, R(6));
        R(4) |= R(5);
        gm_set_u32(PY_ACT_INFO + 4, R(4));
        R(4) = R(10) | R(5);
        gm_set_u8(PY_OLD_ACT_INFO, (uint8_t)R(4));
        NV_R(30, was);
        R(3) = p; BL(0x81805C64u, hle_getPlayer__9daPyMng_cFi);
        int count = 1;
        if (CMPU(R(3), 0) != 0) {                         /* a player that is alive counts */
            vcall(GM_PASS, 0x81805C7Cu, R(3), VT_IS_ALIVE);
            count = CMPU(R(3), 0) == 0;
        }
        if (count) {
            R(3) = 0x80430000u; R(4) = gm_u32(PY_NUM);
            if (CMPS(R(4), 7) <= 0) { R(4)++; gm_set_u32(PY_NUM, R(4)); }
        }
        GM_LOOP();                                       /* (the jump back to the return) */
    }
    R(3) = cntlzw(was) >> 5;                             /* (was == 0) */
    return R(3);
}
/* decNum(player): the player leaves play; returns whether it was in play */
static uint32_t py_decNum(GM_CTX, uint32_t p) {
    PY_FN(0x81806C94u);
    uint32_t b = bit(p);
    R(4) = PY_ACT_INFO; R(6) = gm_u32(PY_ACT_INFO); R(5) = b;
    R(7) = (uint32_t)((int32_t)b >> 31); ctx->xer_ca = (int32_t)b < 0 && (b & 0x7FFFFFFFu);
    R(4) = gm_u32(PY_ACT_INFO + 4);
    R(7) &= R(6);
    R(8) = R(4) & R(5);
    uint32_t was = R(8) | R(7);
    CR0(ctx, was);
    R(7) = 0x81860000u;
    if (was) {
        R(9) = 0x80430000u;
        R(8) = ~b;
        R(10) = gm_u8(PY_OLD_ACT_INFO);
        R(8) = (uint32_t)((int32_t)R(8) >> 31); ctx->xer_ca = (int32_t)~b < 0 && (~b & 0x7FFFFFFFu);
        R(6) &= R(8); R(7) = PY_ACT_INFO;
        gm_set_u32(PY_ACT_INFO, R(6));
        R(4) &= ~b;
        gm_set_u32(PY_ACT_INFO + 4, R(4));
        R(4) = R(10) & ~b;
        gm_set_u8(PY_OLD_ACT_INFO, (uint8_t)R(4));
        NV_R(30, was);
        R(3) = p; BL(0x81806CFCu, hle_getPlayer__9daPyMng_cFi);
        int count = 1;
        if (CMPU(R(3), 0) != 0) {
            vcall(GM_PASS, 0x81806D14u, R(3), VT_IS_ALIVE);
            count = CMPU(R(3), 0) == 0;
        }
        if (count) {
            R(3) = 0x80430000u; R(4) = gm_u32(PY_NUM);
            if (CMPS(R(4), 0) > 0) { R(4)--; gm_set_u32(PY_NUM, R(4)); }
        }
        /* the view goes to the first player still in play */
        R(3) = PY_ACT_INFO; R(4) = gm_u32(PY_ACT_INFO); R(5) = 8;
        R(4) = gm_u32(PY_ACT_INFO + 4);
        ctx->ctr = 8;
        for (uint32_t q = 0; q < 8; q++) {
            R(3) = q;
            R(5) = (R(4) >> q) & 1; CR0(ctx, R(5));
            if (R(5)) { R(4) = 0x80430000u; gm_set_u32(PY_CTRL_PLR_NO, q); break; }
            R(3) = q + 1;
            if (--ctx->ctr == 0) break;
            GM_LOOP();
        }
    }
    return nonzero(GM_PASS, 3, 3, was);
}
/* addNum() / decNum(): mNum alone (at most 8, at least 0) */
static void py_addNumOnly(GM_CTX) {
    R(4) = 0x80430000u; R(3) = gm_u32(PY_NUM);
    if (CMPS(R(3), 7) > 0) return;
    R(5) = R(3) + 1; gm_set_u32(PY_NUM, R(5));
}
static void py_decNumOnly(GM_CTX) {
    R(4) = 0x80430000u; R(3) = gm_u32(PY_NUM);
    if (CMPS(R(3), 0) <= 0) return;
    R(5) = R(3) - 1; gm_set_u32(PY_NUM, R(5));
}
/* isCreateBalloon(player): the player starts in a bubble - a bubble item, or no lives left */
static uint32_t py_isCreateBalloon(GM_CTX, uint32_t p) {
    R(3) = gm_u32(PY_TYPE + 4 * p);
    R(5) = 0x81860000u;
    R(4) = R(3) << 2;
    R(3) = gm_u8(PY_CREATE_ITEM + R(4) + 3) & 4; CR0(ctx, R(3));
    if (R(3)) { R(3) = 1; return 1; }
    R(3) = gm_u32(PY_REST + R(4));
    int lives = CMPS(R(3), 0) > 0;
    R(3) = !lives;
    return R(3);
}
/* create(player, position, gotoKind, faceLeft): the player's actor, if it takes part */
static uint32_t py_create(GM_CTX, uint32_t p, gptr pos, uint32_t goto_kind, uint32_t face_left) {
    PY_FN(0x81805D38u);
    R(7) = PY_ENTRY; R(8) = p << 2;
    uint32_t entry = gm_u32(PY_ENTRY + R(8));
    NV_R(30, entry);
    if (CMPU(entry, 0) != 0) {
        R(7) = pos;
        R(4) = (face_left << 24 & 0xFF000000u) | (goto_kind << 16 & 0xFF0000u) | (p & 0x3F);
        R(3) = 13;                                        /* (dProf::PLAYER) */
        R(5) = R(7); R(6) = 0; R(7) = 0;
        BL(0x81805D84u, hle_create__13dStageActor_cF6ActorsUiP7Point3dP6S16VecUc);
    }
    return nonzero(GM_PASS, 3, 3, entry);
}

/* ================================================================== Yoshis */
/* setYoshi(yoshi): note a Yoshi's ID in the first free slot; false when full or null */
static uint32_t py_setYoshi(GM_CTX, gptr yoshi) {
    R(4) = yoshi;
    int none = CMPU(yoshi, 0) == 0;
    R(3) = 0;
    if (none) return 0;
    R(5) = 8; ctx->ctr = 8;
    for (uint32_t i = 0;; i++) {
        R(5) = PY_YOSHI_ID + 4 * i; R(6) = gm_u32(R(5));
        if (CMPU(R(6), 0) == 0) { R(3) = gm_u32(yoshi); gm_set_u32(R(5), R(3)); R(3) = 1; return 1; }
        GM_LOOP();
        if (--ctx->ctr == 0) return 0;
    }
}
/* releaseYoshi(yoshi): forget its slot */
static void py_releaseYoshi(GM_CTX, gptr yoshi) {
    R(4) = 8;
    uint32_t id = gm_u32(yoshi); R(3) = id;
    ctx->ctr = 8;
    for (uint32_t i = 0;; i++) {
        R(4) = PY_YOSHI_ID + 4 * i; R(5) = gm_u32(R(4));
        if (CMPU(R(5), id) == 0) { R(3) = 0; gm_set_u32(R(4), 0); return; }
        GM_LOOP();
        if (--ctx->ctr == 0) return;
    }
}
/* getYoshi(player): the Yoshi that player rides, else null */
static gptr py_getYoshi(GM_CTX, uint32_t p) {
    PY_FN(0x81806928u);
    NV_R(30, p);
    gptr found = 0;
    for (uint32_t i = 0, left = 8;; i++) {
        NV_R(27, PY_YOSHI_ID + 4 * i); NV_R(28, left);
        R(3) = gm_u32(PY_YOSHI_ID + 4 * i);
        BL(0x81806960u, hle_search__7fBase_cFUi);
        if (CMPU(R(3), 0) != 0) {
            gptr y = R(3); NV_R(29, y);
            vcall_t(GM_PASS, 0x81806980u, y, VT_YOSHI_PLR_NO, 3);
            R(3) = (uint32_t)(int32_t)(int8_t)gm_u8(R(3));
            if (CMPU(R(3), p) == 0) { found = y; break; }
        }
        left--; NV_R(28, left);
        if (CMPU(left, 0) <= 0) { NV_R(29, 0); break; }
        GM_LOOP();
    }
    R(3) = found;
    return found;
}
/* getYoshiNum: how many Yoshis are out */
static uint32_t py_getYoshiNum(GM_CTX) {
    PY_FN(0x818069C4u);
    uint32_t n = 0; NV_R(30, 0);
    for (uint32_t i = 0, left = 8;; i++) {
        NV_R(28, PY_YOSHI_ID + 4 * i); NV_R(29, left);
        R(3) = gm_u32(PY_YOSHI_ID + 4 * i);
        BL(0x818069F8u, hle_search__7fBase_cFUi);
        left--;
        n += nonzero(GM_PASS, 4, 3, R(3));
        NV_R(29, left); NV_R(30, n);
        if (CMPU(left, 0) <= 0) break;
        GM_LOOP();
    }
    R(3) = n;
    return n;
}
/* getCourseInPlayerModelType(player): the model a player enters the course with (4: Toad rescue) */
static uint32_t py_getCourseInPlayerModelType(GM_CTX, uint32_t p) {
    R(3) = gm_u32(PY_TYPE + 4 * p);
    R(5) = 0x81860000u;
    R(4) = R(3) << 2;
    R(3) = gm_u8(PY_CREATE_ITEM + R(4) + 3) & 8; CR0(ctx, R(3));
    if (R(3)) { R(3) = 4; return 4; }
    R(3) = gm_u32(PY_MODEL_TYPES + R(4));
    return R(3);
}
/* setCarryOverYoshiInfo(player, color, fruit) / getYoshiColor / getYoshiFruit: a Yoshi kept for the next course */
static void py_setCarryOverYoshiInfo(GM_CTX, uint32_t p, uint32_t color, uint32_t fruit) {
    R(6) = PY_YOSHI_COLOR; gm_set_u8(PY_YOSHI_COLOR + p, (uint8_t)color);
    R(3) = p << 2; R(4) = PY_YOSHI_FRUIT; gm_set_u32(PY_YOSHI_FRUIT + R(3), fruit);
}
static uint32_t py_getYoshiColor(GM_CTX, uint32_t p) { R(4) = PY_YOSHI_COLOR; return R(3) = gm_u8(PY_YOSHI_COLOR + p); }
static uint32_t py_getYoshiFruit(GM_CTX, uint32_t p) { R(4) = PY_YOSHI_FRUIT; return R(3) = gm_u32(PY_YOSHI_FRUIT + 4 * p); }

/* ================================================================== the view, the music, the frame */
/* getActScrollInfo: a bit per player whose actor the view follows (taking part, not in a bubble) */
static uint32_t py_getActScrollInfo(GM_CTX) {
    PY_FN(0x81806B40u);
    uint32_t bits = 0;
    NV_R(27, 1);
    for (uint32_t p = 0, left = 8;; p++) {
        NV_R(26, PY_ENTRY + 4 * p); NV_R(28, left); NV_R(29, p); NV_R(30, bits);
        R(3) = gm_u32(PY_ENTRY + 4 * p);
        if (CMPU(R(3), 0) != 0) {
            R(3) = p; BL(0x81806B90u, hle_getPlayer__9daPyMng_cFi);
            int follow = 1;
            if (CMPU(R(3), 0) != 0) { R(3) = gm_u8(R(3) + PL_BALLOON); follow = CMPU(R(3), 1) != 0; }
            if (follow) { R(3) = bit(p); bits |= R(3); NV_R(30, bits); }
        }
        left--; NV_R(28, left); NV_R(29, p + 1);
        if (CMPU(left, 0) <= 0) break;
        GM_LOOP();
    }
    R(3) = bits;
    return bits;
}
/* getScrollNum: how many players the view follows */
static uint32_t py_getScrollNum(GM_CTX) {
    PY_FN(0x81806BE4u);
    uint32_t n = 0;
    for (uint32_t p = 0, left = 8;; p++) {
        NV_R(27, PY_ENTRY + 4 * p); NV_R(28, n); NV_R(29, left); NV_R(30, p);
        R(3) = gm_u32(PY_ENTRY + 4 * p);
        if (CMPU(R(3), 0) != 0) {
            R(3) = p; BL(0x81806C2Cu, hle_getPlayer__9daPyMng_cFi);
            int follow = 1;
            if (CMPU(R(3), 0) != 0) { R(3) = gm_u8(R(3) + PL_BALLOON); follow = CMPU(R(3), 1) != 0; }
            if (follow) { n++; NV_R(28, n); }
        }
        left--; NV_R(29, left); NV_R(30, p + 1);
        if (CMPU(left, 0) <= 0) break;
        GM_LOOP();
    }
    R(3) = n & 0xFF;
    return R(3);
}
/* getCourseInListPlrNo(i): the i-th player to enter the course (out of range: OSPanic) */
static uint32_t py_getCourseInListPlrNo(GM_CTX, int32_t i) {
    PY_FN(0x81806DDCu);
    if (CMPS(i, 8) < 0) { R(4) = PY_COURSE_IN_LIST; R(3) = gm_u32(PY_COURSE_IN_LIST + 4 * (uint32_t)i); return R(3); }
    R(4) = PY_PANIC_STRINGS; R(3) = R(4) + 84; R(5) = R(4) + 125; R(6) = R(4) + 167;
    ctx->cr &= ~(1u << (31 - 6));                         /* (crclr 6: no float arguments) */
    R(4) = 736;
    BL(0x81806E30u, mod_OSPanic_818380F8);               /* (does not return) */
    return R(3);
}
/* incRestAll(n): a life (or n) for every player taking part, with the 1-up effect */
static void py_incRestAll(GM_CTX, uint32_t n) {
    PY_FN(0x818070C0u);
    NV_R(30, n); NV_R(26, GAME_RULE);
    for (uint32_t p = 0, left = 8;; p++) {
        NV_R(27, PY_ENTRY + 4 * p); NV_R(28, left); NV_R(29, p);
        R(3) = gm_u32(PY_ENTRY + 4 * p);
        if (CMPU(R(3), 0) != 0) {
            R(3) = gm_u8(GAME_RULE + GR_INFINITE_LIVES);
            R(5) = n; R(4) = R(3) ^ 1; R(3) = p;
            ctx->lr = 0x81807120u; fn_80060460(ctx, base);   /* incRest(player, !infinite lives, n) */
        }
        left--; NV_R(28, left); NV_R(29, p + 1);
        if (CMPU(left, 0) <= 0) break;
        GM_LOOP();
    }
}
/* setCourseInStarBGM: the star music / Yoshi drums carried into the course start again */
static void py_setCourseInStarBGM(GM_CTX) {
    PY_FN(0x81807154u);
    NV_R(30, 0x80430000u);
    R(3) = gm_u32(PY_BGM_STATE);
    R(4) = R(3) & 1; CR0(ctx, R(4));
    if (R(4)) {
        R(3) = gm_u32(SND_SCENE_MGR); R(4) = 4;
        BL(0x81807184u, fn_8019bd90__11SndSceneMgrFi_8019BC50);
        R(3) = gm_u32(PY_BGM_STATE);
    }
    R(3) &= 2; CR0(ctx, R(3));
    if (R(3)) {
        R(3) = gm_u32(SND_SCENE_MGR); R(4) = 512;
        BL(0x818071A0u, fn_8019bd90__11SndSceneMgrFi_8019BC50);
    }
}
/* stopStarBGM: the star music ends once no player has more than a second of star left */
static void py_stopStarBGM(GM_CTX) {
    PY_FN(0x818071B4u);
    R(3) = gm_u8(PY_BGM_STATE + 3) & 1; CR0(ctx, R(3));
    if (!R(3)) return;
    for (uint32_t p = 0, left = 8;; p++) {
        NV_R(29, left); NV_R(30, p);
        R(3) = p; BL(0x818071ECu, hle_getPlayer__9daPyMng_cFi);
        if (CMPU(R(3), 0) != 0) {
            R(3) = gm_u32(R(3) + PL_STAR_TIMER);
            if (CMPS(R(3), 59) > 0) return;              /* (still a star: the music goes on) */
        }
        left--; NV_R(29, left); NV_R(30, p + 1);
        if (CMPU(left, 0) <= 0) break;
        GM_LOOP();
    }
    R(3) = 0x80430000u; R(4) = gm_u32(PY_BGM_STATE) & ~1u; gm_set_u32(PY_BGM_STATE, R(4));
    R(3) = gm_u32(SND_SCENE_MGR); R(4) = 4;
    BL(0x81807230u, fn_8019be60__11SndSceneMgrFi_8019BD20);
}
/* stopYoshiBGM: the Yoshi drums end once nobody rides a Yoshi */
static void py_stopYoshiBGM(GM_CTX) {
    PY_FN(0x81807248u);
    R(3) = gm_u8(PY_BGM_STATE + 3) & 2; CR0(ctx, R(3));
    if (!R(3)) return;
    for (uint32_t p = 0, left = 8;; p++) {
        NV_R(29, left); NV_R(30, p);
        R(3) = p; BL(0x81807280u, hle_getPlayer__9daPyMng_cFi);
        if (CMPU(R(3), 0) != 0) {
            R(4) = FLAG_YOSHI_RIDE; BL(0x81807290u, testFlag__10daPlBase_cFi_80056CF0);
            if (CMPU(R(3), 0) != 0) return;
        }
        left--; NV_R(29, left); NV_R(30, p + 1);
        if (CMPU(left, 0) <= 0) break;
        GM_LOOP();
    }
    R(3) = 0x80430000u; R(4) = gm_u32(PY_BGM_STATE) & ~2u; gm_set_u32(PY_BGM_STATE, R(4));
    R(3) = gm_u32(SND_SCENE_MGR); R(4) = 512;
    BL(0x818072C8u, fn_8019be60__11SndSceneMgrFi_8019BD20);
}
/* executeLastPlayer / executeLastAll: the frame's last step for each Yoshi, then each player */
static void py_executeLast(GM_CTX, uint32_t slot, const uint32_t ra[4]) {
    for (uint32_t i = 0, left = 8;; i++) {
        NV_R(29, PY_YOSHI_ID + 4 * i); NV_R(30, left);
        R(3) = gm_u32(PY_YOSHI_ID + 4 * i);
        BL(ra[0], hle_search__7fBase_cFUi);
        if (CMPU(R(3), 0) != 0) vcall(GM_PASS, ra[1], R(3), slot);
        left--; NV_R(30, left);
        if (CMPU(left, 0) <= 0) break;
        GM_LOOP();
    }
    for (uint32_t p = 0, left = 8;; p++) {
        NV_R(29, left); NV_R(30, p);
        R(3) = p; BL(ra[2], hle_getPlayer__9daPyMng_cFi);
        if (CMPU(R(3), 0) != 0) vcall(GM_PASS, ra[3], R(3), slot);
        left--; NV_R(29, left); NV_R(30, p + 1);
        if (CMPU(left, 0) <= 0) break;
        GM_LOOP();
    }
}
static void py_executeLastPlayer(GM_CTX) {
    PY_FN(0x818072E0u);
    static const uint32_t ra[4] = { 0x8180730Cu, 0x81807324u, 0x81807340u, 0x81807358u };
    py_executeLast(GM_PASS, VT_EXECUTE_LAST, ra);
}
static void py_executeLastAll(GM_CTX) {
    PY_FN(0x81807380u);
    static const uint32_t ra[4] = { 0x818073ACu, 0x818073C4u, 0x818073E0u, 0x818073F8u };
    py_executeLast(GM_PASS, VT_EXECUTE_LAST_ALL, ra);
}

/* ================================================================== a stage starts, a frame ends */
void hle_setPlayer__9daPyMng_cFiP7dAcPy_c(ppc_context *ctx, uint8_t *base);   /* daPyMng_c::setPlayer */
#define DSCSTAGE_IS_COURSE_IN 0x8042A21Cu  /* dScStage_c::m_isCourseIn (u8) */
#define DINFO_INSTANCE      0x80429F7Cu  /* dInfo_c::m_instance */
#define INFO_CYUUKAN_INDEX  2804         /* dInfo_c: s32 mCyuukanIndex */
#define INFO_KINOPIO_IN_CHUKAN 36        /* dInfo_c: bool mCyuukan.mIsKinopioInChukan */
#define PY_TIME_UP_NUM      0x80429CC8u  /* mTimeUpPlayerNum, then mAllBalloon, mPauseEnableInfo, mPauseDisable, */
#define PY_PAUSE_DISABLE    0x80429CD4u  /*   mStopTimerInfo, mStopTimerInfoOld, mQuakeTrigger (7 words) */
#define PY_STOP_TIMER       0x80429CD8u
#define PY_STOP_TIMER_OLD   0x80429CDCu
#define PY_QUAKE_TRIGGER    0x80429CE0u
#define DEMO_MNG_INSTANCE   0x80429C94u  /* daPyDemoMng_c::mspInstance */
#define MULTI_MNG_INSTANCE  0x80429FB0u  /* dMultiMng_c::mspInstance */
#define DNEXT_INSTANCE      0x80429FC0u  /* dNext_c::m_instance: +24 m_exitReq (u8), +28 m_timer (u16) */
#define DQUAKE_INSTANCE     0x8042A008u  /* dQuake_c::m_instance: +48 mFlags (u32) */
#define PAUSE_MNG_INSTANCE  0x80429FD8u  /* PauseManager_c::m_instance */
#define STAGE_TIMER_INSTANCE 0x8042A070u /* dStageTimer_c::m_instance: +12 m_isStop */
#define PY_EFFECT_INSTANCE  0x80429FF0u  /* dPyEffectMng_c::mspInstance */
#define VT_IS_WAIT_FRAME_MAX 880         /* (virtual: daPlBase_c::isWaitFrameCountMax) */

/* initStage: nobody in play yet; the entries come into play; with one player at a checkpoint
   where a Toad was being carried, the Toad joins as the first free player; the counters cleared */
static void py_initStage(GM_CTX) {
    PY_FN(0x81805870u);
    BL(0x81805894u, hle_mod_fn_80061160);                                /* checkCorrectCreateInfo */
    R(3) = 0x80430000u; NV_R(29, 0); R(5) = 0x80430000u;
    gm_set_u32(PY_NUM, 0);
    R(3) = 0x81860000u; gm_set_u8(PY_OLD_ACT_INFO, 0);
    R(5) = 0x81860000u; R(4) = PY_ACT_INFO;
    R(3) = PY_STAR_TIME; R(5) = PY_STAR_COUNT; NV_R(28, 8);
    gm_set_u32(PY_ACT_INFO, 0);
    NV_R(27, PY_STAR_TIME - 2); NV_R(26, PY_STAR_COUNT - 2); NV_R(30, 0);
    gm_set_u32(PY_ACT_INFO + 4, 0);
    for (uint32_t p = 0;; ) {                                            /* no player actors, no stars */
        R(3) = p; R(4) = 0; BL(0x818058E0u, hle_setPlayer__9daPyMng_cFiP7dAcPy_c);
        NV_R(28, R(28) - 1);
        NV_R(27, PY_STAR_TIME + 2 * p); gm_set_u16(R(27), 0);
        int more = CMPU(R(28), 0) > 0;
        NV_R(26, PY_STAR_COUNT + 2 * p); gm_set_u16(R(26), 0);
        NV_R(30, ++p);
        if (!more) break;
        GM_LOOP();
    }
    R(3) = PY_ENTRY; NV_R(29, 8); NV_R(28, PY_ENTRY - 4); NV_R(30, 0);
    for (uint32_t p = 0;; ) {                                            /* the entries come into play */
        NV_R(28, PY_ENTRY + 4 * p); R(3) = gm_u32(R(28));
        if (CMPU(R(3), 0) != 0) { R(3) = p; BL(0x81805920u, hle_mod_addNum__9daPyMng_cFi); }
        NV_R(29, R(29) - 1);
        int more = CMPU(R(29), 0) > 0;
        NV_R(30, ++p);
        if (!more) break;
        GM_LOOP();
    }
    /* the Toad carried to a checkpoint comes back, as the first free player */
    R(3) = gm_u8(DSCSTAGE_IS_COURSE_IN);
    if (CMPU(R(3), 0) == 0) goto counters;
    R(3) = gm_u32(DINFO_INSTANCE); R(4) = gm_u32(R(3) + INFO_CYUUKAN_INDEX);
    if (CMPS(R(4), 0) < 0) goto counters;
    R(4) = 0; ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {                                   /* (isOnePlayer: the entries) */
        R(5) = PY_ENTRY + 4 * p; R(6) = gm_u32(R(5));
        R(4) += NONZERO(7, 6, R(6));
        if (--ctx->ctr) GM_LOOP();
    }
    if (CMPU(R(4), 1) != 0) goto counters;
    R(3) = gm_u8(R(3) + INFO_KINOPIO_IN_CHUKAN);
    if (CMPU(R(3), 1) != 0) goto counters;
    R(3) = 0; ctx->ctr = 8;
    for (uint32_t p = 0;; p++) {
        R(4) = PY_ENTRY + 4 * p; R(5) = gm_u32(R(4));
        if (CMPU(R(5), 0) == 0) break;
        R(3) = p + 1;
        if (--ctx->ctr == 0) goto counters;
        GM_LOOP();
    }
    {   /* (initKinopioPlayer(NONE, p) inline - the low word of mActPlayerInfo only) */
        uint32_t p = R(3);
        R(6) = 0x80430000u; R(7) = gm_u8(PY_OLD_ACT_INFO); R(5) = 1;
        gm_set_u32(R(4), 1);
        R(4) = p << 2; R(3) = i2_bit(p);
        R(8) = 0x81860000u; R(7) |= R(3); R(5) = 0x81860000u;
        gm_set_u8(PY_OLD_ACT_INFO, (uint8_t)R(7));
        R(7) = PY_ACT_INFO; R(8) = gm_u32(PY_ACT_INFO + 4);
        R(5) = PY_TYPE; R(4) = gm_u32(PY_TYPE + R(4));
        R(6) = 0x81860000u; R(3) = R(8) | R(3); R(5) = 8; R(6) = PY_CREATE_ITEM;
        gm_set_u32(PY_ACT_INFO + 4, R(3));
        R(3) = R(4) << 2; R(8) = 0x80430000u;
        gm_set_u32(PY_CREATE_ITEM + R(3), 8);                            /* (RESCUE_TOAD) */
        R(3) = 0; gm_set_u32(PY_KINOPIO_MODE, 0);
    }
counters:
    R(4) = 0x80430000u; R(3) = 0;
    for (uint32_t a = PY_TIME_UP_NUM; a <= PY_QUAKE_TRIGGER; a += 4) gm_set_u32(a, 0);
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) { R(4) = PY_QUAKE_TIMER + 4 * p; gm_set_u32(R(4), 0); if (--ctx->ctr) GM_LOOP(); }
    R(4) = 0; ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) { R(3) = PY_QUAKE_EFFECT + 4 * p; gm_set_u32(R(3), 0); if (--ctx->ctr) GM_LOOP(); }
    R(4) = gm_u32(PY_REST); R(5) = 0x80430000u; R(3) = 0;
    gm_set_u32(PY_BGM_STATE, 0);
    R(4) = CMPS(R(4), 98) > 0;                                           /* (checkBonusNoCap inline) */
    gm_set_u32(PY_BONUS_NO_CAP, R(4));
    R(4) = 0x80430000u; gm_set_u32(PY_KINOPIO_CARRY, 0);
    R(3) = gm_u32(DEMO_MNG_INSTANCE); BL(0x81805ADCu, fn_8005B430);      /* daPyDemoMng_c::initStage */
    R(3) = gm_u32(MULTI_MNG_INSTANCE); BL(0x81805AE8u, fn_800CE860);     /* dMultiMng_c::initStage */
}

/* update: once a frame - infinite lives, the game display's counters, the quake timers, a
   scene exit waits for the players, the quake's effect on the players, pause and the timer */
static void py_update(GM_CTX) {
    PY_FN(0x81806528u);
    R(3) = gm_u8(GAME_RULE + GR_INFINITE_LIVES);
    if (CMPU(R(3), 1) == 0) {                                            /* infinite lives: count deaths, keep 5 lives */
        R(3) = PY_REST; R(4) = PY_DEATH_COUNT; R(6) = 5;
        ctx->ctr = 8;
        for (uint32_t p = 0; p < 8; p++) {
            R(5) = PY_TYPE + 4 * p; R(8) = gm_u32(R(5)) << 2;
            R(7) = PY_REST + R(8); R(9) = gm_u32(R(7));
            if (CMPU(R(9), 4) == 0) { R(9) = gm_u32(PY_DEATH_COUNT + R(8)) + 1; gm_set_u32(PY_DEATH_COUNT + R(8), R(9)); }
            gm_set_u32(R(7), 5);
            if (--ctx->ctr) GM_LOOP();
        }
    }
    BL(0x818065B8u, fn_800608E0);                                        /* checkLastAlivePlayer */
    BL(0x818065BCu, fn_80101960);                                        /* dScStage_c::getGameDisplay */
    if (CMPU(R(3), 0) != 0) {
        gptr disp = R(3); NV_R(30, disp);
        R(3) = gm_u8(GAME_RULE + GR_INFINITE_LIVES);
        R(4) = CMPU(R(3), 0) != 0 ? PY_DEATH_COUNT : PY_REST;
        R(3) = 0x81860000u; if (R(4) == PY_REST) R(3) = 0x81850000u;
        R(3) = disp; BL(0x818065F8u, mfn_81832A24);                      /* dGameDisplay_c::updatePlayNum */
        R(3) = 8; R(4) = 0; ctx->ctr = 8;
        for (uint32_t c = 0; c < 8; c++) { R(3) = PY_COIN + 4 * c; R(5) = gm_u32(R(3)); R(4) += R(5); if (--ctx->ctr) GM_LOOP(); }
        R(3) = disp; BL(0x81806624u, fn_80159960);                       /* setCoinNum(getCoinAll()) */
        R(3) = 0x80430000u; R(4) = gm_u32(PY_SCORE);
        R(3) = disp; BL(0x81806634u, hle_mod_fn_80159CB0);                /* setScore */
        R(3) = disp; BL(0x8180663Cu, mod_fn_80159AF0_81832CB4);          /* setCollect */
    }
    /* the quake timers: a timer running out ends the player's quake effect */
    R(3) = PY_QUAKE_TIMER - 4; R(5) = PY_QUAKE_EFFECT - 4; R(4) = 0;
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        R(3) = PY_QUAKE_TIMER + 4 * p; R(7) = gm_u32(R(3));
        R(6) = R(5); R(5) += 4;
        if (CMPU(R(7), 0) != 0) {
            R(7) -= 1;
            int out = CMPU(R(7), 0) == 0;
            gm_set_u32(R(3), R(7));
            if (out) gm_set_u32(R(6) + 4, 0);
        }
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    /* a scene exit waits while a player in play still has something to finish */
    R(3) = gm_u32(DNEXT_INSTANCE); R(3) = gm_u8(R(3) + 24);
    if (CMPU(R(3), 1) == 0) {
        uint32_t wait = 0;
        NV_R(28, 8); NV_R(30, 0); NV_R(27, 0);
        for (uint32_t p = 0;; ) {
            R(3) = 0x81860000u;
            R(4) = gm_u32(PY_ACT_INFO); R(3) = PY_ACT_INFO;              /* (lwzu: the high word) */
            ctx->xer_ca = 32 >= p; R(5) = 32 - p;
            R(3) = gm_u32(PY_ACT_INFO + 4);
            R(5) = (R(5) & 63) > 31 ? 0 : R(4) << (R(5) & 63);
            R(3) = (p & 63) > 31 ? 0 : R(3) >> (p & 63);
            R(3) |= R(5);
            R(5) = p - 32;
            R(4) = (R(5) & 63) > 31 ? 0 : R(4) >> (R(5) & 63);
            R(3) = (R(3) | R(4)) & 1; CR0(ctx, R(3));                    /* (mActPlayerInfo >> p & 1) */
            if (R(3)) {
                R(3) = p; BL(0x818066ECu, getCtrlPlayer__9daPyMng_cFi_8005FB90);
                if (CMPU(R(3), 0) != 0) {
                    gptr pl = R(3);
                    R(4) = 100; NV_R(29, pl); BL(0x81806700u, testFlag__10daPlBase_cFi_80056CF0);
                    if (CMPU(R(3), 0) == 0) {
                        i2_vcall(ctx, base, 0x8180671Cu, pl, VT_IS_WAIT_FRAME_MAX, 3);
                        R(3) ^= 1; wait |= R(3); NV_R(27, wait);
                    }
                }
            }
            NV_R(28, R(28) - 1);
            int more = CMPU(R(28), 0) > 0;
            NV_R(30, ++p);
            if (!more) break;
            GM_LOOP();
        }
        R(3) = wait & 1; CR0(ctx, R(3));
        if (!R(3)) { R(3) = gm_u32(DNEXT_INSTANCE); R(4) = 0; gm_set_u16(R(3) + 28, 0); }
    }
    /* a quake shakes the players once (a big one, or for players without their own quake effect) */
    R(3) = gm_u32(DQUAKE_INSTANCE); R(3) = gm_u8(R(3) + 51) & 0x38; CR0(ctx, R(3));
    if (!R(3)) NV_R(29, 0);
    else {
        R(3) = gm_u32(PY_QUAKE_TRIGGER); NV_R(29, 1);
        if (CMPU(R(3), 0) == 0) {
            R(3) = PY_QUAKE_EFFECT; NV_R(28, 8); NV_R(30, 0); NV_R(26, PY_QUAKE_EFFECT - 4); NV_R(27, 0x80430000u);
            for (uint32_t p = 0;; ) {
                R(3) = p; NV_R(25, R(26)); NV_R(26, R(26) + 4);
                BL(0x8180679Cu, getCtrlPlayer__9daPyMng_cFi_8005FB90);
                if (CMPU(R(3), 0) != 0) {
                    R(4) = gm_u32(DQUAKE_INSTANCE); R(5) = gm_u32(R(4) + 48);
                    R(4) = R(5) & 0x20; CR0(ctx, R(4)); R(4) = 139;
                    int set = R(5) & 0x20;
                    if (!set) {
                        R(4) = R(5) & 8; CR0(ctx, R(4)); R(4) = 140;
                        set = R(5) & 8;
                        if (!set) { R(5) = gm_u32(R(25) + 4); set = CMPU(R(5), 0) == 0; }
                    }
                    if (set) BL(0x818067D4u, setFlag__10daPlBase_cFi_80056C70);
                }
                NV_R(28, R(28) - 1);
                int more = CMPU(R(28), 0) > 0;
                NV_R(30, ++p);
                if (!more) break;
                GM_LOOP();
            }
        }
    }
    R(3) = 0x80430000u; R(4) = gm_u32(PY_PAUSE_DISABLE);
    gm_set_u32(PY_QUAKE_TRIGGER, R(29));
    R(3) = gm_u32(PAUSE_MNG_INSTANCE); R(4) = cntlzw(R(4)) >> 5;
    BL(0x81806810u, fn_800D0B20);                                        /* PauseManager_c::setPauseEnable(!mPauseDisable) */
    R(3) = gm_u32(PY_STOP_TIMER); R(4) = 0x80430000u; R(5) = gm_u32(PY_STOP_TIMER_OLD);
    if (CMPU(R(3), R(5)) != 0) {                                         /* the stage timer stops / runs */
        R(5) = gm_u32(STAGE_TIMER_INSTANCE);
        NONZERO(6, 6, R(3));
        gm_set_u32(PY_STOP_TIMER_OLD, R(3));
        gm_set_u8(R(5) + 12, (uint8_t)R(6));
    }
    R(3) = gm_u32(DEMO_MNG_INSTANCE); BL(0x8180684Cu, fn_8005B550);      /* daPyDemoMng_c::update */
    R(3) = gm_u32(PY_EFFECT_INSTANCE); BL(0x81806858u, fn_800D2D80);     /* dPyEffectMng_c::update */
}

/* ================================================================== coins */
#define STACK_GUARD         0x8185FED4u  /* (the module's stack guard word, checked at the end) */
#define BG_PARAMETER        0x80429E00u  /* dBgParameter_c::ms_Instance_p: the screen position / size (+56 ...) */
#define F_HALF              0x818486CCu  /* 0.5f */
#define SND_OBJ_CMN_MAP     0x80429D60u  /* the 2D sound object (SndObjctCmnMap) */
#define SCORE_MNG_INSTANCE  0x8042A050u  /* dScoreMng_c::m_instance */
#define SE_COIN_100_A       179          /* (the 100-coin jingle, two parts) */
#define SE_COIN_100_B       180
static inline double lfs_(GM_CTX, int n, gptr a) { (void)base; double v = ldfs(base, a); ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define LFS(n, a) lfs_(GM_PASS, (n), (a))
#define FS(n, v) (ctx->f[n].d = ctx->ps1[n] = (v))                     /* (single arithmetic: both halves) */
/* incCoin(player): a coin for the player's character (with the Toad's coins going to the player
   carrying it); the 100th coin of all of them is an extra life for everyone taking part */
static void py_incCoin(GM_CTX, uint32_t plr) {
    PY_FN(0x81806E30u);
    gptr sp = gm_frame_sp;
    R(4) = gm_u32(STACK_GUARD); gm_set_u32(sp + 48, R(4));
    gm_set_u32(sp + 44, plr);
    R(3) = sp + 44; BL(0x81806E6Cu, changeItemKinopioPlrNo__9daPyMng_cFRi_80060170);   /* (a carried Toad's coin: the carrier's) */
    R(3) = gm_u32(MULTI_MNG_INSTANCE); R(4) = gm_u32(sp + 44);
    BL(0x81806E7Cu, fn_800CE9D0);                                        /* dMultiMng_c::incCoin(player) */
    R(3) = 0; ctx->ctr = 8;
    for (uint32_t c = 0; c < 8; c++) { R(4) = PY_COIN + 4 * c; R(5) = gm_u32(R(4)); R(3) += R(5); if (--ctx->ctr) GM_LOOP(); }
    if (CMPS(R(3), 99) < 0) {                                            /* one more */
        R(3) = gm_u32(sp + 44); R(4) = PY_TYPE; R(3) <<= 2;
        R(3) = gm_u32(PY_TYPE + R(3)); R(4) = PY_COIN; R(3) <<= 2;
        R(5) = gm_u32(PY_COIN + R(3)) + 1; gm_set_u32(PY_COIN + R(3), R(5));
    } else {                                                             /* the 100th: lives for all, the coins reset */
        uint32_t entries = 0;
        R(3) = PY_ENTRY - 4; ctx->ctr = 8;
        for (uint32_t p = 0; p < 8; p++) { R(3) = PY_ENTRY + 4 * p; entries += NONZERO(5, 4, gm_u32(R(3))); if (--ctx->ctr) GM_LOOP(); }
        NV_R(27, entries);
        int none = CMPU(entries, 0) == 0;
        NV_R(26, cntlzw(entries));
        if (!none) {                                                     /* the jingle, at the screen's centre, to every remote in play */
            R(3) = gm_u32(BG_PARAMETER); R(4) = 0x81850000u;
            LFS(0, F_HALF); R(4) = sp + 16;
            LFS(2, R(3) + 64); LFS(3, R(3) + 68); LFS(1, R(3) + 56);
            FS(2, frsp(ctx->f[2].d * ctx->f[0].d));
            LFS(4, R(3) + 60);
            FS(0, frsp(ctx->f[3].d * ctx->f[0].d));
            FS(1, frsp(ctx->f[1].d + ctx->f[2].d));
            R(3) = sp + 24;
            FS(0, frsp(ctx->f[4].d - ctx->f[0].d));
            stfs(base, sp + 16, ctx->f[1].d); stfs(base, sp + 20, ctx->f[0].d);
            BL(0x81806F54u, cvtSndObjctPos__6dAudioFRC7mVec2_c_8006A3F0);
            R(3) = gm_u32(sp + 28); R(5) = 0x81860000u; R(4) = gm_u32(sp + 24); NV_R(28, 8);
            gm_set_u32(sp + 36, R(3));
            R(3) = PY_ENTRY; NV_R(30, 0); NV_R(25, PY_ENTRY - 4); NV_R(29, 0);
            gm_set_u32(sp + 32, R(4));
            uint32_t remotes = 0;
            for (uint32_t p = 0;; ) {
                NV_R(25, PY_ENTRY + 4 * p); R(3) = gm_u32(R(25));
                if (CMPU(R(3), 0) != 0) { R(3) = p; BL(0x81806F90u, mod_getRemotePlayer__6dAudioFi_81807C9C); remotes |= R(3); NV_R(30, remotes); }
                NV_R(28, R(28) - 1);
                int more = CMPU(R(28), 0) > 0;
                NV_R(29, ++p);
                if (!more) break;
                GM_LOOP();
            }
            NV_R(29, gm_u32(SND_OBJ_CMN_MAP)); NV_R(28, sp + 32);
            R(4) = SE_COIN_100_A; R(5) = R(28); R(3) = R(29); R(6) = R(30);
            BL(0x81806FC4u, startSound__14SndObjctCmnMapFUlRCQ34nw4r4math4VEC2Ul_80198C30);
            R(3) = R(29); R(4) = SE_COIN_100_B; R(5) = R(28); R(6) = R(30);
            BL(0x81806FD8u, startSound__14SndObjctCmnMapFUlRCQ34nw4r4math4VEC2Ul_80198C30);
        }
        R(4) = 0x81860000u;
        NONZERO(3, 28, R(27));                                           /* (r28 = entries != 0) */
        R(3) = PY_ENTRY;
        NV_R(30, R(26) >> 5);                                            /* (nobody taking part) */
        NV_R(26, 8); NV_R(29, 0); NV_R(27, PY_ENTRY - 4); NV_R(25, 0x80430000u);
        for (uint32_t p = 0;; ) {
            NV_R(27, PY_ENTRY + 4 * p); R(3) = gm_u32(R(27));
            if (CMPU(R(3), 0) != 0) {
                R(3) = p; BL(0x81807010u, hle_getPlayer__9daPyMng_cFi);
                int life = 0;
                if (CMPU(R(3), 0) != 0) { R(4) = 4; BL(0x81807020u, testFlag__10daPlBase_cFi_80056CF0); life = CMPU(R(3), 0) != 0; }
                if (life) { R(3) = p; R(4) = 1; R(5) = R(28); BL(0x81807038u, fn_80060460); }   /* incRest(player, 1, ...) */
                else {                                                   /* (not playing now: the 1-up as score) */
                    R(3) = gm_u32(SCORE_MNG_INSTANCE); R(4) = 8; R(5) = p; R(6) = R(30);
                    BL(0x81807050u, fn_800e25a0__11dScoreMng_cFUlii_800E24B0);
                }
            }
            NV_R(26, R(26) - 1);
            int more = CMPU(R(26), 0) > 0;
            NV_R(29, ++p);
            if (!more) break;
            GM_LOOP();
        }
        R(4) = 0; ctx->ctr = 8;
        for (uint32_t c = 0; c < 8; c++) { R(3) = PY_COIN + 4 * c; gm_set_u32(R(3), 0); if (--ctx->ctr) GM_LOOP(); }
    }
    R(3) = gm_u32(STACK_GUARD); R(4) = gm_u32(sp + 48);
    if (CMPU(R(3), R(4)) != 0) BL(0x818070C0u, mfn_81844FCC);           /* (stack smashed: panic) */
}

/* ================================================================== ground-pound quakes */
#define DSCSTAGE_IS_STAFF_CREDIT 0x8042A21Fu /* dScStage_c::m_isStaffCredit (u8) */
#define FFEAT_ONE_PLAYER_HIP_QUAKE 0x8185E8B0u /* fFeat::one_player_special_hip_attack_quake (u8) */
#define GR_BUBBLE_SWARM     10           /* dGameRule_s: bool bubble_swarm_mode */
#define SND_AUDIO_MGR       0x8042A488u  /* SndAudioMgr::sInstance */
#define BALLOON_MNG_INSTANCE 0x80429D88u /* dBalloonMng_c::m_instance */
#define PY_QUAKE_SE_LIST    (PY_MODEL_TYPES + 72)   /* SE_PLY_HPDP_SPECIAL_TWO / THREE / FOUR */
#define PY_EFFECT_NAME_1    (PY_MODEL_TYPES + 107)  /* "Wm_mr_vshipattack" ... (the two effect names) */
#define PY_EFFECT_NAME_2    (PY_MODEL_TYPES + 145)
#define EFFECT_Z            0x453B8000u  /* 3000.0f: the second effect in front */
#define AC_POS              172          /* dActor_c::mPos (x, y, z) */
void hle_startSystemSe__11SndAudioMgrFUiUl(ppc_context *ctx, uint8_t *base);
void hle_createEffect__3mEfFPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c(ppc_context *ctx, uint8_t *base);

/* setHipAttackSpecialEffect: the "power impact" - each player whose quake has just started
   (timer running, effect not yet shown) gets the effect at its position (or its Yoshi's) and a shock */
static void py_setHipAttackSpecialEffect(GM_CTX) {
    PY_FN(0x81807590u);
    gptr sp = gm_frame_sp;
    R(3) = gm_u32(STACK_GUARD); gm_set_u32(sp + 28, R(3));
    R(3) = gm_u32(SND_SCENE_MGR); BL(0x818075E0u, fn_8019C4E0);           /* SndSceneMgr::onPowerImpact */
    R(3) = PY_QUAKE_EFFECT; R(4) = PY_QUAKE_TIMER; R(5) = PY_MODEL_TYPES; R(6) = 0x453B0000u;
    NV_R(25, 8); NV_R(30, 0); NV_R(24, 1); NV_R(29, sp + 16); NV_R(23, EFFECT_Z);
    NV_R(21, PY_QUAKE_EFFECT - 4); NV_R(22, PY_QUAKE_TIMER - 4);
    NV_R(28, PY_EFFECT_NAME_1); NV_R(27, PY_EFFECT_NAME_2); NV_R(20, 0x80430000u);
    for (uint32_t p = 0;; ) {
        NV_R(22, PY_QUAKE_TIMER + 4 * p); R(4) = gm_u32(R(22));
        R(3) = R(21); NV_R(21, R(21) + 4);
        if (CMPU(R(4), 0) == 0) goto next;                               /* (no quake for this player) */
        R(4) = gm_u32(R(3) + 4);
        if (CMPU(R(4), 0) != 0) goto next;                               /* (shown already) */
        gm_set_u32(R(3) + 4, 1);
        R(3) = p; BL(0x81807650u, hle_getPlayer__9daPyMng_cFi);
        if (CMPU(R(3), 0) == 0) goto next;
        R(4) = FLAG_YOSHI_RIDE; NV_R(26, R(3)); BL(0x81807664u, testFlag__10daPlBase_cFi_80056CF0);
        if (CMPU(R(3), 0) != 0) {                                        /* on a Yoshi: at the Yoshi */
            R(3) = R(26); BL(0x81807674u, getYoshi__7dAcPy_cFv_80139950);
            NV_R(26, R(3));
            if (CMPU(R(3), 0) == 0) goto next;
        }
        R(3) = gm_u32(R(26) + AC_POS + 8); R(5) = R(29); R(4) = gm_u32(R(26) + AC_POS); R(6) = 0;
        gm_set_u32(sp + 24, R(3)); R(7) = 0;
        R(3) = gm_u32(R(26) + AC_POS + 4); gm_set_u32(sp + 16, R(4)); R(4) = 0;
        gm_set_u32(sp + 20, R(3));
        R(3) = R(28); BL(0x818076B0u, hle_createEffect__3mEfFPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
        R(3) = R(27); R(4) = 0; R(5) = R(29); R(6) = 0; R(7) = 0;
        gm_set_u32(sp + 24, R(23));
        BL(0x818076CCu, hle_createEffect__3mEfFPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
        R(3) = gm_u32(DQUAKE_INSTANCE); R(4) = (uint32_t)(int32_t)(int8_t)p; R(5) = 3; R(6) = 3; R(7) = 18; R(8) = 0;
        BL(0x818076E8u, fn_800D8B00);                                    /* dQuake_c::startShock */
    next:
        NV_R(25, R(25) - 1);
        int more = CMPU(R(25), 0) > 0;
        NV_R(30, ++p);
        if (!more) break;
        GM_LOOP();
    }
    R(3) = gm_u32(STACK_GUARD); R(4) = gm_u32(sp + 28);
    if (CMPU(R(3), R(4)) != 0) BL(0x8180774Cu, mfn_81844FCC);
}
/* setHipAttackQuake(type, player): a ground pound shakes the screen; two or more players
   pounding together (or one, with the module's option) make the special quake */
static void py_setHipAttackQuake(GM_CTX, uint32_t type, uint32_t plr) {
    PY_FN(0x81807420u);
    if (CMPU(plr, 0xFF) == 0) return;
    if (CMPU(type, 2) == 0) {
        R(3) = gm_u32(DQUAKE_INSTANCE); R(4) = (uint32_t)(int32_t)(int8_t)plr; R(5) = 7;
        R(6) = 0; R(7) = 0; BL(0x81807510u, shockMotor__8dQuake_cFScQ28dQuake_c12TYPE_SHOCK_eib_800D8BB0);
        return;
    }
    R(5) = 0x81860000u; R(6) = plr << 2; R(7) = 5; R(8) = 0x81860000u; R(9) = PY_QUAKE_TIMER;
    gm_set_u32(PY_QUAKE_TIMER + R(6), 5);
    R(5) = 0; R(7) = PY_QUAKE_EFFECT;
    gm_set_u32(PY_QUAKE_EFFECT + R(6), 0);
    ctx->ctr = 8; R(6) = plr;
    for (uint32_t o = 0;; o++) {                                         /* the other players quaking now */
        int other = CMPU(R(6), 0) != 0;
        R(8) = PY_QUAKE_TIMER + 4 * o;
        if (other) { R(7) = gm_u32(R(8)); R(5) += NONZERO(9, 7, R(7)); }
        R(6) -= 1; R(7) = R(8);
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    uint32_t count = R(5);
    R(6) = gm_u8(DSCSTAGE_IS_STAFF_CREDIT);
    int special = 0;
    if (CMPU(R(6), 0) == 0) {
        R(6) = gm_u8(FFEAT_ONE_PLAYER_HIP_QUAKE);
        if (CMPU(R(6), 0) != 0) special = 1;
        else if (CMPU(count, 0) != 0) special = 1;
    }
    if (!special) {
        R(5) = 0x80430000u;
        int one = CMPU(type, 1) == 0;
        R(3) = gm_u32(DQUAKE_INSTANCE); R(4) = (uint32_t)(int32_t)(int8_t)plr;
        if (one) { R(5) = 3; R(6) = 3; R(7) = 0; R(8) = 0; BL(0x818074FCu, fn_800D8B00); }   /* startShock(HIP_ATTACK) */
        else { R(5) = 4; R(6) = 0; R(7) = 0; BL(0x81807510u, shockMotor__8dQuake_cFScQ28dQuake_c12TYPE_SHOCK_eib_800D8BB0); }
        return;
    }
    R(3) = 0x80430000u; R(4) = count;
    if (CMPS(count, 3) >= 0) R(4) = 3;
    R(3) = gm_u32(SND_AUDIO_MGR);
    R(4) = CMPS(count, 0) > 0 ? R(4) - 1 : 0;                            /* (clamp(count - 1, 0, 2)) */
    R(5) = 0x81850000u; R(4) <<= 2; R(5) = PY_MODEL_TYPES; R(4) += R(5);
    R(4) = gm_u32(R(4) + 72); R(5) = 1;
    BL(0x81807568u, hle_startSystemSe__11SndAudioMgrFUiUl);
    R(3) = gm_u8(GAME_RULE + GR_BUBBLE_SWARM);
    if (CMPU(R(3), 1) == 0) { R(3) = gm_u32(BALLOON_MNG_INSTANCE); BL(0x81807588u, mfn_81808204); }   /* dBalloonMng_c::popAll */
    BL(0x8180758Cu, hle_mod_fn_80060DB0);                                /* setHipAttackSpecialEffect */
    GM_LOOP();                                                           /* (the jump back to the return) */
}

/* ================================================================== hle entry points
   Verified memory: the manager's arrays and scalars (calls into players / Yoshis / the music
   change more; RT_GM_VERIFY's double run of those is for the registers only). */
#define A(i) GM_ARG(i)
#define PY_MEM PY_ACT_INFO, 0x288, 0x80429CA0u, 0x50, PY_REST, 32
static void py_selftest(GM_CTX);
GM_HLE_INT (mod_getEntryNum__9daPyMng_cFv, PY_MEM)                  { py_selftest(GM_PASS); py_getEntryNum(GM_PASS); }
GM_HLE_INT (mod_getNumInGame__9daPyMng_cFv, PY_MEM)                 { py_getNumInGame(GM_PASS); }
GM_HLE_VOID(mod_fn_8005EA60, PY_MEM)                                { py_initGame(GM_PASS); }
GM_HLE_VOID(mod_fn_8005ECE0, PY_MEM)                                { py_setDefaultParam(GM_PASS); }
GM_HLE_VOID(mod_fn_80061160, PY_MEM)                                { py_checkCorrectCreateInfo(GM_PASS); }
GM_HLE_INT (mod_addNum__9daPyMng_cFi, PY_MEM)                       { py_addNum(GM_PASS, A(0)); }
GM_HLE_VOID(mod_fn_8005f570__9daPyMng_cF16PLAYER_POWERUP_ei, PY_MEM) { py_initKinopioPlayer(GM_PASS, A(0), A(1)); }
GM_HLE_VOID(mod_fn_80060EF0, PY_MEM)                                { py_checkBonusNoCap(GM_PASS); }
GM_HLE_INT (mod_fn_8005EEE0, PY_MEM)                                { py_create(GM_PASS, A(0), A(1), A(2), A(3)); }
GM_HLE_VOID(mod_fn_8005F920, PY_MEM)                                { py_decideCtrlPlrNo(GM_PASS); }
GM_HLE_INT (mod_isCreateBalloon__9daPyMng_cFi, PY_MEM)              { py_isCreateBalloon(GM_PASS, A(0)); }
GM_HLE_INT (mod_fn_80060200, PY_MEM)                                { py_getCoinAll(GM_PASS); }
GM_HLE_INT (mod_fn_8005F990, PY_MEM)                                { py_setYoshi(GM_PASS, A(0)); }
GM_HLE_VOID(mod_fn_8005FA00, PY_MEM)                                { py_releaseYoshi(GM_PASS, A(0)); }
GM_HLE_INT (mod_getYoshi__9daPyMng_cFi, PY_MEM)                     { py_getYoshi(GM_PASS, A(0)); }
GM_HLE_INT (mod_fn_8005FB00, PY_MEM)                                { py_getYoshiNum(GM_PASS); }
GM_HLE_INT (mod_getCourseInPlayerModelType__9daPyMng_cFUc, PY_MEM)  { py_getCourseInPlayerModelType(GM_PASS, A(0)); }
GM_HLE_VOID(mod_setCarryOverYoshiInfo__9daPyMng_cFUcUci, PY_MEM)    { py_setCarryOverYoshiInfo(GM_PASS, A(0), A(1), A(2)); }
GM_HLE_INT (mod_getYoshiColor__9daPyMng_cFUc, PY_MEM)               { py_getYoshiColor(GM_PASS, A(0)); }
GM_HLE_INT (mod_getYoshiFruit__9daPyMng_cFUc, PY_MEM)               { py_getYoshiFruit(GM_PASS, A(0)); }
GM_HLE_INT (mod_fn_8005FC70, PY_MEM)                                { py_getActScrollInfo(GM_PASS); }
GM_HLE_INT (mod_fn_8005FD20, PY_MEM)                                { py_getScrollNum(GM_PASS); }
GM_HLE_VOID(mod_fn_8005FEB0, PY_MEM)                                { py_addNumOnly(GM_PASS); }
GM_HLE_INT (mod_decNum__9daPyMng_cFi, PY_MEM)                       { py_decNum(GM_PASS, A(0)); }
GM_HLE_VOID(mod_fn_8005FED0, PY_MEM)                                { py_decNumOnly(GM_PASS); }
GM_HLE_INT (mod_getPlayerIndex__9daPyMng_cF13PLAYER_TYPE_e, PY_MEM) { py_findPlayerWithType(GM_PASS, A(0)); }
GM_HLE_INT (mod_fn_800601E0, PY_MEM)                                { py_getCourseInListPlrNo(GM_PASS, (int32_t)A(0)); }
GM_HLE_VOID(mod_fn_80060590, PY_MEM)                                { py_incRestAll(GM_PASS, A(0)); }
GM_HLE_VOID(mod_fn_80060700, PY_MEM)                                { py_setCourseInStarBGM(GM_PASS); }
GM_HLE_VOID(mod_stopStarBGM__9daPyMng_cFv, PY_MEM)                  { py_stopStarBGM(GM_PASS); }
GM_HLE_VOID(mod_stopYoshiBGM__9daPyMng_cFv, PY_MEM)                 { py_stopYoshiBGM(GM_PASS); }
GM_HLE_VOID(mod_fn_80060970, PY_MEM)                                { py_executeLastPlayer(GM_PASS); }
GM_HLE_VOID(mod_fn_80060A10, PY_MEM)                                { py_executeLastAll(GM_PASS); }
GM_HLE_VOID(mod_fn_8005EB10, PY_MEM)                                { py_initStage(GM_PASS); }
GM_HLE_VOID(mod_fn_8005F5C0, PY_MEM)                                { py_update(GM_PASS); }
GM_HLE_VOID(mod_fn_80060250, PY_MEM)                                { py_incCoin(GM_PASS, A(0)); }
GM_HLE_VOID(mod_setHipAttackQuake__9daPyMng_cFiUc, PY_MEM)          { py_setHipAttackQuake(GM_PASS, A(0), A(1)); }
GM_HLE_VOID(mod_fn_80060DB0, PY_MEM)                                { py_setHipAttackSpecialEffect(GM_PASS); }

/* ================================================================== self-test (RT_GM_SELFTEST=py_mng)
   The functions that only read / write the manager's own state, with its arrays and scalars
   random (characters, power-ups, lives, coins also out of range, for checkCorrectCreateInfo) and
   random players. The ones that call into the players / Yoshis / music are left to RT_GM_VERIFY. */
static const gm_test_t py_tests[] = {
    GM_TEST(mod_getEntryNum__9daPyMng_cFv, GMV_RET, "!"),
    GM_TEST(mod_getNumInGame__9daPyMng_cFv, GMV_RET, "!"),
    GM_TEST(mod_fn_8005EA60, 0, "!"),
    GM_TEST(mod_fn_8005ECE0, 0, "!"),
    GM_TEST(mod_fn_80061160, 0, "!"),
    GM_TEST(mod_fn_8005f570__9daPyMng_cF16PLAYER_POWERUP_ei, 0, "!kp"),
    GM_TEST(mod_fn_80060EF0, 0, "!"),
    GM_TEST(mod_fn_8005F920, 0, "!"),
    GM_TEST(mod_isCreateBalloon__9daPyMng_cFi, GMV_RET, "!p"),
    GM_TEST(mod_fn_80060200, GMV_RET, "!"),
    GM_TEST(mod_fn_8005F990, GMV_RET, "!Y"),
    GM_TEST(mod_fn_8005FA00, 0, "!Y"),
    GM_TEST(mod_getCourseInPlayerModelType__9daPyMng_cFUc, GMV_RET, "!p"),
    GM_TEST(mod_setCarryOverYoshiInfo__9daPyMng_cFUcUci, 0, "!pkv"),
    GM_TEST(mod_getYoshiColor__9daPyMng_cFUc, GMV_RET, "!p"),
    GM_TEST(mod_getYoshiFruit__9daPyMng_cFUc, GMV_RET, "!p"),
    GM_TEST(mod_fn_8005FEB0, 0, "!"),
    GM_TEST(mod_fn_8005FED0, 0, "!"),
    GM_TEST(mod_getPlayerIndex__9daPyMng_cF13PLAYER_TYPE_e, GMV_RET, "!T"),
    GM_TEST(mod_fn_800601E0, GMV_RET, "!p"),
};
static void py_randomize(GM_CTX, int round) {
    (void)ctx; (void)base;
    for (uint32_t a = 0; a < 0x138; a += 4) gm_set_u32(PY_ACT_INFO + a, gm_rand() & gm_rand());
    for (uint32_t p = 0; p < 8; p++) {
        gm_set_u32(PY_ENTRY + 4 * p, gm_rand() % 3 ? gm_rand() & 1 : gm_rand());
        gm_set_u32(PY_TYPE + 4 * p, round % 4 ? (p + gm_rand()) % 8 : gm_rand() % 11);
        gm_set_u32(PY_MODE + 4 * p, gm_rand() % 9);
        gm_set_u32(PY_CREATE_ITEM + 4 * p, gm_rand() & 0xF);
        gm_set_u32(PY_COIN + 4 * p, round % 3 ? gm_rand() % 20 : gm_rand() % 120);
        gm_set_u32(PY_REST + 4 * p, gm_rand() % 3 ? gm_rand() % 101 : (uint32_t)((int32_t)(gm_rand() % 200) - 50));
        if (gm_rand() % 3 == 0) gm_set_u32(PY_YOSHI_ID + 4 * p, 0);
    }
    gm_set_u32(PY_NUM, (uint32_t)((int32_t)(gm_rand() % 12) - 2));
    gm_set_u32(PY_SCORE, gm_rand() % 2 ? gm_rand() % 1000000 : gm_rand());
    for (uint32_t a = 4; a < 0x50; a += 4) if (a != 0x20) gm_set_u32(0x80429CA0u + a, gm_rand() & gm_rand());
    gm_set_u32(PY_SCORE, gm_rand() % 2 ? gm_rand() % 1000000 : gm_rand());
}
static uint32_t py_arg(char k) {
    switch (k) {
    case 'Y': return PY_YOSHI_ID + 4 * (gm_rand() % 8);  /* (a "Yoshi" whose ID is a slot's: found / not found) */
    case 'T': return gm_rand() % 10;                     /* (a character, also none) */
    default:  return 0xDEADBEEFu;
    }
}
static void py_selftest(GM_CTX) {
    if (!gm_selftest_wanted("py_mng")) return;
    const gptr ranges[] = { PY_ACT_INFO, 0x138, 0x80429CA0u, 0x50, PY_REST, 32 };
    const gm_selftest_t t = { "py_mng", py_tests, (int)(sizeof py_tests / sizeof *py_tests), 300,
                              ranges, 3, py_randomize, py_arg };
    gm_selftest(GM_PASS, &t);
}
