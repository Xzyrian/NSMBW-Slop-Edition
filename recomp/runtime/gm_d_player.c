/* gm_d_player.c - dAcPy_c, the player: the game's own version (track B, gm.h, docs/DECOMP.md),
 * instance 2 (track B helper). The small methods (at most 96 bytes) the A/B inputs reach.
 *
 * Names from NSMBW-Decomp (source/dol/bases/d_a_player.cpp, PAL addresses = E2 + 0x140), checked
 * against the recompiled code (the E2 vtable is at 0x80325420: the virtuals were named by their
 * slots in the module's annotated headers). Field names: the decomp's (dAcPy_c's own fields m_XXXX
 * at 0x14D8 + XXXX) or the module's header where the decomp has none.
 *
 * Register-exact (gm_i2.h): r0-r12, CR, CTR, XER[CA], f0-f13 and both paired-single halves as the
 * PowerPC code leaves them; r30 / r31 held as the PowerPC code holds them at each call (NV_R),
 * the frames pushed with their prologues replayed (I2_FN).
 *
 * Calls into daPlBase_c (another helper may make those native at the same time) go through PB():
 * the hle_ entry when one is linked in, else the recompiled function - the symbol the recompiled
 * code calls either way. Which functions are on and how they were verified: see the list before
 * the entry points at the end. */
#include "gm_i2.h"
RT_STATE_FILE                                   /* (game code: its variables are part of a save state) */

/* ---- fBase_c / dBaseActor_c / dActor_c fields */
#define AC_UNIQUE_ID        0           /* fBaseID_e mUniqueID */
#define AC_PROF_NAME        8           /* u16 mProfName */
#define AC_VTABLE           96
#define AC_POS              172         /* mVec3_c mPos */
#define AC_SCALE            220         /* mVec3_c mScale */
#define AC_SPEED_Y          236         /* mSpeed.y */
#define AC_ANGLE_Y          258         /* s16 mAngle.y */
#define AC_SPEED_F          268         /* float mSpeedF */
#define AC_ACCEL_Y          276         /* float mAccelY */
#define AC_MAX_FALL_SPEED   280         /* float mMaxFallSpeed */
#define AC_CC_OFFSET        356         /* mCc.mCcData.mBase.mOffset (x, y), mSize (x, y) at +8 */
#define AC_CC_VS_DAMAGE     380         /* u32 mCc.mCcData.mVsDamage */
#define AC_BC               492         /* dBc_c mBc */
#define AC_VISIBLE_SIZE     792         /* mVec2_c mVisibleAreaSize (setPlayerData) */
#define AC_VISIBLE_OFFSET   800         /* mVec2_c mVisibleAreaOffset */
#define AC_DIRECTION        840         /* u8 mDirection */
#define AC_PROPEL_PARTS     904         /* dPropelParts_c *mpPropelParts */
#define AC_KIND             908         /* u8 mKind (1 = a player) */
#define AC_PLAYER_NO        909         /* s8 mPlayerNo */
#define AC_EXEC_STOP_MASK   910         /* u8 mExecStopMask */
/* ---- daPlBase_c fields */
#define PL_SMOKE_EFFECT     1784        /* mEf::levelEffect_c mSmokeEffect */
#define PL_KEY              3748        /* dAcPyKey_c mKey */
#define PL_RIDE_ACTOR_ID    4104        /* fBaseID_e mRideActorID (the Yoshi / player ridden) */
#define PL_RELATED_ACTOR_ID 4108        /* fBaseID_e mRelatedActorID (mActionActorID) */
#define PL_STATUS_FLAGS     4116        /* u32 mStatusFlags[7] */
#define PL_MODEL_HEIGHT     4144        /* float mModelHeight */
#define PL_SPEED_DATA       4192        /* const sSpeedData *mSpeedDataNormal, mSpeedDataStar at +4 */
#define PL_GRAVITY_DATA     4200        /* const float *mGravityData */
#define PL_STAR_TIMER       4208        /* int mStarTimer */
#define PL_DAMAGE_INVULN    4212        /* int mDamageInvulnTimer */
#define PL_CHANGE_INVULN    4216        /* int mPowerupChangeInvulnTimer */
#define PL_POWERUP          4240        /* PLAYER_POWERUP_e mPowerup */
#define PL_NOW_BG_CROSS1    4308        /* u32 mNowBgCross1, mNowBgCross2 at +4 */
#define PL_OLD_BG_CROSS1    4316        /* u32 mOldBgCross1, mOldBgCross2 at +4 */
#define PL_ATT_CC1          4644        /* mAttCc1.mCcData.mBase: mOffset (x, y), mSize (x, y) */
#define PL_ATT_CC1_ATTACK   4661        /* u8 mAttCc1.mCcData.mAttack */
#define PL_ATT_CC1_VS_KIND  4664        /* u32 mAttCc1.mCcData.mVsKind */
#define PL_ATT_CC1_VS_DMG   4668        /* u32 mAttCc1.mCcData.mVsDamage */
#define PL_DEMO_SUBSTATE    5208        /* int mDemoSubstate */
#define PL_DEMO_SUBSTATE_T  5212        /* int mDemoSubstateTimer */
#define PL_SUBSTATE         5284        /* int mSubstate */
#define PL_SUBSTATE_TIMER   5288        /* int mSubstateTimer */
#define PL_POWERUP_COPY2    5344        /* PLAYER_POWERUP_e mPowerupCopy2 (the module: mNextMode) */
#define PL_CC_M0C           5348        /* mVec2_c m_0c (the body cc's offset) */
#define PL_PC               5372        /* dPc_c mPc (+45: m_2d) */
#define PL_PC_M2D           5417
/* ---- dAcPy_c fields (m_XXXX = 0x14D8 + XXXX) */
#define PY_SCROLL_MODE      5436        /* s8 mScrollMode */
#define PY_CHANGE_TYPE      5437        /* s8 mChangeType */
#define PY_AMI_RELATED2     5444        /* float mAmiRelated2 (the model scale) */
#define PY_M74              5452        /* int m_74 */
#define PY_WAIT_FRAME_COUNT 5468        /* int mWaitFrameCount */
#define PY_JUMP_COUNTER     5476        /* int mJumpCounter */
#define PY_PROPEL_M2EC      6084        /* int m_2ec */
#define PY_PROPEL_FLY_TIME  6092        /* s16 m_2f4 */
#define PY_PROPEL_ROLL_SPD  6094        /* s16 mPropelRollSpeed */
#define PY_FOLLOW_EF        6396        /* dEf::followEffect_c mFollowEf */
#define PY_FALL_SPIN_EF     6672        /* int m_538 (the fall-spin effect is on) */
#define PY_FALL_SPIN_M53C   6676        /* int m_53c */
#define PY_WATER_JUMP_M_B88 8288        /* u8 m_b88 */
#define PY_MISS_SPIN_ANGLE  9524        /* s16 m_105c */
#define PY_FOLLOW_EF2       9528        /* dEf::followEffect_c mFollowEf2 */
#define PY_SPIN_JUMP_EF     10080       /* u32 m_1288 (the spin-jump effect is on) */
#define PY_LIFT_RESERVE_ID  10196       /* fBaseID_e m_12fc: the actor reserved for a spin lift-up */
#define PY_LIFT_RESERVE_M   10200       /* float m_1300 */
#define PY_LIFT_OFFSET      10204       /* float m_1304 */
#define PY_LIFT_M1308       10208       /* int m_1308 (0: the lift-up is done) */
#define PY_KEY_TIMER_B      10220       /* int: setInvalidKeyTimer's second argument (m_1310) */
#define PY_KEY_TIMER_A      10228       /* int: its first (m_1318) */
#define PY_POWERUP_EF_TIMER 10236       /* int mPowerUpEffectTimer */
#define PY_POWERUP_TYPE     10240       /* int mPowerUpType */
#define PY_MDL              10852       /* dPyMdlBase_c *mPyMdlMng.mpMdl */
#define PY_CC_M1598         10864       /* float m_1598, m_159c at +4 */
#define PY_CARRY_ACTOR_ID   10872       /* fBaseID_e mCarryActorID */
#define PY_WATER_WALK_TIMER 10892       /* s16 mWaterWalkTimer */
#define PY_SIZE             11528       /* sizeof(dAcPy_c) */
/* the model (dPyMdlBase_c) */
#define MDL_ANM             40          /* m3d::fanm_c mAnm */
#define MDL_ANM_ID          340         /* int mCurrAnmID */
/* virtual methods (dAcPy_c's vtable offsets) */
#define VT_SET_POWERUP      228
#define VT_GET_TALL_TYPE    232
#define VT_IS_ITEM_KINOPIO  224
#define VT_CHANGE_STATE     660
#define VT_SET_WAIT_ANM     888         /* setWaitActionAnm(blend) */
#define VT_SET_WALK_ANM     892         /* setWalkActionAnm(blend) */
#define VT_GET_GRAVITY_DATA 964
#define VT_IS_CARRY         968
#define VT_SET_STAR         984         /* setStar(set, timer) */
#define VT_START_QUAKE      1084        /* startQuakeShock(type) */
#define VT_START_RUMBLE     1088        /* startPatternRumble(pattern) */
#define VT_GET_MUKI_ANGLE   1092        /* getMukiAngle(dir) */
#define EF_KILL             24          /* (followEffect_c's vtable: kill) */
/* the game's data (E2) */
#define SC_WATER_RUN_EF     0x80429370u /* const char *sc_waterRunEffectID[2] (r13 - 25360) */
#define L_MODE_CC_SIZE      0x802F50A8u /* int l_mode_cc_size_data[7] */
#define L_CC_SIZE_DATA      0x80325260u /* const sCcDatNew *l_cc_size_data[] */
#define SC_CC_DATA          0x802F50C4u /* sCcDatNewF scCcData, scAtCcData (initCcData) */
#define SC_AT_CC_DATA       0x802F50E8u
#define SC_BG_POINT_DATA    0x8032528Cu /* const sBcPlayerPointData *scBgPointData[7] (64 bytes each) */
#define L_PLAYER_CULL       0x802F57C0u /* mVec2_POD_c l_player_cull_data[2] */
#define SC_SPEED_HIO_DATA   0x802F57D0u /* int scSpeedHioData[7] */
#define M_SPEED_HIO         0x803768B0u /* dPyHIO speed data, 240 bytes per entry (+120: the star data) */
#define POWER_CHANGE_DATA   0x802F5580u /* daPlayerData_c::smc_POWER_CHANGE_DATA (+152 gravity[0], +224 gravity[1]) */
#define LIFT_UP_POS_DATA    0x80325340u /* sGlobalData_c<dAcPy_c>::mData.mPos[] (12 bytes each; the y at +36) */
#define L_CHANGE_INIT_PROC  0x80325230u /* l_changeInitProc[2] (pointers to member functions, 12 bytes) */
#define RUMBLE_PROPEL_FLY   0x803250ECu /* "***---***---*----**-----*----**-----*-----**-----*" */
#define STATE_PLAYER_EAT    0x80376530u /* dAcPy_c::StateID_PlayerEat */
#define STATE_DEMO_IN_DOOR  0x80376670u /* dAcPy_c::StateID_DemoInDoor */
#define PY_REST_MOD         0x81851D8Cu /* daPyMng_c::mRest[8] (the module's) */
#define PY_TYPE_MOD         0x8185E93Cu /* daPyMng_c::mPlayerType[8] (the module's) */
#define PY_REST_GAME        0x80354E90u /* (the game's own arrays, without the module) */
#define PY_TYPE_GAME        0x80354E60u
/* profiles */
#define PROF_AC_LIGHT_BLOCK 412
#define PROF_AC_PROP_BLOCK  413
/* status flags (daPlBase_c::onStatus / offStatus / isStatus numbers) */
#define ST_CAN_WATER_WALK   193
#define ST_CAN_LAND         143
#define ST_AB               171         /* (calcJumpCount: no count) */
#define ST_TWIRL            45
#define ST_CAN_SPIN         159
#define ST_A2               162
#define ST_AA               170
#define ST_97               151
#define ST_46               70
#define ST_THROW            24
#define ST_INVISIBLE        187
#define ST_RIDE_YOSHI       75
#define ST_45               69          /* (riding a player) */
/* sounds */
#define SE_PLY_ROLLING      260
#define SE_PLY_SPIN_ONCE    272
#define SE_PLY_SLIP_W       234
#define SE_PLY_SWIM         318
#define SE_PLY_PRPL_LETDOWN_SPIN 282

/* ---- calls into daPlBase_c: the native when one is linked in, else the recompiled function */
#define PB_DECL(h, f) void h(ppc_context *, uint8_t *) __attribute__((weak)); void f(ppc_context *, uint8_t *) __attribute__((weak));
#define PB(h, f) (h ? h : f)
PB_DECL(hle_testFlag__10daPlBase_cFi, testFlag__10daPlBase_cFi_80056CF0)
PB_DECL(hle_setFlag__10daPlBase_cFi, setFlag__10daPlBase_cFi_80056C70)
PB_DECL(hle_clearFlag__10daPlBase_cFi, clearFlag__10daPlBase_cFi_80056CB0)
PB_DECL(hle_PlayPlayerSound, PlayPlayerSound_80057E70)
PB_DECL(hle_fn_80057F60, fn_80057F60)
PB_DECL(hle_fn_80048F30, fn_80048F30)
PB_DECL(hle_fn_800497E0, fn_800497E0)
PB_DECL(hle_fn_80049880, fn_80049880)
PB_DECL(hle_fn_80049940, fn_80049940)
PB_DECL(hle_fn_8004CA60, fn_8004CA60)
PB_DECL(hle_fn_8004CF20, fn_8004CF20)
PB_DECL(hle_fn_800480D0, fn_800480D0)
PB_DECL(hle_fn_80048170, fn_80048170)
PB_DECL(hle_fn_800481C0, fn_800481C0)
PB_DECL(hle_fn_8004D210, fn_8004D210)
PB_DECL(hle_fn_8004CFD0, fn_8004CFD0)
PB_DECL(hle_fn_8004D040, fn_8004D040)
PB_DECL(hle_fn_80047DC0, fn_80047DC0)
PB_DECL(hle_fn_8004F670, fn_8004F670)
PB_DECL(hle_fn_8004E290, hle_fn_8004E290)
PB_DECL(hle_fn_8004E700, fn_8004E700)
PB_DECL(hle_fn_8004E7A0, fn_8004E7A0)
PB_DECL(hle_fn_80053650, fn_80053650)
PB_DECL(hle_fn_800534B0, fn_800534B0)
PB_DECL(hle_fn_80056BD0, fn_80056BD0)
PB_DECL(hle_fn_80046AB0, fn_80046AB0)
PB_DECL(hle_fn_80058280, fn_80058280)
PB_DECL(hle_fn_800582A0, fn_800582A0)
#define PL_testFlag                 PB(hle_testFlag__10daPlBase_cFi, testFlag__10daPlBase_cFi_80056CF0)
#define PL_onStatus                 PB(hle_setFlag__10daPlBase_cFi, setFlag__10daPlBase_cFi_80056C70)
#define PL_offStatus                PB(hle_clearFlag__10daPlBase_cFi, clearFlag__10daPlBase_cFi_80056CB0)
#define PL_startSound               PB(hle_PlayPlayerSound, PlayPlayerSound_80057E70)
#define PL_holdSound                PB(hle_fn_80057F60, fn_80057F60)
#define PL_setHipAttack_AttackStart PB(hle_fn_80048F30, fn_80048F30)
#define PL_initializeState_HipAttack PB(hle_fn_800497E0, fn_800497E0)
#define PL_finalizeState_HipAttack  PB(hle_fn_80049880, fn_80049880)
#define PL_executeState_HipAttack   PB(hle_fn_80049940, fn_80049940)
#define PL_setSlipSE                PB(hle_fn_8004CA60, fn_8004CA60)
#define PL_setSlipSmokeEffect       PB(hle_fn_8004CF20, fn_8004CF20)
#define PL_initializeState_Slip     PB(hle_fn_800480D0, fn_800480D0)
#define PL_finalizeState_Slip       PB(hle_fn_80048170, fn_80048170)
#define PL_executeState_Slip        PB(hle_fn_800481C0, fn_800481C0)
#define PL_fadeOutTurnEffect        PB(hle_fn_8004D210, fn_8004D210)
#define PL_setBrakeSmokeEffect      PB(hle_fn_8004CFD0, fn_8004CFD0)
#define PL_setTurnSmokeEffect       PB(hle_fn_8004D040, fn_8004D040)
#define PL_setCancelCrouch          PB(hle_fn_80047DC0, fn_80047DC0)
#define PL_initDemoOutDokan         PB(hle_fn_8004F670, fn_8004F670)
#define PL_changeDemoState          PB(hle_fn_8004E290, hle_fn_8004E290)
#define PL_initializeState_DemoStartWait PB(hle_fn_8004E700, fn_8004E700)
#define PL_finalizeState_DemoStartWait   PB(hle_fn_8004E7A0, fn_8004E7A0)
#define PL_setCcAtBody              PB(hle_fn_80053650, fn_80053650)
#define PL_initCollision            PB(hle_fn_800534B0, fn_800534B0)
#define PL_isMameAction             PB(hle_fn_80056BD0, fn_80056BD0)
#define PL_preExecute               PB(hle_fn_80046AB0, fn_80046AB0)
#define PL_startQuakeShock          PB(hle_fn_80058280, fn_80058280)
#define PL_startPatternRumble       PB(hle_fn_800582A0, fn_800582A0)

/* ---- this file's natives, called from each other through their hle_ entries (so a verified call
   verifies them too) */
void hle_fn_801298B0(ppc_context *ctx, uint8_t *base);
void hle_fn_8012AB00(ppc_context *ctx, uint8_t *base);
void hle_fn_80145E40(ppc_context *ctx, uint8_t *base);
void hle_fn_8012DBE0(ppc_context *ctx, uint8_t *base);
void hle_fn_8012DC60(ppc_context *ctx, uint8_t *base);
void hle_fn_8013AAA0(ppc_context *ctx, uint8_t *base);
void hle_fn_8012E940(ppc_context *ctx, uint8_t *base);
void hle_fn_80141F70(ppc_context *ctx, uint8_t *base);
void hle_fn_80142510(ppc_context *ctx, uint8_t *base);
void hle_getYoshi__7dAcPy_cFv(ppc_context *ctx, uint8_t *base);
void hle_fn_8012E510(ppc_context *ctx, uint8_t *base);
void hle_fn_8012E360(ppc_context *ctx, uint8_t *base);
void hle_fn_8012E9A0(ppc_context *ctx, uint8_t *base);
/* (other classes' natives) */
void hle_search__7fBase_cFUi(ppc_context *ctx, uint8_t *base);
void hle_isAnimationDone__Q23m3d6fanm_cFv(ppc_context *ctx, uint8_t *base);
void hle_AllocateMemoryBlock(ppc_context *ctx, uint8_t *base);
void hle_createPlayerEffect__3dEfFiPQ23mEf13levelEffect_cPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c(ppc_context *ctx, uint8_t *base);

/* (single-precision helpers: lfs and single arithmetic set both halves) */
#define LDF(n, a)  (ctx->f[n].d = ctx->ps1[n] = ldfs(base, (a)))
#define STF(a, n)  stfs(base, (a), ctx->f[n].d)
#define FS(n, e)   (ctx->f[n].d = ctx->ps1[n] = frsp(e))
#define F(n)       (ctx->f[n].d)
/* a call through the object's vtable (+96): lwz r12, 96(r3); lwz r12, slot(r12); mtctr; bctrl */
#define VCALL(ra, obj, slot) i2_vcall(ctx, base, (ra), (obj), (slot), 12)
/* the same as a tail call (bctr: LR stays the caller's) */
static inline void py_vtail(GM_CTX, gptr obj, uint32_t slot) {
    R(12) = gm_u32(obj + AC_VTABLE); R(12) = gm_u32(R(12) + slot); ctx->ctr = R(12);
    ppc_call_indirect(ctx, base, ctx->ctr);
}
#define VTAIL(obj, slot) py_vtail(GM_PASS, (obj), (slot))
/* onStatus / offStatus / isStatus(flag) (r3 = the object already) */
#define ON_STATUS(ra, f)  (R(4) = (f), BL((ra), PL_onStatus))
#define OFF_STATUS(ra, f) (R(4) = (f), BL((ra), PL_offStatus))

