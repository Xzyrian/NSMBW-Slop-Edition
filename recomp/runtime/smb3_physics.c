/* smb3_physics.c - Super Mario Bros. 3's player movement (see smb3_physics.h).
 * Routine by routine from SMB3Disassembly/PRG/prg008.asm (labels in the comments). */
#include "smb3_physics.h"
#include <string.h>

/* smb3.asm */
#define PLAYER_TOPWALKSPEED   0x18
#define PLAYER_TOPRUNSPEED    0x28
#define PLAYER_TOPPOWERSPEED  0x38
#define PLAYER_MAXSPEED       0x40
#define PLAYER_JUMP           (-0x38)
#define PLAYER_TAILWAG_YVEL   0x10
#define PLAYER_FLY_YVEL       (-0x18)
#define PLAYER_SWIMSTART_YVEL (-0x20)
#define PLAYER_SWIM_YVEL      0x20
#define PLAYER_FROG_MAXYVEL   (-0x20)
#define FALLRATE_MAX          0x40              /* (prg024.asm) */
/* Player_Frame values (smb3.asm PF_*) */
enum { PF_KICK_SMALL = 0x42, PF_KICK_BIG = 0x2D, PF_SKID_SMALL = 0x41, PF_SKID_BIG = 0x30,
       PF_FALLBIG = 0x06, PF_FASTJUMPBIG = 0x38, PF_JUMPFALLSMALL = 0x40, PF_FASTJUMPFALLSMALL = 0x4E,
       PF_JUMPBIG = 0x4F, PF_JUMPRACCOON = 0x50, PF_SOMERSAULT_BASE = 0x1A, PF_WALKSMALL_BASE = 0x3E,
       PF_WALKBIG_BASE = 0x0C, PF_WALKSPECIAL_BASE = 0x00, PF_FROGHOP_BASE = 0x15, PF_INPIPE_SMALL = 0x32,
       PF_INPIPE_BIG = 0x05, PF_SWIMACTIVE_SMALL = 0x46, PF_SWIMACTIVE_BIG = 0x34, PF_FROGSWIM_UPBASE = 0x12,
       PF_FROGSWIM_IDLEBASE = 0x1F, PF_FROGSWIM_LRBASE = 0x21, PF_FROGSWIM_DOWNBASE = 0x24,
       PF_SWIMIDLE_SMALL = 0x46, PF_SWIMIDLE_BIG = 0x3C, PF_TAILATKGROUND_BASE = 0x03, PF_TAILATKINAIR_BASE = 0x09,
       PF_DUCK_NOTRACCOON = 0x0F, PF_DUCK_RACCOON = 0x07, PF_THROWONGROUND_BASE = 0x0E, PF_THROWINAIR_BASE = 0x34,
       PF_RUNSMALL_BASE = 0x4C, PF_RUNBIG_BASE = 0x39, PF_TAILWAGFLY_BASE = 0x36, PF_TAILWAGFALL = 0x08,
       PF_HOLDSMALL_BASE = 0x2E, PF_HOLDBIG_BASE = 0x29 };

/* ---- tables (prg008.asm) ---- */
static const int8_t Player_XAccelMain[] = {
    /* F   N   S   X      F   N   S   X  (without B, with B) */
    -1,  0,  2,  0,   -1,  0,  2,  0,   /* Small */
    -1,  0,  2,  0,   -1,  0,  2,  0,   /* Big */
    -1,  0,  2,  0,   -1,  0,  2,  0,   /* Fire */
    -1,  0,  2,  0,   -1,  0,  2,  0,   /* Leaf */
    -1,  2,  2,  0,   -1,  2,  2,  0,   /* Frog */
    -1,  0,  2,  0,   -1,  0,  2,  0,   /* Tanooki */
    -1,  0,  2,  0,   -1,  0,  2,  0,   /* Hammer */
    /* Player_XAccelMain_UW (offset 56): on the ground / swimming above it */
    -1,  1,  1,  0,   -1,  0,  0,  0,
    /* (Player_Slippery: offsets $40, $48) */
    -1,  0,  0,  0,   -1,  0,  1,  0,
    -1,  0,  0,  0,   -1,  0,  0,  0 };
static const uint8_t Player_XAccelPseudoFrac[] = {
    0x60, 0xE0, 0x00, 0x00,   0x60, 0xE0, 0x00, 0x00,   /* Small */
    0x20, 0xE0, 0x00, 0x00,   0x20, 0xE0, 0x00, 0x00,   /* Big */
    0x20, 0xE0, 0x00, 0x00,   0x20, 0xE0, 0x00, 0x00,   /* Fire */
    0x20, 0xE0, 0x00, 0x00,   0x20, 0xE0, 0x00, 0x00,   /* Leaf */
    0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00,   /* Frog */
    0x60, 0xE0, 0x00, 0x00,   0x60, 0xE0, 0x00, 0x00,   /* Tanooki */
    0x60, 0xE0, 0x00, 0x00,   0x60, 0xE0, 0x00, 0x00,   /* Hammer */
    /* Player_XAccelPseudoFrac_UW */
    0x30, 0x00, 0x00, 0x00,   0xE0, 0x30, 0x80, 0x00,
    0xA0, 0xE0, 0xC0, 0x00,   0xA0, 0xE0, 0x20, 0x00,
    0xD0, 0xE0, 0x60, 0x00,   0xD0, 0xE0, 0xC0, 0x00,
    0x10, 0xF0 };
