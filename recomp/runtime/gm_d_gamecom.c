/* gm_d_gamecom.c - dGameCom utility methods replaced by the 8-player module.
 * Track B (gm_i2.h, docs/DECOMP.md), instance 2. All layout and manager objects remain
 * in big-endian guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define GC_INFO       (0x80430000u - 24708)
#define GC_STACK_GUARD (0x81860000u - 300)

static void gc_createSmallScore(GM_CTX) {
    I2_FN(0x8180AAA8u);
    R(8) = R(4);
    CMPS(R(5), -1); R(4) = R(3);
    if (CR_BIT(ctx, 2)) R(7) = 8;
    else {
        if (CMPS(R(5), 7) > 0) return;
        R(3) = i2_rotl(R(5), 2) & 0xFFFFFFFCu; R(5) = 0x81860000u - 5828;
        R(7) = gm_u32(R(5) + R(3));
    }
    R(3) = gm_u32(0x80430000u - 23856); CMPU(R(6), 0); R(5) = R(8); R(6) = R(7);
    if (CR_BIT(ctx, 2)) BL(0x8180AB08u, fn_8010CEF0);
    else BL(0x8180AB00u, fn_8010CFA0);
}

static void gc_showFukidashi(GM_CTX) {
    R(0) = gm_u32(ctx->r[13] - 21628); R(9) = R(3); R(5) = R(4);
    if (CMPS(R(0), 0) != 0) return;
    R(6) = 0x802F0000u + 2808; R(7) = gm_u32(ctx->r[13] - 21344);
    R(0) = gm_u8(R(6) + R(4));
    if (CMPS(R(0), 0) != 0) {
        R(11) = R(7) + 872; ctx->ctr = 8;
        do {
            R(0) = gm_u8(R(11) + 25);
            if (CMPS(R(0), 0) != 0) {
                R(0) = gm_u32(R(11));
                if (CMPS(R(4), R(0)) == 0) return;
            }
            R(11) += 572;
            if (--ctx->ctr) GM_LOOP(); else break;
        } while (1);
    }
    R(8) = gm_u32(GC_INFO);
    if (CMPS(R(4), 1) == 0) {
        R(6) = R(8) + R(3);
        if (CMPS(R(3), 4) >= 0) R(6) += 106;
        R(0) = gm_u8(R(6) + 2902); if (CMPS(R(0), 0) != 0) return;
    }
    if (CMPS(R(7), 0) == 0) return;
    R(0) = (uint32_t)((int32_t)R(3) * 22); R(0) = R(8) + R(0); R(6) = R(0) + R(4);
    if (CMPS(R(3), 4) >= 0) R(6) += 22;
    R(0) = gm_u8(R(6) + 2814); if (CMPS(R(0), 0) != 0) return;
    R(0) = (uint32_t)((int32_t)R(3) * 572); R(6) = R(7) + R(0);
    R(0) = gm_u8(R(6) + 897);
    if (CMPS(R(0), 0) == 0) {
        R(3) = R(7); R(4) = R(9); fn_801571A0(ctx, base); return;
    }
    R(0) = gm_u32(R(6) + 872); if (CMPS(R(4), R(0)) != 0) return;
    R(3) = gm_u32(R(6) + 880); R(0) = 0;
    gm_set_u32(R(6) + 876, R(3)); gm_set_u32(R(6) + 892, R(0));
}

static void gc_windowPaneColorSet(GM_CTX, gptr window, uint32_t player) {
    I2_FN(0x8180AD10u);
    NV_R(30, window); R(3) = R(4); BL(0x8180AD30u, mfn_81806AB8); NV_R(29, R(3));
    R(3) = gm_u32(gm_u32(window) + 108); R(4) = 1; ctx->ctr = R(3); R(3) = window;
    ctx->lr = 0x8180AD4Cu; ppc_call_indirect(ctx, base, ctx->ctr);
    R(4) = 0x81850000u - 26640; R(5) = i2_rotl(R(29), 2) & 0xFFFFFFFCu;
    R(4) += R(5); R(6) = gm_u8(R(4)); R(7) = gm_u8(R(4) + 2); R(4) = gm_u8(R(4) + 1);
    R(7) = i2_rotl(R(7), 16) & 0xFFFF0000u; gm_set_u32(R(3) + 20, R(7));
    R(7) = 0x81850000u; R(4) = (i2_rotl(R(6), 16) & 0xFFFF0000u) | (R(4) & ~0xFFFF0000u);
    gm_set_u32(R(3) + 16, R(4)); R(4) = R(7) - 26768; R(4) += R(5); R(5) = gm_u8(R(4));
    R(7) = 255; R(6) = gm_u8(R(4) + 2); R(4) = gm_u8(R(4) + 1);
    R(6) = i2_rotl(R(6), 16) & 0xFFFF0000u; R(7) = (R(6) & 0xFFFFFF00u) | (R(7) & ~0xFFFFFF00u);
    R(4) = (i2_rotl(R(5), 16) & 0xFFFF0000u) | (R(4) & ~0xFFFF0000u);
    gm_set_u32(R(3) + 24, R(4)); gm_set_u32(R(3) + 28, R(7));
}

static void gc_playerEnterCheck(GM_CTX, uint32_t player) {
    R(4) = gm_u32(GC_INFO); R(5) = i2_rotl(player, 2) & 0xFFFFFFFCu; CMPU(R(3), 4);
    R(3) = R(4) + R(5); R(3) += CR_BIT(ctx, 0) ? 900 : 2892;
    R(3) = gm_u32(R(3)) ^ 3; R(3) = cntlzw(R(3)); R(3) = i2_rotl(R(3), 27) & 0x7FFFFFFu;
}

static void gc_player1upColor(GM_CTX, gptr text, uint32_t player) {
    I2_FN(0x8180ADF0u);
    NV_R(28, 0x81860000u); NV_R(30, text); R(3) = gm_u32(R(28) - 300);
    gm_set_u32(gm_frame_sp + 20, R(3)); R(3) = R(4); BL(0x8180AE28u, mfn_81806AB8);
    R(5) = gm_u32(text); R(4) = 0x81850000u - 26352; NV_R(27, i2_rotl(R(3), 2) & 0xFFFFFFFCu);
    R(3) = gm_u32(R(4) + R(27)); NV_R(29, gm_frame_sp + 8); NV_R(26, gm_u32(R(5) + 40));
    R(4) = 0; gm_set_u32(gm_frame_sp + 16, R(3)); R(5) = R(29); gm_set_u32(gm_frame_sp + 8, R(3));
    ctx->ctr = R(26); R(3) = text; ctx->lr = 0x8180AE60u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = 0x81850000u - 26384; R(3) = gm_u32(R(3) + R(27)); ctx->ctr = R(26); R(4) = 2; R(5) = R(29);
    gm_set_u32(gm_frame_sp + 12, R(3)); gm_set_u32(gm_frame_sp + 8, R(3)); R(3) = text;
    ctx->lr = 0x8180AE88u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = gm_u32(R(28) - 300); R(4) = gm_u32(gm_frame_sp + 20);
    if (CMPU(R(3), R(4)) == 0) return;
    BL(0x8180AEC0u, mfn_81844FCC);
}

static void gc_isNowCourseClear(GM_CTX) {
    I2_FN(0x8180AFF0u);
    R(3) = 0x81860000u - 508; R(3) = gm_u8(R(3) + 2); CMPU(R(3), 0); R(3) = 1;
    if (!CR_BIT(ctx, 2)) return;
    R(4) = gm_u32(0x80430000u - 24032); if (CMPU(R(4), 0) != 0) return;
    R(4) = 0x80310000u + 23440; R(4) = gm_u8(R(4) + 13); if (CMPU(R(4), 40) == 0) return;
    R(4) = gm_u16(0x80430000u - 30926); if (CMPU(R(4), 5) != 0) return;
    R(4) = 0x80430000u - 24704; R(4) = gm_u8(R(4) + 3) & 0x10; CR0(ctx, R(4));
    if (!CR_BIT(ctx, 2)) return;
    R(3) = gm_u32(0x80430000u - 24512); R(4) = (uint32_t)-1;
    BL(0x8180B06Cu, hle_mod_getSaveGame__10dSaveMng_cFSc);
    R(4) = 0x80310000u; R(5) = R(4) + 23440; R(4) = gm_u8(R(5) + 12); R(6) = 48; R(5) = gm_u8(R(5) + 13);
    BL(0x8180B084u, hle_mod_CheckLevelCondition__9SaveBlockFiii);
}

GM_HLE_VERIFIED_(mod_CreateSmallScore__8dGameComFRC7mVec3_ciib, GMV_IGNORE_POLLS, 0, 0) { gc_createSmallScore(GM_PASS); }
GM_HLE_VERIFIED_(mod_showFukidashi__8dGameComFii, GMV_IGNORE_POLLS, gm_u32(ctx->r[13] - 21344), 4904) {
    gc_showFukidashi(GM_PASS);
}
GM_HLE_VERIFIED_(mod_WindowPaneColorSet__8dGameComFPQ34nw4r3lyt6Windowi, GMV_IGNORE_POLLS, GM_ARG(0), 256) {
    gc_windowPaneColorSet(GM_PASS, GM_ARG(0), GM_ARG(1));
}
GM_HLE_INT(mod_PlayerEnterCheck__8dGameComFi, GC_INFO, 4) { gc_playerEnterCheck(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_Player1upColor__8dGameComFP12LytTextBox_ci, GMV_IGNORE_POLLS, GM_ARG(0), 256, GC_STACK_GUARD, 4) {
    gc_player1upColor(GM_PASS, GM_ARG(0), GM_ARG(1));
}
GM_HLE_INT(mod_isNowCourseClear__8dGameComFv, 0x80315B9Cu, 4) { gc_isNowCourseClear(GM_PASS); }