/* ================================================================== hip attack */
/* setHipAttack_AttackStart: the base's, and the rolling sound */
static void py_setHipAttack_AttackStart(GM_CTX, gptr self) {
    I2_FN(0x801267D0u);
    NV_R(31, self);
    BL(0x801267E8u, PL_setHipAttack_AttackStart);
    R(3) = self; R(4) = SE_PLY_ROLLING; R(5) = 0;
    BL(0x801267F8u, PL_startSound);
}
/* initializeState_HipAttack: the base's, no jump count, no water walk, can land */
static void py_initializeState_HipAttack(GM_CTX, gptr self) {
    I2_FN(0x80126810u);
    NV_R(31, self);
    BL(0x80126828u, PL_initializeState_HipAttack);
    R(0) = 0; gm_set_u32(self + PY_JUMP_COUNTER, 0);
    R(3) = self; OFF_STATUS(0x8012683Cu, ST_CAN_WATER_WALK);
    R(3) = self; ON_STATUS(0x80126848u, ST_CAN_LAND);
}
/* finalizeState_HipAttack */
static void py_finalizeState_HipAttack(GM_CTX, gptr self) {
    I2_FN(0x80126860u);
    NV_R(31, self);
    BL(0x80126878u, PL_finalizeState_HipAttack);
    R(3) = self; OFF_STATUS(0x80126884u, ST_CAN_LAND);
}
/* executeState_HipAttack: into shallow water this frame - the splash; then the base's */
static void py_executeState_HipAttack(GM_CTX, gptr self) {
    I2_FN(0x801268A0u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
    if (R(0)) {
        R(0) = gm_u32(self + PL_OLD_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
        if (!R(0)) BL(0x801268D0u, hle_fn_8012FB10);                        /* (setWaterInEffect) */
    }
    R(3) = self; BL(0x801268D8u, PL_executeState_HipAttack);
}

/* ================================================================== jumps */
/* calcJumpCount: the triple jump's count (0, 1, 2, 0 ...) */
static void py_calcJumpCount(GM_CTX, gptr self) {
    I2_FN(0x80127410u);
    R(4) = ST_AB; NV_R(31, self);
    BL(0x8012742Cu, PL_testFlag);
    if (CMPS(R(3), 0) != 0) return;
    R(3) = gm_u32(self + PY_JUMP_COUNTER); R(0) = R(3) + 1;
    gm_set_u32(self + PY_JUMP_COUNTER, R(0));
    if (CMPS(R(0), 2) > 0) { R(0) = 0; gm_set_u32(self + PY_JUMP_COUNTER, 0); }
}
/* setJumpSpeed: mSpeed.y = getJumpSpeed(), 1.05 times on the third jump */
static void py_setJumpSpeed(GM_CTX, gptr self) {
    I2_FN(0x801275B0u);
    NV_R(31, self);
    BL(0x801275C8u, hle_fn_80127470);                                        /* (getJumpSpeed: f1) */
    R(0) = gm_u32(self + PY_JUMP_COUNTER);
    if (CMPS(R(0), 2) == 0) { LDF(0, R(2) - 22792); FS(1, F(1) * F(0)); }   /* (1.05f) */
    STF(self + AC_SPEED_Y, 1);
}
/* finalizeState_WallJump: mAccelY = getGravityData()[0] */
static void py_finalizeState_WallJump(GM_CTX, gptr self) {
    I2_FN(0x80128D20u);
    NV_R(31, self);
    VCALL(0x80128D44u, self, VT_GET_GRAVITY_DATA);
    LDF(0, R(3));
    STF(self + AC_ACCEL_Y, 0);
}

/* ================================================================== spin jumps */
/* endSpinJumpEffect: kill the spin jump's follow effect */
static void py_endSpinJumpEffect(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PY_SPIN_JUMP_EF);
    if (CMPS(R(0), 0) == 0) return;
    R(0) = 0; gm_set_u32(self + PY_SPIN_JUMP_EF, 0);
    R(3) = self + PY_FOLLOW_EF2; R(12) = gm_u32(R(3));
    R(12) = gm_u32(R(12) + EF_KILL); ctx->ctr = R(12);
    ppc_call_indirect(ctx, base, ctx->ctr);                              /* (bctr) */
}
/* isMissSpinEnableAnm: not in the star roll, nor in a roll jump still playing */
static void py_isMissSpinEnableAnm(GM_CTX, gptr self) {
    I2_FN(0x801298B0u);
    R(3) = gm_u32(self + PY_MDL); R(0) = gm_u32(R(3) + MDL_ANM_ID);
    if (CMPS(R(0), 117) == 0) { R(3) = 0; return; }
    if (CMPS(R(0), 11) == 0) {
        R(3) += MDL_ANM;
        BL(0x801298E4u, hle_isAnimationDone__Q23m3d6fanm_cFv);
        if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
    }
    R(3) = 1;
}
/* getMissSpinAngle */
static void py_getMissSpinAngle(GM_CTX, gptr self) {
    I2_FN(0x80129910u);
    NV_R(31, self);
    BL(0x80129928u, hle_fn_801298B0);
    if (CMPS(R(3), 0) != 0) R(3) = (uint32_t)(int16_t)gm_u16(self + PY_MISS_SPIN_ANGLE);
    else R(3) = 0;
}
/* setMissSpin: a spin in the air without effect - the angle, the sound, the effect */
static void py_setMissSpin(GM_CTX, gptr self) {
    I2_FN(0x80129950u);
    R(4) = SE_PLY_SPIN_ONCE; R(5) = 1;
    R(0) = 0x1400; NV_R(31, self);
    gm_set_u16(self + PY_MISS_SPIN_ANGLE, 0x1400);
    BL(0x80129978u, PL_startSound);
    R(3) = self; BL(0x80129980u, hle_fn_801298B0);
    if (CMPS(R(3), 0) != 0) { R(3) = self; R(4) = 1; BL(0x80129994u, hle_fn_80129220); }   /* (setMissSpinJumpEffect) */
}
/* resetMissSpin */
static void py_resetMissSpin(GM_CTX, gptr self) {
    R(0) = 0; gm_set_u16(self + PY_MISS_SPIN_ANGLE, 0);
}
/* updateMissSpin: the angle turns once round, the twirl status meanwhile */
static void py_updateMissSpin(GM_CTX, gptr self) {
    R(4) = (uint32_t)(int16_t)gm_u16(self + PY_MISS_SPIN_ANGLE);
    int c = CMPS(R(4), 0);
    if (c == 0) return;
    R(0) = R(4) + 0x1400; gm_set_u16(self + PY_MISS_SPIN_ANGLE, (uint16_t)R(0));
    if (c < 0) {
        R(0) = (uint32_t)(int16_t)R(0); CR0(ctx, R(0));                 /* (extsh.) */
        if ((int32_t)R(0) >= 0) { R(0) = 0; gm_set_u16(self + PY_MISS_SPIN_ANGLE, 0); return; }
    }
    R(4) = ST_TWIRL; PL_onStatus(ctx, base);                             /* (b) */
}

/* ================================================================== slips */
/* setSlipSE: on water as the mini: the water slip sound; else the base's */
static void py_setSlipSE(GM_CTX, gptr self) {
    LDF(1, self + AC_SPEED_F); LDF(0, R(2) - 22824);                    /* (0.0f) */
    cr_fcmp(ctx, 0, F(1), F(0));
    if (CR_BIT(ctx, 2)) return;
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x8000; CR0(ctx, R(0));
    if (R(0)) {
        R(0) = gm_u32(self + PL_POWERUP);
        if (CMPS(R(0), 3) == 0) { R(4) = SE_PLY_SLIP_W; R(5) = 0; PL_holdSound(ctx, base); return; }
    }
    PL_setSlipSE(ctx, base);
}
/* setSlipEffect */
static void py_setSlipEffect(GM_CTX, gptr self) {
    I2_FN(0x8012AB40u);
    NV_R(31, self);
    BL(0x8012AB58u, PL_setSlipSmokeEffect);
    R(3) = self; BL(0x8012AB60u, hle_fn_8012AB00);
}
/* initializeState_Slip: the base's, let go of what is carried, can spin, water walk */
static void py_initializeState_Slip(GM_CTX, gptr self) {
    I2_FN(0x8012ABF0u);
    NV_R(31, self);
    BL(0x8012AC08u, PL_initializeState_Slip);
    R(3) = self; BL(0x8012AC10u, hle_fn_8012E5A0);                          /* (releaseCarryActor) */
    R(3) = self; ON_STATUS(0x8012AC1Cu, ST_CAN_SPIN);
    R(3) = self; BL(0x8012AC24u, hle_fn_80145E40);                      /* (setWaterWalkFlag) */
}
/* finalizeState_Slip */
static void py_finalizeState_Slip(GM_CTX, gptr self) {
    I2_FN(0x8012AC40u);
    NV_R(31, self);
    BL(0x8012AC58u, PL_finalizeState_Slip);
    R(3) = self; OFF_STATUS(0x8012AC64u, ST_CAN_SPIN);
}

/* ================================================================== walking, turning, crouching */
/* isWaitFrameCountMax: mWaitFrameCount >= 80 (srawi / subfc / adde) */
static void py_isWaitFrameCountMax(GM_CTX, gptr self) {
    R(5) = gm_u32(self + PY_WAIT_FRAME_COUNT); R(0) = 80; R(3) = 0;
    R(4) = SRAWI31(R(5));
    { uint64_t t = (uint64_t)(uint32_t)~R(0) + R(5) + 1; R(0) = (uint32_t)t; ctx->xer_ca = (uint32_t)(t >> 32); }
    { uint64_t t = (uint64_t)R(4) + R(3) + ctx->xer_ca; R(3) = (uint32_t)t; ctx->xer_ca = (uint32_t)(t >> 32); }
}
/* isIceSlipAnmPlay: on ice, no walk button held, not the penguin */
static void py_isIceSlipAnmPlay(GM_CTX, gptr self) {
    I2_FN(0x8012C5E0u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x800000; CR0(ctx, R(0));
    if (R(0)) {
        R(4) = 0; R(3) = self + PL_KEY;
        BL(0x8012C60Cu, fn_8005E7A0);                                    /* (mKey.buttonWalk(nullptr)) */
        if (CMPS(R(3), 0) == 0) {
            R(0) = gm_u32(self + PL_POWERUP);
            if (CMPS(R(0), 5) != 0) { R(3) = 1; return; }
        }
    }
    R(3) = 0;
}
/* walkActionInit_Wait(blend) */
static void py_walkActionInit_Wait(GM_CTX, gptr self) {
    R(6) = 0; R(5) = 150; R(0) = 8;
    gm_set_u32(self + PL_SUBSTATE, 0); gm_set_u32(self + PL_SUBSTATE_TIMER, 150);
    gm_set_u16(self + PY_WATER_WALK_TIMER, 8);
    VTAIL(self, VT_SET_WAIT_ANM);
}
/* walkActionInit_Move(blend) */
static void py_walkActionInit_Move(GM_CTX, gptr self) {
    R(0) = 1; gm_set_u32(self + PL_SUBSTATE, 1);
    VTAIL(self, VT_SET_WALK_ANM);
}
/* sLib::calcTimer<s16>(timer): count down to 0, the value left */
static void py_calcTimer_s16(GM_CTX, gptr timer) {
    R(4) = (uint32_t)(int16_t)gm_u16(timer);
    if (CMPS(R(4), 0) != 0) { R(0) = R(4) - 1; gm_set_u16(timer, (uint16_t)R(0)); }
    R(3) = (uint32_t)(int16_t)gm_u16(timer);
}
/* sLib::calcTimer<u8>(timer) */
static void py_calcTimer_u8(GM_CTX, gptr timer) {
    R(4) = gm_u8(timer);
    if (CMPS(R(4), 0) != 0) { R(0) = R(4) - 1; gm_set_u8(timer, (uint8_t)R(0)); }
    R(3) = gm_u8(timer);
}
/* setRunOnWaterEffect: running on water - the splash effect */
static void py_setRunOnWaterEffect(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1); R(6) = self;
    R(0) &= 0x20000; CR0(ctx, R(0));
    if (!R(0)) return;
    R(0) = gm_u8(self + AC_DIRECTION); R(5) = R(13) - 25360;            /* (SC_WATER_RUN_EF) */
    R(3) = gm_u8(self + AC_PLAYER_NO); R(4) = self + PL_SMOKE_EFFECT;
    R(0) <<= 2; R(7) = self + AC_POS;
    R(5) = gm_u32(R(5) + R(0)); R(3) = (uint32_t)(int8_t)R(3);
    R(6) = 0; R(8) = 0; R(9) = 0;
    hle_createPlayerEffect__3dEfFiPQ23mEf13levelEffect_cPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c(ctx, base);   /* (b) */
}
/* finalizeState_Turn */
static void py_finalizeState_Turn(GM_CTX, gptr self) {
    I2_FN(0x8012D0C0u);
    R(4) = ST_CAN_SPIN; NV_R(31, self);
    BL(0x8012D0DCu, PL_offStatus);
    R(3) = self; OFF_STATUS(0x8012D0E8u, ST_A2);
    R(3) = self; BL(0x8012D0F0u, PL_fadeOutTurnEffect);
}
/* setTurnSmokeEffect: the brake smoke at joint 7, then the base's */
static void py_setTurnSmokeEffect(GM_CTX, gptr self) {
    I2_FN(0x8012D200u);
    gptr sp = gm_frame_sp;
    R(5) = 7; R(4) = sp + 8; NV_R(31, self);
    R(3) = gm_u32(self + PY_MDL);
    BL(0x8012D224u, hle_getJointPos__12dPyMdlBase_cFP7mVec3_ci);
    R(3) = self; R(4) = sp + 8;
    BL(0x8012D230u, PL_setBrakeSmokeEffect);
    R(3) = self; BL(0x8012D238u, PL_setTurnSmokeEffect);
}
/* setCancelCrouch: face the direction, then the base's */
static void py_setCancelCrouch(GM_CTX, gptr self) {
    I2_FN(0x8012DB90u);
    NV_R(31, self);
    R(4) = gm_u8(self + AC_DIRECTION);
    VCALL(0x8012DBB8u, self, VT_GET_MUKI_ANGLE);
    gm_set_u16(self + AC_ANGLE_Y, (uint16_t)R(3));
    R(3) = self; BL(0x8012DBC4u, PL_setCancelCrouch);
}

/* ================================================================== carrying, lifting, throwing */
/* isCarry: something is carried */
static void py_isCarry(GM_CTX, gptr self) {
    R(3) = gm_u32(self + PY_CARRY_ACTOR_ID);
    R(0) = (uint32_t)-(int32_t)R(3); R(0) |= R(3);
    R(3) = R(0) >> 31;                                                   /* (neg / or / rlwinm 1,31,31) */
}
/* the actor carried (fManager_c::searchBaseByID(mCarryActorID)) and a check of it; r3 = it or 0 */
static void py_searchCarry(GM_CTX, gptr self, uint32_t ra) {
    R(3) = gm_u32(self + PY_CARRY_ACTOR_ID);
    BL(ra, hle_search__7fBase_cFUi);
}
/* getCarryPlayer: the player carried */
static void py_getCarryPlayer(GM_CTX, gptr self) {
    I2_FN(0x8012DBE0u);
    py_searchCarry(GM_PASS, self, 0x8012DBF4u);
    if (CMPS(R(3), 0) != 0) {
        R(0) = gm_u8(R(3) + AC_KIND);
        if (CMPU(R(0), 1) == 0) return;
    }
    R(3) = 0;
}
/* getCarryPropelBlock: the propeller block carried */
static void py_getCarryPropelBlock(GM_CTX, gptr self) {
    I2_FN(0x8012DC20u);
    py_searchCarry(GM_PASS, self, 0x8012DC34u);
    if (CMPS(R(3), 0) != 0) {
        R(0) = gm_u16(R(3) + AC_PROF_NAME);
        if (CMPU(R(0), PROF_AC_PROP_BLOCK) == 0) return;
    }
    R(3) = 0;
}
/* getCarryPropelActor: a propeller player or propeller block carried */
static void py_getCarryPropelActor(GM_CTX, gptr self) {
    I2_FN(0x8012DC60u);
    py_searchCarry(GM_PASS, self, 0x8012DC74u);
    if (CMPS(R(3), 0) != 0) {
        R(0) = gm_u8(R(3) + AC_KIND);
        if (CMPU(R(0), 1) == 0) {
            R(0) = gm_u32(R(3) + PL_POWERUP);
            if (CMPS(R(0), 4) == 0) return;
        } else {
            R(0) = gm_u16(R(3) + AC_PROF_NAME);
            if (CMPU(R(0), PROF_AC_PROP_BLOCK) == 0) return;
        }
    }
    R(3) = 0;
}
/* getCarryHardBlock: a light block or propeller block carried */
static void py_getCarryHardBlock(GM_CTX, gptr self) {
    I2_FN(0x8012DCC0u);
    py_searchCarry(GM_PASS, self, 0x8012DCD4u);
    if (CMPS(R(3), 0) != 0) {
        R(4) = gm_u16(R(3) + AC_PROF_NAME); R(4) += 0x10000;
        R(0) = (R(4) - PROF_AC_LIGHT_BLOCK) & 0xFFFF;
        if (CMPU(R(0), 1) <= 0) return;
    }
    R(3) = 0;
}
/* isLiftUp: carrying, and the lift-up is done */
static void py_isLiftUp(GM_CTX, gptr self) {
    I2_FN(0x8012DD10u);
    NV_R(31, self);
    VCALL(0x8012DD34u, self, VT_IS_CARRY);
    if (CMPS(R(3), 0) != 0) {
        R(0) = gm_u32(self + PY_LIFT_M1308);
        if (CMPS(R(0), 0) == 0) { R(3) = 1; return; }
    }
    R(3) = 0;
}
/* getLiftUpOffset: m_1304 * the lift-up height for the tall type (f1) */
static void py_getLiftUpOffset(GM_CTX, gptr self) {
    I2_FN(0x8012DE20u);
    R(4) = (uint32_t)-1; NV_R(31, self);
    VCALL(0x8012DE48u, self, VT_GET_TALL_TYPE);
    R(0) = R(3) & 0xFF;
    R(0) = (uint32_t)((int32_t)R(0) * 12);
    LDF(0, self + PY_LIFT_OFFSET);
    R(3) = LIFT_UP_POS_DATA + R(0);
    LDF(1, R(3) + 36);
    FS(1, F(0) * F(1));
}
/* clearSpinLiftUpReserve */
static void py_clearSpinLiftUpReserve(GM_CTX, gptr self) {
    LDF(0, R(2) - 22616);                                                /* (256.0f) */
    R(0) = 0; gm_set_u32(self + PY_LIFT_RESERVE_ID, 0);
    STF(self + PY_LIFT_RESERVE_M, 0);
}
/* initializeThrowCommon */
static void py_initializeThrowCommon(GM_CTX, gptr self) {
    I2_FN(0x8012E940u);
    NV_R(31, self);
    BL(0x8012E958u, hle_fn_8012E820);                                        /* (initializeThrowCommonBase) */
    R(3) = self; ON_STATUS(0x8012E964u, ST_AA);
    R(3) = self; ON_STATUS(0x8012E970u, ST_97);
}
/* finalizeState_LiftUp: no lift-up statuses, the offset back to 1, face the direction */
static void py_finalizeState_LiftUp(GM_CTX, gptr self) {
    I2_FN(0x8012F460u);
    R(4) = ST_97; NV_R(31, self);
    BL(0x8012F47Cu, PL_offStatus);
    R(3) = self; OFF_STATUS(0x8012F488u, ST_46);
    LDF(0, R(2) - 22780);                                                /* (1.0f) */
    R(3) = self; STF(self + PY_LIFT_OFFSET, 0);
    R(4) = gm_u8(self + AC_DIRECTION);
    VCALL(0x8012F4A8u, self, VT_GET_MUKI_ANGLE);
    gm_set_u16(self + AC_ANGLE_Y, (uint16_t)R(3));
}
/* checkCarryActor(player): we carry that player and it rides us */
static void py_checkCarryActor(GM_CTX, gptr self, gptr player) {
    R(5) = gm_u32(self + PY_CARRY_ACTOR_ID); R(0) = gm_u32(player + AC_UNIQUE_ID);
    if (CMPS(R(5), R(0)) == 0) {
        R(4) = gm_u32(player + PL_RIDE_ACTOR_ID); R(0) = gm_u32(self + AC_UNIQUE_ID);
        if (CMPS(R(4), R(0)) == 0) { R(3) = 1; return; }
    }
    R(3) = 0;
}
/* getRideYoshi / getRidePlayer: the Yoshi / player ridden (by status) */
static void py_getRide(GM_CTX, gptr self, uint32_t flag, uint32_t ra_test, uint32_t ra_search) {
    R(4) = flag; NV_R(31, self);
    BL(ra_test, PL_testFlag);
    if (CMPS(R(3), 0) != 0) { R(3) = gm_u32(self + PL_RIDE_ACTOR_ID); BL(ra_search, hle_search__7fBase_cFUi); }
    else R(3) = 0;
}
static void py_getRideYoshi(GM_CTX, gptr self) {
    I2_FN(0x80139950u);
    py_getRide(GM_PASS, self, ST_RIDE_YOSHI, 0x8013996Cu, 0x8013997Cu);
}
static void py_getRidePlayer(GM_CTX, gptr self) {
    I2_FN(0x8013AAA0u);
    py_getRide(GM_PASS, self, ST_45, 0x8013AABCu, 0x8013AACCu);
}

/* ================================================================== swimming, poles, balloons */
/* setWaterGroundJump: a jump off the ground under water */
static void py_setWaterGroundJump(GM_CTX, gptr self) {
    I2_FN(0x80130BC0u);
    LDF(0, R(2) - 30756);                                                /* (sc_WaterJumpSpeed 1.25f) */
    R(4) = 1; NV_R(31, self);
    STF(self + AC_SPEED_Y, 0);
    BL(0x80130BE4u, hle_fn_80130500);                                        /* (setSwimAction_Swim(1)) */
    R(3) = self; R(4) = SE_PLY_SWIM; R(5) = 0;
    BL(0x80130BF4u, PL_startSound);
    R(0) = 20; gm_set_u8(self + PY_WATER_JUMP_M_B88, 20);
}
/* releasePoleCheck: let go of the pole controller */
static void py_releasePoleCheck(GM_CTX, gptr self) {
    I2_FN(0x80135FC0u);
    NV_R(31, self);
    R(3) = self + PL_PC;
    BL(0x80135FDCu, hle_release__5dPc_cFv);
    R(0) = 0; gm_set_u8(self + PL_PC_M2D, 0);
}
/* isNotBalloonCourse: the character has no lives left (mRest <= 0: cntlzw / rlwnm) */
static void py_isNotBalloonCourse(GM_CTX, gptr self) {
    R(0) = gm_u8(self + AC_PLAYER_NO);
    uint32_t type_tab = g_mod_on ? PY_TYPE_MOD : PY_TYPE_GAME, rest_tab = g_mod_on ? PY_REST_MOD : PY_REST_GAME;
    R(5) = type_tab; R(4) = rest_tab;
    R(3) = 1; R(0) = (uint32_t)(int8_t)R(0);
    R(0) <<= 2;
    R(0) = gm_u32(R(5) + R(0)); R(0) <<= 2;
    R(0) = gm_u32(R(4) + R(0));
    R(0) = cntlzw(R(0));
    R(3) = i2_rotl(R(3), R(0) & 31) & 1;
}

/* ================================================================== eating, propeller */
/* setEatTongue: changeState(StateID_PlayerEat, 0) */
static void py_setEatTongue(GM_CTX, gptr self) {
    R(12) = gm_u32(self + AC_VTABLE); R(4) = STATE_PLAYER_EAT; R(5) = 0;
    R(12) = gm_u32(R(12) + VT_CHANGE_STATE); ctx->ctr = R(12);
    ppc_call_indirect(ctx, base, ctx->ctr);
}
/* resetPropelFlyTime */
static void py_resetPropelFlyTime(GM_CTX, gptr self) {
    R(0) = (uint32_t)(int16_t)gm_u16(self + PY_PROPEL_FLY_TIME);
    if (CMPS(R(0), 0) != 0) return;
    R(0) = 1; gm_set_u16(self + PY_PROPEL_FLY_TIME, 1);
}
/* setPropelActionFly: the fly substate and its rumble */
static void py_setPropelActionFly(GM_CTX, gptr self) {
    I2_FN(0x8013C660u);
    NV_R(31, self);
    BL(0x8013C678u, hle_fn_8013C520);                                        /* (setPropelActionFlyInit) */
    R(3) = 1; R(0) = 50;
    gm_set_u32(self + PL_SUBSTATE, 1);
    gm_set_u32(self + PY_PROPEL_M2EC, 50);
    R(4) = RUMBLE_PROPEL_FLY;
    VCALL(0x8013C6A4u, self, VT_START_RUMBLE);
}
/* endPropelFlyPartsMove: the propeller parts (also a carried propeller's) stop */
static void py_endPropelFlyPartsMove(GM_CTX, gptr self) {
    I2_FN(0x8013D010u);
    NV_R(31, self);
    BL(0x8013D028u, hle_fn_8012DC60);                                    /* (getCarryPropelActor) */
    if (CMPS(R(3), 0) != 0) {
        R(3) = gm_u32(R(3) + AC_PROPEL_PARTS); R(4) = (uint32_t)(int16_t)gm_u16(self + PY_PROPEL_ROLL_SPD);
        BL(0x8013D03Cu, finalizePropelFly__14dPropelParts_cFs_800D8510);
    }
    R(3) = gm_u32(self + AC_PROPEL_PARTS); R(4) = (uint32_t)(int16_t)gm_u16(self + PY_PROPEL_ROLL_SPD);
    BL(0x8013D048u, finalizePropelFly__14dPropelParts_cFs_800D8510);
}
/* setPropelFallSpinEffect: the sound, the effect on */
static void py_setPropelFallSpinEffect(GM_CTX, gptr self) {
    I2_FN(0x8013D1E0u);
    R(4) = SE_PLY_PRPL_LETDOWN_SPIN; R(5) = 0; NV_R(31, self);
    BL(0x8013D200u, PL_startSound);
    R(0) = gm_u32(self + PY_FALL_SPIN_EF);
    if (CMPS(R(0), 0) == 0) { R(0) = 1; gm_set_u32(self + PY_FALL_SPIN_EF, 1); }
}
/* stopPropelFallSpinEffect */
static void py_stopPropelFallSpinEffect(GM_CTX, gptr self) {
    I2_FN(0x8013D3B0u);
    NV_R(31, self);
    R(12) = gm_u32(self + PY_FOLLOW_EF); R(12) = gm_u32(R(12) + EF_KILL); ctx->ctr = R(12);
    R(3) = self + PY_FOLLOW_EF;
    ctx->lr = 0x8013D3D8u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(0) = 0; gm_set_u32(self + PY_FALL_SPIN_M53C, 0); gm_set_u32(self + PY_FALL_SPIN_EF, 0);
}

/* ================================================================== demos */
/* finalizeState_DemoDown: mMaxFallSpeed = sc_MaxFallSpeed */
static void py_finalizeState_DemoDown(GM_CTX, gptr self) {
    LDF(0, R(2) - 30748);                                                /* (-4.0f) */
    STF(self + AC_MAX_FALL_SPEED, 0);
}
/* finalizeState_DemoInDoor */
static void py_finalizeState_DemoInDoor(GM_CTX, gptr self) {
    R(0) = 0;
    gm_set_u32(self + PL_DAMAGE_INVULN, 0); gm_set_u32(self + PL_CHANGE_INVULN, 0);
    gm_set_u32(self + PY_M74, 0); gm_set_u32(self + PL_RELATED_ACTOR_ID, 0);
}
/* setDemoInDoor_Walk */
static void py_setDemoInDoor_Walk(GM_CTX, gptr self) {
    I2_FN(0x8013EA50u);
    R(4) = ST_INVISIBLE; NV_R(31, self);
    BL(0x8013EA6Cu, PL_offStatus);
    R(3) = 4; R(0) = 10;
    gm_set_u32(self + PL_DEMO_SUBSTATE, 4); gm_set_u32(self + PL_DEMO_SUBSTATE_T, 10);
}
/* initDemoOutDokan: the base's; drop a carried player; the player we ride lets go of us */
static void py_initDemoOutDokan(GM_CTX, gptr self) {
    I2_FN(0x80140C30u);
    NV_R(31, self);
    BL(0x80140C48u, PL_initDemoOutDokan);
    R(3) = self; BL(0x80140C50u, hle_fn_8012DBE0);                      /* (getCarryPlayer) */
    if (CMPS(R(3), 0) != 0) { R(3) = self; BL(0x80140C60u, hle_fn_8012E5A0); }   /* (releaseCarryActor) */
    R(3) = self; BL(0x80140C68u, hle_fn_8013AAA0);                      /* (getRidePlayer) */
    if (CMPS(R(3), 0) != 0) { R(4) = self; BL(0x80140C78u, hle_fn_8012E510); }   /* (ridePlayer->cancelCarry(this)) */
}
/* setChange(mode): the power-up change - its init (by a pointer to member function), update, cc */
static void py_setChange(GM_CTX, gptr self, uint32_t mode) {
    I2_FN(0x80141460u);
    R(5) = 0x80320000u;
    R(0) = mode & 0xFF; R(0) = (uint32_t)(int8_t)R(0);
    R(5) = L_CHANGE_INIT_PROC;
    R(0) = (uint32_t)((int32_t)R(0) * 12);
    NV_R(31, self);
    gm_set_u8(self + PY_CHANGE_TYPE, (uint8_t)mode);
    R(12) = R(5) + R(0);
    BL(0x80141494u, __ptmf_scall_802DCBFC);
    R(3) = self; BL(0x801414A0u, hle_fn_801414C0);                          /* (updateChange) */
    R(3) = self; BL(0x801414A8u, hle_fn_80142030);                          /* (setCcData) */
}
/* fn_801416c0(powerup): mPowerupCopy2 = powerup; setPowerup(powerup, 0) */
static void py_fn_801416c0(GM_CTX, gptr self, uint32_t powerup) {
    gm_set_u32(self + PL_POWERUP_COPY2, powerup);
    R(5) = 0;
    VTAIL(self, VT_SET_POWERUP);
}

/* ================================================================== collision data */
/* setCcDataDirect: the body cc from the power-up's size data */
static void py_setCcDataDirect(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_POWERUP); R(5) = 0x802F0000u; R(4) = 0x80320000u;
    LDF(1, self + PY_CC_M1598);
    R(0) <<= 2; R(5) = L_MODE_CC_SIZE;
    R(0) = gm_u32(R(5) + R(0));
    R(4) = L_CC_SIZE_DATA;
    LDF(0, self + PY_CC_M1598 + 4);
    R(0) <<= 2;
    R(4) = gm_u32(R(4) + R(0));
    LDF(3, R(4));
    STF(self + PL_CC_M0C, 3);
    LDF(2, R(4) + 4);
    FS(1, F(2) + F(1));
    STF(self + AC_CC_OFFSET, 3);
    FS(0, F(0) + F(1));
    STF(self + PL_CC_M0C + 4, 0);
    STF(self + AC_CC_OFFSET + 4, 0);
    LDF(1, R(4) + 12); LDF(0, R(4) + 8);
    STF(self + AC_CC_OFFSET + 8, 0); STF(self + AC_CC_OFFSET + 12, 1);
}
/* setCcAtSpin: the spin attack's cc */
static void py_setCcAtSpin(GM_CTX, gptr self) {
    LDF(1, self + PL_MODEL_HEIGHT); R(5) = 11;
    LDF(0, R(2) - 22804);                                                /* (4.0f) */
    R(4) = 2048;
    R(0) = gm_u32(self + PL_ATT_CC1_VS_KIND);
    FS(2, F(0) + F(1));
    LDF(1, R(2) - 22812);                                                /* (0.5f) */
    LDF(3, self + AC_CC_OFFSET + 8);
    R(6) = R(0) | 2;
    LDF(0, R(2) - 22728);                                                /* (3.5f) */
    FS(2, F(2) * F(1));
    FS(0, F(0) * F(3));
    R(0) = gm_u32(self + AC_CC_VS_DAMAGE);
    LDF(1, self + AC_CC_OFFSET);
    R(0) &= 0xFFFFF7FFu;
    STF(self + PL_ATT_CC1, 1); STF(self + PL_ATT_CC1 + 4, 2);
    STF(self + PL_ATT_CC1 + 8, 0); STF(self + PL_ATT_CC1 + 12, 2);
    gm_set_u32(self + PL_ATT_CC1_VS_KIND, R(6));
    gm_set_u8(self + PL_ATT_CC1_ATTACK, 11);
    gm_set_u32(self + PL_ATT_CC1_VS_DMG, 2048);
    gm_set_u32(self + AC_CC_VS_DAMAGE, R(0));
}
/* setCcAtSpinFall: the spin fall's attack cc (then setCcAtBody(CC_ATTACK_SPIN_FALL)) */
static void py_setCcAtSpinFall(GM_CTX, gptr self) {
    LDF(1, R(2) - 22784);                                                /* (10.0f) */
    R(0) = 13;
    LDF(2, R(2) - 22824);                                                /* (0.0f) */
    R(4) = 13;
    LDF(0, R(2) - 22600);                                                /* (12.0f) */
    STF(self + PL_ATT_CC1, 2); STF(self + PL_ATT_CC1 + 4, 1);
    STF(self + PL_ATT_CC1 + 8, 0); STF(self + PL_ATT_CC1 + 12, 1);
    gm_set_u8(self + PL_ATT_CC1_ATTACK, 13);
    PL_setCcAtBody(ctx, base);                                           /* (b) */
}
/* getCcBounds(bounds): the spin lift-up's range for the power-up */
static void py_getCcBounds(GM_CTX, gptr self, gptr bounds) {
    R(0) = gm_u32(self + PL_POWERUP);
    LDF(3, R(2) - 22228);                                                /* (18.0f) */
    if (CMPS(R(0), 3) == 0) LDF(3, R(2) - 22736);                        /* (the mini: 8.0f) */
    else if (CMPS(R(0), 0) == 0) LDF(3, R(2) - 22604);                   /* (small: 16.0f) */
    if (CMPS(bounds, 0) == 0) return;
    LDF(2, self + PL_MODEL_HEIGHT); LDF(1, R(2) - 22804);                /* (4.0f) */
    LDF(0, R(2) - 22824);                                                /* (0.0f) */
    FS(2, F(1) + F(2));
    LDF(1, R(2) - 22812);                                                /* (0.5f) */
    STF(bounds, 0);
    FS(0, F(2) * F(1));
    STF(bounds + 8, 3); STF(bounds + 4, 0); STF(bounds + 12, 0);
}
/* setCcAtSpinLiftUp: the attack cc from getCcBounds, then the roof check */
static void py_setCcAtSpinLiftUp(GM_CTX, gptr self) {
    I2_FN(0x80141FD0u);
    gptr sp = gm_frame_sp;
    R(4) = sp + 8; NV_R(31, self);
    BL(0x80141FECu, hle_fn_80141F70);
    LDF(0, sp + 8); R(0) = 18;
    STF(self + PL_ATT_CC1, 0);
    R(3) = self;
    LDF(0, sp + 12); STF(self + PL_ATT_CC1 + 4, 0);
    LDF(0, sp + 16); STF(self + PL_ATT_CC1 + 8, 0);
    LDF(0, sp + 20); STF(self + PL_ATT_CC1 + 12, 0);
    gm_set_u8(self + PL_ATT_CC1_ATTACK, 18);
    BL(0x8014201Cu, hle_fn_8012E360);                                        /* (checkSpinLiftUpRoofHeight) */
}
/* initCcData: initCollision(scCcData, scAtCcData) */
static void py_initCcData(GM_CTX, gptr self) {
    (void)self;
    R(4) = 0x802F0000u; R(5) = 0x802F0000u;
    R(4) = SC_CC_DATA; R(5) = SC_AT_CC_DATA;
    PL_initCollision(ctx, base);                                         /* (b) */
}

