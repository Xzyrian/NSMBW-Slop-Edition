/* gm_save_mng.c - dSaveMng_c, the save manager (track B, gm.h, docs/DECOMP.md): the 8-player
 * module's versions (nsmbw-project v0.6.5, wiimj2d/d_system/d_save_manager.cpp), in part - the
 * slot accessors and copies. The NAND saving (startNandSave ...) stays recompiled for now.
 *
 * dSaveMng_c holds the whole save file in memory: the header, the three slots, and a "temp" copy
 * of each slot for the quick save (a mid-world save that is used once). */
#include "gm_i2.h"
RT_STATE_FILE                                   /* (game code: its variables are part of a save state) */

#define SAVEMNG_HEADER          0x0020  /* dMj2dHeader_c (gm_mj2d_header.c) */
#define SAVEMNG_SELECT_FILE     0x0026  /*   s8 header.mLastSelectedFile: the slot in play */
#define SAVEMNG_GAME            0x06C0  /* dMj2dGame_c [3]: the slots */
#define SAVEMNG_TEMP_GAME       0x2340  /* dMj2dGame_c [3]: the quick saves */
#define SLOT_SIZE               0x0980  /* (a slot's stride; the module's slot data is 0x970) */
#define SAVEMNG_SIZE            (SAVEMNG_TEMP_GAME + 3 * SLOT_SIZE)

void dMj2dGame_initialize(GM_CTX, gptr self);   /* gm_mj2d_game.c */

static int32_t slot_of(gptr self, int32_t slot) { return slot == -1 ? gm_s8(self + SAVEMNG_SELECT_FILE) : (int8_t)slot; }
gptr dSaveMng_getSaveGame(gptr self, int32_t slot) { return self + SAVEMNG_GAME + slot_of(self, slot) * SLOT_SIZE; }      /* -1: the slot in play */
gptr dSaveMng_getTempGame(gptr self, int32_t slot) { return self + SAVEMNG_TEMP_GAME + slot_of(self, slot) * SLOT_SIZE; }

/* "copy file" on the file select: the slot, and a fresh quick save for it */
void dSaveMng_saveGameCopy(GM_CTX, gptr self, int32_t dst, int32_t src) {
    gptr to = self + SAVEMNG_GAME + dst * SLOT_SIZE, from = self + SAVEMNG_GAME + src * SLOT_SIZE;
    for (uint32_t i = 0; i < SLOT_SIZE; i++) {
        gm_set_u8(to + i, gm_u8(from + i));
        if (i < SLOT_SIZE - 1) GM_LOOP();
    }
    dMj2dGame_initialize(GM_PASS, self + SAVEMNG_TEMP_GAME + dst * SLOT_SIZE);
}
void dSaveMng_calcCRC(gptr self) { (void)self; }                       /* (the module's JSON saves have none) */
/* continuing from a quick save: it becomes the slot */
void dSaveMng_loadQuickSaveData(GM_CTX, gptr self, int32_t slot) {
    gm_set_u8(self + SAVEMNG_SELECT_FILE, (uint8_t)slot);
    gptr to = self + SAVEMNG_GAME + slot * SLOT_SIZE, from = self + SAVEMNG_TEMP_GAME + slot * SLOT_SIZE;
    for (uint32_t i = 0; i < SLOT_SIZE; i++) {
        gm_set_u8(to + i, gm_u8(from + i));
        if (i < SLOT_SIZE - 1) GM_LOOP();
    }
}

/* ================================================================== hle entry points
   Register-exact (gm_i2.h): also the registers the PowerPC code leaves. */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
