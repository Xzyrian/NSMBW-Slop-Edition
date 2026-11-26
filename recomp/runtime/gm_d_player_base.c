/* gm_d_player_base.c - daPlBase_c, the player base class: its small methods (track B, gm.h,
 * docs/DECOMP.md), instance 2's helper. The game's own version (USA rev 2 = PAL addresses for this
 * class); the module's overrides of the class are in gm_py_player.c.
 *
 * NSMBW-Decomp (source/dol/bases/d_a_player_base.cpp) gives the names; the recompiled code is the
 * truth. Functions the address map left unnamed are identified from what they do and their place
 * in the source (named in the comments; "(by position)" where only the order says so).
 * Every daPlBase_c method here also runs on dAcPy_c and daYoshi_c objects (they derive from it).
 *
 * Register-exact (gm_i2.h, RT_GM_VERIFY_REGS=1): r0-r12, CR0, CTR, XER[CA], f0-f13 and both
 * paired-single halves as the PowerPC code leaves them; framed functions push the PowerPC frame
 * with its prologue replayed and hold r30 / r31 / f31 as the PowerPC code does at each call
 * (I2_FN, NV_R); calls go out with the bl's LR (BL) or as tail calls (LR left the caller's).
 * Virtual calls go through the object's vtable exactly as the PowerPC code does.
 *
 * Which functions are on and how they were verified: see the list before the entry points. */
#include "gm_i2.h"
#include "rt_powerup.h"                      /* (the new power-ups: pu_tab for the game's 7-entry tables) */
RT_STATE_FILE                                   /* (game code: its variables are part of a save state) */

/* ---- fBase_c / dActor_c fields (checked against the recompiled code) */
#define PL_UNIQUE_ID        0           /* fBaseID_e mUniqueID */
#define PL_VTABLE           96
#define PL_POS              172         /* mVec3_c mPos */
#define PL_POS_Y            176
#define PL_POS_Z            180
#define PL_ANGLE_X          256         /* s16 mAngle.x */
#define PL_ANGLE_Y          258         /* s16 mAngle.y */
#define PL_SPEED_F          268         /* float mSpeedF */
#define PL_MAX_FALL_SPEED   280         /* float mMaxFallSpeed */
#define PL_CC               328         /* dCc_c mCc (the body) */
#define PL_BC               492         /* dBc_c mBc (the background checker) */
#define BC_NO_HIT_ACTOR     576         /*   mBc.mpNoHitActor */
#define BC_CTR_WALL_R       592         /*   mBc.mpCtrWalls[0] */
#define BC_CTR_WALL_L       596         /*   mBc.mpCtrWalls[1] */
#define BC_PLAYER_FLAGS     680         /*   u8 mBc.mPlayerFlags (4: on a slope's reverse side) */
#define BG_CTR_E0           224         /* dBg_ctr_c::m_e0 (the owner) */
#define PL_DIRECTION        840         /* u8 mDirection */
#define PL_PLAYER_NO        909         /* s8 mPlayerNo */
/* ---- daPlBase_c fields */
#define PL_SQUISH_STATE     916         /* s32 mSquishState */
#define PL_SQUISH_KEYFRAME  920         /* s32 mSquishKeyframeIdx */
#define PL_SQUISH_SCALE     924         /* float mSquishScale */
#define PL_NO_HIT_PLAYER    936         /* const daPlBase_c *mpNoHitPlayer */
#define PL_NO_HIT_TIMER     940         /* s32 mNoHitTimer */
#define PL_BG_PRESS_ACTIVE  944         /* u32 mBgPressActive (a bit per BgPress_e) */
#define PL_BG_PRESS_IDS     952         /* fBaseID_e mBgPressIDs[] */
#define PL_DEMO_STATE       1012        /* u8 mDemoState */
#define PL_GOTO_POS_Y       1024        /* mGotoPos.y */
#define PL_TURN_SMOKE_EFF   1172        /* dEf::followEffect_c mTurnSmokeEffect */
#define PL_TURN_EFF_FADE    1452        /* u8 mTurnEffectFade */
#define PL_JUMP_DAI_TIMER   1772        /* s32 mJumpDaiFallTimer */
#define PL_BEING_DELETED    1780        /* s32 mIsBeingDeleted */
#define PL_MDL_MNG          3560        /* dPyMdlMng_c *mpMdlMng (+4: mpMdl; the model's +40: mAnm) */
#define PL_SND_OBJ          3564        /* the player's sound object mSndObj (vtable at +0) */
#define PL_SND_PLY_MODE     3740        /* mSndObj.m_04: the power-up's sound set */
#define PL_KEY              3748        /* dAcPyKey_c mKey */
#define PL_RIDE_ACTOR_ID    4104        /* fBaseID_e mRideActorID */
#define PL_HIP_DMG_PLR_ID   4112        /* fBaseID_e mHipAttackPlayerID */
#define PL_STATUS           4116        /* u32 mStatusFlags[7] */
#define PL_AMI_LAYER        4149        /* u8 mAmiLayer */
#define PL_SPEED_DATA       4192        /* const sSpeedData *mSpeedDataNormal */
#define PL_SPEED_DATA_STAR  4196        /* const sSpeedData *mSpeedDataStar */
#define PL_GRAVITY_DATA     4200        /* const float *mGravityData */
#define PL_DAMAGE_INVULN    4212        /* s32 mDamageInvulnTimer */
#define PL_POWERUP_INVULN   4216        /* s32 mPowerupChangeInvulnTimer */
#define PL_TREAD_COUNT      4224        /* s8 mTreadCount */
#define PL_STAR_COUNT       4225        /* s8 mStarCount */
#define PL_COMBO_COUNT      4226        /* s8 mPlComboCount */
#define PL_NEW_FOLLOW_MAME  4228        /* u32 mNewFollowMameKuribo */
#define PL_FOLLOW_MAME      4232        /* u32 mFollowMameKuribo */
#define PL_POWERUP          4240        /* PLAYER_POWERUP_e mPowerup (0 none, 3 mini) */
#define PL_NOW_BG_CROSS1    4308        /* u32 mNowBgCross1 (1 BGC_FOOT, 0x80000 BGC_SIDE_LIMIT_L) */
#define PL_NOW_BG_CROSS2    4312        /* u32 mNowBgCross2 (2 LIFT, 8 AUTOSLIP, 0x80 SLOPE, 0x100 CLIFF, 0x180000 VINE_TOUCH_L|R) */
#define PL_ATT_CC1          4616        /* dCc_c mAttCc1 */
#define PL_ATT_CC2          4780        /* dCc_c mAttCc2 */
#define PL_GROUND_TYPE      4380        /* GroundType_e mGroundType (7: GROUND_TYPE_FUNSUI) */
#define PL_NO_HIT_OBJ_TIMER 4388        /* s32 mNoHitObjTimer */
#define PL_CC_REV           5108        /* float mCcRevRate, mCcRevSpeedF, mCcRevTotalOffsX / Y (5108..5120) */
#define PL_CC_REV_SET       5124        /* bool mCcRevSet, mCcHasInitialRevY */
#define PL_DEMO_STATE_MGR   5144        /* sStateMgr mDemoStateMgr */
#define PL_DEMO_SUBSTATE    5208        /* s32 mDemoSubstate */
#define PL_IS_DEMO_MODE     5216        /* bool mIsDemoMode */
#define PL_STATE_MGR        5220        /* sStateMgr mStateMgr */
#define PL_SUBSTATE_TIMER   5288        /* s32 mSubstateTimer */
#define PL_AIR_PUSH_X       5316        /* float mFinalAirPushForceX */
/* dCc_c (inside the player): the collision data */
#define CC_OFFSET           28          /* mCcData.mBase.mOffset (x, y), mSize (x, y) */
#define CC_VS_KIND          48          /* u32 mCcData.mVsKind */
#define CC_ATTACK           45          /* u8 mCcData.mAttack */
#define CC_VS_DAMAGE        52          /* u32 mCcData.mVsDamage */
/* sStateMgr / sFStateFct_c / sFState_c */
#define SM_METHOD           24          /* the state manager's sStateMethodUsr_FI_c (its vtable at +0) */
#define ST_OBJ              4           /* sFState_c: the object, the state ID */
#define ST_ID               8
/* status flags (daPlBase_c::Status_e) */
#define STATUS_WAIT_JUMP    18
#define STATUS_BIG_JUMP     20
#define STATUS_PLAYER_JUMP  22
#define STATUS_HIP_ATTACK_DAMAGE_PLAYER 35
#define STATUS_PROPEL_NO_ROLL 42
#define STATUS_SLIP_ACTIVE  48
#define STATUS_POLE         53
#define STATUS_TARZAN_ROPE  54
#define STATUS_JUMP_DAI_COOLDOWN 77
#define STATUS_52           82
#define STATUS_53           83
#define STATUS_5E           94
#define STATUS_64           100
#define STATUS_88           136
#define STATUS_97           151
#define STATUS_99           153          /* (the z position is set by hand) */
#define STATUS_A0           160
#define STATUS_A5           165
#define STATUS_FOLLOW_MAME_KURIBO 172
#define STATUS_ABOUT_TO_BE_DELETED 181
#define STATUS_CAN_WATER_WALK 193
#define STATUS_C4           196
/* the virtual methods (vtable offsets) */
#define VT_GET_TALL_TYPE    232
#define VT_INIT_STAMP_RED   268         /* initStampReduction */
#define VT_SET_RED_BOYON    276         /* setReductionBoyon */
#define VT_SET_TIME_OVER    628         /* setTimeOverDemo */
#define VT_INIT_GOAL_BASE   648         /* initDemoGoalBase */
#define VT_CHANGE_STATE     660
#define VT_SET_SLIP_ACTION  920
#define VT_SET_HIP_START    932         /* setHipAttack_AttackStart */
#define VT_IS_LIFT_UP_EX_MAME 976       /* isLiftUpExceptMame */
#define VT_IS_STAR          980
#define VT_SET_Z_POSITION   1060
#define VT_GET_MUKI_ANGLE   1092
#define SM_EXECUTE          16          /* sStateMgr / sStateMethod_c: executeState, finalizeState, getStateID */
#define SM_FINALIZE         20
#define SM_GET_STATE_ID     40
#define SID_IS_NULL         12          /* sStateIDIf_c::isNull */
#define SID_INITIALIZE      40          /* sFStateID_c<T>::initializeState(obj), executeState, finalizeState */
#define SID_EXECUTE         44
#define SID_FINALIZE        48
#define SO_START_SOUND      36          /* the sound object's startSound(id, remote), holdSound(id, remote) */
#define SO_HOLD_SOUND       40
#define EF_FOLLOW_FADE      20          /* dEf::followEffect_c::followFade */
/* data (from the recompiled code: r2 = 0x80433080, r13 = 0x8042F680) */
#define F_ONE               0x8042B874u /* 1.0f (r2 - 30732) */
#define F_ZERO              0x8042B878u /* 0.0f (r2 - 30728) */
#define MUKI_ANGLE          0x8042B880u /* s16 scMukiAngle[2] = { 0x3000, -0x3000 } (r2 - 30720) */
#define DIR_SPEED           0x8042B840u /* float sc_DirSpeed[2] = { 1, -1 } (r2 - 30784) */
#define F_FOUR              0x8042B8ACu /* 4.0f (r2 - 30676) */
#define F_HALF              0x8042B8C4u /* 0.5f (r2 - 30652) */
#define F_MAX_FALL          0x8042B8E0u /* sc_MaxFallSpeed -4.0f (r2 - 30624) */
#define D_INT_TO_FLOAT      0x8042B8B8u /* double 0x4330000080000000 (r2 - 30664) */
#define F_JUMPDAI_RED       0x8042B92Cu /* 0.6f (r2 - 30548) */
#define F_TWO               0x8042B968u /* 2.0f (r2 - 30488) */
#define F_MINUS_TWO         0x8042B8D8u /* -2.0f (r2 - 30632) */
#define SAKA_MAX_SPEED_RATIO 0x802EE978u /* l_sakaMaxSpeedRatio[type][updown] (3 floats per type) */
#define SAKA_STOP_ACCELE    0x802EE9B4u /* l_sakaStopAccele */
#define SAKA_MOVE_ACCELE    0x802EE9F0u /* l_sakaMoveAccele */
#define PLAYER_SOUND_MODE   0x802EEAF0u /* scPlayerSound[7] (setSoundPlyMode) */
#define WATER_OFFSET_Y      0x802EEB80u /* scWaterOffsetY[3] */
#define CREATE_ACTION_PROC  0x80308300u /* l_createActionProc[]: pointers to member functions, 12 bytes each */
#define EF_SPSMOKE          0x80307E50u /* "Wm_mr_spsmoke" */
#define STATE_ID_NULL       0x80377A04u /* sStateID::null */
#define STATE_WALK          0x8035425Cu /* daPlBase_c::StateID_Walk */
#define STATE_DEMO_IN_DOKAN_U 0x8035482Cu /* daPlBase_c::StateID_DemoInDokanU */
#define GAME_MODE           0x8042A204u /* dScStage_c::m_gameMode (r13 - 21628; 2 = the title) */
#define GAME_FLAG           0x80429F80u /* dInfo_c::mGameFlag (r13 - 22272) */
#define STAGE_TIMER_P       0x8042A070u /* dStageTimer_c::m_instance (r13 - 22032) */
#define QUAKE_P             0x8042A008u /* dQuake_c::m_instance (r13 - 22136) */
#define REMOCON_MNG_P       0x8042A028u /* dRemoconMng_c::m_instance (r13 - 22104) */
#define RUMBLE_CORES        0x80377C88u /* mPad::g_core[] (the module moves it: 0x8185FB1C) */
#define RUMBLE_CORES_MOD    0x8185FB1Cu

/* (single-precision helpers: lfs and single arithmetic set both halves, fmr / fabs / frsp / lfd ps0 only) */
#define LDF(n, a)  (ctx->f[n].d = ctx->ps1[n] = ldfs(base, (a)))
#define STF(a, n)  stfs(base, (a), ctx->f[n].d)
#define FS(n, e)   (ctx->f[n].d = ctx->ps1[n] = frsp(e))
#define F(n)       (ctx->f[n].d)
#define FCMP(a, b) cr_fcmp(ctx, 0, (a), (b))
/* rlwinm rD, rS, 2, 0, 29 (an index times 4) */
#define X4(v)      (rotl32((v), 2) & 0xFFFFFFFCu)
/* a virtual call through the player's vtable (+96), the function through r12 into CTR, r3 = the player */
#define VCALL(ra, obj, slot) i2_vcall(ctx, base, (ra), (obj), (slot), 12)
/* a call through an object whose vtable is at +0 (state managers / methods / IDs, the sound object,
   effects): r12 = the function, CTR = r12, r3 = the object; tail = b (LR stays the caller's) */
static void pb_icall(GM_CTX, gptr obj, uint32_t slot, uint32_t ra, int tail) {
    R(12) = gm_u32(gm_u32(obj) + slot); R(3) = obj; ctx->ctr = R(12);
    if (!tail) ctx->lr = ra;
    ppc_call_indirect(ctx, base, ctx->ctr);
}
/* the flag natives (this file), as the recompiled code calls them */
#define SETFLAG(ra, f)   (R(4) = (f), BL((ra), hle_setFlag__10daPlBase_cFi))
#define CLEARFLAG(ra, f) (R(4) = (f), BL((ra), hle_clearFlag__10daPlBase_cFi))
#define TESTFLAG(ra, f)  (R(4) = (f), BL((ra), hle_testFlag__10daPlBase_cFi), CMPS(R(3), 0) != 0)

/* ================================================================== status flags
   mStatusFlags[id / 32] bit (id % 32): the PowerPC code divides with srawi / addze (rounding toward
   zero, XER[CA]) and builds the bit as rlwinm / subf / rotlw / add, so the registers it leaves
   (and r3 = the word's base for setStatus) follow that. */
/* srawi rq, id, 5; addze rq, rq: the word index into rq, XER[CA] as addze leaves it */
static void pb_flagWord(GM_CTX, uint32_t id, int rq) {
    (void)base;
    int32_t v = (int32_t)id;
    ctx->xer_ca = v < 0 && (id & 0x1Fu) != 0; R(rq) = (uint32_t)(v >> 5);
    uint64_t t = (uint64_t)R(rq) + ctx->xer_ca; R(rq) = (uint32_t)t; ctx->xer_ca = (uint32_t)(t >> 32);
}
/* setStatus(id): the word becomes just that bit */
static void pb_setStatus(GM_CTX, gptr self, uint32_t id) {
    int32_t v = (int32_t)id;
    ctx->xer_ca = v < 0 && (id & 0x1Fu) != 0; R(0) = (uint32_t)(v >> 5);
    R(6) = rotl32(id, 27) & 0xF8000000u;
    R(5) = rotl32(id, 1) & 1u;
    R(7) = 1;
    R(4) = R(6) - R(5);
    { uint64_t t = (uint64_t)R(0) + ctx->xer_ca; R(0) = (uint32_t)t; ctx->xer_ca = (uint32_t)(t >> 32); }
    R(4) = rotl32(R(4), 5);
    R(0) = X4(R(0));
    R(4) = R(4) + R(5);
    R(3) = self + R(0);
    R(0) = i2_bit(R(4));
    gm_set_u32(R(3) + PL_STATUS, R(0));
}
/* onStatus(id) / offStatus(id) */
static void pb_onOffStatus(GM_CTX, gptr self, uint32_t id, int on) {
    pb_flagWord(GM_PASS, id, 5);                                   /* (r5 = id / 32, CA) */
    R(0) = rotl32(id, 27) & 0xF8000000u;
    R(4) = rotl32(id, 1) & 1u;
    R(6) = X4(R(5));
    R(0) = R(0) - R(4);
    R(5) = 1;
    R(6) = self + R(6);
    R(0) = rotl32(R(0), 5);
    R(3) = gm_u32(R(6) + PL_STATUS);
    R(0) = R(0) + R(4);
    R(0) = i2_bit(R(0));
    R(0) = on ? R(3) | R(0) : R(3) & ~R(0);
    gm_set_u32(R(6) + PL_STATUS, R(0));
}
/* isStatus(id) (testFlag) */
static uint32_t pb_isStatus(GM_CTX, gptr self, uint32_t id) {
    pb_flagWord(GM_PASS, id, 0);                                   /* (r0 = id / 32, CA) */
    R(6) = rotl32(id, 27) & 0xF8000000u;
    R(5) = rotl32(id, 1) & 1u;
    R(7) = 1;
    R(4) = R(6) - R(5);
    R(0) = X4(R(0));
    R(4) = rotl32(R(4), 5);
    R(3) = self + R(0);
    R(4) = R(4) + R(5);
    R(0) = gm_u32(R(3) + PL_STATUS);
    R(3) = i2_bit(R(4)) & R(0);
    R(0) = (uint32_t)-(int32_t)R(3) | R(3);                              /* (neg / or / srwi 31: != 0) */
    R(3) = R(0) >> 31;
    return R(3);
}

/* ================================================================== the state machine's plumbing */
/* sStateID::null for the virtual states' base IDs: baseID_<name><sStateID_c>() - one copy per
   STATE_VIRTUAL_DEFINE (None ... WaitJump at 80047270, DemoNone ... DemoControl at 8004D6F0), each
   called once by the file's static initializer (fn_800592C0) */
static void pb_baseIDNull(GM_CTX) { (void)base; R(3) = STATE_ID_NULL; }

/* sStateMgr_c<daPlBase_c, sStateMethodUsr_FI_c, sFStateFct_c, sStateIDChk_c> (both of the player's
   state managers' vtables, mStateMgr and mDemoStateMgr): forward to the state method at +24 */
static void pb_stateMgr_call(GM_CTX, gptr mgr, uint32_t slot) { pb_icall(GM_PASS, mgr + SM_METHOD, slot, 0, 1); }

/* sFState_c<daPlBase_c>::initialize / execute / finalize: the state ID calls its method on the object */
static void pb_fstate_call(GM_CTX, gptr st, uint32_t slot) {
    R(4) = st; R(3) = gm_u32(st + ST_ID); R(4) = gm_u32(R(4) + ST_OBJ);
    R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + slot); ctx->ctr = R(12);
    ppc_call_indirect(ctx, base, ctx->ctr);
}
/* sFStateFct_c<daPlBase_c>::build(id): the factory's one state (at +4) for a non-null ID, else none */
static void pb_fstateFct_build(GM_CTX, gptr fct, gptr id) {
    I2_FN(0x80059120u);
    NV_R(31, id); NV_R(30, fct);
    R(3) = id; pb_icall(GM_PASS, id, SID_IS_NULL, 0x80059150u, 0);
    if (CMPS(R(3), 0) == 0) { gm_set_u32(fct + 12, id); R(3) = fct + 4; }
    else R(3) = 0;
}
/* sFStateFct_c<daPlBase_c>::dispose(state *&): the pointer cleared */
static void pb_fstateFct_dispose(GM_CTX, gptr pp) { R(0) = 0; gm_set_u32(pp, 0); }