#define XACCEL_UW 56                            /* (Player_XAccelMain_UW - Player_XAccelMain) */
static const uint8_t Player_WalkAnimTickMax[] = {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x01, 0x01,
    /* (read past the end at |XVel| $48+: the next bytes, Player_RootJumpVel and on) */ 0xC8, 0x00, 0x02 };
/* Player_SpeedJumpInc and the bytes after it (the index reaches 4 at |XVel| $40) */
static const uint8_t Player_SpeedJumpInc[] = {0x00, 0x02, 0x04, 0x08, 0x00, 0x03, 0x06, 0x08};
static const uint8_t Player_SomersaultFlipBits[] = {0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xC0, 0x80, 0x01};
static const uint8_t PowerUp_Ability[SMB3_SUITS] = {0x00, 0x00, 0x00, 0x01, 0x02, 0x01, 0x02};   /* (prg000.asm) bit 0: flies */
static const uint8_t Player_WalkFramesByPUp[] = {
    PF_WALKSMALL_BASE, PF_WALKSMALL_BASE + 1, PF_WALKSMALL_BASE, PF_WALKSMALL_BASE + 1,
    PF_WALKBIG_BASE, PF_WALKBIG_BASE + 1, PF_WALKBIG_BASE + 2, PF_WALKBIG_BASE + 1,
    PF_WALKBIG_BASE, PF_WALKBIG_BASE + 1, PF_WALKBIG_BASE + 2, PF_WALKBIG_BASE + 1,
    PF_WALKSPECIAL_BASE, PF_WALKSPECIAL_BASE + 1, PF_WALKSPECIAL_BASE + 2, PF_WALKSPECIAL_BASE + 1,
    PF_WALKSPECIAL_BASE, PF_WALKSPECIAL_BASE + 1, PF_WALKSPECIAL_BASE + 2, PF_WALKSPECIAL_BASE + 1,
    PF_WALKSPECIAL_BASE, PF_WALKSPECIAL_BASE + 1, PF_WALKSPECIAL_BASE + 2, PF_WALKSPECIAL_BASE + 1,
    PF_WALKBIG_BASE, PF_WALKBIG_BASE + 1, PF_WALKBIG_BASE + 2, PF_WALKBIG_BASE + 1 };
static const uint8_t Player_SkidFrame[] = {PF_SKID_SMALL, PF_SKID_BIG};
static const uint8_t Player_SwimActiveFrames[] = {
    PF_SWIMACTIVE_BIG, PF_SWIMACTIVE_BIG + 1, PF_SWIMACTIVE_BIG + 2, PF_SWIMACTIVE_BIG, PF_SWIMACTIVE_BIG + 1, PF_SWIMACTIVE_BIG + 2,
    PF_SWIMIDLE_SMALL, PF_SWIMIDLE_SMALL + 1, PF_SWIMIDLE_SMALL + 2, PF_SWIMIDLE_SMALL, PF_SWIMIDLE_SMALL + 1, PF_SWIMIDLE_SMALL + 2 };
static const uint8_t Player_SwimIdleFrames[] = {
    PF_SWIMIDLE_BIG, PF_SWIMIDLE_BIG + 1, PF_SWIMIDLE_BIG - 8, PF_SWIMIDLE_BIG + 1,
    PF_SWIMIDLE_SMALL, PF_SWIMIDLE_SMALL, PF_SWIMIDLE_SMALL + 3, PF_SWIMIDLE_SMALL + 3 };
static const uint8_t Player_TailAttackFrames[] = {
    PF_TAILATKGROUND_BASE, PF_TAILATKGROUND_BASE + 1, PF_TAILATKGROUND_BASE, PF_TAILATKGROUND_BASE + 2, PF_TAILATKGROUND_BASE,
    PF_TAILATKINAIR_BASE, PF_TAILATKINAIR_BASE - 5, PF_TAILATKINAIR_BASE, PF_TAILATKINAIR_BASE - 4, PF_TAILATKINAIR_BASE };
static const uint8_t Player_DuckFrame[] = {PF_DUCK_NOTRACCOON, PF_DUCK_RACCOON};
static const uint8_t Player_FireOnGround[] = {PF_THROWONGROUND_BASE, PF_THROWONGROUND_BASE + 3, PF_THROWONGROUND_BASE + 2,
                                              /* Player_FireInAir */ PF_THROWINAIR_BASE, PF_THROWINAIR_BASE + 1, PF_THROWINAIR_BASE + 2};
