/* gm_d_sc_wmap.c - dScWMap_c's module replacements: world-map layout and actor creation,
 * boot parameters and restoration of saved course state (track B, gm_i2.h, docs/DECOMP.md). */
#include "gm_i2.h"
RT_STATE_FILE

#define WMAP_MODE          (0x81860000u - 4864)
#define WMAP_SAVE_MANAGER  (0x80430000u - 24512)
#define WMAP_INFO          (0x80430000u - 24708)
#define WMAP_LAYOUT        (0x809A0000u + 9112)
#define WMAP_STACK_GUARD   (0x81860000u - 300)

static void wmap_parent(GM_CTX, uint32_t profile, gptr self, uint32_t ra) {
    R(3) = profile; R(4) = self; R(5) = 0; R(6) = 0;
    BL(ra, hle__Z20CreateParentedObjectsPvic);
}

static void wmap_parent_indexed(GM_CTX, uint32_t profile, gptr self, uint32_t index, uint32_t ra) {
    R(3) = profile; R(4) = self; R(5) = index; R(6) = 0;
    BL(ra, hle__Z20CreateParentedObjectsPvic);
}

static void wmap_actor(GM_CTX, uint32_t profile, gptr self, uint32_t ra) {
    R(3) = profile; R(4) = self; R(5) = 0; R(6) = 0; R(7) = 0;
    BL(ra, hle_fn_800F2A00);
}

static void wmap_child(GM_CTX, uint32_t profile, gptr self, uint32_t index, uint32_t ra) {
    R(3) = profile; R(4) = self; R(5) = index; R(6) = 0; R(7) = 0;
    BL(ra, hle__Z17CreateChildObjectsPviii);
}

