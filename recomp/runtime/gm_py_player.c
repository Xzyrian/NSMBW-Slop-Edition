/* gm_py_player.c - the 8-player module's overrides of the player classes daPlBase_c and dAcPy_c
 * (track B, gm.h, docs/DECOMP.md), instance 2.
 *
 * The module (nsmbw-project v0.6.5, wiimj2d/d_static/d_a_player/d_a_player_base.cpp and
 * wiimj2d/d_player/d_actors/d_a_player.cpp) replaces 24 of the players' methods: pipes and rail
 * pipes, the goal and "other players stop" demos for eight players, the control demo (with its
 * anti-softlock timer and the item Toad's walking / swimming), wall slides, spin lift-ups (also of
 * tiles, a game rule), the rope angle, falling out of the screen into a bubble, lives / game over,
 * power-up changes, scene changes and the damage entry points (death messages).
 *
 * Register-exact (gm_i2.h): r0-r12, CR0 (and CR2 where the code keeps a CR field), CTR, XER[CA],
 * f0-f13 and both paired-single halves as the PowerPC code leaves them; the non-volatile registers
 * held as the PowerPC code holds them at each call (NV_R), the frames pushed with their prologues
 * replayed (I2_FN). The bodies follow the PowerPC code's branch structure; the labels name the
 * PowerPC addresses where a goto is clearer than nesting.
 *
 * Which functions are on (reached by the A/B inputs) and how they were verified: see the list
 * before the entry points at the end. */
#include "gm_i2.h"
RT_STATE_FILE                                   /* (game code: its variables are part of a save state) */

/* ---- daPlBase_c / dAcPy_c fields (checked against the recompiled code) */
#define PL_VTABLE           96          /* (fBase_c: the vtable) */
#define PL_POS              172         /* mVec3_c mPos */
#define PL_SPEED            232         /* mVec3_c mSpeed */
#define PL_MAX_FALL_SPEED   244         /* mVec3_c (create: zeroed) */
#define PL_ANGLE_Y          258         /* s16 mAngle.y */
#define PL_SPEED_F          268         /* float mSpeedF */
#define PL_ACCEL_Y          276
#define PL_MAX_SPEED_F      280
#define PL_DIRECTION        840         /* u8 mDirection */
#define PL_KIND             908         /* u8 mKind (2 = Yoshi) */
#define PL_PLR_NO           909         /* s8 mPlrNo */
#define PL_EXEC_STOP_MASK   910         /* u8 mExecStopMask */
#define PL_LAYER            911         /* u8 mLayer */
#define PL_DEMO_STATE       1012        /* s8 mDemoState (the control demo's substate) */
#define PL_GOTO_DEST        1016        /* (the next-goto: the low byte at +1019) */
#define PL_GOTO_POS         1020        /* mVec3_c mGotoPos / mControlDemoTargetPos */
#define PL_RAIL_DIR         1032        /* float [2] the rail pipe's direction */
#define PL_RAIL_POINT       1068        /* s16 the rail point */
#define PL_RAIL_TIMER       1070        /* s16 */
#define PL_GOAL_ORDER       1076        /* s32 the place at the goal pole */
#define PL_DEMO_TARGET_X    1104        /* float mControlDemoTargetPos.x */
#define PL_DEMO_SPEED_F     1116        /* float mControlDemoSpeedF */
#define PL_KINOPIO_DIR      1120        /* s32 mItemKinopioDirection */
#define PL_KINOPIO_TIMER    1124        /* s32 mItemKinopioTurnTimer */
#define PL_MDL_MNG          3560        /* dPyMdlMng_c *mpModelMng */
#define PL_AUDIO_REMOTE     3652
#define PL_SND_TYPE         3736
#define PL_KEY              3748        /* dAcPyKey_c mKey (its first word: the remote number) */
#define PL_MODEL_HEIGHT     4144
#define PL_STAR_TIME        4208
#define PL_STAR_COUNT       4225
#define PL_MODE             4240        /* PLAYER_MODE_e mPlayerMode */
#define PL_BGC_FLAGS        4308        /* mNowBgCross (the byte at +4311: bit 0 = BGC_FOOT) */
#define PL_ATTACK           4661        /* u8 mAttCc1.mCcData.mAttack */
#define PL_DEMO_ARG         5204        /* m_DemoStateArg */
#define PL_SUBSTATE_TIMER   5212        /* s32 m_DemoSubstateTimer */
#define PL_STATE_MGR        5272        /* m_StateMgr (its getStateID()->isEqual: the vtable at +0, slot 16) */
#define PL_SUBSTATE_VALUE   5292
#define PL_TYPE             5332        /* PLAYER_TYPE_e mPlayerType */
#define PL_NEXT_MODE        5344        /* PLAYER_MODE_e mNextMode */
#define PL_PC               5372        /* dPc_c mPc (+4 = its angle part, +16 = mCtr) */
#define PL_REST_FLAG        5460        /* m0x1554 */
#define PL_ROPE_ANGLE       7640        /* s16 mRopeAngle, mPrevRopeAngle, mPcAngle, mPrevPcAngle */
#define PL_LIFT_ID          10196       /* the actor to lift (fBaseID_e) */
#define PL_LIFT_TIMER       10208
#define PL_PY_MDL_MNG       10848       /* dPyMdlMng_c mPyMdlMng (+4: mModel) */
#define PL_MODEL            10852
#define PL_CARRY_ID         10872
#define PL_PROPEL_PARTS     11176
/* the virtual methods (vtable offsets) */
#define VT_IS_ITEM_KINOPIO  224
#define VT_SET_POWERUP      228
#define VT_IS_CHANGE        288
#define VT_SET_PRESS_BG_DMG 280
#define VT_CHANGE_STATE     660
#define VT_IS_CARRY         968
#define VT_IS_NO_DAMAGE     1008
#define VT_PLAY_VOICE       1076
#define VT_SET_DAMAGE2      1104
/* the module's data and the game's globals */
#define PY_ACT_INFO         0x8185E888u
#define PY_ENTRY            0x8185E890u /* s32 daPyMng_c::mPlayerEntry[8] */
#define PY_TYPE             0x8185E93Cu /* daPyMng_c::mPlayerType[8] */
#define PY_MODE             0x8185E95Cu /* daPyMng_c::mPlayerMode[8] */
#define PY_CREATE_ITEM      0x8185E97Cu /* daPyMng_c::mCreateItem[8] */
#define PY_STAR_TIME        0x8185EAD0u /* s16 [8]: the star time carried over (gm_py_mng.c calls it m_star_count) */
#define PY_STAR_COUNT       0x8185EAE0u /* s16 [8]: the star count carried over (gm_py_mng.c: m_star_time) */
#define PY_REST             0x81851D8Cu /* s32 mRest[8] */
#define PY_HIO_TABLE        0x81851D5Cu /* dPyStatic_HIO_c * per character */
#define GAME_RULE           0x8185FE04u /* dGameRule_s::current: +4 stop allowed, +8 death messages, +9 liftable tiles */
#define STACK_GUARD         0x8185FED4u
#define EXEC_STOP_REQ       0x80429CF8u /* u8 dActor_c::mExecStopReq (r13 - 22920) */
#define DEMO_MNG_P          0x80429C94u /* daPyDemoMng_c::mspInstance */
#define BG_P                0x80429DD0u /* dBg_c::m_bg_p */
#define QUAKE_P             0x8042A008u /* dQuake_c::m_instance */
#define EXIT_MODE           0x8042900Cu /* dScStage_c's exit mode */
#define DIR_SPEED           0x8042B840u /* float sc_DirSpeed[2] */
#define PROPEL_HIO          0x80370DA0u
#define SIGN                0x8000000000000000ull

/* ---- the natives / functions called (other files) */
void hle_getPlayer__9daPyMng_cFi(ppc_context *ctx, uint8_t *base);
void hle_search__7fBase_cFUi(ppc_context *ctx, uint8_t *base);
void hle_create__13dStageActor_cF6ActorsUiP7Point3dP6S16VecUc(ppc_context *ctx, uint8_t *base);
/* (this file's, called from each other: the hle_ entries, so a verified call verifies them too) */
#ifdef PY_PLAYER_UNREACHED
void hle_mod_fn_800511A0(ppc_context *ctx, uint8_t *base);
#define PLAY_GOAL_OTHER hle_mod_fn_800511A0
#else
#define PLAY_GOAL_OTHER mod_fn_800511A0_81802D7C     /* (off: the recompiled module function) */
#endif
void hle_mod_fn_80139210(ppc_context *ctx, uint8_t *base);

/* (single-precision helpers: lfs and single arithmetic set both halves) */
#define LDF(n, a)  (ctx->f[n].d = ctx->ps1[n] = ldfs(base, (a)))
#define STF(a, n)  stfs(base, (a), ctx->f[n].d)
#define FS(n, e)   (ctx->f[n].d = ctx->ps1[n] = frsp(e))
#define F(n)       (ctx->f[n].d)
#define FCMP(a, b) cr_fcmp(ctx, 0, (a), (b))
#define FLT        CR_BIT(ctx, 0)
#define FGT        CR_BIT(ctx, 1)
#define FEQ        CR_BIT(ctx, 2)
/* a call through the object's vtable (+96), the function through register t into CTR */
#define VCALL(ra, obj, slot, t) i2_vcall(ctx, base, (ra), (obj), (slot), (t))
#define TESTFLAG(ra, f)  (R(4) = (f), BL((ra), hle_testFlag__10daPlBase_cFi), CMPU(R(3), 0) != 0)
#define SETFLAG(ra, f)   (R(4) = (f), BL((ra), hle_setFlag__10daPlBase_cFi))
/* dQuake_c::m_instance->shockMotor(mPlrNo, type, 0, false) */
static void pp_shock(GM_CTX, gptr self, uint32_t type, uint32_t ra) {
    R(4) = gm_u8(self + PL_PLR_NO); R(3) = gm_u32(QUAKE_P); R(5) = type;
    R(4) = (uint32_t)(int8_t)R(4); R(6) = 0; R(7) = 0;
    BL(ra, shockMotor__8dQuake_cFScQ28dQuake_c12TYPE_SHOCK_eib_800D8BB0);
}
/* dScStage_c::isGameStopAllowed(): the rule, or more than one player, or the game's check */
static int pp_gameStopAllowed(GM_CTX, int r, uint32_t ra_num, uint32_t ra_chk) {
    R(r) = gm_u8(GAME_RULE + 4);                                         /* (the rule's byte goes through r3 or r4) */
    if (CMPU(R(r), 1) != 0) return 1;
    BL(ra_num, hle_mod_getNumInGame__9daPyMng_cFv);
    if (CMPU(R(3), 1) == 0) return 1;
    BL(ra_chk, fn_801021B0);
    return CMPU(R(3), 0) != 0;
}
/* m_StateMgr.getStateID()->isEqual(id) (r5 = the method) */
static int pp_isState(GM_CTX, gptr self, uint32_t ra, uint32_t id) {
    R(3) = gm_u32(self + PL_STATE_MGR); R(4) = gm_u32(R(3)); R(5) = gm_u32(R(4) + 16);
    R(4) = id; ctx->ctr = R(5); ctx->lr = ra; ppc_call_indirect(ctx, base, ctx->ctr);
    return CMPU(R(3), 0) != 0;
}
#define STATE_WALK          0x8035425Cu /* daPlBase_c::StateID_Walk ... */
#define STATE_TURN          0x8035441Cu
#define STATE_FALL          0x8035431Cu
#define STATE_SWIM          0x8035449Cu
#define STATE_DEMO_NONE     0x8035476Cu
#define STATE_DEMO_IN_DOKAN_L 0x803548ECu
#define DEMO_STATE_TABLE    0x81851D80u /* the module's DemoInDokanD / U / R / L table */

/* ================================================================== daPlBase_c */
/* initDemoInDokanUD(dir): into an up / down pipe - the goto position, the entry offset (per
   character / power-up, or for a Yoshi by its rider) */