static const uint8_t Player_FrogHopFrames[] = {PF_FROGHOP_BASE, PF_FROGHOP_BASE + 2, PF_FROGHOP_BASE + 1, PF_FROGHOP_BASE};
static const uint8_t Player_SpreadEagleFrames[] = {
    PF_RUNBIG_BASE, PF_RUNBIG_BASE + 1, PF_RUNBIG_BASE + 2, PF_RUNBIG_BASE + 1,
    PF_RUNSMALL_BASE, PF_RUNSMALL_BASE + 1, PF_RUNSMALL_BASE, PF_RUNSMALL_BASE + 1 };
static const uint8_t Player_TailWagFlyFrames[] = {
    PF_TAILWAGFLY_BASE + 2, PF_TAILWAGFLY_BASE + 1, PF_TAILWAGFLY_BASE,
    PF_TAILWAGFLY_BASE + 1, PF_TAILWAGFLY_BASE + 2, PF_TAILWAGFLY_BASE,
    PF_JUMPRACCOON, PF_JUMPRACCOON, PF_JUMPRACCOON,
    PF_TAILWAGFALL + 2, PF_TAILWAGFALL + 1, PF_TAILWAGFALL };
static const uint8_t Player_HoldingFrames[] = {
    PF_HOLDBIG_BASE, PF_HOLDBIG_BASE + 1, PF_HOLDBIG_BASE + 2, PF_HOLDBIG_BASE + 1,
    PF_HOLDSMALL_BASE, PF_HOLDSMALL_BASE + 1, PF_HOLDSMALL_BASE, PF_HOLDSMALL_BASE + 1 };
static const uint8_t Frog_SwimSoundMask[] = {0x03, 0x07};
static const uint8_t Frog_BaseFrame[] = {PF_FROGSWIM_DOWNBASE, PF_FROGSWIM_UPBASE, PF_FROGSWIM_LRBASE};
static const uint8_t Frog_FrameOffset[] = {0x02, 0x02, 0x02, 0x01, 0x00, 0x01, 0x02, 0x02};
static const int8_t Frog_Velocity[] = {16, -16};

static uint8_t negate(uint8_t a) { return (uint8_t)(0 - a); }
static uint8_t absv(uint8_t a) { return (a & 0x80) ? negate(a) : a; }

void smb3p_init(smb3_player *p, int suit, int facing_left) {
    memset(p, 0, sizeof *p);
    p->Player_Suit = (uint8_t)suit;
    p->Player_FlipBits = facing_left ? 0 : SMB3_HFLIP;
    p->Player_WalkFrame = 2;
}

/* Player_ApplyVelocity: the velocity's whole part (a 4-bit signed) and its fraction accumulated */
static int apply_velocity(uint8_t vel, uint8_t *frac) {
    uint8_t lo = (uint8_t)(vel << 4), whole = vel >> 4;
    int w = whole >= 8 ? (int)whole - 16 : (int)whole;
    int carry = *frac + lo > 0xFF; *frac = (uint8_t)(*frac + lo);
    return w + carry;
}
/* Player_ApplyXVelocity */
static int apply_x(smb3_player *p) {
    uint8_t a = absv(p->Player_XVel);
    if (a >= PLAYER_MAXSPEED) p->Player_XVel = (p->Player_XVel & 0x80) ? (uint8_t)-PLAYER_MAXSPEED : PLAYER_MAXSPEED;
    return apply_velocity(p->Player_XVel, &p->Player_XVelFrac);   /* (Player_XVelAdj: conveyors - none here) */
}
/* Player_ApplyYVelocity */
static int apply_y(smb3_player *p) {
    if (!(p->Player_YVel & 0x80) && p->Player_YVel >= FALLRATE_MAX) p->Player_YVel = FALLRATE_MAX;
    return apply_velocity(p->Player_YVel, &p->Player_YVelFrac);
}

/* Player_GroundHControl from PRG008_ABA6 on (Player_UnderwaterHControl comes in there): y the
   index into the Player_XAccel tables so far, top the speed limit (Temp_Var14), mag |XVel| (Temp_Var3) */
