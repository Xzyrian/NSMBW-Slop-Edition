/* gm_d_gamedisplay.c - dGameDisplay_c, the in-game HUD (the 8-player module's version).
 * Track B (gm_i2.h, docs/DECOMP.md), instance 2.
 *
 * Lifecycle, construction / layout, state, settlement, visibility, lives, time / score, rest-coin,
 * 1-up effects, grayscale colours and Star Coin display methods, checked against the recompiled
 * module code (0x818314E4-0x81832FAC). Framed functions replay their PowerPC frames and nested calls
 * with I2_FN / BL; simple state methods are leaves. The complete 2,192-byte object remains in
 * big-endian guest memory. Field names describe only behavior established from the PowerPC code. */
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
#define GD_SIZE               2192       /* dGameDisplay_c_classInit allocates the complete object */
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

/* Construct the embedded layouts, state machine and the eight player/effect display records. */
static void dGameDisplay_constructor(GM_CTX, gptr self) {
    I2_FN(0x8183151Cu);
    NV_R(30, self);
    BL(0x81831538u, mod___ct__7dBase_cFv_81808310);
    gm_set_u32(self + 96, 0x81850000u + 14460);
    R(3) = self + 112; BL(0x8183154Cu, hle___ct__Q23m2d13EmbedLayout_cFv);
    R(3) = self + 520; BL(0x81831554u, fn_800A8AB0);
    gm_set_u32(self + 912, 0x81850000u + 14772);
    gm_set_u32(self + 916, 0x81850000u + 8880);
    gm_set_u32(self + 920, 0x81850000u + 14820);
    gm_set_u32(self + 924, 0x81850000u + 14840);
    NV_R(29, 0); gm_set_u32(self + 928, self); gm_set_u32(self + 932, R(29));
    R(3) = self + 936; R(4) = self + 916; R(5) = self + 920; R(6) = 0x80370000u + 28792;
    BL(0x818315A8u, hle___ct__11dStateMgr_cFP17dStatePointless_cP20dStateExecutorBase_cP12dStateBase_c);
    gm_set_u8(self + 1099, R(29)); gm_set_u8(self + 1106, 1);
    R(3) = self + 1716; R(4) = 0x180000u; ctx->ctr = 8;
    do {
        uint32_t ea = R(3) + 28; gm_set_u32(ea, R(29)); R(3) = ea;
        R(5) = gm_u32(R(3) + 24);
        gm_set_u32(R(3) + 8, R(29));
        R(5) = (R(4) & 0x180000u) | (R(5) & ~0x180000u);
        gm_set_u32(R(3) + 12, R(29)); gm_set_u32(R(3) + 16, R(29));
        gm_set_u32(R(3) + 20, R(29)); gm_set_u32(R(3) + 4, R(29)); gm_set_u32(R(3) + 24, R(5));
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    } while (1);
    R(3) = self + 1960; ctx->ctr = 8;
    do {
        uint32_t ea = R(3) + 8; gm_set_u32(ea, 0); R(3) = ea; gm_set_u32(R(3) + 4, 0);
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    } while (1);
    R(3) = self + 2096; BL(0x81831614u, mfn_81830B1C);
    R(3) = self + 1632; ctx->ctr = 8;
    do {
        uint32_t ea = R(3) + 4; gm_set_u32(ea, (uint32_t)-1); R(3) = ea;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    } while (1);
    gm_set_u32(0x80430000u - 23768, self); R(3) = self;
}

static void dGameDisplay_destructor(GM_CTX, gptr self, uint32_t flags) {
    I2_FN(0x81831650u);
    NV_R(29, flags); NV_R(28, 0); NV_R(30, self);
    R(4) = 0; BL(0x8183167Cu, mod___dt__7dBase_cFv_818083A4);
    R(3) = 0x80430000u; gm_set_u32(R(3) - 23768, R(28));
    R(3) = self + 520; R(4) = (uint32_t)-1; BL(0x81831690u, __dt__Q23mEf3es2Fv_80025F60);
    R(3) = self + 2096; R(4) = (uint32_t)-1; BL(0x8183169Cu, mfn_81830BC4);
    R(3) = self + 112; R(4) = (uint32_t)-1; BL(0x818316A8u, hle___dt__Q23m2d13EmbedLayout_cFv);
    if (CMPS(R(29), 0) > 0) { R(3) = self; BL(0x818316B8u, hle__Z17FreeFromGameHeap1Pv); }
    R(3) = self;
}

static void dGameDisplay_draw(GM_CTX, gptr self) {
    I2_FN(0x81831784u);
    NV_R(30, self);
    R(3) = gm_u8(self + 1106);
    if (CMPU(R(3), 1) == 0) {
        R(3) = gm_u8(self + 1099);
        if (CMPU(R(3), 1) == 0) {
            R(3) = 0x81860000u - 508; R(3) = gm_u8(R(3) + 8);
            if (CMPU(R(3), 0) != 0) { R(3) = self + 2096; BL(0x818317CCu, hle_scheduleForDrawing__Q23m2d6Base_cFv); }
            R(3) = self + 112; BL(0x818317D4u, hle_fn_80006EA0);
        }
    }
    R(3) = 1;
}

/* execute: run the HUD state, animations and per-player visibility while the layout is active. */
static void dGameDisplay_execute(GM_CTX, gptr self) {
    I2_FN(0x818316D8u);
    NV_R(31, self);
    R(0) = gm_u8(self + 1099);
    if (CMPS(R(0), 0) == 0) { R(3) = 1; return; }
    R(3) = self; BL(0x818316FCu, hle_mod_fn_80158890);
    R(12) = gm_u32(self + 912); R(3) = self + 912;
    R(12) = gm_u32(R(12) + 16); ctx->ctr = R(12);
    ctx->lr = 0x81831710u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = self + 112; BL(0x81831718u, hle_isAnyAnimOn__Q23m2d13EmbedLayout_cFv);
    if (CMPS(R(3), 0) == 0 && CMPU(gm_u8(self + 1104), 0) == 0 && CMPU(gm_u8(self + 1105), 0) != 0)
        goto visibility;
    R(3) = self + 112; BL(0x81831740u, hle_execAnimations__Q23m2d13EmbedLayout_cFv);
    R(12) = gm_u32(self + 120); R(3) = self + 112;
    R(12) = gm_u32(R(12) + 16); ctx->ctr = R(12);
    ctx->lr = 0x81831754u; ppc_call_indirect(ctx, base, ctx->ctr);
visibility:
    R(3) = self; BL(0x8183175Cu, hle_mod_fn_80158910);
    R(3) = self; BL(0x81831764u, hle_mod_fn_80158A90);
    R(3) = self; BL(0x8183176Cu, mfn_81831BA0);
    R(3) = 1;
}

