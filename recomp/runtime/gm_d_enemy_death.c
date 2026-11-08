/* gm_d_enemy_death.c - dEn_c's death and its sub-states: how an enemy dies (the hitCallback_*
 * reactions that fill mDeathInfo, the setDeathInfo_* helpers, setDeadMode), the Die* states
 * and their sounds (d_enemy_death.cpp), and the Ice / HitSpin / Eat* states and changeState
 * (d_enemy_state.cpp). Also dEnCombo_c, the combo scores (0x8009F5F0-0x8009F7C0).
 * Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_enemy_death.cpp, d_enemy_state.cpp) and
 * checked against the recompiled USA rev 2 code - where they differ the recompiled code wins.
 * The 8-player module doesn't replace any of these; it patches the player-count compares
 * (cancel-carry loops 4 -> 8, score checks 3 -> 7), which the code follows with g_mod_on as the
 * recompiled code does. hitCallback_Shell's "player < 4" is not patched - kept.
 * Not decompiled: the two static initialisers (fn_800A1E20, fn_800A82C0: they build the
 * StateIDs at boot) and the thirteen 3-instruction getters they call.
 *
 * dEn_c fields used here (see gm_d_enemy.c for more):
 *   +0x0E8 mSpeed  +0x0F4 mSpeedMax (+0x0F8 y)  +0x100 mAngle (x +0x100, y +0x102)
 *   +0x114 mAccelY  +0x11C mAccelF  +0x274 mBc.mFlags  +0x348 mDirection  +0x368 mEatenByID
 *   +0x36C mEatState  +0x38D mPlayerNo  +0x390 mNoRespawn  +0x391 mAmiLayer
 *   +0x394 mStateMgr  +0x414 mDeathInfo (32 bytes: xspeed, yspeed, max yspeed, yaccel, state,
 *   score, -1, dir, killedBy, isDead)  +0x45C mFootAttr3  +0x45D mInLiquid
 *   +0x459 mIceDeathDirection  +0x484 mIceMng (+0x490 mActive, +0x49C mDestroyMode,
 *   +0x4B4 mPlrNo)  +0x480 mBoyoMng.mDirection  +0x4FC mFlags  +0x510 mCombo (+0 mType)
 * vtable (+0x60): +0x098 removeCc, +0x09C reviveCc, +0x0AC calcEatInScale, +0x0D4 changeState,
 *   +0x104 hitCallback_Slip, +0x148 setDeathInfo_IceBreak, +0x14C _IceVanish,
 *   +0x158 setDeathSound_HipAttk, +0x15C _Fire, +0x160 _Slip, +0x164 _Spin,
 *   +0x178 initializeState_DieFall, +0x180 finalizeState_DieFall, +0x20C hipatkEffect,
 *   +0x22C createIceActor, +0x230 setIceAnm, +0x234 returnAnm_Ice, +0x238 returnState_Ice,
 *   +0x248 checkComboClap. daPlBase_c: +0x6C getPlrNo, +0x3E8 getStarCount,
 *   +0x134 mComboMultiplier, +0x1082 mPlComboCount, +0x2A78 mCarryActorID. */
#include "gm.h"
#include "gm_nv.h"
#include <math.h>

extern int g_mod_on;

#define SDA 0x8042F680u
#define SND_OBJ_EMY   (SDA - 22820)      /* dAudio::g_pSndObjEmy */
#define SND_OBJ_MAP   (SDA - 22816)      /* dAudio::g_pSndObjMap */
#define ACTOR_MNG     (SDA - 22848)      /* dActorMng_c::m_instance */
#define SCORE_MNG     (SDA - 22064)      /* dScoreMng_c::m_instance */
#define MULTI_MNG     (SDA - 22224)      /* dMultiMng_c::mspInstance */
#define ENEMY_MNG     (SDA - 22384)      /* dEnemyMng_c::m_instance */
#define SLIP_SE_INIT  (SDA - 22392)      /* (setDeathSound_Slip's table guard) */
#define SLIP_SE_TABLE 0x80357DA8u        /* cs_combo_se */
#define FALL_SPEED_X  0x8042C1B0u        /* l_base_fall_speed_x[2] */
#define EN_MUKI       0x8042C1A0u        /* l_EnMuki[2] (s8) */
#define BASE_ANGLE_Y  0x8042C1A4u        /* l_base_angleY[2] (s16) */
#define DEATH_TABLE   0x802F0560u        /* the constant parts of each sDeathInfoData literal */
#define STATE_ICE     0x80358004u        /* dEn_c::StateID_Ice */
#define STATE_EATNOW  0x803580C4u        /* dEn_c::StateID_EatNow */

#define F_TRG_DIR     0x80064A30u        /* dActor_c::getTrgToSrcDir_Main(f1, f2) */
#define F_SLIDE_SE    0x80065B80u        /* dActor_c::slideComboSE */
#define F_DELETE_ACTOR 0x80064D10u       /* dActor_c::deleteActor */
#define F_CENTER_POS  0x8006CED0u        /* dBaseActor_c::getCenterPos(out, this) */
#define F_CALC_SPEED_Y 0x8006CDE0u       /* dBaseActor_c::calcSpeedY */
#define F_CVT_SND_POS 0x8006A4B0u
#define F_SND_EMY     0x80197F00u        /* SndObjctCmnEmy::startSound */
#define F_SND_MAP     0x80198C30u        /* SndObjctCmnMap::startSound */
#define F_UP_COIN     0x80066630u        /* dActorMng_c::createUpCoin */
#define F_HITDAMAGE   0x800954D0u        /* dEn_c::hitdamageEffect */
#define F_POS_MOVE    0x800955F0u        /* dEn_c::posMove */
#define F_WATER_CHECK 0x80097170u        /* dEn_c::WaterCheck(pos, f1) */
#define F_FUMI_CNT    0x8009F5F0u        /* dEnCombo_c::calcPlFumiCnt */
#define F_STAR_CNT    0x8009F630u        /* dEnCombo_c::calcPlStarCnt */
#define F_COMBO_CNT   0x8009F690u        /* dEnCombo_c::calcPlComboCnt */
#define F_DAMAGE_SCORE 0x8009F6D0u       /* dEnCombo_c::getDamageScore */
#define F_QUAKE_SCORE 0x8009F6F0u        /* dEnCombo_c::getQuakeScore */
#define F_COMBO_SCORE 0x8009F710u        /* dEnCombo_c::getComboScore */
#define F_SCORE_SET   0x800E20A0u        /* dScoreMng_c::ScoreSet(actor, score, player, f1, f2) */
#define F_UNKNOWN_SCORE 0x800E23C0u      /* dScoreMng_c::UnKnownScoreSet(actor, score, f1, f2) */
#define F_GET_PLAYER  0x8005F900u        /* daPyMng_c::getPlayer */
#define F_SEARCH      0x80162D00u        /* fManager_c::searchBaseByID */
#define F_CANCEL_CARRY 0x8012E510u       /* dAcPy_c::cancelCarry */
#define F_VS_HIT_EFF  0x800943D0u        /* EffectManager_c::SetVsHitEffect */
#define F_BREAKDOWN_SE 0x800A7C60u       /* dEnemyMng_c::breakdownSE */
#define F_QUAKE_COMBO 0x800A7C00u        /* dEnemyMng_c::incQuakeComboCount */
#define F_RND_INT     0x800B2EE0u        /* dGameCom::rndInt */
#define F_CREATE_EFFECT 0x8016C890u      /* mEf::createEffect */
#define F_CLAP_SE     0x800CE8C0u        /* dMultiMng_c::setClapSE */
#define F_ICE_INIT    0x800B8550u        /* dIceMng_c::initialize */
#define F_ICE_CREATE  0x800B8700u        /* dIceMng_c::createIce */
#define F_ICE_REMOVE  0x800B8850u        /* dIceMng_c::removeIce */
#define F_ICE_INSTANT 0x800B8A20u        /* dIceMng_c::checkInstantBreak */
#define F_ICE_BREAK_EFF 0x800B8BB0u      /* dIceMng_c::breakEffect */
#define F_ICE_PROC    0x800B8EE0u        /* dIceMng_c::manageProc */
#define F_ICE_INFO_DT 0x80024C20u        /* dIceInfo::~dIceInfo */
#define F_DESTROY_ARR 0x802DCA98u        /* __destroy_arr */
#define F_KILL_ICE    0x800A8170u        /* dEn_c::killIce */
#define F_SMOKE       0x800A0DC0u        /* dEn_c::setDeathInfo_Smoke */
#define F_YOSHI_FUMI  0x800A0FB0u        /* dEn_c::setDeathInfo_YoshiFumi */
#define F_SPIN_FUMI   0x800A1190u        /* dEn_c::setDeathInfo_SpinFumi */

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f      /* (gm.h: the PowerPC function's frame and prologue;
                                                               "FNADDR" marks a line passing the address on, for tools/gm_prologues.py) */
