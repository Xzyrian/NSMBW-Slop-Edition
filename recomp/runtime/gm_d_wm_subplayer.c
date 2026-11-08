/* gm_d_wm_subplayer.c - daWmSubPlayer_c and its position-history node:
 * companion-player creation / models, ordering, walking speed and state queries
 * (track B, gm_i2.h). Objects and the module's ordering tables stay in guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define WSP_PLAYER_MANAGER (0x80430000u - 24160)
#define WSP_TYPE_TABLE     (0x81850000u - 25628)
#define WSP_ORDER_TABLE    (0x81850000u - 5208)
#define WSP_SCENE_TABLE    (0x81860000u - 5796)
#define WSP_STAR_TABLE0    (0x81860000u - 5828)
#define WSP_STAR_TABLE1    (0x81860000u - 5764)

#define LF(n, a) (ctx->f[n].d = ctx->ps1[n] = ldfs(base, (a)))

/* The visible companions are numbered after the active players preceding them. */
static uint32_t wsp_order(GM_CTX, gptr self) {
    R(3) = gm_u32(self + 4) & 15;
    CR0(ctx, R(3));
    if (!R(3)) { R(3) = 1; return R(3); }
    R(4) = gm_u32(WSP_PLAYER_MANAGER); ctx->ctr = R(3); R(3) = 1;
    do {
        R(4) = gm_u32(R(4) + 388); R(5) = gm_u8(R(4) + 292); R(3) += R(5);
        ctx->ctr--; if (ctx->ctr) GM_LOOP();
    } while (ctx->ctr);
    return R(3);
}

/* getPlayerOrderDistance and getPlayerOrderAngle share the ordering-table index. */
static uint32_t wsp_orderTableIndex(GM_CTX, gptr self, uint32_t order, uint32_t ra) {
    BL(ra, fn_2_1811B0_808EE960);
    CMPU(R(3), 0);
    if (R(3)) {
        R(4) = 0x81850000u; R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu;
        R(4) += (uint32_t)-5208; R(3) += R(4);
        R(3) = gm_u32(R(3) - 4) + order;
    } else {
        R(3) = 0;
    }
    return R(3);
}

static uint32_t wsp_create(GM_CTX, gptr self) {
    I2_FN(0x81828914u);
    NV_R(30, self); BL(0x8182892Cu, ext_fn_2_17DA80_81845420);
    R(4) = 0x80370000u; R(5) = gm_u32(R(4) + 31816);
    R(3) = self + 532; R(4) = 16; BL(0x81828940u, fn_2_181FE0_808EF790);
    R(3) = 1; return R(3);
}

static void wsp_loadModel(GM_CTX, gptr self) {
    I2_FN(0x81828958u);
    R(5) = WSP_TYPE_TABLE; R(4) = 0x81860000u; NV_R(28, self);
    R(0) = gm_u32(self + 4); NV_R(31, R(0) & 15);
    R(0) = i2_rotl(R(0), 2) & 0x3Cu; NV_R(30, gm_u32(R(5) + R(0)));
    R(3) = 12; BL(0x8182899Cu, mod___nw__FUl_818432E4);
    NV_R(29, R(3)); CR0(ctx, R(29));
    if (R(29)) {
        R(3) = R(30); BL(0x818289ACu, mfn_81806A48);
        R(4) = R(3); R(3) = R(29); BL(0x818289B8u, __ct__11dPyMdlMng_cFQ211dPyMdlMng_c11ModelType_e_800D6CC0);
    }
    gm_set_u32(self + 460, R(3));
    R(4) = R(31); R(5) = (i2_rotl(R(30), 2) & 0xFFFFFFFCu) + 0x81860000u;
    R(5) = gm_u32(R(5) - 5796) & 0xFFu; R(6) = 1;
    BL(0x818289D8u, create__11dPyMdlMng_cFUcUcQ211dPyMdlMng_c11SceneType_e_800D6DF0);
    gm_set_u32(self + 656, 21); R(3) = 84; BL(0x818289E8u, __nwa__FUl_802B9250);
    gm_set_u32(self + 652, R(3)); NV_R(29, 0); NV_R(30, 0);
    while (R(29) < gm_u32(self + 656)) {
        R(3) = 12; BL(0x81828A00u, __nw__FUl_802B9210);
        R(4) = gm_u32(self + 652); NV_R(29, R(29) + 1);
        gm_set_u32(R(4) + R(30), R(3)); NV_R(30, R(30) + 4);
        R(0) = gm_u32(self + 656); CMPS(R(29), R(0));
        if (CR_BIT(ctx, 0)) GM_LOOP();
    }
    R(4) = 0x80980000u + 23352; R(5) = 0x80980000u + 23368;
    R(3) = self; R(6) = R(4); R(7) = 1; BL(0x81828A3Cu, fn_800F6710);
}