/* create: the key, the title's forced walk to the right, the z position */
static void pb_create(GM_CTX, gptr self) {
    I2_FN(0x80046A50u);
    NV_R(31, self);
    R(3) = self + PL_KEY; BL(0x80046A6Cu, fn_8005E030);                  /* (mKey.init()) */
    R(0) = gm_u32(GAME_MODE);
    if (CMPS(R(0), 2) == 0) {                                            /* (the title: STATUS_FORCE_RIGHT) */
        R(3) = self + PL_KEY; R(4) = 8;
        BL(0x80046A84u, setFlag__14dPlayerInput_cFQ214dPlayerInput_c5Flags_8005E3B0);
    }
    VCALL(0x80046A98u, self, VT_SET_Z_POSITION);
    R(3) = 1;
}
/* doDelete: being deleted, the state finalized */
static void pb_doDelete(GM_CTX, gptr self) {
    I2_FN(0x80047190u);
    R(4) = STATUS_ABOUT_TO_BE_DELETED; R(0) = 1; NV_R(31, self);
    gm_set_u32(self + PL_BEING_DELETED, 1);
    BL(0x800471B4u, hle_setFlag__10daPlBase_cFi);
    pb_icall(GM_PASS, self + PL_STATE_MGR, SM_FINALIZE, 0x800471C8u, 0);
    R(3) = 1;
}
/* executeState: the substate timer counts down, then the state's frame */
static void pb_executeState(GM_CTX, gptr self) {
    R(4) = gm_u32(self + PL_SUBSTATE_TIMER);
    if (CMPS(R(4), 0) != 0) { R(0) = R(4) - 1; gm_set_u32(self + PL_SUBSTATE_TIMER, R(0)); }
    pb_icall(GM_PASS, self + PL_STATE_MGR, SM_EXECUTE, 0, 1);
}

/* ================================================================== the states' methods (small ones) */
/* finalizeState_Walk */
static void pb_finalizeState_Walk(GM_CTX) { R(4) = STATUS_52; hle_clearFlag__10daPlBase_cFi(ctx, base); }
/* executeState_Walk */
static void pb_executeState_Walk(GM_CTX, gptr self) {
    I2_FN(0x800477B0u);
    NV_R(31, self);
    if (TESTFLAG(0x800477CCu, STATUS_52)) { R(3) = self; CLEARFLAG(0x800477E0u, STATUS_52); }
}
/* initializeState_Jump */
static void pb_initializeState_Jump(GM_CTX, gptr self) {
    I2_FN(0x800479A0u);
    NV_R(31, self);
    SETFLAG(0x800479BCu, STATUS_A0);
    R(3) = self; SETFLAG(0x800479C8u, STATUS_A5);
    R(3) = self; CLEARFLAG(0x800479D4u, STATUS_88);
    R(0) = gm_u32(self + PL_JUMP_DAI_TIMER);
    if (CMPS(R(0), 0) != 0) { R(3) = self; SETFLAG(0x800479ECu, STATUS_JUMP_DAI_COOLDOWN); }
}
/* finalizeState_Fall */
static void pb_finalizeState_Fall(GM_CTX, gptr self) {
    I2_FN(0x80047D10u);
    NV_R(31, self);
    CLEARFLAG(0x80047D2Cu, STATUS_A0);
    R(3) = self; CLEARFLAG(0x80047D38u, STATUS_88);
    R(3) = self; CLEARFLAG(0x80047D44u, STATUS_JUMP_DAI_COOLDOWN);
    R(0) = 0; gm_set_u32(self + PL_JUMP_DAI_TIMER, 0);
}
/* executeState_Fall */
static void pb_executeState_Fall(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_JUMP_DAI_TIMER);
    if (CMPS(R(0), 0) != 0) return;
    R(4) = STATUS_JUMP_DAI_COOLDOWN; hle_clearFlag__10daPlBase_cFi(ctx, base);
}
/* finalizeState_Slip */
static void pb_finalizeState_Slip(GM_CTX, gptr self) {
    I2_FN(0x80048170u);
    NV_R(31, self);
    CLEARFLAG(0x8004818Cu, STATUS_SLIP_ACTIVE);
    R(3) = self; CLEARFLAG(0x80048198u, STATUS_97);
    R(0) = 0; gm_set_u16(self + PL_ANGLE_X, 0);
}
/* finalizeState_PlayerJumpDai */
static void pb_finalizeState_PlayerJumpDai(GM_CTX, gptr self) {
    I2_FN(0x80049F50u);
    NV_R(31, self);
    CLEARFLAG(0x80049F6Cu, STATUS_PLAYER_JUMP);
    R(3) = self; CLEARFLAG(0x80049F78u, STATUS_BIG_JUMP);
    R(0) = 0; gm_set_u32(self + PL_RIDE_ACTOR_ID, 0);
}
/* finalizeState_WaitJump */
static void pb_finalizeState_WaitJump(GM_CTX, gptr self) {
    I2_FN(0x8004B090u);
    NV_R(31, self);
    CLEARFLAG(0x8004B0ACu, STATUS_WAIT_JUMP);
    R(3) = self + PL_KEY; R(4) = 4; BL(0x8004B0B8u, fn_8005E460);       /* (mKey.offStatus(STATUS_FORCE_NO_JUMP)) */
}
/* endDemoInDokan (also finalizeState_DemoInDokanU) */
static void pb_endDemoInDokan(GM_CTX, gptr self) {
    I2_FN(0x8004EA20u);
    R(4) = STATUS_CAN_WATER_WALK; R(0) = 0; NV_R(31, self);
    gm_set_u32(self + PL_DAMAGE_INVULN, 0); gm_set_u32(self + PL_POWERUP_INVULN, 0);
    BL(0x8004EA48u, hle_clearFlag__10daPlBase_cFi);
    R(3) = self; CLEARFLAG(0x8004EA54u, STATUS_PROPEL_NO_ROLL);
    R(3) = self; CLEARFLAG(0x8004EA60u, STATUS_5E);
}
/* demo_dokan_move_y(speed, offset): mPos.y chases mGotoPos.y + offset (sLib::chase) */
static void pb_demo_dokan_move_y(GM_CTX, gptr self) {
    ctx->f[3].u = ctx->f[1].u;
    LDF(0, self + PL_GOTO_POS_Y);
    R(3) = self + PL_POS_Y;
    FS(1, F(0) + F(2));
    ctx->f[2].u = ctx->f[3].u;
    fn_8015F470(ctx, base);
}
/* initializeState_DemoGoal: initDemoGoalBase (virtual, a tail call) */
static void pb_initializeState_DemoGoal(GM_CTX, gptr self) {
    R(12) = gm_u32(self + PL_VTABLE); R(12) = gm_u32(R(12) + VT_INIT_GOAL_BASE); ctx->ctr = R(12);
    ppc_call_indirect(ctx, base, ctx->ctr);
}
/* setDemoGoalMode(mode, param) */
static void pb_setDemoGoalMode(GM_CTX, gptr self, uint32_t mode, uint32_t param) {
    (void)ctx; (void)base;
    gm_set_u32(self + PL_DEMO_SUBSTATE, mode); gm_set_u8(self + PL_DEMO_STATE, (uint8_t)param);
}
/* initialDokanUper: into the up pipe demo */
static void pb_initialDokanUper(GM_CTX) { R(4) = STATE_DEMO_IN_DOKAN_U; R(5) = 0; hle_fn_8004E290(ctx, base); }
/* setCreateAction(action): l_createActionProc[action] (a pointer to member function) */
static void pb_setCreateAction(GM_CTX, uint32_t action) {
    I2_FN(0x8004DB00u);
    R(0) = (uint32_t)((int32_t)action * 12);
    R(4) = CREATE_ACTION_PROC; R(12) = R(4) + R(0);
    BL(0x8004DB20u, __ptmf_scall_802DCBFC);
}

/* ================================================================== sLib::calcTimer<T> (this file's copies) */
static void pb_calcTimer_s8(GM_CTX, gptr p) {
    (void)base;
    R(4) = gm_u8(p); R(0) = (uint32_t)(int8_t)R(4);
    if (CMPS(R(0), 0) != 0) { R(0) = R(4) - 1; gm_set_u8(p, (uint8_t)R(0)); }
    R(3) = gm_u8(p);
}
static void pb_calcTimer_int(GM_CTX, gptr p) {
    (void)base;
    R(4) = gm_u32(p);
    if (CMPS(R(4), 0) != 0) { R(0) = R(4) - 1; gm_set_u32(p, R(0)); }
    R(3) = gm_u32(p);
}

/* ================================================================== direction / angles */
/* getMukiAngle(direction): scMukiAngle[direction] */
static void pb_getMukiAngle(GM_CTX, uint32_t dir) {
    R(0) = rotl32(dir, 1) & 0x1FEu; R(3) = MUKI_ANGLE;
    R(3) = (uint32_t)(int16_t)gm_u16(R(3) + R(0));
}
/* turnAngle: mAngle.y chases the facing angle (0x2000 a frame) */
static void pb_turnAngle(GM_CTX, gptr self) {
    I2_FN(0x80047490u);
    NV_R(31, self);
    R(4) = gm_u8(self + PL_DIRECTION);
    VCALL(0x800474B8u, self, VT_GET_MUKI_ANGLE);
    R(0) = R(3); R(3) = self + PL_ANGLE_Y; R(4) = (uint32_t)(int16_t)R(0); R(5) = 0x2000;
    BL(0x800474CCu, hle_fn_8015F340);                                    /* (mAng::chase) */
}
/* addCalcAngleY(target, scale): sLib::addCalcAngle(&mAngle.y, target, scale, 0x2000, 0x400) */
static void pb_addCalcAngleY(GM_CTX, gptr self) {
    I2_FN(0x800474E0u);
    R(4) = (uint32_t)(int16_t)R(4); R(5) = (uint32_t)(int16_t)R(5);
    R(6) = 0x2000; R(7) = 0x400; R(3) = self + PL_ANGLE_Y;
    BL(0x80047504u, hle_fn_8015F200);
    R(3) = (uint32_t)(int16_t)R(3);
}
/* checkRideActor(other): one rides the other */
static void pb_checkRideActor(GM_CTX, gptr self, gptr other) {
    (void)base;
    R(5) = gm_u32(self + PL_RIDE_ACTOR_ID); R(0) = gm_u32(other + PL_UNIQUE_ID);
    if (CMPS(R(5), R(0)) == 0) { R(3) = 1; return; }
    R(4) = gm_u32(other + PL_RIDE_ACTOR_ID); R(0) = gm_u32(self + PL_UNIQUE_ID);
    R(3) = CMPS(R(4), R(0)) == 0;
}
/* setTurnEnd: face the direction, walk */
static void pb_setTurnEnd(GM_CTX, gptr self) {
    I2_FN(0x80048BA0u);
    NV_R(31, self);
    R(4) = gm_u8(self + PL_DIRECTION);
    VCALL(0x80048BC8u, self, VT_GET_MUKI_ANGLE);
    gm_set_u16(self + PL_ANGLE_Y, (uint16_t)R(3));
    R(4) = STATE_WALK; R(5) = 0;
    VCALL(0x80048BECu, self, VT_CHANGE_STATE);
}

/* ================================================================== crouch / slopes / speed */
/* checkStandUpRoofOnLift: on the ground and not on a lift: no roof check */
static void pb_checkStandUpRoofOnLift(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1u; CR0(ctx, R(0));
    if (R(0)) {
        R(0) = gm_u32(self + PL_NOW_BG_CROSS2) & 2u; CR0(ctx, R(0));
        if (!R(0)) { R(3) = 0; return; }
    }
    hle_fn_80047F10(ctx, base);                                              /* (checkStandUpRoof) */
}
/* checkSakaReverse: hardly moving on a slope's reverse side */
static void pb_checkSakaReverse(GM_CTX, gptr self) {
    LDF(1, self + PL_SPEED_F); LDF(0, F_HALF);
    ctx->f[1].u &= ~0x8000000000000000ull; ctx->f[1].d = frsp(F(1));
    FCMP(F(1), F(0));
    if (!CR_BIT(ctx, 0)) { R(3) = 0; return; }
    R(0) = gm_u8(self + BC_PLAYER_FLAGS) & 4u; CR0(ctx, R(0));
    R(3) = R(0) != 0;
}
/* isSaka: on a slope */
static void pb_isSaka(GM_CTX, gptr self) {
    (void)base;
    R(0) = gm_u32(self + PL_NOW_BG_CROSS2) & 0x80u; CR0(ctx, R(0));
    R(3) = R(0) != 0;
}
/* isSlipSaka: on a slope that isn't attribute 10 */
static void pb_isSlipSaka(GM_CTX, gptr self) {
    I2_FN(0x8004B1C0u);
    NV_R(31, self);
    BL(0x8004B1D8u, hle_fn_8004B1A0);
    if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
    R(3) = self + PL_BC; BL(0x8004B1E8u, getFootAttr__5dBc_cFv_80070720);
    R(0) = R(3) & 0xFFFFu;
    R(3) = CMPU(R(0), 10) != 0;
}
/* checkSlip: on an auto-slip slope (moving right or not at the left limit): slip */
static void pb_checkSlip(GM_CTX, gptr self) {
    I2_FN(0x8004B290u);
    LDF(0, F_ZERO); LDF(1, self + PL_SPEED_F);
    FCMP(F(1), F(0));
    if (!CR_BIT(ctx, 1)) {
        R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x80000u; CR0(ctx, R(0));
        if (R(0)) { R(3) = 0; return; }
    }
    R(0) = gm_u32(self + PL_NOW_BG_CROSS2) & 8u; CR0(ctx, R(0));
    if (!R(0)) { R(3) = 0; return; }
    VCALL(0x8004B2D4u, self, VT_SET_SLIP_ACTION);
    R(3) = 1;
}
/* getSlipMaxSpeedF: on a slope sc_DirSpeed[slope direction] * 4, else 0 */
static void pb_getSlipMaxSpeedF(GM_CTX, gptr self) {
    I2_FN(0x8004B460u);
    NV_R(31, self);
    BL(0x8004B478u, hle_fn_8004B1A0);
    if (CMPS(R(3), 0) == 0) { LDF(1, F_ZERO); return; }
    R(3) = self + PL_BC; BL(0x8004B488u, getSakaDir__5dBc_cFv_800707E0);
    R(0) = X4(R(3)); R(3) = DIR_SPEED;
    LDF(1, R(3) + R(0)); LDF(0, F_FOUR);
    FS(1, F(0) * F(1));
}
/* getSakaMaxSpeedRatio / getSakaStopAccele / getSakaMoveAccele(direction): table[type][updown] */
static void pb_getSakaTable(GM_CTX, gptr self, uint32_t fn, uint32_t ra1, uint32_t ra2, uint32_t table) {
    I2_FN(fn); /* FNADDR 0x8004B4C0 0x8004B520 0x8004B580 */
    NV_R(30, self);
    R(3) = self + PL_BC; BL(ra1, getSakaUpDown__5dBc_cFUc_80070820);   /* (r4: the direction, passed on) */
    NV_R(31, X4(R(3)));
    R(3) = self + PL_BC; BL(ra2, getSakaType__5dBc_cFv_80070760);
    R(0) = (uint32_t)((int32_t)R(3) * 12); R(3) = table;
    R(0) = R(31) + R(0);
    LDF(1, R(3) + R(0));
}
/* powerSet: on the ground grandPowerSet, else airPowerSet */
static void pb_powerSet(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1u; CR0(ctx, R(0));
    if (R(0)) hle_fn_8004BA50(ctx, base); else hle_fn_8004C310(ctx, base);
}
/* maxFallSpeedSet */
static void pb_maxFallSpeedSet(GM_CTX, gptr self) { LDF(0, F_MAX_FALL); STF(self + PL_MAX_FALL_SPEED, 0); }
/* getSpeedData: the star's or the normal one */
static void pb_getSpeedData(GM_CTX, gptr self) {
    I2_FN(0x80057650u);
    NV_R(31, self);
    VCALL(0x80057674u, self, VT_IS_STAR);
    R(3) = CMPS(R(3), 0) != 0 ? gm_u32(self + PL_SPEED_DATA_STAR) : gm_u32(self + PL_SPEED_DATA);
}
/* setJumpAddSpeedF(a) (recompiled as modifyPlayerPropertiesWithRollingObject): in the air, the push
   kept to [-2, 2] in mFinalAirPushForceX */
static void pb_setJumpAddSpeedF(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1u; CR0(ctx, R(0));
    if (R(0)) return;
    LDF(0, F_TWO); FCMP(F(1), F(0));
    CR_SETBIT(ctx, 2, CR_BIT(ctx, 1) | CR_BIT(ctx, 2));                  /* (cror eq, gt, eq: >=) */
    if (CR_BIT(ctx, 2)) ctx->f[1].u = ctx->f[0].u;
    LDF(0, F_MINUS_TWO); FCMP(F(1), F(0));
    CR_SETBIT(ctx, 2, CR_BIT(ctx, 0) | CR_BIT(ctx, 2));                  /* (<=) */
    if (CR_BIT(ctx, 2)) ctx->f[1].u = ctx->f[0].u;
    STF(self + PL_AIR_PUSH_X, 1);
}
/* checkJumpTrigger: on the ground, not at a cliff: startJump(BLEND_DEFAULT, 1) */
static void pb_checkJumpTrigger(GM_CTX, gptr self) {
    I2_FN(0x80057AD0u);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1u; CR0(ctx, R(0));
    if (!R(0)) { R(3) = 0; return; }
    R(0) = gm_u32(self + PL_NOW_BG_CROSS2) & 0x100u; CR0(ctx, R(0));
    if (R(0)) { R(3) = 0; return; }
    R(4) = 1; R(5) = 1; BL(0x80057B00u, hle_fn_800579C0);
    R(3) = CMPS(R(3), 0) != 0;
}
/* setZPositionDirect(z) */
static void pb_setZPositionDirect(GM_CTX, gptr self) {
    I2_FN(0x800577D0u);
    R(4) = STATUS_99; ctx->f[31].u = ctx->f[1].u; NV_R(31, self);
    BL(0x800577F4u, hle_setFlag__10daPlBase_cFi);
    STF(self + PL_POS_Z, 31);
}

/* ================================================================== hip attack */
/* setHipBlockBreak: big enough to break blocks */
static void pb_setHipBlockBreak(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_POWERUP);
    R(4) = STATUS_C4;
    if (CMPS(R(0), 3) == 0 || CMPS(R(0), 0) == 0) hle_clearFlag__10daPlBase_cFi(ctx, base);
    else hle_setFlag__10daPlBase_cFi(ctx, base);
}
/* HipAction_Ready: the animation done: the attack starts */
static void pb_HipAction_Ready(GM_CTX, gptr self) {
    I2_FN(0x800491F0u);
    NV_R(31, self);
    R(4) = gm_u32(self + PL_MDL_MNG); R(3) = gm_u32(R(4) + 4); R(3) += 40;
    BL(0x80049214u, hle_isAnimationDone__Q23m3d6fanm_cFv);
    if (CMPS(R(3), 0) != 0) VCALL(0x80049230u, self, VT_SET_HIP_START);
}
/* HipAction_AttackStart: the substate timer out: the fall */
static void pb_HipAction_AttackStart(GM_CTX, gptr self) {
    R(0) = gm_u32(self + PL_SUBSTATE_TIMER);
    if (CMPS(R(0), 0) != 0) return;
    hle_fn_80048FA0(ctx, base);                                          /* (setHipAttack_AttackFall) */
}

/* ================================================================== demo queries */
/* isDemoAll: isDemo or isControlDemoAll */
static void pb_isDemoAll(GM_CTX, gptr self) {
    I2_FN(0x8004DDE0u);
    NV_R(31, self);
    BL(0x8004DDF8u, hle_fn_8004DD00);
    if (CMPS(R(3), 0) != 0) { R(3) = 1; return; }
    R(3) = self; BL(0x8004DE08u, hle_fn_8004DD70);
    R(3) = CMPS(R(3), 0) != 0;
}
/* isDemoMode */
static void pb_isDemoMode(GM_CTX, gptr self) {
    (void)base;
    R(3) = gm_u8(self + PL_IS_DEMO_MODE);
    R(0) = (uint32_t)-(int32_t)R(3) | R(3); R(3) = R(0) >> 31;
}
/* isPlayerGameStop: dInfo_c::mGameFlag bit 1 */
static void pb_isPlayerGameStop(GM_CTX) {
    (void)base;
    R(0) = gm_u32(GAME_FLAG); R(3) = rotl32(R(0), 31) & 1u;
}
/* checkTimeOut: the timer at 0 (dStageTimer_c::convertToIGT): setTimeOverDemo */
static void pb_checkTimeOut(GM_CTX, gptr self) {
    I2_FN(0x8004E220u);
    R(4) = gm_u32(STAGE_TIMER_P); R(4) = gm_u32(R(4) + 4);
    R(0) = R(4) + 4095;
    { int32_t v = (int32_t)R(0); ctx->xer_ca = v < 0 && (R(0) & 0xFFFu) != 0; R(0) = (uint32_t)(v >> 12); }
    R(0) = (uint32_t)(int16_t)R(0); CR0(ctx, R(0));
    if (R(0)) { R(3) = 0; return; }
    VCALL(0x8004E254u, self, VT_SET_TIME_OVER);
    R(3) = CMPS(R(3), 0) != 0;
}