/* ================================================================== background collision data */
/* getBgPointData_Powerup(powerup, index): &scBgPointData[powerup][index] */
static void py_getBgPointData_Powerup(GM_CTX, uint32_t powerup, uint32_t index) {
    R(3) = 0x80320000u;
    R(4) = powerup << 2;
    R(3) = SC_BG_POINT_DATA;
    R(0) = index << 6;
    R(3) = gm_u32(R(3) + R(4));
    R(3) = R(3) + R(0);
}
/* getStandHeadBgPointY: the head's offset (4096ths) standing, as a float (f1) */
static void py_getStandHeadBgPointY(GM_CTX, gptr self) {
    I2_FN(0x80142530u);
    gptr sp = gm_frame_sp;
    R(5) = 0; R(4) = gm_u32(self + PL_POWERUP);
    BL(0x80142548u, hle_fn_80142510);
    R(3) = gm_u32(R(3) + 28);
    R(0) = 0x43300000u; gm_set_u32(sp + 8, R(0));
    R(0) = R(3) ^ 0x80000000u;
    ctx->f[2].u = ld64(base, R(2) - 22752);                              /* (lfd: 2^52 + 2^31) */
    gm_set_u32(sp + 12, R(0));
    LDF(0, R(2) - 22760);                                                /* (4096.0f) */
    ctx->f[1].u = ld64(base, sp + 8);
    FS(1, F(1) - F(2));
    FS(1, F(1) / F(0));
}
/* initBcData: mBc.init(), setBcData(1), no background crossing now or before */
static void py_initBcData(GM_CTX, gptr self) {
    I2_FN(0x801434E0u);
    NV_R(31, self);
    R(3) = self + AC_BC;
    BL(0x801434FCu, init__5dBc_cFv_8006CFE0);
    R(3) = self; R(4) = 1;
    BL(0x80143508u, hle_fn_80142660);                                        /* (setBcData) */
    R(0) = 0;
    gm_set_u32(self + PL_NOW_BG_CROSS1 + 4, 0); gm_set_u32(self + PL_NOW_BG_CROSS1, 0);
    gm_set_u32(self + PL_OLD_BG_CROSS1 + 4, 0); gm_set_u32(self + PL_OLD_BG_CROSS1, 0);
}
/* maxFallSpeedSet: -2.5 as the mini (isMameAction), else sc_MaxFallSpeed */
static void py_maxFallSpeedSet(GM_CTX, gptr self) {
    I2_FN(0x80143530u);
    NV_R(31, self);
    BL(0x80143548u, PL_isMameAction);
    if (CMPS(R(3), 0) != 0) LDF(0, R(2) - 22356);                        /* (-2.5f) */
    else LDF(0, R(2) - 30748);                                           /* (-4.0f) */
    STF(self + AC_MAX_FALL_SPEED, 0);
}