#define VT(o, off) gm_u32(gm_u32((o) + 0x60) + (off))
static uint32_t vcall1(GM_CTX, gptr o, uint32_t off) { return GM_CALL(VT(o, off), 1, o); }
static uint32_t vcall2(GM_CTX, gptr o, uint32_t off, uint32_t a) { return GM_CALL(VT(o, off), 2, o, a); }
/* a virtual call on an object whose vtable is its first word (the state manager, state IDs) */
static uint32_t vcall0(GM_CTX, gptr o, uint32_t off, int n, uint32_t a) { return GM_CALL(gm_u32(gm_u32(o) + off), n, o, a); }

static double cen_x(GM_CTX, gptr a) { return frsp(LF(a + 0xAC) + LF(a + 0xD0)); }
static double fall_x(GM_CTX, uint32_t dir) { return LF(FALL_SPEED_X + 4 * dir); }
static uint32_t plr_no(GM_CTX, gptr a) { return gm_u8(vcall1(GM_PASS, a, 0x6C)); }
/* getTrgToSrcDir_Main(this centre x, other centre x): a static in effect - r3 is left as is */
static uint32_t trg_dir(GM_CTX, gptr self, gptr other) {
    ctx->f[1].d = ctx->ps1[1] = cen_x(GM_PASS, self);
    ctx->f[2].d = ctx->ps1[2] = cen_x(GM_PASS, other);
    return GM_CALL(F_TRG_DIR, 1, self);
}
static void snd_emy(GM_CTX, gptr self, uint32_t se, gptr tmp) {
    gptr obj = gm_u32(SND_OBJ_EMY);
    GM_CALL(F_CVT_SND_POS, 2, tmp, self + 0xAC);
    GM_CALL(F_SND_EMY, 4, obj, se, tmp, 0);
}
/* a collision's position as a mVec2_c at v2 (if v2) and a mVec3_c at v3, z = 5500 */
static void coll_pos(GM_CTX, gptr cc, gptr v2, gptr v3) {
    double x = LF(cc + 0x90), y = LF(cc + 0x94);
    if (v2) { SF(v2, x); SF(v2 + 4, y); }
    SF(v3, x); SF(v3 + 4, y); SF(v3 + 8, R2F(28064));
}
static uint32_t short_combo(GM_CTX, gptr self) { return gm_u32(self + 0x510) == 2; }

/* mDeathInfo = (sDeathInfoData) { ... }: the literal is built in a stack temporary t from its
   constant part in DEATH_TABLE (32 bytes each), then copied to the object, which also gets
   isDead = 1. m says which parts are not the table's. */
enum { DI_XS = 1, DI_YS = 2, DI_STATE = 4, DI_SCORE = 8, DI_DIR = 16, DI_PLR = 32 };
static void death_info(GM_CTX, gptr self, gptr t, int k, unsigned m, double xs, double ys, uint32_t state,
                       uint32_t score, uint32_t dir, uint32_t plr) {
    gptr tbl = DEATH_TABLE + 32 * k;
    for (int i = 0; i < 8; i++) gm_set_u32(t + 4 * i, gm_u32(tbl + 4 * i));
    if (m & DI_XS) SF(t, xs);
    if (m & DI_YS) SF(t + 4, ys);
    if (m & DI_STATE) gm_set_u32(t + 16, state);
    if (m & DI_SCORE) gm_set_u32(t + 20, score);
    if (m & DI_DIR) gm_set_u8(t + 28, dir);
    if (m & DI_PLR) gm_set_u8(t + 29, plr);
    for (int i = 0; i < 4; i++) SF(self + 0x414 + 4 * i, LF(t + 4 * i));
    for (int i = 4; i < 7; i++) gm_set_u32(self + 0x414 + 4 * i, gm_u32(t + 4 * i));
    gm_set_u8(self + 0x430, gm_u8(t + 28)); gm_set_u8(self + 0x431, gm_u8(t + 29));
    gm_set_u8(self + 0x432, 1);
}
enum { K_STAR, K_CANNON, K_SLIP, K_WIRENET, K_LARGE, K_SPIN, K_HIPATTK, K_YOSHI_BULLET, K_YOSHI_FIRE,
       K_SHELL, K_FIRE, K_QUAKE, K_SMOKE, K_FUMI, K_YOSHI_FUMI, K_OTHER, K_SPIN_FUMI, K_ICE_BREAK,
       K_ICE_VANISH };

