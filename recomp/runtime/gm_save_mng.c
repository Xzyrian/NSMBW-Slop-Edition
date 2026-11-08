/* gm_save_mng.c - dSaveMng_c, the save manager (track B, gm.h, docs/DECOMP.md): all 13 of the
 * 8-player module's versions (nsmbw-project v0.6.5, wiimj2d/d_system/d_save_manager.cpp),
 * including construction, slot loading and the ordinary / multi-mode / quick-save NAND paths.
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

#define SAVEMNG_INSTANCE        (0x80430000u - 24512)
#define SAVEMNG_NAND_MANAGER    (0x80430000u - 24648)
#define SAVEMNG_CURRENT_WORLD   (0x80430000u - 25408)
#define SAVEMNG_INFO_INSTANCE   (0x80430000u - 24708)
#define SAVEMNG_STACK_GUARD     (0x81860000u - 300)
#define SAVEMNG_PLAYER_TYPE     (0x81860000u - 5828)
#define SAVEMNG_PLAYER_MODE     (0x81860000u - 5796)
#define SAVEMNG_CREATE_ITEM     (0x81860000u - 5764)
#define SAVEMNG_PLAYER_ORDER    (0x81860000u - 5732)
#define SAVEMNG_REST            (0x81850000u + 7564)
#define SAVEMNG_SERIALIZED_SIZE 16288
#define SAVEMNG_HEADER_SIZE     1696

/* Allocate and construct the 16,320-byte save manager, retaining the original heap-lock calls. */
static void dSaveMng_create(GM_CTX) {
    I2_FN(0x81813BC4u);
    BL(0x81813BDCu, hle_fn_8016E4F0); NV_R(30, R(3));
    R(3) = SAVEMNG_SIZE; R(4) = 32; BL(0x81813BECu, mfn_818434AC); NV_R(29, R(3));
    BL(0x81813BF4u, fn_800E01D0);
    R(3) = 0x80430000u; gm_set_u32(SAVEMNG_INSTANCE, R(29));
    R(3) = R(30); BL(0x81813C04u, hle_fn_8016E4F0);
}