/* ================================================================== the actor */
/* dAcPy_c's profile: new dAcPy_c (fn_801442B0: the constructor) */
static void py_classInit(GM_CTX) {
    I2_FN(0x80144280u);
    R(3) = PY_SIZE;
    BL(0x80144294u, hle_AllocateMemoryBlock);
    if (CMPS(R(3), 0) != 0) BL(0x801442A0u, fn_801442B0);
}
/* preExecute: a rider takes its Yoshi's execution-stop mask for the base's preExecute */
static void py_preExecute(GM_CTX, gptr self) {
    I2_FN(0x80145040u);
    NV_R(30, self);
    NV_R(31, gm_u8(self + AC_EXEC_STOP_MASK));
    BL(0x80145060u, hle_getYoshi__7dAcPy_cFv);                          /* (getRideYoshi) */
    if (CMPS(R(3), 0) != 0) { R(0) = gm_u8(R(3) + AC_EXEC_STOP_MASK); gm_set_u8(self + AC_EXEC_STOP_MASK, (uint8_t)R(0)); }
    R(3) = self;
    BL(0x80145078u, PL_preExecute);
    gm_set_u8(self + AC_EXEC_STOP_MASK, (uint8_t)R(31));
}
/* getModelScaleBase(): mScale * mAmiRelated2 (the result through r3) */
static void py_getModelScaleBase(GM_CTX, gptr out, gptr self) {
    LDF(3, self + PY_AMI_RELATED2);
    LDF(2, self + AC_SCALE + 8); LDF(1, self + AC_SCALE + 4); LDF(0, self + AC_SCALE);
    FS(2, F(2) * F(3)); FS(1, F(1) * F(3)); FS(0, F(0) * F(3));
    STF(out + 8, 2); STF(out, 0); STF(out + 4, 1);
}
/* setVirusStar(other): the longer star time passes to the other player (setStar(1, timer)) */
static void py_setVirusStar(GM_CTX, gptr self, gptr other) {
    if (CMPS(other, 0) == 0) return;
    R(5) = gm_u32(self + PL_STAR_TIMER); R(0) = gm_u32(other + PL_STAR_TIMER);
    int c = CMPS(R(5), R(0));
    if (c == 0) return;
    if (c > 0) {
        R(12) = gm_u32(other + AC_VTABLE); R(3) = other; R(4) = 1;
        R(12) = gm_u32(R(12) + VT_SET_STAR); ctx->ctr = R(12);
    } else {
        R(12) = gm_u32(self + AC_VTABLE); R(5) = R(0); R(4) = 1;
        R(12) = gm_u32(R(12) + VT_SET_STAR); ctx->ctr = R(12);
    }
    ppc_call_indirect(ctx, base, ctx->ctr);                              /* (bctr) */
}
/* setWaterWalkFlag: the mini out of the water can walk on it */
static void py_setWaterWalkFlag(GM_CTX, gptr self) {
    I2_FN(0x80145E40u);
    NV_R(31, self);
    BL(0x80145E58u, PL_isMameAction);
    if (CMPS(R(3), 0) == 0) return;
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
    if (R(0)) return;
    R(3) = self; ON_STATUS(0x80145E78u, ST_CAN_WATER_WALK);
}
/* getTallType(powerup): l_tall_type[powerup] (-1: the current; the table is a local copy) */
static void py_getTallType(GM_CTX, gptr self, uint32_t powerup) {
    R(0) = (uint32_t)(int8_t)powerup;
    GM_FRAME(16);
    gptr sp = gm_frame_sp;
    R(6) = gm_u32(R(2) - 22196);
    int c = CMPS(R(0), -1);
    R(5) = gm_u16(R(2) - 22192); R(0) = gm_u8(R(2) - 22190);
    gm_set_u32(sp + 8, R(6)); gm_set_u16(sp + 12, (uint16_t)R(5)); gm_set_u8(sp + 14, (uint8_t)R(0));
    if (c == 0) { R(0) = gm_u32(self + PL_POWERUP); R(4) = (uint32_t)(int8_t)R(0); }
    R(0) = (uint32_t)(int8_t)R(4);
    R(3) = sp + 8;
    R(3) = gm_u8(R(3) + R(0));
}
/* setPlayerData: the visible area (setVisibleArea(l_player_cull_data[0], [1]), inlined) */
static void py_setPlayerData(GM_CTX, gptr self) {
    R(5) = 0x802F0000u; R(4) = L_PLAYER_CULL;
    LDF(3, L_PLAYER_CULL); LDF(2, R(4) + 4); LDF(0, R(4) + 12); LDF(1, R(4) + 8);
    STF(self + AC_VISIBLE_OFFSET, 3); STF(self + AC_VISIBLE_OFFSET + 4, 2);
    STF(self + AC_VISIBLE_SIZE, 1); STF(self + AC_VISIBLE_SIZE + 4, 0);
}
/* setSpeedData: the speed tables for the power-up */
static void py_setSpeedData(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_POWERUP); R(5) = 0x802F0000u; R(4) = 0x80370000u;
    R(0) <<= 2; R(5) = SC_SPEED_HIO_DATA;
    R(0) = gm_u32(R(5) + R(0));
    R(4) = M_SPEED_HIO;
    R(0) &= 0xFF; R(0) = (uint32_t)((int32_t)R(0) * 240);
    R(4) = R(4) + R(0);
    gm_set_u32(self + PL_SPEED_DATA, R(4));
    R(0) = R(4) + 120; gm_set_u32(self + PL_SPEED_DATA + 4, R(0));
}
/* setModeGravity: the gravity table for the power-up (the mini's own) */
static void py_setModeGravity(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_POWERUP); R(4) = 0;
    if (CMPS(R(0), 3) == 0) R(4) = 1;
    R(0) = (uint32_t)((int32_t)R(4) * 72);
    R(4) = POWER_CHANGE_DATA + R(0);
    R(0) = R(4) + 152; gm_set_u32(self + PL_GRAVITY_DATA, R(0));
}
/* getGravityData: the mini's (isMameAction) or the normal gravity table */
static void py_getGravityData(GM_CTX, gptr self) {
    I2_FN(0x80146770u);
    BL(0x80146780u, PL_isMameAction);
    R(4) = 0x802F0000u;
    int c = CMPS(R(3), 0);
    R(4) = POWER_CHANGE_DATA; R(3) = R(4) + 152;
    if (c != 0) R(3) = R(4) + 224;
}
/* setScrollMode(mode): an item Toad's is always 1 */
static void py_setScrollMode(GM_CTX, gptr self, uint32_t mode) {
    I2_FN(0x80147250u);
    NV_R(31, mode); NV_R(30, self);
    VCALL(0x8014727Cu, self, VT_IS_ITEM_KINOPIO);
    if (CMPS(R(3), 0) == 0) gm_set_u8(self + PY_SCROLL_MODE, (uint8_t)R(31));
    else { R(0) = 1; gm_set_u8(self + PY_SCROLL_MODE, 1); }
}
/* setInvalidKeyTimer(a, b): the keys off for a while */
static void py_setInvalidKeyTimer(GM_CTX, gptr self, uint32_t a, uint32_t b) {
    gm_set_u32(self + PY_KEY_TIMER_A, a);
    R(4) = 1;
    gm_set_u32(self + PY_KEY_TIMER_B, b);
    R(3) = self + PL_KEY;
    setFlag__14dPlayerInput_cFQ214dPlayerInput_c5Flags_8005E3B0(ctx, base);   /* (b: mKey.onStatus(STATUS_NO_INPUT)) */
}
/* startQuakeShock(type) / startPatternRumble(pattern): the base's, and the carried player's */
static void py_passOnToCarried(GM_CTX, gptr self, uint32_t arg, uint32_t ra0, gm_native_fn fn, uint32_t ra1, uint32_t ra2, uint32_t slot) {
    NV_R(31, arg); NV_R(30, self);
    BL(ra0, fn);
    R(3) = self; BL(ra1, hle_fn_8012DBE0);                              /* (getCarryPlayer) */
    if (CMPS(R(3), 0) != 0) {
        R(12) = gm_u32(R(3) + AC_VTABLE); R(4) = R(31);
        R(12) = gm_u32(R(12) + slot); ctx->ctr = R(12);
        ctx->lr = ra2; ppc_call_indirect(ctx, base, ctx->ctr);
    }
}
static void py_startQuakeShock(GM_CTX, gptr self, uint32_t type) {
    I2_FN(0x801473F0u);
    py_passOnToCarried(GM_PASS, self, type, 0x80147410u, PL_startQuakeShock, 0x80147418u, 0x80147434u, VT_START_QUAKE);
}
static void py_startPatternRumble(GM_CTX, gptr self, uint32_t pattern) {
    I2_FN(0x80147450u);
    py_passOnToCarried(GM_PASS, self, pattern, 0x80147470u, PL_startPatternRumble, 0x80147478u, 0x80147494u, VT_START_RUMBLE);
}
/* setItemGetEffect: the power-up glow (90 frames, from an item) */
static void py_setItemGetEffect(GM_CTX, gptr self) {
    R(4) = 90; R(0) = 0;
    gm_set_u32(self + PY_POWERUP_EF_TIMER, 90); gm_set_u32(self + PY_POWERUP_TYPE, 0);
}
/* isDrawingCarryFukidashi: the carry hint bubble - the hint allowed, on the ground, nothing carried */
static void py_isDrawingCarryFukidashi(GM_CTX, gptr self) {
    I2_FN(0x80147B60u);
    NV_R(31, self);
    BL(0x80147B78u, hle_fn_80147A80);                                        /* (isDrawingFukidashi) */
    if (CMPS(R(3), 0) != 0) {
        R(3) = self + AC_BC;
        BL(0x80147B88u, isFoot__5dBc_cFv_80070CB0);
        if (CMPS(R(3), 0) != 0) {
            R(3) = gm_u32(self + PY_CARRY_ACTOR_ID);
            BL(0x80147B98u, hle_search__7fBase_cFUi);
            if (CMPS(R(3), 0) == 0) { R(3) = 1; return; }
        }
    }
    R(3) = 0;
}

/* ================================================================== the virtual states' base IDs
   (STATE_VIRTUAL_DEFINE's baseID_<name><daPlBase_c>(): the parent state, for the static
   initialiser) */
#define BASE_ID_STATE_DEMO_DOWN 0x80354B2Cu   /* daPlBase_c::StateID_DemoDown ... */
#define BASE_ID_STATE_CLOUD     0x803545DCu
#define BASE_ID_STATE_KANI      0x8035459Cu
#define BASE_ID_STATE_SWIM      0x8035449Cu
#define BASE_ID_STATE_HIP_ATTACK 0x8035445Cu
#define BASE_ID_STATE_TURN      0x8035441Cu
#define BASE_ID_STATE_SLIP      0x803543DCu
#define BASE_ID_STATE_SIT_JUMP  0x803542DCu
#define BASE_ID_STATE_CROUCH    0x8035439Cu
#define BASE_ID_STATE_LAND      0x8035435Cu
#define BASE_ID_STATE_FALL      0x8035431Cu
#define BASE_ID_STATE_JUMP      0x8035429Cu
#define BASE_ID_STATE_WALK      0x8035425Cu
static void py_baseID(GM_CTX, uint32_t id) { R(3) = 0x80350000u; R(3) = id; }

/* ================================================================== hle entry points
   RT_GM_REACH=1 logs each entry's first call (the reach list). Verified memory: the object (and the
   arguments' memory); calls that play sounds / effects / rumble or allocate change more - for those
   RT_GM_VERIFY's double run is for the registers only and the strict A/B is the test. */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
#define PL_MEM SELF, PY_SIZE
static void pa_reached(const char *name) {
    static int on = -1; if (on < 0) on = getenv("RT_GM_REACH") != NULL;
    if (on) rt_log("gm", "reached %s (frame %llu)", name, (unsigned long long)g_frames_presented);
}
#define PA_HLE(name, flags, ...) \
    static void name##_native(ppc_context *ctx, uint8_t *base); \
    GM_HLE(name) { static int seen_; if (!seen_) { seen_ = 1; pa_reached(#name); } \
                   if (gm_verifying()) { const gptr r_[] = { __VA_ARGS__ }; \
                       gm_verify(#name, ctx, base, PA_NATIVE(name), orig_##name, r_, (int)(sizeof r_ / sizeof *r_) / 2, (flags)); } \
                   else name##_native(ctx, base); } \
    static void name##_native(ppc_context *ctx, uint8_t *base)
#ifdef PA_CONTROL                         /* (a control build: the PowerPC version against itself, for the
                                             verifier's double-run artifacts) */
#define PA_NATIVE(name) orig_##name
#else
#define PA_NATIVE(name) name##_native
#endif
#define PA_VOID(name, ...) PA_HLE(name, 0, __VA_ARGS__)
#define PA_INT(name, ...)  PA_HLE(name, GMV_RET, __VA_ARGS__)
static void pa_selftest(GM_CTX, gptr self);

/* All on (every one is reached by the A/B inputs; RT_GM_REACH=1 logs the first calls). */
/* hip attack, jumps, spins */
PA_INT (fn_801267B0, PL_MEM) { pa_selftest(GM_PASS, SELF); py_isCarry(GM_PASS, SELF); }
PA_VOID(fn_801267D0, PL_MEM) { py_setHipAttack_AttackStart(GM_PASS, SELF); }
PA_VOID(fn_80126810, PL_MEM) { py_initializeState_HipAttack(GM_PASS, SELF); }
PA_VOID(fn_80126860, PL_MEM) { py_finalizeState_HipAttack(GM_PASS, SELF); }
PA_VOID(fn_801268A0, PL_MEM) { py_executeState_HipAttack(GM_PASS, SELF); }
PA_VOID(fn_80127410, PL_MEM) { py_calcJumpCount(GM_PASS, SELF); }
PA_VOID(fn_801275B0, PL_MEM) { py_setJumpSpeed(GM_PASS, SELF); }
PA_VOID(fn_80128D20, PL_MEM) { py_finalizeState_WallJump(GM_PASS, SELF); }
PA_VOID(fn_801291F0, PL_MEM) { py_endSpinJumpEffect(GM_PASS, SELF); }
PA_INT (fn_801298B0, PL_MEM) { py_isMissSpinEnableAnm(GM_PASS, SELF); }
PA_INT (fn_80129910, PL_MEM) { py_getMissSpinAngle(GM_PASS, SELF); }
PA_VOID(fn_80129950, PL_MEM) { py_setMissSpin(GM_PASS, SELF); }
PA_VOID(fn_801299B0, PL_MEM) { py_resetMissSpin(GM_PASS, SELF); }
PA_VOID(fn_801299C0, PL_MEM) { py_updateMissSpin(GM_PASS, SELF); }
/* slips, walking, turning, crouching */
PA_VOID(fn_8012AB00, PL_MEM) { py_setSlipSE(GM_PASS, SELF); }
PA_VOID(fn_8012AB40, PL_MEM) { py_setSlipEffect(GM_PASS, SELF); }
PA_VOID(fn_8012ABF0, PL_MEM) { py_initializeState_Slip(GM_PASS, SELF); }
PA_VOID(fn_8012AC40, PL_MEM) { py_finalizeState_Slip(GM_PASS, SELF); }
PA_VOID(fn_8012AC80, PL_MEM) { PL_executeState_Slip(ctx, base); }    /* (executeState_Slip: b the base's) */
PA_INT (fn_8012BD70, PL_MEM) { py_isWaitFrameCountMax(GM_PASS, SELF); }
PA_INT (fn_8012C5E0, PL_MEM) { py_isIceSlipAnmPlay(GM_PASS, SELF); }
PA_VOID(fn_8012C980, PL_MEM) { py_walkActionInit_Wait(GM_PASS, SELF); }
PA_INT (fn_8012CAD0, A(0), 2) { py_calcTimer_s16(GM_PASS, A(0)); }
PA_VOID(fn_8012CAF0, PL_MEM) { py_walkActionInit_Move(GM_PASS, SELF); }
PA_VOID(fn_8012CF30, PL_MEM) { py_setRunOnWaterEffect(GM_PASS, SELF); }
PA_VOID(fn_8012D0C0, PL_MEM) { py_finalizeState_Turn(GM_PASS, SELF); }
PA_VOID(fn_8012D200, PL_MEM) { py_setTurnSmokeEffect(GM_PASS, SELF); }
PA_INT (fn_8012DB90, PL_MEM) { py_setCancelCrouch(GM_PASS, SELF); }
/* carrying, lifting, throwing */
PA_INT (fn_8012DBE0, PL_MEM) { py_getCarryPlayer(GM_PASS, SELF); }
PA_INT (fn_8012DC20, PL_MEM) { py_getCarryPropelBlock(GM_PASS, SELF); }
PA_INT (fn_8012DC60, PL_MEM) { py_getCarryPropelActor(GM_PASS, SELF); }
PA_INT (fn_8012DCC0, PL_MEM) { py_getCarryHardBlock(GM_PASS, SELF); }
PA_INT (fn_8012DD10, PL_MEM) { py_isLiftUp(GM_PASS, SELF); }
PA_VOID(fn_8012DE20, PL_MEM) { py_getLiftUpOffset(GM_PASS, SELF); }
PA_VOID(fn_8012E120, PL_MEM) { py_clearSpinLiftUpReserve(GM_PASS, SELF); }
PA_VOID(fn_8012E940, PL_MEM) { py_initializeThrowCommon(GM_PASS, SELF); }
PA_VOID(fn_8012E990, PL_MEM) { R(4) = ST_THROW; PL_offStatus(ctx, base); }   /* (finalizeThrowCommonBase: b offStatus) */
PA_INT (aramGetFirstUserAddress, PL_MEM) {                           /* (getWallBgPointData: the symbol is a wrong port) */
    I2_FN(0x8012EDC0u); BL(0x8012EDD0u, hle_fn_80142580); R(3) += 32; }     /* (getBgPointData()->mWall) */
PA_INT (fn_8012EDF0, PL_MEM) {                                       /* (getHeadBgPointData) */
    I2_FN(0x8012EDF0u); BL(0x8012EE00u, hle_fn_80142580); R(3) += 16; }     /* (getBgPointData()->mHead) */
PA_VOID(fn_8012F040, PL_MEM) { hle_fn_8012E940(ctx, base); }          /* (initializeState_Throw: b initializeThrowCommon) */
PA_VOID(fn_8012F050, PL_MEM) { hle_fn_8012E9A0(ctx, base); }              /* (finalizeState_Throw: b finalizeThrowCommon) */
PA_VOID(fn_8012F460, PL_MEM) { py_finalizeState_LiftUp(GM_PASS, SELF); }
PA_INT (fn_8013A150, PL_MEM) { py_checkCarryActor(GM_PASS, SELF, A(1)); }
PA_INT (getYoshi__7dAcPy_cFv, PL_MEM) { py_getRideYoshi(GM_PASS, SELF); }
PA_INT (fn_8013AAA0, PL_MEM) { py_getRidePlayer(GM_PASS, SELF); }
/* swimming, poles, balloons, eating, propeller */
PA_VOID(fn_80130BC0, PL_MEM) { py_setWaterGroundJump(GM_PASS, SELF); }
PA_VOID(sdpu_release_ccb, PL_MEM) { py_releasePoleCheck(GM_PASS, SELF); }   /* (releasePoleCheck: the symbol is a wrong port) */
PA_INT (fn_80138750, PL_MEM) { py_isNotBalloonCourse(GM_PASS, SELF); }
PA_VOID(fn_8013AC50, PL_MEM) { py_setEatTongue(GM_PASS, SELF); }
PA_VOID(fn_8013C380, PL_MEM) { py_resetPropelFlyTime(GM_PASS, SELF); }
PA_VOID(fn_8013C660, PL_MEM) { py_setPropelActionFly(GM_PASS, SELF); }
PA_VOID(fn_8013D010, PL_MEM) { py_endPropelFlyPartsMove(GM_PASS, SELF); }
PA_VOID(fn_8013D1E0, PL_MEM) { py_setPropelFallSpinEffect(GM_PASS, SELF); }
PA_VOID(fn_8013D3B0, PL_MEM) { py_stopPropelFallSpinEffect(GM_PASS, SELF); }
/* demos */
PA_VOID(fn_8013DC20, PL_MEM) { py_finalizeState_DemoDown(GM_PASS, SELF); }
PA_VOID(fn_8013DF40, PL_MEM) { R(4) = ST_INVISIBLE; PL_offStatus(ctx, base); }   /* (finalizeState_DemoFallDown: b offStatus) */
PA_VOID(fn_8013EA30, PL_MEM) { py_finalizeState_DemoInDoor(GM_PASS, SELF); }
PA_VOID(fn_8013EA50, PL_MEM) { py_setDemoInDoor_Walk(GM_PASS, SELF); }
PA_VOID(fn_80140C30, PL_MEM) { py_initDemoOutDokan(GM_PASS, SELF); }
PA_VOID(fn_80140C90, PL_MEM) {                                        /* (initialDoor: changeDemoState(StateID_DemoInDoor, 0)) */
    R(4) = 0x80370000u; R(5) = 0; R(4) = STATE_DEMO_IN_DOOR; PL_changeDemoState(ctx, base); }
PA_VOID(continueFromMpPauseFix2, PL_MEM) { py_setChange(GM_PASS, SELF, A(1)); }   /* (setChange: the symbol is a wrong port) */
PA_VOID(fn_80141580, PL_MEM) { py_fn_801416c0(GM_PASS, SELF, A(1)); }
PA_VOID(fn_801415A0, PL_MEM) { PL_initializeState_DemoStartWait(ctx, base); }   /* (b the base's) */
PA_VOID(fn_80141630, PL_MEM) { PL_finalizeState_DemoStartWait(ctx, base); }     /* (b the base's) */
/* collision data */
PA_VOID(fn_80141E30, PL_MEM) { py_setCcDataDirect(GM_PASS, SELF); }
PA_VOID(fn_80141EE0, PL_MEM) { py_setCcAtSpin(GM_PASS, SELF); }
PA_VOID(fn_80141F40, PL_MEM) { py_setCcAtSpinFall(GM_PASS, SELF); }
PA_VOID(fn_80141F70, PL_MEM, A(1), 16) { py_getCcBounds(GM_PASS, SELF, A(1)); }
PA_VOID(fn_80141FD0, PL_MEM) { py_setCcAtSpinLiftUp(GM_PASS, SELF); }
PA_INT (fn_80142510, PL_MEM) { py_getBgPointData_Powerup(GM_PASS, A(1), A(2)); }
PA_VOID(fn_80142530, PL_MEM) { py_getStandHeadBgPointY(GM_PASS, SELF); }
PA_VOID(fn_801434C0, PL_MEM) { py_initCcData(GM_PASS, SELF); }
PA_VOID(fn_801434E0, PL_MEM) { py_initBcData(GM_PASS, SELF); }
PA_VOID(fn_80143530, PL_MEM) { py_maxFallSpeedSet(GM_PASS, SELF); }
PA_INT (fn_80143880, A(0), 1) { py_calcTimer_u8(GM_PASS, A(0)); }
/* the actor */
PA_INT (fn_80144280, 0x80000000u, 4) { py_classInit(GM_PASS); }
PA_INT (fn_80145040, PL_MEM) { py_preExecute(GM_PASS, SELF); }
PA_VOID(fn_80145980, A(0), 12) { py_getModelScaleBase(GM_PASS, A(0), A(1)); }
PA_VOID(fn_80145DF0, PL_MEM, A(1), PY_SIZE) { py_setVirusStar(GM_PASS, SELF, A(1)); }
PA_VOID(fn_80145E40, PL_MEM) { py_setWaterWalkFlag(GM_PASS, SELF); }
PA_INT (fn_80146580, PL_MEM) { py_getTallType(GM_PASS, SELF, A(1)); }
PA_VOID(fn_801466D0, PL_MEM) { py_setPlayerData(GM_PASS, SELF); }
PA_VOID(fn_80146700, PL_MEM) { py_setSpeedData(GM_PASS, SELF); }
PA_VOID(fn_80146740, PL_MEM) { py_setModeGravity(GM_PASS, SELF); }
PA_INT (fn_80146770, PL_MEM) { py_getGravityData(GM_PASS, SELF); }
PA_VOID(fn_80147250, PL_MEM) { py_setScrollMode(GM_PASS, SELF, A(1)); }
PA_VOID(fn_801472D0, PL_MEM) { py_setInvalidKeyTimer(GM_PASS, SELF, A(1), A(2)); }
PA_VOID(fn_801473F0, PL_MEM) { py_startQuakeShock(GM_PASS, SELF, A(1)); }
PA_VOID(fn_80147450, PL_MEM) { py_startPatternRumble(GM_PASS, SELF, A(1)); }
PA_VOID(fn_801474B0, PL_MEM) { py_setItemGetEffect(GM_PASS, SELF); }
PA_INT (fn_80147B60, PL_MEM) { py_isDrawingCarryFukidashi(GM_PASS, SELF); }
/* the virtual states' base IDs */
PA_INT (fn_8014A340, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_DEMO_DOWN); }
PA_INT (fn_8014A350, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_CLOUD); }
PA_INT (fn_8014A360, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_KANI); }
PA_INT (fn_8014A370, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_SWIM); }
PA_INT (fn_8014A380, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_HIP_ATTACK); }
PA_INT (fn_8014A390, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_TURN); }
PA_INT (fn_8014A3A0, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_SLIP); }
PA_INT (fn_8014A3B0, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_SIT_JUMP); }
PA_INT (fn_8014A3C0, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_CROUCH); }
PA_INT (fn_8014A3D0, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_LAND); }
PA_INT (fn_8014A3E0, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_FALL); }
PA_INT (fn_8014A3F0, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_JUMP); }
PA_INT (fn_8014A400, 0x80000000u, 4) { py_baseID(GM_PASS, BASE_ID_STATE_WALK); }

