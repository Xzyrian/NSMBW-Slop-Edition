/* gm_d_enemy_carry.c - dEnemyCarry_c, the base of enemies a player can pick up and throw
 * (d_enemy_carry.cpp, 0x8009EAF0-0x8009F5F0). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_enemy_carry.cpp) and checked against the
 * recompiled USA rev 2 code. The 8-player module replaces initializeState_Throw (its
 * mNoHitPlayer is u8[8]): it stays recompiled. Not decompiled: the static initialiser and its
 * two getters; the state-ID template copies are in gm_state_ids.c.
 *
 * dEnemyCarry_c (after dEn_c): +0x524 mWasDropped  +0x525 mThrowSpeed. Used from dActor_c /
 * dEn_c: +0x12C mCarryingFlags (1: release, 2: throw)  +0x130 mThrowDirection
 * +0x175 mCc attack  +0x178 mCc vs-kind  +0x1E7 mCc ami line  +0x2D1 mBc ami line  +0x2DC mRc
 * vtable (+0x60): +0x0D4 changeState, +0x280 setThrowSpeed, +0x284 setThrowChangeState,
 * +0x288 setPutOnChangeState. dAcPy_c: +0x1035 mAmiLayer. */
#include "gm.h"
#include "gm_nv.h"

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f      /* (gm.h: the PowerPC function's frame and prologue) */
#define VT(o, off) gm_u32(gm_u32((o) + 0x60) + (off))

#define STATE_THROW   0x80357B74u        /* dEnemyCarry_c::StateID_Throw */
#define DEATH_BG_IN   0x802F04E8u        /* setDeathInfo_CarryBgIn's literal, constant part */
#define AMI_LINE      0x8042BB18u        /* l_Ami_Line */
#define BASE_ANGLE_Y  0x8042C1A4u        /* l_base_angleY */
#define EN_MUKI       0x8042C1A0u        /* l_EnMuki (s8) */
#define VTABLE        0x803130F0u
#define F_EN_CT       0x80094E80u        /* dEn_c::dEn_c */
#define F_EN_DT       0x80095130u        /* dEn_c::~dEn_c */
#define F_FREE        0x80162920u        /* (operator delete, game heap) */
#define F_GET_PLAYER  0x8005F900u
#define F_CANCEL_CARRY 0x8012E510u
#define F_SET_RIDE    0x800D98F0u        /* dRc_c::setRide */
#define F_WALL_AND_BG 0x800963B0u        /* dEn_c::checkWallAndBg */

static gptr player(GM_CTX, gptr self) { return GM_CALL(F_GET_PLAYER, 1, (uint32_t)(int32_t)gm_s8(self + 0x38D)); }

static gptr carry_ctor(GM_CTX, gptr self) {
    FN(0x8009EB10);
    GM_CALLR(0x8009EB28u, F_EN_CT, 1, self);
    gm_set_u32(self + 0x60, VTABLE);
    return self;
}
static gptr carry_dtor(GM_CTX, gptr self, int32_t flags) {
    FN(0x8009F010);
    if (self) {
        GM_CALLR(0x8009F03Cu, F_EN_DT, 2, self, 0);
        if (flags > 0) GM_CALLR(0x8009F04Cu, F_FREE, 1, self);
    }
    return self;
}
/* setThrowSpeed(actor): 2.5 or 3, plus half the thrower's speed when thrown the way it moves
   (the clamp against mSpeedMax.x after it changes nothing - kept out) */
