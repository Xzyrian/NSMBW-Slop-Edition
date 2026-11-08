/* gm_d_fukidashi.c - dfukidashiManager_c, the eight speech-bubble layouts.
 * Track B (gm_i2.h, docs/DECOMP.md), instance 2. The 4,904-byte manager and all eight
 * 572-byte child layouts remain in big-endian guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define FK_SIZE       4904
#define FK_CHILD      328
#define FK_CHILD_SIZE 572
#define FK_CHILDREN   8
#define FK_CTOR_INSTANCE (ctx->r[13] - 21344) /* module's manager instance */
#define FK_INSTANCE   0x8042ACA0u            /* original manager pointer cleared by the module destructor */

static void fk_constructor(GM_CTX, gptr self) {
    I2_FN(0x81831134u);
    NV_R(31, self);
    BL(0x8183114Cu, __ct__7dBase_cFv_8006C420);
    R(4) = 0x80320000u + 29392; gm_set_u32(self + 96, R(4));
    R(3) = self + 116; BL(0x81831160u, fn_80006AA0);
    R(3) = self + FK_CHILD; R(4) = 0x800B0000u + 5344; R(5) = 0x800B0000u + 5856;
    R(6) = FK_CHILD_SIZE; R(7) = FK_CHILDREN; BL(0x81831180u, __construct_array_802DC9A0);
    gm_set_u32(FK_CTOR_INSTANCE, self); R(3) = self;
}

static void fk_destructor(GM_CTX, gptr self, uint32_t flags) {
    I2_FN(0x8183119Cu);
    NV_R(29, flags); NV_R(28, 0); NV_R(30, self);
    R(4) = 0; BL(0x818311CCu, mod___dt__7dBase_cFv_818083A4);
    gm_set_u32(FK_INSTANCE, R(28)); NV_R(28, self - 244);
    gm_set_u32(self + 96, 0x81850000u + 14380); NV_R(27, FK_CHILDREN);
    for (;;) {
        uint32_t ea = R(28) + FK_CHILD_SIZE; R(3) = gm_u32(ea); NV_R(28, ea);
        R(4) = (uint32_t)-1; R(3) = gm_u32(R(3) + 8); ctx->ctr = R(3); R(3) = R(28);
        ctx->lr = 0x81831200u; ppc_call_indirect(ctx, base, ctx->ctr);
        NV_R(27, R(27) - 1);
        if (CMPU(R(27), 0) <= 0) break;
        GM_LOOP();
    }
    if (CMPS(R(29), 1) >= 0) { R(3) = self; BL(0x8183121Cu, hle__Z17FreeFromGameHeap1Pv); }
    R(3) = self;
}

static void fk_create(GM_CTX, gptr self) {
    I2_FN(0x81831240u);
    NV_R(29, self); R(4) = 0x80320000u + 29348; R(3) = self + 116; BL(0x8183126Cu, fn_80006BE0);
    if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
    NV_R(31, self + FK_CHILD); NV_R(30, 0);
    for (;;) {
        R(3) = R(31); R(4) = self + 116; BL(0x81831290u, fn_800B1760);
        if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
        NV_R(30, R(30) + 1); NV_R(31, R(31) + FK_CHILD_SIZE);
        if (CMPS(R(30), 8) >= 0) break;
        GM_LOOP();
    }
    R(3) = 1;
}

static void fk_execute(GM_CTX, gptr self) {
    I2_FN(0x818312D0u);
    NV_R(30, self); R(3) = (uint32_t)-1; BL(0x818312F0u, isGameStop__8dGameComFUl_800B3B50);
    if (CMPS(R(3), 0) != 0) { R(3) = 1; return; }
    NV_R(31, self + FK_CHILD); NV_R(30, 0);
    for (;;) {
        R(3) = R(31); BL(0x81831310u, fn_800B1910);
        NV_R(30, R(30) + 1); NV_R(31, R(31) + FK_CHILD_SIZE);
        if (CMPS(R(30), 8) >= 0) break;
        GM_LOOP();
    }
    R(3) = 1;
}

static void fk_draw(GM_CTX, gptr self) {
    I2_FN(0x8183133Cu);
    NV_R(31, self + FK_CHILD); NV_R(30, 0);
    for (;;) {
        R(3) = R(31); BL(0x81831360u, fn_800B1990);
        NV_R(30, R(30) + 1); NV_R(31, R(31) + FK_CHILD_SIZE);
        if (CMPS(R(30), 8) >= 0) break;
        GM_LOOP();
    }
    R(3) = 1;
}

static void fk_doDelete(GM_CTX, gptr self) {
    I2_FN(0x8183138Cu);
    NV_R(30, self); R(3) = self + 116; BL(0x818313ACu, fn_80006BF0);
    if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
    NV_R(31, self + FK_CHILD); NV_R(30, 0);
    for (;;) {
        R(3) = R(31); BL(0x818313CCu, fn_800B19B0);
        if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
        NV_R(30, R(30) + 1); NV_R(31, R(31) + FK_CHILD_SIZE);
        if (CMPS(R(30), 8) >= 0) break;
        GM_LOOP();
    }
    R(3) = 1;
}

/* Write a display value into every child whose player and type match. Player eight selects type one. */
static void fk_setValue(GM_CTX, gptr self, uint32_t type, uint32_t player, uint32_t value) {
    R(7) = CMPU(player, 8) == 0 ? 1 : type;
    R(3) = self + 325; ctx->ctr = FK_CHILDREN;
    do {
        uint32_t ea = R(3) + FK_CHILD_SIZE; R(4) = gm_u8(ea); R(3) = ea;
        if (CMPU(R(4), 1) == 0 && CMPU(gm_u32(R(3) - 25), player) == 0 && CMPU(gm_u32(R(3) - 29), R(7)) == 0)
            gm_set_u32(R(3) - 9, value);
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    } while (1);
}

/* Set or clear a session-info display flag for a valid player type and character. */
static void fk_setInfoFlag(GM_CTX, uint32_t character, uint32_t playerType, uint32_t value) {
    if (CMPU(playerType, 21) > 0 || CMPS(character, 0) < 0 || CMPU(playerType, 7) > 0) return;
    R(3) = gm_u32(0x80430000u - 24708); R(5) = (uint32_t)((int32_t)character * 22);
    R(3) += R(5); R(3) += CMPU(character, 4) < 0 ? 2814 : 2836;
    R(4) = value; gm_set_u8(R(3), R(4));
}

#define SELF GM_ARG(0)
#define FK_MEM SELF, FK_SIZE, FK_INSTANCE, 4
GM_HLE_VERIFIED_(mod_fn_80156ED0, GMV_IGNORE_POLLS, FK_MEM) { fk_constructor(GM_PASS, SELF); }
GM_HLE(mod_fn_80156F40) { fk_destructor(GM_PASS, SELF, GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_80156FD0, GMV_IGNORE_POLLS, FK_MEM) { fk_create(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_80157060, GMV_IGNORE_POLLS, FK_MEM) { fk_execute(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_801570D0, GMV_IGNORE_POLLS, FK_MEM) { fk_draw(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_80157120, GMV_IGNORE_POLLS, FK_MEM) { fk_doDelete(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80157220, FK_MEM) { fk_setValue(GM_PASS, SELF, GM_ARG(1), GM_ARG(2), GM_ARG(3)); }
GM_HLE(mod_fn_80157310) { fk_setInfoFlag(GM_PASS, GM_ARG(0), GM_ARG(1), 1); }
GM_HLE(mod_fn_80157360) { fk_setInfoFlag(GM_PASS, GM_ARG(0), GM_ARG(1), 0); }