/* ################################################################## wave 2: the methods of 97 to 160
   bytes the A/B inputs reach (names from the decomp's order, checked against the code; several
   recompiled names in this range are wrong ports - see the entries) */

/* ---- more fields */
#define AC_ANGLE_X          256         /* s16 mAngle.x */
#define AC_MAX_SPEED_F      272         /* float mMaxSpeedF */
#define AC_LAST_POS         184         /* mVec3_c mLastPos */
#define AC_BC_PLAYER_FLAGS  680         /* u8 mBc.mPlayerFlags (low byte) */
#define AC_LAYER            911         /* u8 mLayer */
#define PL_AMI_LAYER        4149        /* u8 mAmiLayer */
#define PL_WALL_BC_OFFSET   4288        /* int mWallBcData.mOffset */
#define PL_STATE_MGR        5220        /* sFStateMgr_c mStateMgr (vtable at +0) */
#define PY_M60              5432        /* int m_60 */
#define PY_M80              5464        /* int m_80 */
#define PY_M88              5472        /* int m_88 (0: came out of the water) */
#define PY_WALL_SLIDE_CD    5481        /* u8 mWallSlideCooldown */
#define PY_LEVEL_EF1        5488        /* mEf::levelEffect_c mLevelEf1, mLevelEf2 */
#define PY_LEVEL_EF2        5784
#define PY_M2E8             6080        /* s16 m_2e8 */
#define PY_IS_PROPEL_FALL   6096        /* s16 mIsPropelFall */
#define PY_LEVEL_EF9        8308        /* mEf::levelEffect_c mLevelEf9, mLevelEf10 */
#define PY_LEVEL_EF10       8604
#define PY_WATER_M_B89      8289        /* u8 m_b89 */
#define PY_SPIN_COOLDOWN    10184       /* int mSpinCooldown */
#define PY_ROOF_HEIGHT      10192       /* float m_12f8 (checkSpinLiftUpRoofHeight) */
#define PY_FOLLOW_TYPE      10232       /* int mFollowType */
#define PY_ITEM_GET_EF1     10244       /* mEf::followEffect_c mItemGetEffect1, mItemGetEffect2 */
#define PY_ITEM_GET_EF2     10540
#define PY_BALLOON_VOICE_CD 10898       /* s16 mBalloonHelpVoiceCooldown */
#define PY_FOLLOW_EF4       10900       /* mEf::followEffect_c mFollowEf4 */
/* the model (dPyMdlBase_c) */
#define MDL_SPIN_LIFT_PARENT 36         /* dPyMdlBase_c *mpSpinLiftParentMdl */
#define MDL_PLAYER_TYPE     338         /* u8 (getSomeScale's index) */
#define MDL_M17C            380         /* u32 m_17c */
#define MDL_VT_OFF_STAR_ANM 68          /* (its vtable at +0) */
#define MDL_VT_OFF_STAR_EF  76
#define MDL_VT_SET_ANM      92          /* setAnm(anm, rate f1, blend f2, frame f3) */
#define MDL_VT_RELEASE_BODY 104         /* releaseBodyAnm(f1) */
/* virtual methods */
#define VT_START_VOICE      1076        /* startPlayerVoice(voice, arg) */
#define VT_TURN_ANGLE       1096
#define VT_MAX_FALL_SPEED_SET 1100
#define VT_IS_LIFT_UP       972
#define VT_SET_VIRUS_STAR   992         /* setVirusStar(other) */
#define STMGR_VT_GET_STATE  40          /* sFStateMgr_c::getStateID */
#define SID_VT_IS_EQUAL     16          /* sStateIDIf_c::isEqual(id) */
#define EF_FADE             16          /* (levelEffect_c / followEffect_c's vtable: fade) */
#define EF_FOLLOW           176         /* (followEffect_c's vtable: follow(pos, ang, scale)) */
/* the game's data (E2) */
#define SC_SPINDOWN_EF      0x80324B10u /* "Wm_mr_spindown" */
#define SC_SPINDOWNLINE_EF  0x80324B20u /* "Wm_mr_spindownline" */
#define SC_SWIMPADDLE_EF    0x80324DECu /* "Wm_mr_swimpaddle" */
#define SC_FLUTTERKICK_EF   0x80324E00u /* "Wm_mr_flutterkick" */
#define SC_SEALANDSMK_EF    0x80324E50u /* const char *sc_hipAttackEffectID[3] (setSeaLandSmokeEffect) */
#define SC_SPINDEPART_EF    0x80325158u /* "Wm_mr_spindepart" */
#define RUMBLE_PROPEL_BIGFLY 0x803250B8u /* "****--****--**----**----**----**----**----**----**" */
#define PY_MDL_HIO          0x80370DA0u /* dPyMdlMng_c::m_hio (+8: the scales by player type; the anm rates) */
#define SC_BALLOON_OFFSET_Y 0x802F4ED0u /* float scBalloonOffsetY[7] */
#define DATA_802F570C       0x802F570Cu /* dAcPy_c::data_802f5a0c (PAL) */
#define STATE_WALK          0x80375C2Cu /* dAcPy_c::StateID_Walk */
#define STATE_VINE          0x80375FF0u /* dAcPy_c::StateID_Vine */
#define STATE_FIRE          0x803760B0u /* dAcPy_c::StateID_Fire */
#define STATE_RIDE_YOSHI    0x803762B0u /* dAcPy_c::StateID_RideYoshi */
#define STATE_PB_SWIM       BASE_ID_STATE_SWIM   /* daPlBase_c::StateID_Swim (0x8035449C) */
#define DINFO_GAME_FLAG     (R(13) - 22272)      /* dInfo_c::mGameFlag (0x80429F80) */
#define SCSTAGE_INSTANCE    (R(13) - 21688)      /* dScStage_c::m_instance (0x8042A1C8) */
#define SAVEMNG_INSTANCE    (R(13) - 22080)      /* dSaveMng_c::m_instance (0x8042A040) */
#define SCSTAGE_CURR_WORLD  4620
#define SCSTAGE_CURR_COURSE 4621
/* status flags */
#define ST_OUT_OF_PLAY      4
#define ST_STUNNED          6
#define ST_WALL_SLIDE       19
#define ST_PROPEL           38
#define ST_SPIN             43
#define ST_PENGUIN_RECOIL   63
#define ST_51               81
#define ST_53               83          /* (in a balloon) */
#define ST_54               84
#define ST_7A               122
#define ST_7E               126
#define ST_81               129
#define ST_84               132
#define ST_AUTO_BOUNCE      135
#define ST_92               146
#define ST_93               147
#define ST_9B               155
#define ST_9C               156
#define ST_9D               157
#define ST_9E               158
#define ST_A0               160
#define ST_A1               161
#define ST_A3               163
#define ST_FIREBALL_PREPARE 166
#define ST_A8               168
#define ST_B9               185
#define ST_DISPLAY_OUT_NO_DAMAGE 186
#define ST_C2               194
#define ST_C9               201
/* sounds, voices */
#define SE_PLY_HPDP_SPLASH  339
#define SE_PLY_HIP_ATTACK_M 263
#define SE_PLY_HIP_ATTACK   261
#define VOICE_BALLOON_HELP  38

/* ---- more calls into daPlBase_c */
PB_DECL(hle_fn_80048C70, fn_80048C70)
PB_DECL(hle_fn_80047D10, fn_80047D10)
PB_DECL(hle_fn_80047D60, fn_80047D60)
PB_DECL(hle_fn_8004C4F0, fn_8004C4F0)
PB_DECL(hle_fn_8004B730, fn_8004B730)
PB_DECL(hle_fn_8004C450, fn_8004C450)
PB_DECL(hle_fn_800578D0, fn_800578D0)
PB_DECL(hle_fn_80048A60, fn_80048A60)
PB_DECL(hle_fn_80048630, fn_80048630)
PB_DECL(hle_fn_80047630, fn_80047630)
PB_DECL(hle_fn_8004C480, fn_8004C480)
PB_DECL(hle_fn_8004B9A0, fn_8004B9A0)
PB_DECL(hle_fn_80057860, fn_80057860)
PB_DECL(hle_fn_800543E0, hle_fn_800543E0)
PB_DECL(hle_fn_8004E710, fn_8004E710)
PB_DECL(hle_fn_80051080, fn_80051080)
PB_DECL(hle_fn_80047190, fn_80047190)
PB_DECL(hle_fn_8004DD00, fn_8004DD00)
PB_DECL(hle_fn_8004DB40, hle_fn_8004DB40)
#define PL_setHipAttackEffect       PB(hle_fn_80048C70, fn_80048C70)
#define PL_finalizeState_Fall       PB(hle_fn_80047D10, fn_80047D10)
#define PL_executeState_Fall        PB(hle_fn_80047D60, fn_80047D60)
#define PL_setJumpGravity           PB(hle_fn_8004C4F0, fn_8004C4F0)
#define PL_moveSpeedSet             PB(hle_fn_8004B730, fn_8004B730)
#define PL_powerSet                 PB(hle_fn_8004C450, fn_8004C450)
#define PL_setDelayHelpJump         PB(hle_fn_800578D0, fn_800578D0)
#define PL_checkTurn                PB(hle_fn_80048A60, fn_80048A60)
#define PL_slipActionMove           PB(hle_fn_80048630, fn_80048630)
#define PL_walkAction_Move          PB(hle_fn_80047630, fn_80047630)
#define PL_gravitySet               PB(hle_fn_8004C480, fn_8004C480)
#define PL_simpleMoveSpeedSet       PB(hle_fn_8004B9A0, fn_8004B9A0)
#define PL_setAddLiftSpeedF         PB(hle_fn_80057860, fn_80057860)
#define PL_bgCheck                  PB(hle_fn_800543E0, hle_fn_800543E0)
#define PL_executeState_DemoStartWait PB(hle_fn_8004E710, fn_8004E710)
#define PL_setHideNotGoalPlayer     PB(hle_fn_80051080, fn_80051080)
#define PL_doDelete                 PB(hle_fn_80047190, fn_80047190)
#define PL_isDemo                   PB(hle_fn_8004DD00, fn_8004DD00)
#define PL_isDemoType               PB(hle_fn_8004DB40, hle_fn_8004DB40)

/* ---- this wave's natives called from each other, and other natives */
void hle_fn_80130A00(ppc_context *ctx, uint8_t *base);
void hle_fn_8013D140(ppc_context *ctx, uint8_t *base);
void hle_fn_80146FA0(ppc_context *ctx, uint8_t *base);
void hle_fn_80147680(ppc_context *ctx, uint8_t *base);
void hle_fn_801291F0(ppc_context *ctx, uint8_t *base);
void hle_fn_8012AB00(ppc_context *ctx, uint8_t *base);
void hle_fn_8012AB40(ppc_context *ctx, uint8_t *base);
void hle_fn_8012CF30(ppc_context *ctx, uint8_t *base);
void hle_fn_8012E990(ppc_context *ctx, uint8_t *base);
void hle_fn_801275B0(ppc_context *ctx, uint8_t *base);
void hle_fn_8006CE70(ppc_context *ctx, uint8_t *base);
void hle_createPlayerEffect__3dEfFiPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c(ppc_context *ctx, uint8_t *base);
void hle_createPlayerEffect_change__3dEfFiPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c(ppc_context *ctx, uint8_t *base);
#define CREATE_PLAYER_EFFECT_LV hle_createPlayerEffect__3dEfFiPQ23mEf13levelEffect_cPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c

/* a call through an object's own vtable at +0 (the model, the state manager, an effect):
   lwz r12, 0(r3); lwz r12, slot(r12); mtctr; bctrl */
static inline void py_call0(GM_CTX, uint32_t ra, gptr obj, uint32_t slot) {
    R(12) = gm_u32(obj); R(12) = gm_u32(R(12) + slot); ctx->ctr = R(12); R(3) = obj;
    ctx->lr = ra; ppc_call_indirect(ctx, base, ctx->ctr);
}
/* isState(id): mStateMgr.getStateID()->isEqual(id) (r3 = the result) */
static void py_isState(GM_CTX, gptr self, uint32_t id, uint32_t ra0, uint32_t ra1) {
    py_call0(GM_PASS, ra0, self + PL_STATE_MGR, STMGR_VT_GET_STATE);
    R(12) = gm_u32(R(3)); R(4) = id; R(12) = gm_u32(R(12) + SID_VT_IS_EQUAL); ctx->ctr = R(12);
    ctx->lr = ra1; ppc_call_indirect(ctx, base, ctx->ctr);
}
/* offStatus for a list of flags (r3 = the object each time, as the PowerPC code reloads it); the
   first call's r3 is the object already */
static void py_offStatusList(GM_CTX, gptr self, const uint16_t *flags, uint32_t ra, int n) {
    for (int i = 0; i < n; i++) { R(3) = self; OFF_STATUS(ra + 12 * i, flags[i]); }
}
/* createPlayerEffect(mPlayerNo, ef, name, 0, pos, nullptr, nullptr) */
static void py_levelEffect(GM_CTX, gptr self, uint32_t ra, gptr ef, uint32_t name, gptr pos) {
    R(3) = (uint32_t)(int8_t)gm_u8(self + AC_PLAYER_NO);
    R(4) = ef; R(5) = name; R(6) = 0; R(7) = pos; R(8) = 0; R(9) = 0;
    BL(ra, CREATE_PLAYER_EFFECT_LV);
}

