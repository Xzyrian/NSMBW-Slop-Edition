/* gm_py_key.c - the controller input: dGameKey_c, dGameKeyCore_c, dAcPyKey_c (track B, gm.h,
 * docs/DECOMP.md), instance 2.
 *
 * The 8-player module's versions (nsmbw-project v0.6.5, wiimj2d/d_static/d_game_key/
 * d_game_key.cpp, d_game_key_core.cpp, d_static/d_a_player/d_a_player_key.cpp):
 *  - dGameKey_c holds a dGameKeyCore_c per player (8 instead of 4) and reads them all each frame;
 *  - dGameKeyCore_c::read takes one player's remote (or the replay of a title demo / hint movie),
 *    turns Nunchuk, Classic and GameCube buttons into the sideways-remote layout (setConfigKey),
 *    keeps the auto-repeat of the d-pad, the tilt (handleTilting) and the shake (setShakeY);
 *  - dAcPyKey_c is a player's view of its core: held / triggered buttons, the demo overrides, the
 *    hip-attack hold and the jump history (the module dropped the per-remote history offset).
 *
 * The game's read__10dGameKey_cFv hands over to the module's read when g_mod_on; rt_menu.c wraps
 * that game symbol (hle_read__10dGameKey_cFv -> orig_read__10dGameKey_cFv -> the module's read,
 * now hle_mod_read__10dGameKey_cFv here), so the title players' run key still lands after it.
 *
 * Nine of the twelve are on (every input reaches them each frame; triggerJumpBuf the title demos
 * and the attract demos); the constructor, the destructor and buttonOne are written but off
 * (GM_PY_KEY_OFF): no input reaches them.
 *
 * Register-exact (gm_i2.h): every function leaves r0-r12, CR0, CTR, XER[CA], the FPRs it uses
 * and the memory as the PowerPC code does; framed functions push the PowerPC frame (I2_FN), store
 * the same frame words (the core's float copies at sp+16..28, the tilt's fctiwz at sp+16 / +24)
 * and keep r26-r31 as the PowerPC code holds them at each call. */
#include "gm_i2.h"
RT_STATE_FILE                                   /* (game code: its variables are part of a save state) */

/* ---- dGameKey_c */
#define GK_INSTANCE         0x80429F50u /* dGameKey_c::m_instance (r13 - 22320) */
#define GK_VTABLE           0x81851F24u /* the module's dGameKey_c vtable */
#define GK_CORES            4           /* dGameKeyCore_c *mpCores[8] */
#define GK_CHANNELS         0x818498D0u /* mPad::CH_e s_channels[8] (the constructor's table) */
#define GK_SIZE             36
/* ---- dGameKeyCore_c (148 bytes allocated) */
#define GKC_PLAYER_NO       4           /* int mPlayerNo */
#define GKC_TYPE            8           /* Type_e mType: 0 core, 1 Nunchuk, 2 GameCube, 3 Classic */
#define GKC_RAW_HELD        12          /* u32 mRawHeld */
#define GKC_PREV_RAW_HELD   16
#define GKC_HELD            20          /* u32 mHeld (after setConfigKey) */
#define GKC_PREV_HELD       24
#define GKC_TRIGGERED       28          /* u32 mTriggered (its top byte: bit 24 = shake) */
#define GKC_REPEAT          32          /* u32 m0x20: the d-pad's auto-repeat bits */
#define GKC_REPEAT_TIMER    36          /* u32 m0x24 */
#define GKC_REPEAT_FIRST    40          /* u32 m0x28: the delay after a press */
#define GKC_REPEAT_NEXT     44          /* u32 m0x2C: the delay between repeats */
#define GKC_EXTRA_TRIG      48          /* u32 m0x30 */
#define GKC_ACCEL           52          /* mVec3_c mAccel */
#define GKC_ACCEL_OLD       64
#define GKC_VERT_X          76          /* mVec2_c mAccelVerticalX (Y, Z at +16, +32), their olds at +8 */
#define GKC_VERT_X_OLD      84
#define GKC_VERT_Y          92
#define GKC_VERT_Y_OLD      100
#define GKC_VERT_Z          108
#define GKC_ANGLE           116         /* mVec2_c mAngle (the pointer) */
#define GKC_ANGLE_OLD       124
#define GKC_MOVE_DIST       132         /* f32 mMoveDistance */
#define GKC_MOVE_DIST_OLD   136
#define GKC_SHAKE           140         /* bool mShake, mShakeOld (+141) */
#define GKC_TILT            142         /* s16 mTilt */
#define GKC_SHAKE_T1        144         /* u8 mShakeTimer1, 2 (+145), 3 (+146) */
#define GKC_SIZE            148
/* ---- what a core reads */
#define CORE_ORDER          0x8185FB1Cu /* mPad::g_core_order[8]: EGG::Controller * per player */
#define REPLAY_PLAY         0x8185F8DCu /* dScStage_c::m_replayPlay_p[8] (dReplayPlay_c *) */
#define REMOCON_MNG         0x8042A028u /* dRemoconMng_c::m_instance (r13 - 22104) */
#define PLAYER_CHANNEL      0x818542A4u /* mPad::g_playerChannel[8] */
#define PAD_ADDITIONAL      0x80377CA8u /* mPad::g_PadAdditionalData[] (24 bytes: mAccVertical[3]) */
#define VT_CORE_CTRL        0x80350030u /* EGG::CoreController's vtable */
#define VT_GC_CTRL          0x8185E738u /* the module's GameCube controller vtable */
#define VT_CTRL_WRAP        0x8185E770u /* (a controller holding its core controller at +44) */
#define GAME_RULE           0x8185FE04u /* dGameRule_s::current; +3 shake_with_button */
#define F_ZERO              0x81848674u /* 0.0f */
#define F_ONE               0x818487B0u /* 1.0f */
#define F_NEG_16384         0x818487A0u /* (the Nunchuk tilt scale) */
#define F_16384             0x81848734u
#define D_1_2               0x81848898u /* 1.2 (double) */
#define D_0_28              0x81848858u /* 0.28 (double) */
/* ---- dAcPyKey_c (0x164 bytes) */
#define PK_REMOCON          0           /* int mRemoconID (-1: none) */
#define PK_DOWN             4           /* u16 mDownButtons, mTriggeredButtons (+6) */
#define PK_PREV_DOWN        8           /* u16, and the previous trigger (+10) */
#define PK_DEMO_DOWN        12          /* u16 mDownButtonsDemo, mTriggeredButtonsDemo (+14) */
#define PK_DEMO_SHAKE       16          /* u16 mDemoDoShake */
#define PK_STATUS           18          /* u16 mStatus: 1 none, 2 no cross, 0x40 shake cooldown, 0x80 demo, 0x100 walk */
#define PK_HIP_ATK          20          /* u8 count, read (+21), hold start (+22) */
#define PK_SHAKE_JUMP       23          /* u8 mTriggerShakeJump, mActiveShakeJump (+24) */
#define PK_SHAKE_COOLDOWN   28          /* int */
#define PK_JUMP_TRIG_HIST   36          /* int [10] (the module: no per-remote offset) */
#define PK_JUMP_BTN_HIST    196         /* int [10] */
#define PK_SIZE             0x164

