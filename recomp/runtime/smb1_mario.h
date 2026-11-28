/* smb1_mario.h - Retro Mario (SMB1): Super Mario Bros.' own player code, run from its ROM.
 *
 * Nothing here is a port. Each player has its own copy of the NES's 2 KB of RAM, and each frame
 * SMB1's own routines run on it on a small 6502 (smb1_cpu.c), from the ROM built from
 * SMB1Disassembly (tools/smb1_embed.py -> out/smb1_rom.c, out/smb1_syms.h):
 *   - movement: the frame's timers (DecTimers), PlayerCtrlRoutine's reading of the controller,
 *     then PlayerMovementSubs (PlayerPhysicsSub, OnGroundStateSub / JumpSwimSub / FallingSub,
 *     GetPlayerAnimSpeed, ImposeFriction, MovePlayerHorizontally, MovePlayerVertically) and
 *     ChkMoveDir - the routines, their tables and their quirks are the ROM's;
 *   - looks: PlayerGfxHandler (ProcessPlayerAction, AnimationControl, RenderPlayerSub,
 *     ChkForPlayerAttrib, the fireball throw, the swimming kick, growing and shrinking, the
 *     death picture) writes the player's 8 sprites into OAM; they are drawn from the ROM's
 *     pattern table in the ROM's colours (PlayerColors, the ground palettes);
 *   - sounds: what the routines put in the sound queues is played as SMB1's sound engine
 *     (SoundEngine, bank 2) makes it - rendered on a small APU the first time it is needed.
 * The level is NSMBW's: the host moves the NSMBW player by what the routines moved, NSMBW's
 * collision runs, and what it found goes back into the RAM as PlayerBGCollision would put it
 * (smb1m_collide). SMB1's y grows downwards; so does everything here. */
#pragma once
#include <stdint.h>

/* SavedJoypadBits */
enum { SMB1_A = 0x80, SMB1_B = 0x40, SMB1_SELECT = 0x20, SMB1_START = 0x10,
       SMB1_UP = 0x08, SMB1_DOWN = 0x04, SMB1_LEFT = 0x02, SMB1_RIGHT = 0x01 };
/* Player_State */
enum { SMB1_ON_GROUND = 0, SMB1_JUMP_SWIM = 1, SMB1_FALLING = 2, SMB1_CLIMBING = 3 };
/* PlayerFacingDir */
enum { SMB1_FACE_RIGHT = 1, SMB1_FACE_LEFT = 2 };
/* colours (rt_retro.c): Mario's own (PlayerColors), Fire Mario's, an Ice Flower Mario's (NSMBW's: ours) */
enum { SMB1_PAL_MARIO, SMB1_PAL_FIERY, SMB1_PAL_ICE };

typedef struct smb1_mario {
    uint8_t ram[0x800];
    int grow;                         /* growing / shrinking (PlayerChangeSizeFlag, for the pictures only) */
    int flash;                        /* frames of Fire Mario's palette flashing left (PlayerFireFlower) */
    uint8_t sfx[4];                   /* queued this frame: Square1, Square2, Noise, EventMusic */
} smb1_mario;

typedef struct {
    float dy;                         /* pixels moved down this frame (with the fraction) */
    float vx;                         /* horizontal speed, pixels a frame (Player_X_Speed / 16) */
    int jumped;                       /* a jump or a swim stroke started this frame */
} smb1_motion;

/* the picture: 32 x 32, the player's 16-wide body in the middle (Player_Rel_XPos at x 8), his
   head row (Player_Rel_YPos) at the top - his feet at the bottom; each pixel 0 (none) or
   palette * 4 + colour (1-3) */
typedef struct { uint8_t px[32 * 32]; uint8_t colours[16]; uint64_t hash; } smb1_picture;

int  smb1m_available(void);                 /* the ROM is there (else no SMB1 Mario) */
void smb1m_init(smb1_mario *m, int small, int face_left);
uint8_t *smb1m_ram(smb1_mario *m, const char *what);   /* (testing / logging) */

/* one frame of movement: buttons are SavedJoypadBits; swimming / at the water's surface from
   NSMBW's state */
void smb1m_frame(smb1_mario *m, uint8_t buttons, int swimming, int water_top, smb1_motion *out);
/* PlayerBGCollision, from what NSMBW's collision found this frame (after the move): feet on the
   ground, head against a ceiling, a wall the player was stopped by on the right / left */
void smb1m_collide(smb1_mario *m, int foot, int head, int wall_right, int wall_left);
void smb1m_stomp(smb1_mario *m, int high);  /* bounced off an enemy (SetBounce; high: a paratroopa's) */
void smb1m_spring(smb1_mario *m, int a_held);   /* launched by a springboard (JumpspringHandler) */
void smb1m_fire(smb1_mario *m);             /* threw a fireball (ProcFireball_Bubble's throwing pose) */
void smb1m_set_size(smb1_mario *m, int small, int animate);   /* PlayerSize (animate: grow / shrink) */
void smb1m_fire_flash(smb1_mario *m);       /* became Fire Mario: the palette flashes */

/* the pictures for states SMB1's movement doesn't run in: the RAM set as for such a frame */
typedef struct {
    int dead;                         /* GameEngineSubroutine $0B: the death picture */
    int climbing, climb_dir;          /* on a vine / pole / net: climb_dir -1 up, 1 down, 0 still */
    int in_air, swimming;
    int speed;                        /* Player_X_Speed (1/16 px a frame, signed) */
    int face_left;
    int crouching;
} smb1_pose;
void smb1m_pose(smb1_mario *m, const smb1_pose *p);
void smb1m_timers(smb1_mario *m);           /* (smb1m_frame does this; a posed frame needs it) */

/* PlayerGfxHandler: the picture for this frame (call once a frame, after the move).
   star: frames of NSMBW's star left (0: none) - the palette cycles as CyclePlayerPalette does */
void smb1m_graphics(smb1_mario *m, int pal, int star_frames, smb1_picture *out);

/* the queued sounds as names for rt_sfx.c's "@smb1" (smb1_sfx_<queue>_<bit>, smb1_mus_<bit>):
   returns how many, into names[] (each up to 24 chars) */
int  smb1m_take_sounds(smb1_mario *m, char names[][24], int max);
/* rt_sfx.c: a sound rendered by SMB1's SoundEngine - 32 kHz stereo (0: not one of SMB1's) */
int  smb1_sfx_render(const char *name, int16_t **pcm, int *frames);
