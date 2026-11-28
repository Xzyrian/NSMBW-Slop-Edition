/* smb3_physics.h - the player movement of Super Mario Bros. 3 (NES), for the retro characters.
 *
 * A port of the player code in the SMB3 disassembly (SMB3Disassembly/PRG/prg008.asm: Player_Update,
 * Player_Control, PowerUpMovement_JumpTable (GndMov_* / Swim_*), Player_GroundHControl,
 * Player_UnderwaterHControl, Player_JumpFlyFlutter, Player_SwimV, Player_ApplyXVelocity /
 * Player_ApplyYVelocity, Player_PowerUpdate, and the frame choice: Player_CommonGroundAnims,
 * Player_SoarJumpFallFrame, Player_AnimTailWag, Player_TailAttackAnim, Player_ShootAnim,
 * Player_SwimAnim, Player_SetSpecialFrames), byte for byte: the same 8-bit velocities (1/16 pixel
 * a frame, 4.4 fixed point), tables, constants, order of operations and quirks (the "wiggly"
 * pseudo-random carry in the acceleration, the literal #Pad_Input in Player_UnderwaterHControl,
 * the frog hop counter shared with the fire counter). The variables keep the disassembly's names.
 *
 * It knows nothing about the level (Player_DetectSolids is the host's): each frame the host gives
 * the buttons, moves the player by the velocities and reports what the collision found
 * (smb3p_land, smb3p_leave_ground, smb3p_ceiling, smb3p_wall), as the SMB1 Mario host does for smb1_mario.c. Units are
 * the same in both games: 1 pixel = 1 unit, 60 frames a second, y down (the host flips).
 */
#pragma once
#include <stdint.h>

/* Pad_Holding / Pad_Input */
enum { SMB3_A = 0x80, SMB3_B = 0x40, SMB3_SELECT = 0x20, SMB3_START = 0x10,
       SMB3_UP = 0x08, SMB3_DOWN = 0x04, SMB3_LEFT = 0x02, SMB3_RIGHT = 0x01 };
/* Player_Suit */
enum { SMB3_SMALL, SMB3_BIG, SMB3_FIRE, SMB3_LEAF, SMB3_FROG, SMB3_TANOOKI, SMB3_HAMMER, SMB3_SUITS };
/* Player_FlipBits */
#define SMB3_HFLIP 0x40                        /* (SPR_HFLIP: facing right - the frames face left) */

typedef struct smb3_player {
    /* set by the host each frame */
    uint8_t Player_Suit;
    uint8_t Player_InWater;        /* swimming (NSMBW's Swim state) */
    uint8_t WaterSurface;          /* swimming with the head out of the water (Player_Control's surface checks) */
    uint8_t Player_IsHolding;      /* carrying something (holding frames) */
    uint8_t Player_StarInv;        /* star invincible (the somersault jump) */
    uint8_t PWing;                 /* the P-Wing: Player_FlyTime held at $FF */
    /* state (the disassembly's RAM) */
    uint8_t Player_XVel, Player_YVel;          /* signed, 1/16 pixel a frame */
    uint8_t Player_XVelFrac, Player_YVelFrac;  /* the accumulated fractions (Player_XVelFrac,X) */
    uint8_t Player_InAir, Player_InAir_OLD;
    uint8_t Player_FlipBits, Player_FlipBits_OLD;
    uint8_t Player_MoveLR;         /* 2 right, 1 left, 0 still */
    uint8_t Player_IsDucking;
    uint8_t Player_Power;          /* the power meter: $7F full */
    uint8_t Player_PMeterCnt, Player_RunFlag, Player_FlyTime;
    uint8_t Player_WagCount, Player_TailCount, Player_TailAttack;
    uint8_t Player_FireCount;      /* (shared with Player_FrogHopCnt) */
    uint8_t Player_AllowAirJump, Player_Flip, Player_mGoomba, Player_Kick, Player_PipeFace;
    uint8_t Player_WalkAnimTicks, Player_WalkFrame, Counter_ByPlayerSpd, Player_SwimCnt;
    uint8_t Player_Frame;
    uint8_t Player_HitCeiling;
    uint8_t Counter_1, Counter_Wiggly;
    uint8_t Pad_Holding, Pad_Input, pad_prev;
    /* what this frame did (for the host) */
    uint8_t jumped, swam, tailwag, tailattack, frog_hop, skid;
} smb3_player;

typedef struct {
    float dx, dy;                  /* pixels moved this frame by the velocities (y down) */
    int ix, iy;                    /* the same in SMB3's whole pixels (Player_ApplyVelocity with its fractions) */
} smb3_motion;

void smb3p_init(smb3_player *p, int suit, int facing_left);
/* one frame of Player_Control and Player_PowerUpdate: buttons are Pad_Holding (SMB3_A | ...) */
void smb3p_frame(smb3_player *p, uint8_t buttons, smb3_motion *m);
/* Player_DetectSolids, from the host's collision (after moving the player) */
void smb3p_land(smb3_player *p);              /* feet on the ground while falling (or standing) */
void smb3p_leave_ground(smb3_player *p);      /* walked off: InAir, YVel 0 */
void smb3p_ceiling(smb3_player *p);           /* head hit while rising: YVel 1 */
void smb3p_wall(smb3_player *p, int dir);     /* blocked moving right (1) / left (2): XVel 0 */
/* bounces from objects */
void smb3p_stomp(smb3_player *p);             /* an enemy stomped: YVel -$40 */
void smb3p_launch(smb3_player *p, int yvel);  /* a spring etc.: that YVel */
void smb3p_fired(smb3_player *p);             /* a fireball / hammer thrown: Player_FireCount */
/* Player_SetSpecialFrames (after the collision): spread eagle, somersault, holding, kick */
void smb3p_special_frames(smb3_player *p);