/* ================================================================== hitCallback_* */
/* Star / Cannon / Slip: the hit effect at the collision, the combo sound and score, fall */
static uint32_t hit_combo(GM_CTX, gptr self, gptr cc1, gptr cc2, int kind) {
    static const uint32_t fn[] = { 0x8009F840u, 0x8009F9D0u, 0x8009FB50u };   /* FNADDR */
    FN(fn[kind]);
    gptr pl = gm_u32(cc2 + 4);
    uint32_t dir = trg_dir(GM_PASS, self, pl) & 0xFF;
    uint32_t plr = plr_no(GM_PASS, pl);
    coll_pos(GM_PASS, cc1, f + 8, f + 16);
    GM_CALL(F_HITDAMAGE, 2, self, f + 16);
    uint32_t cnt;
    if (kind == 0) {
        uint32_t sh = short_combo(GM_PASS, self);
        uint32_t n = (uint32_t)(int32_t)(int8_t)vcall1(GM_PASS, pl, 0x3E8);
        GM_CALL(F_SLIDE_SE, 3, pl, n, sh);
        cnt = GM_CALL(F_STAR_CNT, 1, pl);
    } else if (kind == 1) {
        uint32_t sh = short_combo(GM_PASS, self);
        GM_CALL(F_SLIDE_SE, 3, pl, (uint32_t)(int32_t)gm_s8(pl + 0x1082), sh);
        cnt = GM_CALL(F_COMBO_CNT, 1, pl);
    } else {
        vcall2(GM_PASS, self, 0x160, pl);                                 /* setDeathSound_Slip */
        cnt = GM_CALL(F_COMBO_CNT, 1, pl);
    }
    uint32_t score = GM_CALL(F_COMBO_SCORE, 2, self + 0x510, cnt);
    death_info(GM_PASS, self, f + 32, kind, DI_XS | DI_SCORE | DI_DIR | DI_PLR, fall_x(GM_PASS, dir), 0, 0, score, dir, plr);
    return 1;
}
/* WireNet: knocked off a fence */
static uint32_t hit_wirenet(GM_CTX, gptr self, gptr cc2) {
    FN(0x8009FCE0);
    gptr pl = gm_u32(cc2 + 4);
    uint32_t dir = trg_dir(GM_PASS, self, pl) & 0xFF;
    uint32_t plr = plr_no(GM_PASS, pl);
    snd_emy(GM_PASS, self, 379, f + 8);                                   /* SE_EMY_DOWN */
    double xs = frsp(R2F(28060) * fall_x(GM_PASS, dir));
    for (int i = 0; i < 8; i++) gm_set_u32(f + 16 + 4 * i, gm_u32(DEATH_TABLE + 32 * K_WIRENET + 4 * i));
    SF(f + 16, xs);
    uint32_t score = GM_CALLR(0x8009FDC8u, F_DAMAGE_SCORE, 1, self + 0x510);
    death_info(GM_PASS, self, f + 16, K_WIRENET, DI_XS | DI_SCORE | DI_DIR | DI_PLR, xs, 0, 0, score, dir, plr);
    return 1;
}
/* int -> double through the stack, as the code converts (the magic 0x4330... double) */
static double i2d(GM_CTX, gptr tmp, int32_t v) {
    gm_set_u32(tmp, 0x43300000u); gm_set_u32(tmp + 4, (uint32_t)v ^ 0x80000000u);
    return frsp(((double)v + 4503601774854144.0) - 4503601774854144.0);
}
/* Large: hit by a big thing - thrown along with the player's speed */
static uint32_t hit_large(GM_CTX, gptr self, gptr cc2) {
    FN(0x8009FE40);
    gptr pl = gm_u32(cc2 + 4);
    uint32_t dir = trg_dir(GM_PASS, self, pl) & 0xFF;
    gptr pn = vcall1(GM_PASS, pl, 0x6C);
    double d = frsp(LF(pl + 0xE8) - LF(self + 0xE8));
    double xs = i2d(GM_PASS, f + 40, gm_s8(EN_MUKI + dir));
    uint32_t plr = gm_u8(pn);
    xs = frsp(xs + d);
    if (xs > R2F(28056)) xs = R2F(28056);
    else if (xs < R2F(28052)) xs = R2F(28052);
    for (int i = 0; i < 8; i++) gm_set_u32(f + 8 + 4 * i, gm_u32(DEATH_TABLE + 32 * K_LARGE + 4 * i));
    SF(f + 8, xs);
    uint32_t score = GM_CALLR(0x8009FF48u, F_DAMAGE_SCORE, 1, self + 0x510);
    death_info(GM_PASS, self, f + 8, K_LARGE, DI_XS | DI_SCORE | DI_DIR | DI_PLR, xs, 0, 0, score, dir, plr);
    return 1;
}
/* Spin / HipAttk: the hard / soft hit effect at the player, the stomp combo score */
static uint32_t hit_stomp(GM_CTX, gptr self, gptr cc2, int hip) {
    FN(hip ? 0x800A0150u : 0x8009FFD0u);
    gptr pl = gm_u32(cc2 + 4);
    uint32_t dir = trg_dir(GM_PASS, self, pl) & 0xFF;
    uint32_t plr = plr_no(GM_PASS, pl);
    vcall1(GM_PASS, self, hip ? 0x158 : 0x164);                          /* setDeathSound_HipAttk / _Spin */
    double x = LF(pl + 0xAC), y = LF(pl + 0xB0);
    SF(f + 16, x); SF(f + 20, y); SF(f + 24, R2F(28064)); SF(f + 8, x); SF(f + 12, y);
    vcall2(GM_PASS, self, 0x20C, f + 16);                                 /* hipatkEffect */
    uint32_t cnt = GM_CALL(F_FUMI_CNT, 1, pl);
    uint32_t score = GM_CALL(F_COMBO_SCORE, 2, self + 0x510, cnt);
    death_info(GM_PASS, self, f + 32, hip ? K_HIPATTK : K_SPIN, DI_XS | DI_SCORE | DI_DIR | DI_PLR,
               fall_x(GM_PASS, dir), 0, 0, score, dir, plr);
    return 1;
}
/* YoshiHipAttk: the score now, then the Yoshi-stomp death */
static uint32_t hit_yoshi_hipattk(GM_CTX, gptr self, gptr cc2) {
    FN(0x800A02D0);
    gptr pl = gm_u32(cc2 + 4);
    trg_dir(GM_PASS, self, pl);                                           /* (unused) */
    uint32_t plr = plr_no(GM_PASS, pl);
    uint32_t cnt = GM_CALLR(0x800A032Cu, F_FUMI_CNT, 1, pl);
    int32_t score = (int32_t)GM_CALLR(0x800A0338u, F_COMBO_SCORE, 2, self + 0x510, cnt);
    if (score >= 0 && plr < (g_mod_on ? 8u : 4u)) {
        ctx->f[1].d = ctx->ps1[1] = R2F(25592); ctx->f[2].d = ctx->ps1[2] = R2F(25588);
        GM_CALLR(0x800A0364u, F_SCORE_SET, 4, gm_u32(SCORE_MNG), self, (uint32_t)score, plr);
    }
    snd_emy(GM_PASS, self, 404, f + 8);                                   /* SE_EMY_YOSHI_HPDP */
    GM_CALLR(0x800A0394u, F_YOSHI_FUMI, 2, self, pl);
    return 1;
}
/* YoshiBullet: a coin pops out */
static uint32_t hit_yoshi_bullet(GM_CTX, gptr self, gptr cc1, gptr cc2) {
    FN(0x800A03C0);
    gptr pl = gm_u32(cc2 + 4);
    uint32_t dir = trg_dir(GM_PASS, self, pl) & 0xFF;
    uint32_t plr = plr_no(GM_PASS, pl);
    vcall1(GM_PASS, self, 0x15C);                                         /* setDeathSound_Fire */
    coll_pos(GM_PASS, cc1, 0, f + 20);
    GM_CALLR(0x800A0458u, F_HITDAMAGE, 2, self, f + 20);
    GM_CALLR(0x800A0464u, F_CENTER_POS, 2, f + 8, self);
    GM_CALLR(0x800A047Cu, F_UP_COIN, 5, gm_u32(ACTOR_MNG), f + 8, dir, 1, 0);
    double xs = fall_x(GM_PASS, dir);
    for (int i = 0; i < 8; i++) gm_set_u32(f + 32 + 4 * i, gm_u32(DEATH_TABLE + 32 * K_YOSHI_BULLET + 4 * i));
    SF(f + 32, xs);
    uint32_t score = GM_CALLR(0x800A04DCu, F_DAMAGE_SCORE, 1, self + 0x510);
    death_info(GM_PASS, self, f + 32, K_YOSHI_BULLET, DI_XS | DI_SCORE | DI_DIR | DI_PLR, xs, 0, 0, score, dir, plr);
    return 1;
}
/* the player's own combo counter (Yoshi fire, shells): sound, then count up to 8 */
static uint32_t multiplier_score(GM_CTX, gptr self, gptr pl) {
    GM_CALL(F_SLIDE_SE, 3, pl, gm_u32(pl + 0x134), short_combo(GM_PASS, self));
    int32_t n = (int32_t)gm_u32(pl + 0x134) + 1;
    gm_set_u32(pl + 0x134, (uint32_t)n);
    if (n >= 8) gm_set_u32(pl + 0x134, 8);
    return GM_CALL(F_COMBO_SCORE, 2, self + 0x510, gm_u32(pl + 0x134));
}
/* YoshiFire: direction from the fire's speed, a coin, the player's combo */
static uint32_t hit_yoshi_fire(GM_CTX, gptr self, gptr cc1, gptr cc2) {
    FN(0x800A0550);
    gptr pl = gm_u32(cc2 + 4);
    uint32_t dir = !(LF(pl + 0xE8) >= R2F(28040));
    GM_CALLR(0x800A059Cu, F_CENTER_POS, 2, f + 28, self);
    GM_CALLR(0x800A05B4u, F_UP_COIN, 5, gm_u32(ACTOR_MNG), f + 28, dir, 1, 0);
    uint32_t plr = plr_no(GM_PASS, pl);
    coll_pos(GM_PASS, cc1, f + 8, f + 16);
    GM_CALLR(0x800A05F8u, F_HITDAMAGE, 2, self, f + 16);
    uint32_t score = multiplier_score(GM_PASS, self, pl);
    death_info(GM_PASS, self, f + 40, K_YOSHI_FIRE, DI_XS | DI_SCORE | DI_DIR | DI_PLR, fall_x(GM_PASS, dir), 0, 0, score, dir, plr);
    return 1;
}
/* Shell: a player's shell counts the combo; anything else just the down sound */
static uint32_t hit_shell(GM_CTX, gptr self, gptr cc1, gptr cc2) {
    FN(0x800A0700);
    gptr pl = gm_u32(cc2 + 4);
    uint32_t dir = trg_dir(GM_PASS, self, pl) & 0xFF;
    uint32_t plr = plr_no(GM_PASS, pl);
    coll_pos(GM_PASS, cc1, f + 16, f + 24);
    GM_CALLR(0x800A0784u, F_HITDAMAGE, 2, self, f + 24);
    uint32_t score = 0xFFFFFFFFu;
    if (plr <= 3) score = multiplier_score(GM_PASS, self, pl);
    else snd_emy(GM_PASS, self, 379, f + 8);
    death_info(GM_PASS, self, f + 40, K_SHELL, DI_XS | DI_SCORE | DI_DIR | DI_PLR, fall_x(GM_PASS, dir), 0, 0, score, dir, plr);
    return 1;
}
/* Fire: direction from the fireball's speed, a coin */
static uint32_t hit_fire(GM_CTX, gptr self, gptr cc2) {
    FN(0x800A08D0);
    gptr pl = gm_u32(cc2 + 4);
    uint32_t dir = !(LF(pl + 0xE8) >= R2F(28040));
    uint32_t plr = plr_no(GM_PASS, pl);
    vcall1(GM_PASS, self, 0x15C);                                         /* setDeathSound_Fire */
    GM_CALLR(0x800A0948u, F_CENTER_POS, 2, f + 8, self);
    GM_CALLR(0x800A0960u, F_UP_COIN, 5, gm_u32(ACTOR_MNG), f + 8, dir, 1, 0);
    double xs = fall_x(GM_PASS, dir);
    for (int i = 0; i < 8; i++) gm_set_u32(f + 24 + 4 * i, gm_u32(DEATH_TABLE + 32 * K_FIRE + 4 * i));
    SF(f + 24, xs);
    uint32_t score = GM_CALLR(0x800A09C0u, F_DAMAGE_SCORE, 1, self + 0x510);
    death_info(GM_PASS, self, f + 24, K_FIRE, DI_XS | DI_SCORE | DI_DIR | DI_PLR, xs, 0, 0, score, dir, plr);
    return 1;
}
/* the players carrying this enemy let go (the first one found) */
static void cancel_carry(GM_CTX, gptr self) {
    int n = g_mod_on ? 8 : 4;
    for (int i = 0;;) {
        gptr p = GM_CALL(F_GET_PLAYER, 1, (uint32_t)i);
        if (p && GM_CALL(F_SEARCH, 1, gm_u32(p + 0x2A78)) == self) { GM_CALL(F_CANCEL_CARRY, 2, p, self); return; }
        if (++i >= n) return;
        GM_LOOP();
    }
}
/* Ice: frozen (unless already) - the state machine's Ice sub-state */
static uint32_t hit_ice(GM_CTX, gptr self, gptr cc2) {
    FN(0x800A0A30);
    if (gm_u32(self + 0x490) == 0) {
        gptr pl = gm_u32(cc2 + 4);
        gm_set_u8(self + 0x480, (LF(pl + 0xE8) >= R2F(28040)) ? 0 : 1);
        cancel_carry(GM_PASS, self);
        gm_set_u32(self + 0x4B4, (uint32_t)(int32_t)(int8_t)plr_no(GM_PASS, pl));
        vcall0(GM_PASS, self + 0x394, 0x30, 2, STATE_ICE);              /* mStateMgr.changeToSubState */
    }
    return 1;
}

