/* gm_d_fukidashi_info.c - dfukidashiInfo_c, one speech-bubble child layout.
 * Track B (gm_i2.h, docs/DECOMP.md), instance 2. The complete 572-byte child and its
 * layout objects remain in big-endian guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define FI_SIZE       572
#define FI_INFO       0x80429F7Cu /* dInfo_c pointer; player/session flags begin at +2814 */
#define FI_INFO_FLAGS 2814
#define FI_INFO_SIZE  208

static void fi_draw(GM_CTX, gptr self) {
    I2_FN(0x8180A3F0u);
    NV_R(30, self);
    R(3) = gm_u8(self + 569);
    if (CMPU(R(3), 1) == 0) {
        R(3) = 0x81860000u - 508;
        R(3) = gm_u8(R(3) + 6);
        if (CMPU(R(3), 0) != 0) {
            if (CMPU(R(3), 1) != 0) return;
            BL(0x8180A430u, hle_mod_getNumInGame__9daPyMng_cFv);
            if (CMPS(R(3), 4) >= 0) return;
        }
        R(3) = self + 4;
        BL(0x8180A440u, hle_fn_80006EA0);
    }
}

static void fi_setPosOffset(GM_CTX, gptr self, uint32_t character, uint32_t index) {
    R(6) = 0x81850000u;
    R(4) = (uint32_t)((int32_t)character * 28);
    R(6) -= 27024;
    R(5) = i2_rotl(index, 2) & 0xFFFFFFFCu;
    R(4) = R(6) + R(4);
    R(4) = gm_u32(R(4) + R(5));
    R(5) = 0;
    gm_set_u32(self + 476, R(5));
    gm_set_u32(self + 480, R(4));
    gm_set_u32(self + 484, R(5));
}

/* Apply the two layout colours to all four panes of one picture/text group. */
static void fi_colorGroup(GM_CTX, gptr frame, int counter, uint32_t ra0, uint32_t ra1, uint32_t ra2) {
    R(4) = 0; R(5) = R(28); R(3) = gm_u32(R(29));
    gm_set_u32(frame + 20, R(25));
    NV_R(24, gm_u32(R(3) + 40));
    R(3) = R(29); gm_set_u32(frame + 8, R(25)); ctx->ctr = R(24);
    ctx->lr = ra0; ppc_call_indirect(ctx, base, ctx->ctr);
    ctx->ctr = R(24); R(3) = R(29); R(4) = 1; R(5) = R(28);
    gm_set_u32(frame + 20, R(25)); gm_set_u32(frame + 8, R(25));
    ctx->lr = ra1; ppc_call_indirect(ctx, base, ctx->ctr);
    NV_R(28, 2); NV_R(counter, 2);
    for (;;) {
        R(5) = frame + 8; ctx->ctr = R(24); R(3) = R(29); R(4) = R(28);
        gm_set_u32(frame + 16, R(26)); gm_set_u32(frame + 8, R(26));
        ctx->lr = ra2; ppc_call_indirect(ctx, base, ctx->ctr);
        NV_R(counter, R(counter) - 1);
        CMPU(R(counter), 0);
        NV_R(28, R(28) + 1);
        if (CR_BIT(ctx, 1)) { GM_LOOP(); continue; }
        break;
    }
}