static void hcontrol_tail(smb3_player *p, int y, uint8_t top, uint8_t mag) {
    uint8_t lr = p->Pad_Holding & (SMB3_LEFT | SMB3_RIGHT);
    int right;
    if (!lr) {
        if (p->Player_InAir || !p->Player_XVel) return;
        right = !(p->Player_XVel & 0x80);                              /* (friction towards 0: Y still the "F" offset) */
    } else {
        y += 2;                                                         /* ("skid") */
        if (!(lr & p->Player_MoveLR)) {
            y--;                                                        /* ("normal") */
            if (mag == top) return;
            if (!((int8_t)(mag - top) < 0)) {                           /* (BMI on the subtraction) */
                if (p->Player_InAir) return;
                y--;                                                    /* ("friction": over the top speed) */
            }
        }
        right = (p->Pad_Holding & SMB3_RIGHT) != 0;
    }
    uint8_t t1, t2;
    if (right) { t1 = Player_XAccelPseudoFrac[y]; t2 = (uint8_t)Player_XAccelMain[y]; }
    else {
        t1 = (uint8_t)(0 - Player_XAccelPseudoFrac[y]);
        t2 = (uint8_t)~(uint8_t)Player_XAccelMain[y];
        if (!t1) t2++;
    }
    int carry = t1 + p->Counter_Wiggly > 0xFF;                          /* (a semi-random carry: Counter_Wiggly) */
    p->Player_XVel = (uint8_t)(p->Player_XVel + t2 + carry);
}
static const uint8_t Player_UphillSpeedVals[] = {0x00, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10, 0x0F, 0x0E, 0x0D};
/* Player_GroundHControl (uphill speeds and slippery ground: NSMBW's - not here) */
static void ground_hcontrol(smb3_player *p, uint8_t mag) {
    uint8_t top = PLAYER_TOPWALKSPEED;
    if (p->Pad_Holding & SMB3_B) {
        if (!p->Player_InAir && mag >= PLAYER_TOPRUNSPEED && !((int8_t)(mag - PLAYER_TOPRUNSPEED) < 0)) p->Player_RunFlag++;
        top = PLAYER_TOPRUNSPEED;
        if (p->Player_Power == 0x7F) top = PLAYER_TOPPOWERSPEED;
    }
    (void)Player_UphillSpeedVals;
    int y = p->Player_Suit << 3;
    if (p->Pad_Holding & SMB3_B) y += 4;
    hcontrol_tail(p, y, top, mag);
}
/* Player_UnderwaterHControl */
static void underwater_hcontrol(smb3_player *p, uint8_t mag) {
    int y = XACCEL_UW;
    uint8_t top = 0x08;                                                 /* ("pretend like Player is definitely hitting UP") */
    if (p->Player_InAir) { top = 0xF8; y += 4; }                        /* (LDA #Pad_Input: the address of Pad_Input, $F8 - the disassembly's literal) */
    uint8_t air = p->Player_InAir; p->Player_InAir = 0;
    hcontrol_tail(p, y, top, mag);
    p->Player_InAir = air;
}