/* ================================================================== collision */
/* getCcLineKind: on a vine fence its layer, else 3 */
static void pb_getCcLineKind(GM_CTX, gptr self) {
    (void)base;
    R(0) = gm_u32(self + PL_NOW_BG_CROSS2) & 0x180000u; CR0(ctx, R(0));
    R(3) = R(0) ? gm_u8(self + PL_AMI_LAYER) : 3;
}
/* clearCcData: the five collisions cleared */
static void pb_clearCcData(GM_CTX, gptr self) {
    I2_FN(0x80053600u);
    NV_R(31, self);
    R(3) = self + PL_CC;     BL(0x8005361Cu, hle_clear__13ActivePhysicsFv);
    R(3) = self + 4452;      BL(0x80053624u, hle_clear__13ActivePhysicsFv);   /* (mCc1) */
    R(3) = self + PL_ATT_CC1; BL(0x8005362Cu, hle_clear__13ActivePhysicsFv);
    R(3) = self + PL_ATT_CC2; BL(0x80053634u, hle_clear__13ActivePhysicsFv);
    R(3) = self + 4944;      BL(0x8005363Cu, hle_clear__13ActivePhysicsFv);   /* (mAttCc3) */
}
/* setCcAtBody(attack): both attack collisions take the body's box and the attack */
static void pb_setCcAtBody(GM_CTX, gptr self, uint32_t attack) {
    R(0) = gm_u32(self + PL_CC + CC_VS_KIND); R(5) = 7;
    LDF(0, self + PL_CC + CC_OFFSET + 4); LDF(1, self + PL_CC + CC_OFFSET);
    R(0) &= 0xFFFFFFF8u;                                                 /* (not players, player attacks, Yoshis) */
    LDF(2, self + PL_CC + CC_OFFSET + 12); LDF(3, self + PL_CC + CC_OFFSET + 8);
    STF(self + PL_ATT_CC2 + CC_OFFSET, 1); STF(self + PL_ATT_CC2 + CC_OFFSET + 4, 0);
    STF(self + PL_ATT_CC2 + CC_OFFSET + 8, 3); STF(self + PL_ATT_CC2 + CC_OFFSET + 12, 2);
    gm_set_u8(self + PL_ATT_CC2 + CC_ATTACK, (uint8_t)attack); gm_set_u32(self + PL_ATT_CC2 + CC_VS_KIND, R(5));
    STF(self + PL_ATT_CC1 + CC_OFFSET, 1); STF(self + PL_ATT_CC1 + CC_OFFSET + 4, 0);
    STF(self + PL_ATT_CC1 + CC_OFFSET + 8, 3); STF(self + PL_ATT_CC1 + CC_OFFSET + 12, 2);
    gm_set_u8(self + PL_ATT_CC1 + CC_ATTACK, (uint8_t)attack); gm_set_u32(self + PL_ATT_CC1 + CC_VS_KIND, R(0));
}
/* setCcAtSlip: CC_ATTACK_SLIP (5) */
static void pb_setCcAtSlip(GM_CTX) { R(4) = 5; hle_fn_80053650(ctx, base); }
/* setCcAtHipAttack: CC_ATTACK_HIP_ATTACK (7), no damage kinds */
static void pb_setCcAtHipAttack(GM_CTX, gptr self) {
    I2_FN(0x80053700u);
    R(4) = 7; NV_R(31, self);
    BL(0x8005371Cu, hle_fn_80053650);
    R(0) = 0; gm_set_u32(self + PL_ATT_CC2 + CC_VS_DAMAGE, 0); gm_set_u32(self + PL_ATT_CC1 + CC_VS_DAMAGE, 0);
}
/* isActionRevisionY: on a pole or a rope */
static void pb_isActionRevisionY(GM_CTX, gptr self) {
    I2_FN(0x800538E0u);
    NV_R(31, self);
    if (TESTFLAG(0x800538FCu, STATUS_POLE)) { R(3) = 1; return; }
    R(3) = self;
    R(3) = TESTFLAG(0x80053910u, STATUS_TARZAN_ROPE);
}
/* clearCcPlayerRev */
static void pb_clearCcPlayerRev(GM_CTX, gptr self) {
    LDF(0, F_ZERO); R(0) = 0;
    STF(self + PL_CC_REV + 12, 0); STF(self + PL_CC_REV, 0); STF(self + PL_CC_REV + 4, 0); STF(self + PL_CC_REV + 8, 0);
    gm_set_u8(self + PL_CC_REV_SET, 0); gm_set_u8(self + PL_CC_REV_SET + 1, 0);
}

/* ================================================================== the squish (reduction) */
/* setReductionScale: setReductionBoyon, initStampReduction (both virtual) */
static void pb_setReductionScale(GM_CTX, gptr self) {
    I2_FN(0x80053F90u);
    NV_R(31, self);
    VCALL(0x80053FB4u, self, VT_SET_RED_BOYON);
    VCALL(0x80053FC8u, self, VT_INIT_STAMP_RED);
}
/* calcJumpDaiReductionScale(i1, i2): mSquishScale = min(i1, i2) * 0.6f / i2 (the int -> float
   conversions through the frame, as the PowerPC code does them) */
static void pb_calcJumpDaiReductionScale(GM_CTX, gptr self) {
    CMPS(R(4), R(5));
    uint32_t sp = R(1) - 32; gm_set_u32(sp, R(1));                       /* (stwu r1, -32: a frame of its own) */
    if (CR_BIT(ctx, 1)) R(4) = R(5);
    R(6) = 0x43300000u; R(0) = R(4) ^ 0x80000000u;
    gm_set_u32(sp + 12, R(0));
    R(4) = R(5) ^ 0x80000000u;
    ctx->f[3].u = ld64(base, D_INT_TO_FLOAT);
    R(0) = 1;
    gm_set_u32(sp + 8, R(6));
    LDF(1, F_JUMPDAI_RED);
    ctx->f[0].u = ld64(base, sp + 8);
    gm_set_u32(sp + 20, R(4));
    FS(2, F(0) - F(3));
    gm_set_u32(sp + 16, R(6));
    ctx->f[0].u = ld64(base, sp + 16);
    FS(1, F(1) * F(2));
    gm_set_u32(self + PL_SQUISH_STATE, R(0));
    FS(0, F(0) - F(3));
    FS(0, F(1) / F(0));
    STF(self + PL_SQUISH_SCALE, 0);
}
/* setReductionBoyon: SQUISH_ANIMATION from keyframe 4 */
static void pb_setReductionBoyon(GM_CTX, gptr self) {
    (void)base;
    R(4) = 3; R(0) = 4;
    gm_set_u32(self + PL_SQUISH_STATE, 3); gm_set_u32(self + PL_SQUISH_KEYFRAME, 4);
}
/* getReductionModelScale (the result through r3): (1 + s, 1 - s, 1 + s) */
static void pb_getReductionModelScale(GM_CTX, gptr out, gptr self) {
    LDF(1, F_ONE); LDF(0, self + PL_SQUISH_SCALE);
    FS(2, F(1) + F(0)); FS(0, F(1) - F(0));
    STF(out, 2); STF(out + 4, 0); STF(out + 8, 2);
}

/* ================================================================== players / objects not hit, presses */
/* setNoHitPlayer(player, duration) */
static void pb_setNoHitPlayer(GM_CTX, gptr self, uint32_t pl, uint32_t t) {
    (void)ctx; (void)base;
    gm_set_u32(self + PL_NO_HIT_PLAYER, pl); gm_set_u32(self + PL_NO_HIT_TIMER, t);
}
/* updateNoHitPlayer */
static void pb_updateNoHitPlayer(GM_CTX, gptr self) {
    (void)base;
    R(4) = gm_u32(self + PL_NO_HIT_TIMER);
    if (CMPS(R(4), 0) != 0) { R(0) = R(4) - 1; gm_set_u32(self + PL_NO_HIT_TIMER, R(0)); }
    R(0) = gm_u32(self + PL_NO_HIT_TIMER);
    if (CMPS(R(0), 0) != 0) return;
    R(0) = 0; gm_set_u32(self + PL_NO_HIT_PLAYER, 0);
}
/* clearHipAttackDamagePlayer */
static void pb_clearHipAttackDamagePlayer(GM_CTX, gptr self) {
    I2_FN(0x80054280u);
    NV_R(31, self);
    CLEARFLAG(0x8005429Cu, STATUS_HIP_ATTACK_DAMAGE_PLAYER);
    R(0) = 0; gm_set_u32(self + PL_HIP_DMG_PLR_ID, 0);
}
/* calcNoHitObjBgTimer: the timer out: the background collides with the object again */
static void pb_calcNoHitObjBgTimer(GM_CTX, gptr self) {
    (void)base;
    R(0) = gm_u32(self + PL_NO_HIT_OBJ_TIMER);
    if (CMPS(R(0), 0) == 0) return;
    { uint32_t a = R(0); R(0) = a - 1; ctx->xer_ca = a != 0; }          /* (addic. r0, r0, -1) */
    CR0(ctx, R(0));
    gm_set_u32(self + PL_NO_HIT_OBJ_TIMER, R(0));
    if (R(0)) return;
    R(0) = 0; gm_set_u32(self + BC_NO_HIT_ACTOR, 0);
}
/* setBgPressReq(actor, kind) (recompiled as HurtMarioBecauseOfBeingSquashed): the press bit, the
   presser's ID (r3 ends as the player + 4 * kind) */
static void pb_setBgPressReq(GM_CTX, gptr self, gptr actor, uint32_t kind) {
    R(0) = 1; R(6) = gm_u32(self + PL_BG_PRESS_ACTIVE);
    R(0) = i2_bit(kind);
    int none = CMPS(actor, 0) == 0;
    R(0) = R(6) | R(0);
    gm_set_u32(self + PL_BG_PRESS_ACTIVE, R(0));
    R(0) = X4(kind);
    R(4) = none ? 0 : gm_u32(actor + PL_UNIQUE_ID);
    R(3) = self + R(0);
    gm_set_u32(R(3) + PL_BG_PRESS_IDS, R(4));
}
/* isEnablePressLR: not when both walls belong to the same thing */
static void pb_isEnablePressLR(GM_CTX, gptr self) {
    (void)base;
    R(4) = gm_u32(self + BC_CTR_WALL_L); R(5) = gm_u32(self + BC_CTR_WALL_R);
    if (CMPS(R(4), 0) == 0 || CMPS(R(5), 0) == 0) { R(3) = 1; return; }
    if (CMPU(R(4), R(5)) == 0) { R(3) = 0; return; }
    R(3) = gm_u32(R(4) + BG_CTR_E0); R(0) = gm_u32(R(5) + BG_CTR_E0);
    R(3) = CMPS(R(3), R(0)) != 0;
}
/* getWaterCheckPosY: mPos.y + scWaterOffsetY[getTallType(-1)] */
static void pb_getWaterCheckPosY(GM_CTX, gptr self) {
    I2_FN(0x800552D0u);
    R(4) = (uint32_t)-1; NV_R(31, self);
    VCALL(0x800552F8u, self, VT_GET_TALL_TYPE);
    R(4) = 0x802F0000u; LDF(0, self + PL_POS_Y);
    R(0) = rotl32(R(3), 2) & 0x3FCu;
    R(4) = WATER_OFFSET_Y;
    LDF(1, R(4) + R(0));
    FS(1, F(0) + F(1));
}

/* ================================================================== power-up, counters, getters */
static void pb_setPowerup(GM_CTX, gptr self, uint32_t p) { (void)ctx; (void)base; gm_set_u32(self + PL_POWERUP, p); }
/* isMameAction: mini, and not lifting something */
static void pb_isMameAction(GM_CTX, gptr self) {
    I2_FN(0x80056BD0u);
    R(0) = gm_u32(self + PL_POWERUP);
    if (CMPS(R(0), 3) != 0) { R(3) = 0; return; }
    VCALL(0x80056BF8u, self, VT_IS_LIFT_UP_EX_MAME);
    R(3) = CMPS(R(3), 0) == 0;
}
/* setSoundPlyMode: the sound object's mode from scPlayerSound[mPowerup] */
static void pb_setSoundPlyMode(GM_CTX, gptr self) {
    (void)base;
    R(0) = pu_tab(gm_u32(self + PL_POWERUP)); R(4) = PLAYER_SOUND_MODE;
    R(0) = X4(R(0)); R(0) = gm_u32(R(4) + R(0));
    gm_set_u32(self + PL_SND_PLY_MODE, R(0));
}
/* clearFollowMameKuribo: the count this frame becomes the count, the new count 0 */
static void pb_clearFollowMameKuribo(GM_CTX, gptr self) {
    I2_FN(0x80057C80u);
    NV_R(31, self);
    CLEARFLAG(0x80057C9Cu, STATUS_FOLLOW_MAME_KURIBO);
    R(3) = gm_u32(self + PL_NEW_FOLLOW_MAME); R(0) = 0;
    gm_set_u32(self + PL_FOLLOW_MAME, R(3)); gm_set_u32(self + PL_NEW_FOLLOW_MAME, 0);
}
/* isMaskDraw: neither STATUS_53 nor STATUS_64 */
static void pb_isMaskDraw(GM_CTX, gptr self) {
    I2_FN(0x80057CD0u);
    NV_R(31, self);
    if (TESTFLAG(0x80057CECu, STATUS_53)) { R(3) = 0; return; }
    R(3) = self;
    R(3) = !TESTFLAG(0x80057D00u, STATUS_64);
}
/* clearTreadCount / clearStarCount / clearComboCount */
static void pb_clearCount(GM_CTX, gptr self, uint32_t off) { (void)base; R(0) = 0; gm_set_u8(self + off, 0); }
/* calcTreadCount(max): counts up to max (returned zero-extended, as lbz leaves it) */
static void pb_calcTreadCount(GM_CTX, gptr self, uint32_t max) {
    (void)base;
    R(5) = gm_u8(self + PL_TREAD_COUNT); R(0) = (uint32_t)(int8_t)R(5);
    if (CMPS(R(0), max) < 0) { R(0) = R(5) + 1; gm_set_u8(self + PL_TREAD_COUNT, (uint8_t)R(0)); }
    R(3) = gm_u8(self + PL_TREAD_COUNT);
}