/* ================================================================== setDeadMode, setDeathInfo_* */
/* setDeadMode(actor, i): killed by something that isn't a collision (1: in smoke) */
static void set_dead_mode(GM_CTX, gptr self, gptr actor, uint32_t i) {
    FN(0x800A0B30);
    if (gm_u8(self + 0x432) || gm_u8(self + 0x390)) return;
    gptr mgr = self + 0x394;
    gptr id = vcall0(GM_PASS, mgr, 0x28, 1, 0);                           /* getStateID */
    if (vcall0(GM_PASS, id, 0x14, 2, STATE_ICE) && gm_u32(self + 0x49C) != 0) return;
    vcall1(GM_PASS, self, 0x98);                                          /* removeCc */
    if (i == 1) { GM_CALLR(0x800A0BE8u, F_SMOKE, 2, self, actor); return; }
    GM_CALLR(0x800A0BFCu, F_SPIN_FUMI, 3, self, actor, 0);
    GM_CALLR(0x800A0C08u, F_CENTER_POS, 2, f + 16, self);
    SF(f + 16, frsp(LF(f + 16) + LF(ctx->r[2] - 28032 + 4 * gm_u8(self + 0x430))));   /* cs_effect_offset_x */
    GM_CALLR(0x800A0C30u, F_HITDAMAGE, 2, self, f + 16);
    snd_emy(GM_PASS, self, 379, f + 8);
}
/* setDeathInfo_Quake(i): a POW block / quake - up, no sideways speed, the quake combo */
static void death_quake(GM_CTX, gptr self, uint32_t i) {
    FN(0x800A0C70);
    double ys = R2F(28024);
    SF(f + 12, frsp(LF(self + 0xB0) + LF(self + 0xD4)));
    SF(f + 8, cen_x(GM_PASS, self));
    SF(f + 16, R2F(28064));
    if (i == 0) { GM_CALLR(0x800A0CC8u, F_VS_HIT_EFF, 1, f + 8); ys = R2F(28024); }
    else if (i == 1) { GM_CALLR(0x800A0CE0u, F_VS_HIT_EFF, 1, f + 8); ys = R2F(28020); }
    gptr em = gm_u32(ENEMY_MNG);
    GM_CALLR(0x800A0CF4u, F_BREAKDOWN_SE, 3, em, gm_u32(em + 340), self + 0xAC);
    GM_CALLR(0x800A0D00u, F_QUAKE_COMBO, 2, gm_u32(ENEMY_MNG), 0);
    uint32_t score = GM_CALLR(0x800A0D10u, F_QUAKE_SCORE, 2, self + 0x510, gm_u32(gm_u32(ENEMY_MNG) + 340));
    death_info(GM_PASS, self, f + 24, K_QUAKE, DI_YS | DI_SCORE | DI_DIR, 0, ys, 0, score, gm_u8(self + 0x348), 0);
}
/* setDeathInfo_Smoke(actor) / _Other(actor): vanish (the player from the actor, if any) */
static void death_smoke_other(GM_CTX, gptr self, gptr actor, int other) {
    FN(other ? 0x800A10B0u : 0x800A0DC0u);
    uint32_t plr = other ? 0xFF : gm_u8(self + 0x38D);
    if (actor) plr = plr_no(GM_PASS, actor);
    death_info(GM_PASS, self, f + 8, other ? K_OTHER : K_SMOKE, DI_PLR, 0, 0, 0, 0, 0, plr);
}
/* setDeathInfo_Fumi(actor, speed, state, _) */
static void death_fumi(GM_CTX, gptr self, gptr actor, gptr speed, uint32_t state) {
    FN(0x800A0EA0);
    uint32_t dir = trg_dir(GM_PASS, self, actor);
    uint32_t plr = plr_no(GM_PASS, actor);
    death_info(GM_PASS, self, f + 8, K_FUMI, DI_XS | DI_YS | DI_STATE | DI_DIR | DI_PLR, LF(speed), LF(speed + 4), state, 0, dir, plr);
}
/* setDeathInfo_YoshiFumi(actor) / _SpinFumi(actor, _) */
static void death_dir_plr(GM_CTX, gptr self, gptr actor, int spin) {
    FN(spin ? 0x800A1190u : 0x800A0FB0u);
    uint32_t dir = trg_dir(GM_PASS, self, actor);
    if (spin) dir &= 0xFF;
    uint32_t plr = plr_no(GM_PASS, actor);
    if (spin) death_info(GM_PASS, self, f + 8, K_SPIN_FUMI, DI_XS | DI_DIR | DI_PLR, fall_x(GM_PASS, dir), 0, 0, 0, dir, plr);
    else death_info(GM_PASS, self, f + 8, K_YOSHI_FUMI, DI_DIR | DI_PLR, 0, 0, 0, 0, dir, plr);
}
/* setDeathInfo_IceBreak / _IceVanish: the ice is gone; break: fall, vanish: a coin */
static void death_ice(GM_CTX, gptr self, int vanish) {
    FN(vanish ? 0x800A1370u : 0x800A12A0u);
    GM_CALL(F_KILL_ICE, 1, self);
    if (!vanish) {
        uint32_t dir = gm_u8(self + 0x459);
        death_info(GM_PASS, self, f + 8, K_ICE_BREAK, DI_XS | DI_DIR | DI_PLR, fall_x(GM_PASS, dir), 0, 0, 0, dir, gm_u8(self + 0x38D));
        return;
    }
    uint32_t r = GM_CALL(F_RND_INT, 1, 2);
    GM_CALL(F_CENTER_POS, 2, f + 8, self);
    GM_CALL(F_UP_COIN, 5, gm_u32(ACTOR_MNG), f + 8, r & 0xFF, 1, 0);
    death_info(GM_PASS, self, f + 24, K_ICE_VANISH, DI_DIR | DI_PLR, 0, 0, 0, 0, gm_u8(self + 0x459), gm_u8(self + 0x38D));
}

