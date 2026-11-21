/* gm_mj_conv.c - instance 2 (track B): the 8-player module (d_project, linked at 0x81800000) - the
 * functions the A/B inputs reach that no hand-written native covers. Transliterated by
 * tools/gm_conv.py from the recompiled bodies (statement for statement in the natives' macros);
 * the gate is the strict A/B (against the previous build and the build with no natives).
 * Functions another runtime file defines or calls by symbol are left to their owners.
 * Names are owed (mj_m_<addr>).
 * Build flags (testing): -DGM_MJ_COUNT logs each native's first call, -DGM_MJ_VERIFY makes them
 * switchable (RT_GM_VERIFY=orig:<names>). */

#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d

/* mod_beginState_BattleIn__12daBossDemo_cFv (mod_beginState_BattleIn__12daBossDemo_cFv, 196 bytes) */
static void mj_mod_beginState_BattleIn__12daBossDemo_cF_00dfc(GM_CTX) {
    GM_FN(0x81800DFC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 1);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25452));
    GM_CALLV(0x81800E28u, 0x8005B5D0u, 0);
    R(3) = ld32(base, (R(30) + 984));
    GM_CALLV(0x81800E30u, 0x80162D00u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81800E9C; }
    R(28) = ld32(base, (R(3) + 96));
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(28) + 712));
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81800E50u, ctx->ctr, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld8(base, (R(3) + -6048));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81800E9C; }
    R(3) = ld32(base, (R(29) + 1528));
    R(4) = (0 + 0);
    st32(base, (R(3) + 4), R(4));
    R(3) = ld32(base, (R(28) + 752));
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81800E7Cu, ctx->ctr, 0);
    R(3) = ld32(base, (R(28) + 800));
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81800E8Cu, ctx->ctr, 0);
    R(3) = ld32(base, (R(28) + 816));
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81800E9Cu, ctx->ctr, 0);
L_81800E9C:;
    R(3) = (0 + 0);
    st32(base, (R(30) + 980), R(3));
    R(0) = lr;
}

/* mod_fn_80021AB0 (mod_fn_80021AB0, 136 bytes) */
static void mj_mod_fn_80021AB0_00ec0(GM_CTX) {
    GM_FN(0x81800EC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81850000u);
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = (R(3) + 9252);
    R(28) = ld32(base, (R(3) + R(4)));
    R(29) = (0 + 9);
    R(30) = (0 + 0);
L_81800EF0:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81800EF8u, 0x81806928u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81800F10; }
    R(3) = ld32(base, (R(3) + 5336));
    R(3) = ld32(base, (R(3) + 588));
    cr_cmp_u(ctx, 0, R(28), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81800F28; }
L_81800F10:;
    R(29) = (R(29) + -1);
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(30) = (R(30) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81800EF0; }
    R(3) = (0 + 0);
    goto L_81800F2C;
L_81800F28:;
    R(3) = (0 + 1);
L_81800F2C:;
    R(0) = lr;
}

/* mod_fn_80021B30 (mod_fn_80021B30, 176 bytes) */
static void mj_mod_fn_80021B30_00f48(GM_CTX) {
    GM_FN(0x81800F48); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -508);
    R(3) = ld8(base, (R(3) + 7));
    R(30) = (0 + 0);
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_81800FD8; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25272));
    R(4) = (0 + 0x0u);
    R(29) = (0 + 8);
    R(30) = R(4) | 0xFFFFu;
    R(28) = ld16(base, (R(3) + 3016));
L_81800F90:;
    R(4) = R(28) & 0xFFFFu;
    GM_CALLV(0x81800F98u, 0x80021AB0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (R(28) + 1);
    if ((CR_BIT(ctx, 2))) { goto L_81800FB8; }
    R(29) = (R(29) + -1);
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(28) = R(3) |R(3);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81800F90; }
    goto L_81800FD8;
L_81800FB8:;
    R(4) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(4) + -25272));
    R(5) = (int16_t)R(28);
    st16(base, (R(4) + 3016), R(3));
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 9252);
    R(4) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(30) = ld32(base, (R(3) + R(4)));
L_81800FD8:;
    R(3) = (int16_t)R(30);
    R(0) = lr;
}

/* mfn_81800FF8 (mfn_81800FF8, 336 bytes) */
static void mj_mfn_81800FF8_00ff8(GM_CTX) {
    GM_FN(0x81800FF8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(12) = ctx->cr;
    R(27) = R(3) |R(3);
    R(28) = R(4) |R(4);
    R(29) = R(6) |R(6);
    R(30) = R(5) |R(5);
    R(3) = (0 + 8);
    cr_cmp_u(ctx, 0, R(4), 0x1Bu);
    R(4) = (0 + 0);
    st32(base, (f + 20), R(12));
    if ((CR_BIT(ctx, 1))) { goto L_81801070; }
    R(5) = (0 + 1);
    R(6) = (0 + 0x8000000u);
    { uint32_t s_ = R(28) & 63; R(5) = s_ > 31 ? 0 : R(5) << s_; }
    R(6) = R(6) | 0x82u;
    R(5) = R(5) &R(6);
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81801070; }
    R(4) = (0 + 1);
    R(3) = R(28) |R(28);
L_81801070:;
    cr_cmp_s(ctx, 2, (int32_t)R(29), 1);
    if ((CR_BIT(ctx, 8))) { goto L_81801088; }
    R(5) = (R(30) + -4);
    ctx->ctr = R(29);
L_81801080:;
    { uint32_t ea_ = R(5) + 4; st32(base, ea_, R(3)); R(5) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81801080; }
L_81801088:;
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180109C; }
    cr_cmp_u(ctx, 0, R(29), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_818010D8; }
L_81801098:;
    st32(base, (R(30) + 0), R(28));
L_8180109C:;
    R(12) = ld32(base, (f + 20));
    ctx->cr = (ctx->cr & ~0xF00000u) | (R(12) & 0xF00000u);
    R(0) = lr;
    return;
L_818010D8:;
    GM_CALLV(0x818010DCu, 0x818056E4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81801098; }
    if ((CR_BIT(ctx, 8))) { GM_LOOP(); goto L_81801098; }
    R(26) = R(3) |R(3);
    R(24) = (0 + 0);
    R(23) = (0 + 1);
    R(22) = (0 + 0);
L_818010F8:;
    R(25) = (R(23) + -1);
    R(3) = R(25) |R(25);
    GM_CALLV(0x81801104u, 0x8005F900u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81801130; }
    R(4) = (int8_t)R(25);
    R(3) = R(27) |R(27);
    GM_CALLV(0x81801118u, 0x80022180u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180112C; }
    R(3) = rotl32(R(22), 2) & 0xFFFFFFFCu;
    R(22) = (R(22) + 1);
    st32(base, (R(30) + R(3)), R(28));
L_8180112C:;
    R(24) = (R(24) + 1);
L_81801130:;
    cr_cmp_s(ctx, 0, (int32_t)R(23), (int32_t)R(26));
    if ((!CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81801098; }
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(29));
    R(23) = (R(23) + 1);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818010F8; }
    GM_LOOP(); goto L_81801098;
}

/* mod_fn_80022810 (mod_fn_80022810, 768 bytes) */
static void mj_mod_fn_80022810_01148(GM_CTX) {
    GM_FN(0x81801148); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(0) = ld32(base, (R(3) + 1608));
    R(27) = R(3) |R(3);
    R(28) = R(4) |R(4);
    R(29) = R(5) |R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81801430; }
    R(0) = ld8(base, (R(4) + 20));
    R(30) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180119C; }
    R(5) = ld32(base, (R(4) + 16));
    R(3) = (0 + 0x802F0000u);
    R(3) = (R(3) + -7392);
    R(0) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(31) = ld32(base, (R(3) + R(0)));
    goto L_818011B4;
L_8180119C:;
    R(5) = ld32(base, (R(4) + 16));
    R(3) = (0 + 0x802F0000u);
    R(3) = (R(3) + -7320);
    R(30) = (0 + 4096);
    R(0) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(31) = ld32(base, (R(3) + R(0)));
L_818011B4:;
    cr_cmp_u(ctx, 0, R(31), 0xFu);
    if ((CR_BIT(ctx, 2))) { goto L_81801430; }
    cr_cmp_u(ctx, 0, R(31), 0x6u);
    if ((!CR_BIT(ctx, 2))) { goto L_818011C8; }
    goto L_81801430;
L_818011C8:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 14);
    if ((!CR_BIT(ctx, 2))) { goto L_81801224; }
    R(0) = ld8(base, (R(4) + 12));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), -1);
    if ((CR_BIT(ctx, 2))) { goto L_81801430; }
    R(3) = R(27) |R(27);
    GM_CALLV(0x818011E8u, 0x80022390u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180121C; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81801224; }
    R(0) = ld8(base, (R(28) + 12));
    R(3) = R(27) |R(27);
    R(4) = (int8_t)R(0);
    GM_CALLV(0x81801208u, 0x80022180u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801430; }
    R(31) = (0 + 2);
    goto L_81801224;
    goto L_81801430;
L_8180121C:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801430; }
L_81801224:;
    cr_cmp_u(ctx, 0, R(31), 0xCu);
    R(4) = ld8(base, (R(28) + 21));
    if ((!CR_BIT(ctx, 2))) { goto L_81801248; }
    R(3) = R(27) |R(27);
    R(4) = (0 + 0);
    GM_CALLV(0x8180123Cu, 0x800223C0u, 0);
    R(0) = (0 + 1);
    st32(base, (R(27) + 1608), R(0));
    goto L_81801430;
L_81801248:;
    cr_cmp_u(ctx, 0, R(31), 0xDu);
    if ((!CR_BIT(ctx, 2))) { goto L_81801264; }
    R(3) = R(27) |R(27);
    GM_CALLV(0x81801258u, 0x800217F0u, 0);
    R(0) = (0 + 1);
    st32(base, (R(27) + 1608), R(0));
    goto L_81801430;
L_81801264:;
    cr_cmp_u(ctx, 0, R(31), 0x5u);
    if ((!CR_BIT(ctx, 2))) { goto L_81801304; }
    { uint32_t ea_ = (R(27) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld8(base, (R(27) + 1677));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_818012D8; }
    { uint32_t ea_ = (R(13) + -17308); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 28);
    R(3) = ld32(base, (R(13) + -22848));
    R(5) = (0 + 5);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    R(6) = (0 + 0);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x818012B0u, 0x80066740u, 0);
    R(29) = ld32(base, (R(13) + -22816));
    R(4) = R(28) |R(28);
    R(3) = (f + 8);
    GM_CALLV(0x818012C0u, 0x8006A4B0u, 0);
    R(3) = R(29) |R(29);
    R(5) = (f + 8);
    R(4) = (0 + 568);
    R(6) = (0 + 0);
    GM_CALLV(0x818012D4u, 0x80198C30u, 0);
    goto L_818012F8;
L_818012D8:;
    { uint32_t ea_ = (R(13) + -17296); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 28);
    R(3) = ld32(base, (R(13) + -22848));
    R(5) = (0 + 5);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    R(6) = (0 + 0);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x818012F8u, 0x800667B0u, 0);
L_818012F8:;
    R(0) = (0 + 1);
    st32(base, (R(27) + 1608), R(0));
    goto L_81801430;
L_81801304:;
    cr_cmp_u(ctx, 0, R(31), 0xAu);
    if ((!CR_BIT(ctx, 2))) { goto L_81801328; }
    R(5) = ld8(base, (R(27) + 1677));
    R(3) = R(27) |R(27);
    R(4) = (0 + 1);
    GM_CALLV(0x8180131Cu, 0x80021A20u, 0);
    R(0) = (0 + 1);
    st32(base, (R(27) + 1608), R(0));
    goto L_81801430;
L_81801328:;
    cr_cmp_u(ctx, 0, R(31), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_81801338; }
    cr_cmp_u(ctx, 0, R(31), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180133C; }
L_81801338:;
    R(4) = (0 + 0);
L_8180133C:;
    { uint32_t ea_ = (R(28) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -17388); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(27) + 1680));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8180136C; }
    R(0) = ld8(base, (R(27) + 911));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801374; }
L_8180136C:;
    { uint32_t ea_ = (R(13) + -17292); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
L_81801374:;
    R(29) = ld8(base, (R(28) + 12));
    R(3) = (int8_t)R(29);
    cr_cmp_s(ctx, 0, (int32_t)R(3), -1);
    if ((CR_BIT(ctx, 2))) { goto L_81801430; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818013C0; }
    R(5) = ld8(base, (R(28) + 22));
    R(0) = R(31) |R(30);
    R(4) = ld8(base, (R(27) + 1677));
    R(3) = rotl32(R(3), 16) & 0xFFFF0000u;
    R(0) = R(0) | 0x40000000u;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(4) = rotl32(R(4), 14) & 0xFFFFC000u;
    R(0) = R(3) |R(0);
    R(3) = R(4) |R(0);
    if ((CR_BIT(ctx, 2))) { goto L_818013D0; }
    R(0) = rotl32(R(5), 20) & 0xFF00000u;
    R(3) = R(3) |R(0);
    goto L_818013D0;
L_818013C0:;
    R(0) = R(31) |R(30);
    R(3) = rotl32(R(3), 16) & 0xFFFF0000u;
    R(0) = R(0) | 0xA000000u;
    R(3) = R(3) |R(0);
L_818013D0:;
    R(7) = ld8(base, (R(27) + 911));
    R(4) = R(3) | 0x800u;
    R(5) = (f + 16);
    R(3) = (0 + 60);
    R(6) = (0 + 0);
    GM_CALLV(0x818013E8u, 0x80064610u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801404; }
    R(0) = ld8(base, (R(28) + 22));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801404; }
    R(0) = ld32(base, (R(27) + 0));
    st32(base, (R(3) + 3024), R(0));
L_81801404:;
    R(3) = R(27) |R(27);
    R(5) = R(31) |R(31);
    R(4) = (f + 16);
    R(6) = (int8_t)R(29);
    R(7) = (0 + 0);
    R(8) = (0 + 0);
    GM_CALLV(0x81801420u, 0x80022490u, 0);
    cr_cmp_u(ctx, 0, R(31), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_81801430; }
    R(0) = (0 + 1);
    st32(base, (R(27) + 1608), R(0));
L_81801430:;
    R(11) = (f + 64);
    R(0) = lr;
}

/* mod_fn_8002DAB0 (mod_fn_8002DAB0, 128 bytes) */
static void mj_mod_fn_8002DAB0_01514(GM_CTX) {
    GM_FN(0x81801514); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = (0 + 1);
    R(29) = (0 + 8);
    R(30) = (0 + 0);
L_81801538:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81801540u, 0x8005F900u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81801554; }
    GM_CALLV(0x8180154Cu, 0x8004DD00u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81801574; }
L_81801554:;
    cr_cmp_u(ctx, 0, R(30), 0x7u);
    R(28) = (0 + 1);
    if ((CR_BIT(ctx, 0))) { goto L_81801564; }
    R(28) = (0 + 0);
L_81801564:;
    R(29) = (R(29) + -1);
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(30) = (R(30) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81801538; }
L_81801574:;
    R(3) = R(28) & 0x1u;
    R(0) = lr;
}

/* mod_fn_8002F870 (mod_fn_8002F870, 132 bytes) */
static void mj_mod_fn_8002F870_01594(GM_CTX) {
    GM_FN(0x81801594); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(5) |R(5);
    R(29) = R(3) |R(3);
    R(31) = ld32(base, (R(5) + 4));
    R(4) = R(31) |R(31);
    GM_CALLV(0x818015C0u, 0x800971F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818015FC; }
    R(12) = ld32(base, (R(29) + 96));
    R(3) = R(29) |R(29);
    R(4) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 544));
    ctx->ctr = R(12);
    GM_CALLV(0x818015E0u, ctx->ctr, 0);
    R(0) = ld8(base, (R(30) + 45));
    cr_cmp_u(ctx, 0, R(0), 0xAu);
    if ((!CR_BIT(ctx, 2))) { goto L_818015FC; }
    R(3) = R(29) |R(29);
    R(4) = R(31) |R(31);
    R(5) = (0 + 28);
    GM_CALLV(0x818015FCu, 0x81809F98u, 0);
L_818015FC:;
    R(0) = lr;
}

/* mfn_818016C4 (mfn_818016C4, 4 bytes) */
static void mj_mfn_818016C4_016c4(GM_CTX) {

}

/* mod_fn_800389E0 (mod_fn_800389E0, 1420 bytes) */
static void mj_mod_fn_800389E0_016e4(GM_CTX) {
    GM_FN(0x818016E4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(30) = ld32(base, (R(5) + 4));
    R(27) = R(3) |R(3);
    R(31) = (0 + 0x80350000u);
    R(28) = R(4) |R(4);
    R(3) = ld32(base, (R(30) + 10872));
    R(29) = R(5) |R(5);
    R(31) = (R(31) + 14808);
    GM_CALLV(0x81801718u, 0x80162D00u, 0);
    cr_cmp_u(ctx, 0, R(3), R(27));
    if ((CR_BIT(ctx, 2))) { goto L_81801C58; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 43);
    GM_CALLV(0x8180172Cu, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818018B0; }
    R(12) = ld32(base, (R(27) + 916));
    R(3) = (R(27) + 916);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x81801748u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (R(31) + 12);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8180175Cu, ctx->ctr, 0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(0) = rotl32(R(0), 1) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_818018B0; }
    R(3) = R(27) |R(27);
    R(4) = R(30) |R(30);
    GM_CALLV(0x81801778u, 0x80096330u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818017C0; }
    R(0) = ld8(base, (R(27) + 909));
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(13) + -16592); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (R(31) + 76);
    { uint32_t ea_ = (R(13) + -16568); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (int8_t)R(0);
    { uint32_t ea_ = (R(13) + -16564); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (R(27) + 1992), R(0));
    { uint32_t ea_ = (R(27) + 1932); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(27) + 1936); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(27) + 1940); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(27) + 96));
    R(12) = ld32(base, (R(12) + 212));
    ctx->ctr = R(12);
    GM_CALLV(0x818017BCu, ctx->ctr, 0);
    goto L_81801C58;
L_818017C0:;
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 224));
    ctx->ctr = R(12);
    GM_CALLV(0x818017D4u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180182C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x818017E4u, 0x8009F5F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    R(29) = R(3) |R(3);
    if ((!CR_BIT(ctx, 0))) { goto L_818017F4; }
    R(29) = (0 + 1);
L_818017F4:;
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(26) = ld32(base, (R(13) + -22064));
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x8180180Cu, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(3) = R(26) |R(26);
    { uint32_t ea_ = (R(13) + -10744); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = R(27) |R(27);
    { uint32_t ea_ = (R(13) + -10740); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = R(29) |R(29);
    R(6) = (int8_t)R(0);
    GM_CALLV(0x8180182Cu, 0x800E20A0u, 0);
L_8180182C:;
    R(3) = ld32(base, (R(30) + 10872));
    GM_CALLV(0x81801834u, 0x80162D00u, 0);
    R(4) = R(3) |R(3);
    CR0(ctx, R(4));
    if ((CR_BIT(ctx, 2))) { goto L_8180186C; }
    R(0) = ld8(base, (R(3) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81801858; }
    R(3) = R(27) |R(27);
    R(5) = (0 + 10);
    GM_CALLV(0x81801854u, 0x81809F98u, 0);
    goto L_8180186C;
L_81801858:;
    st32(base, (R(3) + 336), R(27));
    R(0) = (0 + 12);
    R(3) = ld32(base, (R(3) + 0));
    st32(base, (R(27) + 1968), R(3));
    st32(base, (R(27) + 1972), R(0));
L_8180186C:;
    R(0) = ld8(base, (R(27) + 1117));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801884; }
    R(4) = R(30) |R(30);
    R(5) = (0 + 16);
    GM_CALLV(0x81801884u, 0x81809F98u, 0);
L_81801884:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(5) = R(30) |R(30);
    GM_CALLV(0x81801894u, 0x800396A0u, 0);
    R(12) = ld32(base, (R(27) + 96));
    R(3) = R(27) |R(27);
    R(4) = (R(31) + 140);
    R(12) = ld32(base, (R(12) + 212));
    ctx->ctr = R(12);
    GM_CALLV(0x818018ACu, ctx->ctr, 0);
    goto L_81801C58;
L_818018B0:;
    R(12) = ld32(base, (R(27) + 96));
    R(3) = R(27) |R(27);
    R(12) = ld32(base, (R(12) + 732));
    ctx->ctr = R(12);
    GM_CALLV(0x818018C4u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(26) = R(3) |R(3);
    R(6) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_818018D8; }
    R(6) = (0 + 2);
L_818018D8:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    GM_CALLV(0x818018E8u, 0x800964A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801A14; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_818019B8; }
    { uint32_t ea_ = (R(13) + -16592); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(27) + 916);
    { uint32_t ea_ = (R(27) + 236); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(27) + 916));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x81801914u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 11700);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8180192Cu, ctx->ctr, 0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(0) = rotl32(R(0), 1) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8180194C; }
    R(3) = R(27) |R(27);
    R(4) = R(30) |R(30);
    GM_CALLV(0x81801948u, 0x8003A490u, 0);
    goto L_81801C58;
L_8180194C:;
    R(12) = ld32(base, (R(27) + 96));
    R(3) = R(27) |R(27);
    R(4) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 724));
    ctx->ctr = R(12);
    GM_CALLV(0x81801964u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81801C58; }
    R(0) = ld32(base, (R(27) + 1996));
    { uint32_t ea_ = (R(13) + -16592); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (R(27) + 232); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 236); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 240); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 1088); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 1092); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 1096); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_8180199C; }
    { uint32_t ea_ = (R(27) + 2004); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 172); stfs(base, ea_, ctx->f[0].d); }
L_8180199C:;
    R(12) = ld32(base, (R(27) + 96));
    R(3) = R(27) |R(27);
    R(4) = (R(31) + 12);
    R(12) = ld32(base, (R(12) + 212));
    ctx->ctr = R(12);
    GM_CALLV(0x818019B4u, ctx->ctr, 0);
    goto L_81801C58;
L_818019B8:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_818019F0; }
    cr_cmp_s(ctx, 0, (int32_t)R(26), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818019DC; }
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    GM_CALLV(0x818019D8u, 0x80095C20u, 0);
    goto L_81801C58;
L_818019DC:;
    R(3) = R(27) |R(27);
    R(4) = R(30) |R(30);
    R(5) = (0 + 1);
    GM_CALLV(0x818019ECu, 0x800A1190u, 0);
    goto L_81801C58;
L_818019F0:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_81801C58; }
    cr_cmp_s(ctx, 0, (int32_t)R(26), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801C58; }
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    GM_CALLV(0x81801A10u, 0x80095C20u, 0);
    goto L_81801C58;
L_81801A14:;
    R(12) = ld32(base, (R(27) + 916));
    R(3) = (R(27) + 916);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x81801A28u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (R(31) + 12);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x81801A3Cu, ctx->ctr, 0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(0) = rotl32(R(0), 1) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81801B24; }
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 224));
    ctx->ctr = R(12);
    GM_CALLV(0x81801A60u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81801AB8; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81801A70u, 0x8009F5F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    R(29) = R(3) |R(3);
    if ((!CR_BIT(ctx, 0))) { goto L_81801A80; }
    R(29) = (0 + 1);
L_81801A80:;
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(26) = ld32(base, (R(13) + -22064));
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81801A98u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(3) = R(26) |R(26);
    { uint32_t ea_ = (R(13) + -10744); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = R(27) |R(27);
    { uint32_t ea_ = (R(13) + -10740); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = R(29) |R(29);
    R(6) = (int8_t)R(0);
    GM_CALLV(0x81801AB8u, 0x800E20A0u, 0);
L_81801AB8:;
    R(3) = ld32(base, (R(30) + 10872));
    GM_CALLV(0x81801AC0u, 0x80162D00u, 0);
    R(4) = R(3) |R(3);
    CR0(ctx, R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81801AF8; }
    R(0) = ld8(base, (R(3) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81801AE4; }
    R(3) = R(27) |R(27);
    R(5) = (0 + 10);
    GM_CALLV(0x81801AE0u, 0x81809F98u, 0);
    goto L_81801AF8;
L_81801AE4:;
    st32(base, (R(3) + 336), R(27));
    R(0) = (0 + 12);
    R(3) = ld32(base, (R(3) + 0));
    st32(base, (R(27) + 1968), R(3));
    st32(base, (R(27) + 1972), R(0));
L_81801AF8:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(5) = R(30) |R(30);
    GM_CALLV(0x81801B08u, 0x800396A0u, 0);
    R(12) = ld32(base, (R(27) + 96));
    R(3) = R(27) |R(27);
    R(4) = (R(31) + 140);
    R(12) = ld32(base, (R(12) + 212));
    ctx->ctr = R(12);
    GM_CALLV(0x81801B20u, ctx->ctr, 0);
    goto L_81801C58;
L_81801B24:;
    R(12) = ld32(base, (R(27) + 916));
    R(3) = (R(27) + 916);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x81801B38u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 11700);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x81801B50u, ctx->ctr, 0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(0) = rotl32(R(0), 1) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_81801C58; }
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 1008));
    ctx->ctr = R(12);
    GM_CALLV(0x81801B74u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81801C58; }
    R(12) = ld32(base, (R(27) + 916));
    R(3) = (R(27) + 916);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x81801B90u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (R(31) + 140);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x81801BA4u, ctx->ctr, 0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(0) = rotl32(R(0), 1) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81801C48; }
    R(3) = R(27) |R(27);
    R(4) = R(30) |R(30);
    GM_CALLV(0x81801BC0u, 0x800397B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801C48; }
    R(0) = ld32(base, (R(27) + 1996));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81801C58; }
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(5) = R(30) |R(30);
    GM_CALLV(0x81801BE4u, 0x800396A0u, 0);
    R(0) = ld8(base, (R(27) + 1117));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81801C58; }
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 8), R(0));
    R(4) = ld8(base, (R(27) + 909));
    R(3) = R(27) |R(27);
    R(5) = (0 + 24);
    GM_CALLV(0x81801C08u, 0x81809FFCu, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = (R(3) + -15968);
    { uint32_t ea_ = (R(13) + -16560); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -16552); ctx->f[2].u = ld64(base, ea_); }
    R(0) = ld8(base, (R(27) + 840));
    { uint32_t ea_ = (R(27) + 284); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld8(base, (R(3) + R(0)));
    { uint32_t ea_ = (R(13) + -16580); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (int8_t)R(0);
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    { uint32_t ea_ = (f + 8); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 232); stfs(base, ea_, ctx->f[0].d); }
    goto L_81801C58;
L_81801C48:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    GM_CALLV(0x81801C58u, 0x80095C20u, 0);
L_81801C58:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* mod_fn_800396A0 (mod_fn_800396A0, 228 bytes) */
static void mj_mod_fn_800396A0_01cb0(GM_CTX) {
    GM_FN(0x81801CB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(31) + 96));
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81801CE8u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    st8(base, (R(29) + 909), R(0));
    { uint32_t ea_ = (R(29) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 208); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 172); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 208); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d + ctx->f[2].d);
    GM_CALLV(0x81801D0Cu, 0x80064A30u, 0);
    st8(base, (R(29) + 840), R(3));
    R(3) = R(29) |R(29);
    R(4) = ld8(base, (R(29) + 909));
    R(5) = (0 + 4);
    GM_CALLV(0x81801D20u, 0x81809FFCu, 0);
    R(3) = R(29) |R(29);
    R(4) = R(31) |R(31);
    GM_CALLV(0x81801D2Cu, 0x8003A360u, 0);
    R(12) = ld32(base, (R(29) + 96));
    R(3) = R(29) |R(29);
    R(4) = ld8(base, (R(29) + 909));
    R(12) = ld32(base, (R(12) + 744));
    R(4) = (int8_t)R(4);
    ctx->ctr = R(12);
    GM_CALLV(0x81801D48u, ctx->ctr, 0);
    { uint32_t ea_ = (R(30) + 148); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(29) |R(29);
    { uint32_t ea_ = (R(30) + 144); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (f + 8);
    { uint32_t ea_ = (R(13) + -16536); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(29) + 96));
    R(12) = ld32(base, (R(12) + 748));
    ctx->ctr = R(12);
    GM_CALLV(0x81801D78u, ctx->ctr, 0);
    R(0) = lr;
}

/* mod_fn_8003B3E0 (mod_fn_8003B3E0, 760 bytes) */
static void mj_mod_fn_8003B3E0_02020(GM_CTX) {
    GM_FN(0x81802020); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 1);
    R(5) = (0 + -12288);
    R(4) = (0 + 8192);
    R(0) = (0 + 0);
    R(31) = R(3) |R(3);
    R(7) = ld8(base, (R(3) + 909));
    st32(base, (R(3) + 1600), R(6));
    cr_cmp_u(ctx, 0, R(7), 0x7u);
    st32(base, (R(3) + 1604), R(5));
    st32(base, (R(3) + 1608), R(4));
    st32(base, (R(3) + 1612), R(0));
    if ((CR_BIT(ctx, 1))) { goto L_818021F4; }
    R(3) = (int8_t)R(7);
    GM_CALLV(0x8180206Cu, 0x8005F900u, 0);
    R(0) = ld8(base, (R(3) + 487));
    R(30) = R(3) |R(3);
    st8(base, (R(31) + 487), R(0));
    R(4) = R(30) |R(30);
    R(0) = ld8(base, (R(3) + 487));
    R(3) = R(31) |R(31);
    st8(base, (R(31) + 721), R(0));
    GM_CALLV(0x8180208Cu, 0x80039880u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    st32(base, (R(31) + 1996), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81802190; }
    { uint32_t ea_ = (R(13) + -16592); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 2000); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(30) + 4240));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818020F4; }
    R(3) = (0 + 0x80430000u);
    R(4) = ld8(base, (R(31) + 840));
    R(3) = (R(3) + -15968);
    R(0) = (0 + 0x43300000u);
    R(4) = ld8(base, (R(3) + R(4)));
    R(3) = (0 + 0x802F0000u);
    st32(base, (f + 8), R(0));
    R(3) = (R(3) + -6400);
    R(0) = (int8_t)R(4);
    { uint32_t ea_ = (R(13) + -16552); ctx->f[2].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 232); stfs(base, ea_, ctx->f[0].d); }
    goto L_81802138;
L_818020F4:;
    R(3) = (0 + 0x80430000u);
    R(4) = ld8(base, (R(31) + 840));
    R(3) = (R(3) + -15968);
    R(0) = (0 + 0x43300000u);
    R(4) = ld8(base, (R(3) + R(4)));
    R(3) = (0 + 0x802F0000u);
    st32(base, (f + 8), R(0));
    R(3) = (R(3) + -6400);
    R(0) = (int8_t)R(4);
    { uint32_t ea_ = (R(13) + -16552); ctx->f[2].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 232); stfs(base, ea_, ctx->f[0].d); }
L_81802138:;
    R(3) = R(31) |R(31);
    R(4) = ld8(base, (R(31) + 909));
    R(5) = (0 + 3);
    GM_CALLV(0x81802148u, 0x81809FFCu, 0);
    R(3) = (0 + 4);
    GM_CALLV(0x81802150u, 0x818432E4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_81802168; }
    R(4) = (0 + 0x80310000u);
    R(4) = (R(4) + 20392);
    st32(base, (R(3) + 0), R(4));
L_81802168:;
    R(3) = ld32(base, (R(31) + 1308));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81802188; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x81802188u, ctx->ctr, 0);
L_81802188:;
    st32(base, (R(31) + 1308), R(30));
    goto L_818021C4;
L_81802190:;
    R(3) = (R(30) + 492);
    GM_CALLV(0x81802198u, 0x80070CB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818021B4; }
    R(3) = R(31) |R(31);
    R(4) = ld8(base, (R(31) + 909));
    R(5) = (0 + 18);
    GM_CALLV(0x818021B0u, 0x81809FFCu, 0);
    goto L_818021C4;
L_818021B4:;
    R(3) = R(31) |R(31);
    R(4) = ld8(base, (R(31) + 909));
    R(5) = (0 + 10);
    GM_CALLV(0x818021C4u, 0x81809FFCu, 0);
L_818021C4:;
    R(0) = ld32(base, (R(31) + 1556));
    R(4) = ld32(base, (R(31) + 1568));
    R(5) = R(0) | 0xC0000u;
    R(3) = ld32(base, (R(31) + 1584));
    R(0) = ld32(base, (R(31) + 1600));
    R(4) = R(4) | 0xC0000u;
    R(3) = R(3) | 0xC0000u;
    st32(base, (R(31) + 1556), R(5));
    R(0) = R(0) | 0xC0000u;
    st32(base, (R(31) + 1568), R(4));
    st32(base, (R(31) + 1584), R(3));
    st32(base, (R(31) + 1600), R(0));
L_818021F4:;
    R(0) = (0 + 0);
    st32(base, (R(31) + 1948), R(0));
    R(3) = (R(31) + 916);
    R(12) = ld32(base, (R(31) + 916));
    R(12) = ld32(base, (R(12) + 44));
    ctx->ctr = R(12);
    GM_CALLV(0x81802210u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 14884);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x81802228u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81802238; }
    R(0) = (0 + 1);
    st32(base, (R(31) + 1948), R(0));
L_81802238:;
    R(0) = ld32(base, (R(31) + 1968));
    R(5) = (0 + 9);
    R(6) = ld32(base, (R(31) + 376));
    R(4) = (0 + 0);
    R(3) = ld32(base, (R(31) + 1556));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    R(0) = ld32(base, (R(31) + 1584));
    R(6) = R(6) | 0xB0u;
    { uint32_t ea_ = (R(13) + -16396); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = R(3) | 0x900000u;
    { uint32_t ea_ = (R(13) + -16412); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = R(0) | 0x900000u;
    { uint32_t ea_ = (R(31) + 232); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -16416); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -16592); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (R(31) + 376), R(6));
    st8(base, (R(31) + 373), R(5));
    st32(base, (R(31) + 1916), R(4));
    { uint32_t ea_ = (R(31) + 284); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(31) + 276); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 244); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(31) + 248); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 252); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 1556), R(3));
    st32(base, (R(31) + 1584), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_818022B0; }
    R(3) = R(3) | 0x400u;
    R(0) = R(0) | 0x400u;
    st32(base, (R(31) + 1556), R(3));
    st32(base, (R(31) + 1584), R(0));
L_818022B0:;
    R(4) = R(31) |R(31);
    R(3) = (R(31) + 492);
    R(5) = (R(31) + 1600);
    R(6) = (R(31) + 1556);
    R(7) = (R(31) + 1584);
    GM_CALLV(0x818022C8u, 0x8006D090u, 0);
    R(0) = ld8(base, (R(31) + 1988));
    R(3) = (0 + 0);
    R(4) = ld8(base, (R(31) + 909));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    st8(base, (R(31) + 644), R(4));
    st16(base, (R(31) + 1976), R(3));
    st16(base, (R(31) + 1978), R(3));
    st16(base, (R(31) + 1980), R(3));
    st16(base, (R(31) + 1982), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_818022FC; }
    R(0) = (0 + -32768);
    st16(base, (R(31) + 256), R(0));
    goto L_81802300;
L_818022FC:;
    st16(base, (R(31) + 256), R(3));
L_81802300:;
    R(0) = lr;
}

/* mod_fn_8003B830 (mod_fn_8003B830, 740 bytes) */
static void mj_mod_fn_8003B830_02318(GM_CTX) {
    GM_FN(0x81802318); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld8(base, (R(3) + 780));
    R(0) = R(0) & 0xF7u;
    CR0(ctx, R(0));
    st8(base, (R(3) + 780), R(0));
    GM_CALLV(0x8180233Cu, 0x8006CD90u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x81802344u, 0x8006CDE0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8180234Cu, 0x800955F0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x81802354u, 0x8003A3A0u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 760));
    ctx->ctr = R(12);
    GM_CALLV(0x81802368u, ctx->ctr, 0);
    R(0) = ld32(base, (R(31) + 1972));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180238C; }
    R(3) = ld32(base, (R(31) + 1556));
    R(0) = ld32(base, (R(31) + 1584));
    R(3) = R(3) & 0xFFFFFBFFu;
    st32(base, (R(31) + 1556), R(3));
    R(0) = R(0) & 0xFFFFFBFFu;
    st32(base, (R(31) + 1584), R(0));
L_8180238C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x81802394u, 0x80097050u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8180239Cu, 0x80096F60u, 0);
    R(4) = ld32(base, (R(31) + 628));
    R(3) = (R(31) + 492);
    GM_CALLV(0x818023A8u, 0x8006EF40u, 0);
    R(0) = ld32(base, (R(31) + 1996));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81802460; }
    { uint32_t ea_ = (R(31) + 232); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 2000); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    { uint32_t ea_ = (R(13) + -16504); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = frsp(ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(31) + 2000); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81802418; }
    { uint32_t ea_ = (R(13) + -16384); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 284); stfs(base, ea_, ctx->f[0].d); }
    R(3) = R(31) |R(31);
    R(4) = ld8(base, (R(31) + 909));
    R(5) = (0 + 16);
    GM_CALLV(0x818023F8u, 0x81809FFCu, 0);
    R(0) = (0 + 0);
    R(4) = ld8(base, (R(31) + 840));
    st32(base, (R(31) + 1996), R(0));
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = (R(13) + -16600);
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 244); stfs(base, ea_, ctx->f[0].d); }
    goto L_81802460;
L_81802418:;
    R(3) = ld8(base, (R(31) + 909));
    GM_CALLV(0x81802420u, 0x8005F900u, 0);
    R(0) = ld32(base, (R(3) + 4308));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81802460; }
    R(5) = ld8(base, (R(31) + 840));
    R(4) = (0 + 0);
    R(3) = (R(13) + -16600);
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(13) + -16384); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + R(5)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 284); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 244); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 1996), R(4));
    R(3) = R(31) |R(31);
    R(4) = ld8(base, (R(31) + 909));
    R(5) = (0 + 16);
    GM_CALLV(0x81802460u, 0x81809FFCu, 0);
L_81802460:;
    R(3) = (R(31) + 492);
    GM_CALLV(0x81802468u, 0x80070CB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818024BC; }
    { uint32_t ea_ = (R(13) + -16412); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(13) + -16592); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(31) + 492);
    { uint32_t ea_ = (R(31) + 276); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 236); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(31) + 1948), R(0));
    st32(base, (R(31) + 336), R(0));
    GM_CALLV(0x81802494u, 0x80070720u, 0);
    R(0) = R(3) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_81802570; }
    R(3) = (R(31) + 328);
    GM_CALLV(0x818024A8u, 0x8008C380u, 0);
    { uint32_t ea_ = (R(31) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -16380); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 176); stfs(base, ea_, ctx->f[0].d); }
    goto L_81802570;
L_818024BC:;
    R(0) = ld32(base, (R(31) + 1948));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180255C; }
    { uint32_t ea_ = (R(13) + -16564); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 36);
    { uint32_t ea_ = (R(31) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 8);
    { uint32_t ea_ = (R(31) + 180); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(6) = (0 + 1);
    { uint32_t ea_ = (R(31) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[2].d); }
    R(7) = (0 + -1);
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[3].d); }
    R(5) = ld8(base, (R(31) + 911));
    GM_CALLV(0x81802500u, 0x800757B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180255C; }
    { uint32_t ea_ = (R(31) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8180255C; }
    { uint32_t ea_ = (R(13) + -16572); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    st32(base, (R(31) + 1948), R(0));
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st32(base, (R(31) + 336), R(0));
    R(3) = ld8(base, (R(31) + 911));
    GM_CALLV(0x81802538u, 0x80070BF0u, 0);
    R(0) = rotl32(R(3), 16) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x8u);
    if ((CR_BIT(ctx, 2))) { goto L_8180255C; }
    { uint32_t ea_ = (f + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8180255C; }
    { uint32_t ea_ = (R(31) + 176); stfs(base, ea_, ctx->f[1].d); }
L_8180255C:;
    R(0) = ld32(base, (R(31) + 628));
    R(0) = R(0) & 0x3C000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81802570; }
    { uint32_t ea_ = (R(13) + -16376); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 236); stfs(base, ea_, ctx->f[0].d); }
L_81802570:;
    R(3) = ld8(base, (R(31) + 840));
    R(0) = (0 + 21);
    R(4) = ld32(base, (R(31) + 628));
    { uint32_t s_ = R(3) & 63; R(0) = s_ > 31 ? 0 : R(0) << s_; }
    R(0) = R(4) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_818025E8; }
    { uint32_t ea_ = (R(31) + 232); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = R(3) ^ 0x1u;
    { uint32_t ea_ = (R(31) + 244); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = R(31) |R(31);
    ctx->f[3].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(31) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -16372); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[2].u ^ 0x8000000000000000ull;
    st8(base, (R(31) + 840), R(0));
    R(3) = (f + 24);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 232); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(31) + 244); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 236); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x818025C4u, 0x8006CED0u, 0);
    R(31) = ld32(base, (R(13) + -22820));
    R(3) = (f + 16);
    R(4) = (f + 24);
    GM_CALLV(0x818025D4u, 0x8006A4B0u, 0);
    R(3) = R(31) |R(31);
    R(5) = (f + 16);
    R(4) = (0 + 647);
    R(6) = (0 + 0);
    GM_CALLV(0x818025E8u, 0x80197F00u, 0);
L_818025E8:;
    R(0) = lr;
}

/* mod_fn_800441E0 (mod_fn_800441E0, 472 bytes) */
static void mj_mod_fn_800441E0_02600(GM_CTX) {
    GM_FN(0x81802600); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 1104));
    R(30) = R(4) |R(4);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81802674; }
    R(3) = (0 + 8);
    R(28) = (0 + 8);
    GM_CALLV(0x81802654u, 0x818433C8u, 0);
    R(4) = (0 + 0);
    st32(base, (R(29) + 1104), R(3));
    R(3) = (0 + 0);
    ctx->ctr = R(28);
L_81802664:;
    R(5) = ld32(base, (R(29) + 1104));
    st8(base, (R(5) + R(3)), R(4));
    R(3) = (R(3) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81802664; }
L_81802674:;
    R(25) = ld32(base, (R(29) + 992));
    R(27) = (0 + 0);
    R(26) = (0 + 0);
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81802730; }
    R(24) = (0 + 1);
    R(23) = (0 + 40);
L_81802690:;
    R(28) = ld32(base, (R(25) + 4));
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81802724; }
    R(3) = ld8(base, (R(28) + 908));
    R(3) = (R(3) + -1);
    R(3) = R(3) & 0xFFu;
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_81802724; }
    R(22) = ld32(base, (R(28) + 96));
    R(3) = ld32(base, (R(22) + 224));
    ctx->ctr = R(3);
    R(3) = R(28) |R(28);
    GM_CALLV(0x818026C4u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81802724; }
    R(3) = R(28) |R(28);
    R(4) = (0 + 69);
    GM_CALLV(0x818026D8u, 0x80056CF0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81802724; }
    R(3) = R(28) |R(28);
    R(4) = (0 + 92);
    GM_CALLV(0x818026ECu, 0x80056C70u, 0);
    R(22) = ld32(base, (R(22) + 108));
    R(3) = R(28) |R(28);
    ctx->ctr = R(22);
    GM_CALLV(0x818026FCu, ctx->ctr, 0);
    R(3) = ld8(base, (R(3) + 0));
    ctx->ctr = R(22);
    R(21) = ld32(base, (R(29) + 1104));
    { uint32_t s_ = R(3) & 63; R(3) = s_ > 31 ? 0 : R(24) << s_; }
    R(26) = R(3) |R(26);
    R(3) = R(28) |R(28);
    GM_CALLV(0x81802718u, ctx->ctr, 0);
    R(3) = ld8(base, (R(3) + 0));
    R(3) = (int8_t)R(3);
    st8(base, (R(21) + R(3)), R(23));
L_81802724:;
    R(25) = ld32(base, (R(25) + 12));
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81802690; }
L_81802730:;
    R(3) = (0 + 8);
    ctx->ctr = R(3);
    R(3) = (0 + 1);
L_8180273C:;
    R(4) = ld32(base, (R(29) + 1104));
    R(5) = ld8(base, (R(4) + R(27)));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81802754; }
    R(5) = (R(5) + -1);
    st8(base, (R(4) + R(27)), R(5));
L_81802754:;
    R(4) = R(3) &R(26);
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81802778; }
    R(4) = ld32(base, (R(29) + 1104));
    R(4) = ld8(base, (R(4) + R(27)));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    R(4) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_81802774; }
    R(4) = R(3) |R(3);
L_81802774:;
    R(26) = R(4) |R(26);
L_81802778:;
    R(27) = (R(27) + 1);
    R(3) = rotl32(R(3), 1) & 0xFFFFFFFEu;
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180273C; }
    R(28) = R(26) & 0xFFu;
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x81802794u, 0x800440C0u, 0);
    R(4) = R(3) |R(3);
    st8(base, (R(30) + 0), R(4));
    R(3) = R(28) |R(28);
    R(0) = lr;
}

/* mod_fn_80052900 (mod_fn_80052900, 1284 bytes) */
static void mj_mod_fn_80052900_02ef0(GM_CTX) {
    GM_FN(0x81802EF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 116);
    R(30) = R(3) |R(3);
    GM_CALLV(0x81802F10u, 0x80056CB0u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 115);
    GM_CALLV(0x81802F1Cu, 0x80056CF0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81802F54; }
    R(3) = ld8(base, (R(30) + 4311));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81802F48; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(30) + 268); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -31064); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 268); stfs(base, ea_, ctx->f[0].d); }
    goto L_81802F54;
L_81802F48:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 115);
    GM_CALLV(0x81802F54u, 0x80056CB0u, 0);
L_81802F54:;
    R(3) = ld8(base, (R(30) + 1012));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 5);
    if ((CR_BIT(ctx, 0))) { goto L_81803014; }
    if ((CR_BIT(ctx, 2))) { goto L_81803048; }
    cr_cmp_u(ctx, 0, R(3), 0x6u);
    if ((CR_BIT(ctx, 2))) { goto L_818030C8; }
    cr_cmp_u(ctx, 0, R(3), 0x7u);
    if ((!CR_BIT(ctx, 2))) { goto L_818033DC; }
    R(3) = ld8(base, (R(30) + 4311));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8180314C; }
    R(3) = ld32(base, (R(30) + 5272));
    R(4) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(4) + 16));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 16988);
    ctx->ctr = R(5);
    GM_CALLV(0x81802F9Cu, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81802FC8; }
    R(3) = ld32(base, (R(30) + 5272));
    R(4) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(4) + 16));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 17436);
    ctx->ctr = R(5);
    GM_CALLV(0x81802FC0u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180314C; }
L_81802FC8:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 116);
    GM_CALLV(0x81802FD4u, 0x80056C70u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 99);
    GM_CALLV(0x81802FE0u, 0x80056C70u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x81802FECu, 0x800526C0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81803008; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 1);
    GM_CALLV(0x81803000u, 0x800526C0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_818033DC; }
L_81803008:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81803010u, 0x80052300u, 0);
    goto L_818033DC;
L_81803014:;
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_81803158; }
    cr_cmp_u(ctx, 0, R(3), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_818033DC; }
    R(3) = ld32(base, (R(30) + 5212));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_818033DC; }
    R(3) = (0 + 0x80350000u);
    R(4) = (R(3) + 18284);
    R(3) = R(30) |R(30);
    R(5) = (0 + 0);
    GM_CALLV(0x81803044u, 0x8004E290u, 0);
    goto L_818033DC;
L_81803048:;
    R(3) = ld8(base, (R(30) + 4311));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8180314C; }
    R(3) = ld32(base, (R(30) + 5272));
    R(4) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(4) + 16));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 16988);
    ctx->ctr = R(5);
    GM_CALLV(0x81803070u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180309C; }
    R(3) = ld32(base, (R(30) + 5272));
    R(4) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(4) + 16));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 17436);
    ctx->ctr = R(5);
    GM_CALLV(0x81803094u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180314C; }
L_8180309C:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 116);
    GM_CALLV(0x818030A8u, 0x80056C70u, 0);
    R(3) = ld8(base, (R(30) + 4308));
    R(3) = R(3) & 0x18u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8180329C; }
L_818030B4:;
    R(3) = (0 + 7);
    st8(base, (R(30) + 1012), R(3));
    R(3) = (0 + 0);
    st32(base, (R(30) + 1116), R(3));
    goto L_81803258;
L_818030C8:;
    R(3) = ld32(base, (R(30) + 5272));
    R(4) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(4) + 16));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 17564);
    ctx->ctr = R(5);
    GM_CALLV(0x818030E4u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180314C; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 116);
    GM_CALLV(0x818030F8u, 0x80056C70u, 0);
    R(3) = ld8(base, (R(30) + 4311));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81803124; }
    R(4) = ld32(base, (R(30) + 1120));
    R(3) = R(30) |R(30);
    GM_CALLV(0x81803110u, 0x80052650u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81803124; }
    R(3) = ld32(base, (R(30) + 1120));
    R(3) = R(3) ^ 0x1u;
    st32(base, (R(30) + 1120), R(3));
L_81803124:;
    R(4) = ld32(base, (R(30) + 1120));
    R(3) = (R(30) + 3748);
    R(30) = (R(30) + 268);
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81803260; }
    R(4) = (0 + 8);
    GM_CALLV(0x81803140u, 0x8005E960u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30840); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_81803270;
L_8180314C:;
    R(3) = (0 + 0);
    st8(base, (R(30) + 1012), R(3));
    goto L_818033DC;
L_81803158:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 116);
    GM_CALLV(0x81803164u, 0x80056C70u, 0);
    R(3) = ld32(base, (R(30) + 5272));
    R(4) = ld8(base, (R(30) + 4311));
    R(5) = ld32(base, (R(3) + 0));
    R(4) = R(4) & 0x1u;
    CR0(ctx, R(4));
    R(5) = ld32(base, (R(5) + 16));
    if ((!CR_BIT(ctx, 2))) { goto L_818031A8; }
    R(4) = (0 + 0x80350000u);
    R(29) = (R(4) + 17180);
    ctx->ctr = R(5);
    R(4) = R(29) |R(29);
    GM_CALLV(0x81803190u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81803204; }
    R(3) = ld32(base, (R(30) + 96));
    R(4) = R(29) |R(29);
    R(5) = (0 + 0);
    goto L_818031F4;
L_818031A8:;
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 16988);
    ctx->ctr = R(5);
    GM_CALLV(0x818031B8u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81803204; }
    R(3) = ld32(base, (R(30) + 5272));
    R(4) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(4) + 16));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 17436);
    ctx->ctr = R(5);
    GM_CALLV(0x818031DCu, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81803204; }
    R(3) = ld32(base, (R(30) + 96));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 16988);
    R(5) = (0 + 1);
L_818031F4:;
    R(3) = ld32(base, (R(3) + 660));
    ctx->ctr = R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81803204u, ctx->ctr, 0);
L_81803204:;
    R(3) = ld32(base, (R(30) + 5212));
    { uint32_t ea_ = (R(30) + 1104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180322C; }
    { uint32_t ea_ = (R(30) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 1116); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[3].u = ctx->f[3].u & ~0x8000000000000000ull;
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81803240; }
L_8180322C:;
    R(3) = (0 + 0);
    st8(base, (R(30) + 1012), R(3));
    st32(base, (R(30) + 268), R(3));
    { uint32_t ea_ = (R(30) + 172); stfs(base, ea_, ctx->f[0].d); }
    goto L_818033DC;
L_81803240:;
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    R(3) = (R(30) + 3748);
    if ((!CR_BIT(ctx, 0))) { goto L_81803284; }
    R(4) = (0 + 4);
    GM_CALLV(0x81803254u, 0x8005E960u, 0);
    R(3) = ld32(base, (R(30) + 1116));
L_81803258:;
    st32(base, (R(30) + 268), R(3));
    goto L_818033DC;
L_81803260:;
    R(4) = (0 + 4);
    GM_CALLV(0x81803268u, 0x8005E960u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30872); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_81803270:;
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30876); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81803280u, 0x8015F470u, 0);
    goto L_818033DC;
L_81803284:;
    R(4) = (0 + 8);
    GM_CALLV(0x8180328Cu, 0x8005E960u, 0);
    { uint32_t ea_ = (R(30) + 1116); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(30) + 268); stfs(base, ea_, ctx->f[0].d); }
    goto L_818033DC;
L_8180329C:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x818032A8u, 0x800526C0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818032C4; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 1);
    GM_CALLV(0x818032BCu, 0x800526C0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818030B4; }
L_818032C4:;
    R(3) = ld32(base, (R(30) + 1124));
    R(29) = ld32(base, (R(30) + 1120));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818032DC; }
    R(3) = (R(3) + -1);
    st32(base, (R(30) + 1124), R(3));
L_818032DC:;
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    GM_CALLV(0x818032E8u, 0x80052650u, 0);
    R(4) = ld32(base, (R(30) + 1120));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81803340; }
    R(3) = ld32(base, (R(30) + 1124));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81803340; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30888); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    R(5) = (0 + 1);
    GM_CALLV(0x81803314u, 0x80052500u, 0);
    R(4) = ld32(base, (R(30) + 1120));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180336C; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31104); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    R(5) = (0 + 1);
    GM_CALLV(0x81803334u, 0x80052500u, 0);
    R(4) = ld32(base, (R(30) + 1120));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180336C; }
L_81803340:;
    R(4) = R(4) ^ 0x1u;
    R(3) = (0 + 0x80430000u);
    R(3) = (R(3) + -18368);
    R(5) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(5)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(30) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -31076); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    st32(base, (R(30) + 1120), R(4));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 1104); stfs(base, ea_, ctx->f[0].d); }
L_8180336C:;
    R(3) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(4) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(4) + -31076); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80430000u);
    R(4) = (R(4) + -18368);
    { uint32_t ea_ = (R(30) + 1104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + R(3)); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(30) + 3748);
    { uint32_t ea_ = (R(30) + 172); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[1].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_818033B0; }
    R(4) = (0 + 4);
    GM_CALLV(0x818033A4u, 0x8005E960u, 0);
    { uint32_t ea_ = (R(30) + 1116); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0);
    goto L_818033C4;
L_818033B0:;
    R(4) = (0 + 8);
    GM_CALLV(0x818033B8u, 0x8005E960u, 0);
    { uint32_t ea_ = (R(30) + 1116); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 1);
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
L_818033C4:;
    cr_cmp_u(ctx, 0, R(29), R(3));
    { uint32_t ea_ = (R(30) + 268); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(30) + 1120), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_818033DC; }
    R(3) = (0 + 180);
    st32(base, (R(30) + 1124), R(3));
L_818033DC:;
    R(0) = lr;
}

/* mod_fn_8005E5D0 (mod_fn_8005E5D0, 60 bytes) */
static void mj_mod_fn_8005E5D0_05624(GM_CTX) {
    R(4) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(3) + 0));
    R(4) = ld32(base, (R(4) + -24752));
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(3) = ld16(base, (R(3) + 4));
    R(4) = R(4) + R(5);
    R(4) = ld32(base, (R(4) + 4));
    R(4) = ld32(base, (R(4) + 8));
    R(4) = (R(4) + -1);
    cr_cmp_u(ctx, 0, R(4), 0x2u);
    R(4) = (0 + 1024);
    if ((CR_BIT(ctx, 0))) { goto L_81805658; }
    R(4) = (0 + 512);
L_81805658:;
    R(3) = R(4) &R(3);
}

/* mfn_8180637C (mfn_8180637C, 348 bytes) */
static void mj_mfn_8180637C_0637c(GM_CTX) {
    GM_FN(0x8180637C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(24) = (0 + 0x81860000u);
    R(29) = R(4) |R(4);
    cr_cmp_u(ctx, 0, R(3), R(29));
    R(4) = ld32(base, (R(24) + -300));
    st32(base, (f + 72), R(4));
    if ((!CR_BIT(ctx, 0))) { goto L_81806494; }
    R(30) = R(5) |R(5);
    R(28) = R(3) |R(3);
    R(23) = (R(29) + -4);
    R(27) = (f + 40);
L_818063D0:;
    R(3) = R(27) |R(27);
    R(4) = R(30) |R(30);
    R(5) = (0 + 32);
    GM_CALLV(0x818063E0u, 0x81844C38u, 0);
    R(3) = ld32(base, (R(29) + -4));
    cr_cmp_u(ctx, 0, R(23), R(28));
    if ((!CR_BIT(ctx, 1))) { goto L_81806454; }
    R(5) = (R(28) + 4);
    cr_cmp_u(ctx, 0, R(23), R(5));
    R(4) = R(23) |R(23);
    if ((CR_BIT(ctx, 1))) { goto L_81806400; }
    R(4) = R(5) |R(5);
L_81806400:;
    R(5) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(27) + R(5)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = ~(R(28) | R(28));
    R(4) = R(5) + R(4);
    R(4) = rotl32(R(4), 30) & 0x3FFFFFFFu;
    R(3) = (R(28) + -4);
    R(4) = (R(4) + 1);
    R(26) = R(28) |R(28);
    ctx->ctr = R(4);
L_81806424:;
    { uint32_t ea_ = R(3) + 4; R(4) = ld32(base, ea_); R(3) = ea_; }
    R(5) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(27) + R(5)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81806448; }
    R(5) = ld32(base, (R(26) + 0));
    st32(base, (R(26) + 0), R(4));
    R(26) = (R(26) + 4);
    st32(base, (R(3) + 0), R(5));
L_81806448:;
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81806424; }
    R(3) = ld32(base, (R(29) + -4));
    goto L_81806458;
L_81806454:;
    R(26) = R(28) |R(28);
L_81806458:;
    R(4) = ld32(base, (R(26) + 0));
    R(25) = (f + 8);
    st32(base, (R(26) + 0), R(3));
    R(3) = R(25) |R(25);
    st32(base, (R(29) + -4), R(4));
    R(4) = R(30) |R(30);
    R(5) = (0 + 32);
    GM_CALLV(0x81806478u, 0x81844C38u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(26) |R(26);
    R(5) = R(25) |R(25);
    GM_CALLV(0x81806488u, 0x8180637Cu, 0);
    R(28) = (R(26) + 4);
    cr_cmp_u(ctx, 0, R(28), R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818063D0; }
L_81806494:;
    R(3) = ld32(base, (R(24) + -300));
    R(4) = ld32(base, (f + 72));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_818064D4; }
    R(0) = lr;
    return;
L_818064D4:;
    GM_CALLV(0x818064D8u, 0x81844FCCu, 0);
}

/* ctor_8180774C (ctor_8180774C, 100 bytes) */
static void mj_ctor_8180774C_0774c(GM_CTX) {
    GM_FN(0x8180774C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = (0 + 0x81850000u);
    R(3) = (R(3) + -5828);
    R(4) = (R(4) + -25628);
    R(5) = (0 + 32);
    GM_CALLV(0x81807774u, 0x81844C38u, 0);
    R(3) = (0 + 0x81860000u);
    R(30) = (R(3) + -5636);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81807784u, 0x8005B3A0u, 0);
    R(3) = (0 + 0x80060000u);
    R(5) = (0 + 0x81860000u);
    R(4) = (R(3) + -19488);
    R(5) = (R(5) + -5436);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8180779Cu, 0x81844EF4u, 0);
    R(0) = lr;
}

/* mod_fn_800651C0 (mod_fn_800651C0, 712 bytes) */
static void mj_mod_fn_800651C0_077b0(GM_CTX) {
    GM_FN(0x818077B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = (f + 144);
    R(29) = R(5) |R(5);
    R(28) = R(4) |R(4);
    R(4) = R(31) |R(31);
    GM_CALLV(0x818077F4u, 0x8006CED0u, 0);
    { uint32_t ea_ = (f + 148); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 144); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (R(29) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 180); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d + ctx->f[2].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 140); stfs(base, ea_, ctx->f[5].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 132); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 136); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 124); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 128); stfs(base, ea_, ctx->f[5].d); }
    R(0) = ld32(base, (R(31) + 296));
    cr_cmp_u(ctx, 0, R(0), 0x7u);
    if ((CR_BIT(ctx, 1))) { goto L_8180786C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    R(0) = ((int32_t)R(0) * 22);
    R(3) = ld32(base, (R(13) + -22276));
    R(0) = R(3) + R(0);
    R(3) = R(0) + R(28);
    if ((CR_BIT(ctx, 0))) { goto L_81807858; }
    R(3) = (R(3) + 22);
L_81807858:;
    R(0) = ld8(base, (R(3) + 2814));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180786C; }
    R(0) = (0 + -1);
    st32(base, (R(31) + 296), R(0));
L_8180786C:;
    R(3) = ld32(base, (R(31) + 296));
    cr_cmp_u(ctx, 0, R(3), 0x7u);
    if ((CR_BIT(ctx, 1))) { goto L_81807970; }
    GM_CALLV(0x8180787Cu, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(29) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_81807A44; }
    GM_CALLV(0x8180788Cu, 0x80147B60u, 0);
    R(30) = R(3) |R(3);
    R(3) = R(29) |R(29);
    R(4) = (f + 104);
    GM_CALLV(0x8180789Cu, 0x80141F70u, 0);
    { uint32_t ea_ = (f + 108); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 104); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[3].d + ctx->f[2].d);
    { uint32_t ea_ = (R(29) + 180); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    GM_CALLV(0x818078BCu, 0x80101AA0u, 0);
    ctx->f[4].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (f + 112); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 116); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -15168); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[4].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[30].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[4].d + ctx->f[0].d);
    R(4) = ld32(base, (R(13) + -21344));
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[31].d - ctx->f[5].d);
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[30].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[4].d); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[31].d + ctx->f[5].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[4].d); }
    R(3) = ld32(base, (R(31) + 296));
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ((int32_t)R(3) * 572);
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[31].d); }
    R(4) = R(4) + R(0);
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[30].d); }
    R(0) = ld8(base, (R(4) + 897));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180792C; }
    R(4) = R(28) |R(28);
    GM_CALLV(0x8180792Cu, 0x800B3600u, 0);
L_8180792C:;
    { uint32_t ea_ = (R(13) + -15188); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 132);
    R(4) = (f + 120);
    R(5) = (f + 76);
    R(6) = (f + 64);
    GM_CALLV(0x81807944u, 0x800B3100u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81807954; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81807A44; }
L_81807954:;
    R(3) = ld32(base, (R(31) + 296));
    R(4) = R(28) |R(28);
    R(5) = (0 + 0);
    GM_CALLV(0x81807964u, 0x800B3750u, 0);
    R(0) = (0 + -1);
    st32(base, (R(31) + 296), R(0));
    goto L_81807A44;
L_81807970:;
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8180797Cu, 0x80065520u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(29) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_81807A44; }
    GM_CALLV(0x8180798Cu, 0x80147B60u, 0);
    R(30) = R(3) |R(3);
    R(3) = R(29) |R(29);
    R(4) = (f + 48);
    GM_CALLV(0x8180799Cu, 0x80141F70u, 0);
    { uint32_t ea_ = (f + 52); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 48); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[3].d + ctx->f[2].d);
    { uint32_t ea_ = (R(29) + 180); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    GM_CALLV(0x818079BCu, 0x80101AA0u, 0);
    ctx->f[2].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (f + 60); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 132);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[30].d - ctx->f[3].d);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[30].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[30].d + ctx->f[3].d);
    { uint32_t ea_ = (R(13) + -15188); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[4].d); }
    R(4) = (f + 120);
    R(5) = (f + 20);
    R(6) = (f + 8);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[31].d); }
    GM_CALLV(0x81807A14u, 0x800B3100u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81807A44; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81807A44; }
    R(12) = ld32(base, (R(29) + 96));
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81807A38u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(0) = (int8_t)R(0);
    st32(base, (R(31) + 296), R(0));
L_81807A44:;
    R(3) = (0 + 0);
    R(0) = lr;
}

/* mod_fn_80065480 (mod_fn_80065480, 152 bytes) */
static void mj_mod_fn_80065480_07a78(GM_CTX) {
    GM_FN(0x81807A78); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0);
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
L_81807AA4:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), (int32_t)R(30));
    if ((!CR_BIT(ctx, 2))) { goto L_81807ACC; }
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = (0 + 0);
    GM_CALLV(0x81807ABCu, 0x800B3720u, 0);
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    GM_CALLV(0x81807AC8u, 0x800B3780u, 0);
    goto L_81807ADC;
L_81807ACC:;
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = (0 + 0);
    GM_CALLV(0x81807ADCu, 0x800B3750u, 0);
L_81807ADC:;
    R(31) = (R(31) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81807AA4; }
    R(0) = (0 + -1);
    st32(base, (R(28) + 296), R(0));
    R(0) = lr;
}

/* mod_fn_80065520 (mod_fn_80065520, 256 bytes) */
static void mj_mod_fn_80065520_07b10(GM_CTX) {
    GM_FN(0x81807B10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(27) = R(4) |R(4);
    R(4) = R(3) |R(3);
    R(3) = (f + 8);
    GM_CALLV(0x81807B3Cu, 0x8006CED0u, 0);
    { uint32_t ea_ = (R(13) + -15176); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(29) = (0 + 0);
    R(28) = (0 + 0);
    R(30) = (0 + 0);
    R(31) = (0 + 1);
L_81807B50:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -6004));
    { uint32_t s_ = R(28) & 63; R(0) = s_ > 31 ? 0 : R(31) << s_; }
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81807BD0; }
    R(3) = ld32(base, (R(13) + -22276));
    R(0) = R(30) + R(27);
    R(3) = R(3) + R(0);
    R(0) = ld8(base, (R(3) + 2814));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81807BD0; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x81807B84u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81807BD0; }
    { uint32_t ea_ = (R(3) + 172); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 208); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 212); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81807BD0; }
    R(29) = R(3) |R(3);
    ctx->f[31].u = ctx->f[0].u;
L_81807BD0:;
    R(28) = (R(28) + 1);
    R(30) = (R(30) + 22);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 4);
    if ((CR_BIT(ctx, 0))) { goto L_81807BE4; }
    R(30) = (R(30) + 22);
L_81807BE4:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81807B50; }
    R(3) = R(29) |R(29);
    R(11) = (f + 48);
    R(0) = lr;
}

/* mod_getRemotePlayer__6dAudioFi (mod_getRemotePlayer__6dAudioFi, 84 bytes) */
static void mj_mod_getRemotePlayer__6dAudioFi_07c9c(GM_CTX) {
    GM_FN(0x81807C9C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x81807CB4u, 0x80069520u, 0);
    R(4) = R(3) |R(3);
    R(3) = (0 + 0);
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    R(4) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81807CD0; }
    R(4) = (0 + 2);
    { uint32_t s_ = R(30) & 63; R(4) = s_ > 31 ? 0 : R(4) << s_; }
L_81807CD0:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 3);
    if ((CR_BIT(ctx, 1))) { goto L_81807CDC; }
    R(3) = R(4) |R(4);
L_81807CDC:;
    R(0) = lr;
}

/* mod_fn_80104050 (mod_fn_80104050, 84 bytes) */
static void mj_mod_fn_80104050_07cf0(GM_CTX) {
    GM_FN(0x81807CF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x81807D14u, 0x8183CB74u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81807D28; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 184);
    GM_CALLV(0x81807D28u, 0x818434F4u, 0);
L_81807D28:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_8006C0B0 (mod_fn_8006C0B0, 40 bytes) */
static void mj_mod_fn_8006C0B0_07d44(GM_CTX) {
    GM_FN(0x81807D44); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0);
    R(5) = (0 + 36);
    GM_CALLV(0x81807D5Cu, 0x81844D68u, 0);
    R(0) = lr;
}

/* mod_fn_8006C1C0 (mod_fn_8006C1C0, 676 bytes) */
static void mj_mod_fn_8006C1C0_07e2c(GM_CTX) {
    GM_FN(0x81807E2C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 32));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81807F8C; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25272));
    R(3) = ld8(base, (R(3) + 3019));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81807F8C; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25280));
    R(3) = ld32(base, (R(3) + 24));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81807EA0; }
    R(3) = ld32(base, (R(3) + 984));
    GM_CALLV(0x81807E88u, 0x80162D00u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81807EA0; }
    R(3) = ld32(base, (R(3) + 1528));
    R(3) = ld32(base, (R(3) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81807F84; }
L_81807EA0:;
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -508);
    R(3) = ld8(base, (R(3) + 10));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81807EC0; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81807EBCu, 0x818080D0u, 0);
    goto L_81807F8C;
L_81807EC0:;
    R(3) = (0 + 0x80430000u);
    R(3) = (R(3) + -24704);
    R(3) = ld8(base, (R(3) + 3));
    R(3) = R(3) & 0x10u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81807F8C; }
    GM_CALLV(0x81807ED8u, 0x818056E4u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_81807F8C; }
    R(3) = ld32(base, (R(30) + 28));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_81807FAC; }
    R(27) = (0 + 8);
    R(29) = (0 + 0);
L_81807EF4:;
    R(3) = (0 + 0x81860000u);
    { uint32_t ea_ = R(3) + -6008; R(4) = ld32(base, ea_); R(3) = ea_; }
    { uint32_t a_ = R(29); R(5) = 0x20u - a_; ctx->xer_ca = 0x20u >= a_; }
    R(3) = ld32(base, (R(3) + 4));
    { uint32_t s_ = R(5) & 63; R(5) = s_ > 31 ? 0 : R(4) << s_; }
    { uint32_t s_ = R(29) & 63; R(3) = s_ > 31 ? 0 : R(3) >> s_; }
    R(3) = R(3) |R(5);
    R(5) = (R(29) + -32);
    { uint32_t s_ = R(5) & 63; R(4) = s_ > 31 ? 0 : R(4) >> s_; }
    R(3) = R(3) |R(4);
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81807F70; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x81807F2Cu, 0x8005F900u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81807F70; }
    R(4) = (0 + 4);
    R(28) = R(3) |R(3);
    GM_CALLV(0x81807F40u, 0x80056CF0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81807F64; }
    R(3) = ld32(base, (R(28) + 96));
    R(3) = ld32(base, (R(3) + 288));
    ctx->ctr = R(3);
    R(3) = R(28) |R(28);
    GM_CALLV(0x81807F5Cu, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81807F70; }
L_81807F64:;
    R(3) = ld32(base, (R(30) + 28));
    R(3) = R(3) | 0x80000000u;
    st32(base, (R(30) + 28), R(3));
L_81807F70:;
    R(27) = (R(27) + -1);
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    R(29) = (R(29) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81807EF4; }
    goto L_81807F8C;
L_81807F84:;
    R(3) = (0 + 1);
    st32(base, (R(30) + 32), R(3));
L_81807F8C:;
    R(0) = lr;
    return;
L_81807FAC:;
    R(3) = ld32(base, (R(30) + 24));
    R(4) = (0 + 1800);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1798);
    if ((CR_BIT(ctx, 1))) { goto L_81807FC0; }
    R(4) = (R(3) + 1);
L_81807FC0:;
    R(3) = ld32(base, (R(30) + 0));
    st32(base, (R(30) + 24), R(4));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81807FDC; }
    GM_CALLV(0x81807FD4u, 0x80162D00u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81807F8C; }
L_81807FDC:;
    R(29) = (0 + 0);
    R(3) = R(30) |R(30);
    st32(base, (R(30) + 0), R(29));
    GM_CALLV(0x81807FECu, 0x81807D94u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81807F8C; }
    R(3) = (0 + 0x81860000u);
    { uint32_t ea_ = R(3) + -6008; R(4) = ld32(base, ea_); R(3) = ea_; }
    R(27) = (0 + 8);
    R(28) = (0 + 0);
    R(5) = ld32(base, (R(3) + 4));
L_81808008:;
    { uint32_t a_ = R(29); R(3) = 0x20u - a_; ctx->xer_ca = 0x20u >= a_; }
    { uint32_t s_ = R(29) & 63; R(6) = s_ > 31 ? 0 : R(5) >> s_; }
    { uint32_t s_ = R(3) & 63; R(3) = s_ > 31 ? 0 : R(4) << s_; }
    R(3) = R(6) |R(3);
    R(6) = (R(29) + -32);
    { uint32_t s_ = R(6) & 63; R(6) = s_ > 31 ? 0 : R(4) >> s_; }
    R(3) = R(3) |R(6);
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81808058; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x81808034u, 0x8005F900u, 0);
    R(5) = (0 + 0x81860000u);
    { uint32_t ea_ = R(5) + -6008; R(4) = ld32(base, ea_); R(5) = ea_; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(5) = ld32(base, (R(5) + 4));
    if ((CR_BIT(ctx, 2))) { goto L_81808058; }
    R(3) = ld32(base, (R(3) + 4240));
    R(3) = cntlzw(R(3));
    R(3) = rotl32(R(3), 27) & 0x7FFFFFFu;
    R(28) = R(28) + R(3);
L_81808058:;
    R(27) = (R(27) + -1);
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    R(29) = (R(29) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81808008; }
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81807F8C; }
    cr_cmp_u(ctx, 0, R(28), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_81808088; }
    cr_cmp_u(ctx, 0, R(28), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_81808090; }
    R(3) = (0 + 900);
    goto L_81808094;
L_81808088:;
    R(3) = (0 + 1200);
    goto L_81808094;
L_81808090:;
    R(3) = (0 + 600);
L_81808094:;
    R(4) = ld32(base, (R(30) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81807F8C; }
    R(3) = (0 + 0x81850000u);
    R(5) = (R(3) + -27124);
    R(3) = (0 + 221);
    R(4) = (0 + 4096);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x818080BCu, 0x80064610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81807F8C; }
    R(3) = ld32(base, (R(3) + 0));
    st32(base, (R(30) + 0), R(3));
    GM_LOOP(); goto L_81807F8C;
}

/* mod_fn_800785E0 (mod_fn_800785E0, 156 bytes) */
static void mj_mod_fn_800785E0_0843c(GM_CTX) {
    GM_FN(0x8180843C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x8180845Cu, 0x8005FC70u, 0);
    R(30) = R(3) |R(3);
    R(28) = (0 + 8);
    R(29) = (0 + 0);
    R(27) = (0 + 1);
L_8180846C:;
    { uint32_t s_ = R(29) & 63; R(3) = s_ > 31 ? 0 : R(30) >> s_; }
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81808494; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x81808480u, 0x8005F900u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81808494; }
    R(3) = ld8(base, (R(3) + 5436));
    cr_cmp_u(ctx, 0, R(3), 0x6u);
    if ((CR_BIT(ctx, 2))) { goto L_818084B4; }
L_81808494:;
    cr_cmp_u(ctx, 0, R(29), 0x7u);
    R(27) = (0 + 1);
    if ((CR_BIT(ctx, 0))) { goto L_818084A4; }
    R(27) = (0 + 0);
L_818084A4:;
    R(28) = (R(28) + -1);
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    R(29) = (R(29) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8180846C; }
L_818084B4:;
    R(3) = R(27) & 0x1u;
    R(0) = lr;
}

/* mod_fn_8007BEF0 (mod_fn_8007BEF0, 2308 bytes) */
static void mj_mod_fn_8007BEF0_085e8(GM_CTX) {
    GM_FN(0x818085E8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(13) + -14416); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -14412); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    ctx->f[29].u = ctx->f[30].u;
    ctx->f[28].u = ctx->f[31].u;
    R(31) = R(3) |R(3);
    R(28) = (0 + 0);
    R(29) = ld32(base, (R(13) + -21688));
    R(30) = ld32(base, (R(13) + -22656));
L_81808644:;
    R(4) = ld8(base, (R(29) + 4622));
    R(3) = (f + 32);
    R(5) = ld8(base, (R(29) + 4625));
    GM_CALLV(0x81808654u, 0x8005ED90u, 0);
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 36); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[31].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81808668; }
    ctx->f[31].u = ctx->f[0].u;
L_81808668:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[30].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81808674; }
    ctx->f[30].u = ctx->f[0].u;
L_81808674:;
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81808680; }
    ctx->f[29].u = ctx->f[1].u;
L_81808680:;
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[28].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8180868C; }
    ctx->f[28].u = ctx->f[1].u;
L_8180868C:;
    R(28) = (R(28) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81808644; }
    R(4) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -14704); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(4) + 2572); stfs(base, ea_, ctx->f[31].d); }
    R(3) = (f + 20);
    { uint32_t ea_ = (R(4) + 2576); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(4) + 2580); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (R(4) + 2584); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(4) + 2520); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(4) + 2524); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(4) + 2528); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (R(4) + 2532); stfs(base, ea_, ctx->f[28].d); }
    st32(base, (R(4) + 100), R(0));
    { uint32_t ea_ = (R(4) + 104); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 108); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 112); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 116); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld8(base, (R(29) + 4622));
    R(5) = ld8(base, (R(29) + 4625));
    GM_CALLV(0x818086E8u, 0x8005ED90u, 0);
    { uint32_t ea_ = (f + 24); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(4) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -14612); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(13) + -14608); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -14704); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 96); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + -428); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + -424); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + -416); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81808714u, 0x80079710u, 0);
    R(0) = ld8(base, (R(29) + 4620));
    cr_cmp_u(ctx, 0, R(0), 0x7u);
    if ((!CR_BIT(ctx, 2))) { goto L_81808740; }
    R(0) = ld8(base, (R(29) + 4621));
    cr_cmp_u(ctx, 0, R(0), 0x6u);
    if ((!CR_BIT(ctx, 2))) { goto L_81808740; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -14408); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -440); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -440); stfs(base, ea_, ctx->f[0].d); }
L_81808740:;
    R(3) = R(31) |R(31);
    R(4) = (f + 20);
    R(5) = (0 + 1);
    GM_CALLV(0x81808750u, 0x8007A6C0u, 0);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -14628); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -372); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(3) + -376); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -364); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + -368); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 56); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -372); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 60); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -392); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -372); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -388); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[3].d);
    { uint32_t ea_ = (R(3) + 2512); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + -380); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + -384); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(30) + 64); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + -388); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 68); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    { uint32_t ea_ = (R(30) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 72); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 76); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + 35), R(0));
    st8(base, (R(3) + 36), R(0));
    R(0) = (0 + 8);
    ctx->ctr = R(0);
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -6004);
    R(4) = (0 + 0);
L_818087D8:;
    { uint32_t ea_ = R(5) + 4; R(0) = ld32(base, ea_); R(5) = ea_; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818087EC; }
    R(4) = (R(4) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818087D8; }
L_818087EC:;
    st8(base, (R(3) + 37), R(4));
    GM_CALLV(0x818087F4u, 0x8005FD20u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_81808810; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -372); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 164); stfs(base, ea_, ctx->f[0].d); }
L_81808810:;
    { uint32_t ea_ = (R(13) + -14704); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -14696); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(5) = (0 + 0);
    { uint32_t ea_ = (R(13) + -14404); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = frsp(ctx->f[1].d);
    st32(base, (R(4) + 140), R(5));
    R(6) = R(31) |R(31);
    R(7) = (0 + 0);
    R(0) = (0 + 8);
    { uint32_t ea_ = (R(4) + 136); stfs(base, ea_, ctx->f[3].d); }
    st8(base, (R(4) + 148), R(5));
    { uint32_t ea_ = (R(4) + 152); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 156); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 160); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 168); stfs(base, ea_, ctx->f[1].d); }
    R(3) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -344); stfs(base, ea_, ctx->f[2].d); }
    R(3) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 60); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -340); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 124); stfs(base, ea_, ctx->f[1].d); }
    st16(base, (f + 128), R(5));
L_818088AC:;
    R(3) = R(6) |R(6);
    R(8) = (0 + 0);
L_818088B4:;
    R(4) = R(3) |R(3);
    ctx->ctr = R(0);
L_818088BC:;
    { uint32_t ea_ = (R(4) + 4216); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4220); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4224); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4228); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4232); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4236); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4240); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4244); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4248); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4252); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4256); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4260); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4264); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4268); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4272); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4276); stfs(base, ea_, ctx->f[0].d); }
    st16(base, (R(4) + 4280), R(5));
    { uint32_t ea_ = (R(4) + 4284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4292); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4304); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4308); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4312); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4316); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4320); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4324); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4328); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4332); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4336); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4340); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4344); stfs(base, ea_, ctx->f[0].d); }
    st16(base, (R(4) + 4348), R(5));
    R(4) = (R(4) + 136);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818088BC; }
    R(8) = (R(8) + 1);
    R(3) = (R(3) + 1088);
    cr_cmp_s(ctx, 0, (int32_t)R(8), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818088B4; }
    R(7) = (R(7) + 1);
    R(6) = (R(6) + 8704);
    cr_cmp_s(ctx, 0, (int32_t)R(7), 64);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818088AC; }
    { uint32_t ea_ = (R(13) + -14704); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0);
    R(5) = (0 + 99);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[0].d = frsp(ctx->f[1].d);
    R(6) = R(31) |R(31);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[1].d); }
    R(8) = (0 + 0);
    R(0) = (0 + 4);
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (f + 60), R(5));
    st8(base, (f + 61), R(4));
    st8(base, (f + 62), R(4));
L_818089A4:;
    R(7) = R(6) |R(6);
    ctx->ctr = R(0);
L_818089AC:;
    R(3) = (R(7) + 0x90000u);
    R(7) = (R(7) + 20);
    { uint32_t ea_ = (R(3) + -28552); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28548); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28544); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28540); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -28536), R(5));
    st8(base, (R(3) + -28535), R(4));
    st8(base, (R(3) + -28534), R(4));
    R(3) = (R(7) + 0x90000u);
    R(7) = (R(7) + 20);
    { uint32_t ea_ = (R(3) + -28552); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28548); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28544); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28540); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -28536), R(5));
    st8(base, (R(3) + -28535), R(4));
    st8(base, (R(3) + -28534), R(4));
    R(3) = (R(7) + 0x90000u);
    R(7) = (R(7) + 20);
    { uint32_t ea_ = (R(3) + -28552); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28548); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28544); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28540); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -28536), R(5));
    st8(base, (R(3) + -28535), R(4));
    st8(base, (R(3) + -28534), R(4));
    R(3) = (R(7) + 0x90000u);
    R(7) = (R(7) + 20);
    { uint32_t ea_ = (R(3) + -28552); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28548); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28544); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28540); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -28536), R(5));
    st8(base, (R(3) + -28535), R(4));
    st8(base, (R(3) + -28534), R(4));
    R(3) = (R(7) + 0x90000u);
    R(7) = (R(7) + 20);
    { uint32_t ea_ = (R(3) + -28552); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28548); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28544); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -28540); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -28536), R(5));
    st8(base, (R(3) + -28535), R(4));
    st8(base, (R(3) + -28534), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818089AC; }
    R(8) = (R(8) + 1);
    R(6) = (R(6) + 400);
    cr_cmp_s(ctx, 0, (int32_t)R(8), 64);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818089A4; }
    { uint32_t ea_ = (R(13) + -14704); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (0 + 255);
    R(3) = (R(31) + 0x90000u);
    R(4) = (0 + 0);
    ctx->f[0].d = frsp(ctx->f[1].d);
    R(0) = (0 + 6);
    R(6) = R(31) |R(31);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    R(8) = (0 + 0);
    R(7) = (0 + 255);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (f + 16), R(5));
    st32(base, (R(3) + -2952), R(4));
    st32(base, (R(3) + -2948), R(4));
    ctx->ctr = R(0);
L_81808AB0:;
    R(3) = (R(6) + 0x90000u);
    R(6) = (R(6) + 96);
    { uint32_t ea_ = (R(3) + -2944); stfs(base, ea_, ctx->f[0].d); }
    R(8) = (R(8) + 16);
    { uint32_t ea_ = (R(3) + -2940); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2936), R(7));
    { uint32_t ea_ = (R(3) + -2932); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2928); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2924), R(7));
    { uint32_t ea_ = (R(3) + -2920); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2916); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2912), R(7));
    { uint32_t ea_ = (R(3) + -2908); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2904); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2900), R(7));
    { uint32_t ea_ = (R(3) + -2896); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2892); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2888), R(7));
    { uint32_t ea_ = (R(3) + -2884); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2880); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2876), R(7));
    { uint32_t ea_ = (R(3) + -2872); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2868); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2864), R(7));
    { uint32_t ea_ = (R(3) + -2860); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2856); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2852), R(7));
    R(3) = (R(6) + 0x90000u);
    R(6) = (R(6) + 96);
    { uint32_t ea_ = (R(3) + -2944); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2940); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2936), R(7));
    { uint32_t ea_ = (R(3) + -2932); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2928); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2924), R(7));
    { uint32_t ea_ = (R(3) + -2920); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2916); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2912), R(7));
    { uint32_t ea_ = (R(3) + -2908); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2904); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2900), R(7));
    { uint32_t ea_ = (R(3) + -2896); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2892); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2888), R(7));
    { uint32_t ea_ = (R(3) + -2884); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2880); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2876), R(7));
    { uint32_t ea_ = (R(3) + -2872); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2868); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2864), R(7));
    { uint32_t ea_ = (R(3) + -2860); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -2856); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2852), R(7));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81808AB0; }
    R(5) = ((int32_t)R(8) * 12);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (f + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 6);
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = R(31) |R(31);
    R(3) = R(3) + R(5);
    R(8) = ld8(base, (f + 16));
    { uint32_t ea_ = (R(3) + -2944); stfs(base, ea_, ctx->f[1].d); }
    R(5) = (0 + 0);
    { uint32_t ea_ = (R(3) + -2940); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2936), R(8));
    { uint32_t ea_ = (R(3) + -2932); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -2928); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2924), R(8));
    { uint32_t ea_ = (R(3) + -2920); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -2916); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2912), R(8));
    { uint32_t ea_ = (R(3) + -2908); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -2904); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -2900), R(8));
    ctx->ctr = R(0);
L_81808BE0:;
    R(3) = (R(4) + 0x90000u);
    R(4) = (R(4) + 96);
    { uint32_t ea_ = (R(3) + -1744); stfs(base, ea_, ctx->f[1].d); }
    R(5) = (R(5) + 16);
    { uint32_t ea_ = (R(3) + -1740); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1736), R(7));
    { uint32_t ea_ = (R(3) + -1732); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1728); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1724), R(7));
    { uint32_t ea_ = (R(3) + -1720); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1716); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1712), R(7));
    { uint32_t ea_ = (R(3) + -1708); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1704); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1700), R(7));
    { uint32_t ea_ = (R(3) + -1696); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1692); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1688), R(7));
    { uint32_t ea_ = (R(3) + -1684); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1680); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1676), R(7));
    { uint32_t ea_ = (R(3) + -1672); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1668); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1664), R(7));
    { uint32_t ea_ = (R(3) + -1660); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1656); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1652), R(7));
    R(3) = (R(4) + 0x90000u);
    R(4) = (R(4) + 96);
    { uint32_t ea_ = (R(3) + -1744); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1740); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1736), R(7));
    { uint32_t ea_ = (R(3) + -1732); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1728); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1724), R(7));
    { uint32_t ea_ = (R(3) + -1720); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1716); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1712), R(7));
    { uint32_t ea_ = (R(3) + -1708); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1704); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1700), R(7));
    { uint32_t ea_ = (R(3) + -1696); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1692); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1688), R(7));
    { uint32_t ea_ = (R(3) + -1684); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1680); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1676), R(7));
    { uint32_t ea_ = (R(3) + -1672); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1668); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1664), R(7));
    { uint32_t ea_ = (R(3) + -1660); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -1656); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1652), R(7));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81808BE0; }
    R(3) = ((int32_t)R(5) * 12);
    R(5) = (R(31) + 0x90000u);
    { uint32_t ea_ = (f + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 2);
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(6) = R(31) |R(31);
    R(3) = R(5) + R(3);
    { uint32_t ea_ = (R(13) + -14704); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -1744); stfs(base, ea_, ctx->f[2].d); }
    R(4) = (0 + 0);
    R(9) = (0 + 0);
    { uint32_t ea_ = (R(3) + -1740); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(3) + -1736), R(8));
    { uint32_t ea_ = (R(3) + -1732); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + -1728); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(3) + -1724), R(8));
    { uint32_t ea_ = (R(3) + -1720); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + -1716); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(3) + -1712), R(8));
    { uint32_t ea_ = (R(3) + -1708); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + -1704); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(3) + -1700), R(8));
    { uint32_t ea_ = (R(5) + 272); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(5) + 276), R(4));
    st8(base, (R(5) + 277), R(4));
    st8(base, (R(5) + 278), R(4));
    st8(base, (R(5) + 279), R(4));
    st8(base, (R(5) + 280), R(4));
    { uint32_t ea_ = (R(5) + 284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 300); stfs(base, ea_, ctx->f[0].d); }
    ctx->ctr = R(0);
L_81808D3C:;
    R(3) = (R(6) + 0x90000u);
    R(5) = R(31) + R(9);
    { uint32_t ea_ = (R(3) + 304); stfs(base, ea_, ctx->f[0].d); }
    R(7) = (R(5) + 0x90000u);
    R(9) = (R(9) + 5);
    R(6) = (R(6) + 20);
    st8(base, (R(7) + 464), R(4));
    R(5) = R(31) + R(9);
    R(9) = (R(9) + 5);
    st8(base, (R(7) + 484), R(4));
    { uint32_t ea_ = (R(3) + 308); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(7) + 465), R(4));
    st8(base, (R(7) + 485), R(4));
    { uint32_t ea_ = (R(3) + 312); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(7) + 466), R(4));
    st8(base, (R(7) + 486), R(4));
    { uint32_t ea_ = (R(3) + 316); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(7) + 467), R(4));
    st8(base, (R(7) + 487), R(4));
    { uint32_t ea_ = (R(3) + 320); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (R(6) + 0x90000u);
    R(6) = (R(6) + 20);
    st8(base, (R(7) + 468), R(4));
    st8(base, (R(7) + 488), R(4));
    R(7) = (R(5) + 0x90000u);
    { uint32_t ea_ = (R(3) + 304); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(7) + 464), R(4));
    st8(base, (R(7) + 484), R(4));
    { uint32_t ea_ = (R(3) + 308); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(7) + 465), R(4));
    st8(base, (R(7) + 485), R(4));
    { uint32_t ea_ = (R(3) + 312); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(7) + 466), R(4));
    st8(base, (R(7) + 486), R(4));
    { uint32_t ea_ = (R(3) + 316); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(7) + 467), R(4));
    st8(base, (R(7) + 487), R(4));
    { uint32_t ea_ = (R(3) + 320); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(7) + 468), R(4));
    st8(base, (R(7) + 488), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81808D3C; }
    R(0) = (0 + 25);
    R(5) = R(31) |R(31);
    { uint32_t ea_ = (R(13) + -14704); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(7) = (0 + 0);
    R(3) = (0 + 0);
    ctx->ctr = R(0);
L_81808DF8:;
    R(4) = (R(5) + 0x90000u);
    R(6) = R(31) + R(7);
    { uint32_t ea_ = (R(4) + 504); stfs(base, ea_, ctx->f[0].d); }
    R(6) = (R(6) + 0x90000u);
    R(5) = (R(5) + 32);
    R(7) = (R(7) + 8);
    { uint32_t ea_ = (R(4) + 1304); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 2104), R(3));
    st8(base, (R(6) + 2304), R(3));
    { uint32_t ea_ = (R(4) + 508); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 1308); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 2105), R(3));
    st8(base, (R(6) + 2305), R(3));
    { uint32_t ea_ = (R(4) + 512); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 1312); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 2106), R(3));
    st8(base, (R(6) + 2306), R(3));
    { uint32_t ea_ = (R(4) + 516); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 1316); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 2107), R(3));
    st8(base, (R(6) + 2307), R(3));
    { uint32_t ea_ = (R(4) + 520); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 1320); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 2108), R(3));
    st8(base, (R(6) + 2308), R(3));
    { uint32_t ea_ = (R(4) + 524); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 1324); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 2109), R(3));
    st8(base, (R(6) + 2309), R(3));
    { uint32_t ea_ = (R(4) + 528); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 1328); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 2110), R(3));
    st8(base, (R(6) + 2310), R(3));
    { uint32_t ea_ = (R(4) + 532); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 1332); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 2111), R(3));
    st8(base, (R(6) + 2311), R(3));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81808DF8; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -14696); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    st16(base, (R(3) + 2504), R(0));
    st8(base, (R(3) + 2506), R(0));
    st8(base, (R(3) + 2507), R(0));
    { uint32_t ea_ = (R(3) + 2516); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* mod_fn_8007CA90 (mod_fn_8007CA90, 736 bytes) */
static void mj_mod_fn_8007CA90_08eec(GM_CTX) {
    GM_FN(0x81808EEC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 80);
    R(24) = R(3) |R(3);
    R(25) = R(4) |R(4);
    R(26) = R(5) |R(5);
    R(27) = R(6) |R(6);
    R(31) = (f + 8);
    R(23) = (R(3) + 0x90000u);
    R(30) = (0 + 0);
    R(29) = (0 + 0);
    R(28) = (0 + 0);
    R(22) = (0 + 0);
L_81808F28:;
    R(3) = R(28) |R(28);
    GM_CALLV(0x81808F30u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    st32(base, (R(31) + 0), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81808F5C; }
    R(0) = ld8(base, (R(3) + 5436));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_81808F4C; }
    st32(base, (R(31) + 0), R(22));
L_81808F4C:;
    R(0) = ld8(base, (R(3) + 5436));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_81808F5C; }
    R(29) = (R(29) + 1);
L_81808F5C:;
    R(0) = ld32(base, (R(31) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81808F6C; }
    R(30) = (R(30) + 1);
L_81808F6C:;
    R(0) = ld8(base, (R(23) + 121));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81808F90; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81808F90; }
    R(0) = ld8(base, (R(3) + 5436));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_81808F90; }
    st32(base, (R(31) + 0), R(22));
L_81808F90:;
    R(28) = (R(28) + 1);
    R(31) = (R(31) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81808F28; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), (int32_t)R(29));
    st32(base, (R(25) + 48), R(30));
    if ((CR_BIT(ctx, 1))) { goto L_81808FC0; }
    R(3) = ld32(base, (R(13) + -22704));
    R(0) = (0 + 1);
    R(3) = (R(3) + 0x90000u);
    st8(base, (R(3) + 2506), R(0));
    goto L_818091B4;
L_81808FC0:;
    R(3) = ld32(base, (R(13) + -22704));
    R(28) = (0 + 0x802F0000u);
    R(0) = (0 + 0);
    R(22) = (f + 8);
    R(3) = (R(3) + 0x90000u);
    R(29) = rotl32(R(26), 2) & 0x3FCu;
    st8(base, (R(3) + 2506), R(0));
    R(28) = (R(28) + -1872);
    R(30) = (0 + 0);
L_81808FE4:;
    R(31) = (R(30) + 1);
    R(23) = (f + 8);
    R(0) = rotl32(R(31), 2) & 0xFFFFFFFCu;
    R(23) = R(23) + R(0);
    goto L_81809048;
L_81808FF8:;
    R(3) = ld32(base, (R(23) + 0));
    R(4) = ld32(base, (R(22) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809040; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809020; }
    R(3) = R(22) |R(22);
    R(4) = R(23) |R(23);
    GM_CALLV(0x8180901Cu, 0x8007CA70u, 0);
    goto L_81809040;
L_81809020:;
    R(12) = ld32(base, (R(28) + R(29)));
    ctx->ctr = R(12);
    GM_CALLV(0x8180902Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809040; }
    R(3) = R(22) |R(22);
    R(4) = R(23) |R(23);
    GM_CALLV(0x81809040u, 0x8007CA70u, 0);
L_81809040:;
    R(23) = (R(23) + 4);
    R(31) = (R(31) + 1);
L_81809048:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81808FF8; }
    R(30) = (R(30) + 1);
    R(22) = (R(22) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 7);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81808FE4; }
    R(0) = (R(27) + -1);
    cr_cmp_s(ctx, 0, (int32_t)R(26), 0);
    R(27) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(22) = (f + 8);
    R(28) = ld32(base, (f + 8));
    R(23) = ld32(base, (R(22) + R(27)));
    if ((CR_BIT(ctx, 2))) { goto L_81809098; }
    cr_cmp_s(ctx, 0, (int32_t)R(26), 2);
    if ((CR_BIT(ctx, 2))) { goto L_818090E8; }
    cr_cmp_s(ctx, 0, (int32_t)R(26), 1);
    if ((CR_BIT(ctx, 2))) { goto L_81809138; }
    cr_cmp_s(ctx, 0, (int32_t)R(26), 3);
    if ((CR_BIT(ctx, 2))) { goto L_81809178; }
    goto L_818091B4;
L_81809098:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818090BC; }
    st32(base, (R(25) + 20), R(28));
    R(3) = R(24) |R(24);
    { uint32_t ea_ = (R(28) + 5420); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x818090B0u, 0x8007C7D0u, 0);
    { uint32_t ea_ = (R(25) + 4); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld32(base, (R(28) + 5332));
    st32(base, (R(25) + 36), R(0));
L_818090BC:;
    R(0) = ld32(base, (R(22) + R(27)));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818091B4; }
    st32(base, (R(25) + 16), R(0));
    R(3) = R(24) |R(24);
    { uint32_t ea_ = (R(23) + 5420); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x818090D8u, 0x8007C7D0u, 0);
    { uint32_t ea_ = (R(25) + 0); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld32(base, (R(23) + 5332));
    st32(base, (R(25) + 32), R(0));
    goto L_818091B4;
L_818090E8:;
    cr_cmp_s(ctx, 0, (int32_t)R(23), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180910C; }
    st32(base, (R(25) + 20), R(23));
    R(3) = R(24) |R(24);
    { uint32_t ea_ = (R(23) + 5420); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81809100u, 0x8007C7D0u, 0);
    { uint32_t ea_ = (R(25) + 4); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld32(base, (R(23) + 5332));
    st32(base, (R(25) + 36), R(0));
L_8180910C:;
    R(0) = ld32(base, (f + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818091B4; }
    st32(base, (R(25) + 16), R(0));
    R(3) = R(24) |R(24);
    { uint32_t ea_ = (R(28) + 5420); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81809128u, 0x8007C7D0u, 0);
    { uint32_t ea_ = (R(25) + 0); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld32(base, (R(28) + 5332));
    st32(base, (R(25) + 32), R(0));
    goto L_818091B4;
L_81809138:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809154; }
    st32(base, (R(25) + 24), R(28));
    { uint32_t ea_ = (R(28) + 5424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 8); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(28) + 5332));
    st32(base, (R(25) + 40), R(0));
L_81809154:;
    R(0) = ld32(base, (R(22) + R(27)));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818091B4; }
    st32(base, (R(25) + 28), R(0));
    { uint32_t ea_ = (R(23) + 5424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 12); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(23) + 5332));
    st32(base, (R(25) + 44), R(0));
    goto L_818091B4;
L_81809178:;
    cr_cmp_s(ctx, 0, (int32_t)R(23), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809194; }
    st32(base, (R(25) + 24), R(23));
    { uint32_t ea_ = (R(23) + 5424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 8); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(23) + 5332));
    st32(base, (R(25) + 40), R(0));
L_81809194:;
    R(0) = ld32(base, (f + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818091B4; }
    st32(base, (R(25) + 28), R(0));
    { uint32_t ea_ = (R(28) + 5424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 12); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(28) + 5332));
    st32(base, (R(25) + 44), R(0));
L_818091B4:;
    R(11) = (f + 80);
    R(0) = lr;
}

/* mod_fn_80083490 (mod_fn_80083490, 36 bytes) */
static void mj_mod_fn_80083490_091cc(GM_CTX) {
    R(4) = (int16_t)R(3);
    CR0(ctx, R(4));
    if ((CR_BIT(ctx, 0))) { goto L_818091E8; }
    R(4) = (0 + 0x802F0000u);
    R(3) = rotl32(R(3), 1) & 0xFFFFFFFEu;
    R(4) = (R(4) + -1608);
    R(3) = ld16(base, (R(4) + R(3)));
    return;
L_818091E8:;
    R(3) = R(3) & 0x7FFFu;
}

/* mod_fn_80087F40 (mod_fn_80087F40, 228 bytes) */
static void mj_mod_fn_80087F40_091f0(GM_CTX) {
    GM_FN(0x818091F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0);
    R(0) = ld8(base, (R(4) + 11));
    R(31) = R(4) |R(4);
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), -1);
    if ((!CR_BIT(ctx, 2))) { goto L_81809220; }
    R(0) = (0 + 0);
    R(3) = (0 + 1);
L_81809220:;
    R(7) = ld8(base, (R(4) + 8));
    R(5) = rotl32(R(0), 16) & 0xF0000u;
    R(6) = ld8(base, (R(4) + 10));
    R(3) = rotl32(R(3), 29) & 0x20000000u;
    R(0) = ld8(base, (R(4) + 9));
    R(8) = rotl32(R(7), 4) & 0xFFFFFFF0u;
    R(6) = rotl32(R(6), 24) & 0x3000000u;
    { uint32_t ea_ = (R(4) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(7) = rotl32(R(0), 8) & 0xFFFFFF00u;
    R(0) = ld16(base, (R(4) + 12));
    R(8) = R(8) |R(7);
    { uint32_t ea_ = (R(4) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(8) = R(8) |R(6);
    { uint32_t ea_ = (R(13) + -14152); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(8) = R(8) |R(5);
    R(0) = rotl32(R(0), 20) & 0xFFF00000u;
    R(8) = R(8) |R(3);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[1].d); }
    R(4) = R(8) |R(0);
    R(5) = (f + 16);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    R(3) = (0 + 71);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81809288u, 0x80064610u, 0);
    R(0) = ld8(base, (R(31) + 11));
    R(4) = (int8_t)R(0);
    CR0(ctx, R(4));
    if ((CR_BIT(ctx, 0))) { goto L_8180929C; }
    R(3) = (0 + 10);
    GM_CALLV(0x8180929Cu, 0x80060690u, 0);
L_8180929C:;
    R(31) = ld32(base, (R(13) + -22816));
    R(3) = (f + 8);
    R(4) = (f + 16);
    GM_CALLV(0x818092ACu, 0x8006A4B0u, 0);
    R(3) = R(31) |R(31);
    R(5) = (f + 8);
    R(4) = (0 + 628);
    R(6) = (0 + 0);
    GM_CALLV(0x818092C0u, 0x80198C30u, 0);
    R(0) = lr;
}

/* mod_fn_800883E0 (mod_fn_800883E0, 1420 bytes) */
static void mj_mod_fn_800883E0_093cc(GM_CTX) {
    GM_FN(0x818093CC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 208);
    R(0) = ld32(base, (R(4) + 0));
    R(5) = (0 + 0x43300000u);
    R(29) = (0 + 0x802F0000u);
    st32(base, (f + 120), R(5));
    R(0) = R(0) ^ 0x80000000u;
    { uint32_t ea_ = (R(13) + -14128); ctx->f[1].u = ld64(base, ea_); }
    st32(base, (f + 124), R(0));
    R(16) = R(3) |R(3);
    R(17) = R(4) |R(4);
    R(29) = (R(29) + -224);
    { uint32_t ea_ = (f + 120); ctx->f[0].u = ld64(base, ea_); }
    st32(base, (f + 128), R(5));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[1].d);
    GM_CALLV(0x81809418u, 0x80101AA0u, 0);
    ctx->f[0].u = fctiw_bits(ctx->f[1].d, 1);
    R(25) = ld32(base, (R(17) + 4));
    R(3) = ld32(base, (R(13) + -22704));
    R(6) = (0 + 0);
    { uint32_t ea_ = (f + 136); st64(base, ea_, ctx->f[0].u); }
    R(28) = -(int32_t)R(25);
    R(26) = ld32(base, (f + 140));
    R(5) = R(28) & 0xFFFFu;
    R(4) = R(26) & 0xFFFFu;
    GM_CALLV(0x81809440u, 0x80077610u, 0);
    R(27) = R(3) & 0xFFFFu;
    R(3) = R(16) |R(16);
    R(4) = R(27) |R(27);
    GM_CALLV(0x81809450u, 0x80088210u, 0);
    R(22) = ld8(base, (R(17) + 12));
    R(24) = R(3) |R(3);
    R(23) = ld8(base, (R(17) + 14));
    cr_cmp_u(ctx, 0, R(22), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_81809468; }
    R(22) = (0 + 2);
L_81809468:;
    R(0) = (int8_t)R(23);
    cr_cmp_s(ctx, 0, (int32_t)R(0), -1);
    if ((!CR_BIT(ctx, 2))) { goto L_818094BC; }
    R(0) = (R(3) + -1);
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_818094B4; }
    st32(base, (f + 96), R(26));
    R(4) = (f + 96);
    st32(base, (f + 100), R(25));
    R(0) = ld32(base, (R(17) + 8));
    st32(base, (f + 104), R(0));
    st32(base, (f + 108), R(3));
    R(3) = R(16) |R(16);
    R(0) = ld8(base, (R(17) + 12));
    st8(base, (f + 112), R(0));
    st8(base, (f + 113), R(23));
    R(0) = ld8(base, (R(17) + 15));
    st8(base, (f + 114), R(0));
    GM_CALLV(0x818094B4u, 0x80088970u, 0);
L_818094B4:;
    R(3) = (0 + 0);
    goto L_81809940;
L_818094BC:;
    R(3) = ld32(base, (R(13) + -22704));
    R(4) = R(26) & 0xFFFFu;
    R(5) = R(28) & 0xFFFFu;
    R(21) = (0 + 0);
    R(20) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    GM_CALLV(0x818094DCu, 0x800775A0u, 0);
    cr_cmp_u(ctx, 0, R(24), 0x4u);
    R(19) = rotl32(R(3), 22) & 0x3Fu;
    R(18) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818094FC; }
    R(19) = (R(27) + -3);
    R(24) = (0 + 0);
    R(18) = (0 + 0x800000u);
    goto L_81809508;
L_818094FC:;
    cr_cmp_u(ctx, 0, R(24), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_81809508; }
    R(24) = (0 + 0);
L_81809508:;
    R(3) = (int8_t)R(23);
    GM_CALLV(0x81809510u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809534; }
    R(23) = (0 + 0);
    R(3) = (0 + 0);
    GM_CALLV(0x81809524u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809534; }
    R(3) = (0 + 0);
    goto L_81809940;
L_81809534:;
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 224));
    ctx->ctr = R(12);
    GM_CALLV(0x81809544u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809550; }
    R(23) = (0 + 0);
L_81809550:;
    R(3) = (int8_t)R(23);
    GM_CALLV(0x81809558u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(27) = R(3) |R(3);
    if ((!CR_BIT(ctx, 2))) { goto L_8180956C; }
    R(3) = (0 + 0);
    goto L_81809940;
L_8180956C:;
    R(0) = R(26) ^ 0x80000000u;
    st32(base, (f + 132), R(0));
    { uint32_t ea_ = (R(13) + -14128); ctx->f[2].u = ld64(base, ea_); }
    R(30) = (0 + 0);
    { uint32_t ea_ = (f + 128); ctx->f[1].u = ld64(base, ea_); }
    R(4) = (f + 80);
    { uint32_t ea_ = (R(13) + -14148); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    st32(base, (f + 80), R(3));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(16) |R(16);
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (f + 92), R(22));
    R(0) = ld8(base, (R(17) + 15));
    st8(base, (f + 93), R(0));
    st8(base, (f + 94), R(30));
    GM_CALLV(0x818095B8u, 0x80088100u, 0);
    cr_cmp_u(ctx, 0, R(24), 0x1u);
    R(31) = R(3) |R(3);
    if ((!CR_BIT(ctx, 2))) { goto L_81809748; }
    R(0) = rotl32(R(19), 2) & 0xFFFFFFFCu;
    R(3) = (R(29) + 240);
    R(29) = ld32(base, (R(3) + R(0)));
    cr_cmp_u(ctx, 0, R(29), 0xFu);
    if ((CR_BIT(ctx, 2))) { goto L_818095E0; }
    cr_cmp_u(ctx, 0, R(29), 0x1Fu);
    if ((!CR_BIT(ctx, 2))) { goto L_818096CC; }
L_818095E0:;
    R(0) = ld8(base, (R(17) + 13));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818096C0; }
    R(3) = ld32(base, (R(13) + -22704));
    R(4) = R(26) & 0xFFFFu;
    R(5) = R(28) & 0xFFFFu;
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x81809604u, 0x80077860u, 0);
    cr_cmp_u(ctx, 0, R(29), 0xFu);
    if ((!CR_BIT(ctx, 2))) { goto L_81809668; }
    R(0) = R(26) ^ 0x80000000u;
    st32(base, (f + 124), R(0));
    R(0) = R(25) ^ 0x80000000u;
    { uint32_t ea_ = (R(13) + -14128); ctx->f[2].u = ld64(base, ea_); }
    st32(base, (f + 132), R(0));
    R(5) = (0 + 0);
    { uint32_t ea_ = (f + 120); ctx->f[1].u = ld64(base, ea_); }
    R(3) = R(16) |R(16);
    { uint32_t ea_ = (f + 128); ctx->f[0].u = ld64(base, ea_); }
    R(4) = (f + 64);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld8(base, (R(17) + 12));
    st8(base, (f + 72), R(0));
    st8(base, (f + 73), R(5));
    R(0) = ld8(base, (R(17) + 15));
    st8(base, (f + 74), R(0));
    st8(base, (f + 75), R(23));
    st16(base, (f + 76), R(5));
    GM_CALLV(0x81809664u, 0x80087F40u, 0);
    goto L_818096B8;
L_81809668:;
    R(0) = R(26) ^ 0x80000000u;
    st32(base, (f + 124), R(0));
    R(0) = R(25) ^ 0x80000000u;
    { uint32_t ea_ = (R(13) + -14128); ctx->f[2].u = ld64(base, ea_); }
    st32(base, (f + 132), R(0));
    R(0) = (0 + 0);
    { uint32_t ea_ = (f + 120); ctx->f[1].u = ld64(base, ea_); }
    R(3) = R(16) |R(16);
    { uint32_t ea_ = (f + 128); ctx->f[0].u = ld64(base, ea_); }
    R(4) = (f + 52);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    R(5) = (0 + 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    R(6) = ld8(base, (R(17) + 12));
    st8(base, (f + 60), R(6));
    st8(base, (f + 61), R(23));
    st16(base, (f + 62), R(0));
    GM_CALLV(0x818096B8u, 0x80088030u, 0);
L_818096B8:;
    R(3) = (0 + 0);
    goto L_81809940;
L_818096C0:;
    cr_cmp_u(ctx, 0, R(29), 0x1Fu);
    if ((!CR_BIT(ctx, 2))) { goto L_818096CC; }
    R(29) = (0 + 15);
L_818096CC:;
    cr_cmp_u(ctx, 0, R(29), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_81809814; }
    R(0) = R(26) ^ 0x80000000u;
    st32(base, (f + 124), R(0));
    R(0) = R(25) ^ 0x80000000u;
    { uint32_t ea_ = (R(13) + -14152); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (f + 132), R(0));
    R(4) = (f + 40);
    { uint32_t ea_ = (R(13) + -14128); ctx->f[3].u = ld64(base, ea_); }
    R(5) = (0 + 0);
    { uint32_t ea_ = (f + 120); ctx->f[2].u = ld64(base, ea_); }
    R(6) = (0 + 0);
    { uint32_t ea_ = (f + 128); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[3].d);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[3].d);
    R(3) = ld32(base, (R(13) + -21936));
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8180971Cu, 0x800E76A0u, 0);
    R(0) = (R(3) + -2);
    R(20) = (0 + 1);
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_81809814; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    R(3) = (0 + 0x10000u);
    R(21) = (R(3) + -32768);
    if ((!CR_BIT(ctx, 2))) { goto L_81809814; }
    R(29) = (0 + 5);
    R(20) = (0 + 0);
    goto L_81809814;
L_81809748:;
    cr_cmp_u(ctx, 0, R(24), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_818097C4; }
    R(3) = ld32(base, (R(13) + -22704));
    R(4) = R(26) & 0xFFFFu;
    R(5) = R(28) & 0xFFFFu;
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x81809768u, 0x80077860u, 0);
    R(0) = R(26) ^ 0x80000000u;
    st32(base, (f + 124), R(0));
    R(0) = R(25) ^ 0x80000000u;
    { uint32_t ea_ = (R(13) + -14128); ctx->f[2].u = ld64(base, ea_); }
    st32(base, (f + 132), R(0));
    R(3) = R(16) |R(16);
    { uint32_t ea_ = (f + 120); ctx->f[1].u = ld64(base, ea_); }
    R(4) = (f + 24);
    { uint32_t ea_ = (f + 128); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld8(base, (R(17) + 12));
    st8(base, (f + 32), R(0));
    st8(base, (f + 33), R(30));
    R(0) = ld8(base, (R(17) + 15));
    st8(base, (f + 34), R(0));
    st8(base, (f + 35), R(23));
    st16(base, (f + 36), R(30));
    GM_CALLV(0x818097BCu, 0x80087F40u, 0);
    R(3) = (0 + 0);
    goto L_81809940;
L_818097C4:;
    cr_cmp_s(ctx, 0, (int32_t)R(18), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818097DC; }
    R(0) = rotl32(R(19), 2) & 0xFFFFFFFCu;
    R(3) = (R(29) + 176);
    R(29) = ld32(base, (R(3) + R(0)));
    goto L_81809814;
L_818097DC:;
    R(0) = rotl32(R(19), 2) & 0xFFFFFFFCu;
    R(3) = (R(29) + 0);
    R(29) = ld32(base, (R(3) + R(0)));
    cr_cmp_u(ctx, 0, R(29), 0x1Bu);
    if ((!CR_BIT(ctx, 2))) { goto L_81809814; }
    R(12) = ld32(base, (R(27) + 96));
    R(3) = R(27) |R(27);
    R(12) = ld32(base, (R(12) + 980));
    ctx->ctr = R(12);
    GM_CALLV(0x81809804u, ctx->ctr, 0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(3) = (v_ >> 31); }
    R(29) = (R(3) + 2);
L_81809814:;
    cr_cmp_u(ctx, 0, R(29), 0xCu);
    if ((!CR_BIT(ctx, 2))) { goto L_81809860; }
    cr_cmp_u(ctx, 0, R(24), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81809844; }
    GM_CALLV(0x81809828u, 0x8005FB00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809860; }
    GM_CALLV(0x81809834u, 0x80060AB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809860; }
    R(29) = (0 + 24);
    goto L_81809860;
L_81809844:;
    GM_CALLV(0x81809848u, 0x8005FEF0u, 0);
    R(19) = R(3) |R(3);
    R(3) = R(16) |R(16);
    GM_CALLV(0x81809854u, 0x80088270u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(19));
    if ((CR_BIT(ctx, 0))) { goto L_81809860; }
    R(29) = (0 + 24);
L_81809860:;
    R(0) = ld32(base, (R(27) + 4240));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_81809894; }
    cr_cmp_s(ctx, 0, (int32_t)R(20), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809894; }
    R(3) = ld32(base, (R(13) + -22704));
    R(4) = R(26) & 0xFFFFu;
    R(5) = R(28) & 0xFFFFu;
    R(6) = (0 + 0);
    R(7) = (0 + 14);
    GM_CALLV(0x81809890u, 0x80077860u, 0);
    goto L_818098AC;
L_81809894:;
    R(3) = ld32(base, (R(13) + -22704));
    R(4) = R(26) & 0xFFFFu;
    R(5) = R(28) & 0xFFFFu;
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x818098ACu, 0x80077860u, 0);
L_818098AC:;
    R(0) = R(26) ^ 0x80000000u;
    st32(base, (f + 124), R(0));
    R(0) = R(25) ^ 0x80000000u;
    { uint32_t ea_ = (R(13) + -14152); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (f + 132), R(0));
    R(8) = rotl32(R(31), 31) & 0x80000000u;
    { uint32_t ea_ = (R(13) + -14128); ctx->f[3].u = ld64(base, ea_); }
    R(0) = (int8_t)R(23);
    { uint32_t ea_ = (f + 120); ctx->f[2].u = ld64(base, ea_); }
    R(8) = (rotl32(R(29), 0) & 0x1Fu) | (R(8) & ~0x1Fu);
    { uint32_t ea_ = (f + 128); ctx->f[1].u = ld64(base, ea_); }
    R(3) = rotl32(R(24), 5) & 0xFFFFFFE0u;
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[3].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[3].d);
    R(8) = R(8) |R(3);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    R(8) = R(8) |R(21);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    R(0) = rotl32(R(0), 16) & 0xF0000u;
    R(8) = R(8) |R(0);
    R(5) = (f + 8);
    R(4) = ld8(base, (R(17) + 15));
    R(0) = rotl32(R(22), 29) & 0x60000000u;
    R(3) = (0 + 59);
    R(6) = (0 + 0);
    R(4) = rotl32(R(4), 24) & 0x3000000u;
    R(7) = (0 + 0);
    R(8) = R(8) |R(4);
    R(8) = R(8) |R(0);
    R(4) = R(8) |R(18);
    GM_CALLV(0x8180992Cu, 0x80064610u, 0);
    cr_cmp_u(ctx, 0, R(29), 0xFu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180993C; }
    R(3) = (0 + 0);
    goto L_81809940;
L_8180993C:;
    R(3) = (0 + 1);
L_81809940:;
    R(11) = (f + 208);
    R(0) = lr;
}

/* mod_fn_8008EEC0 (mod_fn_8008EEC0, 8 bytes) */
static void mj_mod_fn_8008EEC0_099a8(GM_CTX) {
    R(3) = (0 + 1);
}

/* mod_beforeExecute__5dEn_cFv (mod_beforeExecute__5dEn_cFv, 508 bytes) */
static void mj_mod_beforeExecute__5dEn_cFv_099b0(GM_CTX) {
    GM_FN(0x818099B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x818099C8u, 0x800643F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818099D8; }
    R(3) = (0 + 0);
    goto L_81809B98;
L_818099D8:;
    R(0) = ld8(base, (R(31) + 912));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809AE0; }
    R(12) = ld32(base, (R(31) + 916));
    R(3) = (R(31) + 916);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x818099F8u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80360000u);
    R(4) = (R(4) + -32764);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x81809A10u, ctx->ctr, 0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(0) = rotl32(R(0), 1) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_81809AE0; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 336));
    ctx->ctr = R(12);
    GM_CALLV(0x81809A34u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809AE0; }
    R(3) = ld32(base, (R(13) + -22136));
    R(3) = ld32(base, (R(3) + 48));
    R(0) = R(3) & 0x2u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81809A84; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 536));
    ctx->ctr = R(12);
    GM_CALLV(0x81809A60u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809AE0; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    R(12) = ld32(base, (R(12) + 324));
    ctx->ctr = R(12);
    GM_CALLV(0x81809A80u, ctx->ctr, 0);
    goto L_81809AE0;
L_81809A84:;
    R(0) = R(3) & 0x4u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81809AC4; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 536));
    ctx->ctr = R(12);
    GM_CALLV(0x81809AA0u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809AE0; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 324));
    ctx->ctr = R(12);
    GM_CALLV(0x81809AC0u, ctx->ctr, 0);
    goto L_81809AE0;
L_81809AC4:;
    R(0) = R(3) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81809AE0; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 532));
    ctx->ctr = R(12);
    GM_CALLV(0x81809AE0u, ctx->ctr, 0);
L_81809AE0:;
    R(0) = ld8(base, (R(31) + 1074));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809B2C; }
    R(0) = ld8(base, (R(31) + 912));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809B20; }
    R(0) = (0 + 1);
    st8(base, (R(31) + 912), R(0));
    R(3) = R(31) |R(31);
    GM_CALLV(0x81809B08u, 0x80097E30u, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = ld32(base, (R(31) + 1060));
    R(12) = ld32(base, (R(12) + 212));
    ctx->ctr = R(12);
    GM_CALLV(0x81809B20u, ctx->ctr, 0);
L_81809B20:;
    R(0) = (0 + 0);
    st8(base, (R(31) + 1074), R(0));
    goto L_81809B78;
L_81809B2C:;
    R(3) = ld8(base, (R(31) + 1292));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809B40; }
    R(0) = (R(3) + -1);
    st8(base, (R(31) + 1292), R(0));
L_81809B40:;
    R(3) = ld16(base, (R(31) + 1280));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809B54; }
    R(0) = (R(3) + -1);
    st16(base, (R(31) + 1280), R(0));
L_81809B54:;
    R(3) = ld16(base, (R(31) + 1282));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809B68; }
    R(0) = (R(3) + -1);
    st16(base, (R(31) + 1282), R(0));
L_81809B68:;
    R(3) = R(31) |R(31);
    R(4) = (0 + -1);
    R(5) = (0 + -1);
    GM_CALLV(0x81809B78u, 0x8180A08Cu, 0);
L_81809B78:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 552));
    ctx->ctr = R(12);
    GM_CALLV(0x81809B8Cu, ctx->ctr, 0);
    R(0) = ld8(base, (R(31) + 11));
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
L_81809B98:;
    R(0) = lr;
}

/* mod_collisionCallback__5dEn_cFP13ActivePhysicsP13ActivePhysics (mod_collisionCallback__5dEn_cFP13ActivePhysicsP13ActivePhysics, 668 bytes) */
static void mj_mod_collisionCallback__5dEn_cFP13ActiveP_09bac(GM_CTX) {
    GM_FN(0x81809BAC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(31) = ld32(base, (R(3) + 4));
    R(28) = ld32(base, (R(4) + 4));
    R(0) = ld8(base, (R(31) + 1074));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809BF4; }
    R(0) = ld8(base, (R(3) + 161));
    R(0) = R(0) | 0x2u;
    st8(base, (R(3) + 161), R(0));
    goto L_81809E28;
L_81809BF4:;
    R(0) = ld8(base, (R(28) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_81809C54; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 228));
    ctx->ctr = R(12);
    GM_CALLV(0x81809C1Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809C34; }
    R(0) = ld8(base, (R(29) + 161));
    R(0) = R(0) | 0x2u;
    st8(base, (R(29) + 161), R(0));
    goto L_81809E28;
L_81809C34:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 244));
    ctx->ctr = R(12);
    GM_CALLV(0x81809C50u, ctx->ctr, 0);
    goto L_81809E28;
L_81809C54:;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81809D04; }
    R(0) = ld32(base, (R(31) + 1276));
    R(0) = R(0) & 0x1000000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_81809C78; }
    { uint32_t ea_ = (R(31) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81809C70u, 0x80096300u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809E28; }
L_81809C78:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 232));
    ctx->ctr = R(12);
    GM_CALLV(0x81809C94u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809CB4; }
    R(0) = ld32(base, (R(29) + 24));
    st32(base, (R(31) + 1076), R(0));
    R(0) = ld8(base, (R(29) + 161));
    R(0) = R(0) | 0x2u;
    st8(base, (R(29) + 161), R(0));
    goto L_81809E28;
L_81809CB4:;
    R(0) = ld8(base, (R(30) + 44));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_81809E28; }
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    GM_CALLV(0x81809CCCu, 0x8180A038u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809E28; }
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    R(5) = (0 + 5);
    GM_CALLV(0x81809CE4u, 0x81809F98u, 0);
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(12) = ld32(base, (R(31) + 96));
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 248));
    ctx->ctr = R(12);
    GM_CALLV(0x81809D00u, ctx->ctr, 0);
    goto L_81809E28;
L_81809D04:;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_81809DF0; }
    R(12) = ld32(base, (R(28) + 96));
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81809D20u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(28) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(0), 0x7u);
    if ((CR_BIT(ctx, 1))) { goto L_81809E28; }
    R(0) = ld8(base, (R(30) + 45));
    cr_cmp_u(ctx, 0, R(0), 0xFu);
    if ((!CR_BIT(ctx, 2))) { goto L_81809D5C; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 340));
    ctx->ctr = R(12);
    GM_CALLV(0x81809D58u, ctx->ctr, 0);
    goto L_81809E28;
L_81809D5C:;
    { uint32_t ea_ = (R(31) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(29) |R(29);
    GM_CALLV(0x81809D68u, 0x80096300u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809E28; }
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 236));
    ctx->ctr = R(12);
    GM_CALLV(0x81809D8Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809DAC; }
    R(0) = ld32(base, (R(29) + 24));
    st32(base, (R(31) + 1076), R(0));
    R(0) = ld8(base, (R(29) + 161));
    R(0) = R(0) | 0x2u;
    st8(base, (R(29) + 161), R(0));
    goto L_81809E28;
L_81809DAC:;
    R(4) = ld8(base, (R(28) + 0));
    R(3) = R(31) |R(31);
    GM_CALLV(0x81809DB8u, 0x8180A01Cu, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81809E28; }
    R(4) = ld8(base, (R(28) + 0));
    R(3) = R(31) |R(31);
    R(5) = (0 + 5);
    GM_CALLV(0x81809DD0u, 0x81809FFCu, 0);
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(12) = ld32(base, (R(31) + 96));
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 252));
    ctx->ctr = R(12);
    GM_CALLV(0x81809DECu, ctx->ctr, 0);
    goto L_81809E28;
L_81809DF0:;
    R(12) = ld32(base, (R(31) + 96));
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 240));
    ctx->ctr = R(12);
    GM_CALLV(0x81809E0Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81809E28; }
    R(0) = ld32(base, (R(29) + 24));
    st32(base, (R(31) + 1076), R(0));
    R(0) = ld8(base, (R(29) + 161));
    R(0) = R(0) | 0x2u;
    st8(base, (R(29) + 161), R(0));
L_81809E28:;
    R(0) = lr;
}

/* mfn_81809F98 (mfn_81809F98, 100 bytes) */
static void mj_mfn_81809F98_09f98(GM_CTX) {
    GM_FN(0x81809F98); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(4) + 96));
    R(30) = R(5) |R(5);
    R(3) = ld32(base, (R(3) + 108));
    ctx->ctr = R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x81809FC8u, ctx->ctr, 0);
    R(4) = ld8(base, (R(3) + 0));
    R(3) = (0 + 255);
    cr_cmp_u(ctx, 0, R(4), 0x7u);
    if ((CR_BIT(ctx, 1))) { goto L_81809FE4; }
    R(3) = R(29) + R(4);
    st8(base, (R(3) + 1284), R(30));
    R(3) = R(30) |R(30);
L_81809FE4:;
    R(0) = lr;
}

/* mfn_81809FFC (mfn_81809FFC, 32 bytes) */
static void mj_mfn_81809FFC_09ffc(GM_CTX) {
    cr_cmp_u(ctx, 0, R(4), 0x7u);
    R(6) = (0 + 255);
    if ((CR_BIT(ctx, 1))) { goto L_8180A014; }
    R(3) = R(3) + R(4);
    R(6) = R(5) |R(5);
    st8(base, (R(3) + 1284), R(5));
L_8180A014:;
    R(3) = R(6) |R(6);
}

/* mfn_8180A01C (mfn_8180A01C, 28 bytes) */
static void mj_mfn_8180A01C_0a01c(GM_CTX) {
    cr_cmp_u(ctx, 0, R(4), 0x7u);
    R(5) = (0 + 255);
    if ((CR_BIT(ctx, 1))) { goto L_8180A030; }
    R(3) = R(3) + R(4);
    R(5) = ld8(base, (R(3) + 1284));
L_8180A030:;
    R(3) = R(5) |R(5);
}

/* mfn_8180A038 (mfn_8180A038, 84 bytes) */
static void mj_mfn_8180A038_0a038(GM_CTX) {
    GM_FN(0x8180A038); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(4) + 96));
    R(3) = ld32(base, (R(3) + 108));
    ctx->ctr = R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x8180A060u, ctx->ctr, 0);
    R(4) = ld8(base, (R(3) + 0));
    R(3) = (0 + 255);
    cr_cmp_u(ctx, 0, R(4), 0x7u);
    if ((CR_BIT(ctx, 1))) { goto L_8180A078; }
    R(3) = R(30) + R(4);
    R(3) = ld8(base, (R(3) + 1284));
L_8180A078:;
    R(0) = lr;
}

/* mfn_8180A08C (mfn_8180A08C, 216 bytes) */
static void mj_mfn_8180A08C_0a08c(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(4), -1);
    if ((CR_BIT(ctx, 2))) { goto L_8180A0C8; }
    cr_cmp_u(ctx, 0, R(4), 0x7u);
    R(6) = (0 + 255);
    if ((CR_BIT(ctx, 1))) { goto L_8180A15C; }
    R(3) = R(3) + R(4);
    R(6) = ld8(base, (R(3) + 1284));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 1);
    if ((CR_BIT(ctx, 0))) { goto L_8180A130; }
    R(4) = R(5) & 0xFFu;
    R(6) = R(6) + R(4);
    cr_cmp_u(ctx, 0, R(6), 0xFFu);
    if ((CR_BIT(ctx, 0))) { goto L_8180A158; }
    R(6) = (0 + 255);
    goto L_8180A158;
L_8180A0C8:;
    R(4) = (0 + 8);
    R(3) = (R(3) + 1283);
    cr_cmp_s(ctx, 0, (int32_t)R(5), 1);
    ctx->ctr = R(4);
    R(4) = R(5) & 0xFFu;
    cr_cmp_s(ctx, 1, (int32_t)R(5), 0);
L_8180A0E0:;
    { uint32_t ea_ = R(3) + 1; R(6) = ld8(base, ea_); R(3) = ea_; }
    if ((CR_BIT(ctx, 0))) { goto L_8180A0FC; }
    R(6) = R(6) + R(4);
    cr_cmp_u(ctx, 5, R(6), 0xFFu);
    if ((CR_BIT(ctx, 20))) { goto L_8180A120; }
    R(6) = (0 + 255);
    goto L_8180A120;
L_8180A0FC:;
    R(7) = R(6) + R(5);
    R(8) = R(7) & 0xFFu;
    R(6) = R(6) & 0xFFu;
    cr_cmp_u(ctx, 5, R(8), R(6));
    R(6) = (0 + 0);
    if ((CR_BIT(ctx, 21))) { goto L_8180A118; }
    R(6) = R(7) |R(7);
L_8180A118:;
    if ((CR_BIT(ctx, 4))) { goto L_8180A120; }
    R(6) = R(7) |R(7);
L_8180A120:;
    st8(base, (R(3) + 0), R(6));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180A0E0; }
    R(6) = (0 + 0);
    goto L_8180A15C;
L_8180A130:;
    R(4) = R(6) + R(5);
    R(7) = R(4) & 0xFFu;
    R(6) = R(6) & 0xFFu;
    cr_cmp_u(ctx, 0, R(7), R(6));
    R(6) = (0 + 0);
    if ((CR_BIT(ctx, 1))) { goto L_8180A14C; }
    R(6) = R(4) |R(4);
L_8180A14C:;
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180A158; }
    R(6) = R(4) |R(4);
L_8180A158:;
    st8(base, (R(3) + 1284), R(6));
L_8180A15C:;
    R(3) = R(6) & 0xFFu;
}

/* mod_fn_80098B60 (mod_fn_80098B60, 264 bytes) */
static void mj_mod_fn_80098B60_0a164(GM_CTX) {
    GM_FN(0x8180A164); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 820));
    ctx->ctr = R(12);
    GM_CALLV(0x8180A19Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180A1B8; }
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    GM_CALLV(0x8180A1B4u, 0x80095C20u, 0);
    goto L_8180A24C;
L_8180A1B8:;
    R(31) = ld32(base, (R(30) + 4));
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(6) = (0 + 2);
    GM_CALLV(0x8180A1D0u, 0x800964A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8180A1EC; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 2))) { goto L_8180A1EC; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180A218; }
    goto L_8180A24C;
L_8180A1EC:;
    R(12) = ld32(base, (R(28) + 96));
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 824));
    ctx->ctr = R(12);
    GM_CALLV(0x8180A200u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180A24C; }
    R(4) = ld32(base, (R(30) + 4));
    R(3) = R(28) |R(28);
    GM_CALLV(0x8180A214u, 0x80098D90u, 0);
    goto L_8180A24C;
L_8180A218:;
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    GM_CALLV(0x8180A228u, 0x80095C20u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 63);
    GM_CALLV(0x8180A234u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180A24C; }
    R(3) = R(28) |R(28);
    R(4) = R(31) |R(31);
    R(5) = (0 + 16);
    GM_CALLV(0x8180A24Cu, 0x81809F98u, 0);
L_8180A24C:;
    R(0) = lr;
}

/* mfn_8180AB68 (mfn_8180AB68, 180 bytes) */
static void mj_mfn_8180AB68_0ab68(GM_CTX) {
    GM_FN(0x8180AB68); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8180AC08; }
    R(8) = (0 + 0x80430000u);
    R(8) = ld32(base, (R(8) + -24752));
    R(6) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(6) = R(8) + R(6);
    R(6) = ld32(base, (R(6) + 4));
    R(8) = ld32(base, (R(6) + 8));
    R(8) = R(8) & 0xFFFFFFFEu;
    cr_cmp_u(ctx, 0, R(8), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180AC08; }
    R(4) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(6) + 80); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(7), 0x0u);
    { uint32_t ea_ = (R(4) + -30892); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x81850000u);
    ctx->f[0].d = ctx->f[0].d / ctx->f[1].d;
    { uint32_t ea_ = (R(4) + -30924); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->f[0].d * ctx->f[1].d;
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[0].u); }
    R(4) = ld32(base, (f + 12));
    R(6) = ld16(base, (R(3) + 0));
    R(4) = R(6) + R(4);
    R(4) = (int16_t)R(4);
    if ((CR_BIT(ctx, 2))) { goto L_8180AC04; }
    R(6) = -(int32_t)R(7);
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(7));
    R(9) = (int16_t)R(6);
    R(8) = R(4) |R(4);
    if ((CR_BIT(ctx, 0))) { goto L_8180ABF4; }
    R(8) = R(7) |R(7);
L_8180ABF4:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(9));
    if ((CR_BIT(ctx, 0))) { goto L_8180AC00; }
    R(6) = R(8) |R(8);
L_8180AC00:;
    R(4) = R(6) |R(6);
L_8180AC04:;
    R(4) = (int16_t)R(4);
L_8180AC08:;
    GM_CALLV(0x8180AC0Cu, 0x8015F4F0u, 0);
    R(0) = lr;
}

/* mod__Z32CheckIfContinueShouldBeActivatedv (mod__Z32CheckIfContinueShouldBeActivatedv, 52 bytes) */
static void mj_mod__Z32CheckIfContinueShouldBeActivated_0b094(GM_CTX) {
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 7564);
    R(3) = (R(3) + -4);
    R(4) = (0 + 0);
L_8180B0A4:;
    { uint32_t ea_ = R(3) + 4; R(5) = ld32(base, ea_); R(3) = ea_; }
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180B0BC; }
    cr_cmp_u(ctx, 0, R(4), 0x1Cu);
    R(4) = (R(4) + 4);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180B0A4; }
L_8180B0BC:;
    R(3) = cntlzw(R(5));
    R(3) = rotl32(R(3), 27) & 0x7FFFFFFu;
}

/* mfn_8180B1E8 (mfn_8180B1E8, 216 bytes) */
static void mj_mfn_8180B1E8_0b1e8(GM_CTX) {
    GM_FN(0x8180B1E8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81850000u);
    R(29) = R(4) |R(4);
    R(3) = (R(3) + 7972);
    st32(base, (R(30) + 0), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8180B248; }
    R(3) = (0 + 4);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    ctx->ctr = R(3);
L_8180B238:;
    { uint32_t ea_ = R(4) + 4; R(6) = ld32(base, ea_); R(4) = ea_; }
    { uint32_t ea_ = R(5) + 4; st32(base, ea_, R(6)); R(5) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180B238; }
    goto L_8180B24C;
L_8180B248:;
    R(3) = (0 + 0);
L_8180B24C:;
    R(5) = (0 + 0x81850000u);
    R(4) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(5) = (R(5) + -26416);
    R(5) = R(4) + R(5);
    R(27) = R(30) + R(4);
    R(26) = (R(5) + -4);
    { uint32_t a_ = R(3); R(25) = 0x8u - a_; ctx->xer_ca = 0x8u >= a_; }
L_8180B268:;
    R(3) = (0 + 148);
    GM_CALLV(0x8180B270u, 0x818432E4u, 0);
    { uint32_t ea_ = R(26) + 4; R(4) = ld32(base, ea_); R(26) = ea_; }
    R(28) = R(3) |R(3);
    GM_CALLV(0x8180B27Cu, 0x800B5B00u, 0);
    R(25) = (R(25) + -1);
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    { uint32_t ea_ = R(27) + 4; st32(base, ea_, R(28)); R(27) = ea_; }
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8180B268; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8180B294u, 0x802B9280u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* ctor_8180B3F0 (ctor_8180B3F0, 128 bytes) */
static void mj_ctor_8180B3F0_0b3f0(GM_CTX) {
    GM_FN(0x8180B3F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -5320));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180B454; }
    R(4) = (0 + 1);
    st8(base, (R(3) + -5320), R(4));
    R(3) = (0 + 0x80370000u);
    R(3) = ld32(base, (R(3) + 31816));
    GM_CALLV(0x8180B42Cu, 0x8016E4F0u, 0);
    R(30) = R(3) |R(3);
    R(3) = (0 + 36);
    GM_CALLV(0x8180B438u, 0x818432E4u, 0);
    R(28) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(28) + -24752));
    R(29) = R(3) |R(3);
    GM_CALLV(0x8180B448u, 0x8180B1E8u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8180B450u, 0x8016E4F0u, 0);
    st32(base, (R(28) + -24752), R(29));
L_8180B454:;
    R(0) = lr;
}

/* ctor_8180B470 (ctor_8180B470, 80 bytes) */
static void mj_ctor_8180B470_0b470(GM_CTX) {
    GM_FN(0x8180B470); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -5312));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180B4B0; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x81850000u);
    st8(base, (R(3) + -5312), R(4));
    R(4) = (0 + 0x81810000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 8036);
    R(4) = (R(4) + -19264);
    R(5) = (R(6) + -5304);
    GM_CALLV(0x8180B4B0u, 0x81844EF4u, 0);
L_8180B4B0:;
    R(0) = lr;
}

/* ctor_8180B514 (ctor_8180B514, 80 bytes) */
static void mj_ctor_8180B514_0b514(GM_CTX) {
    GM_FN(0x8180B514); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -5288));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180B554; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x81850000u);
    st8(base, (R(3) + -5288), R(4));
    R(4) = (0 + 0x81810000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 8084);
    R(4) = (R(4) + -19264);
    R(5) = (R(6) + -5280);
    GM_CALLV(0x8180B554u, 0x81844EF4u, 0);
L_8180B554:;
    R(0) = lr;
}

/* ctor_8180B564 (ctor_8180B564, 80 bytes) */
static void mj_ctor_8180B564_0b564(GM_CTX) {
    GM_FN(0x8180B564); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -5264));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180B5A4; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x81850000u);
    st8(base, (R(3) + -5264), R(4));
    R(4) = (0 + 0x81810000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 8132);
    R(4) = (R(4) + -19264);
    R(5) = (R(6) + -5256);
    GM_CALLV(0x8180B5A4u, 0x81844EF4u, 0);
L_8180B5A4:;
    R(0) = lr;
}

/* mfn_8180BF3C (mfn_8180BF3C, 212 bytes) */
static void mj_mfn_8180BF3C_0bf3c(GM_CTX) {
    GM_FN(0x8180BF3C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    st32(base, (f + 2928), R(3));
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 23456);
    st32(base, (R(30) + 0), R(3));
    R(3) = (R(30) + 8);
    GM_CALLV(0x8180BF78u, 0x8008ED70u, 0);
    R(3) = (0 + 0);
    st32(base, (R(30) + 2908), R(3));
    R(4) = (0 + 0);
    st32(base, (R(30) + 2912), R(3));
    R(5) = (0 + 92);
    st32(base, (R(30) + 2916), R(3));
    st32(base, (R(30) + 2920), R(3));
    R(3) = (R(30) + 2924);
    GM_CALLV(0x8180BF9Cu, 0x81844D68u, 0);
    R(3) = (R(29) + -1);
    R(4) = (f + 19);
    R(5) = (0 + 2908);
    ctx->ctr = R(5);
L_8180BFAC:;
    { uint32_t ea_ = R(3) + 1; R(5) = ld8(base, ea_); R(3) = ea_; }
    { uint32_t ea_ = R(4) + 1; st8(base, ea_, R(5)); R(4) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180BFAC; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8180BFC0u, 0x802B9280u, 0);
    R(3) = (f + 19);
    R(4) = (R(30) + -1);
    R(5) = (0 + 2908);
    ctx->ctr = R(5);
L_8180BFD0:;
    { uint32_t ea_ = R(3) + 1; R(5) = ld8(base, ea_); R(3) = ea_; }
    { uint32_t ea_ = R(4) + 1; st8(base, ea_, R(5)); R(4) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180BFD0; }
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 2928));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8180C00C; }
    R(3) = R(30) |R(30);
    R(0) = lr;
    return;
L_8180C00C:;
    GM_CALLV(0x8180C010u, 0x81844FCCu, 0);
}

/* ctor_8180C414 (ctor_8180C414, 40 bytes) */
static void mj_ctor_8180C414_0c414(GM_CTX) {
    GM_FN(0x8180C414); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -5244);
    GM_CALLV(0x8180C42Cu, 0x800E3AB0u, 0);
    R(0) = lr;
}

/* mfn_8180C440 (mfn_8180C440, 4 bytes) */
static void mj_mfn_8180C440_0c440(GM_CTX) {

}

/* mfn_8180C488 (mfn_8180C488, 4 bytes) */
static void mj_mfn_8180C488_0c488(GM_CTX) {

}

/* mfn_8180C48C (mfn_8180C48C, 96 bytes) */
static void mj_mfn_8180C48C_0c48c(GM_CTX) {
    GM_FN(0x8180C48C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x8180C4A4u, 0x800D2DD0u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 8204);
    st32(base, (R(30) + 0), R(3));
    R(3) = (R(30) + 2084);
    GM_CALLV(0x8180C4B8u, 0x80836C20u, 0);
    R(3) = (R(30) + 2128);
    GM_CALLV(0x8180C4C0u, 0x80836C20u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 8396);
    R(4) = (0 + 15);
    st32(base, (R(30) + 1912), R(3));
    R(3) = R(30) |R(30);
    st32(base, (R(30) + 1916), R(4));
    R(0) = lr;
}

/* mfn_8180C4EC (mfn_8180C4EC, 84 bytes) */
static void mj_mfn_8180C4EC_0c4ec(GM_CTX) {
    GM_FN(0x8180C4EC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8180C510u, 0x800D30E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8180C524; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 2172);
    GM_CALLV(0x8180C524u, 0x818434F4u, 0);
L_8180C524:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mfn_8180C540 (mfn_8180C540, 212 bytes) */
static void mj_mfn_8180C540_0c540(GM_CTX) {
    GM_FN(0x8180C540); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(25) = (0 + 0x81860000u);
    R(28) = R(3) |R(3);
    R(27) = (R(28) + 524);
    R(29) = R(4) |R(4);
    R(3) = ld32(base, (R(25) + -300));
    R(4) = R(5) |R(5);
    R(30) = R(6) |R(6);
    st32(base, (f + 32), R(3));
    R(3) = R(27) |R(27);
    GM_CALLV(0x8180C58Cu, 0x8023A200u, 0);
    R(26) = R(3) |R(3);
    R(3) = ld32(base, (R(28) + 1912));
    R(4) = rotl32(R(30), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(4);
    R(4) = ld32(base, (R(3) + 8));
    R(3) = R(27) |R(27);
    GM_CALLV(0x8180C5A8u, 0x80239E30u, 0);
    st32(base, (f + 24), R(26));
    R(6) = (R(28) + 4);
    st32(base, (f + 28), R(3));
    R(4) = (f + 8);
    st32(base, (f + 8), R(3));
    R(5) = (f + 12);
    R(3) = ld32(base, (f + 24));
    R(7) = (0 + 0);
    R(8) = (0 + 2);
    st32(base, (f + 12), R(3));
    R(3) = R(29) |R(29);
    GM_CALLV(0x8180C5D8u, 0x80166830u, 0);
    R(3) = ld32(base, (R(25) + -300));
    R(4) = ld32(base, (f + 32));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8180C610; }
    R(0) = lr;
    return;
L_8180C610:;
    GM_CALLV(0x8180C614u, 0x81844FCCu, 0);
}

/* mfn_8180C614 (mfn_8180C614, 180 bytes) */
static void mj_mfn_8180C614_0c614(GM_CTX) {
    GM_FN(0x8180C614); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x8180C630u, 0x800D3380u, 0);
    R(3) = (0 + 0x81850000u);
    R(29) = (R(3) + -26151);
    R(4) = (R(30) + 1728);
    R(3) = R(30) |R(30);
    R(5) = R(29) |R(29);
    R(6) = (0 + 4);
    GM_CALLV(0x8180C64Cu, 0x8180C540u, 0);
    R(4) = (R(30) + 1640);
    R(5) = (R(29) + 8);
    R(3) = R(30) |R(30);
    R(6) = (0 + 0);
    GM_CALLV(0x8180C660u, 0x8180C540u, 0);
    R(4) = (R(30) + 1772);
    R(3) = R(30) |R(30);
    R(5) = R(29) |R(29);
    R(6) = (0 + 6);
    GM_CALLV(0x8180C674u, 0x8180C540u, 0);
    R(4) = (R(30) + 2084);
    R(5) = (R(29) + 39);
    R(3) = R(30) |R(30);
    R(6) = (0 + 2);
    GM_CALLV(0x8180C688u, 0x8180C540u, 0);
    R(4) = (R(30) + 1816);
    R(3) = R(30) |R(30);
    R(5) = R(29) |R(29);
    R(6) = (0 + 7);
    GM_CALLV(0x8180C69Cu, 0x8180C540u, 0);
    R(4) = (R(30) + 2128);
    R(5) = (R(29) + 28);
    R(3) = R(30) |R(30);
    R(6) = (0 + 3);
    GM_CALLV(0x8180C6B0u, 0x8180C540u, 0);
    R(0) = lr;
}

/* mfn_8180C6C8 (mfn_8180C6C8, 572 bytes) */
static void mj_mfn_8180C6C8_0c6c8(GM_CTX) {
    GM_FN(0x8180C6C8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(25) = (0 + 0x81860000u);
    R(30) = R(3) |R(3);
    R(5) = ld32(base, (R(25) + -300));
    st32(base, (f + 28), R(5));
    R(3) = ld8(base, (R(3) + 339));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_8180C8BC; }
    R(28) = ld32(base, (R(30) + 1904));
    st8(base, (R(30) + 339), R(4));
    R(3) = R(28) & 0xFFFFFFFEu;
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    R(3) = ld8(base, (R(30) + 337));
    if ((!CR_BIT(ctx, 2))) { goto L_8180C748; }
    R(3) = R(3) ^ 0x7u;
    R(4) = (0 + -30624);
    R(3) = cntlzw(R(3));
    R(3) = rotl32(R(3), 29) & 0x4u;
    R(4) = (R(4) + 0x81850000u);
    { uint32_t ea_ = (R(4) + R(3)); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    goto L_8180C78C;
L_8180C748:;
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8180C76C; }
    R(4) = R(4) ^ 0x2u;
    R(5) = (0 + -30560);
    R(4) = cntlzw(R(4));
    R(4) = rotl32(R(4), 29) & 0x4u;
    R(5) = (R(5) + 0x81850000u);
    R(4) = R(5) + R(4);
    goto L_8180C774;
L_8180C76C:;
    R(4) = (0 + -30800);
    R(4) = (R(4) + 0x81850000u);
L_8180C774:;
    { uint32_t ea_ = (R(4) + 0); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(3), 0x7u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180C78C; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31012); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d + ctx->f[0].d);
L_8180C78C:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8180C794u, 0x800D3CB0u, 0);
    R(27) = R(3) |R(3);
    R(3) = (0 + 0x81850000u);
    R(24) = rotl32(R(28), 2) & 0xFFFFFFFCu;
    R(3) = (R(3) + 8452);
    R(4) = ld32(base, (R(3) + R(24)));
    R(29) = (R(30) + 524);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8180C7B4u, 0x8023A200u, 0);
    R(4) = rotl32(R(28), 7) & 0xFFFFFF80u;
    R(4) = R(30) + R(4);
    R(26) = (R(4) + 1192);
    R(28) = (f + 8);
    st32(base, (f + 24), R(3));
    R(4) = R(26) |R(26);
    st32(base, (f + 8), R(3));
    R(3) = R(27) |R(27);
    R(6) = (0 + 0);
    R(5) = R(28) |R(28);
    R(7) = (0 + 4);
    GM_CALLV(0x8180C7E4u, 0x80166BD0u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31116); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(3) = R(27) |R(27);
    R(4) = (0 + 0);
    ctx->f[1].u = ctx->f[30].u;
    GM_CALLV(0x8180C7FCu, 0x80166F10u, 0);
    R(3) = R(27) |R(27);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = (0 + 0);
    GM_CALLV(0x8180C80Cu, 0x80166EF0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x8180C818u, 0x80169F30u, 0);
    R(4) = ld32(base, (R(30) + 1904));
    R(3) = (0 + 2128);
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    if ((CR_BIT(ctx, 2))) { goto L_8180C82C; }
    R(3) = (0 + 1640);
L_8180C82C:;
    cr_cmp_u(ctx, 0, R(4), 0x2u);
    R(4) = (0 + 2084);
    if ((CR_BIT(ctx, 2))) { goto L_8180C83C; }
    R(4) = R(3) |R(3);
L_8180C83C:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 8468);
    R(27) = R(30) + R(4);
    R(4) = ld32(base, (R(3) + R(24)));
    R(3) = R(29) |R(29);
    GM_CALLV(0x8180C854u, 0x8023A200u, 0);
    R(29) = R(3) |R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8180C860u, 0x800BD0F0u, 0);
    R(30) = R(3) |R(3);
    R(3) = R(27) |R(27);
    R(4) = R(30) |R(30);
    R(5) = R(28) |R(28);
    R(6) = (0 + 0);
    R(7) = (0 + 4);
    st32(base, (f + 20), R(29));
    st32(base, (f + 8), R(29));
    GM_CALLV(0x8180C884u, 0x80166BD0u, 0);
    R(3) = R(27) |R(27);
    ctx->f[1].u = ctx->f[30].u;
    R(4) = (0 + 0);
    GM_CALLV(0x8180C894u, 0x80166F10u, 0);
    R(3) = R(27) |R(27);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = (0 + 0);
    GM_CALLV(0x8180C8A4u, 0x80166EF0u, 0);
    R(3) = ld32(base, (R(30) + 0));
    R(4) = R(27) |R(27);
    R(3) = ld32(base, (R(3) + 24));
    ctx->ctr = R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8180C8BCu, ctx->ctr, 0);
L_8180C8BC:;
    R(3) = ld32(base, (R(25) + -300));
    R(4) = ld32(base, (f + 28));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8180C900; }
    R(0) = lr;
    return;
L_8180C900:;
    GM_CALLV(0x8180C904u, 0x81844FCCu, 0);
}

/* mfn_8180C904 (mfn_8180C904, 636 bytes) */
static void mj_mfn_8180C904_0c904(GM_CTX) {
    GM_FN(0x8180C904); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 1904));
    R(27) = R(4) |R(4);
    R(28) = R(6) |R(6);
    R(29) = R(5) |R(5);
    cr_cmp_u(ctx, 0, R(3), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180C964; }
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180CA00; }
    cr_cmp_u(ctx, 0, R(27), 0x5Cu);
    if ((CR_BIT(ctx, 2))) { goto L_8180C9F0; }
    cr_cmp_u(ctx, 0, R(27), 0x75u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180C964; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 259);
    goto L_8180CA0C;
L_8180C964:;
    R(3) = R(30) |R(30);
    R(4) = R(27) |R(27);
    R(5) = R(29) |R(29);
    R(6) = R(28) |R(28);
    GM_CALLV(0x8180C978u, 0x800D3EF0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8180CA3C; }
    cr_cmp_s(ctx, 0, (int32_t)R(27), 49);
    R(3) = (0 + 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8180C9C0; }
    cr_cmp_s(ctx, 0, (int32_t)R(27), 119);
    if ((CR_BIT(ctx, 1))) { goto L_8180CA5C; }
    cr_cmp_s(ctx, 0, (int32_t)R(27), 90);
    if ((!CR_BIT(ctx, 0))) { goto L_8180CAC8; }
    cr_cmp_u(ctx, 0, R(27), 0x32u);
    if ((CR_BIT(ctx, 2))) { goto L_8180CB30; }
    cr_cmp_u(ctx, 0, R(27), 0x33u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180CA3C; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 370);
    goto L_8180CA0C;
L_8180C9C0:;
    cr_cmp_s(ctx, 0, (int32_t)R(27), 20);
    if ((!CR_BIT(ctx, 1))) { goto L_8180CA84; }
    cr_cmp_s(ctx, 0, (int32_t)R(27), 48);
    if ((!CR_BIT(ctx, 0))) { goto L_8180CAAC; }
    cr_cmp_u(ctx, 0, R(27), 0x15u);
    if ((CR_BIT(ctx, 2))) { goto L_8180CB00; }
    cr_cmp_u(ctx, 0, R(27), 0x2Fu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180CA3C; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 303);
    goto L_8180CA0C;
L_8180C9F0:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 405);
    goto L_8180CA0C;
L_8180CA00:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 75);
L_8180CA0C:;
    R(3) = (R(30) + 532);
    GM_CALLV(0x8180CA14u, 0x8023A0B0u, 0);
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    st32(base, (R(29) + 0), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_8180CA2C; }
    R(3) = ld32(base, (R(30) + 352));
    R(3) = R(3) | 0x400000u;
    st32(base, (R(30) + 352), R(3));
L_8180CA2C:;
    R(3) = ld32(base, (R(30) + 356));
    R(3) = R(3) | 0x400000u;
    st32(base, (R(30) + 356), R(3));
    R(3) = (0 + 1);
L_8180CA3C:;
    R(0) = lr;
    return;
L_8180CA5C:;
    cr_cmp_s(ctx, 0, (int32_t)R(27), 172);
    if ((!CR_BIT(ctx, 0))) { goto L_8180CAE4; }
    cr_cmp_u(ctx, 0, R(27), 0x78u);
    if ((CR_BIT(ctx, 2))) { goto L_8180CB40; }
    cr_cmp_u(ctx, 0, R(27), 0xABu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180CA3C; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 246);
    GM_LOOP(); goto L_8180CA0C;
L_8180CA84:;
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180CB70; }
    cr_cmp_u(ctx, 0, R(27), 0xBu);
    if ((CR_BIT(ctx, 2))) { goto L_8180CB20; }
    cr_cmp_u(ctx, 0, R(27), 0x14u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180CA3C; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 93);
    GM_LOOP(); goto L_8180CA0C;
L_8180CAAC:;
    if ((CR_BIT(ctx, 2))) { goto L_8180CB10; }
    cr_cmp_u(ctx, 0, R(27), 0x31u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180CA3C; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 336);
    GM_LOOP(); goto L_8180CA0C;
L_8180CAC8:;
    if ((CR_BIT(ctx, 2))) { goto L_8180CB50; }
    cr_cmp_u(ctx, 0, R(27), 0x75u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180CA3C; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 220);
    GM_LOOP(); goto L_8180CA0C;
L_8180CAE4:;
    if ((CR_BIT(ctx, 2))) { goto L_8180CB60; }
    cr_cmp_u(ctx, 0, R(27), 0xAFu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180CA3C; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 288);
    GM_LOOP(); goto L_8180CA0C;
L_8180CB00:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 273);
    GM_LOOP(); goto L_8180CA0C;
L_8180CB10:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 319);
    GM_LOOP(); goto L_8180CA0C;
L_8180CB20:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 207);
    GM_LOOP(); goto L_8180CA0C;
L_8180CB30:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 353);
    GM_LOOP(); goto L_8180CA0C;
L_8180CB40:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 184);
    GM_LOOP(); goto L_8180CA0C;
L_8180CB50:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 387);
    GM_LOOP(); goto L_8180CA0C;
L_8180CB60:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 233);
    GM_LOOP(); goto L_8180CA0C;
L_8180CB70:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -26151);
    R(4) = (R(3) + 58);
    GM_LOOP(); goto L_8180CA0C;
}

/* mfn_8180CB80 (mfn_8180CB80, 272 bytes) */
static void mj_mfn_8180CB80_0cb80(GM_CTX) {
    GM_FN(0x8180CB80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(4) + -300));
    st32(base, (f + 28), R(4));
    R(6) = ld32(base, (R(3) + 352));
    R(4) = R(6) & 0x800000u;
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8180CBB4; }
    R(4) = R(6) & 0x1000000u;
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8180CBB4; }
    R(4) = ld32(base, (R(3) + 1904));
    goto L_8180CBB8;
L_8180CBB4:;
    R(4) = (0 + 0);
L_8180CBB8:;
    R(5) = R(6) & 0x400000u;
    CR0(ctx, R(5));
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(5) = (f + 12);
    if ((!CR_BIT(ctx, 2))) { goto L_8180CBF4; }
    R(8) = (0 + 0x3EC10000u);
    R(7) = (0 + 0x3F190000u);
    R(8) = R(8) | 0x625u;
    R(7) = R(7) | 0x999Au;
    st32(base, (f + 16), R(8));
    R(8) = (0 + 0x3EE60000u);
    st32(base, (f + 12), R(7));
    st32(base, (f + 20), R(7));
    R(7) = R(8) | 0x6666u;
    st32(base, (f + 24), R(7));
    goto L_8180CC10;
L_8180CBF4:;
    R(7) = (0 + 0x3F800000u);
    R(8) = (0 + 0x3F200000u);
    st32(base, (f + 12), R(7));
    st32(base, (f + 20), R(7));
    st32(base, (f + 24), R(7));
    R(7) = R(8) | 0xC49Cu;
    st32(base, (f + 16), R(7));
L_8180CC10:;
    { uint32_t ea_ = (R(5) + R(4)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(6) = R(6) & 0x8u;
    CR0(ctx, R(6));
    if ((CR_BIT(ctx, 2))) { goto L_8180CC68; }
    R(7) = (0 + 0x3E4C0000u);
    R(6) = (0 + 0x3E190000u);
    R(7) = R(7) | 0xCCCDu;
    R(6) = R(6) | 0x999Au;
    st32(base, (f + 16), R(7));
    R(7) = (0 + 0x3EBD0000u);
    st32(base, (f + 12), R(6));
    st32(base, (f + 20), R(6));
    R(6) = R(7) | 0x70A4u;
    st32(base, (f + 24), R(6));
    R(3) = ld8(base, (R(3) + 338));
    { uint32_t ea_ = (R(5) + R(4)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(3), 0x3u);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_8180CC68; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30712); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->f[1].d + ctx->f[0].d;
    ctx->f[1].d = frsp(ctx->f[0].d);
L_8180CC68:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 28));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8180CC8C; }
    R(0) = lr;
    return;
L_8180CC8C:;
    GM_CALLV(0x8180CC90u, 0x81844FCCu, 0);
}

/* mod_fn_800CD1A0 (mod_fn_800CD1A0, 124 bytes) */
static void mj_mod_fn_800CD1A0_0cf04(GM_CTX) {
    GM_FN(0x8180CF04); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -22704));
    R(4) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(4) + -404); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    GM_CALLV(0x8180CF2Cu, 0x800789A0u, 0);
    { uint32_t ea_ = (R(13) + -11504); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
L_8180CF40:;
    R(4) = R(31) & 0xFFFFu;
    R(5) = (f + 8);
    R(3) = (0 + 604);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x8180CF58u, 0x80064610u, 0);
    R(31) = (R(31) + 1);
    cr_cmp_u(ctx, 0, R(31), 0x10u);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8180CF40; }
    R(0) = lr;
}

/* mfn_8180D868 (mfn_8180D868, 52 bytes) */
static void mj_mfn_8180D868_0d868(GM_CTX) {
    GM_FN(0x8180D868); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = R(4) |R(4);
    R(5) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(5) + 16));
    ctx->ctr = R(5);
    R(5) = (0 + 0);
    GM_CALLV(0x8180D88Cu, ctx->ctr, 0);
    R(0) = lr;
}

/* mfn_8180D8B4 (mfn_8180D8B4, 604 bytes) */
static void mj_mfn_8180D8B4_0d8b4(GM_CTX) {
    GM_FN(0x8180D8B4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    R(29) = R(3) |R(3);
    R(30) = R(4) |R(4);
    if ((CR_BIT(ctx, 2))) { goto L_8180D8F8; }
    R(3) = (R(29) + -1);
    ctx->ctr = R(30);
L_8180D8E0:;
    { uint32_t ea_ = R(3) + 1; R(4) = ld8(base, ea_); R(3) = ea_; }
    R(4) = (R(4) + -58);
    R(4) = R(4) & 0xFFu;
    cr_cmp_u(ctx, 0, R(4), 0xF6u);
    if ((CR_BIT(ctx, 0))) { goto L_8180D958; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180D8E0; }
L_8180D8F8:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x8180D900u, 0x802E2108u, 0);
    R(4) = (0 + -43);
    R(5) = (R(3) + -43);
    cr_cmp_u(ctx, 0, R(5), R(4));
    if ((CR_BIT(ctx, 1))) { goto L_8180D938; }
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 176);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 181);
L_8180D924:;
    R(6) = R(30) |R(30);
    R(7) = R(29) |R(29);
    GM_CALLV(0x8180D930u, 0x8015F730u, 0);
L_8180D930:;
    R(3) = (0 + 42);
    goto L_8180D93C;
L_8180D938:;
    R(3) = (R(3) + -1);
L_8180D93C:;
    R(3) = R(3) & 0xFFu;
    R(0) = lr;
    return;
L_8180D958:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 20966);
    if ((!CR_BIT(ctx, 1))) { goto L_8180D998; }
    R(3) = (0 + 0x0u);
    R(4) = R(3) | 0x9743u;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(4));
    if ((CR_BIT(ctx, 1))) { goto L_8180D9C8; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 22972);
    if ((!CR_BIT(ctx, 0))) { goto L_8180DA18; }
    cr_cmp_u(ctx, 0, R(5), 0x51E7u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DAB8; }
    cr_cmp_u(ctx, 0, R(5), 0x51E8u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DA98; }
    cr_cmp_u(ctx, 0, R(5), 0x51E9u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DAF8; }
    R(3) = (0 + 31);
    GM_LOOP(); goto L_8180D93C;
L_8180D998:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 16680);
    if ((!CR_BIT(ctx, 1))) { goto L_8180D9F4; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 20964);
    if ((!CR_BIT(ctx, 0))) { goto L_8180DA54; }
    cr_cmp_u(ctx, 0, R(5), 0x4129u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DAE8; }
    cr_cmp_u(ctx, 0, R(5), 0x49BDu);
    if ((CR_BIT(ctx, 2))) { goto L_8180DAD8; }
    cr_cmp_u(ctx, 0, R(5), 0x51E3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DAF8; }
    R(3) = (0 + 25);
    GM_LOOP(); goto L_8180D93C;
L_8180D9C8:;
    R(3) = R(3) | 0x9DA9u;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(3));
    if ((CR_BIT(ctx, 1))) { goto L_8180DA34; }
    cr_cmp_u(ctx, 0, R(5), 0x9744u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DAC0; }
    cr_cmp_u(ctx, 0, R(5), 0x9DA8u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DAA0; }
    cr_cmp_u(ctx, 0, R(5), 0x9DA9u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DAF8; }
    R(3) = (0 + 33);
    GM_LOOP(); goto L_8180D93C;
L_8180D9F4:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 3628);
    if ((CR_BIT(ctx, 0))) { goto L_8180DA70; }
    if ((CR_BIT(ctx, 2))) { goto L_8180DA90; }
    cr_cmp_u(ctx, 0, R(5), 0x1CECu);
    if ((CR_BIT(ctx, 2))) { goto L_8180DA88; }
    cr_cmp_u(ctx, 0, R(5), 0x3F17u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DAF8; }
    R(3) = (0 + 38);
    GM_LOOP(); goto L_8180D93C;
L_8180DA18:;
    if ((CR_BIT(ctx, 2))) { goto L_8180DAC8; }
    cr_cmp_u(ctx, 0, R(5), 0x60A0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180D930; }
    cr_cmp_u(ctx, 0, R(5), 0x7A68u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DAF8; }
    R(3) = (0 + 20);
    GM_LOOP(); goto L_8180D93C;
L_8180DA34:;
    cr_cmp_u(ctx, 0, R(5), 0x9DAAu);
    if ((CR_BIT(ctx, 2))) { goto L_8180DAD0; }
    cr_cmp_u(ctx, 0, R(5), 0xEDD7u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DAA8; }
    cr_cmp_u(ctx, 0, R(5), 0xF0DAu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DAF8; }
    R(3) = (0 + 39);
    GM_LOOP(); goto L_8180D93C;
L_8180DA54:;
    if ((CR_BIT(ctx, 2))) { goto L_8180DAF0; }
    cr_cmp_u(ctx, 0, R(5), 0x51E5u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DAE0; }
    cr_cmp_u(ctx, 0, R(5), 0x51E6u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DAF8; }
    R(3) = (0 + 28);
    GM_LOOP(); goto L_8180D93C;
L_8180DA70:;
    cr_cmp_u(ctx, 0, R(5), 0x2B1u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DAB0; }
    cr_cmp_u(ctx, 0, R(5), 0x7D8u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DAF8; }
    R(3) = (0 + 37);
    GM_LOOP(); goto L_8180D93C;
L_8180DA88:;
    R(3) = (0 + 22);
    GM_LOOP(); goto L_8180D93C;
L_8180DA90:;
    R(3) = (0 + 41);
    GM_LOOP(); goto L_8180D93C;
L_8180DA98:;
    R(3) = (0 + 30);
    GM_LOOP(); goto L_8180D93C;
L_8180DAA0:;
    R(3) = (0 + 32);
    GM_LOOP(); goto L_8180D93C;
L_8180DAA8:;
    R(3) = (0 + 24);
    GM_LOOP(); goto L_8180D93C;
L_8180DAB0:;
    R(3) = (0 + 21);
    GM_LOOP(); goto L_8180D93C;
L_8180DAB8:;
    R(3) = (0 + 29);
    GM_LOOP(); goto L_8180D93C;
L_8180DAC0:;
    R(3) = (0 + 40);
    GM_LOOP(); goto L_8180D93C;
L_8180DAC8:;
    R(3) = (0 + 23);
    GM_LOOP(); goto L_8180D93C;
L_8180DAD0:;
    R(3) = (0 + 34);
    GM_LOOP(); goto L_8180D93C;
L_8180DAD8:;
    R(3) = (0 + 35);
    GM_LOOP(); goto L_8180D93C;
L_8180DAE0:;
    R(3) = (0 + 27);
    GM_LOOP(); goto L_8180D93C;
L_8180DAE8:;
    R(3) = (0 + 19);
    GM_LOOP(); goto L_8180D93C;
L_8180DAF0:;
    R(3) = (0 + 26);
    GM_LOOP(); goto L_8180D93C;
L_8180DAF8:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 176);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 220);
    GM_LOOP(); goto L_8180D924;
}

/* mfn_8180DC20 (mfn_8180DC20, 220 bytes) */
static void mj_mfn_8180DC20_0dc20(GM_CTX) {
    GM_FN(0x8180DC20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = R(4) |R(4);
    R(4) = (0 + 0x0u);
    R(7) = R(4) | 0x89DAu;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(7));
    R(7) = R(3) |R(3);
    if ((CR_BIT(ctx, 1))) { goto L_8180DC68; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 16986);
    if ((!CR_BIT(ctx, 0))) { goto L_8180DC8C; }
    cr_cmp_u(ctx, 0, R(5), 0x25F8u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180DCEC; }
    cr_cmp_u(ctx, 0, R(5), 0x37BFu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DCD0; }
    R(3) = (0 + 2);
    goto L_8180DCEC;
L_8180DC68:;
    R(3) = R(4) | 0xC209u;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(3));
    if ((CR_BIT(ctx, 1))) { goto L_8180DCA0; }
    cr_cmp_u(ctx, 0, R(5), 0x89DBu);
    if ((CR_BIT(ctx, 2))) { goto L_8180DCB8; }
    cr_cmp_u(ctx, 0, R(5), 0x9031u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DCD0; }
    R(3) = (0 + 5);
    goto L_8180DCEC;
L_8180DC8C:;
    if ((CR_BIT(ctx, 2))) { goto L_8180DCC0; }
    cr_cmp_u(ctx, 0, R(5), 0x76A3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DCD0; }
    R(3) = (0 + 6);
    goto L_8180DCEC;
L_8180DCA0:;
    cr_cmp_u(ctx, 0, R(5), 0xC20Au);
    if ((CR_BIT(ctx, 2))) { goto L_8180DCC8; }
    cr_cmp_u(ctx, 0, R(5), 0xE10Cu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DCD0; }
    R(3) = (0 + 7);
    goto L_8180DCEC;
L_8180DCB8:;
    R(3) = (0 + 3);
    goto L_8180DCEC;
L_8180DCC0:;
    R(3) = (0 + 1);
    goto L_8180DCEC;
L_8180DCC8:;
    R(3) = (0 + 4);
    goto L_8180DCEC;
L_8180DCD0:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 1590);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 337);
    GM_CALLV(0x8180DCE8u, 0x8015F730u, 0);
    R(3) = (0 + 8);
L_8180DCEC:;
    R(0) = lr;
}

/* mfn_8180DCFC (mfn_8180DCFC, 644 bytes) */
static void mj_mfn_8180DCFC_0dcfc(GM_CTX) {
    GM_FN(0x8180DCFC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = ld32(base, (R(3) + 20));
    R(4) = ld16(base, (R(3) + 4));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DD94; }
    R(7) = R(4) & 0x4Bu;
    CR0(ctx, R(7));
    if ((!CR_BIT(ctx, 2))) { goto L_8180DD94; }
    R(5) = (R(5) + -1);
    R(7) = R(4) & 0x20u;
    CR0(ctx, R(7));
    R(4) = rotl32(R(4), 8) & 0xFFFFFF00u;
    st32(base, (R(3) + 20), R(5));
    R(4) = (int16_t)R(4);
    R(5) = ld32(base, (R(3) + 12));
    { int32_t v_ = (int32_t)R(4); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFu) != 0; R(4) = (v_ >> 15); }
    R(4) = R(4) + R(6);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DDB0; }
    R(6) = ld8(base, (R(3) + 6));
    cr_cmp_u(ctx, 0, R(6), 0xEu);
    if ((CR_BIT(ctx, 2))) { goto L_8180DE48; }
    cr_cmp_u(ctx, 0, R(6), 0xDu);
    if ((CR_BIT(ctx, 2))) { goto L_8180DDEC; }
    cr_cmp_u(ctx, 0, R(6), 0xCu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DE88; }
    cr_cmp_u(ctx, 0, R(5), 0x12u);
    R(30) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180DD98; }
    cr_cmp_u(ctx, 0, R(4), 0x45u);
    R(30) = (0 + 1);
    if ((CR_BIT(ctx, 1))) { goto L_8180DD98; }
    R(3) = ld32(base, (R(3) + 16));
    GM_CALLV(0x8180DD84u, 0x8180D1F0u, 0);
    R(5) = (0 + 1);
    R(30) = (0 + 1);
    GM_CALLV(0x8180DD90u, 0x8180D66Cu, 0);
    goto L_8180DD98;
L_8180DD94:;
    R(30) = R(4) & 0x1u;
L_8180DD98:;
    R(3) = R(30) |R(30);
    R(0) = lr;
    return;
L_8180DDB0:;
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DE08; }
    cr_cmp_u(ctx, 0, R(5), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DE28; }
    cr_cmp_u(ctx, 0, R(5), 0x1u);
    R(30) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180DD98; }
    R(3) = ld32(base, (R(3) + 16));
    R(4) = (R(4) + -1);
    R(30) = (0 + 1);
    { uint32_t s_ = R(4) & 63; R(4) = s_ > 31 ? 0 : R(30) << s_; }
    R(5) = ld8(base, (R(3) + 0));
    R(4) = R(5) |R(4);
L_8180DDE4:;
    st8(base, (R(3) + 0), R(4));
    GM_LOOP(); goto L_8180DD98;
L_8180DDEC:;
    cr_cmp_u(ctx, 0, R(5), 0x11u);
    R(30) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180DD98; }
    R(5) = (R(4) + -4);
    R(6) = (0 + -3);
    cr_cmp_u(ctx, 0, R(5), R(6));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8180DD98; }
L_8180DE08:;
    R(3) = ld32(base, (R(3) + 16));
    R(4) = (R(4) + -1);
    R(30) = (0 + 1);
    { uint32_t s_ = R(4) & 63; R(4) = s_ > 31 ? 0 : R(30) << s_; }
    R(5) = ld32(base, (R(3) + 0));
    R(4) = R(5) |R(4);
    st32(base, (R(3) + 0), R(4));
    GM_LOOP(); goto L_8180DD98;
L_8180DE28:;
    R(3) = ld32(base, (R(3) + 16));
    R(4) = (R(4) + -1);
    R(30) = (0 + 1);
    { uint32_t s_ = R(4) & 63; R(4) = s_ > 31 ? 0 : R(30) << s_; }
    R(5) = ld16(base, (R(3) + 0));
    R(4) = R(5) |R(4);
    st16(base, (R(3) + 0), R(4));
    GM_LOOP(); goto L_8180DD98;
L_8180DE48:;
    cr_cmp_u(ctx, 0, R(5), 0x2u);
    R(30) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180DD98; }
    R(5) = ld8(base, (R(3) + 32));
    R(30) = (0 + 1);
    cr_cmp_u(ctx, 0, R(5), 0xAu);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180DD98; }
    R(6) = ld8(base, (R(3) + 33));
    cr_cmp_u(ctx, 0, R(6), 0x2Au);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180DD98; }
    R(3) = ld32(base, (R(3) + 16));
    R(5) = ((int32_t)R(5) * 84);
    R(3) = R(3) + R(5);
    R(5) = rotl32(R(6), 1) & 0xFFFFFFFEu;
    st16(base, (R(3) + R(5)), R(4));
    GM_LOOP(); goto L_8180DD98;
L_8180DE88:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 3);
    R(30) = (0 + 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8180DEC4; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 11);
    if ((CR_BIT(ctx, 0))) { goto L_8180DF04; }
    if ((CR_BIT(ctx, 2))) { goto L_8180DF44; }
    cr_cmp_u(ctx, 0, R(5), 0xDu);
    if ((CR_BIT(ctx, 2))) { goto L_8180DF68; }
    cr_cmp_u(ctx, 0, R(5), 0xFu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180DD98; }
    R(3) = ld32(base, (R(3) + 16));
    { uint32_t a_ = R(4); R(5) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(5) < a_; }
    { uint64_t t_ = (uint64_t)(~R(5)) + (R(4)) + ctx->xer_ca; R(4) = t_; ctx->xer_ca = (t_ >> 32); }
    R(30) = (0 + 1);
    GM_LOOP(); goto L_8180DDE4;
L_8180DEC4:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 2);
    if ((!CR_BIT(ctx, 0))) { goto L_8180DEF4; }
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DEDC; }
    cr_cmp_u(ctx, 0, R(5), 0x1u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180DD98; }
L_8180DEDC:;
    R(5) = ld32(base, (R(3) + 16));
    R(30) = (0 + 1);
    R(6) = (R(5) + 1);
    st32(base, (R(3) + 16), R(6));
    st8(base, (R(5) + 0), R(4));
    GM_LOOP(); goto L_8180DD98;
L_8180DEF4:;
    if ((CR_BIT(ctx, 2))) { goto L_8180DF34; }
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DF24; }
    GM_LOOP(); goto L_8180DD98;
L_8180DF04:;
    cr_cmp_u(ctx, 0, R(5), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_8180DF24; }
    cr_cmp_u(ctx, 0, R(5), 0x5u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180DD98; }
    { uint32_t a_ = R(4); R(6) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(6) < a_; }
    R(5) = ld32(base, (R(3) + 16));
    { uint64_t t_ = (uint64_t)(~R(6)) + (R(4)) + ctx->xer_ca; R(4) = t_; ctx->xer_ca = (t_ >> 32); }
    goto L_8180DF6C;
L_8180DF24:;
    R(5) = ld32(base, (R(3) + 16));
    st32(base, (R(5) + 0), R(4));
    R(4) = (R(5) + 4);
    goto L_8180DF74;
L_8180DF34:;
    R(5) = ld32(base, (R(3) + 16));
    st16(base, (R(5) + 0), R(4));
    R(4) = (R(5) + 2);
    goto L_8180DF74;
L_8180DF44:;
    cr_cmp_u(ctx, 0, R(4), 0x7u);
    R(30) = (0 + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8180DD98; }
    R(5) = ld32(base, (R(3) + 28));
    cr_cmp_u(ctx, 0, R(5), 0x8u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180DD98; }
    R(3) = ld32(base, (R(3) + 16));
    st8(base, (R(3) + R(4)), R(5));
    GM_LOOP(); goto L_8180DD98;
L_8180DF68:;
    R(5) = ld32(base, (R(3) + 16));
L_8180DF6C:;
    st8(base, (R(5) + 0), R(4));
    R(4) = (R(5) + 1);
L_8180DF74:;
    st32(base, (R(3) + 16), R(4));
    R(30) = (0 + 1);
    GM_LOOP(); goto L_8180DD98;
}

/* mfn_8180DF80 (mfn_8180DF80, 1632 bytes) */
static void mj_mfn_8180DF80_0df80(GM_CTX) {
    GM_FN(0x8180DF80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 20));
    R(5) = ld16(base, (R(30) + 4));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E000; }
    R(6) = R(5) & 0x4Bu;
    CR0(ctx, R(6));
    if ((!CR_BIT(ctx, 2))) { goto L_8180E000; }
    R(28) = ld32(base, (R(4) + 4));
    R(27) = ld32(base, (R(4) + 0));
    R(4) = (R(3) + -1);
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    st32(base, (R(30) + 20), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_8180E038; }
    R(4) = (R(27) + -1);
    R(5) = (0 + 0);
    ctx->ctr = R(28);
L_8180DFE8:;
    { uint32_t ea_ = R(4) + 1; R(6) = ld8(base, ea_); R(4) = ea_; }
    R(5) = ((int32_t)R(5) * 9);
    R(5) = R(5) + R(6);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180DFE8; }
    R(5) = R(5) & 0xFFFFu;
    goto L_8180E03C;
L_8180E000:;
    R(3) = R(5) & 0x1u;
    CR0(ctx, R(3));
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    if ((CR_BIT(ctx, 2))) { goto L_8180E018; }
    R(6) = (R(4) + 113);
    goto L_8180E01C;
L_8180E018:;
    R(6) = (R(4) + 129);
L_8180E01C:;
    R(3) = (R(4) + 1752);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 436);
    GM_CALLV(0x8180E02Cu, 0x8015F730u, 0);
    R(3) = ld8(base, (R(30) + 5));
    R(29) = R(3) & 0x1u;
    goto L_8180E590;
L_8180E038:;
    R(5) = (0 + 0);
L_8180E03C:;
    R(4) = ld32(base, (R(30) + 12));
    cr_cmp_s(ctx, 1, (int32_t)R(4), 8);
    if ((!CR_BIT(ctx, 5))) { goto L_8180E088; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 12);
    if ((CR_BIT(ctx, 0))) { goto L_8180E19C; }
    if ((CR_BIT(ctx, 2))) { goto L_8180E25C; }
    cr_cmp_u(ctx, 0, R(4), 0xFu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E2B8; }
    cr_cmp_u(ctx, 0, R(4), 0x10u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E2DC; }
    R(3) = ld32(base, (R(30) + 16));
    cr_cmp_u(ctx, 0, R(5), 0x84E2u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E57C; }
    cr_cmp_u(ctx, 0, R(5), 0x8A54u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E3F4; }
    cr_cmp_u(ctx, 0, R(5), 0xA461u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E450; }
    R(4) = ld8(base, (R(3) + 0));
    goto L_8180E588;
L_8180E088:;
    cr_cmp_s(ctx, 1, (int32_t)R(4), 7);
    if ((!CR_BIT(ctx, 4))) { goto L_8180E15C; }
    cr_cmp_u(ctx, 1, R(4), 0x5u);
    if ((CR_BIT(ctx, 6))) { goto L_8180E1E4; }
    cr_cmp_u(ctx, 1, R(4), 0x6u);
    if ((!CR_BIT(ctx, 6))) { goto L_8180E2DC; }
    if ((CR_BIT(ctx, 2))) { goto L_8180E320; }
    R(3) = (R(27) + -1);
    R(5) = (0 + 0);
    R(4) = (0 + -1);
    R(29) = (0 + 0);
    ctx->ctr = R(28);
L_8180E0B8:;
    { uint32_t ea_ = R(3) + 1; R(6) = ld8(base, ea_); R(3) = ea_; }
    R(7) = (R(6) + -58);
    R(7) = R(7) & 0xFFu;
    cr_cmp_u(ctx, 0, R(7), 0xF5u);
    if ((CR_BIT(ctx, 1))) { goto L_8180E0E0; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), -1);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    cr_cmp_u(ctx, 0, R(6), 0x2Eu);
    R(4) = R(5) |R(5);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
L_8180E0E0:;
    R(5) = (R(5) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180E0B8; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), -1);
    if ((CR_BIT(ctx, 2))) { goto L_8180E320; }
    R(29) = (0 + 0);
    R(25) = R(27) |R(27);
    R(3) = R(27) |R(27);
    { uint32_t ea_ = R(25) + R(4); st8(base, ea_, R(29)); R(25) = ea_; }
    GM_CALLV(0x8180E104u, 0x802E2108u, 0);
    R(26) = R(3) |R(3);
    R(3) = (0 + 46);
    cr_cmp_u(ctx, 0, R(26), 0xFFu);
    st8(base, (R(25) + 0), R(3));
    if ((CR_BIT(ctx, 1))) { goto L_8180E590; }
    R(29) = (0 + 0);
    R(3) = (R(25) + 1);
    R(24) = ld8(base, (R(27) + R(28)));
    st8(base, (R(27) + R(28)), R(29));
    GM_CALLV(0x8180E12Cu, 0x802E2108u, 0);
    cr_cmp_u(ctx, 0, R(3), 0xFFu);
    st8(base, (R(27) + R(28)), R(24));
    if ((CR_BIT(ctx, 1))) { goto L_8180E590; }
    R(4) = ld32(base, (R(30) + 12));
    cr_cmp_u(ctx, 0, R(4), 0x6u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E5C0; }
    R(4) = ld32(base, (R(30) + 16));
    R(5) = (R(4) + 2);
    st32(base, (R(30) + 16), R(5));
    st8(base, (R(4) + 0), R(26));
    st8(base, (R(4) + 1), R(3));
    goto L_8180E58C;
L_8180E15C:;
    if ((CR_BIT(ctx, 6))) { goto L_8180E21C; }
    cr_cmp_u(ctx, 0, R(4), 0x8u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E2DC; }
    R(3) = ld32(base, (R(30) + 16));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 26372);
    R(29) = (0 + 1);
    if ((!CR_BIT(ctx, 1))) { goto L_8180E3BC; }
    R(4) = (0 + 0x0u);
    R(4) = R(4) | 0xACBBu;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(4));
    if ((CR_BIT(ctx, 1))) { goto L_8180E428; }
    cr_cmp_u(ctx, 0, R(5), 0x6705u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E4AC; }
    cr_cmp_u(ctx, 0, R(5), 0x7C7Cu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E2D4; }
    goto L_8180E590;
L_8180E19C:;
    cr_cmp_u(ctx, 0, R(4), 0x9u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E288; }
    cr_cmp_u(ctx, 0, R(4), 0xAu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E2DC; }
    R(3) = ld32(base, (R(30) + 16));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 23524);
    R(4) = ld8(base, (R(3) + 0));
    if ((!CR_BIT(ctx, 1))) { goto L_8180E3DC; }
    R(6) = (0 + 0x0u);
    R(6) = R(6) | 0xA5FCu;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(6));
    if ((CR_BIT(ctx, 1))) { goto L_8180E440; }
    cr_cmp_u(ctx, 0, R(5), 0x5BE5u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E584; }
    cr_cmp_u(ctx, 0, R(5), 0x8BBEu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E588; }
    R(4) = (0 + 5);
    goto L_8180E588;
L_8180E1E4:;
    cr_cmp_u(ctx, 0, R(28), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E328; }
    cr_cmp_u(ctx, 0, R(5), 0x72E8u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E328; }
    R(4) = ld32(base, (R(30) + 0));
    R(5) = (0 + 0);
    st32(base, (R(30) + 20), R(3));
    R(6) = (0 + 1);
    R(3) = ld32(base, (R(4) + 16));
    R(29) = (0 + 1);
    ctx->ctr = R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8180E218u, ctx->ctr, 0);
    goto L_8180E590;
L_8180E21C:;
    R(3) = ld32(base, (R(30) + 16));
    R(4) = (0 + 0x0u);
    R(6) = R(4) | 0xB7DDu;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(6));
    R(29) = (0 + 1);
    if ((!CR_BIT(ctx, 1))) { goto L_8180E3FC; }
    R(4) = R(4) | 0xD415u;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(4));
    if ((CR_BIT(ctx, 1))) { goto L_8180E458; }
    cr_cmp_u(ctx, 0, R(5), 0xB7DEu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E4D8; }
    cr_cmp_u(ctx, 0, R(5), 0xC695u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    R(4) = ld8(base, (R(3) + 0));
    R(4) = R(4) | 0x8u;
    goto L_8180E4F8;
L_8180E25C:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8180E268u, 0x8180DC20u, 0);
    R(4) = ld32(base, (R(30) + 12));
    cr_cmp_u(ctx, 0, R(4), 0xCu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E5C0; }
    R(4) = ld32(base, (R(30) + 16));
    st32(base, (R(4) + 0), R(3));
    R(3) = (R(4) + 4);
L_8180E280:;
    st32(base, (R(30) + 16), R(3));
    goto L_8180E58C;
L_8180E288:;
    R(3) = ld32(base, (R(30) + 16));
    R(4) = (0 + 0x0u);
    R(4) = R(4) | 0x81A3u;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(4));
    R(4) = ld8(base, (R(3) + 0));
    if ((CR_BIT(ctx, 1))) { goto L_8180E360; }
    cr_cmp_u(ctx, 0, R(5), 0x3D8Cu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E48C; }
    cr_cmp_u(ctx, 0, R(5), 0x442Eu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E588; }
    R(4) = R(4) | 0x8u;
    goto L_8180E588;
L_8180E2B8:;
    cr_cmp_u(ctx, 0, R(5), 0x70FBu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E420; }
    cr_cmp_u(ctx, 0, R(5), 0x72E8u);
    R(29) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    R(3) = ld32(base, (R(30) + 16));
    R(29) = (0 + 1);
L_8180E2D4:;
    st8(base, (R(3) + 0), R(29));
    goto L_8180E590;
L_8180E2DC:;
    cr_cmp_u(ctx, 0, R(4), 0x11u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E378; }
    R(3) = ld8(base, (R(30) + 6));
    cr_cmp_u(ctx, 0, R(3), 0xDu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E378; }
    R(3) = ld32(base, (R(30) + 16));
    R(4) = (0 + 0x0u);
    R(4) = R(4) | 0xA460u;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(4));
    R(4) = ld32(base, (R(3) + 0));
    if ((CR_BIT(ctx, 1))) { goto L_8180E474; }
    cr_cmp_u(ctx, 0, R(5), 0x263Cu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E558; }
    cr_cmp_u(ctx, 0, R(5), 0x7E49u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E564; }
    R(4) = R(4) | 0x100u;
    goto L_8180E564;
L_8180E320:;
    R(29) = (0 + 0);
    goto L_8180E590;
L_8180E328:;
    cr_cmp_u(ctx, 0, R(28), 0x5u);
    R(29) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    cr_cmp_u(ctx, 0, R(5), 0x70FBu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    R(4) = ld32(base, (R(30) + 0));
    R(5) = (0 + 0);
    st32(base, (R(30) + 20), R(3));
    R(6) = (0 + 0);
    R(3) = ld32(base, (R(4) + 16));
    ctx->ctr = R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8180E35Cu, ctx->ctr, 0);
    goto L_8180E58C;
L_8180E360:;
    cr_cmp_u(ctx, 0, R(5), 0x81A4u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E494; }
    cr_cmp_u(ctx, 0, R(5), 0xBC4Eu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E588; }
    R(4) = R(4) | 0x1u;
    goto L_8180E588;
L_8180E378:;
    cr_cmp_u(ctx, 0, R(4), 0x13u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E52C; }
    cr_cmp_u(ctx, 0, R(4), 0xEu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E500; }
    cr_cmp_u(ctx, 0, R(4), 0xDu);
    R(29) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8180E3A0u, 0x8180D8B4u, 0);
    R(4) = ld32(base, (R(30) + 12));
    cr_cmp_u(ctx, 0, R(4), 0xDu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E5C0; }
    R(4) = ld32(base, (R(30) + 16));
    st8(base, (R(4) + 0), R(3));
    R(3) = (R(4) + 1);
    GM_LOOP(); goto L_8180E280;
L_8180E3BC:;
    cr_cmp_u(ctx, 0, R(5), 0x2803u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E49C; }
    cr_cmp_u(ctx, 0, R(5), 0x57F2u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E4D0; }
    cr_cmp_u(ctx, 0, R(5), 0x60A0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    R(4) = (0 + 0);
    goto L_8180E4F8;
L_8180E3DC:;
    cr_cmp_u(ctx, 0, R(5), 0x2519u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E4A4; }
    cr_cmp_u(ctx, 0, R(5), 0x4816u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E57C; }
    cr_cmp_u(ctx, 0, R(5), 0x4B12u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E588; }
L_8180E3F4:;
    R(4) = (0 + 1);
    goto L_8180E588;
L_8180E3FC:;
    cr_cmp_u(ctx, 0, R(5), 0x2938u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E4BC; }
    cr_cmp_u(ctx, 0, R(5), 0x2F55u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E4F0; }
    cr_cmp_u(ctx, 0, R(5), 0xA0C4u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    R(4) = ld8(base, (R(3) + 0));
    R(4) = R(4) | 0x10u;
    goto L_8180E4F8;
L_8180E420:;
    R(3) = ld32(base, (R(30) + 16));
    goto L_8180E450;
L_8180E428:;
    cr_cmp_u(ctx, 0, R(5), 0xACBCu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E4B4; }
    cr_cmp_u(ctx, 0, R(5), 0xB859u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    R(4) = (0 + 3);
    goto L_8180E4F8;
L_8180E440:;
    cr_cmp_u(ctx, 0, R(5), 0xA5FDu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E4C8; }
    cr_cmp_u(ctx, 0, R(5), 0xDCA1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E588; }
L_8180E450:;
    R(4) = (0 + 0);
    goto L_8180E588;
L_8180E458:;
    cr_cmp_u(ctx, 0, R(5), 0xD416u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E4E4; }
    cr_cmp_u(ctx, 0, R(5), 0xDED8u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E590; }
    R(4) = ld8(base, (R(3) + 0));
    R(4) = R(4) & 0xFEu;
    goto L_8180E4F8;
L_8180E474:;
    cr_cmp_u(ctx, 0, R(5), 0xFC6Eu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E560; }
    cr_cmp_u(ctx, 0, R(5), 0xA461u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E564; }
    R(4) = R(4) | 0x10u;
    goto L_8180E564;
L_8180E48C:;
    R(4) = R(4) | 0x4u;
    goto L_8180E588;
L_8180E494:;
    R(4) = R(4) | 0x2u;
    goto L_8180E588;
L_8180E49C:;
    R(4) = (0 + 2);
    goto L_8180E4F8;
L_8180E4A4:;
    R(4) = (0 + 6);
    goto L_8180E588;
L_8180E4AC:;
    R(4) = (0 + 4);
    goto L_8180E4F8;
L_8180E4B4:;
    R(4) = (0 + 5);
    goto L_8180E4F8;
L_8180E4BC:;
    R(4) = ld8(base, (R(3) + 0));
    R(4) = R(4) | 0x40u;
    goto L_8180E4F8;
L_8180E4C8:;
    R(4) = (0 + 4);
    goto L_8180E588;
L_8180E4D0:;
    R(4) = (0 + 6);
    goto L_8180E4F8;
L_8180E4D8:;
    R(4) = ld8(base, (R(3) + 0));
    R(4) = R(4) | 0x4u;
    goto L_8180E4F8;
L_8180E4E4:;
    R(4) = ld8(base, (R(3) + 0));
    R(4) = R(4) | 0x2u;
    goto L_8180E4F8;
L_8180E4F0:;
    R(4) = ld8(base, (R(3) + 0));
    R(4) = R(4) | 0x20u;
L_8180E4F8:;
    st8(base, (R(3) + 0), R(4));
    goto L_8180E590;
L_8180E500:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8180E50Cu, 0x8180DB10u, 0);
    R(4) = ld32(base, (R(30) + 12));
    cr_cmp_u(ctx, 0, R(4), 0xEu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E5C0; }
    R(4) = ld32(base, (R(30) + 16));
    R(5) = (R(4) + 2);
    st32(base, (R(30) + 16), R(5));
    st16(base, (R(4) + 0), R(3));
    goto L_8180E58C;
L_8180E52C:;
    R(3) = ld32(base, (R(30) + 16));
    R(4) = (0 + 0x0u);
    R(4) = R(4) | 0x8EBFu;
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(4));
    R(4) = ld8(base, (R(3) + 0));
    if ((CR_BIT(ctx, 1))) { goto L_8180E56C; }
    cr_cmp_u(ctx, 0, R(5), 0x4238u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E450; }
    cr_cmp_u(ctx, 0, R(5), 0x8D40u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E3F4; }
    goto L_8180E588;
L_8180E558:;
    R(4) = R(4) | 0x80u;
    goto L_8180E564;
L_8180E560:;
    R(4) = R(4) | 0x20u;
L_8180E564:;
    st32(base, (R(3) + 0), R(4));
    goto L_8180E58C;
L_8180E56C:;
    cr_cmp_u(ctx, 0, R(5), 0x8EC0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E584; }
    cr_cmp_u(ctx, 0, R(5), 0x9CBFu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E588; }
L_8180E57C:;
    R(4) = (0 + 2);
    goto L_8180E588;
L_8180E584:;
    R(4) = (0 + 3);
L_8180E588:;
    st8(base, (R(3) + 0), R(4));
L_8180E58C:;
    R(29) = (0 + 1);
L_8180E590:;
    R(3) = R(29) |R(29);
    R(0) = lr;
    return;
L_8180E5C0:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 67);
    R(5) = (R(4) + 47);
    R(6) = (R(4) + 75);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 248);
    GM_CALLV(0x8180E5E0u, 0x818380F8u, 0);
}

/* mfn_8180E5E0 (mfn_8180E5E0, 224 bytes) */
static void mj_mfn_8180E5E0_0e5e0(GM_CTX) {
    GM_FN(0x8180E5E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 20));
    R(4) = ld16(base, (R(30) + 4));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E63C; }
    R(5) = R(4) & 0x4Bu;
    CR0(ctx, R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_8180E63C; }
    R(4) = ld32(base, (R(30) + 12));
    R(3) = (R(3) + -1);
    st32(base, (R(30) + 20), R(3));
    cr_cmp_u(ctx, 0, R(4), 0xDu);
    if ((CR_BIT(ctx, 2))) { goto L_8180E674; }
    cr_cmp_u(ctx, 0, R(4), 0xCu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E690; }
    R(3) = ld32(base, (R(30) + 16));
    R(4) = (0 + 8);
    st32(base, (R(3) + 0), R(4));
    R(3) = (R(3) + 4);
    goto L_8180E684;
L_8180E63C:;
    R(3) = R(4) & 0x1u;
    CR0(ctx, R(3));
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    if ((CR_BIT(ctx, 2))) { goto L_8180E654; }
    R(6) = (R(4) + 113);
    goto L_8180E658;
L_8180E654:;
    R(6) = (R(4) + 129);
L_8180E658:;
    R(3) = (R(4) + 1703);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 665);
    GM_CALLV(0x8180E668u, 0x8015F730u, 0);
    R(3) = ld8(base, (R(30) + 5));
    R(3) = R(3) & 0x1u;
    goto L_8180E6AC;
L_8180E674:;
    R(3) = ld32(base, (R(30) + 16));
    R(4) = (0 + 42);
    st8(base, (R(3) + 0), R(4));
    R(3) = (R(3) + 1);
L_8180E684:;
    st32(base, (R(30) + 16), R(3));
    R(3) = (0 + 1);
    goto L_8180E6AC;
L_8180E690:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 1527);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 674);
    GM_CALLV(0x8180E6A8u, 0x8015F730u, 0);
    R(3) = (0 + 0);
L_8180E6AC:;
    R(0) = lr;
}

/* mfn_8180E6C0 (mfn_8180E6C0, 3184 bytes) */
static void mj_mfn_8180E6C0_0e6c0(GM_CTX) {
    GM_FN(0x8180E6C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(12) = ctx->cr;
    st32(base, (f + 20), R(12));
    R(27) = ld32(base, (R(4) + 4));
    R(28) = ld32(base, (R(4) + 0));
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E730; }
    R(30) = R(3) |R(3);
    R(3) = (R(28) + -1);
    R(4) = (0 + 0);
    ctx->ctr = R(27);
L_8180E708:;
    { uint32_t ea_ = R(3) + 1; R(5) = ld8(base, ea_); R(3) = ea_; }
    R(4) = ((int32_t)R(4) * 9);
    R(4) = R(4) + R(5);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180E708; }
    R(3) = ld32(base, (R(30) + 20));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180E730; }
    R(5) = ld16(base, (R(30) + 4));
    R(3) = R(5) & 0xEu;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8180E780; }
L_8180E730:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 1498);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 691);
    R(6) = R(27) |R(27);
    R(7) = R(28) |R(28);
    GM_CALLV(0x8180E750u, 0x8015F730u, 0);
    R(3) = (0 + 0);
L_8180E754:;
    R(12) = ld32(base, (f + 20));
    ctx->cr = (ctx->cr & ~0xF00000u) | (R(12) & 0xF00000u);
    R(0) = lr;
    return;
L_8180E780:;
    R(3) = R(5) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8180E79C; }
    R(3) = ld32(base, (R(30) + 8));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 1);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E754; }
    R(5) = R(5) & 0xFFF0u;
L_8180E79C:;
    R(3) = ld8(base, (R(30) + 6));
    R(29) = R(4) & 0xFFFFu;
    cr_cmp_u(ctx, 1, R(3), 0x0u);
    R(3) = R(5) & 0xFF7Fu;
    CR0(ctx, R(3));
    st16(base, (R(30) + 4), R(3));
    if ((CR_BIT(ctx, 6))) { goto L_8180E84C; }
    R(26) = R(5) & 0x10u;
    GM_CALLV(0x8180E7BCu, 0x800CFBB0u, 0);
    R(4) = ld8(base, (R(30) + 24));
    cr_cmp_u(ctx, 0, R(26), 0x0u);
    R(6) = (R(3) + 1696);
    R(4) = (int8_t)R(4);
    if ((CR_BIT(ctx, 2))) { goto L_8180E7D4; }
    R(6) = (R(3) + 8992);
L_8180E7D4:;
    R(5) = ld8(base, (R(30) + 6));
    R(3) = ((int32_t)R(4) * 2432);
    R(4) = R(6) + R(3);
    R(3) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(5), 6);
    if ((CR_BIT(ctx, 1))) { goto L_8180E8D8; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 4);
    if ((!CR_BIT(ctx, 0))) { goto L_8180E944; }
    cr_cmp_u(ctx, 0, R(5), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8180EA6C; }
    cr_cmp_u(ctx, 0, R(5), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_8180EB68; }
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E754; }
    R(3) = (0 + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 24951);
    st32(base, (R(30) + 20), R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_8180EE3C; }
    R(5) = (0 + 0x0u);
    R(5) = R(5) | 0xDFEFu;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(5));
    if ((CR_BIT(ctx, 1))) { goto L_8180EEBC; }
    cr_cmp_u(ctx, 0, R(29), 0x6178u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F158; }
    cr_cmp_u(ctx, 0, R(29), 0xB5E9u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E754; }
    R(5) = (0 + 5);
    st32(base, (R(30) + 12), R(5));
    R(4) = (R(4) + 2404);
    goto L_8180EA64;
L_8180E84C:;
    cr_cmp_u(ctx, 0, R(27), 0x5u);
    if ((CR_BIT(ctx, 0))) { goto L_8180E88C; }
    R(3) = (0 + 0x81850000u);
    R(26) = (R(3) + -23026);
    R(4) = (R(26) + 313);
    R(3) = R(28) |R(28);
    R(5) = (0 + 4);
    GM_CALLV(0x8180E86Cu, 0x802E1BD0u, 0);
    cr_cmp_u(ctx, 2, R(3), 0x0u);
    if ((CR_BIT(ctx, 10))) { goto L_8180E9EC; }
    R(4) = (R(26) + 318);
    R(3) = R(28) |R(28);
    R(5) = (0 + 4);
    GM_CALLV(0x8180E884u, 0x802E1BD0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180E9EC; }
L_8180E88C:;
    GM_CALLV(0x8180E890u, 0x800CFBB0u, 0);
    R(4) = R(3) |R(3);
    R(3) = (0 + 0x0u);
    R(3) = R(3) | 0x896Au;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(3));
    R(3) = (0 + 1);
    st32(base, (R(30) + 20), R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_8180EA4C; }
    cr_cmp_u(ctx, 0, R(29), 0x896Bu);
    if ((CR_BIT(ctx, 2))) { goto L_8180EC5C; }
    cr_cmp_u(ctx, 0, R(29), 0xEEC9u);
    if ((CR_BIT(ctx, 2))) { goto L_8180EC80; }
    cr_cmp_u(ctx, 0, R(29), 0xB87Eu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180ECBC; }
    R(3) = (0 + 6);
    st32(base, (R(30) + 12), R(3));
    R(3) = (R(4) + 4);
L_8180E8D0:;
    st32(base, (R(30) + 16), R(3));
    goto L_8180EDC0;
L_8180E8D8:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 10);
    if ((!CR_BIT(ctx, 0))) { goto L_8180E9AC; }
    cr_cmp_u(ctx, 0, R(5), 0x7u);
    if ((CR_BIT(ctx, 2))) { goto L_8180EAC4; }
    cr_cmp_u(ctx, 0, R(5), 0x8u);
    if ((CR_BIT(ctx, 2))) { goto L_8180EB98; }
    cr_cmp_u(ctx, 0, R(5), 0x9u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E754; }
    R(3) = ld8(base, (R(30) + 32));
    R(5) = (0 + 0x0u);
    R(5) = R(5) | 0xB3B8u;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(5));
    R(5) = (0 + 1);
    st32(base, (R(30) + 20), R(5));
    if ((CR_BIT(ctx, 1))) { goto L_8180ED28; }
    cr_cmp_u(ctx, 0, R(29), 0x39A9u);
    if ((CR_BIT(ctx, 2))) { goto L_8180EFD8; }
    cr_cmp_u(ctx, 0, R(29), 0xA1F7u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180EFA8; }
    R(5) = ld8(base, (R(30) + 34));
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = R(4) + R(3);
    R(4) = (0 + 16);
    R(3) = R(3) + R(5);
    st32(base, (R(30) + 12), R(4));
    R(3) = (R(3) + 1914);
    GM_LOOP(); goto L_8180E8D0;
L_8180E944:;
    if ((CR_BIT(ctx, 2))) { goto L_8180EB0C; }
    cr_cmp_u(ctx, 0, R(5), 0x5u);
    if ((CR_BIT(ctx, 2))) { goto L_8180EBE0; }
    cr_cmp_u(ctx, 0, R(5), 0x6u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E754; }
    R(3) = (R(28) + -1);
    ctx->ctr = R(27);
L_8180E960:;
    { uint32_t ea_ = R(3) + 1; R(4) = ld8(base, ea_); R(3) = ea_; }
    R(4) = (R(4) + -58);
    R(4) = R(4) & 0xFFu;
    cr_cmp_u(ctx, 0, R(4), 0xF5u);
    if ((!CR_BIT(ctx, 1))) { goto L_8180ECE4; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180E960; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x8180E980u, 0x802E2108u, 0);
    R(6) = R(3) |R(3);
    R(3) = (0 + -11);
    R(4) = (R(6) + -11);
    cr_cmp_u(ctx, 0, R(4), R(3));
    if ((CR_BIT(ctx, 1))) { goto L_8180EF1C; }
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 1418);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1077);
    goto L_8180ECFC;
L_8180E9AC:;
    if ((CR_BIT(ctx, 2))) { goto L_8180EB34; }
    cr_cmp_u(ctx, 0, R(5), 0xBu);
    if ((CR_BIT(ctx, 2))) { goto L_8180EC28; }
    cr_cmp_u(ctx, 0, R(5), 0xEu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E754; }
    R(3) = R(28) |R(28);
    R(4) = R(27) |R(27);
    GM_CALLV(0x8180E9CCu, 0x8180DB10u, 0);
    R(4) = R(3) & 0xFF00u;
    cr_cmp_u(ctx, 0, R(4), 0xA00u);
    if ((CR_BIT(ctx, 2))) { goto L_8180ED1C; }
    R(3) = R(3) & 0xFFu;
    cr_cmp_u(ctx, 0, R(3), 0x2Au);
    if ((CR_BIT(ctx, 2))) { goto L_8180ED1C; }
    R(3) = (0 + 1);
    goto L_8180F218;
L_8180E9EC:;
    R(4) = (R(27) + -4);
    R(3) = (R(28) + 3);
    ctx->ctr = R(4);
L_8180E9F8:;
    { uint32_t ea_ = R(3) + 1; R(4) = ld8(base, ea_); R(3) = ea_; }
    R(4) = (R(4) + -58);
    R(4) = R(4) & 0xFFu;
    cr_cmp_u(ctx, 0, R(4), 0xF5u);
    if ((!CR_BIT(ctx, 1))) { goto L_8180ED1C; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180E9F8; }
    R(3) = (R(28) + 4);
    GM_CALLV(0x8180EA18u, 0x802E2108u, 0);
    R(4) = (0 + -4);
    R(5) = (R(3) + -4);
    cr_cmp_u(ctx, 0, R(5), R(4));
    if ((!CR_BIT(ctx, 1))) { goto L_8180ED1C; }
    R(3) = (R(3) + -1);
    st8(base, (R(30) + 24), R(3));
    R(3) = (0 + 8);
    if ((CR_BIT(ctx, 10))) { goto L_8180EA3C; }
    R(3) = (0 + 24);
L_8180EA3C:;
    st16(base, (R(30) + 4), R(3));
    R(3) = (0 + 1);
    st8(base, (R(30) + 6), R(3));
    GM_LOOP(); goto L_8180E754;
L_8180EA4C:;
    cr_cmp_u(ctx, 0, R(29), 0x2B3u);
    if ((CR_BIT(ctx, 2))) { goto L_8180EC98; }
    cr_cmp_u(ctx, 0, R(29), 0x530Bu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180ECBC; }
L_8180EA5C:;
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 6);
L_8180EA64:;
    st32(base, (R(30) + 16), R(4));
    GM_LOOP(); goto L_8180E754;
L_8180EA6C:;
    R(3) = (0 + 0x0u);
    R(5) = R(3) | 0xAC11u;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(5));
    R(5) = (0 + 1);
    st32(base, (R(30) + 20), R(5));
    if ((CR_BIT(ctx, 1))) { goto L_8180ED58; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 26177);
    if ((!CR_BIT(ctx, 1))) { goto L_8180EF48; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 29054);
    if ((!CR_BIT(ctx, 0))) { goto L_8180F0D0; }
    cr_cmp_u(ctx, 0, R(29), 0x6642u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F238; }
    cr_cmp_u(ctx, 0, R(29), 0x68CAu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F2E8; }
    R(5) = (0 + 70);
    st32(base, (R(30) + 20), R(5));
    R(5) = (0 + 12);
    st8(base, (R(30) + 6), R(5));
    R(5) = (0 + 18);
    R(3) = ld16(base, (R(30) + 4));
    R(4) = (R(4) + 1812);
    goto L_8180F2B8;
L_8180EAC4:;
    R(3) = ld8(base, (R(30) + 32));
    R(5) = (0 + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 26589);
    st32(base, (R(30) + 20), R(5));
    if ((!CR_BIT(ctx, 1))) { goto L_8180EE70; }
    R(5) = (0 + 0x0u);
    R(5) = R(5) | 0xC5D8u;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(5));
    if ((CR_BIT(ctx, 1))) { goto L_8180EEDC; }
    cr_cmp_u(ctx, 0, R(29), 0x67DEu);
    if ((CR_BIT(ctx, 2))) { goto L_8180F194; }
    cr_cmp_u(ctx, 0, R(29), 0x6C2Du);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F140; }
    R(3) = R(4) + R(3);
    R(4) = (0 + 8);
    st32(base, (R(30) + 12), R(4));
    R(3) = (R(3) + 15);
    GM_LOOP(); goto L_8180E8D0;
L_8180EB0C:;
    R(3) = R(28) |R(28);
    R(4) = R(27) |R(27);
    R(5) = R(29) |R(29);
    GM_CALLV(0x8180EB1Cu, 0x8180DC20u, 0);
    R(4) = ld16(base, (R(30) + 4));
    cr_cmp_u(ctx, 0, R(3), 0x8u);
    st32(base, (R(30) + 28), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_8180ED98; }
    R(3) = R(4) | 0x1u;
    goto L_8180EDBC;
L_8180EB34:;
    R(3) = R(28) |R(28);
    R(4) = R(27) |R(27);
    R(5) = R(29) |R(29);
    GM_CALLV(0x8180EB44u, 0x8180D8B4u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x2Au);
    st8(base, (R(30) + 33), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_8180EDAC; }
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1012);
    goto L_8180ED18;
L_8180EB68:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 21867);
    if ((!CR_BIT(ctx, 1))) { goto L_8180EE9C; }
    R(3) = (0 + 0x0u);
    R(3) = R(3) | 0x873Eu;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(3));
    if ((CR_BIT(ctx, 1))) { goto L_8180EF04; }
    cr_cmp_u(ctx, 0, R(29), 0x556Cu);
    if ((CR_BIT(ctx, 2))) { goto L_8180F1BC; }
    cr_cmp_u(ctx, 0, R(29), 0x700Au);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F17C; }
    R(4) = (R(4) + 6);
    goto L_8180F208;
L_8180EB98:;
    R(3) = (R(28) + -1);
    ctx->ctr = R(27);
L_8180EBA0:;
    { uint32_t ea_ = R(3) + 1; R(4) = ld8(base, ea_); R(3) = ea_; }
    R(4) = (R(4) + -58);
    R(4) = R(4) & 0xFFu;
    cr_cmp_u(ctx, 0, R(4), 0xF5u);
    if ((!CR_BIT(ctx, 1))) { goto L_8180ED04; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8180EBA0; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x8180EBC0u, 0x802E2108u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x4u);
    if ((CR_BIT(ctx, 0))) { goto L_8180EF30; }
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 971);
    goto L_8180ED18;
L_8180EBE0:;
    R(3) = ld32(base, (R(30) + 28));
    R(5) = (0 + 0x0u);
    R(5) = R(5) | 0x8773u;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(5));
    R(5) = (0 + 1);
    st32(base, (R(30) + 20), R(5));
    if ((CR_BIT(ctx, 1))) { goto L_8180EDC8; }
    cr_cmp_u(ctx, 0, R(29), 0x2443u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F054; }
    cr_cmp_u(ctx, 0, R(29), 0x4AE4u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F0AC; }
    cr_cmp_u(ctx, 0, R(29), 0x6ECAu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F094; }
    R(3) = R(4) + R(3);
    R(4) = (0 + 10);
    st32(base, (R(30) + 12), R(4));
    R(3) = (R(3) + 65);
    GM_LOOP(); goto L_8180E8D0;
L_8180EC28:;
    R(3) = ld8(base, (R(30) + 32));
    R(6) = (0 + 1);
    R(5) = ld8(base, (R(30) + 33));
    cr_cmp_s(ctx, 0, (int32_t)R(29), 29585);
    st32(base, (R(30) + 20), R(6));
    if ((!CR_BIT(ctx, 0))) { goto L_8180EDF4; }
    cr_cmp_u(ctx, 0, R(29), 0x452u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F018; }
    cr_cmp_u(ctx, 0, R(29), 0x4C43u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180EFC0; }
    R(6) = (0 + 4);
    st32(base, (R(30) + 20), R(6));
    goto L_8180EE10;
L_8180EC5C:;
    R(3) = (0 + 2);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 1688);
    R(3) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 16), R(4));
    R(4) = (0 + 10);
    st32(base, (R(30) + 20), R(4));
    R(3) = R(3) | 0x22u;
    goto L_8180EDBC;
L_8180EC80:;
    R(3) = (0 + 0);
    st32(base, (R(30) + 20), R(3));
    R(3) = (0 + 2);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 848);
    goto L_8180ECAC;
L_8180EC98:;
    R(3) = (0 + 0);
    st32(base, (R(30) + 20), R(3));
    R(3) = (0 + 2);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 8);
L_8180ECAC:;
    R(3) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 16), R(4));
    R(4) = (0 + 14);
    goto L_8180EDB4;
L_8180ECBC:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 764);
L_8180ECD0:;
    GM_CALLV(0x8180ECD4u, 0x8015F730u, 0);
    R(4) = (0 + 0);
    R(3) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 20), R(4));
    goto L_8180ED20;
L_8180ECE4:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 1444);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1068);
    R(6) = R(28) |R(28);
L_8180ECFC:;
    GM_CALLV(0x8180ED00u, 0x8015F730u, 0);
    goto L_8180ED1C;
L_8180ED04:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 962);
L_8180ED18:;
    GM_CALLV(0x8180ED1Cu, 0x8015F730u, 0);
L_8180ED1C:;
    R(3) = ld16(base, (R(30) + 4));
L_8180ED20:;
    R(3) = R(3) | 0x1u;
    goto L_8180EDBC;
L_8180ED28:;
    cr_cmp_u(ctx, 0, R(29), 0xB62Au);
    if ((CR_BIT(ctx, 2))) { goto L_8180EFF8; }
    cr_cmp_u(ctx, 0, R(29), 0xB3B9u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180EFA8; }
    R(5) = ld8(base, (R(30) + 34));
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(4) = R(4) + R(3);
    R(3) = (0 + 1);
    R(4) = R(4) + R(5);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 83);
    GM_LOOP(); goto L_8180EA64;
L_8180ED58:;
    R(3) = R(3) | 0xC4C3u;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_8180EF80; }
    R(3) = (0 + 0x0u);
    R(3) = R(3) | 0xF85Cu;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(3));
    if ((CR_BIT(ctx, 1))) { goto L_8180F0F0; }
    cr_cmp_u(ctx, 0, R(29), 0xC4C4u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F254; }
    cr_cmp_u(ctx, 0, R(29), 0xE3FAu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F2E8; }
    R(4) = (0 + 0);
    R(3) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 20), R(4));
    R(4) = (0 + 2);
    goto L_8180EDB4;
L_8180ED98:;
    R(3) = R(4) | 0x8u;
    st16(base, (R(30) + 4), R(3));
    R(3) = (0 + 5);
    st8(base, (R(30) + 6), R(3));
    goto L_8180EDC0;
L_8180EDAC:;
    R(3) = ld16(base, (R(30) + 4));
    R(4) = (0 + 11);
L_8180EDB4:;
    st8(base, (R(30) + 6), R(4));
L_8180EDB8:;
    R(3) = R(3) | 0x8u;
L_8180EDBC:;
    st16(base, (R(30) + 4), R(3));
L_8180EDC0:;
    R(3) = (0 + 1);
    GM_LOOP(); goto L_8180E754;
L_8180EDC8:;
    cr_cmp_u(ctx, 0, R(29), 0x8774u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F068; }
    cr_cmp_u(ctx, 0, R(29), 0xF85Du);
    if ((CR_BIT(ctx, 2))) { goto L_8180F0C0; }
    cr_cmp_u(ctx, 0, R(29), 0xB308u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F094; }
    R(4) = R(4) + R(3);
    R(3) = (0 + 1);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 25);
    GM_LOOP(); goto L_8180EA64;
L_8180EDF4:;
    if ((CR_BIT(ctx, 2))) { goto L_8180F038; }
    cr_cmp_u(ctx, 0, R(29), 0xB682u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180EFC0; }
    R(6) = (0 + 3);
    st32(base, (R(30) + 20), R(6));
    R(6) = (0 + 13);
    st8(base, (R(30) + 6), R(6));
L_8180EE10:;
    R(6) = ld16(base, (R(30) + 4));
    R(3) = ((int32_t)R(3) * 168);
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(3) = R(4) + R(3);
    R(3) = R(3) + R(5);
    R(4) = (0 + 17);
    R(3) = (R(3) + 132);
    st32(base, (R(30) + 12), R(4));
    st32(base, (R(30) + 16), R(3));
    R(3) = R(6) | 0x2u;
    GM_LOOP(); goto L_8180EDBC;
L_8180EE3C:;
    cr_cmp_u(ctx, 0, R(29), 0x3C39u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F110; }
    cr_cmp_u(ctx, 0, R(29), 0x4129u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F1CC; }
    cr_cmp_u(ctx, 0, R(29), 0x4872u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E754; }
    R(5) = (0 + 12);
    R(4) = (R(4) + 2384);
    st32(base, (R(30) + 12), R(5));
    R(5) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 16), R(4));
    R(4) = (0 + 2);
    goto L_8180F1E4;
L_8180EE70:;
    cr_cmp_u(ctx, 0, R(29), 0x20DDu);
    if ((CR_BIT(ctx, 2))) { goto L_8180F12C; }
    cr_cmp_u(ctx, 0, R(29), 0x3FE9u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F1F4; }
    cr_cmp_u(ctx, 0, R(29), 0x6382u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F140; }
    R(3) = R(4) + R(3);
    R(4) = (0 + 15);
    st32(base, (R(30) + 12), R(4));
    R(3) = (R(3) + 73);
    GM_LOOP(); goto L_8180E8D0;
L_8180EE9C:;
    cr_cmp_u(ctx, 0, R(29), 0x157Eu);
    if ((CR_BIT(ctx, 2))) { goto L_8180F164; }
    cr_cmp_u(ctx, 0, R(29), 0x1FD4u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F204; }
    cr_cmp_u(ctx, 0, R(29), 0x4B12u);
    R(4) = (R(4) + 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180F208; }
    goto L_8180F17C;
L_8180EEBC:;
    cr_cmp_u(ctx, 0, R(29), 0xDFF0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F16C; }
    cr_cmp_u(ctx, 0, R(29), 0xF05Cu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8180E754; }
    R(5) = (0 + 14);
    st32(base, (R(30) + 12), R(5));
    R(4) = (R(4) + 2376);
    GM_LOOP(); goto L_8180EA64;
L_8180EEDC:;
    cr_cmp_u(ctx, 0, R(29), 0xC5D9u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F1A8; }
    cr_cmp_u(ctx, 0, R(29), 0xDB5Au);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F140; }
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F300; }
    R(3) = (0 + 5);
    st32(base, (R(30) + 12), R(3));
    R(3) = (R(4) + 7);
    GM_LOOP(); goto L_8180E8D0;
L_8180EF04:;
    cr_cmp_u(ctx, 0, R(29), 0x873Fu);
    if ((CR_BIT(ctx, 2))) { goto L_8180F1C4; }
    cr_cmp_u(ctx, 0, R(29), 0xE7D2u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F17C; }
    R(4) = (R(4) + 4);
    goto L_8180F208;
L_8180EF1C:;
    R(3) = ld16(base, (R(30) + 4));
    R(4) = (0 + 7);
    st8(base, (R(30) + 6), R(4));
    R(4) = (R(6) + -1);
    goto L_8180EF78;
L_8180EF30:;
    R(4) = ld16(base, (R(30) + 4));
    st8(base, (R(30) + 34), R(3));
    R(3) = (0 + 9);
    st8(base, (R(30) + 6), R(3));
    R(3) = R(4) | 0x8u;
    GM_LOOP(); goto L_8180EDBC;
L_8180EF48:;
    cr_cmp_u(ctx, 0, R(29), 0x670u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F294; }
    cr_cmp_u(ctx, 0, R(29), 0x1EFBu);
    if ((CR_BIT(ctx, 2))) { goto L_8180F2C8; }
    cr_cmp_u(ctx, 0, R(29), 0x4E30u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F2E8; }
    R(4) = (0 + 0);
    st32(base, (R(30) + 20), R(4));
    R(4) = (0 + 6);
    R(3) = ld16(base, (R(30) + 4));
    st8(base, (R(30) + 6), R(4));
    R(4) = (0 + 10);
L_8180EF78:;
    st8(base, (R(30) + 32), R(4));
    GM_LOOP(); goto L_8180EDB8;
L_8180EF80:;
    cr_cmp_u(ctx, 0, R(29), 0xAC12u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F2A4; }
    cr_cmp_u(ctx, 0, R(29), 0xB62Au);
    if ((CR_BIT(ctx, 2))) { goto L_8180F2D8; }
    cr_cmp_u(ctx, 0, R(29), 0xB87Eu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F2E8; }
    R(3) = (0 + 6);
    st32(base, (R(30) + 16), R(4));
    st32(base, (R(30) + 12), R(3));
    GM_LOOP(); goto L_8180EDC0;
L_8180EFA8:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1000);
    GM_LOOP(); goto L_8180ECD0;
L_8180EFC0:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1056);
    GM_LOOP(); goto L_8180ECD0;
L_8180EFD8:;
    R(5) = ld8(base, (R(30) + 34));
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(4) = R(4) + R(3);
    R(3) = (0 + 1);
    R(4) = R(4) + R(5);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 1834);
    GM_LOOP(); goto L_8180EA64;
L_8180EFF8:;
    R(5) = ld8(base, (R(30) + 34));
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = R(4) + R(3);
    R(4) = (0 + 0);
    R(3) = R(3) + R(5);
    st32(base, (R(30) + 12), R(4));
    R(3) = (R(3) + 1874);
    GM_LOOP(); goto L_8180E8D0;
L_8180F018:;
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F220; }
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F220; }
    R(3) = (0 + 1);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 2374);
    GM_LOOP(); goto L_8180EA64;
L_8180F038:;
    R(3) = ((int32_t)R(3) * 42);
    R(4) = R(4) + R(3);
    R(3) = (0 + 1);
    R(4) = R(4) + R(5);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 1954);
    GM_LOOP(); goto L_8180EA64;
L_8180F054:;
    R(4) = R(4) + R(3);
    R(3) = (0 + 1);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 41);
    GM_LOOP(); goto L_8180EA64;
L_8180F068:;
    R(5) = ld16(base, (R(30) + 4));
    R(3) = R(4) + R(3);
    R(4) = (0 + 8);
    st32(base, (R(30) + 20), R(4));
    R(4) = (0 + 0);
    { uint32_t ea_ = R(3) + 49; st8(base, ea_, R(4)); R(3) = ea_; }
    R(4) = (0 + 9);
    st32(base, (R(30) + 12), R(4));
    st32(base, (R(30) + 16), R(3));
    R(3) = R(5) | 0x2u;
    GM_LOOP(); goto L_8180EDBC;
L_8180F094:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 950);
    GM_LOOP(); goto L_8180ECD0;
L_8180F0AC:;
    R(3) = R(4) + R(3);
    R(4) = (0 + 0);
    st32(base, (R(30) + 12), R(4));
    R(3) = (R(3) + 33);
    GM_LOOP(); goto L_8180E8D0;
L_8180F0C0:;
    R(3) = (0 + 11);
    st32(base, (R(30) + 12), R(3));
    R(3) = (R(4) + 57);
    GM_LOOP(); goto L_8180E8D0;
L_8180F0D0:;
    if ((CR_BIT(ctx, 2))) { goto L_8180F264; }
    cr_cmp_u(ctx, 0, R(29), 0xA748u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F2E8; }
    R(4) = (0 + 0);
    R(3) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 20), R(4));
    R(4) = (0 + 3);
    GM_LOOP(); goto L_8180EDB4;
L_8180F0F0:;
    cr_cmp_u(ctx, 0, R(29), 0xF85Du);
    if ((CR_BIT(ctx, 2))) { goto L_8180F274; }
    cr_cmp_u(ctx, 0, R(29), 0xF87Cu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F2E8; }
    R(3) = (0 + 19);
    st32(base, (R(30) + 12), R(3));
    R(3) = (R(4) + 2408);
    GM_LOOP(); goto L_8180E8D0;
L_8180F110:;
    R(5) = ld16(base, (R(30) + 4));
    R(3) = (R(4) + 2378);
    st32(base, (R(30) + 16), R(3));
    R(3) = (0 + 1);
    R(4) = R(5) | 0x80u;
    st32(base, (R(30) + 12), R(3));
    goto L_8180F1EC;
L_8180F12C:;
    R(4) = (0 + 0);
    R(3) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 20), R(4));
    R(4) = (0 + 8);
    GM_LOOP(); goto L_8180EDB4;
L_8180F140:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1139);
    GM_LOOP(); goto L_8180ECD0;
L_8180F158:;
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 2379);
    GM_LOOP(); goto L_8180EA64;
L_8180F164:;
    R(4) = (R(4) + 5);
    goto L_8180F208;
L_8180F16C:;
    R(5) = (0 + 4);
    R(4) = (R(4) + 2380);
    st32(base, (R(30) + 12), R(5));
    GM_LOOP(); goto L_8180EA64;
L_8180F17C:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 899);
    GM_LOOP(); goto L_8180ECD0;
L_8180F194:;
    R(3) = R(4) + R(3);
    R(4) = (0 + 13);
    st32(base, (R(30) + 12), R(4));
    R(3) = (R(3) + 1824);
    GM_LOOP(); goto L_8180E8D0;
L_8180F1A8:;
    R(4) = (0 + 0);
    R(3) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 20), R(4));
    R(4) = (0 + 10);
    GM_LOOP(); goto L_8180EDB4;
L_8180F1BC:;
    R(4) = (R(4) + 2);
    goto L_8180F208;
L_8180F1C4:;
    R(4) = (R(4) + 3);
    goto L_8180F208;
L_8180F1CC:;
    R(5) = (0 + 12);
    st32(base, (R(30) + 12), R(5));
    R(4) = (R(4) + 2392);
    R(5) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 16), R(4));
    R(4) = (0 + 3);
L_8180F1E4:;
    st32(base, (R(30) + 20), R(4));
    R(4) = R(5) | 0x2u;
L_8180F1EC:;
    st16(base, (R(30) + 4), R(4));
    GM_LOOP(); goto L_8180E754;
L_8180F1F4:;
    cr_cmp_u(ctx, 0, R(3), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F318; }
    R(3) = (0 + 1);
    GM_LOOP(); goto L_8180EA5C;
L_8180F204:;
    R(4) = (R(4) + 1);
L_8180F208:;
    R(3) = (0 + 1);
    R(4) = (R(4) + 8);
    st32(base, (R(30) + 12), R(3));
    st32(base, (R(30) + 16), R(4));
L_8180F218:;
    st32(base, (R(30) + 20), R(3));
    GM_LOOP(); goto L_8180E754;
L_8180F220:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1047);
    GM_LOOP(); goto L_8180ECD0;
L_8180F238:;
    R(3) = ld16(base, (R(30) + 4));
    R(4) = (R(4) + 3);
    R(3) = R(3) | 0x80u;
    st16(base, (R(30) + 4), R(3));
    R(3) = (0 + 1);
    st32(base, (R(30) + 12), R(3));
    GM_LOOP(); goto L_8180EA64;
L_8180F254:;
    R(3) = (0 + 3);
    st32(base, (R(30) + 12), R(3));
    R(3) = (R(4) + 128);
    GM_LOOP(); goto L_8180E8D0;
L_8180F264:;
    R(3) = (0 + 2);
    st32(base, (R(30) + 12), R(3));
    R(3) = (R(4) + 124);
    GM_LOOP(); goto L_8180E8D0;
L_8180F274:;
    R(4) = (0 + 0);
    st32(base, (R(30) + 20), R(4));
    R(4) = (0 + 4);
    st8(base, (R(30) + 6), R(4));
    R(4) = (0 + 8);
    R(3) = ld16(base, (R(30) + 4));
    st32(base, (R(30) + 28), R(4));
    GM_LOOP(); goto L_8180EDB8;
L_8180F294:;
    R(3) = (0 + 4);
    st32(base, (R(30) + 12), R(3));
    R(3) = (R(4) + 2412);
    GM_LOOP(); goto L_8180E8D0;
L_8180F2A4:;
    R(3) = ld16(base, (R(30) + 4));
    R(5) = (0 + 8);
    st32(base, (R(30) + 20), R(5));
    R(5) = (0 + 7);
    R(4) = (R(4) + 2);
L_8180F2B8:;
    st32(base, (R(30) + 12), R(5));
    st32(base, (R(30) + 16), R(4));
    R(3) = R(3) | 0x2u;
    GM_LOOP(); goto L_8180EDBC;
L_8180F2C8:;
    R(3) = (0 + 1);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 4);
    GM_LOOP(); goto L_8180EA64;
L_8180F2D8:;
    R(3) = (0 + 1);
    st32(base, (R(30) + 12), R(3));
    R(4) = (R(4) + 5);
    GM_LOOP(); goto L_8180EA64;
L_8180F2E8:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 865);
    GM_LOOP(); goto L_8180ECD0;
L_8180F300:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1129);
    GM_LOOP(); goto L_8180ECD0;
L_8180F318:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 24);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1118);
    GM_LOOP(); goto L_8180ECD0;
}

/* mfn_8180F330 (mfn_8180F330, 108 bytes) */
static void mj_mfn_8180F330_0f330(GM_CTX) {
    GM_FN(0x8180F330); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld16(base, (R(3) + 4));
    R(5) = R(4) & 0x1u;
    CR0(ctx, R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_8180F370; }
    R(5) = R(4) & 0x8u;
    CR0(ctx, R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_8180F380; }
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 1624);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1204);
    GM_CALLV(0x8180F368u, 0x8015F730u, 0);
    R(3) = (0 + 0);
    goto L_8180F38C;
L_8180F370:;
    R(4) = ld32(base, (R(3) + 8));
    R(4) = (R(4) + 1);
    st32(base, (R(3) + 8), R(4));
    goto L_8180F388;
L_8180F380:;
    R(4) = R(4) & 0xFFF6u;
    CR0(ctx, R(4));
    st16(base, (R(3) + 4), R(4));
L_8180F388:;
    R(3) = (0 + 1);
L_8180F38C:;
    R(0) = lr;
}

/* mfn_8180F39C (mfn_8180F39C, 428 bytes) */
static void mj_mfn_8180F39C_0f39c(GM_CTX) {
    GM_FN(0x8180F39C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld16(base, (R(3) + 4));
    R(5) = R(4) & 0x1u;
    CR0(ctx, R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_8180F3F4; }
    R(4) = R(4) & 0x48u;
    CR0(ctx, R(4));
    R(30) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F514; }
    R(4) = ld8(base, (R(3) + 6));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 5);
    if ((!CR_BIT(ctx, 1))) { goto L_8180F428; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 8);
    if ((!CR_BIT(ctx, 1))) { goto L_8180F44C; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 11);
    if ((!CR_BIT(ctx, 0))) { goto L_8180F4A0; }
    cr_cmp_u(ctx, 0, R(4), 0x9u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F4B8; }
    cr_cmp_u(ctx, 0, R(4), 0xAu);
    if ((CR_BIT(ctx, 2))) { goto L_8180F464; }
    goto L_8180F52C;
L_8180F3F4:;
    R(5) = ld32(base, (R(3) + 8));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F420; }
    R(5) = (R(5) + -1);
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    R(30) = (0 + 1);
    st32(base, (R(3) + 8), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_8180F514; }
    R(4) = R(4) & 0xFFFEu;
    st16(base, (R(3) + 4), R(4));
    goto L_8180F514;
L_8180F420:;
    R(30) = (0 + 0);
    goto L_8180F514;
L_8180F428:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 3);
    if ((!CR_BIT(ctx, 0))) { goto L_8180F46C; }
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F4F4; }
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F500; }
    cr_cmp_u(ctx, 0, R(4), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F494; }
    goto L_8180F52C;
L_8180F44C:;
    cr_cmp_u(ctx, 0, R(4), 0x6u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F494; }
    cr_cmp_u(ctx, 0, R(4), 0x7u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F4E0; }
    cr_cmp_u(ctx, 0, R(4), 0x8u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F52C; }
L_8180F464:;
    R(4) = (0 + 7);
    goto L_8180F4B0;
L_8180F46C:;
    if ((CR_BIT(ctx, 2))) { goto L_8180F494; }
    cr_cmp_u(ctx, 0, R(4), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F494; }
    cr_cmp_u(ctx, 0, R(4), 0x5u);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F52C; }
    R(4) = (0 + 4);
    st8(base, (R(3) + 6), R(4));
    R(4) = (0 + 8);
    st32(base, (R(3) + 28), R(4));
    goto L_8180F510;
L_8180F494:;
    R(30) = (0 + 1);
    st8(base, (R(3) + 6), R(30));
    goto L_8180F514;
L_8180F4A0:;
    if ((CR_BIT(ctx, 2))) { goto L_8180F4CC; }
    cr_cmp_u(ctx, 0, R(4), 0xEu);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F52C; }
    R(4) = (0 + 0);
L_8180F4B0:;
    st8(base, (R(3) + 6), R(4));
    goto L_8180F510;
L_8180F4B8:;
    R(4) = (0 + 8);
    st8(base, (R(3) + 6), R(4));
    R(4) = (0 + 4);
    st8(base, (R(3) + 34), R(4));
    goto L_8180F510;
L_8180F4CC:;
    R(4) = (0 + 10);
    st8(base, (R(3) + 6), R(4));
    R(4) = (0 + 42);
    st8(base, (R(3) + 33), R(4));
    goto L_8180F510;
L_8180F4E0:;
    R(4) = (0 + 6);
    st8(base, (R(3) + 6), R(4));
    R(4) = (0 + 10);
    st8(base, (R(3) + 32), R(4));
    goto L_8180F510;
L_8180F4F4:;
    R(4) = (0 + 64);
    st16(base, (R(3) + 4), R(4));
    goto L_8180F510;
L_8180F500:;
    R(4) = (0 + 0);
    st8(base, (R(3) + 6), R(4));
    R(4) = (0 + 255);
    st8(base, (R(3) + 24), R(4));
L_8180F510:;
    R(30) = (0 + 1);
L_8180F514:;
    R(3) = R(30) |R(30);
    R(0) = lr;
    return;
L_8180F52C:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -23026);
    R(3) = (R(4) + 1557);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 1271);
    GM_CALLV(0x8180F544u, 0x8015F730u, 0);
    GM_LOOP(); goto L_8180F514;
}

/* mfn_8180F548 (mfn_8180F548, 68 bytes) */
static void mj_mfn_8180F548_0f548(GM_CTX) {
    R(5) = ld16(base, (R(3) + 4));
    R(4) = R(5) & 0x1u;
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8180F574; }
    R(4) = R(5) & 0x2u;
    CR0(ctx, R(4));
    R(4) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_8180F584; }
    R(4) = R(5) & 0xFFF8u;
    R(5) = (0 + 4);
    R(5) = (rotl32(R(4), 0) & 0xFFFFFFFBu) | (R(5) & ~0xFFFFFFFBu);
    st16(base, (R(3) + 4), R(5));
    goto L_8180F580;
L_8180F574:;
    R(4) = ld32(base, (R(3) + 8));
    R(4) = (R(4) + 1);
    st32(base, (R(3) + 8), R(4));
L_8180F580:;
    R(4) = (0 + 1);
L_8180F584:;
    R(3) = R(4) |R(4);
}

/* mfn_8180F58C (mfn_8180F58C, 140 bytes) */
static void mj_mfn_8180F58C_0f58c(GM_CTX) {
    R(5) = ld16(base, (R(3) + 4));
    R(4) = R(5) & 0x1u;
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8180F5D4; }
    R(4) = R(5) & 0x4u;
    CR0(ctx, R(4));
    if ((CR_BIT(ctx, 2))) { goto L_8180F5B0; }
    R(4) = R(5) & 0xFFDAu;
    CR0(ctx, R(4));
    st16(base, (R(3) + 4), R(4));
    R(4) = (0 + 0);
    st32(base, (R(3) + 20), R(4));
L_8180F5B0:;
    R(4) = ld8(base, (R(3) + 6));
    cr_cmp_u(ctx, 0, R(4), 0xCu);
    if ((CR_BIT(ctx, 2))) { goto L_8180F608; }
    cr_cmp_u(ctx, 0, R(4), 0xDu);
    R(4) = (0 + 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F610; }
    R(5) = (0 + 11);
    st8(base, (R(3) + 6), R(5));
    goto L_8180F610;
L_8180F5D4:;
    R(4) = ld32(base, (R(3) + 8));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8180F600; }
    R(4) = (R(4) + -1);
    st32(base, (R(3) + 8), R(4));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    R(4) = (0 + 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8180F610; }
    R(5) = R(5) & 0xFFFEu;
    st16(base, (R(3) + 4), R(5));
    goto L_8180F610;
L_8180F600:;
    R(4) = (0 + 0);
    goto L_8180F610;
L_8180F608:;
    R(4) = (0 + 1);
    st8(base, (R(3) + 6), R(4));
L_8180F610:;
    R(3) = R(4) |R(4);
}

/* mfn_818119AC (mfn_818119AC, 100 bytes) */
static void mj_mfn_818119AC_119ac(GM_CTX) {
    GM_FN(0x818119AC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x80360000u);
    R(30) = (R(3) + -9024);
    R(3) = R(30) |R(30);
    GM_CALLV(0x818119D0u, 0x800CE580u, 0);
    R(29) = (0 + 3);
    R(30) = (R(30) + 8992);
L_818119D8:;
    R(3) = (R(30) + -7296);
    GM_CALLV(0x818119E0u, 0x800CDED0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x818119E8u, 0x800CDED0u, 0);
    R(29) = (R(29) + -1);
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(30) = (R(30) + 2432);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_818119D8; }
    R(0) = lr;
}

/* mfn_81812100 (mfn_81812100, 88 bytes) */
static void mj_mfn_81812100_12100(GM_CTX) {
    GM_FN(0x81812100); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(5) |R(5);
    R(5) = R(4) |R(4);
    R(4) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -5004);
    GM_CALLV(0x81812128u, 0x801D89F0u, 0);
    R(4) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_81812140; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181213Cu, 0x800CFB30u, 0);
    R(4) = (0 + -1);
L_81812140:;
    R(3) = R(4) |R(4);
    R(0) = lr;
}

/* mod_fn_800D0270 (mod_fn_800D0270, 296 bytes) */
static void mj_mod_fn_800D0270_12310(GM_CTX) {
    GM_FN(0x81812310); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(4) = ld8(base, (R(4) + -24035));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81812410; }
    R(30) = R(3) |R(3);
    R(3) = ld8(base, (R(3) + 24));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81812410; }
    R(3) = ld8(base, (R(30) + 25));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81812410; }
    R(3) = ld8(base, (R(30) + 26));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81812410; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25440));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((CR_BIT(ctx, 0))) { goto L_81812380; }
    R(3) = ld16(base, (R(30) + 28));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81812380; }
    R(3) = (R(3) + -1);
    st16(base, (R(30) + 28), R(3));
    goto L_81812410;
L_81812380:;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24512));
    R(4) = (0 + -1);
    GM_CALLV(0x81812390u, 0x81813BA4u, 0);
    R(3) = ld8(base, (R(3) + 2408));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81812408; }
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -6488);
    R(4) = ld32(base, (R(3) + 12));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81812408; }
    R(6) = (0 + 0x80430000u);
    R(6) = ld32(base, (R(6) + -24120));
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(5) = ld8(base, (R(30) + 8));
    R(4) = (R(4) + -4);
    R(7) = ld8(base, (R(6) + 4622));
    R(4) = rotl32(R(4), 30) & 0x3FFFFFFFu;
    R(9) = ld8(base, (R(6) + 4621));
    R(8) = (R(4) + 1);
    R(3) = ld32(base, (R(3) + 8));
    R(4) = rotl32(R(5), 6) & 0x3FC0u;
    R(6) = ld8(base, (R(6) + 4620));
    R(4) = (rotl32(R(7), 14) & 0xC000u) | (R(4) & ~0xC000u);
    R(4) = (rotl32(R(9), 16) & 0x1FF0000u) | (R(4) & ~0x1FF0000u);
    R(5) = (R(3) + -4);
    R(4) = (rotl32(R(6), 25) & 0xFE000000u) | (R(4) & ~0xFE000000u);
    ctx->ctr = R(8);
L_818123F4:;
    { uint32_t ea_ = R(5) + 4; R(6) = ld32(base, ea_); R(5) = ea_; }
    R(6) = R(6) & 0xFFFFFFCFu;
    cr_cmp_u(ctx, 0, R(6), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81812424; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818123F4; }
L_81812408:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81812410u, 0x800D0100u, 0);
L_81812410:;
    R(0) = lr;
    return;
L_81812424:;
    R(3) = R(5) - R(3);
    { int32_t v_ = (int32_t)R(3); ctx->xer_ca = v_ < 0 && (v_ & 0x3u) != 0; R(4) = (v_ >> 2); }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81812434u, 0x81812158u, 0);
    GM_LOOP(); goto L_81812410;
}

/* mod_fn_800D2390 (mod_fn_800D2390, 36 bytes) */
static void mj_mod_fn_800D2390_12438(GM_CTX) {
    R(4) = (0 + 0);
    st32(base, (R(3) + 12), R(4));
    st32(base, (R(3) + 8), R(4));
    st32(base, (R(3) + 16), R(4));
    st8(base, (R(3) + 33), R(4));
    R(4) = (0 + 0x0u);
    R(4) = R(4) | 0xFFFFu;
    st16(base, (R(3) + 30), R(4));
}

/* mod_fn_800D2610 (mod_fn_800D2610, 132 bytes) */
static void mj_mod_fn_800D2610_1245c(GM_CTX) {
    GM_FN(0x8181245C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(9) = (R(9) + 1);
    R(30) = R(3) |R(3);
    st32(base, (R(3) + 4), R(4));
    st8(base, (R(3) + 34), R(10));
    st32(base, (R(3) + 40), R(6));
    R(3) = ld32(base, (R(3) + 52));
    R(11) = ld32(base, (f + 24));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    st8(base, (R(30) + 32), R(9));
    st8(base, (R(30) + 35), R(11));
    st32(base, (R(30) + 44), R(7));
    st32(base, (R(30) + 48), R(8));
    if ((CR_BIT(ctx, 2))) { goto L_818124B8; }
    R(4) = (0 + 16);
    R(3) = (R(3) + -1);
    ctx->ctr = R(4);
    R(4) = (0 + 0);
L_818124B0:;
    { uint32_t ea_ = R(3) + 1; st8(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818124B0; }
L_818124B8:;
    R(3) = R(30) |R(30);
    st8(base, (R(30) + 60), R(5));
    GM_CALLV(0x818124C4u, 0x800D2510u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x818124CCu, 0x800D2690u, 0);
    R(0) = lr;
}

/* mfn_81812734 (mfn_81812734, 8 bytes) */
static void mj_mfn_81812734_12734(GM_CTX) {
    R(3) = ld32(base, (R(3) + 52));
}

/* mfn_8181273C (mfn_8181273C, 436 bytes) */
static void mj_mfn_8181273C_1273c(GM_CTX) {
    GM_FN(0x8181273C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 8908);
    st32(base, (R(30) + 0), R(3));
    R(3) = (0 + 152);
    R(29) = R(4) |R(4);
    GM_CALLV(0x81812780u, 0x818432E4u, 0);
    R(4) = (0 + 12);
    R(28) = R(3) |R(3);
    GM_CALLV(0x8181278Cu, 0x800DC570u, 0);
    R(3) = (0 + 0);
    st32(base, (R(30) + 84), R(28));
    R(5) = (0 + 4);
    st32(base, (R(30) + 88), R(3));
    R(4) = (R(30) + 32);
    ctx->ctr = R(5);
    R(5) = (0 + -1);
    R(6) = R(29) |R(29);
L_818127AC:;
    { uint32_t ea_ = R(6) + 4; R(7) = ld32(base, ea_); R(6) = ea_; }
    { uint32_t ea_ = R(4) + 4; st32(base, ea_, R(7)); R(4) = ea_; }
    st8(base, (R(7) + 86), R(3));
    R(3) = (R(3) + 1);
    st32(base, (R(7) + 4), R(5));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818127AC; }
    R(3) = (0 + 1216);
    R(4) = (0 + 4);
    R(28) = (0 + 4);
    GM_CALLV(0x818127D4u, 0x818434ACu, 0);
    R(27) = R(3) |R(3);
    R(26) = (R(30) + 48);
    R(25) = (0 + 8);
L_818127E0:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x818127ECu, 0x800DC570u, 0);
    R(25) = (R(25) + -1);
    { uint32_t ea_ = R(26) + 4; st32(base, ea_, R(27)); R(26) = ea_; }
    R(28) = (R(28) + 1);
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    R(27) = (R(27) + 152);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_818127E0; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181280Cu, 0x802B9280u, 0);
    R(3) = (0 + 0x80370000u);
    R(27) = (R(30) + 4);
    R(26) = (R(30) + 32);
    R(29) = (0 + 0);
    R(28) = (R(3) + 6256);
    R(25) = (0 + 0);
L_81812824:;
    { uint32_t ea_ = R(26) + 4; R(3) = ld32(base, ea_); R(26) = ea_; }
    R(3) = ld32(base, (R(3) + 144));
    R(4) = ld32(base, (R(3) + 0));
    R(4) = ld32(base, (R(4) + 16));
    ctx->ctr = R(4);
    R(4) = R(28) |R(28);
    GM_CALLV(0x81812840u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81812890; }
    R(3) = ld32(base, (R(26) + 0));
    R(4) = ld32(base, (R(3) + 12));
    st32(base, (R(3) + 4), R(29));
    R(5) = R(4) & 0xFFFFFFFCu;
    cr_cmp_u(ctx, 0, R(5), 0x8u);
    R(5) = rotl32(R(29), 2) & 0xFFFFFFFCu;
    st32(base, (R(27) + R(5)), R(3));
    R(5) = R(4) |R(4);
    if ((CR_BIT(ctx, 2))) { goto L_81812870; }
    R(5) = (R(4) + 8);
L_81812870:;
    R(3) = ld32(base, (R(3) + 16));
    cr_cmp_u(ctx, 0, R(3), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_81812880; }
    R(4) = R(5) |R(5);
L_81812880:;
    R(3) = R(29) |R(29);
    R(24) = (R(29) + 1);
    GM_CALLV(0x8181288Cu, 0x8183C114u, 0);
    R(29) = R(24) |R(24);
L_81812890:;
    cr_cmp_u(ctx, 0, R(25), 0x2u);
    if ((CR_BIT(ctx, 1))) { goto L_818128A4; }
    cr_cmp_u(ctx, 0, R(29), 0x4u);
    R(25) = (R(25) + 1);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81812824; }
L_818128A4:;
    R(3) = ld32(base, (R(30) + 84));
    R(4) = rotl32(R(29), 2) & 0xFFFFFFFCu;
    { uint32_t a_ = R(29); R(5) = 0x8u - a_; ctx->xer_ca = 0x8u >= a_; }
    R(4) = R(30) + R(4);
    ctx->ctr = R(5);
L_818128B8:;
    { uint32_t ea_ = R(4) + 4; st32(base, ea_, R(3)); R(4) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818128B8; }
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_800DC570 (mod_fn_800DC570, 356 bytes) */
static void mj_mod_fn_800DC570_128f0(GM_CTX) {
    GM_FN(0x818128F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81850000u);
    R(29) = R(4) |R(4);
    R(4) = (0 + 0x81850000u);
    R(3) = (R(3) + 8920);
    st32(base, (R(30) + 0), R(3));
    R(4) = (R(4) + 8896);
    R(3) = R(30) |R(30);
    { uint32_t ea_ = R(3) + 8; st32(base, ea_, R(4)); R(3) = ea_; }
    R(4) = R(29) & 0xFFFFFFFCu;
    R(28) = (0 + -1);
    cr_cmp_u(ctx, 0, R(4), 0x4u);
    R(4) = (0 + 3);
    st32(base, (R(30) + 4), R(28));
    st32(base, (R(30) + 12), R(29));
    st32(base, (R(30) + 16), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81812960; }
    R(4) = (0 + 0x80370000u);
    R(6) = (R(4) + 6320);
    goto L_81812968;
L_81812960:;
    R(4) = (0 + 0x81850000u);
    R(6) = (R(4) + 8132);
L_81812968:;
    R(7) = (0 + 0x81850000u);
    st32(base, (R(30) + 36), R(3));
    R(3) = (R(7) + 9036);
    R(8) = (0 + 0x81850000u);
    R(9) = (0 + 0x81850000u);
    st32(base, (R(30) + 20), R(3));
    R(3) = (0 + 0x81850000u);
    R(4) = R(30) |R(30);
    R(5) = R(30) |R(30);
    R(7) = (R(9) + 9084);
    R(26) = (R(8) + 8880);
    R(3) = (R(3) + 9104);
    { uint32_t ea_ = R(5) + 28; st32(base, ea_, R(7)); R(5) = ea_; }
    R(27) = (0 + 0);
    { uint32_t ea_ = R(4) + 24; st32(base, ea_, R(26)); R(4) = ea_; }
    st32(base, (R(30) + 32), R(3));
    R(3) = (R(30) + 44);
    st32(base, (R(30) + 40), R(27));
    GM_CALLV(0x818129B4u, 0x8015FC90u, 0);
    R(3) = (0 + 256);
    R(6) = (0 + 0x81850000u);
    st16(base, (R(30) + 84), R(3));
    R(3) = (0 + 0x81850000u);
    R(6) = (R(6) + 9128);
    R(5) = R(30) |R(30);
    st32(base, (R(30) + 92), R(6));
    R(6) = (0 + 0x81850000u);
    R(3) = (R(3) + 9176);
    R(4) = R(30) |R(30);
    { uint32_t ea_ = R(5) + 100; st32(base, ea_, R(3)); R(5) = ea_; }
    R(3) = (R(6) + 9196);
    R(6) = (0 + 0x80370000u);
    { uint32_t ea_ = R(4) + 96; st32(base, ea_, R(26)); R(4) = ea_; }
    R(6) = (R(6) + 6192);
    st32(base, (R(30) + 104), R(3));
    R(3) = (R(30) + 116);
    st32(base, (R(30) + 80), R(28));
    st8(base, (R(30) + 86), R(29));
    st32(base, (R(30) + 112), R(27));
    st32(base, (R(30) + 108), R(30));
    GM_CALLV(0x81812A0Cu, 0x8015FC90u, 0);
    cr_cmp_u(ctx, 0, R(29), 0xCu);
    if ((CR_BIT(ctx, 2))) { goto L_81812A2C; }
    R(4) = (0 + 0x81860000u);
    R(3) = rotl32(R(29), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + -1204);
    R(3) = ld32(base, (R(4) + R(3)));
    R(4) = (0 + 8);
    GM_CALLV(0x81812A2Cu, 0x802BC920u, 0);
L_81812A2C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_execute__13dRemoconMng_cFv (mod_execute__13dRemoconMng_cFv, 244 bytes) */
static void mj_mod_execute__13dRemoconMng_cFv_12ba4(GM_CTX) {
    GM_FN(0x81812BA4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = (0 + 0x80430000u);
    R(29) = (0 + 36);
    R(30) = (0 + 12);
L_81812BD4:;
    R(3) = ld32(base, (R(28) + -24536));
    R(3) = ld32(base, (R(3) + R(29)));
    GM_CALLV(0x81812BE0u, 0x800DC970u, 0);
    R(30) = (R(30) + -1);
    cr_cmp_u(ctx, 0, R(30), 0x0u);
    R(29) = (R(29) + 4);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81812BD4; }
    R(29) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(29) + -24536));
    R(4) = (0 + 0x80370000u);
    R(28) = (0 + 4);
    R(27) = (0 + 0);
    R(25) = (0 + 1);
    R(26) = (0 + 36);
    R(30) = (R(4) + 6256);
L_81812C10:;
    R(4) = ld32(base, (R(3) + R(26)));
    R(5) = ld8(base, (R(4) + 84));
    cr_cmp_u(ctx, 0, R(5), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81812C44; }
    R(3) = ld32(base, (R(4) + 144));
    R(4) = ld32(base, (R(3) + 0));
    R(4) = ld32(base, (R(4) + 16));
    ctx->ctr = R(4);
    R(4) = R(30) |R(30);
    GM_CALLV(0x81812C38u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81812C68; }
    R(3) = ld32(base, (R(29) + -24536));
L_81812C44:;
    cr_cmp_u(ctx, 0, R(27), 0x3u);
    R(25) = (0 + 1);
    if ((CR_BIT(ctx, 0))) { goto L_81812C54; }
    R(25) = (0 + 0);
L_81812C54:;
    R(28) = (R(28) + -1);
    R(27) = (R(27) + 1);
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    R(26) = (R(26) + 4);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81812C10; }
L_81812C68:;
    R(3) = R(25) & 0x1u;
    GM_CALLV(0x81812C70u, 0x801DFBD0u, 0);
    R(0) = lr;
}

/* mfn_81812E2C (mfn_81812E2C, 152 bytes) */
static void mj_mfn_81812E2C_12e2c(GM_CTX) {
    GM_FN(0x81812E2C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_81812EAC; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24536));
    R(29) = ld32(base, (R(3) + 88));
    cr_cmp_u(ctx, 0, R(29), 0x7u);
    if ((CR_BIT(ctx, 1))) { goto L_81812EAC; }
    R(4) = ld32(base, (R(3) + 84));
    R(5) = rotl32(R(29), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(5);
    { uint32_t a_ = R(29); R(5) = 0x8u - a_; ctx->xer_ca = 0x8u >= a_; }
    ctx->ctr = R(5);
L_81812E78:;
    R(5) = ld32(base, (R(3) + 4));
    cr_cmp_u(ctx, 0, R(5), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81812E94; }
    R(29) = (R(29) + 1);
    R(3) = (R(3) + 4);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81812E78; }
    goto L_81812EAC;
L_81812E94:;
    R(4) = ld8(base, (R(30) + 86));
    st32(base, (R(3) + 4), R(30));
    R(3) = R(29) |R(29);
    R(4) = (int8_t)R(4);
    GM_CALLV(0x81812EA8u, 0x8183C114u, 0);
    st32(base, (R(30) + 4), R(29));
L_81812EAC:;
    R(0) = lr;
}

/* mod_fn_800DC6F0 (mod_fn_800DC6F0, 392 bytes) */
static void mj_mod_fn_800DC6F0_12fc8(GM_CTX) {
    GM_FN(0x81812FC8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + 86));
    R(5) = (R(5) + -1204);
    R(30) = R(3) |R(3);
    R(3) = (int8_t)R(4);
    R(29) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(5) = ld32(base, (R(5) + R(29)));
    R(7) = (0 + 0x81860000u);
    R(7) = (R(7) + -6288);
    R(6) = ld32(base, (R(5) + 0));
    cr_cmp_u(ctx, 0, R(6), R(7));
    if ((!CR_BIT(ctx, 2))) { goto L_8181301C; }
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81813130; }
L_8181301C:;
    R(6) = ld32(base, (R(5) + 0));
    R(7) = (0 + 0x80350000u);
    R(7) = (R(7) + 48);
    cr_cmp_u(ctx, 0, R(6), R(7));
    if ((CR_BIT(ctx, 2))) { goto L_8181307C; }
    R(6) = ld32(base, (R(5) + 0));
    R(7) = (0 + 0x81860000u);
    R(7) = (R(7) + -6288);
    cr_cmp_u(ctx, 0, R(6), R(7));
    if ((CR_BIT(ctx, 2))) { goto L_81813084; }
L_81813044:;
    R(3) = ld32(base, (R(5) + 0));
    R(4) = (0 + 0x81860000u);
    R(4) = (R(4) + -6344);
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81813130; }
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81813130; }
    R(3) = ld8(base, (R(5) + 48));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81813130; }
    R(3) = ld8(base, (R(30) + 84));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81813108; }
    goto L_81813130;
L_8181307C:;
    R(6) = R(5) |R(5);
    goto L_81813090;
L_81813084:;
    R(6) = ld32(base, (R(5) + 44));
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81813044; }
L_81813090:;
    R(5) = ld8(base, (R(6) + 2844));
    R(5) = R(5) & 0x1u;
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81813130; }
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    if ((CR_BIT(ctx, 1))) { goto L_818130FC; }
    R(4) = (0 + 0x80430000u);
    R(28) = ld32(base, (R(4) + -23456));
    R(27) = ld8(base, (R(6) + 116));
    R(4) = ld32(base, (R(28) + 3624));
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(3));
    R(3) = (R(28) + 3620);
    if ((CR_BIT(ctx, 1))) { goto L_818130D0; }
    R(4) = ld32(base, (R(28) + 3620));
    R(4) = ld32(base, (R(4) + 24));
    ctx->ctr = R(4);
    GM_CALLV(0x818130D0u, ctx->ctr, 0);
L_818130D0:;
    R(3) = ld32(base, (R(28) + 3628));
    R(3) = ld32(base, (R(3) + R(29)));
    cr_cmp_u(ctx, 0, R(3), R(27));
    if ((!CR_BIT(ctx, 2))) { goto L_81813130; }
    R(3) = ld8(base, (R(30) + 84));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81813108; }
    R(3) = ld8(base, (R(30) + 86));
    R(3) = (int8_t)R(3);
    GM_CALLV(0x818130F8u, 0x801E0E40u, 0);
    goto L_81813130;
L_818130FC:;
    R(3) = ld8(base, (R(30) + 84));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81813130; }
L_81813108:;
    R(3) = ld32(base, (R(30) + 88));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81813128; }
    R(4) = (0 + 0x80370000u);
    R(3) = (R(30) + 116);
    R(4) = (R(4) + 6256);
    GM_CALLV(0x81813124u, 0x8015FC10u, 0);
    goto L_81813130;
L_81813128:;
    R(3) = (0 + 1);
    st32(base, (R(30) + 88), R(3));
L_81813130:;
    R(0) = lr;
}

/* mod_fn_800DC820 (mod_fn_800DC820, 204 bytes) */
static void mj_mod_fn_800DC820_13150(GM_CTX) {
    GM_FN(0x81813150); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0);
    R(30) = R(3) |R(3);
    R(3) = ld8(base, (R(3) + 86));
    cr_cmp_u(ctx, 0, R(3), 0xCu);
    if ((CR_BIT(ctx, 1))) { goto L_81813184; }
    R(4) = (0 + 0x81850000u);
    R(3) = rotl32(R(3), 3) & 0xFFFFFFF8u;
    R(4) = (R(4) + 8932);
    R(6) = ld32(base, (R(4) + R(3)));
L_81813184:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -20737);
    R(3) = (R(4) + 18);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 246);
    GM_CALLV(0x8181319Cu, 0x8015F730u, 0);
    R(3) = ld8(base, (R(30) + 86));
    R(3) = (int8_t)R(3);
    GM_CALLV(0x818131A8u, 0x8016F460u, 0);
    R(4) = R(3) |R(3);
    R(3) = ld8(base, (R(30) + 86));
    st32(base, (R(30) + 80), R(4));
    cr_cmp_u(ctx, 0, R(3), 0x3u);
    if ((CR_BIT(ctx, 1))) { goto L_81813200; }
    R(4) = (0 + 0);
    GM_CALLV(0x818131C4u, 0x802D6A60u, 0);
    R(3) = (0 + 0x80420000u);
    R(3) = ld8(base, (R(3) + 32624));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81813200; }
    R(3) = ld8(base, (R(30) + 86));
    R(4) = (0 + 0x81860000u);
    R(4) = (R(4) + -1204);
    R(5) = (0 + 0);
    R(3) = (int8_t)R(3);
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(4) + R(3)));
    R(4) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(4) + -30800); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 10);
    GM_CALLV(0x81813200u, 0x802BC9A0u, 0);
L_81813200:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81813208u, 0x81812E2Cu, 0);
    R(0) = lr;
}

/* mod_fn_800DC8E0 (mod_fn_800DC8E0, 292 bytes) */
static void mj_mod_fn_800DC8E0_132c4(GM_CTX) {
    GM_FN(0x818132C4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + 86));
    R(5) = (R(5) + -1204);
    R(30) = R(3) |R(3);
    R(3) = (int8_t)R(4);
    R(6) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(5) = ld32(base, (R(5) + R(6)));
    R(7) = (0 + 0x81860000u);
    R(7) = (R(7) + -6288);
    R(6) = ld32(base, (R(5) + 0));
    cr_cmp_u(ctx, 0, R(6), R(7));
    if ((!CR_BIT(ctx, 2))) { goto L_81813338; }
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81813338; }
    R(3) = ld32(base, (R(30) + 16));
    R(3) = (R(3) + -3);
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((!CR_BIT(ctx, 0))) { goto L_818133C4; }
L_8181331C:;
    R(3) = (R(30) + 8);
    GM_CALLV(0x81813324u, 0x800DCF00u, 0);
    R(3) = ld8(base, (R(30) + 86));
    R(3) = (int8_t)R(3);
    GM_CALLV(0x81813330u, 0x8016F460u, 0);
    st32(base, (R(30) + 80), R(3));
    goto L_818133D4;
L_81813338:;
    R(6) = ld32(base, (R(5) + 0));
    R(7) = (0 + 0x80350000u);
    R(7) = (R(7) + 48);
    cr_cmp_u(ctx, 0, R(6), R(7));
    if ((CR_BIT(ctx, 2))) { goto L_8181338C; }
    R(6) = ld32(base, (R(5) + 0));
    R(7) = (0 + 0x81860000u);
    R(7) = (R(7) + -6288);
    cr_cmp_u(ctx, 0, R(6), R(7));
    if ((CR_BIT(ctx, 2))) { goto L_81813394; }
L_81813360:;
    R(3) = ld32(base, (R(5) + 0));
    R(4) = (0 + 0x81860000u);
    R(4) = (R(4) + -6344);
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181331C; }
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181331C; }
    R(3) = ld8(base, (R(5) + 48));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181331C; }
    goto L_818133C4;
L_8181338C:;
    R(6) = R(5) |R(5);
    goto L_818133A0;
L_81813394:;
    R(6) = ld32(base, (R(5) + 44));
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81813360; }
L_818133A0:;
    R(5) = ld8(base, (R(6) + 2844));
    R(5) = R(5) & 0x1u;
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_818133C4; }
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8181331C; }
    R(4) = ld8(base, (R(30) + 84));
    R(4) = R(4) & 0x1u;
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181331C; }
    GM_CALLV(0x818133C4u, 0x801E0E40u, 0);
L_818133C4:;
    R(4) = (0 + 0x80370000u);
    R(3) = (R(30) + 116);
    R(4) = (R(4) + 6192);
    GM_CALLV(0x818133D4u, 0x8015FC10u, 0);
L_818133D4:;
    R(0) = lr;
}

/* mfn_818133E8 (mfn_818133E8, 356 bytes) */
static void mj_mfn_818133E8_133e8(GM_CTX) {
    GM_FN(0x818133E8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(30) + 4));
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -1204);
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(29) = ld32(base, (R(3) + R(4)));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 48);
    R(3) = ld32(base, (R(29) + 0));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81813450; }
    R(3) = ld32(base, (R(29) + 0));
    R(4) = (0 + 0x81860000u);
    R(4) = (R(4) + -6288);
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8181352C; }
    R(29) = ld32(base, (R(29) + 44));
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181352C; }
L_81813450:;
    R(3) = (0 + 0x80430000u);
    R(28) = ld32(base, (R(29) + 4));
    R(27) = ld32(base, (R(3) + -23456));
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    R(3) = (R(27) + 3620);
    if ((CR_BIT(ctx, 0))) { goto L_81813474; }
    R(4) = ld32(base, (R(27) + 3624));
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(28));
    if ((CR_BIT(ctx, 1))) { goto L_81813484; }
L_81813474:;
    R(4) = ld32(base, (R(27) + 3620));
    R(4) = ld32(base, (R(4) + 24));
    ctx->ctr = R(4);
    GM_CALLV(0x81813484u, ctx->ctr, 0);
L_81813484:;
    R(3) = ld32(base, (R(27) + 3628));
    R(4) = rotl32(R(28), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(3) + R(4)));
    R(3) = ld8(base, (R(29) + 116));
    cr_cmp_u(ctx, 0, R(4), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_8181352C; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 250);
    if ((CR_BIT(ctx, 1))) { goto L_818134D4; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818134F8; }
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_81813510; }
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181352C; }
    R(3) = ld32(base, (R(30) + 8));
    cr_cmp_u(ctx, 0, R(3), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_8181352C; }
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 8084);
    goto L_81813524;
L_818134D4:;
    R(3) = (R(3) + -251);
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((!CR_BIT(ctx, 0))) { goto L_8181352C; }
    R(3) = ld32(base, (R(30) + 8));
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_8181352C; }
    R(3) = (0 + 0x80370000u);
    R(4) = (R(3) + 6512);
    goto L_81813524;
L_818134F8:;
    R(3) = ld32(base, (R(30) + 8));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181352C; }
    R(3) = (0 + 0x80370000u);
    R(4) = (R(3) + 6384);
    goto L_81813524;
L_81813510:;
    R(3) = ld32(base, (R(30) + 8));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8181352C; }
    R(3) = (0 + 0x80370000u);
    R(4) = (R(3) + 6448);
L_81813524:;
    R(3) = (R(30) + 36);
    GM_CALLV(0x8181352Cu, 0x8015FC10u, 0);
L_8181352C:;
    R(0) = lr;
}

/* mod_fn_800DCA00 (mod_fn_800DCA00, 12 bytes) */
static void mj_mod_fn_800DCA00_1354c(GM_CTX) {
    R(4) = (0 + 3);
    st32(base, (R(3) + 8), R(4));
}

/* mod_fn_800DCA20 (mod_fn_800DCA20, 32 bytes) */
static void mj_mod_fn_800DCA20_13558(GM_CTX) {
    GM_FN(0x81813558); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x81813568u, 0x818133E8u, 0);
    R(0) = lr;
}

/* mod_fn_800DCB50 (mod_fn_800DCB50, 12 bytes) */
static void mj_mod_fn_800DCB50_13578(GM_CTX) {
    R(4) = (0 + 0);
    st32(base, (R(3) + 8), R(4));
}

/* mod_fn_800DCB70 (mod_fn_800DCB70, 32 bytes) */
static void mj_mod_fn_800DCB70_13584(GM_CTX) {
    GM_FN(0x81813584); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x81813594u, 0x818133E8u, 0);
    R(0) = lr;
}

/* mfn_81813960 (mfn_81813960, 36 bytes) */
static void mj_mfn_81813960_13960(GM_CTX) {
    GM_FN(0x81813960); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (R(3) + 24);
    GM_CALLV(0x81813974u, 0x8015FAE0u, 0);
    R(0) = lr;
}

/* mfn_81813A0C (mfn_81813A0C, 92 bytes) */
static void mj_mfn_81813A0C_13a0c(GM_CTX) {
    GM_FN(0x81813A0C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(4) + 0));
    R(30) = R(4) |R(4);
    R(3) = ld32(base, (R(3) + 12));
    ctx->ctr = R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x81813A3Cu, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81813A50; }
    R(3) = (R(29) + 4);
    st32(base, (R(29) + 12), R(30));
L_81813A50:;
    R(0) = lr;
}

/* mfn_81813AB4 (mfn_81813AB4, 80 bytes) */
static void mj_mfn_81813AB4_13ab4(GM_CTX) {
    GM_FN(0x81813AB4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld32(base, (R(3) + 8));
    R(3) = ld32(base, (R(3) + 4));
    R(5) = ld32(base, (R(4) + 16));
    R(6) = ld32(base, (R(4) + 12));
    R(4) = ld32(base, (R(4) + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(3) = R(3) + R(6);
    if ((CR_BIT(ctx, 0))) { goto L_81813AEC; }
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(5) = ld32(base, (R(3) + R(5)));
    R(4) = ld32(base, (R(5) + R(4)));
L_81813AEC:;
    ctx->ctr = R(4);
    GM_CALLV(0x81813AF4u, ctx->ctr, 0);
    R(0) = lr;
}

/* mfn_81813B04 (mfn_81813B04, 80 bytes) */
static void mj_mfn_81813B04_13b04(GM_CTX) {
    GM_FN(0x81813B04); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld32(base, (R(3) + 8));
    R(3) = ld32(base, (R(3) + 4));
    R(5) = ld32(base, (R(4) + 28));
    R(6) = ld32(base, (R(4) + 24));
    R(4) = ld32(base, (R(4) + 32));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(3) = R(3) + R(6);
    if ((CR_BIT(ctx, 0))) { goto L_81813B3C; }
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(5) = ld32(base, (R(3) + R(5)));
    R(4) = ld32(base, (R(5) + R(4)));
L_81813B3C:;
    ctx->ctr = R(4);
    GM_CALLV(0x81813B44u, ctx->ctr, 0);
    R(0) = lr;
}

/* mod_fn_800E3AB0 (mod_fn_800E3AB0, 48 bytes) */
static void mj_mod_fn_800E3AB0_145a4(GM_CTX) {
    GM_FN(0x818145A4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x818145BCu, 0x8008ED70u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* find_code_region (find_code_region, 184 bytes) */
static void mj_find_code_region_145d4(GM_CTX) {
    R(3) = (0 + 0x80000000u);
    R(3) = ld8(base, (R(3) + 16954));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 249);
    if ((!CR_BIT(ctx, 0))) { goto L_81814604; }
    cr_cmp_u(ctx, 0, R(3), 0x55u);
    if ((CR_BIT(ctx, 2))) { goto L_81814638; }
    cr_cmp_u(ctx, 0, R(3), 0xACu);
    if ((CR_BIT(ctx, 2))) { goto L_81814664; }
    cr_cmp_u(ctx, 0, R(3), 0xC8u);
    R(3) = (0 + 6);
    if ((!CR_BIT(ctx, 2))) { goto L_8181465C; }
    return;
L_81814604:;
    if ((CR_BIT(ctx, 2))) { goto L_81814640; }
    cr_cmp_u(ctx, 0, R(3), 0xFCu);
    if ((CR_BIT(ctx, 2))) { goto L_8181466C; }
    cr_cmp_u(ctx, 0, R(3), 0xFFu);
    if ((!CR_BIT(ctx, 2))) { goto L_8181465C; }
    R(3) = (0 + 0x800C0000u);
    R(3) = R(3) | 0xF117u;
    R(3) = ld8(base, (R(3) + 368));
    cr_cmp_u(ctx, 0, R(3), 0x30u);
    R(3) = (0 + 1);
    if ((!CR_BIT(ctx, 2))) return;
    R(3) = (0 + 0);
    return;
L_81814638:;
    R(3) = (0 + 8);
    return;
L_81814640:;
    R(3) = (0 + 0x800D0000u);
    R(3) = ld8(base, (R(3) + -3817));
    cr_cmp_u(ctx, 0, R(3), 0x30u);
    R(3) = (0 + 4);
    if ((CR_BIT(ctx, 2))) return;
    R(3) = (0 + 5);
    return;
L_8181465C:;
    R(3) = (0 + 9);
    return;
L_81814664:;
    R(3) = (0 + 7);
    return;
L_8181466C:;
    R(3) = (0 + 0x800C0000u);
    R(3) = R(3) | 0xF117u;
    R(3) = ld8(base, (R(3) + 128));
    cr_cmp_u(ctx, 0, R(3), 0x30u);
    R(3) = (0 + 2);
    if ((CR_BIT(ctx, 2))) return;
    R(3) = (0 + 3);
}

/* ctor_8181468C (ctor_8181468C, 40 bytes) */
static void mj_ctor_8181468C_1468c(GM_CTX) {
    GM_FN(0x8181468C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x8181469Cu, 0x818145D4u, 0);
    R(4) = (0 + 0x81860000u);
    st32(base, (R(4) + -4864), R(3));
    R(0) = lr;
}

/* mfn_818146B4 (mfn_818146B4, 48 bytes) */
static void mj_mfn_818146B4_146b4(GM_CTX) {
    R(5) = R(3) |R(3);
    R(6) = (0 + 192);
    R(3) = (R(3) + 4);
    R(5) = (R(5) + -8);
    ctx->ctr = R(6);
L_818146C8:;
    { uint32_t ea_ = R(5) + 84; R(6) = ld32(base, ea_); R(5) = ea_; }
    cr_cmp_u(ctx, 0, R(6), R(4));
    if ((CR_BIT(ctx, 2))) return;
    R(3) = (R(3) + 84);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818146C8; }
    R(3) = (0 + 0);
}

/* mfn_81814700 (mfn_81814700, 8 bytes) */
static void mj_mfn_81814700_14700(GM_CTX) {
    R(3) = (0 + 4);
}

/* mod_fn_800FE400 (mod_fn_800FE400, 352 bytes) */
static void mj_mod_fn_800FE400_14708(GM_CTX) {
    GM_FN(0x81814708); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(30) = (0 + 0x80320000u);
    R(30) = (R(30) + -15848);
    R(4) = ld32(base, (R(13) + -22088));
    R(5) = (R(30) + 64);
    R(3) = (R(4) + 4);
    R(4) = (R(13) + -27312);
    GM_CALLV(0x8181473Cu, 0x800DF180u, 0);
    st32(base, (R(31) + 524), R(3));
    R(5) = (R(30) + 64);
    R(4) = (R(13) + -27304);
    R(3) = ld32(base, (R(13) + -22088));
    R(3) = (R(3) + 4);
    GM_CALLV(0x81814754u, 0x800DF180u, 0);
    st32(base, (R(31) + 528), R(3));
    R(5) = (R(30) + 64);
    R(4) = (R(13) + -27296);
    R(3) = ld32(base, (R(13) + -22088));
    R(3) = (R(3) + 4);
    GM_CALLV(0x8181476Cu, 0x800DF180u, 0);
    st32(base, (R(31) + 532), R(3));
    R(3) = (R(30) + 48);
    R(0) = ld32(base, (R(31) + 588));
    R(5) = (R(30) + 64);
    R(6) = ld32(base, (R(13) + -22088));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 9220);
    R(4) = ld32(base, (R(3) + R(0)));
    R(3) = (R(6) + 4);
    GM_CALLV(0x81814798u, 0x800DF180u, 0);
    st32(base, (R(31) + 592), R(3));
    R(3) = (R(31) + 524);
    R(4) = (R(30) + 80);
    GM_CALLV(0x818147A8u, 0x80239E30u, 0);
    st32(base, (f + 36), R(3));
    R(30) = (0 + 0);
    goto L_81814840;
L_818147B4:;
    R(4) = R(30) |R(30);
    R(3) = (f + 36);
    GM_CALLV(0x818147C0u, 0x8023B860u, 0);
    st32(base, (f + 32), R(3));
    R(0) = ld32(base, (R(3) + 48));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818147D8; }
    R(4) = R(3) + R(0);
    goto L_818147DC;
L_818147D8:;
    R(4) = (0 + 0);
L_818147DC:;
    R(6) = (R(3) + 324);
    R(0) = (R(3) + 64);
    st32(base, (f + 28), R(4));
    R(3) = (f + 28);
    R(4) = (f + 24);
    R(5) = (f + 20);
    st32(base, (f + 20), R(6));
    st32(base, (f + 24), R(0));
    GM_CALLV(0x81814800u, 0x8023E650u, 0);
    R(7) = ld32(base, (f + 32));
    R(3) = (f + 28);
    R(4) = (f + 16);
    R(5) = (f + 12);
    R(6) = (R(7) + 324);
    R(0) = (R(7) + 64);
    st32(base, (f + 8), R(6));
    R(6) = (f + 8);
    st32(base, (f + 12), R(0));
    R(0) = ld32(base, (R(31) + 592));
    st32(base, (f + 16), R(0));
    GM_CALLV(0x81814830u, 0x8023E390u, 0);
    R(3) = (f + 32);
    R(4) = (0 + 0);
    GM_CALLV(0x8181483Cu, 0x8023CAE0u, 0);
    R(30) = (R(30) + 1);
L_81814840:;
    R(3) = (f + 36);
    GM_CALLV(0x81814848u, 0x8023B8C0u, 0);
    cr_cmp_u(ctx, 0, R(30), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818147B4; }
    R(0) = lr;
}

/* mfn_81814868 (mfn_81814868, 156 bytes) */
static void mj_mfn_81814868_14868(GM_CTX) {
    GM_FN(0x81814868); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x81814888u, 0x801021B0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_818148E4; }
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -508);
    R(3) = ld8(base, (R(3) + 7));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_818148E4; }
    R(3) = (0 + 0x81850000u);
    R(28) = (R(3) + 9252);
    R(29) = (0 + 8);
    R(27) = (R(28) + -4);
    R(30) = (0 + 0);
L_818148B8:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x818148C0u, 0x800B2EE0u, 0);
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = R(27) + 4; R(4) = ld32(base, ea_); R(27) = ea_; }
    R(29) = (R(29) + -1);
    R(5) = ld32(base, (R(28) + R(3)));
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(30) = (R(30) + 1);
    st32(base, (R(27) + 0), R(5));
    st32(base, (R(28) + R(3)), R(4));
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_818148B8; }
L_818148E4:;
    R(0) = lr;
}

/* mod_fn_2_1C1880 (mod_fn_2_1C1880, 56 bytes) */
static void mj_mod_fn_2_1C1880_14904(GM_CTX) {
    GM_FN(0x81814904); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 1456);
    GM_CALLV(0x8181491Cu, 0x801628C0u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x81814924u, 0x8092F060u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_dProf_getName__FUs (mod_dProf_getName__FUs, 52 bytes) */
static void mj_mod_dProf_getName__FUs_14eac(GM_CTX) {
    cr_cmp_u(ctx, 0, R(3), 0x2F1u);
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    if ((CR_BIT(ctx, 1))) { goto L_81814EC8; }
    R(4) = (0 + 0x80320000u);
    R(4) = (R(4) + 2112);
    R(3) = R(4) + R(3);
    goto L_81814ED8;
L_81814EC8:;
    R(4) = (0 + 0x81850000u);
    R(4) = (R(4) + 9284);
    R(3) = R(4) + R(3);
    R(3) = (R(3) + -3016);
L_81814ED8:;
    R(3) = ld32(base, (R(3) + 0));
}

/* ctor_8181505C (ctor_8181505C, 144 bytes) */
static void mj_ctor_8181505C_1505c(GM_CTX) {
    R(3) = (0 + 757);
    R(4) = (0 + 0x81860000u);
    ctx->ctr = R(3);
    R(3) = (R(4) + -4860);
    R(3) = (R(3) + -4);
    R(4) = (0 + 0);
L_81815074:;
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81815074; }
    R(3) = (0 + 754);
    R(4) = (0 + 0x81860000u);
    ctx->ctr = R(3);
    R(3) = (0 + 0x80770000u);
    R(4) = (R(4) + -4860);
    R(5) = (R(3) + -22648);
    R(3) = (R(4) + -4);
    R(4) = (R(5) + -4);
L_8181509C:;
    { uint32_t ea_ = R(4) + 4; R(5) = ld32(base, ea_); R(4) = ea_; }
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(5)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181509C; }
    R(3) = (0 + 0x81860000u);
    R(4) = (0 + 0x81850000u);
    R(3) = (R(3) + -4860);
    R(4) = (R(4) + 9360);
    R(3) = (R(3) + 3012);
    R(4) = (R(4) + -4);
    R(5) = (0 + 0);
L_818150C4:;
    { uint32_t ea_ = R(4) + 4; R(6) = ld32(base, ea_); R(4) = ea_; }
    R(5) = (R(5) + 1);
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(6)); R(3) = ea_; }
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818150C4; }
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -4860);
    R(4) = (0 + 0x80430000u);
    st32(base, (R(4) + -23624), R(3));
}

/* mod_fn_2_510 (mod_fn_2_510, 592 bytes) */
static void mj_mod_fn_2_510_1723c(GM_CTX) {
    GM_FN(0x8181723C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(30) = R(3) |R(3);
    R(5) = ld32(base, (R(3) + 588));
    R(0) = ld32(base, (R(3) + 584));
    R(28) = ld32(base, (R(4) + -24536));
    cr_cmp_s(ctx, 0, (int32_t)R(0), (int32_t)R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_818172E8; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8181746C; }
    R(0) = ld32(base, (R(3) + 572));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = R(28) + R(0);
    R(3) = ld32(base, (R(3) + 4));
    { uint32_t ea_ = R(3) + 92; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x8181729Cu, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 6256);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x818172B4u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8181746C; }
    R(0) = ld8(base, (R(30) + 570));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8181746C; }
    R(3) = (R(30) + 112);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x818172D8u, 0x800C93D0u, 0);
    R(0) = (0 + 0);
    st8(base, (R(30) + 570), R(0));
    st32(base, (R(30) + 572), R(0));
    goto L_8181746C;
L_818172E8:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 3);
    if ((CR_BIT(ctx, 2))) { goto L_8181746C; }
    GM_CALLV(0x818172F4u, 0x800CDC60u, 0);
    R(0) = ld32(base, (R(30) + 588));
    R(31) = R(3) |R(3);
    R(29) = (0 + 0x80930000u);
    st32(base, (R(30) + 584), R(0));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(30) + 548));
    R(29) = (R(29) + 15524);
    R(4) = R(31) |R(31);
    R(6) = ld32(base, (R(29) + R(0)));
    R(5) = (0 + 2);
    R(7) = (0 + 0);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x81817328u, 0x800C9A60u, 0);
    R(0) = ld32(base, (R(30) + 584));
    R(4) = R(31) |R(31);
    R(3) = ld32(base, (R(30) + 552));
    R(5) = (0 + 2);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(7) = (0 + 0);
    R(6) = ld32(base, (R(29) + R(0)));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x8181734Cu, 0x800C9A60u, 0);
    R(3) = (R(30) + 112);
    GM_CALLV(0x81817354u, 0x800C9500u, 0);
    R(0) = ld32(base, (R(30) + 584));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8181738C; }
    R(3) = (R(30) + 112);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x81817370u, 0x800C93D0u, 0);
    R(3) = (R(30) + 112);
    R(4) = (0 + 2);
    GM_CALLV(0x8181737Cu, 0x800C9380u, 0);
    R(0) = (0 + 0);
    st8(base, (R(30) + 570), R(0));
    R(28) = (0 + 13);
    goto L_81817434;
L_8181738C:;
    R(3) = (R(30) + 112);
    R(4) = (0 + 1);
    R(5) = (0 + 0);
    GM_CALLV(0x8181739Cu, 0x800C93D0u, 0);
    R(0) = ld32(base, (R(30) + 584));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_818173E8; }
    R(3) = ld32(base, (R(30) + 572));
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = R(28) + R(0);
    R(3) = ld32(base, (R(3) + 4));
    { uint32_t ea_ = R(3) + 92; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x818173C8u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 6256);
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x818173E0u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81817418; }
L_818173E8:;
    R(3) = (R(30) + 112);
    R(4) = (0 + 0);
    GM_CALLV(0x818173F4u, 0x800C9380u, 0);
    R(29) = ld32(base, (R(30) + 500));
    { uint32_t ea_ = (R(30) + 564); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(29) + 0));
    GM_CALLV(0x81817404u, 0x801637D0u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181740Cu, 0x801644D0u, 0);
    R(0) = (0 + 1);
    st8(base, (R(30) + 570), R(0));
    goto L_81817430;
L_81817418:;
    R(3) = (R(30) + 112);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x81817428u, 0x800C93D0u, 0);
    R(0) = (0 + 0);
    st8(base, (R(30) + 570), R(0));
L_81817430:;
    R(28) = (0 + 10);
L_81817434:;
    R(3) = ld32(base, (R(30) + 556));
    R(4) = R(31) |R(31);
    R(6) = R(28) |R(28);
    R(5) = (0 + 2);
    R(7) = (0 + 0);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x81817450u, 0x800C9A60u, 0);
    R(3) = ld32(base, (R(30) + 560));
    R(4) = R(31) |R(31);
    R(6) = R(28) |R(28);
    R(5) = (0 + 2);
    R(7) = (0 + 0);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x8181746Cu, 0x800C9A60u, 0);
L_8181746C:;
    R(0) = lr;
}

/* mod_fn_2_2370 (mod_fn_2_2370, 328 bytes) */
static void mj_mod_fn_2_2370_176cc(GM_CTX) {
    GM_FN(0x818176CC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 728));
    R(4) = ld32(base, (R(4) + -24536));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_81817758; }
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = R(4) + R(3);
    R(3) = ld32(base, (R(3) + 4));
    R(3) = ld32(base, (R(3) + 144));
    R(4) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(4) + 16));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 6256);
    ctx->ctr = R(5);
    GM_CALLV(0x81817728u, ctx->ctr, 0);
    R(29) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81817750; }
    R(3) = ld32(base, (R(30) + 728));
    R(5) = (0 + 0);
    R(4) = ld32(base, (R(30) + 640));
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    st32(base, (R(4) + R(3)), R(5));
    R(3) = R(30) |R(30);
    GM_CALLV(0x81817750u, 0x81817618u, 0);
L_81817750:;
    R(3) = R(29) ^ 0x1u;
    goto L_818177F4;
L_81817758:;
    R(3) = (0 + 0x80370000u);
    R(27) = (R(4) + 4);
    R(28) = (0 + 0);
    R(29) = (R(3) + 6256);
L_81817768:;
    R(3) = rotl32(R(28), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(27) + R(3)));
    R(3) = ld32(base, (R(3) + 144));
    R(4) = ld32(base, (R(3) + 0));
    R(4) = ld32(base, (R(4) + 16));
    ctx->ctr = R(4);
    R(4) = R(29) |R(29);
    GM_CALLV(0x81817788u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818177D4; }
    R(3) = ld32(base, (R(30) + 756));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818177D4; }
    R(4) = ld32(base, (R(30) + 644));
    ctx->ctr = R(3);
    R(4) = (R(4) + -4);
L_818177A8:;
    { uint32_t ea_ = R(4) + 4; R(5) = ld32(base, ea_); R(4) = ea_; }
    cr_cmp_u(ctx, 0, R(5), R(28));
    if ((CR_BIT(ctx, 2))) { goto L_818177D4; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818177A8; }
    R(4) = ld32(base, (R(30) + 644));
    ctx->ctr = R(3);
    R(3) = (R(4) + -4);
L_818177C4:;
    { uint32_t ea_ = R(3) + 4; R(4) = ld32(base, ea_); R(3) = ea_; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 0))) { goto L_818177E8; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818177C4; }
L_818177D4:;
    R(28) = (R(28) + 1);
    cr_cmp_u(ctx, 0, R(28), 0x8u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81817768; }
    R(3) = (0 + 0);
    goto L_818177F4;
L_818177E8:;
    st32(base, (R(3) + 0), R(28));
    R(3) = (0 + 1);
    st32(base, (R(30) + 728), R(28));
L_818177F4:;
    R(0) = lr;
}

/* mfn_81817814 (mfn_81817814, 36 bytes) */
static void mj_mfn_81817814_17814(GM_CTX) {
    cr_cmp_u(ctx, 0, R(3), 0x10u);
    R(4) = (0 + 0);
    if ((CR_BIT(ctx, 1))) { goto L_81817830; }
    R(4) = (0 + 0x81850000u);
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + -15780);
    R(4) = ld32(base, (R(4) + R(3)));
L_81817830:;
    R(3) = R(4) |R(4);
}

/* mfn_81817838 (mfn_81817838, 40 bytes) */
static void mj_mfn_81817838_17838(GM_CTX) {
    cr_cmp_u(ctx, 0, R(3), 0x11u);
    R(4) = (0 + 1);
    if ((CR_BIT(ctx, 0))) { goto L_81817848; }
    R(4) = (0 + 0);
L_81817848:;
    R(5) = (0 + 0x10000u);
    R(3) = R(3) & 0x1FFFFu;
    R(5) = R(5) | 0x5538u;
    { uint32_t s_ = R(3) & 63; R(3) = s_ > 31 ? 0 : R(5) >> s_; }
    R(3) = R(4) &R(3);
}

/* mod_fn_2_2920 (mod_fn_2_2920, 492 bytes) */
static void mj_mod_fn_2_2920_17af0(GM_CTX) {
    GM_FN(0x81817AF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(30) + 124));
    R(3) = (0 + 0x80430000u);
    R(3) = ld16(base, (R(3) + -30926));
    R(5) = ld32(base, (R(4) + 524));
    cr_cmp_u(ctx, 0, R(3), 0x3u);
    R(6) = ld8(base, (R(5) + 187));
    R(6) = R(6) & 0xFEu;
    st8(base, (R(5) + 187), R(6));
    R(5) = ld32(base, (R(4) + 528));
    R(6) = ld8(base, (R(5) + 187));
    R(6) = R(6) & 0xFEu;
    st8(base, (R(5) + 187), R(6));
    R(5) = ld32(base, (R(4) + 532));
    R(6) = ld8(base, (R(5) + 187));
    R(6) = R(6) & 0xFEu;
    st8(base, (R(5) + 187), R(6));
    R(4) = ld32(base, (R(4) + 536));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = R(5) & 0xFEu;
    st8(base, (R(4) + 187), R(5));
    R(4) = ld32(base, (R(30) + 632));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = R(5) & 0xFEu;
    st8(base, (R(4) + 187), R(5));
    R(4) = ld32(base, (R(30) + 636));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = R(5) | 0x1u;
    st8(base, (R(4) + 187), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_81817C00; }
    R(3) = ld32(base, (R(30) + 728));
    R(4) = ld32(base, (R(30) + 640));
    R(5) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(4) + R(5)));
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_81817CC4; }
    R(29) = ld32(base, (R(30) + 124));
    R(4) = (0 + 3);
    st32(base, (R(29) + 572), R(3));
    st32(base, (R(29) + 584), R(4));
    GM_CALLV(0x81817BA8u, 0x81817CDCu, 0);
    R(4) = ld32(base, (R(29) + 524));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = (rotl32(R(3), 29) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(4) + 187), R(5));
    R(4) = ld32(base, (R(29) + 528));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = (rotl32(R(3), 30) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(4) + 187), R(5));
    R(4) = ld32(base, (R(29) + 532));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = (rotl32(R(3), 31) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(4) + 187), R(5));
    R(4) = ld32(base, (R(29) + 536));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = (rotl32(R(3), 0) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(4) + 187), R(5));
    R(4) = (0 + 1);
    R(3) = ld32(base, (R(30) + 124));
    st32(base, (R(3) + 588), R(4));
    R(4) = ld32(base, (R(30) + 748));
    st32(base, (R(3) + 564), R(4));
    goto L_81817CC4;
L_81817C00:;
    R(3) = (0 + -1);
    st32(base, (R(30) + 728), R(3));
    R(3) = R(30) |R(30);
    GM_CALLV(0x81817C10u, 0x818176CCu, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81817CC4; }
    R(3) = ld32(base, (R(30) + 728));
    R(4) = (0 + 3);
    R(29) = ld32(base, (R(30) + 124));
    st32(base, (R(29) + 572), R(3));
    st32(base, (R(29) + 584), R(4));
    GM_CALLV(0x81817C30u, 0x81817CDCu, 0);
    R(4) = ld32(base, (R(29) + 524));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = (rotl32(R(3), 29) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(4) + 187), R(5));
    R(4) = ld32(base, (R(29) + 528));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = (rotl32(R(3), 30) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(4) + 187), R(5));
    R(4) = ld32(base, (R(29) + 532));
    R(5) = ld8(base, (R(4) + 187));
    R(5) = (rotl32(R(3), 31) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(4) + 187), R(5));
    R(4) = ld32(base, (R(29) + 536));
    R(29) = (0 + 1);
    R(5) = ld8(base, (R(4) + 187));
    R(5) = (rotl32(R(3), 0) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(4) + 187), R(5));
    R(4) = (0 + 0);
    R(3) = ld32(base, (R(30) + 124));
    st32(base, (R(3) + 588), R(4));
    R(4) = ld32(base, (R(30) + 748));
    st32(base, (R(3) + 564), R(4));
    R(3) = ld32(base, (R(30) + 728));
    R(4) = ld32(base, (R(30) + 640));
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    st32(base, (R(4) + R(3)), R(29));
    R(3) = R(30) |R(30);
    GM_CALLV(0x81817CA0u, 0x81817A24u, 0);
    R(3) = ld32(base, (R(30) + 736));
    R(4) = ld32(base, (R(30) + 120));
    R(5) = ld32(base, (R(30) + 640));
    st32(base, (R(4) + 612), R(3));
    R(3) = ld32(base, (R(30) + 728));
    st8(base, (R(4) + 617), R(29));
    R(4) = (0 + 2);
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    st32(base, (R(5) + R(3)), R(4));
L_81817CC4:;
    R(0) = lr;
}

/* mfn_81817CDC (mfn_81817CDC, 152 bytes) */
static void mj_mfn_81817CDC_17cdc(GM_CTX) {
    R(4) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(3), 0x7u);
    R(3) = (0 + 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81817CF0; }
    return;
L_81817CF0:;
    R(5) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(5) + -24536));
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(4) = R(5) + R(4);
    R(5) = ld32(base, (R(4) + 4));
    R(4) = ld32(base, (R(5) + 12));
    R(6) = R(4) & 0xFFFFFFFCu;
    cr_cmp_u(ctx, 0, R(6), 0x8u);
    R(6) = ld32(base, (R(5) + 16));
    R(5) = R(4) |R(4);
    if ((CR_BIT(ctx, 2))) { goto L_81817D20; }
    R(5) = (R(4) + 8);
L_81817D20:;
    cr_cmp_u(ctx, 0, R(6), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_81817D2C; }
    R(4) = R(5) |R(5);
L_81817D2C:;
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    if ((CR_BIT(ctx, 1))) { goto L_81817D40; }
    R(3) = (0 + 8);
    { uint32_t s_ = R(4) & 63; R(3) = s_ > 31 ? 0 : R(3) >> s_; }
    return;
L_81817D40:;
    R(5) = R(4) & 0xFFFFFFFCu;
    cr_cmp_u(ctx, 0, R(5), 0x8u);
    if ((CR_BIT(ctx, 2))) { goto L_81817D64; }
    cr_cmp_u(ctx, 0, R(5), 0x4u);
    if ((!CR_BIT(ctx, 2))) return;
    R(3) = (0 + 128);
    { uint32_t s_ = R(4) & 63; R(3) = s_ > 31 ? 0 : R(3) >> s_; }
    R(3) = R(3) | 0x10u;
    return;
L_81817D64:;
    R(3) = (0 + 2048);
    { uint32_t s_ = R(4) & 63; R(3) = s_ > 31 ? 0 : R(3) >> s_; }
    R(3) = R(3) | 0x20u;
}

/* mod_fn_2_2B30 (mod_fn_2_2B30, 284 bytes) */
static void mj_mod_fn_2_2B30_17d74(GM_CTX) {
    GM_FN(0x81817D74); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld8(base, (R(3) + 665));
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81817E80; }
    R(4) = (0 + 0x80430000u);
    R(4) = ld16(base, (R(4) + -30926));
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    R(4) = ld32(base, (R(3) + 728));
    if ((!CR_BIT(ctx, 2))) { goto L_81817DF4; }
    R(5) = ld32(base, (R(3) + 640));
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(5) = ld32(base, (R(5) + R(4)));
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_81817E08; }
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -5828);
    R(4) = ld32(base, (R(5) + R(4)));
    R(5) = (0 + 0x81850000u);
    R(6) = (0 + 8);
    R(5) = (R(5) + -25628);
    ctx->ctr = R(6);
    R(6) = (R(5) + -4);
    R(5) = (0 + 0);
L_81817DD8:;
    { uint32_t ea_ = R(6) + 4; R(7) = ld32(base, ea_); R(6) = ea_; }
    cr_cmp_u(ctx, 0, R(7), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81817E14; }
    R(5) = (R(5) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81817DD8; }
    R(4) = (0 + -1);
    goto L_81817E18;
L_81817DF4:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), -1);
    if ((!CR_BIT(ctx, 1))) { goto L_81817E08; }
    R(4) = (0 + 0x80990000u);
    R(4) = (R(4) + 2944);
    goto L_81817E78;
L_81817E08:;
    R(4) = (0 + 0x80990000u);
    R(4) = (R(4) + 2624);
    goto L_81817E78;
L_81817E14:;
    { uint32_t a_ = R(5); R(4) = 0x4u - a_; ctx->xer_ca = 0x4u >= a_; }
L_81817E18:;
    R(5) = (0 + 0x81850000u);
    R(6) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(5) = (R(5) + -25628);
    R(5) = R(5) - R(6);
    R(5) = ld32(base, (R(5) + 16));
    R(6) = ld32(base, (R(3) + 128));
    st32(base, (R(3) + 736), R(4));
    R(4) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(6) + R(4)));
    R(6) = ld32(base, (R(3) + 680));
    st32(base, (R(3) + 724), R(5));
    st32(base, (R(4) + 560), R(6));
    R(5) = ld32(base, (R(3) + 676));
    st32(base, (R(4) + 556), R(5));
    R(5) = ld32(base, (R(3) + 684));
    st32(base, (R(4) + 564), R(5));
    R(5) = ld32(base, (R(3) + 676));
    st32(base, (R(4) + 172), R(5));
    R(5) = ld32(base, (R(3) + 680));
    st32(base, (R(4) + 176), R(5));
    R(5) = ld32(base, (R(3) + 684));
    st32(base, (R(4) + 180), R(5));
    R(4) = (0 + 0x80990000u);
    R(4) = (R(4) + 3392);
L_81817E78:;
    R(3) = (R(3) + 576);
    GM_CALLV(0x81817E80u, 0x8015FC10u, 0);
L_81817E80:;
    R(0) = lr;
}

/* mod_fn_2_3770 (mod_fn_2_3770, 248 bytes) */
static void mj_mod_fn_2_3770_18110(GM_CTX) {
    GM_FN(0x81818110); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80930000u);
    R(7) = (0 + 0x80930000u);
    R(0) = (0 + 0x43300000u);
    { uint32_t ea_ = (R(4) + 15704); ctx->f[2].u = ld64(base, ea_); }
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(7) + 15696); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(30) = (0 + 1);
    R(5) = ld32(base, (R(3) + 724));
    R(6) = (0 + 0x80930000u);
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    st32(base, (f + 32), R(0));
    R(12) = ld32(base, (R(3) + 128));
    { uint32_t ea_ = (R(3) + 684); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(8) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(3) + 680); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(10) = ld32(base, (R(12) + R(5)));
    R(5) = (0 + 0);
    R(4) = (0 + 4);
    { uint32_t ea_ = (R(3) + 676); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(10) + 556); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 21184); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(10) + 560); stfs(base, ea_, ctx->f[4].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (R(10) + 564); stfs(base, ea_, ctx->f[3].d); }
    R(6) = ld32(base, (R(8) + -23424));
    { uint32_t ea_ = (R(3) + 260); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(6) = ld32(base, (R(6) + 0));
    R(0) = ld32(base, (R(3) + 724));
    R(6) = ld16(base, (R(6) + 4));
    st32(base, (f + 36), R(6));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(6) = ld32(base, (R(3) + 128));
    { uint32_t ea_ = (R(3) + 264); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); ctx->f[1].u = ld64(base, ea_); }
    R(6) = ld32(base, (R(6) + R(0)));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[5].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[6].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(6) + 172); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 176); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 180); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 615), R(30));
    R(3) = (R(3) + 144);
    st8(base, (R(6) + 609), R(30));
    GM_CALLV(0x818181ECu, 0x800C92F0u, 0);
    st8(base, (R(31) + 662), R(30));
    R(0) = lr;
}

/* mod_fn_2_3920 (mod_fn_2_3920, 220 bytes) */
static void mj_mod_fn_2_3920_18208(GM_CTX) {
    GM_FN(0x81818208); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(30) + 724));
    R(3) = (0 + 0x81850000u);
    R(5) = ld32(base, (R(30) + 128));
    R(3) = (R(3) + -26672);
    R(6) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(4) = rotl32(R(4), 2) & 0x1Cu;
    R(29) = ld32(base, (R(5) + R(6)));
    R(3) = R(3) + R(4);
    R(28) = (0 + 1);
    R(5) = ld32(base, (R(29) + 568));
    R(4) = R(5) ^ 0x3u;
    R(4) = cntlzw(R(4));
    R(4) = rotl32(R(4), 28) & 0x2u;
    R(4) = ld16(base, (R(3) + R(4)));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23416));
    R(5) = (0 + 1);
    GM_CALLV(0x8181826Cu, 0x80195380u, 0);
    R(3) = ld8(base, (R(29) + 610));
    R(5) = ld32(base, (R(30) + 728));
    R(4) = ld32(base, (R(30) + 724));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -5828);
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    st32(base, (R(3) + R(5)), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_818182BC; }
    R(3) = ld8(base, (R(29) + 611));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_818182BC; }
    R(4) = (0 + 2);
    R(3) = (0 + 1);
    st32(base, (R(29) + 572), R(4));
    R(4) = (0 + 0x3F800000u);
    st8(base, (R(29) + 611), R(3));
    st32(base, (R(29) + 576), R(3));
    st32(base, (R(29) + 592), R(4));
    st8(base, (R(29) + 613), R(3));
L_818182BC:;
    R(3) = ld32(base, (R(30) + 752));
    st32(base, (R(29) + 604), R(3));
    st8(base, (R(30) + 662), R(28));
    R(0) = lr;
}

/* mod_fn_2_3AB0 (mod_fn_2_3AB0, 68 bytes) */
static void mj_mod_fn_2_3AB0_182e4(GM_CTX) {
    R(0) = ld32(base, (R(3) + 724));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(3) + 128));
    R(4) = ld32(base, (R(4) + R(0)));
    R(0) = ld8(base, (R(4) + 611));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) return;
    R(0) = ld8(base, (R(4) + 610));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81818310; }
    return;
L_81818310:;
    { uint32_t ea_ = R(3) + 552; R(12) = ld32(base, ea_); R(3) = ea_; }
    R(4) = (0 + 0x80990000u);
    R(4) = (R(4) + 3392);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* mod_fn_2_3B00 (mod_fn_2_3B00, 52 bytes) */
static void mj_mod_fn_2_3B00_18328(GM_CTX) {
    R(4) = ld32(base, (R(3) + 724));
    R(5) = (0 + 0);
    R(0) = (0 + 1);
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(6) = ld32(base, (R(3) + 128));
    R(4) = ld32(base, (R(6) + R(4)));
    st8(base, (R(4) + 615), R(5));
    { uint32_t ea_ = (R(3) + 748); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = ld32(base, (R(3) + 124));
    st32(base, (R(4) + 588), R(0));
    { uint32_t ea_ = (R(4) + 564); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + 662), R(5));
}

/* mod_fn_2_3B40 (mod_fn_2_3B40, 72 bytes) */
static void mj_mod_fn_2_3B40_1835c(GM_CTX) {
    R(5) = ld32(base, (R(3) + 724));
    R(4) = (0 + 0x80430000u);
    R(6) = ld32(base, (R(3) + 128));
    R(7) = ld16(base, (R(4) + -30926));
    R(4) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(6) + R(4)));
    R(5) = ld32(base, (R(3) + 728));
    cr_cmp_u(ctx, 0, R(7), 0x3u);
    st32(base, (R(4) + 584), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_81818398; }
    R(5) = ld32(base, (R(3) + 732));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81818398; }
    R(5) = (0 + 1);
    st8(base, (R(4) + 618), R(5));
L_81818398:;
    R(4) = (0 + 1);
    st8(base, (R(3) + 666), R(4));
}

/* mod_fn_2_3C60 (mod_fn_2_3C60, 32 bytes) */
static void mj_mod_fn_2_3C60_1848c(GM_CTX) {
    R(5) = ld32(base, (R(3) + 724));
    R(4) = (0 + 0);
    R(6) = ld32(base, (R(3) + 128));
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    st8(base, (R(3) + 666), R(4));
    R(5) = ld32(base, (R(6) + R(5)));
    st8(base, (R(5) + 618), R(4));
}

/* mod_fn_2_52E0 (mod_fn_2_52E0, 56 bytes) */
static void mj_mod_fn_2_52E0_185d8(GM_CTX) {
    GM_FN(0x818185D8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 704);
    GM_CALLV(0x818185F0u, 0x801628C0u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x818185F8u, 0x80772AC0u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_56C0 (mod_fn_2_56C0, 396 bytes) */
static void mj_mod_fn_2_56C0_18610(GM_CTX) {
    GM_FN(0x81818610); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(26) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(26) + -300));
    st32(base, (f + 48), R(4));
    R(27) = ld32(base, (R(3) + 244));
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81818758; }
    R(30) = R(3) |R(3);
    R(29) = (R(3) + 112);
    R(3) = (0 + 0x81850000u);
    R(25) = (R(3) + -15708);
    R(4) = (R(25) + 202);
    R(3) = R(29) |R(29);
    R(5) = (0 + 0);
    GM_CALLV(0x8181866Cu, 0x800C8A10u, 0);
    R(3) = (R(25) + 241);
    st32(base, (f + 16), R(3));
    R(4) = (f + 16);
    R(3) = R(29) |R(29);
    R(5) = (0 + 1);
    GM_CALLV(0x81818684u, 0x800C8FB0u, 0);
    R(3) = (R(25) + 36);
    st32(base, (f + 16), R(3));
    R(3) = (0 + 0x81850000u);
    R(4) = (f + 16);
    R(5) = (R(3) + -15712);
    R(3) = R(29) |R(29);
    R(6) = (0 + 1);
    GM_CALLV(0x818186A4u, 0x800C90F0u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x818186ACu, 0x80007220u, 0);
    R(4) = (R(25) + 136);
    st32(base, (R(30) + 584), R(3));
    R(3) = (R(25) + 152);
    st32(base, (f + 16), R(4));
    R(5) = (R(30) + 588);
    st32(base, (f + 20), R(3));
    R(4) = (f + 16);
    R(3) = R(29) |R(29);
    R(6) = (0 + 2);
    GM_CALLV(0x818186D4u, 0x800C8D60u, 0);
    R(3) = (0 + 0x81850000u);
    R(28) = (f + 16);
    R(4) = (R(3) + 9544);
    R(3) = R(28) |R(28);
    R(5) = (0 + 32);
    GM_CALLV(0x818186ECu, 0x81844C38u, 0);
    R(5) = (R(30) + 596);
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(6) = (0 + 8);
    GM_CALLV(0x81818700u, 0x800C8E40u, 0);
    R(3) = (R(25) + 90);
    st32(base, (f + 16), R(3));
    R(3) = (R(25) + 101);
    st32(base, (f + 20), R(3));
    R(3) = (R(25) + 112);
    st32(base, (f + 24), R(3));
    R(3) = (R(25) + 124);
    st32(base, (f + 28), R(3));
    R(5) = (R(30) + 628);
    R(4) = (f + 16);
    R(3) = R(29) |R(29);
    R(6) = (0 + 4);
    GM_CALLV(0x81818734u, 0x800C8EB0u, 0);
    R(3) = (R(25) + 18);
    st32(base, (f + 16), R(3));
    R(3) = (R(25) + 27);
    st32(base, (f + 20), R(3));
    R(5) = (R(30) + 696);
    R(4) = (f + 16);
    R(3) = R(29) |R(29);
    R(6) = (0 + 2);
    GM_CALLV(0x81818758u, 0x800C8E40u, 0);
L_81818758:;
    R(3) = ld32(base, (R(26) + -300));
    R(4) = ld32(base, (f + 48));
    cr_cmp_u(ctx, 0, R(3), R(4));
    { uint32_t a_ = R(27); R(3) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(3) < a_; }
    { uint64_t t_ = (uint64_t)(~R(3)) + (R(27)) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
    if ((!CR_BIT(ctx, 2))) { goto L_81818798; }
    R(0) = lr;
    return;
L_81818798:;
    GM_CALLV(0x8181879Cu, 0x81844FCCu, 0);
}

/* mod_fn_2_60D0 (mod_fn_2_60D0, 60 bytes) */
static void mj_mod_fn_2_60D0_189f4(GM_CTX) {
    R(4) = (0 + 0x81850000u);
    { uint32_t ea_ = R(4) + 7564; R(5) = ld32(base, ea_); R(4) = ea_; }
    R(6) = (0 + 6);
    st32(base, (R(3) + 652), R(6));
    st32(base, (R(3) + 660), R(6));
    R(6) = ld32(base, (R(4) + 4));
    st32(base, (R(3) + 676), R(5));
    R(5) = ld32(base, (R(4) + 8));
    R(4) = ld32(base, (R(4) + 12));
    st32(base, (R(3) + 680), R(6));
    st32(base, (R(3) + 688), R(4));
    R(4) = (0 + 0);
    st32(base, (R(3) + 684), R(5));
    st16(base, (R(3) + 670), R(4));
}

/* mod_fn_2_9E70 (mod_fn_2_9E70, 56 bytes) */
static void mj_mod_fn_2_9E70_18a30(GM_CTX) {
    GM_FN(0x81818A30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 980);
    GM_CALLV(0x81818A48u, 0x801628C0u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x81818A50u, 0x80777650u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_D2A0 (mod_fn_2_D2A0, 244 bytes) */
static void mj_mod_fn_2_D2A0_1960c(GM_CTX) {
    GM_FN(0x8181960C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld8(base, (R(3) + 624));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 1);
    if ((!CR_BIT(ctx, 2))) { goto L_818196E8; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181963Cu, 0x8077ABB0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_818196E8; }
    GM_CALLV(0x8181964Cu, 0x800B54B0u, 0);
    R(4) = ld32(base, (R(30) + 600));
    R(3) = R(3) ^ 0x1u;
    R(5) = cntlzw(R(3));
    R(6) = ld8(base, (R(4) + 187));
    R(6) = R(6) & 0xFEu;
    R(6) = (rotl32(R(5), 27) & 0x1u) | (R(6) & ~0x1u);
    st8(base, (R(4) + 187), R(6));
    { uint32_t a_ = R(3); R(6) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(6) < a_; }
    R(4) = ld32(base, (R(30) + 604));
    { uint64_t t_ = (uint64_t)(~R(6)) + (R(3)) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
    R(5) = ld8(base, (R(4) + 187));
    R(5) = R(5) & 0xFEu;
    R(5) = (rotl32(R(3), 0) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(4) + 187), R(5));
    GM_CALLV(0x81819688u, 0x800CDC60u, 0);
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(30) + 608));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = R(29) |R(29);
    R(5) = (0 + 2);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x818196A8u, 0x800C9A60u, 0);
    R(3) = ld32(base, (R(30) + 612));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = R(29) |R(29);
    R(5) = (0 + 2);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x818196C4u, 0x800C9A60u, 0);
    R(3) = ld32(base, (R(30) + 580));
    R(4) = ld8(base, (R(3) + 187));
    R(4) = R(4) & 0xFEu;
    st8(base, (R(3) + 187), R(4));
    R(3) = (0 + 3);
    st8(base, (R(30) + 124), R(3));
    R(3) = (0 + 0x1000000u);
    st32(base, (R(30) + 624), R(3));
    R(3) = (0 + 1);
L_818196E8:;
    R(0) = lr;
}

/* mod_fn_2_31EC0 (mod_fn_2_31EC0, 56 bytes) */
static void mj_mod_fn_2_31EC0_1bafc(GM_CTX) {
    GM_FN(0x8181BAFC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 2228);
    GM_CALLV(0x8181BB14u, 0x801628C0u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8181BB1Cu, 0x8181BB34u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_31EF0 (mod_fn_2_31EF0, 304 bytes) */
static void mj_mod_fn_2_31EF0_1bb34(GM_CTX) {
    GM_FN(0x8181BB34); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x8181BB50u, 0x81808310u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 11036);
    st32(base, (R(30) + 96), R(3));
    R(3) = (R(30) + 180);
    GM_CALLV(0x8181BB64u, 0x80006AA0u, 0);
    R(3) = (R(30) + 392);
    GM_CALLV(0x8181BB6Cu, 0x80006AA0u, 0);
    R(3) = (R(30) + 604);
    GM_CALLV(0x8181BB74u, 0x80006AA0u, 0);
    R(3) = (R(30) + 816);
    GM_CALLV(0x8181BB7Cu, 0x80006AA0u, 0);
    R(3) = (R(30) + 1028);
    GM_CALLV(0x8181BB84u, 0x800C8950u, 0);
    R(3) = (0 + 0x81850000u);
    R(6) = (0 + 0x81850000u);
    R(3) = (R(3) + 11260);
    R(4) = R(30) |R(30);
    R(7) = (0 + 0x81850000u);
    st32(base, (R(30) + 1436), R(3));
    R(3) = (R(6) + 8880);
    R(5) = R(30) |R(30);
    { uint32_t ea_ = R(4) + 1440; st32(base, ea_, R(3)); R(4) = ea_; }
    R(3) = (0 + 0x81850000u);
    R(6) = (R(7) + 11308);
    { uint32_t ea_ = R(5) + 1444; st32(base, ea_, R(6)); R(5) = ea_; }
    R(3) = (R(3) + 11328);
    R(6) = (0 + 0x80990000u);
    R(29) = (0 + 0);
    st32(base, (R(30) + 1448), R(3));
    R(3) = (R(30) + 1460);
    R(6) = (R(6) + 17648);
    st32(base, (R(30) + 1452), R(30));
    st32(base, (R(30) + 1456), R(29));
    GM_CALLV(0x8181BBD8u, 0x8015FC90u, 0);
    R(4) = (0 + 8);
    R(3) = R(30) |R(30);
    { uint32_t ea_ = R(3) + 1808; st32(base, ea_, R(4)); R(3) = ea_; }
    st8(base, (R(3) + -148), R(29));
    st16(base, (R(3) + -143), R(29));
    st8(base, (R(3) + -141), R(29));
    st8(base, (R(3) + -139), R(29));
    ctx->ctr = R(4);
L_8181BBF8:;
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(29)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BBF8; }
    R(4) = (0 + 8);
    R(3) = (R(30) + 1840);
    ctx->ctr = R(4);
    R(4) = (0 + 0);
L_8181BC10:;
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BC10; }
    R(4) = (0 + 8);
    R(3) = (R(30) + 1872);
    ctx->ctr = R(4);
    R(4) = (0 + 0);
L_8181BC28:;
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BC28; }
    R(4) = (0 + 8);
    R(3) = (R(30) + 1904);
    ctx->ctr = R(4);
    R(4) = (0 + 0);
L_8181BC40:;
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BC40; }
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_32160 (mod_fn_2_32160, 104 bytes) */
static void mj_mod_fn_2_32160_1bc64(GM_CTX) {
    GM_FN(0x8181BC64); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8181BC88u, 0x818083A4u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 11036);
    st32(base, (R(30) + 96), R(3));
    R(3) = (R(30) + 1028);
    R(4) = (0 + -1);
    GM_CALLV(0x8181BCA0u, 0x800C89A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8181BCB0; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181BCB0u, 0x80162920u, 0);
L_8181BCB0:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_32220 (mod_fn_2_32220, 820 bytes) */
static void mj_mod_fn_2_32220_1bccc(GM_CTX) {
    GM_FN(0x8181BCCC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld8(base, (R(3) + 1660));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 1);
    if ((CR_BIT(ctx, 2))) { goto L_8181BD0C; }
L_8181BCF4:;
    R(0) = lr;
    return;
L_8181BD0C:;
    R(4) = R(30) |R(30);
    { uint32_t ea_ = R(4) + 1808; R(3) = ld32(base, ea_); R(4) = ea_; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181BD58; }
    ctx->ctr = R(3);
L_8181BD20:;
    { uint32_t ea_ = R(4) + 4; R(3) = ld32(base, ea_); R(4) = ea_; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181BCF4; }
    R(5) = ld32(base, (R(4) + 32));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181BCF4; }
    R(5) = ld32(base, (R(4) + 64));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181BCF4; }
    R(5) = ld32(base, (R(4) + 96));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181BCF4; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BD20; }
L_8181BD58:;
    R(3) = ld8(base, (R(30) + 1669));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181BDA8; }
    R(3) = (0 + 0x81850000u);
    R(29) = (R(30) + 816);
    R(3) = (R(3) + -9798);
    R(4) = (R(3) + 926);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181BD7Cu, 0x80006BE0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181BCF4; }
    R(4) = ld32(base, (R(30) + 1808));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181BDA8; }
    R(3) = (R(30) + 1904);
    ctx->ctr = R(4);
L_8181BD9C:;
    { uint32_t ea_ = R(3) + 4; R(4) = ld32(base, ea_); R(3) = ea_; }
    st32(base, (R(4) + 244), R(29));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BD9C; }
L_8181BDA8:;
    R(3) = ld8(base, (R(30) + 1665));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181BDF8; }
    R(3) = (0 + 0x81850000u);
    R(29) = (R(30) + 180);
    R(3) = (R(3) + -9798);
    R(4) = (R(3) + 814);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181BDCCu, 0x80006BE0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181BCF4; }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = R(3) + 1808; R(4) = ld32(base, ea_); R(3) = ea_; }
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181BDF8; }
    ctx->ctr = R(4);
L_8181BDEC:;
    { uint32_t ea_ = R(3) + 4; R(4) = ld32(base, ea_); R(3) = ea_; }
    st32(base, (R(4) + 276), R(29));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BDEC; }
L_8181BDF8:;
    R(3) = ld8(base, (R(30) + 1666));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181BE48; }
    R(3) = (0 + 0x81850000u);
    R(29) = (R(30) + 392);
    R(3) = (R(3) + -9798);
    R(4) = (R(3) + 987);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181BE1Cu, 0x80006BE0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181BCF4; }
    R(4) = ld32(base, (R(30) + 1808));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181BE48; }
    R(3) = (R(30) + 1840);
    ctx->ctr = R(4);
L_8181BE3C:;
    { uint32_t ea_ = R(3) + 4; R(4) = ld32(base, ea_); R(3) = ea_; }
    st32(base, (R(4) + 244), R(29));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BE3C; }
L_8181BE48:;
    R(3) = ld8(base, (R(30) + 1667));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181BE98; }
    R(3) = (0 + 0x81850000u);
    R(29) = (R(30) + 604);
    R(3) = (R(3) + -9798);
    R(4) = (R(3) + 869);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181BE6Cu, 0x80006BE0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181BCF4; }
    R(4) = ld32(base, (R(30) + 1808));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181BE98; }
    R(3) = (R(30) + 1872);
    ctx->ctr = R(4);
L_8181BE8C:;
    { uint32_t ea_ = R(3) + 4; R(4) = ld32(base, ea_); R(3) = ea_; }
    st32(base, (R(4) + 244), R(29));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BE8C; }
L_8181BE98:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181BEA0u, 0x8181C000u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181BCF4; }
    GM_CALLV(0x8181BEB0u, 0x800CDC60u, 0);
    R(4) = ld32(base, (R(30) + 1808));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    R(4) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8181BEE0; }
    R(3) = (R(30) + 2080);
    R(5) = (0 + 0);
    R(6) = (0 + 10);
L_8181BECC:;
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(6)); R(3) = ea_; }
    R(5) = (R(5) + 1);
    R(7) = ld32(base, (R(30) + 1808));
    cr_cmp_u(ctx, 0, R(5), R(7));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8181BECC; }
L_8181BEE0:;
    R(5) = (0 + 8);
    R(3) = (R(30) + 2048);
    ctx->ctr = R(5);
    R(5) = (0 + 10);
L_8181BEF0:;
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(5)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BEF0; }
    R(3) = ld32(base, (R(30) + 1592));
    R(6) = (0 + 0x80430000u);
    R(6) = ld16(base, (R(6) + -30926));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = ld8(base, (R(3) + 187));
    cr_cmp_u(ctx, 0, R(6), 0x3u);
    R(5) = R(5) | 0x1u;
    st8(base, (R(3) + 187), R(5));
    R(3) = ld32(base, (R(30) + 1596));
    R(5) = ld8(base, (R(3) + 187));
    R(5) = R(5) | 0x1u;
    st8(base, (R(3) + 187), R(5));
    R(3) = ld32(base, (R(30) + 1600));
    R(5) = ld8(base, (R(3) + 187));
    R(5) = R(5) & 0xFEu;
    st8(base, (R(3) + 187), R(5));
    R(5) = (0 + 2);
    R(3) = ld32(base, (R(30) + 1552));
    if ((!CR_BIT(ctx, 2))) { goto L_8181BF90; }
    R(6) = (0 + 14);
    R(7) = (0 + 0);
    GM_CALLV(0x8181BF50u, 0x800C9A60u, 0);
    GM_CALLV(0x8181BF54u, 0x800B54B0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181BF9C; }
    R(3) = ld32(base, (R(30) + 1592));
    R(4) = ld8(base, (R(3) + 187));
    R(4) = R(4) & 0xFEu;
    st8(base, (R(3) + 187), R(4));
    R(3) = ld32(base, (R(30) + 1596));
    R(4) = ld8(base, (R(3) + 187));
    R(4) = R(4) & 0xFEu;
    st8(base, (R(3) + 187), R(4));
    R(3) = ld32(base, (R(30) + 1600));
    R(4) = ld8(base, (R(3) + 187));
    R(4) = R(4) | 0x1u;
    st8(base, (R(3) + 187), R(4));
    goto L_8181BF9C;
L_8181BF90:;
    R(6) = (0 + 29);
    R(7) = (0 + 0);
    GM_CALLV(0x8181BF9Cu, 0x800C9A60u, 0);
L_8181BF9C:;
    R(3) = ld32(base, (R(30) + 1496));
    R(4) = (0 + 0);
    st32(base, (R(30) + 1676), R(4));
    R(5) = ld8(base, (R(3) + 187));
    R(5) = R(5) & 0xFEu;
    st8(base, (R(3) + 187), R(5));
    R(3) = (0 + 1);
    R(5) = (0 + 8);
    st8(base, (R(30) + 1660), R(3));
    R(3) = (R(30) + 1968);
    st16(base, (R(30) + 1662), R(4));
    st8(base, (R(30) + 1664), R(4));
    R(4) = (0 + -2);
    st32(base, (R(30) + 1732), R(5));
    ctx->ctr = R(5);
L_8181BFD8:;
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BFD8; }
    R(4) = (0 + 8);
    R(3) = (R(30) + 2112);
    ctx->ctr = R(4);
    R(4) = (0 + -1);
L_8181BFF0:;
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181BFF0; }
    R(3) = (0 + 1);
    GM_LOOP(); goto L_8181BCF4;
}

/* mod_fn_2_32560 (mod_fn_2_32560, 632 bytes) */
static void mj_mod_fn_2_32560_1c000(GM_CTX) {
    GM_FN(0x8181C000); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0);
    R(25) = (0 + 0);
    R(27) = (0 + 0x81860000u);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(27) + -300));
    R(28) = (R(30) + 1028);
    st32(base, (f + 160), R(3));
    R(3) = (0 + 0x81850000u);
    R(26) = (R(3) + -9798);
    R(4) = (R(26) + 521);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8181C054u, 0x800C8CB0u, 0);
    R(29) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181C238; }
    R(4) = (R(26) + 427);
    R(3) = R(28) |R(28);
    R(5) = (0 + 0);
    GM_CALLV(0x8181C070u, 0x800C8A10u, 0);
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 11116);
    R(3) = R(28) |R(28);
    R(5) = (0 + 8);
    GM_CALLV(0x8181C084u, 0x800C8FB0u, 0);
    R(3) = (R(26) + 53);
    st32(base, (f + 88), R(3));
    R(4) = (R(26) + 16);
    st32(base, (f + 144), R(3));
    R(5) = (R(26) + 39);
    st32(base, (f + 152), R(3));
    R(3) = (0 + 1);
    st32(base, (f + 24), R(3));
    R(6) = (R(26) + 26);
    st32(base, (f + 28), R(3));
    st32(base, (f + 32), R(3));
    st32(base, (f + 36), R(3));
    R(3) = (0 + 2);
    st32(base, (f + 40), R(3));
    st32(base, (f + 44), R(3));
    R(3) = (0 + 3);
    st32(base, (f + 48), R(3));
    st32(base, (f + 52), R(3));
    R(3) = (0 + 4);
    st32(base, (f + 56), R(3));
    st32(base, (f + 60), R(3));
    R(3) = (0 + 5);
    st32(base, (f + 64), R(3));
    st32(base, (f + 68), R(3));
    R(3) = (0 + 6);
    st32(base, (f + 72), R(3));
    st32(base, (f + 76), R(3));
    R(3) = (0 + 7);
    st32(base, (f + 92), R(4));
    st32(base, (f + 96), R(5));
    st32(base, (f + 100), R(6));
    st32(base, (f + 104), R(4));
    st32(base, (f + 108), R(4));
    st32(base, (f + 112), R(5));
    st32(base, (f + 116), R(6));
    st32(base, (f + 120), R(5));
    st32(base, (f + 124), R(6));
    st32(base, (f + 128), R(5));
    st32(base, (f + 132), R(6));
    st32(base, (f + 136), R(5));
    R(5) = (f + 16);
    st32(base, (f + 140), R(6));
    R(6) = (0 + 18);
    st32(base, (f + 148), R(4));
    st32(base, (f + 156), R(4));
    R(4) = (f + 88);
    st32(base, (f + 80), R(3));
    st32(base, (f + 84), R(3));
    R(3) = R(28) |R(28);
    st32(base, (f + 16), R(25));
    st32(base, (f + 20), R(25));
    GM_CALLV(0x8181C154u, 0x800C90F0u, 0);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8181C15Cu, 0x80007220u, 0);
    st32(base, (R(30) + 1496), R(3));
    R(3) = (0 + 0x81850000u);
    R(5) = (R(30) + 1500);
    R(4) = (R(3) + 11148);
    R(3) = R(28) |R(28);
    R(6) = (0 + 10);
    R(25) = (0 + 10);
    GM_CALLV(0x8181C17Cu, 0x800C8D60u, 0);
    R(3) = (R(26) + 64);
    st32(base, (f + 88), R(3));
    R(3) = (R(26) + 140);
    st32(base, (f + 92), R(3));
    R(3) = (R(26) + 131);
    st32(base, (f + 96), R(3));
    R(3) = (R(26) + 123);
    st32(base, (f + 100), R(3));
    R(3) = (R(26) + 115);
    st32(base, (f + 104), R(3));
    R(3) = (R(26) + 98);
    st32(base, (f + 108), R(3));
    R(3) = (0 + 11);
    st32(base, (f + 16), R(3));
    R(3) = (0 + 25);
    st32(base, (f + 20), R(3));
    R(4) = (f + 88);
    st32(base, (f + 24), R(3));
    R(3) = (0 + 26);
    st32(base, (f + 28), R(3));
    R(5) = (f + 16);
    st32(base, (f + 32), R(3));
    R(3) = (0 + 27);
    st32(base, (f + 36), R(3));
    R(3) = R(28) |R(28);
    R(6) = (0 + 2);
    R(7) = (0 + 6);
    GM_CALLV(0x8181C1ECu, 0x800C8F20u, 0);
    R(3) = (0 + 0x81850000u);
    R(5) = (R(30) + 1540);
    R(4) = (R(3) + 11188);
    R(3) = R(28) |R(28);
    R(6) = (0 + 4);
    GM_CALLV(0x8181C204u, 0x800C8EB0u, 0);
    R(3) = (0 + 0x81850000u);
    R(5) = (R(30) + 1556);
    R(4) = (R(3) + 11204);
    R(3) = R(28) |R(28);
    R(6) = (0 + 12);
    GM_CALLV(0x8181C21Cu, 0x800C8E40u, 0);
    R(3) = (0 + 0x81850000u);
    R(5) = (R(30) + 1604);
    R(4) = (R(3) + 11252);
    R(3) = R(28) |R(28);
    R(6) = (0 + 2);
    GM_CALLV(0x8181C234u, 0x800C8DD0u, 0);
    st8(base, (R(30) + 1040), R(25));
L_8181C238:;
    R(3) = ld32(base, (R(27) + -300));
    R(4) = ld32(base, (f + 160));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8181C274; }
    R(3) = R(29) |R(29);
    R(0) = lr;
    return;
L_8181C274:;
    GM_CALLV(0x8181C278u, 0x81844FCCu, 0);
}

/* mod_fn_2_328F0 (mod_fn_2_328F0, 224 bytes) */
static void mj_mod_fn_2_328F0_1c278(GM_CTX) {
    GM_FN(0x8181C278); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 1808));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181C338; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31116); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(29) = (R(30) + 1904);
    R(28) = (0 + 0);
L_8181C2B4:;
    { uint32_t ea_ = R(29) + 4; R(3) = ld32(base, ea_); R(29) = ea_; }
    R(4) = (0 + 0);
    R(3) = (R(3) + 112);
    GM_CALLV(0x8181C2C4u, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181C2F8; }
    R(3) = ld32(base, (R(29) + 0));
    R(3) = ld32(base, (R(3) + 500));
    R(3) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 7, ctx->f[0].d, ctx->f[31].d);
    R(3) = ctx->cr;
    R(4) = ctx->cr;
    R(3) = R(3) & 0x1u;
    R(4) = rotl32(R(4), 29) & 0x1u;
    R(3) = R(4) |R(3);
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8181C310; }
L_8181C2F8:;
    R(3) = ld32(base, (R(30) + 1808));
    R(28) = (R(28) + 1);
    cr_cmp_u(ctx, 0, R(28), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8181C2B4; }
    ctx->f[0].u = ctx->f[31].u;
    goto L_8181C314;
L_8181C310:;
    R(3) = ld32(base, (R(30) + 1808));
L_8181C314:;
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181C338; }
    R(4) = (R(30) + 1808);
    ctx->ctr = R(3);
L_8181C324:;
    { uint32_t ea_ = R(4) + 4; R(3) = ld32(base, ea_); R(4) = ea_; }
    R(5) = ld32(base, (R(4) + 32));
    { uint32_t ea_ = (R(3) + 748); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 692); stfs(base, ea_, ctx->f[0].d); }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181C324; }
L_8181C338:;
    R(0) = lr;
}

/* mod_fn_2_32A00 (mod_fn_2_32A00, 440 bytes) */
static void mj_mod_fn_2_32A00_1c358(GM_CTX) {
    GM_FRAME(32); gptr f = gm_frame_sp;
    R(10) = ld32(base, (R(3) + 1808));
    st32(base, (f + 12), R(27));
    cr_cmp_u(ctx, 0, R(10), 0x0u);
    st32(base, (f + 16), R(28));
    st32(base, (f + 20), R(29));
    st32(base, (f + 24), R(30));
    if ((CR_BIT(ctx, 2))) { goto L_8181C4F8; }
    R(7) = (0 + 0x81850000u);
    R(8) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(7) + -30828); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(9) = (0 + -30704);
    { uint32_t ea_ = (R(8) + -30776); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(11) = (0 + 0x3F4C0000u);
    R(4) = (R(3) + 1500);
    R(5) = (R(3) + 2048);
    R(6) = (0 + 0);
    R(7) = (R(9) + 0x81850000u);
    R(8) = R(11) | 0xCCCDu;
    R(9) = (0 + 0);
L_8181C3A8:;
    { uint32_t ea_ = R(5) + 4; R(11) = ld32(base, ea_); R(5) = ea_; }
    cr_cmp_u(ctx, 0, R(11), 0xAu);
    if ((CR_BIT(ctx, 2))) { goto L_8181C4EC; }
    R(10) = rotl32(R(11), 2) & 0xFFFFFFFCu;
    R(10) = ld32(base, (R(4) + R(10)));
    R(11) = ld32(base, (R(3) + 1732));
    { uint32_t ea_ = (R(10) + 132); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(10) + 152); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(11), 5);
    if ((CR_BIT(ctx, 0))) { goto L_8181C404; }
    cr_cmp_u(ctx, 0, R(11), 0x7u);
    R(11) = (0 + 2);
    if ((CR_BIT(ctx, 0))) { goto L_8181C3E0; }
    R(11) = (0 + 3);
L_8181C3E0:;
    cr_cmp_u(ctx, 0, R(11), R(9));
    R(11) = (0 + 1);
    if ((CR_BIT(ctx, 0))) { goto L_8181C3F0; }
    R(11) = (0 + 0);
L_8181C3F0:;
    R(11) = rotl32(R(11), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(7) + R(11)); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[1].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d * ctx->f[1].d);
    goto L_8181C408;
L_8181C404:;
    ctx->f[5].u = ctx->f[0].u;
L_8181C408:;
    R(12) = ld32(base, (R(5) + -240));
    { uint32_t ea_ = (R(10) + 160); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(10) + 144); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(29) = ld32(base, (R(12) + 612));
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[6].d + ctx->f[5].d);
    R(11) = ld32(base, (R(5) + -208));
    R(10) = ld32(base, (R(5) + -176));
    R(30) = ld32(base, (R(5) + -144));
    { uint32_t ea_ = (R(29) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(29) + 48); stfs(base, ea_, ctx->f[5].d); }
    st32(base, (R(29) + 52), R(6));
    R(29) = R(8) |R(8);
    R(0) = ld32(base, (R(3) + 1732));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((CR_BIT(ctx, 1))) { goto L_8181C448; }
    R(29) = (0 + 0x3F800000u);
L_8181C448:;
    R(28) = ld32(base, (R(12) + 612));
    st32(base, (R(28) + 72), R(29));
    st32(base, (R(28) + 68), R(29));
    R(29) = ld32(base, (R(10) + 580));
    { uint32_t ea_ = (R(29) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(29) + 48); stfs(base, ea_, ctx->f[5].d); }
    st32(base, (R(29) + 52), R(6));
    R(29) = ld32(base, (R(30) + 520));
    { uint32_t ea_ = (R(29) + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(29) + 48); stfs(base, ea_, ctx->f[5].d); }
    st32(base, (R(29) + 52), R(6));
    R(30) = ld32(base, (R(30) + 520));
    { uint32_t ea_ = (R(30) + 72); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(30) + 68); stfs(base, ea_, ctx->f[2].d); }
    R(30) = ld32(base, (R(12) + 624));
    R(29) = ld32(base, (R(12) + 616));
    R(28) = ld32(base, (R(11) + 592));
    R(0) = ld32(base, (R(30) + 144));
    R(30) = ld32(base, (R(30) + 160));
    R(27) = ld32(base, (R(29) + 152));
    R(29) = ld32(base, (R(29) + 132));
    st32(base, (R(28) + 52), R(6));
    st32(base, (R(28) + 44), R(0));
    st32(base, (R(28) + 48), R(30));
    R(30) = ld32(base, (R(11) + 592));
    st32(base, (R(30) + 72), R(27));
    st32(base, (R(30) + 68), R(29));
    R(12) = ld32(base, (R(12) + 620));
    R(30) = ld32(base, (R(11) + 588));
    R(0) = ld32(base, (R(12) + 144));
    R(12) = ld32(base, (R(12) + 160));
    st32(base, (R(30) + 52), R(6));
    st32(base, (R(30) + 44), R(0));
    st32(base, (R(30) + 48), R(12));
    R(11) = ld32(base, (R(11) + 588));
    st32(base, (R(11) + 72), R(27));
    st32(base, (R(11) + 68), R(29));
    R(10) = ld32(base, (R(10) + 580));
    st32(base, (R(10) + 72), R(27));
    st32(base, (R(10) + 68), R(29));
    R(10) = ld32(base, (R(3) + 1808));
L_8181C4EC:;
    R(9) = (R(9) + 1);
    cr_cmp_u(ctx, 0, R(9), R(10));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8181C3A8; }
L_8181C4F8:;
    R(30) = ld32(base, (f + 24));
    R(29) = ld32(base, (f + 20));
    R(28) = ld32(base, (f + 16));
    R(27) = ld32(base, (f + 12));
}

/* mod_fn_2_32CD0 (mod_fn_2_32CD0, 584 bytes) */
static void mj_mod_fn_2_32CD0_1c510(GM_CTX) {
    GM_FN(0x8181C510); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x81860000u);
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(4) + -300));
    st32(base, (f + 36), R(4));
    R(4) = (0 + 0x80430000u);
    R(4) = ld16(base, (R(4) + -30926));
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181C670; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30800); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(28) = (R(30) + 1500);
    R(27) = (R(30) + 1940);
    R(26) = (R(30) + 2144);
    R(25) = (0 + 8);
    R(24) = (0 + 0x42480000u);
    R(30) = (f + 12);
    R(29) = (f + 24);
L_8181C580:;
    { uint32_t ea_ = R(26) + 4; R(3) = ld32(base, ea_); R(26) = ea_; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8181C660; }
    R(4) = ld32(base, (R(26) + -128));
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181C660; }
    R(4) = (0 + 0x80370000u);
    { uint32_t ea_ = R(4) + 32200; R(5) = ld32(base, ea_); R(4) = ea_; }
    R(6) = ld32(base, (R(26) + -64));
    st32(base, (f + 24), R(5));
    R(5) = R(4) |R(4);
    R(7) = ld32(base, (R(4) + 8));
    cr_cmp_u(ctx, 0, R(6), 0xAu);
    { uint32_t ea_ = R(5) + 4; R(8) = ld32(base, ea_); R(5) = ea_; }
    st32(base, (f + 32), R(7));
    st32(base, (f + 28), R(8));
    if ((!CR_BIT(ctx, 2))) { goto L_8181C5CC; }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_8181C624;
L_8181C5CC:;
    R(3) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(28) + R(3)));
    R(4) = ld32(base, (R(3) + 144));
    R(3) = ld32(base, (R(3) + 160));
    st32(base, (f + 24), R(4));
    R(4) = R(29) |R(29);
    st32(base, (f + 28), R(3));
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181C5F0u, 0x800B32E0u, 0);
    R(3) = ld32(base, (f + 20));
    ctx->f[0].u = ctx->f[31].u;
    R(5) = ld32(base, (R(26) + -64));
    st32(base, (f + 32), R(3));
    R(3) = ld32(base, (f + 12));
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (f + 16));
    R(5) = ld32(base, (R(28) + R(5)));
    st32(base, (f + 24), R(3));
    R(3) = ld32(base, (R(26) + 0));
    st32(base, (f + 28), R(4));
    R(4) = (R(5) + 68);
    R(5) = (R(5) + 72);
L_8181C624:;
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(6) = ld32(base, (f + 32));
    R(7) = ld32(base, (R(27) + R(3)));
    R(4) = ld32(base, (R(4) + 0));
    R(5) = ld32(base, (R(5) + 0));
    R(8) = ld32(base, (f + 28));
    st32(base, (R(7) + 180), R(6));
    R(6) = ld32(base, (f + 24));
    st32(base, (R(7) + 176), R(8));
    st32(base, (R(7) + 172), R(6));
    R(3) = ld32(base, (R(27) + R(3)));
    st32(base, (R(3) + 544), R(4));
    st32(base, (R(3) + 548), R(5));
    { uint32_t ea_ = (R(3) + 552); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(3) + 604), R(24));
L_8181C660:;
    R(25) = (R(25) + -1);
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8181C580; }
    goto L_8181C710;
L_8181C670:;
    R(4) = ld32(base, (R(30) + 2084));
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 32200);
    { uint32_t ea_ = (R(3) + 8); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(4) = R(30) + R(4);
    R(3) = ld32(base, (R(3) + 8));
    R(4) = ld32(base, (R(4) + 1500));
    st32(base, (f + 32), R(3));
    R(3) = ld32(base, (R(4) + 144));
    R(4) = ld32(base, (R(4) + 160));
    st32(base, (f + 24), R(3));
    R(3) = (f + 12);
    st32(base, (f + 28), R(4));
    R(4) = (f + 24);
    GM_CALLV(0x8181C6B0u, 0x800B32E0u, 0);
    R(3) = ld32(base, (f + 20));
    R(4) = ld32(base, (f + 16));
    st32(base, (f + 32), R(3));
    R(3) = ld32(base, (R(30) + 2084));
    st32(base, (f + 28), R(4));
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = R(30) + R(3);
    R(5) = ld32(base, (R(3) + 1500));
    R(3) = (R(30) + 1936);
    R(4) = ld32(base, (f + 12));
    { uint32_t ea_ = (R(5) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 72); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    st32(base, (f + 24), R(4));
    R(4) = (0 + 8);
    ctx->ctr = R(4);
    R(4) = (0 + 0x42480000u);
L_8181C6F4:;
    { uint32_t ea_ = R(3) + 4; R(5) = ld32(base, ea_); R(3) = ea_; }
    { uint32_t ea_ = (R(5) + 176); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(5) + 544); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 548); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(5) + 552); stfs(base, ea_, ctx->f[31].d); }
    st32(base, (R(5) + 604), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181C6F4; }
L_8181C710:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 36));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8181C754; }
    R(0) = lr;
    return;
L_8181C754:;
    GM_CALLV(0x8181C758u, 0x81844FCCu, 0);
}

/* mod_fn_2_33050 (mod_fn_2_33050, 108 bytes) */
static void mj_mod_fn_2_33050_1c758(GM_CTX) {
    R(4) = (0 + 0x80430000u);
    R(5) = (0 + 0x80430000u);
    R(7) = ld32(base, (R(4) + -24708));
    R(6) = (0 + 8);
    R(5) = ld32(base, (R(5) + -24536));
    R(4) = (0 + 0);
    R(3) = (R(3) + 2016);
    ctx->ctr = R(6);
    R(6) = (R(7) + 2892);
    R(7) = (0 + 3);
L_8181C780:;
    { uint32_t ea_ = R(3) + 4; R(9) = ld32(base, ea_); R(3) = ea_; }
    { uint32_t ea_ = R(5) + 4; R(8) = ld32(base, ea_); R(5) = ea_; }
    cr_cmp_u(ctx, 0, R(9), 0x3u);
    R(9) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8181C7B0; }
    cr_cmp_u(ctx, 0, R(4), 0x4u);
    if ((CR_BIT(ctx, 0))) { goto L_8181C7A4; }
    R(9) = R(6) |R(6);
    goto L_8181C7A8;
L_8181C7A4:;
    R(9) = (R(6) + -1992);
L_8181C7A8:;
    st32(base, (R(9) + 0), R(7));
    R(9) = (0 + 1);
L_8181C7B0:;
    R(4) = (R(4) + 1);
    R(6) = (R(6) + 4);
    st8(base, (R(8) + 84), R(9));
    ctx->ctr--;
    if ((ctx->ctr == 0)) return;
    GM_LOOP(); goto L_8181C780;
}

/* mod_fn_2_33100 (mod_fn_2_33100, 300 bytes) */
static void mj_mod_fn_2_33100_1c7c4(GM_CTX) {
    GM_FRAME(32); gptr f = gm_frame_sp;
    R(4) = (0 + 0x80430000u);
    R(5) = (0 + 0x80430000u);
    R(10) = ld32(base, (R(4) + -24536));
    R(8) = (0 + 12);
    R(9) = ld32(base, (R(5) + -24708));
    R(4) = (0 + 1);
    st32(base, (f + 20), R(29));
    R(5) = (R(3) + 2196);
    st32(base, (f + 24), R(30));
    R(6) = (R(3) + 1576);
    R(7) = (R(3) + 1968);
    ctx->ctr = R(8);
    R(8) = (R(9) + 2892);
    R(9) = (R(9) + 900);
    R(10) = (R(10) + 32);
    R(11) = (0 + 0);
L_8181C808:;
    { uint32_t ea_ = R(10) + 4; R(30) = ld32(base, ea_); R(10) = ea_; }
    { uint32_t ea_ = R(7) + 4; R(0) = ld32(base, ea_); R(7) = ea_; }
    R(12) = ld32(base, (R(30) + 4));
    cr_cmp_u(ctx, 0, R(12), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8181C8DC; }
    R(30) = ld8(base, (R(30) + 86));
    cr_cmp_u(ctx, 0, R(30), 0x3u);
    R(0) = (int8_t)R(30);
    if ((CR_BIT(ctx, 1))) { goto L_8181C838; }
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(30) = R(6) + R(0);
    goto L_8181C848;
L_8181C838:;
    cr_cmp_u(ctx, 0, R(30), 0x8u);
    if ((!CR_BIT(ctx, 0))) { goto L_8181C8C4; }
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(30) = R(5) + R(0);
L_8181C848:;
    R(30) = ld32(base, (R(30) + 0));
    cr_cmp_u(ctx, 0, R(30), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181C898; }
    R(0) = ld8(base, (R(30) + 187));
    R(29) = ~(R(12) | R(12));
    cr_cmp_s(ctx, 0, (int32_t)R(12), -1);
    R(0) = (rotl32(R(29), 1) & 0x1u) | (R(0) & ~0x1u);
    st8(base, (R(30) + 187), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_8181C8A0; }
L_8181C86C:;
    cr_cmp_u(ctx, 0, R(12), 0x4u);
    R(0) = rotl32(R(12), 2) & 0xFFFFFFFCu;
    if ((CR_BIT(ctx, 0))) { goto L_8181C880; }
    R(30) = R(8) + R(0);
    goto L_8181C884;
L_8181C880:;
    R(30) = R(9) + R(0);
L_8181C884:;
    R(0) = ld32(base, (R(30) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 1))) { goto L_8181C8D8; }
    st32(base, (R(30) + 0), R(4));
    goto L_8181C8D8;
L_8181C898:;
    cr_cmp_s(ctx, 0, (int32_t)R(12), 0);
    if ((!CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8181C86C; }
L_8181C8A0:;
    R(0) = ld8(base, (R(3) + 1673));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181C8D8; }
    R(0) = ld32(base, (R(7) + 0));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    if ((CR_BIT(ctx, 0))) { goto L_8181C8D0; }
    R(30) = R(8) + R(0);
    goto L_8181C8D4;
L_8181C8C4:;
    cr_cmp_s(ctx, 0, (int32_t)R(12), -1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8181C86C; }
    GM_LOOP(); goto L_8181C8A0;
L_8181C8D0:;
    R(30) = R(9) + R(0);
L_8181C8D4:;
    st32(base, (R(30) + 0), R(11));
L_8181C8D8:;
    st32(base, (R(7) + 0), R(12));
L_8181C8DC:;
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181C808; }
    R(30) = ld32(base, (f + 24));
    R(29) = ld32(base, (f + 20));
}

/* mod_fn_2_33260 (mod_fn_2_33260, 144 bytes) */
static void mj_mod_fn_2_33260_1c8f0(GM_CTX) {
    GM_FN(0x8181C8F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 1808));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181C960; }
    R(3) = ld32(base, (R(30) + 1732));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 4);
    if ((CR_BIT(ctx, 0))) { goto L_8181C92C; }
    R(3) = (0 + 4);
L_8181C92C:;
    R(29) = (R(3) + -1);
    R(28) = (R(30) + 2080);
    R(27) = (0 + 0);
L_8181C938:;
    R(5) = R(27) & 0x3u;
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    GM_CALLV(0x8181C948u, 0x807A09F0u, 0);
    { uint32_t ea_ = R(28) + 4; st32(base, ea_, R(3)); R(28) = ea_; }
    R(27) = (R(27) + 1);
    st32(base, (R(28) + -32), R(3));
    R(3) = ld32(base, (R(30) + 1808));
    cr_cmp_u(ctx, 0, R(27), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8181C938; }
L_8181C960:;
    R(0) = lr;
}

/* mod_fn_2_332E0 (mod_fn_2_332E0, 432 bytes) */
static void mj_mod_fn_2_332E0_1c980(GM_CTX) {
    GM_FN(0x8181C980); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(27) = (0 + 0x81860000u);
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(27) + -300));
    st32(base, (f + 44), R(4));
    R(3) = ld32(base, (R(3) + 1808));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181CAE0; }
    R(3) = (0 + -30672);
    R(26) = (R(30) + 2052);
    R(25) = (R(30) + 1500);
    R(24) = (R(30) + 1812);
    R(23) = (0 + 0);
    R(22) = (0 + 4);
    R(29) = (f + 20);
    R(21) = (R(3) + 0x81850000u);
    R(28) = (f + 32);
L_8181C9F8:;
    R(4) = (0 + 0x80370000u);
    { uint32_t ea_ = R(4) + 32200; R(5) = ld32(base, ea_); R(4) = ea_; }
    R(20) = rotl32(R(23), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(26) + R(20)));
    st32(base, (f + 32), R(5));
    R(5) = ld32(base, (R(4) + 8));
    cr_cmp_u(ctx, 0, R(3), 0xAu);
    R(4) = ld32(base, (R(4) + 4));
    st32(base, (f + 40), R(5));
    st32(base, (f + 36), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_8181CA60; }
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(25) + R(3)));
    R(4) = ld32(base, (R(3) + 144));
    R(3) = ld32(base, (R(3) + 160));
    st32(base, (f + 32), R(4));
    R(4) = R(28) |R(28);
    st32(base, (f + 36), R(3));
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181CA48u, 0x800B32E0u, 0);
    R(3) = ld32(base, (f + 28));
    R(4) = ld32(base, (f + 24));
    st32(base, (f + 40), R(3));
    R(3) = ld32(base, (f + 20));
    st32(base, (f + 36), R(4));
    st32(base, (f + 32), R(3));
L_8181CA60:;
    R(3) = ld32(base, (R(30) + 1732));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 5);
    if ((CR_BIT(ctx, 0))) { goto L_8181CAA0; }
    cr_cmp_u(ctx, 0, R(3), 0x7u);
    R(3) = (0 + 2);
    if ((CR_BIT(ctx, 0))) { goto L_8181CA7C; }
    R(3) = (0 + 3);
L_8181CA7C:;
    cr_cmp_u(ctx, 0, R(3), R(23));
    R(3) = (0 + 1);
    if ((CR_BIT(ctx, 0))) { goto L_8181CA8C; }
    R(3) = (0 + 0);
L_8181CA8C:;
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (f + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(21) + R(3)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
L_8181CAA0:;
    R(3) = R(24) + R(20);
    R(4) = (0 + 676);
    ctx->ctr = R(22);
L_8181CAAC:;
    R(5) = ld32(base, (R(3) + 0));
    R(6) = ld32(base, (f + 32));
    { uint32_t ea_ = R(5) + R(4); st32(base, ea_, R(6)); R(5) = ea_; }
    R(4) = (R(4) + 12);
    R(6) = ld32(base, (f + 40));
    st32(base, (R(5) + 8), R(6));
    R(6) = ld32(base, (f + 36));
    st32(base, (R(5) + 4), R(6));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181CAAC; }
    R(3) = ld32(base, (R(30) + 1808));
    R(23) = (R(23) + 1);
    cr_cmp_u(ctx, 0, R(23), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8181C9F8; }
L_8181CAE0:;
    R(3) = ld32(base, (R(27) + -300));
    R(4) = ld32(base, (f + 44));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8181CB2C; }
    R(0) = lr;
    return;
L_8181CB2C:;
    GM_CALLV(0x8181CB30u, 0x81844FCCu, 0);
}

/* mod_fn_2_33480 (mod_fn_2_33480, 228 bytes) */
static void mj_mod_fn_2_33480_1cb30(GM_CTX) {
    GM_FN(0x8181CB30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(4) + -300));
    R(5) = (0 + 0);
    R(7) = (0 + 0x81860000u);
    R(6) = (0 + 8);
    st32(base, (f + 28), R(4));
    R(7) = (R(7) + -5828);
    st32(base, (f + 20), R(5));
    R(4) = (f + 16);
    st32(base, (f + 16), R(5));
    R(5) = (R(3) + 2016);
    R(7) = (R(7) + -4);
    ctx->ctr = R(6);
    R(6) = (0 + 1);
L_8181CB74:;
    { uint32_t ea_ = R(5) + 4; R(8) = ld32(base, ea_); R(5) = ea_; }
    cr_cmp_u(ctx, 0, R(8), 0x3u);
    R(8) = (R(7) + 4);
    if ((!CR_BIT(ctx, 2))) { goto L_8181CB90; }
    R(9) = ld32(base, (R(5) + 128));
    st32(base, (R(7) + 4), R(9));
    st8(base, (R(4) + R(9)), R(6));
L_8181CB90:;
    R(7) = R(8) |R(8);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181CB74; }
    R(5) = (0 + 8);
    R(7) = (0 + 0x81860000u);
    R(3) = (R(3) + 2016);
    R(6) = (0 + 0);
    ctx->ctr = R(5);
    R(5) = (R(7) + -5828);
    R(7) = (0 + 0);
L_8181CBB4:;
    R(8) = ld8(base, (R(4) + R(7)));
    cr_cmp_u(ctx, 0, R(8), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181CBE4; }
    R(8) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(8) = R(3) + R(8);
L_8181CBC8:;
    { uint32_t ea_ = R(8) + 4; R(10) = ld32(base, ea_); R(8) = ea_; }
    R(9) = R(6) |R(6);
    R(6) = (R(6) + 1);
    cr_cmp_u(ctx, 0, R(10), 0x3u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8181CBC8; }
    R(8) = rotl32(R(9), 2) & 0xFFFFFFFCu;
    st32(base, (R(5) + R(8)), R(7));
L_8181CBE4:;
    R(7) = (R(7) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181CBB4; }
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 28));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8181CC10; }
    R(0) = lr;
    return;
L_8181CC10:;
    GM_CALLV(0x8181CC14u, 0x81844FCCu, 0);
}

/* mod_fn_2_33630 (mod_fn_2_33630, 16 bytes) */
static void mj_mod_fn_2_33630_1ccf4(GM_CTX) {
    R(4) = (0 + 0);
    st8(base, (R(3) + 1673), R(4));
    st8(base, (R(3) + 1671), R(4));
}

/* mod_fn_2_33640 (mod_fn_2_33640, 724 bytes) */
static void mj_mod_fn_2_33640_1cd04(GM_CTX) {
    GM_FN(0x8181CD04); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x80430000u);
    R(3) = (R(3) + -24704);
    R(3) = ld8(base, (R(3) + 3));
    R(3) = R(3) & 0x10u;
    CR0(ctx, R(3));
    R(3) = (0 + 0x80430000u);
    R(29) = ld32(base, (R(3) + -24708));
    if ((CR_BIT(ctx, 2))) { goto L_8181CD48; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181CD48u, 0x800BB130u, 0);
L_8181CD48:;
    R(5) = (0 + 1);
    R(3) = (0 + 0);
    R(28) = R(30) |R(30);
    st8(base, (R(29) + 2812), R(5));
    R(5) = (0 + 0x81860000u);
    R(6) = (0 + 8);
    { uint32_t ea_ = R(28) + 1696; st32(base, ea_, R(3)); R(28) = ea_; }
    R(7) = (R(5) + -5828);
    R(4) = (R(29) + 2892);
    R(27) = (R(28) + 324);
    R(5) = (R(28) + 480);
    ctx->ctr = R(6);
    R(6) = (R(7) + -4);
    R(7) = (0 + 0);
L_8181CD80:;
    { uint32_t ea_ = R(6) + 4; R(8) = ld32(base, ea_); R(6) = ea_; }
    cr_cmp_u(ctx, 0, R(3), 0x4u);
    { uint32_t ea_ = R(5) + 4; st32(base, ea_, R(8)); R(5) = ea_; }
    st32(base, (R(5) + -32), R(8));
    if ((CR_BIT(ctx, 0))) { goto L_8181CD9C; }
    R(8) = R(4) |R(4);
    goto L_8181CDA0;
L_8181CD9C:;
    R(8) = (R(4) + -1992);
L_8181CDA0:;
    R(8) = ld32(base, (R(8) + 0));
    cr_cmp_u(ctx, 0, R(8), 0x3u);
    st32(base, (R(5) + -160), R(8));
    if ((!CR_BIT(ctx, 2))) { goto L_8181CDB8; }
    R(7) = (R(7) + 1);
    st32(base, (R(28) + 0), R(7));
L_8181CDB8:;
    R(3) = (R(3) + 1);
    R(4) = (R(4) + 4);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181CD80; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181CDCCu, 0x8181C8F0u, 0);
    R(3) = ld32(base, (R(30) + 1808));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (R(30) + 1940);
    if ((CR_BIT(ctx, 2))) { goto L_8181CE58; }
    R(4) = (R(30) + 1808);
    R(5) = (0 + 0);
    R(6) = (0 + -1);
    R(7) = (0 + 0x42480000u);
L_8181CDEC:;
    { uint32_t ea_ = R(4) + 4; R(8) = ld32(base, ea_); R(4) = ea_; }
    R(5) = (R(5) + 1);
    R(9) = ld32(base, (R(30) + 1732));
    R(11) = ld32(base, (R(4) + 64));
    st32(base, (R(8) + 744), R(9));
    R(9) = ld32(base, (R(4) + 96));
    R(10) = ld32(base, (R(4) + 32));
    st32(base, (R(8) + 120), R(11));
    R(11) = ld32(base, (R(9) + 540));
    st32(base, (R(8) + 640), R(27));
    st32(base, (R(8) + 648), R(28));
    st32(base, (R(8) + 128), R(3));
    st32(base, (R(4) + 304), R(6));
    st32(base, (R(8) + 116), R(10));
    st32(base, (R(8) + 124), R(9));
    st32(base, (R(10) + 520), R(9));
    R(10) = ld8(base, (R(11) + 187));
    R(10) = R(10) | 0x1u;
    st8(base, (R(11) + 187), R(10));
    R(9) = ld32(base, (R(9) + 544));
    R(10) = ld8(base, (R(9) + 187));
    R(10) = R(10) | 0x1u;
    st8(base, (R(9) + 187), R(10));
    R(9) = ld32(base, (R(30) + 1808));
    st32(base, (R(8) + 752), R(7));
    cr_cmp_u(ctx, 0, R(5), R(9));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8181CDEC; }
L_8181CE58:;
    R(9) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(9) + -30772); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(7) = (0 + 8);
    R(8) = (0 + 0x81860000u);
    ctx->ctr = R(7);
    R(7) = (R(8) + -5828);
    R(4) = (R(30) + 2016);
    R(5) = (0 + 0x42480000u);
    R(6) = (0 + 1);
    R(7) = (R(7) + -4);
L_8181CE80:;
    { uint32_t ea_ = R(7) + 4; R(8) = ld32(base, ea_); R(7) = ea_; }
    { uint32_t ea_ = R(4) + 4; R(9) = ld32(base, ea_); R(4) = ea_; }
    R(8) = rotl32(R(8), 2) & 0xFFFFFFFCu;
    R(8) = ld32(base, (R(3) + R(8)));
    cr_cmp_u(ctx, 0, R(9), 0x3u);
    st32(base, (R(8) + 604), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_8181CEAC; }
    { uint32_t ea_ = (R(8) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st8(base, (R(8) + 609), R(6));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(8) + 176); stfs(base, ea_, ctx->f[1].d); }
L_8181CEAC:;
    st8(base, (R(8) + 615), R(6));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181CE80; }
    R(3) = ld32(base, (R(30) + 1564));
    R(4) = (0 + 0x80430000u);
    R(4) = ld16(base, (R(4) + -30926));
    R(5) = ld8(base, (R(3) + 187));
    R(6) = R(4) ^ 0x3u;
    R(7) = cntlzw(R(6));
    R(5) = R(5) & 0xFEu;
    R(5) = (rotl32(R(7), 27) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(3) + 187), R(5));
    { uint32_t a_ = R(6); R(8) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(8) < a_; }
    R(3) = ld32(base, (R(30) + 1568));
    { uint64_t t_ = (uint64_t)(~R(8)) + (R(6)) + ctx->xer_ca; R(6) = t_; ctx->xer_ca = (t_ >> 32); }
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    R(5) = ld8(base, (R(3) + 187));
    R(5) = R(5) & 0xFEu;
    R(5) = (rotl32(R(7), 27) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(3) + 187), R(5));
    R(3) = ld32(base, (R(30) + 1572));
    R(5) = ld8(base, (R(3) + 187));
    R(5) = R(5) & 0xFEu;
    R(5) = (rotl32(R(6), 0) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(3) + 187), R(5));
    R(3) = ld32(base, (R(30) + 1540));
    R(5) = ld8(base, (R(3) + 187));
    R(5) = R(5) & 0xFEu;
    R(5) = (rotl32(R(7), 27) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(3) + 187), R(5));
    R(3) = ld32(base, (R(30) + 1544));
    R(5) = ld8(base, (R(3) + 187));
    R(5) = R(5) & 0xFEu;
    R(5) = (rotl32(R(6), 0) & 0x1u) | (R(5) & ~0x1u);
    st8(base, (R(3) + 187), R(5));
    if ((CR_BIT(ctx, 2))) { goto L_8181CF64; }
    R(3) = ld32(base, (R(30) + 1732));
    st32(base, (R(29) + 972), R(3));
    R(29) = ld32(base, (R(30) + 1544));
    GM_CALLV(0x8181CF48u, 0x800CDC60u, 0);
    R(4) = R(3) |R(3);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(3) = R(29) |R(29);
    R(5) = (0 + 2);
    R(6) = (0 + 28);
    R(7) = (0 + 0);
    GM_CALLV(0x8181CF64u, 0x800C9A60u, 0);
L_8181CF64:;
    R(29) = (R(30) + 1028);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181CF70u, 0x800C9500u, 0);
    R(3) = R(29) |R(29);
    R(4) = (0 + 2);
    R(5) = (0 + 0);
    R(28) = (0 + 0);
    GM_CALLV(0x8181CF84u, 0x800C93D0u, 0);
    R(3) = R(29) |R(29);
    R(4) = (0 + 3);
    R(5) = (0 + 0);
    GM_CALLV(0x8181CF94u, 0x800C93D0u, 0);
    R(3) = ld32(base, (R(30) + 1496));
    R(4) = ld8(base, (R(3) + 187));
    R(4) = R(4) | 0x1u;
    st8(base, (R(3) + 187), R(4));
    R(4) = (0 + 0x80990000u);
    R(3) = (R(30) + 1460);
    R(4) = (R(4) + 17712);
    st8(base, (R(30) + 1664), R(28));
    GM_CALLV(0x8181CFB8u, 0x8015FC10u, 0);
    R(0) = lr;
}

/* mfn_8181CFD8 (mfn_8181CFD8, 36 bytes) */
static void mj_mfn_8181CFD8_1cfd8(GM_CTX) {
    GM_FN(0x8181CFD8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (R(3) + 24);
    GM_CALLV(0x8181CFECu, 0x8015FC10u, 0);
    R(0) = lr;
}

/* mod_fn_2_33A00 (mod_fn_2_33A00, 36 bytes) */
static void mj_mod_fn_2_33A00_1cffc(GM_CTX) {
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24536));
    R(4) = (0 + 8);
    ctx->ctr = R(4);
    R(4) = (0 + 1);
L_8181D010:;
    { uint32_t ea_ = R(3) + 4; R(5) = ld32(base, ea_); R(3) = ea_; }
    st8(base, (R(5) + 84), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181D010; }
}

/* mod_fn_2_33A30 (mod_fn_2_33A30, 252 bytes) */
static void mj_mod_fn_2_33A30_1d020(GM_CTX) {
    GM_FN(0x8181D020); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 1);
    R(30) = R(3) |R(3);
    R(3) = (0 + 256);
    R(29) = (R(30) + 1028);
    st16(base, (R(30) + 1671), R(3));
    R(3) = R(29) |R(29);
    R(5) = (0 + 0);
    R(27) = (0 + 0);
    R(28) = (0 + 1);
    GM_CALLV(0x8181D064u, 0x800C92F0u, 0);
    R(3) = R(29) |R(29);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x8181D074u, 0x800C92F0u, 0);
    R(5) = ld32(base, (R(30) + 1732));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181D0CC; }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = R(3) + 1808; R(4) = ld32(base, ea_); R(3) = ea_; }
    ctx->ctr = R(5);
    R(5) = (R(3) + 308);
    R(6) = (R(3) + 372);
    R(7) = (R(3) + 340);
L_8181D098:;
    { uint32_t ea_ = R(3) + 4; R(8) = ld32(base, ea_); R(3) = ea_; }
    R(9) = ld32(base, (R(3) + 96));
    st8(base, (R(8) + 661), R(28));
    st32(base, (R(8) + 644), R(5));
    st32(base, (R(8) + 656), R(6));
    st32(base, (R(8) + 652), R(7));
    st32(base, (R(8) + 756), R(4));
    st32(base, (R(9) + 572), R(27));
    st8(base, (R(9) + 569), R(28));
    st32(base, (R(9) + 584), R(28));
    st32(base, (R(9) + 588), R(27));
    st32(base, (R(9) + 564), R(27));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181D098; }
L_8181D0CC:;
    R(30) = (R(30) + 1936);
    R(29) = (0 + 8);
L_8181D0D4:;
    { uint32_t ea_ = R(30) + 4; R(3) = ld32(base, ea_); R(30) = ea_; }
    R(3) = ld32(base, (R(3) + 296));
    R(3) = ld32(base, (R(3) + 4));
    R(4) = ld32(base, (R(3) + 0));
    R(4) = ld32(base, (R(4) + 172));
    ctx->ctr = R(4);
    GM_CALLV(0x8181D0F0u, ctx->ctr, 0);
    R(29) = (R(29) + -1);
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8181D0D4; }
    R(0) = lr;
}

/* mod_fn_2_33B60 (mod_fn_2_33B60, 108 bytes) */
static void mj_mod_fn_2_33B60_1d11c(GM_CTX) {
    GM_FN(0x8181D11C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 1);
    R(29) = (R(3) + 1028);
    R(30) = R(3) |R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181D144u, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D170; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 0);
    GM_CALLV(0x8181D158u, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D170; }
    R(4) = (0 + 0x80990000u);
    R(3) = (R(30) + 1460);
    R(4) = (R(4) + 17776);
    GM_CALLV(0x8181D170u, 0x8015FC10u, 0);
L_8181D170:;
    R(0) = lr;
}

/* mod_fn_2_33BD0 (mod_fn_2_33BD0, 36 bytes) */
static void mj_mod_fn_2_33BD0_1d188(GM_CTX) {
    R(4) = (0 + 0);
    st8(base, (R(3) + 1671), R(4));
    R(3) = (R(3) + 1936);
    R(5) = (0 + 8);
    ctx->ctr = R(5);
L_8181D19C:;
    { uint32_t ea_ = R(3) + 4; R(5) = ld32(base, ea_); R(3) = ea_; }
    st8(base, (R(5) + 615), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181D19C; }
}

/* mod_fn_2_33C10 (mod_fn_2_33C10, 284 bytes) */
static void mj_mod_fn_2_33C10_1d1ac(GM_CTX) {
    GM_FN(0x8181D1AC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(4) = ld16(base, (R(4) + -30926));
    R(30) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(4), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D274; }
    R(3) = (0 + 0x80430000u);
    R(26) = ld32(base, (R(3) + -24536));
    R(4) = (0 + 0x80370000u);
    R(27) = (0 + 8);
    R(29) = (0 + 0);
    R(28) = (R(4) + 6256);
    R(25) = (0 + 0x80430000u);
L_8181D200:;
    { uint32_t ea_ = R(26) + 4; R(3) = ld32(base, ea_); R(26) = ea_; }
    R(3) = ld32(base, (R(3) + 144));
    R(4) = ld32(base, (R(3) + 0));
    R(4) = ld32(base, (R(4) + 16));
    ctx->ctr = R(4);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8181D21Cu, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D240; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181D22Cu, 0x8180ADB8u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181D240; }
    R(3) = ld32(base, (R(25) + -23848));
    R(4) = R(29) |R(29);
    GM_CALLV(0x8181D240u, 0x8010E600u, 0);
L_8181D240:;
    R(27) = (R(27) + -1);
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    R(29) = (R(29) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8181D200; }
    R(3) = ld32(base, (R(30) + 1696));
    R(4) = ld32(base, (R(30) + 1732));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(4));
    if ((CR_BIT(ctx, 0))) { goto L_8181D290; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181D268u, 0x8181C980u, 0);
    R(3) = (0 + 0x80990000u);
    R(4) = (R(3) + 17904);
    goto L_8181D298;
L_8181D274:;
    R(3) = ld32(base, (R(30) + 1696));
    R(4) = ld32(base, (R(30) + 1732));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(4));
    if ((CR_BIT(ctx, 0))) { goto L_8181D290; }
    R(3) = (0 + 0x80990000u);
    R(4) = (R(3) + 18032);
    goto L_8181D298;
L_8181D290:;
    R(3) = (0 + 0x80990000u);
    R(4) = (R(3) + 17840);
L_8181D298:;
    R(3) = (R(30) + 1460);
    GM_CALLV(0x8181D2A0u, 0x8015FC10u, 0);
    R(0) = lr;
}

/* mod_fn_2_33D50 (mod_fn_2_33D50, 12 bytes) */
static void mj_mod_fn_2_33D50_1d2c8(GM_CTX) {
    R(4) = (0 + 1);
    st8(base, (R(3) + 1673), R(4));
}

/* mod_fn_2_33D60 (mod_fn_2_33D60, 72 bytes) */
static void mj_mod_fn_2_33D60_1d2d4(GM_CTX) {
    GM_FN(0x8181D2D4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 1);
    R(6) = ld32(base, (R(3) + 1732));
    st8(base, (R(3) + 1664), R(4));
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181D308; }
    R(5) = (R(3) + 1808);
    ctx->ctr = R(6);
L_8181D2FC:;
    { uint32_t ea_ = R(5) + 4; R(6) = ld32(base, ea_); R(5) = ea_; }
    st8(base, (R(6) + 665), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181D2FC; }
L_8181D308:;
    GM_CALLV(0x8181D30Cu, 0x8181C980u, 0);
    R(0) = lr;
}

/* mod_fn_2_340C0 (mod_fn_2_340C0, 44 bytes) */
static void mj_mod_fn_2_340C0_1d5e0(GM_CTX) {
    GM_FN(0x8181D5E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80990000u);
    R(3) = (R(3) + 1460);
    R(4) = (R(4) + 18032);
    GM_CALLV(0x8181D5FCu, 0x8015FC10u, 0);
    R(0) = lr;
}

/* mod_fn_2_340F0 (mod_fn_2_340F0, 232 bytes) */
static void mj_mod_fn_2_340F0_1d60c(GM_CTX) {
    GM_FN(0x8181D60C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 4);
    R(29) = (R(3) + 1028);
    R(30) = R(3) |R(3);
    R(3) = R(29) |R(29);
    R(5) = (0 + 0);
    GM_CALLV(0x8181D638u, 0x800C92F0u, 0);
    R(3) = R(29) |R(29);
    R(4) = (0 + 2);
    R(5) = (0 + 0);
    GM_CALLV(0x8181D648u, 0x800C92F0u, 0);
    R(3) = R(29) |R(29);
    R(4) = (0 + 5);
    R(5) = (0 + 0);
    GM_CALLV(0x8181D658u, 0x800C92F0u, 0);
    R(3) = R(29) |R(29);
    R(4) = (0 + 3);
    R(5) = (0 + 0);
    GM_CALLV(0x8181D668u, 0x800C92F0u, 0);
    R(4) = (0 + 8);
    R(3) = (R(30) + 1936);
    ctx->ctr = R(4);
    R(4) = (0 + 1);
L_8181D678:;
    { uint32_t ea_ = R(3) + 4; R(5) = ld32(base, ea_); R(3) = ea_; }
    st8(base, (R(5) + 614), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181D678; }
    R(3) = ld32(base, (R(30) + 1808));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181D6CC; }
    R(3) = (R(30) + 1904);
    R(4) = (0 + 0);
L_8181D698:;
    { uint32_t ea_ = R(3) + 4; R(5) = ld32(base, ea_); R(3) = ea_; }
    R(4) = (R(4) + 1);
    R(6) = ld32(base, (R(5) + 540));
    R(7) = ld8(base, (R(6) + 187));
    R(7) = R(7) & 0xFEu;
    st8(base, (R(6) + 187), R(7));
    R(5) = ld32(base, (R(5) + 544));
    R(6) = ld8(base, (R(5) + 187));
    R(6) = R(6) & 0xFEu;
    st8(base, (R(5) + 187), R(6));
    R(5) = ld32(base, (R(30) + 1808));
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8181D698; }
L_8181D6CC:;
    R(3) = (0 + 1);
    st8(base, (R(30) + 1672), R(3));
    R(3) = (0 + 0);
    st8(base, (R(30) + 1664), R(3));
    R(0) = lr;
}

/* mod_fn_2_34220 (mod_fn_2_34220, 164 bytes) */
static void mj_mod_fn_2_34220_1d6f4(GM_CTX) {
    GM_FN(0x8181D6F4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 4);
    R(29) = (R(3) + 1028);
    R(30) = R(3) |R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181D71Cu, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D780; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 2);
    GM_CALLV(0x8181D730u, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D780; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 5);
    GM_CALLV(0x8181D744u, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D780; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 3);
    GM_CALLV(0x8181D758u, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D780; }
    R(3) = (0 + 0);
    st32(base, (R(30) + 1736), R(3));
    R(3) = (0 + -1);
    R(4) = (0 + 0x80990000u);
    st32(base, (R(30) + 1740), R(3));
    R(3) = (R(30) + 1460);
    R(4) = (R(4) + 18096);
    GM_CALLV(0x8181D780u, 0x8015FC10u, 0);
L_8181D780:;
    R(0) = lr;
}

/* mod_fn_2_342E0 (mod_fn_2_342E0, 100 bytes) */
static void mj_mod_fn_2_342E0_1d798(GM_CTX) {
    GM_FN(0x8181D798); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 1740));
    R(30) = (R(29) + 1028);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8181D7D0; }
    R(4) = (R(3) + 12);
    R(3) = R(30) |R(30);
    R(5) = (0 + 0);
    GM_CALLV(0x8181D7D0u, 0x800C92F0u, 0);
L_8181D7D0:;
    R(3) = ld32(base, (R(29) + 1736));
    R(5) = (0 + 0);
    R(4) = (R(3) + 6);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181D7E4u, 0x800C92F0u, 0);
    R(0) = lr;
}

/* mod_fn_2_34340 (mod_fn_2_34340, 124 bytes) */
static void mj_mod_fn_2_34340_1d7fc(GM_CTX) {
    GM_FN(0x8181D7FC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 1740));
    R(29) = (R(30) + 1028);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8181D838; }
    R(4) = (R(3) + 12);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181D830u, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D860; }
L_8181D838:;
    R(3) = ld32(base, (R(30) + 1736));
    R(4) = (R(3) + 6);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8181D848u, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181D860; }
    R(4) = (0 + 0x80990000u);
    R(3) = (R(30) + 1460);
    R(4) = (R(4) + 18160);
    GM_CALLV(0x8181D860u, 0x8015FC10u, 0);
L_8181D860:;
    R(0) = lr;
}

/* mod_fn_2_343D0 (mod_fn_2_343D0, 56 bytes) */
static void mj_mod_fn_2_343D0_1d878(GM_CTX) {
    GM_FN(0x8181D878); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0);
    R(4) = ld32(base, (R(3) + 1736));
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(4);
    R(3) = ld32(base, (R(3) + 1556));
    R(4) = (0 + 0);
    GM_CALLV(0x8181D8A0u, 0x800B44D0u, 0);
    R(0) = lr;
}

/* mod_fn_2_345A0 (mod_fn_2_345A0, 48 bytes) */
static void mj_mod_fn_2_345A0_1da2c(GM_CTX) {
    GM_FN(0x8181DA2C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0);
    R(4) = ld32(base, (R(3) + 1736));
    R(3) = (R(3) + 1028);
    R(4) = (R(4) + 10);
    GM_CALLV(0x8181DA4Cu, 0x800C92F0u, 0);
    R(0) = lr;
}

/* mod_fn_2_34630 (mod_fn_2_34630, 188 bytes) */
static void mj_mod_fn_2_34630_1daa8(GM_CTX) {
    GM_FN(0x8181DAA8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(12) = ctx->cr;
    R(4) = (0 + 0x80430000u);
    R(30) = R(3) |R(3);
    st32(base, (f + 16), R(12));
    R(3) = (0 + 0);
    R(4) = ld16(base, (R(4) + -30926));
    R(29) = (R(30) + 1028);
    st8(base, (R(30) + 1664), R(3));
    R(3) = ld32(base, (R(30) + 1736));
    R(4) = R(4) & 0xFFFFu;
    R(5) = ld8(base, (R(30) + 1672));
    R(4) = R(4) ^ 0x3u;
    R(3) = R(3) ^ 0x1u;
    R(3) = cntlzw(R(3));
    R(4) = cntlzw(R(4));
    R(3) = R(3) |R(4);
    R(3) = rotl32(R(3), 27) & 0x7FFFFFFu;
    CR0(ctx, R(3));
    CR_SET(ctx, 2, (ctx->cr >> 28) & 0xF);
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181DB24; }
    R(4) = (0 + 17);
    if ((!CR_BIT(ctx, 10))) { goto L_8181DB18; }
    R(4) = (0 + 15);
L_8181DB18:;
    R(3) = R(29) |R(29);
    R(5) = (0 + 0);
    GM_CALLV(0x8181DB24u, 0x800C92F0u, 0);
L_8181DB24:;
    R(4) = (0 + 16);
    if ((!CR_BIT(ctx, 10))) { goto L_8181DB30; }
    R(4) = (0 + 14);
L_8181DB30:;
    R(3) = R(29) |R(29);
    R(5) = (0 + 0);
    GM_CALLV(0x8181DB3Cu, 0x800C92F0u, 0);
    R(3) = (0 + 1);
    st8(base, (R(30) + 1671), R(3));
    R(12) = ld32(base, (f + 16));
    ctx->cr = (ctx->cr & ~0xF00000u) | (R(12) & 0xF00000u);
    R(0) = lr;
}

/* mod_fn_2_34710 (mod_fn_2_34710, 536 bytes) */
static void mj_mod_fn_2_34710_1db64(GM_CTX) {
    GM_FN(0x8181DB64); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + -1);
    R(30) = R(3) |R(3);
    R(3) = (R(3) + 1028);
    GM_CALLV(0x8181DB98u, 0x800C9610u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181DD54; }
    R(3) = ld32(base, (R(30) + 1496));
    R(4) = ld8(base, (R(3) + 187));
    R(4) = R(4) & 0xFEu;
    st8(base, (R(3) + 187), R(4));
    R(4) = (0 + 0x80990000u);
    R(3) = (R(30) + 1460);
    R(4) = (R(4) + 17648);
    GM_CALLV(0x8181DBC0u, 0x8015FC10u, 0);
    R(4) = ld32(base, (R(30) + 1808));
    R(3) = (0 + 0x80430000u);
    R(29) = ld32(base, (R(3) + -24708));
    R(3) = (0 + 0);
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    st8(base, (R(30) + 1662), R(3));
    st8(base, (R(29) + 2812), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8181DC94; }
    R(4) = (0 + 0x80430000u);
    R(0) = ld16(base, (R(4) + -30926));
    R(10) = (0 + 0x81850000u);
    R(11) = (0 + 0x81860000u);
    R(5) = (R(30) + 2180);
    R(6) = (R(30) + 1940);
    R(7) = (R(30) + 1908);
    R(8) = (0 + 1);
    R(9) = (0 + 4);
    R(10) = (R(10) + -25628);
    R(11) = (R(11) + -5828);
    R(12) = (0 + 0);
L_8181DC10:;
    R(28) = ld32(base, (R(30) + 1736));
    cr_cmp_u(ctx, 0, R(28), 0x1u);
    R(28) = rotl32(R(12), 2) & 0xFFFFFFFCu;
    if ((!CR_BIT(ctx, 2))) { goto L_8181DC40; }
    R(27) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(27), 0xAu);
    if ((!CR_BIT(ctx, 2))) { goto L_8181DC40; }
    R(27) = ld32(base, (R(10) + R(28)));
    st32(base, (R(5) + R(28)), R(27));
    R(0) = ld16(base, (R(4) + -30926));
    st32(base, (R(11) + R(28)), R(27));
    goto L_8181DC44;
L_8181DC40:;
    R(27) = ld32(base, (R(11) + R(28)));
L_8181DC44:;
    R(27) = rotl32(R(27), 2) & 0xFFFFFFFCu;
    R(27) = ld32(base, (R(6) + R(27)));
    R(26) = ld8(base, (R(27) + 609));
    cr_cmp_u(ctx, 0, R(26), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181DC5C; }
    st8(base, (R(27) + 617), R(8));
L_8181DC5C:;
    R(28) = ld32(base, (R(7) + R(28)));
    ctx->ctr = R(9);
    R(27) = (R(28) + 520);
L_8181DC68:;
    { uint32_t ea_ = R(27) + 4; R(26) = ld32(base, ea_); R(27) = ea_; }
    R(25) = ld8(base, (R(26) + 187));
    R(25) = R(25) & 0xFEu;
    st8(base, (R(26) + 187), R(25));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181DC68; }
    R(27) = ld32(base, (R(30) + 1808));
    R(12) = (R(12) + 1);
    st8(base, (R(28) + 569), R(3));
    cr_cmp_u(ctx, 0, R(12), R(27));
    st32(base, (R(28) + 572), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8181DC10; }
L_8181DC94:;
    R(3) = (R(29) + 2892);
    R(5) = (0 + 8);
    R(4) = (0 + 0);
    ctx->ctr = R(5);
    R(5) = R(3) |R(3);
    R(6) = (0 + 0);
L_8181DCAC:;
    cr_cmp_u(ctx, 0, R(6), 0x4u);
    if ((CR_BIT(ctx, 0))) { goto L_8181DCBC; }
    R(7) = R(5) |R(5);
    goto L_8181DCC0;
L_8181DCBC:;
    R(7) = (R(5) + -1992);
L_8181DCC0:;
    R(6) = (R(6) + 1);
    R(5) = (R(5) + 4);
    st32(base, (R(7) + 0), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181DCAC; }
    R(4) = ld32(base, (R(30) + 1736));
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181DD18; }
    R(5) = (0 + 8);
    R(4) = (R(30) + 2016);
    ctx->ctr = R(5);
    R(5) = (0 + 0);
L_8181DCEC:;
    cr_cmp_u(ctx, 0, R(5), 0x4u);
    if ((CR_BIT(ctx, 0))) { goto L_8181DCFC; }
    R(6) = R(3) |R(3);
    goto L_8181DD00;
L_8181DCFC:;
    R(6) = (R(3) + -1992);
L_8181DD00:;
    { uint32_t ea_ = R(4) + 4; R(7) = ld32(base, ea_); R(4) = ea_; }
    R(5) = (R(5) + 1);
    R(3) = (R(3) + 4);
    st32(base, (R(6) + 0), R(7));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181DCEC; }
    goto L_8181DD38;
L_8181DD18:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181DD20u, 0x8181CB30u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181DD28u, 0x8181C758u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23848));
    R(4) = (0 + 1);
    st8(base, (R(3) + 3069), R(4));
L_8181DD38:;
    R(30) = (R(29) + 8);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181DD44u, 0x8008EEC0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8181DD54; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8181DD54u, 0x8008EDB0u, 0);
L_8181DD54:;
    R(0) = lr;
}

/* mod_fn_2_34910 (mod_fn_2_34910, 120 bytes) */
static void mj_mod_fn_2_34910_1dd7c(GM_CTX) {
    R(4) = (0 + 0x80430000u);
    R(7) = ld16(base, (R(4) + -30926));
    R(5) = (0 + 8);
    R(4) = (R(3) + 1936);
    ctx->ctr = R(5);
    R(5) = (0 + 0);
    R(6) = (0 + 1);
    cr_cmp_u(ctx, 0, R(7), 0x3u);
L_8181DD9C:;
    { uint32_t ea_ = R(4) + 4; R(7) = ld32(base, ea_); R(4) = ea_; }
    st8(base, (R(7) + 614), R(5));
    st8(base, (R(7) + 617), R(6));
    if ((!CR_BIT(ctx, 2))) { goto L_8181DDB0; }
    st8(base, (R(7) + 618), R(5));
L_8181DDB0:;
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181DD9C; }
    R(4) = R(3) |R(3);
    { uint32_t ea_ = R(4) + 1808; R(5) = ld32(base, ea_); R(4) = ea_; }
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8181DDE8; }
    ctx->ctr = R(5);
    R(5) = (0 + 1);
L_8181DDCC:;
    { uint32_t ea_ = R(4) + 4; R(6) = ld32(base, ea_); R(4) = ea_; }
    st8(base, (R(6) + 664), R(5));
    R(6) = ld32(base, (R(4) + 32));
    R(7) = ld32(base, (R(4) + 64));
    st8(base, (R(6) + 672), R(5));
    st8(base, (R(7) + 620), R(5));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8181DDCC; }
L_8181DDE8:;
    R(4) = (0 + 0);
    st16(base, (R(3) + 1671), R(4));
}

/* mfn_8181DE64 (mfn_8181DE64, 36 bytes) */
static void mj_mfn_8181DE64_1de64(GM_CTX) {
    GM_FN(0x8181DE64); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (R(3) + 24);
    GM_CALLV(0x8181DE78u, 0x8015FAE0u, 0);
    R(0) = lr;
}

/* mfn_8181DF18 (mfn_8181DF18, 92 bytes) */
static void mj_mfn_8181DF18_1df18(GM_CTX) {
    GM_FN(0x8181DF18); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(4) + 0));
    R(30) = R(4) |R(4);
    R(3) = ld32(base, (R(3) + 12));
    ctx->ctr = R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x8181DF48u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8181DF5C; }
    R(3) = (R(29) + 4);
    st32(base, (R(29) + 12), R(30));
L_8181DF5C:;
    R(0) = lr;
}

/* mfn_8181DF74 (mfn_8181DF74, 12 bytes) */
static void mj_mfn_8181DF74_1df74(GM_CTX) {
    R(3) = (0 + 0);
    st32(base, (R(4) + 0), R(3));
}

/* mfn_8181DFC0 (mfn_8181DFC0, 84 bytes) */
static void mj_mfn_8181DFC0_1dfc0(GM_CTX) {
    GM_FN(0x8181DFC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld32(base, (R(3) + 8));
    R(3) = ld32(base, (R(3) + 4));
    R(5) = ld32(base, (R(4) + 16));
    R(6) = ld32(base, (R(4) + 12));
    R(4) = ld32(base, (R(4) + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(3) = R(3) + R(6);
    if ((CR_BIT(ctx, 0))) { goto L_8181DFFC; }
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(5) = R(3) + R(5);
    R(5) = ld32(base, (R(5) + 96));
    R(4) = ld32(base, (R(5) + R(4)));
L_8181DFFC:;
    ctx->ctr = R(4);
    GM_CALLV(0x8181E004u, ctx->ctr, 0);
    R(0) = lr;
}

/* mfn_8181E014 (mfn_8181E014, 84 bytes) */
static void mj_mfn_8181E014_1e014(GM_CTX) {
    GM_FN(0x8181E014); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld32(base, (R(3) + 8));
    R(3) = ld32(base, (R(3) + 4));
    R(5) = ld32(base, (R(4) + 28));
    R(6) = ld32(base, (R(4) + 24));
    R(4) = ld32(base, (R(4) + 32));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(3) = R(3) + R(6);
    if ((CR_BIT(ctx, 0))) { goto L_8181E050; }
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(5) = R(3) + R(5);
    R(5) = ld32(base, (R(5) + 96));
    R(4) = ld32(base, (R(5) + R(4)));
L_8181E050:;
    ctx->ctr = R(4);
    GM_CALLV(0x8181E058u, ctx->ctr, 0);
    R(0) = lr;
}

/* mfn_8181E068 (mfn_8181E068, 84 bytes) */
static void mj_mfn_8181E068_1e068(GM_CTX) {
    GM_FN(0x8181E068); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld32(base, (R(3) + 8));
    R(3) = ld32(base, (R(3) + 4));
    R(5) = ld32(base, (R(4) + 40));
    R(6) = ld32(base, (R(4) + 36));
    R(4) = ld32(base, (R(4) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(3) = R(3) + R(6);
    if ((CR_BIT(ctx, 0))) { goto L_8181E0A4; }
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(5) = R(3) + R(5);
    R(5) = ld32(base, (R(5) + 96));
    R(4) = ld32(base, (R(5) + R(4)));
L_8181E0A4:;
    ctx->ctr = R(4);
    GM_CALLV(0x8181E0ACu, ctx->ctr, 0);
    R(0) = lr;
}

/* mod_fn_2_3E670 (mod_fn_2_3E670, 56 bytes) */
static void mj_mod_fn_2_3E670_1e1f4(GM_CTX) {
    GM_FN(0x8181E1F4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 688);
    GM_CALLV(0x8181E20Cu, 0x801628C0u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8181E214u, 0x807ABE50u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_74F70 (mod_fn_2_74F70, 372 bytes) */
static void mj_mod_fn_2_74F70_23708(GM_CTX) {
    GM_FN(0x81823708); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(30) = R(3) |R(3);
    R(3) = (0 + 255);
    st8(base, (R(30) + 909), R(3));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24120));
    R(4) = ld32(base, (R(4) + -24708));
    R(7) = ld32(base, (R(30) + 4));
    R(5) = ld8(base, (R(3) + 4620));
    R(6) = ld8(base, (R(3) + 4621));
    R(27) = R(7) & 0x1u;
    R(28) = (R(4) + 8);
    R(4) = R(27) |R(27);
    R(29) = ld8(base, (R(3) + 4622));
    R(3) = R(28) |R(28);
    GM_CALLV(0x81823768u, 0x8008F000u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81823784; }
    R(3) = R(28) |R(28);
    R(4) = R(27) |R(27);
    GM_CALLV(0x8182377Cu, 0x8008F070u, 0);
    st8(base, (R(30) + 909), R(3));
    goto L_818237B8;
L_81823784:;
    R(3) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(30) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = R(29) |R(29);
    R(3) = ld32(base, (R(3) + -24784));
    { uint32_t ea_ = (R(30) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x8182379Cu, 0x800B0FD0u, 0);
    R(4) = (R(3) + -2);
    R(4) = R(4) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(4), 0x6u);
    if ((CR_BIT(ctx, 1))) { goto L_818237B4; }
    st8(base, (R(30) + 909), R(3));
    goto L_818237C0;
L_818237B4:;
    R(3) = ld8(base, (R(30) + 909));
L_818237B8:;
    R(4) = (int8_t)R(3);
    CR0(ctx, R(4));
    if ((CR_BIT(ctx, 0))) { goto L_81823828; }
L_818237C0:;
    R(4) = (0 + 0x81860000u);
    R(3) = rotl32(R(3), 2) & 0x3FCu;
    R(4) = (R(4) + -5828);
    R(3) = ld32(base, (R(4) + R(3)));
    GM_CALLV(0x818237D4u, 0x81806AB8u, 0);
    R(3) = (R(3) + 1);
    R(4) = (0 + 0x43300000u);
    R(3) = (R(3) + 0x80000000u);
    st32(base, (f + 8), R(4));
    R(4) = (0 + 0x81850000u);
    st32(base, (f + 12), R(3));
    R(3) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(4) + -31040); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[2].u = ld64(base, ea_); }
    R(4) = ld8(base, (R(30) + 909));
    R(3) = ld32(base, (R(3) + -24784));
    ctx->f[0].d = ctx->f[2].d - ctx->f[0].d;
    { uint32_t ea_ = (R(30) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (int8_t)R(4);
    { uint32_t ea_ = (R(30) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (R(4) + 1);
    R(5) = R(4) & 0xFFFFu;
    R(4) = R(29) |R(29);
    ctx->f[31].d = frsp(ctx->f[0].d);
    GM_CALLV(0x81823824u, 0x800B1100u, 0);
    goto L_81823830;
L_81823828:;
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31116); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
L_81823830:;
    R(4) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(4) + -31116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(30) + 1008);
    R(30) = (R(30) + 1132);
    R(4) = R(30) |R(30);
    GM_CALLV(0x81823848u, 0x80169F80u, 0);
    R(3) = R(30) |R(30);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = (0 + 0);
    GM_CALLV(0x81823858u, 0x80166EF0u, 0);
    R(0) = lr;
}

/* mod_fn_2_C2EF0 (mod_fn_2_C2EF0, 84 bytes) */
static void mj_mod_fn_2_C2EF0_23c84(GM_CTX) {
    GM_FN(0x81823C84); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 152);
    GM_CALLV(0x81823C9Cu, 0x801628C0u, 0);
    R(4) = (0 + 0);
    R(5) = (0 + 152);
    R(30) = R(3) |R(3);
    GM_CALLV(0x81823CACu, 0x81844D68u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81823CB4u, 0x81808310u, 0);
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 12340);
    st32(base, (R(30) + 96), R(4));
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_C2F40 (mod_fn_2_C2F40, 40 bytes) */
static void mj_mod_fn_2_C2F40_23cd8(GM_CTX) {
    R(5) = (0 + 8);
    R(4) = (R(3) + 108);
    R(3) = (R(3) + 143);
    ctx->ctr = R(5);
    R(5) = (0 + 0);
L_81823CEC:;
    { uint32_t ea_ = R(3) + 1; st8(base, ea_, R(5)); R(3) = ea_; }
    { uint32_t ea_ = R(4) + 4; st32(base, ea_, R(5)); R(4) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81823CEC; }
    R(3) = (0 + 1);
}

/* mod_fn_2_C2F80 (mod_fn_2_C2F80, 848 bytes) */
static void mj_mod_fn_2_C2F80_23d00(GM_CTX) {
    GM_FN(0x81823D00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = (0 + -1);
    GM_CALLV(0x81823D28u, 0x800B3B50u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81823E18; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23488));
    R(4) = ld32(base, (R(3) + 0));
    R(4) = ld32(base, (R(4) + 16));
    ctx->ctr = R(4);
    GM_CALLV(0x81823D48u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81823D90; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24456));
    GM_CALLV(0x81823D5Cu, 0x800E4010u, 0);
    GM_CALLV(0x81823D60u, 0x8008DED0u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25152));
    GM_CALLV(0x81823D6Cu, 0x80076BC0u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25280));
    GM_CALLV(0x81823D78u, 0x80066F70u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25208));
    GM_CALLV(0x81823D84u, 0x8006C1C0u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24368));
    GM_CALLV(0x81823D90u, 0x800E7530u, 0);
L_81823D90:;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24856));
    GM_CALLV(0x81823D9Cu, 0x800923D0u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25264));
    GM_CALLV(0x81823DA8u, 0x800691B0u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24464));
    GM_CALLV(0x81823DB4u, 0x800E3930u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24640));
    GM_CALLV(0x81823DC0u, 0x800D0270u, 0);
    GM_CALLV(0x81823DC4u, 0x80060970u, 0);
    GM_CALLV(0x81823DC8u, 0x8008C9E0u, 0);
    GM_CALLV(0x81823DCCu, 0x80080630u, 0);
    GM_CALLV(0x81823DD0u, 0x80060A10u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25280));
    GM_CALLV(0x81823DDCu, 0x80066EC0u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -25272));
    GM_CALLV(0x81823DE8u, 0x80068620u, 0);
    R(29) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(29) + -24816));
    R(4) = (0 + 0);
    st32(base, (R(3) + 312), R(4));
    GM_CALLV(0x81823DFCu, 0x800A7D30u, 0);
    R(3) = ld32(base, (R(29) + -24816));
    R(4) = ld32(base, (R(3) + 372));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81823E14; }
    R(4) = (R(4) + -1);
    st32(base, (R(3) + 372), R(4));
L_81823E14:;
    GM_CALLV(0x81823E18u, 0x8005F5C0u, 0);
L_81823E18:;
    R(3) = (0 + 0x80430000u);
    R(3) = ld8(base, (R(3) + -25350));
    R(3) = R(3) & 0x2u;
    CR0(ctx, R(3));
    R(3) = (0 + 0x80430000u);
    R(28) = ld32(base, (R(3) + -24752));
    if ((CR_BIT(ctx, 2))) { goto L_81823EBC; }
    R(27) = (0 + 8);
    R(29) = (0 + 0);
L_81823E38:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x81823E40u, 0x8005F900u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81823E60; }
    R(4) = ld32(base, (R(3) + 96));
    R(4) = ld32(base, (R(4) + 288));
    ctx->ctr = R(4);
    GM_CALLV(0x81823E58u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81823E74; }
L_81823E60:;
    R(27) = (R(27) + -1);
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    R(29) = (R(29) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81823E38; }
    goto L_81823EBC;
L_81823E74:;
    R(4) = (0 + 8);
    R(3) = (R(30) + 108);
    R(6) = (R(30) + 143);
    ctx->ctr = R(4);
    R(4) = (0 + 1);
    R(5) = R(28) |R(28);
L_81823E8C:;
    { uint32_t ea_ = R(5) + 4; R(7) = ld32(base, ea_); R(5) = ea_; }
    { uint32_t ea_ = R(3) + 4; R(8) = ld32(base, ea_); R(3) = ea_; }
    R(9) = ld32(base, (R(7) + 28));
    R(10) = ld8(base, (R(7) + 140));
    R(7) = (R(6) + 1);
    R(8) = R(8) |R(9);
    st32(base, (R(3) + 0), R(8));
    cr_cmp_u(ctx, 0, R(10), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81823EB4; }
    st8(base, (R(6) + 1), R(4));
L_81823EB4:;
    R(6) = R(7) |R(7);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81823E8C; }
L_81823EBC:;
    R(3) = (0 + -1);
    GM_CALLV(0x81823EC4u, 0x800B3B50u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81823F28; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld8(base, (R(3) + -25350));
    R(3) = R(3) & 0x2u;
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81823F28; }
    R(4) = (0 + 8);
    R(3) = (R(30) + 108);
    R(5) = (R(30) + 143);
    ctx->ctr = R(4);
    R(4) = (0 + 0);
L_81823EF0:;
    { uint32_t ea_ = R(3) + 4; R(7) = ld32(base, ea_); R(3) = ea_; }
    { uint32_t ea_ = R(28) + 4; R(6) = ld32(base, ea_); R(28) = ea_; }
    cr_cmp_u(ctx, 0, R(7), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81823F10; }
    R(8) = ld32(base, (R(6) + 20));
    R(7) = R(8) &R(7);
    st32(base, (R(6) + 48), R(7));
    st32(base, (R(3) + 0), R(4));
L_81823F10:;
    R(7) = ld8(base, (R(5) + 1));
    st8(base, (R(6) + 141), R(7));
    R(6) = (R(5) + 1);
    st8(base, (R(5) + 1), R(4));
    R(5) = R(6) |R(6);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81823EF0; }
L_81823F28:;
    R(30) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(30) + -24060));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23416));
    { uint32_t a_ = R(4); R(5) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(5) < a_; }
    { uint64_t t_ = (uint64_t)(~R(5)) + (R(4)) + ctx->xer_ca; R(4) = t_; ctx->xer_ca = (t_ >> 32); }
    GM_CALLV(0x81823F44u, 0x80196E90u, 0);
    GM_CALLV(0x81823F48u, 0x801021B0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81823FD0; }
    R(3) = ld32(base, (R(30) + -24060));
    R(4) = (0 + 0x80430000u);
    R(5) = ld8(base, (R(4) + -24028));
    R(3) = R(3) & 0xFFFFFFFDu;
    CR0(ctx, R(3));
    R(3) = R(5) & 0xFEu;
    st8(base, (R(4) + -24028), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81823FD0; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld8(base, (R(3) + -24026));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81823FD0; }
    R(3) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(3) + -23840));
    R(5) = (0 + 0x80430000u);
    R(6) = (0 + 0);
    st32(base, (R(5) + -24060), R(6));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81823FA0; }
    R(4) = (R(4) + -1);
    st32(base, (R(3) + -23840), R(4));
L_81823FA0:;
    R(30) = (0 + 8);
    R(29) = (0 + 4);
    R(28) = (0 + 0x80430000u);
L_81823FAC:;
    R(3) = ld32(base, (R(28) + -24536));
    R(3) = ld32(base, (R(3) + R(29)));
    GM_CALLV(0x81823FB8u, 0x800DC990u, 0);
    R(30) = (R(30) + -1);
    cr_cmp_u(ctx, 0, R(30), 0x0u);
    R(29) = (R(29) + 4);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81823FAC; }
    R(3) = (0 + 1);
    GM_CALLV(0x81823FD0u, 0x801BE2F0u, 0);
L_81823FD0:;
    R(3) = (0 + -1);
    GM_CALLV(0x81823FD8u, 0x800B3B50u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81824020; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld8(base, (R(3) + -25350));
    R(3) = R(3) & 0xFu;
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81824020; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23488));
    R(4) = ld32(base, (R(3) + 0));
    R(4) = ld32(base, (R(4) + 16));
    ctx->ctr = R(4);
    GM_CALLV(0x81824008u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81824020; }
    R(3) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(3) + -24064));
    R(4) = (R(4) + 1);
    st32(base, (R(3) + -24064), R(4));
L_81824020:;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24616));
    GM_CALLV(0x8182402Cu, 0x800D1260u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* mfn_81824050 (mfn_81824050, 80 bytes) */
static void mj_mfn_81824050_24050(GM_CTX) {
    GM_FN(0x81824050); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x81824074u, 0x818083A4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81824084; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81824084u, 0x80162920u, 0);
L_81824084:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mfn_81824194 (mfn_81824194, 4 bytes) */
static void mj_mfn_81824194_24194(GM_CTX) {

}

/* mod_fn_2_CE880 (mod_fn_2_CE880, 56 bytes) */
static void mj_mod_fn_2_CE880_24198(GM_CTX) {
    GM_FN(0x81824198); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 1672);
    GM_CALLV(0x818241B0u, 0x801628C0u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x818241B8u, 0x818241D0u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mfn_818241D0 (mfn_818241D0, 200 bytes) */
static void mj_mfn_818241D0_241d0(GM_CTX) {
    GM_FN(0x818241D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x818241ECu, 0x80066FC0u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 7288);
    st32(base, (R(30) + 96), R(3));
    R(3) = (R(30) + 976);
    GM_CALLV(0x81824200u, 0x800DB130u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 12468);
    st32(base, (R(30) + 96), R(3));
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 12420);
    st32(base, (R(30) + 1108), R(3));
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 12444);
    R(29) = (0 + 0);
    st32(base, (R(30) + 1116), R(3));
    R(3) = (R(30) + 1128);
    st32(base, (R(30) + 1112), R(30));
    st32(base, (R(30) + 1120), R(30));
    st32(base, (R(30) + 1104), R(29));
    GM_CALLV(0x8182423Cu, 0x80069020u, 0);
    R(3) = (R(30) + 1160);
    st32(base, (R(30) + 1156), R(29));
    GM_CALLV(0x81824248u, 0x80169CD0u, 0);
    R(3) = (R(30) + 1224);
    GM_CALLV(0x81824250u, 0x80169CD0u, 0);
    R(3) = (R(30) + 1288);
    GM_CALLV(0x81824258u, 0x80169CD0u, 0);
    R(3) = (R(30) + 1352);
    GM_CALLV(0x81824260u, 0x800D54A0u, 0);
    R(3) = (R(30) + 1408);
    GM_CALLV(0x81824268u, 0x80836C20u, 0);
    R(3) = (R(30) + 1452);
    GM_CALLV(0x81824270u, 0x80836C20u, 0);
    R(3) = (0 + 0x80960000u);
    R(4) = (R(3) + 31992);
    st32(base, (R(30) + 96), R(4));
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_CFBE0 (mod_fn_2_CFBE0, 328 bytes) */
static void mj_mod_fn_2_CFBE0_24318(GM_CTX) {
    GM_FN(0x81824318); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = (0 + 0);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    st32(base, (f + 20), R(3));
    R(28) = ld32(base, (R(30) + 992));
    st32(base, (f + 12), R(29));
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    st32(base, (f + 8), R(29));
    if ((CR_BIT(ctx, 2))) { goto L_818243B8; }
    R(27) = (f + 8);
    R(26) = (0 + 1);
L_81824368:;
    R(3) = ld32(base, (R(28) + 4));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818243AC; }
    R(4) = ld16(base, (R(3) + 8));
    R(4) = (R(4) + -15);
    R(4) = R(4) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(4), 0xFFFEu);
    if ((CR_BIT(ctx, 0))) { goto L_818243AC; }
    R(4) = ld32(base, (R(3) + 96));
    R(4) = ld32(base, (R(4) + 108));
    ctx->ctr = R(4);
    GM_CALLV(0x81824398u, ctx->ctr, 0);
    R(3) = ld8(base, (R(3) + 0));
    cr_cmp_u(ctx, 0, R(3), 0xFFu);
    if ((CR_BIT(ctx, 2))) { goto L_818243AC; }
    R(3) = (int8_t)R(3);
    st8(base, (R(27) + R(3)), R(26));
L_818243AC:;
    R(28) = ld32(base, (R(28) + 12));
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81824368; }
L_818243B8:;
    R(3) = (R(30) + 1636);
    R(4) = (f + 7);
    R(5) = (0 + 0);
L_818243C4:;
    R(8) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(6) = R(4) + R(5);
    { uint32_t a_ = R(5); R(9) = 0x8u - a_; ctx->xer_ca = 0x8u >= a_; }
    R(7) = R(30) + R(8);
    R(8) = R(3) + R(8);
    ctx->ctr = R(9);
L_818243DC:;
    { uint32_t ea_ = R(6) + 1; R(9) = ld8(base, ea_); R(6) = ea_; }
    { uint32_t ea_ = R(8) + 4; R(10) = ld32(base, ea_); R(8) = ea_; }
    cr_cmp_u(ctx, 0, R(10), R(9));
    if ((!CR_BIT(ctx, 2))) { goto L_818243FC; }
    R(5) = (R(5) + 1);
    R(7) = (R(7) + 4);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818243DC; }
    goto L_81824414;
L_818243FC:;
    R(5) = (R(5) + 1);
    cr_cmp_u(ctx, 0, R(5), 0x8u);
    R(29) = (0 + 1);
    st32(base, (R(7) + 1640), R(9));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818243C4; }
    goto L_8182441C;
L_81824414:;
    R(3) = R(29) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81824424; }
L_8182441C:;
    R(3) = ld16(base, (R(30) + 1510));
    st16(base, (R(30) + 1496), R(3));
L_81824424:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 20));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8182445C; }
    R(0) = lr;
    return;
L_8182445C:;
    GM_CALLV(0x81824460u, 0x81844FCCu, 0);
}

/* mod_fn_2_100ED0 (mod_fn_2_100ED0, 68 bytes) */
static void mj_mod_fn_2_100ED0_2661c(GM_CTX) {
    GM_FN(0x8182661C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 1120);
    GM_CALLV(0x81826634u, 0x801628C0u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8182663Cu, 0x80066FC0u, 0);
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 12904);
    st32(base, (R(30) + 96), R(4));
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_101120 (mod_fn_2_101120, 8 bytes) */
static void mj_mod_fn_2_101120_26660(GM_CTX) {
    R(3) = (0 + 1);
}

/* mod_fn_2_101130 (mod_fn_2_101130, 252 bytes) */
static void mj_mod_fn_2_101130_26668(GM_CTX) {
    GM_FN(0x81826668); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = ld32(base, (R(4) + 4));
    R(4) = ld8(base, (R(30) + 908));
    R(4) = (R(4) + -3);
    R(4) = R(4) & 0xFFu;
    cr_cmp_u(ctx, 0, R(4), 0xFEu);
    if ((CR_BIT(ctx, 0))) { goto L_81826744; }
    cr_cmp_u(ctx, 0, R(30), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81826744; }
    R(28) = ld32(base, (R(30) + 96));
    R(29) = ld32(base, (R(3) + 4));
    R(3) = ld32(base, (R(28) + 224));
    ctx->ctr = R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x818266BCu, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81826744; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x818266CCu, 0x8004DD00u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81826744; }
    R(3) = ld32(base, (R(28) + 108));
    ctx->ctr = R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x818266E4u, ctx->ctr, 0);
    R(3) = ld8(base, (R(3) + 0));
    R(28) = (int8_t)R(3);
    R(27) = R(29) + R(28);
    R(3) = ld8(base, (R(27) + 1108));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81826744; }
    R(3) = ld16(base, (R(29) + 1016));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182671C; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 51);
    GM_CALLV(0x81826714u, 0x80056CF0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81826744; }
L_8182671C:;
    R(3) = rotl32(R(28), 1) & 0xFFFFFFFEu;
    R(5) = (0 + 10);
    R(3) = R(29) + R(3);
    R(4) = (0 + 1);
    st16(base, (R(3) + 1076), R(5));
    R(5) = rotl32(R(28), 2) & 0xFFFFFFFCu;
    st16(base, (R(3) + 1092), R(4));
    R(3) = R(29) + R(5);
    st8(base, (R(27) + 1108), R(4));
    st32(base, (R(3) + 1044), R(30));
L_81826744:;
    R(0) = lr;
}

/* mod_fn_2_101270 (mod_fn_2_101270, 416 bytes) */
static void mj_mod_fn_2_101270_26764(GM_CTX) {
    GM_FN(0x81826764); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(4) = (0 + 0x80430000u);
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(4) + -25452));
    R(0) = ld32(base, (R(4) + 88));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818268E4; }
    R(0) = ld16(base, (R(3) + 852));
    R(6) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818267D8; }
    R(4) = (0 + 0x80430000u);
    R(0) = ld32(base, (R(3) + 856));
    R(5) = ld32(base, (R(4) + -24456));
    R(3) = ld32(base, (R(3) + 860));
    R(4) = ld32(base, (R(5) + 0));
    R(5) = ld32(base, (R(5) + 4));
    R(0) = R(4) &R(0);
    R(3) = R(5) &R(3);
    R(0) = R(3) |R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_818267DC; }
    R(6) = (0 + 1);
    goto L_818267DC;
L_818267D8:;
    R(6) = (0 + 1);
L_818267DC:;
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818268E4; }
    R(3) = (0 + 0x80940000u);
    R(25) = R(31) |R(31);
    { uint32_t ea_ = (R(3) + -25672); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(23) = (0 + 0);
    R(26) = (0 + 0x80430000u);
    R(27) = (0 + 0x80430000u);
    R(28) = (0 + 0x80970000u);
    R(29) = (0 + 1);
    R(30) = (0 + 0);
L_81826808:;
    R(24) = R(31) + R(23);
    R(0) = ld8(base, (R(24) + 1108));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_818268D4; }
    R(0) = ld8(base, (R(31) + 1043));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818268A8; }
    R(3) = ld32(base, (R(26) + -24640));
    R(0) = ld8(base, (R(3) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818268E4; }
    R(3) = R(23) |R(23);
    GM_CALLV(0x8182683Cu, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(22) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_818268D4; }
    GM_CALLV(0x8182684Cu, 0x80051E70u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818268D4; }
    R(3) = ld32(base, (R(27) + -25452));
    R(0) = ld32(base, (R(3) + 128));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_8182687C; }
    st32(base, (R(3) + 128), R(23));
    R(3) = (0 + 3);
    R(4) = (0 + 0);
    R(5) = (0 + 2);
    R(6) = (0 + 5);
    GM_CALLV(0x8182687Cu, 0x80102260u, 0);
L_8182687C:;
    { uint32_t ea_ = (R(31) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(22) |R(22);
    R(4) = (f + 8);
    R(5) = (R(28) + 5524);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[31].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81826898u, 0x80052080u, 0);
    R(3) = ld32(base, (R(27) + -25452));
    st32(base, (R(3) + 92), R(29));
    st8(base, (R(24) + 1108), R(30));
    goto L_818268D4;
L_818268A8:;
    R(0) = ld32(base, (R(25) + 1044));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818268D4; }
    R(3) = R(23) |R(23);
    GM_CALLV(0x818268BCu, 0x8005FB90u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818268D4; }
    R(4) = ld8(base, (R(31) + 1042));
    R(5) = (0 + 10);
    R(6) = ld32(base, (R(31) + 1008));
    GM_CALLV(0x818268D4u, 0x80052EF0u, 0);
L_818268D4:;
    R(23) = (R(23) + 1);
    R(25) = (R(25) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(23), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81826808; }
L_818268E4:;
    R(11) = (f + 64);
    R(0) = lr;
}

/* mod_fn_2_101410 (mod_fn_2_101410, 80 bytes) */
static void mj_mod_fn_2_101410_26904(GM_CTX) {
    GM_FN(0x81826904); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x81826928u, 0x800671B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81826938; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81826938u, 0x80162920u, 0);
L_81826938:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_101700 (mod_fn_2_101700, 476 bytes) */
static void mj_mod_fn_2_101700_26954(GM_CTX) {
    GM_FN(0x81826954); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81850000u);
    R(3) = ld32(base, (R(3) + 13128));
    GM_CALLV(0x81826978u, 0x801628C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(29) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_81826B10; }
    GM_CALLV(0x81826988u, 0x80066FC0u, 0);
    R(4) = (0 + 0x80300000u);
    R(3) = (R(29) + 976);
    R(4) = (R(4) + 29632);
    st32(base, (R(29) + 96), R(4));
    GM_CALLV(0x8182699Cu, 0x800DB130u, 0);
    R(4) = (0 + 0x80970000u);
    R(3) = (R(29) + 1112);
    R(4) = (R(4) + 6052);
    st32(base, (R(29) + 96), R(4));
    GM_CALLV(0x818269B0u, 0x80069020u, 0);
    R(30) = (0 + 0);
    st32(base, (R(29) + 1140), R(30));
    R(3) = (R(29) + 1144);
    GM_CALLV(0x818269C0u, 0x80169CD0u, 0);
    R(31) = (0 + 0x80330000u);
    R(3) = (R(29) + 1220);
    R(31) = (R(31) + -27176);
    st32(base, (R(29) + 1208), R(31));
    st32(base, (R(29) + 1212), R(30));
    st32(base, (R(29) + 1216), R(30));
    GM_CALLV(0x818269DCu, 0x8016A5E0u, 0);
    R(3) = (0 + 0x80330000u);
    R(3) = (R(3) + -27320);
    st32(base, (R(29) + 1208), R(3));
    R(3) = (R(29) + 1264);
    st32(base, (R(29) + 1248), R(30));
    st32(base, (R(29) + 1252), R(31));
    st32(base, (R(29) + 1256), R(30));
    st32(base, (R(29) + 1260), R(30));
    GM_CALLV(0x81826A00u, 0x8016A5E0u, 0);
    R(3) = (0 + 0x80330000u);
    R(3) = (R(3) + -27272);
    st32(base, (R(29) + 1252), R(3));
    R(3) = (R(29) + 1308);
    st32(base, (R(29) + 1292), R(30));
    st32(base, (R(29) + 1296), R(31));
    st32(base, (R(29) + 1300), R(30));
    st32(base, (R(29) + 1304), R(30));
    GM_CALLV(0x81826A24u, 0x8016A5E0u, 0);
    R(3) = (0 + 0x80330000u);
    R(3) = (R(3) + -27368);
    st32(base, (R(29) + 1296), R(3));
    R(3) = (R(29) + 1340);
    st32(base, (R(29) + 1336), R(30));
    GM_CALLV(0x81826A3Cu, 0x8016A740u, 0);
    R(4) = (0 + 0x80310000u);
    R(3) = (0 + 0x80940000u);
    R(4) = (R(4) + 30816);
    st32(base, (R(29) + 1368), R(4));
    { uint32_t ea_ = (R(3) + -25664); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x80870000u);
    { uint32_t ea_ = (R(29) + 1384); stfs(base, ea_, ctx->f[0].d); }
    R(5) = (0 + 0x80870000u);
    R(3) = (R(29) + 1396);
    R(4) = (R(4) + -3952);
    st32(base, (R(29) + 1388), R(30));
    R(5) = (R(5) + -3808);
    R(6) = (0 + 232);
    R(7) = (0 + 2);
    st32(base, (R(29) + 1392), R(30));
    GM_CALLV(0x81826A7Cu, 0x802DC9A0u, 0);
    R(4) = (0 + 0x80870000u);
    R(5) = (0 + 0x80870000u);
    R(3) = (R(29) + 1860);
    R(6) = (0 + 144);
    R(4) = (R(4) + -3680);
    R(5) = (R(5) + -3584);
    R(7) = (0 + 5);
    GM_CALLV(0x81826A9Cu, 0x802DC9A0u, 0);
    R(31) = (R(29) + 2652);
    R(3) = R(31) |R(31);
    GM_CALLV(0x81826AA8u, 0x802D7AA0u, 0);
    R(3) = (0 + 0x80330000u);
    R(4) = (0 + 0x800E0000u);
    R(3) = (R(3) + -26280);
    st32(base, (R(31) + 0), R(3));
    R(5) = (0 + 0x80800000u);
    R(4) = (R(4) + -19376);
    st32(base, (R(31) + 276), R(30));
    R(3) = (R(29) + 2948);
    R(5) = (R(5) + 8064);
    R(6) = (0 + 92);
    st32(base, (R(31) + 280), R(30));
    R(7) = (0 + 6);
    st8(base, (R(31) + 284), R(30));
    st8(base, (R(31) + 285), R(30));
    st32(base, (R(31) + 288), R(30));
    st32(base, (R(31) + 292), R(30));
    GM_CALLV(0x81826AECu, 0x802DC9A0u, 0);
    R(4) = (0 + 0x80970000u);
    R(3) = (0 + 0x80320000u);
    R(4) = (R(4) + 6280);
    st32(base, (R(29) + 3508), R(4));
    R(3) = (R(3) + -29320);
    st32(base, (R(29) + 3512), R(29));
    st32(base, (R(29) + 3516), R(3));
    st32(base, (R(29) + 3520), R(30));
    st8(base, (R(29) + 3564), R(30));
L_81826B10:;
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* mod_fn_2_103920 (mod_fn_2_103920, 276 bytes) */
static void mj_mod_fn_2_103920_26b30(GM_CTX) {
    GM_FN(0x81826B30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x81826B4Cu, 0x80870ED0u, 0);
    R(31) = R(3) |R(3);
    GM_CALLV(0x81826B54u, 0x8005FFB0u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81826B74; }
    cr_cmp_u(ctx, 0, R(31), 0x8u);
    if ((!CR_BIT(ctx, 0))) { goto L_81826BBC; }
    st8(base, (R(30) + 1072), R(31));
    goto L_81826BBC;
L_81826B74:;
    cr_cmp_u(ctx, 0, R(31), 0x8u);
    if ((!CR_BIT(ctx, 0))) { goto L_81826B84; }
    R(0) = (0 + 16);
    st8(base, (R(30) + 3599), R(0));
L_81826B84:;
    R(3) = R(30) |R(30);
    R(5) = R(31) |R(31);
    R(4) = (f + 8);
    GM_CALLV(0x81826B94u, 0x80870FD0u, 0);
    R(0) = ld8(base, (R(30) + 3592));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81826BA8; }
    R(0) = ld32(base, (f + 8));
    st8(base, (R(30) + 1072), R(0));
L_81826BA8:;
    R(3) = ld8(base, (R(30) + 3599));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81826BBC; }
    R(0) = (R(3) + -1);
    st8(base, (R(30) + 3599), R(0));
L_81826BBC:;
    R(0) = ld8(base, (R(30) + 1072));
    R(0) = (int8_t)R(0);
    cr_cmp_u(ctx, 0, R(0), 0x8u);
    if ((!CR_BIT(ctx, 0))) { goto L_81826C14; }
    R(3) = (0 + 0x80430000u);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(3) + -24752));
    R(3) = R(3) + R(0);
    R(3) = ld32(base, (R(3) + 4));
    GM_CALLV(0x81826BE4u, 0x800B5C50u, 0);
    R(0) = rotl32(R(3), 16) & 0xFFFFu;
    R(3) = (R(30) + 3588);
    R(4) = (int16_t)R(0);
    R(5) = (0 + 2048);
    R(12) = R(6) |R(6);
    R(11) = R(7) |R(7);
    R(6) = ld8(base, (R(30) + 1072));
    R(7) = (0 + 16384);
    GM_CALLV(0x81826C08u, 0x8180AB68u, 0);
    R(6) = R(12) |R(12);
    R(7) = R(11) |R(11);
    goto L_81826C2C;
L_81826C14:;
    R(3) = (R(30) + 3588);
    R(4) = (0 + 0);
    R(5) = (0 + 8);
    R(6) = (0 + 2048);
    R(7) = (0 + 8);
    GM_CALLV(0x81826C2Cu, 0x8015F200u, 0);
L_81826C2C:;
    R(0) = lr;
}

/* mod_fn_2_103CA0 (mod_fn_2_103CA0, 628 bytes) */
static void mj_mod_fn_2_103CA0_26c44(GM_CTX) {
    GM_FN(0x81826C44); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(22) = R(3) |R(3);
    R(4) = (R(3) + 3608);
    R(5) = (R(3) + 3616);
L_81826C6C:;
    R(3) = ld8(base, (R(4) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81826C80; }
    R(0) = (R(3) + -1);
    st8(base, (R(4) + 0), R(0));
L_81826C80:;
    R(4) = (R(4) + 1);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81826C6C; }
    R(3) = (f + 8);
    R(4) = (0 + 0);
    R(5) = (0 + 5);
    GM_CALLV(0x81826C9Cu, 0x80160AD0u, 0);
    R(3) = (0 + 0x80940000u);
    R(27) = (R(22) + 2948);
    { uint32_t ea_ = (R(3) + -25484); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(26) = (R(22) + 3500);
    R(31) = (f + 8);
    R(28) = (0 + 0);
    R(29) = (0 + 1);
    R(30) = (0 + 0x80940000u);
    R(21) = (0 + 4);
L_81826CC0:;
    R(25) = ld32(base, (R(27) + 16));
    goto L_81826E3C;
L_81826CC8:;
    R(20) = ld32(base, (R(25) + 4));
    R(24) = (0 + 0);
    R(0) = ld8(base, (R(20) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81826D40; }
    R(12) = ld32(base, (R(20) + 96));
    R(3) = R(20) |R(20);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81826CF0u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    cr_cmp_u(ctx, 0, R(0), 0x8u);
    if ((!CR_BIT(ctx, 0))) { goto L_81826D78; }
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(29) << s_; }
    R(24) = R(20) |R(20);
    R(3) = R(20) |R(20);
    R(28) = R(28) |R(0);
    GM_CALLV(0x81826D10u, 0x8012DBE0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81826D78; }
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81826D28u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((!CR_BIT(ctx, 0))) { goto L_81826D78; }
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(29) << s_; }
    R(28) = R(28) |R(0);
    goto L_81826D78;
L_81826D40:;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_81826D78; }
    R(12) = ld32(base, (R(20) + 96));
    R(3) = R(20) |R(20);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81826D5Cu, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(0) = (int8_t)R(0);
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((!CR_BIT(ctx, 0))) { goto L_81826D78; }
    { uint32_t s_ = R(0) & 63; R(0) = s_ > 31 ? 0 : R(29) << s_; }
    R(24) = R(20) |R(20);
    R(28) = R(28) |R(0);
L_81826D78:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81826E38; }
    { uint32_t ea_ = (R(24) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(23) = (0 + 0);
    { uint32_t ea_ = (R(22) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + -25488); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
L_81826D94:;
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    R(0) = ctx->cr;
    R(0) = rotl32(R(0), 1) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81826DB8; }
    R(3) = ld8(base, (R(31) + R(23)));
    R(0) = (R(3) + 1);
    st8(base, (R(31) + R(23)), R(0));
    goto L_81826DC4;
L_81826DB8:;
    R(23) = (R(23) + 1);
    cr_cmp_u(ctx, 0, R(23), 0x4u);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81826D94; }
L_81826DC4:;
    cr_cmp_u(ctx, 0, R(23), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_81826DD8; }
    R(3) = ld8(base, (R(31) + R(23)));
    R(0) = (R(3) + 1);
    st8(base, (R(31) + R(23)), R(0));
L_81826DD8:;
    R(0) = ld8(base, (R(24) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81826E38; }
    R(12) = ld32(base, (R(24) + 96));
    R(3) = R(24) |R(24);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81826DF8u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    cr_cmp_u(ctx, 0, R(0), 0x8u);
    if ((!CR_BIT(ctx, 0))) { goto L_81826E38; }
    R(20) = R(22) + R(0);
    R(0) = ld8(base, (R(20) + 3608));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81826E38; }
    R(3) = R(24) |R(24);
    R(4) = (0 + 28);
    GM_CALLV(0x81826E20u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81826E38; }
    R(3) = R(22) |R(22);
    R(4) = R(23) |R(23);
    GM_CALLV(0x81826E34u, 0x80870530u, 0);
    st8(base, (R(20) + 3608), R(21));
L_81826E38:;
    R(25) = ld32(base, (R(25) + 12));
L_81826E3C:;
    cr_cmp_s(ctx, 0, (int32_t)R(25), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81826CC8; }
    R(27) = (R(27) + 92);
    cr_cmp_u(ctx, 0, R(27), R(26));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81826CC0; }
    R(3) = (R(22) + 1860);
    R(4) = (f + 8);
    R(5) = (f + 13);
L_81826E5C:;
    R(0) = ld8(base, (R(4) + 0));
    R(4) = (R(4) + 1);
    cr_cmp_u(ctx, 0, R(4), R(5));
    st8(base, (R(3) + 58), R(0));
    R(3) = (R(3) + 144);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81826E5C; }
    st8(base, (R(22) + 3601), R(28));
    R(3) = (0 + 0);
    R(4) = (0 + 0);
L_81826E80:;
    R(4) = (R(4) + 1);
    R(0) = R(28) & 0x1u;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 8);
    R(28) = rotl32(R(28), 31) & 0x7FFFFFFFu;
    R(3) = R(3) + R(0);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81826E80; }
    R(11) = (f + 64);
    R(0) = lr;
}

/* mfn_81826EB8 (mfn_81826EB8, 8 bytes) */
static void mj_mfn_81826EB8_26eb8(GM_CTX) {
    R(3) = (0 + 9360);
}

/* mod_fn_2_108940 (mod_fn_2_108940, 252 bytes) */
static void mj_mod_fn_2_108940_26ec0(GM_CTX) {
    GM_FN(0x81826EC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    GM_CALLV(0x81826ED8u, 0x81826EB8u, 0);
    GM_CALLV(0x81826EDCu, 0x801628C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(26) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_81826FA0; }
    GM_CALLV(0x81826EECu, 0x8006C6D0u, 0);
    R(4) = (0 + 0x80970000u);
    R(3) = (R(26) + 296);
    R(4) = (R(4) + 10096);
    st32(base, (R(26) + 96), R(4));
    GM_CALLV(0x81826F00u, 0x80069020u, 0);
    R(25) = (R(26) + 324);
    R(3) = R(25) |R(25);
    GM_CALLV(0x81826F0Cu, 0x8016A010u, 0);
    R(27) = (0 + 0x80970000u);
    R(28) = (0 + 0x807C0000u);
    R(27) = (R(27) + 10192);
    R(29) = (0 + 0x80770000u);
    st32(base, (R(25) + 0), R(27));
    R(3) = (R(25) + 172);
    R(4) = (R(28) + -20976);
    R(5) = (R(29) + -3120);
    R(6) = (0 + 8);
    R(7) = (0 + 100);
    GM_CALLV(0x81826F38u, 0x802DC9A0u, 0);
    R(30) = (0 + 0x80770000u);
    R(31) = (0 + 0x80770000u);
    R(3) = (R(25) + 2972);
    R(6) = (0 + 12);
    R(4) = (R(30) + -2784);
    R(5) = (R(31) + -3184);
    R(7) = (0 + 100);
    GM_CALLV(0x81826F58u, 0x802DC9A0u, 0);
    R(25) = (R(26) + 4796);
    R(3) = R(25) |R(25);
    GM_CALLV(0x81826F64u, 0x8016A010u, 0);
    st32(base, (R(25) + 0), R(27));
    R(3) = (R(25) + 172);
    R(4) = (R(28) + -20976);
    R(5) = (R(29) + -3120);
    R(6) = (0 + 8);
    R(7) = (0 + 100);
    GM_CALLV(0x81826F80u, 0x802DC9A0u, 0);
    R(3) = (R(25) + 2972);
    R(4) = (R(30) + -2784);
    R(5) = (R(31) + -3184);
    R(6) = (0 + 12);
    R(7) = (0 + 100);
    GM_CALLV(0x81826F98u, 0x802DC9A0u, 0);
    R(0) = (0 + 0);
    st32(base, (R(26) + 9268), R(0));
L_81826FA0:;
    R(11) = (f + 48);
    R(3) = R(26) |R(26);
    R(0) = lr;
}

/* mod_fn_2_108EE0 (mod_fn_2_108EE0, 3168 bytes) */
static void mj_mod_fn_2_108EE0_26fbc(GM_CTX) {
    GM_FN(0x81826FBC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 352);
    R(4) = (0 + 0x80430000u);
    R(25) = (0 + 0x80940000u);
    R(15) = ld32(base, (R(4) + -25136));
    R(31) = R(3) |R(3);
    R(25) = (R(25) + -25048);
    R(3) = (0 + 0);
    GM_CALLV(0x8182707Cu, 0x8005F900u, 0);
    R(3) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(25) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = ld32(base, (R(3) + -25088));
    R(3) = (R(15) + 0x90000u);
    { uint32_t ea_ = (R(25) + 16); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 64); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 60); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[1].d - ctx->f[3].d);
    { uint32_t ea_ = (R(4) + 68); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[2].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[3].d + ctx->f[4].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[4].d - ctx->f[5].d);
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[3].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[28].d = ctx->ps1[28] = frsp(ctx->f[1].d - ctx->f[3].d);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld8(base, (R(3) + 280));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818270E8; }
    R(3) = (0 + 0x80430000u);
    R(0) = ld8(base, (R(3) + -25350));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_818270E8; }
    R(3) = (0 + 1);
    goto L_81827B74;
L_818270E8:;
    R(3) = (0 + -1);
    GM_CALLV(0x818270F0u, 0x800B3B50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81827100; }
    R(3) = (0 + 1);
    goto L_81827B74;
L_81827100:;
    R(15) = (R(31) + 9316);
    R(16) = (0 + 0);
L_81827108:;
    R(3) = R(16) |R(16);
    GM_CALLV(0x81827110u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81827174; }
    { uint32_t ea_ = (R(3) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 43);
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81827138u, 0x80056CF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182715C; }
    { uint32_t ea_ = (R(25) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(15) |R(15);
    { uint32_t ea_ = (R(25) + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 28); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x81827158u, 0x8015F140u, 0);
    goto L_81827174;
L_8182715C:;
    { uint32_t ea_ = (R(25) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(15) |R(15);
    { uint32_t ea_ = (R(25) + 32); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 36); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 40); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x81827174u, 0x8015F140u, 0);
L_81827174:;
    R(16) = (R(16) + 1);
    R(15) = (R(15) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(16), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_81827188; }
    R(15) = (R(15) + 12);
L_81827188:;
    cr_cmp_s(ctx, 0, (int32_t)R(16), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81827108; }
    R(3) = ld16(base, (R(31) + 9332));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 180), R(3));
    R(3) = ld8(base, (R(31) + 9292));
    st32(base, (f + 176), R(0));
    { uint32_t ea_ = (R(25) + 152); ctx->f[2].u = ld64(base, ea_); }
    cr_cmp_u(ctx, 0, R(3), 0x7u);
    { uint32_t ea_ = (f + 176); ctx->f[1].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(25) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 184); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 188));
    st16(base, (R(31) + 9332), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_81827810; }
    R(3) = (0 + 1);
    GM_CALLV(0x818271D8u, 0x8006A1D0u, 0);
    R(15) = R(3) & 0xFFu;
    R(3) = (0 + 1);
    GM_CALLV(0x818271E4u, 0x8006A200u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(15), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182720C; }
    R(0) = ld8(base, (R(31) + 9334));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81827204; }
    R(0) = (0 + 0);
    st8(base, (R(31) + 9334), R(0));
    goto L_8182720C;
L_81827204:;
    R(0) = (0 + 1);
    st8(base, (R(31) + 9334), R(0));
L_8182720C:;
    R(0) = ld8(base, (R(31) + 9334));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81827234; }
    { uint32_t ea_ = (R(25) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 9336);
    { uint32_t ea_ = (R(25) + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 48); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 52); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x81827230u, 0x8015F140u, 0);
    goto L_8182724C;
L_81827234:;
    { uint32_t ea_ = (R(25) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 9336);
    { uint32_t ea_ = (R(25) + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 48); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 52); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x8182724Cu, 0x8015F140u, 0);
L_8182724C:;
    R(0) = (0 + 0);
    st16(base, (R(31) + 9340), R(0));
    R(3) = (0 + 1);
    GM_CALLV(0x8182725Cu, 0x8006A200u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182726C; }
    R(0) = (0 + 1);
    st16(base, (R(31) + 9340), R(0));
L_8182726C:;
    { uint32_t ea_ = (R(25) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(22) = R(31) |R(31);
    { uint32_t ea_ = (f + 240); st64(base, ea_, ctx->f[0].u); }
    R(23) = R(31) |R(31);
    { uint32_t ea_ = (R(25) + 112); ctx->f[0].u = ld64(base, ea_); }
    R(20) = R(31) |R(31);
    { uint32_t ea_ = (f + 256); st64(base, ea_, ctx->f[0].u); }
    R(19) = R(31) |R(31);
    { uint32_t ea_ = (R(25) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(18) = (R(31) + 3296);
    { uint32_t ea_ = (f + 200); st64(base, ea_, ctx->f[0].u); }
    R(24) = (f + 12);
    { uint32_t ea_ = (R(25) + 80); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(16) = (0 + 0);
    { uint32_t ea_ = (f + 208); st64(base, ea_, ctx->f[0].u); }
    R(21) = (0 + 0);
    { uint32_t ea_ = (R(25) + 84); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(30) = (0 + 0x80430000u);
    { uint32_t ea_ = (f + 216); st64(base, ea_, ctx->f[0].u); }
    R(28) = (0 + 1);
    { uint32_t ea_ = (R(25) + 88); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(29) = (0 + 0);
    { uint32_t ea_ = (f + 224); st64(base, ea_, ctx->f[0].u); }
    R(26) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(25) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 232); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(25) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 248); st64(base, ea_, ctx->f[0].u); }
    { uint32_t ea_ = (R(25) + 124); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 4); ctx->f[24].d = ctx->ps1[24] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 100); ctx->f[21].d = ctx->ps1[21] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 24); ctx->f[20].d = ctx->ps1[20] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 104); ctx->f[19].d = ctx->ps1[19] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 32); ctx->f[18].d = ctx->ps1[18] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 68); ctx->f[17].d = ctx->ps1[17] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 8); ctx->f[16].d = ctx->ps1[16] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 76); ctx->f[15].d = ctx->ps1[15] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 60); ctx->f[25].d = ctx->ps1[25] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 28); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 72); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 264); st64(base, ea_, ctx->f[0].u); }
L_81827310:;
    R(3) = ld32(base, (R(26) + -25136));
    R(0) = (R(3) + 0x90000u);
    R(27) = R(0) + R(21);
    R(0) = ld8(base, (R(27) + -1736));
    cr_cmp_u(ctx, 0, R(0), 0xFFu);
    if ((CR_BIT(ctx, 2))) { goto L_81827794; }
    R(0) = ld32(base, (R(22) + 1296));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81827340; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_818273F8; }
    goto L_81827754;
L_81827340:;
    { uint32_t ea_ = (R(25) + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81827348u, 0x800B2F10u, 0);
    ctx->f[14].d = ctx->ps1[14] = frsp(ctx->f[25].d + ctx->f[1].d);
    { uint32_t ea_ = (R(25) + 32); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81827354u, 0x800B2F10u, 0);
    ctx->f[26].d = ctx->ps1[26] = frsp(ctx->f[17].d + ctx->f[1].d);
    { uint32_t ea_ = (R(25) + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81827360u, 0x800B2F10u, 0);
    ctx->f[27].d = ctx->ps1[27] = frsp(ctx->f[20].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[23].d * ctx->f[26].d);
    { uint32_t ea_ = (R(22) + 1696); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (R(22) + 2096); stfs(base, ea_, ctx->f[14].d); }
    { uint32_t ea_ = (R(22) + 2496); stfs(base, ea_, ctx->f[24].d); }
    { uint32_t ea_ = (R(22) + 2896); stfs(base, ea_, ctx->f[24].d); }
    { uint32_t ea_ = (R(23) + 496); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(23) + 500); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + -1744); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81827388u, 0x80101AA0u, 0);
    { uint32_t ea_ = (R(27) + -1744); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[22].d * ctx->f[26].d);
    ctx->f[1].d = frsp(ctx->f[1].d);
    R(3) = (0 + 0x10000u);
    { uint32_t ea_ = (R(27) + -1740); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(20) + 3296); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
    { uint32_t ea_ = (R(20) + 3300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(20) + 3304); stfs(base, ea_, ctx->f[16].d); }
    R(4) = ld32(base, (R(22) + 1296));
    R(0) = (R(4) + 1);
    st32(base, (R(22) + 1296), R(0));
    GM_CALLV(0x818273BCu, 0x800B2EE0u, 0);
    st16(base, (R(19) + 4496), R(3));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[15].d * ctx->f[26].d);
    { uint32_t ea_ = (f + 200); ctx->f[0].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(22) + 6168); stfs(base, ea_, ctx->f[27].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[26].d);
    { uint32_t ea_ = (R(22) + 6568); stfs(base, ea_, ctx->f[14].d); }
    { uint32_t ea_ = (R(22) + 6968); stfs(base, ea_, ctx->f[24].d); }
    { uint32_t ea_ = (R(22) + 7368); stfs(base, ea_, ctx->f[16].d); }
    { uint32_t ea_ = (R(23) + 4968); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(23) + 4972); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + -1740); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + -1744); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(20) + 7768); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(20) + 7772); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(20) + 7776); stfs(base, ea_, ctx->f[16].d); }
L_818273F8:;
    { uint32_t ea_ = (R(18) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) + R(16);
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(18) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(18) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + 4696), R(28));
    st8(base, (R(3) + 9168), R(28));
    { uint32_t ea_ = (f + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[31].d);
    if ((CR_BIT(ctx, 0))) { goto L_81827444; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[30].d);
    if ((CR_BIT(ctx, 1))) { goto L_81827444; }
    { uint32_t ea_ = (f + 72); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[29].d);
    if ((CR_BIT(ctx, 1))) { goto L_81827444; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[28].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81827450; }
L_81827444:;
    st8(base, (R(3) + 4696), R(29));
    st8(base, (R(3) + 9168), R(29));
    goto L_81827794;
L_81827450:;
    { uint32_t ea_ = (R(31) + 9336); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 128);
    { uint32_t ea_ = (R(22) + 2496); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d * ctx->f[16].d);
    { uint32_t ea_ = (f + 216); ctx->f[0].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(22) + 1696); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(25) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[2].d * ctx->f[3].d);
    R(5) = (int16_t)ld16(base, (R(19) + 4496));
    ctx->f[3].u = ctx->f[1].u;
    ctx->f[4].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 208); ctx->f[0].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 176); st64(base, ea_, ctx->f[4].u); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[5].d);
    { uint32_t ea_ = (R(25) + 28); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = ld32(base, (f + 180));
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 184); st64(base, ea_, ctx->f[0].u); }
    R(4) = ld32(base, (f + 188));
    R(5) = R(5) + R(4);
    R(5) = R(5) + R(0);
    st16(base, (R(19) + 4496), R(5));
    GM_CALLV(0x818274B0u, 0x801C0BD0u, 0);
    { uint32_t ea_ = (R(31) + 9336); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 128);
    { uint32_t ea_ = (f + 224); ctx->f[0].u = ld64(base, ea_); }
    R(4) = (f + 16);
    { uint32_t ea_ = (R(22) + 1696); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 192); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 196));
    st16(base, (f + 16), R(0));
    GM_CALLV(0x818274E0u, 0x8016EEF0u, 0);
    { uint32_t ea_ = (R(25) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 80);
    { uint32_t ea_ = (R(25) + 92); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[1].u;
    GM_CALLV(0x818274F4u, 0x801C0BD0u, 0);
    R(3) = (f + 128);
    R(4) = (f + 80);
    R(5) = R(3) |R(3);
    GM_CALLV(0x81827504u, 0x801C0540u, 0);
    R(3) = (f + 128);
    R(4) = (f + 44);
    GM_CALLV(0x81827510u, 0x8016F130u, 0);
    { uint32_t ea_ = (R(27) + -1744); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(17) = R(31) |R(31);
    { uint32_t ea_ = (f + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(15) = (0 + 0);
    { uint32_t ea_ = (f + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 76); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 4); ctx->f[14].d = ctx->ps1[14] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(27) + -1740); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(20) + 3296); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(20) + 3300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(20) + 3304); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(22) + 6968); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 232); ctx->f[0].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(31) + 9336); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(22) + 1696); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(22) + 6968); stfs(base, ea_, ctx->f[0].d); }
L_81827570:;
    R(3) = R(15) |R(15);
    GM_CALLV(0x81827578u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81827630; }
    { uint32_t ea_ = (R(3) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 72); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 76); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[1].d); }
    if ((CR_BIT(ctx, 0))) { goto L_81827630; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    R(3) = (f + 56);
    R(4) = (f + 68);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[21].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x818275C0u, 0x801C1650u, 0);
    GM_CALLV(0x818275C4u, 0x802BE470u, 0);
    { uint32_t ea_ = (R(17) + 9316); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81827630; }
    { uint32_t ea_ = (f + 72); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 56);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    R(4) = (f + 68);
    GM_CALLV(0x818275E4u, 0x801C1650u, 0);
    GM_CALLV(0x818275E8u, 0x802BE470u, 0);
    { uint32_t ea_ = (R(17) + 9316); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (int16_t)ld16(base, (R(31) + 9332));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d / ctx->f[0].d);
    st16(base, (f + 12), R(0));
    ctx->f[14].d = ctx->ps1[14] = frsp(ctx->f[20].d * ctx->f[0].d);
    ctx->f[14].d = ctx->ps1[14] = frsp(ctx->f[14].d + ctx->f[20].d);
    { uint32_t ea_ = (R(24) + 0); psq_l(ctx, base, 0, ea_, 1, 3); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[19].d * ctx->f[0].d);
    GM_CALLV(0x8182760Cu, 0x80237BD0u, 0);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[18].d * ctx->f[1].d);
    { uint32_t ea_ = (f + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[16].d - ctx->f[14].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[17].d + ctx->f[3].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    ctx->f[14].d = ctx->ps1[14] = frsp(ctx->f[2].d * ctx->f[3].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81827630; }
    ctx->f[14].u = ctx->f[14].u ^ 0x8000000000000000ull;
L_81827630:;
    R(15) = (R(15) + 1);
    R(17) = (R(17) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(15), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_81827644; }
    R(17) = (R(17) + 12);
L_81827644:;
    cr_cmp_s(ctx, 0, (int32_t)R(15), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81827570; }
    { uint32_t ea_ = (R(22) + 2496); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[24].d, ctx->f[14].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_81827734; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[24].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81827678; }
    cr_fcmp(ctx, 0, ctx->f[14].d, ctx->f[24].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81827688; }
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    goto L_81827688;
L_81827678:;
    cr_fcmp(ctx, 0, ctx->f[14].d, ctx->f[24].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81827688; }
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
L_81827688:;
    { uint32_t ea_ = (f + 240); ctx->f[0].u = ld64(base, ea_); }
    R(3) = (f + 24);
    { uint32_t ea_ = (R(25) + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[14].d);
    { uint32_t ea_ = (R(25) + 28); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 64); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x818276A4u, 0x8015F140u, 0);
    { uint32_t ea_ = (R(22) + 2896); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[24].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_8182774C; }
    { uint32_t ea_ = (f + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[16].d);
    if ((CR_BIT(ctx, 1))) { goto L_818276C8; }
    { uint32_t ea_ = (f + 248); ctx->f[0].u = ld64(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8182774C; }
L_818276C8:;
    { uint32_t ea_ = (f + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 76); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d + ctx->f[15].d);
    { uint32_t ea_ = (f + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 256); ctx->f[0].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 72); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[2].d); }
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81827714; }
    R(3) = ld32(base, (R(30) + -25280));
    R(4) = (f + 32);
    R(5) = (0 + 0);
    R(6) = (0 + 1);
    R(7) = (0 + 0);
    GM_CALLV(0x81827710u, 0x80066630u, 0);
    goto L_8182772C;
L_81827714:;
    R(3) = ld32(base, (R(30) + -25280));
    R(4) = (f + 32);
    R(5) = (0 + 1);
    R(6) = (0 + 1);
    R(7) = (0 + 0);
    GM_CALLV(0x8182772Cu, 0x80066630u, 0);
L_8182772C:;
    { uint32_t ea_ = (R(22) + 2896); stfs(base, ea_, ctx->f[16].d); }
    goto L_8182774C;
L_81827734:;
    { uint32_t ea_ = (R(25) + 120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[24].u;
    { uint32_t ea_ = (R(25) + 52); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (f + 24);
    ctx->f[3].u = ctx->f[2].u;
    GM_CALLV(0x8182774Cu, 0x8015F140u, 0);
L_8182774C:;
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(22) + 2496); stfs(base, ea_, ctx->f[0].d); }
L_81827754:;
    R(0) = (int16_t)ld16(base, (R(31) + 9340));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182776C; }
    { uint32_t ea_ = (f + 264); ctx->f[0].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(23) + 496); stfs(base, ea_, ctx->f[0].d); }
    goto L_81827794;
L_8182776C:;
    { uint32_t ea_ = (R(23) + 496); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 20);
    { uint32_t ea_ = (R(25) + 64); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[4].u = ctx->f[2].u;
    { uint32_t ea_ = (R(25) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(23) + 500); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x8182778Cu, 0x8015F140u, 0);
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(23) + 496); stfs(base, ea_, ctx->f[0].d); }
L_81827794:;
    R(16) = (R(16) + 1);
    R(22) = (R(22) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(16), 100);
    R(23) = (R(23) + 8);
    R(20) = (R(20) + 12);
    R(19) = (R(19) + 2);
    R(18) = (R(18) + 12);
    R(21) = (R(21) + 12);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81827310; }
    { uint32_t ea_ = (R(25) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 124);
    R(4) = (int16_t)ld16(base, (R(31) + 9308));
    ctx->f[2].u = ctx->f[1].u;
    { uint32_t ea_ = (R(31) + 180); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = (R(4) + 200);
    st16(base, (R(31) + 9308), R(0));
    GM_CALLV(0x818277D8u, 0x801C0BD0u, 0);
    R(3) = (R(31) + 324);
    R(4) = (R(31) + 124);
    GM_CALLV(0x818277E4u, 0x8016A170u, 0);
    { uint32_t ea_ = (R(31) + 180); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(31) + 124);
    { uint32_t ea_ = (R(25) + 128); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[2].d - ctx->f[0].d);
    ctx->f[2].u = ctx->f[1].u;
    GM_CALLV(0x81827800u, 0x801C0BD0u, 0);
    R(3) = (R(31) + 4796);
    R(4) = (R(31) + 124);
    GM_CALLV(0x8182780Cu, 0x8016A170u, 0);
    goto L_81827B70;
L_81827810:;
    cr_cmp_u(ctx, 0, R(3), 0x6u);
    if ((!CR_BIT(ctx, 2))) { goto L_81827B70; }
    { uint32_t ea_ = (R(25) + 8); ctx->f[15].d = ctx->ps1[15] = ldfs(base, ea_); }
    R(28) = R(31) |R(31);
    { uint32_t ea_ = (R(31) + 9312); stfs(base, ea_, ctx->f[15].d); }
    R(29) = R(31) |R(31);
    { uint32_t ea_ = (R(25) + 24); ctx->f[19].d = ctx->ps1[19] = ldfs(base, ea_); }
    R(23) = R(31) |R(31);
    { uint32_t ea_ = (R(25) + 104); ctx->f[20].d = ctx->ps1[20] = ldfs(base, ea_); }
    R(22) = R(31) |R(31);
    { uint32_t ea_ = (R(25) + 32); ctx->f[21].d = ctx->ps1[21] = ldfs(base, ea_); }
    R(21) = (R(31) + 3296);
    { uint32_t ea_ = (R(25) + 68); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    R(24) = (f + 10);
    { uint32_t ea_ = (R(25) + 148); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    R(26) = (f + 8);
    { uint32_t ea_ = (R(25) + 4); ctx->f[16].d = ctx->ps1[16] = ldfs(base, ea_); }
    R(15) = (0 + 0);
    { uint32_t ea_ = (R(25) + 132); ctx->f[17].d = ctx->ps1[17] = ldfs(base, ea_); }
    R(27) = (0 + 0);
    { uint32_t ea_ = (R(25) + 16); ctx->f[18].d = ctx->ps1[18] = ldfs(base, ea_); }
    R(17) = (0 + 1);
    { uint32_t ea_ = (R(25) + 140); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
    R(16) = (0 + 0);
    { uint32_t ea_ = (R(25) + 144); ctx->f[24].d = ctx->ps1[24] = ldfs(base, ea_); }
    R(30) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(25) + 100); ctx->f[25].d = ctx->ps1[25] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 28); ctx->f[26].d = ctx->ps1[26] = ldfs(base, ea_); }
L_81827880:;
    R(3) = ld32(base, (R(30) + -25136));
    R(0) = (R(3) + 0x90000u);
    R(18) = R(0) + R(27);
    R(0) = ld8(base, (R(18) + -2936));
    cr_cmp_u(ctx, 0, R(0), 0xFFu);
    if ((CR_BIT(ctx, 2))) { goto L_81827B20; }
    R(0) = ld32(base, (R(28) + 1296));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818278B0; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_81827904; }
    goto L_81827B20;
L_818278B0:;
    { uint32_t ea_ = (R(25) + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x818278B8u, 0x800B2F10u, 0);
    { uint32_t ea_ = (R(28) + 1696); stfs(base, ea_, ctx->f[15].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[19].d + ctx->f[1].d);
    R(3) = (0 + 0x10000u);
    { uint32_t ea_ = (R(28) + 2096); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(28) + 2496); stfs(base, ea_, ctx->f[16].d); }
    { uint32_t ea_ = (R(28) + 2896); stfs(base, ea_, ctx->f[15].d); }
    { uint32_t ea_ = (R(29) + 496); stfs(base, ea_, ctx->f[17].d); }
    { uint32_t ea_ = (R(29) + 500); stfs(base, ea_, ctx->f[18].d); }
    { uint32_t ea_ = (R(18) + -2940); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(18) + -2944); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(23) + 3296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(23) + 3300); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(23) + 3304); stfs(base, ea_, ctx->f[15].d); }
    R(4) = ld32(base, (R(28) + 1296));
    R(0) = (R(4) + 1);
    st32(base, (R(28) + 1296), R(0));
    GM_CALLV(0x818278FCu, 0x800B2EE0u, 0);
    st16(base, (R(22) + 4496), R(3));
    { uint32_t ea_ = (R(31) + 9312); stfs(base, ea_, ctx->f[15].d); }
L_81827904:;
    { uint32_t ea_ = (R(21) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) + R(15);
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(21) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(21) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + 4696), R(17));
    { uint32_t ea_ = (f + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[31].d);
    if ((CR_BIT(ctx, 0))) { goto L_8182794C; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[30].d);
    if ((CR_BIT(ctx, 1))) { goto L_8182794C; }
    { uint32_t ea_ = (f + 72); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[29].d);
    if ((CR_BIT(ctx, 1))) { goto L_8182794C; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[28].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81827954; }
L_8182794C:;
    st8(base, (R(3) + 4696), R(16));
    goto L_81827B20;
L_81827954:;
    { uint32_t ea_ = (R(31) + 9312); stfs(base, ea_, ctx->f[15].d); }
    R(18) = R(31) |R(31);
    { uint32_t ea_ = (R(25) + 4); ctx->f[14].d = ctx->ps1[14] = ldfs(base, ea_); }
    R(19) = (0 + 0);
L_81827964:;
    R(3) = R(19) |R(19);
    GM_CALLV(0x8182796Cu, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81827A34; }
    { uint32_t ea_ = (R(3) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 72); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 76); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[1].d); }
    if ((CR_BIT(ctx, 0))) { goto L_81827A34; }
    R(3) = (f + 56);
    R(4) = (f + 68);
    GM_CALLV(0x818279A4u, 0x801C1650u, 0);
    GM_CALLV(0x818279A8u, 0x802BE470u, 0);
    { uint32_t ea_ = (R(18) + 9316); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81827A34; }
    R(3) = (f + 56);
    R(4) = (f + 68);
    GM_CALLV(0x818279C0u, 0x801C1650u, 0);
    GM_CALLV(0x818279C4u, 0x802BE470u, 0);
    { uint32_t ea_ = (R(18) + 9316); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 9312); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[2].d);
    ctx->f[14].d = ctx->ps1[14] = frsp(ctx->f[19].d * ctx->f[1].d);
    ctx->f[14].d = ctx->ps1[14] = frsp(ctx->f[14].d + ctx->f[19].d);
    cr_fcmp(ctx, 0, ctx->f[14].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_818279FC; }
    ctx->f[1].u = ctx->f[14].u;
    { uint32_t ea_ = (R(31) + 9312); stfs(base, ea_, ctx->f[14].d); }
    ctx->f[2].u = ctx->f[19].u;
    { uint32_t ea_ = (R(25) + 136); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 40); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (R(31) + 9312);
    GM_CALLV(0x818279FCu, 0x8015F140u, 0);
L_818279FC:;
    R(0) = (int16_t)ld16(base, (R(31) + 9332));
    st16(base, (f + 10), R(0));
    { uint32_t ea_ = (R(24) + 0); psq_l(ctx, base, 0, ea_, 1, 3); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[20].d * ctx->f[0].d);
    GM_CALLV(0x81827A10u, 0x80237BD0u, 0);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[21].d * ctx->f[1].d);
    { uint32_t ea_ = (f + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[15].d - ctx->f[14].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[22].d + ctx->f[3].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    ctx->f[14].d = ctx->ps1[14] = frsp(ctx->f[2].d * ctx->f[3].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81827A34; }
    ctx->f[14].u = ctx->f[14].u ^ 0x8000000000000000ull;
L_81827A34:;
    R(19) = (R(19) + 1);
    R(18) = (R(18) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(19), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_81827A48; }
    R(18) = (R(18) + 12);
L_81827A48:;
    cr_cmp_s(ctx, 0, (int32_t)R(19), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81827964; }
    { uint32_t ea_ = (R(31) + 9312); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 2896); stfs(base, ea_, ctx->f[0].d); }
    R(18) = (int16_t)ld16(base, (R(22) + 4496));
    st16(base, (f + 8), R(18));
    { uint32_t ea_ = (R(26) + 0); psq_l(ctx, base, 0, ea_, 1, 3); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[20].d * ctx->f[0].d);
    GM_CALLV(0x81827A6Cu, 0x80237BD0u, 0);
    { uint32_t ea_ = (R(28) + 2096); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[24].d * ctx->f[14].d);
    { uint32_t ea_ = (R(28) + 1696); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[16].d, ctx->f[14].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[23].d * ctx->f[2].d);
    { uint32_t ea_ = (R(25) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[3].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[4].d + ctx->f[25].d);
    ctx->f[2].u = fctiw_bits(ctx->f[2].d, 1);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 192); st64(base, ea_, ctx->f[2].u); }
    R(0) = ld32(base, (f + 196));
    R(0) = R(18) + R(0);
    st16(base, (R(22) + 4496), R(0));
    { uint32_t ea_ = (R(28) + 2496); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_81827AEC; }
    ctx->f[2].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[3].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[2].d);
    ctx->f[2].d = frsp(ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[26].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81827B18; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[4].d);
    { uint32_t ea_ = (R(25) + 136); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[25].u;
    { uint32_t ea_ = (R(25) + 24); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (f + 28);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[27].d * ctx->f[0].d);
    GM_CALLV(0x81827AE8u, 0x8015F140u, 0);
    goto L_81827B18;
L_81827AEC:;
    { uint32_t ea_ = (R(25) + 136); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 28);
    { uint32_t ea_ = (R(25) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(25) + 40); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x81827B00u, 0x8015F140u, 0);
    { uint32_t ea_ = (R(25) + 64); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(31) + 9312);
    { uint32_t ea_ = (R(25) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[2].u;
    { uint32_t ea_ = (R(25) + 40); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x81827B18u, 0x8015F140u, 0);
L_81827B18:;
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 2496); stfs(base, ea_, ctx->f[0].d); }
L_81827B20:;
    R(15) = (R(15) + 1);
    R(28) = (R(28) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(15), 100);
    R(29) = (R(29) + 8);
    R(23) = (R(23) + 12);
    R(22) = (R(22) + 2);
    R(21) = (R(21) + 12);
    R(27) = (R(27) + 12);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81827880; }
    { uint32_t ea_ = (R(25) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 124);
    R(4) = (int16_t)ld16(base, (R(31) + 9308));
    ctx->f[2].u = ctx->f[1].u;
    { uint32_t ea_ = (R(31) + 180); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = (R(4) + 200);
    st16(base, (R(31) + 9308), R(0));
    GM_CALLV(0x81827B64u, 0x801C0BD0u, 0);
    R(3) = (R(31) + 324);
    R(4) = (R(31) + 124);
    GM_CALLV(0x81827B70u, 0x8016A170u, 0);
L_81827B70:;
    R(3) = (0 + 1);
L_81827B74:;
    R(11) = (f + 352);
    R(0) = lr;
}

/* mod_fn_2_157EF0 (mod_fn_2_157EF0, 328 bytes) */
static void mj_mod_fn_2_157EF0_28600(GM_CTX) {
    GM_FN(0x81828600); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x81850000u);
    R(29) = (0 + 0x81860000u);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(29) + -300));
    { uint32_t ea_ = (R(4) + -30936); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(4) = R(30) |R(30);
    st32(base, (f + 64), R(3));
    { uint32_t ea_ = (R(30) + 544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d * ctx->f[4].d);
    { uint32_t ea_ = R(4) + 220; stfs(base, ea_, ctx->f[2].d); R(4) = ea_; }
    R(3) = ld32(base, (R(4) + 76));
    { uint32_t ea_ = (R(4) + 328); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = ld32(base, (R(3) + 4));
    { uint32_t ea_ = (R(4) + 332); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d * ctx->f[4].d);
    R(5) = ld8(base, (R(5) + 337));
    { uint32_t ea_ = (R(4) + -48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[5].d * ctx->f[4].d);
    { uint32_t ea_ = (R(4) + -44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (R(5) + -6);
    R(5) = R(5) & 0xFFu;
    cr_cmp_u(ctx, 0, R(5), 0xFDu);
    { uint32_t ea_ = (R(4) + 4); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(4) + 8); stfs(base, ea_, ctx->f[4].d); }
    if ((CR_BIT(ctx, 1))) { goto L_81828698; }
    R(5) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(5) + -30960); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[5].d);
    { uint32_t ea_ = (R(30) + 220); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[5].d);
    { uint32_t ea_ = (R(30) + 224); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d * ctx->f[5].d);
    { uint32_t ea_ = (R(30) + 228); stfs(base, ea_, ctx->f[2].d); }
L_81828698:;
    { uint32_t ea_ = (R(30) + 604); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (f + 28);
    { uint32_t ea_ = (R(30) + 180); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[1].d); }
    R(5) = ld32(base, (f + 56));
    { uint32_t ea_ = (R(30) + 588); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 600); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[4].d);
    st32(base, (f + 12), R(5));
    R(5) = ld32(base, (f + 52));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (f + 8), R(5));
    R(5) = ld32(base, (f + 60));
    st32(base, (f + 16), R(5));
    R(5) = ld32(base, (R(30) + 256));
    st32(base, (f + 20), R(5));
    R(5) = ld16(base, (R(30) + 260));
    st16(base, (f + 24), R(5));
    R(5) = ld32(base, (R(4) + 0));
    st32(base, (f + 28), R(5));
    R(5) = ld32(base, (R(4) + 4));
    st32(base, (f + 32), R(5));
    R(5) = (f + 20);
    R(4) = ld32(base, (R(4) + 8));
    st32(base, (f + 36), R(4));
    R(4) = (f + 8);
    GM_CALLV(0x81828710u, 0x800D6F40u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x8182871Cu, 0x808C6EF0u, 0);
    R(3) = ld32(base, (R(29) + -300));
    R(4) = ld32(base, (f + 64));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81828744; }
    R(0) = lr;
    return;
L_81828744:;
    GM_CALLV(0x81828748u, 0x81844FCCu, 0);
}

/* mod_fn_2_1581F0 (mod_fn_2_1581F0, 192 bytes) */
static void mj_mod_fn_2_1581F0_28748(GM_CTX) {
    GM_FN(0x81828748); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(30) + 4));
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -5796);
    R(5) = rotl32(R(4), 2) & 0x3Cu;
    R(3) = ld32(base, (R(3) + R(5)));
    R(29) = R(4) & 0xFu;
    st32(base, (R(30) + 568), R(3));
    R(3) = (0 + 12);
    GM_CALLV(0x81828788u, 0x818432E4u, 0);
    R(28) = R(3) |R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81828794u, 0x81806A48u, 0);
    R(4) = R(3) |R(3);
    R(3) = R(28) |R(28);
    GM_CALLV(0x818287A0u, 0x800D6CC0u, 0);
    R(5) = ld8(base, (R(30) + 571));
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(6) = (0 + 2);
    st32(base, (R(30) + 296), R(28));
    GM_CALLV(0x818287B8u, 0x800D6DF0u, 0);
    R(3) = ld32(base, (R(30) + 296));
    R(5) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(5) + -30756); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (0 + 0x81850000u);
    R(3) = ld32(base, (R(3) + 4));
    { uint32_t ea_ = (R(5) + -30904); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (0 + 0x81850000u);
    R(4) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(5) + -31116); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(4) = ld32(base, (R(4) + 92));
    ctx->ctr = R(4);
    R(4) = (0 + 0);
    GM_CALLV(0x818287ECu, ctx->ctr, 0);
    R(0) = lr;
}

/* ctor_81829008 (ctor_81829008, 44 bytes) */
static void mj_ctor_81829008_29008(GM_CTX) {
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -1776));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) return;
    R(4) = (0 + 1);
    st8(base, (R(3) + -1776), R(4));
    R(4) = (0 + 0x3D4C0000u);
    R(3) = (0 + 0x80940000u);
    R(4) = R(4) | 0xCCCDu;
    st32(base, (R(3) + -12744), R(4));
}

/* mod_fn_2_1A3BE0 (mod_fn_2_1A3BE0, 452 bytes) */
static void mj_mod_fn_2_1A3BE0_29bd0(GM_CTX) {
    GM_FN(0x81829BD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(4) = (0 + 0x80370000u);
    R(28) = (0 + 0x80990000u);
    R(29) = (0 + 0x80940000u);
    R(5) = ld32(base, (R(4) + 31816));
    R(27) = R(3) |R(3);
    R(28) = (R(28) + -25320);
    R(29) = (R(29) + -9648);
    R(4) = (0 + -1);
    R(6) = (0 + 0);
    R(7) = (0 + 32);
    R(3) = (R(3) + 1316);
    GM_CALLV(0x81829C1Cu, 0x800690C0u, 0);
    R(3) = (0 + 0x80430000u);
    R(5) = (R(28) + 12);
    R(3) = ld32(base, (R(3) + -24520));
    R(4) = (R(28) + 36);
    R(3) = (R(3) + 4);
    GM_CALLV(0x81829C34u, 0x800DF180u, 0);
    st32(base, (R(27) + 1344), R(3));
    R(3) = (R(27) + 1344);
    R(4) = (R(28) + 36);
    GM_CALLV(0x81829C44u, 0x80239E30u, 0);
    st32(base, (f + 24), R(3));
    R(30) = R(3) |R(3);
    R(3) = (R(27) + 1348);
    R(4) = (f + 24);
    R(5) = (R(27) + 1316);
    R(6) = (0 + 35);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x81829C68u, 0x80169D90u, 0);
    R(3) = (R(27) + 1348);
    GM_CALLV(0x81829C70u, 0x80064C10u, 0);
    R(3) = (R(27) + 1344);
    R(4) = (R(28) + 48);
    GM_CALLV(0x81829C7Cu, 0x8023A0B0u, 0);
    st32(base, (f + 16), R(3));
    R(31) = R(3) |R(3);
    R(3) = (R(27) + 1412);
    R(4) = (f + 20);
    st32(base, (f + 20), R(30));
    R(5) = (f + 16);
    R(6) = (R(27) + 1316);
    R(7) = (0 + 0);
    GM_CALLV(0x81829CA0u, 0x801650D0u, 0);
    st32(base, (f + 32), R(31));
    R(3) = (R(27) + 1412);
    R(4) = (R(27) + 1348);
    R(5) = (f + 32);
    R(6) = (0 + 0);
    GM_CALLV(0x81829CB8u, 0x801651F0u, 0);
    { uint32_t ea_ = (R(29) + 96); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(27) + 1348);
    R(4) = (R(27) + 1412);
    GM_CALLV(0x81829CC8u, 0x80169F80u, 0);
    R(3) = (R(27) + 1344);
    R(4) = (R(28) + 36);
    GM_CALLV(0x81829CD4u, 0x8023A200u, 0);
    st32(base, (R(27) + 1468), R(3));
    R(4) = (f + 12);
    R(5) = (f + 8);
    R(6) = (R(27) + 1316);
    st32(base, (f + 8), R(3));
    R(3) = (R(27) + 1472);
    R(7) = (0 + 0);
    R(8) = (0 + 1);
    st32(base, (f + 12), R(30));
    GM_CALLV(0x81829CFCu, 0x80166830u, 0);
    R(3) = (R(27) + 1316);
    GM_CALLV(0x81829D04u, 0x800690E0u, 0);
    R(5) = ld32(base, (R(27) + 1528));
    R(4) = (R(29) + 112);
    R(0) = ld32(base, (R(27) + 1468));
    R(3) = (R(27) + 1472);
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    st32(base, (f + 28), R(0));
    R(4) = (0 + 0x81850000u);
    R(4) = (R(4) + -4836);
    { uint32_t ea_ = (R(4) + R(5)); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(4) = (R(27) + 1348);
    R(5) = (f + 28);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    GM_CALLV(0x81829D3Cu, 0x80166BD0u, 0);
    R(12) = ld32(base, (R(27) + 1348));
    R(3) = (R(27) + 1348);
    R(4) = (R(27) + 1472);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x81829D54u, ctx->ctr, 0);
    ctx->f[1].u = ctx->f[31].u;
    R(3) = (R(27) + 1472);
    R(4) = (0 + 0);
    GM_CALLV(0x81829D64u, 0x80166EF0u, 0);
    { uint32_t ea_ = (R(29) + 88); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(27) + 1472);
    R(4) = (0 + 0);
    GM_CALLV(0x81829D74u, 0x80166F10u, 0);
    R(11) = (f + 64);
    R(0) = lr;
}

/* mod_fn_2_1A3EE0 (mod_fn_2_1A3EE0, 116 bytes) */
static void mj_mod_fn_2_1A3EE0_29ddc(GM_CTX) {
    GM_FN(0x81829DDC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0);
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(30) + 1528));
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 13760);
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(3) + R(4)));
    R(29) = (R(30) + 172);
    R(4) = (0 + 0);
    R(5) = R(29) |R(29);
    R(7) = (0 + 0);
    GM_CALLV(0x81829E20u, 0x8016C890u, 0);
    R(4) = ld32(base, (R(30) + 1528));
    R(3) = R(29) |R(29);
    R(5) = (0 + 0);
    GM_CALLV(0x81829E30u, 0x8005E9A0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81829E38u, 0x80162510u, 0);
    R(0) = lr;
}

/* mod_fn_2_1A4330 (mod_fn_2_1A4330, 232 bytes) */
static void mj_mod_fn_2_1A4330_29e50(GM_CTX) {
    GM_FN(0x81829E50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x81829E68u, 0x818056E4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 5);
    if ((CR_BIT(ctx, 0))) { goto L_81829E88; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30764); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81829E7Cu, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30656); ctx->f[0].u = ld64(base, ea_); }
    goto L_81829ED0;
L_81829E88:;
    R(3) = ld32(base, (R(30) + 1524));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81829EBC; }
    R(3) = ld8(base, (R(30) + 840));
    R(4) = (0 + -30648);
    R(4) = (R(4) + 0x81850000u);
    R(3) = cntlzw(R(3));
    R(3) = rotl32(R(3), 29) & 0x4u;
    R(3) = ld32(base, (R(4) + R(3)));
    st32(base, (R(30) + 232), R(3));
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31004); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_81829F04;
L_81829EBC:;
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30768); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81829EC8u, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30616); ctx->f[0].u = ld64(base, ea_); }
L_81829ED0:;
    R(3) = ld8(base, (R(30) + 840));
    ctx->f[0].d = ctx->f[1].d + ctx->f[0].d;
    ctx->f[0].d = frsp(ctx->f[0].d);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81829EE8; }
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
L_81829EE8:;
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30956); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 232); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81829EF8u, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30856); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
L_81829F04:;
    R(3) = (0 + 0);
    st32(base, (R(30) + 240), R(3));
    R(3) = (0 + 13);
    st16(base, (R(30) + 1552), R(3));
    R(3) = R(30) |R(30);
    R(4) = (0 + 1);
    { uint32_t ea_ = (R(30) + 236); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81829F24u, 0x80911550u, 0);
    R(0) = lr;
}

/* mfn_8182AA74 (mfn_8182AA74, 116 bytes) */
static void mj_mfn_8182AA74_2aa74(GM_CTX) {
    GM_FN(0x8182AA74); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 520));
    R(29) = R(4) |R(4);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182AAAC; }
    R(4) = (0 + 52);
    GM_CALLV(0x8182AAA4u, 0x818434F4u, 0);
    R(3) = (0 + 0);
    st32(base, (R(30) + 520), R(3));
L_8182AAAC:;
    R(3) = R(30) |R(30);
    R(4) = (0 + -1);
    GM_CALLV(0x8182AAB8u, 0x800C89A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 1);
    if ((CR_BIT(ctx, 0))) { goto L_8182AACC; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 780);
    GM_CALLV(0x8182AACCu, 0x818434F4u, 0);
L_8182AACC:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_1B14B0 (mod_fn_2_1B14B0, 72 bytes) */
static void mj_mod_fn_2_1B14B0_2aae8(GM_CTX) {
    GM_FN(0x8182AAE8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24520));
    R(4) = (0 + 0x81850000u);
    R(6) = (0 + 0x81850000u);
    R(5) = (R(4) + 13792);
    R(4) = (R(6) + -4732);
    R(4) = (R(4) + 27);
    R(6) = (0 + 41);
    R(7) = (0 + 0);
    GM_CALLV(0x8182AB1Cu, 0x800DF7D0u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* mod_fn_2_1B1830 (mod_fn_2_1B1830, 104 bytes) */
static void mj_mod_fn_2_1B1830_2ab30(GM_CTX) {
    GM_FN(0x8182AB30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8182AB54u, 0x800E1A20u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 13956);
    st32(base, (R(30) + 96), R(3));
    R(3) = (R(30) + 176);
    R(4) = (0 + -1);
    GM_CALLV(0x8182AB6Cu, 0x8182AA74u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8182AB7C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182AB7Cu, 0x80162920u, 0);
L_8182AB7C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_2_1B21A0 (mod_fn_2_1B21A0, 32 bytes) */
static void mj_mod_fn_2_1B21A0_2ab98(GM_CTX) {
    GM_FN(0x8182AB98); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x8182ABA8u, 0x81814868u, 0);
    R(0) = lr;
}

/* mod_fn_2_1B2DB0 (mod_fn_2_1B2DB0, 200 bytes) */
static void mj_mod_fn_2_1B2DB0_2aedc(GM_CTX) {
    GM_FN(0x8182AEDC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(4) = ld8(base, (R(4) + -24144));
    R(30) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182AF2C; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23488));
    R(4) = ld32(base, (R(3) + 0));
    R(4) = ld32(base, (R(4) + 12));
    ctx->ctr = R(4);
    R(4) = (0 + 0);
    GM_CALLV(0x8182AF1Cu, ctx->ctr, 0);
L_8182AF1C:;
    R(4) = ld32(base, (R(30) + 4));
    R(3) = (0 + 0);
    GM_CALLV(0x8182AF28u, 0x800E37D0u, 0);
    goto L_8182AF58;
L_8182AF2C:;
    R(3) = ld8(base, (R(30) + 913));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182AF58; }
    GM_CALLV(0x8182AF3Cu, 0x800B3B20u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182AF58; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23848));
    R(3) = ld8(base, (R(3) + 3070));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182AF6C; }
L_8182AF58:;
    R(0) = lr;
    return;
L_8182AF6C:;
    R(3) = ld32(base, (R(30) + 952));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8182AF1C; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23452));
    R(4) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(4) + -24752));
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = R(4) + R(3);
    R(3) = ld32(base, (R(3) + 4));
    R(3) = ld16(base, (R(3) + 30));
    R(3) = R(3) & 0xF0Fu;
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8182AF1C; }
    GM_LOOP(); goto L_8182AF58;
}

/* mod_fn_2_1B5170 (mod_fn_2_1B5170, 2008 bytes) */
static void mj_mod_fn_2_1B5170_2afa4(GM_CTX) {
    GM_FN(0x8182AFA4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(0) = ld32(base, (R(3) + 408));
    R(4) = (0 + 0x80430000u);
    R(29) = ld32(base, (R(4) + -24512));
    R(4) = (0 + 0x43300000u);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    R(30) = (0 + 0x80940000u);
    R(31) = (0 + 0x80990000u);
    R(28) = (0 + 0);
    st32(base, (f + 24), R(4));
    R(27) = R(3) |R(3);
    R(30) = (R(30) + -8584);
    R(31) = (R(31) + -12984);
    st32(base, (f + 32), R(4));
    st8(base, (R(3) + 413), R(28));
    if ((CR_BIT(ctx, 1))) { goto L_8182B018; }
    R(0) = ld32(base, (R(3) + 332));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 60);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B008; }
    R(3) = (0 + 1);
    GM_CALLV(0x8182B008u, 0x800B5280u, 0);
L_8182B008:;
    R(0) = ld32(base, (R(27) + 332));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 500);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B018; }
    GM_CALLV(0x8182B018u, 0x800B52C0u, 0);
L_8182B018:;
    R(0) = ld32(base, (R(27) + 408));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B078; }
    R(0) = ld32(base, (R(27) + 332));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3100);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B068; }
    R(3) = (0 + 0x80430000u);
    R(4) = (0 + -1);
    R(3) = ld32(base, (R(3) + -24512));
    GM_CALLV(0x8182B040u, 0x800E0380u, 0);
    R(4) = (0 + 8);
    R(5) = (0 + 1);
    GM_CALLV(0x8182B04Cu, 0x800CE350u, 0);
    R(0) = R(3) & 0xFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182B060; }
    R(3) = (0 + 3);
    GM_CALLV(0x8182B05Cu, 0x800B5280u, 0);
    goto L_8182B068;
L_8182B060:;
    R(3) = (0 + 2);
    GM_CALLV(0x8182B068u, 0x800B5280u, 0);
L_8182B068:;
    R(0) = ld32(base, (R(27) + 332));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3400);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B078; }
    GM_CALLV(0x8182B078u, 0x800B52C0u, 0);
L_8182B078:;
    R(3) = (R(27) + 124);
    GM_CALLV(0x8182B080u, 0x800D8EA0u, 0);
    R(0) = ld32(base, (R(27) + 356));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182B0B8; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8182B178; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((CR_BIT(ctx, 2))) { goto L_8182B544; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 11);
    if ((CR_BIT(ctx, 2))) { goto L_8182B584; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 12);
    if ((CR_BIT(ctx, 2))) { goto L_8182B5D8; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 13);
    if ((CR_BIT(ctx, 2))) { goto L_8182B5F4; }
    goto L_8182B634;
L_8182B0B8:;
    R(0) = ld32(base, (R(27) + 408));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 1))) { goto L_8182B0F8; }
    R(26) = (0 + 0x80430000u);
    R(5) = (R(31) + 1128);
    R(3) = ld32(base, (R(26) + -24520));
    R(4) = (R(31) + 1068);
    R(3) = (R(3) + 4);
    GM_CALLV(0x8182B0DCu, 0x800DF180u, 0);
    R(6) = ld32(base, (R(26) + -24520));
    R(26) = R(3) |R(3);
    R(5) = (R(31) + 1152);
    R(4) = (R(31) + 1080);
    R(3) = (R(6) + 4);
    GM_CALLV(0x8182B0F4u, 0x800DF180u, 0);
    goto L_8182B164;
L_8182B0F8:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B134; }
    R(26) = (0 + 0x80430000u);
    R(5) = (R(31) + 1180);
    R(3) = ld32(base, (R(26) + -24520));
    R(4) = (R(31) + 1068);
    R(3) = (R(3) + 4);
    GM_CALLV(0x8182B118u, 0x800DF180u, 0);
    R(6) = ld32(base, (R(26) + -24520));
    R(26) = R(3) |R(3);
    R(5) = (R(31) + 1208);
    R(4) = (R(31) + 1080);
    R(3) = (R(6) + 4);
    GM_CALLV(0x8182B130u, 0x800DF180u, 0);
    goto L_8182B164;
L_8182B134:;
    R(26) = (0 + 0x80430000u);
    R(5) = (R(31) + 1236);
    R(3) = ld32(base, (R(26) + -24520));
    R(4) = (R(31) + 1068);
    R(3) = (R(3) + 4);
    GM_CALLV(0x8182B14Cu, 0x800DF180u, 0);
    R(6) = ld32(base, (R(26) + -24520));
    R(26) = R(3) |R(3);
    R(5) = (R(31) + 1268);
    R(4) = (R(31) + 1080);
    R(3) = (R(6) + 4);
    GM_CALLV(0x8182B164u, 0x800DF180u, 0);
L_8182B164:;
    R(4) = ld32(base, (R(27) + 356));
    st32(base, (R(27) + 192), R(26));
    R(0) = (R(4) + 1);
    st32(base, (R(27) + 196), R(3));
    st32(base, (R(27) + 356), R(0));
L_8182B178:;
    R(0) = ld32(base, (R(27) + 336));
    R(5) = ld32(base, (R(27) + 192));
    R(4) = ((int32_t)R(0) * 36);
    R(3) = ld32(base, (R(27) + 332));
    R(0) = ld32(base, (R(5) + R(4)));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { goto L_8182B1F4; }
    R(3) = R(5) + R(4);
    R(0) = ld32(base, (R(3) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B1AC; }
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (R(27) + 360), R(0));
L_8182B1AC:;
    R(0) = ld32(base, (R(27) + 336));
    R(3) = ld32(base, (R(27) + 192));
    R(0) = ((int32_t)R(0) * 36);
    R(3) = R(3) + R(0);
    R(0) = ld32(base, (R(3) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B1E0; }
    R(0) = ld32(base, (R(27) + 408));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B1DC; }
    R(0) = (0 + -1);
    st32(base, (R(27) + 404), R(0));
L_8182B1DC:;
    R(28) = (0 + 1);
L_8182B1E0:;
    R(3) = ld32(base, (R(27) + 336));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 500);
    if ((CR_BIT(ctx, 1))) { goto L_8182B1F4; }
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 336), R(0));
L_8182B1F4:;
    R(0) = ld32(base, (R(27) + 344));
    R(3) = ld32(base, (R(27) + 192));
    R(0) = ((int32_t)R(0) * 36);
    R(5) = ld32(base, (R(27) + 332));
    R(4) = ld32(base, (R(3) + R(0)));
    cr_cmp_s(ctx, 1, (int32_t)R(5), (int32_t)R(4));
    if ((CR_BIT(ctx, 4))) { goto L_8182B2B0; }
    R(8) = R(3) + R(0);
    R(0) = ld32(base, (R(8) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B29C; }
    if ((!CR_BIT(ctx, 6))) { goto L_8182B29C; }
    R(0) = ld32(base, (R(8) + 12));
    R(3) = (R(31) + 968);
    { uint32_t ea_ = (R(30) + 16); ctx->f[1].u = ld64(base, ea_); }
    R(5) = (f + 8);
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 28), R(0));
    R(4) = (0 + 0);
    R(6) = (0 + 0);
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    R(7) = (0 + 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(8) + 16));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 36), R(0));
    { uint32_t ea_ = (f + 32); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(8) + 20));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 28), R(0));
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(8) + 8));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(3) + R(0)));
    GM_CALLV(0x8182B294u, 0x8016C890u, 0);
    R(0) = (0 + 1);
    st8(base, (R(27) + 413), R(0));
L_8182B29C:;
    R(3) = ld32(base, (R(27) + 344));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 500);
    if ((CR_BIT(ctx, 1))) { goto L_8182B2B0; }
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 344), R(0));
L_8182B2B0:;
    R(0) = ld32(base, (R(27) + 352));
    R(3) = ld32(base, (R(27) + 192));
    R(0) = ((int32_t)R(0) * 36);
    R(5) = ld32(base, (R(27) + 332));
    R(4) = ld32(base, (R(3) + R(0)));
    cr_cmp_s(ctx, 1, (int32_t)R(5), (int32_t)R(4));
    if ((CR_BIT(ctx, 4))) { goto L_8182B30C; }
    R(4) = R(3) + R(0);
    R(0) = ld32(base, (R(4) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 6);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B2F8; }
    if ((!CR_BIT(ctx, 6))) { goto L_8182B2F8; }
    R(3) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(4) + 8));
    R(3) = ld32(base, (R(3) + -24568));
    R(4) = (0 + -1);
    R(6) = (0 + 0);
    GM_CALLV(0x8182B2F8u, 0x800D8E40u, 0);
L_8182B2F8:;
    R(3) = ld32(base, (R(27) + 352));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 500);
    if ((CR_BIT(ctx, 1))) { goto L_8182B30C; }
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 352), R(0));
L_8182B30C:;
    R(0) = ld32(base, (R(27) + 340));
    R(5) = ld32(base, (R(27) + 192));
    R(4) = ((int32_t)R(0) * 36);
    R(3) = ld32(base, (R(27) + 332));
    R(0) = ld32(base, (R(5) + R(4)));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_8182B3EC; }
    R(3) = R(5) + R(4);
    R(0) = ld32(base, (R(3) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B3D8; }
    R(0) = ld32(base, (R(3) + 8));
    { uint32_t ea_ = (R(30) + 16); ctx->f[1].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 36), R(0));
    { uint32_t ea_ = (f + 32); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 364); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(3) + 12));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 28), R(0));
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 368); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(3) + 16));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 36), R(0));
    { uint32_t ea_ = (f + 32); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 372); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(3) + 20));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 28), R(0));
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 376); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(3) + 24));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 36), R(0));
    { uint32_t ea_ = (f + 32); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 380); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(3) + 28));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 28), R(0));
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 384); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(3) + 32));
    st32(base, (R(27) + 400), R(0));
    st32(base, (R(27) + 404), R(0));
L_8182B3D8:;
    R(3) = ld32(base, (R(27) + 340));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 500);
    if ((CR_BIT(ctx, 1))) { goto L_8182B3EC; }
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 340), R(0));
L_8182B3EC:;
    R(0) = ld32(base, (R(27) + 348));
    R(4) = ld32(base, (R(27) + 196));
    R(0) = ((int32_t)R(0) * 36);
    R(3) = ld32(base, (R(27) + 332));
    { uint32_t ea_ = R(4) + R(0); R(0) = ld32(base, ea_); R(4) = ea_; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8182B43C; }
    R(0) = ld32(base, (R(4) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B424; }
    R(4) = ld32(base, (R(4) + 8));
    R(3) = (R(27) + 204);
    R(5) = (0 + 0);
    GM_CALLV(0x8182B424u, 0x80199E90u, 0);
L_8182B424:;
    R(3) = ld32(base, (R(27) + 348));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 500);
    if ((CR_BIT(ctx, 1))) { goto L_8182B43C; }
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 348), R(0));
    GM_LOOP(); goto L_8182B3EC;
L_8182B43C:;
    R(0) = ld32(base, (R(27) + 408));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8182B464; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24752));
    R(3) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 28));
    R(0) = R(0) & 0x101u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182B464; }
    R(28) = (0 + 1);
L_8182B464:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182B528; }
    R(3) = ld32(base, (R(27) + 408));
    R(0) = (0 + 1);
    st8(base, (R(27) + 412), R(0));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B48C; }
    R(0) = (0 + 10);
    st32(base, (R(27) + 356), R(0));
    goto L_8182B634;
L_8182B48C:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B4A4; }
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    GM_CALLV(0x8182B4A0u, 0x801017D0u, 0);
    goto L_8182B51C;
L_8182B4A4:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B4BC; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24708));
    GM_CALLV(0x8182B4B8u, 0x800BB880u, 0);
    goto L_8182B51C;
L_8182B4BC:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B51C; }
    R(3) = R(29) |R(29);
    R(4) = (0 + -1);
    GM_CALLV(0x8182B4D0u, 0x800E0380u, 0);
    R(4) = (0 + 8);
    R(5) = (0 + 1);
    GM_CALLV(0x8182B4DCu, 0x800CE350u, 0);
    R(0) = R(3) & 0xFFu;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8182B500; }
    R(3) = (0 + 0);
    GM_CALLV(0x8182B4ECu, 0x800B0DB0u, 0);
    R(3) = (0 + 4);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    GM_CALLV(0x8182B4FCu, 0x800E1E60u, 0);
    goto L_8182B51C;
L_8182B500:;
    R(3) = (0 + 0);
    GM_CALLV(0x8182B508u, 0x800B0DB0u, 0);
    GM_CALLV(0x8182B50Cu, 0x80102A40u, 0);
    R(4) = R(3) |R(3);
    R(3) = (0 + 3);
    R(5) = (0 + 0);
    GM_CALLV(0x8182B51Cu, 0x800E1E60u, 0);
L_8182B51C:;
    R(3) = ld32(base, (R(27) + 356));
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 356), R(0));
L_8182B528:;
    R(0) = ld8(base, (R(27) + 412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B634; }
    R(3) = ld32(base, (R(27) + 332));
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 332), R(0));
    goto L_8182B634;
L_8182B544:;
    R(3) = R(29) |R(29);
    R(4) = (0 + -1);
    GM_CALLV(0x8182B550u, 0x800E0380u, 0);
    R(4) = (0 + 0);
    R(5) = (0 + 1);
    GM_CALLV(0x8182B55Cu, 0x800CE360u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182B564u, 0x800E1690u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182B56Cu, 0x800E04B0u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182B574u, 0x800E0540u, 0);
    R(3) = ld32(base, (R(27) + 356));
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 356), R(0));
    goto L_8182B634;
L_8182B584:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182B58Cu, 0x800E0430u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B634; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24648));
    R(4) = ld32(base, (R(3) + 120));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182B5CC; }
    R(3) = (0 + 0x80430000u);
    R(0) = (0 + 1);
    R(3) = ld32(base, (R(3) + -23848));
    st8(base, (R(3) + 2959), R(0));
    st32(base, (R(3) + 2896), R(4));
    R(3) = ld32(base, (R(27) + 356));
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 356), R(0));
    goto L_8182B634;
L_8182B5CC:;
    R(0) = (0 + 13);
    st32(base, (R(27) + 356), R(0));
    goto L_8182B634;
L_8182B5D8:;
    GM_CALLV(0x8182B5DCu, 0x8076DBD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B634; }
    R(3) = ld32(base, (R(27) + 356));
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 356), R(0));
    goto L_8182B634;
L_8182B5F4:;
    R(3) = R(29) |R(29);
    R(4) = (0 + -1);
    GM_CALLV(0x8182B600u, 0x800E0380u, 0);
    R(4) = (0 + 0);
    R(5) = (0 + 1);
    GM_CALLV(0x8182B60Cu, 0x800CE380u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x8182B614u, 0x800B0DB0u, 0);
    GM_CALLV(0x8182B618u, 0x80102A40u, 0);
    R(4) = R(3) |R(3);
    R(3) = (0 + 3);
    R(5) = (0 + 0);
    GM_CALLV(0x8182B628u, 0x800E1E60u, 0);
    R(3) = ld32(base, (R(27) + 356));
    R(0) = (R(3) + 1);
    st32(base, (R(27) + 356), R(0));
L_8182B634:;
    R(0) = ld8(base, (R(27) + 412));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B760; }
    R(0) = ld32(base, (R(27) + 404));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8182B70C; }
    R(4) = ld32(base, (R(27) + 400));
    R(3) = R(0) ^ 0x80000000u;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(0) = R(4) ^ 0x80000000u;
    if ((CR_BIT(ctx, 1))) { goto L_8182B66C; }
    { uint32_t ea_ = (R(30) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 416); stfs(base, ea_, ctx->f[0].d); }
    goto L_8182B698;
L_8182B66C:;
    st32(base, (f + 36), R(3));
    { uint32_t ea_ = (R(30) + 16); ctx->f[3].u = ld64(base, ea_); }
    st32(base, (f + 28), R(0));
    { uint32_t ea_ = (f + 32); ctx->f[0].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 24); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[3].d);
    { uint32_t ea_ = (R(30) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d / ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 416); stfs(base, ea_, ctx->f[0].d); }
L_8182B698:;
    { uint32_t ea_ = (R(27) + 384); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 372); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = ld8(base, (R(27) + 412));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (R(27) + 416); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (R(27) + 376); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d * ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 364); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 380); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 368); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d - ctx->f[7].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d - ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d / ctx->f[0].d);
    { uint32_t ea_ = (R(27) + 396); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d * ctx->f[6].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[5].d * ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[7].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d + ctx->f[0].d);
    { uint32_t ea_ = (R(27) + 388); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(27) + 392); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_8182B70C; }
    R(3) = ld32(base, (R(27) + 404));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182B70C; }
    R(0) = (R(3) + -1);
    st32(base, (R(27) + 404), R(0));
L_8182B70C:;
    R(0) = ld32(base, (R(27) + 332));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 20);
    if ((!CR_BIT(ctx, 1))) { goto L_8182B760; }
    R(0) = ld32(base, (R(27) + 408));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8182B760; }
    R(4) = (0 + 0x80430000u);
    R(3) = (0 + 0x80430000u);
    R(0) = ld32(base, (R(4) + -23452));
    R(3) = ld32(base, (R(3) + -24752));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(0);
    R(3) = ld32(base, (R(3) + 4));
    R(0) = ld32(base, (R(3) + 28));
    R(0) = R(0) & 0xF0Fu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182B760; }
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    GM_CALLV(0x8182B758u, 0x801017D0u, 0);
    R(0) = (0 + 1);
    st8(base, (R(27) + 412), R(0));
L_8182B760:;
    R(11) = (f + 64);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* mod_fn_4_4F2B0 (mod_fn_4_4F2B0, 376 bytes) */
static void mj_mod_fn_4_4F2B0_2bf34(GM_CTX) {
    GM_FN(0x8182BF34); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x81850000u);
    R(4) = (R(4) + 7564);
    R(23) = (R(4) + -4);
    R(24) = (0 + 2);
    R(25) = (0 + 0);
    R(26) = (0 + 8);
    R(22) = (0 + 0);
    R(28) = (f + 12);
    R(29) = (f + 16);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    st32(base, (f + 20), R(3));
L_8182BF98:;
    { uint32_t ea_ = R(23) + 4; R(3) = ld32(base, ea_); R(23) = ea_; }
    cr_cmp_u(ctx, 0, R(22), 0x3u);
    st32(base, (f + 16), R(3));
    if ((CR_BIT(ctx, 1))) { goto L_8182BFBC; }
    R(3) = rotl32(R(22), 2) & 0xFFFFFFFCu;
    R(4) = R(30) + R(3);
    R(3) = (R(4) + 432);
    R(4) = (R(4) + 448);
    goto L_8182BFCC;
L_8182BFBC:;
    R(3) = ld32(base, (R(30) + 520));
    R(4) = R(3) + R(25);
    R(3) = (R(4) + -12);
    R(4) = (R(4) + 4);
L_8182BFCC:;
    R(5) = ld32(base, (R(3) + 0));
    R(27) = ld32(base, (R(4) + 0));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182BFF0; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(6) = (0 + 1);
    st32(base, (f + 12), R(24));
    GM_CALLV(0x8182BFF0u, 0x800B3B60u, 0);
L_8182BFF0:;
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182C010; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = R(27) |R(27);
    R(6) = (0 + 1);
    st32(base, (f + 12), R(24));
    GM_CALLV(0x8182C010u, 0x800B3B60u, 0);
L_8182C010:;
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182C04C; }
    R(5) = ld32(base, (R(30) + 516));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(6) = (0 + 1);
    st32(base, (f + 12), R(24));
    GM_CALLV(0x8182C030u, 0x800B3B60u, 0);
    R(3) = ld32(base, (R(30) + 520));
    R(4) = R(28) |R(28);
    st32(base, (f + 12), R(24));
    R(6) = (0 + 1);
    R(5) = ld32(base, (R(3) + 0));
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182C04Cu, 0x800B3B60u, 0);
L_8182C04C:;
    R(26) = (R(26) + -1);
    R(22) = (R(22) + 1);
    cr_cmp_u(ctx, 0, R(26), 0x0u);
    R(25) = (R(25) + 4);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8182BF98; }
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 20));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8182C0A8; }
    R(0) = lr;
    return;
L_8182C0A8:;
    GM_CALLV(0x8182C0ACu, 0x81844FCCu, 0);
}

/* mfn_8182C0AC (mfn_8182C0AC, 160 bytes) */
static void mj_mfn_8182C0AC_2c0ac(GM_CTX) {
    GM_FN(0x8182C0AC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(27) = ld32(base, (R(3) + 520));
    R(3) = (0 + 52);
    GM_CALLV(0x8182C0D8u, 0x818432E4u, 0);
    R(28) = (R(3) + 4);
    R(29) = R(3) |R(3);
    R(3) = R(28) |R(28);
    R(4) = (0 + 0);
    R(5) = (0 + 48);
    GM_CALLV(0x8182C0F0u, 0x81844D68u, 0);
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 14036);
    R(3) = R(30) |R(30);
    R(5) = R(28) |R(28);
    R(6) = (0 + 8);
    st32(base, (R(30) + 520), R(29));
    st32(base, (R(29) + 0), R(27));
    GM_CALLV(0x8182C110u, 0x800C8EB0u, 0);
    R(3) = ld32(base, (R(30) + 520));
    R(6) = (0 + 4);
    R(5) = (R(3) + 36);
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 14068);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182C12Cu, 0x800C8D60u, 0);
    R(0) = lr;
}

/* mod_fn_4_4F630 (mod_fn_4_4F630, 1108 bytes) */
static void mj_mod_fn_4_4F630_2c14c(GM_CTX) {
    GM_FN(0x8182C14C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(0) = ld8(base, (R(3) + 736));
    R(29) = (0 + 0x80B90000u);
    R(28) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    R(29) = (R(29) + -32136);
    if ((CR_BIT(ctx, 2))) { goto L_8182C180; }
    R(3) = (0 + 1);
    goto L_8182C588;
L_8182C180:;
    R(4) = (R(29) + 2036);
    R(5) = (0 + 0);
    GM_CALLV(0x8182C18Cu, 0x800C8CB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182C19C; }
    R(3) = (0 + 0);
    goto L_8182C588;
L_8182C19C:;
    R(12) = ld32(base, (R(28) + 8));
    R(3) = R(28) |R(28);
    R(4) = (R(29) + 2056);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x8182C1B8u, ctx->ctr, 0);
    R(3) = R(28) |R(28);
    R(4) = (R(29) + 368);
    R(5) = (0 + 8);
    GM_CALLV(0x8182C1C8u, 0x800C8FB0u, 0);
    R(5) = (0 + 0x80B70000u);
    R(3) = R(28) |R(28);
    R(4) = (R(29) + 512);
    R(6) = (0 + 15);
    R(5) = (R(5) + 23192);
    GM_CALLV(0x8182C1E0u, 0x800C90F0u, 0);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8182C1E8u, 0x80007220u, 0);
    st32(base, (R(28) + 408), R(3));
    R(5) = (0 + 0x80B70000u);
    R(3) = R(28) |R(28);
    R(4) = (R(29) + 648);
    R(5) = (R(5) + 23256);
    R(6) = (0 + 200);
    R(7) = (0 + 6);
    GM_CALLV(0x8182C208u, 0x800C8F20u, 0);
    R(3) = R(28) |R(28);
    R(4) = (R(29) + 1056);
    R(5) = (R(28) + 412);
    R(6) = (0 + 28);
    GM_CALLV(0x8182C21Cu, 0x800C8EB0u, 0);
    GM_CALLV(0x8182C220u, 0x800CDC60u, 0);
    R(31) = R(3) |R(3);
    R(30) = (R(28) + 52);
    R(27) = (0 + 13);
L_8182C22C:;
    R(3) = ld32(base, (R(30) + 412));
    R(4) = R(31) |R(31);
    R(5) = (0 + 102);
    R(6) = (0 + 42);
    R(7) = (0 + 0);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x8182C248u, 0x800C9A60u, 0);
    R(27) = (R(27) + 1);
    R(30) = (R(30) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(27), 22);
    if ((!CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8182C22C; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x8182C260u, 0x8182C0ACu, 0);
    R(3) = R(28) |R(28);
    R(4) = (R(29) + 1560);
    R(5) = (R(28) + 524);
    R(6) = (0 + 34);
    GM_CALLV(0x8182C274u, 0x800C8E40u, 0);
    R(3) = R(28) |R(28);
    R(4) = (R(29) + 1960);
    R(5) = (R(28) + 660);
    R(6) = (0 + 19);
    GM_CALLV(0x8182C288u, 0x800C8D60u, 0);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8182C290u, 0x80B6BD00u, 0);
    R(4) = ld32(base, (R(28) + 408));
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 23440);
    R(0) = ld8(base, (R(4) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(4) + 187), R(0));
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8182C2D0; }
    R(3) = ld32(base, (R(28) + 732));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    goto L_8182C2E0;
L_8182C2D0:;
    R(3) = ld32(base, (R(28) + 732));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
L_8182C2E0:;
    R(4) = ld32(base, (R(28) + 524));
    R(3) = (0 + 0x80430000u);
    R(30) = ld32(base, (R(3) + -24708));
    R(0) = ld8(base, (R(4) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(4) + 187), R(0));
    R(3) = ld32(base, (R(28) + 528));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 532));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 536));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 540));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(4) = ld32(base, (R(28) + 544));
    R(0) = ld8(base, (R(4) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(4) + 187), R(0));
    R(3) = ld32(base, (R(28) + 548));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 552));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 556));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 560));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 564));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(29) = ld32(base, (R(30) + 1000));
    cr_cmp_s(ctx, 0, (int32_t)R(29), 10);
    if ((CR_BIT(ctx, 0))) { goto L_8182C3A8; }
    R(29) = (R(29) + -10);
L_8182C3A8:;
    R(3) = ld32(base, (R(28) + 412));
    R(31) = (0 + 0x80430000u);
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 416));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 420));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 424));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 428));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(0) = ld32(base, (R(31) + -24704));
    R(0) = R(0) & 0x40u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182C4F8; }
    R(0) = ld32(base, (R(30) + 996));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182C4F8; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 5);
    if ((!CR_BIT(ctx, 0))) { goto L_8182C4F8; }
    R(3) = ld32(base, (R(28) + 656));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 512));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 420));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    R(3) = ld32(base, (R(28) + 424));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(3) + 187), R(0));
    GM_CALLV(0x8182C478u, 0x800CDC60u, 0);
    R(27) = R(3) |R(3);
    R(3) = ld32(base, (R(28) + 416));
    R(4) = R(27) |R(27);
    R(5) = (0 + 102);
    R(6) = (0 + 31);
    R(7) = (0 + 0);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x8182C498u, 0x800C9A60u, 0);
    R(0) = (R(29) + 1);
    st32(base, (R(30) + 952), R(0));
    R(4) = R(27) |R(27);
    R(5) = (0 + 102);
    R(3) = ld32(base, (R(28) + 428));
    R(6) = (0 + 33);
    R(7) = (0 + 0);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x8182C4BCu, 0x800C9A60u, 0);
    R(0) = ld32(base, (R(31) + -24704));
    R(0) = R(0) & 0x20u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182C4E0; }
    R(3) = ld32(base, (R(28) + 564));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    goto L_8182C520;
L_8182C4E0:;
    R(3) = ld32(base, (R(28) + 560));
    R(0) = ld8(base, (R(3) + 187));
    R(0) = R(0) & 0xFEu;
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 187), R(0));
    goto L_8182C520;
L_8182C4F8:;
    R(4) = ld32(base, (R(28) + 656));
    R(3) = R(28) |R(28);
    R(0) = ld8(base, (R(4) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(4) + 187), R(0));
    R(4) = ld32(base, (R(28) + 512));
    R(0) = ld8(base, (R(4) + 187));
    R(0) = R(0) & 0xFEu;
    st8(base, (R(4) + 187), R(0));
    GM_CALLV(0x8182C520u, 0x80B6BE10u, 0);
L_8182C520:;
    R(4) = (0 + 1);
    R(29) = (0 + 0);
    st8(base, (R(28) + 736), R(4));
    R(3) = (0 + 0x80430000u);
    st32(base, (R(28) + 740), R(29));
    R(0) = ld8(base, (R(3) + -24144));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182C558; }
    R(3) = (0 + 0x80430000u);
    R(4) = (0 + 1);
    R(3) = ld32(base, (R(3) + -23848));
    GM_CALLV(0x8182C550u, 0x8010E490u, 0);
    st8(base, (R(28) + 738), R(29));
    goto L_8182C55C;
L_8182C558:;
    st8(base, (R(28) + 738), R(4));
L_8182C55C:;
    R(0) = (0 + 0);
    st8(base, (R(28) + 739), R(0));
    R(3) = R(28) |R(28);
    GM_CALLV(0x8182C56Cu, 0x800C9500u, 0);
    R(3) = R(28) |R(28);
    R(4) = (0 + 14);
    R(5) = (0 + 0);
    GM_CALLV(0x8182C57Cu, 0x800C92F0u, 0);
    R(0) = (0 + 380);
    st32(base, (R(28) + 772), R(0));
    R(3) = (0 + 1);
L_8182C588:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* mod_fn_4_4FE20 (mod_fn_4_4FE20, 1120 bytes) */
static void mj_mod_fn_4_4FE20_2c5a0(GM_CTX) {
    GM_FN(0x8182C5A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 4);
    R(28) = (f + 28);
    R(29) = (f + 76);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(3) + -300));
    R(3) = (0 + 0);
    st32(base, (f + 172), R(4));
    R(4) = (R(30) + 656);
    ctx->ctr = R(5);
L_8182C5EC:;
    { uint32_t ea_ = R(4) + 4; R(5) = ld32(base, ea_); R(4) = ea_; }
    R(9) = R(3) |R(3);
    R(6) = ld32(base, (R(5) + 44));
    R(7) = ld32(base, (R(5) + 48));
    R(8) = ld8(base, (R(5) + 187));
    { uint32_t ea_ = R(9) + R(29); st32(base, ea_, R(6)); R(9) = ea_; }
    st32(base, (R(9) + 4), R(7));
    R(7) = R(8) & 0xFEu;
    st8(base, (R(5) + 187), R(7));
    R(6) = ld32(base, (R(5) + 52));
    R(5) = ld32(base, (R(4) + 52));
    st32(base, (R(9) + 8), R(6));
    R(9) = (R(3) + 12);
    R(6) = ld32(base, (R(5) + 44));
    R(7) = ld32(base, (R(5) + 48));
    R(8) = ld32(base, (R(5) + 52));
    { uint32_t ea_ = R(3) + R(28); st32(base, ea_, R(6)); R(3) = ea_; }
    R(6) = ld8(base, (R(5) + 187));
    st32(base, (R(3) + 4), R(7));
    st32(base, (R(3) + 8), R(8));
    R(3) = R(6) & 0xFEu;
    st8(base, (R(5) + 187), R(3));
    R(3) = R(9) |R(9);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8182C5EC; }
    R(4) = (0 + 4);
    R(3) = (0 + 36);
    ctx->ctr = R(4);
    R(4) = (0 + 48);
L_8182C65C:;
    R(5) = ld32(base, (R(30) + 520));
    R(9) = (R(4) + 12);
    R(5) = ld32(base, (R(5) + R(3)));
    R(3) = (R(3) + 4);
    R(6) = ld32(base, (R(5) + 44));
    R(7) = ld32(base, (R(5) + 48));
    R(8) = ld32(base, (R(5) + 52));
    { uint32_t ea_ = R(4) + R(29); st32(base, ea_, R(6)); R(4) = ea_; }
    R(6) = ld8(base, (R(5) + 187));
    st32(base, (R(4) + 4), R(7));
    st32(base, (R(4) + 8), R(8));
    R(4) = R(6) & 0xFEu;
    st8(base, (R(5) + 187), R(4));
    R(4) = R(9) |R(9);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8182C65C; }
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 23440);
    R(3) = ld32(base, (R(3) + 8));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8182C83C; }
    GM_CALLV(0x8182C6B0u, 0x818056B4u, 0);
    R(7) = (0 + 8);
    R(8) = (0 + 0x81860000u);
    R(9) = (0 + 0x81860000u);
    R(10) = (0 + -31116);
    ctx->ctr = R(7);
    R(7) = (R(8) + -6000);
    R(9) = (R(9) + -5828);
    R(4) = (R(30) + 660);
    R(5) = (R(30) + 712);
    R(6) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 5);
    R(8) = (R(10) + 0x81850000u);
    R(10) = (R(7) + -4);
    R(9) = (R(9) + -4);
    R(3) = (0 + 0);
L_8182C6EC:;
    { uint32_t ea_ = R(9) + 4; R(11) = ld32(base, ea_); R(9) = ea_; }
    R(12) = R(10) |R(10);
    R(10) = (R(10) + 4);
    cr_cmp_u(ctx, 1, R(11), 0x7u);
    if ((CR_BIT(ctx, 5))) { goto L_8182C7C4; }
    cr_cmp_u(ctx, 1, R(6), 0x7u);
    if ((CR_BIT(ctx, 5))) { goto L_8182C774; }
    R(12) = ld32(base, (R(12) + 4));
    cr_cmp_u(ctx, 1, R(12), 0x0u);
    if ((CR_BIT(ctx, 6))) { goto L_8182C774; }
    cr_cmp_u(ctx, 1, R(11), 0x4u);
    R(12) = rotl32(R(11), 2) & 0xFFFFFFFCu;
    if ((CR_BIT(ctx, 4))) { goto L_8182C730; }
    R(0) = ld32(base, (R(30) + 520));
    R(12) = R(0) + R(12);
    R(12) = (R(12) + 20);
    goto L_8182C734;
L_8182C730:;
    R(12) = R(4) + R(12);
L_8182C734:;
    R(0) = ((int32_t)R(6) * 12);
    R(27) = R(29) + R(0);
    R(26) = R(8) |R(8);
    if ((CR_BIT(ctx, 0))) { goto L_8182C748; }
    R(26) = R(27) |R(27);
L_8182C748:;
    R(12) = ld32(base, (R(12) + 0));
    R(6) = (R(6) + 1);
    R(26) = ld32(base, (R(26) + 0));
    R(0) = ld32(base, (R(27) + 4));
    st32(base, (R(12) + 44), R(26));
    R(26) = ld8(base, (R(12) + 187));
    R(27) = ld32(base, (R(27) + 8));
    st32(base, (R(12) + 48), R(0));
    R(0) = R(26) | 0x1u;
    st32(base, (R(12) + 52), R(27));
    st8(base, (R(12) + 187), R(0));
L_8182C774:;
    cr_cmp_u(ctx, 1, R(11), 0x3u);
    if ((CR_BIT(ctx, 5))) { goto L_8182C7C4; }
    cr_cmp_u(ctx, 1, R(3), 0x3u);
    if ((CR_BIT(ctx, 5))) { goto L_8182C7C4; }
    R(11) = rotl32(R(11), 2) & 0xFFFFFFFCu;
    R(12) = ld32(base, (R(7) + R(11)));
    cr_cmp_u(ctx, 1, R(12), 0x0u);
    if ((CR_BIT(ctx, 6))) { goto L_8182C7C4; }
    R(12) = ((int32_t)R(3) * 12);
    R(11) = ld32(base, (R(5) + R(11)));
    R(3) = (R(3) + 1);
    { uint32_t ea_ = R(12) + R(28); R(0) = ld32(base, ea_); R(12) = ea_; }
    R(27) = ld8(base, (R(11) + 187));
    st32(base, (R(11) + 44), R(0));
    R(0) = ld32(base, (R(12) + 8));
    R(12) = ld32(base, (R(12) + 4));
    st32(base, (R(11) + 52), R(0));
    st32(base, (R(11) + 48), R(12));
    R(12) = R(27) | 0x1u;
    st8(base, (R(11) + 187), R(12));
L_8182C7C4:;
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8182C6EC; }
    R(4) = (R(6) + -1);
    cr_cmp_s(ctx, 0, (int32_t)R(4), 3);
    st32(base, (R(30) + 760), R(6));
    if ((CR_BIT(ctx, 0))) { goto L_8182C7DC; }
    R(4) = (0 + 3);
L_8182C7DC:;
    { int32_t v_ = (int32_t)R(4); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(5) = (v_ >> 31); }
    R(4) = R(4) & ~R(5);
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(4) = R(30) + R(4);
    R(4) = ld32(base, (R(4) + 676));
    R(3) = (R(3) + -1);
    R(5) = ld32(base, (R(30) + 692));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    R(6) = ld32(base, (R(4) + 44));
    R(7) = ld32(base, (R(4) + 52));
    R(4) = ld32(base, (R(4) + 48));
    st32(base, (R(5) + 52), R(7));
    st32(base, (R(5) + 48), R(4));
    st32(base, (R(5) + 44), R(6));
    if ((CR_BIT(ctx, 0))) { goto L_8182C81C; }
    R(3) = (0 + 3);
L_8182C81C:;
    { int32_t v_ = (int32_t)R(3); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(4) = (v_ >> 31); }
    R(3) = R(3) & ~R(4);
    R(3) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = R(30) + R(3);
    R(3) = ld32(base, (R(3) + 696));
    R(4) = ld32(base, (R(30) + 728));
    R(3) = ld32(base, (R(3) + 44));
    st32(base, (R(4) + 44), R(3));
L_8182C83C:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 1);
    R(5) = (0 + 0);
    GM_CALLV(0x8182C84Cu, 0x800C93D0u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 3);
    R(5) = (0 + 0);
    GM_CALLV(0x8182C85Cu, 0x800C93D0u, 0);
    R(29) = (0 + 4);
    R(28) = (0 + 4);
L_8182C864:;
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    R(5) = (0 + 0);
    GM_CALLV(0x8182C874u, 0x800C93D0u, 0);
    R(28) = (R(28) + -1);
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    R(29) = (R(29) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8182C864; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(28) = (0 + 0);
    GM_CALLV(0x8182C898u, 0x800C92F0u, 0);
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 23440);
    R(3) = ld32(base, (R(3) + 8));
    R(4) = (0 + 1);
    st8(base, (R(30) + 737), R(4));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    R(3) = (0 + 2);
    if ((!CR_BIT(ctx, 2))) { goto L_8182C98C; }
    GM_CALLV(0x8182C8BCu, 0x800CDC60u, 0);
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(30) + 504));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = R(29) |R(29);
    R(5) = (0 + 102);
    R(6) = (0 + 45);
    R(7) = (0 + 0);
    GM_CALLV(0x8182C8DCu, 0x800C9A60u, 0);
    R(3) = ld32(base, (R(30) + 508));
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = R(29) |R(29);
    R(5) = (0 + 102);
    R(6) = (0 + 45);
    R(7) = (0 + 0);
    GM_CALLV(0x8182C8F8u, 0x800C9A60u, 0);
    R(4) = ld32(base, (R(30) + 504));
    R(3) = (f + 12);
    { uint32_t ea_ = (R(4) + 76); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    GM_CALLV(0x8182C908u, 0x802AE3D0u, 0);
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x81850000u);
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(30) + 504));
    { uint32_t ea_ = (R(4) + -31028); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d - ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    R(4) = ld32(base, (R(3) + 48));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[1].d); }
    R(5) = ld32(base, (R(30) + 508));
    R(3) = ld32(base, (R(3) + 52));
    { uint32_t ea_ = (R(5) + 44); stfs(base, ea_, ctx->f[1].d); }
    st32(base, (R(5) + 52), R(3));
    st32(base, (R(5) + 48), R(4));
    R(3) = ld32(base, (R(30) + 648));
    { uint32_t ea_ = (R(3) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = ld32(base, (R(3) + 48));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[0].d); }
    R(5) = ld32(base, (R(30) + 652));
    R(3) = ld32(base, (R(3) + 52));
    { uint32_t ea_ = (R(5) + 44); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(5) + 52), R(3));
    R(3) = R(30) |R(30);
    st32(base, (R(5) + 48), R(4));
    R(4) = (0 + 1);
    R(5) = (0 + 0);
    GM_CALLV(0x8182C984u, 0x800C92F0u, 0);
    R(3) = (0 + 1);
    st8(base, (R(30) + 739), R(28));
L_8182C98C:;
    st32(base, (R(30) + 740), R(3));
    R(3) = (R(30) + 564);
    R(4) = (0 + 20);
    ctx->ctr = R(4);
L_8182C99C:;
    { uint32_t ea_ = R(3) + 4; R(4) = ld32(base, ea_); R(3) = ea_; }
    R(5) = ld8(base, (R(4) + 187));
    R(5) = R(5) & 0xFEu;
    st8(base, (R(4) + 187), R(5));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8182C99C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182C9B8u, 0x800C9560u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182C9C0u, 0x80006EB0u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 172));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8182C9FC; }
    R(0) = lr;
    return;
L_8182C9FC:;
    GM_CALLV(0x8182CA00u, 0x81844FCCu, 0);
}

/* mod_fn_80111850 (mod_fn_80111850, 1496 bytes) */
static void mj_mod_fn_80111850_2ca00(GM_CTX) {
    GM_FN(0x8182CA00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + -1);
    R(6) = (0 + 0);
    R(7) = (0 + 32);
    R(29) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(30) = (R(29) + 1316);
    R(3) = ld32(base, (R(3) + -300));
    st32(base, (f + 124), R(3));
    R(3) = (0 + 0x80370000u);
    R(5) = ld32(base, (R(3) + 31816));
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182CA70u, 0x800690C0u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24520));
    R(4) = (0 + 0x81850000u);
    R(26) = (R(4) + -4138);
    R(5) = (R(26) + 68);
    R(3) = (R(3) + 4);
    R(4) = R(26) |R(26);
    GM_CALLV(0x8182CA90u, 0x800DF180u, 0);
    R(28) = R(29) |R(29);
    { uint32_t ea_ = R(28) + 1344; st32(base, ea_, R(3)); R(28) = ea_; }
    R(3) = R(28) |R(28);
    R(4) = R(26) |R(26);
    GM_CALLV(0x8182CAA4u, 0x80239E30u, 0);
    R(24) = (R(28) + 4);
    R(27) = (f + 8);
    R(23) = R(3) |R(3);
    st32(base, (f + 120), R(3));
    R(5) = R(30) |R(30);
    st32(base, (f + 8), R(3));
    R(3) = R(24) |R(24);
    R(6) = (0 + 32);
    R(7) = (0 + 1);
    R(4) = R(27) |R(27);
    R(8) = (0 + 0);
    GM_CALLV(0x8182CAD4u, 0x80169D90u, 0);
    R(3) = R(24) |R(24);
    R(4) = (0 + -1);
    R(5) = (0 + 152);
    GM_CALLV(0x8182CAE4u, 0x8016A2A0u, 0);
    R(22) = (R(26) + 8);
    R(3) = R(28) |R(28);
    R(4) = R(22) |R(22);
    GM_CALLV(0x8182CAF4u, 0x8023A0B0u, 0);
    st32(base, (f + 112), R(3));
    R(21) = R(3) |R(3);
    R(3) = ld32(base, (f + 112));
    R(20) = (R(28) + 132);
    R(25) = (f + 12);
    R(4) = R(27) |R(27);
    st32(base, (f + 12), R(3));
    R(3) = R(20) |R(20);
    R(6) = R(30) |R(30);
    R(5) = R(25) |R(25);
    R(7) = (0 + 0);
    st32(base, (f + 116), R(23));
    st32(base, (f + 8), R(23));
    GM_CALLV(0x8182CB2Cu, 0x801650D0u, 0);
    R(3) = R(20) |R(20);
    R(4) = R(24) |R(24);
    R(5) = R(27) |R(27);
    R(6) = (0 + 0);
    st32(base, (f + 108), R(21));
    st32(base, (f + 8), R(21));
    GM_CALLV(0x8182CB48u, 0x801651F0u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30800); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(3) = R(24) |R(24);
    R(4) = R(20) |R(20);
    ctx->f[1].u = ctx->f[31].u;
    GM_CALLV(0x8182CB60u, 0x80169F80u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(22) |R(22);
    GM_CALLV(0x8182CB6Cu, 0x8023A270u, 0);
    st32(base, (f + 100), R(3));
    R(22) = R(3) |R(3);
    R(3) = ld32(base, (f + 100));
    R(21) = (R(28) + 332);
    R(4) = R(27) |R(27);
    R(5) = R(25) |R(25);
    st32(base, (f + 12), R(3));
    R(3) = R(21) |R(21);
    R(6) = R(30) |R(30);
    R(7) = (0 + 0);
    R(8) = (0 + 1);
    st32(base, (f + 104), R(23));
    st32(base, (f + 8), R(23));
    GM_CALLV(0x8182CBA4u, 0x80167420u, 0);
    R(3) = R(21) |R(21);
    R(4) = R(24) |R(24);
    R(5) = R(27) |R(27);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    st32(base, (f + 96), R(22));
    st32(base, (f + 8), R(22));
    GM_CALLV(0x8182CBC4u, 0x80167800u, 0);
    R(3) = R(24) |R(24);
    R(4) = R(21) |R(21);
    ctx->f[1].u = ctx->f[31].u;
    GM_CALLV(0x8182CBD4u, 0x80169F80u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(26) |R(26);
    GM_CALLV(0x8182CBE0u, 0x8023A200u, 0);
    st32(base, (f + 88), R(3));
    R(22) = R(3) |R(3);
    R(3) = ld32(base, (f + 88));
    R(4) = R(27) |R(27);
    st32(base, (f + 92), R(23));
    R(5) = R(25) |R(25);
    st32(base, (f + 8), R(23));
    R(23) = (R(28) + 244);
    st32(base, (f + 12), R(3));
    R(3) = R(23) |R(23);
    R(6) = R(30) |R(30);
    R(7) = (0 + 0);
    R(8) = (0 + 1);
    GM_CALLV(0x8182CC18u, 0x80166830u, 0);
    R(3) = R(23) |R(23);
    R(4) = R(24) |R(24);
    R(5) = R(27) |R(27);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    st32(base, (f + 84), R(22));
    st32(base, (f + 8), R(22));
    GM_CALLV(0x8182CC38u, 0x80166BD0u, 0);
    R(3) = R(24) |R(24);
    R(4) = R(23) |R(23);
    ctx->f[1].u = ctx->f[31].u;
    GM_CALLV(0x8182CC48u, 0x80169F80u, 0);
    R(20) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(20) + -25280));
    GM_CALLV(0x8182CC54u, 0x80066540u, 0);
    R(4) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(4) + -31116); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    ctx->f[1].u = ctx->f[31].u;
    if ((!CR_BIT(ctx, 2))) { goto L_8182CC6C; }
    ctx->f[1].u = ctx->f[30].u;
L_8182CC6C:;
    R(3) = R(23) |R(23);
    R(4) = (0 + 0);
    GM_CALLV(0x8182CC78u, 0x80166EF0u, 0);
    R(3) = R(23) |R(23);
    ctx->f[1].u = ctx->f[30].u;
    R(4) = (0 + 0);
    GM_CALLV(0x8182CC88u, 0x80166F10u, 0);
    R(22) = (R(26) + 23);
    R(3) = R(28) |R(28);
    R(4) = R(22) |R(22);
    GM_CALLV(0x8182CC98u, 0x80239E30u, 0);
    R(24) = (R(28) + 68);
    R(23) = R(3) |R(3);
    st32(base, (f + 80), R(3));
    R(4) = R(27) |R(27);
    st32(base, (f + 8), R(3));
    R(3) = R(24) |R(24);
    R(5) = R(30) |R(30);
    R(6) = (0 + 32);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x8182CCC4u, 0x80169D90u, 0);
    R(4) = (R(26) + 41);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8182CCD0u, 0x8023A0B0u, 0);
    st32(base, (f + 72), R(3));
    R(26) = R(3) |R(3);
    R(3) = ld32(base, (f + 72));
    R(21) = (R(28) + 188);
    R(4) = R(27) |R(27);
    R(5) = R(25) |R(25);
    st32(base, (f + 12), R(3));
    R(3) = R(21) |R(21);
    R(6) = R(30) |R(30);
    R(7) = (0 + 0);
    st32(base, (f + 76), R(23));
    st32(base, (f + 8), R(23));
    GM_CALLV(0x8182CD04u, 0x801650D0u, 0);
    R(3) = R(21) |R(21);
    R(4) = R(24) |R(24);
    R(5) = R(27) |R(27);
    R(6) = (0 + 0);
    st32(base, (f + 68), R(26));
    st32(base, (f + 8), R(26));
    GM_CALLV(0x8182CD20u, 0x801651F0u, 0);
    R(3) = R(24) |R(24);
    R(4) = R(21) |R(21);
    ctx->f[1].u = ctx->f[31].u;
    GM_CALLV(0x8182CD30u, 0x80169F80u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(22) |R(22);
    GM_CALLV(0x8182CD3Cu, 0x8023A200u, 0);
    st32(base, (f + 60), R(3));
    R(22) = R(3) |R(3);
    R(3) = ld32(base, (f + 60));
    R(26) = (R(28) + 288);
    R(4) = R(27) |R(27);
    R(5) = R(25) |R(25);
    st32(base, (f + 12), R(3));
    R(3) = R(26) |R(26);
    R(6) = R(30) |R(30);
    R(7) = (0 + 0);
    R(8) = (0 + 1);
    st32(base, (f + 64), R(23));
    st32(base, (f + 8), R(23));
    GM_CALLV(0x8182CD74u, 0x80166830u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(24) |R(24);
    R(5) = R(27) |R(27);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    st32(base, (f + 56), R(22));
    st32(base, (f + 8), R(22));
    GM_CALLV(0x8182CD94u, 0x80166BD0u, 0);
    R(3) = R(24) |R(24);
    R(4) = R(26) |R(26);
    ctx->f[1].u = ctx->f[31].u;
    GM_CALLV(0x8182CDA4u, 0x80169F80u, 0);
    R(3) = ld32(base, (R(20) + -25280));
    GM_CALLV(0x8182CDACu, 0x80066540u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182CDB8; }
    ctx->f[31].u = ctx->f[30].u;
L_8182CDB8:;
    R(3) = R(26) |R(26);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = (0 + 0);
    GM_CALLV(0x8182CDC8u, 0x80166EF0u, 0);
    R(3) = R(26) |R(26);
    ctx->f[1].u = ctx->f[30].u;
    R(4) = (0 + 0);
    GM_CALLV(0x8182CDD8u, 0x80166F10u, 0);
    R(3) = ld32(base, (R(28) + 684));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182CF74; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24520));
    R(4) = (0 + 0x81850000u);
    R(23) = (R(4) + -4138);
    R(28) = (R(23) + 14);
    R(3) = (R(3) + 4);
    R(5) = (R(23) + 86);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8182CE08u, 0x800DF180u, 0);
    R(26) = (f + 52);
    st32(base, (f + 52), R(3));
    R(3) = R(26) |R(26);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8182CE1Cu, 0x80239E30u, 0);
    R(28) = (R(29) + 1720);
    R(25) = (f + 8);
    R(27) = R(3) |R(3);
    st32(base, (f + 48), R(3));
    R(5) = R(30) |R(30);
    st32(base, (f + 8), R(3));
    R(3) = R(28) |R(28);
    R(6) = (0 + 32);
    R(7) = (0 + 1);
    R(4) = R(25) |R(25);
    R(8) = (0 + 0);
    GM_CALLV(0x8182CE4Cu, 0x80169D90u, 0);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8182CE54u, 0x80064C10u, 0);
    R(4) = (R(23) + 36);
    R(3) = R(26) |R(26);
    GM_CALLV(0x8182CE60u, 0x8023A0B0u, 0);
    st32(base, (f + 40), R(3));
    R(26) = R(3) |R(3);
    R(3) = ld32(base, (f + 40));
    R(24) = (R(29) + 1784);
    R(5) = (f + 12);
    R(4) = R(25) |R(25);
    st32(base, (f + 12), R(3));
    R(3) = R(24) |R(24);
    R(6) = R(30) |R(30);
    R(7) = (0 + 0);
    st32(base, (f + 44), R(27));
    st32(base, (f + 8), R(27));
    GM_CALLV(0x8182CE94u, 0x801650D0u, 0);
    R(3) = R(24) |R(24);
    R(4) = R(28) |R(28);
    R(5) = R(25) |R(25);
    R(6) = (0 + 0);
    st32(base, (f + 36), R(26));
    st32(base, (f + 8), R(26));
    GM_CALLV(0x8182CEB0u, 0x801651F0u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(24) |R(24);
    GM_CALLV(0x8182CEBCu, 0x80169F30u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31028); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(24) |R(24);
    GM_CALLV(0x8182CECCu, 0x801680E0u, 0);
    R(3) = ld8(base, (R(29) + 5));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8182CF74; }
    R(4) = (R(23) + 52);
    R(3) = (f + 52);
    GM_CALLV(0x8182CEE4u, 0x8023A200u, 0);
    st32(base, (f + 28), R(3));
    R(26) = R(3) |R(3);
    R(3) = ld32(base, (f + 28));
    R(29) = (R(29) + 1840);
    st32(base, (f + 32), R(27));
    R(5) = (f + 12);
    st32(base, (f + 8), R(27));
    R(27) = (f + 8);
    st32(base, (f + 12), R(3));
    R(3) = R(29) |R(29);
    R(6) = R(30) |R(30);
    R(7) = (0 + 0);
    R(4) = R(27) |R(27);
    R(8) = (0 + 1);
    GM_CALLV(0x8182CF20u, 0x80166830u, 0);
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = R(27) |R(27);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    st32(base, (f + 24), R(26));
    st32(base, (f + 8), R(26));
    GM_CALLV(0x8182CF40u, 0x80166BD0u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    GM_CALLV(0x8182CF4Cu, 0x80169F30u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30800); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(29) |R(29);
    R(4) = (0 + 0);
    GM_CALLV(0x8182CF60u, 0x80166EF0u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(29) |R(29);
    R(4) = (0 + 0);
    GM_CALLV(0x8182CF74u, 0x80166F10u, 0);
L_8182CF74:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182CF7Cu, 0x800690E0u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 124));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8182CFD4; }
    R(0) = lr;
    return;
L_8182CFD4:;
    GM_CALLV(0x8182CFD8u, 0x81844FCCu, 0);
}

/* mod_fn_801133B0 (mod_fn_801133B0, 256 bytes) */
static void mj_mod_fn_801133B0_2d144(GM_CTX) {
    GM_FN(0x8182D144); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 2028));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182D198; }
    R(3) = ld8(base, (R(30) + 5));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8182D22C; }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = R(3) + 2016; R(4) = ld32(base, ea_); R(3) = ea_; }
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182D1A8; }
    R(3) = (0 + 30);
    st32(base, (R(30) + 2016), R(3));
    R(3) = (0 + 31);
    st32(base, (R(30) + 2020), R(3));
    goto L_8182D218;
L_8182D198:;
    R(3) = R(30) |R(30);
    { uint32_t ea_ = R(3) + 2016; R(4) = ld32(base, ea_); R(3) = ea_; }
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182D1B4; }
L_8182D1A8:;
    R(4) = (R(4) + -1);
    st32(base, (R(3) + 0), R(4));
    goto L_8182D22C;
L_8182D1B4:;
    R(3) = ld32(base, (R(30) + 2064));
    GM_CALLV(0x8182D1BCu, 0x8005F900u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182D22C; }
    R(29) = R(3) |R(3);
    R(3) = (R(3) + 3748);
    GM_CALLV(0x8182D1D0u, 0x8005E780u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182D22C; }
    R(3) = (0 + 30);
    st32(base, (R(30) + 2016), R(3));
    R(3) = (0 + 31);
    st32(base, (R(30) + 2020), R(3));
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182D1F0u, 0x801132C0u, 0);
    R(4) = ld8(base, (R(30) + 2067));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24568));
    R(5) = (0 + 10);
    R(4) = (int8_t)R(4);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x8182D210u, 0x800D8BB0u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182D218u, 0x80138D40u, 0);
L_8182D218:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 1);
    GM_CALLV(0x8182D224u, 0x80111D80u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182D22Cu, 0x80112F50u, 0);
L_8182D22C:;
    R(0) = lr;
}

/* mod_fn_8011A570 (mod_fn_8011A570, 124 bytes) */
static void mj_mod_fn_8011A570_2d244(GM_CTX) {
    GM_FN(0x8182D244); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 4));
    R(3) = R(0) & 0xFu;
    R(4) = rotl32(R(0), 16) & 0x3u;
    GM_CALLV(0x8182D268u, 0x8011AF20u, 0);
    R(6) = ld32(base, (R(31) + 4));
    R(7) = (0 + 0x81860000u);
    R(5) = (0 + 0x81860000u);
    R(0) = (0 + 60);
    R(4) = R(6) & 0xFu;
    st8(base, (R(31) + 909), R(4));
    R(8) = rotl32(R(6), 2) & 0x3Cu;
    R(7) = (R(7) + -1736);
    st32(base, (R(31) + 1364), R(4));
    R(5) = (R(5) + -1704);
    R(6) = ld32(base, (R(7) + R(8)));
    R(4) = ld32(base, (R(5) + R(8)));
    R(6) = (R(6) + 1);
    st32(base, (R(7) + R(8)), R(6));
    R(4) = (R(4) + 1);
    st32(base, (R(5) + R(8)), R(4));
    st32(base, (R(31) + 1368), R(0));
    R(0) = lr;
}

/* mod_fn_80123330 (mod_fn_80123330, 688 bytes) */
static void mj_mod_fn_80123330_2d2c0(GM_CTX) {
    GM_FN(0x8182D2C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x802F0000u);
    R(31) = (R(31) + 19712);
    R(30) = (0 + 0x81860000u);
    R(30) = (R(30) + -6192);
    R(29) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 4));
    R(0) = R(4) & 0xFu;
    st8(base, (R(3) + 909), R(0));
    R(3) = R(0) |R(0);
    R(4) = rotl32(R(4), 16) & 0x3u;
    R(3) = (int8_t)R(3);
    GM_CALLV(0x8182D308u, 0x801245C0u, 0);
    R(0) = ld8(base, (R(29) + 909));
    R(4) = (0 + 60);
    st32(base, (R(29) + 976), R(4));
    R(6) = (R(30) + 0);
    R(0) = (int8_t)R(0);
    R(4) = (R(30) + 32);
    R(7) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(5) = ld32(base, (R(6) + R(7)));
    R(3) = ld32(base, (R(4) + R(7)));
    R(0) = (R(5) + 1);
    st32(base, (R(6) + R(7)), R(0));
    R(0) = (R(3) + 1);
    st32(base, (R(4) + R(7)), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8182D354; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182D34Cu, 0x80162510u, 0);
    R(3) = (0 + 0);
    goto L_8182D554;
L_8182D354:;
    R(0) = ld32(base, (R(29) + 4));
    R(4) = (R(29) + 992);
    { uint32_t ea_ = (R(29) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = rotl32(R(0), 24) & 0x3u;
    R(0) = rotl32(R(0), 20) & 0x3u;
    st8(base, (R(29) + 487), R(0));
    { uint32_t ea_ = (R(29) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    st8(base, (R(29) + 721), R(0));
    st8(base, (R(29) + 778), R(0));
    st8(base, (R(29) + 911), R(3));
    st8(base, (R(29) + 488), R(3));
    st8(base, (R(29) + 728), R(3));
    GM_CALLV(0x8182D388u, 0x80075270u, 0);
    R(0) = ld32(base, (R(29) + 4));
    R(4) = (f + 12);
    st32(base, (R(29) + 988), R(3));
    R(3) = R(29) |R(29);
    R(0) = rotl32(R(0), 28) & 0x1u;
    { uint32_t ea_ = (R(13) + -8208); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st8(base, (R(29) + 840), R(0));
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8182D3ACu, 0x801237F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182D3C4; }
    { uint32_t ea_ = (R(13) + -8204); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(29) + 176); stfs(base, ea_, ctx->f[0].d); }
L_8182D3C4:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182D3CCu, 0x80123740u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182D410; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182D3DCu, 0x80123A00u, 0);
    R(30) = ld32(base, (R(13) + -22816));
    R(3) = (f + 16);
    R(4) = (R(29) + 172);
    GM_CALLV(0x8182D3ECu, 0x8006A4B0u, 0);
    R(3) = R(30) |R(30);
    R(5) = (f + 16);
    R(4) = (0 + 617);
    R(6) = (0 + 0);
    GM_CALLV(0x8182D400u, 0x80198C30u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8182D408u, 0x80162510u, 0);
    R(3) = (0 + 0);
    goto L_8182D554;
L_8182D410:;
    R(0) = ld32(base, (R(29) + 288));
    R(3) = (0 + 5);
    { uint32_t ea_ = (R(13) + -8208); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = R(0) | 0x80u;
    { uint32_t ea_ = (R(29) + 208); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 212); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 216); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(29) + 877), R(3));
    st32(base, (R(29) + 288), R(0));
    R(3) = ld32(base, (R(13) + -21688));
    R(4) = ld32(base, (R(13) + -22504));
    R(0) = ld8(base, (R(3) + 4622));
    R(0) = ((int32_t)R(0) * 944);
    R(3) = R(4) + R(0);
    R(0) = ld32(base, (R(3) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182D458; }
    goto L_8182D45C;
L_8182D458:;
    R(3) = (0 + 0);
L_8182D45C:;
    R(4) = (R(29) + 172);
    GM_CALLV(0x8182D464u, 0x8008E770u, 0);
    st8(base, (R(29) + 841), R(3));
    R(4) = R(29) |R(29);
    R(3) = (R(29) + 328);
    R(5) = (R(31) + 52);
    GM_CALLV(0x8182D478u, 0x8008C3E0u, 0);
    R(0) = ld8(base, (R(29) + 911));
    R(3) = (R(29) + 328);
    st8(base, (R(29) + 488), R(0));
    GM_CALLV(0x8182D488u, 0x8008C330u, 0);
    R(12) = ld32(base, (R(29) + 1036));
    R(3) = (R(29) + 1036);
    R(4) = (R(29) + 1008);
    R(5) = (0 + 3);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x8182D4A4u, ctx->ctr, 0);
    { uint32_t ea_ = (R(13) + -8204); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 24);
    { uint32_t ea_ = (R(29) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 8);
    { uint32_t ea_ = (R(29) + 180); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(6) = (0 + 1);
    { uint32_t ea_ = (R(29) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[3].d); }
    R(5) = ld8(base, (R(29) + 911));
    GM_CALLV(0x8182D4D8u, 0x80075CA0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182D4FC; }
    { uint32_t ea_ = (f + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -8200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8182D4FC; }
    { uint32_t ea_ = (R(29) + 176); stfs(base, ea_, ctx->f[0].d); }
L_8182D4FC:;
    R(4) = R(29) |R(29);
    R(3) = (R(29) + 492);
    R(5) = (R(31) + 16);
    R(6) = (R(31) + 28);
    R(7) = (R(31) + 40);
    GM_CALLV(0x8182D514u, 0x8006D090u, 0);
    { uint32_t ea_ = (R(29) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(29) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(29) + 916);
    { uint32_t ea_ = (R(29) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 23256);
    st32(base, (R(29) + 980), R(0));
    { uint32_t ea_ = (R(29) + 996); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(29) + 1000); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(29) + 1004); stfs(base, ea_, ctx->f[0].d); }
    R(12) = ld32(base, (R(29) + 916));
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x8182D550u, ctx->ctr, 0);
    R(3) = (0 + 1);
L_8182D554:;
    R(0) = lr;
}

/* mod_fn_80125F10 (mod_fn_80125F10, 40 bytes) */
static void mj_mod_fn_80125F10_2d570(GM_CTX) {
    R(3) = ld8(base, (R(3) + 914));
    cr_cmp_u(ctx, 0, R(3), 0x8u);
    if ((CR_BIT(ctx, 0))) { goto L_8182D58C; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 16);
    if ((!CR_BIT(ctx, 0))) { goto L_8182D590; }
    R(3) = (R(3) + -8);
    GM_TAIL(0x8005FB70u, 0); return;
L_8182D58C:;
    GM_TAIL(0x8005F900u, 0); return;
L_8182D590:;
    R(3) = (0 + 0);
}

/* mod_fn_80125F70 (mod_fn_80125F70, 24 bytes) */
static void mj_mod_fn_80125F70_2d598(GM_CTX) {
    R(3) = ld8(base, (R(3) + 914));
    R(3) = R(3) & 0xF8u;
    R(3) = R(3) ^ 0x8u;
    R(3) = cntlzw(R(3));
    R(3) = rotl32(R(3), 27) & 0x7FFFFFFu;
}

/* mfn_8182DD3C (mfn_8182DD3C, 104 bytes) */
static void mj_mfn_8182DD3C_2dd3c(GM_CTX) {
    GM_FN(0x8182DD3C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x8182DD54u, 0x80050D80u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182DD90; }
    R(3) = (0 + 0);
    st32(base, (R(30) + 276), R(3));
    R(5) = (0 + 0);
    st32(base, (R(30) + 268), R(3));
    st32(base, (R(30) + 4292), R(3));
    st32(base, (R(30) + 4296), R(3));
    st32(base, (R(30) + 4300), R(3));
    st32(base, (R(30) + 4304), R(3));
    st32(base, (R(30) + 236), R(3));
    R(3) = (0 + 0x80370000u);
    R(4) = (R(3) + 26480);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182DD90u, 0x8004E290u, 0);
L_8182DD90:;
    R(0) = lr;
}

/* mod_dAcPy_vf3F8 (mod_dAcPy_vf3F8, 264 bytes) */
static void mj_mod_dAcPy_vf3F8_2ebe4(GM_CTX) {
    GM_FN(0x8182EBE4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = R(3) |R(3);
    R(29) = R(4) |R(4);
    R(30) = R(5) |R(5);
    GM_CALLV(0x8182EC14u, 0x8004DD00u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(27) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182ECC4; }
    R(3) = ld32(base, (R(28) + 4240));
    R(4) = ld32(base, (R(28) + 5344));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8182ECC4; }
    R(26) = ld32(base, (R(28) + 96));
    R(3) = ld32(base, (R(26) + 288));
    ctx->ctr = R(3);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8182EC44u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182ECC4; }
    R(3) = ld32(base, (R(26) + 1104));
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    ctx->ctr = R(3);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8182EC64u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182ECC4; }
    R(4) = ld8(base, (R(28) + 909));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24568));
    R(5) = (0 + 4);
    R(4) = (int8_t)R(4);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x8182EC8Cu, 0x800D8BB0u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -508);
    R(3) = ld8(base, (R(3) + 8));
    R(27) = (0 + 1);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182ECC4; }
    R(3) = R(28) |R(28);
    R(4) = (0 + 4);
    GM_CALLV(0x8182ECB0u, 0x80056CF0u, 0);
    R(6) = R(3) |R(3);
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    GM_CALLV(0x8182ECC4u, 0x818033F4u, 0);
L_8182ECC4:;
    R(3) = R(27) |R(27);
    R(0) = lr;
}

/* mod_fn_80150CD0 (mod_fn_80150CD0, 260 bytes) */
static void mj_mod_fn_80150CD0_2ecec(GM_CTX) {
    GM_FN(0x8182ECEC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 1);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8182ED08u, 0x80056CF0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182EDDC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182ED18u, 0x801502E0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182ED20u, 0x800583A0u, 0);
    R(3) = (R(30) + 5332);
    GM_CALLV(0x8182ED28u, 0x800D7000u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -508);
    R(3) = ld8(base, (R(3) + 4));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182ED54; }
    GM_CALLV(0x8182ED40u, 0x818056E4u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8182ED54; }
    GM_CALLV(0x8182ED4Cu, 0x801021B0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182EDDC; }
L_8182ED54:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 198);
    GM_CALLV(0x8182ED60u, 0x80056CF0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182ED98; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 198);
    GM_CALLV(0x8182ED74u, 0x80056CB0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182ED7Cu, 0x8004E050u, 0);
    R(3) = ld8(base, (R(30) + 909));
    R(4) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(4) + -25384));
    R(6) = (0 + 1);
    { uint32_t s_ = R(3) & 63; R(3) = s_ > 31 ? 0 : R(6) << s_; }
    R(3) = R(3) |R(5);
    st32(base, (R(4) + -25384), R(3));
L_8182ED98:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 199);
    GM_CALLV(0x8182EDA4u, 0x80056CF0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8182EDDC; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 199);
    GM_CALLV(0x8182EDB8u, 0x80056CB0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8182EDC0u, 0x8004E100u, 0);
    R(3) = ld8(base, (R(30) + 909));
    R(4) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(4) + -25384));
    R(6) = (0 + -2);
    R(3) = rotl32(R(6), (R(3) & 31)) & 0xFFFFFFFFu;
    R(3) = R(5) &R(3);
    st32(base, (R(4) + -25384), R(3));
L_8182EDDC:;
    R(0) = lr;
}

/* mfn_8182EDF0 (mfn_8182EDF0, 60 bytes) */
static void mj_mfn_8182EDF0_2edf0(GM_CTX) {
    R(3) = rotl32(R(3), 31) & 0xFFFFFFFFu;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 0))) { goto L_8182EE24; }
    R(5) = (0 + -1);
L_8182EDFC:;
    R(3) = rotl32(R(3), 31) & 0xFFFFFFFFu;
    CR0(ctx, R(3));
    R(4) = R(5) |R(5);
    R(3) = R(3) | 0x40000000u;
    R(5) = (R(5) + 1);
    if ((!CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8182EDFC; }
    cr_cmp_u(ctx, 0, R(5), 0x6u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 1))) return;
    R(3) = (R(4) + 2);
    return;
L_8182EE24:;
    R(3) = (0 + 0);
}

/* mod_fn_80154F60 (mod_fn_80154F60, 6280 bytes) */
static void mj_mod_fn_80154F60_2ef38(GM_CTX) {
    GM_FN(0x8182EF38); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 208);
    R(4) = (R(3) + 0x90000u);
    R(31) = R(3) |R(3);
    R(27) = ld32(base, (R(13) + -22656));
    R(26) = ld32(base, (R(13) + -21688));
    R(3) = ld8(base, (R(4) + 37));
    GM_CALLV(0x8182EFDCu, 0x8005F900u, 0);
    R(29) = R(3) |R(3);
    GM_CALLV(0x8182EFE4u, 0x8005FD20u, 0);
    R(0) = ld8(base, (R(26) + 4622));
    R(28) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22504));
    R(0) = ((int32_t)R(0) * 944);
    R(23) = ld8(base, (R(26) + 4623));
    R(25) = R(3) + R(0);
    R(0) = ld32(base, (R(25) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F00C; }
    goto L_8182F010;
L_8182F00C:;
    R(25) = (0 + 0);
L_8182F010:;
    R(3) = (0 + -1);
    GM_CALLV(0x8182F018u, 0x800B3B50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F028; }
    R(3) = (0 + 1);
    goto L_81830730;
L_8182F028:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F038; }
    R(3) = (0 + 1);
    goto L_81830730;
L_8182F038:;
    R(0) = (0 + 5);
    R(8) = (0 + 0);
    R(5) = (0 + 10);
    R(4) = (0 + 0);
    ctx->ctr = R(0);
    R(0) = R(0) | 0x0u;
L_8182F050:;
    R(0) = ld32(base, (R(13) + -22704));
    R(3) = R(0) + R(8);
    R(6) = (R(3) + 0x90000u);
    R(7) = ld8(base, (R(6) + 484));
    cr_cmp_s(ctx, 0, (int32_t)R(7), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F088; }
    cr_cmp_s(ctx, 0, (int32_t)R(7), 99);
    if ((!CR_BIT(ctx, 0))) { goto L_8182F088; }
    { uint64_t t_ = (uint64_t)(~R(5)) + (R(7)) + 1; R(0) = t_; ctx->xer_ca = (t_ >> 32); }
    R(0) = rotl32(R(7), 1) & 0x1u;
    { uint64_t t_ = (uint64_t)(~R(0)) + (R(4)) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
    R(0) = (R(7) + 1);
    R(0) = R(0) &R(3);
    st8(base, (R(6) + 484), R(0));
L_8182F088:;
    R(0) = ld32(base, (R(13) + -22704));
    R(8) = (R(8) + 1);
    R(3) = R(0) + R(8);
    R(6) = (R(3) + 0x90000u);
    R(7) = ld8(base, (R(6) + 484));
    cr_cmp_s(ctx, 0, (int32_t)R(7), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F0C4; }
    cr_cmp_s(ctx, 0, (int32_t)R(7), 99);
    if ((!CR_BIT(ctx, 0))) { goto L_8182F0C4; }
    { uint64_t t_ = (uint64_t)(~R(5)) + (R(7)) + 1; R(0) = t_; ctx->xer_ca = (t_ >> 32); }
    R(0) = rotl32(R(7), 1) & 0x1u;
    { uint64_t t_ = (uint64_t)(~R(0)) + (R(4)) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
    R(0) = (R(7) + 1);
    R(0) = R(0) &R(3);
    st8(base, (R(6) + 484), R(0));
L_8182F0C4:;
    R(0) = ld32(base, (R(13) + -22704));
    R(8) = (R(8) + 1);
    R(3) = R(0) + R(8);
    R(6) = (R(3) + 0x90000u);
    R(7) = ld8(base, (R(6) + 484));
    cr_cmp_s(ctx, 0, (int32_t)R(7), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F100; }
    cr_cmp_s(ctx, 0, (int32_t)R(7), 99);
    if ((!CR_BIT(ctx, 0))) { goto L_8182F100; }
    { uint64_t t_ = (uint64_t)(~R(5)) + (R(7)) + 1; R(0) = t_; ctx->xer_ca = (t_ >> 32); }
    R(0) = rotl32(R(7), 1) & 0x1u;
    { uint64_t t_ = (uint64_t)(~R(0)) + (R(4)) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
    R(0) = (R(7) + 1);
    R(0) = R(0) &R(3);
    st8(base, (R(6) + 484), R(0));
L_8182F100:;
    R(0) = ld32(base, (R(13) + -22704));
    R(8) = (R(8) + 1);
    R(3) = R(0) + R(8);
    R(6) = (R(3) + 0x90000u);
    R(7) = ld8(base, (R(6) + 484));
    cr_cmp_s(ctx, 0, (int32_t)R(7), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F13C; }
    cr_cmp_s(ctx, 0, (int32_t)R(7), 99);
    if ((!CR_BIT(ctx, 0))) { goto L_8182F13C; }
    { uint64_t t_ = (uint64_t)(~R(5)) + (R(7)) + 1; R(0) = t_; ctx->xer_ca = (t_ >> 32); }
    R(0) = rotl32(R(7), 1) & 0x1u;
    { uint64_t t_ = (uint64_t)(~R(0)) + (R(4)) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
    R(0) = (R(7) + 1);
    R(0) = R(0) &R(3);
    st8(base, (R(6) + 484), R(0));
L_8182F13C:;
    R(8) = (R(8) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8182F050; }
    R(3) = R(27) |R(27);
    GM_CALLV(0x8182F14Cu, 0x80082180u, 0);
    R(3) = R(27) |R(27);
    GM_CALLV(0x8182F154u, 0x800821E0u, 0);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(27) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -344); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(13) + -7040); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -340); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (R(27) + 80); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(27) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 60); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (R(27) + 84); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld8(base, (R(26) + 4620));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F5C4; }
    R(0) = ld8(base, (R(26) + 4621));
    cr_cmp_u(ctx, 0, R(0), 0x17u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F5C4; }
    R(0) = ld8(base, (R(26) + 4622));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F5C4; }
    R(0) = (int16_t)ld16(base, (R(3) + 3040));
    { uint32_t ea_ = (R(29) + 5420); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 5424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (R(29) + 5428); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 128); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_8182F1F0; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8182F29C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8182F348; }
    goto L_8182F3F4;
L_8182F1F0:;
    { uint32_t ea_ = (R(27) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7012); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F28C; }
    { uint32_t ea_ = (R(13) + -7008); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F28C; }
    { uint32_t ea_ = (R(3) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(13) + -7004); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x8182F224u, 0x80154E50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(5) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8182F250; }
    R(3) = ld32(base, (R(13) + -20984));
    R(4) = (0 + 187);
    GM_CALLV(0x8182F23Cu, 0x80195380u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = (int16_t)ld16(base, (R(4) + 3040));
    R(0) = (R(3) + 1);
    st16(base, (R(4) + 3040), R(0));
    goto L_8182F3FC;
L_8182F250:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 3042));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F27C; }
    R(3) = ld32(base, (R(13) + -20984));
    R(4) = (0 + 188);
    R(5) = (0 + 1);
    GM_CALLV(0x8182F270u, 0x80195380u, 0);
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 1);
    st8(base, (R(3) + 3042), R(0));
L_8182F27C:;
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 1);
    st16(base, (R(3) + 2504), R(0));
    goto L_8182F3FC;
L_8182F28C:;
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 0);
    st8(base, (R(3) + 3042), R(0));
    goto L_8182F3FC;
L_8182F29C:;
    { uint32_t ea_ = (R(27) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7000); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F338; }
    { uint32_t ea_ = (R(13) + -6996); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F338; }
    { uint32_t ea_ = (R(3) + 60); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(13) + -6992); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x8182F2D0u, 0x80154E50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(5) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8182F2FC; }
    R(3) = ld32(base, (R(13) + -20984));
    R(4) = (0 + 187);
    GM_CALLV(0x8182F2E8u, 0x80195380u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = (int16_t)ld16(base, (R(4) + 3040));
    R(0) = (R(3) + 1);
    st16(base, (R(4) + 3040), R(0));
    goto L_8182F3FC;
L_8182F2FC:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 3042));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F328; }
    R(3) = ld32(base, (R(13) + -20984));
    R(4) = (0 + 188);
    R(5) = (0 + 1);
    GM_CALLV(0x8182F31Cu, 0x80195380u, 0);
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 1);
    st8(base, (R(3) + 3042), R(0));
L_8182F328:;
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 2);
    st16(base, (R(3) + 2504), R(0));
    goto L_8182F3FC;
L_8182F338:;
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 0);
    st8(base, (R(3) + 3042), R(0));
    goto L_8182F3FC;
L_8182F348:;
    { uint32_t ea_ = (R(27) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -6988); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F3E4; }
    { uint32_t ea_ = (R(13) + -6984); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F3E4; }
    { uint32_t ea_ = (R(13) + -7004); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(13) + -6980); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x8182F37Cu, 0x80154E50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(5) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8182F3A8; }
    R(3) = ld32(base, (R(13) + -20984));
    R(4) = (0 + 187);
    GM_CALLV(0x8182F394u, 0x80195380u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = (int16_t)ld16(base, (R(4) + 3040));
    R(0) = (R(3) + 1);
    st16(base, (R(4) + 3040), R(0));
    goto L_8182F3FC;
L_8182F3A8:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 3042));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F3D4; }
    R(3) = ld32(base, (R(13) + -20984));
    R(4) = (0 + 188);
    R(5) = (0 + 1);
    GM_CALLV(0x8182F3C8u, 0x80195380u, 0);
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 1);
    st8(base, (R(3) + 3042), R(0));
L_8182F3D4:;
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 3);
    st16(base, (R(3) + 2504), R(0));
    goto L_8182F3FC;
L_8182F3E4:;
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 0);
    st8(base, (R(3) + 3042), R(0));
    goto L_8182F3FC;
L_8182F3F4:;
    R(0) = (0 + 0);
    st16(base, (R(3) + 3040), R(0));
L_8182F3FC:;
    { uint32_t ea_ = (R(27) + 56); ctx->f[17].d = ctx->ps1[17] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8182F408u, 0x800789A0u, 0);
    cr_fcmp(ctx, 0, ctx->f[17].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8182F438; }
    { uint32_t ea_ = (R(27) + 56); ctx->f[17].d = ctx->ps1[17] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8182F41Cu, 0x800789A0u, 0);
    { uint32_t ea_ = (R(13) + -6976); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[17].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8182F438; }
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 0);
    st16(base, (R(3) + 2504), R(0));
L_8182F438:;
    R(4) = (R(31) + 0x90000u);
    R(0) = (int16_t)ld16(base, (R(4) + 2504));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F4A4; }
    R(0) = (0 + 2);
    st32(base, (R(13) + -21624), R(0));
    { uint32_t ea_ = (R(13) + -6972); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(13) + -6968); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -412); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + -408); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8182F468u, 0x800789A0u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8182F478u, 0x80078B40u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8182F488u, 0x800789A0u, 0);
    ctx->f[17].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8182F494u, 0x80078B40u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[17].d);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -352); stfs(base, ea_, ctx->f[0].d); }
    goto L_8182F5C4;
L_8182F4A4:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F508; }
    R(0) = (0 + 2);
    st32(base, (R(13) + -21624), R(0));
    { uint32_t ea_ = (R(13) + -6964); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(13) + -6960); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -412); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + -408); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8182F4CCu, 0x800789A0u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8182F4DCu, 0x80078B40u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8182F4ECu, 0x800789A0u, 0);
    ctx->f[17].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8182F4F8u, 0x80078B40u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[17].d);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -352); stfs(base, ea_, ctx->f[0].d); }
    goto L_8182F5C4;
L_8182F508:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F56C; }
    R(0) = (0 + 2);
    st32(base, (R(13) + -21624), R(0));
    { uint32_t ea_ = (R(13) + -6956); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(13) + -6952); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -412); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + -408); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8182F530u, 0x800789A0u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8182F540u, 0x80078B40u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8182F550u, 0x800789A0u, 0);
    ctx->f[17].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8182F55Cu, 0x80078B40u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[17].d);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -352); stfs(base, ea_, ctx->f[0].d); }
    goto L_8182F5C4;
L_8182F56C:;
    R(0) = (0 + 2);
    st32(base, (R(13) + -21624), R(0));
    { uint32_t ea_ = (R(13) + -6948); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(13) + -6944); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -412); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(4) + -408); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8182F58Cu, 0x800789A0u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 48); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8182F59Cu, 0x80078B40u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 52); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8182F5ACu, 0x800789A0u, 0);
    ctx->f[17].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8182F5B8u, 0x80078B40u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[17].d);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -352); stfs(base, ea_, ctx->f[0].d); }
L_8182F5C4:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F858; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 152); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(23) = ld8(base, (R(29) + 841));
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8182F720; }
    R(3) = R(25) |R(25);
    R(4) = R(23) |R(23);
    GM_CALLV(0x8182F5F0u, 0x8008E530u, 0);
    R(5) = (R(31) + 0x90000u);
    R(4) = R(23) |R(23);
    st8(base, (R(5) + 254), R(3));
    R(3) = R(25) |R(25);
    GM_CALLV(0x8182F604u, 0x8008E560u, 0);
    R(5) = (R(31) + 0x90000u);
    R(4) = R(23) |R(23);
    st8(base, (R(5) + 255), R(3));
    R(3) = R(25) |R(25);
    GM_CALLV(0x8182F618u, 0x8008E590u, 0);
    R(4) = (R(31) + 0x90000u);
    st8(base, (R(4) + 256), R(3));
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8182F628u, 0x80078EB0u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = R(23) |R(23);
    { uint32_t ea_ = (R(4) + 152); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8182F638u, 0x80078780u, 0);
    cr_cmp_u(ctx, 0, R(3), 0xFu);
    if ((CR_BIT(ctx, 2))) { goto L_8182F674; }
    R(3) = R(23) |R(23);
    GM_CALLV(0x8182F648u, 0x80078780u, 0);
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 148), R(3));
    { uint32_t ea_ = (R(13) + -6880); ctx->f[2].u = ld64(base, ea_); }
    R(3) = (R(31) + 0x90000u);
    st32(base, (f + 144), R(0));
    { uint32_t ea_ = (R(13) + -6940); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 144); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[0].d); }
    goto L_8182F680;
L_8182F674:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -6936); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[0].d); }
L_8182F680:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 254));
    cr_cmp_u(ctx, 0, R(0), 0x5u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F720; }
    R(0) = (0 + 1);
    st8(base, (R(3) + 33), R(0));
    R(20) = (0 + 0);
    goto L_8182F710;
L_8182F6A0:;
    R(3) = R(23) |R(23);
    R(4) = R(20) & 0xFFu;
    GM_CALLV(0x8182F6ACu, 0x80078830u, 0);
    R(5) = ld8(base, (R(3) + 18));
    R(29) = R(3) |R(3);
    R(4) = (0 + 1);
    R(3) = (0 + 0);
    R(5) = (R(5) + -1);
    GM_CALLV(0x8182F6C4u, 0x802DD1ECu, 0);
    R(5) = ld32(base, (R(13) + -22024));
    R(0) = ld32(base, (R(5) + 0));
    R(5) = ld32(base, (R(5) + 4));
    R(0) = R(3) &R(0);
    R(3) = R(4) &R(5);
    R(0) = R(3) |R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182F70C; }
    R(3) = (R(31) + 0x90000u);
    st8(base, (R(3) + 32), R(20));
    R(0) = ld8(base, (R(29) + 12));
    st8(base, (R(3) + 257), R(0));
    R(0) = ld8(base, (R(29) + 13));
    st8(base, (R(3) + 254), R(0));
    R(0) = ld8(base, (R(29) + 14));
    st8(base, (R(3) + 255), R(0));
    R(0) = ld8(base, (R(29) + 15));
    st8(base, (R(3) + 256), R(0));
    goto L_8182F720;
L_8182F70C:;
    R(20) = (R(20) + 1);
L_8182F710:;
    R(3) = R(23) |R(23);
    GM_CALLV(0x8182F718u, 0x80078800u, 0);
    cr_cmp_u(ctx, 0, R(20), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8182F6A0; }
L_8182F720:;
    R(3) = R(25) |R(25);
    R(4) = R(23) |R(23);
    GM_CALLV(0x8182F72Cu, 0x8008E4D0u, 0);
    R(0) = R(3) |R(3);
    R(3) = R(25) |R(25);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x8182F73Cu, 0x8008E500u, 0);
    R(4) = (R(31) + 0x90000u);
    st8(base, (R(4) + 257), R(3));
    R(3) = R(23) |R(23);
    GM_CALLV(0x8182F74Cu, 0x80078800u, 0);
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 33));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F858; }
    R(4) = ld8(base, (R(3) + 32));
    R(3) = R(23) |R(23);
    GM_CALLV(0x8182F768u, 0x80078830u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(29) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8182F858; }
    R(20) = (R(31) + 0x90000u);
    R(22) = (0 + 0);
    goto L_8182F848;
L_8182F780:;
    R(0) = ld8(base, (R(20) + 32));
    cr_cmp_s(ctx, 0, (int32_t)R(22), (int32_t)R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182F844; }
    R(3) = R(23) |R(23);
    R(4) = R(22) & 0xFFu;
    GM_CALLV(0x8182F798u, 0x80078830u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8182F844; }
    R(5) = ld8(base, (R(3) + 18));
    R(4) = (0 + 1);
    R(3) = (0 + 0);
    R(5) = (R(5) + -1);
    GM_CALLV(0x8182F7B8u, 0x802DD1ECu, 0);
    R(24) = ld32(base, (R(13) + -22024));
    R(6) = ld32(base, (R(24) + 0));
    R(7) = ld32(base, (R(24) + 4));
    R(0) = R(3) &R(6);
    R(5) = R(4) &R(7);
    R(0) = R(5) |R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182F844; }
    R(0) = R(7) |R(4);
    st32(base, (R(24) + 4), R(0));
    R(0) = R(6) |R(3);
    R(4) = (0 + 1);
    st32(base, (R(24) + 0), R(0));
    R(3) = (0 + 0);
    R(5) = ld8(base, (R(29) + 18));
    R(5) = (R(5) + -1);
    GM_CALLV(0x8182F7F8u, 0x802DD1ECu, 0);
    R(0) = ld32(base, (R(24) + 0));
    R(3) = ~(R(3) | R(3));
    R(5) = ld32(base, (R(24) + 4));
    R(4) = ~(R(4) | R(4));
    R(0) = R(0) &R(3);
    R(3) = (R(31) + 0x90000u);
    R(4) = R(5) &R(4);
    st32(base, (R(24) + 4), R(4));
    st32(base, (R(24) + 0), R(0));
    st8(base, (R(3) + 32), R(22));
    R(0) = ld8(base, (R(30) + 12));
    st8(base, (R(3) + 257), R(0));
    R(0) = ld8(base, (R(30) + 13));
    st8(base, (R(3) + 254), R(0));
    R(0) = ld8(base, (R(30) + 14));
    st8(base, (R(3) + 255), R(0));
    R(0) = ld8(base, (R(30) + 15));
    st8(base, (R(3) + 256), R(0));
    goto L_8182F858;
L_8182F844:;
    R(22) = (R(22) + 1);
L_8182F848:;
    R(3) = R(23) |R(23);
    GM_CALLV(0x8182F850u, 0x80078800u, 0);
    cr_cmp_u(ctx, 0, R(22), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8182F780; }
L_8182F858:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -356); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[1].d); }
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8182F888; }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F8D0; }
L_8182F888:;
    GM_CALLV(0x8182F88Cu, 0x8005FFB0u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F8AC; }
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 198));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F8C8; }
L_8182F8AC:;
    GM_CALLV(0x8182F8B0u, 0x8005FC70u, 0);
    GM_CALLV(0x8182F8B4u, 0x8182EDF0u, 0);
    R(4) = (R(31) + 0x90000u);
    st8(base, (R(4) + 37), R(3));
    R(0) = (0 + 0);
    st8(base, (R(4) + 36), R(0));
    goto L_8182F8D0;
L_8182F8C8:;
    R(0) = (0 + 1);
    st8(base, (R(3) + 36), R(0));
L_8182F8D0:;
    R(3) = ld32(base, (R(13) + -22208));
    R(0) = ld8(base, (R(3) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F9D8; }
    R(4) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(4) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F990; }
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + -356); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8182F900u, 0x80079710u, 0);
    R(3) = (R(31) + 0x90000u);
    R(3) = ld8(base, (R(3) + 37));
    GM_CALLV(0x8182F90Cu, 0x8005F900u, 0);
    { uint32_t ea_ = (R(3) + 5420); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 100);
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[0].d); }
    R(5) = (0 + 0);
    { uint32_t ea_ = (R(3) + 5424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 5428); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8182F934u, 0x8007A6C0u, 0);
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 198));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F958; }
    R(0) = ld8(base, (R(3) + 280));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182F958; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8182F958u, 0x80079E80u, 0);
L_8182F958:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -356); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8182F980; }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F9D8; }
L_8182F980:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 3036); stfs(base, ea_, ctx->f[0].d); }
    goto L_8182F9D8;
L_8182F990:;
    { uint32_t ea_ = (R(13) + -7044); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + -356); stfs(base, ea_, ctx->f[0].d); }
    R(4) = (0 + 0);
    GM_CALLV(0x8182F9A4u, 0x8007AB70u, 0);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -356); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8182F9CC; }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182F9D8; }
L_8182F9CC:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7044); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 3036); stfs(base, ea_, ctx->f[0].d); }
L_8182F9D8:;
    R(3) = ld32(base, (R(13) + -22704));
    R(3) = (R(3) + 0x90000u);
    R(0) = ld8(base, (R(3) + 2506));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182F9F4; }
    R(3) = (0 + 1);
    goto L_81830730;
L_8182F9F4:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -372); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -364); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -356); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[5].d);
    { uint32_t ea_ = (R(3) + -376); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -368); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -392); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[2].d - ctx->f[4].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[30].d * ctx->f[1].d);
    { uint32_t ea_ = (R(3) + -384); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -388); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[6].d);
    { uint32_t ea_ = (R(3) + -380); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[30].d * ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[8].d - ctx->f[7].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d * ctx->f[1].d);
    ctx->f[28].d = ctx->ps1[28] = frsp(ctx->f[5].d + ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d * ctx->f[0].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[4].d + ctx->f[3].d);
    ctx->f[27].d = ctx->ps1[27] = frsp(ctx->f[6].d + ctx->f[1].d);
    ctx->f[26].d = ctx->ps1[26] = frsp(ctx->f[7].d + ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182FA6C; }
    { uint32_t ea_ = (R(3) + -368); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + -364); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + -384); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + -380); stfs(base, ea_, ctx->f[7].d); }
L_8182FA6C:;
    R(0) = R(23) & 0xFFu;
    R(3) = (R(31) + 0x90000u);
    R(0) = ((int32_t)R(0) * 400);
    R(22) = (0 + 0);
    R(24) = (0 + 0);
    R(3) = R(3) + R(0);
    R(20) = (R(3) + -28552);
L_8182FA88:;
    R(0) = R(24) & 0xFFu;
    R(3) = R(31) |R(31);
    R(0) = ((int32_t)R(0) * 20);
    R(21) = R(20) + R(0);
    R(4) = R(21) |R(21);
    GM_CALLV(0x8182FAA0u, 0x80156C30u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8182FAC0; }
    R(4) = ld8(base, (R(21) + 17));
    R(3) = (R(31) + 0x90000u);
    R(22) = (0 + 1);
    R(0) = (R(4) + 1);
    st8(base, (R(3) + 276), R(0));
    goto L_8182FACC;
L_8182FAC0:;
    R(24) = (R(24) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(24), 20);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8182FA88; }
L_8182FACC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8182FAD4u, 0x80156D70u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8182FAEC; }
    R(3) = (R(31) + 0x90000u);
    R(0) = (0 + 4);
    st8(base, (R(3) + 276), R(0));
    R(22) = (0 + 1);
L_8182FAEC:;
    R(5) = ld8(base, (R(26) + 4622));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182FC28; }
    R(0) = ld32(base, (R(13) + -21624));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8182FC28; }
    R(3) = ld32(base, (R(25) + 12));
    R(4) = ld8(base, (R(26) + 4625));
    R(0) = ld8(base, (R(3) + 16));
    cr_cmp_u(ctx, 0, R(4), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8182FC28; }
    R(3) = (R(31) + 0x90000u);
    R(6) = ld8(base, (R(3) + 276));
    R(0) = (R(6) + 246);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x5u);
    if ((!CR_BIT(ctx, 1))) { goto L_8182FC28; }
    R(0) = (R(6) + 239);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x6u);
    if ((!CR_BIT(ctx, 1))) { goto L_8182FC28; }
    R(4) = ld8(base, (R(26) + 4620));
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + 23440);
    cr_cmp_u(ctx, 0, R(4), 0x2u);
    R(3) = ld8(base, (R(3) + 13));
    if ((!CR_BIT(ctx, 2))) { goto L_8182FB64; }
    R(0) = ld8(base, (R(26) + 4621));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_8182FC28; }
L_8182FB64:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8182FB78; }
    R(0) = ld8(base, (R(26) + 4621));
    cr_cmp_u(ctx, 0, R(0), 0x29u);
    if ((CR_BIT(ctx, 2))) { goto L_8182FC28; }
L_8182FB78:;
    cr_cmp_u(ctx, 0, R(4), 0x7u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182FB94; }
    R(0) = ld8(base, (R(26) + 4621));
    cr_cmp_u(ctx, 0, R(0), 0x17u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182FB94; }
    cr_cmp_u(ctx, 0, R(5), 0x3u);
    if ((CR_BIT(ctx, 2))) { goto L_8182FC28; }
L_8182FB94:;
    R(0) = (R(3) + 224);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 1))) { goto L_8182FC28; }
    R(0) = ld32(base, (R(13) + -21632));
    cr_cmp_u(ctx, 0, R(0), 0x5Au);
    if ((!CR_BIT(ctx, 0))) { goto L_8182FC28; }
    R(3) = (R(31) + 0x90000u);
    R(4) = ld32(base, (R(13) + -22276));
    R(0) = ld8(base, (R(3) + 198));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182FBD0; }
    R(0) = (0 + 0);
    st8(base, (R(3) + 276), R(0));
    goto L_8182FC28;
L_8182FBD0:;
    R(0) = ld8(base, (R(13) + -21604));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182FC00; }
    R(0) = ld32(base, (R(4) + 2804));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_8182FC00; }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 8);
    st8(base, (R(3) + 276), R(0));
    R(22) = (0 + 1);
    { uint32_t ea_ = (R(3) + 272); stfs(base, ea_, ctx->f[0].d); }
    goto L_8182FC28;
L_8182FC00:;
    cr_cmp_u(ctx, 0, R(6), 0x8u);
    if ((!CR_BIT(ctx, 2))) { goto L_8182FC28; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 272); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182FC28; }
    R(0) = (0 + 0);
    st8(base, (R(3) + 276), R(0));
L_8182FC28:;
    R(4) = (R(31) + 0x90000u);
    R(3) = ld32(base, (R(13) + -23020));
    { uint32_t ea_ = (R(4) + 272); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(13) + -6928); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(24) = ld8(base, (R(4) + 280));
    { uint32_t ea_ = (R(4) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(24), 0);
    { uint32_t ea_ = (R(3) + 52); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[25].d = ctx->ps1[25] = frsp(ctx->f[26].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 48); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_8182FC8C; }
    cr_cmp_s(ctx, 0, (int32_t)R(24), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8182FCCC; }
    cr_cmp_s(ctx, 0, (int32_t)R(24), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8182FD5C; }
    cr_cmp_s(ctx, 0, (int32_t)R(24), 3);
    if ((CR_BIT(ctx, 2))) { goto L_8182FE2C; }
    cr_cmp_s(ctx, 0, (int32_t)R(24), 4);
    if ((CR_BIT(ctx, 2))) { goto L_8182FF04; }
    goto L_8182FF88;
L_8182FC8C:;
    R(0) = ld32(base, (R(3) + 16));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182FF88; }
    { uint32_t ea_ = (R(13) + -7040); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[28].d - ctx->f[26].d);
    R(3) = (0 + 1);
    R(0) = (0 + 6);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[27].d);
    { uint32_t ea_ = (R(4) + 288); stfs(base, ea_, ctx->f[0].d); }
    R(24) = (R(24) + 1);
    st8(base, (R(4) + 279), R(3));
    R(22) = (0 + 1);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d + ctx->f[1].d);
    st8(base, (R(4) + 276), R(0));
    { uint32_t ea_ = (R(4) + 284); stfs(base, ea_, ctx->f[0].d); }
    goto L_8182FF88;
L_8182FCCC:;
    { uint32_t ea_ = (R(13) + -7040); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 284); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[27].d);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 288); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[2].d); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8182FD04; }
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 44);
    { uint32_t ea_ = (R(13) + -6920); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x8182FD04u, 0x8015F140u, 0);
L_8182FD04:;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[25].d - ctx->f[26].d);
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7032); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 40);
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x8182FD1Cu, 0x8015F140u, 0);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (f + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 284); stfs(base, ea_, ctx->f[0].d); }
    R(0) = (0 + 6);
    R(22) = (0 + 1);
    { uint32_t ea_ = (f + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 288); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + 276), R(0));
    R(3) = ld32(base, (R(13) + -23020));
    R(0) = ld32(base, (R(3) + 16));
    R(0) = R(0) & 0x2u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182FF88; }
    R(0) = (0 + 40);
    st32(base, (R(13) + -21352), R(0));
    R(24) = (R(24) + 1);
    goto L_8182FF88;
L_8182FD5C:;
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[25].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8182FD74; }
    R(0) = (0 + 6);
    st8(base, (R(4) + 276), R(0));
    R(22) = (0 + 1);
L_8182FD74:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld32(base, (R(13) + -21352));
    { uint32_t ea_ = (R(3) + 284); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 15);
    { uint32_t ea_ = (R(3) + 288); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 1))) { goto L_8182FDC0; }
    { uint32_t ea_ = (R(13) + -7040); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 88); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[27].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8182FDC0; }
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 44);
    { uint32_t ea_ = (R(13) + -6920); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x8182FDC0u, 0x8015F140u, 0);
L_8182FDC0:;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[25].d - ctx->f[26].d);
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7032); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 40);
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x8182FDD8u, 0x8015F140u, 0);
    R(3) = ld32(base, (R(13) + -21352));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8182FDEC; }
    R(0) = (R(3) + -1);
    st32(base, (R(13) + -21352), R(0));
L_8182FDEC:;
    R(4) = (R(31) + 0x90000u);
    { uint32_t ea_ = (f + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 288); stfs(base, ea_, ctx->f[0].d); }
    R(3) = ld32(base, (R(13) + -23020));
    R(0) = ld32(base, (R(3) + 16));
    R(0) = R(0) & 0x8u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182FF88; }
    R(0) = (0 + 5);
    st8(base, (R(4) + 276), R(0));
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(24) = (R(24) + 1);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[0].d); }
    R(22) = (0 + 2);
    goto L_8182FF88;
L_8182FE2C:;
    { uint32_t ea_ = (R(4) + 284); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 44);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 288); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(13) + -6920); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x8182FE50u, 0x8015F140u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[25].d - ctx->f[26].d);
    { uint32_t ea_ = (f + 92); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 48); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[5].d);
    { uint32_t ea_ = (R(13) + -6916); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[4].d - ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8182FE98; }
    { uint32_t ea_ = (R(13) + -6920); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 40);
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[3].d);
    { uint32_t ea_ = (R(13) + -7032); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d + ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d + ctx->f[0].d);
    GM_CALLV(0x8182FE94u, 0x8015F140u, 0);
    goto L_8182FEB8;
L_8182FE98:;
    { uint32_t ea_ = (R(13) + -6912); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 40);
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[3].d);
    { uint32_t ea_ = (R(13) + -7032); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d + ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d + ctx->f[0].d);
    GM_CALLV(0x8182FEB8u, 0x8015F140u, 0);
L_8182FEB8:;
    R(4) = (R(31) + 0x90000u);
    { uint32_t ea_ = (f + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 284); stfs(base, ea_, ctx->f[0].d); }
    R(0) = (0 + 5);
    R(22) = (0 + 1);
    { uint32_t ea_ = (f + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 288); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(4) + 276), R(0));
    R(3) = ld32(base, (R(13) + -23020));
    R(0) = ld32(base, (R(3) + 16));
    R(0) = R(0) & 0x20u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8182FF88; }
    R(0) = (0 + 7);
    st8(base, (R(4) + 276), R(0));
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(24) = (R(24) + 1);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[0].d); }
    R(22) = (0 + 2);
    goto L_8182FF88;
L_8182FF04:;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[25].d - ctx->f[26].d);
    R(0) = (0 + 7);
    st8(base, (R(4) + 276), R(0));
    R(22) = (0 + 1);
    { uint32_t ea_ = (R(4) + 288); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[5].d);
    { uint32_t ea_ = (R(13) + -6916); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[2].d); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    { uint32_t ea_ = (f + 48); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    if ((!CR_BIT(ctx, 0))) { goto L_8182FF58; }
    { uint32_t ea_ = (R(13) + -6908); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 40);
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(13) + -7032); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d + ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d + ctx->f[0].d);
    GM_CALLV(0x8182FF54u, 0x8015F140u, 0);
    goto L_8182FF7C;
L_8182FF58:;
    { uint32_t ea_ = (R(13) + -6904); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 40);
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(13) + -7032); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d + ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d + ctx->f[0].d);
    GM_CALLV(0x8182FF7Cu, 0x8015F140u, 0);
L_8182FF7C:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (f + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 288); stfs(base, ea_, ctx->f[0].d); }
L_8182FF88:;
    R(0) = R(24) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 1))) { goto L_8182FFA0; }
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((CR_BIT(ctx, 2))) { goto L_8182FFA8; }
    goto L_8182FFB0;
L_8182FFA0:;
    { uint32_t ea_ = (R(13) + -6900); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    goto L_8182FFB4;
L_8182FFA8:;
    { uint32_t ea_ = (R(13) + -6896); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    goto L_8182FFB4;
L_8182FFB0:;
    { uint32_t ea_ = (R(13) + -6892); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
L_8182FFB4:;
    R(3) = (R(31) + 0x90000u);
    R(4) = ld8(base, (R(3) + 276));
    st8(base, (R(3) + 280), R(24));
    R(0) = (R(4) + 246);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x5u);
    if ((!CR_BIT(ctx, 1))) { goto L_81830040; }
    R(0) = (R(4) + 239);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x6u);
    if ((!CR_BIT(ctx, 1))) { goto L_81830040; }
    cr_cmp_s(ctx, 0, (int32_t)R(22), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_81830000; }
    { uint32_t ea_ = (R(13) + -7044); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 48);
    { uint32_t ea_ = (R(13) + -7040); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -6932); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x8182FFFCu, 0x8015F140u, 0);
    goto L_81830014;
L_81830000:;
    { uint32_t ea_ = (R(13) + -7056); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 48);
    { uint32_t ea_ = (R(13) + -7040); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -6932); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x81830014u, 0x8015F140u, 0);
L_81830014:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 280));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830040; }
    { uint32_t ea_ = (f + 48); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7056); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830040; }
    R(0) = (0 + 0);
    st8(base, (R(3) + 276), R(0));
L_81830040:;
    R(0) = R(23) & 0xFFu;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7056); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    ctx->f[21].u = ctx->f[28].u;
    { uint32_t ea_ = (f + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(26) = ((int32_t)R(0) * 8704);
    ctx->f[20].u = ctx->f[28].u;
    { uint32_t ea_ = (R(3) + -404); ctx->f[25].d = ctx->ps1[25] = ldfs(base, ea_); }
    ctx->f[19].u = ctx->f[29].u;
    ctx->f[18].u = ctx->f[29].u;
    { uint32_t ea_ = (R(3) + -400); ctx->f[24].d = ctx->ps1[24] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -412); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -408); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    R(22) = (0 + 0);
    { uint32_t ea_ = (R(3) + 272); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(13) + -6888); ctx->f[17].d = ctx->ps1[17] = ldfs(base, ea_); }
    R(23) = (0 + 0);
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[31].d); }
    R(25) = (0 + 0);
    R(30) = (0 + 0);
    R(21) = (0 + 0);
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[31].d); }
L_8183009C:;
    R(0) = R(21) & 0xFFu;
    R(20) = (0 + 0);
    R(29) = ((int32_t)R(0) * 1088);
L_818300A8:;
    R(3) = ld32(base, (R(13) + -22704));
    R(0) = R(20) & 0xFFu;
    R(4) = ((int32_t)R(0) * 68);
    R(0) = (R(3) + 4216);
    R(0) = R(0) + R(26);
    R(0) = R(0) + R(29);
    { uint32_t ea_ = (R(4) + R(0)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(24) = R(0) + R(4);
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { goto L_81830198; }
    R(3) = R(31) |R(31);
    R(4) = R(24) |R(24);
    R(5) = (f + 20);
    R(6) = (f + 16);
    GM_CALLV(0x818300E4u, 0x80156930u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_81830198; }
    R(3) = ld16(base, (R(24) + 64));
    R(0) = R(3) & 0x10u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81830148; }
    cr_cmp_s(ctx, 0, (int32_t)R(22), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830198; }
    { uint32_t ea_ = (R(24) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = R(3) & 0x100u;
    CR0(ctx, R(0));
    ctx->f[1].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[1].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_81830124; }
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830198; }
L_81830124:;
    { uint32_t ea_ = (f + 80); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830198; }
    { uint32_t ea_ = (R(24) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[21].u = ctx->f[1].u;
    R(22) = (0 + 1);
    ctx->f[25].u = ctx->f[0].u ^ 0x8000000000000000ull;
    goto L_81830198;
L_81830148:;
    cr_cmp_s(ctx, 0, (int32_t)R(23), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830198; }
    { uint32_t ea_ = (R(24) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = R(3) & 0x200u;
    CR0(ctx, R(0));
    ctx->f[1].u = ctx->f[0].u ^ 0x8000000000000000ull;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[26].d);
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_81830178; }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830198; }
L_81830178:;
    { uint32_t ea_ = (f + 80); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830198; }
    { uint32_t ea_ = (R(24) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[20].u = ctx->f[1].u;
    R(23) = (0 + 1);
    ctx->f[24].u = ctx->f[0].u ^ 0x8000000000000000ull;
L_81830198:;
    { uint32_t ea_ = (R(24) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { goto L_81830260; }
    R(3) = R(31) |R(31);
    R(4) = R(24) |R(24);
    R(5) = (f + 12);
    R(6) = (f + 8);
    GM_CALLV(0x818301B8u, 0x80156AB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_81830260; }
    R(3) = ld16(base, (R(24) + 64));
    R(0) = R(3) & 0x40u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81830214; }
    cr_cmp_s(ctx, 0, (int32_t)R(25), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830260; }
    { uint32_t ea_ = (R(24) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = R(3) & 0x100u;
    CR0(ctx, R(0));
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[1].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_818301F4; }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830260; }
L_818301F4:;
    { uint32_t ea_ = (f + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830260; }
    ctx->f[19].u = ctx->f[0].u;
    { uint32_t ea_ = (R(24) + 32); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
    R(25) = (0 + 1);
    goto L_81830260;
L_81830214:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830260; }
    { uint32_t ea_ = (R(24) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = R(3) & 0x200u;
    CR0(ctx, R(0));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[27].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[17].d);
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_81830244; }
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830260; }
L_81830244:;
    { uint32_t ea_ = (f + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830260; }
    ctx->f[18].u = ctx->f[0].u;
    { uint32_t ea_ = (R(24) + 36); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    R(30) = (0 + 1);
L_81830260:;
    R(20) = (R(20) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(20), 16);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818300A8; }
    R(21) = (R(21) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(21), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8183009C; }
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830294; }
    { uint32_t ea_ = (R(3) + 72); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    goto L_8183029C;
L_81830294:;
    { uint32_t ea_ = (R(3) + 88); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
L_8183029C:;
    ctx->f[1].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[25].d);
    if ((!CR_BIT(ctx, 1))) { goto L_818302BC; }
    { uint32_t ea_ = (R(27) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[21].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_818302BC; }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[25].d); }
    goto L_81830314;
L_818302BC:;
    { uint32_t ea_ = (R(27) + 60); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[25].d);
    if ((!CR_BIT(ctx, 1))) { goto L_818302E4; }
    ctx->f[0].d = frsp(ctx->f[0].d);
    { uint32_t ea_ = (R(13) + -6888); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_818302E4; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
L_818302E4:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld32(base, (R(3) + 3032));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((CR_BIT(ctx, 0))) { goto L_81830310; }
    ctx->f[1].u = ctx->f[25].u;
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -6884); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 36);
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x8183030Cu, 0x8015F140u, 0);
    goto L_81830314;
L_81830310:;
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[25].d); }
L_81830314:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830330; }
    { uint32_t ea_ = (f + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 72); stfs(base, ea_, ctx->f[0].d); }
    goto L_81830338;
L_81830330:;
    { uint32_t ea_ = (f + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 88); stfs(base, ea_, ctx->f[0].d); }
L_81830338:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + 72); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 88); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = ld8(base, (R(3) + 36));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_8183036C; }
    { uint32_t ea_ = (R(3) + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    goto L_81830374;
L_8183036C:;
    { uint32_t ea_ = (R(3) + 92); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
L_81830374:;
    ctx->f[1].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[24].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81830394; }
    { uint32_t ea_ = (R(27) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81830394; }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[24].d); }
    goto L_818303F4;
L_81830394:;
    { uint32_t ea_ = (R(27) + 60); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[24].d);
    if ((!CR_BIT(ctx, 0))) { goto L_818303C4; }
    ctx->f[0].d = frsp(ctx->f[0].d);
    { uint32_t ea_ = (R(13) + -6888); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[26].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 0))) { goto L_818303C4; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[26].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
L_818303C4:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld32(base, (R(3) + 3032));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((CR_BIT(ctx, 0))) { goto L_818303F0; }
    ctx->f[1].u = ctx->f[24].u;
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -6884); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 32);
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x818303ECu, 0x8015F140u, 0);
    goto L_818303F4;
L_818303F0:;
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[24].d); }
L_818303F4:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830410; }
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 76); stfs(base, ea_, ctx->f[0].d); }
    goto L_81830418;
L_81830410:;
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[0].d); }
L_81830418:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + 76); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 92); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = ld8(base, (R(3) + 36));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 60); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_8183044C; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x81830448u, 0x80078CE0u, 0);
    goto L_81830454;
L_8183044C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x81830454u, 0x80078CF0u, 0);
L_81830454:;
    ctx->f[0].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[23].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8183047C; }
    { uint32_t ea_ = (R(27) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[19].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8183047C; }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[23].d); }
    goto L_818304D4;
L_8183047C:;
    { uint32_t ea_ = (R(27) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[23].d);
    if ((!CR_BIT(ctx, 1))) { goto L_818304A4; }
    ctx->f[0].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (R(13) + -6888); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_818304A4; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
L_818304A4:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld32(base, (R(3) + 3032));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((CR_BIT(ctx, 0))) { goto L_818304D0; }
    ctx->f[1].u = ctx->f[23].u;
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -6884); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 28);
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x818304CCu, 0x8015F140u, 0);
    goto L_818304D4;
L_818304D0:;
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[23].d); }
L_818304D4:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818304F0; }
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 64); stfs(base, ea_, ctx->f[0].d); }
    goto L_818304F8;
L_818304F0:;
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 80); stfs(base, ea_, ctx->f[0].d); }
L_818304F8:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x81830500u, 0x80078CE0u, 0);
    ctx->f[19].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8183050Cu, 0x80078CF0u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[19].d);
    R(3) = R(31) |R(31);
    ctx->f[19].d = ctx->ps1[19] = frsp(ctx->f[30].d * ctx->f[0].d);
    GM_CALLV(0x8183051Cu, 0x80078CE0u, 0);
    R(3) = (R(31) + 0x90000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[19].d);
    R(0) = ld8(base, (R(3) + 36));
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[0].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830540; }
    { uint32_t ea_ = (R(3) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    goto L_81830548;
L_81830540:;
    { uint32_t ea_ = (R(3) + 84); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
L_81830548:;
    ctx->f[0].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[22].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830570; }
    { uint32_t ea_ = (R(27) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[18].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830570; }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[22].d); }
    goto L_81830598;
L_81830570:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld32(base, (R(3) + 3032));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((CR_BIT(ctx, 0))) { goto L_81830598; }
    ctx->f[1].u = ctx->f[22].u;
    { uint32_t ea_ = (R(13) + -6924); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -6884); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 24);
    { uint32_t ea_ = (R(13) + -7044); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x81830598u, 0x8015F140u, 0);
L_81830598:;
    R(3) = (R(31) + 0x90000u);
    R(0) = ld8(base, (R(3) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818305B4; }
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 68); stfs(base, ea_, ctx->f[0].d); }
    goto L_818305BC;
L_818305B4:;
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 84); stfs(base, ea_, ctx->f[0].d); }
L_818305BC:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + 68); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 84); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[0].d); }
    R(3) = ld32(base, (R(13) + -22208));
    R(0) = ld8(base, (R(3) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818306D0; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x818305F0u, 0x80078A70u, 0);
    ctx->f[17].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x818305FCu, 0x80078C10u, 0);
    R(3) = (R(31) + 0x90000u);
    R(0) = ld32(base, (R(13) + -21624));
    { uint32_t ea_ = (R(3) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[27].d);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    { uint32_t ea_ = (R(3) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[26].d + ctx->f[0].d);
    if ((CR_BIT(ctx, 2))) { goto L_81830654; }
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[17].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8183062C; }
    ctx->f[29].u = ctx->f[17].u;
    goto L_81830638;
L_8183062C:;
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81830638; }
    ctx->f[29].u = ctx->f[1].u;
L_81830638:;
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81830648; }
    ctx->f[28].u = ctx->f[0].u;
    goto L_81830654;
L_81830648:;
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_81830654; }
    ctx->f[28].u = ctx->f[2].u;
L_81830654:;
    { uint32_t ea_ = (R(27) + 96); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (R(13) + -7036); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 100); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(27) + 88); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((CR_BIT(ctx, 2))) { goto L_81830670; }
    ctx->f[29].u = ctx->f[1].u;
L_81830670:;
    { uint32_t ea_ = (R(27) + 92); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -7036); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((CR_BIT(ctx, 2))) { goto L_81830684; }
    ctx->f[28].u = ctx->f[1].u;
L_81830684:;
    { uint32_t ea_ = (R(27) + 120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -7040); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[29].d + ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[27].d);
    { uint32_t ea_ = (R(27) + 56); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[26].d);
    { uint32_t ea_ = (R(27) + 124); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[28].d + ctx->f[2].d);
    { uint32_t ea_ = (R(27) + 60); stfs(base, ea_, ctx->f[2].d); }
    st32(base, (R(3) + 3028), R(28));
    { uint32_t ea_ = (R(27) + 64); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (R(27) + 68); stfs(base, ea_, ctx->f[26].d); }
    { uint32_t ea_ = (R(27) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[1].d);
    { uint32_t ea_ = (R(27) + 72); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(27) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(27) + 76); stfs(base, ea_, ctx->f[0].d); }
L_818306D0:;
    R(0) = ld8(base, (R(13) + -22918));
    R(0) = R(0) & 0xFu;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_818306FC; }
    R(3) = (R(31) + 0x90000u);
    R(3) = (R(3) + 2640);
    GM_CALLV(0x818306E8u, 0x80087890u, 0);
    R(3) = (R(31) + 0x90000u);
    R(3) = (R(3) + 2732);
    GM_CALLV(0x818306F4u, 0x800D8670u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x818306FCu, 0x80078300u, 0);
L_818306FC:;
    R(3) = (R(31) + 0x90000u);
    R(3) = (R(3) + 2912);
    GM_CALLV(0x81830708u, 0x8007E4E0u, 0);
    R(3) = (R(31) + 0x90000u);
    R(3) = (R(3) + 2752);
    GM_CALLV(0x81830714u, 0x80089B60u, 0);
    R(4) = (R(31) + 0x90000u);
    R(3) = ld32(base, (R(4) + 3032));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 100);
    if ((!CR_BIT(ctx, 0))) { goto L_8183072C; }
    R(0) = (R(3) + 1);
    st32(base, (R(4) + 3032), R(0));
L_8183072C:;
    R(3) = (0 + 1);
L_81830730:;
    R(11) = (f + 208);
    R(0) = lr;
}

/* mod_fn_80156820 (mod_fn_80156820, 104 bytes) */
static void mj_mod_fn_80156820_307c0(GM_CTX) {
    GM_FN(0x818307C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    GM_CALLV(0x818307D8u, 0x8005FC70u, 0);
    R(4) = (0 + 8);
    ctx->ctr = R(4);
    R(4) = (0 + 0);
L_818307E4:;
    { uint32_t s_ = R(4) & 63; R(5) = s_ > 31 ? 0 : R(3) >> s_; }
    R(5) = R(5) & 0x1u;
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_818307FC; }
    cr_cmp_u(ctx, 0, R(30), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183080C; }
    R(30) = (R(30) + -1);
L_818307FC:;
    R(4) = (R(4) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818307E4; }
    R(3) = (0 + 0);
    goto L_81830814;
L_8183080C:;
    R(3) = R(4) |R(4);
    GM_CALLV(0x81830814u, 0x8005F900u, 0);
L_81830814:;
    R(0) = lr;
}

/* mod_fn_801568D0 (mod_fn_801568D0, 72 bytes) */
static void mj_mod_fn_801568D0_30828(GM_CTX) {
    GM_FN(0x81830828); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x81830838u, 0x8005FC70u, 0);
    R(4) = (0 + 8);
    R(5) = (0 + 0);
    ctx->ctr = R(4);
    R(4) = (0 + 0);
L_81830848:;
    { uint32_t s_ = R(5) & 63; R(6) = s_ > 31 ? 0 : R(3) >> s_; }
    R(6) = R(6) & 0x1u;
    R(4) = R(6) + R(4);
    R(5) = (R(5) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81830848; }
    R(3) = R(4) |R(4);
    R(0) = lr;
}

/* mod_fn_80156C30 (mod_fn_80156C30, 312 bytes) */
static void mj_mod_fn_80156C30_309e4(GM_CTX) {
    GM_FN(0x818309E4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(26) = R(3) |R(3);
    R(27) = R(4) |R(4);
    GM_CALLV(0x81830A04u, 0x801568D0u, 0);
    R(31) = R(3) |R(3);
    R(29) = (0 + 0);
    R(30) = (0 + 0);
    R(28) = (0 + 0);
L_81830A14:;
    R(3) = R(26) |R(26);
    R(4) = R(28) |R(28);
    GM_CALLV(0x81830A20u, 0x80156820u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81830A84; }
    { uint32_t ea_ = (R(3) + 5420); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 5424); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 5428); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[1].d); }
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830A84; }
    { uint32_t ea_ = (R(27) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830A84; }
    { uint32_t ea_ = (R(27) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830A84; }
    { uint32_t ea_ = (R(27) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81830A84; }
    R(30) = (R(30) + 1);
L_81830A84:;
    R(28) = (R(28) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81830A14; }
    R(0) = ld8(base, (R(27) + 16));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81830AAC; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81830B00; }
    R(29) = (0 + 1);
    goto L_81830B00;
L_81830AAC:;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81830AD8; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), (int32_t)R(31));
    if ((!CR_BIT(ctx, 2))) { goto L_81830B00; }
    GM_CALLV(0x81830AC0u, 0x8005FD20u, 0);
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(0) = rotl32(R(0), 27) & 0x7FFFFFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81830B00; }
    R(29) = (0 + 1);
    goto L_81830B00;
L_81830AD8:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81830B00; }
    GM_CALLV(0x81830AE4u, 0x8005FD20u, 0);
    R(0) = R(3) ^ 0x1u;
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0x1u) != 0; R(4) = (v_ >> 1); }
    R(0) = R(0) &R(3);
    R(0) = R(4) - R(0);
    R(0) = rotl32(R(0), 1) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81830B00; }
    R(29) = (0 + 1);
L_81830B00:;
    R(11) = (f + 48);
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* mod_fn_80156EA0 (mod_fn_80156EA0, 56 bytes) */
static void mj_mod_fn_80156EA0_310fc(GM_CTX) {
    GM_FN(0x818310FC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 4904);
    GM_CALLV(0x81831114u, 0x801628C0u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8183111Cu, 0x80156ED0u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_801576E0 (mod_fn_801576E0, 56 bytes) */
static void mj_mod_fn_801576E0_314e4(GM_CTX) {
    GM_FN(0x818314E4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 2192);
    GM_CALLV(0x818314FCu, 0x801628C0u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x81831504u, 0x80157710u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mfn_81832A24 (mfn_81832A24, 540 bytes) */
static void mj_mfn_81832A24_32a24(GM_CTX) {
    GM_FN(0x81832A24); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x81850000u);
    R(6) = (0 + 0x81860000u);
    R(7) = (0 + 0x81850000u);
    R(17) = (R(7) + -3968);
    R(18) = (R(6) + -508);
    R(19) = (R(5) + -4032);
    R(20) = (R(4) + -4);
    R(23) = (0 + 0);
    R(24) = (0 + 1);
    R(25) = (0 + 0);
    R(26) = (0 + 8);
    R(27) = (0 + 0);
    R(28) = (f + 16);
    R(29) = (f + 20);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(22) = (R(30) + 1212);
    R(21) = (R(30) + 1632);
    R(15) = (R(30) + 1059);
    st32(base, (f + 24), R(3));
L_81832AC4:;
    R(5) = ld8(base, (R(30) + 1676));
    R(16) = (R(15) + 1);
    { uint32_t ea_ = R(20) + 4; R(3) = ld32(base, ea_); R(20) = ea_; }
    { uint32_t ea_ = R(21) + 4; R(4) = ld32(base, ea_); R(21) = ea_; }
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    st32(base, (f + 20), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81832AE8; }
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81832BC0; }
L_81832AE8:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(4));
    st32(base, (R(21) + 0), R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_81832B24; }
    R(4) = ld8(base, (R(15) + 1));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81832B24; }
    R(4) = ld32(base, (R(19) + R(23)));
    R(3) = R(30) |R(30);
    GM_CALLV(0x81832B0Cu, 0x801590B0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 15);
    if ((!CR_BIT(ctx, 2))) { goto L_81832B1C; }
    R(3) = (0 + 0);
L_81832B1C:;
    st8(base, (R(15) + 1), R(3));
    R(3) = ld32(base, (f + 20));
L_81832B24:;
    R(4) = ld8(base, (R(18) + 5));
    cr_cmp_u(ctx, 1, R(3), 0x0u);
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81832B58; }
    if ((!CR_BIT(ctx, 6))) { goto L_81832B58; }
    R(3) = ld8(base, (R(15) + 609));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81832B7C; }
    R(3) = R(30) |R(30);
    R(4) = R(27) |R(27);
    GM_CALLV(0x81832B50u, 0x80159250u, 0);
    st8(base, (R(15) + 609), R(24));
    goto L_81832B7C;
L_81832B58:;
    if ((!CR_BIT(ctx, 6))) { goto L_81832B60; }
    if ((CR_BIT(ctx, 2))) { goto L_81832B7C; }
L_81832B60:;
    R(3) = ld8(base, (R(15) + 609));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81832B7C; }
    R(3) = R(30) |R(30);
    R(4) = R(27) |R(27);
    GM_CALLV(0x81832B78u, 0x801594E0u, 0);
    st8(base, (R(15) + 609), R(25));
L_81832B7C:;
    R(3) = ld32(base, (f + 20));
    R(4) = ld8(base, (R(18) + 5));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 99);
    R(3) = (0 + 4);
    if ((CR_BIT(ctx, 1))) { goto L_81832B94; }
    R(3) = (0 + 2);
L_81832B94:;
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81832BA0; }
    R(3) = (0 + 2);
L_81832BA0:;
    R(4) = ld32(base, (R(17) + R(23)));
    R(6) = (0 + 0);
    st32(base, (f + 16), R(3));
    R(3) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(5) = ld32(base, (R(22) + R(3)));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x81832BC0u, 0x800B3B60u, 0);
L_81832BC0:;
    R(26) = (R(26) + -1);
    R(27) = (R(27) + 1);
    cr_cmp_u(ctx, 0, R(26), 0x0u);
    R(23) = (R(23) + 4);
    R(15) = R(16) |R(16);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81832AC4; }
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 24));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81832C3C; }
    R(0) = lr;
    return;
L_81832C3C:;
    GM_CALLV(0x81832C40u, 0x81844FCCu, 0);
}

/* mfn_81833024 (mfn_81833024, 36 bytes) */
static void mj_mfn_81833024_33024(GM_CTX) {
    GM_FN(0x81833024); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (R(3) + 24);
    GM_CALLV(0x81833038u, 0x8015FAE0u, 0);
    R(0) = lr;
}

/* mfn_818330D8 (mfn_818330D8, 92 bytes) */
static void mj_mfn_818330D8_330d8(GM_CTX) {
    GM_FN(0x818330D8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(4) + 0));
    R(30) = R(4) |R(4);
    R(3) = ld32(base, (R(3) + 12));
    ctx->ctr = R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x81833108u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8183311C; }
    R(3) = (R(29) + 4);
    st32(base, (R(29) + 12), R(30));
L_8183311C:;
    R(0) = lr;
}

/* mfn_81833180 (mfn_81833180, 84 bytes) */
static void mj_mfn_81833180_33180(GM_CTX) {
    GM_FN(0x81833180); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld32(base, (R(3) + 8));
    R(3) = ld32(base, (R(3) + 4));
    R(5) = ld32(base, (R(4) + 16));
    R(6) = ld32(base, (R(4) + 12));
    R(4) = ld32(base, (R(4) + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(3) = R(3) + R(6);
    if ((CR_BIT(ctx, 0))) { goto L_818331BC; }
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(5) = R(3) + R(5);
    R(5) = ld32(base, (R(5) + 96));
    R(4) = ld32(base, (R(5) + R(4)));
L_818331BC:;
    ctx->ctr = R(4);
    GM_CALLV(0x818331C4u, ctx->ctr, 0);
    R(0) = lr;
}

/* mfn_818331D4 (mfn_818331D4, 84 bytes) */
static void mj_mfn_818331D4_331d4(GM_CTX) {
    GM_FN(0x818331D4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ld32(base, (R(3) + 8));
    R(3) = ld32(base, (R(3) + 4));
    R(5) = ld32(base, (R(4) + 28));
    R(6) = ld32(base, (R(4) + 24));
    R(4) = ld32(base, (R(4) + 32));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(3) = R(3) + R(6);
    if ((CR_BIT(ctx, 0))) { goto L_81833210; }
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(5) = R(3) + R(5);
    R(5) = ld32(base, (R(5) + 96));
    R(4) = ld32(base, (R(5) + R(4)));
L_81833210:;
    ctx->ctr = R(4);
    GM_CALLV(0x81833218u, ctx->ctr, 0);
    R(0) = lr;
}

/* mod_fn_8015D710 (mod_fn_8015D710, 828 bytes) */
static void mj_mod_fn_8015D710_3327c(GM_CTX) {
    GM_FN(0x8183327C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    st32(base, (f + 44), R(3));
    R(3) = (0 + 0x81860000u);
    R(3) = ld8(base, (R(3) + -1831));
    R(4) = (R(3) + -1);
    R(4) = R(4) & 0xFFu;
    cr_cmp_u(ctx, 0, R(4), 0xEu);
    if ((CR_BIT(ctx, 1))) { goto L_818332F4; }
    R(3) = (R(3) + -2);
    R(4) = (0 + 0x80430000u);
    st32(base, (R(4) + -24072), R(3));
    R(3) = (0 + 1);
L_818332E8:;
    R(4) = (0 + 0);
    GM_CALLV(0x818332F0u, 0x818151B4u, 0);
    goto L_8183355C;
L_818332F4:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld8(base, (R(3) + -1830));
    R(4) = (R(3) + -1);
    R(4) = R(4) & 0xFFu;
    cr_cmp_u(ctx, 0, R(4), 0x40u);
    if ((CR_BIT(ctx, 1))) { goto L_81833320; }
    R(3) = (R(3) + -2);
    R(4) = (0 + 0x80430000u);
    st32(base, (R(4) + -24072), R(3));
    GM_CALLV(0x8183331Cu, 0x8181532Cu, 0);
    goto L_8183355C;
L_81833320:;
    R(29) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(29) + -1668));
    R(30) = (0 + 0);
    R(3) = (0 + 0);
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81833348; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24536));
    GM_CALLV(0x81833344u, 0x81812C98u, 0);
    R(3) = ld8(base, (R(29) + -1668));
L_81833348:;
    R(4) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(4) + -1669));
    st32(base, (f + 36), R(30));
    R(4) = R(3) + R(4);
    CR0(ctx, R(4));
    st32(base, (f + 32), R(30));
    if ((CR_BIT(ctx, 2))) { goto L_818334A0; }
    cr_cmp_u(ctx, 0, R(4), 0x8u);
    R(5) = (0 + 8);
    if ((CR_BIT(ctx, 0))) { goto L_81833370; }
    R(4) = (0 + 8);
L_81833370:;
    R(11) = (0 + 0x81860000u);
    R(12) = (0 + 0x81860000u);
    R(24) = ld8(base, (R(11) + -1666));
    R(10) = (0 + 0x80430000u);
    R(22) = ld8(base, (R(12) + -1665));
    R(9) = (0 + 0x81860000u);
    R(25) = ld32(base, (R(10) + -24708));
    R(30) = (0 + 0x81850000u);
    R(28) = (0 + 0x81860000u);
    R(9) = ld8(base, (R(9) + -1667));
    R(26) = (0 + 0x81860000u);
    R(29) = (0 + 0x81850000u);
    R(11) = (R(30) + 14865);
    R(30) = (R(28) + -5828);
    R(28) = (R(26) + -5796);
    R(26) = R(24) & 0x1u;
    CR0(ctx, R(26));
    R(27) = (0 + 0x81860000u);
    R(23) = (0 + 0x81860000u);
    R(12) = (R(29) + -25628);
    CR_SET(ctx, 1, (ctx->cr >> 28) & 0xF);
    R(24) = R(22) & 0x1u;
    CR0(ctx, R(24));
    R(6) = (0 + 0);
    R(7) = (f + 32);
    R(8) = (0 + 1);
    R(10) = (0 + 3);
    R(29) = (R(27) + -6000);
    R(27) = (R(23) + -5764);
    R(0) = (R(12) + -4);
    R(26) = (R(25) + 2892);
    R(25) = (R(25) + 900);
    R(24) = (0 + 0);
L_818333EC:;
    cr_cmp_u(ctx, 6, R(24), R(3));
    R(23) = rotl32(R(24), 2) & 0xFFFFFFFCu;
    cr_cmp_u(ctx, 5, R(24), 0x4u);
    if ((!CR_BIT(ctx, 24))) { goto L_81833408; }
    if ((CR_BIT(ctx, 20))) { goto L_81833460; }
    R(23) = R(26) + R(23);
    goto L_81833464;
L_81833408:;
    R(22) = ld8(base, (R(11) + R(24)));
    cr_cmp_u(ctx, 6, R(22), 0x7u);
    if ((CR_BIT(ctx, 25))) { goto L_81833420; }
    R(21) = ld8(base, (R(7) + R(22)));
    cr_cmp_u(ctx, 6, R(21), 0x1u);
    if ((!CR_BIT(ctx, 26))) { goto L_81833440; }
L_81833420:;
    R(21) = R(0) |R(0);
    ctx->ctr = R(5);
L_81833428:;
    { uint32_t ea_ = R(21) + 4; R(22) = ld32(base, ea_); R(21) = ea_; }
    R(20) = ld8(base, (R(7) + R(22)));
    cr_cmp_u(ctx, 6, R(20), 0x1u);
    if ((!CR_BIT(ctx, 26))) { goto L_81833440; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81833428; }
    R(22) = ld32(base, (R(12) + 32));
L_81833440:;
    st8(base, (R(7) + R(22)), R(8));
    st32(base, (R(30) + R(23)), R(22));
    R(22) = rotl32(R(22), 2) & 0xFFFFFFFCu;
    st32(base, (R(29) + R(23)), R(8));
    st32(base, (R(28) + R(22)), R(9));
    if ((CR_BIT(ctx, 20))) { goto L_8183346C; }
    R(23) = R(26) + R(23);
    goto L_81833470;
L_81833460:;
    R(23) = R(25) + R(23);
L_81833464:;
    st32(base, (R(23) + 0), R(6));
    goto L_81833494;
L_8183346C:;
    R(23) = R(25) + R(23);
L_81833470:;
    st32(base, (R(23) + 0), R(10));
    if ((CR_BIT(ctx, 6))) { goto L_81833484; }
    R(23) = ld32(base, (R(27) + R(22)));
    R(23) = R(23) | 0x1u;
    st32(base, (R(27) + R(22)), R(23));
L_81833484:;
    if ((CR_BIT(ctx, 2))) { goto L_81833494; }
    R(23) = ld32(base, (R(27) + R(22)));
    R(23) = R(23) | 0x2u;
    st32(base, (R(27) + R(22)), R(23));
L_81833494:;
    R(24) = (R(24) + 1);
    cr_cmp_u(ctx, 5, R(24), R(4));
    if ((!CR_BIT(ctx, 22))) { GM_LOOP(); goto L_818333EC; }
L_818334A0:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld8(base, (R(3) + -1664));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818334C0; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24708));
    GM_CALLV(0x818334BCu, 0x800BB880u, 0);
    goto L_8183355C;
L_818334C0:;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -1663));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818334E0; }
    R(3) = (0 + 8);
    R(5) = (0 + 0);
    GM_CALLV(0x818334DCu, 0x800E1E60u, 0);
    goto L_8183355C;
L_818334E0:;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -1672));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818335AC; }
    R(3) = (0 + 0x81860000u);
    R(5) = ld8(base, (R(3) + -1670));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818335AC; }
    R(7) = (0 + 0x81850000u);
    R(5) = (R(5) + -1);
    R(7) = ld8(base, (R(7) + 14864));
    R(3) = (0 + 0x80430000u);
    st8(base, (f + 22), R(5));
    R(5) = (0 + 0x81860000u);
    R(5) = ld8(base, (R(5) + -1671));
    R(4) = (R(4) + -1);
    R(3) = ld32(base, (R(3) + -24708));
    R(6) = (0 + 0);
    st8(base, (f + 28), R(4));
    st8(base, (f + 30), R(4));
    R(4) = (R(7) + -1);
    st8(base, (f + 21), R(4));
    R(4) = (R(5) + -1);
    st8(base, (f + 29), R(4));
    st8(base, (f + 31), R(4));
    R(4) = (f + 16);
    st32(base, (f + 16), R(6));
    st8(base, (f + 20), R(6));
    st8(base, (f + 23), R(6));
    st32(base, (f + 24), R(6));
    GM_CALLV(0x8183355Cu, 0x800BB780u, 0);
L_8183355C:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 44));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_818335B4; }
    R(0) = lr;
    return;
L_818335AC:;
    R(3) = (0 + 0);
    GM_LOOP(); goto L_818332E8;
L_818335B4:;
    GM_CALLV(0x818335B8u, 0x81844FCCu, 0);
}

/* mod_fn_3_1C070 (mod_fn_3_1C070, 1124 bytes) */
static void mj_mod_fn_3_1C070_339f4(GM_CTX) {
    GM_FN(0x818339F4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(31) = (0 + 0x80AD0000u);
    R(31) = (R(31) + -7536);
    R(30) = R(3) |R(3);
    R(29) = ld32(base, (R(4) + -25136));
    R(3) = ld32(base, (R(3) + 1724));
    cr_cmp_u(ctx, 0, R(29), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81833A70; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81833A50; }
    { uint32_t a_ = R(3); R(5) = a_ + 0x64u; ctx->xer_ca = R(5) < a_; }
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81833A44; }
    R(5) = (R(5) + -100);
L_81833A44:;
    R(3) = (R(3) + 100);
    R(4) = (R(30) + 1724);
    GM_CALLV(0x81833A50u, 0x80161800u, 0);
L_81833A50:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81833A70; }
    { uint32_t a_ = R(29); R(5) = a_ + 0x64u; ctx->xer_ca = R(5) < a_; }
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81833A64; }
    R(5) = (R(5) + -100);
L_81833A64:;
    R(3) = (R(29) + 100);
    R(4) = (R(30) + 1724);
    GM_CALLV(0x81833A70u, 0x80161750u, 0);
L_81833A70:;
    R(3) = ld32(base, (R(30) + 1724));
    R(4) = (0 + 0);
    GM_CALLV(0x81833A7Cu, 0x80078520u, 0);
    R(4) = (R(30) + 1688);
    GM_CALLV(0x81833A84u, 0x80014820u, 0);
    R(28) = ld32(base, (R(30) + 4));
    R(3) = (R(31) + 8);
    { uint32_t ea_ = (R(30) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(29) = (0 + 8);
    { uint32_t ea_ = (R(30) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(11) = R(28) & 0x1Fu;
    { uint32_t ea_ = (R(30) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(10) = rotl32(R(28), 27) & 0x7u;
    { uint32_t ea_ = (R(3) + 4); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(9) = rotl32(R(28), 24) & 0x3u;
    { uint32_t ea_ = (R(31) + 8); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    R(8) = rotl32(R(28), 1) & 0x1u;
    { uint32_t ea_ = (R(3) + 12); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(7) = R(28) & 0x8000u;
    { uint32_t ea_ = (R(3) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(6) = rotl32(R(28), 3) & 0x3u;
    R(5) = rotl32(R(28), 8) & 0x3u;
    R(0) = (0 + 1);
    st16(base, (R(30) + 868), R(29));
    R(3) = (0 + 0x80430000u);
    R(4) = (0 + 0);
    { uint32_t ea_ = (R(30) + 2016); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 2020); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 2024); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(30) + 2048), R(11));
    st32(base, (R(30) + 2052), R(10));
    st32(base, (R(30) + 2056), R(9));
    st8(base, (R(30) + 840), R(8));
    st32(base, (R(30) + 2044), R(7));
    st8(base, (R(30) + 2084), R(6));
    st8(base, (R(30) + 1638), R(5));
    { uint32_t ea_ = (R(30) + 800); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(30) + 804); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(30) + 792); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(30) + 796); stfs(base, ea_, ctx->f[3].d); }
    st32(base, (R(30) + 308), R(0));
    R(3) = ld32(base, (R(3) + -24576));
    GM_CALLV(0x81833B1Cu, 0x800D87B0u, 0);
    R(0) = rotl32(R(28), 9) & 0x1u;
    CR0(ctx, R(0));
    st8(base, (R(30) + 2080), R(3));
    R(0) = rotl32(R(28), 16) & 0xFu;
    st8(base, (R(30) + 2083), R(0));
    st8(base, (R(30) + 909), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_81833B38; }
    st32(base, (R(30) + 2052), R(29));
L_81833B38:;
    R(3) = ld8(base, (R(30) + 2083));
    GM_CALLV(0x81833B40u, 0x8005F900u, 0);
    { uint32_t ea_ = (R(3) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(30) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 100); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    st8(base, (R(30) + 2077), R(0));
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_81833B6C; }
    R(0) = (0 + 0);
    st8(base, (R(30) + 2077), R(0));
L_81833B6C:;
    R(4) = R(30) |R(30);
    R(3) = (R(30) + 492);
    R(6) = (R(31) + 36);
    R(5) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x81833B84u, 0x8006D090u, 0);
    R(0) = ld32(base, (R(30) + 2052));
    R(4) = (R(31) + 80);
    { uint32_t ea_ = (R(30) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(30) + 1688);
    R(0) = rotl32(R(0), 1) & 0xFFFFFFFEu;
    R(5) = ld8(base, (R(30) + 2083));
    R(0) = ld16(base, (R(4) + R(0)));
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(30) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0);
    st8(base, (R(30) + 644), R(5));
    st16(base, (R(30) + 1696), R(0));
    { uint32_t ea_ = (R(30) + 1700); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 1704); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81833BC0u, 0x80014660u, 0);
    { uint32_t ea_ = (R(30) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(29) = (0 + 0);
    { uint32_t ea_ = (R(31) + 104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 2);
    { uint32_t ea_ = (R(30) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 100); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st8(base, (R(30) + 2079), R(0));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 176); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 172); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 1584); stfs(base, ea_, ctx->f[1].d); }
    st16(base, (R(30) + 2070), R(29));
    st16(base, (R(30) + 2060), R(29));
    st16(base, (R(30) + 2066), R(29));
    st8(base, (R(30) + 2076), R(29));
    GM_CALLV(0x81833C08u, 0x80021690u, 0);
    R(3) = ld32(base, (R(30) + 2048));
    R(0) = (0 + 1);
    st8(base, (R(30) + 1663), R(0));
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    st8(base, (R(30) + 2082), R(29));
    st32(base, (R(30) + 1608), R(29));
    if ((CR_BIT(ctx, 2))) { goto L_81833C2C; }
    cr_cmp_u(ctx, 0, R(3), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_81833C58; }
L_81833C2C:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x81833C38u, 0x809BF5D0u, 0);
    R(0) = ld32(base, (R(30) + 2048));
    R(3) = (0 + 1);
    st8(base, (R(30) + 2082), R(3));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_81833CAC; }
    R(0) = (0 + 8);
    st16(base, (R(30) + 1280), R(0));
    goto L_81833CAC;
L_81833C58:;
    cr_cmp_u(ctx, 0, R(3), 0x1Au);
    if ((!CR_BIT(ctx, 2))) { goto L_81833C74; }
    R(3) = (0 + 5);
    R(0) = (0 + 15);
    st16(base, (R(30) + 2060), R(3));
    st32(base, (R(30) + 2048), R(0));
    goto L_81833CAC;
L_81833C74:;
    cr_cmp_u(ctx, 0, R(3), 0x15u);
    if ((!CR_BIT(ctx, 2))) { goto L_81833CAC; }
    R(0) = ld8(base, (R(30) + 2083));
    R(3) = R(30) |R(30);
    R(4) = (int8_t)R(0);
    GM_CALLV(0x81833C8Cu, 0x80022180u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81833CA4; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x81833CA0u, 0x809BF5D0u, 0);
    goto L_81833CAC;
L_81833CA4:;
    R(0) = (0 + 8);
    st32(base, (R(30) + 2048), R(0));
L_81833CAC:;
    R(0) = ld32(base, (R(30) + 2048));
    R(3) = (R(31) + 48);
    R(4) = (0 + 0);
    R(0) = ld8(base, (R(3) + R(0)));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81833CD4; }
    R(0) = ld8(base, (R(30) + 2084));
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_81833CD4; }
    R(4) = (0 + 1);
L_81833CD4:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_81833D14; }
    R(4) = R(30) |R(30);
    R(3) = (R(30) + 492);
    R(5) = (R(31) + 24);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x81833CF4u, 0x8006D090u, 0);
    R(12) = ld32(base, (R(30) + 96));
    R(4) = (0 + 0x80350000u);
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 212));
    R(4) = (R(4) + 10868);
    ctx->ctr = R(12);
    GM_CALLV(0x81833D10u, ctx->ctr, 0);
    goto L_81833D5C;
L_81833D14:;
    R(0) = ld32(base, (R(30) + 2056));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81833D40; }
    R(12) = ld32(base, (R(30) + 96));
    R(4) = (0 + 0x80B10000u);
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 212));
    R(4) = (R(4) + 9720);
    ctx->ctr = R(12);
    GM_CALLV(0x81833D3Cu, ctx->ctr, 0);
    goto L_81833D5C;
L_81833D40:;
    R(12) = ld32(base, (R(30) + 96));
    R(4) = (0 + 0x80350000u);
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 212));
    R(4) = (R(4) + 10804);
    ctx->ctr = R(12);
    GM_CALLV(0x81833D5Cu, ctx->ctr, 0);
L_81833D5C:;
    R(0) = ld8(base, (R(30) + 2084));
    { uint32_t ea_ = (R(31) + 108); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    { uint32_t ea_ = (R(30) + 220); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 224); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 228); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_81833D84; }
    R(0) = (0 + 1);
    st8(base, (R(30) + 1673), R(0));
    st8(base, (R(30) + 1674), R(0));
L_81833D84:;
    { uint32_t ea_ = (R(30) + 220); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    R(10) = (0 + 0x80020000u);
    { uint32_t ea_ = (R(30) + 224); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(9) = (0 + 0x80020000u);
    { uint32_t ea_ = (R(30) + 228); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(10) = (R(10) + 3424);
    { uint32_t ea_ = (R(31) + 112); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(9) = (R(9) + 3744);
    { uint32_t ea_ = (R(31) + 104); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(31) + 100); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = R(30) |R(30);
    { uint32_t ea_ = (R(31) + 116); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(30) + 1732);
    { uint32_t ea_ = (R(30) + 2004); stfs(base, ea_, ctx->f[6].d); }
    R(5) = (R(30) + 1960);
    R(7) = ld8(base, (R(30) + 911));
    R(8) = (R(30) + 2004);
    { uint32_t ea_ = (R(30) + 2008); stfs(base, ea_, ctx->f[5].d); }
    R(6) = (0 + 3);
    { uint32_t ea_ = (R(30) + 2012); stfs(base, ea_, ctx->f[4].d); }
    st32(base, (R(30) + 1976), R(10));
    st32(base, (R(30) + 1980), R(9));
    st32(base, (R(30) + 1984), R(0));
    { uint32_t ea_ = (R(30) + 1960); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(30) + 1964); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 1968); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 1972); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81833DF8u, 0x8007FB10u, 0);
    R(6) = (0 + 0x80020000u);
    R(5) = (0 + 0x80020000u);
    R(4) = (0 + 0x80020000u);
    R(3) = (0 + 3);
    R(6) = (R(6) + 4480);
    R(5) = (R(5) + 4464);
    R(4) = (R(4) + 4512);
    R(0) = (0 + 608);
    st8(base, (R(30) + 1953), R(3));
    R(3) = (R(30) + 1732);
    st32(base, (R(30) + 1940), R(0));
    st32(base, (R(30) + 1808), R(6));
    st32(base, (R(30) + 1812), R(5));
    st32(base, (R(30) + 1816), R(4));
    GM_CALLV(0x81833E34u, 0x8007F900u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* mod_fn_3_1C800 (mod_fn_3_1C800, 708 bytes) */
static void mj_mod_fn_3_1C800_33e58(GM_CTX) {
    GM_FN(0x81833E58); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(27) = (0 + 0x81860000u);
    R(28) = (0 + 0);
    R(29) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(27) + -300));
    st32(base, (f + 56), R(4));
    R(3) = ld32(base, (R(3) + 1608));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_818340D4; }
    R(3) = ld32(base, (R(30) + 2048));
    cr_cmp_u(ctx, 0, R(29), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81833ED8; }
    cr_cmp_u(ctx, 0, R(3), 0x15u);
    if ((!CR_BIT(ctx, 2))) { goto L_81833ED8; }
    R(3) = ld8(base, (R(30) + 2083));
    R(4) = (int8_t)R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81833ECCu, 0x80022180u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_818340D4; }
    R(3) = ld32(base, (R(30) + 2048));
L_81833ED8:;
    cr_cmp_u(ctx, 0, R(3), 0x1Fu);
    R(4) = (0 + 1);
    if ((CR_BIT(ctx, 0))) { goto L_81833EE8; }
    R(4) = (0 + 0);
L_81833EE8:;
    R(5) = (0 + 0x60040000u);
    R(3) = R(3) & 0x7FFFFFFFu;
    R(5) = R(5) | 0x341Cu;
    { uint32_t s_ = R(3) & 63; R(3) = s_ > 31 ? 0 : R(5) >> s_; }
    R(25) = R(4) &R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81833F04u, 0x80022390u, 0);
    R(28) = R(3) |R(3);
    R(3) = ld32(base, (R(30) + 180));
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    R(4) = ld32(base, (R(30) + 176));
    st32(base, (f + 20), R(3));
    R(3) = ld32(base, (R(30) + 172));
    R(26) = ld32(base, (R(30) + 4));
    st32(base, (f + 16), R(4));
    st32(base, (f + 12), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_8183401C; }
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183401C; }
    R(3) = ld32(base, (R(30) + 2052));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183401C; }
    R(4) = R(26) & 0x1Fu;
    R(5) = (f + 24);
    R(3) = R(30) |R(30);
    R(6) = (0 + 8);
    GM_CALLV(0x81833F54u, 0x81800FF8u, 0);
    R(3) = ld8(base, (R(30) + 2084));
    R(4) = (0 + -30640);
    R(4) = (R(4) + 0x81850000u);
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = R(3) ^ 0x3u;
    R(5) = cntlzw(R(5));
    R(5) = rotl32(R(5), 29) & 0x4u;
    { uint32_t ea_ = (R(4) + R(5)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 0))) { goto L_81834010; }
    cr_cmp_u(ctx, 0, R(3), 0x3u);
    R(29) = (0 + 0xC000000u);
    if ((CR_BIT(ctx, 2))) { goto L_81833F94; }
    R(29) = (0 + 0xB000000u);
L_81833F94:;
    R(26) = (f + 20);
    R(25) = (R(28) + 1);
    R(24) = (0 + 0);
    R(28) = (f + 12);
    R(23) = (0 + 0);
L_81833FA8:;
    { uint32_t ea_ = R(26) + 4; R(3) = ld32(base, ea_); R(26) = ea_; }
    R(4) = R(24) & 0xC00000u;
    R(7) = ld8(base, (R(30) + 911));
    R(4) = R(23) + R(4);
    R(3) = R(3) & 0x1Fu;
    R(3) = (rotl32(R(29), 0) & 0x3FFFE0u) | (R(3) & ~0x3FFFE0u);
    R(3) = (rotl32(R(29), 0) & 0x7F000000u) | (R(3) & ~0x7F000000u);
    R(29) = R(4) + R(3);
    R(3) = (0 + 60);
    R(4) = R(29) |R(29);
    R(5) = R(28) |R(28);
    R(6) = (0 + 0);
    GM_CALLV(0x81833FDCu, 0x80064610u, 0);
    R(3) = ld8(base, (R(30) + 2083));
    R(4) = R(28) |R(28);
    R(5) = ld32(base, (R(26) + 0));
    R(7) = (0 + 1);
    R(6) = (int8_t)R(3);
    R(3) = R(30) |R(30);
    R(8) = (0 + 0);
    GM_CALLV(0x81833FFCu, 0x80022490u, 0);
    R(25) = (R(25) + -1);
    R(23) = (R(23) + 0x80000000u);
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    R(24) = (R(24) + 0x200000u);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81833FA8; }
L_81834010:;
    R(3) = (0 + 1);
    st32(base, (R(30) + 1608), R(3));
    goto L_818340D0;
L_8183401C:;
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183405C; }
    R(3) = ld32(base, (R(30) + 2048));
    cr_cmp_u(ctx, 0, R(3), 0x15u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183405C; }
    R(3) = ld8(base, (R(30) + 2083));
    R(4) = (int8_t)R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81834040u, 0x80022180u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183405C; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -30932); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
L_8183405C:;
    R(3) = ld8(base, (R(30) + 2076));
    R(7) = ld8(base, (R(30) + 911));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81834084; }
    R(3) = (0 + 0x800F0000u);
    R(3) = R(3) | 0x1Fu;
    R(3) = R(26) &R(3);
    R(4) = (0 + 0x3000000u);
    R(4) = (rotl32(R(3), 0) & 0xFCFFFFFFu) | (R(4) & ~0xFCFFFFFFu);
    goto L_81834094;
L_81834084:;
    R(4) = R(26) & 0x3F00u;
    R(4) = (rotl32(R(26), 17) & 0xC000u) | (R(4) & ~0xC000u);
    R(4) = (rotl32(R(26), 0) & 0xFF0000u) | (R(4) & ~0xFF0000u);
    R(4) = (rotl32(R(26), 0) & 0xF000007Fu) | (R(4) & ~0xF000007Fu);
L_81834094:;
    R(29) = (f + 12);
    R(3) = (0 + 60);
    R(5) = R(29) |R(29);
    R(6) = (0 + 0);
    GM_CALLV(0x818340A8u, 0x80064610u, 0);
    R(3) = ld8(base, (R(30) + 2083));
    R(4) = (0 + 1);
    R(5) = ld32(base, (R(30) + 2048));
    R(7) = (0 + 0);
    st32(base, (R(30) + 1608), R(4));
    R(6) = (int8_t)R(3);
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    R(8) = (0 + 0);
    GM_CALLV(0x818340D0u, 0x80022490u, 0);
L_818340D0:;
    R(28) = (0 + 1);
L_818340D4:;
    R(3) = ld32(base, (R(27) + -300));
    R(4) = ld32(base, (f + 56));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81834118; }
    R(3) = R(28) |R(28);
    R(0) = lr;
    return;
L_81834118:;
    GM_CALLV(0x8183411Cu, 0x81844FCCu, 0);
}

/* mod_fn_3_1D040 (mod_fn_3_1D040, 508 bytes) */
static void mj_mod_fn_3_1D040_341d0(GM_CTX) {
    GM_FN(0x818341D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 2048));
    cr_cmp_u(ctx, 0, R(0), 0xFu);
    if ((CR_BIT(ctx, 2))) { goto L_818343B0; }
    cr_cmp_u(ctx, 0, R(0), 0x1Eu);
    R(31) = (0 + 0);
    if ((CR_BIT(ctx, 1))) { goto L_8183439C; }
    R(4) = (0 + 0x81830000u);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + 17356);
    R(4) = ld32(base, (R(4) + R(0)));
    ctx->ctr = R(4);
    { switch (ctx->ctr) { case 0x8183421Cu: goto L_8183421C; case 0x81834224u: goto L_81834224; case 0x8183426Cu: goto L_8183426C; case 0x818342B4u: goto L_818342B4; case 0x818342C0u: goto L_818342C0; case 0x818342CCu: goto L_818342CC; case 0x818342E0u: goto L_818342E0; case 0x818342E8u: goto L_818342E8; case 0x8183439Cu: goto L_8183439C; default: rt_fatal("818341D0: jump table target %08X", ctx->ctr); return; } }
L_8183421C:;
    R(31) = (0 + 1);
    goto L_8183439C;
L_81834224:;
    R(31) = (0 + 1);
    GM_CALLV(0x8183422Cu, 0x80022390u, 0);
    R(0) = (R(3) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_81834244; }
    R(0) = ld32(base, (R(30) + 2052));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81834258; }
L_81834244:;
    R(0) = ld32(base, (R(30) + 4));
    R(3) = R(30) |R(30);
    R(4) = rotl32(R(0), 3) & 0x3u;
    GM_CALLV(0x81834254u, 0x80021BD0u, 0);
    goto L_8183439C;
L_81834258:;
    R(0) = ld32(base, (R(30) + 4));
    R(3) = R(30) |R(30);
    R(4) = rotl32(R(0), 3) & 0x3u;
    GM_CALLV(0x81834268u, 0x80021C80u, 0);
    goto L_8183439C;
L_8183426C:;
    R(31) = (0 + 1);
    GM_CALLV(0x81834274u, 0x80022390u, 0);
    R(0) = (R(3) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8183428C; }
    R(0) = ld32(base, (R(30) + 2052));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_818342A0; }
L_8183428C:;
    R(0) = ld32(base, (R(30) + 4));
    R(3) = R(30) |R(30);
    R(4) = rotl32(R(0), 3) & 0x3u;
    GM_CALLV(0x8183429Cu, 0x80021EA0u, 0);
    goto L_8183439C;
L_818342A0:;
    R(0) = ld32(base, (R(30) + 4));
    R(3) = R(30) |R(30);
    R(4) = rotl32(R(0), 3) & 0x3u;
    GM_CALLV(0x818342B0u, 0x80021F50u, 0);
    goto L_8183439C;
L_818342B4:;
    GM_CALLV(0x818342B8u, 0x809BFAD0u, 0);
    R(31) = (0 + 1);
    goto L_8183439C;
L_818342C0:;
    GM_CALLV(0x818342C4u, 0x809BF8B0u, 0);
    R(31) = (0 + 1);
    goto L_8183439C;
L_818342CC:;
    R(5) = ld8(base, (R(3) + 2084));
    R(4) = (0 + 0);
    GM_CALLV(0x818342D8u, 0x80021A20u, 0);
    R(31) = (0 + 1);
    goto L_8183439C;
L_818342E0:;
    R(31) = (0 + 1);
    goto L_8183439C;
L_818342E8:;
    { uint32_t ea_ = (R(3) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (0 + 1);
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 172); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld8(base, (R(3) + 2076));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8183431C; }
    R(0) = ld8(base, (R(3) + 2084));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_81834374; }
L_8183431C:;
    R(5) = (0 + 0x80AD0000u);
    R(3) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(5) + -7432); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 16);
    { uint32_t ea_ = (f + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (0 + 5);
    R(3) = ld32(base, (R(3) + -25280));
    R(6) = (0 + 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81834348u, 0x80066740u, 0);
    R(4) = (0 + 0x80430000u);
    R(3) = (f + 8);
    R(29) = ld32(base, (R(4) + -25248));
    R(4) = (R(30) + 172);
    GM_CALLV(0x8183435Cu, 0x8006A4B0u, 0);
    R(3) = R(29) |R(29);
    R(5) = (f + 8);
    R(4) = (0 + 568);
    R(6) = (0 + 0);
    GM_CALLV(0x81834370u, 0x80198C30u, 0);
    goto L_8183439C;
L_81834374:;
    R(4) = (0 + 0x80AD0000u);
    R(3) = (0 + 0x80430000u);
    { uint32_t ea_ = (R(4) + -7436); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 16);
    R(3) = ld32(base, (R(3) + -25280));
    R(5) = (0 + 5);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    R(6) = (0 + 0);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8183439Cu, 0x800667B0u, 0);
L_8183439C:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818343B0; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 1);
    GM_CALLV(0x818343B0u, 0x809BF5D0u, 0);
L_818343B0:;
    R(0) = lr;
}

/* mod_fn_3_2D390 (mod_fn_3_2D390, 480 bytes) */
static void mj_mod_fn_3_2D390_34870(GM_CTX) {
    GM_FN(0x81834870); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(27) = (0 + 0x80AD0000u);
    R(31) = ld32(base, (R(3) + 4));
    R(27) = (R(27) + -5944);
    { uint32_t ea_ = (R(3) + 172); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = rotl32(R(31), 3) & 0x1u;
    CR0(ctx, R(0));
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(30) = rotl32(R(31), 28) & 0x3u;
    { uint32_t ea_ = (R(27) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d + ctx->f[2].d);
    R(0) = rotl32(R(31), 8) & 0x3u;
    st8(base, (R(3) + 1734), R(30));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    R(28) = R(3) |R(3);
    st8(base, (R(3) + 1638), R(0));
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_818348E8; }
    R(4) = R(28) |R(28);
    R(6) = (R(27) + 0);
    R(5) = (0 + 0);
    R(7) = (0 + 0);
    R(3) = (R(3) + 492);
    GM_CALLV(0x818348E4u, 0x8006D090u, 0);
    goto L_81834900;
L_818348E8:;
    R(4) = R(28) |R(28);
    R(6) = (R(27) + 12);
    R(5) = (0 + 0);
    R(7) = (0 + 0);
    R(3) = (R(3) + 492);
    GM_CALLV(0x81834900u, 0x8006D090u, 0);
L_81834900:;
    R(0) = rotl32(R(31), 20) & 0xFu;
    CR0(ctx, R(0));
    R(29) = rotl32(R(31), 16) & 0xFu;
    R(11) = (0 + 0);
    st8(base, (R(28) + 909), R(29));
    R(0) = (0 + 1);
    st8(base, (R(28) + 644), R(29));
    st16(base, (R(28) + 1732), R(11));
    st32(base, (R(28) + 308), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_818349FC; }
    R(0) = ld8(base, (R(28) + 1734));
    { uint32_t ea_ = (R(27) + 32); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    { uint32_t ea_ = (R(28) + 220); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(28) + 224); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(28) + 228); stfs(base, ea_, ctx->f[4].d); }
    if ((CR_BIT(ctx, 2))) { goto L_818349FC; }
    { uint32_t ea_ = (R(27) + 36); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(10) = (0 + 0x80020000u);
    { uint32_t ea_ = (R(27) + 28); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(9) = (0 + 0x80020000u);
    { uint32_t ea_ = (R(27) + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(10) = (R(10) + 3056);
    { uint32_t ea_ = (R(27) + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(9) = (R(9) + 3696);
    { uint32_t ea_ = (R(28) + 1716); stfs(base, ea_, ctx->f[4].d); }
    R(4) = R(28) |R(28);
    R(7) = ld8(base, (R(28) + 911));
    R(3) = (R(28) + 1332);
    { uint32_t ea_ = (R(28) + 1720); stfs(base, ea_, ctx->f[4].d); }
    R(5) = (R(28) + 1688);
    R(8) = (R(28) + 1716);
    R(6) = (0 + 3);
    { uint32_t ea_ = (R(28) + 1724); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(28) + 1688); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(28) + 1692); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(28) + 1696); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(28) + 1700); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(28) + 1704), R(10));
    st32(base, (R(28) + 1708), R(9));
    st32(base, (R(28) + 1712), R(11));
    GM_CALLV(0x818349A4u, 0x8007FB10u, 0);
    R(0) = (0 + 3);
    st32(base, (R(28) + 1536), R(0));
    R(3) = R(29) |R(29);
    GM_CALLV(0x818349B4u, 0x8005FB90u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818349C0; }
    st32(base, (R(28) + 1388), R(3));
L_818349C0:;
    R(6) = (0 + 0x80020000u);
    R(5) = (0 + 0x80020000u);
    R(4) = (0 + 0x80020000u);
    R(3) = (R(28) + 1332);
    R(6) = (R(6) + 4480);
    R(5) = (R(5) + 4464);
    R(4) = (R(4) + 4512);
    st32(base, (R(28) + 1408), R(6));
    st32(base, (R(28) + 1412), R(5));
    st32(base, (R(28) + 1416), R(4));
    GM_CALLV(0x818349ECu, 0x8007F900u, 0);
    { uint32_t ea_ = (R(27) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(28) + 236); stfs(base, ea_, ctx->f[0].d); }
    st16(base, (R(28) + 1732), R(0));
L_818349FC:;
    { uint32_t ea_ = (R(28) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(28) |R(28);
    GM_CALLV(0x81834A08u, 0x80021690u, 0);
    R(0) = (0 + 4);
    R(5) = (0 + 1);
    st16(base, (R(28) + 1728), R(0));
    R(3) = (0 + 0x80430000u);
    R(0) = rotl32(R(31), 20) & 0xF00u;
    R(4) = (R(28) + 172);
    st8(base, (R(28) + 1663), R(5));
    R(5) = R(30) |R(0);
    R(6) = (int8_t)R(29);
    R(3) = ld32(base, (R(3) + -24856));
    GM_CALLV(0x81834A34u, 0x800925F0u, 0);
    R(11) = (f + 32);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* mod_fn_3_85560 (mod_fn_3_85560, 812 bytes) */
static void mj_mod_fn_3_85560_35aac(GM_CTX) {
    GM_FN(0x81835AAC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(27) = (0 + 0x81860000u);
    R(28) = (0 + 0);
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(27) + -300));
    st32(base, (f + 32), R(4));
    R(3) = ld32(base, (R(3) + 3052));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81835D98; }
    R(3) = ld8(base, (R(30) + 3583));
    cr_cmp_u(ctx, 0, R(3), 0xFFu);
    if ((CR_BIT(ctx, 2))) { goto L_81835D98; }
    R(3) = (int8_t)R(3);
    GM_CALLV(0x81835B04u, 0x8005F900u, 0);
    R(29) = R(3) |R(3);
    GM_CALLV(0x81835B0Cu, 0x8004DD00u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81835B28; }
L_81835B14:;
    R(28) = (0 + 0);
    R(3) = (0 + 255);
    st32(base, (R(30) + 3052), R(28));
    st8(base, (R(30) + 3583), R(3));
    goto L_81835D98;
L_81835B28:;
    R(3) = ld16(base, (R(30) + 3530));
    R(26) = R(3) & 0xFFu;
    cr_cmp_u(ctx, 0, R(26), 0x6u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835B7C; }
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -508);
    R(3) = ld8(base, (R(3) + 11));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835BF8; }
    R(28) = ld32(base, (R(29) + 96));
    R(3) = ld32(base, (R(28) + 1048));
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81835B60u, ctx->ctr, 0);
    R(3) = ld32(base, (R(28) + 1016));
    R(4) = R(30) |R(30);
    R(5) = (0 + 18);
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81835B78u, ctx->ctr, 0);
    goto L_81835C30;
L_81835B7C:;
    R(25) = ld32(base, (R(29) + 96));
    R(3) = ld32(base, (R(25) + 224));
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81835B90u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81835B14; }
    cr_cmp_u(ctx, 0, R(26), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835C48; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835BA8u, 0x80A290B0u, 0);
    R(3) = ld32(base, (R(25) + 984));
    R(4) = (0 + 0);
    R(5) = (0 + 660);
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81835BC0u, ctx->ctr, 0);
    R(4) = ld8(base, (R(30) + 3583));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24496));
    R(6) = (0 + 1);
    R(5) = (int8_t)R(4);
    R(4) = (0 + 4);
    R(28) = (0 + 1);
    GM_CALLV(0x81835BE0u, 0x800E24B0u, 0);
    R(4) = ld8(base, (R(30) + 3583));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24816));
    R(4) = (int8_t)R(4);
    GM_CALLV(0x81835BF4u, 0x800A7860u, 0);
    goto L_81835D88;
L_81835BF8:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835C00u, 0x80A290B0u, 0);
    R(3) = ld32(base, (R(29) + 96));
    R(3) = ld32(base, (R(3) + 1048));
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81835C14u, ctx->ctr, 0);
    R(4) = ld8(base, (R(30) + 3583));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24496));
    R(6) = (0 + 1);
    R(5) = (int8_t)R(4);
    R(4) = (0 + 8);
    GM_CALLV(0x81835C30u, 0x800E24B0u, 0);
L_81835C30:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835C38u, 0x80A28280u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835C40u, 0x80162510u, 0);
    R(28) = (0 + 1);
    goto L_81835D98;
L_81835C48:;
    R(3) = ld32(base, (R(29) + 5344));
    cr_cmp_s(ctx, 0, (int32_t)R(26), 11);
    if ((!CR_BIT(ctx, 0))) { goto L_81835C80; }
    cr_cmp_u(ctx, 0, R(26), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81835CA8; }
    cr_cmp_u(ctx, 0, R(26), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_81835CD8; }
    cr_cmp_u(ctx, 0, R(26), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835D98; }
    cr_cmp_u(ctx, 0, R(3), 0x6u);
    if ((CR_BIT(ctx, 2))) { goto L_81835CF4; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 6);
    goto L_81835D40;
L_81835C80:;
    if ((CR_BIT(ctx, 2))) { goto L_81835CC4; }
    cr_cmp_u(ctx, 0, R(26), 0xDu);
    if ((CR_BIT(ctx, 2))) { goto L_81835CEC; }
    cr_cmp_u(ctx, 0, R(26), 0xEu);
    if ((!CR_BIT(ctx, 2))) { goto L_81835D98; }
    cr_cmp_u(ctx, 0, R(3), 0x5u);
    if ((CR_BIT(ctx, 2))) { goto L_81835CF4; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 5);
    goto L_81835D40;
L_81835CA8:;
    cr_cmp_u(ctx, 0, R(3), 0x3u);
    if ((CR_BIT(ctx, 2))) { goto L_81835CB8; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835CF4; }
L_81835CB8:;
    R(3) = R(29) |R(29);
    R(4) = (0 + 1);
    goto L_81835D40;
L_81835CC4:;
    cr_cmp_u(ctx, 0, R(3), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_81835CF4; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 4);
    goto L_81835D40;
L_81835CD8:;
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_81835CF4; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 2);
    goto L_81835D40;
L_81835CEC:;
    cr_cmp_u(ctx, 0, R(3), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835D38; }
L_81835CF4:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835CFCu, 0x80A290B0u, 0);
    R(3) = (0 + 0x80430000u);
    R(29) = ld32(base, (R(3) + -25248));
    R(4) = (R(30) + 172);
    R(3) = (f + 16);
    GM_CALLV(0x81835D10u, 0x8006A4B0u, 0);
    R(3) = ld32(base, (f + 20));
    R(5) = (f + 24);
    R(4) = ld32(base, (f + 16));
    R(6) = (0 + 0);
    st32(base, (f + 28), R(3));
    R(3) = R(29) |R(29);
    st32(base, (f + 24), R(4));
    R(4) = (0 + 278);
    GM_CALLV(0x81835D34u, 0x80198C30u, 0);
    goto L_81835D68;
L_81835D38:;
    R(3) = R(29) |R(29);
    R(4) = (0 + 3);
L_81835D40:;
    GM_CALLV(0x81835D44u, 0x80145AC0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81835D68; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835D54u, 0x80A290E0u, 0);
    R(4) = ld8(base, (R(30) + 3583));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24816));
    R(4) = (int8_t)R(4);
    GM_CALLV(0x81835D68u, 0x800A7860u, 0);
L_81835D68:;
    R(4) = ld8(base, (R(30) + 3583));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24496));
    R(6) = (0 + 1);
    R(5) = (int8_t)R(4);
    R(4) = (0 + 4);
    R(28) = (0 + 1);
    GM_CALLV(0x81835D88u, 0x800E24B0u, 0);
L_81835D88:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835D90u, 0x80A28280u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835D98u, 0x80162510u, 0);
L_81835D98:;
    R(3) = ld32(base, (R(27) + -300));
    R(4) = ld32(base, (f + 32));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81835DD4; }
    R(3) = R(28) |R(28);
    R(0) = lr;
    return;
L_81835DD4:;
    GM_CALLV(0x81835DD8u, 0x81844FCCu, 0);
}

/* mod_fn_3_88390 (mod_fn_3_88390, 512 bytes) */
static void mj_mod_fn_3_88390_35dd8(GM_CTX) {
    GM_FN(0x81835DD8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld16(base, (R(3) + 3530));
    cr_cmp_u(ctx, 0, R(3), 0xBu);
    if ((!CR_BIT(ctx, 2))) { goto L_81835E3C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835E04u, 0x80A28A00u, 0);
    R(3) = ld32(base, (R(30) + 3496));
    { uint32_t ea_ = (R(30) + 180); stfs(base, ea_, ctx->f[1].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((!CR_BIT(ctx, 0))) { goto L_81835E60; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81835EDC; }
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835F58; }
    R(3) = (0 + 0x3FE60000u);
    R(3) = R(3) | 0x6666u;
    st32(base, (R(30) + 232), R(3));
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30856); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_81835F54;
L_81835E3C:;
    R(3) = ld32(base, (R(30) + 3496));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835EA8; }
    R(3) = (0 + 0x3FE60000u);
    R(3) = R(3) | 0x6666u;
    st32(base, (R(30) + 232), R(3));
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31004); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_81835F54;
L_81835E60:;
    if ((CR_BIT(ctx, 2))) { goto L_81835F1C; }
    cr_cmp_u(ctx, 0, R(3), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835F58; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31028); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81835E78u, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30820); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -30764); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 232); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81835E94u, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30788); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30760); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    goto L_81835F10;
L_81835EA8:;
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30768); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81835EB4u, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31052); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -30956); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 232); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81835ED0u, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30856); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_81835F50;
L_81835EDC:;
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31028); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[31].u;
    GM_CALLV(0x81835EECu, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[31].d);
    { uint32_t ea_ = (R(3) + -30784); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 232); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81835F00u, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30788); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30852); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
L_81835F10:;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
    goto L_81835F54;
L_81835F1C:;
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31028); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x81835F28u, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30788); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[31].d);
    { uint32_t ea_ = (R(3) + -30756); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 232); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x81835F44u, 0x800B2F10u, 0);
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30952); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[31].d);
L_81835F50:;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
L_81835F54:;
    { uint32_t ea_ = (R(30) + 236); stfs(base, ea_, ctx->f[0].d); }
L_81835F58:;
    R(3) = ld8(base, (R(30) + 840));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81835F70; }
    { uint32_t ea_ = (R(30) + 232); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(30) + 232); stfs(base, ea_, ctx->f[0].d); }
L_81835F70:;
    R(3) = (0 + 0);
    st32(base, (R(30) + 240), R(3));
    R(3) = R(30) |R(30);
    GM_CALLV(0x81835F80u, 0x80A2AEB0u, 0);
    R(3) = ld16(base, (R(30) + 3530));
    cr_cmp_u(ctx, 0, R(3), 0xBu);
    if ((!CR_BIT(ctx, 2))) { goto L_81835FC0; }
    R(3) = ld32(base, (R(30) + 3496));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81835FB8; }
    cr_cmp_u(ctx, 0, R(3), 0x3u);
    if ((CR_BIT(ctx, 2))) { goto L_81835FB0; }
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_81835FC0; }
    R(3) = (0 + 82);
    goto L_81835FBC;
L_81835FB0:;
    R(3) = (0 + 98);
    goto L_81835FBC;
L_81835FB8:;
    R(3) = (0 + 64);
L_81835FBC:;
    st32(base, (R(30) + 3452), R(3));
L_81835FC0:;
    R(0) = lr;
}

/* mod_fn_3_968D0 (mod_fn_3_968D0, 868 bytes) */
static void mj_mod_fn_3_968D0_361ec(GM_CTX) {
    GM_FN(0x818361EC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80430000u);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(6) = ld32(base, (R(6) + -24120));
    R(6) = ld8(base, (R(6) + 4621));
    R(0) = (R(6) + -32);
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((CR_BIT(ctx, 1))) { goto L_81836240; }
    R(3) = (0 + 0);
    goto L_81836520;
L_81836240:;
    { uint32_t ea_ = (R(3) + 176); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (R(5) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 180); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d + ctx->f[2].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 148); stfs(base, ea_, ctx->f[5].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 140); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 144); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 128); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 132); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 136); stfs(base, ea_, ctx->f[5].d); }
    R(0) = ld32(base, (R(3) + 296));
    cr_cmp_u(ctx, 0, R(0), 0x7u);
    if ((CR_BIT(ctx, 1))) { goto L_818362BC; }
    R(5) = (0 + 0x80430000u);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    R(0) = ((int32_t)R(0) * 22);
    R(5) = ld32(base, (R(5) + -24708));
    R(0) = R(5) + R(0);
    R(4) = R(0) + R(4);
    if ((CR_BIT(ctx, 0))) { goto L_818362A8; }
    R(4) = (R(4) + 22);
L_818362A8:;
    R(0) = ld8(base, (R(4) + 2814));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818362BC; }
    R(0) = (0 + -1);
    st32(base, (R(3) + 296), R(0));
L_818362BC:;
    R(3) = ld32(base, (R(3) + 296));
    cr_cmp_u(ctx, 0, R(3), 0x7u);
    if ((CR_BIT(ctx, 1))) { goto L_818363F0; }
    GM_CALLV(0x818362CCu, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(28) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8183651C; }
    GM_CALLV(0x818362DCu, 0x80147B60u, 0);
    R(29) = R(3) |R(3);
    R(3) = R(28) |R(28);
    R(4) = (f + 112);
    GM_CALLV(0x818362ECu, 0x80141F70u, 0);
    { uint32_t ea_ = (f + 116); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 112); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[3].d + ctx->f[2].d);
    { uint32_t ea_ = (R(28) + 180); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    GM_CALLV(0x8183630Cu, 0x80101AA0u, 0);
    ctx->f[4].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (f + 120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x80AD0000u);
    { uint32_t ea_ = (f + 124); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 6692); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (0 + 0x80430000u);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[4].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[30].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[4].d + ctx->f[0].d);
    R(4) = ld32(base, (R(3) + -23776));
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[31].d - ctx->f[5].d);
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[30].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[4].d); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[31].d + ctx->f[5].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[4].d); }
    R(3) = ld32(base, (R(30) + 296));
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ((int32_t)R(3) * 572);
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[31].d); }
    R(4) = R(4) + R(0);
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[30].d); }
    R(0) = ld8(base, (R(4) + 897));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81836384; }
    R(4) = R(31) |R(31);
    GM_CALLV(0x81836384u, 0x800B3600u, 0);
L_81836384:;
    R(4) = (0 + 0x80AD0000u);
    R(3) = (f + 140);
    { uint32_t ea_ = (R(4) + 6580); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (f + 128);
    R(5) = (f + 84);
    R(6) = (f + 72);
    GM_CALLV(0x818363A0u, 0x800B3100u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_818363B0; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818363E4; }
L_818363B0:;
    R(3) = ld16(base, (R(30) + 1588));
    cr_cmp_u(ctx, 0, R(3), 0x3Cu);
    if ((!CR_BIT(ctx, 1))) { goto L_818363D8; }
    R(3) = ld32(base, (R(30) + 296));
    R(4) = R(31) |R(31);
    R(5) = (0 + 0);
    GM_CALLV(0x818363CCu, 0x800B3750u, 0);
    R(0) = (0 + -1);
    st32(base, (R(30) + 296), R(0));
    goto L_8183651C;
L_818363D8:;
    R(0) = (R(3) + 1);
    st16(base, (R(30) + 1588), R(0));
    goto L_8183651C;
L_818363E4:;
    R(0) = (0 + 0);
    st16(base, (R(30) + 1588), R(0));
    goto L_8183651C;
L_818363F0:;
    R(3) = R(30) |R(30);
    R(4) = (f + 8);
    GM_CALLV(0x818363FCu, 0x80064740u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(28) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8183651C; }
    R(0) = ld8(base, (R(3) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183651C; }
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81836424u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24708));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    R(0) = ((int32_t)R(0) * 22);
    R(0) = R(3) + R(0);
    R(3) = R(0) + R(31);
    if ((CR_BIT(ctx, 0))) { goto L_8183644C; }
    R(3) = (R(3) + 22);
L_8183644C:;
    R(0) = ld8(base, (R(3) + 2814));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8183651C; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x81836460u, 0x80147B60u, 0);
    R(31) = R(3) |R(3);
    R(3) = R(28) |R(28);
    R(4) = (f + 56);
    GM_CALLV(0x81836470u, 0x80141F70u, 0);
    { uint32_t ea_ = (f + 60); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[3].d + ctx->f[2].d);
    { uint32_t ea_ = (R(28) + 180); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    GM_CALLV(0x81836490u, 0x80101AA0u, 0);
    ctx->f[2].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (f + 68); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x80AD0000u);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[30].d - ctx->f[3].d);
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 6580); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[30].d + ctx->f[3].d);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[30].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    R(3) = (f + 140);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[31].d); }
    R(4) = (f + 128);
    R(5) = (f + 28);
    R(6) = (f + 16);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[31].d); }
    GM_CALLV(0x818364ECu, 0x800B3100u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8183651C; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8183651C; }
    R(12) = ld32(base, (R(28) + 96));
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 108));
    ctx->ctr = R(12);
    GM_CALLV(0x81836510u, ctx->ctr, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(0) = (int8_t)R(0);
    st32(base, (R(30) + 296), R(0));
L_8183651C:;
    R(3) = (0 + 0);
L_81836520:;
    R(0) = lr;
}

/* mod_getID__12dStateBase_cFv (mod_getID__12dStateBase_cFv, 40 bytes) */
static void mj_mod_getID__12dStateBase_cFv_383a8(GM_CTX) {
    R(4) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(4), -1);
    if ((!CR_BIT(ctx, 2))) { goto L_818383C8; }
    R(5) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(5) + -23712));
    R(4) = (R(4) + 1);
    st32(base, (R(5) + -23712), R(4));
    st32(base, (R(3) + 8), R(4));
L_818383C8:;
    R(3) = R(4) |R(4);
}

/* ctor_818383D0 (ctor_818383D0, 80 bytes) */
static void mj_ctor_818383D0_383d0(GM_CTX) {
    GM_FN(0x818383D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -1656));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81838410; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x80370000u);
    st8(base, (R(3) + -1656), R(4));
    R(4) = (0 + 0x80160000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 31236);
    R(4) = (R(4) + -2048);
    R(5) = (R(6) + -1648);
    GM_CALLV(0x81838410u, 0x81844EF4u, 0);
L_81838410:;
    R(0) = lr;
}

/* mfn_81838720 (mfn_81838720, 1232 bytes) */
static void mj_mfn_81838720_38720(GM_CTX) {
    GM_FN(0x81838720); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 40);
    R(30) = R(4) |R(4);
    R(4) = (0 + 0);
    R(28) = (0 + 0);
    R(29) = R(3) |R(3);
    GM_CALLV(0x81838770u, 0x81844D68u, 0);
    R(3) = (0 + 11);
    st8(base, (R(29) + 1), R(3));
    R(3) = R(30) |R(30);
    st32(base, (R(29) + 8), R(28));
    GM_CALLV(0x81838784u, 0x81838DBCu, 0);
    R(4) = ld8(base, (R(30) + 22));
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_818387C8; }
    cr_cmp_u(ctx, 0, R(3), 0x2Cu);
    st8(base, (R(30) + 22), R(28));
    if ((!CR_BIT(ctx, 2))) { goto L_818387B4; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x818387A4u, 0x81838DBCu, 0);
    R(4) = R(3) & 0xFFFFFFDFu;
    cr_cmp_u(ctx, 0, R(4), 0x5Du);
    if ((!CR_BIT(ctx, 2))) { goto L_818387C8; }
    goto L_818388DC;
L_818387B4:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 0))) { goto L_818387C8; }
    R(4) = R(3) & 0xFFFFFFDFu;
    cr_cmp_u(ctx, 0, R(4), 0x5Du);
    if ((!CR_BIT(ctx, 2))) { goto L_818388DC; }
L_818387C8:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_818388D0; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 90);
    if ((CR_BIT(ctx, 1))) { goto L_81838920; }
    R(4) = (R(3) + -34);
    cr_cmp_u(ctx, 0, R(4), 0x17u);
    if ((CR_BIT(ctx, 1))) { goto L_818388DC; }
    R(26) = (0 + 1);
    R(5) = (0 + 0xFF0000u);
    { uint32_t s_ = R(4) & 63; R(6) = s_ > 31 ? 0 : R(26) << s_; }
    R(5) = R(5) | 0xCA00u;
    R(5) = R(6) &R(5);
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81838A1C; }
    R(28) = R(30) |R(30);
    { uint32_t ea_ = R(28) + 40; st8(base, ea_, R(3)); R(28) = ea_; }
    R(3) = (0 + 0x4000000u);
    R(24) = (0 + 511);
    R(25) = (0 + 0);
    R(23) = (0 + 41);
    R(22) = R(3) | 0xDu;
    R(21) = R(28) |R(28);
L_8183881C:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838824u, 0x81838BF0u, 0);
    R(27) = R(3) |R(3);
    R(3) = (R(3) + -48);
    cr_cmp_u(ctx, 0, R(3), 0xAu);
    R(20) = (R(27) + -43);
    if ((CR_BIT(ctx, 0))) { goto L_8183884C; }
    cr_cmp_u(ctx, 0, R(20), 0x1Au);
    if ((CR_BIT(ctx, 1))) { goto L_81838890; }
    { uint32_t s_ = R(20) & 63; R(3) = s_ > 31 ? 0 : R(26) << s_; }
    R(3) = R(3) &R(22);
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81838890; }
L_8183884C:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838854u, 0x81838DBCu, 0);
    R(24) = (R(24) + -1);
    cr_cmp_u(ctx, 0, R(24), 0x0u);
    if ((!CR_BIT(ctx, 1))) { goto L_818388DC; }
    cr_cmp_u(ctx, 0, R(20), 0x1Au);
    if ((CR_BIT(ctx, 1))) { goto L_81838874; }
    { uint32_t s_ = R(20) & 63; R(3) = s_ > 31 ? 0 : R(26) << s_; }
    R(3) = R(3) &R(22);
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_8183887C; }
L_81838874:;
    cr_cmp_u(ctx, 0, R(27), 0x65u);
    if ((!CR_BIT(ctx, 2))) { goto L_81838880; }
L_8183887C:;
    R(25) = (0 + 1);
L_81838880:;
    st8(base, (R(21) + 1), R(27));
    R(21) = (R(21) + 1);
    R(23) = (R(23) + 1);
    GM_LOOP(); goto L_8183881C;
L_81838890:;
    cr_cmp_u(ctx, 0, R(27), 0x65u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8183884C; }
    R(3) = (R(23) + -40);
    R(5) = R(25) & 0x1u;
    CR0(ctx, R(5));
    R(4) = (0 + 0);
    R(27) = (0 + 1);
    R(5) = R(30) + R(3);
    st32(base, (R(29) + 4), R(28));
    st8(base, (R(29) + 0), R(27));
    st8(base, (R(5) + 40), R(4));
    st32(base, (R(29) + 8), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81838B5C; }
    R(3) = (0 + 2);
    st8(base, (R(29) + 1), R(3));
    st8(base, (R(30) + 22), R(27));
    goto L_818388E4;
L_818388D0:;
    R(3) = ld8(base, (R(30) + 21));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_818388E4; }
L_818388DC:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x818388E4u, 0x81838EB8u, 0);
L_818388E4:;
    R(0) = lr;
    return;
L_81838920:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 109);
    if ((!CR_BIT(ctx, 1))) { goto L_8183898C; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 123);
    if ((!CR_BIT(ctx, 0))) { goto L_81838A08; }
    cr_cmp_u(ctx, 0, R(3), 0x6Eu);
    if ((CR_BIT(ctx, 2))) { goto L_81838AFC; }
    cr_cmp_u(ctx, 0, R(3), 0x74u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838948u, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x72u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838958u, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x75u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838968u, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x65u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = (0 + 260);
    st16(base, (R(29) + 0), R(3));
    R(4) = (0 + 1);
    R(3) = (0 + 0);
    st8(base, (R(29) + 33), R(4));
    st32(base, (R(29) + 20), R(4));
    goto L_81838A00;
L_8183898C:;
    cr_cmp_u(ctx, 0, R(3), 0x5Bu);
    if ((CR_BIT(ctx, 2))) { goto L_81838B50; }
    cr_cmp_u(ctx, 0, R(3), 0x5Du);
    if ((CR_BIT(ctx, 2))) { goto L_81838B3C; }
    cr_cmp_u(ctx, 0, R(3), 0x66u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x818389ACu, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x61u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x818389BCu, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x6Cu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x818389CCu, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x73u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x818389DCu, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x65u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = (0 + 260);
    st16(base, (R(29) + 0), R(3));
    R(3) = (0 + 1);
    st8(base, (R(29) + 33), R(3));
    R(3) = (0 + 0);
    st32(base, (R(29) + 20), R(3));
    R(4) = (0 + 0);
L_81838A00:;
    st32(base, (R(29) + 16), R(3));
    goto L_81838B7C;
L_81838A08:;
    if ((CR_BIT(ctx, 2))) { goto L_81838B34; }
    cr_cmp_u(ctx, 0, R(3), 0x7Du);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = (0 + 264);
    goto L_81838B40;
L_81838A1C:;
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(28) = (R(30) + 40);
    R(25) = (R(30) + 39);
    R(26) = (0 + 511);
    R(27) = (0 + 40);
L_81838A34:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838A3Cu, 0x81838C84u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818388DC; }
    cr_cmp_u(ctx, 0, R(3), 0x5Cu);
    if ((CR_BIT(ctx, 2))) { goto L_81838A70; }
    cr_cmp_u(ctx, 0, R(3), 0x22u);
    if ((CR_BIT(ctx, 2))) { goto L_81838BA0; }
L_81838A54:;
    R(26) = (R(26) + -1);
    st8(base, (R(25) + 1), R(3));
    R(25) = (R(25) + 1);
    cr_cmp_u(ctx, 0, R(26), 0x0u);
    R(27) = (R(27) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81838A34; }
    GM_LOOP(); goto L_818388DC;
L_81838A70:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838A78u, 0x81838C84u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818388DC; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 101);
    if ((CR_BIT(ctx, 1))) { goto L_81838AA4; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 92);
    if ((!CR_BIT(ctx, 0))) { goto L_81838AC4; }
    cr_cmp_u(ctx, 0, R(3), 0x22u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81838A54; }
    cr_cmp_u(ctx, 0, R(3), 0x2Fu);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81838A54; }
    GM_LOOP(); goto L_818388DC;
L_81838AA4:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 114);
    if ((!CR_BIT(ctx, 0))) { goto L_81838AD8; }
    cr_cmp_u(ctx, 0, R(3), 0x66u);
    if ((CR_BIT(ctx, 2))) { goto L_81838AEC; }
    cr_cmp_u(ctx, 0, R(3), 0x6Eu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = (0 + 10);
    GM_LOOP(); goto L_81838A54;
L_81838AC4:;
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81838A54; }
    cr_cmp_u(ctx, 0, R(3), 0x62u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = (0 + 8);
    GM_LOOP(); goto L_81838A54;
L_81838AD8:;
    if ((CR_BIT(ctx, 2))) { goto L_81838AF4; }
    cr_cmp_u(ctx, 0, R(3), 0x74u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = (0 + 9);
    GM_LOOP(); goto L_81838A54;
L_81838AEC:;
    R(3) = (0 + 12);
    GM_LOOP(); goto L_81838A54;
L_81838AF4:;
    R(3) = (0 + 13);
    GM_LOOP(); goto L_81838A54;
L_81838AFC:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838B04u, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x75u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838B14u, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x6Cu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838B24u, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x6Cu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818388DC; }
    R(3) = (0 + 261);
    goto L_81838B40;
L_81838B34:;
    R(3) = (0 + 263);
    goto L_81838B54;
L_81838B3C:;
    R(3) = (0 + 266);
L_81838B40:;
    st16(base, (R(29) + 0), R(3));
    R(3) = (0 + 1);
    st8(base, (R(30) + 22), R(3));
    GM_LOOP(); goto L_818388E4;
L_81838B50:;
    R(3) = (0 + 265);
L_81838B54:;
    st16(base, (R(29) + 0), R(3));
    GM_LOOP(); goto L_818388E4;
L_81838B5C:;
    R(3) = R(28) |R(28);
    GM_CALLV(0x81838B64u, 0x802E2108u, 0);
    R(4) = R(3) |R(3);
    { int32_t v_ = (int32_t)R(3); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(3) = (v_ >> 31); }
    st8(base, (R(29) + 33), R(27));
    st32(base, (R(29) + 20), R(4));
    st32(base, (R(29) + 16), R(3));
    st8(base, (R(29) + 1), R(27));
L_81838B7C:;
    R(5) = (0 + 1);
    st8(base, (R(30) + 22), R(5));
    R(5) = R(4) |R(3);
    { uint32_t a_ = R(5); R(6) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(6) < a_; }
    { uint64_t t_ = (uint64_t)(~R(6)) + (R(5)) + ctx->xer_ca; R(5) = t_; ctx->xer_ca = (t_ >> 32); }
    st8(base, (R(29) + 32), R(5));
    GM_CALLV(0x81838B98u, 0x81844F10u, 0);
    { uint32_t ea_ = (R(29) + 24); st64(base, ea_, ctx->f[1].u); }
    GM_LOOP(); goto L_818388E4;
L_81838BA0:;
    R(3) = (R(27) + -40);
    R(27) = (0 + 0);
    st32(base, (R(29) + 4), R(28));
    R(28) = (0 + 1);
    R(4) = R(30) + R(3);
    st32(base, (R(29) + 8), R(3));
    R(3) = R(30) |R(30);
    st8(base, (R(29) + 0), R(28));
    st8(base, (R(4) + 40), R(27));
    GM_CALLV(0x81838BC8u, 0x81838BF0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x3Au);
    if ((!CR_BIT(ctx, 2))) { goto L_81838BE0; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838BD8u, 0x81838DBCu, 0);
    st8(base, (R(29) + 1), R(27));
    GM_LOOP(); goto L_818388E4;
L_81838BE0:;
    R(3) = (0 + 6);
    st8(base, (R(29) + 1), R(3));
    st8(base, (R(30) + 22), R(28));
    GM_LOOP(); goto L_818388E4;
}

/* mfn_81838BF0 (mfn_81838BF0, 80 bytes) */
static void mj_mfn_81838BF0_38bf0(GM_CTX) {
    GM_FN(0x81838BF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_81838C2C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838C18u, 0x81838DBCu, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_81838C28; }
    st32(base, (R(30) + 24), R(3));
    goto L_81838C2C;
L_81838C28:;
    R(3) = (0 + -1);
L_81838C2C:;
    R(0) = lr;
}

/* mfn_81838C84 (mfn_81838C84, 232 bytes) */
static void mj_mfn_81838C84_38c84(GM_CTX) {
    GM_FN(0x81838C84); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = ld32(base, (R(3) + 28));
    R(30) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 0))) { goto L_81838CB4; }
    R(3) = (0 + -1);
    st32(base, (R(30) + 28), R(3));
    goto L_81838D38;
L_81838CB4:;
    R(3) = ld32(base, (R(30) + 16));
    R(5) = ld32(base, (R(30) + 8));
    cr_cmp_u(ctx, 0, R(3), R(5));
    if ((CR_BIT(ctx, 0))) { goto L_81838D28; }
    R(3) = ld8(base, (R(30) + 21));
    R(29) = (0 + -1);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81838D38; }
    R(6) = ld32(base, (R(30) + 12));
    R(4) = (0 + 0);
    R(7) = ld32(base, (R(30) + 32));
    R(5) = R(6) + R(5);
    R(3) = ld32(base, (R(30) + 0));
    ctx->ctr = R(7);
    st32(base, (R(30) + 8), R(4));
    st32(base, (R(30) + 16), R(4));
    R(4) = ld32(base, (R(30) + 4));
    st32(base, (R(30) + 12), R(5));
    R(5) = ld32(base, (R(30) + 36));
    GM_CALLV(0x81838D04u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81838D54; }
    R(4) = ld32(base, (R(30) + 4));
    st32(base, (R(30) + 8), R(3));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 0))) { goto L_81838D24; }
    R(3) = (0 + 1);
    st8(base, (R(30) + 21), R(3));
L_81838D24:;
    R(3) = ld32(base, (R(30) + 16));
L_81838D28:;
    R(4) = ld32(base, (R(30) + 0));
    R(5) = (R(3) + 1);
    st32(base, (R(30) + 16), R(5));
    R(29) = ld8(base, (R(4) + R(3)));
L_81838D38:;
    R(3) = R(29) |R(29);
    R(0) = lr;
    return;
L_81838D54:;
    R(4) = ld8(base, (R(30) + 21));
    R(3) = cntlzw(R(3));
    R(3) = rotl32(R(3), 27) & 0x7FFFFFFu;
    R(3) = R(4) |R(3);
    st8(base, (R(30) + 21), R(3));
    GM_LOOP(); goto L_81838D38;
}

/* mfn_81838DBC (mfn_81838DBC, 252 bytes) */
static void mj_mfn_81838DBC_38dbc(GM_CTX) {
    GM_FN(0x81838DBC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = (0 + -1);
    R(29) = ld32(base, (R(30) + 24));
    st32(base, (R(30) + 24), R(3));
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 0))) { goto L_81838E90; }
L_81838DE8:;
    R(3) = R(29) |R(29);
    R(0) = lr;
    return;
L_81838E04:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838E0Cu, 0x81838D6Cu, 0);
    cr_cmp_u(ctx, 0, R(3), 0x2Fu);
    if ((!CR_BIT(ctx, 2))) { goto L_81838E30; }
L_81838E14:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838E1Cu, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0xAu);
    if ((CR_BIT(ctx, 2))) { goto L_81838E90; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81838E14; }
    goto L_81838E90;
L_81838E30:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838E38u, 0x81838D6Cu, 0);
    cr_cmp_u(ctx, 0, R(3), 0x2Au);
    if ((!CR_BIT(ctx, 2))) { goto L_81838EB0; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838E48u, 0x81838C84u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838E50u, 0x81838C84u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(29) = (0 + -1);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81838DE8; }
L_81838E5C:;
    cr_cmp_u(ctx, 0, R(3), 0x2Au);
    if ((!CR_BIT(ctx, 2))) { goto L_81838E74; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838E6Cu, 0x81838D6Cu, 0);
    cr_cmp_u(ctx, 0, R(3), 0x2Fu);
    if ((CR_BIT(ctx, 2))) { goto L_81838E88; }
L_81838E74:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838E7Cu, 0x81838C84u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81838E5C; }
    GM_LOOP(); goto L_81838DE8;
L_81838E88:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838E90u, 0x81838C84u, 0);
L_81838E90:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81838E98u, 0x81838C84u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x21u);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81838E90; }
    R(29) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(3), 0x2Fu);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81838E04; }
    GM_LOOP(); goto L_81838DE8;
L_81838EB0:;
    R(29) = (0 + 47);
    GM_LOOP(); goto L_81838DE8;
}

/* mod_fn_8016B2A0 (mod_fn_8016B2A0, 764 bytes) */
static void mj_mod_fn_8016B2A0_39ffc(GM_CTX) {
    GM_FN(0x81839FFC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(21) = (0 + 0x81860000u);
    R(23) = R(10) |R(10);
    R(24) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(26) = R(5) |R(5);
    R(27) = R(6) |R(6);
    R(28) = R(7) |R(7);
    R(29) = R(8) |R(8);
    R(30) = R(9) |R(9);
    R(3) = ld32(base, (R(3) + -300));
    R(25) = R(4) |R(4);
    R(4) = (0 + 0);
    st32(base, (f + 284), R(3));
    R(3) = ld8(base, (R(21) + -1268));
    st32(base, (f + 24), R(4));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    st32(base, (f + 20), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_8183A2C0; }
L_8183A07C:;
    cr_cmp_u(ctx, 0, R(23), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A120; }
    R(22) = R(23) & 0xFFu;
    R(3) = R(22) |R(22);
    GM_CALLV(0x8183A090u, 0x8016B0F0u, 0);
    R(21) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(20) = (R(3) + -1512);
    R(3) = R(20) |R(20);
    R(4) = R(24) |R(24);
    GM_CALLV(0x8183A0A8u, 0x802B7C30u, 0);
    R(3) = (0 + 0x81850000u);
    R(10) = ld32(base, (R(3) + 17020));
    R(23) = (0 + 0);
    R(3) = R(20) |R(20);
    R(4) = R(21) |R(21);
    R(5) = R(25) |R(25);
    R(6) = R(26) |R(26);
    R(7) = R(27) |R(27);
    R(8) = R(28) |R(28);
    R(9) = (0 + 0);
    st32(base, (f + 12), R(23));
    st32(base, (f + 8), R(23));
    GM_CALLV(0x8183A0DCu, 0x802B8150u, 0);
    R(28) = R(3) |R(3);
    GM_CALLV(0x8183A0E4u, 0x802B9700u, 0);
    st32(base, (f + 24), R(3));
    st32(base, (f + 20), R(3));
    R(3) = R(22) |R(22);
    GM_CALLV(0x8183A0F4u, 0x8016B130u, 0);
    R(3) = R(20) |R(20);
    GM_CALLV(0x8183A0FCu, 0x802B7D10u, 0);
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A1F8; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x8183A10Cu, 0x802B9700u, 0);
    R(4) = R(3) |R(3);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8183A118u, 0x801AC500u, 0);
    R(23) = R(28) |R(28);
    goto L_8183A1F8;
L_8183A120:;
    R(3) = (f + 28);
    R(4) = (0 + 0);
    R(5) = (0 + 256);
    GM_CALLV(0x8183A130u, 0x81844D68u, 0);
    R(3) = R(24) |R(24);
    GM_CALLV(0x8183A138u, 0x818417C4u, 0);
    cr_cmp_u(ctx, 0, R(28), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A1D4; }
    cr_cmp_u(ctx, 0, R(26), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A1D4; }
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A1D4; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A1D4; }
    R(23) = (f + 28);
    R(3) = R(24) |R(24);
    R(4) = R(23) |R(23);
    R(5) = (0 + 255);
    GM_CALLV(0x8183A16Cu, 0x81841640u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A1D4; }
    R(4) = (0 + 0);
    R(3) = (f + 27);
L_8183A17C:;
    { uint32_t ea_ = R(3) + 1; R(6) = ld8(base, ea_); R(3) = ea_; }
    R(5) = R(4) |R(4);
    R(4) = (R(4) + 1);
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8183A17C; }
    cr_cmp_u(ctx, 0, R(5), 0x5u);
    if ((CR_BIT(ctx, 0))) { goto L_8183A1D4; }
    R(4) = (0 + 0);
    R(3) = (f + 27);
L_8183A1A0:;
    { uint32_t ea_ = R(3) + 1; R(6) = ld8(base, ea_); R(3) = ea_; }
    R(5) = R(4) |R(4);
    R(4) = (R(4) + 1);
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8183A1A0; }
    R(4) = (0 + 0x81850000u);
    R(3) = R(23) + R(5);
    R(4) = (R(4) + -2461);
    R(3) = (R(3) + -4);
    R(4) = (R(4) + 22);
    GM_CALLV(0x8183A1CCu, 0x802E1AB4u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A26C; }
L_8183A1D4:;
    R(8) = (f + 24);
    R(9) = (f + 20);
    R(3) = R(24) |R(24);
    R(4) = R(25) |R(25);
    R(5) = R(26) |R(26);
    R(6) = R(27) |R(27);
    R(7) = R(28) |R(28);
    GM_CALLV(0x8183A1F4u, 0x802B7ED0u, 0);
    R(23) = R(3) |R(3);
L_8183A1F8:;
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A208; }
    R(3) = ld32(base, (f + 24));
    st32(base, (R(29) + 0), R(3));
L_8183A208:;
    cr_cmp_u(ctx, 0, R(30), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A218; }
    R(3) = ld32(base, (f + 20));
    st32(base, (R(30) + 0), R(3));
L_8183A218:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 284));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8183A2F4; }
    R(3) = R(23) |R(23);
    R(0) = lr;
    return;
L_8183A26C:;
    R(23) = (f + 28);
    R(3) = R(23) |R(23);
    GM_CALLV(0x8183A278u, 0x81845438u, 0);
    R(4) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(22) = (R(3) + -1512);
    R(3) = R(22) |R(22);
    GM_CALLV(0x8183A28Cu, 0x802B7C30u, 0);
    R(7) = (f + 24);
    R(8) = (f + 20);
    R(3) = R(22) |R(22);
    R(4) = R(23) |R(23);
    R(5) = R(26) |R(26);
    R(6) = R(27) |R(27);
    GM_CALLV(0x8183A2A8u, 0x8183B0D8u, 0);
    R(23) = R(3) |R(3);
    R(3) = R(22) |R(22);
    GM_CALLV(0x8183A2B4u, 0x802B7D10u, 0);
    cr_cmp_u(ctx, 0, R(23), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8183A1F8; }
    GM_LOOP(); goto L_8183A1D4;
L_8183A2C0:;
    R(3) = (0 + 0x81860000u);
    R(22) = (R(3) + -1512);
    R(3) = R(22) |R(22);
    GM_CALLV(0x8183A2D0u, 0x802B7B00u, 0);
    R(3) = (0 + 0x802B0000u);
    R(5) = (0 + 0x81860000u);
    R(4) = (R(3) + 31568);
    R(5) = (R(5) + -1264);
    R(3) = R(22) |R(22);
    GM_CALLV(0x8183A2E8u, 0x81844EF4u, 0);
    R(3) = (0 + 1);
    st8(base, (R(21) + -1268), R(3));
    GM_LOOP(); goto L_8183A07C;
L_8183A2F4:;
    GM_CALLV(0x8183A2F8u, 0x81844FCCu, 0);
}

/* mfn_8183A2F8 (mfn_8183A2F8, 196 bytes) */
static void mj_mfn_8183A2F8_3a2f8(GM_CTX) {
    GM_FN(0x8183A2F8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(24) = (0 + 0x81860000u);
    R(25) = R(4) |R(4);
    R(26) = R(5) |R(5);
    R(27) = R(6) |R(6);
    R(28) = R(7) |R(7);
    R(29) = R(8) |R(8);
    R(30) = R(9) |R(9);
    R(4) = ld32(base, (R(24) + -300));
    st32(base, (f + 12), R(4));
    R(4) = (f + 11);
    GM_CALLV(0x8183A34Cu, 0x8016BC30u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8183A378; }
    R(10) = ld8(base, (f + 11));
    R(4) = R(25) |R(25);
    R(5) = R(26) |R(26);
    R(6) = R(27) |R(27);
    R(7) = R(28) |R(28);
    R(8) = R(29) |R(29);
    R(9) = R(30) |R(30);
    GM_CALLV(0x8183A374u, 0x8016B2A0u, 0);
    goto L_8183A37C;
L_8183A378:;
    R(3) = (0 + 0);
L_8183A37C:;
    R(4) = ld32(base, (R(24) + -300));
    R(5) = ld32(base, (f + 12));
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_8183A3B8; }
    R(0) = lr;
    return;
L_8183A3B8:;
    GM_CALLV(0x8183A3BCu, 0x81844FCCu, 0);
}

/* mod_fn_8016BC30 (mod_fn_8016BC30, 204 bytes) */
static void mj_mod_fn_8016BC30_3a3bc(GM_CTX) {
    GM_FN(0x8183A3BC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(30) = R(4) |R(4);
    R(4) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(4) + -300));
    st32(base, (f + 524), R(4));
    R(4) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(4) + -1516));
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A448; }
    R(3) = (0 + 0x81850000u);
    R(28) = (f + 12);
    R(3) = (R(3) + -2461);
    R(4) = (R(3) + 27);
    R(3) = R(28) |R(28);
    R(5) = (0 + 512);
    GM_CALLV(0x8183A414u, 0x81844C38u, 0);
    R(3) = ld8(base, (R(29) + 0));
    R(5) = (0 + 499);
    R(3) = R(3) ^ 0x2Fu;
    R(3) = cntlzw(R(3));
    R(3) = rotl32(R(3), 27) & 0x7FFFFFFu;
    R(4) = R(29) + R(3);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8183A434u, 0x802E1A68u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(30) |R(30);
    GM_CALLV(0x8183A440u, 0x8183A4A4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), -1);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A454; }
L_8183A448:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    GM_CALLV(0x8183A454u, 0x8183A4A4u, 0);
L_8183A454:;
    R(4) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(4) + -300));
    R(5) = ld32(base, (f + 524));
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_8183A484; }
    R(0) = lr;
    return;
L_8183A484:;
    GM_CALLV(0x8183A488u, 0x81844FCCu, 0);
}

/* mfn_8183A4A4 (mfn_8183A4A4, 116 bytes) */
static void mj_mfn_8183A4A4_3a4a4(GM_CTX) {
    GM_FN(0x8183A4A4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(30) = R(4) |R(4);
    GM_CALLV(0x8183A4C4u, 0x8016BC20u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A4E0; }
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    GM_CALLV(0x8183A4D8u, 0x8016BAA0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), -1);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A500; }
L_8183A4E0:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x8183A4E8u, 0x818414E4u, 0);
    cr_cmp_u(ctx, 0, R(30), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A500; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), -1);
    if ((CR_BIT(ctx, 2))) { goto L_8183A500; }
    R(4) = (0 + 0);
    st8(base, (R(30) + 0), R(4));
L_8183A500:;
    R(0) = lr;
}

/* mod_create__16mDvd_toMainRam_cFPCcUcPQ23EGG4Heap (mod_create__16mDvd_toMainRam_cFPCcUcPQ23EGG4Heap, 64 bytes) */
static void mj_mod_create__16mDvd_toMainRam_cFPCcUcPQ23_3a518(GM_CTX) {
    GM_FN(0x8183A518); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x8183A52Cu, 0x81845430u, 0);
    R(30) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A540; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8183A540u, 0x8016B4F0u, 0);
L_8183A540:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mfn_8183A558 (mfn_8183A558, 168 bytes) */
static void mj_mfn_8183A558_3a558(GM_CTX) {
    GM_FN(0x8183A558); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(27) = (0 + 0x81860000u);
    R(28) = (f + 20);
    R(29) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(27) + -300));
    st32(base, (f + 264), R(3));
    R(3) = R(28) |R(28);
    GM_CALLV(0x8183A594u, 0x802B7B00u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(30) |R(30);
    GM_CALLV(0x8183A5A0u, 0x802B7CB0u, 0);
    R(30) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A5BC; }
    R(3) = ld32(base, (f + 132));
    st32(base, (R(29) + 0), R(3));
    R(3) = (f + 20);
    GM_CALLV(0x8183A5BCu, 0x802B7D10u, 0);
L_8183A5BC:;
    R(3) = (f + 20);
    R(4) = (0 + -1);
    GM_CALLV(0x8183A5C8u, 0x802B7B50u, 0);
    R(3) = ld32(base, (R(27) + -300));
    R(4) = ld32(base, (f + 264));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8183A5FC; }
    R(3) = R(30) |R(30);
    R(0) = lr;
    return;
L_8183A5FC:;
    GM_CALLV(0x8183A600u, 0x81844FCCu, 0);
}

/* ctor_8183A600 (ctor_8183A600, 288 bytes) */
static void mj_ctor_8183A600_3a600(GM_CTX) {
    GM_FN(0x8183A600); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -1632));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A640; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x80370000u);
    st8(base, (R(3) + -1632), R(4));
    R(4) = (0 + 0x81840000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 31460);
    R(4) = (R(4) + -24600);
    R(5) = (R(6) + -1624);
    GM_CALLV(0x8183A640u, 0x81844EF4u, 0);
L_8183A640:;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -1608));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A674; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x80370000u);
    st8(base, (R(3) + -1608), R(4));
    R(4) = (0 + 0x81840000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 31472);
    R(4) = (R(4) + -24596);
    R(5) = (R(6) + -1600);
    GM_CALLV(0x8183A674u, 0x81844EF4u, 0);
L_8183A674:;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -1584));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A6A8; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x80370000u);
    st8(base, (R(3) + -1584), R(4));
    R(4) = (0 + 0x81840000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 31484);
    R(4) = (R(4) + -24592);
    R(5) = (R(6) + -1576);
    GM_CALLV(0x8183A6A8u, 0x81844EF4u, 0);
L_8183A6A8:;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -1560));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A6DC; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x80370000u);
    st8(base, (R(3) + -1560), R(4));
    R(4) = (0 + 0x81840000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 31496);
    R(4) = (R(4) + -24588);
    R(5) = (R(6) + -1552);
    GM_CALLV(0x8183A6DCu, 0x81844EF4u, 0);
L_8183A6DC:;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -1536));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183A710; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x80370000u);
    st8(base, (R(3) + -1536), R(4));
    R(4) = (0 + 0x81840000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 31508);
    R(4) = (R(4) + -24584);
    R(5) = (R(6) + -1528);
    GM_CALLV(0x8183A710u, 0x81844EF4u, 0);
L_8183A710:;
    R(0) = lr;
}

/* mfn_8183A720 (mfn_8183A720, 108 bytes) */
static void mj_mfn_8183A720_3a720(GM_CTX) {
    GM_FN(0x8183A720); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 8));
    R(29) = R(4) |R(4);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A74C; }
    GM_CALLV(0x8183A74Cu, 0x802B9290u, 0);
L_8183A74C:;
    R(3) = ld32(base, (R(30) + 20));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A75C; }
    GM_CALLV(0x8183A75Cu, 0x802B9290u, 0);
L_8183A75C:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 1);
    if ((CR_BIT(ctx, 0))) { goto L_8183A770; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 32);
    GM_CALLV(0x8183A770u, 0x818434F4u, 0);
L_8183A770:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mfn_8183A78C (mfn_8183A78C, 264 bytes) */
static void mj_mfn_8183A78C_3a78c(GM_CTX) {
    GM_FN(0x8183A78C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 24));
    R(27) = (0 + 0);
    R(29) = R(4) |R(4);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_8183A7F0; }
    R(28) = (0 + 0);
L_8183A7C8:;
    R(3) = ld32(base, (R(30) + 20));
    R(4) = R(29) |R(29);
    R(3) = R(3) + R(28);
    GM_CALLV(0x8183A7D8u, 0x802E1AB4u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A854; }
    R(3) = ld32(base, (R(30) + 24));
    R(28) = (R(28) + 1);
    cr_cmp_u(ctx, 0, R(28), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8183A7C8; }
L_8183A7F0:;
    R(5) = (R(29) + -1);
L_8183A7F4:;
    { uint32_t ea_ = R(5) + 1; R(6) = ld8(base, ea_); R(5) = ea_; }
    R(4) = R(27) |R(27);
    R(27) = (R(27) + 1);
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8183A7F4; }
    R(6) = ld32(base, (R(30) + 28));
    R(5) = R(3) + R(27);
    cr_cmp_u(ctx, 0, R(5), R(6));
    if ((CR_BIT(ctx, 1))) { goto L_8183A878; }
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A84C; }
    R(6) = ld32(base, (R(30) + 20));
    R(5) = (R(29) + -1);
    R(4) = (R(4) + 1);
    ctx->ctr = R(4);
    R(3) = R(3) + R(6);
    R(3) = (R(3) + -1);
L_8183A838:;
    { uint32_t ea_ = R(5) + 1; R(4) = ld8(base, ea_); R(5) = ea_; }
    { uint32_t ea_ = R(3) + 1; st8(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8183A838; }
    R(3) = ld32(base, (R(30) + 24));
    R(5) = R(3) + R(27);
L_8183A84C:;
    R(28) = R(3) |R(3);
    st32(base, (R(30) + 24), R(5));
L_8183A854:;
    R(3) = R(28) |R(28);
    R(0) = lr;
    return;
L_8183A878:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1922);
    R(5) = (R(3) + 18);
    R(6) = (R(3) + 460);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 44);
    GM_CALLV(0x8183A894u, 0x818380F8u, 0);
}

/* mfn_8183A894 (mfn_8183A894, 472 bytes) */
static void mj_mfn_8183A894_3a894(GM_CTX) {
    GM_FN(0x8183A894); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    R(28) = R(4) |R(4);
    R(4) = ld32(base, (R(3) + 12));
    R(29) = R(3) |R(3);
    R(30) = R(6) |R(6);
    if ((!CR_BIT(ctx, 0))) { goto L_8183A8D8; }
    R(3) = R(30) + R(4);
    R(30) = (R(3) + 1);
L_8183A8D8:;
    cr_cmp_u(ctx, 0, R(30), R(4));
    R(3) = (0 + -1);
    if ((CR_BIT(ctx, 1))) { goto L_8183AA44; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8183AA44; }
    R(6) = ld32(base, (R(29) + 16));
    cr_cmp_u(ctx, 0, R(30), R(6));
    if ((!CR_BIT(ctx, 0))) { goto L_8183AA44; }
    R(6) = ld32(base, (R(28) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(7), 0);
    R(27) = rotl32(R(6), 8) & 0xFFu;
    if ((CR_BIT(ctx, 0))) { goto L_8183A94C; }
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A914; }
    st32(base, (R(28) + 4), R(7));
L_8183A914:;
    R(3) = ld32(base, (R(29) + 8));
L_8183A918:;
    R(4) = ((int32_t)R(7) * 12);
    R(3) = R(3) + R(4);
    R(6) = ld32(base, (R(3) + 8));
    R(6) = (R(6) + 1);
    st32(base, (R(3) + 8), R(6));
    R(3) = ld32(base, (R(29) + 8));
    R(4) = R(3) + R(4);
    R(4) = ld32(base, (R(4) + 4));
    cr_cmp_u(ctx, 0, R(4), R(7));
    R(7) = R(4) |R(4);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8183A918; }
    R(4) = ld32(base, (R(29) + 12));
    goto L_8183A954;
L_8183A94C:;
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AA44; }
L_8183A954:;
    cr_cmp_u(ctx, 0, R(30), R(4));
    if ((!CR_BIT(ctx, 0))) { goto L_8183A9F0; }
    R(3) = (R(4) + -1);
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(30));
    if ((CR_BIT(ctx, 0))) { goto L_8183A9F0; }
    R(4) = ((int32_t)R(4) * 12);
L_8183A96C:;
    R(6) = ld32(base, (R(29) + 8));
    R(7) = R(6) + R(4);
    R(8) = ld32(base, (R(7) + -12));
    st32(base, (R(6) + R(4)), R(8));
    R(6) = ld32(base, (R(7) + -4));
    R(8) = ld32(base, (R(7) + -8));
    st32(base, (R(7) + 8), R(6));
    st32(base, (R(7) + 4), R(8));
    R(6) = ld32(base, (R(29) + 8));
    R(7) = ld8(base, (R(6) + R(4)));
    cr_cmp_u(ctx, 0, R(7), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183A9E0; }
    R(7) = R(6) + R(4);
    R(8) = ld32(base, (R(7) + 4));
    R(6) = (0 + 1);
    R(9) = (0 + 1);
    cr_cmp_u(ctx, 0, R(8), R(30));
    if ((!CR_BIT(ctx, 0))) { goto L_8183A9B8; }
    R(9) = (0 + 0);
L_8183A9B8:;
    R(8) = R(8) + R(9);
    st32(base, (R(7) + 4), R(8));
    R(7) = ld32(base, (R(29) + 8));
    R(7) = R(7) + R(4);
    R(8) = ld32(base, (R(7) + 8));
    cr_cmp_u(ctx, 0, R(8), R(30));
    if ((!CR_BIT(ctx, 0))) { goto L_8183A9D8; }
    R(6) = (0 + 0);
L_8183A9D8:;
    R(6) = R(8) + R(6);
    st32(base, (R(7) + 8), R(6));
L_8183A9E0:;
    R(3) = (R(3) + -1);
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(30));
    R(4) = (R(4) + -12);
    if ((!CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8183A96C; }
L_8183A9F0:;
    R(3) = R(29) |R(29);
    R(4) = R(5) |R(5);
    R(25) = ld32(base, (R(29) + 8));
    R(26) = ((int32_t)R(30) * 12);
    GM_CALLV(0x8183AA04u, 0x8183A78Cu, 0);
    { uint32_t a_ = R(27); R(4) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(4) < a_; }
    { uint64_t t_ = (uint64_t)(~R(4)) + (R(27)) + ctx->xer_ca; R(4) = t_; ctx->xer_ca = (t_ >> 32); }
    R(3) = (rotl32(R(4), 24) & 0xFF000000u) | (R(3) & ~0xFF000000u);
    R(4) = ld32(base, (R(28) + 4));
    cr_cmp_u(ctx, 0, R(27), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AA24; }
    R(5) = (R(30) + 1);
    goto L_8183AA28;
L_8183AA24:;
    R(5) = ld32(base, (R(28) + 8));
L_8183AA28:;
    { uint32_t ea_ = R(26) + R(25); st32(base, ea_, R(3)); R(26) = ea_; }
    st32(base, (R(26) + 4), R(4));
    st32(base, (R(26) + 8), R(5));
    R(3) = ld32(base, (R(29) + 12));
    R(3) = (R(3) + 1);
    st32(base, (R(29) + 12), R(3));
    R(3) = R(30) |R(30);
L_8183AA44:;
    R(0) = lr;
}

/* mfn_8183AA6C (mfn_8183AA6C, 956 bytes) */
static void mj_mfn_8183AA6C_3aa6c(GM_CTX) {
    GM_FN(0x8183AA6C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(12) = ctx->cr;
    R(25) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(4) = (0 + 0x81860000u);
    st32(base, (f + 44), R(12));
    R(24) = R(29) |R(29);
    R(4) = ld32(base, (R(4) + -300));
    st32(base, (f + 40), R(4));
    R(4) = ((int32_t)R(5) * 12);
    { uint32_t ea_ = R(24) + R(4); R(4) = ld32(base, ea_); R(24) = ea_; }
    R(5) = R(4) & 0xFF000000u;
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_8183ADEC; }
    R(28) = R(3) |R(3);
    R(3) = ld32(base, (R(29) + 8));
    R(30) = R(7) |R(7);
    R(5) = ld32(base, (R(28) + 12));
    R(26) = R(6) |R(6);
    R(3) = ((int32_t)R(3) * 12);
    R(20) = R(29) + R(3);
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    R(27) = R(6) |R(6);
    if ((!CR_BIT(ctx, 2))) { goto L_8183AB4C; }
    R(3) = ld32(base, (R(24) + 8));
    R(4) = R(4) & 0xFFFFFFu;
    R(5) = R(20) + R(4);
    R(4) = (f + 8);
    st32(base, (f + 16), R(3));
    R(6) = (0 + 0);
    R(3) = ld32(base, (R(24) + 4));
    R(7) = (0 + -1);
    st32(base, (f + 12), R(3));
    R(3) = ld32(base, (R(24) + 0));
    st32(base, (f + 8), R(3));
    R(3) = R(28) |R(28);
    GM_CALLV(0x8183AB40u, 0x8183A894u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8183AE0C; }
    R(27) = (R(3) + 1);
L_8183AB4C:;
    R(19) = ld32(base, (R(24) + 8));
    R(24) = (R(25) + 1);
    cr_cmp_u(ctx, 0, R(24), R(19));
    if ((!CR_BIT(ctx, 0))) { goto L_8183AD10; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1922);
    R(26) = (R(26) + -1);
    R(25) = (R(3) + 52);
L_8183AB6C:;
    R(3) = ((int32_t)R(24) * 12);
    R(18) = R(29) |R(29);
    { uint32_t ea_ = R(18) + R(3); R(3) = ld32(base, ea_); R(18) = ea_; }
    R(23) = R(20) |R(20);
    R(3) = R(3) & 0xFFFFFFu;
    { uint32_t ea_ = R(23) + R(3); R(3) = ld8(base, ea_); R(23) = ea_; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AD04; }
    R(3) = R(23) |R(23);
    R(4) = R(25) |R(25);
    GM_CALLV(0x8183AB98u, 0x802E1AB4u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AD04; }
    R(3) = ld32(base, (R(28) + 12));
    cr_cmp_u(ctx, 0, R(27), R(3));
    if ((!CR_BIT(ctx, 0))) { goto L_8183AC1C; }
    R(3) = ((int32_t)R(27) * 12);
    R(22) = (0 + 1);
L_8183ABB4:;
    R(17) = ld32(base, (R(28) + 8));
    R(16) = R(3) |R(3);
    R(21) = ld32(base, (R(28) + 20));
    R(3) = ld32(base, (R(17) + R(3)));
    R(3) = R(3) & 0xFFFFFFu;
    { uint32_t ea_ = R(21) + R(3); R(3) = ld8(base, ea_); R(21) = ea_; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AC00; }
    R(3) = R(21) |R(21);
    R(4) = R(25) |R(25);
    GM_CALLV(0x8183ABE0u, 0x802E1AB4u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AC00; }
    R(3) = R(23) |R(23);
    R(4) = R(21) |R(21);
    GM_CALLV(0x8183ABF4u, 0x802E1AB4u, 0);
    R(22) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8183AC14; }
L_8183AC00:;
    R(3) = ld32(base, (R(28) + 12));
    R(27) = (R(27) + 1);
    cr_cmp_u(ctx, 0, R(27), R(3));
    R(3) = (R(16) + 12);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8183ABB4; }
L_8183AC14:;
    R(3) = R(17) + R(16);
    goto L_8183AC24;
L_8183AC1C:;
    R(22) = (0 + 1);
    R(3) = (0 + 0);
L_8183AC24:;
    R(7) = ld32(base, (R(18) + 4));
    cr_cmp_u(ctx, 0, R(22), 0x0u);
    R(5) = ld32(base, (R(18) + 0));
    R(4) = ld32(base, (R(18) + 8));
    R(6) = rotl32(R(7), 30) & 0x3FFFFFFFu;
    R(6) = R(6) + R(30);
    R(8) = rotl32(R(5), 8) & 0xFFu;
    if ((CR_BIT(ctx, 2))) { goto L_8183ACB4; }
    cr_cmp_u(ctx, 2, R(8), 0x0u);
    if ((CR_BIT(ctx, 10))) { goto L_8183AC50; }
    R(6) = R(7) |R(7);
L_8183AC50:;
    st32(base, (f + 28), R(5));
    R(3) = R(28) |R(28);
    st32(base, (f + 32), R(6));
    R(7) = R(26) |R(26);
    st32(base, (f + 36), R(4));
    st32(base, (f + 16), R(4));
    R(4) = (f + 8);
    st32(base, (f + 12), R(6));
    R(6) = R(27) |R(27);
    st32(base, (f + 8), R(5));
    R(5) = R(23) |R(23);
    GM_CALLV(0x8183AC80u, 0x8183A894u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8183AD7C; }
    R(27) = (R(3) + 1);
    if ((CR_BIT(ctx, 10))) { goto L_8183AD04; }
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = R(24) |R(24);
    R(6) = R(27) |R(27);
    R(7) = R(30) |R(30);
    GM_CALLV(0x8183ACA8u, 0x8183AA6Cu, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_8183ACF8; }
    goto L_8183AD98;
L_8183ACB4:;
    cr_cmp_u(ctx, 0, R(8), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183ACCC; }
    st32(base, (R(3) + 4), R(6));
    R(27) = (R(27) + 1);
    st32(base, (R(3) + 8), R(4));
    goto L_8183AD04;
L_8183ACCC:;
    R(3) = ld8(base, (R(3) + 0));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183ADD0; }
    R(6) = (R(27) + 1);
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = R(24) |R(24);
    R(7) = R(30) |R(30);
    GM_CALLV(0x8183ACF0u, 0x8183AA6Cu, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8183ADB4; }
L_8183ACF8:;
    R(27) = R(3) |R(3);
    R(3) = ld32(base, (R(18) + 8));
    R(24) = (R(3) + -1);
L_8183AD04:;
    R(24) = (R(24) + 1);
    cr_cmp_u(ctx, 0, R(24), R(19));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8183AB6C; }
L_8183AD10:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 40));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8183AE08; }
    R(12) = ld32(base, (f + 44));
    R(3) = R(27) |R(27);
    ctx->cr = (ctx->cr & ~0xF00000u) | (R(12) & 0xF00000u);
    R(0) = lr;
    return;
L_8183AD7C:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1922);
    R(5) = (R(3) + 18);
    R(6) = (R(3) + 38);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 177);
    GM_CALLV(0x8183AD98u, 0x818380F8u, 0);
L_8183AD98:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1922);
    R(5) = (R(3) + 18);
    R(6) = (R(3) + 38);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 182);
    GM_CALLV(0x8183ADB4u, 0x818380F8u, 0);
L_8183ADB4:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1922);
    R(5) = (R(3) + 18);
    R(6) = (R(3) + 38);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 165);
    GM_CALLV(0x8183ADD0u, 0x818380F8u, 0);
L_8183ADD0:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1922);
    R(5) = (R(3) + 18);
    R(6) = (R(3) + 54);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 162);
    GM_CALLV(0x8183ADECu, 0x818380F8u, 0);
L_8183ADEC:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1922);
    R(5) = (R(3) + 18);
    R(6) = (R(3) + 172);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 117);
    GM_CALLV(0x8183AE08u, 0x818380F8u, 0);
L_8183AE08:;
    GM_CALLV(0x8183AE0Cu, 0x81844FCCu, 0);
L_8183AE0C:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1922);
    R(5) = (R(3) + 18);
    R(6) = (R(3) + 38);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 123);
    GM_CALLV(0x8183AE28u, 0x818380F8u, 0);
}

/* mfn_8183AE28 (mfn_8183AE28, 424 bytes) */
static void mj_mfn_8183AE28_3ae28(GM_CTX) {
    GM_FN(0x8183AE28); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(27) = R(3) |R(3);
    R(3) = ((int32_t)R(6) * 12);
    R(3) = R(4) + R(3);
    R(3) = ld32(base, (R(3) + 8));
    R(23) = ld32(base, (R(27) + 16));
    R(3) = R(3) - R(6);
    R(28) = R(4) |R(4);
    R(4) = R(3) + R(23);
    st32(base, (R(27) + 16), R(4));
    R(24) = ld32(base, (R(27) + 28));
    R(3) = ld32(base, (R(28) + 8));
    R(29) = R(6) |R(6);
    R(6) = ld32(base, (R(27) + 4));
    R(5) = R(24) + R(5);
    R(3) = ((int32_t)R(3) * -12);
    R(26) = (0 + -4);
    R(30) = R(7) |R(7);
    R(3) = R(5) + R(3);
    cr_cmp_u(ctx, 0, R(6), 0x2u);
    st32(base, (R(27) + 28), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8183AEAC; }
    R(26) = (0 + 4);
L_8183AEAC:;
    R(3) = ld32(base, (R(27) + 0));
    R(4) = ((int32_t)R(4) * 12);
    R(5) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(5) + 20));
    ctx->ctr = R(5);
    R(5) = R(26) |R(26);
    GM_CALLV(0x8183AEC8u, ctx->ctr, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AFB4; }
    R(25) = R(3) |R(3);
    R(3) = ld32(base, (R(27) + 0));
    R(4) = ld32(base, (R(27) + 28));
    R(5) = ld32(base, (R(3) + 0));
    R(5) = ld32(base, (R(5) + 20));
    ctx->ctr = R(5);
    R(5) = R(26) |R(26);
    GM_CALLV(0x8183AEF0u, ctx->ctr, 0);
    R(4) = ld32(base, (R(27) + 8));
    R(26) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AF2C; }
    R(6) = ((int32_t)R(23) * 12);
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AF24; }
    R(3) = (R(4) + -1);
    R(5) = (R(25) + -1);
    ctx->ctr = R(6);
L_8183AF18:;
    { uint32_t ea_ = R(3) + 1; R(6) = ld8(base, ea_); R(3) = ea_; }
    { uint32_t ea_ = R(5) + 1; st8(base, ea_, R(6)); R(5) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8183AF18; }
L_8183AF24:;
    R(3) = R(4) |R(4);
    GM_CALLV(0x8183AF2Cu, 0x802B9290u, 0);
L_8183AF2C:;
    R(3) = ld32(base, (R(27) + 20));
    st32(base, (R(27) + 8), R(25));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AF60; }
    cr_cmp_u(ctx, 0, R(24), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183AF5C; }
    R(4) = (R(3) + -1);
    R(5) = (R(26) + -1);
    ctx->ctr = R(24);
L_8183AF50:;
    { uint32_t ea_ = R(4) + 1; R(6) = ld8(base, ea_); R(4) = ea_; }
    { uint32_t ea_ = R(5) + 1; st8(base, ea_, R(6)); R(5) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8183AF50; }
L_8183AF5C:;
    GM_CALLV(0x8183AF60u, 0x802B9290u, 0);
L_8183AF60:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    R(6) = (0 + 1);
    R(7) = R(30) |R(30);
    st32(base, (R(27) + 20), R(26));
    GM_CALLV(0x8183AF7Cu, 0x8183AA6Cu, 0);
    R(3) = ~(R(3) | R(3));
    R(3) = rotl32(R(3), 1) & 0x1u;
    R(0) = lr;
    return;
L_8183AFB4:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1922);
    R(5) = (R(3) + 18);
    R(6) = (R(3) + 70);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 207);
    GM_CALLV(0x8183AFD0u, 0x818380F8u, 0);
}

/* mod_create__4mPadFv (mod_create__4mPadFv, 224 bytes) */
static void mj_mod_create__4mPadFv_3ba58(GM_CTX) {
    GM_FN(0x8183BA58); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -20880));
    R(4) = (0 + 0x80430000u);
    R(5) = (0 + 0x81860000u);
    R(27) = (0 + 0);
    st32(base, (R(4) + -23456), R(3));
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -1144);
    R(28) = (R(3) + -1);
    R(29) = (0 + 12);
    R(30) = (R(5) + -1132);
L_8183BAA0:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    R(5) = (0 + 24);
    GM_CALLV(0x8183BAB0u, 0x81844D68u, 0);
    R(29) = (R(29) + -1);
    { uint32_t ea_ = R(28) + 1; st8(base, ea_, R(27)); R(28) = ea_; }
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(30) = (R(30) + 24);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183BAA0; }
    GM_CALLV(0x8183BAC8u, 0x8183BBB4u, 0);
    R(3) = (0 + 12);
    R(4) = (0 + 0x81860000u);
    ctx->ctr = R(3);
    R(3) = (0 + 0x81860000u);
    R(4) = (R(4) + -1252);
    R(5) = (R(3) + -1204);
    R(3) = (R(4) + -4);
    R(4) = (R(5) + -4);
L_8183BAE8:;
    { uint32_t ea_ = R(4) + 4; R(5) = ld32(base, ea_); R(4) = ea_; }
    { uint32_t ea_ = R(3) + 4; st32(base, ea_, R(5)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8183BAE8; }
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23456));
    R(4) = ld32(base, (R(3) + 16));
    R(4) = ld32(base, (R(4) + 12));
    ctx->ctr = R(4);
    GM_CALLV(0x8183BB0Cu, ctx->ctr, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -308));
    GM_CALLV(0x8183BB18u, 0x81844A50u, 0);
    R(0) = lr;
}

/* mod_fn_8016F550 (mod_fn_8016F550, 124 bytes) */
static void mj_mod_fn_8016F550_3bb38(GM_CTX) {
    GM_FN(0x8183BB38); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = (0 + 0x81860000u);
    R(30) = (R(3) + -1132);
    R(3) = (R(4) + -1144);
    R(27) = (0 + 0);
    R(28) = (R(3) + -1);
    R(29) = (0 + 12);
L_8183BB70:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    R(5) = (0 + 24);
    GM_CALLV(0x8183BB80u, 0x81844D68u, 0);
    R(29) = (R(29) + -1);
    { uint32_t ea_ = R(28) + 1; st8(base, ea_, R(27)); R(28) = ea_; }
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(30) = (R(30) + 24);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183BB70; }
    R(0) = lr;
}

/* mod_beginPad__4mPadFv (mod_beginPad__4mPadFv, 1160 bytes) */
static void mj_mod_beginPad__4mPadFv_3bbb4(GM_CTX) {
    GM_FN(0x8183BBB4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80430000u);
    R(26) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(26) + -23456));
    R(5) = ld32(base, (R(4) + -23440));
    R(6) = ld32(base, (R(3) + 16));
    R(5) = (R(5) + 1);
    st32(base, (R(4) + -23440), R(5));
    R(4) = ld32(base, (R(6) + 8));
    ctx->ctr = R(4);
    GM_CALLV(0x8183BC2Cu, ctx->ctr, 0);
    R(3) = (0 + 0x81860000u);
    R(30) = ld32(base, (R(3) + -308));
    R(3) = R(30) |R(30);
    GM_CALLV(0x8183BC3Cu, 0x8184499Cu, 0);
    R(3) = (0 + 0x81860000u);
    R(4) = (0 + 0x80370000u);
    R(5) = (0 + 0x81860000u);
    R(6) = (0 + 0x81860000u);
    R(7) = (0 + 0x81860000u);
    R(29) = (R(3) + -1132);
    R(3) = (R(4) + 31912);
    R(4) = (R(5) + -1156);
    R(5) = (R(6) + -1204);
    R(25) = (0 + 4);
    R(24) = (0 + 0);
    R(23) = (0 + 1);
    R(22) = (0 + 0x80430000u);
    R(21) = (0 + 0x80430000u);
    R(20) = (R(7) + -1144);
    R(18) = (R(3) + -24);
    R(17) = (R(4) + -1);
    R(19) = (R(5) + -4);
    R(28) = (0 + 0);
L_8183BC88:;
    R(3) = ld32(base, (R(26) + -23456));
    R(15) = R(18) |R(18);
    R(4) = R(28) |R(28);
    R(16) = R(17) |R(17);
    R(18) = (R(18) + 24);
    R(14) = (R(15) + 32);
    R(17) = (R(17) + 1);
    GM_CALLV(0x8183BCA8u, 0x802BD370u, 0);
    R(27) = R(3) |R(3);
    R(3) = ld8(base, (R(3) + 2844));
    { uint32_t ea_ = R(19) + 4; st32(base, ea_, R(27)); R(19) = ea_; }
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_8183BD0C; }
    R(3) = ld8(base, (R(16) + 1));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183BD78; }
    R(3) = (R(27) + 24);
    R(4) = (0 + 0);
    R(5) = (0 + 176);
    GM_CALLV(0x8183BCD8u, 0x81844D68u, 0);
    R(3) = R(27) |R(27);
    GM_CALLV(0x8183BCE0u, 0x802BC800u, 0);
    R(3) = (R(14) + -8);
    R(4) = (0 + 0);
    R(5) = (0 + 24);
    GM_CALLV(0x8183BCF0u, 0x81844D68u, 0);
    R(3) = R(29) |R(29);
    R(4) = (0 + 0);
    R(5) = (0 + 24);
    GM_CALLV(0x8183BD00u, 0x81844D68u, 0);
    st8(base, (R(20) + R(28)), R(24));
    st8(base, (R(16) + 1), R(24));
    goto L_8183BD78;
L_8183BD0C:;
    { uint32_t ea_ = (R(27) + 108); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(27) + 112); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(15) + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(15) + 28); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(15) + 32); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(15) + 36); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(15) + 28); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[3].d);
    { uint32_t ea_ = (R(15) + 24); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (R(15) + 36); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[5].d);
    { uint32_t ea_ = (R(15) + 32); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[4].d);
    { uint32_t ea_ = (R(15) + 44); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(15) + 40); stfs(base, ea_, ctx->f[0].d); }
    R(3) = ld32(base, (R(22) + -23432));
    st8(base, (R(16) + 1), R(23));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183BD78; }
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8183BD70; }
    R(4) = ld32(base, (R(21) + -23428));
    cr_cmp_u(ctx, 0, R(28), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8183BD90; }
L_8183BD70:;
    R(3) = R(28) |R(28);
    GM_CALLV(0x8183BD78u, 0x8016F5D0u, 0);
L_8183BD78:;
    R(25) = (R(25) + -1);
    R(28) = (R(28) + 1);
    cr_cmp_u(ctx, 0, R(25), 0x0u);
    R(29) = (R(29) + 24);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183BC88; }
    goto L_8183BDA8;
L_8183BD90:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183BD78; }
    R(3) = R(4) ^R(28);
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8183BD70; }
    GM_LOOP(); goto L_8183BD78;
L_8183BDA8:;
    R(3) = (0 + 0x81860000u);
    R(4) = (0 + 0x81860000u);
    R(5) = (0 + 0x81860000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(3) + -1132);
    R(24) = (R(4) + -1156);
    R(4) = (R(5) + -1204);
    R(29) = (0 + 4);
    R(28) = (0 + 8);
    R(27) = (0 + 0x80430000u);
    R(26) = (0 + 0x80430000u);
    R(25) = (0 + 0);
    R(23) = (R(6) + -1144);
    R(19) = (R(3) + 168);
    R(22) = (R(24) + -1);
    R(21) = (R(4) + 28);
    R(20) = (0 + 0x80430000u);
L_8183BDEC:;
    R(3) = ld32(base, (R(27) + -23456));
    R(4) = (R(28) + -8);
    R(18) = R(19) |R(19);
    R(19) = (R(19) + 24);
    GM_CALLV(0x8183BE00u, 0x802BD370u, 0);
    { uint32_t ea_ = R(22) + 1; R(4) = ld8(base, ea_); R(22) = ea_; }
    R(5) = ld32(base, (R(3) + 20));
    R(3) = R(24) |R(24);
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    R(4) = (0 + 0);
    { uint32_t ea_ = R(21) + 4; st32(base, ea_, R(5)); R(21) = ea_; }
    if ((!CR_BIT(ctx, 2))) { goto L_8183BE94; }
    R(5) = ld32(base, (R(5) + 44));
    R(3) = ld8(base, (R(5) + 2844));
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    R(3) = R(24) |R(24);
    if ((CR_BIT(ctx, 2))) { goto L_8183BE94; }
    R(3) = ld8(base, (R(5) + 116));
    R(4) = R(3) ^ 0x2u;
    R(4) = cntlzw(R(4));
    R(4) = rotl32(R(4), 27) & 0x7FFFFFFu;
    cr_cmp_u(ctx, 0, R(3), 0x2u);
    st8(base, (R(22) + 8), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8183BE98; }
    R(3) = ld32(base, (R(26) + -23432));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183BE98; }
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8183BE6C; }
    R(4) = ld32(base, (R(20) + -23428));
    cr_cmp_u(ctx, 0, R(28), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8183BEAC; }
L_8183BE6C:;
    R(4) = (0 + 1);
    R(3) = R(23) |R(23);
    st32(base, (R(18) + 24), R(25));
    st32(base, (R(18) + 28), R(25));
    st32(base, (R(18) + 32), R(25));
    st32(base, (R(18) + 36), R(25));
    st32(base, (R(18) + 40), R(25));
    st16(base, (R(18) + 44), R(25));
    st8(base, (R(18) + 46), R(25));
    st8(base, (R(18) + 47), R(25));
L_8183BE94:;
    st8(base, (R(3) + R(28)), R(4));
L_8183BE98:;
    R(29) = (R(29) + -1);
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(28) = (R(28) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183BDEC; }
    goto L_8183BEC4;
L_8183BEAC:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183BE98; }
    R(3) = R(4) ^R(28);
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8183BE6C; }
    GM_LOOP(); goto L_8183BE98;
L_8183BEC4:;
    R(3) = (0 + 0x81860000u);
    R(4) = (0 + 0x81860000u);
    R(5) = (0 + 0x81860000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(3) + -1132);
    R(4) = (R(4) + -1156);
    R(5) = (R(5) + -1204);
    R(29) = (0 + 4);
    R(28) = (0 + 0x80430000u);
    R(27) = (0 + 0);
    R(26) = (0 + 1);
    R(25) = (0 + 0x80430000u);
    R(24) = (R(6) + -1144);
    R(21) = (R(3) + 72);
    R(23) = (R(4) + 3);
    R(22) = (R(5) + 12);
    R(20) = (0 + 4);
L_8183BF08:;
    R(4) = (R(29) + -4);
    R(3) = R(30) |R(30);
    R(19) = R(21) |R(21);
    R(21) = (R(21) + 24);
    GM_CALLV(0x8183BF1Cu, 0x818448D8u, 0);
    R(4) = ld8(base, (R(3) + 48));
    { uint32_t ea_ = R(22) + 4; st32(base, ea_, R(3)); R(22) = ea_; }
    R(4) = R(4) & 0x1u;
    CR0(ctx, R(4));
    { uint32_t ea_ = R(23) + 1; st8(base, ea_, R(4)); R(23) = ea_; }
    if ((CR_BIT(ctx, 2))) { goto L_8183BF74; }
    R(3) = ld32(base, (R(28) + -23432));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183BF74; }
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8183BF50; }
    R(4) = ld32(base, (R(25) + -23428));
    cr_cmp_u(ctx, 0, R(29), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8183BF88; }
L_8183BF50:;
    st32(base, (R(19) + 24), R(27));
    st32(base, (R(19) + 28), R(27));
    st32(base, (R(19) + 32), R(27));
    st32(base, (R(19) + 36), R(27));
    st32(base, (R(19) + 40), R(27));
    st16(base, (R(19) + 44), R(27));
    st8(base, (R(19) + 46), R(27));
    st8(base, (R(19) + 47), R(27));
    st8(base, (R(24) + R(29)), R(26));
L_8183BF74:;
    R(20) = (R(20) + -1);
    cr_cmp_u(ctx, 0, R(20), 0x0u);
    R(29) = (R(29) + 1);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183BF08; }
    goto L_8183BFA0;
L_8183BF88:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183BF74; }
    R(3) = R(4) ^R(29);
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8183BF50; }
    GM_LOOP(); goto L_8183BF74;
L_8183BFA0:;
    R(3) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(3) + -23432));
    R(3) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(3) + -23428));
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(4));
    if ((CR_BIT(ctx, 1))) { goto L_8183BFC0; }
    R(4) = (0 + 0);
    goto L_8183BFC4;
L_8183BFC0:;
    R(4) = (R(4) + 1);
L_8183BFC4:;
    R(5) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(5) + -23452));
    R(6) = (0 + 0x81860000u);
    R(6) = (R(6) + -1252);
    st32(base, (R(3) + -23428), R(4));
    R(5) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(5) = ld32(base, (R(6) + R(5)));
    R(3) = (0 + 0x80430000u);
    st32(base, (R(3) + -23448), R(5));
    R(0) = lr;
}

/* mod_endPad__4mPadFv (mod_endPad__4mPadFv, 64 bytes) */
static void mj_mod_endPad__4mPadFv_3c03c(GM_CTX) {
    GM_FN(0x8183C03C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23456));
    R(4) = ld32(base, (R(3) + 16));
    R(4) = ld32(base, (R(4) + 12));
    ctx->ctr = R(4);
    GM_CALLV(0x8183C060u, ctx->ctr, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -308));
    GM_CALLV(0x8183C06Cu, 0x81844A50u, 0);
    R(0) = lr;
}

/* mod_fn_8016F460 (mod_fn_8016F460, 60 bytes) */
static void mj_mod_fn_8016F460_3c0d8(GM_CTX) {
    R(4) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    R(3) = (0 + 4);
    if ((CR_BIT(ctx, 1))) return;
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -1144);
    R(5) = ld8(base, (R(5) + R(4)));
    cr_cmp_u(ctx, 0, R(5), 0x1u);
    if ((!CR_BIT(ctx, 2))) return;
    R(3) = ((int32_t)R(4) * 24);
    R(4) = (0 + 0x81860000u);
    R(4) = (R(4) + -1132);
    R(3) = R(4) + R(3);
    R(3) = ld8(base, (R(3) + 20));
}

/* mfn_8183C114 (mfn_8183C114, 176 bytes) */
static void mj_mfn_8183C114_3c114(GM_CTX) {
    GM_FN(0x8183C114); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_u(ctx, 0, R(4), 0xCu);
    R(29) = R(3) |R(3);
    R(30) = R(4) |R(4);
    R(7) = (0 + 0);
    if ((CR_BIT(ctx, 1))) { goto L_8183C14C; }
    R(4) = (0 + 0x81850000u);
    R(3) = rotl32(R(30), 3) & 0xFFFFFFF8u;
    R(4) = (R(4) + 8932);
    R(7) = ld32(base, (R(4) + R(3)));
L_8183C14C:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + -1417);
    R(3) = (R(4) + 39);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 259);
    R(6) = R(29) |R(29);
    GM_CALLV(0x8183C168u, 0x8015F730u, 0);
    R(5) = (0 + 0x81860000u);
    R(4) = rotl32(R(30), 2) & 0xFFFFFFFCu;
    R(5) = (R(5) + -1204);
    R(4) = ld32(base, (R(5) + R(4)));
    R(5) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(5) + -23452));
    R(6) = (0 + 0x81860000u);
    R(3) = rotl32(R(29), 2) & 0xFFFFFFFCu;
    R(6) = (R(6) + -1252);
    st32(base, (R(6) + R(3)), R(4));
    R(4) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(4) = ld32(base, (R(6) + R(4)));
    R(5) = (0 + 0x81850000u);
    R(5) = (R(5) + 17060);
    st32(base, (R(5) + R(3)), R(30));
    R(3) = (0 + 0x80430000u);
    st32(base, (R(3) + -23448), R(4));
    R(0) = lr;
}

/* ctor_8183C1C4 (ctor_8183C1C4, 384 bytes) */
static void mj_ctor_8183C1C4_3c1c4(GM_CTX) {
    GM_FN(0x8183C1C4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23444));
    R(4) = (0 + 0x81860000u);
    R(5) = (0 + 8);
    { uint32_t ea_ = R(4) + -1156; st32(base, ea_, R(3)); R(4) = ea_; }
    R(3) = (R(4) + 3);
    R(4) = (0 + 0);
    ctx->ctr = R(5);
L_8183C1F8:;
    { uint32_t ea_ = R(3) + 1; st8(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8183C1F8; }
    R(4) = (0 + 0x80430000u);
    { uint32_t ea_ = R(4) + -23436; R(5) = ld8(base, ea_); R(4) = ea_; }
    R(3) = (0 + 0x81860000u);
    R(6) = ld8(base, (R(4) + 1));
    { uint32_t ea_ = R(3) + -1144; st8(base, ea_, R(5)); R(3) = ea_; }
    R(5) = ld8(base, (R(4) + 2));
    R(4) = ld8(base, (R(4) + 3));
    st8(base, (R(3) + 1), R(6));
    st8(base, (R(3) + 2), R(5));
    R(5) = (0 + 8);
    { uint32_t ea_ = R(3) + 3; st8(base, ea_, R(4)); R(3) = ea_; }
    R(4) = (0 + 0);
    ctx->ctr = R(5);
L_8183C234:;
    { uint32_t ea_ = R(3) + 1; st8(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8183C234; }
    R(3) = (0 + 0x81860000u);
    R(4) = (0 + 0x80370000u);
    R(30) = (R(3) + -1132);
    R(29) = (R(4) + 32008);
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C25Cu, 0x81844C38u, 0);
    R(3) = (R(30) + 24);
    R(4) = (R(29) + 24);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C26Cu, 0x81844C38u, 0);
    R(3) = (R(30) + 48);
    R(4) = (R(29) + 48);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C27Cu, 0x81844C38u, 0);
    R(3) = (R(30) + 72);
    R(4) = (R(29) + 72);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C28Cu, 0x81844C38u, 0);
    R(29) = (0 + 8);
    R(30) = (R(30) + 96);
L_8183C294:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C2A4u, 0x81844D68u, 0);
    R(29) = (R(29) + -1);
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(30) = (R(30) + 24);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183C294; }
    R(3) = (0 + 0x81860000u);
    R(4) = (0 + 0x80370000u);
    R(30) = (R(3) + -844);
    R(29) = (R(4) + 32104);
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C2D4u, 0x81844C38u, 0);
    R(3) = (R(30) + 24);
    R(4) = (R(29) + 24);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C2E4u, 0x81844C38u, 0);
    R(3) = (R(30) + 48);
    R(4) = (R(29) + 48);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C2F4u, 0x81844C38u, 0);
    R(3) = (R(30) + 72);
    R(4) = (R(29) + 72);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C304u, 0x81844C38u, 0);
    R(29) = (0 + 8);
    R(30) = (R(30) + 96);
L_8183C30C:;
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    R(5) = (0 + 24);
    GM_CALLV(0x8183C31Cu, 0x81844D68u, 0);
    R(29) = (R(29) + -1);
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(30) = (R(30) + 24);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_8183C30C; }
    R(0) = lr;
}

/* mfn_8183C5AC (mfn_8183C5AC, 444 bytes) */
static void mj_mfn_8183C5AC_3c5ac(GM_CTX) {
    GM_FN(0x8183C5AC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (f + 24);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    st32(base, (f + 28), R(3));
    R(3) = (0 + 0);
    st32(base, (f + 24), R(3));
    st32(base, (f + 20), R(3));
    R(3) = (0 + 0x81850000u);
    R(29) = (R(3) + -1346);
    R(3) = (R(29) + 75);
    GM_CALLV(0x8183C5F4u, 0x8183A558u, 0);
    R(3) = (R(29) + 110);
    R(4) = (f + 20);
    GM_CALLV(0x8183C600u, 0x8183A558u, 0);
    R(4) = ld32(base, (f + 24));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183C6E0; }
    R(3) = ld32(base, (f + 20));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183C6E0; }
    R(30) = (R(30) + 12);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8183C624u, 0x8027A330u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183C6F8; }
    R(4) = ld32(base, (f + 20));
    R(28) = R(3) |R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8183C63Cu, 0x8027A330u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183C714; }
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81850000u);
    R(29) = (R(3) + -1346);
    R(3) = (R(29) + 75);
    R(4) = R(28) |R(28);
    R(5) = (0 + 0);
    R(6) = (0 + 1);
    R(7) = (0 + 0);
    R(8) = (0 + 0);
    R(9) = (0 + 0);
    GM_CALLV(0x8183C670u, 0x8183A2F8u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183C730; }
    R(28) = R(3) |R(3);
    R(3) = (R(29) + 110);
    R(4) = R(30) |R(30);
    R(5) = (0 + 0);
    R(6) = (0 + 1);
    R(7) = (0 + 0);
    R(8) = (0 + 0);
    R(9) = (0 + 0);
    GM_CALLV(0x8183C69Cu, 0x8183A2F8u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8183C748; }
    R(4) = R(3) |R(3);
    R(3) = R(28) |R(28);
    GM_CALLV(0x8183C6B0u, 0x81843020u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 28));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8183C764; }
    R(0) = lr;
    return;
L_8183C6E0:;
    R(5) = (R(29) + 16);
    R(6) = (R(29) + 146);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(3) = R(29) |R(29);
    R(4) = (0 + 31);
    GM_CALLV(0x8183C6F8u, 0x818380F8u, 0);
L_8183C6F8:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1346);
    R(5) = (R(3) + 16);
    R(6) = (R(3) + 36);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 33);
    GM_CALLV(0x8183C714u, 0x818380F8u, 0);
L_8183C714:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1346);
    R(5) = (R(3) + 16);
    R(6) = (R(3) + 55);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 35);
    GM_CALLV(0x8183C730u, 0x818380F8u, 0);
L_8183C730:;
    R(5) = (R(29) + 16);
    R(6) = (R(29) + 36);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(3) = R(29) |R(29);
    R(4) = (0 + 42);
    GM_CALLV(0x8183C748u, 0x818380F8u, 0);
L_8183C748:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + -1346);
    R(5) = (R(3) + 16);
    R(6) = (R(3) + 55);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 48);
    GM_CALLV(0x8183C764u, 0x818380F8u, 0);
L_8183C764:;
    GM_CALLV(0x8183C768u, 0x81844FCCu, 0);
}

/* mfn_8183C768 (mfn_8183C768, 96 bytes) */
static void mj_mfn_8183C768_3c768(GM_CTX) {
    GM_FN(0x8183C768); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8183C78Cu, 0x80197380u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 9428);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    st32(base, (R(30) + 0), R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_8183C7AC; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 172);
    GM_CALLV(0x8183C7ACu, 0x818434F4u, 0);
L_8183C7AC:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mfn_8183C7C8 (mfn_8183C7C8, 96 bytes) */
static void mj_mfn_8183C7C8_3c7c8(GM_CTX) {
    GM_FN(0x8183C7C8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8183C7ECu, 0x80197380u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 9492);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    st32(base, (R(30) + 0), R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_8183C80C; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 380);
    GM_CALLV(0x8183C80Cu, 0x818434F4u, 0);
L_8183C80C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mod_fn_80198BB0 (mod_fn_80198BB0, 96 bytes) */
static void mj_mod_fn_80198BB0_3c828(GM_CTX) {
    GM_FN(0x8183C828); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8183C84Cu, 0x80197380u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 9492);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    st32(base, (R(30) + 0), R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_8183C86C; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 380);
    GM_CALLV(0x8183C86Cu, 0x818434F4u, 0);
L_8183C86C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mfn_8183CB74 (mfn_8183CB74, 96 bytes) */
static void mj_mfn_8183CB74_3cb74(GM_CTX) {
    GM_FN(0x8183CB74); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8183CB98u, 0x80197380u, 0);
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 9428);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    st32(base, (R(30) + 0), R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_8183CBB8; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 184);
    GM_CALLV(0x8183CBB8u, 0x818434F4u, 0);
L_8183CBB8:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* ctor_8183CEC4 (ctor_8183CEC4, 80 bytes) */
static void mj_ctor_8183CEC4_3cec4(GM_CTX) {
    GM_FN(0x8183CEC4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -552));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183CF04; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x81850000u);
    st8(base, (R(3) + -552), R(4));
    R(4) = (0 + 0x81840000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 17440);
    R(4) = (R(4) + -12524);
    R(5) = (R(6) + -544);
    GM_CALLV(0x8183CF04u, 0x81844EF4u, 0);
L_8183CF04:;
    R(0) = lr;
}

/* ctor_8183D078 (ctor_8183D078, 80 bytes) */
static void mj_ctor_8183D078_3d078(GM_CTX) {
    GM_FN(0x8183D078); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(3) + -528));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8183D0B8; }
    R(4) = (0 + 1);
    R(5) = (0 + 0x81850000u);
    st8(base, (R(3) + -528), R(4));
    R(4) = (0 + 0x81840000u);
    R(6) = (0 + 0x81860000u);
    R(3) = (R(5) + 17488);
    R(4) = (R(4) + -12524);
    R(5) = (R(6) + -520);
    GM_CALLV(0x8183D0B8u, 0x81844EF4u, 0);
L_8183D0B8:;
    R(0) = lr;
}

/* mfn_8183EA10 (mfn_8183EA10, 44 bytes) */
static void mj_mfn_8183EA10_3ea10(GM_CTX) {
    GM_FN(0x8183EA10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81840000u);
    R(3) = (R(3) + -5572);
    R(4) = (0 + 0);
    GM_CALLV(0x8183EA2Cu, 0x802356D0u, 0);
    R(0) = lr;
}

/* ctor_8183F498 (ctor_8183F498, 164 bytes) */
static void mj_ctor_8183F498_3f498(GM_CTX) {
    R(3) = (0 + 0x80000000u);
    R(3) = ld8(base, (R(3) + 26500));
    R(5) = (0 + 0x81860000u);
    R(4) = (0 + 0x80000000u);
    R(4) = ld8(base, (R(4) + 26518));
    { uint32_t ea_ = R(5) + -508; st8(base, ea_, R(3)); R(5) = ea_; }
    R(3) = (0 + 0x80000000u);
    R(3) = ld8(base, (R(3) + 26507));
    st8(base, (R(5) + 1), R(4));
    R(4) = (0 + 0x80000000u);
    st8(base, (R(5) + 2), R(3));
    R(3) = (0 + 0x80000000u);
    R(4) = ld8(base, (R(4) + 26508));
    R(3) = ld8(base, (R(3) + 26502));
    st8(base, (R(5) + 3), R(4));
    R(4) = (0 + 0x80000000u);
    st8(base, (R(5) + 4), R(3));
    R(3) = (0 + 0x80000000u);
    R(4) = ld8(base, (R(4) + 26503));
    R(3) = ld8(base, (R(3) + 26509));
    st8(base, (R(5) + 5), R(4));
    R(4) = (0 + 0x80000000u);
    st8(base, (R(5) + 6), R(3));
    R(3) = (0 + 0x80000000u);
    R(4) = ld8(base, (R(4) + 26510));
    R(3) = ld8(base, (R(3) + 26504));
    st8(base, (R(5) + 7), R(4));
    R(4) = (0 + 0x80000000u);
    st8(base, (R(5) + 8), R(3));
    R(3) = (0 + 0x80000000u);
    R(4) = ld8(base, (R(4) + 26511));
    R(3) = ld8(base, (R(3) + 26516));
    st8(base, (R(5) + 9), R(4));
    R(4) = (0 + 0x80000000u);
    st8(base, (R(5) + 10), R(3));
    R(3) = (0 + 0x81860000u);
    R(4) = ld8(base, (R(4) + 26517));
    R(3) = ld8(base, (R(3) + -6544));
    st8(base, (R(5) + 11), R(4));
    st8(base, (R(5) + 12), R(3));
}

/* mfn_818409A4 (mfn_818409A4, 268 bytes) */
static void mj_mfn_818409A4_409a4(GM_CTX) {
    GM_FN(0x818409A4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(27) = R(5) |R(5);
    R(29) = R(3) |R(3);
    R(30) = R(4) |R(4);
    R(4) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(4) + -300));
    R(28) = R(30) |R(30);
    st32(base, (f + 52), R(4));
    { uint32_t ea_ = R(28) + 552; R(4) = ld8(base, ea_); R(28) = ea_; }
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81840A0C; }
    R(26) = (f + 8);
    R(3) = R(26) |R(26);
    R(4) = R(30) |R(30);
    GM_CALLV(0x818409FCu, 0x81838720u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(26) |R(26);
    R(5) = (0 + 34);
    GM_CALLV(0x81840A0Cu, 0x81844C38u, 0);
L_81840A0C:;
    R(3) = ld8(base, (R(30) + 553));
    cr_cmp_u(ctx, 0, R(3), R(27));
    if ((!CR_BIT(ctx, 2))) { goto L_81840A54; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (0 + 40);
    GM_CALLV(0x81840A28u, 0x81844C38u, 0);
    R(3) = (0 + 11);
    st16(base, (R(30) + 552), R(3));
    R(3) = (0 + 0);
    st32(base, (R(30) + 556), R(3));
    st32(base, (R(30) + 560), R(3));
    st32(base, (R(30) + 572), R(3));
    st32(base, (R(30) + 568), R(3));
    st32(base, (R(30) + 580), R(3));
    st32(base, (R(30) + 576), R(3));
    st16(base, (R(30) + 584), R(3));
    goto L_81840A74;
L_81840A54:;
    R(3) = R(29) |R(29);
    R(4) = (0 + 0);
    R(5) = (0 + 40);
    R(30) = (0 + 0);
    GM_CALLV(0x81840A68u, 0x81844D68u, 0);
    R(3) = (0 + 11);
    st8(base, (R(29) + 1), R(3));
    st32(base, (R(29) + 8), R(30));
L_81840A74:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 52));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81840AAC; }
    R(0) = lr;
    return;
L_81840AAC:;
    GM_CALLV(0x81840AB0u, 0x81844FCCu, 0);
}

/* mfn_81840AB0 (mfn_81840AB0, 184 bytes) */
static void mj_mfn_81840AB0_40ab0(GM_CTX) {
    GM_FN(0x81840AB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = (0 + -1);
    st32(base, (R(29) + 24), R(3));
    st32(base, (R(29) + 28), R(3));
    R(3) = (0 + 11);
    st16(base, (R(29) + 552), R(3));
    R(3) = (0 + 0x81840000u);
    R(3) = (R(3) + 2920);
    st32(base, (R(29) + 32), R(3));
    R(3) = ld32(base, (R(5) + 0));
    R(30) = R(4) |R(4);
    R(4) = ld32(base, (R(5) + 4));
    R(28) = (R(29) + 592);
    R(27) = (0 + 0);
    st32(base, (R(29) + 0), R(3));
    R(3) = R(28) |R(28);
    st32(base, (R(29) + 8), R(27));
    st32(base, (R(29) + 12), R(27));
    st32(base, (R(29) + 16), R(27));
    st16(base, (R(29) + 20), R(27));
    st8(base, (R(29) + 22), R(27));
    st32(base, (R(29) + 36), R(29));
    st32(base, (R(29) + 556), R(27));
    st32(base, (R(29) + 560), R(27));
    st32(base, (R(29) + 4), R(4));
    GM_CALLV(0x81840B34u, 0x802B7B00u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(30) |R(30);
    GM_CALLV(0x81840B40u, 0x802B7CB0u, 0);
    st32(base, (R(29) + 836), R(27));
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* mfn_81840B68 (mfn_81840B68, 128 bytes) */
static void mj_mfn_81840B68_40b68(GM_CTX) {
    GM_FN(0x81840B68); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = (R(5) + 592);
    R(29) = R(3) |R(3);
    R(3) = R(28) |R(28);
    R(27) = R(4) |R(4);
    R(30) = R(5) |R(5);
    GM_CALLV(0x81840B9Cu, 0x8008F750u, 0);
    R(6) = ld32(base, (R(30) + 836));
    R(5) = R(3) - R(6);
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(27));
    if ((CR_BIT(ctx, 0))) { goto L_81840BB0; }
    R(5) = R(27) |R(27);
L_81840BB0:;
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    GM_CALLV(0x81840BBCu, 0x802B7D70u, 0);
    R(4) = ld32(base, (R(30) + 836));
    R(4) = R(4) + R(3);
    st32(base, (R(30) + 836), R(4));
    R(0) = lr;
}

/* mfn_81840BE8 (mfn_81840BE8, 108 bytes) */
static void mj_mfn_81840BE8_40be8(GM_CTX) {
    GM_FN(0x81840BE8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(30) = R(4) |R(4);
    GM_CALLV(0x81840C08u, 0x8183EA10u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24432));
    R(5) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(5) + -24428));
    R(4) = ld16(base, (R(3) + 28));
    R(4) = R(4) & 0xFFFEu;
    st16(base, (R(3) + 28), R(4));
    R(4) = R(30) |R(30);
    R(3) = ld16(base, (R(5) + 28));
    R(3) = R(3) & 0xFFFEu;
    st16(base, (R(5) + 28), R(3));
    R(3) = R(29) |R(29);
    GM_CALLV(0x81840C3Cu, 0x81841460u, 0);
    R(0) = lr;
}

/* mfn_81840C54 (mfn_81840C54, 316 bytes) */
static void mj_mfn_81840C54_40c54(GM_CTX) {
    GM_FN(0x81840C54); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x80370000u);
    R(3) = ld32(base, (R(3) + 31816));
    GM_CALLV(0x81840C80u, 0x8016E4F0u, 0);
    R(29) = R(3) |R(3);
    GM_CALLV(0x81840C88u, 0x81844664u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -20880));
    GM_CALLV(0x81840C94u, 0x81844184u, 0);
    GM_CALLV(0x81840C98u, 0x8183BA58u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -6424);
    R(4) = (R(3) + 8);
    GM_CALLV(0x81840CA8u, 0x8016B090u, 0);
    R(3) = (0 + 92);
    GM_CALLV(0x81840CB0u, 0x818432E4u, 0);
    R(27) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(27) + -24536));
    R(28) = R(3) |R(3);
    GM_CALLV(0x81840CC0u, 0x8181273Cu, 0);
    st32(base, (R(27) + -24536), R(28));
    GM_CALLV(0x81840CC8u, 0x818119ACu, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24512));
    GM_CALLV(0x81840CD4u, 0x800E02D0u, 0);
    R(3) = (0 + 3032);
    GM_CALLV(0x81840CDCu, 0x818432E4u, 0);
    R(27) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(27) + -24708));
    R(28) = R(3) |R(3);
    GM_CALLV(0x81840CECu, 0x8180BF3Cu, 0);
    st32(base, (R(27) + -24708), R(28));
    GM_CALLV(0x81840CF4u, 0x8005EA60u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -23416));
    GM_CALLV(0x81840D00u, 0x8183C5ACu, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81840D08u, 0x81840D90u, 0);
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 3847);
    R(7) = (R(30) + 64);
    R(3) = (R(4) + 59);
    R(4) = (R(4) + 10);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 60);
    R(6) = R(30) |R(30);
    GM_CALLV(0x81840D2Cu, 0x8015F730u, 0);
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -24432));
    R(5) = (0 + 0x80430000u);
    R(5) = ld32(base, (R(5) + -24428));
    R(4) = ld16(base, (R(3) + 28));
    R(4) = R(4) | 0x1u;
    st16(base, (R(3) + 28), R(4));
    R(4) = (0 + 0x80430000u);
    R(3) = ld16(base, (R(5) + 28));
    R(4) = ld32(base, (R(4) + -23744));
    R(3) = R(3) | 0x1u;
    st16(base, (R(5) + 28), R(3));
    R(3) = (0 + 1);
    st8(base, (R(4) + 258), R(3));
    R(3) = R(29) |R(29);
    GM_CALLV(0x81840D6Cu, 0x8016E4F0u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* preinit (preinit, 36 bytes) */
static void mj_preinit_40f24(GM_CTX) {
    GM_FN(0x81840F24); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x81840F34u, 0x81840BE8u, 0);
    R(3) = (0 + 0);
    R(0) = lr;
}

/* mfn_81840F88 (mfn_81840F88, 72 bytes) */
static void mj_mfn_81840F88_40f88(GM_CTX) {
    GM_FN(0x81840F88); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(7) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 0))) { goto L_81840FC0; }
    R(8) = ld32(base, (R(7) + 12));
    cr_cmp_u(ctx, 0, R(8), R(4));
    if ((!CR_BIT(ctx, 1))) { goto L_81840FC0; }
    R(3) = R(7) |R(7);
    GM_CALLV(0x81840FB8u, 0x8019FC80u, 0);
    { uint32_t a_ = R(3); R(4) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(4) < a_; }
    { uint64_t t_ = (uint64_t)(~R(4)) + (R(3)) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
L_81840FC0:;
    R(0) = lr;
}

/* mfn_81840FD0 (mfn_81840FD0, 52 bytes) */
static void mj_mfn_81840FD0_40fd0(GM_CTX) {
    R(5) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 0))) return;
    R(6) = ld32(base, (R(5) + 12));
    cr_cmp_u(ctx, 0, R(6), R(4));
    if ((!CR_BIT(ctx, 1))) return;
    R(3) = ld32(base, (R(5) + 4));
    R(4) = ((int32_t)R(4) * 12);
    R(3) = ld8(base, (R(3) + R(4)));
    { uint32_t a_ = R(3); R(4) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(4) < a_; }
    { uint64_t t_ = (uint64_t)(~R(4)) + (R(3)) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
}

/* mfn_81841364 (mfn_81841364, 232 bytes) */
static void mj_mfn_81841364_41364(GM_CTX) {
    GM_FN(0x81841364); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(27) = R(3) |R(3);
    R(29) = R(4) |R(4);
    GM_CALLV(0x8184138Cu, 0x801B1140u, 0);
    R(30) = R(3) |R(3);
    R(3) = R(27) |R(27);
    GM_CALLV(0x81841398u, 0x801BB680u, 0);
    R(5) = (0 + 0x80340000u);
    R(4) = rotl32(R(27), 2) & 0xFFFFFFFCu;
    R(5) = (R(5) + -88);
    R(4) = R(5) + R(4);
    R(4) = ld8(base, (R(4) + 3));
    R(28) = R(3) |R(3);
    R(4) = R(4) & 0x80u;
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_818413CC; }
    ctx->ctr = R(29);
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x818413C8u, ctx->ctr, 0);
    goto L_81841420;
L_818413CC:;
    R(4) = (0 + 0x80390000u);
    R(3) = rotl32(R(27), 4) & 0xFFFFFFF0u;
    R(4) = (R(4) + -1616);
    R(3) = R(3) + R(4);
    R(4) = (0 + 4);
    R(3) = (R(3) + -4);
    ctx->ctr = R(4);
L_818413E8:;
    { uint32_t ea_ = R(3) + 4; R(4) = ld32(base, ea_); R(3) = ea_; }
    cr_cmp_u(ctx, 0, R(4), R(29));
    if ((CR_BIT(ctx, 2))) { goto L_81841420; }
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8184141C; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818413E8; }
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 3929);
    R(5) = (R(3) + 25);
    R(6) = (R(3) + 9);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 199);
    GM_CALLV(0x8184141Cu, 0x818380F8u, 0);
L_8184141C:;
    st32(base, (R(3) + 0), R(29));
L_81841420:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81841428u, 0x801B1180u, 0);
    R(3) = R(28) |R(28);
    R(0) = lr;
}

/* mfn_81841460 (mfn_81841460, 132 bytes) */
static void mj_mfn_81841460_41460(GM_CTX) {
    GM_FN(0x81841460); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), -1);
    if ((CR_BIT(ctx, 2))) { goto L_818414B8; }
    R(5) = (0 + 0x81860000u);
    R(5) = ld32(base, (R(5) + -492));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_818414B8; }
    R(5) = (0 + 0x81860000u);
    st32(base, (R(5) + -6416), R(3));
    R(3) = (0 + 0x81860000u);
    st32(base, (R(3) + -492), R(4));
    R(3) = (0 + 0x81850000u);
    R(30) = (R(3) + 4122);
    R(5) = (R(30) + 4);
    R(3) = R(4) |R(4);
    R(4) = R(5) |R(5);
    GM_CALLV(0x818414B0u, 0x8019FEA0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818414CC; }
L_818414B8:;
    R(0) = lr;
    return;
L_818414CC:;
    R(3) = (R(30) + 10);
    R(5) = (R(30) + 33);
    R(6) = (R(30) + 18);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 38);
    GM_CALLV(0x818414E4u, 0x818380F8u, 0);
}

/* mod__Z24DVDConvertPathToEntrynumPKc (mod__Z24DVDConvertPathToEntrynumPKc, 112 bytes) */
static void mj_mod__Z24DVDConvertPathToEntrynumPKc_414e4(GM_CTX) {
    GM_FN(0x818414E4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x81860000u);
    R(5) = ld32(base, (R(4) + -492));
    R(30) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81841538; }
    R(3) = ld8(base, (R(30) + 0));
    R(3) = R(3) ^ 0x2Fu;
    R(3) = cntlzw(R(3));
    R(3) = rotl32(R(3), 27) & 0x7FFFFFFu;
    R(4) = R(30) + R(3);
    R(3) = R(5) |R(5);
    GM_CALLV(0x81841524u, 0x8019FA00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), -1);
    if ((CR_BIT(ctx, 2))) { goto L_81841538; }
    R(3) = (R(3) + 13568);
    R(3) = (R(3) + 0xC0000u);
    goto L_81841540;
L_81841538:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81841540u, 0x81845438u, 0);
L_81841540:;
    R(0) = lr;
}

/* mod__Z11DVDFastOpeniP9DVDHandle (mod__Z11DVDFastOpeniP9DVDHandle, 236 bytes) */
static void mj_mod__Z11DVDFastOpeniP9DVDHandle_41554(GM_CTX) {
    GM_FN(0x81841554); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0xC0000u);
    R(5) = R(5) | 0x3500u;
    R(30) = R(4) |R(4);
    R(4) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(4) + -300));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(5));
    st32(base, (f + 32), R(4));
    if ((CR_BIT(ctx, 0))) { goto L_81841600; }
    R(4) = (0 + 0x81860000u);
    R(6) = ld32(base, (R(4) + -492));
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81841600; }
    R(3) = (R(3) + -13568);
    R(4) = (R(3) + 0xFFF40000u);
    R(5) = (f + 20);
    R(3) = R(6) |R(6);
    GM_CALLV(0x818415ACu, 0x8019F9B0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(29) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_8184160C; }
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -6416));
    R(4) = R(30) |R(30);
    GM_CALLV(0x818415C8u, 0x81845440u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_8184160C; }
    R(29) = (f + 20);
    R(3) = R(29) |R(29);
    GM_CALLV(0x818415DCu, 0x8019FE70u, 0);
    R(4) = ld32(base, (R(30) + 48));
    R(3) = rotl32(R(3), 30) & 0x3FFFFFFFu;
    R(3) = R(4) + R(3);
    st32(base, (R(30) + 48), R(3));
    R(3) = R(29) |R(29);
    GM_CALLV(0x818415F4u, 0x8019FE80u, 0);
    R(29) = (0 + 1);
    st32(base, (R(30) + 52), R(3));
    goto L_8184160C;
L_81841600:;
    R(4) = R(30) |R(30);
    GM_CALLV(0x81841608u, 0x81845440u, 0);
    R(29) = R(3) |R(3);
L_8184160C:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 32));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_8184163C; }
    R(3) = R(29) |R(29);
    R(0) = lr;
    return;
L_8184163C:;
    GM_CALLV(0x81841640u, 0x81844FCCu, 0);
}

/* mfn_81841640 (mfn_81841640, 388 bytes) */
static void mj_mfn_81841640_41640(GM_CTX) {
    GM_FN(0x81841640); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = R(3) |R(3);
    R(3) = (0 + 0xC0000u);
    R(3) = R(3) | 0x3500u;
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(3));
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    if ((CR_BIT(ctx, 0))) { goto L_818416B0; }
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -492));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818416B0; }
    R(4) = (R(28) + -13568);
    R(4) = (R(4) + 0xFFF40000u);
    R(5) = R(29) |R(29);
    R(6) = R(30) |R(30);
    GM_CALLV(0x818416ACu, 0x81840F88u, 0);
    goto L_81841794;
L_818416B0:;
    R(3) = (0 + 0x81850000u);
    R(26) = (0 + 0);
    R(23) = (0 + 1);
    R(25) = (0 + 0x80430000u);
    R(24) = (0 + 0x80430000u);
    R(27) = (R(3) + 4122);
L_818416C8:;
    R(3) = ld32(base, (R(25) + -22264));
    cr_cmp_u(ctx, 0, R(23), R(28));
    if ((CR_BIT(ctx, 2))) { goto L_81841744; }
L_818416D4:;
    R(4) = ((int32_t)R(23) * 12);
    R(5) = R(3) |R(3);
    { uint32_t ea_ = R(5) + R(4); R(4) = ld32(base, ea_); R(5) = ea_; }
    R(6) = R(4) & 0xFF000000u;
    CR0(ctx, R(6));
    if ((!CR_BIT(ctx, 2))) { goto L_818416F4; }
    R(5) = (R(23) + 1);
    cr_cmp_u(ctx, 0, R(5), R(28));
    goto L_81841700;
L_818416F4:;
    R(5) = ld32(base, (R(5) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(5), (int32_t)R(28));
    if ((CR_BIT(ctx, 1))) { goto L_8184170C; }
L_81841700:;
    R(23) = R(5) |R(5);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818416D4; }
    goto L_81841744;
L_8184170C:;
    R(5) = ld32(base, (R(24) + -22268));
    R(4) = R(4) & 0xFFFFFFu;
    R(3) = R(29) + R(26);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(6) = R(5) + R(4);
    R(4) = R(30) - R(26);
    R(5) = R(27) |R(27);
    GM_CALLV(0x8184172Cu, 0x802E16E8u, 0);
    R(26) = R(3) + R(26);
    R(23) = (R(23) + 1);
    cr_cmp_u(ctx, 0, R(26), R(30));
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818416C8; }
    goto L_81841794;
L_81841744:;
    R(4) = ((int32_t)R(28) * 12);
    R(3) = ld32(base, (R(3) + R(4)));
    R(4) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(4) + -22268));
    R(5) = R(3) & 0xFFFFFFu;
    R(3) = R(3) & 0xFF000000u;
    CR0(ctx, R(3));
    R(3) = (0 + 0x81850000u);
    R(6) = R(4) + R(5);
    R(5) = (R(3) + 4122);
    if ((!CR_BIT(ctx, 2))) { goto L_81841770; }
    R(5) = (R(5) + 7);
L_81841770:;
    R(3) = R(29) + R(26);
    R(4) = R(30) - R(26);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x81841780u, 0x802E16E8u, 0);
    R(3) = R(3) + R(26);
    cr_cmp_u(ctx, 0, R(3), R(30));
    R(3) = (0 + 1);
    if ((CR_BIT(ctx, 0))) { goto L_81841794; }
    R(3) = (0 + 0);
L_81841794:;
    R(0) = lr;
}

/* mfn_818417C4 (mfn_818417C4, 104 bytes) */
static void mj_mfn_818417C4_417c4(GM_CTX) {
    GM_FN(0x818417C4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0xC0000u);
    R(4) = R(4) | 0x3500u;
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(4));
    if ((CR_BIT(ctx, 0))) { goto L_81841804; }
    R(4) = (0 + 0x81860000u);
    R(5) = ld32(base, (R(4) + -492));
    cr_cmp_u(ctx, 0, R(5), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81841804; }
    R(3) = (R(3) + -13568);
    R(4) = (R(3) + 0xFFF40000u);
    R(3) = R(5) |R(5);
    GM_CALLV(0x81841800u, 0x81840FD0u, 0);
    goto L_8184181C;
L_81841804:;
    R(4) = (0 + 0x80430000u);
    R(4) = ld32(base, (R(4) + -22264));
    R(3) = ((int32_t)R(3) * 12);
    R(3) = ld8(base, (R(4) + R(3)));
    { uint32_t a_ = R(3); R(4) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(4) < a_; }
    { uint64_t t_ = (uint64_t)(~R(4)) + (R(3)) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
L_8184181C:;
    R(0) = lr;
}

/* mfn_8184182C (mfn_8184182C, 12 bytes) */
static void mj_mfn_8184182C_4182c(GM_CTX) {
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -492));
}

/* mfn_81841838 (mfn_81841838, 12 bytes) */
static void mj_mfn_81841838_41838(GM_CTX) {
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -6416));
}

/* mfn_81841D6C (mfn_81841D6C, 168 bytes) */
static void mj_mfn_81841D6C_41d6c(GM_CTX) {
    GM_FN(0x81841D6C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(3) + -476));
    R(5) = (0 + 0x81860000u);
    R(3) = cntlzw(R(4));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    st32(base, (R(5) + -6408), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81841DE4; }
    R(5) = R(4) & 0xF0000000u;
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81841DF4; }
    R(5) = (0 + 0x80000000u);
    { uint32_t s_ = R(3) & 63; R(5) = s_ > 31 ? 0 : R(5) >> s_; }
    R(4) = R(4) & ~R(5);
    R(5) = (0 + 0x81860000u);
    st32(base, (R(5) + -476), R(4));
    R(5) = (0 + 0x81860000u);
    R(4) = ((int32_t)R(3) * 12);
    R(5) = (R(5) + -436);
    R(4) = R(4) + R(5);
    R(5) = (0 + 12);
    R(4) = (R(4) + -1);
    ctx->ctr = R(5);
    R(5) = (0 + 0);
L_81841DD0:;
    { uint32_t ea_ = R(4) + 1; st8(base, ea_, R(5)); R(4) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81841DD0; }
    R(4) = (0 + 0x81840000u);
    R(4) = (R(4) + 7700);
    GM_CALLV(0x81841DE4u, 0x81841364u, 0);
L_81841DE4:;
    R(0) = lr;
    return;
L_81841DF4:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 4176);
    R(3) = (R(4) + 128);
    R(5) = (R(4) + 134);
    R(6) = (R(4) + 154);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 125);
    GM_CALLV(0x81841E14u, 0x818380F8u, 0);
}

/* mfn_81841E14 (mfn_81841E14, 472 bytes) */
static void mj_mfn_81841E14_41e14(GM_CTX) {
    GM_FN(0x81841E14); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x81860000u);
    R(5) = ld32(base, (R(5) + -6408));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 4);
    if ((!CR_BIT(ctx, 0))) { goto L_81841F8C; }
    cr_cmp_u(ctx, 0, R(5), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81841FAC; }
    R(5) = R(4) & 0x80u;
    CR0(ctx, R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_81841FCC; }
    R(5) = (0 + 0x81860000u);
    R(6) = ld32(base, (R(5) + -472));
    R(7) = (0 + 0x80000000u);
    { uint32_t s_ = R(3) & 63; R(30) = s_ > 31 ? 0 : R(7) >> s_; }
    R(7) = R(4) & 0xFu;
    CR0(ctx, R(7));
    R(7) = R(6) & ~R(30);
    st32(base, (R(5) + -472), R(7));
    if ((!CR_BIT(ctx, 2))) { goto L_81841F74; }
    R(8) = R(4) & 0x19000000u;
    CR0(ctx, R(8));
    R(8) = R(8) ^ 0x9000000u;
    cr_cmp_u(ctx, 0, R(8), 0x0u);
    R(8) = (0 + 0x81860000u);
    R(7) = R(4) & 0xFFFFFF00u;
    R(5) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(8) = (R(8) + -452);
    st32(base, (R(8) + R(5)), R(7));
    if ((!CR_BIT(ctx, 2))) { goto L_81841F74; }
    R(7) = (0 + 0x81860000u);
    R(7) = ld32(base, (R(7) + -6400));
    cr_cmp_u(ctx, 0, R(7), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_81841EA0; }
    GM_CALLV(0x81841E9Cu, 0x81841C20u, 0);
    goto L_81841F74;
L_81841EA0:;
    R(7) = R(4) & 0x84000000u;
    CR0(ctx, R(7));
    R(7) = R(7) ^ 0x80000000u;
    cr_cmp_u(ctx, 0, R(7), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81841EF8; }
    R(6) = R(4) & 0x1C0000u;
    R(6) = R(6) ^ 0x100000u;
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81841F78; }
    R(4) = R(4) & 0x40000000u;
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81841F28; }
    R(4) = (0 + 0x81860000u);
    R(4) = (R(4) + -384);
    R(4) = R(4) + R(5);
    R(5) = (0 + 0x81860000u);
    R(6) = ((int32_t)R(3) * 12);
    R(5) = (R(5) + -436);
    R(6) = R(5) + R(6);
    R(5) = (0 + 0x81840000u);
    R(8) = (R(5) + 8728);
    R(5) = (0 + 3);
    R(7) = (0 + 8);
    goto L_81841F50;
L_81841EF8:;
    R(4) = R(6) &R(30);
    CR0(ctx, R(4));
    R(5) = (0 + 0x81860000u);
    R(4) = ((int32_t)R(3) * 12);
    R(5) = (R(5) + -436);
    R(6) = R(5) + R(4);
    if ((CR_BIT(ctx, 2))) { goto L_81841F38; }
    R(4) = (0 + 0x81860000u);
    R(5) = (0 + 0x81840000u);
    R(4) = (R(4) + -6388);
    R(8) = (R(5) + 8440);
    R(5) = (0 + 3);
    goto L_81841F4C;
L_81841F28:;
    R(5) = (0 + 0x81860000u);
    R(4) = ((int32_t)R(3) * 12);
    R(5) = (R(5) + -436);
    R(6) = R(5) + R(4);
L_81841F38:;
    R(4) = (0 + 0x81860000u);
    R(5) = (0 + 0x81840000u);
    R(4) = (R(4) + -6392);
    R(8) = (R(5) + 8440);
    R(5) = (0 + 1);
L_81841F4C:;
    R(7) = (0 + 10);
L_81841F50:;
    R(9) = (0 + 0);
    R(10) = (0 + 0);
    GM_CALLV(0x81841F5Cu, 0x801BB250u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81841F78; }
    R(3) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(3) + -460));
    R(4) = R(4) |R(30);
    st32(base, (R(3) + -460), R(4));
L_81841F74:;
    GM_CALLV(0x81841F78u, 0x81841D6Cu, 0);
L_81841F78:;
    R(0) = lr;
    return;
L_81841F8C:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 4176);
    R(3) = (R(4) + 128);
    R(5) = (R(4) + 134);
    R(6) = (R(4) + 154);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 240);
    GM_CALLV(0x81841FACu, 0x818380F8u, 0);
L_81841FAC:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 4176);
    R(3) = (R(4) + 128);
    R(5) = (R(4) + 134);
    R(6) = (R(4) + 204);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 241);
    GM_CALLV(0x81841FCCu, 0x818380F8u, 0);
L_81841FCC:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 4176);
    R(3) = (R(4) + 128);
    R(5) = (R(4) + 134);
    R(6) = (R(4) + 264);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 245);
    GM_CALLV(0x81841FECu, 0x818380F8u, 0);
}

/* mfn_818423A0 (mfn_818423A0, 256 bytes) */
static void mj_mfn_818423A0_423a0(GM_CTX) {
    GM_FN(0x818423A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = R(3) & 0xFFFFFFFu;
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81842484; }
    GM_CALLV(0x818423C4u, 0x801B1140u, 0);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(5) = (0 + 0);
    R(4) = ld32(base, (R(3) + -460));
    R(6) = (0 + 0x81860000u);
    st32(base, (R(3) + -460), R(5));
    R(3) = (0 + 0x81860000u);
    R(5) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -468));
    R(4) = R(4) |R(29);
    R(5) = ld32(base, (R(5) + -464));
    R(8) = (0 + 0x81860000u);
    R(7) = ld32(base, (R(6) + -480));
    R(3) = R(5) |R(3);
    R(8) = ld32(base, (R(8) + -6400));
    R(4) = R(4) & ~R(3);
    R(3) = R(7) & ~R(4);
    st32(base, (R(6) + -480), R(3));
    R(3) = (0 + 0x81860000u);
    R(5) = ld32(base, (R(3) + -476));
    R(6) = (0 + 0x81860000u);
    cr_cmp_u(ctx, 0, R(8), 0x4u);
    R(8) = ld32(base, (R(6) + -456));
    R(5) = R(4) |R(5);
    st32(base, (R(3) + -476), R(5));
    R(3) = R(5) &R(7);
    R(5) = R(8) & ~R(4);
    st32(base, (R(6) + -456), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_81842448; }
    R(5) = (0 + 0x81860000u);
    R(6) = ld32(base, (R(5) + -472));
    R(4) = R(6) |R(4);
    st32(base, (R(5) + -472), R(4));
L_81842448:;
    GM_CALLV(0x8184244Cu, 0x818411D8u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -6408));
    cr_cmp_u(ctx, 0, R(3), 0x20u);
    if ((!CR_BIT(ctx, 2))) { goto L_81842460; }
    GM_CALLV(0x81842460u, 0x81841D6Cu, 0);
L_81842460:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81842468u, 0x801B1180u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
    return;
L_81842484:;
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 4176);
    R(3) = (R(4) + 128);
    R(5) = (R(4) + 226);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 334);
    GM_CALLV(0x818424A0u, 0x818380F8u, 0);
}

/* mfn_818425A0 (mfn_818425A0, 244 bytes) */
static void mj_mfn_818425A0_425a0(GM_CTX) {
    GM_FN(0x818425A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x81860000u);
    R(3) = ld8(base, (R(3) + -484));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_8184267C; }
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -6412));
    GM_CALLV(0x818425CCu, 0x801AB1C0u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -388));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818425E0; }
    GM_CALLV(0x818425E0u, 0x81842694u, 0);
L_818425E0:;
    R(3) = (0 + 0x80430000u);
    R(3) = ld32(base, (R(3) + -22612));
    R(4) = (0 + 0x80000000u);
    R(5) = (0 + 0x81860000u);
    R(30) = R(4) | 0x30E0u;
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 1);
    st8(base, (R(5) + -484), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81842634; }
    GM_CALLV(0x81842608u, 0x801B5F80u, 0);
    R(6) = rotl32(R(4), 16) & 0xFFFFu;
    R(4) = R(6) + R(4);
    R(6) = rotl32(R(3), 16) & 0xFFFFu;
    R(3) = R(4) + R(3);
    R(3) = R(3) + R(6);
    R(5) = (0 + 0x81860000u);
    R(3) = R(3) & 0x3FFFu;
    R(4) = (0 + 0xF0000000u);
    st16(base, (R(30) + 0), R(3));
    st32(base, (R(5) + -472), R(4));
    goto L_8184263C;
L_81842634:;
    R(3) = ld16(base, (R(30) + 0));
    R(3) = R(3) & 0x3FFFu;
L_8184263C:;
    R(4) = (0 + 4);
    ctx->ctr = R(4);
    R(4) = (0 + 0x81860000u);
    R(3) = rotl32(R(3), 8) & 0xFFFFFF00u;
    R(4) = (R(4) + -384);
    R(3) = R(3) | 0x4D000000u;
    R(4) = (R(4) + -4);
L_81842658:;
    { uint32_t ea_ = R(4) + 4; st32(base, ea_, R(3)); R(4) = ea_; }
    R(3) = (R(3) + 0x400000u);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842658; }
    GM_CALLV(0x81842668u, 0x801BB920u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = (R(3) + -6384);
    GM_CALLV(0x81842674u, 0x801B32D0u, 0);
    R(3) = (0 + 0xF0000000u);
    GM_CALLV(0x8184267Cu, 0x818423A0u, 0);
L_8184267C:;
    R(3) = (0 + 1);
    R(0) = lr;
}

/* mfn_81842714 (mfn_81842714, 1320 bytes) */
static void mj_mfn_81842714_42714(GM_CTX) {
    GM_FN(0x81842714); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    st32(base, (f + 52), R(3));
    GM_CALLV(0x8184277Cu, 0x801B1140u, 0);
    R(4) = (f + 44);
    st32(base, (f + 40), R(3));
    R(3) = (0 + 0x81860000u);
    st32(base, (f + 36), R(4));
    R(4) = (0 + 0x81860000u);
    R(5) = (0 + 0x81860000u);
    R(23) = (R(3) + -368);
    R(3) = (R(4) + -452);
    R(6) = (0 + 0x81860000u);
    st32(base, (f + 32), R(3));
    R(3) = (R(5) + -436);
    R(7) = (0 + 0x81840000u);
    st32(base, (f + 24), R(3));
    R(3) = (R(6) + -6392);
    R(8) = (0 + 0x81840000u);
    st32(base, (f + 20), R(3));
    R(3) = (R(7) + 8584);
    R(21) = (0 + 0);
    R(20) = (0 + 0x80000000u);
    R(19) = (0 + 0x81860000u);
    R(18) = (0 + 0x81860000u);
    R(17) = (0 + 0x81860000u);
    R(16) = (0 + 254);
    R(15) = (0 + 10);
    R(14) = (0 + 0x81860000u);
    R(27) = (0 + 0);
    R(26) = R(30) |R(30);
    st32(base, (f + 16), R(3));
    R(3) = (R(8) + 8952);
    R(24) = R(23) |R(23);
    R(22) = (0 + 0);
    st32(base, (f + 28), R(3));
L_818427FC:;
    R(3) = ld32(base, (R(19) + -460));
    R(25) = ((int32_t)R(22) * 12);
    { uint32_t s_ = R(22) & 63; R(28) = s_ > 31 ? 0 : R(20) >> s_; }
    R(29) = (R(25) + -1);
    R(3) = R(3) &R(28);
    CR0(ctx, R(3));
    R(31) = R(30) + R(29);
    if ((CR_BIT(ctx, 2))) { goto L_81842834; }
    R(3) = (0 + 0);
    GM_CALLV(0x81842820u, 0x818423A0u, 0);
    st8(base, (R(26) + 10), R(16));
    ctx->ctr = R(15);
L_81842828:;
    { uint32_t ea_ = R(31) + 1; st8(base, ea_, R(21)); R(31) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842828; }
    goto L_818428A8;
L_81842834:;
    R(3) = ld32(base, (R(18) + -476));
    R(3) = R(3) &R(28);
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81842880; }
    R(3) = ld32(base, (R(17) + -6408));
    cr_cmp_u(ctx, 0, R(3), R(22));
    if ((CR_BIT(ctx, 2))) { goto L_81842880; }
    R(3) = ld32(base, (R(14) + -480));
    R(3) = R(3) &R(28);
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81842894; }
    R(3) = R(22) |R(22);
    GM_CALLV(0x81842860u, 0x81841020u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818428C0; }
    R(3) = (0 + 253);
    st8(base, (R(26) + 10), R(3));
    ctx->ctr = R(15);
L_81842874:;
    { uint32_t ea_ = R(31) + 1; st8(base, ea_, R(21)); R(31) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842874; }
    goto L_818428A8;
L_81842880:;
    st8(base, (R(26) + 10), R(16));
    ctx->ctr = R(15);
L_81842888:;
    { uint32_t ea_ = R(31) + 1; st8(base, ea_, R(21)); R(31) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842888; }
    goto L_818428A8;
L_81842894:;
    R(3) = (0 + 255);
    st8(base, (R(26) + 10), R(3));
    ctx->ctr = R(15);
L_818428A0:;
    { uint32_t ea_ = R(31) + 1; st8(base, ea_, R(21)); R(31) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818428A0; }
L_818428A8:;
    R(22) = (R(22) + 1);
    R(26) = (R(26) + 12);
    cr_cmp_u(ctx, 0, R(22), 0x4u);
    R(24) = (R(24) + 12);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818427FC; }
    goto L_81842BC0;
L_818428C0:;
    R(3) = R(22) |R(22);
    GM_CALLV(0x818428C8u, 0x8184105Cu, 0);
    R(3) = R(3) & 0x8u;
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81842ADC; }
    R(3) = R(22) |R(22);
    GM_CALLV(0x818428D8u, 0x801BB680u, 0);
    R(3) = R(3) & 0x20000000u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_818428E4; }
    R(28) = (0 + 0);
L_818428E4:;
    R(4) = ld32(base, (f + 36));
    R(3) = R(22) |R(22);
    R(27) = R(28) |R(27);
    GM_CALLV(0x818428F4u, 0x81841264u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81842B30; }
    R(3) = ld32(base, (f + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_81842B68; }
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -6396));
    R(4) = R(26) |R(26);
    R(5) = ld32(base, (f + 36));
    ctx->ctr = R(3);
    R(3) = R(22) |R(22);
    GM_CALLV(0x81842924u, ctx->ctr, 0);
    R(4) = ld32(base, (f + 32));
    R(3) = rotl32(R(22), 2) & 0xFFFFFFFCu;
    R(3) = ld16(base, (R(4) + R(3)));
    cr_cmp_u(ctx, 0, R(3), 0x900u);
    if ((!CR_BIT(ctx, 2))) { goto L_81842948; }
    R(3) = ld8(base, (R(26) + 1));
    R(3) = R(3) & 0x80u;
    CR0(ctx, R(3));
    R(3) = (0 + 10);
    if ((CR_BIT(ctx, 2))) { goto L_8184294C; }
L_81842948:;
    R(3) = (0 + 3);
L_8184294C:;
    R(5) = ld8(base, (R(26) + 2));
    R(4) = R(23) + R(25);
    R(6) = ld8(base, (R(4) + 2));
    R(5) = (int8_t)R(5);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(7) = (v_ >> 31); }
    R(6) = (int8_t)R(6);
    R(5) = R(5) ^R(7);
    R(5) = R(5) - R(7);
    { int32_t v_ = (int32_t)R(6); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(7) = (v_ >> 31); }
    R(6) = R(6) ^R(7);
    R(6) = R(7) - R(6);
    R(5) = R(5) + R(6);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(6) = (v_ >> 31); }
    R(5) = R(5) ^R(6);
    R(5) = R(5) - R(6);
    cr_cmp_u(ctx, 0, R(5), R(3));
    if ((!CR_BIT(ctx, 0))) { goto L_81842AA0; }
    R(5) = ld8(base, (R(26) + 3));
    R(6) = ld8(base, (R(4) + 3));
    R(5) = (int8_t)R(5);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(7) = (v_ >> 31); }
    R(6) = (int8_t)R(6);
    R(5) = R(5) ^R(7);
    R(5) = R(5) - R(7);
    { int32_t v_ = (int32_t)R(6); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(7) = (v_ >> 31); }
    R(6) = R(6) ^R(7);
    R(6) = R(7) - R(6);
    R(5) = R(5) + R(6);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(6) = (v_ >> 31); }
    R(5) = R(5) ^R(6);
    R(5) = R(5) - R(6);
    cr_cmp_u(ctx, 0, R(5), R(3));
    if ((!CR_BIT(ctx, 0))) { goto L_81842AA0; }
    R(5) = ld8(base, (R(26) + 4));
    R(6) = ld8(base, (R(4) + 4));
    R(5) = (int8_t)R(5);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(7) = (v_ >> 31); }
    R(6) = (int8_t)R(6);
    R(5) = R(5) ^R(7);
    R(5) = R(5) - R(7);
    { int32_t v_ = (int32_t)R(6); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(7) = (v_ >> 31); }
    R(6) = R(6) ^R(7);
    R(6) = R(7) - R(6);
    R(5) = R(5) + R(6);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(6) = (v_ >> 31); }
    R(5) = R(5) ^R(6);
    R(5) = R(5) - R(6);
    cr_cmp_u(ctx, 0, R(5), R(3));
    if ((!CR_BIT(ctx, 0))) { goto L_81842AA0; }
    R(5) = ld8(base, (R(26) + 5));
    R(6) = ld8(base, (R(4) + 5));
    R(5) = (int8_t)R(5);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(7) = (v_ >> 31); }
    R(6) = (int8_t)R(6);
    R(5) = R(5) ^R(7);
    R(5) = R(5) - R(7);
    { int32_t v_ = (int32_t)R(6); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(7) = (v_ >> 31); }
    R(6) = R(6) ^R(7);
    R(6) = R(7) - R(6);
    R(5) = R(5) + R(6);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(6) = (v_ >> 31); }
    R(5) = R(5) ^R(6);
    R(5) = R(5) - R(6);
    cr_cmp_u(ctx, 0, R(5), R(3));
    if ((!CR_BIT(ctx, 0))) { goto L_81842AA0; }
    R(5) = ld8(base, (R(26) + 6));
    R(6) = ld8(base, (R(4) + 6));
    R(5) = R(5) - R(6);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(6) = (v_ >> 31); }
    R(5) = R(5) ^R(6);
    R(5) = R(5) - R(6);
    cr_cmp_u(ctx, 0, R(5), R(3));
    if ((!CR_BIT(ctx, 0))) { goto L_81842AA0; }
    R(5) = ld8(base, (R(26) + 7));
    R(6) = ld8(base, (R(4) + 7));
    R(5) = R(5) - R(6);
    { int32_t v_ = (int32_t)R(5); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(6) = (v_ >> 31); }
    R(5) = R(5) ^R(6);
    R(5) = R(5) - R(6);
    cr_cmp_u(ctx, 0, R(5), R(3));
    if ((!CR_BIT(ctx, 0))) { goto L_81842AA0; }
    R(3) = ld16(base, (R(4) + 0));
    R(4) = ld16(base, (R(26) + 0));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81842AA4; }
L_81842AA0:;
    GM_CALLV(0x81842AA4u, 0x8184144Cu, 0);
L_81842AA4:;
    R(4) = (0 + 12);
    R(3) = R(23) + R(29);
    ctx->ctr = R(4);
    R(4) = R(31) |R(31);
L_81842AB4:;
    { uint32_t ea_ = R(4) + 1; R(5) = ld8(base, ea_); R(4) = ea_; }
    { uint32_t ea_ = R(3) + 1; st8(base, ea_, R(5)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842AB4; }
    R(3) = ld16(base, (R(26) + 0));
    R(4) = R(3) & 0x2000u;
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81842B80; }
    R(3) = R(3) & 0xDF7Fu;
    CR0(ctx, R(3));
    st8(base, (R(26) + 10), R(21));
    st16(base, (R(26) + 0), R(3));
    GM_LOOP(); goto L_818428A8;
L_81842ADC:;
    R(4) = (f + 44);
    R(3) = R(22) |R(22);
    GM_CALLV(0x81842AE8u, 0x81841264u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -468));
    R(3) = R(3) &R(28);
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81842B48; }
    st8(base, (R(26) + 10), R(21));
    ctx->ctr = R(15);
L_81842B00:;
    { uint32_t ea_ = R(31) + 1; st8(base, ea_, R(21)); R(31) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842B00; }
    R(5) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(5) + -464));
    R(4) = R(3) &R(28);
    CR0(ctx, R(4));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818428A8; }
    R(4) = ld32(base, (f + 28));
    R(3) = R(3) |R(28);
    st32(base, (R(5) + -464), R(3));
    R(3) = R(22) |R(22);
    GM_CALLV(0x81842B2Cu, 0x81841364u, 0);
    GM_LOOP(); goto L_818428A8;
L_81842B30:;
    R(3) = (0 + 253);
    st8(base, (R(26) + 10), R(3));
    ctx->ctr = R(15);
L_81842B3C:;
    { uint32_t ea_ = R(31) + 1; st8(base, ea_, R(21)); R(31) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842B3C; }
    GM_LOOP(); goto L_818428A8;
L_81842B48:;
    R(3) = R(22) |R(22);
    GM_CALLV(0x81842B50u, 0x81841CB8u, 0);
    R(3) = (0 + 255);
    st8(base, (R(26) + 10), R(3));
    ctx->ctr = R(15);
L_81842B5C:;
    { uint32_t ea_ = R(31) + 1; st8(base, ea_, R(21)); R(31) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842B5C; }
    GM_LOOP(); goto L_818428A8;
L_81842B68:;
    R(3) = (0 + 253);
    st8(base, (R(26) + 10), R(3));
    ctx->ctr = R(15);
L_81842B74:;
    { uint32_t ea_ = R(31) + 1; st8(base, ea_, R(21)); R(31) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842B74; }
    GM_LOOP(); goto L_818428A8;
L_81842B80:;
    R(3) = (0 + 253);
    st8(base, (R(26) + 10), R(3));
    ctx->ctr = R(15);
L_81842B8C:;
    { uint32_t ea_ = R(31) + 1; st8(base, ea_, R(21)); R(31) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81842B8C; }
    R(3) = ld32(base, (f + 24));
    R(5) = (0 + 1);
    R(4) = ld32(base, (f + 20));
    R(7) = (0 + 10);
    R(8) = ld32(base, (f + 16));
    R(6) = R(3) + R(25);
    R(3) = R(22) |R(22);
    R(9) = (0 + 0);
    R(10) = (0 + 0);
    GM_CALLV(0x81842BBCu, 0x801BB250u, 0);
    GM_LOOP(); goto L_818428A8;
L_81842BC0:;
    R(3) = ld32(base, (f + 40));
    GM_CALLV(0x81842BC8u, 0x801B1180u, 0);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 52));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81842C38; }
    R(3) = R(27) |R(27);
    R(0) = lr;
    return;
L_81842C38:;
    GM_CALLV(0x81842C3Cu, 0x81844FCCu, 0);
}

/* mfn_81842F7C (mfn_81842F7C, 164 bytes) */
static void mj_mfn_81842F7C_42f7c(GM_CTX) {
    GM_FN(0x81842F7C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = (R(3) + -2);
    R(29) = (0 + 4);
    R(30) = (R(3) + 5);
L_81842FA0:;
    { uint32_t ea_ = R(28) + 12; R(3) = ld8(base, ea_); R(28) = ea_; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81842FF4; }
    R(3) = (R(30) + -3);
    R(4) = (R(30) + -2);
    GM_CALLV(0x81842FB8u, 0x81842EACu, 0);
    R(3) = (R(30) + -1);
    R(4) = R(30) |R(30);
    GM_CALLV(0x81842FC4u, 0x81842EACu, 0);
    R(5) = ld8(base, (R(28) + -4));
    R(3) = (0 + 0);
    R(4) = (0 + 0);
    cr_cmp_u(ctx, 0, R(5), 0xBu);
    if ((CR_BIT(ctx, 0))) { goto L_81842FDC; }
    R(4) = (R(5) + -10);
L_81842FDC:;
    R(5) = ld8(base, (R(28) + -3));
    st8(base, (R(28) + -4), R(4));
    cr_cmp_u(ctx, 0, R(5), 0xBu);
    if ((CR_BIT(ctx, 0))) { goto L_81842FF0; }
    R(3) = (R(5) + -10);
L_81842FF0:;
    st8(base, (R(28) + -3), R(3));
L_81842FF4:;
    R(29) = (R(29) + -1);
    cr_cmp_u(ctx, 0, R(29), 0x0u);
    R(30) = (R(30) + 12);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_81842FA0; }
    R(0) = lr;
}

/* mfn_81843020 (mfn_81843020, 24 bytes) */
static void mj_mfn_81843020_43020(GM_CTX) {
    R(5) = (0 + 0x81860000u);
    st32(base, (R(5) + -316), R(3));
    R(5) = (0 + 0x81860000u);
    R(3) = (0 + 1000);
    st32(base, (R(5) + -312), R(4));
}

/* mod_fn_802695E0 (mod_fn_802695E0, 28 bytes) */
static void mj_mod_fn_802695E0_43038(GM_CTX) {
    cr_cmp_u(ctx, 0, R(4), 0x3E8u);
    if ((CR_BIT(ctx, 2))) { goto L_81843048; }
    R(3) = (0 + 0);
    return;
L_81843048:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -312));
}

/* mod_fn_802695F0 (mod_fn_802695F0, 28 bytes) */
static void mj_mod_fn_802695F0_43054(GM_CTX) {
    cr_cmp_u(ctx, 0, R(4), 0x3E8u);
    if ((CR_BIT(ctx, 2))) { goto L_81843064; }
    R(3) = (0 + 0);
    return;
L_81843064:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -316));
}

/* mfn_81843070 (mfn_81843070, 172 bytes) */
static void mj_mfn_81843070_43070(GM_CTX) {
    R(4) = (R(3) + -5010);
    cr_cmp_u(ctx, 0, R(4), 0x45u);
    if ((CR_BIT(ctx, 1))) { goto L_818430A8; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 5065);
    if ((CR_BIT(ctx, 1))) { goto L_818430B4; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 5036);
    if ((!CR_BIT(ctx, 0))) { goto L_818430D4; }
    cr_cmp_u(ctx, 0, R(3), 0x139Du);
    R(4) = (0 + 951);
    if ((CR_BIT(ctx, 2))) { goto L_818430AC; }
    cr_cmp_u(ctx, 0, R(3), 0x13A5u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843114; }
    R(4) = (0 + 959);
    goto L_818430AC;
L_818430A8:;
    R(4) = R(3) |R(3);
L_818430AC:;
    R(3) = R(4) |R(4);
    return;
L_818430B4:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 5075);
    if ((!CR_BIT(ctx, 0))) { goto L_818430E8; }
    cr_cmp_u(ctx, 0, R(3), 0x13CAu);
    if ((CR_BIT(ctx, 2))) { goto L_818430FC; }
    cr_cmp_u(ctx, 0, R(3), 0x13D1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843114; }
    R(4) = (0 + 1003);
    GM_LOOP(); goto L_818430AC;
L_818430D4:;
    if ((CR_BIT(ctx, 2))) { goto L_81843104; }
    cr_cmp_u(ctx, 0, R(3), 0x13C4u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843114; }
    R(4) = (0 + 990);
    GM_LOOP(); goto L_818430AC;
L_818430E8:;
    if ((CR_BIT(ctx, 2))) { goto L_8184310C; }
    cr_cmp_u(ctx, 0, R(3), 0x13D7u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843114; }
    R(4) = (0 + 1009);
    GM_LOOP(); goto L_818430AC;
L_818430FC:;
    R(4) = (0 + 854);
    GM_LOOP(); goto L_818430AC;
L_81843104:;
    R(4) = (0 + 1048);
    GM_LOOP(); goto L_818430AC;
L_8184310C:;
    R(4) = (0 + 1005);
    GM_LOOP(); goto L_818430AC;
L_81843114:;
    R(4) = (R(3) + -4000);
    GM_LOOP(); goto L_818430AC;
}

/* mod_fn_80275EE0 (mod_fn_80275EE0, 60 bytes) */
static void mj_mod_fn_80275EE0_4311c(GM_CTX) {
    GM_FN(0x8184311C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x81843138u, 0x81843070u, 0);
    R(4) = R(3) |R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x81843144u, 0x81845448u, 0);
    R(0) = lr;
}

/* mod_fn_80275FD0 (mod_fn_80275FD0, 76 bytes) */
static void mj_mod_fn_80275FD0_43158(GM_CTX) {
    GM_FN(0x81843158); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = R(4) |R(4);
    R(30) = R(5) |R(5);
    GM_CALLV(0x8184317Cu, 0x81843070u, 0);
    R(4) = R(3) |R(3);
    R(3) = R(29) |R(29);
    R(5) = R(30) |R(30);
    GM_CALLV(0x8184318Cu, 0x81845450u, 0);
    R(0) = lr;
}

/* mod_fn_80276210 (mod_fn_80276210, 116 bytes) */
static void mj_mod_fn_80276210_431a4(GM_CTX) {
    GM_FN(0x818431A4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = R(3) |R(3);
    R(3) = R(4) |R(4);
    R(29) = R(4) |R(4);
    R(30) = R(5) |R(5);
    GM_CALLV(0x818431D0u, 0x81843070u, 0);
    R(4) = R(3) |R(3);
    R(3) = R(28) |R(28);
    R(5) = R(30) |R(30);
    GM_CALLV(0x818431E0u, 0x81845458u, 0);
    R(4) = (R(29) + -5010);
    cr_cmp_u(ctx, 0, R(4), 0x45u);
    if ((CR_BIT(ctx, 1))) { goto L_818431FC; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818431FC; }
    R(4) = (0 + 1000);
    st32(base, (R(30) + 4), R(4));
L_818431FC:;
    R(0) = lr;
}

/* mod_fn_802764F0 (mod_fn_802764F0, 84 bytes) */
static void mj_mod_fn_802764F0_43218(GM_CTX) {
    GM_FN(0x81843218); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_u(ctx, 0, R(4), 0x3E8u);
    R(30) = R(5) |R(5);
    R(5) = (0 + 1000);
    if ((CR_BIT(ctx, 2))) { goto L_81843248; }
    GM_CALLV(0x8184323Cu, 0x8184326Cu, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843264; }
    R(5) = ld32(base, (R(3) + 4));
L_81843248:;
    R(3) = (0 + 1);
    st32(base, (R(30) + 0), R(5));
L_81843250:;
    R(0) = lr;
    return;
L_81843264:;
    R(3) = (0 + 0);
    GM_LOOP(); goto L_81843250;
}

/* mfn_8184326C (mfn_8184326C, 120 bytes) */
static void mj_mfn_8184326C_4326c(GM_CTX) {
    GM_FN(0x8184326C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = ld32(base, (R(3) + 40));
    R(29) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = ld8(base, (R(5) + 8));
    R(4) = ld32(base, (R(5) + 12));
    GM_CALLV(0x81843298u, 0x80283A60u, 0);
    R(4) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    R(3) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_818432CC; }
    R(5) = ld32(base, (R(4) + 0));
    cr_cmp_u(ctx, 0, R(5), R(29));
    if ((!CR_BIT(ctx, 1))) { goto L_818432CC; }
    R(3) = rotl32(R(29), 3) & 0xFFFFFFF8u;
    R(4) = R(4) + R(3);
    R(5) = ld32(base, (R(30) + 40));
    R(3) = ld8(base, (R(4) + 4));
    R(4) = ld32(base, (R(4) + 8));
    GM_CALLV(0x818432CCu, 0x80283A60u, 0);
L_818432CC:;
    R(0) = lr;
}

/* mod___nw__FUlPQ23EGG4Heapi (mod___nw__FUlPQ23EGG4Heapi, 80 bytes) */
static void mj_mod___nw__FUlPQ23EGG4Heapi_43378(GM_CTX) {
    GM_FN(0x81843378); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = R(4) |R(4);
    R(4) = R(5) |R(5);
    R(5) = R(6) |R(6);
    GM_CALLV(0x81843394u, 0x802B8CC0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818433AC; }
    R(0) = lr;
    return;
L_818433AC:;
    R(3) = (0 + 0x81850000u);
    R(6) = (R(3) + 4700);
    R(3) = (R(6) + 6);
    R(5) = (R(6) + 18);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 82);
    GM_CALLV(0x818433C8u, 0x818380F8u, 0);
}

/* mod___nwa__FUl (mod___nwa__FUl, 76 bytes) */
static void mj_mod___nwa__FUl_433c8(GM_CTX) {
    GM_FN(0x818433C8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 4);
    R(5) = (0 + 0);
    GM_CALLV(0x818433E0u, 0x802B8CC0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818433F8; }
    R(0) = lr;
    return;
L_818433F8:;
    R(3) = (0 + 0x81850000u);
    R(6) = (R(3) + 4700);
    R(3) = (R(6) + 6);
    R(5) = (R(6) + 18);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 91);
    GM_CALLV(0x81843414u, 0x818380F8u, 0);
}

/* mod_fn_802B9260 (mod_fn_802B9260, 72 bytes) */
static void mj_mod_fn_802B9260_43414(GM_CTX) {
    GM_FN(0x81843414); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0);
    GM_CALLV(0x81843428u, 0x802B8CC0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843440; }
    R(0) = lr;
    return;
L_81843440:;
    R(3) = (0 + 0x81850000u);
    R(6) = (R(3) + 4700);
    R(3) = (R(6) + 6);
    R(5) = (R(6) + 18);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 100);
    GM_CALLV(0x8184345Cu, 0x818380F8u, 0);
}

/* mod___nwa__FUlPQ23EGG4Heapi (mod___nwa__FUlPQ23EGG4Heapi, 80 bytes) */
static void mj_mod___nwa__FUlPQ23EGG4Heapi_4345c(GM_CTX) {
    GM_FN(0x8184345C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = R(4) |R(4);
    R(4) = R(5) |R(5);
    R(5) = R(6) |R(6);
    GM_CALLV(0x81843478u, 0x802B8CC0u, 0);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843490; }
    R(0) = lr;
    return;
L_81843490:;
    R(3) = (0 + 0x81850000u);
    R(6) = (R(3) + 4700);
    R(3) = (R(6) + 6);
    R(5) = (R(6) + 18);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 109);
    GM_CALLV(0x818434ACu, 0x818380F8u, 0);
}

/* mod_fn_802BC900 (mod_fn_802BC900, 156 bytes) */
static void mj_mod_fn_802BC900_437a4(GM_CTX) {
    GM_FN(0x818437A4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (R(5) + -6288);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81843830; }
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (0 + 0x80350000u);
    R(5) = (R(5) + 48);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81843810; }
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -6288);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81843818; }
L_818437EC:;
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -6344);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_81843830; }
    R(3) = ld32(base, (R(3) + 40));
    R(4) = (0 + 1);
    GM_CALLV(0x8184380Cu, 0x81842C3Cu, 0);
    goto L_81843830;
L_81843810:;
    R(4) = R(3) |R(3);
    goto L_81843824;
L_81843818:;
    R(4) = ld32(base, (R(3) + 44));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_818437EC; }
L_81843824:;
    R(3) = ld32(base, (R(4) + 4));
    R(4) = (0 + 1);
    GM_CALLV(0x81843830u, 0x801E14E0u, 0);
L_81843830:;
    R(0) = lr;
}

/* mod_fn_802BC910 (mod_fn_802BC910, 156 bytes) */
static void mj_mod_fn_802BC910_43840(GM_CTX) {
    GM_FN(0x81843840); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (R(5) + -6288);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((CR_BIT(ctx, 2))) { goto L_818438CC; }
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (0 + 0x80350000u);
    R(5) = (R(5) + 48);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((CR_BIT(ctx, 2))) { goto L_818438AC; }
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -6288);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((CR_BIT(ctx, 2))) { goto L_818438B4; }
L_81843888:;
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -6344);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_818438CC; }
    R(3) = ld32(base, (R(3) + 40));
    R(4) = (0 + 0);
    GM_CALLV(0x818438A8u, 0x81842C3Cu, 0);
    goto L_818438CC;
L_818438AC:;
    R(4) = R(3) |R(3);
    goto L_818438C0;
L_818438B4:;
    R(4) = ld32(base, (R(3) + 44));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_81843888; }
L_818438C0:;
    R(3) = ld32(base, (R(4) + 4));
    R(4) = (0 + 0);
    GM_CALLV(0x818438CCu, 0x801E14E0u, 0);
L_818438CC:;
    R(0) = lr;
}

/* mod_fn_802BC920 (mod_fn_802BC920, 200 bytes) */
static void mj_mod_fn_802BC920_438dc(GM_CTX) {
    GM_FN(0x818438DC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -6288);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 0));
    cr_cmp_u(ctx, 0, R(3), R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81843988; }
    R(3) = (0 + 32);
    R(29) = R(4) |R(4);
    GM_CALLV(0x81843918u, 0x818432E4u, 0);
    R(28) = R(3) |R(3);
    GM_CALLV(0x81843920u, 0x802BDD00u, 0);
    R(3) = ld32(base, (R(30) + 0));
    R(4) = (0 + 0x80350000u);
    R(4) = (R(4) + 48);
    cr_cmp_u(ctx, 0, R(3), R(4));
    R(3) = R(30) |R(30);
    if ((CR_BIT(ctx, 2))) { goto L_81843974; }
    R(3) = ld32(base, (R(30) + 0));
    R(4) = (0 + 0x81860000u);
    R(4) = (R(4) + -6288);
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81843968; }
L_8184394C:;
    R(3) = ld32(base, (R(30) + 0));
    R(4) = (0 + 0x81860000u);
    R(4) = (R(4) + -6344);
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81843978; }
    st32(base, (R(30) + 68), R(28));
    goto L_81843978;
L_81843968:;
    R(3) = ld32(base, (R(30) + 44));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8184394C; }
L_81843974:;
    st32(base, (R(3) + 2888), R(28));
L_81843978:;
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    GM_CALLV(0x81843988u, 0x802BDD60u, 0);
L_81843988:;
    R(0) = lr;
}

/* mod_startPatternRumble__Q23EGG14CoreControllerFPCcib (mod_startPatternRumble__Q23EGG14CoreControllerFPCcib, 156 bytes) */
static void mj_mod_startPatternRumble__Q23EGG14CoreCont_439a4(GM_CTX) {
    GM_FN(0x818439A4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(8) = (0 + 0x81860000u);
    R(7) = ld32(base, (R(3) + 0));
    R(8) = (R(8) + -6288);
    cr_cmp_u(ctx, 0, R(7), R(8));
    if ((CR_BIT(ctx, 2))) { goto L_81843A30; }
    R(7) = ld32(base, (R(3) + 0));
    R(8) = (0 + 0x80350000u);
    R(8) = (R(8) + 48);
    cr_cmp_u(ctx, 0, R(7), R(8));
    R(7) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_818439FC; }
    R(7) = ld32(base, (R(3) + 0));
    R(8) = (0 + 0x81860000u);
    R(8) = (R(8) + -6288);
    cr_cmp_u(ctx, 0, R(7), R(8));
    if ((!CR_BIT(ctx, 2))) { goto L_81843A08; }
    R(7) = ld32(base, (R(3) + 44));
    cr_cmp_u(ctx, 0, R(7), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843A08; }
L_818439FC:;
    R(7) = ld32(base, (R(7) + 2888));
    cr_cmp_u(ctx, 0, R(7), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843A28; }
L_81843A08:;
    R(7) = ld32(base, (R(3) + 0));
    R(8) = (0 + 0x81860000u);
    R(8) = (R(8) + -6344);
    cr_cmp_u(ctx, 0, R(7), R(8));
    if ((!CR_BIT(ctx, 2))) { goto L_81843A30; }
    R(7) = ld32(base, (R(3) + 68));
    cr_cmp_u(ctx, 0, R(7), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843A30; }
L_81843A28:;
    R(3) = R(7) |R(7);
    GM_CALLV(0x81843A30u, 0x802BDF70u, 0);
L_81843A30:;
    R(0) = lr;
}

/* mod_fn_802BC9A0 (mod_fn_802BC9A0, 156 bytes) */
static void mj_mod_fn_802BC9A0_43a40(GM_CTX) {
    GM_FN(0x81843A40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(7) = (0 + 0x81860000u);
    R(6) = ld32(base, (R(3) + 0));
    R(7) = (R(7) + -6288);
    cr_cmp_u(ctx, 0, R(6), R(7));
    if ((CR_BIT(ctx, 2))) { goto L_81843ACC; }
    R(6) = ld32(base, (R(3) + 0));
    R(7) = (0 + 0x80350000u);
    R(7) = (R(7) + 48);
    cr_cmp_u(ctx, 0, R(6), R(7));
    R(6) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_81843A98; }
    R(6) = ld32(base, (R(3) + 0));
    R(7) = (0 + 0x81860000u);
    R(7) = (R(7) + -6288);
    cr_cmp_u(ctx, 0, R(6), R(7));
    if ((!CR_BIT(ctx, 2))) { goto L_81843AA4; }
    R(6) = ld32(base, (R(3) + 44));
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843AA4; }
L_81843A98:;
    R(6) = ld32(base, (R(6) + 2888));
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843AC4; }
L_81843AA4:;
    R(6) = ld32(base, (R(3) + 0));
    R(7) = (0 + 0x81860000u);
    R(7) = (R(7) + -6344);
    cr_cmp_u(ctx, 0, R(6), R(7));
    if ((!CR_BIT(ctx, 2))) { goto L_81843ACC; }
    R(6) = ld32(base, (R(3) + 68));
    cr_cmp_u(ctx, 0, R(6), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843ACC; }
L_81843AC4:;
    R(3) = R(6) |R(6);
    GM_CALLV(0x81843ACCu, 0x802BDFC0u, 0);
L_81843ACC:;
    R(0) = lr;
}

/* mod_fn_802BC9C0 (mod_fn_802BC9C0, 156 bytes) */
static void mj_mod_fn_802BC9C0_43adc(GM_CTX) {
    GM_FN(0x81843ADC); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x81860000u);
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (R(5) + -6288);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81843B68; }
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (0 + 0x80350000u);
    R(5) = (R(5) + 48);
    cr_cmp_u(ctx, 0, R(4), R(5));
    R(4) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_81843B34; }
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -6288);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_81843B40; }
    R(4) = ld32(base, (R(3) + 44));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843B40; }
L_81843B34:;
    R(4) = ld32(base, (R(4) + 2888));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843B60; }
L_81843B40:;
    R(4) = ld32(base, (R(3) + 0));
    R(5) = (0 + 0x81860000u);
    R(5) = (R(5) + -6344);
    cr_cmp_u(ctx, 0, R(4), R(5));
    if ((!CR_BIT(ctx, 2))) { goto L_81843B68; }
    R(4) = ld32(base, (R(3) + 68));
    cr_cmp_u(ctx, 0, R(4), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843B68; }
L_81843B60:;
    R(3) = R(4) |R(4);
    GM_CALLV(0x81843B68u, 0x802BDDF0u, 0);
L_81843B68:;
    R(0) = lr;
}

/* mod_fn_802BCDE0 (mod_fn_802BCDE0, 1028 bytes) */
static void mj_mod_fn_802BCDE0_43b78(GM_CTX) {
    GM_FN(0x81843B78); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (f + 44);
    R(5) = (0 + 16);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = (R(30) + 24);
    st32(base, (f + 48), R(3));
    R(3) = ld32(base, (R(30) + 4));
    GM_CALLV(0x81843BB0u, 0x801ED3B0u, 0);
    R(4) = ld32(base, (f + 44));
    R(4) = R(3) | ~R(4);
    CR0(ctx, R(4));
    R(4) = (0 + 1);
    if ((CR_BIT(ctx, 2))) { goto L_81843BC4; }
    R(4) = R(3) |R(3);
L_81843BC4:;
    R(3) = ld32(base, (R(30) + 4));
    st32(base, (R(30) + 2840), R(4));
    R(4) = (f + 40);
    GM_CALLV(0x81843BD4u, 0x801E0F40u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), -1);
    if ((CR_BIT(ctx, 2))) { goto L_81843BFC; }
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843C08; }
    R(3) = ld32(base, (f + 40));
    cr_cmp_u(ctx, 0, R(3), 0xFEu);
    R(3) = ld8(base, (R(30) + 2844));
    if ((CR_BIT(ctx, 2))) { goto L_81843C00; }
    R(3) = R(3) | 0x1u;
    goto L_81843C04;
L_81843BFC:;
    R(3) = ld8(base, (R(30) + 2844));
L_81843C00:;
    R(3) = R(3) & 0xFEu;
L_81843C04:;
    st8(base, (R(30) + 2844), R(3));
L_81843C08:;
    R(3) = ld32(base, (R(30) + 2840));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81843D5C; }
    R(6) = ld8(base, (R(30) + 116));
    R(4) = (0 + 0);
    R(29) = ld32(base, (R(30) + 8));
    cr_cmp_u(ctx, 0, R(6), 0x1u);
    st32(base, (R(30) + 8), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81843CD8; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(30) + 120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -31112); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 124); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 7, ctx->f[2].d, ctx->f[1].d);
    R(3) = ctx->cr;
    R(4) = ctx->cr;
    R(3) = R(3) & 0x1u;
    R(4) = rotl32(R(4), 30) & 0x1u;
    R(3) = R(3) ^ 0x1u;
    R(4) = R(4) ^ 0x1u;
    R(3) = R(4) &R(3);
    CR0(ctx, R(3));
    R(4) = (0 + 4);
    if ((!CR_BIT(ctx, 2))) { goto L_81843C90; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31028); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_fcmp(ctx, 7, ctx->f[2].d, ctx->f[3].d);
    R(3) = ctx->cr;
    R(4) = ctx->cr;
    R(3) = R(3) & 0x1u;
    R(4) = rotl32(R(4), 29) & 0x1u;
    R(3) = R(4) |R(3);
    CR0(ctx, R(3));
    R(4) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_81843C90; }
    R(4) = (0 + 8);
L_81843C90:;
    cr_fcmp(ctx, 7, ctx->f[0].d, ctx->f[1].d);
    R(3) = ctx->cr;
    R(5) = ctx->cr;
    R(3) = R(3) & 0x1u;
    R(5) = rotl32(R(5), 30) & 0x1u;
    R(3) = R(5) |R(3);
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81843D04; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31028); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 7, ctx->f[0].d, ctx->f[1].d);
    R(3) = ctx->cr;
    R(5) = ctx->cr;
    R(3) = R(3) & 0x1u;
    R(5) = rotl32(R(5), 29) & 0x1u;
    R(3) = R(5) |R(3);
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81843D08; }
    R(4) = R(4) | 0x1u;
    goto L_81843D08;
L_81843CD8:;
    R(3) = ld32(base, (R(30) + 20));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843D28; }
    R(5) = ld8(base, (R(3) + 48));
    cr_cmp_u(ctx, 0, R(6), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843D20; }
    R(4) = R(5) | 0x1u;
    st8(base, (R(3) + 48), R(4));
    GM_CALLV(0x81843CFCu, 0x81843F7Cu, 0);
    R(4) = ld32(base, (R(30) + 8));
    goto L_81843D28;
L_81843D04:;
    R(4) = R(4) | 0x2u;
L_81843D08:;
    R(3) = ld32(base, (R(30) + 20));
    R(4) = rotl32(R(4), 16) & 0xFFFF0000u;
    st32(base, (R(30) + 8), R(4));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843D28; }
    R(5) = ld8(base, (R(3) + 48));
L_81843D20:;
    R(5) = R(5) & 0xFEu;
    st8(base, (R(3) + 48), R(5));
L_81843D28:;
    R(3) = ld32(base, (R(30) + 24));
    R(7) = R(4) & ~R(29);
    R(5) = ld32(base, (R(30) + 28));
    R(8) = R(29) & ~R(4);
    R(6) = ld32(base, (R(30) + 32));
    R(3) = (rotl32(R(4), 0) & 0xF0000u) | (R(3) & ~0xF0000u);
    R(5) = (rotl32(R(7), 0) & 0xF0000u) | (R(5) & ~0xF0000u);
    st32(base, (R(30) + 12), R(7));
    R(6) = (rotl32(R(8), 0) & 0xF0000u) | (R(6) & ~0xF0000u);
    st32(base, (R(30) + 16), R(8));
    st32(base, (R(30) + 24), R(3));
    st32(base, (R(30) + 28), R(5));
    st32(base, (R(30) + 32), R(6));
L_81843D5C:;
    R(4) = (R(30) + 2892);
    R(3) = (R(30) + 2888);
    R(5) = (0 + 12);
    ctx->ctr = R(5);
L_81843D6C:;
    { uint32_t ea_ = R(3) + 4; R(5) = ld32(base, ea_); R(3) = ea_; }
    st32(base, (R(3) + 48), R(5));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81843D6C; }
    R(7) = ld32(base, (R(30) + 36));
    R(3) = (0 + 0);
    R(8) = ld32(base, (R(30) + 40));
    R(10) = (0 + 3);
    R(9) = ld32(base, (R(30) + 44));
    R(5) = (f + 24);
    { uint32_t ea_ = (R(30) + 3008); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(6) = (R(30) + 2844);
    st32(base, (f + 28), R(7));
    R(7) = (0 + 1);
    st32(base, (f + 32), R(8));
    R(8) = (0 + -2);
    st32(base, (f + 36), R(9));
    R(9) = (0 + 0);
    st8(base, (R(30) + 2988), R(3));
    ctx->ctr = R(10);
    R(10) = (0 + 0);
L_81843DBC:;
    { uint32_t ea_ = R(6) + 4; ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); R(6) = ea_; }
    { uint32_t ea_ = R(5) + 4; ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); R(5) = ea_; }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d - ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_81843E00; }
    R(12) = ld32(base, (R(6) + 148));
    R(11) = ld32(base, (R(30) + 2992));
    R(12) = (R(12) + 1);
    st32(base, (R(6) + 148), R(12));
    cr_cmp_s(ctx, 0, (int32_t)R(11), (int32_t)R(12));
    if ((CR_BIT(ctx, 1))) { goto L_81843E10; }
    st32(base, (R(6) + 148), R(11));
    { uint32_t s_ = R(9) & 63; R(11) = s_ > 31 ? 0 : R(7) << s_; }
    R(10) = R(10) |R(11);
    st8(base, (R(30) + 2988), R(10));
    { uint32_t ea_ = (R(6) + 164); stfs(base, ea_, ctx->f[1].d); }
    goto L_81843E10;
L_81843E00:;
    R(11) = rotl32(R(8), (R(9) & 31)) & 0xFFFFFFFFu;
    R(10) = R(10) &R(11);
    st8(base, (R(30) + 2988), R(10));
    st32(base, (R(6) + 148), R(3));
L_81843E10:;
    R(9) = (R(9) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81843DBC; }
    R(3) = R(30) |R(30);
    R(5) = (0 + 1);
    GM_CALLV(0x81843E24u, 0x802BC9E0u, 0);
    R(3) = ld8(base, (R(30) + 2876));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843E94; }
    R(3) = ld32(base, (R(30) + 2872));
    R(4) = ld8(base, (R(30) + 2885));
    { uint32_t s_ = R(4) & 63; R(3) = s_ > 31 ? 0 : R(3) >> s_; }
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81843E50; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81843E4Cu, 0x802BC900u, 0);
    goto L_81843E58;
L_81843E50:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81843E58u, 0x802BC910u, 0);
L_81843E58:;
    R(3) = ld8(base, (R(30) + 2885));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843E68; }
    R(3) = ld8(base, (R(30) + 2884));
L_81843E68:;
    R(4) = ld32(base, (R(30) + 2880));
    R(3) = (R(3) + -1);
    st8(base, (R(30) + 2885), R(3));
    R(3) = (R(4) + -1);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    st32(base, (R(30) + 2880), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81843E94; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81843E8Cu, 0x802BC910u, 0);
    R(3) = (0 + 0);
    st8(base, (R(30) + 2876), R(3));
L_81843E94:;
    R(3) = ld32(base, (R(30) + 2888));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_81843EA4; }
    GM_CALLV(0x81843EA4u, 0x802BDE60u, 0);
L_81843EA4:;
    R(3) = ld32(base, (R(30) + 24));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81843F44; }
    { uint32_t ea_ = (R(30) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(30) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 2848); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 2852); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 44); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 2856); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[4].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + -31080); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[5].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[0].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[2].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[3].d);
    if ((CR_BIT(ctx, 1))) { goto L_81843F44; }
    R(3) = (f + 20);
    R(4) = R(30) |R(30);
    GM_CALLV(0x81843EFCu, 0x802BC8C0u, 0);
    { uint32_t ea_ = (R(30) + 2860); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (f + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 2864); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + -31016); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[0].d + ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((CR_BIT(ctx, 1))) { goto L_81843F44; }
    R(3) = ld32(base, (R(30) + 2868));
    R(4) = rotl32(R(3), 26) & 0x3FFFFFFu;
    cr_cmp_u(ctx, 0, R(4), 0xD2Eu);
    if ((CR_BIT(ctx, 1))) { goto L_81843F4C; }
    R(3) = (R(3) + 1);
    goto L_81843F48;
L_81843F44:;
    R(3) = (0 + 0);
L_81843F48:;
    st32(base, (R(30) + 2868), R(3));
L_81843F4C:;
    R(3) = (0 + 0x81860000u);
    R(3) = ld32(base, (R(3) + -300));
    R(4) = ld32(base, (f + 48));
    cr_cmp_u(ctx, 0, R(3), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_81843F78; }
    R(0) = lr;
    return;
L_81843F78:;
    GM_CALLV(0x81843F7Cu, 0x81844FCCu, 0);
}

/* mfn_81844184 (mfn_81844184, 192 bytes) */
static void mj_mfn_81844184_44184(GM_CTX) {
    GM_FN(0x81844184); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 4);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 24));
    R(3) = ((int32_t)R(3) * 56);
    GM_CALLV(0x818441A8u, 0x818434ACu, 0);
    R(6) = ld32(base, (R(30) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81844230; }
    R(5) = ld32(base, (R(30) + 28));
    R(4) = (0 + 0x81860000u);
    R(8) = (R(3) + -56);
    R(9) = (R(3) + -24);
    R(3) = (0 + 0);
    R(4) = (R(4) + -6288);
    R(5) = (R(5) + -4);
    R(7) = (0 + 0);
L_818441D4:;
    { uint32_t ea_ = R(5) + 4; R(12) = ld32(base, ea_); R(5) = ea_; }
    R(10) = (R(9) + 56);
    R(11) = ld32(base, (R(12) + 20));
    cr_cmp_u(ctx, 0, R(11), 0x0u);
    R(11) = (R(8) + 56);
    if ((!CR_BIT(ctx, 2))) { goto L_8184421C; }
    R(6) = ld32(base, (R(12) + 4));
    st32(base, (R(12) + 20), R(11));
    st32(base, (R(8) + 96), R(6));
    R(6) = ld32(base, (R(30) + 24));
    st32(base, (R(8) + 56), R(4));
    st32(base, (R(8) + 60), R(3));
    st32(base, (R(8) + 64), R(3));
    st32(base, (R(8) + 68), R(3));
    st32(base, (R(9) + 56), R(3));
    st32(base, (R(9) + 60), R(3));
    st32(base, (R(8) + 100), R(12));
    st32(base, (R(8) + 108), R(3));
L_8184421C:;
    R(7) = (R(7) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(6));
    R(8) = R(11) |R(11);
    R(9) = R(10) |R(10);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_818441D4; }
L_81844230:;
    R(0) = lr;
}

/* mfn_81844244 (mfn_81844244, 936 bytes) */
static void mj_mfn_81844244_44244(GM_CTX) {
    GM_FN(0x81844244); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld8(base, (R(4) + 10));
    st32(base, (R(30) + 44), R(4));
    R(3) = (int8_t)R(3);
    CR0(ctx, R(3));
    R(3) = ld8(base, (R(30) + 48));
    if ((CR_BIT(ctx, 0))) { goto L_81844454; }
    R(6) = (0 + 0x81850000u);
    R(5) = ld32(base, (R(30) + 4));
    R(3) = R(3) | 0x1u;
    { uint32_t ea_ = (R(6) + -30800); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(6) = R(5) & 0x40u;
    CR0(ctx, R(6));
    st8(base, (R(30) + 48), R(3));
    ctx->f[1].u = ctx->f[0].u;
    if ((!CR_BIT(ctx, 2))) { goto L_818442BC; }
    R(3) = ld8(base, (R(4) + 6));
    R(6) = (0 + 0x43300000u);
    st32(base, (f + 48), R(6));
    st32(base, (f + 52), R(3));
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (f + 48); ctx->f[1].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(3) + -30832); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30860); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->f[1].d - ctx->f[2].d;
    ctx->f[1].d = frsp(ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[3].d);
L_818442BC:;
    R(3) = R(5) & 0x20u;
    CR0(ctx, R(3));
    { uint32_t ea_ = (R(30) + 32); stfs(base, ea_, ctx->f[1].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_818442F8; }
    R(3) = ld8(base, (R(4) + 7));
    R(6) = (0 + 0x43300000u);
    st32(base, (f + 40), R(6));
    st32(base, (f + 44), R(3));
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (f + 40); ctx->f[0].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(3) + -30832); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -30860); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->f[0].d - ctx->f[1].d;
    ctx->f[0].d = frsp(ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[2].d);
L_818442F8:;
    R(3) = ld8(base, (R(4) + 2));
    R(6) = (0 + 0x43300000u);
    { uint32_t ea_ = (R(30) + 36); stfs(base, ea_, ctx->f[0].d); }
    R(7) = (0 + 0x81850000u);
    R(3) = (int8_t)R(3);
    R(3) = R(3) ^ 0x80000000u;
    st32(base, (f + 32), R(6));
    st32(base, (f + 36), R(3));
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(7) + -31040); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(7) = (0 + 0x81850000u);
    { uint32_t ea_ = (f + 32); ctx->f[1].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(3) + -31132); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(3) = ld8(base, (R(4) + 3));
    ctx->f[1].d = ctx->f[1].d - ctx->f[0].d;
    ctx->f[1].d = frsp(ctx->f[1].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d / ctx->f[5].d);
    R(3) = (int8_t)R(3);
    R(3) = R(3) ^ 0x80000000u;
    { uint32_t ea_ = (R(30) + 16); stfs(base, ea_, ctx->f[3].d); }
    st32(base, (f + 24), R(6));
    st32(base, (f + 28), R(3));
    { uint32_t ea_ = (f + 24); ctx->f[1].u = ld64(base, ea_); }
    R(3) = ld8(base, (R(4) + 4));
    { uint32_t ea_ = (R(7) + -31112); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(3) = (int8_t)R(3);
    R(3) = R(3) ^ 0x80000000u;
    ctx->f[1].d = ctx->f[1].d - ctx->f[0].d;
    ctx->f[1].d = frsp(ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d / ctx->f[5].d);
    { uint32_t ea_ = (R(30) + 20); stfs(base, ea_, ctx->f[2].d); }
    st32(base, (f + 16), R(6));
    st32(base, (f + 20), R(3));
    { uint32_t ea_ = (f + 16); ctx->f[1].u = ld64(base, ea_); }
    R(3) = ld8(base, (R(4) + 5));
    R(3) = (int8_t)R(3);
    R(3) = R(3) ^ 0x80000000u;
    ctx->f[1].d = ctx->f[1].d - ctx->f[0].d;
    ctx->f[1].d = frsp(ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[5].d);
    { uint32_t ea_ = (R(30) + 24); stfs(base, ea_, ctx->f[1].d); }
    st32(base, (f + 8), R(6));
    st32(base, (f + 12), R(3));
    { uint32_t ea_ = (f + 8); ctx->f[6].u = ld64(base, ea_); }
    cr_fcmp(ctx, 7, ctx->f[3].d, ctx->f[4].d);
    R(3) = ctx->cr;
    R(6) = ctx->cr;
    ctx->f[0].d = ctx->f[6].d - ctx->f[0].d;
    R(3) = R(3) & 0x1u;
    R(6) = rotl32(R(6), 30) & 0x1u;
    R(3) = R(3) ^ 0x1u;
    R(6) = R(6) ^ 0x1u;
    R(3) = R(6) &R(3);
    CR0(ctx, R(3));
    ctx->f[0].d = frsp(ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[5].d);
    R(3) = (0 + 4);
    { uint32_t ea_ = (R(30) + 28); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_8184440C; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31028); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    cr_fcmp(ctx, 7, ctx->f[3].d, ctx->f[5].d);
    R(3) = ctx->cr;
    R(6) = ctx->cr;
    R(3) = R(3) & 0x1u;
    R(6) = rotl32(R(6), 29) & 0x1u;
    R(3) = R(6) |R(3);
    CR0(ctx, R(3));
    R(3) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8184440C; }
    R(3) = (0 + 8);
L_8184440C:;
    cr_fcmp(ctx, 7, ctx->f[2].d, ctx->f[4].d);
    R(6) = ctx->cr;
    R(7) = ctx->cr;
    R(6) = R(6) & 0x1u;
    R(7) = rotl32(R(7), 30) & 0x1u;
    R(6) = R(7) |R(6);
    CR0(ctx, R(6));
    if ((CR_BIT(ctx, 2))) { goto L_81844460; }
    R(6) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(6) + -31028); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_fcmp(ctx, 7, ctx->f[2].d, ctx->f[3].d);
    R(6) = ctx->cr;
    R(7) = ctx->cr;
    R(6) = R(6) & 0x1u;
    R(7) = rotl32(R(7), 29) & 0x1u;
    R(6) = R(7) |R(6);
    CR0(ctx, R(6));
    if ((!CR_BIT(ctx, 2))) { goto L_81844464; }
    R(3) = R(3) | 0x1u;
    goto L_81844464;
L_81844454:;
    R(3) = R(3) & 0xFEu;
    st8(base, (R(30) + 48), R(3));
    goto L_818445D8;
L_81844460:;
    R(3) = R(3) | 0x2u;
L_81844464:;
    R(6) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(6) + -31112); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = ld16(base, (R(4) + 0));
    cr_fcmp(ctx, 7, ctx->f[1].d, ctx->f[2].d);
    R(6) = ctx->cr;
    R(7) = ctx->cr;
    R(6) = R(6) & 0x1u;
    R(7) = rotl32(R(7), 30) & 0x1u;
    R(6) = R(6) ^ 0x1u;
    R(7) = R(7) ^ 0x1u;
    R(6) = R(7) &R(6);
    CR0(ctx, R(6));
    R(6) = (0 + 4);
    if ((!CR_BIT(ctx, 2))) { goto L_818444C4; }
    R(6) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(6) + -31028); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_fcmp(ctx, 7, ctx->f[1].d, ctx->f[3].d);
    R(6) = ctx->cr;
    R(7) = ctx->cr;
    R(6) = R(6) & 0x1u;
    R(7) = rotl32(R(7), 29) & 0x1u;
    R(6) = R(7) |R(6);
    CR0(ctx, R(6));
    R(6) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_818444C4; }
    R(6) = (0 + 8);
L_818444C4:;
    cr_fcmp(ctx, 7, ctx->f[0].d, ctx->f[2].d);
    R(7) = ctx->cr;
    R(8) = ctx->cr;
    R(4) = (rotl32(R(3), 16) & 0xFFFF0000u) | (R(4) & ~0xFFFF0000u);
    R(7) = R(7) & 0x1u;
    R(8) = rotl32(R(8), 30) & 0x1u;
    R(7) = R(8) |R(7);
    CR0(ctx, R(7));
    if ((CR_BIT(ctx, 2))) { goto L_81844510; }
    R(3) = (0 + 0x81850000u);
    { uint32_t ea_ = (R(3) + -31028); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 7, ctx->f[0].d, ctx->f[1].d);
    R(3) = ctx->cr;
    R(7) = ctx->cr;
    R(3) = R(3) & 0x1u;
    R(7) = rotl32(R(7), 29) & 0x1u;
    R(3) = R(7) |R(3);
    CR0(ctx, R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_81844514; }
    R(6) = R(6) | 0x1u;
    goto L_81844514;
L_81844510:;
    R(6) = R(6) | 0x2u;
L_81844514:;
    R(4) = (rotl32(R(6), 20) & 0xFFF00000u) | (R(4) & ~0xFFF00000u);
    R(3) = R(4) & ~R(5);
    st32(base, (R(30) + 8), R(3));
    R(3) = ld32(base, (R(30) + 68));
    st32(base, (R(30) + 4), R(4));
    R(4) = R(5) & ~R(4);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    st32(base, (R(30) + 12), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_8184453C; }
    GM_CALLV(0x8184453Cu, 0x802BDE60u, 0);
L_8184453C:;
    R(3) = ld8(base, (R(30) + 56));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_818445AC; }
    R(3) = ld32(base, (R(30) + 52));
    R(4) = ld8(base, (R(30) + 65));
    { uint32_t s_ = R(4) & 63; R(3) = s_ > 31 ? 0 : R(3) >> s_; }
    R(3) = R(3) & 0x1u;
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_81844568; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x81844564u, 0x802BC900u, 0);
    goto L_81844570;
L_81844568:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x81844570u, 0x802BC910u, 0);
L_81844570:;
    R(3) = ld8(base, (R(30) + 65));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81844580; }
    R(3) = ld8(base, (R(30) + 64));
L_81844580:;
    R(4) = ld32(base, (R(30) + 60));
    R(3) = (R(3) + -1);
    st8(base, (R(30) + 65), R(3));
    R(3) = (R(4) + -1);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    st32(base, (R(30) + 60), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_818445AC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x818445A4u, 0x802BC910u, 0);
    R(3) = (0 + 0);
    st8(base, (R(30) + 56), R(3));
L_818445AC:;
    R(3) = ld32(base, (R(30) + 4));
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((CR_BIT(ctx, 2))) { goto L_818445D0; }
    R(3) = ld32(base, (R(30) + 72));
    R(4) = rotl32(R(3), 26) & 0x3FFFFFFu;
    cr_cmp_u(ctx, 0, R(4), 0xD2Eu);
    if ((CR_BIT(ctx, 1))) { goto L_818445D8; }
    R(3) = (R(3) + 1);
    goto L_818445D4;
L_818445D0:;
    R(3) = (0 + 0);
L_818445D4:;
    st32(base, (R(30) + 72), R(3));
L_818445D8:;
    R(0) = lr;
}

/* mfn_81844664 (mfn_81844664, 112 bytes) */
static void mj_mfn_81844664_44664(GM_CTX) {
    GM_FN(0x81844664); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = (0 + 0x81860000u);
    R(7) = ld32(base, (R(29) + -308));
    cr_cmp_u(ctx, 0, R(7), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_818446B8; }
    R(3) = (0 + 80);
    GM_CALLV(0x81844690u, 0x818432E4u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x81844698u, 0x818446D4u, 0);
    st32(base, (R(29) + -308), R(30));
    R(3) = R(30) |R(30);
    R(0) = lr;
    return;
L_818446B8:;
    R(3) = (0 + 0x81850000u);
    R(3) = (R(3) + 4738);
    R(5) = (R(3) + 34);
    R(6) = (R(3) + 18);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(4) = (0 + 380);
    GM_CALLV(0x818446D4u, 0x818380F8u, 0);
}

/* mfn_818446D4 (mfn_818446D4, 516 bytes) */
static void mj_mfn_818446D4_446d4(GM_CTX) {
    GM_FN(0x818446D4); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x818446F4u, 0x802BA2D0u, 0);
    R(4) = (0 + 0x81860000u);
    R(4) = (R(4) + -6232);
    R(5) = (0 + 0x81860000u);
    R(3) = (0 + 0);
    st32(base, (R(30) + 0), R(4));
    R(4) = R(30) |R(30);
    R(5) = (R(5) + -6220);
    st32(base, (R(30) + 20), R(3));
    st32(base, (R(30) + 24), R(3));
    { uint32_t ea_ = R(4) + 16; st32(base, ea_, R(5)); R(4) = ea_; }
    R(5) = (0 + 4);
    ctx->ctr = R(5);
L_81844724:;
    { uint32_t ea_ = R(4) + 12; st16(base, ea_, R(3)); R(4) = ea_; }
    st32(base, (R(4) + 2), R(3));
    st32(base, (R(4) + 6), R(3));
    st8(base, (R(4) + 10), R(3));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_81844724; }
    GM_CALLV(0x8184473Cu, 0x818425A0u, 0);
    R(29) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(3), 0x0u);
    if ((!CR_BIT(ctx, 2))) { goto L_81844760; }
    R(3) = (0 + 0x81850000u);
    R(4) = (R(3) + 4738);
    R(3) = (R(4) + 73);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    R(5) = (0 + 391);
    GM_CALLV(0x81844760u, 0x8015F730u, 0);
L_81844760:;
    R(28) = (0 + 4);
    R(3) = (0 + 16);
    st32(base, (R(30) + 20), R(28));
    GM_CALLV(0x81844770u, 0x818433C8u, 0);
    st32(base, (R(30) + 24), R(3));
    R(3) = (0 + 308);
    GM_CALLV(0x8184477Cu, 0x818433C8u, 0);
    R(4) = ld32(base, (R(30) + 20));
    R(6) = (0 + 1);
    st32(base, (R(3) + 120), R(6));
    R(6) = (0 + 2);
    st32(base, (R(3) + 196), R(6));
    R(6) = (0 + 3);
    st32(base, (R(3) + 272), R(6));
    R(6) = (0 + 0x81860000u);
    R(5) = (0 + 0);
    R(6) = (R(6) + -6344);
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    st32(base, (R(3) + 0), R(28));
    st32(base, (R(3) + 8), R(5));
    st32(base, (R(3) + 12), R(5));
    st32(base, (R(3) + 16), R(5));
    st32(base, (R(3) + 36), R(5));
    st32(base, (R(3) + 40), R(5));
    st32(base, (R(3) + 44), R(5));
    st32(base, (R(3) + 48), R(5));
    st32(base, (R(3) + 56), R(5));
    st8(base, (R(3) + 60), R(5));
    st32(base, (R(3) + 64), R(5));
    st16(base, (R(3) + 68), R(5));
    st32(base, (R(3) + 72), R(5));
    st32(base, (R(3) + 76), R(5));
    st32(base, (R(3) + 84), R(5));
    st32(base, (R(3) + 88), R(5));
    st32(base, (R(3) + 92), R(5));
    st32(base, (R(3) + 112), R(5));
    st32(base, (R(3) + 116), R(5));
    st32(base, (R(3) + 124), R(5));
    st32(base, (R(3) + 132), R(5));
    st8(base, (R(3) + 136), R(5));
    st32(base, (R(3) + 140), R(5));
    st16(base, (R(3) + 144), R(5));
    st32(base, (R(3) + 148), R(5));
    st32(base, (R(3) + 152), R(5));
    st32(base, (R(3) + 160), R(5));
    st32(base, (R(3) + 164), R(5));
    st32(base, (R(3) + 168), R(5));
    st32(base, (R(3) + 188), R(5));
    st32(base, (R(3) + 192), R(5));
    st32(base, (R(3) + 200), R(5));
    st32(base, (R(3) + 208), R(5));
    st8(base, (R(3) + 212), R(5));
    st32(base, (R(3) + 216), R(5));
    st16(base, (R(3) + 220), R(5));
    st32(base, (R(3) + 224), R(5));
    st32(base, (R(3) + 228), R(5));
    st32(base, (R(3) + 236), R(5));
    st32(base, (R(3) + 240), R(5));
    st32(base, (R(3) + 244), R(5));
    st32(base, (R(3) + 264), R(5));
    st32(base, (R(3) + 268), R(5));
    st32(base, (R(3) + 276), R(5));
    st32(base, (R(3) + 284), R(5));
    st8(base, (R(3) + 288), R(5));
    st32(base, (R(3) + 292), R(5));
    st16(base, (R(3) + 296), R(5));
    st32(base, (R(3) + 4), R(6));
    st32(base, (R(3) + 80), R(6));
    st32(base, (R(3) + 156), R(6));
    st32(base, (R(3) + 232), R(6));
    st32(base, (R(3) + 300), R(5));
    st32(base, (R(3) + 304), R(5));
    if ((!CR_BIT(ctx, 1))) { goto L_818448AC; }
    R(3) = (R(3) + 4);
    R(4) = (0 + 0);
L_8184488C:;
    R(6) = ld32(base, (R(30) + 24));
    R(4) = (R(4) + 1);
    st32(base, (R(6) + R(5)), R(3));
    R(3) = (R(3) + 76);
    R(6) = ld32(base, (R(30) + 20));
    R(5) = (R(5) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(6));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8184488C; }
L_818448AC:;
    { uint32_t a_ = R(29); R(3) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(3) < a_; }
    { uint64_t t_ = (uint64_t)(~R(3)) + (R(29)) + ctx->xer_ca; R(4) = t_; ctx->xer_ca = (t_ >> 32); }
    st8(base, (R(30) + 76), R(4));
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* mfn_818448D8 (mfn_818448D8, 104 bytes) */
static void mj_mfn_818448D8_448d8(GM_CTX) {
    GM_FN(0x818448D8); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(29) = R(3) |R(3);
    R(30) = R(4) |R(4);
    R(3) = (R(3) + 16);
    if ((CR_BIT(ctx, 0))) { goto L_8184490C; }
    R(4) = ld32(base, (R(29) + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(30));
    if ((CR_BIT(ctx, 1))) { goto L_8184491C; }
L_8184490C:;
    R(4) = ld32(base, (R(29) + 16));
    R(4) = ld32(base, (R(4) + 24));
    ctx->ctr = R(4);
    GM_CALLV(0x8184491Cu, ctx->ctr, 0);
L_8184491C:;
    R(3) = ld32(base, (R(29) + 24));
    R(4) = rotl32(R(30), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(3) + R(4)));
    R(0) = lr;
}

/* mfn_8184499C (mfn_8184499C, 180 bytes) */
static void mj_mfn_8184499C_4499c(GM_CTX) {
    GM_FN(0x8184499C); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 48);
    R(29) = (R(3) + 28);
    R(30) = R(3) |R(3);
    R(3) = (R(3) + 27);
    ctx->ctr = R(4);
    R(4) = (0 + 0);
L_818449D0:;
    { uint32_t ea_ = R(3) + 1; st8(base, ea_, R(4)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_818449D0; }
    R(3) = ld8(base, (R(30) + 76));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81844A30; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x818449ECu, 0x81842714u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x818449F4u, 0x81842F7Cu, 0);
    R(3) = ld32(base, (R(30) + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81844A30; }
    R(28) = (0 + 0);
    R(27) = (0 + 0);
L_81844A08:;
    R(3) = ld32(base, (R(30) + 24));
    R(4) = R(29) |R(29);
    R(3) = ld32(base, (R(3) + R(28)));
    GM_CALLV(0x81844A18u, 0x81844244u, 0);
    R(3) = ld32(base, (R(30) + 20));
    R(27) = (R(27) + 1);
    R(29) = (R(29) + 12);
    R(28) = (R(28) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(27), (int32_t)R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81844A08; }
L_81844A30:;
    R(0) = lr;
}

/* mfn_81844A50 (mfn_81844A50, 232 bytes) */
static void mj_mfn_81844A50_44a50(GM_CTX) {
    GM_FN(0x81844A50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld8(base, (R(3) + 76));
    cr_cmp_u(ctx, 0, R(3), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_81844B0C; }
    R(3) = ld32(base, (R(30) + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_81844B00; }
    R(27) = ld32(base, (R(30) + 16));
    R(26) = (0 + 0);
    R(29) = (R(30) + 16);
    R(25) = (0 + 0x80000000u);
    R(24) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(26), (int32_t)R(3));
    R(28) = (0 + 0);
L_81844AB0:;
    if ((CR_BIT(ctx, 0))) { goto L_81844AC8; }
    R(3) = ld32(base, (R(27) + 24));
    ctx->ctr = R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x81844AC4u, ctx->ctr, 0);
    R(3) = ld32(base, (R(30) + 20));
L_81844AC8:;
    R(4) = ld32(base, (R(30) + 24));
    R(4) = ld32(base, (R(4) + R(26)));
    R(4) = ld8(base, (R(4) + 48));
    R(4) = R(4) & 0x1u;
    CR0(ctx, R(4));
    if ((CR_BIT(ctx, 2))) { goto L_81844AE4; }
    R(4) = (0 + 0);
    goto L_81844AE8;
L_81844AE4:;
    { uint32_t s_ = R(24) & 63; R(4) = s_ > 31 ? 0 : R(25) >> s_; }
L_81844AE8:;
    R(24) = (R(24) + 1);
    R(28) = R(4) |R(28);
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(3));
    R(26) = (R(26) + 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_81844AB0; }
    goto L_81844B04;
L_81844B00:;
    R(28) = (0 + 0);
L_81844B04:;
    R(3) = R(28) |R(28);
    GM_CALLV(0x81844B0Cu, 0x818423A0u, 0);
L_81844B0C:;
    R(0) = lr;
}

/* mfn_81844EF4 (mfn_81844EF4, 28 bytes) */
static void mj_mfn_81844EF4_44ef4(GM_CTX) {
    R(6) = (0 + 0x81860000u);
    R(7) = ld32(base, (R(6) + -304));
    st32(base, (R(5) + 4), R(4));
    st32(base, (R(5) + 8), R(3));
    st32(base, (R(5) + 0), R(7));
    st32(base, (R(6) + -304), R(5));
}

/* mfn_81844F10 (mfn_81844F10, 176 bytes) */
static void mj_mfn_81844F10_44f10(GM_CTX) {
    GM_FRAME(16); gptr f = gm_frame_sp;
    R(5) = R(3) & 0x80000000u;
    CR0(ctx, R(5));
    if ((CR_BIT(ctx, 2))) { goto L_81844F24; }
    { uint32_t a_ = R(4); R(4) = 0x0u - a_; ctx->xer_ca = 0x0u >= a_; }
    { uint64_t t_ = (uint64_t)(~R(3)) + (0) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
L_81844F24:;
    R(7) = R(3) |R(4);
    CR0(ctx, R(7));
    R(6) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_81844FAC; }
    R(7) = cntlzw(R(3));
    R(8) = cntlzw(R(4));
    R(9) = rotl32(R(7), 26) & 0xF8000000u;
    { int32_t v_ = (int32_t)R(9); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(9) = (v_ >> 31); }
    R(9) = R(9) &R(8);
    R(7) = R(7) + R(9);
    { uint32_t a_ = R(7); R(8) = 0x20u - a_; ctx->xer_ca = 0x20u >= a_; }
    { uint32_t a_ = R(7); R(9) = a_ + 0xFFFFFFE0u; ctx->xer_ca = R(9) < a_; }
    { uint32_t s_ = R(7) & 63; R(3) = s_ > 31 ? 0 : R(3) << s_; }
    { uint32_t s_ = R(8) & 63; R(10) = s_ > 31 ? 0 : R(4) >> s_; }
    R(3) = R(3) |R(10);
    { uint32_t s_ = R(9) & 63; R(10) = s_ > 31 ? 0 : R(4) << s_; }
    R(3) = R(3) |R(10);
    { uint32_t s_ = R(7) & 63; R(4) = s_ > 31 ? 0 : R(4) << s_; }
    R(6) = R(6) - R(7);
    R(7) = R(4) & 0x7FFu;
    cr_cmp_s(ctx, 0, (int32_t)R(7), 1024);
    R(6) = (R(6) + 1086);
    if ((CR_BIT(ctx, 0))) { goto L_81844F94; }
    if ((CR_BIT(ctx, 1))) { goto L_81844F88; }
    R(7) = R(4) & 0x800u;
    CR0(ctx, R(7));
    if ((CR_BIT(ctx, 2))) { goto L_81844F94; }
L_81844F88:;
    { uint32_t a_ = R(4); R(4) = a_ + 0x800u; ctx->xer_ca = R(4) < a_; }
    { uint64_t t_ = (uint64_t)(R(3)) + (0) + ctx->xer_ca; R(3) = t_; ctx->xer_ca = (t_ >> 32); }
    { uint64_t t_ = (uint64_t)(R(6)) + (0) + ctx->xer_ca; R(6) = t_; ctx->xer_ca = (t_ >> 32); }
L_81844F94:;
    R(4) = rotl32(R(4), 21) & 0xFFFFFFFFu;
    R(4) = (rotl32(R(3), 21) & 0xFFE00000u) | (R(4) & ~0xFFE00000u);
    R(3) = rotl32(R(3), 21) & 0xFFFFFu;
    R(6) = rotl32(R(6), 20) & 0xFFF00000u;
    R(3) = R(6) |R(3);
    R(3) = R(5) |R(3);
L_81844FAC:;
    st32(base, (f + 8), R(3));
    st32(base, (f + 12), R(4));
    { uint32_t ea_ = (f + 8); ctx->f[1].u = ld64(base, ea_); }
}

/* stack_chk_init (stack_chk_init, 12 bytes) */
static void mj_stack_chk_init_44fc0(GM_CTX) {
    R(4) = (0 + 0x81860000u);
    st32(base, (R(4) + -300), R(3));
}

/* ext_fn_8005B4A0 (ext_fn_8005B4A0, 8 bytes) */
static void mj_ext_fn_8005B4A0_45400(GM_CTX) {
    { uint32_t ea_ = (R(2) + -30312); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    GM_TAIL(0x8005B4A4u, 0); return;
}

/* ext__Z11DVDFastOpeniP9DVDHandle (ext__Z11DVDFastOpeniP9DVDHandle, 8 bytes) */
static void mj_ext__Z11DVDFastOpeniP9DVDHandle_45440(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    GM_TAIL(0x801CA994u, 0); return;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_MJ_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_MJ_COUNT)
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(mod_beginState_BattleIn__12daBossDemo_cFv, 4) { mj_mod_beginState_BattleIn__12daBossDemo_cF_00dfc(GM_PASS); }
E(mod_fn_80021AB0, 4) { mj_mod_fn_80021AB0_00ec0(GM_PASS); }
E(mod_fn_80021B30, 4) { mj_mod_fn_80021B30_00f48(GM_PASS); }
E(mfn_81800FF8, 4) { mj_mfn_81800FF8_00ff8(GM_PASS); }
E(mod_fn_80022810, 4) { mj_mod_fn_80022810_01148(GM_PASS); }
E(mod_fn_8002DAB0, 4) { mj_mod_fn_8002DAB0_01514(GM_PASS); }
E(mod_fn_8002F870, 4) { mj_mod_fn_8002F870_01594(GM_PASS); }
E(mfn_818016C4, 4) { mj_mfn_818016C4_016c4(GM_PASS); }
E(mod_fn_800389E0, 4) { mj_mod_fn_800389E0_016e4(GM_PASS); }
E(mod_fn_800396A0, 4) { mj_mod_fn_800396A0_01cb0(GM_PASS); }
E(mod_fn_8003B3E0, 4) { mj_mod_fn_8003B3E0_02020(GM_PASS); }
E(mod_fn_8003B830, 4) { mj_mod_fn_8003B830_02318(GM_PASS); }
E(mod_fn_800441E0, 4) { mj_mod_fn_800441E0_02600(GM_PASS); }
E(mod_fn_80052900, 4) { mj_mod_fn_80052900_02ef0(GM_PASS); }
E(mod_fn_8005E5D0, 4) { mj_mod_fn_8005E5D0_05624(GM_PASS); }
E(mfn_8180637C, 4) { mj_mfn_8180637C_0637c(GM_PASS); }
E(ctor_8180774C, 4) { mj_ctor_8180774C_0774c(GM_PASS); }
E(mod_fn_800651C0, 4) { mj_mod_fn_800651C0_077b0(GM_PASS); }
E(mod_fn_80065480, 4) { mj_mod_fn_80065480_07a78(GM_PASS); }
E(mod_fn_80065520, 4) { mj_mod_fn_80065520_07b10(GM_PASS); }
E(mod_getRemotePlayer__6dAudioFi, 4) { mj_mod_getRemotePlayer__6dAudioFi_07c9c(GM_PASS); }
E(mod_fn_80104050, 4) { mj_mod_fn_80104050_07cf0(GM_PASS); }
E(mod_fn_8006C0B0, 4) { mj_mod_fn_8006C0B0_07d44(GM_PASS); }
E(mod_fn_8006C1C0, 4) { mj_mod_fn_8006C1C0_07e2c(GM_PASS); }
E(mod_fn_800785E0, 4) { mj_mod_fn_800785E0_0843c(GM_PASS); }
E(mod_fn_8007BEF0, 4) { mj_mod_fn_8007BEF0_085e8(GM_PASS); }
E(mod_fn_8007CA90, 4) { mj_mod_fn_8007CA90_08eec(GM_PASS); }
E(mod_fn_80083490, 4) { mj_mod_fn_80083490_091cc(GM_PASS); }
E(mod_fn_80087F40, 4) { mj_mod_fn_80087F40_091f0(GM_PASS); }
E(mod_fn_800883E0, 4) { mj_mod_fn_800883E0_093cc(GM_PASS); }
E(mod_fn_8008EEC0, 4) { mj_mod_fn_8008EEC0_099a8(GM_PASS); }
E(mod_beforeExecute__5dEn_cFv, 4) { mj_mod_beforeExecute__5dEn_cFv_099b0(GM_PASS); }
E(mod_collisionCallback__5dEn_cFP13ActivePhysicsP13ActivePhysics, 4) { mj_mod_collisionCallback__5dEn_cFP13ActiveP_09bac(GM_PASS); }
E(mfn_81809F98, 4) { mj_mfn_81809F98_09f98(GM_PASS); }
E(mfn_81809FFC, 4) { mj_mfn_81809FFC_09ffc(GM_PASS); }
E(mfn_8180A01C, 4) { mj_mfn_8180A01C_0a01c(GM_PASS); }
E(mfn_8180A038, 4) { mj_mfn_8180A038_0a038(GM_PASS); }
E(mfn_8180A08C, 4) { mj_mfn_8180A08C_0a08c(GM_PASS); }
E(mod_fn_80098B60, 4) { mj_mod_fn_80098B60_0a164(GM_PASS); }
E(mfn_8180AB68, 4) { mj_mfn_8180AB68_0ab68(GM_PASS); }
E(mod__Z32CheckIfContinueShouldBeActivatedv, 4) { mj_mod__Z32CheckIfContinueShouldBeActivated_0b094(GM_PASS); }
E(mfn_8180B1E8, 4) { mj_mfn_8180B1E8_0b1e8(GM_PASS); }
E(ctor_8180B3F0, 4) { mj_ctor_8180B3F0_0b3f0(GM_PASS); }
E(ctor_8180B470, 4) { mj_ctor_8180B470_0b470(GM_PASS); }
E(ctor_8180B514, 4) { mj_ctor_8180B514_0b514(GM_PASS); }
E(ctor_8180B564, 4) { mj_ctor_8180B564_0b564(GM_PASS); }
E(mfn_8180BF3C, 4) { mj_mfn_8180BF3C_0bf3c(GM_PASS); }
E(ctor_8180C414, 4) { mj_ctor_8180C414_0c414(GM_PASS); }
E(mfn_8180C440, 4) { mj_mfn_8180C440_0c440(GM_PASS); }
E(mfn_8180C488, 4) { mj_mfn_8180C488_0c488(GM_PASS); }
E(mfn_8180C48C, 4) { mj_mfn_8180C48C_0c48c(GM_PASS); }
E(mfn_8180C4EC, 4) { mj_mfn_8180C4EC_0c4ec(GM_PASS); }
E(mfn_8180C540, 4) { mj_mfn_8180C540_0c540(GM_PASS); }
E(mfn_8180C614, 4) { mj_mfn_8180C614_0c614(GM_PASS); }
E(mfn_8180C6C8, 4) { mj_mfn_8180C6C8_0c6c8(GM_PASS); }
E(mfn_8180C904, 4) { mj_mfn_8180C904_0c904(GM_PASS); }
E(mfn_8180CB80, 4) { mj_mfn_8180CB80_0cb80(GM_PASS); }
E(mod_fn_800CD1A0, 4) { mj_mod_fn_800CD1A0_0cf04(GM_PASS); }
E(mfn_8180D868, 4) { mj_mfn_8180D868_0d868(GM_PASS); }
E(mfn_8180D8B4, 4) { mj_mfn_8180D8B4_0d8b4(GM_PASS); }
E(mfn_8180DC20, 4) { mj_mfn_8180DC20_0dc20(GM_PASS); }
E(mfn_8180DCFC, 4) { mj_mfn_8180DCFC_0dcfc(GM_PASS); }
E(mfn_8180DF80, 4) { mj_mfn_8180DF80_0df80(GM_PASS); }
E(mfn_8180E5E0, 4) { mj_mfn_8180E5E0_0e5e0(GM_PASS); }
E(mfn_8180E6C0, 4) { mj_mfn_8180E6C0_0e6c0(GM_PASS); }
E(mfn_8180F330, 4) { mj_mfn_8180F330_0f330(GM_PASS); }
E(mfn_8180F39C, 4) { mj_mfn_8180F39C_0f39c(GM_PASS); }
E(mfn_8180F548, 4) { mj_mfn_8180F548_0f548(GM_PASS); }
E(mfn_8180F58C, 4) { mj_mfn_8180F58C_0f58c(GM_PASS); }
E(mfn_818119AC, 4) { mj_mfn_818119AC_119ac(GM_PASS); }
E(mfn_81812100, 4) { mj_mfn_81812100_12100(GM_PASS); }
E(mod_fn_800D0270, 4) { mj_mod_fn_800D0270_12310(GM_PASS); }
E(mod_fn_800D2390, 4) { mj_mod_fn_800D2390_12438(GM_PASS); }
E(mod_fn_800D2610, 4) { mj_mod_fn_800D2610_1245c(GM_PASS); }
E(mfn_81812734, 4) { mj_mfn_81812734_12734(GM_PASS); }
E(mfn_8181273C, 4) { mj_mfn_8181273C_1273c(GM_PASS); }
E(mod_fn_800DC570, 4) { mj_mod_fn_800DC570_128f0(GM_PASS); }
E(mod_execute__13dRemoconMng_cFv, 4) { mj_mod_execute__13dRemoconMng_cFv_12ba4(GM_PASS); }
E(mfn_81812E2C, 4) { mj_mfn_81812E2C_12e2c(GM_PASS); }
E(mod_fn_800DC6F0, 4) { mj_mod_fn_800DC6F0_12fc8(GM_PASS); }
E(mod_fn_800DC820, 4) { mj_mod_fn_800DC820_13150(GM_PASS); }
E(mod_fn_800DC8E0, 4) { mj_mod_fn_800DC8E0_132c4(GM_PASS); }
E(mfn_818133E8, 4) { mj_mfn_818133E8_133e8(GM_PASS); }
E(mod_fn_800DCA00, 4) { mj_mod_fn_800DCA00_1354c(GM_PASS); }
E(mod_fn_800DCA20, 4) { mj_mod_fn_800DCA20_13558(GM_PASS); }
E(mod_fn_800DCB50, 4) { mj_mod_fn_800DCB50_13578(GM_PASS); }
E(mod_fn_800DCB70, 4) { mj_mod_fn_800DCB70_13584(GM_PASS); }
E(mfn_81813960, 4) { mj_mfn_81813960_13960(GM_PASS); }
E(mfn_81813A0C, 4) { mj_mfn_81813A0C_13a0c(GM_PASS); }
E(mfn_81813AB4, 4) { mj_mfn_81813AB4_13ab4(GM_PASS); }
E(mfn_81813B04, 4) { mj_mfn_81813B04_13b04(GM_PASS); }
E(mod_fn_800E3AB0, 4) { mj_mod_fn_800E3AB0_145a4(GM_PASS); }
E(find_code_region, 4) { mj_find_code_region_145d4(GM_PASS); }
E(ctor_8181468C, 4) { mj_ctor_8181468C_1468c(GM_PASS); }
E(mfn_818146B4, 4) { mj_mfn_818146B4_146b4(GM_PASS); }
E(mfn_81814700, 4) { mj_mfn_81814700_14700(GM_PASS); }
E(mod_fn_800FE400, 4) { mj_mod_fn_800FE400_14708(GM_PASS); }
E(mfn_81814868, 4) { mj_mfn_81814868_14868(GM_PASS); }
E(mod_fn_2_1C1880, 4) { mj_mod_fn_2_1C1880_14904(GM_PASS); }
E(mod_dProf_getName__FUs, 4) { mj_mod_dProf_getName__FUs_14eac(GM_PASS); }
E(ctor_8181505C, 4) { mj_ctor_8181505C_1505c(GM_PASS); }
E(mod_fn_2_510, 4) { mj_mod_fn_2_510_1723c(GM_PASS); }
E(mod_fn_2_2370, 4) { mj_mod_fn_2_2370_176cc(GM_PASS); }
E(mfn_81817814, 4) { mj_mfn_81817814_17814(GM_PASS); }
E(mfn_81817838, 4) { mj_mfn_81817838_17838(GM_PASS); }
E(mod_fn_2_2920, 4) { mj_mod_fn_2_2920_17af0(GM_PASS); }
E(mfn_81817CDC, 4) { mj_mfn_81817CDC_17cdc(GM_PASS); }
E(mod_fn_2_2B30, 4) { mj_mod_fn_2_2B30_17d74(GM_PASS); }
E(mod_fn_2_3770, 4) { mj_mod_fn_2_3770_18110(GM_PASS); }
E(mod_fn_2_3920, 4) { mj_mod_fn_2_3920_18208(GM_PASS); }
E(mod_fn_2_3AB0, 4) { mj_mod_fn_2_3AB0_182e4(GM_PASS); }
E(mod_fn_2_3B00, 4) { mj_mod_fn_2_3B00_18328(GM_PASS); }
E(mod_fn_2_3B40, 4) { mj_mod_fn_2_3B40_1835c(GM_PASS); }
E(mod_fn_2_3C60, 4) { mj_mod_fn_2_3C60_1848c(GM_PASS); }
E(mod_fn_2_52E0, 4) { mj_mod_fn_2_52E0_185d8(GM_PASS); }
E(mod_fn_2_56C0, 4) { mj_mod_fn_2_56C0_18610(GM_PASS); }
E(mod_fn_2_60D0, 4) { mj_mod_fn_2_60D0_189f4(GM_PASS); }
E(mod_fn_2_9E70, 4) { mj_mod_fn_2_9E70_18a30(GM_PASS); }
E(mod_fn_2_D2A0, 4) { mj_mod_fn_2_D2A0_1960c(GM_PASS); }
E(mod_fn_2_31EC0, 4) { mj_mod_fn_2_31EC0_1bafc(GM_PASS); }
E(mod_fn_2_31EF0, 4) { mj_mod_fn_2_31EF0_1bb34(GM_PASS); }
E(mod_fn_2_32160, 4) { mj_mod_fn_2_32160_1bc64(GM_PASS); }
E(mod_fn_2_32220, 4) { mj_mod_fn_2_32220_1bccc(GM_PASS); }
E(mod_fn_2_32560, 4) { mj_mod_fn_2_32560_1c000(GM_PASS); }
E(mod_fn_2_328F0, 4) { mj_mod_fn_2_328F0_1c278(GM_PASS); }
E(mod_fn_2_32A00, 4) { mj_mod_fn_2_32A00_1c358(GM_PASS); }
E(mod_fn_2_32CD0, 4) { mj_mod_fn_2_32CD0_1c510(GM_PASS); }
E(mod_fn_2_33050, 4) { mj_mod_fn_2_33050_1c758(GM_PASS); }
E(mod_fn_2_33100, 4) { mj_mod_fn_2_33100_1c7c4(GM_PASS); }
E(mod_fn_2_33260, 4) { mj_mod_fn_2_33260_1c8f0(GM_PASS); }
E(mod_fn_2_332E0, 4) { mj_mod_fn_2_332E0_1c980(GM_PASS); }
E(mod_fn_2_33480, 4) { mj_mod_fn_2_33480_1cb30(GM_PASS); }
E(mod_fn_2_33630, 4) { mj_mod_fn_2_33630_1ccf4(GM_PASS); }
E(mod_fn_2_33640, 4) { mj_mod_fn_2_33640_1cd04(GM_PASS); }
E(mfn_8181CFD8, 4) { mj_mfn_8181CFD8_1cfd8(GM_PASS); }
E(mod_fn_2_33A00, 4) { mj_mod_fn_2_33A00_1cffc(GM_PASS); }
E(mod_fn_2_33A30, 4) { mj_mod_fn_2_33A30_1d020(GM_PASS); }
E(mod_fn_2_33B60, 4) { mj_mod_fn_2_33B60_1d11c(GM_PASS); }
E(mod_fn_2_33BD0, 4) { mj_mod_fn_2_33BD0_1d188(GM_PASS); }
E(mod_fn_2_33C10, 4) { mj_mod_fn_2_33C10_1d1ac(GM_PASS); }
E(mod_fn_2_33D50, 4) { mj_mod_fn_2_33D50_1d2c8(GM_PASS); }
E(mod_fn_2_33D60, 4) { mj_mod_fn_2_33D60_1d2d4(GM_PASS); }
E(mod_fn_2_340C0, 4) { mj_mod_fn_2_340C0_1d5e0(GM_PASS); }
E(mod_fn_2_340F0, 4) { mj_mod_fn_2_340F0_1d60c(GM_PASS); }
E(mod_fn_2_34220, 4) { mj_mod_fn_2_34220_1d6f4(GM_PASS); }
E(mod_fn_2_342E0, 4) { mj_mod_fn_2_342E0_1d798(GM_PASS); }
E(mod_fn_2_34340, 4) { mj_mod_fn_2_34340_1d7fc(GM_PASS); }
E(mod_fn_2_343D0, 4) { mj_mod_fn_2_343D0_1d878(GM_PASS); }
E(mod_fn_2_345A0, 4) { mj_mod_fn_2_345A0_1da2c(GM_PASS); }
E(mod_fn_2_34630, 4) { mj_mod_fn_2_34630_1daa8(GM_PASS); }
E(mod_fn_2_34710, 4) { mj_mod_fn_2_34710_1db64(GM_PASS); }
E(mod_fn_2_34910, 4) { mj_mod_fn_2_34910_1dd7c(GM_PASS); }
E(mfn_8181DE64, 4) { mj_mfn_8181DE64_1de64(GM_PASS); }
E(mfn_8181DF18, 4) { mj_mfn_8181DF18_1df18(GM_PASS); }
E(mfn_8181DF74, 4) { mj_mfn_8181DF74_1df74(GM_PASS); }
E(mfn_8181DFC0, 4) { mj_mfn_8181DFC0_1dfc0(GM_PASS); }
E(mfn_8181E014, 4) { mj_mfn_8181E014_1e014(GM_PASS); }
E(mfn_8181E068, 4) { mj_mfn_8181E068_1e068(GM_PASS); }
E(mod_fn_2_3E670, 4) { mj_mod_fn_2_3E670_1e1f4(GM_PASS); }
E(mod_fn_2_74F70, 4) { mj_mod_fn_2_74F70_23708(GM_PASS); }
E(mod_fn_2_C2EF0, 4) { mj_mod_fn_2_C2EF0_23c84(GM_PASS); }
E(mod_fn_2_C2F40, 4) { mj_mod_fn_2_C2F40_23cd8(GM_PASS); }
E(mod_fn_2_C2F80, 4) { mj_mod_fn_2_C2F80_23d00(GM_PASS); }
E(mfn_81824050, 4) { mj_mfn_81824050_24050(GM_PASS); }
E(mfn_81824194, 4) { mj_mfn_81824194_24194(GM_PASS); }
E(mod_fn_2_CE880, 4) { mj_mod_fn_2_CE880_24198(GM_PASS); }
E(mfn_818241D0, 4) { mj_mfn_818241D0_241d0(GM_PASS); }
E(mod_fn_2_CFBE0, 4) { mj_mod_fn_2_CFBE0_24318(GM_PASS); }
E(mod_fn_2_100ED0, 4) { mj_mod_fn_2_100ED0_2661c(GM_PASS); }
E(mod_fn_2_101120, 4) { mj_mod_fn_2_101120_26660(GM_PASS); }
E(mod_fn_2_101130, 4) { mj_mod_fn_2_101130_26668(GM_PASS); }
E(mod_fn_2_101270, 4) { mj_mod_fn_2_101270_26764(GM_PASS); }
E(mod_fn_2_101410, 4) { mj_mod_fn_2_101410_26904(GM_PASS); }
E(mod_fn_2_101700, 4) { mj_mod_fn_2_101700_26954(GM_PASS); }
E(mod_fn_2_103920, 4) { mj_mod_fn_2_103920_26b30(GM_PASS); }
E(mod_fn_2_103CA0, 4) { mj_mod_fn_2_103CA0_26c44(GM_PASS); }
E(mfn_81826EB8, 4) { mj_mfn_81826EB8_26eb8(GM_PASS); }
E(mod_fn_2_108940, 4) { mj_mod_fn_2_108940_26ec0(GM_PASS); }
E(mod_fn_2_108EE0, 4) { mj_mod_fn_2_108EE0_26fbc(GM_PASS); }
E(mod_fn_2_157EF0, 4) { mj_mod_fn_2_157EF0_28600(GM_PASS); }
E(mod_fn_2_1581F0, 4) { mj_mod_fn_2_1581F0_28748(GM_PASS); }
E(ctor_81829008, 4) { mj_ctor_81829008_29008(GM_PASS); }
E(mod_fn_2_1A3BE0, 4) { mj_mod_fn_2_1A3BE0_29bd0(GM_PASS); }
E(mod_fn_2_1A3EE0, 4) { mj_mod_fn_2_1A3EE0_29ddc(GM_PASS); }
E(mod_fn_2_1A4330, 4) { mj_mod_fn_2_1A4330_29e50(GM_PASS); }
E(mfn_8182AA74, 4) { mj_mfn_8182AA74_2aa74(GM_PASS); }
E(mod_fn_2_1B14B0, 4) { mj_mod_fn_2_1B14B0_2aae8(GM_PASS); }
E(mod_fn_2_1B1830, 4) { mj_mod_fn_2_1B1830_2ab30(GM_PASS); }
E(mod_fn_2_1B21A0, 4) { mj_mod_fn_2_1B21A0_2ab98(GM_PASS); }
E(mod_fn_2_1B2DB0, 4) { mj_mod_fn_2_1B2DB0_2aedc(GM_PASS); }
E(mod_fn_2_1B5170, 4) { mj_mod_fn_2_1B5170_2afa4(GM_PASS); }
E(mod_fn_4_4F2B0, 4) { mj_mod_fn_4_4F2B0_2bf34(GM_PASS); }
E(mfn_8182C0AC, 4) { mj_mfn_8182C0AC_2c0ac(GM_PASS); }
E(mod_fn_4_4F630, 4) { mj_mod_fn_4_4F630_2c14c(GM_PASS); }
E(mod_fn_4_4FE20, 4) { mj_mod_fn_4_4FE20_2c5a0(GM_PASS); }
E(mod_fn_80111850, 4) { mj_mod_fn_80111850_2ca00(GM_PASS); }
E(mod_fn_801133B0, 4) { mj_mod_fn_801133B0_2d144(GM_PASS); }
E(mod_fn_8011A570, 4) { mj_mod_fn_8011A570_2d244(GM_PASS); }
E(mod_fn_80123330, 4) { mj_mod_fn_80123330_2d2c0(GM_PASS); }
E(mod_fn_80125F10, 4) { mj_mod_fn_80125F10_2d570(GM_PASS); }
E(mod_fn_80125F70, 4) { mj_mod_fn_80125F70_2d598(GM_PASS); }
E(mfn_8182DD3C, 4) { mj_mfn_8182DD3C_2dd3c(GM_PASS); }
E(mod_dAcPy_vf3F8, 4) { mj_mod_dAcPy_vf3F8_2ebe4(GM_PASS); }
E(mod_fn_80150CD0, 4) { mj_mod_fn_80150CD0_2ecec(GM_PASS); }
E(mfn_8182EDF0, 4) { mj_mfn_8182EDF0_2edf0(GM_PASS); }
E(mod_fn_80154F60, 4) { mj_mod_fn_80154F60_2ef38(GM_PASS); }
E(mod_fn_80156820, 4) { mj_mod_fn_80156820_307c0(GM_PASS); }
E(mod_fn_801568D0, 4) { mj_mod_fn_801568D0_30828(GM_PASS); }
E(mod_fn_80156C30, 4) { mj_mod_fn_80156C30_309e4(GM_PASS); }
E(mod_fn_80156EA0, 4) { mj_mod_fn_80156EA0_310fc(GM_PASS); }
E(mod_fn_801576E0, 4) { mj_mod_fn_801576E0_314e4(GM_PASS); }
E(mfn_81832A24, 4) { mj_mfn_81832A24_32a24(GM_PASS); }
E(mfn_81833024, 4) { mj_mfn_81833024_33024(GM_PASS); }
E(mfn_818330D8, 4) { mj_mfn_818330D8_330d8(GM_PASS); }
E(mfn_81833180, 4) { mj_mfn_81833180_33180(GM_PASS); }
E(mfn_818331D4, 4) { mj_mfn_818331D4_331d4(GM_PASS); }
E(mod_fn_8015D710, 4) { mj_mod_fn_8015D710_3327c(GM_PASS); }
E(mod_fn_3_1C070, 4) { mj_mod_fn_3_1C070_339f4(GM_PASS); }
E(mod_fn_3_1C800, 4) { mj_mod_fn_3_1C800_33e58(GM_PASS); }
E(mod_fn_3_1D040, 4) { mj_mod_fn_3_1D040_341d0(GM_PASS); }
E(mod_fn_3_2D390, 4) { mj_mod_fn_3_2D390_34870(GM_PASS); }
E(mod_fn_3_85560, 4) { mj_mod_fn_3_85560_35aac(GM_PASS); }
E(mod_fn_3_88390, 4) { mj_mod_fn_3_88390_35dd8(GM_PASS); }
E(mod_fn_3_968D0, 4) { mj_mod_fn_3_968D0_361ec(GM_PASS); }
E(mod_getID__12dStateBase_cFv, 4) { mj_mod_getID__12dStateBase_cFv_383a8(GM_PASS); }
E(ctor_818383D0, 4) { mj_ctor_818383D0_383d0(GM_PASS); }
E(mfn_81838720, 4) { mj_mfn_81838720_38720(GM_PASS); }
E(mfn_81838BF0, 4) { mj_mfn_81838BF0_38bf0(GM_PASS); }
E(mfn_81838C84, 4) { mj_mfn_81838C84_38c84(GM_PASS); }
E(mfn_81838DBC, 4) { mj_mfn_81838DBC_38dbc(GM_PASS); }
E(mod_fn_8016B2A0, 4) { mj_mod_fn_8016B2A0_39ffc(GM_PASS); }
E(mfn_8183A2F8, 4) { mj_mfn_8183A2F8_3a2f8(GM_PASS); }
E(mod_fn_8016BC30, 4) { mj_mod_fn_8016BC30_3a3bc(GM_PASS); }
E(mfn_8183A4A4, 4) { mj_mfn_8183A4A4_3a4a4(GM_PASS); }
E(mod_create__16mDvd_toMainRam_cFPCcUcPQ23EGG4Heap, 4) { mj_mod_create__16mDvd_toMainRam_cFPCcUcPQ23_3a518(GM_PASS); }
E(mfn_8183A558, 4) { mj_mfn_8183A558_3a558(GM_PASS); }
E(ctor_8183A600, 4) { mj_ctor_8183A600_3a600(GM_PASS); }
E(mfn_8183A720, 4) { mj_mfn_8183A720_3a720(GM_PASS); }
E(mfn_8183A78C, 4) { mj_mfn_8183A78C_3a78c(GM_PASS); }
E(mfn_8183A894, 4) { mj_mfn_8183A894_3a894(GM_PASS); }
E(mfn_8183AA6C, 4) { mj_mfn_8183AA6C_3aa6c(GM_PASS); }
E(mfn_8183AE28, 4) { mj_mfn_8183AE28_3ae28(GM_PASS); }
E(mod_create__4mPadFv, 4) { mj_mod_create__4mPadFv_3ba58(GM_PASS); }
E(mod_fn_8016F550, 4) { mj_mod_fn_8016F550_3bb38(GM_PASS); }
E(mod_beginPad__4mPadFv, 4) { mj_mod_beginPad__4mPadFv_3bbb4(GM_PASS); }
E(mod_endPad__4mPadFv, 4) { mj_mod_endPad__4mPadFv_3c03c(GM_PASS); }
E(mod_fn_8016F460, 4) { mj_mod_fn_8016F460_3c0d8(GM_PASS); }
E(mfn_8183C114, 4) { mj_mfn_8183C114_3c114(GM_PASS); }
E(ctor_8183C1C4, 4) { mj_ctor_8183C1C4_3c1c4(GM_PASS); }
E(mfn_8183C5AC, 4) { mj_mfn_8183C5AC_3c5ac(GM_PASS); }
E(mfn_8183C768, 4) { mj_mfn_8183C768_3c768(GM_PASS); }
E(mfn_8183C7C8, 4) { mj_mfn_8183C7C8_3c7c8(GM_PASS); }
E(mod_fn_80198BB0, 4) { mj_mod_fn_80198BB0_3c828(GM_PASS); }
E(mfn_8183CB74, 4) { mj_mfn_8183CB74_3cb74(GM_PASS); }
E(ctor_8183CEC4, 4) { mj_ctor_8183CEC4_3cec4(GM_PASS); }
E(ctor_8183D078, 4) { mj_ctor_8183D078_3d078(GM_PASS); }
E(mfn_8183EA10, 4) { mj_mfn_8183EA10_3ea10(GM_PASS); }
E(ctor_8183F498, 4) { mj_ctor_8183F498_3f498(GM_PASS); }
E(mfn_818409A4, 4) { mj_mfn_818409A4_409a4(GM_PASS); }
E(mfn_81840AB0, 4) { mj_mfn_81840AB0_40ab0(GM_PASS); }
E(mfn_81840B68, 4) { mj_mfn_81840B68_40b68(GM_PASS); }
E(mfn_81840BE8, 4) { mj_mfn_81840BE8_40be8(GM_PASS); }
E(mfn_81840C54, 4) { mj_mfn_81840C54_40c54(GM_PASS); }
E(preinit, 4) { mj_preinit_40f24(GM_PASS); }
E(mfn_81840F88, 4) { mj_mfn_81840F88_40f88(GM_PASS); }
E(mfn_81840FD0, 4) { mj_mfn_81840FD0_40fd0(GM_PASS); }
E(mfn_81841364, 4) { mj_mfn_81841364_41364(GM_PASS); }
E(mfn_81841460, 4) { mj_mfn_81841460_41460(GM_PASS); }
E(mod__Z24DVDConvertPathToEntrynumPKc, 4) { mj_mod__Z24DVDConvertPathToEntrynumPKc_414e4(GM_PASS); }
E(mod__Z11DVDFastOpeniP9DVDHandle, 4) { mj_mod__Z11DVDFastOpeniP9DVDHandle_41554(GM_PASS); }
E(mfn_81841640, 4) { mj_mfn_81841640_41640(GM_PASS); }
E(mfn_818417C4, 4) { mj_mfn_818417C4_417c4(GM_PASS); }
E(mfn_8184182C, 4) { mj_mfn_8184182C_4182c(GM_PASS); }
E(mfn_81841838, 4) { mj_mfn_81841838_41838(GM_PASS); }
E(mfn_81841D6C, 4) { mj_mfn_81841D6C_41d6c(GM_PASS); }
E(mfn_81841E14, 4) { mj_mfn_81841E14_41e14(GM_PASS); }
E(mfn_818423A0, 4) { mj_mfn_818423A0_423a0(GM_PASS); }
E(mfn_818425A0, 4) { mj_mfn_818425A0_425a0(GM_PASS); }
E(mfn_81842714, 4) { mj_mfn_81842714_42714(GM_PASS); }
E(mfn_81842F7C, 4) { mj_mfn_81842F7C_42f7c(GM_PASS); }
E(mfn_81843020, 4) { mj_mfn_81843020_43020(GM_PASS); }
E(mod_fn_802695E0, 4) { mj_mod_fn_802695E0_43038(GM_PASS); }
E(mod_fn_802695F0, 4) { mj_mod_fn_802695F0_43054(GM_PASS); }
E(mfn_81843070, 4) { mj_mfn_81843070_43070(GM_PASS); }
E(mod_fn_80275EE0, 4) { mj_mod_fn_80275EE0_4311c(GM_PASS); }
E(mod_fn_80275FD0, 4) { mj_mod_fn_80275FD0_43158(GM_PASS); }
E(mod_fn_80276210, 4) { mj_mod_fn_80276210_431a4(GM_PASS); }
E(mod_fn_802764F0, 4) { mj_mod_fn_802764F0_43218(GM_PASS); }
E(mfn_8184326C, 4) { mj_mfn_8184326C_4326c(GM_PASS); }
E(mod___nw__FUlPQ23EGG4Heapi, 4) { mj_mod___nw__FUlPQ23EGG4Heapi_43378(GM_PASS); }
E(mod___nwa__FUl, 4) { mj_mod___nwa__FUl_433c8(GM_PASS); }
E(mod_fn_802B9260, 4) { mj_mod_fn_802B9260_43414(GM_PASS); }
E(mod___nwa__FUlPQ23EGG4Heapi, 4) { mj_mod___nwa__FUlPQ23EGG4Heapi_4345c(GM_PASS); }
E(mod_fn_802BC900, 4) { mj_mod_fn_802BC900_437a4(GM_PASS); }
E(mod_fn_802BC910, 4) { mj_mod_fn_802BC910_43840(GM_PASS); }
E(mod_fn_802BC920, 4) { mj_mod_fn_802BC920_438dc(GM_PASS); }
E(mod_startPatternRumble__Q23EGG14CoreControllerFPCcib, 4) { mj_mod_startPatternRumble__Q23EGG14CoreCont_439a4(GM_PASS); }
E(mod_fn_802BC9A0, 4) { mj_mod_fn_802BC9A0_43a40(GM_PASS); }
E(mod_fn_802BC9C0, 4) { mj_mod_fn_802BC9C0_43adc(GM_PASS); }
E(mod_fn_802BCDE0, 4) { mj_mod_fn_802BCDE0_43b78(GM_PASS); }
E(mfn_81844184, 4) { mj_mfn_81844184_44184(GM_PASS); }
E(mfn_81844244, 4) { mj_mfn_81844244_44244(GM_PASS); }
E(mfn_81844664, 4) { mj_mfn_81844664_44664(GM_PASS); }
E(mfn_818446D4, 4) { mj_mfn_818446D4_446d4(GM_PASS); }
E(mfn_818448D8, 4) { mj_mfn_818448D8_448d8(GM_PASS); }
E(mfn_8184499C, 4) { mj_mfn_8184499C_4499c(GM_PASS); }
E(mfn_81844A50, 4) { mj_mfn_81844A50_44a50(GM_PASS); }
E(mfn_81844EF4, 4) { mj_mfn_81844EF4_44ef4(GM_PASS); }
E(mfn_81844F10, 4) { mj_mfn_81844F10_44f10(GM_PASS); }
E(stack_chk_init, 4) { mj_stack_chk_init_44fc0(GM_PASS); }
E(ext_fn_8005B4A0, 4) { mj_ext_fn_8005B4A0_45400(GM_PASS); }
E(ext__Z11DVDFastOpeniP9DVDHandle, 4) { mj_ext__Z11DVDFastOpeniP9DVDHandle_45440(GM_PASS); }
