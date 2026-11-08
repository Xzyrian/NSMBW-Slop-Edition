/* gm_mj2d_game.c - dMj2dGame_c, one save slot's game data (track B, gm.h).
 *
 * Decompiled from the 8-player module's version (nsmbw-project v0.6.5,
 * wiimj2d/d_static/d_mj2d/d_mj2d_game.cpp), which replaces the game's: 8 players, a save revision
 * of 14.1, a checkpoint and the pipe randomizer settings added at the end. Field offsets checked
 * against the recompiled code (the module's layout, not the game's original 0x980 one).
 *
 * Game address (USA rev 2) -> recompiled name: mod_fn_<game address>; the four course flag
 * functions keep the names the module's symbol map gave them (SaveBlock::...). */
#include "gm_i2.h"
RT_STATE_FILE                                   /* (no variables; the convention for game code) */

/* ---- dMj2dGame_c, the module's layout ---- */
#define MJ2D_REVISION           0x000   /* u8 major, u8 minor */
#define MJ2D_GAME_COMPLETION    0x002   /* u8: GAME_COMPLETION_e */
#define MJ2D_IBARA_NOW          0x006   /* u8: the world map's vine shuffle counter */
#define MJ2D_STOCK_ITEM         0x008   /* u8 [7] */
#define MJ2D_START_KINOKO       0x00F   /* u8 [10 worlds]: START_KINOKO_KIND_e */
#define MJ2D_PLAYER_CONTINUE    0x019   /* s8 [8 players] */
#define MJ2D_PLAYER_COIN        0x021   /* s8 [8] */
#define MJ2D_PLAYER_LIFE        0x029   /* u8 [8] */
#define MJ2D_PLAYER_CREATE_ITEM 0x031   /* u8 [8]: PLAYER_CREATE_ITEM_e (only STAR_POWER kept) */
#define MJ2D_PLAYER_CHARACTER   0x039   /* u8 [8]: PLAYER_TYPE_e */
#define MJ2D_PLAYER_POWERUP     0x041   /* u8 [8]: PLAYER_MODE_e */
#define MJ2D_WORLD_COMPLETION   0x049   /* u8 [10]: WORLD_COMPLETION_e */
#define MJ2D_ENEMY_REVIVAL      0x053   /* u8 [10][4] */
#define MJ2D_STAFFROLL_HISCORE  0x07C   /* u16 */
#define MJ2D_SCORE              0x080   /* u32 */
#define MJ2D_COURSE_COMPLETION  0x084   /* u32 [10][42]: COURSE_COMPLETION_e */
#define MJ2D_OTEHON_OPEN        0x714   /* std::bitset<70>: 3 words (see otehon_* below) */
#define MJ2D_KINOPIO_COURSE     0x720   /* u8 [10]: STAGE_e */
#define MJ2D_ENEMY_SCENE        0x72A   /* u8 [10][4] */
#define MJ2D_ENEMY_POS_INDEX    0x752   /* s8 [10][4] */
#define MJ2D_ENEMY_WALK_DIR     0x77A   /* s8 [10][4]: PATH_DIRECTION_e */
#define MJ2D_DEATH_COUNT        0x7A2   /* u8 [10][42] */
#define MJ2D_DEATH_COUNT_SWITCH 0x946   /* u8: World 3-4 with the world map switch on */
#define MJ2D_SIZE               0x970   /* (what initialize() copies) */

#define WORLD_COUNT 10
#define STAGE_COUNT 42
#define STAGE_RESCUE 38
#define COURSE_GOAL_MASK 0x30           /* GOAL_NORMAL | GOAL_SECRET */
#define GAME_COMPLETION_SAVE_EMPTY 0x01
#define GAME_COMPLETION_SUPER_GUIDE 0x40
#define SAVE_REVISION 0x0E01            /* 14.1 */

#define FFEAT_COMPLETED_ALL_LEVELS 0x80006785u   /* fFeat::completed_all_levels (a Riivolution option byte) */
#define DEFAULT_GAME_IMAGE   0x81849C20u  /* the module's constexpr dMj2dGame_c{} that initialize() copies */
#define DEFAULT_PLAYER_TYPES 0x81849BE4u  /* dMj2dGame_c::scDefaultPlayerTypes[8] (s32) */
#define A_MEMCPY             0x81844C38u  /* the module's memcpy */
#define A_OSPANIC            0x818380F8u  /* the module's OSPanic(file, line, format, ...) */
#define S_BITSET_FILE        0x8184A5A0u  /* "bitset" ... the strings the library's range check passes */

static gptr course(gptr self, uint32_t world, uint32_t stage) {          /* &mCourseCompletion[world][stage] */
    return self + MJ2D_COURSE_COMPLETION + world * (STAGE_COUNT * 4) + stage * 4;
}