static void savemng_selftest(GM_CTX, gptr self);
static uint32_t slot_r(GM_CTX) { CMPS(A(1), -1); R(4) = (uint32_t)(slot_of(SELF, (int32_t)A(1)) * (int32_t)SLOT_SIZE); return R(4); }
GM_HLE_INT (mod_getSaveGame__10dSaveMng_cFSc, 0, 0) { savemng_selftest(GM_PASS, SELF); gptr r = dSaveMng_getSaveGame(SELF, (int32_t)A(1)); slot_r(GM_PASS); R(3) = r; }
GM_HLE_INT (mod_getTempGame__10dSaveMng_cFSc, 0, 0) { gptr r = dSaveMng_getTempGame(SELF, (int32_t)A(1)); slot_r(GM_PASS); R(3) = r; }
GM_HLE_VOID(mod_fn_800E03E0, SELF, SAVEMNG_SIZE) {                       /* saveGameCopy(dst, src): framed; the slot's fresh quick save is the native initialize */
    I2_FN(0x81813CE4u);
    gptr self = SELF; int32_t dst = (int32_t)A(1), src = (int32_t)A(2);
    gptr to = self + SAVEMNG_GAME + (uint32_t)dst * SLOT_SIZE, from = self + SAVEMNG_GAME + (uint32_t)src * SLOT_SIZE;
    for (uint32_t i = 0; i < SLOT_SIZE; i++) {
        gm_set_u8(to + i, gm_u8(from + i));
        if (i < SLOT_SIZE - 1) GM_LOOP();
    }
    R(4) = self + (uint32_t)dst * SLOT_SIZE; R(5) = to + SLOT_SIZE - 1; R(6) = gm_u8(from + SLOT_SIZE - 1); R(3) = from + SLOT_SIZE - 1;
    ctx->ctr = 0;
    R(3) = R(4) + SAVEMNG_TEMP_GAME;
    BL(0x81813D24u, hle_mod_fn_800CDED0);                                /* dMj2dGame_c::initialize */
}
GM_HLE_VOID(mod_calcCRC__10dSaveMng_cFv, 0, 0)      { dSaveMng_calcCRC(SELF); }
GM_HLE_VOID(mod_fn_800E1940, SELF, SAVEMNG_SIZE) {
    gptr self = SELF; int32_t slot = (int32_t)A(1);
    dSaveMng_loadQuickSaveData(GM_PASS, self, slot);
    gptr from = self + SAVEMNG_TEMP_GAME + (uint32_t)slot * SLOT_SIZE;
    R(3) = from + SLOT_SIZE - 1; R(4) = gm_u8(R(3)); R(5) = SLOT_SIZE; ctx->ctr = 0;
}

/* ================================================================== self-test (RT_GM_SELFTEST=save_mng) */
static const gm_test_t savemng_tests[] = {
    GM_TEST(mod_getSaveGame__10dSaveMng_cFSc, GMV_RET, "T"),
    GM_TEST(mod_getTempGame__10dSaveMng_cFSc, GMV_RET, "T"),
    GM_TEST(mod_fn_800E03E0, 0, "SS"),
    GM_TEST(mod_calcCRC__10dSaveMng_cFv, 0, ""),
    GM_TEST(mod_fn_800E1940, 0, "S"),
};
static gptr savemng_test_self;
static void savemng_randomize(GM_CTX, int round) {
    (void)round;
    for (uint32_t i = 0; i < SAVEMNG_SIZE; i += 4) gm_set_u32(savemng_test_self + i, gm_rand());
    gm_set_u8(savemng_test_self + SAVEMNG_SELECT_FILE, gm_rand() % 3);
}
static uint32_t savemng_arg(char k) { return k == 'T' ? (gm_rand() & 1 ? (uint32_t)-1 : gm_rand() % 3) : 0xDEADBEEFu; }   /* a slot or -1 */
static void savemng_selftest(GM_CTX, gptr self) {
    if (!gm_selftest_wanted("save_mng")) return;
    savemng_test_self = self;
    const gptr ranges[] = { self, SAVEMNG_SIZE };
    const gm_selftest_t t = { "save_mng", savemng_tests, (int)(sizeof savemng_tests / sizeof *savemng_tests), 50, ranges, 1, savemng_randomize, savemng_arg };
    gm_selftest(GM_PASS, &t);
}
