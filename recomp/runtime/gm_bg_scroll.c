/* gm_bg_scroll.c - instance 2 (track B, camera / scroll): the background manager dBg_c - scroll
 * position and limits, loop scroll, auto scroll, the screen / zoom parameters (dBgParameter_c),
 * water and wave levels, the coin bitfield - and the background collision objects dBg_ctr_c,
 * E2 0x80076800-0x80084000 (after dBc_c's checks). Transliterated by tools/gm_conv.py from the
 * recompiled bodies (statement for statement in the natives' macros); only functions the A/B
 * inputs (tools/ab_inputs/) reach are on, the gate is the strict A/B. Functions another runtime
 * file defines or calls by symbol (gm_bg.c's tile lookups ...) are left to their owners.
 * Build flags (testing): -DGM_BG_COUNT logs each native's first call, -DGM_BG_VERIFY makes them
 * switchable (RT_GM_VERIFY=orig:<names>). */

#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d

/* fn_80076BB0 (fn_80076BB0, 4 bytes) */
static void bg_m_76bb0(GM_CTX) {

}

/* fn_80076BC0 (fn_80076BC0, 40 bytes) */
static void bg_m_76bc0(GM_CTX) {
    R(0) = (0 + 0);
    st8(base, (R(3) + 500), R(0));
    st16(base, (R(3) + 504), R(0));
    st8(base, (R(3) + 501), R(0));
    st16(base, (R(3) + 506), R(0));
    st8(base, (R(3) + 502), R(0));
    st16(base, (R(3) + 508), R(0));
    st8(base, (R(3) + 503), R(0));
    st16(base, (R(3) + 510), R(0));
}

/* fn_80076BF0 (fn_80076BF0, 372 bytes) */
static void bg_m_76bf0(GM_CTX) {
    R(0) = (0 + 4);
    R(10) = (0 + 0);
    R(5) = (0 + 0);
    R(4) = (0 + -1);
    ctx->ctr = R(0);
L_80076C04:;
    R(7) = rotl32(R(10), 2) & 0x3FFFCu;
    R(0) = R(10) & 0xFFFFu;
    st32(base, (R(3) + R(7)), R(5));
    R(9) = R(3) + R(0);
    R(10) = (R(10) + 8);
    R(8) = R(3) + R(7);
    st8(base, (R(9) + 400), R(4));
    R(7) = rotl32(R(10), 2) & 0x3FFFCu;
    R(6) = R(10) & 0xFFFFu;
    R(10) = (R(10) + 8);
    st32(base, (R(8) + 4), R(5));
    st8(base, (R(9) + 401), R(4));
    st32(base, (R(8) + 8), R(5));
    st8(base, (R(9) + 402), R(4));
    st32(base, (R(8) + 12), R(5));
    st8(base, (R(9) + 403), R(4));
    st32(base, (R(8) + 16), R(5));
    st8(base, (R(9) + 404), R(4));
    st32(base, (R(8) + 20), R(5));
    st8(base, (R(9) + 405), R(4));
    st32(base, (R(8) + 24), R(5));
    st8(base, (R(9) + 406), R(4));
    st32(base, (R(8) + 28), R(5));
    R(8) = R(3) + R(7);
    R(7) = rotl32(R(10), 2) & 0x3FFFCu;
    st8(base, (R(9) + 407), R(4));
    R(9) = R(3) + R(6);
    R(6) = R(10) & 0xFFFFu;
    R(10) = (R(10) + 8);
    st32(base, (R(8) + 0), R(5));
    st8(base, (R(9) + 400), R(4));
    st32(base, (R(8) + 4), R(5));
    st8(base, (R(9) + 401), R(4));
    st32(base, (R(8) + 8), R(5));
    st8(base, (R(9) + 402), R(4));
    st32(base, (R(8) + 12), R(5));
    st8(base, (R(9) + 403), R(4));
    st32(base, (R(8) + 16), R(5));
    st8(base, (R(9) + 404), R(4));
    st32(base, (R(8) + 20), R(5));
    st8(base, (R(9) + 405), R(4));
    st32(base, (R(8) + 24), R(5));
    st8(base, (R(9) + 406), R(4));
    st32(base, (R(8) + 28), R(5));
    R(8) = R(3) + R(7);
    st8(base, (R(9) + 407), R(4));
    R(9) = R(3) + R(6);
    R(6) = R(10) & 0xFFFFu;
    st32(base, (R(3) + R(7)), R(5));
    st8(base, (R(9) + 400), R(4));
    st32(base, (R(8) + 4), R(5));
    st8(base, (R(9) + 401), R(4));
    st32(base, (R(8) + 8), R(5));
    st8(base, (R(9) + 402), R(4));
    st32(base, (R(8) + 12), R(5));
    st8(base, (R(9) + 403), R(4));
    st32(base, (R(8) + 16), R(5));
    st8(base, (R(9) + 404), R(4));
    st32(base, (R(8) + 20), R(5));
    st8(base, (R(9) + 405), R(4));
    st32(base, (R(8) + 24), R(5));
    st8(base, (R(9) + 406), R(4));
    st32(base, (R(8) + 28), R(5));
    st8(base, (R(9) + 407), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80076C04; }
    R(4) = rotl32(R(10), 2) & 0x3FFFCu;
    R(8) = (0 + 0);
    st32(base, (R(3) + R(4)), R(8));
    R(9) = R(3) + R(4);
    R(4) = R(3) + R(6);
    R(7) = (0 + -1);
    st8(base, (R(4) + 400), R(7));
    R(0) = (R(10) + 1);
    R(5) = R(0) & 0xFFFFu;
    st32(base, (R(9) + 4), R(8));
    R(6) = R(3) + R(5);
    R(0) = (R(10) + 2);
    st8(base, (R(6) + 400), R(7));
    R(4) = R(0) & 0xFFFFu;
    R(0) = (R(10) + 3);
    st32(base, (R(9) + 8), R(8));
    R(5) = R(3) + R(4);
    R(0) = R(0) & 0xFFFFu;
    st8(base, (R(5) + 400), R(7));
    R(4) = R(3) + R(0);
    st32(base, (R(9) + 12), R(8));
    st8(base, (R(4) + 400), R(7));
    GM_TAIL(0x80076BC0u, 0); return;
}

/* fn_80076FD0 (fn_80076FD0, 68 bytes) */
static void bg_m_76fd0(GM_CTX) {
    GM_FN(0x80076FD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld32(base, (R(13) + -22708));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80077004; }
    R(3) = ld32(base, (R(13) + -22712));
    R(5) = (0 + 0);
    R(4) = ld32(base, (R(13) + -18544));
    R(6) = (0 + 32);
    R(7) = (0 + 0);
    GM_CALLV(0x80077000u, 0x8016E630u, 0);
    st32(base, (R(13) + -22708), R(3));
L_80077004:;
    R(0) = lr;
}

/* fn_80077020 (fn_80077020, 64 bytes) */
static void bg_m_77020(GM_CTX) {
    GM_FN(0x80077020); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(3) = ld32(base, (R(13) + -22708));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077050; }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    GM_CALLV(0x80077048u, ctx->ctr, 0);
    R(0) = (0 + 0);
    st32(base, (R(13) + -22708), R(0));
L_80077050:;
    R(0) = lr;
}

/* fn_80077060 (fn_80077060, 808 bytes) */
static void bg_m_77060(GM_CTX) {
    GM_FN(0x80077060); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    GM_CALLV(0x8007707Cu, 0x8006C420u, 0);
    R(6) = (0 + 0x80310000u);
    R(3) = (R(30) + 0x90000u);
    R(6) = (R(6) + -2928);
    R(4) = (0 + 0x80070000u);
    R(5) = (0 + 0x80070000u);
    st32(base, (R(30) + 96), R(6));
    R(4) = (R(4) + 29584);
    R(6) = (0 + 28);
    R(5) = (R(5) + 29600);
    R(7) = (0 + 2);
    R(3) = (R(3) + 172);
    GM_CALLV(0x800770ACu, 0x802DC9A0u, 0);
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (0 + 0);
    { uint32_t ea_ = (R(3) + 2520); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 2524); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 2528); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 2532); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(3) + 2536), R(31));
    st32(base, (R(3) + 2540), R(31));
    st32(base, (R(3) + 2544), R(31));
    st32(base, (R(3) + 2548), R(31));
    { uint32_t ea_ = (R(3) + 2572); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 2576); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 2580); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 2584); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(3) + 2588), R(31));
    st32(base, (R(3) + 2592), R(31));
    st32(base, (R(3) + 2596), R(31));
    st32(base, (R(3) + 2600), R(31));
    R(3) = (R(3) + 2640);
    GM_CALLV(0x80077100u, 0x80087380u, 0);
    st32(base, (R(13) + -22704), R(30));
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = (0 + 2);
    R(4) = R(30) |R(30);
    st32(base, (R(30) + 112), R(31));
    { uint32_t ea_ = (R(2) + -29548); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -444); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -440); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -436); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -432); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -428); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -424); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -420); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -392); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -388); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -384); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -380); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -376); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -372); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -368); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -364); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -360); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -356); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -352); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -348); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -344); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -340); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -332); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -328); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -396); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -324); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -320); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -316); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + -312); stfs(base, ea_, ctx->f[1].d); }
    ctx->ctr = R(0);
L_80077190:;
    R(3) = (R(4) + 0x90000u);
    R(4) = (R(4) + 32);
    { uint32_t ea_ = (R(3) + -308); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -304); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -292); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -280); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (R(4) + 0x90000u);
    R(4) = (R(4) + 32);
    { uint32_t ea_ = (R(3) + -308); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -304); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -292); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -280); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (R(4) + 0x90000u);
    R(4) = (R(4) + 32);
    { uint32_t ea_ = (R(3) + -308); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -304); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -292); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -280); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (R(4) + 0x90000u);
    R(4) = (R(4) + 32);
    { uint32_t ea_ = (R(3) + -308); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -304); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -292); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -280); stfs(base, ea_, ctx->f[0].d); }
    R(3) = (R(4) + 0x90000u);
    R(4) = (R(4) + 32);
    { uint32_t ea_ = (R(3) + -308); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -304); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -300); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -296); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -292); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -288); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -284); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -280); stfs(base, ea_, ctx->f[0].d); }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80077190; }
    R(6) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(31) = (0 + 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29548); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(5) = (0 + 0x80310000u);
    { uint32_t ea_ = (R(6) + 12); stfs(base, ea_, ctx->f[2].d); }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (R(6) + 16); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 20); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 40); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(6) + 32), R(31));
    st8(base, (R(6) + 33), R(31));
    st8(base, (R(6) + 34), R(31));
    st8(base, (R(6) + 44), R(31));
    { uint32_t ea_ = (R(6) + 48); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 56); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 60); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 64); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 68); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 72); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 76); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 80); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 84); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 88); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 92); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(6) + 120), R(31));
    st8(base, (R(6) + 121), R(31));
    st8(base, (R(6) + 122), R(31));
    { uint32_t ea_ = (R(6) + -336); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 136); stfs(base, ea_, ctx->f[2].d); }
    st32(base, (R(6) + 140), R(31));
    { uint32_t ea_ = (R(6) + 144); stfs(base, ea_, ctx->f[1].d); }
    st8(base, (R(6) + 148), R(31));
    { uint32_t ea_ = (R(6) + 152); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 164); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 168); stfs(base, ea_, ctx->f[1].d); }
    st32(base, (R(6) + 236), R(31));
    st32(base, (R(6) + 240), R(31));
    { uint32_t ea_ = (R(6) + 244); stfs(base, ea_, ctx->f[1].d); }
    st16(base, (R(6) + 248), R(31));
    st16(base, (R(6) + 250), R(31));
    st8(base, (R(6) + 254), R(31));
    st8(base, (R(6) + 255), R(31));
    st8(base, (R(6) + 256), R(31));
    st8(base, (R(6) + 257), R(31));
    st8(base, (R(6) + 258), R(31));
    st8(base, (R(6) + 259), R(31));
    st16(base, (R(6) + 294), R(31));
    st8(base, (R(6) + 292), R(31));
    { uint32_t ea_ = R(5) + -3104; R(4) = ld32(base, ea_); R(5) = ea_; }
    R(0) = ld32(base, (R(5) + 4));
    st32(base, (R(6) + 128), R(0));
    st32(base, (R(6) + 124), R(4));
    R(0) = ld32(base, (R(5) + 8));
    st32(base, (R(6) + 132), R(0));
    st32(base, (R(6) + 2624), R(31));
    st32(base, (R(6) + 2628), R(31));
    st32(base, (R(6) + 2632), R(31));
    st32(base, (R(6) + 2636), R(31));
    GM_CALLV(0x8007735Cu, 0x80079B60u, 0);
    R(3) = (R(30) + 0x90000u);
    st8(base, (R(3) + 2508), R(31));
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007736Cu, 0x800784D0u, 0);
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_80077390 (fn_80077390, 4 bytes) */
static void bg_m_77390(GM_CTX) {

}

/* fn_800773A0 (fn_800773A0, 64 bytes) */
static void bg_m_773a0(GM_CTX) {
    GM_FN(0x800773A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800773C8; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800773C8; }
    GM_CALLV(0x800773C8u, 0x802B9280u, 0);
L_800773C8:;
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_800773E0 (fn_800773E0, 144 bytes) */
static void bg_m_773e0(GM_CTX) {
    GM_FN(0x800773E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80077454; }
    R(3) = (R(3) + 0x90000u);
    R(0) = (0 + 0);
    st32(base, (R(13) + -22704), R(0));
    R(4) = (0 + -1);
    R(3) = (R(3) + 2640);
    GM_CALLV(0x8007741Cu, 0x80087410u, 0);
    R(3) = (R(30) + 0x90000u);
    R(4) = (0 + 0x80070000u);
    R(4) = (R(4) + 29600);
    R(5) = (0 + 28);
    R(6) = (0 + 2);
    R(3) = (R(3) + 172);
    GM_CALLV(0x80077438u, 0x802DCA98u, 0);
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x80077444u, 0x8006C490u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80077454; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80077454u, 0x80162920u, 0);
L_80077454:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_80077490 (fn_80077490, 16 bytes) */
static void bg_m_77490(GM_CTX) {
    R(3) = ld32(base, (R(3) + 112));
    R(0) = rotl32(R(4), 3) & 0x7FFF8u;
    R(3) = R(3) + R(0);
}

/* fn_800775A0 (fn_800775A0, 100 bytes) */
static void bg_m_775a0(GM_CTX) {
    GM_FN(0x800775A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(8) = (0 + 0);
    R(31) = R(7) |R(7);
    R(7) = (0 + 0);
    GM_CALLV(0x800775C0u, 0x80077520u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(4) = (0 + 0x10000u);
    R(0) = (R(4) + -1);
    if ((CR_BIT(ctx, 2))) { goto L_800775EC; }
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800775E4; }
    R(3) = ld16(base, (R(3) + 0));
    GM_CALLV(0x800775E0u, 0x80081AB0u, 0);
    goto L_800775E8;
L_800775E4:;
    R(3) = ld16(base, (R(3) + 0));
L_800775E8:;
    R(0) = R(3) |R(3);
L_800775EC:;
    R(3) = R(0) |R(0);
    R(0) = lr;
}

/* fn_80077610 (fn_80077610, 52 bytes) */
static void bg_m_77610(GM_CTX) {
    GM_FN(0x80077610); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(7) = (0 + 1);
    GM_CALLV(0x80077624u, 0x800775A0u, 0);
    R(0) = R(3) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_80077634; }
    R(3) = R(3) & 0x3FFu;
L_80077634:;
    R(0) = lr;
}

/* fn_80077730 (fn_80077730, 120 bytes) */
static void bg_m_77730(GM_CTX) {
    GM_FN(0x80077730); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(31) = rotl32(R(5), 2) & 0x3C00u;
    R(0) = rotl32(R(5), 28) & 0xFu;
    R(31) = R(31) + R(0);
    R(5) = ld32(base, (R(13) + -21688));
    R(0) = rotl32(R(4), 28) & 0x1F0u;
    R(27) = R(4) |R(4);
    R(31) = R(31) + R(0);
    R(4) = ld8(base, (R(5) + 4622));
    R(3) = ld32(base, (R(13) + -22656));
    R(28) = R(7) |R(7);
    R(29) = R(8) |R(8);
    R(30) = R(9) |R(9);
    R(5) = R(31) & 0xFFFFu;
    GM_CALLV(0x8007777Cu, 0x80082120u, 0);
    st16(base, (R(28) + 0), R(3));
    R(3) = rotl32(R(27), 28) & 0xFu;
    GM_CALLV(0x80077788u, 0x800834B0u, 0);
    st16(base, (R(29) + 0), R(3));
    R(11) = (f + 32);
    st16(base, (R(30) + 0), R(31));
    R(0) = lr;
}

/* CoinGetBitSet__5dBg_cFUsUsi (CoinGetBitSet__5dBg_cFUsUsi, 96 bytes) */
static void bg_CoinGetBitSet__5dBg_cFUsUsi_777b0(GM_CTX) {
    GM_FN(0x800777B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(7) = (f + 10);
    R(8) = (f + 8);
    R(9) = (f + 12);
    R(31) = R(6) |R(6);
    GM_CALLV(0x800777D4u, 0x80077730u, 0);
    R(3) = ld16(base, (f + 10));
    R(6) = R(31) |R(31);
    R(0) = ld16(base, (f + 8));
    R(4) = ld32(base, (R(13) + -21688));
    R(7) = R(3) |R(0);
    st16(base, (f + 10), R(7));
    R(3) = ld32(base, (R(13) + -22656));
    R(4) = ld8(base, (R(4) + 4622));
    R(5) = ld16(base, (f + 12));
    GM_CALLV(0x800777FCu, 0x80082140u, 0);
    R(0) = lr;
}

/* CoinGetBitCheck__5dBg_cFUsUsi (CoinGetBitCheck__5dBg_cFUsUsi, 68 bytes) */
static void bg_CoinGetBitCheck__5dBg_cFUsUsi_77810(GM_CTX) {
    GM_FN(0x80077810); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(7) = (f + 10);
    R(8) = (f + 8);
    R(9) = (f + 12);
    GM_CALLV(0x8007782Cu, 0x80077730u, 0);
    R(3) = ld16(base, (f + 10));
    R(0) = ld16(base, (f + 8));
    R(3) = R(3) &R(0);
    R(0) = -(int32_t)R(3);
    R(0) = R(0) |R(3);
    R(3) = rotl32(R(0), 1) & 0x1u;
    R(0) = lr;
}

/* placeTile__8BgGmBaseFUsUsii (placeTile__8BgGmBaseFUsUsii, 288 bytes) */
static void bg_placeTile__8BgGmBaseFUsUsii_77860(GM_CTX) {
    GM_FN(0x80077860); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    cr_cmp_u(ctx, 0, R(7), 0x2u);
    R(26) = R(3) |R(3);
    R(27) = R(4) |R(4);
    R(28) = R(5) |R(5);
    R(29) = R(6) |R(6);
    R(30) = R(7) |R(7);
    if ((!CR_BIT(ctx, 2))) { goto L_800778A8; }
    R(3) = ld32(base, (R(13) + -22144));
    R(4) = (0 + 0);
    GM_CALLV(0x8007789Cu, 0x800D87B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800778A8; }
    R(30) = (0 + 4);
L_800778A8:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = R(28) |R(28);
    R(6) = R(29) & 0xFFu;
    R(7) = (f + 12);
    R(8) = (0 + 1);
    GM_CALLV(0x800778C4u, 0x80077520u, 0);
    R(0) = ld32(base, (f + 12));
    R(31) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077968; }
    R(0) = (0 + 0);
    st16(base, (f + 8), R(0));
    R(4) = (f + 8);
    R(3) = ld16(base, (R(3) + 0));
    GM_CALLV(0x800778E8u, 0x80081900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077904; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = R(28) |R(28);
    R(6) = R(29) |R(29);
    GM_CALLV(0x80077904u, 0x800777B0u, 0);
L_80077904:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007790Cu, 0x80083490u, 0);
    R(6) = R(3) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(6), 0xFFFFu);
    if ((!CR_BIT(ctx, 2))) { goto L_80077948; }
    cr_cmp_u(ctx, 0, R(30), 0x8Au);
    if ((!CR_BIT(ctx, 2))) { goto L_80077930; }
    R(0) = ld16(base, (R(31) + 0));
    R(0) = R(0) & 0x3FFu;
    st16(base, (R(31) + 0), R(0));
    goto L_80077968;
L_80077930:;
    cr_cmp_u(ctx, 0, R(30), 0x8Bu);
    if ((!CR_BIT(ctx, 2))) { goto L_80077968; }
    R(0) = ld16(base, (R(31) + 0));
    R(0) = R(0) | 0x400u;
    st16(base, (R(31) + 0), R(0));
    goto L_80077968;
L_80077948:;
    st16(base, (R(31) + 0), R(3));
    R(3) = (R(26) + 0x90000u);
    R(0) = rotl32(R(29), 2) & 0xFFFFFFFCu;
    R(4) = rotl32(R(27), 28) & 0xFFFu;
    R(3) = R(3) + R(0);
    R(5) = rotl32(R(28), 28) & 0xFFFu;
    R(3) = ld32(base, (R(3) + 2624));
    GM_CALLV(0x80077968u, 0x80083380u, 0);
L_80077968:;
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_80077980 (fn_80077980, 116 bytes) */
static void bg_m_77980(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    R(3) = ld32(base, (R(13) + -21688));
    R(5) = ld32(base, (R(13) + -22672));
    if ((CR_BIT(ctx, 2))) { goto L_800779A4; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800779AC; }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800779CC; }
    goto L_800779EC;
L_800779A4:;
    R(3) = (0 + 1);
    return;
L_800779AC:;
    R(0) = ld8(base, (R(3) + 4622));
    R(0) = ((int32_t)R(0) * 12);
    R(3) = R(5) + R(0);
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800779EC; }
    R(3) = (0 + 1);
    return;
L_800779CC:;
    R(0) = ld8(base, (R(3) + 4622));
    R(0) = ((int32_t)R(0) * 12);
    R(3) = R(5) + R(0);
    R(0) = ld32(base, (R(3) + 12));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800779EC; }
    R(3) = (0 + 1);
    return;
L_800779EC:;
    R(3) = (0 + 0);
}

/* fn_80077A00 (fn_80077A00, 252 bytes) */
static void bg_m_77a00(GM_CTX) {
    GM_FN(0x80077A00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 176);
    R(4) = ld32(base, (R(13) + -22708));
    R(25) = R(3) |R(3);
    R(3) = (0 + 8192);
    R(5) = (0 + 4);
    GM_CALLV(0x80077A28u, 0x802B9270u, 0);
    st32(base, (R(25) + 112), R(3));
    R(27) = (0 + 0);
    R(30) = (0 + 0);
    R(31) = (0 + 0x80310000u);
    R(3) = ld32(base, (R(13) + -21688));
    R(28) = ld8(base, (R(3) + 4622));
L_80077A40:;
    R(3) = ld32(base, (R(13) + -22672));
    R(4) = R(28) |R(28);
    R(5) = R(27) |R(27);
    GM_CALLV(0x80077A50u, 0x800813F0u, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(29) = R(3) |R(3);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80077AD4; }
    R(5) = R(29) |R(29);
    R(3) = (f + 72);
    R(4) = (R(31) + -3092);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80077A74u, 0x802E17DCu, 0);
    R(5) = R(29) |R(29);
    R(3) = (f + 8);
    R(4) = (R(13) + -32048);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80077A88u, 0x802E17DCu, 0);
    R(3) = ld32(base, (R(13) + -22088));
    R(4) = (f + 8);
    R(5) = (f + 72);
    R(3) = (R(3) + 4);
    GM_CALLV(0x80077A9Cu, 0x800DF180u, 0);
    R(29) = R(3) |R(3);
    R(26) = (0 + 0);
L_80077AA4:;
    R(0) = R(26) + R(30);
    R(3) = R(25) |R(25);
    R(4) = R(0) & 0xFFFFu;
    GM_CALLV(0x80077AB4u, 0x80077490u, 0);
    R(0) = ld32(base, (R(29) + 0));
    R(26) = (R(26) + 1);
    R(4) = ld32(base, (R(29) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(26), 256);
    st32(base, (R(3) + 4), R(4));
    R(29) = (R(29) + 8);
    st32(base, (R(3) + 0), R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80077AA4; }
L_80077AD4:;
    R(27) = (R(27) + 1);
    R(30) = (R(30) + 256);
    cr_cmp_s(ctx, 0, (int32_t)R(27), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80077A40; }
    R(11) = (f + 176);
    R(0) = lr;
}

/* fn_80077B00 (fn_80077B00, 60 bytes) */
static void bg_m_77b00(GM_CTX) {
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 2))) { goto L_80077B18; }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_80077B18:;
    { uint32_t ea_ = (R(13) + -21908); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(13) + -22656));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 64); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(13) + -21904); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(13) + -22656));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 68); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_80077B40 (fn_80077B40, 568 bytes) */
static void bg_m_77b40(GM_CTX) {
    GM_FN(0x80077B40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 80);
    R(4) = (0 + 0x80370000u);
    R(31) = R(3) |R(3);
    R(4) = (R(4) + 31816);
    R(3) = (R(3) + 0x90000u);
    R(4) = ld32(base, (R(4) + 8));
    R(3) = (R(3) + 2640);
    GM_CALLV(0x80077B70u, 0x80087510u, 0);
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29528); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -412); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -404); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -408); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d * ctx->f[4].d);
    ctx->f[2].u = ctx->f[5].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(3) + -400); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[5].d - ctx->f[6].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[4].d);
    ctx->f[1].u = fctiw_bits(ctx->f[1].d, 1);
    ctx->f[4].u = fctiw_bits(ctx->f[3].d, 1);
    { uint32_t ea_ = (f + 40); st64(base, ea_, ctx->f[1].u); }
    ctx->f[3].u = fctiw_bits(ctx->f[2].d, 1);
    ctx->f[2].u = fctiw_bits(ctx->f[5].d, 1);
    ctx->f[1].u = fctiw_bits(ctx->f[6].d, 1);
    R(28) = ld32(base, (f + 44));
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[4].u); }
    R(0) = R(28) & 0xFu;
    CR0(ctx, R(0));
    { uint32_t ea_ = (f + 16); st64(base, ea_, ctx->f[3].u); }
    R(30) = ld32(base, (f + 12));
    { uint32_t ea_ = (f + 24); st64(base, ea_, ctx->f[2].u); }
    R(29) = ld32(base, (f + 20));
    { uint32_t ea_ = (f + 32); st64(base, ea_, ctx->f[1].u); }
    R(3) = ld32(base, (f + 28));
    { uint32_t ea_ = (f + 48); st64(base, ea_, ctx->f[0].u); }
    R(4) = ld32(base, (f + 36));
    R(27) = ld32(base, (f + 52));
    if ((CR_BIT(ctx, 2))) { goto L_80077BF8; }
    R(28) = rotl32(R(28), 28) & 0xFFFu;
    R(28) = (R(28) + 1);
    goto L_80077BFC;
L_80077BF8:;
    R(28) = rotl32(R(28), 28) & 0xFFFu;
L_80077BFC:;
    R(0) = R(27) & 0xFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80077C10; }
    R(27) = rotl32(R(27), 28) & 0xFFFu;
    R(27) = (R(27) + 1);
    goto L_80077C38;
L_80077C10:;
    R(0) = R(3) & 0xFu;
    CR0(ctx, R(0));
    R(27) = rotl32(R(27), 28) & 0xFFFu;
    if ((CR_BIT(ctx, 2))) { goto L_80077C24; }
    R(0) = (R(27) + 1);
    R(27) = R(0) & 0xFFFFu;
L_80077C24:;
    R(0) = R(4) & 0xFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80077C38; }
    R(3) = R(27) & 0xFFFFu;
    R(0) = (R(3) + 1);
    R(27) = R(0) & 0xFFFFu;
L_80077C38:;
    R(0) = ld32(base, (R(13) + -21624));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80077C4C; }
    R(28) = (R(28) + 2);
    R(30) = (R(30) + -1);
L_80077C4C:;
    R(29) = (R(29) + -1);
    R(27) = (R(27) + 2);
    R(3) = R(31) |R(31);
    R(5) = R(30) & 0xFFFFu;
    R(6) = R(29) & 0xFFFFu;
    R(7) = R(28) & 0xFFFFu;
    R(8) = R(27) & 0xFFFFu;
    R(4) = (0 + 0);
    R(9) = (0 + 0);
    R(10) = (0 + 4);
    GM_CALLV(0x80077C78u, 0x80077EB0u, 0);
    R(5) = (R(31) + 0x90000u);
    R(4) = (0 + 1);
    st32(base, (R(5) + 2624), R(3));
    R(3) = R(31) |R(31);
    GM_CALLV(0x80077C8Cu, 0x80077980u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077CC0; }
    R(3) = R(31) |R(31);
    R(5) = R(30) & 0xFFFFu;
    R(6) = R(29) & 0xFFFFu;
    R(7) = R(28) & 0xFFFFu;
    R(8) = R(27) & 0xFFFFu;
    R(4) = (0 + 1);
    R(9) = (0 + 127);
    R(10) = (0 + 3);
    GM_CALLV(0x80077CB8u, 0x80077EB0u, 0);
    R(4) = (R(31) + 0x90000u);
    st32(base, (R(4) + 2628), R(3));
L_80077CC0:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 2);
    GM_CALLV(0x80077CCCu, 0x80077980u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077D60; }
    R(3) = R(31) |R(31);
    R(5) = R(30) & 0xFFFFu;
    R(6) = R(29) & 0xFFFFu;
    R(7) = R(28) & 0xFFFFu;
    R(8) = R(27) & 0xFFFFu;
    R(4) = (0 + 2);
    R(9) = (0 + 3);
    R(10) = (0 + -1);
    GM_CALLV(0x80077CF8u, 0x80077EB0u, 0);
    R(4) = (R(31) + 0x90000u);
    R(5) = (0 + 4);
    st32(base, (R(4) + 2632), R(3));
    R(3) = (0 + 40);
    R(4) = ld32(base, (R(13) + -22708));
    GM_CALLV(0x80077D10u, 0x802B9240u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80077D48; }
    GM_CALLV(0x80077D20u, 0x8016A010u, 0);
    R(4) = (0 + 0x80300000u);
    R(3) = (R(30) + 8);
    R(4) = (R(4) + -7032);
    st32(base, (R(30) + 0), R(4));
    GM_CALLV(0x80077D34u, 0x8016A5E0u, 0);
    R(0) = (0 + 0);
    st32(base, (R(30) + 36), R(0));
    R(3) = (0 + 0x80310000u);
    R(3) = (R(3) + -480);
    st32(base, (R(30) + 0), R(3));
L_80077D48:;
    R(4) = (R(31) + 0x90000u);
    R(3) = R(30) |R(30);
    st32(base, (R(4) + 2636), R(30));
    R(4) = ld32(base, (R(4) + 2632));
    R(5) = ld32(base, (R(13) + -22708));
    GM_CALLV(0x80077D60u, 0x800833E0u, 0);
L_80077D60:;
    R(11) = (f + 80);
    R(0) = lr;
}

/* fn_80077D80 (fn_80077D80, 168 bytes) */
static void bg_m_77d80(GM_CTX) {
    GM_FN(0x80077D80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (R(3) + 0x90000u);
    R(29) = R(3) |R(3);
    R(3) = ld32(base, (R(4) + 2636));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077DC0; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x80077DC0u, ctx->ctr, 0);
L_80077DC0:;
    R(3) = (R(29) + 0x90000u);
    R(31) = (0 + 0);
    st32(base, (R(3) + 2636), R(31));
    R(30) = (0 + 0);
L_80077DD0:;
    R(3) = (R(29) + 0x90000u);
    R(3) = ld32(base, (R(3) + 2624));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077DF4; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x80077DF4u, ctx->ctr, 0);
L_80077DF4:;
    R(30) = (R(30) + 1);
    R(3) = (R(29) + 0x90000u);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 3);
    st32(base, (R(3) + 2624), R(31));
    R(29) = (R(29) + 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80077DD0; }
    R(0) = lr;
}

/* fn_80077E30 (fn_80077E30, 120 bytes) */
static void bg_m_77e30(GM_CTX) {
    GM_FN(0x80077E30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80077E8C; }
    if ((CR_BIT(ctx, 2))) { goto L_80077E7C; }
    R(4) = (0 + -1);
    R(3) = (R(3) + 8);
    GM_CALLV(0x80077E64u, 0x8016A630u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077E7C; }
    if ((CR_BIT(ctx, 2))) { goto L_80077E7C; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x80077E7Cu, 0x8016A030u, 0);
L_80077E7C:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80077E8C; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80077E8Cu, 0x802B9280u, 0);
L_80077E8C:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_80077EB0 (fn_80077EB0, 924 bytes) */
static void bg_m_77eb0(GM_CTX) {
    GM_FN(0x80077EB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 128);
    R(26) = ld32(base, (R(13) + -21688));
    R(22) = R(4) |R(4);
    R(27) = ld32(base, (R(13) + -22672));
    R(25) = (0 + 0x80310000u);
    R(4) = ld8(base, (R(26) + 4622));
    R(21) = R(3) |R(3);
    R(23) = R(5) |R(5);
    R(24) = R(6) |R(6);
    R(20) = R(7) |R(7);
    R(31) = R(8) |R(8);
    R(29) = R(9) |R(9);
    R(28) = R(10) |R(10);
    R(3) = R(27) |R(27);
    R(5) = R(22) |R(22);
    R(25) = (R(25) + -3104);
    R(30) = (0 + 0);
    GM_CALLV(0x80077F10u, 0x80081850u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80078228; }
    R(4) = ld32(base, (R(13) + -22708));
    R(3) = (0 + 68);
    R(5) = (0 + 4);
    GM_CALLV(0x80077F28u, 0x802B9240u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80077F3C; }
    GM_CALLV(0x80077F38u, 0x80082310u, 0);
    R(30) = R(3) |R(3);
L_80077F3C:;
    R(0) = R(22) & 0xFFFFu;
    st32(base, (f + 8), R(0));
    R(3) = (0 + 0x80370000u);
    R(4) = R(23) |R(23);
    R(10) = ld32(base, (R(3) + 31816));
    R(3) = R(30) |R(30);
    R(5) = R(24) |R(24);
    R(6) = R(20) |R(20);
    R(7) = R(31) |R(31);
    R(8) = R(29) |R(29);
    R(9) = R(28) |R(28);
    GM_CALLV(0x80077F6Cu, 0x80082410u, 0);
    R(4) = ld8(base, (R(26) + 4622));
    R(3) = R(27) |R(27);
    R(29) = (0 + 0);
    R(5) = (0 + 1);
    GM_CALLV(0x80077F80u, 0x800813F0u, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(26) = R(3) |R(3);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80077FCC; }
    R(4) = (R(25) + 36);
    GM_CALLV(0x80077F98u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077FC8; }
    R(3) = R(26) |R(26);
    R(4) = (R(25) + 48);
    GM_CALLV(0x80077FACu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80077FC8; }
    R(3) = R(26) |R(26);
    R(4) = (R(25) + 60);
    GM_CALLV(0x80077FC0u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80077FCC; }
L_80077FC8:;
    R(29) = (0 + 1);
L_80077FCC:;
    { uint32_t ea_ = (R(2) + -29536); ctx->f[31].u = ld64(base, ea_); }
    R(28) = (0 + 0);
    R(31) = (0 + 0x43300000u);
    goto L_80078218;
L_80077FDC:;
    R(0) = ld16(base, (R(30) + 48));
    R(27) = (0 + 0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80078214; }
    R(0) = R(28) & 0xFFFFu;
    R(0) = R(0) + R(24);
    R(25) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    goto L_80078204;
L_80077FFC:;
    R(0) = R(27) & 0xFFFFu;
    R(3) = R(21) |R(21);
    R(0) = R(0) + R(23);
    R(5) = R(25) & 0xFFFFu;
    R(26) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    R(6) = R(22) & 0xFFu;
    R(4) = rotl32(R(0), 4) & 0xFFF0u;
    R(7) = (0 + 0);
    GM_CALLV(0x80078020u, 0x800775A0u, 0);
    R(0) = R(3) & 0xFFFFu;
    R(6) = R(3) |R(3);
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((!CR_BIT(ctx, 2))) { goto L_80078034; }
    R(6) = (0 + 0);
L_80078034:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800781EC; }
    R(3) = (R(6) + 0x10000u);
    R(0) = (R(3) + -416);
    R(0) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((!CR_BIT(ctx, 1))) { goto L_80078070; }
    R(0) = (R(3) + -432);
    R(0) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 1))) { goto L_80078070; }
    R(0) = (R(3) + -448);
    R(0) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((CR_BIT(ctx, 1))) { goto L_800781EC; }
L_80078070:;
    R(0) = (R(25) + 16);
    st32(base, (f + 68), R(0));
    R(4) = (R(26) + 8);
    R(5) = (R(6) + 0x10000u);
    st32(base, (f + 64), R(31));
    R(0) = (R(5) + -416);
    R(0) = R(0) & 0xFFFFu;
    R(7) = (R(21) + 0x90000u);
    { uint32_t ea_ = (f + 64); ctx->f[0].u = ld64(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    st32(base, (f + 60), R(4));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[31].d);
    R(3) = ld32(base, (R(7) + -2952));
    st32(base, (f + 56), R(31));
    R(4) = ld32(base, (R(7) + -2948));
    { uint32_t ea_ = (f + 56); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[31].d);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[1].d); }
    if ((!CR_BIT(ctx, 1))) { goto L_800780D4; }
    R(0) = (R(5) + -448);
    R(0) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((CR_BIT(ctx, 1))) { goto L_8007814C; }
L_800780D4:;
    R(5) = (R(6) + 0x10000u);
    R(0) = (R(5) + -416);
    R(0) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((CR_BIT(ctx, 1))) { goto L_800780F4; }
    R(0) = (R(6) + -416);
    st8(base, (f + 48), R(0));
    goto L_800780FC;
L_800780F4:;
    R(0) = (R(6) + -447);
    st8(base, (f + 48), R(0));
L_800780FC:;
    R(0) = ((int32_t)R(3) * 12);
    R(5) = ld32(base, (f + 40));
    st32(base, (f + 28), R(5));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 100);
    R(5) = ld32(base, (f + 44));
    R(7) = R(21) + R(0);
    st32(base, (f + 32), R(5));
    R(5) = (R(7) + 0x90000u);
    { uint32_t ea_ = (f + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = ld32(base, (f + 48));
    st32(base, (f + 36), R(0));
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + -2944); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld8(base, (f + 36));
    { uint32_t ea_ = (R(5) + -2940); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(5) + -2936), R(0));
    if ((!CR_BIT(ctx, 0))) { goto L_80078144; }
    R(3) = (R(3) + 1);
L_80078144:;
    R(5) = (R(21) + 0x90000u);
    st32(base, (R(5) + -2952), R(3));
L_8007814C:;
    R(5) = (R(6) + 0x10000u);
    R(0) = (R(5) + -432);
    R(0) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 1))) { goto L_80078170; }
    R(0) = (R(5) + -448);
    R(0) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((CR_BIT(ctx, 1))) { goto L_800781E8; }
L_80078170:;
    R(5) = (R(6) + 0x10000u);
    R(0) = (R(5) + -432);
    R(0) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((CR_BIT(ctx, 1))) { goto L_80078190; }
    R(0) = (R(6) + -432);
    st8(base, (f + 48), R(0));
    goto L_80078198;
L_80078190:;
    R(0) = (R(6) + -448);
    st8(base, (f + 48), R(0));
L_80078198:;
    R(0) = ((int32_t)R(4) * 12);
    R(5) = ld32(base, (f + 40));
    st32(base, (f + 16), R(5));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 100);
    R(3) = ld32(base, (f + 44));
    R(5) = R(21) + R(0);
    st32(base, (f + 20), R(3));
    R(3) = (R(5) + 0x90000u);
    { uint32_t ea_ = (f + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = ld32(base, (f + 48));
    st32(base, (f + 24), R(0));
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -1744); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld8(base, (f + 24));
    { uint32_t ea_ = (R(3) + -1740); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + -1736), R(0));
    if ((!CR_BIT(ctx, 0))) { goto L_800781E0; }
    R(4) = (R(4) + 1);
L_800781E0:;
    R(3) = (R(21) + 0x90000u);
    st32(base, (R(3) + -2948), R(4));
L_800781E8:;
    R(6) = (0 + 0);
L_800781EC:;
    R(3) = R(30) |R(30);
    R(4) = R(27) & 0xFFFFu;
    R(5) = R(28) & 0xFFFFu;
    R(6) = R(6) & 0xFFFFu;
    GM_CALLV(0x80078200u, 0x800826C0u, 0);
    R(27) = (R(27) + 1);
L_80078204:;
    R(0) = ld16(base, (R(30) + 48));
    R(3) = R(27) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(3), R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80077FFC; }
L_80078214:;
    R(28) = (R(28) + 1);
L_80078218:;
    R(0) = ld16(base, (R(30) + 50));
    R(3) = R(28) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(3), R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80077FDC; }
L_80078228:;
    R(3) = R(30) |R(30);
    R(11) = (f + 128);
    R(0) = lr;
}

/* fn_80078300 (fn_80078300, 272 bytes) */
static void bg_m_78300(GM_CTX) {
    GM_FN(0x80078300); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    { uint32_t ea_ = (R(2) + -29536); ctx->f[30].u = ld64(base, ea_); }
    R(27) = R(3) |R(3);
    { uint32_t ea_ = (R(2) + -29520); ctx->f[31].u = ld64(base, ea_); }
    R(29) = (R(3) + 120);
    R(28) = (0 + 0);
    R(31) = (0 + 0x43300000u);
L_8007833C:;
    R(0) = ld32(base, (R(29) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800783D8; }
    { uint32_t a_ = R(0); R(0) = a_ + 0xFFFFFFFFu; ctx->xer_ca = R(0) < a_; }
    CR0(ctx, R(0));
    st32(base, (R(29) + 8), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800783D8; }
    R(0) = ld32(base, (R(29) + 12));
    R(3) = R(27) |R(27);
    R(4) = ld16(base, (R(29) + 0));
    R(5) = ld16(base, (R(29) + 2));
    R(7) = R(0) & 0xFFFFu;
    R(6) = ld32(base, (R(29) + 4));
    GM_CALLV(0x80078370u, 0x80077860u, 0);
    R(5) = ld32(base, (R(27) + 116));
    R(3) = (f + 8);
    st32(base, (f + 24), R(31));
    R(4) = (f + 16);
    R(0) = (R(5) + -1);
    st32(base, (R(27) + 116), R(0));
    R(0) = ld16(base, (R(29) + 0));
    st32(base, (f + 28), R(0));
    R(30) = ld32(base, (R(13) + -22816));
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    st32(base, (f + 32), R(31));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[30].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld16(base, (R(29) + 2));
    R(0) = -(int32_t)R(0);
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 36), R(0));
    { uint32_t ea_ = (f + 32); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[31].d);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x800783C4u, 0x8006A3F0u, 0);
    R(3) = R(30) |R(30);
    R(5) = (f + 8);
    R(4) = (0 + 569);
    R(6) = (0 + 0);
    GM_CALLV(0x800783D8u, 0x80198C30u, 0);
L_800783D8:;
    R(28) = (R(28) + 1);
    R(29) = (R(29) + 16);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 256);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8007833C; }
    R(11) = (f + 64);
    R(0) = lr;
}

/* setWaterInWave__5dBg_cFffUc (setWaterInWave__5dBg_cFffUc, 88 bytes) */
static void bg_setWaterInWave__5dBg_cFffUc_78410(GM_CTX) {
    R(0) = (0 + 20);
    R(8) = (0 + 0);
    ctx->ctr = R(0);
    R(0) = R(0) | 0x0u;
L_80078420:;
    R(5) = (R(8) + 0x90000u);
    R(6) = (R(5) + 484);
    R(0) = ld8(base, (R(3) + R(6)));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007845C; }
    R(5) = (0 + 1);
    R(0) = (R(3) + 0x90000u);
    st8(base, (R(3) + R(6)), R(5));
    R(7) = rotl32(R(8), 2) & 0xFFFFFFFCu;
    R(5) = R(0) + R(7);
    R(3) = R(0) + R(8);
    { uint32_t ea_ = (R(5) + 304); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(5) + 384); stfs(base, ea_, ctx->f[2].d); }
    st8(base, (R(3) + 464), R(4));
    return;
L_8007845C:;
    R(8) = (R(8) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80078420; }
}

/* fn_800784D0 (fn_800784D0, 64 bytes) */
static void bg_m_784d0(GM_CTX) {
    R(5) = ld32(base, (R(13) + -22276));
    R(4) = (R(3) + 0x90000u);
    R(0) = (0 + 0);
    st8(base, (R(4) + 2728), R(0));
    R(0) = ld8(base, (R(5) + 896));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800784F4; }
    R(0) = (0 + 1);
    st8(base, (R(4) + 2728), R(0));
L_800784F4:;
    R(0) = ld32(base, (R(13) + -22272));
    R(0) = R(0) & 0x10u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) return;
    R(3) = (R(3) + 0x90000u);
    R(0) = (0 + 1);
    st8(base, (R(3) + 2728), R(0));
}

/* getTileRendererList__7dBgGm_cFi (getTileRendererList__7dBgGm_cFi, 24 bytes) */
static void bg_getTileRendererList__7dBgGm_cFi_78520(GM_CTX) {
    R(3) = (R(3) + 0x90000u);
    R(0) = rotl32(R(4), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(0);
    R(3) = ld32(base, (R(3) + 2624));
    R(3) = (R(3) + 56);
}

/* fn_80078780 (fn_80078780, 124 bytes) */
static void bg_m_78780(GM_CTX) {
    GM_FN(0x80078780); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = R(3) |R(3);
    R(5) = ld32(base, (R(13) + -21688));
    R(3) = ld32(base, (R(13) + -22504));
    R(0) = ld8(base, (R(5) + 4622));
    R(0) = ((int32_t)R(0) * 944);
    R(31) = R(3) + R(0);
    R(0) = ld32(base, (R(31) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800787B8; }
    goto L_800787BC;
L_800787B8:;
    R(31) = (0 + 0);
L_800787BC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800787C4u, 0x8008E4D0u, 0);
    R(0) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x800787D4u, 0x8008E500u, 0);
    R(0) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x800787E4u, 0x8008E310u, 0);
    R(0) = lr;
    R(3) = ld16(base, (R(3) + 18));
}

/* fn_80078800 (fn_80078800, 48 bytes) */
static void bg_m_78800(GM_CTX) {
    R(3) = ld32(base, (R(13) + -21688));
    R(4) = ld32(base, (R(13) + -22504));
    R(0) = ld8(base, (R(3) + 4622));
    R(0) = ((int32_t)R(0) * 944);
    R(3) = R(4) + R(0);
    R(0) = ld32(base, (R(3) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80078824; }
    goto L_80078828;
L_80078824:;
    R(3) = (0 + 0);
L_80078828:;
    R(3) = ld32(base, (R(3) + 164));
}

/* fn_80078860 (fn_80078860, 316 bytes) */
static void bg_m_78860(GM_CTX) {
    R(5) = (R(3) + 0x90000u);
    ctx->f[0].u = ctx->f[1].u;
    R(0) = ld8(base, (R(5) + 276));
    cr_cmp_u(ctx, 0, R(0), 0x17u);
    if ((CR_BIT(ctx, 1))) { goto L_80078984; }
    R(4) = (0 + 0x80310000u);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(4) = (R(4) + -3028);
    R(4) = ld32(base, (R(4) + R(0)));
    ctx->ctr = R(4);
    { switch (ctx->ctr) { case 0x8007888Cu: goto L_8007888C; case 0x80078894u: goto L_80078894; case 0x8007889Cu: goto L_8007889C; case 0x800788A4u: goto L_800788A4; case 0x800788ACu: goto L_800788AC; case 0x800788BCu: goto L_800788BC; case 0x800788C8u: goto L_800788C8; case 0x800788D0u: goto L_800788D0; case 0x800788DCu: goto L_800788DC; case 0x800788E4u: goto L_800788E4; case 0x800788ECu: goto L_800788EC; case 0x800788F8u: goto L_800788F8; case 0x80078904u: goto L_80078904; case 0x80078910u: goto L_80078910; case 0x8007891Cu: goto L_8007891C; case 0x80078928u: goto L_80078928; case 0x80078934u: goto L_80078934; case 0x80078940u: goto L_80078940; case 0x8007894Cu: goto L_8007894C; case 0x80078958u: goto L_80078958; case 0x80078964u: goto L_80078964; case 0x80078970u: goto L_80078970; case 0x8007897Cu: goto L_8007897C; case 0x80078984u: goto L_80078984; default: rt_fatal("80078860: jump table target %08X", ctx->ctr); return; } }
L_8007888C:;
    { uint32_t ea_ = (R(2) + -29500); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_80078894:;
    { uint32_t ea_ = (R(2) + -29496); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_8007889C:;
    { uint32_t ea_ = (R(2) + -29492); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_800788A4:;
    { uint32_t ea_ = (R(2) + -29488); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_800788AC:;
    { uint32_t ea_ = (R(5) + 40); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[2].d);
    goto L_80078984;
L_800788BC:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29508); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_800788C8:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_800788D0:;
    { uint32_t ea_ = (R(2) + -29508); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_800788DC:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_800788E4:;
    { uint32_t ea_ = (R(2) + -29484); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_800788EC:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[1].u;
    goto L_80078984;
L_800788F8:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29484); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_80078904:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29500); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_80078910:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29496); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_8007891C:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29492); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_80078928:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29488); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_80078934:;
    { uint32_t ea_ = (R(2) + -29480); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[1].u;
    goto L_80078984;
L_80078940:;
    { uint32_t ea_ = (R(2) + -29480); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_8007894C:;
    { uint32_t ea_ = (R(2) + -29480); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29484); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_80078958:;
    { uint32_t ea_ = (R(2) + -29480); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29500); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_80078964:;
    { uint32_t ea_ = (R(2) + -29480); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29496); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_80078970:;
    { uint32_t ea_ = (R(2) + -29480); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29492); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    goto L_80078984;
L_8007897C:;
    { uint32_t ea_ = (R(2) + -29480); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29488); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
L_80078984:;
    R(3) = (R(3) + 0x90000u);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 272); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
}

/* fn_800789A0 (fn_800789A0, 200 bytes) */
static void bg_m_789a0(GM_CTX) {
    GM_FN(0x800789A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (R(3) + 0x90000u);
    R(31) = R(3) |R(3);
    R(0) = ld8(base, (R(4) + 254));
    { uint32_t ea_ = (R(4) + -412); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_80078A38; }
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_80078A38; }
    { uint32_t ea_ = (R(4) + 12); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    GM_CALLV(0x800789F0u, 0x80079060u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80078A38; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -21908); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80078A14u, 0x80079060u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[30].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[31].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[30].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d + ctx->f[0].d);
L_80078A38:;
    ctx->f[1].u = ctx->f[29].u;
    R(0) = lr;
}

/* getLeftLimit__5dBg_cFv (getLeftLimit__5dBg_cFv, 200 bytes) */
static void bg_getLeftLimit__5dBg_cFv_78a70(GM_CTX) {
    GM_FN(0x80078A70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (R(3) + 0x90000u);
    R(31) = R(3) |R(3);
    R(0) = ld8(base, (R(4) + 254));
    { uint32_t ea_ = (R(4) + 48); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_80078B08; }
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_80078B08; }
    { uint32_t ea_ = (R(4) + 12); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    GM_CALLV(0x80078AC0u, 0x80079060u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80078B08; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -21908); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80078AE4u, 0x80079060u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[30].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[31].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[30].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d + ctx->f[0].d);
L_80078B08:;
    ctx->f[1].u = ctx->f[29].u;
    R(0) = lr;
}

/* fn_80078B40 (fn_80078B40, 200 bytes) */
static void bg_m_78b40(GM_CTX) {
    GM_FN(0x80078B40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (R(3) + 0x90000u);
    R(31) = R(3) |R(3);
    R(0) = ld8(base, (R(4) + 254));
    { uint32_t ea_ = (R(4) + -408); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_80078BD8; }
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_80078BD8; }
    { uint32_t ea_ = (R(4) + 12); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    GM_CALLV(0x80078B90u, 0x80079060u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80078BD8; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -21908); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80078BB4u, 0x80079060u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[30].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[31].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[30].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d - ctx->f[0].d);
L_80078BD8:;
    ctx->f[1].u = ctx->f[29].u;
    R(0) = lr;
}

/* getRightLimit__5dBg_cFv (getRightLimit__5dBg_cFv, 200 bytes) */
static void bg_getRightLimit__5dBg_cFv_78c10(GM_CTX) {
    GM_FN(0x80078C10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (R(3) + 0x90000u);
    R(31) = R(3) |R(3);
    R(0) = ld8(base, (R(4) + 254));
    { uint32_t ea_ = (R(4) + 52); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_80078CA8; }
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_80078CA8; }
    { uint32_t ea_ = (R(4) + 12); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    GM_CALLV(0x80078C60u, 0x80079060u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80078CA8; }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(13) + -21908); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80078C84u, 0x80079060u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[30].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[31].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[30].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d - ctx->f[0].d);
L_80078CA8:;
    ctx->f[1].u = ctx->f[29].u;
    R(0) = lr;
}

/* fn_80078CE0 (fn_80078CE0, 12 bytes) */
static void bg_m_78ce0(GM_CTX) {
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(3) + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_80078CF0 (fn_80078CF0, 12 bytes) */
static void bg_m_78cf0(GM_CTX) {
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(3) + 80); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
}

/* fn_80078D00 (fn_80078D00, 432 bytes) */
static void bg_m_78d00(GM_CTX) {
    GM_FN(0x80078D00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 224);
    R(6) = (0 + 0x802F0000u);
    R(4) = (R(3) + 0x90000u);
    R(6) = (R(6) + -2472);
    R(16) = ld8(base, (R(4) + 254));
    R(5) = (R(6) + 88);
    R(17) = ld32(base, (R(6) + 0));
    R(15) = ld32(base, (R(5) + 12));
    R(8) = (R(6) + 0);
    st32(base, (f + 136), R(15));
    R(7) = (R(6) + 48);
    R(15) = ld32(base, (R(5) + 16));
    cr_cmp_u(ctx, 0, R(16), 0x1u);
    R(0) = ld32(base, (R(5) + 4));
    st32(base, (f + 124), R(15));
    R(28) = ld32(base, (R(6) + 48));
    R(15) = ld32(base, (R(5) + 20));
    st32(base, (f + 128), R(15));
    R(15) = ld32(base, (R(5) + 24));
    R(14) = ld32(base, (R(5) + 8));
    st32(base, (f + 12), R(0));
    R(0) = ld32(base, (f + 136));
    st32(base, (f + 20), R(0));
    R(0) = ld32(base, (f + 124));
    R(18) = ld32(base, (R(8) + 4));
    R(19) = ld32(base, (R(8) + 8));
    R(20) = ld32(base, (R(8) + 12));
    R(21) = ld32(base, (R(8) + 16));
    R(22) = ld32(base, (R(8) + 20));
    R(23) = ld32(base, (R(8) + 24));
    R(24) = ld32(base, (R(8) + 28));
    R(25) = ld32(base, (R(8) + 32));
    R(26) = ld32(base, (R(8) + 36));
    R(27) = ld32(base, (R(8) + 40));
    R(29) = ld32(base, (R(7) + 4));
    R(30) = ld32(base, (R(7) + 8));
    R(31) = ld32(base, (R(7) + 12));
    R(12) = ld32(base, (R(7) + 16));
    R(11) = ld32(base, (R(7) + 20));
    R(10) = ld32(base, (R(7) + 24));
    R(9) = ld32(base, (R(7) + 28));
    R(8) = ld32(base, (R(7) + 32));
    R(7) = ld32(base, (R(7) + 36));
    R(6) = ld32(base, (R(6) + 88));
    R(5) = ld32(base, (R(5) + 28));
    st32(base, (f + 24), R(0));
    R(0) = ld32(base, (f + 128));
    st32(base, (f + 28), R(0));
    R(0) = R(15) |R(15);
    st32(base, (f + 132), R(15));
    st32(base, (f + 80), R(17));
    st32(base, (f + 84), R(18));
    st32(base, (f + 88), R(19));
    st32(base, (f + 92), R(20));
    st32(base, (f + 96), R(21));
    st32(base, (f + 100), R(22));
    st32(base, (f + 104), R(23));
    st32(base, (f + 108), R(24));
    st32(base, (f + 112), R(25));
    st32(base, (f + 116), R(26));
    st32(base, (f + 120), R(27));
    st32(base, (f + 40), R(28));
    st32(base, (f + 44), R(29));
    st32(base, (f + 48), R(30));
    st32(base, (f + 52), R(31));
    st32(base, (f + 56), R(12));
    st32(base, (f + 60), R(11));
    st32(base, (f + 64), R(10));
    st32(base, (f + 68), R(9));
    st32(base, (f + 72), R(8));
    st32(base, (f + 76), R(7));
    st32(base, (f + 8), R(6));
    st32(base, (f + 16), R(14));
    st32(base, (f + 32), R(0));
    st32(base, (f + 36), R(5));
    if ((!CR_BIT(ctx, 1))) { goto L_80078E5C; }
    R(0) = (R(16) + 250);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_80078E5C; }
    cr_cmp_u(ctx, 0, R(16), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_80078E74; }
    goto L_80078E88;
L_80078E5C:;
    R(4) = (R(3) + 0x90000u);
    R(3) = (f + 80);
    R(0) = ld8(base, (R(4) + 255));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_80078E98;
L_80078E74:;
    R(0) = ld8(base, (R(4) + 255));
    R(3) = (f + 8);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_80078E98;
L_80078E88:;
    R(0) = ld8(base, (R(4) + 255));
    R(3) = (f + 40);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_80078E98:;
    R(11) = (f + 224);
    R(0) = lr;
}

/* fn_80078EB0 (fn_80078EB0, 52 bytes) */
static void bg_m_78eb0(GM_CTX) {
    GM_FN(0x80078EB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x80078EC8u, 0x80078D00u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80078ED0u, 0x80078860u, 0);
    R(0) = lr;
}

/* fn_80079020 (fn_80079020, 52 bytes) */
static void bg_m_79020(GM_CTX) {
    GM_FN(0x80079020); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x80079038u, 0x80078EF0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80079040u, 0x80078860u, 0);
    R(0) = lr;
}

/* fn_80079060 (fn_80079060, 356 bytes) */
static void bg_m_79060(GM_CTX) {
    GM_FN(0x80079060); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 144);
    R(4) = (R(3) + 0x90000u);
    R(5) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(5) + -2272; R(20) = ld32(base, ea_); R(5) = ea_; }
    R(12) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(12) + -2224; R(11) = ld32(base, ea_); R(12) = ea_; }
    R(31) = R(3) |R(3);
    R(19) = ld8(base, (R(4) + 254));
    R(21) = ld32(base, (R(5) + 4));
    R(22) = ld32(base, (R(5) + 8));
    cr_cmp_u(ctx, 0, R(19), 0x1u);
    R(23) = ld32(base, (R(5) + 12));
    R(24) = ld32(base, (R(5) + 16));
    R(25) = ld32(base, (R(5) + 20));
    R(26) = ld32(base, (R(5) + 24));
    R(27) = ld32(base, (R(5) + 28));
    R(28) = ld32(base, (R(5) + 32));
    R(29) = ld32(base, (R(5) + 36));
    R(30) = ld32(base, (R(5) + 40));
    R(10) = ld32(base, (R(12) + 4));
    R(9) = ld32(base, (R(12) + 8));
    R(8) = ld32(base, (R(12) + 12));
    R(7) = ld32(base, (R(12) + 16));
    R(6) = ld32(base, (R(12) + 20));
    R(5) = ld32(base, (R(12) + 24));
    R(0) = ld32(base, (R(12) + 28));
    st32(base, (f + 44), R(21));
    st32(base, (f + 48), R(22));
    st32(base, (f + 52), R(23));
    st32(base, (f + 56), R(24));
    st32(base, (f + 60), R(25));
    st32(base, (f + 64), R(26));
    st32(base, (f + 68), R(27));
    st32(base, (f + 72), R(28));
    st32(base, (f + 76), R(29));
    st32(base, (f + 80), R(30));
    st32(base, (f + 8), R(11));
    st32(base, (f + 12), R(10));
    st32(base, (f + 16), R(9));
    st32(base, (f + 20), R(8));
    st32(base, (f + 24), R(7));
    st32(base, (f + 28), R(6));
    st32(base, (f + 32), R(5));
    st32(base, (f + 36), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_80079144; }
    R(0) = (R(19) + 250);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_80079144; }
    cr_cmp_u(ctx, 0, R(19), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_8007915C; }
    goto L_80079170;
L_80079144:;
    R(4) = (R(3) + 0x90000u);
    R(3) = (f + 40);
    R(0) = ld8(base, (R(4) + 255));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_80079174;
L_8007915C:;
    R(0) = ld8(base, (R(4) + 255));
    R(3) = (f + 8);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_80079174;
L_80079170:;
    GM_CALLV(0x80079174u, 0x80078D00u, 0);
L_80079174:;
    { uint32_t ea_ = (R(13) + -21908); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -352); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[3].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80079190; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d / ctx->f[2].d);
L_80079190:;
    { uint32_t ea_ = (R(13) + -21904); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -348); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[3].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800791AC; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d / ctx->f[2].d);
L_800791AC:;
    R(11) = (f + 144);
    R(0) = lr;
}

/* fn_800791D0 (fn_800791D0, 128 bytes) */
static void bg_m_791d0(GM_CTX) {
    GM_FN(0x800791D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800791E8u, 0x80079060u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x800791F0u, 0x80078860u, 0);
    { uint32_t ea_ = (R(13) + -21908); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -352); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[3].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007920C; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d / ctx->f[2].d);
L_8007920C:;
    { uint32_t ea_ = (R(13) + -21904); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -348); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[3].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80079228; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d / ctx->f[2].d);
L_80079228:;
    { uint32_t ea_ = (R(2) + -29472); ctx->f[0].u = ld64(base, ea_); }
    R(3) = (R(31) + 0x90000u);
    ctx->f[0].d = ctx->f[0].d / ctx->f[1].d;
    ctx->f[0].d = frsp(ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_80079250 (fn_80079250, 292 bytes) */
static void bg_m_79250(GM_CTX) {
    GM_FN(0x80079250); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 144);
    R(4) = (R(3) + 0x90000u);
    R(5) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(5) + -2192; R(21) = ld32(base, ea_); R(5) = ea_; }
    R(12) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(12) + -2144; R(11) = ld32(base, ea_); R(12) = ea_; }
    R(20) = ld8(base, (R(4) + 254));
    R(22) = ld32(base, (R(5) + 4));
    R(23) = ld32(base, (R(5) + 8));
    cr_cmp_u(ctx, 0, R(20), 0x1u);
    R(24) = ld32(base, (R(5) + 12));
    R(25) = ld32(base, (R(5) + 16));
    R(26) = ld32(base, (R(5) + 20));
    R(27) = ld32(base, (R(5) + 24));
    R(28) = ld32(base, (R(5) + 28));
    R(29) = ld32(base, (R(5) + 32));
    R(30) = ld32(base, (R(5) + 36));
    R(31) = ld32(base, (R(5) + 40));
    R(10) = ld32(base, (R(12) + 4));
    R(9) = ld32(base, (R(12) + 8));
    R(8) = ld32(base, (R(12) + 12));
    R(7) = ld32(base, (R(12) + 16));
    R(6) = ld32(base, (R(12) + 20));
    R(5) = ld32(base, (R(12) + 24));
    R(0) = ld32(base, (R(12) + 28));
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st32(base, (f + 44), R(22));
    st32(base, (f + 48), R(23));
    st32(base, (f + 52), R(24));
    st32(base, (f + 56), R(25));
    st32(base, (f + 60), R(26));
    st32(base, (f + 64), R(27));
    st32(base, (f + 68), R(28));
    st32(base, (f + 72), R(29));
    st32(base, (f + 76), R(30));
    st32(base, (f + 80), R(31));
    st32(base, (f + 8), R(11));
    st32(base, (f + 12), R(10));
    st32(base, (f + 16), R(9));
    st32(base, (f + 20), R(8));
    st32(base, (f + 24), R(7));
    st32(base, (f + 28), R(6));
    st32(base, (f + 32), R(5));
    st32(base, (f + 36), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_80079334; }
    R(0) = (R(20) + 250);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_80079334; }
    cr_cmp_u(ctx, 0, R(20), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_8007934C; }
    goto L_8007935C;
L_80079334:;
    R(4) = (R(3) + 0x90000u);
    R(3) = (f + 40);
    R(0) = ld8(base, (R(4) + 255));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_8007935C;
L_8007934C:;
    R(0) = ld8(base, (R(4) + 255));
    R(3) = (f + 8);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_8007935C:;
    R(11) = (f + 144);
    R(0) = lr;
}

/* fn_80079380 (fn_80079380, 292 bytes) */
static void bg_m_79380(GM_CTX) {
    GM_FN(0x80079380); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 144);
    R(4) = (R(3) + 0x90000u);
    R(5) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(5) + -2112; R(21) = ld32(base, ea_); R(5) = ea_; }
    R(12) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(12) + -2064; R(11) = ld32(base, ea_); R(12) = ea_; }
    R(20) = ld8(base, (R(4) + 254));
    R(22) = ld32(base, (R(5) + 4));
    R(23) = ld32(base, (R(5) + 8));
    cr_cmp_u(ctx, 0, R(20), 0x1u);
    R(24) = ld32(base, (R(5) + 12));
    R(25) = ld32(base, (R(5) + 16));
    R(26) = ld32(base, (R(5) + 20));
    R(27) = ld32(base, (R(5) + 24));
    R(28) = ld32(base, (R(5) + 28));
    R(29) = ld32(base, (R(5) + 32));
    R(30) = ld32(base, (R(5) + 36));
    R(31) = ld32(base, (R(5) + 40));
    R(10) = ld32(base, (R(12) + 4));
    R(9) = ld32(base, (R(12) + 8));
    R(8) = ld32(base, (R(12) + 12));
    R(7) = ld32(base, (R(12) + 16));
    R(6) = ld32(base, (R(12) + 20));
    R(5) = ld32(base, (R(12) + 24));
    R(0) = ld32(base, (R(12) + 28));
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st32(base, (f + 44), R(22));
    st32(base, (f + 48), R(23));
    st32(base, (f + 52), R(24));
    st32(base, (f + 56), R(25));
    st32(base, (f + 60), R(26));
    st32(base, (f + 64), R(27));
    st32(base, (f + 68), R(28));
    st32(base, (f + 72), R(29));
    st32(base, (f + 76), R(30));
    st32(base, (f + 80), R(31));
    st32(base, (f + 8), R(11));
    st32(base, (f + 12), R(10));
    st32(base, (f + 16), R(9));
    st32(base, (f + 20), R(8));
    st32(base, (f + 24), R(7));
    st32(base, (f + 28), R(6));
    st32(base, (f + 32), R(5));
    st32(base, (f + 36), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_80079464; }
    R(0) = (R(20) + 250);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_80079464; }
    cr_cmp_u(ctx, 0, R(20), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_8007947C; }
    goto L_8007948C;
L_80079464:;
    R(4) = (R(3) + 0x90000u);
    R(3) = (f + 40);
    R(0) = ld8(base, (R(4) + 255));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_8007948C;
L_8007947C:;
    R(0) = ld8(base, (R(4) + 255));
    R(3) = (f + 8);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_8007948C:;
    R(11) = (f + 144);
    R(0) = lr;
}

/* fn_800794B0 (fn_800794B0, 292 bytes) */
static void bg_m_794b0(GM_CTX) {
    GM_FN(0x800794B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 144);
    R(4) = (R(3) + 0x90000u);
    R(5) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(5) + -2032; R(21) = ld32(base, ea_); R(5) = ea_; }
    R(12) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(12) + -1984; R(11) = ld32(base, ea_); R(12) = ea_; }
    R(20) = ld8(base, (R(4) + 254));
    R(22) = ld32(base, (R(5) + 4));
    R(23) = ld32(base, (R(5) + 8));
    cr_cmp_u(ctx, 0, R(20), 0x1u);
    R(24) = ld32(base, (R(5) + 12));
    R(25) = ld32(base, (R(5) + 16));
    R(26) = ld32(base, (R(5) + 20));
    R(27) = ld32(base, (R(5) + 24));
    R(28) = ld32(base, (R(5) + 28));
    R(29) = ld32(base, (R(5) + 32));
    R(30) = ld32(base, (R(5) + 36));
    R(31) = ld32(base, (R(5) + 40));
    R(10) = ld32(base, (R(12) + 4));
    R(9) = ld32(base, (R(12) + 8));
    R(8) = ld32(base, (R(12) + 12));
    R(7) = ld32(base, (R(12) + 16));
    R(6) = ld32(base, (R(12) + 20));
    R(5) = ld32(base, (R(12) + 24));
    R(0) = ld32(base, (R(12) + 28));
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st32(base, (f + 44), R(22));
    st32(base, (f + 48), R(23));
    st32(base, (f + 52), R(24));
    st32(base, (f + 56), R(25));
    st32(base, (f + 60), R(26));
    st32(base, (f + 64), R(27));
    st32(base, (f + 68), R(28));
    st32(base, (f + 72), R(29));
    st32(base, (f + 76), R(30));
    st32(base, (f + 80), R(31));
    st32(base, (f + 8), R(11));
    st32(base, (f + 12), R(10));
    st32(base, (f + 16), R(9));
    st32(base, (f + 20), R(8));
    st32(base, (f + 24), R(7));
    st32(base, (f + 28), R(6));
    st32(base, (f + 32), R(5));
    st32(base, (f + 36), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_80079594; }
    R(0) = (R(20) + 250);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_80079594; }
    cr_cmp_u(ctx, 0, R(20), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_800795AC; }
    goto L_800795BC;
L_80079594:;
    R(4) = (R(3) + 0x90000u);
    R(3) = (f + 40);
    R(0) = ld8(base, (R(4) + 255));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_800795BC;
L_800795AC:;
    R(0) = ld8(base, (R(4) + 255));
    R(3) = (f + 8);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_800795BC:;
    R(11) = (f + 144);
    R(0) = lr;
}

/* fn_800795E0 (fn_800795E0, 292 bytes) */
static void bg_m_795e0(GM_CTX) {
    GM_FN(0x800795E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 144);
    R(4) = (R(3) + 0x90000u);
    R(5) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(5) + -1952; R(21) = ld32(base, ea_); R(5) = ea_; }
    R(12) = (0 + 0x802F0000u);
    { uint32_t ea_ = R(12) + -1904; R(11) = ld32(base, ea_); R(12) = ea_; }
    R(20) = ld8(base, (R(4) + 254));
    R(22) = ld32(base, (R(5) + 4));
    R(23) = ld32(base, (R(5) + 8));
    cr_cmp_u(ctx, 0, R(20), 0x1u);
    R(24) = ld32(base, (R(5) + 12));
    R(25) = ld32(base, (R(5) + 16));
    R(26) = ld32(base, (R(5) + 20));
    R(27) = ld32(base, (R(5) + 24));
    R(28) = ld32(base, (R(5) + 28));
    R(29) = ld32(base, (R(5) + 32));
    R(30) = ld32(base, (R(5) + 36));
    R(31) = ld32(base, (R(5) + 40));
    R(10) = ld32(base, (R(12) + 4));
    R(9) = ld32(base, (R(12) + 8));
    R(8) = ld32(base, (R(12) + 12));
    R(7) = ld32(base, (R(12) + 16));
    R(6) = ld32(base, (R(12) + 20));
    R(5) = ld32(base, (R(12) + 24));
    R(0) = ld32(base, (R(12) + 28));
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st32(base, (f + 44), R(22));
    st32(base, (f + 48), R(23));
    st32(base, (f + 52), R(24));
    st32(base, (f + 56), R(25));
    st32(base, (f + 60), R(26));
    st32(base, (f + 64), R(27));
    st32(base, (f + 68), R(28));
    st32(base, (f + 72), R(29));
    st32(base, (f + 76), R(30));
    st32(base, (f + 80), R(31));
    st32(base, (f + 8), R(11));
    st32(base, (f + 12), R(10));
    st32(base, (f + 16), R(9));
    st32(base, (f + 20), R(8));
    st32(base, (f + 24), R(7));
    st32(base, (f + 28), R(6));
    st32(base, (f + 32), R(5));
    st32(base, (f + 36), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_800796C4; }
    R(0) = (R(20) + 250);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 1))) { goto L_800796C4; }
    cr_cmp_u(ctx, 0, R(20), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_800796DC; }
    goto L_800796EC;
L_800796C4:;
    R(4) = (R(3) + 0x90000u);
    R(3) = (f + 40);
    R(0) = ld8(base, (R(4) + 255));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    goto L_800796EC;
L_800796DC:;
    R(0) = ld8(base, (R(4) + 255));
    R(3) = (f + 8);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    { uint32_t ea_ = (R(3) + R(0)); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_800796EC:;
    R(11) = (f + 144);
    R(0) = lr;
}

/* fn_80079710 (fn_80079710, 108 bytes) */
static void bg_m_79710(GM_CTX) {
    GM_FN(0x80079710); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -23004));
    GM_CALLV(0x80079730u, 0x8005F900u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80079764; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80079744u, 0x80077B00u, 0);
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007974Cu, 0x80079780u, 0);
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x80079758u, 0x800799E0u, 0);
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    GM_CALLV(0x80079764u, 0x80079AA0u, 0);
L_80079764:;
    R(0) = lr;
}

/* fn_80079780 (fn_80079780, 596 bytes) */
static void bg_m_79780(GM_CTX) {
    GM_FN(0x80079780); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x43300000u);
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(13) + -21688));
    R(5) = ld32(base, (R(13) + -22504));
    R(0) = ld8(base, (R(4) + 4622));
    st32(base, (f + 8), R(6));
    R(0) = ((int32_t)R(0) * 944);
    st32(base, (f + 16), R(6));
    R(31) = R(5) + R(0);
    R(0) = ld32(base, (R(31) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800797D8; }
    goto L_800797DC;
L_800797D8:;
    R(31) = (0 + 0);
L_800797DC:;
    R(4) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 2))) { goto L_800797F4; }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_800797F4:;
    { uint32_t ea_ = (R(2) + -29464); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29460); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -29456); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -436); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + -432); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80079818u, 0x800785E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_800798A0; }
    R(3) = (R(30) + 0x90000u);
    R(0) = ld8(base, (R(3) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007983C; }
    R(0) = ld8(base, (R(3) + 198));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800798A0; }
L_8007983C:;
    { uint32_t ea_ = (R(2) + -29452); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(3) = (R(30) + 0x90000u);
    R(4) = ld8(base, (R(3) + 257));
    R(3) = R(31) |R(31);
    ctx->f[30].u = ctx->f[31].u;
    GM_CALLV(0x80079854u, 0x8008E310u, 0);
    R(0) = ld32(base, (R(3) + 8));
    R(4) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29520); ctx->f[1].u = ld64(base, ea_); }
    R(3) = R(31) |R(31);
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    R(4) = ld8(base, (R(4) + 257));
    { uint32_t ea_ = (f + 8); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d + ctx->f[0].d);
    GM_CALLV(0x80079880u, 0x8008E310u, 0);
    R(0) = ld32(base, (R(3) + 12));
    { uint32_t ea_ = (R(2) + -29520); ctx->f[1].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[30].d - ctx->f[0].d);
    goto L_800798F8;
L_800798A0:;
    R(4) = (R(30) + 0x90000u);
    R(3) = R(31) |R(31);
    R(4) = ld8(base, (R(4) + 257));
    GM_CALLV(0x800798B0u, 0x8008E310u, 0);
    R(0) = ld32(base, (R(3) + 0));
    R(4) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29520); ctx->f[1].u = ld64(base, ea_); }
    R(3) = R(31) |R(31);
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    R(4) = ld8(base, (R(4) + 257));
    { uint32_t ea_ = (f + 8); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d + ctx->f[0].d);
    GM_CALLV(0x800798DCu, 0x8008E310u, 0);
    R(0) = ld32(base, (R(3) + 4));
    { uint32_t ea_ = (R(2) + -29520); ctx->f[1].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[30].d - ctx->f[0].d);
L_800798F8:;
    R(3) = (R(30) + 0x90000u);
    R(0) = ld8(base, (R(3) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80079968; }
    R(0) = ld8(base, (R(3) + 198));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80079968; }
    R(4) = ld8(base, (R(3) + 257));
    R(3) = R(31) |R(31);
    GM_CALLV(0x80079920u, 0x8008E310u, 0);
    R(0) = ld16(base, (R(3) + 20));
    R(4) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29520); ctx->f[1].u = ld64(base, ea_); }
    R(3) = R(31) |R(31);
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 12), R(0));
    R(4) = ld8(base, (R(4) + 257));
    { uint32_t ea_ = (f + 8); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d + ctx->f[0].d);
    GM_CALLV(0x8007994Cu, 0x8008E310u, 0);
    R(0) = ld16(base, (R(3) + 22));
    { uint32_t ea_ = (R(2) + -29520); ctx->f[1].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 20), R(0));
    { uint32_t ea_ = (f + 16); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[30].d - ctx->f[0].d);
L_80079968:;
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29448); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -416); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(3) + -428);
    { uint32_t ea_ = (R(2) + -29444); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d + ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -29440); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[30].d - ctx->f[0].d);
    ctx->f[1].u = ctx->f[31].u;
    GM_CALLV(0x80079990u, 0x8015F140u, 0);
    ctx->f[1].u = ctx->f[30].u;
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29448); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(3) + -424);
    { uint32_t ea_ = (R(2) + -29444); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29440); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_CALLV(0x800799ACu, 0x8015F140u, 0);
    R(0) = lr;
}

/* fn_800799E0 (fn_800799E0, 188 bytes) */
static void bg_m_799e0(GM_CTX) {
    { uint32_t ea_ = (R(4) + 196); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29436); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d * ctx->f[2].d);
    { uint32_t ea_ = (R(4) + -488); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[3].d);
    if ((CR_BIT(ctx, 2))) return;
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (R(2) + -29432); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80079A18; }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d + ctx->f[2].d);
    goto L_80079A28;
L_80079A18:;
    { uint32_t ea_ = (R(2) + -29428); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80079A28; }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[2].d - ctx->f[1].d);
L_80079A28:;
    { uint32_t ea_ = (R(2) + -29424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80079A3C; }
    ctx->f[3].u = ctx->f[0].u;
    goto L_80079A4C;
L_80079A3C:;
    { uint32_t ea_ = (R(2) + -29420); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80079A4C; }
    ctx->f[3].u = ctx->f[0].u;
L_80079A4C:;
    R(4) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(4) + -444); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -436); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d + ctx->f[3].d);
    { uint32_t ea_ = (R(4) + -444); stfs(base, ea_, ctx->f[2].d); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80079A74; }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d - ctx->f[4].d);
    { uint32_t ea_ = (R(4) + -444); stfs(base, ea_, ctx->f[0].d); }
    goto L_80079A90;
L_80079A74:;
    { uint32_t ea_ = (R(4) + -432); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[0].u ^ 0x8000000000000000ull;
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80079A90; }
    ctx->f[0].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (R(4) + -444); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d - ctx->f[4].d);
L_80079A90:;
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(3) + -488); stfs(base, ea_, ctx->f[3].d); }
}

/* fn_80079AA0 (fn_80079AA0, 180 bytes) */
static void bg_m_79aa0(GM_CTX) {
    R(5) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(4) + 5424); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + -388); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d * ctx->f[2].d);
    { uint32_t ea_ = (R(5) + -428); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + -424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80079AF8; }
    { uint32_t ea_ = (R(5) + -440); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[4].d);
    { uint32_t ea_ = (R(5) + -440); stfs(base, ea_, ctx->f[0].d); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) return;
    { uint32_t ea_ = (R(5) + -440); stfs(base, ea_, ctx->f[2].d); }
    return;
L_80079AF8:;
    if ((!CR_BIT(ctx, 0))) { goto L_80079B20; }
    { uint32_t ea_ = (R(5) + -440); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[3].u ^ 0x8000000000000000ull;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[4].d);
    { uint32_t ea_ = (R(5) + -440); stfs(base, ea_, ctx->f[1].d); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) return;
    { uint32_t ea_ = (R(5) + -440); stfs(base, ea_, ctx->f[0].d); }
    return;
L_80079B20:;
    { uint32_t ea_ = (R(5) + -440); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_80079B34; }
    { uint32_t ea_ = (R(5) + -440); stfs(base, ea_, ctx->f[2].d); }
L_80079B34:;
    R(3) = (R(3) + 0x90000u);
    ctx->f[0].u = ctx->f[3].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(3) + -440); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) return;
    { uint32_t ea_ = (R(3) + -440); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_80079B60 (fn_80079B60, 144 bytes) */
static void bg_m_79b60(GM_CTX) {
    R(5) = ld32(base, (R(13) + -22656));
    R(3) = (R(3) + 0x90000u);
    R(6) = ld32(base, (R(13) + -21688));
    R(4) = (0 + 0);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 1);
    st8(base, (R(3) + 198), R(4));
    { uint32_t ea_ = (R(5) + 56); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(5) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 184); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 188); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + 192), R(4));
    st8(base, (R(3) + 193), R(4));
    st8(base, (R(3) + 194), R(4));
    st8(base, (R(3) + 195), R(4));
    st8(base, (R(3) + 196), R(4));
    st8(base, (R(3) + 197), R(4));
    st32(base, (R(3) + 236), R(4));
    st32(base, (R(3) + 240), R(4));
    { uint32_t ea_ = (R(3) + 244); stfs(base, ea_, ctx->f[0].d); }
    st8(base, (R(3) + 252), R(4));
    st8(base, (R(3) + 253), R(0));
    R(0) = ld8(base, (R(6) + 4620));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) return;
    R(0) = ld8(base, (R(6) + 4621));
    cr_cmp_u(ctx, 0, R(0), 0x17u);
    if ((!CR_BIT(ctx, 2))) return;
    R(0) = ld8(base, (R(6) + 4622));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) return;
    { uint32_t ea_ = (R(2) + -29416); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 184); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_8007A6C0 (fn_8007A6C0, 1200 bytes) */
static void bg_m_7a6c0(GM_CTX) {
    GM_FN(0x8007A6C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(6) = ld32(base, (R(13) + -22704));
    R(30) = R(3) |R(3);
    R(29) = ld32(base, (R(13) + -22656));
    R(26) = R(4) |R(4);
    R(3) = (R(6) + 0x90000u);
    { uint32_t ea_ = (R(13) + -21908); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    R(0) = ld8(base, (R(3) + 2506));
    R(31) = R(5) |R(5);
    { uint32_t ea_ = (R(13) + -21904); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AAB0; }
    R(3) = R(6) |R(6);
    GM_CALLV(0x8007A750u, 0x800791D0u, 0);
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 16); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007A7A8; }
    R(3) = ld32(base, (R(13) + -22656));
    R(28) = ld32(base, (R(13) + -22704));
    { uint32_t ea_ = (R(3) + 52); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    R(3) = R(28) |R(28);
    GM_CALLV(0x8007A778u, 0x80078EB0u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(28) |R(28);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d / ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[30].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[28].d * ctx->f[0].d);
    GM_CALLV(0x8007A794u, 0x80078EB0u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(30) + 0x90000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[30].d);
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
L_8007A7A8:;
    R(4) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 136); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 156); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[29].d * ctx->f[1].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[31].d * ctx->f[1].d);
    { uint32_t ea_ = (R(4) + -392); stfs(base, ea_, ctx->f[30].d); }
    ctx->f[27].d = ctx->ps1[27] = frsp(ctx->f[0].d * ctx->f[30].d);
    { uint32_t ea_ = (R(4) + -388); stfs(base, ea_, ctx->f[29].d); }
    GM_CALLV(0x8007A7E0u, 0x80078A70u, 0);
    ctx->f[26].u = ctx->f[1].u;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007A7ECu, 0x80078C10u, 0);
    R(4) = (R(30) + 0x90000u);
    ctx->f[25].d = ctx->ps1[25] = frsp(ctx->f[1].d - ctx->f[30].d);
    { uint32_t ea_ = (R(4) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (R(4) + 56); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(28) = (0 + 1);
    ctx->f[24].d = ctx->ps1[24] = frsp(ctx->f[29].d + ctx->f[0].d);
    R(27) = (0 + 1);
    GM_CALLV(0x8007A810u, 0x800789A0u, 0);
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(29) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -344); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[30].u = ctx->f[1].u;
    { uint32_t ea_ = (R(3) + -388); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(26) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[3].d);
    { uint32_t ea_ = (R(29) + 60); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(26) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -444); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -340); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -440); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d + ctx->f[28].d);
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[23].d = ctx->ps1[23] = frsp(ctx->f[0].d - ctx->f[29].d);
    R(0) = ld32(base, (R(13) + -21624));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[27].d);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8007A884; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[26].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007A874; }
    ctx->f[0].u = ctx->f[26].u;
    goto L_8007A8D4;
L_8007A874:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[25].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007A8D4; }
    ctx->f[0].u = ctx->f[25].u;
    goto L_8007A8D4;
L_8007A884:;
    R(4) = ld32(base, (R(13) + -21688));
    R(0) = ld8(base, (R(4) + 4620));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007A8D4; }
    R(0) = ld8(base, (R(4) + 4621));
    cr_cmp_u(ctx, 0, R(0), 0x17u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007A8D4; }
    R(0) = ld8(base, (R(4) + 4622));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007A8D4; }
    R(0) = (int16_t)ld16(base, (R(3) + 2504));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007A8D4; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[26].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007A8C8; }
    ctx->f[0].u = ctx->f[26].u;
    goto L_8007A8D4;
L_8007A8C8:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[25].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007A8D4; }
    ctx->f[0].u = ctx->f[25].u;
L_8007A8D4:;
    cr_fcmp(ctx, 0, ctx->f[23].d, ctx->f[24].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007A8E4; }
    ctx->f[23].u = ctx->f[24].u;
    goto L_8007A8F0;
L_8007A8E4:;
    cr_fcmp(ctx, 0, ctx->f[23].d, ctx->f[31].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007A8F0; }
    ctx->f[23].u = ctx->f[31].u;
L_8007A8F0:;
    R(3) = (R(30) + 0x90000u);
    R(0) = ld8(base, (R(3) + 198));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007A940; }
    R(0) = ld8(base, (R(3) + 196));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007A920; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8007A92C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8007A938; }
    goto L_8007A940;
L_8007A920:;
    R(28) = (0 + 0);
    R(27) = (0 + 0);
    goto L_8007A940;
L_8007A92C:;
    R(28) = (0 + 0);
    R(27) = (0 + 1);
    goto L_8007A940;
L_8007A938:;
    R(28) = (0 + 1);
    R(27) = (0 + 0);
L_8007A940:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007A950; }
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(3) + -376); stfs(base, ea_, ctx->f[0].d); }
L_8007A950:;
    cr_cmp_s(ctx, 0, (int32_t)R(27), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007A9F4; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007A960u, 0x8007E0E0u, 0);
    { uint32_t ea_ = (R(2) + -29548); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007A9B4; }
    R(4) = ld32(base, (R(13) + -22656));
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (R(4) + 60); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    GM_CALLV(0x8007A97Cu, 0x8007E0E0u, 0);
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8007A9B4; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007A990u, 0x8007E0E0u, 0);
    cr_fcmp(ctx, 0, ctx->f[23].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007A9B4; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007A9A0u, 0x80078540u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007A9B4; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007A9B0u, 0x8007E0E0u, 0);
    ctx->f[23].u = ctx->f[1].u;
L_8007A9B4:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007A9D4; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007A9C4u, 0x8007E0E0u, 0);
    { uint32_t ea_ = (R(2) + -29548); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8007A9E0; }
L_8007A9D4:;
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(3) + -372); stfs(base, ea_, ctx->f[23].d); }
    goto L_8007A9F4;
L_8007A9E0:;
    ctx->f[1].u = ctx->f[23].u;
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29304); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(3) + -372);
    GM_CALLV(0x8007A9F4u, 0x8015F470u, 0);
L_8007A9F4:;
    R(3) = (R(30) + 0x90000u);
    R(0) = ld8(base, (R(3) + 254));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8007AA0C; }
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AA30; }
L_8007AA0C:;
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -352); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -392); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d + ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -376); stfs(base, ea_, ctx->f[1].d); }
L_8007AA30:;
    R(3) = (R(30) + 0x90000u);
    R(0) = ld8(base, (R(3) + 254));
    cr_cmp_u(ctx, 0, R(0), 0x6u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AA50; }
    { uint32_t ea_ = (R(3) + -388); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -400); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -372); stfs(base, ea_, ctx->f[0].d); }
L_8007AA50:;
    R(3) = (R(30) + 0x90000u);
    R(0) = ld8(base, (R(3) + 198));
    { uint32_t ea_ = (R(3) + -444); stfs(base, ea_, ctx->f[28].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (R(3) + -440); stfs(base, ea_, ctx->f[29].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_8007AA78; }
    { uint32_t ea_ = (R(3) + -376); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -372); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[1].d); }
L_8007AA78:;
    R(3) = (R(30) + 0x90000u);
    R(0) = ld8(base, (R(3) + 279));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007AAB0; }
    { uint32_t ea_ = (R(3) + -392); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 284); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 288); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -388); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[3].d);
    { uint32_t ea_ = (R(3) + -376); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -372); stfs(base, ea_, ctx->f[1].d); }
L_8007AAB0:;
    R(4) = (R(30) + 0x90000u);
    R(3) = R(30) |R(30);
    R(5) = ld8(base, (R(4) + 121));
    R(6) = (0 + 1);
    R(4) = (R(4) + 2520);
    GM_CALLV(0x8007AAC8u, 0x8007CA90u, 0);
    R(4) = (R(30) + 0x90000u);
    R(3) = R(30) |R(30);
    R(5) = ld8(base, (R(4) + 122));
    R(6) = (0 + 1);
    R(4) = (R(4) + 2520);
    GM_CALLV(0x8007AAE0u, 0x8007CA90u, 0);
    R(3) = ld32(base, (R(13) + -22704));
    R(3) = (R(3) + 0x90000u);
    R(0) = ld8(base, (R(3) + 2506));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AB10; }
    R(4) = (R(30) + 0x90000u);
    R(3) = R(30) |R(30);
    R(5) = R(4) |R(4);
    R(6) = (0 + 1);
    R(4) = (R(4) + 2572);
    R(5) = (R(5) + 2520);
    GM_CALLV(0x8007AB10u, 0x8007CD70u, 0);
L_8007AB10:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_8007AB70 (fn_8007AB70, 196 bytes) */
static void bg_m_7ab70(GM_CTX) {
    GM_FN(0x8007AB70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    GM_CALLV(0x8007AB94u, 0x8005FD20u, 0);
    R(4) = (R(29) + 0x90000u);
    R(31) = R(3) |R(3);
    R(5) = ld8(base, (R(4) + 121));
    R(3) = R(29) |R(29);
    R(6) = R(31) |R(31);
    R(4) = (R(4) + 2520);
    GM_CALLV(0x8007ABB0u, 0x8007CA90u, 0);
    R(4) = (R(29) + 0x90000u);
    R(3) = R(29) |R(29);
    R(5) = ld8(base, (R(4) + 122));
    R(6) = R(31) |R(31);
    R(4) = (R(4) + 2520);
    GM_CALLV(0x8007ABC8u, 0x8007CA90u, 0);
    R(3) = ld32(base, (R(13) + -22704));
    R(3) = (R(3) + 0x90000u);
    R(0) = ld8(base, (R(3) + 2506));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AC18; }
    R(4) = (R(29) + 0x90000u);
    R(3) = R(29) |R(29);
    R(5) = R(4) |R(4);
    R(6) = R(30) |R(30);
    R(4) = (R(4) + 2572);
    R(5) = (R(5) + 2520);
    GM_CALLV(0x8007ABF8u, 0x8007CD70u, 0);
    R(4) = (R(29) + 0x90000u);
    R(3) = R(29) |R(29);
    R(12) = R(4) |R(4);
    R(5) = R(30) |R(30);
    R(12) = (R(12) + 124);
    R(4) = (R(4) + 2572);
    GM_CALLV(0x8007AC14u, 0x802DCBFCu, 0);
    R(0) = R(0) | 0x0u;
L_8007AC18:;
    R(0) = lr;
}

/* fn_8007AC40 (fn_8007AC40, 3632 bytes) */
static void bg_m_7ac40(GM_CTX) {
    GM_FN(0x8007AC40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(6) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(4) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(27) = R(3) |R(3);
    { uint32_t ea_ = (R(4) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(28) = R(4) |R(4);
    { uint32_t ea_ = (R(4) + 12); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(13) + -21908); ctx->f[26].d = ctx->ps1[26] = ldfs(base, ea_); }
    R(29) = R(5) |R(5);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[2].d);
    { uint32_t ea_ = (R(6) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].u = ctx->f[0].u & ~0x8000000000000000ull;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[1].u & ~0x8000000000000000ull;
    { uint32_t ea_ = (R(6) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = frsp(ctx->f[3].d);
    { uint32_t ea_ = (R(13) + -21904); ctx->f[25].d = ctx->ps1[25] = ldfs(base, ea_); }
    ctx->f[24].d = ctx->ps1[24] = frsp(ctx->f[0].d / ctx->f[2].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(13) + -22704));
    ctx->f[2].d = frsp(ctx->f[4].d);
    ctx->f[23].d = ctx->ps1[23] = frsp(ctx->f[0].d / ctx->f[1].d);
    ctx->f[20].d = ctx->ps1[20] = frsp(ctx->f[3].d / ctx->f[26].d);
    ctx->f[21].d = ctx->ps1[21] = frsp(ctx->f[2].d / ctx->f[25].d);
    GM_CALLV(0x8007AD2Cu, 0x80079250u, 0);
    ctx->f[19].u = ctx->f[1].u;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007AD38u, 0x80079380u, 0);
    ctx->f[18].u = ctx->f[1].u;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007AD44u, 0x800794B0u, 0);
    ctx->f[27].u = ctx->f[1].u;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007AD50u, 0x800795E0u, 0);
    ctx->f[28].u = ctx->f[1].u;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007AD5Cu, 0x80078EB0u, 0);
    ctx->f[29].u = ctx->f[1].u;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007AD68u, 0x80079020u, 0);
    ctx->f[30].u = ctx->f[1].u;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007AD74u, 0x800791D0u, 0);
    R(3) = (R(27) + 0x90000u);
    ctx->f[31].u = ctx->f[1].u;
    R(0) = ld8(base, (R(3) + 254));
    R(30) = (0 + 0);
    R(31) = ld32(base, (R(13) + -21688));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AD98; }
    { uint32_t ea_ = (R(2) + -29300); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    goto L_8007AD9C;
L_8007AD98:;
    { uint32_t ea_ = (R(2) + -29296); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
L_8007AD9C:;
    ctx->f[1].u = ctx->f[23].u;
    R(4) = R(27) |R(27);
    ctx->f[21].d = ctx->ps1[21] = frsp(ctx->f[21].d * ctx->f[2].d);
    R(5) = R(28) |R(28);
    R(3) = (f + 8);
    GM_CALLV(0x8007ADB4u, 0x8007BD40u, 0);
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 254));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007ADD0; }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[20].u = ctx->f[21].u;
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
L_8007ADD0:;
    R(3) = (R(27) + 0x90000u);
    R(3) = ld8(base, (R(3) + 254));
    R(0) = (R(3) + 250);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_8007ADFC; }
    { uint32_t ea_ = (f + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[21].u = ctx->f[20].u;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
L_8007ADFC:;
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 254));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AEC8; }
    R(3) = ld8(base, (R(3) + 255));
    R(0) = (R(3) + 251);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 1))) { goto L_8007AE30; }
    R(0) = (R(3) + 255);
    R(0) = R(0) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 1))) { goto L_8007AE7C; }
L_8007AE30:;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007AE38u, 0x800791D0u, 0);
    cr_fcmp(ctx, 0, ctx->f[24].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007AE4C; }
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[18].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007AE4C; }
    ctx->f[20].u = ctx->f[18].u;
L_8007AE4C:;
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007AE54u, 0x80078540u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AEC8; }
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 34));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AEC8; }
    cr_fcmp(ctx, 0, ctx->f[21].d, ctx->f[18].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007AEC8; }
    ctx->f[21].u = ctx->f[18].u;
    goto L_8007AEC8;
L_8007AE7C:;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007AE84u, 0x80079020u, 0);
    cr_fcmp(ctx, 0, ctx->f[24].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8007AE9C; }
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[19].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007AE9C; }
    ctx->f[20].u = ctx->f[19].u;
L_8007AE9C:;
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007AEA4u, 0x80078540u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AEC8; }
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 34));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AEC8; }
    cr_fcmp(ctx, 0, ctx->f[21].d, ctx->f[19].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007AEC8; }
    ctx->f[21].u = ctx->f[19].u;
L_8007AEC8:;
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 254));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AF2C; }
    R(0) = ld8(base, (R(3) + 255));
    cr_cmp_u(ctx, 0, R(0), 0xAu);
    if ((!CR_BIT(ctx, 2))) { goto L_8007AF2C; }
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007AEECu, 0x80078670u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8007AF1C; }
    { uint32_t ea_ = (R(2) + -29316); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[28].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 1))) { goto L_8007AF14; }
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 2507));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007AF24; }
L_8007AF14:;
    ctx->f[20].u = ctx->f[0].u;
    goto L_8007AF24;
L_8007AF1C:;
    { uint32_t ea_ = (R(2) + -29316); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[20].d = ctx->ps1[20] = frsp(ctx->f[0].d + ctx->f[18].d);
L_8007AF24:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[21].d = ctx->ps1[21] = frsp(ctx->f[20].d - ctx->f[0].d);
L_8007AF2C:;
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[21].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007AF38; }
    goto L_8007AF3C;
L_8007AF38:;
    ctx->f[20].u = ctx->f[21].u;
L_8007AF3C:;
    R(3) = ld32(base, (R(13) + -23020));
    R(0) = ld32(base, (R(3) + 16));
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8007B084; }
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 148));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007AF70; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8007AF90; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8007AFE0; }
    goto L_8007B014;
L_8007AF70:;
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[19].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007AF88; }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[30].d); }
    st8(base, (R(3) + 148), R(0));
    goto L_8007B014;
L_8007AF88:;
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[29].d); }
    goto L_8007B014;
L_8007AF90:;
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[18].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007AFA8; }
    R(0) = (0 + 2);
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[31].d); }
    st8(base, (R(3) + 148), R(0));
    goto L_8007B014;
L_8007AFA8:;
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[27].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007AFD0; }
    R(0) = (int16_t)ld16(base, (R(3) + 294));
    R(30) = (0 + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 120);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B014; }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[29].d); }
    st8(base, (R(3) + 148), R(0));
    goto L_8007B014;
L_8007AFD0:;
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[19].d);
    if ((CR_BIT(ctx, 0))) { goto L_8007B014; }
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[30].d); }
    goto L_8007B014;
L_8007AFE0:;
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[28].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B008; }
    R(0) = (int16_t)ld16(base, (R(3) + 294));
    R(30) = (0 + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 120);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B014; }
    R(0) = (0 + 1);
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[30].d); }
    st8(base, (R(3) + 148), R(0));
    goto L_8007B014;
L_8007B008:;
    cr_fcmp(ctx, 0, ctx->f[20].d, ctx->f[18].d);
    if ((CR_BIT(ctx, 0))) { goto L_8007B014; }
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[31].d); }
L_8007B014:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 152); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[31].d);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B054; }
    { uint32_t ea_ = (R(3) + 160); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[30].d);
    if ((CR_BIT(ctx, 2))) { goto L_8007B048; }
    { uint32_t ea_ = (R(3) + 136); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8007B048; }
    { uint32_t ea_ = (R(3) + 156); stfs(base, ea_, ctx->f[1].d); }
L_8007B048:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 160); stfs(base, ea_, ctx->f[30].d); }
    goto L_8007B058;
L_8007B054:;
    { uint32_t ea_ = (R(3) + 160); stfs(base, ea_, ctx->f[29].d); }
L_8007B058:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007B074; }
    R(4) = (R(27) + 0x90000u);
    R(3) = (int16_t)ld16(base, (R(4) + 294));
    R(0) = (R(3) + 1);
    st16(base, (R(4) + 294), R(0));
    goto L_8007B090;
L_8007B074:;
    R(3) = (R(27) + 0x90000u);
    R(0) = (0 + 0);
    st16(base, (R(3) + 294), R(0));
    goto L_8007B090;
L_8007B084:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 152); stfs(base, ea_, ctx->f[0].d); }
L_8007B090:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 152); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[27].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B140; }
    R(0) = ld8(base, (R(3) + 276));
    { uint32_t ea_ = (R(2) + -29292); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (R(2) + -29288); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29284); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    if ((CR_BIT(ctx, 2))) { goto L_8007B0D0; }
    cr_cmp_u(ctx, 0, R(0), 0x8u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B0D0; }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29448); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[6].u = ctx->f[2].u;
L_8007B0D0:;
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[20].d * ctx->f[20].d);
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29280); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[27].u;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(3) + 156);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[20].d * ctx->f[5].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[5].d * ctx->f[3].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[5].d + ctx->f[0].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[6].d * ctx->f[5].d);
    GM_CALLV(0x8007B0FCu, 0x8015F140u, 0);
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 156); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B1C0; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[27].d - ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -29448); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B130; }
    R(0) = (0 + 90);
    st32(base, (R(3) + 140), R(0));
L_8007B130:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007B1C0;
L_8007B140:;
    if ((!CR_BIT(ctx, 1))) { goto L_8007B1B8; }
    R(0) = ld8(base, (R(3) + 276));
    { uint32_t ea_ = (R(2) + -29476); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (R(2) + -29288); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29284); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    if ((CR_BIT(ctx, 2))) { goto L_8007B170; }
    cr_cmp_u(ctx, 0, R(0), 0x8u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B170; }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29448); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[5].u = ctx->f[2].u;
L_8007B170:;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[20].d * ctx->f[20].d);
    R(3) = (R(27) + 0x90000u);
    R(0) = ld32(base, (R(3) + 140));
    { uint32_t ea_ = (R(2) + -29280); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[20].d * ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d * ctx->f[1].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d + ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B1A8; }
    ctx->f[1].u = ctx->f[27].u;
    R(3) = (R(3) + 136);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[5].d * ctx->f[3].d);
    GM_CALLV(0x8007B1A8u, 0x8015F140u, 0);
L_8007B1A8:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 160); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 156); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007B1C0;
L_8007B1B8:;
    { uint32_t ea_ = (R(3) + 160); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 156); stfs(base, ea_, ctx->f[0].d); }
L_8007B1C0:;
    R(4) = (R(27) + 0x90000u);
    R(3) = ld32(base, (R(4) + 140));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007B1D8; }
    R(0) = (R(3) + -1);
    st32(base, (R(4) + 140), R(0));
L_8007B1D8:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[23].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B1EC; }
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[23].d); }
L_8007B1EC:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B204; }
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[29].d); }
    goto L_8007B210;
L_8007B204:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[31].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B210; }
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[31].d); }
L_8007B210:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(13) + -21904); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 136); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[28].d * ctx->f[2].d);
    ctx->f[1].u = ctx->f[1].u ^ 0x8000000000000000ull;
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B240; }
    ctx->f[28].d = ctx->ps1[28] = frsp(ctx->f[1].d / ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[28].d); }
L_8007B240:;
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007B248u, 0x8007E0E0u, 0);
    { uint32_t ea_ = (R(2) + -29548); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B2BC; }
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(13) + -21904); ctx->f[19].d = ctx->ps1[19] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -400); ctx->f[18].d = ctx->ps1[18] = ldfs(base, ea_); }
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007B268u, 0x8007E0E0u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[18].d - ctx->f[1].d);
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 34));
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    ctx->f[18].d = ctx->ps1[18] = frsp(ctx->f[0].d / ctx->f[19].d);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B290; }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 2516); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007B2A8;
L_8007B290:;
    { uint32_t ea_ = (R(2) + -29316); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (R(3) + 2516);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[3].u;
    { uint32_t ea_ = (R(2) + -29476); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x8007B2A8u, 0x8015F140u, 0);
L_8007B2A8:;
    R(3) = (R(27) + 0x90000u);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[18].d - ctx->f[28].d);
    { uint32_t ea_ = (R(3) + 2516); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[28].d = ctx->ps1[28] = frsp(ctx->f[28].d + ctx->f[0].d);
L_8007B2BC:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[26].d * ctx->f[28].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[25].d * ctx->f[28].d);
    R(4) = (R(27) + 0x90000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[28].d);
    { uint32_t ea_ = (R(4) + -384); stfs(base, ea_, ctx->f[1].d); }
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(4) + -380); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 12); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[18].d = ctx->ps1[18] = frsp(ctx->f[1].d * ctx->f[22].d);
    ctx->f[19].d = ctx->ps1[19] = frsp(ctx->f[2].d * ctx->f[22].d);
    GM_CALLV(0x8007B2ECu, 0x800789A0u, 0);
    ctx->f[20].u = ctx->f[1].u;
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007B2F8u, 0x80078B40u, 0);
    { uint32_t ea_ = (R(28) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(28) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = ld32(base, (R(13) + -21624));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 12); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    { uint32_t ea_ = (R(28) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[2].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[4].d + ctx->f[3].d);
    { uint32_t ea_ = (R(3) + -404); ctx->f[26].d = ctx->ps1[26] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -400); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    ctx->f[21].d = ctx->ps1[21] = frsp(ctx->f[2].d * ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[5].d - ctx->f[18].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[5].d + ctx->f[18].d);
    if ((CR_BIT(ctx, 2))) { goto L_8007B360; }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[20].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B350; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[20].d - ctx->f[0].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[5].d + ctx->f[0].d);
    goto L_8007B360;
L_8007B350:;
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B360; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[5].d - ctx->f[0].d);
L_8007B360:;
    R(3) = (R(27) + 0x90000u);
    ctx->f[23].d = ctx->ps1[23] = frsp(ctx->f[5].d - ctx->f[18].d);
    R(4) = ld8(base, (R(3) + 254));
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B37C; }
    cr_cmp_u(ctx, 0, R(4), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B3CC; }
L_8007B37C:;
    R(3) = (R(27) + 0x90000u);
    R(5) = ld32(base, (R(13) + -21688));
    { uint32_t ea_ = (R(3) + -352); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = ld8(base, (R(5) + 4620));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(3) + -384); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0xBu);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    ctx->f[23].d = ctx->ps1[23] = frsp(ctx->f[20].d + ctx->f[1].d);
    ctx->f[23].d = ctx->ps1[23] = frsp(ctx->f[23].d - ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B3CC; }
    R(0) = ld8(base, (R(5) + 4621));
    cr_cmp_u(ctx, 0, R(0), 0x41u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B3CC; }
    R(0) = ld8(base, (R(5) + 4622));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B3CC; }
    { uint32_t ea_ = (R(2) + -29504); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[23].d = ctx->ps1[23] = frsp(ctx->f[23].d - ctx->f[0].d);
L_8007B3CC:;
    cr_cmp_u(ctx, 0, R(4), 0x1u);
    R(30) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007B408; }
    cr_cmp_u(ctx, 0, R(4), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B408; }
    ctx->f[1].u = ctx->f[28].u;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8007B3F0u, 0x8007BC40u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007B408; }
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8007B404u, 0x8007BA70u, 0);
    R(30) = (0 + 1);
L_8007B408:;
    R(0) = ld32(base, (R(13) + -21624));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8007B450; }
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007B41Cu, 0x80078A70u, 0);
    R(3) = (R(27) + 0x90000u);
    ctx->f[20].u = ctx->f[1].u;
    { uint32_t ea_ = (R(3) + -384); ctx->f[18].d = ctx->ps1[18] = ldfs(base, ea_); }
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007B430u, 0x80078C10u, 0);
    cr_fcmp(ctx, 0, ctx->f[23].d, ctx->f[20].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[18].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B444; }
    ctx->f[23].u = ctx->f[20].u;
    goto L_8007B450;
L_8007B444:;
    cr_fcmp(ctx, 0, ctx->f[23].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B450; }
    ctx->f[23].u = ctx->f[0].u;
L_8007B450:;
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B46C; }
    R(0) = ld32(base, (R(13) + -21624));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8007B46C; }
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + -368); stfs(base, ea_, ctx->f[23].d); }
L_8007B46C:;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[21].d + ctx->f[19].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[21].d - ctx->f[19].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[26].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B480; }
    goto L_8007B484;
L_8007B480:;
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[27].d);
L_8007B484:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    R(30) = (0 + 0);
    GM_CALLV(0x8007B494u, 0x8007BBF0u, 0);
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + -364); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B4C4; }
    R(0) = ld8(base, (R(3) + 121));
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B4BC; }
    R(0) = ld8(base, (R(3) + 122));
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B4C4; }
L_8007B4BC:;
    ctx->f[22].u = ctx->f[1].u;
    R(30) = R(30) | 0x10u;
L_8007B4C4:;
    R(3) = R(27) |R(27);
    R(4) = R(28) |R(28);
    GM_CALLV(0x8007B4D0u, 0x8007BBA0u, 0);
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + -364); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B544; }
    R(0) = ld8(base, (R(3) + 121));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B4F8; }
    R(0) = ld8(base, (R(3) + 122));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B504; }
L_8007B4F8:;
    ctx->f[22].u = ctx->f[1].u;
    R(30) = (0 + 1);
    goto L_8007B544;
L_8007B504:;
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B544; }
    R(0) = R(30) & 0x10u;
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8007B544; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 24), R(0));
    { uint32_t ea_ = (R(2) + -29520); ctx->f[2].u = ld64(base, ea_); }
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 16); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 20));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 28), R(0));
    { uint32_t ea_ = (f + 24); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (R(3) + -416); stfs(base, ea_, ctx->f[0].d); }
L_8007B544:;
    R(0) = R(30) & 0xFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8007B5A8; }
    cr_cmp_u(ctx, 0, R(0), 0x11u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B588; }
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 121));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B570; }
    R(0) = ld8(base, (R(3) + 122));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B57C; }
L_8007B570:;
    R(0) = R(30) & 0x10u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8007B5A8; }
    goto L_8007B5A8;
L_8007B57C:;
    R(0) = R(30) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8007B5A8; }
    goto L_8007B5A8;
L_8007B588:;
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 121));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B5A4; }
    R(0) = ld8(base, (R(3) + 122));
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B5A8; }
L_8007B5A4:;
    ctx->f[22].u = ctx->f[1].u;
L_8007B5A8:;
    R(0) = R(30) & 0xFFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8007B64C; }
    R(4) = (R(27) + 0x90000u);
    ctx->f[1].u = fctiw_bits(ctx->f[22].d, 1);
    { uint32_t ea_ = (R(4) + -364); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); st64(base, ea_, ctx->f[1].u); }
    ctx->f[0].u = fctiw_bits(ctx->f[2].d, 1);
    R(3) = ld32(base, (f + 28));
    { uint32_t ea_ = (f + 16); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 0))) { goto L_8007B608; }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[22].d);
    { uint32_t ea_ = (R(2) + -29304); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B5F8; }
    { uint32_t ea_ = (R(4) + 164); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 164); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007B64C;
L_8007B5F8:;
    { uint32_t ea_ = (R(4) + 164); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(4) + 164); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007B64C;
L_8007B608:;
    { uint32_t ea_ = (f + 24); st64(base, ea_, ctx->f[1].u); }
    { uint32_t ea_ = (f + 16); st64(base, ea_, ctx->f[0].u); }
    R(3) = ld32(base, (f + 28));
    R(0) = ld32(base, (f + 20));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_8007B64C; }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[22].d - ctx->f[2].d);
    { uint32_t ea_ = (R(2) + -29304); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B640; }
    { uint32_t ea_ = (R(4) + 164); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 164); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007B64C;
L_8007B640:;
    { uint32_t ea_ = (R(4) + 164); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(4) + 164); stfs(base, ea_, ctx->f[0].d); }
L_8007B64C:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29464); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -364); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(28) + 12); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B670; }
    ctx->f[4].u = ctx->f[0].u;
L_8007B670:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29464); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -380); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -364); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[5].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B694; }
    ctx->f[5].u = ctx->f[0].u;
L_8007B694:;
    { uint32_t ea_ = (R(2) + -29476); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[4].d + ctx->f[5].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[25].d);
    { uint32_t ea_ = (R(3) + 164); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[28].d - ctx->f[1].d);
    R(3) = R(27) |R(27);
    ctx->f[19].d = ctx->ps1[19] = frsp(ctx->f[3].d * ctx->f[4].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d * ctx->f[1].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[0].d + ctx->f[1].d);
    ctx->f[18].u = ctx->f[29].u;
    GM_CALLV(0x8007B6C8u, 0x80079780u, 0);
    R(4) = (R(27) + 0x90000u);
    R(3) = ld32(base, (R(13) + -22704));
    { uint32_t ea_ = (R(4) + 12); ctx->f[20].d = ctx->ps1[20] = ldfs(base, ea_); }
    GM_CALLV(0x8007B6D8u, 0x80078EB0u, 0);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[7].d / ctx->f[20].d);
    { uint32_t ea_ = (R(3) + -380); ctx->f[9].d = ctx->ps1[9] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -364); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -428); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -424); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29304); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d * ctx->f[9].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[8].d - ctx->f[9].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[5].d * ctx->f[6].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[8].d - ctx->f[1].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[7].d + ctx->f[5].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[4].d * ctx->f[5].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d * ctx->f[5].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[8].d - ctx->f[4].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B734; }
    ctx->f[3].u = ctx->f[0].u;
L_8007B734:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -380); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -364); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -29304); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B760; }
    ctx->f[4].u = ctx->f[0].u;
L_8007B760:;
    cr_fcmp(ctx, 0, ctx->f[19].d, ctx->f[3].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B780; }
    R(3) = (R(27) + 0x90000u);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[19].d - ctx->f[3].d);
    { uint32_t ea_ = (R(3) + 168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007B79C;
L_8007B780:;
    cr_fcmp(ctx, 0, ctx->f[19].d, ctx->f[4].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B79C; }
    R(3) = (R(27) + 0x90000u);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[4].d - ctx->f[19].d);
    { uint32_t ea_ = (R(3) + 168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[0].d); }
L_8007B79C:;
    R(3) = (R(27) + 0x90000u);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[25].d * ctx->f[28].d);
    { uint32_t ea_ = (R(3) + 168); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d + ctx->f[2].d);
    { uint32_t ea_ = (R(3) + -360); stfs(base, ea_, ctx->f[29].d); }
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[26].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d - ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B7D4; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d - ctx->f[26].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[29].d - ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -360); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007B7F0;
L_8007B7D4:;
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[27].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B7F0; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[27].d - ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[29].d + ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + -360); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[0].d); }
L_8007B7F0:;
    R(4) = (R(27) + 0x90000u);
    R(0) = (0 + 0);
    st8(base, (R(4) + 34), R(0));
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(4) + -360); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    GM_CALLV(0x8007B808u, 0x8007E0E0u, 0);
    { uint32_t ea_ = (R(2) + -29548); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B898; }
    R(4) = ld32(base, (R(13) + -22656));
    R(3) = R(27) |R(27);
    { uint32_t ea_ = (R(4) + 60); ctx->f[19].d = ctx->ps1[19] = ldfs(base, ea_); }
    GM_CALLV(0x8007B824u, 0x8007E0E0u, 0);
    cr_fcmp(ctx, 0, ctx->f[19].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8007B88C; }
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007B838u, 0x8007E0E0u, 0);
    cr_fcmp(ctx, 0, ctx->f[22].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B898; }
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(13) + -21904); ctx->f[20].d = ctx->ps1[20] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -400); ctx->f[19].d = ctx->ps1[19] = ldfs(base, ea_); }
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007B854u, 0x8007E0E0u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[19].d - ctx->f[1].d);
    R(3) = R(27) |R(27);
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    ctx->f[19].d = ctx->ps1[19] = frsp(ctx->f[0].d / ctx->f[20].d);
    GM_CALLV(0x8007B868u, 0x80078540u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B898; }
    cr_fcmp(ctx, 0, ctx->f[19].d, ctx->f[28].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8007B898; }
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007B884u, 0x8007E0E0u, 0);
    ctx->f[22].u = ctx->f[1].u;
    goto L_8007B898;
L_8007B88C:;
    R(3) = (R(27) + 0x90000u);
    R(0) = (0 + 1);
    st8(base, (R(3) + 34), R(0));
L_8007B898:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + -380); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[22].d, ctx->f[3].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007B8CC; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[22].d);
    { uint32_t ea_ = (R(3) + 168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[22].u = ctx->f[3].u;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007B8E8;
L_8007B8CC:;
    cr_fcmp(ctx, 0, ctx->f[22].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007B8E8; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[22].d - ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[22].u = ctx->f[2].u;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[0].d); }
L_8007B8E8:;
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 254));
    cr_cmp_u(ctx, 0, R(0), 0x6u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B904; }
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[22].u = ctx->f[3].u;
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[0].d); }
L_8007B904:;
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 2508));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B950; }
    R(3) = ld8(base, (R(31) + 4621));
    cr_cmp_u(ctx, 0, R(3), 0x25u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B92C; }
    R(0) = ld8(base, (R(31) + 4625));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B944; }
L_8007B92C:;
    cr_cmp_u(ctx, 0, R(3), 0x17u);
    if ((CR_BIT(ctx, 2))) { goto L_8007B944; }
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + 2512); ctx->f[22].d = ctx->ps1[22] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[22].d - ctx->f[18].d);
    { uint32_t ea_ = (R(3) + 168); stfs(base, ea_, ctx->f[0].d); }
L_8007B944:;
    R(3) = (R(27) + 0x90000u);
    R(0) = (0 + 1);
    st8(base, (R(3) + 2508), R(0));
L_8007B950:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B970; }
    R(3) = R(27) |R(27);
    GM_CALLV(0x8007B960u, 0x8007E0E0u, 0);
    { uint32_t ea_ = (R(2) + -29548); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8007B97C; }
L_8007B970:;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(3) + -364); stfs(base, ea_, ctx->f[22].d); }
    goto L_8007B990;
L_8007B97C:;
    ctx->f[1].u = ctx->f[22].u;
    R(3) = (R(27) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29304); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (R(3) + -364);
    GM_CALLV(0x8007B990u, 0x8015F470u, 0);
L_8007B990:;
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 279));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007B9C8; }
    { uint32_t ea_ = (R(3) + -384); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 284); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 288); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -380); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[3].d);
    { uint32_t ea_ = (R(3) + -368); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + -364); stfs(base, ea_, ctx->f[1].d); }
L_8007B9C8:;
    R(3) = (R(27) + 0x90000u);
    R(0) = ld8(base, (R(3) + 198));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007B9E8; }
    { uint32_t ea_ = (R(3) + -368); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -364); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 172); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[1].d); }
L_8007B9E8:;
    R(11) = (f + 64);
    R(0) = lr;
}

/* fn_8007BA70 (fn_8007BA70, 304 bytes) */
static void bg_m_7ba70(GM_CTX) {
    GM_FN(0x8007BA70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(4) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(5) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = R(3) |R(3);
    R(0) = ld8(base, (R(5) + 121));
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    { uint32_t ea_ = (R(5) + -384); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_8007BACC; }
    R(0) = ld8(base, (R(5) + 122));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007BAE4; }
L_8007BACC:;
    R(4) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(2) + -29276); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    goto L_8007BAF8;
L_8007BAE4:;
    R(4) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(2) + -29276); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 120); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d - ctx->f[0].d);
L_8007BAF8:;
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[2].d - ctx->f[0].d);
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(3) + -368); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29280); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[30].d - ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007BB1C; }
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[1].d + ctx->f[2].d);
    goto L_8007BB2C;
L_8007BB1C:;
    { uint32_t ea_ = (R(2) + -29272); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007BB2C; }
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[2].d - ctx->f[1].d);
L_8007BB2C:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8007BB34u, 0x80078A70u, 0);
    ctx->f[29].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8007BB40u, 0x80078C10u, 0);
    R(0) = ld32(base, (R(13) + -21624));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[31].d);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8007BB6C; }
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007BB60; }
    ctx->f[30].u = ctx->f[29].u;
    goto L_8007BB6C;
L_8007BB60:;
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007BB6C; }
    ctx->f[30].u = ctx->f[0].u;
L_8007BB6C:;
    R(3) = (R(31) + 0x90000u);
    { uint32_t ea_ = (R(3) + -368); stfs(base, ea_, ctx->f[30].d); }
    R(0) = lr;
}

/* fn_8007BBA0 (fn_8007BBA0, 68 bytes) */
static void bg_m_7bba0(GM_CTX) {
    { uint32_t ea_ = (R(2) + -29268); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(4) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + -364); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -29272); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d - ctx->f[2].d);
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007BBCC; }
    { uint32_t ea_ = (R(2) + -29280); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[0].d);
L_8007BBCC:;
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(3) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) return;
    ctx->f[1].u = ctx->f[0].u;
}

/* fn_8007BBF0 (fn_8007BBF0, 80 bytes) */
static void bg_m_7bbf0(GM_CTX) {
    R(6) = ld32(base, (R(13) + -22656));
    R(5) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29464); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 68); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (R(5) + -364); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29280); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[4].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d - ctx->f[3].d);
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007BC24; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d + ctx->f[3].d);
L_8007BC24:;
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(3) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) return;
    ctx->f[1].u = ctx->f[0].u;
}

/* fn_8007BC40 (fn_8007BC40, 256 bytes) */
static void bg_m_7bc40(GM_CTX) {
    GM_FN(0x8007BC40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(4) + 0); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    ctx->f[28].u = ctx->f[1].u;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    GM_CALLV(0x8007BC8Cu, 0x80078A70u, 0);
    ctx->f[31].u = ctx->f[1].u;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007BC98u, 0x80078C10u, 0);
    R(3) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(2) + -29276); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d + ctx->f[3].d);
    ctx->f[4].u = ctx->f[3].u;
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007BCBC; }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[30].d - ctx->f[31].d);
L_8007BCBC:;
    { uint32_t ea_ = (R(3) + 120); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29276); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007BCD8; }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d - ctx->f[29].d);
L_8007BCD8:;
    { uint32_t ea_ = (R(13) + -21908); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d + ctx->f[4].d);
    { uint32_t ea_ = (R(31) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[28].d * ctx->f[1].d);
    { uint32_t ea_ = (R(31) + 4); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007BD04; }
    R(3) = (0 + 1);
    goto L_8007BD08;
L_8007BD04:;
    R(3) = (0 + 0);
L_8007BD08:;
    R(0) = lr;
}

/* fn_8007BD40 (fn_8007BD40, 432 bytes) */
static void bg_m_7bd40(GM_CTX) {
    GM_FN(0x8007BD40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[31].u = ctx->f[2].u;
    ctx->f[30].u = ctx->f[1].u;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    R(3) = R(30) |R(30);
    { uint32_t ea_ = (R(13) + -21908); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(13) + -21904); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    GM_CALLV(0x8007BDB0u, 0x80078A70u, 0);
    ctx->f[29].u = ctx->f[1].u;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007BDBCu, 0x80078C10u, 0);
    { uint32_t ea_ = (R(2) + -29276); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    R(3) = (R(30) + 0x90000u);
    { uint32_t ea_ = (R(31) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 4); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[7].u = ctx->f[6].u;
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[0].d - ctx->f[6].d);
    { uint32_t ea_ = (R(3) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[6].d + ctx->f[4].d);
    { uint32_t ea_ = (R(3) + 60); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[5].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007BDEC; }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[0].d - ctx->f[29].d);
L_8007BDEC:;
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007BDFC; }
    { uint32_t ea_ = (R(31) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[1].d - ctx->f[0].d);
L_8007BDFC:;
    { uint32_t ea_ = (R(31) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 4); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[4].d - ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[6].d + ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[7].d + ctx->f[1].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d / ctx->f[28].d);
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007BE28; }
    ctx->f[4].u = ctx->f[0].u;
    goto L_8007BE34;
L_8007BE28:;
    cr_fcmp(ctx, 0, ctx->f[4].d, ctx->f[30].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007BE34; }
    ctx->f[4].u = ctx->f[30].u;
L_8007BE34:;
    { uint32_t ea_ = (R(2) + -29452); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29460); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[6].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[7].d);
    cr_fcmp(ctx, 0, ctx->f[5].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007BE58; }
    ctx->f[6].d = ctx->ps1[6] = frsp(ctx->f[2].d - ctx->f[0].d);
L_8007BE58:;
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[3].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007BE68; }
    { uint32_t ea_ = (R(31) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[0].d - ctx->f[3].d);
L_8007BE68:;
    { uint32_t ea_ = (R(31) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[6].d + ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[7].d + ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[31].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[27].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007BE98; }
    ctx->f[1].u = ctx->f[0].u;
    goto L_8007BEA4;
L_8007BE98:;
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[30].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007BEA4; }
    ctx->f[1].u = ctx->f[30].u;
L_8007BEA4:;
    { uint32_t ea_ = (R(29) + 0); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(29) + 4); stfs(base, ea_, ctx->f[1].d); }
    R(0) = lr;
}

/* fn_8007C7D0 (fn_8007C7D0, 372 bytes) */
static void bg_m_7c7d0(GM_CTX) {
    GM_FN(0x8007C7D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (R(3) + 0x90000u);
    ctx->f[31].u = ctx->f[1].u;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(13) + -21624));
    { uint32_t ea_ = (R(4) + -352); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_8007C904; }
    R(4) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(4) + 56); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    GM_CALLV(0x8007C830u, 0x800789A0u, 0);
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007C894; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8007C840u, 0x800789A0u, 0);
    ctx->f[30].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8007C84Cu, 0x80078B40u, 0);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[30].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[0].d * ctx->f[1].d);
    GM_CALLV(0x8007C860u, 0x800789A0u, 0);
    R(4) = ld32(base, (R(13) + -22656));
    ctx->f[27].d = ctx->ps1[27] = frsp(ctx->f[1].d + ctx->f[30].d);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 64); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 56); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    GM_CALLV(0x8007C878u, 0x800789A0u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[30].d);
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007C904; }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[27].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007C904; }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d - ctx->f[29].d);
    goto L_8007C904;
L_8007C894:;
    R(4) = ld32(base, (R(13) + -22656));
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 64); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 56); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    GM_CALLV(0x8007C8A8u, 0x80078B40u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[28].d);
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007C904; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x8007C8BCu, 0x800789A0u, 0);
    ctx->f[30].u = ctx->f[1].u;
    R(3) = R(31) |R(31);
    GM_CALLV(0x8007C8C8u, 0x80078B40u, 0);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[30].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[0].d * ctx->f[1].d);
    GM_CALLV(0x8007C8DCu, 0x800789A0u, 0);
    R(4) = ld32(base, (R(13) + -22656));
    ctx->f[27].d = ctx->ps1[27] = frsp(ctx->f[1].d + ctx->f[30].d);
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(4) + 56); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    GM_CALLV(0x8007C8F0u, 0x80078B40u, 0);
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007C904; }
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[27].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007C904; }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d + ctx->f[29].d);
L_8007C904:;
    ctx->f[1].u = ctx->f[31].u;
    R(0) = lr;
}

/* fn_8007C950 (fn_8007C950, 100 bytes) */
static void bg_m_7c950(GM_CTX) {
    GM_FN(0x8007C950); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = R(3) |R(3);
    R(31) = R(4) |R(4);
    R(3) = ld32(base, (R(13) + -22704));
    { uint32_t ea_ = (R(5) + 5420); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x8007C97Cu, 0x8007C7D0u, 0);
    ctx->f[31].u = ctx->f[1].u;
    R(3) = ld32(base, (R(13) + -22704));
    { uint32_t ea_ = (R(31) + 5420); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x8007C98Cu, 0x8007C7D0u, 0);
    cr_fcmp(ctx, 0, ctx->f[31].d, ctx->f[1].d);
    R(3) = ctx->cr;
    R(3) = rotl32(R(3), 2) & 0x1u;
    R(0) = lr;
}

/* fn_8007CA50 (fn_8007CA50, 24 bytes) */
static void bg_m_7ca50(GM_CTX) {
    { uint32_t ea_ = (R(3) + 5424); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 5424); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    R(3) = ctx->cr;
    R(3) = rotl32(R(3), 1) & 0x1u;
}

/* fn_8007CA70 (fn_8007CA70, 20 bytes) */
static void bg_m_7ca70(GM_CTX) {
    R(5) = ld32(base, (R(3) + 0));
    R(0) = ld32(base, (R(4) + 0));
    st32(base, (R(3) + 0), R(0));
    st32(base, (R(4) + 0), R(5));
}

/* fn_8007CD70 (fn_8007CD70, 2108 bytes) */
static void bg_m_7cd70(GM_CTX) {
    GM_FN(0x8007CD70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(7) = ld32(base, (R(13) + -22656));
    R(29) = R(3) |R(3);
    R(0) = ld8(base, (R(13) + -22918));
    R(30) = R(4) |R(4);
    { uint32_t ea_ = (R(7) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(31) = (0 + 0);
    R(0) = R(0) & 0x2u;
    CR0(ctx, R(0));
    { uint32_t ea_ = (R(7) + 56); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(7) + 60); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(7) + 68); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    if ((!CR_BIT(ctx, 2))) { goto L_8007D504; }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007CE58; }
    R(0) = ld32(base, (R(13) + -21632));
    cr_cmp_u(ctx, 0, R(0), 0xAu);
    if ((!CR_BIT(ctx, 0))) { goto L_8007CE80; }
L_8007CE58:;
    R(0) = ld32(base, (R(5) + 32));
    st32(base, (R(4) + 32), R(0));
    R(0) = ld32(base, (R(5) + 36));
    st32(base, (R(4) + 36), R(0));
    R(0) = ld32(base, (R(5) + 40));
    st32(base, (R(4) + 40), R(0));
    R(0) = ld32(base, (R(5) + 44));
    st32(base, (R(4) + 44), R(0));
    R(0) = ld32(base, (R(5) + 48));
    st32(base, (R(4) + 48), R(0));
L_8007CE80:;
    R(7) = ld32(base, (R(4) + 48));
    R(0) = ld32(base, (R(5) + 48));
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8007CED4; }
    R(7) = ld32(base, (R(4) + 32));
    R(0) = ld32(base, (R(5) + 32));
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8007CED0; }
    R(7) = ld32(base, (R(4) + 36));
    R(0) = ld32(base, (R(5) + 36));
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8007CED0; }
    R(7) = ld32(base, (R(4) + 40));
    R(0) = ld32(base, (R(5) + 40));
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8007CED0; }
    R(7) = ld32(base, (R(4) + 44));
    R(0) = ld32(base, (R(5) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(7), (int32_t)R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8007CED4; }
L_8007CED0:;
    R(31) = (0 + 1);
L_8007CED4:;
    R(0) = ld32(base, (R(5) + 32));
    R(26) = (0 + 0);
    st32(base, (R(4) + 32), R(0));
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = ld32(base, (R(5) + 36));
    st32(base, (R(4) + 36), R(0));
    { uint32_t ea_ = (R(2) + -29476); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = ld32(base, (R(5) + 40));
    st32(base, (R(4) + 40), R(0));
    { uint32_t ea_ = (R(2) + -29464); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(0) = ld32(base, (R(5) + 44));
    st32(base, (R(4) + 44), R(0));
    R(0) = ld32(base, (R(5) + 48));
    st32(base, (R(4) + 48), R(0));
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[0].d); }
    R(28) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(5) + 0); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[30].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
    R(27) = ld32(base, (R(13) + -21688));
    { uint32_t ea_ = (R(5) + 4); ctx->f[27].d = ctx->ps1[27] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (R(4) + 12); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[3].d);
    { uint32_t ea_ = (R(5) + 8); ctx->f[26].d = ctx->ps1[26] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (R(5) + 12); ctx->f[25].d = ctx->ps1[25] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 0))) { goto L_8007CF64; }
    ctx->f[28].u = ctx->f[30].u;
L_8007CF64:;
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[27].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007CF78; }
    ctx->f[27].u = ctx->f[0].u;
L_8007CF78:;
    cr_fcmp(ctx, 0, ctx->f[26].d, ctx->f[29].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007CF84; }
    ctx->f[26].u = ctx->f[29].u;
L_8007CF84:;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d - ctx->f[31].d);
    cr_fcmp(ctx, 0, ctx->f[25].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007CF94; }
    ctx->f[25].u = ctx->f[0].u;
L_8007CF94:;
    R(0) = ld32(base, (R(13) + -21624));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8007CFA8; }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8007CFC4; }
L_8007CFA8:;
    { uint32_t ea_ = (R(2) + -29248); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); stfs(base, ea_, ctx->f[27].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[28].d);
    { uint32_t ea_ = (R(4) + 8); stfs(base, ea_, ctx->f[26].d); }
    { uint32_t ea_ = (R(4) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 12); stfs(base, ea_, ctx->f[25].d); }
    goto L_8007D440;
L_8007CFC4:;
    R(3) = (R(3) + 0x90000u);
    R(0) = ld8(base, (R(3) + 121));
    cr_cmp_u(ctx, 0, R(0), 0x3u);
    if ((!CR_BIT(ctx, 2))) { goto L_8007CFD8; }
    { uint32_t ea_ = (R(2) + -29460); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
L_8007CFD8:;
    cr_fcmp(ctx, 0, ctx->f[26].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007CFEC; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d - ctx->f[4].d);
    cr_fcmp(ctx, 0, ctx->f[26].d, ctx->f[0].d);
    if ((CR_BIT(ctx, 1))) { goto L_8007D004; }
L_8007CFEC:;
    cr_fcmp(ctx, 0, ctx->f[25].d, ctx->f[3].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007D008; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d - ctx->f[31].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[4].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[25].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007D008; }
L_8007D004:;
    R(26) = (0 + 1);
L_8007D008:;
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(4) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d + ctx->f[2].d);
    { uint32_t ea_ = (R(5) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[14].d = ctx->ps1[14] = frsp(ctx->f[3].d * ctx->f[0].d);
    { uint32_t ea_ = (R(5) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[4].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[5].d + ctx->f[0].d);
    ctx->f[15].d = ctx->ps1[15] = frsp(ctx->f[3].d * ctx->f[2].d);
    ctx->f[16].d = ctx->ps1[16] = frsp(ctx->f[3].d * ctx->f[1].d);
    ctx->f[17].d = ctx->ps1[17] = frsp(ctx->f[3].d * ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[16].d - ctx->f[14].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[17].d - ctx->f[15].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    GM_CALLV(0x8007D064u, 0x802E8868u, 0);
    ctx->f[2].d = frsp(ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    if ((CR_BIT(ctx, 2))) { goto L_8007D088; }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[16].d - ctx->f[14].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[17].d - ctx->f[15].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d / ctx->f[2].d);
    goto L_8007D090;
L_8007D088:;
    { uint32_t ea_ = (R(2) + -29544); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[1].u;
L_8007D090:;
    ctx->f[2].u = ctx->f[1].u & ~0x8000000000000000ull;
    R(0) = ld8(base, (R(27) + 4620));
    ctx->f[3].u = ctx->f[0].u & ~0x8000000000000000ull;
    { uint32_t ea_ = (R(2) + -29280); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29244); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_u(ctx, 0, R(0), 0x7u);
    ctx->f[22].d = frsp(ctx->f[2].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[20].d = ctx->ps1[20] = ldfs(base, ea_); }
    ctx->f[2].d = frsp(ctx->f[3].d);
    ctx->f[19].d = ctx->ps1[19] = frsp(ctx->f[1].d * ctx->f[22].d);
    ctx->f[18].d = ctx->ps1[18] = frsp(ctx->f[0].d * ctx->f[2].d);
    if ((!CR_BIT(ctx, 2))) { goto L_8007D0CC; }
    R(0) = ld8(base, (R(27) + 4621));
    cr_cmp_u(ctx, 0, R(0), 0x6u);
    if ((CR_BIT(ctx, 2))) { goto L_8007D0D4; }
L_8007D0CC:;
    cr_cmp_s(ctx, 0, (int32_t)R(26), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007D0EC; }
L_8007D0D4:;
    { uint32_t ea_ = (R(2) + -29280); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[24].d = ctx->ps1[24] = ldfs(base, ea_); }
    ctx->f[22].d = ctx->ps1[22] = frsp(ctx->f[0].d * ctx->f[22].d);
    ctx->f[23].u = ctx->f[24].u;
    ctx->f[21].d = ctx->ps1[21] = frsp(ctx->f[0].d * ctx->f[2].d);
    goto L_8007D0FC;
L_8007D0EC:;
    { uint32_t ea_ = (R(2) + -29488); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29240); ctx->f[24].d = ctx->ps1[24] = ldfs(base, ea_); }
    ctx->f[21].d = ctx->ps1[21] = frsp(ctx->f[0].d * ctx->f[2].d);
    { uint32_t ea_ = (R(2) + -29476); ctx->f[23].d = ctx->ps1[23] = ldfs(base, ea_); }
L_8007D0FC:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[17].d = ctx->ps1[17] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29448); ctx->f[16].d = ctx->ps1[16] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29236); ctx->f[15].d = ctx->ps1[15] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29312); ctx->f[14].d = ctx->ps1[14] = ldfs(base, ea_); }
    if ((CR_BIT(ctx, 2))) { goto L_8007D134; }
    R(3) = (R(29) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29544); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 120);
    st32(base, (R(3) + 100), R(0));
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 112); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[0].d); }
L_8007D134:;
    R(4) = (R(29) + 0x90000u);
    R(3) = ld32(base, (R(4) + 100));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007D150; }
    R(0) = (R(3) + -1);
    st32(base, (R(4) + 100), R(0));
    { uint32_t ea_ = (R(2) + -29544); ctx->f[17].d = ctx->ps1[17] = ldfs(base, ea_); }
L_8007D150:;
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007D17C; }
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[3].u = ctx->f[15].u;
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[14].u;
    R(3) = (R(3) + 104);
    GM_CALLV(0x8007D178u, 0x8015F140u, 0);
    goto L_8007D1D4;
L_8007D17C:;
    { uint32_t ea_ = (R(28) + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[28].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007D1B8; }
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[3].u = ctx->f[15].u;
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[14].u;
    R(3) = (R(3) + 104);
    GM_CALLV(0x8007D1B4u, 0x8015F140u, 0);
    goto L_8007D1D4;
L_8007D1B8:;
    ctx->f[1].u = ctx->f[17].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(3) + 104);
    ctx->f[3].u = ctx->f[15].u;
    ctx->f[4].u = ctx->f[14].u;
    GM_CALLV(0x8007D1D4u, 0x8015F140u, 0);
L_8007D1D4:;
    R(3) = (R(29) + 0x90000u);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[24].d - ctx->f[20].d);
    { uint32_t ea_ = (R(3) + 104); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[22].d - ctx->f[19].d);
    ctx->f[1].u = ctx->f[28].u;
    { uint32_t ea_ = (R(2) + -29448); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d * ctx->f[0].d);
    R(3) = (f + 20);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[20].d + ctx->f[2].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[19].d + ctx->f[0].d);
    GM_CALLV(0x8007D204u, 0x8015F140u, 0);
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[27].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007D230; }
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[3].u = ctx->f[15].u;
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[14].u;
    R(3) = (R(3) + 108);
    GM_CALLV(0x8007D22Cu, 0x8015F140u, 0);
    goto L_8007D288;
L_8007D230:;
    { uint32_t ea_ = (R(28) + 64); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[27].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007D26C; }
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[3].u = ctx->f[15].u;
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[14].u;
    R(3) = (R(3) + 108);
    GM_CALLV(0x8007D268u, 0x8015F140u, 0);
    goto L_8007D288;
L_8007D26C:;
    ctx->f[1].u = ctx->f[17].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(3) + 108);
    ctx->f[3].u = ctx->f[15].u;
    ctx->f[4].u = ctx->f[14].u;
    GM_CALLV(0x8007D288u, 0x8015F140u, 0);
L_8007D288:;
    R(3) = (R(29) + 0x90000u);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[24].d - ctx->f[20].d);
    { uint32_t ea_ = (R(3) + 108); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[22].d - ctx->f[19].d);
    ctx->f[1].u = ctx->f[27].u;
    { uint32_t ea_ = (R(2) + -29448); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d * ctx->f[0].d);
    R(3) = (f + 16);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[20].d + ctx->f[2].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[19].d + ctx->f[0].d);
    GM_CALLV(0x8007D2B8u, 0x8015F140u, 0);
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[26].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007D2E4; }
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[3].u = ctx->f[15].u;
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[14].u;
    R(3) = (R(3) + 112);
    GM_CALLV(0x8007D2E0u, 0x8015F140u, 0);
    goto L_8007D33C;
L_8007D2E4:;
    { uint32_t ea_ = (R(28) + 68); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 60); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[26].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007D320; }
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[3].u = ctx->f[15].u;
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[14].u;
    R(3) = (R(3) + 112);
    GM_CALLV(0x8007D31Cu, 0x8015F140u, 0);
    goto L_8007D33C;
L_8007D320:;
    ctx->f[1].u = ctx->f[17].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(3) + 112);
    ctx->f[3].u = ctx->f[15].u;
    ctx->f[4].u = ctx->f[14].u;
    GM_CALLV(0x8007D33Cu, 0x8015F140u, 0);
L_8007D33C:;
    R(3) = (R(29) + 0x90000u);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[23].d - ctx->f[20].d);
    { uint32_t ea_ = (R(3) + 112); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[21].d - ctx->f[18].d);
    ctx->f[1].u = ctx->f[26].u;
    { uint32_t ea_ = (R(2) + -29448); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d * ctx->f[0].d);
    R(3) = (f + 12);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[20].d + ctx->f[2].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[18].d + ctx->f[0].d);
    GM_CALLV(0x8007D36Cu, 0x8015F140u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[25].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_8007D398; }
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[3].u = ctx->f[15].u;
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[14].u;
    R(3) = (R(3) + 116);
    GM_CALLV(0x8007D394u, 0x8015F140u, 0);
    goto L_8007D3F0;
L_8007D398:;
    { uint32_t ea_ = (R(28) + 68); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(28) + 60); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[25].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_8007D3D4; }
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[3].u = ctx->f[15].u;
    { uint32_t ea_ = (R(2) + -29552); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[4].u = ctx->f[14].u;
    R(3) = (R(3) + 116);
    GM_CALLV(0x8007D3D0u, 0x8015F140u, 0);
    goto L_8007D3F0;
L_8007D3D4:;
    ctx->f[1].u = ctx->f[17].u;
    R(3) = (R(29) + 0x90000u);
    ctx->f[2].u = ctx->f[16].u;
    R(3) = (R(3) + 116);
    ctx->f[3].u = ctx->f[15].u;
    ctx->f[4].u = ctx->f[14].u;
    GM_CALLV(0x8007D3F0u, 0x8015F140u, 0);
L_8007D3F0:;
    R(3) = (R(29) + 0x90000u);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[23].d - ctx->f[20].d);
    { uint32_t ea_ = (R(3) + 116); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[21].d - ctx->f[18].d);
    ctx->f[1].u = ctx->f[25].u;
    { uint32_t ea_ = (R(2) + -29448); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d * ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d * ctx->f[0].d);
    R(3) = (f + 8);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[20].d + ctx->f[2].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[18].d + ctx->f[0].d);
    GM_CALLV(0x8007D420u, 0x8015F140u, 0);
    { uint32_t ea_ = (f + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 0); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 12); stfs(base, ea_, ctx->f[0].d); }
L_8007D440:;
    { uint32_t ea_ = (R(30) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 12); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 8); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29476); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[4].d + ctx->f[3].d);
    R(3) = ld32(base, (R(13) + -22704));
    ctx->f[14].d = ctx->ps1[14] = frsp(ctx->f[1].d * ctx->f[2].d);
    ctx->f[15].d = ctx->ps1[15] = frsp(ctx->f[1].d * ctx->f[0].d);
    GM_CALLV(0x8007D46Cu, 0x80078A70u, 0);
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8007D494; }
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007D480u, 0x80078C10u, 0);
    { uint32_t ea_ = (f + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8007D4A8; }
L_8007D494:;
    R(3) = ld32(base, (R(13) + -22704));
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(3) + 296); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007D4BC;
L_8007D4A8:;
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(13) + -22704));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[14].d - ctx->f[0].d);
    R(3) = (R(3) + 0x90000u);
    { uint32_t ea_ = (R(3) + 296); stfs(base, ea_, ctx->f[0].d); }
L_8007D4BC:;
    R(4) = ld32(base, (R(13) + -22704));
    R(3) = (R(4) + 0x90000u);
    { uint32_t ea_ = (R(3) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8007D4E8; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d - ctx->f[31].d);
    { uint32_t ea_ = (R(3) + 60); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8007D4F8; }
L_8007D4E8:;
    R(3) = (R(4) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 300); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007D504;
L_8007D4F8:;
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[15].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 300); stfs(base, ea_, ctx->f[0].d); }
L_8007D504:;
    R(11) = (f + 64);
    R(0) = lr;
}

/* fn_8007D5B0 (fn_8007D5B0, 444 bytes) */
static void bg_m_7d5b0(GM_CTX) {
    R(6) = ((int32_t)R(6) * 8704);
    R(0) = (0 + 4);
    R(7) = (0 + 0);
    R(3) = R(3) + R(6);
    R(5) = ((int32_t)R(5) * 1088);
    R(3) = (R(3) + 4216);
    R(5) = R(3) + R(5);
    ctx->ctr = R(0);
L_8007D5D0:;
    R(0) = R(7) & 0xFFu;
    { uint32_t ea_ = (R(4) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = ((int32_t)R(0) * 68);
    R(6) = R(5) + R(0);
    { uint32_t ea_ = (R(6) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8007D658; }
    R(7) = (R(7) + 1);
    R(0) = R(7) & 0xFFu;
    R(0) = ((int32_t)R(0) * 68);
    R(6) = R(5) + R(0);
    { uint32_t ea_ = (R(6) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8007D658; }
    R(7) = (R(7) + 1);
    R(0) = R(7) & 0xFFu;
    R(0) = ((int32_t)R(0) * 68);
    R(6) = R(5) + R(0);
    { uint32_t ea_ = (R(6) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8007D658; }
    R(7) = (R(7) + 1);
    R(0) = R(7) & 0xFFu;
    R(0) = ((int32_t)R(0) * 68);
    R(6) = R(5) + R(0);
    { uint32_t ea_ = (R(6) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((CR_BIT(ctx, 2))) { goto L_8007D658; }
    R(7) = (R(7) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8007D5D0; }
L_8007D658:;
    R(0) = R(7) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x10u);
    if ((CR_BIT(ctx, 0))) { goto L_8007D668; }
    R(7) = (0 + 0);
L_8007D668:;
    R(3) = R(7) & 0xFFu;
    R(4) = (0 + 15);
    { uint32_t a_ = R(3); R(0) = 0xFu - a_; ctx->xer_ca = 0xFu >= a_; }
    ctx->ctr = R(0);
    cr_cmp_u(ctx, 0, R(3), 0xFu);
    if ((CR_BIT(ctx, 2))) { goto L_8007D728; }
L_8007D680:;
    R(3) = R(4) & 0xFFu;
    R(4) = (R(4) + -1);
    R(0) = R(4) & 0xFFu;
    R(0) = ((int32_t)R(0) * 68);
    R(6) = R(5) + R(0);
    R(0) = ((int32_t)R(3) * 68);
    { uint32_t ea_ = (R(6) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + R(0)); stfs(base, ea_, ctx->f[0].d); }
    R(3) = R(5) + R(0);
    { uint32_t ea_ = (R(6) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 20); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 32); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 36); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 52); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 60); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld16(base, (R(6) + 64));
    st16(base, (R(3) + 64), R(0));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8007D680; }
L_8007D728:;
    { uint32_t ea_ = (R(2) + -29552); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (0 + 0);
    { uint32_t ea_ = (R(6) + 0); stfs(base, ea_, ctx->f[0].d); }
    R(3) = R(7) |R(7);
    { uint32_t ea_ = (R(6) + 4); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 16); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 32); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 40); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 44); stfs(base, ea_, ctx->f[0].d); }
    st16(base, (R(6) + 64), R(0));
}

/* fn_8007E0E0 (fn_8007E0E0, 136 bytes) */
static void bg_m_7e0e0(GM_CTX) {
    GM_FN(0x8007E0E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(4) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(13) + -21904); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 68); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 60); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8007E124u, 0x80078EB0u, 0);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[1].d * ctx->f[31].d);
    R(3) = (R(31) + 0x90000u);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[29].d - ctx->f[30].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d + ctx->f[1].d);
    R(0) = lr;
}

/* fn_8007E170 (fn_8007E170, 12 bytes) */
static void bg_m_7e170(GM_CTX) {
    R(0) = (0 + 0x10000u);
    st32(base, (R(13) + -22712), R(0));
}

/* fn_8007E180 (fn_8007E180, 80 bytes) */
static void bg_m_7e180(GM_CTX) {
    GM_FN(0x8007E180); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80310000u);
    R(4) = (R(4) + -680);
    R(31) = R(3) |R(3);
    st32(base, (R(3) + 0), R(4));
    R(3) = (R(3) + 4);
    GM_CALLV(0x8007E1A8u, 0x80069020u, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 56), R(0));
    R(3) = R(31) |R(31);
    st32(base, (R(31) + 60), R(0));
    st32(base, (R(13) + -22696), R(31));
    R(0) = lr;
}

/* fn_8007E1D0 (fn_8007E1D0, 236 bytes) */
static void bg_m_7e1d0(GM_CTX) {
    GM_FN(0x8007E1D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(29) = R(4) |R(4);
    R(28) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8007E298; }
    R(4) = (0 + 0x80310000u);
    R(30) = (0 + 0);
    R(4) = (R(4) + -680);
    st32(base, (R(3) + 0), R(4));
    R(31) = (0 + 0);
    goto L_8007E24C;
L_8007E214:;
    R(0) = ld32(base, (R(28) + 56));
    R(3) = R(0) + R(31);
    R(0) = ld16(base, (R(31) + R(0)));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_8007E244; }
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007E238; }
    GM_CALLV(0x8007E238u, 0x8007EB70u, 0);
L_8007E238:;
    R(0) = ld32(base, (R(28) + 56));
    R(3) = R(0) + R(31);
    GM_CALLV(0x8007E244u, 0x8007EA50u, 0);
L_8007E244:;
    R(31) = (R(31) + 12);
    R(30) = (R(30) + 1);
L_8007E24C:;
    R(0) = ld32(base, (R(28) + 60));
    cr_cmp_s(ctx, 0, (int32_t)R(30), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8007E214; }
    GM_CALLV(0x8007E25Cu, 0x8016A5D0u, 0);
    R(0) = ld32(base, (R(28) + 24));
    cr_cmp_u(ctx, 0, R(0), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_8007E270; }
    R(3) = (R(28) + 4);
    GM_CALLV(0x8007E270u, 0x8016A880u, 0);
L_8007E270:;
    R(0) = (0 + 0);
    st32(base, (R(13) + -22696), R(0));
    R(3) = (R(28) + 4);
    R(4) = (0 + -1);
    st32(base, (R(13) + -22692), R(0));
    GM_CALLV(0x8007E288u, 0x80069060u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8007E298; }
    R(3) = R(28) |R(28);
    GM_CALLV(0x8007E298u, 0x802B9280u, 0);
L_8007E298:;
    R(3) = R(28) |R(28);
    R(0) = lr;
}

/* fn_8007E2C0 (fn_8007E2C0, 264 bytes) */
static void bg_m_7e2c0(GM_CTX) {
    GM_FN(0x8007E2C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = (0 + 0x80310000u);
    R(31) = (R(31) + -2784);
    R(29) = R(3) |R(3);
    R(4) = ld32(base, (R(13) + -21688));
    R(5) = ld32(base, (R(13) + -22504));
    R(0) = ld8(base, (R(4) + 4622));
    R(0) = ((int32_t)R(0) * 944);
    R(3) = R(5) + R(0);
    R(0) = ld32(base, (R(3) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007E308; }
    goto L_8007E30C;
L_8007E308:;
    R(3) = (0 + 0);
L_8007E30C:;
    R(30) = ld32(base, (R(3) + 8));
    R(4) = (R(31) + 2004);
    R(3) = (R(30) + 96);
    GM_CALLV(0x8007E31Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007E330; }
    R(0) = (0 + 1);
    st32(base, (R(29) + 64), R(0));
    goto L_8007E398;
L_8007E330:;
    R(3) = (R(30) + 96);
    R(4) = (R(31) + 2016);
    GM_CALLV(0x8007E33Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007E350; }
    R(0) = (0 + 2);
    st32(base, (R(29) + 64), R(0));
    goto L_8007E398;
L_8007E350:;
    R(3) = (R(30) + 96);
    R(4) = (R(31) + 2032);
    GM_CALLV(0x8007E35Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007E370; }
    R(0) = (0 + 3);
    st32(base, (R(29) + 64), R(0));
    goto L_8007E398;
L_8007E370:;
    R(3) = (R(30) + 96);
    R(4) = (R(31) + 2048);
    GM_CALLV(0x8007E37Cu, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007E390; }
    R(0) = (0 + 4);
    st32(base, (R(29) + 64), R(0));
    goto L_8007E398;
L_8007E390:;
    R(0) = (0 + 0);
    st32(base, (R(29) + 64), R(0));
L_8007E398:;
    R(0) = ld32(base, (R(29) + 64));
    R(3) = (R(31) + 1984);
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(0) = ld32(base, (R(3) + R(0)));
    st32(base, (R(13) + -22692), R(0));
    R(0) = lr;
}

/* fn_8007E3D0 (fn_8007E3D0, 88 bytes) */
static void bg_m_7e3d0(GM_CTX) {
    GM_FN(0x8007E3D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(6) = (0 + 0x80310000u);
    R(4) = (0 + 0x10000u);
    R(6) = (R(6) + -712);
    R(7) = (0 + 32);
    R(8) = (0 + 0);
    R(31) = R(3) |R(3);
    R(3) = (R(3) + 4);
    R(5) = ld32(base, (R(13) + -18544));
    GM_CALLV(0x8007E404u, 0x8016A960u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8007E40Cu, 0x8007E430u, 0);
    R(3) = (R(31) + 4);
    GM_CALLV(0x8007E414u, 0x8016A9B0u, 0);
    R(0) = lr;
}

/* fn_8007E430 (fn_8007E430, 176 bytes) */
static void bg_m_7e430(GM_CTX) {
    GM_FN(0x8007E430); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0);
    R(29) = R(3) |R(3);
    GM_CALLV(0x8007E454u, 0x8007E860u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    st32(base, (R(29) + 60), R(3));
    if ((!CR_BIT(ctx, 1))) { goto L_8007E4C0; }
    R(4) = ((int32_t)R(3) * 12);
    R(31) = R(3) |R(3);
    R(3) = (R(4) + 16);
    GM_CALLV(0x8007E470u, 0x802B9250u, 0);
    R(7) = R(31) |R(31);
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 12);
    GM_CALLV(0x8007E484u, 0x802DC7E0u, 0);
    st32(base, (R(29) + 56), R(3));
    R(30) = (0 + 0);
    R(31) = (0 + 0);
    goto L_8007E4A8;
L_8007E494:;
    R(0) = ld32(base, (R(29) + 56));
    R(3) = R(0) + R(31);
    GM_CALLV(0x8007E4A0u, 0x8007EA30u, 0);
    R(31) = (R(31) + 12);
    R(30) = (R(30) + 1);
L_8007E4A8:;
    R(0) = ld32(base, (R(29) + 60));
    cr_cmp_s(ctx, 0, (int32_t)R(30), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8007E494; }
    R(3) = R(29) |R(29);
    R(4) = (0 + 1);
    GM_CALLV(0x8007E4C0u, 0x8007E860u, 0);
L_8007E4C0:;
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_8007E4E0 (fn_8007E4E0, 64 bytes) */
static void bg_m_7e4e0(GM_CTX) {
    R(4) = ld32(base, (R(13) + -22656));
    { uint32_t ea_ = (R(2) + -29232); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 56); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 32); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(4) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 60); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 36); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(4) + 60); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 48); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[1].d); }
    GM_TAIL(0x8007E520u, 0); return;
}

/* fn_8007E520 (fn_8007E520, 716 bytes) */
static void bg_m_7e520(GM_CTX) {
    GM_FN(0x8007E520); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 176);
    R(0) = ld32(base, (R(3) + 56));
    R(26) = R(3) |R(3);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007E7BC; }
    R(5) = ld32(base, (R(13) + -22704));
    R(27) = (0 + 0);
    R(4) = ld32(base, (R(3) + 32));
    R(30) = (0 + 0);
    R(5) = (R(5) + 0x90000u);
    R(0) = ld32(base, (R(3) + 36));
    { uint32_t ea_ = (R(5) + -412); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(31) = (0 + 0x43300000u);
    { uint32_t ea_ = (R(5) + -404); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29228); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (f + 100), R(4));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -29216); ctx->f[29].u = ld64(base, ea_); }
    st32(base, (f + 104), R(0));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -29232); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    R(0) = ld32(base, (R(3) + 40));
    st32(base, (f + 108), R(0));
    ctx->f[1].u = fctiw_bits(ctx->f[1].d, 1);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (R(2) + -29224); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 128); st64(base, ea_, ctx->f[1].u); }
    R(4) = ld32(base, (R(3) + 44));
    R(0) = ld32(base, (R(3) + 48));
    { uint32_t ea_ = (f + 136); st64(base, ea_, ctx->f[0].u); }
    R(29) = ld32(base, (f + 132));
    st32(base, (f + 88), R(4));
    R(28) = ld32(base, (f + 140));
    st32(base, (f + 92), R(0));
    R(0) = ld32(base, (R(3) + 52));
    st32(base, (f + 96), R(0));
    goto L_8007E7B0;
L_8007E5DC:;
    R(0) = ld32(base, (R(26) + 56));
    R(4) = R(0) + R(30);
    R(0) = ld16(base, (R(30) + R(0)));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_8007E7A8; }
    R(0) = ld16(base, (R(4) + 2));
    R(3) = (f + 52);
    st32(base, (f + 136), R(31));
    R(0) = R(29) + R(0);
    R(0) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    st32(base, (f + 128), R(31));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 140), R(0));
    { uint32_t ea_ = (f + 136); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[29].d);
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld16(base, (R(4) + 4));
    R(0) = -(int32_t)R(0);
    R(0) = R(28) + R(0);
    R(0) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 132), R(0));
    { uint32_t ea_ = (f + 128); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[29].d);
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x8007E644u, 0x8007EBC0u, 0);
    { uint32_t ea_ = (f + 112); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 40);
    { uint32_t ea_ = (f + 52); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(26) + 56));
    R(4) = R(0) + R(30);
    GM_CALLV(0x8007E664u, 0x8007EBC0u, 0);
    { uint32_t ea_ = (f + 116); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 32);
    { uint32_t ea_ = (f + 44); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 112); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[30].d); }
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[30].d); }
    R(0) = ld32(base, (R(26) + 56));
    R(4) = R(0) + R(30);
    GM_CALLV(0x8007E698u, 0x8007EBF0u, 0);
    { uint32_t ea_ = (f + 32); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 24);
    { uint32_t ea_ = (f + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(26) + 56));
    R(4) = R(0) + R(30);
    GM_CALLV(0x8007E6BCu, 0x8007EBF0u, 0);
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 16);
    { uint32_t ea_ = (f + 112); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[31].d * ctx->f[0].d);
    { uint32_t ea_ = (f + 80); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[3].d - ctx->f[4].d);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(26) + 56));
    R(4) = R(0) + R(30);
    GM_CALLV(0x8007E6F8u, 0x8007EBF0u, 0);
    { uint32_t ea_ = (f + 16); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 8);
    { uint32_t ea_ = (f + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(26) + 56));
    R(4) = R(0) + R(30);
    GM_CALLV(0x8007E71Cu, 0x8007EBF0u, 0);
    { uint32_t ea_ = (f + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[0].d); }
    R(0) = ld32(base, (R(26) + 56));
    R(3) = R(0) + R(30);
    R(0) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007E774; }
    { uint32_t ea_ = (R(2) + -29232); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 76);
    R(4) = (f + 64);
    R(5) = (f + 100);
    R(6) = (f + 88);
    GM_CALLV(0x8007E75Cu, 0x800B3100u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8007E7A8; }
    R(0) = ld32(base, (R(26) + 56));
    R(3) = R(0) + R(30);
    GM_CALLV(0x8007E770u, 0x8007EB70u, 0);
    goto L_8007E7A8;
L_8007E774:;
    { uint32_t ea_ = (R(2) + -29232); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 76);
    R(4) = (f + 64);
    R(5) = (f + 100);
    R(6) = (f + 88);
    GM_CALLV(0x8007E78Cu, 0x800B3100u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007E7A8; }
    R(0) = ld32(base, (R(26) + 56));
    R(5) = (f + 112);
    R(4) = (0 + 0);
    R(3) = R(0) + R(30);
    GM_CALLV(0x8007E7A8u, 0x8007EA80u, 0);
L_8007E7A8:;
    R(30) = (R(30) + 12);
    R(27) = (R(27) + 1);
L_8007E7B0:;
    R(0) = ld32(base, (R(26) + 60));
    cr_cmp_s(ctx, 0, (int32_t)R(27), (int32_t)R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8007E5DC; }
L_8007E7BC:;
    R(11) = (f + 176);
    R(0) = lr;
}

/* fn_8007E860 (fn_8007E860, 464 bytes) */
static void bg_m_7e860(GM_CTX) {
    GM_FN(0x8007E860); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 96);
    R(28) = ld32(base, (R(13) + -22704));
    R(19) = R(3) |R(3);
    { uint32_t ea_ = (R(2) + -29228); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(20) = R(4) |R(4);
    R(17) = (R(28) + 0x90000u);
    { uint32_t ea_ = (R(17) + -412); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[0].d);
    GM_CALLV(0x8007E894u, 0x802DCC4Cu, 0);
    { uint32_t ea_ = (R(17) + -404); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(18) = R(17) |R(17);
    { uint32_t ea_ = (R(2) + -29228); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(29) = R(3) |R(3);
    ctx->f[1].u = ctx->f[1].u ^ 0x8000000000000000ull;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[0].d);
    GM_CALLV(0x8007E8B0u, 0x802DCC4Cu, 0);
    { uint32_t ea_ = (R(17) + -412); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(30) = R(3) |R(3);
    { uint32_t ea_ = (R(17) + -408); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(17) + -400); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(18) + -404); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    ctx->f[1].u = fctiw_bits(ctx->f[1].d, 1);
    { uint32_t ea_ = (f + 8); st64(base, ea_, ctx->f[1].u); }
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    R(27) = ld32(base, (f + 12));
    { uint32_t ea_ = (f + 16); st64(base, ea_, ctx->f[0].u); }
    R(0) = R(27) & 0xFu;
    CR0(ctx, R(0));
    R(3) = ld32(base, (f + 20));
    if ((CR_BIT(ctx, 2))) { goto L_8007E8F8; }
    R(27) = rotl32(R(27), 28) & 0xFFFu;
    R(27) = (R(27) + 1);
    goto L_8007E8FC;
L_8007E8F8:;
    R(27) = rotl32(R(27), 28) & 0xFFFu;
L_8007E8FC:;
    R(0) = R(3) & 0xFu;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8007E910; }
    R(3) = rotl32(R(3), 28) & 0xFFFu;
    R(3) = (R(3) + 1);
    goto L_8007E914;
L_8007E910:;
    R(3) = rotl32(R(3), 28) & 0xFFFu;
L_8007E914:;
    R(31) = R(27) & 0xFFFFu;
    R(18) = R(3) & 0xFFFFu;
    R(26) = (0 + 0);
    R(25) = (0 + 0);
    goto L_8007EA08;
L_8007E928:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    R(24) = (0 + 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007EA04; }
    R(0) = R(25) & 0xFFFFu;
    R(17) = R(27) & 0xFFFFu;
    R(0) = R(0) + R(30);
    R(22) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    goto L_8007E9F8;
L_8007E948:;
    R(0) = R(24) & 0xFFFFu;
    R(21) = (0 + 0);
    R(0) = R(0) + R(29);
    R(23) = rotl32(R(0), 4) & 0xFFFFFFF0u;
L_8007E958:;
    R(3) = R(28) |R(28);
    R(4) = R(21) & 0xFFu;
    GM_CALLV(0x8007E964u, 0x80077980u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007E9E8; }
    R(3) = R(28) |R(28);
    R(4) = R(23) & 0xFFFFu;
    R(5) = R(22) & 0xFFFFu;
    R(6) = R(21) & 0xFFu;
    GM_CALLV(0x8007E980u, 0x80077610u, 0);
    R(0) = R(3) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((!CR_BIT(ctx, 2))) { goto L_8007E990; }
    R(3) = (0 + 0);
L_8007E990:;
    R(4) = ld32(base, (R(13) + -22692));
    R(3) = R(3) & 0xFFFFu;
    R(5) = (0 + 0);
    goto L_8007E9DC;
L_8007E9A0:;
    R(0) = ld32(base, (R(4) + 0));
    cr_cmp_u(ctx, 0, R(3), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8007E9D4; }
    cr_cmp_s(ctx, 0, (int32_t)R(20), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007E9CC; }
    R(4) = R(5) & 0xFFFFu;
    R(3) = R(19) |R(19);
    R(5) = R(24) & 0xFFFFu;
    R(6) = R(25) & 0xFFFFu;
    R(7) = R(21) & 0xFFu;
    GM_CALLV(0x8007E9CCu, 0x8007E7F0u, 0);
L_8007E9CC:;
    R(26) = (R(26) + 1);
    goto L_8007E9E8;
L_8007E9D4:;
    R(4) = (R(4) + 32);
    R(5) = (R(5) + 1);
L_8007E9DC:;
    R(0) = ld16(base, (R(4) + 4));
    cr_cmp_u(ctx, 0, R(0), 0x2EBu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_8007E9A0; }
L_8007E9E8:;
    R(21) = (R(21) + 1);
    cr_cmp_u(ctx, 0, R(21), 0x3u);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8007E958; }
    R(24) = (R(24) + 1);
L_8007E9F8:;
    R(0) = R(24) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), R(17));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8007E948; }
L_8007EA04:;
    R(25) = (R(25) + 1);
L_8007EA08:;
    R(0) = R(25) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), R(18));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8007E928; }
    R(11) = (f + 96);
    R(3) = R(26) |R(26);
    R(0) = lr;
}

/* fn_8007EC20 (fn_8007EC20, 2740 bytes) */
static void bg_m_7ec20(GM_CTX) {
    GM_FN(0x8007EC20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -29232); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(4) = (0 + 0x80080000u);
    R(4) = (R(4) + -2336);
    { uint32_t ea_ = (R(2) + -29196); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (0 + 0);
    R(31) = (0 + 0x80310000u);
    R(31) = (R(31) + -2784);
    { uint32_t ea_ = (R(2) + -29204); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(6) = (R(31) + 0);
    { uint32_t ea_ = (R(2) + -29200); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(30) = (0 + 0x80350000u);
    R(30) = (R(30) + 24368);
    { uint32_t ea_ = (f + 1236); stfs(base, ea_, ctx->f[3].d); }
    R(5) = (R(30) + 0);
    { uint32_t ea_ = (f + 1240); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 1244); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 8); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 16); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 496); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 500); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 20); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 1224); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 1228); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 1232); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 40); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 44); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 48); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 488); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 492); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 56); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x8007ECBCu, 0x802DC780u, 0);
    { uint32_t ea_ = (R(2) + -29196); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(6) = (R(31) + 64);
    { uint32_t ea_ = (R(2) + -29232); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29204); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29200); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29188); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29192); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29184); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 1212); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1216); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1220); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 8); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 12); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 480); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 484); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 20); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1200); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1204); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1208); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 40); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 44); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 472); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 476); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 52); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 56); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1188); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1192); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1196); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 72); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 76); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 80); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 464); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 468); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 84); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 88); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1176); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1180); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1184); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 104); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 108); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 112); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 456); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 460); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 116); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 120); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1164); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1168); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 1172); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 136); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 140); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 144); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 448); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 452); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 148); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 152); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 1152); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1156); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 1160); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 168); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 172); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 176); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 440); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 444); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 180); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 184); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 1140); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1144); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1148); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 200); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 204); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 208); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 432); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 436); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 212); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 216); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1128); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1132); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1136); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 232); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 236); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 240); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 424); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 428); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 244); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 248); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1116); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 1120); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1124); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(2) + -29180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + 264); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 268); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 272); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 416); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 420); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 276); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 280); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1104); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 1108); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1112); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 296); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 300); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 304); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 408); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 412); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 308); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 312); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1092); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1096); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1100); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 328); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 332); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 336); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 400); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 404); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 340); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 344); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1080); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 1084); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 1088); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 360); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 364); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 368); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 392); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 396); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 372); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 376); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 1068); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 1072); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 1076); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 392); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 396); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 400); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 384); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 388); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 404); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 408); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 1056); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 1060); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 1064); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 424); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 428); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 432); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 376); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 380); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 436); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 440); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 1044); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 1048); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 1052); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 456); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 460); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 464); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 368); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 372); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 468); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 472); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 1032); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1036); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1040); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 488); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 492); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 496); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 360); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 364); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 500); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 504); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1020); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1024); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1028); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 520); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 524); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 528); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 352); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 356); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 532); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 536); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 1008); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1012); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1016); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 552); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 556); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 560); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 344); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 348); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 564); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 568); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 996); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 1000); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 1004); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 584); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 588); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 592); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 336); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 340); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 596); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 600); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 984); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 988); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 992); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 616); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 620); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 624); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 328); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 332); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 628); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 632); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 972); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 976); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 980); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 648); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 652); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 656); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 320); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 324); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 660); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 664); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 960); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 964); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 968); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 680); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 684); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 688); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 312); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 316); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 692); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 696); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 948); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 952); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 956); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 712); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 716); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 720); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 304); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 308); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 724); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 728); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 936); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 940); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 944); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 744); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 748); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 752); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 296); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 300); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 756); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 760); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 924); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 928); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 932); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 776); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 780); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 784); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 288); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 292); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 788); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 792); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 912); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 916); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 920); stfs(base, ea_, ctx->f[4].d); }
    R(4) = (0 + 0x80080000u);
    { uint32_t ea_ = (R(6) + 808); stfs(base, ea_, ctx->f[6].d); }
    R(4) = (R(4) + -2240);
    R(5) = (R(30) + 12);
    { uint32_t ea_ = (R(6) + 812); stfs(base, ea_, ctx->f[5].d); }
    R(3) = (0 + 0);
    { uint32_t ea_ = (R(6) + 816); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 280); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 284); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 820); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 824); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 900); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 904); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 908); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 840); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 844); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 848); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 272); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 276); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 852); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 856); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 888); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 892); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 896); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 872); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 876); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 880); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 264); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 268); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 884); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 888); stfs(base, ea_, ctx->f[4].d); }
    GM_CALLV(0x8007F154u, 0x802DC780u, 0);
    { uint32_t ea_ = (R(2) + -29196); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(6) = (R(31) + 960);
    { uint32_t ea_ = (R(2) + -29232); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29200); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29204); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29188); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29184); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29180); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 876); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 880); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 884); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 8); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 12); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 256); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 260); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 20); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 864); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 868); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 872); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 40); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 44); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 248); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 252); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 52); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 56); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 852); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 856); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 860); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 72); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 76); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 80); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 240); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 244); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 84); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 88); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 840); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 844); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 848); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 104); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 108); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 112); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 232); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 236); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 116); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 120); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 828); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 832); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 836); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 136); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 140); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 144); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 224); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 228); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 148); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 152); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 816); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 820); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 824); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 168); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 172); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 176); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 216); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 220); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 180); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 184); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 804); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 808); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 812); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 200); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 204); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 208); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 208); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 212); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 212); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 216); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 792); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 796); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 800); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 232); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 236); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 240); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 200); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 204); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 244); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 248); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 780); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 784); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 788); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 264); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 268); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 272); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 192); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 196); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 276); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 280); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 768); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 772); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 776); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 296); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 300); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 304); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 184); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 188); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 308); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 312); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 756); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 760); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 764); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 328); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 332); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 336); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 176); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 180); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 340); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 344); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 744); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 748); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 752); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 360); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 364); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 368); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 168); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 172); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 372); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 376); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 732); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 736); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 740); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 392); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 396); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 400); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 160); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 164); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 404); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 408); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 720); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 724); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 728); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 424); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 428); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 432); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 152); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 156); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 436); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 440); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 708); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 712); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 716); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 456); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 460); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 464); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 144); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 148); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 468); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 472); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 696); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 700); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 704); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 488); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 492); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 496); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 136); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 140); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 500); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 504); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 684); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 688); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 692); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 520); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 524); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 528); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 128); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 132); stfs(base, ea_, ctx->f[3].d); }
    R(4) = (0 + 0x80080000u);
    { uint32_t ea_ = (R(6) + 532); stfs(base, ea_, ctx->f[3].d); }
    R(4) = (R(4) + -2208);
    R(5) = (R(30) + 24);
    { uint32_t ea_ = (R(6) + 536); stfs(base, ea_, ctx->f[3].d); }
    R(3) = (0 + 0);
    { uint32_t ea_ = (f + 672); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 676); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 680); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 552); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 556); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 560); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 124); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 564); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 568); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 660); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 664); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 668); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 584); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 588); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 592); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 596); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 600); stfs(base, ea_, ctx->f[4].d); }
    GM_CALLV(0x8007F480u, 0x802DC780u, 0);
    { uint32_t ea_ = (R(2) + -29196); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(6) = (R(31) + 1568);
    { uint32_t ea_ = (R(2) + -29232); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29204); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29200); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29188); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29180); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29184); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 648); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 652); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 656); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 8); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 12); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 20); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 636); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 640); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 644); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 40); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 44); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 48); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 52); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 56); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 624); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 628); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 632); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 72); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 76); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 80); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 88); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 84); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 88); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 612); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 616); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 620); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 104); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 108); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 112); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 80); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 84); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 116); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 120); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 600); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 604); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 608); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 136); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 140); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 144); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 72); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 76); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 148); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 152); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 588); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 592); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 596); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 168); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 172); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 176); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 180); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 184); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 576); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 580); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 584); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 200); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(6) + 204); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 208); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 212); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 216); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 564); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 568); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 572); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 232); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 236); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(6) + 240); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(6) + 244); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 248); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 552); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 556); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 560); stfs(base, ea_, ctx->f[4].d); }
    R(4) = (0 + 0x80080000u);
    { uint32_t ea_ = (R(6) + 264); stfs(base, ea_, ctx->f[6].d); }
    R(4) = (R(4) + -2176);
    R(5) = (R(30) + 36);
    { uint32_t ea_ = (R(6) + 268); stfs(base, ea_, ctx->f[5].d); }
    R(3) = (0 + 0);
    { uint32_t ea_ = (R(6) + 272); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 276); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 280); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 540); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 544); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 548); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 296); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 300); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 304); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 308); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 312); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 528); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 532); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 536); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 328); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 332); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 336); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 340); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 344); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 516); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 520); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 524); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 360); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (R(6) + 364); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (R(6) + 368); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 372); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(6) + 376); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 504); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 508); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 512); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 392); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 396); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 400); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 404); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(6) + 408); stfs(base, ea_, ctx->f[4].d); }
    GM_CALLV(0x8007F6BCu, 0x802DC780u, 0);
    R(0) = lr;
}

/* __ct__9dBg_ctr_cFv (__ct__9dBg_ctr_cFv, 84 bytes) */
static void bg___ct__9dBg_ctr_cFv_7f7a0(GM_CTX) {
    GM_FN(0x8007F7A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 0x80080000u);
    R(5) = (0 + 0x80000000u);
    R(4) = (R(4) + -2048);
    R(5) = (R(5) + 28144);
    R(6) = (0 + 8);
    R(31) = R(3) |R(3);
    R(7) = (0 + 4);
    R(3) = (R(3) + 96);
    GM_CALLV(0x8007F7D4u, 0x802DC9A0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8007F7DCu, 0x8007F8A0u, 0);
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_8007F800 (fn_8007F800, 4 bytes) */
static void bg_m_7f800(GM_CTX) {

}

/* __dt__9dBg_ctr_cFv (__dt__9dBg_ctr_cFv, 108 bytes) */
static void bg___dt__9dBg_ctr_cFv_7f810(GM_CTX) {
    GM_FN(0x8007F810); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_8007F860; }
    GM_CALLV(0x8007F838u, 0x8007F950u, 0);
    R(4) = (0 + 0x80000000u);
    R(3) = (R(30) + 96);
    R(4) = (R(4) + 28144);
    R(5) = (0 + 8);
    R(6) = (0 + 4);
    GM_CALLV(0x8007F850u, 0x802DCA98u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8007F860; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007F860u, 0x802B9280u, 0);
L_8007F860:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_8007F880 (fn_8007F880, 24 bytes) */
static void bg_m_7f880(GM_CTX) {
    R(0) = (0 + 0);
    st32(base, (R(13) + -22688), R(0));
    st32(base, (R(13) + -22684), R(0));
    st32(base, (R(13) + -22680), R(0));
    st32(base, (R(13) + -22676), R(0));
}

/* fn_8007F8A0 (fn_8007F8A0, 84 bytes) */
static void bg_m_7f8a0(GM_CTX) {
    { uint32_t ea_ = (R(2) + -29176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (0 + 0);
    R(0) = (0 + -1);
    st32(base, (R(3) + 4), R(4));
    st32(base, (R(3) + 8), R(4));
    st32(base, (R(3) + 12), R(4));
    st32(base, (R(3) + 16), R(4));
    st32(base, (R(3) + 20), R(4));
    st32(base, (R(3) + 24), R(4));
    st32(base, (R(3) + 40), R(4));
    st32(base, (R(3) + 28), R(4));
    st32(base, (R(3) + 44), R(4));
    st32(base, (R(3) + 32), R(4));
    st32(base, (R(3) + 48), R(4));
    st32(base, (R(3) + 36), R(4));
    st32(base, (R(3) + 52), R(4));
    st8(base, (R(3) + 220), R(4));
    st32(base, (R(3) + 224), R(0));
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[0].d); }
}

/* entry__9dBg_ctr_cFv (entry__9dBg_ctr_cFv, 72 bytes) */
static void bg_entry__9dBg_ctr_cFv_7f900(GM_CTX) {
    R(0) = ld8(base, (R(3) + 220));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) return;
    R(4) = ld32(base, (R(13) + -22688));
    st32(base, (R(3) + 4), R(4));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    st32(base, (R(13) + -22688), R(3));
    if ((!CR_BIT(ctx, 2))) { goto L_8007F930; }
    R(0) = ld32(base, (R(13) + -22684));
    st32(base, (R(3) + 8), R(0));
    st32(base, (R(13) + -22684), R(3));
    goto L_8007F93C;
L_8007F930:;
    R(0) = ld32(base, (R(4) + 8));
    st32(base, (R(3) + 8), R(0));
    st32(base, (R(4) + 8), R(3));
L_8007F93C:;
    R(0) = (0 + 1);
    st8(base, (R(3) + 220), R(0));
}

/* release__9dBg_ctr_cFv (release__9dBg_ctr_cFv, 84 bytes) */
static void bg_release__9dBg_ctr_cFv_7f950(GM_CTX) {
    R(0) = ld8(base, (R(3) + 220));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) return;
    R(4) = ld32(base, (R(3) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007F974; }
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (R(4) + 8), R(0));
    goto L_8007F97C;
L_8007F974:;
    R(0) = ld32(base, (R(3) + 8));
    st32(base, (R(13) + -22684), R(0));
L_8007F97C:;
    R(4) = ld32(base, (R(3) + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007F994; }
    R(0) = ld32(base, (R(3) + 4));
    st32(base, (R(4) + 4), R(0));
    goto L_8007F99C;
L_8007F994:;
    R(0) = ld32(base, (R(3) + 4));
    st32(base, (R(13) + -22688), R(0));
L_8007F99C:;
    GM_TAIL(0x8007F8A0u, 0); return;
}

/* baseSetup__7PhysicsFP8dActor_cPvPvPvUcUc (baseSetup__7PhysicsFP8dActor_cPvPvPvUcUc, 144 bytes) */
static void bg_baseSetup__7PhysicsFP8dActor_cPvPvPvUcUc_7f9b0(GM_CTX) {
    GM_FRAME(16); gptr f = gm_frame_sp;
    R(12) = (0 + 0x80080000u);
    R(11) = (0 + 0x80080000u);
    R(10) = (0 + 0x80080000u);
    st32(base, (f + 12), R(31));
    R(31) = (R(4) + 260);
    { uint32_t ea_ = (R(2) + -29176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(12) = (R(12) + 3520);
    st32(base, (R(3) + 0), R(4));
    R(11) = (R(11) + 3552);
    R(10) = (R(10) + 3584);
    st32(base, (R(3) + 188), R(31));
    R(0) = (int16_t)ld16(base, (R(4) + 260));
    st16(base, (R(3) + 192), R(0));
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[0].d); }
    st32(base, (R(3) + 64), R(5));
    st32(base, (R(3) + 68), R(6));
    st32(base, (R(3) + 72), R(7));
    st8(base, (R(3) + 221), R(8));
    st8(base, (R(3) + 222), R(9));
    st32(base, (R(3) + 76), R(12));
    st32(base, (R(3) + 80), R(11));
    st32(base, (R(3) + 84), R(10));
    R(0) = ld32(base, (R(13) + -22680));
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((CR_BIT(ctx, 2))) { goto L_8007FA2C; }
    R(5) = ld32(base, (R(13) + -22676));
    st32(base, (R(13) + -22680), R(4));
    R(0) = (R(5) + 1);
    st32(base, (R(13) + -22676), R(0));
L_8007FA2C:;
    R(0) = ld32(base, (R(13) + -22676));
    st32(base, (R(3) + 224), R(0));
    R(31) = ld32(base, (f + 12));
}

/* set__9dBg_ctr_cFP8dActor_cffffPFP8dActor_cP8dActor_c_vPFP8dActor_cP8dActor_c_vPFP8dActor_cP8dActor_cUc_vUcUcP7mVec3_c (set__9dBg_ctr_cFP8dActor_cffffPFP8dActor_cP8dActor_c_vPFP8dActor_cP8dActor_c_vPFP8dActor_cP8dActor_cUc_vUcUcP7mVec3_c, 132 bytes) */
static void bg_set__9dBg_ctr_cFP8dActor_cffffPFP8dActor_7fa40(GM_CTX) {
    GM_FN(0x8007FA40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    GM_CALLV(0x8007FA54u, 0x802DCCE0u, 0);
    ctx->f[28].u = ctx->f[1].u;
    R(30) = R(3) |R(3);
    ctx->f[29].u = ctx->f[2].u;
    R(31) = R(10) |R(10);
    ctx->f[30].u = ctx->f[3].u;
    ctx->f[31].u = ctx->f[4].u;
    GM_CALLV(0x8007FA78u, 0x8007F9B0u, 0);
    ctx->f[1].u = ctx->f[28].u;
    R(3) = R(30) |R(30);
    ctx->f[2].u = ctx->f[29].u;
    R(4) = R(31) |R(31);
    ctx->f[3].u = ctx->f[30].u;
    ctx->f[4].u = ctx->f[31].u;
    GM_CALLV(0x8007FA94u, 0x8007FBF0u, 0);
    R(0) = (0 + 0);
    st32(base, (R(30) + 200), R(0));
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007FAA4u, 0x8007FDA0u, 0);
    R(11) = (f + 48);
    GM_CALLV(0x8007FAACu, 0x802DCD2Cu, 0);
    R(0) = lr;
}

/* fn_8007FAD0 (fn_8007FAD0, 52 bytes) */
static void bg_m_7fad0(GM_CTX) {
    gptr f = R(1);                                                           /* (the caller's frame: stack arguments) */
    R(12) = R(5) |R(5);
    R(11) = R(6) |R(6);
    R(5) = R(7) |R(7);
    R(6) = R(8) |R(8);
    R(7) = R(9) |R(9);
    R(8) = R(10) |R(10);
    R(9) = ld8(base, (f + 11));
    R(10) = ld32(base, (f + 12));
    { uint32_t ea_ = (R(12) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(12) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(11) + 0); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(11) + 4); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    GM_TAIL(0x8007FA40u, 0); return;
}

/* setup__7PhysicsFP8dActor_cPQ27Physics4InfoUcUcP7Point2d (setup__7PhysicsFP8dActor_cPQ27Physics4InfoUcUcP7Point2d, 100 bytes) */
static void bg_setup__7PhysicsFP8dActor_cPQ27Physics4In_7fb10(GM_CTX) {
    GM_FN(0x8007FB10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = R(5) |R(5);
    R(10) = R(6) |R(6);
    R(6) = (f + 16);
    { uint32_t ea_ = (R(5) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 12); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(5) = (f + 24);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[1].d); }
    R(9) = ld32(base, (R(11) + 24));
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[2].d); }
    st32(base, (f + 8), R(7));
    R(7) = ld32(base, (R(11) + 16));
    st32(base, (f + 12), R(8));
    R(8) = ld32(base, (R(11) + 20));
    GM_CALLV(0x8007FB64u, 0x8007FAD0u, 0);
    R(0) = lr;
}

/* setOfs__9dBg_ctr_cFffffP7mVec3_c (setOfs__9dBg_ctr_cFffffP7mVec3_c, 204 bytes) */
static void bg_setOfs__9dBg_ctr_cFffffP7mVec3_c_7fbf0(GM_CTX) {
    GM_FN(0x8007FBF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    { uint32_t ea_ = (R(2) + -29172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    ctx->f[31].u = ctx->f[4].u;
    ctx->f[30].u = ctx->f[3].u;
    ctx->f[29].u = ctx->f[2].u;
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_8007FC50; }
    { uint32_t ea_ = (R(4) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
L_8007FC50:;
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[0].d);
    GM_CALLV(0x8007FC60u, 0x8007FCE0u, 0);
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[29].d * ctx->f[0].d);
    GM_CALLV(0x8007FC70u, 0x8007FD10u, 0);
    { uint32_t ea_ = (f + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d * ctx->f[0].d);
    GM_CALLV(0x8007FC80u, 0x8007FD40u, 0);
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = R(31) |R(31);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[0].d);
    GM_CALLV(0x8007FC90u, 0x8007FD60u, 0);
    R(0) = lr;
}

/* fn_8007FCE0 (fn_8007FCE0, 44 bytes) */
static void bg_m_7fce0(GM_CTX) {
    R(4) = ld32(base, (R(3) + 0));
    R(0) = ld32(base, (R(3) + 208));
    { uint32_t ea_ = (R(4) + 208); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 128); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 128); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) return;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 176); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_8007FD10 (fn_8007FD10, 44 bytes) */
static void bg_m_7fd10(GM_CTX) {
    R(4) = ld32(base, (R(3) + 0));
    R(0) = ld32(base, (R(3) + 208));
    { uint32_t ea_ = (R(4) + 212); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 132); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(0) = R(0) & 0x1u;
    CR0(ctx, R(0));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 132); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) return;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (R(3) + 180); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_8007FD40 (fn_8007FD40, 20 bytes) */
static void bg_m_7fd40(GM_CTX) {
    R(4) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(4) + 208); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 136); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_8007FD60 (fn_8007FD60, 20 bytes) */
static void bg_m_7fd60(GM_CTX) {
    R(4) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(4) + 212); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 140); stfs(base, ea_, ctx->f[0].d); }
}

/* setPtrToRotation__7PhysicsFPs (setPtrToRotation__7PhysicsFPs, 28 bytes) */
static void bg_setPtrToRotation__7PhysicsFPs_7fd80(GM_CTX) {
    R(0) = ld32(base, (R(3) + 188));
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((CR_BIT(ctx, 2))) return;
    st32(base, (R(3) + 188), R(4));
    R(0) = (int16_t)ld16(base, (R(4) + 0));
    st16(base, (R(3) + 192), R(0));
}

/* calc__9dBg_ctr_cFv (calc__9dBg_ctr_cFv, 500 bytes) */
static void bg_calc__9dBg_ctr_cFv_7fda0(GM_CTX) {
    GM_FN(0x8007FDA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = (0 + 1);
    R(30) = R(3) |R(3);
    st32(base, (R(3) + 60), R(0));
    R(3) = (f + 32);
    R(4) = ld32(base, (R(30) + 0));
    GM_CALLV(0x8007FDDCu, 0x8006CED0u, 0);
    { uint32_t ea_ = (f + 32); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    GM_CALLV(0x8007FDE4u, 0x80101AA0u, 0);
    { uint32_t ea_ = (f + 32); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 88); stfs(base, ea_, ctx->f[3].d); }
    R(0) = ld32(base, (R(30) + 200));
    { uint32_t ea_ = (f + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 92); stfs(base, ea_, ctx->f[2].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    R(3) = ld32(base, (R(30) + 188));
    R(0) = (int16_t)ld16(base, (R(30) + 192));
    R(31) = (int16_t)ld16(base, (R(3) + 0));
    { uint32_t ea_ = (R(30) + 160); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = R(31) - R(0);
    { uint32_t ea_ = (R(30) + 164); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st16(base, (R(30) + 194), R(0));
    st16(base, (R(30) + 196), R(0));
    { uint32_t ea_ = (R(30) + 168); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 172); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_8007FE4C; }
    { uint32_t ea_ = (R(30) + 128); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 132); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 88); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 92); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 160); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(30) + 164); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007FF44;
L_8007FE4C:;
    st16(base, (f + 10), R(31));
    R(3) = (f + 10);
    { uint32_t ea_ = (R(3) + 0); psq_l(ctx, base, 1, ea_, 1, 3); }
    { uint32_t ea_ = (R(2) + -29168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    GM_CALLV(0x8007FE64u, 0x80237C40u, 0);
    st16(base, (f + 8), R(31));
    R(3) = (f + 8);
    ctx->f[31].u = ctx->f[1].u;
    { uint32_t ea_ = (R(3) + 0); psq_l(ctx, base, 1, ea_, 1, 3); }
    { uint32_t ea_ = (R(2) + -29168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    GM_CALLV(0x8007FE80u, 0x80237BD0u, 0);
    { uint32_t ea_ = (R(30) + 132); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 128); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 140); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[13].d = ctx->ps1[13] = frsp(ctx->f[7].d * ctx->f[31].d);
    { uint32_t ea_ = (R(30) + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[12].d = ctx->ps1[12] = frsp(ctx->f[4].d * ctx->f[1].d);
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[4].d * ctx->f[31].d);
    { uint32_t ea_ = (R(30) + 92); ctx->f[10].d = ctx->ps1[10] = ldfs(base, ea_); }
    ctx->f[8].d = ctx->ps1[8] = frsp(ctx->f[7].d * ctx->f[1].d);
    ctx->f[11].d = ctx->ps1[11] = frsp(ctx->f[13].d + ctx->f[12].d);
    { uint32_t ea_ = (R(30) + 88); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[2].d * ctx->f[31].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[2].d * ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -29164); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d * ctx->f[31].d);
    ctx->f[11].d = ctx->ps1[11] = frsp(ctx->f[10].d + ctx->f[11].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d + ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[4].d);
    { uint32_t ea_ = (R(30) + 100); stfs(base, ea_, ctx->f[11].d); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[9].d - ctx->f[8].d);
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[10].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[6].d + ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[6].d + ctx->f[7].d);
    { uint32_t ea_ = (R(30) + 116); stfs(base, ea_, ctx->f[31].d); }
    ctx->f[7].d = ctx->ps1[7] = frsp(ctx->f[11].d + ctx->f[31].d);
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[5].d + ctx->f[12].d);
    { uint32_t ea_ = (R(30) + 96); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[11].d = ctx->ps1[11] = frsp(ctx->f[1].d + ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[13].d + ctx->f[3].d);
    { uint32_t ea_ = (R(30) + 112); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[12].d = ctx->ps1[12] = frsp(ctx->f[7].d * ctx->f[30].d);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[9].d - ctx->f[4].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[11].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d - ctx->f[8].d);
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[11].d * ctx->f[30].d);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[7].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[10].d + ctx->f[5].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[6].d + ctx->f[4].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[9].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[10].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[6].d + ctx->f[0].d);
    { uint32_t ea_ = (R(30) + 108); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(30) + 104); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(30) + 120); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(30) + 124); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[12].d); }
    { uint32_t ea_ = (R(30) + 160); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(30) + 164); stfs(base, ea_, ctx->f[12].d); }
L_8007FF44:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x8007FF4Cu, 0x80080170u, 0);
    R(3) = ld32(base, (R(30) + 0));
    { uint32_t ea_ = (R(3) + 172); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 148); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 152); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 156); stfs(base, ea_, ctx->f[0].d); }
    st16(base, (R(30) + 192), R(31));
    R(0) = lr;
}

/* fn_8007FFA0 (fn_8007FFA0, 460 bytes) */
static void bg_m_7ffa0(GM_CTX) {
    GM_FN(0x8007FFA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(0) = ld32(base, (R(3) + 208));
    R(29) = R(3) |R(3);
    { uint32_t ea_ = (R(2) + -29176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(27) = R(4) |R(4);
    R(0) = R(0) & 0x2u;
    CR0(ctx, R(0));
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    R(31) = ld32(base, (R(4) + 20));
    R(28) = R(6) |R(6);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_8008000C; }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    { uint32_t ea_ = (R(5) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    if ((!CR_BIT(ctx, 2))) { goto L_8007FFF8; }
    { uint32_t ea_ = (R(4) + 216); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[0].d);
L_8007FFF8:;
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
    { uint32_t ea_ = (R(4) + 220); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
L_8008000C:;
    { uint32_t ea_ = (f + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (int16_t)ld16(base, (R(3) + 194));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
    if ((CR_BIT(ctx, 2))) { goto L_800800D0; }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 2);
    if ((CR_BIT(ctx, 2))) { goto L_80080038; }
    R(30) = (R(4) + 52);
    goto L_8008003C;
L_80080038:;
    R(30) = (R(4) + 60);
L_8008003C:;
    { uint32_t ea_ = (R(30) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d * ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    GM_CALLV(0x80080054u, 0x802BE470u, 0);
    ctx->f[31].u = ctx->f[1].u;
    { uint32_t ea_ = (R(30) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    GM_CALLV(0x80080064u, 0x80237ED0u, 0);
    R(0) = (int16_t)ld16(base, (R(29) + 194));
    R(4) = (f + 10);
    R(0) = R(0) + R(3);
    st16(base, (f + 10), R(0));
    R(29) = (int16_t)R(0);
    { uint32_t ea_ = (R(4) + 0); psq_l(ctx, base, 1, ea_, 1, 3); }
    { uint32_t ea_ = (R(2) + -29168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    GM_CALLV(0x80080088u, 0x80237C40u, 0);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[31].d * ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (f + 8);
    st16(base, (f + 8), R(29));
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 0); psq_l(ctx, base, 1, ea_, 1, 3); }
    { uint32_t ea_ = (R(2) + -29168); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d * ctx->f[1].d);
    GM_CALLV(0x800800B8u, 0x80237BD0u, 0);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[31].d * ctx->f[1].d);
    { uint32_t ea_ = (R(30) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d - ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[0].d); }
L_800800D0:;
    cr_cmp_s(ctx, 0, (int32_t)R(28), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800800EC; }
    { uint32_t ea_ = (R(2) + -29176); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_800800EC; }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
L_800800EC:;
    { uint32_t ea_ = (R(31) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    GM_CALLV(0x800800FCu, 0x80101AA0u, 0);
    { uint32_t ea_ = (R(31) + 0); stfs(base, ea_, ctx->f[1].d); }
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 4); stfs(base, ea_, ctx->f[0].d); }
    if ((!CR_BIT(ctx, 2))) { goto L_8008014C; }
    R(3) = ld32(base, (R(27) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8008014C; }
    { uint32_t ea_ = (f + 24); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 784); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 784); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 788); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 788); stfs(base, ea_, ctx->f[0].d); }
L_8008014C:;
    R(11) = (f + 64);
    R(0) = lr;
}

/* fn_80080170 (fn_80080170, 288 bytes) */
static void bg_m_80170(GM_CTX) {
    GM_FN(0x80080170); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(29) = R(3) |R(3);
    R(4) = ld32(base, (R(3) + 0));
    { uint32_t ea_ = (R(3) + 156); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 180); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 176); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 152); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 172); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 148); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 180); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    R(31) = ld32(base, (R(3) + 12));
    goto L_800801F8;
L_800801E0:;
    R(3) = R(29) |R(29);
    R(4) = R(31) |R(31);
    R(5) = (f + 8);
    R(6) = (0 + 0);
    GM_CALLV(0x800801F4u, 0x8007FFA0u, 0);
    R(31) = ld32(base, (R(31) + 108));
L_800801F8:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_800801E0; }
    R(31) = R(29) |R(29);
    R(30) = (0 + 0);
L_80080208:;
    R(4) = ld32(base, (R(31) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80080224; }
    R(3) = R(29) |R(29);
    R(5) = (f + 8);
    R(6) = (0 + 1);
    GM_CALLV(0x80080224u, 0x8007FFA0u, 0);
L_80080224:;
    R(30) = (R(30) + 1);
    R(31) = (R(31) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80080208; }
    R(31) = R(29) |R(29);
    R(30) = (0 + 0);
L_8008023C:;
    R(4) = ld32(base, (R(31) + 40));
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80080258; }
    R(3) = R(29) |R(29);
    R(5) = (f + 8);
    R(6) = (0 + 2);
    GM_CALLV(0x80080258u, 0x8007FFA0u, 0);
L_80080258:;
    R(30) = (R(30) + 1);
    R(31) = (R(31) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8008023C; }
    { uint32_t ea_ = (R(2) + -29176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(29) + 176); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(29) + 180); stfs(base, ea_, ctx->f[0].d); }
    R(0) = lr;
}

/* fn_80080530 (fn_80080530, 156 bytes) */
static void bg_m_80530(GM_CTX) {
    R(0) = ld32(base, (R(3) + 40));
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_80080544; }
    R(3) = (0 + 1);
    return;
L_80080544:;
    R(0) = ld32(base, (R(3) + 44));
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_80080558; }
    R(3) = (0 + 1);
    return;
L_80080558:;
    R(0) = ld32(base, (R(3) + 48));
    R(5) = (R(3) + 8);
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_80080570; }
    R(3) = (0 + 1);
    return;
L_80080570:;
    R(0) = ld32(base, (R(5) + 44));
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_80080584; }
    R(3) = (0 + 1);
    return;
L_80080584:;
    R(0) = (0 + 4);
    R(5) = R(3) |R(3);
    R(6) = (0 + 0);
    ctx->ctr = R(0);
    R(0) = R(0) | 0x0u;
L_80080598:;
    R(0) = ld32(base, (R(5) + 40));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800805B8; }
    R(0) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(5) = R(3) + R(0);
    R(3) = (0 + 1);
    st32(base, (R(5) + 40), R(4));
    return;
L_800805B8:;
    R(5) = (R(5) + 4);
    R(6) = (R(6) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80080598; }
    R(3) = (0 + 0);
}

/* fn_800805D0 (fn_800805D0, 88 bytes) */
static void bg_m_805d0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 60));
    R(5) = (0 + 0);
    R(4) = ld32(base, (R(3) + 216));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    st32(base, (R(3) + 12), R(5));
    R(0) = R(4) & 0x1u;
    st32(base, (R(3) + 16), R(5));
    st32(base, (R(3) + 20), R(5));
    st32(base, (R(3) + 24), R(5));
    st32(base, (R(3) + 40), R(5));
    st32(base, (R(3) + 28), R(5));
    st32(base, (R(3) + 44), R(5));
    st32(base, (R(3) + 32), R(5));
    st32(base, (R(3) + 48), R(5));
    st32(base, (R(3) + 36), R(5));
    st32(base, (R(3) + 52), R(5));
    st32(base, (R(3) + 216), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080620; }
    st32(base, (R(3) + 60), R(5));
    return;
L_80080620:;
    st16(base, (R(3) + 196), R(5));
}

/* fn_80080630 (fn_80080630, 64 bytes) */
static void bg_m_80630(GM_CTX) {
    GM_FN(0x80080630); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = ld32(base, (R(13) + -22688));
    goto L_80080654;
L_80080648:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x80080650u, 0x800805D0u, 0);
    R(31) = ld32(base, (R(31) + 4));
L_80080654:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_80080648; }
    R(0) = lr;
}

/* fn_80080670 (fn_80080670, 520 bytes) */
static void bg_m_80670(GM_CTX) {
    GM_FN(0x80080670); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800806A0; }
    R(3) = (0 + 0);
    goto L_80080860;
L_800806A0:;
    R(0) = ld32(base, (R(3) + 200));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_80080714; }
    { uint32_t ea_ = (R(3) + 88); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 92); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    R(3) = (f + 24);
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -29176); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[5].d - ctx->f[1].d);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[4].d); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[4].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 68); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 28); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[2].d); }
    GM_CALLV(0x800806F4u, 0x801C14C0u, 0);
    { uint32_t ea_ = (R(30) + 144); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    R(0) = ctx->cr;
    R(0) = rotl32(R(0), 3) & 0x1u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8008085C; }
    R(3) = (0 + 1);
    goto L_80080860;
L_80080714:;
    R(5) = ld32(base, (R(3) + 188));
    R(0) = (int16_t)ld16(base, (R(5) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8008077C; }
    { uint32_t ea_ = (R(3) + 100); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8008085C; }
    { uint32_t ea_ = (R(3) + 116); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8008085C; }
    { uint32_t ea_ = (R(3) + 112); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8008085C; }
    { uint32_t ea_ = (R(3) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8008085C; }
    R(3) = (0 + 1);
    goto L_80080860;
L_8008077C:;
    { uint32_t ea_ = (R(3) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = -(int32_t)R(0);
    { uint32_t ea_ = (R(3) + 100); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(3) = (f + 120);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(2) + -29176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[2].d); }
    R(4) = (f + 8);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[0].d); }
    st16(base, (f + 8), R(0));
    GM_CALLV(0x800807ACu, 0x8016EE30u, 0);
    { uint32_t ea_ = (R(31) + 8); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 72);
    { uint32_t ea_ = (f + 56); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 4); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 52); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[3].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    GM_CALLV(0x800807E4u, 0x801C0BD0u, 0);
    R(3) = (f + 120);
    R(4) = (f + 72);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800807F4u, 0x801C0540u, 0);
    R(3) = (f + 120);
    R(4) = (f + 36);
    GM_CALLV(0x80080800u, 0x8016F130u, 0);
    { uint32_t ea_ = (f + 36); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29176); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[3].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8008085C; }
    { uint32_t ea_ = (R(30) + 136); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 128); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8008085C; }
    { uint32_t ea_ = (f + 40); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[3].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8008085C; }
    { uint32_t ea_ = (R(30) + 140); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 132); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[0].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_8008085C; }
    R(3) = (0 + 1);
    goto L_80080860;
L_8008085C:;
    R(3) = (0 + 0);
L_80080860:;
    R(0) = lr;
}

/* fn_80080880 (fn_80080880, 128 bytes) */
static void bg_m_80880(GM_CTX) {
    cr_fcmp(ctx, 0, ctx->f[2].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80080894; }
    ctx->f[0].u = ctx->f[2].u;
    ctx->f[2].u = ctx->f[1].u;
    ctx->f[1].u = ctx->f[0].u;
L_80080894:;
    R(5) = ld32(base, (R(3) + 188));
    R(4) = (0 + 0x802F0000u);
    R(4) = (R(4) + -1856);
    R(0) = (int16_t)ld16(base, (R(5) + 0));
    R(5) = rotl32(R(0), 20) & 0xCu;
    R(0) = ld32(base, (R(4) + R(5)));
    R(0) = rotl32(R(0), 3) & 0xFFFFFFF8u;
    R(4) = R(3) + R(0);
    { uint32_t ea_ = (R(4) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[1].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800808CC; }
    R(3) = (0 + 0);
    return;
L_800808CC:;
    R(4) = (0 + 0x802F0000u);
    R(4) = (R(4) + -1840);
    R(0) = ld32(base, (R(4) + R(5)));
    R(0) = rotl32(R(0), 3) & 0xFFFFFFF8u;
    R(3) = R(3) + R(0);
    { uint32_t ea_ = (R(3) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[3].d + ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[0].d, ctx->f[2].d);
    R(0) = ctx->cr;
    R(0) = rotl32(R(0), 2) & 0x1u;
    R(0) = cntlzw(R(0));
    R(3) = rotl32(R(0), 27) & 0x7FFFFFFu;
}

/* fn_80080900 (fn_80080900, 1024 bytes) */
static void bg_m_80900(GM_CTX) {
    GM_FN(0x80080900); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 352);
    R(0) = ld32(base, (R(3) + 0));
    R(20) = R(4) |R(4);
    R(21) = R(5) |R(5);
    R(22) = R(6) |R(6);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8008093C; }
    R(3) = (0 + 0);
    goto L_80080CE0;
L_8008093C:;
    R(0) = ld32(base, (R(3) + 200));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_80080A94; }
    { uint32_t ea_ = (R(4) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    R(4) = (f + 192);
    { uint32_t ea_ = (R(3) + 92); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(5) = (f + 16);
    { uint32_t ea_ = (R(3) + 88); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(6) = (f + 12);
    { uint32_t ea_ = (R(3) + 144); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = R(20) |R(20);
    { uint32_t ea_ = (f + 208); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 212); stfs(base, ea_, ctx->f[1].d); }
    R(8) = ld32(base, (f + 208));
    { uint32_t ea_ = (f + 216); stfs(base, ea_, ctx->f[2].d); }
    R(7) = ld32(base, (f + 212));
    R(0) = ld32(base, (f + 216));
    st32(base, (f + 192), R(8));
    st32(base, (f + 196), R(7));
    st32(base, (f + 200), R(0));
    { uint32_t ea_ = (f + 204); stfs(base, ea_, ctx->f[3].d); }
    GM_CALLV(0x80080994u, 0x802394E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80080CDC; }
    { uint32_t ea_ = (R(20) + 12); psq_l(ctx, base, 0, ea_, 0, 0); }
    R(3) = (f + 128);
    { uint32_t ea_ = (R(20) + 0); psq_l(ctx, base, 1, ea_, 0, 0); }
    cr_cmp_s(ctx, 0, (int32_t)R(21), 0);
    { uint32_t ea_ = (R(20) + 8); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { double a_ = frsp(ctx->f[0].d - ctx->f[1].d), b_ = frsp(ctx->ps1[0] - ctx->ps1[1]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
    { uint32_t ea_ = (R(20) + 20); psq_l(ctx, base, 0, ea_, 1, 0); }
    { uint32_t ea_ = (R(20) + 8); psq_l(ctx, base, 1, ea_, 1, 0); }
    { uint32_t ea_ = (R(3) + 0); psq_st(ctx, base, 2, ea_, 0, 0); }
    { double a_ = frsp(ctx->f[0].d - ctx->f[1].d), b_ = frsp(ctx->ps1[0] - ctx->ps1[1]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
    { uint32_t ea_ = (R(20) + 4); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 132); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); psq_st(ctx, base, 2, ea_, 1, 0); }
    { uint32_t ea_ = (f + 128); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 16); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[1].d * ctx->f[3].d);
    { uint32_t ea_ = (f + 176); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[0].d * ctx->f[3].d);
    { uint32_t ea_ = (R(20) + 0); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[3].d);
    { uint32_t ea_ = (f + 180); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[5].d + ctx->f[7].d);
    { uint32_t ea_ = (f + 184); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[4].d + ctx->f[6].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[8].d);
    { uint32_t ea_ = (f + 116); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 120); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 124); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 104); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 108); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 112); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 92); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 96); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (f + 100); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(20) + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(20) + 16); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(20) + 20); stfs(base, ea_, ctx->f[3].d); }
    if ((CR_BIT(ctx, 2))) { goto L_80080A8C; }
    R(4) = (f + 208);
    { uint32_t ea_ = (R(20) + 12); psq_l(ctx, base, 0, ea_, 0, 0); }
    { uint32_t ea_ = (R(4) + 0); psq_l(ctx, base, 1, ea_, 0, 0); }
    R(3) = (f + 80);
    { double a_ = frsp(ctx->f[0].d - ctx->f[1].d), b_ = frsp(ctx->ps1[0] - ctx->ps1[1]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
    { uint32_t ea_ = (R(20) + 20); psq_l(ctx, base, 0, ea_, 1, 0); }
    { uint32_t ea_ = (R(4) + 8); psq_l(ctx, base, 1, ea_, 1, 0); }
    { uint32_t ea_ = (R(3) + 0); psq_st(ctx, base, 2, ea_, 0, 0); }
    { double a_ = frsp(ctx->f[0].d - ctx->f[1].d), b_ = frsp(ctx->ps1[0] - ctx->ps1[1]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
    { uint32_t ea_ = (f + 84); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 8); psq_st(ctx, base, 2, ea_, 1, 0); }
    { uint32_t ea_ = (f + 80); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[3].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (f + 88); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 164); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 168); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 172); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80080A80u, 0x801611C0u, 0);
    R(3) = (R(3) + 0x10000u);
    R(0) = (R(3) + -32768);
    st16(base, (R(21) + 0), R(0));
L_80080A8C:;
    R(3) = (0 + 1);
    goto L_80080CE0;
L_80080A94:;
    { uint32_t ea_ = (R(4) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    { uint32_t ea_ = (R(3) + 100); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 96); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 108); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 104); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 116); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 112); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 124); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 120); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 248); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (f + 252); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 256); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 260); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 264); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 268); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 272); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 276); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 280); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 284); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 288); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 292); stfs(base, ea_, ctx->f[2].d); }
    if ((CR_BIT(ctx, 2))) { goto L_80080AFC; }
    R(22) = (0 + 0);
L_80080AFC:;
    cr_cmp_s(ctx, 0, (int32_t)R(22), 1);
    R(26) = (0 + 0);
    R(25) = (0 + 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80080B3C; }
    R(3) = ld32(base, (R(3) + 188));
    { uint32_t ea_ = (R(4) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = (int16_t)ld16(base, (R(3) + 0));
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    R(0) = -(int32_t)R(0);
    R(26) = rotl32(R(0), 18) & 0x3u;
    if ((!CR_BIT(ctx, 0))) { goto L_80080B34; }
    R(0) = (R(26) + 2);
    R(26) = R(0) & 0x3u;
L_80080B34:;
    R(0) = (R(26) + -1);
    R(25) = R(0) & 0x3u;
L_80080B3C:;
    { uint32_t ea_ = (R(2) + -29172); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(27) = (f + 248);
    R(28) = (f + 224);
    R(29) = (f + 236);
    R(30) = (f + 20);
    R(31) = (f + 68);
    R(24) = (0 + 0);
    R(23) = (0 + 0);
L_80080B5C:;
    cr_cmp_s(ctx, 0, (int32_t)R(22), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80080B7C; }
    R(0) = R(26) & 0xFFu;
    cr_cmp_s(ctx, 0, (int32_t)R(0), (int32_t)R(23));
    if ((CR_BIT(ctx, 2))) { goto L_80080B7C; }
    R(0) = R(25) & 0xFFu;
    cr_cmp_s(ctx, 0, (int32_t)R(0), (int32_t)R(23));
    if ((!CR_BIT(ctx, 2))) { goto L_80080CBC; }
L_80080B7C:;
    R(0) = (R(23) + 1);
    { uint32_t ea_ = (R(27) + 0); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(0) = R(0) & 0x3u;
    { uint32_t ea_ = (R(27) + 4); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(0) = ((int32_t)R(0) * 12);
    R(7) = (f + 248);
    { uint32_t ea_ = (R(27) + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = R(20) |R(20);
    { uint32_t ea_ = (f + 224); stfs(base, ea_, ctx->f[1].d); }
    R(4) = (f + 224);
    { uint32_t ea_ = R(7) + R(0); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); R(7) = ea_; }
    R(5) = (f + 8);
    { uint32_t ea_ = (f + 228); stfs(base, ea_, ctx->f[0].d); }
    R(6) = (0 + 0);
    { uint32_t ea_ = (R(7) + 4); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(7) + 8); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 232); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 236); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 240); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 244); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80080BD0u, 0x802390D0u, 0);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[31].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80080CBC; }
    { uint32_t ea_ = (R(20) + 12); psq_l(ctx, base, 0, ea_, 0, 0); }
    cr_cmp_s(ctx, 0, (int32_t)R(21), 0);
    { uint32_t ea_ = (R(20) + 0); psq_l(ctx, base, 1, ea_, 0, 0); }
    { uint32_t ea_ = (R(20) + 8); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    { double a_ = frsp(ctx->f[0].d - ctx->f[1].d), b_ = frsp(ctx->ps1[0] - ctx->ps1[1]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
    { uint32_t ea_ = (R(20) + 20); psq_l(ctx, base, 0, ea_, 1, 0); }
    { uint32_t ea_ = (R(20) + 8); psq_l(ctx, base, 1, ea_, 1, 0); }
    { uint32_t ea_ = (R(31) + 0); psq_st(ctx, base, 2, ea_, 0, 0); }
    { double a_ = frsp(ctx->f[0].d - ctx->f[1].d), b_ = frsp(ctx->ps1[0] - ctx->ps1[1]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
    { uint32_t ea_ = (R(20) + 4); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 72); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 8); psq_st(ctx, base, 2, ea_, 1, 0); }
    { uint32_t ea_ = (f + 68); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 76); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[5].d = ctx->ps1[5] = frsp(ctx->f[1].d * ctx->f[3].d);
    { uint32_t ea_ = (f + 152); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[0].d * ctx->f[3].d);
    { uint32_t ea_ = (R(20) + 0); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d * ctx->f[3].d);
    { uint32_t ea_ = (f + 156); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[9].d = ctx->ps1[9] = frsp(ctx->f[5].d + ctx->f[7].d);
    { uint32_t ea_ = (f + 160); stfs(base, ea_, ctx->f[0].d); }
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[4].d + ctx->f[6].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[2].d + ctx->f[8].d);
    { uint32_t ea_ = (f + 56); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[5].d); }
    { uint32_t ea_ = (f + 64); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[8].d); }
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[7].d); }
    { uint32_t ea_ = (f + 52); stfs(base, ea_, ctx->f[6].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (f + 40); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (R(20) + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(20) + 16); stfs(base, ea_, ctx->f[9].d); }
    { uint32_t ea_ = (R(20) + 20); stfs(base, ea_, ctx->f[3].d); }
    if ((CR_BIT(ctx, 2))) { goto L_80080CB8; }
    { uint32_t ea_ = (R(29) + 0); psq_l(ctx, base, 0, ea_, 0, 0); }
    { uint32_t ea_ = (R(28) + 0); psq_l(ctx, base, 1, ea_, 0, 0); }
    { double a_ = frsp(ctx->f[0].d - ctx->f[1].d), b_ = frsp(ctx->ps1[0] - ctx->ps1[1]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
    { uint32_t ea_ = (R(29) + 8); psq_l(ctx, base, 0, ea_, 1, 0); }
    { uint32_t ea_ = (R(28) + 8); psq_l(ctx, base, 1, ea_, 1, 0); }
    { uint32_t ea_ = (R(30) + 0); psq_st(ctx, base, 2, ea_, 0, 0); }
    { double a_ = frsp(ctx->f[0].d - ctx->f[1].d), b_ = frsp(ctx->ps1[0] - ctx->ps1[1]); ctx->f[2].d = a_; ctx->ps1[2] = b_; }
    { uint32_t ea_ = (f + 24); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(30) + 8); psq_st(ctx, base, 2, ea_, 1, 0); }
    { uint32_t ea_ = (f + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[3].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 140); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 144); stfs(base, ea_, ctx->f[3].d); }
    { uint32_t ea_ = (f + 148); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80080CB0u, 0x801611C0u, 0);
    R(0) = (R(3) + 16384);
    st16(base, (R(21) + 0), R(0));
L_80080CB8:;
    R(24) = (0 + 1);
L_80080CBC:;
    R(23) = (R(23) + 1);
    R(27) = (R(27) + 12);
    cr_cmp_s(ctx, 0, (int32_t)R(23), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80080B5C; }
    R(0) = -(int32_t)R(24);
    R(0) = R(0) |R(24);
    R(3) = rotl32(R(0), 1) & 0x1u;
    goto L_80080CE0;
L_80080CDC:;
    R(3) = (0 + 0);
L_80080CE0:;
    R(11) = (f + 352);
    R(0) = lr;
}

/* fn_80080D00 (fn_80080D00, 52 bytes) */
static void bg_m_80d00(GM_CTX) {
    R(0) = ld32(base, (R(3) + 208));
    R(0) = R(0) & 0x80000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080D14; }
    R(3) = (0 + 1);
    return;
L_80080D14:;
    R(12) = ld32(base, (R(3) + 76));
    cr_cmp_s(ctx, 0, (int32_t)R(12), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80080D28; }
    R(3) = (0 + 0);
    return;
L_80080D28:;
    R(3) = ld32(base, (R(3) + 0));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_80080D40 (fn_80080D40, 52 bytes) */
static void bg_m_80d40(GM_CTX) {
    R(0) = ld32(base, (R(3) + 208));
    R(0) = R(0) & 0x100000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080D54; }
    R(3) = (0 + 1);
    return;
L_80080D54:;
    R(12) = ld32(base, (R(3) + 80));
    cr_cmp_s(ctx, 0, (int32_t)R(12), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80080D68; }
    R(3) = (0 + 0);
    return;
L_80080D68:;
    R(3) = ld32(base, (R(3) + 0));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_80080D80 (fn_80080D80, 52 bytes) */
static void bg_m_80d80(GM_CTX) {
    R(0) = ld32(base, (R(3) + 208));
    R(0) = R(0) & 0x200000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080D94; }
    R(3) = (0 + 1);
    return;
L_80080D94:;
    R(12) = ld32(base, (R(3) + 84));
    cr_cmp_s(ctx, 0, (int32_t)R(12), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80080DA8; }
    R(3) = (0 + 0);
    return;
L_80080DA8:;
    R(3) = ld32(base, (R(3) + 0));
    ctx->ctr = R(12);
    { GM_TAIL(ctx->ctr, 0); return; }
}

/* fn_80080E40 (fn_80080E40, 484 bytes) */
static void bg_m_80e40(GM_CTX) {
    GM_FN(0x80080E40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(29) = R(3) |R(3);
    R(0) = ld8(base, (R(3) + 220));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80080E80; }
    R(7) = ld32(base, (R(3) + 0));
    cr_cmp_s(ctx, 0, (int32_t)R(7), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80080E88; }
L_80080E80:;
    R(3) = (0 + 0);
    goto L_80081004;
L_80080E88:;
    R(0) = ld32(base, (R(3) + 212));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80081000; }
    R(5) = ld8(base, (R(4) + 229));
    R(0) = ld8(base, (R(3) + 221));
    R(0) = R(5) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80081000; }
    R(5) = ld32(base, (R(4) + 4));
    cr_cmp_u(ctx, 0, R(5), R(7));
    if ((CR_BIT(ctx, 2))) { goto L_80081000; }
    R(0) = ld32(base, (R(3) + 56));
    cr_cmp_u(ctx, 0, R(5), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80081000; }
    R(0) = ld32(base, (R(4) + 84));
    cr_cmp_u(ctx, 0, R(0), R(7));
    if ((CR_BIT(ctx, 2))) { goto L_80081000; }
    R(4) = ld32(base, (R(4) + 232));
    R(0) = ld8(base, (R(3) + 222));
    R(4) = ld8(base, (R(4) + 0));
    cr_cmp_u(ctx, 0, R(4), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80081000; }
    R(4) = (0 + 0x802F0000u);
    R(28) = rotl32(R(6), 2) & 0x3FCu;
    R(4) = (R(4) + -1824);
    R(3) = ld32(base, (R(3) + 208));
    R(0) = ld32(base, (R(4) + R(28)));
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080F00; }
    R(3) = (0 + 0);
    goto L_80081004;
L_80080F00:;
    R(3) = R(30) |R(30);
    GM_CALLV(0x80080F08u, 0x80070C80u, 0);
    R(0) = R(3) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x1u);
    if ((CR_BIT(ctx, 2))) { goto L_80080F28; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80080F1Cu, 0x80070C80u, 0);
    R(0) = R(3) & 0xFFu;
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_80080F48; }
L_80080F28:;
    R(3) = (0 + 0x802F0000u);
    R(4) = ld32(base, (R(29) + 208));
    R(3) = (R(3) + -1808);
    R(0) = ld32(base, (R(3) + R(28)));
    R(0) = R(4) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080F5C; }
    R(3) = (0 + 0);
    goto L_80081004;
L_80080F48:;
    R(4) = ld32(base, (R(29) + 208));
    R(0) = R(4) & 0x4000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080F5C; }
    R(3) = (0 + 0);
    goto L_80081004;
L_80080F5C:;
    R(0) = ld32(base, (R(29) + 204));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_80080F84; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_80080F94; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((CR_BIT(ctx, 2))) { goto L_80080FA4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 4);
    if ((CR_BIT(ctx, 2))) { goto L_80080FB8; }
    goto L_80080FC8;
L_80080F84:;
    R(0) = R(31) & 0x40u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080FC8; }
    R(3) = (0 + 0);
    goto L_80081004;
L_80080F94:;
    R(0) = R(31) & 0x80u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080FC8; }
    R(3) = (0 + 0);
    goto L_80081004;
L_80080FA4:;
    R(0) = R(31) & 0x10000000u;
    R(0) = (rotl32(R(31), 0) & 0x100u) | (R(0) & ~0x100u);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080FC8; }
    R(3) = (0 + 0);
    goto L_80081004;
L_80080FB8:;
    R(0) = R(31) & 0x200u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080FC8; }
    R(3) = (0 + 0);
    goto L_80081004;
L_80080FC8:;
    R(0) = R(4) & 0x800u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080FE0; }
    R(0) = R(31) & 0x400u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080FE0; }
    R(3) = (0 + 0);
    goto L_80081004;
L_80080FE0:;
    R(0) = R(4) & 0x1000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080FF8; }
    R(0) = R(31) & 0x800u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80080FF8; }
    R(3) = (0 + 0);
    goto L_80081004;
L_80080FF8:;
    R(3) = (0 + 1);
    goto L_80081004;
L_80081000:;
    R(3) = (0 + 0);
L_80081004:;
    R(0) = lr;
}

/* fn_80081030 (fn_80081030, 52 bytes) */
static void bg_m_81030(GM_CTX) {
    R(0) = R(4) & 0xA0000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80081040; }
    R(3) = (0 + 0);
    return;
L_80081040:;
    R(0) = R(4) & 0x40000000u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8008105C; }
    R(0) = ld32(base, (R(3) + 208));
    R(0) = R(0) & 0x800u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_8008105C; }
    R(3) = (0 + 0);
    return;
L_8008105C:;
    R(3) = (0 + 1);
}

/* fn_80081070 (fn_80081070, 652 bytes) */
static void bg_m_81070(GM_CTX) {
    R(4) = (0 + 0x80310000u);
    R(0) = (0 + 4);
    R(4) = (R(4) + -516);
    st32(base, (R(3) + 0), R(4));
    R(5) = R(3) |R(3);
    R(6) = R(3) |R(3);
    R(7) = R(3) |R(3);
    st32(base, (R(13) + -22672), R(3));
    R(4) = (0 + 0);
    ctx->ctr = R(0);
L_80081098:;
    st32(base, (R(5) + 4), R(4));
    R(8) = (R(7) + 64);
    st32(base, (R(5) + 52), R(4));
    st32(base, (R(6) + 744), R(4));
    st32(base, (R(5) + 8), R(4));
    st32(base, (R(5) + 56), R(4));
    st32(base, (R(6) + 748), R(4));
    st32(base, (R(5) + 12), R(4));
    st32(base, (R(5) + 60), R(4));
    st32(base, (R(6) + 752), R(4));
    st32(base, (R(6) + 100), R(4));
    st32(base, (R(6) + 164), R(4));
    st32(base, (R(6) + 104), R(4));
    st32(base, (R(6) + 168), R(4));
    st32(base, (R(6) + 108), R(4));
    st32(base, (R(6) + 172), R(4));
    st32(base, (R(6) + 112), R(4));
    st32(base, (R(6) + 176), R(4));
    st8(base, (R(7) + 228), R(4));
    st8(base, (R(7) + 229), R(4));
    st8(base, (R(7) + 230), R(4));
    st8(base, (R(7) + 231), R(4));
    st8(base, (R(7) + 232), R(4));
    st8(base, (R(7) + 233), R(4));
    st8(base, (R(7) + 234), R(4));
    st8(base, (R(7) + 235), R(4));
    st8(base, (R(7) + 236), R(4));
    st8(base, (R(7) + 237), R(4));
    st8(base, (R(7) + 238), R(4));
    st8(base, (R(7) + 239), R(4));
    st8(base, (R(7) + 240), R(4));
    st8(base, (R(7) + 241), R(4));
    st8(base, (R(7) + 242), R(4));
    st8(base, (R(7) + 243), R(4));
    st8(base, (R(7) + 244), R(4));
    st8(base, (R(7) + 245), R(4));
    st8(base, (R(7) + 246), R(4));
    st8(base, (R(7) + 247), R(4));
    st8(base, (R(7) + 248), R(4));
    st8(base, (R(7) + 249), R(4));
    st8(base, (R(7) + 250), R(4));
    st8(base, (R(7) + 251), R(4));
    st8(base, (R(7) + 252), R(4));
    st8(base, (R(7) + 253), R(4));
    st8(base, (R(7) + 254), R(4));
    st8(base, (R(7) + 255), R(4));
    st8(base, (R(7) + 256), R(4));
    st8(base, (R(7) + 257), R(4));
    st8(base, (R(7) + 258), R(4));
    st8(base, (R(7) + 259), R(4));
    st8(base, (R(7) + 260), R(4));
    st8(base, (R(7) + 261), R(4));
    st8(base, (R(7) + 262), R(4));
    st8(base, (R(7) + 263), R(4));
    st8(base, (R(7) + 264), R(4));
    st8(base, (R(7) + 265), R(4));
    st8(base, (R(7) + 266), R(4));
    st8(base, (R(7) + 267), R(4));
    st8(base, (R(7) + 268), R(4));
    st8(base, (R(7) + 269), R(4));
    st8(base, (R(7) + 270), R(4));
    st8(base, (R(7) + 271), R(4));
    st8(base, (R(7) + 272), R(4));
    st8(base, (R(7) + 273), R(4));
    st8(base, (R(7) + 274), R(4));
    st8(base, (R(7) + 275), R(4));
    st8(base, (R(7) + 276), R(4));
    st8(base, (R(7) + 277), R(4));
    st8(base, (R(7) + 278), R(4));
    st8(base, (R(7) + 279), R(4));
    st8(base, (R(7) + 280), R(4));
    st8(base, (R(7) + 281), R(4));
    st8(base, (R(7) + 282), R(4));
    st8(base, (R(7) + 283), R(4));
    st8(base, (R(7) + 284), R(4));
    st8(base, (R(7) + 285), R(4));
    st8(base, (R(7) + 286), R(4));
    st8(base, (R(7) + 287), R(4));
    st8(base, (R(7) + 288), R(4));
    st8(base, (R(7) + 289), R(4));
    st8(base, (R(7) + 290), R(4));
    st8(base, (R(7) + 291), R(4));
    st8(base, (R(8) + 228), R(4));
    R(5) = (R(5) + 12);
    R(6) = (R(6) + 16);
    R(7) = (R(7) + 128);
    st8(base, (R(8) + 229), R(4));
    st8(base, (R(8) + 230), R(4));
    st8(base, (R(8) + 231), R(4));
    st8(base, (R(8) + 232), R(4));
    st8(base, (R(8) + 233), R(4));
    st8(base, (R(8) + 234), R(4));
    st8(base, (R(8) + 235), R(4));
    st8(base, (R(8) + 236), R(4));
    st8(base, (R(8) + 237), R(4));
    st8(base, (R(8) + 238), R(4));
    st8(base, (R(8) + 239), R(4));
    st8(base, (R(8) + 240), R(4));
    st8(base, (R(8) + 241), R(4));
    st8(base, (R(8) + 242), R(4));
    st8(base, (R(8) + 243), R(4));
    st8(base, (R(8) + 244), R(4));
    st8(base, (R(8) + 245), R(4));
    st8(base, (R(8) + 246), R(4));
    st8(base, (R(8) + 247), R(4));
    st8(base, (R(8) + 248), R(4));
    st8(base, (R(8) + 249), R(4));
    st8(base, (R(8) + 250), R(4));
    st8(base, (R(8) + 251), R(4));
    st8(base, (R(8) + 252), R(4));
    st8(base, (R(8) + 253), R(4));
    st8(base, (R(8) + 254), R(4));
    st8(base, (R(8) + 255), R(4));
    st8(base, (R(8) + 256), R(4));
    st8(base, (R(8) + 257), R(4));
    st8(base, (R(8) + 258), R(4));
    st8(base, (R(8) + 259), R(4));
    st8(base, (R(8) + 260), R(4));
    st8(base, (R(8) + 261), R(4));
    st8(base, (R(8) + 262), R(4));
    st8(base, (R(8) + 263), R(4));
    st8(base, (R(8) + 264), R(4));
    st8(base, (R(8) + 265), R(4));
    st8(base, (R(8) + 266), R(4));
    st8(base, (R(8) + 267), R(4));
    st8(base, (R(8) + 268), R(4));
    st8(base, (R(8) + 269), R(4));
    st8(base, (R(8) + 270), R(4));
    st8(base, (R(8) + 271), R(4));
    st8(base, (R(8) + 272), R(4));
    st8(base, (R(8) + 273), R(4));
    st8(base, (R(8) + 274), R(4));
    st8(base, (R(8) + 275), R(4));
    st8(base, (R(8) + 276), R(4));
    st8(base, (R(8) + 277), R(4));
    st8(base, (R(8) + 278), R(4));
    st8(base, (R(8) + 279), R(4));
    st8(base, (R(8) + 280), R(4));
    st8(base, (R(8) + 281), R(4));
    st8(base, (R(8) + 282), R(4));
    st8(base, (R(8) + 283), R(4));
    st8(base, (R(8) + 284), R(4));
    st8(base, (R(8) + 285), R(4));
    st8(base, (R(8) + 286), R(4));
    st8(base, (R(8) + 287), R(4));
    st8(base, (R(8) + 288), R(4));
    st8(base, (R(8) + 289), R(4));
    st8(base, (R(8) + 290), R(4));
    st8(base, (R(8) + 291), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80081098; }
    R(0) = (0 + 0);
    st32(base, (R(3) + 740), R(0));
}

/* fn_80081300 (fn_80081300, 240 bytes) */
static void bg_m_81300(GM_CTX) {
    GM_FN(0x80081300); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(23) = R(3) |R(3);
    R(24) = R(4) |R(4);
    if ((CR_BIT(ctx, 2))) { goto L_800813D4; }
    R(4) = (0 + 0x80310000u);
    R(30) = R(23) |R(23);
    R(4) = (R(4) + -516);
    st32(base, (R(3) + 0), R(4));
    R(29) = R(23) |R(23);
    R(26) = (0 + 0);
    R(31) = (0 + 0);
L_80081340:;
    R(28) = R(30) |R(30);
    R(27) = R(29) |R(29);
    R(25) = (0 + 0);
L_8008134C:;
    R(3) = ld32(base, (R(28) + 52));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081374; }
    if ((CR_BIT(ctx, 2))) { goto L_80081370; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x80081370u, ctx->ctr, 0);
L_80081370:;
    st32(base, (R(28) + 52), R(31));
L_80081374:;
    R(3) = ld32(base, (R(27) + 744));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081394; }
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    GM_CALLV(0x80081390u, ctx->ctr, 0);
    st32(base, (R(27) + 744), R(31));
L_80081394:;
    R(25) = (R(25) + 1);
    R(27) = (R(27) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(25), 3);
    R(28) = (R(28) + 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8008134C; }
    R(26) = (R(26) + 1);
    R(29) = (R(29) + 16);
    cr_cmp_s(ctx, 0, (int32_t)R(26), 4);
    R(30) = (R(30) + 12);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80081340; }
    cr_cmp_s(ctx, 0, (int32_t)R(24), 0);
    R(0) = (0 + 0);
    st32(base, (R(13) + -22672), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_800813D4; }
    R(3) = R(23) |R(23);
    GM_CALLV(0x800813D4u, 0x802B9280u, 0);
L_800813D4:;
    R(11) = (f + 48);
    R(3) = R(23) |R(23);
    R(0) = lr;
}

/* GetTilesetName__FPvii (GetTilesetName__FPvii, 24 bytes) */
static void bg_GetTilesetName__FPvii_813f0(GM_CTX) {
    R(4) = rotl32(R(4), 7) & 0xFFFFFF80u;
    R(0) = rotl32(R(5), 5) & 0xFFFFFFE0u;
    R(3) = R(3) + R(4);
    R(3) = R(3) + R(0);
    R(3) = (R(3) + 228);
}

/* fn_80081410 (fn_80081410, 192 bytes) */
static void bg_m_81410(GM_CTX) {
    GM_FN(0x80081410); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(30) = (R(3) + 228);
    R(27) = (0 + 0);
    R(31) = (0 + 0);
L_80081430:;
    R(0) = ld32(base, (R(13) + -22504));
    R(3) = R(0) + R(31);
    R(0) = ld32(base, (R(3) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081448; }
    goto L_8008144C;
L_80081448:;
    R(3) = (0 + 0);
L_8008144C:;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800814A4; }
    R(5) = ld32(base, (R(3) + 8));
    R(28) = R(30) |R(30);
    st32(base, (f + 8), R(5));
    R(29) = (f + 8);
    R(4) = (R(5) + 32);
    R(3) = (R(5) + 64);
    R(0) = (R(5) + 96);
    st32(base, (f + 12), R(4));
    R(26) = (0 + 0);
    st32(base, (f + 16), R(3));
    st32(base, (f + 20), R(0));
L_80081480:;
    R(4) = ld32(base, (R(29) + 0));
    R(3) = R(28) |R(28);
    R(5) = (0 + 32);
    GM_CALLV(0x80081490u, 0x802E19F8u, 0);
    R(26) = (R(26) + 1);
    R(28) = (R(28) + 32);
    cr_cmp_s(ctx, 0, (int32_t)R(26), 4);
    R(29) = (R(29) + 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80081480; }
L_800814A4:;
    R(27) = (R(27) + 1);
    R(30) = (R(30) + 128);
    cr_cmp_s(ctx, 0, (int32_t)R(27), 4);
    R(31) = (R(31) + 944);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80081430; }
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_800814D0 (fn_800814D0, 456 bytes) */
static void bg_m_814d0(GM_CTX) {
    GM_FN(0x800814D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 112);
    R(0) = ld8(base, (R(13) + -22664));
    R(30) = (0 + 0x80310000u);
    R(23) = R(3) |R(3);
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    R(30) = (R(30) + -664);
    if ((!CR_BIT(ctx, 2))) { goto L_80081510; }
    R(3) = (0 + 0x80370000u);
    R(0) = (0 + 1);
    R(3) = (R(3) + 15740);
    st32(base, (R(13) + -22668), R(3));
    st8(base, (R(13) + -22664), R(0));
L_80081510:;
    R(26) = ld32(base, (R(13) + -22088));
    R(29) = R(23) |R(23);
    R(28) = R(23) |R(23);
    R(25) = (0 + 0);
    R(31) = (0 + 0);
L_80081524:;
    R(3) = (f + 8);
    R(4) = (R(30) + 0);
    R(5) = (R(25) + 1);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80081538u, 0x802E17DCu, 0);
    R(4) = ld32(base, (R(13) + -22668));
    R(3) = (R(26) + 4);
    R(5) = (f + 8);
    GM_CALLV(0x80081548u, 0x800DF3C0u, 0);
    st32(base, (R(29) + 12), R(3));
    R(3) = (f + 8);
    R(4) = (R(30) + 28);
    R(5) = (R(25) + 1);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80081560u, 0x802E17DCu, 0);
    R(4) = ld32(base, (R(13) + -22668));
    R(3) = (R(26) + 4);
    R(5) = (f + 8);
    GM_CALLV(0x80081570u, 0x800DF3C0u, 0);
    st32(base, (R(29) + 4), R(3));
    R(3) = (f + 8);
    R(4) = (R(30) + 56);
    R(5) = (R(25) + 1);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80081588u, 0x802E17DCu, 0);
    R(4) = ld32(base, (R(13) + -22668));
    R(3) = (R(26) + 4);
    R(5) = (f + 8);
    GM_CALLV(0x80081598u, 0x800DF3C0u, 0);
    st32(base, (R(29) + 8), R(3));
    R(27) = R(28) |R(28);
    R(24) = (0 + 0);
L_800815A4:;
    R(3) = R(23) |R(23);
    R(4) = R(25) |R(25);
    R(5) = R(24) |R(24);
    GM_CALLV(0x800815B4u, 0x800813F0u, 0);
    R(0) = ld8(base, (R(3) + 0));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_800815CC; }
    st32(base, (R(27) + 100), R(31));
    st32(base, (R(27) + 164), R(31));
    goto L_8008165C;
L_800815CC:;
    R(3) = R(23) |R(23);
    R(4) = R(25) |R(25);
    R(5) = R(24) |R(24);
    GM_CALLV(0x800815DCu, 0x800813F0u, 0);
    R(5) = R(3) |R(3);
    R(3) = (f + 8);
    R(4) = (R(30) + 84);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x800815F0u, 0x802E17DCu, 0);
    R(3) = R(23) |R(23);
    R(4) = R(25) |R(25);
    R(5) = R(24) |R(24);
    GM_CALLV(0x80081600u, 0x800813F0u, 0);
    R(4) = R(3) |R(3);
    R(3) = (R(26) + 4);
    R(5) = (f + 8);
    GM_CALLV(0x80081610u, 0x800DF180u, 0);
    st32(base, (R(27) + 100), R(3));
    R(3) = R(23) |R(23);
    R(4) = R(25) |R(25);
    R(5) = R(24) |R(24);
    GM_CALLV(0x80081624u, 0x800813F0u, 0);
    R(5) = R(3) |R(3);
    R(3) = (f + 8);
    R(4) = (R(30) + 104);
    CR_SETBIT(ctx, 6, (CR_BIT(ctx, 6) ^ CR_BIT(ctx, 6)));
    GM_CALLV(0x80081638u, 0x802E17DCu, 0);
    R(3) = R(23) |R(23);
    R(4) = R(25) |R(25);
    R(5) = R(24) |R(24);
    GM_CALLV(0x80081648u, 0x800813F0u, 0);
    R(4) = R(3) |R(3);
    R(3) = (R(26) + 4);
    R(5) = (f + 8);
    GM_CALLV(0x80081658u, 0x800DF180u, 0);
    st32(base, (R(27) + 164), R(3));
L_8008165C:;
    R(24) = (R(24) + 1);
    R(27) = (R(27) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(24), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800815A4; }
    R(25) = (R(25) + 1);
    R(28) = (R(28) + 16);
    cr_cmp_s(ctx, 0, (int32_t)R(25), 4);
    R(29) = (R(29) + 12);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80081524; }
    R(11) = (f + 112);
    R(0) = lr;
}

/* fn_800816A0 (fn_800816A0, 212 bytes) */
static void bg_m_816a0(GM_CTX) {
    GM_FN(0x800816A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(21) = R(3) |R(3);
    R(25) = (0 + 0);
    R(29) = R(21) |R(21);
    R(30) = (0 + 0x80310000u);
    R(28) = R(21) |R(21);
    R(31) = (0 + 0);
L_800816CC:;
    GM_CALLV(0x800816D0u, 0x800818D0u, 0);
    R(24) = R(3) |R(3);
    R(27) = R(29) |R(29);
    R(26) = R(28) |R(28);
    R(22) = (0 + 0);
L_800816E0:;
    R(0) = ld32(base, (R(27) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081724; }
    R(4) = ld32(base, (R(21) + 740));
    R(3) = R(24) |R(24);
    R(5) = (R(30) + -544);
    R(6) = (0 + 32);
    R(7) = (0 + 0);
    GM_CALLV(0x80081704u, 0x8016E630u, 0);
    R(23) = R(3) |R(3);
    R(5) = R(25) |R(25);
    R(4) = R(23) |R(23);
    R(6) = R(22) |R(22);
    R(3) = (0 + 0);
    GM_CALLV(0x8008171Cu, 0x80083560u, 0);
    st32(base, (R(27) + 52), R(3));
    goto L_8008172C;
L_80081724:;
    st32(base, (R(27) + 52), R(31));
    R(23) = (0 + 0);
L_8008172C:;
    R(22) = (R(22) + 1);
    st32(base, (R(26) + 744), R(23));
    cr_cmp_s(ctx, 0, (int32_t)R(22), 3);
    R(27) = (R(27) + 4);
    R(26) = (R(26) + 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800816E0; }
    R(25) = (R(25) + 1);
    R(28) = (R(28) + 16);
    cr_cmp_s(ctx, 0, (int32_t)R(25), 4);
    R(29) = (R(29) + 12);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800816CC; }
    R(11) = (f + 64);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_80081780 (fn_80081780, 120 bytes) */
static void bg_m_81780(GM_CTX) {
    GM_FN(0x80081780); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ((int32_t)R(4) * 12);
    R(31) = R(3) + R(0);
    R(30) = (0 + 0);
    R(29) = R(4) |R(4);
L_800817A8:;
    R(0) = ld32(base, (R(31) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800817CC; }
    R(3) = ld32(base, (R(31) + 52));
    R(5) = R(29) |R(29);
    R(6) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x800817C8u, 0x80083560u, 0);
    st32(base, (R(31) + 52), R(3));
L_800817CC:;
    R(30) = (R(30) + 1);
    R(31) = (R(31) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 3);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800817A8; }
    R(0) = lr;
}

/* fn_80081800 (fn_80081800, 68 bytes) */
static void bg_m_81800(GM_CTX) {
    GM_FN(0x80081800); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    st32(base, (R(3) + 740), R(4));
    GM_CALLV(0x8008181Cu, 0x80081410u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80081824u, 0x800814D0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x8008182Cu, 0x800816A0u, 0);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_80081870 (fn_80081870, 32 bytes) */
static void bg_m_81870(GM_CTX) {
    R(0) = rotl32(R(4), 4) & 0xFFFFFFF0u;
    R(4) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(0);
    R(3) = R(3) + R(4);
    R(0) = rotl32(R(6), 1) & 0x1FFFEu;
    R(3) = ld32(base, (R(3) + 100));
    R(3) = ld16(base, (R(3) + R(0)));
}

/* fn_80081890 (fn_80081890, 28 bytes) */
static void bg_m_81890(GM_CTX) {
    R(4) = rotl32(R(4), 4) & 0xFFFFFFF0u;
    R(0) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(4);
    R(3) = R(3) + R(0);
    R(0) = ld32(base, (R(3) + 164));
    R(3) = R(0) + R(6);
}

/* fn_800818B0 (fn_800818B0, 24 bytes) */
static void bg_m_818b0(GM_CTX) {
    R(4) = ((int32_t)R(4) * 12);
    R(0) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(4);
    R(3) = R(3) + R(0);
    R(3) = ld32(base, (R(3) + 4));
}

/* fn_800818D0 (fn_800818D0, 12 bytes) */
static void bg_m_818d0(GM_CTX) {
    R(3) = (0 + 0x20000u);
    R(3) = (R(3) + 3884);
}

/* fn_80081900 (fn_80081900, 88 bytes) */
static void bg_m_81900(GM_CTX) {
    R(5) = (0 + 0x802F0000u);
    R(7) = (0 + 0);
    st16(base, (R(4) + 0), R(7));
    R(5) = (R(5) + -1792);
    goto L_8008193C;
    R(0) = R(0) | 0x0u;
L_80081918:;
    R(6) = ld16(base, (R(4) + 0));
    R(0) = (R(6) + 1);
    st16(base, (R(4) + 0), R(0));
    R(0) = rotl32(R(0), 1) & 0x1FFFEu;
    R(0) = ld16(base, (R(5) + R(0)));
    cr_cmp_u(ctx, 0, R(3), R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_8008193C; }
    R(7) = (0 + 1);
    goto L_80081950;
L_8008193C:;
    R(0) = ld16(base, (R(4) + 0));
    R(0) = rotl32(R(0), 1) & 0xFFFFFFFEu;
    R(0) = ld16(base, (R(5) + R(0)));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_80081918; }
L_80081950:;
    R(3) = R(7) |R(7);
}

/* fn_80081AB0 (fn_80081AB0, 240 bytes) */
static void bg_m_81ab0(GM_CTX) {
    GM_FN(0x80081AB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(31) = ld32(base, (R(13) + -22144));
    R(3) = R(31) |R(31);
    GM_CALLV(0x80081AD4u, 0x800D87D0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081B54; }
    R(3) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x80081AE8u, 0x800D87B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081B20; }
    cr_cmp_u(ctx, 0, R(30), 0x1Eu);
    if ((!CR_BIT(ctx, 2))) { goto L_80081B00; }
    R(3) = (0 + 48);
    goto L_80081B88;
L_80081B00:;
    cr_cmp_u(ctx, 0, R(30), 0x30u);
    if ((!CR_BIT(ctx, 2))) { goto L_80081B10; }
    R(3) = (0 + 30);
    goto L_80081B88;
L_80081B10:;
    cr_cmp_u(ctx, 0, R(30), 0x2Eu);
    if ((!CR_BIT(ctx, 2))) { goto L_80081B20; }
    R(3) = (0 + 47);
    goto L_80081B88;
L_80081B20:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 1);
    GM_CALLV(0x80081B2Cu, 0x800D87B0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081B54; }
    cr_cmp_u(ctx, 0, R(30), 0x3Bu);
    if ((!CR_BIT(ctx, 2))) { goto L_80081B44; }
    R(3) = (0 + 55);
    goto L_80081B88;
L_80081B44:;
    cr_cmp_u(ctx, 0, R(30), 0x3Cu);
    if ((!CR_BIT(ctx, 2))) { goto L_80081B54; }
    R(3) = (0 + 55);
    goto L_80081B88;
L_80081B54:;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x80081B5Cu, 0x80078510u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081B84; }
    cr_cmp_u(ctx, 0, R(30), 0x3Bu);
    if ((!CR_BIT(ctx, 2))) { goto L_80081B74; }
    R(3) = (0 + 55);
    goto L_80081B88;
L_80081B74:;
    cr_cmp_u(ctx, 0, R(30), 0x3Cu);
    if ((!CR_BIT(ctx, 2))) { goto L_80081B84; }
    R(3) = (0 + 55);
    goto L_80081B88;
L_80081B84:;
    R(3) = R(30) |R(30);
L_80081B88:;
    R(0) = lr;
}

/* fn_80081BE0 (fn_80081BE0, 84 bytes) */
static void bg_m_81be0(GM_CTX) {
    R(6) = ld32(base, (R(13) + -21688));
    R(3) = (R(3) + -1);
    R(0) = ld8(base, (R(6) + 4620));
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80081C2C; }
    R(0) = ld8(base, (R(6) + 4621));
    R(3) = (R(4) + -1);
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80081C2C; }
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_80081C14; }
    R(3) = (0 + 1);
    return;
L_80081C14:;
    R(0) = ld8(base, (R(6) + 4622));
    R(3) = (R(5) + -1);
    cr_cmp_s(ctx, 0, (int32_t)R(3), (int32_t)R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80081C2C; }
    R(3) = (0 + 1);
    return;
L_80081C2C:;
    R(3) = (0 + 0);
}

/* fn_80081C40 (fn_80081C40, 224 bytes) */
static void bg_m_81c40(GM_CTX) {
    GM_FN(0x80081C40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(3) |R(3);
    R(4) = ld32(base, (R(13) + -21688));
    R(3) = ld32(base, (R(13) + -22504));
    R(0) = ld8(base, (R(4) + 4622));
    R(0) = ((int32_t)R(0) * 944);
    R(31) = R(3) + R(0);
    R(0) = ld32(base, (R(31) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081C7C; }
    goto L_80081C80;
L_80081C7C:;
    R(31) = (0 + 0);
L_80081C80:;
    R(5) = ld32(base, (R(13) + -22704));
    R(3) = R(31) |R(31);
    { uint32_t ea_ = (R(2) + -29160); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (f + 8);
    R(5) = (R(5) + 0x90000u);
    { uint32_t ea_ = (R(5) + -404); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + -412); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 16); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80081CACu, 0x8008E770u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    R(0) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80081CC4; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 1);
    if ((CR_BIT(ctx, 2))) { goto L_80081CE4; }
    goto L_80081D04;
L_80081CC4:;
    R(3) = R(31) |R(31);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x80081CD0u, 0x8008E650u, 0);
    R(0) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x80081CE0u, 0x8008E350u, 0);
    goto L_80081D08;
L_80081CE4:;
    R(3) = R(31) |R(31);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x80081CF0u, 0x8008E680u, 0);
    R(0) = R(3) |R(3);
    R(3) = R(31) |R(31);
    R(4) = R(0) & 0xFFu;
    GM_CALLV(0x80081D00u, 0x8008E390u, 0);
    goto L_80081D08;
L_80081D04:;
    R(3) = (0 + 0);
L_80081D08:;
    R(0) = lr;
}

/* fn_80081D20 (fn_80081D20, 360 bytes) */
static void bg_m_81d20(GM_CTX) {
    GM_FN(0x80081D20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(5) = (0 + 0x80310000u);
    R(4) = (0 + 0);
    R(5) = (R(5) + -492);
    { uint32_t ea_ = (R(2) + -29152); ctx->f[4].d = ctx->ps1[4] = ldfs(base, ea_); }
    R(0) = (0 + 2);
    R(31) = R(3) |R(3);
    { uint32_t ea_ = (R(2) + -29148); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    st32(base, (R(3) + 0), R(5));
    { uint32_t ea_ = (R(2) + -29144); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    st32(base, (R(13) + -22656), R(3));
    st32(base, (R(3) + 4), R(4));
    st32(base, (R(3) + 16), R(4));
    st32(base, (R(3) + 28), R(4));
    st32(base, (R(3) + 40), R(4));
    st32(base, (R(3) + 8), R(4));
    st32(base, (R(3) + 20), R(4));
    st32(base, (R(3) + 32), R(4));
    st32(base, (R(3) + 44), R(4));
    st32(base, (R(3) + 12), R(4));
    st32(base, (R(3) + 24), R(4));
    st32(base, (R(3) + 36), R(4));
    st32(base, (R(3) + 48), R(4));
    { uint32_t ea_ = (R(3) + 52); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 56); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 60); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(13) + -21908); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 64); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d * ctx->f[1].d);
    { uint32_t ea_ = (R(13) + -21904); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 68); stfs(base, ea_, ctx->f[5].d); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[4].d + ctx->f[1].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d * ctx->f[5].d);
    { uint32_t ea_ = (R(3) + 88); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 72); stfs(base, ea_, ctx->f[2].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[4].d + ctx->f[1].d);
    { uint32_t ea_ = (R(3) + 80); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 76); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 84); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 92); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 96); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 100); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 104); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 108); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(13) + -21908); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 112); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(13) + -21904); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 116); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(3) + 120); stfs(base, ea_, ctx->f[4].d); }
    { uint32_t ea_ = (R(3) + 124); stfs(base, ea_, ctx->f[4].d); }
    st8(base, (R(3) + 128), R(0));
    st8(base, (R(3) + 129), R(4));
    GM_CALLV(0x80081E00u, 0x80081F40u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80081E08u, 0x80082160u, 0);
    R(0) = ld8(base, (R(13) + -22648));
    R(0) = (int8_t)R(0);
    CR0(ctx, R(0));
    if ((!CR_BIT(ctx, 2))) { goto L_80081E2C; }
    GM_CALLV(0x80081E18u, 0x800818D0u, 0);
    R(3) = ((int32_t)R(3) * 12);
    R(0) = (0 + 1);
    st8(base, (R(13) + -22648), R(0));
    R(0) = (R(3) + 4096);
    st32(base, (R(13) + -22652), R(0));
L_80081E2C:;
    R(5) = (0 + 0x80310000u);
    R(3) = ld32(base, (R(13) + -22652));
    R(4) = ld32(base, (R(13) + -18544));
    R(5) = (R(5) + -504);
    R(6) = (0 + 32);
    R(7) = (0 + 0);
    GM_CALLV(0x80081E48u, 0x8016E630u, 0);
    st32(base, (R(31) + 148), R(3));
    R(4) = R(3) |R(3);
    R(3) = (0 + 808);
    R(5) = (0 + 4);
    GM_CALLV(0x80081E5Cu, 0x802B9240u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081E68; }
    GM_CALLV(0x80081E68u, 0x80081070u, 0);
L_80081E68:;
    R(4) = ld32(base, (R(31) + 148));
    GM_CALLV(0x80081E70u, 0x80081800u, 0);
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_80081E90 (fn_80081E90, 164 bytes) */
static void bg_m_81e90(GM_CTX) {
    GM_FN(0x80081E90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80081F18; }
    R(4) = (0 + 0x80310000u);
    R(4) = (R(4) + -492);
    st32(base, (R(3) + 0), R(4));
    GM_CALLV(0x80081EC4u, 0x80082050u, 0);
    R(3) = ld32(base, (R(13) + -22672));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80081EE8; }
    if ((CR_BIT(ctx, 2))) { goto L_80081EE8; }
    R(12) = ld32(base, (R(3) + 0));
    R(4) = (0 + 1);
    R(12) = ld32(base, (R(12) + 8));
    ctx->ctr = R(12);
    GM_CALLV(0x80081EE8u, ctx->ctr, 0);
L_80081EE8:;
    R(3) = ld32(base, (R(30) + 148));
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    GM_CALLV(0x80081EFCu, ctx->ctr, 0);
    R(0) = (0 + 0);
    st32(base, (R(30) + 148), R(0));
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    st32(base, (R(13) + -22656), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_80081F18; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80081F18u, 0x802B9280u, 0);
L_80081F18:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_80081F40 (fn_80081F40, 272 bytes) */
static void bg_m_81f40(GM_CTX) {
    GM_FN(0x80081F40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 48);
    R(24) = R(3) |R(3);
    R(25) = (0 + 0);
    R(28) = (0 + 0);
    R(30) = (0 + 0);
    R(29) = (0 + 0x80370000u);
    R(31) = (0 + 1024);
L_80081F6C:;
    R(27) = R(24) + R(28);
    R(26) = (0 + 0);
L_80081F74:;
    R(4) = ld32(base, (R(29) + 31816));
    R(3) = (0 + 0x10000u);
    R(5) = (0 + 4);
    GM_CALLV(0x80081F84u, 0x802B9270u, 0);
    R(4) = R(3) |R(3);
    ctx->ctr = R(31);
L_80081F8C:;
    st16(base, (R(4) + 0), R(30));
    st16(base, (R(4) + 2), R(30));
    st16(base, (R(4) + 4), R(30));
    st16(base, (R(4) + 6), R(30));
    st16(base, (R(4) + 8), R(30));
    st16(base, (R(4) + 10), R(30));
    st16(base, (R(4) + 12), R(30));
    st16(base, (R(4) + 14), R(30));
    st16(base, (R(4) + 16), R(30));
    st16(base, (R(4) + 18), R(30));
    st16(base, (R(4) + 20), R(30));
    st16(base, (R(4) + 22), R(30));
    st16(base, (R(4) + 24), R(30));
    st16(base, (R(4) + 26), R(30));
    st16(base, (R(4) + 28), R(30));
    st16(base, (R(4) + 30), R(30));
    st16(base, (R(4) + 32), R(30));
    st16(base, (R(4) + 34), R(30));
    st16(base, (R(4) + 36), R(30));
    st16(base, (R(4) + 38), R(30));
    st16(base, (R(4) + 40), R(30));
    st16(base, (R(4) + 42), R(30));
    st16(base, (R(4) + 44), R(30));
    st16(base, (R(4) + 46), R(30));
    st16(base, (R(4) + 48), R(30));
    st16(base, (R(4) + 50), R(30));
    st16(base, (R(4) + 52), R(30));
    st16(base, (R(4) + 54), R(30));
    st16(base, (R(4) + 56), R(30));
    st16(base, (R(4) + 58), R(30));
    st16(base, (R(4) + 60), R(30));
    st16(base, (R(4) + 62), R(30));
    R(4) = (R(4) + 64);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80081F8C; }
    R(26) = (R(26) + 1);
    st32(base, (R(27) + 4), R(3));
    cr_cmp_s(ctx, 0, (int32_t)R(26), 4);
    R(27) = (R(27) + 12);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80081F74; }
    R(25) = (R(25) + 1);
    R(28) = (R(28) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(25), 3);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80081F6C; }
    R(11) = (f + 48);
    R(0) = lr;
}

/* fn_80082050 (fn_80082050, 124 bytes) */
static void bg_m_82050(GM_CTX) {
    GM_FN(0x80082050); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(27) = R(3) |R(3);
    R(29) = (0 + 0);
    R(31) = (0 + 0);
L_80082070:;
    R(30) = R(27) + R(31);
    R(28) = (0 + 0);
L_80082078:;
    R(0) = ld32(base, (R(30) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80082094; }
    R(3) = R(27) |R(27);
    R(5) = R(29) |R(29);
    R(4) = R(28) & 0xFFFFu;
    GM_CALLV(0x80082094u, 0x800820D0u, 0);
L_80082094:;
    R(28) = (R(28) + 1);
    R(30) = (R(30) + 12);
    cr_cmp_s(ctx, 0, (int32_t)R(28), 4);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80082078; }
    R(29) = (R(29) + 1);
    R(31) = (R(31) + 4);
    cr_cmp_s(ctx, 0, (int32_t)R(29), 3);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80082070; }
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_800820D0 (fn_800820D0, 76 bytes) */
static void bg_m_820d0(GM_CTX) {
    GM_FN(0x800820D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = ((int32_t)R(4) * 12);
    R(0) = rotl32(R(5), 2) & 0xFFFFFFFCu;
    R(3) = R(3) + R(4);
    R(31) = R(3) + R(0);
    R(3) = ld32(base, (R(31) + 4));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80082108; }
    GM_CALLV(0x80082100u, 0x802B9290u, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 4), R(0));
L_80082108:;
    R(0) = lr;
}

/* fn_80082120 (fn_80082120, 32 bytes) */
static void bg_m_82120(GM_CTX) {
    R(7) = ((int32_t)R(4) * 12);
    R(4) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(0) = rotl32(R(5), 1) & 0x1FFFEu;
    R(3) = R(3) + R(7);
    R(3) = R(3) + R(4);
    R(3) = ld32(base, (R(3) + 4));
    R(3) = ld16(base, (R(3) + R(0)));
}

/* fn_80082140 (fn_80082140, 32 bytes) */
static void bg_m_82140(GM_CTX) {
    R(8) = ((int32_t)R(4) * 12);
    R(4) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(0) = rotl32(R(5), 1) & 0x1FFFEu;
    R(3) = R(3) + R(8);
    R(3) = R(3) + R(4);
    R(3) = ld32(base, (R(3) + 4));
    st16(base, (R(3) + R(0)), R(7));
}

/* fn_80082160 (fn_80082160, 24 bytes) */
static void bg_m_82160(GM_CTX) {
    R(0) = (0 + 0);
    st32(base, (R(3) + 132), R(0));
    st32(base, (R(3) + 136), R(0));
    st32(base, (R(3) + 140), R(0));
    st32(base, (R(3) + 144), R(0));
}

/* fn_80082180 (fn_80082180, 84 bytes) */
static void bg_m_82180(GM_CTX) {
    R(4) = ld32(base, (R(13) + -22704));
    { uint32_t ea_ = (R(3) + 56); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(4) = (R(4) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29140); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -344); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800821B4; }
    R(0) = (0 + 0);
    st8(base, (R(3) + 128), R(0));
    return;
L_800821B4:;
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800821C8; }
    R(0) = (0 + 2);
    st8(base, (R(3) + 128), R(0));
    return;
L_800821C8:;
    R(0) = (0 + 1);
    st8(base, (R(3) + 128), R(0));
}

/* fn_800821E0 (fn_800821E0, 84 bytes) */
static void bg_m_821e0(GM_CTX) {
    R(4) = ld32(base, (R(13) + -22704));
    { uint32_t ea_ = (R(3) + 60); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(4) = (R(4) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29140); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + -340); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[3].d - ctx->f[2].d);
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80082214; }
    R(0) = (0 + 0);
    st8(base, (R(3) + 129), R(0));
    return;
L_80082214:;
    cr_fcmp(ctx, 0, ctx->f[3].d, ctx->f[2].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80082228; }
    R(0) = (0 + 1);
    st8(base, (R(3) + 129), R(0));
    return;
L_80082228:;
    R(0) = (0 + 2);
    st8(base, (R(3) + 129), R(0));
}

/* getLoopScrollDispPosX__14dBgParameter_cFf (getLoopScrollDispPosX__14dBgParameter_cFf, 160 bytes) */
static void bg_getLoopScrollDispPosX__14dBgParameter_cF_82240(GM_CTX) {
    GM_FN(0x80082240); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(0) = ld32(base, (R(13) + -21624));
    ctx->f[29].u = ctx->f[1].u;
    { uint32_t ea_ = (R(3) + 56); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_800822B4; }
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x80082280u, 0x800789A0u, 0);
    ctx->f[31].u = ctx->f[1].u;
    R(3) = ld32(base, (R(13) + -22704));
    GM_CALLV(0x8008228Cu, 0x80078B40u, 0);
    cr_fcmp(ctx, 0, ctx->f[30].d, ctx->f[31].d);
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
    if ((!CR_BIT(ctx, 2))) { goto L_800822B4; }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[31].d + ctx->f[1].d);
    { uint32_t ea_ = (R(2) + -29148); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d * ctx->f[0].d);
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_800822B4; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[31].d);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[30].d + ctx->f[0].d);
L_800822B4:;
    ctx->f[1].u = ctx->f[30].u;
    R(0) = lr;
}

/* fn_800822E0 (fn_800822E0, 44 bytes) */
static void bg_m_822e0(GM_CTX) {
    GM_FN(0x800822E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800822F8; }
    GM_CALLV(0x800822F8u, 0x80081AB0u, 0);
L_800822F8:;
    R(0) = lr;
    R(3) = R(3) & 0x3FFu;
}

/* fn_80082310 (fn_80082310, 88 bytes) */
static void bg_m_82310(GM_CTX) {
    GM_FN(0x80082310); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x80082328u, 0x8016A010u, 0);
    R(4) = (0 + 0x80310000u);
    R(3) = (R(31) + 8);
    R(4) = (R(4) + -448);
    st32(base, (R(31) + 0), R(4));
    GM_CALLV(0x8008233Cu, 0x8016A5E0u, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 40), R(0));
    R(3) = (R(31) + 56);
    st32(base, (R(31) + 44), R(0));
    GM_CALLV(0x80082350u, 0x800148F0u, 0);
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_80082370 (fn_80082370, 152 bytes) */
static void bg_m_82370(GM_CTX) {
    GM_FN(0x80082370); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800823EC; }
    R(12) = (0 + 0x80310000u);
    R(12) = (R(12) + -448);
    st32(base, (R(3) + 0), R(12));
    R(12) = ld32(base, (R(12) + 16));
    ctx->ctr = R(12);
    GM_CALLV(0x800823ACu, ctx->ctr, 0);
    R(3) = (R(30) + 56);
    R(4) = (0 + -1);
    GM_CALLV(0x800823B8u, 0x80014910u, 0);
    R(3) = (R(30) + 8);
    R(4) = (0 + -1);
    GM_CALLV(0x800823C4u, 0x8016A630u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800823DC; }
    if ((CR_BIT(ctx, 2))) { goto L_800823DC; }
    R(3) = R(30) |R(30);
    R(4) = (0 + 0);
    GM_CALLV(0x800823DCu, 0x8016A030u, 0);
L_800823DC:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_800823EC; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x800823ECu, 0x802B9280u, 0);
L_800823EC:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* fn_80082410 (fn_80082410, 336 bytes) */
static void bg_m_82410(GM_CTX) {
    GM_FN(0x80082410); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(0) = ld16(base, (f + 42));
    R(30) = R(10) |R(10);
    st16(base, (R(3) + 36), R(4));
    R(26) = R(3) |R(3);
    R(27) = R(6) |R(6);
    R(31) = R(7) |R(7);
    st16(base, (R(3) + 38), R(5));
    R(28) = R(8) |R(8);
    R(29) = R(9) |R(9);
    R(4) = R(30) |R(30);
    st16(base, (R(3) + 52), R(0));
    R(5) = (0 + 32);
    st16(base, (R(3) + 48), R(6));
    st16(base, (R(3) + 50), R(7));
    R(3) = (R(3) + 8);
    GM_CALLV(0x80082464u, 0x8016A690u, 0);
    R(3) = R(26) |R(26);
    R(4) = (R(26) + 8);
    R(5) = (0 + 0);
    GM_CALLV(0x80082474u, 0x80007510u, 0);
    R(0) = ((int32_t)R(27) * (int32_t)R(31));
    cr_cmp_s(ctx, 0, (int32_t)R(28), 0);
    R(31) = rotl32(R(0), 1) & 0xFFFFFFFEu;
    if ((CR_BIT(ctx, 0))) { goto L_800824C4; }
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    R(5) = (0 + 4);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800824A0u, ctx->ctr, 0);
    st32(base, (R(26) + 40), R(3));
    R(5) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x800824B0u, 0x80160AD0u, 0);
    R(3) = R(26) |R(26);
    R(4) = (0 + 6);
    R(5) = (0 + 0);
    GM_CALLV(0x800824C0u, 0x8016A0F0u, 0);
    goto L_800824D8;
L_800824C4:;
    R(3) = R(26) |R(26);
    R(4) = (0 + 6);
    R(5) = (0 + 1);
    GM_CALLV(0x800824D4u, 0x8016A0F0u, 0);
    R(28) = (0 + 0);
L_800824D8:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((CR_BIT(ctx, 0))) { goto L_80082520; }
    R(12) = ld32(base, (R(30) + 0));
    R(3) = R(30) |R(30);
    R(4) = R(31) |R(31);
    R(5) = (0 + 4);
    R(12) = ld32(base, (R(12) + 20));
    ctx->ctr = R(12);
    GM_CALLV(0x800824FCu, ctx->ctr, 0);
    st32(base, (R(26) + 44), R(3));
    R(5) = R(31) |R(31);
    R(4) = (0 + 0);
    GM_CALLV(0x8008250Cu, 0x80160AD0u, 0);
    R(3) = R(26) |R(26);
    R(4) = (0 + 7);
    R(5) = (0 + 0);
    GM_CALLV(0x8008251Cu, 0x8016A0F0u, 0);
    goto L_80082534;
L_80082520:;
    R(3) = R(26) |R(26);
    R(4) = (0 + 7);
    R(5) = (0 + 1);
    GM_CALLV(0x80082530u, 0x8016A0F0u, 0);
    R(29) = (0 + 0);
L_80082534:;
    R(3) = R(26) |R(26);
    R(4) = R(28) |R(28);
    R(5) = R(29) |R(29);
    GM_CALLV(0x80082544u, 0x8016A2A0u, 0);
    R(11) = (f + 32);
    R(3) = (0 + 1);
    R(0) = lr;
}

/* fn_80082560 (fn_80082560, 120 bytes) */
static void bg_m_82560(GM_CTX) {
    GM_FN(0x80082560); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x80082578u, 0x8016A5D0u, 0);
    R(0) = ld32(base, (R(31) + 28));
    cr_cmp_u(ctx, 0, R(0), R(3));
    if ((CR_BIT(ctx, 2))) { goto L_800825C4; }
    R(3) = ld32(base, (R(31) + 40));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800825A0; }
    R(4) = (0 + 0);
    GM_CALLV(0x80082598u, 0x802B8F70u, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 40), R(0));
L_800825A0:;
    R(3) = ld32(base, (R(31) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800825BC; }
    R(4) = (0 + 0);
    GM_CALLV(0x800825B4u, 0x802B8F70u, 0);
    R(0) = (0 + 0);
    st32(base, (R(31) + 44), R(0));
L_800825BC:;
    R(3) = R(31) |R(31);
    GM_CALLV(0x800825C4u, 0x8016A090u, 0);
L_800825C4:;
    R(0) = lr;
}

/* fn_800825E0 (fn_800825E0, 116 bytes) */
static void bg_m_825e0(GM_CTX) {
    GM_FN(0x800825E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 6);
    R(5) = (f + 8);
    R(31) = R(3) |R(3);
    GM_CALLV(0x80082600u, 0x8016A110u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80082614; }
    R(0) = ld32(base, (f + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80082640; }
L_80082614:;
    R(0) = ld16(base, (R(31) + 52));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_80082640; }
    R(4) = ld32(base, (R(31) + 40));
    R(3) = R(31) |R(31);
    GM_CALLV(0x8008262Cu, 0x80082740u, 0);
    GM_CALLV(0x80082630u, 0x80164F50u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x80082638u, 0x802D2F80u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x80082640u, 0x802D2F20u, 0);
L_80082640:;
    R(0) = lr;
}

/* fn_80082660 (fn_80082660, 96 bytes) */
static void bg_m_82660(GM_CTX) {
    GM_FN(0x80082660); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = (0 + 7);
    R(5) = (f + 8);
    R(31) = R(3) |R(3);
    GM_CALLV(0x80082680u, 0x8016A110u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80082694; }
    R(0) = ld32(base, (f + 8));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_800826AC; }
L_80082694:;
    R(0) = ld16(base, (R(31) + 52));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((CR_BIT(ctx, 2))) { goto L_800826AC; }
    R(4) = ld32(base, (R(31) + 40));
    R(3) = R(31) |R(31);
    GM_CALLV(0x800826ACu, 0x80082740u, 0);
L_800826AC:;
    R(0) = lr;
}

/* fn_800826C0 (fn_800826C0, 28 bytes) */
static void bg_m_826c0(GM_CTX) {
    R(0) = ld16(base, (R(3) + 48));
    R(3) = ld32(base, (R(3) + 40));
    R(0) = ((int32_t)R(5) * (int32_t)R(0));
    R(0) = R(4) + R(0);
    R(0) = rotl32(R(0), 1) & 0xFFFFFFFEu;
    st16(base, (R(3) + R(0)), R(6));
}

/* fn_800826E0 (fn_800826E0, 92 bytes) */
static void bg_m_826e0(GM_CTX) {
    GM_FRAME(16); gptr f = gm_frame_sp;
    R(0) = ld32(base, (R(13) + -21624));
    R(4) = ld32(base, (R(13) + -22704));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_8008270C; }
    R(3) = (R(4) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -412); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
    goto L_80082718;
L_8008270C:;
    R(3) = (R(4) + 0x90000u);
    { uint32_t ea_ = (R(3) + -412); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
L_80082718:;
    R(3) = (R(4) + 0x90000u);
    { uint32_t ea_ = (R(2) + -29136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + -404); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = ld32(base, (f + 8));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    R(4) = ld32(base, (f + 12));
}

/* fn_80082740 (fn_80082740, 1176 bytes) */
static void bg_m_82740(GM_CTX) {
    GM_FN(0x80082740); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 160);
    R(21) = ld32(base, (R(13) + -22704));
    R(0) = (0 + 0x43300000u);
    R(25) = R(3) |R(3);
    { uint32_t ea_ = (R(2) + -29132); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(3) = (R(21) + 0x90000u);
    st32(base, (f + 80), R(0));
    { uint32_t ea_ = (R(3) + -356); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(26) = R(4) |R(4);
    { uint32_t ea_ = (R(3) + 12); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    st32(base, (f + 88), R(0));
    R(31) = ld32(base, (R(13) + -22656));
    if ((!CR_BIT(ctx, 1))) { goto L_800827B8; }
    { uint32_t ea_ = (R(2) + -29124); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_800827B8; }
    { uint32_t ea_ = (R(2) + -29128); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
L_800827B8:;
    { uint32_t ea_ = (R(2) + -29116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[28].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d + ctx->f[1].d);
    GM_CALLV(0x800827CCu, 0x802DCC4Cu, 0);
    { uint32_t ea_ = (R(2) + -29136); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(28) = (R(3) + 2);
    { uint32_t ea_ = (R(2) + -29120); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[28].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d + ctx->f[1].d);
    GM_CALLV(0x800827E4u, 0x802DCC4Cu, 0);
    R(0) = ld16(base, (R(25) + 48));
    R(27) = (R(3) + 2);
    cr_cmp_u(ctx, 0, R(28), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_800827F8; }
    R(28) = R(0) |R(0);
L_800827F8:;
    R(0) = ld16(base, (R(25) + 50));
    cr_cmp_u(ctx, 0, R(27), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_80082808; }
    R(27) = R(0) |R(0);
L_80082808:;
    R(3) = R(25) |R(25);
    GM_CALLV(0x80082810u, 0x800826E0u, 0);
    st32(base, (f + 24), R(3));
    R(3) = R(25) |R(25);
    st32(base, (f + 28), R(4));
    GM_CALLV(0x80082820u, 0x800826E0u, 0);
    R(6) = (R(21) + 0x90000u);
    R(5) = ld32(base, (R(13) + -22136));
    { uint32_t ea_ = (R(6) + -412); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29108); ctx->f[5].d = ctx->ps1[5] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(6) + -404); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[4].d = ctx->ps1[4] = frsp(ctx->f[0].d / ctx->f[5].d);
    R(6) = ld32(base, (R(13) + -21624));
    st32(base, (f + 16), R(3));
    { uint32_t ea_ = (R(31) + 56); ctx->f[7].d = ctx->ps1[7] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    { uint32_t ea_ = (R(5) + 40); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[2].d / ctx->f[5].d);
    { uint32_t ea_ = (R(31) + 60); ctx->f[8].d = ctx->ps1[8] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(5) + 44); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29096); ctx->f[3].u = ld64(base, ea_); }
    st32(base, (f + 20), R(4));
    { uint32_t ea_ = (R(2) + -29112); ctx->f[6].d = ctx->ps1[6] = ldfs(base, ea_); }
    ctx->f[4].u = fctiw_bits(ctx->f[4].d, 1);
    ctx->f[2].u = fctiw_bits(ctx->f[2].d, 1);
    { uint32_t ea_ = (f + 96); st64(base, ea_, ctx->f[4].u); }
    ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[7].d + ctx->f[1].d);
    ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[8].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 104); st64(base, ea_, ctx->f[2].u); }
    R(3) = ld32(base, (f + 100));
    R(0) = ld32(base, (f + 108));
    R(3) = R(3) ^ 0x80000000u;
    st32(base, (f + 84), R(3));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 92), R(0));
    { uint32_t ea_ = (f + 80); ctx->f[1].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 88); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[3].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[3].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[5].d * ctx->f[1].d);
    ctx->f[3].d = ctx->ps1[3] = frsp(ctx->f[5].d * ctx->f[0].d);
    if ((!CR_BIT(ctx, 2))) { goto L_800828D4; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[6].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 104); st64(base, ea_, ctx->f[0].u); }
    R(30) = ld32(base, (f + 108));
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800828F4; }
    R(30) = (0 + 0);
    goto L_800828F4;
L_800828D4:;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d - ctx->f[2].d);
    { uint32_t ea_ = (R(2) + -29104); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[6].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 104); st64(base, ea_, ctx->f[0].u); }
    R(30) = ld32(base, (f + 108));
    R(30) = (R(30) + -4096);
L_800828F4:;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d - ctx->f[3].d);
    { uint32_t ea_ = (R(2) + -29112); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    ctx->f[1].d = frsp(ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 104); st64(base, ea_, ctx->f[0].u); }
    R(29) = ld32(base, (f + 108));
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_80082924; }
    R(29) = (0 + 0);
    goto L_80082938;
L_80082924:;
    R(0) = ld16(base, (R(25) + 50));
    R(0) = R(0) - R(27);
    cr_cmp_u(ctx, 0, R(29), R(0));
    if ((!CR_BIT(ctx, 1))) { goto L_80082938; }
    R(29) = R(0) |R(0);
L_80082938:;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d - ctx->f[3].d);
    { uint32_t ea_ = (R(31) + 68); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[31].d - ctx->f[2].d);
    ctx->f[28].d = ctx->ps1[28] = frsp(ctx->f[0].d - ctx->f[1].d);
    if ((!CR_BIT(ctx, 2))) { goto L_80082978; }
    R(0) = (R(30) + -1);
    { uint32_t ea_ = (R(2) + -29096); ctx->f[2].u = ld64(base, ea_); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 84), R(0));
    { uint32_t ea_ = (R(2) + -29136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 80); ctx->f[1].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d - ctx->f[0].d);
    goto L_80082998;
L_80082978:;
    R(0) = R(30) ^ 0x80000000u;
    st32(base, (f + 92), R(0));
    { uint32_t ea_ = (R(2) + -29096); ctx->f[2].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 88); ctx->f[1].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(2) + -29136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[1].d);
    ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d - ctx->f[0].d);
L_80082998:;
    R(0) = (R(29) + -1);
    R(22) = (0 + 0x802F0000u);
    R(21) = R(0) ^ 0x80000000u;
    st32(base, (f + 84), R(21));
    { uint32_t ea_ = R(22) + -1688; R(23) = ld32(base, ea_); R(22) = ea_; }
    R(3) = (0 + 27);
    { uint32_t ea_ = (R(2) + -29096); ctx->f[2].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 80); ctx->f[0].u = ld64(base, ea_); }
    R(24) = ld32(base, (R(22) + 4));
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[2].d);
    { uint32_t ea_ = (R(2) + -29136); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(12) = ld32(base, (R(22) + 8));
    R(11) = ld32(base, (R(22) + 12));
    R(10) = ld32(base, (R(22) + 16));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d * ctx->f[2].d);
    R(9) = ld32(base, (R(22) + 20));
    R(8) = ld32(base, (R(22) + 24));
    R(7) = ld32(base, (R(22) + 28));
    ctx->f[28].d = ctx->ps1[28] = frsp(ctx->f[28].d + ctx->f[0].d);
    R(6) = ld32(base, (R(22) + 32));
    R(5) = ld32(base, (R(22) + 36));
    R(4) = ld32(base, (R(22) + 40));
    R(0) = ld32(base, (R(22) + 44));
    st32(base, (f + 32), R(23));
    { uint32_t ea_ = (R(2) + -29128); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    st32(base, (f + 36), R(24));
    st32(base, (f + 40), R(12));
    st32(base, (f + 44), R(11));
    st32(base, (f + 48), R(10));
    st32(base, (f + 52), R(9));
    st32(base, (f + 56), R(8));
    st32(base, (f + 60), R(7));
    st32(base, (f + 64), R(6));
    st32(base, (f + 68), R(5));
    st32(base, (f + 72), R(4));
    st32(base, (f + 76), R(0));
    { uint32_t ea_ = (R(31) + 64); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[0].d); }
    { uint32_t ea_ = (R(31) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].u = ctx->f[0].u ^ 0x8000000000000000ull;
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d * ctx->f[0].d);
    { uint32_t ea_ = (f + 60); stfs(base, ea_, ctx->f[0].d); }
    GM_CALLV(0x80082A4Cu, 0x801C9A60u, 0);
    R(21) = ld32(base, (R(13) + -22640));
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 1);
    R(3) = ld32(base, (R(21) + 36));
    GM_CALLV(0x80082A64u, 0x8010A9B0u, 0);
    R(0) = ld16(base, (R(25) + 52));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_80082A98; }
    R(0) = ld8(base, (R(25) + 54));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80082A88; }
    R(3) = (0 + 1);
    GM_CALLV(0x80082A84u, 0x801C8E40u, 0);
    goto L_80082A90;
L_80082A88:;
    R(3) = (0 + 0);
    GM_CALLV(0x80082A90u, 0x801C8E40u, 0);
L_80082A90:;
    R(3) = (0 + 1);
    GM_CALLV(0x80082A98u, 0x801C8E10u, 0);
L_80082A98:;
    ctx->f[1].u = ctx->f[29].u;
    st32(base, (f + 8), R(29));
    ctx->f[2].u = ctx->f[28].u;
    R(3) = R(25) |R(25);
    R(7) = R(28) |R(28);
    R(8) = R(27) |R(27);
    R(9) = R(26) |R(26);
    R(10) = R(30) |R(30);
    R(6) = (f + 32);
    R(4) = (0 + 1);
    R(5) = (0 + 0);
    GM_CALLV(0x80082AC8u, 0x80082BE0u, 0);
    ctx->f[1].u = ctx->f[31].u;
    R(3) = R(25) |R(25);
    ctx->f[2].u = ctx->f[30].u;
    R(5) = (f + 32);
    R(4) = (0 + 1);
    GM_CALLV(0x80082AE0u, 0x80082ED0u, 0);
    R(0) = ld8(base, (R(21) + 84));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80082B74; }
    R(0) = ld16(base, (R(25) + 52));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80082B74; }
    R(3) = ld32(base, (R(21) + 36));
    R(4) = (0 + 0);
    R(5) = (0 + 0);
    R(6) = (0 + 0);
    GM_CALLV(0x80082B0Cu, 0x8010A9B0u, 0);
    R(0) = ld16(base, (R(25) + 52));
    cr_cmp_u(ctx, 0, R(0), 0x2u);
    if ((!CR_BIT(ctx, 2))) { goto L_80082B2C; }
    R(0) = ld8(base, (R(25) + 54));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80082B2C; }
    R(3) = (0 + 1);
    GM_CALLV(0x80082B2Cu, 0x801C8E40u, 0);
L_80082B2C:;
    ctx->f[1].u = ctx->f[29].u;
    st32(base, (f + 8), R(29));
    ctx->f[2].u = ctx->f[28].u;
    R(3) = R(25) |R(25);
    R(7) = R(28) |R(28);
    R(8) = R(27) |R(27);
    R(9) = R(26) |R(26);
    R(10) = R(30) |R(30);
    R(6) = (f + 32);
    R(4) = (0 + 0);
    R(5) = (0 + 1);
    GM_CALLV(0x80082B5Cu, 0x80082BE0u, 0);
    ctx->f[1].u = ctx->f[31].u;
    R(3) = R(25) |R(25);
    ctx->f[2].u = ctx->f[30].u;
    R(5) = (f + 32);
    R(4) = (0 + 0);
    GM_CALLV(0x80082B74u, 0x80082ED0u, 0);
L_80082B74:;
    GM_CALLV(0x80082B78u, 0x8010AA30u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x80082B80u, 0x801C9A60u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x80082B88u, 0x801C8110u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x80082B90u, 0x801C8130u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x80082B98u, 0x801C8130u, 0);
    R(0) = (0 + 0);
    st8(base, (R(25) + 54), R(0));
    R(11) = (f + 160);
    R(0) = lr;
}

/* fn_80082BE0 (fn_80082BE0, 752 bytes) */
static void bg_m_82be0(GM_CTX) {
    GM_FN(0x80082BE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 208);
    R(0) = ld16(base, (R(3) + 52));
    ctx->f[30].u = ctx->f[1].u;
    ctx->f[31].u = ctx->f[2].u;
    R(23) = ld32(base, (f + 248));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    R(17) = R(3) |R(3);
    R(18) = R(4) |R(4);
    R(24) = R(6) |R(6);
    R(19) = R(7) |R(7);
    R(20) = R(8) |R(8);
    R(21) = R(9) |R(9);
    R(22) = R(10) |R(10);
    if ((CR_BIT(ctx, 2))) { goto L_80082C4C; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_80082C54; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_80082C5C; }
    goto L_80082C60;
L_80082C4C:;
    GM_CALLV(0x80082C50u, 0x80087340u, 0);
    goto L_80082C60;
L_80082C54:;
    GM_CALLV(0x80082C58u, 0x80087360u, 0);
    goto L_80082C60;
L_80082C5C:;
    { uint32_t ea_ = (R(2) + -29088); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
L_80082C60:;
    ctx->f[3].u = ctx->f[1].u;
    R(3) = (f + 8);
    ctx->f[2].u = ctx->f[31].u;
    ctx->f[1].u = ctx->f[30].u ^ 0x8000000000000000ull;
    GM_CALLV(0x80082C74u, 0x801C0BD0u, 0);
    R(3) = R(24) |R(24);
    R(4) = (f + 8);
    R(5) = (f + 56);
    GM_CALLV(0x80082C84u, 0x801C0540u, 0);
    R(3) = (f + 56);
    R(4) = (0 + 27);
    GM_CALLV(0x80082C90u, 0x801C9940u, 0);
    R(3) = (f + 56);
    R(4) = (0 + 27);
    GM_CALLV(0x80082C9Cu, 0x801C99C0u, 0);
    R(26) = ld32(base, (R(13) + -22704));
    R(0) = (0 + 0x43300000u);
    { uint32_t ea_ = (R(2) + -29108); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(4) = (R(26) + 0x90000u);
    st32(base, (f + 112), R(0));
    { uint32_t ea_ = (R(4) + -412); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = R(26) |R(26);
    { uint32_t ea_ = (R(4) + -404); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d / ctx->f[0].d);
    st32(base, (f + 128), R(0));
    R(24) = ld32(base, (R(13) + -22640));
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d / ctx->f[0].d);
    ctx->f[1].u = fctiw_bits(ctx->f[1].d, 1);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 104); st64(base, ea_, ctx->f[1].u); }
    { uint32_t ea_ = (f + 120); st64(base, ea_, ctx->f[0].u); }
    R(4) = ld32(base, (f + 108));
    R(0) = ld32(base, (f + 124));
    R(4) = R(4) ^ 0x80000000u;
    st32(base, (f + 116), R(4));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 132), R(0));
    GM_CALLV(0x80082CF8u, 0x800789A0u, 0);
    ctx->f[31].u = ctx->f[1].u;
    R(3) = R(26) |R(26);
    GM_CALLV(0x80082D04u, 0x80078B40u, 0);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[31].d);
    R(30) = ld8(base, (R(24) + 84));
    R(31) = (R(26) + 0x90000u);
    R(27) = (0 + 0);
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    { uint32_t ea_ = (f + 136); st64(base, ea_, ctx->f[0].u); }
    R(0) = ld32(base, (f + 140));
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0xFu) != 0; R(0) = (v_ >> 4); }
    { uint64_t t_ = (uint64_t)(R(0)) + (0) + ctx->xer_ca; R(28) = t_; ctx->xer_ca = (t_ >> 32); }
    goto L_80082EA0;
L_80082D2C:;
    R(29) = R(22) |R(22);
    R(26) = (0 + 0);
    goto L_80082E90;
L_80082D38:;
    R(0) = (int16_t)ld16(base, (R(31) + 2504));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80082D70; }
    R(3) = ld16(base, (R(17) + 48));
    R(4) = R(3) + R(29);
    R(0) = divwu(R(4), R(3));
    R(5) = ((int32_t)R(3) * (int32_t)R(23));
    R(3) = ((int32_t)R(0) * (int32_t)R(3));
    R(0) = rotl32(R(5), 1) & 0xFFFFFFFEu;
    R(0) = R(21) + R(0);
    R(3) = R(4) - R(3);
    R(3) = rotl32(R(3), 1) & 0xFFFFFFFEu;
    R(25) = ld16(base, (R(3) + R(0)));
    goto L_80082E14;
L_80082D70:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_80082DA8; }
    R(4) = R(28) + R(29);
    R(3) = ld16(base, (R(17) + 48));
    R(0) = divwu(R(4), R(28));
    R(5) = ((int32_t)R(3) * (int32_t)R(23));
    R(3) = ((int32_t)R(0) * (int32_t)R(28));
    R(0) = rotl32(R(5), 1) & 0xFFFFFFFEu;
    R(0) = R(21) + R(0);
    R(3) = R(4) - R(3);
    R(3) = rotl32(R(3), 1) & 0xFFFFFFFEu;
    R(3) = R(3) + R(0);
    R(25) = ld16(base, (R(3) + 78));
    goto L_80082E14;
L_80082DA8:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((!CR_BIT(ctx, 2))) { goto L_80082DE0; }
    R(4) = R(28) + R(29);
    R(3) = ld16(base, (R(17) + 48));
    R(0) = divwu(R(4), R(28));
    R(5) = ((int32_t)R(3) * (int32_t)R(23));
    R(3) = ((int32_t)R(0) * (int32_t)R(28));
    R(0) = rotl32(R(5), 1) & 0xFFFFFFFEu;
    R(0) = R(21) + R(0);
    R(3) = R(4) - R(3);
    R(3) = rotl32(R(3), 1) & 0xFFFFFFFEu;
    R(3) = R(3) + R(0);
    R(25) = ld16(base, (R(3) + 270));
    goto L_80082E14;
L_80082DE0:;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_80082E14; }
    R(4) = R(28) + R(29);
    R(3) = ld16(base, (R(17) + 48));
    R(0) = divwu(R(4), R(28));
    R(5) = ((int32_t)R(3) * (int32_t)R(23));
    R(3) = ((int32_t)R(0) * (int32_t)R(28));
    R(0) = rotl32(R(5), 1) & 0xFFFFFFFEu;
    R(0) = R(21) + R(0);
    R(3) = R(4) - R(3);
    R(3) = rotl32(R(3), 1) & 0xFFFFFFFEu;
    R(3) = R(3) + R(0);
    R(25) = ld16(base, (R(3) + 458));
L_80082E14:;
    R(24) = R(25) & 0x3FFu;
    CR0(ctx, R(24));
    if ((CR_BIT(ctx, 2))) { goto L_80082E88; }
    cr_cmp_s(ctx, 0, (int32_t)R(18), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80082E40; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80082E54; }
    cr_cmp_u(ctx, 0, R(24), 0x2C0u);
    if ((CR_BIT(ctx, 0))) { goto L_80082E54; }
    cr_cmp_u(ctx, 0, R(24), 0x2FFu);
    if ((!CR_BIT(ctx, 1))) { goto L_80082E88; }
    goto L_80082E54;
L_80082E40:;
    R(3) = (R(24) + 0x10000u);
    R(0) = (R(3) + -704);
    R(0) = R(0) & 0xFFFFu;
    cr_cmp_u(ctx, 0, R(0), 0x3Fu);
    if ((CR_BIT(ctx, 1))) { goto L_80082E88; }
L_80082E54:;
    cr_cmp_u(ctx, 0, R(24), 0x100u);
    if ((!CR_BIT(ctx, 0))) { goto L_80082E6C; }
    R(3) = R(25) |R(25);
    R(4) = (0 + 1);
    GM_CALLV(0x80082E68u, 0x800822E0u, 0);
    R(24) = R(3) |R(3);
L_80082E6C:;
    R(3) = (0 + 1);
    GM_CALLV(0x80082E74u, 0x8010AA40u, 0);
    R(4) = R(26) |R(26);
    R(5) = R(27) |R(27);
    R(3) = R(24) & 0xFFFFu;
    GM_CALLV(0x80082E84u, 0x8010AA60u, 0);
    GM_CALLV(0x80082E88u, 0x8010AA90u, 0);
L_80082E88:;
    R(29) = (R(29) + 1);
    R(26) = (R(26) + 1);
L_80082E90:;
    cr_cmp_u(ctx, 0, R(26), R(19));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80082D38; }
    R(23) = (R(23) + 1);
    R(27) = (R(27) + 1);
L_80082EA0:;
    cr_cmp_u(ctx, 0, R(27), R(20));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80082D2C; }
    R(11) = (f + 208);
    R(0) = lr;
}

/* fn_80082ED0 (fn_80082ED0, 1192 bytes) */
static void bg_m_82ed0(GM_CTX) {
    GM_FN(0x80082ED0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 272);
    R(7) = ld32(base, (R(13) + -22656));
    ctx->f[27].u = ctx->f[1].u;
    R(6) = ld32(base, (R(13) + -22640));
    R(28) = R(3) |R(3);
    { uint32_t ea_ = (R(7) + 68); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    R(26) = R(4) |R(4);
    R(30) = ld8(base, (R(6) + 84));
    ctx->f[24].d = ctx->ps1[24] = frsp(ctx->f[2].d - ctx->f[0].d);
    R(27) = R(5) |R(5);
    GM_CALLV(0x80082F64u, 0x801C4070u, 0);
    R(3) = (0 + 9);
    R(4) = (0 + 1);
    GM_CALLV(0x80082F70u, 0x801C37C0u, 0);
    R(3) = (0 + 13);
    R(4) = (0 + 1);
    GM_CALLV(0x80082F7Cu, 0x801C37C0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 9);
    R(5) = (0 + 1);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x80082F94u, 0x801C40B0u, 0);
    R(3) = (0 + 0);
    R(4) = (0 + 13);
    R(5) = (0 + 1);
    R(6) = (0 + 4);
    R(7) = (0 + 0);
    GM_CALLV(0x80082FACu, 0x801C40B0u, 0);
    R(0) = ld32(base, (R(28) + 56));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80083308; }
    R(29) = ld32(base, (R(28) + 60));
    { uint32_t ea_ = (R(2) + -29136); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29084); ctx->f[30].d = ctx->ps1[30] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29080); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29132); ctx->f[28].d = ctx->ps1[28] = ldfs(base, ea_); }
    goto L_80083300;
L_80082FD0:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x80082FD8u, 0x80014630u, 0);
    R(31) = R(3) |R(3);
    R(3) = R(29) |R(29);
    GM_CALLV(0x80082FE4u, 0x80014640u, 0);
    R(4) = R(3) |R(3);
    R(3) = R(31) & 0xFFFFu;
    GM_CALLV(0x80082FF0u, 0x800822E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(26), 0);
    R(28) = R(3) & 0xFFFFu;
    if ((CR_BIT(ctx, 2))) { goto L_80083018; }
    cr_cmp_s(ctx, 0, (int32_t)R(30), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80083024; }
    cr_cmp_u(ctx, 0, R(28), 0x2C0u);
    if ((CR_BIT(ctx, 0))) { goto L_80083024; }
    cr_cmp_u(ctx, 0, R(28), 0x2FFu);
    if ((!CR_BIT(ctx, 1))) { goto L_800832FC; }
    goto L_80083024;
L_80083018:;
    R(0) = (R(28) + -704);
    cr_cmp_u(ctx, 0, R(0), 0x3Fu);
    if ((CR_BIT(ctx, 1))) { goto L_800832FC; }
L_80083024:;
    R(3) = R(29) |R(29);
    GM_CALLV(0x8008302Cu, 0x80014670u, 0);
    ctx->f[25].u = ctx->f[1].u;
    R(3) = R(29) |R(29);
    GM_CALLV(0x80083038u, 0x80014680u, 0);
    ctx->f[26].u = ctx->f[1].u;
    R(3) = R(29) |R(29);
    GM_CALLV(0x80083044u, 0x80014690u, 0);
    ctx->f[23].u = ctx->f[1].u;
    R(3) = R(29) |R(29);
    GM_CALLV(0x80083050u, 0x800146C0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80083070; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800830F0; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 2))) { goto L_80083194; }
    goto L_80083270;
L_80083070:;
    ctx->f[1].u = ctx->f[27].u ^ 0x8000000000000000ull;
    R(3) = (f + 152);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[24].d + ctx->f[26].d);
    ctx->f[3].u = ctx->f[23].u;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[25].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[31].d + ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d + ctx->f[1].d);
    GM_CALLV(0x80083090u, 0x801C0BD0u, 0);
    R(3) = R(27) |R(27);
    R(4) = (f + 152);
    R(5) = (f + 200);
    GM_CALLV(0x800830A0u, 0x801C0540u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x800830A8u, 0x80014710u, 0);
    ctx->f[2].u = ctx->f[1].u;
    { uint32_t ea_ = (R(2) + -29124); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 8);
    GM_CALLV(0x800830B8u, 0x801C0C60u, 0);
    R(3) = (f + 200);
    R(4) = (f + 8);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800830C8u, 0x801C0540u, 0);
    ctx->f[1].u = ctx->f[30].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(2) + -29132); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[31].u ^ 0x8000000000000000ull;
    R(3) = (f + 104);
    GM_CALLV(0x800830DCu, 0x801C0BD0u, 0);
    R(3) = (f + 200);
    R(4) = (f + 104);
    R(5) = R(3) |R(3);
    GM_CALLV(0x800830ECu, 0x801C0540u, 0);
    goto L_80083298;
L_800830F0:;
    ctx->f[1].u = ctx->f[27].u ^ 0x8000000000000000ull;
    R(3) = (f + 152);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[24].d + ctx->f[26].d);
    ctx->f[3].u = ctx->f[23].u;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[25].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[30].d + ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[30].d + ctx->f[1].d);
    GM_CALLV(0x80083110u, 0x801C0BD0u, 0);
    R(3) = R(27) |R(27);
    R(4) = (f + 152);
    R(5) = (f + 200);
    GM_CALLV(0x80083120u, 0x801C0540u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x80083128u, 0x80014750u, 0);
    R(3) = (f + 56);
    R(4) = (0 + 122);
    GM_CALLV(0x80083134u, 0x801C0970u, 0);
    R(3) = (f + 200);
    R(4) = (f + 56);
    R(5) = R(3) |R(3);
    GM_CALLV(0x80083144u, 0x801C0540u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8008314Cu, 0x80014710u, 0);
    ctx->f[2].u = ctx->f[1].u;
    { uint32_t ea_ = (R(2) + -29124); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 8);
    GM_CALLV(0x8008315Cu, 0x801C0C60u, 0);
    R(3) = (f + 200);
    R(4) = (f + 8);
    R(5) = R(3) |R(3);
    GM_CALLV(0x8008316Cu, 0x801C0540u, 0);
    ctx->f[1].u = ctx->f[30].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(2) + -29132); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = (f + 104);
    ctx->f[2].u = ctx->f[1].u;
    GM_CALLV(0x80083180u, 0x801C0BD0u, 0);
    R(3) = (f + 200);
    R(4) = (f + 104);
    R(5) = R(3) |R(3);
    GM_CALLV(0x80083190u, 0x801C0540u, 0);
    goto L_80083298;
L_80083194:;
    ctx->f[22].u = ctx->f[30].u;
    R(3) = R(29) |R(29);
    ctx->f[21].u = ctx->f[30].u;
    GM_CALLV(0x800831A4u, 0x800147E0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800831C8; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 1);
    if ((CR_BIT(ctx, 2))) { goto L_800831D4; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 2);
    if ((CR_BIT(ctx, 2))) { goto L_800831E0; }
    cr_cmp_s(ctx, 0, (int32_t)R(3), 3);
    if ((CR_BIT(ctx, 2))) { goto L_800831EC; }
    goto L_800831F4;
L_800831C8:;
    ctx->f[22].d = ctx->ps1[22] = frsp(ctx->f[30].d - ctx->f[29].d);
    ctx->f[21].u = ctx->f[22].u;
    goto L_800831F4;
L_800831D4:;
    ctx->f[22].d = ctx->ps1[22] = frsp(ctx->f[30].d + ctx->f[29].d);
    ctx->f[21].d = ctx->ps1[21] = frsp(ctx->f[30].d - ctx->f[29].d);
    goto L_800831F4;
L_800831E0:;
    ctx->f[22].d = ctx->ps1[22] = frsp(ctx->f[30].d - ctx->f[29].d);
    ctx->f[21].d = ctx->ps1[21] = frsp(ctx->f[30].d + ctx->f[29].d);
    goto L_800831F4;
L_800831EC:;
    ctx->f[22].d = ctx->ps1[22] = frsp(ctx->f[30].d + ctx->f[29].d);
    ctx->f[21].u = ctx->f[22].u;
L_800831F4:;
    ctx->f[1].u = ctx->f[27].u ^ 0x8000000000000000ull;
    R(3) = (f + 152);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[24].d + ctx->f[26].d);
    ctx->f[3].u = ctx->f[23].u;
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[25].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[21].d + ctx->f[0].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[22].d + ctx->f[1].d);
    GM_CALLV(0x80083214u, 0x801C0BD0u, 0);
    R(3) = R(27) |R(27);
    R(4) = (f + 152);
    R(5) = (f + 200);
    GM_CALLV(0x80083224u, 0x801C0540u, 0);
    R(3) = R(29) |R(29);
    GM_CALLV(0x8008322Cu, 0x80014750u, 0);
    R(3) = (f + 56);
    R(4) = (0 + 122);
    GM_CALLV(0x80083238u, 0x801C0970u, 0);
    R(3) = (f + 200);
    R(4) = (f + 56);
    R(5) = R(3) |R(3);
    GM_CALLV(0x80083248u, 0x801C0540u, 0);
    ctx->f[1].u = ctx->f[22].u ^ 0x8000000000000000ull;
    { uint32_t ea_ = (R(2) + -29132); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[21].u ^ 0x8000000000000000ull;
    R(3) = (f + 104);
    GM_CALLV(0x8008325Cu, 0x801C0BD0u, 0);
    R(3) = (f + 200);
    R(4) = (f + 104);
    R(5) = R(3) |R(3);
    GM_CALLV(0x8008326Cu, 0x801C0540u, 0);
    goto L_80083298;
L_80083270:;
    ctx->f[0].u = ctx->f[27].u ^ 0x8000000000000000ull;
    R(3) = (f + 152);
    ctx->f[3].u = ctx->f[23].u;
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[24].d + ctx->f[26].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d + ctx->f[25].d);
    GM_CALLV(0x80083288u, 0x801C0BD0u, 0);
    R(3) = R(27) |R(27);
    R(4) = (f + 152);
    R(5) = (f + 200);
    GM_CALLV(0x80083298u, 0x801C0540u, 0);
L_80083298:;
    R(3) = (f + 200);
    R(4) = (0 + 27);
    GM_CALLV(0x800832A4u, 0x801C9940u, 0);
    R(3) = (f + 200);
    R(4) = (0 + 27);
    GM_CALLV(0x800832B0u, 0x801C99C0u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x800832B8u, 0x8010AA40u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(31), 3);
    if ((!CR_BIT(ctx, 2))) { goto L_800832E4; }
    R(3) = R(29) |R(29);
    GM_CALLV(0x800832C8u, 0x800147E0u, 0);
    ctx->f[1].u = ctx->f[28].u;
    R(4) = R(3) |R(3);
    ctx->f[2].u = ctx->f[28].u;
    { uint32_t ea_ = (R(2) + -29132); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    R(3) = R(28) |R(28);
    GM_CALLV(0x800832E0u, 0x8010AA80u, 0);
    goto L_800832F8;
L_800832E4:;
    ctx->f[1].u = ctx->f[28].u;
    { uint32_t ea_ = (R(2) + -29132); ctx->f[3].d = ctx->ps1[3] = ldfs(base, ea_); }
    ctx->f[2].u = ctx->f[28].u;
    R(3) = R(28) |R(28);
    GM_CALLV(0x800832F8u, 0x8010AA70u, 0);
L_800832F8:;
    GM_CALLV(0x800832FCu, 0x8010AA90u, 0);
L_800832FC:;
    R(29) = ld32(base, (R(29) + 4));
L_80083300:;
    cr_cmp_s(ctx, 0, (int32_t)R(29), 0);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_80082FD0; }
L_80083308:;
    R(11) = (f + 272);
    R(0) = lr;
}

/* fn_80083380 (fn_80083380, 84 bytes) */
static void bg_m_83380(GM_CTX) {
    R(0) = ld16(base, (R(3) + 36));
    R(7) = ld16(base, (R(3) + 48));
    R(4) = R(4) - R(0);
    R(0) = ld16(base, (R(3) + 38));
    cr_cmp_u(ctx, 0, R(4), R(7));
    R(5) = R(5) - R(0);
    if ((!CR_BIT(ctx, 0))) { goto L_800833C8; }
    R(0) = ld16(base, (R(3) + 50));
    cr_cmp_u(ctx, 0, R(5), R(0));
    if ((!CR_BIT(ctx, 0))) { goto L_800833C8; }
    R(0) = ((int32_t)R(7) * (int32_t)R(5));
    R(3) = ld32(base, (R(3) + 40));
    R(4) = rotl32(R(4), 1) & 0xFFFFFFFEu;
    R(0) = rotl32(R(0), 1) & 0xFFFFFFFEu;
    R(0) = R(3) + R(0);
    R(3) = ld16(base, (R(4) + R(0)));
    st16(base, (R(4) + R(0)), R(6));
    return;
L_800833C8:;
    R(3) = (0 + 0x10000u);
    R(3) = (R(3) + -1);
}

/* fn_800833E0 (fn_800833E0, 96 bytes) */
static void bg_m_833e0(GM_CTX) {
    GM_FN(0x800833E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    GM_CALLV(0x800833F8u, 0x8000F270u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80083408; }
    R(3) = (0 + 0);
    goto L_8008342C;
L_80083408:;
    R(3) = R(31) |R(31);
    R(4) = (0 + 6);
    R(5) = (0 + -1);
    GM_CALLV(0x80083418u, 0x8016A2A0u, 0);
    R(3) = R(31) |R(31);
    R(4) = (0 + 7);
    R(5) = (0 + 1);
    GM_CALLV(0x80083428u, 0x8016A0F0u, 0);
    R(3) = (0 + 1);
L_8008342C:;
    R(0) = lr;
}

/* fn_80083440 (fn_80083440, 48 bytes) */
static void bg_m_83440(GM_CTX) {
    GM_FN(0x80083440); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    GM_CALLV(0x80083450u, 0x8000F2E0u, 0);
    R(3) = (0 + 0);
    GM_CALLV(0x80083458u, 0x801C8E40u, 0);
    R(3) = (0 + 1);
    GM_CALLV(0x80083460u, 0x801C8E10u, 0);
    R(0) = lr;
}

/* fn_800834B0 (fn_800834B0, 20 bytes) */
static void bg_m_834b0(GM_CTX) {
    R(4) = (0 + 0x802F0000u);
    R(0) = rotl32(R(3), 1) & 0x1FFFEu;
    R(4) = (R(4) + -1640);
    R(3) = ld16(base, (R(4) + R(0)));
}

/* fn_800834D0 (fn_800834D0, 132 bytes) */
static void bg_m_834d0(GM_CTX) {
    GM_FN(0x800834D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(4) |R(4);
    R(30) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_80083538; }
    R(0) = ld32(base, (R(3) + 3108));
    R(4) = (0 + 0x80310000u);
    R(4) = (R(4) + 2320);
    st32(base, (R(3) + 0), R(4));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80083528; }
    R(3) = R(0) |R(0);
    R(12) = ld32(base, (R(3) + 0));
    R(12) = ld32(base, (R(12) + 28));
    ctx->ctr = R(12);
    GM_CALLV(0x80083520u, ctx->ctr, 0);
    R(0) = (0 + 0);
    st32(base, (R(30) + 3108), R(0));
L_80083528:;
    cr_cmp_s(ctx, 0, (int32_t)R(31), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_80083538; }
    R(3) = R(30) |R(30);
    GM_CALLV(0x80083538u, 0x802B9280u, 0);
L_80083538:;
    R(3) = R(30) |R(30);
    R(0) = lr;
}

/* OriginalTilesetLoadingThing (OriginalTilesetLoadingThing, 252 bytes) */
static void bg_OriginalTilesetLoadingThing_83560(GM_CTX) {
    GM_FN(0x80083560); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(0) = (0 + 0);
    R(31) = R(3) |R(3);
    R(30) = R(6) |R(6);
    R(29) = R(5) |R(5);
    R(28) = R(4) |R(4);
    if ((!CR_BIT(ctx, 2))) { goto L_80083600; }
    R(3) = (0 + 3116);
    R(5) = (0 + 4);
    GM_CALLV(0x800835A4u, 0x802B9240u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    R(31) = R(3) |R(3);
    if ((CR_BIT(ctx, 2))) { goto L_800835CC; }
    R(4) = (0 + 0x80310000u);
    R(0) = (0 + 0);
    R(4) = (R(4) + 2320);
    st32(base, (R(3) + 0), R(4));
    st32(base, (R(3) + 3100), R(30));
    st32(base, (R(3) + 3104), R(29));
    st32(base, (R(3) + 3108), R(0));
L_800835CC:;
    R(12) = ld32(base, (R(28) + 0));
    R(3) = R(28) |R(28);
    R(4) = (0 + 4);
    R(12) = ld32(base, (R(12) + 40));
    ctx->ctr = R(12);
    GM_CALLV(0x800835E4u, ctx->ctr, 0);
    R(4) = R(28) |R(28);
    R(5) = (0 + 0);
    R(6) = (0 + 32);
    R(7) = (0 + 0);
    R(3) = (R(3) + -256);
    GM_CALLV(0x800835FCu, 0x8016E630u, 0);
    R(0) = R(3) |R(3);
L_80083600:;
    R(3) = R(31) |R(31);
    R(4) = R(0) |R(0);
    GM_CALLV(0x8008360Cu, 0x80083AD0u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80083614u, 0x80083870u, 0);
    R(3) = ld32(base, (R(13) + -22672));
    R(4) = R(29) |R(29);
    R(5) = R(30) |R(30);
    GM_CALLV(0x80083624u, 0x800818B0u, 0);
    R(4) = R(3) |R(3);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80083630u, 0x80083D00u, 0);
    R(3) = R(31) |R(31);
    GM_CALLV(0x80083638u, 0x80083B30u, 0);
    R(3) = R(31) |R(31);
    R(0) = lr;
}

/* fn_80083660 (fn_80083660, 360 bytes) */
static void bg_m_83660(GM_CTX) {
    R(0) = (0 + 64);
    R(6) = (0 + 0);
    R(4) = (0 + 0);
    ctx->ctr = R(0);
L_80083670:;
    R(5) = R(3) + R(6);
    R(6) = (R(6) + 8);
    st8(base, (R(5) + 1032), R(4));
    st8(base, (R(5) + 1033), R(4));
    st8(base, (R(5) + 1034), R(4));
    st8(base, (R(5) + 1035), R(4));
    st8(base, (R(5) + 1036), R(4));
    st8(base, (R(5) + 1037), R(4));
    st8(base, (R(5) + 1038), R(4));
    st8(base, (R(5) + 1039), R(4));
    R(5) = R(3) + R(6);
    R(6) = (R(6) + 8);
    st8(base, (R(5) + 1032), R(4));
    st8(base, (R(5) + 1033), R(4));
    st8(base, (R(5) + 1034), R(4));
    st8(base, (R(5) + 1035), R(4));
    st8(base, (R(5) + 1036), R(4));
    st8(base, (R(5) + 1037), R(4));
    st8(base, (R(5) + 1038), R(4));
    st8(base, (R(5) + 1039), R(4));
    R(5) = R(3) + R(6);
    R(6) = (R(6) + 8);
    st8(base, (R(5) + 1032), R(4));
    st8(base, (R(5) + 1033), R(4));
    st8(base, (R(5) + 1034), R(4));
    st8(base, (R(5) + 1035), R(4));
    st8(base, (R(5) + 1036), R(4));
    st8(base, (R(5) + 1037), R(4));
    st8(base, (R(5) + 1038), R(4));
    st8(base, (R(5) + 1039), R(4));
    R(5) = R(3) + R(6);
    R(6) = (R(6) + 8);
    st8(base, (R(5) + 1032), R(4));
    st8(base, (R(5) + 1033), R(4));
    st8(base, (R(5) + 1034), R(4));
    st8(base, (R(5) + 1035), R(4));
    st8(base, (R(5) + 1036), R(4));
    st8(base, (R(5) + 1037), R(4));
    st8(base, (R(5) + 1038), R(4));
    st8(base, (R(5) + 1039), R(4));
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80083670; }
    R(0) = (0 + 8);
    R(5) = R(3) |R(3);
    R(6) = (0 + 0);
    R(4) = (0 + 0);
    ctx->ctr = R(0);
L_80083728:;
    st32(base, (R(5) + 4), R(4));
    R(6) = (R(6) + 32);
    st32(base, (R(5) + 8), R(4));
    st32(base, (R(5) + 12), R(4));
    st32(base, (R(5) + 16), R(4));
    st32(base, (R(5) + 20), R(4));
    st32(base, (R(5) + 24), R(4));
    st32(base, (R(5) + 28), R(4));
    st32(base, (R(5) + 32), R(4));
    st32(base, (R(5) + 36), R(4));
    st32(base, (R(5) + 40), R(4));
    st32(base, (R(5) + 44), R(4));
    st32(base, (R(5) + 48), R(4));
    st32(base, (R(5) + 52), R(4));
    st32(base, (R(5) + 56), R(4));
    st32(base, (R(5) + 60), R(4));
    st32(base, (R(5) + 64), R(4));
    st32(base, (R(5) + 68), R(4));
    st32(base, (R(5) + 72), R(4));
    st32(base, (R(5) + 76), R(4));
    st32(base, (R(5) + 80), R(4));
    st32(base, (R(5) + 84), R(4));
    st32(base, (R(5) + 88), R(4));
    st32(base, (R(5) + 92), R(4));
    st32(base, (R(5) + 96), R(4));
    st32(base, (R(5) + 100), R(4));
    st32(base, (R(5) + 104), R(4));
    st32(base, (R(5) + 108), R(4));
    st32(base, (R(5) + 112), R(4));
    st32(base, (R(5) + 116), R(4));
    st32(base, (R(5) + 120), R(4));
    st32(base, (R(5) + 124), R(4));
    { uint32_t ea_ = R(5) + 128; st32(base, ea_, R(4)); R(5) = ea_; }
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80083728; }
    R(0) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(5) = (0 + 0);
    R(4) = R(3) + R(0);
    st32(base, (R(4) + 4), R(5));
    st16(base, (R(3) + 3080), R(5));
}

/* fn_800837D0 (fn_800837D0, 152 bytes) */
static void bg_m_837d0(GM_CTX) {
    GM_FN(0x800837D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(4) = R(3) + R(4);
    R(28) = R(3) |R(3);
    R(0) = ld16(base, (R(3) + 3080));
    R(3) = (0 + 512);
    st8(base, (R(4) + 1032), R(0));
    GM_CALLV(0x80083804u, 0x802B9250u, 0);
    R(30) = R(3) |R(3);
    R(29) = (0 + 0);
    R(31) = R(30) |R(30);
L_80083810:;
    R(3) = (0 + 10);
    GM_CALLV(0x80083818u, 0x80083490u, 0);
    R(29) = (R(29) + 1);
    st16(base, (R(31) + 0), R(3));
    cr_cmp_s(ctx, 0, (int32_t)R(29), 256);
    R(31) = (R(31) + 2);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80083810; }
    R(0) = ld16(base, (R(28) + 3080));
    R(0) = rotl32(R(0), 2) & 0xFFFFFFFCu;
    R(3) = R(28) + R(0);
    st32(base, (R(3) + 4), R(30));
    R(3) = ld16(base, (R(28) + 3080));
    R(0) = (R(3) + 1);
    st16(base, (R(28) + 3080), R(0));
    R(0) = lr;
}

/* fn_80083870 (fn_80083870, 608 bytes) */
static void bg_m_83870(GM_CTX) {
    GM_FN(0x80083870); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 96);
    R(0) = (0 + 0x43300000u);
    st32(base, (f + 56), R(0));
    R(27) = R(3) |R(3);
    st32(base, (f + 64), R(0));
    GM_CALLV(0x800838B0u, 0x80083BD0u, 0);
    R(3) = R(27) |R(27);
    GM_CALLV(0x800838B8u, 0x80083660u, 0);
    R(3) = R(27) |R(27);
    R(4) = (0 + 0);
    GM_CALLV(0x800838C4u, 0x800837D0u, 0);
    R(0) = ld32(base, (R(27) + 3104));
    R(3) = ld32(base, (R(13) + -22504));
    R(0) = ((int32_t)R(0) * 944);
    R(31) = R(3) + R(0);
    R(0) = ld32(base, (R(31) + 44));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_800838E4; }
    goto L_800838E8;
L_800838E4:;
    R(31) = (0 + 0);
L_800838E8:;
    { uint32_t ea_ = (R(2) + -29068); ctx->f[31].d = ctx->ps1[31] = ldfs(base, ea_); }
    R(30) = (0 + 0);
    { uint32_t ea_ = (R(2) + -29056); ctx->f[30].u = ld64(base, ea_); }
    { uint32_t ea_ = (R(2) + -29072); ctx->f[29].d = ctx->ps1[29] = ldfs(base, ea_); }
L_800838F8:;
    R(0) = rotl32(R(30), 26) & 0xFC000000u;
    R(4) = rotl32(R(30), 1) & 0x1u;
    R(3) = R(0) - R(4);
    R(28) = (0 + 0);
    { int32_t v_ = (int32_t)R(30); ctx->xer_ca = v_ < 0 && (v_ & 0x3Fu) != 0; R(0) = (v_ >> 6); }
    R(3) = rotl32(R(3), 6) & 0xFFFFFFFFu;
    R(3) = R(3) + R(4);
    { uint64_t t_ = (uint64_t)(R(0)) + (0) + ctx->xer_ca; R(0) = t_; ctx->xer_ca = (t_ >> 32); }
    R(3) = rotl32(R(3), 4) & 0xFFFFFFF0u;
    R(0) = rotl32(R(0), 4) & 0xFFFFFFF0u;
    R(3) = R(3) ^ 0x80000000u;
    st32(base, (f + 60), R(3));
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 68), R(0));
    { uint32_t ea_ = (f + 56); ctx->f[1].u = ld64(base, ea_); }
    { uint32_t ea_ = (f + 64); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d - ctx->f[30].d);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[30].d);
    { uint32_t ea_ = (f + 44); stfs(base, ea_, ctx->f[1].d); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[29].d + ctx->f[1].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[29].d + ctx->f[2].d);
    { uint32_t ea_ = (f + 48); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (f + 32); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (f + 36); stfs(base, ea_, ctx->f[0].d); }
    R(29) = ld32(base, (R(31) + 44));
    goto L_80083A5C;
L_80083960:;
    R(0) = ld16(base, (R(29) + 0));
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0xFu) != 0; R(0) = (v_ >> 4); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 60), R(0));
    { uint32_t ea_ = (f + 56); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[0].d - ctx->f[30].d);
    { uint32_t ea_ = (f + 20); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld16(base, (R(29) + 2));
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0xFu) != 0; R(0) = (v_ >> 4); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 68), R(0));
    { uint32_t ea_ = (f + 64); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[0].d - ctx->f[30].d);
    { uint32_t ea_ = (f + 24); stfs(base, ea_, ctx->f[2].d); }
    R(0) = ld16(base, (R(29) + 4));
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0xFu) != 0; R(0) = (v_ >> 4); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 60), R(0));
    { uint32_t ea_ = (f + 56); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[30].d);
    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[1].d); }
    R(0) = ld16(base, (R(29) + 6));
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 0xFu) != 0; R(0) = (v_ >> 4); }
    R(0) = R(0) ^ 0x80000000u;
    st32(base, (f + 68), R(0));
    { uint32_t ea_ = (f + 64); ctx->f[0].u = ld64(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d - ctx->f[30].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[2].d + ctx->f[0].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
    R(3) = ld16(base, (R(29) + 4));
    R(0) = rotl32(R(3), 28) & 0xF0000000u;
    R(3) = rotl32(R(3), 1) & 0x1u;
    R(0) = R(0) - R(3);
    R(0) = rotl32(R(0), 4) & 0xFFFFFFFFu;
    R(0) = R(0) + R(3);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_800839FC; }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[31].d);
    { uint32_t ea_ = (f + 8); stfs(base, ea_, ctx->f[0].d); }
L_800839FC:;
    R(3) = ld16(base, (R(29) + 6));
    R(0) = rotl32(R(3), 28) & 0xF0000000u;
    R(3) = rotl32(R(3), 1) & 0x1u;
    R(0) = R(0) - R(3);
    R(0) = rotl32(R(0), 4) & 0xFFFFFFFFu;
    R(0) = R(0) + R(3);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80083A24; }
    { uint32_t ea_ = (f + 12); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[31].d);
    { uint32_t ea_ = (f + 12); stfs(base, ea_, ctx->f[0].d); }
L_80083A24:;
    { uint32_t ea_ = (R(2) + -29064); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    R(3) = (f + 44);
    R(4) = (f + 32);
    R(5) = (f + 20);
    R(6) = (f + 8);
    GM_CALLV(0x80083A3Cu, 0x800B3100u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80083A54; }
    R(3) = R(27) |R(27);
    R(4) = R(30) |R(30);
    GM_CALLV(0x80083A50u, 0x800837D0u, 0);
    goto L_80083A68;
L_80083A54:;
    R(29) = (R(29) + 24);
    R(28) = (R(28) + 1);
L_80083A5C:;
    R(0) = ld32(base, (R(31) + 156));
    cr_cmp_u(ctx, 0, R(28), R(0));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80083960; }
L_80083A68:;
    R(30) = (R(30) + 1);
    cr_cmp_s(ctx, 0, (int32_t)R(30), 2048);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800838F8; }
    R(3) = (0 + 2);
    R(4) = (0 + 24);
    R(5) = (0 + 1);
    GM_CALLV(0x80083A84u, 0x80081BE0u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80083A98; }
    R(0) = (0 + 0);
    st8(base, (R(27) + 3112), R(0));
    goto L_80083AA0;
L_80083A98:;
    R(0) = (0 + 1);
    st8(base, (R(27) + 3112), R(0));
L_80083AA0:;
    R(11) = (f + 96);
    R(0) = lr;
}

/* fn_80083AD0 (fn_80083AD0, 84 bytes) */
static void bg_m_83ad0(GM_CTX) {
    GM_FN(0x80083AD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(0) = ld32(base, (R(3) + 3108));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_80083B00; }
    R(3) = R(0) |R(0);
    R(4) = (0 + 3);
    GM_CALLV(0x80083AFCu, 0x802B99C0u, 0);
    goto L_80083B04;
L_80083B00:;
    st32(base, (R(3) + 3108), R(4));
L_80083B04:;
    GM_CALLV(0x80083B08u, 0x8016E970u, 0);
    R(3) = ld32(base, (R(31) + 3108));
    GM_CALLV(0x80083B10u, 0x8016E4F0u, 0);
    R(0) = lr;
}

/* fn_80083B30 (fn_80083B30, 4 bytes) */
static void bg_m_83b30(GM_CTX) {
    GM_TAIL(0x8016E980u, 0); return;
}

/* fn_80083BD0 (fn_80083BD0, 296 bytes) */
static void bg_m_83bd0(GM_CTX) {
    GM_FN(0x80083BD0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 32);
    R(30) = ld32(base, (R(13) + -22672));
    R(0) = (0 + -1);
    R(31) = (0 + 0x80310000u);
    R(4) = ld32(base, (R(3) + 3104));
    st32(base, (R(3) + 3084), R(0));
    R(26) = R(3) |R(3);
    R(31) = (R(31) + -416);
    R(5) = (0 + 1);
    st32(base, (R(3) + 3088), R(0));
    st32(base, (R(3) + 3092), R(0));
    st32(base, (R(3) + 3096), R(0));
    R(3) = R(30) |R(30);
    GM_CALLV(0x80083C18u, 0x800813F0u, 0);
    R(28) = R(3) |R(3);
    R(29) = (R(31) + 664);
    R(27) = (0 + 0);
L_80083C24:;
    R(4) = ld32(base, (R(29) + 0));
    R(3) = R(28) |R(28);
    GM_CALLV(0x80083C30u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80083C40; }
    st32(base, (R(26) + 3088), R(27));
    goto L_80083C50;
L_80083C40:;
    R(27) = (R(27) + 1);
    R(29) = (R(29) + 4);
    cr_cmp_u(ctx, 0, R(27), 0x28u);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80083C24; }
L_80083C50:;
    R(4) = ld32(base, (R(26) + 3104));
    R(3) = R(30) |R(30);
    R(5) = (0 + 2);
    GM_CALLV(0x80083C60u, 0x800813F0u, 0);
    R(28) = R(3) |R(3);
    R(29) = (R(31) + 1064);
    R(27) = (0 + 0);
L_80083C6C:;
    R(4) = ld32(base, (R(29) + 0));
    R(3) = R(28) |R(28);
    GM_CALLV(0x80083C78u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80083C88; }
    st32(base, (R(26) + 3092), R(27));
    goto L_80083C98;
L_80083C88:;
    R(27) = (R(27) + 1);
    R(29) = (R(29) + 4);
    cr_cmp_u(ctx, 0, R(27), 0x10u);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80083C6C; }
L_80083C98:;
    R(4) = ld32(base, (R(26) + 3104));
    R(3) = R(30) |R(30);
    R(5) = (0 + 3);
    GM_CALLV(0x80083CA8u, 0x800813F0u, 0);
    R(29) = R(3) |R(3);
    R(30) = (R(31) + 1232);
    R(27) = (0 + 0);
L_80083CB4:;
    R(4) = ld32(base, (R(30) + 0));
    R(3) = R(29) |R(29);
    GM_CALLV(0x80083CC0u, 0x802E1AB4u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80083CD0; }
    st32(base, (R(26) + 3096), R(27));
    goto L_80083CE0;
L_80083CD0:;
    R(27) = (R(27) + 1);
    R(30) = (R(30) + 4);
    cr_cmp_u(ctx, 0, R(27), 0x6u);
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80083CB4; }
L_80083CE0:;
    R(11) = (f + 32);
    R(0) = lr;
}

/* fn_80083D00 (fn_80083D00, 284 bytes) */
static void bg_m_83d00(GM_CTX) {
    GM_FN(0x80083D00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 3152);
    R(0) = ld32(base, (R(3) + 3104));
    R(29) = R(3) |R(3);
    st16(base, (f + 3112), R(0));
    R(30) = R(4) |R(4);
    R(31) = (0 + 0);
    goto L_80083DF4;
L_80083D2C:;
    R(0) = rotl32(R(31), 1) & 0x1FFFEu;
    R(3) = ld16(base, (R(30) + R(0)));
    R(4) = R(30) + R(0);
    st16(base, (f + 3100), R(3));
    cr_cmp_u(ctx, 0, R(3), 0x7FFFu);
    R(28) = rotl32(R(3), 1) & 0xFFFEu;
    R(0) = ld16(base, (R(4) + 2));
    st16(base, (f + 3102), R(0));
    R(0) = ld16(base, (R(4) + 4));
    st16(base, (f + 3104), R(0));
    R(0) = ld16(base, (R(4) + 6));
    st16(base, (f + 3106), R(0));
    R(0) = ld16(base, (R(4) + 8));
    st16(base, (f + 3108), R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80083DF0; }
    R(27) = rotl32(R(3), 20) & 0xFu;
    R(28) = R(28) & 0x1FFFu;
    R(3) = ld32(base, (R(13) + -22672));
    R(5) = R(27) |R(27);
    R(4) = ld32(base, (R(29) + 3104));
    R(6) = R(28) |R(28);
    GM_CALLV(0x80083D84u, 0x80081870u, 0);
    st16(base, (f + 3098), R(3));
    R(0) = (R(28) + 1);
    R(3) = ld32(base, (R(13) + -22672));
    R(5) = R(27) |R(27);
    R(4) = ld32(base, (R(29) + 3104));
    R(6) = R(0) & 0xFFFFu;
    GM_CALLV(0x80083DA0u, 0x80081870u, 0);
    R(28) = R(3) |R(3);
    R(3) = ld32(base, (R(13) + -22672));
    R(4) = ld32(base, (R(29) + 3104));
    R(5) = R(27) |R(27);
    R(6) = ld16(base, (f + 3098));
    GM_CALLV(0x80083DB8u, 0x80081890u, 0);
    R(0) = rotl32(R(28), 24) & 0xFFu;
    st32(base, (f + 3080), R(3));
    st8(base, (f + 3084), R(28));
    st8(base, (f + 3085), R(0));
    R(0) = ld8(base, (R(3) + 0));
    R(0) = R(0) & 0x80u;
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80083DE4; }
    R(3) = R(29) |R(29);
    R(4) = (f + 8);
    GM_CALLV(0x80083DE0u, 0x800859F0u, 0);
    goto L_80083DF0;
L_80083DE4:;
    R(3) = R(29) |R(29);
    R(4) = (f + 8);
    GM_CALLV(0x80083DF0u, 0x80085780u, 0);
L_80083DF0:;
    R(31) = (R(31) + 5);
L_80083DF4:;
    R(0) = rotl32(R(31), 1) & 0x1FFFEu;
    R(0) = ld16(base, (R(30) + R(0)));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((!CR_BIT(ctx, 2))) { GM_LOOP(); goto L_80083D2C; }
    R(11) = (f + 3152);
    R(0) = lr;
}

/* fn_80083E20 (fn_80083E20, 152 bytes) */
static void bg_m_83e20(GM_CTX) {
    GM_FN(0x80083E20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(30) = R(4) |R(4);
    R(5) = ld16(base, (R(4) + 3084));
    cr_cmp_u(ctx, 0, R(5), 0x400u);
    if ((!CR_BIT(ctx, 0))) { goto L_80083E50; }
    R(0) = ld16(base, (R(4) + 3086));
    cr_cmp_u(ctx, 0, R(0), 0x200u);
    if ((CR_BIT(ctx, 0))) { goto L_80083E60; }
L_80083E50:;
    R(3) = (0 + 0x10000u);
    R(0) = (R(3) + -1);
    st16(base, (R(4) + 3082), R(0));
    goto L_80083EA0;
L_80083E60:;
    R(4) = rotl32(R(0), 2) & 0xFFC0u;
    R(0) = rotl32(R(5), 28) & 0xFFFu;
    R(4) = R(4) + R(0);
    R(4) = R(4) & 0xFFFFu;
    R(31) = R(3) + R(4);
    R(0) = ld8(base, (R(31) + 1032));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80083E84; }
    GM_CALLV(0x80083E84u, 0x800837D0u, 0);
L_80083E84:;
    R(4) = ld8(base, (R(31) + 1032));
    R(0) = ld16(base, (R(30) + 3084));
    R(3) = ld16(base, (R(30) + 3086));
    R(0) = R(0) & 0xFu;
    st16(base, (R(30) + 3082), R(4));
    R(0) = (rotl32(R(3), 4) & 0xF0u) | (R(0) & ~0xF0u);
    st16(base, (R(30) + 3102), R(0));
L_80083EA0:;
    R(0) = lr;
}

/* fn_80083EC0 (fn_80083EC0, 32 bytes) */
static void bg_m_83ec0(GM_CTX) {
    R(3) = ld32(base, (R(4) + 3072));
    R(6) = ld8(base, (R(3) + R(5)));
    R(3) = R(5) + R(3);
    st16(base, (R(4) + 3088), R(6));
    R(0) = ld8(base, (R(3) + 1));
    R(6) = (rotl32(R(0), 8) & 0xFF00u) | (R(6) & ~0xFF00u);
    st16(base, (R(4) + 3088), R(6));
}

/* fn_80083EE0 (fn_80083EE0, 164 bytes) */
static void bg_m_83ee0(GM_CTX) {
    GM_FN(0x80083EE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(8) = R(3) |R(3);
    R(31) = R(5) |R(5);
    R(30) = R(4) |R(4);
    R(6) = ld16(base, (R(4) + 3086));
    R(0) = ld16(base, (R(4) + 3084));
    R(7) = rotl32(R(6), 6) & 0x3C00u;
    R(3) = R(6) & 0xFu;
    R(7) = R(7) + R(3);
    R(0) = R(0) & 0x1F0u;
    R(7) = R(7) + R(0);
    R(3) = ld32(base, (R(13) + -22656));
    R(4) = ld16(base, (R(4) + 3104));
    R(5) = R(7) & 0xFFFFu;
    R(6) = ld32(base, (R(8) + 3100));
    GM_CALLV(0x80083F30u, 0x80082120u, 0);
    R(0) = ld16(base, (R(30) + 3084));
    R(4) = (0 + 0x802F0000u);
    R(4) = (R(4) + -1640);
    R(3) = R(3) & 0xFFFFu;
    R(0) = rotl32(R(0), 1) & 0x1Eu;
    R(0) = ld16(base, (R(4) + R(0)));
    R(0) = R(3) &R(0);
    CR0(ctx, R(0));
    if ((CR_BIT(ctx, 2))) { goto L_80083F6C; }
    R(3) = R(31) |R(31);
    GM_CALLV(0x80083F58u, 0x800818E0u, 0);
    R(4) = (0 + 0x802F0000u);
    R(0) = rotl32(R(3), 1) & 0x1FFFEu;
    R(4) = (R(4) + -1608);
    R(0) = ld16(base, (R(4) + R(0)));
    st16(base, (R(30) + 3088), R(0));
L_80083F6C:;
    R(0) = lr;
}

/* fn_80083FC0 (fn_80083FC0, 1732 bytes) */
static void bg_m_83fc0(GM_CTX) {
    GM_FN(0x80083FC0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(11) = (f + 64);
    R(22) = ld32(base, (R(5) + 0));
    R(28) = R(5) |R(5);
    R(7) = ld32(base, (R(4) + 3072));
    R(26) = R(3) |R(3);
    R(27) = R(4) |R(4);
    R(29) = R(6) |R(6);
    R(5) = R(7) + R(22);
    R(21) = R(22) |R(22);
    R(3) = R(5) |R(5);
L_80083FF8:;
    R(0) = ld8(base, (R(5) + 0));
    R(0) = R(0) & 0x1u;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_80084024; }
    R(0) = ld8(base, (R(3) + 0));
    cr_cmp_u(ctx, 0, R(0), 0xFEu);
    if ((CR_BIT(ctx, 2))) { goto L_80084024; }
    R(5) = (R(5) + 3);
    R(21) = (R(21) + 3);
    R(3) = (R(3) + 3);
    GM_LOOP(); goto L_80083FF8;
L_80084024:;
    R(5) = R(7) + R(21);
    R(20) = R(21) |R(21);
    R(3) = R(5) |R(5);
L_80084030:;
    R(0) = ld8(base, (R(5) + 0));
    R(0) = R(0) & 0x1u;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((!CR_BIT(ctx, 2))) { goto L_8008405C; }
    R(0) = ld8(base, (R(3) + 0));
    cr_cmp_u(ctx, 0, R(0), 0xFEu);
    if ((CR_BIT(ctx, 2))) { goto L_8008405C; }
    R(5) = (R(5) + 3);
    R(20) = (R(20) + 3);
    R(3) = (R(3) + 3);
    GM_LOOP(); goto L_80084030;
L_8008405C:;
    R(31) = R(20) |R(20);
    R(3) = R(7) + R(20);
    R(0) = R(0) | 0x0u;
L_80084068:;
    R(0) = ld8(base, (R(3) + 0));
    cr_cmp_u(ctx, 0, R(0), 0xFEu);
    if ((CR_BIT(ctx, 2))) { goto L_80084080; }
    R(3) = (R(3) + 1);
    R(31) = (R(31) + 1);
    GM_LOOP(); goto L_80084068;
L_80084080:;
    cr_cmp_s(ctx, 0, (int32_t)R(21), (int32_t)R(20));
    R(30) = ld16(base, (R(4) + 3084));
    if ((!CR_BIT(ctx, 2))) { goto L_800844E8; }
    cr_cmp_s(ctx, 0, (int32_t)R(21), (int32_t)R(31));
    if ((!CR_BIT(ctx, 2))) { goto L_800844E8; }
    cr_cmp_s(ctx, 0, (int32_t)R(6), 0);
    if ((!CR_BIT(ctx, 0))) { goto L_800842C8; }
    R(29) = -(int32_t)R(6);
    R(24) = (R(21) + -3);
    R(0) = (R(29) + -1);
    R(23) = (0 + 0);
    R(0) = R(0) & 0xFFFFu;
    R(0) = R(30) + R(0);
    st16(base, (R(4) + 3084), R(0));
    goto L_8008411C;
L_800840BC:;
    R(3) = ld32(base, (R(27) + 3072));
    R(0) = ld8(base, (R(3) + R(24)));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_80084124; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(24) + 1);
    GM_CALLV(0x800840DCu, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800840E8u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_80084100; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084100u, 0x80086B20u, 0);
L_80084100:;
    R(3) = ld16(base, (R(27) + 3084));
    R(24) = (R(24) + -3);
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(22));
    R(0) = (R(3) + -1);
    st16(base, (R(27) + 3084), R(0));
    if ((CR_BIT(ctx, 0))) { goto L_80084124; }
    R(23) = (R(23) + 1);
L_8008411C:;
    cr_cmp_s(ctx, 0, (int32_t)R(23), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800840BC; }
L_80084124:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(22));
    if ((CR_BIT(ctx, 0))) { goto L_800842B4; }
    R(3) = (R(24) + 3);
    R(0) = (0 + 3);
    R(3) = R(3) - R(22);
    R(21) = R(24) |R(24);
    R(3) = divwu(R(3), R(0));
    ctx->ctr = R(3);
    if ((CR_BIT(ctx, 0))) { goto L_80084160; }
L_80084148:;
    R(3) = ld32(base, (R(27) + 3072));
    R(0) = ld8(base, (R(3) + R(21)));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_80084160; }
    R(21) = (R(21) + -3);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80084148; }
L_80084160:;
    cr_cmp_s(ctx, 0, (int32_t)R(21), (int32_t)R(22));
    if ((CR_BIT(ctx, 0))) { goto L_80084250; }
    R(3) = ld32(base, (R(27) + 3072));
    R(0) = ld8(base, (R(3) + R(21)));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_80084250; }
    R(3) = (0 + 0x55550000u);
    R(25) = R(24) |R(24);
    R(0) = (R(3) + 21846);
    R(3) = (((int64_t)(int32_t)R(0) * (int32_t)R(21)) >> 32);
    R(0) = rotl32(R(3), 1) & 0x1u;
    R(3) = R(3) + R(0);
    R(0) = (R(3) + 1);
    R(19) = R(29) - R(0);
    goto L_800841F0;
L_8008419C:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(25) + 1);
    GM_CALLV(0x800841ACu, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800841B8u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_800841D0; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800841D0u, 0x80086B20u, 0);
L_800841D0:;
    R(3) = ld16(base, (R(27) + 3084));
    R(25) = (R(25) + -3);
    cr_cmp_s(ctx, 0, (int32_t)R(25), (int32_t)R(21));
    R(0) = (R(3) + -1);
    st16(base, (R(27) + 3084), R(0));
    if ((CR_BIT(ctx, 1))) { goto L_800841EC; }
    R(25) = R(24) |R(24);
L_800841EC:;
    R(23) = (R(23) + 1);
L_800841F0:;
    cr_cmp_s(ctx, 0, (int32_t)R(23), (int32_t)R(19));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8008419C; }
    goto L_80084244;
L_800841FC:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(21) + 1);
    GM_CALLV(0x8008420Cu, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084218u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_80084230; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084230u, 0x80086B20u, 0);
L_80084230:;
    R(3) = ld16(base, (R(27) + 3084));
    R(21) = (R(21) + -3);
    R(23) = (R(23) + 1);
    R(0) = (R(3) + -1);
    st16(base, (R(27) + 3084), R(0));
L_80084244:;
    cr_cmp_s(ctx, 0, (int32_t)R(23), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800841FC; }
    goto L_800842B4;
L_80084250:;
    R(19) = R(24) |R(24);
    goto L_800842AC;
L_80084258:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(19) + 1);
    GM_CALLV(0x80084268u, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084274u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_8008428C; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x8008428Cu, 0x80086B20u, 0);
L_8008428C:;
    R(3) = ld16(base, (R(27) + 3084));
    R(19) = (R(19) + -3);
    cr_cmp_s(ctx, 0, (int32_t)R(19), (int32_t)R(22));
    R(0) = (R(3) + -1);
    st16(base, (R(27) + 3084), R(0));
    if ((!CR_BIT(ctx, 0))) { goto L_800842A8; }
    R(19) = R(24) |R(24);
L_800842A8:;
    R(23) = (R(23) + 1);
L_800842AC:;
    cr_cmp_s(ctx, 0, (int32_t)R(23), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80084258; }
L_800842B4:;
    R(3) = ld16(base, (R(27) + 3086));
    st16(base, (R(27) + 3084), R(30));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3086), R(0));
    goto L_80084668;
L_800842C8:;
    R(24) = (0 + 0);
    goto L_80084330;
L_800842D0:;
    R(3) = ld32(base, (R(27) + 3072));
    R(0) = ld8(base, (R(3) + R(22)));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_80084338; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(22) + 1);
    GM_CALLV(0x800842F0u, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800842FCu, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_80084314; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084314u, 0x80086B20u, 0);
L_80084314:;
    R(3) = ld16(base, (R(27) + 3084));
    R(22) = (R(22) + 3);
    cr_cmp_s(ctx, 0, (int32_t)R(22), (int32_t)R(21));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3084), R(0));
    if ((!CR_BIT(ctx, 0))) { goto L_80084338; }
    R(24) = (R(24) + 1);
L_80084330:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800842D0; }
L_80084338:;
    cr_cmp_s(ctx, 0, (int32_t)R(22), (int32_t)R(21));
    if ((!CR_BIT(ctx, 0))) { goto L_80084668; }
    R(3) = (R(21) + 2);
    R(0) = (0 + 3);
    R(3) = R(3) - R(22);
    R(23) = R(22) |R(22);
    R(3) = divwu(R(3), R(0));
    ctx->ctr = R(3);
    if ((!CR_BIT(ctx, 0))) { goto L_80084378; }
    R(0) = R(0) | 0x0u;
L_80084360:;
    R(3) = ld32(base, (R(27) + 3072));
    R(0) = ld8(base, (R(3) + R(23)));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((CR_BIT(ctx, 2))) { goto L_80084378; }
    R(23) = (R(23) + 3);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80084360; }
L_80084378:;
    R(3) = ld32(base, (R(27) + 3072));
    R(0) = ld8(base, (R(3) + R(23)));
    cr_cmp_u(ctx, 0, R(0), 0x4u);
    if ((!CR_BIT(ctx, 2))) { goto L_80084470; }
    R(3) = (0 + 0x55550000u);
    R(0) = R(21) - R(23);
    R(3) = (R(3) + 21846);
    R(25) = R(22) |R(22);
    R(3) = (((int64_t)(int32_t)R(3) * (int32_t)R(0)) >> 32);
    R(0) = rotl32(R(3), 1) & 0x1u;
    R(0) = R(3) + R(0);
    R(19) = R(29) - R(0);
    goto L_80084400;
L_800843AC:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(25) + 1);
    GM_CALLV(0x800843BCu, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800843C8u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_800843E0; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800843E0u, 0x80086B20u, 0);
L_800843E0:;
    R(3) = ld16(base, (R(27) + 3084));
    R(25) = (R(25) + 3);
    cr_cmp_s(ctx, 0, (int32_t)R(25), (int32_t)R(23));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3084), R(0));
    if ((CR_BIT(ctx, 0))) { goto L_800843FC; }
    R(25) = R(22) |R(22);
L_800843FC:;
    R(24) = (R(24) + 1);
L_80084400:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(19));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800843AC; }
    goto L_80084454;
L_8008440C:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(23) + 1);
    GM_CALLV(0x8008441Cu, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084428u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_80084440; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084440u, 0x80086B20u, 0);
L_80084440:;
    R(3) = ld16(base, (R(27) + 3084));
    R(23) = (R(23) + 3);
    R(24) = (R(24) + 1);
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3084), R(0));
L_80084454:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_8008440C; }
    R(3) = ld16(base, (R(27) + 3086));
    st16(base, (R(27) + 3084), R(30));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3086), R(0));
    goto L_80084668;
L_80084470:;
    R(19) = R(22) |R(22);
    goto L_800844CC;
L_80084478:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(19) + 1);
    GM_CALLV(0x80084488u, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084494u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_800844AC; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800844ACu, 0x80086B20u, 0);
L_800844AC:;
    R(3) = ld16(base, (R(27) + 3084));
    R(19) = (R(19) + 3);
    cr_cmp_s(ctx, 0, (int32_t)R(19), (int32_t)R(21));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3084), R(0));
    if ((CR_BIT(ctx, 0))) { goto L_800844C8; }
    R(19) = R(22) |R(22);
L_800844C8:;
    R(24) = (R(24) + 1);
L_800844CC:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80084478; }
    R(3) = ld16(base, (R(27) + 3086));
    st16(base, (R(27) + 3084), R(30));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3086), R(0));
    goto L_80084668;
L_800844E8:;
    R(3) = (0 + 0x55550000u);
    { int32_t v_ = (int32_t)R(6); ctx->xer_ca = v_ < 0 && (v_ & 0x7FFFFFFFu) != 0; R(5) = (v_ >> 31); }
    R(0) = R(31) - R(20);
    R(23) = R(22) |R(22);
    R(3) = (R(3) + 21846);
    R(4) = R(5) ^R(6);
    R(3) = (((int64_t)(int32_t)R(3) * (int32_t)R(0)) >> 32);
    R(25) = R(22) |R(22);
    R(29) = R(4) - R(5);
    R(24) = (0 + 0);
    R(0) = rotl32(R(3), 1) & 0x1u;
    R(0) = R(3) + R(0);
    R(19) = R(29) - R(0);
    goto L_80084580;
L_80084520:;
    cr_cmp_s(ctx, 0, (int32_t)R(25), (int32_t)R(21));
    if ((!CR_BIT(ctx, 0))) { goto L_80084588; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(23) + 1);
    GM_CALLV(0x80084538u, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084544u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_8008455C; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x8008455Cu, 0x80086B20u, 0);
L_8008455C:;
    R(3) = ld16(base, (R(27) + 3084));
    R(23) = (R(23) + 3);
    cr_cmp_s(ctx, 0, (int32_t)R(23), (int32_t)R(21));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3084), R(0));
    if ((CR_BIT(ctx, 0))) { goto L_80084578; }
    R(23) = R(22) |R(22);
L_80084578:;
    R(25) = (R(25) + 3);
    R(24) = (R(24) + 1);
L_80084580:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80084520; }
L_80084588:;
    R(22) = R(21) |R(21);
    goto L_800845EC;
L_80084590:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(19));
    if ((!CR_BIT(ctx, 0))) { goto L_800845F4; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(22) + 1);
    GM_CALLV(0x800845A8u, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800845B4u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_800845CC; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x800845CCu, 0x80086B20u, 0);
L_800845CC:;
    R(3) = ld16(base, (R(27) + 3084));
    R(22) = (R(22) + 3);
    cr_cmp_s(ctx, 0, (int32_t)R(22), (int32_t)R(20));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3084), R(0));
    if ((CR_BIT(ctx, 0))) { goto L_800845E8; }
    R(22) = R(21) |R(21);
L_800845E8:;
    R(24) = (R(24) + 1);
L_800845EC:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_80084590; }
L_800845F4:;
    R(19) = R(20) |R(20);
    goto L_80084650;
L_800845FC:;
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    R(5) = (R(19) + 1);
    GM_CALLV(0x8008460Cu, 0x80083EC0u, 0);
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084618u, 0x80083E20u, 0);
    R(0) = ld16(base, (R(27) + 3082));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((CR_BIT(ctx, 2))) { goto L_80084630; }
    R(3) = R(26) |R(26);
    R(4) = R(27) |R(27);
    GM_CALLV(0x80084630u, 0x80086B20u, 0);
L_80084630:;
    R(3) = ld16(base, (R(27) + 3084));
    R(19) = (R(19) + 3);
    cr_cmp_s(ctx, 0, (int32_t)R(19), (int32_t)R(31));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3084), R(0));
    if ((CR_BIT(ctx, 0))) { goto L_8008464C; }
    R(19) = R(20) |R(20);
L_8008464C:;
    R(24) = (R(24) + 1);
L_80084650:;
    cr_cmp_s(ctx, 0, (int32_t)R(24), (int32_t)R(29));
    if ((CR_BIT(ctx, 0))) { GM_LOOP(); goto L_800845FC; }
    R(3) = ld16(base, (R(27) + 3086));
    st16(base, (R(27) + 3084), R(30));
    R(0) = (R(3) + 1);
    st16(base, (R(27) + 3086), R(0));
L_80084668:;
    st32(base, (R(28) + 0), R(31));
    R(11) = (f + 64);
    R(0) = lr;
}


/* fn_8007E7F0 (fn_8007E7F0, 108 bytes) */
static void bg_m_7e7f0(GM_CTX) {
    GM_FN(0x8007E7F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(10) = (0 + 0);
    R(8) = (0 + 0);
    R(0) = ld32(base, (R(3) + 60));
    ctx->ctr = R(0);
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 1))) { goto L_8007E848; }
    R(0) = R(0) | 0x0u;
L_8007E818:;
    R(9) = ld32(base, (R(3) + 56));
    R(0) = ld16(base, (R(9) + R(8)));
    cr_cmp_u(ctx, 0, R(0), 0xFFFFu);
    if ((!CR_BIT(ctx, 2))) { goto L_8007E83C; }
    R(0) = ((int32_t)R(10) * 12);
    R(3) = R(9) + R(0);
    GM_CALLV(0x8007E834u, 0x8007EA60u, 0);
    R(3) = (0 + 1);
    goto L_8007E84C;
L_8007E83C:;
    R(8) = (R(8) + 12);
    R(10) = (R(10) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_8007E818; }
L_8007E848:;
    R(3) = (0 + 0);
L_8007E84C:;
    R(0) = lr;
}

/* fn_8007EA30 (fn_8007EA30, 32 bytes) */
static void bg_m_7ea30(GM_CTX) {
    R(4) = (0 + 0x10000u);
    R(0) = (0 + 0);
    R(4) = (R(4) + -1);
    st16(base, (R(3) + 0), R(4));
    st16(base, (R(3) + 2), R(0));
    st16(base, (R(3) + 4), R(0));
    st32(base, (R(3) + 8), R(0));
}

/* fn_8007EA50 (fn_8007EA50, 4 bytes) */
static void bg_m_7ea50(GM_CTX) {
    GM_TAIL(0x8007EA30u, 0); return;
}

/* fn_8007EA60 (fn_8007EA60, 20 bytes) */
static void bg_m_7ea60(GM_CTX) {
    st16(base, (R(3) + 0), R(4));
    st16(base, (R(3) + 2), R(5));
    st16(base, (R(3) + 4), R(6));
    st8(base, (R(3) + 6), R(7));
}

/* fn_8007EA80 (fn_8007EA80, 240 bytes) */
static void bg_m_7ea80(GM_CTX) {
    GM_FN(0x8007EA80); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(5) |R(5);
    R(30) = R(3) |R(3);
    R(0) = ld8(base, (R(3) + 6));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007EABC; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 1);
    if ((CR_BIT(ctx, 2))) { goto L_8007EAD4; }
    cr_cmp_s(ctx, 0, (int32_t)R(0), 2);
    if ((CR_BIT(ctx, 2))) { goto L_8007EAF4; }
    goto L_8007EB08;
L_8007EABC:;
    R(4) = R(30) |R(30);
    R(3) = (f + 32);
    GM_CALLV(0x8007EAC8u, 0x8007EBC0u, 0);
    { uint32_t ea_ = (f + 40); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 8); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007EB08;
L_8007EAD4:;
    R(4) = R(30) |R(30);
    R(3) = (f + 20);
    GM_CALLV(0x8007EAE0u, 0x8007EBC0u, 0);
    { uint32_t ea_ = (R(2) + -29208); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (f + 28); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    { uint32_t ea_ = (R(31) + 8); stfs(base, ea_, ctx->f[0].d); }
    goto L_8007EB08;
L_8007EAF4:;
    R(4) = R(30) |R(30);
    R(3) = (f + 8);
    GM_CALLV(0x8007EB00u, 0x8007EBC0u, 0);
    { uint32_t ea_ = (f + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(31) + 8); stfs(base, ea_, ctx->f[0].d); }
L_8007EB08:;
    R(0) = ld16(base, (R(30) + 0));
    R(5) = R(31) |R(31);
    R(4) = ld32(base, (R(13) + -22692));
    R(6) = (0 + 0);
    R(3) = rotl32(R(0), 5) & 0xFFFFFFE0u;
    R(0) = ld8(base, (R(30) + 6));
    R(3) = R(4) + R(3);
    R(4) = ld32(base, (R(3) + 28));
    R(0) = rotl32(R(0), 8) & 0xFFFFFF00u;
    R(3) = ld16(base, (R(3) + 4));
    R(4) = R(4) |R(0);
    GM_CALLV(0x8007EB38u, 0x8006CA80u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007EB4C; }
    R(0) = ld32(base, (R(3) + 0));
    st32(base, (R(30) + 8), R(0));
    goto L_8007EB54;
L_8007EB4C:;
    R(0) = (0 + 0);
    st32(base, (R(30) + 8), R(0));
L_8007EB54:;
    R(3) = ld32(base, (R(30) + 8));
    R(0) = lr;
}

/* fn_8007EB70 (fn_8007EB70, 68 bytes) */
static void bg_m_7eb70(GM_CTX) {
    GM_FN(0x8007EB70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;
    R(0) = ctx->lr;
    R(31) = R(3) |R(3);
    R(3) = ld32(base, (R(3) + 8));
    GM_CALLV(0x8007EB8Cu, 0x80162D00u, 0);
    cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
    if ((CR_BIT(ctx, 2))) { goto L_8007EB98; }
    GM_CALLV(0x8007EB98u, 0x80162510u, 0);
L_8007EB98:;
    R(0) = (0 + 0);
    st32(base, (R(31) + 8), R(0));
    R(0) = lr;
}

/* fn_8007EBC0 (fn_8007EBC0, 44 bytes) */
static void bg_m_7ebc0(GM_CTX) {
    R(0) = ld16(base, (R(4) + 0));
    R(4) = ld32(base, (R(13) + -22692));
    R(0) = rotl32(R(0), 5) & 0xFFFFFFE0u;
    R(4) = R(4) + R(0);
    { uint32_t ea_ = (R(4) + 16); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 12); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 8); ctx->f[2].d = ctx->ps1[2] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[2].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 8); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_8007EBF0 (fn_8007EBF0, 36 bytes) */
static void bg_m_7ebf0(GM_CTX) {
    R(0) = ld16(base, (R(4) + 0));
    R(4) = ld32(base, (R(13) + -22692));
    R(0) = rotl32(R(0), 5) & 0xFFFFFFE0u;
    R(4) = R(4) + R(0);
    { uint32_t ea_ = (R(4) + 24); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(4) + 20); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(3) + 0); stfs(base, ea_, ctx->f[1].d); }
    { uint32_t ea_ = (R(3) + 4); stfs(base, ea_, ctx->f[0].d); }
}

/* fn_800803F0 (fn_800803F0, 156 bytes) */
static void bg_m_803f0(GM_CTX) {
    R(0) = ld32(base, (R(3) + 24));
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_80080404; }
    R(3) = (0 + 1);
    return;
L_80080404:;
    R(0) = ld32(base, (R(3) + 28));
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_80080418; }
    R(3) = (0 + 1);
    return;
L_80080418:;
    R(0) = ld32(base, (R(3) + 32));
    R(5) = (R(3) + 8);
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_80080430; }
    R(3) = (0 + 1);
    return;
L_80080430:;
    R(0) = ld32(base, (R(5) + 28));
    cr_cmp_u(ctx, 0, R(0), R(4));
    if ((!CR_BIT(ctx, 2))) { goto L_80080444; }
    R(3) = (0 + 1);
    return;
L_80080444:;
    R(0) = (0 + 4);
    R(5) = R(3) |R(3);
    R(6) = (0 + 0);
    ctx->ctr = R(0);
    R(0) = R(0) | 0x0u;
L_80080458:;
    R(0) = ld32(base, (R(5) + 24));
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80080478; }
    R(0) = rotl32(R(6), 2) & 0xFFFFFFFCu;
    R(5) = R(3) + R(0);
    R(3) = (0 + 1);
    st32(base, (R(5) + 24), R(4));
    return;
L_80080478:;
    R(5) = (R(5) + 4);
    R(6) = (R(6) + 1);
    ctx->ctr--;
    if ((ctx->ctr != 0)) { GM_LOOP(); goto L_80080458; }
    R(3) = (0 + 0);
}

/* fn_80080DC0 (fn_80080DC0, 24 bytes) */
static void bg_m_80dc0(GM_CTX) {
    { uint32_t ea_ = (R(3) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    R(3) = ctx->cr;
    R(3) = rotl32(R(3), 2) & 0x1u;
}

/* fn_80080DE0 (fn_80080DE0, 24 bytes) */
static void bg_m_80de0(GM_CTX) {
    { uint32_t ea_ = (R(3) + 236); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    R(3) = ctx->cr;
    R(3) = rotl32(R(3), 1) & 0x1u;
}

/* fn_80080E00 (fn_80080E00, 64 bytes) */
static void bg_m_80e00(GM_CTX) {
    cr_cmp_s(ctx, 0, (int32_t)R(5), 0);
    if ((!CR_BIT(ctx, 2))) { goto L_80080E20; }
    { uint32_t ea_ = (R(3) + 232); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 1))) { goto L_80080E38; }
    R(3) = (0 + 1);
    return;
L_80080E20:;
    { uint32_t ea_ = (R(3) + 232); ctx->f[1].d = ctx->ps1[1] = ldfs(base, ea_); }
    { uint32_t ea_ = (R(2) + -29176); ctx->f[0].d = ctx->ps1[0] = ldfs(base, ea_); }
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if ((!CR_BIT(ctx, 0))) { goto L_80080E38; }
    R(3) = (0 + 1);
    return;
L_80080E38:;
    R(3) = (0 + 0);
}

/* fn_800818E0 (fn_800818E0, 20 bytes) */
static void bg_m_818e0(GM_CTX) {
    R(4) = (0 + 0x802F0000u);
    R(0) = rotl32(R(3), 1) & 0x1FFFEu;
    R(4) = (R(4) + -1740);
    R(3) = ld16(base, (R(4) + R(0)));
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_BG_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_BG_COUNT)
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_80076BB0, 4) { bg_m_76bb0(GM_PASS); }
E(fn_80076BC0, 4) { bg_m_76bc0(GM_PASS); }
E(fn_80076BF0, 4) { bg_m_76bf0(GM_PASS); }
E(fn_80076FD0, 4) { bg_m_76fd0(GM_PASS); }
E(fn_80077020, 4) { bg_m_77020(GM_PASS); }
E(fn_80077060, 4) { bg_m_77060(GM_PASS); }
E(fn_80077390, 4) { bg_m_77390(GM_PASS); }
E(fn_800773A0, 4) { bg_m_773a0(GM_PASS); }
E(fn_800773E0, 4) { bg_m_773e0(GM_PASS); }
E(fn_80077490, 4) { bg_m_77490(GM_PASS); }
E(fn_800775A0, 4) { bg_m_775a0(GM_PASS); }
E(fn_80077610, 4) { bg_m_77610(GM_PASS); }
E(fn_80077730, 4) { bg_m_77730(GM_PASS); }
E(CoinGetBitSet__5dBg_cFUsUsi, 4) { bg_CoinGetBitSet__5dBg_cFUsUsi_777b0(GM_PASS); }
E(CoinGetBitCheck__5dBg_cFUsUsi, 4) { bg_CoinGetBitCheck__5dBg_cFUsUsi_77810(GM_PASS); }
E(placeTile__8BgGmBaseFUsUsii, 4) { bg_placeTile__8BgGmBaseFUsUsii_77860(GM_PASS); }
E(fn_80077980, 4) { bg_m_77980(GM_PASS); }
E(fn_80077A00, 4) { bg_m_77a00(GM_PASS); }
E(fn_80077B00, 4) { bg_m_77b00(GM_PASS); }
E(fn_80077B40, 4) { bg_m_77b40(GM_PASS); }
E(fn_80077D80, 4) { bg_m_77d80(GM_PASS); }
E(fn_80077E30, 4) { bg_m_77e30(GM_PASS); }
E(fn_80077EB0, 4) { bg_m_77eb0(GM_PASS); }
E(fn_80078300, 4) { bg_m_78300(GM_PASS); }
E(setWaterInWave__5dBg_cFffUc, 4) { bg_setWaterInWave__5dBg_cFffUc_78410(GM_PASS); }
E(fn_800784D0, 4) { bg_m_784d0(GM_PASS); }
E(getTileRendererList__7dBgGm_cFi, 4) { bg_getTileRendererList__7dBgGm_cFi_78520(GM_PASS); }
E(fn_80078780, 4) { bg_m_78780(GM_PASS); }
E(fn_80078800, 4) { bg_m_78800(GM_PASS); }
E(fn_80078860, 4) { bg_m_78860(GM_PASS); }
E(fn_800789A0, 4) { bg_m_789a0(GM_PASS); }
E(getLeftLimit__5dBg_cFv, 4) { bg_getLeftLimit__5dBg_cFv_78a70(GM_PASS); }
E(fn_80078B40, 4) { bg_m_78b40(GM_PASS); }
E(getRightLimit__5dBg_cFv, 4) { bg_getRightLimit__5dBg_cFv_78c10(GM_PASS); }
E(fn_80078CE0, 4) { bg_m_78ce0(GM_PASS); }
E(fn_80078CF0, 4) { bg_m_78cf0(GM_PASS); }
E(fn_80078D00, 4) { bg_m_78d00(GM_PASS); }
E(fn_80078EB0, 4) { bg_m_78eb0(GM_PASS); }
E(fn_80079020, 4) { bg_m_79020(GM_PASS); }
E(fn_800791D0, 4) { bg_m_791d0(GM_PASS); }
E(fn_80079710, 4) { bg_m_79710(GM_PASS); }
E(fn_80079780, 4) { bg_m_79780(GM_PASS); }
E(fn_800799E0, 4) { bg_m_799e0(GM_PASS); }
E(fn_80079AA0, 4) { bg_m_79aa0(GM_PASS); }
E(fn_80079B60, 4) { bg_m_79b60(GM_PASS); }
E(fn_8007A6C0, 4) { bg_m_7a6c0(GM_PASS); }
E(fn_8007AB70, 4) { bg_m_7ab70(GM_PASS); }
E(fn_8007AC40, 4) { bg_m_7ac40(GM_PASS); }
E(fn_8007BA70, 4) { bg_m_7ba70(GM_PASS); }
E(fn_8007BBA0, 4) { bg_m_7bba0(GM_PASS); }
E(fn_8007BBF0, 4) { bg_m_7bbf0(GM_PASS); }
E(fn_8007BC40, 4) { bg_m_7bc40(GM_PASS); }
E(fn_8007BD40, 4) { bg_m_7bd40(GM_PASS); }
E(fn_8007C7D0, 4) { bg_m_7c7d0(GM_PASS); }
E(fn_8007C950, 4) { bg_m_7c950(GM_PASS); }
E(fn_8007CA50, 4) { bg_m_7ca50(GM_PASS); }
E(fn_8007CA70, 4) { bg_m_7ca70(GM_PASS); }
E(fn_8007CD70, 4) { bg_m_7cd70(GM_PASS); }
E(fn_8007D5B0, 4) { bg_m_7d5b0(GM_PASS); }
E(fn_8007E0E0, 4) { bg_m_7e0e0(GM_PASS); }
E(fn_8007E170, 4) { bg_m_7e170(GM_PASS); }
E(fn_8007E180, 4) { bg_m_7e180(GM_PASS); }
E(fn_8007E1D0, 4) { bg_m_7e1d0(GM_PASS); }
E(fn_8007E2C0, 4) { bg_m_7e2c0(GM_PASS); }
E(fn_8007E3D0, 4) { bg_m_7e3d0(GM_PASS); }
E(fn_8007E430, 4) { bg_m_7e430(GM_PASS); }
E(fn_8007E4E0, 4) { bg_m_7e4e0(GM_PASS); }
E(fn_8007E520, 4) { bg_m_7e520(GM_PASS); }
E(fn_8007E860, 4) { bg_m_7e860(GM_PASS); }
E(fn_8007EC20, 4) { bg_m_7ec20(GM_PASS); }
E(__ct__9dBg_ctr_cFv, 4) { bg___ct__9dBg_ctr_cFv_7f7a0(GM_PASS); }
E(fn_8007F800, 4) { bg_m_7f800(GM_PASS); }
E(__dt__9dBg_ctr_cFv, 4) { bg___dt__9dBg_ctr_cFv_7f810(GM_PASS); }
E(fn_8007F880, 4) { bg_m_7f880(GM_PASS); }
E(fn_8007F8A0, 4) { bg_m_7f8a0(GM_PASS); }
E(entry__9dBg_ctr_cFv, 4) { bg_entry__9dBg_ctr_cFv_7f900(GM_PASS); }
E(release__9dBg_ctr_cFv, 4) { bg_release__9dBg_ctr_cFv_7f950(GM_PASS); }
E(baseSetup__7PhysicsFP8dActor_cPvPvPvUcUc, 4) { bg_baseSetup__7PhysicsFP8dActor_cPvPvPvUcUc_7f9b0(GM_PASS); }
E(set__9dBg_ctr_cFP8dActor_cffffPFP8dActor_cP8dActor_c_vPFP8dActor_cP8dActor_c_vPFP8dActor_cP8dActor_cUc_vUcUcP7mVec3_c, 4) { bg_set__9dBg_ctr_cFP8dActor_cffffPFP8dActor_7fa40(GM_PASS); }
E(fn_8007FAD0, 4) { bg_m_7fad0(GM_PASS); }
E(setup__7PhysicsFP8dActor_cPQ27Physics4InfoUcUcP7Point2d, 4) { bg_setup__7PhysicsFP8dActor_cPQ27Physics4In_7fb10(GM_PASS); }
E(setOfs__9dBg_ctr_cFffffP7mVec3_c, 4) { bg_setOfs__9dBg_ctr_cFffffP7mVec3_c_7fbf0(GM_PASS); }
E(fn_8007FCE0, 4) { bg_m_7fce0(GM_PASS); }
E(fn_8007FD10, 4) { bg_m_7fd10(GM_PASS); }
E(fn_8007FD40, 4) { bg_m_7fd40(GM_PASS); }
E(fn_8007FD60, 4) { bg_m_7fd60(GM_PASS); }
E(setPtrToRotation__7PhysicsFPs, 4) { bg_setPtrToRotation__7PhysicsFPs_7fd80(GM_PASS); }
E(calc__9dBg_ctr_cFv, 4) { bg_calc__9dBg_ctr_cFv_7fda0(GM_PASS); }
E(fn_8007FFA0, 4) { bg_m_7ffa0(GM_PASS); }
E(fn_80080170, 4) { bg_m_80170(GM_PASS); }
E(fn_80080530, 4) { bg_m_80530(GM_PASS); }
E(fn_800805D0, 4) { bg_m_805d0(GM_PASS); }
E(fn_80080630, 4) { bg_m_80630(GM_PASS); }
E(fn_80080670, 4) { bg_m_80670(GM_PASS); }
E(fn_80080880, 4) { bg_m_80880(GM_PASS); }
E(fn_80080900, 4) { bg_m_80900(GM_PASS); }
E(fn_80080D00, 4) { bg_m_80d00(GM_PASS); }
E(fn_80080D40, 4) { bg_m_80d40(GM_PASS); }
E(fn_80080D80, 4) { bg_m_80d80(GM_PASS); }
E(fn_80080E40, 4) { bg_m_80e40(GM_PASS); }
E(fn_80081030, 4) { bg_m_81030(GM_PASS); }
E(fn_80081070, 4) { bg_m_81070(GM_PASS); }
E(fn_80081300, 4) { bg_m_81300(GM_PASS); }
E(GetTilesetName__FPvii, 4) { bg_GetTilesetName__FPvii_813f0(GM_PASS); }
E(fn_80081410, 4) { bg_m_81410(GM_PASS); }
E(fn_800814D0, 4) { bg_m_814d0(GM_PASS); }
E(fn_800816A0, 4) { bg_m_816a0(GM_PASS); }
E(fn_80081780, 4) { bg_m_81780(GM_PASS); }
E(fn_80081800, 4) { bg_m_81800(GM_PASS); }
E(fn_80081870, 4) { bg_m_81870(GM_PASS); }
E(fn_80081890, 4) { bg_m_81890(GM_PASS); }
E(fn_800818B0, 4) { bg_m_818b0(GM_PASS); }
E(fn_800818D0, 4) { bg_m_818d0(GM_PASS); }
E(fn_80081900, 4) { bg_m_81900(GM_PASS); }
E(fn_80081AB0, 4) { bg_m_81ab0(GM_PASS); }
E(fn_80081BE0, 4) { bg_m_81be0(GM_PASS); }
E(fn_80081C40, 4) { bg_m_81c40(GM_PASS); }
E(fn_80081D20, 4) { bg_m_81d20(GM_PASS); }
E(fn_80081E90, 4) { bg_m_81e90(GM_PASS); }
E(fn_80081F40, 4) { bg_m_81f40(GM_PASS); }
E(fn_80082050, 4) { bg_m_82050(GM_PASS); }
E(fn_800820D0, 4) { bg_m_820d0(GM_PASS); }
E(fn_80082120, 4) { bg_m_82120(GM_PASS); }
E(fn_80082140, 4) { bg_m_82140(GM_PASS); }
E(fn_80082160, 4) { bg_m_82160(GM_PASS); }
E(fn_80082180, 4) { bg_m_82180(GM_PASS); }
E(fn_800821E0, 4) { bg_m_821e0(GM_PASS); }
E(getLoopScrollDispPosX__14dBgParameter_cFf, 4) { bg_getLoopScrollDispPosX__14dBgParameter_cF_82240(GM_PASS); }
E(fn_800822E0, 4) { bg_m_822e0(GM_PASS); }
E(fn_80082310, 4) { bg_m_82310(GM_PASS); }
E(fn_80082370, 4) { bg_m_82370(GM_PASS); }
E(fn_80082410, 4) { bg_m_82410(GM_PASS); }
E(fn_80082560, 4) { bg_m_82560(GM_PASS); }
E(fn_800825E0, 4) { bg_m_825e0(GM_PASS); }
E(fn_80082660, 4) { bg_m_82660(GM_PASS); }
E(fn_800826C0, 4) { bg_m_826c0(GM_PASS); }
E(fn_800826E0, 4) { bg_m_826e0(GM_PASS); }
E(fn_80082740, 4) { bg_m_82740(GM_PASS); }
E(fn_80082BE0, 4) { bg_m_82be0(GM_PASS); }
E(fn_80082ED0, 4) { bg_m_82ed0(GM_PASS); }
E(fn_80083380, 4) { bg_m_83380(GM_PASS); }
E(fn_800833E0, 4) { bg_m_833e0(GM_PASS); }
E(fn_80083440, 4) { bg_m_83440(GM_PASS); }
E(fn_800834B0, 4) { bg_m_834b0(GM_PASS); }
E(fn_800834D0, 4) { bg_m_834d0(GM_PASS); }
E(OriginalTilesetLoadingThing, 4) { bg_OriginalTilesetLoadingThing_83560(GM_PASS); }
E(fn_80083660, 4) { bg_m_83660(GM_PASS); }
E(fn_800837D0, 4) { bg_m_837d0(GM_PASS); }
E(fn_80083870, 4) { bg_m_83870(GM_PASS); }
E(fn_80083AD0, 4) { bg_m_83ad0(GM_PASS); }
E(fn_80083B30, 4) { bg_m_83b30(GM_PASS); }
E(fn_80083BD0, 4) { bg_m_83bd0(GM_PASS); }
E(fn_80083D00, 4) { bg_m_83d00(GM_PASS); }
E(fn_80083E20, 4) { bg_m_83e20(GM_PASS); }
E(fn_80083EC0, 4) { bg_m_83ec0(GM_PASS); }
E(fn_80083EE0, 4) { bg_m_83ee0(GM_PASS); }
E(fn_80083FC0, 4) { bg_m_83fc0(GM_PASS); }
E(fn_8007E7F0, 4) { bg_m_7e7f0(GM_PASS); }
E(fn_8007EA30, 4) { bg_m_7ea30(GM_PASS); }
E(fn_8007EA50, 4) { bg_m_7ea50(GM_PASS); }
E(fn_8007EA60, 4) { bg_m_7ea60(GM_PASS); }
E(fn_8007EA80, 4) { bg_m_7ea80(GM_PASS); }
E(fn_8007EB70, 4) { bg_m_7eb70(GM_PASS); }
E(fn_8007EBC0, 4) { bg_m_7ebc0(GM_PASS); }
E(fn_8007EBF0, 4) { bg_m_7ebf0(GM_PASS); }
E(fn_800803F0, 4) { bg_m_803f0(GM_PASS); }
E(fn_80080DC0, 4) { bg_m_80dc0(GM_PASS); }
E(fn_80080DE0, 4) { bg_m_80de0(GM_PASS); }
E(fn_80080E00, 4) { bg_m_80e00(GM_PASS); }
E(fn_800818E0, 4) { bg_m_818e0(GM_PASS); }