static void pl_initDemoInDokanUD(GM_CTX, gptr self, uint32_t dir) {
    I2_FN(0x81802840u);
    NV_R(30, self);
    R(3) = gm_u32(self + PL_MDL_MNG); NV_R(29, dir);
    R(3) = gm_u32(R(3) + 4);                                             /* (mModel->setAnm(0, rate, blend, 0.0f)) */
    R(4) = 0x80370DA0u; LDF(1, R(4) + 44);
    R(5) = gm_u32(R(3)); LDF(2, R(4) + 48);
    R(4) = gm_u32(R(5) + 92); R(5) = 0x81850000u; LDF(3, 0x81848674u);
    ctx->ctr = R(4); R(4) = 0;
    ctx->lr = 0x81802894u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = gm_u32(self + PL_POS); int up = CMPU(R(29), 1) == 0; R(4) = gm_u32(self + PL_POS + 4);
    gm_set_u32(self + PL_GOTO_POS, R(3)); R(3) = gm_u32(self + PL_POS + 8); NV_R(28, gm_u8(self + PL_KIND));
    gm_set_u32(self + PL_GOTO_POS + 4, R(4)); gm_set_u32(self + PL_GOTO_POS + 8, R(3));
    if (up) {
        R(4) = gm_u32(self + PL_DEMO_ARG); R(5) = 0x81850000u - 30720; R(3) = R(28) ^ 2;
        R(4) ^= 2; R(4) = cntlzw(R(4)); R(4) = i2_rotl(R(4), 29) & 4;
        LDF(1, R(5) + R(4));                                             /* (16 / 32) */
        R(4) = 0x81850000u - 30688; R(3) = cntlzw(R(3)); LDF(0, self + PL_GOTO_POS + 4);
        R(3) = i2_rotl(R(3), 29) & 4; LDF(2, R(4) + R(3));               /* (8 / 16) */
        FS(0, F(0) + F(1)); LDF(3, self + PL_POS + 4);
        int yoshi = CMPU(R(28), 2) == 0;
        STF(self + PL_GOTO_POS + 4, 0); FS(0, F(3) - F(2)); STF(self + PL_POS + 4, 0);
        if (yoshi) goto angle0;
        goto done;
    }
    R(3) = self; SETFLAG(0x8180291Cu, 42);
    if (CMPU(R(28), 2) == 0) {                                           /* a Yoshi: by its rider */
        R(3) = self; BL(0x8180292Cu, hle_getPlayerRideOn__9daYoshi_cCFv);
        if (CMPU(R(3), 0) == 0) { R(3) = 0x81850000u; LDF(0, 0x81848754u); goto offset; }
        R(4) = gm_u32(R(3) + PL_MODE); R(5) = 8;
        if (CMPU(R(4), 3) != 0) R(5) = 4;
        int none = CMPU(R(4), 0) == 0; R(4) = 0;
        if (!none) R(4) = R(5);
        R(3) = gm_u32(R(3) + PL_TYPE); R(5) = 3;
        if (CMPU(R(3), 7) <= 0) R(5) = R(3);
        R(3) = R(5) << 2; R(5) = PY_HIO_TABLE; R(3) = gm_u32(R(5) + R(3));
        LDF(0, R(3) + R(4));
    offset:
        LDF(1, self + PL_POS + 4); R(3) = 0x81850000u; LDF(2, 0x818487ACu);
        FS(0, F(1) - F(0)); STF(self + PL_GOTO_POS + 4, 0);
        FS(0, F(1) + F(2)); STF(self + PL_POS + 4, 0);
    angle0:
        R(3) = 0; gm_set_u16(self + PL_ANGLE_Y, 0);
        goto done;
    }
    R(3) = gm_u32(self + PL_MODE);
    if (CMPU(R(3), 0) == 0) { R(3) = 12; goto zero; }
    if (CMPU(R(3), 4) == 0) { LDF(0, self + PL_MODEL_HEIGHT); R(3) = 24; goto hio; }
    if (CMPU(R(3), 3) != 0) { LDF(0, self + PL_MODEL_HEIGHT); R(3) = 20; goto hio; }
    R(3) = 16;
zero:
    R(4) = 0x81850000u; LDF(0, 0x81848674u);
hio:
    R(4) = gm_u32(self + PL_TYPE); R(5) = 3;
    if (CMPU(R(4), 7) <= 0) R(5) = R(4);
    R(4) = R(5) << 2; R(5) = PY_HIO_TABLE; R(4) = gm_u32(R(5) + R(4));
    LDF(2, self + PL_POS + 4); LDF(1, R(4) + R(3));
    R(3) = 0x81850000u; LDF(3, 0x818487ACu);
    FS(0, F(0) + F(1)); FS(0, F(2) - F(0)); STF(self + PL_GOTO_POS + 4, 0);
    FS(0, F(2) + F(3)); STF(self + PL_POS + 4, 0);
done:
    R(3) = self; BL(0x81802A4Cu, hle_fn_8004E980);                          /* (initDemoInDokan) */
}

/* the current course's dCdFile_c (r13 copies; 0 when its areas are missing) */
static void pl_cdFile(GM_CTX, int rf, int rs, int rd) {
    R(rf) = gm_u32(R(13) - 21720); R(rs) = gm_u32(R(13) - 22536);
    R(0) = gm_u8(R(rf) + 4622); R(0) = (uint32_t)((int32_t)R(0) * 944); R(rd) = R(rs) + R(0);
    R(0) = gm_u32(R(rd) + 44);
    if (CMPS(R(0), 0) == 0) R(rd) = 0;
}
/* initializeState_DemoRailDokan: into a rail pipe - the rail, its first point and direction */
static void pl_initializeState_DemoRailDokan(GM_CTX, gptr self) {
    I2_FN(0x81802A68u);
    gptr sp = gm_frame_sp;
    R(4) = 187; NV_R(31, self);
    BL(0x81802A88u, hle_setFlag__10daPlBase_cFi);
    pl_cdFile(GM_PASS, 3, 4, 3);
    R(0) = gm_u32(self + PL_GOTO_DEST); R(4) = R(0) & 0xFF;
    BL(0x81802ABCu, hle_getNextGotoByID__9dCourse_cFUc);
    NV_R(30, R(3)); R(3) = gm_u8(R(3) + 15);
    BL(0x81802AC8u, hle_GetRail);
    pl_cdFile(GM_PASS, 4, 5, 6);
    R(0) = gm_u16(R(30) + 16) & 1; CR0(ctx, R(0));
    if (R(0)) { R(7) = gm_u16(R(3) + 4); R(0) = R(7) - 2; gm_set_u16(self + PL_RAIL_POINT, (uint16_t)R(0)); }   /* (backwards: from the end) */
    else { R(0) = 1; gm_set_u16(self + PL_RAIL_POINT, 1); }
    R(5) = gm_u16(R(3) + 2); R(4) = (uint32_t)(int16_t)gm_u16(self + PL_RAIL_POINT);
    R(6) = gm_u32(R(6) + 60); R(0) = R(5) + R(4); R(0) <<= 4; R(5) = R(6) + R(0);
    R(4) = (uint32_t)(int16_t)gm_u16(R(5) + 2); R(3) = 0x43300000u;
    R(0) = (uint32_t)(int16_t)gm_u16(R(5)); R(4) = (uint32_t)-(int32_t)R(4);
    gm_set_u32(sp + 16, R(3)); R(4) ^= 0x80000000u; R(0) ^= 0x80000000u;
    gm_set_u32(sp + 20, R(4)); ctx->f[3].u = ld64(base, R(2) - 30664); ctx->f[0].u = ld64(base, sp + 16);
    gm_set_u32(sp + 28, R(0)); FS(2, F(0) - F(3)); LDF(0, self + PL_POS + 4);
    gm_set_u32(sp + 24, R(3)); LDF(1, self + PL_POS);
    FS(4, F(2) - F(0)); ctx->f[0].u = ld64(base, sp + 24); FS(2, F(0) - F(3));
    STF(sp + 12, 4); FS(0, F(4) * F(4)); FS(1, F(2) - F(1)); STF(sp + 8, 1);
    FS(1, F(1) * F(1)); FS(1, F(1) + F(0));
    BL(0x81802B90u, sqrt__Q23EGG7Math_f_Ff_802BE470);
    LDF(2, sp + 12); LDF(0, sp + 8); FS(3, F(2) / F(1));
    LDF(2, R(2) - 30488); LDF(4, R(2) - 30652);
    FS(0, F(0) / F(1)); FS(3, F(2) * F(3)); FS(2, F(2) * F(0)); FS(1, F(1) * F(4));
    STF(self + PL_RAIL_DIR + 4, 3); STF(self + PL_RAIL_DIR, 2);
    ctx->f[0].u = fctiw_bits(F(1), 1); st64(base, sp + 32, ctx->f[0].u);
    R(0) = gm_u32(sp + 36); gm_set_u16(self + PL_RAIL_TIMER, (uint16_t)R(0));
}

/* setExitRailDokan: out of a rail pipe - the destination's pipe entry */
static void pl_setExitRailDokan(GM_CTX, gptr self) {
    I2_FN(0x81802BE4u);
    NV_R(30, self);
    R(3) = gm_u32(0x8042A1C8u); R(4) = gm_u32(0x80429E98u);             /* (dScStage_c / dCd_c instances) */
    R(3) = gm_u8(R(3) + 4622); NV_R(29, 0);
    R(3) = (uint32_t)((int32_t)R(3) * 48); R(3) = R(4) + R(3);
    R(4) = gm_u32(R(3) + 44);
    if (CMPU(R(4), 0) != 0) NV_R(29, R(3));
    R(4) = gm_u8(self + PL_GOTO_DEST + 3); R(3) = R(29);
    BL(0x81802C38u, hle_getNextGotoByID__9dCourse_cFUc);
    R(4) = gm_u8(R(3) + 10); R(3) = R(29);
    BL(0x81802C44u, hle_getNextGotoByID__9dCourse_cFUc);
    R(4) = gm_u8(R(3) + 11); R(5) = gm_u8(R(3) + 14);
    R(3) = R(4) - 3; R(4) = R(3) & 0xFF;
    int c = CMPU(R(4), 3);
    gm_set_u8(self + PL_LAYER, (uint8_t)R(5));
    if (c > 0) {                                                         /* (assert: the type is a pipe) */
        R(4) = 0x81850000u - 30304; R(3) = R(4) + 394; R(5) = R(4) + 474; R(6) = R(4) + 2513;
        CR_SETBIT(ctx, 6, 0); R(4) = 242;
        BL(0x81802CC4u, mod_OSPanic_818380F8);
        return;
    }
    if (c < 0) { R(3) = i2_rotl(R(3), 2) & 0x3FC; R(4) = gm_u32(DEMO_STATE_TABLE + R(3)); }
    else { R(3) = 0x80350000u; R(4) = STATE_DEMO_IN_DOKAN_L; }
    R(3) = self; R(5) = 1;
    BL(0x81802C8Cu, hle_fn_8004E290);                                        /* (changeDemoState) */
}

/* stopGoalOther / playGoalOther: the other players' execution stops (resumes) while a player is
   at the goal - the players with the goal flag keep running (stop) or get their stop bit back */
static void pl_goalOther_loop(GM_CTX, gptr self, int stop, int r_left, int r_i, const uint32_t ra[5]) {
    for (uint32_t p = 0;; ) {
        R(3) = p; BL(ra[0], getCtrlPlayer__9daPyMng_cFi_8005FB90);
        if (CMPU(R(3), 0) != 0) {
            if (!stop) R(3) = self;                                      /* (the module tests its own flag here) */
            if (TESTFLAG(ra[1], 101)) {
                R(3) = p; BL(ra[2], hle_getPlayer__9daPyMng_cFi);
                if (CMPU(R(3), 0) != 0) {
                    R(4) = gm_u8(R(3) + PL_EXEC_STOP_MASK);
                    if (stop) { R(4) &= 0xFD; CR0(ctx, R(4)); } else R(4) |= 2;
                    gm_set_u8(R(3) + PL_EXEC_STOP_MASK, (uint8_t)R(4));
                }
                R(3) = p; BL(ra[3], hle_mod_getYoshi__9daPyMng_cFi);
                if (CMPU(R(3), 0) != 0) {
                    R(4) = gm_u8(R(3) + PL_EXEC_STOP_MASK);
                    if (stop) { R(4) &= 0xFD; CR0(ctx, R(4)); } else R(4) |= 2;
                    gm_set_u8(R(3) + PL_EXEC_STOP_MASK, (uint8_t)R(4));
                }
            }
        }
        NV_R(r_left, R(r_left) - 1);
        int more = CMPU(R(r_left), 0) > 0;
        NV_R(r_i, ++p);
        if (!more) break;
        GM_LOOP();
    }
}
static void pl_stopGoalOther(GM_CTX, gptr self) {
    I2_FN(0x81802CC4u);
    BL(0x81802CDCu, hle_fn_8004E040);                                        /* (isPlayerGameStop) */
    if (CMPU(R(3), 0) == 0) return;
    R(3) = 0x80430000u; R(4) = gm_u8(EXEC_STOP_REQ);
    NV_R(29, 8); NV_R(30, 0);
    R(4) |= 0xF; gm_set_u8(EXEC_STOP_REQ, (uint8_t)R(4));
    static const uint32_t ra[5] = { 0x81802D04u, 0x81802D14u, 0x81802D24u, 0x81802D40u };
    pl_goalOther_loop(GM_PASS, self, 1, 29, 30, ra);
}
static void pl_playGoalOther(GM_CTX, gptr self) {
    I2_FN(0x81802D7Cu);
    NV_R(30, self);
    R(3) = 0x80430000u; R(4) = gm_u8(EXEC_STOP_REQ);
    NV_R(28, 8); NV_R(29, 0);
    R(4) &= 0xF0; gm_set_u8(EXEC_STOP_REQ, (uint8_t)R(4));
    static const uint32_t ra[5] = { 0x81802DB8u, 0x81802DCCu, 0x81802DDCu, 0x81802DF8u };
    pl_goalOther_loop(GM_PASS, self, 0, 28, 29, ra);
}