/* ---- other functions */
extern void hle_fn_8015F200(ppc_context *ctx, uint8_t *base);   /* sLib::addCalcAngle (gm_s_lib.c) */
void hle_mod_fn_800B5C60(ppc_context *ctx, uint8_t *base);
void hle_mod_fn_800B6080(ppc_context *ctx, uint8_t *base);
void hle_mod_fn_800B61A0(ppc_context *ctx, uint8_t *base);
void hle_mod_fn_800B6250(ppc_context *ctx, uint8_t *base);
/* (recompiled: operator new / sized delete of the module, the game's dGameKeyCore_c constructor and
   allclear, EGG::Math<float>::sqrt, the dAcPyKey_c helpers clearCrossKey / offStatus /
   triggerJump / buttonJump) */

#define FL(n, v) (ctx->f[n].d = ctx->ps1[n] = (v))                /* lfs / single arithmetic: both halves */
#define FABS(n, m) (ctx->f[n].u = ctx->f[m].u & ~0x8000000000000000ull)   /* fabs: ps0 only */
#define CR7_BIT(sh) (i2_rotl(ctx->cr, (sh)) & 1)                 /* (mfcr; rlwinm r, r, sh, 31, 31) */

/* ================================================================== dGameKey_c */
#ifdef GM_PY_KEY_OFF   /* (the constructor / destructor: written but off, see the entry points) */
/* dGameKey_c(): a core for each player, on the channels of the table */
static void gk_ctor(GM_CTX, gptr self) {
    I2_FN(0x8180B158u);
    R(4) = GK_CHANNELS; NV_R(30, self); R(3) = GK_VTABLE;
    NV_R(27, GK_CHANNELS - 4); NV_R(28, 8); NV_R(26, self);
    gm_set_u32(self, GK_VTABLE);
    for (;;) {
        R(3) = GKC_SIZE; BL(0x8180B1A4u, mod___nw__FUl_818432E4);
        uint32_t ea = R(27) + 4; R(4) = gm_u32(ea); NV_R(27, ea);          /* (lwzu: the channel) */
        NV_R(29, R(3));
        BL(0x8180B1B0u, fn_800B5B00);                                     /* dGameKeyCore_c(channel) */
        NV_R(28, R(28) - 1); int more = CMPU(R(28), 0) > 0;
        ea = R(26) + 4; gm_set_u32(ea, R(29)); NV_R(26, ea);             /* (stwu) */
        if (!more) break;
        GM_LOOP();
    }
    R(3) = self;
}
/* ~dGameKey_c(): each core deleted (its virtual deleting destructor); the object too when asked */
static void gk_dtor(GM_CTX, gptr self, uint32_t del) {
    I2_FN(0x8180B2C0u);
    NV_R(30, self); R(3) = GK_VTABLE; NV_R(28, 8); NV_R(29, del); NV_R(27, self);
    gm_set_u32(self, GK_VTABLE);
    for (;;) {
        uint32_t ea = R(27) + 4; R(3) = gm_u32(ea); NV_R(27, ea);
        if (CMPU(R(3), 0) != 0) {
            R(4) = gm_u32(R(3)); R(4) = gm_u32(R(4) + 8); ctx->ctr = R(4); R(4) = 1;
            ctx->lr = 0x8180B318u; ppc_call_indirect(ctx, base, ctx->ctr);
        }
        NV_R(28, R(28) - 1); int more = CMPU(R(28), 0) > 0;
        if (!more) break;
        GM_LOOP();
    }
    if (CMPS(R(29), 1) >= 0) { R(3) = self; R(4) = GK_SIZE; BL(0x8180B338u, mfn_818434F4); }
    R(3) = self;
}
#endif
/* allclear: every core cleared (the game's dGameKeyCore_c::allclear) */
static void gk_allclear(GM_CTX, gptr self) {
    I2_FN(0x8180B35Cu);
    NV_R(29, 8); NV_R(30, self);
    for (;;) {
        uint32_t ea = R(30) + 4; R(3) = gm_u32(ea); NV_R(30, ea);
        BL(0x8180B380u, fn_800B5B90);
        NV_R(29, R(29) - 1); int more = CMPU(R(29), 0) > 0;
        if (!more) break;
        GM_LOOP();
    }
}
/* read: every core reads its remote; returns 0 */
static uint32_t gk_read(GM_CTX, gptr self) {
    I2_FN(0x8180B3A4u);
    NV_R(29, 8); NV_R(30, self);
    for (;;) {
        uint32_t ea = R(30) + 4; R(3) = gm_u32(ea); NV_R(30, ea);
        BL(0x8180B3C8u, hle_mod_fn_800B5C60);
        NV_R(29, R(29) - 1); int more = CMPU(R(29), 0) > 0;
        if (!more) break;
        GM_LOOP();
    }
    R(3) = 0;
    return 0;
}