/* ================================================================== the Die* states */
/* the score a death gives, now (to the player, or "unknown" for a quake) */
static void death_score(GM_CTX, gptr self) {
    int32_t score = (int32_t)gm_u32(self + 0x428);
    uint32_t plr = (uint32_t)(int32_t)gm_s8(self + 0x431);
    if (score < 0) return;
    if (plr <= (g_mod_on ? 7u : 3u)) {
        ctx->f[1].d = ctx->ps1[1] = R2F(25592); ctx->f[2].d = ctx->ps1[2] = R2F(25588);
        GM_CALL(F_SCORE_SET, 4, gm_u32(SCORE_MNG), self, (uint32_t)score, plr);
    } else if (plr == 50) {                                               /* dDeathInfo_c::smc_UNKNOWN_HIT */
        ctx->f[1].d = ctx->ps1[1] = R2F(28040); ctx->f[2].d = ctx->ps1[2] = R2F(28016);
        GM_CALL(F_UNKNOWN_SCORE, 3, gm_u32(SCORE_MNG), self, (uint32_t)score);
    }
}
/* initializeState_DieFumi / _DieFall: the speeds from mDeathInfo, face the way it looks */
static void die_fall_begin(GM_CTX, gptr self, int fall) {
    FN(fall ? 0x800A16A0u : 0x800A1470u);
    cancel_carry(GM_PASS, self);
    vcall1(GM_PASS, self, 0x98);                                          /* removeCc */
    int16_t ay = gm_s16(self + 0x102);
    double z = R2F(28040);
    gm_set_u32(self + 0x274, 0);
    SF(self + 0xE8, LF(self + 0x414)); SF(self + 0xEC, LF(self + 0x418)); SF(self + 0xF0, z);
    SF(self + 0xF4, z); SF(self + 0xF8, LF(self + 0x41C)); SF(self + 0xFC, z);
    gm_set_u8(self + 0x45C, 0);
    gm_set_u8(self + 0x459, gm_u8(self + 0x430));
    SF(self + 0x11C, z); SF(self + 0x114, LF(self + 0x420));
    gm_set_u8(self + 0x348, ay < 0 ? 1 : 0);
    gm_set_u16(self + 0x102, gm_u16(BASE_ANGLE_Y + 2 * gm_u8(self + 0x348)));
    death_score(GM_PASS, self);
    SF(self + 0xB4, gm_u8(self + 0x391) == 1 ? R2F(28012) : R2F(28008));
}
/* an angle step slowed in liquids (smc_WATER_ROLL_DEC_RATE), through the stack as the code does */
static int32_t water_roll(GM_CTX, gptr self, gptr f, int32_t d) {
    if (!gm_u8(self + 0x45D)) return d;
    double x = i2d(GM_PASS, f + 8, d);
    uint64_t b = fctiw_bits(frsp(x * R2F(28348)), 1);
    st64(base, f + 16, b);
    return (int32_t)gm_u32(f + 20);
}
static void die_move(GM_CTX, gptr self) {
    GM_CALL(F_CALC_SPEED_Y, 1, self);
    GM_CALL(F_POS_MOVE, 1, self);
    ctx->f[1].d = ctx->ps1[1] = R2F(28004);
    GM_CALL(F_WATER_CHECK, 2, self, self + 0xAC);
}
static void die_fumi_execute(GM_CTX, gptr self) {
    FN(0x800A1600);
    int32_t d = water_roll(GM_PASS, self, f, 768);
    gm_set_u16(self + 0x100, (uint16_t)(gm_s16(self + 0x100) + d));
    die_move(GM_PASS, self);
}
static void die_fall_execute(GM_CTX, gptr self) {
    FN(0x800A1830);
    uint32_t idir = gm_u8(self + 0x459);
    int16_t spin = gm_s16(ctx->r[2] - 28000 + 2 * idir);                 /* cs_spin_speed */
    int32_t dx, dy;
    if (gm_u8(self + 0x348) == idir) { dx = 3072; dy = (int16_t)-spin; }
    else { dx = -3072; dy = spin; }
    dx = water_roll(GM_PASS, self, f, dx);
    gm_set_u16(self + 0x100, (uint16_t)(gm_s16(self + 0x100) + dx));
    gm_set_u16(self + 0x102, (uint16_t)(gm_s16(self + 0x102) + dy));
    die_move(GM_PASS, self);
}
static void die_bigfall_execute(GM_CTX, gptr self) {
    FN(0x800A1930);
    gm_set_u16(self + 0x100, (uint16_t)(gm_s16(self + 0x100) + 3072));
    die_move(GM_PASS, self);
}
/* initializeState_DieSmoke / _DieYoshiFumi: an effect at the centre, no more collisions */
static void die_effect_begin(GM_CTX, gptr self, int yoshi) {
    FN(yoshi ? 0x800A1AC0u : 0x800A1980u);
    GM_CALL(F_CENTER_POS, 2, f + 8, self);
    GM_CALL(F_CREATE_EFFECT, 5, yoshi ? 0x80313498u : 0x80313488u, 0, f + 8, 0, 0);   /* "Wm_mr_yoshistep" / "Wm_en_burst_m" */
    vcall1(GM_PASS, self, 0x98);
}
static void die_ice_vanish_begin(GM_CTX, gptr self) {
    FN(0x800A1A10);
    vcall1(GM_PASS, self, 0x98);
    death_score(GM_PASS, self);
}