/* AreaCheck: map each active player into layout space and fade the areas that obscure them. */
static void dGameDisplay_AreaCheck(GM_CTX, gptr self) {
    I2_FN(0x81831E84u);
    gptr sp = gm_frame_sp;
    NV_R(27, 0x81860000u); NV_R(30, self);
    R(4) = gm_u32(R(27) - 300); gm_set_u32(sp + 24, R(4));
    R(3) = gm_u32(self + 1168); R(3) = gm_u8(R(3) + 187) & 1; CR0(ctx, R(3));
    if (CR_BIT(ctx, 2)) goto guard;
    NV_R(26, self + 1100); NV_R(25, self + 1104);
    NV_R(29, 0); NV_R(28, sp + 12); NV_R(24, 3); NV_R(23, 1);
    for (;;) {
        uint32_t hi = gm_u32(0x81860000u - 6008);
        uint32_t lo = gm_u32(0x81860000u - 6004);
        ctx->xer_ca = R(29) <= 32;
        R(5) = (32 - R(29)) & 63; R(5) = R(5) > 31 ? 0 : hi << R(5);
        R(3) = R(29) & 63; R(3) = R(3) > 31 ? 0 : lo >> R(3);
        R(3) |= R(5);
        R(5) = (R(29) - 32) & 63; R(4) = R(5) > 31 ? 0 : hi >> R(5);
        R(3) = (R(3) | R(4)) & 1; CR0(ctx, R(3));
        if (!CR_BIT(ctx, 2)) {
            R(3) = R(29); BL(0x81831F20u, hle_getPlayer__9daPyMng_cFi);
            if (CMPU(R(3), 0) != 0) {
                R(4) = R(3); R(3) = R(28); BL(0x81831F34u, hle_Actor_GetVec3WithValuesAdded);
                R(3) = R(28); BL(0x81831F3Cu, getGlbPosToLyt__8dGameComFR7mVec3_c_800B33D0);
                ctx->f[0].d = ctx->ps1[0] = ldfs(base, sp + 12);
                ctx->f[1].d = ctx->ps1[1] = ldfs(base, sp + 16);
                R(3) = R(26); R(4) = R(25); ctx->ctr = R(24);
                do {
                    uint32_t ea = R(3) + 1; R(6) = gm_u8(ea); R(3) = ea;
                    R(5) = R(4); R(4) += 16;
                    if (CMPU(R(6), 0) == 0) {
                        ctx->f[2].d = ctx->ps1[2] = ldfs(base, R(5) + 16);
                        cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
                        if (!CR_BIT(ctx, 1)) {
                            ctx->f[2].d = ctx->ps1[2] = ldfs(base, R(5) + 8);
                            cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
                            if (!CR_BIT(ctx, 0)) {
                                ctx->f[2].d = ctx->ps1[2] = ldfs(base, R(5) + 8);
                                cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[2].d);
                                if (!CR_BIT(ctx, 0)) {
                                    ctx->f[2].d = ctx->ps1[2] = ldfs(base, R(5) + 12);
                                    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[2].d);
                                    if (!CR_BIT(ctx, 1)) {
                                        gm_set_u8(self + 1104, R(23)); gm_set_u8(R(3), R(23));
                                    }
                                }
                            }
                        }
                    }
                    if (--ctx->ctr == 0) break;
                    GM_LOOP();
                } while (1);
            }
        }
        NV_R(29, R(29) + 1);
        if (CMPU(R(29), 8) == 0) break;
        GM_LOOP();
    }
guard:
    R(3) = gm_u32(R(27) - 300); R(4) = gm_u32(sp + 24);
    if (CMPU(R(3), R(4)) != 0) BL(0x81831FF0u, mfn_81844FCC);
}

/* AlphaEnterAndExit: move the three player-area panes between alpha 71 and 255. */
static void dGameDisplay_AlphaEnterAndExit(GM_CTX, gptr self) {
    R(4) = gm_u32(self + 1168); R(4) = gm_u8(R(4) + 187) & 1; CR0(ctx, R(4));
    if (CR_BIT(ctx, 2)) return;
    R(4) = self + 1256; R(5) = self + 1100; R(6) = self + 1044;
    R(9) = 0x81850000u - 3848 - 4; R(8) = 0; ctx->ctr = 3;
    do {
        uint32_t ea = R(9) + 4; R(10) = gm_u32(ea); R(9) = ea;
        R(10) = gm_u32(R(4) + (i2_rotl(R(10), 2) & 0xFFFFFFFCu));
        R(12) = gm_u8(R(10) + 184); R(11) = CMPU(R(12), 71) >= 0;
        ea = R(5) + 1; R(0) = gm_u8(ea); R(5) = ea;
        int entering = CMPU(R(0), 0) == 0;
        if (!entering) R(11) = i2_rotl(cntlzw(R(12) ^ 0xFFu), 27) & 0x7FFFFFFu;
        R(12) = entering ? 12 : (uint32_t)-12;
        ea = R(6) + 4; R(0) = gm_u32(ea); R(6) = ea;
        R(12) += R(0);
        if (CMPS(R(12), 255) > 0) R(12) = 255;
        if (CMPS(R(12), 71) <= 0) R(12) = 71;
        R(8) += R(11); gm_set_u32(R(6), R(12)); gm_set_u8(R(10) + 184, R(12)); gm_set_u8(R(5), 0);
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    } while (1);
    gm_set_u8(self + 1104, CMPU(R(8), 3) < 0);
}

/* AreaSetupAll: update the first three player areas, then derive the shared camera height
   from the selected player when the display mode is not six. */
static void dGameDisplay_AreaSetupAll(GM_CTX, gptr self) {
    I2_FN(0x818317ECu);
    NV_R(30, self);
    R(3) = 0x81850000u - 3848;
    NV_R(27, R(3) - 4); NV_R(28, 3); NV_R(29, 0);
    for (;;) {
        uint32_t ea = R(27) + 4; R(5) = gm_u32(ea); NV_R(27, ea);
        R(3) = R(30); R(4) = R(29); BL(0x81831830u, fn_801582B0);
        NV_R(28, R(28) - 1);
        int more = CMPU(R(28), 0) > 0;
        NV_R(29, R(29) + 1);
        if (!more) break;
        GM_LOOP();
    }
    R(3) = gm_u32(self + 1044);
    if (CMPU(R(3), 6) == 0) return;
    R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu;
    R(3) = gm_u32(self + R(3) + 1172);
    ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(3) + 144);
    ctx->f[1].d = ctx->ps1[1] = ldfs(base, R(3) + 76);
    R(3) = 0x81850000u;
    ctx->f[2].d = ctx->ps1[2] = ldfs(base, R(3) - 31028);
    R(3) = 0x81850000u;
    ctx->f[3].d = ctx->ps1[3] = ldfs(base, R(3) - 30824);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[3].d);
    stfs(base, self + 1124, ctx->f[0].d);
}