static void wsp_calcWalkSpeed(GM_CTX, gptr self) {
    I2_FN(0x81828BD4u);
    uint32_t saved_cr = ctx->cr;
    R(12) = saved_cr; NV_R(30, self); R(4) = gm_u32(0x81860000u - 300);
    ctx->f[31].d = ctx->ps1[31] = ldfs(base, self + 268);
    BL(0x81828C08u, fn_2_1817D0_808EEF80); CMPU(R(3), 0);
    if (!R(3)) goto check_speed_cap;

    wsp_order(GM_PASS, self);
    R(4) = WSP_ORDER_TABLE; R(3) = (i2_rotl(R(3), 2) & 0xFFFFFFFCu) + R(4);
    LF(1, R(3) + 28); R(3) = self; BL(0x81828CE0u, fn_2_1804A0_808EDC50);
    goto store_speed;

check_speed_cap:
    R(3) = gm_u32(self + 512); CMPU(R(3), 2);
    if (CR_BIT(ctx, 0)) goto store_speed;
    R(4) = R(1) + 20; R(3) = self; BL(0x81828C58u, mfn_81828A94);
    cr_cmp_u(ctx, 2, R(3), 0);
    if (CR_BIT(ctx, 10)) {
        R(3) = self; BL(0x81828C68u, fn_2_180970_808EE120);
        LF(0, 0x81850000u - 30984); cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
        if (!CR_BIT(ctx, 0)) goto speed_above_target;
    }
    LF(1, 0x81850000u - 30876);
call_speed_two:
    R(3) = self; BL(0x81828C88u, fn_2_1804A0_808EDC50); R(3) = 2;
store_walk_state:
    gm_set_u32(self + 680, R(3));
blend_distance:
    LF(0, self + 268);
    ctx->f[1].u = ld64(base, 0x81850000u - 30664);
    ctx->f[2].u = ld64(base, 0x81850000u - 30584);
    ctx->f[0].d = ctx->f[0].d * ctx->f[1].d;
    ctx->f[0].d = ctx->f[31].d * ctx->f[2].d + ctx->f[0].d;
    LF(2, R(1) + 20); ctx->f[1].d = frsp(ctx->f[0].d);
    if (CR_BIT(ctx, 10)) {
        ctx->f[0].u = ctx->f[1].u;
    } else {
        LF(0, 0x81850000u - 31116);
    }
    LF(3, 0x81850000u - 30984); cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[3].d);
    if (CR_BIT(ctx, 1)) ctx->f[0].u = ctx->f[1].u;
    GM_LOOP();
    stfs(base, self + 268, ctx->f[0].d);
    goto finish;

speed_above_target:
    LF(0, 0x81850000u - 30752); cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if (CR_BIT(ctx, 0)) {
        LF(1, 0x81850000u - 30808); GM_LOOP(); goto call_speed_two;
    }
    LF(0, 0x81850000u - 30868); cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if (!CR_BIT(ctx, 1)) {
        LF(1, 0x81850000u - 30800); R(3) = self;
        BL(0x81828DACu, fn_2_1804A0_808EDC50); GM_LOOP(); goto blend_distance;
    }
    LF(1, 0x81850000u - 30756); R(3) = self;
    BL(0x81828D94u, fn_2_1804A0_808EDC50); R(3) = 1; GM_LOOP(); goto store_walk_state;

store_speed:
    LF(0, self + 268);
    ctx->f[1].u = ld64(base, 0x81850000u - 30664);
    ctx->f[2].u = ld64(base, 0x81850000u - 30584);
    ctx->f[0].d = frsp(ctx->f[0].d * ctx->f[1].d + ctx->f[31].d * ctx->f[2].d);
    stfs(base, self + 268, ctx->f[0].d);

finish:
    R(3) = gm_u32(0x81860000u - 300); R(4) = R(3); CMPU(R(3), R(4));
    R(12) = saved_cr; ctx->cr = (ctx->cr & ~0xF00000u) | (saved_cr & 0xF00000u);
}