/* setControlDemoWalk(pos, speed): walk to x = *pos at |*speed| (at most the high speed); a new
   target restarts the module's anti-softlock timer (10 s) */
static void pl_setControlDemoWalk(GM_CTX, gptr self, gptr pos, gptr speed) {
    I2_FN(0x81802E38u);
    NV_R(28, pos); R(4) = 114; NV_R(29, speed); NV_R(30, self);
    BL(0x81802E68u, hle_testFlag__10daPlBase_cFi);
    if (CMPU(R(3), 0) == 0) return;
    R(3) = gm_u8(self + PL_DEMO_STATE); LDF(0, R(28));
    int same = 0;
    if (CMPU(R(3), 1) == 0) { LDF(1, self + PL_DEMO_TARGET_X); FCMP(F(1), F(0)); same = FEQ; }
    if (!same) { R(3) = 600; gm_set_u32(self + PL_SUBSTATE_TIMER, 600); }
    STF(self + PL_DEMO_TARGET_X, 0);
    R(3) = 1; LDF(0, R(29));
    gm_set_u8(self + PL_DEMO_STATE, 1);
    R(3) = self; ctx->f[31].u = ctx->f[0].u & ~SIGN;                    /* (fabs: ps0 only) */
    STF(self + PL_DEMO_SPEED_F, 31);
    BL(0x81802EB4u, hle_fn_80057650);                                        /* (getSpeedData) */
    LDF(0, R(3) + 8); FCMP(F(0), F(31));
    if (!FLT) return;
    R(3) = self; BL(0x81802EC8u, hle_fn_80057650);
    R(3) = gm_u32(R(3) + 8); gm_set_u32(self + PL_DEMO_SPEED_F, R(3));
}

/* executeState_DemoControl: the control demo's substates - walk to a target (with the timer),
   wait for the timer, the item Toad's walk / swim / sink-sand wait */
static void pl_executeState_DemoControl(GM_CTX, gptr self) {
    I2_FN(0x81802EF0u);
    R(4) = 116; NV_R(30, self);
    BL(0x81802F10u, hle_clearFlag__10daPlBase_cFi);
    R(3) = self;
    if (TESTFLAG(0x81802F1Cu, 115)) {
        R(3) = gm_u8(self + PL_BGC_FLAGS + 3) & 1; CR0(ctx, R(3));
        if (!R(3)) { R(3) = 0x81850000u; LDF(0, self + PL_SPEED_F); LDF(1, 0x818486A8u); FS(0, F(0) * F(1)); STF(self + PL_SPEED_F, 0); }
        else { R(3) = self; R(4) = 115; BL(0x81802F54u, hle_clearFlag__10daPlBase_cFi); }
    }
    R(3) = gm_u8(self + PL_DEMO_STATE);
    int c = CMPS(R(3), 5);
    if (c < 0) goto below5;
    if (c == 0) goto kinopio_walk;
    if (CMPU(R(3), 6) == 0) goto kinopio_swim;
    if (CMPU(R(3), 7) != 0) return;
    /* 7: the item Toad waits on sink sand */
    R(3) = gm_u8(self + PL_BGC_FLAGS + 3) & 1; CR0(ctx, R(3));
    if (!R(3)) goto to_wait;
    if (!pp_isState(GM_PASS, self, 0x81802F9Cu, STATE_WALK) && !pp_isState(GM_PASS, self, 0x81802FC0u, STATE_TURN)) goto to_wait;
    R(3) = self; SETFLAG(0x81802FD4u, 116);
    R(3) = self; SETFLAG(0x81802FE0u, 99);
    R(3) = self; R(4) = 0; BL(0x81802FECu, fn_800526C0);                /* (checkKinopioWaitBG) */
    if (CMPU(R(3), 0) != 0) {
        R(3) = self; R(4) = 1; BL(0x81803000u, fn_800526C0);
        if (CMPU(R(3), 0) != 0) return;
    }
    R(3) = self; BL(0x81803010u, fn_80052300);                          /* (setControlDemoKinopioWalk) */
    return;
below5:
    if (CMPU(R(3), 1) == 0) goto walk;
    if (CMPU(R(3), 4) != 0) return;
    /* 4: when the timer runs out, the demo ends */
    R(3) = gm_u32(self + PL_SUBSTATE_TIMER);
    if (CMPU(R(3), 0) != 0) return;
    R(3) = 0x80350000u; R(4) = STATE_DEMO_NONE; R(3) = self; R(5) = 0;
    BL(0x81803044u, hle_fn_8004E290);
    return;
kinopio_walk:                                                            /* 5: the item Toad walks about */
    R(3) = gm_u8(self + PL_BGC_FLAGS + 3) & 1; CR0(ctx, R(3));
    if (!R(3)) goto to_wait;
    if (!pp_isState(GM_PASS, self, 0x81803070u, STATE_WALK) && !pp_isState(GM_PASS, self, 0x81803094u, STATE_TURN)) goto to_wait;
    R(3) = self; SETFLAG(0x818030A8u, 116);
    R(3) = gm_u8(self + PL_BGC_FLAGS) & 0x18; CR0(ctx, R(3));
    if (!R(3)) goto kinopio_turn;
sink_sand:
    R(3) = 7; gm_set_u8(self + PL_DEMO_STATE, 7);
    R(3) = 0; gm_set_u32(self + PL_DEMO_SPEED_F, 0);
    gm_set_u32(self + PL_SPEED_F, R(3));
    return;
kinopio_swim:                                                            /* 6: the item Toad swims */
    if (!pp_isState(GM_PASS, self, 0x818030E4u, STATE_SWIM)) goto to_wait;
    R(3) = self; SETFLAG(0x818030F8u, 116);
    R(3) = gm_u8(self + PL_BGC_FLAGS + 3) & 1; CR0(ctx, R(3));
    if (R(3)) {
        R(4) = gm_u32(self + PL_KINOPIO_DIR); R(3) = self;
        BL(0x81803110u, fn_80052650);                                    /* (isHitWallKinopioWalk) */
        if (CMPU(R(3), 0) != 0) { R(3) = gm_u32(self + PL_KINOPIO_DIR) ^ 1; gm_set_u32(self + PL_KINOPIO_DIR, R(3)); }
    }
    R(4) = gm_u32(self + PL_KINOPIO_DIR); R(3) = self + PL_KEY; NV_R(30, self + PL_SPEED_F);
    if (CMPU(R(4), 0) != 0) {
        R(4) = 8; BL(0x81803140u, setTransientForcedButtons__14dPlayerInput_cFUi_8005E960);
        R(3) = 0x81850000u; LDF(1, 0x81848788u);                         /* (-0.5625) */
    } else {
        R(4) = 4; BL(0x81803268u, setTransientForcedButtons__14dPlayerInput_cFUi_8005E960);
        R(3) = 0x81850000u; LDF(1, 0x81848768u);                         /* (0.5625) */
    }
    R(3) = 0x81850000u; LDF(2, 0x81848764u);
    R(3) = R(30); BL(0x81803280u, fn_8015F470);                         /* (sLib::chase(&mSpeedF, f1, 0.1)) */
    return;
to_wait:
    R(3) = 0; gm_set_u8(self + PL_DEMO_STATE, 0);
    return;
walk:                                                                    /* 1: walk to the target */
    R(3) = self; SETFLAG(0x81803164u, 116);
    R(3) = gm_u32(self + PL_STATE_MGR); R(4) = gm_u8(self + PL_BGC_FLAGS + 3);
    R(5) = gm_u32(R(3)); R(4) &= 1; CR0(ctx, R(4)); R(5) = gm_u32(R(5) + 16);
    if (!R(4)) {
        NV_R(29, STATE_FALL); ctx->ctr = R(5); R(4) = R(29);
        ctx->lr = 0x81803190u; ppc_call_indirect(ctx, base, ctx->ctr);
        if (CMPU(R(3), 0) != 0) goto walk_target;
        R(3) = gm_u32(self + PL_VTABLE); R(4) = R(29); R(5) = 0;
    } else {
        R(4) = STATE_WALK; ctx->ctr = R(5);
        ctx->lr = 0x818031B8u; ppc_call_indirect(ctx, base, ctx->ctr);
        if (CMPU(R(3), 0) != 0) goto walk_target;
        if (pp_isState(GM_PASS, self, 0x818031DCu, STATE_TURN)) goto walk_target;
        R(3) = gm_u32(self + PL_VTABLE); R(4) = STATE_WALK; R(5) = 1;
    }
    R(3) = gm_u32(R(3) + VT_CHANGE_STATE); ctx->ctr = R(3); R(3) = self;
    ctx->lr = 0x81803204u; ppc_call_indirect(ctx, base, ctx->ctr);
walk_target:
    R(3) = gm_u32(self + PL_SUBSTATE_TIMER); LDF(0, self + PL_DEMO_TARGET_X);
    if (CMPU(R(3), 0) != 0) {
        LDF(1, self + PL_POS); LDF(2, self + PL_DEMO_SPEED_F);
        FS(3, F(1) - F(0)); ctx->f[3].u &= ~SIGN;
        FCMP(F(3), F(2));
        if (!FLT) {
            FCMP(F(1), F(0)); R(3) = self + PL_KEY;
            if (FLT) {
                R(4) = 4; BL(0x81803254u, setTransientForcedButtons__14dPlayerInput_cFUi_8005E960);
                R(3) = gm_u32(self + PL_DEMO_SPEED_F);
                gm_set_u32(self + PL_SPEED_F, R(3));
            } else {
                R(4) = 8; BL(0x8180328Cu, setTransientForcedButtons__14dPlayerInput_cFUi_8005E960);
                LDF(0, self + PL_DEMO_SPEED_F); ctx->f[0].u ^= SIGN;
                STF(self + PL_SPEED_F, 0);
            }
            return;
        }
    }
    R(3) = 0; gm_set_u8(self + PL_DEMO_STATE, 0); gm_set_u32(self + PL_SPEED_F, 0);   /* (there, or the timer ran out) */
    STF(self + PL_POS, 0);
    return;
kinopio_turn:
    R(3) = self; R(4) = 0; BL(0x818032A8u, fn_800526C0);
    if (CMPU(R(3), 0) != 0) {
        R(3) = self; R(4) = 1; BL(0x818032BCu, fn_800526C0);
        if (CMPU(R(3), 0) != 0) { GM_LOOP(); goto sink_sand; }          /* (a branch back: it polls) */
    }
    R(3) = gm_u32(self + PL_KINOPIO_TIMER); NV_R(29, gm_u32(self + PL_KINOPIO_DIR));
    if (CMPU(R(3), 0) != 0) { R(3) -= 1; gm_set_u32(self + PL_KINOPIO_TIMER, R(3)); }
    R(3) = self; R(4) = R(29); BL(0x818032E8u, fn_80052650);
    R(4) = gm_u32(self + PL_KINOPIO_DIR);
    if (CMPU(R(3), 0) != 0) goto turn;
    R(3) = gm_u32(self + PL_KINOPIO_TIMER);
    if (CMPU(R(3), 0) == 0) goto turn;
    R(3) = 0x81850000u; LDF(1, 0x81848758u); R(3) = self; R(5) = 1;
    BL(0x81803314u, fn_80052500);                                        /* (isHitGroundKinopioWalk(dir, 4.0, 1)) */
    R(4) = gm_u32(self + PL_KINOPIO_DIR);
    if (CMPU(R(3), 0) != 0) goto go;
    R(3) = 0x81850000u; LDF(1, 0x81848680u); R(3) = self; R(5) = 1;
    BL(0x81803334u, fn_80052500);
    R(4) = gm_u32(self + PL_KINOPIO_DIR);
    if (CMPU(R(3), 0) != 0) goto go;
turn:
    R(4) ^= 1; R(3) = DIR_SPEED; R(5) = R(4) << 2;
    LDF(1, R(3) + R(5)); R(3) = 0x81850000u; LDF(0, self + PL_POS); LDF(2, 0x8184869Cu);
    gm_set_u32(self + PL_KINOPIO_DIR, R(4));
    FS(0, F(1) * F(2) + F(0)); STF(self + PL_DEMO_TARGET_X, 0);
go:
    R(3) = R(4) << 2; R(4) = 0x81850000u; LDF(1, 0x8184869Cu);
    R(4) = DIR_SPEED; LDF(0, self + PL_DEMO_TARGET_X); LDF(2, R(4) + R(3));
    R(3) = self + PL_KEY; LDF(3, self + PL_POS);
    FS(0, F(2) * F(1) + F(0)); FCMP(F(3), F(0));
    if (FLT) {
        R(4) = 4; BL(0x818033A4u, setTransientForcedButtons__14dPlayerInput_cFUi_8005E960);
        LDF(0, self + PL_DEMO_SPEED_F); R(3) = 0;
    } else {
        R(4) = 8; BL(0x818033B8u, setTransientForcedButtons__14dPlayerInput_cFUi_8005E960);
        LDF(0, self + PL_DEMO_SPEED_F); R(3) = 1; ctx->f[0].u ^= SIGN;
    }
    c = CMPU(R(29), R(3));
    STF(self + PL_SPEED_F, 0); gm_set_u32(self + PL_KINOPIO_DIR, R(3));
    if (c != 0) { R(3) = 180; gm_set_u32(self + PL_KINOPIO_TIMER, 180); }
}