/* ================================================================== death sounds */
static void sound_fire(GM_CTX, gptr self) { FN(0x800A1BB0); snd_emy(GM_PASS, self, 379, f + 8); }
/* HipAttk / Spin: hard or soft */
static void sound_hpdp(GM_CTX, gptr self, uint32_t addr) {
    FN(addr);
    if (gm_u32(self + 0x4FC) & 2) snd_emy(GM_PASS, self, 396, f + 16);   /* SE_EMY_DOWN_HPDP_H */
    else snd_emy(GM_PASS, self, 395, f + 8);                              /* SE_EMY_DOWN_HPDP_S */
}
/* Slip: the combo sound for the player's slide count, the clap from 8 */
static void sound_slip(GM_CTX, gptr self, gptr pl) {
    FN(0x800A1C80);
    if (!gm_s8(SLIP_SE_INIT)) {
        static const uint32_t t[9] = { 380, 381, 382, 383, 384, 385, 386, 386, 386 };
        for (int i = 0; i < 9; i++) gm_set_u32(SLIP_SE_TABLE + 4 * i, t[i]);
        gm_set_u8(SLIP_SE_INIT, 1);
    }
    uint32_t n = (uint32_t)(int32_t)gm_s8(pl + 0x1082);
    if (n >= 9) n = 8;
    if (vcall2(GM_PASS, self, 0x248, n)) GM_CALLR(0x800A1D30u, F_CLAP_SE, 1, gm_u32(MULTI_MNG));
    GM_CALLR(0x800A1D3Cu, F_CENTER_POS, 2, f + 16, self);
    gptr obj = gm_u32(SND_OBJ_EMY);
    GM_CALLR(0x800A1D4Cu, F_CVT_SND_POS, 2, f + 8, f + 16);
    GM_CALLR(0x800A1D6Cu, F_SND_EMY, 4, obj, gm_u32(SLIP_SE_TABLE + 4 * n), f + 8, 0);
}

/* ================================================================== d_enemy_state.cpp */
/* changeState(id): out of the Ice sub-state first */
static void change_state(GM_CTX, gptr self, gptr id) {
    FN(0x800A7DF0);
    gptr mgr = self + 0x394;
    gptr cur = vcall0(GM_PASS, mgr, 0x28, 1, 0);
    if (vcall0(GM_PASS, cur, 0x14, 2, STATE_ICE)) vcall0(GM_PASS, mgr, 0x34, 1, 0);   /* returnState */
    vcall0(GM_PASS, mgr, 0x18, 2, id);
}
static void ice_begin(GM_CTX, gptr self) {
    FN(0x800A7E90);
    GM_CALLR(0x800A7EACu, F_ICE_INIT, 1, self + 0x484);
    vcall1(GM_PASS, self, 0x22C);                                         /* createIceActor */
    gm_set_u32(self + 0x274, 0);
    vcall1(GM_PASS, self, 0x230);                                         /* setIceAnm */
    vcall1(GM_PASS, self, 0x98);                                          /* removeCc */
    if (GM_CALLR(0x800A7F00u, F_ICE_INSTANT, 2, self + 0x484, gm_u32(self + 0x4FC) & 0x10000)) gm_set_u32(self + 0x49C, 1);
    gm_set_u32(self + 0x490, 1);
}
static void ice_execute(GM_CTX, gptr self) {
    FN(0x800A7F40);
    int32_t r = (int32_t)GM_CALLR(0x800A7F64u, F_ICE_PROC, 1, self + 0x484);
    if (r == 3) { vcall1(GM_PASS, self, 0x234); vcall1(GM_PASS, self, 0x238); }      /* returnAnm_Ice, returnState_Ice */
    else if (r == 1) vcall1(GM_PASS, self, 0x9C);                                      /* reviveCc */
    else if (r == 0) {
        int32_t mode = (int32_t)gm_u32(self + 0x49C);
        if (mode == 0) return;
        GM_CALLR(0x800A7FD8u, F_ICE_BREAK_EFF, 1, self + 0x484);
        gptr obj = gm_u32(SND_OBJ_MAP);
        GM_CALLR(0x800A7FE8u, F_CVT_SND_POS, 2, f + 8, self + 0xAC);
        GM_CALLR(0x800A7FFCu, F_SND_MAP, 4, obj, 620, f + 8, 0);                        /* SE_OBJ_PNGN_ICE_BREAK */
        if (mode == 1) vcall1(GM_PASS, self, 0x148);
        else if (mode == 3) vcall1(GM_PASS, self, 0x14C);
    }
}
/* createIceActor: one block of ice the enemy's size, mode 0 */
static uint32_t create_ice_actor(GM_CTX, gptr self) {
    FN(0x800A8060);
    double one = R2F(27776), zero = R2F(27772);
    for (int o = 24; o <= 76; o += 4) gm_set_u32(f + o, 0);
    gm_set_u32(f + 20, 0);
    double z = LF(self + 0xB4), y = LF(self + 0xB0), x = LF(self + 0xAC);
    SF(f + 24, x); SF(f + 28, y); SF(f + 32, z);
    SF(f + 8, one); SF(f + 12, one); SF(f + 16, one);
    SF(f + 36, one); SF(f + 40, one); SF(f + 44, one);
    for (int o = 48; o <= 76; o += 4) SF(f + o, zero);
    uint32_t r = GM_CALLR(0x800A8118u, F_ICE_CREATE, 3, self + 0x484, f + 20, 1);
    GM_CALLR(0x800A8134u, F_DESTROY_ARR, 4, f + 20, F_ICE_INFO_DT, 60, 1);
    return r;
}
static void eat_in_execute(GM_CTX, gptr self) {
    FN(0x800A81E0);
    if (gm_u8(self + 0x36C) == 2) { vcall2(GM_PASS, self, 0xD4, STATE_EATNOW); return; }   /* EAT_STATE_EATEN: changeState */
    gptr a = GM_CALLR(0x800A8224u, F_SEARCH, 1, gm_u32(self + 0x368));
    if (a) vcall2(GM_PASS, self, 0xAC, a);                                /* calcEatInScale */
}