/* Player_JumpFlyFlutter */
static const uint8_t PRG008_AC22[] = {0xD0, 0xCE, 0xCC, 0xCA, 0xCA, 0xCA};
static void jump_fly_flutter(smb3_player *p) {
    if (p->Player_AllowAirJump) p->Player_AllowAirJump--;
    uint8_t tv1 = p->Pad_Input & SMB3_A;
    if (tv1 && (p->Player_AllowAirJump || !p->Player_InAir)) {
        p->jumped = 1;                                                  /* (SND_PLAYERJUMP) */
        if (p->Player_StarInv && p->Player_Power != 0x7F && !p->Player_IsHolding && p->Player_Suit && p->Player_Suit != SMB3_FROG) {
            p->Player_Flip = p->Player_Suit; p->Player_InAir = p->Player_Suit;   /* (mid air and somersaulting) */
            p->Player_AllowAirJump = 0;
        }
        uint8_t x = absv(p->Player_XVel) >> 4;
        p->Player_YVel = (uint8_t)((uint8_t)PLAYER_JUMP - Player_SpeedJumpInc[x]);
        p->Player_InAir = 1;
        p->Player_WagCount = 0; p->Player_AllowAirJump = 0;
        if (p->Player_Power == 0x7F && !p->Player_FlyTime) p->Player_FlyTime = 0x80;
    }
    if (!p->Player_InAir) {
        if (!(PowerUp_Ability[p->Player_Suit] & 1)) p->Player_FlyTime = 0;
    } else {
        uint8_t y = 5;
        if ((int8_t)p->Player_YVel < -0x20) {                           /* (CMP #-$20 / BGS: unsigned >= $E0) */
            if (p->Player_mGoomba) goto add;
            if (p->Pad_Holding & SMB3_A) { y = 1; goto add; }
        }
        p->Player_mGoomba = 0;
    add:
        p->Player_YVel = (uint8_t)(p->Player_YVel + y);
        if (p->Player_WagCount) p->Player_WagCount--;
        if ((PowerUp_Ability[p->Player_Suit] & 1) && tv1) p->Player_WagCount = 0x10;
        if (p->Player_WagCount) {
            /* RACCOON / TANOOKI TAIL WAG LOGIC: CMP #PLAYER_FLY_YVEL / BLS (BMI: the difference's sign) */
            if (!((int8_t)(uint8_t)(p->Player_YVel - (uint8_t)PLAYER_FLY_YVEL) < 0)) {
                uint8_t ny = (uint8_t)PLAYER_FLY_YVEL; int set = 1;
                if (p->Player_FlyTime) {
                    if (p->Player_FlyTime < 0x0F) { ny = 0xF0; if (!(p->Player_FlyTime & 0x08)) ny = 0; }
                } else {
                    set = 0;
                    if (!(p->Player_YVel & 0x80) && p->Player_YVel >= PLAYER_TAILWAG_YVEL) { ny = PLAYER_TAILWAG_YVEL; set = 1; }
                }
                if (set) p->Player_YVel = ny;
            }
        }
    }
    (void)PRG008_AC22;                                                  /* (Player_UphillSpeedIdx: NSMBW's slopes) */
}
/* Player_SwimV */
static void swim_v(smb3_player *p) {
    if (p->Pad_Input & SMB3_A) {
        p->swam = 1;                                                    /* (SND_PLAYERSWIM) */
        if (!p->Player_InAir) { p->Player_InAir = (uint8_t)PLAYER_SWIMSTART_YVEL; p->Player_YVel = (uint8_t)PLAYER_SWIMSTART_YVEL; }
        else p->Player_YVel = (uint8_t)(p->Player_YVel - PLAYER_SWIM_YVEL);
    }
    if (!p->Player_InAir) return;
    if ((p->Player_YVel & 0x80) || !(p->Counter_1 & 0x02)) p->Player_YVel++;
    uint8_t y = PLAYER_SWIM_YVEL, a = p->Player_YVel;
    if (a & 0x80) y = (uint8_t)PLAYER_SWIMSTART_YVEL;                   /* (Player_AboveTop: not here) */
    uint8_t r = (uint8_t)(a + PLAYER_SWIM_YVEL);
    if (!(r < PLAYER_MAXSPEED)) p->Player_YVel = y;
}
/* Player_SwimAnim */
static void swim_anim(smb3_player *p) {
    if (!p->Player_InAir) return;
    if (p->Pad_Input & SMB3_A) {
        if (!p->Player_SwimCnt) { p->Player_SwimCnt = 0; p->Counter_ByPlayerSpd = 0; p->Player_WalkAnimTicks = 0; }
        p->Player_SwimCnt++;
    }
    if (p->Player_SwimCnt) {
        uint8_t a = p->Counter_ByPlayerSpd;
        if (a >= 6) {
            if (--p->Player_SwimCnt) { p->Player_SwimCnt = 0; p->Counter_ByPlayerSpd = 0; p->Player_WalkAnimTicks = 0; p->Player_SwimCnt++; a = 0; }   /* (BNE PRG008_AD8C: restarts) */
            else a = 5;
        }
        if (!p->Player_Suit) a += 6;
        p->Player_Frame = Player_SwimActiveFrames[a > 11 ? 11 : a];
        return;
    }
    if (!p->Player_XVel) p->Player_WalkFrame = (p->Counter_1 & 0x30) >> 4;
    int y = p->Player_WalkFrame & 3; if (!p->Player_Suit) y += 4;
    p->Player_Frame = Player_SwimIdleFrames[y];
}
/* Player_CommonGroundAnims */
static void common_ground_anims(smb3_player *p) {
    uint8_t y = absv(p->Player_XVel) >> 3;
    p->Player_WalkAnimTicks++;
    if (!((int8_t)(p->Player_WalkAnimTicks - Player_WalkAnimTickMax[y < sizeof Player_WalkAnimTickMax ? y : sizeof Player_WalkAnimTickMax - 1]) < 0)) {
        p->Player_WalkAnimTicks = 0;
        p->Player_WalkFrame++; p->Counter_ByPlayerSpd++;
        if (!((int8_t)(p->Player_WalkFrame - 4) < 0)) p->Player_WalkFrame = 0;
    }
    if (!(p->Pad_Holding & (SMB3_LEFT | SMB3_RIGHT)) && !p->Player_XVel) p->Player_WalkFrame = 2;
    if (!p->Player_TailAttack && (p->Pad_Holding & (SMB3_LEFT | SMB3_RIGHT)))
        p->Player_FlipBits = (p->Pad_Holding & SMB3_LEFT) ? 0 : SMB3_HFLIP;
    p->Player_Frame = Player_WalkFramesByPUp[(p->Player_Suit << 2) | (p->Player_WalkFrame & 3)];
    p->skid = 0;
    if (!p->Player_InWater && !((uint8_t)(p->Player_XVel + 1) < 3) && (p->Player_MoveLR & p->Pad_Holding)) {
        /* (Player_MoveLR 2 = moving right AND PAD_LEFT 2: pressing the opposite way to the movement) */
        if (!p->Player_InAir) { p->skid = 1; p->Player_Frame = Player_SkidFrame[p->Player_Suit ? 1 : 0]; }   /* (SND_LEVELSKID) */
    }
    if (p->Player_IsDucking) p->Player_Frame = Player_DuckFrame[PowerUp_Ability[p->Player_Suit] & 1];
}
/* Player_SoarJumpFallFrame */
static void soar_jump_fall_frame(smb3_player *p) {
    if (p->Player_AllowAirJump || !p->Player_InAir || p->Player_IsDucking) return;
    uint8_t f = PF_FASTJUMPBIG;
    if (!p->Player_FlyTime) { f = PF_JUMPBIG; if (!(p->Player_YVel & 0x80)) f = PF_FALLBIG; }
    p->Player_Frame = f;
}
/* Player_AnimTailWag */
static void anim_tail_wag(smb3_player *p) {
    if (p->Player_AllowAirJump || !p->Player_InAir) return;
    if (!p->Player_IsDucking) {
        if (p->Pad_Input & SMB3_A) { if (!p->jumped) p->tailwag = 1; p->Player_TailCount = 10; }   /* (SND_LEVELTAILWAG unless a jump is queued) */
        uint8_t a = p->Player_FlyTime ? 0 : 6;
        if (!(p->Player_YVel & 0x80)) a += 3;
        a += p->Player_TailCount >> 2;
        p->Player_Frame = Player_TailWagFlyFrames[a < sizeof Player_TailWagFlyFrames ? a : sizeof Player_TailWagFlyFrames - 1];
    }
    if (!(p->Player_FlyTime | p->Player_WagCount)) return;             /* (flying or fluttering: slows to walking speed) */
    int8_t y = -1; uint8_t mag = p->Player_XVel;
    if (p->Player_XVel & 0x80) { y = 1; mag = negate(mag); }
    if (mag < PLAYER_TOPWALKSPEED) return;
    p->Player_XVel = (uint8_t)(p->Player_XVel + y);                    /* (slows to walking speed in the air) */
}
/* Player_TailAttackAnim */
static void tail_attack_anim(smb3_player *p) {
    if (p->Pad_Holding & SMB3_DOWN) return;
    if ((p->Pad_Input & SMB3_B) && !p->Player_TailAttack) { p->Player_TailAttack = 0x12; p->tailattack = 1; }   /* (SND_LEVELTAILWAG) */
    if (!p->Player_TailAttack) return;
    uint8_t y = p->Player_TailAttack >> 2;
    if (p->Player_InAir) y += 5;
    p->Player_Frame = Player_TailAttackFrames[y < sizeof Player_TailAttackFrames ? y : sizeof Player_TailAttackFrames - 1];
    if (p->Player_TailAttack == 0x0B || p->Player_TailAttack == 0x03) p->Player_FlipBits ^= SMB3_HFLIP;
}
/* Player_ShootAnim */
static void shoot_anim(smb3_player *p) {
    if (!p->Player_FireCount) return;
    uint8_t a = p->Player_FireCount >> 2;
    if (p->Player_InAir) a += 3;
    p->Player_Frame = Player_FireOnGround[a < 6 ? a : 5];
}
/* GndMov_Frog's hopping and Swim_Frog */
static void frog_ground(smb3_player *p) {
    if (p->Player_IsHolding) return;
    int y;
    if (p->Player_InAir) { p->Player_FireCount = 0; y = 1; }           /* (Player_FrogHopCnt) */
    else {
        uint8_t a = p->Player_FireCount;
        if (!a) {
            p->Player_XVel = 0;
            if (p->Pad_Holding & (SMB3_LEFT | SMB3_RIGHT)) { p->frog_hop = 1; p->Player_FireCount = 0x1F; a = 0x1F; }   /* (SND_PLAYERFROG) */
        }
        y = a >> 3;
    }
    p->Player_Frame = Player_FrogHopFrames[y & 3];
}
static void swim_frog(smb3_player *p) {
    int x = -1;
    uint8_t ud = p->Pad_Holding & (SMB3_UP | SMB3_DOWN);
    if (ud) {
        p->Player_InAir = ud;
        x = ud >> 3;                                                    /* (1 up, 0 down) */
        uint8_t a = (uint8_t)Frog_Velocity[x];
        if (p->Pad_Holding & SMB3_A) a = (uint8_t)(a << 1);
        /* CMP #(PLAYER_FROG_MAXYVEL+1) / BLT: unsigned against $E1 */
        if (!(a < (uint8_t)(PLAYER_FROG_MAXYVEL + 1)) && !p->Player_InAir) a = (uint8_t)PLAYER_FROG_MAXYVEL;
        p->Player_YVel = a;
    } else if (p->Player_YVel) {
        uint8_t y = (uint8_t)(p->Player_YVel + 1);
        if (!(p->Player_YVel & 0x80)) y = (uint8_t)(y - 2);
        p->Player_YVel = y;
    }
    uint8_t lr = p->Pad_Holding & (SMB3_LEFT | SMB3_RIGHT);
    if (lr) {
        uint8_t a = (uint8_t)Frog_Velocity[lr >> 1];
        if (p->Pad_Holding & SMB3_A) a = (uint8_t)(a << 1);
        p->Player_XVel = a; x = 2;
    } else if (p->Player_XVel) {
        uint8_t y = (uint8_t)(p->Player_XVel + 1);
        if (!(p->Player_XVel & 0x80)) y = (uint8_t)(y - 2);
        p->Player_XVel = y;
    } else if (!p->Player_InAir) { p->Player_Frame = 0x15; return; }
    if (x < 0) { p->Player_Frame = (uint8_t)(PF_FROGSWIM_IDLEBASE + ((p->Counter_1 & 0x08) ? 1 : 0)); return; }
    uint8_t a = p->Counter_1 >> 2; int yi = 0;
    if (!(p->Pad_Holding & SMB3_A)) { a >>= 1; yi = 1; }
    uint8_t y = a & 7;
    if (!y && !(p->Counter_1 & Frog_SwimSoundMask[yi])) p->swam = 1;   /* (SND_PLAYERSWIM) */
    p->Player_Frame = (uint8_t)(Frog_BaseFrame[x] + Frog_FrameOffset[y]);
}