static uint32_t wmap_createLayoutPhase(GM_CTX, gptr self) {
    I2_FN(0x818157F4u);
    NV_R(30, self); R(4) = gm_u32(WMAP_MODE);
    cr_cmp_s(ctx, 2, (int32_t)R(4), 6); cr_cmp_s(ctx, 3, (int32_t)R(4), 8);
    int atLeast6 = (int32_t)R(4) >= 6, atLeast8 = (int32_t)R(4) >= 8;

    R(3) = atLeast6 ? 721 : 719; if (atLeast8) R(3) = 723;
    wmap_parent(GM_PASS, R(3), self, 0x81815860u); R(4) = R(3); gm_set_u32(self + 124, R(4));
    R(3) = atLeast6 ? 707 : 705; if (atLeast8) R(3) = 709;
    wmap_parent(GM_PASS, R(3), self, 0x8181588Cu); NV_R(29, R(3));
    R(3) = atLeast8 ? 691 : 689; wmap_parent(GM_PASS, R(3), self, 0x818158B0u);
    gm_set_u32(R(29) + 192, R(3));
    R(3) = atLeast8 ? 692 : 690; wmap_parent(GM_PASS, R(3), self, 0x818158D4u);
    R(4) = gm_u32(R(29) + 192); gm_set_u32(R(29) + 196, R(3)); gm_set_u32(R(4) + 620, R(3));
    R(3) = atLeast8 ? 694 : 692; wmap_parent(GM_PASS, R(3), self, 0x818158FCu);
    NV_R(28, R(3)); gm_set_u32(R(29) + 188, R(3));
    R(3) = atLeast8 ? 693 : 691; NV_R(27, R(3)); wmap_parent(GM_PASS, R(3), self, 0x81815920u);
    gm_set_u32(R(28) + 116, R(3));
    R(3) = R(27); wmap_parent(GM_PASS, R(3), self, 0x81815938u);
    NV_R(26, R(28) + 120); gm_set_u32(R(26), R(3));
    NV_R(27, atLeast6 ? 742 : 740); if (atLeast8) NV_R(27, 744); NV_R(25, 24);
    do {
        wmap_parent(GM_PASS, R(27), self, 0x8181596Cu);
        R(25)--; CMPU(R(25), 0); R(26) += 4; gm_set_u32(R(26), R(3));
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
    R(3) = atLeast6 ? 734 : 732; if (atLeast8) R(3) = 736;
    wmap_parent(GM_PASS, R(3), self, 0x818159A0u); R(4) = R(3); gm_set_u32(R(28) + 220, R(4));
    R(3) = atLeast8 ? 695 : 693; wmap_parent(GM_PASS, R(3), self, 0x818159C4u);
    R(4) = R(3); gm_set_u32(R(29) + 172, R(4));
    R(3) = atLeast8 ? 696 : 694; wmap_parent(GM_PASS, R(3), self, 0x818159E8u);
    R(4) = R(3); gm_set_u32(R(29) + 176, R(4)); R(4) = gm_u32(R(3) + 1808);
    CMPU(R(4), 0);
    if (!CR_BIT(ctx, 2)) {
        uint32_t first, second, third, fourth;
        if (!atLeast6) {
            first = 735; second = 736; third = 737; fourth = 738;
        } else if (!atLeast8) {
            first = 737; second = 736; third = 737; fourth = 738;
        } else {
            first = 739; second = 740; third = 741; fourth = 742;
        }
        NV_R(27, first); NV_R(25, second); NV_R(28, third); NV_R(26, fourth);
        NV_R(23, 0); NV_R(24, 0);
        do {
            wmap_parent_indexed(GM_PASS, R(27), self, R(24), 0x81815A50u);
            R(4) = gm_u32(R(29) + 176) + R(23); gm_set_u32(R(4) + 1812, R(3));
            wmap_parent_indexed(GM_PASS, R(25), self, R(24), 0x81815A70u);
            R(4) = gm_u32(R(29) + 176) + R(23); gm_set_u32(R(4) + 1844, R(3));
            wmap_parent_indexed(GM_PASS, R(28), self, R(24), 0x81815A90u);
            R(4) = gm_u32(R(29) + 176) + R(23); gm_set_u32(R(4) + 1876, R(3));
            wmap_parent_indexed(GM_PASS, R(26), self, R(24), 0x81815AB0u);
            R(4) = gm_u32(R(29) + 176) + R(23); R(24)++; gm_set_u32(R(4) + 1908, R(3));
            R(23) += 4; R(3) = gm_u32(gm_u32(R(29) + 176) + 1808); CMPU(R(24), R(3));
            if (CR_BIT(ctx, 0)) GM_LOOP(); else break;
        } while (1);
    }
    NV_R(28, 697); R(3) = atLeast8 ? 697 : 695; wmap_parent(GM_PASS, R(3), self, 0x81815AF4u);
    R(4) = R(3); gm_set_u32(R(29) + 180, R(4));
    R(3) = atLeast8 ? 698 : 696; wmap_parent(GM_PASS, R(3), self, 0x81815B18u);
    R(4) = gm_u32(R(29) + 180); gm_set_u32(R(29) + 184, R(3)); gm_set_u32(R(4) + 784, R(3));
    if (atLeast8) NV_R(28, 699); wmap_parent(GM_PASS, R(28), self, 0x81815B40u);
    R(4) = R(3); gm_set_u32(R(29) + 1320, R(4));
    R(3) = atLeast6 ? 728 : 726; if (atLeast8) R(3) = 730;
    wmap_parent(GM_PASS, R(3), self, 0x81815B6Cu); R(4) = R(3); gm_set_u32(R(29) + 1324, R(4));
    R(3) = atLeast6 ? 706 : 704; if (atLeast8) R(3) = 708;
    wmap_parent(GM_PASS, R(3), self, 0x81815B98u); R(4) = R(3); gm_set_u32(R(29) + 1328, R(4));
    R(3) = atLeast6 ? 736 : 734; if (atLeast8) R(3) = 738;
    wmap_parent(GM_PASS, R(3), self, 0x81815BC4u); R(4) = R(3); gm_set_u32(R(29) + 1332, R(4));
    R(3) = atLeast6 ? 748 : 746; if (atLeast8) R(3) = 750;
    wmap_parent(GM_PASS, R(3), self, 0x81815BF0u); R(4) = R(3); gm_set_u32(R(29) + 1336, R(4));
    R(3) = 1; return R(3);
}

static uint32_t wmap_createActorsPhase(GM_CTX, gptr self) {
    I2_FN(0x81815C64u);
    NV_R(30, self); R(3) = gm_u32(WMAP_MODE); cr_cmp_s(ctx, 2, (int32_t)R(3), 8);
    int atLeast8 = (int32_t)R(3) >= 8;
    R(3) = atLeast8 ? 625 : 623; NV_R(29, 0); wmap_actor(GM_PASS, R(3), self, 0x81815CD0u);
    NV_R(28, gm_u32(0x80430000u - 24180)); R(3) = R(28); BL(0x81815CE0u, mfn_81828888);
    R(3) = atLeast8 ? 623 : 621; wmap_actor(GM_PASS, R(3), self, 0x81815D00u);
    R(3) = atLeast8 ? 662 : 660; wmap_actor(GM_PASS, R(3), self, 0x81815D20u);
    R(3) = atLeast8 ? 624 : 622; wmap_actor(GM_PASS, R(3), self, 0x81815D40u);
    R(3) = R(28); BL(0x81815D48u, fn_2_173FB0_808E1760);
    R(3) = R(28); BL(0x81815D50u, fn_2_1726B0_808DFE60); BL(0x81815D54u, fn_2_170A00_808DE1B0);
    NV_R(27, gm_u32(WMAP_LAYOUT)); NV_R(28, atLeast8 ? 700 : 698);
    R(3) = gm_u32(R(27) + 176); NV_R(26, gm_u32(R(27) + 180));
    NV_R(25, R(27) + 1392); NV_R(24, R(3) + 1940); NV_R(23, R(26) + 2272); NV_R(22, R(26) + 740);
    int haveFirst = R(3) != 0, haveSecond = R(26) != 0;
    cr_cmp_u(ctx, 3, R(3), 0); cr_cmp_u(ctx, 4, R(26), 0);
    do {
        wmap_child(GM_PASS, R(28), self, R(29), 0x81815DA0u);
        R(4) = i2_rotl(R(29), 2) & 0xFFFFFFFCu; R(5) = R(25) + R(4); gm_set_u32(R(5), R(3));
        if (haveFirst) gm_set_u32(R(24) + R(4), R(3));
        if (haveSecond) {
            R(3) = gm_u32(R(5)); CMPU(R(29), 3); gm_set_u32(R(23) + R(4), R(3));
            if (!CR_BIT(ctx, 1)) gm_set_u32(R(22) + R(4), R(3));
        }
        R(29)++; CMPU(R(29), 8); if (!CR_BIT(ctx, 2)) GM_LOOP(); else break;
    } while (1);
    if (haveSecond) {
        NV_R(29, atLeast8 ? 669 : 667); R(26) += 752; NV_R(25, 7); NV_R(28, 0);
        do {
            wmap_child(GM_PASS, R(29), self, R(28), 0x81815E1Cu);
            R(25)--; R(26) += 4; gm_set_u32(R(26), R(3)); CMPU(R(25), 0); R(28)++;
            if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
        } while (1);
    }
    R(3) = gm_u32(R(27) + 192); CMPU(R(3), 0);
    if (!CR_BIT(ctx, 2)) {
        NV_R(29, atLeast8 ? 668 : 666); NV_R(27, R(3) + 580); NV_R(26, 9); NV_R(28, 0);
        do {
            wmap_child(GM_PASS, R(29), self, R(28), 0x81815E6Cu);
            R(26)--; R(27) += 4; gm_set_u32(R(27), R(3)); CMPU(R(26), 0); R(28)++;
            if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
        } while (1);
    }
    R(3) = 1; return R(3);
}

static void wmap_createBootParam(GM_CTX) {
    I2_FN(0x81815FE8u);
    R(4) = gm_u32(WMAP_INFO); R(5) = 5; R(3) = gm_u8(R(4) + 63); R(4) = gm_u8(R(4) + 67);
    BL(0x8181600Cu, fn_80102A60);
}

static void wmap_initLoadGame(GM_CTX) {
    I2_FN(0x8181601Cu);
    R(4) = (uint32_t)-1; NV_R(28, (uint32_t)-1);
    R(3) = gm_u32(WMAP_STACK_GUARD); gm_set_u32(gm_frame_sp + 36, R(3));
    R(3) = gm_u32(WMAP_SAVE_MANAGER); BL(0x8181606Cu, hle_mod_getSaveGame__10dSaveMng_cFSc); NV_R(30, R(3));
    NV_R(29, gm_u32(WMAP_INFO)); R(3) = gm_u8(R(30) + 3); R(4) = gm_u8(R(30) + 4);
    gm_set_u32(R(29) + 60, R(3)); R(3) = gm_u8(R(30) + 5); gm_set_u32(R(29) + 64, R(4));
    gm_set_u32(R(29) + 68, R(3)); R(3) = R(30); gm_set_u32(R(29) + 72, R(28)); BL(0x8181609Cu, hle_mod_fn_800CE560);
    R(5) = R(3); R(3) = R(29); R(4) = 4; BL(0x818160ACu, fn_800BBC50);
    R(3) = R(30); BL(0x818160B4u, hle_mod_fn_800CE560); R(5) = R(3); R(3) = R(29); R(4) = 4; BL(0x818160C4u, fn_800BBC60);
    R(3) = gm_u8(R(30) + 7); NV_R(28, 0); NV_R(27, gm_frame_sp + 20); NV_R(24, 42); gm_set_u8(R(29) + 896, R(3));
    do {
        NV_R(23, R(29) + R(28)); NV_R(26, R(28) & 0xFF); NV_R(25, 0); NV_R(22, 4);
        do {
            R(3) = R(30); R(4) = R(26); R(5) = R(25); BL(0x818160F8u, hle_mod_fn_800CE490); gm_set_u32(gm_frame_sp + 20, R(3));
            R(3) = R(30); R(4) = R(26); R(5) = R(25); BL(0x8181610Cu, hle_mod_fn_800CE4D0); gm_set_u32(gm_frame_sp + 24, R(3));
            R(3) = R(30); R(4) = R(26); R(5) = R(25); BL(0x81816120u, hle_mod_fn_800CE510); gm_set_u32(gm_frame_sp + 28, R(3));
            R(3) = R(30); R(4) = R(26); R(5) = R(25); BL(0x81816134u, hle_mod_fn_800CE450); gm_set_u8(gm_frame_sp + 32, R(3));
            R(3) = R(29); R(4) = R(28); R(5) = R(25); R(6) = R(27); BL(0x8181614Cu, fn_800BBB70);
            R(3) = R(30); R(4) = R(26); BL(0x81816158u, hle_mod_fn_800CE540); gm_set_u8(R(23) + 917, R(3));
            R(3) ^= 42; R(22)--; R(3) = cntlzw(R(3)); CMPU(R(22), 0); R(3) = i2_rotl(R(3), 27) & 0x7FFFFFFu;
            R(25)++; gm_set_u8(R(23) + 927, R(24)); gm_set_u8(R(23) + 937, R(3));
            if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
        } while (1);
        R(28)++; CMPU(R(28), 10); if (!CR_BIT(ctx, 2)) GM_LOOP(); else break;
    } while (1);
    R(3) = 0x80430000u; R(4) = 0; gm_set_u8(0x80430000u - 23976, R(4)); BL(0x8181619Cu, fn_800FCDB0);
    R(3) = gm_u32(WMAP_STACK_GUARD); R(4) = gm_u32(gm_frame_sp + 36);
    if (CMPU(R(3), R(4)) != 0) BL(0x818161E8u, mfn_81844FCC);
}

GM_HLE_VERIFIED_(mod_fn_2_1B9670, GMV_IGNORE_POLLS, 0, 0) { R(3) = wmap_createLayoutPhase(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_2_1B9A20, GMV_IGNORE_POLLS, 0, 0) { R(3) = wmap_createActorsPhase(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_80102A40, GMV_IGNORE_POLLS, 0, 0) { wmap_createBootParam(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_80102A80, GMV_IGNORE_POLLS, 0, 0) { wmap_initLoadGame(GM_PASS); }
