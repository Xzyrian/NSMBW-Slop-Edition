/* gm_d_stock_item.c - dStockItem_c: stock-item layout, player / item positioning,
 * item-use effects, selection checks and window states (track B, gm_i2.h). */
#include "gm_i2.h"
RT_STATE_FILE

#define STOCK_FRAME         (0x81860000u - 300)
#define STOCK_RES           (0x81850000u - 6908)
#define STOCK_ACTIVE        (0x81860000u - 5828)
#define STOCK_CREATE_ITEM   (0x81860000u - 5764)
#define STOCK_PLAYER_MODE   (0x81860000u - 5796)
#define STOCK_INFO          (0x80430000u - 24708)
#define STOCK_SOUND_MANAGER (0x80430000u - 23416)
#define STOCK_SOUND_GLOBAL  (0x80430000u - 23384)
#define STOCK_CONST         (0x80930000u + 22752)
#define STOCK_MODE_TABLE    (0x80930000u + 23016)
#define STOCK_ITEM_TABLE    (0x80930000u + 23068)
#define STOCK_OPEN_WAIT     (0x80990000u + 22608)

#define LF(n, a) (ctx->f[n].d = ctx->ps1[n] = ldfs(base, (a)))
#define SF(a, v) stfs(base, (a), (v))

static uint32_t stock_classInit(GM_CTX) {
    I2_FN(0x8181F0A8u);
    R(3) = 2488; BL(0x8181F0C0u, hle_AllocateMemoryBlock);
    NV_R(30, R(3)); BL(0x8181F0C8u, fn_2_41C00_807AF3B0);
    R(3) = R(30); return R(3);
}