/* ---- players ---- */
void dMj2dGame_setPlrID(gptr self, int player, int type)      { gm_set_u8(self + MJ2D_PLAYER_CHARACTER + player, (uint8_t)type); }
int  dMj2dGame_getPlrID(gptr self, int player)                { return gm_u8(self + MJ2D_PLAYER_CHARACTER + player); }
void dMj2dGame_setPlrMode(gptr self, int player, int mode)    { gm_set_u8(self + MJ2D_PLAYER_POWERUP + player, (uint8_t)mode); }
int  dMj2dGame_getPlrMode(gptr self, int player)              { return gm_u8(self + MJ2D_PLAYER_POWERUP + player); }
void dMj2dGame_setRest(gptr self, int player, int lives)      { gm_set_u8(self + MJ2D_PLAYER_LIFE + player, (uint8_t)lives); }
int  dMj2dGame_getRest(gptr self, int player)                 { return gm_u8(self + MJ2D_PLAYER_LIFE + player); }
void dMj2dGame_setCreateItem(gptr self, int player, int flag) { gm_set_u8(self + MJ2D_PLAYER_CREATE_ITEM + player, (uint8_t)(flag & 1)); }   /* (STAR_POWER only) */
int  dMj2dGame_getCreateItem(gptr self, int player)           { return gm_u8(self + MJ2D_PLAYER_CREATE_ITEM + player) & 1; }
void dMj2dGame_setCoin(gptr self, int player, int coins)      { gm_set_u8(self + MJ2D_PLAYER_COIN + player, (uint8_t)coins); }
int  dMj2dGame_getCoin(gptr self, int player)                 { return gm_s8(self + MJ2D_PLAYER_COIN + player); }
void dMj2dGame_setContinue(gptr self, int player, int n)      { gm_set_u8(self + MJ2D_PLAYER_CONTINUE + player, (uint8_t)n); }
int  dMj2dGame_getContinue(gptr self, int player)             { return gm_s8(self + MJ2D_PLAYER_CONTINUE + player); }

/* ---- score ---- */
void     dMj2dGame_setScore(gptr self, uint32_t score) { gm_set_u32(self + MJ2D_SCORE, score); }
uint32_t dMj2dGame_getScore(gptr self)                 { return gm_u32(self + MJ2D_SCORE); }
void dMj2dGame_setStaffCreditHighScore(gptr self, uint32_t score) {      /* (only a better score) */
    if (gm_u16(self + MJ2D_STAFFROLL_HISCORE) < score) gm_set_u16(self + MJ2D_STAFFROLL_HISCORE, (uint16_t)score);
}
int dMj2dGame_getStaffCreditHighScore(gptr self) { return gm_u16(self + MJ2D_STAFFROLL_HISCORE); }

/* ---- hint movies: a std::bitset<70>, as the module's compiler built it - three words, and a bit
   n is set in all three at position n % 32 (and tested in their OR). Not a correct bitset, but
   what the saves hold. Out of range (n >= 70): the library's range check panics. */
static void otehon_range_panic(GM_CTX, uint32_t line) {
    GM_CALL(A_OSPANIC, 4, S_BITSET_FILE, line, S_BITSET_FILE + 15, S_BITSET_FILE + 7);   /* (does not return) */
}
static void otehon_set(gptr bits, uint32_t n, uint32_t v) {
    uint32_t sh = n & 31, mask = 1u << sh, val = (v << sh) | (sh ? v >> (32 - sh) : 0);   /* (a rotate) */
    for (int w = 0; w < 3; w++) gm_set_u32(bits + 4 * w, (gm_u32(bits + 4 * w) & ~mask) | val);
}
static uint32_t otehon_test(gptr bits, uint32_t n) {
    uint32_t all = gm_u32(bits) | gm_u32(bits + 4) | gm_u32(bits + 8), sh = (0u - n) & 31;
    return ((all << sh) | (sh ? all >> (32 - sh) : 0)) & 1;              /* (rotate left by -n) */
}

/* ---- Star Coins, course and world flags ---- */
uint32_t dMj2dGame_isCollectCoin(gptr self, uint32_t world, uint32_t stage, uint32_t coin) {
    uint32_t sh = coin & 63;
    return (sh > 31 ? 0 : 1u << sh) & gm_u8(course(self, world, stage) + 3);   /* (the flags' low byte) */
}
int dMj2dGame_getTotalWorldCollectCoin(GM_CTX, gptr self, uint32_t world) {
    int count = 0;
    for (uint32_t stage = 0; stage < STAGE_COUNT; stage++) {
        uint32_t flags = gm_u32(course(self, world, stage));
        for (uint32_t coin = 0; coin < 3; coin++) {
            count += (flags >> coin) & 1;
            if (coin < 2) GM_LOOP();
        }
        if (stage < STAGE_COUNT - 1) GM_LOOP();
    }
    return count;
}
uint32_t dMj2dGame_getCourseDataFlag(gptr self, uint32_t world, uint32_t stage) {
    uint32_t flags = gm_u32(course(self, world, stage));
    return gm_u8(FFEAT_COMPLETED_ALL_LEVELS) ? flags | COURSE_GOAL_MASK : flags;
}
int dMj2dGame_isCourseDataFlag(gptr self, uint32_t world, uint32_t stage, uint32_t flag) {
    if (gm_u8(FFEAT_COMPLETED_ALL_LEVELS)) return 1;
    return (gm_u32(course(self, world, stage)) & flag) != 0;
}
void dMj2dGame_onCourseDataFlag(gptr self, uint32_t world, uint32_t stage, uint32_t flag) {
    gptr c = course(self, world, stage); gm_set_u32(c, gm_u32(c) | flag);
}
void dMj2dGame_offCourseDataFlag(gptr self, uint32_t world, uint32_t stage, uint32_t flag) {
    gptr c = course(self, world, stage); gm_set_u32(c, gm_u32(c) & ~flag);
}
uint32_t dMj2dGame_isWorldDataFlag(gptr self, uint32_t world, uint32_t flag) { return gm_u8(self + MJ2D_WORLD_COMPLETION + world) & flag; }
void dMj2dGame_onWorldDataFlag(gptr self, uint32_t world, uint32_t flag) {
    gptr w = self + MJ2D_WORLD_COMPLETION + world; gm_set_u8(w, (uint8_t)(gm_u8(w) | flag));
}
void dMj2dGame_offWorldDataFlag(gptr self, uint32_t world, uint32_t flag) {
    gptr w = self + MJ2D_WORLD_COMPLETION + world; gm_set_u8(w, (uint8_t)(gm_u8(w) & ~flag));
}