static double wsp_getPlayerOrderDistance(GM_CTX, gptr self) {
    I2_FN(0x81828DB4u);
    uint32_t order = wsp_order(GM_PASS, self); NV_R(30, order);
    wsp_orderTableIndex(GM_PASS, self, order, 0x81828DFCu);
    R(4) = WSP_ORDER_TABLE; R(3) = (i2_rotl(R(3), 2) & 0xFFFFFFFCu) + R(4);
    LF(1, R(3) + 60); return ctx->f[1].d;
}

static uint32_t wsp_getPlayerOrderTableIndex(GM_CTX, gptr self, uint32_t order) {
    I2_FN(0x81828E4Cu);
    NV_R(30, order); BL(0x81828E64u, fn_2_1811B0_808EE960); CMPU(R(3), 0);
    if (R(3)) {
        R(4) = 0x81850000u; R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu;
        R(4) += (uint32_t)-5208; R(3) += R(4); R(3) = gm_u32(R(3) - 4) + order;
    } else {
        R(3) = 0;
    }
    return R(3);
}

static uint32_t wsp_getPlayerOrderAngle(GM_CTX, gptr self) {
    I2_FN(0x81828EA0u);
    uint32_t order = wsp_order(GM_PASS, self); NV_R(30, order);
    wsp_orderTableIndex(GM_PASS, self, order, 0x81828EE8u);
    R(4) = WSP_ORDER_TABLE; R(3) = (i2_rotl(R(3), 1) & 0xFFFFFFFEu) + R(4);
    R(3) = (uint32_t)(int16_t)gm_u16(R(3) + 200); return R(3);
}

static uint32_t wsp_isPlayerType(GM_CTX, gptr self, uint32_t type) {
    R(3) = gm_u32(self + 4); R(5) = WSP_TYPE_TABLE;
    R(3) = i2_rotl(R(3), 2) & 0x3Cu; R(3) = gm_u32(R(5) + R(3));
    R(3) = cntlzw(R(3) ^ type); R(3) = i2_rotl(R(3), 27) & 0x7FFFFFFu;
    return R(3);
}

static uint32_t wsp_isPlayerStar(GM_CTX, gptr self) {
    R(3) = gm_u32(self + 460); R(4) = WSP_STAR_TABLE0;
    R(3) = gm_u32(R(3) + 4); R(3) = gm_u8(R(3) + 336);
    R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(3) = gm_u32(R(4) + R(3));
    R(4) = WSP_STAR_TABLE1; R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu;
    R(3) = gm_u32(R(4) + R(3)) & 1; return R(3);
}

static uint32_t wsp_pushNext(GM_CTX, gptr self) {
    I2_FN(0x81828F90u);
    NV_R(30, self); R(4) = gm_u32(self + 12); R(3) = gm_u32(self + 4); CMPU(R(4), R(3));
    if (CR_BIT(ctx, 1)) { R(3) = 0; return R(3); }
    if (!CR_BIT(ctx, 0)) {
        R(3) = self; BL(0x81828FC4u, fn_2_181F30_808EF6E0);
        R(4) = gm_u32(self + 12); R(3) = gm_u32(self + 4);
    }
    R(5) = gm_u32(self + 16); R(7) = gm_u32(self + 8); R(5) += R(4);
    R(6) = divwu(R(5), R(3)); gm_set_u32(self + 12, R(4) + 1);
    R(3) = R(5) - R(6) * R(3); R(3) = R(7) + (i2_rotl(R(3), 3) & 0xFFFFFFF8u);
    return R(3);
}

GM_HLE_VERIFIED_(mod_fn_2_17DA80, GMV_IGNORE_POLLS, 0, 0) { R(3) = wsp_create(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_17E030, GMV_IGNORE_POLLS, 0, 0) { wsp_loadModel(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_180920, GMV_IGNORE_POLLS, 0, 0) { R(3) = wsp_order(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_180E80, GMV_IGNORE_POLLS, 0, 0) { wsp_calcWalkSpeed(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1811C0, GMV_IGNORE_POLLS, 0, 0) { wsp_getPlayerOrderDistance(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_181260, GMV_IGNORE_POLLS, 0, 0) { R(3) = wsp_getPlayerOrderTableIndex(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_2_181210, GMV_IGNORE_POLLS, 0, 0) { R(3) = wsp_getPlayerOrderAngle(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_181B10, 0, 0, 0) { R(3) = wsp_isPlayerType(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_2_181B30, 0, 0, 0) { R(3) = wsp_isPlayerStar(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_181EE0, GMV_IGNORE_POLLS, 0, 0) { R(3) = wsp_pushNext(GM_PASS, GM_ARG(0)); }