static uint32_t stock_createLayout(GM_CTX, gptr self) {
    I2_FN(0x8181F0E0u);
    NV_R(25, 0x81860000u); NV_R(28, self); NV_R(29, self + 116);
    R(3) = gm_u32(STOCK_FRAME); gm_set_u32(gm_frame_sp + 128, R(3));
    NV_R(27, STOCK_RES); R(4) = R(27) + 1229; R(3) = R(29); R(5) = 0;
    BL(0x8181F130u, hle_loadArc__Q23m2d13EmbedLayout_cFPCcb);
    NV_R(30, R(3)); CMPU(R(3), 0);
    if (R(3) != 0) {
        R(4) = R(27) + 1210; R(3) = R(29); R(5) = 0; BL(0x8181F14Cu, hle_fn_800C8A10);
        NV_R(26, gm_frame_sp + 8); R(4) = 0x81850000u + 11836; R(3) = R(26); R(5) = 24;
        BL(0x8181F164u, mod_memcpy_81844C38);
        R(3) = R(29); R(4) = R(26); R(5) = 6; BL(0x8181F174u, hle_loadAnimations__Q23m2d13EmbedLayout_cFPPCci);
        NV_R(26, gm_frame_sp + 8); R(4) = 0x81850000u + 11860; R(3) = R(26); R(5) = 120;
        BL(0x8181F18Cu, mod_memcpy_81844C38);
        R(5) = R(27) + 8; R(3) = R(29); R(4) = R(26); R(6) = 30;
        BL(0x8181F1A0u, hle_loadGroups__Q23m2d13EmbedLayout_cFPPCcPCii);
        R(3) = R(29); BL(0x8181F1A8u, CBGetBytesAvailableForRead_80007220); gm_set_u32(R(28) + 584, R(3));
        R(5) = R(28) + 588; R(4) = 0x81850000u + 11980; R(3) = R(29); R(6) = 14;
        BL(0x8181F1C4u, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
        R(3) = R(27) + 1130; gm_set_u32(gm_frame_sp + 8, R(3));
        R(3) = R(27) + 941; gm_set_u32(gm_frame_sp + 12, R(3));
        R(4) = gm_frame_sp + 8; R(3) = R(29); R(5) = R(27); R(6) = 2; R(7) = 2;
        BL(0x8181F1ECu, hle_setLangStrings__Q23m2d13EmbedLayout_cFPPCcPCiii);
        R(5) = R(28) + 644; R(4) = 0x81850000u + 12036; R(3) = R(29); R(6) = 24;
        BL(0x8181F204u, hle_getPictures__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7Picturei);
        R(5) = R(28) + 2312; R(4) = 0x81850000u + 12132; R(3) = R(29); R(6) = 8;
        BL(0x8181F21Cu, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
        R(5) = R(28) + 2344; R(4) = 0x81850000u + 12164; R(3) = R(29); R(6) = 36;
        BL(0x8181F234u, hle_getPictures__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7Picturei);
    }
    R(3) = gm_u32(STOCK_FRAME); R(4) = gm_u32(gm_frame_sp + 128); CMPU(R(3), R(4));
    if (R(3) == R(4)) { R(3) = R(30); return R(3); }
    BL(0x8181F270u, mfn_81844FCC); return R(3);
}

static uint32_t stock_getPosPane(GM_CTX, gptr self, uint32_t player) {
    I2_FN(0x8181F274u);
    R(3) = gm_u32(self + 2224); R(5) = 0x81850000u - 7164;
    R(4) = i2_rotl(player, 2) & 0xFFFFFFFCu; R(3) = i2_rotl(R(3), 5) & 0xFFFFFFE0u;
    R(3) = R(5) + R(3); R(3) += R(4); R(4) = gm_u32(R(3) - 32); R(3) = 44;
    CMPU(R(4), 0); if (R(4) != 0) R(3) = R(4); return R(3);
}

static void stock_calcPosScale(GM_CTX, gptr self) {
    I2_FN(0x8181F2A8u);
    R(11) = gm_frame_sp + 432; BL(0x8181F2CCu, __save_gpr_entry_802DCD48);
    R(4) = gm_u32(self + 2224); NV_R(31, STOCK_CONST); NV_R(20, STOCK_ACTIVE);
    R(0) = R(4) - 1; LF(0, R(31) + 248); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
    LF(1, R(31) + 176); R(4) = self + R(0); NV_R(30, self); R(4) = gm_u32(R(4) + 588);
    SF(gm_frame_sp + 44, ctx->f[1].d); NV_R(21, 0); R(3) = gm_u32(R(4) + 68); NV_R(22, 0);
    R(0) = gm_u32(R(4) + 72); gm_set_u32(gm_frame_sp + 16, R(3)); LF(31, R(31) + 252);
    gm_set_u32(gm_frame_sp + 20, R(0)); LF(1, gm_frame_sp + 16); LF(2, gm_frame_sp + 20);
    SF(gm_frame_sp + 144, ctx->f[0].d); LF(30, R(31) + 256); SF(gm_frame_sp + 156, ctx->f[1].d);
    SF(gm_frame_sp + 28, ctx->f[2].d); SF(gm_frame_sp + 148, ctx->f[0].d); SF(gm_frame_sp + 152, ctx->f[0].d);

    do {
        R(3) = R(30) + R(22); R(0) = gm_u8(R(3) + 2304); CMPS(R(0), 0);
        if (R(0) != 0) {
            NV_R(23, gm_u32(R(20))); R(3) = R(30); R(4) = R(21);
            BL(0x8181F35Cu, hle_mod_getIconPictureIDforPlayer__12dStockItem_cFi); CMPS(R(3), 44);
            if (R(3) != 44) {
                R(0) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(3) = gm_frame_sp + 84;
                R(5) = R(30) + R(0); R(4) = gm_frame_sp + 132; NV_R(17, gm_u32(R(5) + 2312));
                R(5) = gm_u32(R(17) + 144); gm_set_u32(gm_frame_sp + 324, R(5));
                R(0) = gm_u32(R(17) + 160); gm_set_u32(gm_frame_sp + 340, R(0));
                NV_R(16, gm_u32(R(17) + 132)); R(12) = gm_u32(R(17) + 136);
                R(11) = gm_u32(R(17) + 140); R(10) = gm_u32(R(17) + 148);
                R(9) = gm_u32(R(17) + 152); R(8) = gm_u32(R(17) + 156);
                R(7) = gm_u32(R(17) + 164); R(6) = gm_u32(R(17) + 168);
                R(5) = gm_u32(R(17) + 172); R(0) = gm_u32(R(17) + 176);
                LF(1, gm_frame_sp + 324); LF(0, gm_frame_sp + 340);
                gm_set_u32(gm_frame_sp + 312, R(16)); gm_set_u32(gm_frame_sp + 316, R(12));
                gm_set_u32(gm_frame_sp + 320, R(11)); gm_set_u32(gm_frame_sp + 328, R(10));
                gm_set_u32(gm_frame_sp + 332, R(9)); gm_set_u32(gm_frame_sp + 336, R(8));
                gm_set_u32(gm_frame_sp + 344, R(7)); gm_set_u32(gm_frame_sp + 348, R(6));
                gm_set_u32(gm_frame_sp + 352, R(5)); gm_set_u32(gm_frame_sp + 356, R(0));
                SF(gm_frame_sp + 132, ctx->f[1].d); SF(gm_frame_sp + 136, ctx->f[0].d);
                SF(gm_frame_sp + 140, ctx->f[31].d);
                BL(0x8181F3F0u, CrapUpPositions__FP7Point3dPC7Point3d_800B32E0);
                LF(3, gm_frame_sp + 84); R(0) = i2_rotl(R(23), 2) & 0xFFFFFFFCu;
                LF(1, gm_frame_sp + 88); R(4) = R(30) + R(0); LF(0, gm_frame_sp + 92);
                SF(gm_frame_sp + 136, ctx->f[1].d); LF(2, gm_frame_sp + 144);
                SF(gm_frame_sp + 140, ctx->f[0].d); LF(1, gm_frame_sp + 148);
                SF(gm_frame_sp + 132, ctx->f[3].d); LF(0, gm_frame_sp + 152);
                R(3) = gm_u32(R(4) + 2272); SF(R(3) + 172, ctx->f[3].d);
                LF(3, gm_frame_sp + 136); SF(R(3) + 176, ctx->f[3].d);
                LF(3, gm_frame_sp + 140); SF(R(3) + 180, ctx->f[3].d);
                R(3) = gm_u32(R(4) + 2272); SF(R(3) + 544, ctx->f[2].d);
                SF(R(3) + 548, ctx->f[1].d); SF(R(3) + 552, ctx->f[0].d);
                R(3) = gm_u32(R(4) + 2272); SF(R(3) + 604, ctx->f[30].d);
            }
            NV_R(21, R(21) + 1);
        }
        NV_R(22, R(22) + 1); NV_R(20, R(20) + 4); CMPS(R(22), 8);
        if ((int32_t)R(22) < 8) GM_LOOP(); else break;
    } while (1);

    LF(30, R(31) + 176); NV_R(20, R(30)); LF(31, R(31) + 252); NV_R(21, 0);
    do {
        NV_R(17, gm_u32(R(20) + 604)); R(3) = gm_frame_sp + 60; R(6) = gm_u32(R(20) + 672);
        R(4) = gm_frame_sp + 72; R(8) = gm_u32(R(17) + 144); gm_set_u32(gm_frame_sp + 276, R(8));
        R(7) = gm_u32(R(17) + 160); gm_set_u32(gm_frame_sp + 292, R(7));
        R(5) = gm_u32(R(6) + 68); R(0) = gm_u32(R(6) + 72); gm_set_u32(gm_frame_sp + 8, R(5));
        NV_R(16, gm_u32(R(17) + 132)); gm_set_u32(gm_frame_sp + 12, R(0));
        R(12) = gm_u32(R(17) + 136); R(11) = gm_u32(R(17) + 140);
        R(10) = gm_u32(R(17) + 148); R(9) = gm_u32(R(17) + 152); R(8) = gm_u32(R(17) + 156);
        R(7) = gm_u32(R(17) + 164); R(6) = gm_u32(R(17) + 168);
        R(5) = gm_u32(R(17) + 172); R(0) = gm_u32(R(17) + 176);
        LF(1, gm_frame_sp + 276); LF(0, gm_frame_sp + 292); LF(3, gm_frame_sp + 12); LF(2, gm_frame_sp + 8);
        gm_set_u32(gm_frame_sp + 264, R(16)); gm_set_u32(gm_frame_sp + 268, R(12));
        gm_set_u32(gm_frame_sp + 272, R(11)); gm_set_u32(gm_frame_sp + 280, R(10));
        gm_set_u32(gm_frame_sp + 284, R(9)); gm_set_u32(gm_frame_sp + 288, R(8));
        gm_set_u32(gm_frame_sp + 296, R(7)); gm_set_u32(gm_frame_sp + 300, R(6));
        gm_set_u32(gm_frame_sp + 304, R(5)); gm_set_u32(gm_frame_sp + 308, R(0));
        SF(gm_frame_sp + 120, ctx->f[2].d); SF(gm_frame_sp + 124, ctx->f[3].d);
        SF(gm_frame_sp + 128, ctx->f[30].d); SF(gm_frame_sp + 108, ctx->f[1].d);
        SF(gm_frame_sp + 112, ctx->f[0].d); SF(gm_frame_sp + 72, ctx->f[1].d);
        SF(gm_frame_sp + 76, ctx->f[0].d); SF(gm_frame_sp + 80, ctx->f[31].d);
        BL(0x8181F524u, CrapUpPositions__FP7Point3dPC7Point3d_800B32E0);
        LF(4, gm_frame_sp + 64); NV_R(21, R(21) + 1); LF(3, gm_frame_sp + 68);
        ctx->f[0].d = frsp(ctx->f[30].d); LF(5, gm_frame_sp + 60); CMPS(R(21), 7);
        R(3) = gm_u32(R(20) + 756); LF(2, gm_frame_sp + 120); SF(R(3) + 172, ctx->f[5].d);
        LF(1, gm_frame_sp + 124); SF(R(3) + 176, ctx->f[4].d); SF(R(3) + 180, ctx->f[3].d);
        R(3) = gm_u32(R(20) + 756); NV_R(20, R(20) + 4); SF(gm_frame_sp + 108, ctx->f[5].d);
        SF(R(3) + 500, ctx->f[2].d); SF(R(3) + 504, ctx->f[1].d);
        SF(gm_frame_sp + 112, ctx->f[4].d); SF(gm_frame_sp + 116, ctx->f[3].d);
        SF(gm_frame_sp + 48, ctx->f[5].d); SF(gm_frame_sp + 52, ctx->f[4].d);
        SF(gm_frame_sp + 56, ctx->f[3].d); SF(R(3) + 508, ctx->f[0].d);
        if ((int32_t)R(21) < 7) GM_LOOP(); else break;
    } while (1);

    R(3) = gm_u32(R(30) + 632); NV_R(17, gm_u32(R(30) + 636));
    NV_R(20, gm_u32(R(30) + 784)); LF(5, R(3) + 144); NV_R(16, gm_u32(R(20) + 520));
    LF(4, R(3) + 160); SF(R(16) + 44, ctx->f[5].d); LF(3, STOCK_CONST + 252);
    SF(R(16) + 48, ctx->f[4].d); SF(R(16) + 52, ctx->f[3].d);
    LF(2, R(17) + 132); LF(1, R(17) + 152); SF(R(16) + 68, ctx->f[2].d); SF(R(16) + 72, ctx->f[1].d);
    for (uint32_t i = 0; i < 7; i++) {
        NV_R(20, gm_u32(R(30) + 784)); NV_R(31, gm_u32(R(30) + 672 + 4 * i));
        NV_R(16, gm_u32(R(20) + 580 + 4 * i)); LF(0, R(31) + 68); SF(R(16) + 68, ctx->f[0].d);
        LF(0, R(31) + 72); SF(R(16) + 72, ctx->f[0].d);
    }
    R(11) = gm_frame_sp + 432; BL(0x8181F76Cu, __restore_gpr_entry_802DCD94);
}

static void stock_calc2DPlayerItemUpdate(GM_CTX, gptr self) {
    I2_FN(0x8181F77Cu);
    R(11) = gm_frame_sp + 112; BL(0x8181F790u, __save_gpr_entry_802DCD5C);
    R(0) = gm_u32(self + 2208); NV_R(23, self); NV_R(26, 0); CMPS(R(0), 6);
    if (R(0) == 6) {
        NV_R(22, STOCK_CREATE_ITEM); NV_R(27, STOCK_ACTIVE); NV_R(28, R(23)); NV_R(29, 0); NV_R(24, 1);
        do {
            R(0) = gm_u32(R(27)); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
            R(0) = gm_u32(R(22) + R(0)) & 1; CR0(ctx, R(0));
            if (R(0) == 0) {
                R(3) = R(23) + R(29); R(0) = gm_u8(R(3) + 2304); CMPS(R(0), 0);
                if (R(0) != 0) {
                    CMPS(R(26), 0); if (R(26) == 0) BL(0x8181F7F0u, fn_80101110);
                    NV_R(25, gm_u32(R(27))); R(0) = i2_rotl(R(25), 2) & 0xFFFFFFFCu;
                    gm_set_u32(R(22) + R(0), R(24)); NV_R(30, R(23) + R(0)); R(4) = gm_u32(R(30) + 2272);
                    R(3) = gm_u32(R(4) + 296); LF(0, R(4) + 180); R(3) = gm_u32(R(3) + 4);
                    LF(1, R(4) + 176); R(12) = gm_u32(R(3)); LF(2, R(4) + 172);
                    R(12) = gm_u32(R(12) + 64); SF(gm_frame_sp + 48, ctx->f[2].d);
                    SF(gm_frame_sp + 52, ctx->f[1].d); SF(gm_frame_sp + 56, ctx->f[0].d);
                    ctx->ctr = R(12); ctx->lr = 0x8181F834u; ppc_call_indirect(ctx, base, ctx->ctr);
                    R(3) = gm_u32(R(30) + 2272); R(3) = gm_u32(R(3) + 296); R(3) = gm_u32(R(3) + 4);
                    R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 72);
                    ctx->ctr = R(12); ctx->lr = 0x8181F850u; ppc_call_indirect(ctx, base, ctx->ctr);
                    NV_R(26, 1); CMPS(R(29), 4);
                    if ((int32_t)R(29) < 4) {
                        gm_set_u32(R(28) + 2192, R(25)); R(3) = R(23); LF(0, gm_frame_sp + 56);
                        R(6) = R(29); LF(1, gm_frame_sp + 52); R(5) = gm_frame_sp + 24;
                        LF(2, gm_frame_sp + 48); SF(gm_frame_sp + 24, ctx->f[2].d);
                        SF(gm_frame_sp + 28, ctx->f[1].d); SF(gm_frame_sp + 32, ctx->f[0].d);
                        R(4) = gm_u32(R(30) + 740); R(0) = gm_u32(R(4) + 4); R(4) = R(0) & 15;
                        BL(0x8181F894u, fn_2_42BC0_807B0370);
                    }
                }
            }
            NV_R(29, R(29) + 1); NV_R(28, R(28) + 4); CMPS(R(29), 8); NV_R(27, R(27) + 4);
            if ((int32_t)R(29) < 8) GM_LOOP(); else break;
        } while (1);
    } else {
        NV_R(28, STOCK_ACTIVE); NV_R(30, STOCK_CREATE_ITEM); NV_R(31, STOCK_PLAYER_MODE);
        NV_R(22, STOCK_MODE_TABLE); NV_R(25, gm_u32(self + 808)); NV_R(27, R(23)); NV_R(24, 0);
        do {
            NV_R(29, gm_u32(R(28))); R(3) = R(25); R(5) = gm_frame_sp + 8;
            NV_R(21, i2_rotl(R(29), 2) & 0xFFFFFFFCu); R(0) = gm_u32(R(30) + R(21));
            R(4) = gm_u32(R(31) + R(21)); R(0) &= 1; gm_set_u8(gm_frame_sp + 8, R(0));
            BL(0x8181F8FCu, fn_800FC850); R(0) = gm_u32(R(31) + R(21)); CMPS(R(3), R(0));
            if (R(3) != R(0)) {
                R(4) = R(23) + R(24); R(0) = gm_u8(R(4) + 2304); CMPS(R(0), 0);
                if (R(0) != 0) {
                    gm_set_u32(R(31) + R(21), R(3)); NV_R(21, R(23) + R(21));
                    R(0) = gm_u32(R(23) + 2208); R(3) = gm_u32(R(21) + 2272);
                    R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; R(4) = gm_u32(R(22) + R(0));
                    BL(0x8181F934u, fn_2_159650_808C6E00);
                    R(4) = gm_u32(R(21) + 2272); R(3) = R(23); R(6) = R(24); R(5) = gm_frame_sp + 12;
                    LF(0, R(4) + 180); NV_R(26, 1); LF(1, R(4) + 176); LF(2, R(4) + 172);
                    SF(gm_frame_sp + 36, ctx->f[2].d); CMPS(R(24), 4);
                    if ((int32_t)R(24) < 4) {
                        gm_set_u32(R(27) + 2192, R(29)); SF(gm_frame_sp + 12, ctx->f[2].d);
                        SF(gm_frame_sp + 16, ctx->f[1].d); SF(gm_frame_sp + 20, ctx->f[0].d);
                        R(4) = gm_u32(R(21) + 2272); SF(gm_frame_sp + 40, ctx->f[1].d);
                        R(0) = gm_u32(R(4) + 4); SF(gm_frame_sp + 44, ctx->f[0].d); R(4) = R(0) & 15;
                        BL(0x8181F988u, fn_2_42BC0_807B0370);
                    }
                }
            }
            NV_R(24, R(24) + 1); NV_R(27, R(27) + 4); CMPS(R(24), 8); NV_R(28, R(28) + 4);
            if ((int32_t)R(24) < 8) GM_LOOP(); else break;
        } while (1);
    }
    CMPS(R(26), 0);
    if (R(26) != 0) {
        R(4) = gm_u32(R(23) + 2208); R(3) = gm_u32(STOCK_INFO); BL(0x8181F9B4u, fn_800BB330);
        R(0) = gm_u32(R(23) + 2208); R(3) = R(23); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
        R(5) = R(23) + R(0); R(4) = gm_u32(R(5) + 2228); R(0) = R(4) - 1; gm_set_u32(R(5) + 2228, R(0));
        R(5) = gm_u32(R(23) + 2208); R(0) = i2_rotl(R(5), 2) & 0xFFFFFFFCu;
        R(4) = R(23) + R(0); R(4) = gm_u32(R(4) + 2228); BL(0x8181F9E4u, fn_2_42BA0_807B0350);
        R(0) = gm_u32(R(23) + 2208); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; R(3) = R(23) + R(0);
        R(0) = gm_u32(R(3) + 2228); CMPS(R(0), 0);
        if (R(0) == 0) { R(3) = gm_u32(R(3) + 756); R(0) = 1; gm_set_u32(R(3) + 516, R(0)); }
    }
    R(11) = gm_frame_sp + 112; BL(0x8181FA10u, __restore_gpr_entry_802DCDA8);
}

static void stock_calcUseEffects(GM_CTX, gptr self) {
    I2_FN(0x8181FA20u); LF(31, 0x80930000u + 23008);
    NV_R(30, self + 812); NV_R(29, 0); NV_R(28, self); NV_R(31, R(28));
    do {
        R(0) = gm_u32(R(31) + 2192); CMPS(R(0), 4);
        if (R(0) != 4) {
            R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu; R(3) = R(30); R(5) = R(28) + R(0);
            R(4) = gm_frame_sp + 8; R(7) = gm_u32(R(5) + 2272); R(5) = 0; R(6) = 0;
            LF(0, R(7) + 176); LF(1, R(7) + 180); LF(2, R(7) + 172);
            ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[31].d);
            SF(gm_frame_sp + 8, ctx->f[2].d); SF(gm_frame_sp + 16, ctx->f[1].d); SF(gm_frame_sp + 12, ctx->f[0].d);
            R(12) = gm_u32(R(30)); R(12) = gm_u32(R(12) + 176);
            ctx->ctr = R(12); ctx->lr = 0x8181FAB0u; ppc_call_indirect(ctx, base, ctx->ctr);
        }
        NV_R(29, R(29) + 1); NV_R(30, R(30) + 276); CMPS(R(29), 4); NV_R(31, R(31) + 4);
        if ((int32_t)R(29) < 4) GM_LOOP(); else break;
    } while (1);
}