/* ---- world map ---- */
void dMj2dGame_setStartKinokoKind(gptr self, uint32_t world, uint32_t kind) { gm_set_u8(self + MJ2D_START_KINOKO + world, (uint8_t)kind); }
int  dMj2dGame_getStartKinokoKind(gptr self, uint32_t world)               { return gm_u8(self + MJ2D_START_KINOKO + world); }
void dMj2dGame_setKinopioCourseNo(gptr self, uint32_t world, uint32_t stage) { gm_set_u8(self + MJ2D_KINOPIO_COURSE + world, (uint8_t)stage); }
int  dMj2dGame_getKinopioCourseNo(gptr self, uint32_t world)               { return gm_u8(self + MJ2D_KINOPIO_COURSE + world); }
void dMj2dGame_setIbaraNow(gptr self, uint32_t n) { gm_set_u8(self + MJ2D_IBARA_NOW, (uint8_t)n); }
int  dMj2dGame_getIbaraNow(gptr self)             { return gm_u8(self + MJ2D_IBARA_NOW); }
/* the ambush enemies, 4 per world */
#define ENEMY(field, world, enemy) (self + (field) + (world) * 4 + (enemy))
void dMj2dGame_setCSEnemyRevivalCnt(gptr self, uint32_t world, uint32_t enemy, uint32_t n) { gm_set_u8(ENEMY(MJ2D_ENEMY_REVIVAL, world, enemy), (uint8_t)n); }
int  dMj2dGame_getCSEnemyRevivalCnt(gptr self, uint32_t world, uint32_t enemy) { return gm_u8(ENEMY(MJ2D_ENEMY_REVIVAL, world, enemy)); }
void dMj2dGame_setCSEnemySceneNo(gptr self, uint32_t world, uint32_t enemy, uint32_t n) { gm_set_u8(ENEMY(MJ2D_ENEMY_SCENE, world, enemy), (uint8_t)n); }
int  dMj2dGame_getCSEnemySceneNo(gptr self, uint32_t world, uint32_t enemy) { return gm_u8(ENEMY(MJ2D_ENEMY_SCENE, world, enemy)); }
void dMj2dGame_setCSEnemyPosIndex(gptr self, uint32_t world, uint32_t enemy, uint32_t node) { gm_set_u8(ENEMY(MJ2D_ENEMY_POS_INDEX, world, enemy), (uint8_t)node); }
int  dMj2dGame_getCSEnemyPosIndex(gptr self, uint32_t world, uint32_t enemy) { return gm_s8(ENEMY(MJ2D_ENEMY_POS_INDEX, world, enemy)); }
void dMj2dGame_setCSEnemyWalkDir(gptr self, uint32_t world, uint32_t enemy, uint32_t dir) { gm_set_u8(ENEMY(MJ2D_ENEMY_WALK_DIR, world, enemy), (uint8_t)dir); }
int  dMj2dGame_getCSEnemyWalkDir(gptr self, uint32_t world, uint32_t enemy) { return gm_s8(ENEMY(MJ2D_ENEMY_WALK_DIR, world, enemy)); }

/* ---- deaths per stage (the Super Guide shows after 8) ---- */
void dMj2dGame_setDeathCount(gptr self, uint32_t world, uint32_t stage, uint32_t switch_on, uint32_t count) {
    if (world <= 7 && count >= 8 && (stage < 24 || stage == 37))       /* (a normal world; stages up to the castle, or the airship) */
        gm_set_u8(self + MJ2D_GAME_COMPLETION, gm_u8(self + MJ2D_GAME_COMPLETION) | GAME_COMPLETION_SUPER_GUIDE);
    if (stage == 3 && world == 2 && switch_on) gm_set_u8(self + MJ2D_DEATH_COUNT_SWITCH, (uint8_t)count);   /* (World 3-4, switch on) */
    else gm_set_u8(self + MJ2D_DEATH_COUNT + world * STAGE_COUNT + stage, (uint8_t)count);
}
int dMj2dGame_getDeathCount(gptr self, uint32_t world, uint32_t stage, uint32_t switch_on) {
    if (switch_on && world == 2 && stage == 3) return gm_u8(self + MJ2D_DEATH_COUNT_SWITCH);
    return gm_u8(self + MJ2D_DEATH_COUNT + world * STAGE_COUNT + stage);
}
void dMj2dGame_setSwitchDeathCount(gptr self, uint32_t count) { gm_set_u8(self + MJ2D_DEATH_COUNT_SWITCH, (uint8_t)count); }
int  dMj2dGame_getSwitchDeathCount(gptr self)                 { return gm_u8(self + MJ2D_DEATH_COUNT_SWITCH); }