/* RestDispSetup: place the active players' life icons and restore their character materials. */
static void dGameDisplay_RestDispSetup(GM_CTX, gptr self) {
    I2_FN(0x81831BC8u);
    gptr sp = gm_frame_sp;
    NV_R(30, self); NV_R(26, self + 1172);
    gm_set_u32(sp + 108, gm_u32(0x81860000u - 300));
    R(3) = 0x81850000u - 4000 - 4; R(4) = sp + 12; ctx->ctr = 8;
    do {
        uint32_t ea = R(3) + 4; R(5) = gm_u32(ea); R(3) = ea;
        R(5) = gm_u32(R(26) + (i2_rotl(R(5), 2) & 0xFFFFFFFCu));
        R(6) = gm_u32(R(5) + 44); R(7) = gm_u32(R(5) + 48); R(8) = gm_u32(R(5) + 52);
        gm_set_u32(R(4), R(6)); gm_set_u32(R(4) + 4, R(7)); gm_set_u32(R(4) + 8, R(8));
        gm_set_u8(R(5) + 187, gm_u8(R(5) + 187) & 0xFEu); R(4) += 12;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    } while (1);
    NV_R(25, self + 1744); NV_R(24, self + 1968); NV_R(23, self + 2032); NV_R(22, 8);
    R(3) = 0; NV_R(21, 0x81850000u - 4000);
    NV_R(18, 0x81860000u - 5828 - 4); NV_R(20, 0x81860000u - 6000 - 4); NV_R(19, sp + 12);
    for (;;) {
        uint32_t ea = R(20) + 4; R(5) = gm_u32(ea); NV_R(20, ea);
        R(4) = R(18); NV_R(18, R(18) + 4);
        if (CMPU(R(5), 0) != 0) {
            NV_R(29, gm_u32(R(4) + 4));
            if (CMPU(R(29), 7) <= 0) {
                R(4) = gm_u32(R(21) + (i2_rotl(R(29), 2) & 0xFFFFFFFCu));
                R(7) = (uint32_t)((int32_t)R(3) * 12);
                ea = R(7) + R(19); R(8) = gm_u32(ea); R(7) = ea;
                NV_R(16, R(3) + 1); NV_R(17, i2_rotl(R(4), 2) & 0xFFFFFFFCu);
                R(5) = gm_u32(R(26) + R(17)); R(3) = R(29);
                gm_set_u8(R(5) + 187, gm_u8(R(5) + 187) | 1);
                R(5) = gm_u32(R(7) + 8); R(6) = gm_u32(R(26) + R(17)); R(7) = gm_u32(R(7) + 4);
                gm_set_u32(R(6) + 52, R(5)); gm_set_u32(R(6) + 48, R(7)); gm_set_u32(R(6) + 44, R(8));
                gm_set_u32(self + 1044, R(4)); BL(0x81831D18u, mfn_81806AB8); NV_R(28, R(3));
                R(3) = gm_u32(R(26) + R(17)); R(4) = gm_u32(R(3)); R(4) = gm_u32(R(4) + 104); ctx->ctr = R(4);
                ctx->lr = 0x81831D30u; ppc_call_indirect(ctx, base, ctx->ctr);
                NV_R(27, R(25) + (uint32_t)((int32_t)R(28) * 28));
                BL(0x81831D3Cu, fn_802B3300);
                R(4) = R(27); R(5) = 28; BL(0x81831D48u, mod_memcpy_81844C38);
                R(3) = i2_rotl(R(29), 3) & 0xFFFFFFF8u; R(4) = R(23);
                ea = R(4) + R(3); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea); R(4) = ea;
                R(3) = i2_rotl(R(28), 3) & 0xFFFFFFF8u; R(5) = R(23);
                ea = R(5) + R(3); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea); R(5) = ea;
                ctx->f[2].d = ctx->ps1[2] = ldfs(base, R(4) + 4); R(4) = R(24);
                ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d / ctx->f[0].d);
                ctx->f[1].d = ctx->ps1[1] = frsp(ldfs(base, R(5) + 4) / ctx->f[2].d);
                ea = R(4) + R(3); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea); R(4) = ea;
                R(3) = gm_u32(R(26) + R(17)); ctx->f[3].d = ctx->ps1[3] = ldfs(base, R(4) + 4);
                ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d); stfs(base, R(3) + 76, ctx->f[0].d);
                ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d * ctx->f[1].d); stfs(base, R(3) + 80, ctx->f[0].d);
                R(3) = R(16);
            }
        }
        NV_R(22, R(22) - 1);
        if (CMPU(R(22), 0) <= 0) break;
        GM_LOOP();
    }
    R(3) = gm_u32(0x81860000u - 300); R(4) = gm_u32(sp + 108);
    if (CMPU(R(3), R(4)) != 0) BL(0x81831E04u, mfn_81844FCC);
}