static uint32_t stock_checkItemSelect(GM_CTX, gptr self) {
    I2_FN(0x8181FB40u);
    R(11) = gm_frame_sp + 48; BL(0x8181FB54u, __save_gpr_entry_802DCD6C);
    R(5) = gm_u32(self + 2208); R(4) = STOCK_ITEM_TABLE; NV_R(25, self);
    R(0) = i2_rotl(R(5), 2) & 0xFFFFFFFCu; CMPS(R(5), 6); NV_R(27, gm_u32(R(4) + R(0)));
    gm_set_u32(self + 808, R(27));
    if (R(5) == 6) {
        R(0) = gm_u8(self + 2304); R(7) = 0; CMPS(R(0), 0);
        if (R(0) != 0) {
            R(0) = gm_u32(STOCK_ACTIVE); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
            R(0) = gm_u32(STOCK_PLAYER_MODE + R(0)); CMPS(R(0), 3); if (R(0) == 3) R(7) = 1;
        }
        NV_R(30, STOCK_CREATE_ITEM); NV_R(29, STOCK_ACTIVE); R(8) = 0; ctx->ctr = 8;
        do {
            R(0) = gm_u32(R(29)); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
            R(0) = gm_u32(R(30) + R(0)) & 1; CR0(ctx, R(0));
            if (R(0) == 0) {
                R(4) = self + R(8); R(0) = gm_u8(R(4) + 2304); CMPS(R(0), 0);
                if (R(0) != 0) {
                    CMPS(R(7), 0); R(3) = gm_u32(R(29)); R(4) = R(7) != 0;
                    BL(R(7) ? 0x8181FC00u : 0x8181FC10u, mfn_8181FAF0);
                    R(3) = 1; goto out;
                }
            }
            NV_R(29, R(29) + 4); R(8)++;
            if (--ctx->ctr) GM_LOOP(); else break;
        } while (1);
    } else {
        NV_R(29, STOCK_ACTIVE); NV_R(30, STOCK_CREATE_ITEM); NV_R(31, STOCK_PLAYER_MODE); NV_R(26, 0);
        do {
            R(0) = gm_u32(R(29)); R(3) = R(27); R(5) = gm_frame_sp + 8;
            NV_R(28, i2_rotl(R(0), 2) & 0xFFFFFFFCu); R(0) = gm_u32(R(30) + R(28));
            R(4) = gm_u32(R(31) + R(28)); R(0) &= 1; gm_set_u8(gm_frame_sp + 8, R(0));
            BL(0x8181FC68u, fn_800FC850); R(0) = gm_u32(R(31) + R(28)); CMPS(R(3), R(0));
            if (R(3) != R(0)) {
                R(3) = R(25) + R(26); R(0) = gm_u8(R(3) + 2304); CMPS(R(0), 0);
                if (R(0) != 0) {
                    R(0) = gm_u32(R(25) + 808); R(4) = 1641; CMPU(R(0), 1);
                    if (R(0) > 1 && R(0) != 3) {
                        if (R(0) == 2) R(4) = 1642;
                        else if (R(0) == 4) R(4) = 1643;
                        else if (R(0) == 5) R(4) = 1644;
                        else R(4) = 0;
                    }
                    if (R(4) != 0) {
                        R(3) = gm_u32(STOCK_SOUND_MANAGER); R(5) = 1;
                        BL(R(4) == 1641 ? 0x8181FCC8u : R(4) == 1642 ? 0x8181FCE0u :
                           R(4) == 1643 ? 0x8181FCF8u : 0x8181FD10u, hle_startSystemSe__11SndAudioMgrFUiUl);
                    }
                    R(3) = 1; goto out;
                }
            }
            NV_R(26, R(26) + 1); NV_R(29, R(29) + 4); CMPS(R(26), 8);
            if ((int32_t)R(26) < 8) GM_LOOP(); else break;
        } while (1);
    }
    R(3) = 0;
out:
    R(11) = gm_frame_sp + 48; BL(0x8181FD34u, __restore_gpr_entry_802DCDB8); return R(3);
}