/* ================================================================== dGameKeyCore_c */
/* setConfigKey(input): a controller's buttons in the sideways-remote layout (bit 24: shake) */
static uint32_t gkc_setConfigKey(GM_CTX, gptr self, uint32_t in) {
    R(3) = gm_u32(self + GKC_TYPE);
    if (CMPU(R(3), 1) == 0) {                              /* ---- Nunchuk */
        uint32_t stick = in & 0xF0000u; CR0(ctx, stick);
        R(5) = 0x10008u; R(6) = 0x9010u; R(3) = in;
        if (stick) R(3) = in & 0xFFFFFFF0u;                /* (the stick pushed: no d-pad) */
        R(7) = R(3) & 0x20004u; CR0(ctx, R(7));
        R(4) = in & 0x9010u;                               /* (home, minus, plus) */
        if (R(7)) R(4) |= 1;                               /* down */
        else { R(5) = R(3) & 0x10008u; CR0(ctx, R(5)); if (R(5)) R(4) |= 2; }   /* up */
        R(5) = R(3) & 0x80002u; CR0(ctx, R(5));
        if (R(5)) R(4) |= 4;                               /* right */
        else { R(5) = R(3) & 0x40001u; CR0(ctx, R(5)); if (R(5)) R(4) |= 8; }   /* left */
        R(5) = gm_u8(GAME_RULE + 3);
        int shake_btn = CMPU(R(5), 0) != 0;
        R(5) = shake_btn ? 0x300u : 0x4300u;               /* (with the shake button C shakes, else C is A) */
        R(6) = shake_btn ? i2_rotl(R(3), 10) & 0x1000000u : 0;
        R(5) = R(3) & R(5); CR0(ctx, R(5));
        R(4) = (R(6) & 0x1000000u) | (R(4) & ~0x1000000u);
        if (R(5)) R(4) |= 0x800;                           /* A */
        R(5) = R(3) & 0x400; CR0(ctx, R(5));
        if (R(5)) R(4) |= 0x600;                           /* B: B + 1 */
        R(5) = R(3) & 0x2000; CR0(ctx, R(5));
        if (R(5)) R(4) |= 0x2200;                          /* Z: Z + 1 */
        R(3) = i2_rotl(R(3), 29) & 0x100;                  /* A: 2 */
        R(3) = R(4) | R(3);
        return R(3);
    }
    if (CMPU(R(3), 2) == 0) {                              /* ---- GameCube */
        uint32_t down = in & 0x20004u; CR0(ctx, down);
        NONZERO(5, 3, in & 0x10008u);
        if (down) R(3) = 1; else R(3) <<= 1;               /* down, else up */
        R(5) = in & 0x80002u; CR0(ctx, R(5));
        if (R(5)) { R(5) = 4; R(3) |= 4; }                 /* right */
        else { R(5) = in & 0x40001u; CR0(ctx, R(5)); if (R(5)) { R(5) = 8; R(3) |= 8; } }   /* left */
        R(3) &= 0xFF;
        R(5) = in & 0x200; CR0(ctx, R(5));
        R(3) = (in & 0x100) | (R(3) & ~0x100u);            /* A: 2 */
        if (R(5)) R(3) |= 0x2200;                          /* B: Z + 1 */
        R(5) = in & 0x800; CR0(ctx, R(5));
        if (R(5)) R(3) |= 0x600;                           /* Y: B + 1 */
        R(5) = in & 0x10; CR0(ctx, R(5));
        if (R(5)) { R(3) |= 0x1000; R(3) |= 0x1000000; }   /* Z: shake + minus */
        R(5) = i2_rotl(in, 24) & 0x10;                     /* (start: plus) */
        R(5) = (i2_rotl(in, 1) & 0x800) | (R(5) & ~0x800u);   /* (X: A) */
        R(3) = R(5) | R(3);
        return R(3);
    }
    if (CMPU(R(3), 3) == 0) {                              /* ---- Classic */
        uint32_t down = in & 0x24000u; CR0(ctx, down);
        NONZERO(5, 3, in & 0x10001u);
        if (down) R(3) = 1; else R(3) <<= 1;
        R(5) = in & 0x88000u; CR0(ctx, R(5));
        if (R(5)) { R(5) = 4; R(3) |= 4; }
        else { R(5) = in & 0x40002u; CR0(ctx, R(5)); if (R(5)) { R(5) = 8; R(3) |= 8; } }
        R(5) = in & 0x50; CR0(ctx, R(5));
        if (R(5)) { R(5) = 0x100; R(3) |= 0x100; }         /* a / b: 2 */
        R(5) = in & 0x28; CR0(ctx, R(5));
        if (R(5)) { R(5) = 0x200; R(3) |= 0x200; }         /* x / y: 1 */
        R(5) = in & 0x84; CR0(ctx, R(5));
        if (R(5)) { R(5) = 0x1000000; R(3) |= 0x1000000; } /* zl / zr: shake */
        R(5) = in & 0x1000; CR0(ctx, R(5));
        if (R(5)) R(3) |= 0x1800;                          /* minus: A + minus */
        R(4) = i2_rotl(in, 26) & 0x10;                     /* (plus) */
        R(3) |= R(4);
        return R(3);
    }
    /* ---- the sideways remote: B also shakes with the shake button rule */
    R(3) = gm_u8(GAME_RULE + 3);
    R(5) = in & 0x400;
    if (CMPU(R(3), 0) != 0) R(3) = in | 0x1000000u; else R(3) = in;
    if (CMPU(R(5), 0) != 0) return R(3);
    R(3) = in;
    return R(3);
}

/* handleTilting: mTilt from the replay, the Nunchuk (eased: sLib::addCalcAngle) or the remote */
static void gkc_handleTilting(GM_CTX, gptr self) {
    I2_FN(0x8180BC78u);
    gptr sp = gm_frame_sp;
    R(5) = gm_u32(self + GKC_PLAYER_NO) << 2; R(4) = gm_u32(REPLAY_PLAY + R(5));
    if (CMPU(R(4), 0) != 0) {
        R(4) = gm_u16(R(4) + 156);                         /* (the replay's tilt) */
        gm_set_u16(self + GKC_TILT, (uint16_t)R(4));
        return;
    }
    R(4) = gm_u32(self + GKC_TYPE);
    if (CMPU(R(4), 1) == 0) {
        R(4) = 0x81850000u;
        FL(0, ldfs(base, self + GKC_ACCEL + 8));
        R(3) = self + GKC_TILT;
        FL(1, ldfs(base, F_NEG_16384));
        R(5) = 10; R(6) = 0x1000; R(7) = 0;
        ctx->f[0].d = ctx->f[0].d * ctx->f[1].d;           /* (fmul: ps0 only) */
        ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
        st64(base, sp + 16, ctx->f[0].u); R(4) = gm_u32(sp + 20);
        BL(0x8180BCE4u, hle_fn_8015F200);                  /* sLib::addCalcAngle(&mTilt, -accel.z * 16384, 10, 0x1000, 0) */
        return;
    }
    R(4) = 0x81850000u;
    FL(0, ldfs(base, self + GKC_VERT_X + 4));
    FL(1, ldfs(base, F_16384));
    ctx->f[0].d = ctx->f[0].d * ctx->f[1].d;
    ctx->f[0].u = fctiw_bits(ctx->f[0].d, 1);
    st64(base, sp + 24, ctx->f[0].u); R(4) = gm_u32(sp + 28);
    gm_set_u16(self + GKC_TILT, (uint16_t)R(4));
}