/* ================================================================== dAcPy_c */
/* executeState_WallSlide: down a wall - land, wall-jump, ground-pound, let go (holding away for
   15 frames or no wall), else slide */
static void py_executeState_WallSlide(GM_CTX, gptr self) {
    I2_FN(0x8182D5B0u);
    gptr sp = gm_frame_sp;
    NV_R(30, self);
    R(4) = gm_u32(STACK_GUARD); gm_set_u32(sp + 16, R(4));
    R(3) = gm_u8(self + PL_BGC_FLAGS + 3) & 1; CR0(ctx, R(3));
    if (R(3)) { R(3) = gm_u32(self + PL_VTABLE); R(4) = 0x80375C2Cu; goto change; }   /* (StateID_Walk) */
    NV_R(29, self + PL_KEY); R(3) = R(29);
    BL(0x8182D5ECu, fn_8005E6F0);                                        /* (mKey.triggerJump) */
    if (CMPU(R(3), 0) == 0) goto hip;
    R(3) = gm_u32(self + PL_VTABLE); R(4) = 0x803761B0u;                /* (StateID_WallJump) */
change:
    R(3) = gm_u32(R(3) + VT_CHANGE_STATE); ctx->ctr = R(3); R(3) = self; R(5) = 0;
    ctx->lr = 0x8182D624u; ppc_call_indirect(ctx, base, ctx->ctr);
done:
    R(3) = gm_u32(STACK_GUARD); R(4) = gm_u32(sp + 16);
    if (CMPU(R(3), R(4)) != 0) BL(0x8182D73Cu, mfn_81844FCC);
    return;
hip:
    R(3) = self; BL(0x8182D658u, hle_fn_801266B0);                       /* (setHipAttackAction) */
    if (CMPU(R(3), 0) != 0) { GM_LOOP(); goto done; }
    R(4) = sp + 12; R(3) = R(29);
    BL(0x8182D66Cu, fn_8005E7A0);                                        /* (mKey.buttonWalk(&dir)) */
    if (CMPU(R(3), 0) != 0) {
        R(3) = gm_u32(sp + 12); R(4) = gm_u8(self + PL_DIRECTION);
        if (CMPU(R(3), R(4)) != 0) goto away;
    }
    R(3) = 0; gm_set_u32(self + PL_SUBSTATE_VALUE, 0);
check:
    R(4) = gm_u8(self + PL_DIRECTION); R(3) = self;
    BL(0x8182D698u, hle_fn_801284C0);                                        /* (checkWallSlideEnable) */
    if (CMPU(R(3), 0) != 0) { R(3) = gm_u32(self + PL_VTABLE); R(4) = 0x80375CACu; GM_LOOP(); goto change; }   /* (StateID_Fall) */
    R(3) = self; BL(0x8182D6B8u, hle_fn_80056BD0);                          /* (isMameAction) */
    R(3) = CMPU(R(3), 0) != 0 ? 0x81850000u - 30916 : 0x81850000u - 30948;
    R(3) = gm_u32(R(3)); gm_set_u32(self + PL_MAX_SPEED_F, R(3));
    R(3) = self; BL(0x8182D71Cu, hle_fn_80128830);                          /* (setWallSlideEffect) */
    R(3) = gm_u8(self + PL_DIRECTION); R(4) = DIR_SPEED;
    R(3) <<= 2; R(3) = gm_u32(R(4) + R(3)); gm_set_u32(self + PL_SPEED_F, R(3));
    GM_LOOP(); goto done;
away:
    R(3) = gm_u32(self + PL_SUBSTATE_VALUE); R(4) = R(3) + 1;
    int c = CMPS(R(3), 14); gm_set_u32(self + PL_SUBSTATE_VALUE, R(4));
    if (c < 0) { GM_LOOP(); goto check; }
    R(3) = gm_u32(self + PL_VTABLE); R(4) = 0x80375CACu; R(5) = 0;
    R(3) = gm_u32(R(3) + VT_CHANGE_STATE); ctx->ctr = R(3); R(3) = self;
    ctx->lr = 0x8182D700u; ppc_call_indirect(ctx, base, ctx->ctr);
    GM_LOOP(); goto check;
}

/* setSpinLiftUpReserve: lift the actor reserved for a spin lift-up - or, with the liftable-tiles
   rule, the tile underfoot (an AC_BG_CARRY clone, the tile removed) */
static void py_setSpinLiftUpReserve(GM_CTX, gptr self) {
    I2_FN(0x8182D73Cu);
    gptr sp = gm_frame_sp;
    R(4) = 122; NV_R(30, self);
    BL(0x8182D770u, hle_testFlag__10daPlBase_cFi);
    if (CMPU(R(3), 0) != 0) return;
    R(3) = self; BL(0x8182D780u, hle_fn_8004DD00);                          /* (isDemo) */
    if (CMPU(R(3), 0) != 0) return;
    NV_R(26, gm_u32(self + PL_VTABLE));
    VCALL(0x8182D79Cu, self, VT_IS_CARRY, 3);
    if (CMPU(R(3), 0) != 0) return;
    R(3) = self; if (TESTFLAG(0x8182D7B0u, 4)) return;
    R(3) = self; if (TESTFLAG(0x8182D7C4u, 6)) return;
    R(3) = self; if (TESTFLAG(0x8182D7D8u, 8)) return;
    R(3) = gm_u32(self + PL_LIFT_ID);
    BL(0x8182D7E8u, hle_search__7fBase_cFUi);
    if (CMPU(R(3), 0) != 0) {
        NV_R(28, gm_u32(R(3) + PL_VTABLE)); NV_R(29, R(3));
        VCALL(0x8182D808u, R(29), 116, 3);                               /* (isSpinLiftUpEnable) */
        if (CMPU(R(3), 0) != 0) {
            R(3) = gm_u32(R(29)); R(6) = 0; R(4) = gm_u32(self + PL_MODEL); R(5) = gm_u8(R(29) + PL_KIND);
            gm_set_u32(self + PL_CARRY_ID, R(3)); R(3) = gm_u32(R(4) + 380);
            int pl = CMPU(R(5), 1) == 0;
            gm_set_u32(self + PL_LIFT_TIMER, R(6)); R(3) |= 4; gm_set_u32(R(4) + 380, R(3));
            if (pl) {
                R(3) = R(29); BL(0x8182D844u, hle_fn_80056E30);             /* (getModel) */
                R(4) = gm_u32(self + PL_MODEL); gm_set_u32(R(4) + 36, R(3));
            }
            R(3) = gm_u32(R(26) + VT_CHANGE_STATE); R(4) = 0x803760F0u; R(5) = 0;   /* (StateID_LiftUp) */
            ctx->ctr = R(3); R(3) = self; ctx->lr = 0x8182D868u; ppc_call_indirect(ctx, base, ctx->ctr);
            pp_shock(GM_PASS, self, 7, 0x8182D888u);
            R(3) = gm_u32(R(28) + 120); R(4) = self; ctx->ctr = R(3); R(3) = R(29);   /* (setSpinLiftUpActor) */
            ctx->lr = 0x8182D89Cu; ppc_call_indirect(ctx, base, ctx->ctr);
            goto clear;
        }
    }
    R(3) = gm_u8(GAME_RULE + 9);                                         /* (liftable tiles) */
    if (CMPU(R(3), 1) != 0) goto clear;
    R(3) = gm_u8(self + PL_ATTACK);
    if (CMPU(R(3), 0x12) != 0) goto clear;
    R(3) = self + PL_KEY; BL(0x8182D8C8u, hle_mod_fn_8005E5D0);   /* (mKey.buttonOne) */
    if (CMPU(R(3), 0) == 0) goto clear;
    R(3) = gm_u32(R(26) + 244); ctx->ctr = R(3); R(3) = self;           /* (getFootBgPointData) */
    ctx->lr = 0x8182D8E0u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = gm_u32(R(3) + 8); R(4) = 0x43300000u; gm_set_u32(sp + 16, R(4));
    R(4) = 0x81850000u; R(3) ^= 0x80000000u; gm_set_u32(sp + 20, R(3));
    NV_R(27, self); LDF(0, 0x818486C0u); R(3) = 0x81850000u;
    ctx->f[1].u = ld64(base, sp + 16); NV_R(25, 0x80430000u);
    { uint32_t ea = R(27) + PL_POS; LDF(2, ea); NV_R(27, ea); }
    R(7) = 0; LDF(3, 0x8184875Cu);
    ctx->f[0].d = F(1) - F(0);                                            /* (fsub, fmul: double, ps0) */
    ctx->f[1].u = fctiw_bits(F(2), 1); st64(base, sp + 8, ctx->f[1].u);
    ctx->f[0].d = F(0) * F(3);
    LDF(1, R(27) + 4); ctx->f[0].d = frsp(F(0));
    R(3) = gm_u32(sp + 12); R(8) = 0;
    FS(0, F(1) + F(0)); ctx->f[0].u ^= SIGN;
    ctx->f[0].u = fctiw_bits(F(0), 1); st64(base, sp + 24, ctx->f[0].u);
    NV_R(29, R(3) & 0xFFF0); R(4) = gm_u32(sp + 28); NV_R(24, 0);
    R(3) = gm_u32(R(25) - 25136); R(6) = gm_u8(R(27) + 739);            /* (dBg_c::m_bg_p, mLayer) */
    NV_R(28, R(4) & 0xFFF0); R(4) = R(29); R(5) = R(28);
    BL(0x8182D96Cu, hle_getPointerToTile__8BgGmBaseFiiiPib);
    R(4) = gm_u16(R(3));
    if (CMPU(R(4), 0) == 0) goto clear;
    R(3) = 756; R(5) = R(27); R(6) = 0; R(7) = 0;                        /* (construct AC_BG_CARRY) */
    BL(0x8182D98Cu, hle_create__13dStageActor_cF6ActorsUiP7Point3dP6S16VecUc);
    NV_R(27, R(3)); R(3) = gm_u32(self + PL_MODEL); R(4) = gm_u32(R(27)); R(5) = gm_u32(R(3) + 380);
    gm_set_u32(self + PL_CARRY_ID, R(4)); R(4) = R(5) | 4; gm_set_u32(self + PL_LIFT_TIMER, R(24));
    R(5) = 0; gm_set_u32(R(3) + 380, R(4));
    R(4) = 0x803760F0u; R(3) = gm_u32(R(26) + VT_CHANGE_STATE); ctx->ctr = R(3); R(3) = self;
    ctx->lr = 0x8182D9C8u; ppc_call_indirect(ctx, base, ctx->ctr);
    pp_shock(GM_PASS, self, 7, 0x8182D9E8u);
    R(3) = gm_u32(R(27) + PL_VTABLE); R(4) = self; R(3) = gm_u32(R(3) + 120); ctx->ctr = R(3); R(3) = R(27);
    ctx->lr = 0x8182DA00u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = gm_u32(R(25) - 25136); R(4) = R(29); R(6) = gm_u8(self + PL_LAYER); R(5) = R(28); R(7) = 0;
    BL(0x8182DA18u, hle_placeTile__8BgGmBaseFUsUsii);
clear:
    R(3) = self; BL(0x8182DA20u, hle_fn_8012E120);                          /* (clearSpinLiftUpReserve) */
}