static void stock_windowOpenInit(GM_CTX, gptr self) {
    I2_FN(0x8181FD44u);
    R(11) = gm_frame_sp + 32; BL(0x8181FD58u, __save_gpr_entry_802DCD74);
    NV_R(31, self); BL(0x8181FD60u, hle_getMesRes__10dMessage_cFv);
    R(3) = gm_u32(STOCK_INFO); NV_R(28, STOCK_ACTIVE); NV_R(29, 1); NV_R(30, 0);
    gm_set_u8(R(3) + 2812, R(29)); NV_R(27, 0); gm_set_u32(R(31) + 2224, R(30));
    do {
        R(3) = R(27); BL(0x8181FD8Cu, hle_mod_PlayerEnterCheck__8dGameComFi); CMPS(R(3), 0);
        R(3) = R(31) + R(27);
        if (CR_BIT(ctx, 2)) gm_set_u8(R(3) + 2304, R(30));
        else {
            gm_set_u8(R(3) + 2304, R(29)); R(0) = gm_u32(R(28)); R(0) = i2_rotl(R(0), 2) & 0xFFFFFFFCu;
            R(4) = R(31) + R(0); R(3) = gm_u32(R(4) + 2272); gm_set_u8(R(3) + 609, R(29));
            R(3) = gm_u32(R(4) + 2272); gm_set_u8(R(3) + 615, R(29));
            R(3) = gm_u32(R(31) + 2224); R(0) = R(3) + 1; gm_set_u32(R(31) + 2224, R(0));
        }
        NV_R(27, R(27) + 1); NV_R(28, R(28) + 4); CMPS(R(27), 8);
        if ((int32_t)R(27) < 8) GM_LOOP(); else break;
    } while (1);
    NV_R(29, R(31)); NV_R(27, 0);
    do {
        R(4) = gm_u32(R(29) + 2228); R(3) = R(31); R(5) = R(27); BL(0x8181FDF8u, fn_2_42BA0_807B0350);
        NV_R(27, R(27) + 1); NV_R(29, R(29) + 4); CMPS(R(27), 7);
        if ((int32_t)R(27) < 7) GM_LOOP(); else break;
    } while (1);
    R(12) = gm_u32(R(31) + 524); R(4) = STOCK_OPEN_WAIT; R(3) = R(31) + 524;
    R(12) = gm_u32(R(12) + 24); ctx->ctr = R(12); ctx->lr = 0x8181FE24u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(11) = gm_frame_sp + 32; BL(0x8181FE2Cu, __restore_gpr_entry_802DCDC0);
}