/* createLayout: load the HUD archive, bind its panes and cache player materials and positions. */
static void dGameDisplay_createLayout(GM_CTX, gptr self) {
    I2_FN(0x818318A0u);
    gptr sp = gm_frame_sp;
    NV_R(26, 0x81860000u); NV_R(27, 0); NV_R(29, self); NV_R(28, self + 112);
    gm_set_u32(sp + 40, gm_u32(R(26) - 300));
    NV_R(25, 0x81850000u - 3836);
    R(3) = R(28); R(4) = R(25) + 765; R(5) = 0; BL(0x818318FCu, hle_loadArc__Q23m2d13EmbedLayout_cFPCcb);
    NV_R(30, R(3));
    if (CMPU(R(3), 0) == 0) goto guard;
    R(3) = R(28); R(4) = R(25) + 746; R(5) = 0; BL(0x81831918u, hle_fn_800C8A10);
    R(4) = gm_u32(self + 244);
    if (CMPU(R(4), 0) != 0) NV_R(27, gm_u32(R(4) + 4));
    R(3) = self + 2096; R(4) = R(27); R(5) = R(28) + 48; BL(0x81831938u, mfn_81830C64);
    R(3) = R(28); R(4) = 0x81850000u + 14540; R(5) = 1; BL(0x8183194Cu, hle_loadAnimations__Q23m2d13EmbedLayout_cFPPCci);
    NV_R(25, 0x81850000u - 3836);
    gm_set_u32(sp + 24, R(25) + 679); gm_set_u32(sp + 8, 0);
    R(3) = R(28); R(4) = sp + 24; R(5) = sp + 8; R(6) = 1; BL(0x81831978u, hle_loadGroups__Q23m2d13EmbedLayout_cFPPCcPCii);
    R(3) = R(28); BL(0x81831980u, CBGetBytesAvailableForRead_80007220); gm_set_u32(self + 1168, R(3));
    R(3) = R(28); R(4) = 0x81850000u + 14544; R(5) = self + 1256; R(6) = 20;
    BL(0x818319A0u, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
    R(3) = R(28); R(4) = 0x81850000u + 14624; R(5) = self + 1728; R(6) = 4;
    BL(0x818319B8u, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
    NV_R(27, self + 1172);
    R(3) = R(28); R(4) = 0x81850000u + 14640; R(5) = R(27); R(6) = 10;
    BL(0x818319D4u, hle_getPictures__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7Picturei);
    R(3) = R(28); R(4) = 0x81850000u + 14680; R(5) = self + 1680; R(6) = 4;
    BL(0x818319ECu, hle_getPictures__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7Picturei);
    R(5) = self + 1212; R(6) = 11;
    R(3) = gm_u32(self + 1176); gm_set_u8(R(3) + 187, gm_u8(R(3) + 187) & 0xFEu);
    R(3) = gm_u32(self + 1184); gm_set_u8(R(3) + 187, gm_u8(R(3) + 187) & 0xFEu);
    R(3) = gm_u32(self + 1192); gm_set_u8(R(3) + 187, gm_u8(R(3) + 187) & 0xFEu);
    R(3) = gm_u32(self + 1172); gm_set_u8(R(3) + 187, gm_u8(R(3) + 187) | 1);
    R(3) = gm_u32(self + 1180); gm_set_u8(R(3) + 187, gm_u8(R(3) + 187) | 1);
    R(3) = gm_u32(self + 1188); gm_set_u8(R(3) + 187, gm_u8(R(3) + 187) | 1);
    R(3) = gm_u32(self + 1196); gm_set_u8(R(3) + 187, gm_u8(R(3) + 187) & 0xFEu);
    R(3) = R(28); R(4) = 0x81850000u + 14696;
    BL(0x81831A74u, hle_getTextBoxes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7TextBoxi);
    R(3) = R(28); R(4) = 0x81850000u + 14740; R(5) = self + 1696; R(6) = 8; NV_R(24, 8);
    BL(0x81831A90u, hle_getTextBoxes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7TextBoxi);
    gm_set_u32(sp + 24, R(25) + 393); gm_set_u32(sp + 28, R(25) + 355);
    gm_set_u32(sp + 32, R(25) + 228); gm_set_u32(sp + 36, R(25) + 126);
    gm_set_u32(sp + 16, 19); gm_set_u32(sp + 20, 19); gm_set_u32(sp + 8, 20); gm_set_u32(sp + 12, 20);
    R(3) = R(28); R(4) = sp + 24; R(5) = sp + 8; R(6) = 1; R(7) = 4;
    BL(0x81831ADCu, hle_setLangStrings__Q23m2d13EmbedLayout_cFPPCcPCiii);
    NV_R(28, self + 1744); NV_R(29, self + 1960); NV_R(25, 0x81850000u - 4000 - 4);
    do {
        uint32_t ea = R(25) + 4; R(3) = gm_u32(ea); NV_R(25, ea);
        NV_R(23, i2_rotl(R(3), 2) & 0xFFFFFFFCu);
        R(3) = gm_u32(R(27) + R(23)); R(4) = gm_u32(R(3)); R(4) = gm_u32(R(4) + 104); ctx->ctr = R(4);
        ctx->lr = 0x81831B0Cu; ppc_call_indirect(ctx, base, ctx->ctr);
        BL(0x81831B10u, fn_802B3300);
        R(4) = R(3); R(3) = R(28); R(5) = 28; BL(0x81831B20u, mod_memcpy_81844C38);
        R(3) = gm_u32(R(27) + R(23)); NV_R(24, R(24) - 1); NV_R(28, R(28) + 28);
        R(4) = gm_u32(R(3) + 76); R(3) = gm_u32(R(3) + 80);
        ea = R(29) + 8; gm_set_u32(ea, R(4)); NV_R(29, ea); gm_set_u32(R(29) + 4, R(3));
        R(3) = gm_u32(R(27) + R(23)); R(4) = gm_u32(R(3) + 72); R(3) = gm_u32(R(3) + 68);
        gm_set_u32(R(29) + 68, R(4)); gm_set_u32(R(29) + 64, R(3));
        if (CMPU(R(24), 0) <= 0) break;
        GM_LOOP();
    } while (1);
guard:
    R(3) = gm_u32(R(26) - 300); R(4) = gm_u32(sp + 40);
    if (CMPU(R(3), R(4)) != 0) { BL(0x81831BA0u, mfn_81844FCC); return; }
    R(3) = R(30);
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

/* NormalSettle: take one score unit from the rounded time bonus and award the corresponding
   score. Returns one once no more than one unit remains. */
static void dGameDisplay_NormalSettle(GM_CTX, gptr self) {
    uint32_t cr_in = ctx->cr;
    I2_FN(0x818320B8u);
    gptr sp = gm_frame_sp;
    R(12) = cr_in; gm_set_u32(sp + 20, cr_in);
    R(4) = 0x80430000u;
    R(5) = gm_u32(R(4) - 24464);
    R(4) = gm_u32(R(5) + 4) + 4095;
    int32_t rounded = (int32_t)R(4);
    ctx->xer_ca = rounded < 0 && ((uint32_t)rounded & 0xFFFu) != 0;
    R(4) = (uint32_t)(rounded >> 12);
    uint64_t sum = (uint64_t)R(4) + ctx->xer_ca;
    R(4) = (uint32_t)sum; ctx->xer_ca = (uint32_t)(sum >> 32);
    R(6) = (uint32_t)(int16_t)R(4);
    cr_cmp_s(ctx, 2, (int32_t)R(6), 1);
    int done = CR_BIT(ctx, 8);                  /* save the result before native callees can clobber CR2 */
    if (!done) {
        R(6) = gm_u32(self + 1036);
        R(7) = R(4) & 0x7FFFu;
        cr_cmp_s(ctx, 0, (int32_t)R(6), (int32_t)R(7));
        if (!CR_BIT(ctx, 0)) R(6) = R(7);
        R(3) = gm_u32(self + 1040);
        R(4) = (uint32_t)(int16_t)(R(4) - R(6));
        NV_R(30, R(3) * R(6));
        R(3) = R(5); BL(0x81832120u, fn_800E3910);
        R(3) = gm_u8(0x80430000u - 24704 + 3) & 0x40u; CR0(ctx, R(3));
        if (CR_BIT(ctx, 2)) {
            R(3) = gm_u32(0x80430000u - 23416); R(4) = 145; R(5) = 1;
            BL(0x81832148u, hle_startSystemSe__11SndAudioMgrFUiUl);
        }
        R(3) = R(30); R(4) = (uint32_t)-1; BL(0x81832154u, addScore__9daPyMng_cFii_80060690);
    }
    R(3) = done;
    R(12) = gm_u32(sp + 20);
    ctx->cr = (ctx->cr & ~0xF00000u) | (R(12) & 0xF00000u);
}

/* OtasukeSettle: the assist-mode three-count display, followed by time / score decrements.
   Returns one when both the displayed count and the remaining score have reached zero. */
static void dGameDisplay_OtasukeSettle(GM_CTX, gptr self) {
    I2_FN(0x8183217Cu);
    gptr sp = gm_frame_sp;
    NV_R(30, self); NV_R(29, 0x81860000u);
    R(3) = gm_u32(R(29) - 300); gm_set_u32(sp + 20, R(3));
    R(5) = 0x80430000u;
    R(3) = gm_u32(R(5) - 24464);
    NV_R(27, gm_u32(R(5) - 25408));
    R(4) = gm_u32(R(3) + 4);
    R(3) = R(30); R(4) += 4095;
    int32_t rounded = (int32_t)R(4);
    ctx->xer_ca = rounded < 0 && ((uint32_t)rounded & 0xFFFu) != 0;
    R(5) = (uint32_t)(rounded >> 12);
    { uint32_t ea = R(3) + 988; R(4) = gm_u32(ea); R(3) = ea; }
    uint64_t sum = (uint64_t)R(5) + ctx->xer_ca;
    R(5) = (uint32_t)sum; ctx->xer_ca = (uint32_t)(sum >> 32);
    R(6) = (R(5) & 0xFFFFu) | R(27); NV_R(28, R(6) | R(4)); CR0(ctx, R(28));
    if (!CR_BIT(ctx, 2)) {
        cr_cmp_s(ctx, 0, (int32_t)R(4), 3);
        NV_R(26, (uint32_t)(int16_t)R(5));
        if (!CR_BIT(ctx, 1)) R(4) = 3;
        R(5) = gm_u32(self + 1244);
        R(4) -= 3; gm_set_u32(self + 988, R(4));
        R(4) = 2; gm_set_u32(sp + 16, R(4));
        R(4) = sp + 16; R(6) = 0;
        BL(0x81832214u, LayoutDispNumber__8dGameComFRCiRCiP12LytTextBox_cb_800B3B60);
        R(3) = gm_u32(self + 1036); R(3) = R(26) - R(3);
        int32_t left = (int32_t)R(3);
        ctx->xer_ca = left < 0 && ((uint32_t)left & 0x7FFFFFFFu) != 0;
        R(4) = (uint32_t)(left >> 31); R(4) = R(3) & ~R(4);
        R(3) = gm_u32(0x80430000u - 24464); R(4) = (uint32_t)(int16_t)R(4);
        BL(0x81832234u, fn_800E3910);
        R(3) = gm_u32(self + 1040); R(4) = gm_u32(self + 1036); R(3) = R(4) * R(3);
        R(3) = R(27) - R(3);
        left = (int32_t)R(3);
        ctx->xer_ca = left < 0 && ((uint32_t)left & 0x7FFFFFFFu) != 0;
        R(5) = (uint32_t)(left >> 31); R(4) = 0x80430000u; R(3) &= ~R(5);
        gm_set_u32(R(4) - 25408, R(3));
        R(3) = gm_u32(0x80430000u - 23416); R(4) = 145; R(5) = 1;
        BL(0x81832268u, hle_startSystemSe__11SndAudioMgrFUiUl);
    }
    R(3) = gm_u32(R(29) - 300); R(4) = gm_u32(sp + 20);
    if (CMPU(R(3), R(4)) != 0) { BL(0x818322A8u, mfn_81844FCC); return; }
    R(3) = i2_rotl(cntlzw(R(28)), 27) & 0x7FFFFFFu;
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
        BL(0x8183245Cu, hle_mod_fn_80158D00);
        if (CMPU(R(3), 0) == 0) return;
        R(3) = 0;
        gm_set_u32(R(30) + GD_GOAL_ELAPSED, R(3));
    } else {
        R(3) = R(30);
        BL(0x81832478u, hle_mod_fn_80158C50);
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

/* Spawn the two 1-up effects at a player's position when the game state permits them. */
static void dGameDisplay_Effect1Up(GM_CTX, gptr self, uint32_t player) {
    I2_FN(0x818324FCu);
    NV_R(31, self); NV_R(30, player);
    R(3) = gm_u32(ctx->r[13] - 21056); R(12) = gm_u32(gm_u32(R(3)) + 16); ctx->ctr = R(12);
    ctx->lr = 0x8183252Cu; ppc_call_indirect(ctx, base, ctx->ctr);
    R(0) = cntlzw(R(3) - 1); R(0) = i2_rotl(R(0), 27) & 0x7FFFFFFu; CR0(ctx, R(0)); R(3) = 0;
    if (CR_BIT(ctx, 2)) return;
    R(0) = gm_u8(ctx->r[13] - 22174); if (CMPS(R(0), 0) != 0) return;
    R(0) = gm_u32(ctx->r[13] - 21600); if (CMPS(R(0), 0) != 0) return;
    R(4) = 0x80310000u; R(0) = gm_u32(R(4) + 23448); if (CMPS(R(0), 3) == 0) return;
    R(0) = i2_rotl(R(30), 2) & 0xFFFFFFFCu; R(3) = R(31) + R(0);
    ctx->f[0].d = ctx->ps1[0] = ldfs(base, ctx->r[13] - 6848);
    NV_R(30, gm_u32(R(3) + 1256)); R(3) = gm_frame_sp + 8; R(4) = 0;
    R(5) = gm_u32(R(30) + 144); gm_set_u32(gm_frame_sp + 36, R(5));
    R(0) = gm_u32(R(30) + 160); gm_set_u32(gm_frame_sp + 52, R(0));
    NV_R(31, gm_u32(R(30) + 132)); R(12) = gm_u32(R(30) + 136); R(11) = gm_u32(R(30) + 140);
    R(10) = gm_u32(R(30) + 148); R(9) = gm_u32(R(30) + 152); R(8) = gm_u32(R(30) + 156);
    R(7) = gm_u32(R(30) + 164); R(6) = gm_u32(R(30) + 168); R(5) = gm_u32(R(30) + 172);
    R(0) = gm_u32(R(30) + 176);
    ctx->f[2].d = ctx->ps1[2] = ldfs(base, gm_frame_sp + 36);
    ctx->f[1].d = ctx->ps1[1] = ldfs(base, gm_frame_sp + 52);
    gm_set_u32(gm_frame_sp + 24, R(31)); gm_set_u32(gm_frame_sp + 28, R(12));
    gm_set_u32(gm_frame_sp + 32, R(11)); gm_set_u32(gm_frame_sp + 40, R(10));
    gm_set_u32(gm_frame_sp + 44, R(9)); gm_set_u32(gm_frame_sp + 48, R(8));
    gm_set_u32(gm_frame_sp + 56, R(7)); gm_set_u32(gm_frame_sp + 60, R(6));
    gm_set_u32(gm_frame_sp + 64, R(5)); gm_set_u32(gm_frame_sp + 68, R(0));
    stfs(base, gm_frame_sp + 8, ctx->f[2].d); stfs(base, gm_frame_sp + 12, ctx->f[1].d);
    stfs(base, gm_frame_sp + 16, ctx->f[0].d);
    BL(0x818325FCu, GetPosForLayoutEffect__FP7Point3db_800B37E0);
    R(3) = 0x80320000u + 30364; R(5) = gm_frame_sp + 8; R(4) = 0; R(6) = 0; R(7) = 0;
    BL(0x81832618u, hle_createEffect__3mEfFPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
    ctx->f[2].d = ctx->ps1[2] = ldfs(base, gm_frame_sp + 36); R(3) = gm_frame_sp + 8;
    ctx->f[1].d = ctx->ps1[1] = ldfs(base, gm_frame_sp + 52); R(4) = 1;
    ctx->f[0].d = ctx->ps1[0] = ldfs(base, ctx->r[13] - 6848);
    stfs(base, gm_frame_sp + 8, ctx->f[2].d); stfs(base, gm_frame_sp + 12, ctx->f[1].d);
    stfs(base, gm_frame_sp + 16, ctx->f[0].d);
    BL(0x8183263Cu, GetPosForLayoutEffect__FP7Point3db_800B37E0);
    R(3) = 0x80320000u + 30376; R(5) = gm_frame_sp + 8; R(4) = 0; R(6) = 0; R(7) = 0;
    BL(0x81832658u, hle_createEffect__3mEfFPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
    R(3) = 1;
}

/* Save the three current text colours, then apply the shared grayscale tint. */
static void dGameDisplay_GrayColorSet(GM_CTX, gptr self, uint32_t index) {
    I2_FN(0x81832674u);
    NV_R(27, self); NV_R(28, index);
    R(0) = (uint32_t)(int8_t)gm_u8(ctx->r[13] - 21332); CR0(ctx, R(0));
    if (CR_BIT(ctx, 2)) {
        R(6) = ctx->r[13] - 21328; R(7) = 160; R(5) = 255; R(0) = 1;
        gm_set_u8(ctx->r[13] - 21328, R(7)); gm_set_u8(R(6) + 1, R(7));
        gm_set_u8(R(6) + 2, R(7)); gm_set_u8(R(6) + 3, R(5)); gm_set_u8(ctx->r[13] - 21332, R(0));
    }
    R(5) = 0x81850000u - 4000; R(0) = i2_rotl(R(4), 2) & 0xFFFFFFFCu;
    R(0) = gm_u32(R(5) + R(0)); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
    R(3) = gm_u32(R(3) + R(0) + 1172); R(12) = gm_u32(gm_u32(R(3)) + 104); ctx->ctr = R(12);
    ctx->lr = 0x818326ECu; ppc_call_indirect(ctx, base, ctx->ctr);
    R(0) = gm_u32(R(3) + 24); NV_R(29, i2_rotl(R(28), 3) & 0xFFFFFFF8u);
    gm_set_u32(gm_frame_sp + 72, R(0)); NV_R(30, ctx->r[13] - 21328); R(4) = gm_u32(R(3) + 28);
    NV_R(31, 0x81850000u); R(9) = R(27) + R(29); R(0) = (uint32_t)gm_s16(gm_frame_sp + 72);
    gm_set_u32(gm_frame_sp + 76, R(4)); NV_R(31, R(31) - 3936); R(4) = gm_u8(ctx->r[13] - 21328);
    NV_R(28, i2_rotl(R(28), 1) & 0xFFFFFFFEu); gm_set_u16(R(9) + 1444, R(0));
    R(0) = gm_u8(R(30) + 1); R(5) = (uint32_t)gm_s16(gm_frame_sp + 74); gm_set_u16(gm_frame_sp + 26, R(0));
    R(7) = gm_u8(R(30) + 2); gm_set_u16(gm_frame_sp + 24, R(4)); R(6) = gm_u8(R(30) + 3);
    gm_set_u16(R(9) + 1446, R(5)); R(8) = (uint32_t)gm_s16(gm_frame_sp + 76); R(4) = gm_u32(gm_frame_sp + 24);
    R(0) = gm_u32(R(31) + R(29)); gm_set_u16(R(9) + 1448, R(8)); R(5) = (uint32_t)gm_s16(gm_frame_sp + 78);
    R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; gm_set_u32(gm_frame_sp + 64, R(4)); R(4) = R(27) + R(0);
    gm_set_u16(R(9) + 1450, R(5)); R(5) = (uint32_t)gm_s16(gm_frame_sp + 64); gm_set_u16(gm_frame_sp + 28, R(7));
    R(0) = (uint32_t)gm_s16(gm_frame_sp + 66); gm_set_u16(R(3) + 24, R(5)); gm_set_u16(gm_frame_sp + 30, R(6));
    R(5) = gm_u32(gm_frame_sp + 28); gm_set_u32(gm_frame_sp + 68, R(5)); gm_set_u16(R(3) + 26, R(0));
    R(0) = (uint32_t)gm_s16(gm_frame_sp + 68); gm_set_u16(R(3) + 28, R(0));
    R(0) = (uint32_t)gm_s16(gm_frame_sp + 70); gm_set_u16(R(3) + 30, R(0));
    R(3) = gm_u32(R(4) + 1212); R(12) = gm_u32(gm_u32(R(3)) + 104); ctx->ctr = R(12);
    ctx->lr = 0x818327A4u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(4) = gm_u32(R(3) + 24); R(0) = R(28) + 1; gm_set_u32(gm_frame_sp + 56, R(4));
    R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; R(5) = gm_u32(R(3) + 28); R(9) = R(27) + R(29);
    R(4) = (uint32_t)gm_s16(gm_frame_sp + 56); gm_set_u16(R(9) + 1508, R(4)); R(4) = gm_u8(R(30) + 1);
    gm_set_u32(gm_frame_sp + 60, R(5)); R(5) = gm_u8(ctx->r[13] - 21328); gm_set_u16(gm_frame_sp + 16, R(5));
    R(8) = (uint32_t)gm_s16(gm_frame_sp + 58); gm_set_u16(gm_frame_sp + 18, R(4)); R(7) = gm_u8(R(30) + 2);
    gm_set_u16(R(9) + 1510, R(8)); R(8) = (uint32_t)gm_s16(gm_frame_sp + 60); R(4) = gm_u32(gm_frame_sp + 16);
    R(6) = gm_u8(R(30) + 3); R(0) = gm_u32(R(31) + R(0)); gm_set_u16(R(9) + 1512, R(8));
    R(5) = (uint32_t)gm_s16(gm_frame_sp + 62); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
    gm_set_u32(gm_frame_sp + 48, R(4)); R(4) = R(27) + R(0); gm_set_u16(R(9) + 1514, R(5));
    R(5) = (uint32_t)gm_s16(gm_frame_sp + 48); gm_set_u16(gm_frame_sp + 20, R(7));
    R(0) = (uint32_t)gm_s16(gm_frame_sp + 50); gm_set_u16(R(3) + 24, R(5)); gm_set_u16(gm_frame_sp + 22, R(6));
    R(5) = gm_u32(gm_frame_sp + 20); gm_set_u32(gm_frame_sp + 52, R(5)); gm_set_u16(R(3) + 26, R(0));
    R(0) = (uint32_t)gm_s16(gm_frame_sp + 52); gm_set_u16(R(3) + 28, R(0));
    R(0) = (uint32_t)gm_s16(gm_frame_sp + 54); gm_set_u16(R(3) + 30, R(0));
    R(3) = gm_u32(R(4) + 1212); R(12) = gm_u32(gm_u32(R(3)) + 104); ctx->ctr = R(12);
    ctx->lr = 0x81832850u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(0) = gm_u32(R(3) + 24); R(8) = R(27) + R(29); gm_set_u32(gm_frame_sp + 40, R(0));
    R(4) = gm_u32(R(3) + 28); R(0) = (uint32_t)gm_s16(gm_frame_sp + 40); gm_set_u16(R(8) + 1572, R(0));
    R(0) = gm_u8(R(30) + 1); gm_set_u32(gm_frame_sp + 44, R(4)); R(4) = gm_u8(ctx->r[13] - 21328);
    gm_set_u16(gm_frame_sp + 8, R(4)); R(7) = (uint32_t)gm_s16(gm_frame_sp + 42); gm_set_u16(gm_frame_sp + 10, R(0));
    R(6) = gm_u8(R(30) + 2); gm_set_u16(R(8) + 1574, R(7)); R(7) = (uint32_t)gm_s16(gm_frame_sp + 44);
    R(0) = gm_u32(gm_frame_sp + 8); R(5) = gm_u8(R(30) + 3); gm_set_u32(gm_frame_sp + 32, R(0));
    R(4) = (uint32_t)gm_s16(gm_frame_sp + 46); gm_set_u16(R(8) + 1576, R(7));
    R(0) = (uint32_t)gm_s16(gm_frame_sp + 34); gm_set_u16(R(8) + 1578, R(4));
    R(4) = (uint32_t)gm_s16(gm_frame_sp + 32); gm_set_u16(R(3) + 24, R(4)); gm_set_u16(gm_frame_sp + 12, R(6));
    gm_set_u16(gm_frame_sp + 14, R(5)); R(4) = gm_u32(gm_frame_sp + 12); gm_set_u32(gm_frame_sp + 36, R(4));
    gm_set_u16(R(3) + 26, R(0)); R(0) = (uint32_t)gm_s16(gm_frame_sp + 36); gm_set_u16(R(3) + 28, R(0));
    R(0) = (uint32_t)gm_s16(gm_frame_sp + 38); gm_set_u16(R(3) + 30, R(0)); R(11) = gm_frame_sp + 112;
}

static void dGameDisplay_ReturnGrayColorSet(GM_CTX, gptr self, uint32_t index) {
    I2_FN(0x818328ECu);
    NV_R(30, self); NV_R(28, index);
    R(5) = 0x81850000u - 4000; R(0) = i2_rotl(R(4), 2) & 0xFFFFFFFCu;
    R(0) = gm_u32(R(5) + R(0)); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
    R(3) = gm_u32(R(3) + R(0) + 1172); R(12) = gm_u32(gm_u32(R(3)) + 104); ctx->ctr = R(12);
    ctx->lr = 0x8183293Cu; ppc_call_indirect(ctx, base, ctx->ctr);
    NV_R(31, i2_rotl(R(28), 3) & 0xFFFFFFF8u); NV_R(29, 0x81850000u); R(5) = R(30) + R(31);
    NV_R(28, i2_rotl(R(28), 1) & 0xFFFFFFFEu); R(0) = (uint32_t)gm_s16(R(5) + 1444); NV_R(29, R(29) - 3936);
    gm_set_u16(R(3) + 24, R(0)); R(0) = gm_u32(R(29) + R(31)); R(4) = (uint32_t)gm_s16(R(5) + 1446);
    gm_set_u16(R(3) + 26, R(4)); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; R(4) = R(30) + R(0);
    R(0) = (uint32_t)gm_s16(R(5) + 1448); gm_set_u16(R(3) + 28, R(0));
    R(0) = (uint32_t)gm_s16(R(5) + 1450); gm_set_u16(R(3) + 30, R(0));
    R(3) = gm_u32(R(4) + 1212); R(12) = gm_u32(gm_u32(R(3)) + 104); ctx->ctr = R(12);
    ctx->lr = 0x81832990u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(5) = R(30) + R(31); R(0) = R(28) + 1; R(4) = (uint32_t)gm_s16(R(5) + 1508);
    R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; gm_set_u16(R(3) + 24, R(4)); R(0) = gm_u32(R(29) + R(0));
    R(4) = (uint32_t)gm_s16(R(5) + 1510); gm_set_u16(R(3) + 26, R(4));
    R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; R(4) = R(30) + R(0);
    R(0) = (uint32_t)gm_s16(R(5) + 1512); gm_set_u16(R(3) + 28, R(0));
    R(0) = (uint32_t)gm_s16(R(5) + 1514); gm_set_u16(R(3) + 30, R(0));
    R(3) = gm_u32(R(4) + 1212); R(12) = gm_u32(gm_u32(R(3)) + 104); ctx->ctr = R(12);
    ctx->lr = 0x818329DCu; ppc_call_indirect(ctx, base, ctx->ctr);
    R(4) = R(30) + R(31); R(0) = (uint32_t)gm_s16(R(4) + 1572); gm_set_u16(R(3) + 24, R(0));
    R(0) = (uint32_t)gm_s16(R(4) + 1574); gm_set_u16(R(3) + 26, R(0));
    R(0) = (uint32_t)gm_s16(R(4) + 1576); gm_set_u16(R(3) + 28, R(0));
    R(0) = (uint32_t)gm_s16(R(4) + 1578); gm_set_u16(R(3) + 30, R(0));
}

/* Update the three collected Star Coin icons and their animated state slots. */
static void dGameDisplay_setCollect(GM_CTX, gptr self) {
    I2_FN(0x81832CB4u);
    uint32_t saved_cr2 = ctx->cr & 0xF00000u;
    NV_R(30, self); R(3) = gm_u8(self + 1107);
    if (CMPU(R(3), 0) != 0) goto done;
    R(3) = gm_u32(0x80430000u - 24120); NV_R(29, gm_u8(R(3) + 4620));
    if (CMPU(R(29), 9) > 0) { GM_LOOP(); goto done; }
    NV_R(28, gm_u8(R(3) + 4621));
    if (CMPU(R(28), 41) > 0) { GM_LOOP(); goto done; }
    R(3) = 0x80310000u + 23440; NV_R(26, gm_u32(R(3) + 8)); R(3) = R(26) & 0xFFFFFFFEu;
    if (CMPU(R(3), 2) == 0) { GM_LOOP(); goto done; }
    R(3) = gm_u32(0x80430000u - 24512); R(4) = (uint32_t)-1;
    BL(0x81832DC0u, hle_mod_getSaveGame__10dSaveMng_cFSc); NV_R(27, R(3));
    R(3) = 0x80370000u + 16816; R(4) = 0x81850000u - 3872; R(5) = 0x81850000u - 3860;
    NV_R(25, self + 1172); NV_R(24, self + 1004); NV_R(23, 3); NV_R(22, 0);
    cr_cmp_u(ctx, 2, R(26), 0); NV_R(21, 2); NV_R(20, 0);
    NV_R(17, R(3) - 4); NV_R(19, R(4) - 4); NV_R(18, R(5) - 4); NV_R(26, 0);
    for (;;) {
        uint32_t ea;
        R(3) = R(27); R(4) = R(29); R(5) = R(28); R(6) = R(26); NV_R(16, R(17));
        ea = R(19) + 4; NV_R(15, gm_u32(ea)); NV_R(19, ea); NV_R(17, R(17) + 4);
        ea = R(18) + 4; NV_R(14, gm_u32(ea)); NV_R(18, ea);
        BL(0x81832E2Cu, hle_mod_fn_800CE210);
        R(4) = i2_rotl(R(14), 2) & 0xFFFFFFFCu; R(4) = gm_u32(R(25) + R(4));
        R(5) = i2_rotl(R(15), 2) & 0xFFFFFFFCu; R(7) = gm_u8(R(4) + 187); R(6) = R(7) & 0xFEu;
        if (CR_BIT(ctx, 10) && CMPU(R(3), 0) != 0) {
            gm_set_u8(R(4) + 187, R(6)); R(3) = gm_u32(R(25) + R(5)); R(4) = gm_u8(R(3) + 187);
            R(4) |= 1; gm_set_u8(R(3) + 187, R(4)); gm_set_u32(R(24) + R(20), R(21));
        } else {
            R(3) = gm_u32(R(16) + 4);
            if (CMPU(R(3), 8) == 0) {
                R(3) = R(7) | 1; gm_set_u8(R(4) + 187, R(3)); R(3) = gm_u32(R(25) + R(5));
                R(4) = gm_u8(R(3) + 187) & 0xFEu; gm_set_u8(R(3) + 187, R(4));
                gm_set_u32(R(24) + R(20), R(22));
            } else {
                gm_set_u8(R(4) + 187, R(6)); R(3) = gm_u32(R(25) + R(5)); R(4) = gm_u8(R(3) + 187);
                R(4) |= 1; gm_set_u8(R(3) + 187, R(4)); R(3) = gm_u32(R(24) + R(20));
                if (CMPU(R(3), 2) != 0) {
                    R(3) = R(30); R(4) = R(26); gm_set_u32(R(24) + R(20), R(21));
                    BL(0x81832EC4u, fn_801597A0);
                }
            }
        }
        NV_R(23, R(23) - 1); NV_R(26, R(26) + 1); CMPU(R(23), 0); NV_R(20, R(20) + 4);
        if (!CR_BIT(ctx, 1)) break;
        GM_LOOP();
    }
    R(3) = self + 112; BL(0x81832EE0u, hle_fn_80006EB0); GM_LOOP();
done:
    R(12) = saved_cr2; ctx->cr = (ctx->cr & ~0xF00000u) | (R(12) & 0xF00000u);
}

/* ================================================================== entry points */
#define SELF GM_ARG(0)
#define GD_MEM SELF, GD_SIZE, GD_REST_COIN_GLOBAL, 1, GD_STACK_GUARD, 4
static void gd_selftest(GM_CTX, gptr self);

GM_HLE_VERIFIED_(mod_fn_80157710, GMV_IGNORE_POLLS, GD_MEM, 0x8042A328u, 4) { dGameDisplay_constructor(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80157960, GD_MEM, 0x8042A328u, 4) { dGameDisplay_destructor(GM_PASS, SELF, GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_80157F90, GMV_IGNORE_POLLS, GD_MEM) { dGameDisplay_execute(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_801580A0, GD_MEM) { dGameDisplay_draw(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80158480, GD_MEM) { dGameDisplay_AreaSetupAll(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_80158580, GMV_IGNORE_POLLS, GD_MEM) { dGameDisplay_RestDispSetup(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_801586F0, GD_MEM) { dGameDisplay_createLayout(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_80158910, GMV_IGNORE_POLLS, GD_MEM) { dGameDisplay_AreaCheck(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_80158A90, GMV_IGNORE_POLLS, GD_MEM) { dGameDisplay_AlphaEnterAndExit(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80158890, GD_MEM, gm_u32(GD_STAGE_C4_INSTANCE) + 29, 1) { dGameDisplay_RestCoinAnimeCheck(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_80158C50, GMV_RET | GMV_IGNORE_POLLS, GD_MEM, gm_u32(0x8042A070u) + 4, 4, 0x80429CA0u, 0x50) { dGameDisplay_NormalSettle(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_80158D00, GMV_RET | GMV_IGNORE_POLLS, GD_MEM, gm_u32(0x8042A070u) + 4, 4, 0x80429CC0u, 4) { dGameDisplay_OtasukeSettle(GM_PASS, SELF); }
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
GM_HLE_VERIFIED_(mod_fn_801590B0, GMV_RET | GMV_IGNORE_POLLS, GD_MEM) { dGameDisplay_Effect1Up(GM_PASS, SELF, GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_80159250, GMV_IGNORE_POLLS, GD_MEM, ctx->r[13] - 21332, 8) { dGameDisplay_GrayColorSet(GM_PASS, SELF, GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_801594E0, GMV_IGNORE_POLLS, GD_MEM) { dGameDisplay_ReturnGrayColorSet(GM_PASS, SELF, GM_ARG(1)); }
GM_HLE_VOID(mod_fn_80159880, GD_MEM) { dGameDisplay_setPlayNum(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_80159AC0, GD_MEM) { dGameDisplay_setTime(GM_PASS, SELF, GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_80159AF0, GMV_IGNORE_POLLS, GD_MEM) { dGameDisplay_setCollect(GM_PASS, SELF); }
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