/* updateRopeAngle: the rope / pole controller's angle for this player; 1 when on one */
static void py_updateRopeAngle(GM_CTX, gptr self) {
    I2_FN(0x8182DA4Cu);
    NV_R(30, self);
    R(3) = gm_u16(self + PL_ROPE_ANGLE + 4); gm_set_u16(self + PL_ROPE_ANGLE + 6, (uint16_t)R(3));
    R(3) = self + PL_PC + 4; BL(0x8182DA70u, hle_getAngle__5dPc_cCFv);
    R(4) = gm_u32(self + PL_PC + 16); R(5) = gm_u16(self + PL_ROPE_ANGLE);
    gm_set_u16(self + PL_ROPE_ANGLE + 4, (uint16_t)R(3));
    int c = CMPU(R(4), 0); R(3) = 0;
    gm_set_u16(self + PL_ROPE_ANGLE + 2, (uint16_t)R(5));
    if (c == 0) return;
    R(5) = gm_u8(R(4) + 32); R(5) = (R(5) - 1) & 0xFF;
    if (CMPU(R(5), 1) > 0) return;
    R(3) = gm_u32(R(4) + 52);
    if (CMPU(R(3), 0) != 0) {
        R(4) = (uint32_t)(int8_t)gm_u8(self + PL_PLR_NO); R(4) <<= 1;
        R(3) = gm_u16(R(3) + R(4));
    } else R(3) = 0;
    gm_set_u16(self + PL_ROPE_ANGLE, (uint16_t)R(3));
    R(3) = 1;
}

/* setBalloonInDispOutBase(type, yoshi, noDeathMsg): out of the screen - into a bubble (a player
   carried along goes too), the death message */
static void py_setBalloonInDispOutBase(GM_CTX, gptr self, uint32_t type, uint32_t yoshi, uint32_t no_msg) {
    I2_FN(0x8182DB08u);
    gptr sp = gm_frame_sp;
    R(12) = ctx->cr; gm_set_u32(sp + 16, R(12));                         /* (mfcr: CR2 is kept) */
    NV_R(25, type); NV_R(27, yoshi); NV_R(29, no_msg); NV_R(30, self);
    BL(0x8182DB48u, hle_fn_80050D80);                                        /* (isDispOutCheckOn) */
    int c = CMPU(R(3), 0); NV_R(26, 0);
    if (c == 0) goto end;
    R(3) = R(25) & 0xFFFFFFFDu; CR0(ctx, R(3)); CR_SET(ctx, 2, (ctx->cr >> 28) & 0xF);   /* (cr2.eq: type 0 or 2) */
    if (R(3)) {
        VCALL(0x8182DB74u, self, VT_IS_ITEM_KINOPIO, 3);
        if (CMPU(R(3), 0) == 0) goto carry;
        R(3) = 0x80430000u; R(3) = gm_u32(BG_P); R(4) = 0x900C6u;
        R(3) = gm_u8(R(3) + R(4));                                       /* (isAutoscroll) */
        if (CMPU(R(3), 1) == 0) goto carry;
        goto end;
    }
    R(3) = self; BL(0x8182DBA4u, hle_fn_8004DDE0);                          /* (isDemoAll) */
    if (CMPU(R(3), 0) != 0) { R(3) = self; if (!TESTFLAG(0x8182DBB8u, 90)) goto end; }
    R(3) = self; if (TESTFLAG(0x8182DBCCu, 184)) goto end;
carry:
    R(3) = self; BL(0x8182DBDCu, hle_fn_8012DBE0);                          /* (getCarryPlayer) */
    if (CMPU(R(3), 0) != 0) {
        R(4) = R(25); R(5) = 0; R(6) = 1; NV_R(28, R(3));
        BL(0x8182DBF8u, hle_mod_fn_80139210);
        if (CMPU(R(3), 0) != 0) goto carried;
    }
    NV_R(28, 0);
carried:
    if (CMPU(R(27), 0) != 0) { R(3) = self; SETFLAG(0x8182DC18u, 184); }
    R(3) = self;
    if (TESTFLAG(0x8182DC24u, 185)) { R(3) = self; BL(0x8182DC34u, hle_mfn_8182DD3C); }   /* (setFallDownDemoNoMsg) */
    else {
        R(3) = gm_u32(self + PL_VTABLE); R(4) = 11; R(5) = 0;
        R(3) = gm_u32(R(3) + VT_SET_PRESS_BG_DMG); ctx->ctr = R(3); R(3) = self;
        ctx->lr = 0x8182DC54u; ppc_call_indirect(ctx, base, ctx->ctr);
    }
    R(5) = 20;                                                           /* (DamageType_e::FALL_DOWN) */
    if (CR_BIT(ctx, 10)) {
        R(3) = gm_u32(self + PL_VTABLE); R(4) = 44; R(5) = 0;
        R(3) = gm_u32(R(3) + VT_PLAY_VOICE); ctx->ctr = R(3); R(3) = self;
        ctx->lr = 0x8182DC78u; ppc_call_indirect(ctx, base, ctx->ctr);
        pp_shock(GM_PASS, self, 4, 0x8182DC98u);
        R(5) = 21;                                                       /* (SCROLL_OUT) */
    }
    R(3) = gm_u8(GAME_RULE + 8); NV_R(26, 1);                            /* (death messages) */
    if (CMPU(R(3), 0) == 0) goto end;
    if (CMPU(R(29), 0) != 0) goto end;
    if (CMPU(R(28), 0) != 0) { R(3) = R(28); R(4) = self; }
    else { R(3) = self; R(4) = 0; }
    R(6) = 1; BL(0x8182DCE0u, mfn_818033F4);                            /* (addDeathMessage) */
end:
    R(12) = gm_u32(sp + 16); R(3) = R(26);
    ctx->cr = (ctx->cr & ~0xF00000u) | (R(12) & 0xF00000u);             /* (mtcrf: CR2 back) */
}
/* setBalloonInDispOutByYoshi(type) / setBalloonInDispOut(type) */
static void py_setBalloonInDispOut(GM_CTX, uint32_t fn, uint32_t yoshi, uint32_t ra) {
    I2_FN(fn); /* FNADDR 0x8182DAE0u 0x8182DD14u */
    R(5) = yoshi; R(6) = 0;
    BL(ra, hle_mod_fn_80139210);
}

/* checkRest: out of lives - an item Toad goes; with someone left the bubble, else the world map /
   game over */
