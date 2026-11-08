/* gm_d_enemy.c - dEn_c, the base of every enemy (d_enemy.cpp): the lifecycle steps, movement,
 * the collision dispatch, stomps, liquids and the small helpers.
 * Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_enemy.cpp) and checked against the
 * recompiled USA rev 2 code - where they differ the recompiled code wins. The 8-player module
 * replaces preExecute, normal_collcheck, slipBound and setEatSpitOut (they stay recompiled: its
 * mNoHitPlayer is u8[8] at +0x504) and patches a few player loops (g_mod_on, as the recompiled
 * code does).
 *
 * dEn_c (after dActorMultiState_c):
 *   +0x414 mDeathInfo (+0x1E: +0x432 isDead)   +0x440 mFootPush   +0x44C mFootPush2
 *   +0x45C mFootAttr3   +0x45D mInLiquid   +0x4FC mFlags (2: hard)
 * dCc_c: +4 owner, +0x20/+0x28 offset y / size y, +0x2D attack kind, +0x34 vs-damage mask.
 * vtable (+0x60): +0x100 hitCallback_Star, +0x104 _Slip, +0x10C _Spin, +0x114 _WireNet,
 *   +0x118 _HipAttk, +0x11C _YoshiHipAttk, +0x124 _PenguinSlide, +0x128 _Cannon, +0x12C _Shell,
 *   +0x130 _Fire, +0x134 _Ice, +0x138 _YoshiBullet, +0x13C _YoshiFire, +0x220 setDamage. */
#include "gm.h"
#include "gm_nv.h"
#include <math.h>
#include <string.h>

/* gm_d_base.c / gm_f_base.c / gm_d_actor.c */
void dBaseActor_getCenterPos(GM_CTX, gptr out, gptr self);
void fBase_postCreate(GM_CTX, gptr self, uint32_t state);
void dActor_postExecute(GM_CTX, gptr self, uint32_t status);
int32_t dActor_preDraw(GM_CTX, gptr self);
extern int g_mod_on;

#define SDA 0x8042F680u
#define EXEC_STOP     (SDA - 0x5986)
#define SEARCH_FUNC   (SDA - 0x5984)     /* dActor_c::mSearchNearPlayerFunc */
#define BG_PARAM      (SDA - 0x5880)     /* dBgParameter_c::ms_Instance_p */
#define SND_OBJ_EMY   (SDA - 0x5924)     /* dAudio::g_pSndObjEmy */
#define AMI_LINE      0x8042BB18u        /* l_Ami_Line */
#define F_BOYON_INIT  0x80097F40u        /* dEn_c::boyonInit */
#define F_CHECK_WATER 0x80075270u        /* dBc_c::checkWater(x, y, layer, 0) */
#define F_CREATE_EFFECT 0x8016C890u      /* mEf::createEffect */
#define F_EFFECT_CHANGE 0x8008F9F0u      /* dEf::createEffect_change */
#define F_CVT_SND_POS 0x8006A4B0u        /* dAudio::cvtSndObjctPos */
#define F_START_SOUND 0x80197F00u        /* SndObjctCmnEmy::startSound */
#define F_SAKA_ANGLE  0x80070920u        /* dBc_c::getSakaMoveAngle */
#define F_COS_FIDX    0x80237C40u
#define F_SIN_FIDX    0x80237BD0u
#define F_IS_FOOT     0x80070CB0u        /* dBc_c::isFoot */
#define F_LINE_BOUNDARY 0x800971F0u      /* dEn_c::LineBoundaryCheck */
#define F_IS_MAME     0x80056BD0u        /* daPlBase_c::isMameAction */
#define F_SPIN_LIFT   0x8012E400u        /* dAcPy_c::spinLiftUp(actor, 1) */
#define F_CHECK_WALL  0x8006FA40u        /* dBc_c::checkWall(&dir) */
#define F_CHECK_BG    0x800709C0u        /* dBc_c::checkBg(x, y, layer, line, mask) */
#define F_DELETE      0x802B9280u        /* operator delete */

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f      /* (gm.h: the PowerPC function's frame and prologue) */
static uint32_t vcall3(GM_CTX, gptr obj, uint32_t off, uint32_t a, uint32_t b) { return GM_CALL(gm_u32(gm_u32(obj + 0x60) + off), 3, obj, a, b); }
/* an angle as the code loads it: psq_l through GQR3 */
static double gqr_load(GM_CTX, gptr a, int q) { uint32_t g = ctx->gqr[q], sz; return psq_dequant(base, a, (g >> 16) & 7, (g >> 24) & 0x3F, &sz); }

/* ================================================================== lifecycle */
void dEn_postCreate(GM_CTX, gptr self, uint32_t status) {
    FN(0x800951D0);
    GM_CALLR(0x800951F0u, F_BOYON_INIT, 1, self);
    ctx->f[1].d = ctx->ps1[1] = LF(self + 0xAC); ctx->f[2].d = ctx->ps1[2] = LF(self + 0xB0);
    if (GM_CALLR(0x80095204u, F_CHECK_WATER, 2, gm_u8(self + 0x38F), 0)) gm_set_u8(self + 0x45D, 1);
    fBase_postCreate(GM_PASS, self, status);
}
void dEn_postExecute(GM_CTX, gptr self, uint32_t status) {
    if (status == 2 && !(gm_u8(EXEC_STOP) & 8)) gm_set_u8(self + 0x34A, 0);
    dActor_postExecute(GM_PASS, self, status);
}

/* ================================================================== effects and sounds */
void dEn_hitdamageEffect(GM_CTX, gptr pos) {
    FN(0x800954D0);
    SF(f + 8, LF(pos)); SF(f + 12, LF(pos + 4)); SF(f + 16, R2F(28328));
    GM_CALLR(0x80095510u, F_CREATE_EFFECT, 5, 0x80311BB0u, 0, f + 8, 0, 0);       /* "Wm_en_hit" */
}
uint32_t dEn_hipatkEffect(GM_CTX, gptr self, gptr pos) {
    uint32_t name = (gm_u32(self + 0x4FC) & 2) ? 0x80311BBCu : 0x80311BCCu;   /* "Wm_mr_hardhit" / "Wm_mr_softhit" */
    return GM_CALL(F_EFFECT_CHANGE, 5, name, 0, pos, 0, 0);
}
void dEn_fumidamageSE(GM_CTX, gptr self) {
    FN(0x80095580);
    gptr obj = gm_u32(SDA - 22820);
    GM_CALLR(0x800955A4u, F_CVT_SND_POS, 2, f + 8, self + 0xAC);
    GM_CALLR(0x800955B8u, F_START_SOUND, 4, obj, 379, f + 8, 0);                    /* SE_EMY_DOWN */
}

/* ================================================================== movement */
/* posMove: speed along the slope (halved in liquids), the foot pushes. Register-exact (part 55):
   the PowerPC code's temporaries - the move vector at sp+12, the angles at sp+8 / sp+10, f30 / f31,
   r30 / r31 - are written as it writes them (the no-input attract demos diverged for good at field
   15342 with the earlier version: a later uninitialised read of this frame) */
