/* gm_d_course_guide.c - dCourseSelectGuide_c: eight-player course-select icons,
 * remaining-life numbers and alpha (track B, gm_i2.h).
 * Layout objects and panes remain in big-endian guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define CSG_VT          (0x81850000u + 7228)
#define CSG_GLOBAL      (0x80430000u - 25604)
#define CSG_ACTIVE      (0x81860000u - 5828)
#define CSG_FRAME       (0x81860000u - 300)
#define CSG_PANE_NAMES  (0x81850000u + 7240)
#define CSG_PIC_NAMES   (0x81850000u + 7256)
#define CSG_TEXT_NAMES  (0x81850000u + 7272)
#define CSG_REST_VALUES (0x81850000u + 7564)

static void csg_playerIconDisp(GM_CTX, gptr self);

static gptr csg_destruct(GM_CTX, gptr self, int32_t flags) {
    I2_FN(0x81800564u);
    NV_R(30, self); R(3) = gm_u32(self + 1104); NV_R(29, flags);
    R(4) = CSG_VT; NV_R(28, 0); gm_set_u32(self, CSG_VT);
    CMPU(R(3), 0); gm_set_u32(CSG_GLOBAL, 0);
    if (R(3)) {
        R(4) = 48; BL(0x818005B0u, mfn_818434F4); gm_set_u32(self + 1104, 0);
    }
    R(3) = self + 8; R(4) = (uint32_t)-1; BL(0x818005C0u, hle___dt__Q23m2d13EmbedLayout_cFv);
    CMPS(flags, 1);
    if (flags >= 1) { R(3) = self; R(4) = 1120; BL(0x818005D4u, mfn_818434F4); }
    R(3) = self; return R(3);
}

static uint32_t csg_createLayout(GM_CTX, gptr self) {
    I2_FN(0x818005F4u);
    NV_R(30, self); gm_set_u32(self + 1104, 0);
    R(3) = self; BL(0x81800620u, ext_fn_80010290_818453F8);
    uint32_t result = R(3); NV_R(29, result); CMPU(R(3), 0);
    if (result) {
        R(3) = 48; BL(0x81800634u, mod___nw__FUl_818432E4);
        R(5) = R(3); NV_R(28, self + 8); gm_set_u32(self + 1104, R(3));
        R(4) = CSG_PANE_NAMES; R(3) = R(28); R(6) = 4;
        BL(0x81800654u, hle_getPanes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt4Panei);
        R(3) = gm_u32(self + 1104); R(6) = 4; R(5) = R(3) + 32; R(4) = CSG_PIC_NAMES; R(3) = R(28);
        BL(0x81800670u, hle_getPictures__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7Picturei);
        R(3) = gm_u32(self + 1104); R(6) = 4; R(5) = R(3) + 16; R(4) = CSG_TEXT_NAMES; R(3) = R(28);
        BL(0x8180068Cu, hle_getTextBoxes__Q23m2d13EmbedLayout_cCFPPCcPPQ34nw4r3lyt7TextBoxi);
        R(3) = self; BL(0x81800694u, hle_mod_fn_80010690);
        R(3) = self; BL(0x8180069Cu, hle_mod_fn_80010800);
    }
    R(3) = result; return R(3);
}

static void csg_playerIconDisp(GM_CTX, gptr self) {
    I2_FN(0x818006BCu);
    NV_R(30, self); R(3) = gm_u32(self + 1104); CMPU(R(3), 0);
    if (!R(3)) return;
    NV_R(26, self + 1008); NV_R(27, 0); NV_R(29, 0);
    R(3) = gm_u32(R(26)); NV_R(28, R(26) - 108);
    R(4) = gm_u8(R(3) + 187) & 0xFE; gm_set_u8(R(3) + 187, R(4));
    R(3) = gm_u32(R(26) + 4); R(4) = gm_u8(R(3) + 187) & 0xFE; gm_set_u8(R(3) + 187, R(4));
    R(3) = gm_u32(R(26) + 12); R(4) = gm_u8(R(3) + 187) & 0xFE; gm_set_u8(R(3) + 187, R(4));
    R(3) = gm_u32(R(26) + 8); R(4) = gm_u8(R(3) + 187) & 0xFE; gm_set_u8(R(3) + 187, R(4));
    R(3) = gm_u32(R(26) + 96);
    R(4) = gm_u32(R(3) + 32); R(5) = gm_u8(R(4) + 187) & 0xFE; gm_set_u8(R(4) + 187, R(5));
    R(4) = gm_u32(R(3) + 36); R(5) = gm_u8(R(4) + 187) & 0xFE; gm_set_u8(R(4) + 187, R(5));
    R(4) = gm_u32(R(3) + 40); R(5) = gm_u8(R(4) + 187) & 0xFE; gm_set_u8(R(4) + 187, R(5));
    R(3) = gm_u32(R(3) + 44); R(5) = gm_u8(R(3) + 187) & 0xFE; gm_set_u8(R(3) + 187, R(5));
    NV_R(24, CSG_ACTIVE - 4);

    for (;;) {
        R(3) = R(29); NV_R(25, R(24) + 4); BL(0x818007A0u, hle_mod_PlayerEnterCheck__8dGameComFi);
        CMPU(R(3), 0);
        if (R(3)) {
            R(3) = gm_u32(R(24) + 4); CMPU(R(3), 7);
            if (R(3) <= 7) {
                R(5) = gm_u32(self + 1104); CMPU(R(3), 4); R(4) = R(26);
                if (R(3) >= 4) R(4) = R(5) + 16;
                CMPU(R(27), 4); R(6) = i2_rotl(R(27), 2) & 0xFFFFFFFCu;
                if (R(27) >= 4) R(5) = R(5) + R(6) - 16;
                else R(5) = R(28) + R(6);
                R(5) = gm_u32(R(5)); R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(3) = gm_u32(R(4) + R(3));
                NV_R(27, R(27) + 1);
                R(4) = gm_u32(R(5) + 52); R(6) = gm_u8(R(3) + 187); gm_set_u32(R(3) + 52, R(4));
                R(4) = gm_u32(R(5) + 48); gm_set_u32(R(3) + 48, R(4));
                R(4) = gm_u32(R(5) + 44); R(5) = R(6) | 1;
                gm_set_u8(R(3) + 187, R(5)); gm_set_u32(R(3) + 44, R(4));
            }
        }
        CMPU(R(29), 6);
        if (R(29) > 6) break;
        CMPU(R(27), 8); NV_R(29, R(29) + 1); NV_R(24, R(25));
        if (R(27) < 8) GM_LOOP(); else break;
    }

    R(3) = self + 896; ctx->ctr = 4;
    do {
        R(4) = gm_u32(R(3) + 4); R(3) += 4; R(5) = gm_u8(R(4) + 187) & 0xFE;
        gm_set_u8(R(4) + 187, R(5));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    ctx->ctr = 4; R(3) = 0;
    do {
        R(4) = gm_u32(gm_u32(self + 1104) + R(3)); R(3) += 4;
        R(5) = gm_u8(R(4) + 187) & 0xFE; gm_set_u8(R(4) + 187, R(5));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);

    CMPU(R(27), 0);
    if (R(27)) {
        CMPU(R(27), 5); R(3) = R(27) - 1;
        if (R(27) >= 5) R(3) = R(27) - 5;
        if (R(27) >= 5) NV_R(28, gm_u32(self + 1104));
        R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(3) = gm_u32(R(28) + R(3));
        R(4) = gm_u8(R(3) + 187) | 1; gm_set_u8(R(3) + 187, R(4));
    }
}

static void csg_restNumberDisp(GM_CTX, gptr self) {
    I2_FN(0x818008D8u);
    NV_R(27, 0x81860000u); NV_R(30, self);
    R(4) = gm_u32(CSG_FRAME); gm_set_u32(gm_frame_sp + 28, R(4));
    R(3) = gm_u32(self + 1104); CMPU(R(3), 0);
    if (R(3)) {
        R(3) = CSG_REST_VALUES; NV_R(26, self + 956); NV_R(25, self + 1042);
        NV_R(24, 8); NV_R(23, 0); NV_R(22, 2); NV_R(29, gm_frame_sp + 24);
        NV_R(28, gm_frame_sp + 20); NV_R(21, R(3) - 4); NV_R(20, 0);
        do {
            R(3) = gm_u32(R(21) + 4); NV_R(21, R(21) + 4);
            R(5) = (uint32_t)(int16_t)gm_u16(R(25) + 2); NV_R(25, R(25) + 2);
            R(4) = (uint32_t)(int16_t)R(3); CMPU(R(4), R(5));
            if (R(4) != R(5)) {
                gm_set_u16(R(25), R(3)); CMPU(R(20), 4); R(3) = R(26);
                gm_set_u32(gm_frame_sp + 24, R(4)); gm_set_u32(gm_frame_sp + 20, R(22));
                if (R(20) >= 4) R(3) = gm_u32(self + 1104) + R(23);
                R(5) = gm_u32(R(3)); R(3) = R(29); R(4) = R(28); R(6) = 1;
                BL(0x818009A0u, LayoutDispNumber__8dGameComFRCiRCiP12LytTextBox_cb_800B3B60);
            }
            NV_R(24, R(24) - 1); NV_R(20, R(20) + 1); NV_R(26, R(26) + 4);
            CMPU(R(24), 0); NV_R(23, R(23) + 4);
            if (R(24)) GM_LOOP(); else break;
        } while (1);
        gm_set_u8(self + 1102, 0);
    }
    R(3) = gm_u32(CSG_FRAME); R(4) = gm_u32(gm_frame_sp + 28); CMPU(R(3), R(4));
    if (R(3) != R(4)) BL(0x81800A10u, mfn_81844FCC);
}

static void csg_restAlphaDisp(GM_CTX, gptr self) {
    R(4) = gm_u32(self + 1104); CMPU(R(4), 0); if (!R(4)) return;
    R(5) = gm_u32(self + 1068); R(6) = gm_u32(self + 1072); CMPS(R(5), R(6));
    if ((int32_t)R(5) == (int32_t)R(6)) return;
    if ((int32_t)R(5) > (int32_t)R(6)) {
        R(5) -= 20; CMPS(R(5), R(6)); if ((int32_t)R(5) <= (int32_t)R(6)) R(5) = R(6);
    } else {
        R(5) += 20; CMPS(R(6), R(5)); if ((int32_t)R(6) >= (int32_t)R(5)) R(6) = R(5);
        R(5) = R(6);
    }
    gm_set_u32(self + 1068, R(5));
    R(3) = self + 896; ctx->ctr = 4;
    do {
        R(6) = gm_u32(R(3) + 4); R(3) += 4; R(7) = gm_u32(R(3) + 108);
        gm_set_u8(R(6) + 184, R(5)); gm_set_u8(R(7) + 184, R(5));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    R(3) = R(4) - 4; ctx->ctr = 4;
    do {
        R(4) = gm_u32(R(3) + 4); R(3) += 4; R(6) = gm_u32(R(3) + 32);
        gm_set_u8(R(4) + 184, R(5)); gm_set_u8(R(6) + 184, R(5));
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
}

GM_HLE_VERIFIED_(mod_fn_80010140, GMV_IGNORE_POLLS, 0, 0) { R(3) = csg_destruct(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_80010290, GMV_IGNORE_POLLS, 0, 0) { R(3) = csg_createLayout(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_80010690, GMV_IGNORE_POLLS, 0, 0) { csg_playerIconDisp(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_80010800, GMV_IGNORE_POLLS, 0, 0) { csg_restNumberDisp(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_800108C0, GMV_IGNORE_POLLS, 0, 0) { csg_restAlphaDisp(GM_PASS, GM_ARG(0)); }