static void fi_colorSet(GM_CTX, gptr self) {
    I2_FN(0x8180A480u);
    R(5) = 0x80430000u; R(4) = 0x81860000u - 5828; NV_R(30, self);
    R(3) = gm_u32(0x81860000u - 300); gm_set_u32(gm_frame_sp + 24, R(3));
    R(3) = gm_u32(self + 540); R(5) = gm_u8(R(5) - 24606);
    R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(4) = gm_u32(R(4) + R(3));
    R(3) = R(5) & 1; CR0(ctx, R(3)); R(5) = gm_u32(self + 544); R(3) = R(4);
    if (!CR_BIT(ctx, 2)) R(3) = 0;
    if (CMPU(R(5), 8) != 0) R(3) = R(4);
    BL(0x8180A4FCu, mfn_81806AB8);
    R(4) = 0x81850000u; NV_R(29, gm_u32(self + 508)); R(5) = 0x81850000u;
    R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(4) -= 26736; R(6) = 0x81850000u;
    NV_R(25, gm_u32(R(4) + R(3))); R(4) = R(5) - 26448;
    NV_R(26, gm_u32(R(4) + R(3))); R(4) = R(6) - 26800;
    NV_R(27, gm_u32(R(4) + R(3))); NV_R(28, gm_frame_sp + 8);
    fi_colorGroup(GM_PASS, gm_frame_sp, 23, 0x8180A550u, 0x8180A56Cu, 0x8180A590u);
    NV_R(29, gm_u32(self + 512)); NV_R(28, gm_frame_sp + 8);
    fi_colorGroup(GM_PASS, gm_frame_sp, 23, 0x8180A5CCu, 0x8180A5E8u, 0x8180A60Cu);
    NV_R(29, gm_u32(self + 516)); NV_R(28, gm_frame_sp + 8);
    fi_colorGroup(GM_PASS, gm_frame_sp, 23, 0x8180A648u, 0x8180A664u, 0x8180A688u);
    NV_R(29, gm_u32(self + 520)); NV_R(28, gm_frame_sp + 8);
    fi_colorGroup(GM_PASS, gm_frame_sp, 25, 0x8180A6C4u, 0x8180A6E0u, 0x8180A704u);
    R(3) = gm_u32(self + 524); R(4) = gm_u32(gm_u32(R(3)) + 104); ctx->ctr = R(4);
    ctx->lr = 0x8180A728u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(4) = i2_rotl(R(27), 16) & 0xFFu; R(5) = R(27) & 0xFFu;
    R(5) = (i2_rotl(R(27), 8) & 0xFF0000u) | (R(5) & ~0xFF0000u);
    R(4) = (i2_rotl(R(27), 24) & 0xFF0000u) | (R(4) & ~0xFF0000u);
    gm_set_u32(R(3) + 28, R(5)); gm_set_u32(R(3) + 24, R(4));
    R(3) = gm_u32(0x81860000u - 300); R(4) = gm_u32(gm_frame_sp + 24);
    if (CMPU(R(3), R(4)) == 0) return;
    BL(0x8180A788u, mfn_81844FCC);
}

static void fi_executeMove(GM_CTX, gptr self) {
    I2_FN(0x8180A788u);
    NV_R(30, self); R(4) = gm_u32(self + 548); NV_R(31, gm_u32(ctx->r[13] - 22276));
    if (CMPS(R(4), 0) != 0) {
        R(0) = gm_u32(self + 564); R(0) = R(4) + R(0); gm_set_u32(self + 548, R(0));
    }
    R(4) = gm_u32(self + 560);
    if (CMPS(R(4), 0) >= 0) {
        R(0) = (uint32_t)-1; gm_set_u32(self + 548, R(4)); gm_set_u32(self + 564, R(0));
    }
    R(0) = gm_u8(self + 570);
    if (CMPS(R(0), 0) != 0) { R(0) = 0; gm_set_u32(self + 548, R(0)); }
    R(0) = gm_u32(self + 544);
    if (CMPS(R(0), 1) == 0) {
        BL(0x8180A7F8u, fn_800B2350); R(0) = R(3) & 0xFFu; CR0(ctx, R(0));
        if (CR_BIT(ctx, 2)) {
            BL(0x8180A804u, fn_800B2360); R(0) = R(3) & 0xFFu; CR0(ctx, R(0));
            if (CR_BIT(ctx, 2)) {
                R(0) = gm_u32(self + 560);
                if (CMPS(R(0), 0) < 0) return;
                R(0) = 0; gm_set_u32(self + 548, R(0));
            }
        }
    }
    R(0) = gm_u32(self + 560);
    if (CMPS(R(0), 0) >= 0) { R(0) = (uint32_t)-1; gm_set_u32(self + 560, R(0)); }
    R(0) = gm_u32(self + 548); cr_cmp_s(ctx, 1, (int32_t)R(0), 0);
    if (!CR_BIT(ctx, 6)) return;
    R(0) = gm_u32(self + 544);
    if (CMPS(R(0), 1) == 0) {
        R(0) = gm_u8(self + 570);
        if (CMPS(R(0), 0) == 0 && CR_BIT(ctx, 6)) {
            R(0) = gm_u32(self + 540); R(4) = 1; R(3) = R(31) + R(0);
            if (CMPS(R(0), 4) >= 0) R(3) += 106;
            gm_set_u8(R(3) + 2902, R(4));
        }
    }
    R(12) = gm_u32(self + 412); R(4) = 0x80360000u - 30184; R(3) = self + 412;
    R(12) = gm_u32(R(12) + 24); R(4) += 0; ctx->ctr = R(12);
    ctx->lr = 0x8180A894u; ppc_call_indirect(ctx, base, ctx->ctr);
}