/* ---- items ---- */
void dMj2dGame_setStockItem(gptr self, uint32_t item, int32_t count) {
    if (count > 99) count = 99;                                         /* (MAX_STOCK_ITEM) */
    gm_set_u8(self + MJ2D_STOCK_ITEM + item, (uint8_t)count);
}

/* ---- the whole slot ---- */
void dMj2dGame_initialize(GM_CTX, gptr self) {
    GM_CALL(A_MEMCPY, 3, self, DEFAULT_GAME_IMAGE, MJ2D_SIZE);           /* *this = {} */
    gm_set_u16(self + MJ2D_REVISION, SAVE_REVISION);
    gm_set_u8(self + MJ2D_GAME_COMPLETION, GAME_COMPLETION_SAVE_EMPTY);
    for (uint32_t w = 0; w < WORLD_COUNT; w++) {                        /* the Toad rescue stages count as cleared */
        dMj2dGame_onCourseDataFlag(self, w, STAGE_RESCUE, COURSE_GOAL_MASK);
        if (w < WORLD_COUNT - 1) GM_LOOP();
    }
    for (int p = 0; p < 8; p++) {
        dMj2dGame_setPlrID(self, p, gm_s32(DEFAULT_PLAYER_TYPES + 4 * p));
        dMj2dGame_setPlrMode(self, p, 0);
        dMj2dGame_setRest(self, p, 5);
        dMj2dGame_setCreateItem(self, p, 0);
        if (p < 7) GM_LOOP();
    }
    for (uint32_t w = 0; w < WORLD_COUNT; w++) {
        dMj2dGame_setKinopioCourseNo(self, w, STAGE_COUNT);             /* (STAGE_e::COUNT: none) */
        for (uint32_t e = 0; e < 4; e++) {
            dMj2dGame_setCSEnemyPosIndex(self, w, e, 0xFF);
            dMj2dGame_setCSEnemyWalkDir(self, w, e, 2);                 /* (PATH_DIRECTION_e::INITIAL) */
            if (e < 3) GM_LOOP();
        }
        if (w < WORLD_COUNT - 1) GM_LOOP();
    }
    dMj2dGame_setIbaraNow(self, 2);
}
void dMj2dGame_versionUpdate(GM_CTX, gptr self) {                        /* (an older save's slot starts over) */
    if (gm_u8(self + MJ2D_REVISION) < 14) dMj2dGame_initialize(GM_PASS, self);
    gm_set_u16(self + MJ2D_REVISION, SAVE_REVISION);
}

/* ================================================================== hle entry points
   Register-exact (gm_i2.h): each entry also leaves the registers the PowerPC code leaves - the
   address it computed (self + index ...) in r3 / r4, the compares' CR0. */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
#undef R
#define R(n) ctx->r[n]
/* (each entry point: the memory a call may change is the slot, [SELF, SELF + MJ2D_SIZE)) */
/* a player's / world's byte: r3 = self + index (add r3, r3, r4) */
#define AT(i) (R(3) = SELF + A(i))
/* an ambush enemy's byte: r4 = world << 2, r3 = self + r4 + enemy */
#define AT_ENEMY() (R(4) = A(1) << 2, R(3) = SELF + R(4) + A(2))
/* a course's flags: r4 = stage << 2 (after world * 168), r3 = &flags - 132 */
#define AT_COURSE() (R(3) = SELF + (uint32_t)((int32_t)A(1) * 168), R(4) = A(2) << 2, R(3) += R(4))