/* ================================================================== dEnCombo_c (the score of a combo) */
#define COMBO_DAMAGE  0x802F0508u        /* the plain score, by combo type */
#define COMBO_REGULAR 0x802F0514u        /* by count: 100, 200, ... 1-up */
#define COMBO_SHORT   0x802F0538u
/* calcPlFumiCnt / calcPlComboCnt(player): count up (capped at 8 by the player) and read it */
static int32_t combo_count(GM_CTX, gptr pl, int slide) {
    FN(slide ? 0x8009F690u : 0x8009F5F0u);
    GM_CALL(slide ? 0x80058260u : 0x800581B0u, 2, pl, 8);
    return gm_s8(pl + (slide ? 0x1082 : 0x1080));
}
static int32_t combo_star_count(GM_CTX, gptr pl) {
    FN(0x8009F630);
    vcall2(GM_PASS, pl, 0x3EC, 8);                                        /* the star count, up */
    return (int8_t)vcall1(GM_PASS, pl, 0x3E8);
}
static uint32_t combo_score(GM_CTX, gptr combo, int32_t n) {
    if (n < 0) return 0xFFFFFFFFu;
    if ((uint32_t)n >= 9) n = 8;
    int32_t type = (int32_t)gm_u32(combo);
    if (type == 1) return gm_u32(COMBO_REGULAR + 4 * n);
    if (type == 2) return gm_u32(COMBO_SHORT + 4 * n);
    return 0xFFFFFFFFu;
}
/* (combo, actor, score, player): give the score, by combo type */
static void combo_score_set(GM_CTX, gptr combo, gptr actor, int32_t score, uint32_t plr) {
    if (score < 0) return;
    int32_t type = (int32_t)gm_u32(combo);
    if (type != 1 && type != 2) return;
    ctx->f[1].d = ctx->ps1[1] = R2F(25592); ctx->f[2].d = ctx->ps1[2] = R2F(25588);
    GM_CALL(type == 1 ? F_SCORE_SET : 0x800E22F0u, 4, gm_u32(SCORE_MNG), actor, (uint32_t)score, plr);
}

/* ================================================================== hle entry points
   On in hle_funcs.txt: the 19 (+ getDamageScore) the test runs reach (frozen enemies breaking / vanishing, smoke,
   changeState, the state calls) and the 26 with empty bodies. (The sFStateVirtualID_c<dEn_c> copies are in gm_state_ids.c.) Written but off (no test reaches
   them yet - most need a power-up or Yoshi; enable after a run that does):
   collisionCat3_StarPower, collisionCat11_PipeCannon, collisionCat5_Mario,
   collisionCatA_PenguinMario, collisionCat8_FencePunch, _vf108, collisionCatD_Drill,
   collisionCat7_GroundPound, collisionCat7_GroundPoundYoshi, collisionCat13_Hammer,
   collisionCat14_YoshiFire, collisionCat9_RollingObject, collisionCat1_Fireball_E_Explosion,
   fn_800A0B30, OriginalPowBlockActivated, fn_800A0FB0, _vf140, killByDieFall, dieFumi_Begin,
   dieFumi_Execute, dieFall_Execute, dieBigFall_Begin, dieBigFall_End, dieBigFall_Execute,
   dieYoshiFumi_Begin, dieYoshiFumi_Execute, dieOther_Begin, playEnemyDownSound1,
   playHpdpSound1, playEnemyDownComboSound, playHpdpSound2,
   CreateIceActors, _vf238, eatIn_Execute; and of dEnCombo_c all but
   getDamageScore (the stomp code in gm_d_enemy.c works the combo out itself). */