/* Copy the NAND buffer into the manager, then reset its header and all six game slots. */
static void dSaveMng_refresh(GM_CTX, gptr self) {
    I2_FN(0x81813C1Cu);
    NV_R(30, self); BL(0x81813C38u, fn_800CFBB0);
    if (CMPU(R(3), 0) == 0) {
        R(3) = 0x81850000u; R(6) = R(3) - 20664; R(3) = R(6) + 16; R(5) = R(6) + 35;
        CR_SETBIT(ctx, 6, CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)); R(4) = 36;
        BL(0x81813CC4u, mod_OSPanic_818380F8);
        return;
    }
    R(4) = R(3) - 1; R(3) = self + 32; R(5) = self + 31; ctx->ctr = SAVEMNG_SERIALIZED_SIZE;
    do {
        R(6) = gm_u8(R(4) + 1); R(4)++; R(5)++; gm_set_u8(R(5), R(6));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    BL(0x81813C68u, hle_mod_fn_800CE6C0);
    NV_R(30, self + SAVEMNG_TEMP_GAME); NV_R(29, 3);
    do {
        R(3) = R(30) - 3 * SLOT_SIZE; BL(0x81813C78u, hle_mod_fn_800CE020);
        R(3) = R(30); BL(0x81813C80u, hle_mod_fn_800CE020);
        R(29)--; CMPU(R(29), 0); R(30) += SLOT_SIZE;
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
}

/* Queue the ordinary save buffer. The NAND thread returns zero on success. */
static void dSaveMng_startNandSave(GM_CTX, gptr self) {
    I2_FN(0x81813D38u);
    NV_R(30, self); R(3) = 0x80430000u; R(3) = gm_u32(SAVEMNG_NAND_MANAGER);
    R(4) = self + SAVEMNG_HEADER; BL(0x81813D5Cu, mod_fn_800CF080_81811A10);
    gm_set_u8(self, R(3));
}

/* These three methods use a 16,352-byte, 32-byte-aligned alloca frame. Its register save area is
 * relative to the caller's SP, not the aligned SP, so gm_prologue.py's fixed-frame form does not apply. */
typedef struct {
    ppc_context *ctx;
    uint32_t r27, r28, r29, r30, r31;
    int save27;
} savemng_buffer_frame_t;

static savemng_buffer_frame_t savemng_buffer_begin(ppc_context *ctx, uint8_t *base, int save27) {
    (void)base;
    savemng_buffer_frame_t f = { ctx, ctx->r[27], ctx->r[28], ctx->r[29], ctx->r[30], ctx->r[31], save27 };
    uint32_t sp = ctx->r[1], rem = sp & 31;
    gm_set_u32(sp + 4, ctx->lr);
    ctx->r[0] = rem; ctx->r[0] = 0xFFFFC020u - rem; ctx->xer_ca = 0xFFFFC020u >= rem;
    gm_set_u32(sp + ctx->r[0], sp); ctx->r[1] += ctx->r[0];
    ctx->r[0] = ctx->r[1] - ctx->r[0];
    uint32_t a = ctx->r[0]; ctx->r[0] = a - 8; ctx->xer_ca = ctx->r[0] < a;
    gm_set_u32(ctx->r[0], ctx->r[30]);
    a = ctx->r[0]; ctx->r[30] = a + 8; ctx->xer_ca = ctx->r[30] < a;
    gm_set_u32(ctx->r[30] - 16, ctx->r[28]); gm_set_u32(ctx->r[30] - 12, ctx->r[29]);
    if (save27) gm_set_u32(ctx->r[30] - 20, ctx->r[27]);
    return f;
}

static void savemng_buffer_end(savemng_buffer_frame_t *f) {
    ppc_context *ctx = f->ctx;
    ctx->r[29] = gm_u32(ctx->r[30] - 12);
    ctx->r[0] = ctx->r[31]; ctx->r[28] = gm_u32(ctx->r[30] - 16);
    if (f->save27) ctx->r[27] = gm_u32(ctx->r[30] - 20);
    ctx->r[31] = gm_u32(ctx->r[1]); ctx->r[30] = gm_u32(ctx->r[31] - 8);
    ctx->r[1] = ctx->r[31]; ctx->r[31] = ctx->r[0];
    ctx->r[0] = gm_u32(ctx->r[1] + 4); ctx->lr = ctx->r[0];
}

#define SAVEMNG_BUFFER_FRAME(save27) \
    savemng_buffer_frame_t savemng_buffer_frame_ __attribute__((cleanup(savemng_buffer_end))) = \
        savemng_buffer_begin(ctx, base, (save27)); \
    gptr gm_frame_sp = ctx->r[1]; (void)gm_frame_sp

static void savemng_copy_loop(GM_CTX, uint32_t count) {
    ctx->ctr = count;
    do {
        R(3)++; R(5) = gm_u8(R(3)); R(4)++; gm_set_u8(R(4), R(5));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
}

/* mode 0: all three normal and temporary slots; mode 1: quick-save the selected normal slot;
 * mode 2: delete the quick save by restoring its selected temporary slot from the normal slot. */
static void dSaveMng_startBufferedSave(GM_CTX, gptr self, int mode) {
    SAVEMNG_BUFFER_FRAME(mode != 0);
    R(29) = self; R(3) = 0x81860000u; R(3) = gm_u32(SAVEMNG_STACK_GUARD);
    gm_set_u32(gm_frame_sp + (mode == 0 ? 16332 : 16328), R(3));
    BL(mode == 0 ? 0x81813DB4u : mode == 1 ? 0x81813F7Cu : 0x81814070u, fn_800CFBB0);
    if (mode == 0) R(28) = R(3);
    else { R(28) = gm_frame_sp + 32; R(27) = R(3); }
    R(3) = gm_frame_sp + 32;
    BL(mode == 0 ? 0x81813DC0u : mode == 1 ? 0x81813F8Cu : 0x81814080u, mfn_81813E68);
    if (mode == 0) {
        R(3) = self + 31; R(4) = gm_frame_sp + 31; savemng_copy_loop(GM_PASS, SAVEMNG_HEADER_SIZE);
        R(3) = R(28) + SAVEMNG_HEADER_SIZE - 1; R(4) = gm_frame_sp + 32 + SAVEMNG_HEADER_SIZE - 1;
        savemng_copy_loop(GM_PASS, 3 * SLOT_SIZE);
        R(3) = R(28) + SAVEMNG_TEMP_GAME - 33; R(4) = gm_frame_sp + SAVEMNG_TEMP_GAME - 1;
        savemng_copy_loop(GM_PASS, 3 * SLOT_SIZE);
    } else {
        R(3) = R(27) - 1; R(4) = gm_frame_sp + 31; savemng_copy_loop(GM_PASS, SAVEMNG_SERIALIZED_SIZE);
        R(3) = gm_u8(self + SAVEMNG_SELECT_FILE); R(5) = SLOT_SIZE; ctx->ctr = R(5);
        R(3) = (uint32_t)((int32_t)R(3) * SLOT_SIZE); R(4) = R(3) + R(28); R(3) += self;
        R(3) += mode == 1 ? SAVEMNG_GAME - 1 : SAVEMNG_TEMP_GAME - 1;
        R(4) += SAVEMNG_TEMP_GAME - 33;
        do {
            R(3)++; R(5) = gm_u8(R(3)); R(4)++; gm_set_u8(R(4), R(5));
            if (--ctx->ctr) GM_LOOP(); else break;
        } while (1);
    }
    R(3) = 0x80430000u; R(3) = gm_u32(SAVEMNG_NAND_MANAGER); R(4) = gm_frame_sp + 32;
    BL(mode == 0 ? 0x81813E24u : mode == 1 ? 0x81813FE4u : 0x818140D8u, mod_fn_800CF080_81811A10);
    gm_set_u8(self, R(3));
    R(4) = 0x81860000u; R(4) = gm_u32(SAVEMNG_STACK_GUARD);
    R(5) = gm_u32(gm_frame_sp + (mode == 0 ? 16332 : 16328));
    if (CMPU(R(4), R(5)) != 0)
        BL(mode == 0 ? 0x81813E68u : mode == 1 ? 0x81814028u : 0x8181411Cu, mfn_81844FCC);
}

/* Copy live player, star-coin and world state into the selected slot before a NAND save. */
static void dSaveMng_prepareSave(GM_CTX, gptr self) {
    I2_FN(0x81814148u);
    R(4) = gm_u8(self + SAVEMNG_SELECT_FILE); R(4) = (uint32_t)(int8_t)R(4);
    R(4) = (uint32_t)((int32_t)R(4) * (int32_t)SLOT_SIZE); NV_R(24, self + R(4)); NV_R(30, R(24) + SAVEMNG_GAME);
    BL(0x81814198u, fn_800B5400);
    R(3) = 0x80430000u; R(4) = gm_u32(SAVEMNG_CURRENT_WORLD); R(3) = R(30); BL(0x818141A8u, hle_mod_fn_800CE100);
    R(3) = 0x81850000u; R(4) = 0x81860000u; R(5) = 0x81860000u; R(6) = 0x81860000u; R(7) = 0x81860000u;
    R(3) = SAVEMNG_REST; R(4) = SAVEMNG_PLAYER_MODE; R(5) = SAVEMNG_PLAYER_TYPE;
    NV_R(28, 8); NV_R(27, 0); NV_R(26, SAVEMNG_CREATE_ITEM); NV_R(25, SAVEMNG_PLAYER_ORDER);
    NV_R(21, SAVEMNG_REST - 4); NV_R(23, SAVEMNG_PLAYER_MODE - 4); NV_R(22, SAVEMNG_PLAYER_TYPE - 4); NV_R(29, 0);
    do {
        R(22) += 4; R(5) = gm_u32(R(22)); R(3) = R(30); R(4) = R(29); NV_R(20, R(21) + 4);
        BL(0x818141FCu, hle_mod_fn_800CE060);
        R(23) += 4; R(5) = gm_u32(R(23)); R(3) = R(30); R(4) = R(29); BL(0x8181420Cu, hle_mod_fn_800CE080);
        R(5) = gm_u8(R(21) + 7); R(3) = R(30); R(4) = R(29); BL(0x8181421Cu, hle_mod_fn_800CE0A0);
        R(5) = gm_u32(R(26) + R(27)); R(3) = R(30); R(4) = R(29); BL(0x8181422Cu, hle_mod_fn_800CE0C0);
        R(3) = R(25) + R(27); R(3) = gm_u8(R(3) + 3); R(4) = R(29); R(5) = (uint32_t)(int8_t)R(3); R(3) = R(30);
        BL(0x81814244u, hle_mod_fn_800CE0E0);
        R(28)--; R(29)++; CMPU(R(28), 0); R(27) += 4; R(21) = R(20);
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
    R(3) = 0x80430000u; NV_R(29, gm_u32(SAVEMNG_INFO_INSTANCE)); NV_R(28, 0); NV_R(23, R(29) + 917);
    do {
        NV_R(22, 4); NV_R(27, R(28) & 0xFF); NV_R(26, 0);
        do {
            R(3) = R(29); R(4) = R(28); R(5) = R(26); BL(0x81814288u, fn_800BBBB0);
            R(6) = gm_u8(R(3) + 3); NV_R(25, R(3)); R(3) = R(30); R(4) = R(27); R(5) = R(26);
            BL(0x818142A0u, hle_mod_fn_800CE470);
            R(6) = gm_u8(R(25) + 7); R(3) = R(30); R(4) = R(27); R(5) = R(26); BL(0x818142B4u, hle_mod_fn_800CE4B0);
            R(3) = gm_u8(R(25) + 11); R(4) = R(27); R(5) = R(26); R(6) = (uint32_t)(int8_t)R(3); R(3) = R(30);
            BL(0x818142CCu, hle_mod_fn_800CE4F0);
            R(22)--; CMPU(R(22), 0); R(26)++;
            if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
        } while (1);
        R(5) = gm_u8(R(23) + R(28)); R(3) = R(30); R(4) = R(27); BL(0x818142ECu, hle_mod_fn_800CE530);
        R(28)++; CMPU(R(28), 10);
        if (!CR_BIT(ctx, 2)) GM_LOOP(); else break;
    } while (1);
    R(3) = R(30); BL(0x81814300u, mfn_8180D634);
    R(3) = gm_u32(R(29) + 12);
    if (CMPS(R(3), 0) < 0) { R(4) = R(29) + 8; R(3) = R(30); BL(0x81814318u, mfn_8180D5E4); }
    NV_R(29, 0x80430000u); R(3) = gm_u32(SAVEMNG_INFO_INSTANCE); R(4) = 4; BL(0x81814328u, fn_800BBC70);
    R(4) = R(3); R(3) = R(30); BL(0x81814334u, hle_mod_fn_800CE550);
    R(3) = gm_u32(R(29) - 24708); R(4) = gm_u8(R(24) + 1730); R(3) = gm_u8(R(3) + 896);
    gm_set_u8(R(24) + 1735, R(3)); R(3) = R(4) & 0xFE; gm_set_u8(R(24) + 1730, R(3));
}

/* Select a slot and copy its saved player / world state into the live session. */
static void dSaveMng_initLoadGame(GM_CTX, gptr self, int32_t slot) {
    I2_FN(0x81814388u);
    R(5) = 0x81860000u; R(5) = gm_u32(SAVEMNG_STACK_GUARD); gm_set_u32(gm_frame_sp + 16, R(5));
    R(5) = (uint32_t)(slot * (int32_t)SLOT_SIZE); NV_R(28, self + R(5)); NV_R(30, R(28) + SAVEMNG_GAME);
    gm_set_u8(self + SAVEMNG_SELECT_FILE, slot); R(3) = R(30); BL(0x818143E0u, hle_mod_fn_800CE110);
    gm_set_u32(SAVEMNG_CURRENT_WORLD, R(3));
    NV_R(25, SAVEMNG_PLAYER_TYPE); NV_R(24, SAVEMNG_PLAYER_ORDER); NV_R(23, SAVEMNG_CREATE_ITEM - 4);
    NV_R(22, SAVEMNG_REST - 4); NV_R(21, SAVEMNG_PLAYER_MODE - 4); NV_R(27, 8); NV_R(26, 0); NV_R(29, 0);
    do {
        R(3) = R(30); R(4) = R(29); BL(0x81814434u, hle_mod_fn_800CE070);
        R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; gm_set_u32(R(25) + R(3), R(29));
        R(3) = R(30); R(4) = R(29); BL(0x81814448u, hle_mod_fn_800CE090);
        R(21) += 4; gm_set_u32(R(21), R(3));
        R(3) = R(30); R(4) = R(29); BL(0x81814458u, hle_mod_fn_800CE0B0);
        R(22) += 4; gm_set_u32(R(22), R(3));
        R(3) = R(30); R(4) = R(29); BL(0x81814468u, hle_mod_fn_800CE0D0);
        R(23) += 4; gm_set_u32(R(23), R(3));
        R(3) = R(30); R(4) = R(29); BL(0x81814478u, hle_mod_fn_800CE0F0);
        R(27)--; R(29)++; gm_set_u32(R(24) + R(26), R(3)); CMPU(R(27), 0); R(26) += 4;
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
    R(3) = gm_u32(SAVEMNG_INFO_INSTANCE); R(4) = R(3) + 8; R(3) = R(30); BL(0x818144A4u, mfn_8180D518);
    BL(0x818144A8u, hle_mod_fn_80060EF0); BL(0x818144ACu, mod_fn_80102A80_8181601C);
    R(3) = gm_u8(R(28) + 4136); NONZERO(4, 3, R(3)); gm_set_u8(gm_frame_sp + 8, R(3));
    R(3) = gm_frame_sp + 8; gm_set_u32(gm_frame_sp + 12, R(3)); BL(0x818144C8u, mfn_8183A488);
    R(3) = 0x81860000u; R(3) = gm_u32(SAVEMNG_STACK_GUARD); R(4) = gm_u32(gm_frame_sp + 16);
    if (CMPU(R(3), R(4)) != 0) BL(0x81814518u, mfn_81844FCC);
}

/* ================================================================== hle entry points
   Register-exact (gm_i2.h): also the registers the PowerPC code leaves. World-changing entry
   points use isolated native / PowerPC A/B runs rather than the verifier's double invocation. */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
static void savemng_selftest(GM_CTX, gptr self);
static uint32_t slot_r(GM_CTX) { CMPS(A(1), -1); R(4) = (uint32_t)(slot_of(SELF, (int32_t)A(1)) * (int32_t)SLOT_SIZE); return R(4); }
GM_HLE_INT (mod_getSaveGame__10dSaveMng_cFSc, 0, 0) { savemng_selftest(GM_PASS, SELF); gptr r = dSaveMng_getSaveGame(SELF, (int32_t)A(1)); slot_r(GM_PASS); R(3) = r; }
GM_HLE_INT (mod_getTempGame__10dSaveMng_cFSc, 0, 0) { gptr r = dSaveMng_getTempGame(SELF, (int32_t)A(1)); slot_r(GM_PASS); R(3) = r; }
GM_HLE_VERIFIED_(mod_create__10dSaveMng_cFPQ23EGG4Heap, GMV_IGNORE_POLLS, 0, 0) { dSaveMng_create(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_800E02D0, GMV_IGNORE_POLLS, SELF, SAVEMNG_SIZE) { dSaveMng_refresh(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_startNandSave__10dSaveMng_cFv, GMV_IGNORE_POLLS, 0, 0) { dSaveMng_startNandSave(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_800E0C20, GMV_IGNORE_POLLS, 0, 0) { dSaveMng_startBufferedSave(GM_PASS, SELF, 0); }
GM_HLE_VERIFIED_(mod_fn_800E0D20, GMV_IGNORE_POLLS, 0, 0) { dSaveMng_startBufferedSave(GM_PASS, SELF, 1); }
GM_HLE_VERIFIED_(mod_fn_800E11D0, GMV_IGNORE_POLLS, 0, 0) { dSaveMng_startBufferedSave(GM_PASS, SELF, 2); }
void chars_prepare_save(void);
GM_HLE_VERIFIED_(mod_fn_800E1690, GMV_IGNORE_POLLS, 0, 0) { chars_prepare_save(); dSaveMng_prepareSave(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_800E1840, GMV_IGNORE_POLLS, 0, 0) { dSaveMng_initLoadGame(GM_PASS, SELF, (int32_t)A(1)); }
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
