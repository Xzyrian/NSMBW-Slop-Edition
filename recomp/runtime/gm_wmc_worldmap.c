/* gm_wmc_worldmap.c - instance 2 (track B): the world map and the scene classes in the DOL
 * (E2 0x800F32F0-0x80106DF0: dWmConnect_c, dWmLib, dWmViewClip_c, daWmMap_c, daWmPlayer_c,
 * dCsSeqMng_c, dScStage_c, dScWMap_c, dWmBgmSync_c, dWmEffectManager_c, dWmSeManager_c ...).
 * Transliterated by tools/gm_conv.py from the recompiled bodies; only functions the A/B inputs
 * reach are on, the gate is the strict A/B (against the previous build and the build with no
 * natives). Functions another runtime file defines or calls by symbol are left to their owners.
 * Names are owed (wm_m_<addr>). Flags: -DGM_WMC_COUNT / -DGM_WMC_VERIFY. */

#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d

/* GetPointFromIndex__12dWmConnect_cFi (GetPointFromIndex__12dWmConnect_cFi, 64 bytes) */
static void wm_GetPointFromIndex__12dWmConnect_cFi_f32f0(GM_CTX) {
    R(0) = (0 + 192);
    R(5) = R(3) |R(3);
    R(6) = (0 + 0);
    ctx->ctr = R(0);
L_800F3300:;
    R(0) = ld32(base, (R(5) + 80));
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800F331C; }
    R(0) = ((int32_t)R(6) * 84);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 4);
    return;
L_800F331C:;
    R(5) = (R(5) + 84);
    R(6) = (R(6) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800F3300; }
    R(3) = (0 + 0);
}

/* fn_800F3330 (fn_800F3330, 140 bytes) */
static void wm_m_f3330(GM_CTX) {
    GM_FN(0x800F3330); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(29) = R(5) |R(5);
    GM_CALLV(0x800F3354u, 0x800F32F0u, 0);
    R(30) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800F3364u, 0x800F32F0u, 0);
    R(31) = R(3) |R(3);
    R(29) = (0 + 0);
L_800F336C:;
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800F3378u, 0x800F33C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F3390; }
    cr_cmp_u(ctx, 0, R(3), R(31));
    if ((!CR_BIT(ctx, 2))) { goto L_800F3390; }
    R(3) = R(29) |R(29);
    goto L_800F33A0;
L_800F3390:;
    R(29) = (R(29) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 6);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F336C; }
    R(3) = (0 + 6);
L_800F33A0:;
    R(0) = lr;
}

/* fn_800F33C0 (fn_800F33C0, 16 bytes) */
static void wm_m_f33c0(GM_CTX) {
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(0);
    R(3) = ld32(base, (R(3) + 24));
}

/* fn_800F33D0 (fn_800F33D0, 112 bytes) */
static void wm_m_f33d0(GM_CTX) {
    GM_FN(0x800F33D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24880); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -17216);
    { uint32_t ea_ = (R(2) + -24876); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x800F0000u);
    { uint32_t ea_ = (R(2) + -24872); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 13376);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15552);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800F3428u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21840), R(0));
    R(0) = lr;
}

/* fn_800F3460 (fn_800F3460, 148 bytes) */
static void wm_m_f3460(GM_CTX) {
    R(5) = ld8(base, (R(4) + 0));
    R(7) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(5), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3484; }
    { uint32_t ea_ = R(4) + 1; R(5) = ld8(base, ea_); R(4) = ea_; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3484; }
    R(3) = (0 + 0);
    return;
L_800F3484:;
    R(0) = (int8_t)R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3498; }
    R(3) = (0 + 0);
    return;
L_800F3498:;
    R(5) = R(3) |R(3);
    R(0) = R(0) | 0x0u;
L_800F34A0:;
    R(6) = ld8(base, (R(4) + 0));
    R(0) = (int8_t)R(6);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F34CC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((CR_BIT(ctx, 2))) { goto L_800F34CC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 13);
    if ((!CR_BIT(ctx, 2))) { goto L_800F34D8; }
    R(0) = ld8(base, (R(4) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((!CR_BIT(ctx, 2))) { goto L_800F34D8; }
L_800F34CC:;
    R(0) = (0 + 0);
    st8(base, (R(3) + R(7)), R(0));
    goto L_800F34EC;
L_800F34D8:;
    st8(base, (R(5) + 0), R(6));
    R(7) = (R(7) + 1);
    R(5) = (R(5) + 1);
    R(4) = (R(4) + 1);
    GM_LOOP(); goto L_800F34A0;
L_800F34EC:;
    R(3) = R(7) |R(7);
}

/* fn_800F3500 (fn_800F3500, 152 bytes) */
static void wm_m_f3500(GM_CTX) {
    GM_FN(0x800F3500); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(27) = R(3) |R(3);
    R(28) = R(4) |R(4);
    if ((CR_BIT(ctx, 2))) { goto L_800F357C; }
    R(4) = (0 + 0x80320000u);
    R(30) = (R(3) + 0x10000u);
    R(4) = (R(4) + -16864);
    st32(base, (R(3) + 0), R(4));
    R(31) = R(27) |R(27);
    R(29) = (0 + 0);
    R(30) = (R(30) + 24344);
L_800F3540:;
    R(3) = (R(31) + 0x10000u);
    R(0) = ld32(base, (R(3) + 24356));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F3558; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x800F3558u, 0x800F5A80u, 0);
L_800F3558:;
    R(29) = (R(29) + 1);
    R(30) = (R(30) + 24);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 64);
    R(31) = (R(31) + 24);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F3540; }
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800F357C; }
    R(3) = R(27) |R(27);
    GM_CALLV(0x800F357Cu, 0x802B9280u, 0);
L_800F357C:;
    R(11) = (f + 32);
    R(3) = R(27) |R(27);
    R(0) = lr;
}

/* fn_800F35A0 (fn_800F35A0, 60 bytes) */
static void wm_m_f35a0(GM_CTX) {
    GM_FN(0x800F35A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    st32(base, (R(3) + 4), R(4));
    st32(base, (R(3) + 8), R(5));
    GM_CALLV(0x800F35C0u, 0x800F35E0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800F35C8u, 0x800F39D0u, 0);
    R(0) = lr;
}

/* fn_800F35E0 (fn_800F35E0, 996 bytes) */
static void wm_m_f35e0(GM_CTX) {
    R(4) = (0 + 0);
    st32(base, (R(3) + 12), R(4));
    R(5) = R(3) |R(3);
    R(7) = (0 + 0);
    st32(base, (R(3) + 16), R(4));
    R(0) = (0 + 32);
    st32(base, (R(3) + 20), R(4));
L_800F35FC:;
    st8(base, (R(5) + 24), R(4));
    R(6) = R(5) |R(5);
    R(8) = (0 + 0);
    st8(base, (R(5) + 25), R(4));
    st8(base, (R(5) + 26), R(4));
    st8(base, (R(5) + 27), R(4));
    st8(base, (R(5) + 28), R(4));
    st8(base, (R(5) + 29), R(4));
    st8(base, (R(5) + 209), R(4));
    st8(base, (R(5) + 30), R(4));
    st8(base, (R(5) + 210), R(4));
    st8(base, (R(5) + 31), R(4));
    st8(base, (R(5) + 211), R(4));
    st8(base, (R(5) + 32), R(4));
    st8(base, (R(5) + 212), R(4));
    st8(base, (R(5) + 33), R(4));
    st8(base, (R(5) + 213), R(4));
    st8(base, (R(5) + 34), R(4));
    st8(base, (R(5) + 214), R(4));
    st8(base, (R(5) + 35), R(4));
    st8(base, (R(5) + 215), R(4));
    st8(base, (R(5) + 36), R(4));
    st8(base, (R(5) + 216), R(4));
    st8(base, (R(5) + 37), R(4));
    st8(base, (R(5) + 217), R(4));
    st8(base, (R(5) + 38), R(4));
    st8(base, (R(5) + 218), R(4));
    st8(base, (R(5) + 39), R(4));
    st8(base, (R(5) + 219), R(4));
    st8(base, (R(5) + 40), R(4));
    st8(base, (R(5) + 220), R(4));
    st8(base, (R(5) + 41), R(4));
    st8(base, (R(5) + 221), R(4));
    st8(base, (R(5) + 42), R(4));
    st8(base, (R(5) + 222), R(4));
    st8(base, (R(5) + 43), R(4));
    st8(base, (R(5) + 223), R(4));
    st8(base, (R(5) + 44), R(4));
    st8(base, (R(5) + 224), R(4));
    st8(base, (R(5) + 45), R(4));
    st8(base, (R(5) + 225), R(4));
    st8(base, (R(5) + 46), R(4));
    st8(base, (R(5) + 226), R(4));
    st8(base, (R(5) + 47), R(4));
    st8(base, (R(5) + 227), R(4));
    st8(base, (R(5) + 48), R(4));
    st8(base, (R(5) + 228), R(4));
    ctx->ctr = R(0);
L_800F36BC:;
    st8(base, (R(6) + 49), R(4));
    R(8) = (R(8) + 1);
    st8(base, (R(6) + 229), R(4));
    st8(base, (R(6) + 50), R(4));
    st8(base, (R(6) + 230), R(4));
    st8(base, (R(6) + 51), R(4));
    st8(base, (R(6) + 231), R(4));
    st8(base, (R(6) + 52), R(4));
    st8(base, (R(6) + 232), R(4));
    st8(base, (R(6) + 53), R(4));
    st8(base, (R(6) + 233), R(4));
    st8(base, (R(6) + 54), R(4));
    st8(base, (R(6) + 234), R(4));
    st8(base, (R(6) + 55), R(4));
    st8(base, (R(6) + 235), R(4));
    st8(base, (R(6) + 56), R(4));
    st8(base, (R(6) + 236), R(4));
    st8(base, (R(6) + 57), R(4));
    st8(base, (R(6) + 237), R(4));
    st8(base, (R(6) + 58), R(4));
    st8(base, (R(6) + 238), R(4));
    st8(base, (R(6) + 59), R(4));
    st8(base, (R(6) + 239), R(4));
    st8(base, (R(6) + 60), R(4));
    st8(base, (R(6) + 240), R(4));
    st8(base, (R(6) + 61), R(4));
    st8(base, (R(6) + 241), R(4));
    st8(base, (R(6) + 62), R(4));
    st8(base, (R(6) + 242), R(4));
    st8(base, (R(6) + 63), R(4));
    st8(base, (R(6) + 243), R(4));
    st8(base, (R(6) + 64), R(4));
    st8(base, (R(6) + 244), R(4));
    st8(base, (R(6) + 65), R(4));
    st8(base, (R(6) + 245), R(4));
    st8(base, (R(6) + 66), R(4));
    st8(base, (R(6) + 246), R(4));
    st8(base, (R(6) + 67), R(4));
    st8(base, (R(6) + 247), R(4));
    st8(base, (R(6) + 68), R(4));
    st8(base, (R(6) + 248), R(4));
    R(6) = (R(6) + 20);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800F36BC; }
    st8(base, (R(5) + 408), R(4));
    R(7) = (R(7) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(7), 192);
    st8(base, (R(5) + 428), R(4));
    st8(base, (R(5) + 409), R(4));
    st8(base, (R(5) + 429), R(4));
    st8(base, (R(5) + 410), R(4));
    st8(base, (R(5) + 430), R(4));
    st8(base, (R(5) + 411), R(4));
    st8(base, (R(5) + 431), R(4));
    st8(base, (R(5) + 412), R(4));
    st8(base, (R(5) + 432), R(4));
    st8(base, (R(5) + 413), R(4));
    st8(base, (R(5) + 433), R(4));
    st8(base, (R(5) + 414), R(4));
    st8(base, (R(5) + 434), R(4));
    st8(base, (R(5) + 415), R(4));
    st8(base, (R(5) + 435), R(4));
    st8(base, (R(5) + 416), R(4));
    st8(base, (R(5) + 436), R(4));
    st8(base, (R(5) + 417), R(4));
    st8(base, (R(5) + 437), R(4));
    st8(base, (R(5) + 418), R(4));
    st8(base, (R(5) + 438), R(4));
    st8(base, (R(5) + 419), R(4));
    st8(base, (R(5) + 439), R(4));
    st8(base, (R(5) + 420), R(4));
    st8(base, (R(5) + 440), R(4));
    st8(base, (R(5) + 421), R(4));
    st8(base, (R(5) + 441), R(4));
    st8(base, (R(5) + 422), R(4));
    st8(base, (R(5) + 442), R(4));
    st8(base, (R(5) + 423), R(4));
    st8(base, (R(5) + 443), R(4));
    st8(base, (R(5) + 424), R(4));
    st8(base, (R(5) + 444), R(4));
    st8(base, (R(5) + 425), R(4));
    st8(base, (R(5) + 445), R(4));
    st8(base, (R(5) + 426), R(4));
    st8(base, (R(5) + 446), R(4));
    st8(base, (R(5) + 427), R(4));
    st8(base, (R(5) + 447), R(4));
    st32(base, (R(5) + 448), R(4));
    st32(base, (R(5) + 452), R(4));
    st32(base, (R(5) + 456), R(4));
    st8(base, (R(5) + 460), R(4));
    st32(base, (R(5) + 464), R(4));
    st8(base, (R(5) + 468), R(4));
    R(5) = (R(5) + 448);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F35FC; }
    R(0) = (0 + 80);
    R(8) = R(3) |R(3);
    R(10) = (0 + 0);
    R(6) = (0 + 0);
    R(5) = (0 + -1);
    ctx->ctr = R(0);
L_800F3848:;
    R(11) = (0 + 0);
    R(4) = (R(8) + 0x10000u);
    R(7) = (R(11) + 0x10000u);
    R(10) = (R(10) + 1);
    R(9) = (R(7) + 20504);
    { uint32_t ea_ = R(9) + R(8); st8(base, ea_, R(6)); R(9) = ea_; }
    R(11) = (0 + 5);
    st8(base, (R(9) + 1), R(6));
    R(7) = (R(11) + 0x10000u);
    R(11) = (0 + 0);
    st8(base, (R(9) + 2), R(6));
    st8(base, (R(9) + 3), R(6));
    st8(base, (R(9) + 4), R(6));
    R(9) = (R(7) + 20504);
    R(7) = (R(11) + 0x10000u);
    R(11) = (0 + 5);
    { uint32_t ea_ = R(9) + R(8); st8(base, ea_, R(6)); R(9) = ea_; }
    R(8) = (R(8) + 24);
    st8(base, (R(9) + 1), R(6));
    st8(base, (R(9) + 2), R(6));
    st8(base, (R(9) + 3), R(6));
    st8(base, (R(9) + 4), R(6));
    R(9) = (R(7) + 20504);
    R(7) = (R(11) + 0x10000u);
    st32(base, (R(4) + 20516), R(5));
    st32(base, (R(4) + 20520), R(6));
    st8(base, (R(4) + 20524), R(6));
    R(4) = (R(8) + 0x10000u);
    { uint32_t ea_ = R(9) + R(8); st8(base, ea_, R(6)); R(9) = ea_; }
    st8(base, (R(9) + 1), R(6));
    st8(base, (R(9) + 2), R(6));
    st8(base, (R(9) + 3), R(6));
    st8(base, (R(9) + 4), R(6));
    R(9) = (R(7) + 20504);
    { uint32_t ea_ = R(9) + R(8); st8(base, ea_, R(6)); R(9) = ea_; }
    R(8) = (R(8) + 24);
    st8(base, (R(9) + 1), R(6));
    st8(base, (R(9) + 2), R(6));
    st8(base, (R(9) + 3), R(6));
    st8(base, (R(9) + 4), R(6));
    st32(base, (R(4) + 20516), R(5));
    st32(base, (R(4) + 20520), R(6));
    st8(base, (R(4) + 20524), R(6));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800F3848; }
    R(4) = (0 + 0x20000u);
    R(0) = (0 + 32);
    R(9) = (0 + 0);
    R(6) = (0 + 0);
    R(4) = (R(4) + -31073);
    ctx->ctr = R(0);
L_800F3910:;
    R(10) = (0 + 0);
    R(5) = (R(3) + 0x10000u);
    R(7) = (R(10) + 0x10000u);
    R(9) = (R(9) + 1);
    R(8) = (R(7) + 24344);
    { uint32_t ea_ = R(8) + R(3); st8(base, ea_, R(6)); R(8) = ea_; }
    R(10) = (0 + 5);
    st8(base, (R(8) + 1), R(6));
    R(7) = (R(10) + 0x10000u);
    R(10) = (0 + 0);
    st8(base, (R(8) + 2), R(6));
    st8(base, (R(8) + 3), R(6));
    st8(base, (R(8) + 4), R(6));
    R(8) = (R(7) + 24344);
    R(7) = (R(10) + 0x10000u);
    R(10) = (0 + 5);
    { uint32_t ea_ = R(8) + R(3); st8(base, ea_, R(6)); R(8) = ea_; }
    R(3) = (R(3) + 24);
    st8(base, (R(8) + 1), R(6));
    st8(base, (R(8) + 2), R(6));
    st8(base, (R(8) + 3), R(6));
    st8(base, (R(8) + 4), R(6));
    R(8) = (R(7) + 24344);
    R(7) = (R(10) + 0x10000u);
    st32(base, (R(5) + 24356), R(6));
    st32(base, (R(5) + 24364), R(4));
    st32(base, (R(5) + 24360), R(6));
    R(5) = (R(3) + 0x10000u);
    { uint32_t ea_ = R(8) + R(3); st8(base, ea_, R(6)); R(8) = ea_; }
    st8(base, (R(8) + 1), R(6));
    st8(base, (R(8) + 2), R(6));
    st8(base, (R(8) + 3), R(6));
    st8(base, (R(8) + 4), R(6));
    R(8) = (R(7) + 24344);
    { uint32_t ea_ = R(8) + R(3); st8(base, ea_, R(6)); R(8) = ea_; }
    R(3) = (R(3) + 24);
    st8(base, (R(8) + 1), R(6));
    st8(base, (R(8) + 2), R(6));
    st8(base, (R(8) + 3), R(6));
    st8(base, (R(8) + 4), R(6));
    st32(base, (R(5) + 24356), R(6));
    st32(base, (R(5) + 24364), R(4));
    st32(base, (R(5) + 24360), R(6));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800F3910; }
}

/* fn_800F39D0 (fn_800F39D0, 1104 bytes) */
static void wm_m_f39d0(GM_CTX) {
    GM_FN(0x800F39D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80320000u);
    R(31) = (R(31) + -17176);
    R(5) = (R(31) + 48);
    R(29) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 4));
    R(3) = (f + 16);
    R(30) = ld32(base, (R(13) + -22088));
    R(6) = (R(4) + 1);
    R(4) = (0 + 32);
    R(7) = R(6) |R(6);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x800F3A1Cu, 0x802E16E8u, 0);
    R(4) = ld32(base, (R(13) + -28008));
    R(3) = (R(30) + 4);
    R(5) = (f + 16);
    R(6) = (f + 12);
    GM_CALLV(0x800F3A30u, 0x800DF440u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(28) = R(3) |R(3);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3A88; }
    R(6) = ld32(base, (R(29) + 4));
    R(3) = (f + 16);
    R(5) = (R(31) + 68);
    R(4) = (0 + 32);
    R(6) = (R(6) + 1);
    R(7) = R(6) |R(6);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x800F3A5Cu, 0x802E16E8u, 0);
    R(0) = ld32(base, (R(29) + 8));
    R(3) = (R(30) + 4);
    R(6) = ld8(base, (f + 26));
    R(5) = (f + 16);
    R(0) = (int8_t)R(0);
    R(4) = ld32(base, (R(13) + -28008));
    R(0) = R(6) + R(0);
    st8(base, (f + 26), R(0));
    R(6) = (f + 12);
    GM_CALLV(0x800F3A84u, 0x800DF1E0u, 0);
    R(28) = R(3) |R(3);
L_800F3A88:;
    R(6) = (0 + 0);
    st32(base, (f + 8), R(6));
    goto L_800F3A9C;
L_800F3A94:;
    R(6) = (R(6) + 1);
    st32(base, (f + 8), R(6));
L_800F3A9C:;
    R(0) = ld8(base, (R(28) + R(6)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F3A94; }
    R(6) = (R(6) + 1);
    st32(base, (f + 8), R(6));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (f + 8);
    GM_CALLV(0x800F3AC4u, 0x800F3E20u, 0);
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F3AD4u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (R(5) + 1);
    st32(base, (f + 8), R(5));
    GM_CALLV(0x800F3AF4u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (f + 8);
    GM_CALLV(0x800F3B0Cu, 0x800F3E80u, 0);
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F3B1Cu, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F3B34u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (f + 8);
    R(6) = (0 + 1);
    GM_CALLV(0x800F3B50u, 0x800F4870u, 0);
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F3B60u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (R(5) + 1);
    st32(base, (f + 8), R(5));
    GM_CALLV(0x800F3B80u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (f + 8);
    R(6) = (0 + 1);
    GM_CALLV(0x800F3B9Cu, 0x800F4B50u, 0);
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F3BACu, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (R(5) + 1);
    st32(base, (f + 8), R(5));
    GM_CALLV(0x800F3BCCu, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (f + 8);
    R(6) = (0 + 1);
    GM_CALLV(0x800F3BE8u, 0x800F4DA0u, 0);
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F3BF8u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F3C10u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (f + 8);
    R(6) = (0 + 0);
    GM_CALLV(0x800F3C2Cu, 0x800F4870u, 0);
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F3C3Cu, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (R(5) + 1);
    st32(base, (f + 8), R(5));
    GM_CALLV(0x800F3C5Cu, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (f + 8);
    R(6) = (0 + 0);
    GM_CALLV(0x800F3C78u, 0x800F4B50u, 0);
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F3C88u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(5) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (R(5) + 1);
    st32(base, (f + 8), R(5));
    GM_CALLV(0x800F3CA8u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3CC4; }
    R(3) = R(29) |R(29);
    R(4) = R(28) |R(28);
    R(5) = (f + 8);
    R(6) = (0 + 0);
    GM_CALLV(0x800F3CC4u, 0x800F4DA0u, 0);
L_800F3CC4:;
    R(3) = ld32(base, (R(29) + 12));
    R(0) = (R(3) + 1);
    st32(base, (R(29) + 12), R(0));
    R(3) = ld32(base, (f + 8));
    R(0) = ld32(base, (f + 12));
    R(6) = (R(3) + 2);
    st32(base, (f + 8), R(6));
    cr_cmp_u(ctx, 0, R(6), R(0));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F3A9C; }
    R(6) = ld32(base, (R(29) + 4));
    R(3) = (f + 16);
    R(5) = (R(31) + 88);
    R(4) = (0 + 32);
    R(6) = (R(6) + 1);
    R(7) = R(6) |R(6);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x800F3D08u, 0x802E16E8u, 0);
    R(4) = ld32(base, (R(13) + -28008));
    R(3) = (R(30) + 4);
    R(5) = (f + 16);
    R(6) = (f + 12);
    GM_CALLV(0x800F3D1Cu, 0x800DF440u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3D6C; }
    R(6) = ld32(base, (R(29) + 4));
    R(3) = (f + 16);
    R(5) = (R(31) + 108);
    R(4) = (0 + 32);
    R(6) = (R(6) + 1);
    R(7) = R(6) |R(6);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x800F3D44u, 0x802E16E8u, 0);
    R(0) = ld32(base, (R(29) + 8));
    R(3) = (R(30) + 4);
    R(6) = ld8(base, (f + 26));
    R(5) = (f + 16);
    R(0) = (int8_t)R(0);
    R(4) = ld32(base, (R(13) + -28008));
    R(0) = R(6) + R(0);
    st8(base, (f + 26), R(0));
    R(6) = (f + 12);
    GM_CALLV(0x800F3D6Cu, 0x800DF1E0u, 0);
L_800F3D6C:;
    R(6) = (0 + 0);
    st32(base, (f + 8), R(6));
    R(30) = R(3) |R(3);
L_800F3D78:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = (f + 8);
    GM_CALLV(0x800F3D88u, 0x800F4F80u, 0);
    R(6) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = (f + 8);
    R(6) = (R(6) + 1);
    st32(base, (f + 8), R(6));
    GM_CALLV(0x800F3DA4u, 0x800F5050u, 0);
    R(6) = ld32(base, (f + 8));
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = (f + 8);
    R(6) = (R(6) + 1);
    st32(base, (f + 8), R(6));
    GM_CALLV(0x800F3DC0u, 0x800F5130u, 0);
    R(4) = ld32(base, (R(29) + 16));
    R(3) = ((int32_t)R(4) * 24);
    R(3) = (R(3) + 0x10000u);
    R(0) = (R(3) + 20504);
    R(0) = ld8(base, (R(29) + R(0)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 48);
    if ((CR_BIT(ctx, 2))) { goto L_800F3DE8; }
    R(0) = (R(4) + 1);
    st32(base, (R(29) + 16), R(0));
L_800F3DE8:;
    R(3) = ld32(base, (f + 8));
    R(0) = ld32(base, (f + 12));
    R(3) = (R(3) + 2);
    st32(base, (f + 8), R(3));
    cr_cmp_u(ctx, 0, R(3), R(0));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F3D78; }
    R(0) = lr;
}

/* fn_800F3E20 (fn_800F3E20, 84 bytes) */
static void wm_m_f3e20(GM_CTX) {
    GM_FN(0x800F3E20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(6) = ld32(base, (R(3) + 12));
    R(0) = ld32(base, (R(5) + 0));
    R(5) = (0 + 5);
    R(6) = ((int32_t)R(6) * 448);
    R(4) = R(4) + R(0);
    R(3) = R(3) + R(6);
    R(3) = (R(3) + 24);
    GM_CALLV(0x800F3E54u, 0x800F3460u, 0);
    R(0) = ld32(base, (R(31) + 0));
    R(0) = R(0) + R(3);
    st32(base, (R(31) + 0), R(0));
    R(0) = lr;
}

/* fn_800F3E80 (fn_800F3E80, 2544 bytes) */
static void wm_m_f3e80(GM_CTX) {
    GM_FN(0x800F3E80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 80);
    R(25) = R(4) |R(4);
    R(4) = ld32(base, (R(3) + 12));
    R(24) = R(3) |R(3);
    R(26) = R(5) |R(5);
    GM_CALLV(0x800F3EA8u, 0x800F56B0u, 0);
    R(4) = ld32(base, (R(26) + 0));
    R(5) = ld8(base, (R(25) + R(4)));
    R(0) = (int8_t)R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3ED8; }
    R(3) = R(4) + R(25);
    R(0) = ld8(base, (R(3) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3ED8; }
    R(0) = (R(4) + 3);
    st32(base, (R(26) + 0), R(0));
    goto L_800F4858;
L_800F3ED8:;
    R(0) = (int8_t)R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3EF4; }
    R(3) = ld32(base, (R(26) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(26) + 0), R(0));
    goto L_800F4858;
L_800F3EF4:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    R(27) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3F10; }
    R(3) = ld32(base, (R(26) + 0));
    R(27) = (0 + 1);
    R(0) = (R(3) + 1);
    st32(base, (R(26) + 0), R(0));
L_800F3F10:;
    R(29) = (f + 8);
    R(28) = (0 + 0);
    R(30) = (0 + 0x80320000u);
    R(31) = (0 + 0x80320000u);
L_800F3F20:;
    R(23) = (f + 8);
    R(22) = (0 + 0);
L_800F3F28:;
    R(5) = ld32(base, (R(26) + 0));
    R(0) = ld8(base, (R(25) + R(5)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F3F58; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((CR_BIT(ctx, 2))) { goto L_800F3F58; }
    R(3) = R(24) |R(24);
    R(4) = R(25) |R(25);
    GM_CALLV(0x800F3F50u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F3F60; }
L_800F3F58:;
    st8(base, (R(29) + R(22)), R(28));
    goto L_800F3F80;
L_800F3F60:;
    R(4) = ld32(base, (R(26) + 0));
    R(22) = (R(22) + 1);
    R(3) = ld8(base, (R(25) + R(4)));
    R(0) = (R(4) + 1);
    st8(base, (R(23) + 0), R(3));
    R(23) = (R(23) + 1);
    st32(base, (R(26) + 0), R(0));
    GM_LOOP(); goto L_800F3F28;
L_800F3F80:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -28004);
    GM_CALLV(0x800F3F8Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3FB0; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x1u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F3FB0:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -28000);
    GM_CALLV(0x800F3FBCu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F3FE0; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x2u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F3FE0:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27992);
    GM_CALLV(0x800F3FECu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4010; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x4u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4010:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27984);
    GM_CALLV(0x800F401Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4040; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x8u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4040:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27976);
    GM_CALLV(0x800F404Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4070; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x10u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4070:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27968);
    GM_CALLV(0x800F407Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F40A0; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x20u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F40A0:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27960);
    GM_CALLV(0x800F40ACu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F40D0; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x40u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F40D0:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27952);
    GM_CALLV(0x800F40DCu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4100; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x80u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4100:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27944);
    GM_CALLV(0x800F410Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4130; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x100u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4130:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27936);
    GM_CALLV(0x800F413Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4160; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x400u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4160:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27928);
    GM_CALLV(0x800F416Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4190; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x800u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4190:;
    R(3) = R(29) |R(29);
    R(4) = (R(30) + -17048);
    GM_CALLV(0x800F419Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F41C0; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x40000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F41C0:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27920);
    GM_CALLV(0x800F41CCu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F41F0; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x80000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F41F0:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27912);
    R(5) = (0 + 6);
    GM_CALLV(0x800F4200u, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4304; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x800F4210u, 0x802DC69Cu, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 6);
    if ((!CR_BIT(ctx, 2))) { goto L_800F424C; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x1000u;
    st32(base, (R(3) + 456), R(0));
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x2000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F424C:;
    R(0) = (R(3) + -7);
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_800F4604; }
    R(0) = ld8(base, (f + 14));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 120);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4284; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x1000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F42D0;
L_800F4284:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 121);
    if ((!CR_BIT(ctx, 2))) { goto L_800F42A8; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x2000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F42D0;
L_800F42A8:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 49);
    if ((CR_BIT(ctx, 0))) { goto L_800F42D0; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 57);
    if ((CR_BIT(ctx, 1))) { goto L_800F42D0; }
    R(3) = (f + 14);
    GM_CALLV(0x800F42C0u, 0x802E2108u, 0);
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(4) = R(24) + R(0);
    st8(base, (R(4) + 460), R(3));
L_800F42D0:;
    R(0) = ld8(base, (f + 15));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 49);
    if ((CR_BIT(ctx, 0))) { goto L_800F4604; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 57);
    if ((CR_BIT(ctx, 1))) { goto L_800F4604; }
    R(3) = (f + 15);
    GM_CALLV(0x800F42F0u, 0x802E2108u, 0);
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(4) = R(24) + R(0);
    st8(base, (R(4) + 460), R(3));
    goto L_800F4604;
L_800F4304:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27904);
    GM_CALLV(0x800F4310u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4334; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x4000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4334:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27896);
    GM_CALLV(0x800F4340u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4364; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x8000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4364:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27888);
    GM_CALLV(0x800F4370u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4394; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x10000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4394:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27880);
    GM_CALLV(0x800F43A0u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F43C4; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x20000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F43C4:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27872);
    GM_CALLV(0x800F43D0u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F43F4; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x2000000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F43F4:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27864);
    GM_CALLV(0x800F4400u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4424; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x4000000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4424:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27856);
    GM_CALLV(0x800F4430u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4454; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x8000000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4454:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27848);
    GM_CALLV(0x800F4460u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4484; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x10000000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4484:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27840);
    GM_CALLV(0x800F4490u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F44B4; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x20000000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F44B4:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27832);
    GM_CALLV(0x800F44C0u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F44E4; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x40000000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F44E4:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27824);
    R(5) = (0 + 5);
    GM_CALLV(0x800F44F4u, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4518; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x100000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4518:;
    R(3) = R(29) |R(29);
    R(4) = (R(31) + -17036);
    GM_CALLV(0x800F4524u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4548; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x200000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4548:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27816);
    GM_CALLV(0x800F4554u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4578; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x400000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F4578:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27808);
    GM_CALLV(0x800F4584u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F45A8; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x800000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F45A8:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27800);
    GM_CALLV(0x800F45B4u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F45D8; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x1000000u;
    st32(base, (R(3) + 456), R(0));
    goto L_800F4604;
L_800F45D8:;
    R(3) = R(29) |R(29);
    R(4) = (R(13) + -27792);
    GM_CALLV(0x800F45E4u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4604; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 456));
    R(0) = R(0) | 0x80000000u;
    st32(base, (R(3) + 456), R(0));
L_800F4604:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27784);
    GM_CALLV(0x800F4610u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4634; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x2u;
    st32(base, (R(3) + 464), R(0));
    goto L_800F47E0;
L_800F4634:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27776);
    GM_CALLV(0x800F4640u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4664; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x4u;
    st32(base, (R(3) + 464), R(0));
    goto L_800F47E0;
L_800F4664:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27768);
    GM_CALLV(0x800F4670u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4694; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x8u;
    st32(base, (R(3) + 464), R(0));
    goto L_800F47E0;
L_800F4694:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27760);
    GM_CALLV(0x800F46A0u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F46C4; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x10u;
    st32(base, (R(3) + 464), R(0));
    goto L_800F47E0;
L_800F46C4:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27752);
    GM_CALLV(0x800F46D0u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F46F4; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x20u;
    st32(base, (R(3) + 464), R(0));
    goto L_800F47E0;
L_800F46F4:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27744);
    GM_CALLV(0x800F4700u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4724; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x40u;
    st32(base, (R(3) + 464), R(0));
    goto L_800F47E0;
L_800F4724:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27736);
    GM_CALLV(0x800F4730u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4754; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x80u;
    st32(base, (R(3) + 464), R(0));
    goto L_800F47E0;
L_800F4754:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27728);
    GM_CALLV(0x800F4760u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4784; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x100u;
    st32(base, (R(3) + 464), R(0));
    goto L_800F47E0;
L_800F4784:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27720);
    GM_CALLV(0x800F4790u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F47B4; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x400u;
    st32(base, (R(3) + 464), R(0));
    goto L_800F47E0;
L_800F47B4:;
    R(3) = (f + 8);
    R(4) = (R(13) + -27712);
    GM_CALLV(0x800F47C0u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F47E0; }
    R(0) = ld32(base, (R(24) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(24) + R(0);
    R(0) = ld32(base, (R(3) + 464));
    R(0) = R(0) | 0x800u;
    st32(base, (R(3) + 464), R(0));
L_800F47E0:;
    R(5) = ld32(base, (R(26) + 0));
    R(0) = ld8(base, (R(25) + R(5)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4800; }
    R(0) = (R(5) + 1);
    st32(base, (R(26) + 0), R(0));
    goto L_800F4834;
L_800F4800:;
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4810; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4834; }
L_800F4810:;
    R(3) = R(24) |R(24);
    R(4) = R(25) |R(25);
    GM_CALLV(0x800F481Cu, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4834; }
    R(3) = ld32(base, (R(26) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(26) + 0), R(0));
    GM_LOOP(); goto L_800F3F20;
L_800F4834:;
    R(5) = ld32(base, (R(26) + 0));
    R(3) = R(24) |R(24);
    R(4) = R(25) |R(25);
    GM_CALLV(0x800F4844u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4858; }
    R(3) = ld32(base, (R(26) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(26) + 0), R(0));
L_800F4858:;
    R(11) = (f + 80);
    R(0) = lr;
}

/* fn_800F4870 (fn_800F4870, 736 bytes) */
static void wm_m_f4870(GM_CTX) {
    GM_FN(0x800F4870); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(8) = ld32(base, (R(5) + 0));
    R(26) = R(3) |R(3);
    R(27) = R(4) |R(4);
    R(28) = R(5) |R(5);
    R(9) = ld8(base, (R(4) + R(8)));
    R(29) = R(6) |R(6);
    R(30) = (0 + 0);
    R(0) = (int8_t)R(9);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F48C8; }
    R(7) = R(8) + R(4);
    R(0) = ld8(base, (R(7) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F48C8; }
    R(0) = (R(8) + 2);
    st32(base, (R(5) + 0), R(0));
    goto L_800F4B0C;
L_800F48C8:;
    R(0) = (int8_t)R(9);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F49D4; }
    R(8) = ld32(base, (R(5) + 0));
    R(7) = (0 + 0);
    R(0) = (0 + 2);
    R(8) = (R(8) + 1);
    st32(base, (R(5) + 0), R(8));
L_800F48E8:;
    R(10) = R(3) + R(7);
    R(12) = (0 + 0);
    ctx->ctr = R(0);
    R(0) = R(0) | 0x0u;
L_800F48F8:;
    R(8) = ld32(base, (R(5) + 0));
    R(11) = ld8(base, (R(4) + R(8)));
    R(8) = (int8_t)R(11);
    cr_cmp_s(ctx, 0, (int32_t)R(8), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F494C; }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F492C; }
    R(9) = ld32(base, (R(3) + 12));
    R(8) = R(12) + R(10);
    R(9) = ((int32_t)R(9) * 448);
    R(8) = R(9) + R(8);
    st8(base, (R(8) + 29), R(11));
    goto L_800F4940;
L_800F492C:;
    R(9) = ld32(base, (R(3) + 12));
    R(8) = R(12) + R(10);
    R(9) = ((int32_t)R(9) * 448);
    R(8) = R(9) + R(8);
    st8(base, (R(8) + 209), R(11));
L_800F4940:;
    R(8) = ld32(base, (R(5) + 0));
    R(8) = (R(8) + 1);
    st32(base, (R(5) + 0), R(8));
L_800F494C:;
    R(8) = ld32(base, (R(5) + 0));
    R(12) = (R(12) + 1);
    R(11) = ld8(base, (R(4) + R(8)));
    R(8) = (int8_t)R(11);
    cr_cmp_s(ctx, 0, (int32_t)R(8), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F49A4; }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4984; }
    R(9) = ld32(base, (R(3) + 12));
    R(8) = R(12) + R(10);
    R(9) = ((int32_t)R(9) * 448);
    R(8) = R(9) + R(8);
    st8(base, (R(8) + 29), R(11));
    goto L_800F4998;
L_800F4984:;
    R(9) = ld32(base, (R(3) + 12));
    R(8) = R(12) + R(10);
    R(9) = ((int32_t)R(9) * 448);
    R(8) = R(9) + R(8);
    st8(base, (R(8) + 209), R(11));
L_800F4998:;
    R(8) = ld32(base, (R(5) + 0));
    R(8) = (R(8) + 1);
    st32(base, (R(5) + 0), R(8));
L_800F49A4:;
    R(12) = (R(12) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800F48F8; }
    R(9) = ld32(base, (R(5) + 0));
    R(7) = (R(7) + 5);
    R(30) = (R(30) + 1);
    R(8) = (R(9) + 1);
    st32(base, (R(5) + 0), R(8));
    R(8) = ld8(base, (R(4) + R(9)));
    R(8) = (int8_t)R(8);
    cr_cmp_s(ctx, 0, (int32_t)R(8), 34);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F48E8; }
    goto L_800F4B0C;
L_800F49D4:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4B0C; }
    R(31) = (0 + 0);
    R(25) = (0 + 2);
L_800F49E4:;
    R(4) = R(26) + R(31);
    R(6) = (0 + 0);
    ctx->ctr = R(25);
L_800F49F0:;
    R(0) = ld32(base, (R(28) + 0));
    R(5) = ld8(base, (R(27) + R(0)));
    R(0) = (int8_t)R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4A44; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4A24; }
    R(3) = ld32(base, (R(26) + 12));
    R(0) = R(6) + R(4);
    R(3) = ((int32_t)R(3) * 448);
    R(3) = R(3) + R(0);
    st8(base, (R(3) + 29), R(5));
    goto L_800F4A38;
L_800F4A24:;
    R(3) = ld32(base, (R(26) + 12));
    R(0) = R(6) + R(4);
    R(3) = ((int32_t)R(3) * 448);
    R(3) = R(3) + R(0);
    st8(base, (R(3) + 209), R(5));
L_800F4A38:;
    R(3) = ld32(base, (R(28) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(28) + 0), R(0));
L_800F4A44:;
    R(0) = ld32(base, (R(28) + 0));
    R(6) = (R(6) + 1);
    R(5) = ld8(base, (R(27) + R(0)));
    R(0) = (int8_t)R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4A9C; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4A7C; }
    R(3) = ld32(base, (R(26) + 12));
    R(0) = R(6) + R(4);
    R(3) = ((int32_t)R(3) * 448);
    R(3) = R(3) + R(0);
    st8(base, (R(3) + 29), R(5));
    goto L_800F4A90;
L_800F4A7C:;
    R(3) = ld32(base, (R(26) + 12));
    R(0) = R(6) + R(4);
    R(3) = ((int32_t)R(3) * 448);
    R(3) = R(3) + R(0);
    st8(base, (R(3) + 209), R(5));
L_800F4A90:;
    R(3) = ld32(base, (R(28) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(28) + 0), R(0));
L_800F4A9C:;
    R(6) = (R(6) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800F49F0; }
    R(31) = (R(31) + 5);
    R(30) = (R(30) + 1);
    goto L_800F4AD0;
L_800F4AB0:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800F4ABCu, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4AE4; }
    R(3) = ld32(base, (R(28) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(28) + 0), R(0));
L_800F4AD0:;
    R(5) = ld32(base, (R(28) + 0));
    R(0) = ld8(base, (R(27) + R(5)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F4AB0; }
L_800F4AE4:;
    R(5) = ld32(base, (R(28) + 0));
    R(0) = ld8(base, (R(27) + R(5)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4B0C; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800F4B04u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F49E4; }
L_800F4B0C:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4B28; }
    R(0) = ld32(base, (R(26) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(26) + R(0);
    st32(base, (R(3) + 392), R(30));
    goto L_800F4B38;
L_800F4B28:;
    R(0) = ld32(base, (R(26) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(26) + R(0);
    st32(base, (R(3) + 404), R(30));
L_800F4B38:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_800F4B50 (fn_800F4B50, 592 bytes) */
static void wm_m_f4b50(GM_CTX) {
    GM_FN(0x800F4B50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(8) = ld32(base, (R(5) + 0));
    R(26) = R(3) |R(3);
    R(27) = R(4) |R(4);
    R(28) = R(5) |R(5);
    R(9) = ld8(base, (R(4) + R(8)));
    R(29) = R(6) |R(6);
    R(30) = (0 + 0);
    R(0) = (int8_t)R(9);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4BA8; }
    R(7) = R(8) + R(4);
    R(0) = ld8(base, (R(7) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4BA8; }
    R(0) = (R(8) + 2);
    st32(base, (R(5) + 0), R(0));
    goto L_800F4D5C;
L_800F4BA8:;
    R(0) = (int8_t)R(9);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4C6C; }
    R(8) = ld32(base, (R(5) + 0));
    R(7) = (0 + 0);
    R(0) = (0 + 9);
    R(8) = (R(8) + 1);
    st32(base, (R(5) + 0), R(8));
L_800F4BC8:;
    R(10) = R(3) + R(7);
    R(12) = (0 + 0);
    ctx->ctr = R(0);
    R(0) = R(0) | 0x0u;
L_800F4BD8:;
    R(8) = ld32(base, (R(5) + 0));
    R(11) = ld8(base, (R(4) + R(8)));
    R(8) = (int8_t)R(11);
    cr_cmp_s(ctx, 0, (int32_t)R(8), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4C3C; }
    cr_cmp_s(ctx, 0, (int32_t)R(8), 34);
    if ((CR_BIT(ctx, 2))) { goto L_800F4C3C; }
    cr_cmp_s(ctx, 0, (int32_t)R(8), 32);
    if ((CR_BIT(ctx, 2))) { goto L_800F4C30; }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4C1C; }
    R(9) = ld32(base, (R(3) + 12));
    R(8) = R(12) + R(10);
    R(9) = ((int32_t)R(9) * 448);
    R(8) = R(9) + R(8);
    st8(base, (R(8) + 49), R(11));
    goto L_800F4C30;
L_800F4C1C:;
    R(9) = ld32(base, (R(3) + 12));
    R(8) = R(12) + R(10);
    R(9) = ((int32_t)R(9) * 448);
    R(8) = R(9) + R(8);
    st8(base, (R(8) + 229), R(11));
L_800F4C30:;
    R(8) = ld32(base, (R(5) + 0));
    R(8) = (R(8) + 1);
    st32(base, (R(5) + 0), R(8));
L_800F4C3C:;
    R(12) = (R(12) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800F4BD8; }
    R(9) = ld32(base, (R(5) + 0));
    R(7) = (R(7) + 10);
    R(30) = (R(30) + 1);
    R(8) = (R(9) + 1);
    st32(base, (R(5) + 0), R(8));
    R(8) = ld8(base, (R(4) + R(9)));
    R(8) = (int8_t)R(8);
    cr_cmp_s(ctx, 0, (int32_t)R(8), 34);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F4BC8; }
    goto L_800F4D5C;
L_800F4C6C:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4D5C; }
    R(31) = (0 + 0);
    R(25) = (0 + 9);
L_800F4C7C:;
    R(4) = R(26) + R(31);
    R(6) = (0 + 0);
    ctx->ctr = R(25);
L_800F4C88:;
    R(0) = ld32(base, (R(28) + 0));
    R(5) = ld8(base, (R(27) + R(0)));
    R(0) = (int8_t)R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4CEC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((CR_BIT(ctx, 2))) { goto L_800F4CEC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 32);
    if ((CR_BIT(ctx, 2))) { goto L_800F4CE0; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4CCC; }
    R(3) = ld32(base, (R(26) + 12));
    R(0) = R(6) + R(4);
    R(3) = ((int32_t)R(3) * 448);
    R(3) = R(3) + R(0);
    st8(base, (R(3) + 49), R(5));
    goto L_800F4CE0;
L_800F4CCC:;
    R(3) = ld32(base, (R(26) + 12));
    R(0) = R(6) + R(4);
    R(3) = ((int32_t)R(3) * 448);
    R(3) = R(3) + R(0);
    st8(base, (R(3) + 229), R(5));
L_800F4CE0:;
    R(3) = ld32(base, (R(28) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(28) + 0), R(0));
L_800F4CEC:;
    R(6) = (R(6) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800F4C88; }
    R(31) = (R(31) + 10);
    R(30) = (R(30) + 1);
    goto L_800F4D20;
L_800F4D00:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800F4D0Cu, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4D34; }
    R(3) = ld32(base, (R(28) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(28) + 0), R(0));
L_800F4D20:;
    R(5) = ld32(base, (R(28) + 0));
    R(0) = ld8(base, (R(27) + R(5)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F4D00; }
L_800F4D34:;
    R(5) = ld32(base, (R(28) + 0));
    R(0) = ld8(base, (R(27) + R(5)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4D5C; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800F4D54u, 0x800F5F10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F4C7C; }
L_800F4D5C:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4D78; }
    R(0) = ld32(base, (R(26) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(26) + R(0);
    st32(base, (R(3) + 396), R(30));
    goto L_800F4D88;
L_800F4D78:;
    R(0) = ld32(base, (R(26) + 12));
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(26) + R(0);
    st32(base, (R(3) + 400), R(30));
L_800F4D88:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_800F4DA0 (fn_800F4DA0, 468 bytes) */
static void wm_m_f4da0(GM_CTX) {
    GM_FRAME(16); gptr f = gm_frame_sp;
    R(9) = (0 + 0);
    st32(base, (f + 12), R(31));
    R(7) = ld32(base, (R(5) + 0));
    R(0) = ld8(base, (R(4) + R(7)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4DCC; }
    R(0) = (R(7) + 1);
    st32(base, (R(5) + 0), R(0));
    R(9) = (0 + 1);
L_800F4DCC:;
    R(7) = (0 + 0);
    R(0) = (0 + 0);
    R(0) = R(0) | 0x0u;
L_800F4DD8:;
    R(12) = R(3) + R(7);
    R(8) = (0 + 0);
L_800F4DE0:;
    R(10) = ld32(base, (R(5) + 0));
    R(31) = ld8(base, (R(4) + R(10)));
    R(11) = R(4) + R(10);
    R(10) = (int8_t)R(31);
    cr_cmp_s(ctx, 0, (int32_t)R(10), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4E14; }
    cr_cmp_s(ctx, 0, (int32_t)R(10), 34);
    if ((CR_BIT(ctx, 2))) { goto L_800F4E14; }
    cr_cmp_s(ctx, 0, (int32_t)R(10), 13);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4E98; }
    R(10) = ld8(base, (R(11) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(10), 10);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4E98; }
L_800F4E14:;
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4E38; }
    R(10) = ld32(base, (R(3) + 12));
    R(11) = R(7) + R(3);
    R(10) = ((int32_t)R(10) * 448);
    R(10) = R(8) + R(10);
    R(10) = R(11) + R(10);
    st8(base, (R(10) + 408), R(0));
    goto L_800F4E50;
L_800F4E38:;
    R(10) = ld32(base, (R(3) + 12));
    R(11) = R(7) + R(3);
    R(10) = ((int32_t)R(10) * 448);
    R(10) = R(8) + R(10);
    R(10) = R(11) + R(10);
    st8(base, (R(10) + 428), R(0));
L_800F4E50:;
    cr_cmp_s(ctx, 0, (int32_t)R(8), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800F4EE0; }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4E7C; }
    R(10) = ld32(base, (R(3) + 12));
    R(10) = ((int32_t)R(10) * 448);
    R(11) = R(3) + R(10);
    R(10) = ld32(base, (R(11) + 448));
    R(10) = (R(10) + 1);
    st32(base, (R(11) + 448), R(10));
    goto L_800F4EE0;
L_800F4E7C:;
    R(10) = ld32(base, (R(3) + 12));
    R(10) = ((int32_t)R(10) * 448);
    R(11) = R(3) + R(10);
    R(10) = ld32(base, (R(11) + 452));
    R(10) = (R(10) + 1);
    st32(base, (R(11) + 452), R(10));
    goto L_800F4EE0;
L_800F4E98:;
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F4EB8; }
    R(11) = ld32(base, (R(3) + 12));
    R(10) = R(8) + R(12);
    R(11) = ((int32_t)R(11) * 448);
    R(10) = R(11) + R(10);
    st8(base, (R(10) + 408), R(31));
    goto L_800F4ECC;
L_800F4EB8:;
    R(11) = ld32(base, (R(3) + 12));
    R(10) = R(8) + R(12);
    R(11) = ((int32_t)R(11) * 448);
    R(10) = R(11) + R(10);
    st8(base, (R(10) + 428), R(31));
L_800F4ECC:;
    R(10) = ld32(base, (R(5) + 0));
    R(8) = (R(8) + 1);
    R(10) = (R(10) + 1);
    st32(base, (R(5) + 0), R(10));
    GM_LOOP(); goto L_800F4DE0;
L_800F4EE0:;
    R(11) = ld32(base, (R(5) + 0));
    R(31) = ld8(base, (R(4) + R(11)));
    R(12) = R(4) + R(11);
    R(10) = (int8_t)R(31);
    cr_cmp_s(ctx, 0, (int32_t)R(10), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4F04; }
    R(0) = (R(11) + 1);
    st32(base, (R(5) + 0), R(0));
    goto L_800F4F68;
L_800F4F04:;
    cr_cmp_s(ctx, 0, (int32_t)R(9), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4F14; }
    cr_cmp_s(ctx, 0, (int32_t)R(10), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F4F2C; }
L_800F4F14:;
    R(10) = (int8_t)R(31);
    cr_cmp_s(ctx, 0, (int32_t)R(10), 13);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4F54; }
    R(10) = ld8(base, (R(12) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(10), 10);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4F54; }
L_800F4F2C:;
    cr_cmp_s(ctx, 0, (int32_t)R(8), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4F68; }
    R(0) = ld8(base, (R(4) + R(11)));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((!CR_BIT(ctx, 2))) { goto L_800F4F68; }
    R(3) = ld32(base, (R(5) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(5) + 0), R(0));
    goto L_800F4F68;
L_800F4F54:;
    R(8) = ld32(base, (R(5) + 0));
    R(7) = (R(7) + 10);
    R(8) = (R(8) + 1);
    st32(base, (R(5) + 0), R(8));
    GM_LOOP(); goto L_800F4DD8;
L_800F4F68:;
    R(31) = ld32(base, (f + 12));
}

/* fn_800F4F80 (fn_800F4F80, 204 bytes) */
static void wm_m_f4f80(GM_CTX) {
    GM_FN(0x800F4F80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(6) = ld32(base, (R(3) + 16));
    R(7) = (R(3) + 0x10000u);
    R(0) = ld32(base, (R(5) + 0));
    R(26) = R(3) |R(3);
    R(6) = ((int32_t)R(6) * 24);
    R(25) = R(5) |R(5);
    R(3) = (f + 8);
    R(4) = R(4) + R(0);
    R(6) = R(7) + R(6);
    R(5) = (0 + 10);
    R(28) = (R(6) + 20504);
    GM_CALLV(0x800F4FC4u, 0x800F3460u, 0);
    R(4) = ld32(base, (R(26) + 16));
    R(30) = (R(26) + 0x10000u);
    R(31) = R(3) |R(3);
    R(27) = (0 + 0);
    R(29) = (R(4) + -1);
    R(26) = (0 + 0);
    R(30) = (R(30) + 20504);
    goto L_800F5008;
L_800F4FE4:;
    R(3) = R(30) |R(30);
    R(4) = (f + 8);
    R(5) = (0 + 10);
    GM_CALLV(0x800F4FF4u, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5000; }
    R(27) = (0 + 1);
L_800F5000:;
    R(30) = (R(30) + 24);
    R(26) = (R(26) + 1);
L_800F5008:;
    cr_cmp_s(ctx, 0, (int32_t)R(26), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F4FE4; }
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5028; }
    R(3) = R(28) |R(28);
    R(4) = (f + 8);
    R(5) = (0 + 10);
    GM_CALLV(0x800F5028u, 0x802E19F8u, 0);
L_800F5028:;
    R(0) = ld32(base, (R(25) + 0));
    R(11) = (f + 64);
    R(0) = R(0) + R(31);
    st32(base, (R(25) + 0), R(0));
    R(0) = lr;
}

/* fn_800F5050 (fn_800F5050, 212 bytes) */
static void wm_m_f5050(GM_CTX) {
    GM_FN(0x800F5050); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(5) |R(5);
    R(28) = R(3) |R(3);
    R(3) = (f + 8);
    R(0) = ld32(base, (R(5) + 0));
    R(5) = (0 + 20);
    R(4) = R(4) + R(0);
    GM_CALLV(0x800F5088u, 0x800F3460u, 0);
    R(4) = ld32(base, (R(29) + 0));
    R(0) = (R(28) + 0x10000u);
    R(3) = R(4) + R(3);
    st32(base, (R(29) + 0), R(3));
    R(3) = ld32(base, (R(28) + 16));
    R(30) = ((int32_t)R(3) * 24);
    R(3) = R(0) + R(30);
    R(0) = ld8(base, (R(3) + 20504));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 48);
    if ((CR_BIT(ctx, 2))) { goto L_800F5104; }
    R(31) = (0 + 0x80320000u);
    R(29) = (0 + 0);
    R(31) = (R(31) + -16944);
    goto L_800F50F8;
L_800F50C0:;
    R(4) = (f + 8);
    GM_CALLV(0x800F50C8u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F50F0; }
    R(4) = (0 + 0x802F0000u);
    R(0) = (R(28) + 0x10000u);
    R(5) = rotl32(R(29), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + 13168);
    R(3) = R(0) + R(30);
    R(0) = ld32(base, (R(4) + R(5)));
    st32(base, (R(3) + 20516), R(0));
    goto L_800F5104;
L_800F50F0:;
    R(31) = (R(31) + 4);
    R(29) = (R(29) + 1);
L_800F50F8:;
    R(3) = ld32(base, (R(31) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F50C0; }
L_800F5104:;
    R(0) = lr;
}

/* fn_800F5130 (fn_800F5130, 468 bytes) */
static void wm_m_f5130(GM_CTX) {
    GM_FN(0x800F5130); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 80);
    R(6) = ld32(base, (R(5) + 0));
    R(26) = R(3) |R(3);
    R(27) = R(4) |R(4);
    R(28) = R(5) |R(5);
    R(7) = ld8(base, (R(4) + R(6)));
    R(0) = (int8_t)R(7);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 13);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5174; }
    R(3) = R(6) + R(4);
    R(0) = ld8(base, (R(3) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((CR_BIT(ctx, 2))) { goto L_800F52EC; }
L_800F5174:;
    R(0) = (int8_t)R(7);
    R(29) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5194; }
    R(3) = ld32(base, (R(5) + 0));
    R(29) = (0 + 1);
    R(0) = (R(3) + 1);
    st32(base, (R(5) + 0), R(0));
L_800F5194:;
    R(31) = (f + 8);
    R(30) = (0 + 0);
L_800F519C:;
    R(4) = (f + 8);
    R(6) = (0 + 0);
    R(0) = R(0) | 0x0u;
L_800F51A8:;
    R(0) = ld32(base, (R(28) + 0));
    R(5) = ld8(base, (R(27) + R(0)));
    R(3) = R(27) + R(0);
    R(0) = (int8_t)R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F51DC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((CR_BIT(ctx, 2))) { goto L_800F51DC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 13);
    if ((!CR_BIT(ctx, 2))) { goto L_800F51E4; }
    R(0) = ld8(base, (R(3) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((!CR_BIT(ctx, 2))) { goto L_800F51E4; }
L_800F51DC:;
    st8(base, (R(31) + R(6)), R(30));
    goto L_800F5200;
L_800F51E4:;
    st8(base, (R(4) + 0), R(5));
    R(4) = (R(4) + 1);
    R(6) = (R(6) + 1);
    R(3) = ld32(base, (R(28) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(28) + 0), R(0));
    GM_LOOP(); goto L_800F51A8;
L_800F5200:;
    R(0) = ld32(base, (R(26) + 16));
    R(0) = ((int32_t)R(0) * 24);
    R(25) = R(26) + R(0);
    R(3) = (R(25) + 0x10000u);
    R(0) = ld8(base, (R(3) + 20504));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 48);
    if ((CR_BIT(ctx, 2))) { goto L_800F5290; }
    R(3) = R(31) |R(31);
    R(4) = (R(13) + -27636);
    GM_CALLV(0x800F5228u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5244; }
    R(3) = (R(25) + 0x10000u);
    R(0) = ld8(base, (R(3) + 20524));
    R(0) = R(0) | 0x1u;
    st8(base, (R(3) + 20524), R(0));
    goto L_800F5290;
L_800F5244:;
    R(3) = R(31) |R(31);
    R(4) = (R(13) + -27632);
    GM_CALLV(0x800F5250u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F526C; }
    R(3) = (R(25) + 0x10000u);
    R(0) = ld8(base, (R(3) + 20524));
    R(0) = R(0) | 0x2u;
    st8(base, (R(3) + 20524), R(0));
    goto L_800F5290;
L_800F526C:;
    R(3) = R(31) |R(31);
    R(4) = (R(13) + -27628);
    GM_CALLV(0x800F5278u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5290; }
    R(3) = (R(25) + 0x10000u);
    R(0) = ld8(base, (R(3) + 20524));
    R(0) = R(0) | 0x4u;
    st8(base, (R(3) + 20524), R(0));
L_800F5290:;
    R(3) = ld32(base, (R(28) + 0));
    R(5) = ld8(base, (R(27) + R(3)));
    R(4) = R(27) + R(3);
    R(0) = (int8_t)R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 34);
    if ((!CR_BIT(ctx, 2))) { goto L_800F52B4; }
    R(0) = (R(3) + 1);
    st32(base, (R(28) + 0), R(0));
    goto L_800F52EC;
L_800F52B4:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F52C4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 44);
    if ((CR_BIT(ctx, 2))) { goto L_800F52EC; }
L_800F52C4:;
    R(0) = (int8_t)R(5);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 13);
    if ((!CR_BIT(ctx, 2))) { goto L_800F52DC; }
    R(0) = ld8(base, (R(4) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((CR_BIT(ctx, 2))) { goto L_800F52EC; }
L_800F52DC:;
    R(3) = ld32(base, (R(28) + 0));
    R(0) = (R(3) + 1);
    st32(base, (R(28) + 0), R(0));
    GM_LOOP(); goto L_800F519C;
L_800F52EC:;
    R(11) = (f + 80);
    R(0) = lr;
}

/* fn_800F5310 (fn_800F5310, 132 bytes) */
static void wm_m_f5310(GM_CTX) {
    GM_FN(0x800F5310); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(31) = (R(3) + 0x10000u);
    R(30) = ld32(base, (R(3) + 16));
    R(27) = R(3) |R(3);
    R(28) = R(4) |R(4);
    R(29) = (0 + 0);
    R(31) = (R(31) + 20504);
    goto L_800F5370;
L_800F5340:;
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F534Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5368; }
    R(0) = ((int32_t)R(29) * 24);
    R(3) = (R(27) + 0x10000u);
    R(3) = R(3) + R(0);
    R(3) = ld32(base, (R(3) + 20516));
    goto L_800F537C;
L_800F5368:;
    R(31) = (R(31) + 24);
    R(29) = (R(29) + 1);
L_800F5370:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(30));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F5340; }
    R(3) = (0 + -1);
L_800F537C:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_800F53A0 (fn_800F53A0, 128 bytes) */
static void wm_m_f53a0(GM_CTX) {
    GM_FN(0x800F53A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (R(3) + 24);
    R(29) = (0 + 0);
    R(28) = R(4) |R(4);
    R(30) = ld32(base, (R(3) + 12));
    goto L_800F53F4;
L_800F53D0:;
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800F53DCu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F53EC; }
    R(3) = R(29) |R(29);
    goto L_800F5400;
L_800F53EC:;
    R(31) = (R(31) + 448);
    R(29) = (R(29) + 1);
L_800F53F4:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(30));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F53D0; }
    R(3) = (0 + -1);
L_800F5400:;
    R(0) = lr;
}

/* fn_800F5420 (fn_800F5420, 172 bytes) */
static void wm_m_f5420(GM_CTX) {
    GM_FN(0x800F5420); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x800F5440u, 0x80168400u, 0);
    st32(base, (f + 8), R(3));
    R(31) = (0 + 0);
    goto L_800F54A4;
L_800F544C:;
    R(4) = R(31) |R(31);
    R(3) = (f + 8);
    GM_CALLV(0x800F5458u, 0x8023B2A0u, 0);
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F546C; }
    R(4) = R(3) + R(0);
    goto L_800F5470;
L_800F546C:;
    R(4) = (0 + 0);
L_800F5470:;
    R(0) = ld8(base, (R(4) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 75);
    if ((!CR_BIT(ctx, 2))) { goto L_800F54A0; }
    R(0) = ld32(base, (R(30) + 12));
    R(5) = (0 + 5);
    R(0) = ((int32_t)R(0) * 448);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 24);
    GM_CALLV(0x800F5494u, 0x802E19F8u, 0);
    R(3) = ld32(base, (R(30) + 12));
    R(0) = (R(3) + 1);
    st32(base, (R(30) + 12), R(0));
L_800F54A0:;
    R(31) = (R(31) + 1);
L_800F54A4:;
    R(3) = (f + 8);
    GM_CALLV(0x800F54ACu, 0x8023B360u, 0);
    cr_cmp_u(ctx, 0, R(31), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F544C; }
    R(0) = lr;
}

/* fn_800F54D0 (fn_800F54D0, 468 bytes) */
static void wm_m_f54d0(GM_CTX) {
    GM_FN(0x800F54D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x800F54F4u, 0x80168400u, 0);
    st32(base, (f + 12), R(3));
    R(31) = (0 + 0);
    goto L_800F5678;
L_800F5500:;
    R(4) = R(31) |R(31);
    R(3) = (f + 12);
    GM_CALLV(0x800F550Cu, 0x8023B2A0u, 0);
    st32(base, (f + 8), R(3));
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F5524; }
    R(29) = R(3) + R(0);
    goto L_800F5528;
L_800F5524:;
    R(29) = (0 + 0);
L_800F5528:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x800F5530u, 0x802DC69Cu, 0);
    cr_cmp_u(ctx, 0, R(3), 0x9u);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5674; }
    R(0) = ld8(base, (R(29) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 82);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5674; }
    R(3) = ld8(base, (R(29) + 4));
    R(0) = (R(3) + -48);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x9u);
    if ((CR_BIT(ctx, 1))) { goto L_800F5674; }
    R(3) = ld8(base, (R(29) + 8));
    R(0) = (R(3) + -48);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x9u);
    if ((CR_BIT(ctx, 1))) { goto L_800F5674; }
    R(0) = ld32(base, (R(30) + 20));
    R(3) = (R(30) + 0x10000u);
    R(4) = R(29) |R(29);
    R(5) = (0 + 10);
    R(0) = ((int32_t)R(0) * 24);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 24344);
    GM_CALLV(0x800F558Cu, 0x802E19F8u, 0);
    R(0) = ld32(base, (R(30) + 20));
    R(3) = (R(30) + 0x10000u);
    R(4) = (f + 24);
    R(0) = ((int32_t)R(0) * 24);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 24344);
    GM_CALLV(0x800F55A8u, 0x800F9270u, 0);
    R(0) = ld32(base, (R(30) + 20));
    R(3) = (R(30) + 0x10000u);
    R(4) = (f + 16);
    R(0) = ((int32_t)R(0) * 24);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 24344);
    GM_CALLV(0x800F55C4u, 0x800F92C0u, 0);
    R(0) = ld32(base, (R(30) + 20));
    R(3) = (R(30) + 0x10000u);
    R(4) = (0 + 20);
    R(0) = ((int32_t)R(0) * 24);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 24344);
    GM_CALLV(0x800F55E0u, 0x800F59E0u, 0);
    R(0) = ld32(base, (R(30) + 20));
    R(6) = (R(30) + 0x10000u);
    R(3) = R(30) |R(30);
    R(4) = (f + 24);
    R(0) = ((int32_t)R(0) * 24);
    R(5) = (f + 16);
    R(7) = (0 + 20);
    R(8) = (0 + 1);
    R(6) = R(6) + R(0);
    R(6) = (R(6) + 24344);
    GM_CALLV(0x800F560Cu, 0x800F5C10u, 0);
    R(0) = ld32(base, (R(30) + 20));
    R(6) = (R(30) + 0x10000u);
    R(3) = R(30) |R(30);
    R(4) = (f + 24);
    R(0) = ((int32_t)R(0) * 24);
    R(5) = (f + 16);
    R(7) = (0 + 20);
    R(8) = (0 + 1);
    R(6) = R(6) + R(0);
    R(6) = (R(6) + 24344);
    GM_CALLV(0x800F5638u, 0x800F5A90u, 0);
    R(5) = ld32(base, (R(30) + 20));
    R(4) = (R(30) + 0x10000u);
    R(3) = R(30) |R(30);
    R(5) = (R(5) + 1);
    st32(base, (R(30) + 20), R(5));
    R(0) = (R(5) + -1);
    R(0) = ((int32_t)R(0) * 24);
    R(4) = R(4) + R(0);
    R(4) = (R(4) + 24344);
    GM_CALLV(0x800F5660u, 0x800F5E60u, 0);
    R(5) = ld32(base, (R(30) + 20));
    R(3) = R(30) |R(30);
    R(4) = (f + 8);
    R(5) = (R(5) + -1);
    GM_CALLV(0x800F5674u, 0x800F5D40u, 0);
L_800F5674:;
    R(31) = (R(31) + 1);
L_800F5678:;
    R(3) = (f + 12);
    GM_CALLV(0x800F5680u, 0x8023B360u, 0);
    cr_cmp_u(ctx, 0, R(31), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F5500; }
    R(0) = lr;
}

/* fn_800F59E0 (fn_800F59E0, 152 bytes) */
static void wm_m_f59e0(GM_CTX) {
    GM_FN(0x800F59E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(3) = R(0) + R(4);
    GM_CALLV(0x800F5A10u, 0x802B9250u, 0);
    st32(base, (R(28) + 12), R(3));
    R(30) = (0 + 0);
    R(31) = (0 + 0);
    goto L_800F5A3C;
L_800F5A20:;
    R(0) = ld32(base, (R(28) + 12));
    R(4) = (0 + 0);
    R(5) = (0 + 5);
    R(3) = R(0) + R(31);
    GM_CALLV(0x800F5A34u, 0x800046B4u, 0);
    R(31) = (R(31) + 5);
    R(30) = (R(30) + 1);
L_800F5A3C:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F5A20; }
    R(3) = (0 + 0x20000u);
    R(4) = (0 + 0);
    R(0) = (R(3) + -31073);
    st32(base, (R(28) + 16), R(4));
    st32(base, (R(28) + 20), R(0));
    R(0) = lr;
}

/* fn_800F5A90 (fn_800F5A90, 384 bytes) */
static void wm_m_f5a90(GM_CTX) {
    GM_FN(0x800F5A90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    cr_cmp_s(ctx, 0, (int32_t)R(8), 0);
    R(24) = R(3) |R(3);
    R(25) = R(4) |R(4);
    R(26) = R(5) |R(5);
    R(30) = R(6) |R(6);
    R(27) = R(7) |R(7);
    R(31) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F5ACC; }
    R(0) = (0 + 0);
    st32(base, (R(13) + -21828), R(0));
L_800F5ACC:;
    R(4) = ld32(base, (R(13) + -21828));
    R(4) = (R(4) + 1);
    st32(base, (R(13) + -21828), R(4));
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(7));
    if ((CR_BIT(ctx, 0))) { goto L_800F5AF0; }
    R(0) = (R(4) + -1);
    st32(base, (R(13) + -21828), R(0));
    R(3) = (0 + 0);
    goto L_800F5BF8;
L_800F5AF0:;
    R(29) = (R(3) + 0x10000u);
    R(28) = (0 + 0);
    R(29) = (R(29) + 20504);
    goto L_800F5BDC;
L_800F5B00:;
    R(3) = R(29) |R(29);
    R(4) = (f + 16);
    GM_CALLV(0x800F5B0Cu, 0x800F9270u, 0);
    R(4) = R(25) |R(25);
    R(3) = (f + 16);
    R(5) = (0 + 4);
    GM_CALLV(0x800F5B1Cu, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5BD4; }
    R(3) = R(29) |R(29);
    R(4) = (f + 8);
    GM_CALLV(0x800F5B30u, 0x800F92C0u, 0);
    R(4) = R(26) |R(26);
    R(3) = (f + 8);
    R(5) = (0 + 4);
    GM_CALLV(0x800F5B40u, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5B60; }
    R(3) = ld32(base, (R(30) + 20));
    R(0) = ld32(base, (R(13) + -21828));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800F5BE8; }
    R(31) = (0 + 1);
    goto L_800F5BE8;
L_800F5B60:;
    R(3) = R(24) |R(24);
    R(5) = R(26) |R(26);
    R(6) = R(30) |R(30);
    R(7) = R(27) |R(27);
    R(4) = (f + 8);
    R(8) = (0 + 0);
    GM_CALLV(0x800F5B7Cu, 0x800F5A90u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F5BD4; }
    R(3) = ld32(base, (R(30) + 16));
    R(4) = (f + 8);
    R(6) = ld32(base, (R(30) + 12));
    R(5) = (0 + 4);
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(0) = R(0) + R(3);
    R(3) = R(6) + R(0);
    GM_CALLV(0x800F5BA4u, 0x802E19F8u, 0);
    R(3) = ld32(base, (R(30) + 16));
    R(5) = (0 + 48);
    R(4) = ld32(base, (R(30) + 12));
    R(31) = (0 + 1);
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(0) = R(0) + R(3);
    R(3) = R(4) + R(0);
    st8(base, (R(3) + 5), R(5));
    R(3) = ld32(base, (R(30) + 16));
    R(0) = (R(3) + 1);
    st32(base, (R(30) + 16), R(0));
    goto L_800F5BE8;
L_800F5BD4:;
    R(29) = (R(29) + 24);
    R(28) = (R(28) + 1);
L_800F5BDC:;
    R(0) = ld32(base, (R(24) + 16));
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F5B00; }
L_800F5BE8:;
    R(4) = ld32(base, (R(13) + -21828));
    R(3) = R(31) |R(31);
    R(0) = (R(4) + -1);
    st32(base, (R(13) + -21828), R(0));
L_800F5BF8:;
    R(11) = (f + 64);
    R(0) = lr;
}

/* fn_800F5C10 (fn_800F5C10, 300 bytes) */
static void wm_m_f5c10(GM_CTX) {
    GM_FN(0x800F5C10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    cr_cmp_s(ctx, 0, (int32_t)R(8), 0);
    R(24) = R(3) |R(3);
    R(25) = R(4) |R(4);
    R(26) = R(5) |R(5);
    R(27) = R(6) |R(6);
    R(28) = R(7) |R(7);
    if ((CR_BIT(ctx, 2))) { goto L_800F5C48; }
    R(0) = (0 + 0);
    st32(base, (R(13) + -21824), R(0));
L_800F5C48:;
    R(4) = ld32(base, (R(13) + -21824));
    R(30) = (0 + 0);
    R(4) = (R(4) + 1);
    st32(base, (R(13) + -21824), R(4));
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(7));
    if ((CR_BIT(ctx, 0))) { goto L_800F5C70; }
    R(0) = (R(4) + -1);
    st32(base, (R(13) + -21824), R(0));
    R(3) = (0 + 0);
    goto L_800F5D24;
L_800F5C70:;
    R(31) = (R(3) + 0x10000u);
    R(29) = (0 + 0);
    R(31) = (R(31) + 20504);
    goto L_800F5D08;
L_800F5C80:;
    R(3) = R(31) |R(31);
    R(4) = (f + 16);
    GM_CALLV(0x800F5C8Cu, 0x800F9270u, 0);
    R(4) = R(25) |R(25);
    R(3) = (f + 16);
    R(5) = (0 + 4);
    GM_CALLV(0x800F5C9Cu, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5D00; }
    R(3) = R(31) |R(31);
    R(4) = (f + 8);
    GM_CALLV(0x800F5CB0u, 0x800F92C0u, 0);
    R(4) = R(26) |R(26);
    R(3) = (f + 8);
    R(5) = (0 + 4);
    GM_CALLV(0x800F5CC0u, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800F5CE4; }
    R(3) = ld32(base, (R(13) + -21824));
    R(0) = ld32(base, (R(27) + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(0), (int32_t)R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_800F5CDC; }
    st32(base, (R(27) + 20), R(3));
L_800F5CDC:;
    R(30) = (0 + 1);
    goto L_800F5D14;
L_800F5CE4:;
    R(3) = R(24) |R(24);
    R(5) = R(26) |R(26);
    R(6) = R(27) |R(27);
    R(7) = R(28) |R(28);
    R(4) = (f + 8);
    R(8) = (0 + 0);
    GM_CALLV(0x800F5D00u, 0x800F5C10u, 0);
L_800F5D00:;
    R(31) = (R(31) + 24);
    R(29) = (R(29) + 1);
L_800F5D08:;
    R(0) = ld32(base, (R(24) + 16));
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F5C80; }
L_800F5D14:;
    R(4) = ld32(base, (R(13) + -21824));
    R(3) = R(30) |R(30);
    R(0) = (R(4) + -1);
    st32(base, (R(13) + -21824), R(0));
L_800F5D24:;
    R(11) = (f + 64);
    R(0) = lr;
}

/* fn_800F5D40 (fn_800F5D40, 280 bytes) */
static void wm_m_f5d40(GM_CTX) {
    GM_FN(0x800F5D40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = ld32(base, (R(4) + 0));
    R(0) = ld32(base, (R(6) + 96));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F5D6C; }
    R(4) = R(6) + R(0);
    goto L_800F5D70;
L_800F5D6C:;
    R(4) = (0 + 0);
L_800F5D70:;
    R(7) = (0 + 0);
    goto L_800F5D94;
L_800F5D78:;
    R(0) = ld32(base, (R(4) + 96));
    R(7) = (R(7) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F5D90; }
    R(4) = R(4) + R(0);
    goto L_800F5D94;
L_800F5D90:;
    R(4) = (0 + 0);
L_800F5D94:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F5D78; }
    R(5) = ((int32_t)R(5) * 24);
    R(0) = (R(3) + 0x10000u);
    R(4) = R(0) + R(5);
    R(0) = ld32(base, (R(4) + 24360));
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { goto L_800F5E40; }
    R(0) = ld32(base, (R(6) + 96));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F5DC8; }
    R(30) = R(6) + R(0);
    goto L_800F5DCC;
L_800F5DC8:;
    R(30) = (0 + 0);
L_800F5DCC:;
    R(3) = R(3) + R(5);
    R(0) = (0 + 0);
    st32(base, (R(4) + 24360), R(0));
    R(31) = (R(3) + 0x10000u);
    goto L_800F5E38;
L_800F5DE0:;
    R(5) = ld32(base, (R(30) + 8));
    R(3) = ld32(base, (R(31) + 24360));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    R(4) = ld32(base, (R(31) + 24356));
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(0) = R(0) + R(3);
    R(3) = R(4) + R(0);
    if ((CR_BIT(ctx, 2))) { goto L_800F5E08; }
    R(4) = R(30) + R(5);
    goto L_800F5E0C;
L_800F5E08:;
    R(4) = (0 + 0);
L_800F5E0C:;
    R(5) = (0 + 5);
    GM_CALLV(0x800F5E14u, 0x802E19F8u, 0);
    R(3) = ld32(base, (R(31) + 24360));
    R(0) = (R(3) + 1);
    st32(base, (R(31) + 24360), R(0));
    R(0) = ld32(base, (R(30) + 96));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F5E34; }
    R(30) = R(30) + R(0);
    goto L_800F5E38;
L_800F5E34:;
    R(30) = (0 + 0);
L_800F5E38:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F5DE0; }
L_800F5E40:;
    R(0) = lr;
}

/* fn_800F5E60 (fn_800F5E60, 176 bytes) */
static void wm_m_f5e60(GM_CTX) {
    GM_FN(0x800F5E60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(28) = ld32(base, (R(4) + 16));
    R(26) = R(4) |R(4);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 1);
    if ((!CR_BIT(ctx, 1))) { goto L_800F5EF8; }
    R(0) = rotl32(R(28), 1) & 0x1u;
    R(27) = (0 + 0);
    R(0) = R(0) + R(28);
    R(31) = (0 + 0);
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0x1u) != 0; R(30) = (v_ >> 1); }
    goto L_800F5EF0;
L_800F5E9C:;
    R(0) = ld32(base, (R(26) + 12));
    R(3) = (R(13) + -21820);
    R(5) = (0 + 5);
    R(4) = R(0) + R(31);
    GM_CALLV(0x800F5EB0u, 0x802E19F8u, 0);
    R(3) = R(28) - R(27);
    R(6) = ld32(base, (R(26) + 12));
    R(4) = (R(3) + -1);
    R(5) = (0 + 5);
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = R(6) + R(31);
    R(29) = R(0) + R(4);
    R(4) = R(6) + R(29);
    GM_CALLV(0x800F5ED4u, 0x802E19F8u, 0);
    R(0) = ld32(base, (R(26) + 12));
    R(4) = (R(13) + -21820);
    R(5) = (0 + 5);
    R(3) = R(0) + R(29);
    GM_CALLV(0x800F5EE8u, 0x802E19F8u, 0);
    R(31) = (R(31) + 5);
    R(27) = (R(27) + 1);
L_800F5EF0:;
    cr_cmp_s(ctx, 0, (int32_t)R(27), (int32_t)R(30));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F5E9C; }
L_800F5EF8:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_800F5F10 (fn_800F5F10, 44 bytes) */
static void wm_m_f5f10(GM_CTX) {
    R(0) = ld8(base, (R(4) + R(5)));
    R(3) = (0 + 0);
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 13);
    if ((!CR_BIT(ctx, 2))) return;
    R(4) = R(5) + R(4);
    R(0) = ld8(base, (R(4) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 10);
    if ((!CR_BIT(ctx, 2))) return;
    R(3) = (0 + 1);
}

/* fn_800F5F40 (fn_800F5F40, 112 bytes) */
static void wm_m_f5f40(GM_CTX) {
    GM_FN(0x800F5F40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24820); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -17176);
    { uint32_t ea_ = (R(2) + -24816); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 23);
    { uint32_t ea_ = (R(2) + -24812); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x800F0000u);
    R(5) = (0 + 0x80370000u);
    st32(base, (R(6) + 12), R(0));
    R(4) = (R(4) + 24496);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    R(5) = (R(5) + 15568);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800F5F98u, 0x802DC780u, 0);
    R(0) = (0 + 38);
    st32(base, (R(13) + -21832), R(0));
    R(0) = lr;
}

/* fn_800F6020 (fn_800F6020, 136 bytes) */
static void wm_m_f6020(GM_CTX) {
    GM_FN(0x800F6020); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(4) = R(3) |R(3);
    R(3) = (0 + 2);
    GM_CALLV(0x800F6044u, 0x80162DB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((!CR_BIT(ctx, 2))) { goto L_800F6060; }
    R(0) = (0 + 0);
    st32(base, (R(30) + 0), R(0));
    R(3) = (0 + 0);
    goto L_800F6090;
L_800F6060:;
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 88));
    ctx->ctr = R(12);
    GM_CALLV(0x800F6070u, ctx->ctr, 0);
    R(0) = (R(3) + -1);
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((CR_BIT(ctx, 1))) { goto L_800F6084; }
    st32(base, (R(30) + 0), R(31));
    goto L_800F608C;
L_800F6084:;
    R(0) = (0 + 0);
    st32(base, (R(30) + 0), R(0));
L_800F608C:;
    R(3) = R(31) |R(31);
L_800F6090:;
    R(0) = lr;
}

/* fn_800F60D0 (fn_800F60D0, 12 bytes) */
static void wm_m_f60d0(GM_CTX) {
    R(0) = (0 + 1);
    st8(base, (R(3) + 313), R(0));
}

/* fn_800F60E0 (fn_800F60E0, 44 bytes) */
static void wm_m_f60e0(GM_CTX) {
    R(4) = ld32(base, (R(13) + -21716));
    R(0) = ld32(base, (R(4) + 428));
    R(4) = ld32(base, (R(4) + 432));
    cr_cmp_u(ctx, 0, R(0), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_800F60FC; }
    cr_cmp_u(ctx, 0, R(4), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_800F6104; }
L_800F60FC:;
    R(3) = (0 + 1);
    return;
L_800F6104:;
    R(3) = (0 + 0);
}

/* fn_800F6110 (fn_800F6110, 24 bytes) */
static void wm_m_f6110(GM_CTX) {
    { uint32_t ea_ = (R(4) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_800F6124; }
    GM_TAIL(0x800F6130u, 0); return;
L_800F6124:;
    GM_TAIL(0x800F6220u, 0); return;
}

/* fn_800F6130 (fn_800F6130, 240 bytes) */
static void wm_m_f6130(GM_CTX) {
    GM_FN(0x800F6130); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -24808); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(6) = R(6) ^ 0x80000000u;
    R(0) = (0 + 0x43300000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -24800); ctx->f[4].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[31].u = ctx->f[2].u;
    ctx->f[2].u = ctx->f[0].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[30].u = ctx->f[1].u;
    st32(base, (f + 28), R(6));
    st32(base, (f + 24), R(0));
    { uint32_t ea_ = (f + 24); ctx->f[1].u = ld64(base, ea_); }
    R(31) = R(3) |R(3);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[1].d - ctx->f[4].d);
    { uint32_t ea_ = (R(5) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[28].d = ctx->ps1[28] = frsp(ctx->f[2].d / ctx->f[29].d);
    { uint32_t ea_ = (R(4) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[4].d * ctx->f[4].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[1].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    GM_CALLV(0x800F61D8u, 0x802BE470u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d / ctx->f[29].d);
    { uint32_t ea_ = (R(31) + 280); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (R(31) + 276); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (R(31) + 236); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (R(31) + 268); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_800F6320 (fn_800F6320, 104 bytes) */
static void wm_m_f6320(GM_CTX) {
    GM_FN(0x800F6320); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = R(5) |R(5);
    { uint32_t ea_ = (R(2) + -24788); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(3) + 360);
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 360); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 364); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (R(3) + 172);
    { uint32_t ea_ = (R(3) + 368); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800F6360u, 0x800F6110u, 0);
    R(3) = (R(31) + 172);
    R(4) = (R(31) + 360);
    GM_CALLV(0x800F636Cu, 0x80160E80u, 0);
    st16(base, (R(31) + 258), R(3));
    st16(base, (R(31) + 264), R(3));
    R(0) = lr;
}

/* fn_800F6390 (fn_800F6390, 124 bytes) */
static void wm_m_f6390(GM_CTX) {
    GM_FN(0x800F6390); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800F63A8u, 0x8006CC00u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800F63B0u, 0x8006CD40u, 0);
    { uint32_t ea_ = (R(31) + 188); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 364); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800F63F4; }
    { uint32_t ea_ = (R(31) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800F63F4; }
    { uint32_t ea_ = (R(31) + 360); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (0 + 1);
    { uint32_t ea_ = (R(31) + 364); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 368); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 172); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(31) + 176); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(31) + 180); stfs(base, ea_, ctx->f[0].d); }
    goto L_800F63F8;
L_800F63F4:;
    R(3) = (0 + 0);
L_800F63F8:;
    R(0) = lr;
}

/* fn_800F6410 (fn_800F6410, 168 bytes) */
static void wm_m_f6410(GM_CTX) {
    GM_FN(0x800F6410); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(4) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 20);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800F6444u, 0x80170980u, 0);
    { uint32_t ea_ = (f + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24784); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800F6490; }
    { uint32_t ea_ = (f + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800F6490; }
    { uint32_t ea_ = (R(2) + -24780); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24776); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
L_800F6490:;
    { uint32_t ea_ = (f + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x800F649Cu, 0x801611C0u, 0);
    st16(base, (R(31) + 258), R(3));
    st16(base, (R(31) + 264), R(3));
    R(0) = lr;
}

/* fn_800F6810 (fn_800F6810, 252 bytes) */
static void wm_m_f6810(GM_CTX) {
    GM_FN(0x800F6810); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + 0);
    ctx->f[31].u = ctx->f[4].u;
    ctx->f[30].u = ctx->f[3].u;
    ctx->f[29].u = ctx->f[2].u;
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(3) + 180); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (int16_t)ld16(base, (R(3) + 258));
    ctx->f[3].u = ctx->f[5].u;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    R(3) = (R(3) + 124);
    ctx->f[2].u = ctx->f[0].u;
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[5].d); }
    st16(base, (f + 22), R(4));
    st16(base, (f + 24), R(0));
    st16(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800F6888u, 0x801C0BD0u, 0);
    R(6) = ld16(base, (f + 24));
    R(3) = (R(31) + 124);
    R(7) = ld16(base, (f + 22));
    R(4) = (f + 8);
    R(0) = ld16(base, (f + 20));
    R(5) = (f + 12);
    st16(base, (f + 16), R(6));
    R(6) = (f + 16);
    st16(base, (f + 12), R(7));
    st16(base, (f + 8), R(0));
    GM_CALLV(0x800F68B4u, 0x8016EF50u, 0);
    R(3) = (R(31) + 344);
    R(4) = (R(31) + 124);
    GM_CALLV(0x800F68C0u, 0x8016A170u, 0);
    ctx->f[1].u = ctx->f[29].u;
    R(3) = (R(31) + 344);
    ctx->f[2].u = ctx->f[30].u;
    ctx->f[3].u = ctx->f[31].u;
    GM_CALLV(0x800F68D4u, 0x8016A130u, 0);
    R(3) = (R(31) + 344);
    R(4) = (0 + 0);
    GM_CALLV(0x800F68E0u, 0x8016A1A0u, 0);
    R(0) = lr;
}

/* fn_800F6910 (fn_800F6910, 12 bytes) */
static void wm_m_f6910(GM_CTX) {
    ctx->f[4].u = ctx->f[2].u;
    { uint32_t ea_ = (R(2) + -24772); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    GM_TAIL(0x800F6810u, 0); return;
}

/* fn_800F6920 (fn_800F6920, 32 bytes) */
static void wm_m_f6920(GM_CTX) {
    R(3) = ld32(base, (R(3) + 356));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) return;
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800F6940 (fn_800F6940, 164 bytes) */
static void wm_m_f6940(GM_CTX) {
    GM_FN(0x800F6940); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(8) = R(6) ^ 0x80000000u;
    { uint32_t ea_ = (R(2) + -24800); ctx->f[4].u = ld64(base, ea_); }
    R(0) = (0 + 0x43300000u);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 8); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    st32(base, (f + 28), R(8));
    ctx->f[6].d = frsp(ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 0); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    st32(base, (f + 24), R(0));
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    R(31) = R(7) |R(7);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[4].d);
    { uint32_t ea_ = (R(4) + 4); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(30) = R(3) |R(3);
    R(4) = (f + 8);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[5].d / ctx->f[0].d);
    st32(base, (R(3) + 384), R(5));
    R(5) = R(6) |R(6);
    { uint32_t ea_ = (R(3) + 372); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 220); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 224); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 228); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 380); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 376); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[7].d); }
    GM_CALLV(0x800F69C4u, 0x800F6320u, 0);
    R(0) = (int16_t)ld16(base, (R(31) + 0));
    st16(base, (R(30) + 258), R(0));
    R(0) = lr;
}

/* fn_800F69F0 (fn_800F69F0, 188 bytes) */
static void wm_m_f69f0(GM_CTX) {
    GM_FN(0x800F69F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[3].u;
    ctx->f[30].u = ctx->f[2].u;
    { uint32_t ea_ = (R(7) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[29].u = ctx->f[1].u;
    { uint32_t ea_ = (R(7) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(31) = R(6) |R(6);
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    GM_CALLV(0x800F6A4Cu, 0x801611C0u, 0);
    ctx->f[1].u = ctx->f[29].u;
    st16(base, (f + 8), R(3));
    ctx->f[2].u = ctx->f[30].u;
    R(3) = R(28) |R(28);
    ctx->f[3].u = ctx->f[31].u;
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    R(6) = R(31) |R(31);
    R(7) = (f + 8);
    GM_CALLV(0x800F6A74u, 0x800F6940u, 0);
    R(0) = lr;
}

/* fn_800F6AB0 (fn_800F6AB0, 156 bytes) */
static void wm_m_f6ab0(GM_CTX) {
    R(4) = ld32(base, (R(3) + 384));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800F6AC8; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 384), R(0));
    goto L_800F6B44;
L_800F6AC8:;
    { uint32_t ea_ = (R(3) + 372); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 376); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24780); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 372); stfs(base, ea_, ctx->f[1].d); }
    if ((!CR_BIT(ctx, 1))) { goto L_800F6B14; }
    { uint32_t ea_ = (R(3) + 380); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800F6B00; }
    { uint32_t ea_ = (R(3) + 220); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 224); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 228); stfs(base, ea_, ctx->f[1].d); }
    goto L_800F6B40;
L_800F6B00:;
    { uint32_t ea_ = (R(3) + 372); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 220); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 224); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 228); stfs(base, ea_, ctx->f[0].d); }
    goto L_800F6B40;
L_800F6B14:;
    { uint32_t ea_ = (R(3) + 380); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800F6B30; }
    { uint32_t ea_ = (R(3) + 220); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 224); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 228); stfs(base, ea_, ctx->f[1].d); }
    goto L_800F6B40;
L_800F6B30:;
    { uint32_t ea_ = (R(3) + 372); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 220); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 224); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 228); stfs(base, ea_, ctx->f[0].d); }
L_800F6B40:;
    GM_TAIL(0x800F6390u, 0); return;
L_800F6B44:;
    R(3) = (0 + 0);
}

/* fn_800F6B50 (fn_800F6B50, 232 bytes) */
static void wm_m_f6b50(GM_CTX) {
    R(0) = (R(6) + -2);
    { uint32_t ea_ = (R(2) + -24780); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_800F6B78; }
    R(0) = (R(6) + -4);
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_800F6BD4; }
    cr_cmp_u(ctx, 0, R(6), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_800F6C30; }
    return;
L_800F6B78:;
    { uint32_t ea_ = (R(4) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[4].d - ctx->f[2].d);
    { uint32_t ea_ = (R(5) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[0].d - ctx->f[4].d);
    { uint32_t ea_ = (R(4) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24768); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].u = ctx->f[5].u & ~0x8000000000000000ull;
    ctx->f[4].u = ctx->f[4].u & ~0x8000000000000000ull;
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[2].d = frsp(ctx->f[5].d);
    ctx->f[3].d = frsp(ctx->f[4].d);
    ctx->f[4].u = ctx->f[6].u & ~0x8000000000000000ull;
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d / ctx->f[2].d);
    ctx->f[2].d = frsp(ctx->f[4].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800F6BC4; }
    ctx->f[6].u = ctx->f[1].u;
L_800F6BC4:;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[6].d * ctx->f[3].d);
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d + ctx->f[1].d);
    return;
L_800F6BD4:;
    { uint32_t ea_ = (R(4) + 0); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[4].d - ctx->f[2].d);
    { uint32_t ea_ = (R(5) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[0].d - ctx->f[4].d);
    { uint32_t ea_ = (R(4) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24768); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].u = ctx->f[5].u & ~0x8000000000000000ull;
    ctx->f[4].u = ctx->f[4].u & ~0x8000000000000000ull;
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[2].d = frsp(ctx->f[5].d);
    ctx->f[3].d = frsp(ctx->f[4].d);
    ctx->f[4].u = ctx->f[6].u & ~0x8000000000000000ull;
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d / ctx->f[2].d);
    ctx->f[2].d = frsp(ctx->f[4].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800F6C20; }
    ctx->f[6].u = ctx->f[1].u;
L_800F6C20:;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[6].d * ctx->f[3].d);
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d + ctx->f[1].d);
    return;
L_800F6C30:;
    { uint32_t ea_ = (R(5) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_800F6C40 (fn_800F6C40, 108 bytes) */
static void wm_m_f6c40(GM_CTX) {
    R(0) = (R(4) + -2);
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 1))) { goto L_800F6C60; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F6C84; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800F6C98; }
    return;
L_800F6C60:;
    { uint32_t ea_ = (R(3) + 236); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24780); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) return;
    { uint32_t ea_ = (R(3) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) return;
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[1].d); }
    return;
L_800F6C84:;
    { uint32_t ea_ = (R(3) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) return;
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[1].d); }
    return;
L_800F6C98:;
    { uint32_t ea_ = (R(3) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) return;
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[1].d); }
}

/* fn_800F6CB0 (fn_800F6CB0, 24 bytes) */
static void wm_m_f6cb0(GM_CTX) {
    { uint32_t ea_ = (R(2) + -24780); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 268); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 276); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 236); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 280); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_800F6D60 (fn_800F6D60, 112 bytes) */
static void wm_m_f6d60(GM_CTX) {
    GM_FN(0x800F6D60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(3) = ld32(base, (R(13) + -21716));
    GM_CALLV(0x800F6D84u, 0x801015E0u, 0);
    R(4) = (0 + 0);
    ctx->ctr = R(31);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800F6DB4; }
    R(0) = R(0) | 0x0u;
L_800F6D98:;
    R(0) = ld32(base, (R(30) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800F6DAC; }
    R(4) = (0 + 1);
    goto L_800F6DB4;
L_800F6DAC:;
    R(30) = (R(30) + 4);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800F6D98; }
L_800F6DB4:;
    R(3) = R(4) |R(4);
    R(0) = lr;
}

/* fn_800F6DD0 (fn_800F6DD0, 12 bytes) */
static void wm_m_f6dd0(GM_CTX) {
    R(0) = (0 + 0);
    st8(base, (R(3) + 313), R(0));
}

/* fn_800F6DE0 (fn_800F6DE0, 8 bytes) */
static void wm_m_f6de0(GM_CTX) {
    R(3) = ld8(base, (R(3) + 313));
}

/* fn_800F6EB0 (fn_800F6EB0, 112 bytes) */
static void wm_m_f6eb0(GM_CTX) {
    GM_FN(0x800F6EB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24764); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -16848);
    { uint32_t ea_ = (R(2) + -24760); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x800F0000u);
    { uint32_t ea_ = (R(2) + -24756); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 28448);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15584);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800F6F08u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21808), R(0));
    R(0) = lr;
}

/* fn_800F9080 (fn_800F9080, 184 bytes) */
static void wm_m_f9080(GM_CTX) {
    GM_FN(0x800F9080); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(30) = (0 + 0x802F0000u);
    R(28) = (0 + 1);
    R(30) = (R(30) + 13248);
    R(27) = (0 + 0);
L_800F90A4:;
    R(3) = ld16(base, (R(30) + 0));
    R(4) = (0 + 0);
    GM_CALLV(0x800F90B0u, 0x80162D50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(29) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800F910C; }
    R(31) = (0 + 0x802F0000u);
    R(30) = rotl32(R(27), 1) & 0xFFFFFFFEu;
    R(31) = (R(31) + 13248);
    goto L_800F9100;
L_800F90CC:;
    R(12) = ld32(base, (R(29) + 96));
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 244));
    ctx->ctr = R(12);
    GM_CALLV(0x800F90E0u, ctx->ctr, 0);
    R(5) = R(28) &R(3);
    R(3) = ld16(base, (R(31) + R(30)));
    R(0) = -(int32_t)R(5);
    R(4) = R(29) |R(29);
    R(0) = R(0) |R(5);
    R(28) = rotl32(R(0), 1) & 0x1u;
    GM_CALLV(0x800F90FCu, 0x80162D50u, 0);
    R(29) = R(3) |R(3);
L_800F9100:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F90CC; }
    goto L_800F911C;
L_800F910C:;
    R(27) = (R(27) + 1);
    R(30) = (R(30) + 2);
    cr_cmp_u(ctx, 0, R(27), 0x5u);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800F90A4; }
L_800F911C:;
    R(11) = (f + 32);
    R(3) = R(28) |R(28);
    R(0) = lr;
}

/* fn_800F91E0 (fn_800F91E0, 112 bytes) */
static void wm_m_f91e0(GM_CTX) {
    GM_FN(0x800F91E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24728); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -16680);
    { uint32_t ea_ = (R(2) + -24724); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24720); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + -28080);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15600);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800F9238u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21800), R(0));
    R(0) = lr;
}

/* GetStartPointNameFromRouteName__6dWmLibFPCcPc (GetStartPointNameFromRouteName__6dWmLibFPCcPc, 68 bytes) */
static void wm_GetStartPointNameFromRouteName__6dWmLibF_f9270(GM_CTX) {
    GM_FN(0x800F9270); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = R(3) |R(3);
    R(5) = (0 + 4);
    R(31) = R(4) |R(4);
    R(3) = R(31) |R(31);
    R(4) = (R(6) + 1);
    GM_CALLV(0x800F9298u, 0x802E19F8u, 0);
    R(0) = (0 + 0);
    st8(base, (R(31) + 4), R(0));
    R(0) = lr;
}

/* GetEndPointNameFromRouteName__6dWmLibFPCcPc (GetEndPointNameFromRouteName__6dWmLibFPCcPc, 68 bytes) */
static void wm_GetEndPointNameFromRouteName__6dWmLibFPC_f92c0(GM_CTX) {
    GM_FN(0x800F92C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = R(3) |R(3);
    R(5) = (0 + 4);
    R(31) = R(4) |R(4);
    R(3) = R(31) |R(31);
    R(4) = (R(6) + 5);
    GM_CALLV(0x800F92E8u, 0x802E19F8u, 0);
    R(0) = (0 + 0);
    st8(base, (R(31) + 4), R(0));
    R(0) = lr;
}

/* fn_800F9310 (fn_800F9310, 96 bytes) */
static void wm_m_f9310(GM_CTX) {
    GM_FN(0x800F9310); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + 82);
    R(31) = R(5) |R(5);
    R(5) = (0 + 4);
    R(30) = R(3) |R(3);
    st8(base, (R(3) + 0), R(0));
    R(3) = (R(3) + 1);
    GM_CALLV(0x800F9340u, 0x802E19F8u, 0);
    R(4) = R(31) |R(31);
    R(3) = (R(30) + 5);
    R(5) = (0 + 4);
    GM_CALLV(0x800F9350u, 0x802E19F8u, 0);
    R(0) = (0 + 0);
    st8(base, (R(30) + 9), R(0));
    R(0) = lr;
}

/* fn_800F9370 (fn_800F9370, 436 bytes) */
static void wm_m_f9370(GM_CTX) {
    GM_FN(0x800F9370); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 9);
    R(0) = (0 + 87);
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    st8(base, (R(5) + 0), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800F93A8; }
    R(0) = (R(3) + 56);
    st8(base, (R(5) + 1), R(0));
    goto L_800F93B0;
L_800F93A8:;
    R(0) = (R(3) + 49);
    st8(base, (R(5) + 1), R(0));
L_800F93B0:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x800F93B8u, 0x800F9840u, 0);
    cr_cmp_u(ctx, 0, R(3), 0xAu);
    if ((CR_BIT(ctx, 1))) { goto L_800F94F8; }
    R(4) = (0 + 0x80320000u);
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + -16192);
    R(4) = ld32(base, (R(4) + R(0)));
    ctx->ctr = R(4);
    { switch (ctx->ctr) { case 0x800F93D8u: goto L_800F93D8; case 0x800F940Cu: goto L_800F940C; case 0x800F9428u: goto L_800F9428; case 0x800F9448u: goto L_800F9448; case 0x800F9464u: goto L_800F9464; case 0x800F9474u: goto L_800F9474; case 0x800F9490u: goto L_800F9490; case 0x800F94ACu: goto L_800F94AC; case 0x800F94C8u: goto L_800F94C8; case 0x800F94E4u: goto L_800F94E4; case 0x800F94F8u: goto L_800F94F8; default: rt_fatal("800F9370: jump table target %08X", ctx->ctr); return; } }
L_800F93D8:;
    R(3) = (0 + 0x66660000u);
    R(4) = (0 + 48);
    R(0) = (R(3) + 26215);
    st8(base, (R(31) + 2), R(4));
    R(0) = (((int64_t)(int32_t)R(0) * (int32_t)R(30)) >> 32);
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0x3u) != 0; R(0) = (v_ >> 2); }
    R(3) = rotl32(R(0), 1) & 0x1u;
    R(0) = R(0) + R(3);
    R(0) = ((int32_t)R(0) * 10);
    R(3) = R(30) - R(0);
    R(0) = (R(3) + 49);
    st8(base, (R(31) + 3), R(0));
    goto L_800F9500;
L_800F940C:;
    R(3) = ld32(base, (R(2) + -24860));
    R(0) = (R(30) + 48);
    R(4) = (0 + 71);
    st8(base, (R(31) + 2), R(4));
    R(0) = R(0) - R(3);
    st8(base, (R(31) + 3), R(0));
    goto L_800F9500;
L_800F9428:;
    R(3) = ld32(base, (R(2) + -24860));
    R(4) = (0 + 84);
    R(0) = (R(30) + 48);
    st8(base, (R(31) + 2), R(4));
    R(3) = (R(3) + 1);
    R(0) = R(0) - R(3);
    st8(base, (R(31) + 3), R(0));
    goto L_800F9500;
L_800F9448:;
    R(3) = ld32(base, (R(2) + -24852));
    R(0) = (R(30) + 48);
    R(4) = (0 + 67);
    st8(base, (R(31) + 2), R(4));
    R(0) = R(0) - R(3);
    st8(base, (R(31) + 3), R(0));
    goto L_800F9500;
L_800F9464:;
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x800F9470u, 0x800F9620u, 0);
    goto L_800F9500;
L_800F9474:;
    R(3) = ld32(base, (R(2) + -24844));
    R(0) = (R(30) + 48);
    R(4) = (0 + 69);
    st8(base, (R(31) + 2), R(4));
    R(0) = R(0) - R(3);
    st8(base, (R(31) + 3), R(0));
    goto L_800F9500;
L_800F9490:;
    R(3) = ld32(base, (R(2) + -24840));
    R(0) = (R(30) + 48);
    R(4) = (0 + 87);
    st8(base, (R(31) + 2), R(4));
    R(0) = R(0) - R(3);
    st8(base, (R(31) + 3), R(0));
    goto L_800F9500;
L_800F94AC:;
    R(3) = ld32(base, (R(2) + -24832));
    R(0) = (R(30) + 48);
    R(4) = (0 + 65);
    st8(base, (R(31) + 2), R(4));
    R(0) = R(0) - R(3);
    st8(base, (R(31) + 3), R(0));
    goto L_800F9500;
L_800F94C8:;
    R(3) = ld32(base, (R(2) + -24828));
    R(0) = (R(30) + 48);
    R(4) = (0 + 83);
    st8(base, (R(31) + 2), R(4));
    R(0) = R(0) - R(3);
    st8(base, (R(31) + 3), R(0));
    goto L_800F9500;
L_800F94E4:;
    R(3) = (0 + 88);
    R(0) = (0 + 48);
    st8(base, (R(31) + 2), R(3));
    st8(base, (R(31) + 3), R(0));
    goto L_800F9500;
L_800F94F8:;
    R(3) = (0 + 0);
    goto L_800F950C;
L_800F9500:;
    R(0) = (0 + 0);
    st8(base, (R(31) + 4), R(0));
    R(3) = (0 + 1);
L_800F950C:;
    R(0) = lr;
}

/* fn_800F9930 (fn_800F9930, 60 bytes) */
static void wm_m_f9930(GM_CTX) {
    GM_FN(0x800F9930); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x800F9940u, 0x800F9840u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(0) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_800F9954; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800F9958; }
L_800F9954:;
    R(0) = (0 + 1);
L_800F9958:;
    R(3) = R(0) |R(0);
    R(0) = lr;
}

/* fn_800F9970 (fn_800F9970, 128 bytes) */
static void wm_m_f9970(GM_CTX) {
    R(4) = ld8(base, (R(3) + 0));
    R(0) = (int8_t)R(4);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 70);
    if ((!CR_BIT(ctx, 2))) { goto L_800F9988; }
    R(3) = (0 + 0);
    return;
L_800F9988:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 75);
    if ((!CR_BIT(ctx, 2))) { goto L_800F9998; }
    R(3) = (0 + 1);
    return;
L_800F9998:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 87);
    if ((!CR_BIT(ctx, 2))) { goto L_800F99B4; }
    R(0) = ld8(base, (R(3) + 2));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 83);
    if ((!CR_BIT(ctx, 2))) { goto L_800F99B4; }
    R(3) = (0 + 2);
    return;
L_800F99B4:;
    R(0) = (int8_t)R(4);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 87);
    if ((!CR_BIT(ctx, 2))) { goto L_800F99E8; }
    R(0) = ld8(base, (R(3) + 2));
    R(0) = (int8_t)R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 88);
    if ((CR_BIT(ctx, 2))) { goto L_800F99E8; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 75);
    if ((CR_BIT(ctx, 2))) { goto L_800F99E8; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 87);
    if ((CR_BIT(ctx, 2))) { goto L_800F99E8; }
    R(3) = (0 + 3);
    return;
L_800F99E8:;
    R(3) = (0 + 4);
}

/* fn_800F9BE0 (fn_800F9BE0, 100 bytes) */
static void wm_m_f9be0(GM_CTX) {
    GM_FN(0x800F9BE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(4) = (0 + 0);
    R(30) = R(3) |R(3);
L_800F9C00:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x800F9C08u, 0x80162D50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(4) = R(3) |R(3);
    if ((!CR_BIT(ctx, 2))) { goto L_800F9C1C; }
    R(3) = (0 + 0);
    goto L_800F9C2C;
L_800F9C1C:;
    R(0) = ld32(base, (R(3) + 4));
    R(0) = rotl32(R(0), 24) & 0xFFu;
    cr_cmp_s(ctx, 0, (int32_t)R(31), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F9C00; }
L_800F9C2C:;
    R(0) = lr;
}

/* fn_800F9C50 (fn_800F9C50, 124 bytes) */
static void wm_m_f9c50(GM_CTX) {
    GM_FN(0x800F9C50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
L_800F9C74:;
    R(3) = R(29) |R(29);
    R(4) = R(31) |R(31);
    GM_CALLV(0x800F9C80u, 0x80162D50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800F9CAC; }
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 112));
    ctx->ctr = R(12);
    GM_CALLV(0x800F9C9Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), (int32_t)R(3));
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800F9C74; }
    R(3) = R(31) |R(31);
    goto L_800F9CB0;
L_800F9CAC:;
    R(3) = (0 + 0);
L_800F9CB0:;
    R(0) = lr;
}

/* fn_800F9CD0 (fn_800F9CD0, 84 bytes) */
static void wm_m_f9cd0(GM_CTX) {
    GM_FN(0x800F9CD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = (0 + 0);
    GM_CALLV(0x800F9CF4u, 0x80164B20u, 0);
    st32(base, (f + 8), R(3));
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    R(3) = (f + 8);
    GM_CALLV(0x800F9D08u, 0x80253ED0u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_800F9DB0 (fn_800F9DB0, 240 bytes) */
static void wm_m_f9db0(GM_CTX) {
    GM_FRAME(48); gptr f = gm_frame_sp;
    R(0) = (0 + 0x43300000u);
    { uint32_t ea_ = (R(2) + -24688); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    R(7) = ld32(base, (R(13) + -20992));
    { uint32_t ea_ = (R(2) + -24684); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(7) = ld32(base, (R(7) + 0));
    st32(base, (f + 24), R(0));
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[5].d - ctx->f[6].d);
    R(7) = ld16(base, (R(7) + 4));
    st32(base, (f + 28), R(7));
    { uint32_t ea_ = (R(2) + -24696); ctx->f[11].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    st32(base, (f + 32), R(0));
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[11].d);
    { uint32_t ea_ = (R(2) + -24704); ctx->f[10].d = ctx->ps1[10] = ldfs(base, ea_); }
    st32(base, (f + 36), R(7));
    { uint32_t ea_ = (R(4) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[10].d * ctx->f[2].d);
    { uint32_t ea_ = (f + 32); ctx->f[0].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(6) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[0].d - ctx->f[11].d);
    { uint32_t ea_ = (R(5) + 0); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[1].d - ctx->f[9].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[4].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[5].d); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[10].d * ctx->f[8].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[9].d / ctx->f[8].d);
    { uint32_t ea_ = (R(6) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[8].d); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[8].d - ctx->f[6].d);
    R(4) = ld32(base, (R(13) + -20992));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    R(4) = ld32(base, (R(4) + 0));
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[5].d * ctx->f[2].d);
    R(0) = ld16(base, (R(4) + 6));
    st32(base, (f + 28), R(0));
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d / ctx->f[3].d);
    { uint32_t ea_ = (f + 24); ctx->f[8].u = ld64(base, ea_); }
    st32(base, (f + 36), R(0));
    { uint32_t ea_ = (f + 32); ctx->f[5].u = ld64(base, ea_); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[8].d - ctx->f[11].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d + ctx->f[2].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[5].d - ctx->f[11].d);
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[10].d * ctx->f[8].d);
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[10].d * ctx->f[5].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[7].d - ctx->f[8].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d / ctx->f[4].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[6].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_800F9EA0 (fn_800F9EA0, 108 bytes) */
static void wm_m_f9ea0(GM_CTX) {
    GM_FN(0x800F9EA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(6) |R(6);
    R(30) = R(5) |R(5);
    R(29) = R(3) |R(3);
    R(3) = (f + 16);
    GM_CALLV(0x800F9ECCu, 0x800F9CD0u, 0);
    { uint32_t ea_ = (f + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(29) |R(29);
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = R(30) |R(30);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    R(6) = R(31) |R(31);
    R(4) = (f + 8);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x800F9EF0u, 0x800F9DB0u, 0);
    R(0) = lr;
}

/* GetOpenStatus__6dWmLibFii (GetOpenStatus__6dWmLibFii, 32 bytes) */
static void wm_GetOpenStatus__6dWmLibFii_fa330(GM_CTX) {
    R(6) = ld32(base, (R(13) + -21748));
    R(5) = (0 + 0x10000u);
    R(0) = (R(5) + 25880);
    R(5) = ld32(base, (R(6) + 13196));
    R(0) = ((int32_t)R(5) * (int32_t)R(0));
    R(5) = R(6) + R(0);
    R(5) = (R(5) + 13204);
    GM_TAIL(0x800FA350u, 0); return;
}

/* fn_800FA350 (fn_800FA350, 648 bytes) */
static void wm_m_fa350(GM_CTX) {
    GM_FN(0x800FA350); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 80);
    R(28) = R(3) & 0xFFu;
    R(18) = R(3) |R(3);
    R(19) = R(5) |R(5);
    R(20) = R(4) |R(4);
    R(3) = R(28) |R(28);
    R(5) = (f + 8);
    GM_CALLV(0x800FA380u, 0x800F9370u, 0);
    R(3) = ld32(base, (R(13) + -22080));
    R(4) = (0 + -1);
    GM_CALLV(0x800FA38Cu, 0x800E0380u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(20), 0);
    R(27) = R(3) |R(3);
    R(26) = (0 + 0);
    if ((CR_BIT(ctx, 1))) { goto L_800FA3B0; }
    R(3) = (0 + 0);
    R(4) = (0 + 2);
    GM_CALLV(0x800FA3A8u, 0x800FA5E0u, 0);
    R(26) = R(3) |R(3);
    goto L_800FA5BC;
L_800FA3B0:;
    R(25) = (0 + 0);
    R(24) = (0 + 0);
    R(23) = (0 + 0);
L_800FA3BC:;
    R(4) = R(23) |R(23);
    R(5) = R(19) |R(19);
    R(3) = (f + 8);
    GM_CALLV(0x800FA3CCu, 0x800FA630u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(29) = R(3) |R(3);
    if ((!CR_BIT(ctx, 1))) { goto L_800FA3DC; }
    R(24) = (0 + 1);
L_800FA3DC:;
    R(22) = (0 + 0);
    R(21) = (0 + 0);
    goto L_800FA588;
L_800FA3E8:;
    R(4) = R(23) |R(23);
    R(5) = R(22) |R(22);
    R(6) = R(19) |R(19);
    R(3) = (f + 8);
    GM_CALLV(0x800FA3FCu, 0x800FA6C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(22) = R(3) |R(3);
    R(30) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA440; }
    R(3) = R(19) |R(19);
    R(4) = R(22) |R(22);
    GM_CALLV(0x800FA418u, 0x800F56B0u, 0);
    GM_CALLV(0x800FA41Cu, 0x800F9530u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 38);
    if ((CR_BIT(ctx, 2))) { goto L_800FA42C; }
    R(30) = (0 + 1);
    goto L_800FA448;
L_800FA42C:;
    R(3) = R(26) |R(26);
    R(4) = (0 + 2);
    GM_CALLV(0x800FA438u, 0x800FA5E0u, 0);
    R(26) = R(3) |R(3);
    goto L_800FA448;
L_800FA440:;
    if ((!CR_BIT(ctx, 1))) { goto L_800FA448; }
    R(30) = (0 + 1);
L_800FA448:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA580; }
    R(3) = R(19) |R(19);
    R(4) = R(22) |R(22);
    GM_CALLV(0x800FA45Cu, 0x800F56B0u, 0);
    GM_CALLV(0x800FA460u, 0x800F9530u, 0);
    R(20) = R(3) |R(3);
    R(3) = R(28) |R(28);
    R(4) = R(20) |R(20);
    GM_CALLV(0x800FA470u, 0x800FA8C0u, 0);
    R(30) = R(3) |R(3);
    R(3) = R(28) |R(28);
    R(4) = R(20) |R(20);
    R(5) = R(22) |R(22);
    GM_CALLV(0x800FA484u, 0x800FA9C0u, 0);
    R(31) = R(3) |R(3);
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(5) = R(20) |R(20);
    GM_CALLV(0x800FA498u, 0x800CE3A0u, 0);
    R(0) = (R(30) + -1);
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((CR_BIT(ctx, 1))) { goto L_800FA580; }
    cr_cmp_s(ctx, 0, (int32_t)R(23), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA520; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA4C8; }
    R(3) = R(18) |R(18);
    R(4) = R(20) |R(20);
    GM_CALLV(0x800FA4C0u, 0x800FB150u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA4D0; }
L_800FA4C8:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA4E4; }
L_800FA4D0:;
    R(3) = R(26) |R(26);
    R(4) = (0 + 1);
    GM_CALLV(0x800FA4DCu, 0x800FA5E0u, 0);
    R(26) = R(3) |R(3);
    goto L_800FA57C;
L_800FA4E4:;
    R(3) = R(18) |R(18);
    R(4) = R(20) |R(20);
    GM_CALLV(0x800FA4F0u, 0x800FB1F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA50C; }
    R(3) = R(18) |R(18);
    R(4) = R(20) |R(20);
    GM_CALLV(0x800FA504u, 0x800FB150u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA57C; }
L_800FA50C:;
    R(3) = R(26) |R(26);
    R(4) = (0 + 3);
    GM_CALLV(0x800FA518u, 0x800FA5E0u, 0);
    R(26) = R(3) |R(3);
    goto L_800FA57C;
L_800FA520:;
    cr_cmp_s(ctx, 0, (int32_t)R(23), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA57C; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA544; }
    R(3) = R(26) |R(26);
    R(4) = (0 + 1);
    GM_CALLV(0x800FA53Cu, 0x800FA5E0u, 0);
    R(26) = R(3) |R(3);
    goto L_800FA57C;
L_800FA544:;
    R(3) = R(18) |R(18);
    R(4) = R(20) |R(20);
    GM_CALLV(0x800FA550u, 0x800FB240u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA56C; }
    R(3) = R(18) |R(18);
    R(4) = R(20) |R(20);
    GM_CALLV(0x800FA564u, 0x800FB1A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA57C; }
L_800FA56C:;
    R(3) = R(26) |R(26);
    R(4) = (0 + 3);
    GM_CALLV(0x800FA578u, 0x800FA5E0u, 0);
    R(26) = R(3) |R(3);
L_800FA57C:;
    R(25) = (0 + 1);
L_800FA580:;
    R(22) = (R(22) + 1);
    R(21) = (R(21) + 1);
L_800FA588:;
    cr_cmp_s(ctx, 0, (int32_t)R(21), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FA3E8; }
    R(23) = (R(23) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(23), 2);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FA3BC; }
    cr_cmp_s(ctx, 0, (int32_t)R(25), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA5BC; }
    cr_cmp_s(ctx, 0, (int32_t)R(24), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA5BC; }
    R(3) = R(26) |R(26);
    R(4) = (0 + 2);
    GM_CALLV(0x800FA5B8u, 0x800FA5E0u, 0);
    R(26) = R(3) |R(3);
L_800FA5BC:;
    R(11) = (f + 80);
    R(3) = R(26) |R(26);
    R(0) = lr;
}

/* fn_800FA5E0 (fn_800FA5E0, 60 bytes) */
static void wm_m_fa5e0(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA604; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800FA60C; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((CR_BIT(ctx, 2))) return;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 2))) return;
    return;
L_800FA604:;
    R(3) = R(4) |R(4);
    return;
L_800FA60C:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    if ((!CR_BIT(ctx, 1))) return;
    R(3) = R(4) |R(4);
}

/* fn_800FA630 (fn_800FA630, 136 bytes) */
static void wm_m_fa630(GM_CTX) {
    GM_FN(0x800FA630); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0);
    R(30) = R(5) |R(5);
    R(6) = R(30) |R(30);
    R(5) = (0 + 0);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    GM_CALLV(0x800FA668u, 0x800FA6C0u, 0);
    R(5) = R(3) |R(3);
    goto L_800FA68C;
L_800FA670:;
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(6) = R(30) |R(30);
    R(5) = (R(5) + 1);
    R(31) = (R(31) + 1);
    GM_CALLV(0x800FA688u, 0x800FA6C0u, 0);
    R(5) = R(3) |R(3);
L_800FA68C:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FA670; }
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_800FA6C0 (fn_800FA6C0, 280 bytes) */
static void wm_m_fa6c0(GM_CTX) {
    GM_FN(0x800FA6C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(0) = cntlzw(R(4));
    R(26) = R(3) |R(3);
    R(29) = R(5) |R(5);
    R(27) = R(6) |R(6);
    R(31) = rotl32(R(0), 27) & 0x7FFFFFFu;
    R(30) = (0 + -1);
    goto L_800FA7B0;
L_800FA6F0:;
    R(28) = (0 + 0);
    goto L_800FA72C;
L_800FA6F8:;
    R(3) = R(27) |R(27);
    R(4) = R(31) |R(31);
    R(5) = R(29) |R(29);
    R(6) = R(28) |R(28);
    GM_CALLV(0x800FA70Cu, 0x800F56C0u, 0);
    R(4) = R(26) |R(26);
    R(5) = (0 + 4);
    GM_CALLV(0x800FA718u, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA728; }
    R(30) = R(29) |R(29);
    goto L_800FA744;
L_800FA728:;
    R(28) = (R(28) + 1);
L_800FA72C:;
    R(3) = R(27) |R(27);
    R(4) = R(31) |R(31);
    R(5) = R(29) |R(29);
    GM_CALLV(0x800FA73Cu, 0x800F5700u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FA6F8; }
L_800FA744:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800FA7A4; }
    R(28) = (0 + 0);
    goto L_800FA78C;
L_800FA754:;
    R(3) = R(27) |R(27);
    R(4) = R(31) |R(31);
    R(5) = R(29) |R(29);
    R(6) = R(28) |R(28);
    GM_CALLV(0x800FA768u, 0x800F5730u, 0);
    R(4) = R(26) |R(26);
    R(5) = (0 + 4);
    R(3) = (R(3) + 5);
    GM_CALLV(0x800FA778u, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA788; }
    R(30) = R(29) |R(29);
    goto L_800FA7A4;
L_800FA788:;
    R(28) = (R(28) + 1);
L_800FA78C:;
    R(3) = R(27) |R(27);
    R(4) = R(31) |R(31);
    R(5) = R(29) |R(29);
    GM_CALLV(0x800FA79Cu, 0x800F5770u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FA754; }
L_800FA7A4:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800FA7BC; }
    R(29) = (R(29) + 1);
L_800FA7B0:;
    R(0) = ld32(base, (R(27) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FA6F0; }
L_800FA7BC:;
    R(11) = (f + 32);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* GetClearStatus__6dWmLibFii (GetClearStatus__6dWmLibFii, 248 bytes) */
static void wm_GetClearStatus__6dWmLibFii_fa8c0(GM_CTX) {
    GM_FN(0x800FA8C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) & 0xFFu;
    R(30) = R(4) & 0xFFu;
    R(4) = (0 + -1);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FA8ECu, 0x800E0380u, 0);
    R(4) = R(31) |R(31);
    R(5) = R(30) |R(30);
    GM_CALLV(0x800FA8F8u, 0x800CE3A0u, 0);
    R(5) = rotl32(R(3), 28) & 0x1u;
    CR0(ctx, R(5));
    R(4) = rotl32(R(3), 27) & 0x1u;
    R(0) = rotl32(R(3), 25) & 0x1u;
    R(29) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA91C; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA91C; }
    R(29) = (0 + 2);
    goto L_800FA978;
L_800FA91C:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA93C; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA934; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA93C; }
L_800FA934:;
    R(29) = (0 + 1);
    goto L_800FA978;
L_800FA93C:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA95C; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA95C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA95C; }
    R(29) = (0 + 3);
    goto L_800FA978;
L_800FA95C:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA978; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA978; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA978; }
    R(29) = (0 + 4);
L_800FA978:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FA998; }
    R(3) = R(31) |R(31);
    R(4) = R(30) |R(30);
    GM_CALLV(0x800FA98Cu, 0x800FB1A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FA998; }
    R(29) = (0 + 3);
L_800FA998:;
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* GetCurrentPlayResultStatus__6dWmLibFiii (GetCurrentPlayResultStatus__6dWmLibFiii, 420 bytes) */
static void wm_GetCurrentPlayResultStatus__6dWmLibFiii_fa9c0(GM_CTX) {
    GM_FN(0x800FA9C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(30) = R(3) & 0xFFu;
    R(31) = ld32(base, (R(13) + -22276));
    R(29) = R(4) & 0xFFu;
    R(3) = ld32(base, (R(13) + -22080));
    R(27) = R(5) |R(5);
    R(4) = (0 + -1);
    GM_CALLV(0x800FA9F0u, 0x800E0380u, 0);
    R(4) = R(30) |R(30);
    R(5) = R(29) |R(29);
    GM_CALLV(0x800FA9FCu, 0x800CE3A0u, 0);
    R(0) = ld32(base, (R(31) + 68));
    R(3) = R(27) & 0xFFu;
    R(28) = ld32(base, (R(31) + 96));
    R(27) = (0 + 9);
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800FAB44; }
    R(0) = ld32(base, (R(31) + 84));
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800FAB44; }
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAA30; }
    R(27) = (0 + 0);
    goto L_800FAA88;
L_800FAA30:;
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FAA3Cu, 0x800FB1F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAA58; }
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FAA50u, 0x800FB240u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FAA88; }
L_800FAA58:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAA68; }
    R(27) = (0 + 2);
    goto L_800FAA88;
L_800FAA68:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAA78; }
    R(27) = (0 + 3);
    goto L_800FAA88;
L_800FAA78:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 1);
    R(27) = (0 + 5);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAA88; }
    R(27) = (0 + 6);
L_800FAA88:;
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FAA94u, 0x800FB150u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FAAFC; }
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FAAA8u, 0x800FB1F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAAFC; }
    cr_cmp_s(ctx, 0, (int32_t)R(28), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAAC0; }
    R(27) = (0 + 4);
    goto L_800FAAFC;
L_800FAAC0:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAAD0; }
    R(27) = (0 + 7);
    goto L_800FAAFC;
L_800FAAD0:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAAE0; }
    R(27) = (0 + 6);
    goto L_800FAAFC;
L_800FAAE0:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAAF0; }
    R(27) = (0 + 3);
    goto L_800FAAFC;
L_800FAAF0:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 5);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAAFC; }
    R(27) = (0 + 5);
L_800FAAFC:;
    cr_cmp_s(ctx, 0, (int32_t)R(27), 9);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAB48; }
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FAB10u, 0x800FB240u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAB3C; }
    R(3) = R(30) |R(30);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FAB24u, 0x800FB1A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FAB3C; }
    cr_cmp_s(ctx, 0, (int32_t)R(28), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAB3C; }
    R(27) = (0 + 3);
    goto L_800FAB48;
L_800FAB3C:;
    R(27) = (0 + 1);
    goto L_800FAB48;
L_800FAB44:;
    R(27) = (0 + 8);
L_800FAB48:;
    R(11) = (f + 32);
    R(3) = R(27) |R(27);
    R(0) = lr;
}

/* IsCourseOmoteClear__6dWmLibFii (IsCourseOmoteClear__6dWmLibFii, 68 bytes) */
static void wm_IsCourseOmoteClear__6dWmLibFii_fad60(GM_CTX) {
    GM_FN(0x800FAD60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x800FAD70u, 0x800FA8C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800FAD88; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800FAD88; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAD90; }
L_800FAD88:;
    R(3) = (0 + 1);
    goto L_800FAD94;
L_800FAD90:;
    R(3) = (0 + 0);
L_800FAD94:;
    R(0) = lr;
}

/* IsCourseUraClear__6dWmLibFii (IsCourseUraClear__6dWmLibFii, 92 bytes) */
static void wm_IsCourseUraClear__6dWmLibFii_fadb0(GM_CTX) {
    GM_FN(0x800FADB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    GM_CALLV(0x800FADD0u, 0x800FA8C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800FADE0; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FADE8; }
L_800FADE0:;
    R(3) = (0 + 1);
    goto L_800FADF4;
L_800FADE8:;
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x800FADF4u, 0x800FB1A0u, 0);
L_800FADF4:;
    R(0) = lr;
}

/* IsCourseClear__6dWmLibFii (IsCourseClear__6dWmLibFii, 60 bytes) */
static void wm_IsCourseClear__6dWmLibFii_fae40(GM_CTX) {
    GM_FN(0x800FAE40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x800FAE50u, 0x800FA8C0u, 0);
    R(4) = (R(3) + -1);
    R(3) = (0 + 3);
    { uint32_t a_ = R(4); R(0) = 0x3u - a_; ctx->xer_ca = 0x3u >= a_; }
    R(3) = R(3) | ~R(4);
    R(0) = rotl32(R(0), 31) & 0x7FFFFFFFu;
    R(0) = R(3) - R(0);
    R(3) = rotl32(R(0), 1) & 0x1u;
    R(0) = lr;
}

/* IsCourseFirstOmoteClear__6dWmLibFiii (IsCourseFirstOmoteClear__6dWmLibFiii, 240 bytes) */
static void wm_IsCourseFirstOmoteClear__6dWmLibFiii_fae80(GM_CTX) {
    GM_FN(0x800FAE80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(4) = (0 + -1);
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FAEB0u, 0x800E0380u, 0);
    R(4) = ld32(base, (R(13) + -22276));
    R(0) = ld32(base, (R(4) + 80));
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FAEC8; }
    R(3) = (0 + 0);
    goto L_800FAF54;
L_800FAEC8:;
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    GM_CALLV(0x800FAED4u, 0x800CE3A0u, 0);
    R(0) = R(3) & 0x10u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FAEEC; }
    R(0) = R(3) & 0x80u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FAEEC; }
    R(3) = (0 + 0);
    goto L_800FAF54;
L_800FAEEC:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800FAEFC; }
    R(3) = ld32(base, (R(13) + -22276));
    R(31) = ld32(base, (R(3) + 68));
L_800FAEFC:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    GM_CALLV(0x800FAF0Cu, 0x800FA9C0u, 0);
    R(31) = R(3) |R(3);
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    GM_CALLV(0x800FAF1Cu, 0x800FB1F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FAF2C; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800FAF48; }
L_800FAF2C:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    GM_CALLV(0x800FAF38u, 0x800FB150u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FAF50; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAF50; }
L_800FAF48:;
    R(3) = (0 + 1);
    goto L_800FAF54;
L_800FAF50:;
    R(3) = (0 + 0);
L_800FAF54:;
    R(0) = lr;
}

/* IsCourseFirstUraClear__6dWmLibFiii (IsCourseFirstUraClear__6dWmLibFiii, 204 bytes) */
static void wm_IsCourseFirstUraClear__6dWmLibFiii_faf70(GM_CTX) {
    GM_FN(0x800FAF70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(6) = ld32(base, (R(13) + -22276));
    R(0) = ld32(base, (R(6) + 80));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FAFAC; }
    R(3) = (0 + 0);
    goto L_800FB020;
L_800FAFAC:;
    GM_CALLV(0x800FAFB0u, 0x800FADB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FB01C; }
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    GM_CALLV(0x800FAFC8u, 0x800FA9C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FAFD8; }
    R(3) = (0 + 1);
    goto L_800FB020;
L_800FAFD8:;
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    GM_CALLV(0x800FAFE4u, 0x800FB1A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FB01C; }
    R(3) = ld32(base, (R(13) + -22276));
    R(0) = ld32(base, (R(3) + 96));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB01C; }
    R(0) = ld32(base, (R(3) + 84));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB01C; }
    R(0) = ld32(base, (R(3) + 80));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB01C; }
    R(3) = (0 + 1);
    goto L_800FB020;
L_800FB01C:;
    R(3) = (0 + 0);
L_800FB020:;
    R(0) = lr;
}

/* IsCourseFirstClear__6dWmLibFii (IsCourseFirstClear__6dWmLibFii, 260 bytes) */
static void wm_IsCourseFirstClear__6dWmLibFii_fb040(GM_CTX) {
    GM_FN(0x800FB040); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    R(5) = ld32(base, (R(13) + -22276));
    R(0) = ld32(base, (R(5) + 80));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FB07C; }
    R(3) = (0 + 0);
    goto L_800FB124;
L_800FB07C:;
    R(3) = ld32(base, (R(13) + -22080));
    R(4) = (0 + -1);
    GM_CALLV(0x800FB088u, 0x800E0380u, 0);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    GM_CALLV(0x800FB094u, 0x800CE3A0u, 0);
    R(5) = ld32(base, (R(13) + -22276));
    R(31) = R(3) |R(3);
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = ld32(base, (R(5) + 68));
    GM_CALLV(0x800FB0ACu, 0x800FA9C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    R(30) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB0DC; }
    R(0) = R(31) & 0x80u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800FB120; }
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FB0CCu, 0x800FADB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB120; }
    R(30) = (0 + 1);
    goto L_800FB120;
L_800FB0DC:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB100; }
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FB0F0u, 0x800FAD60u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB120; }
    R(30) = (0 + 1);
    goto L_800FB120;
L_800FB100:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB120; }
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FB114u, 0x800FAE10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FB120; }
    R(30) = (0 + 1);
L_800FB120:;
    R(3) = R(30) |R(30);
L_800FB124:;
    R(0) = lr;
}

/* IsCourseOtasukeClearSimple__6dWmLibFii (IsCourseOtasukeClearSimple__6dWmLibFii, 80 bytes) */
static void wm_IsCourseOtasukeClearSimple__6dWmLibFii_fb150(GM_CTX) {
    GM_FN(0x800FB150); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(4) = (0 + -1);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FB178u, 0x800E0380u, 0);
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    R(6) = (0 + 128);
    GM_CALLV(0x800FB188u, 0x800CE3C0u, 0);
    R(0) = lr;
}

/* IsCourseUraOtasukeClearSimple__6dWmLibFii (IsCourseUraOtasukeClearSimple__6dWmLibFii, 80 bytes) */
static void wm_IsCourseUraOtasukeClearSimple__6dWmLibFi_fb1a0(GM_CTX) {
    GM_FN(0x800FB1A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(4) = (0 + -1);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FB1C8u, 0x800E0380u, 0);
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    R(6) = (0 + 256);
    GM_CALLV(0x800FB1D8u, 0x800CE3C0u, 0);
    R(0) = lr;
}

/* IsCourseOmoteClearSimple__6dWmLibFii (IsCourseOmoteClearSimple__6dWmLibFii, 80 bytes) */
static void wm_IsCourseOmoteClearSimple__6dWmLibFii_fb1f0(GM_CTX) {
    GM_FN(0x800FB1F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(4) = (0 + -1);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FB218u, 0x800E0380u, 0);
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    R(6) = (0 + 16);
    GM_CALLV(0x800FB228u, 0x800CE3C0u, 0);
    R(0) = lr;
}

/* IsCourseUraClearSimple__6dWmLibFii (IsCourseUraClearSimple__6dWmLibFii, 80 bytes) */
static void wm_IsCourseUraClearSimple__6dWmLibFii_fb240(GM_CTX) {
    GM_FN(0x800FB240); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(4) = (0 + -1);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FB268u, 0x800E0380u, 0);
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    R(6) = (0 + 32);
    GM_CALLV(0x800FB278u, 0x800CE3C0u, 0);
    R(0) = lr;
}

/* IsCourseFailed__6dWmLibFiii (IsCourseFailed__6dWmLibFiii, 60 bytes) */
static void wm_IsCourseFailed__6dWmLibFiii_fb290(GM_CTX) {
    GM_FN(0x800FB290); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x800FB2A0u, 0x800FA9C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800FB2B0; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 6);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB2B8; }
L_800FB2B0:;
    R(3) = (0 + 1);
    goto L_800FB2BC;
L_800FB2B8:;
    R(3) = (0 + 0);
L_800FB2BC:;
    R(0) = lr;
}

/* fn_800FB2D0 (fn_800FB2D0, 80 bytes) */
static void wm_m_fb2d0(GM_CTX) {
    GM_FN(0x800FB2D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + -1);
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FB2F0u, 0x800E0380u, 0);
    R(4) = R(31) |R(31);
    R(5) = (0 + 1);
    GM_CALLV(0x800FB2FCu, 0x800CE350u, 0);
    R(3) = R(3) & 0xFFu;
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(3) = rotl32(R(0), 1) & 0x1u;
    R(0) = lr;
}

/* getStartPointKinokoHouseKindNum__6dWmLibFv (getStartPointKinokoHouseKindNum__6dWmLibFv, 48 bytes) */
static void wm_getStartPointKinokoHouseKindNum__6dWmLib_fb350(GM_CTX) {
    GM_FN(0x800FB350); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + -1);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FB368u, 0x800E0380u, 0);
    R(4) = ld8(base, (R(13) + -21555));
    GM_CALLV(0x800FB370u, 0x800CE250u, 0);
    R(0) = lr;
}

/* fn_800FB4B0 (fn_800FB4B0, 440 bytes) */
static void wm_m_fb4b0(GM_CTX) {
    GM_FN(0x800FB4B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 96);
    R(6) = (0 + 109);
    R(0) = (0 + 116);
    R(25) = R(3) |R(3);
    R(27) = R(5) |R(5);
    st8(base, (f + 36), R(6));
    R(26) = R(4) |R(4);
    R(3) = (f + 38);
    R(5) = (0 + 9);
    st8(base, (f + 37), R(0));
    GM_CALLV(0x800FB4ECu, 0x802E19F8u, 0);
    R(0) = (0 + 97);
    R(31) = (0 + 0);
    st8(base, (f + 47), R(0));
    R(3) = R(25) |R(25);
    R(4) = (f + 36);
    st8(base, (f + 48), R(31));
    GM_CALLV(0x800FB508u, 0x800F11C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FB528; }
    R(3) = R(27) |R(27);
    R(4) = (f + 36);
    R(5) = (0 + 14);
    GM_CALLV(0x800FB520u, 0x802E19F8u, 0);
    R(3) = (0 + 1);
    goto L_800FB650;
L_800FB528:;
    st8(base, (R(27) + 0), R(31));
    R(29) = (0 + 0);
    R(30) = (0 + 48);
L_800FB534:;
    st8(base, (f + 48), R(30));
    R(3) = R(25) |R(25);
    R(4) = (f + 36);
    st8(base, (f + 49), R(31));
    GM_CALLV(0x800FB548u, 0x800F11C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FB63C; }
    R(3) = R(26) |R(26);
    R(4) = (f + 16);
    GM_CALLV(0x800FB55Cu, 0x800F92C0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(29) |R(29);
    R(5) = (f + 24);
    GM_CALLV(0x800FB56Cu, 0x800FB6C0u, 0);
    R(31) = R(3) |R(3);
    R(3) = (f + 24);
    R(4) = (f + 8);
    GM_CALLV(0x800FB57Cu, 0x800F9270u, 0);
    R(3) = (f + 8);
    GM_CALLV(0x800FB584u, 0x800F9530u, 0);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(25) + 2004));
    R(4) = R(30) |R(30);
    GM_CALLV(0x800FB594u, 0x800FA8C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    R(28) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB5D0; }
    R(3) = ld32(base, (R(25) + 2004));
    R(4) = R(30) |R(30);
    GM_CALLV(0x800FB5ACu, 0x800FAD60u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FB604; }
    R(0) = ld8(base, (f + 47));
    R(5) = R(29) |R(29);
    R(3) = (f + 24);
    R(4) = (int8_t)R(0);
    GM_CALLV(0x800FB5C8u, 0x800FB900u, 0);
    R(28) = R(3) |R(3);
    goto L_800FB604;
L_800FB5D0:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB604; }
    R(3) = ld32(base, (R(25) + 2004));
    R(4) = R(30) |R(30);
    GM_CALLV(0x800FB5E4u, 0x800FADB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FB604; }
    R(0) = ld8(base, (f + 47));
    R(5) = R(29) |R(29);
    R(3) = (f + 24);
    R(4) = (int8_t)R(0);
    GM_CALLV(0x800FB600u, 0x800FB900u, 0);
    R(28) = R(3) |R(3);
L_800FB604:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FB624; }
    R(3) = R(27) |R(27);
    R(4) = (f + 36);
    R(5) = (0 + 14);
    GM_CALLV(0x800FB61Cu, 0x802E19F8u, 0);
    R(3) = (0 + 1);
    goto L_800FB650;
L_800FB624:;
    R(3) = R(26) |R(26);
    R(4) = R(29) |R(29);
    R(5) = R(27) |R(27);
    GM_CALLV(0x800FB634u, 0x800FB7F0u, 0);
    R(3) = (0 + 1);
    goto L_800FB650;
L_800FB63C:;
    R(29) = (R(29) + 1);
    R(30) = (R(30) + 2);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 5);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FB534; }
    R(3) = (0 + 0);
L_800FB650:;
    R(11) = (f + 96);
    R(0) = lr;
}

/* fn_800FBDE0 (fn_800FBDE0, 124 bytes) */
static void wm_m_fbde0(GM_CTX) {
    GM_FN(0x800FBDE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(29) = (0 + 0);
    R(28) = (0 + 0);
    R(31) = (0 + 0x802F0000u);
L_800FBE00:;
    R(30) = (R(31) + 13376);
    R(27) = (0 + 0);
L_800FBE08:;
    R(4) = ld32(base, (R(30) + 0));
    R(3) = R(28) |R(28);
    GM_CALLV(0x800FBE14u, 0x800FAE40u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FBE24; }
    R(29) = (0 + 1);
    goto L_800FBE34;
L_800FBE24:;
    R(27) = (R(27) + 1);
    R(30) = (R(30) + 4);
    cr_cmp_u(ctx, 0, R(27), 0x7u);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FBE08; }
L_800FBE34:;
    R(28) = (R(28) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 10);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FBE00; }
    R(11) = (f + 32);
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* fn_800FBF30 (fn_800FBF30, 120 bytes) */
static void wm_m_fbf30(GM_CTX) {
    GM_FN(0x800FBF30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + -1);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FBF54u, 0x800E0380u, 0);
    R(31) = R(3) |R(3);
    R(30) = (0 + 0);
    R(29) = (0 + 0);
L_800FBF60:;
    R(3) = R(31) |R(31);
    R(4) = R(29) |R(29);
    R(5) = (0 + 1);
    GM_CALLV(0x800FBF70u, 0x800CE350u, 0);
    R(0) = R(3) & 0xFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FBF7C; }
    R(30) = R(29) |R(29);
L_800FBF7C:;
    R(29) = (R(29) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 8);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FBF60; }
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_800FBFB0 (fn_800FBFB0, 64 bytes) */
static void wm_m_fbfb0(GM_CTX) {
    GM_FN(0x800FBFB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x800FBFC0u, 0x800FBF30u, 0);
    R(4) = ld8(base, (R(13) + -21555));
    R(0) = (0 + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(4));
    if ((!CR_BIT(ctx, 1))) { goto L_800FBFDC; }
    cr_cmp_u(ctx, 0, R(4), 0x7u);
    if ((CR_BIT(ctx, 2))) { goto L_800FBFDC; }
    R(0) = (0 + 0);
L_800FBFDC:;
    R(3) = R(0) |R(0);
    R(0) = lr;
}

/* fn_800FC040 (fn_800FC040, 92 bytes) */
static void wm_m_fc040(GM_CTX) {
    GM_FN(0x800FC040); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -21748));
    GM_CALLV(0x800FC054u, 0x801002F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(4) = (0 + 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800FC068; }
    R(4) = (0 + 1);
    goto L_800FC088;
L_800FC068:;
    R(3) = ld8(base, (R(3) + 3));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 48);
    if ((!CR_BIT(ctx, 2))) { goto L_800FC078; }
    R(4) = (0 + 1);
L_800FC078:;
    R(0) = (int8_t)R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 49);
    if ((!CR_BIT(ctx, 2))) { goto L_800FC088; }
    R(4) = (0 + 0);
L_800FC088:;
    R(0) = lr;
    R(3) = R(4) |R(4);
}

/* fn_800FC0A0 (fn_800FC0A0, 156 bytes) */
static void wm_m_fc0a0(GM_CTX) {
    GM_FN(0x800FC0A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0x10000u);
    R(0) = (R(3) + 25880);
    R(29) = (0 + 0);
    R(28) = (0 + 0);
    R(4) = ld32(base, (R(13) + -21748));
    R(3) = ld32(base, (R(4) + 13196));
    R(0) = ((int32_t)R(3) * (int32_t)R(0));
    R(3) = R(4) + R(0);
    R(30) = ld32(base, (R(3) + 13216));
    R(31) = (R(3) + 13204);
    goto L_800FC110;
L_800FC0E8:;
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    GM_CALLV(0x800FC0F4u, 0x800F56B0u, 0);
    GM_CALLV(0x800FC0F8u, 0x800F9530u, 0);
    GM_CALLV(0x800FC0FCu, 0x800F9840u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 8);
    if ((!CR_BIT(ctx, 2))) { goto L_800FC10C; }
    R(29) = (0 + 1);
    goto L_800FC118;
L_800FC10C:;
    R(28) = (R(28) + 1);
L_800FC110:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(30));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FC0E8; }
L_800FC118:;
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* getEnemyRevivalCount__6dWmLibFii (getEnemyRevivalCount__6dWmLibFii, 80 bytes) */
static void wm_getEnemyRevivalCount__6dWmLibFii_fc140(GM_CTX) {
    GM_FN(0x800FC140); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(4) = (0 + -1);
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FC168u, 0x800E0380u, 0);
    R(4) = R(30) |R(30);
    R(5) = R(31) |R(31);
    GM_CALLV(0x800FC174u, 0x800CE450u, 0);
    R(3) = R(3) & 0xFFu;
    R(0) = lr;
}

/* fn_800FC2D0 (fn_800FC2D0, 156 bytes) */
static void wm_m_fc2d0(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(4), 5);
    if ((CR_BIT(ctx, 2))) { goto L_800FC2F4; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 4);
    if ((CR_BIT(ctx, 2))) { goto L_800FC30C; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800FC324; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 3);
    if ((CR_BIT(ctx, 2))) { goto L_800FC33C; }
    goto L_800FC354;
L_800FC2F4:;
    { uint32_t ea_ = (R(2) + -24668); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24684); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    return;
L_800FC30C:;
    { uint32_t ea_ = (R(2) + -24668); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24688); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    return;
L_800FC324:;
    { uint32_t ea_ = (R(2) + -24668); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24684); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    return;
L_800FC33C:;
    { uint32_t ea_ = (R(2) + -24668); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24688); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    return;
L_800FC354:;
    { uint32_t ea_ = (R(2) + -24668); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24684); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_800FC370 (fn_800FC370, 20 bytes) */
static void wm_m_fc370(GM_CTX) {
    R(3) = ld8(base, (R(13) + -21555));
    R(0) = (R(3) + -8);
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
}

/* fn_800FC5C0 (fn_800FC5C0, 552 bytes) */
static void wm_m_fc5c0(GM_CTX) {
    GM_FN(0x800FC5C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[2].u;
    ctx->f[30].u = ctx->f[1].u;
    R(30) = R(3) |R(3);
    R(31) = ld32(base, (R(13) + -21728));
    GM_CALLV(0x800FC5F8u, 0x80100940u, 0);
    R(0) = ld32(base, (R(31) + 576));
    { uint32_t ea_ = (R(31) + 180); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 176); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 5);
    { uint32_t ea_ = (R(31) + 172); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    if ((CR_BIT(ctx, 2))) { goto L_800FC644; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((CR_BIT(ctx, 2))) { goto L_800FC67C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800FC6B4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((CR_BIT(ctx, 2))) { goto L_800FC73C; }
    goto L_800FC7C0;
L_800FC644:;
    { uint32_t ea_ = (R(2) + -24704); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d * ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 16); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[5].d - ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d - ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d + ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[4].d + ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 20); stfs(base, ea_, ctx->f[0].d); }
    goto L_800FC7C0;
L_800FC67C:;
    { uint32_t ea_ = (R(2) + -24704); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d * ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 16); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[5].d - ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d - ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d + ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[4].d + ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 20); stfs(base, ea_, ctx->f[0].d); }
    goto L_800FC7C0;
L_800FC6B4:;
    cr_fcmp(ctx, 0, ctx->f[5].d, ctx->f[5].d);
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(2) + -24704); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = frsp(ctx->f[5].d);
    { uint32_t ea_ = (f + 20); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[30].d * ctx->f[1].d);
    { uint32_t ea_ = (f + 8); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[31].d * ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[6].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[0].d - ctx->f[5].d);
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[4].d);
    { uint32_t ea_ = (R(30) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(30) + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 20); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 0))) { goto L_800FC710; }
    goto L_800FC714;
L_800FC710:;
    ctx->f[6].u = ctx->f[2].u;
L_800FC714:;
    { uint32_t ea_ = (R(2) + -24704); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].d = frsp(ctx->f[6].d);
    { uint32_t ea_ = (R(30) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[30].d * ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 20); stfs(base, ea_, ctx->f[0].d); }
    goto L_800FC7C0;
L_800FC73C:;
    cr_fcmp(ctx, 0, ctx->f[5].d, ctx->f[5].d);
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(2) + -24704); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = frsp(ctx->f[5].d);
    { uint32_t ea_ = (f + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[30].d * ctx->f[1].d);
    { uint32_t ea_ = (f + 20); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[31].d * ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[6].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[0].d - ctx->f[5].d);
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[4].d);
    { uint32_t ea_ = (R(30) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(30) + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 20); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 0))) { goto L_800FC798; }
    goto L_800FC79C;
L_800FC798:;
    ctx->f[6].u = ctx->f[2].u;
L_800FC79C:;
    { uint32_t ea_ = (R(2) + -24704); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].d = frsp(ctx->f[6].d);
    { uint32_t ea_ = (R(30) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[30].d * ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 20); stfs(base, ea_, ctx->f[0].d); }
L_800FC7C0:;
    R(0) = lr;
}

/* fn_800FC7F0 (fn_800FC7F0, 20 bytes) */
static void wm_m_fc7f0(GM_CTX) {
    R(3) = ld8(base, (R(13) + -21555));
    R(0) = (R(3) + -1);
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
}

/* fn_800FCA20 (fn_800FCA20, 44 bytes) */
static void wm_m_fca20(GM_CTX) {
    GM_FN(0x800FCA20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 38);
    GM_CALLV(0x800FCA34u, 0x800FAE40u, 0);
    R(0) = cntlzw(R(3));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
    R(0) = lr;
}

/* fn_800FCA50 (fn_800FCA50, 136 bytes) */
static void wm_m_fca50(GM_CTX) {
    GM_FN(0x800FCA50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 0);
    R(4) = (0 + 2);
    GM_CALLV(0x800FCA74u, 0x800FAE40u, 0);
    R(29) = R(3) |R(3);
    R(3) = ld8(base, (R(13) + -21555));
    GM_CALLV(0x800FCA80u, 0x800FCA20u, 0);
    R(30) = R(3) |R(3);
    GM_CALLV(0x800FCA88u, 0x800FC9C0u, 0);
    R(31) = R(3) |R(3);
    GM_CALLV(0x800FCA90u, 0x800FCAF0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    R(0) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FCAB8; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FCAB8; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FCAB8; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FCAB8; }
    R(0) = (0 + 1);
L_800FCAB8:;
    R(3) = R(0) |R(0);
    R(0) = lr;
}

/* fn_800FCAF0 (fn_800FCAF0, 88 bytes) */
static void wm_m_fcaf0(GM_CTX) {
    GM_FN(0x800FCAF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0);
    R(3) = ld8(base, (R(13) + -21555));
    R(0) = (R(3) + -1);
    cr_cmp_u(ctx, 0, R(0), 0x6u);
    if ((!CR_BIT(ctx, 1))) { goto L_800FCB28; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FCB20; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 8);
    if ((!CR_BIT(ctx, 2))) { goto L_800FCB34; }
L_800FCB20:;
    R(4) = (0 + 1);
    goto L_800FCB34;
L_800FCB28:;
    R(4) = (0 + 21);
    GM_CALLV(0x800FCB30u, 0x800FAE40u, 0);
    R(4) = R(3) |R(3);
L_800FCB34:;
    R(0) = lr;
    R(3) = R(4) |R(4);
}

/* fn_800FCBB0 (fn_800FCBB0, 240 bytes) */
static void wm_m_fcbb0(GM_CTX) {
    GM_FN(0x800FCBB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = (0 + 0);
    R(28) = ld8(base, (R(13) + -21555));
    R(30) = ld32(base, (R(13) + -22276));
    GM_CALLV(0x800FCBDCu, 0x800FCA50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FCC6C; }
    R(31) = R(30) + R(28);
    R(0) = ld8(base, (R(31) + 937));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FCC28; }
    GM_CALLV(0x800FCBF8u, 0x800FCDA0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FCC0C; }
    R(3) = ld8(base, (R(31) + 937));
    R(0) = (R(3) + -1);
    st8(base, (R(31) + 937), R(0));
L_800FCC0C:;
    R(0) = ld8(base, (R(31) + 937));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FCC7C; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x800FCC20u, 0x800FCCA0u, 0);
    R(29) = R(3) |R(3);
    goto L_800FCC7C;
L_800FCC28:;
    R(3) = R(28) |R(28);
    GM_CALLV(0x800FCC30u, 0x800FCDC0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FCC5C; }
    GM_CALLV(0x800FCC3Cu, 0x800FCDB0u, 0);
    R(0) = (0 + 1);
    st8(base, (R(31) + 937), R(0));
    R(0) = (0 + 42);
    R(29) = (0 + 1);
    R(3) = ld8(base, (R(31) + 917));
    st8(base, (R(31) + 927), R(3));
    st8(base, (R(31) + 917), R(0));
    goto L_800FCC7C;
L_800FCC5C:;
    R(3) = R(28) |R(28);
    GM_CALLV(0x800FCC64u, 0x800FCCA0u, 0);
    R(29) = R(3) |R(3);
    goto L_800FCC7C;
L_800FCC6C:;
    R(3) = R(30) + R(28);
    R(0) = (0 + 42);
    st8(base, (R(3) + 927), R(0));
    st8(base, (R(3) + 917), R(0));
L_800FCC7C:;
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* fn_800FD2E0 (fn_800FD2E0, 48 bytes) */
static void wm_m_fd2e0(GM_CTX) {
    GM_FN(0x800FD2E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + -1);
    R(3) = ld32(base, (R(13) + -22080));
    GM_CALLV(0x800FD2F8u, 0x800E0380u, 0);
    R(0) = ld8(base, (R(3) + 2));
    R(3) = rotl32(R(0), 27) & 0x1u;
    R(0) = lr;
}

/* fn_800FD310 (fn_800FD310, 116 bytes) */
static void wm_m_fd310(GM_CTX) {
    GM_FN(0x800FD310); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    GM_CALLV(0x800FD32Cu, 0x800FAD60u, 0);
    R(30) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(31) = (0 + 0);
    GM_CALLV(0x800FD33Cu, 0x800F9840u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800FD368; }
    GM_CALLV(0x800FD348u, 0x800FC0A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FD368; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FD368; }
    GM_CALLV(0x800FD35Cu, 0x800FBFB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FD368; }
    R(31) = (0 + 1);
L_800FD368:;
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_800FD500 (fn_800FD500, 112 bytes) */
static void wm_m_fd500(GM_CTX) {
    GM_FN(0x800FD500); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24660); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -16228);
    { uint32_t ea_ = (R(2) + -24656); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24652); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + -10896);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15616);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800FD558u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21792), R(0));
    R(0) = lr;
}

/* fn_800FD590 (fn_800FD590, 160 bytes) */
static void wm_m_fd590(GM_CTX) {
    R(0) = (0 + 2);
    R(5) = (0 + 0);
    R(6) = R(3) |R(3);
    st32(base, (R(3) + 4), R(5));
    ctx->ctr = R(0);
L_800FD5A4:;
    st8(base, (R(6) + 8), R(5));
    st8(base, (R(6) + 22), R(5));
    st8(base, (R(6) + 36), R(5));
    st8(base, (R(6) + 50), R(5));
    st8(base, (R(6) + 64), R(5));
    st8(base, (R(6) + 78), R(5));
    st8(base, (R(6) + 92), R(5));
    st8(base, (R(6) + 106), R(5));
    st8(base, (R(6) + 120), R(5));
    st8(base, (R(6) + 134), R(5));
    st8(base, (R(6) + 148), R(5));
    st8(base, (R(6) + 162), R(5));
    st8(base, (R(6) + 176), R(5));
    st8(base, (R(6) + 190), R(5));
    st8(base, (R(6) + 204), R(5));
    st8(base, (R(6) + 218), R(5));
    st8(base, (R(6) + 232), R(5));
    st8(base, (R(6) + 246), R(5));
    st8(base, (R(6) + 260), R(5));
    st8(base, (R(6) + 274), R(5));
    st8(base, (R(6) + 288), R(5));
    st8(base, (R(6) + 302), R(5));
    st8(base, (R(6) + 316), R(5));
    st8(base, (R(6) + 330), R(5));
    st8(base, (R(6) + 344), R(5));
    st8(base, (R(6) + 358), R(5));
    st8(base, (R(6) + 372), R(5));
    st8(base, (R(6) + 386), R(5));
    st8(base, (R(6) + 400), R(5));
    st8(base, (R(6) + 414), R(5));
    st8(base, (R(6) + 428), R(5));
    st8(base, (R(6) + 442), R(5));
    R(6) = (R(6) + 448);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800FD5A4; }
    GM_TAIL(0x800FD630u, 0); return;
}

/* fn_800FD630 (fn_800FD630, 228 bytes) */
static void wm_m_fd630(GM_CTX) {
    GM_FN(0x800FD630); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(3) = R(4) |R(4);
    GM_CALLV(0x800FD654u, 0x80168400u, 0);
    st32(base, (f + 8), R(3));
    R(30) = (0 + 0);
    goto L_800FD6E8;
L_800FD660:;
    R(4) = R(30) |R(30);
    R(3) = (f + 8);
    GM_CALLV(0x800FD66Cu, 0x8023B800u, 0);
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FD680; }
    R(31) = R(3) + R(0);
    goto L_800FD684;
L_800FD680:;
    R(31) = (0 + 0);
L_800FD684:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800FD68Cu, 0x802DC69Cu, 0);
    R(0) = (R(3) + -12);
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_800FD6E4; }
    R(0) = ld8(base, (R(31) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 109);
    if ((!CR_BIT(ctx, 2))) { goto L_800FD6E4; }
    R(0) = ld8(base, (R(31) + 1));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 116);
    if ((!CR_BIT(ctx, 2))) { goto L_800FD6E4; }
    R(0) = ld8(base, (R(31) + 2));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 82);
    if ((!CR_BIT(ctx, 2))) { goto L_800FD6E4; }
    R(0) = ld32(base, (R(29) + 4));
    R(4) = R(31) |R(31);
    R(5) = (0 + 14);
    R(0) = ((int32_t)R(0) * 14);
    R(3) = R(29) + R(0);
    R(3) = (R(3) + 8);
    GM_CALLV(0x800FD6D8u, 0x802E19F8u, 0);
    R(3) = ld32(base, (R(29) + 4));
    R(0) = (R(3) + 1);
    st32(base, (R(29) + 4), R(0));
L_800FD6E4:;
    R(30) = (R(30) + 1);
L_800FD6E8:;
    R(3) = (f + 8);
    GM_CALLV(0x800FD6F0u, 0x8023B8C0u, 0);
    cr_cmp_u(ctx, 0, R(30), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FD660; }
    R(0) = lr;
}

/* fn_800FD720 (fn_800FD720, 40 bytes) */
static void wm_m_fd720(GM_CTX) {
    R(5) = ld32(base, (R(3) + 4));
    R(0) = (R(5) + -1);
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_800FD738; }
    R(3) = (0 + 0);
    return;
L_800FD738:;
    R(0) = ((int32_t)R(4) * 14);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 8);
}

/* fn_800FD750 (fn_800FD750, 132 bytes) */
static void wm_m_fd750(GM_CTX) {
    GM_FN(0x800FD750); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (R(3) + 8);
    R(29) = (0 + 0);
    R(28) = R(4) |R(4);
    R(30) = ld32(base, (R(3) + 4));
    goto L_800FD7A8;
L_800FD780:;
    R(3) = R(31) |R(31);
    R(4) = R(28) |R(28);
    R(5) = (0 + 14);
    GM_CALLV(0x800FD790u, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FD7A0; }
    R(3) = (0 + 1);
    goto L_800FD7B4;
L_800FD7A0:;
    R(31) = (R(31) + 14);
    R(29) = (R(29) + 1);
L_800FD7A8:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), (int32_t)R(30));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FD780; }
    R(3) = (0 + 0);
L_800FD7B4:;
    R(0) = lr;
}

/* fn_800FD7E0 (fn_800FD7E0, 20 bytes) */
static void wm_m_fd7e0(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld8(base, (R(13) + -21555));
    R(0) = ld32(base, (R(4) + 4));
    R(4) = R(0) & 0xFFu;
    GM_TAIL(0x800FA330u, 0); return;
}

/* fn_800FD800 (fn_800FD800, 20 bytes) */
static void wm_m_fd800(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld8(base, (R(13) + -21555));
    R(0) = ld32(base, (R(4) + 4));
    R(4) = R(0) & 0xFFu;
    GM_TAIL(0x800FA8C0u, 0); return;
}

/* fn_800FD820 (fn_800FD820, 20 bytes) */
static void wm_m_fd820(GM_CTX) {
    R(0) = ld32(base, (R(3) + 4));
    R(3) = ld8(base, (R(13) + -21555));
    R(4) = R(0) & 0xFFu;
    R(5) = rotl32(R(0), 24) & 0xFFu;
    GM_TAIL(0x800FA9C0u, 0); return;
}

/* fn_800FD8A0 (fn_800FD8A0, 20 bytes) */
static void wm_m_fd8a0(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld8(base, (R(13) + -21555));
    R(0) = ld32(base, (R(4) + 4));
    R(4) = R(0) & 0xFFu;
    GM_TAIL(0x800FAE40u, 0); return;
}

/* fn_800FD8C0 (fn_800FD8C0, 20 bytes) */
static void wm_m_fd8c0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 4));
    R(3) = ld8(base, (R(13) + -21555));
    R(4) = R(0) & 0xFFu;
    R(5) = rotl32(R(0), 24) & 0xFFu;
    GM_TAIL(0x800FAE80u, 0); return;
}

/* fn_800FD900 (fn_800FD900, 20 bytes) */
static void wm_m_fd900(GM_CTX) {
    R(0) = ld32(base, (R(3) + 4));
    R(3) = ld8(base, (R(13) + -21555));
    R(4) = R(0) & 0xFFu;
    R(5) = rotl32(R(0), 24) & 0xFFu;
    GM_TAIL(0x800FB290u, 0); return;
}

/* fn_800FD920 (fn_800FD920, 20 bytes) */
static void wm_m_fd920(GM_CTX) {
    R(4) = R(3) |R(3);
    R(3) = ld8(base, (R(13) + -21555));
    R(0) = ld32(base, (R(4) + 4));
    R(4) = R(0) & 0xFFu;
    GM_TAIL(0x800FB040u, 0); return;
}

/* fn_800FD9C0 (fn_800FD9C0, 112 bytes) */
static void wm_m_fd9c0(GM_CTX) {
    GM_FN(0x800FD9C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24648); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -15944);
    { uint32_t ea_ = (R(2) + -24644); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24640); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + -9680);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15632);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800FDA18u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21784), R(0));
    R(0) = lr;
}

/* fn_800FDA50 (fn_800FDA50, 104 bytes) */
static void wm_m_fda50(GM_CTX) {
    GM_FN(0x800FDA50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    R(4) = (0 + 0x80010000u);
    R(5) = (0 + 0x80010000u);
    R(6) = (R(6) + -15904);
    R(4) = (R(4) + 24112);
    R(31) = R(3) |R(3);
    R(5) = (R(5) + -1040);
    R(7) = (0 + 32);
    st32(base, (R(3) + 0), R(6));
    R(6) = (0 + 12);
    R(3) = (R(3) + 4);
    GM_CALLV(0x800FDA90u, 0x802DC9A0u, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 392), R(0));
    R(3) = R(31) |R(31);
    st32(base, (R(31) + 396), R(0));
    st32(base, (R(31) + 400), R(0));
    R(0) = lr;
}

/* fn_800FDAC0 (fn_800FDAC0, 104 bytes) */
static void wm_m_fdac0(GM_CTX) {
    GM_FN(0x800FDAC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800FDB0C; }
    R(4) = (0 + 0x80010000u);
    R(5) = (0 + 12);
    R(4) = (R(4) + -1040);
    R(6) = (0 + 32);
    R(3) = (R(3) + 4);
    GM_CALLV(0x800FDAFCu, 0x802DCA98u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800FDB0C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x800FDB0Cu, 0x802B9280u, 0);
L_800FDB0C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_800FDB30 (fn_800FDB30, 244 bytes) */
static void wm_m_fdb30(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(5), 3);
    if ((CR_BIT(ctx, 2))) { goto L_800FDB64; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800FDB84; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 4);
    if ((CR_BIT(ctx, 2))) { goto L_800FDBA4; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 5);
    if ((CR_BIT(ctx, 2))) { goto L_800FDBC4; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FDBE4; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800FDC00; }
    goto L_800FDC1C;
L_800FDB64:;
    { uint32_t ea_ = (R(3) + 180); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800FDC1C; }
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (0 + 1);
    return;
L_800FDB84:;
    { uint32_t ea_ = (R(3) + 180); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800FDC1C; }
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (0 + 1);
    return;
L_800FDBA4:;
    { uint32_t ea_ = (R(3) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800FDC1C; }
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (0 + 1);
    return;
L_800FDBC4:;
    { uint32_t ea_ = (R(3) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800FDC1C; }
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (0 + 1);
    return;
L_800FDBE4:;
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800FDC1C; }
    R(3) = (0 + 1);
    return;
L_800FDC00:;
    { uint32_t ea_ = (R(3) + 176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800FDC1C; }
    R(3) = (0 + 1);
    return;
L_800FDC1C:;
    R(3) = (0 + 0);
}

/* fn_800FDC80 (fn_800FDC80, 104 bytes) */
static void wm_m_fdc80(GM_CTX) {
    GM_FN(0x800FDC80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + -1);
    R(30) = R(3) |R(3);
    R(29) = (0 + 0);
L_800FDCA4:;
    R(4) = ld32(base, (R(30) + 428));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 0))) { goto L_800FDCBC; }
    R(3) = ld32(base, (R(13) + -21524));
    GM_CALLV(0x800FDCB8u, 0x801034E0u, 0);
    st32(base, (R(30) + 428), R(31));
L_800FDCBC:;
    R(29) = (R(29) + 1);
    R(30) = (R(30) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 2);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FDCA4; }
    R(0) = lr;
}

/* fn_800FDCF0 (fn_800FDCF0, 68 bytes) */
static void wm_m_fdcf0(GM_CTX) {
    GM_FN(0x800FDCF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 456));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 0))) { goto L_800FDD20; }
    R(3) = ld32(base, (R(13) + -21508));
    GM_CALLV(0x800FDD18u, 0x801055D0u, 0);
    R(0) = (0 + -1);
    st32(base, (R(31) + 456), R(0));
L_800FDD20:;
    R(0) = lr;
}

/* fn_800FDD40 (fn_800FDD40, 24 bytes) */
static void wm_m_fdd40(GM_CTX) {
    R(5) = (0 + 0);
    R(0) = (0 + 2);
    st32(base, (R(3) + 440), R(5));
    st32(base, (R(3) + 444), R(0));
    st32(base, (R(3) + 452), R(4));
}

/* fn_800FDD60 (fn_800FDD60, 428 bytes) */
static void wm_m_fdd60(GM_CTX) {
    GM_FN(0x800FDD60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0);
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 440));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FDDBC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800FDDC8; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800FDDEC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((CR_BIT(ctx, 2))) { goto L_800FDE2C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 6);
    if ((CR_BIT(ctx, 2))) { goto L_800FDE70; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 7);
    if ((CR_BIT(ctx, 2))) { goto L_800FDEB4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 8);
    if ((CR_BIT(ctx, 2))) { goto L_800FDEEC; }
    goto L_800FDEF0;
L_800FDDBC:;
    R(0) = (0 + 1);
    st32(base, (R(3) + 440), R(0));
    goto L_800FDEF0;
L_800FDDC8:;
    R(12) = ld32(base, (R(3) + 96));
    R(5) = (0 + 0);
    R(4) = ld32(base, (R(3) + 452));
    R(12) = ld32(base, (R(12) + 112));
    ctx->ctr = R(12);
    GM_CALLV(0x800FDDE0u, ctx->ctr, 0);
    R(0) = (0 + 2);
    st32(base, (R(30) + 440), R(0));
    goto L_800FDEF0;
L_800FDDEC:;
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 116));
    ctx->ctr = R(12);
    GM_CALLV(0x800FDDFCu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FDEF0; }
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(4) = (0 + 5);
    R(5) = (0 + 1);
    R(12) = ld32(base, (R(12) + 112));
    ctx->ctr = R(12);
    GM_CALLV(0x800FDE20u, ctx->ctr, 0);
    R(0) = (0 + 4);
    st32(base, (R(30) + 440), R(0));
    goto L_800FDEF0;
L_800FDE2C:;
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 116));
    ctx->ctr = R(12);
    GM_CALLV(0x800FDE3Cu, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FDEF0; }
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 128));
    ctx->ctr = R(12);
    GM_CALLV(0x800FDE5Cu, ctx->ctr, 0);
    R(3) = (0 + 30);
    R(0) = (0 + 7);
    st32(base, (R(30) + 448), R(3));
    st32(base, (R(30) + 440), R(0));
    goto L_800FDEF0;
L_800FDE70:;
    R(12) = ld32(base, (R(3) + 96));
    R(12) = ld32(base, (R(12) + 116));
    ctx->ctr = R(12);
    GM_CALLV(0x800FDE80u, ctx->ctr, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FDEF0; }
    R(12) = ld32(base, (R(30) + 96));
    R(3) = R(30) |R(30);
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 128));
    ctx->ctr = R(12);
    GM_CALLV(0x800FDEA0u, ctx->ctr, 0);
    R(3) = (0 + 30);
    R(0) = (0 + 7);
    st32(base, (R(30) + 448), R(3));
    st32(base, (R(30) + 440), R(0));
    goto L_800FDEF0;
L_800FDEB4:;
    R(4) = ld32(base, (R(3) + 448));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800FDECC; }
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 448), R(0));
    goto L_800FDEF0;
L_800FDECC:;
    R(12) = ld32(base, (R(3) + 96));
    R(4) = (0 + 0);
    R(12) = ld32(base, (R(12) + 128));
    ctx->ctr = R(12);
    GM_CALLV(0x800FDEE0u, ctx->ctr, 0);
    R(0) = (0 + 8);
    st32(base, (R(30) + 440), R(0));
    goto L_800FDEF0;
L_800FDEEC:;
    R(31) = (0 + 1);
L_800FDEF0:;
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_800FDF10 (fn_800FDF10, 40 bytes) */
static void wm_m_fdf10(GM_CTX) {
    R(4) = (R(4) + -1);
    R(3) = (0 + 0);
    cr_cmp_u(ctx, 0, R(4), 0x5u);
    if ((CR_BIT(ctx, 1))) return;
    R(0) = (0 + 1);
    { uint32_t s_ = R(4) & 63; R(0) = s_ > 31 ? 0 : R(0) << s_; }
    R(0) = R(0) & 0x3Bu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) return;
    R(3) = (0 + 1);
}

/* fn_800FDF40 (fn_800FDF40, 76 bytes) */
static void wm_m_fdf40(GM_CTX) {
    GM_FN(0x800FDF40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -22276));
    R(0) = ld32(base, (R(3) + 84));
    cr_cmp_u(ctx, 0, R(0), 0x13u);
    if ((!CR_BIT(ctx, 1))) { goto L_800FDF70; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 37);
    if ((!CR_BIT(ctx, 2))) { goto L_800FDF78; }
    GM_CALLV(0x800FDF68u, 0x800FBFB0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FDF78; }
L_800FDF70:;
    R(3) = (0 + 1);
    goto L_800FDF7C;
L_800FDF78:;
    R(3) = (0 + 0);
L_800FDF7C:;
    R(0) = lr;
}

/* fn_800FDF90 (fn_800FDF90, 4 bytes) */
static void wm_m_fdf90(GM_CTX) {

}

/* fn_800FDFA0 (fn_800FDFA0, 112 bytes) */
static void wm_m_fdfa0(GM_CTX) {
    GM_FN(0x800FDFA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24632); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -15888);
    { uint32_t ea_ = (R(2) + -24628); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24624); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + -8176);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15648);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800FDFF8u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21776), R(0));
    R(0) = lr;
}

/* fn_800FE030 (fn_800FE030, 8 bytes) */
static void wm_m_fe030(GM_CTX) {
    R(3) = (R(3) + 4);
    GM_TAIL(0x8016DE00u, 0); return;
}

/* CheckClipSphere__13dWmViewClip_cFPC9mSphere_c (CheckClipSphere__13dWmViewClip_cFPC9mSphere_c, 8 bytes) */
static void wm_CheckClipSphere__13dWmViewClip_cFPC9mSph_fe040(GM_CTX) {
    R(3) = (R(3) + 4);
    GM_TAIL(0x8016E230u, 0); return;
}

/* fn_800FE050 (fn_800FE050, 8 bytes) */
static void wm_m_fe050(GM_CTX) {
    R(3) = ld32(base, (R(13) + -27232));
}

/* fn_800FE060 (fn_800FE060, 164 bytes) */
static void wm_m_fe060(GM_CTX) {
    GM_FN(0x800FE060); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    GM_CALLV(0x800FE078u, 0x800FE050u, 0);
    R(31) = R(3) |R(3);
    R(28) = (0 + 0);
    R(30) = (0 + 0);
    goto L_800FE0DC;
L_800FE088:;
    R(0) = ld32(base, (R(31) + 4));
    R(26) = R(0) + R(30);
    R(0) = ld16(base, (R(30) + R(0)));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FE0D4; }
    R(29) = ld32(base, (R(26) + 4));
    R(27) = (0 + 0);
    goto L_800FE0C8;
L_800FE0A8:;
    R(3) = ld16(base, (R(29) + 0));
    GM_CALLV(0x800FE0B0u, 0x8008F620u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800FE0C0; }
    R(3) = (0 + 0);
    goto L_800FE0EC;
L_800FE0C0:;
    R(29) = (R(29) + 2);
    R(27) = (R(27) + 1);
L_800FE0C8:;
    R(0) = ld16(base, (R(26) + 2));
    cr_cmp_s(ctx, 0, (int32_t)R(27), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FE0A8; }
L_800FE0D4:;
    R(30) = (R(30) + 8);
    R(28) = (R(28) + 1);
L_800FE0DC:;
    R(0) = ld16(base, (R(31) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FE088; }
    R(3) = (0 + 1);
L_800FE0EC:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_800FE110 (fn_800FE110, 172 bytes) */
static void wm_m_fe110(GM_CTX) {
    GM_FN(0x800FE110); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    GM_CALLV(0x800FE128u, 0x800FE050u, 0);
    R(31) = R(3) |R(3);
    R(28) = (0 + 0);
    R(30) = (0 + 0);
    goto L_800FE194;
L_800FE138:;
    R(0) = ld32(base, (R(31) + 4));
    R(3) = R(0) + R(30);
    R(0) = ld16(base, (R(30) + R(0)));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FE18C; }
    R(4) = ld16(base, (R(3) + 2));
    R(3) = ld32(base, (R(3) + 4));
    R(27) = (R(4) + -1);
    R(0) = rotl32(R(27), 1) & 0xFFFFFFFEu;
    R(29) = R(3) + R(0);
    goto L_800FE184;
L_800FE164:;
    R(3) = ld16(base, (R(29) + 0));
    GM_CALLV(0x800FE16Cu, 0x8008F610u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FE17C; }
    R(3) = (0 + 0);
    goto L_800FE1A4;
L_800FE17C:;
    R(29) = (R(29) + -2);
    R(27) = (R(27) + -1);
L_800FE184:;
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    if ((!CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FE164; }
L_800FE18C:;
    R(30) = (R(30) + 8);
    R(28) = (R(28) + 1);
L_800FE194:;
    R(0) = ld16(base, (R(31) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FE138; }
    R(3) = (0 + 1);
L_800FE1A4:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_800FE1C0 (fn_800FE1C0, 4 bytes) */
static void wm_m_fe1c0(GM_CTX) {

}

/* fn_800FE1D0 (fn_800FE1D0, 196 bytes) */
static void wm_m_fe1d0(GM_CTX) {
    GM_FN(0x800FE1D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x800FE1ECu, 0x800D5330u, 0);
    R(3) = (0 + 0x80320000u);
    R(4) = (0 + 0x80330000u);
    R(31) = (0 + 0);
    st32(base, (R(30) + 524), R(31));
    R(3) = (R(3) + -15744);
    R(4) = (R(4) + -27176);
    st32(base, (R(30) + 0), R(3));
    R(3) = (R(30) + 556);
    st32(base, (R(30) + 528), R(31));
    st32(base, (R(30) + 532), R(31));
    st32(base, (R(30) + 536), R(31));
    st32(base, (R(30) + 540), R(31));
    st32(base, (R(30) + 544), R(4));
    st32(base, (R(30) + 548), R(31));
    st32(base, (R(30) + 552), R(31));
    GM_CALLV(0x800FE22Cu, 0x8016A5E0u, 0);
    R(3) = (0 + 0x80330000u);
    st32(base, (R(30) + 584), R(31));
    R(3) = (R(3) + -27320);
    st32(base, (R(30) + 544), R(3));
    R(3) = (R(30) + 596);
    st32(base, (R(30) + 588), R(31));
    st32(base, (R(30) + 592), R(31));
    GM_CALLV(0x800FE24Cu, 0x80169CD0u, 0);
    { uint32_t ea_ = (R(2) + -24612); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x80320000u);
    R(4) = (R(4) + -15568);
    st32(base, (R(30) + 660), R(31));
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (R(30) + 664); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 668); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(30) + 672), R(31));
    { uint32_t ea_ = (R(30) + 1012); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 1016); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(30) + 1020), R(4));
    st32(base, (R(30) + 1024), R(30));
    R(0) = lr;
}

/* fn_800FE2E0 (fn_800FE2E0, 120 bytes) */
static void wm_m_fe2e0(GM_CTX) {
    GM_FN(0x800FE2E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800FE33C; }
    { uint32_t a_ = R(3); R(3) = a_ + 0x254u; ctx->xer_ca = R(3) < a_; }
    CR0(ctx, R(3));
    if ((CR_BIT(ctx, 2))) { goto L_800FE314; }
    R(4) = (0 + -1);
    GM_CALLV(0x800FE314u, 0x80169D20u, 0);
L_800FE314:;
    R(3) = (R(30) + 544);
    R(4) = (0 + -1);
    GM_CALLV(0x800FE320u, 0x80166A70u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x800FE32Cu, 0x800D54E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800FE33C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x800FE33Cu, 0x802B9280u, 0);
L_800FE33C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_800FE360 (fn_800FE360, 68 bytes) */
static void wm_m_fe360(GM_CTX) {
    GM_FN(0x800FE360); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + 255);
    R(31) = R(3) |R(3);
    R(4) = ld8(base, (R(3) + 336));
    st32(base, (R(3) + 588), R(4));
    st8(base, (R(3) + 336), R(0));
    GM_CALLV(0x800FE388u, 0x800FE400u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800FE390u, 0x800FE560u, 0);
    R(0) = lr;
}

/* fn_800FE3B0 (fn_800FE3B0, 64 bytes) */
static void wm_m_fe3b0(GM_CTX) {
    GM_FN(0x800FE3B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE3D4u, ctx->ctr, 0);
    R(4) = (R(31) + 1020);
    GM_CALLV(0x800FE3DCu, 0x8016A000u, 0);
    R(0) = lr;
}

/* fn_800FE3F0 (fn_800FE3F0, 8 bytes) */
static void wm_m_fe3f0(GM_CTX) {
    R(3) = (R(3) + 596);
}

/* fn_800FE560 (fn_800FE560, 512 bytes) */
static void wm_m_fe560(GM_CTX) {
    GM_FN(0x800FE560); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80320000u);
    R(4) = (R(4) + -15768);
    R(29) = R(3) |R(3);
    R(3) = (R(3) + 524);
    GM_CALLV(0x800FE58Cu, 0x80239E30u, 0);
    R(12) = ld32(base, (R(29) + 0));
    R(30) = R(3) |R(3);
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE5A4u, ctx->ctr, 0);
    st32(base, (f + 36), R(30));
    R(4) = (f + 36);
    R(5) = (R(29) + 4);
    R(6) = (0 + 2163);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800FE5C0u, 0x80169D90u, 0);
    R(12) = ld32(base, (R(29) + 0));
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE5D4u, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x800FE5E0u, 0x800D5B90u, 0);
    R(3) = (R(29) + 528);
    R(4) = (R(13) + -27288);
    GM_CALLV(0x800FE5ECu, 0x8023A0B0u, 0);
    st32(base, (f + 28), R(3));
    R(31) = R(3) |R(3);
    R(3) = (R(29) + 40);
    R(4) = (f + 32);
    st32(base, (f + 32), R(30));
    R(5) = (f + 28);
    R(6) = (R(29) + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x800FE610u, 0x801650D0u, 0);
    st32(base, (f + 20), R(31));
    R(3) = (R(29) + 96);
    R(4) = (f + 24);
    R(5) = (f + 20);
    st32(base, (f + 24), R(30));
    R(6) = (R(29) + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x800FE630u, 0x801650D0u, 0);
    st32(base, (f + 16), R(30));
    R(3) = (R(29) + 152);
    R(4) = (f + 16);
    R(6) = (R(29) + 4);
    R(5) = (0 + 2);
    R(7) = (0 + 0);
    GM_CALLV(0x800FE64Cu, 0x80165520u, 0);
    { uint32_t ea_ = (R(2) + -24608); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(29) + 152);
    R(5) = (R(29) + 40);
    R(4) = (0 + 0);
    GM_CALLV(0x800FE660u, 0x801656C0u, 0);
    { uint32_t ea_ = (R(2) + -24608); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(29) + 152);
    R(5) = (R(29) + 96);
    R(4) = (0 + 1);
    GM_CALLV(0x800FE674u, 0x801656C0u, 0);
    R(3) = (R(29) + 592);
    R(4) = (R(13) + -27280);
    GM_CALLV(0x800FE680u, 0x8023A200u, 0);
    st32(base, (f + 48), R(3));
    R(3) = (f + 48);
    GM_CALLV(0x800FE68Cu, 0x8023F890u, 0);
    R(0) = ld32(base, (R(29) + 592));
    R(3) = (f + 48);
    st32(base, (f + 44), R(0));
    R(4) = (f + 44);
    GM_CALLV(0x800FE6A0u, 0x8023F720u, 0);
    R(0) = ld32(base, (f + 48));
    R(3) = (R(29) + 544);
    st32(base, (f + 8), R(0));
    R(4) = (f + 12);
    R(5) = (f + 8);
    R(6) = (R(29) + 4);
    st32(base, (f + 12), R(30));
    R(7) = (0 + 0);
    R(8) = (0 + 1);
    GM_CALLV(0x800FE6C8u, 0x80166830u, 0);
    R(0) = ld32(base, (f + 48));
    R(3) = R(29) |R(29);
    st32(base, (f + 40), R(0));
    R(12) = ld32(base, (R(29) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE6E4u, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = (R(29) + 544);
    R(5) = (f + 40);
    R(6) = (0 + 0);
    R(7) = (0 + 4);
    GM_CALLV(0x800FE6FCu, 0x80166BD0u, 0);
    R(12) = ld32(base, (R(29) + 0));
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE710u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (R(29) + 544);
    R(12) = ld32(base, (R(12) + 24));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE724u, ctx->ctr, 0);
    { uint32_t ea_ = (R(2) + -24600); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x800FE72Cu, 0x800B2F10u, 0);
    { uint32_t ea_ = (R(2) + -24604); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 56); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 60));
    st32(base, (R(29) + 372), R(0));
    R(0) = lr;
}

/* fn_800FE760 (fn_800FE760, 200 bytes) */
static void wm_m_fe760(GM_CTX) {
    GM_FN(0x800FE760); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 15);
    R(4) = (f + 56);
    R(30) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE790u, ctx->ctr, 0);
    R(3) = (f + 56);
    R(4) = (R(30) + 204);
    GM_CALLV(0x800FE79Cu, 0x8016F130u, 0);
    { uint32_t ea_ = (R(2) + -24612); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 8);
    { uint32_t ea_ = (R(2) + -24596); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[1].u;
    GM_CALLV(0x800FE7B0u, 0x801C0BD0u, 0);
    R(3) = (f + 56);
    R(4) = (f + 8);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800FE7C0u, 0x801C0540u, 0);
    R(3) = (f + 56);
    R(4) = (R(30) + 192);
    GM_CALLV(0x800FE7CCu, 0x8016F130u, 0);
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE7E0u, ctx->ctr, 0);
    R(31) = R(3) |R(3);
    R(4) = (R(30) + 216);
    GM_CALLV(0x800FE7ECu, 0x8016A170u, 0);
    R(0) = (0 + 1);
    st32(base, (R(30) + 520), R(0));
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x800FE800u, 0x8016A1A0u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x800FE808u, 0x800FF740u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x800FE810u, 0x800FFC40u, 0);
    R(0) = lr;
}

/* fn_800FE830 (fn_800FE830, 180 bytes) */
static void wm_m_fe830(GM_CTX) {
    GM_FN(0x800FE830); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + 2);
    R(31) = R(3) |R(3);
    st32(base, (R(3) + 520), R(0));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE85Cu, ctx->ctr, 0);
    R(4) = (0 + 0);
    GM_CALLV(0x800FE864u, 0x8016A1A0u, 0);
    R(0) = ld32(base, (R(31) + 380));
    R(0) = R(0) & 0x20u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FE880; }
    R(0) = ld32(base, (R(31) + 380));
    R(0) = R(0) & 0xFFFFFFDFu;
    st32(base, (R(31) + 380), R(0));
    goto L_800FE890;
L_800FE880:;
    { uint32_t ea_ = (R(2) + -24612); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (R(31) + 1012);
    { uint32_t ea_ = (R(2) + -24592); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x800FE890u, 0x8015F470u, 0);
L_800FE890:;
    R(0) = ld32(base, (R(31) + 660));
    { uint32_t ea_ = (R(2) + -24612); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800FE8C4; }
    R(0) = ld32(base, (R(31) + 352));
    R(0) = R(0) & 0x2000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FE8C4; }
    R(0) = ld32(base, (R(31) + 344));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 97);
    if ((CR_BIT(ctx, 2))) { goto L_800FE8C4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 100);
    if ((CR_BIT(ctx, 2))) { goto L_800FE8C4; }
    { uint32_t ea_ = (R(2) + -24608); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_800FE8C4:;
    { uint32_t ea_ = (R(2) + -24588); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(31) + 1016);
    GM_CALLV(0x800FE8D0u, 0x8015F470u, 0);
    R(0) = lr;
}

/* fn_800FE8F0 (fn_800FE8F0, 228 bytes) */
static void wm_m_fe8f0(GM_CTX) {
    GM_FN(0x800FE8F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(3) + 40));
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    R(3) = (R(3) + 40);
    GM_CALLV(0x800FE918u, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 96));
    R(3) = (R(31) + 96);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE92Cu, ctx->ctr, 0);
    R(12) = ld32(base, (R(31) + 0));
    R(3) = R(31) |R(31);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE940u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE950u, ctx->ctr, 0);
    R(3) = ld32(base, (R(31) + 372));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FE968; }
    R(0) = (R(3) + -1);
    st32(base, (R(31) + 372), R(0));
    goto L_800FE9AC;
L_800FE968:;
    R(3) = (R(31) + 544);
    R(4) = (0 + 0);
    GM_CALLV(0x800FE974u, 0x80166F20u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FE9AC; }
    { uint32_t ea_ = (R(2) + -24600); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x800FE984u, 0x800B2F10u, 0);
    { uint32_t ea_ = (R(2) + -24604); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(31) + 544);
    R(4) = (0 + 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -24612); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 12));
    st32(base, (R(31) + 372), R(0));
    GM_CALLV(0x800FE9ACu, 0x80166EF0u, 0);
L_800FE9AC:;
    R(12) = ld32(base, (R(31) + 544));
    R(3) = (R(31) + 544);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800FE9C0u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_800FE9E0 (fn_800FE9E0, 168 bytes) */
static void wm_m_fe9e0(GM_CTX) {
    GM_FN(0x800FE9E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0);
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 660));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800FEA0C; }
    R(31) = (0 + 1);
L_800FEA0C:;
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEA20u, ctx->ctr, 0);
    R(5) = R(31) |R(31);
    R(4) = (0 + 24);
    GM_CALLV(0x800FEA2Cu, 0x8000D660u, 0);
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEA40u, ctx->ctr, 0);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEA50u, ctx->ctr, 0);
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEA64u, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(30) |R(30);
    GM_CALLV(0x800FEA70u, 0x800D5B90u, 0);
    R(0) = lr;
}

/* fn_800FEA90 (fn_800FEA90, 4 bytes) */
static void wm_m_fea90(GM_CTX) {
    GM_TAIL(0x800D5DD0u, 0); return;
}

/* fn_800FEAA0 (fn_800FEAA0, 148 bytes) */
static void wm_m_feaa0(GM_CTX) {
    GM_FN(0x800FEAA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ((int32_t)R(4) * 36);
    R(4) = (0 + 0x802F0000u);
    R(31) = R(6) |R(6);
    R(4) = (R(4) + 4944);
    R(4) = R(4) + R(0);
    R(4) = ld32(base, (R(4) + 8));
    R(30) = R(5) |R(5);
    R(29) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FEB14; }
    R(3) = (R(3) + 532);
    GM_CALLV(0x800FEAE8u, 0x8023A0B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    st32(base, (R(30) + 0), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_800FEB00; }
    R(0) = ld32(base, (R(29) + 352));
    R(0) = R(0) | 0x100000u;
    st32(base, (R(29) + 352), R(0));
L_800FEB00:;
    R(0) = ld32(base, (R(29) + 356));
    R(3) = (0 + 1);
    R(0) = R(0) | 0x100000u;
    st32(base, (R(29) + 356), R(0));
    goto L_800FEB18;
L_800FEB14:;
    R(3) = (0 + 0);
L_800FEB18:;
    R(0) = lr;
}

/* fn_800FEB40 (fn_800FEB40, 208 bytes) */
static void wm_m_feb40(GM_CTX) {
    GM_FN(0x800FEB40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[3].u;
    ctx->f[30].u = ctx->f[2].u;
    ctx->f[29].u = ctx->f[1].u;
    R(31) = (R(3) + 40);
    R(30) = R(5) |R(5);
    R(29) = R(3) |R(3);
    R(0) = ld32(base, (R(4) + 0));
    st32(base, (R(3) + 536), R(0));
    R(0) = ld32(base, (R(4) + 0));
    st32(base, (f + 8), R(0));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEB9Cu, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(6) = R(30) |R(30);
    R(5) = (f + 8);
    GM_CALLV(0x800FEBB0u, 0x801651F0u, 0);
    ctx->f[1].u = ctx->f[29].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800FEBBCu, 0x801680E0u, 0);
    ctx->f[1].u = ctx->f[30].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800FEBC8u, 0x80168FE0u, 0);
    R(12) = ld32(base, (R(29) + 0));
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEBDCu, ctx->ctr, 0);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = (R(29) + 152);
    GM_CALLV(0x800FEBE8u, 0x80169F80u, 0);
    R(0) = lr;
}

/* fn_800FEC10 (fn_800FEC10, 440 bytes) */
static void wm_m_fec10(GM_CTX) {
    GM_FN(0x800FEC10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[3].u;
    ctx->f[30].u = ctx->f[2].u;
    ctx->f[29].u = ctx->f[1].u;
    R(31) = (0 + -1);
    R(29) = R(5) |R(5);
    R(28) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 356));
    R(4) = ld32(base, (R(4) + 0));
    R(0) = R(0) & 0x20u;
    CR0(ctx, R(0));
    st32(base, (R(3) + 540), R(4));
    R(30) = ld32(base, (R(3) + 344));
    if ((CR_BIT(ctx, 2))) { goto L_800FED04; }
    R(0) = ld32(base, (R(3) + 352));
    R(0) = R(0) & 0x400u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FED04; }
    R(0) = ld32(base, (R(3) + 344));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 96);
    if ((CR_BIT(ctx, 2))) { goto L_800FECAC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 97);
    if ((CR_BIT(ctx, 2))) { goto L_800FECB4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 98);
    if ((CR_BIT(ctx, 2))) { goto L_800FECBC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 99);
    if ((CR_BIT(ctx, 2))) { goto L_800FECC4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 100);
    if ((CR_BIT(ctx, 2))) { goto L_800FECCC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 101);
    if ((CR_BIT(ctx, 2))) { goto L_800FECD4; }
    goto L_800FECD8;
L_800FECAC:;
    R(31) = (0 + 102);
    goto L_800FECD8;
L_800FECB4:;
    R(31) = (0 + 103);
    goto L_800FECD8;
L_800FECBC:;
    R(31) = (0 + 104);
    goto L_800FECD8;
L_800FECC4:;
    R(31) = (0 + 105);
    goto L_800FECD8;
L_800FECCC:;
    R(31) = (0 + 106);
    goto L_800FECD8;
L_800FECD4:;
    R(31) = (0 + 107);
L_800FECD8:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), -1);
    if ((CR_BIT(ctx, 2))) { goto L_800FED04; }
    R(0) = ((int32_t)R(31) * 36);
    R(4) = (0 + 0x802F0000u);
    R(3) = (R(3) + 532);
    R(4) = (R(4) + 4944);
    R(4) = R(4) + R(0);
    R(4) = ld32(base, (R(4) + 8));
    GM_CALLV(0x800FECFCu, 0x8023A0B0u, 0);
    st32(base, (R(28) + 540), R(3));
    R(30) = R(31) |R(31);
L_800FED04:;
    R(0) = ld32(base, (R(28) + 540));
    R(3) = R(28) |R(28);
    st32(base, (f + 8), R(0));
    R(31) = (R(28) + 96);
    R(12) = ld32(base, (R(28) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FED24u, ctx->ctr, 0);
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(6) = R(29) |R(29);
    R(5) = (f + 8);
    GM_CALLV(0x800FED38u, 0x801651F0u, 0);
    ctx->f[1].u = ctx->f[29].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800FED44u, 0x801680E0u, 0);
    ctx->f[1].u = ctx->f[30].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800FED50u, 0x80168FE0u, 0);
    R(12) = ld32(base, (R(28) + 0));
    R(3) = R(28) |R(28);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FED64u, ctx->ctr, 0);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = (R(28) + 152);
    GM_CALLV(0x800FED70u, 0x80169F80u, 0);
    R(3) = ld32(base, (R(28) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FED9C; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), -1);
    if ((!CR_BIT(ctx, 2))) { goto L_800FED88; }
    R(30) = ld32(base, (R(28) + 340));
L_800FED88:;
    ctx->f[1].u = ctx->f[29].u;
    R(4) = R(30) |R(30);
    ctx->f[2].u = ctx->f[31].u;
    ctx->f[3].u = ctx->f[30].u;
    GM_CALLV(0x800FED9Cu, 0x800D65E0u, 0);
L_800FED9C:;
    R(0) = lr;
}

/* fn_800FEDD0 (fn_800FEDD0, 252 bytes) */
static void wm_m_fedd0(GM_CTX) {
    GM_FN(0x800FEDD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x802F0000u);
    R(5) = (0 + -1);
    R(4) = (R(4) + 4944);
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
    GM_CALLV(0x800FEE2Cu, ctx->ctr, 0);
    R(4) = ld32(base, (R(31) + 0));
    GM_CALLV(0x800FEE34u, 0x8023A0B0u, 0);
    st32(base, (f + 8), R(3));
    R(3) = R(30) |R(30);
    R(5) = (f + 8);
    R(6) = (0 + 1);
    R(12) = ld32(base, (R(30) + 0));
    R(4) = ld32(base, (R(30) + 340));
    R(12) = ld32(base, (R(12) + 96));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEE58u, ctx->ctr, 0);
    R(0) = ld32(base, (R(30) + 352));
    { uint32_t ea_ = (R(2) + -24584); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FEE6C; }
    { uint32_t ea_ = (R(2) + -24612); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
L_800FEE6C:;
    R(3) = (R(30) + 40);
    GM_CALLV(0x800FEE74u, 0x80168080u, 0);
    ctx->f[31].u = ctx->f[1].u;
    R(3) = (R(30) + 40);
    GM_CALLV(0x800FEE80u, 0x801680C0u, 0);
    R(12) = ld32(base, (R(30) + 0));
    ctx->f[2].u = ctx->f[31].u;
    ctx->f[3].u = ctx->f[30].u;
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 116));
    R(4) = (f + 8);
    R(5) = ld8(base, (R(30) + 92));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEEA4u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_800FEED0 (fn_800FEED0, 304 bytes) */
static void wm_m_feed0(GM_CTX) {
    GM_FN(0x800FEED0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80320000u);
    R(4) = (R(4) + -15768);
    R(29) = R(3) |R(3);
    R(3) = (R(3) + 524);
    GM_CALLV(0x800FEEFCu, 0x80239E30u, 0);
    R(30) = ld32(base, (R(29) + 44));
    R(31) = R(3) |R(3);
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(12) = ld32(base, (R(12) + 52));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEF18u, ctx->ctr, 0);
    R(29) = ld32(base, (R(29) + 100));
    R(12) = ld32(base, (R(29) + 0));
    R(3) = R(29) |R(29);
    R(12) = ld32(base, (R(12) + 52));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEF30u, ctx->ctr, 0);
    st32(base, (f + 24), R(31));
    R(3) = R(30) |R(30);
    R(4) = (f + 24);
    R(5) = (0 + 5);
    R(12) = ld32(base, (R(30) + 0));
    R(6) = (0 + 1);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEF54u, ctx->ctr, 0);
    st32(base, (f + 20), R(31));
    R(3) = R(30) |R(30);
    R(4) = (f + 20);
    R(5) = (0 + 2);
    R(12) = ld32(base, (R(30) + 0));
    R(6) = (0 + 1);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEF78u, ctx->ctr, 0);
    st32(base, (f + 16), R(31));
    R(3) = R(30) |R(30);
    R(4) = (f + 16);
    R(5) = (0 + 0);
    R(12) = ld32(base, (R(30) + 0));
    R(6) = (0 + 0);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEF9Cu, ctx->ctr, 0);
    st32(base, (f + 12), R(31));
    R(3) = R(29) |R(29);
    R(4) = (f + 12);
    R(5) = (0 + 1);
    R(12) = ld32(base, (R(29) + 0));
    R(6) = (0 + 0);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEFC0u, ctx->ctr, 0);
    st32(base, (f + 8), R(31));
    R(3) = R(29) |R(29);
    R(4) = (f + 8);
    R(5) = (0 + 8);
    R(12) = ld32(base, (R(29) + 0));
    R(6) = (0 + 1);
    R(12) = ld32(base, (R(12) + 80));
    ctx->ctr = R(12);
    GM_CALLV(0x800FEFE4u, ctx->ctr, 0);
    R(0) = lr;
}

/* fn_800FF000 (fn_800FF000, 84 bytes) */
static void wm_m_ff000(GM_CTX) {
    GM_FN(0x800FF000); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800FF018u, 0x800D5C10u, 0);
    R(0) = ld32(base, (R(31) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FF040; }
    R(3) = (R(31) + 96);
    GM_CALLV(0x800FF02Cu, 0x80168080u, 0);
    R(3) = ld32(base, (R(31) + 36));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 132));
    ctx->ctr = R(12);
    GM_CALLV(0x800FF040u, ctx->ctr, 0);
L_800FF040:;
    R(0) = lr;
}

/* fn_800FF0C0 (fn_800FF0C0, 84 bytes) */
static void wm_m_ff0c0(GM_CTX) {
    GM_FN(0x800FF0C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800FF0D8u, 0x800D5C90u, 0);
    R(0) = ld32(base, (R(31) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FF100; }
    R(3) = (R(31) + 96);
    GM_CALLV(0x800FF0ECu, 0x801680C0u, 0);
    R(3) = ld32(base, (R(31) + 36));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 140));
    ctx->ctr = R(12);
    GM_CALLV(0x800FF100u, ctx->ctr, 0);
L_800FF100:;
    R(0) = lr;
}

/* fn_800FF120 (fn_800FF120, 84 bytes) */
static void wm_m_ff120(GM_CTX) {
    GM_FN(0x800FF120); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800FF138u, 0x800D5D00u, 0);
    R(0) = ld32(base, (R(31) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FF160; }
    R(3) = (R(31) + 96);
    GM_CALLV(0x800FF14Cu, 0x801680C0u, 0);
    R(3) = ld32(base, (R(31) + 36));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 140));
    ctx->ctr = R(12);
    GM_CALLV(0x800FF160u, ctx->ctr, 0);
L_800FF160:;
    R(0) = lr;
}

/* fn_800FF180 (fn_800FF180, 144 bytes) */
static void wm_m_ff180(GM_CTX) {
    GM_FN(0x800FF180); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(6) = ld32(base, (R(3) + 536));
    R(0) = ld32(base, (R(6) + 16));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FF1B8; }
    R(0) = R(6) + R(0);
    goto L_800FF1BC;
L_800FF1B8:;
    R(0) = (0 + 0);
L_800FF1BC:;
    st32(base, (f + 8), R(0));
    R(4) = R(5) |R(5);
    R(3) = (f + 8);
    GM_CALLV(0x800FF1CCu, 0x80239D30u, 0);
    R(31) = R(3) |R(3);
    R(3) = (R(29) + 40);
    GM_CALLV(0x800FF1D8u, 0x80168080u, 0);
    R(5) = R(31) |R(31);
    R(3) = (R(29) + 536);
    R(4) = (f + 12);
    GM_CALLV(0x800FF1E8u, 0x80241690u, 0);
    R(4) = R(30) |R(30);
    R(3) = (f + 12);
    GM_CALLV(0x800FF1F4u, 0x802418B0u, 0);
    R(0) = lr;
}

/* fn_800FF210 (fn_800FF210, 28 bytes) */
static void wm_m_ff210(GM_CTX) {
    R(0) = ld32(base, (R(3) + 356));
    R(0) = R(0) & 0x100000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FF224; }
    R(3) = (R(3) + 532);
    return;
L_800FF224:;
    R(3) = (R(3) + 528);
}

/* fn_800FF230 (fn_800FF230, 236 bytes) */
static void wm_m_ff230(GM_CTX) {
    GM_FN(0x800FF230); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(3) = R(6) |R(6);
    GM_CALLV(0x800FF25Cu, 0x8023B300u, 0);
    R(4) = ld32(base, (R(29) + 4));
    R(0) = ld32(base, (R(4) + 352));
    R(0) = R(0) & 0x100000u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800FF2CC; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FF2CC; }
    cr_cmp_u(ctx, 0, R(30), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_800FF2A8; }
    R(3) = R(31) |R(31);
    R(4) = (f + 20);
    GM_CALLV(0x800FF288u, 0x802418B0u, 0);
    { uint32_t ea_ = (f + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -24580); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 20);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800FF2A4u, 0x80241BE0u, 0);
    goto L_800FF2CC;
L_800FF2A8:;
    { uint32_t ea_ = (R(3) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 20);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800FF2CCu, 0x80241BE0u, 0);
L_800FF2CC:;
    R(3) = ld32(base, (R(29) + 4));
    R(0) = ld32(base, (R(3) + 356));
    R(0) = R(0) & 0x20u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800FF300; }
    cr_cmp_u(ctx, 0, R(30), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_800FF300; }
    R(5) = (0 + 0x80320000u);
    R(4) = (f + 8);
    R(5) = (R(5) + -15756);
    GM_CALLV(0x800FF2F4u, 0x800FF180u, 0);
    R(3) = R(31) |R(31);
    R(4) = (f + 8);
    GM_CALLV(0x800FF300u, 0x80241BE0u, 0);
L_800FF300:;
    R(0) = lr;
}

/* fn_800FF590 (fn_800FF590, 200 bytes) */
static void wm_m_ff590(GM_CTX) {
    GM_FN(0x800FF590); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (R(5) + -17);
    cr_cmp_u(ctx, 0, R(0), 0x6u);
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    if ((CR_BIT(ctx, 1))) { goto L_800FF624; }
    R(4) = R(31) |R(31);
    GM_CALLV(0x800FF5C0u, 0x800FF6B0u, 0);
    { uint32_t ea_ = (R(3) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 44); stfs(base, ea_, ctx->f[0].d); }
    goto L_800FF640;
L_800FF624:;
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800FF634u, ctx->ctr, 0);
    R(4) = R(31) |R(31);
    R(5) = R(30) |R(30);
    GM_CALLV(0x800FF640u, 0x80168180u, 0);
L_800FF640:;
    R(0) = lr;
}

/* fn_800FF660 (fn_800FF660, 20 bytes) */
static void wm_m_ff660(GM_CTX) {
    R(0) = R(3) |R(3);
    R(3) = R(4) |R(4);
    R(4) = R(0) |R(0);
    R(5) = (0 + 17);
    GM_TAIL(0x800D5790u, 0); return;
}

/* fn_800FF680 (fn_800FF680, 32 bytes) */
static void wm_m_ff680(GM_CTX) {
    R(12) = ld32(base, (R(4) + 0));
    R(0) = R(3) |R(3);
    R(3) = R(4) |R(4);
    R(5) = (0 + 23);
    R(12) = ld32(base, (R(12) + 80));
    R(4) = R(0) |R(0);
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_800FF6A0 (fn_800FF6A0, 8 bytes) */
static void wm_m_ff6a0(GM_CTX) {
    R(4) = (R(4) + -17);
    GM_TAIL(0x800FF6C0u, 0); return;
}

/* fn_800FF6B0 (fn_800FF6B0, 8 bytes) */
static void wm_m_ff6b0(GM_CTX) {
    R(4) = (R(4) + -17);
    GM_TAIL(0x800FF730u, 0); return;
}

/* fn_800FF6C0 (fn_800FF6C0, 108 bytes) */
static void wm_m_ff6c0(GM_CTX) {
    R(0) = ((int32_t)R(4) * 48);
    { uint32_t ea_ = (R(5) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(3) + R(0);
    { uint32_t ea_ = (R(3) + 676); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 680); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(5) + 16); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 684); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(5) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 688); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 692); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(5) + 28); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 696); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(5) + 32); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 700); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(5) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 704); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(5) + 40); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 708); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(5) + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 712); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 716); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 720); stfs(base, ea_, ctx->f[1].d); }
}

/* fn_800FF730 (fn_800FF730, 16 bytes) */
static void wm_m_ff730(GM_CTX) {
    R(0) = ((int32_t)R(4) * 48);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 676);
}

/* fn_800FF740 (fn_800FF740, 780 bytes) */
static void wm_m_ff740(GM_CTX) {
    GM_FN(0x800FF740); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(28) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 660));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800FFA04; }
    R(4) = (f + 24);
    R(5) = (0 + 0);
    GM_CALLV(0x800FF798u, 0x800D5790u, 0);
    R(0) = ld32(base, (R(28) + 672));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800FF7B4; }
    R(0) = (0 + 1);
    st32(base, (R(28) + 672), R(0));
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 668); stfs(base, ea_, ctx->f[0].d); }
L_800FF7B4:;
    { uint32_t ea_ = (R(28) + 668); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24572); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[2].d - ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800FF7D4; }
    ctx->f[31].u = ctx->f[0].u;
L_800FF7D4:;
    { uint32_t ea_ = (R(2) + -24568); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800FF7E8; }
    ctx->f[31].u = ctx->f[0].u;
L_800FF7E8:;
    { uint32_t ea_ = (R(2) + -24612); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(31) = (f + 256);
    { uint32_t ea_ = (R(2) + -24564); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    R(30) = (0 + 1);
    { uint32_t ea_ = (R(2) + -24560); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
L_800FF7FC:;
    R(3) = R(28) |R(28);
    R(4) = (R(30) + -1);
    GM_CALLV(0x800FF808u, 0x800FF730u, 0);
    R(4) = (f + 40);
    GM_CALLV(0x800FF810u, 0x8016F130u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(30) |R(30);
    GM_CALLV(0x800FF81Cu, 0x800FF730u, 0);
    R(4) = (f + 52);
    GM_CALLV(0x800FF824u, 0x8016F130u, 0);
    { uint32_t ea_ = (f + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 12);
    { uint32_t ea_ = (f + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 56); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 44); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 52); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[4].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800FF85Cu, 0x801C14C0u, 0);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[30].d + ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -24612); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 160);
    ctx->f[3].u = ctx->f[1].u;
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[30].d / ctx->f[28].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d * ctx->f[0].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d / ctx->f[29].d);
    GM_CALLV(0x800FF884u, 0x801C0BD0u, 0);
    { uint32_t ea_ = (R(2) + -24612); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 64);
    ctx->f[2].u = ctx->f[1].u;
    ctx->f[3].u = ctx->f[1].u;
    GM_CALLV(0x800FF898u, 0x801C0C60u, 0);
    R(3) = (f + 160);
    R(4) = (f + 64);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800FF8A8u, 0x801C0540u, 0);
    { uint32_t ea_ = (f + 160); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(30) = (R(30) + 1);
    { uint32_t ea_ = (R(31) + 0); stfs(base, ea_, ctx->f[0].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 7);
    { uint32_t ea_ = (f + 164); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 184); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 188); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 192); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 196); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 204); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 44); stfs(base, ea_, ctx->f[0].d); }
    R(31) = (R(31) + 48);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FF7FC; }
    R(31) = (f + 256);
    R(29) = (0 + 1);
L_800FF920:;
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    GM_CALLV(0x800FF92Cu, 0x800FF730u, 0);
    { uint32_t ea_ = (R(3) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (R(29) + -1);
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 124); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 128); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 132); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 136); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 140); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 144); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 148); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 152); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(28) |R(28);
    { uint32_t ea_ = (f + 156); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800FF998u, 0x800FF730u, 0);
    R(4) = (f + 40);
    GM_CALLV(0x800FF9A0u, 0x8016F130u, 0);
    R(3) = (f + 112);
    R(4) = (f + 52);
    GM_CALLV(0x800FF9ACu, 0x8016F130u, 0);
    R(3) = (f + 40);
    R(4) = (f + 52);
    GM_CALLV(0x800FF9B8u, 0x80160EA0u, 0);
    R(0) = -(int32_t)R(3);
    R(3) = (f + 112);
    R(4) = R(3) |R(3);
    R(5) = R(31) |R(31);
    R(30) = (int16_t)R(0);
    GM_CALLV(0x800FF9D0u, 0x80238130u, 0);
    st16(base, (f + 8), R(30));
    R(3) = (f + 112);
    R(4) = (f + 8);
    GM_CALLV(0x800FF9E0u, 0x8016EEF0u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = (f + 112);
    GM_CALLV(0x800FF9F0u, 0x800FF6C0u, 0);
    R(29) = (R(29) + 1);
    R(31) = (R(31) + 48);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 7);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FF920; }
    goto L_800FFA0C;
L_800FFA04:;
    R(0) = (0 + 0);
    st32(base, (R(3) + 672), R(0));
L_800FFA0C:;
    R(0) = lr;
}

/* fn_800FFA50 (fn_800FFA50, 496 bytes) */
static void wm_m_ffa50(GM_CTX) {
    GM_FN(0x800FFA50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = (f + 32);
    R(4) = R(30) |R(30);
    GM_CALLV(0x800FFA84u, 0x800FF660u, 0);
    { uint32_t ea_ = (R(2) + -24612); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(31) = (0 + 1);
    { uint32_t ea_ = (R(2) + -24592); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
L_800FFA90:;
    R(3) = R(30) |R(30);
    R(4) = (R(31) + -1);
    GM_CALLV(0x800FFA9Cu, 0x800FF730u, 0);
    R(4) = (f + 48);
    GM_CALLV(0x800FFAA4u, 0x8016F130u, 0);
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x800FFAB0u, 0x800FF730u, 0);
    R(4) = (f + 60);
    GM_CALLV(0x800FFAB8u, 0x8016F130u, 0);
    { uint32_t ea_ = (f + 32); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 664); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800FFC0C; }
    { uint32_t ea_ = (f + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[0].d = frsp(ctx->f[0].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[1].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[5].d, ctx->f[30].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800FFAF8; }
    ctx->f[5].u = ctx->f[30].u;
L_800FFAF8:;
    { uint32_t ea_ = (f + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (f + 52); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[4].u & ~0x8000000000000000ull;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(2) + -24612); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    ctx->f[1].d = frsp(ctx->f[3].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[2].d); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[31].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800FFB48; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[5].d / ctx->f[4].d);
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[6].d = frsp(ctx->f[0].d);
L_800FFB48:;
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 72);
    { uint32_t ea_ = (f + 24); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d * ctx->f[6].d);
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d * ctx->f[6].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[6].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x800FFB74u, 0x801C0BD0u, 0);
    { uint32_t ea_ = (f + 72); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (f + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (R(31) + -1);
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[1].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 80); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[0].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 88); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[2].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 92); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[1].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 96); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[0].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 104); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 108); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 112); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[30].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[8].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800FFBECu, 0x800FF730u, 0);
    R(5) = R(3) |R(3);
    R(3) = (f + 72);
    R(4) = R(3) |R(3);
    GM_CALLV(0x800FFBFCu, 0x80238130u, 0);
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    R(5) = (f + 72);
    GM_CALLV(0x800FFC0Cu, 0x800FF6C0u, 0);
L_800FFC0C:;
    R(31) = (R(31) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 7);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FFA90; }
    R(0) = lr;
}

/* fn_800FFC40 (fn_800FFC40, 356 bytes) */
static void wm_m_ffc40(GM_CTX) {
    GM_FN(0x800FFC40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 660));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800FFC6C; }
    R(3) = (0 + 0);
    goto L_800FFD8C;
L_800FFC6C:;
    R(4) = R(30) |R(30);
    R(3) = (f + 24);
    GM_CALLV(0x800FFC78u, 0x800FF660u, 0);
    R(31) = (0 + 1);
L_800FFC7C:;
    R(3) = R(30) |R(30);
    R(4) = (R(31) + -1);
    GM_CALLV(0x800FFC88u, 0x800FF730u, 0);
    R(4) = (f + 40);
    GM_CALLV(0x800FFC90u, 0x8016F130u, 0);
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x800FFC9Cu, 0x800FF730u, 0);
    R(4) = (f + 52);
    GM_CALLV(0x800FFCA4u, 0x8016F130u, 0);
    { uint32_t ea_ = (f + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 664); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800FFD74; }
    R(3) = (f + 40);
    R(4) = (f + 52);
    R(5) = (f + 8);
    R(6) = (0 + 0);
    R(7) = (0 + 1);
    R(8) = (0 + 0);
    GM_CALLV(0x800FFCE0u, 0x80075FD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FFD74; }
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24556); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    ctx->f[0].u = ctx->f[0].u & ~0x8000000000000000ull;
    ctx->f[3].d = frsp(ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800FFD28; }
    { uint32_t ea_ = (f + 52); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[1].u;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800FFD20; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[1].d);
    goto L_800FFD24;
L_800FFD20:;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[2].d);
L_800FFD24:;
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
L_800FFD28:;
    { uint32_t ea_ = (R(30) + 664); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[3].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800FFD80; }
    R(3) = ld32(base, (R(30) + 32));
    { uint32_t ea_ = (R(30) + 664); stfs(base, ea_, ctx->f[3].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800FFD80; }
    R(0) = ld8(base, (R(3) + 908));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_800FFD80; }
    { uint32_t ea_ = (f + 48); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (f + 12);
    { uint32_t ea_ = (f + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x800FFD70u, 0x80152880u, 0);
    goto L_800FFD80;
L_800FFD74:;
    R(31) = (R(31) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 7);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800FFC7C; }
L_800FFD80:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x800FFD88u, 0x800FFA50u, 0);
    R(3) = (0 + 0);
L_800FFD8C:;
    R(0) = lr;
}

/* fn_800FFDB0 (fn_800FFDB0, 112 bytes) */
static void wm_m_ffdb0(GM_CTX) {
    GM_FN(0x800FFDB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    ctx->f[31].u = ctx->f[1].u;
    R(31) = R(3) |R(3);
    R(4) = R(31) |R(31);
    R(3) = (f + 8);
    GM_CALLV(0x800FFDDCu, 0x800FF660u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 664); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d - ctx->f[1].d);
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800FFDFC; }
    { uint32_t ea_ = (R(31) + 664); stfs(base, ea_, ctx->f[1].d); }
L_800FFDFC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800FFE04u, 0x800FFA50u, 0);
    R(0) = lr;
}

/* fn_800FFE20 (fn_800FFE20, 52 bytes) */
static void wm_m_ffe20(GM_CTX) {
    { uint32_t ea_ = (R(2) + -24608); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800FFE30; }
    ctx->f[1].u = ctx->f[0].u;
L_800FFE30:;
    { uint32_t ea_ = (R(2) + -24612); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800FFE40; }
    ctx->f[1].u = ctx->f[0].u;
L_800FFE40:;
    R(0) = ld32(base, (R(3) + 380));
    { uint32_t ea_ = (R(3) + 1012); stfs(base, ea_, ctx->f[1].d); }
    R(0) = R(0) | 0x20u;
    st32(base, (R(3) + 380), R(0));
}

/* fn_800FFE70 (fn_800FFE70, 216 bytes) */
static void wm_m_ffe70(GM_CTX) {
    R(5) = ld32(base, (R(13) + -21688));
    R(0) = (0 + 2);
    R(3) = ld8(base, (R(13) + -21768));
    R(7) = (0 + 0);
    R(6) = ld8(base, (R(5) + 4620));
    R(4) = (0 + 1);
    R(5) = ld8(base, (R(5) + 4621));
    ctx->ctr = R(0);
L_800FFE90:;
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(6));
    if ((!CR_BIT(ctx, 2))) { goto L_800FFEA0; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 23);
    if ((CR_BIT(ctx, 2))) { goto L_800FFEB8; }
L_800FFEA0:;
    { uint32_t s_ = R(7) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(3) = R(3) & 0xFFu;
    R(0) = R(0) ^ 0xFFu;
    R(0) = R(0) & 0xFFu;
    R(3) = R(3) &R(0);
    st8(base, (R(13) + -21768), R(3));
L_800FFEB8:;
    R(7) = (R(7) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(6));
    if ((!CR_BIT(ctx, 2))) { goto L_800FFECC; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 23);
    if ((CR_BIT(ctx, 2))) { goto L_800FFEE4; }
L_800FFECC:;
    { uint32_t s_ = R(7) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(3) = R(3) & 0xFFu;
    R(0) = R(0) ^ 0xFFu;
    R(0) = R(0) & 0xFFu;
    R(3) = R(3) &R(0);
    st8(base, (R(13) + -21768), R(3));
L_800FFEE4:;
    R(7) = (R(7) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(6));
    if ((!CR_BIT(ctx, 2))) { goto L_800FFEF8; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 23);
    if ((CR_BIT(ctx, 2))) { goto L_800FFF10; }
L_800FFEF8:;
    { uint32_t s_ = R(7) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(3) = R(3) & 0xFFu;
    R(0) = R(0) ^ 0xFFu;
    R(0) = R(0) & 0xFFu;
    R(3) = R(3) &R(0);
    st8(base, (R(13) + -21768), R(3));
L_800FFF10:;
    R(7) = (R(7) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(6));
    if ((!CR_BIT(ctx, 2))) { goto L_800FFF24; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 23);
    if ((CR_BIT(ctx, 2))) { goto L_800FFF3C; }
L_800FFF24:;
    { uint32_t s_ = R(7) & 63; R(0) = s_ > 31 ? 0 : R(4) << s_; }
    R(3) = R(3) & 0xFFu;
    R(0) = R(0) ^ 0xFFu;
    R(0) = R(0) & 0xFFu;
    R(3) = R(3) &R(0);
    st8(base, (R(13) + -21768), R(3));
L_800FFF3C:;
    R(7) = (R(7) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_800FFE90; }
}

/* fn_800FFF90 (fn_800FFF90, 40 bytes) */
static void wm_m_fff90(GM_CTX) {
    R(3) = ld32(base, (R(13) + -21688));
    R(0) = ld8(base, (R(3) + 4620));
    R(3) = ld8(base, (R(3) + 4621));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 7);
    if ((!CR_BIT(ctx, 2))) { goto L_800FFFAC; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 37);
    if ((CR_BIT(ctx, 2))) return;
L_800FFFAC:;
    R(0) = (0 + 0);
    st8(base, (R(13) + -21760), R(0));
}

/* fn_800FFFC0 (fn_800FFFC0, 20 bytes) */
static void wm_m_fffc0(GM_CTX) {
    R(3) = (0 + 0x80320000u);
    R(0) = ld16(base, (R(2) + -24552));
    R(3) = (R(3) + -14344);
    st16(base, (R(3) + 2), R(0));
}

/* fn_800FFFE0 (fn_800FFFE0, 76 bytes) */
static void wm_m_fffe0(GM_CTX) {
    GM_FN(0x800FFFE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 595);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x80100004u, 0x80064610u, 0);
    R(3) = (0 + 595);
    R(4) = (0 + 1);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    R(7) = (0 + 0);
    GM_CALLV(0x8010001Cu, 0x80064610u, 0);
    R(0) = lr;
}

/* fn_80100200 (fn_80100200, 100 bytes) */
static void wm_m_00200(GM_CTX) {
    GM_FN(0x80100200); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = (R(31) + 0x60000u);
    R(0) = ld32(base, (R(4) + 13196));
    R(4) = R(5) |R(5);
    R(0) = ((int32_t)R(0) * 16136);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + -14348);
    GM_CALLV(0x80100238u, 0x800F32F0u, 0);
    R(5) = R(3) |R(3);
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    R(5) = (R(5) + 4);
    GM_CALLV(0x8010024Cu, 0x80100270u, 0);
    R(0) = lr;
}

/* fn_80100270 (fn_80100270, 80 bytes) */
static void wm_m_00270(GM_CTX) {
    GM_FN(0x80100270); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = R(4) |R(4);
    R(4) = R(5) |R(5);
    R(5) = (f + 8);
    GM_CALLV(0x80100294u, 0x801006E0u, 0);
    R(3) = ld32(base, (f + 8));
    R(0) = ld32(base, (f + 12));
    st32(base, (R(31) + 4), R(0));
    st32(base, (R(31) + 0), R(3));
    R(0) = ld32(base, (f + 16));
    st32(base, (R(31) + 8), R(0));
    R(0) = lr;
}

/* fn_801002C0 (fn_801002C0, 8 bytes) */
static void wm_m_002c0(GM_CTX) {
    R(5) = ld32(base, (R(3) + 13196));
    GM_TAIL(0x801002D0u, 0); return;
}

/* fn_801002D0 (fn_801002D0, 24 bytes) */
static void wm_m_002d0(GM_CTX) {
    R(6) = (0 + 0x10000u);
    R(0) = (R(6) + 25880);
    R(0) = ((int32_t)R(5) * (int32_t)R(0));
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 13204);
    GM_TAIL(0x800F53A0u, 0); return;
}

/* fn_801002F0 (fn_801002F0, 148 bytes) */
static void wm_m_002f0(GM_CTX) {
    GM_FN(0x801002F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x10000u);
    R(31) = (R(4) + 25880);
    R(30) = (0 + 0);
    R(29) = R(3) |R(3);
    goto L_8010034C;
L_8010031C:;
    R(3) = R(29) + R(4);
    R(4) = R(30) |R(30);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x8010032Cu, 0x800F56B0u, 0);
    R(0) = ld8(base, (R(3) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 87);
    if ((!CR_BIT(ctx, 2))) { goto L_80100348; }
    R(0) = ld8(base, (R(3) + 2));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 83);
    if ((!CR_BIT(ctx, 2))) { goto L_80100348; }
    goto L_80100368;
L_80100348:;
    R(30) = (R(30) + 1);
L_8010034C:;
    R(0) = ld32(base, (R(29) + 13196));
    R(4) = ((int32_t)R(0) * (int32_t)R(31));
    R(3) = R(29) + R(4);
    R(0) = ld32(base, (R(3) + 13216));
    cr_cmp_s(ctx, 0, (int32_t)R(30), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8010031C; }
    R(3) = (0 + 0);
L_80100368:;
    R(0) = lr;
}

/* fn_80100430 (fn_80100430, 116 bytes) */
static void wm_m_00430(GM_CTX) {
    GM_FN(0x80100430); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 13196));
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x8010045Cu, 0x800F0F30u, 0);
    R(31) = (0 + 0);
    goto L_80100480;
L_80100464:;
    R(0) = ld32(base, (R(30) + 13196));
    R(4) = R(3) |R(3);
    R(31) = (R(31) + 1);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 424);
    GM_CALLV(0x80100480u, 0x800DFCE0u, 0);
L_80100480:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80100464; }
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_801004B0 (fn_801004B0, 120 bytes) */
static void wm_m_004b0(GM_CTX) {
    GM_FN(0x801004B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 13196));
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 416);
    GM_CALLV(0x801004E0u, 0x800F0F30u, 0);
    goto L_80100500;
L_801004E4:;
    R(0) = ld32(base, (R(30) + 13196));
    R(4) = R(3) |R(3);
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 424);
    GM_CALLV(0x801004FCu, 0x800DFCE0u, 0);
    R(31) = (R(31) + -1);
L_80100500:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_80100510; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 1))) { GM_LOOP(); goto L_801004E4; }
L_80100510:;
    R(0) = lr;
}

/* fn_80100530 (fn_80100530, 132 bytes) */
static void wm_m_00530(GM_CTX) {
    GM_FN(0x80100530); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0);
    R(30) = R(5) |R(5);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    goto L_80100584;
L_80100560:;
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(5) = R(31) |R(31);
    R(6) = R(30) |R(30);
    GM_CALLV(0x80100574u, 0x801005C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100580; }
    goto L_80100594;
L_80100580:;
    R(31) = (R(31) + 1);
L_80100584:;
    R(0) = ld32(base, (R(28) + 13200));
    cr_cmp_s(ctx, 0, (int32_t)R(31), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80100560; }
    R(3) = (0 + 0);
L_80100594:;
    R(0) = lr;
}

/* fn_801005C0 (fn_801005C0, 244 bytes) */
static void wm_m_005c0(GM_CTX) {
    GM_FN(0x801005C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(0) = ((int32_t)R(5) * 3064);
    R(26) = R(4) |R(4);
    R(27) = R(6) |R(6);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 424);
    GM_CALLV(0x801005ECu, 0x80168400u, 0);
    st32(base, (f + 8), R(3));
    R(3) = R(26) |R(26);
    GM_CALLV(0x801005F8u, 0x802DC69Cu, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    R(30) = R(3) |R(3);
    R(31) = (0 + 0);
    R(29) = (0 + 0);
    R(28) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100678; }
    R(3) = ld32(base, (R(27) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100624; }
    R(3) = ld32(base, (R(3) + 12));
    goto L_80100628;
L_80100624:;
    R(3) = R(31) |R(31);
L_80100628:;
    R(28) = (R(3) + 1);
    goto L_80100678;
L_80100630:;
    R(4) = R(28) |R(28);
    R(3) = (f + 8);
    GM_CALLV(0x8010063Cu, 0x8023B2A0u, 0);
    R(0) = ld32(base, (R(3) + 8));
    R(31) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100654; }
    R(3) = R(3) + R(0);
    goto L_80100658;
L_80100654:;
    R(3) = (0 + 0);
L_80100658:;
    R(4) = R(26) |R(26);
    R(5) = R(30) |R(30);
    GM_CALLV(0x80100664u, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80100674; }
    R(29) = (0 + 1);
    goto L_80100688;
L_80100674:;
    R(28) = (R(28) + 1);
L_80100678:;
    R(3) = (f + 8);
    GM_CALLV(0x80100680u, 0x8023B360u, 0);
    cr_cmp_u(ctx, 0, R(28), R(3));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80100630; }
L_80100688:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100698; }
    R(3) = R(31) |R(31);
    goto L_8010069C;
L_80100698:;
    R(3) = (0 + 0);
L_8010069C:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* GetNodePos__9daWmMap_cFlR7mVec3_c (GetNodePos__9daWmMap_cFlR7mVec3_c, 20 bytes) */
static void wm_GetNodePos__9daWmMap_cFlR7mVec3_c_006c0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 13196));
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 416);
    GM_TAIL(0x800F0EB0u, 0); return;
}

/* fn_801006E0 (fn_801006E0, 20 bytes) */
static void wm_m_006e0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 13196));
    R(0) = ((int32_t)R(0) * 3064);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 416);
    GM_TAIL(0x800F0EC0u, 0); return;
}

/* GetNodeCount__9daWmMap_cFi (GetNodeCount__9daWmMap_cFi, 272 bytes) */
static void wm_GetNodeCount__9daWmMap_cFi_00720(GM_CTX) {
    GM_FN(0x80100720); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x10000u);
    R(31) = (R(5) + 25880);
    R(30) = (0 + 0);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
L_80100750:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8010076C; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 1);
    if ((CR_BIT(ctx, 2))) { goto L_80100788; }
    cr_cmp_s(ctx, 0, (int32_t)R(29), 2);
    if ((CR_BIT(ctx, 2))) { goto L_801007CC; }
    goto L_801007E4;
L_8010076C:;
    R(6) = R(30) |R(30);
    R(3) = (f + 8);
    R(4) = (0 + 8);
    R(5) = (R(13) + -26680);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80100784u, 0x802E16E8u, 0);
    goto L_801007E4;
L_80100788:;
    R(0) = ld8(base, (R(13) + -21555));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_801007B0; }
    R(6) = R(30) |R(30);
    R(3) = (f + 8);
    R(4) = (0 + 8);
    R(5) = (R(13) + -26680);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x801007ACu, 0x802E16E8u, 0);
    goto L_801007E4;
L_801007B0:;
    R(6) = R(30) |R(30);
    R(3) = (f + 8);
    R(4) = (0 + 8);
    R(5) = (R(13) + -26672);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x801007C8u, 0x802E16E8u, 0);
    goto L_801007E4;
L_801007CC:;
    R(6) = R(30) |R(30);
    R(3) = (f + 8);
    R(4) = (0 + 8);
    R(5) = (R(13) + -26664);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x801007E4u, 0x802E16E8u, 0);
L_801007E4:;
    R(0) = ld32(base, (R(28) + 13196));
    R(4) = (f + 8);
    R(0) = ((int32_t)R(0) * (int32_t)R(31));
    R(3) = R(28) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x801007FCu, 0x800F53A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 0))) { goto L_8010080C; }
    R(30) = (R(30) + 1);
    GM_LOOP(); goto L_80100750;
L_8010080C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_80100830 (fn_80100830, 168 bytes) */
static void wm_m_00830(GM_CTX) {
    GM_FN(0x80100830); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24544); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -14160);
    { uint32_t ea_ = (R(2) + -24540); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24536); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 2272);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15664);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80100888u, 0x802DC780u, 0);
    R(0) = ld8(base, (R(13) + -21744));
    R(3) = ld32(base, (R(2) + -24828));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    st32(base, (R(13) + -21752), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_801008C8; }
    R(3) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24532); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(3) + -13904);
    R(0) = (0 + 1);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(13) + -21744), R(0));
L_801008C8:;
    R(0) = lr;
}

/* checkWalkPlayers__12daWmPlayer_cFv (checkWalkPlayers__12daWmPlayer_cFv, 60 bytes) */
static void wm_checkWalkPlayers__12daWmPlayer_cFv_00900(GM_CTX) {
    R(3) = ld32(base, (R(13) + -21728));
    goto L_8010092C;
L_80100908:;
    R(0) = ld8(base, (R(3) + 292));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100928; }
    R(0) = ld8(base, (R(3) + 396));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100928; }
    R(3) = (0 + 1);
    return;
L_80100928:;
    R(3) = ld32(base, (R(3) + 388));
L_8010092C:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_80100908; }
    R(3) = (0 + 0);
}

/* fn_80100970 (fn_80100970, 136 bytes) */
static void wm_m_00970(GM_CTX) {
    cr_cmp_u(ctx, 0, R(3), 0x17u);
    if ((CR_BIT(ctx, 1))) { goto L_801009F0; }
    R(4) = (0 + 0x80320000u);
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + -10352);
    R(4) = ld32(base, (R(4) + R(0)));
    ctx->ctr = R(4);
    { switch (ctx->ctr) { case 0x80100990u: goto L_80100990; case 0x80100998u: goto L_80100998; case 0x801009A0u: goto L_801009A0; case 0x801009A8u: goto L_801009A8; case 0x801009B0u: goto L_801009B0; case 0x801009B8u: goto L_801009B8; case 0x801009C0u: goto L_801009C0; case 0x801009C8u: goto L_801009C8; case 0x801009D0u: goto L_801009D0; case 0x801009D8u: goto L_801009D8; case 0x801009E0u: goto L_801009E0; case 0x801009E8u: goto L_801009E8; case 0x801009F0u: goto L_801009F0; default: rt_fatal("80100970: jump table target %08X", ctx->ctr); return; } }
L_80100990:;
    R(3) = (0 + 3);
    return;
L_80100998:;
    R(3) = (0 + 4);
    return;
L_801009A0:;
    R(3) = (0 + 8);
    return;
L_801009A8:;
    R(3) = (0 + 9);
    return;
L_801009B0:;
    R(3) = (0 + 6);
    return;
L_801009B8:;
    R(3) = (0 + 7);
    return;
L_801009C0:;
    R(3) = (0 + 2);
    return;
L_801009C8:;
    R(3) = (0 + 2);
    return;
L_801009D0:;
    R(3) = (0 + 5);
    return;
L_801009D8:;
    R(3) = (0 + 10);
    return;
L_801009E0:;
    R(3) = (0 + 2);
    return;
L_801009E8:;
    R(3) = (0 + 8);
    return;
L_801009F0:;
    R(3) = (0 + 47);
}

/* fn_80100A00 (fn_80100A00, 76 bytes) */
static void wm_m_00a00(GM_CTX) {
    R(0) = (R(3) + -4);
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 1))) { goto L_80100A34; }
    R(0) = (R(3) + -1);
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_80100A34; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100A2C; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 2))) { goto L_80100A3C; }
    goto L_80100A44;
L_80100A2C:;
    { uint32_t ea_ = (R(2) + -24508); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    return;
L_80100A34:;
    { uint32_t ea_ = (R(2) + -24504); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    return;
L_80100A3C:;
    { uint32_t ea_ = (R(2) + -24500); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    return;
L_80100A44:;
    { uint32_t ea_ = (R(2) + -24504); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_80100AA0 (fn_80100AA0, 156 bytes) */
static void wm_m_00aa0(GM_CTX) {
    GM_FN(0x80100AA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x1000000u);
    R(31) = (0 + 0x10000u);
    R(0) = (R(31) + 25880);
    R(29) = R(3) |R(3);
    R(4) = R(29) |R(29);
    R(30) = ld32(base, (R(13) + -21748));
    R(3) = ld32(base, (R(30) + 13196));
    R(0) = ((int32_t)R(3) * (int32_t)R(0));
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x80100AE4u, 0x800F57A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100AF4; }
    R(3) = (0 + 47);
    goto L_80100B20;
L_80100AF4:;
    R(3) = ld32(base, (R(30) + 13196));
    R(0) = (R(31) + 25880);
    R(4) = R(29) |R(29);
    R(5) = (0 + 0x800000u);
    R(0) = ((int32_t)R(3) * (int32_t)R(0));
    R(3) = R(30) + R(0);
    R(3) = (R(3) + 13204);
    GM_CALLV(0x80100B14u, 0x800F57A0u, 0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(3) = rotl32(R(0), 1) & 0x1u;
L_80100B20:;
    R(0) = lr;
}

/* fn_80100BD0 (fn_80100BD0, 204 bytes) */
static void wm_m_00bd0(GM_CTX) {
    cr_cmp_u(ctx, 0, R(3), 0x1Au);
    if ((CR_BIT(ctx, 1))) { goto L_80100C94; }
    R(5) = (0 + 0x80320000u);
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(5) = (R(5) + -10204);
    R(5) = ld32(base, (R(5) + R(0)));
    ctx->ctr = R(5);
    { switch (ctx->ctr) { case 0x80100BF0u: goto L_80100BF0; case 0x80100BF8u: goto L_80100BF8; case 0x80100C00u: goto L_80100C00; case 0x80100C14u: goto L_80100C14; case 0x80100C1Cu: goto L_80100C1C; case 0x80100C24u: goto L_80100C24; case 0x80100C2Cu: goto L_80100C2C; case 0x80100C40u: goto L_80100C40; case 0x80100C54u: goto L_80100C54; case 0x80100C5Cu: goto L_80100C5C; case 0x80100C64u: goto L_80100C64; case 0x80100C6Cu: goto L_80100C6C; case 0x80100C74u: goto L_80100C74; case 0x80100C7Cu: goto L_80100C7C; case 0x80100C84u: goto L_80100C84; case 0x80100C8Cu: goto L_80100C8C; case 0x80100C94u: goto L_80100C94; default: rt_fatal("80100BD0: jump table target %08X", ctx->ctr); return; } }
L_80100BF0:;
    R(3) = (0 + 121);
    return;
L_80100BF8:;
    R(3) = (0 + 16);
    return;
L_80100C00:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 2);
    R(3) = (0 + 121);
    if ((!CR_BIT(ctx, 2))) return;
    R(3) = (0 + 18);
    return;
L_80100C14:;
    R(3) = (0 + 19);
    return;
L_80100C1C:;
    R(3) = (0 + 20);
    return;
L_80100C24:;
    R(3) = (0 + 21);
    return;
L_80100C2C:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 2);
    R(3) = (0 + 121);
    if ((!CR_BIT(ctx, 2))) return;
    R(3) = (0 + 18);
    return;
L_80100C40:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 2);
    R(3) = (0 + 121);
    if ((!CR_BIT(ctx, 2))) return;
    R(3) = (0 + 21);
    return;
L_80100C54:;
    R(3) = (0 + 18);
    return;
L_80100C5C:;
    R(3) = (0 + 23);
    return;
L_80100C64:;
    R(3) = (0 + 22);
    return;
L_80100C6C:;
    R(3) = (0 + 26);
    return;
L_80100C74:;
    R(3) = (0 + 27);
    return;
L_80100C7C:;
    R(3) = (0 + 25);
    return;
L_80100C84:;
    R(3) = (0 + 9);
    return;
L_80100C8C:;
    R(3) = (0 + 17);
    return;
L_80100C94:;
    R(3) = (0 + 121);
}

/* fn_80100CA0 (fn_80100CA0, 240 bytes) */
static void wm_m_00ca0(GM_CTX) {
    GM_FN(0x80100CA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 24);
    R(31) = (0 + 0);
    R(30) = R(4) |R(4);
    if ((CR_BIT(ctx, 2))) { goto L_80100CE0; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 25);
    if ((CR_BIT(ctx, 2))) { goto L_80100CE0; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 2))) { goto L_80100CE0; }
    R(0) = (R(3) + -21);
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_80100D18; }
L_80100CE0:;
    { uint32_t ea_ = (R(2) + -24496); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (0 + 0);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80100CFC; }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_80100D14; }
L_80100CFC:;
    { uint32_t ea_ = (R(2) + -24492); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80100D18; }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80100D18; }
L_80100D14:;
    R(31) = (0 + 1);
L_80100D18:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 6);
    if ((!CR_BIT(ctx, 2))) { goto L_80100D58; }
    { uint32_t ea_ = (R(2) + -24488); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (0 + 0);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80100D3C; }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_80100D54; }
L_80100D3C:;
    { uint32_t ea_ = (R(2) + -24484); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80100D58; }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80100D58; }
L_80100D54:;
    R(31) = (0 + 1);
L_80100D58:;
    GM_CALLV(0x80100D5Cu, 0x80100F70u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100D74; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 2);
    if ((CR_BIT(ctx, 2))) { goto L_80100D74; }
    R(3) = (0 + 0);
    goto L_80100D78;
L_80100D74:;
    R(3) = R(31) |R(31);
L_80100D78:;
    R(0) = lr;
}

/* fn_80100D90 (fn_80100D90, 8 bytes) */
static void wm_m_00d90(GM_CTX) {
    R(5) = (R(4) + 172);
    GM_TAIL(0x80100DA0u, 0); return;
}

/* fn_80100DA0 (fn_80100DA0, 460 bytes) */
static void wm_m_00da0(GM_CTX) {
    GM_FN(0x80100DA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -24480); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(6) = (f + 24);
    { uint32_t ea_ = (R(2) + -24504); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = R(3) |R(3);
    R(30) = R(4) |R(4);
    R(4) = R(5) |R(5);
    R(5) = (f + 32);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x80100DE4u, 0x800F9EA0u, 0);
    R(3) = ld32(base, (R(13) + -21748));
    R(0) = ld32(base, (R(3) + 13196));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80100EBC; }
    R(0) = ld8(base, (R(13) + -21555));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_80100E68; }
    { uint32_t ea_ = (R(31) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24480); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80100E1C; }
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[2].d); }
    goto L_80100EBC;
L_80100E1C:;
    { uint32_t ea_ = (R(2) + -24504); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80100E34; }
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[1].d); }
    goto L_80100EBC;
L_80100E34:;
    { uint32_t ea_ = (R(31) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_80100E50; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80100EBC; }
L_80100E50:;
    { uint32_t ea_ = (R(2) + -24476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[0].d); }
    goto L_80100EBC;
L_80100E68:;
    { uint32_t ea_ = (R(31) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24480); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_80100EA8; }
    { uint32_t ea_ = (R(31) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_80100EA8; }
    { uint32_t ea_ = (R(2) + -24504); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_80100EA8; }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80100EBC; }
L_80100EA8:;
    { uint32_t ea_ = (R(2) + -24476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[0].d); }
L_80100EBC:;
    R(4) = ld32(base, (R(13) + -20992));
    R(0) = (0 + 0x43300000u);
    R(3) = (0 + 0x80320000u);
    st32(base, (f + 40), R(0));
    R(4) = ld32(base, (R(4) + 0));
    R(3) = (R(3) + -11364);
    st32(base, (f + 48), R(0));
    R(4) = ld16(base, (R(4) + 4));
    { uint32_t ea_ = (R(2) + -24472); ctx->f[3].u = ld64(base, ea_); }
    R(4) = rotl32(R(4), 31) & 0x7FFFFFFFu;
    { uint32_t ea_ = (R(31) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = R(4) ^ 0x80000000u;
    st32(base, (f + 44), R(0));
    { uint32_t ea_ = (R(31) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 40); ctx->f[2].u = ld64(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d * ctx->f[2].d);
    { uint32_t ea_ = (R(31) + 0); stfs(base, ea_, ctx->f[2].d); }
    R(4) = ld32(base, (R(13) + -20992));
    R(4) = ld32(base, (R(4) + 0));
    R(0) = ld16(base, (R(4) + 6));
    R(0) = rotl32(R(0), 31) & 0x7FFFFFFFu;
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 52), R(0));
    { uint32_t ea_ = (f + 48); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[1].d); }
    R(4) = ld32(base, (R(30) + 464));
    R(0) = ld8(base, (R(4) + 338));
    R(0) = rotl32(R(0), 3) & 0xFFFFFFF8u;
    R(3) = R(3) + R(0);
    { uint32_t ea_ = (R(3) + 120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 124); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_80100F70 (fn_80100F70, 32 bytes) */
static void wm_m_00f70(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(3), 7);
    R(0) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_80100F84; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 8);
    if ((!CR_BIT(ctx, 2))) { goto L_80100F88; }
L_80100F84:;
    R(0) = (0 + 1);
L_80100F88:;
    R(3) = R(0) |R(0);
}

/* fn_80101430 (fn_80101430, 336 bytes) */
static void wm_m_01430(GM_CTX) {
    GM_FN(0x80101430); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24460); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -11400);
    { uint32_t ea_ = (R(2) + -24456); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24452); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 5504);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15680);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80101488u, 0x802DC780u, 0);
    R(0) = ld8(base, (R(13) + -21724));
    R(3) = ld32(base, (R(2) + -24828));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    st32(base, (R(13) + -21736), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_80101570; }
    R(3) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24504); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    R(3) = (R(3) + -11364);
    { uint32_t ea_ = (R(2) + -24484); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24476); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (0 + 25);
    { uint32_t ea_ = (R(2) + -24448); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(2) + -24488); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24444); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24440); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st16(base, (R(3) + 30), R(4));
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 132); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 140); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(3) + 144); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 148); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 156); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 160); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 164); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 544); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 548); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 552); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 556); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 560); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 564); stfs(base, ea_, ctx->f[2].d); }
    st8(base, (R(13) + -21724), R(0));
L_80101570:;
    R(0) = lr;
}

/* fn_801015A0 (fn_801015A0, 52 bytes) */
static void wm_m_015a0(GM_CTX) {
    R(5) = ld32(base, (R(3) + 424));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 0))) { goto L_801015CC; }
    R(4) = (0 + 0x80320000u);
    R(0) = ld32(base, (R(3) + 344));
    R(3) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + -10060);
    R(0) = rotl32(R(0), 3) & 0xFFFFFFF8u;
    R(3) = ld32(base, (R(4) + R(3)));
    R(3) = R(3) + R(0);
    return;
L_801015CC:;
    R(3) = (0 + 0);
}

/* GetCutName__11dCsSeqMng_cFv (GetCutName__11dCsSeqMng_cFv, 76 bytes) */
static void wm_GetCutName__11dCsSeqMng_cFv_015e0(GM_CTX) {
    GM_FN(0x801015E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x801015F8u, 0x801015A0u, 0);
    R(0) = ld8(base, (R(31) + 357));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80101614; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80101614; }
    R(3) = ld32(base, (R(3) + 0));
    goto L_80101618;
L_80101614:;
    R(3) = (0 + -1);
L_80101618:;
    R(0) = lr;
}

/* fn_80101630 (fn_80101630, 52 bytes) */
static void wm_m_01630(GM_CTX) {
    GM_FN(0x80101630); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x80101640u, 0x801015A0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80101650; }
    R(3) = ld32(base, (R(3) + 4));
    goto L_80101654;
L_80101650:;
    R(3) = (0 + -1);
L_80101654:;
    R(0) = lr;
}

/* fn_80101670 (fn_80101670, 28 bytes) */
static void wm_m_01670(GM_CTX) {
    R(0) = (0 + 0);
    R(4) = (0 + -1);
    st32(base, (R(3) + 0), R(4));
    st32(base, (R(3) + 4), R(0));
    st32(base, (R(3) + 8), R(0));
    st32(base, (R(3) + 12), R(0));
}

/* fn_80101690 (fn_80101690, 20 bytes) */
static void wm_m_01690(GM_CTX) {
    st32(base, (R(3) + 0), R(4));
    st32(base, (R(3) + 4), R(7));
    st32(base, (R(3) + 8), R(5));
    st32(base, (R(3) + 12), R(6));
}

/* fn_80101720 (fn_80101720, 112 bytes) */
static void wm_m_01720(GM_CTX) {
    GM_FN(0x80101720); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24432); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + -10096);
    { uint32_t ea_ = (R(2) + -24428); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 6032);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15696);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80101778u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21720), R(0));
    R(0) = lr;
}

/* fn_80101940 (fn_80101940, 16 bytes) */
static void wm_m_01940(GM_CTX) {
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = (R(13) + -21692);
    st32(base, (R(3) + R(0)), R(4));
}

/* fn_80101950 (fn_80101950, 16 bytes) */
static void wm_m_01950(GM_CTX) {
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(3) = (R(13) + -21692);
    R(3) = ld32(base, (R(3) + R(0)));
}

/* fn_80101960 (fn_80101960, 40 bytes) */
static void wm_m_01960(GM_CTX) {
    R(3) = ld32(base, (R(13) + -21688));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80101974; }
    R(3) = (0 + 0);
    return;
L_80101974:;
    R(3) = ld32(base, (R(3) + 4564));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) return;
    R(3) = (0 + 0);
}

/* setChangePosFunc__10dScStage_cFi (setChangePosFunc__10dScStage_cFi, 24 bytes) */
static void wm_setChangePosFunc__10dScStage_cFi_01bc0(GM_CTX) {
    R(4) = (0 + 0x802F0000u);
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + 18968);
    R(0) = ld32(base, (R(4) + R(0)));
    st32(base, (R(13) + -21592), R(0));
}

/* fn_80101BE0 (fn_80101BE0, 4 bytes) */
static void wm_m_01be0(GM_CTX) {

}

/* fn_80101BF0 (fn_80101BF0, 100 bytes) */
static void wm_m_01bf0(GM_CTX) {
    R(4) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(3) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = ld32(base, (R(13) + -22704));
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d - ctx->f[2].d);
    { uint32_t ea_ = (R(2) + -24396); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (R(5) + 0x90000u);
    { uint32_t ea_ = (R(4) + -352); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80101C38; }
    ctx->f[1].u = ctx->f[3].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(2) + -24392); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) return;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[3].d);
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[0].d); }
    return;
L_80101C38:;
    { uint32_t ea_ = (R(2) + -24392); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d * ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) return;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[3].d);
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_80101C60 (fn_80101C60, 116 bytes) */
static void wm_m_01c60(GM_CTX) {
    GM_FN(0x80101C60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(31) = (R(31) + 15752);
    R(29) = R(3) |R(3);
    R(0) = ld32(base, (R(13) + -21620));
    R(30) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    GM_CALLV(0x80101C90u, 0x802DC69Cu, 0);
    R(3) = (R(3) + 1);
    R(0) = rotl32(R(3), 1) & 0xFFFFFFFEu;
    R(3) = R(0) - R(3);
    GM_CALLV(0x80101CA0u, 0x802B9250u, 0);
    st32(base, (R(31) + R(30)), R(3));
    R(4) = R(29) |R(29);
    GM_CALLV(0x80101CACu, 0x802E1938u, 0);
    R(3) = ld32(base, (R(13) + -21620));
    R(0) = (R(3) + 1);
    st32(base, (R(13) + -21620), R(0));
    R(0) = lr;
}

/* fn_80101CE0 (fn_80101CE0, 84 bytes) */
static void wm_m_01ce0(GM_CTX) {
    GM_FN(0x80101CE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(31) = (R(31) + 15752);
    goto L_80101D14;
L_80101CFC:;
    R(3) = ld32(base, (R(13) + -21620));
    R(0) = (R(3) + -1);
    st32(base, (R(13) + -21620), R(0));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(31) + R(0)));
    GM_CALLV(0x80101D14u, 0x802B9290u, 0);
L_80101D14:;
    R(0) = ld32(base, (R(13) + -21620));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_80101CFC; }
    R(0) = lr;
}

/* fn_80101D40 (fn_80101D40, 116 bytes) */
static void wm_m_01d40(GM_CTX) {
    GM_FN(0x80101D40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(31) = (R(31) + 15816);
    R(29) = R(3) |R(3);
    R(0) = ld32(base, (R(13) + -21616));
    R(30) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    GM_CALLV(0x80101D70u, 0x802DC69Cu, 0);
    R(3) = (R(3) + 1);
    R(0) = rotl32(R(3), 1) & 0xFFFFFFFEu;
    R(3) = R(0) - R(3);
    GM_CALLV(0x80101D80u, 0x802B9250u, 0);
    st32(base, (R(31) + R(30)), R(3));
    R(4) = R(29) |R(29);
    GM_CALLV(0x80101D8Cu, 0x802E1938u, 0);
    R(3) = ld32(base, (R(13) + -21616));
    R(0) = (R(3) + 1);
    st32(base, (R(13) + -21616), R(0));
    R(0) = lr;
}

/* fn_80101DC0 (fn_80101DC0, 84 bytes) */
static void wm_m_01dc0(GM_CTX) {
    GM_FN(0x80101DC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(31) = (R(31) + 15816);
    goto L_80101DF4;
L_80101DDC:;
    R(3) = ld32(base, (R(13) + -21616));
    R(0) = (R(3) + -1);
    st32(base, (R(13) + -21616), R(0));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(31) + R(0)));
    GM_CALLV(0x80101DF4u, 0x802B9290u, 0);
L_80101DF4:;
    R(0) = ld32(base, (R(13) + -21616));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_80101DDC; }
    R(0) = lr;
}

/* fn_80101E20 (fn_80101E20, 116 bytes) */
static void wm_m_01e20(GM_CTX) {
    GM_FN(0x80101E20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(31) = (R(31) + 16616);
    R(29) = R(3) |R(3);
    R(0) = ld32(base, (R(13) + -21612));
    R(30) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    GM_CALLV(0x80101E50u, 0x802DC69Cu, 0);
    R(3) = (R(3) + 1);
    R(0) = rotl32(R(3), 1) & 0xFFFFFFFEu;
    R(3) = R(0) - R(3);
    GM_CALLV(0x80101E60u, 0x802B9250u, 0);
    st32(base, (R(31) + R(30)), R(3));
    R(4) = R(29) |R(29);
    GM_CALLV(0x80101E6Cu, 0x802E1938u, 0);
    R(3) = ld32(base, (R(13) + -21612));
    R(0) = (R(3) + 1);
    st32(base, (R(13) + -21612), R(0));
    R(0) = lr;
}

/* fn_80101EA0 (fn_80101EA0, 84 bytes) */
static void wm_m_01ea0(GM_CTX) {
    GM_FN(0x80101EA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80370000u);
    R(31) = (R(31) + 16616);
    goto L_80101ED4;
L_80101EBC:;
    R(3) = ld32(base, (R(13) + -21612));
    R(0) = (R(3) + -1);
    st32(base, (R(13) + -21612), R(0));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = ld32(base, (R(31) + R(0)));
    GM_CALLV(0x80101ED4u, 0x802B9290u, 0);
L_80101ED4:;
    R(0) = ld32(base, (R(13) + -21612));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_80101EBC; }
    R(0) = lr;
}

/* fn_80101F00 (fn_80101F00, 76 bytes) */
static void wm_m_01f00(GM_CTX) {
    R(6) = ld32(base, (R(13) + -21608));
    R(4) = (0 + 0x80370000u);
    R(4) = (R(4) + 16776);
    ctx->ctr = R(6);
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80101F2C; }
L_80101F18:;
    R(0) = ld32(base, (R(4) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((CR_BIT(ctx, 2))) return;
    R(4) = (R(4) + 4);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80101F18; }
L_80101F2C:;
    R(4) = ld32(base, (R(13) + -21608));
    R(5) = (0 + 0x80370000u);
    R(6) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(5) = (R(5) + 16776);
    R(0) = (R(4) + 1);
    st32(base, (R(5) + R(6)), R(3));
    st32(base, (R(13) + -21608), R(0));
}

/* fn_80101F50 (fn_80101F50, 124 bytes) */
static void wm_m_01f50(GM_CTX) {
    R(7) = ld32(base, (R(13) + -21608));
    R(3) = (0 + 0x80370000u);
    R(3) = (R(3) + 16776);
    R(5) = (0 + 14);
    cr_cmp_s(ctx, 0, (int32_t)R(7), 0);
    R(0) = rotl32(R(7), 2) & 0xFFFFFFFCu;
    R(4) = R(7) |R(7);
    R(6) = R(3) + R(0);
    if ((CR_BIT(ctx, 2))) { goto L_80101FC4; }
    R(3) = rotl32(R(7), 29) & 0x1FFFFFFFu;
    CR0(ctx, R(3));
    R(0) = -(int32_t)R(7);
    ctx->ctr = R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80101FB0; }
L_80101F84:;
    st32(base, (R(6) + -4), R(5));
    st32(base, (R(6) + -8), R(5));
    st32(base, (R(6) + -12), R(5));
    st32(base, (R(6) + -16), R(5));
    st32(base, (R(6) + -20), R(5));
    st32(base, (R(6) + -24), R(5));
    st32(base, (R(6) + -28), R(5));
    { uint32_t ea_ = R(6) + -32; st32(base, ea_, R(5)); R(6) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80101F84; }
    R(4) = R(7) & 0x7u;
    CR0(ctx, R(4));
    if ((CR_BIT(ctx, 2))) { goto L_80101FC0; }
L_80101FB0:;
    ctx->ctr = R(4);
    R(0) = R(0) | 0x0u;
L_80101FB8:;
    { uint32_t ea_ = R(6) + -4; st32(base, ea_, R(5)); R(6) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80101FB8; }
L_80101FC0:;
    R(7) = R(7) + R(0);
L_80101FC4:;
    st32(base, (R(13) + -21608), R(7));
}

/* fn_801020F0 (fn_801020F0, 80 bytes) */
static void wm_m_020f0(GM_CTX) {
    GM_FN(0x801020F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0);
L_80102104:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8010210Cu, 0x80102060u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8010211C; }
    R(3) = (0 + 0);
    goto L_8010212C;
L_8010211C:;
    R(31) = (R(31) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80102104; }
    R(3) = (0 + 1);
L_8010212C:;
    R(0) = lr;
}

/* createReplayDataHeap__10dScStage_cFPQ23EGG4HeapUli (createReplayDataHeap__10dScStage_cFPQ23EGG4HeapUli, 80 bytes) */
static void wm_createReplayDataHeap__10dScStage_cFPQ23E_021d0(GM_CTX) {
    GM_FN(0x801021D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(7) = R(3) |R(3);
    R(0) = ld32(base, (R(13) + -21588));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80102210; }
    R(3) = divwu(R(4), R(5));
    R(6) = (0 + 0x802F0000u);
    R(4) = R(5) |R(5);
    R(5) = R(7) |R(7);
    R(6) = (R(6) + 18980);
    R(7) = (0 + 32);
    R(8) = (0 + 4);
    GM_CALLV(0x8010220Cu, 0x8016E7F0u, 0);
    st32(base, (R(13) + -21588), R(3));
L_80102210:;
    R(0) = lr;
}

/* fn_801024A0 (fn_801024A0, 216 bytes) */
static void wm_m_024a0(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(5), 1);
    R(9) = (0 + 0x80320000u);
    R(10) = R(7) |R(7);
    R(9) = (R(9) + 5112);
    if ((!CR_BIT(ctx, 2))) { goto L_8010251C; }
    R(6) = (0 + 0x80310000u);
    R(7) = (0 + 0);
    R(6) = (R(6) + 23440);
    R(0) = ld8(base, (R(6) + 12));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_801024EC; }
    R(0) = ld8(base, (R(6) + 13));
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_801024EC; }
    R(6) = ld32(base, (R(13) + -22276));
    R(0) = ld8(base, (R(6) + 896));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801024EC; }
    R(7) = (0 + 1);
L_801024EC:;
    R(6) = (R(2) + -24384);
    R(0) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(8) = ld8(base, (R(6) + R(7)));
    R(5) = (R(9) + 36);
    R(6) = ld32(base, (R(5) + R(0)));
    R(7) = R(4) |R(4);
    R(5) = (R(9) + 56);
    R(8) = (int8_t)R(8);
    R(9) = (R(10) + 1);
    R(4) = (0 + 29);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_TAIL(0x802E16E8u, 0); return;
L_8010251C:;
    cr_cmp_s(ctx, 0, (int32_t)R(5), 4);
    if ((!CR_BIT(ctx, 2))) { goto L_80102554; }
    R(7) = (R(2) + -24388);
    R(0) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(8) = ld8(base, (R(7) + R(6)));
    R(5) = (R(9) + 36);
    R(6) = ld32(base, (R(5) + R(0)));
    R(7) = R(4) |R(4);
    R(5) = (R(9) + 56);
    R(8) = (int8_t)R(8);
    R(9) = (R(10) + 1);
    R(4) = (0 + 29);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_TAIL(0x802E16E8u, 0); return;
L_80102554:;
    R(0) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(5) = (R(9) + 36);
    R(6) = ld32(base, (R(5) + R(0)));
    R(7) = R(4) |R(4);
    R(5) = (R(9) + 80);
    R(8) = (R(10) + 1);
    R(4) = (0 + 29);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_TAIL(0x802E16E8u, 0); return;
}

/* fn_80102580 (fn_80102580, 32 bytes) */
static void wm_m_02580(GM_CTX) {
    R(3) = ld32(base, (R(13) + -21644));
    R(0) = (R(3) + 1);
    st32(base, (R(13) + -21644), R(0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 20);
    if ((CR_BIT(ctx, 0))) return;
    R(0) = (0 + 0);
    st32(base, (R(13) + -21644), R(0));
}

/* setTitleReplayRandomTable__10dScStage_cFv (setTitleReplayRandomTable__10dScStage_cFv, 16 bytes) */
static void wm_setTitleReplayRandomTable__10dScStage_cF_025c0(GM_CTX) {
    R(3) = (0 + 0x80370000u);
    R(4) = (0 + 15);
    R(3) = (R(3) + 16828);
    GM_TAIL(0x800B54C0u, 0); return;
}

/* fn_801025D0 (fn_801025D0, 112 bytes) */
static void wm_m_025d0(GM_CTX) {
    GM_FN(0x801025D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24380); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + 5112);
    { uint32_t ea_ = (R(2) + -24376); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24372); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 9792);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 15728);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80102628u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21696), R(0));
    R(0) = lr;
}

/* fn_80102660 (fn_80102660, 16 bytes) */
static void wm_m_02660(GM_CTX) {
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = (R(13) + -21576);
    st32(base, (R(3) + R(0)), R(5));
}

/* fn_80102670 (fn_80102670, 28 bytes) */
static void wm_m_02670(GM_CTX) {
    R(5) = R(3) |R(3);
    R(3) = R(4) |R(4);
    R(6) = (R(5) + 1);
    R(4) = (0 + 6);
    R(5) = (R(13) + -26168);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_TAIL(0x802E16E8u, 0); return;
}

/* _Z20SetSomeConditionShitiij (_Z20SetSomeConditionShitiij, 48 bytes) */
static void wm__Z20SetSomeConditionShitiij_026d0(GM_CTX) {
    R(0) = ld8(base, (R(13) + -21553));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) return;
    R(0) = ((int32_t)R(3) * 168);
    R(3) = (0 + 0x80370000u);
    R(4) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = (R(3) + 16880);
    R(3) = R(3) + R(0);
    R(0) = ld32(base, (R(4) + R(3)));
    R(0) = R(0) |R(5);
    st32(base, (R(4) + R(3)), R(0));
}

/* fn_80102730 (fn_80102730, 32 bytes) */
static void wm_m_02730(GM_CTX) {
    R(0) = ld8(base, (R(13) + -21553));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) return;
    R(5) = (0 + 0x80370000u);
    R(0) = rotl32(R(3), 2) & 0xFFFFFFFCu;
    R(5) = (R(5) + 18560);
    st32(base, (R(5) + R(0)), R(4));
}

/* IsCourseType__9dScWMap_cFiiQ29dScWMap_c12CourseType_e (IsCourseType__9dScWMap_cFiiQ29dScWMap_c12CourseType_e, 60 bytes) */
static void wm_IsCourseType__9dScWMap_cFiiQ29dScWMap_c1_02750(GM_CTX) {
    cr_cmp_u(ctx, 0, R(4), 0x29u);
    if ((CR_BIT(ctx, 1))) { goto L_80102784; }
    R(0) = ((int32_t)R(3) * 168);
    R(6) = (0 + 0x80370000u);
    R(3) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(6) = (R(6) + 16880);
    R(0) = R(6) + R(0);
    R(0) = ld32(base, (R(3) + R(0)));
    R(3) = R(5) &R(0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(3) = rotl32(R(0), 1) & 0x1u;
    return;
L_80102784:;
    R(3) = (0 + 0);
}

/* fn_80102790 (fn_80102790, 48 bytes) */
static void wm_m_02790(GM_CTX) {
    R(3) = ld8(base, (R(13) + -21542));
    R(4) = (0 + 0);
    R(0) = ld8(base, (R(13) + -21540));
    R(5) = (0 + 255);
    st8(base, (R(13) + -26171), R(5));
    st8(base, (R(13) + -26170), R(4));
    st8(base, (R(13) + -21544), R(4));
    st8(base, (R(13) + -21541), R(3));
    st8(base, (R(13) + -21539), R(0));
    st8(base, (R(13) + -21542), R(4));
    st8(base, (R(13) + -21540), R(4));
}

/* fn_80102C10 (fn_80102C10, 112 bytes) */
static void wm_m_02c10(GM_CTX) {
    GM_FN(0x80102C10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24368); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + 5216);
    { uint32_t ea_ = (R(2) + -24364); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24360); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 11392);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 16864);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80102C68u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21584), R(0));
    R(0) = lr;
}

/* fn_80102CA0 (fn_80102CA0, 268 bytes) */
static void wm_m_02ca0(GM_CTX) {
    GM_FN(0x80102CA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80102CC8; }
    R(3) = (0 + 0);
    goto L_80102D98;
L_80102CC8:;
    R(0) = ld8(base, (R(3) + 14));
    R(4) = (0 + 0);
    st8(base, (R(3) + 12), R(4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80102D94; }
    GM_CALLV(0x80102CE0u, 0x8006A1C0u, 0);
    R(0) = R(3) & 0xFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80102D14; }
    R(3) = ld32(base, (R(31) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80102CFC; }
    R(0) = (R(3) + -1);
    st32(base, (R(31) + 8), R(0));
L_80102CFC:;
    R(0) = ld32(base, (R(31) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80102D14; }
    R(3) = ld32(base, (R(31) + 4));
    R(0) = (R(3) + 1);
    st32(base, (R(31) + 4), R(0));
L_80102D14:;
    R(3) = ld32(base, (R(31) + 24));
    R(4) = ld32(base, (R(31) + 4));
    R(0) = (int16_t)ld16(base, (R(3) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80102D50; }
    { uint32_t ea_ = (R(2) + -24352); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 1);
    R(0) = (0 + 0);
    st8(base, (R(31) + 12), R(3));
    R(3) = R(31) |R(31);
    st32(base, (R(31) + 4), R(0));
    { uint32_t ea_ = (R(31) + 16); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80102D48u, 0x80102E00u, 0);
    { uint32_t ea_ = (R(31) + 20); stfs(base, ea_, ctx->f[1].d); }
    goto L_80102D74;
L_80102D50:;
    { uint32_t ea_ = (R(31) + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -24348); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 16); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80102D68u, 0x80102E00u, 0);
    { uint32_t ea_ = (R(31) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 20); stfs(base, ea_, ctx->f[0].d); }
L_80102D74:;
    GM_CALLV(0x80102D78u, 0x8006A1F0u, 0);
    R(0) = R(3) & 0xFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80102D8C; }
    R(0) = (0 + 1);
    st8(base, (R(31) + 13), R(0));
    goto L_80102D94;
L_80102D8C:;
    R(0) = (0 + 0);
    st8(base, (R(31) + 13), R(0));
L_80102D94:;
    R(3) = (0 + 1);
L_80102D98:;
    R(0) = lr;
}

/* fn_80102E00 (fn_80102E00, 116 bytes) */
static void wm_m_02e00(GM_CTX) {
    GM_FN(0x80102E00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x80102E18u, 0x8006A230u, 0);
    R(4) = ld32(base, (R(31) + 24));
    R(5) = (0 + 0x43300000u);
    R(3) = R(3) & 0xFFFFu;
    st32(base, (f + 16), R(5));
    R(0) = (int16_t)ld16(base, (R(4) + 0));
    { uint32_t ea_ = (R(2) + -24328); ctx->f[1].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    st32(base, (f + 12), R(3));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -24344); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (f + 8), R(5));
    { uint32_t ea_ = (R(2) + -24336); ctx->f[3].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[2].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    R(0) = lr;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d / ctx->f[1].d);
}

/* fn_80102E80 (fn_80102E80, 112 bytes) */
static void wm_m_02e80(GM_CTX) {
    GM_FN(0x80102E80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24320); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + 5256);
    { uint32_t ea_ = (R(2) + -24316); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24312); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 12016);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 18640);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80102ED8u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21536), R(0));
    R(0) = lr;
}

/* fn_80102F10 (fn_80102F10, 116 bytes) */
static void wm_m_02f10(GM_CTX) {
    GM_FN(0x80102F10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = (0 + 28564);
    GM_CALLV(0x80102F28u, 0x802B9210u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80102F60; }
    R(5) = (0 + 0x80320000u);
    R(4) = (0 + 0x80100000u);
    R(5) = (R(5) + 6272);
    st32(base, (R(3) + 0), R(5));
    R(5) = (0 + 0x80100000u);
    R(4) = (R(4) + 12176);
    R(5) = (R(5) + 12288);
    R(6) = (0 + 336);
    R(7) = (0 + 85);
    R(3) = (R(3) + 4);
    GM_CALLV(0x80102F60u, 0x802DC9A0u, 0);
L_80102F60:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x80102F68u, 0x80103150u, 0);
    st32(base, (R(13) + -21524), R(31));
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_80102F90 (fn_80102F90, 104 bytes) */
static void wm_m_02f90(GM_CTX) {
    GM_FN(0x80102F90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (R(3) + 36);
    R(30) = R(3) |R(3);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80102FB4u, 0x802D7AA0u, 0);
    R(3) = (0 + 0x80330000u);
    R(0) = (0 + 0);
    R(3) = (R(3) + -26280);
    st32(base, (R(31) + 0), R(3));
    R(3) = R(30) |R(30);
    st32(base, (R(31) + 276), R(0));
    st32(base, (R(31) + 280), R(0));
    st8(base, (R(31) + 284), R(0));
    st8(base, (R(31) + 285), R(0));
    st32(base, (R(31) + 288), R(0));
    st32(base, (R(31) + 292), R(0));
    R(0) = lr;
}

/* fn_80103000 (fn_80103000, 136 bytes) */
static void wm_m_03000(GM_CTX) {
    GM_FN(0x80103000); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80103068; }
    { uint32_t a_ = R(3); R(31) = a_ + 0x24u; ctx->xer_ca = R(31) < a_; }
    CR0(ctx, R(31));
    if ((CR_BIT(ctx, 2))) { goto L_80103058; }
    R(4) = (0 + 0x80330000u);
    R(3) = R(31) |R(31);
    R(4) = (R(4) + -26280);
    st32(base, (R(31) + 0), R(4));
    GM_CALLV(0x80103044u, 0x8016D4B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103058; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x80103058u, 0x802D7B20u, 0);
L_80103058:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80103068; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x80103068u, 0x802B9280u, 0);
L_80103068:;
    R(3) = R(29) |R(29);
    R(0) = lr;
}

/* fn_80103090 (fn_80103090, 72 bytes) */
static void wm_m_03090(GM_CTX) {
    GM_FN(0x80103090); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -21524));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801030C8; }
    if ((CR_BIT(ctx, 2))) { goto L_801030C0; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x801030C0u, ctx->ctr, 0);
L_801030C0:;
    R(0) = (0 + 0);
    st32(base, (R(13) + -21524), R(0));
L_801030C8:;
    R(0) = lr;
}

/* fn_801030E0 (fn_801030E0, 104 bytes) */
static void wm_m_030e0(GM_CTX) {
    GM_FN(0x801030E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8010312C; }
    R(4) = (0 + 0x80100000u);
    R(5) = (0 + 336);
    R(4) = (R(4) + 12288);
    R(6) = (0 + 85);
    R(3) = (R(3) + 4);
    GM_CALLV(0x8010311Cu, 0x802DCA98u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8010312C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8010312Cu, 0x802B9280u, 0);
L_8010312C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_80103150 (fn_80103150, 84 bytes) */
static void wm_m_03150(GM_CTX) {
    R(5) = (0 + 0x80370000u);
    R(0) = (0 + 85);
    R(4) = (R(5) + 32200);
    R(7) = (0 + 47);
    R(6) = (0 + 0);
    ctx->ctr = R(0);
L_80103168:;
    st32(base, (R(3) + 4), R(7));
    st32(base, (R(3) + 8), R(6));
    st32(base, (R(3) + 12), R(6));
    st32(base, (R(3) + 16), R(6));
    st32(base, (R(3) + 20), R(6));
    st32(base, (R(3) + 24), R(6));
    { uint32_t ea_ = (R(5) + 32200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = R(3) + 336; st8(base, ea_, R(6)); R(3) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80103168; }
}

/* fn_801031B0 (fn_801031B0, 104 bytes) */
static void wm_m_031b0(GM_CTX) {
    GM_FN(0x801031B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = (0 + 0);
    R(29) = R(3) |R(3);
    R(31) = R(29) |R(29);
L_801031D4:;
    R(0) = ld8(base, (R(31) + 336));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801031EC; }
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    GM_CALLV(0x801031ECu, 0x80103220u, 0);
L_801031EC:;
    R(30) = (R(30) + 1);
    R(31) = (R(31) + 336);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 85);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_801031D4; }
    R(0) = lr;
}

/* fn_80103220 (fn_80103220, 228 bytes) */
static void wm_m_03220(GM_CTX) {
    GM_FN(0x80103220); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ((int32_t)R(4) * 336);
    R(31) = R(3) + R(0);
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(31) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8010327C; }
    R(5) = ld32(base, (R(31) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8010327C; }
    R(3) = (f + 8);
    GM_CALLV(0x80103260u, 0x800FC4F0u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 36); stfs(base, ea_, ctx->f[0].d); }
    goto L_801032A0;
L_8010327C:;
    R(3) = ld32(base, (R(31) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801032A0; }
    { uint32_t ea_ = (R(3) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 36); stfs(base, ea_, ctx->f[0].d); }
L_801032A0:;
    R(4) = ld32(base, (R(31) + 4));
    R(3) = R(30) |R(30);
    GM_CALLV(0x801032ACu, 0x80103580u, 0);
    R(30) = R(3) |R(3);
    R(4) = (R(13) + -26128);
    R(5) = (0 + 1);
    GM_CALLV(0x801032BCu, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801032EC; }
    R(12) = ld32(base, (R(31) + 40));
    R(3) = (R(31) + 40);
    R(4) = R(30) |R(30);
    R(6) = (R(31) + 28);
    R(12) = ld32(base, (R(12) + 160));
    R(5) = (0 + 0);
    R(7) = ld32(base, (R(31) + 16));
    R(8) = ld32(base, (R(31) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x801032ECu, ctx->ctr, 0);
L_801032EC:;
    R(0) = lr;
}

/* fn_80103310 (fn_80103310, 116 bytes) */
static void wm_m_03310(GM_CTX) {
    GM_FN(0x80103310); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(8) |R(8);
    R(30) = R(7) |R(7);
    R(29) = R(4) |R(4);
    R(4) = R(5) |R(5);
    R(5) = R(6) |R(6);
    R(28) = R(3) |R(3);
    R(3) = (f + 8);
    GM_CALLV(0x8010334Cu, 0x800FC4F0u, 0);
    R(3) = R(28) |R(28);
    R(4) = R(29) |R(29);
    R(6) = R(30) |R(30);
    R(7) = R(31) |R(31);
    R(5) = (f + 8);
    GM_CALLV(0x80103364u, 0x80103390u, 0);
    R(0) = lr;
}

/* playEffect__18dWmEffectManager_cFiPC7mVec3_cPC7mAng3_cPC7mVec3_c (playEffect__18dWmEffectManager_cFiPC7mVec3_cPC7mAng3_cPC7mVec3_c, 124 bytes) */
static void wm_playEffect__18dWmEffectManager_cFiPC7mVe_03390(GM_CTX) {
    GM_FN(0x80103390); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(7) |R(7);
    R(29) = R(6) |R(6);
    R(28) = R(5) |R(5);
    GM_CALLV(0x801033BCu, 0x80103580u, 0);
    R(31) = R(3) |R(3);
    R(4) = (R(13) + -26128);
    R(5) = (0 + 1);
    GM_CALLV(0x801033CCu, 0x802E1BD0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801033EC; }
    R(3) = R(31) |R(31);
    R(5) = R(28) |R(28);
    R(6) = R(29) |R(29);
    R(7) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x801033ECu, 0x8016C890u, 0);
L_801033EC:;
    R(0) = lr;
}

/* fn_80103410 (fn_80103410, 16 bytes) */
static void wm_m_03410(GM_CTX) {
    R(9) = R(8) |R(8);
    R(8) = R(7) |R(7);
    R(7) = (0 + 0);
    GM_TAIL(0x80103440u, 0); return;
}

/* fn_80103440 (fn_80103440, 148 bytes) */
static void wm_m_03440(GM_CTX) {
    GM_FN(0x80103440); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(25) = R(3) |R(3);
    R(26) = R(4) |R(4);
    R(27) = R(5) |R(5);
    R(28) = R(6) |R(6);
    R(29) = R(7) |R(7);
    R(30) = R(8) |R(8);
    R(31) = R(9) |R(9);
    GM_CALLV(0x80103474u, 0x80103500u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_80103484; }
    R(3) = (0 + -1);
    goto L_801034BC;
L_80103484:;
    cr_cmp_s(ctx, 0, (int32_t)R(26), 47);
    if ((!CR_BIT(ctx, 2))) { goto L_80103494; }
    R(3) = (0 + -1);
    goto L_801034BC;
L_80103494:;
    R(4) = ((int32_t)R(3) * 336);
    R(0) = (0 + 1);
    R(4) = R(25) + R(4);
    st32(base, (R(4) + 4), R(26));
    st32(base, (R(4) + 8), R(27));
    st32(base, (R(4) + 12), R(28));
    st32(base, (R(4) + 16), R(30));
    st32(base, (R(4) + 20), R(31));
    st32(base, (R(4) + 24), R(29));
    st8(base, (R(4) + 336), R(0));
L_801034BC:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* endEffect__18dWmEffectManager_cFi (endEffect__18dWmEffectManager_cFi, 20 bytes) */
static void wm_endEffect__18dWmEffectManager_cFi_034e0(GM_CTX) {
    R(0) = ((int32_t)R(4) * 336);
    R(4) = (0 + 0);
    R(3) = R(3) + R(0);
    st8(base, (R(3) + 336), R(4));
}

/* fn_80103500 (fn_80103500, 128 bytes) */
static void wm_m_03500(GM_CTX) {
    R(0) = (0 + 17);
    R(4) = (0 + 0);
    ctx->ctr = R(0);
    R(0) = R(0) | 0x0u;
L_80103510:;
    R(0) = ld8(base, (R(3) + 336));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103568; }
    R(0) = ld8(base, (R(3) + 672));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103568; }
    R(0) = ld8(base, (R(3) + 1008));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103568; }
    R(0) = ld8(base, (R(3) + 1344));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103568; }
    R(0) = ld8(base, (R(3) + 1680));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103568; }
    R(3) = (R(3) + 1680);
    R(4) = (R(4) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80103510; }
L_80103568:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 85);
    if ((!CR_BIT(ctx, 2))) { goto L_80103578; }
    R(3) = (0 + -1);
    return;
L_80103578:;
    R(3) = R(4) |R(4);
}

/* fn_80103580 (fn_80103580, 424 bytes) */
static void wm_m_03580(GM_CTX) {
    cr_cmp_u(ctx, 0, R(4), 0x2Eu);
    R(5) = (0 + 0x80320000u);
    R(5) = (R(5) + 5312);
    if ((CR_BIT(ctx, 1))) { goto L_80103720; }
    R(3) = (0 + 0x80320000u);
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = (R(3) + 6084);
    R(3) = ld32(base, (R(3) + R(0)));
    ctx->ctr = R(3);
    { switch (ctx->ctr) { case 0x801035A8u: goto L_801035A8; case 0x801035B0u: goto L_801035B0; case 0x801035B8u: goto L_801035B8; case 0x801035C0u: goto L_801035C0; case 0x801035C8u: goto L_801035C8; case 0x801035D0u: goto L_801035D0; case 0x801035D8u: goto L_801035D8; case 0x801035E0u: goto L_801035E0; case 0x801035E8u: goto L_801035E8; case 0x801035F0u: goto L_801035F0; case 0x801035F8u: goto L_801035F8; case 0x80103600u: goto L_80103600; case 0x80103608u: goto L_80103608; case 0x80103610u: goto L_80103610; case 0x80103618u: goto L_80103618; case 0x80103620u: goto L_80103620; case 0x80103628u: goto L_80103628; case 0x80103630u: goto L_80103630; case 0x80103638u: goto L_80103638; case 0x80103640u: goto L_80103640; case 0x80103648u: goto L_80103648; case 0x80103650u: goto L_80103650; case 0x80103658u: goto L_80103658; case 0x80103660u: goto L_80103660; case 0x80103668u: goto L_80103668; case 0x80103670u: goto L_80103670; case 0x80103678u: goto L_80103678; case 0x80103680u: goto L_80103680; case 0x80103688u: goto L_80103688; case 0x80103690u: goto L_80103690; case 0x80103698u: goto L_80103698; case 0x801036A0u: goto L_801036A0; case 0x801036A8u: goto L_801036A8; case 0x801036B0u: goto L_801036B0; case 0x801036B8u: goto L_801036B8; case 0x801036C0u: goto L_801036C0; case 0x801036C8u: goto L_801036C8; case 0x801036D0u: goto L_801036D0; case 0x801036D8u: goto L_801036D8; case 0x801036E0u: goto L_801036E0; case 0x801036E8u: goto L_801036E8; case 0x801036F0u: goto L_801036F0; case 0x801036F8u: goto L_801036F8; case 0x80103700u: goto L_80103700; case 0x80103708u: goto L_80103708; case 0x80103710u: goto L_80103710; case 0x80103718u: goto L_80103718; default: rt_fatal("80103580: jump table target %08X", ctx->ctr); return; } }
L_801035A8:;
    R(3) = (R(5) + 36);
    return;
L_801035B0:;
    R(3) = (R(5) + 56);
    return;
L_801035B8:;
    R(3) = (R(5) + 80);
    return;
L_801035C0:;
    R(3) = (R(5) + 96);
    return;
L_801035C8:;
    R(3) = (R(5) + 116);
    return;
L_801035D0:;
    R(3) = (R(5) + 80);
    return;
L_801035D8:;
    R(3) = (R(5) + 80);
    return;
L_801035E0:;
    R(3) = (R(5) + 80);
    return;
L_801035E8:;
    R(3) = (R(5) + 136);
    return;
L_801035F0:;
    R(3) = (R(5) + 152);
    return;
L_801035F8:;
    R(3) = (R(5) + 168);
    return;
L_80103600:;
    R(3) = (R(5) + 180);
    return;
L_80103608:;
    R(3) = (R(5) + 36);
    return;
L_80103610:;
    R(3) = (R(5) + 200);
    return;
L_80103618:;
    R(3) = (R(5) + 216);
    return;
L_80103620:;
    R(3) = (R(5) + 240);
    return;
L_80103628:;
    R(3) = (R(5) + 256);
    return;
L_80103630:;
    R(3) = (R(5) + 272);
    return;
L_80103638:;
    R(3) = (R(5) + 296);
    return;
L_80103640:;
    R(3) = (R(5) + 312);
    return;
L_80103648:;
    R(3) = (R(5) + 332);
    return;
L_80103650:;
    R(3) = (R(5) + 352);
    return;
L_80103658:;
    R(3) = (R(5) + 368);
    return;
L_80103660:;
    R(3) = (R(5) + 36);
    return;
L_80103668:;
    R(3) = (R(5) + 36);
    return;
L_80103670:;
    R(3) = (R(5) + 396);
    return;
L_80103678:;
    R(3) = (R(5) + 416);
    return;
L_80103680:;
    R(3) = (R(5) + 432);
    return;
L_80103688:;
    R(3) = (R(5) + 448);
    return;
L_80103690:;
    R(3) = (R(5) + 464);
    return;
L_80103698:;
    R(3) = (R(5) + 480);
    return;
L_801036A0:;
    R(3) = (R(5) + 500);
    return;
L_801036A8:;
    R(3) = (R(5) + 520);
    return;
L_801036B0:;
    R(3) = (R(5) + 540);
    return;
L_801036B8:;
    R(3) = (R(5) + 560);
    return;
L_801036C0:;
    R(3) = (R(5) + 580);
    return;
L_801036C8:;
    R(3) = (R(5) + 600);
    return;
L_801036D0:;
    R(3) = (R(5) + 616);
    return;
L_801036D8:;
    R(3) = (R(5) + 636);
    return;
L_801036E0:;
    R(3) = (R(5) + 656);
    return;
L_801036E8:;
    R(3) = (R(5) + 676);
    return;
L_801036F0:;
    R(3) = (R(5) + 696);
    return;
L_801036F8:;
    R(3) = (R(5) + 716);
    return;
L_80103700:;
    R(3) = (R(5) + 728);
    return;
L_80103708:;
    R(3) = (R(5) + 744);
    return;
L_80103710:;
    R(3) = (R(5) + 760);
    return;
L_80103718:;
    R(3) = (R(5) + 168);
    return;
L_80103720:;
    R(3) = (R(13) + -26128);
}

/* fn_80103730 (fn_80103730, 112 bytes) */
static void wm_m_03730(GM_CTX) {
    GM_FN(0x80103730); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24304); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + 5312);
    { uint32_t ea_ = (R(2) + -24300); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24296); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 14240);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 18656);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80103788u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21528), R(0));
    R(0) = lr;
}

/* fn_801037C0 (fn_801037C0, 128 bytes) */
static void wm_m_037c0(GM_CTX) {
    GM_FN(0x801037C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld32(base, (R(3) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 1))) { goto L_801037E4; }
    R(0) = ld8(base, (R(3) + 40));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103824; }
L_801037E4:;
    R(0) = ld32(base, (R(3) + 32));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8010382C; }
    { uint32_t a_ = R(0); R(0) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    st32(base, (R(3) + 32), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8010381C; }
    R(0) = ld8(base, (R(3) + 40));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80103814; }
    R(4) = ld32(base, (R(3) + 24));
    R(0) = (R(4) + -1);
    st32(base, (R(3) + 24), R(0));
L_80103814:;
    R(0) = ld32(base, (R(3) + 36));
    st32(base, (R(3) + 32), R(0));
L_8010381C:;
    GM_CALLV(0x80103820u, 0x80103840u, 0);
    goto L_8010382C;
L_80103824:;
    R(3) = (0 + 1);
    goto L_80103830;
L_8010382C:;
    R(3) = (0 + 0);
L_80103830:;
    R(0) = lr;
}

/* fn_80103840 (fn_80103840, 172 bytes) */
static void wm_m_03840(GM_CTX) {
    GM_FN(0x80103840); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x10000u);
    R(0) = (R(4) + -1);
    R(31) = R(3) |R(3);
    R(6) = (int16_t)ld16(base, (R(3) + 28));
    R(5) = (int16_t)ld16(base, (R(3) + 4));
    { uint32_t ea_ = (R(3) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = R(6) + R(5);
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[0].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(4), (int32_t)R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_8010387C; }
    R(4) = (0 + 0);
L_8010387C:;
    { uint32_t ea_ = (R(3) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(3) + 52); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24288); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[1].d);
    st16(base, (R(3) + 4), R(4));
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[1].d); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    st8(base, (R(3) + 20), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_801038B4; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    R(0) = (0 + 1);
    st8(base, (R(3) + 20), R(0));
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[0].d); }
L_801038B4:;
    { uint32_t ea_ = (R(3) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24284); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    GM_CALLV(0x801038C4u, 0x80237BD0u, 0);
    { uint32_t ea_ = (R(31) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(31) + 12); stfs(base, ea_, ctx->f[1].d); }
    R(0) = lr;
}

/* fn_801038F0 (fn_801038F0, 276 bytes) */
static void wm_m_038f0(GM_CTX) {
    GM_FRAME(32); gptr f = gm_frame_sp;
    R(0) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    st8(base, (R(3) + 40), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80103918; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    if ((CR_BIT(ctx, 2))) { goto L_80103924; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 2);
    if ((CR_BIT(ctx, 2))) { goto L_80103934; }
    goto L_80103938;
L_80103918:;
    R(0) = (0 + 1);
    st8(base, (R(3) + 40), R(0));
    goto L_80103938;
L_80103924:;
    R(4) = ld32(base, (R(3) + 60));
    R(0) = (int16_t)ld16(base, (R(4) + 6));
    st32(base, (R(3) + 24), R(0));
    goto L_80103938;
L_80103934:;
    st32(base, (R(3) + 24), R(5));
L_80103938:;
    { uint32_t ea_ = (R(2) + -24280); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 2))) { goto L_8010396C; }
    R(4) = ld32(base, (R(3) + 60));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 8), R(0));
    R(0) = (int16_t)ld16(base, (R(4) + 4));
    { uint32_t ea_ = (R(2) + -24272); ctx->f[2].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    { uint32_t ea_ = (f + 8); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[2].d);
    goto L_80103970;
L_8010396C:;
    ctx->f[2].u = ctx->f[1].u;
L_80103970:;
    { uint32_t ea_ = (R(2) + -24280); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[2].d); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 2))) { goto L_801039A4; }
    R(4) = ld32(base, (R(3) + 60));
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 16), R(0));
    R(0) = (int16_t)ld16(base, (R(4) + 4));
    { uint32_t ea_ = (R(2) + -24272); ctx->f[1].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[1].d);
L_801039A4:;
    ctx->f[1].u = fctiw_bits(ctx->f[1].d, 1);
    { uint32_t ea_ = (R(2) + -24280); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0x10000u);
    R(0) = (0 + 0);
    { uint32_t ea_ = (f + 24); st64(base, ea_, ctx->f[1].u); }
    R(4) = (R(4) + -1);
    R(6) = ld32(base, (f + 28));
    { uint32_t ea_ = (R(2) + -24288); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = divw((int32_t)R(4), (int32_t)R(6));
    { uint32_t ea_ = (R(3) + 48); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st32(base, (R(3) + 32), R(6));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d / ctx->f[1].d);
    R(4) = ld32(base, (R(3) + 60));
    st32(base, (R(3) + 36), R(6));
    st16(base, (R(3) + 28), R(5));
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[1].d); }
    st16(base, (R(3) + 4), R(0));
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_80103A10 (fn_80103A10, 8 bytes) */
static void wm_m_03a10(GM_CTX) {
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[1].d); }
}

/* fn_80103A20 (fn_80103A20, 8 bytes) */
static void wm_m_03a20(GM_CTX) {
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[1].d); }
}

/* fn_80103A30 (fn_80103A30, 112 bytes) */
static void wm_m_03a30(GM_CTX) {
    GM_FN(0x80103A30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24264); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + 6288);
    { uint32_t ea_ = (R(2) + -24260); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24256); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 15008);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 18672);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80103A88u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21520), R(0));
    R(0) = lr;
}

/* fn_80103AC0 (fn_80103AC0, 60 bytes) */
static void wm_m_03ac0(GM_CTX) {
    GM_FN(0x80103AC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80320000u);
    R(4) = (R(4) + 6328);
    R(31) = R(3) |R(3);
    st32(base, (R(3) + 0), R(4));
    GM_CALLV(0x80103AE4u, 0x80103E20u, 0);
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_80103B00 (fn_80103B00, 64 bytes) */
static void wm_m_03b00(GM_CTX) {
    GM_FN(0x80103B00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80103B28; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80103B28; }
    GM_CALLV(0x80103B28u, 0x802B9280u, 0);
L_80103B28:;
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_80103D40 (fn_80103D40, 76 bytes) */
static void wm_m_03d40(GM_CTX) {
    R(0) = ld32(base, (R(4) + 0));
    st32(base, (R(3) + 4), R(0));
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(4) + 16));
    st32(base, (R(3) + 20), R(0));
    { uint32_t ea_ = (R(4) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_80103E20 (fn_80103E20, 24 bytes) */
static void wm_m_03e20(GM_CTX) {
    { uint32_t ea_ = (R(2) + -24248); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24228); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_80103F10 (fn_80103F10, 316 bytes) */
static void wm_m_03f10(GM_CTX) {
    GM_FN(0x80103F10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0);
    R(30) = (0 + 0);
L_80103F2C:;
    R(0) = ld32(base, (R(13) + -21508));
    R(3) = R(0) + R(31);
    R(3) = ld32(base, (R(3) + 16));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103F58; }
    if ((CR_BIT(ctx, 2))) { goto L_80103F58; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x80103F58u, ctx->ctr, 0);
L_80103F58:;
    R(30) = (R(30) + 1);
    R(31) = (R(31) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80103F2C; }
    R(3) = ld32(base, (R(13) + -21508));
    R(3) = ld32(base, (R(3) + 32));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103F90; }
    if ((CR_BIT(ctx, 2))) { goto L_80103F90; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x80103F90u, ctx->ctr, 0);
L_80103F90:;
    R(3) = ld32(base, (R(13) + -21508));
    R(3) = ld32(base, (R(3) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103FB8; }
    if ((CR_BIT(ctx, 2))) { goto L_80103FB8; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x80103FB8u, ctx->ctr, 0);
L_80103FB8:;
    R(3) = ld32(base, (R(13) + -21508));
    R(3) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80103FE0; }
    if ((CR_BIT(ctx, 2))) { goto L_80103FE0; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x80103FE0u, ctx->ctr, 0);
L_80103FE0:;
    R(3) = ld32(base, (R(13) + -21508));
    R(3) = ld32(base, (R(3) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80104008; }
    if ((CR_BIT(ctx, 2))) { goto L_80104008; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x80104008u, ctx->ctr, 0);
L_80104008:;
    R(3) = ld32(base, (R(13) + -21508));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80104034; }
    if ((CR_BIT(ctx, 2))) { goto L_8010402C; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x8010402Cu, ctx->ctr, 0);
L_8010402C:;
    R(0) = (0 + 0);
    st32(base, (R(13) + -21508), R(0));
L_80104034:;
    R(0) = lr;
}

/* playSound__14dWmSeManager_cFiRC7mVec3_ci (playSound__14dWmSeManager_cFiRC7mVec3_ci, 292 bytes) */
static void wm_playSound__14dWmSeManager_cFiRC7mVec3_ci_05240(GM_CTX) {
    GM_FN(0x80105240); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(27) = R(3) |R(3);
    R(28) = R(4) |R(4);
    R(29) = R(5) |R(5);
    R(30) = R(6) |R(6);
    GM_CALLV(0x80105268u, 0x801056C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8010534C; }
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x80105280u, 0x80105A20u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((CR_BIT(ctx, 2))) { goto L_801052AC; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 2))) { goto L_801052DC; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 4);
    if ((CR_BIT(ctx, 2))) { goto L_801052FC; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 5);
    if ((CR_BIT(ctx, 2))) { goto L_8010532C; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 6);
    if ((CR_BIT(ctx, 2))) { goto L_80105340; }
    goto L_8010534C;
L_801052AC:;
    R(4) = R(29) |R(29);
    R(3) = (f + 16);
    GM_CALLV(0x801052B8u, 0x8006A5E0u, 0);
    R(3) = ld32(base, (R(27) + 12));
    R(4) = R(31) |R(31);
    R(6) = R(30) |R(30);
    R(5) = (f + 16);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 32));
    ctx->ctr = R(12);
    GM_CALLV(0x801052D8u, ctx->ctr, 0);
    goto L_8010534C;
L_801052DC:;
    R(3) = ld32(base, (R(27) + 4));
    R(4) = R(31) |R(31);
    R(5) = R(30) |R(30);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 36));
    ctx->ctr = R(12);
    GM_CALLV(0x801052F8u, ctx->ctr, 0);
    goto L_8010534C;
L_801052FC:;
    R(4) = R(29) |R(29);
    R(3) = (f + 8);
    GM_CALLV(0x80105308u, 0x8006A5E0u, 0);
    R(3) = ld32(base, (R(27) + 8));
    R(4) = R(31) |R(31);
    R(6) = R(30) |R(30);
    R(5) = (f + 8);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 32));
    ctx->ctr = R(12);
    GM_CALLV(0x80105328u, ctx->ctr, 0);
    goto L_8010534C;
L_8010532C:;
    R(3) = ld32(base, (R(13) + -20984));
    R(4) = R(31) |R(31);
    R(5) = R(30) |R(30);
    GM_CALLV(0x8010533Cu, 0x80195370u, 0);
    goto L_8010534C;
L_80105340:;
    R(3) = ld32(base, (R(13) + -20984));
    R(4) = R(31) |R(31);
    GM_CALLV(0x8010534Cu, 0x801954A0u, 0);
L_8010534C:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_80105370 (fn_80105370, 160 bytes) */
static void wm_m_05370(GM_CTX) {
    GM_FN(0x80105370); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    GM_CALLV(0x80105394u, 0x801056C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_801053F4; }
    R(3) = R(29) |R(29);
    R(4) = R(30) |R(30);
    GM_CALLV(0x801053ACu, 0x80105A20u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((CR_BIT(ctx, 2))) { goto L_801053C8; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 2))) { goto L_801053D8; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 4);
    if ((CR_BIT(ctx, 2))) { goto L_801053E8; }
    goto L_801053F4;
L_801053C8:;
    R(3) = ld32(base, (R(29) + 12));
    R(4) = R(31) |R(31);
    GM_CALLV(0x801053D4u, 0x80199810u, 0);
    goto L_801053F4;
L_801053D8:;
    R(3) = ld32(base, (R(29) + 4));
    R(4) = R(31) |R(31);
    GM_CALLV(0x801053E4u, 0x80197E30u, 0);
    goto L_801053F4;
L_801053E8:;
    R(3) = ld32(base, (R(29) + 8));
    R(4) = R(31) |R(31);
    GM_CALLV(0x801053F4u, 0x80198AE0u, 0);
L_801053F4:;
    R(0) = lr;
}

/* playSound__14dWmSeManager_cFiiRC7mVec3_cii (playSound__14dWmSeManager_cFiiRC7mVec3_cii, 56 bytes) */
static void wm_playSound__14dWmSeManager_cFiiRC7mVec3_c_05440(GM_CTX) {
    GM_FN(0x80105440); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(9) = R(7) |R(7);
    R(7) = (0 + 0);
    R(10) = (f + 8);
    st32(base, (f + 8), R(8));
    R(8) = R(6) |R(6);
    R(6) = (0 + 0);
    GM_CALLV(0x80105468u, 0x80105480u, 0);
    R(0) = lr;
}

/* fn_80105480 (fn_80105480, 176 bytes) */
static void wm_m_05480(GM_CTX) {
    GM_FN(0x80105480); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(24) = R(3) |R(3);
    R(25) = R(4) |R(4);
    R(26) = R(5) |R(5);
    R(27) = R(6) |R(6);
    R(28) = R(7) |R(7);
    R(29) = R(8) |R(8);
    R(30) = R(9) |R(9);
    R(31) = R(10) |R(10);
    GM_CALLV(0x801054B8u, 0x801055F0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_801054C8; }
    R(3) = (0 + -1);
    goto L_80105518;
L_801054C8:;
    cr_cmp_s(ctx, 0, (int32_t)R(25), 121);
    if ((!CR_BIT(ctx, 2))) { goto L_801054D8; }
    R(3) = (0 + -1);
    goto L_80105518;
L_801054D8:;
    R(0) = ((int32_t)R(3) * 52);
    R(6) = ld32(base, (R(31) + 0));
    R(5) = (0 + 4);
    R(4) = (0 + 7);
    R(7) = R(24) + R(0);
    st32(base, (R(7) + 36), R(25));
    R(0) = (0 + 1);
    st32(base, (R(7) + 40), R(27));
    st32(base, (R(7) + 44), R(28));
    st32(base, (R(7) + 48), R(29));
    st32(base, (R(7) + 64), R(26));
    st32(base, (R(7) + 68), R(6));
    st32(base, (R(7) + 72), R(5));
    st32(base, (R(7) + 76), R(4));
    st8(base, (R(7) + 80), R(0));
    st32(base, (R(7) + 84), R(30));
L_80105518:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_801055F0 (fn_801055F0, 208 bytes) */
static void wm_m_055f0(GM_CTX) {
    R(0) = (0 + 3);
    R(4) = (0 + 0);
    ctx->ctr = R(0);
    R(0) = R(0) | 0x0u;
L_80105600:;
    R(0) = ld8(base, (R(3) + 80));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(0) = ld8(base, (R(3) + 132));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(0) = ld8(base, (R(3) + 184));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(0) = ld8(base, (R(3) + 236));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(0) = ld8(base, (R(3) + 288));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(0) = ld8(base, (R(3) + 340));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(0) = ld8(base, (R(3) + 392));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(0) = ld8(base, (R(3) + 444));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(0) = ld8(base, (R(3) + 496));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(0) = ld8(base, (R(3) + 548));
    R(4) = (R(4) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_801056A8; }
    R(3) = (R(3) + 520);
    R(4) = (R(4) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80105600; }
L_801056A8:;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 30);
    if ((!CR_BIT(ctx, 2))) { goto L_801056B8; }
    R(3) = (0 + -1);
    return;
L_801056B8:;
    R(3) = R(4) |R(4);
}

/* fn_80105EE0 (fn_80105EE0, 68 bytes) */
static void wm_m_05ee0(GM_CTX) {
    GM_FN(0x80105EE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x80105EF0u, 0x801056C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(4) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80105F10; }
    R(3) = ld32(base, (R(13) + -20984));
    GM_CALLV(0x80105F04u, 0x80196600u, 0);
    R(0) = cntlzw(R(3));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
    goto L_80105F14;
L_80105F10:;
    R(3) = (0 + 0);
L_80105F14:;
    R(0) = lr;
}

/* fn_80105F40 (fn_80105F40, 112 bytes) */
static void wm_m_05f40(GM_CTX) {
    GM_FN(0x80105F40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24200); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + 6344);
    { uint32_t ea_ = (R(2) + -24196); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24192); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 24496);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 18688);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80105F98u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21512), R(0));
    R(0) = lr;
}

/* fn_80105FD0 (fn_80105FD0, 444 bytes) */
static void wm_m_05fd0(GM_CTX) {
    GM_FN(0x80105FD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(0) = (0 + 0);
    st32(base, (R(3) + 0), R(0));
    R(26) = R(3) |R(3);
    R(27) = R(5) |R(5);
    st32(base, (R(3) + 4), R(0));
    st32(base, (R(3) + 8), R(4));
    st32(base, (R(3) + 12), R(5));
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[1].d); }
    if ((CR_BIT(ctx, 2))) { goto L_80106168; }
    R(23) = (R(4) + 1);
    R(3) = ((int32_t)R(23) * 20);
    R(3) = (R(3) + 16);
    GM_CALLV(0x80106024u, 0x802B9250u, 0);
    R(5) = (0 + 0x80100000u);
    R(7) = R(23) |R(23);
    R(5) = (R(5) + 24976);
    R(4) = (0 + 0);
    R(6) = (0 + 20);
    GM_CALLV(0x8010603Cu, 0x802DC7E0u, 0);
    R(4) = ld32(base, (R(26) + 8));
    st32(base, (R(26) + 0), R(3));
    R(23) = (R(4) + 2);
    R(3) = ((int32_t)R(23) * 12);
    R(3) = (R(3) + 16);
    GM_CALLV(0x80106054u, 0x802B9250u, 0);
    R(4) = (0 + 0x80010000u);
    R(5) = (0 + 0x80010000u);
    R(7) = R(23) |R(23);
    R(6) = (0 + 12);
    R(4) = (R(4) + 24112);
    R(5) = (R(5) + -1040);
    GM_CALLV(0x80106070u, 0x802DC7E0u, 0);
    R(4) = (0 + 0x80370000u);
    st32(base, (R(26) + 4), R(3));
    R(3) = (R(4) + 32200);
    R(7) = (0 + 0);
    R(6) = (0 + 0);
    goto L_801060B0;
L_80106088:;
    R(0) = ld32(base, (R(26) + 4));
    R(7) = (R(7) + 1);
    { uint32_t ea_ = (R(4) + 32200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + R(0)); stfs(base, ea_, ctx->f[0].d); }
    R(5) = R(0) + R(6);
    R(6) = (R(6) + 12);
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 8); stfs(base, ea_, ctx->f[0].d); }
L_801060B0:;
    R(5) = ld32(base, (R(26) + 8));
    R(0) = (R(5) + 2);
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80106088; }
    { uint32_t a_ = R(5); R(0) = a_ + 0x1u; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    R(28) = (0 + 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80106168; }
    R(3) = ((int32_t)R(27) * 12);
    { uint32_t ea_ = (R(2) + -24184); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(30) = rotl32(R(27), 2) & 0xFFFFFFFCu;
    R(31) = (0 + 0);
    R(29) = (R(3) + 16);
    R(23) = (0 + 0x80010000u);
    R(24) = (0 + 0x80010000u);
    R(25) = (0 + 0);
    goto L_80106158;
L_801060F0:;
    R(0) = ld32(base, (R(26) + 0));
    R(5) = (R(28) + 1);
    R(3) = R(30) |R(30);
    R(4) = R(0) + R(31);
    st32(base, (R(4) + 4), R(5));
    GM_CALLV(0x80106108u, 0x802B9250u, 0);
    R(0) = ld32(base, (R(26) + 0));
    R(4) = R(0) + R(31);
    st32(base, (R(4) + 8), R(3));
    R(3) = R(29) |R(29);
    R(0) = ld32(base, (R(26) + 0));
    R(4) = R(0) + R(31);
    { uint32_t ea_ = (R(4) + 12); stfs(base, ea_, ctx->f[31].d); }
    GM_CALLV(0x80106128u, 0x802B9250u, 0);
    R(7) = R(27) |R(27);
    R(4) = (R(23) + 24112);
    R(5) = (R(24) + -1040);
    R(6) = (0 + 12);
    GM_CALLV(0x8010613Cu, 0x802DC7E0u, 0);
    R(0) = ld32(base, (R(26) + 0));
    R(28) = (R(28) + 1);
    R(4) = R(0) + R(31);
    st32(base, (R(4) + 16), R(3));
    R(3) = ld32(base, (R(26) + 0));
    st32(base, (R(3) + R(31)), R(25));
    R(31) = (R(31) + 20);
L_80106158:;
    R(3) = ld32(base, (R(26) + 8));
    R(0) = (R(3) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(28), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_801060F0; }
L_80106168:;
    R(3) = R(26) |R(26);
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_80106190 (fn_80106190, 104 bytes) */
static void wm_m_06190(GM_CTX) {
    GM_FN(0x80106190); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_801061DC; }
    R(3) = ld32(base, (R(3) + 8));
    GM_CALLV(0x801061BCu, 0x802B9290u, 0);
    R(4) = (0 + 0x80010000u);
    R(3) = ld32(base, (R(30) + 16));
    R(4) = (R(4) + -1040);
    GM_CALLV(0x801061CCu, 0x802DCB10u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_801061DC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x801061DCu, 0x802B9280u, 0);
L_801061DC:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_80106200 (fn_80106200, 128 bytes) */
static void wm_m_06200(GM_CTX) {
    GM_FN(0x80106200); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80106264; }
    R(3) = ld32(base, (R(3) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8010623C; }
    R(4) = (0 + 0x80010000u);
    R(4) = (R(4) + -1040);
    GM_CALLV(0x8010623Cu, 0x802DCB10u, 0);
L_8010623C:;
    R(3) = ld32(base, (R(30) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80106254; }
    R(4) = (0 + 0x80100000u);
    R(4) = (R(4) + 24976);
    GM_CALLV(0x80106254u, 0x802DCB10u, 0);
L_80106254:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80106264; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80106264u, 0x802B9280u, 0);
L_80106264:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_80106280 (fn_80106280, 40 bytes) */
static void wm_m_06280(GM_CTX) {
    R(0) = (R(4) + 1);
    R(3) = ld32(base, (R(3) + 4));
    R(0) = ((int32_t)R(0) * 12);
    { uint32_t ea_ = (R(5) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = R(3) + R(0); stfs(base, ea_, ctx->f[2].d); R(3) = ea_; }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_801062B0 (fn_801062B0, 880 bytes) */
static void wm_m_062b0(GM_CTX) {
    GM_FN(0x801062B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 128);
    R(5) = ld32(base, (R(3) + 4));
    R(4) = (0 + 0x80370000u);
    { uint32_t ea_ = (R(4) + 32200); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(20) = R(3) |R(3);
    { uint32_t ea_ = (R(5) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_80106324; }
    R(3) = (R(4) + 32200);
    { uint32_t ea_ = (R(5) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_80106324; }
    { uint32_t ea_ = (R(5) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_80106324; }
    R(0) = (0 + 1);
L_80106324:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80106334; }
    R(3) = R(20) |R(20);
    GM_CALLV(0x80106334u, 0x801068B0u, 0);
L_80106334:;
    R(0) = ld32(base, (R(20) + 8));
    R(22) = (0 + 1);
    { uint32_t ea_ = (R(2) + -24180); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 1))) { goto L_801063BC; }
    R(21) = (0 + 12);
    goto L_801063B0;
L_80106350:;
    R(0) = (R(22) + 1);
    R(4) = ld32(base, (R(20) + 4));
    R(0) = ((int32_t)R(0) * 12);
    R(3) = (f + 44);
    R(5) = R(4) + R(21);
    { uint32_t ea_ = (R(5) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = R(4) + R(0);
    { uint32_t ea_ = (R(5) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[4].d - ctx->f[0].d);
    { uint32_t ea_ = (R(4) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[4].d); }
    GM_CALLV(0x8010639Cu, 0x801C14C0u, 0);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 1))) { goto L_801063A8; }
    ctx->f[29].u = ctx->f[1].u;
L_801063A8:;
    R(21) = (R(21) + 12);
    R(22) = (R(22) + 1);
L_801063B0:;
    R(0) = ld32(base, (R(20) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(22), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80106350; }
L_801063BC:;
    R(0) = ld32(base, (R(20) + 8));
    R(23) = (0 + 1);
    { uint32_t ea_ = (R(2) + -24184); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    { uint32_t ea_ = (R(20) + 20); stfs(base, ea_, ctx->f[30].d); }
    if ((!CR_BIT(ctx, 1))) { goto L_801065F0; }
    { uint32_t ea_ = (R(2) + -24176); ctx->f[31].u = ld64(base, ea_); }
    R(28) = (0 + 12);
    R(27) = (0 + 20);
    R(30) = (0 + 0x43300000u);
    R(29) = (0 + 0);
    goto L_801065E4;
L_801063EC:;
    R(0) = (R(23) + 1);
    R(4) = ld32(base, (R(20) + 4));
    R(0) = ((int32_t)R(0) * 12);
    R(3) = ld32(base, (R(20) + 12));
    R(5) = R(4) + R(28);
    R(22) = (R(3) + -1);
    { uint32_t ea_ = (R(5) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = R(4) + R(0);
    { uint32_t ea_ = (R(4) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 32);
    { uint32_t ea_ = (R(4) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(5) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[4].d); }
    GM_CALLV(0x80106440u, 0x801C14C0u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d / ctx->f[29].d);
    R(3) = R(22) ^ 0x80000000u;
    st32(base, (f + 60), R(3));
    R(21) = (0 + 0);
    R(0) = ld32(base, (R(20) + 0));
    st32(base, (f + 56), R(30));
    { uint32_t ea_ = (f + 56); ctx->f[1].u = ld64(base, ea_); }
    R(3) = R(0) + R(27);
    { uint32_t ea_ = (R(3) + -8); stfs(base, ea_, ctx->f[30].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[31].d);
    R(0) = ld32(base, (R(20) + 0));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    R(3) = R(0) + R(27);
    st32(base, (R(3) + -20), R(29));
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 64); st64(base, ea_, ctx->f[0].u); }
    R(22) = ld32(base, (f + 68));
    cr_cmp_s(ctx, 0, (int32_t)R(22), 0);
    if ((CR_BIT(ctx, 0))) { goto L_801065C0; }
    R(0) = (R(23) + -1);
    R(31) = R(22) ^ 0x80000000u;
    R(24) = ((int32_t)R(0) * 20);
    R(26) = (0 + 0);
    R(25) = (0 + 0);
    goto L_801065B8;
L_801064A4:;
    R(0) = R(21) ^ 0x80000000u;
    st32(base, (f + 68), R(0));
    R(0) = ld32(base, (R(20) + 0));
    R(4) = R(20) |R(20);
    st32(base, (f + 64), R(30));
    R(3) = (f + 20);
    R(5) = R(0) + R(24);
    { uint32_t ea_ = (f + 64); ctx->f[0].u = ld64(base, ea_); }
    st32(base, (f + 60), R(31));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[31].d);
    st32(base, (f + 56), R(30));
    { uint32_t ea_ = (f + 56); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[31].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[0].d);
    GM_CALLV(0x801064E0u, 0x80106620u, 0);
    R(0) = ld32(base, (R(20) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(21), 0);
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(27) + R(0);
    R(0) = ld32(base, (R(3) + -4));
    { uint32_t ea_ = (R(26) + R(0)); stfs(base, ea_, ctx->f[0].d); }
    R(3) = R(0) + R(26);
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 1))) { goto L_80106598; }
    R(4) = ld32(base, (R(20) + 0));
    R(0) = (R(21) + -1);
    R(0) = ((int32_t)R(0) * 12);
    R(3) = (f + 8);
    R(4) = R(27) + R(4);
    R(4) = ld32(base, (R(4) + -4));
    R(5) = R(4) + R(0);
    R(4) = R(4) + R(26);
    { uint32_t ea_ = (R(4) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(5) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    GM_CALLV(0x80106564u, 0x801C14C0u, 0);
    R(0) = ld32(base, (R(20) + 0));
    R(3) = R(27) + R(0);
    R(0) = ld32(base, (R(3) + -12));
    R(3) = R(0) + R(25);
    { uint32_t ea_ = (R(3) + -4); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld32(base, (R(20) + 0));
    R(4) = R(27) + R(0);
    R(0) = ld32(base, (R(4) + -12));
    { uint32_t ea_ = (R(4) + -8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(0) + R(25);
    { uint32_t ea_ = (R(3) + -4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(4) + -8); stfs(base, ea_, ctx->f[0].d); }
L_80106598:;
    R(0) = ld32(base, (R(20) + 0));
    R(26) = (R(26) + 12);
    R(25) = (R(25) + 4);
    R(21) = (R(21) + 1);
    R(4) = R(27) + R(0);
    R(3) = ld32(base, (R(4) + -20));
    R(0) = (R(3) + 1);
    st32(base, (R(4) + -20), R(0));
L_801065B8:;
    cr_cmp_s(ctx, 0, (int32_t)R(21), (int32_t)R(22));
    if ((!CR_BIT(ctx, 1))) { GM_LOOP(); goto L_801064A4; }
L_801065C0:;
    R(0) = ld32(base, (R(20) + 0));
    R(28) = (R(28) + 12);
    { uint32_t ea_ = (R(20) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(23) = (R(23) + 1);
    R(3) = R(0) + R(27);
    R(27) = (R(27) + 20);
    { uint32_t ea_ = (R(3) + -8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(20) + 20); stfs(base, ea_, ctx->f[0].d); }
L_801065E4:;
    R(0) = ld32(base, (R(20) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(23), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_801063EC; }
L_801065F0:;
    R(11) = (f + 128);
    R(0) = lr;
}

/* fn_80106620 (fn_80106620, 648 bytes) */
static void wm_m_06620(GM_CTX) {
    GM_FN(0x80106620); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = ld32(base, (R(5) + 4));
    R(5) = (R(6) + -1);
    R(0) = (R(6) + 2);
    R(5) = ((int32_t)R(5) * 12);
    { uint32_t ea_ = (R(2) + -24168); ctx->f[2].u = ld64(base, ea_); }
    R(0) = ((int32_t)R(0) * 12);
    ctx->f[30].u = ctx->f[1].u;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(3) = (R(6) + 1);
    R(7) = ld32(base, (R(4) + 4));
    R(3) = ((int32_t)R(3) * 12);
    { uint32_t ea_ = R(5) + R(7); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); R(5) = ea_; }
    { uint32_t ea_ = R(3) + R(7); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); R(3) = ea_; }
    R(4) = ((int32_t)R(6) * 12);
    { uint32_t ea_ = R(4) + R(7); ctx->f[10].d = ctx->ps1[10] = ldfs(base, ea_); R(4) = ea_; }
    { uint32_t ea_ = (R(5) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(3) = R(7) + R(0);
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[9].d = ctx->ps1[9] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(7) + R(0)); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 124); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80106708u, 0x802E861Cu, 0);
    ctx->f[31].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -24160); ctx->f[2].u = ld64(base, ea_); }
    ctx->f[1].u = ctx->f[30].u;
    GM_CALLV(0x80106718u, 0x802E861Cu, 0);
    ctx->f[13].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -24152); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 16); ctx->f[12].d = ctx->ps1[12] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -24144); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[5].d * ctx->f[31].d);
    ctx->f[6].u = ctx->f[13].u ^ 0x8000000000000000ull;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[5].d * ctx->f[12].d);
    { uint32_t ea_ = (R(2) + -24148); ctx->f[10].d = ctx->ps1[10] = ldfs(base, ea_); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[5].d - ctx->f[12].d);
    { uint32_t ea_ = (f + 88); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[6].d + ctx->f[3].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[12].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 84); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[8].d - ctx->f[30].d);
    { uint32_t ea_ = (f + 80); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[7].d * ctx->f[13].d);
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[1].d * ctx->f[31].d);
    ctx->f[25].d = ctx->ps1[25] = frsp(ctx->f[12].d * ctx->f[9].d);
    { uint32_t ea_ = (f + 100); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[12].d - ctx->f[5].d);
    { uint32_t ea_ = (f + 96); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[11].d = ctx->ps1[11] = frsp(ctx->f[8].d + ctx->f[7].d);
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[13].d - ctx->f[31].d);
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[0].d * ctx->f[31].d);
    { uint32_t ea_ = (f + 92); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[26].d = ctx->ps1[26] = frsp(ctx->f[10].d + ctx->f[11].d);
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[5].d * ctx->f[13].d);
    { uint32_t ea_ = (f + 112); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[10].d = ctx->ps1[10] = frsp(ctx->f[4].d * ctx->f[25].d);
    ctx->f[11].d = ctx->ps1[11] = frsp(ctx->f[3].d * ctx->f[25].d);
    { uint32_t ea_ = (f + 108); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[1].d * ctx->f[26].d);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[6].d * ctx->f[25].d);
    { uint32_t ea_ = (f + 120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[0].d * ctx->f[26].d);
    ctx->f[13].d = ctx->ps1[13] = frsp(ctx->f[2].d * ctx->f[26].d);
    { uint32_t ea_ = (f + 124); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[25].d = ctx->ps1[25] = frsp(ctx->f[12].d * ctx->f[7].d);
    ctx->f[27].d = ctx->ps1[27] = frsp(ctx->f[6].d + ctx->f[29].d);
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[6].d); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[10].d + ctx->f[13].d);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[1].d * ctx->f[25].d);
    { uint32_t ea_ = (f + 116); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[26].d = ctx->ps1[26] = frsp(ctx->f[2].d * ctx->f[25].d);
    ctx->f[25].d = ctx->ps1[25] = frsp(ctx->f[0].d * ctx->f[25].d);
    { uint32_t ea_ = (f + 104); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[28].d = ctx->ps1[28] = frsp(ctx->f[11].d + ctx->f[31].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[12].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[7].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[9].d + ctx->f[8].d);
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[11].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[29].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[4].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[5].d * ctx->f[2].d);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[31].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[2].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[28].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[13].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[7].d + ctx->f[0].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[27].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[27].d); }
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[4].d + ctx->f[6].d);
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[3].d + ctx->f[26].d);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[28].d); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[5].d + ctx->f[25].d);
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[25].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[26].d); }
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[8].d); }
    R(0) = lr;
}

/* fn_801068B0 (fn_801068B0, 608 bytes) */
static void wm_m_068b0(GM_CTX) {
    GM_FN(0x801068B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = ld32(base, (R(3) + 4));
    R(30) = R(3) |R(3);
    { uint32_t ea_ = (R(2) + -24152); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(4) = (f + 92);
    { uint32_t ea_ = (R(5) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 16); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(5) + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[2].d + ctx->f[1].d);
    { uint32_t ea_ = (R(5) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[6].d - ctx->f[0].d);
    { uint32_t ea_ = (R(5) + 20); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[5].d - ctx->f[1].d);
    { uint32_t ea_ = (R(5) + 32); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(2) + -24140); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 0); stfs(base, ea_, ctx->f[8].d); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (R(5) + 4); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (R(5) + 8); stfs(base, ea_, ctx->f[6].d); }
    R(5) = ld32(base, (R(3) + 8));
    R(7) = ld32(base, (R(3) + 4));
    R(3) = (f + 120);
    R(6) = (R(5) + -1);
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[2].d); }
    R(0) = (R(6) + 1);
    R(31) = ((int32_t)R(0) * 12);
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[5].d); }
    R(0) = (R(6) + -1);
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[8].d); }
    R(5) = R(7) + R(31);
    { uint32_t ea_ = (R(7) + R(31)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(6) = ((int32_t)R(6) * 12);
    { uint32_t ea_ = (R(5) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[0].d * ctx->f[4].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[3].d * ctx->f[4].d);
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[6].d); }
    R(6) = R(7) + R(6);
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[2].d * ctx->f[4].d);
    { uint32_t ea_ = (R(6) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(0) = ((int32_t)R(0) * 12);
    { uint32_t ea_ = (R(6) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[10].d = ctx->ps1[10] = frsp(ctx->f[5].d - ctx->f[3].d);
    ctx->f[11].d = ctx->ps1[11] = frsp(ctx->f[8].d - ctx->f[2].d);
    R(7) = R(7) + R(0);
    ctx->f[12].d = ctx->ps1[12] = frsp(ctx->f[9].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[12].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(7) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[13].d = ctx->ps1[13] = frsp(ctx->f[2].d - ctx->f[4].d);
    { uint32_t ea_ = (R(5) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[0].d - ctx->f[4].d);
    { uint32_t ea_ = (R(6) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(7) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[28].d = ctx->ps1[28] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (R(5) + 0); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 0); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(7) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[31].d * ctx->f[29].d);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[4].d - ctx->f[3].d);
    ctx->f[27].d = ctx->ps1[27] = frsp(ctx->f[0].d - ctx->f[3].d);
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[7].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[13].d * ctx->f[28].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[30].d * ctx->f[28].d);
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[9].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[31].d * ctx->f[27].d);
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[8].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[13].d * ctx->f[27].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d * ctx->f[29].d);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[5].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[4].d - ctx->f[3].d);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[12].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[11].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[10].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[31].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[13].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[27].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[28].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[29].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[3].d); }
    GM_CALLV(0x80106A6Cu, 0x80238270u, 0);
    R(4) = (f + 104);
    R(3) = (f + 120);
    R(5) = R(4) |R(4);
    GM_CALLV(0x80106A7Cu, 0x801C1160u, 0);
    R(5) = ld32(base, (R(30) + 4));
    R(3) = ld32(base, (R(30) + 8));
    { uint32_t ea_ = (f + 104); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = R(5) + R(31);
    R(0) = (R(3) + 1);
    { uint32_t ea_ = (R(5) + R(31)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = ((int32_t)R(0) * 12);
    { uint32_t ea_ = (f + 112); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(4) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 108); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d + ctx->f[2].d);
    R(3) = R(5) + R(0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(5) + R(0)); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[2].d); }
    R(0) = lr;
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
}

/* fn_80106D60 (fn_80106D60, 112 bytes) */
static void wm_m_06d60(GM_CTX) {
    GM_FN(0x80106D60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80320000u);
    { uint32_t ea_ = (R(2) + -24136); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(6) = (R(6) + 7088);
    { uint32_t ea_ = (R(2) + -24132); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80100000u);
    { uint32_t ea_ = (R(2) + -24128); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80370000u);
    R(0) = ld32(base, (R(2) + -24852));
    R(4) = (R(4) + 28112);
    st32(base, (R(6) + 12), R(0));
    R(5) = (R(5) + 18704);
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80106DB8u, 0x802DC780u, 0);
    R(0) = ld32(base, (R(2) + -24828));
    st32(base, (R(13) + -21504), R(0));
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_WMC_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_WMC_COUNT)
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(GetPointFromIndex__12dWmConnect_cFi, 4) { wm_GetPointFromIndex__12dWmConnect_cFi_f32f0(GM_PASS); }
E(fn_800F3330, 4) { wm_m_f3330(GM_PASS); }
E(fn_800F33C0, 4) { wm_m_f33c0(GM_PASS); }
E(fn_800F33D0, 4) { wm_m_f33d0(GM_PASS); }
E(fn_800F3460, 4) { wm_m_f3460(GM_PASS); }
E(fn_800F3500, 4) { wm_m_f3500(GM_PASS); }
E(fn_800F35A0, 4) { wm_m_f35a0(GM_PASS); }
E(fn_800F35E0, 4) { wm_m_f35e0(GM_PASS); }
E(fn_800F39D0, 4) { wm_m_f39d0(GM_PASS); }
E(fn_800F3E20, 4) { wm_m_f3e20(GM_PASS); }
E(fn_800F3E80, 4) { wm_m_f3e80(GM_PASS); }
E(fn_800F4870, 4) { wm_m_f4870(GM_PASS); }
E(fn_800F4B50, 4) { wm_m_f4b50(GM_PASS); }
E(fn_800F4DA0, 4) { wm_m_f4da0(GM_PASS); }
E(fn_800F4F80, 4) { wm_m_f4f80(GM_PASS); }
E(fn_800F5050, 4) { wm_m_f5050(GM_PASS); }
E(fn_800F5130, 4) { wm_m_f5130(GM_PASS); }
E(fn_800F5310, 4) { wm_m_f5310(GM_PASS); }
E(fn_800F53A0, 4) { wm_m_f53a0(GM_PASS); }
E(fn_800F5420, 4) { wm_m_f5420(GM_PASS); }
E(fn_800F54D0, 4) { wm_m_f54d0(GM_PASS); }
E(fn_800F59E0, 4) { wm_m_f59e0(GM_PASS); }
E(fn_800F5A90, 4) { wm_m_f5a90(GM_PASS); }
E(fn_800F5C10, 4) { wm_m_f5c10(GM_PASS); }
E(fn_800F5D40, 4) { wm_m_f5d40(GM_PASS); }
E(fn_800F5E60, 4) { wm_m_f5e60(GM_PASS); }
E(fn_800F5F10, 4) { wm_m_f5f10(GM_PASS); }
E(fn_800F5F40, 4) { wm_m_f5f40(GM_PASS); }
E(fn_800F6020, 4) { wm_m_f6020(GM_PASS); }
E(fn_800F60D0, 4) { wm_m_f60d0(GM_PASS); }
E(fn_800F60E0, 4) { wm_m_f60e0(GM_PASS); }
E(fn_800F6110, 4) { wm_m_f6110(GM_PASS); }
E(fn_800F6130, 4) { wm_m_f6130(GM_PASS); }
E(fn_800F6320, 4) { wm_m_f6320(GM_PASS); }
E(fn_800F6390, 4) { wm_m_f6390(GM_PASS); }
E(fn_800F6410, 4) { wm_m_f6410(GM_PASS); }
E(fn_800F6810, 4) { wm_m_f6810(GM_PASS); }
E(fn_800F6910, 4) { wm_m_f6910(GM_PASS); }
E(fn_800F6920, 4) { wm_m_f6920(GM_PASS); }
E(fn_800F6940, 4) { wm_m_f6940(GM_PASS); }
E(fn_800F69F0, 4) { wm_m_f69f0(GM_PASS); }
E(fn_800F6AB0, 4) { wm_m_f6ab0(GM_PASS); }
E(fn_800F6B50, 4) { wm_m_f6b50(GM_PASS); }
E(fn_800F6C40, 4) { wm_m_f6c40(GM_PASS); }
E(fn_800F6CB0, 4) { wm_m_f6cb0(GM_PASS); }
E(fn_800F6D60, 4) { wm_m_f6d60(GM_PASS); }
E(fn_800F6DD0, 4) { wm_m_f6dd0(GM_PASS); }
E(fn_800F6DE0, 4) { wm_m_f6de0(GM_PASS); }
E(fn_800F6EB0, 4) { wm_m_f6eb0(GM_PASS); }
E(fn_800F9080, 4) { wm_m_f9080(GM_PASS); }
E(fn_800F91E0, 4) { wm_m_f91e0(GM_PASS); }
E(GetStartPointNameFromRouteName__6dWmLibFPCcPc, 4) { wm_GetStartPointNameFromRouteName__6dWmLibF_f9270(GM_PASS); }
E(GetEndPointNameFromRouteName__6dWmLibFPCcPc, 4) { wm_GetEndPointNameFromRouteName__6dWmLibFPC_f92c0(GM_PASS); }
E(fn_800F9310, 4) { wm_m_f9310(GM_PASS); }
E(fn_800F9370, 4) { wm_m_f9370(GM_PASS); }
E(fn_800F9930, 4) { wm_m_f9930(GM_PASS); }
E(fn_800F9970, 4) { wm_m_f9970(GM_PASS); }
E(fn_800F9BE0, 4) { wm_m_f9be0(GM_PASS); }
E(fn_800F9C50, 4) { wm_m_f9c50(GM_PASS); }
E(fn_800F9CD0, 4) { wm_m_f9cd0(GM_PASS); }
E(fn_800F9DB0, 4) { wm_m_f9db0(GM_PASS); }
E(fn_800F9EA0, 4) { wm_m_f9ea0(GM_PASS); }
E(GetOpenStatus__6dWmLibFii, 4) { wm_GetOpenStatus__6dWmLibFii_fa330(GM_PASS); }
E(fn_800FA350, 4) { wm_m_fa350(GM_PASS); }
E(fn_800FA5E0, 4) { wm_m_fa5e0(GM_PASS); }
E(fn_800FA630, 4) { wm_m_fa630(GM_PASS); }
E(fn_800FA6C0, 4) { wm_m_fa6c0(GM_PASS); }
E(GetClearStatus__6dWmLibFii, 4) { wm_GetClearStatus__6dWmLibFii_fa8c0(GM_PASS); }
E(GetCurrentPlayResultStatus__6dWmLibFiii, 4) { wm_GetCurrentPlayResultStatus__6dWmLibFiii_fa9c0(GM_PASS); }
E(IsCourseOmoteClear__6dWmLibFii, 4) { wm_IsCourseOmoteClear__6dWmLibFii_fad60(GM_PASS); }
E(IsCourseUraClear__6dWmLibFii, 4) { wm_IsCourseUraClear__6dWmLibFii_fadb0(GM_PASS); }
E(IsCourseClear__6dWmLibFii, 4) { wm_IsCourseClear__6dWmLibFii_fae40(GM_PASS); }
E(IsCourseFirstOmoteClear__6dWmLibFiii, 4) { wm_IsCourseFirstOmoteClear__6dWmLibFiii_fae80(GM_PASS); }
E(IsCourseFirstUraClear__6dWmLibFiii, 4) { wm_IsCourseFirstUraClear__6dWmLibFiii_faf70(GM_PASS); }
E(IsCourseFirstClear__6dWmLibFii, 4) { wm_IsCourseFirstClear__6dWmLibFii_fb040(GM_PASS); }
E(IsCourseOtasukeClearSimple__6dWmLibFii, 4) { wm_IsCourseOtasukeClearSimple__6dWmLibFii_fb150(GM_PASS); }
E(IsCourseUraOtasukeClearSimple__6dWmLibFii, 4) { wm_IsCourseUraOtasukeClearSimple__6dWmLibFi_fb1a0(GM_PASS); }
E(IsCourseOmoteClearSimple__6dWmLibFii, 4) { wm_IsCourseOmoteClearSimple__6dWmLibFii_fb1f0(GM_PASS); }
E(IsCourseUraClearSimple__6dWmLibFii, 4) { wm_IsCourseUraClearSimple__6dWmLibFii_fb240(GM_PASS); }
E(IsCourseFailed__6dWmLibFiii, 4) { wm_IsCourseFailed__6dWmLibFiii_fb290(GM_PASS); }
E(fn_800FB2D0, 4) { wm_m_fb2d0(GM_PASS); }
E(getStartPointKinokoHouseKindNum__6dWmLibFv, 4) { wm_getStartPointKinokoHouseKindNum__6dWmLib_fb350(GM_PASS); }
E(fn_800FB4B0, 4) { wm_m_fb4b0(GM_PASS); }
E(fn_800FBDE0, 4) { wm_m_fbde0(GM_PASS); }
E(fn_800FBF30, 4) { wm_m_fbf30(GM_PASS); }
E(fn_800FBFB0, 4) { wm_m_fbfb0(GM_PASS); }
E(fn_800FC040, 4) { wm_m_fc040(GM_PASS); }
E(fn_800FC0A0, 4) { wm_m_fc0a0(GM_PASS); }
E(getEnemyRevivalCount__6dWmLibFii, 4) { wm_getEnemyRevivalCount__6dWmLibFii_fc140(GM_PASS); }
E(fn_800FC2D0, 4) { wm_m_fc2d0(GM_PASS); }
E(fn_800FC370, 4) { wm_m_fc370(GM_PASS); }
E(fn_800FC5C0, 4) { wm_m_fc5c0(GM_PASS); }
E(fn_800FC7F0, 4) { wm_m_fc7f0(GM_PASS); }
E(fn_800FCA20, 4) { wm_m_fca20(GM_PASS); }
E(fn_800FCA50, 4) { wm_m_fca50(GM_PASS); }
E(fn_800FCAF0, 4) { wm_m_fcaf0(GM_PASS); }
E(fn_800FCBB0, 4) { wm_m_fcbb0(GM_PASS); }
E(fn_800FD2E0, 4) { wm_m_fd2e0(GM_PASS); }
E(fn_800FD310, 4) { wm_m_fd310(GM_PASS); }
E(fn_800FD500, 4) { wm_m_fd500(GM_PASS); }
E(fn_800FD590, 4) { wm_m_fd590(GM_PASS); }
E(fn_800FD630, 4) { wm_m_fd630(GM_PASS); }
E(fn_800FD720, 4) { wm_m_fd720(GM_PASS); }
E(fn_800FD750, 4) { wm_m_fd750(GM_PASS); }
E(fn_800FD7E0, 4) { wm_m_fd7e0(GM_PASS); }
E(fn_800FD800, 4) { wm_m_fd800(GM_PASS); }
E(fn_800FD820, 4) { wm_m_fd820(GM_PASS); }
E(fn_800FD8A0, 4) { wm_m_fd8a0(GM_PASS); }
E(fn_800FD8C0, 4) { wm_m_fd8c0(GM_PASS); }
E(fn_800FD900, 4) { wm_m_fd900(GM_PASS); }
E(fn_800FD920, 4) { wm_m_fd920(GM_PASS); }
E(fn_800FD9C0, 4) { wm_m_fd9c0(GM_PASS); }
E(fn_800FDA50, 4) { wm_m_fda50(GM_PASS); }
E(fn_800FDAC0, 4) { wm_m_fdac0(GM_PASS); }
E(fn_800FDB30, 4) { wm_m_fdb30(GM_PASS); }
E(fn_800FDC80, 4) { wm_m_fdc80(GM_PASS); }
E(fn_800FDCF0, 4) { wm_m_fdcf0(GM_PASS); }
E(fn_800FDD40, 4) { wm_m_fdd40(GM_PASS); }
E(fn_800FDD60, 4) { wm_m_fdd60(GM_PASS); }
E(fn_800FDF10, 4) { wm_m_fdf10(GM_PASS); }
E(fn_800FDF40, 4) { wm_m_fdf40(GM_PASS); }
E(fn_800FDF90, 4) { wm_m_fdf90(GM_PASS); }
E(fn_800FDFA0, 4) { wm_m_fdfa0(GM_PASS); }
E(fn_800FE030, 4) { wm_m_fe030(GM_PASS); }
E(CheckClipSphere__13dWmViewClip_cFPC9mSphere_c, 4) { wm_CheckClipSphere__13dWmViewClip_cFPC9mSph_fe040(GM_PASS); }
E(fn_800FE050, 4) { wm_m_fe050(GM_PASS); }
E(fn_800FE060, 4) { wm_m_fe060(GM_PASS); }
E(fn_800FE110, 4) { wm_m_fe110(GM_PASS); }
E(fn_800FE1C0, 4) { wm_m_fe1c0(GM_PASS); }
E(fn_800FE1D0, 4) { wm_m_fe1d0(GM_PASS); }
E(fn_800FE2E0, 4) { wm_m_fe2e0(GM_PASS); }
E(fn_800FE360, 4) { wm_m_fe360(GM_PASS); }
E(fn_800FE3B0, 4) { wm_m_fe3b0(GM_PASS); }
E(fn_800FE3F0, 4) { wm_m_fe3f0(GM_PASS); }
E(fn_800FE560, 4) { wm_m_fe560(GM_PASS); }
E(fn_800FE760, 4) { wm_m_fe760(GM_PASS); }
E(fn_800FE830, 4) { wm_m_fe830(GM_PASS); }
E(fn_800FE8F0, 4) { wm_m_fe8f0(GM_PASS); }
E(fn_800FE9E0, 4) { wm_m_fe9e0(GM_PASS); }
E(fn_800FEA90, 4) { wm_m_fea90(GM_PASS); }
E(fn_800FEAA0, 4) { wm_m_feaa0(GM_PASS); }
E(fn_800FEB40, 4) { wm_m_feb40(GM_PASS); }
E(fn_800FEC10, 4) { wm_m_fec10(GM_PASS); }
E(fn_800FEDD0, 4) { wm_m_fedd0(GM_PASS); }
E(fn_800FEED0, 4) { wm_m_feed0(GM_PASS); }
E(fn_800FF000, 4) { wm_m_ff000(GM_PASS); }
E(fn_800FF0C0, 4) { wm_m_ff0c0(GM_PASS); }
E(fn_800FF120, 4) { wm_m_ff120(GM_PASS); }
E(fn_800FF180, 4) { wm_m_ff180(GM_PASS); }
E(fn_800FF210, 4) { wm_m_ff210(GM_PASS); }
E(fn_800FF230, 4) { wm_m_ff230(GM_PASS); }
E(fn_800FF590, 4) { wm_m_ff590(GM_PASS); }
E(fn_800FF660, 4) { wm_m_ff660(GM_PASS); }
E(fn_800FF680, 4) { wm_m_ff680(GM_PASS); }
E(fn_800FF6A0, 4) { wm_m_ff6a0(GM_PASS); }
E(fn_800FF6B0, 4) { wm_m_ff6b0(GM_PASS); }
E(fn_800FF6C0, 4) { wm_m_ff6c0(GM_PASS); }
E(fn_800FF730, 4) { wm_m_ff730(GM_PASS); }
E(fn_800FF740, 4) { wm_m_ff740(GM_PASS); }
E(fn_800FFA50, 4) { wm_m_ffa50(GM_PASS); }
E(fn_800FFC40, 4) { wm_m_ffc40(GM_PASS); }
E(fn_800FFDB0, 4) { wm_m_ffdb0(GM_PASS); }
E(fn_800FFE20, 4) { wm_m_ffe20(GM_PASS); }
E(fn_800FFE70, 4) { wm_m_ffe70(GM_PASS); }
E(fn_800FFF90, 4) { wm_m_fff90(GM_PASS); }
E(fn_800FFFC0, 4) { wm_m_fffc0(GM_PASS); }
E(fn_800FFFE0, 4) { wm_m_fffe0(GM_PASS); }
E(fn_80100200, 4) { wm_m_00200(GM_PASS); }
E(fn_80100270, 4) { wm_m_00270(GM_PASS); }
E(fn_801002C0, 4) { wm_m_002c0(GM_PASS); }
E(fn_801002D0, 4) { wm_m_002d0(GM_PASS); }
E(fn_801002F0, 4) { wm_m_002f0(GM_PASS); }
E(fn_80100430, 4) { wm_m_00430(GM_PASS); }
E(fn_801004B0, 4) { wm_m_004b0(GM_PASS); }
E(fn_80100530, 4) { wm_m_00530(GM_PASS); }
E(fn_801005C0, 4) { wm_m_005c0(GM_PASS); }
E(GetNodePos__9daWmMap_cFlR7mVec3_c, 4) { wm_GetNodePos__9daWmMap_cFlR7mVec3_c_006c0(GM_PASS); }
E(fn_801006E0, 4) { wm_m_006e0(GM_PASS); }
E(GetNodeCount__9daWmMap_cFi, 4) { wm_GetNodeCount__9daWmMap_cFi_00720(GM_PASS); }
E(fn_80100830, 4) { wm_m_00830(GM_PASS); }
E(checkWalkPlayers__12daWmPlayer_cFv, 4) { wm_checkWalkPlayers__12daWmPlayer_cFv_00900(GM_PASS); }
E(fn_80100970, 4) { wm_m_00970(GM_PASS); }
E(fn_80100A00, 4) { wm_m_00a00(GM_PASS); }
E(fn_80100AA0, 4) { wm_m_00aa0(GM_PASS); }
E(fn_80100BD0, 4) { wm_m_00bd0(GM_PASS); }
E(fn_80100CA0, 4) { wm_m_00ca0(GM_PASS); }
E(fn_80100D90, 4) { wm_m_00d90(GM_PASS); }
E(fn_80100DA0, 4) { wm_m_00da0(GM_PASS); }
E(fn_80100F70, 4) { wm_m_00f70(GM_PASS); }
E(fn_80101430, 4) { wm_m_01430(GM_PASS); }
E(fn_801015A0, 4) { wm_m_015a0(GM_PASS); }
E(GetCutName__11dCsSeqMng_cFv, 4) { wm_GetCutName__11dCsSeqMng_cFv_015e0(GM_PASS); }
E(fn_80101630, 4) { wm_m_01630(GM_PASS); }
E(fn_80101670, 4) { wm_m_01670(GM_PASS); }
E(fn_80101690, 4) { wm_m_01690(GM_PASS); }
E(fn_80101720, 4) { wm_m_01720(GM_PASS); }
E(fn_80101940, 4) { wm_m_01940(GM_PASS); }
E(fn_80101950, 4) { wm_m_01950(GM_PASS); }
E(fn_80101960, 4) { wm_m_01960(GM_PASS); }
E(setChangePosFunc__10dScStage_cFi, 4) { wm_setChangePosFunc__10dScStage_cFi_01bc0(GM_PASS); }
E(fn_80101BE0, 4) { wm_m_01be0(GM_PASS); }
E(fn_80101BF0, 4) { wm_m_01bf0(GM_PASS); }
E(fn_80101C60, 4) { wm_m_01c60(GM_PASS); }
E(fn_80101CE0, 4) { wm_m_01ce0(GM_PASS); }
E(fn_80101D40, 4) { wm_m_01d40(GM_PASS); }
E(fn_80101DC0, 4) { wm_m_01dc0(GM_PASS); }
E(fn_80101E20, 4) { wm_m_01e20(GM_PASS); }
E(fn_80101EA0, 4) { wm_m_01ea0(GM_PASS); }
E(fn_80101F00, 4) { wm_m_01f00(GM_PASS); }
E(fn_80101F50, 4) { wm_m_01f50(GM_PASS); }
E(fn_801020F0, 4) { wm_m_020f0(GM_PASS); }
E(createReplayDataHeap__10dScStage_cFPQ23EGG4HeapUli, 4) { wm_createReplayDataHeap__10dScStage_cFPQ23E_021d0(GM_PASS); }
E(fn_801024A0, 4) { wm_m_024a0(GM_PASS); }
E(fn_80102580, 4) { wm_m_02580(GM_PASS); }
E(setTitleReplayRandomTable__10dScStage_cFv, 4) { wm_setTitleReplayRandomTable__10dScStage_cF_025c0(GM_PASS); }
E(fn_801025D0, 4) { wm_m_025d0(GM_PASS); }
E(fn_80102660, 4) { wm_m_02660(GM_PASS); }
E(fn_80102670, 4) { wm_m_02670(GM_PASS); }
E(_Z20SetSomeConditionShitiij, 4) { wm__Z20SetSomeConditionShitiij_026d0(GM_PASS); }
E(fn_80102730, 4) { wm_m_02730(GM_PASS); }
E(IsCourseType__9dScWMap_cFiiQ29dScWMap_c12CourseType_e, 4) { wm_IsCourseType__9dScWMap_cFiiQ29dScWMap_c1_02750(GM_PASS); }
E(fn_80102790, 4) { wm_m_02790(GM_PASS); }
E(fn_80102C10, 4) { wm_m_02c10(GM_PASS); }
E(fn_80102CA0, 4) { wm_m_02ca0(GM_PASS); }
E(fn_80102E00, 4) { wm_m_02e00(GM_PASS); }
E(fn_80102E80, 4) { wm_m_02e80(GM_PASS); }
E(fn_80102F10, 4) { wm_m_02f10(GM_PASS); }
E(fn_80102F90, 4) { wm_m_02f90(GM_PASS); }
E(fn_80103000, 4) { wm_m_03000(GM_PASS); }
E(fn_80103090, 4) { wm_m_03090(GM_PASS); }
E(fn_801030E0, 4) { wm_m_030e0(GM_PASS); }
E(fn_80103150, 4) { wm_m_03150(GM_PASS); }
E(fn_801031B0, 4) { wm_m_031b0(GM_PASS); }
E(fn_80103220, 4) { wm_m_03220(GM_PASS); }
E(fn_80103310, 4) { wm_m_03310(GM_PASS); }
E(playEffect__18dWmEffectManager_cFiPC7mVec3_cPC7mAng3_cPC7mVec3_c, 4) { wm_playEffect__18dWmEffectManager_cFiPC7mVe_03390(GM_PASS); }
E(fn_80103410, 4) { wm_m_03410(GM_PASS); }
E(fn_80103440, 4) { wm_m_03440(GM_PASS); }
E(endEffect__18dWmEffectManager_cFi, 4) { wm_endEffect__18dWmEffectManager_cFi_034e0(GM_PASS); }
E(fn_80103500, 4) { wm_m_03500(GM_PASS); }
E(fn_80103580, 4) { wm_m_03580(GM_PASS); }
E(fn_80103730, 4) { wm_m_03730(GM_PASS); }
E(fn_801037C0, 4) { wm_m_037c0(GM_PASS); }
E(fn_80103840, 4) { wm_m_03840(GM_PASS); }
E(fn_801038F0, 4) { wm_m_038f0(GM_PASS); }
E(fn_80103A10, 4) { wm_m_03a10(GM_PASS); }
E(fn_80103A20, 4) { wm_m_03a20(GM_PASS); }
E(fn_80103A30, 4) { wm_m_03a30(GM_PASS); }
E(fn_80103AC0, 4) { wm_m_03ac0(GM_PASS); }
E(fn_80103B00, 4) { wm_m_03b00(GM_PASS); }
E(fn_80103D40, 4) { wm_m_03d40(GM_PASS); }
E(fn_80103E20, 4) { wm_m_03e20(GM_PASS); }
E(fn_80103F10, 4) { wm_m_03f10(GM_PASS); }
E(playSound__14dWmSeManager_cFiRC7mVec3_ci, 4) { wm_playSound__14dWmSeManager_cFiRC7mVec3_ci_05240(GM_PASS); }
E(fn_80105370, 4) { wm_m_05370(GM_PASS); }
E(playSound__14dWmSeManager_cFiiRC7mVec3_cii, 4) { wm_playSound__14dWmSeManager_cFiiRC7mVec3_c_05440(GM_PASS); }
E(fn_80105480, 4) { wm_m_05480(GM_PASS); }
E(fn_801055F0, 4) { wm_m_055f0(GM_PASS); }
E(fn_80105EE0, 4) { wm_m_05ee0(GM_PASS); }
E(fn_80105F40, 4) { wm_m_05f40(GM_PASS); }
E(fn_80105FD0, 4) { wm_m_05fd0(GM_PASS); }
E(fn_80106190, 4) { wm_m_06190(GM_PASS); }
E(fn_80106200, 4) { wm_m_06200(GM_PASS); }
E(fn_80106280, 4) { wm_m_06280(GM_PASS); }
E(fn_801062B0, 4) { wm_m_062b0(GM_PASS); }
E(fn_80106620, 4) { wm_m_06620(GM_PASS); }
E(fn_801068B0, 4) { wm_m_068b0(GM_PASS); }
E(fn_80106D60, 4) { wm_m_06d60(GM_PASS); }
