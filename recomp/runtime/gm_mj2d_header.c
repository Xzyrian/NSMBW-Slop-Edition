/* gm_mj2d_header.c - dMj2dHeader_c, the save file's header (track B, gm.h, docs/DECOMP.md).
 *
 * Decompiled from the 8-player module's version (nsmbw-project v0.6.5,
 * wiimj2d/d_static/d_mj2d/d_mj2d_header.cpp): what isn't one slot's - the play counts of Free Mode
 * and Coin Battle per stage, the worlds open in those modes, the magic and the save revision.
 * Field offsets as the module's compiled code has them (they differ from the header file's
 * comments: the play counts start at 0x008). */
#include "gm_i2.h"
RT_STATE_FILE                                   /* (game code: its variables are part of a save state) */

/* ---- dMj2dHeader_c, the module's layout ---- */
#define HDR_MAGIC               0x000   /* char [4]: "glup" */
#define HDR_REVISION            0x004   /* u8 major, u8 minor */
#define HDR_PLAY_COUNT_FREE     0x008   /* u16 [10 worlds][42 stages] */
#define HDR_PLAY_COUNT_COIN     0x350   /* u16 [10][42] */
#define HDR_MULTI_WORLD_OPEN    0x698   /* u16: a bit per world */
#define HDR_SIZE                0x6A0

#define STAGE_COUNT 42
#define SAVE_REVISION 0x0E01            /* 14.1 */
#define S_MAGIC 0x8184A608u             /* the module's "glup" */

static gptr play_count(gptr self, uint32_t field, uint32_t world, uint32_t stage) {
    return self + field + world * (STAGE_COUNT * 2) + stage * 2;
}

void dMj2dHeader_initialize(GM_CTX, gptr self) {
    for (uint32_t i = 0; i < HDR_SIZE; i++) {                           /* memset(this, 0, sizeof *this) */
        gm_set_u8(self + i, 0);
        if (i < HDR_SIZE - 1) GM_LOOP();
    }
    for (uint32_t i = 0; i < 4; i++) {                                  /* memcpy(mMagic, "glup", 4) */
        gm_set_u8(self + HDR_MAGIC + i, gm_u8(S_MAGIC + i));
        if (i < 3) GM_LOOP();
    }
    gm_set_u16(self + HDR_REVISION, SAVE_REVISION);
}
void dMj2dHeader_versionUpdate(GM_CTX, gptr self) {                      /* (an older save starts over) */
    if (gm_u8(self + HDR_REVISION) < 14) dMj2dHeader_initialize(GM_PASS, self);
    gm_set_u16(self + HDR_REVISION, SAVE_REVISION);
}
int  dMj2dHeader_getPlayCountFreeMode(gptr self, uint32_t world, uint32_t stage) { return gm_u16(play_count(self, HDR_PLAY_COUNT_FREE, world, stage)); }
void dMj2dHeader_setPlayCountFreeMode(gptr self, uint32_t world, uint32_t stage, uint32_t n) { gm_set_u16(play_count(self, HDR_PLAY_COUNT_FREE, world, stage), (uint16_t)n); }
int  dMj2dHeader_getPlayCountCoinBattle(gptr self, uint32_t world, uint32_t stage) { return gm_u16(play_count(self, HDR_PLAY_COUNT_COIN, world, stage)); }
void dMj2dHeader_setPlayCountCoinBattle(gptr self, uint32_t world, uint32_t stage, uint32_t n) { gm_set_u16(play_count(self, HDR_PLAY_COUNT_COIN, world, stage), (uint16_t)n); }
void dMj2dHeader_onMultiWorldOpenFlag(gptr self, uint32_t world) {
    uint32_t sh = world & 63;
    gm_set_u16(self + HDR_MULTI_WORLD_OPEN, (uint16_t)(gm_u16(self + HDR_MULTI_WORLD_OPEN) | (sh > 31 ? 0 : 1u << sh)));
}
int dMj2dHeader_isMultiWorldOpenFlag(gptr self, uint32_t world) {
    uint32_t sh = world & 63;
    return (sh > 31 ? 0 : gm_u16(self + HDR_MULTI_WORLD_OPEN) >> sh) & 1;
}

/* ================================================================== hle entry points
   Register-exact (gm_i2.h): also the registers the PowerPC code leaves. */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