void smb3p_frame(smb3_player *p, uint8_t buttons, smb3_motion *m) {
    p->jumped = p->swam = p->tailwag = p->tailattack = p->frog_hop = 0;
    p->Pad_Holding = buttons; p->Pad_Input = buttons & ~p->pad_prev; p->pad_prev = buttons;
    p->Counter_1++;
    p->Counter_Wiggly = (uint8_t)((p->Counter_Wiggly & 0xF0) - 0x90);
    /* (Event_Countdown and the 7 after it: decremented together each frame) */
    if (p->Player_TailCount) p->Player_TailCount--;
    if (p->Player_FireCount) p->Player_FireCount--;
    if (p->Player_PMeterCnt) p->Player_PMeterCnt--;
    if (p->Player_TailAttack) p->Player_TailAttack--;
    if (p->PWing) p->Player_FlyTime = 0xFF;
    /* ---- Player_Control ---- */
    p->Player_FlipBits_OLD = p->Player_FlipBits;
    p->Player_InAir_OLD = p->Player_InAir;
    {   uint8_t y = p->Player_Suit;                                     /* (PRG008_A6F2: ducking) */
        if (!y || y == SMB3_FROG || p->Player_IsHolding) p->Player_IsDucking = 0;
        else if (p->Player_InAir) { if (p->Player_InWater) p->Player_IsDucking = 0; }
        else {
            p->Player_IsDucking = 0;
            if ((p->Pad_Holding & (SMB3_LEFT | SMB3_RIGHT | SMB3_UP | SMB3_DOWN)) == SMB3_DOWN) p->Player_IsDucking = y;
        }
    }
    /* the water's surface (PRG008_A7E2): rising with the head out of the water - held to -$0C (a little
       less one frame in eight), no stroke; UP + A held leaves the water at -$34 */
    if (p->Player_InWater && p->WaterSurface && p->Player_InAir && (p->Player_YVel & 0x80)) {
        uint8_t y = p->Player_YVel;
        if ((int8_t)y < -0x0C) y = (uint8_t)-0x0C;
        if (!(p->Counter_1 & 0x07)) y++;
        p->Player_YVel = y;
        p->Pad_Input &= (uint8_t)~SMB3_A;
        uint8_t held = p->Pad_Holding;
        p->Pad_Holding &= (uint8_t)~SMB3_UP;
        if ((held & (SMB3_UP | SMB3_A)) == (SMB3_UP | SMB3_A)) p->Player_YVel = (uint8_t)-0x34;
    }
    p->Player_FlipBits &= 0x7F;
    /* velocities applied (this frame's movement is the last frame's velocities) */
    uint8_t xv0 = p->Player_XVel, yv0 = p->Player_YVel;
    m->ix = apply_x(p);
    m->dx = (int8_t)p->Player_XVel / 16.0f;
    (void)xv0;
    {   uint8_t a = p->Player_XVel, y = 2;
        if (a & 0x80) { a = negate(a); y = 1; }
        if (!a) y = 0;
        p->Player_MoveLR = y;
    }
    m->iy = 0; m->dy = 0;
    if (p->Player_InAir) { m->iy = apply_y(p); m->dy = (int8_t)p->Player_YVel / 16.0f; }
    (void)yv0;
    common_ground_anims(p);
    uint8_t mag = absv(p->Player_XVel);
    if (p->Player_InWater) {
        switch (p->Player_Suit) {
        case SMB3_FROG: swim_frog(p); break;
        default:
            underwater_hcontrol(p, mag); swim_v(p); swim_anim(p);
            if (p->Player_Suit == SMB3_FIRE || p->Player_Suit == SMB3_HAMMER) shoot_anim(p);
        }
    } else {
        ground_hcontrol(p, mag);
        jump_fly_flutter(p);
        switch (p->Player_Suit) {
        case SMB3_SMALL:
            if (!p->Player_AllowAirJump && p->Player_InAir) p->Player_Frame = p->Player_FlyTime ? PF_FASTJUMPFALLSMALL : PF_JUMPFALLSMALL;
            break;
        case SMB3_BIG: soar_jump_fall_frame(p); break;
        case SMB3_FIRE: case SMB3_HAMMER: soar_jump_fall_frame(p); shoot_anim(p); break;
        case SMB3_LEAF: case SMB3_TANOOKI: anim_tail_wag(p); tail_attack_anim(p); break;   /* (Player_TanookiStatue: not yet) */
        case SMB3_FROG: frog_ground(p); break;
        }
    }
    /* ---- Player_PowerUpdate ---- */
    if (p->Player_FlyTime) {
        if (p->Player_FlyTime != 0xFF) {
            if (p->Counter_1 & 1) p->Player_FlyTime--;
            if (!p->Player_FlyTime) p->Player_Power = 0;
        }
    } else {
        int skip = 0;
        if (p->Player_Power == 0x7F && p->Player_RunFlag) { p->Player_PMeterCnt = 0x10; skip = 1; }   /* (SND_PLAYERPOWER: the full meter's ring) */
        if (!skip && !p->Player_PMeterCnt) {
            uint8_t old = p->Player_Power;
            p->Player_Power = (uint8_t)((old << 1) | 1);                 /* (SEC / ROL) */
            if (!p->Player_RunFlag) p->Player_Power = (uint8_t)(old >> 1);   /* (ROR back, LSR) */
            if (p->Player_Power) p->Player_PMeterCnt = p->Player_RunFlag ? 0x08 : 0x18;
            else p->Player_FlyTime = 0;
        }
    }
    p->Player_RunFlag = 0;
}