#define A(i) GM_ARG(i)
GM_HLE(collisionCat3_StarPower__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_combo(GM_PASS, A(0), A(1), A(2), 0)); }   /* ::hitCallback_Star */
GM_HLE(collisionCat11_PipeCannon__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_combo(GM_PASS, A(0), A(1), A(2), 1)); }  /* ::hitCallback_Cannon */
GM_HLE(collisionCat5_Mario__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_combo(GM_PASS, A(0), A(1), A(2), 2)); }        /* ::hitCallback_Slip */
GM_HLE(collisionCatA_PenguinMario__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(GM_CALL(VT(A(0), 0x104), 3, A(0), A(1), A(2))); }   /* ::hitCallback_PenguinSlide */
GM_HLE(_vf120__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(0); }                                     /* ::hitCallback_Screw */
GM_HLE(collisionCat8_FencePunch__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_wirenet(GM_PASS, A(0), A(2))); }          /* ::hitCallback_WireNet */
GM_HLE(_vf108__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_large(GM_PASS, A(0), A(2))); }                              /* ::hitCallback_Large */
GM_HLE(_vf110__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(0); }                                     /* ::hitCallback_Rolling */
GM_HLE(collisionCatD_Drill__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_stomp(GM_PASS, A(0), A(2), 0)); }              /* ::hitCallback_Spin */
GM_HLE(collisionCat7_GroundPound__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_stomp(GM_PASS, A(0), A(2), 1)); }        /* ::hitCallback_HipAttk */
GM_HLE(collisionCat7_GroundPoundYoshi__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_yoshi_hipattk(GM_PASS, A(0), A(2))); }   /* ::hitCallback_YoshiHipAttk */
GM_HLE(collisionCat13_Hammer__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_yoshi_bullet(GM_PASS, A(0), A(1), A(2))); }  /* ::hitCallback_YoshiBullet */
GM_HLE(collisionCat14_YoshiFire__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_yoshi_fire(GM_PASS, A(0), A(1), A(2))); } /* ::hitCallback_YoshiFire */
GM_HLE(collisionCat9_RollingObject__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_shell(GM_PASS, A(0), A(1), A(2))); }   /* ::hitCallback_Shell */
GM_HLE(collisionCat1_Fireball_E_Explosion__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_fire(GM_PASS, A(0), A(2))); }   /* ::hitCallback_Fire */
GM_HLE(collisionCat2_IceBall_15_YoshiIce__5dEn_cFP13ActivePhysicsP13ActivePhysics) { GM_RET(hit_ice(GM_PASS, A(0), A(2))); }     /* ::hitCallback_Ice */
GM_HLE(fn_800A0B30) { set_dead_mode(GM_PASS, A(0), A(1), A(2)); }                                          /* ::setDeadMode */
GM_HLE(OriginalPowBlockActivated) { death_quake(GM_PASS, A(0), A(1)); }                                    /* ::setDeathInfo_Quake */
GM_HLE(fn_800A0DC0) { death_smoke_other(GM_PASS, A(0), A(1), 0); }                                         /* ::setDeathInfo_Smoke */
GM_HLE(killWithSpecifiedState__5dEn_cFP13dStageActor_cP7Point2dP12dStateBase_cUi) { death_fumi(GM_PASS, A(0), A(1), A(2), A(3)); }   /* ::setDeathInfo_Fumi */
GM_HLE(fn_800A0FB0) { death_dir_plr(GM_PASS, A(0), A(1), 0); }                                             /* ::setDeathInfo_YoshiFumi */
GM_HLE(_vf140__5dEn_cFP13dStageActor_c) { death_smoke_other(GM_PASS, A(0), A(1), 1); }                     /* ::setDeathInfo_Other */
GM_HLE(killByDieFall__5dEn_cFP13dStageActor_c) { death_dir_plr(GM_PASS, A(0), A(1), 1); }                  /* ::setDeathInfo_SpinFumi */
GM_HLE(_vf148__5dEn_cFv) { death_ice(GM_PASS, A(0), 0); }                                                  /* ::setDeathInfo_IceBreak */
GM_HLE(_vf14C__5dEn_cFv) { death_ice(GM_PASS, A(0), 1); }                                                  /* ::setDeathInfo_IceVanish */
GM_HLE(dieFumi_Begin__5dEn_cFv) { die_fall_begin(GM_PASS, A(0), 0); }                                      /* ::initializeState_DieFumi */
GM_HLE(fn_800A15F0) { }                                                                                    /* ::finalizeState_DieFumi */
GM_HLE(dieFumi_Execute__5dEn_cFv) { die_fumi_execute(GM_PASS, A(0)); }                                     /* ::executeState_DieFumi */
GM_HLE(dieFall_Begin__5dEn_cFv) { die_fall_begin(GM_PASS, A(0), 1); }                                      /* ::initializeState_DieFall */
GM_HLE(dieFumi_End__5dEn_cFv) { }                                                                          /* ::finalizeState_DieFall (misnamed) */
GM_HLE(dieFall_Execute__5dEn_cFv) { die_fall_execute(GM_PASS, A(0)); }                                     /* ::executeState_DieFall */
GM_HLE(dieBigFall_Begin__5dEn_cFv) { GM_CALL(VT(A(0), 0x178), 1, A(0)); }                                  /* ::initializeState_DieBigFall */
GM_HLE(dieBigFall_End__5dEn_cFv) { GM_CALL(VT(A(0), 0x180), 1, A(0)); }                                    /* ::finalizeState_DieBigFall */
GM_HLE(dieBigFall_Execute__5dEn_cFv) { die_bigfall_execute(GM_PASS, A(0)); }                               /* ::executeState_DieBigFall */
GM_HLE(dieSmoke_Begin__5dEn_cFv) { die_effect_begin(GM_PASS, A(0), 0); }                                   /* ::initializeState_DieSmoke */
GM_HLE(dieSmoke_End__5dEn_cFv) { }
GM_HLE(dieSmoke_Execute__5dEn_cFv) { GM_CALL(F_DELETE_ACTOR, 2, A(0), 1); }
GM_HLE(dieIceVanish_Begin__5dEn_cFv) { die_ice_vanish_begin(GM_PASS, A(0)); }                              /* ::initializeState_DieIceVanish */
GM_HLE(dieIceVanish_End__5dEn_cFv) { }
GM_HLE(dieIceVanish_Execute__5dEn_cFv) { GM_CALL(F_DELETE_ACTOR, 2, A(0), 1); }
GM_HLE(dieYoshiFumi_Begin__5dEn_cFv) { die_effect_begin(GM_PASS, A(0), 1); }                               /* ::initializeState_DieYoshiFumi */
GM_HLE(dieYoshiFumi_End__5dEn_cFv) { }
GM_HLE(dieYoshiFumi_Execute__5dEn_cFv) { GM_CALL(F_DELETE_ACTOR, 2, A(0), 1); }
GM_HLE(dieGoal_Begin__5dEn_cFv) { }                                                                        /* ::*State_DieGoal: nothing */
GM_HLE(dieGoal_End__5dEn_cFv) { }
GM_HLE(dieGoal_Execute__5dEn_cFv) { }
GM_HLE(dieOther_Begin__5dEn_cFv) { GM_CALL(F_DELETE_ACTOR, 2, A(0), 1); }                                  /* ::initializeState_DieOther */
GM_HLE(dieOther_End__5dEn_cFv) { }
GM_HLE(dieOther_Execute__5dEn_cFv) { }
GM_HLE(playEnemyDownSound1__5dEn_cFv) { sound_fire(GM_PASS, A(0)); }                                       /* ::setDeathSound_Fire */
GM_HLE(playHpdpSound1__5dEn_cFv) { sound_hpdp(GM_PASS, A(0), 0x800A1C00u); }                               /* FNADDR ::setDeathSound_HipAttk */
GM_HLE(playEnemyDownComboSound__5dEn_cFPv) { sound_slip(GM_PASS, A(0), A(1)); }                            /* ::setDeathSound_Slip */
GM_HLE(playHpdpSound2__5dEn_cFv) { sound_hpdp(GM_PASS, A(0), 0x800A1D90u); }                               /* FNADDR ::setDeathSound_Spin */
GM_HLE(_vf168__5dEn_cFv) { }                                                                               /* ::setDeathSound_Rolling */
/* d_enemy_state.cpp */
GM_HLE(doStateChange__5dEn_cFP12dStateBase_c) { change_state(GM_PASS, A(0), A(1)); }                       /* ::changeState */
GM_HLE(ice_Begin__5dEn_cFv) { ice_begin(GM_PASS, A(0)); }                                                  /* ::initializeState_Ice */
GM_HLE(ice_End__5dEn_cFv) { gm_set_u32(A(0) + 0x490, 0); }                                                 /* ::finalizeState_Ice */
GM_HLE(ice_Execute__5dEn_cFv) { ice_execute(GM_PASS, A(0)); }                                              /* ::executeState_Ice */
GM_HLE(CreateIceActors__5dEn_cFv) { GM_RET(create_ice_actor(GM_PASS, A(0))); }                             /* ::createIceActor */
GM_HLE(_vf230__5dEn_cFv) { }                                                                               /* ::setIceAnm */
GM_HLE(_vf234__5dEn_cFv) { }                                                                               /* ::returnAnm_Ice */
GM_HLE(fn_800A8170) { GM_RET(GM_CALL(F_ICE_REMOVE, 1, A(0) + 0x484)); }                                    /* ::killIce */
GM_HLE(_vf238__5dEn_cFv) { GM_RET(vcall0(GM_PASS, A(0) + 0x394, 0x34, 1, 0)); }                            /* ::returnState_Ice */
GM_HLE(hitSpin_Begin__5dEn_cFv) { }                                                                        /* ::*State_HitSpin, _EatIn, _EatNow, _EatOut */
GM_HLE(hitSpin_End__5dEn_cFv) { }
GM_HLE(hitSpin_Execute__5dEn_cFv) { }
GM_HLE(eatIn_Begin__5dEn_cFv) { }
GM_HLE(eatIn_End__5dEn_cFv) { }
GM_HLE(eatIn_Execute__5dEn_cFv) { eat_in_execute(GM_PASS, A(0)); }
GM_HLE(eatNow_Begin__5dEn_cFv) { }
GM_HLE(eatNow_End__5dEn_cFv) { }
GM_HLE(eatNow_Execute__5dEn_cFv) { }
GM_HLE(eatOut_Begin__5dEn_cFv) { }
GM_HLE(eatOut_End__5dEn_cFv) { }
GM_HLE(eatOut_Execute__5dEn_cFv) { }
/* dEnCombo_c */
GM_HLE(calcPlFumiCnt__10dEnCombo_cFP8dActor_c) { GM_RET((uint32_t)combo_count(GM_PASS, A(0), 0)); }
GM_HLE(calcPlStarCnt__10dEnCombo_cFP8dActor_c) { GM_RET((uint32_t)combo_star_count(GM_PASS, A(0))); }
GM_HLE(calcPlComboCnt__10dEnCombo_cFP8dActor_c) { GM_RET((uint32_t)combo_count(GM_PASS, A(0), 1)); }
GM_HLE(getDamageScore__10dEnCombo_cCFv) { GM_RET(gm_u32(COMBO_DAMAGE + 4 * gm_u32(A(0)))); }
GM_HLE(getQuakeScore__10dEnCombo_cCFi) { GM_RET((int32_t)A(1) > 8 ? 8 : A(1)); }
GM_HLE(getComboScore__10dEnCombo_cFi) { GM_RET(combo_score(GM_PASS, A(0), (int32_t)A(1))); }
GM_HLE(fn_8009F770) { combo_score_set(GM_PASS, A(0), A(1), (int32_t)A(2), A(3)); }                          /* ::setComboScore? (combo, actor, score, player) */