static void fi_finalizeMove(GM_CTX, gptr self) {
    I2_FN(0x8180A8ACu);
    NV_R(30, self); R(4) = gm_u32(self + 556); R(3) = self + 4;
    BL(0x8180A8CCu, hle_fn_800C9490);
    R(3) = gm_u8(self + 570);
    if (CMPU(R(3), 0) == 0) return;
    R(3) = 0x80310000u + 23440; R(4) = gm_u8(R(3) + 13); R(3) = gm_u8(R(3) + 12);
    R(4) &= 0xFFu; R(3) |= R(4); CR0(ctx, R(3));
    R(3) = gm_u32(FI_INFO);
    if (!CR_BIT(ctx, 2)) {
        R(4) = gm_u32(self + 540); R(5) = (uint32_t)((int32_t)R(4) * 22);
        CMPS(R(4), 4); R(4) = R(3) + R(5);
        R(4) += CR_BIT(ctx, 0) ? 2814 : 2836;
        R(5) = gm_u32(self + 544); R(6) = 1; gm_set_u8(R(4) + R(5), R(6));
    }
    R(4) = gm_u32(self + 544);
    if (CMPU(R(4), 8) == 0) {
        static const uint16_t offsets[] = { 2822, 2844, 2866, 2888, 2932, 2954, 2976, 2998 };
        R(4) = 1;
        for (unsigned i = 0; i < sizeof offsets / sizeof *offsets; i++) gm_set_u8(R(3) + offsets[i], R(4));
    }
    R(3) = 0; gm_set_u8(self + 570, R(3));
}

static void fi_finalizeExit(GM_CTX, gptr self) {
    I2_FN(0x8180A974u);
    R(4) = 0x80310000u + 23440; R(5) = gm_u8(R(4) + 13); R(4) = gm_u8(R(4) + 12);
    R(5) &= 0xFFu; NV_R(30, self); R(4) |= R(5); CR0(ctx, R(4));
    if (!CR_BIT(ctx, 2)) {
        R(3) = gm_u32(self + 560);
        if (CMPS(R(3), 0) < 0) goto clear_done;
    }
    R(4) = FI_INFO; R(3) = gm_u32(self + 540); R(4) = gm_u32(R(4));
    CMPS(R(3), 4); R(3) = R(4) + R(3); R(3) += CR_BIT(ctx, 0) ? 2902 : 3008;
    R(4) = 0; gm_set_u8(R(3), R(4));
clear_done:
    R(3) = 0; gm_set_u32(self + 564, R(3)); gm_set_u8(self + 569, R(3));
    R(3) = self + 4; BL(0x8180A9F0u, hle_disableAllAnimations__Q23m2d13EmbedLayout_cFv);
    R(3) = gm_u32(self + 500); R(4) = gm_u8(R(3) + 187); R(4) &= 0xFEu; gm_set_u8(R(3) + 187, R(4));
}

#define SELF GM_ARG(0)
#define FI_MEM SELF, FI_SIZE
#define FI_SESSION gm_u32(FI_INFO) + FI_INFO_FLAGS, FI_INFO_SIZE
#define FI_GLOBAL  0x80315B9Cu, 4 /* the two mode bytes read by Move/Exit */
GM_HLE_VERIFIED_(mod_fn_800B1990, GMV_IGNORE_POLLS, FI_MEM) { fi_draw(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_800B1A50, FI_MEM) { fi_setPosOffset(GM_PASS, SELF, GM_ARG(1), GM_ARG(2)); }
GM_HLE_VERIFIED_(mod_fn_800B1BD0, GMV_IGNORE_POLLS, FI_MEM,
    gm_u32(SELF + 508), 256, gm_u32(SELF + 512), 256,
    gm_u32(SELF + 516), 256, gm_u32(SELF + 520), 256, gm_u32(SELF + 524), 256) {
    fi_colorSet(GM_PASS, SELF);
}
GM_HLE_VERIFIED_(mod_fn_800B2230, GMV_IGNORE_POLLS, FI_MEM, FI_SESSION, FI_GLOBAL) { fi_executeMove(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_800B2370, GMV_IGNORE_POLLS, FI_MEM, FI_SESSION, FI_GLOBAL) { fi_finalizeMove(GM_PASS, SELF); }
GM_HLE_VERIFIED_(mod_fn_800B24B0, GMV_IGNORE_POLLS, FI_MEM, FI_SESSION, FI_GLOBAL, gm_u32(SELF + 500), 256) {
    fi_finalizeExit(GM_PASS, SELF);
}
