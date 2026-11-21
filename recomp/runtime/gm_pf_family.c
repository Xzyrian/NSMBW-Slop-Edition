/* gm_pf_family.c - instance 2 (track B): the rest of the player family in the DOL - the player's
 * ice / Yoshi / fireball classes (E2 0x8014A6F0-0x8015F4F0: daPlyIce_c, daYoshi_c ...), the player
 * models, effects and parts (0x800D1500-0x800D8400: dPc_c, dPyEffectMng_c, dPyMdlBase_c,
 * dPyMdlMng_c, dPlayerOrchestra_c, dPropelParts_c; 0x800CAA10-0x800CCA40: dMarioMdl_c ...).
 * Transliterated by tools/gm_conv.py from the recompiled bodies; only functions the A/B inputs
 * reach are on, the gate is the strict A/B (against the previous build and the build with no
 * natives). Functions another runtime file defines or calls by symbol are left to their owners.
 * Names are owed (pf_m_<addr>). Flags: -DGM_PF_COUNT / -DGM_PF_VERIFY. */

#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d

/* setHeadID__11dMarioMdl_cFQ211dMarioMdl_c10HeadType_e (setHeadID__11dMarioMdl_cFQ211dMarioMdl_c10HeadType_e, 92 bytes) */
static void pf_setHeadID__11dMarioMdl_cFQ211dMarioMdl_c_caa10(GM_CTX) {
    R(0) = ld32(base, (R(13) + -22936));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800CAA40; }
    R(0) = ld8(base, (R(3) + 337));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800CAA40; }
    R(0) = ld32(base, (R(3) + 380));
    R(4) = (0 + 1);
    st32(base, (R(3) + 2156), R(4));
    R(0) = R(0) & 0xFFFFFFFEu;
    st32(base, (R(3) + 380), R(0));
    return;
L_800CAA40:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    st32(base, (R(3) + 2156), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_800CAA5C; }
    R(0) = ld32(base, (R(3) + 380));
    R(0) = R(0) | 0x1u;
    st32(base, (R(3) + 380), R(0));
    return;
L_800CAA5C:;
    R(0) = ld32(base, (R(3) + 380));
    R(0) = R(0) & 0xFFFFFFFEu;
    st32(base, (R(3) + 380), R(0));
}

/* fn_800CAA70 (fn_800CAA70, 144 bytes) */
static void pf_m_caa70(GM_CTX) {
    R(5) = ld32(base, (R(3) + 352));
    R(4) = (0 + 0x802F0000u);
    R(6) = ld32(base, (R(3) + 1904));
    R(4) = (R(4) + 4224);
    R(0) = R(5) & 0x800000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800CAA90; }
    R(0) = R(5) & 0x1000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800CAA94; }
L_800CAA90:;
    R(6) = (0 + 0);
L_800CAA94:;
    R(0) = ld8(base, (R(3) + 337));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800CAAC4; }
    R(0) = R(5) & 0x8u;
    CR0(ctx, R(0));
    R(3) = (R(4) + 128);
    R(0) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    if ((CR_BIT(ctx, 2))) return;
    R(3) = (R(4) + 144);
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    return;
L_800CAAC4:;
    R(0) = R(5) & 0x200000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800CAADC; }
    R(6) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(3) = (R(4) + 176);
    { uint32_t ea_ = (R(3) + R(6)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_800CAAE8;
L_800CAADC:;
    R(6) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(3) = (R(4) + 160);
    { uint32_t ea_ = (R(3) + R(6)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_800CAAE8:;
    R(0) = R(5) & 0x8u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) return;
    R(3) = (R(4) + 192);
    { uint32_t ea_ = (R(3) + R(6)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
}

/* fn_800CAB00 (fn_800CAB00, 8 bytes) */
static void pf_m_cab00(GM_CTX) {
    R(4) = (0 + 0);
    GM_TAIL(0x800CAA10u, 0); return;
}

/* fn_800CAB10 (fn_800CAB10, 32 bytes) */
static void pf_m_cab10(GM_CTX) {
    R(5) = (0 + 0x80310000u);
    R(6) = ld32(base, (R(13) + -22088));
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(4) = (R(13) + -31288);
    R(5) = (R(5) + 30472);
    R(3) = (R(6) + 4);
    R(5) = ld32(base, (R(5) + R(0)));
    GM_TAIL(0x800DF180u, 0); return;
}

/* fn_800CAD20 (fn_800CAD20, 332 bytes) */
static void pf_m_cad20(GM_CTX) {
    GM_FN(0x800CAD20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 4);
    ctx->f[31].u = ctx->f[1].u;
    R(31) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    R(3) = (0 + 128);
    GM_CALLV(0x800CAD58u, 0x801C5570u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800CADB8; }
    { uint32_t ea_ = (R(30) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (0 + 0xCC010000u);
    { uint32_t ea_ = (R(30) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(30) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(30) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(30) + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 36); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[31].d); }
    goto L_800CAE4C;
L_800CADB8:;
    { uint32_t ea_ = (R(30) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (0 + 0xCC010000u);
    { uint32_t ea_ = (R(30) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(2) + -26424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -26424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(2) + -26424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -26400); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(2) + -26400); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -26400); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(2) + -26400); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -26424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
L_800CAE4C:;
    R(0) = lr;
}

/* fn_800CAE70 (fn_800CAE70, 344 bytes) */
static void pf_m_cae70(GM_CTX) {
    GM_FN(0x800CAE70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 4);
    R(31) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    R(3) = (0 + 128);
    GM_CALLV(0x800CAE9Cu, 0x801C5570u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800CAF0C; }
    { uint32_t ea_ = (R(30) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (0 + 0xCC010000u);
    { uint32_t ea_ = (R(30) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    goto L_800CAFB0;
L_800CAF0C:;
    { uint32_t ea_ = (R(30) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (0 + 0xCC010000u);
    { uint32_t ea_ = (R(30) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(2) + -26424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -26424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 20); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(2) + -26424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -26400); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 32); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(2) + -26400); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -26400); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 44); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(2) + -26400); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -26424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -32768); stfs(base, ea_, ctx->f[0].d); }
L_800CAFB0:;
    R(0) = lr;
}

/* fn_800CAFD0 (fn_800CAFD0, 120 bytes) */
static void pf_m_cafd0(GM_CTX) {
    GM_FN(0x800CAFD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80310000u);
    R(5) = (0 + 0x80010000u);
    R(6) = (R(6) + 30716);
    R(5) = (R(5) + -1040);
    R(7) = (0 + 4);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    st32(base, (R(3) + 0), R(6));
    R(6) = (0 + 0x80010000u);
    R(4) = (R(6) + 24112);
    R(3) = (R(3) + 4);
    R(6) = (0 + 12);
    GM_CALLV(0x800CB018u, 0x802DC9A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800CB02C; }
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x800CB02Cu, 0x800CB080u, 0);
L_800CB02C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_800CB050 (fn_800CB050, 24 bytes) */
static void pf_m_cb050(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800CB060; }
    R(3) = (R(3) + 4);
    GM_TAIL(0x800CAE70u, 0); return;
L_800CB060:;
    R(3) = (R(3) + 4);
    GM_TAIL(0x800CAD20u, 0); return;
}

/* fn_800CB080 (fn_800CB080, 100 bytes) */
static void pf_m_cb080(GM_CTX) {
    { uint32_t ea_ = (R(4) + 0); ctx->f[11].d = ctx->ps1[11] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[10].d = ctx->ps1[10] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[9].d = ctx->ps1[9] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 16); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 20); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 24); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 28); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 32); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (R(3) + 24); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_800CB0F0 (fn_800CB0F0, 208 bytes) */
static void pf_m_cb0f0(GM_CTX) {
    GM_FN(0x800CB0F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80310000u);
    R(5) = (R(5) + 30688);
    R(31) = R(3) |R(3);
    st32(base, (R(3) + 0), R(5));
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 100); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[2].d); }
    R(3) = (0 + 16);
    GM_CALLV(0x800CB138u, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800CB150; }
    R(4) = (0 + 10);
    R(5) = (0 + 8);
    R(6) = (0 + 0);
    GM_CALLV(0x800CB150u, 0x800E2AD0u, 0);
L_800CB150:;
    st32(base, (R(31) + 4), R(3));
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -26424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 60); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 64); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 68); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 72); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 76); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 80); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 84); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 88); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 92); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 52); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 96); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 56); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_800CB470 (fn_800CB470, 28 bytes) */
static void pf_m_cb470(GM_CTX) {
    R(4) = (0 + 0x80310000u);
    R(0) = (0 + 0);
    R(4) = (R(4) + 30568);
    st32(base, (R(3) + 0), R(4));
    st32(base, (R(3) + 4), R(0));
    st32(base, (R(3) + 8), R(0));
}

/* fn_800CB490 (fn_800CB490, 280 bytes) */
static void pf_m_cb490(GM_CTX) {
    GM_FN(0x800CB490); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(27) = R(3) |R(3);
    R(28) = R(4) |R(4);
    R(29) = R(5) |R(5);
    R(31) = R(6) |R(6);
    R(3) = R(7) |R(7);
    GM_CALLV(0x800CB4BCu, 0x800CAB10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800CB4D4; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800CB550; }
    goto L_800CB58C;
L_800CB4D4:;
    R(3) = (0 + 24);
    GM_CALLV(0x800CB4DCu, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800CB4F8; }
    GM_CALLV(0x800CB4ECu, 0x8016A010u, 0);
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 30652);
    st32(base, (R(31) + 0), R(3));
L_800CB4F8:;
    st32(base, (R(27) + 4), R(31));
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    R(6) = R(30) |R(30);
    GM_CALLV(0x800CB510u, 0x800CB740u, 0);
    R(3) = (0 + 24);
    GM_CALLV(0x800CB518u, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800CB534; }
    GM_CALLV(0x800CB528u, 0x8016A010u, 0);
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 30616);
    st32(base, (R(31) + 0), R(3));
L_800CB534:;
    st32(base, (R(27) + 8), R(31));
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    R(6) = R(30) |R(30);
    GM_CALLV(0x800CB54Cu, 0x800CB760u, 0);
    goto L_800CB58C;
L_800CB550:;
    R(3) = (0 + 24);
    GM_CALLV(0x800CB558u, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800CB574; }
    GM_CALLV(0x800CB568u, 0x8016A010u, 0);
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 30580);
    st32(base, (R(31) + 0), R(3));
L_800CB574:;
    st32(base, (R(27) + 4), R(31));
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    R(6) = R(30) |R(30);
    GM_CALLV(0x800CB58Cu, 0x800CB780u, 0);
L_800CB58C:;
    R(11) = (f + 32);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_800CB5B0 (fn_800CB5B0, 24 bytes) */
static void pf_m_cb5b0(GM_CTX) {
    R(3) = ld32(base, (R(3) + 4));
    R(3) = ld32(base, (R(3) + 12));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800CB5D0 (fn_800CB5D0, 88 bytes) */
static void pf_m_cb5d0(GM_CTX) {
    GM_FN(0x800CB5D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800CB5F8u, ctx->ctr, 0);
    R(3) = ld32(base, (R(31) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800CB614; }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800CB614u, ctx->ctr, 0);
L_800CB614:;
    R(0) = lr;
}

/* fn_800CB630 (fn_800CB630, 56 bytes) */
static void pf_m_cb630(GM_CTX) {
    GM_FN(0x800CB630); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x800CB64Cu, 0x800CAB10u, 0);
    R(4) = ld32(base, (R(31) + 4));
    st32(base, (R(4) + 8), R(3));
    R(0) = lr;
}

/* fn_800CB670 (fn_800CB670, 196 bytes) */
static void pf_m_cb670(GM_CTX) {
    GM_FN(0x800CB670); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 40);
    ctx->f[31].u = ctx->f[1].u;
    R(28) = R(5) |R(5);
    R(27) = R(3) |R(3);
    R(29) = R(6) |R(6);
    R(30) = R(7) |R(7);
    R(31) = R(8) |R(8);
    R(5) = (0 + 0);
    GM_CALLV(0x800CB6A8u, 0x80007510u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800CB6B8; }
    R(3) = (0 + 0);
    goto L_800CB718;
L_800CB6B8:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    R(0) = (0 + 0);
    st32(base, (R(27) + 12), R(28));
    st32(base, (R(27) + 8), R(31));
    { uint32_t ea_ = (R(27) + 16); stfs(base, ea_, ctx->f[31].d); }
    st8(base, (R(27) + 20), R(0));
    if ((!CR_BIT(ctx, 0))) { goto L_800CB6E8; }
    R(3) = R(27) |R(27);
    R(4) = (0 + 6);
    R(5) = (0 + 1);
    GM_CALLV(0x800CB6E4u, 0x8016A0F0u, 0);
    R(29) = (0 + 0);
L_800CB6E8:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800CB704; }
    R(3) = R(27) |R(27);
    R(4) = (0 + 7);
    R(5) = (0 + 1);
    GM_CALLV(0x800CB700u, 0x8016A0F0u, 0);
    R(30) = (0 + 0);
L_800CB704:;
    R(3) = R(27) |R(27);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    GM_CALLV(0x800CB714u, 0x8016A2A0u, 0);
    R(3) = (0 + 1);
L_800CB718:;
    R(11) = (f + 40);
    R(0) = lr;
}

/* fn_800CB740 (fn_800CB740, 20 bytes) */
static void pf_m_cb740(GM_CTX) {
    { uint32_t ea_ = (R(2) + -26424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(8) = R(6) |R(6);
    R(6) = (0 + 4);
    R(7) = (0 + -1);
    GM_TAIL(0x800CB670u, 0); return;
}

/* fn_800CB760 (fn_800CB760, 20 bytes) */
static void pf_m_cb760(GM_CTX) {
    { uint32_t ea_ = (R(2) + -26380); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(8) = R(6) |R(6);
    R(6) = (0 + 8);
    R(7) = (0 + -1);
    GM_TAIL(0x800CB670u, 0); return;
}

/* fn_800CB780 (fn_800CB780, 88 bytes) */
static void pf_m_cb780(GM_CTX) {
    GM_FN(0x800CB780); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(8) = R(6) |R(6);
    { uint32_t ea_ = (R(2) + -26424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(6) = (0 + -1);
    R(7) = (0 + 137);
    R(31) = R(3) |R(3);
    GM_CALLV(0x800CB7A8u, 0x800CB670u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800CB7B8; }
    R(3) = (0 + 0);
    goto L_800CB7C4;
L_800CB7B8:;
    R(0) = (0 + 1);
    st8(base, (R(31) + 20), R(0));
    R(3) = (0 + 1);
L_800CB7C4:;
    R(0) = lr;
}

/* fn_800CB7E0 (fn_800CB7E0, 4 bytes) */
static void pf_m_cb7e0(GM_CTX) {
    GM_TAIL(0x800CB810u, 0); return;
}

/* fn_800CB7F0 (fn_800CB7F0, 4 bytes) */
static void pf_m_cb7f0(GM_CTX) {
    GM_TAIL(0x800CB810u, 0); return;
}

/* fn_800CB800 (fn_800CB800, 4 bytes) */
static void pf_m_cb800(GM_CTX) {
    GM_TAIL(0x800CB810u, 0); return;
}

/* fn_800CB810 (fn_800CB810, 144 bytes) */
static void pf_m_cb810(GM_CTX) {
    GM_FN(0x800CB810); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 32));
    ctx->ctr = R(12);
    GM_CALLV(0x800CB83Cu, ctx->ctr, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CB844u, 0x802D2F20u, 0);
    R(31) = R(3) |R(3);
    R(3) = (0 + 1);
    GM_CALLV(0x800CB850u, 0x802D2F80u, 0);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(29) + 12));
    { uint32_t ea_ = (R(29) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(3) + 0));
    R(5) = ld8(base, (R(29) + 20));
    R(12) = ld32(base, (R(12) + 12));
    ctx->ctr = R(12);
    GM_CALLV(0x800CB874u, ctx->ctr, 0);
    R(3) = R(30) & 0xFFu;
    GM_CALLV(0x800CB87Cu, 0x802D2F80u, 0);
    R(3) = R(31) & 0xFFu;
    GM_CALLV(0x800CB884u, 0x802D2F20u, 0);
    R(0) = lr;
}

/* fn_800CB8A0 (fn_800CB8A0, 576 bytes) */
static void pf_m_cb8a0(GM_CTX) {
    GM_FN(0x800CB8A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x800CB8BCu, 0x801C4070u, 0);
    R(3) = (0 + 9);
    R(4) = (0 + 1);
    GM_CALLV(0x800CB8C8u, 0x801C37C0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 9);
    R(5) = (0 + 1);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x800CB8E0u, 0x801C40B0u, 0);
    R(3) = (0 + 13);
    R(4) = (0 + 1);
    GM_CALLV(0x800CB8ECu, 0x801C37C0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 13);
    R(5) = (0 + 1);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x800CB904u, 0x801C40B0u, 0);
    R(3) = ld32(base, (R(30) + 8));
    R(4) = (0 + 0);
    GM_CALLV(0x800CB910u, 0x802C22C0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CB918u, 0x801C6AC0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CB920u, 0x801C4A20u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CB928u, 0x801C8110u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CB930u, 0x801C88F0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CB938u, 0x801C8130u, 0);
    R(3) = (0 + 4);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 2);
    R(9) = (0 + 2);
    GM_CALLV(0x800CB958u, 0x801C6AF0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 1);
    R(6) = (0 + 2);
    R(7) = (0 + 3);
    GM_CALLV(0x800CB970u, 0x801C8640u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 4);
    GM_CALLV(0x800CB984u, 0x801C8790u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 1);
    R(5) = (0 + 4);
    R(6) = (0 + 60);
    R(7) = (0 + 0);
    R(8) = (0 + 125);
    GM_CALLV(0x800CB9A0u, 0x801C47D0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 15);
    R(5) = (0 + 15);
    R(6) = (0 + 15);
    R(7) = (0 + 15);
    GM_CALLV(0x800CB9B8u, 0x801C82F0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CB9D4u, 0x801C8370u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 7);
    R(5) = (0 + 7);
    R(6) = (0 + 7);
    R(7) = (0 + 4);
    GM_CALLV(0x800CB9ECu, 0x801C8330u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CBA08u, 0x801C83D0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBA10u, 0x801C8EB0u, 0);
    R(3) = (0 + 1);
    R(4) = (0 + 7);
    R(5) = (0 + 0);
    GM_CALLV(0x800CBA20u, 0x801C8E70u, 0);
    R(3) = (0 + 1);
    R(4) = (0 + 0);
    R(5) = (0 + 5);
    R(6) = (0 + 15);
    GM_CALLV(0x800CBA34u, 0x801C8DC0u, 0);
    R(3) = (0 + 7);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 7);
    R(7) = (0 + 0);
    GM_CALLV(0x800CBA4Cu, 0x801C86C0u, 0);
    R(31) = (0 + 0);
    st32(base, (f + 12), R(31));
    R(4) = (f + 12);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBA60u, 0x801C8430u, 0);
    { uint32_t ea_ = (R(2) + -26424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (f + 8);
    st32(base, (f + 8), R(31));
    R(3) = (0 + 0);
    ctx->f[2].u = ctx->f[1].u;
    ctx->f[3].u = ctx->f[1].u;
    ctx->f[4].u = ctx->f[1].u;
    GM_CALLV(0x800CBA80u, 0x801C8920u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x800CBA90u, 0x801C8CB0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBA98u, 0x801C5860u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBAA0u, 0x801C8F90u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBAA8u, 0x801C9D60u, 0);
    R(3) = R(30) |R(30);
    R(4) = (f + 16);
    GM_CALLV(0x800CBAB4u, 0x8016A190u, 0);
    R(3) = (f + 16);
    R(4) = (0 + 0);
    GM_CALLV(0x800CBAC0u, 0x801C9940u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBAC8u, 0x801C9A60u, 0);
    R(0) = lr;
}

/* fn_800CBAE0 (fn_800CBAE0, 576 bytes) */
static void pf_m_cbae0(GM_CTX) {
    GM_FN(0x800CBAE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x800CBAFCu, 0x801C4070u, 0);
    R(3) = (0 + 9);
    R(4) = (0 + 1);
    GM_CALLV(0x800CBB08u, 0x801C37C0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 9);
    R(5) = (0 + 1);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x800CBB20u, 0x801C40B0u, 0);
    R(3) = (0 + 13);
    R(4) = (0 + 1);
    GM_CALLV(0x800CBB2Cu, 0x801C37C0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 13);
    R(5) = (0 + 1);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x800CBB44u, 0x801C40B0u, 0);
    R(3) = ld32(base, (R(30) + 8));
    R(4) = (0 + 0);
    GM_CALLV(0x800CBB50u, 0x802C22C0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBB58u, 0x801C6AC0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBB60u, 0x801C4A20u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBB68u, 0x801C8110u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBB70u, 0x801C88F0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBB78u, 0x801C8130u, 0);
    R(3) = (0 + 4);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 2);
    R(9) = (0 + 2);
    GM_CALLV(0x800CBB98u, 0x801C6AF0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 1);
    R(6) = (0 + 2);
    R(7) = (0 + 3);
    GM_CALLV(0x800CBBB0u, 0x801C8640u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 4);
    GM_CALLV(0x800CBBC4u, 0x801C8790u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 1);
    R(5) = (0 + 4);
    R(6) = (0 + 60);
    R(7) = (0 + 0);
    R(8) = (0 + 125);
    GM_CALLV(0x800CBBE0u, 0x801C47D0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 15);
    R(5) = (0 + 15);
    R(6) = (0 + 15);
    R(7) = (0 + 15);
    GM_CALLV(0x800CBBF8u, 0x801C82F0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CBC14u, 0x801C8370u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 7);
    R(5) = (0 + 7);
    R(6) = (0 + 7);
    R(7) = (0 + 4);
    GM_CALLV(0x800CBC2Cu, 0x801C8330u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CBC48u, 0x801C83D0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBC50u, 0x801C8EB0u, 0);
    R(3) = (0 + 1);
    R(4) = (0 + 4);
    R(5) = (0 + 0);
    GM_CALLV(0x800CBC60u, 0x801C8E70u, 0);
    R(3) = (0 + 1);
    R(4) = (0 + 1);
    R(5) = (0 + 1);
    R(6) = (0 + 15);
    GM_CALLV(0x800CBC74u, 0x801C8DC0u, 0);
    R(3) = (0 + 4);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 7);
    R(7) = (0 + 0);
    GM_CALLV(0x800CBC8Cu, 0x801C86C0u, 0);
    R(31) = (0 + 0);
    st32(base, (f + 12), R(31));
    R(4) = (f + 12);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBCA0u, 0x801C8430u, 0);
    { uint32_t ea_ = (R(2) + -26424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (f + 8);
    st32(base, (f + 8), R(31));
    R(3) = (0 + 0);
    ctx->f[2].u = ctx->f[1].u;
    ctx->f[3].u = ctx->f[1].u;
    ctx->f[4].u = ctx->f[1].u;
    GM_CALLV(0x800CBCC0u, 0x801C8920u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x800CBCD0u, 0x801C8CB0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBCD8u, 0x801C5860u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBCE0u, 0x801C8F90u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBCE8u, 0x801C9D60u, 0);
    R(3) = R(30) |R(30);
    R(4) = (f + 16);
    GM_CALLV(0x800CBCF4u, 0x8016A190u, 0);
    R(3) = (f + 16);
    R(4) = (0 + 0);
    GM_CALLV(0x800CBD00u, 0x801C9940u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBD08u, 0x801C9A60u, 0);
    R(0) = lr;
}

/* fn_800CBD20 (fn_800CBD20, 576 bytes) */
static void pf_m_cbd20(GM_CTX) {
    GM_FN(0x800CBD20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x800CBD3Cu, 0x801C4070u, 0);
    R(3) = (0 + 9);
    R(4) = (0 + 1);
    GM_CALLV(0x800CBD48u, 0x801C37C0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 9);
    R(5) = (0 + 1);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x800CBD60u, 0x801C40B0u, 0);
    R(3) = (0 + 13);
    R(4) = (0 + 1);
    GM_CALLV(0x800CBD6Cu, 0x801C37C0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 13);
    R(5) = (0 + 1);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x800CBD84u, 0x801C40B0u, 0);
    R(3) = ld32(base, (R(30) + 8));
    R(4) = (0 + 0);
    GM_CALLV(0x800CBD90u, 0x802C22C0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBD98u, 0x801C6AC0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBDA0u, 0x801C4A20u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBDA8u, 0x801C8110u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBDB0u, 0x801C88F0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBDB8u, 0x801C8130u, 0);
    R(3) = (0 + 4);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 2);
    R(9) = (0 + 2);
    GM_CALLV(0x800CBDD8u, 0x801C6AF0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 1);
    R(5) = (0 + 4);
    R(6) = (0 + 60);
    R(7) = (0 + 0);
    R(8) = (0 + 125);
    GM_CALLV(0x800CBDF4u, 0x801C47D0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 1);
    R(6) = (0 + 2);
    R(7) = (0 + 3);
    GM_CALLV(0x800CBE0Cu, 0x801C8640u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 4);
    GM_CALLV(0x800CBE20u, 0x801C8790u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 15);
    R(5) = (0 + 15);
    R(6) = (0 + 15);
    R(7) = (0 + 2);
    GM_CALLV(0x800CBE38u, 0x801C82F0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CBE54u, 0x801C8370u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 7);
    R(5) = (0 + 7);
    R(6) = (0 + 7);
    R(7) = (0 + 4);
    GM_CALLV(0x800CBE6Cu, 0x801C8330u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CBE88u, 0x801C83D0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBE90u, 0x801C8EB0u, 0);
    R(3) = (0 + 1);
    R(4) = (0 + 1);
    R(5) = (0 + 1);
    R(6) = (0 + 15);
    GM_CALLV(0x800CBEA4u, 0x801C8DC0u, 0);
    R(3) = (0 + 1);
    R(4) = (0 + 7);
    R(5) = (0 + 0);
    GM_CALLV(0x800CBEB4u, 0x801C8E70u, 0);
    R(3) = (0 + 7);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 7);
    R(7) = (0 + 0);
    GM_CALLV(0x800CBECCu, 0x801C86C0u, 0);
    R(31) = (0 + 0);
    st32(base, (f + 12), R(31));
    R(4) = (f + 12);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBEE0u, 0x801C8430u, 0);
    { uint32_t ea_ = (R(2) + -26424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (f + 8);
    st32(base, (f + 8), R(31));
    R(3) = (0 + 0);
    ctx->f[2].u = ctx->f[1].u;
    ctx->f[3].u = ctx->f[1].u;
    ctx->f[4].u = ctx->f[1].u;
    GM_CALLV(0x800CBF00u, 0x801C8920u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x800CBF10u, 0x801C8CB0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBF18u, 0x801C5860u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CBF20u, 0x801C8F90u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBF28u, 0x801C9D60u, 0);
    R(3) = R(30) |R(30);
    R(4) = (f + 16);
    GM_CALLV(0x800CBF34u, 0x8016A190u, 0);
    R(3) = (f + 16);
    R(4) = (0 + 0);
    GM_CALLV(0x800CBF40u, 0x801C9940u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CBF48u, 0x801C9A60u, 0);
    R(0) = lr;
}

/* fn_800CBF60 (fn_800CBF60, 60 bytes) */
static void pf_m_cbf60(GM_CTX) {
    GM_FN(0x800CBF60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800CBF78u, 0x8016A010u, 0);
    R(4) = (0 + 0x80310000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 30536);
    st32(base, (R(31) + 0), R(4));
    R(0) = lr;
}

/* fn_800CBFA0 (fn_800CBFA0, 164 bytes) */
static void pf_m_cbfa0(GM_CTX) {
    GM_FN(0x800CBFA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(6) |R(6);
    R(30) = R(5) |R(5);
    R(5) = (0 + 0);
    R(29) = R(3) |R(3);
    GM_CALLV(0x800CBFCCu, 0x80007510u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800CBFDC; }
    R(3) = (0 + 0);
    goto L_800CC028;
L_800CBFDC:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800CBFF8; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 6);
    R(5) = (0 + 1);
    GM_CALLV(0x800CBFF4u, 0x8016A0F0u, 0);
    R(30) = (0 + 0);
L_800CBFF8:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800CC014; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 7);
    R(5) = (0 + 1);
    GM_CALLV(0x800CC010u, 0x8016A0F0u, 0);
    R(31) = (0 + 0);
L_800CC014:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    GM_CALLV(0x800CC024u, 0x8016A2A0u, 0);
    R(3) = (0 + 1);
L_800CC028:;
    R(0) = lr;
}

/* fn_800CC050 (fn_800CC050, 60 bytes) */
static void pf_m_cc050(GM_CTX) {
    GM_FN(0x800CC050); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800CC068u, 0x800CC090u, 0);
    { uint32_t ea_ = (R(31) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    GM_CALLV(0x800CC078u, 0x8000EDF0u, 0);
    R(0) = lr;
}

/* fn_800CC090 (fn_800CC090, 440 bytes) */
static void pf_m_cc090(GM_CTX) {
    GM_FN(0x800CC090); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 1);
    GM_CALLV(0x800CC0A8u, 0x801C6AC0u, 0);
    R(3) = (0 + 4);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    R(8) = (0 + 2);
    R(9) = (0 + 2);
    GM_CALLV(0x800CC0C8u, 0x801C6AF0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC0D0u, 0x801C4A20u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC0D8u, 0x801C8110u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CC0E0u, 0x801C88F0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC0E8u, 0x801C8130u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 1);
    R(6) = (0 + 2);
    R(7) = (0 + 3);
    GM_CALLV(0x800CC100u, 0x801C8640u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 255);
    R(5) = (0 + 255);
    R(6) = (0 + 4);
    GM_CALLV(0x800CC114u, 0x801C8790u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 15);
    R(5) = (0 + 15);
    R(6) = (0 + 15);
    R(7) = (0 + 15);
    GM_CALLV(0x800CC12Cu, 0x801C82F0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CC148u, 0x801C8370u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 7);
    R(5) = (0 + 7);
    R(6) = (0 + 7);
    R(7) = (0 + 7);
    GM_CALLV(0x800CC160u, 0x801C8330u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CC17Cu, 0x801C83D0u, 0);
    R(3) = (0 + 1);
    R(4) = (0 + 6);
    R(5) = (0 + 6);
    R(6) = (0 + 15);
    GM_CALLV(0x800CC190u, 0x801C8DC0u, 0);
    R(31) = (0 + 0);
    st32(base, (f + 12), R(31));
    R(4) = (f + 12);
    R(3) = (0 + 1);
    GM_CALLV(0x800CC1A4u, 0x801C8430u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC1ACu, 0x801C8EB0u, 0);
    R(3) = (0 + 1);
    R(4) = (0 + 3);
    R(5) = (0 + 0);
    GM_CALLV(0x800CC1BCu, 0x801C8E70u, 0);
    R(3) = (0 + 7);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 7);
    R(7) = (0 + 0);
    GM_CALLV(0x800CC1D4u, 0x801C86C0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC1DCu, 0x802D2F80u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CC1E4u, 0x802D2F20u, 0);
    { uint32_t ea_ = (R(2) + -26424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (f + 8);
    st32(base, (f + 8), R(31));
    R(3) = (0 + 0);
    ctx->f[2].u = ctx->f[1].u;
    ctx->f[3].u = ctx->f[1].u;
    ctx->f[4].u = ctx->f[1].u;
    GM_CALLV(0x800CC204u, 0x801C8920u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x800CC214u, 0x801C8CB0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC21Cu, 0x801C5860u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CC224u, 0x801C8F90u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC22Cu, 0x801C9D60u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC234u, 0x801C9A60u, 0);
    R(0) = lr;
}

/* fn_800CC250 (fn_800CC250, 68 bytes) */
static void pf_m_cc250(GM_CTX) {
    GM_FN(0x800CC250); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800CC268u, 0x8016A010u, 0);
    R(3) = (0 + 0x80310000u);
    R(0) = (0 + 0);
    R(3) = (R(3) + 30504);
    st32(base, (R(31) + 0), R(3));
    R(3) = R(31) |R(31);
    st8(base, (R(31) + 20), R(0));
    R(0) = lr;
}

/* fn_800CC2A0 (fn_800CC2A0, 164 bytes) */
static void pf_m_cc2a0(GM_CTX) {
    GM_FN(0x800CC2A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(6) |R(6);
    R(30) = R(5) |R(5);
    R(5) = (0 + 0);
    R(29) = R(3) |R(3);
    GM_CALLV(0x800CC2CCu, 0x80007510u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800CC2DC; }
    R(3) = (0 + 0);
    goto L_800CC328;
L_800CC2DC:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800CC2F8; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 6);
    R(5) = (0 + 1);
    GM_CALLV(0x800CC2F4u, 0x8016A0F0u, 0);
    R(30) = (0 + 0);
L_800CC2F8:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800CC314; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 7);
    R(5) = (0 + 1);
    GM_CALLV(0x800CC310u, 0x8016A0F0u, 0);
    R(31) = (0 + 0);
L_800CC314:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    GM_CALLV(0x800CC324u, 0x8016A2A0u, 0);
    R(3) = (0 + 1);
L_800CC328:;
    R(0) = lr;
}

/* fn_800CC350 (fn_800CC350, 60 bytes) */
static void pf_m_cc350(GM_CTX) {
    GM_FN(0x800CC350); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800CC368u, 0x800CC390u, 0);
    { uint32_t ea_ = (R(31) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    GM_CALLV(0x800CC378u, 0x8000EDF0u, 0);
    R(0) = lr;
}

/* fn_800CC390 (fn_800CC390, 468 bytes) */
static void pf_m_cc390(GM_CTX) {
    GM_FN(0x800CC390); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = (0 + 1);
    GM_CALLV(0x800CC3B0u, 0x801C6AC0u, 0);
    R(3) = (0 + 4);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    R(8) = (0 + 2);
    R(9) = (0 + 2);
    GM_CALLV(0x800CC3D0u, 0x801C6AF0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC3D8u, 0x801C4A20u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC3E0u, 0x801C8110u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CC3E8u, 0x801C88F0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC3F0u, 0x801C8130u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 1);
    R(6) = (0 + 2);
    R(7) = (0 + 3);
    GM_CALLV(0x800CC408u, 0x801C8640u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 255);
    R(5) = (0 + 255);
    R(6) = (0 + 4);
    GM_CALLV(0x800CC41Cu, 0x801C8790u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 15);
    R(5) = (0 + 15);
    R(6) = (0 + 15);
    R(7) = (0 + 15);
    GM_CALLV(0x800CC434u, 0x801C82F0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CC450u, 0x801C8370u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 7);
    R(5) = (0 + 7);
    R(6) = (0 + 7);
    R(7) = (0 + 1);
    GM_CALLV(0x800CC468u, 0x801C8330u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800CC484u, 0x801C83D0u, 0);
    R(3) = (0 + 1);
    R(4) = (0 + 1);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    GM_CALLV(0x800CC498u, 0x801C8DC0u, 0);
    R(31) = (0 + 0);
    st32(base, (f + 12), R(31));
    R(0) = ld8(base, (R(30) + 20));
    R(4) = (f + 16);
    st8(base, (f + 15), R(0));
    R(3) = (0 + 1);
    R(0) = ld32(base, (f + 12));
    st32(base, (f + 16), R(0));
    GM_CALLV(0x800CC4BCu, 0x801C8430u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC4C4u, 0x801C8EB0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 3);
    R(5) = (0 + 0);
    GM_CALLV(0x800CC4D4u, 0x801C8E70u, 0);
    R(3) = (0 + 7);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 7);
    R(7) = (0 + 0);
    GM_CALLV(0x800CC4ECu, 0x801C86C0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CC4F4u, 0x802D2F80u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC4FCu, 0x802D2F20u, 0);
    { uint32_t ea_ = (R(2) + -26424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (f + 8);
    st32(base, (f + 8), R(31));
    R(3) = (0 + 0);
    ctx->f[2].u = ctx->f[1].u;
    ctx->f[3].u = ctx->f[1].u;
    ctx->f[4].u = ctx->f[1].u;
    GM_CALLV(0x800CC51Cu, 0x801C8920u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x800CC52Cu, 0x801C8CB0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC534u, 0x801C5860u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800CC53Cu, 0x801C8F90u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC544u, 0x801C9D60u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x800CC54Cu, 0x801C9A60u, 0);
    R(0) = lr;
}

/* fn_800CC860 (fn_800CC860, 4 bytes) */
static void pf_m_cc860(GM_CTX) {

}

/* fn_800CC8E0 (fn_800CC8E0, 184 bytes) */
static void pf_m_cc8e0(GM_CTX) {
    GM_FN(0x800CC8E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80310000u);
    R(7) = (0 + 32);
    R(6) = (R(6) + 30744);
    R(8) = (0 + 0);
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(4) = (0 + 2048);
    R(29) = R(3) |R(3);
    R(3) = R(30) |R(30);
    R(5) = ld32(base, (R(13) + -18544));
    GM_CALLV(0x800CC924u, 0x8016A960u, 0);
    R(3) = (0 + 52);
    GM_CALLV(0x800CC92Cu, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800CC940; }
    R(4) = (0 + 0x80360000u);
    R(4) = (R(4) + -25520);
    GM_CALLV(0x800CC940u, 0x800CAFD0u, 0);
L_800CC940:;
    st32(base, (R(29) + 24), R(3));
    R(3) = (0 + 12);
    GM_CALLV(0x800CC94Cu, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800CC958; }
    GM_CALLV(0x800CC958u, 0x800CB470u, 0);
L_800CC958:;
    st32(base, (R(29) + 20), R(3));
    R(4) = R(30) |R(30);
    R(5) = ld32(base, (R(29) + 24));
    R(7) = R(31) |R(31);
    R(6) = (0 + 0);
    GM_CALLV(0x800CC970u, 0x800CB490u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x800CC978u, 0x8016A9B0u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_800CC9A0 (fn_800CC9A0, 152 bytes) */
static void pf_m_cc9a0(GM_CTX) {
    GM_FN(0x800CC9A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -26376); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (f + 8);
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(3) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[1].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[0].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d + ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[2].d); }
    R(3) = ld32(base, (R(3) + 24));
    GM_CALLV(0x800CCA18u, 0x800CB080u, 0);
    R(3) = ld32(base, (R(31) + 20));
    GM_CALLV(0x800CCA20u, 0x800CB5B0u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* set__5dPc_cFP8dActor_cUc (set__5dPc_cFP8dActor_cUc, 12 bytes) */
static void pf_set__5dPc_cFP8dActor_cUc_d1500(GM_CTX) {
    st32(base, (R(3) + 4), R(4));
    st8(base, (R(3) + 43), R(5));
}

/* check__5dPc_cFi (check__5dPc_cFi, 300 bytes) */
static void pf_check__5dPc_cFi_d1510(GM_CTX) {
    GM_FN(0x800D1510); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D161C; }
    R(31) = ld32(base, (R(13) + -22168));
    goto L_800D1614;
L_800D1544:;
    R(0) = ld32(base, (R(29) + 16));
    cr_cmp_u(ctx, 0, R(0), R(31));
    if ((CR_BIT(ctx, 2))) { goto L_800D1610; }
    R(3) = R(29) |R(29);
    R(4) = R(31) |R(31);
    R(5) = R(30) |R(30);
    GM_CALLV(0x800D1560u, 0x800D16B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D1610; }
    st32(base, (R(29) + 12), R(31));
    R(3) = ld32(base, (R(29) + 4));
    st32(base, (R(29) + 16), R(31));
    { uint32_t ea_ = (R(2) + -26260); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 268); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -26264); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 196); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -26256); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 20); stfs(base, ea_, ctx->f[3].d); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(29) + 24); stfs(base, ea_, ctx->f[1].d); }
    if ((!CR_BIT(ctx, 0))) { goto L_800D15B0; }
    { uint32_t ea_ = (R(29) + 20); stfs(base, ea_, ctx->f[0].d); }
    goto L_800D15C0;
L_800D15B0:;
    { uint32_t ea_ = (R(2) + -26252); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800D15C0; }
    { uint32_t ea_ = (R(29) + 20); stfs(base, ea_, ctx->f[0].d); }
L_800D15C0:;
    { uint32_t ea_ = (R(29) + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -26264); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D15D8; }
    { uint32_t ea_ = (R(29) + 24); stfs(base, ea_, ctx->f[0].d); }
    goto L_800D15E8;
L_800D15D8:;
    { uint32_t ea_ = (R(2) + -26248); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800D15E8; }
    { uint32_t ea_ = (R(29) + 24); stfs(base, ea_, ctx->f[0].d); }
L_800D15E8:;
    R(5) = (0 + 0);
    R(0) = (0 + 30);
    st16(base, (R(29) + 40), R(5));
    R(3) = (0 + 1);
    R(4) = ld32(base, (R(29) + 4));
    st8(base, (R(29) + 45), R(0));
    st8(base, (R(29) + 42), R(5));
    { uint32_t ea_ = (R(4) + 268); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 24); stfs(base, ea_, ctx->f[0].d); }
    goto L_800D1620;
L_800D1610:;
    R(31) = ld32(base, (R(31) + 8));
L_800D1614:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800D1544; }
L_800D161C:;
    R(3) = (0 + 0);
L_800D1620:;
    R(0) = lr;
}

/* chkTimer__5dPc_cFv (chkTimer__5dPc_cFv, 104 bytes) */
static void pf_chkTimer__5dPc_cFv_d1640(GM_CTX) {
    R(4) = ld8(base, (R(3) + 45));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D1654; }
    R(0) = (R(4) + -1);
    st8(base, (R(3) + 45), R(0));
L_800D1654:;
    R(0) = ld8(base, (R(3) + 45));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D1668; }
    R(0) = (0 + 0);
    st32(base, (R(3) + 16), R(0));
L_800D1668:;
    R(0) = ld32(base, (R(3) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) return;
    R(4) = (int16_t)ld16(base, (R(3) + 40));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800D168C; }
    R(0) = (R(4) + -1);
    st16(base, (R(3) + 40), R(0));
    return;
L_800D168C:;
    R(4) = ld8(base, (R(3) + 46));
    R(0) = ld8(base, (R(3) + 47));
    cr_cmp_u(ctx, 0, R(4), R(0));
    if ((CR_BIT(ctx, 2))) return;
    R(0) = (0 + 2);
    st16(base, (R(3) + 40), R(0));
}

/* fn_800D16B0 (fn_800D16B0, 56 bytes) */
static void pf_m_d16b0(GM_CTX) {
    GM_FN(0x800D16B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x802F0000u);
    R(6) = (R(6) + 4592);
    R(0) = ld8(base, (R(4) + 32));
    R(0) = ((int32_t)R(0) * 12);
    R(12) = R(6) + R(0);
    GM_CALLV(0x800D16D4u, 0x802DCBFCu, 0);
    R(0) = R(0) | 0x0u;
    R(0) = lr;
}

/* fn_800D19E0 (fn_800D19E0, 980 bytes) */
static void pf_m_d19e0(GM_CTX) {
    GM_FN(0x800D19E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 80);
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(28) = R(3) |R(3);
    R(29) = R(4) |R(4);
    if ((CR_BIT(ctx, 2))) { goto L_800D1A84; }
    { uint32_t ea_ = (R(2) + -26232); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    goto L_800D1A88;
L_800D1A84:;
    { uint32_t ea_ = (R(2) + -26252); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
L_800D1A88:;
    R(3) = ld8(base, (R(3) + 43));
    R(31) = (0 + 1);
    R(0) = ld8(base, (R(4) + 34));
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D1D20; }
    R(3) = ld32(base, (R(4) + 48));
    R(4) = (f + 14);
    R(27) = (int16_t)ld16(base, (R(3) + 0));
    st16(base, (f + 14), R(27));
    { uint32_t ea_ = (R(4) + 0); psq_l(ctx, base, 1, ea_, 1, 3); }
    { uint32_t ea_ = (R(2) + -26244); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    GM_CALLV(0x800D1ABCu, 0x80237BD0u, 0);
    st16(base, (f + 12), R(27));
    R(3) = (f + 12);
    { uint32_t ea_ = (R(3) + 0); psq_l(ctx, base, 1, ea_, 1, 3); }
    { uint32_t ea_ = (R(2) + -26244); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    GM_CALLV(0x800D1AD4u, 0x80237C40u, 0);
    R(3) = ld32(base, (R(28) + 4));
    R(26) = (f + 10);
    { uint32_t ea_ = (R(2) + -26252); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    R(25) = (f + 8);
    { uint32_t ea_ = (R(3) + 212); ctx->f[24].d = ctx->ps1[24] = ldfs(base, ea_); }
    R(30) = (0 + 0);
    { uint32_t ea_ = (R(2) + -26264); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    ctx->f[19].u = ctx->f[27].u;
    { uint32_t ea_ = (R(29) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[31].u = ctx->f[27].u;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d * ctx->f[24].d);
    { uint32_t ea_ = (R(3) + 176); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    ctx->f[26].d = ctx->ps1[26] = frsp(ctx->f[1].d - ctx->f[27].d);
    { uint32_t ea_ = (R(3) + 208); ctx->f[25].d = ctx->ps1[25] = ldfs(base, ea_); }
    R(24) = (0 + 0);
    ctx->f[21].d = ctx->ps1[21] = frsp(ctx->f[22].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 172); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
    R(23) = (0 + 0);
    { uint32_t ea_ = (R(2) + -26240); ctx->f[20].d = ctx->ps1[20] = ldfs(base, ea_); }
    R(22) = (0 + 0);
    { uint32_t ea_ = (R(2) + -26244); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -26236); ctx->f[18].d = ctx->ps1[18] = ldfs(base, ea_); }
    goto L_800D1D14;
L_800D1B30:;
    R(3) = ld32(base, (R(29) + 44));
    { uint32_t ea_ = (R(3) + R(24)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[27].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1B5C; }
    ctx->f[27].d = ctx->ps1[27] = frsp(ctx->f[27].d - ctx->f[0].d);
    R(23) = (R(23) + 2);
    ctx->f[20].d = ctx->ps1[20] = frsp(ctx->f[20].d + ctx->f[0].d);
    R(22) = (R(22) + 8);
    R(30) = (R(30) + 1);
    R(24) = (R(24) + 4);
L_800D1B5C:;
    R(3) = ld32(base, (R(29) + 48));
    R(27) = (int16_t)ld16(base, (R(3) + R(23)));
    st16(base, (f + 10), R(27));
    { uint32_t ea_ = (R(26) + 0); psq_l(ctx, base, 0, ea_, 1, 3); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d * ctx->f[0].d);
    GM_CALLV(0x800D1B74u, 0x80237BD0u, 0);
    st16(base, (f + 8), R(27));
    ctx->f[17].u = ctx->f[1].u;
    { uint32_t ea_ = (R(25) + 0); psq_l(ctx, base, 0, ea_, 1, 3); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d * ctx->f[0].d);
    GM_CALLV(0x800D1B88u, 0x80237C40u, 0);
    R(0) = ld32(base, (R(29) + 40));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[27].d * ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[27].d * ctx->f[17].d);
    { uint32_t ea_ = (R(22) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(6) = R(0) + R(22);
    { uint32_t ea_ = (R(6) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[23].d - ctx->f[1].d);
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[28].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1D0C; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[21].d - ctx->f[2].d);
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[31].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_800D1BF0; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[22].d - ctx->f[2].d);
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[31].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1D0C; }
L_800D1BF0:;
    R(5) = ld32(base, (R(28) + 4));
    R(0) = -(int32_t)R(27);
    { uint32_t ea_ = (R(6) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 16);
    { uint32_t ea_ = (R(5) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (int16_t)R(0);
    { uint32_t ea_ = (R(6) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[25].d + ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[24].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x800D1C2Cu, 0x800B3000u, 0);
    { uint32_t ea_ = (f + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[29].d * ctx->f[24].d);
    { uint32_t ea_ = (f + 16); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[24].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[20].d + ctx->f[0].d);
    { uint32_t ea_ = (R(28) + 28); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld8(base, (R(29) + 35));
    { uint32_t ea_ = (R(29) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1C60; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[24].d);
L_800D1C60:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[3].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1D0C; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1D0C; }
    R(0) = ld32(base, (R(29) + 16));
    R(3) = R(0) |R(0);
    goto L_800D1C9C;
    R(0) = R(0) | 0x0u;
L_800D1C88:;
    cr_cmp_u(ctx, 0, R(3), R(28));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1C98; }
    R(31) = (0 + 0);
    goto L_800D1CA4;
L_800D1C98:;
    R(3) = ld32(base, (R(3) + 8));
L_800D1C9C:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800D1C88; }
L_800D1CA4:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D1CB4; }
    st32(base, (R(28) + 8), R(0));
    st32(base, (R(29) + 16), R(28));
L_800D1CB4:;
    st8(base, (R(28) + 44), R(30));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[24].d);
    R(5) = (0 + 0);
    R(4) = (0 + 0);
    R(3) = ld8(base, (R(29) + 60));
    R(0) = (R(3) + -1);
    ctx->ctr = R(0);
    cr_cmp_u(ctx, 0, R(0), 0x0u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D1CFC; }
L_800D1CD8:;
    R(3) = ld32(base, (R(29) + 44));
    { uint32_t ea_ = (R(3) + R(4)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_800D1CFC; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    R(4) = (R(4) + 4);
    R(5) = (R(5) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800D1CD8; }
L_800D1CFC:;
    st8(base, (R(28) + 46), R(5));
    R(3) = (0 + 1);
    { uint32_t ea_ = (R(28) + 32); stfs(base, ea_, ctx->f[1].d); }
    goto L_800D1D24;
L_800D1D0C:;
    ctx->f[19].d = ctx->ps1[19] = frsp(ctx->f[19].d + ctx->f[18].d);
    ctx->f[27].d = ctx->ps1[27] = frsp(ctx->f[27].d + ctx->f[18].d);
L_800D1D14:;
    cr_fcmp(ctx, 0, ctx->f[19].d, ctx->f[26].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800D1B30; }
L_800D1D20:;
    R(3) = (0 + 0);
L_800D1D24:;
    R(11) = (f + 80);
    R(0) = lr;
}

/* fn_800D1DC0 (fn_800D1DC0, 332 bytes) */
static void pf_m_d1dc0(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D1DD0; }
    { uint32_t ea_ = (R(2) + -26232); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_800D1DD4;
L_800D1DD0:;
    { uint32_t ea_ = (R(2) + -26252); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_800D1DD4:;
    R(6) = ld8(base, (R(3) + 43));
    R(0) = ld8(base, (R(4) + 34));
    R(0) = R(6) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D1F04; }
    R(7) = ld32(base, (R(3) + 4));
    R(6) = ld32(base, (R(4) + 40));
    { uint32_t ea_ = (R(7) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1F04; }
    { uint32_t ea_ = (R(6) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -26252); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(7) + 176); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1F04; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1F04; }
    { uint32_t ea_ = (R(7) + 212); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -26264); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld8(base, (R(4) + 35));
    { uint32_t ea_ = (R(4) + 20); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1E5C; }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[1].d);
L_800D1E5C:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1F04; }
    R(0) = ld32(base, (R(4) + 16));
    R(5) = (0 + 1);
    R(6) = R(0) |R(0);
    goto L_800D1E8C;
L_800D1E78:;
    cr_cmp_u(ctx, 0, R(6), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_800D1E88; }
    R(5) = (0 + 0);
    goto L_800D1E94;
L_800D1E88:;
    R(6) = ld32(base, (R(6) + 8));
L_800D1E8C:;
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800D1E78; }
L_800D1E94:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D1EA4; }
    st32(base, (R(3) + 8), R(0));
    st32(base, (R(4) + 16), R(3));
L_800D1EA4:;
    R(0) = (0 + 0);
    st8(base, (R(3) + 44), R(0));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[1].d);
    R(7) = (0 + 0);
    R(5) = ld8(base, (R(4) + 60));
    R(6) = (0 + 0);
    R(0) = (R(5) + -1);
    ctx->ctr = R(0);
    cr_cmp_u(ctx, 0, R(0), 0x0u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D1EF4; }
    R(0) = R(0) | 0x0u;
L_800D1ED0:;
    R(5) = ld32(base, (R(4) + 44));
    { uint32_t ea_ = (R(5) + R(6)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_800D1EF4; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    R(6) = (R(6) + 4);
    R(7) = (R(7) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800D1ED0; }
L_800D1EF4:;
    st8(base, (R(3) + 46), R(7));
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[1].d); }
    R(3) = (0 + 1);
    return;
L_800D1F04:;
    GM_TAIL(0x800D19E0u, 0); return;
}

/* move__5dPc_cFf (move__5dPc_cFf, 108 bytes) */
static void pf_move__5dPc_cFf_d1f10(GM_CTX) {
    GM_FN(0x800D1F10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(5) = ld32(base, (R(3) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D1F38; }
    R(3) = (0 + 1);
    goto L_800D1F68;
L_800D1F38:;
    R(0) = ld8(base, (R(3) + 46));
    R(4) = (0 + 30);
    st8(base, (R(3) + 45), R(4));
    R(4) = (0 + 0x802F0000u);
    R(4) = (R(4) + 4640);
    st8(base, (R(3) + 47), R(0));
    R(0) = ld8(base, (R(5) + 32));
    R(0) = ((int32_t)R(0) * 12);
    R(12) = R(4) + R(0);
    GM_CALLV(0x800D1F60u, 0x802DCBFCu, 0);
    R(0) = R(0) | 0x0u;
    st8(base, (R(31) + 42), R(3));
L_800D1F68:;
    R(0) = lr;
}

/* fn_800D2060 (fn_800D2060, 416 bytes) */
static void pf_m_d2060(GM_CTX) {
    GM_FN(0x800D2060); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(3) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(30) = ld32(base, (R(3) + 12));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld8(base, (R(30) + 35));
    R(0) = R(4) & 0x2u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D20A4; }
    R(3) = (0 + 6);
    goto L_800D21E0;
L_800D20A4:;
    R(5) = ld32(base, (R(3) + 4));
    R(0) = ld8(base, (R(5) + 908));
    { uint32_t ea_ = (R(5) + 212); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_800D20E4; }
    R(0) = ld32(base, (R(5) + 4240));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D20D0; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((CR_BIT(ctx, 2))) { goto L_800D20DC; }
    goto L_800D20E4;
L_800D20D0:;
    { uint32_t ea_ = (R(2) + -26228); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d + ctx->f[0].d);
    goto L_800D20E4;
L_800D20DC:;
    { uint32_t ea_ = (R(2) + -26224); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d + ctx->f[0].d);
L_800D20E4:;
    { uint32_t ea_ = (R(2) + -26264); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = R(4) & 0x1u;
    CR0(ctx, R(0));
    { uint32_t ea_ = (R(30) + 20); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[31].d);
    if ((!CR_BIT(ctx, 2))) { goto L_800D20FC; }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[31].d);
L_800D20FC:;
    { uint32_t ea_ = (R(3) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(6) = (0 + 0);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D211C; }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[1].d); }
    R(6) = (0 + 2);
    goto L_800D2148;
L_800D211C:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D2148; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D213C; }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[2].d); }
    R(6) = (0 + 4);
    goto L_800D2148;
L_800D213C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D2144u, 0x800D2200u, 0);
    R(6) = (0 + 1);
L_800D2148:;
    R(7) = ld8(base, (R(30) + 60));
    R(5) = (0 + 0);
    { uint32_t ea_ = (R(31) + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0);
    R(0) = (R(7) + -1);
    ctx->ctr = R(0);
    cr_cmp_u(ctx, 0, R(0), 0x0u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D218C; }
L_800D2168:;
    R(3) = ld32(base, (R(30) + 44));
    { uint32_t ea_ = (R(3) + R(4)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_800D218C; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    R(4) = (R(4) + 4);
    R(5) = (R(5) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800D2168; }
L_800D218C:;
    { uint32_t ea_ = (R(31) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (R(7) + -1);
    st8(base, (R(31) + 44), R(5));
    R(5) = (0 + 0);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[31].d);
    R(4) = (0 + 0);
    ctx->ctr = R(0);
    cr_cmp_u(ctx, 0, R(0), 0x0u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D21D4; }
L_800D21B0:;
    R(3) = ld32(base, (R(30) + 44));
    { uint32_t ea_ = (R(3) + R(4)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_800D21D4; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    R(4) = (R(4) + 4);
    R(5) = (R(5) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800D21B0; }
L_800D21D4:;
    st8(base, (R(31) + 46), R(5));
    R(3) = R(6) |R(6);
    { uint32_t ea_ = (R(31) + 32); stfs(base, ea_, ctx->f[1].d); }
L_800D21E0:;
    R(0) = lr;
}

/* release__5dPc_cFv (release__5dPc_cFv, 100 bytes) */
static void pf_release__5dPc_cFv_d2200(GM_CTX) {
    R(5) = ld32(base, (R(3) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) return;
    R(4) = ld32(base, (R(5) + 16));
    cr_cmp_u(ctx, 0, R(4), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_800D2258; }
    R(4) = ld32(base, (R(3) + 8));
    R(0) = (0 + 0);
    st32(base, (R(5) + 16), R(4));
    st32(base, (R(3) + 12), R(0));
    return;
    goto L_800D2258;
L_800D2230:;
    R(0) = ld32(base, (R(4) + 8));
    R(5) = R(4) |R(4);
    cr_cmp_u(ctx, 0, R(0), R(3));
    R(4) = R(0) |R(0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D2258; }
    R(4) = ld32(base, (R(3) + 8));
    R(0) = (0 + 0);
    st32(base, (R(5) + 8), R(4));
    st32(base, (R(3) + 12), R(0));
    return;
L_800D2258:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800D2230; }
}

/* getAngle__5dPc_cCFv (getAngle__5dPc_cCFv, 288 bytes) */
static void pf_getAngle__5dPc_cCFv_d2270(GM_CTX) {
    GM_FN(0x800D2270); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = ld32(base, (R(3) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D2290; }
    R(3) = (0 + 0);
    goto L_800D2380;
L_800D2290:;
    R(4) = ld8(base, (R(5) + 32));
    R(6) = (0 + 0);
    R(0) = (R(4) + -1);
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D22C8; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D237C; }
    R(12) = ld32(base, (R(5) + 0));
    R(3) = R(5) |R(5);
    R(12) = ld32(base, (R(12) + 12));
    ctx->ctr = R(12);
    GM_CALLV(0x800D22C0u, ctx->ctr, 0);
    R(6) = R(3) |R(3);
    goto L_800D237C;
L_800D22C8:;
    R(6) = ld8(base, (R(3) + 46));
    R(4) = ld32(base, (R(5) + 44));
    R(0) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(2) + -26240); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = R(4) + R(0);
    goto L_800D22F0;
L_800D22E0:;
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D22FC; }
    R(4) = (R(4) + -4);
    R(6) = (R(6) + -1);
L_800D22F0:;
    { uint32_t ea_ = (R(4) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800D22E0; }
L_800D22FC:;
    R(4) = ld32(base, (R(5) + 44));
    R(0) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    { uint32_t ea_ = (R(4) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d / ctx->f[1].d);
    if ((!CR_BIT(ctx, 2))) { goto L_800D2328; }
    R(3) = ld32(base, (R(5) + 48));
    R(0) = rotl32(R(6), 1) & 0xFFFFFFFEu;
    R(6) = (int16_t)ld16(base, (R(3) + R(0)));
    goto L_800D237C;
L_800D2328:;
    R(0) = (R(6) + -1);
    R(4) = ld32(base, (R(5) + 48));
    R(0) = rotl32(R(0), 1) & 0xFFFFFFFEu;
    R(3) = rotl32(R(6), 1) & 0xFFFFFFFEu;
    R(5) = (int16_t)ld16(base, (R(4) + R(0)));
    R(0) = (0 + 0x43300000u);
    R(3) = (int16_t)ld16(base, (R(4) + R(3)));
    st32(base, (f + 8), R(0));
    R(0) = R(3) - R(5);
    { uint32_t ea_ = (R(2) + -26216); ctx->f[1].u = ld64(base, ea_); }
    R(0) = (int16_t)R(0);
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    { uint32_t ea_ = (f + 8); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 16); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 20));
    R(0) = R(0) + R(5);
    R(6) = (int16_t)R(0);
L_800D237C:;
    R(3) = R(6) |R(6);
L_800D2380:;
    R(0) = lr;
}

/* fn_800D23B0 (fn_800D23B0, 72 bytes) */
static void pf_m_d23b0(GM_CTX) {
    R(0) = ld8(base, (R(3) + 33));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) return;
    R(4) = ld32(base, (R(13) + -22168));
    st32(base, (R(3) + 8), R(4));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    st32(base, (R(13) + -22168), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_800D23E0; }
    R(0) = ld32(base, (R(13) + -22164));
    st32(base, (R(3) + 12), R(0));
    st32(base, (R(13) + -22164), R(3));
    goto L_800D23EC;
L_800D23E0:;
    R(0) = ld32(base, (R(4) + 12));
    st32(base, (R(3) + 12), R(0));
    st32(base, (R(4) + 12), R(3));
L_800D23EC:;
    R(0) = (0 + 1);
    st8(base, (R(3) + 33), R(0));
}

/* fn_800D2400 (fn_800D2400, 84 bytes) */
static void pf_m_d2400(GM_CTX) {
    R(0) = ld8(base, (R(3) + 33));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) return;
    R(4) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D2424; }
    R(0) = ld32(base, (R(3) + 12));
    st32(base, (R(4) + 12), R(0));
    goto L_800D242C;
L_800D2424:;
    R(0) = ld32(base, (R(3) + 12));
    st32(base, (R(13) + -22164), R(0));
L_800D242C:;
    R(4) = ld32(base, (R(3) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D2444; }
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (R(4) + 8), R(0));
    goto L_800D244C;
L_800D2444:;
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (R(13) + -22168), R(0));
L_800D244C:;
    GM_TAIL(0x800D2390u, 0); return;
}

/* fn_800D2510 (fn_800D2510, 252 bytes) */
static void pf_m_d2510(GM_CTX) {
    R(0) = ld8(base, (R(3) + 60));
    R(8) = ld32(base, (R(3) + 44));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(2) + -26240); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    R(9) = R(8) + R(0);
    cr_cmp_u(ctx, 1, R(8), R(9));
    if ((!CR_BIT(ctx, 4))) { goto L_800D2604; }
    R(5) = R(9) - R(8);
    R(6) = (R(9) + -32);
    R(4) = (R(5) + 3);
    { int32_t v_ = (int32_t)R(4); ctx->xer_ca = v_ < 0 && (v_ & 0x3u) != 0; R(0) = (v_ >> 2); }
    { uint64_t t_ = (uint64_t)(R(0)) + (0) + ctx->xer_ca; R(0) = t_; ctx->xer_ca = (t_ >> 32); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 8);
    if ((!CR_BIT(ctx, 1))) { goto L_800D25DC; }
    R(7) = (0 + 0);
    if ((CR_BIT(ctx, 5))) { goto L_800D2574; }
    R(0) = R(5) & 0x80000000u;
    CR0(ctx, R(0));
    R(5) = (0 + 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800D2568; }
    R(0) = R(4) & 0x80000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D2568; }
    R(5) = (0 + 0);
L_800D2568:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D2574; }
    R(7) = (0 + 1);
L_800D2574:;
    cr_cmp_s(ctx, 0, (int32_t)R(7), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D25DC; }
    R(0) = (R(6) + 31);
    R(0) = R(0) - R(8);
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    ctx->ctr = R(0);
    cr_cmp_u(ctx, 0, R(8), R(6));
    if ((!CR_BIT(ctx, 0))) { goto L_800D25DC; }
L_800D2594:;
    { uint32_t ea_ = (R(8) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(8) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d + ctx->f[1].d);
    { uint32_t ea_ = (R(8) + 8); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(8) + 12); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(8) + 16); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d + ctx->f[0].d);
    { uint32_t ea_ = (R(8) + 20); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(8) + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(8) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(8) = (R(8) + 32);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d + ctx->f[5].d);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d + ctx->f[4].d);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d + ctx->f[3].d);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d + ctx->f[2].d);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d + ctx->f[1].d);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d + ctx->f[0].d);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800D2594; }
L_800D25DC:;
    R(0) = (R(9) + 3);
    R(0) = R(0) - R(8);
    R(0) = rotl32(R(0), 30) & 0x3FFFFFFFu;
    ctx->ctr = R(0);
    cr_cmp_u(ctx, 0, R(8), R(9));
    if ((!CR_BIT(ctx, 0))) { goto L_800D2604; }
L_800D25F4:;
    { uint32_t ea_ = (R(8) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(8) = (R(8) + 4);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d + ctx->f[0].d);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800D25F4; }
L_800D2604:;
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[6].d); }
}

/* fn_800D2690 (fn_800D2690, 276 bytes) */
static void pf_m_d2690(GM_CTX) {
    GM_FN(0x800D2690); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(5) = ld32(base, (R(3) + 4));
    R(23) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 40));
    R(24) = (0 + 0);
    { uint32_t ea_ = (R(5) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 0); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld32(base, (R(3) + 40));
    { uint32_t ea_ = (R(5) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); stfs(base, ea_, ctx->f[0].d); }
    R(27) = ld8(base, (R(3) + 60));
    R(26) = ld32(base, (R(3) + 48));
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    R(25) = ld32(base, (R(3) + 44));
    if ((CR_BIT(ctx, 2))) { goto L_800D2774; }
    { uint32_t ea_ = (R(2) + -26244); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(30) = (f + 10);
    R(29) = (f + 8);
    R(28) = (0 + 0);
    goto L_800D276C;
L_800D2700:;
    R(31) = (int16_t)ld16(base, (R(26) + 0));
    st16(base, (f + 10), R(31));
    { uint32_t ea_ = (R(30) + 0); psq_l(ctx, base, 0, ea_, 1, 3); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d * ctx->f[0].d);
    GM_CALLV(0x800D2714u, 0x80237BD0u, 0);
    st16(base, (f + 8), R(31));
    ctx->f[31].u = ctx->f[1].u;
    { uint32_t ea_ = (R(29) + 0); psq_l(ctx, base, 0, ea_, 1, 3); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d * ctx->f[0].d);
    GM_CALLV(0x800D2728u, 0x80237C40u, 0);
    { uint32_t ea_ = (R(25) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(26) = (R(26) + 2);
    R(0) = ld32(base, (R(23) + 40));
    R(25) = (R(25) + 4);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d * ctx->f[31].d);
    R(24) = (R(24) + 1);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(28) + R(0)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(0) + R(28);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(23) + 40));
    R(3) = R(0) + R(28);
    R(28) = (R(28) + 8);
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
L_800D276C:;
    cr_cmp_u(ctx, 0, R(24), R(27));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800D2700; }
L_800D2774:;
    R(3) = R(23) |R(23);
    GM_CALLV(0x800D277Cu, 0x800D27B0u, 0);
    R(11) = (f + 64);
    R(0) = lr;
}

/* fn_800D27B0 (fn_800D27B0, 564 bytes) */
static void pf_m_d27b0(GM_CTX) {
    GM_FN(0x800D27B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 80);
    R(27) = ld32(base, (R(3) + 16));
    R(25) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D2984; }
    { uint32_t ea_ = (R(2) + -26240); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(30) = (f + 10);
    { uint32_t ea_ = (R(2) + -26244); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(29) = (f + 8);
    { uint32_t ea_ = (R(2) + -26260); ctx->f[25].d = ctx->ps1[25] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -26264); ctx->f[26].d = ctx->ps1[26] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -26256); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -26252); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -26248); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    goto L_800D297C;
L_800D2844:;
    R(26) = ld8(base, (R(27) + 46));
    R(3) = ld32(base, (R(25) + 44));
    R(0) = rotl32(R(26), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(27) + 32); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
    R(3) = R(3) + R(0);
    goto L_800D2874;
    R(0) = R(0) | 0x0u;
L_800D2860:;
    cr_cmp_s(ctx, 0, (int32_t)R(26), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D2880; }
    { uint32_t ea_ = (R(27) + 28); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
    R(3) = (R(3) + -4);
    R(26) = (R(26) + -1);
L_800D2874:;
    { uint32_t ea_ = (R(3) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800D2860; }
L_800D2880:;
    R(28) = ld32(base, (R(27) + 4));
    R(0) = rotl32(R(26), 1) & 0xFFFFFFFEu;
    R(3) = ld32(base, (R(25) + 48));
    { uint32_t ea_ = (R(28) + 212); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (int16_t)ld16(base, (R(3) + R(0)));
    st16(base, (f + 10), R(31));
    ctx->f[23].d = ctx->ps1[23] = frsp(ctx->f[23].d + ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 0); psq_l(ctx, base, 0, ea_, 1, 3); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[0].d);
    GM_CALLV(0x800D28A8u, 0x80237BD0u, 0);
    st16(base, (f + 8), R(31));
    ctx->f[24].u = ctx->f[1].u;
    { uint32_t ea_ = (R(29) + 0); psq_l(ctx, base, 0, ea_, 1, 3); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[0].d);
    GM_CALLV(0x800D28BCu, 0x80237C40u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[23].d * ctx->f[1].d);
    { uint32_t ea_ = (R(28) + 180); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(25) + 40));
    R(0) = rotl32(R(26), 3) & 0xFFFFFFF8u;
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[23].d * ctx->f[24].d);
    { uint32_t ea_ = (R(28) + 188); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(3) + R(0);
    ctx->f[3].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d + ctx->f[0].d);
    { uint32_t ea_ = (R(28) + 184); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[5].d + ctx->f[4].d);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[4].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[25].d * ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[27].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[26].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 0))) { goto L_800D2924; }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[27].d); }
    goto L_800D2930;
L_800D2924:;
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[28].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800D2930; }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[28].d); }
L_800D2930:;
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[26].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D2944; }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[26].d); }
    goto L_800D2950;
L_800D2944:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800D2950; }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[29].d); }
L_800D2950:;
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 172); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 176); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 180); stfs(base, ea_, ctx->f[0].d); }
    R(27) = ld32(base, (R(27) + 8));
L_800D297C:;
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800D2844; }
L_800D2984:;
    R(11) = (f + 80);
    R(0) = lr;
}

/* fn_800D29F0 (fn_800D29F0, 96 bytes) */
static void pf_m_d29f0(GM_CTX) {
    GM_FN(0x800D29F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80310000u);
    R(4) = (R(4) + 31484);
    R(31) = (R(3) + 4);
    R(30) = R(3) |R(3);
    st32(base, (R(3) + 0), R(4));
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D2A20u, 0x802D7AA0u, 0);
    R(3) = (0 + 0x80310000u);
    R(0) = (0 + 0);
    R(3) = (R(3) + -30080);
    st32(base, (R(31) + 0), R(3));
    R(3) = R(30) |R(30);
    st32(base, (R(30) + 312), R(0));
    R(0) = lr;
}

/* fn_800D2AC0 (fn_800D2AC0, 208 bytes) */
static void pf_m_d2ac0(GM_CTX) {
    GM_FN(0x800D2AC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld32(base, (R(3) + 312));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D2AE0; }
    R(3) = (0 + 0);
    goto L_800D2B80;
L_800D2AE0:;
    R(0) = (0 + 1);
    st32(base, (R(3) + 308), R(4));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 4);
    st32(base, (R(3) + 312), R(0));
    { uint32_t ea_ = (R(5) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 280); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 292); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 296); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 300); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(3) + 304), R(6));
    if ((!CR_BIT(ctx, 2))) { goto L_800D2B54; }
    R(12) = ld32(base, (R(3) + 4));
    R(5) = (0 + 0x80310000u);
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(6) = (R(3) + 280);
    R(12) = ld32(base, (R(12) + 160));
    R(5) = (R(5) + 31452);
    R(4) = ld32(base, (R(5) + R(0)));
    R(8) = (R(3) + 292);
    R(5) = (0 + 0);
    R(7) = (0 + 0);
    ctx->ctr = R(12);
    R(3) = (R(3) + 4);
    GM_CALLV(0x800D2B50u, ctx->ctr, 0);
    goto L_800D2B7C;
L_800D2B54:;
    R(5) = (0 + 0x80310000u);
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(5) = (R(5) + 31452);
    R(6) = (R(3) + 280);
    R(4) = ld32(base, (R(5) + R(0)));
    R(8) = (R(3) + 292);
    R(5) = (0 + 0);
    R(7) = (0 + 0);
    R(3) = (R(3) + 4);
    GM_CALLV(0x800D2B7Cu, 0x8008FAE0u, 0);
L_800D2B7C:;
    R(3) = (0 + 1);
L_800D2B80:;
    R(0) = lr;
}

/* fn_800D2B90 (fn_800D2B90, 144 bytes) */
static void pf_m_d2b90(GM_CTX) {
    GM_FN(0x800D2B90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 312));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800D2C0C; }
    { uint32_t ea_ = (R(3) + 284); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (f + 8);
    { uint32_t ea_ = (R(2) + -26200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 280); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[0].d);
    R(3) = ld8(base, (R(3) + 304));
    GM_CALLV(0x800D2BCCu, 0x80075270u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800D2BDC; }
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 284); stfs(base, ea_, ctx->f[0].d); }
L_800D2BDC:;
    R(12) = ld32(base, (R(31) + 4));
    R(3) = (R(31) + 4);
    R(4) = (R(31) + 280);
    R(6) = (R(31) + 292);
    R(12) = ld32(base, (R(12) + 176));
    R(5) = (0 + 0);
    ctx->ctr = R(12);
    GM_CALLV(0x800D2BFCu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D2C0C; }
    R(0) = (0 + 0);
    st32(base, (R(31) + 312), R(0));
L_800D2C0C:;
    R(0) = lr;
}

/* fn_800D2C20 (fn_800D2C20, 92 bytes) */
static void pf_m_d2c20(GM_CTX) {
    GM_FN(0x800D2C20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80310000u);
    R(4) = (0 + 0x800D0000u);
    R(5) = (0 + 0x800D0000u);
    R(6) = (R(6) + 31472);
    R(4) = (R(4) + 10736);
    R(31) = R(3) |R(3);
    R(5) = (R(5) + 10832);
    R(7) = (0 + 10);
    st32(base, (R(3) + 0), R(6));
    R(6) = (0 + 316);
    R(3) = (R(3) + 4);
    GM_CALLV(0x800D2C60u, 0x802DC9A0u, 0);
    st32(base, (R(13) + -22160), R(31));
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* setEffect__14dPyEffectMng_cFQ211dPyEffect_c6Type_eR7mVec3_cfUc (setEffect__14dPyEffectMng_cFQ211dPyEffect_c6Type_eR7mVec3_cfUc, 136 bytes) */
static void pf_setEffect__14dPyEffectMng_cFQ211dPyEffec_d2cf0(GM_CTX) {
    GM_FN(0x800D2CF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 40);
    ctx->f[31].u = ctx->f[1].u;
    R(27) = R(4) |R(4);
    R(28) = R(5) |R(5);
    R(29) = R(6) |R(6);
    R(31) = (R(3) + 4);
    R(30) = (0 + 0);
L_800D2D20:;
    ctx->f[1].u = ctx->f[31].u;
    R(3) = R(31) |R(31);
    R(4) = R(27) |R(27);
    R(5) = R(28) |R(28);
    R(6) = R(29) |R(29);
    GM_CALLV(0x800D2D38u, 0x800D2AC0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D2D48; }
    R(3) = (0 + 1);
    goto L_800D2D5C;
L_800D2D48:;
    R(30) = (R(30) + 1);
    R(31) = (R(31) + 316);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 10);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800D2D20; }
    R(3) = (0 + 0);
L_800D2D5C:;
    R(11) = (f + 40);
    R(0) = lr;
}

/* fn_800D2D80 (fn_800D2D80, 76 bytes) */
static void pf_m_d2d80(GM_CTX) {
    GM_FN(0x800D2D80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (R(3) + 4);
    R(30) = (0 + 0);
L_800D2D9C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D2DA4u, 0x800D2B90u, 0);
    R(30) = (R(30) + 1);
    R(31) = (R(31) + 316);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 10);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800D2D9C; }
    R(0) = lr;
}

/* fn_800D2DD0 (fn_800D2DD0, 472 bytes) */
static void pf_m_d2dd0(GM_CTX) {
    GM_FN(0x800D2DD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(27) = R(3) |R(3);
    GM_CALLV(0x800D2DECu, 0x800D5330u, 0);
    R(3) = (0 + 0x80310000u);
    R(28) = (0 + 0);
    R(3) = (R(3) + 32048);
    R(30) = (R(27) + 536);
    st32(base, (R(27) + 0), R(3));
    R(3) = R(30) |R(30);
    st32(base, (R(27) + 524), R(28));
    st32(base, (R(27) + 528), R(28));
    st32(base, (R(27) + 532), R(28));
    GM_CALLV(0x800D2E14u, 0x802D7AA0u, 0);
    R(29) = (0 + 0x80330000u);
    R(31) = (R(27) + 832);
    R(29) = (R(29) + -26280);
    st32(base, (R(30) + 0), R(29));
    R(3) = R(31) |R(31);
    st32(base, (R(30) + 276), R(28));
    st32(base, (R(30) + 280), R(28));
    st8(base, (R(30) + 284), R(28));
    st8(base, (R(30) + 285), R(28));
    st32(base, (R(30) + 288), R(28));
    st32(base, (R(30) + 292), R(28));
    GM_CALLV(0x800D2E44u, 0x802D7AA0u, 0);
    R(4) = (0 + 0x800D0000u);
    R(5) = (0 + 0x800D0000u);
    st32(base, (R(31) + 0), R(29));
    R(3) = (R(27) + 1128);
    R(4) = (R(4) + 12336);
    R(5) = (R(5) + 12400);
    st32(base, (R(31) + 276), R(28));
    R(6) = (0 + 128);
    R(7) = (0 + 4);
    st32(base, (R(31) + 280), R(28));
    st8(base, (R(31) + 284), R(28));
    st8(base, (R(31) + 285), R(28));
    st32(base, (R(31) + 288), R(28));
    st32(base, (R(31) + 292), R(28));
    GM_CALLV(0x800D2E80u, 0x802DC9A0u, 0);
    R(29) = (0 + 0x80330000u);
    st32(base, (R(27) + 1644), R(28));
    R(29) = (R(29) + -27176);
    R(3) = (R(27) + 1652);
    st32(base, (R(27) + 1640), R(29));
    st32(base, (R(27) + 1648), R(28));
    GM_CALLV(0x800D2E9Cu, 0x8016A5E0u, 0);
    R(30) = (0 + 0x80330000u);
    st32(base, (R(27) + 1680), R(28));
    R(30) = (R(30) + -27320);
    R(3) = (R(27) + 1696);
    st32(base, (R(27) + 1640), R(30));
    st32(base, (R(27) + 1684), R(29));
    st32(base, (R(27) + 1688), R(28));
    st32(base, (R(27) + 1692), R(28));
    GM_CALLV(0x800D2EC0u, 0x8016A5E0u, 0);
    R(31) = (0 + 0x80330000u);
    st32(base, (R(27) + 1724), R(28));
    R(31) = (R(31) + -27368);
    R(3) = (R(27) + 1740);
    st32(base, (R(27) + 1684), R(31));
    st32(base, (R(27) + 1728), R(29));
    st32(base, (R(27) + 1732), R(28));
    st32(base, (R(27) + 1736), R(28));
    GM_CALLV(0x800D2EE4u, 0x8016A5E0u, 0);
    st32(base, (R(27) + 1728), R(30));
    R(3) = (R(27) + 1784);
    st32(base, (R(27) + 1768), R(28));
    st32(base, (R(27) + 1772), R(29));
    st32(base, (R(27) + 1776), R(28));
    st32(base, (R(27) + 1780), R(28));
    GM_CALLV(0x800D2F00u, 0x8016A5E0u, 0);
    st32(base, (R(27) + 1772), R(30));
    R(3) = (R(27) + 1828);
    st32(base, (R(27) + 1812), R(28));
    st32(base, (R(27) + 1816), R(29));
    st32(base, (R(27) + 1820), R(28));
    st32(base, (R(27) + 1824), R(28));
    GM_CALLV(0x800D2F1Cu, 0x8016A5E0u, 0);
    st32(base, (R(27) + 1816), R(30));
    R(3) = (R(27) + 1872);
    st32(base, (R(27) + 1856), R(28));
    st32(base, (R(27) + 1860), R(29));
    st32(base, (R(27) + 1864), R(28));
    st32(base, (R(27) + 1868), R(28));
    GM_CALLV(0x800D2F38u, 0x8016A5E0u, 0);
    { uint32_t ea_ = (R(2) + -26188); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80310000u);
    R(4) = (0 + 0x80310000u);
    R(0) = (0 + 1024);
    R(5) = (R(5) + 32264);
    st32(base, (R(27) + 1860), R(31));
    R(4) = (R(4) + 32240);
    R(11) = (f + 32);
    st32(base, (R(27) + 1900), R(28));
    R(3) = R(27) |R(27);
    st32(base, (R(27) + 1904), R(28));
    st32(base, (R(27) + 1908), R(28));
    st32(base, (R(27) + 1916), R(28));
    st16(base, (R(27) + 1920), R(28));
    st16(base, (R(27) + 1922), R(0));
    { uint32_t ea_ = (R(27) + 1924); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 1928); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 1932); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 1936); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(27) + 1940), R(5));
    st32(base, (R(27) + 1944), R(27));
    st32(base, (R(27) + 1948), R(4));
    st32(base, (R(27) + 1952), R(27));
    R(0) = lr;
}

/* fn_800D3030 (fn_800D3030, 56 bytes) */
static void pf_m_d3030(GM_CTX) {
    GM_FN(0x800D3030); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800D3048u, 0x80169CD0u, 0);
    R(3) = (R(31) + 64);
    GM_CALLV(0x800D3050u, 0x80169CD0u, 0);
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_800D3070 (fn_800D3070, 104 bytes) */
static void pf_m_d3070(GM_CTX) {
    GM_FN(0x800D3070); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800D30BC; }
    R(4) = (0 + -1);
    R(3) = (R(3) + 64);
    GM_CALLV(0x800D30A0u, 0x80169D20u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + -1);
    GM_CALLV(0x800D30ACu, 0x80169D20u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800D30BC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x800D30BCu, 0x802B9280u, 0);
L_800D30BC:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_800D30E0 (fn_800D30E0, 292 bytes) */
static void pf_m_d30e0(GM_CTX) {
    GM_FN(0x800D30E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800D31E4; }
    R(4) = (0 + -1);
    R(3) = (R(3) + 1860);
    GM_CALLV(0x800D3114u, 0x80165E70u, 0);
    R(3) = (R(29) + 1816);
    R(4) = (0 + -1);
    GM_CALLV(0x800D3120u, 0x80166A70u, 0);
    R(3) = (R(29) + 1772);
    R(4) = (0 + -1);
    GM_CALLV(0x800D312Cu, 0x80166A70u, 0);
    R(3) = (R(29) + 1728);
    R(4) = (0 + -1);
    GM_CALLV(0x800D3138u, 0x80166A70u, 0);
    R(3) = (R(29) + 1684);
    R(4) = (0 + -1);
    GM_CALLV(0x800D3144u, 0x80165E70u, 0);
    R(3) = (R(29) + 1640);
    R(4) = (0 + -1);
    GM_CALLV(0x800D3150u, 0x80166A70u, 0);
    R(4) = (0 + 0x800D0000u);
    R(3) = (R(29) + 1128);
    R(4) = (R(4) + 12400);
    R(5) = (0 + 128);
    R(6) = (0 + 4);
    GM_CALLV(0x800D3168u, 0x802DCA98u, 0);
    { uint32_t a_ = R(29); R(31) = a_ + 0x340u; ctx->xer_ca = R(31) < a_; }
    CR0(ctx, R(31));
    if ((CR_BIT(ctx, 2))) { goto L_800D3198; }
    R(4) = (0 + 0x80330000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + -26280);
    st32(base, (R(31) + 0), R(4));
    GM_CALLV(0x800D3184u, 0x8016D4B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D3198; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x800D3198u, 0x802D7B20u, 0);
L_800D3198:;
    { uint32_t a_ = R(29); R(31) = a_ + 0x218u; ctx->xer_ca = R(31) < a_; }
    CR0(ctx, R(31));
    if ((CR_BIT(ctx, 2))) { goto L_800D31C8; }
    R(4) = (0 + 0x80330000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + -26280);
    st32(base, (R(31) + 0), R(4));
    GM_CALLV(0x800D31B4u, 0x8016D4B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D31C8; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x800D31C8u, 0x802D7B20u, 0);
L_800D31C8:;
    R(3) = R(29) |R(29);
    R(4) = (0 + 0);
    GM_CALLV(0x800D31D4u, 0x800D54E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800D31E4; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x800D31E4u, 0x802B9280u, 0);
L_800D31E4:;
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* fn_800D3210 (fn_800D3210, 96 bytes) */
static void pf_m_d3210(GM_CTX) {
    GM_FN(0x800D3210); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800D3228u, 0x800D32F0u, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 188));
    ctx->ctr = R(12);
    GM_CALLV(0x800D323Cu, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 184));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3250u, ctx->ctr, 0);
    { uint32_t ea_ = (R(31) + 1936); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 1932); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 1928); stfs(base, ea_, ctx->f[1].d); }
    R(0) = lr;
}

/* fn_800D3280 (fn_800D3280, 112 bytes) */
static void pf_m_d3280(GM_CTX) {
    GM_FN(0x800D3280); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (R(3) + 1128);
    R(30) = (0 + 0);
    R(29) = R(3) |R(3);
L_800D32A4:;
    R(3) = R(31) |R(31);
    R(4) = (R(29) + 1940);
    GM_CALLV(0x800D32B0u, 0x8016A000u, 0);
    R(30) = (R(30) + 1);
    R(31) = (R(31) + 128);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800D32A4; }
    R(3) = (R(29) + 1448);
    R(4) = (R(29) + 1948);
    GM_CALLV(0x800D32CCu, 0x8016A000u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x800D32D4u, 0x800D3AD0u, 0);
    R(0) = lr;
}

/* fn_800D3380 (fn_800D3380, 860 bytes) */
static void pf_m_d3380(GM_CTX) {
    GM_FN(0x800D3380); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 112);
    R(31) = R(3) |R(3);
    R(0) = (0 + 0);
    st32(base, (f + 52), R(0));
    R(26) = R(31) |R(31);
    R(30) = (f + 56);
    R(28) = (R(3) + 1192);
    R(27) = (R(3) + 1128);
    R(25) = (0 + 0);
    R(29) = (0 + 0);
L_800D33B8:;
    R(0) = ld32(base, (R(31) + 1912));
    R(3) = (R(31) + 524);
    R(4) = R(0) + R(29);
    R(4) = ld32(base, (R(4) + 24));
    GM_CALLV(0x800D33CCu, 0x80239E30u, 0);
    st32(base, (f + 48), R(3));
    R(3) = R(28) |R(28);
    R(4) = (f + 48);
    R(5) = (R(31) + 4);
    R(6) = (0 + 2427);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800D33ECu, 0x80169D90u, 0);
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800D33F8u, 0x800D5B90u, 0);
    R(0) = ld32(base, (R(31) + 1912));
    R(3) = (R(31) + 524);
    R(4) = R(0) + R(29);
    R(4) = ld32(base, (R(4) + 8));
    GM_CALLV(0x800D340Cu, 0x80239E30u, 0);
    st32(base, (f + 52), R(3));
    R(4) = (f + 44);
    R(5) = (R(31) + 4);
    R(6) = (0 + 2363);
    st32(base, (f + 44), R(3));
    R(3) = R(27) |R(27);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800D3430u, 0x80169D90u, 0);
    R(3) = R(31) |R(31);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800D343Cu, 0x800D5B90u, 0);
    R(3) = (f + 52);
    R(4) = (0 + 3);
    GM_CALLV(0x800D3448u, 0x8023B2A0u, 0);
    { uint32_t ea_ = (R(3) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 56);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800D3468u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(26) + 2020); stfs(base, ea_, ctx->f[1].d); }
    R(3) = (f + 52);
    R(4) = (0 + 4);
    { uint32_t ea_ = (R(30) + 0); psq_l(ctx, base, 0, ea_, 0, 0); }
    { uint32_t ea_ = (f + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { double a_ = frsp(ctx->f[0].d * ctx->f[0].d), b_ = frsp(ctx->ps1[0] * ctx->ps1[0]); ctx->f[0].d = a_; ctx->ps1[0] = b_; }
    { double a_ = frsp(ctx->f[1].d * ctx->f[1].d + ctx->f[0].d), b_ = frsp(ctx->ps1[1] * ctx->ps1[1] + ctx->ps1[0]); ctx->f[1].d = a_; ctx->ps1[1] = b_; }
    { double a_ = frsp(ctx->f[1].d + ctx->ps1[0]), b_ = frsp(ctx->ps1[0]); ctx->f[1].d = a_; ctx->ps1[1] = b_; }
    { uint32_t ea_ = (R(26) + 2028); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x800D3490u, 0x8023B2A0u, 0);
    { uint32_t ea_ = (R(3) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 56);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800D34B0u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(26) + 2024); stfs(base, ea_, ctx->f[1].d); }
    R(3) = (f + 52);
    R(4) = (0 + 6);
    { uint32_t ea_ = (R(30) + 0); psq_l(ctx, base, 0, ea_, 0, 0); }
    { uint32_t ea_ = (f + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { double a_ = frsp(ctx->f[0].d * ctx->f[0].d), b_ = frsp(ctx->ps1[0] * ctx->ps1[0]); ctx->f[0].d = a_; ctx->ps1[0] = b_; }
    { double a_ = frsp(ctx->f[1].d * ctx->f[1].d + ctx->f[0].d), b_ = frsp(ctx->ps1[1] * ctx->ps1[1] + ctx->ps1[0]); ctx->f[1].d = a_; ctx->ps1[1] = b_; }
    { double a_ = frsp(ctx->f[1].d + ctx->ps1[0]), b_ = frsp(ctx->ps1[0]); ctx->f[1].d = a_; ctx->ps1[1] = b_; }
    { uint32_t ea_ = (R(26) + 2032); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x800D34D8u, 0x8023B2A0u, 0);
    { uint32_t ea_ = (R(3) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 56);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800D34F8u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(26) + 1956); stfs(base, ea_, ctx->f[1].d); }
    R(3) = (f + 52);
    R(4) = (0 + 7);
    { uint32_t ea_ = (R(30) + 0); psq_l(ctx, base, 0, ea_, 0, 0); }
    { uint32_t ea_ = (f + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { double a_ = frsp(ctx->f[0].d * ctx->f[0].d), b_ = frsp(ctx->ps1[0] * ctx->ps1[0]); ctx->f[0].d = a_; ctx->ps1[0] = b_; }
    { double a_ = frsp(ctx->f[1].d * ctx->f[1].d + ctx->f[0].d), b_ = frsp(ctx->ps1[1] * ctx->ps1[1] + ctx->ps1[0]); ctx->f[1].d = a_; ctx->ps1[1] = b_; }
    { double a_ = frsp(ctx->f[1].d + ctx->ps1[0]), b_ = frsp(ctx->ps1[0]); ctx->f[1].d = a_; ctx->ps1[1] = b_; }
    { uint32_t ea_ = (R(26) + 1964); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x800D3520u, 0x8023B2A0u, 0);
    { uint32_t ea_ = (R(3) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 56);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800D3540u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(26) + 1960); stfs(base, ea_, ctx->f[1].d); }
    R(25) = (R(25) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(25), 4);
    R(29) = (R(29) + 4);
    { uint32_t ea_ = (R(30) + 0); psq_l(ctx, base, 0, ea_, 0, 0); }
    R(28) = (R(28) + 128);
    { uint32_t ea_ = (f + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(27) = (R(27) + 128);
    { double a_ = frsp(ctx->f[0].d * ctx->f[0].d), b_ = frsp(ctx->ps1[0] * ctx->ps1[0]); ctx->f[0].d = a_; ctx->ps1[0] = b_; }
    { double a_ = frsp(ctx->f[1].d * ctx->f[1].d + ctx->f[0].d), b_ = frsp(ctx->ps1[1] * ctx->ps1[1] + ctx->ps1[0]); ctx->f[1].d = a_; ctx->ps1[1] = b_; }
    { double a_ = frsp(ctx->f[1].d + ctx->ps1[0]), b_ = frsp(ctx->ps1[0]); ctx->f[1].d = a_; ctx->ps1[1] = b_; }
    { uint32_t ea_ = (R(26) + 1968); stfs(base, ea_, ctx->f[1].d); }
    R(26) = (R(26) + 16);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800D33B8; }
    R(3) = (R(31) + 528);
    R(4) = (R(13) + -31224);
    GM_CALLV(0x800D3584u, 0x8023A0B0u, 0);
    R(0) = ld32(base, (f + 52));
    R(30) = R(3) |R(3);
    st32(base, (f + 36), R(3));
    R(3) = (R(31) + 40);
    R(4) = (f + 40);
    R(5) = (f + 36);
    st32(base, (f + 40), R(0));
    R(6) = (R(31) + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x800D35ACu, 0x801650D0u, 0);
    R(0) = ld32(base, (f + 52));
    R(3) = (R(31) + 96);
    st32(base, (f + 28), R(30));
    R(4) = (f + 32);
    R(5) = (f + 28);
    R(6) = (R(31) + 4);
    st32(base, (f + 32), R(0));
    R(7) = (0 + 0);
    GM_CALLV(0x800D35D0u, 0x801650D0u, 0);
    R(0) = ld32(base, (f + 52));
    R(3) = (R(31) + 152);
    st32(base, (f + 24), R(0));
    R(4) = (f + 24);
    R(6) = (R(31) + 4);
    R(5) = (0 + 2);
    R(7) = (0 + 0);
    GM_CALLV(0x800D35F0u, 0x80165520u, 0);
    { uint32_t ea_ = (R(2) + -26188); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 152);
    R(5) = (R(31) + 40);
    R(4) = (0 + 0);
    GM_CALLV(0x800D3604u, 0x801656C0u, 0);
    { uint32_t ea_ = (R(2) + -26188); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 152);
    R(5) = (R(31) + 96);
    R(4) = (0 + 1);
    GM_CALLV(0x800D3618u, 0x801656C0u, 0);
    R(4) = ld32(base, (R(31) + 1912));
    R(3) = (R(31) + 524);
    R(4) = ld32(base, (R(4) + 8));
    GM_CALLV(0x800D3628u, 0x80239E30u, 0);
    st32(base, (f + 52), R(3));
    R(4) = (0 + 0x80310000u);
    R(4) = (R(4) + 31544);
    R(3) = (R(31) + 528);
    R(0) = ld32(base, (R(31) + 384));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(4) + R(0)));
    GM_CALLV(0x800D3648u, 0x8023A190u, 0);
    R(0) = ld32(base, (f + 52));
    R(4) = (f + 20);
    st32(base, (f + 16), R(3));
    R(3) = (R(31) + 1684);
    R(5) = (f + 16);
    R(6) = (R(31) + 4);
    st32(base, (f + 20), R(0));
    R(7) = (0 + 0);
    R(8) = (0 + 1);
    GM_CALLV(0x800D3670u, 0x80165C30u, 0);
    R(4) = ld32(base, (R(31) + 1912));
    R(3) = (R(31) + 524);
    R(4) = ld32(base, (R(4) + 24));
    GM_CALLV(0x800D3680u, 0x80239E30u, 0);
    R(0) = ld32(base, (R(31) + 384));
    R(4) = (0 + 0x80310000u);
    R(30) = R(3) |R(3);
    R(3) = (R(31) + 528);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + 31588);
    R(4) = ld32(base, (R(4) + R(0)));
    GM_CALLV(0x800D36A0u, 0x8023A190u, 0);
    st32(base, (f + 8), R(3));
    R(3) = (R(31) + 1860);
    R(4) = (f + 12);
    R(5) = (f + 8);
    st32(base, (f + 12), R(30));
    R(6) = (R(31) + 4);
    R(7) = (0 + 0);
    R(8) = (0 + 1);
    GM_CALLV(0x800D36C4u, 0x80165C30u, 0);
    R(11) = (f + 112);
    R(0) = lr;
}

/* fn_800D36E0 (fn_800D36E0, 328 bytes) */
static void pf_m_d36e0(GM_CTX) {
    GM_FN(0x800D36E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800D36F8u, 0x800D4CD0u, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 520), R(0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(31) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3714u, ctx->ctr, 0);
    R(4) = (R(31) + 216);
    GM_CALLV(0x800D371Cu, 0x8016A170u, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3730u, ctx->ctr, 0);
    R(4) = (0 + 0);
    GM_CALLV(0x800D3738u, 0x8016A1A0u, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(4) = (f + 152);
    R(5) = ld32(base, (R(31) + 1916));
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3754u, ctx->ctr, 0);
    { uint32_t ea_ = (R(31) + 312); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 56);
    { uint32_t ea_ = (R(31) + 316); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 320); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    GM_CALLV(0x800D3768u, 0x801C0BD0u, 0);
    R(3) = (f + 152);
    R(4) = (f + 56);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800D3778u, 0x801C0540u, 0);
    R(0) = ld32(base, (R(31) + 1904));
    R(4) = (f + 152);
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(3) = R(31) + R(0);
    R(3) = (R(3) + 1192);
    GM_CALLV(0x800D3790u, 0x8016A170u, 0);
    R(0) = ld32(base, (R(31) + 1904));
    R(4) = (0 + 0);
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(3) = R(31) + R(0);
    R(3) = (R(3) + 1192);
    GM_CALLV(0x800D37A8u, 0x8016A1A0u, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(4) = (f + 104);
    R(5) = ld32(base, (R(31) + 1916));
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800D37C4u, ctx->ctr, 0);
    R(3) = (f + 104);
    R(4) = (R(31) + 204);
    GM_CALLV(0x800D37D0u, 0x8016F130u, 0);
    R(0) = ld32(base, (R(31) + 1904));
    R(3) = (f + 8);
    R(4) = ld32(base, (R(31) + 1912));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(2) + -26184); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = R(4) + R(0);
    { uint32_t ea_ = (R(4) + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[1].u;
    ctx->f[2].u = ctx->f[0].u ^ 0x8000000000000000ull;
    GM_CALLV(0x800D37F8u, 0x801C0BD0u, 0);
    R(3) = (f + 104);
    R(4) = (f + 8);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800D3808u, 0x801C0540u, 0);
    R(3) = (f + 104);
    R(4) = (R(31) + 192);
    GM_CALLV(0x800D3814u, 0x8016F130u, 0);
    R(0) = lr;
}

/* fn_800D3830 (fn_800D3830, 100 bytes) */
static void pf_m_d3830(GM_CTX) {
    GM_FN(0x800D3830); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + 2);
    R(31) = R(3) |R(3);
    st32(base, (R(3) + 520), R(0));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D385Cu, ctx->ctr, 0);
    R(4) = (R(31) + 216);
    GM_CALLV(0x800D3864u, 0x8016A170u, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3878u, ctx->ctr, 0);
    R(4) = (0 + 0);
    GM_CALLV(0x800D3880u, 0x8016A1A0u, 0);
    R(0) = lr;
}

/* fn_800D38A0 (fn_800D38A0, 388 bytes) */
static void pf_m_d38a0(GM_CTX) {
    GM_FN(0x800D38A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800D38B8u, 0x800D5170u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D38C0u, 0x800D6A30u, 0);
    R(12) = ld32(base, (R(31) + 40));
    R(3) = (R(31) + 40);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800D38D4u, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = (R(31) + 96);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800D38E8u, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 1860));
    R(3) = (R(31) + 1860);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800D38FCu, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 1684));
    R(3) = (R(31) + 1684);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3910u, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3924u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3934u, ctx->ctr, 0);
    R(0) = ld32(base, (R(31) + 1904));
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(3) = R(31) + R(0);
    { uint32_t ea_ = R(3) + 1192; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3950u, ctx->ctr, 0);
    R(0) = ld32(base, (R(31) + 368));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800D39DC; }
    R(0) = ld32(base, (R(31) + 372));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D398C; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D3970u, 0x800D3CB0u, 0);
    { uint32_t ea_ = (R(2) + -26184); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 1);
    GM_CALLV(0x800D397Cu, 0x80166F10u, 0);
    R(3) = ld32(base, (R(31) + 372));
    R(0) = (R(3) + -1);
    st32(base, (R(31) + 372), R(0));
    goto L_800D39DC;
L_800D398C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D3994u, 0x800D3CB0u, 0);
    { uint32_t ea_ = (R(2) + -26188); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 1);
    GM_CALLV(0x800D39A0u, 0x80166F10u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D39A8u, 0x800D3CB0u, 0);
    { uint32_t ea_ = (R(2) + -26184); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 1);
    GM_CALLV(0x800D39B4u, 0x80166F30u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D39DC; }
    { uint32_t ea_ = (R(2) + -26176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x800D39C4u, 0x80161400u, 0);
    { uint32_t ea_ = (R(2) + -26180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 12));
    st32(base, (R(31) + 372), R(0));
L_800D39DC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D39E4u, 0x800D3CB0u, 0);
    R(4) = (0 + 1);
    GM_CALLV(0x800D39ECu, 0x80166E80u, 0);
    R(12) = ld32(base, (R(31) + 1640));
    R(3) = (R(31) + 1640);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3A00u, ctx->ctr, 0);
    R(3) = (int16_t)ld16(base, (R(31) + 1922));
    R(0) = (int16_t)ld16(base, (R(31) + 1920));
    R(0) = R(0) - R(3);
    st16(base, (R(31) + 1920), R(0));
    R(0) = lr;
}

/* fn_800D3A30 (fn_800D3A30, 156 bytes) */
static void pf_m_d3a30(GM_CTX) {
    GM_FN(0x800D3A30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3A54u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3A64u, ctx->ctr, 0);
    R(0) = ld32(base, (R(31) + 1904));
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(3) = R(31) + R(0);
    { uint32_t ea_ = R(3) + 1192; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3A80u, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3A94u, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D3AA0u, 0x800D5B90u, 0);
    R(0) = ld32(base, (R(31) + 1904));
    R(3) = R(31) |R(31);
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(4) = R(31) + R(0);
    R(4) = (R(4) + 1192);
    GM_CALLV(0x800D3AB8u, 0x800D5B90u, 0);
    R(0) = lr;
}

/* fn_800D3AD0 (fn_800D3AD0, 80 bytes) */
static void pf_m_d3ad0(GM_CTX) {
    GM_FN(0x800D3AD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (R(13) + -31216);
    R(31) = R(3) |R(3);
    R(3) = (R(3) + 524);
    GM_CALLV(0x800D3AF0u, 0x8023A200u, 0);
    { uint32_t ea_ = (R(2) + -26184); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (f + 8);
    st32(base, (f + 8), R(3));
    R(3) = R(31) |R(31);
    ctx->f[2].u = ctx->f[1].u;
    R(5) = (0 + 0);
    GM_CALLV(0x800D3B0Cu, 0x800D3B20u, 0);
    R(0) = lr;
}

/* fn_800D3B20 (fn_800D3B20, 208 bytes) */
static void pf_m_d3b20(GM_CTX) {
    GM_FN(0x800D3B20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[2].u;
    ctx->f[30].u = ctx->f[1].u;
    R(31) = R(5) |R(5);
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(4) + 0));
    st32(base, (f + 8), R(0));
    GM_CALLV(0x800D3B58u, 0x800D3CB0u, 0);
    R(0) = ld32(base, (R(30) + 1904));
    R(7) = R(31) |R(31);
    R(5) = (f + 8);
    R(6) = (0 + 1);
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(4) = R(30) + R(0);
    R(4) = (R(4) + 1192);
    GM_CALLV(0x800D3B78u, 0x80166BD0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x800D3B80u, 0x800D3CB0u, 0);
    ctx->f[1].u = ctx->f[30].u;
    R(4) = (0 + 1);
    GM_CALLV(0x800D3B8Cu, 0x80166F10u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x800D3B94u, 0x800D3CB0u, 0);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = (0 + 1);
    GM_CALLV(0x800D3BA0u, 0x80166EF0u, 0);
    R(0) = ld32(base, (R(30) + 1904));
    R(3) = R(30) |R(30);
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(4) = R(30) + R(0);
    R(31) = (R(4) + 1192);
    GM_CALLV(0x800D3BB8u, 0x800D3CB0u, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3BD0u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_800D3BF0 (fn_800D3BF0, 140 bytes) */
static void pf_m_d3bf0(GM_CTX) {
    GM_FN(0x800D3BF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 368));
    cr_cmp_s(ctx, 0, (int32_t)R(0), (int32_t)R(4));
    if ((CR_BIT(ctx, 2))) { goto L_800D3C64; }
    R(5) = (0 + 0x802F0000u);
    st32(base, (R(3) + 368), R(4));
    R(0) = rotl32(R(4), 4) & 0xFFFFFFF0u;
    R(3) = (R(3) + 524);
    R(5) = (R(5) + 4688);
    R(4) = ld32(base, (R(5) + R(0)));
    R(31) = R(5) + R(0);
    GM_CALLV(0x800D3C34u, 0x8023A200u, 0);
    st32(base, (f + 8), R(3));
    R(3) = R(30) |R(30);
    R(5) = ld32(base, (R(31) + 4));
    R(4) = (f + 8);
    { uint32_t ea_ = (R(31) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x800D3C50u, 0x800D3B20u, 0);
    R(0) = ld32(base, (R(30) + 368));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D3C64; }
    R(0) = (0 + 0);
    st32(base, (R(30) + 372), R(0));
L_800D3C64:;
    R(0) = lr;
}

/* fn_800D3C80 (fn_800D3C80, 40 bytes) */
static void pf_m_d3c80(GM_CTX) {
    R(4) = ld32(base, (R(3) + 368));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D3C90; }
    GM_TAIL(0x800D3AD0u, 0); return;
L_800D3C90:;
    R(0) = (0 + 0);
    st32(base, (R(3) + 368), R(0));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 128));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D3CB0 (fn_800D3CB0, 44 bytes) */
static void pf_m_d3cb0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 1904));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800D3CC4; }
    R(3) = (R(3) + 1772);
    return;
L_800D3CC4:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800D3CD4; }
    R(3) = (R(3) + 1816);
    return;
L_800D3CD4:;
    R(3) = (R(3) + 1728);
}

/* fn_800D3CE0 (fn_800D3CE0, 520 bytes) */
static void pf_m_d3ce0(GM_CTX) {
    GM_FN(0x800D3CE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80310000u);
    R(6) = (R(6) + 31496);
    R(31) = R(5) |R(5);
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 1904));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800D3ECC; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 103);
    R(0) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D3E00; }
    if ((!CR_BIT(ctx, 0))) { goto L_800D3D54; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 21);
    if ((CR_BIT(ctx, 2))) { goto L_800D3DB8; }
    if ((!CR_BIT(ctx, 0))) { goto L_800D3D3C; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 19);
    if ((CR_BIT(ctx, 2))) { goto L_800D3D88; }
    if ((!CR_BIT(ctx, 0))) { goto L_800D3DA0; }
    goto L_800D3EA4;
L_800D3D3C:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 24);
    if ((CR_BIT(ctx, 2))) { goto L_800D3DD0; }
    if ((CR_BIT(ctx, 0))) { goto L_800D3EA4; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 102);
    if ((!CR_BIT(ctx, 0))) { goto L_800D3DE8; }
    goto L_800D3EA4;
L_800D3D54:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 118);
    if ((CR_BIT(ctx, 2))) { goto L_800D3E60; }
    if ((!CR_BIT(ctx, 0))) { goto L_800D3D78; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 106);
    if ((CR_BIT(ctx, 2))) { goto L_800D3E48; }
    if ((!CR_BIT(ctx, 0))) { goto L_800D3EA4; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 105);
    if ((!CR_BIT(ctx, 0))) { goto L_800D3E30; }
    goto L_800D3E18;
L_800D3D78:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 120);
    if ((CR_BIT(ctx, 2))) { goto L_800D3E90; }
    if ((!CR_BIT(ctx, 0))) { goto L_800D3EA4; }
    goto L_800D3E78;
L_800D3D88:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 280);
    GM_CALLV(0x800D3D94u, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3DA0:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 296);
    GM_CALLV(0x800D3DACu, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3DB8:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 308);
    GM_CALLV(0x800D3DC4u, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3DD0:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 324);
    GM_CALLV(0x800D3DDCu, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3DE8:;
    R(4) = (R(13) + -31184);
    R(3) = (R(3) + 528);
    GM_CALLV(0x800D3DF4u, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3E00:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 344);
    GM_CALLV(0x800D3E0Cu, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3E18:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 360);
    GM_CALLV(0x800D3E24u, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3E30:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 376);
    GM_CALLV(0x800D3E3Cu, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3E48:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 392);
    GM_CALLV(0x800D3E54u, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3E60:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 412);
    GM_CALLV(0x800D3E6Cu, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3E78:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 424);
    GM_CALLV(0x800D3E84u, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3EA4;
L_800D3E90:;
    R(3) = (R(3) + 528);
    R(4) = (R(6) + 436);
    GM_CALLV(0x800D3E9Cu, 0x8023A0B0u, 0);
    st32(base, (R(31) + 0), R(3));
    R(0) = (0 + 1);
L_800D3EA4:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D3ECC; }
    R(4) = ld32(base, (R(30) + 352));
    R(3) = (0 + 1);
    R(0) = ld32(base, (R(30) + 356));
    R(4) = R(4) | 0x800000u;
    st32(base, (R(30) + 352), R(4));
    R(0) = R(0) | 0x800000u;
    st32(base, (R(30) + 356), R(0));
    goto L_800D3ED0;
L_800D3ECC:;
    R(3) = (0 + 0);
L_800D3ED0:;
    R(0) = lr;
}

/* fn_800D3EF0 (fn_800D3EF0, 356 bytes) */
static void pf_m_d3ef0(GM_CTX) {
    GM_FN(0x800D3EF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(6) |R(6);
    R(30) = R(5) |R(5);
    R(5) = (f + 8);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 88));
    ctx->ctr = R(12);
    GM_CALLV(0x800D3F30u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D3F50; }
    R(3) = (R(28) + 528);
    R(4) = (f + 8);
    GM_CALLV(0x800D3F44u, 0x8023A0B0u, 0);
    st32(base, (R(30) + 0), R(3));
    R(3) = (0 + 1);
    goto L_800D4034;
L_800D3F50:;
    R(0) = ld32(base, (R(28) + 1904));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800D3FD8; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 130);
    R(0) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D3F74; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 131);
    if ((CR_BIT(ctx, 2))) { goto L_800D3F90; }
    goto L_800D3FA8;
L_800D3F74:;
    R(4) = (0 + 0x80310000u);
    R(3) = (R(28) + 528);
    R(4) = (R(4) + 31944);
    GM_CALLV(0x800D3F84u, 0x8023A0B0u, 0);
    st32(base, (R(30) + 0), R(3));
    R(0) = (0 + 1);
    goto L_800D3FA8;
L_800D3F90:;
    R(4) = (0 + 0x80310000u);
    R(3) = (R(28) + 528);
    R(4) = (R(4) + 31964);
    GM_CALLV(0x800D3FA0u, 0x8023A0B0u, 0);
    st32(base, (R(30) + 0), R(3));
    R(0) = (0 + 1);
L_800D3FA8:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D4030; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D3FC4; }
    R(0) = ld32(base, (R(28) + 352));
    R(0) = R(0) | 0x1000000u;
    st32(base, (R(28) + 352), R(0));
L_800D3FC4:;
    R(0) = ld32(base, (R(28) + 356));
    R(3) = (0 + 1);
    R(0) = R(0) | 0x1000000u;
    st32(base, (R(28) + 356), R(0));
    goto L_800D4034;
L_800D3FD8:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800D4030; }
    R(0) = ((int32_t)R(29) * 36);
    R(3) = (0 + 0x802F0000u);
    R(3) = (R(3) + 4944);
    R(3) = R(3) + R(0);
    R(4) = ld32(base, (R(3) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D4030; }
    R(3) = (R(28) + 528);
    GM_CALLV(0x800D4004u, 0x8023A0B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    st32(base, (R(30) + 0), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_800D401C; }
    R(0) = ld32(base, (R(28) + 352));
    R(0) = R(0) | 0x800000u;
    st32(base, (R(28) + 352), R(0));
L_800D401C:;
    R(0) = ld32(base, (R(28) + 356));
    R(3) = (0 + 1);
    R(0) = R(0) | 0x800000u;
    st32(base, (R(28) + 356), R(0));
    goto L_800D4034;
L_800D4030:;
    R(3) = (0 + 0);
L_800D4034:;
    R(0) = lr;
}

/* fn_800D4060 (fn_800D4060, 136 bytes) */
static void pf_m_d4060(GM_CTX) {
    GM_FN(0x800D4060); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    GM_CALLV(0x800D4088u, 0x800D6840u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D40C8; }
    R(0) = ld32(base, (R(29) + 1904));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800D40C0; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 5);
    if ((!CR_BIT(ctx, 2))) { goto L_800D40C0; }
    R(0) = ld32(base, (R(29) + 360));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D40C0; }
    R(3) = R(31) |R(31);
    R(4) = (R(13) + -31176);
    R(5) = (0 + 32);
    GM_CALLV(0x800D40C0u, 0x802E19F8u, 0);
L_800D40C0:;
    R(3) = (0 + 1);
    goto L_800D40CC;
L_800D40C8:;
    R(3) = (0 + 0);
L_800D40CC:;
    R(0) = lr;
}

/* fn_800D40F0 (fn_800D40F0, 328 bytes) */
static void pf_m_d40f0(GM_CTX) {
    GM_FN(0x800D40F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(4) = ld32(base, (R(3) + 1908));
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 1904));
    R(4) = (int8_t)R(4);
    R(27) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(27));
    if ((CR_BIT(ctx, 2))) { goto L_800D41CC; }
    R(30) = rotl32(R(4), 7) & 0xFFFFFF80u;
    R(4) = (0 + 0);
    R(3) = R(3) + R(30);
    R(29) = (R(3) + 1128);
    R(3) = R(29) |R(29);
    GM_CALLV(0x800D4140u, 0x80168520u, 0);
    R(27) = rotl32(R(27), 7) & 0xFFFFFF80u;
    R(4) = (R(31) + 152);
    R(3) = R(31) + R(27);
    R(28) = (R(3) + 1128);
    R(12) = ld32(base, (R(28) + 0));
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4164u, ctx->ctr, 0);
    R(3) = R(31) + R(30);
    R(4) = (0 + 3);
    R(30) = (R(3) + 1192);
    R(3) = R(30) |R(30);
    GM_CALLV(0x800D4178u, 0x80168520u, 0);
    R(3) = R(29) |R(29);
    R(4) = (0 + 3);
    GM_CALLV(0x800D4184u, 0x80168520u, 0);
    R(0) = ld32(base, (R(31) + 380));
    R(0) = R(0) & 0x100u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D41CC; }
    R(3) = R(31) |R(31);
    R(4) = R(30) |R(30);
    GM_CALLV(0x800D419Cu, 0x800D4C70u, 0);
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800D41A8u, 0x800D4C70u, 0);
    R(4) = R(31) + R(27);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 1192);
    R(5) = (R(31) + 1860);
    GM_CALLV(0x800D41BCu, 0x800D4C10u, 0);
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    R(5) = (R(31) + 1684);
    GM_CALLV(0x800D41CCu, 0x800D4C10u, 0);
L_800D41CC:;
    R(0) = ld32(base, (R(31) + 348));
    cr_cmp_s(ctx, 0, (int32_t)R(0), -1);
    if ((!CR_BIT(ctx, 2))) { goto L_800D4218; }
    R(27) = ld32(base, (R(31) + 340));
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800D41E8; }
    R(27) = (0 + 0);
L_800D41E8:;
    R(0) = (0 + -1);
    st32(base, (R(31) + 340), R(0));
    R(3) = (R(31) + 40);
    GM_CALLV(0x800D41F8u, 0x80168080u, 0);
    ctx->f[31].u = ctx->f[1].u;
    R(3) = (R(31) + 40);
    GM_CALLV(0x800D4204u, 0x801680C0u, 0);
    ctx->f[3].u = ctx->f[31].u;
    { uint32_t ea_ = (R(2) + -26184); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800D4218u, 0x800D5DD0u, 0);
L_800D4218:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_800D4240 (fn_800D4240, 416 bytes) */
static void pf_m_d4240(GM_CTX) {
    GM_FN(0x800D4240); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[3].u;
    ctx->f[30].u = ctx->f[2].u;
    ctx->f[29].u = ctx->f[1].u;
    R(31) = R(3) |R(3);
    R(30) = R(5) |R(5);
    R(28) = R(4) |R(4);
    R(0) = ld32(base, (R(3) + 1904));
    R(6) = ld32(base, (R(3) + 1912));
    R(3) = (R(3) + 524);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(6) = R(6) + R(0);
    R(4) = ld32(base, (R(6) + 8));
    GM_CALLV(0x800D42A8u, 0x80239E30u, 0);
    R(0) = ld32(base, (R(28) + 0));
    R(3) = R(31) |R(31);
    st32(base, (f + 8), R(0));
    R(29) = (R(31) + 40);
    R(12) = ld32(base, (R(31) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D42C8u, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(29) |R(29);
    R(6) = R(30) |R(30);
    R(5) = (f + 8);
    GM_CALLV(0x800D42DCu, 0x801651F0u, 0);
    ctx->f[1].u = ctx->f[29].u;
    R(3) = R(29) |R(29);
    GM_CALLV(0x800D42E8u, 0x801680E0u, 0);
    ctx->f[1].u = ctx->f[30].u;
    R(3) = R(29) |R(29);
    GM_CALLV(0x800D42F4u, 0x80168FE0u, 0);
    R(3) = ld32(base, (R(28) + 0));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 16), R(0));
    R(0) = ld16(base, (R(3) + 32));
    { uint32_t ea_ = (R(2) + -26168); ctx->f[1].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4334u, ctx->ctr, 0);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = (R(31) + 152);
    GM_CALLV(0x800D4340u, 0x80169F80u, 0);
    ctx->f[0].u = fctiw_bits(ctx->f[31].d, 1);
    R(0) = ld32(base, (R(31) + 352));
    { uint32_t ea_ = (f + 24); st64(base, ea_, ctx->f[0].u); }
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    R(0) = ld32(base, (f + 28));
    st32(base, (R(31) + 396), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D4398; }
    R(0) = ld32(base, (R(31) + 1904));
    R(30) = (0 + 0x80370000u);
    R(4) = ld8(base, (R(31) + 337));
    R(3) = (R(30) + 3488);
    R(29) = R(0) & 0xFFu;
    GM_CALLV(0x800D4374u, 0x8005DC20u, 0);
    R(0) = R(3) & 0xFFu;
    R(4) = (R(30) + 3488);
    R(3) = ((int32_t)R(0) * 68);
    R(0) = rotl32(R(29), 2) & 0x3FCu;
    R(3) = R(4) + R(3);
    R(3) = R(3) + R(0);
    { uint32_t ea_ = (R(3) + 2168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 392); stfs(base, ea_, ctx->f[0].d); }
    goto L_800D43A0;
L_800D4398:;
    { uint32_t ea_ = (R(2) + -26184); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 392); stfs(base, ea_, ctx->f[0].d); }
L_800D43A0:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D43A8u, 0x800D6A30u, 0);
    R(0) = lr;
}

/* fn_800D43E0 (fn_800D43E0, 312 bytes) */
static void pf_m_d43e0(GM_CTX) {
    GM_FN(0x800D43E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[3].u;
    ctx->f[30].u = ctx->f[2].u;
    ctx->f[29].u = ctx->f[1].u;
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 1904));
    R(6) = ld32(base, (R(3) + 1912));
    R(3) = (R(3) + 524);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(6) = R(6) + R(0);
    R(4) = ld32(base, (R(6) + 8));
    GM_CALLV(0x800D4448u, 0x80239E30u, 0);
    R(0) = ld32(base, (R(29) + 0));
    R(3) = R(28) |R(28);
    st32(base, (f + 8), R(0));
    R(31) = (R(28) + 96);
    R(12) = ld32(base, (R(28) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4468u, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(6) = R(30) |R(30);
    R(5) = (f + 8);
    GM_CALLV(0x800D447Cu, 0x801651F0u, 0);
    ctx->f[1].u = ctx->f[29].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D4488u, 0x801680E0u, 0);
    ctx->f[1].u = ctx->f[30].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D4494u, 0x80168FE0u, 0);
    R(3) = ld32(base, (R(29) + 0));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 16), R(0));
    R(0) = ld16(base, (R(3) + 32));
    { uint32_t ea_ = (R(2) + -26168); ctx->f[1].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    R(12) = ld32(base, (R(28) + 0));
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D44D4u, ctx->ctr, 0);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = (R(28) + 152);
    GM_CALLV(0x800D44E0u, 0x80169F80u, 0);
    R(0) = lr;
}

/* fn_800D4520 (fn_800D4520, 316 bytes) */
static void pf_m_d4520(GM_CTX) {
    GM_FN(0x800D4520); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 1904));
    R(4) = ld32(base, (R(3) + 1912));
    R(3) = (R(3) + 524);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = R(4) + R(0);
    R(4) = ld32(base, (R(4) + 8));
    GM_CALLV(0x800D4558u, 0x80239E30u, 0);
    R(30) = ld32(base, (R(29) + 44));
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 52));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4574u, ctx->ctr, 0);
    R(29) = ld32(base, (R(29) + 100));
    R(12) = ld32(base, (R(29) + 0));
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 52));
    ctx->ctr = R(12);
    GM_CALLV(0x800D458Cu, ctx->ctr, 0);
    st32(base, (f + 24), R(31));
    R(3) = R(30) |R(30);
    R(4) = (f + 24);
    R(5) = (0 + 5);
    R(12) = ld32(base, (R(30) + 0));
    R(6) = (0 + 1);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800D45B0u, ctx->ctr, 0);
    st32(base, (f + 20), R(31));
    R(3) = R(30) |R(30);
    R(4) = (f + 20);
    R(5) = (0 + 2);
    R(12) = ld32(base, (R(30) + 0));
    R(6) = (0 + 1);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800D45D4u, ctx->ctr, 0);
    st32(base, (f + 16), R(31));
    R(3) = R(30) |R(30);
    R(4) = (f + 16);
    R(5) = (0 + 1);
    R(12) = ld32(base, (R(30) + 0));
    R(6) = (0 + 0);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800D45F8u, ctx->ctr, 0);
    st32(base, (f + 12), R(31));
    R(3) = R(30) |R(30);
    R(4) = (f + 12);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(30) + 0));
    R(6) = (0 + 0);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800D461Cu, ctx->ctr, 0);
    st32(base, (f + 8), R(31));
    R(3) = R(29) |R(29);
    R(4) = (f + 8);
    R(5) = (0 + 8);
    R(12) = ld32(base, (R(29) + 0));
    R(6) = (0 + 1);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4640u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_800D4660 (fn_800D4660, 16 bytes) */
static void pf_m_d4660(GM_CTX) {
    R(0) = ld32(base, (R(3) + 1904));
    st32(base, (R(3) + 1908), R(0));
    st32(base, (R(3) + 1904), R(4));
}

/* fn_800D4670 (fn_800D4670, 260 bytes) */
static void pf_m_d4670(GM_CTX) {
    GM_FN(0x800D4670); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x802F0000u);
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(5) = (R(5) + 4912);
    R(31) = R(3) |R(3);
    st8(base, (R(3) + 338), R(4));
    R(4) = ld32(base, (R(5) + R(0)));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 176));
    ctx->ctr = R(12);
    GM_CALLV(0x800D46A8u, ctx->ctr, 0);
    R(3) = ld32(base, (R(31) + 1908));
    R(0) = ld32(base, (R(31) + 1904));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D46E4; }
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x800D46CCu, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D46D4u, 0x800D4CD0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D46DCu, 0x800D3C80u, 0);
    R(0) = (0 + 255);
    st8(base, (R(31) + 339), R(0));
L_800D46E4:;
    R(0) = ld8(base, (R(31) + 338));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800D46FC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 6);
    if ((CR_BIT(ctx, 2))) { goto L_800D4718; }
    goto L_800D4734;
L_800D46FC:;
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 52));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4714u, ctx->ctr, 0);
    goto L_800D474C;
L_800D4718:;
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(4) = (0 + 2);
    R(12) = ld32(base, (R(12) + 52));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4730u, ctx->ctr, 0);
    goto L_800D474C;
L_800D4734:;
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    R(12) = ld32(base, (R(12) + 52));
    ctx->ctr = R(12);
    GM_CALLV(0x800D474Cu, ctx->ctr, 0);
L_800D474C:;
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4760u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_800D4790 (fn_800D4790, 484 bytes) */
static void pf_m_d4790(GM_CTX) {
    GM_FN(0x800D4790); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -26168); ctx->f[3].u = ld64(base, ea_); }
    R(6) = (0 + 0);
    R(0) = R(4) ^ 0x80000000u;
    { uint32_t ea_ = (R(2) + -26160); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (f + 24);
    R(4) = (0 + 1);
    { uint32_t ea_ = (R(2) + -26188); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (0 + 0x43300000u);
    st32(base, (f + 44), R(0));
    st32(base, (f + 40), R(31));
    { uint32_t ea_ = (f + 40); ctx->f[1].u = ld64(base, ea_); }
    R(30) = R(3) |R(3);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[2].d);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[30].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 48); st64(base, ea_, ctx->f[0].u); }
    R(28) = ld32(base, (f + 52));
    st8(base, (f + 20), R(28));
    st8(base, (f + 21), R(28));
    st8(base, (f + 22), R(28));
    st8(base, (f + 23), R(28));
    R(0) = ld32(base, (f + 20));
    st32(base, (f + 24), R(0));
    R(0) = ld32(base, (R(3) + 1904));
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 1192);
    GM_CALLV(0x800D4834u, 0x80168710u, 0);
    st8(base, (f + 12), R(28));
    R(3) = R(30) |R(30);
    R(29) = (f + 16);
    st8(base, (f + 13), R(28));
    st8(base, (f + 14), R(28));
    st8(base, (f + 15), R(28));
    R(0) = ld32(base, (f + 12));
    st32(base, (f + 16), R(0));
    R(12) = ld32(base, (R(30) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4864u, ctx->ctr, 0);
    R(5) = R(29) |R(29);
    R(4) = (0 + 1);
    R(6) = (0 + 0);
    GM_CALLV(0x800D4874u, 0x80168710u, 0);
    R(0) = ld32(base, (R(30) + 1904));
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 1192);
    GM_CALLV(0x800D4888u, 0x80168400u, 0);
    R(0) = (0 + 0);
    st32(base, (f + 36), R(3));
    { uint32_t ea_ = (R(2) + -26152); ctx->f[31].u = ld64(base, ea_); }
    R(28) = (0 + 0);
    st32(base, (f + 32), R(0));
    goto L_800D4934;
L_800D48A0:;
    R(4) = R(28) |R(28);
    R(3) = (f + 36);
    GM_CALLV(0x800D48ACu, 0x8023B860u, 0);
    R(0) = ld32(base, (R(3) + 60));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D48C0; }
    R(3) = R(3) + R(0);
    goto L_800D48C4;
L_800D48C0:;
    R(3) = (0 + 0);
L_800D48C4:;
    R(0) = (R(3) + 32);
    st32(base, (f + 32), R(0));
    R(3) = (f + 32);
    R(5) = (f + 28);
    R(4) = (0 + 2);
    GM_CALLV(0x800D48DCu, 0x8023D300u, 0);
    R(0) = ld8(base, (f + 31));
    R(4) = R(28) |R(28);
    st32(base, (f + 52), R(0));
    R(6) = (f + 8);
    R(5) = (0 + 2);
    R(7) = (0 + 0);
    st32(base, (f + 48), R(31));
    { uint32_t ea_ = (f + 48); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[31].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[30].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 40); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 44));
    st8(base, (f + 31), R(0));
    R(0) = ld32(base, (f + 28));
    st32(base, (f + 8), R(0));
    R(0) = ld32(base, (R(30) + 1904));
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 1192);
    GM_CALLV(0x800D4930u, 0x801685E0u, 0);
    R(28) = (R(28) + 1);
L_800D4934:;
    R(3) = (f + 36);
    GM_CALLV(0x800D493Cu, 0x8023B8C0u, 0);
    cr_cmp_u(ctx, 0, R(28), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800D48A0; }
    R(0) = lr;
}

/* fn_800D4980 (fn_800D4980, 76 bytes) */
static void pf_m_d4980(GM_CTX) {
    GM_FN(0x800D4980); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld32(base, (R(3) + 1904));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800D49B8; }
    R(0) = rotl32(R(0), 7) & 0xFFFFFF80u;
    R(5) = R(4) |R(4);
    R(3) = R(3) + R(0);
    R(4) = (0 + 1);
    R(3) = (R(3) + 1192);
    GM_CALLV(0x800D49B0u, 0x80168180u, 0);
    R(3) = (0 + 1);
    goto L_800D49BC;
L_800D49B8:;
    R(3) = (0 + 0);
L_800D49BC:;
    R(0) = lr;
}

/* fn_800D4CD0 (fn_800D4CD0, 172 bytes) */
static void pf_m_d4cd0(GM_CTX) {
    GM_FN(0x800D4CD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4CFCu, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 0));
    { uint32_t ea_ = (R(3) + 40); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 184));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4D14u, ctx->ctr, 0);
    { uint32_t ea_ = (R(2) + -26188); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[31].d);
    if ((!CR_BIT(ctx, 2))) { goto L_800D4D30; }
    { uint32_t ea_ = (R(31) + 1936); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 1932); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 1928); stfs(base, ea_, ctx->f[1].d); }
    goto L_800D4D60;
L_800D4D30:;
    { uint32_t ea_ = (R(31) + 1932); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((CR_BIT(ctx, 2))) { goto L_800D4D44; }
    { uint32_t ea_ = (R(31) + 1936); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 1932); stfs(base, ea_, ctx->f[1].d); }
L_800D4D44:;
    { uint32_t ea_ = (R(2) + -26188); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d * ctx->f[31].d);
    { uint32_t ea_ = (R(31) + 1936); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[31].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 1928); stfs(base, ea_, ctx->f[0].d); }
L_800D4D60:;
    R(0) = lr;
}

/* fn_800D4D80 (fn_800D4D80, 264 bytes) */
static void pf_m_d4d80(GM_CTX) {
    GM_FN(0x800D4D80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(6) = ld32(base, (R(5) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D4DBC; }
    R(31) = ld32(base, (R(6) + 12));
    goto L_800D4DC0;
L_800D4DBC:;
    R(31) = (0 + 0);
L_800D4DC0:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D4E68; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800D4E14; }
    R(3) = R(29) |R(29);
    R(4) = (f + 8);
    GM_CALLV(0x800D4DDCu, 0x802418B0u, 0);
    { uint32_t ea_ = (R(28) + 1928); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = R(29) |R(29);
    { uint32_t ea_ = (f + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (f + 8);
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[3].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800D4E10u, 0x80241BE0u, 0);
    goto L_800D4E68;
L_800D4E14:;
    R(3) = R(29) |R(29);
    R(4) = (R(6) + 56);
    GM_CALLV(0x800D4E20u, 0x80241BE0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 11);
    if ((CR_BIT(ctx, 2))) { goto L_800D4E30; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 14);
    if ((!CR_BIT(ctx, 2))) { goto L_800D4E68; }
L_800D4E30:;
    R(0) = ld32(base, (R(28) + 1904));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800D4E68; }
    R(0) = ld32(base, (R(28) + 356));
    R(0) = R(0) & 0x800000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800D4E68; }
    R(4) = ld32(base, (R(30) + 0));
    R(3) = R(29) |R(29);
    R(4) = (R(4) + 44);
    GM_CALLV(0x800D4E58u, 0x80241AA0u, 0);
    R(4) = ld32(base, (R(30) + 0));
    R(3) = R(29) |R(29);
    R(4) = (R(4) + 32);
    GM_CALLV(0x800D4E68u, 0x80241A00u, 0);
L_800D4E68:;
    R(0) = lr;
}

/* fn_800D4E90 (fn_800D4E90, 92 bytes) */
static void pf_m_d4e90(GM_CTX) {
    GM_FN(0x800D4E90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(3) |R(3);
    R(3) = R(6) |R(6);
    GM_CALLV(0x800D4EB4u, 0x8023B300u, 0);
    st32(base, (f + 8), R(3));
    R(4) = R(31) |R(31);
    R(5) = (f + 8);
    R(3) = ld32(base, (R(30) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 180));
    ctx->ctr = R(12);
    GM_CALLV(0x800D4ED4u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_800D5060 (fn_800D5060, 4 bytes) */
static void pf_m_d5060(GM_CTX) {

}

/* fn_800D5170 (fn_800D5170, 444 bytes) */
static void pf_m_d5170(GM_CTX) {
    GM_FN(0x800D5170); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 380));
    R(0) = R(0) & 0x200u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D5310; }
    R(0) = ld8(base, (R(3) + 338));
    { uint32_t ea_ = (R(2) + -26188); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D51B4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((CR_BIT(ctx, 2))) { goto L_800D51BC; }
    goto L_800D51C0;
L_800D51B4:;
    { uint32_t ea_ = (R(2) + -26140); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    goto L_800D51C0;
L_800D51BC:;
    { uint32_t ea_ = (R(2) + -26136); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
L_800D51C0:;
    { uint32_t ea_ = (R(3) + 332); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (f + 32);
    { uint32_t ea_ = (R(3) + 328); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 324); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[31].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[31].d);
    R(3) = (R(3) + 216);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[31].d);
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x800D51F0u, 0x8016F130u, 0);
    R(0) = ld32(base, (R(31) + 384));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D5210; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800D5258; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800D5288; }
    goto L_800D52AC;
L_800D5210:;
    R(0) = ld8(base, (R(31) + 338));
    R(3) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D5228; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800D522C; }
L_800D5228:;
    R(3) = (0 + 1);
L_800D522C:;
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(5) = (R(13) + -31160);
    R(3) = ld8(base, (R(31) + 336));
    R(4) = (R(31) + 536);
    R(5) = ld32(base, (R(5) + R(0)));
    R(7) = (f + 32);
    R(9) = (R(31) + 324);
    R(6) = (0 + 0);
    R(8) = (0 + 0);
    GM_CALLV(0x800D5254u, 0x8008FC80u, 0);
    goto L_800D52AC;
L_800D5258:;
    R(12) = ld32(base, (R(31) + 536));
    R(4) = (0 + 0x80310000u);
    R(3) = (R(31) + 536);
    R(6) = (f + 32);
    R(12) = ld32(base, (R(12) + 160));
    R(4) = (R(4) + 32012);
    R(8) = (f + 44);
    R(5) = (0 + 0);
    R(7) = (0 + 0);
    ctx->ctr = R(12);
    GM_CALLV(0x800D5284u, ctx->ctr, 0);
    goto L_800D52AC;
L_800D5288:;
    R(5) = (0 + 0x80310000u);
    R(3) = ld8(base, (R(31) + 336));
    R(4) = (R(31) + 536);
    R(7) = (f + 32);
    R(5) = (R(5) + 32012);
    R(9) = (f + 44);
    R(6) = (0 + 0);
    R(8) = (0 + 0);
    GM_CALLV(0x800D52ACu, 0x8008FBA0u, 0);
L_800D52AC:;
    R(0) = ld32(base, (R(31) + 384));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D5310; }
    { uint32_t ea_ = (R(31) + 332); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(31) + 328); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (f + 8);
    { uint32_t ea_ = (R(31) + 324); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[31].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[31].d);
    R(5) = (0 + 8);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[31].d);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x800D52ECu, 0x800D5790u, 0);
    R(5) = (0 + 0x80310000u);
    R(3) = ld8(base, (R(31) + 336));
    R(4) = (R(31) + 832);
    R(7) = (f + 8);
    R(5) = (R(5) + 32032);
    R(9) = (f + 20);
    R(6) = (0 + 0);
    R(8) = (0 + 0);
    GM_CALLV(0x800D5310u, 0x8008FBA0u, 0);
L_800D5310:;
    R(0) = lr;
}

/* fn_800D5330 (fn_800D5330, 360 bytes) */
static void pf_m_d5330(GM_CTX) {
    GM_FN(0x800D5330); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80320000u);
    R(5) = (R(5) + -30304);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    st32(base, (R(3) + 0), R(5));
    R(3) = (R(3) + 4);
    GM_CALLV(0x800D5364u, 0x80069020u, 0);
    R(31) = (0 + 0);
    R(4) = (0 + 0x800D0000u);
    R(5) = (0 + 0x80020000u);
    st32(base, (R(29) + 32), R(31));
    R(3) = (R(29) + 40);
    R(4) = (R(4) + 21664);
    st32(base, (R(29) + 36), R(31));
    R(5) = (R(5) + 24768);
    R(6) = (0 + 56);
    R(7) = (0 + 2);
    GM_CALLV(0x800D5390u, 0x802DC9A0u, 0);
    R(3) = (0 + 0x80330000u);
    st32(base, (R(29) + 156), R(31));
    R(3) = (R(3) + -27176);
    st32(base, (R(29) + 152), R(3));
    R(3) = (R(29) + 164);
    st32(base, (R(29) + 160), R(31));
    GM_CALLV(0x800D53ACu, 0x8016A5E0u, 0);
    { uint32_t ea_ = (R(2) + -26120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (0 + 0x80300000u);
    { uint32_t ea_ = (R(2) + -26116); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + -1);
    R(3) = (R(3) + 13296);
    R(8) = (0 + 255);
    R(4) = (0 + 0x80010000u);
    R(5) = (0 + 0x80010000u);
    st32(base, (R(29) + 152), R(3));
    R(3) = (R(29) + 400);
    R(4) = (R(4) + 24112);
    R(5) = (R(5) + -1040);
    { uint32_t ea_ = (R(29) + 192); stfs(base, ea_, ctx->f[1].d); }
    R(6) = (0 + 12);
    R(7) = (0 + 6);
    { uint32_t ea_ = (R(29) + 196); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 200); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 204); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 208); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 212); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 312); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 316); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 320); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 324); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 328); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 332); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(29) + 336), R(31));
    st8(base, (R(29) + 337), R(30));
    st8(base, (R(29) + 338), R(31));
    st8(base, (R(29) + 339), R(8));
    st32(base, (R(29) + 340), R(0));
    st32(base, (R(29) + 344), R(0));
    st32(base, (R(29) + 348), R(0));
    st32(base, (R(29) + 360), R(31));
    st32(base, (R(29) + 364), R(31));
    st32(base, (R(29) + 368), R(31));
    st32(base, (R(29) + 372), R(31));
    st8(base, (R(29) + 376), R(31));
    st32(base, (R(29) + 380), R(31));
    st32(base, (R(29) + 384), R(31));
    { uint32_t ea_ = (R(29) + 388); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 392); stfs(base, ea_, ctx->f[1].d); }
    st32(base, (R(29) + 396), R(31));
    GM_CALLV(0x800D545Cu, 0x802DC9A0u, 0);
    st16(base, (R(29) + 508), R(31));
    R(3) = R(29) |R(29);
    st16(base, (R(29) + 510), R(31));
    st16(base, (R(29) + 512), R(31));
    st32(base, (R(29) + 516), R(31));
    st32(base, (R(29) + 520), R(31));
    st32(base, (R(29) + 352), R(31));
    st32(base, (R(29) + 356), R(31));
    R(0) = lr;
}

/* fn_800D54A0 (fn_800D54A0, 60 bytes) */
static void pf_m_d54a0(GM_CTX) {
    GM_FN(0x800D54A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800D54B8u, 0x80168D10u, 0);
    R(4) = (0 + 0x80300000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 13320);
    st32(base, (R(31) + 0), R(4));
    R(0) = lr;
}

/* fn_800D54E0 (fn_800D54E0, 156 bytes) */
static void pf_m_d54e0(GM_CTX) {
    GM_FN(0x800D54E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800D5560; }
    R(4) = (0 + 0x80010000u);
    R(5) = (0 + 12);
    R(4) = (R(4) + -1040);
    R(6) = (0 + 6);
    R(3) = (R(3) + 400);
    GM_CALLV(0x800D551Cu, 0x802DCA98u, 0);
    { uint32_t a_ = R(30); R(3) = a_ + 0x98u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_800D552C; }
    R(4) = (0 + 0);
    GM_CALLV(0x800D552Cu, 0x80167EC0u, 0);
L_800D552C:;
    R(4) = (0 + 0x80020000u);
    R(3) = (R(30) + 40);
    R(4) = (R(4) + 24768);
    R(5) = (0 + 56);
    R(6) = (0 + 2);
    GM_CALLV(0x800D5544u, 0x802DCA98u, 0);
    R(3) = (R(30) + 4);
    R(4) = (0 + -1);
    GM_CALLV(0x800D5550u, 0x80069060u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800D5560; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x800D5560u, 0x802B9280u, 0);
L_800D5560:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_800D5580 (fn_800D5580, 168 bytes) */
static void pf_m_d5580(GM_CTX) {
    GM_FN(0x800D5580); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(7) = (0 + 32);
    R(31) = R(5) |R(5);
    R(5) = (0 + 0x10000u);
    R(30) = R(3) |R(3);
    st32(base, (R(3) + 384), R(6));
    R(6) = (0 + 0x80370000u);
    st8(base, (R(3) + 336), R(4));
    R(4) = (R(5) + -16384);
    R(3) = (R(3) + 4);
    R(5) = ld32(base, (R(6) + 31816));
    R(6) = (0 + 0);
    GM_CALLV(0x800D55C4u, 0x800690C0u, 0);
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x800D55D8u, ctx->ctr, 0);
    R(3) = (R(30) + 4);
    GM_CALLV(0x800D55E0u, 0x800690E0u, 0);
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 48));
    ctx->ctr = R(12);
    GM_CALLV(0x800D55F8u, ctx->ctr, 0);
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800D560Cu, ctx->ctr, 0);
    R(3) = (0 + 0);
    R(0) = lr;
}

/* fn_800D5640 (fn_800D5640, 8 bytes) */
static void pf_m_d5640(GM_CTX) {
    st8(base, (R(3) + 338), R(4));
}

/* fn_800D5680 (fn_800D5680, 112 bytes) */
static void pf_m_d5680(GM_CTX) {
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 216); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 220); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 224); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 228); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 232); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 236); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 240); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 244); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 248); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 252); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 256); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 260); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D56F0 (fn_800D56F0, 64 bytes) */
static void pf_m_d56f0(GM_CTX) {
    GM_FN(0x800D56F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800D5708u, 0x800D57F0u, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    GM_CALLV(0x800D571Cu, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_800D5730 (fn_800D5730, 80 bytes) */
static void pf_m_d5730(GM_CTX) {
    GM_FN(0x800D5730); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800D575Cu, ctx->ctr, 0);
    R(4) = R(31) |R(31);
    R(5) = R(30) |R(30);
    GM_CALLV(0x800D5768u, 0x80168180u, 0);
    R(0) = lr;
}

/* getJointPos__12dPyMdlBase_cFP7mVec3_ci (getJointPos__12dPyMdlBase_cFP7mVec3_ci, 96 bytes) */
static void pf_getJointPos__12dPyMdlBase_cFP7mVec3_ci_d5790(GM_CTX) {
    GM_FN(0x800D5790); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(4) = (f + 24);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800D57B8u, ctx->ctr, 0);
    { uint32_t ea_ = (f + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 52); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[1].d); }
    R(0) = lr;
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
}

/* fn_800D57F0 (fn_800D57F0, 908 bytes) */
static void pf_m_d57f0(GM_CTX) {
    GM_FN(0x800D57F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(30) = R(6) |R(6);
    R(29) = R(5) |R(5);
    R(28) = R(4) |R(4);
    R(0) = ld32(base, (R(3) + 384));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D5858; }
    { uint32_t ea_ = (R(6) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 324); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 328); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 332); stfs(base, ea_, ctx->f[0].d); }
L_800D5858:;
    R(4) = ld32(base, (R(3) + 340));
    { uint32_t ea_ = (R(2) + -26112); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (R(4) + -43);
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    { uint32_t ea_ = (R(2) + -26120); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[0].d * ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800D5898; }
    R(0) = (R(4) + -52);
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D58AC; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 126);
    if ((CR_BIT(ctx, 2))) { goto L_800D5898; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 127);
    if ((CR_BIT(ctx, 2))) { goto L_800D58A0; }
    goto L_800D58B8;
L_800D5898:;
    { uint32_t ea_ = (R(2) + -26120); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    goto L_800D58B8;
L_800D58A0:;
    { uint32_t ea_ = (R(2) + -26108); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[0].d * ctx->f[1].d);
    goto L_800D58B8;
L_800D58AC:;
    R(0) = ld8(base, (R(3) + 338));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (R(2) + -26104); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
L_800D58B8:;
    { uint32_t ea_ = (R(2) + -26112); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 320);
    { uint32_t ea_ = (R(6) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 16);
    R(0) = ld16(base, (R(5) + 2));
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[1].d * ctx->f[0].d);
    st16(base, (f + 16), R(0));
    GM_CALLV(0x800D58D8u, 0x8016ED10u, 0);
    ctx->f[2].u = ctx->f[30].u;
    { uint32_t ea_ = (R(2) + -26120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[31].u;
    R(3) = (f + 224);
    GM_CALLV(0x800D58ECu, 0x801C0BD0u, 0);
    R(3) = (f + 320);
    R(4) = (f + 224);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800D58FCu, 0x801C0540u, 0);
    R(0) = (int16_t)ld16(base, (R(29) + 0));
    R(3) = (f + 320);
    R(4) = (f + 12);
    R(0) = -(int32_t)R(0);
    st16(base, (f + 12), R(0));
    GM_CALLV(0x800D5914u, 0x8016ECB0u, 0);
    { uint32_t ea_ = (R(2) + -26120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[30].u ^ 0x8000000000000000ull;
    R(3) = (f + 176);
    ctx->f[3].u = ctx->f[1].u;
    GM_CALLV(0x800D5928u, 0x801C0BD0u, 0);
    R(3) = (f + 320);
    R(4) = (f + 176);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800D5938u, 0x801C0540u, 0);
    { uint32_t ea_ = (R(2) + -26120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[29].u;
    R(3) = (f + 128);
    ctx->f[3].u = ctx->f[1].u;
    GM_CALLV(0x800D594Cu, 0x801C0BD0u, 0);
    R(3) = (f + 320);
    R(4) = (f + 128);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800D595Cu, 0x801C0540u, 0);
    R(0) = ld16(base, (R(29) + 4));
    R(3) = (f + 320);
    st16(base, (f + 8), R(0));
    R(4) = (f + 8);
    GM_CALLV(0x800D5970u, 0x8016EEF0u, 0);
    { uint32_t ea_ = (R(2) + -26120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[29].u ^ 0x8000000000000000ull;
    R(3) = (f + 80);
    ctx->f[3].u = ctx->f[1].u;
    GM_CALLV(0x800D5984u, 0x801C0BD0u, 0);
    R(3) = (f + 320);
    R(4) = (f + 80);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800D5994u, 0x801C0540u, 0);
    { uint32_t ea_ = (R(30) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 32);
    { uint32_t ea_ = (R(30) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    GM_CALLV(0x800D59A8u, 0x801C0C60u, 0);
    R(3) = (f + 320);
    R(4) = (f + 32);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800D59B8u, 0x801C0540u, 0);
    { uint32_t ea_ = (f + 320); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 264); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 324); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 268); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 328); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 272); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 332); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 276); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 336); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 280); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 340); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 344); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 348); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 292); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 352); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 356); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 360); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 304); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 364); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 308); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    R(3) = ld32(base, (R(31) + 340));
    R(0) = (R(3) + -130);
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D5A58; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 133);
    if ((!CR_BIT(ctx, 2))) { goto L_800D5A68; }
    { uint32_t ea_ = (R(2) + -26116); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    goto L_800D5A74;
L_800D5A58:;
    { uint32_t ea_ = (R(2) + -26100); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    goto L_800D5A74;
L_800D5A68:;
    { uint32_t ea_ = (R(2) + -26096); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
L_800D5A74:;
    { uint32_t ea_ = (f + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 388); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(31) + 380));
    R(0) = R(0) & 0x400u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D5AA4; }
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 3488);
    { uint32_t ea_ = (R(3) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
L_800D5AA4:;
    R(0) = ld32(base, (R(31) + 384));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D5AC0; }
    R(3) = (f + 20);
    R(4) = (0 + 0);
    R(5) = (0 + 1);
    GM_CALLV(0x800D5AC0u, 0x80064AF0u, 0);
L_800D5AC0:;
    { uint32_t ea_ = (f + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 272);
    { uint32_t ea_ = (f + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    GM_CALLV(0x800D5AD4u, 0x801C0BD0u, 0);
    R(3) = (f + 272);
    R(4) = (f + 320);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800D5AE4u, 0x801C0540u, 0);
    { uint32_t ea_ = (f + 272); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 216); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 276); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 220); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 280); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 224); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 284); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 228); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 288); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 232); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 292); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 236); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 296); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 240); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 300); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 244); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 304); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 248); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 308); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 252); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 312); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 256); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 316); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 260); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_800D5B90 (fn_800D5B90, 52 bytes) */
static void pf_m_d5b90(GM_CTX) {
    R(0) = ld32(base, (R(3) + 384));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D5BA8; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800D5BB4; }
    return;
L_800D5BA8:;
    R(3) = R(4) |R(4);
    R(4) = (0 + 0);
    GM_TAIL(0x800B3E50u, 0); return;
L_800D5BB4:;
    R(3) = R(4) |R(4);
    R(4) = (0 + 1);
    GM_TAIL(0x800B3E50u, 0); return;
}

/* fn_800D5BE0 (fn_800D5BE0, 40 bytes) */
static void pf_m_d5be0(GM_CTX) {
    R(4) = ld32(base, (R(3) + 344));
    cr_cmp_s(ctx, 0, (int32_t)R(4), -1);
    if ((CR_BIT(ctx, 2))) { goto L_800D5BF8; }
    R(0) = ld32(base, (R(3) + 340));
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800D5C00; }
L_800D5BF8:;
    R(3) = (0 + 0);
    return;
L_800D5C00:;
    R(3) = (0 + 1);
}

/* fn_800D5C10 (fn_800D5C10, 100 bytes) */
static void pf_m_d5c10(GM_CTX) {
    GM_FN(0x800D5C10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[1].u;
    R(31) = R(3) |R(3);
    R(3) = (R(3) + 40);
    GM_CALLV(0x800D5C34u, 0x80168FE0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D5C3Cu, 0x800D5BE0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D5C5C; }
    R(12) = ld32(base, (R(31) + 0));
    ctx->f[1].u = ctx->f[31].u;
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 136));
    ctx->ctr = R(12);
    GM_CALLV(0x800D5C5Cu, ctx->ctr, 0);
L_800D5C5C:;
    R(0) = lr;
}

/* fn_800D5C80 (fn_800D5C80, 8 bytes) */
static void pf_m_d5c80(GM_CTX) {
    R(3) = (R(3) + 96);
    GM_TAIL(0x80168FE0u, 0); return;
}

/* fn_800D5C90 (fn_800D5C90, 100 bytes) */
static void pf_m_d5c90(GM_CTX) {
    GM_FN(0x800D5C90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[1].u;
    R(31) = R(3) |R(3);
    R(3) = (R(3) + 40);
    GM_CALLV(0x800D5CB4u, 0x801680E0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D5CBCu, 0x800D5BE0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D5CDC; }
    R(12) = ld32(base, (R(31) + 0));
    ctx->f[1].u = ctx->f[31].u;
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 144));
    ctx->ctr = R(12);
    GM_CALLV(0x800D5CDCu, ctx->ctr, 0);
L_800D5CDC:;
    R(0) = lr;
}

/* fn_800D5D00 (fn_800D5D00, 8 bytes) */
static void pf_m_d5d00(GM_CTX) {
    R(3) = (R(3) + 96);
    GM_TAIL(0x801680E0u, 0); return;
}

/* setJumpAnmRand__12dPyMdlBase_cFQ212dPyMdlBase_c9RndType_e (setJumpAnmRand__12dPyMdlBase_cFQ212dPyMdlBase_c9RndType_e, 184 bytes) */
static void pf_setJumpAnmRand__12dPyMdlBase_cFQ212dPyMd_d5d10(GM_CTX) {
    GM_FN(0x800D5D10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800D5D38; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800D5D48; }
    goto L_800D5DA0;
L_800D5D38:;
    R(3) = (0 + 3);
    GM_CALLV(0x800D5D40u, 0x800B2EE0u, 0);
    st32(base, (R(31) + 360), R(3));
    goto L_800D5DA0;
L_800D5D48:;
    R(3) = (0 + 10);
    GM_CALLV(0x800D5D50u, 0x800B2EE0u, 0);
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 12), R(3));
    { uint32_t ea_ = (R(2) + -26080); ctx->f[2].u = ld64(base, ea_); }
    st32(base, (f + 8), R(0));
    { uint32_t ea_ = (R(2) + -26092); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D5D80; }
    R(0) = (0 + 0);
    st32(base, (R(31) + 360), R(0));
    goto L_800D5DA0;
L_800D5D80:;
    { uint32_t ea_ = (R(2) + -26088); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D5D98; }
    R(0) = (0 + 1);
    st32(base, (R(31) + 360), R(0));
    goto L_800D5DA0;
L_800D5D98:;
    R(0) = (0 + 2);
    st32(base, (R(31) + 360), R(0));
L_800D5DA0:;
    R(0) = ld32(base, (R(31) + 360));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D5DB4; }
    R(0) = (0 + 0);
    st32(base, (R(31) + 360), R(0));
L_800D5DB4:;
    R(0) = lr;
}

/* fn_800D6200 (fn_800D6200, 232 bytes) */
static void pf_m_d6200(GM_CTX) {
    GM_FN(0x800D6200); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x802F0000u);
    R(0) = ((int32_t)R(4) * 36);
    R(5) = (R(5) + 4944);
    ctx->f[31].u = ctx->f[3].u;
    ctx->f[30].u = ctx->f[2].u;
    ctx->f[29].u = ctx->f[1].u;
    R(31) = R(5) + R(0);
    R(0) = ld32(base, (R(31) + 32));
    R(30) = R(3) |R(3);
    st32(base, (R(3) + 344), R(4));
    st32(base, (R(3) + 356), R(0));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 44));
    ctx->ctr = R(12);
    GM_CALLV(0x800D625Cu, ctx->ctr, 0);
    R(4) = ld32(base, (R(31) + 0));
    GM_CALLV(0x800D6264u, 0x8023A0B0u, 0);
    st32(base, (f + 8), R(3));
    R(3) = R(30) |R(30);
    R(5) = (f + 8);
    R(6) = (0 + 1);
    R(12) = ld32(base, (R(30) + 0));
    R(4) = ld32(base, (R(30) + 344));
    R(12) = ld32(base, (R(12) + 96));
    ctx->ctr = R(12);
    GM_CALLV(0x800D6288u, ctx->ctr, 0);
    R(12) = ld32(base, (R(30) + 0));
    ctx->f[1].u = ctx->f[29].u;
    ctx->f[2].u = ctx->f[30].u;
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 116));
    ctx->f[3].u = ctx->f[31].u;
    R(4) = (f + 8);
    R(5) = ld32(base, (R(31) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x800D62B0u, ctx->ctr, 0);
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 120));
    ctx->ctr = R(12);
    GM_CALLV(0x800D62C4u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_800D62F0 (fn_800D62F0, 360 bytes) */
static void pf_m_d62f0(GM_CTX) {
    GM_FN(0x800D62F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x802F0000u);
    R(5) = (0 + -1);
    R(4) = (R(4) + 4944);
    ctx->f[30].u = ctx->f[1].u;
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 340));
    st32(base, (R(3) + 344), R(5));
    R(0) = ((int32_t)R(0) * 36);
    R(31) = R(4) + R(0);
    R(0) = ld32(base, (R(31) + 32));
    st32(base, (R(3) + 356), R(0));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 44));
    ctx->ctr = R(12);
    GM_CALLV(0x800D6350u, ctx->ctr, 0);
    R(4) = ld32(base, (R(31) + 0));
    GM_CALLV(0x800D6358u, 0x8023A0B0u, 0);
    st32(base, (f + 8), R(3));
    R(3) = R(30) |R(30);
    R(5) = (f + 8);
    R(6) = (0 + 1);
    R(12) = ld32(base, (R(30) + 0));
    R(4) = ld32(base, (R(30) + 340));
    R(12) = ld32(base, (R(12) + 96));
    ctx->ctr = R(12);
    GM_CALLV(0x800D637Cu, ctx->ctr, 0);
    R(0) = ld32(base, (R(30) + 380));
    R(0) = R(0) & 0x6u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D63A4; }
    R(0) = ld32(base, (R(30) + 356));
    R(0) = R(0) & 0x2u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800D63A4; }
    ctx->f[1].u = ctx->f[30].u;
    R(3) = R(30) |R(30);
    GM_CALLV(0x800D63A0u, 0x800D6460u, 0);
    goto L_800D6430;
L_800D63A4:;
    R(0) = ld32(base, (R(30) + 356));
    R(0) = R(0) & 0x1000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D63C0; }
    ctx->f[1].u = ctx->f[30].u;
    R(3) = R(30) |R(30);
    GM_CALLV(0x800D63BCu, 0x800D6550u, 0);
    goto L_800D6430;
L_800D63C0:;
    R(3) = (R(30) + 40);
    GM_CALLV(0x800D63C8u, 0x80168080u, 0);
    R(3) = ld32(base, (f + 8));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 16), R(0));
    ctx->f[31].u = ctx->f[1].u;
    R(0) = ld16(base, (R(3) + 32));
    { uint32_t ea_ = (R(2) + -26072); ctx->f[2].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D6404; }
    { uint32_t ea_ = (R(2) + -26116); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[2].d - ctx->f[0].d);
L_800D6404:;
    R(3) = (R(30) + 40);
    GM_CALLV(0x800D640Cu, 0x801680C0u, 0);
    R(12) = ld32(base, (R(30) + 0));
    ctx->f[2].u = ctx->f[31].u;
    ctx->f[3].u = ctx->f[30].u;
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 116));
    R(4) = (f + 8);
    R(5) = ld8(base, (R(30) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x800D6430u, ctx->ctr, 0);
L_800D6430:;
    R(0) = lr;
}

/* fn_800D6460 (fn_800D6460, 236 bytes) */
static void pf_m_d6460(GM_CTX) {
    GM_FN(0x800D6460); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[1].u;
    R(31) = (0 + 0);
    R(29) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 380));
    R(0) = R(0) & 0x4u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D649C; }
    R(31) = (0 + 1);
L_800D649C:;
    R(4) = ld32(base, (R(3) + 352));
    R(0) = R(4) & 0xC000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D64FC; }
    R(0) = R(4) & 0x4000u;
    CR0(ctx, R(0));
    R(30) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D64B8; }
    R(30) = (0 + 1);
L_800D64B8:;
    R(3) = (R(3) + 40);
    GM_CALLV(0x800D64C0u, 0x80168080u, 0);
    R(12) = ld32(base, (R(29) + 0));
    R(5) = (0 + 0x802F0000u);
    ctx->f[2].u = ctx->f[1].u;
    R(0) = rotl32(R(30), 3) & 0xFFFFFFF8u;
    R(5) = (R(5) + 11320);
    R(12) = ld32(base, (R(12) + 100));
    ctx->f[3].u = ctx->f[31].u;
    R(4) = rotl32(R(31), 2) & 0xFFFFFFFCu;
    R(0) = R(5) + R(0);
    R(3) = R(29) |R(29);
    { uint32_t ea_ = (R(2) + -26056); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = ld32(base, (R(4) + R(0)));
    ctx->ctr = R(12);
    GM_CALLV(0x800D64F8u, ctx->ctr, 0);
    goto L_800D6528;
L_800D64FC:;
    R(12) = ld32(base, (R(29) + 0));
    ctx->f[3].u = ctx->f[31].u;
    R(0) = rotl32(R(31), 2) & 0xFFFFFFFCu;
    R(4) = (R(2) + -26064);
    R(12) = ld32(base, (R(12) + 100));
    R(3) = R(29) |R(29);
    { uint32_t ea_ = (R(2) + -26056); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = ld32(base, (R(4) + R(0)));
    { uint32_t ea_ = (R(2) + -26120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x800D6528u, ctx->ctr, 0);
L_800D6528:;
    R(0) = lr;
}

/* fn_800D6550 (fn_800D6550, 68 bytes) */
static void pf_m_d6550(GM_CTX) {
    R(4) = ld32(base, (R(3) + 340));
    R(5) = (0 + 0x80370000u);
    R(12) = ld32(base, (R(3) + 0));
    R(5) = (R(5) + 3488);
    R(0) = (R(4) + -151);
    ctx->f[3].u = ctx->f[1].u;
    R(0) = cntlzw(R(0));
    R(12) = ld32(base, (R(12) + 100));
    R(4) = rotl32(R(0), 27) & 0x7FFFFFFu;
    { uint32_t ea_ = (R(2) + -26120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (R(4) + 152);
    R(0) = R(4) & 0xFFu;
    R(0) = ((int32_t)R(0) * 12);
    R(5) = R(5) + R(0);
    { uint32_t ea_ = (R(5) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D65E0 (fn_800D65E0, 580 bytes) */
static void pf_m_d65e0(GM_CTX) {
    GM_FN(0x800D65E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + -1);
    R(0) = ((int32_t)R(4) * 36);
    ctx->f[30].u = ctx->f[3].u;
    ctx->f[29].u = ctx->f[2].u;
    ctx->f[28].u = ctx->f[1].u;
    R(31) = (0 + 0x802F0000u);
    R(31) = (R(31) + 4944);
    R(30) = R(31) + R(0);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(6) = ld32(base, (R(3) + 348));
    st32(base, (R(3) + 340), R(5));
    cr_cmp_s(ctx, 0, (int32_t)R(6), (int32_t)R(4));
    st32(base, (R(3) + 348), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_800D6698; }
    R(0) = ld32(base, (R(30) + 16));
    st8(base, (R(3) + 92), R(0));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 140));
    ctx->ctr = R(12);
    GM_CALLV(0x800D6670u, ctx->ctr, 0);
    { uint32_t ea_ = (R(2) + -26120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { goto L_800D67E4; }
    R(12) = ld32(base, (R(28) + 0));
    ctx->f[1].u = ctx->f[30].u;
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 132));
    ctx->ctr = R(12);
    GM_CALLV(0x800D6694u, ctx->ctr, 0);
    goto L_800D67E4;
L_800D6698:;
    R(0) = (0 + 0);
    st32(base, (R(3) + 356), R(0));
    st32(base, (R(3) + 352), R(0));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 44));
    ctx->ctr = R(12);
    GM_CALLV(0x800D66B4u, ctx->ctr, 0);
    R(4) = ld32(base, (R(31) + 4));
    GM_CALLV(0x800D66BCu, 0x8023A0B0u, 0);
    R(31) = ld32(base, (R(30) + 4));
    st32(base, (f + 8), R(3));
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D6708; }
    R(12) = ld32(base, (R(28) + 0));
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 44));
    ctx->ctr = R(12);
    GM_CALLV(0x800D66E0u, ctx->ctr, 0);
    R(4) = R(31) |R(31);
    GM_CALLV(0x800D66E8u, 0x8023A0B0u, 0);
    st32(base, (f + 8), R(3));
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = (f + 8);
    R(12) = ld32(base, (R(28) + 0));
    R(12) = ld32(base, (R(12) + 124));
    ctx->ctr = R(12);
    GM_CALLV(0x800D6708u, ctx->ctr, 0);
L_800D6708:;
    { uint32_t ea_ = (R(2) + -26120); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[31].d);
    if ((CR_BIT(ctx, 2))) { goto L_800D6748; }
    R(3) = ld32(base, (f + 8));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 16), R(0));
    R(0) = ld16(base, (R(3) + 32));
    { uint32_t ea_ = (R(2) + -26072); ctx->f[1].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D677C; }
    ctx->f[31].u = ctx->f[30].u;
    goto L_800D677C;
L_800D6748:;
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[31].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D677C; }
    R(3) = ld32(base, (f + 8));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 16), R(0));
    R(0) = ld16(base, (R(3) + 32));
    { uint32_t ea_ = (R(2) + -26072); ctx->f[2].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (R(2) + -26116); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[1].d - ctx->f[0].d);
L_800D677C:;
    R(12) = ld32(base, (R(28) + 0));
    ctx->f[1].u = ctx->f[28].u;
    ctx->f[2].u = ctx->f[31].u;
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 112));
    ctx->f[3].u = ctx->f[29].u;
    R(4) = (f + 8);
    R(5) = ld32(base, (R(30) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x800D67A4u, ctx->ctr, 0);
    R(12) = ld32(base, (R(28) + 0));
    ctx->f[1].u = ctx->f[28].u;
    ctx->f[2].u = ctx->f[31].u;
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 116));
    ctx->f[3].u = ctx->f[29].u;
    R(4) = (f + 8);
    R(5) = ld32(base, (R(30) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x800D67CCu, ctx->ctr, 0);
    R(12) = ld32(base, (R(28) + 0));
    R(3) = R(28) |R(28);
    R(4) = ld32(base, (R(30) + 28));
    R(12) = ld32(base, (R(12) + 128));
    ctx->ctr = R(12);
    GM_CALLV(0x800D67E4u, ctx->ctr, 0);
L_800D67E4:;
    R(0) = lr;
}

/* fn_800D6840 (fn_800D6840, 240 bytes) */
static void pf_m_d6840(GM_CTX) {
    GM_FN(0x800D6840); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(6), 1);
    R(6) = (0 + 0x80310000u);
    R(6) = (R(6) + 32312);
    R(7) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D6874; }
    R(0) = ld32(base, (R(3) + 356));
    R(0) = R(0) & 0x200u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D6884; }
    R(7) = (0 + 1);
    goto L_800D6884;
L_800D6874:;
    R(0) = ld32(base, (R(3) + 352));
    R(0) = R(0) & 0x200u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D6884; }
    R(7) = (0 + 1);
L_800D6884:;
    cr_cmp_s(ctx, 0, (int32_t)R(7), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D690C; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 5);
    if ((CR_BIT(ctx, 2))) { goto L_800D68A8; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 8);
    if ((CR_BIT(ctx, 2))) { goto L_800D68C8; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 9);
    if ((CR_BIT(ctx, 2))) { goto L_800D68E8; }
    goto L_800D6904;
L_800D68A8:;
    R(0) = ld32(base, (R(3) + 360));
    R(3) = R(5) |R(5);
    R(4) = (R(6) + 0);
    R(5) = (0 + 32);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(4) + R(0)));
    GM_CALLV(0x800D68C4u, 0x802E19F8u, 0);
    goto L_800D6904;
L_800D68C8:;
    R(0) = ld32(base, (R(3) + 360));
    R(3) = R(5) |R(5);
    R(4) = (R(6) + 36);
    R(5) = (0 + 32);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(4) + R(0)));
    GM_CALLV(0x800D68E4u, 0x802E19F8u, 0);
    goto L_800D6904;
L_800D68E8:;
    R(0) = ld32(base, (R(3) + 360));
    R(3) = R(5) |R(5);
    R(4) = (R(6) + 72);
    R(5) = (0 + 32);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(4) + R(0)));
    GM_CALLV(0x800D6904u, 0x802E19F8u, 0);
L_800D6904:;
    R(3) = (0 + 1);
    goto L_800D6920;
L_800D690C:;
    R(4) = ld32(base, (R(3) + 360));
    R(0) = (0 + 0);
    st32(base, (R(3) + 364), R(4));
    st32(base, (R(3) + 360), R(0));
    R(3) = (0 + 0);
L_800D6920:;
    R(0) = lr;
}

/* fn_800D6930 (fn_800D6930, 4 bytes) */
static void pf_m_d6930(GM_CTX) {

}

/* fn_800D69B0 (fn_800D69B0, 120 bytes) */
static void pf_m_d69b0(GM_CTX) {
    R(5) = ld32(base, (R(3) + 36));
    ctx->f[0].u = ctx->f[2].u;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) return;
    R(0) = ld32(base, (R(5) + 380));
    R(0) = R(0) & 0x80u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) return;
    R(6) = ld32(base, (R(3) + 352));
    R(0) = R(6) & 0x2u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800D69E8; }
    R(0) = R(6) & 0x10u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800D69E8; }
    R(0) = R(6) & 0xC000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D6A00; }
L_800D69E8:;
    R(12) = ld32(base, (R(5) + 0));
    ctx->f[1].u = ctx->f[0].u;
    R(3) = R(5) |R(5);
    R(12) = ld32(base, (R(12) + 104));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
L_800D6A00:;
    R(0) = ld32(base, (R(3) + 360));
    ctx->f[2].u = ctx->f[3].u;
    st32(base, (R(5) + 360), R(0));
    ctx->f[3].u = ctx->f[0].u;
    R(3) = ld32(base, (R(3) + 36));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 100));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D6A30 (fn_800D6A30, 124 bytes) */
static void pf_m_d6a30(GM_CTX) {
    GM_FN(0x800D6A30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 396));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D6A90; }
    R(4) = R(0) ^ 0x80000000u;
    R(0) = (0 + 0x43300000u);
    { uint32_t ea_ = (R(3) + 392); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = R(3) + 388; ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); R(3) = ea_; }
    st32(base, (f + 12), R(4));
    { uint32_t ea_ = (R(2) + -26072); ctx->f[2].u = ld64(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d - ctx->f[1].d);
    st32(base, (f + 8), R(0));
    { uint32_t ea_ = (f + 8); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d / ctx->f[0].d);
    GM_CALLV(0x800D6A80u, 0x8015F470u, 0);
    R(3) = ld32(base, (R(31) + 396));
    R(0) = (R(3) + -1);
    st32(base, (R(31) + 396), R(0));
    goto L_800D6A98;
L_800D6A90:;
    { uint32_t ea_ = (R(3) + 392); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 388); stfs(base, ea_, ctx->f[0].d); }
L_800D6A98:;
    R(0) = lr;
}

/* isFootStepTiming__12dPyMdlBase_cFv (isFootStepTiming__12dPyMdlBase_cFv, 336 bytes) */
static void pf_isFootStepTiming__12dPyMdlBase_cFv_d6ab0(GM_CTX) {
    GM_FN(0x800D6AB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 340));
    R(0) = (R(4) + -1);
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 1))) { goto L_800D6B00; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 26);
    if ((CR_BIT(ctx, 2))) { goto L_800D6B00; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 110);
    if ((CR_BIT(ctx, 2))) { goto L_800D6B00; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 133);
    if ((CR_BIT(ctx, 2))) { goto L_800D6B30; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 131);
    if ((CR_BIT(ctx, 2))) { goto L_800D6B60; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 142);
    if ((CR_BIT(ctx, 2))) { goto L_800D6B90; }
    goto L_800D6BE8;
L_800D6B00:;
    { uint32_t ea_ = (R(2) + -26100); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 40);
    GM_CALLV(0x800D6B0Cu, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D6B28; }
    { uint32_t ea_ = (R(2) + -26052); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 40);
    GM_CALLV(0x800D6B20u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D6BE8; }
L_800D6B28:;
    R(3) = (0 + 1);
    goto L_800D6BEC;
L_800D6B30:;
    { uint32_t ea_ = (R(2) + -26048); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 40);
    GM_CALLV(0x800D6B3Cu, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D6B58; }
    { uint32_t ea_ = (R(2) + -26044); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 40);
    GM_CALLV(0x800D6B50u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D6BE8; }
L_800D6B58:;
    R(3) = (0 + 1);
    goto L_800D6BEC;
L_800D6B60:;
    { uint32_t ea_ = (R(2) + -26120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 40);
    GM_CALLV(0x800D6B6Cu, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D6B88; }
    { uint32_t ea_ = (R(2) + -26040); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 40);
    GM_CALLV(0x800D6B80u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D6BE8; }
L_800D6B88:;
    R(3) = (0 + 1);
    goto L_800D6BEC;
L_800D6B90:;
    { uint32_t ea_ = (R(2) + -26120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 40);
    GM_CALLV(0x800D6B9Cu, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D6BE0; }
    { uint32_t ea_ = (R(2) + -26036); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 40);
    GM_CALLV(0x800D6BB0u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D6BE0; }
    { uint32_t ea_ = (R(2) + -26040); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 40);
    GM_CALLV(0x800D6BC4u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800D6BE0; }
    { uint32_t ea_ = (R(2) + -26032); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 40);
    GM_CALLV(0x800D6BD8u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D6BE8; }
L_800D6BE0:;
    R(3) = (0 + 1);
    goto L_800D6BEC;
L_800D6BE8:;
    R(3) = (0 + 0);
L_800D6BEC:;
    R(0) = lr;
}

/* play__11dPyMdlMng_cFv (play__11dPyMdlMng_cFv, 20 bytes) */
static void pf_play__11dPyMdlMng_cFv_d6e90(GM_CTX) {
    R(3) = ld32(base, (R(3) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* calc__11dPyMdlMng_cFR6mMtx_c (calc__11dPyMdlMng_cFR6mMtx_c, 132 bytes) */
static void pf_calc__11dPyMdlMng_cFR6mMtx_c_d6eb0(GM_CTX) {
    GM_FN(0x800D6EB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80370000u);
    R(0) = (0 + 1);
    R(6) = (R(6) + 3488);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    st32(base, (R(3) + 8), R(0));
    R(5) = ld32(base, (R(3) + 4));
    R(3) = (f + 8);
    R(0) = ld8(base, (R(5) + 338));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = R(6) + R(0);
    { uint32_t ea_ = (R(4) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[1].u;
    ctx->f[3].u = ctx->f[1].u;
    GM_CALLV(0x800D6F00u, 0x801C0C60u, 0);
    R(3) = R(31) |R(31);
    R(5) = R(31) |R(31);
    R(4) = (f + 8);
    GM_CALLV(0x800D6F10u, 0x801C0540u, 0);
    R(3) = ld32(base, (R(30) + 4));
    R(4) = R(31) |R(31);
    GM_CALLV(0x800D6F1Cu, 0x800D5680u, 0);
    R(0) = lr;
}

/* calc__11dPyMdlMng_cF7mVec3_c7mAng3_c7mVec3_c (calc__11dPyMdlMng_cF7mVec3_c7mAng3_c7mVec3_c, 180 bytes) */
static void pf_calc__11dPyMdlMng_cF7mVec3_c7mAng3_c7mVe_d6f40(GM_CTX) {
    GM_FN(0x800D6F40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(8) = (0 + 0x80370000u);
    R(0) = (0 + 1);
    R(8) = (R(8) + 3488);
    st32(base, (R(3) + 8), R(0));
    R(7) = ld32(base, (R(3) + 4));
    { uint32_t ea_ = (R(6) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = ld8(base, (R(7) + 338));
    { uint32_t ea_ = (R(6) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(6) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(7) = R(8) + R(0);
    { uint32_t ea_ = (R(7) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[3].d);
    { uint32_t ea_ = (R(6) + 0); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 8); stfs(base, ea_, ctx->f[0].d); }
    R(6) = (f + 16);
    { uint32_t ea_ = (R(4) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(4) = (f + 28);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    R(0) = (int16_t)ld16(base, (R(5) + 0));
    st16(base, (f + 8), R(0));
    R(0) = (int16_t)ld16(base, (R(5) + 2));
    st16(base, (f + 10), R(0));
    R(0) = (int16_t)ld16(base, (R(5) + 4));
    R(5) = (f + 8);
    st16(base, (f + 12), R(0));
    R(3) = ld32(base, (R(3) + 4));
    GM_CALLV(0x800D6FE4u, 0x800D56F0u, 0);
    R(0) = lr;
}

/* calc2__11dPyMdlMng_cFv (calc2__11dPyMdlMng_cFv, 20 bytes) */
static void pf_calc2__11dPyMdlMng_cFv_d7000(GM_CTX) {
    R(3) = ld32(base, (R(3) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 32));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D7050 (fn_800D7050, 72 bytes) */
static void pf_m_d7050(GM_CTX) {
    GM_FN(0x800D7050); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(3) = (R(31) + 3488);
    GM_CALLV(0x800D706Cu, 0x8005DB00u, 0);
    R(4) = (0 + 0x80060000u);
    R(5) = (0 + 0x80370000u);
    R(3) = (R(31) + 3488);
    R(4) = (R(4) + -9248);
    R(5) = (R(5) + 3472);
    GM_CALLV(0x800D7084u, 0x802DC780u, 0);
    R(0) = lr;
}

/* __ct__18dPlayerOrchestra_cFv (__ct__18dPlayerOrchestra_cFv, 24 bytes) */
static void pf___ct__18dPlayerOrchestra_cFv_d70a0(GM_CTX) {
    R(4) = (0 + 0x80320000u);
    R(0) = (0 + 3);
    R(4) = (R(4) + -30064);
    st32(base, (R(3) + 0), R(4));
    st32(base, (R(3) + 4), R(0));
}

/* init__18dPlayerOrchestra_cFi (init__18dPlayerOrchestra_cFi, 28 bytes) */
static void pf_init__18dPlayerOrchestra_cFi_d70c0(GM_CTX) {
    R(0) = (0 + 0);
    st32(base, (R(3) + 8), R(4));
    st16(base, (R(3) + 16), R(0));
    st16(base, (R(3) + 18), R(0));
    st16(base, (R(3) + 12), R(0));
    st16(base, (R(3) + 14), R(0));
}

/* fn_800D7350 (fn_800D7350, 300 bytes) */
static void pf_m_d7350(GM_CTX) {
    cr_cmp_u(ctx, 0, R(5), 0x1u);
    GM_FRAME(32); gptr f = gm_frame_sp;
    if ((CR_BIT(ctx, 2))) { goto L_800D7364; }
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_800D7388; }
L_800D7364:;
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 12), R(4));
    { uint32_t ea_ = (R(2) + -26000); ctx->f[2].u = ld64(base, ea_); }
    st32(base, (f + 8), R(0));
    { uint32_t ea_ = (R(2) + -26020); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    goto L_800D73A8;
L_800D7388:;
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 12), R(4));
    { uint32_t ea_ = (R(2) + -26000); ctx->f[2].u = ld64(base, ea_); }
    st32(base, (f + 8), R(0));
    { uint32_t ea_ = (R(2) + -26016); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
L_800D73A8:;
    { uint32_t ea_ = (R(2) + -26012); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(5), 0x1u);
    R(6) = (R(6) + 1);
    R(0) = (R(7) + 1);
    { uint32_t ea_ = (R(3) + 60); stfs(base, ea_, ctx->f[1].d); }
    R(6) = rotl32(R(6), 4) & 0xFFFFFFF0u;
    R(0) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    { uint32_t ea_ = (R(3) + 76); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_800D73D4; }
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_800D73E0; }
L_800D73D4:;
    st32(base, (R(3) + 88), R(6));
    st32(base, (R(3) + 72), R(0));
    goto L_800D73E8;
L_800D73E0:;
    st32(base, (R(3) + 72), R(6));
    st32(base, (R(3) + 88), R(0));
L_800D73E8:;
    R(6) = (0 + 0x802F0000u);
    R(0) = rotl32(R(8), 2) & 0xFFFFFFFCu;
    R(6) = (R(6) + 11336);
    { uint32_t ea_ = (R(2) + -26016); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + R(0)); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(5), 0x1u);
    { uint32_t ea_ = (R(2) + -26008); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[3].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[3].d);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (f + 16); st64(base, ea_, ctx->f[0].u); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[1].d);
    R(6) = ld32(base, (f + 12));
    R(7) = ld32(base, (f + 20));
    if ((CR_BIT(ctx, 2))) { goto L_800D7430; }
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_800D744C; }
L_800D7430:;
    ctx->f[1].u = ctx->f[3].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(3) + 84); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].u = ctx->f[2].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(3) + 68); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 64); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 80); stfs(base, ea_, ctx->f[2].d); }
    goto L_800D7464;
L_800D744C:;
    ctx->f[1].u = ctx->f[3].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(3) + 68); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].u = ctx->f[2].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(3) + 64); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 84); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 80); stfs(base, ea_, ctx->f[0].d); }
L_800D7464:;
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 108), R(6));
    R(0) = ((int32_t)R(0) * (int32_t)R(7));
    st32(base, (R(3) + 104), R(0));
}

/* fn_800D7480 (fn_800D7480, 64 bytes) */
static void pf_m_d7480(GM_CTX) {
    { uint32_t ea_ = (R(3) + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[0].u;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D749C; }
    ctx->f[2].u = ctx->f[1].u;
    ctx->f[1].u = ctx->f[0].u;
L_800D749C:;
    { uint32_t ea_ = (R(3) + 92); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D74B0; }
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[1].d); }
    return;
L_800D74B0:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) return;
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[2].d); }
}

/* fn_800D74C0 (fn_800D74C0, 216 bytes) */
static void pf_m_d74c0(GM_CTX) {
    GM_FRAME(32); gptr f = gm_frame_sp;
    R(8) = (0 + 0x43300000u);
    R(0) = rotl32(R(7), 4) & 0xFFFFFFF0u;
    R(10) = ld32(base, (R(5) + 0));
    R(7) = R(3) + R(0);
    R(9) = ld32(base, (R(3) + 108));
    st32(base, (f + 8), R(8));
    R(0) = R(10) + R(9);
    { uint32_t ea_ = (R(7) + 64); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(6), R(0));
    st32(base, (f + 16), R(8));
    R(6) = R(6) - R(10);
    if ((CR_BIT(ctx, 0))) { goto L_800D7538; }
    st32(base, (f + 20), R(9));
    R(3) = (0 + 0);
    { uint32_t ea_ = (R(2) + -26000); ctx->f[4].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    st32(base, (f + 12), R(9));
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[4].d);
    { uint32_t ea_ = (R(2) + -25992); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[3].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[4].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[6].d * ctx->f[2].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(4) + 0); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(5) + 0), R(0));
    goto L_800D7590;
L_800D7538:;
    st32(base, (f + 12), R(6));
    R(0) = R(9) - R(6);
    { uint32_t ea_ = (R(2) + -26000); ctx->f[5].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[0].u = ld64(base, ea_); }
    st32(base, (f + 20), R(6));
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d - ctx->f[5].d);
    { uint32_t ea_ = (R(2) + -25992); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st32(base, (f + 12), R(6));
    { uint32_t ea_ = (f + 16); ctx->f[2].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[6].d * ctx->f[3].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[2].d - ctx->f[5].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[5].d);
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[6].d * ctx->f[2].d);
    st32(base, (R(3) + 100), R(0));
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (0 + 1);
L_800D7590:;
}

/* fn_800D7780 (fn_800D7780, 68 bytes) */
static void pf_m_d7780(GM_CTX) {
    R(4) = ld32(base, (R(3) + 104));
    R(6) = (0 + 0);
    R(0) = ld32(base, (R(3) + 108));
    R(7) = rotl32(R(4), 1) & 0xFFFFFFFEu;
    R(4) = ld32(base, (R(3) + 72));
    R(5) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(0) = ld32(base, (R(3) + 88));
    R(7) = R(7) + R(5);
    R(3) = ld32(base, (R(13) + -21632));
    R(7) = R(7) + R(4);
    R(7) = R(7) + R(0);
    CR0(ctx, R(7));
    if ((CR_BIT(ctx, 2))) { goto L_800D77BC; }
    R(0) = divwu(R(3), R(7));
    R(0) = ((int32_t)R(0) * (int32_t)R(7));
    R(6) = R(3) - R(0);
L_800D77BC:;
    R(3) = R(6) |R(6);
}

/* fn_800D77D0 (fn_800D77D0, 80 bytes) */
static void pf_m_d77d0(GM_CTX) {
    GM_FN(0x800D77D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(9) = (R(2) + -26024);
    { uint32_t ea_ = (R(2) + -26012); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = ld8(base, (R(9) + R(5)));
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + 117), R(0));
    GM_CALLV(0x800D77FCu, 0x800D7350u, 0);
    R(0) = ld32(base, (R(13) + -21632));
    R(3) = R(31) |R(31);
    st32(base, (R(31) + 112), R(0));
    GM_CALLV(0x800D780Cu, 0x800D79B0u, 0);
    R(0) = lr;
}

/* fn_800D7820 (fn_800D7820, 92 bytes) */
static void pf_m_d7820(GM_CTX) {
    GM_FN(0x800D7820); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(31) = ld32(base, (R(13) + -21632));
    R(0) = ld32(base, (R(3) + 112));
    cr_cmp_u(ctx, 0, R(31), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800D785C; }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x800D7858u, ctx->ctr, 0);
    st32(base, (R(30) + 112), R(31));
L_800D785C:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x800D7864u, 0x800D7480u, 0);
    R(0) = lr;
}

/* fn_800D7880 (fn_800D7880, 248 bytes) */
static void pf_m_d7880(GM_CTX) {
    GM_FN(0x800D7880); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(31) = R(3) |R(3);
    GM_CALLV(0x800D789Cu, 0x800D7780u, 0);
    { uint32_t ea_ = (R(2) + -26012); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    R(30) = (0 + 0x802F0000u);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    R(28) = R(3) |R(3);
    R(25) = (0 + 0);
    st32(base, (f + 8), R(0));
    R(30) = (R(30) + 11352);
    R(29) = (R(2) + -25984);
L_800D78C0:;
    R(0) = rotl32(R(25), 30) & 0xC0000000u;
    R(5) = rotl32(R(25), 1) & 0x1u;
    R(3) = R(0) - R(5);
    R(6) = R(28) |R(28);
    R(4) = rotl32(R(3), 2) & 0xFFFFFFFFu;
    { int32_t v_ = (int32_t)R(25); ctx->xer_ca = v_ < 0 && (v_ & 0x3u) != 0; R(0) = (v_ >> 2); }
    R(27) = R(4) + R(5);
    R(3) = R(31) |R(31);
    { uint64_t t_ = (uint64_t)(R(0)) + (0) + ctx->xer_ca; R(0) = t_; ctx->xer_ca = (t_ >> 32); }
    R(5) = (f + 8);
    R(4) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(26) = ld32(base, (R(29) + R(4)));
    R(0) = ((int32_t)R(27) * 12);
    R(4) = (f + 12);
    R(7) = R(26) |R(26);
    R(12) = R(30) + R(0);
    GM_CALLV(0x800D7904u, 0x802DCBFCu, 0);
    R(0) = R(0) | 0x0u;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D794C; }
    R(0) = ld32(base, (R(13) + -21632));
    R(4) = (0 + 0x80320000u);
    st32(base, (R(31) + 112), R(0));
    R(0) = rotl32(R(27), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + -30048);
    R(3) = R(31) |R(31);
    st8(base, (R(31) + 116), R(26));
    R(4) = ld32(base, (R(4) + R(0)));
    R(12) = ld32(base, (R(31) + 0));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x800D7940u, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D7948u, 0x800D7480u, 0);
    goto L_800D7960;
L_800D794C:;
    R(25) = (R(25) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(25), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800D78C0; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x800D7960u, 0x800D7480u, 0);
L_800D7960:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_800D79B0 (fn_800D79B0, 40 bytes) */
static void pf_m_d79b0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 108));
    R(4) = (0 + 0);
    st8(base, (R(3) + 116), R(4));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 5920);
    st32(base, (R(3) + 100), R(0));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D79E0 (fn_800D79E0, 4 bytes) */
static void pf_m_d79e0(GM_CTX) {

}

/* fn_800D79F0 (fn_800D79F0, 4 bytes) */
static void pf_m_d79f0(GM_CTX) {

}

/* fn_800D7A00 (fn_800D7A00, 132 bytes) */
static void pf_m_d7a00(GM_CTX) {
    R(4) = ld8(base, (R(3) + 116));
    R(0) = ld32(base, (R(3) + 100));
    R(4) = rotl32(R(4), 4) & 0xFFFFFFF0u;
    { uint32_t ea_ = (R(3) + 96); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = R(3) + R(4);
    { uint32_t ea_ = (R(3) + 92); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 64); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t a_ = R(0); R(0) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[2].d);
    st32(base, (R(3) + 100), R(0));
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) return;
    R(0) = ld32(base, (R(3) + 104));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D7A60; }
    st32(base, (R(3) + 100), R(0));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 5984);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
L_800D7A60:;
    R(0) = ld32(base, (R(3) + 108));
    R(4) = (0 + 0x80370000u);
    st32(base, (R(3) + 100), R(0));
    R(4) = (R(4) + 6048);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D7A90 (fn_800D7A90, 4 bytes) */
static void pf_m_d7a90(GM_CTX) {

}

/* fn_800D7AA0 (fn_800D7AA0, 4 bytes) */
static void pf_m_d7aa0(GM_CTX) {

}

/* fn_800D7AB0 (fn_800D7AB0, 68 bytes) */
static void pf_m_d7ab0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 100));
    { uint32_t ea_ = (R(3) + 92); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t a_ = R(0); R(0) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    st32(base, (R(3) + 100), R(0));
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) return;
    R(0) = ld32(base, (R(3) + 108));
    R(4) = (0 + 0x80370000u);
    st32(base, (R(3) + 100), R(0));
    R(4) = (R(4) + 6048);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D7B00 (fn_800D7B00, 4 bytes) */
static void pf_m_d7b00(GM_CTX) {

}

/* fn_800D7B10 (fn_800D7B10, 4 bytes) */
static void pf_m_d7b10(GM_CTX) {

}

/* fn_800D7B20 (fn_800D7B20, 92 bytes) */
static void pf_m_d7b20(GM_CTX) {
    R(4) = ld8(base, (R(3) + 116));
    R(0) = ld32(base, (R(3) + 100));
    R(4) = rotl32(R(4), 4) & 0xFFFFFFF0u;
    { uint32_t ea_ = (R(3) + 96); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = R(3) + R(4);
    { uint32_t ea_ = (R(3) + 92); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 64); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t a_ = R(0); R(0) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    st32(base, (R(3) + 100), R(0));
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) return;
    R(0) = ld32(base, (R(4) + 72));
    R(4) = (0 + 0x80370000u);
    st32(base, (R(3) + 100), R(0));
    R(4) = (R(4) + 6112);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D7B80 (fn_800D7B80, 32 bytes) */
static void pf_m_d7b80(GM_CTX) {
    R(0) = ld8(base, (R(3) + 116));
    { uint32_t ea_ = (R(2) + -26012); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[0].d); }
    R(4) = R(3) + R(0);
    { uint32_t ea_ = (R(4) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_800D7BA0 (fn_800D7BA0, 16 bytes) */
static void pf_m_d7ba0(GM_CTX) {
    R(0) = ld8(base, (R(3) + 116));
    R(0) = R(0) ^ 0x1u;
    st8(base, (R(3) + 116), R(0));
}

/* fn_800D7BB0 (fn_800D7BB0, 52 bytes) */
static void pf_m_d7bb0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 100));
    { uint32_t a_ = R(0); R(0) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    st32(base, (R(3) + 100), R(0));
    if ((!CR_BIT(ctx, 2))) return;
    R(0) = ld32(base, (R(3) + 108));
    R(4) = (0 + 0x80370000u);
    st32(base, (R(3) + 100), R(0));
    R(4) = (R(4) + 5920);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800D7C80 (fn_800D7C80, 824 bytes) */
static void pf_m_d7c80(GM_CTX) {
    GM_FN(0x800D7C80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 176);
    R(29) = (0 + 0x80320000u);
    R(28) = (0 + 0x80370000u);
    R(29) = (R(29) + -30048);
    R(3) = (R(29) + 16);
    R(27) = ld32(base, (R(29) + 16));
    R(6) = (R(29) + 28);
    R(5) = (R(29) + 40);
    R(12) = ld32(base, (R(3) + 4));
    R(28) = (R(28) + 5904);
    R(11) = ld32(base, (R(3) + 8));
    R(4) = (R(29) + 160);
    R(10) = ld32(base, (R(29) + 28));
    R(3) = (R(28) + 16);
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 40));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 116), R(27));
    st32(base, (f + 120), R(12));
    st32(base, (f + 124), R(11));
    st32(base, (f + 128), R(10));
    st32(base, (f + 132), R(9));
    st32(base, (f + 136), R(8));
    st32(base, (f + 140), R(7));
    st32(base, (f + 144), R(6));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x800D7D04u, 0x8015F7C0u, 0);
    R(30) = (0 + 0x80320000u);
    R(3) = (R(28) + 16);
    R(27) = ld32(base, (f + 140));
    R(30) = (R(30) + -29736);
    R(12) = ld32(base, (f + 144));
    R(31) = (0 + 0x800D0000u);
    R(11) = ld32(base, (f + 148));
    R(4) = (R(31) + 32704);
    R(10) = ld32(base, (f + 128));
    R(5) = (R(28) + 0);
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(28) + 16), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x800D7D6Cu, 0x802DC780u, 0);
    R(3) = (R(29) + 52);
    R(6) = (R(29) + 64);
    R(5) = (R(29) + 76);
    R(27) = ld32(base, (R(29) + 52));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 200);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 80);
    R(10) = ld32(base, (R(29) + 64));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 76));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 80), R(27));
    st32(base, (f + 84), R(12));
    st32(base, (f + 88), R(11));
    st32(base, (f + 92), R(10));
    st32(base, (f + 96), R(9));
    st32(base, (f + 100), R(8));
    st32(base, (f + 104), R(7));
    st32(base, (f + 108), R(6));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x800D7DCCu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 80);
    R(27) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(31) + 32704);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(28) + 64);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(28) + 80), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x800D7E28u, 0x802DC780u, 0);
    R(3) = (R(29) + 88);
    R(6) = (R(29) + 100);
    R(5) = (R(29) + 112);
    R(27) = ld32(base, (R(29) + 88));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 236);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 144);
    R(10) = ld32(base, (R(29) + 100));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 112));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 44), R(27));
    st32(base, (f + 48), R(12));
    st32(base, (f + 52), R(11));
    st32(base, (f + 56), R(10));
    st32(base, (f + 60), R(9));
    st32(base, (f + 64), R(8));
    st32(base, (f + 68), R(7));
    st32(base, (f + 72), R(6));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x800D7E88u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 144);
    R(27) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(31) + 32704);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(28) + 128);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(28) + 144), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x800D7EE4u, 0x802DC780u, 0);
    R(3) = (R(29) + 124);
    R(6) = (R(29) + 136);
    R(5) = (R(29) + 148);
    R(27) = ld32(base, (R(29) + 124));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 276);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 208);
    R(10) = ld32(base, (R(29) + 136));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 148));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 8), R(27));
    st32(base, (f + 12), R(12));
    st32(base, (f + 16), R(11));
    st32(base, (f + 20), R(10));
    st32(base, (f + 24), R(9));
    st32(base, (f + 28), R(8));
    st32(base, (f + 32), R(7));
    st32(base, (f + 36), R(6));
    st32(base, (f + 40), R(0));
    GM_CALLV(0x800D7F44u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 208);
    R(29) = ld32(base, (f + 32));
    R(12) = ld32(base, (f + 36));
    R(7) = R(27) |R(27);
    R(11) = ld32(base, (f + 40));
    R(4) = (R(31) + 32704);
    R(10) = ld32(base, (f + 20));
    R(5) = (R(28) + 192);
    R(9) = ld32(base, (f + 24));
    R(8) = ld32(base, (f + 28));
    R(6) = ld32(base, (f + 12));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(28) + 208), R(30));
    st32(base, (R(3) + 12), R(29));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x800D7FA0u, 0x802DC780u, 0);
    R(11) = (f + 176);
    R(0) = lr;
}

/* fn_800D80B0 (fn_800D80B0, 28 bytes) */
static void pf_m_d80b0(GM_CTX) {
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[6].d); }
}

/* fn_800D80D0 (fn_800D80D0, 244 bytes) */
static void pf_m_d80d0(GM_CTX) {
    { uint32_t ea_ = (R(3) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -25976); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D810C; }
    { uint32_t ea_ = (R(3) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D8124; }
    ctx->f[3].u = ctx->f[2].u;
    goto L_800D8124;
L_800D810C:;
    { uint32_t ea_ = (R(3) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D8124; }
    ctx->f[3].u = ctx->f[2].u;
L_800D8124:;
    { uint32_t ea_ = (R(3) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D813C; }
    ctx->f[3].u = ctx->f[0].u;
    goto L_800D8150;
L_800D813C:;
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D8150; }
    ctx->f[3].u = ctx->f[0].u;
L_800D8150:;
    { uint32_t ea_ = (R(3) + 16); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[2].u ^ 0x8000000000000000ull;
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D81B4; }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D81B4; }
    { uint32_t ea_ = (R(2) + -25976); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800D8198; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D81B8; }
    ctx->f[1].u = ctx->f[0].u;
    ctx->f[3].u = ctx->f[0].u;
    goto L_800D81B8;
L_800D8198:;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800D81B8; }
    ctx->f[1].u = ctx->f[0].u;
    ctx->f[3].u = ctx->f[0].u;
    goto L_800D81B8;
L_800D81B4:;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[3].d);
L_800D81B8:;
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[3].d); }
}

/* fn_800D81D0 (fn_800D81D0, 16 bytes) */
static void pf_m_d81d0(GM_CTX) {
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
}

/* __ct__14dPropelParts_cFv (__ct__14dPropelParts_cFv, 160 bytes) */
static void pf___ct__14dPropelParts_cFv_d81e0(GM_CTX) {
    GM_FN(0x800D81E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -25968); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (R(5) + -29664);
    R(0) = ld32(base, (R(2) + -26192));
    R(4) = (0 + 4);
    R(31) = (0 + 0);
    R(30) = (R(3) + 20);
    R(29) = R(3) |R(3);
    st32(base, (R(3) + 0), R(5));
    st32(base, (R(3) + 4), R(31));
    st32(base, (R(3) + 8), R(4));
    st16(base, (R(3) + 12), R(0));
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[0].d); }
    R(3) = R(30) |R(30);
    GM_CALLV(0x800D8234u, 0x802D7AA0u, 0);
    { uint32_t ea_ = (R(2) + -25964); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x80330000u);
    R(3) = (R(3) + -26280);
    st32(base, (R(30) + 0), R(3));
    R(3) = R(29) |R(29);
    st32(base, (R(30) + 276), R(31));
    st32(base, (R(30) + 280), R(31));
    st8(base, (R(30) + 284), R(31));
    st8(base, (R(30) + 285), R(31));
    st32(base, (R(30) + 288), R(31));
    st32(base, (R(30) + 292), R(31));
    { uint32_t ea_ = (R(29) + 316); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* create__14dPropelParts_cFP8dActor_c (create__14dPropelParts_cFP8dActor_c, 28 bytes) */
static void pf_create__14dPropelParts_cFP8dActor_c_d8280(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D8290; }
    st32(base, (R(3) + 4), R(4));
    st32(base, (R(4) + 904), R(3));
L_800D8290:;
    R(0) = (0 + 4);
    st32(base, (R(3) + 8), R(0));
}

/* update__14dPropelParts_cFRC6mMtx_c (update__14dPropelParts_cFRC6mMtx_c, 376 bytes) */
static void pf_update__14dPropelParts_cFRC6mMtx_c_d82a0(GM_CTX) {
    GM_FN(0x800D82A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800D82F4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800D8328; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800D835C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((CR_BIT(ctx, 2))) { goto L_800D8390; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((CR_BIT(ctx, 2))) { goto L_800D83AC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    if ((CR_BIT(ctx, 2))) { goto L_800D83D4; }
    goto L_800D83F4;
L_800D82F4:;
    R(4) = (0 + 16384);
    R(5) = (0 + 2048);
    R(3) = (R(3) + 12);
    GM_CALLV(0x800D8304u, 0x8015F340u, 0);
    { uint32_t ea_ = (R(2) + -25960); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 16);
    { uint32_t ea_ = (R(2) + -25956); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x800D8314u, 0x8015F470u, 0);
    { uint32_t ea_ = (R(2) + -25968); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 316);
    { uint32_t ea_ = (R(2) + -25952); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x800D8324u, 0x8015F470u, 0);
    goto L_800D83F4;
L_800D8328:;
    R(4) = (0 + 8192);
    R(5) = (0 + 256);
    R(3) = (R(3) + 12);
    GM_CALLV(0x800D8338u, 0x8015F340u, 0);
    { uint32_t ea_ = (R(2) + -25968); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 16);
    { uint32_t ea_ = (R(2) + -25952); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x800D8348u, 0x8015F470u, 0);
    { uint32_t ea_ = (R(2) + -25948); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 316);
    { uint32_t ea_ = (R(2) + -25952); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x800D8358u, 0x8015F470u, 0);
    goto L_800D83F4;
L_800D835C:;
    R(4) = (0 + 16384);
    R(5) = (0 + 2048);
    R(3) = (R(3) + 12);
    GM_CALLV(0x800D836Cu, 0x8015F340u, 0);
    { uint32_t ea_ = (R(2) + -25960); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 16);
    { uint32_t ea_ = (R(2) + -25956); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x800D837Cu, 0x8015F470u, 0);
    { uint32_t ea_ = (R(2) + -25964); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 316);
    { uint32_t ea_ = (R(2) + -25952); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x800D838Cu, 0x8015F470u, 0);
    goto L_800D83F4;
L_800D8390:;
    { uint32_t ea_ = (R(2) + -25968); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(2) + -25964); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st16(base, (R(3) + 12), R(0));
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 316); stfs(base, ea_, ctx->f[0].d); }
    goto L_800D83F4;
L_800D83AC:;
    R(0) = ld32(base, (R(2) + -26192));
    R(5) = (0 + 128);
    R(3) = (R(3) + 12);
    R(4) = (int16_t)R(0);
    GM_CALLV(0x800D83C0u, 0x8015F340u, 0);
    { uint32_t ea_ = (R(2) + -25968); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -25964); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 316); stfs(base, ea_, ctx->f[0].d); }
    goto L_800D83F4;
L_800D83D4:;
    R(4) = (0 + 16384);
    R(5) = (0 + 2048);
    R(3) = (R(3) + 12);
    GM_CALLV(0x800D83E4u, 0x8015F340u, 0);
    { uint32_t ea_ = (R(2) + -25968); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -25964); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 316); stfs(base, ea_, ctx->f[0].d); }
L_800D83F4:;
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x800D8400u, 0x800D8420u, 0);
    R(0) = lr;
}

/* fn_8014A6F0 (fn_8014A6F0, 624 bytes) */
static void pf_m_4a6f0(GM_CTX) {
    GM_FN(0x8014A6F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(3) = (0 + 3440);
    GM_CALLV(0x8014A70Cu, 0x801628C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8014A944; }
    GM_CALLV(0x8014A71Cu, 0x80064110u, 0);
    R(4) = (0 + 0x80320000u);
    R(3) = (R(31) + 916);
    R(4) = (R(4) + 26164);
    st32(base, (R(31) + 96), R(4));
    GM_CALLV(0x8014A730u, 0x80069020u, 0);
    R(29) = (0 + 0);
    st32(base, (R(31) + 944), R(29));
    R(3) = (R(31) + 948);
    GM_CALLV(0x8014A740u, 0x80169CD0u, 0);
    st32(base, (R(31) + 1012), R(29));
    R(3) = (0 + 0x80330000u);
    R(3) = (R(3) + -27176);
    st32(base, (R(31) + 1016), R(3));
    R(3) = (R(31) + 1028);
    st32(base, (R(31) + 1020), R(29));
    st32(base, (R(31) + 1024), R(29));
    GM_CALLV(0x8014A760u, 0x8016A5E0u, 0);
    R(3) = (0 + 0x80330000u);
    R(3) = (R(3) + -27272);
    st32(base, (R(31) + 1016), R(3));
    R(3) = (R(31) + 1060);
    st32(base, (R(31) + 1056), R(29));
    GM_CALLV(0x8014A778u, 0x8007F7A0u, 0);
    st32(base, (R(31) + 1312), R(29));
    R(3) = (0 + 0x80320000u);
    R(3) = (R(3) + 16704);
    R(4) = (0 + 0x80320000u);
    st32(base, (R(31) + 1320), R(3));
    R(28) = (R(31) + 1336);
    { uint32_t ea_ = (R(2) + -22156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (R(4) + 16688);
    { uint32_t ea_ = (R(31) + 1324); stfs(base, ea_, ctx->f[0].d); }
    R(3) = R(28) |R(28);
    { uint32_t ea_ = (R(31) + 1328); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 1332); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 1320), R(4));
    GM_CALLV(0x8014A7B0u, 0x802D7AA0u, 0);
    R(30) = (0 + 0x80310000u);
    R(4) = (0 + 0x80320000u);
    R(30) = (R(30) + -30080);
    st32(base, (R(28) + 0), R(30));
    { uint32_t ea_ = (R(2) + -22156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(28) = (R(31) + 1628);
    { uint32_t ea_ = (R(31) + 1616); stfs(base, ea_, ctx->f[0].d); }
    R(4) = (R(4) + 16672);
    R(3) = R(28) |R(28);
    { uint32_t ea_ = (R(31) + 1620); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 1624); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 1612), R(4));
    GM_CALLV(0x8014A7E4u, 0x802D7AA0u, 0);
    R(3) = (0 + 0x80330000u);
    R(4) = (0 + 0x80320000u);
    R(3) = (R(3) + -26280);
    st32(base, (R(28) + 0), R(3));
    R(27) = (R(31) + 1940);
    { uint32_t ea_ = (R(2) + -22156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (R(28) + 276), R(29));
    R(4) = (R(4) + 16656);
    R(3) = R(27) |R(27);
    st32(base, (R(28) + 280), R(29));
    st8(base, (R(28) + 284), R(29));
    st8(base, (R(28) + 285), R(29));
    st32(base, (R(28) + 288), R(29));
    st32(base, (R(28) + 292), R(29));
    { uint32_t ea_ = (R(31) + 1928); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 1932); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 1936); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 1924), R(4));
    GM_CALLV(0x8014A830u, 0x802D7AA0u, 0);
    st32(base, (R(27) + 0), R(30));
    R(4) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -22156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(27) = (R(31) + 2232);
    { uint32_t ea_ = (R(31) + 2220); stfs(base, ea_, ctx->f[0].d); }
    R(4) = (R(4) + 16640);
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(31) + 2224); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 2228); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 2216), R(4));
    GM_CALLV(0x8014A85Cu, 0x802D7AA0u, 0);
    st32(base, (R(27) + 0), R(30));
    R(4) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -22156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(27) = (R(31) + 2524);
    { uint32_t ea_ = (R(31) + 2512); stfs(base, ea_, ctx->f[0].d); }
    R(4) = (R(4) + 16624);
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(31) + 2516); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 2520); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 2508), R(4));
    GM_CALLV(0x8014A888u, 0x802D7AA0u, 0);
    st32(base, (R(27) + 0), R(30));
    R(4) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -22156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(27) = (R(31) + 2816);
    { uint32_t ea_ = (R(31) + 2804); stfs(base, ea_, ctx->f[0].d); }
    R(4) = (R(4) + 16608);
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(31) + 2808); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 2812); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 2800), R(4));
    GM_CALLV(0x8014A8B4u, 0x802D7AA0u, 0);
    st32(base, (R(27) + 0), R(30));
    R(4) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -22156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(27) = (R(31) + 3108);
    { uint32_t ea_ = (R(31) + 3096); stfs(base, ea_, ctx->f[0].d); }
    R(4) = (R(4) + 16592);
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(31) + 3100); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 3104); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 3092), R(4));
    GM_CALLV(0x8014A8E0u, 0x802D7AA0u, 0);
    st32(base, (R(27) + 0), R(30));
    R(9) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -22156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(9) = (R(9) + 16576);
    { uint32_t ea_ = (R(31) + 3388); stfs(base, ea_, ctx->f[0].d); }
    R(8) = (R(31) + 1320);
    R(7) = (R(31) + 1612);
    R(6) = (R(31) + 1924);
    { uint32_t ea_ = (R(31) + 3392); stfs(base, ea_, ctx->f[0].d); }
    R(5) = (R(31) + 2216);
    R(4) = (R(31) + 2508);
    R(3) = (R(31) + 2800);
    { uint32_t ea_ = (R(31) + 3396); stfs(base, ea_, ctx->f[0].d); }
    R(0) = (R(31) + 3092);
    R(10) = (R(31) + 3384);
    st32(base, (R(31) + 3384), R(9));
    st32(base, (R(31) + 3432), R(31));
    st32(base, (R(31) + 3400), R(8));
    st32(base, (R(31) + 3404), R(7));
    st32(base, (R(31) + 3408), R(6));
    st32(base, (R(31) + 3412), R(5));
    st32(base, (R(31) + 3416), R(4));
    st32(base, (R(31) + 3420), R(3));
    st32(base, (R(31) + 3424), R(0));
    st32(base, (R(31) + 3428), R(10));
L_8014A944:;
    R(11) = (f + 32);
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_8014A960 (fn_8014A960, 396 bytes) */
static void pf_m_4a960(GM_CTX) {
    GM_FN(0x8014A960); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014A978u, 0x8014AAF0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014A980u, 0x80162590u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014A998; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014A990u, 0x80162510u, 0);
    R(3) = (0 + 1);
    goto L_8014AAD8;
L_8014A998:;
    { uint32_t ea_ = (R(2) + -22152); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(6) = (0 + 0x80360000u);
    { uint32_t ea_ = (R(31) + 1288); stfs(base, ea_, ctx->f[1].d); }
    R(7) = (0 + 0x80150000u);
    R(10) = (R(6) + -29844);
    R(8) = (0 + 0x80150000u);
    { uint32_t ea_ = (R(31) + 1292); stfs(base, ea_, ctx->f[1].d); }
    R(9) = (0 + 0x80150000u);
    { uint32_t ea_ = (R(2) + -22148); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(31) + 1296); stfs(base, ea_, ctx->f[1].d); }
    R(4) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -22140); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(31) + 1060);
    { uint32_t ea_ = (R(6) + -29844); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    R(5) = (f + 24);
    { uint32_t ea_ = (R(10) + 4); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    R(6) = (f + 16);
    { uint32_t ea_ = (R(10) + 8); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[7].d * ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[6].d * ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -22144); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 208); stfs(base, ea_, ctx->f[1].d); }
    R(7) = (R(7) + -20480);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[4].d * ctx->f[3].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[2].d * ctx->f[3].d);
    { uint32_t ea_ = (R(31) + 216); stfs(base, ea_, ctx->f[1].d); }
    R(8) = (R(8) + -20448);
    ctx->f[1].u = ctx->f[4].u ^ 0x8000000000000000ull;
    R(9) = (R(9) + -20416);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d + ctx->f[3].d);
    ctx->f[0].u = ctx->f[3].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[7].d); }
    R(10) = (0 + 1);
    { uint32_t ea_ = (R(31) + 212); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d + ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
    ctx->f[2].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    R(11) = ld8(base, (R(31) + 911));
    st32(base, (f + 8), R(11));
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (f + 12), R(0));
    GM_CALLV(0x8014AA68u, 0x8007FAD0u, 0);
    R(0) = (0 + 1384);
    st32(base, (R(31) + 1268), R(0));
    R(3) = (R(31) + 1060);
    GM_CALLV(0x8014AA78u, 0x8007F900u, 0);
    R(3) = (R(31) + 1016);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x8014AA88u, 0x80167B60u, 0);
    { uint32_t ea_ = (R(2) + -22156); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 948);
    R(4) = (R(31) + 1016);
    GM_CALLV(0x8014AA98u, 0x80169F80u, 0);
    R(3) = (R(31) + 1312);
    R(4) = (0 + 1);
    R(5) = (0 + 0);
    GM_CALLV(0x8014AAA8u, 0x800B80E0u, 0);
    R(3) = (R(31) + 1312);
    R(4) = (0 + 0);
    GM_CALLV(0x8014AAB4u, 0x800B8250u, 0);
    R(3) = (R(31) + 1312);
    R(4) = (0 + 1);
    GM_CALLV(0x8014AAC0u, 0x800B8250u, 0);
    { uint32_t ea_ = (R(2) + -22168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 1);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 64); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 68));
    st32(base, (R(31) + 1300), R(0));
L_8014AAD8:;
    R(0) = lr;
}

/* fn_8014AAF0 (fn_8014AAF0, 252 bytes) */
static void pf_m_4aaf0(GM_CTX) {
    GM_FN(0x8014AAF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80370000u);
    R(6) = (0 + 0);
    R(7) = (0 + 32);
    R(30) = R(3) |R(3);
    R(3) = (R(3) + 916);
    R(5) = ld32(base, (R(4) + 31816));
    R(4) = (0 + -1);
    GM_CALLV(0x8014AB24u, 0x800690C0u, 0);
    R(3) = ld32(base, (R(13) + -22088));
    R(5) = (0 + 0x80320000u);
    R(5) = (R(5) + 26148);
    R(4) = (R(13) + -25312);
    R(3) = (R(3) + 4);
    GM_CALLV(0x8014AB3Cu, 0x800DF180u, 0);
    st32(base, (R(30) + 944), R(3));
    R(3) = (R(30) + 944);
    R(4) = ld32(base, (R(13) + -25320));
    GM_CALLV(0x8014AB4Cu, 0x80239E30u, 0);
    st32(base, (f + 16), R(3));
    R(31) = R(3) |R(3);
    R(3) = (R(30) + 948);
    R(4) = (f + 16);
    R(5) = (R(30) + 916);
    R(6) = (0 + 32);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x8014AB70u, 0x80169D90u, 0);
    R(3) = (R(30) + 948);
    GM_CALLV(0x8014AB78u, 0x80064BF0u, 0);
    R(4) = ld32(base, (R(13) + -25316));
    R(3) = (R(30) + 944);
    GM_CALLV(0x8014AB84u, 0x8023A270u, 0);
    st32(base, (R(30) + 1012), R(3));
    R(4) = (f + 12);
    R(5) = (f + 8);
    R(6) = (R(30) + 916);
    st32(base, (f + 8), R(3));
    R(3) = (R(30) + 1016);
    R(7) = (0 + 0);
    R(8) = (0 + 1);
    st32(base, (f + 12), R(31));
    GM_CALLV(0x8014ABACu, 0x80167420u, 0);
    R(0) = ld32(base, (R(30) + 1012));
    R(3) = (R(30) + 1016);
    st32(base, (f + 20), R(0));
    R(4) = (R(30) + 948);
    R(5) = (f + 20);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x8014ABCCu, 0x80167800u, 0);
    R(3) = (R(30) + 916);
    GM_CALLV(0x8014ABD4u, 0x800690E0u, 0);
    R(0) = lr;
}

/* fn_8014ABF0 (fn_8014ABF0, 4 bytes) */
static void pf_m_4abf0(GM_CTX) {

}

/* fn_8014AC00 (fn_8014AC00, 8 bytes) */
static void pf_m_4ac00(GM_CTX) {
    R(3) = (0 + 1);
}

/* fn_8014AC10 (fn_8014AC10, 412 bytes) */
static void pf_m_4ac10(GM_CTX) {
    GM_FN(0x8014AC10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    GM_CALLV(0x8014AC38u, 0x80162590u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(3) |R(3);
    if ((!CR_BIT(ctx, 2))) { goto L_8014AC50; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014AC4Cu, 0x80162510u, 0);
    goto L_8014AD88;
L_8014AC50:;
    R(5) = ld32(base, (R(29) + 1300));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 24), R(0));
    R(4) = R(5) ^ 0x80000000u;
    { uint32_t ea_ = (R(2) + -22128); ctx->f[2].u = ld64(base, ea_); }
    st32(base, (f + 28), R(4));
    { uint32_t ea_ = (R(2) + -22160); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); ctx->f[1].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(2) + -22144); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014AC88; }
    { uint32_t ea_ = (R(2) + -22156); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    goto L_8014ACA8;
L_8014AC88:;
    st32(base, (f + 28), R(4));
    { uint32_t ea_ = (R(2) + -22164); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (f + 24), R(0));
    { uint32_t ea_ = (f + 24); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014ACA8; }
    { uint32_t ea_ = (R(2) + -22148); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
L_8014ACA8:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014ACBC; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014ACB8u, 0x8014AEF0u, 0);
    goto L_8014AD88;
L_8014ACBC:;
    R(3) = (R(3) + 3748);
    GM_CALLV(0x8014ACC4u, 0x8005E780u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014AD38; }
    R(0) = ld32(base, (R(29) + 1308));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014AD10; }
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(31) = ld32(base, (R(13) + -22136));
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x8014ACF0u, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(0) = ld8(base, (R(4) + 0));
    R(5) = (0 + 6);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    R(4) = (int8_t)R(0);
    GM_CALLV(0x8014AD10u, 0x800D8BB0u, 0);
L_8014AD10:;
    R(3) = ld32(base, (R(29) + 1304));
    R(0) = (0 + 10);
    st32(base, (R(29) + 1308), R(0));
    R(0) = (R(3) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    st32(base, (R(29) + 1304), R(0));
    if ((CR_BIT(ctx, 0))) { goto L_8014AD38; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014AD34u, 0x8014AEF0u, 0);
    goto L_8014AD88;
L_8014AD38:;
    R(0) = ld32(base, (R(29) + 1308));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014AD48; }
    { uint32_t ea_ = (R(2) + -22136); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
L_8014AD48:;
    R(0) = ld32(base, (R(29) + 1300));
    R(0) = R(0) & 0x2u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014AD58; }
    ctx->f[31].u = ctx->f[31].u ^ 0x8000000000000000ull;
L_8014AD58:;
    ctx->f[1].u = ctx->f[31].u;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014AD64u, 0x801393D0u, 0);
    R(4) = R(30) |R(30);
    R(3) = (f + 8);
    GM_CALLV(0x8014AD70u, 0x80139420u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 172); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 176); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 180); stfs(base, ea_, ctx->f[0].d); }
L_8014AD88:;
    R(0) = lr;
}

/* fn_8014ADB0 (fn_8014ADB0, 128 bytes) */
static void pf_m_4adb0(GM_CTX) {
    GM_FN(0x8014ADB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 1300));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014ADD8; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 1300), R(0));
L_8014ADD8:;
    R(4) = ld32(base, (R(3) + 1308));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014ADEC; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 1308), R(0));
L_8014ADEC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014ADF4u, 0x8014AC10u, 0);
    R(3) = (R(31) + 1312);
    GM_CALLV(0x8014ADFCu, 0x800B8110u, 0);
    R(12) = ld32(base, (R(31) + 1016));
    R(3) = (R(31) + 1016);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8014AE10u, ctx->ctr, 0);
    R(3) = (R(31) + 1060);
    GM_CALLV(0x8014AE18u, 0x8007FDA0u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* setRevivalBreakIce__10daPlyIce_cFv (setRevivalBreakIce__10daPlyIce_cFv, 200 bytes) */
static void pf_setRevivalBreakIce__10daPlyIce_cFv_4aef0(GM_CTX) {
    GM_FN(0x8014AEF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x8014AF0Cu, 0x80162590u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8014AF54; }
    GM_CALLV(0x8014AF1Cu, 0x80139460u, 0);
    R(3) = R(31) |R(31);
    R(31) = ld32(base, (R(13) + -22136));
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x8014AF34u, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(0) = ld8(base, (R(4) + 0));
    R(5) = (0 + 4);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    R(4) = (int8_t)R(0);
    GM_CALLV(0x8014AF54u, 0x800D8BB0u, 0);
L_8014AF54:;
    R(31) = ld32(base, (R(13) + -22816));
    R(3) = (f + 8);
    R(4) = (R(30) + 172);
    GM_CALLV(0x8014AF64u, 0x8006A4B0u, 0);
    R(3) = R(31) |R(31);
    R(5) = (f + 8);
    R(4) = (0 + 620);
    R(6) = (0 + 0);
    GM_CALLV(0x8014AF78u, 0x80198C30u, 0);
    R(0) = ld32(base, (R(30) + 1312));
    R(3) = (R(30) + 1312);
    R(4) = (0 + 2);
    R(0) = R(0) & 0xFFFFFFFDu;
    st32(base, (R(30) + 1312), R(0));
    GM_CALLV(0x8014AF90u, 0x800B8250u, 0);
    R(3) = (R(30) + 1312);
    GM_CALLV(0x8014AF98u, 0x800B82D0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014AFA0u, 0x80162510u, 0);
    R(0) = lr;
}

/* fn_8014AFC0 (fn_8014AFC0, 56 bytes) */
static void pf_m_4afc0(GM_CTX) {
    GM_FN(0x8014AFC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld32(base, (R(3) + 1276));
    R(0) = R(0) & 0xEu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014AFE4; }
    GM_CALLV(0x8014AFDCu, 0x8014AE30u, 0);
    R(3) = (0 + 1);
    goto L_8014AFE8;
L_8014AFE4:;
    R(3) = (0 + 0);
L_8014AFE8:;
    R(0) = lr;
}

/* fn_8014B000 (fn_8014B000, 32 bytes) */
static void pf_m_4b000(GM_CTX) {
    GM_FN(0x8014B000); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x8014B010u, 0x8014AFC0u, 0);
    R(0) = lr;
}

/* fn_8014B040 (fn_8014B040, 32 bytes) */
static void pf_m_4b040(GM_CTX) {
    GM_FN(0x8014B040); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x8014B050u, 0x8014AFC0u, 0);
    R(0) = lr;
}

/* fn_8014B060 (fn_8014B060, 204 bytes) */
static void pf_m_4b060(GM_CTX) {
    GM_FN(0x8014B060); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (R(3) + 256);
    R(5) = (0 + 1);
    R(31) = R(3) |R(3);
    R(3) = (R(3) + 172);
    GM_CALLV(0x8014B084u, 0x80064AF0u, 0);
    { uint32_t ea_ = (R(2) + -22140); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 124);
    { uint32_t ea_ = (R(31) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 180); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x8014B0A0u, 0x801C0BD0u, 0);
    R(0) = ld16(base, (R(31) + 258));
    R(3) = (R(31) + 124);
    st16(base, (f + 16), R(0));
    R(4) = (f + 16);
    GM_CALLV(0x8014B0B4u, 0x8016EDD0u, 0);
    R(0) = ld16(base, (R(31) + 256));
    R(3) = (R(31) + 124);
    st16(base, (f + 12), R(0));
    R(4) = (f + 12);
    GM_CALLV(0x8014B0C8u, 0x8016ECB0u, 0);
    R(0) = ld16(base, (R(31) + 260));
    R(3) = (R(31) + 124);
    st16(base, (f + 8), R(0));
    R(4) = (f + 8);
    GM_CALLV(0x8014B0DCu, 0x8016EEF0u, 0);
    R(3) = (R(31) + 948);
    R(4) = (R(31) + 124);
    GM_CALLV(0x8014B0E8u, 0x8016A170u, 0);
    R(3) = (R(31) + 948);
    R(4) = (R(31) + 1288);
    GM_CALLV(0x8014B0F4u, 0x8016A150u, 0);
    R(3) = (R(31) + 948);
    R(4) = (0 + 0);
    GM_CALLV(0x8014B100u, 0x8016A1A0u, 0);
    R(12) = ld32(base, (R(31) + 948));
    R(3) = (R(31) + 948);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8014B114u, ctx->ctr, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_8014B130 (fn_8014B130, 388 bytes) */
static void pf_m_4b130(GM_CTX) {
    GM_FN(0x8014B130); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8014B290; }
    { uint32_t a_ = R(3); R(31) = a_ + 0x520u; ctx->xer_ca = R(31) < a_; }
    CR0(ctx, R(31));
    if ((CR_BIT(ctx, 2))) { goto L_8014B244; }
    { uint32_t a_ = R(31); R(3) = a_ + 0x6F4u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B180; }
    { uint32_t a_ = R(3); R(3) = a_ + 0x10u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B180; }
    if ((CR_BIT(ctx, 2))) { goto L_8014B180; }
    R(4) = (0 + 0);
    GM_CALLV(0x8014B180u, 0x802D7B20u, 0);
L_8014B180:;
    { uint32_t a_ = R(31); R(3) = a_ + 0x5D0u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B19C; }
    { uint32_t a_ = R(3); R(3) = a_ + 0x10u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B19C; }
    if ((CR_BIT(ctx, 2))) { goto L_8014B19C; }
    R(4) = (0 + 0);
    GM_CALLV(0x8014B19Cu, 0x802D7B20u, 0);
L_8014B19C:;
    { uint32_t a_ = R(31); R(3) = a_ + 0x4ACu; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B1B8; }
    { uint32_t a_ = R(3); R(3) = a_ + 0x10u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B1B8; }
    if ((CR_BIT(ctx, 2))) { goto L_8014B1B8; }
    R(4) = (0 + 0);
    GM_CALLV(0x8014B1B8u, 0x802D7B20u, 0);
L_8014B1B8:;
    { uint32_t a_ = R(31); R(3) = a_ + 0x388u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B1D4; }
    { uint32_t a_ = R(3); R(3) = a_ + 0x10u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B1D4; }
    if ((CR_BIT(ctx, 2))) { goto L_8014B1D4; }
    R(4) = (0 + 0);
    GM_CALLV(0x8014B1D4u, 0x802D7B20u, 0);
L_8014B1D4:;
    { uint32_t a_ = R(31); R(3) = a_ + 0x264u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B1F0; }
    { uint32_t a_ = R(3); R(3) = a_ + 0x10u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B1F0; }
    if ((CR_BIT(ctx, 2))) { goto L_8014B1F0; }
    R(4) = (0 + 0);
    GM_CALLV(0x8014B1F0u, 0x802D7B20u, 0);
L_8014B1F0:;
    { uint32_t a_ = R(31); R(0) = a_ + 0x12Cu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014B228; }
    { uint32_t a_ = R(0); R(30) = a_ + 0x10u; ctx->xer_ca = R(30) < a_; }
    CR0(ctx, R(30));
    if ((CR_BIT(ctx, 2))) { goto L_8014B228; }
    R(4) = (0 + 0x80330000u);
    R(3) = R(30) |R(30);
    R(4) = (R(4) + -26280);
    st32(base, (R(30) + 0), R(4));
    GM_CALLV(0x8014B214u, 0x8016D4B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014B228; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x8014B228u, 0x802D7B20u, 0);
L_8014B228:;
    { uint32_t a_ = R(31); R(3) = a_ + 0x8u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B244; }
    { uint32_t a_ = R(3); R(3) = a_ + 0x10u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B244; }
    if ((CR_BIT(ctx, 2))) { goto L_8014B244; }
    R(4) = (0 + 0);
    GM_CALLV(0x8014B244u, 0x802D7B20u, 0);
L_8014B244:;
    R(3) = (R(28) + 1060);
    R(4) = (0 + -1);
    GM_CALLV(0x8014B250u, 0x8007F810u, 0);
    R(3) = (R(28) + 1016);
    R(4) = (0 + -1);
    GM_CALLV(0x8014B25Cu, 0x801676A0u, 0);
    R(3) = (R(28) + 948);
    R(4) = (0 + -1);
    GM_CALLV(0x8014B268u, 0x80169D20u, 0);
    R(3) = (R(28) + 916);
    R(4) = (0 + -1);
    GM_CALLV(0x8014B274u, 0x80069060u, 0);
    R(3) = R(28) |R(28);
    R(4) = (0 + 0);
    GM_CALLV(0x8014B280u, 0x800642B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8014B290; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x8014B290u, 0x80162920u, 0);
L_8014B290:;
    R(3) = R(28) |R(28);
    R(0) = lr;
}

/* fn_8014B2C0 (fn_8014B2C0, 48 bytes) */
static void pf_m_4b2c0(GM_CTX) {
    GM_FN(0x8014B2C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 6088);
    GM_CALLV(0x8014B2D4u, 0x801628C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014B2E0; }
    GM_CALLV(0x8014B2E0u, 0x8014B2F0u, 0);
L_8014B2E0:;
    R(0) = lr;
}

/* fn_8014B2F0 (fn_8014B2F0, 312 bytes) */
static void pf_m_4b2f0(GM_CTX) {
    GM_FN(0x8014B2F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(27) = R(3) |R(3);
    GM_CALLV(0x8014B30Cu, 0x800460D0u, 0);
    R(4) = (0 + 0x80320000u);
    R(3) = (R(27) + 5332);
    R(4) = (R(4) + 26516);
    st32(base, (R(27) + 96), R(4));
    R(4) = (0 + 5);
    GM_CALLV(0x8014B324u, 0x800D6CC0u, 0);
    R(3) = (0 + 0x80320000u);
    R(9) = (0 + 0x80300000u);
    R(8) = (0 + 0x80320000u);
    R(7) = (0 + 0x80320000u);
    R(3) = (R(3) + 27672);
    R(9) = (R(9) + -5384);
    R(8) = (R(8) + 27720);
    R(7) = (R(7) + 27744);
    R(30) = (0 + 0);
    R(6) = (0 + 0x80370000u);
    st32(base, (R(27) + 5344), R(3));
    R(5) = (R(27) + 5352);
    R(4) = (R(27) + 5348);
    R(3) = (R(27) + 5368);
    st32(base, (R(27) + 5348), R(9));
    R(6) = (R(6) + 31236);
    st32(base, (R(27) + 5352), R(8));
    st32(base, (R(27) + 5356), R(7));
    st32(base, (R(27) + 5360), R(27));
    st32(base, (R(27) + 5364), R(30));
    GM_CALLV(0x8014B378u, 0x8015FC90u, 0);
    R(3) = (0 + 0x80320000u);
    R(29) = (R(27) + 5484);
    R(3) = (R(3) + 27624);
    st32(base, (R(27) + 5344), R(3));
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014B390u, 0x802D7AA0u, 0);
    R(31) = (0 + 0x80330000u);
    R(28) = (R(27) + 5780);
    R(31) = (R(31) + -26280);
    st32(base, (R(29) + 0), R(31));
    R(3) = R(28) |R(28);
    st32(base, (R(29) + 276), R(30));
    st32(base, (R(29) + 280), R(30));
    st8(base, (R(29) + 284), R(30));
    st8(base, (R(29) + 285), R(30));
    st32(base, (R(29) + 288), R(30));
    st32(base, (R(29) + 292), R(30));
    GM_CALLV(0x8014B3C0u, 0x802D7AA0u, 0);
    st32(base, (R(28) + 0), R(31));
    R(3) = R(27) |R(27);
    R(4) = (0 + 2);
    st32(base, (R(28) + 276), R(30));
    st32(base, (R(28) + 280), R(30));
    st8(base, (R(28) + 284), R(30));
    st8(base, (R(28) + 285), R(30));
    st32(base, (R(28) + 288), R(30));
    st32(base, (R(28) + 292), R(30));
    GM_CALLV(0x8014B3E8u, 0x800646E0u, 0);
    R(0) = (R(27) + 5332);
    R(3) = (0 + 4);
    st8(base, (R(27) + 910), R(3));
    R(3) = R(27) |R(27);
    R(4) = ld32(base, (R(27) + 5336));
    st8(base, (R(27) + 877), R(30));
    st32(base, (R(27) + 3560), R(0));
    st32(base, (R(4) + 32), R(27));
    GM_CALLV(0x8014B40Cu, 0x80060F20u, 0);
    R(11) = (f + 32);
    R(3) = R(27) |R(27);
    R(0) = lr;
}

/* fn_8014B580 (fn_8014B580, 236 bytes) */
static void pf_m_4b580(GM_CTX) {
    GM_FN(0x8014B580); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8014B64C; }
    { uint32_t a_ = R(3); R(31) = a_ + 0x1694u; ctx->xer_ca = R(31) < a_; }
    CR0(ctx, R(31));
    if ((CR_BIT(ctx, 2))) { goto L_8014B5D8; }
    R(4) = (0 + 0x80330000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + -26280);
    st32(base, (R(31) + 0), R(4));
    GM_CALLV(0x8014B5C4u, 0x8016D4B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014B5D8; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x8014B5D8u, 0x802D7B20u, 0);
L_8014B5D8:;
    { uint32_t a_ = R(29); R(31) = a_ + 0x156Cu; ctx->xer_ca = R(31) < a_; }
    CR0(ctx, R(31));
    if ((CR_BIT(ctx, 2))) { goto L_8014B608; }
    R(4) = (0 + 0x80330000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + -26280);
    st32(base, (R(31) + 0), R(4));
    GM_CALLV(0x8014B5F4u, 0x8016D4B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014B608; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x8014B608u, 0x802D7B20u, 0);
L_8014B608:;
    { uint32_t a_ = R(29); R(0) = a_ + 0x14E0u; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014B624; }
    if ((CR_BIT(ctx, 2))) { goto L_8014B624; }
    { uint32_t a_ = R(0); R(3) = a_ + 0x18u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8014B624; }
    R(4) = (0 + 0);
    GM_CALLV(0x8014B624u, 0x8015F9F0u, 0);
L_8014B624:;
    R(3) = (R(29) + 5332);
    R(4) = (0 + -1);
    GM_CALLV(0x8014B630u, 0x800D6E00u, 0);
    R(3) = R(29) |R(29);
    R(4) = (0 + 0);
    GM_CALLV(0x8014B63Cu, 0x800467C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8014B64C; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014B64Cu, 0x80162920u, 0);
L_8014B64C:;
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* fn_8014B850 (fn_8014B850, 112 bytes) */
static void pf_m_4b850(GM_CTX) {
    GM_FN(0x8014B850); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014B878; }
    R(3) = (0 + 0);
    goto L_8014B8AC;
L_8014B878:;
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x8014B880u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014B898; }
    R(0) = ld8(base, (R(3) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8014B898; }
    GM_CALLV(0x8014B898u, 0x80162510u, 0);
L_8014B898:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014B8A0u, 0x80047190u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014B8A8u, 0x8005FA00u, 0);
    R(3) = (0 + 1);
L_8014B8AC:;
    R(0) = lr;
}

/* fn_8014B8C0 (fn_8014B8C0, 92 bytes) */
static void pf_m_4b8c0(GM_CTX) {
    GM_FN(0x8014B8C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014B8D8u, 0x80046AB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014B8E8; }
    R(3) = (0 + 0);
    goto L_8014B908;
L_8014B8E8:;
    R(3) = ld32(base, (R(31) + 5448));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014B904; }
    R(0) = (R(3) + -1);
    st32(base, (R(31) + 5448), R(0));
    R(3) = (0 + 0);
    goto L_8014B908;
L_8014B904:;
    R(3) = (0 + 1);
L_8014B908:;
    R(0) = lr;
}

/* YoshiStateOrig (YoshiStateOrig, 236 bytes) */
static void pf_YoshiStateOrig_4b920(GM_CTX) {
    GM_FN(0x8014B920); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(31) = (R(31) + 27320);
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(0) = ld8(base, (R(3) + 909));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 0))) { goto L_8014B9DC; }
    R(12) = ld32(base, (R(29) + 0));
    R(3) = R(29) |R(29);
    R(4) = (R(31) + 16);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8014B974u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014B9DC; }
    R(12) = ld32(base, (R(29) + 0));
    R(3) = R(29) |R(29);
    R(4) = (R(31) + 80);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8014B994u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014B9DC; }
    R(12) = ld32(base, (R(29) + 0));
    R(3) = R(29) |R(29);
    R(4) = (R(31) + 144);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8014B9B4u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014B9DC; }
    R(12) = ld32(base, (R(29) + 0));
    R(3) = R(29) |R(29);
    R(4) = (R(31) + 844);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8014B9D4u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014B9EC; }
L_8014B9DC:;
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    GM_CALLV(0x8014B9ECu, 0x80047390u, 0);
L_8014B9EC:;
    R(0) = lr;
}

/* fn_8014BA10 (fn_8014BA10, 16 bytes) */
static void pf_m_4ba10(GM_CTX) {
    R(0) = rotl32(R(4), 1) & 0x1FEu;
    R(3) = (R(2) + -22092);
    R(3) = (int16_t)ld16(base, (R(3) + R(0)));
}

/* fn_8014BA20 (fn_8014BA20, 180 bytes) */
static void pf_m_4ba20(GM_CTX) {
    GM_FN(0x8014BA20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 176);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014BA3Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014BA84; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = ld8(base, (R(31) + 5440));
    R(12) = ld32(base, (R(12) + 1092));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BA5Cu, ctx->ctr, 0);
    { uint32_t ea_ = (R(2) + -22088); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = R(3) |R(3);
    R(3) = (R(31) + 258);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    R(4) = (int16_t)R(0);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[0].u); }
    R(5) = ld32(base, (f + 12));
    R(5) = (int16_t)R(5);
    GM_CALLV(0x8014BA80u, 0x8015F340u, 0);
    goto L_8014BAC0;
L_8014BA84:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = ld8(base, (R(31) + 840));
    R(12) = ld32(base, (R(12) + 1092));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BA9Cu, ctx->ctr, 0);
    { uint32_t ea_ = (R(2) + -22088); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = R(3) |R(3);
    R(3) = (R(31) + 258);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    R(4) = (int16_t)R(0);
    { uint32_t ea_ = (f + 16); st64(base, ea_, ctx->f[0].u); }
    R(5) = ld32(base, (f + 20));
    R(5) = (int16_t)R(5);
    GM_CALLV(0x8014BAC0u, 0x8015F340u, 0);
L_8014BAC0:;
    R(0) = lr;
}

/* fn_8014BAE0 (fn_8014BAE0, 248 bytes) */
static void pf_m_4bae0(GM_CTX) {
    GM_FN(0x8014BAE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 203);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014BAFCu, 0x80056C70u, 0);
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014BB40; }
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0);
    { uint32_t ea_ = (R(5) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 48); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014BB34u, ctx->ctr, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 5284), R(0));
    goto L_8014BB74;
L_8014BB40:;
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 6);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BB6Cu, ctx->ctr, 0);
    R(0) = (0 + 1);
    st32(base, (R(31) + 5284), R(0));
L_8014BB74:;
    R(3) = ld32(base, (R(31) + 5408));
    GM_CALLV(0x8014BB7Cu, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014BB90; }
    R(3) = ld32(base, (R(31) + 5336));
    R(0) = (0 + 0);
    st32(base, (R(3) + 660), R(0));
L_8014BB90:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 964));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BBA4u, ctx->ctr, 0);
    { uint32_t ea_ = (R(3) + 0); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -30748); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 236); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 276); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(31) + 280); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 284); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 5416); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_8014BBE0 (fn_8014BBE0, 8 bytes) */
static void pf_m_4bbe0(GM_CTX) {
    R(4) = (0 + 203);
    GM_TAIL(0x80056CB0u, 0); return;
}

/* fn_8014BBF0 (fn_8014BBF0, 596 bytes) */
static void pf_m_4bbf0(GM_CTX) {
    GM_FN(0x8014BBF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 964));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BC14u, ctx->ctr, 0);
    { uint32_t ea_ = (R(3) + 0); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -30748); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 236); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 276); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(31) + 280); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 284); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 5416); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(31) + 96));
    R(12) = ld32(base, (R(12) + 1096));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BC48u, ctx->ctr, 0);
    R(0) = ld32(base, (R(31) + 5284));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8014BC68; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014BCB0; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8014BD94; }
    goto L_8014BE00;
L_8014BC68:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014BC74u, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014BCB0; }
    R(0) = (0 + 0);
    st32(base, (R(31) + 5284), R(0));
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0);
    { uint32_t ea_ = (R(5) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 48); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014BCB0u, ctx->ctr, 0);
L_8014BCB0:;
    { uint32_t ea_ = (R(31) + 5416); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22072); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014BCC8; }
    { uint32_t ea_ = (R(2) + -22068); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 236); stfs(base, ea_, ctx->f[0].d); }
L_8014BCC8:;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 268);
    { uint32_t ea_ = (R(2) + -22064); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x8014BCD8u, 0x8015F470u, 0);
    GM_CALLV(0x8014BCDCu, 0x8006A1F0u, 0);
    R(0) = R(3) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 0))) { goto L_8014BD50; }
    R(0) = ld8(base, (R(31) + 840));
    R(4) = (0 + 2);
    R(5) = (0 + 0x80370000u);
    R(3) = (R(2) + -22080);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    st32(base, (R(31) + 5284), R(4));
    R(4) = ld32(base, (R(3) + R(0)));
    R(5) = (R(5) + 3488);
    R(3) = ld32(base, (R(31) + 5336));
    R(0) = R(4) & 0xFFu;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = ((int32_t)R(0) * 12);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 92));
    R(5) = R(5) + R(0);
    { uint32_t ea_ = (R(5) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 48); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014BD34u, ctx->ctr, 0);
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 132));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BD4Cu, ctx->ctr, 0);
    goto L_8014BE30;
L_8014BD50:;
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8014BE00; }
    R(0) = (0 + 1);
    st32(base, (R(31) + 5284), R(0));
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22060); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 6);
    { uint32_t ea_ = (R(5) + 116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014BD90u, ctx->ctr, 0);
    goto L_8014BE00;
L_8014BD94:;
    { uint32_t ea_ = (R(31) + 236); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(31) + 268);
    { uint32_t ea_ = (R(31) + 5416); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22056); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x8014BDACu, 0x8015F470u, 0);
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014BE00; }
    R(0) = (0 + 2);
    st32(base, (R(31) + 5284), R(0));
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 7);
    { uint32_t ea_ = (R(5) + 128); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 132); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014BDECu, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 1044));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BE00u, ctx->ctr, 0);
L_8014BE00:;
    { uint32_t ea_ = (R(31) + 268); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { goto L_8014BE30; }
    R(4) = ld8(base, (R(31) + 840));
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014BE1Cu, 0x800557E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014BE30; }
    R(0) = ld8(base, (R(31) + 840));
    R(0) = R(0) ^ 0x1u;
    st8(base, (R(31) + 840), R(0));
L_8014BE30:;
    R(0) = lr;
}

/* fn_8014BE50 (fn_8014BE50, 340 bytes) */
static void pf_m_4be50(GM_CTX) {
    GM_FN(0x8014BE50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 126);
    R(31) = (0 + 0);
    R(30) = R(3) |R(3);
    st8(base, (R(3) + 840), R(31));
    GM_CALLV(0x8014BE78u, 0x80056C70u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 122);
    GM_CALLV(0x8014BE84u, 0x80056C70u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 170);
    GM_CALLV(0x8014BE90u, 0x80056C70u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 151);
    GM_CALLV(0x8014BE9Cu, 0x80056C70u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 168);
    GM_CALLV(0x8014BEA8u, 0x80056C70u, 0);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = (0 + 5);
    { uint32_t ea_ = (R(30) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 284); stfs(base, ea_, ctx->f[3].d); }
    R(3) = ld32(base, (R(30) + 5336));
    { uint32_t ea_ = (R(30) + 236); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(30) + 268); stfs(base, ea_, ctx->f[3].d); }
    st32(base, (R(30) + 5288), R(0));
    { uint32_t ea_ = (R(30) + 184); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 188); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 192); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(3) + 660), R(31));
    R(0) = ld32(base, (R(30) + 4308));
    R(0) = R(0) & 0x4000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014BF34; }
    { uint32_t ea_ = (R(2) + -22052); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22048); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -30748); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 36);
    { uint32_t ea_ = (R(30) + 236); stfs(base, ea_, ctx->f[2].d); }
    R(3) = ld32(base, (R(30) + 5336));
    st32(base, (R(30) + 5284), R(31));
    { uint32_t ea_ = (R(2) + -22060); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 276); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 280); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(5) + 476); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BF30u, ctx->ctr, 0);
    goto L_8014BF74;
L_8014BF34:;
    { uint32_t ea_ = (R(2) + -30748); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(30) + 236); stfs(base, ea_, ctx->f[3].d); }
    R(5) = (0 + 0x80370000u);
    R(3) = ld32(base, (R(30) + 5336));
    ctx->f[2].u = ctx->f[3].u;
    { uint32_t ea_ = (R(30) + 276); stfs(base, ea_, ctx->f[3].d); }
    R(5) = (R(5) + 3488);
    R(4) = (0 + 115);
    st32(base, (R(30) + 5284), R(0));
    { uint32_t ea_ = (R(30) + 280); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(5) + 1424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014BF74u, ctx->ctr, 0);
L_8014BF74:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 193);
    R(5) = (0 + 0);
    GM_CALLV(0x8014BF84u, 0x80057E70u, 0);
    R(0) = (0 + 0);
    st16(base, (R(30) + 258), R(0));
    R(0) = lr;
}

/* fn_8014BFB0 (fn_8014BFB0, 108 bytes) */
static void pf_m_4bfb0(GM_CTX) {
    GM_FN(0x8014BFB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 168);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014BFCCu, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 151);
    GM_CALLV(0x8014BFD8u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 126);
    GM_CALLV(0x8014BFE4u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 122);
    GM_CALLV(0x8014BFF0u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 170);
    GM_CALLV(0x8014BFFCu, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 187);
    GM_CALLV(0x8014C008u, 0x80056CB0u, 0);
    R(0) = lr;
}

/* fn_8014C020 (fn_8014C020, 336 bytes) */
static void pf_m_4c020(GM_CTX) {
    GM_FN(0x8014C020); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 5284));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C054; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8014C09C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8014C10C; }
    goto L_8014C15C;
L_8014C054:;
    R(0) = ld32(base, (R(3) + 5288));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C15C; }
    R(12) = ld32(base, (R(3) + 96));
    R(4) = ld8(base, (R(3) + 840));
    R(12) = ld32(base, (R(12) + 1092));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C074u, ctx->ctr, 0);
    st16(base, (R(31) + 258), R(3));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (R(4) + 27336);
    R(12) = ld32(base, (R(12) + 660));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C098u, ctx->ctr, 0);
    goto L_8014C15C;
L_8014C09C:;
    R(3) = ld32(base, (R(3) + 5336));
    { uint32_t ea_ = (R(2) + -22116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014C0ACu, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C0C0; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 122);
    GM_CALLV(0x8014C0C0u, 0x80056CB0u, 0);
L_8014C0C0:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014C0CCu, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C15C; }
    R(0) = (0 + 2);
    st32(base, (R(31) + 5284), R(0));
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 116);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 1436); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C108u, ctx->ctr, 0);
    goto L_8014C15C;
L_8014C10C:;
    R(3) = ld32(base, (R(3) + 5336));
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014C118u, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C15C; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = ld8(base, (R(31) + 840));
    R(12) = ld32(base, (R(12) + 1092));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C138u, ctx->ctr, 0);
    st16(base, (R(31) + 258), R(3));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (R(4) + 27336);
    R(12) = ld32(base, (R(12) + 660));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C15Cu, ctx->ctr, 0);
L_8014C15C:;
    R(0) = lr;
}

/* fn_8014C170 (fn_8014C170, 136 bytes) */
static void pf_m_4c170(GM_CTX) {
    GM_FN(0x8014C170); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(31) = ld32(base, (R(3) + 5336));
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x8014C194u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C1A4; }
    R(0) = (0 + 0);
    st32(base, (R(31) + 660), R(0));
L_8014C1A4:;
    R(3) = ld32(base, (R(30) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 142);
    { uint32_t ea_ = (R(5) + 1748); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 1752); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014C1D0u, ctx->ctr, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 190);
    R(5) = (0 + 0);
    GM_CALLV(0x8014C1E0u, 0x80057E70u, 0);
    R(0) = lr;
}

/* fn_8014C200 (fn_8014C200, 56 bytes) */
static void pf_m_4c200(GM_CTX) {
    GM_FN(0x8014C200); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 132);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014C21Cu, 0x80056CB0u, 0);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 268); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_8014C240 (fn_8014C240, 240 bytes) */
static void pf_m_4c240(GM_CTX) {
    GM_FN(0x8014C240); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 964));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C264u, ctx->ctr, 0);
    { uint32_t ea_ = (R(3) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -30748); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 276); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 280); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(31) + 96));
    R(12) = ld32(base, (R(12) + 1096));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C288u, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014C290u, 0x8014C330u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 132);
    GM_CALLV(0x8014C29Cu, 0x80056C70u, 0);
    R(4) = ld8(base, (R(31) + 840));
    R(3) = (0 + 0x80430000u);
    R(0) = ld32(base, (R(31) + 4308));
    R(3) = (R(3) + -18368);
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(2) + -22068); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + R(4)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = R(0) & 0x18000000u;
    CR0(ctx, R(0));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 268); stfs(base, ea_, ctx->f[1].d); }
    if ((CR_BIT(ctx, 2))) { goto L_8014C2D4; }
    { uint32_t ea_ = (R(2) + -22104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 268); stfs(base, ea_, ctx->f[0].d); }
L_8014C2D4:;
    R(4) = ld8(base, (R(31) + 840));
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C2F4; }
    R(0) = ld32(base, (R(31) + 4308));
    R(3) = rotl32(R(0), 27) & 0x1u;
    R(0) = rotl32(R(0), 13) & 0x1u;
    R(0) = R(3) |R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8014C310; }
L_8014C2F4:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C31C; }
    R(0) = ld32(base, (R(31) + 4308));
    R(3) = rotl32(R(0), 26) & 0x1u;
    R(0) = rotl32(R(0), 12) & 0x1u;
    R(0) = R(3) |R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014C31C; }
L_8014C310:;
    R(0) = ld8(base, (R(31) + 840));
    R(0) = R(0) ^ 0x1u;
    st8(base, (R(31) + 840), R(0));
L_8014C31C:;
    R(0) = lr;
}

/* fn_8014C330 (fn_8014C330, 100 bytes) */
static void pf_m_4c330(GM_CTX) {
    GM_FN(0x8014C330); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 15);
    R(4) = (f + 8);
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5336));
    GM_CALLV(0x8014C354u, 0x800D5790u, 0);
    R(12) = ld32(base, (R(31) + 5484));
    R(4) = (0 + 0x80320000u);
    R(3) = (R(31) + 5484);
    R(6) = (f + 8);
    R(12) = ld32(base, (R(12) + 160));
    R(4) = (R(4) + 26388);
    R(5) = (0 + 0);
    R(7) = (0 + 0);
    R(8) = (0 + 0);
    ctx->ctr = R(12);
    GM_CALLV(0x8014C380u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_8014C3A0 (fn_8014C3A0, 92 bytes) */
static void pf_m_4c3a0(GM_CTX) {
    GM_FN(0x8014C3A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 122);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014C3BCu, 0x80056C70u, 0);
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 113);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 1400); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C3E8u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_8014C400 (fn_8014C400, 8 bytes) */
static void pf_m_4c400(GM_CTX) {
    R(4) = (0 + 122);
    GM_TAIL(0x80056CB0u, 0); return;
}

/* fn_8014C410 (fn_8014C410, 228 bytes) */
static void pf_m_4c410(GM_CTX) {
    GM_FN(0x8014C410); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014C428u, 0x8004C480u, 0);
    { uint32_t ea_ = (R(2) + -30748); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 280); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 272); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8014C440u, 0x8004BA50u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 1096));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C454u, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 912));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C468u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C4E0; }
    R(3) = (R(31) + 3748);
    GM_CALLV(0x8014C478u, 0x8005E6F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C4AC; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -30776); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 1020));
    R(5) = (0 + 0);
    { uint32_t ea_ = (R(31) + 268); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (0 + 1);
    ctx->ctr = R(12);
    GM_CALLV(0x8014C4A8u, ctx->ctr, 0);
    goto L_8014C4E0;
L_8014C4AC:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014C4B8u, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C4E0; }
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 1);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27588);
    ctx->ctr = R(12);
    GM_CALLV(0x8014C4E0u, ctx->ctr, 0);
L_8014C4E0:;
    R(0) = lr;
}

/* fn_8014C500 (fn_8014C500, 108 bytes) */
static void pf_m_4c500(GM_CTX) {
    GM_FN(0x8014C500); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(3) + 268); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 272); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014C538; }
    GM_CALLV(0x8014C530u, 0x80048A60u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C558; }
L_8014C538:;
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27588);
    ctx->ctr = R(12);
    GM_CALLV(0x8014C558u, ctx->ctr, 0);
L_8014C558:;
    R(0) = lr;
}

/* fn_8014C570 (fn_8014C570, 288 bytes) */
static void pf_m_4c570(GM_CTX) {
    GM_FN(0x8014C570); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C5B4; }
    R(12) = ld32(base, (R(3) + 96));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 27336);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C5ACu, ctx->ctr, 0);
    R(3) = (0 + 1);
    goto L_8014C67C;
L_8014C5B4:;
    R(0) = ld32(base, (R(3) + 4312));
    R(0) = R(0) & 0x100u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014C5C8; }
    R(3) = (0 + 1);
    goto L_8014C67C;
L_8014C5C8:;
    GM_CALLV(0x8014C5CCu, 0x8004B290u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C5DC; }
    R(3) = (0 + 1);
    goto L_8014C67C;
L_8014C5DC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014C5E4u, 0x80057AD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C5F4; }
    R(3) = (0 + 1);
    goto L_8014C67C;
L_8014C5F4:;
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8014C654; }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(31) + 236); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8014C610u, 0x800578D0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C620; }
    R(3) = (0 + 1);
    goto L_8014C67C;
L_8014C620:;
    R(0) = ld32(base, (R(31) + 4404));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C654; }
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27716);
    ctx->ctr = R(12);
    GM_CALLV(0x8014C64Cu, ctx->ctr, 0);
    R(3) = (0 + 1);
    goto L_8014C67C;
L_8014C654:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 912));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C668u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C678; }
    R(3) = (0 + 1);
    goto L_8014C67C;
L_8014C678:;
    R(3) = (0 + 0);
L_8014C67C:;
    R(0) = lr;
}

/* fn_8014C690 (fn_8014C690, 148 bytes) */
static void pf_m_4c690(GM_CTX) {
    GM_FN(0x8014C690); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(31) = ld32(base, (R(3) + 5280));
    GM_CALLV(0x8014C6B0u, 0x80047800u, 0);
    { uint32_t ea_ = (R(30) + 268); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { goto L_8014C6DC; }
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 904));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C6D8u, ctx->ctr, 0);
    goto L_8014C6F4;
L_8014C6DC:;
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 896));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C6F4u, ctx->ctr, 0);
L_8014C6F4:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 160);
    GM_CALLV(0x8014C700u, 0x80056C70u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 178);
    GM_CALLV(0x8014C70Cu, 0x80056C70u, 0);
    R(0) = lr;
}

/* fn_8014C730 (fn_8014C730, 76 bytes) */
static void pf_m_4c730(GM_CTX) {
    GM_FN(0x8014C730); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014C748u, 0x800477A0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 160);
    GM_CALLV(0x8014C754u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 178);
    GM_CALLV(0x8014C760u, 0x80056CB0u, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 1156), R(0));
    R(0) = lr;
}

/* fn_8014C780 (fn_8014C780, 284 bytes) */
static void pf_m_4c780(GM_CTX) {
    GM_FN(0x8014C780); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014C798u, 0x800477B0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014C7A0u, 0x8004C480u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 1100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C7B4u, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014C7BCu, 0x8004B730u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014C7C4u, 0x8004C450u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 1096));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C7D8u, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 884));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C7ECu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C888; }
    R(3) = (R(31) + 3748);
    R(4) = (0 + 0);
    GM_CALLV(0x8014C800u, 0x8005E7A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C844; }
    R(3) = ld8(base, (R(31) + 840));
    R(0) = ld8(base, (R(31) + 4148));
    cr_cmp_u(ctx, 0, R(3), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014C844; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014C820u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C834; }
    R(4) = (0 + 6);
    R(3) = (R(3) + 3748);
    GM_CALLV(0x8014C834u, 0x8005E3B0u, 0);
L_8014C834:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014C83Cu, 0x80048A60u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C888; }
L_8014C844:;
    R(0) = ld32(base, (R(31) + 5284));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014C85C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8014C874; }
    goto L_8014C888;
L_8014C85C:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 900));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C870u, ctx->ctr, 0);
    goto L_8014C888;
L_8014C874:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 908));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C888u, ctx->ctr, 0);
L_8014C888:;
    R(0) = lr;
}

/* fn_8014C8A0 (fn_8014C8A0, 24 bytes) */
static void pf_m_4c8a0(GM_CTX) {
    R(0) = (0 + 0);
    st32(base, (R(3) + 5284), R(0));
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 888));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8014C8C0 (fn_8014C8C0, 56 bytes) */
static void pf_m_4c8c0(GM_CTX) {
    { uint32_t ea_ = (R(3) + 268); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { goto L_8014C8E4; }
    R(12) = ld32(base, (R(3) + 96));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 904));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
L_8014C8E4:;
    R(12) = ld32(base, (R(3) + 96));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 888));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8014C900 (fn_8014C900, 24 bytes) */
static void pf_m_4c900(GM_CTX) {
    R(0) = (0 + 1);
    st32(base, (R(3) + 5284), R(0));
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 892));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8014C920 (fn_8014C920, 4 bytes) */
static void pf_m_4c920(GM_CTX) {
    GM_TAIL(0x80047630u, 0); return;
}

/* fn_8014C930 (fn_8014C930, 764 bytes) */
static void pf_m_4c930(GM_CTX) {
    GM_FN(0x8014C930); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(31) = R(3) |R(3);
    R(29) = R(4) |R(4);
    { uint32_t ea_ = (R(3) + 268); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = ld32(base, (R(3) + 4308));
    ctx->f[1].u = ctx->f[0].u & ~0x8000000000000000ull;
    R(0) = R(5) & 0x40000000u;
    CR0(ctx, R(0));
    ctx->f[31].d = frsp(ctx->f[1].d);
    if ((CR_BIT(ctx, 2))) { goto L_8014C98C; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[30].d);
    if ((CR_BIT(ctx, 1))) { goto L_8014C9A4; }
L_8014C98C:;
    R(0) = R(5) & 0x80000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014CA00; }
    { uint32_t ea_ = (R(3) + 268); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014CA00; }
L_8014C9A4:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8014C9B0; }
    { uint32_t ea_ = (R(2) + -22044); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
L_8014C9B0:;
    { uint32_t ea_ = (R(2) + -22040); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22068); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014C9C8; }
    goto L_8014C9DC;
L_8014C9C8:;
    { uint32_t ea_ = (R(2) + -22044); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8014C9D8; }
    goto L_8014C9DC;
L_8014C9D8:;
    ctx->f[1].u = ctx->f[0].u;
L_8014C9DC:;
    R(3) = ld32(base, (R(3) + 5336));
    ctx->f[2].u = ctx->f[30].u;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(4) = (0 + 2);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014C9FCu, ctx->ctr, 0);
    goto L_8014CBF8;
L_8014CA00:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014CA08u, 0x80057650u, 0);
    { uint32_t ea_ = (R(3) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8014CA3C; }
    { uint32_t ea_ = (R(2) + -22040); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(30) = (0 + 2);
    { uint32_t ea_ = (R(2) + -22068); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014CA34; }
    goto L_8014CA94;
L_8014CA34:;
    ctx->f[29].u = ctx->f[0].u;
    goto L_8014CA94;
L_8014CA3C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014CA44u, 0x80057650u, 0);
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014CA74; }
    { uint32_t ea_ = (R(2) + -22036); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(30) = (0 + 3);
    { uint32_t ea_ = (R(2) + -22104); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014CA6C; }
    goto L_8014CA94;
L_8014CA6C:;
    ctx->f[29].u = ctx->f[0].u;
    goto L_8014CA94;
L_8014CA74:;
    { uint32_t ea_ = (R(2) + -22036); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(30) = (0 + 4);
    { uint32_t ea_ = (R(2) + -22104); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014CA90; }
    goto L_8014CA94;
L_8014CA90:;
    ctx->f[29].u = ctx->f[0].u;
L_8014CA94:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014CA9Cu, 0x8004B1A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014CB04; }
    R(4) = ld8(base, (R(31) + 840));
    R(3) = (R(31) + 492);
    GM_CALLV(0x8014CAB0u, 0x80070820u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8014CB04; }
    R(0) = ld8(base, (R(31) + 840));
    R(3) = (0 + 0x80430000u);
    R(3) = (R(3) + -18368);
    { uint32_t ea_ = (R(31) + 268); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8014CB04; }
    { uint32_t ea_ = (R(2) + -22068); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22032); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[29].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8014CAFC; }
    goto L_8014CB00;
L_8014CAFC:;
    ctx->f[1].u = ctx->f[0].u;
L_8014CB00:;
    ctx->f[29].u = ctx->f[1].u;
L_8014CB04:;
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x800000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014CB7C; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014CB18u, 0x80057650u, 0);
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014CB44; }
    { uint32_t ea_ = (R(2) + -22028); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22032); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[29].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8014CB3C; }
    goto L_8014CB40;
L_8014CB3C:;
    ctx->f[1].u = ctx->f[0].u;
L_8014CB40:;
    ctx->f[29].u = ctx->f[1].u;
L_8014CB44:;
    R(3) = (R(31) + 3748);
    R(4) = (0 + 0);
    GM_CALLV(0x8014CB50u, 0x8005E7A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014CB7C; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014CB60u, 0x80047920u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 888));
    ctx->ctr = R(12);
    GM_CALLV(0x8014CB78u, ctx->ctr, 0);
    goto L_8014CBF8;
L_8014CB7C:;
    R(0) = (0 + 0);
    st32(base, (R(31) + 1156), R(0));
    R(3) = R(31) |R(31);
    R(4) = (0 + 98);
    GM_CALLV(0x8014CB90u, 0x80056C70u, 0);
    R(3) = ld32(base, (R(31) + 4308));
    R(0) = R(3) & 0x18000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014CBB8; }
    R(0) = R(3) & 0x10000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014CBB0; }
    { uint32_t ea_ = (R(2) + -22104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d * ctx->f[0].d);
    goto L_8014CBB8;
L_8014CBB0:;
    { uint32_t ea_ = (R(2) + -22024); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d * ctx->f[0].d);
L_8014CBB8:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8014CBD4; }
    R(0) = ((int32_t)R(30) * 12);
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 3488);
    R(3) = R(3) + R(0);
    { uint32_t ea_ = (R(3) + 48); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
L_8014CBD4:;
    R(3) = ld32(base, (R(31) + 5336));
    ctx->f[1].u = ctx->f[29].u;
    ctx->f[2].u = ctx->f[30].u;
    R(4) = R(30) |R(30);
    R(12) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014CBF8u, ctx->ctr, 0);
L_8014CBF8:;
    R(0) = lr;
}

/* fn_8014CC30 (fn_8014CC30, 320 bytes) */
static void pf_m_4cc30(GM_CTX) {
    GM_FN(0x8014CC30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(5) = ld32(base, (R(3) + 5336));
    R(0) = ld32(base, (R(5) + 352));
    R(0) = R(0) & 0x20u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014CCE4; }
    R(31) = ld32(base, (R(5) + 344));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(31), -1);
    if ((CR_BIT(ctx, 2))) { goto L_8014CCE4; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8014CCA8; }
    R(0) = R(31) & 0xFFu;
    R(3) = (0 + 0x80370000u);
    R(0) = ((int32_t)R(0) * 12);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(3) + 3488);
    R(3) = R(3) + R(0);
    { uint32_t ea_ = (R(3) + 48); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014CCA8; }
    ctx->f[30].u = ctx->f[0].u;
L_8014CCA8:;
    R(3) = (R(5) + 96);
    GM_CALLV(0x8014CCB0u, 0x80168080u, 0);
    R(3) = ld32(base, (R(30) + 5336));
    ctx->f[31].u = ctx->f[1].u;
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014CCC0u, 0x801680C0u, 0);
    R(3) = ld32(base, (R(30) + 5336));
    ctx->f[2].u = ctx->f[30].u;
    ctx->f[3].u = ctx->f[31].u;
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014CCE0u, ctx->ctr, 0);
    goto L_8014CD48;
L_8014CCE4:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8014CD1C; }
    R(3) = ld32(base, (R(3) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22060); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0);
    { uint32_t ea_ = (R(5) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014CD18u, ctx->ctr, 0);
    goto L_8014CD48;
L_8014CD1C:;
    R(3) = ld32(base, (R(3) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0);
    { uint32_t ea_ = (R(5) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 48); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014CD48u, ctx->ctr, 0);
L_8014CD48:;
    R(0) = lr;
}

/* fn_8014CD70 (fn_8014CD70, 84 bytes) */
static void pf_m_4cd70(GM_CTX) {
    GM_FN(0x8014CD70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 4308));
    R(0) = R(0) & 0xFFFFFFFEu;
    st32(base, (R(3) + 4308), R(0));
    GM_CALLV(0x8014CD94u, 0x80057860u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014CD9Cu, 0x8004C480u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 1100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014CDB0u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_8014CDD0 (fn_8014CDD0, 216 bytes) */
static void pf_m_4cdd0(GM_CTX) {
    GM_FN(0x8014CDD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(3) + 268); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[31].d = frsp(ctx->f[0].d);
    GM_CALLV(0x8014CE08u, 0x80057650u, 0);
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8014CE28; }
    { uint32_t ea_ = (R(2) + -22020); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8014CE30; }
L_8014CE28:;
    { uint32_t ea_ = (R(2) + -22064); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    goto L_8014CE54;
L_8014CE30:;
    { uint32_t ea_ = (R(2) + -22036); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8014CE44; }
    { uint32_t ea_ = (R(2) + -22016); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    goto L_8014CE54;
L_8014CE44:;
    { uint32_t ea_ = (R(2) + -22024); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8014CE54; }
    { uint32_t ea_ = (R(2) + -22012); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
L_8014CE54:;
    R(3) = ld32(base, (R(31) + 4308));
    R(0) = R(3) & 0x18000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014CE78; }
    R(0) = R(3) & 0x10000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014CE70; }
    { uint32_t ea_ = (R(2) + -30768); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_8014CE80;
L_8014CE70:;
    { uint32_t ea_ = (R(2) + -30772); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_8014CE80;
L_8014CE78:;
    { uint32_t ea_ = (R(2) + -30776); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[30].d);
L_8014CE80:;
    { uint32_t ea_ = (R(31) + 236); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_8014CEB0 (fn_8014CEB0, 284 bytes) */
static void pf_m_4ceb0(GM_CTX) {
    GM_FN(0x8014CEB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 12);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014CECCu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014CF04; }
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 117);
    { uint32_t ea_ = (R(5) + 1448); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 1452); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014CF00u, ctx->ctr, 0);
    goto L_8014CFB8;
L_8014CF04:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 13);
    GM_CALLV(0x8014CF10u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014CF48; }
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 67);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 848); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014CF44u, ctx->ctr, 0);
    goto L_8014CFB8;
L_8014CF48:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 15);
    GM_CALLV(0x8014CF54u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014CF8C; }
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 118);
    { uint32_t ea_ = (R(5) + 1460); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 1464); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014CF88u, ctx->ctr, 0);
    goto L_8014CFB8;
L_8014CF8C:;
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 5);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 104); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014CFB8u, ctx->ctr, 0);
L_8014CFB8:;
    R(0) = lr;
}

/* fn_8014CFD0 (fn_8014CFD0, 148 bytes) */
static void pf_m_4cfd0(GM_CTX) {
    GM_FN(0x8014CFD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 348);
    R(5) = (0 + 0);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014CFF0u, 0x80057F60u, 0);
    R(3) = ld32(base, (R(31) + 5336));
    R(4) = (f + 16);
    R(5) = (0 + 15);
    GM_CALLV(0x8014D000u, 0x800D5790u, 0);
    R(0) = (0 + 0);
    st16(base, (f + 8), R(0));
    st16(base, (f + 10), R(0));
    st16(base, (f + 12), R(0));
    R(0) = ld8(base, (R(31) + 840));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8014D024; }
    R(0) = (0 + -32768);
    st16(base, (f + 10), R(0));
L_8014D024:;
    R(12) = ld32(base, (R(31) + 5780));
    R(4) = (0 + 0x80320000u);
    R(3) = (R(31) + 5780);
    R(6) = (f + 16);
    R(12) = ld32(base, (R(12) + 160));
    R(4) = (R(4) + 26408);
    R(7) = (f + 8);
    R(5) = (0 + 0);
    R(8) = (0 + 0);
    ctx->ctr = R(12);
    GM_CALLV(0x8014D050u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_8014D070 (fn_8014D070, 596 bytes) */
static void pf_m_4d070(GM_CTX) {
    GM_FN(0x8014D070); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014D088u, 0x8004C480u, 0);
    R(0) = ld8(base, (R(31) + 5420));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D0A8; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8014D14C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8014D1AC; }
    goto L_8014D2B0;
L_8014D0A8:;
    R(0) = ld8(base, (R(31) + 5421));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014D0C0; }
    R(0) = (0 + 4);
    st8(base, (R(31) + 5420), R(0));
    goto L_8014D2B0;
L_8014D0C0:;
    { uint32_t ea_ = (R(31) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014D2B0; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 15);
    GM_CALLV(0x8014D0DCu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D114; }
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 119);
    { uint32_t ea_ = (R(5) + 1472); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 1476); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014D110u, ctx->ctr, 0);
    goto L_8014D140;
L_8014D114:;
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22060); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 6);
    { uint32_t ea_ = (R(5) + 116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014D140u, ctx->ctr, 0);
L_8014D140:;
    R(0) = (0 + 1);
    st8(base, (R(31) + 5420), R(0));
    goto L_8014D2B0;
L_8014D14C:;
    { uint32_t ea_ = (R(31) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22008); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014D2B0; }
    R(3) = (R(31) + 3748);
    GM_CALLV(0x8014D164u, 0x8005E770u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D2B0; }
    R(3) = (0 + 0);
    R(0) = (0 + 2);
    st8(base, (R(31) + 5421), R(3));
    R(5) = (0 + 0x80370000u);
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (R(5) + 3488);
    st8(base, (R(31) + 5420), R(0));
    R(4) = (0 + 114);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(5) + 1412); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 1416); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014D1A8u, ctx->ctr, 0);
    goto L_8014D2B0;
L_8014D1AC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D1B4u, 0x8014CFD0u, 0);
    { uint32_t ea_ = (R(31) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014D1C8; }
    ctx->f[1].u = ctx->f[0].u;
L_8014D1C8:;
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -22104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[0].d);
    R(12) = ld32(base, (R(12) + 60));
    ctx->ctr = R(12);
    GM_CALLV(0x8014D1E4u, ctx->ctr, 0);
    { uint32_t ea_ = (R(31) + 272); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22036); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8014D220; }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8014D210; }
    { uint32_t ea_ = (R(31) + 272); stfs(base, ea_, ctx->f[2].d); }
    goto L_8014D218;
L_8014D210:;
    ctx->f[0].u = ctx->f[2].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(31) + 272); stfs(base, ea_, ctx->f[0].d); }
L_8014D218:;
    { uint32_t ea_ = (R(2) + -22004); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 284); stfs(base, ea_, ctx->f[0].d); }
L_8014D220:;
    { uint32_t ea_ = (R(31) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22000); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8014D23C; }
    { uint32_t ea_ = (R(2) + -21996); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 276); stfs(base, ea_, ctx->f[0].d); }
    goto L_8014D244;
L_8014D23C:;
    { uint32_t ea_ = (R(2) + -21992); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 276); stfs(base, ea_, ctx->f[0].d); }
L_8014D244:;
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x2u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014D25C; }
    R(0) = (0 + 4);
    st8(base, (R(31) + 5420), R(0));
    goto L_8014D2B0;
L_8014D25C:;
    R(3) = (R(31) + 3748);
    GM_CALLV(0x8014D264u, 0x8005E770u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D27C; }
    { uint32_t ea_ = (R(31) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -21988); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8014D2B0; }
L_8014D27C:;
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22060); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 6);
    { uint32_t ea_ = (R(5) + 116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014D2A8u, ctx->ctr, 0);
    R(0) = (0 + 4);
    st8(base, (R(31) + 5420), R(0));
L_8014D2B0:;
    R(0) = lr;
}

/* fn_8014D2D0 (fn_8014D2D0, 460 bytes) */
static void pf_m_4d2d0(GM_CTX) {
    GM_FN(0x8014D2D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 1096));
    ctx->ctr = R(12);
    GM_CALLV(0x8014D2F4u, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D2FCu, 0x8014E4E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014D488; }
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x60u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014D31C; }
    R(3) = (R(31) + 3748);
    R(4) = (0 + 1);
    GM_CALLV(0x8014D31Cu, 0x8005E460u, 0);
L_8014D31C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D324u, 0x8014D070u, 0);
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014D488; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 1);
    GM_CALLV(0x8014D33Cu, 0x8004CE00u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 15);
    GM_CALLV(0x8014D348u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D374; }
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 2);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27844);
    ctx->ctr = R(12);
    GM_CALLV(0x8014D370u, ctx->ctr, 0);
    goto L_8014D488;
L_8014D374:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 884));
    ctx->ctr = R(12);
    GM_CALLV(0x8014D388u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014D488; }
    R(0) = (0 + 0);
    st16(base, (R(31) + 256), R(0));
    R(3) = R(31) |R(31);
    R(4) = (0 + 10);
    GM_CALLV(0x8014D3A4u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D3DC; }
    R(0) = ld32(base, (R(31) + 4312));
    R(0) = R(0) & 0x20u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014D3DC; }
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 1);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27780);
    ctx->ctr = R(12);
    GM_CALLV(0x8014D3D8u, ctx->ctr, 0);
    goto L_8014D488;
L_8014D3DC:;
    { uint32_t ea_ = (R(31) + 268); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { goto L_8014D3F8; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D3F4u, 0x8014C500u, 0);
    goto L_8014D488;
L_8014D3F8:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 13);
    GM_CALLV(0x8014D404u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D43C; }
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 69);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 872); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x8014D438u, ctx->ctr, 0);
    goto L_8014D468;
L_8014D43C:;
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 7);
    { uint32_t ea_ = (R(5) + 128); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 132); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014D468u, ctx->ctr, 0);
L_8014D468:;
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27780);
    ctx->ctr = R(12);
    GM_CALLV(0x8014D488u, ctx->ctr, 0);
L_8014D488:;
    R(0) = lr;
}

/* fn_8014D4A0 (fn_8014D4A0, 292 bytes) */
static void pf_m_4d4a0(GM_CTX) {
    GM_FN(0x8014D4A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    GM_CALLV(0x8014D4C0u, 0x800479A0u, 0);
    R(31) = (0 + 0);
    st8(base, (R(29) + 5420), R(31));
    R(3) = R(29) |R(29);
    R(4) = (0 + 178);
    GM_CALLV(0x8014D4D4u, 0x80056C70u, 0);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(29) |R(29);
    { uint32_t ea_ = (R(29) + 244); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld8(base, (R(29) + 840));
    st16(base, (R(29) + 256), R(31));
    R(12) = ld32(base, (R(29) + 96));
    R(12) = ld32(base, (R(12) + 1092));
    ctx->ctr = R(12);
    GM_CALLV(0x8014D4F8u, ctx->ctr, 0);
    st16(base, (R(29) + 258), R(3));
    R(3) = R(29) |R(29);
    R(4) = (0 + 1);
    GM_CALLV(0x8014D508u, 0x8004CD80u, 0);
    R(31) = ld32(base, (R(29) + 5280));
    R(30) = (0 + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D538; }
    R(30) = ld32(base, (R(31) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(30), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_8014D538; }
    R(3) = (R(29) + 3748);
    GM_CALLV(0x8014D52Cu, 0x8005E740u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014D538; }
    R(30) = (0 + 0);
L_8014D538:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8014D54C; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8014D560; }
    goto L_8014D570;
L_8014D54C:;
    R(3) = R(29) |R(29);
    R(4) = (0 + 245);
    R(5) = (0 + 0);
    GM_CALLV(0x8014D55Cu, 0x80057E70u, 0);
    goto L_8014D570;
L_8014D560:;
    R(3) = R(29) |R(29);
    R(4) = (0 + 241);
    R(5) = (0 + 0);
    GM_CALLV(0x8014D570u, 0x80057E70u, 0);
L_8014D570:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D590; }
    { uint32_t ea_ = (R(31) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { goto L_8014D590; }
    { uint32_t ea_ = (R(29) + 236); stfs(base, ea_, ctx->f[1].d); }
    goto L_8014D598;
L_8014D590:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014D598u, 0x8014CDD0u, 0);
L_8014D598:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014D5A0u, 0x8014CEB0u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014D5A8u, 0x8014CD70u, 0);
    R(0) = lr;
}

/* fn_8014D5D0 (fn_8014D5D0, 56 bytes) */
static void pf_m_4d5d0(GM_CTX) {
    GM_FN(0x8014D5D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014D5E8u, 0x80047A00u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 178);
    GM_CALLV(0x8014D5F4u, 0x80056CB0u, 0);
    R(0) = lr;
}

/* fn_8014D610 (fn_8014D610, 96 bytes) */
static void pf_m_4d610(GM_CTX) {
    GM_FN(0x8014D610); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014D628u, 0x80047AC0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D630u, 0x8004C480u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 1100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014D644u, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D64Cu, 0x8004B730u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D654u, 0x8004C450u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D65Cu, 0x8014D2D0u, 0);
    R(0) = lr;
}

/* fn_8014D6D0 (fn_8014D6D0, 80 bytes) */
static void pf_m_4d6d0(GM_CTX) {
    GM_FN(0x8014D6D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014D6E8u, 0x80047C40u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 178);
    GM_CALLV(0x8014D6F4u, 0x80056C70u, 0);
    R(0) = (0 + 0);
    st8(base, (R(31) + 5420), R(0));
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D704u, 0x8014CD70u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D70Cu, 0x8004B730u, 0);
    R(0) = lr;
}

/* fn_8014D720 (fn_8014D720, 56 bytes) */
static void pf_m_4d720(GM_CTX) {
    GM_FN(0x8014D720); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014D738u, 0x80047D10u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 178);
    GM_CALLV(0x8014D744u, 0x80056CB0u, 0);
    R(0) = lr;
}

/* fn_8014D760 (fn_8014D760, 104 bytes) */
static void pf_m_4d760(GM_CTX) {
    GM_FN(0x8014D760); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014D778u, 0x80047D60u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D780u, 0x8004C480u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 1100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014D794u, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D79Cu, 0x8004B730u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D7A4u, 0x8004C450u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D7ACu, 0x8014D2D0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D7B4u, 0x800578D0u, 0);
    R(0) = lr;
}

/* fn_8014D7D0 (fn_8014D7D0, 56 bytes) */
static void pf_m_4d7d0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 5284));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) return;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (0 + 10);
    { uint32_t ea_ = (R(3) + 268); stfs(base, ea_, ctx->f[2].d); }
    R(3) = ld32(base, (R(3) + 5336));
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(2) + -22068); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 92));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8014D810 (fn_8014D810, 4 bytes) */
static void pf_m_4d810(GM_CTX) {

}

/* fn_8014D820 (fn_8014D820, 280 bytes) */
static void pf_m_4d820(GM_CTX) {
    GM_FN(0x8014D820); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014D838u, 0x8004C480u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 1100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014D84Cu, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D854u, 0x8004B9A0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D85Cu, 0x8004C450u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 884));
    ctx->ctr = R(12);
    GM_CALLV(0x8014D870u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014D924; }
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x60u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014D890; }
    R(3) = (R(31) + 3748);
    R(4) = (0 + 1);
    GM_CALLV(0x8014D890u, 0x8005E460u, 0);
L_8014D890:;
    R(0) = ld32(base, (R(31) + 5284));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014D8D0; }
    R(3) = (R(31) + 3748);
    R(4) = (0 + 0);
    GM_CALLV(0x8014D8A8u, 0x8005E7A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014D8C4; }
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014D8BCu, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D924; }
L_8014D8C4:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D8CCu, 0x8014C500u, 0);
    goto L_8014D924;
L_8014D8D0:;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(31) + 3748);
    { uint32_t ea_ = (R(31) + 268); stfs(base, ea_, ctx->f[0].d); }
    R(4) = (0 + 0);
    GM_CALLV(0x8014D8E4u, 0x8005E7A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D908; }
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014D8F8u, 0x80168080u, 0);
    { uint32_t ea_ = (R(2) + -22060); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8014D91C; }
L_8014D908:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014D914u, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014D924; }
L_8014D91C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014D924u, 0x8014C500u, 0);
L_8014D924:;
    R(0) = lr;
}

/* fn_8014DBB0 (fn_8014DBB0, 168 bytes) */
static void pf_m_4dbb0(GM_CTX) {
    GM_FN(0x8014DBB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 81);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014DBCCu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014DC40; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 15);
    GM_CALLV(0x8014DBE0u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014DC40; }
    R(3) = (R(31) + 3748);
    GM_CALLV(0x8014DBF0u, 0x8005E830u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014DC40; }
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x18000000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8014DC40; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 190);
    GM_CALLV(0x8014DC10u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014DC40; }
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27844);
    ctx->ctr = R(12);
    GM_CALLV(0x8014DC38u, ctx->ctr, 0);
    R(3) = (0 + 1);
    goto L_8014DC44;
L_8014DC40:;
    R(3) = (0 + 0);
L_8014DC44:;
    R(0) = lr;
}

/* fn_8014E4E0 (fn_8014E4E0, 140 bytes) */
static void pf_m_4e4e0(GM_CTX) {
    GM_FN(0x8014E4E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 167);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014E4FCu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014E554; }
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8014E554; }
    R(0) = ld32(base, (R(31) + 4312));
    R(0) = R(0) & 0x40u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8014E554; }
    R(3) = (R(31) + 3748);
    GM_CALLV(0x8014E524u, 0x8005E300u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014E554; }
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 28100);
    ctx->ctr = R(12);
    GM_CALLV(0x8014E54Cu, ctx->ctr, 0);
    R(3) = (0 + 1);
    goto L_8014E558;
L_8014E554:;
    R(3) = (0 + 0);
L_8014E558:;
    R(0) = lr;
}

/* fn_8014E6B0 (fn_8014E6B0, 80 bytes) */
static void pf_m_4e6b0(GM_CTX) {
    GM_FN(0x8014E6B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014E6C8u, 0x8004A830u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 178);
    GM_CALLV(0x8014E6D4u, 0x80056C70u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014E6DCu, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014E6EC; }
    R(4) = (0 + 6);
    GM_CALLV(0x8014E6ECu, 0x80147250u, 0);
L_8014E6EC:;
    R(0) = lr;
}

/* fn_8014E700 (fn_8014E700, 80 bytes) */
static void pf_m_4e700(GM_CTX) {
    GM_FN(0x8014E700); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014E718u, 0x8004A8C0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 178);
    GM_CALLV(0x8014E724u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014E72Cu, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014E73C; }
    R(4) = (0 + 0);
    GM_CALLV(0x8014E73Cu, 0x80147250u, 0);
L_8014E73C:;
    R(0) = lr;
}

/* fn_8014E750 (fn_8014E750, 16 bytes) */
static void pf_m_4e750(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 3488);
    { uint32_t ea_ = (R(3) + 2368); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_8014E760 (fn_8014E760, 68 bytes) */
static void pf_m_4e760(GM_CTX) {
    GM_FN(0x8014E760); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0);
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 888));
    ctx->ctr = R(12);
    GM_CALLV(0x8014E788u, ctx->ctr, 0);
    R(0) = (0 + 1);
    st32(base, (R(31) + 5284), R(0));
    R(0) = lr;
}

/* fn_8014E820 (fn_8014E820, 240 bytes) */
static void pf_m_4e820(GM_CTX) {
    GM_FN(0x8014E820); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014E838u, 0x8004A920u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014E8FC; }
    R(0) = ld32(base, (R(31) + 5284));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014E868; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8014E884; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8014E8A0; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((CR_BIT(ctx, 2))) { goto L_8014E8E0; }
    goto L_8014E8FC;
L_8014E868:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014E874u, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014E884; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014E884u, 0x8014E760u, 0);
L_8014E884:;
    R(3) = (R(31) + 3748);
    GM_CALLV(0x8014E88Cu, 0x8005E830u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014E8FC; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014E89Cu, 0x8014E7B0u, 0);
    goto L_8014E8FC;
L_8014E8A0:;
    R(3) = (R(31) + 3748);
    GM_CALLV(0x8014E8A8u, 0x8005E830u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014E8FC; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 81);
    GM_CALLV(0x8014E8BCu, 0x80056CB0u, 0);
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -22000); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 140));
    ctx->ctr = R(12);
    GM_CALLV(0x8014E8D4u, ctx->ctr, 0);
    R(0) = (0 + 3);
    st32(base, (R(31) + 5284), R(0));
    goto L_8014E8FC;
L_8014E8E0:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 40);
    GM_CALLV(0x8014E8ECu, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014E8FC; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014E8FCu, 0x8014E760u, 0);
L_8014E8FC:;
    R(0) = lr;
}

/* getPlayerRideOn__9daYoshi_cCFv (getPlayerRideOn__9daYoshi_cCFv, 24 bytes) */
static void pf_getPlayerRideOn__9daYoshi_cCFv_4e9b0(GM_CTX) {
    R(3) = ld32(base, (R(3) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014E9C0; }
    GM_TAIL(0x80162D00u, 0); return;
L_8014E9C0:;
    R(3) = (0 + 0);
}

/* checkRideOffAble__9daYoshi_cFv (checkRideOffAble__9daYoshi_cFv, 96 bytes) */
static void pf_checkRideOffAble__9daYoshi_cFv_4e9d0(GM_CTX) {
    GM_FN(0x8014E9D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 145);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014E9ECu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014EA10; }
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x10000000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8014EA10; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014EA08u, 0x80150650u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014EA18; }
L_8014EA10:;
    R(3) = (0 + 0);
    goto L_8014EA1C;
L_8014EA18:;
    R(3) = (0 + 1);
L_8014EA1C:;
    R(0) = lr;
}

/* setRideOffPlayer__9daYoshi_cFv (setRideOffPlayer__9daYoshi_cFv, 188 bytes) */
static void pf_setRideOffPlayer__9daYoshi_cFv_4eb80(GM_CTX) {
    GM_FN(0x8014EB80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + 0);
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 5336));
    st32(base, (R(4) + 36), R(0));
    GM_CALLV(0x8014EBA4u, 0x8004DD00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014EC00; }
    R(3) = ld32(base, (R(31) + 5408));
    GM_CALLV(0x8014EBB4u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014EBE0; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x8014EBC8u, 0x8014EFB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014EBE0; }
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 28424);
    GM_CALLV(0x8014EBE0u, 0x8014ED00u, 0);
L_8014EBE0:;
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27336);
    ctx->ctr = R(12);
    GM_CALLV(0x8014EC00u, ctx->ctr, 0);
L_8014EC00:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 255);
    GM_CALLV(0x8014EC0Cu, 0x8014EC40u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014EC14u, 0x80060FE0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 76);
    GM_CALLV(0x8014EC20u, 0x80056CB0u, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 5412), R(0));
    R(0) = lr;
}

/* fn_8014EC40 (fn_8014EC40, 160 bytes) */
static void pf_m_4ec40(GM_CTX) {
    GM_FN(0x8014EC40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(5) = ld32(base, (R(3) + 5336));
    st8(base, (R(3) + 909), R(4));
    st8(base, (R(5) + 336), R(4));
    R(4) = ld8(base, (R(3) + 909));
    R(0) = (int8_t)R(4);
    cr_cmp_s(ctx, 0, (int32_t)R(0), -1);
    if ((CR_BIT(ctx, 2))) { goto L_8014EC94; }
    st32(base, (R(3) + 3748), R(0));
    st8(base, (R(3) + 644), R(4));
    R(3) = R(4) |R(4);
    R(3) = (int8_t)R(3);
    GM_CALLV(0x8014EC84u, 0x80069530u, 0);
    R(0) = (0 + 2);
    st32(base, (R(31) + 3652), R(3));
    st8(base, (R(31) + 910), R(0));
    goto L_8014ECCC;
L_8014EC94:;
    R(4) = (0 + -1);
    R(0) = (0 + 0);
    st32(base, (R(3) + 3748), R(4));
    st8(base, (R(3) + 644), R(0));
    R(3) = (0 + 0);
    GM_CALLV(0x8014ECACu, 0x80069530u, 0);
    st32(base, (R(31) + 3652), R(3));
    R(3) = R(31) |R(31);
    R(4) = (0 + 101);
    GM_CALLV(0x8014ECBCu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014ECCC; }
    R(0) = (0 + 4);
    st8(base, (R(31) + 910), R(0));
L_8014ECCC:;
    R(0) = lr;
}

/* fn_8014ECE0 (fn_8014ECE0, 16 bytes) */
static void pf_m_4ece0(GM_CTX) {
    { uint32_t ea_ = R(3) + 5344; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8014ECF0 (fn_8014ECF0, 16 bytes) */
static void pf_m_4ecf0(GM_CTX) {
    { uint32_t ea_ = R(3) + 24; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8014ED00 (fn_8014ED00, 24 bytes) */
static void pf_m_4ed00(GM_CTX) {
    R(0) = (0 + 0);
    st32(base, (R(3) + 5404), R(0));
    { uint32_t ea_ = R(3) + 5344; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8014ED20 (fn_8014ED20, 16 bytes) */
static void pf_m_4ed20(GM_CTX) {
    { uint32_t ea_ = R(3) + 24; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8014ED30 (fn_8014ED30, 8 bytes) */
static void pf_m_4ed30(GM_CTX) {
    R(4) = (0 + 177);
    GM_TAIL(0x80056C70u, 0); return;
}

/* fn_8014ED40 (fn_8014ED40, 8 bytes) */
static void pf_m_4ed40(GM_CTX) {
    R(4) = (0 + 177);
    GM_TAIL(0x80056CB0u, 0); return;
}

/* fn_8014ED50 (fn_8014ED50, 64 bytes) */
static void pf_m_4ed50(GM_CTX) {
    GM_FN(0x8014ED50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 178);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014ED6Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014ED7C; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014ED7Cu, 0x80151C20u, 0);
L_8014ED7C:;
    R(0) = lr;
}

/* fn_8014ED90 (fn_8014ED90, 128 bytes) */
static void pf_m_4ed90(GM_CTX) {
    GM_FN(0x8014ED90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x8014EDB4u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014EDC8; }
    R(0) = (0 + 0);
    st8(base, (R(3) + 876), R(0));
    st32(base, (R(3) + 872), R(0));
L_8014EDC8:;
    R(0) = ld32(base, (R(31) + 0));
    R(3) = R(30) |R(30);
    st32(base, (R(30) + 5408), R(0));
    R(4) = (0 + 0);
    GM_CALLV(0x8014EDDCu, 0x8014F630u, 0);
    R(0) = (0 + 1);
    st8(base, (R(31) + 876), R(0));
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    R(0) = ld32(base, (R(30) + 0));
    st32(base, (R(31) + 872), R(0));
    GM_CALLV(0x8014EDF8u, 0x801506A0u, 0);
    R(0) = lr;
}

/* fn_8014EE10 (fn_8014EE10, 212 bytes) */
static void pf_m_4ee10(GM_CTX) {
    GM_FN(0x8014EE10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = (R(3) + 3748);
    GM_CALLV(0x8014EE2Cu, 0x8005E630u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014EECC; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 177);
    GM_CALLV(0x8014EE40u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014EE5C; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 174);
    GM_CALLV(0x8014EE54u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014EE64; }
L_8014EE5C:;
    R(3) = (0 + 0);
    goto L_8014EED0;
L_8014EE64:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014EE6Cu, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014EE80; }
    R(4) = (0 + 6);
    R(3) = (R(3) + 3748);
    GM_CALLV(0x8014EE80u, 0x8005E3B0u, 0);
L_8014EE80:;
    R(3) = ld32(base, (R(31) + 5408));
    GM_CALLV(0x8014EE88u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014EEB4; }
    R(0) = ld32(base, (R(31) + 5432));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014EECC; }
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 28360);
    GM_CALLV(0x8014EEACu, 0x8014ED00u, 0);
    R(3) = (0 + 1);
    goto L_8014EED0;
L_8014EEB4:;
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 28424);
    GM_CALLV(0x8014EEC4u, 0x8014ED00u, 0);
    R(3) = (0 + 1);
    goto L_8014EED0;
L_8014EECC:;
    R(3) = (0 + 0);
L_8014EED0:;
    R(0) = lr;
}

/* fn_8014EFA0 (fn_8014EFA0, 16 bytes) */
static void pf_m_4efa0(GM_CTX) {
    { uint32_t ea_ = R(3) + 24; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8014EFB0 (fn_8014EFB0, 264 bytes) */
static void pf_m_4efb0(GM_CTX) {
    GM_FN(0x8014EFB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 5344));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    R(3) = (R(3) + 5344);
    GM_CALLV(0x8014EFE4u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 28424);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x8014EFFCu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F008; }
    R(30) = (0 + 1);
L_8014F008:;
    R(3) = ld32(base, (R(29) + 5408));
    GM_CALLV(0x8014F010u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8014F098; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F058; }
    R(0) = ld8(base, (R(3) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8014F038; }
    R(3) = (0 + 0);
    goto L_8014F09C;
L_8014F038:;
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 224));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F048u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F06C; }
    R(3) = (0 + 0);
    goto L_8014F09C;
L_8014F058:;
    R(0) = ld8(base, (R(3) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F06C; }
    R(0) = (0 + 10);
    st32(base, (R(3) + 1084), R(0));
L_8014F06C:;
    R(0) = (0 + 3);
    st8(base, (R(31) + 876), R(0));
    R(3) = R(29) |R(29);
    R(4) = R(31) |R(31);
    GM_CALLV(0x8014F080u, 0x801507C0u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014F088u, 0x80150020u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8014F090u, 0x80150150u, 0);
    R(3) = (0 + 1);
    goto L_8014F09C;
L_8014F098:;
    R(3) = (0 + 0);
L_8014F09C:;
    R(0) = lr;
}

/* fn_8014F0C0 (fn_8014F0C0, 160 bytes) */
static void pf_m_4f0c0(GM_CTX) {
    GM_FN(0x8014F0C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 176);
    R(30) = R(3) |R(3);
    R(0) = ld8(base, (R(3) + 909));
    st8(base, (R(3) + 5441), R(0));
    GM_CALLV(0x8014F0E8u, 0x80056C70u, 0);
    R(0) = ld8(base, (R(30) + 840));
    st8(base, (R(30) + 5440), R(0));
    R(3) = (int16_t)ld16(base, (R(30) + 258));
    GM_CALLV(0x8014F0F8u, 0x802DE514u, 0);
    R(12) = ld32(base, (R(30) + 96));
    R(31) = R(3) |R(3);
    R(3) = R(30) |R(30);
    R(4) = ld8(base, (R(30) + 5440));
    R(12) = ld32(base, (R(12) + 1092));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F114u, ctx->ctr, 0);
    R(3) = (int16_t)R(3);
    GM_CALLV(0x8014F11Cu, 0x802DE514u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(31));
    if ((CR_BIT(ctx, 1))) { goto L_8014F130; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014F12Cu, 0x8014F470u, 0);
    goto L_8014F138;
L_8014F130:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014F138u, 0x8014F3D0u, 0);
L_8014F138:;
    R(3) = (0 + 10);
    R(0) = (0 + 0);
    st32(base, (R(30) + 5424), R(3));
    st32(base, (R(30) + 6076), R(0));
    R(0) = lr;
}

/* fn_8014F160 (fn_8014F160, 152 bytes) */
static void pf_m_4f160(GM_CTX) {
    GM_FN(0x8014F160); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + -1);
    R(30) = R(3) |R(3);
    st8(base, (R(3) + 5441), R(0));
    R(31) = ld32(base, (R(3) + 5336));
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x8014F18Cu, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(4) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8014F1B4; }
    R(0) = ld8(base, (R(3) + 876));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F1B4; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014F1ACu, 0x80150700u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014F1B4u, 0x80150150u, 0);
L_8014F1B4:;
    R(3) = ld32(base, (R(30) + 5408));
    GM_CALLV(0x8014F1BCu, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F1CC; }
    R(0) = (0 + 0);
    st32(base, (R(31) + 660), R(0));
L_8014F1CC:;
    R(0) = ld32(base, (R(30) + 5476));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    if ((CR_BIT(ctx, 0))) { goto L_8014F1E0; }
    R(0) = (0 + 4);
    st32(base, (R(30) + 5476), R(0));
L_8014F1E0:;
    R(0) = lr;
}

/* fn_8014F200 (fn_8014F200, 132 bytes) */
static void pf_m_4f200(GM_CTX) {
    GM_FN(0x8014F200); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 175);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014F21Cu, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 176);
    GM_CALLV(0x8014F228u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 179);
    GM_CALLV(0x8014F234u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 3);
    GM_CALLV(0x8014F240u, 0x80056CB0u, 0);
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = ld32(base, (R(3) + 380));
    R(0) = R(0) & 0xFFFFFFF7u;
    st32(base, (R(3) + 380), R(0));
    R(3) = ld32(base, (R(31) + 5336));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 104));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F268u, ctx->ctr, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014F270u, 0x8014F160u, 0);
    R(0) = lr;
}

/* fn_8014F290 (fn_8014F290, 308 bytes) */
static void pf_m_4f290(GM_CTX) {
    GM_FN(0x8014F290); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 5456));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8014F2BC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8014F334; }
    goto L_8014F3A0;
L_8014F2BC:;
    R(3) = ld32(base, (R(3) + 5336));
    { uint32_t ea_ = (R(2) + -21972); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014F2CCu, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F3A0; }
    R(3) = ld32(base, (R(31) + 5336));
    R(0) = (0 + 2);
    st32(base, (R(31) + 5456), R(0));
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014F2E8u, 0x801680C0u, 0);
    { uint32_t ea_ = (R(31) + 5460); stfs(base, ea_, ctx->f[1].d); }
    R(3) = ld32(base, (R(31) + 5336));
    GM_CALLV(0x8014F2F4u, 0x800D5BE0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F318; }
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 144));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F314u, ctx->ctr, 0);
    goto L_8014F3A0;
L_8014F318:;
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 140));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F330u, ctx->ctr, 0);
    goto L_8014F3A0;
L_8014F334:;
    R(4) = ld32(base, (R(3) + 5452));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F348; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 5452), R(0));
L_8014F348:;
    R(0) = ld32(base, (R(3) + 5452));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F3A0; }
    R(0) = (0 + 0);
    st32(base, (R(3) + 5456), R(0));
    R(3) = ld32(base, (R(3) + 5336));
    GM_CALLV(0x8014F364u, 0x800D5BE0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F388; }
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(31) + 5460); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 144));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F384u, ctx->ctr, 0);
    goto L_8014F3A0;
L_8014F388:;
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(31) + 5460); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 140));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F3A0u, ctx->ctr, 0);
L_8014F3A0:;
    R(3) = ld32(base, (R(31) + 5456));
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(3) = rotl32(R(0), 1) & 0x1u;
    R(0) = lr;
}

/* fn_8014F3D0 (fn_8014F3D0, 12 bytes) */
static void pf_m_4f3d0(GM_CTX) {
    R(0) = (0 + 0);
    st32(base, (R(3) + 5404), R(0));
}

/* fn_8014F3E0 (fn_8014F3E0, 136 bytes) */
static void pf_m_4f3e0(GM_CTX) {
    GM_FN(0x8014F3E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F414; }
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 28296);
    GM_CALLV(0x8014F410u, 0x8014ED00u, 0);
    goto L_8014F450;
L_8014F414:;
    R(3) = (int16_t)ld16(base, (R(3) + 258));
    GM_CALLV(0x8014F41Cu, 0x802DE514u, 0);
    R(12) = ld32(base, (R(30) + 96));
    R(31) = R(3) |R(3);
    R(3) = R(30) |R(30);
    R(4) = ld8(base, (R(30) + 5440));
    R(12) = ld32(base, (R(12) + 1092));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F438u, ctx->ctr, 0);
    R(3) = (int16_t)R(3);
    GM_CALLV(0x8014F440u, 0x802DE514u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(31));
    if ((CR_BIT(ctx, 1))) { goto L_8014F450; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014F450u, 0x8014F470u, 0);
L_8014F450:;
    R(0) = lr;
}

/* fn_8014F470 (fn_8014F470, 208 bytes) */
static void pf_m_4f470(GM_CTX) {
    GM_FN(0x8014F470); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 175);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014F48Cu, 0x80056C70u, 0);
    R(3) = ld32(base, (R(31) + 5336));
    R(0) = ld32(base, (R(3) + 380));
    R(0) = R(0) | 0x8u;
    st32(base, (R(3) + 380), R(0));
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8014F4D8; }
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 96);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 1196); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F4D4u, ctx->ctr, 0);
    goto L_8014F504;
L_8014F4D8:;
    R(3) = ld32(base, (R(31) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    R(4) = (0 + 96);
    R(12) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(5) + 2380); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 100));
    { uint32_t ea_ = (R(5) + 2376); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 2372); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014F504u, ctx->ctr, 0);
L_8014F504:;
    R(6) = ld32(base, (R(31) + 5336));
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(2) + -24616); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    st32(base, (R(6) + 660), R(0));
    R(4) = (0 + 346);
    R(5) = (0 + 0);
    { uint32_t ea_ = (R(6) + 664); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 5404), R(0));
    GM_CALLV(0x8014F52Cu, 0x80057E70u, 0);
    R(0) = lr;
}

/* fn_8014F540 (fn_8014F540, 72 bytes) */
static void pf_m_4f540(GM_CTX) {
    GM_FN(0x8014F540); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014F558u, 0x80151AC0u, 0);
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014F564u, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F574; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014F574u, 0x8014FC50u, 0);
L_8014F574:;
    R(0) = lr;
}

/* fn_8014F590 (fn_8014F590, 160 bytes) */
static void pf_m_4f590(GM_CTX) {
    GM_FN(0x8014F590); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 176);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8014F5ACu, 0x80056CB0u, 0);
    R(3) = ld32(base, (R(31) + 5408));
    GM_CALLV(0x8014F5B4u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(4) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8014F5D0; }
    R(0) = (0 + 2);
    st8(base, (R(3) + 876), R(0));
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014F5D0u, 0x80150760u, 0);
L_8014F5D0:;
    R(5) = ld32(base, (R(31) + 5336));
    R(0) = (0 + 2);
    R(3) = R(31) |R(31);
    R(4) = (0 + 175);
    st32(base, (R(5) + 660), R(0));
    GM_CALLV(0x8014F5E8u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014F5F0u, 0x80150650u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F61C; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 179);
    GM_CALLV(0x8014F604u, 0x80056C70u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 3);
    GM_CALLV(0x8014F610u, 0x80056C70u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 198);
    GM_CALLV(0x8014F61Cu, 0x80056C70u, 0);
L_8014F61C:;
    R(0) = lr;
}

/* fn_8014F630 (fn_8014F630, 528 bytes) */
static void pf_m_4f630(GM_CTX) {
    GM_FN(0x8014F630); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    st32(base, (R(3) + 5452), R(0));
    st32(base, (R(3) + 5456), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8014F68C; }
    R(3) = ld32(base, (R(3) + 5336));
    R(0) = ld32(base, (R(3) + 340));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 99);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F690; }
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014F684u, 0x80168080u, 0);
    ctx->f[31].u = ctx->f[1].u;
    goto L_8014F690;
L_8014F68C:;
    { uint32_t ea_ = (R(2) + -21968); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
L_8014F690:;
    R(3) = ld32(base, (R(30) + 5408));
    GM_CALLV(0x8014F698u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F810; }
    R(0) = ld8(base, (R(3) + 877));
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((CR_BIT(ctx, 2))) { goto L_8014F6B4; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F76C; }
L_8014F6B4:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014F6BCu, 0x80150650u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F71C; }
    R(3) = ld32(base, (R(30) + 5336));
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = ld32(base, (R(3) + 380));
    R(0) = R(0) & 0xFFFFFFF7u;
    st32(base, (R(3) + 380), R(0));
    R(3) = ld32(base, (R(30) + 5336));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 104));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F6ECu, ctx->ctr, 0);
    R(3) = ld32(base, (R(30) + 5336));
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 101);
    { uint32_t ea_ = (R(5) + 1256); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 92));
    { uint32_t ea_ = (R(5) + 1260); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x8014F718u, ctx->ctr, 0);
    goto L_8014F748;
L_8014F71C:;
    R(3) = ld32(base, (R(30) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 100);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 1244); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F748u, ctx->ctr, 0);
L_8014F748:;
    R(3) = ld32(base, (R(30) + 5336));
    ctx->f[1].u = ctx->f[31].u;
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 132));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F760u, ctx->ctr, 0);
    R(0) = (0 + 4);
    st32(base, (R(30) + 5404), R(0));
    goto L_8014F810;
L_8014F76C:;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F7C4; }
    R(3) = ld32(base, (R(30) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 100);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 1244); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F7A0u, ctx->ctr, 0);
    R(3) = ld32(base, (R(30) + 5336));
    ctx->f[1].u = ctx->f[31].u;
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 132));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F7B8u, ctx->ctr, 0);
    R(0) = (0 + 3);
    st32(base, (R(30) + 5404), R(0));
    goto L_8014F810;
L_8014F7C4:;
    R(3) = ld32(base, (R(30) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 98);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 1220); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F7F0u, ctx->ctr, 0);
    R(3) = ld32(base, (R(30) + 5336));
    ctx->f[1].u = ctx->f[31].u;
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 132));
    ctx->ctr = R(12);
    GM_CALLV(0x8014F808u, ctx->ctr, 0);
    R(0) = (0 + 2);
    st32(base, (R(30) + 5404), R(0));
L_8014F810:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 191);
    R(5) = (0 + 0);
    GM_CALLV(0x8014F820u, 0x80057E70u, 0);
    R(0) = lr;
}

/* fn_8014F840 (fn_8014F840, 356 bytes) */
static void pf_m_4f840(GM_CTX) {
    GM_FN(0x8014F840); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x8014F860u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(3) |R(3);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F888; }
    R(0) = (0 + 0);
    R(4) = (0 + 0x80370000u);
    st32(base, (R(31) + 5408), R(0));
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 28296);
    GM_CALLV(0x8014F884u, 0x8014ED00u, 0);
    goto L_8014F98C;
L_8014F888:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014F894u, 0x80168080u, 0);
    { uint32_t ea_ = (R(2) + -21972); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((!CR_BIT(ctx, 0))) { goto L_8014F8B4; }
    st32(base, (R(31) + 5424), R(0));
L_8014F8B4:;
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -21972); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014F8C4u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F8DC; }
    R(0) = (0 + 0);
    st32(base, (R(31) + 5424), R(0));
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014F8DCu, 0x8014F590u, 0);
L_8014F8DC:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014F8E8u, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014F98C; }
    R(0) = ld8(base, (R(30) + 877));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F938; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014F904u, 0x80162510u, 0);
    R(0) = ld8(base, (R(31) + 909));
    R(3) = (0 + 0);
    st32(base, (R(31) + 5408), R(3));
    R(3) = (0 + 19);
    R(0) = (int8_t)R(0);
    R(5) = (0 + 0);
    R(4) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x8014F92Cu, 0x80064610u, 0);
    R(0) = ld32(base, (R(3) + 0));
    st32(base, (R(31) + 5408), R(0));
    goto L_8014F97C;
L_8014F938:;
    cr_cmp_u(ctx, 0, R(0), 0x5u);
    if ((!CR_BIT(ctx, 2))) { goto L_8014F97C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014F948u, 0x80162510u, 0);
    R(0) = ld8(base, (R(31) + 909));
    R(3) = (0 + 0);
    st32(base, (R(31) + 5408), R(3));
    R(3) = (0 + 19);
    R(0) = (int8_t)R(0);
    R(5) = (0 + 0);
    R(0) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    R(6) = (0 + 0);
    R(4) = R(0) | 0x1u;
    R(7) = (0 + 0);
    GM_CALLV(0x8014F974u, 0x80064610u, 0);
    R(0) = ld32(base, (R(3) + 0));
    st32(base, (R(31) + 5408), R(0));
L_8014F97C:;
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 28296);
    GM_CALLV(0x8014F98Cu, 0x8014ED00u, 0);
L_8014F98C:;
    R(0) = lr;
}

/* fn_8014F9B0 (fn_8014F9B0, 276 bytes) */
static void pf_m_4f9b0(GM_CTX) {
    GM_FN(0x8014F9B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x8014F9D0u, 0x80162D00u, 0);
    R(4) = ld32(base, (R(30) + 5336));
    R(31) = R(3) |R(3);
    R(3) = (R(4) + 96);
    GM_CALLV(0x8014F9E0u, 0x80168080u, 0);
    { uint32_t ea_ = (R(2) + -21972); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 12));
    cr_cmp_u(ctx, 0, R(0), 0x9u);
    if ((CR_BIT(ctx, 1))) { goto L_8014FA00; }
    st32(base, (R(30) + 5424), R(0));
L_8014FA00:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014FA08u, 0x8014F290u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014FAAC; }
    R(3) = ld32(base, (R(30) + 5336));
    { uint32_t ea_ = (R(2) + -22060); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014FA20u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014FA34; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014FA30u, 0x8014F590u, 0);
    goto L_8014FAAC;
L_8014FA34:;
    R(3) = ld32(base, (R(30) + 5336));
    { uint32_t ea_ = (R(2) + -21964); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014FA44u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014FA80; }
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x8014FA58u, 0x80150830u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014FA60u, 0x80150150u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 189);
    R(5) = (0 + 0);
    GM_CALLV(0x8014FA70u, 0x80057E70u, 0);
    R(3) = ld32(base, (R(30) + 5336));
    R(0) = (0 + 0);
    st32(base, (R(3) + 660), R(0));
    goto L_8014FAAC;
L_8014FA80:;
    R(3) = ld32(base, (R(30) + 5336));
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014FA8Cu, 0x80168080u, 0);
    { uint32_t ea_ = (R(2) + -21960); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8014FAAC; }
    R(4) = (0 + 0x80370000u);
    R(3) = R(30) |R(30);
    R(4) = (R(4) + 28296);
    GM_CALLV(0x8014FAACu, 0x8014ED00u, 0);
L_8014FAAC:;
    R(0) = lr;
}

/* fn_8014FAD0 (fn_8014FAD0, 228 bytes) */
static void pf_m_4fad0(GM_CTX) {
    GM_FN(0x8014FAD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x8014FAF0u, 0x80162D00u, 0);
    R(4) = ld32(base, (R(30) + 5336));
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(2) + -21956); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(4) + 96);
    GM_CALLV(0x8014FB04u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014FB40; }
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x8014FB18u, 0x80150830u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014FB20u, 0x80150150u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 189);
    R(5) = (0 + 0);
    GM_CALLV(0x8014FB30u, 0x80057E70u, 0);
    R(3) = ld32(base, (R(30) + 5336));
    R(0) = (0 + 0);
    st32(base, (R(3) + 660), R(0));
    goto L_8014FB9C;
L_8014FB40:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014FB48u, 0x80150650u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014FB70; }
    R(3) = ld32(base, (R(30) + 5336));
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014FB5Cu, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014FB9C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8014FB6Cu, 0x801504D0u, 0);
    goto L_8014FB9C;
L_8014FB70:;
    R(3) = ld32(base, (R(30) + 5336));
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014FB7Cu, 0x80168080u, 0);
    { uint32_t ea_ = (R(2) + -21952); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8014FB9C; }
    R(4) = (0 + 0x80370000u);
    R(3) = R(30) |R(30);
    R(4) = (R(4) + 28296);
    GM_CALLV(0x8014FB9Cu, 0x8014ED00u, 0);
L_8014FB9C:;
    R(0) = lr;
}

/* fn_8014FBC0 (fn_8014FBC0, 144 bytes) */
static void pf_m_4fbc0(GM_CTX) {
    GM_FN(0x8014FBC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 5336));
    R(3) = (R(4) + 96);
    GM_CALLV(0x8014FBE0u, 0x80168080u, 0);
    { uint32_t ea_ = (R(2) + -21972); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 12));
    cr_cmp_u(ctx, 0, R(0), 0x9u);
    if ((CR_BIT(ctx, 1))) { goto L_8014FC00; }
    st32(base, (R(31) + 5424), R(0));
L_8014FC00:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014FC08u, 0x8014F290u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014FC3C; }
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -22060); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014FC20u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014FC34; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014FC30u, 0x8014F590u, 0);
    goto L_8014FC3C;
L_8014FC34:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014FC3Cu, 0x8014FAD0u, 0);
L_8014FC3C:;
    R(0) = lr;
}

/* fn_8014FC50 (fn_8014FC50, 108 bytes) */
static void pf_m_4fc50(GM_CTX) {
    GM_FN(0x8014FC50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 5336));
    R(0) = ld32(base, (R(4) + 344));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 99);
    if ((CR_BIT(ctx, 2))) { goto L_8014FCA0; }
    R(3) = ld32(base, (R(3) + 5336));
    R(5) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(5) + 3488);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 99);
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(5) + 1232); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014FCA0u, ctx->ctr, 0);
L_8014FCA0:;
    R(0) = (0 + 5);
    st32(base, (R(31) + 5404), R(0));
    R(0) = lr;
}

/* fn_8014FCC0 (fn_8014FCC0, 156 bytes) */
static void pf_m_4fcc0(GM_CTX) {
    GM_FN(0x8014FCC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 5336));
    R(3) = (R(4) + 96);
    GM_CALLV(0x8014FCE0u, 0x80168080u, 0);
    { uint32_t ea_ = (R(2) + -22028); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8014FCF4; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8014FCF4u, 0x80151AC0u, 0);
L_8014FCF4:;
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -21972); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014FD04u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014FD24; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 176);
    GM_CALLV(0x8014FD18u, 0x80056CB0u, 0);
    R(3) = ld32(base, (R(31) + 5336));
    R(0) = (0 + 0);
    st32(base, (R(3) + 660), R(0));
L_8014FD24:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 96);
    GM_CALLV(0x8014FD30u, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014FD48; }
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 28296);
    GM_CALLV(0x8014FD48u, 0x8014ED00u, 0);
L_8014FD48:;
    R(0) = lr;
}

/* fn_8014FD60 (fn_8014FD60, 76 bytes) */
static void pf_m_4fd60(GM_CTX) {
    GM_FN(0x8014FD60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld32(base, (R(3) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014FD80; }
    R(0) = ld8(base, (R(3) + 840));
    st8(base, (R(3) + 5440), R(0));
L_8014FD80:;
    R(0) = ld32(base, (R(3) + 5404));
    R(4) = (0 + 0x80320000u);
    R(4) = (R(4) + 26424);
    R(0) = ((int32_t)R(0) * 12);
    R(12) = R(4) + R(0);
    GM_CALLV(0x8014FD98u, 0x802DCBFCu, 0);
    R(0) = R(0) | 0x0u;
    R(0) = lr;
}

/* fn_8014FF00 (fn_8014FF00, 116 bytes) */
static void pf_m_4ff00(GM_CTX) {
    GM_FN(0x8014FF00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(5) = (R(5) + 3488);
    ctx->f[3].u = ctx->f[2].u;
    R(4) = (0 + 97);
    R(31) = R(3) |R(3);
    R(6) = ld32(base, (R(3) + 5336));
    R(0) = ld32(base, (R(6) + 380));
    R(0) = R(0) | 0x10u;
    st32(base, (R(6) + 380), R(0));
    R(3) = ld32(base, (R(3) + 5336));
    { uint32_t ea_ = (R(5) + 1208); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 100));
    ctx->ctr = R(12);
    GM_CALLV(0x8014FF50u, ctx->ctr, 0);
    R(3) = (0 + 0);
    R(0) = (0 + 30);
    st32(base, (R(31) + 5428), R(3));
    st32(base, (R(31) + 5432), R(0));
    R(0) = lr;
}

/* fn_8014FF80 (fn_8014FF80, 148 bytes) */
static void pf_m_4ff80(GM_CTX) {
    GM_FN(0x8014FF80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 5336));
    R(0) = ld32(base, (R(4) + 380));
    R(0) = R(0) & 0xFFFFFFEFu;
    st32(base, (R(4) + 380), R(0));
    R(3) = ld32(base, (R(3) + 5336));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 104));
    ctx->ctr = R(12);
    GM_CALLV(0x8014FFBCu, ctx->ctr, 0);
    R(0) = ld32(base, (R(31) + 5428));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8014FFE4; }
    R(3) = ld32(base, (R(31) + 5408));
    GM_CALLV(0x8014FFD0u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8014FFE4; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x8014FFE4u, 0x8014EFB0u, 0);
L_8014FFE4:;
    R(3) = ld32(base, (R(31) + 5408));
    GM_CALLV(0x8014FFECu, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80150000; }
    R(3) = ld32(base, (R(31) + 5336));
    R(0) = (0 + 0);
    st32(base, (R(3) + 660), R(0));
L_80150000:;
    R(0) = lr;
}

/* fn_80150020 (fn_80150020, 104 bytes) */
static void pf_m_50020(GM_CTX) {
    GM_FN(0x80150020); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x8015003Cu, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150074; }
    R(0) = ld16(base, (R(3) + 8));
    cr_cmp_u(ctx, 0, R(0), 0x13u);
    if ((!CR_BIT(ctx, 2))) { goto L_80150064; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 349);
    R(5) = (0 + 0);
    GM_CALLV(0x80150060u, 0x80057E70u, 0);
    goto L_80150074;
L_80150064:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 192);
    R(5) = (0 + 0);
    GM_CALLV(0x80150074u, 0x80057E70u, 0);
L_80150074:;
    R(0) = lr;
}

/* fn_80150090 (fn_80150090, 184 bytes) */
static void pf_m_50090(GM_CTX) {
    GM_FN(0x80150090); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 1096));
    ctx->ctr = R(12);
    GM_CALLV(0x801500B4u, ctx->ctr, 0);
    R(3) = ld32(base, (R(31) + 5336));
    { uint32_t ea_ = (R(2) + -22028); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 96);
    GM_CALLV(0x801500C4u, 0x801690E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150110; }
    R(0) = (0 + 1);
    st32(base, (R(31) + 5428), R(0));
    R(3) = ld32(base, (R(31) + 5408));
    GM_CALLV(0x801500DCu, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(4) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80150110; }
    R(0) = (0 + 4);
    st8(base, (R(3) + 876), R(0));
    R(3) = R(31) |R(31);
    GM_CALLV(0x801500F8u, 0x801507C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150110; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150108u, 0x80150020u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150110u, 0x80150150u, 0);
L_80150110:;
    R(3) = ld32(base, (R(31) + 5336));
    R(3) = (R(3) + 96);
    GM_CALLV(0x8015011Cu, 0x80169020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150134; }
    R(4) = (0 + 0x80370000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + 28296);
    GM_CALLV(0x80150134u, 0x8014ED00u, 0);
L_80150134:;
    R(0) = lr;
}

/* fn_80150150 (fn_80150150, 92 bytes) */
static void pf_m_50150(GM_CTX) {
    GM_FN(0x80150150); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x8015016Cu, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150194; }
    R(0) = (0 + 0);
    st8(base, (R(3) + 876), R(0));
    st32(base, (R(3) + 872), R(0));
    R(3) = (0 + 1);
    R(4) = ld32(base, (R(31) + 5336));
    st32(base, (R(31) + 5408), R(0));
    st32(base, (R(4) + 660), R(0));
    goto L_80150198;
L_80150194:;
    R(3) = (0 + 0);
L_80150198:;
    R(0) = lr;
}

/* fn_801501B0 (fn_801501B0, 28 bytes) */
static void pf_m_501b0(GM_CTX) {
    { uint32_t ea_ = (R(2) + -21948); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0);
    R(0) = (0 + 1);
    st32(base, (R(3) + 5464), R(4));
    { uint32_t ea_ = (R(3) + 5468); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(3) + 5472), R(0));
}

/* fn_801501D0 (fn_801501D0, 272 bytes) */
static void pf_m_501d0(GM_CTX) {
    GM_FN(0x801501D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5408));
    GM_CALLV(0x801501F8u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150208; }
    R(3) = (0 + 0);
    goto L_801502C4;
L_80150208:;
    R(12) = ld32(base, (R(29) + 5344));
    R(3) = (R(29) + 5344);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x8015021Cu, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 28296);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x80150234u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150244; }
    R(3) = (0 + 0);
    goto L_801502C4;
L_80150244:;
    R(31) = ld32(base, (R(30) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80150258; }
    R(3) = (0 + 0);
    goto L_801502C4;
L_80150258:;
    R(0) = ld8(base, (R(31) + 876));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015026C; }
    R(3) = (0 + 0);
    goto L_801502C4;
L_8015026C:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x80150274u, 0x8008C570u, 0);
    { uint32_t ea_ = (R(29) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 5468); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_801502C0; }
    st32(base, (R(29) + 5464), R(30));
    { uint32_t ea_ = (R(29) + 5468); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld8(base, (R(31) + 877));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801502B0; }
    R(0) = (0 + 1);
    st32(base, (R(29) + 5472), R(0));
    goto L_801502B8;
L_801502B0:;
    R(0) = (0 + 0);
    st32(base, (R(29) + 5472), R(0));
L_801502B8:;
    R(3) = (0 + 1);
    goto L_801502C4;
L_801502C0:;
    R(3) = (0 + 0);
L_801502C4:;
    R(0) = lr;
}

/* fn_801502E0 (fn_801502E0, 256 bytes) */
static void pf_m_502e0(GM_CTX) {
    GM_FN(0x801502E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 5464));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801503B8; }
    R(31) = ld32(base, (R(3) + 5336));
    R(3) = R(0) |R(0);
    GM_CALLV(0x80150320u, 0x8008C570u, 0);
    R(0) = ld32(base, (R(30) + 5472));
    ctx->f[30].u = ctx->f[1].u;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_80150350; }
    R(4) = ld32(base, (R(30) + 5464));
    R(3) = R(30) |R(30);
    R(4) = ld32(base, (R(4) + 4));
    GM_CALLV(0x80150340u, 0x8014ED90u, 0);
    ctx->f[1].u = ctx->f[30].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8015034Cu, 0x800FFDB0u, 0);
    goto L_801503B0;
L_80150350:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x80150358u, 0x8014FC50u, 0);
    { uint32_t ea_ = (R(30) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80150374; }
    R(3) = ld32(base, (R(30) + 5464));
    GM_CALLV(0x8015036Cu, 0x8008C530u, 0);
    ctx->f[31].u = ctx->f[1].u;
    goto L_80150380;
L_80150374:;
    R(3) = ld32(base, (R(30) + 5464));
    GM_CALLV(0x8015037Cu, 0x8008C550u, 0);
    ctx->f[31].u = ctx->f[1].u;
L_80150380:;
    { uint32_t ea_ = (R(30) + 180); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(3) = (R(30) + 328);
    GM_CALLV(0x8015038Cu, 0x8008C510u, 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[31].d); }
    R(3) = R(30) |R(30);
    R(4) = (f + 8);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[30].d); }
    GM_CALLV(0x801503A4u, 0x80152880u, 0);
    ctx->f[1].u = ctx->f[31].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x801503B0u, 0x800FFDB0u, 0);
L_801503B0:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x801503B8u, 0x801501B0u, 0);
L_801503B8:;
    R(0) = lr;
}

/* fn_80150650 (fn_80150650, 40 bytes) */
static void pf_m_50650(GM_CTX) {
    R(0) = ld32(base, (R(3) + 5476));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    if ((CR_BIT(ctx, 0))) { goto L_80150664; }
    R(3) = (0 + 1);
    return;
L_80150664:;
    R(3) = ld32(base, (R(3) + 5480));
    R(0) = -(int32_t)R(3);
    R(0) = R(0) & ~R(3);
    R(3) = rotl32(R(0), 1) & 0x1u;
}

/* fn_80150680 (fn_80150680, 32 bytes) */
static void pf_m_50680(GM_CTX) {
    R(4) = ld32(base, (R(3) + 5476));
    R(0) = (R(4) + 1);
    st32(base, (R(3) + 5476), R(0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    if ((!CR_BIT(ctx, 1))) return;
    R(0) = (0 + 5);
    st32(base, (R(3) + 5476), R(0));
}

/* fn_801506A0 (fn_801506A0, 88 bytes) */
static void pf_m_506a0(GM_CTX) {
    GM_FN(0x801506A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_801506E4; }
    R(0) = (0 + 1);
    st32(base, (R(3) + 5444), R(0));
    R(3) = R(4) |R(4);
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 128));
    ctx->ctr = R(12);
    GM_CALLV(0x801506DCu, ctx->ctr, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 5444), R(0));
L_801506E4:;
    R(0) = lr;
}

/* fn_80150760 (fn_80150760, 88 bytes) */
static void pf_m_50760(GM_CTX) {
    GM_FN(0x80150760); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_801507A4; }
    R(0) = (0 + 1);
    st32(base, (R(3) + 5444), R(0));
    R(3) = R(4) |R(4);
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 136));
    ctx->ctr = R(12);
    GM_CALLV(0x8015079Cu, ctx->ctr, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 5444), R(0));
L_801507A4:;
    R(0) = lr;
}

/* fn_801507C0 (fn_801507C0, 108 bytes) */
static void pf_m_507c0(GM_CTX) {
    GM_FN(0x801507C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(5) = (0 + 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8015080C; }
    R(0) = (0 + 1);
    st32(base, (R(3) + 5444), R(0));
    R(3) = R(4) |R(4);
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 140));
    ctx->ctr = R(12);
    GM_CALLV(0x80150800u, ctx->ctr, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 5444), R(0));
    R(5) = R(3) |R(3);
L_8015080C:;
    R(0) = -(int32_t)R(5);
    R(0) = R(0) |R(5);
    R(3) = rotl32(R(0), 1) & 0x1u;
    R(0) = lr;
}

/* fn_80150830 (fn_80150830, 108 bytes) */
static void pf_m_50830(GM_CTX) {
    GM_FN(0x80150830); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(5) = (0 + 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8015087C; }
    R(0) = (0 + 1);
    st32(base, (R(3) + 5444), R(0));
    R(3) = R(4) |R(4);
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 144));
    ctx->ctr = R(12);
    GM_CALLV(0x80150870u, ctx->ctr, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 5444), R(0));
    R(5) = R(3) |R(3);
L_8015087C:;
    R(0) = -(int32_t)R(5);
    R(0) = R(0) |R(5);
    R(3) = rotl32(R(0), 1) & 0x1u;
    R(0) = lr;
}

/* fn_801508A0 (fn_801508A0, 516 bytes) */
static void pf_m_508a0(GM_CTX) {
    GM_FN(0x801508A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 288));
    ctx->ctr = R(12);
    GM_CALLV(0x801508C4u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80150A90; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 2);
    GM_CALLV(0x801508D8u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801508E8; }
    R(3) = (R(31) + 5332);
    GM_CALLV(0x801508E8u, 0x800D6E90u, 0);
L_801508E8:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x801508F0u, 0x8004D5C0u, 0);
    R(0) = ld8(base, (R(31) + 840));
    R(3) = R(31) |R(31);
    st8(base, (R(31) + 4148), R(0));
    R(4) = (0 + 150);
    GM_CALLV(0x80150904u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015093C; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 151);
    GM_CALLV(0x80150918u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015093C; }
    R(3) = (R(31) + 3748);
    R(4) = (f + 8);
    GM_CALLV(0x8015092Cu, 0x8005E7A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015093C; }
    R(0) = ld32(base, (f + 8));
    st8(base, (R(31) + 840), R(0));
L_8015093C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150944u, 0x8004E360u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80150A90; }
    R(3) = ld8(base, (R(13) + -22920));
    R(0) = ld8(base, (R(31) + 910));
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80150A90; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150964u, 0x80057D70u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8015096Cu, 0x80056D50u, 0);
    R(3) = ld32(base, (R(31) + 5432));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150980; }
    R(0) = (R(3) + -1);
    st32(base, (R(31) + 5432), R(0));
L_80150980:;
    R(3) = ld32(base, (R(31) + 5436));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150994; }
    R(0) = (R(3) + -1);
    st32(base, (R(31) + 5436), R(0));
L_80150994:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8015099Cu, 0x80150AB0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x801509A4u, 0x8014ECE0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 179);
    GM_CALLV(0x801509B0u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801509C8; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x801509C0u, 0x80047440u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x801509C8u, 0x80056E40u, 0);
L_801509C8:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x801509D0u, 0x80151D00u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 980));
    ctx->ctr = R(12);
    GM_CALLV(0x801509E4u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801509F4; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x801509F4u, 0x80053740u, 0);
L_801509F4:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x801509FCu, 0x80151630u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 1);
    GM_CALLV(0x80150A08u, 0x800543E0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150A10u, 0x80055EF0u, 0);
    R(0) = ld32(base, (R(31) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80150A50; }
    { uint32_t ea_ = (R(31) + 804); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(13) + -22704));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(31) + 796); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(3) + -400); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80150A50; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150A4Cu, 0x80162510u, 0);
    goto L_80150A90;
L_80150A50:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 119);
    GM_CALLV(0x80150A5Cu, 0x80056C70u, 0);
    R(0) = ld32(base, (R(31) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150A90; }
    R(0) = ld8(base, (R(31) + 3773));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150A90; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150A7Cu, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150A90; }
    R(4) = (0 + 6);
    R(3) = (R(3) + 3748);
    GM_CALLV(0x80150A90u, 0x8005E3B0u, 0);
L_80150A90:;
    R(0) = lr;
}

/* fn_80150AB0 (fn_80150AB0, 196 bytes) */
static void pf_m_50ab0(GM_CTX) {
    GM_FN(0x80150AB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150B60; }
    R(4) = (0 + 139);
    GM_CALLV(0x80150AD8u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150B0C; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 139);
    GM_CALLV(0x80150AECu, 0x80056CB0u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    R(5) = (0 + 4);
    R(12) = ld32(base, (R(12) + 1012));
    ctx->ctr = R(12);
    GM_CALLV(0x80150B08u, ctx->ctr, 0);
    goto L_80150B60;
L_80150B0C:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 140);
    GM_CALLV(0x80150B18u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150B54; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 140);
    GM_CALLV(0x80150B2Cu, 0x80056CB0u, 0);
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80150B60; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -22032); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 1028));
    ctx->ctr = R(12);
    GM_CALLV(0x80150B50u, ctx->ctr, 0);
    goto L_80150B60;
L_80150B54:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150B5Cu, 0x8014EE10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
L_80150B60:;
    R(0) = lr;
}

/* fn_80150B80 (fn_80150B80, 332 bytes) */
static void pf_m_50b80(GM_CTX) {
    GM_FN(0x80150B80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 1);
    R(31) = R(3) |R(3);
    GM_CALLV(0x80150B9Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150CB8; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150BACu, 0x80054280u, 0);
    { uint32_t ea_ = (R(31) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(31) + 5332);
    { uint32_t ea_ = (R(31) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (f + 28);
    { uint32_t ea_ = (R(31) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (f + 8);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    R(6) = (f + 16);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 228); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 224); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 220); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    R(0) = (int16_t)ld16(base, (R(31) + 256));
    st16(base, (f + 8), R(0));
    R(0) = (int16_t)ld16(base, (R(31) + 258));
    st16(base, (f + 10), R(0));
    R(0) = (int16_t)ld16(base, (R(31) + 260));
    st16(base, (f + 12), R(0));
    GM_CALLV(0x80150C08u, 0x800D6F40u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 123);
    GM_CALLV(0x80150C14u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150C38; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 123);
    GM_CALLV(0x80150C28u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150C30u, 0x80151AD0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150C38u, 0x801501B0u, 0);
L_80150C38:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 124);
    GM_CALLV(0x80150C44u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150C60; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 124);
    GM_CALLV(0x80150C58u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150C60u, 0x80151C30u, 0);
L_80150C60:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 119);
    GM_CALLV(0x80150C6Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150C94; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80150C7Cu, 0x800537B0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 119);
    GM_CALLV(0x80150C88u, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 120);
    GM_CALLV(0x80150C94u, 0x80056CB0u, 0);
L_80150C94:;
    R(3) = ld32(base, (R(31) + 5408));
    GM_CALLV(0x80150C9Cu, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150CB8; }
    R(12) = ld32(base, (R(3) + 96));
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 148));
    ctx->ctr = R(12);
    GM_CALLV(0x80150CB8u, ctx->ctr, 0);
L_80150CB8:;
    R(0) = lr;
}

/* fn_80150DB0 (fn_80150DB0, 40 bytes) */
static void pf_m_50db0(GM_CTX) {
    GM_FN(0x80150DB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (R(3) + 5332);
    GM_CALLV(0x80150DC4u, 0x800D7020u, 0);
    R(0) = lr;
    R(3) = (0 + 1);
}

/* fn_80150DE0 (fn_80150DE0, 44 bytes) */
static void pf_m_50de0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 5444));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_80150E04; }
    R(0) = ld8(base, (R(3) + 5441));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), -1);
    if ((CR_BIT(ctx, 2))) { goto L_80150E04; }
    R(3) = (R(3) + 5441);
    return;
L_80150E04:;
    R(3) = (R(3) + 909);
}

/* fn_80150E10 (fn_80150E10, 200 bytes) */
static void pf_m_50e10(GM_CTX) {
    GM_FN(0x80150E10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150E48; }
    GM_CALLV(0x80150E34u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80150EC4; }
    { uint32_t ea_ = (R(3) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 180); stfs(base, ea_, ctx->f[0].d); }
    goto L_80150EC4;
L_80150E48:;
    R(0) = ld8(base, (R(3) + 4149));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_80150E94; }
    R(0) = ld8(base, (R(3) + 911));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80150E94; }
    R(4) = ld8(base, (R(3) + 4150));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 8), R(0));
    R(0) = rotl32(R(4), 5) & 0xFFFFFFE0u;
    { uint32_t ea_ = (R(2) + -21928); ctx->f[2].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    { uint32_t ea_ = (R(2) + -21940); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[0].d); }
    goto L_80150EC4;
L_80150E94:;
    R(4) = ld8(base, (R(3) + 4150));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 8), R(0));
    R(0) = rotl32(R(4), 5) & 0xFFFFFFE0u;
    { uint32_t ea_ = (R(2) + -21928); ctx->f[2].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    { uint32_t ea_ = (R(2) + -21936); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[0].d); }
L_80150EC4:;
    R(0) = lr;
}

/* fn_80151030 (fn_80151030, 16 bytes) */
static void pf_m_51030(GM_CTX) {
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 1024));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_80151040 (fn_80151040, 552 bytes) */
static void pf_m_51040(GM_CTX) {
    GM_FN(0x80151040); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    ctx->f[30].u = ctx->f[1].u;
    R(31) = (0 + 0x80370000u);
    ctx->f[31].u = ctx->f[2].u;
    R(26) = R(3) |R(3);
    R(27) = R(4) |R(4);
    R(28) = R(5) |R(5);
    R(29) = R(6) |R(6);
    R(31) = (R(31) + 27320);
    GM_CALLV(0x80151088u, 0x8004DD00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801510A4; }
    R(3) = R(26) |R(26);
    R(4) = (0 + 4);
    GM_CALLV(0x8015109Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801510AC; }
L_801510A4:;
    R(3) = (0 + 0);
    goto L_80151240;
L_801510AC:;
    R(12) = ld32(base, (R(26) + 96));
    R(3) = R(26) |R(26);
    R(4) = (0 + 0);
    R(12) = ld32(base, (R(12) + 1036));
    ctx->ctr = R(12);
    GM_CALLV(0x801510C4u, ctx->ctr, 0);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(30) = (0 + 0);
    { uint32_t ea_ = (R(26) + 268); stfs(base, ea_, ctx->f[31].d); }
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80151114; }
    R(3) = R(26) |R(26);
    R(4) = (0 + 128);
    GM_CALLV(0x801510E8u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151104; }
    R(0) = ld32(base, (R(26) + 4316));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80151114; }
    R(30) = (0 + 1);
    goto L_80151114;
L_80151104:;
    R(0) = ld32(base, (R(26) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80151114; }
    R(30) = (0 + 0);
L_80151114:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801511D8; }
    R(3) = R(26) |R(26);
    R(30) = (0 + 0);
    R(4) = (0 + 15);
    GM_CALLV(0x8015112Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151138; }
    R(30) = (0 + 1);
L_80151138:;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[30].d);
    if ((!CR_BIT(ctx, 2))) { goto L_80151164; }
    R(12) = ld32(base, (R(26) + 96));
    R(3) = R(26) |R(26);
    R(4) = (R(31) + 396);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    ctx->ctr = R(12);
    GM_CALLV(0x80151160u, ctx->ctr, 0);
    goto L_8015119C;
L_80151164:;
    R(3) = (0 + 0x80310000u);
    R(0) = (0 + 1);
    R(3) = (R(3) + -30288);
    st32(base, (f + 8), R(3));
    R(3) = R(26) |R(26);
    R(4) = (R(31) + 332);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[30].d); }
    R(5) = (f + 8);
    st32(base, (f + 16), R(29));
    st32(base, (f + 20), R(0));
    R(12) = ld32(base, (R(26) + 96));
    R(12) = ld32(base, (R(12) + 660));
    ctx->ctr = R(12);
    GM_CALLV(0x8015119Cu, ctx->ctr, 0);
L_8015119C:;
    R(3) = R(26) |R(26);
    R(4) = (0 + 171);
    GM_CALLV(0x801511A8u, 0x80056C70u, 0);
    R(3) = R(26) |R(26);
    R(4) = (0 + 136);
    GM_CALLV(0x801511B4u, 0x80056C70u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801511D8; }
    R(12) = ld32(base, (R(26) + 96));
    R(3) = R(26) |R(26);
    R(4) = (R(31) + 588);
    R(5) = (0 + 1);
    R(12) = ld32(base, (R(12) + 660));
    ctx->ctr = R(12);
    GM_CALLV(0x801511D8u, ctx->ctr, 0);
L_801511D8:;
    R(3) = R(26) |R(26);
    R(4) = (0 + 167);
    GM_CALLV(0x801511E4u, 0x80056CB0u, 0);
    R(0) = ld32(base, (R(26) + 4308));
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    R(0) = R(0) & 0xFFFFFFFEu;
    st32(base, (R(26) + 4308), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80151210; }
    R(3) = (R(26) + 3748);
    R(4) = (0 + 1);
    GM_CALLV(0x80151204u, 0x8005E3B0u, 0);
    R(3) = R(26) |R(26);
    R(4) = (0 + 167);
    GM_CALLV(0x80151210u, 0x80056C70u, 0);
L_80151210:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_80151228; }
    R(3) = (R(26) + 3748);
    R(4) = (0 + 3);
    GM_CALLV(0x80151224u, 0x8005E3B0u, 0);
    goto L_8015123C;
L_80151228:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_8015123C; }
    R(3) = (R(26) + 3748);
    R(4) = (0 + 4);
    GM_CALLV(0x8015123Cu, 0x8005E3B0u, 0);
L_8015123C:;
    R(3) = (0 + 1);
L_80151240:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_80151270 (fn_80151270, 176 bytes) */
static void pf_m_51270(GM_CTX) {
    GM_FN(0x80151270); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801512D8; }
    GM_CALLV(0x80151294u, 0x8004DD00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801512D8; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 4);
    GM_CALLV(0x801512A8u, 0x8004DB40u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801512D8; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 185);
    GM_CALLV(0x801512BCu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801512D8; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 132);
    GM_CALLV(0x801512D0u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801512E0; }
L_801512D8:;
    R(3) = (0 + 1);
    goto L_8015130C;
L_801512E0:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x801512E8u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151308; }
    R(4) = ld32(base, (R(3) + 4212));
    R(0) = ld32(base, (R(3) + 4216));
    R(0) = R(4) |R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80151308; }
    R(3) = (0 + 1);
    goto L_8015130C;
L_80151308:;
    R(3) = (0 + 0);
L_8015130C:;
    R(0) = lr;
}

/* fn_80151320 (fn_80151320, 168 bytes) */
static void pf_m_51320(GM_CTX) {
    GM_FN(0x80151320); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 1008));
    ctx->ctr = R(12);
    GM_CALLV(0x80151354u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151364; }
    R(3) = (0 + 0);
    goto L_801513AC;
L_80151364:;
    R(3) = R(31) |R(31);
    R(31) = ld8(base, (R(31) + 909));
    R(12) = ld32(base, (R(3) + 96));
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(31) = (int8_t)R(31);
    R(12) = ld32(base, (R(12) + 1104));
    ctx->ctr = R(12);
    GM_CALLV(0x80151388u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801513A8; }
    R(3) = ld32(base, (R(13) + -22136));
    R(4) = R(31) |R(31);
    R(5) = (0 + 4);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x801513A8u, 0x800D8BB0u, 0);
L_801513A8:;
    R(3) = (0 + 0);
L_801513AC:;
    R(0) = lr;
}

/* fn_80151470 (fn_80151470, 332 bytes) */
static void pf_m_51470(GM_CTX) {
    GM_FN(0x80151470); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(4) = (0 + 4);
    R(28) = R(3) |R(3);
    GM_CALLV(0x801514A0u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801514BC; }
    R(3) = R(28) |R(28);
    R(4) = (0 + 6);
    GM_CALLV(0x801514B4u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801514C4; }
L_801514BC:;
    R(3) = (0 + 0);
    goto L_8015159C;
L_801514C4:;
    R(0) = ld32(base, (R(28) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151598; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x801514D8u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80151598; }
    R(3) = R(28) |R(28);
    R(4) = (0 + 0);
    GM_CALLV(0x801514F0u, 0x8014EFB0u, 0);
    R(0) = (R(30) + -3);
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 1))) { goto L_80151508; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 17);
    if ((CR_BIT(ctx, 2))) { goto L_80151528; }
    goto L_80151540;
L_80151508:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 1012));
    ctx->ctr = R(12);
    GM_CALLV(0x80151524u, ctx->ctr, 0);
    goto L_80151598;
L_80151528:;
    R(12) = ld32(base, (R(28) + 96));
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 264));
    ctx->ctr = R(12);
    GM_CALLV(0x8015153Cu, ctx->ctr, 0);
    goto L_80151598;
L_80151540:;
    R(0) = (0 + 127);
    st32(base, (R(31) + 4212), R(0));
    { uint32_t ea_ = (R(2) + -21976); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(31) + 96));
    R(4) = (0 + 1);
    { uint32_t ea_ = (R(2) + -30776); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 2);
    R(12) = ld32(base, (R(12) + 1020));
    R(6) = (0 + 0);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->ctr = R(12);
    GM_CALLV(0x80151578u, ctx->ctr, 0);
    R(12) = ld32(base, (R(28) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(28) |R(28);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27464);
    ctx->ctr = R(12);
    GM_CALLV(0x80151598u, ctx->ctr, 0);
L_80151598:;
    R(3) = (0 + 1);
L_8015159C:;
    R(0) = lr;
}

/* fn_801515C0 (fn_801515C0, 36 bytes) */
static void pf_m_515c0(GM_CTX) {
    R(4) = ld32(base, (R(3) + 5336));
    R(3) = (0 + 0x802F0000u);
    R(3) = (R(3) + 22632);
    R(0) = ld32(base, (R(4) + 352));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) return;
    R(3) = (0 + 0x802F0000u);
    R(3) = (R(3) + 22680);
}

/* fn_80151630 (fn_80151630, 668 bytes) */
static void pf_m_51630(GM_CTX) {
    GM_FN(0x80151630); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 184);
    R(30) = R(3) |R(3);
    GM_CALLV(0x80151650u, 0x80056CB0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x80151658u, 0x801515C0u, 0);
    R(0) = ld32(base, (R(3) + 0));
    st32(base, (R(30) + 4260), R(0));
    R(0) = ld32(base, (R(3) + 4));
    st32(base, (R(30) + 4264), R(0));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (R(30) + 4268), R(0));
    R(0) = ld32(base, (R(3) + 12));
    st32(base, (R(30) + 4272), R(0));
    R(0) = ld32(base, (R(3) + 16));
    st32(base, (R(30) + 4244), R(0));
    R(0) = ld32(base, (R(3) + 20));
    st32(base, (R(30) + 4248), R(0));
    R(0) = ld32(base, (R(3) + 24));
    st32(base, (R(30) + 4252), R(0));
    R(0) = ld32(base, (R(3) + 28));
    st32(base, (R(30) + 4256), R(0));
    R(0) = ld32(base, (R(3) + 32));
    st32(base, (R(30) + 4276), R(0));
    R(0) = ld32(base, (R(3) + 36));
    st32(base, (R(30) + 4280), R(0));
    R(0) = ld32(base, (R(3) + 40));
    st32(base, (R(30) + 4284), R(0));
    R(0) = ld32(base, (R(3) + 44));
    R(3) = R(30) |R(30);
    st32(base, (R(30) + 4288), R(0));
    GM_CALLV(0x801516C0u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((!CR_BIT(ctx, 2))) { goto L_801516EC; }
    R(0) = (0 + 2049);
    st32(base, (R(30) + 4260), R(0));
    R(3) = R(30) |R(30);
    R(4) = (0 + 184);
    st32(base, (R(30) + 4244), R(0));
    st32(base, (R(30) + 4276), R(0));
    GM_CALLV(0x801516E8u, 0x80056C70u, 0);
    goto L_80151878;
L_801516EC:;
    R(12) = ld32(base, (R(30) + 5220));
    R(3) = (R(30) + 5220);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x80151700u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 28100);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x80151718u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015179C; }
    R(3) = ld32(base, (R(30) + 5336));
    R(0) = ld32(base, (R(3) + 340));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 17);
    if ((CR_BIT(ctx, 2))) { goto L_8015173C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 18);
    if ((CR_BIT(ctx, 2))) { goto L_8015177C; }
    goto L_8015179C;
L_8015173C:;
    { uint32_t ea_ = (R(30) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8015179C; }
    R(0) = ld32(base, (R(30) + 4260));
    R(3) = R(30) |R(30);
    R(4) = (0 + 196);
    R(0) = R(0) | 0x500000u;
    st32(base, (R(30) + 4260), R(0));
    GM_CALLV(0x80151764u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015179C; }
    R(0) = ld32(base, (R(30) + 4260));
    R(0) = R(0) | 0x800000u;
    st32(base, (R(30) + 4260), R(0));
    goto L_8015179C;
L_8015177C:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 196);
    GM_CALLV(0x80151788u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015179C; }
    R(0) = ld32(base, (R(30) + 4260));
    R(0) = R(0) | 0x900000u;
    st32(base, (R(30) + 4260), R(0));
L_8015179C:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 48);
    GM_CALLV(0x801517A8u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801517BC; }
    R(0) = ld32(base, (R(30) + 4260));
    R(0) = R(0) | 0x10000u;
    st32(base, (R(30) + 4260), R(0));
L_801517BC:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 164);
    GM_CALLV(0x801517C8u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801517DC; }
    R(0) = ld32(base, (R(30) + 4260));
    R(0) = R(0) | 0x8u;
    st32(base, (R(30) + 4260), R(0));
L_801517DC:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 93);
    GM_CALLV(0x801517E8u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801517FC; }
    R(0) = ld32(base, (R(30) + 4260));
    R(0) = R(0) | 0x20u;
    st32(base, (R(30) + 4260), R(0));
L_801517FC:;
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 980));
    ctx->ctr = R(12);
    GM_CALLV(0x80151810u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151830; }
    R(3) = ld32(base, (R(30) + 4276));
    R(0) = ld32(base, (R(30) + 4244));
    R(3) = R(3) | 0x2000000u;
    st32(base, (R(30) + 4276), R(3));
    R(0) = R(0) | 0x2000000u;
    st32(base, (R(30) + 4244), R(0));
L_80151830:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 130);
    GM_CALLV(0x8015183Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151850; }
    R(0) = ld32(base, (R(30) + 4244));
    R(0) = R(0) | 0x4000000u;
    st32(base, (R(30) + 4244), R(0));
L_80151850:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 224));
    ctx->ctr = R(12);
    GM_CALLV(0x80151864u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151878; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 184);
    GM_CALLV(0x80151878u, 0x80056C70u, 0);
L_80151878:;
    R(4) = R(30) |R(30);
    R(3) = (R(30) + 492);
    R(5) = (R(30) + 4260);
    R(6) = (R(30) + 4244);
    R(7) = (R(30) + 4276);
    GM_CALLV(0x80151890u, 0x8006D090u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x80151898u, 0x80053490u, 0);
    st8(base, (R(30) + 721), R(3));
    R(3) = R(30) |R(30);
    GM_CALLV(0x801518A4u, 0x80053490u, 0);
    R(0) = ld8(base, (R(30) + 911));
    st8(base, (R(30) + 778), R(3));
    st8(base, (R(30) + 728), R(0));
    st8(base, (R(30) + 782), R(0));
    R(0) = lr;
}

/* fn_801518D0 (fn_801518D0, 320 bytes) */
static void pf_m_518d0(GM_CTX) {
    GM_FN(0x801518D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x801518E8u, 0x80054F80u, 0);
    R(0) = ld32(base, (R(31) + 4312));
    R(0) = R(0) & 0x20000000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80151964; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 26);
    GM_CALLV(0x80151900u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80151964; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 27);
    GM_CALLV(0x80151914u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80151964; }
    R(3) = ld32(base, (R(31) + 4308));
    R(0) = R(3) & 0x20u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80151938; }
    { uint32_t ea_ = (R(31) + 268); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 0))) { goto L_80151950; }
L_80151938:;
    R(0) = R(3) & 0x40u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80151964; }
    { uint32_t ea_ = (R(31) + 268); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80151964; }
L_80151950:;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 268); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 272); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 5316); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 5324); stfs(base, ea_, ctx->f[0].d); }
L_80151964:;
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_801519AC; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 83);
    GM_CALLV(0x8015197Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801519AC; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 6);
    GM_CALLV(0x80151990u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_801519AC; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 4);
    GM_CALLV(0x801519A4u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801519C0; }
L_801519AC:;
    R(0) = ld32(base, (R(31) + 4312));
    R(0) = R(0) & 0x40000000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_801519C0; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x801519C0u, 0x800581A0u, 0);
L_801519C0:;
    R(0) = ld32(base, (R(31) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_801519FC; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 1036));
    ctx->ctr = R(12);
    GM_CALLV(0x801519E4u, ctx->ctr, 0);
    R(3) = (R(31) + 3748);
    R(4) = (0 + 3);
    GM_CALLV(0x801519F0u, 0x8005E460u, 0);
    R(3) = (R(31) + 3748);
    R(4) = (0 + 4);
    GM_CALLV(0x801519FCu, 0x8005E460u, 0);
L_801519FC:;
    R(0) = lr;
}

/* fn_80151A70 (fn_80151A70, 68 bytes) */
static void pf_m_51a70(GM_CTX) {
    GM_FN(0x80151A70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 14);
    R(31) = R(3) |R(3);
    GM_CALLV(0x80151A8Cu, 0x80056CB0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 167);
    GM_CALLV(0x80151A98u, 0x80056CB0u, 0);
    R(0) = (0 + 1);
    st8(base, (R(31) + 5421), R(0));
    R(0) = lr;
}

/* fn_80151AC0 (fn_80151AC0, 8 bytes) */
static void pf_m_51ac0(GM_CTX) {
    R(4) = (0 + 123);
    GM_TAIL(0x80056C70u, 0); return;
}

/* fn_80151AD0 (fn_80151AD0, 324 bytes) */
static void pf_m_51ad0(GM_CTX) {
    GM_FN(0x80151AD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 23);
    R(4) = (f + 56);
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5336));
    GM_CALLV(0x80151AF4u, 0x800D5790u, 0);
    R(3) = ld32(base, (R(31) + 5336));
    R(4) = (f + 44);
    R(5) = (0 + 17);
    GM_CALLV(0x80151B04u, 0x800D5790u, 0);
    { uint32_t ea_ = (f + 60); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 48); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[3].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22104); ctx->f[10].d = ctx->ps1[10] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[5].d * ctx->f[10].d);
    { uint32_t ea_ = (R(31) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[6].d * ctx->f[10].d);
    { uint32_t ea_ = (f + 64); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[11].d = ctx->ps1[11] = frsp(ctx->f[8].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 52); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 180); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[9].d - ctx->f[0].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[2].d + ctx->f[1].d);
    { uint32_t ea_ = (R(31) + 4648); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 4644); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[4].d * ctx->f[10].d);
    { uint32_t ea_ = (f + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[6].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[7].d - ctx->f[3].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[5].d); }
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[9].d); }
    ctx->f[0].d = frsp(ctx->f[0].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[8].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[10].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[11].d); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_80151C00; }
    { uint32_t ea_ = (f + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[10].d);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[1].d); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[1].d);
    if ((CR_BIT(ctx, 2))) { goto L_80151C00; }
    { uint32_t ea_ = (R(2) + -22028); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80151BD4; }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
L_80151BD4:;
    { uint32_t ea_ = (R(2) + -22032); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 15);
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(31) + 4664));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 36); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(3) | 0x42u;
    { uint32_t ea_ = (R(31) + 4656); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 4652); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 4664), R(3));
    st8(base, (R(31) + 4661), R(0));
L_80151C00:;
    R(0) = lr;
}

/* fn_80151C20 (fn_80151C20, 8 bytes) */
static void pf_m_51c20(GM_CTX) {
    R(4) = (0 + 124);
    GM_TAIL(0x80056C70u, 0); return;
}

/* fn_80151C30 (fn_80151C30, 204 bytes) */
static void pf_m_51c30(GM_CTX) {
    GM_FN(0x80151C30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 17);
    R(4) = (f + 72);
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 5336));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x80151C60u, ctx->ctr, 0);
    { uint32_t ea_ = (R(2) + -22044); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 24);
    { uint32_t ea_ = (R(2) + -21984); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    GM_CALLV(0x80151C74u, 0x801C0BD0u, 0);
    R(3) = (f + 72);
    R(4) = (f + 24);
    R(5) = R(3) |R(3);
    GM_CALLV(0x80151C84u, 0x801C0540u, 0);
    R(3) = (f + 72);
    R(4) = (f + 8);
    GM_CALLV(0x80151C90u, 0x8016F130u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 16);
    { uint32_t ea_ = (R(31) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 12); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 16); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22032); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(31) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(31) + 180); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[1].d); }
    R(3) = ld32(base, (R(31) + 4664));
    { uint32_t ea_ = (R(31) + 4644); stfs(base, ea_, ctx->f[4].d); }
    R(3) = R(3) | 0x42u;
    { uint32_t ea_ = (R(31) + 4648); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(31) + 4652); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 4656); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 4664), R(3));
    st8(base, (R(31) + 4661), R(0));
    R(0) = lr;
}

/* fn_80151D00 (fn_80151D00, 324 bytes) */
static void pf_m_51d00(GM_CTX) {
    GM_FN(0x80151D00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x802F0000u);
    R(5) = (R(5) + 22512);
    R(6) = (R(5) + 216);
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 5336));
    R(4) = ld32(base, (R(4) + 352));
    R(0) = R(4) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80151D38; }
    R(6) = (R(5) + 232);
    goto L_80151D44;
L_80151D38:;
    R(0) = R(4) & 0x10u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80151D44; }
    R(6) = (R(5) + 248);
L_80151D44:;
    { uint32_t ea_ = (R(6) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 356); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(3) + 5412));
    { uint32_t ea_ = (R(6) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 360); stfs(base, ea_, ctx->f[0].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (R(3) + 4144); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d * ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 364); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 368); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 208); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 212); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 216); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_80151E30; }
    { uint32_t ea_ = R(3) + 5220; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x80151D9Cu, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 27336);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x80151DB4u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151DC8; }
    R(0) = (0 + 269);
    st32(base, (R(31) + 376), R(0));
    goto L_80151DD0;
L_80151DC8:;
    R(0) = (0 + 265);
    st32(base, (R(31) + 376), R(0));
L_80151DD0:;
    R(0) = ld32(base, (R(31) + 4308));
    R(4) = (0 + 0);
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (0 + 0x400000u);
    { uint32_t ea_ = (R(2) + -21916); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = R(0) & 0x18000000u;
    CR0(ctx, R(0));
    st8(base, (R(31) + 373), R(4));
    st32(base, (R(31) + 380), R(3));
    { uint32_t ea_ = (R(31) + 356); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 360); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_80151E0C; }
    { uint32_t ea_ = (R(2) + -22032); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 364); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 368); stfs(base, ea_, ctx->f[0].d); }
    goto L_80151E1C;
L_80151E0C:;
    { uint32_t ea_ = (R(2) + -22028); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22032); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 364); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 368); stfs(base, ea_, ctx->f[0].d); }
L_80151E1C:;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22028); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 208); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 212); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 216); stfs(base, ea_, ctx->f[1].d); }
L_80151E30:;
    R(0) = lr;
}

/* fn_80151E50 (fn_80151E50, 452 bytes) */
static void pf_m_51e50(GM_CTX) {
    GM_FN(0x80151E50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(30) = ld32(base, (R(3) + 4));
    R(27) = R(4) |R(4);
    R(29) = ld32(base, (R(4) + 4));
    R(3) = ld32(base, (R(30) + 5412));
    R(0) = ld32(base, (R(29) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80151E88; }
    R(3) = (0 + 0);
    goto L_80151FFC;
L_80151E88:;
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x80151E9Cu, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(3) = (int8_t)R(0);
    GM_CALLV(0x80151EA8u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(28) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80151FF8; }
    R(3) = ld8(base, (R(27) + 45));
    R(0) = (R(3) + -19);
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 1))) { goto L_80151FA4; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 7);
    if ((CR_BIT(ctx, 2))) { goto L_80151ED4; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 13);
    if ((!CR_BIT(ctx, 2))) { goto L_80151FF8; }
L_80151ED4:;
    R(12) = ld32(base, (R(28) + 96));
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = (0 + 4);
    R(12) = ld32(base, (R(12) + 1012));
    ctx->ctr = R(12);
    GM_CALLV(0x80151EF0u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151F9C; }
    R(0) = ld8(base, (R(27) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80151F88; }
    R(12) = ld32(base, (R(29) + 96));
    R(3) = R(29) |R(29);
    R(31) = ld32(base, (R(13) + -22136));
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x80151F1Cu, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(0) = ld8(base, (R(4) + 0));
    R(5) = (0 + 4);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    R(4) = (int8_t)R(0);
    GM_CALLV(0x80151F3Cu, 0x800D8BB0u, 0);
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    R(5) = (0 + 0);
    GM_CALLV(0x80151F4Cu, 0x8014EA30u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80151F9C; }
    R(0) = ld8(base, (R(30) + 840));
    R(3) = R(30) |R(30);
    st8(base, (R(29) + 840), R(0));
    R(4) = (0 + 1);
    { uint32_t ea_ = (R(2) + -30776); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (0 + 2);
    R(12) = ld32(base, (R(30) + 96));
    R(6) = (0 + 0);
    { uint32_t ea_ = (R(30) + 268); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(12) + 1020));
    ctx->ctr = R(12);
    GM_CALLV(0x80151F84u, ctx->ctr, 0);
    goto L_80151F9C;
L_80151F88:;
    R(0) = ld8(base, (R(27) + 45));
    cr_cmp_u(ctx, 0, R(0), 0x7u);
    if ((!CR_BIT(ctx, 2))) { goto L_80151F9C; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x80151F9Cu, 0x80048C40u, 0);
L_80151F9C:;
    R(3) = (0 + 1);
    goto L_80151FFC;
L_80151FA4:;
    R(12) = ld32(base, (R(29) + 96));
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x80151FB8u, ctx->ctr, 0);
    R(12) = ld32(base, (R(28) + 96));
    R(0) = ld8(base, (R(3) + 0));
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 108));
    R(31) = (int8_t)R(0);
    ctx->ctr = R(12);
    GM_CALLV(0x80151FD4u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), (int32_t)R(31));
    if ((CR_BIT(ctx, 2))) { goto L_80151FF0; }
    R(4) = ld8(base, (R(27) + 45));
    R(3) = R(28) |R(28);
    GM_CALLV(0x80151FF0u, 0x80141640u, 0);
L_80151FF0:;
    R(3) = (0 + 1);
    goto L_80151FFC;
L_80151FF8:;
    R(3) = (0 + 0);
L_80151FFC:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_80152020 (fn_80152020, 260 bytes) */
static void pf_m_52020(GM_CTX) {
    GM_FN(0x80152020); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(31) = ld32(base, (R(3) + 4));
    R(30) = ld32(base, (R(4) + 4));
    { uint32_t ea_ = (R(31) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80152100; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 77);
    GM_CALLV(0x8015206Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152100; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 4);
    GM_CALLV(0x80152080u, 0x8004DB40u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152100; }
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    GM_CALLV(0x80152098u, 0x80053C80u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152100; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 10);
    GM_CALLV(0x801520ACu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801520E4; }
    { uint32_t ea_ = (R(30) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -22120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_801520E4; }
    { uint32_t ea_ = (R(28) + 112); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    R(4) = (0 + 1);
    GM_CALLV(0x801520D4u, 0x80053E60u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x801520DCu, 0x80053DF0u, 0);
    R(3) = (0 + 1);
    goto L_80152104;
L_801520E4:;
    R(3) = R(31) |R(31);
    R(4) = R(30) |R(30);
    GM_CALLV(0x801520F0u, 0x80049C70u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152100; }
    R(3) = (0 + 1);
    goto L_80152104;
L_80152100:;
    R(3) = (0 + 0);
L_80152104:;
    R(0) = lr;
}

/* fn_80152130 (fn_80152130, 376 bytes) */
static void pf_m_52130(GM_CTX) {
    GM_FN(0x80152130); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(30) = ld32(base, (R(3) + 4));
    R(31) = ld32(base, (R(4) + 4));
    R(0) = ld32(base, (R(30) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152288; }
    R(3) = ld8(base, (R(4) + 44));
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_80152180; }
    R(0) = ld32(base, (R(31) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152288; }
L_80152180:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152190; }
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_801521AC; }
L_80152190:;
    R(0) = ld32(base, (R(31) + 936));
    cr_cmp_u(ctx, 0, R(30), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80152288; }
    R(0) = ld32(base, (R(30) + 936));
    cr_cmp_u(ctx, 0, R(31), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_801521AC; }
    goto L_80152288;
L_801521AC:;
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    GM_CALLV(0x801521B8u, 0x80151E50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152288; }
    R(0) = ld8(base, (R(29) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015223C; }
    R(0) = ld8(base, (R(31) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8015223C; }
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x801521E4u, 0x80047580u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152288; }
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    GM_CALLV(0x801521F8u, 0x80152020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152288; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = (0 + -1);
    R(12) = ld32(base, (R(12) + 232));
    ctx->ctr = R(12);
    GM_CALLV(0x80152218u, ctx->ctr, 0);
    R(4) = (0 + 0x802F0000u);
    R(0) = rotl32(R(3), 2) & 0x3FCu;
    R(4) = (R(4) + 22776);
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (R(4) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    R(6) = (0 + 0);
    GM_CALLV(0x8015223Cu, 0x80053940u, 0);
L_8015223C:;
    R(0) = ld8(base, (R(29) + 44));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_80152288; }
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x80152254u, 0x80047580u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152288; }
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    GM_CALLV(0x80152268u, 0x80152020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152288; }
    { uint32_t ea_ = (R(2) + -22104); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    R(6) = (0 + 2);
    GM_CALLV(0x80152288u, 0x80053940u, 0);
L_80152288:;
    R(0) = lr;
}

/* fn_801522B0 (fn_801522B0, 172 bytes) */
static void pf_m_522b0(GM_CTX) {
    GM_FN(0x801522B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(31) = ld32(base, (R(3) + 4));
    R(3) = R(31) |R(31);
    GM_CALLV(0x801522DCu, 0x8004DD00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152340; }
    R(0) = ld8(base, (R(29) + 45));
    cr_cmp_u(ctx, 0, R(0), 0xFu);
    if ((!CR_BIT(ctx, 2))) { goto L_80152314; }
    R(3) = R(31) |R(31);
    R(4) = R(30) |R(30);
    GM_CALLV(0x801522FCu, 0x801501D0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152314; }
    R(0) = ld8(base, (R(30) + 161));
    R(0) = R(0) | 0x2u;
    st8(base, (R(30) + 161), R(0));
    goto L_80152340;
L_80152314:;
    R(0) = ld8(base, (R(29) + 45));
    cr_cmp_u(ctx, 0, R(0), 0x10u);
    if ((!CR_BIT(ctx, 2))) { goto L_80152340; }
    R(4) = ld32(base, (R(30) + 4));
    R(3) = R(31) |R(31);
    GM_CALLV(0x8015232Cu, 0x801503E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152340; }
    R(0) = ld8(base, (R(30) + 161));
    R(0) = R(0) | 0x2u;
    st8(base, (R(30) + 161), R(0));
L_80152340:;
    R(0) = lr;
}

/* fn_80152360 (fn_80152360, 56 bytes) */
static void pf_m_52360(GM_CTX) {
    GM_FN(0x80152360); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x80152370u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152388; }
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 264));
    ctx->ctr = R(12);
    GM_CALLV(0x80152388u, ctx->ctr, 0);
L_80152388:;
    R(0) = lr;
}

/* fn_801523A0 (fn_801523A0, 56 bytes) */
static void pf_m_523a0(GM_CTX) {
    GM_FN(0x801523A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x801523B0u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801523C8; }
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 268));
    ctx->ctr = R(12);
    GM_CALLV(0x801523C8u, ctx->ctr, 0);
L_801523C8:;
    R(0) = lr;
}

/* fn_801523E0 (fn_801523E0, 88 bytes) */
static void pf_m_523e0(GM_CTX) {
    GM_FN(0x801523E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    GM_CALLV(0x80152400u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152420; }
    R(12) = ld32(base, (R(3) + 96));
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 272));
    ctx->ctr = R(12);
    GM_CALLV(0x80152420u, ctx->ctr, 0);
L_80152420:;
    R(0) = lr;
}

/* getTongueTipMtx__9daYoshi_cFP6mMtx_c (getTongueTipMtx__9daYoshi_cFP6mMtx_c, 152 bytes) */
static void pf_getTongueTipMtx__9daYoshi_cFP6mMtx_c_52480(GM_CTX) {
    GM_FN(0x80152480); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(4) = ld32(base, (R(3) + 5336));
    R(3) = (f + 8);
    GM_CALLV(0x801524A0u, 0x800FF680u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 1);
    { uint32_t ea_ = (R(31) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 52); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 44); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* getMouthMtx__9daYoshi_cFP6mMtx_c (getMouthMtx__9daYoshi_cFP6mMtx_c, 56 bytes) */
static void pf_getMouthMtx__9daYoshi_cFP6mMtx_c_52520(GM_CTX) {
    GM_FN(0x80152520); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 16);
    R(3) = ld32(base, (R(3) + 5336));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x80152544u, ctx->ctr, 0);
    R(0) = lr;
    R(3) = (0 + 1);
}

/* fn_80152560 (fn_80152560, 64 bytes) */
static void pf_m_52560(GM_CTX) {
    GM_FN(0x80152560); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x80152570u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015258C; }
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 980));
    ctx->ctr = R(12);
    GM_CALLV(0x80152588u, ctx->ctr, 0);
    goto L_80152590;
L_8015258C:;
    R(3) = (0 + 0);
L_80152590:;
    R(0) = lr;
}

/* fn_801527A0 (fn_801527A0, 76 bytes) */
static void pf_m_527a0(GM_CTX) {
    GM_FN(0x801527A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld32(base, (R(3) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801527D8; }
    GM_CALLV(0x801527BCu, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801527D8; }
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 288));
    ctx->ctr = R(12);
    GM_CALLV(0x801527D4u, ctx->ctr, 0);
    goto L_801527DC;
L_801527D8:;
    R(3) = (0 + 0);
L_801527DC:;
    R(0) = lr;
}

/* fn_801527F0 (fn_801527F0, 8 bytes) */
static void pf_m_527f0(GM_CTX) {
    R(4) = (0 + 259);
    GM_TAIL(0x80058110u, 0); return;
}

/* fn_80152B30 (fn_80152B30, 236 bytes) */
static void pf_m_52b30(GM_CTX) {
    GM_FN(0x80152B30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    GM_CALLV(0x80152B50u, 0x80050D80u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152B60; }
    R(3) = (0 + 0);
    goto L_80152C04;
L_80152B60:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 141);
    GM_CALLV(0x80152B6Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152B7C; }
    R(3) = (0 + 0);
    goto L_80152C04;
L_80152B7C:;
    R(0) = ld32(base, (R(30) + 5412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152C00; }
    R(3) = ld32(base, (R(30) + 5408));
    GM_CALLV(0x80152B90u, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152BAC; }
    R(0) = ld8(base, (R(3) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_80152BAC; }
    R(4) = R(31) |R(31);
    GM_CALLV(0x80152BACu, 0x801391F0u, 0);
L_80152BAC:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x80152BB4u, 0x8014E9B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152C00; }
    R(0) = ld8(base, (R(3) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_80152C00; }
    R(4) = R(31) |R(31);
    GM_CALLV(0x80152BD0u, 0x801391F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152C00; }
    R(12) = ld32(base, (R(30) + 96));
    R(4) = (0 + 0x80370000u);
    R(3) = R(30) |R(30);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 660));
    R(4) = (R(4) + 27464);
    ctx->ctr = R(12);
    GM_CALLV(0x80152BF8u, ctx->ctr, 0);
    R(3) = (0 + 1);
    goto L_80152C04;
L_80152C00:;
    R(3) = (0 + 0);
L_80152C04:;
    R(0) = lr;
}

/* fn_80152C80 (fn_80152C80, 112 bytes) */
static void pf_m_52c80(GM_CTX) {
    GM_FN(0x80152C80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x80152C98u, 0x8004F260u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152CA8; }
    R(3) = (0 + 0);
    goto L_80152CDC;
L_80152CA8:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 175);
    GM_CALLV(0x80152CB4u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80152CD0; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 179);
    GM_CALLV(0x80152CC8u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80152CD8; }
L_80152CD0:;
    R(3) = (0 + 0);
    goto L_80152CDC;
L_80152CD8:;
    R(3) = (0 + 1);
L_80152CDC:;
    R(0) = lr;
}

/* fn_801531A0 (fn_801531A0, 36 bytes) */
static void pf_m_531a0(GM_CTX) {
    GM_FN(0x801531A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x801531B0u, 0x80056E30u, 0);
    R(0) = lr;
    R(3) = (R(3) + 192);
}

/* fn_80153210 (fn_80153210, 36 bytes) */
static void pf_m_53210(GM_CTX) {
    GM_FN(0x80153210); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x80153220u, 0x801515C0u, 0);
    R(0) = lr;
    R(3) = (R(3) + 16);
}

/* fn_80153240 (fn_80153240, 96 bytes) */
static void pf_m_53240(GM_CTX) {
    GM_FN(0x80153240); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(31) + 0));
    R(12) = ld32(base, (R(12) + 12));
    ctx->ctr = R(12);
    GM_CALLV(0x80153270u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80153284; }
    st32(base, (R(30) + 12), R(31));
    R(3) = (R(30) + 4);
    goto L_80153288;
L_80153284:;
    R(3) = (0 + 0);
L_80153288:;
    R(0) = lr;
}

/* fn_801532A0 (fn_801532A0, 12 bytes) */
static void pf_m_532a0(GM_CTX) {
    R(0) = (0 + 0);
    st32(base, (R(4) + 0), R(0));
}

/* fn_801532B0 (fn_801532B0, 28 bytes) */
static void pf_m_532b0(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 8));
    R(4) = ld32(base, (R(4) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_801532D0 (fn_801532D0, 28 bytes) */
static void pf_m_532d0(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 8));
    R(4) = ld32(base, (R(4) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 44));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_801532F0 (fn_801532F0, 28 bytes) */
static void pf_m_532f0(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 8));
    R(4) = ld32(base, (R(4) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 48));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_80153400 (fn_80153400, 3832 bytes) */
static void pf_m_53400(GM_CTX) {
    GM_FN(0x80153400); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 736);
    R(26) = (0 + 0x80320000u);
    R(27) = (0 + 0x80370000u);
    R(26) = (R(26) + 26376);
    R(3) = (R(26) + 1536);
    R(23) = ld32(base, (R(26) + 1536));
    R(6) = (R(26) + 1548);
    R(5) = (R(26) + 1560);
    R(12) = ld32(base, (R(3) + 4));
    R(27) = (R(27) + 27320);
    R(11) = ld32(base, (R(3) + 8));
    R(4) = (R(26) + 2220);
    R(10) = ld32(base, (R(26) + 1548));
    R(3) = (R(27) + 16);
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(26) + 1560));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 656), R(23));
    st32(base, (f + 660), R(12));
    st32(base, (f + 664), R(11));
    st32(base, (f + 668), R(10));
    st32(base, (f + 672), R(9));
    st32(base, (f + 676), R(8));
    st32(base, (f + 680), R(7));
    st32(base, (f + 684), R(6));
    st32(base, (f + 688), R(0));
    GM_CALLV(0x80153484u, 0x8015F7C0u, 0);
    R(28) = (0 + 0x80320000u);
    R(3) = (R(27) + 16);
    R(23) = ld32(base, (f + 680));
    R(28) = (R(28) + 29168);
    R(12) = ld32(base, (f + 684));
    R(29) = (0 + 0x80150000u);
    R(11) = ld32(base, (f + 688));
    R(4) = (R(29) + 17152);
    R(10) = ld32(base, (f + 668));
    R(5) = (R(27) + 0);
    R(9) = ld32(base, (f + 672));
    R(8) = ld32(base, (f + 676));
    R(7) = ld32(base, (f + 656));
    R(6) = ld32(base, (f + 660));
    R(0) = ld32(base, (f + 664));
    st32(base, (R(27) + 16), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x801534ECu, 0x802DC780u, 0);
    R(3) = (R(26) + 1572);
    R(6) = (R(26) + 1584);
    R(5) = (R(26) + 1596);
    R(23) = ld32(base, (R(26) + 1572));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(26) + 2252);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(27) + 80);
    R(10) = ld32(base, (R(26) + 1584));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(26) + 1596));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 620), R(23));
    st32(base, (f + 624), R(12));
    st32(base, (f + 628), R(11));
    st32(base, (f + 632), R(10));
    st32(base, (f + 636), R(9));
    st32(base, (f + 640), R(8));
    st32(base, (f + 644), R(7));
    st32(base, (f + 648), R(6));
    st32(base, (f + 652), R(0));
    GM_CALLV(0x8015354Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 80);
    R(23) = ld32(base, (f + 644));
    R(12) = ld32(base, (f + 648));
    R(4) = (R(29) + 17152);
    R(11) = ld32(base, (f + 652));
    R(5) = (R(27) + 64);
    R(10) = ld32(base, (f + 632));
    R(9) = ld32(base, (f + 636));
    R(8) = ld32(base, (f + 640));
    R(7) = ld32(base, (f + 620));
    R(6) = ld32(base, (f + 624));
    R(0) = ld32(base, (f + 628));
    st32(base, (R(27) + 80), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x801535A8u, 0x802DC780u, 0);
    R(3) = (R(26) + 1608);
    R(6) = (R(26) + 1620);
    R(5) = (R(26) + 1632);
    R(23) = ld32(base, (R(26) + 1608));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(26) + 2280);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(27) + 144);
    R(10) = ld32(base, (R(26) + 1620));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(26) + 1632));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 584), R(23));
    st32(base, (f + 588), R(12));
    st32(base, (f + 592), R(11));
    st32(base, (f + 596), R(10));
    st32(base, (f + 600), R(9));
    st32(base, (f + 604), R(8));
    st32(base, (f + 608), R(7));
    st32(base, (f + 612), R(6));
    st32(base, (f + 616), R(0));
    GM_CALLV(0x80153608u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 144);
    R(23) = ld32(base, (f + 608));
    R(12) = ld32(base, (f + 612));
    R(4) = (R(29) + 17152);
    R(11) = ld32(base, (f + 616));
    R(5) = (R(27) + 128);
    R(10) = ld32(base, (f + 596));
    R(9) = ld32(base, (f + 600));
    R(8) = ld32(base, (f + 604));
    R(7) = ld32(base, (f + 584));
    R(6) = ld32(base, (f + 588));
    R(0) = ld32(base, (f + 592));
    st32(base, (R(27) + 144), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80153664u, 0x802DC780u, 0);
    R(3) = (R(26) + 1644);
    R(6) = (R(26) + 1656);
    R(5) = (R(26) + 1668);
    R(23) = ld32(base, (R(26) + 1644));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(26) + 2312);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(27) + 208);
    R(10) = ld32(base, (R(26) + 1656));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(26) + 1668));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 548), R(23));
    st32(base, (f + 552), R(12));
    st32(base, (f + 556), R(11));
    st32(base, (f + 560), R(10));
    st32(base, (f + 564), R(9));
    st32(base, (f + 568), R(8));
    st32(base, (f + 572), R(7));
    st32(base, (f + 576), R(6));
    st32(base, (f + 580), R(0));
    GM_CALLV(0x801536C4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 208);
    R(23) = ld32(base, (f + 572));
    R(12) = ld32(base, (f + 576));
    R(4) = (R(29) + 17152);
    R(11) = ld32(base, (f + 580));
    R(5) = (R(27) + 192);
    R(10) = ld32(base, (f + 560));
    R(9) = ld32(base, (f + 564));
    R(8) = ld32(base, (f + 568));
    R(7) = ld32(base, (f + 548));
    R(6) = ld32(base, (f + 552));
    R(0) = ld32(base, (f + 556));
    st32(base, (R(27) + 208), R(28));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80153720u, 0x802DC780u, 0);
    R(5) = (R(26) + 1680);
    R(4) = (R(26) + 1692);
    R(3) = (R(26) + 1704);
    R(11) = ld32(base, (R(26) + 1680));
    R(10) = ld32(base, (R(5) + 4));
    R(30) = (R(26) + 2344);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 1692));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 1704));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 512), R(11));
    st32(base, (f + 516), R(10));
    st32(base, (f + 520), R(9));
    st32(base, (f + 524), R(8));
    st32(base, (f + 528), R(7));
    st32(base, (f + 532), R(6));
    st32(base, (f + 536), R(5));
    st32(base, (f + 540), R(4));
    st32(base, (f + 544), R(0));
    GM_CALLV(0x8015377Cu, 0x80154460u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(30) |R(30);
    R(3) = (R(27) + 268);
    GM_CALLV(0x8015378Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 268);
    R(23) = ld32(base, (f + 536));
    R(12) = ld32(base, (f + 540));
    R(30) = (0 + 0x80320000u);
    R(11) = ld32(base, (f + 544));
    R(30) = (R(30) + 29116);
    R(10) = ld32(base, (f + 524));
    R(31) = (0 + 0x80150000u);
    R(9) = ld32(base, (f + 528));
    R(4) = (R(31) + 17248);
    R(8) = ld32(base, (f + 532));
    R(5) = (R(27) + 256);
    R(7) = ld32(base, (f + 512));
    R(6) = ld32(base, (f + 516));
    R(0) = ld32(base, (f + 520));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 268), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x801537F8u, 0x802DC780u, 0);
    R(5) = (R(26) + 1716);
    R(4) = (R(26) + 1728);
    R(3) = (R(26) + 1740);
    R(11) = ld32(base, (R(26) + 1716));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2368);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 1728));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 1740));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 476), R(11));
    st32(base, (f + 480), R(10));
    st32(base, (f + 484), R(9));
    st32(base, (f + 488), R(8));
    st32(base, (f + 492), R(7));
    st32(base, (f + 496), R(6));
    st32(base, (f + 500), R(5));
    st32(base, (f + 504), R(4));
    st32(base, (f + 508), R(0));
    GM_CALLV(0x80153854u, 0x80154450u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 332);
    GM_CALLV(0x80153864u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 332);
    R(23) = ld32(base, (f + 500));
    R(12) = ld32(base, (f + 504));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 508));
    R(5) = (R(27) + 320);
    R(10) = ld32(base, (f + 488));
    R(9) = ld32(base, (f + 492));
    R(8) = ld32(base, (f + 496));
    R(7) = ld32(base, (f + 476));
    R(6) = ld32(base, (f + 480));
    R(0) = ld32(base, (f + 484));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 332), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x801538C4u, 0x802DC780u, 0);
    R(5) = (R(26) + 1752);
    R(4) = (R(26) + 1764);
    R(3) = (R(26) + 1776);
    R(11) = ld32(base, (R(26) + 1752));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2392);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 1764));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 1776));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 440), R(11));
    st32(base, (f + 444), R(10));
    st32(base, (f + 448), R(9));
    st32(base, (f + 452), R(8));
    st32(base, (f + 456), R(7));
    st32(base, (f + 460), R(6));
    st32(base, (f + 464), R(5));
    st32(base, (f + 468), R(4));
    st32(base, (f + 472), R(0));
    GM_CALLV(0x80153920u, 0x80154440u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 396);
    GM_CALLV(0x80153930u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 396);
    R(23) = ld32(base, (f + 464));
    R(12) = ld32(base, (f + 468));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 472));
    R(5) = (R(27) + 384);
    R(10) = ld32(base, (f + 452));
    R(9) = ld32(base, (f + 456));
    R(8) = ld32(base, (f + 460));
    R(7) = ld32(base, (f + 440));
    R(6) = ld32(base, (f + 444));
    R(0) = ld32(base, (f + 448));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 396), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80153990u, 0x802DC780u, 0);
    R(5) = (R(26) + 1788);
    R(4) = (R(26) + 1800);
    R(3) = (R(26) + 1812);
    R(11) = ld32(base, (R(26) + 1788));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2416);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 1800));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 1812));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 404), R(11));
    st32(base, (f + 408), R(10));
    st32(base, (f + 412), R(9));
    st32(base, (f + 416), R(8));
    st32(base, (f + 420), R(7));
    st32(base, (f + 424), R(6));
    st32(base, (f + 428), R(5));
    st32(base, (f + 432), R(4));
    st32(base, (f + 436), R(0));
    GM_CALLV(0x801539ECu, 0x80154430u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 460);
    GM_CALLV(0x801539FCu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 460);
    R(23) = ld32(base, (f + 428));
    R(12) = ld32(base, (f + 432));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 436));
    R(5) = (R(27) + 448);
    R(10) = ld32(base, (f + 416));
    R(9) = ld32(base, (f + 420));
    R(8) = ld32(base, (f + 424));
    R(7) = ld32(base, (f + 404));
    R(6) = ld32(base, (f + 408));
    R(0) = ld32(base, (f + 412));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 460), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80153A5Cu, 0x802DC780u, 0);
    R(5) = (R(26) + 1824);
    R(4) = (R(26) + 1836);
    R(3) = (R(26) + 1848);
    R(11) = ld32(base, (R(26) + 1824));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2440);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 1836));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 1848));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 368), R(11));
    st32(base, (f + 372), R(10));
    st32(base, (f + 376), R(9));
    st32(base, (f + 380), R(8));
    st32(base, (f + 384), R(7));
    st32(base, (f + 388), R(6));
    st32(base, (f + 392), R(5));
    st32(base, (f + 396), R(4));
    st32(base, (f + 400), R(0));
    GM_CALLV(0x80153AB8u, 0x80154420u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 524);
    GM_CALLV(0x80153AC8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 524);
    R(23) = ld32(base, (f + 392));
    R(12) = ld32(base, (f + 396));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 400));
    R(5) = (R(27) + 512);
    R(10) = ld32(base, (f + 380));
    R(9) = ld32(base, (f + 384));
    R(8) = ld32(base, (f + 388));
    R(7) = ld32(base, (f + 368));
    R(6) = ld32(base, (f + 372));
    R(0) = ld32(base, (f + 376));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 524), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80153B28u, 0x802DC780u, 0);
    R(5) = (R(26) + 1860);
    R(4) = (R(26) + 1872);
    R(3) = (R(26) + 1884);
    R(11) = ld32(base, (R(26) + 1860));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2468);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 1872));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 1884));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 332), R(11));
    st32(base, (f + 336), R(10));
    st32(base, (f + 340), R(9));
    st32(base, (f + 344), R(8));
    st32(base, (f + 348), R(7));
    st32(base, (f + 352), R(6));
    st32(base, (f + 356), R(5));
    st32(base, (f + 360), R(4));
    st32(base, (f + 364), R(0));
    GM_CALLV(0x80153B84u, 0x80154410u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 588);
    GM_CALLV(0x80153B94u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 588);
    R(23) = ld32(base, (f + 356));
    R(12) = ld32(base, (f + 360));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 364));
    R(5) = (R(27) + 576);
    R(10) = ld32(base, (f + 344));
    R(9) = ld32(base, (f + 348));
    R(8) = ld32(base, (f + 352));
    R(7) = ld32(base, (f + 332));
    R(6) = ld32(base, (f + 336));
    R(0) = ld32(base, (f + 340));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 588), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80153BF4u, 0x802DC780u, 0);
    R(5) = (R(26) + 1896);
    R(4) = (R(26) + 1908);
    R(3) = (R(26) + 1920);
    R(11) = ld32(base, (R(26) + 1896));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2496);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 1908));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 1920));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 296), R(11));
    st32(base, (f + 300), R(10));
    st32(base, (f + 304), R(9));
    st32(base, (f + 308), R(8));
    st32(base, (f + 312), R(7));
    st32(base, (f + 316), R(6));
    st32(base, (f + 320), R(5));
    st32(base, (f + 324), R(4));
    st32(base, (f + 328), R(0));
    GM_CALLV(0x80153C50u, 0x80154400u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 652);
    GM_CALLV(0x80153C60u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 652);
    R(23) = ld32(base, (f + 320));
    R(12) = ld32(base, (f + 324));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 328));
    R(5) = (R(27) + 640);
    R(10) = ld32(base, (f + 308));
    R(9) = ld32(base, (f + 312));
    R(8) = ld32(base, (f + 316));
    R(7) = ld32(base, (f + 296));
    R(6) = ld32(base, (f + 300));
    R(0) = ld32(base, (f + 304));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 652), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80153CC0u, 0x802DC780u, 0);
    R(5) = (R(26) + 1932);
    R(4) = (R(26) + 1944);
    R(3) = (R(26) + 1956);
    R(11) = ld32(base, (R(26) + 1932));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2520);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 1944));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 1956));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 260), R(11));
    st32(base, (f + 264), R(10));
    st32(base, (f + 268), R(9));
    st32(base, (f + 272), R(8));
    st32(base, (f + 276), R(7));
    st32(base, (f + 280), R(6));
    st32(base, (f + 284), R(5));
    st32(base, (f + 288), R(4));
    st32(base, (f + 292), R(0));
    GM_CALLV(0x80153D1Cu, 0x801543F0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 716);
    GM_CALLV(0x80153D2Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 716);
    R(23) = ld32(base, (f + 284));
    R(12) = ld32(base, (f + 288));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 292));
    R(5) = (R(27) + 704);
    R(10) = ld32(base, (f + 272));
    R(9) = ld32(base, (f + 276));
    R(8) = ld32(base, (f + 280));
    R(7) = ld32(base, (f + 260));
    R(6) = ld32(base, (f + 264));
    R(0) = ld32(base, (f + 268));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 716), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80153D8Cu, 0x802DC780u, 0);
    R(5) = (R(26) + 1968);
    R(4) = (R(26) + 1980);
    R(3) = (R(26) + 1992);
    R(11) = ld32(base, (R(26) + 1968));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2544);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 1980));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 1992));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 224), R(11));
    st32(base, (f + 228), R(10));
    st32(base, (f + 232), R(9));
    st32(base, (f + 236), R(8));
    st32(base, (f + 240), R(7));
    st32(base, (f + 244), R(6));
    st32(base, (f + 248), R(5));
    st32(base, (f + 252), R(4));
    st32(base, (f + 256), R(0));
    GM_CALLV(0x80153DE8u, 0x801543E0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 780);
    GM_CALLV(0x80153DF8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 780);
    R(23) = ld32(base, (f + 248));
    R(12) = ld32(base, (f + 252));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 256));
    R(5) = (R(27) + 768);
    R(10) = ld32(base, (f + 236));
    R(9) = ld32(base, (f + 240));
    R(8) = ld32(base, (f + 244));
    R(7) = ld32(base, (f + 224));
    R(6) = ld32(base, (f + 228));
    R(0) = ld32(base, (f + 232));
    st32(base, (R(3) + 12), R(23));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 780), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80153E58u, 0x802DC780u, 0);
    R(5) = (R(26) + 2004);
    R(4) = (R(26) + 2016);
    R(3) = (R(26) + 2028);
    R(11) = ld32(base, (R(26) + 2004));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2576);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 2016));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 2028));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 188), R(11));
    st32(base, (f + 192), R(10));
    st32(base, (f + 196), R(9));
    st32(base, (f + 200), R(8));
    st32(base, (f + 204), R(7));
    st32(base, (f + 208), R(6));
    st32(base, (f + 212), R(5));
    st32(base, (f + 216), R(4));
    st32(base, (f + 220), R(0));
    GM_CALLV(0x80153EB4u, 0x801543D0u, 0);
    R(23) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 844);
    GM_CALLV(0x80153EC4u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 844);
    R(24) = ld32(base, (f + 212));
    R(12) = ld32(base, (f + 216));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 220));
    R(5) = (R(27) + 832);
    R(10) = ld32(base, (f + 200));
    R(9) = ld32(base, (f + 204));
    R(8) = ld32(base, (f + 208));
    R(7) = ld32(base, (f + 188));
    R(6) = ld32(base, (f + 192));
    R(0) = ld32(base, (f + 196));
    st32(base, (R(3) + 12), R(24));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 844), R(30));
    st32(base, (R(3) + 48), R(23));
    GM_CALLV(0x80153F24u, 0x802DC780u, 0);
    R(5) = (R(26) + 2040);
    R(4) = (R(26) + 2052);
    R(3) = (R(26) + 2064);
    R(11) = ld32(base, (R(26) + 2040));
    R(10) = ld32(base, (R(5) + 4));
    R(25) = (R(26) + 2604);
    R(9) = ld32(base, (R(5) + 8));
    R(8) = ld32(base, (R(26) + 2052));
    R(7) = ld32(base, (R(4) + 4));
    R(6) = ld32(base, (R(4) + 8));
    R(5) = ld32(base, (R(26) + 2064));
    R(4) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (f + 152), R(11));
    st32(base, (f + 156), R(10));
    st32(base, (f + 160), R(9));
    st32(base, (f + 164), R(8));
    st32(base, (f + 168), R(7));
    st32(base, (f + 172), R(6));
    st32(base, (f + 176), R(5));
    st32(base, (f + 180), R(4));
    st32(base, (f + 184), R(0));
    GM_CALLV(0x80153F80u, 0x801543C0u, 0);
    R(24) = R(3) |R(3);
    R(4) = R(25) |R(25);
    R(3) = (R(27) + 908);
    GM_CALLV(0x80153F90u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 908);
    R(25) = ld32(base, (f + 176));
    R(12) = ld32(base, (f + 180));
    R(4) = (R(31) + 17248);
    R(11) = ld32(base, (f + 184));
    R(5) = (R(27) + 896);
    R(10) = ld32(base, (f + 164));
    R(9) = ld32(base, (f + 168));
    R(8) = ld32(base, (f + 172));
    R(7) = ld32(base, (f + 152));
    R(6) = ld32(base, (f + 156));
    R(0) = ld32(base, (f + 160));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    st32(base, (R(27) + 908), R(30));
    st32(base, (R(3) + 48), R(24));
    GM_CALLV(0x80153FF0u, 0x802DC780u, 0);
    R(3) = (R(26) + 2076);
    R(6) = (R(26) + 2088);
    R(5) = (R(26) + 2100);
    R(25) = ld32(base, (R(26) + 2076));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(26) + 2632);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(27) + 976);
    R(10) = ld32(base, (R(26) + 2088));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(26) + 2100));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 116), R(25));
    st32(base, (f + 120), R(12));
    st32(base, (f + 124), R(11));
    st32(base, (f + 128), R(10));
    st32(base, (f + 132), R(9));
    st32(base, (f + 136), R(8));
    st32(base, (f + 140), R(7));
    st32(base, (f + 144), R(6));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x80154050u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 976);
    R(25) = ld32(base, (f + 140));
    R(12) = ld32(base, (f + 144));
    R(4) = (R(29) + 17152);
    R(11) = ld32(base, (f + 148));
    R(5) = (R(27) + 960);
    R(10) = ld32(base, (f + 128));
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(27) + 976), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x801540ACu, 0x802DC780u, 0);
    R(3) = (R(26) + 2112);
    R(6) = (R(26) + 2124);
    R(5) = (R(26) + 2136);
    R(25) = ld32(base, (R(26) + 2112));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(26) + 2660);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(27) + 1040);
    R(10) = ld32(base, (R(26) + 2124));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(26) + 2136));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 80), R(25));
    st32(base, (f + 84), R(12));
    st32(base, (f + 88), R(11));
    st32(base, (f + 92), R(10));
    st32(base, (f + 96), R(9));
    st32(base, (f + 100), R(8));
    st32(base, (f + 104), R(7));
    st32(base, (f + 108), R(6));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x8015410Cu, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1040);
    R(25) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(29) + 17152);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(27) + 1024);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(27) + 1040), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80154168u, 0x802DC780u, 0);
    R(3) = (R(26) + 2148);
    R(6) = (R(26) + 2160);
    R(5) = (R(26) + 2172);
    R(25) = ld32(base, (R(26) + 2148));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(26) + 2684);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(27) + 1104);
    R(10) = ld32(base, (R(26) + 2160));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(26) + 2172));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 44), R(25));
    st32(base, (f + 48), R(12));
    st32(base, (f + 52), R(11));
    st32(base, (f + 56), R(10));
    st32(base, (f + 60), R(9));
    st32(base, (f + 64), R(8));
    st32(base, (f + 68), R(7));
    st32(base, (f + 72), R(6));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x801541C8u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1104);
    R(25) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(29) + 17152);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(27) + 1088);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(27) + 1104), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80154224u, 0x802DC780u, 0);
    R(3) = (R(26) + 2184);
    R(6) = (R(26) + 2196);
    R(5) = (R(26) + 2208);
    R(25) = ld32(base, (R(26) + 2184));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(26) + 2712);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(27) + 1168);
    R(10) = ld32(base, (R(26) + 2196));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(26) + 2208));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 8), R(25));
    st32(base, (f + 12), R(12));
    st32(base, (f + 16), R(11));
    st32(base, (f + 20), R(10));
    st32(base, (f + 24), R(9));
    st32(base, (f + 28), R(8));
    st32(base, (f + 32), R(7));
    st32(base, (f + 36), R(6));
    st32(base, (f + 40), R(0));
    GM_CALLV(0x80154284u, 0x8015F7C0u, 0);
    R(3) = (R(27) + 1168);
    R(25) = ld32(base, (f + 32));
    R(12) = ld32(base, (f + 36));
    R(4) = (R(29) + 17152);
    R(11) = ld32(base, (f + 40));
    R(5) = (R(27) + 1152);
    R(10) = ld32(base, (f + 20));
    R(9) = ld32(base, (f + 24));
    R(8) = ld32(base, (f + 28));
    R(7) = ld32(base, (f + 8));
    R(6) = ld32(base, (f + 12));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(27) + 1168), R(28));
    st32(base, (R(3) + 12), R(25));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x801542E0u, 0x802DC780u, 0);
    R(11) = (f + 736);
    R(0) = lr;
}

/* fn_801543C0 (fn_801543C0, 12 bytes) */
static void pf_m_543c0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17884);
}

/* fn_801543D0 (fn_801543D0, 12 bytes) */
static void pf_m_543d0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17756);
}

/* fn_801543E0 (fn_801543E0, 12 bytes) */
static void pf_m_543e0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17500);
}

/* fn_801543F0 (fn_801543F0, 12 bytes) */
static void pf_m_543f0(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17436);
}

/* fn_80154400 (fn_80154400, 12 bytes) */
static void pf_m_54400(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17372);
}

/* fn_80154410 (fn_80154410, 12 bytes) */
static void pf_m_54410(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17116);
}

/* fn_80154420 (fn_80154420, 12 bytes) */
static void pf_m_54420(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17308);
}

/* fn_80154430 (fn_80154430, 12 bytes) */
static void pf_m_54430(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17244);
}

/* fn_80154440 (fn_80154440, 12 bytes) */
static void pf_m_54440(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17180);
}

/* fn_80154450 (fn_80154450, 12 bytes) */
static void pf_m_54450(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 17052);
}

/* fn_80154460 (fn_80154460, 12 bytes) */
static void pf_m_54460(GM_CTX) {
    R(3) = (0 + 0x80350000u);
    R(3) = (R(3) + 16988);
}

/* fn_801546C0 (fn_801546C0, 128 bytes) */
static void pf_m_546c0(GM_CTX) {
    GM_FN(0x801546C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x90000u);
    R(3) = (R(3) + 3044);
    GM_CALLV(0x801546DCu, 0x801628C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80154728; }
    GM_CALLV(0x801546ECu, 0x80077060u, 0);
    R(4) = (0 + 0x80320000u);
    R(3) = (R(31) + 0x90000u);
    R(4) = (R(4) + 29256);
    st32(base, (R(31) + 96), R(4));
    R(3) = (R(3) + 2732);
    GM_CALLV(0x80154704u, 0x800D85D0u, 0);
    R(3) = (R(31) + 0x90000u);
    R(3) = (R(3) + 2752);
    GM_CALLV(0x80154710u, 0x80089150u, 0);
    R(3) = (R(31) + 0x90000u);
    R(3) = (R(3) + 2912);
    GM_CALLV(0x8015471Cu, 0x8007E180u, 0);
    R(3) = (R(31) + 0x90000u);
    R(3) = (R(3) + 2980);
    GM_CALLV(0x80154728u, 0x800CD390u, 0);
L_80154728:;
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_80154740 (fn_80154740, 348 bytes) */
static void pf_m_54740(GM_CTX) {
    GM_FN(0x80154740); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x8015475Cu, 0x80076FD0u, 0);
    R(0) = ld8(base, (R(13) + -21604));
    R(4) = ld32(base, (R(13) + -21688));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    R(3) = ld32(base, (R(13) + -22208));
    if ((!CR_BIT(ctx, 2))) { goto L_80154788; }
    R(0) = ld32(base, (R(3) + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_80154788; }
    R(3) = ld32(base, (R(13) + -22672));
    R(4) = ld8(base, (R(4) + 4622));
    GM_CALLV(0x80154788u, 0x80081780u, 0);
L_80154788:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x80154790u, 0x801548A0u, 0);
    R(31) = (0 + 0);
L_80154794:;
    R(3) = R(30) |R(30);
    R(4) = R(31) & 0xFFFFu;
    R(5) = (0 + 1);
    GM_CALLV(0x801547A4u, 0x80154A70u, 0);
    R(31) = (R(31) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80154794; }
    R(3) = (R(30) + 0x90000u);
    R(31) = (0 + 0);
    st8(base, (R(3) + 292), R(31));
    R(3) = R(30) |R(30);
    GM_CALLV(0x801547C4u, 0x80077A00u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x801547CCu, 0x80077B40u, 0);
    R(3) = (R(30) + 0x90000u);
    R(3) = (R(3) + 2980);
    GM_CALLV(0x801547D8u, 0x800CD470u, 0);
    R(3) = (R(30) + 0x90000u);
    R(3) = (R(3) + 2980);
    GM_CALLV(0x801547E4u, 0x800CD520u, 0);
    { uint32_t ea_ = (R(2) + -21904); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (f + 8);
    { uint32_t ea_ = (R(2) + -21900); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 125);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    R(4) = (0 + 511);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80154810u, 0x80064610u, 0);
    { uint32_t ea_ = (R(2) + -21896); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (f + 8);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (0 + 125);
    R(4) = (0 + 767);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x80154830u, 0x80064610u, 0);
    R(3) = (R(30) + 0x90000u);
    R(3) = (R(3) + 2732);
    GM_CALLV(0x8015483Cu, 0x800D8640u, 0);
    R(3) = (R(30) + 0x90000u);
    R(3) = (R(3) + 2752);
    GM_CALLV(0x80154848u, 0x800892F0u, 0);
    R(3) = (R(30) + 0x90000u);
    R(3) = (R(3) + 2912);
    GM_CALLV(0x80154854u, 0x8007E2C0u, 0);
    R(3) = (R(30) + 0x90000u);
    R(3) = (R(3) + 2912);
    GM_CALLV(0x80154860u, 0x8007E3D0u, 0);
    R(4) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -21904); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    st32(base, (R(4) + 3028), R(0));
    R(3) = (0 + 1);
    { uint32_t ea_ = (R(4) + 3036); stfs(base, ea_, ctx->f[0].d); }
    st16(base, (R(4) + 2504), R(31));
    st16(base, (R(4) + 3040), R(31));
    st8(base, (R(4) + 2508), R(31));
    R(0) = lr;
}

/* fn_801548A0 (fn_801548A0, 464 bytes) */
static void pf_m_548a0(GM_CTX) {
    GM_FN(0x801548A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(13) + -21688));
    R(3) = ld32(base, (R(13) + -22504));
    R(0) = ld8(base, (R(4) + 4622));
    R(29) = ld32(base, (R(13) + -22656));
    R(0) = ((int32_t)R(0) * 944);
    R(30) = R(3) + R(0);
    R(0) = ld32(base, (R(30) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801548F8; }
    goto L_801548FC;
L_801548F8:;
    R(30) = (0 + 0);
L_801548FC:;
    R(28) = ld8(base, (R(4) + 4623));
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (R(13) + -21908); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -21904); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(4) = R(28) |R(28);
    GM_CALLV(0x80154914u, 0x8008E530u, 0);
    R(5) = (R(31) + 0x90000u);
    R(4) = R(28) |R(28);
    st8(base, (R(5) + 254), R(3));
    R(3) = R(30) |R(30);
    GM_CALLV(0x80154928u, 0x8008E560u, 0);
    R(5) = (R(31) + 0x90000u);
    R(4) = R(28) |R(28);
    st8(base, (R(5) + 255), R(3));
    R(3) = R(30) |R(30);
    GM_CALLV(0x8015493Cu, 0x8008E590u, 0);
    R(4) = (R(31) + 0x90000u);
    st8(base, (R(4) + 256), R(3));
    R(3) = R(31) |R(31);
    GM_CALLV(0x8015494Cu, 0x80078EB0u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 152); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8015495Cu, 0x80078EB0u, 0);
    { uint32_t ea_ = (R(2) + -21892); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(2) + -21888); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d / ctx->f[1].d);
    R(4) = R(28) |R(28);
    { uint32_t ea_ = (R(5) + 12); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d / ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[1].d);
    { uint32_t ea_ = (R(29) + 64); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(5) + 12); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d / ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[30].d * ctx->f[2].d);
    { uint32_t ea_ = (R(29) + 68); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    { uint32_t ea_ = (R(29) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[1].d);
    { uint32_t ea_ = (R(29) + 72); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(29) + 76); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x801549B8u, 0x8008E4D0u, 0);
    R(0) = R(3) |R(3);
    R(3) = R(30) |R(30);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x801549C8u, 0x8008E500u, 0);
    R(5) = (R(31) + 0x90000u);
    R(4) = R(28) |R(28);
    st8(base, (R(5) + 257), R(3));
    R(3) = R(30) |R(30);
    GM_CALLV(0x801549DCu, 0x8008E4D0u, 0);
    R(0) = R(3) |R(3);
    R(3) = R(30) |R(30);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x801549ECu, 0x8008E710u, 0);
    R(5) = (R(31) + 0x90000u);
    R(4) = R(28) |R(28);
    st8(base, (R(5) + 258), R(3));
    R(3) = R(30) |R(30);
    GM_CALLV(0x80154A00u, 0x8008E4D0u, 0);
    R(0) = R(3) |R(3);
    R(3) = R(30) |R(30);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x80154A10u, 0x8008E710u, 0);
    R(4) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(2) + -21884); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st8(base, (R(4) + 259), R(3));
    { uint32_t ea_ = (R(2) + -21904); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(3) + 88); stfs(base, ea_, ctx->f[1].d); }
    R(3) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[1].d); }
    R(3) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[0].d); }
    R(3) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_80154A70 (fn_80154A70, 648 bytes) */
static void pf_m_54a70(GM_CTX) {
    GM_FN(0x80154A70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(13) + -21688));
    R(3) = ld32(base, (R(13) + -22504));
    R(0) = ld8(base, (R(4) + 4622));
    R(0) = ((int32_t)R(0) * 944);
    R(3) = R(3) + R(0);
    R(0) = ld32(base, (R(3) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80154AB8; }
    goto L_80154ABC;
L_80154AB8:;
    R(3) = (0 + 0);
L_80154ABC:;
    R(4) = ld8(base, (R(4) + 4623));
    R(5) = (f + 8);
    GM_CALLV(0x80154AC8u, 0x8008E410u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80154B04; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -412); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -408); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -404); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -400); stfs(base, ea_, ctx->f[0].d); }
L_80154B04:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x80154B0Cu, 0x800789A0u, 0);
    ctx->f[31].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x80154B18u, 0x80078B40u, 0);
    R(4) = (R(31) + 0x90000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[31].d);
    { uint32_t ea_ = (R(4) + -400); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + -404); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -412); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -408); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (R(4) + -352); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + -348); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(4) + 56); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 60); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 64); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 68); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(4) + 72); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 76); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 80); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 84); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(4) + 88); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 92); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(13) + -21908); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    GM_CALLV(0x80154B78u, 0x800789A0u, 0);
    ctx->f[31].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x80154B84u, 0x80078B40u, 0);
    R(3) = (R(31) + 0x90000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[31].d);
    { uint32_t ea_ = (R(3) + -400); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -404); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[0].d / ctx->f[30].d);
    { uint32_t ea_ = (R(13) + -21904); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[3].d);
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80154BB0; }
    goto L_80154BB4;
L_80154BB0:;
    ctx->f[4].u = ctx->f[0].u;
L_80154BB4:;
    { uint32_t ea_ = (R(2) + -21880); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80154BC4; }
    ctx->f[4].u = ctx->f[0].u;
L_80154BC4:;
    { uint32_t ea_ = (R(2) + -21872); ctx->f[0].u = ld64(base, ea_); }
    R(4) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(4) + 258));
    ctx->f[1].d = ctx->f[0].d / ctx->f[4].d;
    { uint32_t ea_ = (R(2) + -21892); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 24); stfs(base, ea_, ctx->f[0].d); }
    cr_cmp_u(ctx, 0, R(0), 0x7u);
    ctx->f[0].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (R(4) + 40); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 1))) { goto L_80154CA0; }
    R(3) = (0 + 0x80320000u);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = (R(3) + 29224);
    R(3) = ld32(base, (R(3) + R(0)));
    ctx->ctr = R(3);
    { switch (ctx->ctr) { case 0x80154C04u: goto L_80154C04; case 0x80154C18u: goto L_80154C18; case 0x80154C2Cu: goto L_80154C2C; case 0x80154C40u: goto L_80154C40; case 0x80154C54u: goto L_80154C54; case 0x80154C68u: goto L_80154C68; case 0x80154C7Cu: goto L_80154C7C; case 0x80154C90u: goto L_80154C90; default: rt_fatal("80154A70: jump table target %08X", ctx->ctr); return; } }
L_80154C04:;
    R(3) = (0 + 0);
    R(0) = (0 + 3);
    st8(base, (R(4) + 121), R(3));
    st8(base, (R(4) + 122), R(0));
    goto L_80154CA0;
L_80154C18:;
    R(3) = (0 + 0);
    R(0) = (0 + 1);
    st8(base, (R(4) + 121), R(3));
    st8(base, (R(4) + 122), R(0));
    goto L_80154CA0;
L_80154C2C:;
    R(3) = (0 + 2);
    R(0) = (0 + 3);
    st8(base, (R(4) + 121), R(3));
    st8(base, (R(4) + 122), R(0));
    goto L_80154CA0;
L_80154C40:;
    R(3) = (0 + 2);
    R(0) = (0 + 1);
    st8(base, (R(4) + 121), R(3));
    st8(base, (R(4) + 122), R(0));
    goto L_80154CA0;
L_80154C54:;
    R(3) = (0 + 3);
    R(0) = (0 + 0);
    st8(base, (R(4) + 121), R(3));
    st8(base, (R(4) + 122), R(0));
    goto L_80154CA0;
L_80154C68:;
    R(3) = (0 + 3);
    R(0) = (0 + 2);
    st8(base, (R(4) + 121), R(3));
    st8(base, (R(4) + 122), R(0));
    goto L_80154CA0;
L_80154C7C:;
    R(3) = (0 + 1);
    R(0) = (0 + 0);
    st8(base, (R(4) + 121), R(3));
    st8(base, (R(4) + 122), R(0));
    goto L_80154CA0;
L_80154C90:;
    R(3) = (0 + 1);
    R(0) = (0 + 2);
    st8(base, (R(4) + 121), R(3));
    st8(base, (R(4) + 122), R(0));
L_80154CA0:;
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 0);
    st8(base, (R(3) + 44), R(0));
    R(3) = R(31) |R(31);
    GM_CALLV(0x80154CB4u, 0x80077B00u, 0);
    R(4) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(2) + -21864); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -316); stfs(base, ea_, ctx->f[0].d); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + -312); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80154CCCu, 0x8007BEF0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80154CD4u, 0x80079B60u, 0);
    R(0) = lr;
}

/* fn_80154D00 (fn_80154D00, 72 bytes) */
static void pf_m_54d00(GM_CTX) {
    GM_FN(0x80154D00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = (R(3) + 0x90000u);
    R(3) = (R(3) + 2732);
    GM_CALLV(0x80154D20u, 0x800D8780u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80154D28u, 0x80077D80u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80154D30u, 0x80077020u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_80154D50 (fn_80154D50, 244 bytes) */
static void pf_m_54d50(GM_CTX) {
    GM_FN(0x80154D50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = R(3) |R(3);
    R(3) = (R(3) + 0x90000u);
    R(3) = (R(3) + 2980);
    GM_CALLV(0x80154D7Cu, 0x800CD600u, 0);
    R(3) = (R(28) + 0x90000u);
    R(3) = (R(3) + 2640);
    GM_CALLV(0x80154D88u, 0x800878D0u, 0);
    R(30) = R(28) |R(28);
    R(29) = (0 + 0);
    R(31) = (0 + 1);
L_80154D94:;
    R(3) = (R(30) + 0x90000u);
    R(4) = ld32(base, (R(3) + 2624));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80154DBC; }
    st8(base, (R(4) + 54), R(31));
    R(3) = ld32(base, (R(3) + 2624));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x80154DBCu, ctx->ctr, 0);
L_80154DBC:;
    R(29) = (R(29) + 1);
    R(30) = (R(30) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 3);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80154D94; }
    GM_CALLV(0x80154DD0u, 0x800CD2C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80154DF8; }
    R(3) = (R(28) + 0x90000u);
    R(3) = ld32(base, (R(3) + 2636));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80154DF8; }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x80154DF8u, ctx->ctr, 0);
L_80154DF8:;
    R(3) = (R(28) + 0x90000u);
    R(3) = (R(3) + 2752);
    GM_CALLV(0x80154E04u, 0x80089B80u, 0);
    R(3) = (R(28) + 0x90000u);
    R(3) = (R(3) + 2980);
    GM_CALLV(0x80154E10u, 0x800CD610u, 0);
    R(4) = (R(28) + 0x90000u);
    R(0) = (0 + 0);
    st32(base, (R(4) + 3032), R(0));
    R(3) = (0 + 1);
    st8(base, (R(4) + 3042), R(0));
    R(0) = lr;
}

/* fn_80156930 (fn_80156930, 372 bytes) */
static void pf_m_56930(GM_CTX) {
    GM_FN(0x80156930); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(24) = R(3) |R(3);
    R(25) = R(4) |R(4);
    R(30) = R(5) |R(5);
    R(31) = R(6) |R(6);
    GM_CALLV(0x80156968u, 0x801568D0u, 0);
    { uint32_t ea_ = (R(2) + -21884); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(29) = R(3) |R(3);
    { uint32_t ea_ = (R(2) + -21720); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(27) = (0 + 0);
    R(28) = (0 + 0);
    R(26) = (0 + 0);
L_80156980:;
    R(3) = R(24) |R(24);
    R(4) = R(26) |R(26);
    GM_CALLV(0x8015698Cu, 0x80156820u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801569EC; }
    { uint32_t ea_ = (R(3) + 5420); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 5424); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 5428); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[1].d); }
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_801569EC; }
    { uint32_t ea_ = (R(25) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_801569EC; }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[31].d);
    R(28) = (R(28) + 1);
    if ((!CR_BIT(ctx, 1))) { goto L_801569DC; }
    ctx->f[31].u = ctx->f[2].u;
L_801569DC:;
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[30].d);
    if ((!CR_BIT(ctx, 0))) { goto L_801569EC; }
    ctx->f[30].u = ctx->f[0].u;
L_801569EC:;
    R(26) = (R(26) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(26), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80156980; }
    R(3) = ld16(base, (R(25) + 64));
    R(0) = R(3) & 0x1000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80156A14; }
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80156A70; }
    R(27) = (0 + 1);
    goto L_80156A70;
L_80156A14:;
    R(0) = R(3) & 0x2000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80156A40; }
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(29));
    if ((!CR_BIT(ctx, 2))) { goto L_80156A70; }
    GM_CALLV(0x80156A28u, 0x8005FFB0u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80156A70; }
    R(27) = (0 + 1);
    goto L_80156A70;
L_80156A40:;
    R(0) = R(3) & 0x4000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80156A70; }
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(29));
    if ((!CR_BIT(ctx, 2))) { goto L_80156A70; }
    GM_CALLV(0x80156A54u, 0x8005FD20u, 0);
    R(0) = R(3) ^ 0x1u;
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0x1u) != 0; R(4) = (v_ >> 1); }
    R(0) = R(0) &R(3);
    R(0) = R(4) - R(0);
    R(0) = rotl32(R(0), 1) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80156A70; }
    R(27) = (0 + 1);
L_80156A70:;
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[31].d); }
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(31) + 0); stfs(base, ea_, ctx->f[30].d); }
    R(11) = (f + 64);
    R(0) = lr;
}

/* fn_80156D70 (fn_80156D70, 132 bytes) */
static void pf_m_56d70(GM_CTX) {
    GM_FN(0x80156D70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(27) = R(3) |R(3);
    GM_CALLV(0x80156D8Cu, 0x801568D0u, 0);
    R(31) = R(3) |R(3);
    R(29) = (0 + 0);
    R(30) = (0 + 0);
    R(28) = (0 + 0);
L_80156D9C:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x80156DA8u, 0x80156820u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80156DC0; }
    R(0) = ld8(base, (R(3) + 5436));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_80156DC0; }
    R(30) = (R(30) + 1);
L_80156DC0:;
    R(28) = (R(28) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80156D9C; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), (int32_t)R(31));
    if ((!CR_BIT(ctx, 2))) { goto L_80156DD8; }
    R(29) = (0 + 1);
L_80156DD8:;
    R(11) = (f + 32);
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* fn_80156E00 (fn_80156E00, 156 bytes) */
static void pf_m_56e00(GM_CTX) {
    GM_FN(0x80156E00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80156E80; }
    R(3) = (R(3) + 0x90000u);
    R(4) = (0 + -1);
    R(3) = (R(3) + 2980);
    GM_CALLV(0x80156E34u, 0x800CD3E0u, 0);
    R(3) = (R(30) + 0x90000u);
    R(4) = (0 + -1);
    R(3) = (R(3) + 2912);
    GM_CALLV(0x80156E44u, 0x8007E1D0u, 0);
    R(3) = (R(30) + 0x90000u);
    R(4) = (0 + -1);
    R(3) = (R(3) + 2752);
    GM_CALLV(0x80156E54u, 0x80089210u, 0);
    R(3) = (R(30) + 0x90000u);
    R(4) = (0 + -1);
    R(3) = (R(3) + 2732);
    GM_CALLV(0x80156E64u, 0x800D85F0u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x80156E70u, 0x800773E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80156E80; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80156E80u, 0x80162920u, 0);
L_80156E80:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_801573B0 (fn_801573B0, 808 bytes) */
static void pf_m_573b0(GM_CTX) {
    GM_FRAME(384); gptr f = gm_frame_sp;
    { uint32_t ea_ = (f + 368); st64(base, ea_, ctx->f[31].u); }
    { uint32_t ea_ = (f + 376); psq_st(ctx, base, 31, ea_, 0, 0); }
    { uint32_t ea_ = (f + 352); st64(base, ea_, ctx->f[30].u); }
    { uint32_t ea_ = (f + 360); psq_st(ctx, base, 30, ea_, 0, 0); }
    { uint32_t ea_ = (f + 336); st64(base, ea_, ctx->f[29].u); }
    { uint32_t ea_ = (f + 344); psq_st(ctx, base, 29, ea_, 0, 0); }
    { uint32_t ea_ = (f + 320); st64(base, ea_, ctx->f[28].u); }
    { uint32_t ea_ = (f + 328); psq_st(ctx, base, 28, ea_, 0, 0); }
    { uint32_t ea_ = (f + 304); st64(base, ea_, ctx->f[27].u); }
    { uint32_t ea_ = (f + 312); psq_st(ctx, base, 27, ea_, 0, 0); }
    { uint32_t ea_ = (f + 288); st64(base, ea_, ctx->f[26].u); }
    { uint32_t ea_ = (f + 296); psq_st(ctx, base, 26, ea_, 0, 0); }
    { uint32_t ea_ = (f + 272); st64(base, ea_, ctx->f[25].u); }
    { uint32_t ea_ = (f + 280); psq_st(ctx, base, 25, ea_, 0, 0); }
    { uint32_t ea_ = (f + 256); st64(base, ea_, ctx->f[24].u); }
    { uint32_t ea_ = (f + 264); psq_st(ctx, base, 24, ea_, 0, 0); }
    { uint32_t ea_ = (f + 240); st64(base, ea_, ctx->f[23].u); }
    { uint32_t ea_ = (f + 248); psq_st(ctx, base, 23, ea_, 0, 0); }
    { uint32_t ea_ = (f + 224); st64(base, ea_, ctx->f[22].u); }
    { uint32_t ea_ = (f + 232); psq_st(ctx, base, 22, ea_, 0, 0); }
    { uint32_t ea_ = (f + 208); st64(base, ea_, ctx->f[21].u); }
    { uint32_t ea_ = (f + 216); psq_st(ctx, base, 21, ea_, 0, 0); }
    { uint32_t ea_ = (f + 192); st64(base, ea_, ctx->f[20].u); }
    { uint32_t ea_ = (f + 200); psq_st(ctx, base, 20, ea_, 0, 0); }
    { uint32_t ea_ = (f + 176); st64(base, ea_, ctx->f[19].u); }
    { uint32_t ea_ = (f + 184); psq_st(ctx, base, 19, ea_, 0, 0); }
    { uint32_t ea_ = (f + 160); st64(base, ea_, ctx->f[18].u); }
    { uint32_t ea_ = (f + 168); psq_st(ctx, base, 18, ea_, 0, 0); }
    { uint32_t ea_ = (f + 144); st64(base, ea_, ctx->f[17].u); }
    { uint32_t ea_ = (f + 152); psq_st(ctx, base, 17, ea_, 0, 0); }
    { uint32_t ea_ = (f + 128); st64(base, ea_, ctx->f[16].u); }
    { uint32_t ea_ = (f + 136); psq_st(ctx, base, 16, ea_, 0, 0); }
    { uint32_t ea_ = (f + 112); st64(base, ea_, ctx->f[15].u); }
    { uint32_t ea_ = (f + 120); psq_st(ctx, base, 15, ea_, 0, 0); }
    { uint32_t ea_ = (f + 96); st64(base, ea_, ctx->f[14].u); }
    { uint32_t ea_ = (f + 104); psq_st(ctx, base, 14, ea_, 0, 0); }
    R(0) = ld8(base, (R(13) + -21340));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80157640; }
    { uint32_t ea_ = (R(2) + -27584); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x80370000u);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[0].u); }
    R(4) = (R(3) + 28536);
    { uint32_t ea_ = (R(2) + -27576); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27592); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(2) + -27568); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(2) + -27560); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 124); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 8); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 32); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(2) + -27552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27508); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27500); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27492); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27484); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27476); ctx->f[13].d = ctx->ps1[13] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27468); ctx->f[12].d = ctx->ps1[12] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27460); ctx->f[11].d = ctx->ps1[11] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27504); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27496); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27488); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 128); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 16); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 40); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(2) + -27544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 132); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 24); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 48); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(2) + -27536); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 136); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 32); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 56); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(2) + -27528); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 140); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 40); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 64); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(2) + -27520); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 144); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 48); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 72); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(2) + -27512); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 148); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 56); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 80); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(2) + -27620); ctx->f[14].d = ctx->ps1[14] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 152); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 64); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(4) + 156); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 72); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(2) + -27612); ctx->f[15].d = ctx->ps1[15] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27604); ctx->f[16].d = ctx->ps1[16] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27596); ctx->f[17].d = ctx->ps1[17] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27588); ctx->f[18].d = ctx->ps1[18] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27580); ctx->f[19].d = ctx->ps1[19] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27572); ctx->f[20].d = ctx->ps1[20] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27564); ctx->f[21].d = ctx->ps1[21] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27556); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27548); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27540); ctx->f[24].d = ctx->ps1[24] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27532); ctx->f[25].d = ctx->ps1[25] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27524); ctx->f[26].d = ctx->ps1[26] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27516); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27616); ctx->f[10].d = ctx->ps1[10] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27608); ctx->f[9].d = ctx->ps1[9] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27600); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27480); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27472); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27464); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -27456); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 160); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 80); ctx->f[7].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(3) + 28536); stfs(base, ea_, ctx->f[14].d); }
    { uint32_t ea_ = (R(4) + 4); stfs(base, ea_, ctx->f[15].d); }
    { uint32_t ea_ = (R(4) + 8); stfs(base, ea_, ctx->f[16].d); }
    { uint32_t ea_ = (R(4) + 12); stfs(base, ea_, ctx->f[17].d); }
    { uint32_t ea_ = (R(4) + 16); stfs(base, ea_, ctx->f[18].d); }
    { uint32_t ea_ = (R(4) + 20); stfs(base, ea_, ctx->f[19].d); }
    { uint32_t ea_ = (R(4) + 24); stfs(base, ea_, ctx->f[20].d); }
    { uint32_t ea_ = (R(4) + 28); stfs(base, ea_, ctx->f[21].d); }
    { uint32_t ea_ = (R(4) + 32); stfs(base, ea_, ctx->f[22].d); }
    { uint32_t ea_ = (R(4) + 36); stfs(base, ea_, ctx->f[23].d); }
    { uint32_t ea_ = (R(4) + 40); stfs(base, ea_, ctx->f[24].d); }
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[25].d); }
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[26].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (R(4) + 56); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(4) + 60); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (R(4) + 64); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(4) + 68); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(4) + 72); stfs(base, ea_, ctx->f[13].d); }
    { uint32_t ea_ = (R(4) + 76); stfs(base, ea_, ctx->f[12].d); }
    { uint32_t ea_ = (R(4) + 80); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (R(4) + 84); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(4) + 88); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (R(4) + 92); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(4) + 96); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(4) + 100); stfs(base, ea_, ctx->f[13].d); }
    { uint32_t ea_ = (R(4) + 104); stfs(base, ea_, ctx->f[12].d); }
    { uint32_t ea_ = (R(4) + 108); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (R(4) + 112); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (R(4) + 116); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(4) + 120); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (R(4) + 164); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (R(4) + 168); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(4) + 172); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(4) + 176); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 180); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 184); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 188); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + 192); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 196); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(4) + 200); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(4) + 204); stfs(base, ea_, ctx->f[4].d); }
    R(3) = ld32(base, (R(2) + -27624));
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(4) + 208); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 212); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 216); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + 220); stfs(base, ea_, ctx->f[0].d); }
    st16(base, (R(4) + 224), R(3));
    st8(base, (R(13) + -21340), R(0));
L_80157640:;
    { uint32_t ea_ = (f + 376); psq_l(ctx, base, 31, ea_, 0, 0); }
    { uint32_t ea_ = (f + 368); ctx->f[31].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 360); psq_l(ctx, base, 30, ea_, 0, 0); }
    { uint32_t ea_ = (f + 352); ctx->f[30].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 344); psq_l(ctx, base, 29, ea_, 0, 0); }
    { uint32_t ea_ = (f + 336); ctx->f[29].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 328); psq_l(ctx, base, 28, ea_, 0, 0); }
    { uint32_t ea_ = (f + 320); ctx->f[28].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 312); psq_l(ctx, base, 27, ea_, 0, 0); }
    { uint32_t ea_ = (f + 304); ctx->f[27].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 296); psq_l(ctx, base, 26, ea_, 0, 0); }
    { uint32_t ea_ = (f + 288); ctx->f[26].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 280); psq_l(ctx, base, 25, ea_, 0, 0); }
    { uint32_t ea_ = (f + 272); ctx->f[25].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 264); psq_l(ctx, base, 24, ea_, 0, 0); }
    { uint32_t ea_ = (f + 256); ctx->f[24].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 248); psq_l(ctx, base, 23, ea_, 0, 0); }
    { uint32_t ea_ = (f + 240); ctx->f[23].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 232); psq_l(ctx, base, 22, ea_, 0, 0); }
    { uint32_t ea_ = (f + 224); ctx->f[22].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 216); psq_l(ctx, base, 21, ea_, 0, 0); }
    { uint32_t ea_ = (f + 208); ctx->f[21].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 200); psq_l(ctx, base, 20, ea_, 0, 0); }
    { uint32_t ea_ = (f + 192); ctx->f[20].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 184); psq_l(ctx, base, 19, ea_, 0, 0); }
    { uint32_t ea_ = (f + 176); ctx->f[19].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 168); psq_l(ctx, base, 18, ea_, 0, 0); }
    { uint32_t ea_ = (f + 160); ctx->f[18].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 152); psq_l(ctx, base, 17, ea_, 0, 0); }
    { uint32_t ea_ = (f + 144); ctx->f[17].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 136); psq_l(ctx, base, 16, ea_, 0, 0); }
    { uint32_t ea_ = (f + 128); ctx->f[16].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 120); psq_l(ctx, base, 15, ea_, 0, 0); }
    { uint32_t ea_ = (f + 112); ctx->f[15].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 104); psq_l(ctx, base, 14, ea_, 0, 0); }
    { uint32_t ea_ = (f + 96); ctx->f[14].u = ld64(base, ea_); }
}

/* fn_801580F0 (fn_801580F0, 8 bytes) */
static void pf_m_580f0(GM_CTX) {
    R(3) = (R(3) + 112);
    GM_TAIL(0x800C9930u, 0); return;
}

/* fn_80158100 (fn_80158100, 420 bytes) */
static void pf_m_58100(GM_CTX) {
    GM_FN(0x80158100); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld32(base, (R(13) + -21628));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_80158294; }
    { uint32_t ea_ = (R(2) + -21696); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -21692); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1352); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[1].d + ctx->f[6].d);
    { uint32_t ea_ = (R(3) + 1348); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1356); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[4].d);
    R(4) = ld32(base, (R(3) + 1316));
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[1].d - ctx->f[6].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[7].d + ctx->f[5].d);
    { uint32_t ea_ = (R(2) + -21688); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d + ctx->f[3].d);
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[5].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 1360); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1364); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1368); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[6].d + ctx->f[4].d);
    R(4) = ld32(base, (R(3) + 1320));
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d + ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 1372); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1376); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1380); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[4].d);
    R(4) = ld32(base, (R(3) + 1260));
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d + ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 1384); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1388); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1392); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[4].d);
    R(4) = ld32(base, (R(3) + 1280));
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d + ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 1396); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1400); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1404); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[4].d);
    R(4) = ld32(base, (R(3) + 1256));
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[5].d + ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 1408); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1412); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1416); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[4].d);
    R(4) = ld32(base, (R(3) + 1284));
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d + ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 1420); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1424); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1428); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[4].d);
    R(4) = ld32(base, (R(3) + 1288));
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d + ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 1432); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 1436); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 1440); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d + ctx->f[3].d);
    R(4) = ld32(base, (R(3) + 1312));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(3) + 120));
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[3].d); }
    R(12) = ld32(base, (R(12) + 16));
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    ctx->ctr = R(12);
    R(3) = (R(3) + 112);
    GM_CALLV(0x80158294u, ctx->ctr, 0);
L_80158294:;
    R(0) = lr;
}

/* fn_80159960 (fn_80159960, 348 bytes) */
static void pf_m_59960(GM_CTX) {
    GM_FN(0x80159960); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(30) = R(4) |R(4);
    R(0) = ld8(base, (R(3) + 1107));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80159AA4; }
    R(0) = ld32(base, (R(3) + 988));
    cr_cmp_s(ctx, 0, (int32_t)R(0), (int32_t)R(4));
    if ((CR_BIT(ctx, 2))) { goto L_80159AA4; }
    st32(base, (R(3) + 988), R(4));
    R(4) = (R(2) + -21708);
    R(5) = ld32(base, (R(3) + 1244));
    R(6) = (0 + 0);
    R(3) = (R(3) + 988);
    GM_CALLV(0x801599ACu, 0x800B3B60u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80159AA4; }
    R(0) = ld32(base, (R(31) + 1092));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80159AA4; }
    R(3) = ld32(base, (R(13) + -21056));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x801599D4u, ctx->ctr, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_801599E8; }
    goto L_80159AA4;
L_801599E8:;
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 23440);
    R(3) = ld32(base, (R(3) + 8));
    R(0) = (R(3) + -2);
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_80159AA4; }
    R(30) = ld32(base, (R(31) + 1308));
    R(3) = (f + 8);
    { uint32_t ea_ = (R(2) + -21696); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0);
    R(5) = ld32(base, (R(30) + 144));
    st32(base, (f + 36), R(5));
    R(0) = ld32(base, (R(30) + 160));
    st32(base, (f + 52), R(0));
    R(31) = ld32(base, (R(30) + 132));
    R(12) = ld32(base, (R(30) + 136));
    R(11) = ld32(base, (R(30) + 140));
    R(10) = ld32(base, (R(30) + 148));
    R(9) = ld32(base, (R(30) + 152));
    R(8) = ld32(base, (R(30) + 156));
    R(7) = ld32(base, (R(30) + 164));
    R(6) = ld32(base, (R(30) + 168));
    R(5) = ld32(base, (R(30) + 172));
    R(0) = ld32(base, (R(30) + 176));
    { uint32_t ea_ = (f + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 52); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st32(base, (f + 24), R(31));
    st32(base, (f + 28), R(12));
    st32(base, (f + 32), R(11));
    st32(base, (f + 40), R(10));
    st32(base, (f + 44), R(9));
    st32(base, (f + 48), R(8));
    st32(base, (f + 56), R(7));
    st32(base, (f + 60), R(6));
    st32(base, (f + 64), R(5));
    st32(base, (f + 68), R(0));
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80159A88u, 0x800B37E0u, 0);
    R(3) = (0 + 0x80320000u);
    R(5) = (f + 8);
    R(3) = (R(3) + 30432);
    R(4) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x80159AA4u, 0x8016C890u, 0);
L_80159AA4:;
    R(0) = lr;
}

/* fn_80159F10 (fn_80159F10, 824 bytes) */
static void pf_m_59f10(GM_CTX) {
    GM_FN(0x80159F10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 176);
    R(29) = (0 + 0x80320000u);
    R(28) = (0 + 0x80370000u);
    R(29) = (R(29) + 29472);
    R(3) = (R(29) + 1328);
    R(27) = ld32(base, (R(29) + 1328));
    R(6) = (R(29) + 1340);
    R(5) = (R(29) + 1352);
    R(12) = ld32(base, (R(3) + 4));
    R(28) = (R(28) + 28776);
    R(11) = ld32(base, (R(3) + 8));
    R(4) = (R(29) + 1472);
    R(10) = ld32(base, (R(29) + 1340));
    R(3) = (R(28) + 16);
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1352));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 116), R(27));
    st32(base, (f + 120), R(12));
    st32(base, (f + 124), R(11));
    st32(base, (f + 128), R(10));
    st32(base, (f + 132), R(9));
    st32(base, (f + 136), R(8));
    st32(base, (f + 140), R(7));
    st32(base, (f + 144), R(6));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x80159F94u, 0x8015F7C0u, 0);
    R(30) = (0 + 0x80320000u);
    R(3) = (R(28) + 16);
    R(27) = ld32(base, (f + 140));
    R(30) = (R(30) + 31104);
    R(12) = ld32(base, (f + 144));
    R(31) = (0 + 0x80160000u);
    R(11) = ld32(base, (f + 148));
    R(4) = (R(31) + -23984);
    R(10) = ld32(base, (f + 128));
    R(5) = (R(28) + 0);
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(28) + 16), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x80159FFCu, 0x802DC780u, 0);
    R(3) = (R(29) + 1364);
    R(6) = (R(29) + 1376);
    R(5) = (R(29) + 1388);
    R(27) = ld32(base, (R(29) + 1364));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 1512);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 80);
    R(10) = ld32(base, (R(29) + 1376));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1388));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 80), R(27));
    st32(base, (f + 84), R(12));
    st32(base, (f + 88), R(11));
    st32(base, (f + 92), R(10));
    st32(base, (f + 96), R(9));
    st32(base, (f + 100), R(8));
    st32(base, (f + 104), R(7));
    st32(base, (f + 108), R(6));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x8015A05Cu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 80);
    R(27) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(31) + -23984);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(28) + 64);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(28) + 80), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015A0B8u, 0x802DC780u, 0);
    R(3) = (R(29) + 1400);
    R(6) = (R(29) + 1412);
    R(5) = (R(29) + 1424);
    R(27) = ld32(base, (R(29) + 1400));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 1552);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 144);
    R(10) = ld32(base, (R(29) + 1412));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1424));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 44), R(27));
    st32(base, (f + 48), R(12));
    st32(base, (f + 52), R(11));
    st32(base, (f + 56), R(10));
    st32(base, (f + 60), R(9));
    st32(base, (f + 64), R(8));
    st32(base, (f + 68), R(7));
    st32(base, (f + 72), R(6));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x8015A118u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 144);
    R(27) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(31) + -23984);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(28) + 128);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(28) + 144), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015A174u, 0x802DC780u, 0);
    R(3) = (R(29) + 1436);
    R(6) = (R(29) + 1448);
    R(5) = (R(29) + 1460);
    R(27) = ld32(base, (R(29) + 1436));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 1596);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 208);
    R(10) = ld32(base, (R(29) + 1448));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1460));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 8), R(27));
    st32(base, (f + 12), R(12));
    st32(base, (f + 16), R(11));
    st32(base, (f + 20), R(10));
    st32(base, (f + 24), R(9));
    st32(base, (f + 28), R(8));
    st32(base, (f + 32), R(7));
    st32(base, (f + 36), R(6));
    st32(base, (f + 40), R(0));
    GM_CALLV(0x8015A1D4u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 208);
    R(29) = ld32(base, (f + 32));
    R(12) = ld32(base, (f + 36));
    R(7) = R(27) |R(27);
    R(11) = ld32(base, (f + 40));
    R(4) = (R(31) + -23984);
    R(10) = ld32(base, (f + 20));
    R(5) = (R(28) + 192);
    R(9) = ld32(base, (f + 24));
    R(8) = ld32(base, (f + 28));
    R(6) = ld32(base, (f + 12));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(28) + 208), R(30));
    st32(base, (R(3) + 12), R(29));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015A230u, 0x802DC780u, 0);
    R(11) = (f + 176);
    R(0) = lr;
}

/* fn_8015A340 (fn_8015A340, 48 bytes) */
static void pf_m_5a340(GM_CTX) {
    GM_FN(0x8015A340); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 664);
    GM_CALLV(0x8015A354u, 0x801628C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015A360; }
    GM_CALLV(0x8015A360u, 0x8015A370u, 0);
L_8015A360:;
    R(0) = lr;
}

/* fn_8015A370 (fn_8015A370, 180 bytes) */
static void pf_m_5a370(GM_CTX) {
    GM_FN(0x8015A370); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x8015A38Cu, 0x8006C420u, 0);
    R(4) = (0 + 0x80320000u);
    R(3) = (R(30) + 112);
    R(4) = (R(4) + 32048);
    st32(base, (R(30) + 96), R(4));
    GM_CALLV(0x8015A3A0u, 0x800C8950u, 0);
    R(3) = (0 + 0x80320000u);
    R(9) = (0 + 0x80300000u);
    R(8) = (0 + 0x80320000u);
    R(7) = (0 + 0x80320000u);
    R(3) = (R(3) + 32176);
    R(9) = (R(9) + -5384);
    R(8) = (R(8) + 32224);
    R(7) = (R(7) + 32248);
    R(31) = (0 + 0);
    R(6) = (0 + 0x80370000u);
    st32(base, (R(30) + 520), R(3));
    R(5) = (R(30) + 528);
    R(4) = (R(30) + 524);
    R(3) = (R(30) + 544);
    st32(base, (R(30) + 524), R(9));
    R(6) = (R(6) + 29056);
    st32(base, (R(30) + 528), R(8));
    st32(base, (R(30) + 532), R(7));
    st32(base, (R(30) + 536), R(30));
    st32(base, (R(30) + 540), R(31));
    GM_CALLV(0x8015A3F4u, 0x8015FC90u, 0);
    R(3) = (0 + 0x80320000u);
    st8(base, (R(30) + 656), R(31));
    R(3) = (R(3) + 32128);
    st32(base, (R(30) + 520), R(3));
    R(3) = R(30) |R(30);
    st32(base, (R(13) + -21316), R(30));
    R(0) = lr;
}

/* fn_8015A580 (fn_8015A580, 132 bytes) */
static void pf_m_5a580(GM_CTX) {
    GM_FN(0x8015A580); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8015A5E8; }
    { uint32_t a_ = R(3); R(0) = a_ + 0x208u; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8015A5C0; }
    if ((CR_BIT(ctx, 2))) { goto L_8015A5C0; }
    { uint32_t a_ = R(0); R(3) = a_ + 0x18u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8015A5C0; }
    R(4) = (0 + 0);
    GM_CALLV(0x8015A5C0u, 0x8015F9F0u, 0);
L_8015A5C0:;
    R(3) = (R(30) + 112);
    R(4) = (0 + -1);
    GM_CALLV(0x8015A5CCu, 0x800C89A0u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x8015A5D8u, 0x8006C490u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8015A5E8; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8015A5E8u, 0x80162920u, 0);
L_8015A5E8:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_8015A610 (fn_8015A610, 508 bytes) */
static void pf_m_5a610(GM_CTX) {
    GM_FN(0x8015A610); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(30) = (0 + 0x80320000u);
    R(30) = (R(30) + 31160);
    R(29) = (0 + 0x802F0000u);
    R(29) = (R(29) + 23008);
    R(0) = ld8(base, (R(3) + 656));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015A650; }
    R(3) = (0 + 1);
    goto L_8015A7F0;
L_8015A650:;
    R(4) = (R(30) + 760);
    R(5) = (0 + 0);
    R(3) = (R(3) + 112);
    GM_CALLV(0x8015A660u, 0x800C8CB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015A670; }
    R(3) = (0 + 0);
    goto L_8015A7F0;
L_8015A670:;
    R(12) = ld32(base, (R(31) + 120));
    R(3) = (R(31) + 112);
    R(4) = (R(30) + 784);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8015A68Cu, ctx->ctr, 0);
    R(3) = (R(31) + 112);
    R(4) = (R(30) + 260);
    R(5) = (0 + 7);
    GM_CALLV(0x8015A69Cu, 0x800C8FB0u, 0);
    R(3) = (R(31) + 112);
    R(4) = (R(30) + 340);
    R(5) = (R(29) + 0);
    R(6) = (0 + 11);
    GM_CALLV(0x8015A6B0u, 0x800C90F0u, 0);
    R(3) = (R(31) + 112);
    R(4) = (R(30) + 440);
    R(5) = (R(29) + 48);
    R(6) = (0 + 1);
    R(7) = (0 + 4);
    GM_CALLV(0x8015A6C8u, 0x800C8F20u, 0);
    R(3) = (R(31) + 112);
    R(4) = (R(30) + 496);
    R(5) = (R(29) + 64);
    R(6) = (0 + 2);
    R(7) = (0 + 3);
    GM_CALLV(0x8015A6E0u, 0x800C8F20u, 0);
    R(3) = (R(31) + 112);
    R(4) = (R(30) + 560);
    R(5) = (R(31) + 580);
    R(6) = (0 + 4);
    GM_CALLV(0x8015A6F4u, 0x800C8E40u, 0);
    R(3) = (R(31) + 112);
    R(5) = (R(31) + 596);
    R(4) = (R(13) + -25240);
    R(6) = (0 + 1);
    GM_CALLV(0x8015A708u, 0x800C8DD0u, 0);
    R(3) = (R(31) + 112);
    R(4) = (R(30) + 664);
    R(5) = (R(31) + 600);
    R(6) = (0 + 8);
    GM_CALLV(0x8015A71Cu, 0x800C8EB0u, 0);
    R(3) = (R(31) + 112);
    R(4) = (R(30) + 748);
    R(5) = (R(31) + 632);
    R(6) = (0 + 3);
    GM_CALLV(0x8015A730u, 0x800C8D60u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 141);
    R(0) = (0 + 1);
    st8(base, (R(31) + 124), R(4));
    st8(base, (R(31) + 657), R(3));
    st8(base, (R(31) + 656), R(0));
    st8(base, (R(31) + 660), R(3));
    st32(base, (R(31) + 652), R(3));
    st8(base, (R(31) + 661), R(3));
    st8(base, (R(31) + 659), R(3));
    GM_CALLV(0x8015A75Cu, 0x800B4DE0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015A784; }
    R(0) = ld16(base, (R(13) + -28494));
    cr_cmp_u(ctx, 0, R(0), 0x5u);
    if ((!CR_BIT(ctx, 2))) { goto L_8015A784; }
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 23440);
    R(0) = ld8(base, (R(3) + 13));
    cr_cmp_u(ctx, 0, R(0), 0x23u);
    if ((!CR_BIT(ctx, 2))) { goto L_8015A798; }
L_8015A784:;
    R(3) = ld32(base, (R(31) + 588));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    goto L_8015A7AC;
L_8015A798:;
    R(3) = ld32(base, (R(31) + 588));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
L_8015A7AC:;
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 23440);
    R(3) = ld8(base, (R(3) + 13));
    R(0) = (R(3) + 224);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((CR_BIT(ctx, 1))) { goto L_8015A7DC; }
    R(3) = ld32(base, (R(31) + 588));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
L_8015A7DC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8015A7E4u, 0x8015AB20u, 0);
    R(3) = (R(31) + 112);
    GM_CALLV(0x8015A7ECu, 0x800C9500u, 0);
    R(3) = (0 + 1);
L_8015A7F0:;
    R(0) = lr;
}

/* fn_8015A810 (fn_8015A810, 112 bytes) */
static void pf_m_5a810(GM_CTX) {
    GM_FN(0x8015A810); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld8(base, (R(3) + 656));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015A868; }
    R(0) = ld8(base, (R(3) + 657));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015A868; }
    { uint32_t ea_ = R(3) + 520; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x8015A84Cu, ctx->ctr, 0);
    R(3) = (R(31) + 112);
    GM_CALLV(0x8015A854u, 0x800C9560u, 0);
    R(12) = ld32(base, (R(31) + 120));
    R(3) = (R(31) + 112);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x8015A868u, ctx->ctr, 0);
L_8015A868:;
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_8015A890 (fn_8015A890, 64 bytes) */
static void pf_m_5a890(GM_CTX) {
    GM_FN(0x8015A890); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld8(base, (R(3) + 656));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015A8BC; }
    R(0) = ld8(base, (R(3) + 657));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015A8BC; }
    R(3) = (R(3) + 112);
    GM_CALLV(0x8015A8BCu, 0x80006EA0u, 0);
L_8015A8BC:;
    R(0) = lr;
    R(3) = (0 + 1);
}

/* fn_8015A8D0 (fn_8015A8D0, 64 bytes) */
static void pf_m_5a8d0(GM_CTX) {
    GM_FN(0x8015A8D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (R(3) + 112);
    GM_CALLV(0x8015A8E4u, 0x800C9930u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015A8F4; }
    R(3) = (0 + 0);
    goto L_8015A900;
L_8015A8F4:;
    R(0) = (0 + 0);
    st32(base, (R(13) + -21316), R(0));
    R(3) = (0 + 1);
L_8015A900:;
    R(0) = lr;
}

/* fn_8015A910 (fn_8015A910, 524 bytes) */
static void pf_m_5a910(GM_CTX) {
    GM_FN(0x8015A910); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(31) = R(3) |R(3);
    GM_CALLV(0x8015A92Cu, 0x800CDC60u, 0);
    R(4) = (0 + 0x80310000u);
    R(30) = ld32(base, (R(13) + -22276));
    R(4) = (R(4) + 23440);
    R(28) = R(3) |R(3);
    R(27) = ld8(base, (R(4) + 12));
    R(29) = ld8(base, (R(4) + 13));
    cr_cmp_u(ctx, 0, R(27), 0x9u);
    if ((!CR_BIT(ctx, 1))) { goto L_8015A950; }
    R(27) = (0 + 9);
L_8015A950:;
    R(3) = R(27) & 0xFFu;
    R(4) = R(28) |R(28);
    R(0) = (R(3) + 1);
    st32(base, (R(30) + 948), R(0));
    R(5) = (0 + 2);
    R(6) = (0 + 81);
    R(3) = ld32(base, (R(31) + 616));
    R(7) = (0 + 0);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x8015A978u, 0x800C9A60u, 0);
    R(0) = (R(29) + -20);
    cr_cmp_u(ctx, 0, R(0), 0x14u);
    if ((CR_BIT(ctx, 1))) { goto L_8015AA7C; }
    R(3) = (0 + 0x80320000u);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = (R(3) + 31964);
    R(3) = ld32(base, (R(3) + R(0)));
    ctx->ctr = R(3);
    { switch (ctx->ctr) { case 0x8015A99Cu: goto L_8015A99C; case 0x8015A9A4u: goto L_8015A9A4; case 0x8015A9ACu: goto L_8015A9AC; case 0x8015A9C8u: goto L_8015A9C8; case 0x8015AA10u: goto L_8015AA10; case 0x8015AA40u: goto L_8015AA40; case 0x8015AA48u: goto L_8015AA48; case 0x8015AA50u: goto L_8015AA50; case 0x8015AA58u: goto L_8015AA58; case 0x8015AA60u: goto L_8015AA60; case 0x8015AA7Cu: goto L_8015AA7C; default: rt_fatal("8015A910: jump table target %08X", ctx->ctr); return; } }
L_8015A99C:;
    R(6) = (0 + 85);
    goto L_8015AAC8;
L_8015A9A4:;
    R(6) = (0 + 84);
    goto L_8015AAC8;
L_8015A9AC:;
    R(0) = R(27) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x7u);
    if ((CR_BIT(ctx, 2))) { goto L_8015A9C0; }
    R(6) = (0 + 83);
    goto L_8015AAC8;
L_8015A9C0:;
    R(6) = (0 + 93);
    goto L_8015AAC8;
L_8015A9C8:;
    R(4) = R(29) |R(29);
    R(3) = R(27) & 0xFFu;
    R(5) = (0 + 128);
    GM_CALLV(0x8015A9D8u, 0x80102750u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015A9E8; }
    R(6) = (0 + 91);
    goto L_8015AAC8;
L_8015A9E8:;
    R(4) = R(29) |R(29);
    R(3) = R(27) & 0xFFu;
    R(5) = (0 + 512);
    GM_CALLV(0x8015A9F8u, 0x80102750u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015AA08; }
    R(6) = (0 + 92);
    goto L_8015AAC8;
L_8015AA08:;
    R(6) = (0 + 88);
    goto L_8015AAC8;
L_8015AA10:;
    GM_CALLV(0x8015AA14u, 0x800FB3C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015AA24; }
    R(6) = (0 + 92);
    goto L_8015AAC8;
L_8015AA24:;
    GM_CALLV(0x8015AA28u, 0x800FB460u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015AA38; }
    R(6) = (0 + 88);
    goto L_8015AAC8;
L_8015AA38:;
    R(6) = (0 + 91);
    goto L_8015AAC8;
L_8015AA40:;
    R(6) = (0 + 94);
    goto L_8015AAC8;
L_8015AA48:;
    R(6) = (0 + 86);
    goto L_8015AAC8;
L_8015AA50:;
    R(6) = (0 + 90);
    goto L_8015AAC8;
L_8015AA58:;
    R(6) = (0 + 95);
    goto L_8015AAC8;
L_8015AA60:;
    GM_CALLV(0x8015AA64u, 0x800FBFF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015AA74; }
    R(6) = (0 + 95);
    goto L_8015AAC8;
L_8015AA74:;
    R(6) = (0 + 87);
    goto L_8015AAC8;
L_8015AA7C:;
    R(0) = (R(29) + 1);
    st32(base, (R(30) + 952), R(0));
    R(4) = R(28) |R(28);
    R(5) = (0 + 2);
    R(3) = ld32(base, (R(31) + 620));
    R(6) = (0 + 82);
    R(7) = (0 + 0);
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(31) + 620));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x8015AAB4u, 0x800C9A60u, 0);
    R(3) = ld32(base, (R(31) + 624));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    goto L_8015AB04;
L_8015AAC8:;
    R(3) = ld32(base, (R(31) + 620));
    R(4) = R(28) |R(28);
    R(5) = (0 + 2);
    R(7) = (0 + 0);
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(31) + 624));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(31) + 624));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x8015AB04u, 0x800C9A60u, 0);
L_8015AB04:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_8015AB20 (fn_8015AB20, 268 bytes) */
static void pf_m_5ab20(GM_CTX) {
    GM_FN(0x8015AB20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 632));
    R(0) = ld8(base, (R(4) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(4) + 187), R(0));
    R(4) = ld32(base, (R(3) + 636));
    R(0) = ld8(base, (R(4) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(4) + 187), R(0));
    R(3) = ld32(base, (R(3) + 640));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    GM_CALLV(0x8015AB6Cu, 0x800CDC60u, 0);
    R(9) = ld32(base, (R(13) + -22276));
    R(4) = ld32(base, (R(9) + 1000));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 10);
    if ((CR_BIT(ctx, 0))) { goto L_8015AB80; }
    R(4) = (R(4) + -10);
L_8015AB80:;
    R(0) = ld32(base, (R(13) + -22272));
    R(0) = R(0) & 0x40u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8015AC00; }
    R(0) = ld32(base, (R(9) + 996));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015AC00; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 5);
    if ((!CR_BIT(ctx, 0))) { goto L_8015AC00; }
    R(8) = ld32(base, (R(31) + 620));
    R(0) = (R(4) + 1);
    R(4) = R(3) |R(3);
    R(5) = (0 + 2);
    R(3) = ld8(base, (R(8) + 187));
    R(6) = (0 + 82);
    R(7) = (0 + 0);
    R(3) = R(3) & 0xFEu;
    R(3) = R(3) | 0x1u;
    st8(base, (R(8) + 187), R(3));
    R(8) = ld32(base, (R(31) + 624));
    R(3) = ld8(base, (R(8) + 187));
    R(3) = R(3) & 0xFEu;
    st8(base, (R(8) + 187), R(3));
    R(8) = ld32(base, (R(31) + 592));
    R(3) = ld8(base, (R(8) + 187));
    R(3) = R(3) & 0xFEu;
    R(3) = R(3) | 0x1u;
    st8(base, (R(8) + 187), R(3));
    st32(base, (R(9) + 952), R(0));
    R(3) = ld32(base, (R(31) + 620));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x8015ABFCu, 0x800C9A60u, 0);
    goto L_8015AC18;
L_8015AC00:;
    R(4) = ld32(base, (R(31) + 592));
    R(3) = R(31) |R(31);
    R(0) = ld8(base, (R(4) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(4) + 187), R(0));
    GM_CALLV(0x8015AC18u, 0x8015A910u, 0);
L_8015AC18:;
    R(0) = lr;
}

/* fn_8015B320 (fn_8015B320, 1276 bytes) */
static void pf_m_5b320(GM_CTX) {
    GM_FN(0x8015B320); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 272);
    R(29) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -21664); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(29) = (R(29) + 31160);
    { uint32_t ea_ = (R(2) + -21660); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(6) = (R(29) + 0);
    { uint32_t ea_ = (R(2) + -21656); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = ld32(base, (R(2) + -24852));
    R(28) = (0 + 0x80370000u);
    R(28) = (R(28) + 29032);
    R(4) = (0 + 0x80160000u);
    st32(base, (R(6) + 12), R(0));
    R(4) = (R(4) + -18400);
    R(5) = (R(28) + 0);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 224); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 228); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 232); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8015B388u, 0x802DC780u, 0);
    R(7) = (R(29) + 1240);
    R(6) = (R(29) + 1252);
    R(5) = (R(29) + 1264);
    R(30) = ld32(base, (R(2) + -24828));
    R(27) = ld32(base, (R(29) + 1240));
    R(4) = (R(29) + 1456);
    R(12) = ld32(base, (R(7) + 4));
    R(3) = (R(28) + 24);
    R(11) = ld32(base, (R(7) + 8));
    R(10) = ld32(base, (R(29) + 1252));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1264));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (R(13) + -21320), R(30));
    st32(base, (f + 188), R(27));
    st32(base, (f + 192), R(12));
    st32(base, (f + 196), R(11));
    st32(base, (f + 200), R(10));
    st32(base, (f + 204), R(9));
    st32(base, (f + 208), R(8));
    st32(base, (f + 212), R(7));
    st32(base, (f + 216), R(6));
    st32(base, (f + 220), R(0));
    GM_CALLV(0x8015B3F0u, 0x8015F7C0u, 0);
    R(30) = (0 + 0x80330000u);
    R(3) = (R(28) + 24);
    R(27) = ld32(base, (f + 212));
    R(30) = (R(30) + -32680);
    R(12) = ld32(base, (f + 216));
    R(31) = (0 + 0x80160000u);
    R(11) = ld32(base, (f + 220));
    R(4) = (R(31) + -18368);
    R(10) = ld32(base, (f + 200));
    R(5) = (R(28) + 12);
    R(9) = ld32(base, (f + 204));
    R(8) = ld32(base, (f + 208));
    R(7) = ld32(base, (f + 188));
    R(6) = ld32(base, (f + 192));
    R(0) = ld32(base, (f + 196));
    st32(base, (R(28) + 24), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015B458u, 0x802DC780u, 0);
    R(3) = (R(29) + 1276);
    R(6) = (R(29) + 1288);
    R(5) = (R(29) + 1300);
    R(27) = ld32(base, (R(29) + 1276));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 1488);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 88);
    R(10) = ld32(base, (R(29) + 1288));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1300));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 152), R(27));
    st32(base, (f + 156), R(12));
    st32(base, (f + 160), R(11));
    st32(base, (f + 164), R(10));
    st32(base, (f + 168), R(9));
    st32(base, (f + 172), R(8));
    st32(base, (f + 176), R(7));
    st32(base, (f + 180), R(6));
    st32(base, (f + 184), R(0));
    GM_CALLV(0x8015B4B8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 88);
    R(27) = ld32(base, (f + 176));
    R(12) = ld32(base, (f + 180));
    R(4) = (R(31) + -18368);
    R(11) = ld32(base, (f + 184));
    R(5) = (R(28) + 72);
    R(10) = ld32(base, (f + 164));
    R(9) = ld32(base, (f + 168));
    R(8) = ld32(base, (f + 172));
    R(7) = ld32(base, (f + 152));
    R(6) = ld32(base, (f + 156));
    R(0) = ld32(base, (f + 160));
    st32(base, (R(28) + 88), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015B514u, 0x802DC780u, 0);
    R(3) = (R(29) + 1312);
    R(6) = (R(29) + 1324);
    R(5) = (R(29) + 1336);
    R(27) = ld32(base, (R(29) + 1312));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 1528);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 152);
    R(10) = ld32(base, (R(29) + 1324));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1336));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 116), R(27));
    st32(base, (f + 120), R(12));
    st32(base, (f + 124), R(11));
    st32(base, (f + 128), R(10));
    st32(base, (f + 132), R(9));
    st32(base, (f + 136), R(8));
    st32(base, (f + 140), R(7));
    st32(base, (f + 144), R(6));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x8015B574u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 152);
    R(27) = ld32(base, (f + 140));
    R(12) = ld32(base, (f + 144));
    R(4) = (R(31) + -18368);
    R(11) = ld32(base, (f + 148));
    R(5) = (R(28) + 136);
    R(10) = ld32(base, (f + 128));
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(28) + 152), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015B5D0u, 0x802DC780u, 0);
    R(3) = (R(29) + 1348);
    R(6) = (R(29) + 1360);
    R(5) = (R(29) + 1372);
    R(27) = ld32(base, (R(29) + 1348));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 1576);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 216);
    R(10) = ld32(base, (R(29) + 1360));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1372));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 80), R(27));
    st32(base, (f + 84), R(12));
    st32(base, (f + 88), R(11));
    st32(base, (f + 92), R(10));
    st32(base, (f + 96), R(9));
    st32(base, (f + 100), R(8));
    st32(base, (f + 104), R(7));
    st32(base, (f + 108), R(6));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x8015B630u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 216);
    R(27) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(31) + -18368);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(28) + 200);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(28) + 216), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015B68Cu, 0x802DC780u, 0);
    R(3) = (R(29) + 1384);
    R(6) = (R(29) + 1396);
    R(5) = (R(29) + 1408);
    R(27) = ld32(base, (R(29) + 1384));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 1612);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 280);
    R(10) = ld32(base, (R(29) + 1396));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1408));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 44), R(27));
    st32(base, (f + 48), R(12));
    st32(base, (f + 52), R(11));
    st32(base, (f + 56), R(10));
    st32(base, (f + 60), R(9));
    st32(base, (f + 64), R(8));
    st32(base, (f + 68), R(7));
    st32(base, (f + 72), R(6));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x8015B6ECu, 0x8015F7C0u, 0);
    R(3) = (R(28) + 280);
    R(27) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(31) + -18368);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(28) + 264);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(28) + 280), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015B748u, 0x802DC780u, 0);
    R(3) = (R(29) + 1420);
    R(6) = (R(29) + 1432);
    R(5) = (R(29) + 1444);
    R(27) = ld32(base, (R(29) + 1420));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(29) + 1652);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(28) + 344);
    R(10) = ld32(base, (R(29) + 1432));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(29) + 1444));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 8), R(27));
    st32(base, (f + 12), R(12));
    st32(base, (f + 16), R(11));
    st32(base, (f + 20), R(10));
    st32(base, (f + 24), R(9));
    st32(base, (f + 28), R(8));
    st32(base, (f + 32), R(7));
    st32(base, (f + 36), R(6));
    st32(base, (f + 40), R(0));
    GM_CALLV(0x8015B7A8u, 0x8015F7C0u, 0);
    R(3) = (R(28) + 344);
    R(29) = ld32(base, (f + 32));
    R(12) = ld32(base, (f + 36));
    R(7) = R(27) |R(27);
    R(11) = ld32(base, (f + 40));
    R(4) = (R(31) + -18368);
    R(10) = ld32(base, (f + 20));
    R(5) = (R(28) + 328);
    R(9) = ld32(base, (f + 24));
    R(8) = ld32(base, (f + 28));
    R(6) = ld32(base, (f + 12));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(28) + 344), R(30));
    st32(base, (R(3) + 12), R(29));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015B804u, 0x802DC780u, 0);
    R(11) = (f + 272);
    R(0) = lr;
}

/* fn_8015B930 (fn_8015B930, 48 bytes) */
static void pf_m_5b930(GM_CTX) {
    GM_FN(0x8015B930); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 272);
    GM_CALLV(0x8015B944u, 0x801628C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015B950; }
    GM_CALLV(0x8015B950u, 0x8015C130u, 0);
L_8015B950:;
    R(0) = lr;
}

/* fn_8015B960 (fn_8015B960, 4 bytes) */
static void pf_m_5b960(GM_CTX) {
    GM_TAIL(0x800067A0u, 0); return;
}

/* fn_8015B970 (fn_8015B970, 76 bytes) */
static void pf_m_5b970(GM_CTX) {
    GM_FN(0x8015B970); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(3) = (R(31) + 29440);
    GM_CALLV(0x8015B98Cu, 0x80160020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015B9A4; }
    R(3) = (R(31) + 29440);
    GM_CALLV(0x8015B99Cu, 0x8015FF40u, 0);
    R(3) = (0 + 1);
    goto L_8015B9A8;
L_8015B9A4:;
    R(3) = (0 + 0);
L_8015B9A8:;
    R(0) = lr;
}

/* fn_8015B9C0 (fn_8015B9C0, 76 bytes) */
static void pf_m_5b9c0(GM_CTX) {
    GM_FN(0x8015B9C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(3) = (R(31) + 29528);
    GM_CALLV(0x8015B9DCu, 0x80160020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015B9F4; }
    R(3) = (R(31) + 29528);
    GM_CALLV(0x8015B9ECu, 0x8015FF40u, 0);
    R(3) = (0 + 1);
    goto L_8015B9F8;
L_8015B9F4:;
    R(3) = (0 + 0);
L_8015B9F8:;
    R(0) = lr;
}

/* fn_8015BA10 (fn_8015BA10, 76 bytes) */
static void pf_m_5ba10(GM_CTX) {
    GM_FN(0x8015BA10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(3) = (R(31) + 29616);
    GM_CALLV(0x8015BA2Cu, 0x80160020u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BA44; }
    R(3) = (R(31) + 29616);
    GM_CALLV(0x8015BA3Cu, 0x8015FF40u, 0);
    R(3) = (0 + 1);
    goto L_8015BA48;
L_8015BA44:;
    R(3) = (0 + 0);
L_8015BA48:;
    R(0) = lr;
}

/* fn_8015BA60 (fn_8015BA60, 136 bytes) */
static void pf_m_5ba60(GM_CTX) {
    GM_FN(0x8015BA60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 7);
    GM_CALLV(0x8015BA74u, 0x8008F620u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8015BAD4; }
    R(3) = (0 + 5);
    GM_CALLV(0x8015BA84u, 0x8008F620u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8015BAD4; }
    R(3) = (0 + 6);
    GM_CALLV(0x8015BA94u, 0x8008F620u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8015BAD4; }
    R(3) = (0 + 9);
    GM_CALLV(0x8015BAA4u, 0x8008F620u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8015BAD4; }
    R(3) = (0 + 711);
    GM_CALLV(0x8015BAB4u, 0x8008F620u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8015BAD4; }
    R(3) = (0 + 8);
    GM_CALLV(0x8015BAC4u, 0x8008F620u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8015BAD4; }
    R(3) = (0 + 1);
    goto L_8015BAD8;
L_8015BAD4:;
    R(3) = (0 + 0);
L_8015BAD8:;
    R(0) = lr;
}

/* fn_8015BAF0 (fn_8015BAF0, 48 bytes) */
static void pf_m_5baf0(GM_CTX) {
    GM_FN(0x8015BAF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0);
    GM_CALLV(0x8015BB04u, 0x8008F620u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
    R(0) = lr;
}

/* fn_8015BB30 (fn_8015BB30, 48 bytes) */
static void pf_m_5bb30(GM_CTX) {
    GM_FN(0x8015BB30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 4);
    GM_CALLV(0x8015BB44u, 0x8008F620u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
    R(0) = lr;
}

/* fn_8015BB60 (fn_8015BB60, 48 bytes) */
static void pf_m_5bb60(GM_CTX) {
    GM_FN(0x8015BB60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 3);
    GM_CALLV(0x8015BB74u, 0x8008F620u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
    R(0) = lr;
}

/* fn_8015BB90 (fn_8015BB90, 48 bytes) */
static void pf_m_5bb90(GM_CTX) {
    GM_FN(0x8015BB90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 10);
    GM_CALLV(0x8015BBA4u, 0x8008F620u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
    R(0) = lr;
}

/* fn_8015BBC0 (fn_8015BBC0, 48 bytes) */
static void pf_m_5bbc0(GM_CTX) {
    GM_FN(0x8015BBC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 11);
    GM_CALLV(0x8015BBD4u, 0x8008F620u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
    R(0) = lr;
}

/* fn_8015BBF0 (fn_8015BBF0, 72 bytes) */
static void pf_m_5bbf0(GM_CTX) {
    GM_FN(0x8015BBF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 704);
    GM_CALLV(0x8015BC04u, 0x8008F620u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8015BC14; }
    R(3) = (0 + 0);
    goto L_8015BC28;
L_8015BC14:;
    R(3) = (0 + 741);
    GM_CALLV(0x8015BC1Cu, 0x8008F620u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
L_8015BC28:;
    R(0) = lr;
}

/* fn_8015BC40 (fn_8015BC40, 68 bytes) */
static void pf_m_5bc40(GM_CTX) {
    GM_FN(0x8015BC40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(31) = R(3) |R(3);
    R(3) = (0 + 620);
    R(4) = R(31) |R(31);
    GM_CALLV(0x8015BC68u, 0x80162B00u, 0);
    st32(base, (R(31) + 240), R(3));
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_8015BC90 (fn_8015BC90, 24 bytes) */
static void pf_m_5bc90(GM_CTX) {
    R(3) = ld32(base, (R(3) + 240));
    R(3) = ld8(base, (R(3) + 520));
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(3) = rotl32(R(0), 1) & 0x1u;
}

/* fn_8015BCB0 (fn_8015BCB0, 40 bytes) */
static void pf_m_5bcb0(GM_CTX) {
    GM_FN(0x8015BCB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x8015BCC0u, 0x8010D190u, 0);
    GM_CALLV(0x8015BCC4u, 0x8015BCE0u, 0);
    R(0) = lr;
    R(3) = (0 + 1);
}

/* fn_8015BCE0 (fn_8015BCE0, 16 bytes) */
static void pf_m_5bce0(GM_CTX) {
    R(3) = ld32(base, (R(13) + -21408));
    R(0) = (R(3) + 1);
    st32(base, (R(13) + -21408), R(0));
}

/* fn_8015BCF0 (fn_8015BCF0, 24 bytes) */
static void pf_m_5bcf0(GM_CTX) {
    R(4) = ld32(base, (R(13) + -22312));
    R(5) = (0 + 0x80160000u);
    R(5) = (R(5) + -18080);
    R(3) = (0 + 1);
    st32(base, (R(4) + 0), R(5));
}

/* fn_8015BD10 (fn_8015BD10, 36 bytes) */
static void pf_m_5bd10(GM_CTX) {
    GM_FN(0x8015BD10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x8015BD20u, 0x8006A280u, 0);
    R(0) = lr;
    R(3) = (0 + 1);
}

/* fn_8015BD40 (fn_8015BD40, 52 bytes) */
static void pf_m_5bd40(GM_CTX) {
    GM_FN(0x8015BD40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x80160000u);
    R(4) = (0 + 0);
    R(3) = (R(3) + -17136);
    GM_CALLV(0x8015BD5Cu, 0x8016B950u, 0);
    st32(base, (R(13) + -21296), R(3));
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_8015BD80 (fn_8015BD80, 80 bytes) */
static void pf_m_5bd80(GM_CTX) {
    GM_FN(0x8015BD80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -21296));
    R(0) = ld8(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015BDA4; }
    R(3) = (0 + 0);
    goto L_8015BDC0;
L_8015BDA4:;
    GM_CALLV(0x8015BDA8u, 0x8016B7E0u, 0);
    R(0) = (0 + 0);
    st32(base, (R(13) + -21296), R(0));
    R(3) = (0 + 1);
    GM_CALLV(0x8015BDB8u, 0x8006A6A0u, 0);
    GM_CALLV(0x8015BDBCu, 0x8006A6F0u, 0);
    R(3) = (0 + 1);
L_8015BDC0:;
    R(0) = lr;
}

/* fn_8015BDD0 (fn_8015BDD0, 72 bytes) */
static void pf_m_5bdd0(GM_CTX) {
    GM_FN(0x8015BDD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8015BDE8u, 0x8006A760u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BE00; }
    R(0) = (0 + 1);
    R(0) = R(0) | 0x0u;
    R(3) = (0 + 1);
    goto L_8015BE04;
L_8015BE00:;
    R(3) = (0 + 0);
L_8015BE04:;
    R(0) = lr;
}

/* fn_8015BE20 (fn_8015BE20, 64 bytes) */
static void pf_m_5be20(GM_CTX) {
    GM_FN(0x8015BE20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0);
    GM_CALLV(0x8015BE38u, 0x80109340u, 0);
    GM_CALLV(0x8015BE3Cu, 0x80109480u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BE48; }
    R(31) = (0 + 1);
L_8015BE48:;
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_8015BE60 (fn_8015BE60, 60 bytes) */
static void pf_m_5be60(GM_CTX) {
    GM_FN(0x8015BE60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80330000u);
    R(5) = (0 + 0x802F0000u);
    R(4) = (R(4) + -32608);
    R(5) = (R(5) + 23088);
    R(6) = (0 + 0);
    R(3) = ld32(base, (R(13) + -22088));
    GM_CALLV(0x8015BE88u, 0x800DF840u, 0);
    R(0) = lr;
    R(3) = (0 + 1);
}

/* fn_8015BEA0 (fn_8015BEA0, 60 bytes) */
static void pf_m_5bea0(GM_CTX) {
    GM_FN(0x8015BEA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80330000u);
    R(4) = (R(13) + -25224);
    R(5) = (R(5) + -32556);
    R(6) = (0 + 3);
    R(7) = (0 + 0);
    R(3) = ld32(base, (R(13) + -22088));
    GM_CALLV(0x8015BEC8u, 0x800DF7D0u, 0);
    R(0) = lr;
    R(3) = (0 + 1);
}

/* fn_8015BEE0 (fn_8015BEE0, 48 bytes) */
static void pf_m_5bee0(GM_CTX) {
    GM_FN(0x8015BEE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -22088));
    R(3) = (R(3) + 4);
    GM_CALLV(0x8015BEF8u, 0x800DF4E0u, 0);
    R(0) = cntlzw(R(3));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
    R(0) = lr;
}

/* fn_8015BF10 (fn_8015BF10, 64 bytes) */
static void pf_m_5bf10(GM_CTX) {
    GM_FN(0x8015BF10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -23104));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BF3C; }
    GM_CALLV(0x8015BF2Cu, 0x8001C240u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BF3C; }
    R(3) = (0 + 1);
    goto L_8015BF40;
L_8015BF3C:;
    R(3) = (0 + 0);
L_8015BF40:;
    R(0) = lr;
}

/* fn_8015BF50 (fn_8015BF50, 64 bytes) */
static void pf_m_5bf50(GM_CTX) {
    GM_FN(0x8015BF50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -23112));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BF7C; }
    GM_CALLV(0x8015BF6Cu, 0x8001BC60u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BF7C; }
    R(3) = (0 + 1);
    goto L_8015BF80;
L_8015BF7C:;
    R(3) = (0 + 0);
L_8015BF80:;
    R(0) = lr;
}

/* fn_8015BF90 (fn_8015BF90, 64 bytes) */
static void pf_m_5bf90(GM_CTX) {
    GM_FN(0x8015BF90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -23096));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BFBC; }
    GM_CALLV(0x8015BFACu, 0x8001C760u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BFBC; }
    R(3) = (0 + 1);
    goto L_8015BFC0;
L_8015BFBC:;
    R(3) = (0 + 0);
L_8015BFC0:;
    R(0) = lr;
}

/* fn_8015BFD0 (fn_8015BFD0, 64 bytes) */
static void pf_m_5bfd0(GM_CTX) {
    GM_FN(0x8015BFD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -23120));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BFFC; }
    GM_CALLV(0x8015BFECu, 0x8001B470u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015BFFC; }
    R(3) = (0 + 1);
    goto L_8015C000;
L_8015BFFC:;
    R(3) = (0 + 0);
L_8015C000:;
    R(0) = lr;
}

/* fn_8015C010 (fn_8015C010, 92 bytes) */
static void pf_m_5c010(GM_CTX) {
    GM_FN(0x8015C010); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(31) = R(3) |R(3);
    R(3) = (0 + 704);
    R(4) = R(31) |R(31);
    GM_CALLV(0x8015C038u, 0x80162B00u, 0);
    st32(base, (R(31) + 244), R(3));
    R(4) = R(31) |R(31);
    R(3) = (0 + 719);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    GM_CALLV(0x8015C050u, 0x80162B00u, 0);
    st32(base, (R(31) + 248), R(3));
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_8015C070 (fn_8015C070, 20 bytes) */
static void pf_m_5c070(GM_CTX) {
    R(3) = ld8(base, (R(13) + -21411));
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(3) = rotl32(R(0), 1) & 0x1u;
}

/* fn_8015C090 (fn_8015C090, 68 bytes) */
static void pf_m_5c090(GM_CTX) {
    GM_FN(0x8015C090); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(31) = R(3) |R(3);
    R(3) = (0 + 741);
    R(4) = R(31) |R(31);
    GM_CALLV(0x8015C0B8u, 0x80162B00u, 0);
    st32(base, (R(31) + 252), R(3));
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_8015C0E0 (fn_8015C0E0, 24 bytes) */
static void pf_m_5c0e0(GM_CTX) {
    R(3) = ld32(base, (R(3) + 252));
    R(3) = ld8(base, (R(3) + 520));
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(3) = rotl32(R(0), 1) & 0x1u;
}

/* fn_8015C100 (fn_8015C100, 48 bytes) */
static void pf_m_5c100(GM_CTX) {
    R(4) = ld32(base, (R(3) + 244));
    R(3) = ld32(base, (R(3) + 248));
    R(0) = ld8(base, (R(4) + 660));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015C120; }
    R(0) = ld8(base, (R(3) + 3384));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015C128; }
L_8015C120:;
    R(3) = (0 + 0);
    return;
L_8015C128:;
    R(3) = (0 + 1);
}

/* fn_8015C130 (fn_8015C130, 228 bytes) */
static void pf_m_5c130(GM_CTX) {
    GM_FN(0x8015C130); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(25) = R(3) |R(3);
    GM_CALLV(0x8015C14Cu, 0x800E19B0u, 0);
    R(3) = (0 + 0x80330000u);
    R(26) = (0 + 0x80330000u);
    R(27) = (0 + 0x80300000u);
    R(28) = (0 + 0x80330000u);
    R(29) = (0 + 0x80330000u);
    R(3) = (R(3) + -32384);
    R(26) = (R(26) + -32256);
    R(27) = (R(27) + -5384);
    R(28) = (R(28) + -32208);
    R(29) = (R(29) + -32184);
    R(30) = (0 + 0);
    R(6) = (0 + 0x80370000u);
    st32(base, (R(25) + 96), R(3));
    R(5) = (R(25) + 124);
    R(4) = (R(25) + 120);
    R(3) = (R(25) + 140);
    st32(base, (R(25) + 116), R(26));
    R(6) = (R(6) + 29896);
    st32(base, (R(25) + 120), R(27));
    st32(base, (R(25) + 124), R(28));
    st32(base, (R(25) + 128), R(29));
    st32(base, (R(25) + 132), R(25));
    st32(base, (R(25) + 136), R(30));
    GM_CALLV(0x8015C1ACu, 0x8015FC90u, 0);
    R(31) = (0 + 0x80330000u);
    R(6) = (0 + 0x80370000u);
    R(31) = (R(31) + -32304);
    st32(base, (R(25) + 116), R(31));
    R(5) = (R(25) + 184);
    R(4) = (R(25) + 180);
    st32(base, (R(25) + 176), R(26));
    R(3) = (R(25) + 200);
    R(6) = (R(6) + 29704);
    st32(base, (R(25) + 180), R(27));
    st32(base, (R(25) + 184), R(28));
    st32(base, (R(25) + 188), R(29));
    st32(base, (R(25) + 192), R(25));
    st32(base, (R(25) + 196), R(30));
    GM_CALLV(0x8015C1E8u, 0x8015FC90u, 0);
    R(0) = (R(13) + -21304);
    st32(base, (R(25) + 176), R(31));
    R(11) = (f + 48);
    R(3) = R(25) |R(25);
    st32(base, (R(25) + 112), R(0));
    st32(base, (R(13) + -21312), R(25));
    R(0) = lr;
}

/* fn_8015C370 (fn_8015C370, 156 bytes) */
static void pf_m_5c370(GM_CTX) {
    GM_FN(0x8015C370); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8015C3F0; }
    { uint32_t a_ = R(3); R(3) = a_ + 0xB0u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    R(0) = (0 + 0);
    st32(base, (R(13) + -21312), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8015C3B8; }
    if ((CR_BIT(ctx, 2))) { goto L_8015C3B8; }
    { uint32_t a_ = R(3); R(3) = a_ + 0x18u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8015C3B8; }
    R(4) = (0 + 0);
    GM_CALLV(0x8015C3B8u, 0x8015F9F0u, 0);
L_8015C3B8:;
    { uint32_t a_ = R(30); R(0) = a_ + 0x74u; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8015C3D4; }
    if ((CR_BIT(ctx, 2))) { goto L_8015C3D4; }
    { uint32_t a_ = R(0); R(3) = a_ + 0x18u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8015C3D4; }
    R(4) = (0 + 0);
    GM_CALLV(0x8015C3D4u, 0x8015F9F0u, 0);
L_8015C3D4:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x8015C3E0u, 0x800E1A20u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8015C3F0; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8015C3F0u, 0x80162920u, 0);
L_8015C3F0:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_8015C410 (fn_8015C410, 156 bytes) */
static void pf_m_5c410(GM_CTX) {
    GM_FN(0x8015C410); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + 255);
    R(31) = R(3) |R(3);
    R(3) = (f + 8);
    st32(base, (f + 8), R(0));
    GM_CALLV(0x8015C434u, 0x800E4850u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x8015C43Cu, 0x800E4830u, 0);
    R(3) = (0 + 30);
    GM_CALLV(0x8015C444u, 0x800E1F50u, 0);
    R(3) = (0 + 30);
    GM_CALLV(0x8015C44Cu, 0x800E1F60u, 0);
    GM_CALLV(0x8015C450u, 0x800B2E70u, 0);
    R(3) = (0 + 20);
    GM_CALLV(0x8015C458u, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015C464; }
    GM_CALLV(0x8015C464u, 0x800DF680u, 0);
L_8015C464:;
    R(3) = (0 + 2908);
    GM_CALLV(0x8015C46Cu, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015C478; }
    GM_CALLV(0x8015C478u, 0x800BB090u, 0);
L_8015C478:;
    GM_CALLV(0x8015C47Cu, 0x801025C0u, 0);
    GM_CALLV(0x8015C480u, 0x800B2FB0u, 0);
    R(0) = (0 + 0);
    st8(base, (R(31) + 260), R(0));
    R(3) = (0 + 1);
    st8(base, (R(31) + 261), R(0));
    GM_CALLV(0x8015C494u, 0x801BE2F0u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_8015C4B0 (fn_8015C4B0, 16 bytes) */
static void pf_m_5c4b0(GM_CTX) {
    R(3) = ld32(base, (R(13) + -22312));
    R(0) = (0 + 0);
    st32(base, (R(3) + 0), R(0));
}

/* fn_8015C4C0 (fn_8015C4C0, 148 bytes) */
static void pf_m_5c4c0(GM_CTX) {
    GM_FN(0x8015C4C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = R(3) |R(3);
    R(3) = (R(13) + -21288);
    GM_CALLV(0x8015C4D8u, 0x8015F620u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8015C4E8; }
    R(3) = (0 + 0);
    goto L_8015C544;
L_8015C4E8:;
    GM_CALLV(0x8015C4ECu, 0x80107F10u, 0);
    GM_CALLV(0x8015C4F0u, 0x80108150u, 0);
    R(0) = (0 + 0);
    st8(base, (R(13) + -30480), R(0));
    R(3) = (0 + 30);
    GM_CALLV(0x8015C500u, 0x800E1F50u, 0);
    R(3) = (0 + 30);
    GM_CALLV(0x8015C508u, 0x800E1F60u, 0);
    R(3) = (0 + 704);
    GM_CALLV(0x8015C510u, 0x8008F610u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015C520; }
    R(3) = (0 + 0);
    goto L_8015C544;
L_8015C520:;
    R(3) = (0 + 741);
    GM_CALLV(0x8015C528u, 0x8008F610u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015C538; }
    R(3) = (0 + 0);
    goto L_8015C544;
L_8015C538:;
    R(3) = (0 + 0);
    GM_CALLV(0x8015C540u, 0x800E5060u, 0);
    R(3) = (0 + 1);
L_8015C544:;
    R(0) = lr;
}

/* fn_8015C560 (fn_8015C560, 64 bytes) */
static void pf_m_5c560(GM_CTX) {
    GM_FN(0x8015C560); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x8015C570u, 0x800E1BE0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015C580; }
    R(3) = (0 + 0);
    goto L_8015C590;
L_8015C580:;
    GM_CALLV(0x8015C584u, 0x80107F10u, 0);
    R(4) = (0 + 1);
    GM_CALLV(0x8015C58Cu, 0x80108170u, 0);
    R(3) = (0 + 1);
L_8015C590:;
    R(0) = lr;
}

/* fn_8015C5A0 (fn_8015C5A0, 108 bytes) */
static void pf_m_5c5a0(GM_CTX) {
    GM_FN(0x8015C5A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = (R(13) + -21288);
    R(4) = R(31) |R(31);
    GM_CALLV(0x8015C5C0u, 0x8015F620u, 0);
    R(12) = ld32(base, (R(31) + 176));
    R(3) = (R(31) + 176);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x8015C5D4u, ctx->ctr, 0);
    R(0) = ld8(base, (R(31) + 259));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015C5F4; }
    R(12) = ld32(base, (R(31) + 116));
    R(3) = (R(31) + 116);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x8015C5F4u, ctx->ctr, 0);
L_8015C5F4:;
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_8015C610 (fn_8015C610, 16 bytes) */
static void pf_m_5c610(GM_CTX) {
    { uint32_t ea_ = R(3) + 24; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8015C620 (fn_8015C620, 8 bytes) */
static void pf_m_5c620(GM_CTX) {
    R(3) = (0 + 1);
}

/* fn_8015C630 (fn_8015C630, 72 bytes) */
static void pf_m_5c630(GM_CTX) {
    GM_FN(0x8015C630); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -21648); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    st8(base, (R(3) + 259), R(0));
    R(3) = ld32(base, (R(3) + 240));
    R(31) = ld32(base, (R(3) + 500));
    R(3) = ld32(base, (R(31) + 0));
    GM_CALLV(0x8015C65Cu, 0x801637D0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8015C664u, 0x801644D0u, 0);
    R(0) = lr;
}

/* fn_8015C680 (fn_8015C680, 100 bytes) */
static void pf_m_5c680(GM_CTX) {
    GM_FN(0x8015C680); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8015C698u, 0x80107F10u, 0);
    R(0) = ld32(base, (R(3) + 40));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8015C6D0; }
    GM_CALLV(0x8015C6A8u, 0x80109340u, 0);
    R(0) = ld32(base, (R(3) + 472));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 29768);
    R(0) = R(0) | 0x40u;
    st32(base, (R(3) + 472), R(0));
    R(3) = (R(31) + 176);
    R(12) = ld32(base, (R(31) + 176));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x8015C6D0u, ctx->ctr, 0);
L_8015C6D0:;
    R(0) = lr;
}

/* fn_8015C6F0 (fn_8015C6F0, 16 bytes) */
static void pf_m_5c6f0(GM_CTX) {
    { uint32_t ea_ = R(3) + 24; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8015CCB0 (fn_8015CCB0, 4 bytes) */
static void pf_m_5ccb0(GM_CTX) {

}

/* fn_8015CCC0 (fn_8015CCC0, 104 bytes) */
static void pf_m_5ccc0(GM_CTX) {
    GM_FN(0x8015CCC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -21056));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x8015CCE8u, ctx->ctr, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8015CD14; }
    R(12) = ld32(base, (R(31) + 116));
    R(4) = (0 + 0x80370000u);
    R(3) = (R(31) + 116);
    R(12) = ld32(base, (R(12) + 24));
    R(4) = (R(4) + 29960);
    ctx->ctr = R(12);
    GM_CALLV(0x8015CD14u, ctx->ctr, 0);
L_8015CD14:;
    R(0) = lr;
}

/* fn_8015CD30 (fn_8015CD30, 4 bytes) */
static void pf_m_5cd30(GM_CTX) {

}

/* fn_8015CD40 (fn_8015CD40, 80 bytes) */
static void pf_m_5cd40(GM_CTX) {
    GM_FN(0x8015CD40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 1200);
    { uint32_t ea_ = (R(2) + -21648); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 60);
    st32(base, (R(3) + 264), R(4));
    R(4) = ld32(base, (R(3) + 240));
    st32(base, (R(3) + 268), R(0));
    R(31) = ld32(base, (R(4) + 500));
    R(3) = ld32(base, (R(31) + 0));
    GM_CALLV(0x8015CD74u, 0x801637D0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8015CD7Cu, 0x801644D0u, 0);
    R(0) = lr;
}

/* fn_8015CD90 (fn_8015CD90, 56 bytes) */
static void pf_m_5cd90(GM_CTX) {
    R(4) = ld32(base, (R(3) + 268));
    R(5) = ld32(base, (R(3) + 264));
    { uint32_t a_ = R(4); R(0) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    st32(base, (R(3) + 268), R(0));
    R(0) = (R(5) + -1);
    st32(base, (R(3) + 264), R(0));
    if ((CR_BIT(ctx, 1))) return;
    { uint32_t ea_ = R(3) + 116; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 30024);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8015CDD0 (fn_8015CDD0, 4 bytes) */
static void pf_m_5cdd0(GM_CTX) {

}

/* fn_8015CDE0 (fn_8015CDE0, 4 bytes) */
static void pf_m_5cde0(GM_CTX) {

}

/* fn_8015CDF0 (fn_8015CDF0, 128 bytes) */
static void pf_m_5cdf0(GM_CTX) {
    GM_FN(0x8015CDF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 264));
    { uint32_t a_ = R(4); R(0) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    st32(base, (R(3) + 264), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_8015CE40; }
    R(3) = ld32(base, (R(13) + -21016));
    R(4) = (0 + 32543);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 32));
    ctx->ctr = R(12);
    GM_CALLV(0x8015CE2Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015CE40; }
    R(0) = ld32(base, (R(13) + -22272));
    R(0) = R(0) & 0x80000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8015CE5C; }
L_8015CE40:;
    R(12) = ld32(base, (R(31) + 116));
    R(4) = (0 + 0x80370000u);
    R(3) = (R(31) + 116);
    R(12) = ld32(base, (R(12) + 24));
    R(4) = (R(4) + 30088);
    ctx->ctr = R(12);
    GM_CALLV(0x8015CE5Cu, ctx->ctr, 0);
L_8015CE5C:;
    R(0) = lr;
}

/* fn_8015CE70 (fn_8015CE70, 4 bytes) */
static void pf_m_5ce70(GM_CTX) {

}

/* fn_8015CE80 (fn_8015CE80, 80 bytes) */
static void pf_m_5ce80(GM_CTX) {
    GM_FN(0x8015CE80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0);
    R(0) = (0 + 0);
    st8(base, (R(13) + -28484), R(0));
    GM_CALLV(0x8015CE9Cu, 0x800B0DB0u, 0);
    R(3) = (0 + 30);
    GM_CALLV(0x8015CEA4u, 0x800B0A90u, 0);
    GM_CALLV(0x8015CEA8u, 0x80109340u, 0);
    R(0) = ld32(base, (R(3) + 472));
    R(0) = R(0) | 0x40u;
    st32(base, (R(3) + 472), R(0));
    GM_CALLV(0x8015CEB8u, 0x80107F10u, 0);
    R(4) = (0 + 1);
    GM_CALLV(0x8015CEC0u, 0x80108160u, 0);
    R(0) = lr;
}

/* fn_8015CED0 (fn_8015CED0, 136 bytes) */
static void pf_m_5ced0(GM_CTX) {
    GM_FN(0x8015CED0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -21056));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x8015CEF8u, ctx->ctr, 0);
    R(0) = cntlzw(R(3));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8015CF44; }
    R(3) = ld32(base, (R(31) + 252));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015CF44; }
    R(0) = ld8(base, (R(3) + 520));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015CF44; }
    R(5) = ld32(base, (R(31) + 240));
    R(0) = (0 + 0);
    R(4) = (0 + 0x80370000u);
    R(3) = (R(31) + 116);
    st8(base, (R(5) + 521), R(0));
    R(4) = (R(4) + 30152);
    R(12) = ld32(base, (R(31) + 116));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x8015CF44u, ctx->ctr, 0);
L_8015CF44:;
    R(0) = lr;
}

/* fn_8015CF60 (fn_8015CF60, 12 bytes) */
static void pf_m_5cf60(GM_CTX) {
    R(3) = ld32(base, (R(13) + -21416));
    R(4) = (0 + 0);
    GM_TAIL(0x8010E490u, 0); return;
}

/* fn_8015CF70 (fn_8015CF70, 68 bytes) */
static void pf_m_5cf70(GM_CTX) {
    GM_FN(0x8015CF70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = (0 + 0);
    GM_CALLV(0x8015CF8Cu, 0x800B0DB0u, 0);
    R(3) = (0 + 30);
    GM_CALLV(0x8015CF94u, 0x800B0A20u, 0);
    R(3) = ld32(base, (R(31) + 252));
    R(0) = (0 + 1);
    st8(base, (R(3) + 521), R(0));
    R(0) = lr;
}

/* fn_8015CFC0 (fn_8015CFC0, 104 bytes) */
static void pf_m_5cfc0(GM_CTX) {
    GM_FN(0x8015CFC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -21056));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x8015CFE8u, ctx->ctr, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8015D014; }
    R(12) = ld32(base, (R(31) + 116));
    R(4) = (0 + 0x80370000u);
    R(3) = (R(31) + 116);
    R(12) = ld32(base, (R(12) + 24));
    R(4) = (R(4) + 30216);
    ctx->ctr = R(12);
    GM_CALLV(0x8015D014u, ctx->ctr, 0);
L_8015D014:;
    R(0) = lr;
}

/* fn_8015D030 (fn_8015D030, 68 bytes) */
static void pf_m_5d030(GM_CTX) {
    GM_FN(0x8015D030); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + 1);
    st8(base, (R(13) + -28484), R(0));
    GM_CALLV(0x8015D048u, 0x80109340u, 0);
    R(0) = ld32(base, (R(3) + 472));
    R(0) = R(0) & 0xFFFFFFBFu;
    st32(base, (R(3) + 472), R(0));
    GM_CALLV(0x8015D058u, 0x80107F10u, 0);
    R(4) = (0 + 0);
    GM_CALLV(0x8015D060u, 0x80108160u, 0);
    GM_CALLV(0x8015D064u, 0x8015D080u, 0);
    R(0) = lr;
}

/* fn_8015D080 (fn_8015D080, 24 bytes) */
static void pf_m_5d080(GM_CTX) {
    R(3) = ld32(base, (R(13) + -21408));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) return;
    R(0) = (R(3) + -1);
    st32(base, (R(13) + -21408), R(0));
}

/* fn_8015D0A0 (fn_8015D0A0, 72 bytes) */
static void pf_m_5d0a0(GM_CTX) {
    GM_FN(0x8015D0A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8015D0B8u, 0x80109340u, 0);
    R(5) = ld32(base, (R(3) + 472));
    R(4) = (0 + 300);
    R(0) = (0 + 30);
    R(5) = R(5) & 0xFFFFFFF7u;
    st32(base, (R(3) + 472), R(5));
    st32(base, (R(31) + 264), R(4));
    st32(base, (R(31) + 268), R(0));
    R(0) = lr;
}

/* fn_8015D0F0 (fn_8015D0F0, 80 bytes) */
static void pf_m_5d0f0(GM_CTX) {
    R(4) = ld32(base, (R(3) + 264));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8015D104; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 264), R(0));
L_8015D104:;
    R(4) = ld32(base, (R(3) + 268));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8015D118; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 268), R(0));
L_8015D118:;
    R(0) = ld8(base, (R(3) + 258));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) return;
    { uint32_t ea_ = R(3) + 116; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 30280);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8015D140 (fn_8015D140, 4 bytes) */
static void pf_m_5d140(GM_CTX) {

}

/* fn_8015D150 (fn_8015D150, 4 bytes) */
static void pf_m_5d150(GM_CTX) {

}

/* fn_8015D160 (fn_8015D160, 76 bytes) */
static void pf_m_5d160(GM_CTX) {
    R(4) = ld32(base, (R(3) + 264));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8015D174; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 264), R(0));
L_8015D174:;
    R(4) = ld32(base, (R(3) + 268));
    { uint32_t a_ = R(4); R(0) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    st32(base, (R(3) + 268), R(0));
    if ((CR_BIT(ctx, 1))) return;
    R(5) = ld32(base, (R(3) + 252));
    R(0) = (0 + 1);
    R(4) = (0 + 0x80370000u);
    st32(base, (R(5) + 524), R(0));
    R(4) = (R(4) + 30344);
    { uint32_t ea_ = R(3) + 116; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8015D1B0 (fn_8015D1B0, 4 bytes) */
static void pf_m_5d1b0(GM_CTX) {

}

/* fn_8015D1C0 (fn_8015D1C0, 4 bytes) */
static void pf_m_5d1c0(GM_CTX) {

}

/* fn_8015D1D0 (fn_8015D1D0, 164 bytes) */
static void pf_m_5d1d0(GM_CTX) {
    GM_FN(0x8015D1D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 264));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015D1F8; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 264), R(0));
L_8015D1F8:;
    R(3) = ld32(base, (R(13) + -21016));
    R(4) = (0 + 32543);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 32));
    ctx->ctr = R(12);
    GM_CALLV(0x8015D210u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015D224; }
    R(0) = ld32(base, (R(13) + -22272));
    R(0) = R(0) & 0x80000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8015D238; }
L_8015D224:;
    R(3) = ld32(base, (R(31) + 252));
    R(4) = (0 + 4);
    R(0) = (0 + 0);
    st32(base, (R(3) + 524), R(4));
    st32(base, (R(31) + 264), R(0));
L_8015D238:;
    R(0) = ld32(base, (R(31) + 264));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 1))) { goto L_8015D260; }
    R(12) = ld32(base, (R(31) + 116));
    R(4) = (0 + 0x80370000u);
    R(3) = (R(31) + 116);
    R(12) = ld32(base, (R(12) + 24));
    R(4) = (R(4) + 30408);
    ctx->ctr = R(12);
    GM_CALLV(0x8015D260u, ctx->ctr, 0);
L_8015D260:;
    R(0) = lr;
}

/* fn_8015D280 (fn_8015D280, 4 bytes) */
static void pf_m_5d280(GM_CTX) {

}

/* fn_8015D290 (fn_8015D290, 4 bytes) */
static void pf_m_5d290(GM_CTX) {

}

/* fn_8015D2A0 (fn_8015D2A0, 128 bytes) */
static void pf_m_5d2a0(GM_CTX) {
    GM_FN(0x8015D2A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(13) + -22216));
    R(0) = ld32(base, (R(4) + 116));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015D30C; }
    GM_CALLV(0x8015D2C8u, 0x80107F10u, 0);
    R(0) = ld32(base, (R(3) + 12));
    R(4) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    if ((CR_BIT(ctx, 2))) { goto L_8015D2E4; }
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    if ((!CR_BIT(ctx, 2))) { goto L_8015D2E8; }
L_8015D2E4:;
    R(4) = (0 + 1);
L_8015D2E8:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015D30C; }
    R(12) = ld32(base, (R(31) + 116));
    R(4) = (0 + 0x80370000u);
    R(3) = (R(31) + 116);
    R(12) = ld32(base, (R(12) + 24));
    R(4) = (R(4) + 30472);
    ctx->ctr = R(12);
    GM_CALLV(0x8015D30Cu, ctx->ctr, 0);
L_8015D30C:;
    R(0) = lr;
}

/* fn_8015D320 (fn_8015D320, 4 bytes) */
static void pf_m_5d320(GM_CTX) {

}

/* fn_8015D330 (fn_8015D330, 84 bytes) */
static void pf_m_5d330(GM_CTX) {
    GM_FN(0x8015D330); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x8015D348u, 0x80109340u, 0);
    R(0) = ld32(base, (R(3) + 472));
    R(0) = R(0) | 0x40u;
    st32(base, (R(3) + 472), R(0));
    GM_CALLV(0x8015D358u, 0x80107F10u, 0);
    R(4) = (0 + 1);
    GM_CALLV(0x8015D360u, 0x80108160u, 0);
    R(3) = ld32(base, (R(13) + -22216));
    GM_CALLV(0x8015D368u, 0x800CEE20u, 0);
    R(0) = (0 + 0);
    st8(base, (R(31) + 256), R(0));
    R(0) = lr;
}

/* fn_8015D390 (fn_8015D390, 4 bytes) */
static void pf_m_5d390(GM_CTX) {

}

/* fn_8015D3A0 (fn_8015D3A0, 180 bytes) */
static void pf_m_5d3a0(GM_CTX) {
    GM_FN(0x8015D3A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(31) = (R(31) + 29424);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x8015D3C8u, 0x800E0450u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015D43C; }
    R(3) = ld32(base, (R(13) + -22216));
    R(0) = ld32(base, (R(3) + 120));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015D3FC; }
    R(12) = ld32(base, (R(30) + 116));
    R(3) = (R(30) + 116);
    R(4) = (R(31) + 1304);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x8015D3F8u, ctx->ctr, 0);
    goto L_8015D43C;
L_8015D3FC:;
    R(0) = ld8(base, (R(3) + 124));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015D424; }
    R(12) = ld32(base, (R(30) + 116));
    R(3) = (R(30) + 116);
    R(4) = (R(31) + 1240);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x8015D420u, ctx->ctr, 0);
    goto L_8015D43C;
L_8015D424:;
    R(12) = ld32(base, (R(30) + 116));
    R(3) = (R(30) + 116);
    R(4) = (R(31) + 1112);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x8015D43Cu, ctx->ctr, 0);
L_8015D43C:;
    R(0) = lr;
}

/* fn_8015D640 (fn_8015D640, 8 bytes) */
static void pf_m_5d640(GM_CTX) {
    R(3) = ld32(base, (R(13) + -22080));
    GM_TAIL(0x800E1680u, 0); return;
}

/* fn_8015D650 (fn_8015D650, 160 bytes) */
static void pf_m_5d650(GM_CTX) {
    GM_FN(0x8015D650); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x8015D66Cu, 0x800E0450u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015D6DC; }
    R(3) = ld32(base, (R(13) + -22216));
    R(0) = ld32(base, (R(3) + 120));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8015D6A4; }
    R(12) = ld32(base, (R(31) + 116));
    R(4) = (0 + 0x80370000u);
    R(3) = (R(31) + 116);
    R(12) = ld32(base, (R(12) + 24));
    R(4) = (R(4) + 30728);
    ctx->ctr = R(12);
    GM_CALLV(0x8015D6A0u, ctx->ctr, 0);
    goto L_8015D6DC;
L_8015D6A4:;
    GM_CALLV(0x8015D6A8u, 0x80109340u, 0);
    R(0) = ld32(base, (R(3) + 472));
    R(0) = R(0) & 0xFFFFFFBFu;
    st32(base, (R(3) + 472), R(0));
    GM_CALLV(0x8015D6B8u, 0x80107F10u, 0);
    R(4) = (0 + 0);
    GM_CALLV(0x8015D6C0u, 0x80108160u, 0);
    R(12) = ld32(base, (R(31) + 116));
    R(4) = (0 + 0x80370000u);
    R(3) = (R(31) + 116);
    R(12) = ld32(base, (R(12) + 24));
    R(4) = (R(4) + 31048);
    ctx->ctr = R(12);
    GM_CALLV(0x8015D6DCu, ctx->ctr, 0);
L_8015D6DC:;
    R(0) = lr;
}

/* fn_8015D6F0 (fn_8015D6F0, 4 bytes) */
static void pf_m_5d6f0(GM_CTX) {

}

/* fn_8015D700 (fn_8015D700, 4 bytes) */
static void pf_m_5d700(GM_CTX) {

}

/* fn_8015DC40 (fn_8015DC40, 96 bytes) */
static void pf_m_5dc40(GM_CTX) {
    GM_FN(0x8015DC40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(31) + 0));
    R(12) = ld32(base, (R(12) + 12));
    ctx->ctr = R(12);
    GM_CALLV(0x8015DC70u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8015DC84; }
    st32(base, (R(30) + 12), R(31));
    R(3) = (R(30) + 4);
    goto L_8015DC88;
L_8015DC84:;
    R(3) = (0 + 0);
L_8015DC88:;
    R(0) = lr;
}

/* fn_8015DCA0 (fn_8015DCA0, 12 bytes) */
static void pf_m_5dca0(GM_CTX) {
    R(0) = (0 + 0);
    st32(base, (R(4) + 0), R(0));
}

/* fn_8015DCB0 (fn_8015DCB0, 28 bytes) */
static void pf_m_5dcb0(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 8));
    R(4) = ld32(base, (R(4) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8015DCD0 (fn_8015DCD0, 28 bytes) */
static void pf_m_5dcd0(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 8));
    R(4) = ld32(base, (R(4) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 44));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8015DCF0 (fn_8015DCF0, 28 bytes) */
static void pf_m_5dcf0(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 8));
    R(4) = ld32(base, (R(4) + 4));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 48));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_8015DDD0 (fn_8015DDD0, 4716 bytes) */
static void pf_m_5ddd0(GM_CTX) {
    GM_FN(0x8015DDD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 896);
    R(29) = (0 + 0x80370000u);
    R(28) = (0 + 0x80330000u);
    R(29) = (R(29) + 29424);
    R(4) = (R(13) + -25216);
    R(28) = (R(28) + -32624);
    R(5) = (0 + 0);
    R(3) = (R(29) + 16);
    GM_CALLV(0x8015DE04u, 0x8008F870u, 0);
    R(27) = (0 + 0x80090000u);
    R(3) = (R(29) + 16);
    R(4) = (R(27) + -2032);
    R(5) = (R(29) + 0);
    GM_CALLV(0x8015DE18u, 0x802DC780u, 0);
    R(3) = (R(29) + 104);
    R(4) = (R(28) + 1456);
    R(5) = (0 + 0);
    GM_CALLV(0x8015DE28u, 0x8008F870u, 0);
    R(3) = (R(29) + 104);
    R(4) = (R(27) + -2032);
    R(5) = (R(29) + 88);
    GM_CALLV(0x8015DE38u, 0x802DC780u, 0);
    R(3) = (R(29) + 192);
    R(4) = (R(28) + 1468);
    R(5) = (0 + 0);
    GM_CALLV(0x8015DE48u, 0x8008F870u, 0);
    R(3) = (R(29) + 192);
    R(4) = (R(27) + -2032);
    R(5) = (R(29) + 176);
    GM_CALLV(0x8015DE58u, 0x802DC780u, 0);
    R(4) = (R(28) + 0);
    R(3) = (R(13) + -21304);
    R(5) = (0 + 3);
    GM_CALLV(0x8015DE68u, 0x8015F600u, 0);
    R(4) = (R(28) + 80);
    R(3) = (R(13) + -21288);
    R(5) = (0 + 32);
    GM_CALLV(0x8015DE78u, 0x8015F600u, 0);
    R(3) = (R(28) + 592);
    R(6) = (R(28) + 604);
    R(5) = (R(28) + 616);
    R(27) = ld32(base, (R(28) + 592));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1480);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 280);
    R(10) = ld32(base, (R(28) + 604));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 616));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 836), R(27));
    st32(base, (f + 840), R(12));
    st32(base, (f + 844), R(11));
    st32(base, (f + 848), R(10));
    st32(base, (f + 852), R(9));
    st32(base, (f + 856), R(8));
    st32(base, (f + 860), R(7));
    st32(base, (f + 864), R(6));
    st32(base, (f + 868), R(0));
    GM_CALLV(0x8015DED8u, 0x8015F7C0u, 0);
    R(30) = (0 + 0x80330000u);
    R(3) = (R(29) + 280);
    R(27) = ld32(base, (f + 860));
    R(30) = (R(30) + -30236);
    R(12) = ld32(base, (f + 864));
    R(31) = (0 + 0x80160000u);
    R(11) = ld32(base, (f + 868));
    R(4) = (R(31) + -4032);
    R(10) = ld32(base, (f + 848));
    R(5) = (R(29) + 264);
    R(9) = ld32(base, (f + 852));
    R(8) = ld32(base, (f + 856));
    R(7) = ld32(base, (f + 836));
    R(6) = ld32(base, (f + 840));
    R(0) = ld32(base, (f + 844));
    st32(base, (R(29) + 280), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015DF40u, 0x802DC780u, 0);
    R(3) = (R(28) + 628);
    R(6) = (R(28) + 640);
    R(5) = (R(28) + 652);
    R(27) = ld32(base, (R(28) + 628));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1512);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 344);
    R(10) = ld32(base, (R(28) + 640));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 652));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 800), R(27));
    st32(base, (f + 804), R(12));
    st32(base, (f + 808), R(11));
    st32(base, (f + 812), R(10));
    st32(base, (f + 816), R(9));
    st32(base, (f + 820), R(8));
    st32(base, (f + 824), R(7));
    st32(base, (f + 828), R(6));
    st32(base, (f + 832), R(0));
    GM_CALLV(0x8015DFA0u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 344);
    R(27) = ld32(base, (f + 824));
    R(12) = ld32(base, (f + 828));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 832));
    R(5) = (R(29) + 328);
    R(10) = ld32(base, (f + 812));
    R(9) = ld32(base, (f + 816));
    R(8) = ld32(base, (f + 820));
    R(7) = ld32(base, (f + 800));
    R(6) = ld32(base, (f + 804));
    R(0) = ld32(base, (f + 808));
    st32(base, (R(29) + 344), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015DFFCu, 0x802DC780u, 0);
    R(3) = (R(28) + 664);
    R(6) = (R(28) + 676);
    R(5) = (R(28) + 688);
    R(27) = ld32(base, (R(28) + 664));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1544);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 408);
    R(10) = ld32(base, (R(28) + 676));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 688));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 764), R(27));
    st32(base, (f + 768), R(12));
    st32(base, (f + 772), R(11));
    st32(base, (f + 776), R(10));
    st32(base, (f + 780), R(9));
    st32(base, (f + 784), R(8));
    st32(base, (f + 788), R(7));
    st32(base, (f + 792), R(6));
    st32(base, (f + 796), R(0));
    GM_CALLV(0x8015E05Cu, 0x8015F7C0u, 0);
    R(3) = (R(29) + 408);
    R(27) = ld32(base, (f + 788));
    R(12) = ld32(base, (f + 792));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 796));
    R(5) = (R(29) + 392);
    R(10) = ld32(base, (f + 776));
    R(9) = ld32(base, (f + 780));
    R(8) = ld32(base, (f + 784));
    R(7) = ld32(base, (f + 764));
    R(6) = ld32(base, (f + 768));
    R(0) = ld32(base, (f + 772));
    st32(base, (R(29) + 408), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E0B8u, 0x802DC780u, 0);
    R(3) = (R(28) + 700);
    R(6) = (R(28) + 712);
    R(5) = (R(28) + 724);
    R(27) = ld32(base, (R(28) + 700));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1576);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 472);
    R(10) = ld32(base, (R(28) + 712));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 724));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 728), R(27));
    st32(base, (f + 732), R(12));
    st32(base, (f + 736), R(11));
    st32(base, (f + 740), R(10));
    st32(base, (f + 744), R(9));
    st32(base, (f + 748), R(8));
    st32(base, (f + 752), R(7));
    st32(base, (f + 756), R(6));
    st32(base, (f + 760), R(0));
    GM_CALLV(0x8015E118u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 472);
    R(27) = ld32(base, (f + 752));
    R(12) = ld32(base, (f + 756));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 760));
    R(5) = (R(29) + 456);
    R(10) = ld32(base, (f + 740));
    R(9) = ld32(base, (f + 744));
    R(8) = ld32(base, (f + 748));
    R(7) = ld32(base, (f + 728));
    R(6) = ld32(base, (f + 732));
    R(0) = ld32(base, (f + 736));
    st32(base, (R(29) + 472), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E174u, 0x802DC780u, 0);
    R(3) = (R(28) + 736);
    R(6) = (R(28) + 748);
    R(5) = (R(28) + 760);
    R(27) = ld32(base, (R(28) + 736));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1608);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 536);
    R(10) = ld32(base, (R(28) + 748));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 760));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 692), R(27));
    st32(base, (f + 696), R(12));
    st32(base, (f + 700), R(11));
    st32(base, (f + 704), R(10));
    st32(base, (f + 708), R(9));
    st32(base, (f + 712), R(8));
    st32(base, (f + 716), R(7));
    st32(base, (f + 720), R(6));
    st32(base, (f + 724), R(0));
    GM_CALLV(0x8015E1D4u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 536);
    R(27) = ld32(base, (f + 716));
    R(12) = ld32(base, (f + 720));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 724));
    R(5) = (R(29) + 520);
    R(10) = ld32(base, (f + 704));
    R(9) = ld32(base, (f + 708));
    R(8) = ld32(base, (f + 712));
    R(7) = ld32(base, (f + 692));
    R(6) = ld32(base, (f + 696));
    R(0) = ld32(base, (f + 700));
    st32(base, (R(29) + 536), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E230u, 0x802DC780u, 0);
    R(3) = (R(28) + 772);
    R(6) = (R(28) + 784);
    R(5) = (R(28) + 796);
    R(27) = ld32(base, (R(28) + 772));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1644);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 600);
    R(10) = ld32(base, (R(28) + 784));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 796));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 656), R(27));
    st32(base, (f + 660), R(12));
    st32(base, (f + 664), R(11));
    st32(base, (f + 668), R(10));
    st32(base, (f + 672), R(9));
    st32(base, (f + 676), R(8));
    st32(base, (f + 680), R(7));
    st32(base, (f + 684), R(6));
    st32(base, (f + 688), R(0));
    GM_CALLV(0x8015E290u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 600);
    R(27) = ld32(base, (f + 680));
    R(12) = ld32(base, (f + 684));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 688));
    R(5) = (R(29) + 584);
    R(10) = ld32(base, (f + 668));
    R(9) = ld32(base, (f + 672));
    R(8) = ld32(base, (f + 676));
    R(7) = ld32(base, (f + 656));
    R(6) = ld32(base, (f + 660));
    R(0) = ld32(base, (f + 664));
    st32(base, (R(29) + 600), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E2ECu, 0x802DC780u, 0);
    R(3) = (R(28) + 808);
    R(6) = (R(28) + 820);
    R(5) = (R(28) + 832);
    R(27) = ld32(base, (R(28) + 808));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1684);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 664);
    R(10) = ld32(base, (R(28) + 820));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 832));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 620), R(27));
    st32(base, (f + 624), R(12));
    st32(base, (f + 628), R(11));
    st32(base, (f + 632), R(10));
    st32(base, (f + 636), R(9));
    st32(base, (f + 640), R(8));
    st32(base, (f + 644), R(7));
    st32(base, (f + 648), R(6));
    st32(base, (f + 652), R(0));
    GM_CALLV(0x8015E34Cu, 0x8015F7C0u, 0);
    R(3) = (R(29) + 664);
    R(27) = ld32(base, (f + 644));
    R(12) = ld32(base, (f + 648));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 652));
    R(5) = (R(29) + 648);
    R(10) = ld32(base, (f + 632));
    R(9) = ld32(base, (f + 636));
    R(8) = ld32(base, (f + 640));
    R(7) = ld32(base, (f + 620));
    R(6) = ld32(base, (f + 624));
    R(0) = ld32(base, (f + 628));
    st32(base, (R(29) + 664), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E3A8u, 0x802DC780u, 0);
    R(3) = (R(28) + 844);
    R(6) = (R(28) + 856);
    R(5) = (R(28) + 868);
    R(27) = ld32(base, (R(28) + 844));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1720);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 728);
    R(10) = ld32(base, (R(28) + 856));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 868));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 584), R(27));
    st32(base, (f + 588), R(12));
    st32(base, (f + 592), R(11));
    st32(base, (f + 596), R(10));
    st32(base, (f + 600), R(9));
    st32(base, (f + 604), R(8));
    st32(base, (f + 608), R(7));
    st32(base, (f + 612), R(6));
    st32(base, (f + 616), R(0));
    GM_CALLV(0x8015E408u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 728);
    R(27) = ld32(base, (f + 608));
    R(12) = ld32(base, (f + 612));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 616));
    R(5) = (R(29) + 712);
    R(10) = ld32(base, (f + 596));
    R(9) = ld32(base, (f + 600));
    R(8) = ld32(base, (f + 604));
    R(7) = ld32(base, (f + 584));
    R(6) = ld32(base, (f + 588));
    R(0) = ld32(base, (f + 592));
    st32(base, (R(29) + 728), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E464u, 0x802DC780u, 0);
    R(3) = (R(28) + 880);
    R(6) = (R(28) + 892);
    R(5) = (R(28) + 904);
    R(27) = ld32(base, (R(28) + 880));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1768);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 792);
    R(10) = ld32(base, (R(28) + 892));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 904));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 548), R(27));
    st32(base, (f + 552), R(12));
    st32(base, (f + 556), R(11));
    st32(base, (f + 560), R(10));
    st32(base, (f + 564), R(9));
    st32(base, (f + 568), R(8));
    st32(base, (f + 572), R(7));
    st32(base, (f + 576), R(6));
    st32(base, (f + 580), R(0));
    GM_CALLV(0x8015E4C4u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 792);
    R(27) = ld32(base, (f + 572));
    R(12) = ld32(base, (f + 576));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 580));
    R(5) = (R(29) + 776);
    R(10) = ld32(base, (f + 560));
    R(9) = ld32(base, (f + 564));
    R(8) = ld32(base, (f + 568));
    R(7) = ld32(base, (f + 548));
    R(6) = ld32(base, (f + 552));
    R(0) = ld32(base, (f + 556));
    st32(base, (R(29) + 792), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E520u, 0x802DC780u, 0);
    R(3) = (R(28) + 916);
    R(6) = (R(28) + 928);
    R(5) = (R(28) + 940);
    R(27) = ld32(base, (R(28) + 916));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1824);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 856);
    R(10) = ld32(base, (R(28) + 928));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 940));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 512), R(27));
    st32(base, (f + 516), R(12));
    st32(base, (f + 520), R(11));
    st32(base, (f + 524), R(10));
    st32(base, (f + 528), R(9));
    st32(base, (f + 532), R(8));
    st32(base, (f + 536), R(7));
    st32(base, (f + 540), R(6));
    st32(base, (f + 544), R(0));
    GM_CALLV(0x8015E580u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 856);
    R(27) = ld32(base, (f + 536));
    R(12) = ld32(base, (f + 540));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 544));
    R(5) = (R(29) + 840);
    R(10) = ld32(base, (f + 524));
    R(9) = ld32(base, (f + 528));
    R(8) = ld32(base, (f + 532));
    R(7) = ld32(base, (f + 512));
    R(6) = ld32(base, (f + 516));
    R(0) = ld32(base, (f + 520));
    st32(base, (R(29) + 856), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E5DCu, 0x802DC780u, 0);
    R(3) = (R(28) + 952);
    R(6) = (R(28) + 964);
    R(5) = (R(28) + 976);
    R(27) = ld32(base, (R(28) + 952));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1872);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 920);
    R(10) = ld32(base, (R(28) + 964));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 976));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 476), R(27));
    st32(base, (f + 480), R(12));
    st32(base, (f + 484), R(11));
    st32(base, (f + 488), R(10));
    st32(base, (f + 492), R(9));
    st32(base, (f + 496), R(8));
    st32(base, (f + 500), R(7));
    st32(base, (f + 504), R(6));
    st32(base, (f + 508), R(0));
    GM_CALLV(0x8015E63Cu, 0x8015F7C0u, 0);
    R(3) = (R(29) + 920);
    R(27) = ld32(base, (f + 500));
    R(12) = ld32(base, (f + 504));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 508));
    R(5) = (R(29) + 904);
    R(10) = ld32(base, (f + 488));
    R(9) = ld32(base, (f + 492));
    R(8) = ld32(base, (f + 496));
    R(7) = ld32(base, (f + 476));
    R(6) = ld32(base, (f + 480));
    R(0) = ld32(base, (f + 484));
    st32(base, (R(29) + 920), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E698u, 0x802DC780u, 0);
    R(3) = (R(28) + 988);
    R(6) = (R(28) + 1000);
    R(5) = (R(28) + 1012);
    R(27) = ld32(base, (R(28) + 988));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1924);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 984);
    R(10) = ld32(base, (R(28) + 1000));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1012));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 440), R(27));
    st32(base, (f + 444), R(12));
    st32(base, (f + 448), R(11));
    st32(base, (f + 452), R(10));
    st32(base, (f + 456), R(9));
    st32(base, (f + 460), R(8));
    st32(base, (f + 464), R(7));
    st32(base, (f + 468), R(6));
    st32(base, (f + 472), R(0));
    GM_CALLV(0x8015E6F8u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 984);
    R(27) = ld32(base, (f + 464));
    R(12) = ld32(base, (f + 468));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 472));
    R(5) = (R(29) + 968);
    R(10) = ld32(base, (f + 452));
    R(9) = ld32(base, (f + 456));
    R(8) = ld32(base, (f + 460));
    R(7) = ld32(base, (f + 440));
    R(6) = ld32(base, (f + 444));
    R(0) = ld32(base, (f + 448));
    st32(base, (R(29) + 984), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E754u, 0x802DC780u, 0);
    R(3) = (R(28) + 1024);
    R(6) = (R(28) + 1036);
    R(5) = (R(28) + 1048);
    R(27) = ld32(base, (R(28) + 1024));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 1964);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1048);
    R(10) = ld32(base, (R(28) + 1036));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1048));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 404), R(27));
    st32(base, (f + 408), R(12));
    st32(base, (f + 412), R(11));
    st32(base, (f + 416), R(10));
    st32(base, (f + 420), R(9));
    st32(base, (f + 424), R(8));
    st32(base, (f + 428), R(7));
    st32(base, (f + 432), R(6));
    st32(base, (f + 436), R(0));
    GM_CALLV(0x8015E7B4u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1048);
    R(27) = ld32(base, (f + 428));
    R(12) = ld32(base, (f + 432));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 436));
    R(5) = (R(29) + 1032);
    R(10) = ld32(base, (f + 416));
    R(9) = ld32(base, (f + 420));
    R(8) = ld32(base, (f + 424));
    R(7) = ld32(base, (f + 404));
    R(6) = ld32(base, (f + 408));
    R(0) = ld32(base, (f + 412));
    st32(base, (R(29) + 1048), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E810u, 0x802DC780u, 0);
    R(3) = (R(28) + 1060);
    R(6) = (R(28) + 1072);
    R(5) = (R(28) + 1084);
    R(27) = ld32(base, (R(28) + 1060));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2000);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1112);
    R(10) = ld32(base, (R(28) + 1072));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1084));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 368), R(27));
    st32(base, (f + 372), R(12));
    st32(base, (f + 376), R(11));
    st32(base, (f + 380), R(10));
    st32(base, (f + 384), R(9));
    st32(base, (f + 388), R(8));
    st32(base, (f + 392), R(7));
    st32(base, (f + 396), R(6));
    st32(base, (f + 400), R(0));
    GM_CALLV(0x8015E870u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1112);
    R(27) = ld32(base, (f + 392));
    R(12) = ld32(base, (f + 396));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 400));
    R(5) = (R(29) + 1096);
    R(10) = ld32(base, (f + 380));
    R(9) = ld32(base, (f + 384));
    R(8) = ld32(base, (f + 388));
    R(7) = ld32(base, (f + 368));
    R(6) = ld32(base, (f + 372));
    R(0) = ld32(base, (f + 376));
    st32(base, (R(29) + 1112), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E8CCu, 0x802DC780u, 0);
    R(3) = (R(28) + 1096);
    R(6) = (R(28) + 1108);
    R(5) = (R(28) + 1120);
    R(27) = ld32(base, (R(28) + 1096));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2036);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1176);
    R(10) = ld32(base, (R(28) + 1108));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1120));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 332), R(27));
    st32(base, (f + 336), R(12));
    st32(base, (f + 340), R(11));
    st32(base, (f + 344), R(10));
    st32(base, (f + 348), R(9));
    st32(base, (f + 352), R(8));
    st32(base, (f + 356), R(7));
    st32(base, (f + 360), R(6));
    st32(base, (f + 364), R(0));
    GM_CALLV(0x8015E92Cu, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1176);
    R(27) = ld32(base, (f + 356));
    R(12) = ld32(base, (f + 360));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 364));
    R(5) = (R(29) + 1160);
    R(10) = ld32(base, (f + 344));
    R(9) = ld32(base, (f + 348));
    R(8) = ld32(base, (f + 352));
    R(7) = ld32(base, (f + 332));
    R(6) = ld32(base, (f + 336));
    R(0) = ld32(base, (f + 340));
    st32(base, (R(29) + 1176), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015E988u, 0x802DC780u, 0);
    R(3) = (R(28) + 1132);
    R(6) = (R(28) + 1144);
    R(5) = (R(28) + 1156);
    R(27) = ld32(base, (R(28) + 1132));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2072);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1240);
    R(10) = ld32(base, (R(28) + 1144));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1156));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 296), R(27));
    st32(base, (f + 300), R(12));
    st32(base, (f + 304), R(11));
    st32(base, (f + 308), R(10));
    st32(base, (f + 312), R(9));
    st32(base, (f + 316), R(8));
    st32(base, (f + 320), R(7));
    st32(base, (f + 324), R(6));
    st32(base, (f + 328), R(0));
    GM_CALLV(0x8015E9E8u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1240);
    R(27) = ld32(base, (f + 320));
    R(12) = ld32(base, (f + 324));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 328));
    R(5) = (R(29) + 1224);
    R(10) = ld32(base, (f + 308));
    R(9) = ld32(base, (f + 312));
    R(8) = ld32(base, (f + 316));
    R(7) = ld32(base, (f + 296));
    R(6) = ld32(base, (f + 300));
    R(0) = ld32(base, (f + 304));
    st32(base, (R(29) + 1240), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015EA44u, 0x802DC780u, 0);
    R(3) = (R(28) + 1168);
    R(6) = (R(28) + 1180);
    R(5) = (R(28) + 1192);
    R(27) = ld32(base, (R(28) + 1168));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2096);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1304);
    R(10) = ld32(base, (R(28) + 1180));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1192));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 260), R(27));
    st32(base, (f + 264), R(12));
    st32(base, (f + 268), R(11));
    st32(base, (f + 272), R(10));
    st32(base, (f + 276), R(9));
    st32(base, (f + 280), R(8));
    st32(base, (f + 284), R(7));
    st32(base, (f + 288), R(6));
    st32(base, (f + 292), R(0));
    GM_CALLV(0x8015EAA4u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1304);
    R(27) = ld32(base, (f + 284));
    R(12) = ld32(base, (f + 288));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 292));
    R(5) = (R(29) + 1288);
    R(10) = ld32(base, (f + 272));
    R(9) = ld32(base, (f + 276));
    R(8) = ld32(base, (f + 280));
    R(7) = ld32(base, (f + 260));
    R(6) = ld32(base, (f + 264));
    R(0) = ld32(base, (f + 268));
    st32(base, (R(29) + 1304), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015EB00u, 0x802DC780u, 0);
    R(3) = (R(28) + 1204);
    R(6) = (R(28) + 1216);
    R(5) = (R(28) + 1228);
    R(27) = ld32(base, (R(28) + 1204));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2132);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1368);
    R(10) = ld32(base, (R(28) + 1216));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1228));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 224), R(27));
    st32(base, (f + 228), R(12));
    st32(base, (f + 232), R(11));
    st32(base, (f + 236), R(10));
    st32(base, (f + 240), R(9));
    st32(base, (f + 244), R(8));
    st32(base, (f + 248), R(7));
    st32(base, (f + 252), R(6));
    st32(base, (f + 256), R(0));
    GM_CALLV(0x8015EB60u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1368);
    R(27) = ld32(base, (f + 248));
    R(12) = ld32(base, (f + 252));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 256));
    R(5) = (R(29) + 1352);
    R(10) = ld32(base, (f + 236));
    R(9) = ld32(base, (f + 240));
    R(8) = ld32(base, (f + 244));
    R(7) = ld32(base, (f + 224));
    R(6) = ld32(base, (f + 228));
    R(0) = ld32(base, (f + 232));
    st32(base, (R(29) + 1368), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015EBBCu, 0x802DC780u, 0);
    R(3) = (R(28) + 1240);
    R(6) = (R(28) + 1252);
    R(5) = (R(28) + 1264);
    R(27) = ld32(base, (R(28) + 1240));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2168);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1432);
    R(10) = ld32(base, (R(28) + 1252));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1264));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 188), R(27));
    st32(base, (f + 192), R(12));
    st32(base, (f + 196), R(11));
    st32(base, (f + 200), R(10));
    st32(base, (f + 204), R(9));
    st32(base, (f + 208), R(8));
    st32(base, (f + 212), R(7));
    st32(base, (f + 216), R(6));
    st32(base, (f + 220), R(0));
    GM_CALLV(0x8015EC1Cu, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1432);
    R(27) = ld32(base, (f + 212));
    R(12) = ld32(base, (f + 216));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 220));
    R(5) = (R(29) + 1416);
    R(10) = ld32(base, (f + 200));
    R(9) = ld32(base, (f + 204));
    R(8) = ld32(base, (f + 208));
    R(7) = ld32(base, (f + 188));
    R(6) = ld32(base, (f + 192));
    R(0) = ld32(base, (f + 196));
    st32(base, (R(29) + 1432), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015EC78u, 0x802DC780u, 0);
    R(3) = (R(28) + 1276);
    R(6) = (R(28) + 1288);
    R(5) = (R(28) + 1300);
    R(27) = ld32(base, (R(28) + 1276));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2204);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1496);
    R(10) = ld32(base, (R(28) + 1288));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1300));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 152), R(27));
    st32(base, (f + 156), R(12));
    st32(base, (f + 160), R(11));
    st32(base, (f + 164), R(10));
    st32(base, (f + 168), R(9));
    st32(base, (f + 172), R(8));
    st32(base, (f + 176), R(7));
    st32(base, (f + 180), R(6));
    st32(base, (f + 184), R(0));
    GM_CALLV(0x8015ECD8u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1496);
    R(27) = ld32(base, (f + 176));
    R(12) = ld32(base, (f + 180));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 184));
    R(5) = (R(29) + 1480);
    R(10) = ld32(base, (f + 164));
    R(9) = ld32(base, (f + 168));
    R(8) = ld32(base, (f + 172));
    R(7) = ld32(base, (f + 152));
    R(6) = ld32(base, (f + 156));
    R(0) = ld32(base, (f + 160));
    st32(base, (R(29) + 1496), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015ED34u, 0x802DC780u, 0);
    R(3) = (R(28) + 1312);
    R(6) = (R(28) + 1324);
    R(5) = (R(28) + 1336);
    R(27) = ld32(base, (R(28) + 1312));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2240);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1560);
    R(10) = ld32(base, (R(28) + 1324));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1336));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 116), R(27));
    st32(base, (f + 120), R(12));
    st32(base, (f + 124), R(11));
    st32(base, (f + 128), R(10));
    st32(base, (f + 132), R(9));
    st32(base, (f + 136), R(8));
    st32(base, (f + 140), R(7));
    st32(base, (f + 144), R(6));
    st32(base, (f + 148), R(0));
    GM_CALLV(0x8015ED94u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1560);
    R(27) = ld32(base, (f + 140));
    R(12) = ld32(base, (f + 144));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 148));
    R(5) = (R(29) + 1544);
    R(10) = ld32(base, (f + 128));
    R(9) = ld32(base, (f + 132));
    R(8) = ld32(base, (f + 136));
    R(7) = ld32(base, (f + 116));
    R(6) = ld32(base, (f + 120));
    R(0) = ld32(base, (f + 124));
    st32(base, (R(29) + 1560), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015EDF0u, 0x802DC780u, 0);
    R(3) = (R(28) + 1348);
    R(6) = (R(28) + 1360);
    R(5) = (R(28) + 1372);
    R(27) = ld32(base, (R(28) + 1348));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2276);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1624);
    R(10) = ld32(base, (R(28) + 1360));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1372));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 80), R(27));
    st32(base, (f + 84), R(12));
    st32(base, (f + 88), R(11));
    st32(base, (f + 92), R(10));
    st32(base, (f + 96), R(9));
    st32(base, (f + 100), R(8));
    st32(base, (f + 104), R(7));
    st32(base, (f + 108), R(6));
    st32(base, (f + 112), R(0));
    GM_CALLV(0x8015EE50u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1624);
    R(27) = ld32(base, (f + 104));
    R(12) = ld32(base, (f + 108));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 112));
    R(5) = (R(29) + 1608);
    R(10) = ld32(base, (f + 92));
    R(9) = ld32(base, (f + 96));
    R(8) = ld32(base, (f + 100));
    R(7) = ld32(base, (f + 80));
    R(6) = ld32(base, (f + 84));
    R(0) = ld32(base, (f + 88));
    st32(base, (R(29) + 1624), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015EEACu, 0x802DC780u, 0);
    R(3) = (R(28) + 1384);
    R(6) = (R(28) + 1396);
    R(5) = (R(28) + 1408);
    R(27) = ld32(base, (R(28) + 1384));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2304);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1688);
    R(10) = ld32(base, (R(28) + 1396));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1408));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 44), R(27));
    st32(base, (f + 48), R(12));
    st32(base, (f + 52), R(11));
    st32(base, (f + 56), R(10));
    st32(base, (f + 60), R(9));
    st32(base, (f + 64), R(8));
    st32(base, (f + 68), R(7));
    st32(base, (f + 72), R(6));
    st32(base, (f + 76), R(0));
    GM_CALLV(0x8015EF0Cu, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1688);
    R(27) = ld32(base, (f + 68));
    R(12) = ld32(base, (f + 72));
    R(4) = (R(31) + -4032);
    R(11) = ld32(base, (f + 76));
    R(5) = (R(29) + 1672);
    R(10) = ld32(base, (f + 56));
    R(9) = ld32(base, (f + 60));
    R(8) = ld32(base, (f + 64));
    R(7) = ld32(base, (f + 44));
    R(6) = ld32(base, (f + 48));
    R(0) = ld32(base, (f + 52));
    st32(base, (R(29) + 1688), R(30));
    st32(base, (R(3) + 12), R(27));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015EF68u, 0x802DC780u, 0);
    R(3) = (R(28) + 1420);
    R(6) = (R(28) + 1432);
    R(5) = (R(28) + 1444);
    R(27) = ld32(base, (R(28) + 1420));
    R(12) = ld32(base, (R(3) + 4));
    R(4) = (R(28) + 2348);
    R(11) = ld32(base, (R(3) + 8));
    R(3) = (R(29) + 1752);
    R(10) = ld32(base, (R(28) + 1432));
    R(9) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(7) = ld32(base, (R(28) + 1444));
    R(6) = ld32(base, (R(5) + 4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (f + 8), R(27));
    st32(base, (f + 12), R(12));
    st32(base, (f + 16), R(11));
    st32(base, (f + 20), R(10));
    st32(base, (f + 24), R(9));
    st32(base, (f + 28), R(8));
    st32(base, (f + 32), R(7));
    st32(base, (f + 36), R(6));
    st32(base, (f + 40), R(0));
    GM_CALLV(0x8015EFC8u, 0x8015F7C0u, 0);
    R(3) = (R(29) + 1752);
    R(28) = ld32(base, (f + 32));
    R(12) = ld32(base, (f + 36));
    R(7) = R(27) |R(27);
    R(11) = ld32(base, (f + 40));
    R(4) = (R(31) + -4032);
    R(10) = ld32(base, (f + 20));
    R(5) = (R(29) + 1736);
    R(9) = ld32(base, (f + 24));
    R(8) = ld32(base, (f + 28));
    R(6) = ld32(base, (f + 12));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(29) + 1752), R(30));
    st32(base, (R(3) + 12), R(28));
    st32(base, (R(3) + 16), R(12));
    st32(base, (R(3) + 20), R(11));
    st32(base, (R(3) + 24), R(10));
    st32(base, (R(3) + 28), R(9));
    st32(base, (R(3) + 32), R(8));
    st32(base, (R(3) + 36), R(7));
    st32(base, (R(3) + 40), R(6));
    st32(base, (R(3) + 44), R(0));
    GM_CALLV(0x8015F024u, 0x802DC780u, 0);
    R(11) = (f + 896);
    R(0) = lr;
}

/* fn_8015F3B0 (fn_8015F3B0, 4 bytes) */
static void pf_m_5f3b0(GM_CTX) {
    GM_TAIL(0x8015F3C0u, 0); return;
}

/* fn_8015F410 (fn_8015F410, 4 bytes) */
static void pf_m_5f410(GM_CTX) {
    GM_TAIL(0x8015F420u, 0); return;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_PF_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_PF_COUNT)
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(setHeadID__11dMarioMdl_cFQ211dMarioMdl_c10HeadType_e, 4) { pf_setHeadID__11dMarioMdl_cFQ211dMarioMdl_c_caa10(GM_PASS); }
E(fn_800CAA70, 4) { pf_m_caa70(GM_PASS); }
E(fn_800CAB00, 4) { pf_m_cab00(GM_PASS); }
E(fn_800CAB10, 4) { pf_m_cab10(GM_PASS); }
E(fn_800CAD20, 4) { pf_m_cad20(GM_PASS); }
E(fn_800CAE70, 4) { pf_m_cae70(GM_PASS); }
E(fn_800CAFD0, 4) { pf_m_cafd0(GM_PASS); }
E(fn_800CB050, 4) { pf_m_cb050(GM_PASS); }
E(fn_800CB080, 4) { pf_m_cb080(GM_PASS); }
E(fn_800CB0F0, 4) { pf_m_cb0f0(GM_PASS); }
E(fn_800CB470, 4) { pf_m_cb470(GM_PASS); }
E(fn_800CB490, 4) { pf_m_cb490(GM_PASS); }
E(fn_800CB5B0, 4) { pf_m_cb5b0(GM_PASS); }
E(fn_800CB5D0, 4) { pf_m_cb5d0(GM_PASS); }
E(fn_800CB630, 4) { pf_m_cb630(GM_PASS); }
E(fn_800CB670, 4) { pf_m_cb670(GM_PASS); }
E(fn_800CB740, 4) { pf_m_cb740(GM_PASS); }
E(fn_800CB760, 4) { pf_m_cb760(GM_PASS); }
E(fn_800CB780, 4) { pf_m_cb780(GM_PASS); }
E(fn_800CB7E0, 4) { pf_m_cb7e0(GM_PASS); }
E(fn_800CB7F0, 4) { pf_m_cb7f0(GM_PASS); }
E(fn_800CB800, 4) { pf_m_cb800(GM_PASS); }
E(fn_800CB810, 4) { pf_m_cb810(GM_PASS); }
E(fn_800CB8A0, 4) { pf_m_cb8a0(GM_PASS); }
E(fn_800CBAE0, 4) { pf_m_cbae0(GM_PASS); }
E(fn_800CBD20, 4) { pf_m_cbd20(GM_PASS); }
E(fn_800CBF60, 4) { pf_m_cbf60(GM_PASS); }
E(fn_800CBFA0, 4) { pf_m_cbfa0(GM_PASS); }
E(fn_800CC050, 4) { pf_m_cc050(GM_PASS); }
E(fn_800CC090, 4) { pf_m_cc090(GM_PASS); }
E(fn_800CC250, 4) { pf_m_cc250(GM_PASS); }
E(fn_800CC2A0, 4) { pf_m_cc2a0(GM_PASS); }
E(fn_800CC350, 4) { pf_m_cc350(GM_PASS); }
E(fn_800CC390, 4) { pf_m_cc390(GM_PASS); }
E(fn_800CC860, 4) { pf_m_cc860(GM_PASS); }
E(fn_800CC8E0, 4) { pf_m_cc8e0(GM_PASS); }
E(fn_800CC9A0, 4) { pf_m_cc9a0(GM_PASS); }
E(set__5dPc_cFP8dActor_cUc, 4) { pf_set__5dPc_cFP8dActor_cUc_d1500(GM_PASS); }
E(check__5dPc_cFi, 4) { pf_check__5dPc_cFi_d1510(GM_PASS); }
E(chkTimer__5dPc_cFv, 4) { pf_chkTimer__5dPc_cFv_d1640(GM_PASS); }
E(fn_800D16B0, 4) { pf_m_d16b0(GM_PASS); }
E(fn_800D19E0, 4) { pf_m_d19e0(GM_PASS); }
E(fn_800D1DC0, 4) { pf_m_d1dc0(GM_PASS); }
E(move__5dPc_cFf, 4) { pf_move__5dPc_cFf_d1f10(GM_PASS); }
E(fn_800D2060, 4) { pf_m_d2060(GM_PASS); }
E(release__5dPc_cFv, 4) { pf_release__5dPc_cFv_d2200(GM_PASS); }
E(getAngle__5dPc_cCFv, 4) { pf_getAngle__5dPc_cCFv_d2270(GM_PASS); }
E(fn_800D23B0, 4) { pf_m_d23b0(GM_PASS); }
E(fn_800D2400, 4) { pf_m_d2400(GM_PASS); }
E(fn_800D2510, 4) { pf_m_d2510(GM_PASS); }
E(fn_800D2690, 4) { pf_m_d2690(GM_PASS); }
E(fn_800D27B0, 4) { pf_m_d27b0(GM_PASS); }
E(fn_800D29F0, 4) { pf_m_d29f0(GM_PASS); }
E(fn_800D2AC0, 4) { pf_m_d2ac0(GM_PASS); }
E(fn_800D2B90, 4) { pf_m_d2b90(GM_PASS); }
E(fn_800D2C20, 4) { pf_m_d2c20(GM_PASS); }
E(setEffect__14dPyEffectMng_cFQ211dPyEffect_c6Type_eR7mVec3_cfUc, 4) { pf_setEffect__14dPyEffectMng_cFQ211dPyEffec_d2cf0(GM_PASS); }
E(fn_800D2D80, 4) { pf_m_d2d80(GM_PASS); }
E(fn_800D2DD0, 4) { pf_m_d2dd0(GM_PASS); }
E(fn_800D3030, 4) { pf_m_d3030(GM_PASS); }
E(fn_800D3070, 4) { pf_m_d3070(GM_PASS); }
E(fn_800D30E0, 4) { pf_m_d30e0(GM_PASS); }
E(fn_800D3210, 4) { pf_m_d3210(GM_PASS); }
E(fn_800D3280, 4) { pf_m_d3280(GM_PASS); }
E(fn_800D3380, 4) { pf_m_d3380(GM_PASS); }
E(fn_800D36E0, 4) { pf_m_d36e0(GM_PASS); }
E(fn_800D3830, 4) { pf_m_d3830(GM_PASS); }
E(fn_800D38A0, 4) { pf_m_d38a0(GM_PASS); }
E(fn_800D3A30, 4) { pf_m_d3a30(GM_PASS); }
E(fn_800D3AD0, 4) { pf_m_d3ad0(GM_PASS); }
E(fn_800D3B20, 4) { pf_m_d3b20(GM_PASS); }
E(fn_800D3BF0, 4) { pf_m_d3bf0(GM_PASS); }
E(fn_800D3C80, 4) { pf_m_d3c80(GM_PASS); }
E(fn_800D3CB0, 4) { pf_m_d3cb0(GM_PASS); }
E(fn_800D3CE0, 4) { pf_m_d3ce0(GM_PASS); }
E(fn_800D3EF0, 4) { pf_m_d3ef0(GM_PASS); }
E(fn_800D4060, 4) { pf_m_d4060(GM_PASS); }
E(fn_800D40F0, 4) { pf_m_d40f0(GM_PASS); }
E(fn_800D4240, 4) { pf_m_d4240(GM_PASS); }
E(fn_800D43E0, 4) { pf_m_d43e0(GM_PASS); }
E(fn_800D4520, 4) { pf_m_d4520(GM_PASS); }
E(fn_800D4660, 4) { pf_m_d4660(GM_PASS); }
E(fn_800D4670, 4) { pf_m_d4670(GM_PASS); }
E(fn_800D4790, 4) { pf_m_d4790(GM_PASS); }
E(fn_800D4980, 4) { pf_m_d4980(GM_PASS); }
E(fn_800D4CD0, 4) { pf_m_d4cd0(GM_PASS); }
E(fn_800D4D80, 4) { pf_m_d4d80(GM_PASS); }
E(fn_800D4E90, 4) { pf_m_d4e90(GM_PASS); }
E(fn_800D5060, 4) { pf_m_d5060(GM_PASS); }
E(fn_800D5170, 4) { pf_m_d5170(GM_PASS); }
E(fn_800D5330, 4) { pf_m_d5330(GM_PASS); }
E(fn_800D54A0, 4) { pf_m_d54a0(GM_PASS); }
E(fn_800D54E0, 4) { pf_m_d54e0(GM_PASS); }
E(fn_800D5580, 4) { pf_m_d5580(GM_PASS); }
E(fn_800D5640, 4) { pf_m_d5640(GM_PASS); }
E(fn_800D5680, 4) { pf_m_d5680(GM_PASS); }
E(fn_800D56F0, 4) { pf_m_d56f0(GM_PASS); }
E(fn_800D5730, 4) { pf_m_d5730(GM_PASS); }
E(getJointPos__12dPyMdlBase_cFP7mVec3_ci, 4) { pf_getJointPos__12dPyMdlBase_cFP7mVec3_ci_d5790(GM_PASS); }
E(fn_800D57F0, 4) { pf_m_d57f0(GM_PASS); }
E(fn_800D5B90, 4) { pf_m_d5b90(GM_PASS); }
E(fn_800D5BE0, 4) { pf_m_d5be0(GM_PASS); }
E(fn_800D5C10, 4) { pf_m_d5c10(GM_PASS); }
E(fn_800D5C80, 4) { pf_m_d5c80(GM_PASS); }
E(fn_800D5C90, 4) { pf_m_d5c90(GM_PASS); }
E(fn_800D5D00, 4) { pf_m_d5d00(GM_PASS); }
E(setJumpAnmRand__12dPyMdlBase_cFQ212dPyMdlBase_c9RndType_e, 4) { pf_setJumpAnmRand__12dPyMdlBase_cFQ212dPyMd_d5d10(GM_PASS); }
E(fn_800D6200, 4) { pf_m_d6200(GM_PASS); }
E(fn_800D62F0, 4) { pf_m_d62f0(GM_PASS); }
E(fn_800D6460, 4) { pf_m_d6460(GM_PASS); }
E(fn_800D6550, 4) { pf_m_d6550(GM_PASS); }
E(fn_800D65E0, 4) { pf_m_d65e0(GM_PASS); }
E(fn_800D6840, 4) { pf_m_d6840(GM_PASS); }
E(fn_800D6930, 4) { pf_m_d6930(GM_PASS); }
E(fn_800D69B0, 4) { pf_m_d69b0(GM_PASS); }
E(fn_800D6A30, 4) { pf_m_d6a30(GM_PASS); }
E(isFootStepTiming__12dPyMdlBase_cFv, 4) { pf_isFootStepTiming__12dPyMdlBase_cFv_d6ab0(GM_PASS); }
E(play__11dPyMdlMng_cFv, 4) { pf_play__11dPyMdlMng_cFv_d6e90(GM_PASS); }
E(calc__11dPyMdlMng_cFR6mMtx_c, 4) { pf_calc__11dPyMdlMng_cFR6mMtx_c_d6eb0(GM_PASS); }
E(calc__11dPyMdlMng_cF7mVec3_c7mAng3_c7mVec3_c, 4) { pf_calc__11dPyMdlMng_cF7mVec3_c7mAng3_c7mVe_d6f40(GM_PASS); }
E(calc2__11dPyMdlMng_cFv, 4) { pf_calc2__11dPyMdlMng_cFv_d7000(GM_PASS); }
E(fn_800D7050, 4) { pf_m_d7050(GM_PASS); }
E(__ct__18dPlayerOrchestra_cFv, 4) { pf___ct__18dPlayerOrchestra_cFv_d70a0(GM_PASS); }
E(init__18dPlayerOrchestra_cFi, 4) { pf_init__18dPlayerOrchestra_cFi_d70c0(GM_PASS); }
E(fn_800D7350, 4) { pf_m_d7350(GM_PASS); }
E(fn_800D7480, 4) { pf_m_d7480(GM_PASS); }
E(fn_800D74C0, 4) { pf_m_d74c0(GM_PASS); }
E(fn_800D7780, 4) { pf_m_d7780(GM_PASS); }
E(fn_800D77D0, 4) { pf_m_d77d0(GM_PASS); }
E(fn_800D7820, 4) { pf_m_d7820(GM_PASS); }
E(fn_800D7880, 4) { pf_m_d7880(GM_PASS); }
E(fn_800D79B0, 4) { pf_m_d79b0(GM_PASS); }
E(fn_800D79E0, 4) { pf_m_d79e0(GM_PASS); }
E(fn_800D79F0, 4) { pf_m_d79f0(GM_PASS); }
E(fn_800D7A00, 4) { pf_m_d7a00(GM_PASS); }
E(fn_800D7A90, 4) { pf_m_d7a90(GM_PASS); }
E(fn_800D7AA0, 4) { pf_m_d7aa0(GM_PASS); }
E(fn_800D7AB0, 4) { pf_m_d7ab0(GM_PASS); }
E(fn_800D7B00, 4) { pf_m_d7b00(GM_PASS); }
E(fn_800D7B10, 4) { pf_m_d7b10(GM_PASS); }
E(fn_800D7B20, 4) { pf_m_d7b20(GM_PASS); }
E(fn_800D7B80, 4) { pf_m_d7b80(GM_PASS); }
E(fn_800D7BA0, 4) { pf_m_d7ba0(GM_PASS); }
E(fn_800D7BB0, 4) { pf_m_d7bb0(GM_PASS); }
E(fn_800D7C80, 4) { pf_m_d7c80(GM_PASS); }
E(fn_800D80B0, 4) { pf_m_d80b0(GM_PASS); }
E(fn_800D80D0, 4) { pf_m_d80d0(GM_PASS); }
E(fn_800D81D0, 4) { pf_m_d81d0(GM_PASS); }
E(__ct__14dPropelParts_cFv, 4) { pf___ct__14dPropelParts_cFv_d81e0(GM_PASS); }
E(create__14dPropelParts_cFP8dActor_c, 4) { pf_create__14dPropelParts_cFP8dActor_c_d8280(GM_PASS); }
E(update__14dPropelParts_cFRC6mMtx_c, 4) { pf_update__14dPropelParts_cFRC6mMtx_c_d82a0(GM_PASS); }
E(fn_8014A6F0, 4) { pf_m_4a6f0(GM_PASS); }
E(fn_8014A960, 4) { pf_m_4a960(GM_PASS); }
E(fn_8014AAF0, 4) { pf_m_4aaf0(GM_PASS); }
E(fn_8014ABF0, 4) { pf_m_4abf0(GM_PASS); }
E(fn_8014AC00, 4) { pf_m_4ac00(GM_PASS); }
E(fn_8014AC10, 4) { pf_m_4ac10(GM_PASS); }
E(fn_8014ADB0, 4) { pf_m_4adb0(GM_PASS); }
E(setRevivalBreakIce__10daPlyIce_cFv, 4) { pf_setRevivalBreakIce__10daPlyIce_cFv_4aef0(GM_PASS); }
E(fn_8014AFC0, 4) { pf_m_4afc0(GM_PASS); }
E(fn_8014B000, 4) { pf_m_4b000(GM_PASS); }
E(fn_8014B040, 4) { pf_m_4b040(GM_PASS); }
E(fn_8014B060, 4) { pf_m_4b060(GM_PASS); }
E(fn_8014B130, 4) { pf_m_4b130(GM_PASS); }
E(fn_8014B2C0, 4) { pf_m_4b2c0(GM_PASS); }
E(fn_8014B2F0, 4) { pf_m_4b2f0(GM_PASS); }
E(fn_8014B580, 4) { pf_m_4b580(GM_PASS); }
E(fn_8014B850, 4) { pf_m_4b850(GM_PASS); }
E(fn_8014B8C0, 4) { pf_m_4b8c0(GM_PASS); }
E(YoshiStateOrig, 4) { pf_YoshiStateOrig_4b920(GM_PASS); }
E(fn_8014BA10, 4) { pf_m_4ba10(GM_PASS); }
E(fn_8014BA20, 4) { pf_m_4ba20(GM_PASS); }
E(fn_8014BAE0, 4) { pf_m_4bae0(GM_PASS); }
E(fn_8014BBE0, 4) { pf_m_4bbe0(GM_PASS); }
E(fn_8014BBF0, 4) { pf_m_4bbf0(GM_PASS); }
E(fn_8014BE50, 4) { pf_m_4be50(GM_PASS); }
E(fn_8014BFB0, 4) { pf_m_4bfb0(GM_PASS); }
E(fn_8014C020, 4) { pf_m_4c020(GM_PASS); }
E(fn_8014C170, 4) { pf_m_4c170(GM_PASS); }
E(fn_8014C200, 4) { pf_m_4c200(GM_PASS); }
E(fn_8014C240, 4) { pf_m_4c240(GM_PASS); }
E(fn_8014C330, 4) { pf_m_4c330(GM_PASS); }
E(fn_8014C3A0, 4) { pf_m_4c3a0(GM_PASS); }
E(fn_8014C400, 4) { pf_m_4c400(GM_PASS); }
E(fn_8014C410, 4) { pf_m_4c410(GM_PASS); }
E(fn_8014C500, 4) { pf_m_4c500(GM_PASS); }
E(fn_8014C570, 4) { pf_m_4c570(GM_PASS); }
E(fn_8014C690, 4) { pf_m_4c690(GM_PASS); }
E(fn_8014C730, 4) { pf_m_4c730(GM_PASS); }
E(fn_8014C780, 4) { pf_m_4c780(GM_PASS); }
E(fn_8014C8A0, 4) { pf_m_4c8a0(GM_PASS); }
E(fn_8014C8C0, 4) { pf_m_4c8c0(GM_PASS); }
E(fn_8014C900, 4) { pf_m_4c900(GM_PASS); }
E(fn_8014C920, 4) { pf_m_4c920(GM_PASS); }
E(fn_8014C930, 4) { pf_m_4c930(GM_PASS); }
E(fn_8014CC30, 4) { pf_m_4cc30(GM_PASS); }
E(fn_8014CD70, 4) { pf_m_4cd70(GM_PASS); }
E(fn_8014CDD0, 4) { pf_m_4cdd0(GM_PASS); }
E(fn_8014CEB0, 4) { pf_m_4ceb0(GM_PASS); }
E(fn_8014CFD0, 4) { pf_m_4cfd0(GM_PASS); }
E(fn_8014D070, 4) { pf_m_4d070(GM_PASS); }
E(fn_8014D2D0, 4) { pf_m_4d2d0(GM_PASS); }
E(fn_8014D4A0, 4) { pf_m_4d4a0(GM_PASS); }
E(fn_8014D5D0, 4) { pf_m_4d5d0(GM_PASS); }
E(fn_8014D610, 4) { pf_m_4d610(GM_PASS); }
E(fn_8014D6D0, 4) { pf_m_4d6d0(GM_PASS); }
E(fn_8014D720, 4) { pf_m_4d720(GM_PASS); }
E(fn_8014D760, 4) { pf_m_4d760(GM_PASS); }
E(fn_8014D7D0, 4) { pf_m_4d7d0(GM_PASS); }
E(fn_8014D810, 4) { pf_m_4d810(GM_PASS); }
E(fn_8014D820, 4) { pf_m_4d820(GM_PASS); }
E(fn_8014DBB0, 4) { pf_m_4dbb0(GM_PASS); }
E(fn_8014E4E0, 4) { pf_m_4e4e0(GM_PASS); }
E(fn_8014E6B0, 4) { pf_m_4e6b0(GM_PASS); }
E(fn_8014E700, 4) { pf_m_4e700(GM_PASS); }
E(fn_8014E750, 4) { pf_m_4e750(GM_PASS); }
E(fn_8014E760, 4) { pf_m_4e760(GM_PASS); }
E(fn_8014E820, 4) { pf_m_4e820(GM_PASS); }
E(getPlayerRideOn__9daYoshi_cCFv, 4) { pf_getPlayerRideOn__9daYoshi_cCFv_4e9b0(GM_PASS); }
E(checkRideOffAble__9daYoshi_cFv, 4) { pf_checkRideOffAble__9daYoshi_cFv_4e9d0(GM_PASS); }
E(setRideOffPlayer__9daYoshi_cFv, 4) { pf_setRideOffPlayer__9daYoshi_cFv_4eb80(GM_PASS); }
E(fn_8014EC40, 4) { pf_m_4ec40(GM_PASS); }
E(fn_8014ECE0, 4) { pf_m_4ece0(GM_PASS); }
E(fn_8014ECF0, 4) { pf_m_4ecf0(GM_PASS); }
E(fn_8014ED00, 4) { pf_m_4ed00(GM_PASS); }
E(fn_8014ED20, 4) { pf_m_4ed20(GM_PASS); }
E(fn_8014ED30, 4) { pf_m_4ed30(GM_PASS); }
E(fn_8014ED40, 4) { pf_m_4ed40(GM_PASS); }
E(fn_8014ED50, 4) { pf_m_4ed50(GM_PASS); }
E(fn_8014ED90, 4) { pf_m_4ed90(GM_PASS); }
E(fn_8014EE10, 4) { pf_m_4ee10(GM_PASS); }
E(fn_8014EFA0, 4) { pf_m_4efa0(GM_PASS); }
E(fn_8014EFB0, 4) { pf_m_4efb0(GM_PASS); }
E(fn_8014F0C0, 4) { pf_m_4f0c0(GM_PASS); }
E(fn_8014F160, 4) { pf_m_4f160(GM_PASS); }
E(fn_8014F200, 4) { pf_m_4f200(GM_PASS); }
E(fn_8014F290, 4) { pf_m_4f290(GM_PASS); }
E(fn_8014F3D0, 4) { pf_m_4f3d0(GM_PASS); }
E(fn_8014F3E0, 4) { pf_m_4f3e0(GM_PASS); }
E(fn_8014F470, 4) { pf_m_4f470(GM_PASS); }
E(fn_8014F540, 4) { pf_m_4f540(GM_PASS); }
E(fn_8014F590, 4) { pf_m_4f590(GM_PASS); }
E(fn_8014F630, 4) { pf_m_4f630(GM_PASS); }
E(fn_8014F840, 4) { pf_m_4f840(GM_PASS); }
E(fn_8014F9B0, 4) { pf_m_4f9b0(GM_PASS); }
E(fn_8014FAD0, 4) { pf_m_4fad0(GM_PASS); }
E(fn_8014FBC0, 4) { pf_m_4fbc0(GM_PASS); }
E(fn_8014FC50, 4) { pf_m_4fc50(GM_PASS); }
E(fn_8014FCC0, 4) { pf_m_4fcc0(GM_PASS); }
E(fn_8014FD60, 4) { pf_m_4fd60(GM_PASS); }
E(fn_8014FF00, 4) { pf_m_4ff00(GM_PASS); }
E(fn_8014FF80, 4) { pf_m_4ff80(GM_PASS); }
E(fn_80150020, 4) { pf_m_50020(GM_PASS); }
E(fn_80150090, 4) { pf_m_50090(GM_PASS); }
E(fn_80150150, 4) { pf_m_50150(GM_PASS); }
E(fn_801501B0, 4) { pf_m_501b0(GM_PASS); }
E(fn_801501D0, 4) { pf_m_501d0(GM_PASS); }
E(fn_801502E0, 4) { pf_m_502e0(GM_PASS); }
E(fn_80150650, 4) { pf_m_50650(GM_PASS); }
E(fn_80150680, 4) { pf_m_50680(GM_PASS); }
E(fn_801506A0, 4) { pf_m_506a0(GM_PASS); }
E(fn_80150760, 4) { pf_m_50760(GM_PASS); }
E(fn_801507C0, 4) { pf_m_507c0(GM_PASS); }
E(fn_80150830, 4) { pf_m_50830(GM_PASS); }
E(fn_801508A0, 4) { pf_m_508a0(GM_PASS); }
E(fn_80150AB0, 4) { pf_m_50ab0(GM_PASS); }
E(fn_80150B80, 4) { pf_m_50b80(GM_PASS); }
E(fn_80150DB0, 4) { pf_m_50db0(GM_PASS); }
E(fn_80150DE0, 4) { pf_m_50de0(GM_PASS); }
E(fn_80150E10, 4) { pf_m_50e10(GM_PASS); }
E(fn_80151030, 4) { pf_m_51030(GM_PASS); }
E(fn_80151040, 4) { pf_m_51040(GM_PASS); }
E(fn_80151270, 4) { pf_m_51270(GM_PASS); }
E(fn_80151320, 4) { pf_m_51320(GM_PASS); }
E(fn_80151470, 4) { pf_m_51470(GM_PASS); }
E(fn_801515C0, 4) { pf_m_515c0(GM_PASS); }
E(fn_80151630, 4) { pf_m_51630(GM_PASS); }
E(fn_801518D0, 4) { pf_m_518d0(GM_PASS); }
E(fn_80151A70, 4) { pf_m_51a70(GM_PASS); }
E(fn_80151AC0, 4) { pf_m_51ac0(GM_PASS); }
E(fn_80151AD0, 4) { pf_m_51ad0(GM_PASS); }
E(fn_80151C20, 4) { pf_m_51c20(GM_PASS); }
E(fn_80151C30, 4) { pf_m_51c30(GM_PASS); }
E(fn_80151D00, 4) { pf_m_51d00(GM_PASS); }
E(fn_80151E50, 4) { pf_m_51e50(GM_PASS); }
E(fn_80152020, 4) { pf_m_52020(GM_PASS); }
E(fn_80152130, 4) { pf_m_52130(GM_PASS); }
E(fn_801522B0, 4) { pf_m_522b0(GM_PASS); }
E(fn_80152360, 4) { pf_m_52360(GM_PASS); }
E(fn_801523A0, 4) { pf_m_523a0(GM_PASS); }
E(fn_801523E0, 4) { pf_m_523e0(GM_PASS); }
E(getTongueTipMtx__9daYoshi_cFP6mMtx_c, 4) { pf_getTongueTipMtx__9daYoshi_cFP6mMtx_c_52480(GM_PASS); }
E(getMouthMtx__9daYoshi_cFP6mMtx_c, 4) { pf_getMouthMtx__9daYoshi_cFP6mMtx_c_52520(GM_PASS); }
E(fn_80152560, 4) { pf_m_52560(GM_PASS); }
E(fn_801527A0, 4) { pf_m_527a0(GM_PASS); }
E(fn_801527F0, 4) { pf_m_527f0(GM_PASS); }
E(fn_80152B30, 4) { pf_m_52b30(GM_PASS); }
E(fn_80152C80, 4) { pf_m_52c80(GM_PASS); }
E(fn_801531A0, 4) { pf_m_531a0(GM_PASS); }
E(fn_80153210, 4) { pf_m_53210(GM_PASS); }
E(fn_80153240, 4) { pf_m_53240(GM_PASS); }
E(fn_801532A0, 4) { pf_m_532a0(GM_PASS); }
E(fn_801532B0, 4) { pf_m_532b0(GM_PASS); }
E(fn_801532D0, 4) { pf_m_532d0(GM_PASS); }
E(fn_801532F0, 4) { pf_m_532f0(GM_PASS); }
E(fn_80153400, 4) { pf_m_53400(GM_PASS); }
E(fn_801543C0, 4) { pf_m_543c0(GM_PASS); }
E(fn_801543D0, 4) { pf_m_543d0(GM_PASS); }
E(fn_801543E0, 4) { pf_m_543e0(GM_PASS); }
E(fn_801543F0, 4) { pf_m_543f0(GM_PASS); }
E(fn_80154400, 4) { pf_m_54400(GM_PASS); }
E(fn_80154410, 4) { pf_m_54410(GM_PASS); }
E(fn_80154420, 4) { pf_m_54420(GM_PASS); }
E(fn_80154430, 4) { pf_m_54430(GM_PASS); }
E(fn_80154440, 4) { pf_m_54440(GM_PASS); }
E(fn_80154450, 4) { pf_m_54450(GM_PASS); }
E(fn_80154460, 4) { pf_m_54460(GM_PASS); }
E(fn_801546C0, 4) { pf_m_546c0(GM_PASS); }
E(fn_80154740, 4) { pf_m_54740(GM_PASS); }
E(fn_801548A0, 4) { pf_m_548a0(GM_PASS); }
E(fn_80154A70, 4) { pf_m_54a70(GM_PASS); }
E(fn_80154D00, 4) { pf_m_54d00(GM_PASS); }
E(fn_80154D50, 4) { pf_m_54d50(GM_PASS); }
E(fn_80156930, 4) { pf_m_56930(GM_PASS); }
E(fn_80156D70, 4) { pf_m_56d70(GM_PASS); }
E(fn_80156E00, 4) { pf_m_56e00(GM_PASS); }
E(fn_801573B0, 4) { pf_m_573b0(GM_PASS); }
E(fn_801580F0, 4) { pf_m_580f0(GM_PASS); }
E(fn_80158100, 4) { pf_m_58100(GM_PASS); }
E(fn_80159960, 4) { pf_m_59960(GM_PASS); }
E(fn_80159F10, 4) { pf_m_59f10(GM_PASS); }
E(fn_8015A340, 4) { pf_m_5a340(GM_PASS); }
E(fn_8015A370, 4) { pf_m_5a370(GM_PASS); }
E(fn_8015A580, 4) { pf_m_5a580(GM_PASS); }
E(fn_8015A610, 4) { pf_m_5a610(GM_PASS); }
E(fn_8015A810, 4) { pf_m_5a810(GM_PASS); }
E(fn_8015A890, 4) { pf_m_5a890(GM_PASS); }
E(fn_8015A8D0, 4) { pf_m_5a8d0(GM_PASS); }
E(fn_8015A910, 4) { pf_m_5a910(GM_PASS); }
E(fn_8015AB20, 4) { pf_m_5ab20(GM_PASS); }
E(fn_8015B320, 4) { pf_m_5b320(GM_PASS); }
E(fn_8015B930, 4) { pf_m_5b930(GM_PASS); }
E(fn_8015B960, 4) { pf_m_5b960(GM_PASS); }
E(fn_8015B970, 4) { pf_m_5b970(GM_PASS); }
E(fn_8015B9C0, 4) { pf_m_5b9c0(GM_PASS); }
E(fn_8015BA10, 4) { pf_m_5ba10(GM_PASS); }
E(fn_8015BA60, 4) { pf_m_5ba60(GM_PASS); }
E(fn_8015BAF0, 4) { pf_m_5baf0(GM_PASS); }
E(fn_8015BB30, 4) { pf_m_5bb30(GM_PASS); }
E(fn_8015BB60, 4) { pf_m_5bb60(GM_PASS); }
E(fn_8015BB90, 4) { pf_m_5bb90(GM_PASS); }
E(fn_8015BBC0, 4) { pf_m_5bbc0(GM_PASS); }
E(fn_8015BBF0, 4) { pf_m_5bbf0(GM_PASS); }
E(fn_8015BC40, 4) { pf_m_5bc40(GM_PASS); }
E(fn_8015BC90, 4) { pf_m_5bc90(GM_PASS); }
E(fn_8015BCB0, 4) { pf_m_5bcb0(GM_PASS); }
E(fn_8015BCE0, 4) { pf_m_5bce0(GM_PASS); }
E(fn_8015BCF0, 4) { pf_m_5bcf0(GM_PASS); }
E(fn_8015BD10, 4) { pf_m_5bd10(GM_PASS); }
E(fn_8015BD40, 4) { pf_m_5bd40(GM_PASS); }
E(fn_8015BD80, 4) { pf_m_5bd80(GM_PASS); }
E(fn_8015BDD0, 4) { pf_m_5bdd0(GM_PASS); }
E(fn_8015BE20, 4) { pf_m_5be20(GM_PASS); }
E(fn_8015BE60, 4) { pf_m_5be60(GM_PASS); }
E(fn_8015BEA0, 4) { pf_m_5bea0(GM_PASS); }
E(fn_8015BEE0, 4) { pf_m_5bee0(GM_PASS); }
E(fn_8015BF10, 4) { pf_m_5bf10(GM_PASS); }
E(fn_8015BF50, 4) { pf_m_5bf50(GM_PASS); }
E(fn_8015BF90, 4) { pf_m_5bf90(GM_PASS); }
E(fn_8015BFD0, 4) { pf_m_5bfd0(GM_PASS); }
E(fn_8015C010, 4) { pf_m_5c010(GM_PASS); }
E(fn_8015C070, 4) { pf_m_5c070(GM_PASS); }
E(fn_8015C090, 4) { pf_m_5c090(GM_PASS); }
E(fn_8015C0E0, 4) { pf_m_5c0e0(GM_PASS); }
E(fn_8015C100, 4) { pf_m_5c100(GM_PASS); }
E(fn_8015C130, 4) { pf_m_5c130(GM_PASS); }
E(fn_8015C370, 4) { pf_m_5c370(GM_PASS); }
E(fn_8015C410, 4) { pf_m_5c410(GM_PASS); }
E(fn_8015C4B0, 4) { pf_m_5c4b0(GM_PASS); }
E(fn_8015C4C0, 4) { pf_m_5c4c0(GM_PASS); }
E(fn_8015C560, 4) { pf_m_5c560(GM_PASS); }
E(fn_8015C5A0, 4) { pf_m_5c5a0(GM_PASS); }
E(fn_8015C610, 4) { pf_m_5c610(GM_PASS); }
E(fn_8015C620, 4) { pf_m_5c620(GM_PASS); }
E(fn_8015C630, 4) { pf_m_5c630(GM_PASS); }
E(fn_8015C680, 4) { pf_m_5c680(GM_PASS); }
E(fn_8015C6F0, 4) { pf_m_5c6f0(GM_PASS); }
E(fn_8015CCB0, 4) { pf_m_5ccb0(GM_PASS); }
E(fn_8015CCC0, 4) { pf_m_5ccc0(GM_PASS); }
E(fn_8015CD30, 4) { pf_m_5cd30(GM_PASS); }
E(fn_8015CD40, 4) { pf_m_5cd40(GM_PASS); }
E(fn_8015CD90, 4) { pf_m_5cd90(GM_PASS); }
E(fn_8015CDD0, 4) { pf_m_5cdd0(GM_PASS); }
E(fn_8015CDE0, 4) { pf_m_5cde0(GM_PASS); }
E(fn_8015CDF0, 4) { pf_m_5cdf0(GM_PASS); }
E(fn_8015CE70, 4) { pf_m_5ce70(GM_PASS); }
E(fn_8015CE80, 4) { pf_m_5ce80(GM_PASS); }
E(fn_8015CED0, 4) { pf_m_5ced0(GM_PASS); }
E(fn_8015CF60, 4) { pf_m_5cf60(GM_PASS); }
E(fn_8015CF70, 4) { pf_m_5cf70(GM_PASS); }
E(fn_8015CFC0, 4) { pf_m_5cfc0(GM_PASS); }
E(fn_8015D030, 4) { pf_m_5d030(GM_PASS); }
E(fn_8015D080, 4) { pf_m_5d080(GM_PASS); }
E(fn_8015D0A0, 4) { pf_m_5d0a0(GM_PASS); }
E(fn_8015D0F0, 4) { pf_m_5d0f0(GM_PASS); }
E(fn_8015D140, 4) { pf_m_5d140(GM_PASS); }
E(fn_8015D150, 4) { pf_m_5d150(GM_PASS); }
E(fn_8015D160, 4) { pf_m_5d160(GM_PASS); }
E(fn_8015D1B0, 4) { pf_m_5d1b0(GM_PASS); }
E(fn_8015D1C0, 4) { pf_m_5d1c0(GM_PASS); }
E(fn_8015D1D0, 4) { pf_m_5d1d0(GM_PASS); }
E(fn_8015D280, 4) { pf_m_5d280(GM_PASS); }
E(fn_8015D290, 4) { pf_m_5d290(GM_PASS); }
E(fn_8015D2A0, 4) { pf_m_5d2a0(GM_PASS); }
E(fn_8015D320, 4) { pf_m_5d320(GM_PASS); }
E(fn_8015D330, 4) { pf_m_5d330(GM_PASS); }
E(fn_8015D390, 4) { pf_m_5d390(GM_PASS); }
E(fn_8015D3A0, 4) { pf_m_5d3a0(GM_PASS); }
E(fn_8015D640, 4) { pf_m_5d640(GM_PASS); }
E(fn_8015D650, 4) { pf_m_5d650(GM_PASS); }
E(fn_8015D6F0, 4) { pf_m_5d6f0(GM_PASS); }
E(fn_8015D700, 4) { pf_m_5d700(GM_PASS); }
E(fn_8015DC40, 4) { pf_m_5dc40(GM_PASS); }
E(fn_8015DCA0, 4) { pf_m_5dca0(GM_PASS); }
E(fn_8015DCB0, 4) { pf_m_5dcb0(GM_PASS); }
E(fn_8015DCD0, 4) { pf_m_5dcd0(GM_PASS); }
E(fn_8015DCF0, 4) { pf_m_5dcf0(GM_PASS); }
E(fn_8015DDD0, 4) { pf_m_5ddd0(GM_PASS); }
E(fn_8015F3B0, 4) { pf_m_5f3b0(GM_PASS); }
E(fn_8015F410, 4) { pf_m_5f410(GM_PASS); }