static void set_throw_speed(GM_CTX, gptr self, gptr actor) {
    uint32_t dir = gm_u8(self + 0x348);
    double s = LF(ctx->r[2] - (gm_u8(self + 0x525) ? 28112 : 28120) + 4 * dir);   /* smc_DIR_MODE1 / 0 */
    double ax = LF(actor + 0xE8);
    if (dir == (uint32_t)(ax < R2F(28104))) s = frsp(s + frsp(R2F(28100) * ax));
    double z = R2F(28104);
    SF(self + 0xE8, s); SF(self + 0xEC, z); SF(self + 0xF0, z);
}
/* setDeathInfo_CarryBgIn(actor): thrown into a wall - fall out */
static void death_bg_in(GM_CTX, gptr self, gptr actor) {
    FN(0x8009EC30);
    gptr t = f + 8;
    for (int i = 0; i < 8; i++) gm_set_u32(t + 4 * i, gm_u32(DEATH_BG_IN + 4 * i));
    gm_set_u8(t + 28, gm_u8(self + 0x348));
    uint32_t plr = gm_u8(GM_CALLR(0x8009ECA8u, VT(actor, 0x6C), 1, actor));
    gm_set_u8(t + 29, plr);
    for (int i = 0; i < 4; i++) SF(self + 0x414 + 4 * i, LF(t + 4 * i));
    for (int i = 4; i < 7; i++) gm_set_u32(self + 0x414 + 4 * i, gm_u32(t + 4 * i));
    gm_set_u8(self + 0x430, gm_u8(t + 28)); gm_set_u8(self + 0x431, plr);
    gm_set_u8(self + 0x432, 1);
}
/* initializeState_Carry: on the other layer of a fence than the player, hits like a shell */
static void carry_begin(GM_CTX, gptr self) {
    FN(0x8009ED10);
    gptr pl = player(GM_PASS, self);
    gm_set_u8(self + 0x391, gm_u8(pl + 0x1035) == 1 ? 0 : 1);
    uint32_t line = gm_u8(AMI_LINE + gm_u8(self + 0x391));
    uint32_t vs = gm_u32(self + 0x178);
    gm_set_u8(self + 0x1E7, line); gm_set_u8(self + 0x2D1, line);
    gm_set_u32(self + 0x178, vs | 0x80);                                  /* CC_KIND_KILLER */
    gm_set_u8(self + 0x175, 9);                                           /* CC_ATTACK_SHELL */
    GM_CALLR(0x8009ED88u, F_SET_RIDE, 2, self + 0x2DC, 0);
    gm_set_u8(self + 0x524, 0);
}
static void carry_end(GM_CTX, gptr self) {
    FN(0x8009EDB0);
    gptr pl = player(GM_PASS, self);
    GM_CALLR(0x8009EDDCu, F_CANCEL_CARRY, 2, pl, self);
    uint32_t vs = gm_u32(self + 0x178);
    gm_set_u8(self + 0x175, 0);
    gm_set_u32(self + 0x178, vs & ~0x80u);
    GM_CALLR(0x8009EDFCu, F_SET_RIDE, 2, self + 0x2DC, 0);
    gm_set_u32(self + 0x274, 0);
    gm_set_u32(self + 0x12C, gm_u32(self + 0x12C) & ~3u);
}
/* executeState_Carry: on release - out of a wall, or thrown / put down in front */
static void carry_execute(GM_CTX, gptr self) {
    FN(0x8009EE30);
    gptr pl = player(GM_PASS, self);
    if (!(gm_u32(self + 0x12C) & 1)) return;
    uint32_t dir = gm_u8(self + 0x130);
    gm_set_u8(self + 0x348, dir);
    gm_set_u16(self + 0x102, gm_u16(BASE_ANGLE_Y + 2 * dir));
    if (GM_CALLR(0x8009EE88u, F_WALL_AND_BG, 1, self)) { GM_CALLR(0x8009EE9Cu, 0x8009EC30u, 2, self, pl); return; }   /* setDeathInfo_CarryBgIn */
    dir = gm_u8(self + 0x348);
    if (!(gm_u32(self + 0x274) & (21u << dir))) {
        int32_t m = gm_s8(EN_MUKI + dir);
        gm_set_u32(f + 8, 0x43300000u); gm_set_u32(f + 12, (uint32_t)m ^ 0x80000000u);
        double md = frsp((double)m);
        SF(self + 0xAC, frsp(LF(self + 0xAC) + frsp(R2F(28096) * md)));
    }
    gm_set_u8(self + 0x38D, gm_u8(GM_CALLR(0x8009EF0Cu, VT(pl, 0x6C), 1, pl)));
    if (gm_u32(self + 0x12C) & 2) {
        GM_CALLR(0x8009EF38u, VT(self, 0x280), 2, self, pl);                            /* setThrowSpeed */
        GM_CALLR(0x8009EF4Cu, VT(self, 0x284), 1, self);                                /* setThrowChangeState */
    } else {
        SF(self + 0xB0, frsp(LF(self + 0xB0) + R2F(28092)));
        GM_CALLR(0x8009EF74u, VT(self, 0x288), 1, self);                                /* setPutOnChangeState */
    }
}

/* ================================================================== hle entry points
   All written but off: no test run reaches a carryable enemy yet (enable after one does). */
#define A(i) GM_ARG(i)
GM_HLE(fn_8009EB10) { GM_RET(carry_ctor(GM_PASS, A(0))); }                                   /* dEnemyCarry_c::dEnemyCarry_c */
GM_HLE(fn_8009F010) { GM_RET(carry_dtor(GM_PASS, A(0), (int32_t)A(1))); }                   /* ::~dEnemyCarry_c */
GM_HLE(fn_8009EB50) { set_throw_speed(GM_PASS, A(0), A(1)); }                               /* ::setThrowSpeed */
GM_HLE(fn_8009EBF0) { gm_set_u8(A(0) + 0x524, 0); GM_CALL(VT(A(0), 0xD4), 2, A(0), STATE_THROW); }   /* ::setThrowChangeState */
GM_HLE(fn_8009EC10) { gm_set_u8(A(0) + 0x524, 1); GM_CALL(VT(A(0), 0xD4), 2, A(0), STATE_THROW); }   /* ::setPutOnChangeState */
GM_HLE(fn_8009EC30) { death_bg_in(GM_PASS, A(0), A(1)); }                                   /* ::setDeathInfo_CarryBgIn */
GM_HLE(fn_8009ED10) { carry_begin(GM_PASS, A(0)); }                                         /* ::initializeState_Carry */
GM_HLE(fn_8009EDB0) { carry_end(GM_PASS, A(0)); }                                           /* ::finalizeState_Carry */
GM_HLE(fn_8009EE30) { carry_execute(GM_PASS, A(0)); }                                       /* ::executeState_Carry */
GM_HLE(fn_8009EFD0) {                                                                       /* ::finalizeState_Throw */
    gptr s = A(0); double z = R2F(28104);
    gm_set_u32(s + 0x178, gm_u32(s + 0x178) & ~0xA0u); gm_set_u8(s + 0x175, 0);
    SF(s + 0x11C, z); SF(s + 0xF4, z);
}
GM_HLE(fn_8009F000) { }                                                                     /* ::executeState_Throw */