/* ================================================================== effects, quakes, rumble */
/* setSandFunsuiLandEffect: on a sand fountain, its smoke */
static void pb_setSandFunsuiLandEffect(GM_CTX, gptr self) {
    I2_FN(0x8004CD20u);
    R(5) = self; R(0) = gm_u32(self + PL_GROUND_TYPE);
    if (CMPS(R(0), 7) != 0) { R(3) = 0; return; }
    R(3) = gm_u8(self + PL_PLAYER_NO); R(6) = self + PL_POS; R(5) = 0; R(4) = EF_SPSMOKE;
    R(3) = (uint32_t)(int8_t)R(3); R(7) = 0; R(8) = 0;
    BL(0x8004CD60u, hle_createPlayerEffect__3dEfFiPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
    R(3) = 1;
}
/* fadeOutTurnEffect */
static void pb_fadeOutTurnEffect(GM_CTX, gptr self) {
    I2_FN(0x8004D210u);
    NV_R(31, self);
    R(0) = gm_u8(self + PL_TURN_EFF_FADE);
    if (CMPU(R(0), 1) != 0) return;
    pb_icall(GM_PASS, self + PL_TURN_SMOKE_EFF, EF_FOLLOW_FADE, 0x8004D240u, 0);
    R(0) = 0; gm_set_u8(self + PL_TURN_EFF_FADE, 0);
}
/* startQuakeShock(type): dQuake_c::m_instance->shockMotor(mPlayerNo, type, 0, false) */
static void pb_startQuakeShock(GM_CTX, gptr self, uint32_t type) {
    R(5) = self; R(3) = gm_u32(QUAKE_P); R(0) = gm_u8(self + PL_PLAYER_NO);
    R(5) = type; R(6) = 0; R(7) = 0; R(4) = (uint32_t)(int8_t)R(0);
    shockMotor__8dQuake_cFScQ28dQuake_c12TYPE_SHOCK_eib_800D8BB0(ctx, base);
}
/* startPatternRumble(pattern): the player's remote, if its rumble is on */
static void pb_startPatternRumble(GM_CTX, gptr self) {
    R(0) = gm_u8(self + PL_PLAYER_NO); R(3) = gm_u32(REMOCON_MNG_P);
    R(0) = (uint32_t)(int8_t)R(0); R(0) = X4(R(0));
    R(3) = R(3) + R(0); R(3) = gm_u32(R(3) + 4);                         /* (mRemocons[mPlayerNo]) */
    R(0) = gm_u8(R(3) + 85);                                             /* (mIsRumbleEnabled) */
    if (CMPS(R(0), 0) == 0) return;
    R(0) = gm_u32(R(3) + 4);                                             /* (mControllerID) */
    R(3) = g_mod_on ? RUMBLE_CORES_MOD : RUMBLE_CORES;
    R(5) = 0; R(0) = X4(R(0)); R(6) = 0;
    R(3) = gm_u32(R(3) + R(0));
    startPatternRumble__Q23EGG14CoreControllerFPCcib_802BC980(ctx, base);
}

/* ================================================================== sounds */
/* startSound(id, mode) / holdSound(id, mode) (startSound recompiled as PlayPlayerSound): unless
   suppressed, the sound object's startSound / holdSound(id, 0) */
static void pb_sound(GM_CTX, gptr self, uint32_t fn, uint32_t ra_sup, uint32_t slot, uint32_t ra) {
    I2_FN(fn); /* FNADDR 0x80057E70 0x80057F60 */
    NV_R(31, R(4)); R(4) = R(5); NV_R(30, self);
    BL(ra_sup, hle_fn_80057E00);                                         /* (suppressSound) */
    if (CMPS(R(3), 0) != 0) return;
    R(12) = gm_u32(self + PL_SND_OBJ); R(3) = self + PL_SND_OBJ; R(4) = R(31); R(5) = 0;
    R(12) = gm_u32(R(12) + slot); ctx->ctr = R(12);
    ctx->lr = ra; ppc_call_indirect(ctx, base, ctx->ctr);
}
/* startPlayerVoice(voice, mode) */
static void pb_startPlayerVoice(GM_CTX, gptr self) {
    I2_FN(0x80058050u);
    NV_R(31, R(4)); R(4) = R(5); NV_R(30, self);
    BL(0x80058074u, hle_fn_80057E00);
    if (CMPS(R(3), 0) != 0) return;
    R(4) = R(31); R(3) = self + PL_SND_OBJ; R(5) = 0;
    BL(0x8005808Cu, fn_8019AAB0__11SndObjctPlyFUli_8019A970);
}
/* startFootSoundPlayer(id): with |mSpeedF| */
static void pb_startFootSoundPlayer(GM_CTX, gptr self) {
    I2_FN(0x80058110u);
    NV_R(31, R(4)); R(4) = 1; NV_R(30, self);
    BL(0x80058134u, hle_fn_80057E00);
    if (CMPS(R(3), 0) != 0) return;
    LDF(0, self + PL_SPEED_F);
    R(4) = R(31); R(3) = self + PL_SND_OBJ; R(5) = 0;
    ctx->f[0].u &= ~0x8000000000000000ull; ctx->f[1].d = frsp(F(0));
    BL(0x80058158u, startFootSound__11SndObjctPlyFUlfUl_8019A6D0);
}
/* NMSndObject<4>::SoundHandlePrm: the constructor / destructor __construct_array runs for the
   sound object's six handles (a SoundHandle and a float 1.0f) */
static void pb_soundHandlePrm_ct(GM_CTX, gptr h) {
    LDF(0, F_ONE); R(0) = 0;
    gm_set_u32(h, 0); STF(h + 4, 0);
}
static void pb_soundHandlePrm_dt(GM_CTX, gptr h, uint32_t del) {
    I2_FN(0x80046490u);
    CMPS(h, 0);
    NV_R(31, del); NV_R(30, h);
    if (h) {
        BL(0x800464BCu, DetachSound__Q34nw4r3snd11SoundHandleFv_8027A200);
        if (CMPS(R(31), 0) > 0) { R(3) = R(30); BL(0x800464CCu, __dl__FPv_802B9280); }
    }
    R(3) = R(30);
}

/* ================================================================== hle entry points
   On: the 150 the A/B inputs reach in 300 s (RT_GM_REACH=1 logs each entry's first call).
   Written but off (no A/B input reaches them within the baseline's 300 s, the coverage build's longer
   title demos do; -DPL_BASE_UNREACHED and their names in hle_funcs.txt switch them on and add them to
   the self-test, where they passed): finalizeState_Slip (fn_80048170), sLib::calcTimer<s8>
   (fn_800483F0), setCcAtSlip (fn_800536A0), isEnablePressLR (fn_800565E0). Verified memory:
   the object (a dAcPy_c is 0x2D08 bytes; the state managers, sound handles, timers and the
   factory: their own words). Calls that play sounds / effects / quakes / rumble or run another
   state's methods change more than that: for those RT_GM_VERIFY's double run checks the registers
   only, and the strict A/B is the test (see the report: which are left out of the live verify). */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
#define PL_SIZE 0x2D08
#define PB_MEM SELF, PL_SIZE
static void pb_reached(const char *name) {
    static int on = -1; if (on < 0) on = getenv("RT_GM_REACH") != NULL;
    if (on) rt_log("gm", "reached %s (frame %llu)", name, (unsigned long long)g_frames_presented);
}
#define PB_HLE(name, flags, ...) \
    static void name##_native(ppc_context *ctx, uint8_t *base); \
    GM_HLE(name) { static int seen_; if (!seen_) { seen_ = 1; pb_reached(#name); } \
                   if (gm_verifying()) { const gptr r_[] = { __VA_ARGS__ }; \
                       gm_verify(#name, ctx, base, name##_native, orig_##name, r_, (int)(sizeof r_ / sizeof *r_) / 2, (flags)); } \
                   else name##_native(ctx, base); } \
    static void name##_native(ppc_context *ctx, uint8_t *base)
#define PB_VOID(name, ...) PB_HLE(name, 0, __VA_ARGS__)
#define PB_INT(name, ...)  PB_HLE(name, GMV_RET, __VA_ARGS__)
static void pb_selftest(GM_CTX, gptr self);

/* -- status flags */
PB_VOID(fn_80056C30, PB_MEM)                    { pb_setStatus(GM_PASS, SELF, A(1)); }
PB_VOID(setFlag__10daPlBase_cFi, PB_MEM)        { pb_onOffStatus(GM_PASS, SELF, A(1), 1); }
PB_VOID(clearFlag__10daPlBase_cFi, PB_MEM)      { pb_onOffStatus(GM_PASS, SELF, A(1), 0); }
PB_INT (testFlag__10daPlBase_cFi, PB_MEM)       { pb_isStatus(GM_PASS, SELF, A(1)); }
/* -- the state machine */
PB_INT (fn_80046A50, PB_MEM)                    { pb_create(GM_PASS, SELF); }
PB_INT (fn_80047190, PB_MEM)                    { pb_doDelete(GM_PASS, SELF); }
PB_VOID(fn_80047440, PB_MEM)                    { if (ctx->lr == 0x801439ECu) pb_selftest(GM_PASS, SELF);
                                                  pb_executeState(GM_PASS, SELF); }
PB_VOID(fn_80047470, SELF, 0x40)                { pb_stateMgr_call(GM_PASS, SELF, SM_EXECUTE); }
PB_VOID(fn_800471E0, SELF, 0x40)                { pb_stateMgr_call(GM_PASS, SELF, SM_FINALIZE); }
PB_INT (fn_8004A2B0, SELF, 0x40)                { pb_stateMgr_call(GM_PASS, SELF, SM_GET_STATE_ID); }
PB_VOID(fn_80059190, SELF, 16)                  { pb_fstate_call(GM_PASS, SELF, SID_INITIALIZE); }
PB_VOID(fn_800591B0, SELF, 16)                  { pb_fstate_call(GM_PASS, SELF, SID_EXECUTE); }
PB_VOID(fn_800591D0, SELF, 16)                  { pb_fstate_call(GM_PASS, SELF, SID_FINALIZE); }
PB_INT (fn_80059120, SELF, 16)                  { pb_fstateFct_build(GM_PASS, SELF, A(1)); }
PB_VOID(fn_80059180, A(1), 4)                   { pb_fstateFct_dispose(GM_PASS, A(1)); }
#define PB_NULL_ID(name) PB_INT(name, SELF, 0)  { pb_baseIDNull(GM_PASS); }
PB_NULL_ID(fn_80047270) PB_NULL_ID(fn_80047280) PB_NULL_ID(fn_80047290) PB_NULL_ID(fn_800472A0)
PB_NULL_ID(fn_800472B0) PB_NULL_ID(fn_800472C0) PB_NULL_ID(fn_800472D0) PB_NULL_ID(fn_800472E0)
PB_NULL_ID(fn_800472F0) PB_NULL_ID(fn_80047300) PB_NULL_ID(fn_80047310) PB_NULL_ID(fn_80047320)
PB_NULL_ID(fn_80047330) PB_NULL_ID(fn_80047340) PB_NULL_ID(fn_80047350) PB_NULL_ID(fn_80047360)
PB_NULL_ID(fn_80047370) PB_NULL_ID(fn_80047380)
PB_NULL_ID(fn_8004D6F0) PB_NULL_ID(fn_8004D700) PB_NULL_ID(fn_8004D710) PB_NULL_ID(fn_8004D720)
PB_NULL_ID(fn_8004D730) PB_NULL_ID(fn_8004D740) PB_NULL_ID(fn_8004D750) PB_NULL_ID(fn_8004D760)
PB_NULL_ID(fn_8004D770) PB_NULL_ID(fn_8004D780) PB_NULL_ID(fn_8004D790) PB_NULL_ID(fn_8004D7A0)
PB_NULL_ID(fn_8004D7B0) PB_NULL_ID(fn_8004D7C0) PB_NULL_ID(fn_8004D7D0) PB_NULL_ID(fn_8004D7E0)
PB_NULL_ID(fn_8004D7F0) PB_NULL_ID(fn_8004D800) PB_NULL_ID(fn_8004D810)
/* -- the states' methods: initializeState_None / finalizeState_None, finalizeState_DemoNone,
      initializeState_DemoStartWait / finalizeState_DemoStartWait (empty), checkBgCrossSub (empty) */
PB_VOID(fn_800475B0, SELF, 0)                   { (void)ctx; (void)base; }
PB_VOID(fn_800475C0, SELF, 0)                   { (void)ctx; (void)base; }
PB_VOID(fn_8004E4C0, SELF, 0)                   { (void)ctx; (void)base; }
PB_VOID(fn_8004E700, SELF, 0)                   { (void)ctx; (void)base; }
PB_VOID(fn_8004E7A0, SELF, 0)                   { (void)ctx; (void)base; }
PB_VOID(fn_800544E0, SELF, 0)                   { (void)ctx; (void)base; }
PB_VOID(fn_800477A0, PB_MEM)                    { pb_finalizeState_Walk(GM_PASS); }
PB_VOID(fn_800477B0, PB_MEM)                    { pb_executeState_Walk(GM_PASS, SELF); }
PB_VOID(fn_800479A0, PB_MEM)                    { pb_initializeState_Jump(GM_PASS, SELF); }
PB_VOID(fn_80047D10, PB_MEM)                    { pb_finalizeState_Fall(GM_PASS, SELF); }
PB_VOID(fn_80047D60, PB_MEM)                    { pb_executeState_Fall(GM_PASS, SELF); }
#ifdef PL_BASE_UNREACHED
PB_VOID(fn_80048170, PB_MEM)                    { pb_finalizeState_Slip(GM_PASS, SELF); }
#endif
PB_VOID(fn_80049F50, PB_MEM)                    { pb_finalizeState_PlayerJumpDai(GM_PASS, SELF); }
PB_VOID(fn_8004B090, PB_MEM)                    { pb_finalizeState_WaitJump(GM_PASS, SELF); }
PB_VOID(fn_8004EA20, PB_MEM)                    { pb_endDemoInDokan(GM_PASS, SELF); }
PB_VOID(fn_8004F100, PB_MEM)                    { R(4) = 0; fn_8004EDE0(ctx, base); }    /* initializeState_DemoInDokanU: initDemoInDokanUD(DOKAN_U) */
PB_VOID(fn_8004F110, PB_MEM)                    { hle_fn_8004EA20(ctx, base); }          /* finalizeState_DemoInDokanU: endDemoInDokan */
PB_VOID(fn_8004F120, PB_MEM)                    { R(4) = 0; hle_fn_8004EA80(ctx, base); }    /* executeState_DemoInDokanU: executeDemoInDokan(DOKAN_U) */
PB_VOID(fn_8004FF00, PB_MEM)                    { R(4) = 3; hle_fn_8004FA70(ctx, base); }    /* initializeState_DemoOutDokanR: initDemoOutDokanLR(DOKAN_R) */
PB_VOID(fn_8004FF20, PB_MEM)                    { hle_fn_8004FBB0(ctx, base); }              /* executeState_DemoOutDokanR: executeDemoOutDokanLR */
PB_VOID(fn_80051400, PB_MEM)                    { pb_initializeState_DemoGoal(GM_PASS, SELF); }
PB_INT(fn_8004F240, PB_MEM)                    { pb_demo_dokan_move_y(GM_PASS, SELF); }
PB_VOID(fn_80051AA0, PB_MEM)                    { pb_setDemoGoalMode(GM_PASS, SELF, A(1), A(2)); }
PB_VOID(fn_8004D830, PB_MEM)                    { pb_initialDokanUper(GM_PASS); }
PB_VOID(fn_8004DB00, PB_MEM)                    { pb_setCreateAction(GM_PASS, A(1)); }
/* -- sLib::calcTimer */
#ifdef PL_BASE_UNREACHED
PB_INT (fn_800483F0, A(0), 1)                   { pb_calcTimer_s8(GM_PASS, A(0)); }
#endif
PB_INT (fn_80052ED0, A(0), 4)                   { pb_calcTimer_int(GM_PASS, A(0)); }
/* -- direction / angles */
PB_INT (fn_80047480, SELF, 0)                   { pb_getMukiAngle(GM_PASS, A(1)); }
PB_INT (fn_80047490, PB_MEM)                    { pb_turnAngle(GM_PASS, SELF); }
PB_INT (fn_800474E0, PB_MEM)                    { pb_addCalcAngleY(GM_PASS, SELF); }
PB_INT (fn_80047580, PB_MEM)                    { pb_checkRideActor(GM_PASS, SELF, A(1)); }
PB_VOID(fn_80048BA0, PB_MEM)                    { pb_setTurnEnd(GM_PASS, SELF); }
/* -- crouch / slopes / speed */
PB_INT (fn_80047EE0, PB_MEM)                    { pb_checkStandUpRoofOnLift(GM_PASS, SELF); }
PB_INT (fn_8004B160, PB_MEM)                    { pb_checkSakaReverse(GM_PASS, SELF); }
PB_INT (fn_8004B1A0, PB_MEM)                    { pb_isSaka(GM_PASS, SELF); }
PB_INT (fn_8004B1C0, PB_MEM)                    { pb_isSlipSaka(GM_PASS, SELF); }
PB_INT (fn_8004B290, PB_MEM)                    { pb_checkSlip(GM_PASS, SELF); }
PB_VOID(fn_8004B460, PB_MEM)                    { pb_getSlipMaxSpeedF(GM_PASS, SELF); }
PB_VOID(fn_8004B4C0, PB_MEM)                    { pb_getSakaTable(GM_PASS, SELF, 0x8004B4C0u, 0x8004B4E0u, 0x8004B4ECu, SAKA_MAX_SPEED_RATIO); }
PB_VOID(fn_8004B520, PB_MEM)                    { pb_getSakaTable(GM_PASS, SELF, 0x8004B520u, 0x8004B540u, 0x8004B54Cu, SAKA_STOP_ACCELE); }
PB_VOID(fn_8004B580, PB_MEM)                    { pb_getSakaTable(GM_PASS, SELF, 0x8004B580u, 0x8004B5A0u, 0x8004B5ACu, SAKA_MOVE_ACCELE); }
PB_VOID(fn_8004C450, PB_MEM)                    { pb_powerSet(GM_PASS, SELF); }
PB_VOID(fn_8004C470, PB_MEM)                    { pb_maxFallSpeedSet(GM_PASS, SELF); }
PB_INT (fn_80057650, PB_MEM)                    { pb_getSpeedData(GM_PASS, SELF); }
PB_VOID(modifyPlayerPropertiesWithRollingObject, PB_MEM) { pb_setJumpAddSpeedF(GM_PASS, SELF); }
PB_INT (fn_80057AD0, PB_MEM)                    { pb_checkJumpTrigger(GM_PASS, SELF); }
PB_VOID(fn_800577D0, PB_MEM)                    { pb_setZPositionDirect(GM_PASS, SELF); }
PB_VOID(fn_80057810, PB_MEM)                    { R(4) = STATUS_99; hle_clearFlag__10daPlBase_cFi(ctx, base); }   /* offZPosSetNone */
/* -- hip attack */
PB_VOID(fn_80048E10, PB_MEM)                    { pb_setHipBlockBreak(GM_PASS, SELF); }
PB_VOID(fn_800491F0, PB_MEM)                    { pb_HipAction_Ready(GM_PASS, SELF); }
PB_VOID(fn_80049250, PB_MEM)                    { pb_HipAction_AttackStart(GM_PASS, SELF); }
/* -- demo queries */
PB_INT (fn_8004DDE0, PB_MEM)                    { pb_isDemoAll(GM_PASS, SELF); }
PB_INT (fn_8004DE30, PB_MEM)                    { pb_isDemoMode(GM_PASS, SELF); }
PB_INT (fn_8004E040, SELF, 0)                   { pb_isPlayerGameStop(GM_PASS); }
PB_INT (fn_8004E220, PB_MEM)                    { pb_checkTimeOut(GM_PASS, SELF); }
/* -- collision */
PB_INT (fn_80053490, PB_MEM)                    { pb_getCcLineKind(GM_PASS, SELF); }
PB_VOID(fn_80053600, PB_MEM)                    { pb_clearCcData(GM_PASS, SELF); }
PB_VOID(fn_80053650, PB_MEM)                    { pb_setCcAtBody(GM_PASS, SELF, A(1)); }
#ifdef PL_BASE_UNREACHED
PB_VOID(fn_800536A0, PB_MEM)                    { pb_setCcAtSlip(GM_PASS); }
#endif
PB_VOID(fn_80053700, PB_MEM)                    { pb_setCcAtHipAttack(GM_PASS, SELF); }
PB_INT (fn_800538E0, PB_MEM)                    { pb_isActionRevisionY(GM_PASS, SELF); }
PB_VOID(fn_80053AA0, PB_MEM)                    { pb_clearCcPlayerRev(GM_PASS, SELF); }
/* -- squish */
PB_VOID(fn_80053F90, PB_MEM)                    { pb_setReductionScale(GM_PASS, SELF); }
PB_VOID(fn_80054070, PB_MEM)                    { pb_calcJumpDaiReductionScale(GM_PASS, SELF); }
PB_VOID(fn_800540D0, PB_MEM)                    { pb_setReductionBoyon(GM_PASS, SELF); }
PB_VOID(fn_800541C0, A(0), 12, A(1), PL_SIZE)   { pb_getReductionModelScale(GM_PASS, A(0), A(1)); }
/* -- not hit / presses */
PB_VOID(fn_800541E0, PB_MEM)                    { pb_setNoHitPlayer(GM_PASS, SELF, A(1), A(2)); }
PB_VOID(fn_800541F0, PB_MEM)                    { pb_updateNoHitPlayer(GM_PASS, SELF); }
PB_VOID(fn_80054280, PB_MEM)                    { pb_clearHipAttackDamagePlayer(GM_PASS, SELF); }
PB_VOID(fn_800542D0, PB_MEM)                    { pb_calcNoHitObjBgTimer(GM_PASS, SELF); }
PB_VOID(HurtMarioBecauseOfBeingSquashed, PB_MEM) { pb_setBgPressReq(GM_PASS, SELF, A(1), A(2)); }
#ifdef PL_BASE_UNREACHED
PB_INT (fn_800565E0, PB_MEM)                    { pb_isEnablePressLR(GM_PASS, SELF); }
#endif
PB_VOID(fn_800552D0, PB_MEM)                    { pb_getWaterCheckPosY(GM_PASS, SELF); }
/* -- power-up, counters, getters */
PB_VOID(fn_80056BC0, PB_MEM)                    { pb_setPowerup(GM_PASS, SELF, A(1)); }
PB_INT (fn_80056BD0, PB_MEM)                    { pb_isMameAction(GM_PASS, SELF); }
PB_VOID(fn_8004D5A0, PB_MEM)                    { pb_setSoundPlyMode(GM_PASS, SELF); }
PB_VOID(fn_80057C80, PB_MEM)                    { pb_clearFollowMameKuribo(GM_PASS, SELF); }
PB_INT (fn_80057CC0, SELF, 0)                   { (void)base; R(3) = gm_u32(SELF + PL_FOLLOW_MAME); }      /* getFollowMameKuribo */
PB_INT (fn_80057CD0, PB_MEM)                    { pb_isMaskDraw(GM_PASS, SELF); }
PB_VOID(fn_800581A0, PB_MEM)                    { pb_clearCount(GM_PASS, SELF, PL_TREAD_COUNT); }
PB_INT (fn_800581B0, PB_MEM)                    { pb_calcTreadCount(GM_PASS, SELF, A(1)); }
PB_VOID(fn_800581D0, PB_MEM)                    { pb_clearCount(GM_PASS, SELF, PL_STAR_COUNT); }
PB_VOID(fn_80058250, PB_MEM)                    { pb_clearCount(GM_PASS, SELF, PL_COMBO_COUNT); }
PB_INT (fn_80048B90, SELF, 0)                   { (void)base; R(3) = 0; }                                  /* isCarry */
PB_INT (fn_80053DE0, SELF, 0)                   { (void)base; R(3) = 0; }                                  /* isLiftUp */
PB_INT (fn_80056D40, SELF, 0)                   { (void)base; R(3) = 2; }                                  /* getTallType */
PB_INT (fn_80049040, SELF, 0)                   { (void)base; R(3) = gm_u32(SELF + PL_GRAVITY_DATA); }     /* getGravityData */
PB_INT (fn_80056E30, SELF, 0)                   { (void)base; R(3) = gm_u32(SELF + PL_MDL_MNG); R(3) = gm_u32(R(3) + 4); }   /* getModel */
/* -- effects, quakes, rumble */
PB_INT (fn_8004CD20, PB_MEM)                    { pb_setSandFunsuiLandEffect(GM_PASS, SELF); }
PB_VOID(fn_8004D210, PB_MEM)                    { pb_fadeOutTurnEffect(GM_PASS, SELF); }
PB_VOID(fn_80058280, PB_MEM)                    { pb_startQuakeShock(GM_PASS, SELF, A(1)); }
PB_VOID(fn_800582A0, PB_MEM)                    { pb_startPatternRumble(GM_PASS, SELF); }
/* -- sounds (the thunks: the player sound object's virtual startSound / holdSound go to SndObjctPly's) */
PB_VOID(PlayPlayerSound, PB_MEM)                { pb_sound(GM_PASS, SELF, 0x80057E70u, 0x80057E94u, SO_START_SOUND, 0x80057EB8u); }
PB_VOID(fn_80057F60, PB_MEM)                    { pb_sound(GM_PASS, SELF, 0x80057F60u, 0x80057F84u, SO_HOLD_SOUND, 0x80057FA8u); }
PB_VOID(fn_80058050, PB_MEM)                    { pb_startPlayerVoice(GM_PASS, SELF); }
PB_VOID(fn_80058110, PB_MEM)                    { pb_startFootSoundPlayer(GM_PASS, SELF); }
PB_INT (fn_80057ED0, SELF, 0x100)               { startSound__11SndObjctPlyFUlUl_80199FB0(ctx, base); }
PB_INT (fn_80057F50, SELF, 0x100)               { R(5) = (uint32_t)(int16_t)R(5); startSound__11SndObjctPlyFUlsUl_8019A1F0(ctx, base); }
PB_INT (fn_80057FC0, SELF, 0x100)               { holdSound__11SndObjctPlyFUlUl_8019A0A0(ctx, base); }
PB_INT (fn_80058040, SELF, 0x100)               { R(5) = (uint32_t)(int16_t)R(5); holdSound__11SndObjctPlyFUlsUl_8019A310(ctx, base); }
PB_VOID(fn_80046470, SELF, 8)                   { pb_soundHandlePrm_ct(GM_PASS, SELF); }
PB_INT (fn_80046490, SELF, 8)                   { pb_soundHandlePrm_dt(GM_PASS, SELF, A(1)); }

/* ================================================================== self-test (RT_GM_SELFTEST=pl_base)
   On a live player (dAcPy_c's first call of executeState): every function that only reads / writes
   the object (and calls nothing that plays, draws or changes state) with random flags, background
   cross bits, power-up, direction, speed, angles, timers, counters, squish / collision values, the
   walls' controllers (none, the same, two scratch ones with equal or different owners) and random
   arguments; the float arguments (f1, f2) random too. The object is put back afterwards. */
#define ST_SCR      0x2B00                 /* (scratch inside the object's range) */
#define ST_CTR_A    (ST_SCR + 0x00)        /*   two background controllers (m_e0 at +224) */
#define ST_CTR_B    (ST_SCR + 0x10)
#define ST_TIMER    (ST_SCR + 0x40)        /*   calcTimer<int>'s / <s8>'s counters */
#define ST_TIMER8   (ST_SCR + 0x44)
#define ST_VEC      (ST_SCR + 0x50)        /*   getReductionModelScale's result */
#define ST_HANDLE   (ST_SCR + 0x60)        /*   a SoundHandlePrm */
#define ST_PTR      (ST_SCR + 0x70)        /*   dispose's pointer */
static gptr pb_test_self;
static void pb_randomize2(GM_CTX);                     /* (wave 2's: at the end of the file) */
static int pb_tests2(const gm_test_t **t);
static float pb_rfloat(void) {
    static const float v[] = { 0.0f, 1.0f, -1.0f, 0.5f, -0.5f, 2.0f, -2.0f, 3.5f, -4.0f, 1e-3f, 2.5f, -0.4999f };
    return gm_rand() % 3 ? v[gm_rand() % 12] : (float)((int32_t)(gm_rand() % 20001) - 10000) / 64.0f;
}
static void pb_randomize(GM_CTX, int round) {
    (void)base; (void)round;
    gptr s = pb_test_self;
    for (uint32_t a = 0; a < 28; a += 4) gm_set_u32(s + PL_STATUS + a, gm_rand() & gm_rand());
    gm_set_u32(s + PL_NOW_BG_CROSS1, gm_rand() & gm_rand()); gm_set_u32(s + PL_NOW_BG_CROSS2, gm_rand() & gm_rand());
    gm_set_u32(s + PL_POWERUP, gm_rand() % 7);
    gm_set_u8(s + PL_DIRECTION, (uint8_t)(gm_rand() & 1));
    gm_set_f32(s + PL_SPEED_F, pb_rfloat());
    gm_set_u16(s + PL_ANGLE_X, (uint16_t)gm_rand()); gm_set_u16(s + PL_ANGLE_Y, (uint16_t)gm_rand());
    gm_set_u32(s + PL_SUBSTATE_TIMER, gm_rand() % 3 ? gm_rand() % 3 : gm_rand());
    gm_set_u32(s + PL_JUMP_DAI_TIMER, gm_rand() % 2 ? 0 : gm_rand());
    for (uint32_t a = 0; a < 3; a++) gm_set_u8(s + PL_TREAD_COUNT + a, (uint8_t)(gm_rand() % 3 ? gm_rand() % 8 : gm_rand()));
    gm_set_u32(s + PL_GROUND_TYPE, gm_rand() % 13);
    gm_set_u32(s + PL_NO_HIT_TIMER, gm_rand() % 3); gm_set_u32(s + PL_NO_HIT_OBJ_TIMER, gm_rand() % 3);
    gm_set_u32(s + PL_NO_HIT_PLAYER, gm_rand()); gm_set_u32(s + BC_NO_HIT_ACTOR, gm_rand());
    gm_set_u32(s + PL_NEW_FOLLOW_MAME, gm_rand() % 4); gm_set_u32(s + PL_FOLLOW_MAME, gm_rand() % 4);
    gm_set_u32(s + PL_SQUISH_STATE, gm_rand() % 4); gm_set_u32(s + PL_SQUISH_KEYFRAME, gm_rand() % 5);
    gm_set_f32(s + PL_SQUISH_SCALE, pb_rfloat());
    gm_set_u8(s + PL_AMI_LAYER, (uint8_t)gm_rand());
    gm_set_u8(s + PL_IS_DEMO_MODE, (uint8_t)(gm_rand() % 3 ? gm_rand() & 1 : gm_rand()));
    gm_set_u32(s + PL_BG_PRESS_ACTIVE, gm_rand() & gm_rand());
    gm_set_u32(s + PL_RIDE_ACTOR_ID, gm_rand() % 3 ? gm_u32(s + PL_UNIQUE_ID) : gm_rand());
    gm_set_u8(s + PL_TURN_EFF_FADE, (uint8_t)(gm_rand() % 3));
    for (uint32_t a = 0; a < 16; a += 4) gm_set_f32(s + PL_CC + CC_OFFSET + a, pb_rfloat());
    gm_set_u32(s + PL_CC + CC_VS_KIND, gm_rand());
    for (uint32_t a = 0; a < 16; a += 4) gm_set_f32(s + PL_CC_REV + a, pb_rfloat());
    gm_set_u8(s + BC_PLAYER_FLAGS, (uint8_t)gm_rand());
    gptr ca = s + ST_CTR_A, cb = s + ST_CTR_B;
    gm_set_u32(ca + BG_CTR_E0, gm_rand() % 3); gm_set_u32(cb + BG_CTR_E0, gm_rand() % 3);
    gptr walls[3] = { 0, ca, cb }, wl = walls[gm_rand() % 3];
    gm_set_u32(s + BC_CTR_WALL_L, wl); gm_set_u32(s + BC_CTR_WALL_R, gm_rand() % 3 == 0 ? wl : walls[gm_rand() % 3]);
    gm_set_u32(s + ST_TIMER, gm_rand() % 3 ? gm_rand() % 3 : gm_rand());
    gm_set_u8(s + ST_TIMER8, (uint8_t)(gm_rand() % 3 ? gm_rand() % 3 : gm_rand()));
    gm_set_u32(s + ST_PTR, gm_rand());
    ctx->f[1].d = ctx->ps1[1] = pb_rfloat(); ctx->f[2].d = ctx->ps1[2] = pb_rfloat();
    pb_randomize2(GM_PASS);
}
static uint32_t pb_arg(char k) {
    gptr s = pb_test_self;
    switch (k) {
    case 'F': return gm_rand() % 224;                    /* a status flag */
    case 'O': return s;                                  /* the other player: itself */
    case 'S': return s;
    case 'A': return gm_rand() % 2 ? s : 0;              /* an actor, or none */
    case 'K': return gm_rand() % 8;                      /* a press kind */
    case 'M': return s + PL_STATE_MGR;
    case 'T': return s + ST_TIMER;
    case 'U': return s + ST_TIMER8;
    case 'V': return s + ST_VEC;
    case 'H': return s + ST_HANDLE;
    case 'P': return s + ST_PTR;
    default:  return 0xDEADBEEFu;
    }
}
static const gm_test_t pb_tests[] = {
    GM_TEST(fn_80056C30, 0, "F"), GM_TEST(setFlag__10daPlBase_cFi, 0, "F"), GM_TEST(clearFlag__10daPlBase_cFi, 0, "F"),
    GM_TEST(testFlag__10daPlBase_cFi, GMV_RET, "F"),
    GM_TEST(fn_8004A2B0, GMV_RET, "!M"), GM_TEST(fn_80059180, 0, "!vP"),
    GM_TEST(fn_80047270, GMV_RET, "!"), GM_TEST(fn_80047380, GMV_RET, "!"), GM_TEST(fn_8004D6F0, GMV_RET, "!"), GM_TEST(fn_8004D810, GMV_RET, "!"),
    GM_TEST(fn_800475B0, 0, ""), GM_TEST(fn_800475C0, 0, ""), GM_TEST(fn_8004E4C0, 0, ""), GM_TEST(fn_8004E700, 0, ""),
    GM_TEST(fn_8004E7A0, 0, ""), GM_TEST(fn_800544E0, 0, ""),
    GM_TEST(fn_800477A0, 0, ""), GM_TEST(fn_800477B0, 0, ""), GM_TEST(fn_800479A0, 0, ""), GM_TEST(fn_80047D10, 0, ""),
    GM_TEST(fn_80047D60, 0, ""), GM_TEST(fn_80049F50, 0, ""), GM_TEST(fn_8004B090, 0, ""),
    GM_TEST(fn_8004EA20, 0, ""), GM_TEST(fn_8004F110, 0, ""),
    GM_TEST(fn_8004F240, GMV_RET, ""), GM_TEST(fn_80051AA0, 0, "vv"),
    GM_TEST(fn_80052ED0, GMV_RET, "!T"),
    GM_TEST(fn_80047480, GMV_RET, "v"), GM_TEST(fn_80047490, GMV_RET, ""), GM_TEST(fn_800474E0, GMV_RET, "hh"),
    GM_TEST(fn_80047580, GMV_RET, "O"),
    GM_TEST(fn_80047EE0, GMV_RET, ""), GM_TEST(fn_8004B160, GMV_RET, ""), GM_TEST(fn_8004B1A0, GMV_RET, ""),
    GM_TEST(fn_8004B1C0, GMV_RET, ""), GM_TEST(fn_8004B460, 0, ""), GM_TEST(fn_8004B4C0, 0, "b"),
    GM_TEST(fn_8004B520, 0, "b"), GM_TEST(fn_8004B580, 0, "b"), GM_TEST(fn_8004C450, 0, ""), GM_TEST(fn_8004C470, 0, ""),
    GM_TEST(fn_80057650, GMV_RET, ""), GM_TEST(modifyPlayerPropertiesWithRollingObject, 0, ""),
    GM_TEST(fn_800577D0, 0, ""), GM_TEST(fn_80057810, 0, ""),
    GM_TEST(fn_80048E10, 0, ""), GM_TEST(fn_80049250, 0, ""),
    GM_TEST(fn_8004DDE0, GMV_RET, ""), GM_TEST(fn_8004DE30, GMV_RET, ""), GM_TEST(fn_8004E040, GMV_RET, ""),
    GM_TEST(fn_80053490, GMV_RET, ""), GM_TEST(fn_80053650, 0, "k"), GM_TEST(fn_80053700, 0, ""),
    GM_TEST(fn_800538E0, GMV_RET, ""), GM_TEST(fn_80053AA0, 0, ""),
    GM_TEST(fn_80054070, 0, "nn"), GM_TEST(fn_800540D0, 0, ""), GM_TEST(fn_800541C0, 0, "!VS"),
    GM_TEST(fn_800541E0, 0, "Ov"), GM_TEST(fn_800541F0, 0, ""), GM_TEST(fn_80054280, 0, ""), GM_TEST(fn_800542D0, 0, ""),
    GM_TEST(HurtMarioBecauseOfBeingSquashed, 0, "AK"), GM_TEST(fn_800552D0, 0, ""),
    GM_TEST(fn_80056BC0, 0, "k"), GM_TEST(fn_80056BD0, GMV_RET, ""), GM_TEST(fn_8004D5A0, 0, ""),
    GM_TEST(fn_80057C80, 0, ""), GM_TEST(fn_80057CC0, GMV_RET, ""), GM_TEST(fn_80057CD0, GMV_RET, ""),
    GM_TEST(fn_800581A0, 0, ""), GM_TEST(fn_800581B0, GMV_RET, "n"), GM_TEST(fn_800581D0, 0, ""), GM_TEST(fn_80058250, 0, ""),
    GM_TEST(fn_80048B90, GMV_RET, ""), GM_TEST(fn_80053DE0, GMV_RET, ""), GM_TEST(fn_80056D40, GMV_RET, ""),
    GM_TEST(fn_80049040, GMV_RET, ""), GM_TEST(fn_80056E30, GMV_RET, ""),
    GM_TEST(fn_80046470, 0, "!H"),
#ifdef PL_BASE_UNREACHED
    GM_TEST(fn_80048170, 0, ""), GM_TEST(fn_800483F0, GMV_RET, "!U"), GM_TEST(fn_800536A0, 0, ""), GM_TEST(fn_800565E0, GMV_RET, ""),
#endif
};
static void pb_selftest(GM_CTX, gptr self) {
    if (!gm_selftest_wanted("pl_base")) return;
    pb_test_self = self;
    double f1 = ctx->f[1].d, f2 = ctx->f[2].d, p1 = ctx->ps1[1], p2 = ctx->ps1[2];
    const gptr ranges[] = { self, PL_SIZE };
    static gm_test_t all[256]; const gm_test_t *t2; int n1 = (int)(sizeof pb_tests / sizeof *pb_tests), n2 = pb_tests2(&t2);
    memcpy(all, pb_tests, n1 * sizeof *all); memcpy(all + n1, t2, n2 * sizeof *all);
    const gm_selftest_t t = { "pl_base", all, n1 + n2, 400, ranges, 1, pb_randomize, pb_arg };
    gm_selftest(GM_PASS, &t);
    ctx->f[1].d = f1; ctx->f[2].d = f2; ctx->ps1[1] = p1; ctx->ps1[2] = p2;
}

/* ######################################################################################################
   wave 2: the next 59 methods (97-160 bytes): drawing, the state change, slips, the hip attack, the jump
   pads, gravity / power, landing effects, demos (dokan, goal), collision set-up, background-check
   bookkeeping, side limits, the z position, nut rides and the remaining sound calls. Same conventions as
   above; the names the address map left open are identified from the code against NSMBW-Decomp's source
   (the order and what each reads / calls).
   ###################################################################################################### */
/* ---- more fields (checked against the recompiled code) */
#define PL_SPEED_X          232         /* mVec3_c mSpeed (x, y, z) */
#define PL_SPEED_Y          236
#define PL_SPEED_Z          240
#define PL_POS_X            172
#define PL_MAX_SPEED_F      272         /* float mMaxSpeedF */
#define PL_ACCEL_Y          276         /* float mAccelY */
#define PL_ACCEL_F          284         /* float mAccelF */
#define PL_VISIBLE          292         /* bool mVisible (dBaseActor_c) */
#define PL_KIND             908         /* u8 mKind (2: STAGE_ACTOR_YOSHI) */
#define PL_EXEC_STOP_MASK   910         /* u8 mExecStopMask */
#define PL_SQUISH_NO_MOVE   928         /* s32 mSquishNoMoveTimer */
#define PL_SQUISH_COOLDOWN  932         /* s32 mSquishCooldownTimer */
#define PL_WARP_POS_X       1020        /* mWarpPos (x, y, z) */
#define PL_WARP_POS_Z       1028
#define PL_GOAL_TOUCH_ORDER 1076        /* s32 mGoalTouchOrder */
#define PL_GOAL_JUMP_TARGET 1088        /* mVec3_c mGoalJumpTarget */
#define PL_GOAL_JUMP_FRAMES 1100        /* s32 mGoalJumpFrameCount */
#define PL_AUTO_SLIP_TIMER  1168        /* u8 mAutoSlipTimer */
#define PL_HIP_DROP_EFFECT  1456        /* mEf::levelEffect_c (the hip attack's drop smoke) */
#define PL_JUMP_DAI_OFFSET  1756        /* mVec3_c mJumpDaiOffset */
#define PL_BRAKE_SMOKE_EFF  2376        /* mEf::levelEffect_c mBrakeSmokeEffect */
#define PL_LAYER            4150        /* u8 mLayer */
#define PL_NO_GRAVITY_TIMER 4204        /* s32 mNoGravityTimer */
#define PL_BG_PUSH_FORCE    4292        /* mVec3_c mBgPushForce, float mExtraPushForceX (4304) */
#define PL_EXTRA_PUSH_X     4304
#define PL_OLD_BG_CROSS1    4316        /* u32 mOldBgCross1, mOldBgCross2 */
#define PL_FOOT_HISTORY     4324        /* u32 mBgFootHistory[10] */
#define PL_STAND_ON_UNIT    4364        /* u32 mStandOnUnitType, mPrevStandOnUnitType (4368) */
#define PL_D80              4372        /* float m_d80[2] (the walls' carried movement) */
#define PL_WATER_DEPTH      4416
#define PL_RIDE_NUT_HEIGHT  4448        /* float mRideNutHeight */
#define PL_CC1              4452        /* dCc_c mCc1, mAttCc3 (4944) */
#define PL_ATT_CC3          4944
#define PL_DEMO_STATE_ARG   5204        /* s32 mDemoStateArg */
#define PL_DEMO_SUB_TIMER   5212        /* s32 mDemoSubstateTimer */
#define PL_STATE_ARG        5280        /* void *mStateArg */
#define PL_SUBSTATE         5284        /* s32 mSubstate, mSubstateTimer (5288), mSubstateValue (5292) */
#define PL_SUBSTATE_VALUE   5292
#define BG_CTR_A0           160         /* dBg_ctr_c: m_a0 (x, y), m_ac (x, y), mFlags, the actor (+0) */
#define BG_CTR_AC           168
#define BG_CTR_FLAGS        208
#define VEC_Y               4
/* more status flags */
#define STATUS_DISABLE_STATE_CHANGE 3
#define STATUS_OUT_OF_PLAY  4
#define STATUS_STUNNED      6
#define STATUS_QUAKE        8
#define STATUS_JUMP         10
#define STATUS_SINK_SAND_JUMP 14
#define STATUS_HIP_ATTACK_FALL 28
#define STATUS_HIP_ATTACK_STAND_UP 30
#define STATUS_SWIM         58
#define STATUS_PENGUIN_SLIDE 60
#define STATUS_4E           78
#define STATUS_RIDE_NUT_2   88
#define STATUS_RIDE_NUT     89
#define STATUS_EXTRA_PUSH_FORCE 93
#define STATUS_GOAL_NOT_GOAL_STOP 101   /* (the decomp's STATUS_GOAL_POLE_NOT_GOAL_NO_MOVE) */
#define STATUS_6B           107
#define STATUS_6C           108
#define STATUS_6D           109
#define STATUS_DEMO_GOAL_HIDE 111
#define STATUS_ENDING_DANCE_AUTO 117
#define STATUS_98           152
#define STATUS_A8           168
#define STATUS_AA           170
#define STATUS_IS_PENGUIN   173
#define STATUS_HIP_ATTACK   174
#define STATUS_INVISIBLE    187
/* more virtual methods */
#define VT_IS_ITEM_KINOPIO  224
#define VT_SET_REDUCTION_SC 264         /* setReductionScale */
#define VT_DEMO_GOAL_RUN    652         /* executeDemoGoal_Run */
#define VT_CHECK_CROUCH     912
#define VT_SET_FALL_ACTION  928
#define VT_GET_HEAD_TOP_POS 960         /* getHeadTopPosP */
#define VT_GET_GRAVITY_DATA 964
#define VT_SET_LAND_SE      1044
#define VT_SET_Z_POS_F      1064        /* setZPosition(float) */
#define VT_OFF_ZPOS_NONE    1072        /* offZPosSetNone */
#define VT_PLAY_VOICE       1076
#define VT_TURN_ANGLE       1096
#define VT_MAX_FALL_SET     1100        /* maxFallSpeedSet */
#define SM_CHANGE_STATE     24          /* the state manager's changeState(id) */
#define MDL_SET_ANM         92          /* dPyMdlBase_c::setAnm(anm, rate, blend, frame) */
#define FADER_GET_STATUS    16          /* mFaderBase_c's status (1: HIDDEN) */
#define SO_START_SOUND_S    48          /* the sound object's startSound(id, s, remote), holdSound(id, s, remote) */
#define SO_HOLD_SOUND_S     52
/* more data */
#define F_MINUS_ONE         0x8042B8A8u /* -1.0f (r2 - 30680) */
#define F_0_1               0x8042B8D0u /* 0.1f (r2 - 30640) */
#define F_MINUS_SIX         0x8042B8D4u /* -6.0f (r2 - 30636) */
#define F_0_9               0x8042B91Cu /* 0.9f (r2 - 30564) */
#define F_WIND_SCALE        0x8042B920u /* 1.11111f (r2 - 30560) */
#define F_DOKAN_Z           0x8042B954u /* -1800.0f (r2 - 30508) */
#define F_SIXTEEN           0x8042B87Cu /* 16.0f (r2 - 30724) */
#define F_THIRTY_TWO        0x8042B95Cu /* 32.0f (r2 - 30500) */
#define F_GOAL_JUMP_ACCEL   0x8042B9A4u /* -0.28f (r2 - 30428) */
#define F_EXTRA_PUSH_RATE   0x8042B9C8u /* 0.4f (r2 - 30392) */
#define F_SIDE_LIMIT_R      0x8042B9E0u /* 0.01f (r2 - 30368) */
#define F_SIDE_LIMIT_L      0x8042B9F0u /* -0.01f (r2 - 30352) */
#define ANM_PARAMS          0x80370DA0u /* the player animations' (rate, blend) table */
#define HIP_DROP_SIZE       0x802EEA68u /* the drop smoke's size per tall type */
#define EF_HIP_DROP         0x80307C48u /* the drop smoke's effect name */
#define BRAKE_SMOKE_IDS     0x80308030u /* sc_brakeSmokeEffectID[ground][2] */
#define STATE_SIT_JUMP      0x803542DCu /* daPlBase_c::StateID_SitJump */
#define STATE_FALL2         0x8035431Cu /* daPlBase_c::StateID_Fall */
#define STATE_WAIT_JUMP     0x8035465Cu /* daPlBase_c::StateID_WaitJump */
#define STATE_DEMO_NONE2    0x8035476Cu /* daPlBase_c::StateID_DemoNone */
#define STATE_DEMO_START_WAIT 0x803547ACu /* daPlBase_c::StateID_DemoStartWait */
#define DEMO_MNG_P          0x80429C94u /* daPyDemoMng_c::mspInstance (r13 - 23020; +28: m_1c) */
#define PAUSE_ENABLE_INFO   0x80429CD0u /* daPyMng_c::mPauseEnableInfo (r13 - 22960) */
#define STOP_TIMER_INFO     0x80429CD8u /* daPyMng_c::mStopTimerInfo (r13 - 22952) */
#define EXEC_STOP_REQ       0x80429CF8u /* u8 dActor_c::mExecStopReq (r13 - 22920) */
#define FADER_P             0x8042A440u /* mFader_c::mFader (r13 - 21056) */
#define SIGN64              0x8000000000000000ull

/* mpMdlMng->mpMdl->setAnm(anm, rate, blend, 0.0f): rate / blend from the animation table (r5 holds it at
   the call, as the PowerPC code leaves it) */
static void pb_setAnm(GM_CTX, gptr self, uint32_t anm, uint32_t prm, uint32_t ra) {
    R(5) = ANM_PARAMS; LDF(3, F_ZERO);
    R(4) = gm_u32(self + PL_MDL_MNG); R(3) = gm_u32(R(4) + 4);
    LDF(1, R(5) + prm); LDF(2, R(5) + prm + 4);
    R(4) = anm;
    pb_icall(GM_PASS, R(3), MDL_SET_ANM, ra, 0);
}
#define CHANGE_STATE(ra, id, arg) (R(4) = (id), R(5) = (arg), VCALL((ra), self, VT_CHANGE_STATE))

/* ================================================================== drawing, the state change */
/* preDraw: visible unless STATUS_INVISIBLE, then dBaseActor_c::preDraw */
static void pb_preDraw(GM_CTX, gptr self) {
    I2_FN(0x800471F0u);
    NV_R(31, self);
    R(4) = STATUS_INVISIBLE; BL(0x8004720Cu, hle_testFlag__10daPlBase_cFi);
    R(0) = CMPS(R(3), 0) == 0;
    gm_set_u8(self + PL_VISIBLE, (uint8_t)R(0));
    R(3) = self; BL(0x80047230u, hle_fn_8006C9F0);
    R(3) = CMPS(R(3), 0) != 0;
}
/* changeState(id, arg) (recompiled as dAcPy_vf294): not while state changes are off; the counters
   cleared, the argument kept, mStateMgr.changeState(id) */
static void pb_changeState(GM_CTX, gptr self) {
    I2_FN(0x80047390u);
    NV_R(31, R(5)); NV_R(30, R(4)); R(4) = STATUS_DISABLE_STATE_CHANGE; NV_R(29, self);
    BL(0x800473BCu, hle_testFlag__10daPlBase_cFi);
    if (CMPS(R(3), 0) != 0) return;
    R(3) = self; BL(0x800473CCu, hle_fn_80058250);                         /* (clearComboCount) */
    R(0) = 0;
    gm_set_u32(self + PL_SUBSTATE, 0); gm_set_u32(self + PL_SUBSTATE_TIMER, 0); gm_set_u32(self + PL_SUBSTATE_VALUE, 0);
    R(3) = self; CLEARFLAG(0x800473E8u, STATUS_97);
    R(3) = self; CLEARFLAG(0x800473F4u, STATUS_98);
    gm_set_u32(self + PL_STATE_ARG, R(31));
    R(4) = R(30); pb_icall(GM_PASS, self + PL_STATE_MGR, SM_CHANGE_STATE, 0x80047410u, 0);
}

/* ================================================================== crouch, slips */
/* setCrouchJump: the jump pressed: the sitting jump */
static void pb_setCrouchJump(GM_CTX, gptr self) {
    I2_FN(0x80047B70u);
    NV_R(31, self);
    R(3) = self + PL_KEY; BL(0x80047B8Cu, fn_8005E6F0);                     /* (mKey.triggerJump()) */
    if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
    CHANGE_STATE(0x80047BB4u, STATE_SIT_JUMP, 0);
    R(3) = 1;
}
/* initializeState_Slip */
static void pb_initializeState_Slip(GM_CTX, gptr self) {
    I2_FN(0x800480D0u);
    R(0) = i2_epi_.lr; NV_R(31, 0); NV_R(30, self);
    gm_set_u32(self + PL_SUBSTATE, 0);
    pb_setAnm(GM_PASS, self, 22, 308, 0x80048120u);                         /* (PLAYER_ANIM_SLIP) */
    R(3) = self; BL(0x80048128u, hle_fn_8004B460);                         /* (getSlipMaxSpeedF) */
    R(0) = 8; STF(self + PL_MAX_SPEED_F, 1);
    gm_set_u32(self + PL_SUBSTATE_TIMER, 8); gm_set_u8(self + PL_AUTO_SLIP_TIMER, 0);
    R(3) = self; SETFLAG(0x80048144u, STATUS_SLIP_ACTIVE);
    R(3) = self; SETFLAG(0x80048150u, STATUS_97);
}
/* setSlipAction_ToStoop / setSlipAction_ToEnd: unless the roof holds the player down, the slide ends
   (ToEnd also stops) */
static void pb_setSlipAction_To(GM_CTX, gptr self, int end) {
    I2_FN(end ? 0x800484B0u : 0x80048410u); /* FNADDR 0x80048410 0x800484B0 */
    const uint32_t d = end ? 0xA0u : 0;                                    /* (ToEnd's code is 0xA0 further) */
    NV_R(31, self);
    BL(0x80048428u + d, hle_fn_80047EE0);                                  /* (checkStandUpRoofOnLift) */
    if (CMPS(R(3), 0) != 0) return;
    R(3) = self; CLEARFLAG(0x8004843Cu + d, STATUS_SLIP_ACTIVE);
    R(3) = self; if (TESTFLAG(0x80048448u + d, STATUS_PENGUIN_SLIDE)) { R(3) = self; CLEARFLAG(0x8004845Cu + d, STATUS_PENGUIN_SLIDE); }
    if (!end) {
        R(0) = 1; gm_set_u32(self + PL_SUBSTATE, 1);
        pb_setAnm(GM_PASS, self, 24, 332, 0x80048494u);                     /* (PLAYER_ANIM_SLIP_TO_STOOP) */
    } else {
        R(0) = 2; gm_set_u32(self + PL_SUBSTATE, 2);
        LDF(3, F_ZERO); STF(self + PL_SPEED_F, 3); STF(self + PL_MAX_SPEED_F, 3);
        pb_setAnm(GM_PASS, self, 23, 320, 0x8004853Cu);                     /* (PLAYER_ANIM_SLIPED) */
    }
}
/* checkCrouchSlip: not in water; moving right or not at the left limit; an auto-slip slope or a slip
   slope: setSlipAction */
static void pb_checkCrouchSlip(GM_CTX, gptr self) {
    I2_FN(0x8004B2F0u);
    NV_R(31, self);
    R(4) = gm_u32(self + PL_NOW_BG_CROSS1); R(0) = R(4) & 0x4000u; CR0(ctx, R(0));
    if (R(0)) { R(3) = 0; return; }
    LDF(1, self + PL_SPEED_F); LDF(0, F_ZERO); FCMP(F(1), F(0));
    if (!CR_BIT(ctx, 1)) {
        R(0) = R(4) & 0x80000u; CR0(ctx, R(0));
        if (R(0)) { R(3) = 0; return; }
    }
    R(0) = gm_u32(self + PL_NOW_BG_CROSS2) & 8u; CR0(ctx, R(0));
    if (!R(0)) {
        R(3) = self; BL(0x8004B344u, hle_fn_8004B1C0);                     /* (isSlipSaka) */
        if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
    }
    VCALL(0x8004B360u, self, VT_SET_SLIP_ACTION);
    R(3) = 1;
}

/* ================================================================== hip attack */
/* setHipAttackDropEffect: the drop smoke at joint 1, sized for the tall type */
static void pb_setHipAttackDropEffect(GM_CTX, gptr self) {
    I2_FN(0x80048D70u);
    R(5) = 1; R(4) = R(1) + 20; NV_R(31, self);
    R(6) = gm_u32(self + PL_MDL_MNG); R(3) = gm_u32(R(6) + 4);
    BL(0x80048D98u, hle_getJointPos__12dPyMdlBase_cFP7mVec3_ci);
    R(4) = (uint32_t)-1; VCALL(0x80048DB0u, self, VT_GET_TALL_TYPE);
    R(0) = rotl32(R(3), 2) & 0x3FCu; R(4) = self + PL_HIP_DROP_EFFECT; R(6) = HIP_DROP_SIZE; R(5) = EF_HIP_DROP;
    LDF(0, R(6) + R(0)); R(7) = R(1) + 20;
    STF(R(1) + 8, 0); R(9) = R(1) + 8; R(6) = 0; R(8) = 0; STF(R(1) + 12, 0); STF(R(1) + 16, 0);
    R(3) = (uint32_t)(int8_t)gm_u8(self + PL_PLAYER_NO);
    BL(0x80048DF4u, hle_createPlayerEffect__3dEfFiPQ23mEf13levelEffect_cPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c);
}
/* setHipAttack_Ready */
static void pb_setHipAttack_Ready(GM_CTX, gptr self) {
    I2_FN(0x80048E40u);
    R(0) = 0; NV_R(31, self);
    gm_set_u32(self + PL_SUBSTATE, 0);
    pb_setAnm(GM_PASS, self, 16, 236, 0x80048E8Cu);                         /* (PLAYER_ANIM_HIPSR) */
    LDF(0, F_ONE); STF(self + PL_SPEED_Y, 0);
}
/* setHipAttack_AttackStart */
static void pb_setHipAttack_AttackStart(GM_CTX, gptr self) {
    I2_FN(0x80048F30u);
    R(0) = 1; NV_R(31, self);
    gm_set_u32(self + PL_SUBSTATE, 1);
    pb_setAnm(GM_PASS, self, 17, 248, 0x80048F7Cu);                         /* (PLAYER_ANIM_HIPAT) */
    LDF(0, F_ZERO); R(0) = 5;
    gm_set_u32(self + PL_SUBSTATE_TIMER, 5); STF(self + PL_SPEED_Y, 0);
}
/* setHipAttack_AttackFall */
static void pb_setHipAttack_AttackFall(GM_CTX, gptr self) {
    I2_FN(0x80048FA0u);
    LDF(1, F_0_1); R(0) = 2; LDF(0, F_ZERO); NV_R(31, self);
    gm_set_u32(self + PL_SUBSTATE, 2); STF(self + PL_ACCEL_F, 1); STF(self + PL_MAX_SPEED_F, 0);
    VCALL(0x80048FDCu, self, VT_GET_GRAVITY_DATA);
    R(0) = gm_u32(self + PL_STATE_ARG); LDF(1, R(3)); LDF(0, F_MINUS_SIX);
    int kinopio = CMPS(R(0), 1) == 0;
    STF(self + PL_ACCEL_Y, 1); STF(self + PL_MAX_FALL_SPEED, 0);
    if (kinopio) LDF(0, F_MINUS_TWO);
    STF(self + PL_SPEED_Y, 0);
    R(3) = self; SETFLAG(0x80049014u, STATUS_HIP_ATTACK_FALL);
    R(3) = self; BL(0x8004901Cu, hle_fn_80048E10);                         /* (setHipBlockBreak) */
    R(0) = 5; gm_set_u32(self + PL_SUBSTATE_TIMER, 5);
}
/* setHipAttack_StandNormalEnd */
static void pb_setHipAttack_StandNormalEnd(GM_CTX, gptr self) {
    I2_FN(0x80049110u);
    R(0) = 5; NV_R(31, self);
    gm_set_u32(self + PL_SUBSTATE, 5);
    pb_setAnm(GM_PASS, self, 23, 320, 0x8004915Cu);                         /* (PLAYER_ANIM_SLIPED) */
    R(3) = self; CLEARFLAG(0x80049168u, STATUS_HIP_ATTACK_STAND_UP);
}
/* HipAction_Ground: neither down held nor on the ground: fall; else stand up */
static void pb_HipAction_Ground(GM_CTX, gptr self) {
    I2_FN(0x800494D0u);
    NV_R(31, self);
    R(3) = self + PL_KEY; BL(0x800494ECu, fn_8005E500);                     /* (mKey.buttonDown()) */
    if (CMPS(R(3), 0) == 0) {
        R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1u; CR0(ctx, R(0));
        if (!R(0)) { CHANGE_STATE(0x80049520u, STATE_FALL2, 0); return; }
    }
    R(3) = self; BL(0x8004952Cu, hle_fn_80049050);                              /* (setHipAttack_StandNormal) */
}
/* HipAction_StandNormalEnd: unless crouching: the animation done: walk, else turn */
static void pb_HipAction_StandNormalEnd(GM_CTX, gptr self) {
    I2_FN(0x800496D0u);
    NV_R(31, self);
    VCALL(0x800496F4u, self, VT_CHECK_CROUCH);
    if (CMPS(R(3), 0) != 0) return;
    R(3) = gm_u32(self + PL_MDL_MNG); R(3) = gm_u32(R(3) + 4); R(3) += 40;
    BL(0x8004970Cu, hle_isAnimationDone__Q23m3d6fanm_cFv);
    if (CMPS(R(3), 0) != 0) CHANGE_STATE(0x80049734u, STATE_WALK, 1);
    else VCALL(0x8004974Cu, self, VT_TURN_ANGLE);
}
/* initializeState_HipAttack */
static void pb_initializeState_HipAttack(GM_CTX, gptr self) {
    I2_FN(0x800497E0u);
    NV_R(31, self);
    R(4) = gm_u8(self + PL_DIRECTION); VCALL(0x80049808u, self, VT_GET_MUKI_ANGLE);
    R(0) = gm_u32(self + PL_STATE_ARG); LDF(0, F_ZERO);
    int c = CMPS(R(0), 0);
    gm_set_u16(self + PL_ANGLE_Y, (uint16_t)R(3));
    STF(self + PL_SPEED_F, 0); STF(self + PL_MAX_SPEED_F, 0); STF(self + PL_ACCEL_Y, 0);
    if (c == 0) { R(3) = self; BL(0x8004983Cu, hle_fn_80048E40); }        /* (setHipAttack_Ready) */
    else if (CMPS(R(0), 1) == 0) { R(3) = self; BL(0x80049848u, fn_80048EB0); }   /* (setHipAttack_KinopioStart) */
    R(3) = self; SETFLAG(0x80049854u, STATUS_A8);
    R(3) = self; SETFLAG(0x80049860u, STATUS_AA);
    R(3) = self; SETFLAG(0x8004986Cu, STATUS_HIP_ATTACK);
}

/* ================================================================== jump pads, waiting jump */
/* setPlayerJumoDaiPos: on the player below: its x / z plus the offset, its head top - 4 */
static void pb_setPlayerJumoDaiPos(GM_CTX, gptr self) {
    I2_FN(0x80049D70u);
    NV_R(30, self);
    R(3) = gm_u32(self + PL_RIDE_ACTOR_ID); BL(0x80049D98u, hle_search__7fBase_cFUi);
    int none = CMPS(R(3), 0) == 0;
    NV_R(31, R(3));
    if (none) return;
    LDF(1, self + PL_JUMP_DAI_OFFSET + 8); LDF(0, R(31) + PL_POS_Z);
    FS(31, F(1) + F(0));
    VCALL(0x80049DC0u, R(31), VT_GET_HEAD_TOP_POS);
    LDF(3, R(3) + VEC_Y); LDF(2, F_FOUR); LDF(0, R(31) + PL_POS_X); LDF(1, self + PL_JUMP_DAI_OFFSET);
    FS(2, F(3) - F(2));
    STF(self + PL_POS_Z, 31);
    FS(0, F(1) + F(0));
    STF(self + PL_POS_Y, 2); STF(self + PL_POS_X, 0);
}
/* executeState_WaitJump */
static void pb_executeState_WaitJump(GM_CTX, gptr self) {
    I2_FN(0x8004B0D0u);
    NV_R(31, self);
    BL(0x8004B0E8u, hle_fn_8004C480);                                      /* (gravitySet) */
    VCALL(0x8004B0FCu, self, VT_MAX_FALL_SET);
    R(3) = self; BL(0x8004B104u, hle_fn_8004B730);                              /* (moveSpeedSet) */
    R(3) = self; BL(0x8004B10Cu, hle_fn_8004C310);                              /* (airPowerSet) */
    LDF(1, self + PL_SPEED_Y); LDF(0, F_ZERO); FCMP(F(1), F(0));
    CR_SETBIT(ctx, 2, CR_BIT(ctx, 0) | CR_BIT(ctx, 2));
    if (CR_BIT(ctx, 2)) CHANGE_STATE(0x8004B140u, STATE_FALL2, 0);
}
/* setWaitJump(speed): not in a demo or out of play: the small hop */
static void pb_setWaitJump(GM_CTX, gptr self) {
    I2_FN(0x80057B90u);
    ctx->f[31].u = ctx->f[1].u; NV_R(31, self);
    BL(0x80057BB4u, hle_fn_8004DD00);                                      /* (isDemo) */
    if (CMPS(R(3), 0) != 0) { R(3) = 0; return; }
    R(3) = self; if (TESTFLAG(0x80057BC8u, STATUS_OUT_OF_PLAY)) { R(3) = 0; return; }
    LDF(0, F_ZERO); STF(self + PL_SPEED_F, 0); STF(self + PL_SPEED_Y, 31);
    CHANGE_STATE(0x80057C04u, STATE_WAIT_JUMP, 0);
    R(3) = 1;
}

/* ================================================================== power, gravity, wind */
/* grandPowerSet: in sinking sand the speed data's slow acceleration, else slipPowerSet(sliding) */
static void pb_grandPowerSet(GM_CTX, gptr self) {
    I2_FN(0x8004BA50u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x18000000u; CR0(ctx, R(0));
    if (R(0)) {
        BL(0x8004BA74u, hle_fn_80057650);                                  /* (getSpeedData) */
        LDF(0, R(3) + 28); STF(self + PL_ACCEL_F, 0);
        return;
    }
    R(4) = STATUS_SLIP_ACTIVE; BL(0x8004BA88u, hle_testFlag__10daPlBase_cFi);
    if (CMPS(R(3), 0) != 0) { R(3) = self; R(4) = 1; BL(0x8004BA9Cu, hle_fn_8004BAC0); }
    else { R(3) = self; R(4) = 0; BL(0x8004BAACu, hle_fn_8004BAC0); }
}
/* getPowerChangeType(any): 0 for the penguin (unless asked for any), ice 1, sand / sinking sand 2 */
static void pb_getPowerChangeType(GM_CTX, gptr self) {
    I2_FN(0x8004BF00u);
    int c = CMPS(R(4), 0); NV_R(31, self);
    if (c == 0) {
        R(4) = STATUS_IS_PENGUIN; BL(0x8004BF24u, hle_testFlag__10daPlBase_cFi);
        if (CMPS(R(3), 0) != 0) { R(3) = 0; return; }
    }
    R(3) = gm_u32(self + PL_NOW_BG_CROSS1);
    R(0) = R(3) & 0x800000u; CR0(ctx, R(0)); if (R(0)) { R(3) = 1; return; }
    R(0) = R(3) & 0x1000000u; CR0(ctx, R(0)); if (R(0)) { R(3) = 2; return; }
    R(0) = R(3) & 0x400000u; CR0(ctx, R(0)); if (R(0)) { R(3) = 2; return; }
    R(3) = 0;
}
/* gravitySet: on the ground the gravity data's first value, in the air setJumpGravity */
static void pb_gravitySet(GM_CTX, gptr self) {
    I2_FN(0x8004C480u);
    R(4) = STATUS_98; NV_R(31, self);
    BL(0x8004C49Cu, hle_testFlag__10daPlBase_cFi);
    if (CMPS(R(3), 0) != 0) return;
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1u; CR0(ctx, R(0));
    if (!R(0)) { R(3) = self; BL(0x8004C4D8u, hle_fn_8004C4F0); return; }
    VCALL(0x8004C4C4u, self, VT_GET_GRAVITY_DATA);
    LDF(0, R(3)); STF(self + PL_ACCEL_Y, 0);
}
/* setJumpGravity */
static void pb_setJumpGravity(GM_CTX, gptr self) {
    I2_FN(0x8004C4F0u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NO_GRAVITY_TIMER);
    if (CMPS(R(0), 0) != 0) { LDF(0, F_ZERO); STF(self + PL_ACCEL_Y, 0); return; }
    R(3) = self + PL_KEY; BL(0x8004C524u, fn_8005E740);                     /* (mKey.buttonJump()) */
    if (CMPS(R(3), 0) != 0) { R(3) = self; BL(0x8004C534u, hle_fn_8004C560); }    /* (setButtonJumpGravity) */
    else { R(3) = self; BL(0x8004C540u, hle_fn_8004C620); }                   /* (setNormalJumpGravity) */
}
/* fn_8004c700(v) (the decomp's name; calcWindSpeed's scaling of the wind): |v| past two 0.1 dead zones,
   the sign back, * 1.11111 */
static void pb_windScale(GM_CTX) {
    LDF(0, F_ZERO); R(0) = 0; FCMP(F(1), F(0));
    if (CR_BIT(ctx, 0)) { ctx->f[1].u ^= SIGN64; R(0) = 1; }
    LDF(0, F_0_1); FCMP(F(1), F(0));
    if (CR_BIT(ctx, 0)) LDF(1, F_ZERO);
    else { FS(1, F(1) - F(0)); LDF(0, F_0_9); FS(1, F(1) / F(0)); }
    LDF(2, F_0_1); FCMP(F(1), F(2));
    if (CR_BIT(ctx, 0)) LDF(1, F_ZERO);
    else { LDF(0, F_ONE); FS(1, F(1) - F(2)); FS(0, F(0) - F(2)); FS(1, F(1) / F(0)); }
    if (CMPU(R(0), 1) == 0) ctx->f[1].u ^= SIGN64;
    LDF(0, F_WIND_SCALE); FS(1, F(1) * F(0));
}

/* ================================================================== landing / jump / brake effects */
/* setStartJumpEffect(light): on the ground: in sinking sand its jump effect, else the fountain's or (1)
   the light landing smoke */
static void pb_setStartJumpEffect(GM_CTX, gptr self) {
    I2_FN(0x8004CD80u);
    NV_R(31, R(4)); NV_R(30, self);
    R(5) = gm_u32(self + PL_NOW_BG_CROSS1); R(0) = R(5) & 1u; CR0(ctx, R(0));
    if (!R(0)) return;
    R(0) = R(5) & 0x18000000u; CR0(ctx, R(0));
    if (R(0)) {
        BL(0x8004CDB4u, fn_8004D510);                                      /* (setSandJumpEffect) */
        R(3) = self; SETFLAG(0x8004CDC0u, STATUS_SINK_SAND_JUMP);
        return;
    }
    BL(0x8004CDC8u, hle_fn_8004CD20);                                      /* (setSandFunsuiLandEffect) */
    if (CMPS(R(3), 0) != 0) return;
    if (CMPS(R(31), 1) != 0) return;
    R(3) = self; BL(0x8004CDE0u, hle_fn_8004CC10);                              /* (setLandSmokeEffectLight) */
}
/* setLandJumpEffect(light): the landing sound, then the fountain's or (1) the light smoke */
static void pb_setLandJumpEffect(GM_CTX, gptr self) {
    I2_FN(0x8004CE00u);
    NV_R(31, R(4)); NV_R(30, self);
    VCALL(0x8004CE2Cu, self, VT_SET_LAND_SE);
    R(3) = self; BL(0x8004CE34u, hle_fn_8004CD20);
    if (CMPS(R(3), 0) != 0) return;
    if (CMPS(R(31), 1) != 0) return;
    R(3) = self; BL(0x8004CE4Cu, hle_fn_8004CC10);
}
/* setBrakeSmokeEffect(offset): on water the slip-on-water effect, else the ground's brake smoke (small
   when mini) - both tail calls */
static void pb_setBrakeSmokeEffect(GM_CTX, gptr self) {
    R(5) = gm_u32(self + PL_GROUND_TYPE); R(8) = self;
    if (CMPS(R(5), 5) == 0) { R(4) = self + PL_BRAKE_SMOKE_EFF; hle_fn_8004CE70(ctx, base); return; }   /* (setSlipOnWaterEffect) */
    R(0) = gm_u32(self + PL_POWERUP); R(7) = 0;
    if (CMPS(R(0), 3) != 0) R(7) = 1;
    R(0) = rotl32(R(5), 3) & 0xFFFFFFF8u; R(6) = BRAKE_SMOKE_IDS;
    R(3) = gm_u8(self + PL_PLAYER_NO); R(5) = X4(R(7)); R(7) = R(4);
    R(0) = R(6) + R(0); R(4) = R(8) + PL_BRAKE_SMOKE_EFF;
    R(5) = gm_u32(R(5) + R(0)); R(3) = (uint32_t)(int8_t)R(3);
    R(6) = 0; R(8) = 0; R(9) = 0;
    hle_createPlayerEffect_change__3dEfFiPQ23mEf13levelEffect_cPCcUlPC7mVec3_cPC7mAng3_cPC7mVec3_c(ctx, base);
}

/* ================================================================== demos */
/* initialNormal: walk, wait for the start, falling, the background checked */
static void pb_initialNormal(GM_CTX, gptr self) {
    I2_FN(0x8004DA90u);
    NV_R(31, self);
    CHANGE_STATE(0x8004DAC0u, STATE_WALK, 0);
    R(4) = STATE_DEMO_START_WAIT; R(3) = self; R(5) = 0; BL(0x8004DAD4u, hle_fn_8004E290);   /* (changeDemoState) */
    LDF(0, F_MINUS_ONE); R(3) = self; STF(self + PL_SPEED_Y, 0);
    R(4) = 0; BL(0x8004DAE8u, hle_fn_800543E0);                                /* (bgCheck(0)) */
}
/* isDemo (isDemoType 1, 2, 3) / isControlDemoAll (4, 5, 6) */
static void pb_isDemoTypes(GM_CTX, gptr self, uint32_t t) {
    const uint32_t d = t == 4 ? 0x70u : 0;                                  /* (isControlDemoAll is 0x70 further) */
    I2_FN(0x8004DD00u + d); /* FNADDR 0x8004DD00 0x8004DD70 */
    R(4) = t; NV_R(31, self);
    BL(0x8004DD1Cu + d, hle_fn_8004DB40);
    if (CMPS(R(3), 0) == 0) {
        R(3) = self; R(4) = t + 1; BL(0x8004DD30u + d, hle_fn_8004DB40);
        if (CMPS(R(3), 0) == 0) {
            R(3) = self; R(4) = t + 2; BL(0x8004DD44u + d, hle_fn_8004DB40);
            if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
        }
    }
    R(3) = 1;
}
/* onDemo / offDemo: the player (not an item Toad) can't pause and stops the timer, or back */
static void pb_onOffDemo(GM_CTX, gptr self, int on) {
    const uint32_t d = on ? 0 : 0x90u;                                      /* (offDemo is 0x90 further) */
    I2_FN(0x8004DE50u + d); /* FNADDR 0x8004DE50 0x8004DEE0 */
    NV_R(31, self);
    R(0) = gm_u8(self + PL_PLAYER_NO); R(3) = (uint32_t)(int8_t)R(0);
    if (CMPS(R(3), -1) == 0) return;
    BL(0x8004DE78u + d, hle_getPlayer__9daPyMng_cFi);
    if (CMPS(R(3), 0) != 0) {
        VCALL(0x8004DE90u + d, R(3), VT_IS_ITEM_KINOPIO);
        if (CMPS(R(3), 0) == 0) {
            R(0) = gm_u8(self + PL_PLAYER_NO); R(4) = 1; R(5) = gm_u32(PAUSE_ENABLE_INFO);
            R(3) = (uint32_t)(int8_t)R(0); R(0) = gm_u32(STOP_TIMER_INFO);
            R(4) = i2_bit(R(3));
            if (on) { R(3) = R(5) & ~R(4); gm_set_u32(PAUSE_ENABLE_INFO, R(3)); R(0) = R(0) | R(4); }
            else    { R(3) = R(5) | R(4);  gm_set_u32(PAUSE_ENABLE_INFO, R(3)); R(0) = R(0) & ~R(4); }
            gm_set_u32(STOP_TIMER_INFO, R(0));
        }
    }
    R(0) = (uint32_t)on; gm_set_u8(self + PL_IS_DEMO_MODE, (uint8_t)on);
}
/* playOther: the actors stopped for the demo run again (the player and its Yoshi; a Yoshi itself) */
static void pb_playOther(GM_CTX, gptr self) {
    I2_FN(0x8004E100u);
    NV_R(31, self);
    R(0) = gm_u8(EXEC_STOP_REQ) & 0xF0u; gm_set_u8(EXEC_STOP_REQ, (uint8_t)R(0));
    R(0) = (uint32_t)(int8_t)gm_u8(self + PL_PLAYER_NO);
    if (CMPS(R(0), -1) != 0) {
        R(3) = R(0); BL(0x8004E138u, hle_getPlayer__9daPyMng_cFi);
        if (CMPS(R(3), 0) != 0) { R(0) = gm_u8(R(3) + PL_EXEC_STOP_MASK) | 2u; gm_set_u8(R(3) + PL_EXEC_STOP_MASK, (uint8_t)R(0)); }
        R(3) = (uint32_t)(int8_t)gm_u8(self + PL_PLAYER_NO);
        BL(0x8004E158u, getYoshi__9daPyMng_cFi_8005FA60);
        if (CMPS(R(3), 0) != 0) { R(0) = gm_u8(R(3) + PL_EXEC_STOP_MASK) | 2u; gm_set_u8(R(3) + PL_EXEC_STOP_MASK, (uint8_t)R(0)); }
        return;
    }
    R(0) = gm_u8(self + PL_KIND);
    if (CMPU(R(0), 2) == 0) { R(0) = gm_u8(self + PL_EXEC_STOP_MASK) | 4u; gm_set_u8(self + PL_EXEC_STOP_MASK, (uint8_t)R(0)); }
}
/* changeNormalAction: the background checked, walk, no demo */
static void pb_changeNormalAction(GM_CTX, gptr self) {
    I2_FN(0x8004E1A0u);
    R(4) = 0; NV_R(31, self);
    BL(0x8004E1BCu, hle_fn_800543E0);                                          /* (bgCheck(0)) */
    VCALL(0x8004E1D0u, self, VT_OFF_ZPOS_NONE);
    CHANGE_STATE(0x8004E1F0u, STATE_WALK, 1);
    R(4) = STATE_DEMO_NONE2; R(3) = self; R(5) = 0; BL(0x8004E204u, hle_fn_8004E290);
}
/* initializeState_DemoNone */
static void pb_initializeState_DemoNone(GM_CTX, gptr self) {
    I2_FN(0x8004E450u);
    R(0) = 15; NV_R(31, self);
    gm_set_u32(self + PL_DEMO_SUB_TIMER, 15);
    R(0) = gm_u8(self + PL_PLAYER_NO); R(3) = gm_u32(DEMO_MNG_P); R(4) = (uint32_t)(int8_t)R(0);
    BL(0x8004E47Cu, clearDemoNo__13daPyDemoMng_cFSc_8005D100);
    R(3) = self; BL(0x8004E484u, hle_fn_8004DEE0);                         /* (offDemo) */
    R(0) = gm_u32(self + PL_DEMO_STATE_ARG);
    if (CMPS(R(0), 1) != 0) { R(3) = self; BL(0x8004E498u, hle_fn_8004E100); }   /* (playOther) */
    R(3) = self; CLEARFLAG(0x8004E4A4u, STATUS_INVISIBLE);
}
/* executeState_DemoStartWait: on the title at once, else once the fade is out: no demo */
static void pb_executeState_DemoStartWait(GM_CTX, gptr self) {
    I2_FN(0x8004E710u);
    NV_R(31, self);
    R(0) = gm_u32(GAME_MODE);
    if (CMPS(R(0), 2) == 0) { R(4) = STATE_DEMO_NONE2; R(5) = 0; BL(0x8004E740u, hle_fn_8004E290); return; }
    R(3) = gm_u32(FADER_P); pb_icall(GM_PASS, R(3), FADER_GET_STATUS, 0x8004E758u, 0);
    R(0) = R(3) - 1; R(0) = cntlzw(R(0)); R(0) = rotl32(R(0), 27) & 0x7FFFFFFu; CR0(ctx, R(0));
    if (!R(0)) return;
    R(3) = self; R(4) = 0; BL(0x8004E774u, hle_fn_800543E0);
    R(4) = STATE_DEMO_NONE2; R(3) = self; R(5) = 0; BL(0x8004E788u, hle_fn_8004E290);
}
/* initDemoInDokan */
static void pb_initDemoInDokan(GM_CTX, gptr self) {
    I2_FN(0x8004E980u);
    R(4) = STATUS_5E; NV_R(31, self);
    BL(0x8004E99Cu, hle_setFlag__10daPlBase_cFi);
    LDF(0, F_ZERO); R(3) = self; STF(self + PL_SPEED_F, 0); LDF(1, F_DOKAN_Z); STF(self + PL_SPEED_Y, 0);
    VCALL(0x8004E9C0u, self, VT_SET_Z_POS_F);
    R(0) = gm_u32(self + PL_DEMO_STATE_ARG);
    if (CMPS(R(0), 1) == 0) { R(0) = 0; gm_set_u32(self + PL_DAMAGE_INVULN, 0); }
    else {
        R(0) = 35; gm_set_u32(self + PL_DAMAGE_INVULN, 35);
        R(0) = gm_u8(self + PL_PLAYER_NO); R(3) = gm_u32(DEMO_MNG_P); R(4) = (uint32_t)(int8_t)R(0);
        BL(0x8004E9F0u, checkDemoNo__13daPyDemoMng_cFSc_8005D090);
        if (CMPS(R(3), 0) != 0) { R(3) = self; BL(0x8004EA00u, hle_continueFromMpPauseFix1); }   /* (stopOther) */
    }
    R(0) = 0; gm_set_u32(self + PL_DEMO_SUBSTATE, 0);
}
/* demo_dokan_move_x(speed, near): mPos.x chases mWarpPos.x; within near of it */
static void pb_demo_dokan_move_x(GM_CTX, gptr self) {
    I2_FN(0x8004F1C0u);
    ctx->f[0].u = ctx->f[1].u; ctx->f[31].u = ctx->f[2].u; ctx->f[2].u = ctx->f[0].u; NV_R(31, self);
    LDF(1, self + PL_WARP_POS_X); R(3) = self + PL_POS_X;
    BL(0x8004F1F4u, fn_8015F470);                                          /* (sLib::chase) */
    LDF(1, self + PL_POS_X); LDF(0, self + PL_WARP_POS_X);
    FS(0, F(1) - F(0));
    ctx->f[0].u &= ~SIGN64; ctx->f[0].d = frsp(F(0));
    FCMP(F(0), F(31)); CR_SETBIT(ctx, 2, CR_BIT(ctx, 0) | CR_BIT(ctx, 2));
    R(3) = CR_BIT(ctx, 2);
}
/* isEnableDokanInStatus: no demo, not out of play / stunned / quaking, not STATUS_53 */
static void pb_isEnableDokanInStatus(GM_CTX, gptr self) {
    I2_FN(0x8004F260u);
    NV_R(31, self);
    BL(0x8004F278u, hle_fn_8004DD00);
    if (CMPS(R(3), 0) != 0) { R(3) = 0; return; }
    R(3) = self; if (TESTFLAG(0x8004F294u, STATUS_OUT_OF_PLAY)) { R(3) = 0; return; }
    R(3) = self; if (TESTFLAG(0x8004F2A8u, STATUS_STUNNED)) { R(3) = 0; return; }
    R(3) = self; if (TESTFLAG(0x8004F2BCu, STATUS_QUAKE)) { R(3) = 0; return; }
    R(3) = self; R(3) = !TESTFLAG(0x8004F2D0u, STATUS_53);
}
/* initDemoOutDokan: stopped, behind, the pipe sound (the water one in shallow water) */
static void pb_initDemoOutDokan(GM_CTX, gptr self) {
    I2_FN(0x8004F670u);
    LDF(0, F_ZERO); R(0) = 0; LDF(1, F_DOKAN_Z); NV_R(31, self);
    STF(self + PL_SPEED_F, 0); STF(self + PL_MAX_SPEED_F, 0);
    STF(self + PL_SPEED_X, 0); STF(self + PL_SPEED_Y, 0); STF(self + PL_SPEED_Z, 0);
    gm_set_u16(self + PL_ANGLE_X, 0);
    VCALL(0x8004F6B8u, self, VT_SET_Z_POS_F);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 0x4000u; CR0(ctx, R(0));
    R(3) = self; R(5) = 0;
    if (R(0)) { R(4) = 321; BL(0x8004F6D4u, hle_PlayPlayerSound); }        /* (SE_PLY_WATER_DOKAN_IN_OUT) */
    else      { R(4) = 196; BL(0x8004F6E8u, hle_PlayPlayerSound); }        /* (SE_PLY_DOKAN_IN_OUT) */
}
/* setHideNotGoalPlayer: unless it may not move: stopped, hidden, falling */
static void pb_setHideNotGoalPlayer(GM_CTX, gptr self) {
    I2_FN(0x80051080u);
    R(4) = STATUS_GOAL_NOT_GOAL_STOP; NV_R(31, self);
    BL(0x8005109Cu, hle_testFlag__10daPlBase_cFi);
    if (CMPS(R(3), 0) != 0) { R(3) = 0; return; }
    LDF(0, F_ZERO); R(3) = self; STF(self + PL_SPEED_F, 0); R(4) = STATUS_DEMO_GOAL_HIDE; STF(self + PL_SPEED_Y, 0);
    BL(0x800510BCu, hle_setFlag__10daPlBase_cFi);
    VCALL(0x800510D0u, self, VT_SET_FALL_ACTION);
    R(3) = 1;
}
/* getDemoGoalLandPos: mWarpPos.z + players * 16, less 32 per earlier touch when more than one (the
   int -> float conversions through the frame) */
static void pb_getDemoGoalLandPos(GM_CTX, gptr self) {
    GM_FRAME(16);
    R(4) = 0x43300000u; ctx->f[3].u = ld64(base, D_INT_TO_FLOAT);
    R(5) = gm_u32(DEMO_MNG_P); gm_set_u32(R(1) + 8, R(4));
    R(5) = gm_u32(R(5) + 28); LDF(1, F_SIXTEEN);
    R(0) = R(5) ^ 0x80000000u; gm_set_u32(R(1) + 12, R(0));
    LDF(0, self + PL_WARP_POS_Z);
    CMPS(R(5), 1);
    ctx->f[2].u = ld64(base, R(1) + 8);
    FS(2, F(2) - F(3)); FS(1, F(1) * F(2)); FS(1, F(0) + F(1));
    if (!CR_BIT(ctx, 1)) return;
    R(0) = gm_u32(self + PL_GOAL_TOUCH_ORDER); gm_set_u32(R(1) + 8, R(4));
    R(0) ^= 0x80000000u; LDF(0, F_THIRTY_TWO); gm_set_u32(R(1) + 12, R(0));
    ctx->f[2].u = ld64(base, R(1) + 8);
    FS(2, F(2) - F(3)); FS(0, F(0) * F(2)); FS(1, F(1) - F(0));
}
/* executeDemoGoal_Wait: STATUS_6B: the pose; STATUS_6D: run */
static void pb_executeDemoGoal_Wait(GM_CTX, gptr self) {
    I2_FN(0x800518A0u);
    R(4) = STATUS_6B; NV_R(31, self);
    BL(0x800518BCu, hle_testFlag__10daPlBase_cFi);
    if (CMPS(R(3), 0) != 0) {
        R(3) = self; CLEARFLAG(0x800518D0u, STATUS_6B);
        R(3) = self; SETFLAG(0x800518DCu, STATUS_6C);
        R(3) = self; R(4) = 2; R(5) = 0; BL(0x800518ECu, hle_fn_80051AA0);  /* (setDemoGoalMode(KIME_POSE, 0)) */
    }
    R(3) = self;
    if (TESTFLAG(0x800518F8u, STATUS_6D)) { R(3) = self; R(4) = 3; R(5) = 0; BL(0x80051910u, hle_fn_80051AA0); }   /* (RUN) */
}
/* executeState_DemoGoal: the goal demo's action, then the background check */
static void pb_executeState_DemoGoal(GM_CTX, gptr self) {
    I2_FN(0x80051AB0u);
    NV_R(31, self);
    R(0) = gm_u32(self + PL_DEMO_SUBSTATE);
    if (CMPS(R(0), 0) == 0) BL(0x80051AF0u, fn_80051590);                  /* (executeDemoGoal_Pole) */
    else if (CMPS(R(0), 1) == 0) BL(0x80051AF8u, hle_fn_800518A0);         /* (executeDemoGoal_Wait) */
    else if (CMPS(R(0), 2) == 0) BL(0x80051B00u, fn_80051930);             /* (executeDemoGoal_KimePose) */
    else if (CMPS(R(0), 3) == 0) VCALL(0x80051B14u, self, VT_DEMO_GOAL_RUN);
    R(3) = self; R(4) = 0; BL(0x80051B20u, hle_fn_800543E0);
}
/* initGoalJump(pos, speed): the frames until the jump comes down to pos.y (the loop polls on each back
   edge, as the PowerPC loop) */
static void pb_initGoalJump(GM_CTX, gptr self, gptr pos) {
    STF(self + PL_SPEED_Y, 1); R(5) = 0;
    LDF(5, self + PL_POS_Y); LDF(2, F_ZERO); LDF(4, F_GOAL_JUMP_ACCEL); LDF(3, F_MAX_FALL);
    for (;;) {
        LDF(0, self + PL_SPEED_Y); STF(self + PL_ACCEL_Y, 4);
        FS(0, F(0) + F(4)); STF(self + PL_SPEED_Y, 0);
        FCMP(F(0), F(3));
        R(0) = rotl32(ctx->cr, 1) & 1u; CR0(ctx, R(0));
        if (R(0)) STF(self + PL_SPEED_Y, 3);
        LDF(0, self + PL_SPEED_Y); FCMP(F(0), F(2));
        FS(5, F(5) + F(0));
        if (CR_BIT(ctx, 0)) {
            LDF(0, pos + VEC_Y); FCMP(F(5), F(0));
            CR_SETBIT(ctx, 2, CR_BIT(ctx, 0) | CR_BIT(ctx, 2));
            if (CR_BIT(ctx, 2)) break;
        }
        R(5) += 1;
        GM_LOOP();
    }
    LDF(0, pos); STF(self + PL_GOAL_JUMP_TARGET, 0);
    LDF(0, pos + 4); STF(self + PL_GOAL_JUMP_TARGET + 4, 0);
    LDF(0, pos + 8); STF(self + PL_GOAL_JUMP_TARGET + 8, 0);
    gm_set_u32(self + PL_GOAL_JUMP_FRAMES, R(5));
    STF(self + PL_SPEED_Y, 1);
}

/* ================================================================== collision, squish */
/* initCollision(body, attack): the body / second body take the first data, the three attacks the second */
static void pb_initCollision(GM_CTX, gptr self) {
    I2_FN(0x800534B0u);
    NV_R(31, R(5)); NV_R(30, R(4)); R(5) = R(30); NV_R(29, self);
    R(4) = self; R(3) = self + PL_CC; BL(0x800534E4u, hle_ActivePhysics_InitWithStruct);
    R(4) = self; R(5) = R(30); R(3) = self + PL_CC1; BL(0x800534F4u, hle_ActivePhysics_InitWithStruct);
    R(4) = self; R(5) = R(31); R(3) = self + PL_ATT_CC1; BL(0x80053504u, hle_ActivePhysics_InitWithStruct);
    R(4) = self; R(5) = R(31); R(3) = self + PL_ATT_CC2; BL(0x80053514u, hle_ActivePhysics_InitWithStruct);
    R(4) = self; R(5) = R(31); R(3) = self + PL_ATT_CC3; BL(0x80053524u, hle_ActivePhysics_InitWithStruct);
}
/* setStampReduction: swimming: sink; else no rise, the squish */
static void pb_setStampReduction(GM_CTX, gptr self) {
    I2_FN(0x80053DF0u);
    R(4) = STATUS_SWIM; NV_R(31, self);
    BL(0x80053E0Cu, hle_testFlag__10daPlBase_cFi);
    if (CMPS(R(3), 0) != 0) { LDF(0, F_MINUS_ONE); STF(self + PL_SPEED_Y, 0); return; }
    LDF(1, self + PL_SPEED_Y); LDF(0, F_ZERO); FCMP(F(1), F(0));
    if (CR_BIT(ctx, 1)) STF(self + PL_SPEED_Y, 0);
    VCALL(0x80053E3Cu, self, VT_SET_REDUCTION_SC);
}
/* initStampReduction: the squish timers, the stomped voice, a quake */
static void pb_initStampReduction(GM_CTX, gptr self) {
    I2_FN(0x80053FE0u);
    R(4) = STATUS_JUMP; NV_R(31, self);
    BL(0x80053FFCu, hle_testFlag__10daPlBase_cFi);
    int set = CMPS(R(3), 0) == 0;
    if (!set) { R(0) = gm_u32(self + PL_SQUISH_KEYFRAME); set = CMPS(R(0), 0) == 0; }
    if (set) { R(0) = 4; gm_set_u32(self + PL_SQUISH_NO_MOVE, 4); }
    R(0) = 10; gm_set_u32(self + PL_SQUISH_COOLDOWN, 10);
    R(3) = self; R(4) = 52; R(5) = 0; VCALL(0x8005403Cu, self, VT_PLAY_VOICE);   /* (VOICE_STOMPED) */
    R(0) = gm_u8(self + PL_PLAYER_NO); R(5) = 7; R(3) = gm_u32(QUAKE_P); R(6) = 0;
    R(4) = (uint32_t)(int8_t)R(0); R(7) = 0;
    BL(0x80054058u, shockMotor__8dQuake_cFScQ28dQuake_c12TYPE_SHOCK_eib_800D8BB0);
}

/* ================================================================== background-check bookkeeping */
/* setOldBGCross: last frame's crosses, the foot history shifted (unrolled) */
static void pb_setOldBGCross(GM_CTX, gptr self) {
    (void)base;
    R(4) = gm_u32(self + PL_NOW_BG_CROSS1); R(0) = gm_u32(self + PL_NOW_BG_CROSS2);
    gm_set_u32(self + PL_OLD_BG_CROSS1, R(4)); gm_set_u32(self + PL_OLD_BG_CROSS1 + 4, R(0));
    for (uint32_t i = 9; i > 0; i--) {
        R(0) = gm_u32(self + PL_FOOT_HISTORY + 4 * (i - 1)); gm_set_u32(self + PL_FOOT_HISTORY + 4 * i, R(0));
    }
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) & 1u; gm_set_u32(self + PL_FOOT_HISTORY, R(0));
}
/* clearBgCheckInfo */
static void pb_clearBgCheckInfo(GM_CTX, gptr self) {
    I2_FN(0x80054370u);
    NV_R(31, self);
    BL(0x80054388u, hle_fn_80054300);                                      /* (setOldBGCross) */
    R(0) = gm_u32(self + PL_STAND_ON_UNIT); R(3) = 0; LDF(0, F_ZERO);
    gm_set_u32(self + PL_NOW_BG_CROSS2, 0); gm_set_u32(self + PL_NOW_BG_CROSS1, 0);
    gm_set_u32(self + PL_STAND_ON_UNIT + 4, R(0)); gm_set_u32(self + PL_STAND_ON_UNIT, 0);
    STF(self + PL_BG_PUSH_FORCE, 0); STF(self + PL_BG_PUSH_FORCE + 4, 0); STF(self + PL_BG_PUSH_FORCE + 8, 0);
    STF(self + PL_EXTRA_PUSH_X, 0);
    gm_set_u32(self + PL_GROUND_TYPE, 0); gm_set_u32(self + PL_WATER_DEPTH, 0);
    STF(self + PL_D80, 0); STF(self + PL_D80 + 4, 0);
}
/* isCarryObjBgCarried(side): the wall's movement kept; a carrying wall whose actor is carried */
static void pb_isCarryObjBgCarried(GM_CTX, gptr self) {
    I2_FN(0x80054EF0u);
    R(0) = rotl32(R(4), 2) & 0x3FCu; R(5) = self + R(0); R(5) = gm_u32(R(5) + BC_CTR_WALL_R);
    if (CMPS(R(5), 0) == 0) { R(3) = 0; return; }
    LDF(1, R(5) + BG_CTR_A0); R(3) = self + R(0); LDF(0, R(5) + BG_CTR_AC); LDF(2, R(5) + BG_CTR_A0 + 4);
    FS(1, F(1) - F(0)); LDF(0, R(5) + BG_CTR_AC + 4);
    STF(R(3) + PL_D80, 1);
    FS(0, F(2) - F(0));
    R(0) = gm_u32(R(5) + BG_CTR_FLAGS); STF(R(1) + 8, 1);
    R(0) &= 0x800u; CR0(ctx, R(0)); STF(R(1) + 12, 0);
    if (!R(0)) { R(3) = 0; return; }
    R(3) = gm_u32(R(5));
    if (CMPS(R(3), 0) == 0) { R(3) = 0; return; }
    R(4) = 0; BL(0x80054F58u, hle_fn_80065FC0);                            /* (dActor_c::checkCarried(nullptr)) */
    R(3) = CMPS(R(3), 0) != 0;
}
/* calcSideLimitMultL / R(limit): at the side limit; moving into it: stopped (a tiny push the way it
   faces when facing away) */
static void pb_calcSideLimitMult(GM_CTX, gptr self, int right) {
    const uint32_t d = right ? 0x70u : 0;                                   /* (R is 0x70 further) */
    I2_FN(0x80055A00u + d); /* FNADDR 0x80055A00 0x80055A70 */
    NV_R(31, self);
    R(0) = gm_u32(self + PL_NOW_BG_CROSS1) | (right ? 0x100000u : 0x80000u); gm_set_u32(self + PL_NOW_BG_CROSS1, R(0));
    BL(0x80055A24u + d, hle_fn_80055900);                                      /* (revSideLimitCommon) */
    LDF(1, self + PL_SPEED_F); LDF(0, F_ZERO); FCMP(F(1), F(0));
    if (!CR_BIT(ctx, right ? 1 : 0)) { R(3) = 0; return; }
    R(0) = gm_u8(self + PL_DIRECTION);
    if (right) { if (CMPS(R(0), 0) == 0) LDF(0, F_SIDE_LIMIT_R); }
    else       { if (CMPU(R(0), 1) == 0) LDF(0, F_SIDE_LIMIT_L); }
    STF(self + PL_SPEED_F, 0);
    R(3) = 1;
}
/* isRideCheckEnable: not rising, and (STATUS_4E) the ridden actor not rising */
static void pb_isRideCheckEnable(GM_CTX, gptr self) {
    I2_FN(0x80056900u);
    LDF(0, F_ZERO); NV_R(31, self); LDF(1, self + PL_SPEED_Y); FCMP(F(1), F(0));
    if (CR_BIT(ctx, 1)) { R(3) = 0; return; }
    R(4) = STATUS_4E; BL(0x80056934u, hle_testFlag__10daPlBase_cFi);
    if (CMPS(R(3), 0) != 0) {
        R(3) = gm_u32(self + PL_RIDE_ACTOR_ID); BL(0x80056944u, hle_search__7fBase_cFUi);
        if (CMPS(R(3), 0) != 0) {
            LDF(1, R(3) + PL_SPEED_Y); LDF(0, F_ZERO); FCMP(F(1), F(0));
            if (CR_BIT(ctx, 1)) { R(3) = 0; return; }
        }
    }
    R(3) = 1;
}

/* ================================================================== position, pushes, nuts */
/* setZPosition(z): set by hand, 32 further back per layer */
static void pb_setZPositionF(GM_CTX, gptr self) {
    I2_FN(0x80057760u);
    R(4) = STATUS_99; ctx->f[31].u = ctx->f[1].u; NV_R(31, self);
    BL(0x80057788u, hle_setFlag__10daPlBase_cFi);
    R(3) = gm_u8(self + PL_LAYER); R(0) = 0x43300000u; gm_set_u32(R(1) + 8, R(0));
    R(0) = rotl32(R(3), 5) & 0xFFFFFFE0u; ctx->f[1].u = ld64(base, D_INT_TO_FLOAT);
    R(0) ^= 0x80000000u; gm_set_u32(R(1) + 12, R(0)); ctx->f[0].u = ld64(base, R(1) + 8);
    FS(0, F(0) - F(1)); FS(0, F(31) - F(0));
    STF(self + PL_POS_Z, 0);
}
/* setAddLiftSpeedF: setJumpAddSpeedF(the background push + the extra push (0.4 of it with the flag)) */
static void pb_setAddLiftSpeedF(GM_CTX, gptr self) {
    I2_FN(0x80057860u);
    R(4) = STATUS_EXTRA_PUSH_FORCE; NV_R(31, self); LDF(31, self + PL_EXTRA_PUSH_X);
    BL(0x80057888u, hle_testFlag__10daPlBase_cFi);
    if (CMPS(R(3), 0) != 0) { LDF(1, F_EXTRA_PUSH_RATE); LDF(0, self + PL_EXTRA_PUSH_X); FS(31, F(1) * F(0)); }
    LDF(0, self + PL_BG_PUSH_FORCE); R(3) = self; FS(1, F(0) + F(31));
    BL(0x800578ACu, hle_modifyPlayerPropertiesWithRollingObject);         /* (setJumpAddSpeedF) */
}
/* updateRideNat: on a nut, not rising: down at its height: STATUS_RIDE_NUT_2; else off */
static void pb_updateRideNat(GM_CTX, gptr self) {
    I2_FN(0x80057D70u);
    R(4) = STATUS_RIDE_NUT; NV_R(31, self);
    BL(0x80057D8Cu, hle_testFlag__10daPlBase_cFi);
    if (CMPS(R(3), 0) != 0) {
        LDF(1, self + PL_SPEED_Y); LDF(0, F_ZERO); FCMP(F(1), F(0));
        CR_SETBIT(ctx, 2, CR_BIT(ctx, 0) | CR_BIT(ctx, 2));
        if (CR_BIT(ctx, 2)) {
            R(3) = self; if (TESTFLAG(0x80057DB4u, STATUS_RIDE_NUT_2)) return;
            LDF(1, self + PL_POS_Y); LDF(0, self + PL_RIDE_NUT_HEIGHT); FCMP(F(1), F(0));
            CR_SETBIT(ctx, 2, CR_BIT(ctx, 0) | CR_BIT(ctx, 2));
            if (!CR_BIT(ctx, 2)) return;
            R(3) = self; SETFLAG(0x80057DDCu, STATUS_RIDE_NUT_2);
            return;
        }
    }
    R(3) = self; CLEARFLAG(0x80057DECu, STATUS_RIDE_NUT_2);
}

/* ================================================================== sounds */
/* suppressSound(mode): mode 1 in the ending dance, or being deleted */
static void pb_suppressSound(GM_CTX, gptr self) {
    I2_FN(0x80057E00u);
    int c = CMPS(R(4), 1); NV_R(31, self);
    if (c == 0) {
        R(4) = STATUS_ENDING_DANCE_AUTO; BL(0x80057E24u, hle_testFlag__10daPlBase_cFi);
        if (CMPS(R(3), 0) != 0) { R(3) = 1; return; }
    }
    R(3) = self; R(4) = STATUS_ABOUT_TO_BE_DELETED; BL(0x80057E40u, hle_testFlag__10daPlBase_cFi);
    R(3) = CMPS(R(3), 0) != 0;
}
/* startSound(id, s, mode) / holdSound(id, s, mode): unless suppressed, the sound object's (id, s, 0) */
static void pb_sound_s(GM_CTX, gptr self, uint32_t fn, uint32_t slot) {
    const uint32_t d = fn - 0x80057EE0u;                                    /* (holdSound is 0xF0 further) */
    I2_FN(fn); /* FNADDR 0x80057EE0 0x80057FD0 */
    NV_R(31, R(5)); NV_R(30, R(4)); R(4) = R(6); NV_R(29, self);
    BL(0x80057F0Cu + d, hle_fn_80057E00);
    if (CMPS(R(3), 0) != 0) return;
    R(12) = gm_u32(self + PL_SND_OBJ); R(3) = self + PL_SND_OBJ; R(4) = R(30); R(5) = R(31);
    R(12) = gm_u32(R(12) + slot); R(6) = 0; ctx->ctr = R(12);
    ctx->lr = 0x80057F34u + d; ppc_call_indirect(ctx, base, ctx->ctr);
}

/* ================================================================== wave 2's hle entry points
   On: the 55 the A/B inputs reach in 300 s (RT_GM_REACH=1). Written but off (behind PL_BASE_UNREACHED2;
   with it, put their names back in hle_funcs.txt): initializeState_Slip (fn_800480D0),
   executeState_WaitJump (fn_8004B0D0), fn_8004c700 (fn_8004C700, self-tested), setWaitJump
   (fn_80057B90). Ranges: the object, and the globals a function changes. The live verify leaves out
   changeState, initializeState_DemoNone, executeState_DemoStartWait, setLandJumpEffect,
   setStampReduction, initStampReduction and executeState_DemoGoal: their calls run other states'
   methods / sounds / quakes / the demo manager twice (the strict A/B is their test). */
#define PB_DEMO_GLOBALS PAUSE_ENABLE_INFO, 12, EXEC_STOP_REQ, 4
PB_INT (fn_800471F0, PB_MEM)                    { pb_preDraw(GM_PASS, SELF); }
PB_VOID(dAcPy_vf294, PB_MEM)                    { pb_changeState(GM_PASS, SELF); }
PB_INT (fn_80047B70, PB_MEM)                    { pb_setCrouchJump(GM_PASS, SELF); }
#ifdef PL_BASE_UNREACHED2
PB_VOID(fn_800480D0, PB_MEM)                    { pb_initializeState_Slip(GM_PASS, SELF); }
#endif
PB_VOID(fn_80048410, PB_MEM)                    { pb_setSlipAction_To(GM_PASS, SELF, 0); }
PB_VOID(fn_800484B0, PB_MEM)                    { pb_setSlipAction_To(GM_PASS, SELF, 1); }
PB_VOID(fn_80048D70, PB_MEM)                    { pb_setHipAttackDropEffect(GM_PASS, SELF); }
PB_VOID(fn_80048E40, PB_MEM)                    { pb_setHipAttack_Ready(GM_PASS, SELF); }
PB_VOID(fn_80048F30, PB_MEM)                    { pb_setHipAttack_AttackStart(GM_PASS, SELF); }
PB_VOID(fn_80048FA0, PB_MEM)                    { pb_setHipAttack_AttackFall(GM_PASS, SELF); }
PB_VOID(fn_80049110, PB_MEM)                    { pb_setHipAttack_StandNormalEnd(GM_PASS, SELF); }
PB_VOID(fn_800494D0, PB_MEM)                    { pb_HipAction_Ground(GM_PASS, SELF); }
PB_VOID(fn_800496D0, PB_MEM)                    { pb_HipAction_StandNormalEnd(GM_PASS, SELF); }
PB_VOID(fn_800497E0, PB_MEM)                    { pb_initializeState_HipAttack(GM_PASS, SELF); }
PB_VOID(fn_80049D70, PB_MEM)                    { pb_setPlayerJumoDaiPos(GM_PASS, SELF); }
#ifdef PL_BASE_UNREACHED2
PB_VOID(fn_8004B0D0, PB_MEM)                    { pb_executeState_WaitJump(GM_PASS, SELF); }
#endif
PB_INT (fn_8004B2F0, PB_MEM)                    { pb_checkCrouchSlip(GM_PASS, SELF); }
PB_VOID(fn_8004BA50, PB_MEM)                    { pb_grandPowerSet(GM_PASS, SELF); }
PB_INT (fn_8004BF00, PB_MEM)                    { pb_getPowerChangeType(GM_PASS, SELF); }
PB_VOID(fn_8004C480, PB_MEM)                    { pb_gravitySet(GM_PASS, SELF); }
PB_VOID(fn_8004C4F0, PB_MEM)                    { pb_setJumpGravity(GM_PASS, SELF); }
#ifdef PL_BASE_UNREACHED2
PB_VOID(fn_8004C700, SELF, 0)                   { pb_windScale(GM_PASS); }
#endif
PB_VOID(fn_8004CD80, PB_MEM)                    { pb_setStartJumpEffect(GM_PASS, SELF); }
PB_VOID(fn_8004CE00, PB_MEM)                    { pb_setLandJumpEffect(GM_PASS, SELF); }
PB_VOID(fn_8004CFD0, PB_MEM)                    { pb_setBrakeSmokeEffect(GM_PASS, SELF); }
PB_VOID(fn_8004DA90, PB_MEM)                    { pb_initialNormal(GM_PASS, SELF); }
PB_INT (fn_8004DD00, PB_MEM)                    { pb_isDemoTypes(GM_PASS, SELF, 1); }
PB_INT (fn_8004DD70, PB_MEM)                    { pb_isDemoTypes(GM_PASS, SELF, 4); }
PB_VOID(fn_8004DE50, PB_MEM, PB_DEMO_GLOBALS)   { pb_onOffDemo(GM_PASS, SELF, 1); }
PB_VOID(fn_8004DEE0, PB_MEM, PB_DEMO_GLOBALS)   { pb_onOffDemo(GM_PASS, SELF, 0); }
PB_VOID(fn_8004E100, PB_MEM, PB_DEMO_GLOBALS)   { pb_playOther(GM_PASS, SELF); }
PB_VOID(fn_8004E1A0, PB_MEM)                    { pb_changeNormalAction(GM_PASS, SELF); }
PB_VOID(fn_8004E450, PB_MEM, PB_DEMO_GLOBALS)   { pb_initializeState_DemoNone(GM_PASS, SELF); }
PB_VOID(fn_8004E710, PB_MEM)                    { pb_executeState_DemoStartWait(GM_PASS, SELF); }
PB_VOID(fn_8004E980, PB_MEM)                    { pb_initDemoInDokan(GM_PASS, SELF); }
PB_INT (fn_8004F1C0, PB_MEM)                    { pb_demo_dokan_move_x(GM_PASS, SELF); }
PB_VOID(fn_8004F670, PB_MEM)                    { pb_initDemoOutDokan(GM_PASS, SELF); }
PB_INT (fn_8004F260, PB_MEM)                    { pb_isEnableDokanInStatus(GM_PASS, SELF); }
PB_INT (fn_80051080, PB_MEM)                    { pb_setHideNotGoalPlayer(GM_PASS, SELF); }
PB_VOID(fn_80051420, PB_MEM)                    { pb_getDemoGoalLandPos(GM_PASS, SELF); }
PB_VOID(fn_800518A0, PB_MEM)                    { pb_executeDemoGoal_Wait(GM_PASS, SELF); }
PB_VOID(fn_80051AB0, PB_MEM)                    { pb_executeState_DemoGoal(GM_PASS, SELF); }
PB_VOID(fn_80051B40, PB_MEM)                    { pb_initGoalJump(GM_PASS, SELF, A(1)); }
PB_VOID(fn_800534B0, PB_MEM)                    { pb_initCollision(GM_PASS, SELF); }
PB_VOID(fn_80053DF0, PB_MEM)                    { pb_setStampReduction(GM_PASS, SELF); }
PB_VOID(fn_80053FE0, PB_MEM)                    { pb_initStampReduction(GM_PASS, SELF); }
PB_VOID(fn_80054300, PB_MEM)                    { pb_setOldBGCross(GM_PASS, SELF); }
PB_VOID(fn_80054370, PB_MEM)                    { pb_clearBgCheckInfo(GM_PASS, SELF); }
PB_INT (fn_80054EF0, PB_MEM)                    { pb_isCarryObjBgCarried(GM_PASS, SELF); }
PB_INT (fn_80055A00, PB_MEM)                    { pb_calcSideLimitMult(GM_PASS, SELF, 0); }
PB_INT (fn_80055A70, PB_MEM)                    { pb_calcSideLimitMult(GM_PASS, SELF, 1); }
PB_INT (fn_80056900, PB_MEM)                    { pb_isRideCheckEnable(GM_PASS, SELF); }
PB_VOID(fn_80057760, PB_MEM)                    { pb_setZPositionF(GM_PASS, SELF); }
PB_VOID(fn_80057860, PB_MEM)                    { pb_setAddLiftSpeedF(GM_PASS, SELF); }
#ifdef PL_BASE_UNREACHED2
PB_INT (fn_80057B90, PB_MEM)                    { pb_setWaitJump(GM_PASS, SELF); }
#endif
PB_VOID(fn_80057D70, PB_MEM)                    { pb_updateRideNat(GM_PASS, SELF); }
PB_INT (fn_80057E00, PB_MEM)                    { pb_suppressSound(GM_PASS, SELF); }
PB_VOID(fn_80057EE0, PB_MEM)                    { pb_sound_s(GM_PASS, SELF, 0x80057EE0u, SO_START_SOUND_S); }
PB_VOID(fn_80057FD0, PB_MEM)                    { pb_sound_s(GM_PASS, SELF, 0x80057FD0u, SO_HOLD_SOUND_S); }

/* ---- wave 2's self-test entries (in RT_GM_SELFTEST=pl_base, with the wave-1 table): the functions that
   only read / write the object, the flags and pure helpers */
static void pb_randomize2(GM_CTX) {
    gptr s = pb_test_self;
    gm_set_u32(s + PL_NO_GRAVITY_TIMER, gm_rand() % 2 ? 0 : gm_rand());
    gm_set_u8(s + PL_LAYER, (uint8_t)(gm_rand() % 3 ? gm_rand() % 3 : gm_rand()));
    gm_set_f32(s + PL_SPEED_Y, pb_rfloat()); gm_set_f32(s + PL_POS_Y, pb_rfloat()); gm_set_f32(s + PL_POS_X, pb_rfloat());
    gm_set_f32(s + PL_WARP_POS_X, pb_rfloat()); gm_set_f32(s + PL_WARP_POS_Z, pb_rfloat());
    gm_set_u32(s + PL_GOAL_TOUCH_ORDER, gm_rand() % 5);
    gm_set_f32(s + PL_RIDE_NUT_HEIGHT, pb_rfloat()); gm_set_f32(s + PL_EXTRA_PUSH_X, pb_rfloat());
    gm_set_f32(s + PL_BG_PUSH_FORCE, pb_rfloat());
    for (uint32_t a = 0; a < 12; a += 4) gm_set_f32(s + ST_VEC + a, pb_rfloat());
    for (uint32_t a = 0; a < 40; a += 4) gm_set_u32(s + PL_FOOT_HISTORY + a, gm_rand() & 1);
    gm_set_u32(s + PL_STAND_ON_UNIT, gm_rand()); gm_set_u32(s + PL_DEMO_SUBSTATE, gm_rand() % 5);
    (void)base; (void)ctx;
}
static const gm_test_t pb_tests_w2[] = {
    GM_TEST(fn_8004BF00, GMV_RET, "b"), GM_TEST(fn_80051420, 0, ""),
    GM_TEST(fn_80051B40, 0, "V"), GM_TEST(fn_800518A0, 0, ""), GM_TEST(fn_80054300, 0, ""), GM_TEST(fn_80054370, 0, ""),
    GM_TEST(fn_80057760, 0, ""), GM_TEST(fn_80057860, 0, ""), GM_TEST(fn_80057D70, 0, ""), GM_TEST(fn_80057E00, GMV_RET, "b"),
    GM_TEST(fn_8004C480, 0, ""), GM_TEST(fn_8004C4F0, 0, ""), GM_TEST(fn_80056900, GMV_RET, ""),
    GM_TEST(fn_8004DD00, GMV_RET, ""), GM_TEST(fn_8004DD70, GMV_RET, ""), GM_TEST(fn_8004F260, GMV_RET, ""),
#ifdef PL_BASE_UNREACHED2
    GM_TEST(fn_8004C700, 0, ""),
#endif
};
static int pb_tests2(const gm_test_t **t) { *t = pb_tests_w2; return (int)(sizeof pb_tests_w2 / sizeof *pb_tests_w2); }