/* ---- Player_DetectSolids, as the host's collision found it ---- */
void smb3p_land(smb3_player *p) {
    if (p->Player_InAir && (p->Player_YVel & 0x80)) return;             /* (rising: no landing - PRG008_B53B) */
    p->Player_InAir = 0; p->Player_YVel = 0;
}
void smb3p_leave_ground(smb3_player *p) { if (!p->Player_InAir) { p->Player_YVel = 0; p->Player_InAir = 1; } }
void smb3p_ceiling(smb3_player *p) {
    if (!(p->Player_YVel & 0x80) || !p->Player_InAir) return;
    p->Player_HitCeiling = 1; p->Player_YVel = 1;
}
void smb3p_wall(smb3_player *p, int dir) {
    if ((dir == 1 && !(p->Player_XVel & 0x80)) || (dir == 2 && (p->Player_XVel & 0x80))) p->Player_XVel = 0;
}
void smb3p_stomp(smb3_player *p) { p->Player_YVel = (uint8_t)-0x40; p->Player_InAir = 1; }
void smb3p_launch(smb3_player *p, int yvel) { p->Player_YVel = (uint8_t)(int8_t)yvel; p->Player_InAir = 1; }
void smb3p_fired(smb3_player *p) { p->Player_FireCount = 0x0B; }