/* setShakeY: mShake from the replay, the shake button, or a sharp vertical swing of the remote */
static void gkc_setShakeY(GM_CTX, gptr self) {
    R(5) = gm_u32(self + GKC_PLAYER_NO) << 2; R(4) = gm_u32(REPLAY_PLAY + R(5));
    if (CMPU(R(4), 0) != 0) {
        R(4) = i2_rotl(gm_u32(R(4) + 100), 3) & 1;         /* (the replay frame's flag bit 29) */
        goto store;
    }
    R(4) = gm_u8(self + GKC_SHAKE_T1 + 2);
    if (CMPU(R(4), 0) != 0) {                              /* (just shaken: a pause) */
        R(4)--; gm_set_u8(self + GKC_SHAKE_T1 + 2, (uint8_t)R(4));
        goto none;
    }
    R(4) = gm_u8(self + GKC_TRIGGERED) & 1; CR0(ctx, R(4));
    if (R(4)) goto shaken;                                 /* (the shake button) */
    R(4) = gm_u32(self + GKC_TYPE);
    if (CMPU(R(4), 2) >= 0) { GM_LOOP(); goto none; }      /* (no motion but the remote's) */
    FL(0, ldfs(base, self + GKC_ACCEL + 4));
    R(4) = 0x81850000u;
    FL(1, ldfs(base, self + GKC_ACCEL_OLD + 4));
    ctx->f[3].u = ld64(base, D_0_28);
    FL(0, frsp(ctx->f[0].d - ctx->f[1].d));
    FABS(2, 0);                                            /* |accel.y - old.y| */
    cr_fcmp(ctx, 7, ctx->f[2].d, ctx->f[3].d);
    R(4) = ctx->cr & 1; R(5) = CR7_BIT(29); R(4) = R(5) | R(4); CR0(ctx, R(4));
    int small = R(4) != 0;                                 /* (below 0.28, or NaN) */
    R(4) = gm_u8(self + GKC_SHAKE_T1);
    if (small) {
        if (CMPU(R(4), 0) == 0) { GM_LOOP(); goto none; }
        R(4) = gm_u8(self + GKC_SHAKE_T1 + 1); R(5) = R(4) + 1;
        int lt = CMPU(R(4), 2) < 0;
        gm_set_u8(self + GKC_SHAKE_T1 + 1, (uint8_t)R(5));
        if (lt) { GM_LOOP(); goto none; }
        R(4) = 0; gm_set_u16(self + GKC_SHAKE_T1, 0);      /* (timers 1 and 2 back to 0) */
        GM_LOOP(); goto none;
    }
    FL(0, ldfs(base, self + GKC_ACCEL));
    R(4) += 1;
    FL(1, ldfs(base, self + GKC_ACCEL_OLD));
    R(5) = R(4) & 0xFF;
    FL(3, ldfs(base, self + GKC_ACCEL + 8));
    int few = CMPU(R(5), 4) < 0;
    FL(4, ldfs(base, self + GKC_ACCEL_OLD + 8));
    gm_set_u8(self + GKC_SHAKE_T1, (uint8_t)R(4));
    if (few) { GM_LOOP(); goto none; }
    FL(3, frsp(ctx->f[3].d - ctx->f[4].d));
    FABS(3, 3);                                            /* |accel.z - old.z| */
    cr_fcmp(ctx, 7, ctx->f[3].d, ctx->f[2].d);
    R(4) = ctx->cr & 1; R(5) = CR7_BIT(30); R(4) ^= 1; R(5) ^= 1; R(4) = R(5) & R(4); CR0(ctx, R(4));
    if (R(4) == 0) {                                       /* (z diff over the y diff: also over the x diff?) */
        FL(0, frsp(ctx->f[0].d - ctx->f[1].d));
        FABS(0, 0);
        cr_fcmp(ctx, 7, ctx->f[3].d, ctx->f[0].d);
        R(4) = ctx->cr & 1; R(5) = CR7_BIT(30); R(4) = R(5) | R(4); CR0(ctx, R(4));
        if (R(4) != 0) { GM_LOOP(); goto none; }
    }
    R(4) = 5; gm_set_u8(self + GKC_SHAKE_T1 + 2, 5);
    R(4) = 0; gm_set_u8(self + GKC_SHAKE_T1, 0);
shaken:
    R(4) = 1;
    GM_LOOP();
    goto store;
none:
    R(4) = 0;
store:
    gm_set_u8(self + GKC_SHAKE, (uint8_t)R(4));
}