/* initialize: framed (memcpy, then the loops inline) - the loops' last registers, as the PowerPC code leaves them */
static void mj2d_initialize_r(GM_CTX) {
    I2_FN(0x8180CF80u);
    gptr self = SELF; NV_R(30, self);
    R(5) = MJ2D_SIZE; R(4) = DEFAULT_GAME_IMAGE; R(3) = self;
    BL(0x8180CFA8u, mod_memcpy_81844C38);                                 /* *this = {} */
    R(3) = SAVE_REVISION; R(4) = 1;
    gm_set_u16(self + MJ2D_REVISION, SAVE_REVISION);
    gm_set_u8(self + MJ2D_GAME_COMPLETION, GAME_COMPLETION_SAVE_EMPTY);
    ctx->ctr = WORLD_COUNT;
    for (uint32_t w = 0; w < WORLD_COUNT; w++) {                          /* the Toad rescue stages count as cleared */
        R(3) = course(self, w, STAGE_RESCUE);
        R(4) = gm_u32(R(3)) | COURSE_GOAL_MASK; gm_set_u32(R(3), R(4));
        if (--ctx->ctr) GM_LOOP();
    }
    R(4) = 0; R(6) = 5;
    ctx->ctr = 8;
    for (uint32_t p = 0; p < 8; p++) {
        R(5) = DEFAULT_PLAYER_TYPES + 4 * p; R(7) = gm_u32(R(5));
        R(3) = self + 57 + p;
        gm_set_u8(self + MJ2D_PLAYER_CHARACTER + p, (uint8_t)R(7));
        gm_set_u8(self + MJ2D_PLAYER_POWERUP + p, 0);
        gm_set_u8(self + MJ2D_PLAYER_LIFE + p, 5);
        gm_set_u8(self + MJ2D_PLAYER_CREATE_ITEM + p, 0);
        if (--ctx->ctr) GM_LOOP();
    }
    R(3) = self + MJ2D_KINOPIO_COURSE; R(5) = 0; R(6) = STAGE_COUNT; R(7) = 4; R(8) = 0xFF; R(9) = 2;
    R(4) = self + MJ2D_ENEMY_WALK_DIR;
    for (uint32_t w = 0;; ) {
        gm_set_u8(self + MJ2D_KINOPIO_COURSE + w, STAGE_COUNT);           /* (STAGE_e::COUNT: none) */
        R(10) = self + w * 4 + 1873;
        ctx->ctr = 4;
        for (uint32_t e = 0; e < 4; e++) {
            R(10) = self + MJ2D_ENEMY_POS_INDEX + w * 4 + e;
            gm_set_u8(R(10), 0xFF);
            gm_set_u8(R(10) + 40, 2);                                     /* (PATH_DIRECTION_e::INITIAL) */
            if (--ctx->ctr) GM_LOOP();
        }
        w++; R(5) = w; R(4) += 4;
        if (CMPU(w, WORLD_COUNT) == 0) break;
        GM_LOOP();
    }
    R(3) = 2; gm_set_u8(self + MJ2D_IBARA_NOW, 2);
}
GM_HLE_VOID(mod_fn_800CDED0, SELF, MJ2D_SIZE) { mj2d_initialize_r(GM_PASS); }
static void mj2d_selftest(GM_CTX, gptr self);
GM_HLE_VOID(mod_fn_800CE020, SELF, MJ2D_SIZE) {                         /* versionUpdate: an older save's slot starts over */
    mj2d_selftest(GM_PASS, SELF);
    I2_FN(0x8180D104u);
    gptr self = SELF; NV_R(30, self);
    R(3) = gm_u8(self + MJ2D_REVISION);
    if (CMPU(R(3), 13) <= 0) { R(3) = self; BL(0x8180D12Cu, hle_mod_fn_800CDED0); }
    R(3) = SAVE_REVISION; gm_set_u16(self + MJ2D_REVISION, SAVE_REVISION);
}
GM_HLE_VOID(mod_fn_800CE060, SELF, MJ2D_SIZE) { dMj2dGame_setPlrID(SELF, A(1), A(2)); AT(1); }
GM_HLE_INT (mod_fn_800CE070, SELF, MJ2D_SIZE) { mj2d_selftest(GM_PASS, SELF); GM_RET(dMj2dGame_getPlrID(SELF, A(1))); }
GM_HLE_VOID(mod_fn_800CE080, SELF, MJ2D_SIZE) { dMj2dGame_setPlrMode(SELF, A(1), A(2)); AT(1); }
GM_HLE_INT (mod_fn_800CE090, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getPlrMode(SELF, A(1))); }
GM_HLE_VOID(mod_fn_800CE0A0, SELF, MJ2D_SIZE) { dMj2dGame_setRest(SELF, A(1), A(2)); AT(1); }
GM_HLE_INT (mod_fn_800CE0B0, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getRest(SELF, A(1))); }
GM_HLE_VOID(mod_fn_800CE0C0, SELF, MJ2D_SIZE) { dMj2dGame_setCreateItem(SELF, A(1), A(2)); R(5) &= 1; AT(1); }
GM_HLE_INT (mod_fn_800CE0D0, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getCreateItem(SELF, A(1))); }
GM_HLE_VOID(mod_fn_800CE0E0, SELF, MJ2D_SIZE) { dMj2dGame_setCoin(SELF, A(1), A(2)); AT(1); }
GM_HLE_INT (mod_fn_800CE0F0, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getCoin(SELF, A(1))); }
GM_HLE_VOID(mod_fn_800CE100, SELF, MJ2D_SIZE) { dMj2dGame_setScore(SELF, A(1)); }
GM_HLE_INT (mod_fn_800CE110, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getScore(SELF)); }
GM_HLE_VOID(mod_fn_800CE120, SELF, MJ2D_SIZE) {                         /* setStaffCreditHighScore */
    R(5) = gm_u16(SELF + MJ2D_STAFFROLL_HISCORE); CMPU(R(5), A(1));
    dMj2dGame_setStaffCreditHighScore(SELF, A(1));
}
GM_HLE_INT (mod_fn_800CE140, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getStaffCreditHighScore(SELF)); }
/* the hint movies' bitset: the library's range check (framed: 0x8180D1F0, 0x8180D6E8 ...), as calls */
static void otehon_check(GM_CTX, uint32_t ra) {                         /* (bitset::set's range check; returns if in range) */
    ctx->lr = ra;
    I2_FN(0x8180D1F0u);
    if (CMPU(R(4), 70) < 0) return;
    otehon_range_panic(GM_PASS, 75);
}
static void otehon_set_r(GM_CTX, uint32_t ra) {                         /* (bitset::set(n, r5), r3 = the bits) */
    ctx->lr = ra;
    I2_FN(0x8180D66Cu);
    if (CMPU(R(4), 70) >= 0) { otehon_range_panic(GM_PASS, 180); return; }
    gptr bits = R(3); uint32_t n = R(4);
    R(6) = gm_u32(bits); R(7) = 1; R(8) = gm_u32(bits + 4);
    R(5) = i2_rotl(R(5), n); R(9) = gm_u32(bits + 8);
    R(4) = i2_rotl(1, n);
    R(6) &= ~R(4); R(7) = R(8) & ~R(4); R(4) = R(9) & ~R(4);
    R(6) |= R(5); gm_set_u32(bits, R(6));
    R(6) = R(7) | R(5); R(4) |= R(5);
    gm_set_u32(bits + 4, R(6)); gm_set_u32(bits + 8, R(4));
}
static void otehon_test_r(GM_CTX, uint32_t ra) {                        /* (bitset::test(n), r3 = the bits) */
    ctx->lr = ra;
    I2_FN(0x8180D6E8u);
    if (CMPU(R(4), 70) >= 0) { otehon_range_panic(GM_PASS, 81); return; }
    gptr bits = R(3);
    R(5) = gm_u32(bits); R(4) = 0u - R(4); R(6) = gm_u32(bits + 4); R(3) = gm_u32(bits + 8);
    R(5) = R(6) | R(5);
    R(3) = i2_rotl(R(5) | R(3), R(4)) & 1;
}
GM_HLE_VOID(mod_fn_800CE150, SELF, MJ2D_SIZE) {                         /* onOtehonMenuOpenFlag(movie) */
    I2_FN(0x8180D1C4u);
    R(3) = SELF + MJ2D_OTEHON_OPEN;
    otehon_check(GM_PASS, 0x8180D1D8u);
    R(5) = 1; otehon_set_r(GM_PASS, 0x8180D1E0u);
}
GM_HLE_INT (mod_fn_800CE160, SELF, MJ2D_SIZE) {                         /* isOtehonMenuOpenFlag(movie) */
    I2_FN(0x8180D230u);
    R(3) = SELF + MJ2D_OTEHON_OPEN;
    otehon_test_r(GM_PASS, 0x8180D244u);
}
GM_HLE_INT (mod_fn_800CE190, SELF, MJ2D_SIZE) {                         /* getTotalWorldCollectCoin(world) */
    gptr self = SELF; uint32_t w = A(1);
    R(3) = dMj2dGame_getTotalWorldCollectCoin(GM_PASS, self, w);
    R(4) = self + 132 + (uint32_t)((int32_t)w * 168); R(5) = STAGE_COUNT;
    R(6) = gm_u32(R(4) + 4 * (STAGE_COUNT - 1)); R(7) = 3; R(8) = (R(6) >> 2) & 1;
    CMPU(3, 3); ctx->ctr = 0;
}
GM_HLE_INT (mod_fn_800CE210, SELF, MJ2D_SIZE) {                         /* isCollectCoin(world, stage, coin) */
    uint32_t r = dMj2dGame_isCollectCoin(SELF, A(1), A(2), A(3));
    R(4) = i2_bit(A(3)); R(3) = r;
}
GM_HLE_VOID(mod_fn_800CE240, SELF, MJ2D_SIZE) { dMj2dGame_setStartKinokoKind(SELF, A(1), A(2)); AT(1); }
GM_HLE_INT (mod_fn_800CE250, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getStartKinokoKind(SELF, A(1))); }
GM_HLE_VOID(mod_fn_800CE260, SELF, MJ2D_SIZE) {                         /* setDeathCount(world, stage, switch, count) */
    gptr self = SELF; uint32_t w = A(1), st = A(2), sw = A(3), n = A(4);
    int to_switch = 0;
    if (!(CMPU(w, 7) > 0) && !(CMPU(n, 8) < 0)) {
        int sg = CMPU(st, 24) < 0 || CMPU(st, 37) == 0;
        if (sg) { R(8) = gm_u8(self + 2) | GAME_COMPLETION_SUPER_GUIDE; gm_set_u8(self + 2, (uint8_t)R(8)); }
        else goto slot;                                                   /* (past the castle, not the airship: no World 3-4 either) */
    }
    to_switch = CMPU(st, 3) == 0 && CMPU(w, 2) == 0 && CMPU(sw, 0) != 0;
    if (to_switch) { gm_set_u8(self + MJ2D_DEATH_COUNT_SWITCH, (uint8_t)n); return; }
slot:
    R(4) = (uint32_t)((int32_t)w * STAGE_COUNT); R(3) = self + R(4) + st;
    gm_set_u8(R(3) + MJ2D_DEATH_COUNT, (uint8_t)n);
}
GM_HLE_INT (mod_fn_800CE2C0, SELF, MJ2D_SIZE) {                         /* getDeathCount(world, stage, switch) */
    gptr self = SELF; uint32_t w = A(1), st = A(2), sw = A(3);
    R(7) = self + (uint32_t)((int32_t)w * STAGE_COUNT) + st;
    CMPU(sw, 0);
    R(6) = R(7) + MJ2D_DEATH_COUNT;
    gptr a = sw ? self + MJ2D_DEATH_COUNT_SWITCH : R(6);
    if (CMPU(w, 2) != 0) a = R(6);
    if (CMPU(st, 3) != 0) a = R(6);
    R(3) = gm_u8(a);
}
GM_HLE_VOID(mod_fn_800CE2F0, SELF, MJ2D_SIZE) { dMj2dGame_setSwitchDeathCount(SELF, A(1)); }
GM_HLE_INT (mod_fn_800CE300, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getSwitchDeathCount(SELF)); }
GM_HLE_VOID(mod_fn_800CE310, SELF, MJ2D_SIZE) { dMj2dGame_setContinue(SELF, A(1), A(2)); AT(1); }
GM_HLE_INT (mod_fn_800CE320, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getContinue(SELF, A(1))); }
GM_HLE_VOID(mod_fn_800CE330, SELF, MJ2D_SIZE) {                         /* setStockItem(item, count) */
    if (CMPS(A(2), 99) >= 0) R(5) = 99;
    dMj2dGame_setStockItem(SELF, A(1), (int32_t)R(5)); AT(1);
}
GM_HLE_INT (mod_fn_800CE350, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_isWorldDataFlag(SELF, A(1), A(2))); }
GM_HLE_VOID(mod_fn_800CE360, SELF, MJ2D_SIZE) { uint32_t old = gm_u8(SELF + MJ2D_WORLD_COMPLETION + A(1)); dMj2dGame_onWorldDataFlag(SELF, A(1), A(2)); AT(1); R(4) = old | R(5); }
GM_HLE_VOID(mod_fn_800CE380, SELF, MJ2D_SIZE) { uint32_t old = gm_u8(SELF + MJ2D_WORLD_COMPLETION + A(1)); dMj2dGame_offWorldDataFlag(SELF, A(1), A(2)); AT(1); R(4) = old & ~R(5); }
GM_HLE_INT (mod__ZN9SaveBlock17GetLevelConditionEii, SELF, MJ2D_SIZE) {
    uint32_t r = dMj2dGame_getCourseDataFlag(SELF, A(1), A(2));
    R(4) = A(2) << 2; R(6) = gm_u8(FFEAT_COMPLETED_ALL_LEVELS); CMPU(R(6), 0); R(3) = r;
}
GM_HLE_INT (mod_CheckLevelCondition__9SaveBlockFiii, SELF, MJ2D_SIZE) {
    uint32_t feat = gm_u8(FFEAT_COMPLETED_ALL_LEVELS); CMPU(feat, 0);
    if (feat) { R(7) = 1; R(3) = 1; return; }
    uint32_t f = A(3); AT_COURSE();
    R(3) = gm_u32(R(3) + 132) & f;
    NONZERO(4, 7, R(3)); R(3) = R(7);
}
GM_HLE_VOID(mod_SetLevelCondition__9SaveBlockFiii, SELF, MJ2D_SIZE)   { dMj2dGame_onCourseDataFlag(SELF, A(1), A(2), A(3)); AT_COURSE(); R(4) = gm_u32(R(3) + 132); }
GM_HLE_VOID(mod_UnsetLevelCondition__9SaveBlockFiii, SELF, MJ2D_SIZE) { dMj2dGame_offCourseDataFlag(SELF, A(1), A(2), A(3)); AT_COURSE(); R(4) = gm_u32(R(3) + 132); }
GM_HLE_VOID(mod_fn_800CE430, SELF, MJ2D_SIZE) { dMj2dGame_setCSEnemyRevivalCnt(SELF, A(1), A(2), A(3)); AT_ENEMY(); }
GM_HLE_INT (mod_fn_800CE450, SELF, MJ2D_SIZE) { uint32_t r = dMj2dGame_getCSEnemyRevivalCnt(SELF, A(1), A(2)); R(4) = A(1) << 2; R(3) = r; }
GM_HLE_VOID(mod_fn_800CE470, SELF, MJ2D_SIZE) { dMj2dGame_setCSEnemySceneNo(SELF, A(1), A(2), A(3)); AT_ENEMY(); }
GM_HLE_INT (mod_fn_800CE490, SELF, MJ2D_SIZE) { uint32_t r = dMj2dGame_getCSEnemySceneNo(SELF, A(1), A(2)); R(4) = A(1) << 2; R(3) = r; }
GM_HLE_VOID(mod_fn_800CE4B0, SELF, MJ2D_SIZE) { dMj2dGame_setCSEnemyPosIndex(SELF, A(1), A(2), A(3)); AT_ENEMY(); }
GM_HLE_INT (mod_fn_800CE4D0, SELF, MJ2D_SIZE) { uint32_t r = (uint32_t)dMj2dGame_getCSEnemyPosIndex(SELF, A(1), A(2)); R(4) = A(1) << 2; R(3) = r; }
GM_HLE_VOID(mod_fn_800CE4F0, SELF, MJ2D_SIZE) { dMj2dGame_setCSEnemyWalkDir(SELF, A(1), A(2), A(3)); AT_ENEMY(); }
GM_HLE_INT (mod_fn_800CE510, SELF, MJ2D_SIZE) { uint32_t r = (uint32_t)dMj2dGame_getCSEnemyWalkDir(SELF, A(1), A(2)); R(4) = A(1) << 2; R(3) = r; }
GM_HLE_VOID(mod_fn_800CE530, SELF, MJ2D_SIZE) { dMj2dGame_setKinopioCourseNo(SELF, A(1), A(2)); AT(1); }
GM_HLE_INT (mod_fn_800CE540, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getKinopioCourseNo(SELF, A(1))); }
GM_HLE_VOID(mod_fn_800CE550, SELF, MJ2D_SIZE) { dMj2dGame_setIbaraNow(SELF, A(1)); }
GM_HLE_INT (mod_fn_800CE560, SELF, MJ2D_SIZE) { GM_RET(dMj2dGame_getIbaraNow(SELF)); }