/* Player_SetSpecialFrames */
void smb3p_special_frames(smb3_player *p) {
    if (!(absv(p->Player_XVel) < 0x37) && !p->Player_FlyTime && !p->Player_IsDucking && !p->Player_InWater) {
        int y = p->Player_WalkFrame & 3; if (!p->Player_Suit) y += 4;
        p->Player_Frame = Player_SpreadEagleFrames[y];
    }
    if (p->Player_Flip) {                                               /* (the somersault) */
        uint8_t a = p->Counter_1 >> 1;
        uint8_t fb = Player_SomersaultFlipBits[a & 7];
        if (p->Player_XVel & 0x80) fb ^= SMB3_HFLIP;
        p->Player_FlipBits = fb;
        p->Player_Frame = (uint8_t)((a & 3) + PF_SOMERSAULT_BASE);
        if (!p->Player_InAir) p->Player_Flip = 0;                       /* (Player_DetectSolids clears it on landing) */
    }
    if (p->Player_IsHolding) {
        int y = p->Player_WalkFrame & 3;
        if (p->Player_InAir_OLD) y = p->Player_Suit ? 0 : 1;
        if (!p->Player_Suit) y += 4;
        p->Player_Frame = Player_HoldingFrames[y];
    }
    if (p->Player_PipeFace || (p->Player_IsHolding && p->Player_FlipBits != p->Player_FlipBits_OLD)) {
        if (!p->Player_PipeFace) p->Player_PipeFace = 7;               /* (turning round with something held: facing the screen a moment) */
        p->Player_PipeFace--;
        p->Player_Frame = p->Player_Suit ? PF_INPIPE_BIG : PF_INPIPE_SMALL;
    }
    if (p->Player_Kick) {
        p->Player_TailAttack = 0;
        p->Player_Frame = p->Player_Suit ? PF_KICK_BIG : PF_KICK_SMALL;
        p->Player_Kick--;
    }
}