/* (each entry point: the memory a call may change is the header, [SELF, SELF + HDR_SIZE)) */
static void hdr_selftest(GM_CTX, gptr self);
static void hdr_init_regs(GM_CTX) { R(5) = S_MAGIC + 3; R(6) = gm_u8(S_MAGIC + 3); ctx->ctr = 0; }   /* (the two byte loops' last registers) */
#define AT_COUNT() (R(3) = SELF + (uint32_t)((int32_t)A(1) * 84), R(4) = A(2) << 1, R(3) += R(4))
GM_HLE_VOID(mod_fn_800CE580, SELF, HDR_SIZE) { dMj2dHeader_initialize(GM_PASS, SELF); hdr_init_regs(GM_PASS); R(4) = SAVE_REVISION; }
GM_HLE_INT (mod_fn_800CE600, SELF, HDR_SIZE) { uint32_t r = dMj2dHeader_getPlayCountFreeMode(SELF, A(1), A(2)); R(4) = A(2) << 1; R(3) = r; }
GM_HLE_VOID(mod_fn_800CE620, SELF, HDR_SIZE) { dMj2dHeader_setPlayCountFreeMode(SELF, A(1), A(2), A(3)); AT_COUNT(); }
GM_HLE_INT (mod_fn_800CE640, SELF, HDR_SIZE) { uint32_t r = dMj2dHeader_getPlayCountCoinBattle(SELF, A(1), A(2)); R(4) = A(2) << 1; R(3) = r; }
GM_HLE_VOID(mod_fn_800CE660, SELF, HDR_SIZE) { dMj2dHeader_setPlayCountCoinBattle(SELF, A(1), A(2), A(3)); AT_COUNT(); }
GM_HLE_VOID(mod_fn_800CE680, SELF, HDR_SIZE) {
    R(5) = gm_u16(SELF + HDR_MULTI_WORLD_OPEN); R(6) = 1;
    dMj2dHeader_onMultiWorldOpenFlag(SELF, A(1));
    R(4) = R(5) | i2_bit(A(1));
}
GM_HLE_INT (mod_fn_800CE6A0, SELF, HDR_SIZE) { hdr_selftest(GM_PASS, SELF); GM_RET(dMj2dHeader_isMultiWorldOpenFlag(SELF, A(1))); }
GM_HLE_VOID(mod_fn_800CE6C0, SELF, HDR_SIZE) {
    hdr_selftest(GM_PASS, SELF);
    R(4) = gm_u8(SELF + HDR_REVISION);
    if (CMPU(R(4), 13) <= 0) { dMj2dHeader_initialize(GM_PASS, SELF); hdr_init_regs(GM_PASS); }
    R(4) = SAVE_REVISION; gm_set_u16(SELF + HDR_REVISION, SAVE_REVISION);
}

/* ================================================================== self-test (RT_GM_SELFTEST=mj2d_header)
   Every entry point with random header contents and arguments (worlds and stages in range, any
   world for the flags), against its PowerPC version; the first time the game uses the header. */
static const gm_test_t hdr_tests[] = {
    GM_TEST(mod_fn_800CE580, 0, ""),
    GM_TEST(mod_fn_800CE600, GMV_RET, "ws"),
    GM_TEST(mod_fn_800CE620, 0, "wsv"),
    GM_TEST(mod_fn_800CE640, GMV_RET, "ws"),
    GM_TEST(mod_fn_800CE660, 0, "wsv"),
    GM_TEST(mod_fn_800CE680, 0, "f"),
    GM_TEST(mod_fn_800CE6A0, GMV_RET, "f"),
    GM_TEST(mod_fn_800CE6C0, 0, ""),
};
static gptr hdr_test_self;
static void hdr_randomize(GM_CTX, int round) {
    for (uint32_t i = 0; i < HDR_SIZE; i += 4) gm_set_u32(hdr_test_self + i, gm_rand());
    if (round & 1) gm_set_u8(hdr_test_self + HDR_REVISION, gm_rand() % 16);
}
static void hdr_selftest(GM_CTX, gptr self) {
    if (!gm_selftest_wanted("mj2d_header")) return;
    hdr_test_self = self;
    const gptr ranges[] = { self, HDR_SIZE };
    const gm_selftest_t t = { "mj2d_header", hdr_tests, (int)(sizeof hdr_tests / sizeof *hdr_tests), 200, ranges, 1, hdr_randomize, NULL };
    gm_selftest(GM_PASS, &t);
}