static void stock_windowCloseFinalize(GM_CTX, gptr self) {
    I2_FN(0x8181FE3Cu);
    NV_R(30, self); R(3) = self + 2272; R(4) = self + 2303; R(6) = STOCK_ACTIVE - 4;
    R(5) = 1; ctx->ctr = 8;
    do {
        R(4)++; R(7) = gm_u8(R(4)); CMPU(R(7), 0); R(7) = R(6) + 4;
        if (!CR_BIT(ctx, 2)) {
            R(6) = gm_u32(R(6) + 4); R(6) = i2_rotl(R(6), 2) & 0xFFFFFFFCu;
            R(6) = gm_u32(R(3) + R(6)); gm_set_u8(R(6) + 617, R(5));
        }
        R(6) = R(7); if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    NV_R(29, R(30) + 752); NV_R(28, 7); NV_R(27, 0);
    do {
        R(29) += 4; R(3) = gm_u32(R(29)); gm_set_u8(R(3) + 521, R(27)); BL(0x8181FEBCu, fn_2_1677A0_808D4F50);
        NV_R(28, R(28) - 1); CMPU(R(28), 0); if (R(28)) GM_LOOP(); else break;
    } while (1);
    R(3) = gm_u32(R(30) + 784); R(4) = 0; gm_set_u8(R(3) + 609, R(4));
    R(3) = gm_u32(STOCK_SOUND_GLOBAL); BL(0x8181FEE0u, hle_fn_8019CC70);
}

GM_HLE_VERIFIED_(mod_fn_2_41BD0, GMV_IGNORE_POLLS, 0, 0) { R(3) = stock_classInit(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_2_42130, GMV_IGNORE_POLLS, 0, 0) { R(3) = stock_createLayout(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_getIconPictureIDforPlayer__12dStockItem_cFi, GMV_IGNORE_POLLS, 0, 0) { R(3) = stock_getPosPane(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_2_42420, GMV_IGNORE_POLLS, 0, 0) { stock_calcPosScale(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_42900, GMV_IGNORE_POLLS, 0, 0) { stock_calc2DPlayerItemUpdate(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_42C00, GMV_IGNORE_POLLS, 0, 0) { stock_calcUseEffects(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_42F20, GMV_IGNORE_POLLS, 0, 0) { R(3) = stock_checkItemSelect(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_43230, GMV_IGNORE_POLLS, 0, 0) { stock_windowOpenInit(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_43C20, GMV_IGNORE_POLLS, 0, 0) { stock_windowCloseFinalize(GM_PASS, GM_ARG(0)); }