/* ================================================================== hip attack, falling, landing */
/* setHipAttackEffect: in shallow water the splash, its sound and the landing sound; else the base's */
static void py_setHipAttackEffect(GM_CTX, gptr self) {
    I2_FN(0x80126630u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
    if (!R(0)) { BL(0x8012669Cu, PL_setHipAttackEffect); return; }
    BL(0x80126654u, hle_fn_80130A00);                                    /* (setSeaLandSmokeEffect) */
    R(3) = self; R(4) = SE_PLY_HPDP_SPLASH; R(5) = 0;
    BL(0x80126664u, PL_startSound);
    R(0) = gm_u32(self + PL_POWERUP);
    if (CMPS(R(0), 3) == 0) { R(3) = self; R(4) = SE_PLY_HIP_ATTACK_M; R(5) = 0; BL(0x80126680u, PL_startSound); }
    else { R(3) = self; R(4) = SE_PLY_HIP_ATTACK; R(5) = 0; BL(0x80126694u, PL_startSound); }
}
/* setSpinHipAttackEffect: the two spin-down effects at the position */
static void py_setSpinHipAttackEffect(GM_CTX, gptr self) {
    I2_FN(0x801268F0u);
    NV_R(31, self);
    py_levelEffect(GM_PASS, self, 0x8012692Cu, self + PY_LEVEL_EF1, SC_SPINDOWN_EF, self + AC_POS);
    py_levelEffect(GM_PASS, self, 0x80126954u, self + PY_LEVEL_EF2, SC_SPINDOWNLINE_EF, self + AC_POS);
}
/* finalizeState_Fall: the base's, mAngle.x = 0, the fall statuses off */
static void py_finalizeState_Fall(GM_CTX, gptr self) {
    static const uint16_t fl[] = { ST_9B, ST_9C, ST_9D, ST_9E, ST_CAN_SPIN, ST_92, ST_CAN_LAND, ST_C2, ST_A1 };
    I2_FN(0x80127050u);
    NV_R(31, self);
    BL(0x80127068u, PL_finalizeState_Fall);
    R(0) = 0; gm_set_u16(self + AC_ANGLE_X, 0);
    py_offStatusList(GM_PASS, self, fl, 0x8012707Cu, 9);
}
/* executeState_Fall: the base's, gravity, speeds; then a hang or a jump (setDelayHelpJump's result
   compared and dropped) */
static void py_executeState_Fall(GM_CTX, gptr self) {
    I2_FN(0x801270F0u);
    NV_R(31, self);
    BL(0x80127108u, PL_executeState_Fall);
    R(3) = self; BL(0x80127110u, PL_setJumpGravity);
    VCALL(0x80127124u, self, VT_MAX_FALL_SPEED_SET);
    R(3) = self; BL(0x8012712Cu, PL_moveSpeedSet);
    R(3) = self; BL(0x80127134u, PL_powerSet);
    R(3) = self; BL(0x8012713Cu, hle_fn_80134B10);                          /* (setKaniActionInitHangHand) */
    if (CMPS(R(3), 0) != 0) return;
    R(3) = self; BL(0x8012714Cu, hle_fn_801278E0);                          /* (jump_common) */
    R(3) = self; BL(0x80127154u, PL_setDelayHelpJump);
    (void)CMPS(R(3), 0);                                                 /* (the result compared, not used) */
}
/* fn_801282d0(blend): the landing ends in a walk - unless walking against the speed turns */
static void py_landToWalk(GM_CTX, gptr self, uint32_t blend) {
    I2_FN(0x80128190u);
    NV_R(31, blend); R(4) = 0; NV_R(30, self);
    R(3) = self + PL_KEY;
    BL(0x801281B8u, fn_8005E7A0);                                        /* (mKey.buttonWalk(nullptr)) */
    if (CMPS(R(3), 0) != 0) {
        LDF(2, self + AC_SPEED_F); LDF(1, self + AC_MAX_SPEED_F); LDF(0, R(2) - 22824);   /* (0.0f) */
        FS(1, F(2) * F(1));
        cr_fcmp(ctx, 0, F(1), F(0));
        if (CR_BIT(ctx, 0)) {
            R(3) = self; BL(0x801281E0u, PL_checkTurn);
            if (CMPS(R(3), 0) != 0) return;
        }
    }
    R(4) = STATE_WALK; R(5) = R(31);
    VCALL(0x80128208u, self, VT_CHANGE_STATE);
}
/* finalizeState_Land */
static void py_finalizeState_Land(GM_CTX, gptr self) {
    static const uint16_t fl[] = { ST_9D, ST_9E, ST_CAN_SPIN, ST_92, ST_A0, ST_A2, ST_A3 };
    I2_FN(0x801282E0u);
    R(4) = ST_9B; NV_R(31, self);
    BL(0x801282FCu, PL_offStatus);
    py_offStatusList(GM_PASS, self, fl, 0x80128308u, 7);
}
/* finalizeState_WallSlide: statuses off, the wall flag of the background check off, the gravity
   back, the cooldown */
static void py_finalizeState_WallSlide(GM_CTX, gptr self) {
    I2_FN(0x801287B0u);
    R(4) = ST_WALL_SLIDE; NV_R(31, self);
    BL(0x801287CCu, PL_offStatus);
    R(3) = self; OFF_STATUS(0x801287D8u, ST_CAN_SPIN);
    R(3) = self; OFF_STATUS(0x801287E4u, ST_CAN_LAND);
    R(0) = gm_u8(self + AC_BC_PLAYER_FLAGS); R(3) = self;
    R(0) &= 0xFD; CR0(ctx, R(0));                                        /* (rlwinm.) */
    gm_set_u8(self + AC_BC_PLAYER_FLAGS, (uint8_t)R(0));
    VCALL(0x80128804u, self, VT_GET_GRAVITY_DATA);
    LDF(0, R(3)); R(0) = 4;
    STF(self + AC_ACCEL_Y, 0);
    gm_set_u8(self + PY_WALL_SLIDE_CD, 4);
}
/* setSpinJumpEffect(i): no spin - the effect ends; carrying - the carried player's; else ours */
static void py_setSpinJumpEffect(GM_CTX, gptr self, uint32_t i) {
    I2_FN(0x80128FC0u);
    NV_R(31, i); R(4) = ST_SPIN; NV_R(30, self);
    BL(0x80128FE4u, PL_testFlag);
    if (CMPS(R(3), 0) == 0) { R(3) = self; BL(0x80128FF4u, hle_fn_801291F0); return; }   /* (endSpinJumpEffect) */
    R(3) = gm_u32(self + PY_CARRY_ACTOR_ID);
    BL(0x80129000u, hle_search__7fBase_cFUi);
    if (CMPS(R(3), 0) != 0) {
        R(3) = self; BL(0x80129010u, hle_fn_8012DBE0);                  /* (getCarryPlayer) */
        if (CMPS(R(3), 0) == 0) return;
        R(4) = R(31); BL(0x80129020u, hle_fn_80129050);                     /* (carryPlayer->setSpinJumpEffectSub(i)) */
    } else {
        R(3) = self; R(4) = R(31); BL(0x80129030u, hle_fn_80129050);        /* (setSpinJumpEffectSub(i)) */
    }
}

/* ================================================================== slips, walking, crouching */
/* slipActionMove(mode): on the ground and moving - the slip effect; then the base's */
static void py_slipActionMove(GM_CTX, gptr self, uint32_t mode) {
    I2_FN(0x8012AB80u);
    NV_R(31, mode); NV_R(30, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1; CR0(ctx, R(0));
    if (R(0)) {
        LDF(1, self + AC_SPEED_F); LDF(0, R(2) - 22816);                 /* (0.1f) */
        ctx->f[1].u &= ~0x8000000000000000ull; ctx->f[1].d = frsp(ctx->f[1].d);   /* (fabs) */
        cr_fcmp(ctx, 0, F(1), F(0));
        if (CR_BIT(ctx, 1)) BL(0x8012ABC4u, hle_fn_8012AB40);            /* (setSlipEffect) */
    }
    R(3) = self; R(4) = R(31);
    BL(0x8012ABD0u, PL_slipActionMove);
}
/* walkAction_Move: turn, the run-on-water splash, the base's, the water walk */
static void py_walkAction_Move(GM_CTX, gptr self) {
    I2_FN(0x8012CB10u);
    R(0) = 0; NV_R(31, self);
    gm_set_u32(self + PY_M80, 0); gm_set_u32(self + PY_WAIT_FRAME_COUNT, 0);
    VCALL(0x8012CB40u, self, VT_TURN_ANGLE);
    R(3) = self; BL(0x8012CB48u, hle_fn_8012CF30);                      /* (setRunOnWaterEffect) */
    R(3) = self; BL(0x8012CB50u, PL_walkAction_Move);
    R(0) = gm_u32(self + PY_M88);
    if (CMPS(R(0), 0) == 0) {
        R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x8000; CR0(ctx, R(0));
        if (!R(0)) { R(0) = 1; gm_set_u32(self + PY_M88, 1); }
    }
    R(0) = gm_u32(self + PY_M88);
    if (CMPS(R(0), 1) == 0) { R(3) = self; BL(0x8012CB84u, hle_fn_80145E40); }   /* (setWaterWalkFlag) */
}
/* setCrouchSmokeEffect: moving - the brake smoke at joint 1 (out of the water), the slip sound */
static void py_setCrouchSmokeEffect(GM_CTX, gptr self) {
    I2_FN(0x8012D5B0u);
    gptr sp = gm_frame_sp;
    LDF(0, R(2) - 22824); NV_R(31, self);                                /* (0.0f) */
    LDF(1, self + AC_SPEED_F);
    cr_fcmp(ctx, 0, F(1), F(0));
    if (CR_BIT(ctx, 2)) return;
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
    if (!R(0)) {
        R(3) = gm_u32(self + PY_MDL); R(4) = sp + 8; R(5) = 1;
        BL(0x8012D5F0u, hle_getJointPos__12dPyMdlBase_cFP7mVec3_ci);
        R(3) = self; R(4) = sp + 8;
        BL(0x8012D5FCu, PL_setBrakeSmokeEffect);
    }
    R(3) = self; BL(0x8012D604u, hle_fn_8012AB00);                      /* (setSlipSE) */
}
/* finalizeState_Crouch */
static void py_finalizeState_Crouch(GM_CTX, gptr self) {
    static const uint16_t fl[] = { ST_9D, ST_CAN_SPIN, ST_AA, ST_51, ST_CAN_LAND, ST_A2, ST_A3 };
    I2_FN(0x8012D7C0u);
    R(4) = ST_A8; NV_R(31, self);
    BL(0x8012D7DCu, PL_offStatus);
    py_offStatusList(GM_PASS, self, fl, 0x8012D7E8u, 7);
    R(0) = 0; gm_set_u16(self + PY_M2E8, 0);
}

/* ================================================================== carrying, throwing */
/* checkSpinLiftUpRoofHeight: the roof above (dBc_c::checkTenjou), if below 0 (the wall data's
   offset goes to the frame as a dead int-to-float conversion) */
static void py_checkSpinLiftUpRoofHeight(GM_CTX, gptr self) {
    I2_FN(0x8012E360u);
    gptr sp = gm_frame_sp;
    LDF(1, R(2) - 22804);                                                /* (4.0f) */
    R(6) = 1; R(0) = 0x43300000u; R(4) = sp + 8;
    LDF(31, R(2) - 22824);                                               /* (0.0f) */
    NV_R(31, self);
    LDF(0, self + AC_POS + 4); LDF(3, self + AC_POS + 8); LDF(2, self + AC_POS);
    FS(0, F(1) + F(0));
    STF(sp + 12, 2); STF(sp + 16, 0); STF(sp + 20, 3);
    R(5) = gm_u32(self + PL_WALL_BC_OFFSET); R(3) = sp + 12;
    gm_set_u32(sp + 24, R(0));
    R(0) = R(5) ^ 0x80000000u;
    R(5) = gm_u8(self + AC_LAYER);
    gm_set_u32(sp + 28, R(0));
    BL(0x8012E3C8u, checkTenjou__5dBc_cFPC7mVec3_cPfUcUc_80075CA0);
    if (CMPS(R(3), 0) != 0) {
        LDF(0, sp + 8);
        cr_fcmp(ctx, 0, F(31), F(0));
        if (CR_BIT(ctx, 1)) ctx->f[31].u = ctx->f[0].u;                  /* (fmr) */
    }
    STF(self + PY_ROOF_HEIGHT, 31);
}
/* cancelCarry(actor): carrying that actor (or any, for nullptr) - let go */
static void py_cancelCarry(GM_CTX, gptr self, gptr actor) {
    I2_FN(0x8012E510u);
    NV_R(31, actor); NV_R(30, self);
    R(3) = gm_u32(self + PY_CARRY_ACTOR_ID);
    BL(0x8012E534u, hle_search__7fBase_cFUi);
    if (CMPU(R(3), R(31)) != 0 && CMPS(R(31), 0) != 0) { R(3) = 0; return; }
    R(3) = gm_u32(self + PY_MDL);
    LDF(1, R(2) - 22824);                                                /* (0.0f) */
    R(0) = gm_u32(R(3) + MDL_M17C) & 0xFFFFFFF9u; gm_set_u32(R(3) + MDL_M17C, R(0));
    R(3) = gm_u32(self + PY_MDL);
    py_call0(GM_PASS, 0x8012E56Cu, R(3), MDL_VT_RELEASE_BODY);
    R(4) = gm_u32(self + PY_MDL); R(0) = 0; R(3) = 1;
    gm_set_u32(R(4) + MDL_SPIN_LIFT_PARENT, 0);
    gm_set_u32(self + PY_CARRY_ACTOR_ID, 0);
}
/* checkEnableThrow: carrying, the actor still there, the carry button let go */
static void py_checkEnableThrow(GM_CTX, gptr self) {
    I2_FN(0x8012E6E0u);
    NV_R(31, self);
    VCALL(0x8012E704u, self, VT_IS_CARRY);
    if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
    R(3) = gm_u32(self + PY_CARRY_ACTOR_ID);
    BL(0x8012E71Cu, hle_search__7fBase_cFUi);
    if (CMPS(R(3), 0) == 0) {
        R(3) = self; R(4) = 0; BL(0x8012E730u, hle_fn_8012E510);         /* (cancelCarry(nullptr)) */
        R(3) = 0; return;
    }
    R(3) = self + PL_KEY;
    BL(0x8012E740u, fn_8005E680);                                        /* (mKey.buttonCarry()) */
    R(0) = cntlzw(R(3));
    R(3) = i2_rotl(R(0), 27) & 0x7FFFFFFu;
}
/* finalizeThrowCommon: the base's, the thrown actor let go (substate 0), statuses off */
static void py_finalizeThrowCommon(GM_CTX, gptr self) {
    static const uint16_t fl[] = { ST_AA, ST_97, ST_92, ST_CAN_LAND };
    I2_FN(0x8012E9A0u);
    NV_R(31, self);
    BL(0x8012E9B8u, hle_fn_8012E990);                                    /* (finalizeThrowCommonBase) */
    R(0) = gm_u32(self + PL_SUBSTATE);
    if (CMPS(R(0), 0) == 0) { R(3) = self; BL(0x8012E9CCu, hle_fn_8012E5A0); }   /* (releaseCarryActor) */
    py_offStatusList(GM_PASS, self, fl, 0x8012E9D8u, 4);
}
/* executeState_Throw: the water's or the air's movement, then executeThrowCommon */
static void py_executeState_Throw(GM_CTX, gptr self) {
    I2_FN(0x8012F060u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
    if (R(0)) BL(0x8012F084u, hle_fn_80131990);                             /* (setWaterMoveSpeed) */
    else {
        BL(0x8012F08Cu, PL_gravitySet);
        VCALL(0x8012F0A0u, self, VT_MAX_FALL_SPEED_SET);
        R(3) = self; BL(0x8012F0A8u, PL_simpleMoveSpeedSet);
        R(3) = self; BL(0x8012F0B0u, PL_powerSet);
    }
    R(3) = self; BL(0x8012F0B8u, hle_fn_8012EE20);                          /* (executeThrowCommon) */
}

/* ================================================================== swimming */
/* setPaddleSwimEffect / setFlutterKickEffect: an effect at each of two joints */
static void py_setTwoJointEffect(GM_CTX, gptr self, gptr sp, uint32_t name, uint32_t j0, uint32_t j1, uint32_t ra) {
    R(5) = j0; R(4) = sp + 8; NV_R(30, self);
    R(3) = gm_u32(self + PY_MDL);
    BL(ra, hle_getJointPos__12dPyMdlBase_cFP7mVec3_ci);
    NV_R(31, 0x80320000u);                                               /* (lis r31: the name's high half, kept) */
    py_levelEffect(GM_PASS, self, ra + 0x28, self + PY_LEVEL_EF9, name, sp + 8);
    R(3) = gm_u32(self + PY_MDL); R(4) = sp + 8; R(5) = j1;
    BL(ra + 0x38, hle_getJointPos__12dPyMdlBase_cFP7mVec3_ci);
    py_levelEffect(GM_PASS, self, ra + 0x5C, self + PY_LEVEL_EF10, name, sp + 8);
}
static void py_setPaddleSwimEffect(GM_CTX, gptr self) {
    I2_FN(0x8012FE50u);
    py_setTwoJointEffect(GM_PASS, self, gm_frame_sp, SC_SWIMPADDLE_EF, 11, 14, 0x8012FE78u);
}
static void py_setFlutterKickEffect(GM_CTX, gptr self) {
    I2_FN(0x80130040u);
    py_setTwoJointEffect(GM_PASS, self, gm_frame_sp, SC_FLUTTERKICK_EF, 4, 7, 0x80130068u);
}
/* setSeaLandSmokeEffect: the landing smoke for the tall type */
static void py_setSeaLandSmokeEffect(GM_CTX, gptr self) {
    I2_FN(0x80130A00u);
    R(4) = (uint32_t)-1; NV_R(31, self);
    VCALL(0x80130A28u, self, VT_GET_TALL_TYPE);
    R(0) = i2_rotl(R(3), 2) & 0x3FC;
    R(4) = SC_SEALANDSMK_EF;
    R(3) = (uint32_t)(int8_t)gm_u8(self + AC_PLAYER_NO);
    R(4) = gm_u32(R(4) + R(0));
    R(6) = self + AC_POS; R(5) = 0; R(7) = 0; R(8) = 0;
    BL(0x80130A54u, hle_createPlayerEffect_change__3dEfFiPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
}
/* setSwimAction_Walk(blend): landing on the floor under water */
static void py_setSwimAction_Walk(GM_CTX, gptr self, uint32_t blend) {
    I2_FN(0x80130B20u);
    NV_R(31, blend); NV_R(30, self);
    R(0) = gm_u32(self + PL_OLD_BG_CROSS1) & 1; CR0(ctx, R(0));
    if (!R(0)) BL(0x80130B4Cu, hle_fn_80130A00);                        /* (setSeaLandSmokeEffect) */
    int c = CMPS(R(31), 1);
    R(3) = 0; R(0) = 1;
    gm_set_u8(self + PY_WATER_M_B89, 0); gm_set_u32(self + PL_SUBSTATE, 1);
    if (c == 0) { R(3) = self; BL(0x80130B6Cu, hle_fn_80130A70); return; }  /* (BLEND_DEFAULT (1): setSwimActionWalkAnm) */
    R(3) = gm_u32(self + PY_MDL); R(5) = PY_MDL_HIO;
    LDF(3, R(2) - 22824);                                                /* (0.0f) */
    R(4) = 39; LDF(1, R(5) + 512); LDF(2, R(5) + 516);
    py_call0(GM_PASS, 0x80130B9Cu, R(3), MDL_VT_SET_ANM);               /* (setAnm(PLAYER_ANIM_SWIM_STANDING)) */
}

/* ================================================================== vines, damage, balloons, Yoshi */
/* isAmiRollAction: in the vine state, rolling */
static void py_isAmiRollAction(GM_CTX, gptr self) {
    I2_FN(0x801337E0u);
    NV_R(31, self);
    py_isState(GM_PASS, self, STATE_VINE, 0x80133808u, 0x80133820u);
    if (CMPS(R(3), 0) != 0) {
        R(0) = gm_u32(self + PL_SUBSTATE);
        if (CMPS(R(0), 3) == 0) { R(3) = 1; return; }
    }
    R(3) = 0;
}
/* finalizeState_FlyDamage */
static void py_finalizeState_FlyDamage(GM_CTX, gptr self) {
    static const uint16_t fl[] = { ST_9C, ST_9D, ST_A1 };
    I2_FN(0x801380D0u);
    R(4) = ST_9B; NV_R(31, self);
    BL(0x801380ECu, PL_offStatus);
    py_offStatusList(GM_PASS, self, fl, 0x801380F8u, 3);
    R(3) = self + PL_KEY; R(4) = 1;
    BL(0x8013811Cu, fn_8005E460);                                        /* (mKey.offStatus(STATUS_DISABLE_LR)) */
    R(3) = self; OFF_STATUS(0x80138128u, ST_PENGUIN_RECOIL);
}
/* setDrawBalloonInPlayer(pos): in a balloon - drawn there (pos.y raised by the power-up's offset) */
static void py_setDrawBalloonInPlayer(GM_CTX, gptr self, gptr pos) {
    I2_FN(0x801386B0u);
    NV_R(31, pos); R(4) = ST_53; NV_R(30, self);
    BL(0x801386D4u, PL_testFlag);
    if (CMPS(R(3), 0) == 0) return;
    R(3) = self; ON_STATUS(0x801386E8u, ST_54);
    R(0) = gm_u32(self + PL_POWERUP); R(3) = SC_BALLOON_OFFSET_Y;
    LDF(1, pos + 4); R(0) <<= 2; LDF(2, pos);
    LDF(0, R(3) + R(0));
    FS(0, F(1) + F(0));
    STF(pos + 4, 0); STF(self + AC_LAST_POS, 2);
    LDF(1, pos + 4); STF(self + AC_LAST_POS + 4, 1);
    LDF(0, pos + 8); STF(self + AC_LAST_POS + 8, 0);
    STF(self + AC_POS, 2); STF(self + AC_POS + 4, 1); STF(self + AC_POS + 8, 0);
}
/* setBalloonHelpVoice: in a balloon, waiting - the help voice every 120 frames at most (the map's
   "setBalloonInNextgoto" is the next function) */
static void py_setBalloonHelpVoice(GM_CTX, gptr self) {
    I2_FN(0x80138D40u);
    R(4) = ST_53; NV_R(31, self);
    BL(0x80138D5Cu, PL_testFlag);
    if (CMPS(R(3), 0) == 0) return;
    R(0) = gm_u32(self + PL_SUBSTATE);
    if (CMPS(R(0), 1) != 0) return;
    R(3) = self; R(4) = ST_B9; BL(0x80138D7Cu, PL_testFlag);
    if (CMPS(R(3), 0) != 0) return;
    R(0) = (uint32_t)(int16_t)gm_u16(self + PY_BALLOON_VOICE_CD);
    if (CMPS(R(0), 0) != 0) return;
    R(4) = VOICE_BALLOON_HELP; R(5) = 0;
    VCALL(0x80138DACu, self, VT_START_VOICE);
    R(0) = 120; gm_set_u16(self + PY_BALLOON_VOICE_CD, 120);
}
/* setRideOnYoshi(yoshi): ride it (the map's "setCloudStateMove" is a wrong name) */
static void py_setRideOnYoshi(GM_CTX, gptr self, gptr yoshi) {
    I2_FN(0x801399A0u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_RIDE_ACTOR_ID);
    if (CMPS(R(0), 0) != 0) return;
    R(0) = gm_u32(yoshi + AC_UNIQUE_ID); R(4) = ST_RIDE_YOSHI;
    gm_set_u32(self + PL_RIDE_ACTOR_ID, R(0));
    BL(0x801399D0u, PL_onStatus);
    R(4) = STATE_RIDE_YOSHI; R(5) = 0;
    VCALL(0x801399F0u, self, VT_CHANGE_STATE);
}
/* initializeState_RideYoshi: the Yoshi music, keys, statuses, no gravity */
static void py_initializeState_RideYoshi(GM_CTX, gptr self) {
    static const uint16_t fl[] = { ST_7A, ST_7E, ST_93, ST_81 };
    I2_FN(0x80139A10u);
    NV_R(31, self);
    BL(0x80139A28u, startYoshiBGM__9daPyMng_cFv_80060830);
    R(3) = self + PL_KEY; R(4) = 1;
    BL(0x80139A34u, setFlag__14dPlayerInput_cFQ214dPlayerInput_c5Flags_8005E3B0);   /* (mKey.onStatus(STATUS_DISABLE_LR)) */
    for (int i = 0; i < 4; i++) { R(3) = self; ON_STATUS(0x80139A40u + 12 * i, fl[i]); }
    LDF(0, R(2) - 22824); R(0) = 10;                                     /* (0.0f) */
    STF(self + AC_ACCEL_Y, 0);
    gm_set_u32(self + PL_SUBSTATE_TIMER, 10); gm_set_u32(self + PY_M60, 10);
}
/* setEatMouth(yoshi): being eaten - invisible, and the star passes on */
static void py_setEatMouth(GM_CTX, gptr self, gptr yoshi) {
    I2_FN(0x8013AC90u);
    NV_R(31, yoshi); NV_R(30, self);
    py_isState(GM_PASS, self, STATE_PLAYER_EAT, 0x8013ACC0u, 0x8013ACD8u);
    if (CMPS(R(3), 0) == 0) return;
    R(3) = self; ON_STATUS(0x8013ACECu, ST_INVISIBLE);
    R(3) = self; ON_STATUS(0x8013ACF8u, ST_C9);
    R(4) = self;
    VCALL(0x8013AD10u, yoshi, VT_SET_VIRUS_STAR);
}

/* ================================================================== fire, propeller */
/* setFireBallAction */
static void py_setFireBallAction(GM_CTX, gptr self) {
    I2_FN(0x8013BA80u);
    R(4) = ST_9E; NV_R(31, self);
    BL(0x8013BA9Cu, PL_testFlag);
    if (CMPS(R(3), 0) != 0) {
        R(3) = self; BL(0x8013BAACu, hle_fn_8013B9C0);                      /* (checkSetFireBall) */
        if (CMPS(R(3), 0) != 0) {
            R(4) = STATE_FIRE; R(5) = 0;
            VCALL(0x8013BAD4u, self, VT_CHANGE_STATE);
            R(3) = 1; return;
        }
    }
    R(3) = 0;
}
/* checkFireJump: a jump out of the fire state */
static void py_checkFireJump(GM_CTX, gptr self) {
    I2_FN(0x8013BB00u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1; CR0(ctx, R(0));
    if (R(0)) {
        R(3) = self + PL_KEY;
        BL(0x8013BB28u, fn_8005E6F0);                                    /* (mKey.triggerJump()) */
        if (CMPS(R(3), 0) != 0) {
            R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
            if (R(0)) { LDF(0, R(2) - 30756); STF(self + AC_SPEED_Y, 0); }  /* (sc_WaterJumpSpeed) */
            else {
                R(3) = self; R(4) = 1; BL(0x8013BB54u, hle_fn_80145E90);    /* (fn_80145fd0(1)) */
                R(3) = self; BL(0x8013BB5Cu, hle_fn_801275B0);          /* (setJumpSpeed) */
            }
            R(3) = self; BL(0x8013BB64u, hle_fn_80127F10);                  /* (setJumpCommonBase) */
            R(3) = 1; return;
        }
    }
    R(3) = 0;
}
/* finalizeState_Fire */
static void py_finalizeState_Fire(GM_CTX, gptr self) {
    static const uint16_t fl[] = { ST_A0, ST_CAN_LAND, ST_9B, ST_9C, ST_9D, ST_FIREBALL_PREPARE, ST_A1 };
    I2_FN(0x8013BE80u);
    R(4) = ST_CAN_SPIN; NV_R(31, self);
    BL(0x8013BE9Cu, PL_offStatus);
    py_offStatusList(GM_PASS, self, fl, 0x8013BEA8u, 7);
}
/* setPropelActionBigFly: the big propeller flight's start */
static void py_setPropelActionBigFly(GM_CTX, gptr self) {
    I2_FN(0x8013C5F0u);
    NV_R(31, self);
    BL(0x8013C608u, hle_fn_8013C520);                                        /* (setPropelActionFlyInit) */
    LDF(0, R(2) - 22812);                                                /* (0.5f) */
    R(3) = 0; R(0) = 38;
    gm_set_u32(self + PL_SUBSTATE, 0);
    R(3) = self;
    STF(self + AC_SPEED_Y, 0);
    gm_set_u32(self + PY_PROPEL_M2EC, 38);
    BL(0x8013C628u, hle_fn_8013D140);                                    /* (setStartPropelJumpEffect) */
    R(4) = RUMBLE_PROPEL_BIGFLY;
    VCALL(0x8013C644u, self, VT_START_RUMBLE);
}
/* setPropelActionFall: the propeller's slow fall */
static void py_setPropelActionFall(GM_CTX, gptr self) {
    I2_FN(0x8013C7C0u);
    R(4) = ST_SPIN; NV_R(31, self);
    BL(0x8013C7DCu, PL_offStatus);
    R(3) = gm_u32(self + PY_MDL); R(5) = PY_MDL_HIO;
    LDF(2, R(2) - 22588);                                                /* (30.0f) */
    R(4) = 134; LDF(1, R(5) + 1652);
    LDF(3, R(2) - 22824);                                                /* (0.0f) */
    py_call0(GM_PASS, 0x8013C808u, R(3), MDL_VT_SET_ANM);               /* (setAnm(PLAYER_ANIM_PL_SPIN_JUMP)) */
    R(3) = self; BL(0x8013C810u, PL_setAddLiftSpeedF);
    R(3) = DATA_802F570C; R(5) = 2; R(4) = 3000;
    LDF(0, R(3) + 28); R(0) = 1;
    gm_set_u32(self + PL_SUBSTATE, 2);
    gm_set_u16(self + PY_PROPEL_ROLL_SPD, 3000); gm_set_u16(self + PY_IS_PROPEL_FALL, 1);
    STF(self + AC_ACCEL_Y, 0);
}
/* updatePropelFlyPartsMove: the propeller parts' mode (ours, and a carried propeller's) */
static void py_updatePropelFlyPartsMove(GM_CTX, gptr self) {
    I2_FN(0x8013CF70u);
    R(4) = ST_PROPEL; NV_R(31, 4); NV_R(30, self);
    BL(0x8013CF94u, PL_testFlag);
    if (CMPS(R(3), 0) != 0) {
        R(0) = gm_u32(self + PL_SUBSTATE);
        if (CMPU(R(0), 1) <= 0) NV_R(31, 0);
        else {
            R(0) = (uint32_t)(int16_t)gm_u16(self + PY_PROPEL_ROLL_SPD); NV_R(31, 2);
            if (CMPS(R(0), 3000) < 0) NV_R(31, 1);
        }
    }
    R(3) = self; BL(0x8013CFCCu, hle_fn_8012DC60);                      /* (getCarryPropelActor) */
    if (CMPS(R(3), 0) == 0) {
        R(3) = gm_u32(self + AC_PROPEL_PARTS); gm_set_u32(R(3) + 8, R(31));
    } else {
        R(4) = gm_u32(self + AC_PROPEL_PARTS); R(0) = 3; gm_set_u32(R(4) + 8, 3);
        R(3) = gm_u32(R(3) + AC_PROPEL_PARTS); gm_set_u32(R(3) + 8, R(31));
    }
}
/* setStartPropelJumpEffect: on the ground, the take-off effect (in front of a cave mask's layer) */
static void py_setStartPropelJumpEffect(GM_CTX, gptr self) {
    I2_FN(0x8013D140u);
    gptr sp = gm_frame_sp;
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1; CR0(ctx, R(0));
    if (!R(0)) return;
    LDF(0, self + AC_POS + 8); LDF(1, self + AC_POS + 4); LDF(2, self + AC_POS);
    STF(sp + 8, 2); STF(sp + 12, 1); STF(sp + 16, 0);
    BL(0x8013D17Cu, isCaveMask__8dMaskMngFv_800CD2C0);
    if (CMPS(R(3), 0) != 0) {
        R(0) = gm_u8(self + AC_LAYER);
        if (CMPS(R(0), 0) == 0) {
            R(0) = gm_u8(self + PL_AMI_LAYER);
            if (CMPU(R(0), 1) == 0) { LDF(0, R(2) - 22312); STF(sp + 16, 0); }   /* (2000.0f) */
        }
    }
    R(3) = (uint32_t)(int8_t)gm_u8(self + AC_PLAYER_NO); R(4) = SC_SPINDEPART_EF;
    R(6) = sp + 8; R(5) = 0; R(7) = 0; R(8) = 0;
    BL(0x8013D1C8u, hle_createPlayerEffect__3dEfFiPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
}

/* ================================================================== demos */
/* exeDemo_DownFall: the gravity by the speed, the fall (b calcFallSpeed) */
static void py_exeDemo_DownFall(GM_CTX, gptr self) {
    LDF(1, self + AC_SPEED_Y); LDF(0, R(2) - 22652);                     /* (2.5f) */
    cr_fcmp(ctx, 0, F(1), F(0));
    if (CR_BIT(ctx, 1)) { LDF(0, R(2) - 22296); STF(self + AC_ACCEL_Y, 0); }   /* (-0.06f) */
    else {
        LDF(0, R(2) - 22812); cr_fcmp(ctx, 0, F(1), F(0));               /* (0.5f) */
        if (CR_BIT(ctx, 1)) { LDF(0, R(2) - 22468); STF(self + AC_ACCEL_Y, 0); }   /* (-0.25f) */
        else {
            LDF(0, R(2) - 22708); cr_fcmp(ctx, 0, F(1), F(0));           /* (-0.5f) */
            if (CR_BIT(ctx, 1)) { LDF(0, R(2) - 22292); STF(self + AC_ACCEL_Y, 0); }   /* (-0.047f) */
            else { LDF(0, R(2) - 22288); STF(self + AC_ACCEL_Y, 0); }    /* (-0.1f) */
        }
    }
    LDF(1, self + AC_POS + 4); LDF(0, self + AC_SPEED_Y);
    FS(0, F(1) + F(0));
    STF(self + AC_POS + 4, 0);
    hle_fn_8006CE70(ctx, base);                                          /* (b dBaseActor_c::calcFallSpeed) */
}
/* setHideNotGoalPlayer: not out of play, not in a balloon, not an item Toad - the base's */
static void py_setHideNotGoalPlayer(GM_CTX, gptr self) {
    I2_FN(0x8013FE00u);
    R(4) = ST_OUT_OF_PLAY; NV_R(31, self);
    BL(0x8013FE1Cu, PL_testFlag);
    if (CMPS(R(3), 0) == 0) {
        R(3) = self; R(4) = ST_53; BL(0x8013FE30u, PL_testFlag);
        if (CMPS(R(3), 0) == 0) {
            VCALL(0x8013FE4Cu, self, VT_IS_ITEM_KINOPIO);
            if (CMPS(R(3), 0) == 0) { R(3) = self; BL(0x8013FE64u, PL_setHideNotGoalPlayer); return; }
        }
    }
    R(3) = 0;
}
/* executeState_DemoStartWait: out of the water - check the background; now in it, start swimming
   (daPlBase_c::StateID_Swim); then the base's (the map's "finalizeState_DemoStartWait" is next) */
static void py_executeState_DemoStartWait(GM_CTX, gptr self) {
    I2_FN(0x801415B0u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
    if (!R(0)) {
        R(4) = 0; BL(0x801415D8u, PL_bgCheck);
        R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
        if (R(0)) {
            R(0) = gm_u32(self + PL_OLD_BG_CROSS1); R(3) = self; R(5) = 0;
            R(0) |= 0x4000; gm_set_u32(self + PL_OLD_BG_CROSS1, R(0));
            R(4) = STATE_PB_SWIM;
            VCALL(0x80141610u, self, VT_CHANGE_STATE);
        }
    }
    R(3) = self; BL(0x80141618u, PL_executeState_DemoStartWait);
}

/* ================================================================== the actor */
/* updateFollowEffect: the 1-up / flag sparkle follows joint 0, until it ends */
static void py_updateFollowEffect(GM_CTX, gptr self) {
    I2_FN(0x801436F0u);
    gptr sp = gm_frame_sp;
    NV_R(31, self);
    R(0) = gm_u32(self + PY_FOLLOW_TYPE);
    if (CMPS(R(0), 0) == 0) return;
    R(3) = gm_u32(self + PY_MDL); R(4) = sp + 20; R(5) = 0;
    BL(0x80143720u, hle_getJointPos__12dPyMdlBase_cFP7mVec3_ci);
    R(4) = gm_u32(self + PY_MDL); R(7) = PY_MDL_HIO;
    R(3) = self + PY_FOLLOW_EF4;
    R(0) = gm_u8(R(4) + MDL_PLAYER_TYPE);
    R(4) = sp + 20; R(6) = sp + 8; R(5) = 0;
    R(0) <<= 2; R(7) += R(0);
    LDF(0, R(7) + 8);                                                    /* (mPyMdlMng.getSomeScale()) */
    STF(sp + 8, 0); STF(sp + 12, 0); STF(sp + 16, 0);
    R(12) = gm_u32(self + PY_FOLLOW_EF4); R(12) = gm_u32(R(12) + EF_FOLLOW); ctx->ctr = R(12);
    ctx->lr = 0x80143768u; ppc_call_indirect(ctx, base, ctx->ctr);
    if (CMPS(R(3), 0) == 0) { R(0) = 0; gm_set_u32(self + PY_FOLLOW_TYPE, 0); }
}
/* doDelete: the 1-1 hint off (dGameCom), setSceneChangeInfo, the base's (the map's "setRopeSwingAnm"
   at 0x80144B20 is setSceneChangeInfo) */
static void py_doDelete(GM_CTX, gptr self) {
    I2_FN(0x80144AA0u);
    NV_R(31, self);
    BL(0x80144AB8u, hle_fn_80147680);                                    /* (fn_801477c0) */
    if (CMPS(R(3), 0) != 0) {
        VCALL(0x80144AD4u, self, VT_IS_ITEM_KINOPIO);
        if (CMPS(R(3), 0) == 0) {
            R(3) = (uint32_t)(int8_t)gm_u8(self + AC_PLAYER_NO); R(4) = 1;
            BL(0x80144AECu, FUN_800b37b0__8dGameComFii_800B37B0);
        }
    }
    R(3) = self; BL(0x80144AF4u, fn_80144B20);                          /* (setSceneChangeInfo) */
    R(3) = self; BL(0x80144AFCu, PL_doDelete);
    R(3) = 1;
}
/* fn_80145c00(powerup): a new power-up to change to (not out of play nor stunned; not the one
   pending; a change) */
static void py_setNextPowerup(GM_CTX, gptr self, uint32_t powerup) {
    I2_FN(0x80145AC0u);
    NV_R(31, powerup); R(4) = ST_OUT_OF_PLAY; NV_R(30, self);
    BL(0x80145AE4u, PL_testFlag);
    if (CMPS(R(3), 0) != 0) { R(3) = 0; return; }
    R(3) = self; R(4) = ST_STUNNED; BL(0x80145AF8u, PL_testFlag);
    if (CMPS(R(3), 0) != 0) { R(3) = 0; return; }
    R(0) = gm_u32(self + PL_POWERUP_COPY2);
    if (CMPS(R(0), R(31)) == 0) { R(3) = 0; return; }
    R(0) = gm_u32(self + PL_POWERUP);
    gm_set_u32(self + PL_POWERUP_COPY2, R(31));
    R(3) = R(31) - R(0); R(0) = R(0) - R(31);
    R(0) = R(3) | R(0);
    R(3) = R(0) >> 31;                                                   /* (rlwinm 1,31,31: != ) */
}
/* endStar */
static void py_endStar(GM_CTX, gptr self) {
    I2_FN(0x80145C50u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_STAR_TIMER);
    if (CMPS(R(0), 0) == 0) return;
    R(0) = 0; gm_set_u32(self + PL_STAR_TIMER, 0);
    py_call0(GM_PASS, 0x80145C8Cu, gm_u32(self + PY_MDL), MDL_VT_OFF_STAR_ANM);
    py_call0(GM_PASS, 0x80145CA0u, gm_u32(self + PY_MDL), MDL_VT_OFF_STAR_EF);
    BL(0x80145CA4u, stopStarBGM__9daPyMng_cFv_80060750);
}
/* isNoDamage */
static void py_isNoDamage(GM_CTX, gptr self) {
    I2_FN(0x80146060u);
    NV_R(31, self);
    R(4) = gm_u32(self + PL_DAMAGE_INVULN); R(0) = gm_u32(self + PL_CHANGE_INVULN);
    R(0) = R(4) | R(0); CR0(ctx, R(0));                                  /* (or.) */
    if (!R(0)) {
        BL(0x80146088u, PL_isDemo);
        if (CMPS(R(3), 0) == 0) {
            R(3) = self; R(4) = 4; BL(0x8014609Cu, PL_isDemoType);       /* (DEMO_PLAYER) */
            if (CMPS(R(3), 0) == 0) {
                R(3) = self; R(4) = ST_DISPLAY_OUT_NO_DAMAGE; BL(0x801460B0u, PL_testFlag);
                if (CMPS(R(3), 0) == 0) {
                    R(3) = self; R(4) = ST_84; BL(0x801460C4u, PL_testFlag);
                    if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
                }
            }
        }
    }
    R(3) = 1;
}
/* setSwimSpeed(speedY f1, speedF f2): in the water - swim with these speeds */
static void py_setSwimSpeed(GM_CTX, gptr self) {
    I2_FN(0x80146E90u);
    ctx->f[31].u = ctx->f[2].u; ctx->f[30].u = ctx->f[1].u;             /* (fmr: held across the call) */
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
    if (!R(0)) { R(3) = 0; return; }
    BL(0x80146EC4u, fn_8012F970);                                        /* (setUzuSwimAction) */
    R(0) = 20;
    STF(self + AC_SPEED_Y, 30); R(3) = 1;
    STF(self + AC_SPEED_F, 31);
    gm_set_u8(self + PY_WATER_JUMP_M_B88, 20);
}
/* isEnablePropelJump */
static void py_isEnablePropelJump(GM_CTX, gptr self) {
    I2_FN(0x80146F00u);
    NV_R(31, self);
    R(0) = gm_u32(self + PY_SPIN_COOLDOWN);
    if (CMPS(R(0), 0) == 0) {
        R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000; CR0(ctx, R(0));
        if (!R(0)) {
            R(4) = ST_CAN_SPIN; BL(0x80146F34u, PL_testFlag);
            if (CMPS(R(3), 0) != 0) {
                R(3) = self; BL(0x80146F4Cu, PL_isDemo);
                if (CMPS(R(3), 0) == 0) {
                    R(3) = self; R(4) = ST_AUTO_BOUNCE; BL(0x80146F60u, PL_testFlag);
                    if (CMPS(R(3), 0) == 0) {
                        R(3) = self; BL(0x80146F78u, hle_fn_80146FA0);  /* (getSpinActionMode() == 1) */
                        R(0) = R(3) - 1; R(0) = cntlzw(R(0));
                        R(3) = i2_rotl(R(0), 27) & 0x7FFFFFFu;
                        return;
                    }
                }
            }
        }
    }
    R(3) = 0;
}
/* getSpinActionMode: 1 for a propeller spin (ours, a carried propeller's or carried player's) */
static void py_getSpinActionMode(GM_CTX, gptr self) {
    I2_FN(0x80146FA0u);
    NV_R(30, self);
    R(0) = gm_u32(self + PL_POWERUP); NV_R(31, (int8_t)R(0));
    BL(0x80146FC4u, hle_fn_8012DC60);                                    /* (getCarryPropelActor) */
    if (CMPS(R(3), 0) != 0) NV_R(31, 4);
    else {
        R(3) = self; BL(0x80146FDCu, hle_fn_8012DBE0);                  /* (getCarryPlayer) */
        if (CMPS(R(3), 0) != 0) { R(0) = gm_u32(R(3) + PL_POWERUP); NV_R(31, (int8_t)R(0)); }
        else if (CMPS(R(31), 4) == 0) {
            VCALL(0x8014700Cu, self, VT_IS_LIFT_UP);
            if (CMPS(R(3), 0) != 0) NV_R(31, 1);
        }
    }
    R(0) = R(31) - 4;
    R(0) = cntlzw(R(0));
    R(3) = i2_rotl(R(0), 27) & 0x7FFFFFFu;
}
/* endPowerUpEffect */
static void py_endPowerUpEffect(GM_CTX, gptr self) {
    I2_FN(0x801474F0u);
    NV_R(31, self);
    R(0) = gm_u32(self + PY_POWERUP_EF_TIMER);
    if (CMPS(R(0), 0) != 0) {
        py_call0(GM_PASS, 0x80147520u, self + PY_ITEM_GET_EF1, EF_FADE);
        R(0) = gm_u32(self + PY_POWERUP_TYPE);
        if (CMPS(R(0), 0) == 0) py_call0(GM_PASS, 0x80147540u, self + PY_ITEM_GET_EF2, EF_FADE);
    }
    R(0) = 0; gm_set_u32(self + PY_POWERUP_EF_TIMER, 0);
}
/* fn_801477c0: single player, in 1-1, its hint flag not yet in the save */
static void py_isCourse11Hint(GM_CTX) {
    I2_FN(0x80147680u);
    R(0) = gm_u32(DINFO_GAME_FLAG) & 0x10; CR0(ctx, R(0));
    if (R(0)) { R(3) = 0; return; }
    R(3) = gm_u32(SCSTAGE_INSTANCE);
    R(0) = gm_u8(R(3) + SCSTAGE_CURR_WORLD);
    if (CMPS(R(0), 0) == 0) {
        R(0) = gm_u8(R(3) + SCSTAGE_CURR_COURSE);
        if (CMPS(R(0), 0) == 0) {
            R(3) = gm_u32(SAVEMNG_INSTANCE); R(4) = (uint32_t)-1;
            BL(0x801476C8u, getSaveGame__10dSaveMng_cFSc_800E0380);
            R(4) = 0; R(5) = 0; R(6) = 16;
            BL(0x801476D8u, CheckLevelCondition__9SaveBlockFiii_800CE3C0);   /* (isCourseDataFlag(0, 0, 0x10)) */
            if (CMPS(R(3), 0) == 0) { R(3) = 1; return; }
        }
    }
    R(3) = 0;
}

/* ================================================================== wave 2's entry points (all on: each is
   reached by the A/B inputs, see the report; RT_GM_REACH=1 logs the first calls) */
/* hip attack, falling, landing, jumps */
PA_VOID(fn_80126630, PL_MEM) { py_setHipAttackEffect(GM_PASS, SELF); }
PA_VOID(fn_801268F0, PL_MEM) { py_setSpinHipAttackEffect(GM_PASS, SELF); }
PA_VOID(fn_80127050, PL_MEM) { py_finalizeState_Fall(GM_PASS, SELF); }
PA_VOID(fn_801270F0, PL_MEM) { py_executeState_Fall(GM_PASS, SELF); }
PA_VOID(fn_80128190, PL_MEM) { py_landToWalk(GM_PASS, SELF, A(1)); }          /* (fn_801282d0; the map's "initializeState_Land" guess is wrong) */
PA_VOID(fn_801282E0, PL_MEM) { py_finalizeState_Land(GM_PASS, SELF); }        /* (the map's guess "executeState_Land" is wrong) */
PA_VOID(fn_801287B0, PL_MEM) { py_finalizeState_WallSlide(GM_PASS, SELF); }
PA_VOID(fn_80128FC0, PL_MEM) { py_setSpinJumpEffect(GM_PASS, SELF, A(1)); }
/* slips, walking, crouching */
PA_VOID(fn_8012AB80, PL_MEM) { py_slipActionMove(GM_PASS, SELF, A(1)); }
PA_VOID(fn_8012CB10, PL_MEM) { py_walkAction_Move(GM_PASS, SELF); }
PA_VOID(fn_8012D5B0, PL_MEM) { py_setCrouchSmokeEffect(GM_PASS, SELF); }
PA_VOID(fn_8012D7C0, PL_MEM) { py_finalizeState_Crouch(GM_PASS, SELF); }
/* carrying, throwing */
PA_VOID(fn_8012E360, PL_MEM) { py_checkSpinLiftUpRoofHeight(GM_PASS, SELF); }
PA_INT (fn_8012E510, PL_MEM) { py_cancelCarry(GM_PASS, SELF, A(1)); }       /* (the map's "setFireBallDamage" is wrong) */
PA_INT (fn_8012E6E0, PL_MEM) { py_checkEnableThrow(GM_PASS, SELF); }
PA_VOID(fn_8012E9A0, PL_MEM) { py_finalizeThrowCommon(GM_PASS, SELF); }
PA_VOID(fn_8012F060, PL_MEM) { py_executeState_Throw(GM_PASS, SELF); }
/* swimming */
PA_VOID(fn_8012FE50, PL_MEM) { py_setPaddleSwimEffect(GM_PASS, SELF); }
PA_VOID(fn_80130040, PL_MEM) { py_setFlutterKickEffect(GM_PASS, SELF); }
PA_VOID(fn_80130A00, PL_MEM) { py_setSeaLandSmokeEffect(GM_PASS, SELF); }
PA_VOID(fn_80130B20, PL_MEM) { py_setSwimAction_Walk(GM_PASS, SELF, A(1)); }
/* vines, damage, balloons, Yoshi */
PA_INT (fn_801337E0, PL_MEM) { py_isAmiRollAction(GM_PASS, SELF); }
PA_VOID(fn_801380D0, PL_MEM) { py_finalizeState_FlyDamage(GM_PASS, SELF); }
PA_VOID(fn_801386B0, PL_MEM, A(1), 12) { py_setDrawBalloonInPlayer(GM_PASS, SELF, A(1)); }
PA_VOID(fn_80138D40, PL_MEM) { py_setBalloonHelpVoice(GM_PASS, SELF); }
PA_VOID(fn_801399A0, PL_MEM) { py_setRideOnYoshi(GM_PASS, SELF, A(1)); }
PA_VOID(fn_80139A10, PL_MEM) { py_initializeState_RideYoshi(GM_PASS, SELF); }
PA_VOID(fn_8013AC90, PL_MEM, A(1), PY_SIZE) { py_setEatMouth(GM_PASS, SELF, A(1)); }
/* fire, propeller */
PA_INT (fn_8013BA80, PL_MEM) { py_setFireBallAction(GM_PASS, SELF); }
PA_INT (fn_8013BB00, PL_MEM) { py_checkFireJump(GM_PASS, SELF); }
PA_VOID(fn_8013BE80, PL_MEM) { py_finalizeState_Fire(GM_PASS, SELF); }
PA_VOID(fn_8013C5F0, PL_MEM) { py_setPropelActionBigFly(GM_PASS, SELF); }
PA_VOID(fn_8013C7C0, PL_MEM) { py_setPropelActionFall(GM_PASS, SELF); }
PA_VOID(fn_8013CF70, PL_MEM) { py_updatePropelFlyPartsMove(GM_PASS, SELF); }
PA_VOID(fn_8013D140, PL_MEM) { py_setStartPropelJumpEffect(GM_PASS, SELF); }
/* demos */
PA_VOID(fn_8013D600, PL_MEM) { py_exeDemo_DownFall(GM_PASS, SELF); }
PA_INT (fn_8013FE00, PL_MEM) { py_setHideNotGoalPlayer(GM_PASS, SELF); }
PA_VOID(fn_801415B0, PL_MEM) { py_executeState_DemoStartWait(GM_PASS, SELF); }
/* the actor */
PA_VOID(fn_801436F0, PL_MEM) { py_updateFollowEffect(GM_PASS, SELF); }
PA_INT (fn_80144AA0, PL_MEM) { py_doDelete(GM_PASS, SELF); }
PA_INT (dAcPy_c__ChangePowerupWithAnimation, PL_MEM) { py_setNextPowerup(GM_PASS, SELF, A(1)); }   /* (fn_80145c00: the symbol is a wrong port) */
PA_VOID(fn_80145C50, PL_MEM) { py_endStar(GM_PASS, SELF); }
PA_INT (fn_80146060, PL_MEM) { py_isNoDamage(GM_PASS, SELF); }
PA_INT (fn_80146E90, PL_MEM) { py_setSwimSpeed(GM_PASS, SELF); }
PA_INT (fn_80146F00, PL_MEM) { py_isEnablePropelJump(GM_PASS, SELF); }
PA_INT (fn_80146FA0, PL_MEM) { py_getSpinActionMode(GM_PASS, SELF); }
PA_VOID(fn_801474F0, PL_MEM) { py_endPowerUpEffect(GM_PASS, SELF); }
PA_INT (fn_80147680, 0x80000000u, 4) { py_isCourse11Hint(GM_PASS); }

/* ================================================================== self-test (RT_GM_SELFTEST=pl_acpy)
   On a live player (the first call of isCarry): the functions that work on the object alone (and
   read other actors / tables), with random power-ups, statuses, background crossings, counters,
   carry / ride IDs (none, the player itself, a stray one), cc sizes and scales, and the model's
   animation ID. The object (and the model's word) is put back after. */
#define ST_SCRATCH 0x2C80                /* (scratch inside the object's range: pointer arguments) */
static gptr pa_test_self;
static float pa_rfloat(void) { static const float v[] = { 0.0f, 1.0f, -1.0f, 0.5f, 16.0f, -4.0f, 31.0f, 1e-3f, -250.5f };
    return gm_rand() % 3 ? v[gm_rand() % 9] : (float)((int32_t)(gm_rand() % 20001) - 10000) / 16.0f; }
static uint32_t pa_rid(gptr s) {
    switch (gm_rand() % 4) { case 0: return 0; case 1: return gm_u32(s + AC_UNIQUE_ID); case 2: return gm_rand(); default: return gm_u32(s + AC_UNIQUE_ID) + 1; }
}
static void pa_randomize(GM_CTX, int round) {
    (void)ctx; (void)base; (void)round;
    gptr s = pa_test_self;
    for (uint32_t a = 0; a < 28; a += 4) gm_set_u32(s + PL_STATUS_FLAGS + a, gm_rand() & gm_rand());
    for (uint32_t a = 0; a < 16; a += 4) gm_set_u32(s + PL_NOW_BG_CROSS1 + a, gm_rand() & gm_rand());
    gm_set_u32(s + PL_POWERUP, gm_rand() % 7);
    gm_set_u32(s + PY_CARRY_ACTOR_ID, pa_rid(s));
    gm_set_u32(s + PL_RIDE_ACTOR_ID, pa_rid(s));
    gm_set_u16(s + PY_MISS_SPIN_ANGLE, (uint16_t)(gm_rand() % 3 ? 0x1400 * (gm_rand() % 14) : gm_rand()));
    gm_set_u16(s + PY_PROPEL_FLY_TIME, (uint16_t)(gm_rand() % 2 ? 0 : gm_rand()));
    gm_set_u16(s + PY_WATER_WALK_TIMER, (uint16_t)(gm_rand() % 3 ? gm_rand() % 4 : gm_rand()));
    gm_set_u32(s + PY_JUMP_COUNTER, gm_rand() % 4);
    gm_set_u32(s + PY_WAIT_FRAME_COUNT, gm_rand() % 2 ? 78 + gm_rand() % 4 : gm_rand());
    gm_set_u32(s + PY_LIFT_M1308, gm_rand() % 2 ? 0 : gm_rand());
    gm_set_u32(s + PY_SPIN_JUMP_EF, 0);                                  /* (no effect kill in the test) */
    gm_set_u8(s + AC_DIRECTION, (uint8_t)(gm_rand() % 2));
    gm_set_u8(s + AC_PLAYER_NO, (uint8_t)(gm_rand() % 8));
    gm_set_f32(s + PL_MODEL_HEIGHT, pa_rfloat());
    gm_set_f32(s + AC_SPEED_F, gm_rand() % 3 ? 0.0f : pa_rfloat());
    gm_set_f32(s + PY_CC_M1598, pa_rfloat()); gm_set_f32(s + PY_CC_M1598 + 4, pa_rfloat());
    for (uint32_t a = 0; a < 12; a += 4) gm_set_f32(s + AC_SCALE + a, pa_rfloat());
    gm_set_f32(s + PY_AMI_RELATED2, pa_rfloat());
    gm_set_f32(s + PY_LIFT_OFFSET, pa_rfloat());
    for (uint32_t a = 0; a < 16; a += 4) gm_set_f32(s + AC_CC_OFFSET + a, pa_rfloat());
    gm_set_u32(s + AC_CC_VS_DAMAGE, gm_rand()); gm_set_u32(s + PL_ATT_CC1_VS_KIND, gm_rand());
    gm_set_u16(s + ST_SCRATCH, (uint16_t)(gm_rand() % 3 ? gm_rand() % 3 : gm_rand()));
    gm_set_u32(gm_u32(s + PY_MDL) + MDL_ANM_ID, gm_rand() % 3 == 0 ? 117 : gm_rand() % 2 ? 11 : gm_rand() % 200);
    /* (wave 2) */
    gm_set_u32(s + PL_SUBSTATE, gm_rand() % 5);
    gm_set_u32(s + PL_POWERUP_COPY2, gm_rand() % 7);
    gm_set_u32(s + PY_SPIN_COOLDOWN, gm_rand() % 2 ? 0 : gm_rand());
    gm_set_u32(s + PL_DAMAGE_INVULN, gm_rand() % 3 ? 0 : gm_rand()); gm_set_u32(s + PL_CHANGE_INVULN, gm_rand() % 3 ? 0 : gm_rand());
    gm_set_u16(s + PY_PROPEL_ROLL_SPD, (uint16_t)(gm_rand() % 2 ? 2990 + gm_rand() % 20 : gm_rand()));
    gm_set_f32(s + AC_SPEED_Y, pa_rfloat()); gm_set_f32(s + AC_MAX_SPEED_F, pa_rfloat());
    for (uint32_t a = 0; a < 12; a += 4) gm_set_f32(s + AC_POS + a, pa_rfloat());
    gm_set_f32(s + ST_SCRATCH + 4, pa_rfloat()); gm_set_f32(s + ST_SCRATCH + 8, pa_rfloat());
}
static uint32_t pa_arg(char k) {
    gptr s = pa_test_self;
    switch (k) {
    case 'P': return s + ST_SCRATCH;                                     /* (a timer / an out vector) */
    case 'S': return s;                                                  /* (the player itself) */
    case 'B': return gm_rand() % 4 ? s + ST_SCRATCH + 16 : 0;            /* (getCcBounds: or none) */
    case 'M': return gm_rand() % 7;                                      /* (a power-up) */
    case 'I': return gm_rand() % 3;                                      /* (a point-data index) */
    case 'T': return (uint32_t)((int32_t)(gm_rand() % 8) - 1);          /* (a power-up or -1) */
    default:  return 0xDEADBEEFu;
    }
}
static const gm_test_t pa_tests[] = {
    GM_TEST(fn_801267B0, GMV_RET, ""), GM_TEST(fn_80127410, 0, ""), GM_TEST(fn_801298B0, GMV_RET, ""),
    GM_TEST(fn_80129910, GMV_RET, ""), GM_TEST(fn_801299B0, 0, ""), GM_TEST(fn_801299C0, 0, ""),
    GM_TEST(fn_8012BD70, GMV_RET, ""), GM_TEST(fn_8012C5E0, GMV_RET, ""), GM_TEST(fn_8012CAD0, GMV_RET, "!P"),
    GM_TEST(fn_8012DBE0, GMV_RET, ""), GM_TEST(fn_8012DC20, GMV_RET, ""), GM_TEST(fn_8012DC60, GMV_RET, ""),
    GM_TEST(fn_8012DCC0, GMV_RET, ""), GM_TEST(fn_8012DD10, GMV_RET, ""), GM_TEST(fn_8012DE20, 0, ""),
    GM_TEST(fn_8012E120, 0, ""), GM_TEST(aramGetFirstUserAddress, GMV_RET, ""), GM_TEST(fn_8012EDF0, GMV_RET, ""),
    GM_TEST(fn_8013A150, GMV_RET, "S"), GM_TEST(getYoshi__7dAcPy_cFv, GMV_RET, ""), GM_TEST(fn_8013AAA0, GMV_RET, ""),
    GM_TEST(fn_80138750, GMV_RET, ""), GM_TEST(fn_8013C380, 0, ""), GM_TEST(fn_8013DC20, 0, ""),
    GM_TEST(fn_8013EA30, 0, ""), GM_TEST(fn_8013EA50, 0, ""), GM_TEST(fn_80141E30, 0, ""),
    GM_TEST(fn_80141EE0, 0, ""), GM_TEST(fn_80141F40, 0, ""), GM_TEST(fn_80141F70, 0, "B"),
    GM_TEST(fn_80141FD0, 0, ""), GM_TEST(fn_80142510, GMV_RET, "MI"), GM_TEST(fn_80142530, 0, ""),
    GM_TEST(fn_80143530, 0, ""), GM_TEST(fn_80143880, GMV_RET, "!P"), GM_TEST(fn_80145980, 0, "!PS"),
    GM_TEST(fn_80145E40, 0, ""), GM_TEST(fn_80146580, GMV_RET, "T"), GM_TEST(fn_801466D0, 0, ""),
    GM_TEST(fn_80146700, 0, ""), GM_TEST(fn_80146740, 0, ""), GM_TEST(fn_80146770, GMV_RET, ""),
    GM_TEST(fn_80147250, 0, "b"), GM_TEST(fn_801472D0, 0, "vv"), GM_TEST(fn_801474B0, 0, ""),
    GM_TEST(fn_8014A340, GMV_RET, "!"), GM_TEST(fn_8014A3A0, GMV_RET, "!"), GM_TEST(fn_8014A400, GMV_RET, "!"),
    /* (wave 2) */
    GM_TEST(fn_801282E0, 0, ""), GM_TEST(fn_801287B0, 0, ""), GM_TEST(fn_8012D7C0, 0, ""),
    GM_TEST(fn_8012E360, 0, ""), GM_TEST(fn_801337E0, GMV_RET, ""), GM_TEST(fn_801380D0, 0, ""),
    GM_TEST(fn_801386B0, 0, "P"), GM_TEST(fn_8013BE80, 0, ""), GM_TEST(fn_8013D600, 0, ""),
    GM_TEST(dAcPy_c__ChangePowerupWithAnimation, GMV_RET, "M"), GM_TEST(fn_80146060, GMV_RET, ""),
    GM_TEST(fn_80146F00, GMV_RET, ""), GM_TEST(fn_80146FA0, GMV_RET, ""), GM_TEST(fn_80147680, GMV_RET, "!"),
};
static void pa_selftest(GM_CTX, gptr self) {
    if (!gm_selftest_wanted("pl_acpy")) return;
    pa_test_self = self;
    const gptr ranges[] = { self, PY_SIZE, gm_u32(self + PY_MDL) + MDL_ANM_ID, 4 };
    const gm_selftest_t t = { "pl_acpy", pa_tests, (int)(sizeof pa_tests / sizeof *pa_tests), 400, ranges, 2, pa_randomize, pa_arg };
    gm_selftest(GM_PASS, &t);
}