void dEn_posMove(GM_CTX, gptr self) {
    FN(0x800955F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
#define R(n) ctx->r[n]
#define FD(n) ctx->f[n].d
#define FB(n, v) (ctx->f[n].d = ctx->ps1[n] = (v))
    FB(0, R2F(28344));
    R(30) = R(3);
    FB(1, LF(R(3) + 232));
    cr_fcmp(ctx, 0, FD(1), FD(0));
    R(0) = ctx->cr;
    R(3) = R(3) + 492;
    R(4) = (R(0) >> 31) & 1u;                                    /* (speed.x < 0) */
    GM_CALLV(0x80095634u, F_SAKA_ANGLE, 0);
    R(0) = gm_u8(R(30) + 1116);
    R(31) = R(3) & 0xFFFFu;
    cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
    if (R(0) != 0) {                                             /* (in a liquid: no move) */
        FB(0, R2F(28344));
        SF(f + 12, FD(0)); SF(f + 16, FD(0)); SF(f + 20, FD(0));
    } else {
        FB(0, LF(R(30) + 232));
        R(3) = f + 10;
        ctx->f[0].u &= ~0x8000000000000000ull;                   /* fabs: ps0 only */
        gm_set_u16(f + 10, (uint16_t)R(31));
        ctx->f[30].d = frsp(FD(0));                              /* (frsp: ps0 only) */
        psq_l(ctx, base, 1, R(3), 1, 3);
        FB(0, R2F(28320));
        FB(1, frsp(FD(0) * FD(1)));
        GM_CALLV(0x8009567Cu, F_COS_FIDX, 0);
        gm_set_u16(f + 8, (uint16_t)R(31));
        R(3) = f + 8;
        ctx->f[31].u = ctx->f[1].u;                              /* (fmr: ps0 only) */
        psq_l(ctx, base, 1, R(3), 1, 3);
        FB(0, R2F(28320));
        FB(1, frsp(FD(0) * FD(1)));
        GM_CALLV(0x80095698u, F_SIN_FIDX, 0);
        FB(1, frsp(FD(30) * FD(1)));
        R(0) = gm_u8(R(30) + 1117);
        FB(2, LF(R(30) + 236));
        FB(3, frsp(FD(30) * FD(31)));
        FB(0, LF(R(30) + 240));
        cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
        SF(f + 20, FD(0));
        FB(0, frsp(FD(2) + FD(1)));
        SF(f + 12, FD(3));
        SF(f + 16, FD(0));
        if (R(0) != 0) {                                         /* (the slow-down) */
            FB(0, R2F(28316)); FB(1, R2F(28344));
            FB(0, frsp(FD(3) * FD(0)));
            SF(R(30) + 1100, FD(1)); SF(R(30) + 1104, FD(1)); SF(R(30) + 1108, FD(1));
            SF(f + 12, FD(0));
        } else {
            R(0) = gm_u8(R(30) + 1074); R(3) = 0;
            cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
            if (R(0) != 0) R(3) = 1;
            else { R(0) = gm_u8(R(30) + 912); cr_cmp_s(ctx, 0, (int32_t)R(0), 0); if (R(0) != 0) R(3) = 1; }
            cr_cmp_s(ctx, 0, (int32_t)R(3), 0);
            if (R(3) == 0) {
                FB(1, LF(R(30) + 236)); FB(0, R2F(28344));
                cr_fcmp(ctx, 0, FD(1), FD(0));
                CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
                if (CR_BIT(ctx, 2)) {
                    FB(1, LF(f + 12)); FB(0, LF(R(30) + 1100));
                    FB(0, frsp(FD(1) + FD(0)));
                    SF(f + 12, FD(0));
                }
            }
        }
    }
    FB(3, LF(f + 12)); FB(1, LF(R(30) + 1088)); FB(2, LF(f + 16));
    FB(6, frsp(FD(3) + FD(1)));
    FB(0, LF(R(30) + 1092)); FB(4, LF(f + 20));
    FB(5, frsp(FD(2) + FD(0)));
    FB(3, LF(R(30) + 1096)); FB(1, LF(R(30) + 172));
    FB(3, frsp(FD(4) + FD(3)));
    FB(0, LF(R(30) + 176));
    FB(2, frsp(FD(1) + FD(6)));
    FB(1, frsp(FD(0) + FD(5)));
    FB(0, LF(R(30) + 180));
    SF(R(30) + 172, FD(2));
    FB(0, frsp(FD(0) + FD(3)));
    SF(R(30) + 176, FD(1));
    SF(R(30) + 180, FD(0));
    SF(f + 12, FD(6)); SF(f + 16, FD(5)); SF(f + 20, FD(3));    /* (after the restores: the frame's last words) */
    R(0) = lr;
#undef R
#undef FD
#undef FB
}
/* Bound(epsY, scaleX, scaleY): bounce off the floor */
void dEn_bound(GM_CTX, gptr self, double eps, double sx, double sy) {
    FN(0x800957B0);
    if (!GM_CALLR(0x800957F0u, F_IS_FOOT, 1, self + 0x1EC)) return;
    if (sx < R2F(28340)) {
        double v = frsp(LF(self + 0xE8) * sx);
        SF(self + 0xE8, v);
        if (frsp(fabs(v)) < R2F(28312)) SF(self + 0xE8, R2F(28344));
    }
    double y = LF(self + 0xEC), z = R2F(28344);
    if (y < z) {
        double v = frsp(frsp(-y) * sy);
        SF(self + 0xEC, v);
        if (v < eps) SF(self + 0xEC, z);
    }
}
/* checkDispIn: the centre inside the screen */
uint32_t dEn_checkDispIn(GM_CTX, gptr self) {
    FN(0x80095890);
    dBaseActor_getCenterPos(GM_PASS, f + 20, self);
    double x = LF(f + 20);
    dBaseActor_getCenterPos(GM_PASS, f + 8, self);
    double y = LF(f + 12);
    gptr bg = gm_u32(BG_PARAM);
    double xs = LF(bg + 56), ys = LF(bg + 60);
    double xe = frsp(xs + LF(bg + 64)), ye = frsp(ys - LF(bg + 68));
    if (x < xs || x > xe || y > ys) return 0;
    return !(y < ye);
}

/* ================================================================== collision dispatch */
/* Normal_VsPlHitCheck / Normal_VsYoshiHitCheck: damage the other unless across a line */
void dEn_vsHitCheck(GM_CTX, gptr self, gptr other) {
    FN(0x80095C20);
    gptr owner = gm_u32(other + 4);
    if (!GM_CALLR(0x80095C44u, F_LINE_BOUNDARY, 2, self, owner)) GM_CALLR(0x80095C64u, gm_u32(gm_u32(self + 0x60) + 0x220), 2, self, owner);
}
uint32_t dEn_enDamageCheck(GM_CTX, gptr self, gptr me, gptr other) {
    FN(0x80095CE0);
    return gm_u8(other + 0x2D) == 9 && vcall3(GM_PASS, self, 0x12C, me, other);
}
uint32_t dEn_plDamageCheck(GM_CTX, gptr self, gptr me, gptr other) {
    FN(0x80095D30);
    gptr owner = gm_u32(other + 4);
    if (gm_u8(owner + 0x38C) != 1) return 0;
    if (gm_u8(other + 0x2D) == 3 && vcall3(GM_PASS, self, 0x100, me, other)) return 1;
    if (gm_u8(other + 0x2D) == 7) {
        if (GM_CALLR(0x80095DB0u, F_IS_MAME, 1, owner)) return 0;
        if (vcall3(GM_PASS, self, 0x118, me, other)) return 1;
    }
    if (gm_u8(other + 0x2D) == 5 && (gm_u32(me + 0x34) & 0x20) && vcall3(GM_PASS, self, 0x104, me, other)) return 1;
    if (gm_u8(other + 0x2D) == 0xA) {
        if (gm_u32(self + 0x120) & 0x200) return 0;
        if (vcall3(GM_PASS, self, 0x124, me, other)) return 1;
    }
    if (gm_u8(other + 0x2D) == 0xD && vcall3(GM_PASS, self, 0x10C, me, other)) return 1;
    if (gm_u8(other + 0x2D) == 0x11 && vcall3(GM_PASS, self, 0x128, me, other)) return 1;
    if (gm_u8(other + 0x2D) == 8 && vcall3(GM_PASS, self, 0x114, me, other)) return 1;
    return 0;
}
uint32_t dEn_yoshiDamageCheck(GM_CTX, gptr self, gptr me, gptr other) {
    FN(0x80095F50);
    if (gm_u8(gm_u32(other + 4) + 0x38C) != 2) return 0;
    if (gm_u8(other + 0x2D) == 3 && vcall3(GM_PASS, self, 0x100, me, other)) return 1;
    if (gm_u8(other + 0x2D) == 7 && vcall3(GM_PASS, self, 0x11C, me, other)) return 1;
    if (gm_u8(other + 0x2D) == 5 && (gm_u32(me + 0x34) & 0x20) && vcall3(GM_PASS, self, 0x104, me, other)) return 1;
    return 0;
}
uint32_t dEn_etcDamageCheck(GM_CTX, gptr me, gptr other) {
    FN(0x80096060);
    gptr o = gm_u32(me + 4);
    uint32_t k = gm_u8(other + 0x2D), vs;
    if (k == 9 && vcall3(GM_PASS, o, 0x12C, me, other)) return 1;
    k = gm_u8(other + 0x2D);
    if (k == 1 && (gm_u32(me + 0x34) & 2) && vcall3(GM_PASS, o, 0x130, me, other)) return 1;
    k = gm_u8(other + 0x2D);
    if (k == 0x14 && (gm_u32(me + 0x34) & 0x100000) && vcall3(GM_PASS, o, 0x13C, me, other)) return 1;
    k = gm_u8(other + 0x2D);
    if (k == 0xE && vcall3(GM_PASS, o, 0x130, me, other)) return 1;
    k = gm_u8(other + 0x2D);
    vs = (k == 2 && (gm_u32(me + 0x34) & 4)) || (k == 0x15 && (gm_u32(me + 0x34) & 0x200000));
    if (vs && vcall3(GM_PASS, o, 0x134, me, other)) return 1;
    k = gm_u8(other + 0x2D);
    if (k == 0x13 && (gm_u32(me + 0x34) & 0x80000) && vcall3(GM_PASS, o, 0x138, me, other)) return 1;
    return 0;
}

/* ================================================================== small helpers */
/* getPl_LRflag / getPl_UDflag(pos): the nearest player left of / below pos */
uint32_t dEn_getPlFlag(GM_CTX, gptr pos, int ud) {
    FN((ud ? 0x800962A0u : 0x80096240u));
    SF(f + 8, LF(pos)); SF(f + 12, LF(pos + 4));
    uint32_t r = 0;
    if (GM_CALL(gm_u32(SEARCH_FUNC), 2, f + 16, f + 8)) r = LF(f + 16 + 4 * ud) < R2F(28344);
    return r;
}
/* CeilCheck(y, cc): the collider's bottom above the screen's top */
uint32_t dEn_ceilCheck(GM_CTX, double y, gptr cc) {
    double t = frsp(frsp(y + LF(cc + 32)) - LF(cc + 40));
    return t > LF(gm_u32(BG_PARAM) + 60);
}
/* carry_check(player): picked up */
uint32_t dEn_carryCheck(GM_CTX, gptr self, gptr pl) {
    FN(0x80096330);
    if (!GM_CALLR(0x8009635Cu, F_SPIN_LIFT, 3, pl, self, 1)) return 0;
    gptr n = GM_CALLR(0x80096378u, gm_u32(gm_u32(pl + 0x60) + 0x6C), 1, pl);
    gm_set_u8(self + 0x38D, gm_u8(n));
    return 1;
}
/* checkWallAndBg: the wall ahead, then the ground at the centre */
uint32_t dEn_checkWallAndBg(GM_CTX, gptr self) {
    FN(0x800963B0);
    SF(f + 8, frsp((double)(int8_t)gm_u8(ctx->r[2] - 28384 + gm_u8(self + 0x348))));
    GM_CALLR(0x80096400u, F_CHECK_WALL, 2, self + 0x1EC, f + 8);
    double x = frsp(LF(self + 0xAC) + LF(self + 0xD0)), y = frsp(LF(self + 0xB0) + LF(self + 0xD4));
    SF(f + 12, x); SF(f + 16, y); SF(f + 20, frsp(LF(self + 0xB4) + LF(self + 0xD8)));
    ctx->f[1].d = ctx->ps1[1] = x; ctx->f[2].d = ctx->ps1[2] = y;
    uint32_t r = GM_CALLR(0x8009644Cu, F_CHECK_BG, 3, gm_u8(self + 0x38F), gm_u8(AMI_LINE + gm_u8(self + 0x391)), 0x819);
    return r;
}

/* ================================================================== stomps */
#define F_FUMI_OPERATE 0x800A29C0u       /* dEnFumiProc_c::operate(info, 1) */
#define F_FUMI_CNT    0x8009F5F0u        /* dEnCombo_c::calcPlFumiCnt */
#define F_SCORE_SET   0x800E1F80u        /* dScoreMng_c::ScoreSet(pos, n, player, 1) */
#define F_SCORE_SET2  0x800E2220u        /* dScoreMng_c::ScoreSet2(pos, n, player) */
#define F_CLAP_SE     0x800CE8C0u        /* dMultiMng_c::setClapSE */
#define F_ANKLE_POS   0x800582F0u        /* daPlBase_c::getAnkleCenterPos */
#define F_STEP_SE     0x80096CA0u        /* dEn_c::fumistepSE / yoshifumistepSE */
#define F_YSTEP_SE    0x80096D00u
#define F_SPIN_JUMP   0x80096780u        /* dEn_c::SpinFumiJumpSet / SpinFumiScoreSet */
#define F_SPIN_SCORE  0x80096790u
#define SCORE_MNG     (SDA - 22064)      /* dScoreMng_c::m_instance */
#define MULTI_MNG     (SDA - 22224)      /* dMultiMng_c::mspInstance */
#define ENEMY_MNG     (SDA - 22384)      /* dEnemyMng_c::m_instance */
/* a guest call that also hands back r4 / r5 as the callee left them (the code passes them on) */
static uint32_t gcall2_regs(GM_CTX, uint32_t fn, uint32_t a, uint32_t b, uint32_t *r4, uint32_t *r5) {
    uint32_t saved[13], lr = ctx->lr, ctr = ctx->ctr;
    memcpy(saved, ctx->r, sizeof saved);
    ctx->r[3] = a; ctx->r[4] = b; ctx->lr = 0;
    ppc_call_indirect(ctx, base, fn);
    uint32_t ret = ctx->r[3]; *r4 = ctx->r[4]; *r5 = ctx->r[5];
    memcpy(ctx->r, saved, sizeof saved); ctx->lr = lr; ctx->ctr = ctr;
    return ret;
}
static void vcall_a(GM_CTX, gptr self, uint32_t off, gptr actor) { GM_CALL(gm_u32(gm_u32(self + 0x60) + off), 2, self, actor); }
/* Enfumi_check(me, other, step): the stomp kind (1 normal, 2 mini, 3 spin) and its reactions */
int32_t dEn_enfumiCheck(GM_CTX, gptr self, gptr me, gptr other, int32_t step) {
    FN(0x800964A0);
    gm_set_u32(f + 8, 0x80311E6Cu); gm_set_u32(f + 12, me); gm_set_u32(f + 16, other);   /* FumiCcInfo_c */
    int32_t r = (int32_t)GM_CALLR(0x800964ECu, F_FUMI_OPERATE, 3, self + 0x514, f + 8, 1);
    gptr o = gm_u32(other + 4);
    if (r == 1) {
        if (gm_u8(o + 0x38C) == 1) {
            if (step == 0) { vcall_a(GM_PASS, self, 0x260, o); vcall_a(GM_PASS, self, 0x264, o); }
            else if (step == 1) GM_CALLR(0x8009656Cu, F_STEP_SE, 2, self, o);
            vcall_a(GM_PASS, self, 0x24C, o); vcall_a(GM_PASS, self, 0x250, o);
        } else {
            if (step == 0) { vcall_a(GM_PASS, self, 0x278, o); vcall_a(GM_PASS, self, 0x27C, o); }
            else if (step == 1) GM_CALLR(0x800965F0u, F_YSTEP_SE, 2, self, o);
            vcall_a(GM_PASS, self, 0x258, o); vcall_a(GM_PASS, self, 0x25C, o);
        }
    } else if (r == 2) {
        vcall_a(GM_PASS, self, 0x254, o); vcall_a(GM_PASS, self, 0x270, o); vcall_a(GM_PASS, self, 0x274, o);
    } else if (r == 3) {
        if (step == 0) { vcall_a(GM_PASS, self, 0x268, o); vcall_a(GM_PASS, self, 0x26C, o); }
        else if (step == 1) GM_CALLR(0x800966C0u, F_STEP_SE, 2, self, o);
        GM_CALLR(0x800966CCu, F_SPIN_JUMP, 2, self, o); GM_CALLR(0x800966D8u, F_SPIN_SCORE, 2, self, o);
    }
    return r;
}
/* PlayerFumiJump(actor, speed): the player jumps off */
void dEn_playerFumiJump(GM_CTX, gptr actor, double v) {
    FN(0x800967A0);
    ctx->f[1].d = ctx->ps1[1] = v; ctx->f[2].d = ctx->ps1[2] = LF(actor + 0x10C);
    GM_CALLR(0x800967D0u, gm_u32(gm_u32(actor + 0x60) + 0x3FC), 4, actor, 1, 0, 2);
    gm_set_u32(gm_u32(ENEMY_MNG) + 312, 1);
}
static double fumi_speed(GM_CTX) { return frsp(R2F(28296) + LF(SDA - 21360)); }
void dEn_mameFumiJumpSet(GM_CTX, gptr self, gptr actor) {
    double v = frsp(fumi_speed(GM_PASS) * R2F(28292)), y = LF(self + 0xEC);
    if (y > R2F(28344)) v = frsp(v + frsp(R2F(28288) * y));
    dEn_playerFumiJump(GM_PASS, actor, v);
}
/* setFumiComboScore(actor): the combo score above the enemy */
void dEn_setFumiComboScore(GM_CTX, gptr self, gptr actor) {
    FN(0x800967F0);
    int32_t n = (int32_t)GM_CALLR(0x80096818u, F_FUMI_CNT, 1, actor);
    if (n < 0) return;
    dBaseActor_getCenterPos(GM_PASS, f + 8, self);
    SF(f + 12, frsp(LF(self + 0xB0) + R2F(25588)));
    int32_t t = (int32_t)gm_u32(self + 0x510);
    if (t == 1 || t == 2) {
        gptr mgr = gm_u32(SCORE_MNG);
        gptr pn = GM_CALL(gm_u32(gm_u32(actor + 0x60) + 0x6C), 1, actor);
        uint32_t pl = (uint32_t)(int32_t)(int8_t)gm_u8(pn);
        if (t == 1) GM_CALLR(0x8009688Cu, F_SCORE_SET, 5, mgr, f + 8, (uint32_t)n, pl, 1);
        else GM_CALLR(0x800968C0u, F_SCORE_SET2, 4, mgr, f + 8, (uint32_t)n, pl);
    }
}
/* fumiSE / spinfumiSE / yoshifumiSE(actor): the combo sound (and the clap at 7) */
void dEn_comboSE(GM_CTX, gptr self, gptr actor, int kind) {
    FN((kind == 0 ? 0x80096910u : kind == 1 ? 0x80096A20u : 0x80096B30u));
    static const uint32_t flag[3] = { SDA - 22400, SDA - 22399, SDA - 22398 };
    static const uint32_t tab[3] = { 0x80357638u, 0x8035765Cu, 0x80357680u }, first[3] = { 372, 388, 397 };
    if (!(int8_t)gm_u8(flag[kind])) {
        for (int i = 0; i < 9; i++) gm_set_u32(tab[kind] + 4 * i, first[kind] + (i < 6 ? i : 6));
        gm_set_u8(flag[kind], 1);
    }
    uint32_t n = (uint32_t)(int32_t)(int8_t)gm_u8(actor + 0x1080);
    if (n >= 9) n = 8;
    uint32_t r4, r5;
    if (gcall2_regs(GM_PASS, gm_u32(gm_u32(self + 0x60) + 0x248), self, n, &r4, &r5))
        GM_CALL(F_CLAP_SE, 3, gm_u32(MULTI_MNG), r4, r5);
    dBaseActor_getCenterPos(GM_PASS, f + 16, self);
    gptr obj = gm_u32(SDA - 22820);
    GM_CALL(F_CVT_SND_POS, 2, f + 8, f + 16);
    GM_CALL(F_START_SOUND, 4, obj, gm_u32(tab[kind] + 4 * n), f + 8, 0);
}
/* a sound at the centre (mamefumiSE 352, fumistepSE 351, yoshifumistepSE 353) */
void dEn_centreSE(GM_CTX, gptr self, uint32_t se) {
    FN((se == 352 ? 0x80096C40u : se == 351 ? 0x80096CA0u : 0x80096D00u));
    dBaseActor_getCenterPos(GM_PASS, f + 16, self);
    gptr obj = gm_u32(SDA - 22820);
    GM_CALL(F_CVT_SND_POS, 2, f + 8, f + 16);
    GM_CALL(F_START_SOUND, 4, obj, se, f + 8, 0);
}
/* fumiEffect(actor): the hit effect at a player's / Yoshi's ankles */
void dEn_fumiEffect(GM_CTX, gptr actor) {
    FN(0x80096D60);
    uint32_t k = gm_u8(actor + 0x38C);
    if (k != 1 && k != 2) return;
    GM_CALLR(0x80096D94u, F_ANKLE_POS, 2, f + 20, actor);
    SF(f + 32, LF(f + 20));
    GM_CALLR(0x80096DA8u, F_ANKLE_POS, 2, f + 8, actor);
    SF(f + 36, LF(f + 12)); SF(f + 40, R2F(28328));
    GM_CALLR(0x80096DD4u, F_CREATE_EFFECT, 5, 0x80311BB0u, 0, f + 32, 0, 0);
}
void dEn_spinfumiEffect(GM_CTX, gptr actor) {
    FN(0x80096DF0);
    SF(f + 8, LF(actor + 0xAC)); SF(f + 12, LF(actor + 0xB0)); SF(f + 16, R2F(28328));
    GM_CALLR(0x80096E30u, F_CREATE_EFFECT, 5, 0x80311BB0u, 0, f + 8, 0, 0);
}

/* ================================================================== the ground, walls, ceiling */
#define F_CHECK_HEAD  0x8006EF40u        /* dBc_c::checkHead(flags) */
#define F_RC_CHECK2   0x800D9A30u        /* dRc_c::check2 */
#define F_FOOT_ENM    0x80072BC0u        /* dBc_c::checkFootEnm */
#define F_FOOT_ATTR   0x80070720u        /* dBc_c::getFootAttr */
#define F_WALL_ENM    0x80072CB0u        /* dBc_c::checkWallEnm(&dir) */
uint32_t dEn_bgCheckFoot(GM_CTX, gptr self) {
    FN(0x80096F60);
    double z = R2F(28344);
    if (!gm_u32(self + 0x1F4)) { SF(self + 0x44C, z); SF(self + 0x450, z); SF(self + 0x454, z); return 0; }
    uint32_t r = GM_CALLR(0x80096FA4u, F_FOOT_ENM, 1, self + 0x1EC);
    gm_set_u8(self + 0x45C, 0); gm_set_u8(self + 0x45E, 0);
    if (GM_CALLR(0x80096FBCu, F_IS_FOOT, 1, self + 0x1EC)) {
        uint32_t a = GM_CALLR(0x80096FCCu, F_FOOT_ATTR, 1, self + 0x1EC) & 0xFFFF;
        if (a == 3) gm_set_u8(self + 0x45C, 1);
        if (a == 1) gm_set_u8(self + 0x45E, 1);
        double x = LF(self + 0x20C), y = LF(self + 0x210), w = LF(self + 0x214);
        SF(self + 0x440, x); SF(self + 0x444, y); SF(self + 0x448, w);
        SF(self + 0x44C, z); SF(self + 0x450, z); SF(self + 0x454, z);
    } else { SF(self + 0x440, z); SF(self + 0x444, z); SF(self + 0x448, z); }
    return r;
}
uint32_t dEn_bgCheckWall(GM_CTX, gptr self) {
    FN(0x80097050);
    if (!gm_u32(self + 0x1FC)) return 0;
    uint32_t lt = frsp(LF(self + 0xAC) - LF(self + 0x238)) < R2F(28344);
    gptr muki = ctx->r[2] - 28384;
    SF(f + 8, frsp((double)(int8_t)gm_u8(muki + lt)));
    uint32_t w1 = GM_CALLR(0x800970D8u, F_WALL_ENM, 2, self + 0x1EC, f + 8);
    SF(f + 8, frsp((double)(int8_t)gm_u8(muki + (lt ^ 1))));
    uint32_t w2 = GM_CALLR(0x80097110u, F_WALL_ENM, 2, self + 0x1EC, f + 8);
    if (gm_u8(self + 0x34A) & 3) w2 |= GM_CALLR(0x8009712Cu, F_WALL_ENM, 2, self + 0x1EC, f + 8);
    gm_set_u32(self + 0x274, gm_u32(self + 0x274) | w1 | w2);
    return w1;
}
/* EnBgCheck: 1 foot, 2 head, 4 wall (and the rail check) */
uint32_t dEn_bgCheck(GM_CTX, gptr self) {
    FN(0x80096E60);
    uint32_t fl = 0;
    uint32_t foot = dEn_bgCheckFoot(GM_PASS, self);
    if (foot) { fl |= 1; SF(self + 0xEC, R2F(28344)); }
    uint32_t head = GM_CALLR(0x80096EACu, F_CHECK_HEAD, 2, self + 0x1EC, foot);
    if (head) fl |= 2;
    uint32_t wall = dEn_bgCheckWall(GM_PASS, self);
    if (wall) fl |= 4;
    uint32_t bf = gm_u32(self + 0x274), all = head | wall | foot;
    if ((bf & 0x8000) && (bf & 3) && gm_u32(self + 0x23C)) {
        uint32_t up = LF(self + 0xEC) > R2F(28344);
        if (!GM_CALLR(0x80096F20u, F_RC_CHECK2, 4, gm_u32(self + 0x23C), all & 0x1F6000, up, 0))
            gm_set_u32(self + 0x274, gm_u32(self + 0x274) & ~0x8000u);
    }
    return fl;
}

/* ================================================================== liquids */
#define F_DEATH_YOGAN 0x800A0DC0u        /* dEn_c::setDeathInfo_YoganFall(0) */
#define F_WATER_DEPTH 0x80076530u
#define F_SPLASH_EFF  0x800929F0u
#define F_SND_MAP     0x80198C30u
#define F_WATER_WAVE  0x80078410u
/* WaterLineProc(pos, h): water (1, 2), lava (3), poison (4): entering sets the liquid speeds
   and splashes; leaving puts the air speeds back */
int32_t dEn_waterLineProc(GM_CTX, gptr self, gptr pos, double h) {
    FN(0x80097250);
    SF(f + 8, R2F(28344));
    ctx->f[1].d = ctx->ps1[1] = LF(pos); ctx->f[2].d = ctx->ps1[2] = LF(pos + 4);
    int32_t r = (int32_t)GM_CALLR(0x80097290u, F_CHECK_WATER, 2, gm_u8(self + 0x38F), f + 8);
    SF(f + 12, LF(self + 0xAC)); SF(f + 16, LF(f + 8)); SF(f + 20, R2F(28284));
    uint32_t vt = gm_u32(self + 0x60);
    if ((uint32_t)(r - 1) <= 1) {
        if (!gm_u8(self + 0x45D)) {
            double a = LF(self + 0x114), m = LF(self + 0xF8), fl = LF(self + 0x118);
            gm_set_u8(self + 0x45D, 1);
            SF(self + 0x4F0, a); SF(self + 0x4F4, m); SF(self + 0x4F8, fl);
            GM_CALL(gm_u32(vt + 0x21C), 1, self);
            ctx->f[1].d = ctx->ps1[1] = h;
            GM_CALL(gm_u32(gm_u32(self + 0x60) + 0xC8), 2, self, f + 12);
        }
    } else if (r == 3 || r == 4) {
        if (!gm_u8(self + 0x45D)) {
            gm_set_u8(self + 0x45D, 1);
            ctx->f[1].d = ctx->ps1[1] = h;
            GM_CALL(gm_u32(vt + (r == 3 ? 0xCC : 0xD0)), 2, self, f + 12);
        }
    } else {
        if (gm_u8(self + 0x45D)) {
            double a = LF(self + 0x4F0), m = LF(self + 0x4F4), fl = LF(self + 0x4F8);
            SF(self + 0x114, a); SF(self + 0xF8, m); SF(self + 0x118, fl);
        }
        gm_set_u8(self + 0x45D, 0);
    }
    return r;
}
/* WaterCheck(pos, h): lava kills; any liquid after a kill counts as killed */
void dEn_waterCheck(GM_CTX, gptr self, gptr pos, double h) {
    FN(0x80097170);
    if (gm_u8(self + 0x45A)) return;
    int32_t r = dEn_waterLineProc(GM_PASS, self, pos, h);
    if (r == 3) { GM_CALLR(0x800971A8u, F_DEATH_YOGAN, 2, self, 0); gm_set_u8(self + 0x45A, 1); }
    else if (r != 0 && gm_u8(self + 0x390)) gm_set_u8(self + 0x45A, 1);
}
/* LineBoundaryCheck(actor): on the other side of a fence line */
uint32_t dEn_lineBoundaryCheck(GM_CTX, gptr self, gptr actor) {
    double z = LF(actor + 0xB4), zero = R2F(28344);
    int chk = (z > zero && gm_u8(self + 0x391) == 1);
    if (!chk) { z = LF(actor + 0xB4); chk = z < zero && gm_u8(self + 0x391) == 0; }
    if (!chk) return 0;
    uint32_t fl = gm_u32(actor + 0x10D8);
    return (fl & 0x80000) || (fl & 0x100000);
}
/* the enemy's lava / poison splash (as dActor_c's, with its own z and kinds 5 / 7) */
void dEn_splash(GM_CTX, gptr self, gptr pos, double size, int poison) {
    FN((poison ? 0x800974F0u : 0x800973F0u));
    double x = LF(pos), y = LF(pos + 4);
    SF(f + 40, x); SF(f + 44, y); SF(f + 48, R2F(28284));
    uint32_t info = (poison ? 7 : 5) | gm_u8(self + 0x38F) << 16;
    SF(f + 28, size); SF(f + 32, size); SF(f + 36, size);
    SF(f + 16, size); SF(f + 20, size); SF(f + 24, size);
    GM_CALL(F_SPLASH_EFF, 5, gm_u32(SDA - 0x5798), f + 40, info, 0xFFFFFFFFu, f + 16);
    gptr obj = gm_u32(SDA - 0x5920);
    GM_CALL(F_CVT_SND_POS, 2, f + 8, poison ? pos : f + 40);
    GM_CALL(F_SND_MAP, 4, obj, poison ? 643 : 644, f + 8, 0);
    ctx->f[1].d = ctx->ps1[1] = LF(pos); ctx->f[2].d = ctx->ps1[2] = LF(pos + 4);
    int small = size < R2F(28340);
    GM_CALL(F_WATER_WAVE, 2, gm_u32(SDA - 0x58B0), poison ? (small ? 23 : 21) : (small ? 16 : 14));
}
/* EnLavaCheck(pos): in lava; a splash when crossing the surface going down */
uint32_t dEn_lavaCheck(GM_CTX, gptr self, gptr pos) {
    FN(0x800975F0);
    SF(f + 8, R2F(28344));
    ctx->f[1].d = ctx->ps1[1] = LF(pos); ctx->f[2].d = ctx->ps1[2] = LF(pos + 4);
    uint32_t r = 0;
    if ((int32_t)GM_CALLR(0x80097628u, F_CHECK_WATER, 2, gm_u8(self + 0x38F), f + 8) == 3) {
        double h = LF(f + 8);
        if (h < R2F(28344) && LF(self + 0xBC) > h && LF(self + 0xB0) <= h) {
            SF(f + 12, LF(pos)); SF(f + 16, h); SF(f + 20, R2F(28280));
            ctx->f[1].d = ctx->ps1[1] = R2F(28340);
            GM_CALLR(0x8009768Cu, gm_u32(gm_u32(self + 0x60) + 0xCC), 2, self, f + 12);
        }
        r = 1;
    }
    return r;
}
uint32_t dEn_waterFlagCheck(GM_CTX, gptr self, gptr pos) {
    FN(0x80097700);
    ctx->f[1].d = ctx->ps1[1] = LF(pos); ctx->f[2].d = ctx->ps1[2] = LF(pos + 4);
    uint32_t r = GM_CALLR(0x80097728u, F_CHECK_WATER, 2, gm_u8(self + 0x38F), 0);
    if (r - 1 > 1) return 0;
    GM_CALLR(0x80097748u, gm_u32(gm_u32(self + 0x60) + 0x21C), 1, self);
    return 1;
}
uint32_t dEn_waterCheckSpeed(GM_CTX, gptr self, gptr pos) {
    FN(0x800976B0);
    if (dEn_waterFlagCheck(GM_PASS, self, pos)) return 1;
    double v = R2F(28332);
    SF(self + 0xF8, v); SF(self + 0x118, v);
    return 0;
}
/* setWaterSpeed: the liquid gravity, all vertical speeds clamped */
static void clamp_w(GM_CTX, gptr a) {
    double v = LF(a), lo = R2F(28272);
    if (v < lo) { SF(a, lo); return; }
    double hi = R2F(28268);
    if (v > hi) SF(a, hi);
}
void dEn_setWaterSpeed(GM_CTX, gptr self) {
    SF(self + 0x114, R2F(28276));
    clamp_w(GM_PASS, self + 0xF8); clamp_w(GM_PASS, self + 0x118); clamp_w(GM_PASS, self + 0xEC);
}

/* ================================================================== players near / carrying */
#define F_GET_PLAYER  0x8005F900u        /* daPyMng_c::getPlayer */
#define ACTIVE_MASK   (SDA - 23000)      /* (u8: the players in the game) */
gptr fManager_searchBaseByID(GM_CTX, uint32_t id);
/* Area_X_check(x) / Area_XY_check(x, y): a player that close */
uint32_t dEn_areaCheck(GM_CTX, gptr self, double dx, double dy, int xy) {
    FN((xy ? 0x800978C0u : 0x80097800u));
    int n = g_mod_on ? 8 : 4;
    for (int i = 0; i < n; i++) {
        GM_LOOP();
        gptr p = GM_CALL(F_GET_PLAYER, 1, (uint32_t)i);
        if (!p || !(gm_u8(ACTIVE_MASK) & (1u << i))) continue;
        if (!(frsp(fabs(frsp(LF(p + 0xAC) - LF(self + 0xAC)))) < dx)) continue;
        if (!xy || frsp(fabs(frsp(LF(p + 0xB0) - LF(self + 0xB0)))) < dy) return 1;
    }
    return 0;
}
uint32_t dEn_playerCarryCheck(GM_CTX, gptr self) {
    /* register-exact (part 56): the loop polls on its back-edge only, as the PowerPC loop does
       (the earlier version polled before every player: one poll too many per call - the no-input
       A/B's last blip, an interrupt's timestamp at field 12517) */
    FN(0x800979B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    ctx->r[31] = 0; ctx->r[30] = ctx->r[3];
    int n = g_mod_on ? 8 : 4;
    for (;;) {
        ctx->r[3] = ctx->r[31];
        GM_CALLV(0x800979D4u, F_GET_PLAYER, 0);
        cr_cmp_s(ctx, 0, (int32_t)ctx->r[3], 0);
        if (ctx->r[3]) {
            ctx->r[3] = gm_u32(ctx->r[3] + 10872);
            GM_CALLV(0x800979E4u, 0x80162D00u, 0);                    /* fManager_c::searchBaseByID */
            cr_cmp_u(ctx, 0, ctx->r[3], ctx->r[30]);
            if (ctx->r[3] == ctx->r[30]) { ctx->r[3] = 1; break; }
        }
        ctx->r[31] = ctx->r[31] + 1;
        cr_cmp_s(ctx, 0, (int32_t)ctx->r[31], n);
        if ((int32_t)ctx->r[31] >= n) { ctx->r[3] = 0; break; }
        GM_LOOP();
    }
    ctx->r[0] = lr;
    return ctx->r[3];
}
/* calcCarryPos(out, pos): pos in the carrying player's hands */
#define F_TEST_FLAG   0x80056CF0u        /* daPlBase_c::testFlag */
#define F_CARRY_OFS   0x8012DE80u
#define F_MODEL       0x80056E30u
#define F_MTX_TRANS   0x801C0BD0u
#define F_MTX_CONCAT  0x801C0540u
#define F_MULT_ZERO   0x8016F130u
void dEn_calcCarryPos(GM_CTX, gptr out, gptr self, gptr pos) {
    FN(0x80097A20);
    gptr p = GM_CALLR(0x80097A54u, F_GET_PLAYER, 1, (uint32_t)(int32_t)(int8_t)gm_u8(self + 0x38D));
    if (GM_CALLR(0x80097A60u, F_TEST_FLAG, 2, p, 4)) {
        double x = LF(self + 0xAC), y = LF(self + 0xB0), z = LF(self + 0xB4);
        SF(out, x); SF(out + 4, y); SF(out + 8, z);
        return;
    }
    GM_CALLR(0x80097A90u, F_CARRY_OFS, 2, f + 8, p);
    ctx->f[1].d = ctx->ps1[1] = LF(f + 8); ctx->f[2].d = ctx->ps1[2] = LF(f + 12); ctx->f[3].d = ctx->ps1[3] = LF(f + 16);
    GM_CALLR(0x80097AA4u, F_MTX_TRANS, 1, f + 80);
    gptr m = GM_CALLR(0x80097AACu, F_MODEL, 1, p);
    GM_CALLR(0x80097AC0u, F_MTX_CONCAT, 3, f + 80, m + 264, f + 80);
    ctx->f[1].d = ctx->ps1[1] = LF(pos); ctx->f[2].d = ctx->ps1[2] = LF(pos + 4); ctx->f[3].d = ctx->ps1[3] = LF(pos + 8);
    GM_CALLR(0x80097AD4u, F_MTX_TRANS, 1, f + 32);
    GM_CALLR(0x80097AE4u, F_MTX_CONCAT, 3, f + 80, f + 32, f + 80);
    GM_CALLR(0x80097AF0u, F_MULT_ZERO, 2, f + 80, f + 20);
    double x = LF(f + 20), y = LF(f + 24), z = LF(f + 28);
    SF(out, x); SF(out + 4, y); SF(out + 8, z);
}
/* turnangle_calc(target, delta): turn by delta[dir] until past target */
uint32_t dEn_turnangleCalc(GM_CTX, gptr self, gptr target, gptr delta) {
    uint32_t d = gm_u8(self + 0x348);
    int16_t a = (int16_t)((int16_t)gm_u16(self + 0x102) + (int16_t)gm_u16(delta + 2 * d));
    gm_set_u16(self + 0x102, (uint16_t)a);
    if ((int16_t)gm_u16(target) <= a || a <= (int16_t)gm_u16(target + 2)) {
        gm_set_u16(self + 0x102, gm_u16(target + 2 * gm_u8(self + 0x348)));
        return 1;
    }
    return 0;
}

/* ================================================================== eating, fire / ice, damage */
#define F_ACTOR_EAT_IN 0x80065A40u       /* dActor_c::calcEatInScale */
#define F_NICE_POINT  0x800CEA20u        /* dMultiMng_c (the enemy-down count) */
#define F_ICE_MISS    0x800943B0u        /* EffectManager_c::SetIceBallMissshitEffect */
#define F_BOYO_BEGIN  0x8009EA30u        /* dEnBoyoMng_c::begin */
#define STATE_EAT_IN  0x80358084u        /* dEn_c::StateID_EatIn */
/* setEatTongue(eater): keep the scale, change to EatIn */
void dEn_setEatTongue(GM_CTX, gptr self, gptr eater) {
    FN(0x80097C40);
    GM_CALLR(0x80097C64u, gm_u32(gm_u32(self + 0x60) + 0x98), 2, self, eater);
    double x = LF(self + 0xDC), y = LF(self + 0xE0), z = LF(self + 0xE4);
    SF(self + 0x370, x); SF(self + 0x374, y); SF(self + 0x378, z);
    GM_CALLR(0x80097C98u, gm_u32(gm_u32(self + 0x60) + 0xD4), 2, self, STATE_EAT_IN);
}
/* setEatTongueOff(eater): back to the state before */
void dEn_setEatTongueOff(GM_CTX, gptr self, gptr eater) {
    FN(0x80097CB0);
    GM_CALLR(0x80097CD4u, gm_u32(gm_u32(self + 0x60) + 0x9C), 2, self, eater);
    GM_CALLR(0x80097CE8u, gm_u32(gm_u32(self + 0x60) + 0xA0), 1, self);
    gptr old = GM_CALLR(0x80097CFCu, gm_u32(gm_u32(self + 0x394) + 0x2C), 1, self + 0x394);
    GM_CALLR(0x80097D14u, gm_u32(gm_u32(self + 0x60) + 0xD4), 2, self, old);
}
void dEn_iceballInvalid(GM_CTX, gptr other) {
    FN(0x80097EA0);
    gptr o = gm_u32(other + 4);
    gptr obj = gm_u32(SDA - 0x5920);
    GM_CALLR(0x80097EC8u, F_CVT_SND_POS, 2, f + 8, o + 0xAC);
    GM_CALLR(0x80097EDCu, F_SND_MAP, 4, obj, 617, f + 8, 0);
    SF(f + 16, LF(o + 0xAC)); SF(f + 20, LF(o + 0xB0)); SF(f + 24, R2F(28328));
    GM_CALLR(0x80097EFCu, F_ICE_MISS, 1, f + 16);
}
void dEn_fireballInvalid(GM_CTX, gptr other) {
    FN(0x80097E50);
    gptr o = gm_u32(other + 4), obj = gm_u32(SDA - 0x5920);
    GM_CALLR(0x80097E74u, F_CVT_SND_POS, 2, f + 8, o + 0xAC);
    GM_CALLR(0x80097E88u, F_SND_MAP, 4, obj, 614, f + 8, 0);
}
/* block_hit_init: hit from below - the effect, the sound, then fall off the screen */
void dEn_blockHitInit(GM_CTX, gptr self) {
    FN(0x80097F70);
    uint32_t dir = gm_u8(self + 0x458);
    gptr pn = GM_CALLR(0x80097FA4u, gm_u32(gm_u32(self + 0x60) + 0x6C), 1, self);
    uint32_t pl = gm_u8(pn);
    double x = LF(self + 0xAC), y = LF(self + 0xB0);
    SF(f + 16, x); SF(f + 20, y); SF(f + 24, x); SF(f + 28, y); SF(f + 32, R2F(28328));
    dEn_hitdamageEffect(GM_PASS, f + 24);
    gptr obj = gm_u32(SDA - 22820);
    GM_CALLR(0x80097FE4u, F_CVT_SND_POS, 2, f + 8, self + 0xAC);
    GM_CALLR(0x80097FF8u, F_START_SOUND, 4, obj, 379, f + 8, 0);
    const gptr t = 0x802F04A0u;                      /* the sDeathInfoData template */
    for (int i = 0; i < 8; i++) gm_set_u32(f + 40 + 4 * i, gm_u32(t + 4 * i));   /* (as the code builds it on the stack) */
    double sx = LF(ctx->r[2] - 28368 + 4 * dir);
    gm_set_u8(self + 0x432, 1);
    SF(self + 0x414, sx);
    SF(self + 0x418, LF(t + 4)); SF(self + 0x41C, LF(t + 8)); SF(self + 0x420, LF(t + 12));
    gm_set_u32(self + 0x424, gm_u32(t + 16)); gm_set_u32(self + 0x428, gm_u32(t + 20)); gm_set_u32(self + 0x42C, gm_u32(t + 24));
    gm_set_u8(self + 0x430, (uint8_t)dir); gm_set_u8(self + 0x431, (uint8_t)pl);
    gm_set_u8(f + 68, (uint8_t)dir); gm_set_u8(f + 69, (uint8_t)pl);
    SF(f + 40, sx);
}

/* ================================================================== constructor, destructors */
gptr dActor_ctor(GM_CTX, gptr self);
void dActor_setKind(GM_CTX, gptr self, uint32_t kind);
void fBase_opDelete(GM_CTX, gptr p);
#define F_STATEMGR_CT 0x8015FC90u        /* dStateMgr_c::dStateMgr_c */
#define F_ICE_CT      0x800B8440u
#define F_ICE_DT      0x800B84E0u
#define F_MULTISTATE_DT 0x80067270u      /* dActorMultiState_c::~dActorMultiState_c */
#define F_NEW         0x802B9210u
#define NULL_STATE    0x80377A04u
static void state_holder(GM_CTX, gptr self, gptr h) {      /* (dActorMultiState_c's two state managers) */
    gm_set_u32(h, 0x80311F28u); gm_set_u32(h + 4, 0x802FEAF8u); gm_set_u32(h + 8, 0x80311F58u);
    gm_set_u32(h + 12, 0x80311F70u); gm_set_u32(h + 16, self); gm_set_u32(h + 20, 0);
    GM_CALL(F_STATEMGR_CT, 4, h + 24, h + 4, h + 8, NULL_STATE);
    gm_set_u32(h, 0x80311EF8u);
}
gptr dEn_ctor(GM_CTX, gptr self) {
    FN(0x80094E80);
    dActor_ctor(GM_PASS, self);
    gm_set_u32(self + 0x394, 0x80311EB8u);
    gm_set_u32(self + 0x60, 0x8030EBB8u);
    state_holder(GM_PASS, self, self + 0x398);
    state_holder(GM_PASS, self, self + 0x3D4);
    double one = R2F(28340), zero = R2F(28344);
    gm_set_u32(self + 0x410, self + 0x398);
    gm_set_u32(self + 0x394, 0x80311E78u);
    gm_set_u32(self + 0x60, 0x80311BE0u);
    gm_set_u8(self + 0x432, 0); gm_set_u16(self + 0x438, 0);
    SF(f + 20, zero); SF(f + 24, zero); SF(f + 28, zero);   /* (the code builds the vectors in its frame) */
    SF(self + 0x440, zero); SF(self + 0x444, zero); SF(self + 0x448, zero);
    gm_set_u8(self + 0x45A, 0); gm_set_u8(self + 0x45C, 0); gm_set_u8(self + 0x45E, 0);
    SF(f + 8, one); SF(f + 12, one); SF(f + 16, one);
    SF(self + 0x464, one); SF(self + 0x468, one); SF(self + 0x46C, one); SF(self + 0x470, one);
    gm_set_u32(self + 0x478, 0); gm_set_u32(self + 0x47C, self);
    GM_CALLR(0x80094FD0u, F_ICE_CT, 2, self + 0x484, self);
    gm_set_u16(self + 0x500, 0); gm_set_u16(self + 0x502, 0);
    gm_set_u32(self + 0x510, 1);
    gm_set_u32(self + 0x514, 0x80311E60u); gm_set_u32(self + 0x518, 0); gm_set_u32(self + 0x51C, 0); gm_set_u32(self + 0x520, self);
    gptr p = GM_CALLR(0x80095000u, F_NEW, 1, 4);
    if (p) gm_set_u32(p, 0x80305C50u);           /* NonUniqueFumiCheck_c */
    gptr old = gm_u32(self + 0x51C);
    if (old) GM_CALLR(0x80095038u, gm_u32(gm_u32(old) + 8), 2, old, 1);
    double a = R2F(28336), m = R2F(28332);
    gm_set_u32(self + 0x51C, p);
    SF(self + 0x114, a); SF(self + 0xF4, zero); SF(self + 0xF8, m); SF(self + 0xFC, zero);
    SF(self + 0x4F0, a); SF(self + 0x4F4, m); SF(self + 0x4F8, m);
    dActor_setKind(GM_PASS, self, 3);
    gm_set_u8(self + 0x38E, 8);
    gm_set_u32(self + 0x4FC, 0);
    gm_set_u16(self + 0x504, 0); gm_set_u16(self + 0x506, 0); gm_set_u16(self + 0x508, 0); gm_set_u16(self + 0x50A, 0);
    return self;
}
/* dEnFumiProc_c's destructor (inlined in dEn_c's too) */
static void fumi_proc_dt(GM_CTX, gptr p) {
    gptr q = gm_u32(p + 8);
    gm_set_u32(p, 0x80311E60u);
    if (q) GM_CALL(gm_u32(gm_u32(q) + 8), 2, q, 1);
}
gptr dEn_dtor(GM_CTX, gptr self, int32_t flags) {
    FN(0x80095130);
    if (!self) return self;
    fumi_proc_dt(GM_PASS, self + 0x514);
    GM_CALLR(0x80095198u, F_ICE_DT, 2, self + 0x484, 0xFFFFFFFFu);
    GM_CALLR(0x800951A4u, F_MULTISTATE_DT, 2, self, 0);
    if (flags > 0) fBase_opDelete(GM_PASS, self);
    return self;
}

/* ================================================================== hle entry points
   In hle_funcs.txt: the 44 the test runs reach (directly, or through a decompiled caller).
   Written but not in hle_funcs.txt (no test run reaches them yet): fumidamageEffect,
   hipatkEffect, fumidamageSE, quakeAction, checkDispIn, Normal_VsYoshiHitCheck, getPl_UDflag,
   fn_80096460, MameFumiJumpSet, YoshiFumiJumpSet, YoshiFumiScoreSet, SpinFumiJumpSet,
   SpinFumiScoreSet, spinfumiSE, yoshifumiSE, mamefumiSE, fumistepSE, yoshifumistepSE,
   spinfumiEffect, EnLavaCheck, Area_X_check, Area_XY_check, setEatTongueOff, calcEatInScale,
   fireballInvalid, setDamage, block_hit_init, ~dEnFumiProc_c. */
#define A(i) GM_ARG(i)
GM_HLE(PClownCarAfterCreate) { dEn_postCreate(GM_PASS, A(0), A(1)); }                                       /* dEn_c::postCreate */
GM_HLE(afterExecute__5dEn_cFi) { dEn_postExecute(GM_PASS, A(0), A(1)); }                                    /* ::postExecute */
GM_HLE(beforeDraw__5dEn_cFv) { GM_RET(dActor_preDraw(GM_PASS, A(0)) != 0); }                               /* ::preDraw */
GM_HLE(fn_800954D0) { dEn_hitdamageEffect(GM_PASS, A(1)); }                                                 /* ::hitdamageEffect */
GM_HLE(spawnHitEffectAtPosition__5dEn_cF7Point2d) { dEn_hitdamageEffect(GM_PASS, A(1)); }                   /* ::fumidamageEffect */
GM_HLE(doSomethingWithHardHitAndSoftHitEffects__5dEn_cF7Point3d) { GM_RET(dEn_hipatkEffect(GM_PASS, A(0), A(1))); }   /* ::hipatkEffect */
GM_HLE(playEnemyDownSound2__5dEn_cFv) { dEn_fumidamageSE(GM_PASS, A(0)); }                                 /* ::fumidamageSE */
GM_HLE(add2ToYSpeed__5dEn_cFv) { SF(A(0) + 0xEC, frsp(LF(A(0) + 0xEC) + R2F(28324))); }                    /* ::quakeAction */
GM_HLE(doSpriteMovement) { dEn_posMove(GM_PASS, A(0)); }                                                    /* ::posMove */
GM_HLE(stuffRelatingToCollisions__5dEn_cFfff) { dEn_bound(GM_PASS, A(0), GM_FARG(0), GM_FARG(1), GM_FARG(2)); }   /* ::Bound */
GM_HLE(_vf218__5dEn_cFv) { GM_RET(dEn_checkDispIn(GM_PASS, A(0))); }                                        /* ::checkDispIn */
GM_HLE(playerCollision__5dEn_cFP13ActivePhysicsP13ActivePhysics) { dEn_vsHitCheck(GM_PASS, A(0), A(2)); }  /* ::Normal_VsPlHitCheck */
GM_HLE(yoshiCollision__5dEn_cFP13ActivePhysicsP13ActivePhysics) { dEn_vsHitCheck(GM_PASS, A(0), A(2)); }   /* ::Normal_VsYoshiHitCheck */
GM_HLE(preSpriteCollision__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(dEn_enDamageCheck(GM_PASS, A(0), A(1), A(2))); }      /* ::EnDamageCheck */
GM_HLE(prePlayerCollision__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(dEn_plDamageCheck(GM_PASS, A(0), A(1), A(2))); }      /* ::PlDamageCheck */
GM_HLE(preYoshiCollision__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(dEn_yoshiDamageCheck(GM_PASS, A(0), A(1), A(2))); }    /* ::YoshiDamageCheck */
GM_HLE(stageActorCollision__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(dEn_etcDamageCheck(GM_PASS, A(1), A(2))); }          /* ::EtcDamageCheck */
GM_HLE(dSprite_c__getXDirectionOfFurthestPlayerRelativeToVEC3) { GM_RET(dEn_getPlFlag(GM_PASS, A(1), 0)); }   /* ::getPl_LRflag */
GM_HLE(fn_800962A0) { GM_RET(dEn_getPlFlag(GM_PASS, A(1), 1)); }                                           /* ::getPl_UDflag */
GM_HLE(fn_80096300) { GM_RET(dEn_ceilCheck(GM_PASS, GM_FARG(0), A(0))); }                                  /* ::CeilCheck (static: y, cc) */
GM_HLE(fn_80096330) { GM_RET(dEn_carryCheck(GM_PASS, A(0), A(1))); }                                       /* ::carry_check */
GM_HLE(fn_800963B0) { GM_RET(dEn_checkWallAndBg(GM_PASS, A(0))); }                                         /* ::checkWallAndBg */
GM_HLE(fn_80096460) { FN(0x80096460); gptr p = A(0); if (p && (int32_t)A(1) > 0) GM_CALLR(0x80096488u, F_DELETE, 1, p); GM_RET(p); }    /* (a small deleting destructor) */
GM_HLE(usedForDeterminingStatePress_or_playerCollision) { GM_RET(dEn_enfumiCheck(GM_PASS, A(0), A(1), A(2), (int32_t)A(3))); }   /* ::Enfumi_check */
GM_HLE(addScoreWhenHit__5dEn_cFPv) { dEn_setFumiComboScore(GM_PASS, A(0), A(1)); }                          /* ::FumiScoreSet */
GM_HLE(bouncePlayerWhenJumpedOn__5dEn_cFPv) { dEn_playerFumiJump(GM_PASS, A(1), fumi_speed(GM_PASS)); }     /* ::FumiJumpSet */
GM_HLE(_vf254__5dEn_cFPv) { dEn_mameFumiJumpSet(GM_PASS, A(0), A(1)); }                                    /* ::MameFumiJumpSet */
GM_HLE(_vf258__5dEn_cFPv) { dEn_playerFumiJump(GM_PASS, A(1), fumi_speed(GM_PASS)); }                       /* ::YoshiFumiJumpSet */
GM_HLE(_vf25C__5dEn_cFPv) { GM_RET(GM_CALL(gm_u32(gm_u32(A(0) + 0x60) + 0x250), 2, A(0), A(1))); }          /* ::YoshiFumiScoreSet */
GM_HLE(fn_80096780) { GM_RET(GM_CALL(gm_u32(gm_u32(A(0) + 0x60) + 0x24C), 2, A(0), A(1))); }                /* ::SpinFumiJumpSet */
GM_HLE(fn_80096790) { GM_RET(GM_CALL(gm_u32(gm_u32(A(0) + 0x60) + 0x250), 2, A(0), A(1))); }                /* ::SpinFumiScoreSet */
GM_HLE(bouncePlayer__5dEn_cFPvf) { dEn_playerFumiJump(GM_PASS, A(1), GM_FARG(0)); }                        /* ::PlayerFumiJump */
GM_HLE(fn_800967F0) { dEn_setFumiComboScore(GM_PASS, A(0), A(1)); }                                        /* ::setFumiComboScore */
GM_HLE(_vf248__5dEn_cFi) { GM_RET((int32_t)A(1) >= (int32_t)gm_u32(0x802F0490u + 4 * gm_u32(A(0) + 0x510))); }   /* ::checkComboClap */
GM_HLE(_vf260__5dEn_cFPv) { dEn_comboSE(GM_PASS, A(0), A(1), 0); }                                         /* ::fumiSE */
GM_HLE(_vf268__5dEn_cFPv) { dEn_comboSE(GM_PASS, A(0), A(1), 1); }                                         /* ::spinfumiSE */
GM_HLE(_vf278__5dEn_cFPv) { dEn_comboSE(GM_PASS, A(0), A(1), 2); }                                         /* ::yoshifumiSE */
GM_HLE(playMameStepSound__5dEn_cFv) { dEn_centreSE(GM_PASS, A(0), 352); }                                  /* ::mamefumiSE */
GM_HLE(fn_80096CA0) { dEn_centreSE(GM_PASS, A(0), 351); }                                                  /* ::fumistepSE */
GM_HLE(fn_80096D00) { dEn_centreSE(GM_PASS, A(0), 353); }                                                  /* ::yoshifumistepSE */
GM_HLE(_vf264__5dEn_cFP13dStageActor_c) { dEn_fumiEffect(GM_PASS, A(1)); }                                 /* ::fumiEffect */
GM_HLE(spawnHitEffectAtPositionAgain__5dEn_cF7Point2d) { dEn_spinfumiEffect(GM_PASS, A(1)); }              /* ::spinfumiEffect */
GM_HLE(SomeStrangeModification) { GM_RET(dEn_bgCheck(GM_PASS, A(0))); }                                    /* ::EnBgCheck */
GM_HLE(fn_80096F60) { GM_RET(dEn_bgCheckFoot(GM_PASS, A(0))); }                                            /* ::EnBgCheckFoot */
GM_HLE(fn_80097050) { GM_RET(dEn_bgCheckWall(GM_PASS, A(0))); }                                            /* ::EnBgCheckWall */
GM_HLE(DoStuffAndMarkDead) { dEn_waterCheck(GM_PASS, A(0), A(1), GM_FARG(0)); }                           /* ::WaterCheck */
GM_HLE(fn_800971F0) { GM_RET(dEn_lineBoundaryCheck(GM_PASS, A(0), A(1))); }                                /* ::LineBoundaryCheck */
GM_HLE(checkLiquidImmersion__5dEn_cFP7Point2df) { GM_RET(dEn_waterLineProc(GM_PASS, A(0), A(1), GM_FARG(0))); }   /* ::WaterLineProc */
GM_HLE(_vfCC__5dEn_cFP7Point2df) { dEn_splash(GM_PASS, A(0), A(1), GM_FARG(0), 0); }                       /* ::yoganSplashEffect */
GM_HLE(_vfD0__5dEn_cFP7Point2df) { dEn_splash(GM_PASS, A(0), A(1), GM_FARG(0), 1); }                       /* ::poisonSplashEffect */
GM_HLE(fn_800975F0) { GM_RET(dEn_lavaCheck(GM_PASS, A(0), A(1))); }                                        /* ::EnLavaCheck */
GM_HLE(fn_800976B0) { GM_RET(dEn_waterCheckSpeed(GM_PASS, A(0), A(1))); }                                  /* ::EnWaterCheck */
GM_HLE(fn_80097700) { GM_RET(dEn_waterFlagCheck(GM_PASS, A(0), A(1))); }                                   /* ::EnWaterFlagCheck */
GM_HLE(_vf21C__5dEn_cFv) { dEn_setWaterSpeed(GM_PASS, A(0)); }                                             /* ::setWaterSpeed */
GM_HLE(fn_80097800) { GM_RET(dEn_areaCheck(GM_PASS, A(0), GM_FARG(0), 0, 0)); }                            /* ::Area_X_check */
GM_HLE(CheckIfPlayerBelow__5dEn_cFff) { GM_RET(dEn_areaCheck(GM_PASS, A(0), GM_FARG(0), GM_FARG(1), 1)); }  /* ::Area_XY_check */
GM_HLE(fn_800979B0) { GM_RET(dEn_playerCarryCheck(GM_PASS, A(0))); }                                       /* ::PlayerCarryCheck */
GM_HLE(fn_80097A20) { dEn_calcCarryPos(GM_PASS, A(0), A(1), A(2)); }                                       /* ::calcCarryPos */
GM_HLE(fn_80097B30) { GM_RET(dEn_turnangleCalc(GM_PASS, A(0), A(1), A(2))); }                              /* ::turnangle_calc */
GM_HLE(eatIn__5dEn_cFv) { dEn_setEatTongue(GM_PASS, A(0), A(1)); }                                      /* ::setEatTongue */
GM_HLE(disableEatIn__5dEn_cFv) { dEn_setEatTongueOff(GM_PASS, A(0), A(1)); }                               /* ::setEatTongueOff */
GM_HLE(fn_80097DF0) { FN(0x80097DF0); gptr me = A(0); GM_CALLR(0x80097E08u, F_ACTOR_EAT_IN, 2, me, A(1)); gm_set_u32(me + 0x478, 0); }    /* ::calcEatInScale */
GM_HLE(fn_80097E30) {                                                                                       /* ::setNicePoint_Death */
    uint32_t k = gm_u8(A(0) + 0x431);
    if (k > (uint32_t)(g_mod_on ? 7 : 3)) return;
    GM_RET(GM_CALL(F_NICE_POINT, 2, gm_u32(MULTI_MNG), (uint32_t)(int32_t)(int8_t)k));
}
GM_HLE(fn_80097E50) { dEn_fireballInvalid(GM_PASS, A(2)); }                                                /* ::fireballInvalid */
GM_HLE(fn_80097EA0) { dEn_iceballInvalid(GM_PASS, A(2)); }                                                 /* ::iceballInvalid */
GM_HLE(_vf220__5dEn_cFPv) { gptr a = A(1); GM_RET(GM_CALL(gm_u32(gm_u32(a + 0x60) + 0x3F4), 3, a, A(0), 0)); }   /* ::setDamage */
GM_HLE(fn_80097F40) {                                                                                       /* ::boyonInit */
    gptr me = A(0), o = gm_u32(me + 0x47C);
    SF(me + 0x464, LF(o + 0xDC)); SF(me + 0x468, LF(o + 0xE0)); SF(me + 0x46C, LF(o + 0xE4));
}
GM_HLE(_vf224__5dEn_cFv) {                                                                                  /* ::boyonBegin */
    ctx->f[1].d = ctx->ps1[1] = R2F(28132);
    GM_RET(GM_CALL(F_BOYO_BEGIN, 2, A(0) + 0x464, gm_u32(ctx->r[2] - 28136)));
}
GM_HLE(kill__5dEn_cFv) { dEn_blockHitInit(GM_PASS, A(0)); }                                                /* ::block_hit_init */
GM_HLE(__ct__5dEn_cFv) { GM_RET(dEn_ctor(GM_PASS, A(0))); }                                                 /* dEn_c::dEn_c */
GM_HLE(__dt__5dEn_cFv) { GM_RET(dEn_dtor(GM_PASS, A(0), (int32_t)A(1))); }                                 /* dEn_c::~dEn_c */
GM_HLE(fn_800950B0) {                                                                                       /* dEnFumiProc_c::~dEnFumiProc_c */
    FN(0x800950B0); gptr p = A(0);
    if (p) { fumi_proc_dt(GM_PASS, p); if ((int32_t)A(1) > 0) GM_CALLR(0x80095114u, F_DELETE, 1, p); }
    GM_RET(p);
}
