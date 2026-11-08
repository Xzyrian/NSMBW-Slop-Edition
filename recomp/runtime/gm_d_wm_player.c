/* gm_d_wm_player.c - daWmPlayer_c: world-map player creation, companion models,
 * route gating, guide input and game-start state (track B, gm_i2.h).
 * Player objects and all tables remain in big-endian guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define WP_MANAGER       (0x80430000u - 24160)
#define WP_MAP           (0x80430000u - 24180)
#define WP_INFO          (0x80430000u - 24708)
#define WP_CS_SEQ        (0x80430000u - 24148)
#define WP_SOUND         (0x80430000u - 23448)
#define WP_LAYOUT        (0x809A0000u + 9112)
#define WP_MODE          (0x81860000u - 4864)
#define WP_ENTRY_TABLE   (0x81860000u - 6000)
#define WP_ACTIVE_TABLE  (0x81860000u - 5828)
#define WP_SCENE_TABLE   (0x81860000u - 5796)
#define WP_STAR_TABLE    (0x81860000u - 5764)
#define WP_MODEL_TABLE   (0x81860000u - 1768)
#define WP_TYPE_TABLE    (0x81850000u - 25628)
#define WP_ALL_OPEN      (0x81860000u - 508 + 1)
#define WP_ZERO          (0x80370000u + 32200)
#define WP_VT            (0x81850000u + 13624)
#define WP_SKELETONS     (0x81850000u + 9376)

static void wp_call(GM_CTX, gptr object, uint32_t slot, uint32_t ra) {
    R(4) = gm_u32(gm_u32(object) + slot); ctx->ctr = R(4); ctx->lr = ra;
    ppc_call_indirect(ctx, base, ctx->ctr);
}

static void wp_updateSubPlayerModel(GM_CTX, gptr self, uint32_t type, uint32_t scene, uint32_t extra);

static gptr wp_construct(GM_CTX, gptr self) {
    I2_FN(0x81829034u);
    NV_R(30, self); BL(0x81829050u, fn_800F5FD0);
    gm_set_u8(self + 424, 1); gm_set_u32(self + 428, (uint32_t)-1);
    NV_R(29, 0); gm_set_u32(self + 432, (uint32_t)-1); gm_set_u8(self + 456, 255);
    gm_set_u32(self + 96, WP_VT); R(3) = self + 460; R(4) = (uint32_t)-1;
    gm_set_u8(self + 396, 0); BL(0x8182908Cu, __ct__11dPyMdlMng_cFQ211dPyMdlMng_c11ModelType_e_800D6CC0);
    gm_set_u32(self + 572, 6); gm_set_u32(self + 576, 6); gm_set_u32(self + 664, 0x3F800000u);
    gm_set_u32(self + 736, 2); gm_set_u32(WP_MANAGER, self); R(3) = WP_ZERO; R(4) = gm_u32(R(3));
    gm_set_u16(self + 602, 0); gm_set_u32(self + 496, R(4)); R(4) = gm_u32(R(3) + 4); R(3) = gm_u32(R(3) + 8);
    gm_set_u32(self + 636, 0); gm_set_u8(self + 764, 0); gm_set_u32(self + 500, R(4));
    gm_set_u32(self + 504, R(3)); R(3) = self; gm_set_u32(self + 668, 0); return R(3);
}

static gptr wp_destruct(GM_CTX, gptr self, int32_t flags) {
    I2_FN(0x818290F8u);
    NV_R(29, flags); R(4) = 0; NV_R(28, 0); NV_R(30, self); BL(0x81829124u, fn_800F6E30);
    gm_set_u32(WP_MANAGER, 0); R(3) = gm_u32(self + 668); R(4) = WP_VT;
    gm_set_u32(self + 464, 0); NV_R(28, self + 460); CMPU(R(3), 0); gm_set_u32(self + 96, WP_VT);
    if (R(3)) {
        R(4) = gm_u32(gm_u32(R(3) + 4) + 8); ctx->ctr = R(4); R(4) = 1;
        ctx->lr = 0x81829160u; ppc_call_indirect(ctx, base, ctx->ctr);
    }
    R(3) = R(28); R(4) = (uint32_t)-1; BL(0x8182916Cu, hle___dt__11dPyMdlMng_cFv);
    if (flags > 1) { R(3) = self; BL(0x8182917Cu, hle__Z17FreeFromGameHeap1Pv); }
    R(3) = self; return R(3);
}

static void wp_createSubPlayers(GM_CTX, gptr self) {
    I2_FN(0x81829274u);
    NV_R(30, self); uint32_t profile = (int32_t)gm_u32(WP_MODE) < 8 ? 661 : 663;
    NV_R(28, profile); NV_R(29, 0); gm_set_u32(self + 392, 0);
    NV_R(27, 8); NV_R(26, WP_TYPE_TABLE - 4); NV_R(25, 0x81860000u); R(3) = self;
    do {
        NV_R(24, R(3)); R(3) = R(28); R(4) = self; R(5) = R(29); R(6) = 0; R(7) = 0;
        NV_R(23, gm_u32(R(26) + 4)); NV_R(26, R(26) + 4);
        BL(0x818292FCu, hle_fn_800F2A00);
        R(4) = gm_u32(WP_ACTIVE_TABLE); gm_set_u32(R(24) + 388, R(3));
        CMPU(R(23), R(4)); gm_set_u32(R(3) + 392, R(24));
        if (R(23) == R(4)) {
            R(4) = gm_u32(R(3) + 460); R(4) = gm_u32(R(4) + 4); gm_set_u32(self + 464, R(4));
        }
        NV_R(27, R(27) - 1); CMPU(R(27), 0); NV_R(29, R(29) + 1);
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
    R(4) = 0; gm_set_u32(R(3) + 388, 0);
}

static uint32_t wp_create(GM_CTX, gptr self) {
    I2_FN(0x8182919Cu);
    NV_R(29, 0); NV_R(30, self); gm_set_u16(self + 258, 0); R(3) = 0; BL(0x818291C4u, fn_8016F430);
    R(3) = self; BL(0x818291CCu, fn_2_196190_80903940); R(3) = self; gm_set_u32(self + 464, 0);
    wp_createSubPlayers(GM_PASS, self); R(3) = gm_u32(self + 464); CMPU(R(3), 0);
    if (!R(3)) {
        R(4) = 0x81850000u - 4936; R(3) = R(4) + 29; R(5) = R(4) + 47; R(6) = R(4) + 67;
        CR_SETBIT(ctx, 6, 0); R(4) = 70; BL(0x81829274u, mod_OSPanic_818380F8); return 0;
    }
    R(3) = self; R(4) = 0; R(5) = (uint32_t)-1; BL(0x818291F4u, fn_2_199840_80906FF0);
    R(4) = 0x81850000u - 4936; R(5) = R(4) + 13; R(3) = self; R(6) = R(4); R(7) = 1; NV_R(29, 1);
    BL(0x81829214u, fn_800F6710); R(3) = self; gm_set_u8(self + 292, 1); BL(0x81829220u, fn_2_195BE0_80903390);
    R(3) = self; BL(0x81829228u, fn_2_196730_80903EE0); R(3) = self; BL(0x81829230u, fn_2_1954B0_80902C60);
    R(3) = self; BL(0x81829238u, fn_2_199DF0_809075A0); R(3) = 1; return R(3);
}

static void wp_playerEntryUpdate(GM_CTX, gptr self) {
    I2_FN(0x81829364u);
    NV_R(30, self); BL(0x818293A0u, CheckIfSinglePlayer_800FC9C0); NV_R(29, R(3));
    NV_R(27, 8); NV_R(26, 0); NV_R(25, 0x81860000u); NV_R(28, 0);
    do {
        R(3) = self; R(4) = R(28); R(5) = 0; R(6) = 0; BL(0x818293C8u, fn_2_195690_80902E40);
        NV_R(27, R(27) - 1); CMPU(R(27), 0); NV_R(28, R(28) + 1); gm_set_u32(WP_ENTRY_TABLE, R(26));
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
    gm_set_u32(WP_ENTRY_TABLE, 1); NV_R(28, gm_u32(WP_INFO) + 2892);
    NV_R(27, 8); NV_R(26, 0); NV_R(25, WP_MODEL_TABLE);
    R(3) = WP_ENTRY_TABLE - 4; R(4) = WP_ACTIVE_TABLE - 4; NV_R(24, R(28)); NV_R(23, 0);
    do {
        R(5) = R(23) < 4 ? R(24) - 1992 : R(24); R(5) = gm_u32(R(5));
        NV_R(22, R(3) + 4); NV_R(21, R(4) + 4); CMPU(R(5), 3);
        if (R(5) == 3) {
            R(4) = gm_u32(R(4) + 4); R(6) = 1; gm_set_u32(R(3) + 4, 1);
            R(3) = R(26) - 1; ctx->xer_ca = R(26) != 0;
            R(5) = i2_rotl(R(4), 2) & 0xFFFFFFFCu; R(5) = gm_u32(R(25) + R(5)); CMPU(R(5), 3);
            int modelIs3 = R(5) == 3;
            R(5) = R(26) != 0; ctx->xer_ca = R(26) != 0;
            if (!modelIs3) R(6) = R(5);
            R(3) = self; BL(0x81829474u, fn_2_195690_80902E40);
        }
        NV_R(27, R(27) - 1); NV_R(23, R(23) + 1); NV_R(24, R(24) + 4); CMPU(R(27), 0);
        NV_R(26, R(26) + 4); R(4) = R(21); R(3) = R(22);
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
    BL(0x81829498u, CheckIfSinglePlayer_800FC9C0); CMPU(R(29), R(3));
    if (R(29) != R(3)) {
        if (R(29)) BL(0x818294ACu, fn_2_16ADC0_808D8570);
        else { BL(0x818294B4u, fn_800FD0B0); BL(0x818294B8u, fn_2_16AE40_808D85F0); }
    }
    ctx->ctr = 8; R(4) = WP_ACTIVE_TABLE - 4; R(5) = WP_MODEL_TABLE; R(3) = 0;
    do {
        R(6) = R(3) < 4 ? R(28) : R(28) - 1992;
        R(7) = gm_u32(R(4) + 4); R(4) += 4; R(3)++; R(6) = gm_u32(R(6)); NV_R(28, R(28) + 4);
        R(7) = i2_rotl(R(7), 2) & 0xFFFFFFFCu; gm_set_u32(R(5) + R(7), R(6));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    R(3) = gm_u32(self + 388); CMPU(R(3), 0);
    while (R(3)) {
        R(4) = 0x80320000u - 11364; gm_set_u32(R(3) + 660, R(4));
        R(3) = gm_u32(R(3) + 388); CMPU(R(3), 0); if (R(3)) GM_LOOP();
    }
}

static void wp_updateSubPlayerModel(GM_CTX, gptr self, uint32_t type, uint32_t scene, uint32_t extra) {
    I2_FN(0x81829564u);
    NV_R(27, gm_u32(self + 388)); CMPU(R(27), 0);
    if (R(27)) {
        NV_R(30, extra); NV_R(29, scene); NV_R(28, self); NV_R(26, type);
        for (;;) {
            R(3) = R(27); R(4) = type; BL(0x818295ACu, hle_mod_fn_2_181B10); CMPU(R(3), 0);
            if (R(3)) {
                NV_R(27, gm_u32(R(27) + 388)); CMPU(R(27), 0);
                if (R(27)) { GM_LOOP(); continue; }
                return;
            }
            R(4) = gm_u32(R(27) + 460); R(3) = gm_u32(WP_ACTIVE_TABLE); NV_R(27, gm_u32(R(4) + 4));
            CMPU(R(3), type); if (R(3) == type) gm_set_u32(self + 464, R(27));
            NV_R(28, gm_u32(R(27))); R(4) = R(29); R(3) = gm_u32(R(28) + 48); ctx->ctr = R(3);
            R(3) = R(27); ctx->lr = 0x818295F8u; ppc_call_indirect(ctx, base, ctx->ctr);
            CMPU(R(30), 0); if (!R(30)) return;
            R(3) = gm_u32(R(28) + 64); ctx->ctr = R(3); R(3) = R(27);
            ctx->lr = 0x81829610u; ppc_call_indirect(ctx, base, ctx->ctr);
            R(3) = gm_u32(R(28) + 72); ctx->ctr = R(3); R(3) = R(27);
            ctx->lr = 0x81829620u; ppc_call_indirect(ctx, base, ctx->ctr); return;
        }
    }
}

static void wp_updatePlayerMode(GM_CTX, gptr self) {
    I2_FN(0x81829644u);
    NV_R(30, self); NV_R(25, gm_u32(WP_INFO) + 2892); NV_R(26, 0x809A0000u);
    NV_R(27, 8); NV_R(29, 0); NV_R(24, WP_STAR_TABLE); R(3) = WP_ACTIVE_TABLE - 4;
    do {
        R(4) = R(29) < 4 ? R(25) : R(25) - 1992; R(4) = gm_u32(R(4)); NV_R(23, R(3) + 4); CMPU(R(4), 3);
        if (R(4) == 3) {
            NV_R(28, gm_u32(R(3) + 4)); R(4) = R(29); R(3) = gm_u32(WP_LAYOUT);
            BL(0x818296D4u, mod_fn_2_1C3A40_81814E70); R(5) = R(3);
            R(3) = i2_rotl(R(28), 2) & 0xFFFFFFFCu; R(3) = gm_u32(R(24) + R(3));
            R(4) = R(28); R(6) = R(3) & 1; R(3) = self;
            wp_updateSubPlayerModel(GM_PASS, self, R(4), R(5), R(6));
        }
        NV_R(27, R(27) - 1); NV_R(29, R(29) + 1); CMPU(R(27), 0); NV_R(25, R(25) + 4); R(3) = R(23);
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
}

static uint32_t wp_isRouteClosedByGate(GM_CTX) {
    I2_FN(0x818299ACu);
    R(5) = gm_u8(WP_ALL_OPEN); CMPU(R(5), 0); R(5) = 0;
    if (CR_BIT(ctx, 2)) { BL(0x818299D4u, ext_fn_2_19A570_81845428); R(5) = R(3); }
    R(3) = R(5); return R(3);
}

static void wp_initActiveCharaFlags(GM_CTX) {
    R(7) = gm_u32(WP_INFO); R(4) = WP_ACTIVE_TABLE - 4; R(3) = 0; ctx->ctr = 8;
    R(5) = R(7) + 2892; R(6) = WP_MODEL_TABLE;
    do {
        R(7) = R(3) < 4 ? R(5) : R(5) - 1992; R(7) = gm_u32(R(7)); CMPU(R(7), 3); R(7) = R(7) == 3 ? 3 : 0;
        R(8) = gm_u32(R(4) + 4); R(4) += 4; R(3)++; R(5) += 4;
        R(8) = i2_rotl(R(8), 2) & 0x1Cu; gm_set_u32(R(6) + R(8), R(7));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
}

static uint32_t wp_getSkeletonRoot(GM_CTX, uint32_t index) {
    CMPU(index, 9); R(4) = 0;
    if (index < 9) { R(4) = WP_SKELETONS; R(3) = i2_rotl(index, 2) & 0xFFFFFFFCu; R(4) = gm_u32(R(4) + R(3)); }
    R(3) = R(4); return R(3);
}

static uint32_t wp_getCourseInVoiceId(GM_CTX, uint32_t point) {
    I2_FN(0x81815110u);
    NV_R(30, point); BL(0x81815128u, fn_80100940); CMPS(R(3), 0); R(3) = 5;
    if (CR_BIT(ctx, 0)) return R(3);
    R(4) = gm_u32(WP_ACTIVE_TABLE); CMPU(R(4), 0); if (!R(4)) return R(3);
    R(3) = gm_u32(WP_MAP); R(4) = gm_u32(R(3) + 13196); R(4) = (uint32_t)((int32_t)R(4) * 11427);
    R(4) = i2_rotl(R(4), 3) & 0xFFFFFFF8u; R(3) += R(4) + 13204; R(4) = point; BL(0x81815168u, hle_fn_800F56B0);
    BL(0x8181516Cu, GetCourseNoFromPointName__6dWmLibFPCc_800F9530);
    BL(0x81815170u, GetCourseTypeFromCourseNo__6dWmLibFi_800F9840);
    R(4) = R(3); R(3)--; CMPU(R(3), 2); R(3) = 6; if (CR_BIT(ctx, 0)) return R(3);
    CMPU(R(4), 3); R(5) = R(4) == 3 ? 4 : 6; CMPU(R(4), 8); if (R(4) != 8) R(3) = R(5); return R(3);
}

static void wp_checkCsGuideKey(GM_CTX, gptr self) {
    I2_FN(0x81829738u);
    NV_R(30, self); BL(0x81829754u, fn_2_19B000_809087B0); CMPU(R(3), 0); R(3) = 0;
    if (CR_BIT(ctx, 2)) return;
    NV_R(29, 0x80430000u); R(3) = gm_u32(WP_CS_SEQ); BL(0x8182976Cu, fn_2_1A7E90_80915640); CMPU(R(3), 0);
    if (R(3)) {
        R(3) = gm_u32(WP_CS_SEQ); BL(0x8182977Cu, FUN_80915600__11dCsSeqMng_cFv_80915610); CMPU(R(3), 0);
        if (!R(3)) goto check_keys;
    }

guide_path:
    R(3) = 4; NV_R(29, gm_u32(self + 648)); gm_set_u32(self + 652, 4); gm_set_u32(self + 648, 4);
    R(3) = self; BL(0x8182979Cu, fn_2_19B600_80908DB0); R(4) = R(3); R(3) = self; BL(0x818297A8u, fn_2_196BD0_80904380);
    R(4) = gm_u8(self + 601) & 0x10; CR0(ctx, R(4));
    if (R(4)) {
        if (gm_u32(self + 648) != 4) { gm_set_u32(self + 768, 0); R(3) = self; BL(0x818297D0u, fn_2_197070_80904820); }
    } else { R(3) = self; BL(0x818297DCu, fn_2_196CA0_80904450); }
    if (gm_u32(self + 648) == 4) gm_set_u32(self + 648, R(29));
    return;

check_keys:
    R(3) = 0; BL(0x818297F8u, mod_fn_800FD390_818146E4); NV_R(29, R(3)); R(3) = gm_u32(WP_SOUND);
    if (R(29) == 1) goto key_one;
    if (R(29) == 2) goto key_two;
    if (R(29) == 3) {
        R(4) = gm_u32(R(3)); R(5) = 0x81860000u - 6288; CMPU(R(4), R(5)); if (R(4) != R(5)) R(3) = 0;
        R(3) = gm_u8(R(3) + 11) & 0x20; CR0(ctx, R(3)); if (R(3)) goto clear_input;
        goto ui_input;
    }
    goto ui_input;

key_two:
    R(4) = gm_u32(R(3)); R(5) = 0x81860000u - 6344; CMPU(R(4), R(5)); if (R(4) != R(5)) R(3) = 0;
    R(3) = gm_u8(R(3) + 10) & 8; CR0(ctx, R(3)); if (R(3)) goto clear_input;
    goto ui_input;

key_one:
    R(4) = gm_u32(gm_u32(R(3)) + 32); ctx->ctr = R(4); R(4) = 16384;
    ctx->lr = 0x818298DCu; ppc_call_indirect(ctx, base, ctx->ctr); CMPU(R(3), 0); if (R(3)) GM_LOOP();
    if (R(3)) goto ui_input;
    goto clear_input;

ui_input:
    R(3) = gm_u32(WP_LAYOUT); R(4) = gm_u8(R(3) + 1350); CMPU(R(4), 0);
    if (!R(4)) { R(4) = gm_u8(gm_u32(R(3) + 1332) + 597); CMPU(R(4), 1); }
    if (gm_u8(R(3) + 1350) || R(4) != 1) gm_set_u8(R(3) + 1349, 1);
    BL(0x81829898u, fn_2_16AF80_808D8730); R(3) = gm_u32(WP_CS_SEQ); R(5) = self;
    R(6) = gm_u32(0x80430000u - 23932); R(4) = 30; goto play_sequence;

clear_input:
    R(3) = gm_u32(WP_SOUND); R(4) = gm_u32(gm_u32(R(3)) + 32); ctx->ctr = R(4); R(4) = 16;
    ctx->lr = 0x81829900u; ppc_call_indirect(ctx, base, ctx->ctr); CMPU(R(3), 0);
    if (!R(3)) { R(3) = gm_u32(WP_CS_SEQ); R(4) = 47; goto sequence_simple; }
    R(4) = R(29) == 0 ? 512 : 1536; NV_R(29, 0x80430000u);
    R(3) = gm_u32(WP_SOUND); R(5) = gm_u32(gm_u32(R(3)) + 32); ctx->ctr = R(5);
    ctx->lr = 0x81829940u; ppc_call_indirect(ctx, base, ctx->ctr); CMPU(R(3), 0);
    if (!R(3)) { R(3) = gm_u32(WP_CS_SEQ); R(4) = 49; goto sequence_simple; }
    R(3) = gm_u32(WP_SOUND); R(4) = gm_u32(gm_u32(R(3)) + 32); ctx->ctr = R(4); R(4) = 4096;
    ctx->lr = 0x81829970u; ppc_call_indirect(ctx, base, ctx->ctr); CMPU(R(3), 0);
    if (!R(3)) { GM_LOOP(); goto guide_path; }
    R(3) = gm_u32(WP_CS_SEQ); R(4) = 50;

sequence_simple:
    R(5) = 0; R(6) = 0;

play_sequence:
    R(7) = 128; BL(0x81829994u, FUN_801017c0__11dCsSeqMng_cFQ211dCsSeqMng_c10CUTSCENE_eP14dWmDemoActor_cPvi_801016B0);
}

static uint32_t wp_startGame(GM_CTX, gptr self, uint32_t world, uint32_t stage, uint32_t entrance) {
    I2_FN(0x81829A5Cu);
    R(11) = gm_frame_sp + 96; BL(0x81829A70u, __save_gpr_entry_802DCD54);
    NV_R(31, gm_u32(WP_INFO)); NV_R(21, gm_u32(WP_LAYOUT)); NV_R(19, self);
    NV_R(28, world); NV_R(29, stage); NV_R(30, entrance); NV_R(24, R(31));
    NV_R(23, WP_ENTRY_TABLE); NV_R(22, WP_ACTIVE_TABLE); NV_R(26, WP_SCENE_TABLE);
    NV_R(20, 0); NV_R(25, 1); NV_R(27, 0);
    do {
        if (R(20) == 4) NV_R(24, R(24) + 1992);
        R(0) = gm_u32(R(24) + 900); CMPS(R(0), 3);
        if ((int32_t)R(0) == 3) {
            gm_set_u32(R(23), R(25)); R(3) = R(21); R(4) = R(20); BL(0x81829AE0u, fn_2_1C3A40_809311F0);
            R(0) = gm_u32(R(22)); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; gm_set_u32(R(26) + R(0), R(3));
        } else gm_set_u32(R(23), R(27));
        NV_R(20, R(20) + 1); NV_R(23, R(23) + 4); CMPS(R(20), 8); NV_R(22, R(22) + 4); NV_R(24, R(24) + 4);
        if (CR_BIT(ctx, 0)) GM_LOOP(); else break;
    } while (1);
    R(3) = self; BL(0x81829B14u, fn_2_199DF0_809075A0);
    gm_set_u32(R(31) + 80, world); gm_set_u32(R(31) + 84, stage); gm_set_u8(R(31) + 109, 0);
    gm_set_u8(R(1) + 9, world); gm_set_u8(R(1) + 8, stage); BL(0x81829B30u, CheckIfSinglePlayer_800FC9C0); CMPS(R(3), 0);
    if (!R(3)) {
        R(5) = 0x80430000u; R(0) = gm_u8(R(1) + 9); R(3) = gm_u32(WP_INFO) + R(0);
        gm_set_u8(R(3) + 937, 1); R(3) = gm_u32(WP_INFO) + R(0); gm_set_u8(R(3) + 917, 42);
    }
    R(3) = world; R(4) = stage; R(5) = R(1) + 9; R(6) = R(1) + 8; BL(0x81829B78u, fn_800FD120);
    R(3) = gm_u8(R(1) + 9); R(4) = 0; R(0) = gm_u8(R(1) + 8);
    gm_set_u32(R(1) + 24, 0); gm_set_u8(R(1) + 23, 0); gm_set_u8(R(1) + 22, 0);
    gm_set_u8(R(1) + 21, entrance); gm_set_u8(R(1) + 28, world); gm_set_u8(R(1) + 29, stage);
    gm_set_u8(R(1) + 30, R(3)); gm_set_u8(R(1) + 31, R(0)); BL(0x81829BA8u, fn_2_1BADF0_809285A0);
    R(3) = R(31); R(4) = R(1) + 16; BL(0x81829BB4u, hle_startGame__7dInfo_cFRCQ27dInfo_c15StartGameInfo_s);
    R(11) = gm_frame_sp + 96; R(3) = 1; BL(0x81829BC0u, __restore_gpr_entry_802DCDA0); return R(3);
}

GM_HLE_VERIFIED_(mod_fn_2_195020, GMV_IGNORE_POLLS, 0, 0) { R(3) = wp_construct(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1950F0, GMV_IGNORE_POLLS, 0, 0) { R(3) = wp_destruct(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_2_1951C0, GMV_IGNORE_POLLS, 0, 0) { R(3) = wp_create(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_195430, GMV_IGNORE_POLLS, 0, 0) { wp_createSubPlayers(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_195500, GMV_IGNORE_POLLS, 0, 0) { wp_playerEntryUpdate(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_195730, GMV_IGNORE_POLLS, 0, 0) { wp_updateSubPlayerModel(GM_PASS, GM_ARG(0), GM_ARG(1), GM_ARG(2), GM_ARG(3)); }
GM_HLE_VERIFIED_(mod_fn_2_195800, GMV_IGNORE_POLLS, 0, 0) { wp_updatePlayerMode(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_196980, GMV_IGNORE_POLLS, 0, 0) { wp_checkCsGuideKey(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_19A570, GMV_IGNORE_POLLS, 0, 0) { R(3) = wp_isRouteClosedByGate(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_2_19BC30, 0, 0, 0) { wp_initActiveCharaFlags(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_2_19F670, GMV_IGNORE_POLLS, 0, 0) { R(3) = wp_startGame(GM_PASS, GM_ARG(0), GM_ARG(1), GM_ARG(2), GM_ARG(3)); }
GM_HLE_VERIFIED_(mod_fn_80100A50, 0, 0, 0) { R(3) = wp_getSkeletonRoot(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_80100B40, GMV_IGNORE_POLLS, 0, 0) { R(3) = wp_getCourseInVoiceId(GM_PASS, GM_ARG(0)); }