static void py_checkRest(GM_CTX, gptr self) {
    I2_FN(0x8182DDA4u);
    NV_R(30, self);
    VCALL(0x8182DDCCu, self, VT_IS_ITEM_KINOPIO, 3);
    if (CMPU(R(3), 0) != 0) { R(3) = self; BL(0x8182DDDCu, hle_Delete__7fBase_cFv); return; }
    R(3) = gm_u32(self + PL_REST_FLAG);
    if (CMPU(R(3), 0) == 0) { R(3) = self; BL(0x8182DE70u, hle_fn_80138E60); return; }   /* (setBalloonInDamage) */
    R(3) = self; if (TESTFLAG(0x8182DDF8u, 5)) return;
    R(3) = self; SETFLAG(0x8182DE0Cu, 5);
    R(3) = 8; ctx->ctr = 8; R(6) = 0x81850000u;
    R(5) = PY_TYPE - 4; R(3) = PY_ENTRY - 4; R(4) = PY_REST;
    for (;;) {
        uint32_t ea = R(3) + 4; R(6) = gm_u32(ea); R(3) = ea;
        int c = CMPU(R(6), 0); R(6) = R(5) + 4;
        if (c != 0) {
            R(5) = gm_u32(R(5) + 4) << 2; R(5) = gm_u32(R(4) + R(5));
            if (CMPU(R(5), 0) != 0) { R(3) = 3; goto scene; }            /* (dProf::WORLD_MAP) */
        }
        R(5) = R(6);
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    R(3) = 9;                                                            /* (dProf::GAMEOVER) */
scene:
    R(4) = 0; R(5) = 1; R(6) = 2;
    BL(0x8182DE88u, hle_mod_setNextScene__10dScStage_cFUsiQ210dScStage_c6Exit_eQ28dFader_c12fader_type_e);
}

/* stopOtherDownDemo: everyone else stops while this player dies (the owner of the demo) */
static void py_stopOtherDownDemo(GM_CTX, gptr self) {
    I2_FN(0x8182DE9Cu);
    NV_R(30, self);
    VCALL(0x8182DECCu, self, VT_IS_ITEM_KINOPIO, 3);
    if (CMPU(R(3), 0) != 0) return;
    R(3) = gm_u32(self + PL_REST_FLAG);
    if (CMPU(R(3), 0) == 0) {
        if (!pp_gameStopAllowed(GM_PASS, 3, 0x8182DFC4u, 0x8182DFD0u)) return;
        R(3) = R(30); BL(0x8182DFE0u, hle_continueFromMpPauseFix1);   /* (stopOther) */
        return;
    }
    R(3) = gm_u8(self + PL_PLR_NO); R(5) = 0x80430000u; R(4) = gm_u32(DEMO_MNG_P);
    R(3) = (uint32_t)(int8_t)R(3); R(6) = gm_u8(EXEC_STOP_REQ); NV_R(28, 8);
    gm_set_u32(R(4) + 132, R(3)); NV_R(30, 0);                           /* (mOwnedPlayer) */
    R(3) = R(6) | 0xF; gm_set_u8(EXEC_STOP_REQ, (uint8_t)R(3));
    for (uint32_t p = 0;; ) {
        R(3) = p; BL(0x8182DF14u, hle_getPlayer__9daPyMng_cFi);
        if (CMPU(R(3), 0) != 0) {
            R(4) = 83; NV_R(29, R(3));
            BL(0x8182DF28u, hle_testFlag__10daPlBase_cFi);
            if (CMPU(R(3), 0) == 0) {
                VCALL(0x8182DF44u, R(29), VT_IS_ITEM_KINOPIO, 3);
                if (CMPU(R(3), 0) == 0) {
                    R(3) = gm_u8(R(29) + PL_EXEC_STOP_MASK) & 0xFD; CR0(ctx, R(3));
                    gm_set_u8(R(29) + PL_EXEC_STOP_MASK, (uint8_t)R(3));
                }
            }
        }
        R(3) = p; BL(0x8182DF60u, hle_mod_getYoshi__9daPyMng_cFi);
        if (CMPU(R(3), 0) != 0) {
            R(4) = 83; NV_R(29, R(3));
            BL(0x8182DF74u, hle_testFlag__10daPlBase_cFi);
            if (CMPU(R(3), 0) == 0) {
                R(3) = gm_u8(R(29) + PL_EXEC_STOP_MASK) & 0xFD; CR0(ctx, R(3));
                gm_set_u8(R(29) + PL_EXEC_STOP_MASK, (uint8_t)R(3));
            }
        }
        NV_R(28, R(28) - 1);
        int more = CMPU(R(28), 0) > 0;
        NV_R(30, ++p);
        if (!more) break;
        GM_LOOP();
    }
    R(3) = 0x80430000u; R(4) = gm_u8(EXEC_STOP_REQ) | 0xD; gm_set_u8(EXEC_STOP_REQ, (uint8_t)R(4));
}

/* playOtherDownDemo: the others resume when nobody owns the down demo */
static void py_playOtherDownDemo(GM_CTX, gptr self) {
    I2_FN(0x8182DFFCu);
    NV_R(30, self);
    if (!pp_gameStopAllowed(GM_PASS, 4, 0x8182E028u, 0x8182E034u)) return;
    VCALL(0x8182E050u, self, VT_IS_ITEM_KINOPIO, 3);
    if (CMPU(R(3), 0) != 0) return;
    R(3) = 0x80430000u; R(3) = gm_u32(DEMO_MNG_P); R(3) = gm_u32(R(3) + 132);
    if (CMPS(R(3), -1) != 0) return;
    R(3) = gm_u32(self + PL_REST_FLAG);
    if (CMPU(R(3), 0) != 0) return;
    R(3) = self; BL(0x8182E080u, hle_fn_8004E100);                          /* (playOther) */
}

/* setFallDownDemo: the death message, then down */
static void py_setFallDownDemo(GM_CTX, gptr self) {
    I2_FN(0x8182E094u);
    NV_R(30, self);
    BL(0x8182E0ACu, hle_fn_80050D80);
    if (CMPU(R(3), 0) == 0) return;
    R(3) = gm_u8(GAME_RULE + 8);
    if (CMPU(R(3), 0) != 0) { R(3) = self; R(4) = 0; R(5) = 20; R(6) = 1; BL(0x8182E0DCu, mfn_818033F4); }
    R(3) = self; BL(0x8182E0E4u, hle_mfn_8182DD3C);
}

/* executeDemoGoal_Run: after the pole - the wait by place (the module: the last of four or more
   may jump the queue at random), run, land, the castle */
static void py_executeDemoGoal_Run(GM_CTX, gptr self) {
    I2_FN(0x8182E0F8u);
    gptr sp = gm_frame_sp;
    NV_R(31, self);
    R(0) = gm_u8(self + PL_DEMO_STATE); R(4) = (uint32_t)(int8_t)R(0); R(0) = R(4) - 1;
    if (CMPU(R(0), 1) <= 0) goto wait;
    if (CMPS(R(4), 0) == 0) goto start;
    if (CMPS(R(4), 3) == 0) goto run;
    if (CMPS(R(4), 4) == 0) goto ground;
    if (CMPS(R(4), 6) == 0) goto jump;
    if (CMPS(R(4), 7) == 0) goto land;
    return;
start:
    R(9) = 0x80430000u; R(9) = gm_u32(DEMO_MNG_P); R(9) = gm_u32(R(9) + 28);   /* (the goal count) */
    if (CMPS(R(9), 4) >= 0) {
        R(9) -= 1; R(0) = gm_u32(self + PL_GOAL_ORDER);
        if (CMPS(R(0), R(9)) == 0) {
            BL(0x8182E178u, rnd__8dGameComFv_800B2F00);
            LDF(0, R(13) - 7964); FCMP(F(1), F(0));
            if (FLT) { R(3) = 60; R(0) = 2; gm_set_u32(self + PL_SUBSTATE_TIMER, 60); gm_set_u8(self + PL_DEMO_STATE, 2); goto yoshis; }
        }
    }
    R(3) = gm_u32(self + PL_GOAL_ORDER); R(0) = 1; gm_set_u8(self + PL_DEMO_STATE, 1);
    R(0) = R(3) << 2; R(3) = R(0) + R(3); R(0) = R(3) + 10;
    gm_set_u32(self + PL_SUBSTATE_TIMER, R(0));                          /* (5 frames a place, + 10) */
yoshis:
    NV_R(30, 0);
    for (;;) {
        R(3) = R(30); BL(0x8182E1C0u, hle_mod_getYoshi__9daPyMng_cFi);
        if (CMPS(R(3), 0) != 0) {
            R(4) = 101; BL(0x8182E1D0u, hle_testFlag__10daPlBase_cFi);
            if (CMPS(R(3), 0) != 0) {
                R(3) = gm_u32(self + PL_SUBSTATE_TIMER); R(0) = R(3) + 14; gm_set_u32(self + PL_SUBSTATE_TIMER, R(0));
                goto wait;
            }
        }
        NV_R(30, R(30) + 1);
        if (CMPS(R(30), 4) >= 0) break;
        GM_LOOP();
    }
wait:
    R(0) = gm_u32(self + PL_SUBSTATE_TIMER);
    if (CMPS(R(0), 0) != 0) return;
    R(3) = gm_u32(R(13) - 23020); R(0) = gm_u32(R(3) + 16) | 0x20; gm_set_u32(R(3) + 16, R(0));
    R(0) = gm_u32(self + PL_GOAL_ORDER);
    if (CMPS(R(0), 0) == 0) {
        R(3) = gm_u32(R(13) - 23020); R(4) = 2; R(5) = 0;
        BL(0x8182E22Cu, setDemoMode__13daPyDemoMng_cFQ213daPyDemoMng_c6Mode_ei_8005B5C0);
    }
    R(0) = gm_u32(self + PL_MODE); R(4) = 0; LDF(2, R(13) - 7976); R(3) = 60; LDF(0, R(13) - 7408);
    int mini = CMPS(R(0), 3) == 0;
    gm_set_u8(self + PL_DIRECTION, 0); LDF(1, R(13) - 7404);
    STF(self + PL_SPEED, 2); STF(self + PL_SPEED + 4, 2); STF(self + PL_SPEED + 8, 2);
    gm_set_u32(self + PL_SUBSTATE_TIMER, 60); STF(self + PL_SPEED_F, 0);
    if (mini) { LDF(0, R(13) - 7960); FS(1, F(0) * F(1)); }
    else {
        R(0) = gm_u8(self + PL_DEMO_STATE);
        if (CMPS(R(0), 2) == 0) { LDF(0, R(13) - 7884); STF(self + PL_SPEED_F, 0); LDF(1, R(13) - 7940); }
    }
    R(3) = gm_u32(self + PL_MODEL); R(4) = 2; LDF(2, R(13) - 7784);
    R(12) = gm_u32(R(3)); LDF(3, R(13) - 7976); R(12) = gm_u32(R(12) + 92); ctx->ctr = R(12);
    ctx->lr = 0x8182E2A8u; ppc_call_indirect(ctx, base, ctx->ctr);     /* (setAnm: run) */
    R(0) = 3; gm_set_u8(self + PL_DEMO_STATE, 3);
    return;
run:
    R(12) = gm_u32(self + PL_VTABLE); R(12) = gm_u32(R(12) + 1096); ctx->ctr = R(12);
    ctx->lr = 0x8182E2C4u; ppc_call_indirect(ctx, base, ctx->ctr);
    LDF(1, self + PL_POS); LDF(0, self + PL_GOTO_POS); FCMP(F(1), F(0));
    if (FGT) {
        R(3) = self + PL_POS; R(4) = sp + 8; R(5) = 0; R(6) = 1; R(7) = (uint32_t)-1;
        BL(0x8182E2ECu, checkGround__5dBc_cFPC7mVec3_cPfUcUcSc_800757B0);
        if (CMPS(R(3), 0) != 0) {
            LDF(1, R(13) - 7932); LDF(0, sp + 8); LDF(2, self + PL_POS + 4);
            FS(0, F(1) + F(0)); FCMP(F(2), F(0));
            if (FLT) STF(self + PL_POS + 4, 0);
        }
        LDF(0, R(13) - 7400); STF(self + PL_POS + 8, 0);
    }
    LDF(1, R(13) - 7520); R(3) = self + PL_POS; LDF(0, self + PL_GOTO_POS); LDF(2, self + PL_SPEED_F);
    FS(1, F(1) + F(0));
    BL(0x8182E330u, fn_8015F470);                                        /* (sLib::chase(&mPos.x, ...)) */
    if (CMPS(R(3), 0) == 0) return;
    R(3) = gm_u32(self + PL_MODEL); R(5) = PROPEL_HIO; LDF(3, R(13) - 7976);
    R(12) = gm_u32(R(3)); R(4) = 0; LDF(1, R(5) + 44); R(12) = gm_u32(R(12) + 92); LDF(2, R(5) + 48);
    ctx->ctr = R(12); ctx->lr = 0x8182E364u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(0) = 4; gm_set_u8(self + PL_DEMO_STATE, 4);
    R(3) = self; SETFLAG(0x8182E378u, 110);
    return;
ground:
    LDF(0, R(13) - 7400); STF(self + PL_POS + 8, 0);
    return;
jump:
    BL(0x8182E38Cu, hle_fn_8004C620);
    LDF(2, self + PL_SPEED + 4); LDF(1, self + PL_ACCEL_Y); LDF(0, R(13) - 15900);
    FS(1, F(2) + F(1)); STF(self + PL_SPEED + 4, 1);
    FCMP(F(1), F(0));
    if (FLT) STF(self + PL_SPEED + 4, 0);
    LDF(3, self + PL_POS + 4); LDF(2, self + PL_SPEED + 4); R(0) = gm_u32(self + PL_BGC_FLAGS);
    FS(2, F(3) + F(2)); LDF(1, self + PL_POS); LDF(0, self + PL_SPEED_F);
    R(0) &= 1; CR0(ctx, R(0));
    STF(self + PL_POS + 4, 2); FS(0, F(1) + F(0)); STF(self + PL_POS, 0);
    if (!R(0)) return;
    LDF(3, R(13) - 7976); STF(self + PL_SPEED_F, 3);
    R(5) = PROPEL_HIO; R(3) = gm_u32(self + PL_MODEL); R(4) = 7;
    LDF(1, R(5) + 128); R(12) = gm_u32(R(3)); LDF(2, R(5) + 132); R(12) = gm_u32(R(12) + 92);
    ctx->ctr = R(12); ctx->lr = 0x8182E408u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(12) = gm_u32(self + PL_VTABLE); R(3) = self; R(12) = gm_u32(R(12) + 1044); ctx->ctr = R(12);
    ctx->lr = 0x8182E41Cu; ppc_call_indirect(ctx, base, ctx->ctr);
    R(0) = 7; gm_set_u8(self + PL_DEMO_STATE, 7);
    return;
land:
    R(3) = gm_u32(self + PL_MODEL); R(3) += 40;
    BL(0x8182E434u, hle_isAnimationDone__Q23m3d6fanm_cFv);
    if (CMPS(R(3), 0) == 0) return;
    R(3) = gm_u32(self + PL_MODEL); R(5) = PROPEL_HIO; LDF(3, R(13) - 7976);
    R(12) = gm_u32(R(3)); R(4) = 0; LDF(1, R(5) + 44); R(12) = gm_u32(R(12) + 92); LDF(2, R(5) + 48);
    ctx->ctr = R(12); ctx->lr = 0x8182E468u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = gm_u32(self + PL_GOAL_ORDER); R(0) = 1; gm_set_u8(self + PL_DEMO_STATE, 1);
    R(0) = R(3) << 2; R(0) += R(3); gm_set_u32(self + PL_SUBSTATE_TIMER, R(0));
}

/* initChangeInit / executeChangeInit: a power-up change stops the others (unless a goal demo) */
static void py_initChangeInit(GM_CTX, gptr self) {
    I2_FN(0x8182E498u);
    NV_R(30, self);
    if (!pp_gameStopAllowed(GM_PASS, 4, 0x8182E4C4u, 0x8182E4D0u)) return;
    R(3) = self;
    if (TESTFLAG(0x8182E4E4u, 101)) { R(3) = self; BL(0x8182E4F4u, PLAY_GOAL_OTHER); }
    else { R(3) = self; BL(0x8182E500u, hle_fn_8004E100); }
    R(3) = (uint32_t)(int8_t)gm_u8(self + PL_PLR_NO);
    BL(0x8182E50Cu, pauseOffMove__6dAudioFi_8006A7F0);
}
static void py_executeChangeInit(GM_CTX, gptr self) {
    I2_FN(0x8182E520u);
    R(5) = gm_u32(self + PL_MODE); R(4) = gm_u32(self + PL_NEXT_MODE); NV_R(30, self);
    int same = CMPU(R(5), R(4)) == 0; R(3) = 0;
    if (same) return;
    VCALL(0x8182E55Cu, self, VT_SET_POWERUP, 3);
    if (pp_gameStopAllowed(GM_PASS, 3, 0x8182E574u, 0x8182E580u)) {
        R(3) = self; BL(0x8182E590u, hle_continueFromMpPauseFix1);
        R(3) = (uint32_t)(int8_t)gm_u8(self + PL_PLR_NO);
        BL(0x8182E59Cu, pauseMove__6dAudioFi_8006A7D0);
    }
    R(3) = self; R(4) = 1; BL(0x8182E5A8u, hle_continueFromMpPauseFix2);   /* (setChange) */
    R(3) = gm_u32(self + PL_MODE);
    if (CMPU(R(3), 3) == 0) {                                            /* (mini: the jump speed caps the rise) */
        R(3) = self; BL(0x8182E5BCu, hle_fn_80127470);
        LDF(0, self + PL_SPEED + 4); FCMP(F(1), F(0));
        if (FLT) STF(self + PL_SPEED + 4, 1);
        R(3) = self; BL(0x8182E5D4u, hle_fn_8012E5A0);                      /* (releaseCarryActor) */
    }
    R(3) = self; BL(0x8182E5DCu, hle_fn_8004E040);                          /* (isPlayerGameStop) */
}

/* setSceneChangeInfo: what the player takes into the next scene (power-up, bubble / Yoshi, star) */
static void py_setSceneChangeInfo(GM_CTX, gptr self) {
    I2_FN(0x8182E5F0u);
    NV_R(30, self);
    VCALL(0x8182E624u, self, VT_IS_ITEM_KINOPIO, 3);
    R(4) = 0x80430000u; int kinopio = CMPU(R(3), 0) != 0; R(3) = gm_u32(EXIT_MODE);
    if (kinopio) {
        R(3) -= 3;
        if (CMPU(R(3), 1) > 0) return;
        R(3) = (uint32_t)(int8_t)gm_u8(self + PL_PLR_NO);
        BL(0x8182E64Cu, getCtrlPlayer__9daPyMng_cFi_8005FB90);
        if (CMPU(R(3), 0) == 0) return;
        if (TESTFLAG(0x8182E65Cu, 101)) return;
        R(3) = self; if (TESTFLAG(0x8182E670u, 4)) return;
        R(3) = self; if (TESTFLAG(0x8182E684u, 6)) return;
        R(4) = gm_u8(self + PL_PLR_NO); R(3) = gm_u32(self + PL_MODE); R(4) = (uint32_t)(int8_t)R(4);
        BL(0x8182E69Cu, hle_mod_fn_8005f570__9daPyMng_cF16PLAYER_POWERUP_ei);   /* (initKinopioPlayer) */
        return;
    }
    NV_R(27, gm_u32(self + PL_MODE)); R(4) = R(3) - 3;
    if (CMPU(R(4), 2) < 0) goto carry_over;
    if (CMPU(R(3), 1) == 0) { NV_R(27, 0); NV_R(28, 0); goto store; }   /* (DOWN) */
    int restore = CMPU(R(3), 2) == 0; NV_R(28, 0);
    if (!restore) goto store;
    R(3) = (uint32_t)(int8_t)gm_u8(self + PL_PLR_NO); R(5) = 0x81860000u;   /* (RESTORE_INFO) */
    R(3) <<= 2; R(3) = gm_u32(PY_TYPE + R(3)); R(4) = PY_MODE;
    R(3) <<= 2; NV_R(27, gm_u32(R(4) + R(3)));
    R(4) = R(5) - 5764; NV_R(28, gm_u32(R(4) + R(3)));
    goto store;
carry_over:
    R(3) = self;
    if (TESTFLAG(0x8182E708u, 85)) {
        R(3) = self; BL(0x8182E718u, hle_fn_80138750);                      /* (isNotBalloonCourse) */
        int c = CMPU(R(3), 0); NV_R(28, 0);
        if (c == 0) goto yoshi;
    }
    R(3) = self; R(4) = 83; BL(0x8182E730u, hle_testFlag__10daPlBase_cFi);
    { int c = CMPU(R(3), 0); NV_R(28, 4);
      if (c == 0) {
          R(3) = self; R(4) = 4; BL(0x8182E748u, hle_testFlag__10daPlBase_cFi);
          c = CMPU(R(3), 0); R(4) = 0;
          if (c == 0) R(4) = R(27);
          NV_R(28, R(3) << 2); NV_R(27, R(4));
      } }
yoshi:
    R(3) = self; BL(0x8182E768u, hle_getYoshi__7dAcPy_cFv);
    if (CMPU(R(3), 0) == 0) goto store;
    NV_R(29, R(3)); NV_R(28, gm_u8(self + PL_PLR_NO));
    BL(0x8182E77Cu, hle_fn_80056E30);
    R(5) = gm_u32(R(29) + 5476); R(4) = gm_u32(R(3) + 588); R(3) = R(28);
    BL(0x8182E78Cu, hle_mod_setCarryOverYoshiInfo__9daPyMng_cFUcUci);
    R(3) = self; SETFLAG(0x8182E798u, 197);
    NV_R(28, 2);
store:
    R(3) = gm_u8(self + PL_PLR_NO); R(5) = 1; R(4) = PY_ENTRY;
    R(3) = (uint32_t)(int8_t)R(3); R(6) = R(3) << 2;
    gm_set_u32(R(4) + R(6), R(5));
    R(4) = gm_u32(self + PL_STAR_TIME); R(5) = PY_STAR_TIME;
    R(3) <<= 1; R(7) = gm_u8(self + PL_STAR_COUNT);
    gm_set_u16(R(5) + R(3), (uint16_t)R(4));
    R(4) = gm_u32(PY_TYPE + R(6)); R(6) = 0x81860000u; R(5) = PY_MODE; R(4) <<= 2;
    gm_set_u32(R(5) + R(4), R(27));
    R(6) = PY_CREATE_ITEM; R(5) = PY_STAR_COUNT;
    gm_set_u32(R(6) + R(4), R(28));
    R(4) = (uint32_t)(int8_t)R(7); gm_set_u16(R(5) + R(3), (uint16_t)R(4));
}

/* create: the player's model, power-up, physics and the carried-over state */
static void py_create(GM_CTX, gptr self) {
    I2_FN(0x8182E834u);
    R(6) = 0; NV_R(31, self);
    R(0) = gm_u32(self + PL_MODE); R(4) = gm_u8(self + PL_PLR_NO); R(3) = self + PL_PY_MDL_MNG; R(5) = R(0) & 0xFF;
    BL(0x8182E860u, create__11dPyMdlMng_cFUcUcQ211dPyMdlMng_c11SceneType_e_800D6DF0);
    R(4) = gm_u32(self + PL_MODE); R(3) = self;
    gm_set_u32(self + PL_NEXT_MODE, R(4)); R(5) = 1; gm_set_u32(self + PL_NEXT_MODE - 4, R(4));
    VCALL(0x8182E884u, self, VT_SET_POWERUP, 12);
    R(0) = gm_u32(self + 4); R(3) = self; R(4) = i2_rotl(R(0), 8) & 1;
    gm_set_u8(self + PL_DIRECTION, (uint8_t)R(4));
    VCALL(0x8182E8A4u, self, 1092, 12);
    LDF(1, R(13) - 7976); LDF(0, R(13) - 15900);
    gm_set_u16(self + PL_ANGLE_Y, (uint16_t)R(3)); R(3) = self;
    STF(self + PL_MAX_FALL_SPEED, 1); STF(self + PL_MAX_FALL_SPEED + 4, 1); STF(self + PL_MAX_FALL_SPEED + 8, 1);
    STF(self + PL_MAX_SPEED_F, 0);
    VCALL(0x8182E8D4u, self, 964, 12);
    LDF(1, R(3)); R(3) = self; LDF(0, R(13) - 7932); R(4) = 0;
    STF(self + PL_ACCEL_Y, 1); STF(self + 220, 0); STF(self + 224, 0); STF(self + 228, 0); STF(self + 5444, 0);
    BL(0x8182E8FCu, hle_fn_80056C30);
    R(0) = 0; gm_set_u32(self + PL_CARRY_ID, 0); R(3) = self;
    gm_set_u32(self + 4104, 0); gm_set_u32(self + 4108, 0);
    VCALL(0x8182E920u, self, VT_IS_ITEM_KINOPIO, 12);
    if (CMPS(R(3), 0) != 0) { R(3) = self; R(4) = 1; BL(0x8182E934u, hle_fn_80147250); }
    else { R(3) = self; R(4) = 0; BL(0x8182E944u, hle_fn_80147250); }
    LDF(2, self + PL_POS); R(4) = self; LDF(1, self + PL_POS + 4); R(3) = self + PL_PROPEL_PARTS; LDF(0, self + PL_POS + 8);
    STF(self + 5420, 2); STF(self + 5424, 1); STF(self + 5428, 0);
    BL(0x8182E968u, hle_create__14dPropelParts_cFP8dActor_c);
    R(3) = self; BL(0x8182E970u, hle_fn_801434C0);
    R(3) = self; BL(0x8182E978u, hle_fn_801434E0);
    R(12) = gm_u32(self + PL_VTABLE); R(3) = self; R(0) = gm_u32(self + 4);
    R(12) = gm_u32(R(12) + 624); R(4) = i2_rotl(R(0), 16) & 0xFF; ctx->ctr = R(12);
    ctx->lr = 0x8182E994u; ppc_call_indirect(ctx, base, ctx->ctr);
    R(3) = self; BL(0x8182E99Cu, hle_fn_80145650);
    R(4) = self; R(3) = self + PL_PC; R(5) = 1;
    BL(0x8182E9ACu, hle_set__5dPc_cFP8dActor_cUc);
    R(0) = gm_u32(R(13) - 21600);
    if (CMPS(R(0), 0) == 0) {
        R(3) = gm_u32(R(13) - 21688); R(0) = gm_u8(R(3) + 4621);
        if (CMPU(R(0), 0x28) != 0) {
            R(0) = gm_u8(self + PL_PLR_NO); R(5) = (uint32_t)(int8_t)R(0);
            R(4) = PY_TYPE; R(0) = R(5) << 2; R(3) = PY_CREATE_ITEM;
            R(0) = gm_u32(R(4) + R(0)); R(0) <<= 2; R(0) = gm_u32(R(3) + R(0));
            R(0) &= 1; CR0(ctx, R(0));
            if (R(0)) {                                                  /* (created in a bubble) */
                R(12) = gm_u32(self + PL_VTABLE); R(3) = self; R(4) = 2; R(5) = 660;
                R(12) = gm_u32(R(12) + 984); ctx->ctr = R(12);
                ctx->lr = 0x8182EA14u; ppc_call_indirect(ctx, base, ctx->ctr);
            } else {
                R(3) = (R(5) << 1) + 0x81860000u;                        /* (the star time carried over) */
                R(5) = (uint32_t)(int16_t)gm_u16(R(3) - 5424);
                if (CMPS(R(5), 0) != 0) {
                    R(12) = gm_u32(self + PL_VTABLE); R(3) = self; R(4) = 2;
                    R(12) = gm_u32(R(12) + 984); ctx->ctr = R(12);
                    ctx->lr = 0x8182EA44u; ppc_call_indirect(ctx, base, ctx->ctr);
                }
                R(0) = gm_u8(self + PL_PLR_NO); R(3) = (R(0) << 1) + 0x81860000u;
                R(0) = (uint32_t)(int16_t)gm_u16(R(3) - 5408);
                gm_set_u8(self + PL_STAR_COUNT, (uint8_t)R(0));
            }
        }
    }
    VCALL(0x8182EA6Cu, self, VT_IS_ITEM_KINOPIO, 12);
    if (CMPS(R(3), 0) == 0) {
        R(0) = gm_u32(R(13) - 21628);
        if (CMPS(R(0), 0) == 0) {
            R(3) = (uint32_t)(int8_t)gm_u8(self + PL_PLR_NO);
            BL(0x8182EA8Cu, getRemotePlayer__6dAudioFi_80069530);
            gm_set_u32(self + PL_AUDIO_REMOTE, R(3));
        }
    }
    R(3) = gm_u32(self + PL_TYPE); BL(0x8182EA98u, mfn_81806AB8);
    gm_set_u32(self + PL_SND_TYPE, R(3));
    R(3) = self; BL(0x8182EAA4u, hle_fn_8004D5A0);
    R(3) = self; BL(0x8182EAACu, hle_fn_80046A50);
    R(0) = gm_u8(self + PL_PLR_NO); R(3) = 1; R(0) = (uint32_t)(int8_t)R(0);
    gm_set_u32(self + PL_KEY, R(0));
}

/* setDamage(source, type) / setForcedDamage(source, type): the damage, the rumble and the death
   message (also for a player out of play) */
static void py_damage(GM_CTX, gptr self, uint32_t src, uint32_t type, int forced) {
    I2_FN(forced ? 0x8182EBE4u : 0x8182EAD0u); /* FNADDR */
    NV_R(28, self); NV_R(29, src);
    if (forced) {
        NV_R(30, type);
        BL(0x8182EC14u, hle_fn_8004DD00);                                    /* (isDemo) */
        int c = CMPU(R(3), 0); NV_R(27, 0);
        if (c != 0) goto end;
        R(3) = gm_u32(self + PL_MODE); R(4) = gm_u32(self + PL_NEXT_MODE);
        if (CMPU(R(3), R(4)) != 0) goto end;
        NV_R(26, gm_u32(self + PL_VTABLE));
        VCALL(0x8182EC44u, self, VT_IS_CHANGE, 3);
        if (CMPU(R(3), 0) != 0) goto end;
    } else {
        R(3) = gm_u32(self + PL_MODE); R(4) = gm_u32(self + PL_NEXT_MODE); NV_R(27, 0);
        if (CMPU(R(3), R(4)) != 0) goto end;
        NV_R(26, gm_u32(self + PL_VTABLE)); NV_R(30, type);
        VCALL(0x8182EB24u, self, VT_IS_CHANGE, 3);
        if (CMPU(R(3), 0) != 0) goto end;
        VCALL(0x8182EB3Cu, self, VT_IS_NO_DAMAGE, 3);
        if (CMPU(R(3), 0) != 0) goto end;
    }
    R(3) = gm_u32(R(26) + VT_SET_DAMAGE2); R(4) = R(29); R(5) = R(30); ctx->ctr = R(3); R(3) = self;
    ctx->lr = forced ? 0x8182EC64u : 0x8182EB5Cu; ppc_call_indirect(ctx, base, ctx->ctr);
    if (CMPU(R(3), 0) == 0) goto end;
    pp_shock(GM_PASS, self, 4, forced ? 0x8182EC8Cu : 0x8182EB84u);
    R(3) = gm_u8(GAME_RULE + 8); NV_R(27, 1);
    if (CMPU(R(3), 0) == 0) goto end;
    R(3) = self; R(4) = 4; BL(forced ? 0x8182ECB0u : 0x8182EBA8u, hle_testFlag__10daPlBase_cFi);
    R(6) = R(3); R(3) = self; R(4) = R(29); R(5) = R(30);
    BL(forced ? 0x8182ECC4u : 0x8182EBBCu, mfn_818033F4);              /* (addDeathMessage) */
end:
    R(3) = R(27);
}

/* ================================================================== hle entry points
   On (reached by the A/B inputs, see the report in the file's history): listed in hle_funcs.txt.
   RT_GM_REACH=1 logs each entry's first call (the reach list). Verified memory: the object
   (calls into the model / state manager / other players change more; for those RT_GM_VERIFY's
   double run is for the registers only and the strict A/B is the test). */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
#define PL_SIZE 0x2C00                   /* (dAcPy_c, as far as the fields above go) */
#define PL_MEM SELF, PL_SIZE, EXEC_STOP_REQ, 1
#define GAME_RANDOM 0x80429F44u          /* dGameCom's cRandom_c (executeDemoGoal_Run draws from it) */
#define PL_MEM_SCENE PL_MEM, PY_ACT_INFO, 0x288, 0x80429CA0u, 0x50, EXIT_MODE, 4   /* (+ daPyMng_c's arrays and scalars) */
#define PL_MEM_DEMO PL_MEM, gm_u32(DEMO_MNG_P), 0xD0, GAME_RANDOM, 4   /* (+ the demo manager) */
static void pp_reached(const char *name) {
    static int on = -1; if (on < 0) on = getenv("RT_GM_REACH") != NULL;
    if (on) rt_log("gm", "reached %s (frame %llu)", name, (unsigned long long)g_frames_presented);
}
#define PP_HLE(name, flags, ...) \
    static void name##_native(ppc_context *ctx, uint8_t *base); \
    GM_HLE(name) { static int seen_; if (!seen_) { seen_ = 1; pp_reached(#name); } \
                   if (gm_verifying()) { const gptr r_[] = { __VA_ARGS__ }; \
                       gm_verify(#name, ctx, base, name##_native, orig_##name, r_, (int)(sizeof r_ / sizeof *r_) / 2, (flags)); } \
                   else name##_native(ctx, base); } \
    static void name##_native(ppc_context *ctx, uint8_t *base)
static void pp_selftest(GM_CTX, gptr self);
#define PP_VOID(name, ...) PP_HLE(name, 0, __VA_ARGS__)
#define PP_INT(name, ...)  PP_HLE(name, GMV_RET, __VA_ARGS__)

/* On (reached by the A/B inputs 1-5; RT_GM_REACH=1 logs the first calls):
     initDemoInDokanUD (input 4), stopGoalOther / executeDemoGoal_Run (5), executeState_WallSlide,
     setSpinLiftUpReserve, setBalloonInDispOut / -Base, checkRest, stop- / playOtherDownDemo,
     setFallDownDemo, initChangeInit / executeChangeInit, setSceneChangeInfo, create, setDamage.
   Written but off (no input reaches them; -DPY_PLAYER_UNREACHED and their names in hle_funcs.txt
   switch them on - updateRopeAngle and setControlDemoWalk then join the self-test):
     initializeState_DemoRailDokan / setExitRailDokan (rail pipes), playGoalOther,
     setControlDemoWalk / executeState_DemoControl (control demos), updateRopeAngle,
     setBalloonInDispOutByYoshi, setForcedDamage. */
PP_VOID(mod_fn_8004EDE0, PL_MEM)                       { pl_initDemoInDokanUD(GM_PASS, SELF, A(1)); }
PP_VOID(mod_fn_800510F0, PL_MEM_DEMO)                  { pl_stopGoalOther(GM_PASS, SELF); }
PP_VOID(mod_fn_80128980, PL_MEM)                       { py_executeState_WallSlide(GM_PASS, SELF); }
PP_VOID(mod_fn_8012E1F0, PL_MEM)                       { pp_selftest(GM_PASS, SELF); py_setSpinLiftUpReserve(GM_PASS, SELF); }
PP_INT (mod_fn_80139210, PL_MEM)                       { py_setBalloonInDispOutBase(GM_PASS, SELF, A(1), A(2), A(3)); }
PP_INT (mod_fn_80139200, PL_MEM)                       { py_setBalloonInDispOut(GM_PASS, 0x8182DD14u, 0, 0x8182DD2Cu); }
PP_VOID(mod_fn_8013D670, PL_MEM)                       { py_checkRest(GM_PASS, SELF); }
PP_VOID(mod_fn_8013D8F0, PL_MEM_DEMO)                  { py_stopOtherDownDemo(GM_PASS, SELF); }
PP_VOID(mod_fn_8013D9F0, PL_MEM_DEMO)                  { py_playOtherDownDemo(GM_PASS, SELF); }
PP_VOID(mod_fn_8013DDD0, PL_MEM)                       { py_setFallDownDemo(GM_PASS, SELF); }
PP_VOID(mod_fn_8013FF70, PL_MEM_DEMO)                  { py_executeDemoGoal_Run(GM_PASS, SELF); }
PP_VOID(mod_fn_80140EE0, PL_MEM_DEMO)                  { py_initChangeInit(GM_PASS, SELF); }
PP_INT (mod_fn_80140F40, PL_MEM)                       { py_executeChangeInit(GM_PASS, SELF); }
PP_VOID(mod_fn_80144B20, PL_MEM_SCENE)                 { py_setSceneChangeInfo(GM_PASS, SELF); }
PP_INT (mod_fn_80144D60, PL_MEM)                       { py_create(GM_PASS, SELF); }
PP_INT (mod_dAcPy_vf3F4, PL_MEM)                       { py_damage(GM_PASS, SELF, A(1), A(2), 0); }
#ifdef PY_PLAYER_UNREACHED
PP_VOID(mod_fn_80050870, PL_MEM)                       { pl_initializeState_DemoRailDokan(GM_PASS, SELF); }
PP_VOID(mod_fn_80050A00, PL_MEM)                       { pl_setExitRailDokan(GM_PASS, SELF); }
PP_VOID(mod_fn_800511A0, PL_MEM_DEMO)                  { pl_playGoalOther(GM_PASS, SELF); }
PP_VOID(mod_moveInDirection__10daPlBase_cFPfPf, PL_MEM){ pl_setControlDemoWalk(GM_PASS, SELF, A(1), A(2)); }
PP_VOID(mod_fn_80052900, PL_MEM)                       { pl_executeState_DemoControl(GM_PASS, SELF); }
PP_INT (mod_fn_80136650, PL_MEM)                       { py_updateRopeAngle(GM_PASS, SELF); }
PP_INT (mod_fn_801391F0, PL_MEM)                       { py_setBalloonInDispOut(GM_PASS, 0x8182DAE0u, 1, 0x8182DAF8u); }
PP_INT (mod_dAcPy_vf3F8, PL_MEM)                       { py_damage(GM_PASS, SELF, A(1), A(2), 1); }
#endif

/* ================================================================== self-test (RT_GM_SELFTEST=py_player)
   On a live player (the first call of the entry that starts it): setSceneChangeInfo with random
   flags, exit mode, power-up, star counters and per-character arrays; (with the unreached ones on)
   updateRopeAngle with a random
   rope / pole controller (none, or a scratch one inside the object with random modes, angle
   tables and pole index) and setControlDemoWalk with random flags, substate, targets and speeds
   (its two arguments point at scratch floats inside the object). The object is put back after. */
#define ST_CTR   0x2B00                  /* (scratch inside the object's range: a dPc_c controller) */
#define ST_FLT   0x2B40                  /*   its float table */
#define ST_ANG   0x2B60                  /*   its s16 angle tables */
#define ST_ARG   0x2B80                  /*   setControlDemoWalk's pos / speed */
static gptr pp_test_self;
static void pp_randomize_scene(void);
static float pp_rfloat(void) { static const float v[] = { 0.0f, 1.0f, -1.0f, 0.5625f, 3.0f, -3.0f, 100.0f, 1e-3f, -250.5f };
    return gm_rand() % 3 ? v[gm_rand() % 9] : (float)((int32_t)(gm_rand() % 20001) - 10000) / 16.0f; }
static void pp_randomize(GM_CTX, int round) {
    (void)ctx; (void)base; (void)round;
    gptr s = pp_test_self;
    for (uint32_t a = 0; a < 32; a += 4) gm_set_u32(s + 4116 + a, (gm_rand() & gm_rand()) | (gm_rand() % 2 ? 1u << 18 : 0));   /* (flags; 114 often) */
    gm_set_u8(s + PL_DEMO_STATE, (uint8_t)(gm_rand() % 3));
    float pos = pp_rfloat();
    gm_set_f32(s + ST_ARG, pos); gm_set_f32(s + ST_ARG + 4, pp_rfloat());
    gm_set_f32(s + PL_DEMO_TARGET_X, gm_rand() % 2 ? pos : pp_rfloat());
    gm_set_f32(s + PL_DEMO_SPEED_F, pp_rfloat());
    gm_set_u32(s + PL_SUBSTATE_TIMER, gm_rand() % 4 ? gm_rand() % 1000 : 0);
    for (uint32_t a = 0; a < 8; a += 2) gm_set_u16(s + PL_ROPE_ANGLE + a, (uint16_t)gm_rand());
    gm_set_u8(s + PL_PLR_NO, (uint8_t)(gm_rand() % 8));
    pp_randomize_scene();
    if (gm_rand() % 4 == 0) gm_set_u32(s + PL_PC + 16, 0);
    else {
        gptr c = s + ST_CTR;
        gm_set_u32(s + PL_PC + 16, c);
        gm_set_u8(c + 32, (uint8_t)(1 + gm_rand() % 5));                /* (mode 1-5: 0 is a virtual call) */
        gm_set_u32(c + 44, s + ST_FLT); gm_set_u32(c + 48, s + ST_ANG);
        gm_set_u32(c + 52, gm_rand() % 3 ? s + ST_ANG : 0);
        gm_set_u8(s + PL_PC + 4 + 46, (uint8_t)(gm_rand() % 4));
        gm_set_f32(s + PL_PC + 4 + 32, pp_rfloat());
        for (uint32_t a = 0; a < 16; a += 4) gm_set_f32(s + ST_FLT + a, gm_rand() % 2 ? 1.0f : pp_rfloat());
        for (uint32_t a = 0; a < 32; a += 2) gm_set_u16(s + ST_ANG + a, (uint16_t)gm_rand());
    }
}
/* setSceneChangeInfo: the exit mode, power-up, star counters and daPyMng_c's per-character arrays
   (the character numbers kept 0-7: they index the arrays) */
static void pp_randomize_scene(void) {
    gptr s = pp_test_self;
    gm_set_u32(EXIT_MODE, gm_rand() % 7);
    gm_set_u32(s + PL_MODE, gm_rand() % 7);
    gm_set_u32(s + PL_STAR_TIME, gm_rand() % 3 ? 0 : gm_rand() % 600);
    gm_set_u8(s + PL_STAR_COUNT, (uint8_t)(gm_rand() % 3 ? 0 : gm_rand() % 8));
    for (uint32_t i = 0; i < 8; i++) {
        gm_set_u32(PY_ENTRY + 4 * i, gm_rand() % 2);
        gm_set_u32(PY_TYPE + 4 * i, gm_rand() % 8);
        gm_set_u32(PY_MODE + 4 * i, gm_rand() % 7);
        gm_set_u32(PY_CREATE_ITEM + 4 * i, gm_rand() % 16);
        gm_set_u16(PY_STAR_TIME + 2 * i, (uint16_t)gm_rand()); gm_set_u16(PY_STAR_COUNT + 2 * i, (uint16_t)gm_rand());
    }
}
static uint32_t pp_arg(char k) {
    return k == 'P' ? pp_test_self + ST_ARG : k == 'Q' ? pp_test_self + ST_ARG + 4 : 0xDEADBEEFu;
}
static const gm_test_t pp_tests[] = {
    GM_TEST(mod_fn_80144B20, 0, ""),
#ifdef PY_PLAYER_UNREACHED
    GM_TEST(mod_fn_80136650, GMV_RET, ""),
    GM_TEST(mod_moveInDirection__10daPlBase_cFPfPf, 0, "PQ"),
#endif
};
static void pp_selftest(GM_CTX, gptr self) {
    if (!gm_selftest_wanted("py_player")) return;
    pp_test_self = self;
    const gptr ranges[] = { self, PL_SIZE, EXEC_STOP_REQ, 1, PY_ACT_INFO, 0x288, 0x80429CA0u, 0x50, EXIT_MODE, 4 };
    const gm_selftest_t t = { "py_player", pp_tests, (int)(sizeof pp_tests / sizeof *pp_tests), 400, ranges, 5, pp_randomize, pp_arg };
    gm_selftest(GM_PASS, &t);
}