/* read: one player's buttons, motion and pointer for this frame */
static void gkc_read(GM_CTX, gptr self) {
    I2_FN(0x8180B5B4u);
    gptr sp = gm_frame_sp;
    /* last frame's values */
    R(7) = self + GKC_ACCEL; NV_R(30, self);
    R(3) = gm_u32(self + GKC_ACCEL);                       /* (lwzu r3, 52(r7)) */
    R(5) = 0;
    R(6) = gm_u32(self + GKC_HELD); R(8) = gm_u32(self + GKC_ACCEL + 4);
    gm_set_u32(self + GKC_PREV_HELD, R(6));
    R(6) = gm_u32(self + GKC_ANGLE + 4);
    gm_set_u32(self + GKC_ACCEL_OLD, R(3));
    R(3) = gm_u32(self + GKC_ANGLE);
    gm_set_u32(self + GKC_ACCEL_OLD + 4, R(8));
    R(8) = gm_u32(self + GKC_MOVE_DIST); R(9) = gm_u32(self + GKC_ACCEL + 8);
    R(10) = gm_u32(self + GKC_VERT_X); R(11) = gm_u32(self + GKC_VERT_X + 4);
    R(12) = gm_u32(self + GKC_VERT_Y); R(0) = gm_u32(self + GKC_VERT_Y + 4);
    gm_set_u32(self + GKC_ANGLE_OLD + 4, R(6));
    R(6) = gm_u32(self + GKC_PLAYER_NO); R(4) = gm_u32(self + GKC_RAW_HELD);
    gm_set_u32(self + GKC_ANGLE_OLD, R(3));
    gm_set_u32(self + GKC_MOVE_DIST_OLD, R(8));
    R(8) = 0x81860000u;
    gm_set_u32(self + GKC_ACCEL_OLD + 8, R(9));
    R(3) = CORE_ORDER;
    gm_set_u32(self + GKC_VERT_X_OLD + 4, R(11));
    R(6) <<= 2;
    gm_set_u32(self + GKC_VERT_X_OLD, R(10));
    R(8) = REPLAY_PLAY;
    gm_set_u32(self + GKC_VERT_Y_OLD + 4, R(0));
    gm_set_u32(self + GKC_VERT_Y_OLD, R(12));
    gm_set_u32(self + GKC_TYPE, 0);                        /* (Type_e::CORE) */
    gm_set_u32(self + GKC_PREV_RAW_HELD, R(4));
    R(3) = gm_u32(CORE_ORDER + R(6));                      /* the controller */
    R(8) = gm_u32(REPLAY_PLAY + R(6));                     /* the replay, if one plays */
    gm_set_u32(sp + 28, R(10)); gm_set_u32(sp + 16, R(11));
    int replay = CMPU(R(8), 0) != 0;
    gm_set_u32(sp + 24, R(12));
    FL(3, ldfs(base, sp + 28));                            /* (the old vertical x / y as floats) */
    FL(0, ldfs(base, sp + 16));
    FL(1, ldfs(base, sp + 24));
    gm_set_u32(sp + 20, R(0));
    if (replay) {
        R(3) = gm_u8(R(8) + 100) & 0x10; CR0(ctx, R(3));
        if (R(3)) { R(4) = gm_u32(R(8) + 112); gm_set_u32(self + GKC_PREV_RAW_HELD, R(4)); }
        NV_R(29, gm_u32(R(8) + 108)); gm_set_u32(self + GKC_RAW_HELD, R(29));
        R(3) = gm_u32(R(8) + 120); gm_set_u32(self + GKC_ACCEL, R(3));
        R(3) = gm_u32(R(8) + 124); gm_set_u32(self + GKC_ACCEL + 4, R(3));
        R(3) = gm_u32(R(8) + 128); gm_set_u32(self + GKC_ACCEL + 8, R(3));
        R(3) = gm_u32(R(8) + 136); R(5) = gm_u32(R(8) + 132);
        gm_set_u32(self + GKC_VERT_X + 4, R(3)); gm_set_u32(self + GKC_VERT_X, R(5));
        R(3) = gm_u32(R(8) + 144); R(5) = gm_u32(R(8) + 140);
        gm_set_u32(self + GKC_VERT_Y + 4, R(3)); gm_set_u32(self + GKC_VERT_Y, R(5));
        R(3) = gm_u32(R(8) + 152); R(5) = gm_u32(R(8) + 148);
        gm_set_u32(self + GKC_VERT_Z + 4, R(3)); gm_set_u32(self + GKC_VERT_Z, R(5));
        goto config;
    }
    /* the controller type from the remote's extension: 1 Nunchuk, 4 Classic, 5 GameCube */
    R(7) = gm_u32(REMOCON_MNG);
    FL(2, ldfs(base, sp + 20));
    R(7) = R(7) + R(6);
    R(7) = gm_u32(R(7) + 4);                               /* mpConnect[player] */
    R(8) = gm_u32(R(7) + 16);
    if (CMPU(R(8), 1) == 0) { R(7) = 1; gm_set_u32(self + GKC_TYPE, R(8)); goto core_ctrl; }
    if (CMPU(R(8), 5) == 0) {
        R(5) = 2; gm_set_u32(self + GKC_TYPE, 2);
        R(6) = VT_GC_CTRL; R(5) = gm_u32(R(3));
        if (CMPU(R(5), R(6)) == 0) goto triggers;         /* (the controller is the GameCube one) */
        goto keep;
    }
    { int c = CMPU(R(8), 4); R(7) = 0;
      if (c == 0) { R(5) = 1; R(8) = 3; gm_set_u32(self + GKC_TYPE, 3); } }
core_ctrl:                                                 /* getCoreController() */
    R(8) = gm_u32(R(3)); R(9) = VT_CORE_CTRL;
    if (CMPU(R(8), R(9)) != 0) {
        R(8) = gm_u32(R(3)); R(9) = VT_CTRL_WRAP;
        if (CMPU(R(8), R(9)) != 0) goto keep;
        R(3) = gm_u32(R(3) + 44);
        if (CMPU(R(3), 0) == 0) goto keep;
    }
    if (CMPU(R(5), 0) == 0) goto remote;
    R(3) = gm_u32(R(3) + 20);                              /* (the Classic Controller) */
triggers:                                                  /* Classic / GameCube: the triggers as motion */
    if (CMPU(R(3), 0) == 0) goto keep;
    FL(4, ldfs(base, R(3) + 32));
    R(5) = 0x81850000u;
    FL(5, ldfs(base, R(3) + 36));
    FL(6, ldfs(base, F_ZERO));
    R(5) = 0;
    FL(4, frsp(ctx->f[4].d - ctx->f[5].d));               /* L - R */
    gm_set_u32(self + GKC_ACCEL, 0);
    FL(3, frsp(ctx->f[6].d - ctx->f[3].d));               /* y.x = 0 - vertical x.x */
    gm_set_u32(self + GKC_ACCEL + 8, 0);
    FL(1, frsp(ctx->f[3].d - ctx->f[1].d));               /* z.x = y.x - vertical y.x */
    stfs(base, self + GKC_ACCEL + 4, ctx->f[4].d);
    FL(4, ldfs(base, R(3) + 36));
    FL(5, ldfs(base, R(3) + 32));
    NV_R(29, gm_u32(R(3) + 4));                           /* mDown */
    stfs(base, self + GKC_VERT_Z, ctx->f[1].d);
    FL(1, frsp(ctx->f[4].d - ctx->f[5].d));               /* x.y = R - L */
    FL(0, frsp(ctx->f[1].d - ctx->f[0].d));               /* y.y = x.y - vertical x.y */
    stfs(base, self + GKC_VERT_Y + 4, ctx->f[0].d);
    FL(0, frsp(ctx->f[0].d - ctx->f[2].d));               /* z.y = y.y - vertical y.y */
    gm_set_u32(self + GKC_VERT_X, 0);
    gm_set_u32(self + GKC_RAW_HELD, R(29));
    stfs(base, self + GKC_VERT_Y, ctx->f[3].d);
    stfs(base, self + GKC_VERT_X + 4, ctx->f[1].d);
    stfs(base, self + GKC_VERT_Z + 4, ctx->f[0].d);
    goto config;
keep:                                                      /* (no controller: the buttons stay) */
    NV_R(29, R(4));
    goto config;
remote:                                                    /* the remote (with a Nunchuk: x / z swapped) */
    R(5) = gm_u32(R(3) + 24);
    { int nunchuk = CMPU(R(7), 0) != 0;
      FL(0, ldfs(base, R(3) + 2848));
      NV_R(29, R(5) & 0x7FFFFFFFu);
      gm_set_u32(self + GKC_RAW_HELD, R(29));
      stfs(base, self + GKC_ACCEL, ctx->f[0].d);
      R(5) = gm_u32(R(3) + 2852); gm_set_u32(self + GKC_ACCEL + 4, R(5));
      FL(1, ldfs(base, R(3) + 2856));
      stfs(base, self + GKC_ACCEL + 8, ctx->f[1].d);
      if (nunchuk) { stfs(base, self + GKC_ACCEL, ctx->f[1].d); stfs(base, self + GKC_ACCEL + 8, ctx->f[0].d); } }
    R(5) = gm_u32(PLAYER_CHANNEL + R(6));
    R(6) = PAD_ADDITIONAL;
    R(5) = R(5) * 24;
    R(6) = R(6) + R(5); R(5) = gm_u32(R(6));               /* (lwzux: the channel's vertical accelerations) */
    R(7) = gm_u32(R(6) + 4);
    gm_set_u32(self + GKC_VERT_X, R(5)); gm_set_u32(self + GKC_VERT_X + 4, R(7));
    R(5) = gm_u32(R(6) + 12); R(7) = gm_u32(R(6) + 8);
    gm_set_u32(self + GKC_VERT_Y + 4, R(5)); gm_set_u32(self + GKC_VERT_Y, R(7));
    R(5) = gm_u32(R(6) + 20); R(6) = gm_u32(R(6) + 16);
    gm_set_u32(self + GKC_VERT_Z + 4, R(5)); gm_set_u32(self + GKC_VERT_Z, R(6));
    R(5) = gm_u32(R(3) + 76); gm_set_u32(self + GKC_ANGLE, R(5));
    R(3) = gm_u32(R(3) + 80); gm_set_u32(self + GKC_ANGLE + 4, R(3));
config:
    /* the buttons in the remote's layout, this frame's presses */
    R(3) = self; BL(0x8180B898u, hle_mod_fn_800B6080);    /* setConfigKey(mPrevRawHeld) */
    NV_R(28, R(3)); gm_set_u32(self + GKC_PREV_HELD, R(3));
    R(3) = self; R(4) = R(29); BL(0x8180B8ACu, hle_mod_fn_800B6080);   /* setConfigKey(mRawHeld) */
    R(4) = gm_u32(self + GKC_REPEAT_FIRST);
    R(9) = R(3) & ~R(28);                                  /* triggered */
    R(5) = gm_u32(self + GKC_REPEAT_NEXT);
    R(7) = 2;
    R(6) = gm_u32(self + GKC_REPEAT);
    R(8) = 0;
    R(11) = gm_u32(self + GKC_REPEAT_TIMER);
    R(10) = 1;
    gm_set_u32(self + GKC_HELD, R(3));
    gm_set_u32(self + GKC_TRIGGERED, R(9));
    /* the auto-repeat of down / up / right / left: a press repeats at once, a hold after the timer */
    ctx->ctr = 2;
    for (;;) {
        for (int half = 0; half < 2; half++) {
            R(12) = half ? (R(8) & 63) > 31 ? 0 : R(7) << (R(8) & 63) : i2_bit(R(8));
            R(0) = R(12) & R(9); CR0(ctx, R(0));
            if (R(0)) { R(6) |= R(12); R(11) = R(4); gm_set_u32(self + GKC_REPEAT, R(6)); }
            else {
                R(0) = R(12) & R(3); CR0(ctx, R(0));
                if (!R(0)) { GM_LOOP(); continue; }        /* (not held) */
                if (CMPU(R(11), 0) == 0) { R(6) |= R(12); gm_set_u32(self + GKC_REPEAT, R(6)); R(11) = R(5); }
                else R(11)--;
                GM_LOOP();
            }
            gm_set_u32(self + GKC_REPEAT_TIMER, R(11));
        }
        R(8) += 2;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    /* tilt, movement, shake */
    R(3) = self; BL(0x8180B974u, hle_mod_fn_800B61A0);
    FL(1, ldfs(base, self + GKC_ACCEL));
    FL(0, ldfs(base, self + GKC_ACCEL + 8));
    FL(2, ldfs(base, self + GKC_ACCEL + 4));
    FL(1, frsp(ctx->f[1].d * ctx->f[1].d));
    FL(0, frsp(ctx->f[0].d * ctx->f[0].d + ctx->f[1].d));
    FL(1, frsp(ctx->f[2].d * ctx->f[2].d + ctx->f[0].d));
    BL(0x8180B990u, sqrt__Q23EGG7Math_f_Ff_802BE470);      /* mMoveDistance = |accel| */
    R(3) = 0x81850000u;
    ctx->f[0].u = ld64(base, D_1_2);
    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
    if (CR_BIT(ctx, 0)) { R(3) = 0x81850000u; FL(1, ldfs(base, F_ONE)); }   /* (under 1.2: 1.0) */
    R(3) = self;
    stfs(base, self + GKC_MOVE_DIST, ctx->f[1].d);
    BL(0x8180B9B4u, hle_mod_fn_800B6250);
    R(3) = gm_u32(self + GKC_EXTRA_TRIG);
    if (CMPU(R(3), 0) != 0) { R(3) = 0; gm_set_u32(self + GKC_EXTRA_TRIG, 0); }
    R(3) = gm_u8(self + GKC_SHAKE + 1);
    if (CMPU(R(3), 1) == 0) { R(3) = 0x100; gm_set_u16(self + GKC_SHAKE, 0x100); }   /* (mShake = mShakeOld, mShakeOld = 0) */
}

/* ================================================================== dAcPyKey_c */
/* update: this frame's buttons for the player (none without a remote, the demo's under demo
   control), the shake-jump flags, the jump history */
static void pk_update(GM_CTX, gptr self) {
    I2_FN(0x81805380u);
    NV_R(31, self);
    R(4) = gm_u32(self + PK_REMOCON);
    R(5) = gm_u16(self + PK_DOWN); R(0) = gm_u16(self + PK_DOWN + 2);
    int none = CMPS(R(4), -1) == 0;
    gm_set_u16(self + PK_PREV_DOWN, (uint16_t)R(5)); gm_set_u16(self + PK_PREV_DOWN + 2, (uint16_t)R(0));
    if (none) {
        R(0) = 0; gm_set_u16(self + PK_DOWN, 0); gm_set_u16(self + PK_DOWN + 2, 0);
        return;
    }
    R(6) = gm_u16(self + PK_STATUS);
    R(0) = R(6) & 1; CR0(ctx, R(0));
    if (R(0)) { R(0) = 0; gm_set_u16(self + PK_DOWN, 0); gm_set_u16(self + PK_DOWN + 2, 0); }
    else {
        R(0) = R(6) & 0x80; CR0(ctx, R(0));
        if (R(0)) {                                        /* (demo control: the demo's buttons) */
            R(4) = gm_u16(self + PK_DEMO_DOWN); R(0) = gm_u16(self + PK_DEMO_DOWN + 2);
            R(0) = R(4) | R(0); gm_set_u16(self + PK_DOWN, (uint16_t)R(0));
            R(0) = R(0) & ~R(5); gm_set_u16(self + PK_DOWN + 2, (uint16_t)R(0));
        } else {
            R(0) = R(6) & 0x100; CR0(ctx, R(0));
            if (R(0)) { R(4) = 4; R(0) = 0; gm_set_u16(self + PK_DOWN, 4); gm_set_u16(self + PK_DOWN + 2, 0); }   /* (walk right) */
            else {
                R(5) = gm_u32(GK_INSTANCE);
                R(4) <<= 2;
                R(0) = R(6) & 2; CR0(ctx, R(0));
                R(5) = R(5) + R(4);
                R(4) = gm_u32(R(5) + 4); R(0) = gm_u32(R(4) + GKC_HELD);
                gm_set_u16(self + PK_DOWN, (uint16_t)R(0));
                R(4) = gm_u32(R(5) + 4); R(0) = gm_u32(R(4) + GKC_TRIGGERED);
                gm_set_u16(self + PK_DOWN + 2, (uint16_t)R(0));
                if (CR_BIT(ctx, 2) == 0) BL(0x81805454u, fn_8005E4A0);   /* clearCrossKey */
            }
        }
    }
    R(0) = gm_u16(self + PK_STATUS) & 0x40; CR0(ctx, R(0));
    if (R(0)) {
        R(3) = self; R(4) = 6; BL(0x8180546Cu, fn_8005E460);   /* offStatus(6) */
        R(0) = 10; gm_set_u32(self + PK_SHAKE_COOLDOWN, 10);
    }
    R(3) = gm_u32(self + PK_SHAKE_COOLDOWN);
    if (CMPS(R(3), 0) != 0) { R(0) = R(3) - 1; gm_set_u32(self + PK_SHAKE_COOLDOWN, R(0)); }
    R(4) = gm_u16(self + PK_STATUS);
    R(3) = 0;
    gm_set_u8(self + PK_SHAKE_JUMP + 1, 0);
    R(0) = R(4) & 1; CR0(ctx, R(0));
    gm_set_u8(self + PK_SHAKE_JUMP, 0);
    if (!R(0)) {
        R(0) = R(4) & 0x100; CR0(ctx, R(0));
        if (!R(0)) {
            R(0) = R(4) & 0x80; CR0(ctx, R(0));
            if (R(0)) {                                    /* (the demo's shake) */
                R(0) = gm_u16(self + PK_DEMO_SHAKE);
                gm_set_u8(self + PK_SHAKE_JUMP + 1, (uint8_t)R(0)); gm_set_u8(self + PK_SHAKE_JUMP, (uint8_t)R(0));
            } else {
                R(0) = gm_u32(self + PK_SHAKE_COOLDOWN);
                if (CMPS(R(0), 0) == 0) {
                    R(0) = gm_u32(self + PK_REMOCON); R(3) = gm_u32(GK_INSTANCE);
                    R(0) <<= 2; R(3) = R(3) + R(0);
                    R(3) = gm_u32(R(3) + 4); R(0) = gm_u8(R(3) + GKC_SHAKE);
                    if (CMPS(R(0), 0) != 0) { R(0) = 1; gm_set_u8(self + PK_SHAKE_JUMP + 1, 1); gm_set_u8(self + PK_SHAKE_JUMP, 1); }
                }
            }
        }
    }
    R(0) = gm_u8(self + PK_HIP_ATK + 1);
    if (CMPS(R(0), 0) == 0) { R(0) = 0; gm_set_u8(self + PK_HIP_ATK + 2, 0); gm_set_u8(self + PK_HIP_ATK, 0); }
    NV_R(29, 0);
    gm_set_u8(self + PK_HIP_ATK + 1, 0);
    R(3) = self; NV_R(30, self);
    for (int k = 9; k >= 1; k--) {                          /* (the histories move up one frame) */
        R(0) = gm_u32(self + PK_JUMP_TRIG_HIST + 4 * (k - 1)); gm_set_u32(self + PK_JUMP_TRIG_HIST + 4 * k, R(0));
        R(0) = gm_u32(self + PK_JUMP_BTN_HIST + 4 * (k - 1)); gm_set_u32(self + PK_JUMP_BTN_HIST + 4 * k, R(0));
    }
    BL(0x818055B4u, fn_8005E6E0);                          /* triggerJump */
    gm_set_u32(self + PK_JUMP_TRIG_HIST, R(3));
    R(3) = self; BL(0x818055C0u, fn_8005E740);             /* buttonJump */
    gm_set_u32(self + PK_JUMP_BTN_HIST, R(3));
    gm_set_u16(self + PK_DEMO_DOWN + 2, 0); gm_set_u16(self + PK_DEMO_SHAKE, 0);
}
/* triggerOne / buttonOne: the "1" (run / fire) button - B with a Nunchuk or a GameCube pad */
static uint32_t pk_one(GM_CTX, gptr self, uint32_t field) {
    R(4) = 0x80430000u; R(5) = gm_u32(self + PK_REMOCON);
    R(4) = gm_u32(GK_INSTANCE);
    R(5) <<= 2;
    R(3) = gm_u16(self + field);
    R(4) = R(4) + R(5);
    R(4) = gm_u32(R(4) + 4); R(4) = gm_u32(R(4) + GKC_TYPE);
    R(4) -= 1;
    int nunchuk = CMPU(R(4), 2) < 0;
    R(4) = nunchuk ? 0x400 : 0x200;
    R(3) = R(4) & R(3);
    return R(3);
}
/* triggerJumpBuf(frames): a jump pressed within the last frames (at most 10) */
static uint32_t pk_triggerJumpBuf(GM_CTX, gptr self, uint32_t frames) {
    R(0) = gm_u32(self + PK_REMOCON);
    if (CMPS(R(0), -1) == 0) { R(3) = 0; return 0; }
    if (CMPS(frames, 10) > 0) frames = R(4) = 10;
    R(3) = self + PK_JUMP_TRIG_HIST;
    ctx->ctr = frames;
    if (CMPS(frames, 0) > 0)
        for (;;) {
            R(0) = gm_u32(R(3));
            if (CMPS(R(0), 0) != 0) { R(3) = 1; return 1; }
            R(3) += 4;
            if (--ctx->ctr == 0) break;
            GM_LOOP();
        }
    R(3) = 0;
    return 0;
}

/* ================================================================== hle entry points
   Verified memory: the object (the cores for dGameKey_c's loops). The calls these make change
   nothing else (the cores' controllers / replays are only read). */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
#define CORE(i) gm_u32(SELF + GK_CORES + 4 * (i)), GKC_SIZE
#define GK_MEM CORE(0), CORE(1), CORE(2), CORE(3), CORE(4), CORE(5), CORE(6), CORE(7)
static void key_selftest(GM_CTX, gptr key);
#ifdef GM_PY_KEY_OFF
/* (written but off, not in hle_funcs.txt: no input reaches them - the module builds its instance
   with its own static constructor and never destroys it; buttonOne is not called by the inputs.
   The constructor and destructor allocate / free, so they would be checked by A/B, not verify) */
GM_HLE(mod_fn_800B5930)                                               { gk_ctor(GM_PASS, SELF); }
GM_HLE(mod_fn_800B59B0)                                               { gk_dtor(GM_PASS, SELF, A(1)); }
GM_HLE_INT (mod_fn_8005E5D0, SELF, PK_SIZE)                           { pk_one(GM_PASS, SELF, PK_DOWN); }
#endif
GM_HLE_VOID(mod_fn_800B5A60, GK_MEM)                                  { gk_allclear(GM_PASS, SELF); }
GM_HLE_INT (mod_read__10dGameKey_cFv, GK_MEM)                         { gk_read(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_800B5C60, SELF, GKC_SIZE)                          { gkc_read(GM_PASS, SELF); }
GM_HLE_INT (mod_fn_800B6080, SELF, GKC_SIZE)                          { gkc_setConfigKey(GM_PASS, SELF, A(1)); }
GM_HLE_VOID(mod_fn_800B61A0, SELF, GKC_SIZE)                          { gkc_handleTilting(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_800B6250, SELF, GKC_SIZE)                          { gkc_setShakeY(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_8005E040, SELF, PK_SIZE)                           { key_selftest(GM_PASS, SELF); pk_update(GM_PASS, SELF); }
GM_HLE_INT (mod_fn_8005E590, SELF, PK_SIZE)                           { pk_one(GM_PASS, SELF, PK_DOWN + 2); }
GM_HLE_INT (mod_fn_8005E8B0, SELF, PK_SIZE)                           { pk_triggerJumpBuf(GM_PASS, SELF, A(1)); }

/* ================================================================== self-test (RT_GM_SELFTEST=py_key)
   On the first player's key and the eight live cores, random (players 0-7, every controller type,
   button bits, motion values also NaN / huge, timers, demo flags, jump histories) - the controllers
   and replays they read are the game's own at that moment. */
static const gm_test_t key_tests[] = {
    GM_TEST(mod_fn_800B5A60, 0, "!G"),
    GM_TEST(mod_read__10dGameKey_cFv, GMV_RET, "!G"),
    GM_TEST(mod_fn_800B5C60, 0, "!C"),
    GM_TEST(mod_fn_800B6080, GMV_RET, "!CI"),
    GM_TEST(mod_fn_800B61A0, 0, "!C"),
    GM_TEST(mod_fn_800B6250, 0, "!C"),
    GM_TEST(mod_fn_8005E040, 0, "!K"),
    GM_TEST(mod_fn_8005E590, GMV_RET, "!K"),
#ifdef GM_PY_KEY_OFF
    GM_TEST(mod_fn_8005E5D0, GMV_RET, "!K"),
#endif
    GM_TEST(mod_fn_8005E8B0, GMV_RET, "!Kj"),
};
static gptr key_obj, key_cores[8], key_core_vt[8];
static uint32_t key_float(void) {
    static const float nice[] = { 0.0f, 1.0f, -1.0f, 0.28f, 0.3f, 1.2f, 2.0f, -0.5f, 1e-3f };
    uint32_t r = gm_rand(), u; float f;
    switch (r % 4) {
    case 0: f = nice[gm_rand() % 9]; break;
    case 1: f = (float)((int32_t)(gm_rand() % 8001) - 4000) / 1000.0f; break;
    case 2: return gm_rand();                              /* (any bits: NaN, huge) */
    default: f = (float)((int32_t)(gm_rand() % 201) - 100) / 100.0f; break;
    }
    memcpy(&u, &f, 4); return u;
}
static void key_randomize(GM_CTX, int round) {
    (void)ctx; (void)base;
    for (int i = 0; i < 8; i++) {
        gptr c = key_cores[i];
        gm_set_u32(c, key_core_vt[i]);
        gm_set_u32(c + GKC_PLAYER_NO, gm_rand() % 8);
        gm_set_u32(c + GKC_TYPE, gm_rand() % 5);
        for (uint32_t a = GKC_RAW_HELD; a < GKC_REPEAT; a += 4) gm_set_u32(c + a, gm_rand() & gm_rand());
        gm_set_u32(c + GKC_REPEAT, gm_rand() & gm_rand());
        gm_set_u32(c + GKC_REPEAT_TIMER, gm_rand() % 4 ? gm_rand() % 3 : gm_rand());
        gm_set_u32(c + GKC_REPEAT_FIRST, gm_rand() % 30); gm_set_u32(c + GKC_REPEAT_NEXT, gm_rand() % 10);
        gm_set_u32(c + GKC_EXTRA_TRIG, gm_rand() % 2 ? 0 : gm_rand());
        for (uint32_t a = GKC_ACCEL; a < GKC_SHAKE; a += 4) gm_set_u32(c + a, key_float());
        for (uint32_t a = GKC_SHAKE; a < GKC_SIZE; a++) gm_set_u8(c + a, gm_rand() % 3 ? gm_rand() % 6 : gm_rand());
    }
    gptr k = key_obj;
    gm_set_u32(k + PK_REMOCON, (uint32_t)((int32_t)(gm_rand() % 9) - 1));
    for (uint32_t a = PK_DOWN; a < PK_STATUS; a += 2) gm_set_u16(k + a, gm_rand() & gm_rand());
    uint32_t st = gm_rand(); gm_set_u16(k + PK_STATUS, round % 2 ? st & (st >> 16) & 0x1FF : st);
    for (uint32_t a = PK_HIP_ATK; a < PK_SHAKE_COOLDOWN; a++) gm_set_u8(k + a, gm_rand() % 3 ? gm_rand() % 2 : gm_rand());
    gm_set_u32(k + PK_SHAKE_COOLDOWN, gm_rand() % 3 ? gm_rand() % 3 : gm_rand() % 12);
    gm_set_u32(k + PK_SHAKE_COOLDOWN + 4, gm_rand());
    for (uint32_t a = PK_JUMP_TRIG_HIST; a < PK_SIZE; a += 4) gm_set_u32(k + a, gm_rand() % 5 ? 0 : gm_rand() % 3 ? 1 : gm_rand());
}
static uint32_t key_arg(char k) {
    switch (k) {
    case 'G': return gm_u32(GK_INSTANCE);
    case 'C': return key_cores[gm_rand() % 8];
    case 'K': return key_obj;
    case 'I': return gm_rand() % 4 ? gm_rand() & gm_rand() : gm_rand();   /* (input bits) */
    case 'j': return (uint32_t)((int32_t)(gm_rand() % 18) - 3);          /* (frames, also <= 0 / > 10) */
    default:  return 0xDEADBEEFu;
    }
}
static void key_selftest(GM_CTX, gptr key) {
    if (!gm_selftest_wanted("py_key")) return;
    gptr gk = gm_u32(GK_INSTANCE);
    key_obj = key;
    gptr ranges[18] = { key, PK_SIZE };
    for (int i = 0; i < 8; i++) {
        key_cores[i] = gm_u32(gk + GK_CORES + 4 * i); key_core_vt[i] = gm_u32(key_cores[i]);
        ranges[2 + 2 * i] = key_cores[i]; ranges[3 + 2 * i] = GKC_SIZE;
    }
    const gm_selftest_t t = { "py_key", key_tests, (int)(sizeof key_tests / sizeof *key_tests), 300,
                              ranges, 9, key_randomize, key_arg };
    gm_selftest(GM_PASS, &t);
}