/* ================================================================== self-test (RT_GM_SELFTEST=mj2d, gm_verify.c)
   Every entry point, with random slot contents and arguments in range, against its PowerPC
   version; the first time the game reads or updates a slot. Argument kinds: gm_selftest_arg. */
static const gm_test_t mj2d_tests[] = {
    GM_TEST(mod_fn_800CDED0, 0, ""),
    GM_TEST(mod_fn_800CE020, 0, ""),
    GM_TEST(mod_fn_800CE060, 0, "pv"),
    GM_TEST(mod_fn_800CE070, GMV_RET, "p"),
    GM_TEST(mod_fn_800CE080, 0, "pv"),
    GM_TEST(mod_fn_800CE090, GMV_RET, "p"),
    GM_TEST(mod_fn_800CE0A0, 0, "pv"),
    GM_TEST(mod_fn_800CE0B0, GMV_RET, "p"),
    GM_TEST(mod_fn_800CE0C0, 0, "pv"),
    GM_TEST(mod_fn_800CE0D0, GMV_RET, "p"),
    GM_TEST(mod_fn_800CE0E0, 0, "pv"),
    GM_TEST(mod_fn_800CE0F0, GMV_RET, "p"),
    GM_TEST(mod_fn_800CE100, 0, "v"),
    GM_TEST(mod_fn_800CE110, GMV_RET, ""),
    GM_TEST(mod_fn_800CE120, 0, "h"),
    GM_TEST(mod_fn_800CE140, GMV_RET, ""),
    GM_TEST(mod_fn_800CE150, 0, "m"),
    GM_TEST(mod_fn_800CE160, GMV_RET, "m"),
    GM_TEST(mod_fn_800CE190, GMV_RET, "w"),
    GM_TEST(mod_fn_800CE210, GMV_RET, "wsc"),
    GM_TEST(mod_fn_800CE240, 0, "wv"),
    GM_TEST(mod_fn_800CE250, GMV_RET, "w"),
    GM_TEST(mod_fn_800CE260, 0, "wsbk"),
    GM_TEST(mod_fn_800CE2C0, GMV_RET, "wsb"),
    GM_TEST(mod_fn_800CE2F0, 0, "v"),
    GM_TEST(mod_fn_800CE300, GMV_RET, ""),
    GM_TEST(mod_fn_800CE310, 0, "pv"),
    GM_TEST(mod_fn_800CE320, GMV_RET, "p"),
    GM_TEST(mod_fn_800CE330, 0, "in"),
    GM_TEST(mod_fn_800CE350, GMV_RET, "wv"),
    GM_TEST(mod_fn_800CE360, 0, "wv"),
    GM_TEST(mod_fn_800CE380, 0, "wv"),
    GM_TEST(mod__ZN9SaveBlock17GetLevelConditionEii, GMV_RET, "ws"),
    GM_TEST(mod_CheckLevelCondition__9SaveBlockFiii, GMV_RET, "wsv"),
    GM_TEST(mod_SetLevelCondition__9SaveBlockFiii, 0, "wsv"),
    GM_TEST(mod_UnsetLevelCondition__9SaveBlockFiii, 0, "wsv"),
    GM_TEST(mod_fn_800CE430, 0, "wev"),
    GM_TEST(mod_fn_800CE450, GMV_RET, "we"),
    GM_TEST(mod_fn_800CE470, 0, "wev"),
    GM_TEST(mod_fn_800CE490, GMV_RET, "we"),
    GM_TEST(mod_fn_800CE4B0, 0, "wev"),
    GM_TEST(mod_fn_800CE4D0, GMV_RET, "we"),
    GM_TEST(mod_fn_800CE4F0, 0, "wev"),
    GM_TEST(mod_fn_800CE510, GMV_RET, "we"),
    GM_TEST(mod_fn_800CE530, 0, "wv"),
    GM_TEST(mod_fn_800CE540, GMV_RET, "w"),
    GM_TEST(mod_fn_800CE550, 0, "v"),
    GM_TEST(mod_fn_800CE560, GMV_RET, ""),
};
static gptr mj2d_test_self;
static void mj2d_randomize(GM_CTX, int round) {
    for (uint32_t i = 0; i < MJ2D_SIZE; i += 4) gm_set_u32(mj2d_test_self + i, gm_rand() & gm_rand());   /* (sparse bits) */
    if (round % 3 == 0) gm_set_u8(mj2d_test_self + MJ2D_REVISION, gm_rand() % 16);   /* (versionUpdate: old saves) */
    gm_set_u8(FFEAT_COMPLETED_ALL_LEVELS, round % 5 == 0);
}
static void mj2d_selftest(GM_CTX, gptr self) {
    if (!gm_selftest_wanted("mj2d")) return;
    mj2d_test_self = self;
    const gptr ranges[] = { self, MJ2D_SIZE, FFEAT_COMPLETED_ALL_LEVELS, 1 };
    const gm_selftest_t t = { "mj2d", mj2d_tests, (int)(sizeof mj2d_tests / sizeof *mj2d_tests), 400, ranges, 2, mj2d_randomize, NULL };
    gm_selftest(GM_PASS, &t);
}
