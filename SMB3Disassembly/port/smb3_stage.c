/* smb3_stage.c - prototype: NSMBW players in SMB3's World 1-1.
 *
 * Start Game (SMB3) opens an NSMBW stage instead of the recompiled game's own screen. The stage
 * is NSMBW's course 1-1 used as an empty shell: its actors are not spawned (gm_d_actorcreate.c),
 * its tiles are emptied and covered. In it:
 *   - the level: the recompiled SMB3 is run unseen into 1-1 (its own loader, so the tile map is
 *     exact): Tile_Mem (16 x 27 tiles a screen), Tile_AttrTable (what is solid) and the 256 tile
 *     pictures, built from Tile_Layout_TS1 (bank 15: four 8x8 patterns a tile), the pattern
 *     banks and the palette as the PPU has them in the level;
 *   - collision: NSMBW's tile lookups (gm_bg.c: unit_at) ask smb3_stage_unit() - an SMB3 tile is
 *     solid (>= Tile_AttrTable[q + 4], q = tile / 64), solid on top (>= Tile_AttrTable[q]) or
 *     nothing, as NSMBW unit flags;
 *   - the picture: a draw proc in the stage's 3D scene (as Retro Mario's), the SMB3 sky and the
 *     tiles as flat quads, 1 NES pixel = 1 unit (both games: 16-unit tiles); NSMBW's players,
 *     camera, HUD and pause menu are the game's own.
 * Placed so that SMB3's start (column 2, on the ground) is where the course puts player 1.
 * No SMB3 enemies, blocks or items yet; no end of level. SMB3_STAGE_PROBE=1: NSMBW's own tiles
 * stay, and the unit flags of the course's tiles are logged (to read NSMBW's flag values). */
#include "rt.h"
#include "smb3.h"
#include "nes.h"
#include "smb3_save.h"
#include "smb3_stage.h"
#include "rt_powerup.h"                      /* (the suits are NSMBW power-up states: PU_RACCOON, PU_FROG - POWERUPS.md) */
#include "nes_apu.h"
#include "smb3_syms.h"                         /* (out/: the disassembly's addresses) */
#include <string.h>
#include <stdio.h>
#include <math.h>
RT_STATE_FILE

extern const uint8_t smb3_rom[]; extern const uint32_t smb3_rom_size;
extern int smb3_start_at_map;

/* ---- guest ---- */
#define G_NOW_SCENE     0x80428732u
#define G_GAME_MODE     0x8042A204u
#define SDA             0x8042F680u
#define BG_GM           (SDA - 22704)            /* dBgGm_c::m_bg_p */
#define BG_TILEMAPS     (SDA - 22672)
#define BG_AREA         (SDA - 21688)
#define A_IS_DEMO       0x8004DD00u              /* daPlBase_c::isDemo (a demo of type 1-3: death, pipes, the goal...) */
#define A_UNIT_FLAGS    0x800774A0u              /* dBgGm_c: a tile number's flags (r3:r4) */
#define A_START_GAME    0x800BB780u              /* dInfo_c::startGame(StartGameInfo_s &) */
#define A_SET_FADER     0x800B0DB0u              /* dFader_c::setFader(fader_type_e): 0 the colour fade */
#define A_CRSIN_DISP_OFF 0x8042A1B0u             /* dScCrsin_c::m_isDispOff (bool) */
#define VT_COLOR_FADER  0x80329700u              /* mColorFader_c's vtable */
#define G_DINFO         (0x80430000u - 24708)    /* dInfo_c::m_instance */
#define PL_POS          0x0AC
/* the players a level starts with (as the world map's startGame sets them: gm_d_wm_player.c) */
#define WP_ENTRY_TABLE  (0x81860000u - 6000)     /* u32 x 8: in the level */
#define MOD_PY_REST      0x81851D8Cu            /* daPyMng_c::mRest[8] */
#define WP_ACTIVE_TABLE (0x81860000u - 5828)     /* u32 x 8: their order */
#define WP_SCENE_TABLE  (0x81860000u - 5796)     /* u32 x 8: power-up, by that order */
/* memory of ours: the top of the Game Select picture area (rt_gamesetup.c GP_MEM_END) */
#define SM_MEM          0x818C0000u
#define SM_PROC         (SM_MEM + 0x0000)
#define SM_VTABLE       (SM_MEM + 0x0040)
#define SM_CAMERA       (SM_MEM + 0x0080)
#define SM_MTX          (SM_MEM + 0x00A0)
#define SM_TEXOBJ       (SM_MEM + 0x0100)
#define SM_START_INFO   (SM_MEM + 0x0140)
#define SM_JMTX         (SM_MEM + 0x0200)        /* (a joint's matrix, 3 x 4) */
#define SM_TAILTEX      (SM_MEM + 0x0800)        /* the 3D tails' textures: 16 x 16 RGB5A3 (512 bytes): Mario's, Luigi's at +0x200 */
#define SM_TAILOBJ      (SM_MEM + 0x0C00)        /* (two GXTexObj, 0x20 each) */
#define SM_TEX          (SM_MEM + 0x1000)        /* 256 x up to 448 RGB5A3: up to 224 KB */
#define SM_SBTEX        (SM_MEM + 0x39000)       /* the status bar: 256 x 48 RGB5A3 (24 KB) */
#define SM_SBOBJ        (SM_MEM + 0x3F000)       /* (its GXTexObj) */
#define N_SM_DTOR       0x80003F40u
#define N_SM_DRAW_OPA   0x80003F44u
#define N_SM_DRAW_XLU   0x80003F48u
/* (rt_retro.c's) */
#define A_PROC_SETUP       0x80164FD0u
#define A_LEAF_ENTRY       0x8016A0E0u
#define A_LEAF_FREE        0x8016A090u
#define A_LEAF_GETTYPE     0x8000F720u
#define A_GET_CAMERA_BY_ID 0x80164B20u
#define A_GET_CUR_CAMERA   0x80164B40u
#define A_GET_CAMERA_MTX   0x802540B0u
#define A_G3D_INVALIDATE   0x8024D5E0u
#define A_DISABLE_IND_TEX  0x80164F50u
#define A_GXClearVtxDesc     0x801C4070u
#define A_GXSetVtxDesc       0x801C37C0u
#define A_GXSetVtxAttrFmt    0x801C40B0u
#define A_GXInitTexObj       0x801C6D90u
#define A_GXInitTexObjLOD    0x801C6FF0u
#define A_GXLoadTexObj       0x801C74C0u
#define A_GXSetNumChans      0x801C6AC0u
#define A_GXSetNumTexGens    0x801C4A20u
#define A_GXSetTexCoordGen2  0x801C47D0u
#define A_GXSetNumIndStages  0x801C8110u
#define A_GXSetTevDirect     0x801C8130u
#define A_GXSetNumTevStages  0x801C88F0u
#define A_GXSetTevOrder      0x801C8790u
#define A_GXSetTevOp         0x801C8250u
#define A_GXSetAlphaCompare  0x801C86C0u
#define A_GXSetBlendMode     0x801C8DC0u
#define A_GXSetZMode         0x801C8E70u
#define A_GXSetZCompLoc      0x801C8EB0u
#define A_GXSetCullMode      0x801C5860u
#define A_GXSetColorUpdate   0x801C8E10u
#define A_GXLoadPosMtxImm    0x801C9940u
#define A_GXSetCurrentMtx    0x801C9A60u
#define A_GXBegin            0x801C5570u
#define gcall rt_gcall
static uint32_t fbits(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static float RF(uint32_t a) { uint32_t u = R32(a); float f; memcpy(&f, &u, 4); return f; }

/* ---- the level ---- */
#define LH 27
static struct {
    int ok, w;                                   /* tiles across */
    uint8_t tile[LH * 16 * 15];
    uint8_t attr[8];                             /* Tile_AttrTable */
    uint32_t sky;                                /* 0xAARRGGBB */
    int placed; float lx, ly;                    /* the level's top left (y down, units) */
    float dy;                                    /* (the level this much lower than the players' ground for NSMBW's grid: they come down by it at the lift) */
    int sx, sy;                                  /* where SMB3 starts its player (Player_X / _Y with their high bytes: its 16 x 16 box's top left) */
    int slopes;                                  /* Level_SlopeEn: a slope level (Hills 3, Underground 14) - tiles from attr[q] up are slope shapes */
} L RT_LOCAL;
/* the texture: 256 wide; tile t at ((t % 16) * 16, (t / 16) * 16); below the 256 tiles, slots of
   16 x 16 (slot s at ((s % 16) * 16, (s / 16) * 16), s >= 256): the animated tiles' other frames,
   then the item sprites. 0xAARRGGBB, alpha 0 = transparent. */
#define TEX_H_MAX 448
#define BACKDROP_A 0xFE000000u                    /* (the atlas: a tile's backdrop pixel - tex_upload) */
static uint32_t atlas[256 * TEX_H_MAX] RT_LOCAL;
static int tex_h;                                /* rows in use */
static int16_t anim_slot[256];                  /* first of a tile's 3 other frames, or -1 */
enum { SPR_MUSHROOM, SPR_1UP, SPR_STAR, SPR_FLOWER, SPR_LEAF, SPR_FROG, NSPR };   /* (SPR_FROG: smb3_stage_frog.inc) */
static int spr_slot0;                           /* slot of SPR_MUSHROOM */
/* single 8 x 16 sprites, two to a slot: the coin out of a block (CoinPUp_Patterns, palette 3),
   brick debris (BrickBust: $4B, palette 3), the score digits (Score_PatternLeft/Right, palette 1) */
enum { H_COIN0, H_COIN1, H_COIN2, H_COIN3, H_DEBRIS, H_S59, H_S5B, H_S61, H_S63, H_S69, H_S6B, H_S6D, H_S6F, NHALF };
static const uint8_t half_pat[NHALF] = {0x49, 0x4F, 0x4D, 0x4F, 0x4B, 0x59, 0x5B, 0x61, 0x63, 0x69, 0x6B, 0x6D, 0x6F};
static const uint8_t half_pal[NHALF] = {3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1};
static int half_slot0;
/* the Raccoon suit's placeholder (2D, SMB3's own pixels) for the 3D players: per colour, the tail
   poses (Raccoon CHR page $00: $09 held out, $3B up, $1D / $1F down) and an ear (cut from the head,
   $03) - 8 x 16 halves, two to a slot. Colours as SMB3's PowerUp_Palettes: Mario $16 $36 $0F,
   Luigi $2A; the Toads' (not in SMB3): $12 blue, $28 yellow */
enum { RC_TAIL_OUT, RC_TAIL_UP, RC_TAIL_DOWN1, RC_TAIL_DOWN2, RC_EAR, NRC };
#define NRCOL 4
static const uint8_t RC_TAIL_PAT[4] = {0x09, 0x3B, 0x1D, 0x1F};
static const uint8_t RC_COLOUR[NRCOL] = {0x16, 0x2A, 0x12, 0x28};
static const char *const RC_EAR_ART[8] = {"..KKK...", ".KSSK...", "KSSSK...", "KSSSK...", "KRSSK...", "KRRRK...", ".KKK....", "........"};
static int rc_slot0;
/* SMB3's music (smb3_stage_music.inc): its songs' numbers (smb3.asm) */
#define MUS1_PLAYERDEATH    0x01
#define MUS1_GAMEOVER       0x02
#define MUS1_BOSSVICTORY    0x04
#define MUS1_COURSECLEAR    0x20
#define MUS1_TIMEWARNING    0x40
#define MUS2A_INVINCIBILITY 0x0A
#define MUS2B_PSWITCH       0xA0
#define GOAL_CLEAR_FRAMES   192                 /* (MUS1_COURSECLEAR's length in frames: measured, SMB3_MUSIC_TEST_Q1=20,60) */
#define GOAL_FANFARE_FRAMES 240                 /* (MUS1_BOSSVICTORY's: SMB3_MUSIC_TEST_Q1=04,60) */
#define DEATH_SONG_FRAMES   192                 /* (MUS1_PLAYERDEATH's: SMB3_MUSIC_TEST_Q1=01,60) */
static void music_level_placed(void); static void mus_q1(uint8_t v); static int music_death_left(void);
static void snd_unseen(int on); static void music_sync(ppc_context *ctx, uint8_t *base);   /* (smb3_stage_music.inc) */
static int restart_wait;                        /* (a death's restart held until SMB3's death song is over: smb3_stage_draw_any) */
static int active, probe, tex_ready;
static int await_scene;                         /* (a restart from inside the stage: the level not placed on the old one's players) */
static int keep_counters;                       /* (a restart after a death: SMB3's score and coins stay) */
/* (the world map: smb3_map.inc) */
static int map_on(void), map_enabled(void), map_special(void); static void map_session_stop(void); static int map_session_start(int from_setup), map_session_on(void), map_shown_level(void);
static void map_apply_next(void), map_place(float px, float py), map_camera(void);
static void map_player(ppc_context *ctx, uint8_t *base, uint32_t pl), map_draw(ppc_context *ctx, uint8_t *base);
static int map_level_end(ppc_context *ctx, uint8_t *base, int died), map_again(ppc_context *ctx, uint8_t *base);
static void eh_render(int *slot, const uint8_t *chr, uint32_t nchr, const uint8_t *ram);   /* (smb3_stage_enemies.inc) */
static void plats_off(void);                     /* (smb3_stage_platforms.inc) */
static void th_render(int *slot, const uint8_t *chr, uint32_t nchr, const uint8_t *ram);   /* (smb3_stage_toadhouse.inc) */
static void bt_render(int *slot, const uint8_t *chr, uint32_t nchr, const uint8_t *ram, const uint8_t *wram);   /* (smb3_stage_battle.inc) */
static int bt_quads(void);
static void bt_draw(float z);
static int mg_quads(void);
static void mg_draw(float z);
static int th_quads(void); static void th_draw(float z);
static void objs_load_list(const uint8_t *wram);
static int list_has_bros(const uint8_t *wram);   /* (smb3_stage_battle.inc) */
static int list_has(const uint8_t *wram, int id);
static void glyph_render(int *slot, const uint8_t *chr, uint32_t nchr);
static void quad(float x0, float y0, float x1, float y1, float z, float u0, float v0, float u1, float v1);
#define BG_PARAM_P      0x80429E00u              /* dBgParameter_c::ms_Instance_p (+56 / +60 the screen's top left, +64 / +68 its size) */
/* SMB3's status bar (prg026 StatusBar_*): name table rows 24-29 of $2800 (horizontal levels: the
   bar's at $2B00), their attributes, the pattern tables as its IRQ maps them and the palette, taken
   from the unseen SMB3 in 1-1; the fields SMB3 rewrites each frame (StatusBar_UpdTemplate) written
   here by its own rules from this stage's counters */
#define SB_W 256
#define SB_LIFT 48.0f                            /* (the level and players this much higher: the bar's height, so it hides nothing) */
static int lifted[8];
#define SB_H 48
static struct {
    int ok, time0, time, tick, ptick, inval;
    uint8_t nt[6 * 32], attr[16], chr[0x2000], ctrl, pal[16], shown[6 * 32], pal3;
    uint32_t px[SB_W * SB_H];
} SB RT_LOCAL;

/* ---- slopes (prg000 Level_SlopeSetByQuad / Slope_LUT; PRG008 Player_GetTileSlopeAndQuad) ----
   In a slope level (Level_SlopeEn: Hills, Underground) a tile from its quad's base up (Tile_AttrTable's
   first four: $25 $5F $99 $E2) has a "shape" from these tables, rooted at that base. The shapes
   (Slope_LUT: per pixel across, the low nibble the floor's depth below the tile's top, the high the
   ceiling's reach down from it):
     $00 none   $03 solid square   $04 wall   $07 floor only (unsloped ground: the head passes)
     $08 ceiling only   $01 / 45 deg up (floor 15..0)   $02 \ 45 deg down (0..15)
     $0C $0D / 22.5 deg up over two tiles (15..8, 7..0)   $0E $0F \ down (0..7, 8..15)
     $05 $06 45 deg ceilings, $11 $12 $13 $14 22.5 deg ceilings - each the floor shape upside down
     ($05 = $01's, $06 = $02's, $11 $12 = $0C $0D's, $13 $14 = $0E $0F's) */
static const uint8_t SlopeQuad00[] = {0x01, 0x07, 0x02, 0x0C, 0x0D, 0x0E, 0x0F, 0x07, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x04,
                                      0x07, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x07, 0x04, 0x07, 0x04, 0x04, 0x04, 0x04, 0x04};
static const uint8_t SlopeQuad40[] = {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
                                      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03};
static const uint8_t SlopeQuad80[] = {0x01, 0x07, 0x02, 0x0C, 0x0D, 0x0E, 0x0F, 0x05, 0x06, 0x11, 0x12, 0x13, 0x14, 0x08, 0x07, 0x04,
                                      0x07, 0x04, 0x04, 0x08, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
                                      0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x08};
static const uint8_t SlopeQuadC0[] = {0x01, 0x07, 0x02, 0x0C, 0x0D, 0x0E, 0x0F, 0x05, 0x06, 0x11, 0x12, 0x13, 0x14, 0x07, 0x03, 0x03,
                                      0x03, 0x03, 0x08, 0x07, 0x04, 0x07, 0x04, 0x04, 0x08, 0x08, 0x04};
static const uint8_t Slope_LUT[0x15][16] = {   /* (low nibble: the floor's depth below the tile's top at that pixel across; high: the ceiling's reach down) */
    {0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10}, {0x0F,0x0E,0x0D,0x0C,0x0B,0x0A,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00},
    {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F}, {0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0},
    {0}, {0x00,0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90,0xA0,0xB0,0xC0,0xD0,0xE0,0xF0},
    {0xF0,0xE0,0xD0,0xC0,0xB0,0xA0,0x90,0x80,0x70,0x60,0x50,0x40,0x30,0x20,0x10,0x00}, {0},
    {0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0}, {0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0},
    {0x02,0x02,0x02,0x02,0x03,0x03,0x03,0x03,0x04,0x04,0x04,0x04,0x03,0x03,0x03,0x02}, {0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0,0xF0},
    {0x0F,0x0E,0x0E,0x0D,0x0D,0x0D,0x0C,0x0C,0x0B,0x0B,0x0A,0x0A,0x09,0x09,0x08,0x08}, {0x07,0x06,0x06,0x05,0x05,0x05,0x04,0x04,0x03,0x03,0x02,0x02,0x01,0x01,0x00,0x00},
    {0x00,0x00,0x01,0x01,0x02,0x02,0x03,0x03,0x04,0x04,0x05,0x05,0x05,0x06,0x06,0x07}, {0x08,0x08,0x09,0x09,0x0A,0x0A,0x0B,0x0B,0x0C,0x0C,0x0D,0x0D,0x0D,0x0E,0x0E,0x0F},
    {0x0E,0x0D,0x0B,0x0A,0x09,0x09,0x08,0x08,0x08,0x08,0x08,0x09,0x09,0x0A,0x0B,0x0D}, {0x00,0x00,0x10,0x10,0x20,0x20,0x30,0x30,0x40,0x40,0x50,0x50,0x50,0x60,0x60,0x70},
    {0x80,0x80,0x90,0x90,0xA0,0xA0,0xB0,0xB0,0xC0,0xC0,0xD0,0xD0,0xD0,0xE0,0xE0,0xF0}, {0xF0,0xE0,0xE0,0xD0,0xD0,0xD0,0xC0,0xC0,0xB0,0xB0,0xA0,0xA0,0x90,0x90,0x80,0x80},
    {0x70,0x60,0x60,0x50,0x50,0x50,0x40,0x40,0x30,0x30,0x20,0x20,0x10,0x10,0x00,0x00} };
/* Slope_ObjectVel_Effect ($80: no floor for objects; SMB3's table stops at $0F - its ceilings $10-$14 none either) */
static const int8_t Slope_ObjectVel_Effect[0x15] = {0, -2, 2, 0, 0, -128, -128, 0, 0, -128, 0, -128, -1, -1, 1, 1, -128, -128, -128, -128, -128};
static int slope_shape(uint8_t t) {              /* the tile's shape in a slope level; -1: not a slope level, or a tile below its quad's base */
    if (!L.slopes) return -1;
    static const uint8_t *const tab[4] = {SlopeQuad00, SlopeQuad40, SlopeQuad80, SlopeQuadC0};
    static const int len[4] = {sizeof SlopeQuad00, sizeof SlopeQuad40, sizeof SlopeQuad80, sizeof SlopeQuadC0};
    int q = t >> 6, i = t - L.attr[q];
    if (i < 0) return -1;
    return i < len[q] ? tab[q][i] : 0x03;                                /* (past a table's end: SMB3 reads on into the next - all squares there) */
}
/* NSMBW's unit for a shape (SMB3_STAGE_PROBE on the shell course, and SMB3_STAGE_TEST_UNIT walked
   across: hi word 0x20 a floor slope, 0x40 a ceiling one; low byte 0 / up, 1 \ down, 2 3 the two
   halves of a 22.5 deg / up (low, high), 4 5 of a \ down (high, low); 0x0A NSMBW's flat one-way top.
   A ceiling shape n is floor shape n upside down). -1: not one of those (the caller's classes) */
static int64_t slope_unit(int sh) {
    static const int8_t nsmbw[0x15] = {-1, 0, 1, -1, -1, 0, 1, -1, -1, -1, -1, -1, 2, 3, 4, 5, -1, 2, 3, 4, 5};
    if (sh < 0 || sh > 0x14 || nsmbw[sh] < 0) return -1;
    int ceiling = sh == 0x05 || sh == 0x06 || sh >= 0x11;
    return ceiling ? (int64_t)(0x0000004000000000ull | (uint64_t)nsmbw[sh]) : (int64_t)(0x00000020000D0000ull | (uint64_t)nsmbw[sh]);
}
static int tile_class(uint8_t t) {               /* 2 solid, 1 solid on top, 0 nothing (by Tile_AttrTable, as SMB3's objects test it) */
    int q = t >> 6;
    if (t >= L.attr[q + 4]) return 2;
    if (t >= L.attr[q]) return 1;
    return 0;
}
/* the recompiled SMB3, run unseen from a new game into 1-1 (the same buttons as its test: right,
   up onto 1-1's square, A) */
static int jct_restart;                          /* (the stage starting again after a pipe's junction: SMB3's area up already, the clock kept) */
/* the Frog suit (smb3_stage_frog.inc) */
#define FROG_SUIT_CHR_BANK  0x4C                 /* (the suits' sprites, $90-$95: the bank SMB3's big ? blocks load) */
static void frog_level_loaded(const uint8_t *ram, const uint8_t *wram); static int frog_block_take(int tx, int ty);
static int frog_on(int n); static void frog_set(int n, int on); static void frog_reset(void);
static void frog_touch(ppc_context *ctx, uint8_t *base, uint32_t pl, int n, int mode); static int frog_powerdown(uint32_t pl, uint32_t *powerup);
static void frog_anchor(ppc_context *ctx, uint8_t *base, uint32_t pl); static int frog_anim(ppc_context *ctx, uint8_t *base);
static int level_load(void) {
    if (L.ok) return 1;
    if (!map_session_on() && !jct_restart) {                                             /* (no map: a new game, into 1-1 by its test's buttons) */
    if (!nes_load(smb3_rom, smb3_rom_size)) return 0;
    smb3_start_at_map = 1; smb3_load_from = NULL;
    nes_reset();
    ppu_capture_at(212);                                                 /* (a line of the status bar: its pattern banks) */
    for (int i = 0; i < 760; i++) {                                     /* (frame 760: 1-1 on screen, its pattern banks in) */
        uint8_t b = (i >= 250 && i < 270) ? NES_RIGHT : (i >= 330 && i < 350) ? NES_UP : (i >= 420 && i < 430) ? NES_A : 0;
        nes_set_buttons(0, b); nes_run_frame();
        if (nes_error()) { rt_log("smb3", "stage: SMB3 stopped while loading 1-1: %s", nes_error()); return 0; }
    }
    ppu_capture_at(-1);
    }                                                                    /* (the map's SMB3: the panel's level is up already - smb3_map.inc) */
    {   /* the course's time: its header's hundreds (GamePlay_TimeStart: Level_TimerMSD, the rest 0),
           a few seconds counted off since - so rounded up to the hundred */
        const uint8_t *r = nes_ram_ptr(); int t = r[0x5EE] * 100 + r[0x5EF] * 10 + r[0x5F0];
        SB.time0 = (t + 99) / 100 * 100; }
    for (int i = 0; i < 6 * 32; i++) SB.nt[i] = ppu_peek_nt((uint16_t)(0x2B00 + i));
    for (int i = 0; i < 16; i++) SB.attr[i] = ppu_peek_nt((uint16_t)(0x2BF0 + i));
    memcpy(SB.chr, ppu_captured_chr(), sizeof SB.chr); SB.ctrl = ppu_captured_ctrl();
    for (int i = 0; i < 16; i++) SB.pal[i] = ppu_peek_pal(i);
    SB.pal3 = SB.pal[3];
    memset(SB.shown, 0xFF, sizeof SB.shown); SB.ok = 1;

    const uint8_t *ram = nes_ram_ptr(), *wram = nes_wram_ptr();
    if (!map_session_on() && ram[0x70A] != 1) { rt_log("smb3", "stage: not in 1-1 (tileset %d)", ram[0x70A]); return 0; }
    if (ram[0x70A] == 0 || ram[0x70A] > 18) { rt_log("smb3", "stage: no level up (tileset %d)", ram[0x70A]); return 0; }
    int screens = ram[0x22] + 1; if (screens > 15) screens = 15;
    L.w = screens * 16;
    for (int s = 0; s < screens; s++) for (int r = 0; r < LH; r++) for (int c = 0; c < 16; c++)
        L.tile[r * L.w + s * 16 + c] = wram[s * 0x1B0 + r * 16 + c];
    memcpy(L.attr, wram + 0x1E94, 8);                                    /* Tile_AttrTable ($7E94) */
    L.slopes = ram[SMB3_Level_SlopeEn] != 0;                             /* (Hills / Underground: tiles by slope shape - slope_shape) */
    L.sx = ram[0x75] << 8 | ram[0x90];                                    /* (Player_XHi, Player_X: the level's start, as SMB3 has it now) */
    L.sy = ram[0x87] << 8 | ram[0xA2];                                    /* (Player_YHi, Player_Y) */
    frog_level_loaded(ram, wram);                                        /* (1-1: the Frog suit's ? block) */
    /* the tile pictures: Tile_Layout_TS1 (bank 15 at $A000): upper left, lower left, upper right,
       lower right; the background's patterns as the level has them: PatTable_BankSel ($0719: 2 KB
       banks for $0000 and $0800) - not the PPU's banks now, which at vblank are the status bar's
       (its IRQ swaps them in for the bottom of the screen). The $0800 bank animates: PT2_Anim
       ($60 $62 $64 $66, 8 frames each) - frames 1-3 kept for the tiles they change. */
    static const uint8_t PAGE_A000_ByTileset[19] = {11, 15, 21, 16, 17, 19, 18, 18, 18, 20, 23, 19, 17, 19, 13, 26, 26, 26, 9};   /* (prg030: the tileset's Tile_Layout bank; 1-1's: 15) */
    const uint8_t *lay = smb3_rom + 16 + PAGE_A000_ByTileset[ram[0x70A]] * 0x2000;
    const uint8_t *chr = smb3_rom + 16 + smb3_rom[4] * 0x4000u;
    uint32_t nchr = smb3_rom[5] * 8u;                                    /* 1 KB banks */
    uint8_t sel0 = ram[0x719];
    static const uint8_t anim_banks[4] = {0x60, 0x62, 0x64, 0x66};
    static uint32_t frame[4][256 * 256];
    static const int ox[4] = {0, 0, 8, 8}, oy[4] = {0, 8, 0, 8};
    for (int fr = 0; fr < 4; fr++) {
        uint8_t sel1 = ram[0x70A] == 7 ? ram[0x71A] : anim_banks[fr];   /* (a Toad House: no PT2_Anim - PRG030_8E1D - its own $0800 bank) */
        for (int t = 0; t < 256; t++) {
            int q = t >> 6;
            for (int k = 0; k < 4; k++) {
                uint8_t pat = lay[k * 256 + t];
                for (int y = 0; y < 8; y++) {
                    uint16_t a = (uint16_t)(pat * 16 + y);
                    #define BGCHR(a) chr[(size_t)((((a) < 0x800 ? sel0 : sel1) & 0xFE) | (((a) >> 10) & 1)) % nchr * 0x400 + ((a) & 0x3FF)]
                    uint8_t lo = BGCHR(a), hi = BGCHR((uint16_t)(a + 8));
                    for (int x = 0; x < 8; x++) {
                        int p = ((lo >> (7 - x)) & 1) | (((hi >> (7 - x)) & 1) << 1);
                        frame[fr][((t / 16) * 16 + oy[k] + y) * 256 + (t % 16) * 16 + ox[k] + x] = p ? ppu_rgb(ppu_peek_pal(q * 4 + p)) : (ppu_rgb(ppu_peek_pal(0)) & 0x00FFFFFFu) | BACKDROP_A;   /* (the backdrop colour marked: see tex_upload) */
                    }
                }
            }
        }
    }
    memcpy(atlas, frame[0], sizeof frame[0]);
    int slot = 256, nanim = 0;
    for (int t = 0; t < 256; t++) {
        anim_slot[t] = -1;
        int differs = 0;
        for (int fr = 1; fr < 4 && !differs; fr++)
            for (int y = 0; y < 16 && !differs; y++) differs = memcmp(&frame[0][((t / 16) * 16 + y) * 256 + (t % 16) * 16], &frame[fr][((t / 16) * 16 + y) * 256 + (t % 16) * 16], 64) != 0;
        if (!differs || slot + 3 > (TEX_H_MAX / 16) * 16 - 80 - (ram[0x70A] == 7 ? 48 : 0) - ((ram[0x1E] >= 3 && ram[0x1E] <= 6) || list_has_bros(wram) ? 16 : 0)) continue;   /* (room kept for the sprites below: ~72 slots; a Toad House's Toad, items and letters ~48 more) */
        anim_slot[t] = (int16_t)slot; nanim++;
        for (int fr = 1; fr < 4; fr++, slot++)
            for (int y = 0; y < 16; y++) memcpy(&atlas[((slot / 16) * 16 + y) * 256 + (slot % 16) * 16], &frame[fr][((t / 16) * 16 + y) * 256 + (t % 16) * 16], 64);
    }
    /* the item sprites (8 x 16 sprite patterns, ObjectGroup00_PatternSets / _Attributes): from the
       sprite banks PatTable_BankSel+2..5 ($1000-$1FFF) and the sprite palettes; a pair of the same
       pattern is drawn mirrored on the right */
    { static int lg; if (!lg++ || getenv("SMB3_SLOTLOG")) rt_log("smb3", "stage: animated tiles end at slot %d", slot); }
    slot = (slot + 15) / 16 * 16; spr_slot0 = slot;
    static const uint8_t spr_pat[NSPR][2] = {{0x51, 0x51}, {0x51, 0x51}, {0x55, 0x55}, {0x53, 0x53}, {0x5D, 0x5F}, {0x91, 0x91}};
    static const uint8_t spr_pal[NSPR] = {1, 2, 0, 2, 1, 2};
    for (int i = 0; i < NSPR; i++, slot++)
        for (int half = 0; half < 2; half++) {
            uint8_t n = spr_pat[i][half]; int mirror = half == 1 && spr_pat[i][0] == spr_pat[i][1];
            for (int y = 0; y < 16; y++) {
                uint16_t a = (uint16_t)((n & 1) * 0x1000 + ((n & 0xFE) + (y >> 3)) * 16 + (y & 7));
                uint8_t bank = a >= 0x1000 ? ram[0x71B + ((a - 0x1000) >> 10)] : (uint8_t)((ram[0x719 + (a >> 11)] & 0xFE) | ((a >> 10) & 1));
                if (i == SPR_FROG) bank = FROG_SUIT_CHR_BANK;                /* (the suits' bank, whatever the level has loaded) */
                const uint8_t *c = chr + (size_t)(bank % nchr) * 0x400 + (a & 0x3FF);
                for (int x = 0; x < 8; x++) {
                    int bit = mirror ? x : 7 - x;
                    int p = ((c[0] >> bit) & 1) | (((c[8] >> bit) & 1) << 1);
                    atlas[((slot / 16) * 16 + y) * 256 + (slot % 16) * 16 + half * 8 + x] = p ? ppu_rgb(ppu_peek_pal(16 + spr_pal[i] * 4 + p)) : 0;
                }
            }
        }
    /* the single 8 x 16 sprites (half_pat / half_pal), two a slot */
    half_slot0 = slot;
    for (int f = 0; f < NHALF; f++) {
        int sl = slot + (f >> 1), xo = (f & 1) * 8; uint8_t n = half_pat[f];
        for (int y = 0; y < 16; y++) {
            uint16_t a = (uint16_t)((n & 1) * 0x1000 + ((n & 0xFE) + (y >> 3)) * 16 + (y & 7));
            uint8_t bank = a >= 0x1000 ? ram[0x71B + ((a - 0x1000) >> 10)] : (uint8_t)((ram[0x719 + (a >> 11)] & 0xFE) | ((a >> 10) & 1));
            const uint8_t *c = chr + (size_t)(bank % nchr) * 0x400 + (a & 0x3FF);
            for (int x = 0; x < 8; x++) {
                int p = ((c[0] >> (7 - x)) & 1) | (((c[8] >> (7 - x)) & 1) << 1);
                atlas[((sl / 16) * 16 + y) * 256 + (sl % 16) * 16 + xo + x] = p ? ppu_rgb(ppu_peek_pal(16 + half_pal[f] * 4 + p)) : 0;
            }
        }
    }
    slot += (NHALF + 1) / 2;
    /* the Raccoon placeholder (pixels: 1 the suit colour, 2 $36, 3 $0F) */
    rc_slot0 = slot;
    for (int c = 0; c < NRCOL; c++) for (int k = 0; k < NRC; k++) {
        int h = c * NRC + k, sl = slot + (h >> 1), xo = (h & 1) * 8;
        uint32_t col[4] = {0, ppu_rgb(RC_COLOUR[c]), ppu_rgb(0x36), ppu_rgb(0x0F)};
        for (int y = 0; y < 16; y++) for (int x = 0; x < 8; x++) {
            int p = 0;
            if (k == RC_EAR) { if (y < 8) { char ch = RC_EAR_ART[y][x]; p = ch == 'R' ? 1 : ch == 'S' ? 2 : ch == 'K' ? 3 : 0; } }
            else {
                uint8_t n = RC_TAIL_PAT[k]; const uint8_t *cb = chr + (size_t)(0x00 % nchr) * 0x400 + ((n & 0xFE) + (y >> 3)) * 16 + (y & 7);
                p = ((cb[0] >> (7 - x)) & 1) | (((cb[8] >> (7 - x)) & 1) << 1);
            }
            atlas[((sl / 16) * 16 + y) * 256 + (sl % 16) * 16 + xo + x] = col[p];
        }
    }
    slot += (NRCOL * NRC + 1) / 2;
    eh_render(&slot, chr, nchr, ram);                                   /* (the enemies' sprites) */
    glyph_render(&slot, chr, nchr);                                      /* (the course clear messages' letters) */
    th_render(&slot, chr, nchr, ram);                                    /* (a Toad House: Toad, its items, its letters) */
    if (getenv("SMB3_SLOTLOG")) rt_log("smb3", "stage: sprites end at slot %d", slot);
    objs_load_list(wram);
    bt_render(&slot, chr, nchr, ram, nes_wram_ptr());                    /* (brothers - a map brother's battle, or in the level: them, their hammers / boomerangs, the treasure box) */
    tex_h = (slot + 15) / 16 * 16;
    if (tex_h > TEX_H_MAX) { rt_log("smb3", "stage: the pictures need %d rows, %d fit - the last cut", tex_h, TEX_H_MAX); tex_h = TEX_H_MAX; }
    rt_log("smb3", "stage: %d animated tiles, texture 256 x %d", nanim, tex_h);
    if (getenv("SMB3_STAGE_MAP"))                                        /* (testing: the solidity, rows 14-26) */
        for (int r = 14; r < LH; r++) { char line[200]; int c; for (c = 0; c < L.w && c < 176; c++) { int k = tile_class(L.tile[r * L.w + c]), sh = slope_shape(L.tile[r * L.w + c]); line[c] = k == 2 ? '#' : k == 1 ? '=' : '.';
            if (sh == 0x01 || sh == 0x0C || sh == 0x0D) line[c] = '/'; else if (sh == 0x02 || sh == 0x0E || sh == 0x0F) line[c] = '\\'; else if (sh == 0x05 || sh == 0x06 || sh >= 0x11) line[c] = 'v'; } line[c] = 0; rt_log("smb3", "map %2d %s", r, line); }
    if (getenv("SMB3_STAGE_BLOCKS"))                                     /* (testing: where the blocks are) */
        for (int r = 0; r < LH; r++) for (int c = 0; c < L.w; c++) { uint8_t t = L.tile[r * L.w + c]; if (t >= 0x60 && t <= 0x70) rt_log("smb3", "block %02X at %d,%d", t, c, r); }
    L.sky = ppu_rgb(ppu_peek_pal(0));
    L.ok = 1;
    {   const char *ap = getenv("SMB3_STAGE_ATLAS");                   /* (testing: the tile pictures as a PPM) */
        FILE *f = ap ? fopen(ap, "wb") : NULL;
        if (f) { fprintf(f, "P6 256 %d 255\n", tex_h); for (int i = 0; i < 256 * tex_h; i++) { uint8_t c[3] = {(uint8_t)(atlas[i] >> 16), (uint8_t)(atlas[i] >> 8), (uint8_t)atlas[i]}; fwrite(c, 1, 3, f); } fclose(f); } }
    for (const char *e = getenv("SMB3_FIND_TILE"); e && *e; ) { char *q; int t = (int)strtol(e, &q, 16); char b[512]; int o = 0;   /* (testing: where those tiles are - "AD,AF,..") */
        if (q == e) break;
        for (int x = 0; x < L.w && o < 480; x++) for (int y = 0; y < LH; y++) if (L.tile[y * L.w + x] == t) o += snprintf(b + o, sizeof b - o, " %d,%d", x, y);
        rt_log("smb3", "stage: tile %02X at%s", t, o ? b : " -"); e = *q ? q + 1 : q; }
    rt_log("smb3", "stage: level (tileset %d) loaded: %d x %d tiles, solidity %02X %02X %02X %02X / %02X %02X %02X %02X", nes_ram_ptr()[0x70A], L.w, LH,
           L.attr[0], L.attr[1], L.attr[2], L.attr[3], L.attr[4], L.attr[5], L.attr[6], L.attr[7]);
    return 1;
}

/* ---- the flow ---- */
static void player_scale(int on);
static void blocks_reset(void);
static int wb_hidden(int n);                     /* (a player behind the scenes - the white blocks) */
static int pipe_open_cell(int tx, int ty), pipe_hidden(int n); static void pipe_exit_placed(void);   /* (smb3_stage_pipes.inc) */
static int pswitch_left(void); static void pswitch_resume(int cnt);
static void pipe_frame(uint32_t pl, int n, int big, float px, float py, float h), pipe_player_exec(uint32_t pl, int n), pipes_reset(void);
int retro_is_player(uint32_t pl);               /* rt_retro.c */
#define PLAYER_SCALE    0.80f                    /* (user, 2026-11-21: 80%; the 3D characters only, not Retro Mario) */
/* a death (or time up) with lives left: NSMBW would go to its world map - SMB3 has no map here yet,
   so the level starts again (rt_lyt.c's DoSceneChange asks, for the world map scene) */
int smb3_stage_restart(ppc_context *ctx, uint8_t *base) {
    if (!smb3_stage_on() || probe) return 0;
    if (map_on()) return map_again(ctx, base);                           /* (on the map: NSMBW's way out of a course - the map again) */
    int any = 0; for (int i = 0; i < 8; i++) if (R32(WP_ENTRY_TABLE + 4 * (uint32_t)i) && (int)R32(MOD_PY_REST + 4 * (uint32_t)i) > 0) any = 1;
    if (!any) return 0;                                                  /* (game over: NSMBW's own) */
    if (music_death_left() > 0) {                                        /* (SMB3's death song first: the restart from the next frames' draw) */
        if (!restart_wait) rt_log("smb3", "stage: the restart waits %d frames for the death song", music_death_left());
        restart_wait = 1; return 1; }
    restart_wait = 0;
    if (map_shown_level() && map_level_end(ctx, base, 1)) return 1;      /* (SMB3's map: back to it, the life lost) */
    rt_log("smb3", "stage: a player down - 1-1 again");
    keep_counters = 1; int r = smb3_stage_begin(ctx, base); keep_counters = 0;
    return r;
}
/* the level's own state, fresh: SMB3's loader again, the blocks back, the clock full */
static int reload_pending, reload_keep;          /* (a restart from inside a stage: done once the old stage has gone) */
static int level_fresh(void) {
    if (!level_load()) return 0;
    L.placed = 0; tex_ready = 0;
    if (!jct_restart) { SB.time = SB.time0; SB.tick = 0x28; SB.ptick = 0; }
    /* a P-switch running through a pipe goes on in the other area (SMB3's Level_PSwitchCnt is the
       game's, not the area's: PSwitch_SubstTileAndAttr swaps the new area's tiles as they're read) -
       its count kept, the other area's coins / bricks swapped, its song on (music_bg_want) */
    int ps_keep = jct_restart ? pswitch_left() : 0;
    jct_restart = 0; pipes_reset(); memset(lifted, 0, sizeof lifted);
    L.ok = 0;                                                            /* (a fresh 1-1 each time: blocks back) */
    blocks_reset();
    if (ps_keep) pswitch_resume(ps_keep);
    return 1;
}
/* what the next stage scene shows, made ready: SMB3's map (placed afresh), or a level (loaded
   afresh: 1-1 by the old way, or the level SMB3's map brought up) */
static int stage_fresh(void) {
    map_apply_next();
    if (map_on()) { L.placed = 0; return 1; }
    return level_fresh();
}
static void reload_now(void) {
    if (!reload_pending) return;
    reload_pending = 0;
    int k = keep_counters; keep_counters = reload_keep;
    if (!stage_fresh()) rt_log("smb3", "stage: the level failed to load again");
    keep_counters = k;
}
static int keep_modes;                           /* (a restart that keeps the players' power-ups: a pipe's / door's junction - smb3_stage_pipes.inc) */
static int stage_start_game(ppc_context *ctx, uint8_t *base) {
    /* a restart from inside a stage (a death, the goal, the map's panels): the old stage stays on
       screen through NSMBW's wipe, so it keeps its level - the next one loads once the scene has
       left it. (Reset here, the old stage showed NSMBW's course under it while the wipe ran) */
    await_scene = R16(G_NOW_SCENE) == 5;
    if (await_scene && active && L.placed) { reload_pending = 1; reload_keep = keep_counters || map_session_on(); }
    else { reload_pending = 0; int k = keep_counters; keep_counters = k || map_session_on(); int ok = stage_fresh(); keep_counters = k; if (!ok) return 0; }
    active = 1;
    player_scale(1);
    /* the players: everyone the character select took (dInfo +900 = 3; slots 4-7 the 8-player
       module's, 1992 further), small */
    uint32_t info = R32(G_DINFO); int n = 0;
    for (int i = 0; i < 8; i++) {
        uint32_t st = R32(info + (i >= 4 ? 1992 : 0) + 900 + 4 * (uint32_t)i);
        int on = st == 3;
        W32(WP_ENTRY_TABLE + 4 * (uint32_t)i, (uint32_t)on);
        if (on) { uint32_t k = R32(WP_ACTIVE_TABLE + 4 * (uint32_t)i); if (k < 8 && !keep_modes) W32(WP_SCENE_TABLE + 4 * k, 0); n++; }   /* (small - not after a pipe / door: keep_modes) */
    }
    if (!n) { W32(WP_ENTRY_TABLE, 1); n = 1; }
    W32(info + 80, 0); W32(info + 84, 0); W8(info + 109, 0);
    rt_log("smb3", "stage: %d player(s)", n);
    /* dInfo_c::startGame: course 1-1 (the shell), area 1, entrance 0 */
    for (int i = 0; i < 16; i += 4) W32(SM_START_INFO + i, 0);
    W8(SM_START_INFO + 12, 0); W8(SM_START_INFO + 13, 0); W8(SM_START_INFO + 14, 0); W8(SM_START_INFO + 15, 0);
    rt_log("smb3", "stage: starting (NSMBW course 1-1 as the shell)%s", probe ? " - probe: NSMBW's tiles kept, flags logged" : "");
    if (!probe) {
        /* SMB3 has no course intro: from the map (or a death, the goal) the screen goes black and
           the level's palette fades in (PRG030: Palette_FadeIn after the level loads). NSMBW's
           course intro (scene 7) shown off - dScCrsin_c::m_isDispOff, as the title's restart sets
           it: the scene waits 1 frame instead of 120 and draws nothing - and the plain colour
           fade (dFader_c type 0), which smb3_stage_fader below turns into SMB3's palette fade */
        gcall(ctx, base, A_SET_FADER, 1, 0);
        W8(A_CRSIN_DISP_OFF, 1);
    }
    gcall(ctx, base, A_START_GAME, 2, R32(G_DINFO), SM_START_INFO);
    return 1;
}
/* Start Game (rt_gamesetup.c), and the old restarts: SMB3's map first when it's on (smb3_map.inc),
   else 1-1 */
int smb3_stage_begin(ppc_context *ctx, uint8_t *base) {
    probe = getenv("SMB3_STAGE_PROBE") != NULL;
    if (R16(G_NOW_SCENE) != 5) { map_session_stop(); if (map_enabled() && !probe) map_session_start(1); }   /* (from the setup screens: a new game) */
    return stage_start_game(ctx, base);
}
/* ---- the players at 80% (SMB3's tiles stay on NSMBW's 16-unit grid: NSMBW's collision snaps to
   it) - their models (dPyMdlMng_c's level scales, while the stage runs) and their background
   sensors (after each dAcPy_c::setBcData, gm_d_player_conv.c) ---- */
#define A_MDL_SCALES    0x80370DA8u              /* float[]: each model's scale in levels (dPyMdlMng_c::m_hio) */
#define NSCALES         7                        /* (the 3D models' entries: 1.0 x3, 0.6 (mini), 1.0 x3; past them other settings) */
static float scale_saved[NSCALES]; static uint8_t scale_changed[NSCALES]; static int scaled;
static void WF(uint32_t a, float f) { W32(a, fbits(f)); }
static void player_scale(int on) {
    if (on == scaled) return;
    scaled = on;
    for (int i = 0; i < NSCALES; i++) {
        uint32_t a = A_MDL_SCALES + 4 * (uint32_t)i;
        if (on) { scale_saved[i] = RF(a); scale_changed[i] = scale_saved[i] > 0.2f && scale_saved[i] < 4.0f; if (scale_changed[i]) WF(a, scale_saved[i] * PLAYER_SCALE); }
        else if (scale_changed[i]) WF(a, scale_saved[i]);
    }
    if (on) { char b[200]; int k = 0; for (int i = 0; i < NSCALES; i++) k += snprintf(b + k, sizeof b - k, " %.2f", scale_saved[i]); rt_log("smb3", "stage: players at %.0f%% (model scales%s)", PLAYER_SCALE * 100, b); }
}
void smb3_stage_player_sensors(uint32_t pl) {
    if (!smb3_stage_on() || retro_is_player(pl)) return;                 /* (Retro Mario: SMB1's size already) */
    { static int shown; if (getenv("SMB3_STAGE_SENSORS") && shown++ < 3) { char t[200]; int o = 0;
        for (uint32_t k = 0; k < 3; k++) for (uint32_t j = 0; j < 4; j++) o += snprintf(t + o, sizeof t - o, "%s%d", j ? "," : " | ", j ? (int)(int32_t)R32(pl + 4244 + 16 * k + 4 * j) / 4096 : (int)R32(pl + 4244 + 16 * k));
        rt_log("smb3", "sensors before scaling (head | foot | wall: flags, then 3 offsets): %s", t); } }
    for (uint32_t k = 0; k < 3; k++) {                                   /* foot, head, wall: flags + three 1/4096 coordinates */
        uint32_t s = pl + 4244 + 16 * k;
        for (uint32_t j = 1; j < 4; j++) {
            float v = (float)(int32_t)R32(s + 4 * j) * PLAYER_SCALE;
            /* (the wall sensor in whole units: NSMBW pushes a player out of a wall to the edge plus
               the offset rounded one way on the left and the other on the right - 6.4 left a
               player 7 from a wall on its left, 6.1 from one on its right: a gap on one side) */
            if (k == 2) v = roundf(v / 4096.0f) * 4096.0f;
            W32(s + 4 * j, (uint32_t)(int32_t)v);
        }
    }
}
static int in_stage(void) { return R16(G_NOW_SCENE) == 5 && R32(G_GAME_MODE) != 2; }
int smb3_stage_on(void) {                        /* (on from Start Game through the course intro (scene 7) into the stage; off once elsewhere) */
    int sc = R16(G_NOW_SCENE);
    if (sc != 5) plats_off();                                           /* (the stage gone: the platforms' lines out of NSMBW's list - smb3_stage_enemies.inc) */
    if (sc != 5 && (reload_pending || await_scene)) { await_scene = 0; reload_now(); }   /* (the old stage gone: the level fresh for the new one - the course intro is a few frames now) */
    if (active && sc != 5 && sc != 7 && sc != 10) { active = 0; player_scale(0); }
    return active && in_stage();
}
/* NSMBW's fader in the SMB3 game mode (gm_m_fader.c's mFader_c::draw asks; 1: not drawn).
   In the stage: SMB3's palette fade in its place (rt_gxgl.inc draws it on the whole picture) -
   PRG026's Palette_DoFadeIn / Palette_DoFadeOut step the palette every 4 frames (Fade_Tick), 4
   steps: the colour fader made 16 frames long, a step per 4 of them; held black (opaque) or off
   (hidden). In the course intro between (shown off): the colour fader, made short. */
void rt_nes_fade(int mode, int step, const uint32_t *argb64);   /* rt_gxgl.inc */
int smb3_stage_fader(uint32_t fd) {
    if (!active || probe || !fd) return 0;
    int sc = R16(G_NOW_SCENE); uint32_t st = R32(fd + 4);
    if (sc != 5) smb3_stage_on();                                       /* (the scene between: the next stage's level made ready) */
    int col = R32(fd) == VT_COLOR_FADER;
    if (sc == 7) { if (col && (st == 2 || st == 3) && R16(fd + 10) > 2) W16(fd + 10, 2); return 0; }
    if (!smb3_stage_on()) return 0;
    static uint32_t pal[64]; static int have;
    if (!have) { for (int i = 0; i < 64; i++) pal[i] = ppu_rgb(i); have = 1; }
    if ((st == 2 || st == 3) && R16(fd + 10) > 16 && R16(fd + 10) < 600) W16(fd + 10, 16);   /* (a fader that counts frames: SMB3's 16; a layout wipe ends by its animation) */
    /* (the frames counted here: a layout wipe NSMBW chose itself counts none) */
    static uint32_t lfd, lst; static int k; extern uint64_t g_frames_presented; static uint64_t lf;
    if (fd != lfd || st != lst) { lfd = fd; lst = st; k = 0; lf = g_frames_presented; }
    else if (lf != g_frames_presented) { lf = g_frames_presented; k++; }
    int cur = k, step = cur / 4; if (step > 4) step = 4;
    if (getenv("SMB3_STAGE_FADELOG") && st != 1) rt_log("smb3", "fade: scene %d fader %08X (vtable %08X) status %u frame %d of %d step %d", sc, fd, R32(fd), st, cur, R16(fd + 10), step);
    rt_nes_fade(st == 0 ? 3 : st == 2 ? 1 : st == 3 ? 2 : 0, step, pal);
    return 1;
}
int smb3_stage_suppress_actors(void) { return smb3_stage_on() && !probe; }
float smb3_stage_player_scale(uint32_t pl) { return smb3_stage_on() && !probe && !retro_is_player(pl) ? PLAYER_SCALE : 1.0f; }   /* (gm_d_player.c: offsets that go with the model's size) */

/* the players as last drawn (for solid-on-top: who is rising) */
static struct { int on; float x, y, vy; } rising[8];
/* NSMBW unit flags for SMB3's kinds (read from the course's own tiles: SMB3_STAGE_PROBE) */
/* (hi word: 0x01 solid, 0x20 solid on top, 0x40 ? block (low byte: its item), 0x04 breakable,
   0x10000 pipe; low word 0x000D0000: the course's ground kind - as the course's own tiles have them) */
static const uint64_t UNIT_SOLID = 0x0000000100000000ull, UNIT_TOP = 0x00000020000D000Aull;   /* (low byte 0x0A: NSMBW's flat one-way top; 0-5 and 0x0B-0x12 are its slopes, 0 no top at all - SMB3_STAGE_PROBE on 1-1) */
int smb3_stage_unit(uint32_t x, uint32_t y, uint64_t *flags) {
    if (map_on()) return 0;                                              /* (SMB3's map: nothing to stand on - its players don't run) */
    if (!smb3_stage_on() || probe) return 0;
    *flags = 0;
    if (!L.placed) return 1;
    int tx = (int)floorf(((float)(int32_t)(x & 0xFFFF) - L.lx) / 16.0f), ty = (int)floorf(((float)(int32_t)(y & 0xFFFF) - L.ly) / 16.0f);
    if (tx < 0 || tx >= L.w) { *flags = UNIT_SOLID; return 1; }       /* (the level's ends: walls - SMB3's scroll stops there and the Player with it) */
    if (ty >= LH) return 1;
    if (ty < 0) ty = 0;                                                  /* (above the level: as its top row - walls stay walls) */
    {   const char *e = getenv("SMB3_STAGE_TEST_NSMBW_TILE");          /* (testing: that cell is NSMBW's own) */
        for (int c, r, t, k; e && sscanf(e, "%d,%d,%x%n", &c, &r, &t, &k) == 3; e += k + (e[k] == ';')) if (c == tx && r == ty) return 0; }
    {   const char *e = getenv("SMB3_STAGE_TEST_UNIT");                /* (testing: "col,row,hi,lo;..." - that cell given those NSMBW unit flags, hex) */
        unsigned hi, lo; for (int c, r, k; e && sscanf(e, "%d,%d,%x,%x%n", &c, &r, &hi, &lo, &k) == 4; e += k + (e[k] == ';'))
            if (c == tx && r == ty) { *flags = (uint64_t)hi << 32 | lo; return 1; } }
    if (pipe_open_cell(tx, ty)) return 1;                               /* (a player going into a pipe: through it) */
    int sh = slope_shape(L.tile[ty * L.w + tx]);
    {   int64_t u = slope_unit(sh);                                      /* (a slope: NSMBW's own slope of that shape) */
        if (u >= 0) { *flags = (uint64_t)u; return 1; } }
    int c = sh >= 0 ? (sh == 0 ? 0 : sh == 0x07 ? 1 : 2) : tile_class(L.tile[ty * L.w + tx]);   /* (a slope level: the rest by shape - squares, walls, ceilings solid; unsloped ground a floor) */
    /* solid on top: only the top of it. SMB3 lands the player on such a tile's top edge only (its
       big blocks are solid on top all the way down); NSMBW's are one tile thick, and a stack of
       them lifts a player inside it row by row */
    if (c == 1 && ty > 0 && tile_class(L.tile[(ty - 1) * L.w + tx]) == 1) c = 0;
    /* (user, 2026-11-22: semi-solids are NSMBW's one-way platforms - its flag on the top row. NSMBW
       lands a player on one only from above; given a whole tile it caught feet anywhere inside
       it (a short hop at the edge floated up onto it). So the flag goes only to the player whose
       feet were at or above the top edge last frame - the player nearest the point asked) */
    if (c == 1) {
        float qx = (float)(int32_t)(x & 0xFFFF), qy = (float)(int32_t)(y & 0xFFFF), top = L.ly + ty * 16, best = 1e9f; int who = -1;
        for (int i = 0; i < 8; i++) {
            if (!rising[i].on || fabsf(qx - rising[i].x) >= 20) continue;
            float d = fabsf(qy - -rising[i].y);
            if (d < 48 && d < best) { best = d; who = i; }
        }
        if (who >= 0 && -rising[who].y > top + 1.0f) c = 0;
    }
    if (getenv("SMB3_STAGE_OLD_SEMI") && c == 1) {                     /* (testing: the old stand-in - the upper 8 units, not while rising) */
        float ly_q = (float)(int32_t)(y & 0xFFFF);
        if (ly_q - (L.ly + ty * 16) >= 8) c = 0;
        else for (int i = 0; i < 8; i++)
            if (rising[i].on && rising[i].vy > 0 && fabsf((float)(int32_t)(x & 0xFFFF) - rising[i].x) < 20 && ly_q > -rising[i].y - 48 && ly_q < -rising[i].y + 24) { c = 0; break; }
    }
    *flags = c == 2 ? UNIT_SOLID : c == 1 ? UNIT_TOP : 0;
    return 1;
}

/* ---- the probe: the course's tiles and their flags ---- */
static void probe_tiles(ppc_context *ctx, uint8_t *base) {
    uint32_t tms = R32(BG_TILEMAPS), area = R8(R32(BG_AREA) + 4622);
    static uint16_t seen[1024]; static int nseen; static uint32_t cnt[1024];
    for (int layer = 0; layer < 3; layer++) {
        uint32_t tm = R32(tms + area * 12 + 4 * layer + 52);
        if (!tm) continue;
        for (int b = 0; b < 256; b++) {
            uint32_t p = R32(tm + 4 * b + 4);
            if (!(p >= 0x80000000u && p < 0x94000000u)) continue;
            for (int i = 0; i < 256; i++) {
                uint16_t t = R16(p + 2 * i); if (!t) continue;
                int k; for (k = 0; k < nseen && seen[k] != t; k++) ;
                if (k == nseen && nseen < 1024) { seen[nseen] = t; cnt[nseen] = 0; nseen++; }
                if (k < 1024) cnt[k]++;
            }
        }
        rt_log("smb3", "probe: layer %d tilemap %08X", layer, tm);
    }
    uint32_t tbl = R32(R32(BG_GM) + 112);                                /* (gm_bg.c unit_info: 8 bytes a tile number) */
    for (int k = 0; k < nseen; k++) {
        uint32_t a = tbl + ((uint32_t)(seen[k] & 0x3FF) << 3);
        rt_log("smb3", "probe: tile %04X x%u: flags %08X %08X", seen[k], cnt[k], R32(a), R32(a + 4));
    }
    (void)ctx; (void)base;
}
/* the course's own tiles emptied (its tilemap, every layer of the area) */
static void empty_course(void) {
    uint32_t tms = R32(BG_TILEMAPS), area = R8(R32(BG_AREA) + 4622);
    for (int layer = 0; layer < 3; layer++) {
        uint32_t tm = R32(tms + area * 12 + 4 * layer + 52);
        if (!tm) continue;
        for (int b = 0; b < 256; b++) { uint32_t p = R32(tm + 4 * b + 4); if (p >= 0x80000000u && p < 0x94000000u) for (int i = 0; i < 256; i++) W16(p + 2 * i, 0); }
    }
}

/* ---- blocks and items: ports of SMB3's routines (PRG001 / PRG007 / PRG000), in SMB3's own units:
   positions in level pixels x16 (y down, from the level's top left), velocities in 1/16 pixel a
   frame (SMB3's 4.4 fixed point), the same order of steps each frame and SMB3's timers.
   Each player each frame (from its draw, after its physics): the coins its box overlaps; a new
   head bump (NSMBW's own mNowBgCross1 bit 1) hits the block above its head. ---- */
#define PL_MODE         0x1090
#define PL_BG_CROSS1    0x10D4
#define PL_PLR_NO       0x38D
#define PL_SPEED        0x0E8
#define A_CHANGE_POWERUP 0x80145AC0u            /* dAcPy_c__ChangePowerupWithAnimation (the change with its animation) */
enum { T_SKY = 0x80, T_BUMPCLEAR = 0xF3, T_COIN = 0x40, T_USED = 0x5F, T_QFLOWER = 0x60, T_QLEAF, T_QSTAR, T_QCOIN, T_QCOINSTAR, T_QCOIN2,
       T_BRICK = 0x67, T_BFLOWER, T_BLEAF, T_BSTAR, T_BCOIN, T_BCOINSTAR, T_B10COIN, T_B1UP, T_BVINE, T_BPSWITCH };
#define A_IS_STAR        0x80022170u            /* daPlBase_c::isStar() const */
#define A_TEST_FLAG      0x80056CF0u            /* daPlBase_c::testFlag(int) (isStatus) */
#define STATUS_HIP_FALL  28                     /* (the ground pound's fall) */
#define AC_VTABLE        96
#define VT_SET_STAR      984                    /* dAcPy_c::setStar(set, timer) */
static struct { int coins; uint32_t score; int cards[3]; } SG;   /* SMB3's own counters, the score in tens; Inventory_Cards (0 none, 1 mushroom, 2 flower, 3 star) */  /* SMB3's own counters, the score in tens (its status bar comes later) */
static int tick;                                 /* (Counter_1 / Level_NoStopCnt: +1 a frame) */
static int hit_who;                              /* (the player who hit a block: n) */
/* -- the Raccoon suit (the players' side: NSMBW has no such form - the player stays Super and
   this flag says Raccoon; the tail and ears are drawn at the model's joints) -- */
static struct { int on; uint32_t mdl; int hold; int colour, have; float hips[12], head[12]; int tanim; float tframe; float tv[130][3]; uint8_t tl[130]; float tail[3], fwd[3], ear[2][3]; float tail_s; int tail_pose, face_left; } rc[8];
static struct { int power, pmcnt, fly, wag, tail, run, jump_was, dash_was, ground_was, pstate, pstate_was, wag_anim, fly_anim; uint32_t speed_orig; float pcap; } pm[8];
static int pm_full(int n) { return n >= 0 && n < 8 && pm[n].power == 0x7F; }
static int pm_pspeed(int n) { return n >= 0 && n < 8 && pm[n].pstate; }
/* -- the Raccoon animations: NSMB2's (its rig is NSMBW's), made NSMBW CHR0 by tools/nsmb2_anims.py
   and linked in (smb3_raccoon_anm). They get ids of their own: entries like the game's player
   animation table's (36 bytes: names, settings - copied from a like animation of the game's)
   past its end, in our memory, at the ids that land there; dPyMdlBase_c::setAnm
   (StartAnimOrig) takes them as its own, reading them from our archive while the model's
   animation file (+0x210, the ResFile vtable +44 gives) points there for the call -- */
extern const uint8_t smb3_raccoon_anm[]; extern const size_t smb3_raccoon_anm_size;
void orig_StartAnimOrig(ppc_context *ctx, uint8_t *base);
#define ANM_MEM          0x82100000u             /* the archive */
#define ANM_TAB          0x802F1350u             /* the game's table (177 entries of 36 bytes) */
#define SM_ANM_TAB       (SM_MEM + 0x0300)       /* our entries: the ids that land past here */
#define SM_ANM_NAMES     (SM_MEM + 0x0600)
#define A_START_ANIM     0x800D5DD0u             /* dPyMdlBase_c::setAnm (StartAnimOrig)(mdl, id; f1 rate, f2 blend, f3 frame) */
#define A_RESFILE_INIT   0x8023A590u
#define MDL_RES_ANIM     0x210                   /* dPlayerMdl_c: the animations' ResFile (P_rcha) */
enum { RA_ATTACK_L, RA_ATTACK_R, RA_B_DASH, RA_B_DASH2, RA_FALL, RA_FLY, RA_FLY2, RA_FLY_ST, RA_FLY_C, RA_FLY2_C, RA_FLY_ST_C, RA_RUN, RA_WAIT_L, RA_WAIT_R, RA_F_WAIT, NRA };
static const char *const RA_NAME[NRA] = {"T_attackL", "T_attackR", "T_b_dash", "T_b_dash2", "T_fall", "T_fly", "T_fly2", "T_fly_st",
                                         "T_fly_carry", "T_fly2_carry", "T_fly_st_carry", "T_run", "T_waitL", "T_waitR", "F_wait"};   /* (F_wait: the Frog's idle) */
static const uint8_t RA_LIKE[NRA] = {71, 71, 3, 4, 6, 35, 35, 35, 35, 35, 35, 2, 0, 0, 0};   /* (the game's entry each copies) */
#define RA_PRUN RA_B_DASH2                       /* (NSMB2's Raccoon P-run) */
static int ra_ready; static uint32_t ra_id0;
static void raccoon_anims_init(ppc_context *ctx, uint8_t *base) {
    if (ra_ready) return;
    ra_ready = -1;
    if (smb3_raccoon_anm_size < 16) { rt_log("smb3", "Raccoon: no NSMB2 animations built in (NSMB2_RomFS)"); return; }
    memcpy(G(ANM_MEM), smb3_raccoon_anm, smb3_raccoon_anm_size);
    W32(SM_JMTX + 0x40, ANM_MEM); gcall(ctx, base, A_RESFILE_INIT, 1, SM_JMTX + 0x40);
    ra_id0 = (SM_ANM_TAB - ANM_TAB + 35) / 36;
    for (int k = 0; k < NRA; k++) {
        uint32_t e = ANM_TAB + 36 * (ra_id0 + (uint32_t)k), nm = SM_ANM_NAMES + 16 * (uint32_t)k;
        for (int i = 0; i < 36; i += 4) W32(e + (uint32_t)i, R32(ANM_TAB + 36u * RA_LIKE[k] + (uint32_t)i));
        for (int i = 0; i < 16; i++) W8(nm + (uint32_t)i, (uint8_t)RA_NAME[k][i < (int)strlen(RA_NAME[k]) ? i : (int)strlen(RA_NAME[k])]);
        for (int i = 0; i < 16; i += 4) W32(e + (uint32_t)i, nm);          /* (every variant's name: ours) */
    }
    ra_ready = 1;
    rt_log("smb3", "Raccoon: %d NSMB2 animations (%u bytes), ids %u+", NRA, (unsigned)smb3_raccoon_anm_size, ra_id0);
}
/* -- the NSMB2 animations ported into the player's own animation file: a new BRRES made of the
   model's file (P_rcha) and ours, side by side, under a root of its own whose AnmChr(NW4R)
   group lists both (the group dictionaries - NW4R's Patricia trees - built anew, as wszst /
   BrawlBox build them). The model then simply has them: setAnm, the carry body animation and
   everything else find NSMB2's by name like any of its own, no file swapped for a call -- */
#define MERGE_MEM       0x82200000u              /* (merged files, one per source file: 4 MB each) */
#define MERGE_SPAN      0x00400000u
#define A_GET_RES_ANM_CHR 0x8023A0B0u            /* nw4r::g3d::ResFile::GetResAnmChr(this, name) */
static struct { uint32_t src, dst; } mg[4]; static int nmg;
typedef struct { uint16_t id, left, right; uint32_t name; int len; uint32_t data; } dict_e;   /* (name: guest address of the chars) */
static uint16_t dict_hibit(uint8_t v) { uint16_t i = 7; for (; i > 0 && !(v & 0x80); i--, v <<= 1) ; return i; }
static int dict_bit(const dict_e *e, uint16_t id) { int c = id >> 3; return e->len > c && (R8(e->name + (uint32_t)c) >> (id & 7)) & 1; }
static uint16_t dict_calc_id(const dict_e *o, const dict_e *sub) {
    int ol = o ? o->len : 0, sl = sub->len;
    if (ol < sl) return (uint16_t)((sl - 1) << 3 | dict_hibit(R8(sub->name + (uint32_t)sl - 1)));
    while (sl-- > 0) { uint8_t ch = R8(o->name + (uint32_t)sl) ^ R8(sub->name + (uint32_t)sl); if (ch) return (uint16_t)(sl << 3 | dict_hibit(ch)); }
    return 0xFFFF;
}
static void dict_insert(dict_e *L, int idx) {                          /* (wszst's calc_brres_entry) */
    dict_e *e = &L[idx], *prev = &L[0], *cur = &L[L[0].left];
    e->id = dict_calc_id(0, e); e->left = e->right = (uint16_t)idx;
    int is_right = 0;
    while (e->id <= cur->id && cur->id < prev->id) {
        if (e->id == cur->id) {
            e->id = dict_calc_id(cur, e);
            if (dict_bit(cur, e->id)) { e->left = (uint16_t)idx; e->right = (uint16_t)(cur - L); }
            else { e->left = (uint16_t)(cur - L); e->right = (uint16_t)idx; }
        }
        prev = cur;
        is_right = dict_bit(e, cur->id);
        cur = &L[is_right ? cur->right : cur->left];
    }
    if (dict_bit(cur, e->id)) e->right = (uint16_t)(cur - L); else e->left = (uint16_t)(cur - L);
    if (is_right) prev->right = (uint16_t)idx; else prev->left = (uint16_t)idx;
}
/* a dictionary's entries (guest dict at d): names and data as guest addresses */
static int dict_read(uint32_t d, dict_e *L, int max) {
    int n = (int)R32(d + 4); if (n + 1 > max) return -1;
    for (int i = 1; i <= n; i++) {
        uint32_t e = d + 8 + 16u * (uint32_t)i;
        L[i].name = d + R32(e + 8); L[i].len = (int)R32(L[i].name - 4); L[i].data = d + R32(e + 12);
    }
    return n;
}
/* writes the dictionary at d (entries 1..n), its tree built; returns its size */
static uint32_t dict_write(uint32_t d, dict_e *L, int n) {
    L[0].id = 0xFFFF; L[0].left = L[0].right = 0; L[0].name = 0; L[0].len = 0;
    for (int i = 1; i <= n; i++) dict_insert(L, i);
    uint32_t size = 8 + 16u * (uint32_t)(n + 1);
    W32(d, size); W32(d + 4, (uint32_t)n);
    for (int i = 0; i <= n; i++) {
        uint32_t e = d + 8 + 16u * (uint32_t)i;
        W16(e, L[i].id); W16(e + 2, 0); W16(e + 4, L[i].left); W16(e + 6, L[i].right);
        W32(e + 8, i ? L[i].name - d : 0); W32(e + 12, i ? L[i].data - d : 0);
    }
    return size;
}
static int str_eq(uint32_t a, int la, uint32_t b, int lb) { if (la != lb) return 0; for (int i = 0; i < la; i++) if (R8(a + (uint32_t)i) != R8(b + (uint32_t)i)) return 0; return 1; }
/* the model's file with ours added: built once per source file; 0 if it can't be */
static uint32_t anm_merged(ppc_context *ctx, uint8_t *base, uint32_t src) {
    for (int i = 0; i < nmg; i++) if (mg[i].src == src || mg[i].dst == src) return mg[i].dst;
    if (nmg == 4 || R32(src) != 0x62726573u || R32(ANM_MEM) != 0x62726573u) return 0;   /* ('bres') */
    static dict_e G1[1024], G2[256]; uint32_t dst = MERGE_MEM + MERGE_SPAN * (uint32_t)nmg;
    uint32_t sroot = src + R16(src + 12), oroot = ANM_MEM + R16(ANM_MEM + 12);
    int ng = dict_read(sroot + 8, G2, 64); if (ng < 1) return 0;
    dict_e groups[64]; memcpy(groups, G2, sizeof(dict_e) * (size_t)(ng + 1));
    /* sizes: the root and its group dictionaries first, then the two files whole */
    uint32_t ssize = R32(src + 8), osize = R32(ANM_MEM + 8);
    uint32_t root = dst + 0x10, rdict = root + 8, at = rdict + 8 + 16u * (uint32_t)(ng + 1);
    uint32_t gpos[64]; int gn[64];
    for (int g = 1; g <= ng; g++) {
        int n = (int)R32(groups[g].data + 4), extra = 0;
        { dict_e O[64]; int og = dict_read(oroot + 8, O, 64);
          for (int k = 1; k <= og; k++) if (str_eq(groups[g].name, groups[g].len, O[k].name, O[k].len)) extra = (int)R32(O[k].data + 4); }
        gpos[g] = at; gn[g] = n + extra; at += 8 + 16u * (uint32_t)(n + extra + 1);
    }
    uint32_t scopy = (at + 0x1F) & ~0x1Fu, ocopy = (scopy + ssize + 0x1F) & ~0x1Fu, end = ocopy + osize;
    if (end - dst > MERGE_SPAN) { rt_log("smb3", "Raccoon: the animation file is too big to merge (%u bytes)", ssize); return 0; }
    memmove(G(scopy), G(src), ssize); memmove(G(ocopy), G(ANM_MEM), osize);
#define S2D(a) ((a) - src + scopy)
#define O2D(a) ((a) - ANM_MEM + ocopy)
    /* each group: the source's entries, then ours of the same group not already there */
    dict_e O[64]; int og = dict_read(oroot + 8, O, 64);
    for (int g = 1; g <= ng; g++) {
        int n = dict_read(groups[g].data, G1, 1000); if (n < 0) return 0;
        for (int i = 1; i <= n; i++) { G1[i].name = S2D(G1[i].name); G1[i].data = S2D(G1[i].data); }
        for (int k = 1; k <= og; k++) if (str_eq(groups[g].name, groups[g].len, O[k].name, O[k].len)) {
            int m = dict_read(O[k].data, G2, 250);
            for (int j = 1; j <= m; j++) {
                int dup = 0; for (int i = 1; i <= n; i++) if (str_eq(G1[i].name, G1[i].len, O2D(G2[j].name), G2[j].len)) dup = 1;
                if (dup || n >= 1000) continue;
                n++; G1[n].name = O2D(G2[j].name); G1[n].len = G2[j].len; G1[n].data = O2D(G2[j].data);
            }
        }
        for (int i = 1; i <= n; i++) W32(G1[i].data + 12, (uint32_t)(int32_t)(dst - G1[i].data));   /* (each sub-file's header: magic, size, version, then its offset to its BRRES - the new one) */
        dict_write(gpos[g], G1, n); gn[g] = n;
        groups[g].data = gpos[g]; groups[g].name = S2D(groups[g].name);
    }
    dict_write(rdict, groups, ng);
    W32(root, 0x726F6F74u); W32(root + 4, at - root);                    /* ('root') */
    int nsub = 0; for (int g = 1; g <= ng; g++) nsub += gn[g];
    W32(dst, 0x62726573u); W16(dst + 4, 0xFEFF); W16(dst + 6, 0); W32(dst + 8, end - dst); W16(dst + 12, 0x10); W16(dst + 14, (uint16_t)(1 + nsub));
#undef S2D
#undef O2D
    W32(SM_JMTX + 0x40, dst); gcall(ctx, base, A_RESFILE_INIT, 1, SM_JMTX + 0x40);
    /* checked: every one of ours, and the source's first animations, found by the game's own lookup */
    int bad = 0;
    extern const int smb3_frog_wait_ok;
    for (int k = 0; k < NRA; k++) if (!(k == RA_F_WAIT && !smb3_frog_wait_ok) && !gcall(ctx, base, A_GET_RES_ANM_CHR, 2, SM_JMTX + 0x40, SM_ANM_NAMES + 16u * (uint32_t)k)) bad++;   /* (F_wait: only when the archive has it - else the merge was refused, and tried again every frame) */
    {   int sbad = 0, nn = 0;                  /* (the source's names, through both files) */
        uint32_t ad = 0; for (int g = 1; g <= ng; g++) { const char *want = "AnmChr(NW4R)"; int wl = 12, same = groups[g].len == wl;
            for (int i = 0; same && i < wl; i++) if (R8(groups[g].name + (uint32_t)i) != (uint8_t)want[i]) same = 0;
            if (same) ad = groups[g].data; }
        if (ad) { int n = dict_read(ad, G1, 1000); for (int i = 1; i <= n; i++) { nn++;
            uint32_t a = gcall(ctx, base, A_GET_RES_ANM_CHR, 2, SM_JMTX + 0x40, G1[i].name);
            if (a != G1[i].data) sbad++; } }
        rt_log("smb3", "Raccoon: animations merged into %08X (%u bytes: %08X's %u + ours %u): %d animations, %d of ours missing, %d mislooked", dst, end - dst, src, ssize, osize, nn, bad, sbad);
        if (bad || sbad || !nn) return 0; }
    mg[nmg].src = src; mg[nmg].dst = dst; nmg++;
    return dst;
}
static void ra_play(ppc_context *ctx, uint8_t *base) {
    /* (setAnm also re-sets the carry body animation (its fn_800D6460, while m_17c carries: 2
       a held object, 4 a lifted player) - by name, from the same ResFile. With ours swapped in it
       found nothing and left the arms in their bind pose, straight out, for good: the user's
       T-pose after a flutter with a shell held. So the carry bits are off for the swap - the
       body animation already bound stays as it was) */
    uint32_t mdl = ctx->r[3], old = R32(mdl + MDL_RES_ANIM), carry = R32(mdl + 380) & 6;
    W32(mdl + 380, R32(mdl + 380) & ~6u);
    W32(mdl + MDL_RES_ANIM, ANM_MEM); orig_StartAnimOrig(ctx, base); W32(mdl + MDL_RES_ANIM, old);
    W32(mdl + 380, R32(mdl + 380) | carry);
}
/* a Raccoon animation by us: rate, blend frames; hold: the game's own requests wait until released */
static void ra_start(ppc_context *ctx, uint8_t *base, int n, int k, float rate, float blend, int hold) {
    if (ra_ready <= 0 || n < 0 || n > 7 || !rc[n].mdl) return;
    ppc_fpr f1 = ctx->f[1], f2 = ctx->f[2], f3 = ctx->f[3];
    ctx->f[1].d = ctx->ps1[1] = rate; ctx->f[2].d = ctx->ps1[2] = blend; ctx->f[3].d = ctx->ps1[3] = 0.0;
    gcall(ctx, base, A_START_ANIM, 2, rc[n].mdl, ra_id0 + (uint32_t)k);
    ctx->f[1] = f1; ctx->f[2] = f2; ctx->f[3] = f3;
    rc[n].hold = hold ? k : -1;
}
/* dPyMdlBase_c::setAnm (rt_menu.c's hle_StartAnimOrig asks here first): ours play from our
   archive; while one of ours holds, the game's requests wait; for a Raccoon player, the game's
   dash becomes the Raccoon's. 1: done here */
int smb3_stage_anim(ppc_context *ctx, uint8_t *base) {
    if (ra_ready <= 0 || map_on()) return 0;
    uint32_t mdl = ctx->r[3], id = ctx->r[4];
    if (id >= ra_id0 && id < ra_id0 + NRA) {
        uint32_t f = R32(mdl + MDL_RES_ANIM); for (int i = 0; i < nmg; i++) if (mg[i].dst == f) return 0;   /* (merged: the model has them itself) */
        ra_play(ctx, base); return 1; }
    { int fa = frog_anim(ctx, base); if (fa >= 0) return fa; }          /* (a Frog player's wait: F_wait) */
    int n = -1; for (int i = 0; i < 8; i++) if (rc[i].on && rc[i].mdl == mdl) n = i;
    if (n < 0) return 0;
    if (rc[n].hold >= 0) return 1;
    /* (NSMB2 with the leaf: its T_ running animations for the game's run (2) and dashes (3, 4);
       at P-speed, T_b_dash2 - the P-run) */
    int run = id == 2 || id == 3 || id == 4;
    int k = !run ? -1 : pm_pspeed(n) ? RA_PRUN : id == 2 ? RA_RUN : RA_B_DASH;
    if (k < 0) return 0;
    ctx->r[4] = ra_id0 + (uint32_t)k;
    { uint32_t f = R32(mdl + MDL_RES_ANIM); for (int i = 0; i < nmg; i++) if (mg[i].dst == f) return 0; }   /* (merged: the game plays ours as its own) */
    ra_play(ctx, base); return 1;
}
/* -- the 3D tail: NSMB2's (model mr_tail: 65 vertices skinned to a 5-bone chain; its T_tail_*
   animations), tables from tools/nsmb2_anims.py. Each frame: the animation evaluated (Hermite
   keys), the bones posed, the mesh skinned, then put on the hips (joint 1 "skl_root": the
   tail's root space is that joint's, as in NSMB2) and lit simply; drawn with its own texture
   (the stripes come from the texture repeating along it) -- */
typedef struct { int16_t n; int16_t first; float c; } tail_chan_t;
extern const int smb3_tail_ok, smb3_tail_nbones, smb3_tail_nanims, smb3_tail_nverts[2], smb3_tail_nidx[2];   /* (Mario's raccoon tail, Luigi's fox tail) */
extern const int8_t smb3_tail_parent[]; extern const float smb3_tail_rest[][6]; extern const float smb3_tail_vtx[][8];
extern const uint8_t smb3_tail_vbone[][2]; extern const float smb3_tail_vweight[][2]; extern const uint8_t smb3_tail_idx[];
extern const uint8_t smb3_tail_tex[2][16][16][3]; extern const float smb3_tail_keys[][3];
extern const tail_chan_t smb3_tail_chan[][5][9];
/* the ears: NSMB2's Raccoon body's (Mario's, Luigi's), rigid on the head joint, in its space */
extern const int smb3_ears_nverts[2], smb3_ears_nidx[2]; extern const float smb3_ears_vtx[][6];
extern const uint8_t smb3_ears_rgb[][3]; extern const uint16_t smb3_ears_idx[];
static int ears_have(int c) { return (c == 0 || c == 1) && smb3_ears_nverts[c] > 0; } extern const float smb3_tail_frames[]; extern const uint8_t smb3_tail_loop[];
enum { TA_WAIT, TA_WAIT1, TA_B_DASH, TA_FALL, TA_FLY_A, TA_FLY_B, TA_ATTACK_L, TA_ATTACK_R, TA_SLIP, TA_ROLL_JUMP, TA_FIREJMP };
static int tail_ready;
static int tail_variant(int n) { return rc[n].colour == 1 && smb3_tail_nverts[1] > 0; }   /* (Luigi: the fox's) */
typedef float m34[12];
static void m_mul(m34 o, const m34 a, const m34 b) {
    m34 r;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) r[i * 4 + j] = a[i * 4] * b[j] + a[i * 4 + 1] * b[4 + j] + a[i * 4 + 2] * b[8 + j];
        r[i * 4 + 3] += a[i * 4 + 3];
    }
    memcpy(o, r, sizeof r);
}
static void m_tr(m34 o, const float t[3], const float r[3]) {      /* translate * Rz * Ry * Rx (X first) */
    float cx = cosf(r[0]), sx = sinf(r[0]), cy = cosf(r[1]), sy = sinf(r[1]), cz = cosf(r[2]), sz = sinf(r[2]);
    o[0] = cy * cz; o[1] = sx * sy * cz - cx * sz; o[2] = cx * sy * cz + sx * sz; o[3] = t[0];
    o[4] = cy * sz; o[5] = sx * sy * sz + cx * cz; o[6] = cx * sy * sz - sx * cz; o[7] = t[1];
    o[8] = -sy;     o[9] = sx * cy;                o[10] = cx * cy;               o[11] = t[2];
}
static void m_inv(m34 o, const m34 m) {                            /* (affine) */
    float a = m[0], b = m[1], c = m[2], d = m[4], e = m[5], f = m[6], g = m[8], h = m[9], i = m[10];
    float A = e * i - f * h, B = -(d * i - f * g), C = d * h - e * g, det = a * A + b * B + c * C, k = det ? 1.0f / det : 0;
    m34 r = {A * k, -(b * i - c * h) * k, (b * f - c * e) * k, 0, B * k, (a * i - c * g) * k, -(a * f - c * d) * k, 0, C * k, -(a * h - b * g) * k, (a * e - b * d) * k, 0};
    for (int x = 0; x < 3; x++) r[x * 4 + 3] = -(r[x * 4] * m[3] + r[x * 4 + 1] * m[7] + r[x * 4 + 2] * m[11]);
    memcpy(o, r, sizeof r);
}
static m34 tail_invbind[5];
static float tail_chan(int a, int b, int c, float t) {
    const tail_chan_t *ch = &smb3_tail_chan[a][b][c];
    if (ch->n < 0) return smb3_tail_rest[b][c < 6 ? c - 3 + 3 : c - 6];   /* (rest: rotation c 3-5 -> [3..5], translation c 6-8 -> [0..2]) */
    if (ch->n == 0) return ch->c;
    const float (*k)[3] = &smb3_tail_keys[ch->first];
    if (t <= k[0][0]) return k[0][1];
    for (int i = 0; i + 1 < ch->n; i++) {
        float f0 = k[i][0], f1 = k[i + 1][0];
        if (t > f1 || f1 <= f0) continue;
        float d = f1 - f0, s1 = (t - f0) / d, s2 = s1 * s1, s3 = s2 * s1;
        return k[i][1] * (2 * s3 - 3 * s2 + 1) + k[i + 1][1] * (-2 * s3 + 3 * s2) + (s3 - 2 * s2 + s1) * k[i][2] * d + (s3 - s2) * k[i + 1][2] * d;
    }
    return k[ch->n - 1][1];
}
static void tail_pose(int a, float t, m34 world[5]) {
    for (int b = 0; b < smb3_tail_nbones && b < 5; b++) {
        float tr[3], ro[3];
        for (int c = 0; c < 3; c++) {
            ro[c] = a >= 0 ? tail_chan(a, b, 3 + c, t) : smb3_tail_rest[b][3 + c];
            tr[c] = a >= 0 ? tail_chan(a, b, 6 + c, t) : smb3_tail_rest[b][c];
        }
        m34 l; m_tr(l, tr, ro);
        if (smb3_tail_parent[b] >= 0) m_mul(world[b], world[smb3_tail_parent[b]], l); else memcpy(world[b], l, sizeof(m34));
    }
}
static void tail_init(void) {
    if (tail_ready) return;
    tail_ready = -1;
    if (!smb3_tail_ok || smb3_tail_nbones != 5 || smb3_tail_nverts[0] > 65 || smb3_tail_nverts[1] > 130) return;
    m34 bind[5]; tail_pose(-1, 0, bind);
    for (int b = 0; b < 5; b++) m_inv(tail_invbind[b], bind[b]);
    for (int t = 0; t < 2; t++) for (int y = 0; y < 16; y++) for (int x = 0; x < 16; x++) {   /* RGB5A3 (opaque 555), 4 x 4 tiles */
        const uint8_t *c = smb3_tail_tex[t][y][x];
        uint16_t v = (uint16_t)(0x8000 | ((c[0] >> 3) << 10) | ((c[1] >> 3) << 5) | (c[2] >> 3));
        uint32_t o = SM_TAILTEX + 0x200u * (uint32_t)t + (uint32_t)((((y >> 2) * 4 + (x >> 2)) * 16 + (y & 3) * 4 + (x & 3)) * 2);
        W16(o, v);
    }
    tail_ready = 1;
}
/* the tail's animation for what the player does; then the mesh, posed and placed */
static void tail_update(int n, uint32_t pl) {
    if (tail_ready <= 0) return;
    int a = TA_WAIT;
    if (rc[n].hold == RA_ATTACK_L) a = TA_ATTACK_L; else if (rc[n].hold == RA_ATTACK_R) a = TA_ATTACK_R;
    else if (rc[n].hold == RA_FALL) a = TA_FALL;
    else if (rc[n].hold >= RA_FLY && rc[n].hold <= RA_FLY_ST_C) a = TA_FLY_A;
    else {
        float vx = RF(pl + PL_SPEED), vy = RF(pl + PL_SPEED + 4); int ground = (R32(pl + PL_BG_CROSS1) & 1) != 0;
        if (!ground) a = vy < 0 ? TA_FALL : TA_WAIT1;
        else if (pm_pspeed(n)) a = TA_B_DASH;
    }
    if (a != rc[n].tanim) { rc[n].tanim = a; rc[n].tframe = 0; }
    else {
        rc[n].tframe += 1.0f;
        float fr = smb3_tail_frames[a];
        if (rc[n].tframe > fr) rc[n].tframe = smb3_tail_loop[a] && fr > 0 ? fmodf(rc[n].tframe, fr) : fr;
    }
    m34 w[5], sk[5]; tail_pose(a, rc[n].tframe, w);
    for (int b = 0; b < 5; b++) m_mul(sk[b], w[b], tail_invbind[b]);
    const float L[3] = {-0.35f, 0.55f, 0.76f};                         /* (the light: from the upper left, in front) */
    int tv = tail_variant(n), v0 = tv ? smb3_tail_nverts[0] : 0;
    for (int v = 0; v < smb3_tail_nverts[tv]; v++) {
        float p[3] = {0, 0, 0}, nn[3] = {0, 0, 0};
        for (int k = 0; k < 2; k++) {
            float wt = smb3_tail_vweight[v0 + v][k]; if (wt <= 0) continue;
            const float *m = sk[smb3_tail_vbone[v0 + v][k]], *x = smb3_tail_vtx[v0 + v];
            for (int i = 0; i < 3; i++) {
                p[i] += wt * (m[i * 4] * x[0] + m[i * 4 + 1] * x[1] + m[i * 4 + 2] * x[2] + m[i * 4 + 3]);
                nn[i] += wt * (m[i * 4] * x[3] + m[i * 4 + 1] * x[4] + m[i * 4 + 2] * x[5]);
            }
        }
        const float *h = rc[n].hips; float q[3], qn[3];
        for (int i = 0; i < 3; i++) {
            q[i] = h[i * 4] * p[0] + h[i * 4 + 1] * p[1] + h[i * 4 + 2] * p[2] + h[i * 4 + 3];
            qn[i] = h[i * 4] * nn[0] + h[i * 4 + 1] * nn[1] + h[i * 4 + 2] * nn[2];
        }
        float len = sqrtf(qn[0] * qn[0] + qn[1] * qn[1] + qn[2] * qn[2]); if (len > 0) for (int i = 0; i < 3; i++) qn[i] /= len;
        float d = qn[0] * L[0] + qn[1] * L[1] + qn[2] * L[2]; if (d < 0) d = 0;
        float lit = 0.55f + 0.6f * d; if (lit > 1) lit = 1;
        memcpy(rc[n].tv[v], q, sizeof q); rc[n].tl[v] = (uint8_t)(lit * 255);
    }
}
/* -- the P-meter, flight, flutter and the tail attack: SMB3's (prg008: Player_PowerUpdate,
   Player_JumpFlyFlutter, Player_TailAttackAnim, Player_TailAttack_HitBlocks) on NSMBW's players.
   SMB3's velocities are 1/16 pixel a frame, down positive; NSMBW's are units (= pixels) a frame,
   up positive, its gravity applied before the move: what we set is the speed it ends up moving at -- */
#define PL_SPEED_F       268                    /* float mSpeedF */
#define PL_MAX_SPEED_F   272
#define PL_ACCEL_Y       276
#define PL_DIRECTION     840                    /* u8 mDirection: 0 right, 1 left */
#define PL_KEY           3748                   /* dAcPyKey_c mKey */
#define A_KEY_DASH       0x8005E5D0u            /* dAcPyKey_c: the run button held (by controller style) */
#define A_KEY_JUMP       0x8005E740u            /* dAcPyKey_c::buttonJump */
#define PLAYER_FLY_YVEL     (-0x18)
#define PLAYER_TAILWAG_YVEL 0x10
#define TOPRUNSPEED_PX      2.5f                 /* (PLAYER_TOPRUNSPEED $28: SMB3's run, in pixels a frame) */
#define PL_SPEED_DATA       4192                 /* const sSpeedData *mSpeedDataNormal: 30 floats, [2] the dash's top speed */
#define SM_SPEEDP           (SM_MEM + 0x0C40)    /* the P-speed tables: 8 x 120 bytes */
#define PSPEED_MULT         (4.0f / 3.0f)        /* (the leaf's top speed: NSMBW's dash 3.0 -> 4.0, as SMB3's run -> power step $28 -> $38 is ~1.4x) */
#define PSPEED_RAMP          180                  /* (user, 2026-11-22: about 3 s from a standstill to the top) */
#define PSPEED_NATIVE        80                   /* (NSMBW's own climb to its dash top, measured: the rest of the 3 s is the climb above it) */
#define PSPEED_MARGIN        0.05f                /* (P-speed: faster than NSMBW's own top by this) */
static void vy_set(uint32_t pl, float smb3_vel) {             /* (SMB3 Y velocity -> the NSMBW speed that moves so, gravity included) */
    W32(pl + PL_SPEED + 4, fbits(-smb3_vel / 16.0f - RF(pl + PL_ACCEL_Y)));
}
static void raccoon_set(int n, int on);
/* (the Raccoon is the player's power-up value, PU_RACCOON - rc[].on follows it each frame) */
static void raccoon_set(int n, int on) { if (n >= 0 && n < 8 && rc[n].on != on) { rc[n].on = on; rc[n].hold = -1; rt_log("smb3", "player %d: Raccoon %s", n + 1, on ? "on" : "off"); } }
static ppc_context *blk_ctx; static uint8_t *blk_base;
/* Player_SuitLost: a suit put on (ObjHit_SuperLeaf, ObjHit_Obj1A) or lost to a hit (Player_GetHurt
   from a super suit) - $17 frames of the "poof": the Player hidden behind two smoke sprites
   (Player_SuitLost_DoPoof: $47 $45 $43 $41 by the counter's bits 2-3, at the Player's sprite Y + 8,
   the first turned both ways at X + 8, PAL1) while the game halts (Player_HaltGame: the Player
   and every object stopped). Here: NSMBW's actor stop (dActor_c::mExecStopReq, as its own
   power-up changes use) and the player's invisible status (187) for the time; the new suit is
   in place at once, as Player_QueueSuit has it the next frame. */
#define EXEC_STOP_REQ   0x80429CF8u              /* u8 dActor_c::mExecStopReq */
/* dAcPy_c's fn_801416C0 (mNextMode = p; setPowerup(p, 0) - no change demo; gm_d_player.c
   py_fn_801416c0): not a function start in the recompiled game (it's inside fn_80141640 there), so a
   call to it was fatal - done here (2026-11-26: the crash taking the Frog suit small, or the leaf
   with Fire) */
static void set_powerup_now(ppc_context *ctx, uint8_t *base, uint32_t pl, uint32_t p) {
    W32(pl + 5344, p);
    gcall(ctx, base, R32(R32(pl + 96) + 228), 3, pl, p, 0);
}
static struct { int t, shown, on[8], req[8]; uint32_t pl[8]; } poof;
/* -- an NSMBW character's suit change (CHARACTERS_AND_GAMES.md: the leaf is picked up like any
   NSMBW power-up). dAcPy_c::initChangeNormal / executeChangeNormal: 30 frames with the player and
   every actor stopped, the old and new forms taking turns every 6 frames
   (change_reverse_scale_set: step = 6 - timer / 6), the change sound; afterwards
   mPowerupChangeInvulnTimer 8 (a gain) - or, a suit lost to a hit, mDamageInvulnTimer 127 -- */
#define CHG_FRAMES      30
#define PL_DAMAGE_INVULN_T 4212
#define PL_CHANGE_INVULN_T 4216
#define A_PLAYER_SOUND  0x80057E70u              /* daPlBase_c::startPlayerVoice-ish: PlayPlayerSound(pl, id, 0) */
#define SE_PLY_CHANGE_UP   274                   /* (initChangeNormal: the power-up sound for Super / Fire / Ice) */
#define SE_PLY_CHANGE_DOWN 275                   /* (and for a hit's power-down) */
static struct { int t[8], to[8], req[8]; uint32_t pl[8]; } chg;
static int chg_any(void) { for (int i = 0; i < 8; i++) if (chg.t[i]) return 1; return 0; }
static int chg_new_shown(int i) { return ((CHG_FRAMES - chg.t[i]) / 6) & 1; }
#define RC_SHOWN(i) (rc[i].have && !poof.on[i] && (rc[i].mdl && rt_pu_mdl_get(rc[i].mdl) != 0xFFFFFFFFu ? rt_pu_mdl_get(rc[i].mdl) == PU_RACCOON : rc[i].on))   /* (the Raccoon's parts: not behind the poof; with the model's power-up - NSMBW's change shows the old and new by turns)   /* (the Raccoon's parts: not behind the poof; by turns in a change) */
static void poof_start(int n, uint32_t pl) {
    if (n < 0 || n > 7) return;
    if (!poof.t) W8(EXEC_STOP_REQ, (uint8_t)(R8(EXEC_STOP_REQ) | 0x0F));
    poof.t = 0x17; poof.on[n] = 1; poof.pl[n] = pl;                    /* (the player's model not drawn meanwhile: smb3_stage_player_hidden) */
    rt_log("smb3", "player %d: poof (the suit changes, the game halts $17 frames)", n + 1);
}
static void chg_start(int n, uint32_t pl, int to) {
    if (n < 0 || n > 7) return;
    if (!chg_any() && !poof.t) W8(EXEC_STOP_REQ, (uint8_t)(R8(EXEC_STOP_REQ) | 0x0F));
    chg.t[n] = CHG_FRAMES; chg.to[n] = to; chg.pl[n] = pl;
    gcall(blk_ctx, blk_base, A_PLAYER_SOUND, 3, pl, to ? SE_PLY_CHANGE_UP : SE_PLY_CHANGE_DOWN, 0);
    rt_log("smb3", "player %d: NSMBW change - Raccoon %s (%d frames)", n + 1, to ? "on" : "off", CHG_FRAMES);
}
static void chg_frame(void) {
    if (!chg_any()) return;
    for (int n = 0; n < 8; n++) if (chg.t[n] && !--chg.t[n]) {
        if (chg.to[n]) W32(chg.pl[n] + PL_CHANGE_INVULN_T, 8); else W32(chg.pl[n] + PL_DAMAGE_INVULN_T, 127);
        rt_log("smb3", "player %d: NSMBW change done", n + 1);
    }
    if (!chg_any() && !poof.t) W8(EXEC_STOP_REQ, (uint8_t)(R8(EXEC_STOP_REQ) & 0xF0));
}
static void poof_frame(void) {                   /* (once a frame, from the stage's draw: it runs while everything's stopped) */
    chg_frame();
    for (int n = 0; n < 8; n++) if (poof.req[n] && poof.pl[n]) { poof.req[n] = 0; poof_start(n, poof.pl[n]); }   /* (asked for from setNextPowerup) */
    poof.shown = poof.t;
    if (!poof.t) return;
    if (--poof.t) return;
    if (!chg_any()) W8(EXEC_STOP_REQ, (uint8_t)(R8(EXEC_STOP_REQ) & 0xF0));
    for (int n = 0; n < 8; n++) poof.on[n] = 0;
}
static void give_life(int n) { if (n >= 0 && n < 8) W32(MOD_PY_REST + 4 * (uint32_t)n, R32(MOD_PY_REST + 4 * (uint32_t)n) + 1); }
/* -- SMB3's sound effects (CHARACTERS_AND_GAMES.md rule 5: the level's coins, blocks, items and
   enemies sound as SMB3's): set in its queues where SMB3 sets them - Sound_QPlayer / QLevel1 /
   QLevel2 - and SMB3's engine rules (smb3_stage_music.inc snd_step) play them from GROUP_SMB3.
   What the NSMBW characters do themselves (a jump, a power-up's change) keeps NSMBW's sound -- */
enum { SFXP_BUMP = 0x02, SFXP_SQUISH = 0x04, SFXP_KICK = 0x08,                       /* (Sound_QPlayer: SND_PLAYERBUMP, _SWIM - the stomp's squish -, _KICK) */
       SFX1_COIN = 0x01, SFX1_RISE = 0x02, SFX1_BABOOM = 0x08, SFX1_BLIP = 0x10, SFX1_POWER = 0x20, SFX1_1UP = 0x40, SFX1_POOF = 0x80,   /* (Sound_QLevel1) */
       SFX2_CRUMBLE = 0x01 };                                                         /* (Sound_QLevel2) */
static void sfx_q(uint16_t q, uint8_t v) { nes_ram_ptr()[q] |= v; }
static void sfx_player(uint8_t v) { sfx_q(SMB3_Sound_QPlayer, v); }
static void sfx_level1(uint8_t v) { sfx_q(SMB3_Sound_QLevel1, v); }
static void sfx_level2(uint8_t v) { sfx_q(SMB3_Sound_QLevel2, v); }
static float hit_x;                              /* (the player who hit a block) */

/* -- the bounce (ObjNorm_BounceDU): 10 frames, Y velocity from Bouncer_PUpVel by position,
   negated (hit from below), applied the frame after; then the tile behind it goes in -- */
static const int8_t BOUNCER_VEL[11] = {0x00, -0x40, -0x40, -0x30, -0x20, -0x10, 0x00, 0x10, 0x20, 0x30, 0x40};
#define NBUMP 2
static struct { int on, tx, ty, pos, y16, vy, down, pounded; uint8_t shown, after; int item; } bumps[NBUMP];   /* (down: hit from above - Player_BounceDir 0) */
/* -- the coin out of a block (CoinPUp_UpdateAndDraw): Y velocity -5 whole pixels, +1 every 4th
   frame, gone when it reaches 5; patterns $49 $4F $4D $4F (8 x 16, palette 3, the 2nd mirrored) -- */
#define NPOP 4
static struct { int on, x, y, vy, counter, who; } pops[NPOP];
/* -- score pop-ups (Score_PopUp, Scores_GiveAndDraw): 5 slots; counter $30 down; at $2A the points
   go in (1-up: a life); rising 1 pixel a frame, then every 2nd, then every 4th (Score_RiseCounterMask) -- */
#define NSCORE 5
static struct { int value, x, y, counter, who; } scores[NSCORE];
static const uint8_t SCORE_PAT_L[13] = {0xFF, 0xFF, 0xFF, 0xFF, 0x5B, 0x63, 0x6B, 0x6D, 0x5B, 0x63, 0x6B, 0x6D, 0x61};
static const uint8_t SCORE_PAT_R[13] = {0x5B, 0x63, 0x6B, 0x6D, 0x69, 0x69, 0x69, 0x69, 0x59, 0x59, 0x59, 0x59, 0x6F};
static const uint16_t SCORE_ADD[13] = {1, 2, 4, 8, 10, 20, 40, 80, 100, 200, 400, 800, 0};   /* (in tens) */
static void score_pop(int value, int x, int y, int who) {      /* (Score_FindFreeSlot: 4 down to 0, else 4) */
    int i = NSCORE - 1; while (i >= 0 && scores[i].value) i--; if (i < 0) i = NSCORE - 1;
    scores[i].value = value; scores[i].x = x; scores[i].y = y; scores[i].counter = 0x30; scores[i].who = who;
}
/* -- brick debris (BrickBusts_DrawAndUpdate, bust type 2): two slots; four 8 x 16 chunks of $4B; Y
   velocity -6, +1 every 4th frame; the lower pair 2 more a frame; the pairs part 1 pixel a frame;
   the flips turn with the frame counter -- */
#define NBUST 2
static struct { int on, x, yu, yl, yvel, xdist, hen; } busts[NBUST];
static void bust_start(int tx, int ty) {
    busts[1] = busts[0];                                                 /* (BrickBust_MoveOver) */
    busts[0].on = 1; busts[0].yu = ty * 16 - 1; busts[0].yl = busts[0].yu + 8; busts[0].x = tx * 16;
    busts[0].xdist = 0; busts[0].hen = 0; busts[0].yvel = -6;
}
/* -- the 10-coin brick (LATP_10Coin / LATP_Coin): 200 frames and 10 more coins while it lasts -- */
static struct { int id, count, timer; } b10;
/* -- items (ObjInit_/ObjNorm_ PUpMush, PUp1UpMush, StarOrSuit, FireFlower, SuperLeaf) -- */
#define NITEM 1                                  /* (SMB3: the power-up is always object slot 5) */
typedef struct { int on, kind, x16, y16, xvel, yvel, xfrac, yfrac, timer, timer2, var1, var2, det, flip, block_y, down, pounded; } item_t;
static item_t items[NITEM];
static int mush_fall;                            /* Player_MushFall: 0 left, 1 right */

static int tile_of(float x, float y_up, int *tx, int *ty) {
    *tx = (int)floorf((x - L.lx) / 16.0f); *ty = (int)floorf((-y_up - L.ly) / 16.0f);
    return *tx >= 0 && *tx < L.w && *ty >= 0 && *ty < LH;
}
static int tclass_at(int px, int py) {           /* (level pixels) the solidity of the tile there */
    int tx = px >> 4, ty = py >> 4;
    if (tx < 0 || tx >= L.w || ty < 0 || ty >= LH) return 0;
    return tile_class(L.tile[ty * L.w + tx]);
}
static void coin_get(int who) {                   /* (Coins_Earned; 100: a life, as the status bar does) */
    sfx_level1(SFX1_COIN);                       /* (PRG008_B604 a coin touched, PRG000_C4A7 one out of a block) */
    SG.coins++; if (SG.coins >= 100) { SG.coins -= 100; give_life(who); sfx_level1(SFX1_1UP); rt_log("smb3", "100 coins: 1-up for player %d", who + 1); }
}
static void pop_coin(int tx, int ty) {           /* LATP_CoinCommon -> PRG000_C49B: 4 slots, else the last */
    coin_get(hit_who);
    int i = 0; while (i < NPOP && pops[i].on) i++; if (i == NPOP) i = NPOP - 1;
    pops[i].on = 1; pops[i].x = (tx * 16) | 4; pops[i].y = ty * 16 - 24; pops[i].vy = -5; pops[i].counter = 0; pops[i].who = hit_who;
}
static void item_spawn(int kind, int tx, int ty, int down, int pounded) {
    for (int i = 0; i < NITEM; i++) {                                    /* (Level_PrepareNewObject on slot 5: replaces it) */
        item_t *it = &items[i]; memset(it, 0, sizeof *it);
        /* (ObjNorm_BounceDU at position 10: hit from below - 1 pixel above the block; from above - 8 below its top) */
        it->on = 1; it->kind = kind; it->x16 = tx * 16 * 16; it->y16 = (ty * 16 + (down ? 8 : -1)) * 16; it->block_y = ty * 16;
        it->timer2 = 0x10;                                               /* (no collecting for 16 frames) */
        it->down = down; it->pounded = pounded;
        mush_fall = (tx * 16 + 8) >= (hit_x - L.lx) ? 1 : 0;             /* (Mushroom_SetFall: away from the player) */
        if (kind == SPR_LEAF) {                                          /* ObjInit_SuperLeaf: Leaf_YVels / Leaf_TimerVals by Player_BounceDir */
            it->y16 = (ty * 16 + (down ? 0x0C : -0x0D)) * 16;
            it->timer = down ? 0x08 : 0xFF; it->yvel = down ? 0x04 : (int8_t)0xE0;
        } else if (down) {                                               /* (knocked out downward: Y velocity $10, no rise) */
            it->yvel = 0x10;
            if (kind == SPR_STAR || kind == SPR_FROG) it->xvel = mush_fall ? 0x10 : -0x10;
        } else {
            it->timer = 0x3D;                                            /* (out of the box: PowerUp_DoRaise) */
            if (kind == SPR_STAR || kind == SPR_FROG) { it->xvel = mush_fall ? 0x10 : -0x10; it->yvel = -0x38; }   /* (ObjInit_StarOrSuit: up, PowerUp_BounceXVel) */
        }
        rt_log("smb3", "item %d out of the block at %d,%d%s", kind, tx, ty, down ? " (downward)" : "");
        return;
    }
}
/* ---- the P-Switch (TILEA_PSWITCH $F2, a tile): stood on (the feet, not the head - prg008
   PRG008_B623) it's pressed (CHNGTILE_PSWITCHSTOMP: $D7) and Level_PSwitchCnt $80 - one off every 4
   frames; while it runs PSwitch_SubstTileAndAttr makes coins bricks, bricks coins (and munchers,
   the hidden P-Switch coins $05, coins). SMB3 swaps them as it reads them; here they're swapped in
   the level and back at the end - those still as swapped (a coin taken, a brick broken: gone) ---- */
enum { T_PSWITCH = 0xF2, T_PSWITCH_PRESSED = 0xD7, T_MUNCHER = 0x66, T_PSWITCHCOIN = 0x05 };
static struct { int cnt; int n; struct { uint16_t at; uint8_t was, now; } sw[512]; } PS;
static void pswitch_swap(int on) {
    if (on) {
        PS.n = 0;
        for (int i = 0; i < L.w * LH && PS.n < 512; i++) {
            uint8_t t = L.tile[i], to = t == T_COIN ? T_BRICK : t == T_BRICK ? T_COIN : (t == T_MUNCHER || t == T_PSWITCHCOIN) ? T_COIN : 0;
            if (!to) continue;
            PS.sw[PS.n].at = (uint16_t)i; PS.sw[PS.n].was = t; PS.sw[PS.n].now = to; PS.n++; L.tile[i] = to;
        }
        rt_log("smb3", "P-switch: on (%d tiles swapped)", PS.n);
    } else {
        int back = 0;
        for (int k = 0; k < PS.n; k++) if (L.tile[PS.sw[k].at] == PS.sw[k].now) { L.tile[PS.sw[k].at] = PS.sw[k].was; back++; }
        rt_log("smb3", "P-switch: off (%d tiles back)", back); PS.n = 0;
    }
}
static void pswitch_frame(void) {                /* (Player_Update: Level_PSwitchCnt) */
    if (!PS.cnt) return;
    if (PS.cnt == 1 || !(tick & 3)) { if (--PS.cnt == 0) pswitch_swap(0); }
}
static int pswitch_left(void) { return PS.cnt; }
static void pswitch_resume(int cnt) {           /* (the other area of a pipe: the switch still running) */
    pswitch_swap(1); PS.cnt = cnt;
    rt_log("smb3", "P-switch: still on in the other area (%d left)", cnt);
}
static void pswitch_stomp(int tx, int ty) {
    L.tile[ty * L.w + tx] = T_PSWITCH_PRESSED;
    sfx_level1(SFX1_BABOOM);                     /* (PRG008_B623: the "Wham!") */
    if (!PS.cnt) pswitch_swap(1);
    PS.cnt = 0x80;
}
static int is_block(uint8_t v) { return v >= T_QFLOWER && v <= T_BPSWITCH; }   /* (Level_ActionTiles: TILEA_QBLOCKFLOWER + 17; up only) */
/* note blocks (Level_ActionTiles: TILEA_NOTE $2E - flower $2F, leaf $30, star $31 -, TILEA_HNOTE $71
   (coin heaven's), TILEA_GNOTE $BC; hit from above or below: Level_ActionTiles_HitEnable %0011) */
static int is_note(uint8_t v) { return (v >= 0x2E && v <= 0x31) || v == 0x71 || v == 0xBC; }
static uint8_t note_after(uint8_t v) { return v == 0x71 ? 0x71 : v == 0xBC ? 0xBC : 0x2E; }   /* (Bounce_TileReplacements: CHNGTILE_TONOTEBLOCK / _COINHEAVEN / _TOGNOTEBLOCK) */
static int note_item(uint8_t v, int big);
static void obj_block_bumped(int tx, int ty);
static int bump_self;                            /* (smb3_stage_enemies.inc: the object whose hit bumped a block, -1 a player) */
static void bump_start(int tx, int ty, uint8_t shown, uint8_t after, int item, int down) {
    sfx_player(SFXP_BUMP);                       /* (PRG008_B722: a block that bounces - Player_Bounce) */
    if (!down) obj_block_bumped(tx, ty);   /* (Object_HandleBumpUnderneath: what stands on it - not the shell that bumped it: bump_self) */
    for (int i = 0; i < NBUMP; i++) if (!bumps[i].on) {                  /* (block bump slots: objects 6 and 7) */
        bumps[i].on = 1; bumps[i].tx = tx; bumps[i].ty = ty; bumps[i].pos = 10; bumps[i].y16 = 0; bumps[i].vy = 0;
        bumps[i].shown = shown; bumps[i].after = after; bumps[i].item = item; bumps[i].down = down; bumps[i].pounded = 0;
        L.tile[ty * L.w + tx] = T_BUMPCLEAR;                             /* (TILEA_BLOCKBUMP_CLEAR: solid, unseen; the sprite shows it) */
        return;
    }
    L.tile[ty * L.w + tx] = after;                                       /* (no slot: as it ends) */
}
/* Level_DoBumpBlocks + LATP_HandleSpecialBounceTiles: what the block gives (LATP_QBlocks) and
   what it leaves (LATR_QBlocks: $20 the used block, $30 a brick, $60 a brick with a coin) */
static const uint8_t LATP_Q[17] = {1, 2, 3, 4, 5, 4, 0, 6, 1, 2, 3, 4, 5, 8, 9, 7, 0x0A};
static const uint8_t LATR_Q[17] = {0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60, 0x20, 0x20, 0x20};
static int b10_id(int tx) { return ((tx & 15) << 4 | ((tx >> 4) & 0xFF)) & 0xFF; }   /* (Temp_Var16 | Temp_Var15) */
static int hit_pound;                            /* (this hit is a ground pound from above: the block and its item go up as from below) */
static void hit_block(int tx, int ty, int big, int star, int down) {
    uint8_t v = L.tile[ty * L.w + tx];
    if (is_note(v)) {                                                    /* (LATP_Notes: none, flower, leaf, star; LATR $40 - a note block again) */
        int k = 0; while (k < NBUMP && bumps[k].on) k++;
        if (k == NBUMP) return;
        bump_start(tx, ty, v == 0xBC ? 0xBC : v == 0x71 ? 0x71 : 0x2E, note_after(v), note_item(v, big), down);
        return;
    }
    if (!is_block(v)) return;
    int k = 0; while (k < NBUMP && bumps[k].on) k++;
    if (k == NBUMP) return;                                              /* (no bump slot: nothing happens) */
    if (items[0].on && items[0].timer && (items[0].x16 >> 8) == tx) return;   /* (its power-up still rising) */
    int p = LATP_Q[v - T_QFLOWER], r = LATR_Q[v - T_QFLOWER], item = -1;
    switch (p) {
    case 1: item = big ? SPR_FLOWER : SPR_MUSHROOM; break;               /* LATP_Flower */
    case 2: item = big ? SPR_LEAF : SPR_MUSHROOM; break;                 /* LATP_Leaf */
    case 3: item = SPR_STAR; break;                                      /* LATP_Star */
    case 5: if (star) { item = SPR_STAR; break; }                        /* LATP_CoinStar: invincible - a star, else a coin */
        /* fall through */
    case 8: case 4:
        if (p == 8) { b10.id = b10_id(tx); b10.count = 9; b10.timer = 200; }   /* LATP_10Coin */
        pop_coin(tx, ty);                                                /* LATP_Coin */
        if (b10_id(tx) == b10.id && b10.timer && b10.count >= 0) { b10.count--; r = 0x60; }
        break;
    case 6:                                                              /* LATP_Brick */
        if (ty > 0 && L.tile[(ty - 1) * L.w + tx] == T_COIN) { L.tile[(ty - 1) * L.w + tx] = T_SKY; pop_coin(tx, ty); }   /* (LATP_GetCoinAboveBlock) */
        if (big || bump_self >= 0) { L.tile[ty * L.w + tx] = T_SKY; bust_start(tx, ty); sfx_level2(SFX2_CRUMBLE); SG.score += 1; return; }   /* (10 points; a kicked shell - Object_BumpOffBlocks, tile check index 4 - always busts it) */
        break;
    case 7: rt_log("smb3", "vine block (not yet)"); break;
    case 9: item = SPR_1UP; break;                                       /* LATP_1up */
    case 0x0A:                                                           /* LATP_PSwitch: CHNGTILE_PSWITCHAPPEAR - the switch on top of it */
        if (ty > 0) { L.tile[(ty - 1) * L.w + tx] = T_PSWITCH; rt_log("smb3", "P-switch out at %d,%d", tx, ty - 1); }
        break;
    }
    if (frog_block_take(tx, ty)) item = SPR_FROG;                       /* (the Frog suit's block: a star block that gives the suit) */
    if (hit_pound && item == SPR_LEAF) down = 0;                        /* (user: a pounded leaf alone comes out of the top) */
    bump_start(tx, ty, r == 0x20 ? T_USED : T_BRICK, r == 0x20 ? T_USED : r == 0x30 ? T_BRICK : T_BCOIN, item, down);
    for (int i = 0; i < NBUMP; i++) if (bumps[i].on && bumps[i].tx == tx && bumps[i].ty == ty) bumps[i].pounded = hit_pound;
}
/* Object_Move + Object_InteractWithWorld for a 16 x 16 item: X then Y by the velocities (4.4,
   with the fraction carried), detect (floor 4, ceiling 8, walls 1 / 2), gravity OBJECT_FALL 3 up
   to OBJECT_MAXFALL $40; on the floor: Y to the tile, stop; ceiling: Y velocity 4; wall: turn */
static void obj_move(item_t *it) {
    int fx = it->xfrac + it->xvel; it->x16 += fx >> 4 << 4; it->xfrac = fx & 15;   /* (whole pixels move, the fraction stays) */
    int fy = it->yfrac + it->yvel; it->y16 += fy >> 4 << 4; it->yfrac = fy & 15;
    int x = it->x16 >> 4, y = it->y16 >> 4;
    it->det = 0;
    if (it->yvel >= 0 && (tclass_at(x + 4, y + 16) || tclass_at(x + 11, y + 16))) {
        int ty = (y + 16) >> 4, c = tile_class(L.tile[ty * L.w + ((x + 8) >> 4)]);
        if (c == 2 || ((y + 16) & 15) < 8) it->det |= 4;                 /* (solid on top: from above only) */
    }
    if (it->yvel < 0 && tclass_at(x + 8, y) == 2) it->det |= 8;
    if (it->xvel > 0 && tclass_at(x + 15, y + 8) == 2) it->det |= 1;
    if (it->xvel < 0 && tclass_at(x, y + 8) == 2) it->det |= 2;
    it->yvel += 3; if (it->yvel >= 0x40) it->yvel = 0x40;
    if (it->det & 4) { it->y16 = (y & ~15) << 4; it->yvel = 0; it->yfrac = 0; }
    if (it->det & 8) it->yvel = 4;
    if (it->det & 3) it->xvel = -it->xvel;
}
static void items_frame(void) {
    for (int i = 0; i < NITEM; i++) {
        item_t *it = &items[i]; if (!it->on) continue;
        if (it->timer2) it->timer2--;
        if (it->kind == SPR_LEAF) {                                      /* ObjNorm_SuperLeaf */
            if (it->timer) {
                it->timer--;
                it->y16 += it->yvel;                                     /* (Object_ApplyYVel_NoLimit) */
                it->yvel++;
                if (it->yvel == 0) it->timer = 0;
            } else {
                static const int8_t osc[2] = {2, -2}, lim[2] = {0x20, -0x20}, yv[3] = {0x0A, -0x0A, 0x08};
                int y = it->var2 & 1;
                it->xvel += osc[y];
                if (it->xvel == lim[y]) it->var2++;
                if (it->xvel < 0) y++;
                it->yvel = yv[y] + 6;
                it->x16 += it->xvel; it->y16 += it->yvel;
            }
            if (it->xvel) it->flip = it->xvel > 0;
        } else {
            /* PowerUp_DoRaise: out of the box - 16 frames still, then 1 pixel up every 3rd frame */
            if (it->timer) {
                it->timer--;
                if (it->timer == 0x2D) sfx_level1(SFX1_RISE);           /* (PowerUp_DoRaise: the rising sound at $2D) */
                if (it->timer < 0x2D) { if (--it->var1 < 0) { it->var1 = 2; it->y16 -= 16; } }
                continue;
            }
            if (it->kind == SPR_MUSHROOM || it->kind == SPR_1UP) {      /* ObjNorm_PUpMush */
                if ((it->det & 4) && it->xvel == 0) it->xvel = mush_fall ? 0x10 : -0x10;   /* (PowerUp_BounceXVel) */
                obj_move(it);
            } else if (it->kind == SPR_STAR || it->kind == SPR_FROG) {   /* ObjNorm_StarOrSuit */
                obj_move(it);
                if (it->det & 4) it->yvel = -0x40;
            } else {                                                     /* ObjNorm_FireFlower */
                obj_move(it);
                if (it->yvel == 0) it->xvel = 0;
            }
        }
        if (getenv("SMB3_STAGE_TRACE")) { extern uint64_t g_frames_presented; rt_log("smb3", "trace item %d f%llu x %d y %d xv %d yv %d t %d det %d", it->kind, (unsigned long long)g_frames_presented, it->x16 >> 4, it->y16 >> 4, it->xvel, it->yvel, it->timer, it->det); }
        if ((it->y16 >> 4) > LH * 16 + 32 || (it->x16 >> 4) < -32 || (it->x16 >> 4) > L.w * 16 + 32) it->on = 0;   /* (Object_DeleteOffScreen) */
    }
}
static void items_touch(ppc_context *ctx, uint8_t *base, uint32_t pl, int n, float px, float py, float h) {
    if (gcall(ctx, base, A_IS_DEMO, 1, pl) || gcall(ctx, base, A_TEST_FLAG, 2, pl, 4) || gcall(ctx, base, A_TEST_FLAG, 2, pl, 53)) return;   /* (dying, in a demo - a pipe, the goal -, out of play, in a balloon: no items - SMB3's power-ups ignore a dying Player) */
    float lx = px - L.lx, lyb = -py - L.ly;                              /* (player's feet, level pixels) */
    for (int i = 0; i < NITEM; i++) {
        item_t *it = &items[i];
        if (!it->on || it->timer2 || (it->kind != SPR_LEAF && it->timer)) continue;   /* (PowerUp_DoHitTest: not while Timer2 / rising) */
        if (it->pounded && it->kind == SPR_LEAF) { if (it->yvel < 0) continue; it->pounded = 0; }   /* (out of a pounded block: not till the top of its rise) */
        int x = it->x16 >> 4, y = it->y16 >> 4;
        if (lx + 6 < x + 2 || lx - 6 > x + 14 || lyb < y + 2 || lyb - h > y + 14) continue;
        int mode = (int)R32(pl + PL_MODE), small = mode == 0 || mode == 3;
        /* (PowerUp_PlaySound: SMB3's power-up sound - unless the character changes, whose own
           change sound it is then: NSMBW's, or SMB3's poof for an NES character's leaf) */
        if ((it->kind == SPR_MUSHROOM && !small) || (it->kind == SPR_FLOWER && !small && mode == PU_FIRE) || (it->kind == SPR_LEAF && !small && mode == PU_RACCOON)) sfx_level1(SFX1_POWER);
        switch (it->kind) {
        case SPR_MUSHROOM:                                               /* ObjHit_PUpMush: small - Super */
            if (small) gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, 1);
            break;
        case SPR_FLOWER:                                                 /* ObjHit_FireFlower: small - as a mushroom; else Fire */
            if (small) gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, 1); else if (mode != PU_FIRE) gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, PU_FIRE);
            break;
        case SPR_LEAF:                                                   /* ObjHit_SuperLeaf */
            if (small) gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, 1);    /* (small, not from a star-flash block: as a mushroom - PRG001_A897) */
            else if (mode == PU_RACCOON) { }                             /* (already Raccoon: the power-up sound only) */
            else if (retro_is_player(pl)) { set_powerup_now(ctx, base, pl, PU_RACCOON); poof_start(n, pl); sfx_level1(SFX1_POOF); }   /* (an NES character: SMB3's poof - Player_SuitLost $17, Player_QueueSuit) */
            else gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, PU_RACCOON);  /* (an NSMBW character: NSMBW's own power-up change, to the Raccoon state) */
            break;
        case SPR_FROG: frog_touch(ctx, base, pl, n, mode); break;       /* ObjHit_StarOrSuit, a suit: the Frog (smb3_stage_frog.inc) */
        case SPR_STAR: {                                                 /* ObjHit_StarOrSuit: Player_StarInv $E0, -1 every 2nd frame */
            uint32_t fn = R32(R32(pl + AC_VTABLE) + VT_SET_STAR);
            if (fn) gcall(ctx, base, fn, 3, pl, 1, 0xE0 * 2);
            rt_log("smb3", "player %d: star (NSMBW star timer %d)", n + 1, (int)R32(pl + 4208));
            break; }
        }
        score_pop(it->kind == SPR_1UP ? 0x0D : 0x09, x, y - 16, n);     /* (ObjHit_PUp1UpMush "1-UP"; PUp_GeneralCollect 1000) */
        rt_log("smb3", "player %d got item %d (mode %d)", n + 1, it->kind, mode);
        it->on = 0;
    }
}
#include "smb3_stage_enemies.inc"
static void sb_frame(void);
static void abilities(ppc_context *ctx, uint8_t *base, uint32_t pl, int n, int big) {
    sb_frame();
    {   int retro_smb3_tail(uint32_t pl);                                /* (rt_retro.c: SMB3 Mario - SMB3's own P-meter, flight and tail on him already) */
        int t = retro_smb3_tail(pl);
        if (t >= 0) {                                                    /* (his tail attack reaches SMB3's objects and blocks as the leaf's does) */
            int left = R8(pl + PL_DIRECTION) != 0;
            if (t == 0x0C || t == 9) obj_tail(n, left);
            if (t == 9) {
                float px = RF(pl + PL_POS), py = RF(pl + PL_POS + 4); int tx, ty;
                if (tile_of(px + (left ? -13.0f : 13.0f), py + 4.0f, &tx, &ty) && is_block(L.tile[ty * L.w + tx])) {
                    hit_who = n; hit_x = px; hit_block(tx, ty, 1, gcall(ctx, base, A_IS_STAR, 1, pl) != 0, 0);
                }
            }
            int retro_smb3_power(uint32_t pl, int *flying); int fl = 0;
            pm[n].power = retro_smb3_power(pl, &fl); pm[n].fly = fl; pm[n].wag = 0; pm[n].tail = t;   /* (the status bar's meter: his Player_Power) */
            return;
        }
    }
    uint32_t key = pl + PL_KEY;
    int ground = (R32(pl + PL_BG_CROSS1) & 1) != 0;
    int dash = gcall(ctx, base, A_KEY_DASH, 1, key) != 0, jump = gcall(ctx, base, A_KEY_JUMP, 1, key) != 0;
    int dash_new = dash && !pm[n].dash_was, jump_new = jump && !pm[n].jump_was;
    pm[n].dash_was = dash; pm[n].jump_was = jump;
    float vx = fabsf(RF(pl + PL_SPEED_F)), vy = RF(pl + PL_SPEED + 4);
    /* (the counters at Event_Countdown: once a frame) */
    if (pm[n].pmcnt) pm[n].pmcnt--;
    if (pm[n].tail) pm[n].tail--;
    if (getenv("SMB3_STAGE_TRACE")) rt_log("smb3", "trace pm%d anim %d f%d power %02X rc %d pcap %.2f fly %02X wag %d tail %d vx %.2f max %.2f vy %.2f ground %d dash %d jump %d hold %d", n + 1, rc[n].mdl ? (int)R32(rc[n].mdl + 340) : -1, tick, pm[n].power, rc[n].on, pm[n].pcap, pm[n].fly, pm[n].wag, pm[n].tail, vx, RF(pl + PL_MAX_SPEED_F), vy, ground, dash, jump, rc[n].hold);
    /* P-speed for an NSMBW character (CHARACTERS_AND_GAMES.md; NSMB2's Super Leaf, not SMB3's
       power meter): NSMBW's own run up to its dash top speed; with the leaf the top is raised
       (PSPEED_MULT) and, held at the top, it climbs on so the whole run from a standstill takes
       PSPEED_RAMP frames. The range above NSMBW's own top is P-speed: the P-run, a P-jump, flight */
    {   uint32_t cur = R32(pl + PL_SPEED_DATA), mine = SM_SPEEDP + 120 * (uint32_t)n;
        if (cur != mine) pm[n].speed_orig = cur;
        float base_top = pm[n].speed_orig ? RF(pm[n].speed_orig + 8) : 3.0f, top = base_top * PSPEED_MULT;
        if (pm[n].pcap < base_top) pm[n].pcap = base_top;
        if (!rc[n].on) pm[n].pcap = base_top;
        else if (ground) {
            if (dash && vx >= pm[n].pcap - 0.15f) pm[n].pcap += (top - base_top) / (float)(PSPEED_RAMP - PSPEED_NATIVE);
            else if (!dash || vx < pm[n].pcap - 0.5f) pm[n].pcap = vx > base_top ? vx : base_top;   /* (slowing down or letting go: the climb lost) */
            if (pm[n].pcap > top) pm[n].pcap = top;
        }
        if (pm[n].fly) pm[n].pcap = top;                                 /* (flying: P kept, as NSMB2's meter stays full) */
        int want = pm[n].pcap > base_top + 0.001f && pm[n].speed_orig;
        if (want) {
            if (cur != mine) for (int i = 0; i < 120; i += 4) W32(mine + (uint32_t)i, R32(pm[n].speed_orig + (uint32_t)i));
            W32(mine + 8, fbits(pm[n].pcap)); W32(pl + PL_SPEED_DATA, mine);
        } else if (cur == mine) W32(pl + PL_SPEED_DATA, pm[n].speed_orig);
        /* the status bar's meter: six arrows over NSMBW's own run, [P] in P-speed */
        if (ground || pm[n].fly) {
            int k = (int)(6.0f * vx / base_top); if (k > 6) k = 6; if (k < 0) k = 0;
            pm[n].pstate = ground && rc[n].on && vx > base_top + PSPEED_MARGIN;
            pm[n].power = (pm[n].pstate || pm[n].fly) ? 0x7F : (1 << k) - 1;
        } else pm[n].pstate = 0;
        if (pm[n].fly && pm[n].fly != 0xFF && (tick & 1)) pm[n].fly--;
    }
    int pwas = pm[n].ground_was && pm[n].pstate_was;
    pm[n].pstate_was = pm[n].pstate;
    if (!rc[n].on) { pm[n].fly = 0; pm[n].wag = 0; return; }
    if (pm[n].pstate && !pwas && rc[n].hold < 0) ra_start(ctx, base, n, RA_PRUN, 1.0f, 5.0f, 0);   /* (the P-run: the game asks for its run again each frame and gets ours) */
    /* Player_JumpFlyFlutter (the Raccoon's) */
    if (jump_new && (ground || pm[n].ground_was) && pwas && !pm[n].fly) pm[n].fly = 0x80;   /* (a jump out of P-speed: flight time; NSMBW has already left the ground this frame) */
    if (!ground) {
        if (pm[n].wag) pm[n].wag--;
        if (jump_new) pm[n].wag = 0x10;
        float yv = -vy * 16.0f;                                          /* (SMB3's units) */
        if (pm[n].wag && yv >= PLAYER_FLY_YVEL) {
            if (pm[n].fly) {
                int y = PLAYER_FLY_YVEL;
                if (pm[n].fly < 0x0F) y = (pm[n].fly & 8) ? -0x10 : 0;  /* (little flight left: up and level by turns) */
                vy_set(pl, (float)y);
            } else if (yv >= PLAYER_TAILWAG_YVEL) vy_set(pl, PLAYER_TAILWAG_YVEL);   /* (the flutter: falling slowly) */
        }
    } else pm[n].wag = 0;
    /* Player_TailAttackAnim: B, not ducking, not already - and (NSMB2) not while carrying: the
       run button that picks a shell up does not also swing the tail */
    int carrying = R32(pl + 10872) != 0 || smb3_stage_carry(pl);
    if (dash_new && !pm[n].tail && !carrying) {
        pm[n].tail = 0x12;
        int left = R8(pl + PL_DIRECTION) != 0;
        ra_start(ctx, base, n, left ? RA_ATTACK_L : RA_ATTACK_R, 1.0f, 0.0f, 1);
    }
    if (pm[n].tail == 0x0C || pm[n].tail == 9) obj_tail(n, R8(pl + PL_DIRECTION) != 0);   /* (Object_RespondToTailAttack) */
    /* Player_TailAttack_HitBlocks: at 9, the tile ahead at the feet + 4 (a tail hit busts bricks) */
    if (pm[n].tail == 9) {
        float px = RF(pl + PL_POS), py = RF(pl + PL_POS + 4); int left = R8(pl + PL_DIRECTION) != 0, tx, ty;
        if (tile_of(px + (left ? -13.0f : 13.0f), py + 4.0f, &tx, &ty) && is_block(L.tile[ty * L.w + tx])) {
            hit_who = n; hit_x = px; hit_block(tx, ty, 1, gcall(ctx, base, A_IS_STAR, 1, pl) != 0, 0);
        }
    }
    pm[n].ground_was = ground;
    /* the animations: the swipe until it ends; flight; the flutter */
    int want = -1;
    if (pm[n].tail) want = rc[n].hold == RA_ATTACK_L || rc[n].hold == RA_ATTACK_R ? rc[n].hold : RA_ATTACK_R;
    else if (!ground && pm[n].fly) want = carrying ? RA_FLY_C : RA_FLY;   /* (NSMB2's flight with something held: its _carry version) */
    else if (!ground && pm[n].wag && vy <= 0) want = carrying ? RA_FLY_C : RA_FALL;
    if (want != rc[n].hold) {
        if (want < 0) rc[n].hold = -1;                                   /* (the game's own animation again: it asks for it every frame) */
        else if (want != RA_ATTACK_L && want != RA_ATTACK_R) ra_start(ctx, base, n, want, 1.0f, 3.0f, 1);
    }
    (void)big;
}
/* dAcPy_c::setNextPowerup (gm_d_player.c asks): a Raccoon hit drops to Super, as in SMB3 */
int smb3_stage_powerdown(uint32_t pl, uint32_t *powerup) {
    if (!smb3_stage_on()) return 0;
    /* SMB3's rule (Player_GetHurt): a suit (the Raccoon, the Frog) hit drops to Super, not small */
    int n = (int8_t)R8(pl + PL_PLR_NO); uint32_t mode = R32(pl + PL_MODE);
    if (n < 0 || n > 7 || !pu_is_new(mode) || *powerup != PU_SMALL) return 0;
    *powerup = PU_SUPER;
    if (retro_is_player(pl)) { poof.req[n] = 1; poof.pl[n] = pl; }       /* (an NES character: Player_SuitLost $17 - Big) */
    rt_log("smb3", "player %d: hit - the %s suit gone, Super", n + 1, pu_name(mode));
    return 1;
}
/* landing on a note block (Level_DoBumpBlocks from the feet: Player_BounceDir 0): the block goes
   down and up again (Bouncer_PUpVel, 10 frames) with the Player on it; then ObjNorm_BounceDU's
   launch, Player_YVel -$38 - or -$70 if A was pressed (newly: Pad_Input) while it moved (Timer2).
   NSMBW's own jump is held off meanwhile (smb3_stage_player_exec) */
static struct { int t, big, jump_was; } nb[8];
static int note_item(uint8_t v, int big) {
    switch (v) { case 0x2F: return big ? SPR_FLOWER : SPR_MUSHROOM; case 0x30: return big ? SPR_LEAF : SPR_MUSHROOM; case 0x31: return SPR_STAR; }
    return -1;
}
static void note_frame(uint32_t pl, int n, float px, float py, int big) {
    int ground = (R32(pl + PL_BG_CROSS1) & 1) != 0;
    int jump = gcall(blk_ctx, blk_base, A_KEY_JUMP, 1, pl + PL_KEY) != 0 || (nb[n].t && (R16(pl + PL_KEY + 4) & 0x0900));
    if (nb[n].t) {
        if (jump && !nb[n].jump_was) nb[n].big = 1;
        nb[n].jump_was = jump;
        if (--nb[n].t == 0) {                                            /* (the launch: NSMBW's jump at that speed) */
            uint32_t fn = R32(R32(pl + AC_VTABLE) + 0x3FC);
            blk_ctx->f[1].d = blk_ctx->ps1[1] = nb[n].big ? 7.0 : 3.5; blk_ctx->f[2].d = blk_ctx->ps1[2] = RF(pl + 0x10C);
            if (fn) gcall(blk_ctx, blk_base, fn, 4, pl, 1, 0, 2);
            rt_log("smb3", "note block: player %d launched (%s)", n + 1, nb[n].big ? "high" : "low");
        }
        return;
    }
    nb[n].jump_was = jump;
    if (!ground || RF(pl + PL_SPEED + 4) > 0.5f) return;
    static const float dx[3] = {0, -4, 4};
    for (int k = 0; k < 3; k++) {
        int tx, ty;
        if (!tile_of(px + dx[k], py - 2, &tx, &ty) || !is_note(L.tile[ty * L.w + tx])) continue;
        uint8_t v = L.tile[ty * L.w + tx];
        int s = 0; while (s < NBUMP && bumps[s].on) s++;
        if (s == NBUMP) return;
        hit_who = n; hit_block(tx, ty, big, 0, 1);                       /* (from above: down, its item out below) */
        (void)v;
        nb[n].t = 10; nb[n].big = 0;
        return;
    }
}
static int note_bouncing(int n) { return n >= 0 && n < 8 && nb[n].t > 0; }

/* the white blocks (prg008 PRG008_BE31, plains levels only): standing on a big white block's top
   ($25-$27) holding down, Player_WhiteBlkCnt counts up; at $F0 the Player drops 6 pixels through
   it (its top is solid on top only) and goes behind the scenes (Player_Behind $F0). PRG008_A766:
   Player_Behind counts down every other tick; while the tile at the Player's head (+8, +20 small
   or ducking / +10) is neither $41 nor the sky ($80) it stays behind (at least 1), and no object
   touches it (Player_Behind_En). While Player_Behind isn't 0 it's drawn behind the tiles */
static struct { int cnt, behind, en; } wb[8];
static int wb_hidden(int n) { return n >= 0 && n < 8 && wb[n].en; }
static void white_blocks(uint32_t pl, int n, int big, float px, float py) {
    extern uint64_t g_frames_presented;
    uint16_t keys = R16(pl + PL_KEY + 4); int ground = (R32(pl + PL_BG_CROSS1) & 1) != 0;
    if (wb[n].behind) {
        if (g_frames_presented & 1) wb[n].behind--;
        int duck = (keys & 1) && ground, tx = (int)floorf((px - L.lx) / 16.0f), ty = (int)floorf((-py - L.ly - 32 + ((!big || duck) ? 20 : 10)) / 16.0f);
        int t = tx >= 0 && tx < L.w && ty >= 0 && ty < LH ? L.tile[ty * L.w + tx] : 0x80;
        wb[n].en = !(t == 0x41 || t == 0x80);
        if (wb[n].en && !wb[n].behind) wb[n].behind = 1;
        if (!wb[n].behind) rt_log("smb3", "white block: player %d back in front", n + 1);
    } else wb[n].en = 0;
    int on = 0;
    if (nes_ram_ptr()[0x70A] == 1 && ground) {                           /* (Level_TilesetIdx 0: plains) */
        int ty = (int)floorf((-py - L.ly + 1) / 16.0f);
        for (int k = 0; k < 2 && ty >= 0 && ty < LH; k++) {              /* (Level_Tile_GndL / GndR) */
            int tx = (int)floorf((px + (k ? 3 : -4) - L.lx) / 16.0f);
            if (tx >= 0 && tx < L.w && (uint8_t)(L.tile[ty * L.w + tx] - 0x25) < 3) on = 1;
        }
    }
    if (!on || !(keys & 1)) wb[n].cnt = 0;
    else if (++wb[n].cnt == 0xF0) {                                      /* (fall into the background) */
        wb[n].behind = 0xF0; wb[n].en = 1;
        WF(pl + PL_POS + 4, py - 6.0f); W32(pl + PL_SPEED + 4, fbits(0.0f));
        rising[n].y = py - 6.0f;                                         /* (feet below the top now: it no longer holds them) */
        W16(pl + PL_KEY + 6, (uint16_t)(R16(pl + PL_KEY + 6) & ~0x0900));
        rt_log("smb3", "white block: player %d falls behind the scenes", n + 1);
    }
}
static void player_blocks(uint32_t pl) {
    int n = (int8_t)R8(pl + PL_PLR_NO); if (n < 0 || n > 7) return;
    int mode = (int)R32(pl + PL_MODE), big = mode != 0 && mode != 3;   /* (0 small, 3 mini) */
    raccoon_set(n, mode == PU_RACCOON);                                  /* (the suit: the player's power-up) */
    float px = RF(pl + PL_POS), py = RF(pl + PL_POS + 4);
    float h = (big ? 28.0f : 16.0f) * (retro_is_player(pl) ? 1.0f : PLAYER_SCALE), hw = 5.0f;
    rising[n].on = 1; rising[n].x = px; rising[n].y = py; rising[n].vy = RF(pl + PL_SPEED + 4);
    white_blocks(pl, n, big, px, py);
    pipe_frame(pl, n, big, px, py, h);
    if (getenv("SMB3_MDL_LOG")) { uint32_t mdl = R32(R32(pl + 3560) + 4); static int k; if (mdl && (k++ % 10) == 0) rt_log("smb3", "mdl: player %d mode %u mdl %08X mode %u cur %u prev %u vis %u flags %08X", n + 1, R32(pl + PL_MODE), mdl, R8(mdl + 338), R32(mdl + 1904), R32(mdl + 1908), R8(mdl + 339), R32(pl + 0x10D4)); }
    {   /* testing: SMB3_TEST_GIVE=v[,frame] - NSMBW's change to power-up v (rt_powerup.h), once, that many frames in */
        static int given[8]; static int t[8]; const char *g = getenv("SMB3_TEST_GIVE");
        if (g && !given[n] && ++t[n] > (strchr(g, ',') ? atoi(strchr(g, ',') + 1) : 30)) {
            given[n] = 1; uint32_t v = (uint32_t)atoi(g);
            int r = (int)gcall(blk_ctx, blk_base, A_CHANGE_POWERUP, 2, pl, v);
            rt_log("smb3", "test: player %d given power-up %u (ChangePowerupWithAnimation: %d)", n + 1, v, r);
        }
    }
    { static int last_mode[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
      if (mode != last_mode[n]) { if (last_mode[n] >= 0) rt_log("smb3", "player %d: power-up %d -> %d", n + 1, last_mode[n], mode); last_mode[n] = mode; } }
    if (getenv("SMB3_STAGE_TRACE")) rt_log("smb3", "trace p%d anim %d stop %02X chg %d x %.1f y %.1f vy %.2f bg %08X hip %d", n + 1, R32(R32(pl + 3560) + 4) ? (int)R32(R32(R32(pl + 3560) + 4) + 340) : -1, R8(EXEC_STOP_REQ), chg.t[n], px - L.lx, -py - L.ly, rising[n].vy, R32(pl + PL_BG_CROSS1), (int)gcall(blk_ctx, blk_base, A_TEST_FLAG, 2, pl, STATUS_HIP_FALL));
    hit_x = px;
    if (chg.req[n]) { chg.req[n] = 0; chg_start(n, pl, 0); }            /* (asked for from setNextPowerup: the Raccoon hit) */
    objs_player(pl, n, big, px, py);
    abilities(blk_ctx, blk_base, pl, n, big);
    items_touch(blk_ctx, blk_base, pl, n, px, py, h);
    /* coins: the tiles the box overlaps */
    for (float yy = py + 2; yy < py + h; yy += 8) for (float xx = px - hw; xx <= px + hw; xx += hw) {
        int tx, ty;
        if (tile_of(xx, yy, &tx, &ty) && L.tile[ty * L.w + tx] == T_COIN) { L.tile[ty * L.w + tx] = T_SKY; coin_get(n); SG.score += 5; }   /* (50 points) */
    }
    /* a new head bump: the block above the head (the middle, else the sides) */
    static uint8_t head_was[8];
    int head = (R32(pl + PL_BG_CROSS1) & 2) != 0;
    if (head && !head_was[n]) {
        static const float dx[3] = {0, -5, 5};
        for (int k = 0; k < 3; k++) {
            int tx, ty;
            if (tile_of(px + dx[k], py + h + 4, &tx, &ty) && (is_block(L.tile[ty * L.w + tx]) || is_note(L.tile[ty * L.w + tx]))) {
                hit_who = n; hit_block(tx, ty, big, gcall(blk_ctx, blk_base, A_IS_STAR, 1, pl) != 0, 0); break;
            }
        }
    }
    head_was[n] = (uint8_t)head;
    note_frame(pl, n, px, py, big);
    if (R32(pl + PL_BG_CROSS1) & 1) {                                    /* (the feet on a P-Switch) */
        static const float sdx[3] = {0, -4, 4};
        for (int k = 0; k < 3; k++) { int tx, ty; if (tile_of(px + sdx[k], py - 2, &tx, &ty) && L.tile[ty * L.w + tx] == T_PSWITCH) { pswitch_stomp(tx, ty); rt_log("smb3", "P-switch: pressed by player %d", n + 1); break; } }
    }
    /* the ground pound (NSMBW's, status 28: its fall): the block under the feet, before the landing
       (this frame's fall ahead), is hit from above - SMB3's path for a block hit from above (note
       blocks: bounce down, the item out below); a brick under a big player breaks and the fall goes on */
    if (gcall(blk_ctx, blk_base, A_TEST_FLAG, 2, pl, STATUS_HIP_FALL)) {
        float vy = RF(pl + PL_SPEED + 4), reach = vy < 0 ? -vy + 2 : 2;
        static const float dx[3] = {0, -4, 4};
        for (int k = 0; k < 3; k++) {
            int tx, ty, done = 0;
            for (float yy = py - 1; yy >= py - reach && !done; yy -= 4)
                if (tile_of(px + dx[k], yy, &tx, &ty) && is_block(L.tile[ty * L.w + tx])) {
                    /* (user, 2026-11-22: a ground pound sends a Super Leaf out of the top, as a hit
                       from below would - not to be had till it starts to fall; other items as NSMBW) */
                    hit_who = n; hit_pound = 1; hit_block(tx, ty, big, gcall(blk_ctx, blk_base, A_IS_STAR, 1, pl) != 0, 1); hit_pound = 0; done = 1;
                }
            if (done) break;
        }
    }
}
/* the tracking points, from the model's joints (dPyMdlBase_c::getJointMtx, vtable +80; the
   matrices carry the model's turn and scale): the tail at the hips (joint 1 "skl_root": local Y
   is forward, X up) out behind; the ears on the head (joint "face_1": 16, Toads 15; local -Y up,
   X forward, Z to the side), one to each side */
#define RC_TAIL_BACK  4.5f                       /* (joint units behind the hips) */
#define RC_TAIL_UP    0.5f
#define RC_EAR_UP     7.5f                       /* (above the head joint) */
#define RC_EAR_SIDE   3.8f
#define RC_EAR_BACK   0.5f
static int jmtx(ppc_context *ctx, uint8_t *base, uint32_t mdl, int j, float m[12]) {
    for (int k = 0; k < 12; k++) W32(SM_JMTX + 4 * k, 0);
    gcall(ctx, base, R32(R32(mdl) + 80), 3, mdl, SM_JMTX, j);
    int any = 0; for (int k = 0; k < 12; k++) { m[k] = RF(SM_JMTX + 4 * k); any |= m[k] != 0; }
    return any;
}
static void raccoon_anchor(ppc_context *ctx, uint8_t *base, uint32_t pl) {
    int n = (int8_t)R8(pl + PL_PLR_NO); if (n < 0 || n > 7) return;
    rc[n].have = 0;
    raccoon_set(n, R32(pl + PL_MODE) == PU_RACCOON);                     /* (the suit: the player's power-up) */
    if (!rc[n].on || retro_is_player(pl)) { rc[n].mdl = 0; return; }
    uint32_t mdl = R32(R32(pl + 3560) + 4); if (!mdl) return;
    rc[n].mdl = mdl; raccoon_anims_init(ctx, base);
    if (ra_ready > 0 && !getenv("SMB3_STAGE_NO_MERGE")) { uint32_t f = R32(mdl + MDL_RES_ANIM), m = anm_merged(ctx, base, f); if (m && f != m) W32(mdl + MDL_RES_ANIM, m); }   /* (NSMB2's animations: the model's own now) */
    float h[12], d[12];
    if (!jmtx(ctx, base, mdl, 1, h)) return;
    if (!jmtx(ctx, base, mdl, 16, d) && !jmtx(ctx, base, mdl, 15, d)) return;
    /* columns: X (m0 m4 m8), Y (m1 m5 m9), Z (m2 m6 m10), position (m3 m7 m11) */
    float s = sqrtf(h[1] * h[1] + h[5] * h[5] + h[9] * h[9]); if (s <= 0) return;
    for (int a = 0; a < 3; a++) {
        rc[n].fwd[a] = h[a * 4 + 1] / s;
        rc[n].tail[a] = h[a * 4 + 3] - h[a * 4 + 1] * RC_TAIL_BACK + h[a * 4 + 0] * RC_TAIL_UP;
        for (int e = 0; e < 2; e++)
            rc[n].ear[e][a] = d[a * 4 + 3] - d[a * 4 + 1] * RC_EAR_UP + d[a * 4 + 2] * (e ? RC_EAR_SIDE : -RC_EAR_SIDE) - d[a * 4 + 0] * RC_EAR_BACK;
    }
    rc[n].tail_s = s * 0.875f;                                           /* (an SMB3 pixel: 32 of them to a big player) */
    int type = (int)R32(pl + 0x14D4); rc[n].colour = type >= 0 && type < NRCOL ? type : 0;
    if (getenv("SMB3_STAGE_TEST_COLOUR")) rc[n].colour = atoi(getenv("SMB3_STAGE_TEST_COLOUR"));   /* (testing: another character's parts) */
    rc[n].face_left = rc[n].fwd[0] < 0;
    rc[n].tail_pose = RC_TAIL_OUT;
    memcpy(rc[n].hips, h, sizeof h); memcpy(rc[n].head, d, sizeof d);
    rc[n].have = 1;
    tail_init(); tail_update(n, pl);
}
#include "smb3_stage_frog.inc"
static void blocks_reset(void) {
    frog_reset();
    memset(items, 0, sizeof items); memset(rising, 0, sizeof rising); memset(bumps, 0, sizeof bumps); memset(pops, 0, sizeof pops);
    memset(scores, 0, sizeof scores); memset(rc, 0, sizeof rc); memset(pm, 0, sizeof pm); for (int i = 0; i < 8; i++) rc[i].hold = -1; memset(busts, 0, sizeof busts); memset(&b10, 0, sizeof b10); b10.id = -1; if (!keep_counters) { SG.coins = 0; SG.score = 0; memset(SG.cards, 0, sizeof SG.cards); }
    if (poof.t || chg_any()) W8(EXEC_STOP_REQ, (uint8_t)(R8(EXEC_STOP_REQ) & 0xF0));
    memset(&poof, 0, sizeof poof); memset(&chg, 0, sizeof chg); memset(nb, 0, sizeof nb); memset(&PS, 0, sizeof PS); memset(wb, 0, sizeof wb);
    objs_reset();
}
static void blocks_frame(void) {                 /* (once a frame the game runs) */
    { extern uint64_t g_frames_presented; if (objs_exec_frame != g_frames_presented) return; }
    for (int i = 0; i < NBUMP; i++) {
        if (!bumps[i].on) continue;
        if (bumps[i].pos == 0) {                                         /* done: the tile behind it */
            L.tile[bumps[i].ty * L.w + bumps[i].tx] = bumps[i].after; bumps[i].on = 0; continue;
        }
        if (bumps[i].pos == 10 && bumps[i].item >= 0) item_spawn(bumps[i].item, bumps[i].tx, bumps[i].ty, bumps[i].down, bumps[i].pounded);
        bumps[i].y16 += bumps[i].vy;                                     /* (Object_ApplyYVel) */
        bumps[i].vy = bumps[i].down ? BOUNCER_VEL[bumps[i].pos] : -BOUNCER_VEL[bumps[i].pos];   /* (from below: negated) */
        bumps[i].pos--;
    }
    tick++;
    pswitch_frame();
    if (b10.timer) b10.timer--;                                          /* (Player_Update: the counters at Event_Countdown) */
    for (int i = 0; i < NPOP; i++) {                                     /* CoinPUp_UpdateAndDraw */
        if (!pops[i].on) continue;
        pops[i].counter++;
        pops[i].y += pops[i].vy;
        if (!(pops[i].counter & 3)) {
            pops[i].vy++;
            if (pops[i].vy == 5) { score_pop(5, pops[i].x - 4, pops[i].y, pops[i].who); pops[i].on = 0; }   /* (100 points, centred) */
        }
    }
    for (int i = 0; i < NSCORE; i++) {                                   /* Score_GiveAndDraw */
        if (!scores[i].value) continue;
        if (!scores[i].counter) { scores[i].value = 0; continue; }
        int v = scores[i].value > 0x0D ? 0x0D : scores[i].value;
        if (scores[i].counter-- == 0x2A) { SG.score += SCORE_ADD[v - 1]; if (v == 0x0D) { give_life(scores[i].who); sfx_level1(SFX1_1UP); } }   /* (PRG007_AACF: the 1-up sound) */
        static const uint8_t RISE[4] = {3, 1, 0, 0};
        if (!(tick & RISE[(scores[i].counter >> 4) & 3])) scores[i].y--;
    }
    for (int i = 0; i < NBUST; i++) {                                    /* BrickBust_DrawAndUpdate */
        if (!busts[i].on) continue;
        if (!(tick & 3)) busts[i].yvel++;
        busts[i].yu += busts[i].yvel; busts[i].yl += busts[i].yvel + 2; busts[i].xdist++;
        if (busts[i].yu >= LH * 16) busts[i].hen |= 8;                   /* (off the bottom: that pair goes) */
        if (busts[i].yl >= LH * 16) busts[i].hen |= 4;
        if (busts[i].hen >= 0x0C && busts[i].yvel >= 8) busts[i].on = 0;
    }
    items_frame();
    objs_frame();
}

/* ---- the picture ---- */
/* (a tile's backdrop pixels (colour 0): RGB5A3's other form - 4-bit colour, alpha 6 (219): drawn
   alike (the alpha compare passes them, no blending), but a pass with a higher reference drops
   them - the tiles drawn again in front of a player behind the scenes, its sprite showing where
   SMB3's background is its backdrop colour) */
static void tex_upload(void) {                   /* the atlas as GX RGB5A3 (4 x 4 blocks) */
    uint32_t o = SM_TEX;
    for (int by = 0; by < tex_h; by += 4) for (int bx = 0; bx < 256; bx += 4)
        for (int y = 0; y < 4; y++) for (int x = 0; x < 4; x++) {
            uint32_t c = atlas[(by + y) * 256 + bx + x];
            uint16_t v = (c >> 24) == (BACKDROP_A >> 24) ? (uint16_t)(6 << 12 | ((c >> 20) & 15) << 8 | ((c >> 12) & 15) << 4 | ((c >> 4) & 15))
                       : (c >> 24) ? (uint16_t)(0x8000 | ((c >> 19) & 31) << 10 | ((c >> 11) & 31) << 5 | ((c >> 3) & 31)) : 0;   /* (alpha 0: RGB5A3 transparent) */
            W16(o, v); o += 2;
        }
    tex_ready = 1;
}
static void gx_setup(ppc_context *ctx, uint8_t *base) {
    gcall(ctx, base, A_G3D_INVALIDATE, 1, 0x7FF);
    gcall(ctx, base, A_DISABLE_IND_TEX, 0);
    gcall(ctx, base, A_GXClearVtxDesc, 0);
    gcall(ctx, base, A_GXSetVtxDesc, 2, 9, 1);
    gcall(ctx, base, A_GXSetVtxDesc, 2, 13, 1);
    gcall(ctx, base, A_GXSetVtxAttrFmt, 5, 0, 9, 1, 4, 0);
    gcall(ctx, base, A_GXSetVtxAttrFmt, 5, 0, 13, 1, 4, 0);
    gcall(ctx, base, A_GXSetNumChans, 1, 0);
    gcall(ctx, base, A_GXSetNumTexGens, 1, 1);
    gcall(ctx, base, A_GXSetTexCoordGen2, 6, 0, 1, 4, 60, 0, 125);
    gcall(ctx, base, A_GXSetNumIndStages, 1, 0);
    gcall(ctx, base, A_GXSetTevDirect, 1, 0);
    gcall(ctx, base, A_GXSetNumTevStages, 1, 1);
    gcall(ctx, base, A_GXSetTevOrder, 4, 0, 0, 0, 0xFF);
    gcall(ctx, base, A_GXSetTevOp, 2, 0, 3);
    gcall(ctx, base, A_GXSetAlphaCompare, 5, 4, 0, 0, 7, 0);       /* (alpha > 0: sprites' transparent pixels) */
    gcall(ctx, base, A_GXSetBlendMode, 4, 0, 1, 0, 0);
    gcall(ctx, base, A_GXSetZMode, 3, 1, 3, 1);                     /* LEQUAL, write */
    gcall(ctx, base, A_GXSetZCompLoc, 1, 0);                        /* (after the texture: a transparent pixel leaves the depth - a player behind the scenes shows through) */
    gcall(ctx, base, A_GXSetCullMode, 1, 0);
    gcall(ctx, base, A_GXSetColorUpdate, 1, 1);
    gcall(ctx, base, A_GXInitTexObj, 8, SM_TEXOBJ, SM_TEX, 256, (uint32_t)tex_h, 5, 0, 0, 0);   /* RGB5A3, clamp */
    ctx->f[1].d = 0.0; ctx->f[2].d = 0.0; ctx->f[3].d = 0.0;
    gcall(ctx, base, A_GXInitTexObjLOD, 8, SM_TEXOBJ, 0, 0, 0, 0, 0, 0, 0);
    gcall(ctx, base, A_GXLoadTexObj, 2, SM_TEXOBJ, 0);
    gcall(ctx, base, A_GXLoadPosMtxImm, 2, SM_MTX, 0);
    gcall(ctx, base, A_GXSetCurrentMtx, 1, 0);
}
static void quad(float x0, float y0, float x1, float y1, float z, float u0, float v0, float u1, float v1) {
    /* (the texture coordinates pulled in a 20th of a texel from each edge: point sampling at a
       pixel that lands exactly on a tile's edge took the neighbouring atlas tile's texels - the
       stray dark columns and rows; mirrored quads alike) */
    float eu = 0.05f / 256.0f, ev = 0.05f / (float)(tex_h ? tex_h : 256);
    if (u1 > u0 + eu * 2) { u0 += eu; u1 -= eu; } else if (u0 > u1 + eu * 2) { u0 -= eu; u1 += eu; }
    if (v1 > v0 + ev * 2) { v0 += ev; v1 -= ev; } else if (v0 > v1 + ev * 2) { v0 -= ev; v1 += ev; }
    const float q[4][5] = {{x0, y0, z, u0, v0}, {x1, y0, z, u1, v0}, {x1, y1, z, u1, v1}, {x0, y1, z, u0, v1}};
    for (int i = 0; i < 4; i++) for (int j = 0; j < 5; j++) gx_fifo_write(fbits(q[i][j]), 4);
}
/* the 3D tails: their own vertex format (position, colour, uv), texture (repeating) and TEV
   (texture x vertex colour) */
#define A_GXSetChanCtrl 0x801C6AF0u
static void tail_draw(ppc_context *ctx, uint8_t *base) {
    if (tail_ready <= 0) return;
    int nt = 0; for (int i = 0; i < 8; i++) nt += RC_SHOWN(i);
    if (!nt) return;
    gcall(ctx, base, A_GXClearVtxDesc, 0);
    gcall(ctx, base, A_GXSetVtxDesc, 2, 9, 1); gcall(ctx, base, A_GXSetVtxDesc, 2, 11, 1); gcall(ctx, base, A_GXSetVtxDesc, 2, 13, 1);
    gcall(ctx, base, A_GXSetVtxAttrFmt, 5, 1, 9, 1, 4, 0);
    gcall(ctx, base, A_GXSetVtxAttrFmt, 5, 1, 11, 1, 5, 0);
    gcall(ctx, base, A_GXSetVtxAttrFmt, 5, 1, 13, 1, 4, 0);
    gcall(ctx, base, A_GXSetNumChans, 1, 1);
    gcall(ctx, base, A_GXSetChanCtrl, 7, 4, 0, 0, 1, 0, 0, 2);          /* COLOR0A0: no lighting, the vertex's colour */
    gcall(ctx, base, A_GXSetTevOrder, 4, 0, 0, 0, 4);
    gcall(ctx, base, A_GXSetTevOp, 2, 0, 0);                             /* MODULATE */
    for (int t = 0; t < 2; t++) {                                        /* (each tail with its own texture) */
        int cnt = 0; for (int i = 0; i < 8; i++) if (RC_SHOWN(i) && tail_variant(i) == t) cnt += smb3_tail_nidx[t];
        if (!cnt) continue;
        uint32_t obj = SM_TAILOBJ + 0x20u * (uint32_t)t;
        gcall(ctx, base, A_GXInitTexObj, 8, obj, SM_TAILTEX + 0x200u * (uint32_t)t, 16, 16, 5, 1, 1, 0);   /* RGB5A3, repeat */
        ctx->f[1].d = 0.0; ctx->f[2].d = 0.0; ctx->f[3].d = 0.0;
        gcall(ctx, base, A_GXInitTexObjLOD, 8, obj, 0, 0, 0, 0, 0, 0, 0);
        gcall(ctx, base, A_GXLoadTexObj, 2, obj, 0);
        gcall(ctx, base, A_GXBegin, 3, 0x90, 1, (uint32_t)cnt);
        int v0 = t ? smb3_tail_nverts[0] : 0, i0 = t ? smb3_tail_nidx[0] : 0;
        for (int i = 0; i < 8; i++) if (RC_SHOWN(i) && tail_variant(i) == t)
            for (int k = 0; k < smb3_tail_nidx[t]; k++) {
                int v = smb3_tail_idx[i0 + k]; uint8_t l = rc[i].tl[v];
                for (int j = 0; j < 3; j++) gx_fifo_write(fbits(rc[i].tv[v][j]), 4);
                gx_fifo_write(((uint32_t)l << 24) | ((uint32_t)l << 16) | ((uint32_t)l << 8) | 0xFF, 4);
                gx_fifo_write(fbits(smb3_tail_vtx[v0 + v][6]), 4); gx_fifo_write(fbits(1.0f - smb3_tail_vtx[v0 + v][7]), 4);   /* (3DS textures: v from the bottom) */
            }
    }
    /* the ears: the vertex colour alone (PASSCLR), lit like the tail */
    int ne = 0; for (int i = 0; i < 8; i++) if (RC_SHOWN(i) && ears_have(rc[i].colour)) ne += smb3_ears_nidx[rc[i].colour];
    if (!ne) return;
    gcall(ctx, base, A_GXSetTevOp, 2, 0, 4);
    gcall(ctx, base, A_GXBegin, 3, 0x90, 1, (uint32_t)ne);
    const float L[3] = {-0.35f, 0.55f, 0.76f};
    for (int i = 0; i < 8; i++) if (RC_SHOWN(i) && ears_have(rc[i].colour)) {
        int c = rc[i].colour, v0 = c ? smb3_ears_nverts[0] : 0, i0 = c ? smb3_ears_nidx[0] : 0;
        const float *m = rc[i].head;
        for (int k = 0; k < smb3_ears_nidx[c]; k++) {
            int v = v0 + smb3_ears_idx[i0 + k]; const float *x = smb3_ears_vtx[v];
            float q[3], qn[3];
            for (int a = 0; a < 3; a++) {
                q[a] = m[a * 4] * x[0] + m[a * 4 + 1] * x[1] + m[a * 4 + 2] * x[2] + m[a * 4 + 3];
                qn[a] = m[a * 4] * x[3] + m[a * 4 + 1] * x[4] + m[a * 4 + 2] * x[5];
            }
            float len = sqrtf(qn[0] * qn[0] + qn[1] * qn[1] + qn[2] * qn[2]), dd = len > 0 ? (qn[0] * L[0] + qn[1] * L[1] + qn[2] * L[2]) / len : 0;
            float lit = 0.55f + 0.6f * (dd > 0 ? dd : 0); if (lit > 1) lit = 1;
            uint32_t col = 0xFF;
            for (int a = 0; a < 3; a++) col |= (uint32_t)(smb3_ears_rgb[v][a] * lit) << (24 - 8 * a);
            for (int a = 0; a < 3; a++) gx_fifo_write(fbits(q[a]), 4);
            gx_fifo_write(col, 4); gx_fifo_write(0, 4); gx_fifo_write(0, 4);
        }
    }
}
static void half_quad(int h, float x, float y, float z, int hflip, int vflip) {   /* (an 8 x 16 sprite at level pixel x, y) */
    int sl = half_slot0 + (h >> 1);
    float u0 = (sl % 16) * 16 / 256.0f + (h & 1) * 8 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h;
    float u1 = u0 + 8 / 256.0f, v1 = v0 + 16 / (float)tex_h;
    if (hflip) { float t = u0; u0 = u1; u1 = t; }
    if (vflip) { float t = v0; v0 = v1; v1 = t; }
    quad(L.lx + x, -(L.ly + y), L.lx + x + 8, -(L.ly + y + 16), z, u0, v0, u1, v1);
}
static int half_of(uint8_t pat) { for (int h = H_S59; h < NHALF; h++) if (half_pat[h] == pat) return h; return H_S59; }
static void proc_draw(ppc_context *ctx, uint8_t *base) {
    if (smb3_stage_on() && map_on()) { map_draw(ctx, base); return; }
    if (!smb3_stage_on() || probe || !L.placed) return;
    uint32_t cam = gcall(ctx, base, A_GET_CAMERA_BY_ID, 1, gcall(ctx, base, A_GET_CUR_CAMERA, 0));
    if (getenv("SMB3_STAGE_DRAWLOG")) { extern uint64_t g_frames_presented; rt_log("smb3", "drawlog f%llu proc cam %08X", (unsigned long long)g_frames_presented, cam); }
    if (!cam) return;
    W32(SM_CAMERA, cam); gcall(ctx, base, A_GET_CAMERA_MTX, 2, SM_CAMERA, SM_MTX);
    if (!tex_ready) tex_upload();
    gx_setup(ctx, base);
    /* the tiles that show: from the camera's middle +- 2 screens */
    float zt = pz - 400.0f, zs = pz - 410.0f;
    int nx = 0; for (int i = 0; i < NPOP; i++) nx += pops[i].on; for (int i = 0; i < NITEM; i++) nx += items[i].on; for (int i = 0; i < NBUMP; i++) nx += bumps[i].on;
    for (int i = 0; i < NBUST; i++) nx += busts[i].on * 4; for (int i = 0; i < NSCORE; i++) nx += scores[i].value ? 2 : 0;
    for (int i = 0; i < 8; i++) nx += RC_SHOWN(i) ? 3 : 0;
    nx += objs_quads() + th_quads() + bt_quads() + mg_quads();
    for (int k = 0; k < 8; k++) nx += poof.on[k] ? 2 : 0;
    int n = 1 + L.w * LH + nx;
    gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 4 * n);
    float su = 1.0f / 256, sv = 128.5f / (float)tex_h;
    if (TH.on) { uint8_t t = L.tile[(LH - 1) * L.w]; su = ((t % 16) * 16 + 8) / 256.0f; sv = ((t / 16) * 16 + 8) / (float)tex_h; }   /* (a Toad House: around it, the house's own black - its bottom-left corner's, not the sky colour) */
    extern uint64_t g_frames_presented; int af = (int)((g_frames_presented >> 3) & 3);   /* (SMB3: PT2_Anim, 8 frames each) */
    quad(L.lx - 4000, -(L.ly - 3000), L.lx + L.w * 16 + 4000, -(L.ly + LH * 16 + 3000), zs, su, sv, su, sv);
    #define SLOT_UV(sl, u0, v0) float u0 = ((sl) % 16) * 16 / 256.0f, v0 = ((sl) / 16) * 16 / (float)tex_h
    for (int r = 0; r < LH; r++) for (int c = 0; c < L.w; c++) {
        uint8_t t = L.tile[r * L.w + c];
        float x0 = L.lx + (float)(c * 16), y0 = -(L.ly + (float)(r * 16)), x1 = L.lx + (float)(c * 16 + 16), y1 = -(L.ly + (float)(r * 16 + 16));   /* (shared edges computed alike: no hairline gaps) */
        int sl = af && anim_slot[t] >= 0 ? anim_slot[t] + af - 1 : t;
        SLOT_UV(sl, u0, v0);
        quad(x0, y0, x1, y1, zt, u0, v0, u0 + 16 / 256.0f, v0 + 16 / (float)tex_h);
    }
    for (int i = 0; i < NBUMP; i++) if (bumps[i].on) {                   /* the bouncing block (BounceBlock_Update: drawn as a sprite) */
        uint8_t t = bumps[i].shown; int sl = af && anim_slot[t] >= 0 ? anim_slot[t] + af - 1 : t;
        SLOT_UV(sl, u0, v0);
        float x0 = L.lx + bumps[i].tx * 16, y0 = -(L.ly + bumps[i].ty * 16 + (bumps[i].y16 >> 4));
        quad(x0, y0, x0 + 16, y0 - 16, zt + 1.5f, u0, v0, u0 + 16 / 256.0f, v0 + 16 / (float)tex_h);
    }
    for (int i = 0; i < NPOP; i++) if (pops[i].on) {                     /* coins out of blocks: frame (counter / 4) % 4, the 2nd mirrored */
        int f = (pops[i].counter >> 2) & 3;
        half_quad(H_COIN0 + f, pops[i].x, pops[i].y, zt + 2, f == 1, 0);
    }
    for (int i = 0; i < NBUST; i++) if (busts[i].on) {                   /* brick debris: upper right, upper left, lower right, lower left */
        int hf = (tick >> 1) & 1, vf = (tick >> 2) & 1, e = busts[i].hen;   /* (Level_NoStopCnt & 6: H and V flips) */
        float xr = busts[i].x + busts[i].xdist + 8, xl = busts[i].x - busts[i].xdist, off = -10000;
        half_quad(H_DEBRIS, xr, (e & 8) ? off : busts[i].yu, zt + 2, hf, vf);
        half_quad(H_DEBRIS, xl, (e & 8) ? off : busts[i].yu, zt + 2, hf, vf);
        half_quad(H_DEBRIS, xr, (e & 4) ? off : busts[i].yl, zt + 2, hf, vf);
        half_quad(H_DEBRIS, xl, (e & 4) ? off : busts[i].yl, zt + 2, hf, vf);
    }
    for (int i = 0; i < NSCORE; i++) if (scores[i].value) {              /* score pop-ups: left (none for 10 - 80) and right digits */
        int v = scores[i].value > 0x0D ? 0x0D : scores[i].value;
        uint8_t pl = SCORE_PAT_L[v - 1];
        half_quad(half_of(pl == 0xFF ? 0x59 : pl), pl == 0xFF ? -10000 : scores[i].x, scores[i].y, zt + 3, 0, 0);
        half_quad(half_of(SCORE_PAT_R[v - 1]), scores[i].x + 8, scores[i].y, zt + 3, 0, 0);
    }
    for (int i = 0; i < NITEM; i++) if (items[i].on) {                   /* items: while in the box only the part above it shows */
        int sl = spr_slot0 + items[i].kind; SLOT_UV(sl, u0, v0);
        float u1 = u0 + 16 / 256.0f, v1 = v0 + 16 / (float)tex_h;
        int x = items[i].x16 >> 4, y = items[i].y16 >> 4, yb = y + 16;
        if (items[i].kind != SPR_LEAF && items[i].timer && yb > items[i].block_y) { v1 -= (yb - items[i].block_y) / (float)tex_h; yb = items[i].block_y; }
        if (items[i].down && items[i].kind != SPR_LEAF && y < items[i].block_y + 16 && y + 16 > items[i].block_y) {   /* (under the block) */
            int cut = items[i].block_y + 16 - y; if (cut > 16) cut = 16; v0 += cut / (float)tex_h; y += cut;
        }
        if (yb < y) yb = y;                                              /* (all inside the box: nothing shows; the quad still counts) */
        if (items[i].flip) { float tu = u0; u0 = u1; u1 = tu; }
        /* (rising out of its box: behind the bouncing block, as SMB3's sprite is behind the
           background - else its top row showed over the block as it bounced) */
        quad(L.lx + x, -(L.ly + y), L.lx + x + 16, -(L.ly + yb), items[i].timer && items[i].kind != SPR_LEAF ? zt + 1.0f : zt + 2, u0, v0, u1, v1);
    }
    for (int i = 0; i < 8; i++) if (RC_SHOWN(i)) {           /* the Raccoon placeholder: tail, two ears (in the world, at their joints) */
        float ps = rc[i].tail_s; int fl = rc[i].face_left;
        int h = rc[i].colour * NRC + rc[i].tail_pose, sl = rc_slot0 + (h >> 1);
        float u0 = (sl % 16) * 16 / 256.0f + (h & 1) * 8 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h, u1 = u0 + 8 / 256.0f, v1 = v0 + 16 / (float)tex_h;
        float ax = fl ? 2.0f : 6.0f, ay = 8.5f;                          /* (the tail's root in its 8 x 16: its right edge, facing right) */
        float x0 = rc[i].tail[0] - ax * ps, y0 = rc[i].tail[1] + ay * ps;
        if (fl) { float t = u0; u0 = u1; u1 = t; }
        if (tail_ready > 0) quad(0, 0, 0, 0, 0, 0, 0, 0, 0);               /* (the 3D tail instead: an empty quad keeps the count) */
        else quad(x0, y0, x0 + 8 * ps, y0 - 16 * ps, rc[i].tail[2], u0, v0, u1, v1);
        h = rc[i].colour * NRC + RC_EAR; sl = rc_slot0 + (h >> 1);
        u0 = (sl % 16) * 16 / 256.0f + (h & 1) * 8 / 256.0f; v0 = (sl / 16) * 16 / (float)tex_h; u1 = u0 + 8 / 256.0f; v1 = v0 + 8 / (float)tex_h;
        for (int e = 0; e < 2; e++) {                                    /* (8 x 8, the root at its bottom middle; the 2nd mirrored) */
            float ex = rc[i].ear[e][0] - 2.5f * ps, ey = rc[i].ear[e][1] + 6.0f * ps, eu0 = u0, eu1 = u1;
            if (e != fl) { eu0 = u1; eu1 = u0; ex = rc[i].ear[e][0] - 5.5f * ps; }
            if (ears_have(rc[i].colour)) quad(0, 0, 0, 0, 0, 0, 0, 0, 0);
            else quad(ex, ey, ex + 8 * ps, ey - 8 * ps, rc[i].ear[e][2], eu0, v0, eu1, v1);
        }
    }
    objs_draw(zt + 2.5f);                                               /* (the enemies) */
    th_draw(zt + 2.5f);                                                 /* (a Toad House's message, its item) */
    bt_draw(zt + 2.5f);                                                 /* (a battle's hammers, the poof) */
    mg_draw(zt + 2.6f);                                                 /* (Micro-Goombas) */
    for (int k = 0; k < 8; k++) if (poof.on[k]) {                        /* (the poof: Player_SuitLost_DoPoof) */
        static const uint8_t pp_pat[4] = {0x47, 0x45, 0x43, 0x41};
        uint8_t pt = pp_pat[(poof.shown & 0x0C) >> 2];
        eh_quad(pt, 1, pp[k].x + 8, pp[k].y + 8, 1, 1, zt + 3.0f);
        eh_quad(pt, 1, pp[k].x, pp[k].y + 8, 0, 0, zt + 3.0f);
    }
    {   /* a player behind the scenes (white blocks): the tiles about it again, in front of it -
           their backdrop pixels dropped (PRG029_CF0B: the sprite behind the background) */
        int nbh = 0; for (int k = 0; k < 8; k++) nbh += (wb[k].behind && pp[k].on) || pipe_hidden(k);   /* (in a pipe NSMBW's demo takes it out of play: drawn still) */
        if (nbh && getenv("SMB3_PIPE_LOG")) for (int k = 0; k < 8; k++) if (pipe_hidden(k)) rt_log("smb3", "pipe: overlay for %d at %d,%d (pz %.0f)", k + 1, pp[k].x, pp[k].y, pz);
        if (nbh) {
            gcall(ctx, base, A_GXSetAlphaCompare, 5, 4, 230, 0, 7, 0);
            gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 4 * 25 * nbh);
            for (int k = 0; k < 8; k++) if ((wb[k].behind && pp[k].on) || pipe_hidden(k))
                for (int r = (pp[k].y - 16) >> 4, i = 0; i < 5; i++, r++) for (int c = (pp[k].x - 16) >> 4, j = 0; j < 5; j++, c++) {
                    if (r < 0 || r >= LH || c < 0 || c >= L.w) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); continue; }
                    uint8_t t = L.tile[r * L.w + c]; int sl = af && anim_slot[t] >= 0 ? anim_slot[t] + af - 1 : t;
                    SLOT_UV(sl, u0, v0);
                    quad(L.lx + c * 16, -(L.ly + r * 16), L.lx + c * 16 + 16, -(L.ly + r * 16 + 16), pz + 80.0f, u0, v0, u0 + 16 / 256.0f, v0 + 16 / (float)tex_h);
                }
            gcall(ctx, base, A_GXSetAlphaCompare, 5, 4, 0, 0, 7, 0);
        }
    }
    tail_draw(ctx, base);
    gcall(ctx, base, A_G3D_INVALIDATE, 1, 0x7FF);
}
/* ---- the status bar ---- */
#define SBT(row, col) SB.shown[((row) - 24) * 32 + (col)]
#define A_GXInvalidateTexAll 0x801C76C0u
void gx_mark_dirty(uint32_t addr, uint32_t len);   /* rt_gxrender.c */
/* StatusBar_Fill_Time (each frame the game runs): Level_TimerTick from $28 down, past 0 a second
   off; at 000 it stays */
static int goal_stop_timer(void);
static void goal_msg_draw(ppc_context *ctx, uint8_t *base, float bx, float y0, float sc);
static int th_bar_inventory(uint8_t *t, const uint8_t *nt);
static void th_bar_draw(ppc_context *ctx, uint8_t *base, float bx, float y0, float sc);
static void sb_timer(void) {
    if (SB.time <= 0 || goal_stop_timer() || BT.clock_stop) return;   /* (Level_TimerEn $81 once the card's taken) */
    if (--SB.tick >= 0) return;
    SB.tick = 0x28; SB.time--;
}
static int sb_first_player(void) {               /* (the bar is one player's: the first in) */
    for (int i = 0; i < 8; i++) if (R32(WP_ENTRY_TABLE + 4 * (uint32_t)i)) return i;
    return 0;
}
static void sb_render(void) {
    for (int rr = 0; rr < 6; rr++) for (int c = 0; c < 32; c++) {
        int r = 24 + rr; uint8_t t = SB.shown[rr * 32 + c];
        int ab = SB.attr[((r >> 2) - 6) * 8 + (c >> 2)], q = (ab >> (((r & 2) << 1) | (c & 2))) & 3;
        for (int y = 0; y < 8; y++) {
            uint16_t a = (uint16_t)(((SB.ctrl & 0x10) ? 0x1000 : 0) + t * 16 + y);
            uint8_t lo = SB.chr[a], hi = SB.chr[a + 8];
            for (int x = 0; x < 8; x++) {
                int p = ((lo >> (7 - x)) & 1) | (((hi >> (7 - x)) & 1) << 1);
                SB.px[(rr * 8 + y) * SB_W + c * 8 + x] = c == 0 ? ppu_rgb(0x0F) : ppu_rgb(SB.pal[p ? q * 4 + p : 0]);   /* (column 0: under SMB3's left mask) */
            }
        }
    }
    uint32_t o = SM_SBTEX;
    for (int by = 0; by < SB_H; by += 4) for (int bx = 0; bx < SB_W; bx += 4)
        for (int y = 0; y < 4; y++) for (int x = 0; x < 4; x++) {
            uint32_t c = SB.px[(by + y) * SB_W + bx + x];
            W16(o, (uint16_t)(0x8000 | ((c >> 19) & 31) << 10 | ((c >> 11) & 31) << 5 | ((c >> 3) & 31))); o += 2;
        }
    gx_mark_dirty(SM_SBTEX, SB_W * SB_H * 2); SB.inval = 1;
    const char *dump = getenv("SMB3_STAGE_BAR");                        /* (testing: the bar as drawn, a PPM) */
    if (dump) { FILE *f = fopen(dump, "wb");
        if (f) { fprintf(f, "P6 %d %d 255\n", SB_W, SB_H); for (int i = 0; i < SB_W * SB_H; i++) { uint8_t c[3] = {(uint8_t)(SB.px[i] >> 16), (uint8_t)(SB.px[i] >> 8), (uint8_t)SB.px[i]}; fwrite(c, 1, 3, f); } fclose(f); } }
}
/* StatusBar_UpdateValues: the power meter, coins, lives, score and time as SMB3 writes them */
static void sb_update(void) {
    uint8_t t[6 * 32]; memcpy(t, SB.nt, sizeof t);
    #define T(row, col) t[((row) - 24) * 32 + (col)]
    int n = sb_first_player();
    /* StatusBar_Fill_PowerMT: 6 arrows ($EF dark, $EE lit by Player_Power's bits 0-5), then [P]:
       $3C $3D, or with bit 6 set MaxPower_Tick-- and $2C $2D while its bit 3 is clear */
    int power = pm[n].power;
    for (int i = 0; i < 6; i++) T(25, 8 + i) = (power >> i) & 1 ? 0xEE : 0xEF;
    uint8_t pt = 0x3C;
    if (power & 0x40) { SB.ptick--; if (!(SB.ptick & 8)) pt = 0x2C; }
    T(25, 14) = pt; T(25, 15) = (uint8_t)(pt + 1);
    /* StatusBar_Fill_Coins: two digits ($F0 + d), a blank ($FE) for the leading zero */
    int coins = SG.coins % 100;
    T(25, 18) = coins >= 10 ? (uint8_t)(0xF0 + coins / 10) : 0xFE; T(25, 19) = (uint8_t)(0xF0 + coins % 10);
    /* StatusBar_Fill_Lives: capped at 99, a blank leading zero */
    int lives = (int)R32(MOD_PY_REST + 4 * (uint32_t)n); if (lives > 99) lives = 99;
    if (lives < 0) { T(26, 5) = 0xFE; T(26, 6) = 0xFE; }
    else { T(26, 5) = lives >= 10 ? (uint8_t)(0xF0 + lives / 10) : 0xFE; T(26, 6) = (uint8_t)(0xF0 + lives % 10); }
    /* StatusBar_Fill_Score: 6 digits of the score in tens (then the bar's fixed 0) */
    uint32_t sc = SG.score > 999999 ? 999999 : SG.score;
    for (int i = 5; i >= 0; i--) { T(26, 8 + i) = (uint8_t)(0xF0 + sc % 10); sc /= 10; }
    /* StatusBar_Fill_Time: 3 digits */
    /* StatusBar_Update_Cards: each card 2 x 2 (CardUL / UR / LL / LR by kind) at columns 22, 25, 28 */
    static const uint8_t CUL[4] = {0xFE, 0xE0, 0xE4, 0xAC}, CUR[4] = {0xFE, 0xE1, 0xE6, 0xAD}, CLL[4] = {0xFE, 0xE2, 0xE7, 0xAE}, CLR[4] = {0xFE, 0xE3, 0xE8, 0xAF};
    for (int k = 0; k < 3; k++) { int c = SG.cards[k] & 3; T(25, 22 + 3 * k) = CUL[c]; T(25, 23 + 3 * k) = CUR[c]; T(26, 22 + 3 * k) = CLL[c]; T(26, 23 + 3 * k) = CLR[c]; }
    int tm = SB.time; T(26, 17) = (uint8_t)(0xF0 + tm / 100); T(26, 18) = (uint8_t)(0xF0 + tm / 10 % 10); T(26, 19) = (uint8_t)(0xF0 + tm % 10);
    #undef T
    int inv = th_bar_inventory(t, SB.nt);                                /* (a Toad House's item: the inventory open, Inventory_Open) */
    static int inv_was;
    if (inv != inv_was) { inv_was = inv; SB.pal[3] = inv ? 0x36 : SB.pal3; memset(SB.shown, 0xFF, sizeof SB.shown); }   /* (Inv_OpenPal_Changes: colour 3 salmon) */
    if (memcmp(t, SB.shown, sizeof t)) { memcpy(SB.shown, t, sizeof t); sb_render(); }
}
static void sb_draw(ppc_context *ctx, uint8_t *base) {
    if (map_on()) return;                                                /* (the map: SMB3's own bar is in its picture) */
    if (smb3_stage_on() && !probe) poof_frame();
    if (!SB.ok || !smb3_stage_on() || probe || !L.placed) return;
    sb_update();
    uint32_t bg = R32(BG_PARAM_P);
    uint32_t cam = gcall(ctx, base, A_GET_CAMERA_BY_ID, 1, gcall(ctx, base, A_GET_CUR_CAMERA, 0));
    if (!cam || !bg) return;
    W32(SM_CAMERA, cam); gcall(ctx, base, A_GET_CAMERA_MTX, 2, SM_CAMERA, SM_MTX);
    if (!tex_ready) tex_upload();
    gx_setup(ctx, base);
    if (SB.inval) { gcall(ctx, base, A_GXInvalidateTexAll, 0); SB.inval = 0; }
    gcall(ctx, base, A_GXInitTexObj, 8, SM_SBOBJ, SM_SBTEX, SB_W, SB_H, 5, 0, 0, 0);
    ctx->f[1].d = 0.0; ctx->f[2].d = 0.0; ctx->f[3].d = 0.0;
    gcall(ctx, base, A_GXInitTexObjLOD, 8, SM_SBOBJ, 0, 0, 0, 0, 0, 0, 0);
    gcall(ctx, base, A_GXLoadTexObj, 2, SM_SBOBJ, 0);
    gcall(ctx, base, A_GXSetZMode, 3, 0, 3, 0);                     /* (over everything) */
    /* at the screen's bottom, 48 / 240 of its height as in SMB3; black (column 0's) out to the sides */
    float x0 = RF(bg + 56), y0 = RF(bg + 60), w = RF(bg + 64), h = RF(bg + 68);
    float sc = h / 240.0f, bh = SB_H * sc, bw = SB_W * sc, yb = y0 - h, bx = x0 + (w - bw) * 0.5f;
    float bu = 2.0f / SB_W, bv = 2.0f / SB_H;
    gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 8);
    float ytop = yb + bh, lbot = -(L.ly + LH * 16); if (lbot > ytop) ytop = lbot;   /* (up to the level's bottom: SMB3's black below its last row) */
    quad(x0 - 8, ytop, x0 + w + 8, yb - 8, pz, bu, bv, bu, bv);
    quad(bx, yb + bh, bx + bw, yb, pz, 0, 0, 1, 1);
    goal_msg_draw(ctx, base, bx, y0, sc);
    th_bar_draw(ctx, base, bx, y0, sc);
    gcall(ctx, base, A_G3D_INVALIDATE, 1, 0x7FF);
}
/* the stage's frame for the bar (from the players' execute, so it stops with the game) */
static void sb_frame(void) {
    static uint64_t last; extern uint64_t g_frames_presented;
    if (last == g_frames_presented || !L.placed || objs_exec_frame != g_frames_presented) return;
    last = g_frames_presented; sb_timer();
    /* NSMBW's own timer (dStageTimer_c +4, 4096 a second) kept at SMB3's: its hurry-up at 100 and
       its time-up (checkTimeOut: setTimeOverDemo) come at SMB3's moments */
    uint32_t tm = R32(0x8042A070u);
    if (tm) W32(tm + 4, (uint32_t)((goal.phase || goal.hold || TH.on || BT.clock_stop ? 999 : SB.time) * 4096));   /* (a Toad House: Level_TimerEn off) */   /* (the goal taken: Level_TimerEn stops the clock - the bonus counting it down is no time-up) */
}

/* ---- the vertical scroll (prg008 Player_DoScrolling, a level that isn't freely scrolling): the
   screen stays at its lowest (Vert_Scroll $EF: the level's last row just above the bar) unless
   the Player flies (Player_FlyTime); once up, it follows: the Player's top less than $30 below
   the screen's top - up, at most 3 a frame; $58 or more - down, to the lowest again. NSMBW's own
   camera keeps the horizontal; this replaces its height after it runs (rt_menu.c's
   hle_fn_80154F60, dBg_c's camera execute). The playfield is the screen less the bar, so the
   lowest is the level's bottom less that. ---- */
static float vs_top; static int vs_on;
void smb3_stage_camera(void) {
    if (smb3_stage_on() && map_on()) { vs_on = 0; map_camera(); return; }
    if (!smb3_stage_on() || probe || !L.placed) { vs_on = 0; return; }
    uint32_t bp = R32(BG_PARAM_P), bg = R32(0x80429DD0u);           /* dBgParameter_c, dBg_c */
    if (!bp || !bg) return;
    float h = RF(bp + 68); if (h < 100 || h > 1000) return;
    if (TH.on) {                                                         /* (a Toad House: SMB3's one screen of it, as SMB3 shows it - NSMBW's camera neither zooms out nor moves) */
        float bw = RF(bp + 0x70), bh = RF(bp + 0x74);                   /* (dBgParameter_c: the unzoomed screen; +0x40 / +0x44 this frame's - dBg_c +0x8FE78.. its targets) */
        if (bw > 100 && bh > 100) {
            W32(bp + 0x40, fbits(bw)); W32(bp + 0x44, fbits(bh));
            for (uint32_t o = 0x8FE78; o < 0x8FE88; o += 8) { W32(bg + o, fbits(bw)); W32(bg + o + 4, fbits(bh)); }
            h = bh;
        }
    }
    float play = h - SB_H * h / 240.0f, lowest = LH * 16 - play;
    int n = sb_first_player();
    if (!vs_on || vs_top > lowest) { vs_on = 1; vs_top = lowest; }   /* (the lowest moves with the zoom) */
    if (pp[n].on) {
        int flying = pm[n].fly != 0;
        if (!(vs_top >= lowest && !flying)) {
            float d = (float)pp[n].y - vs_top;
            if (d < 0x30) { float st = d - 0x30; if (st < -3) st = -3; vs_top += st; if (vs_top < 0) vs_top = 0; }
            else if (d >= 0x58) { vs_top += d - 0x58; }
            if (vs_top > lowest) vs_top = lowest;
        }
    }
    {   /* SMB3's horizontal scroll never shows past the level's ends (Horz_Scroll 0 .. Level_Width) */
        float w = RF(bp + 64), x = RF(bp + 56), lo = L.lx, hi = L.lx + L.w * 16 - w;
        float nx = x < lo ? lo : x > hi ? hi : x;
        if (TH.on) { nx = L.lx + 128 - w * 0.5f; lo = nx - 1; hi = nx + 1; }   /* (a Toad House: its one screen centred, still) */
        if (hi > lo && nx != x) { W32(bp + 0x38, fbits(nx)); W32(bp + 0x60, fbits(nx)); W32(bg + 0x900AC, fbits(nx)); W32(bp + 0x48, fbits(nx + w * 0.5f)); W32(bp + 0x50, fbits(nx + w * 0.5f)); }
    }
    float top = -(L.ly + vs_top);                                        /* (NSMBW: y up) */
    W32(bp + 0x3C, fbits(top)); W32(bp + 0x64, fbits(top)); W32(bg + 0x900B0, fbits(top));
    W32(bp + 0x4C, fbits(top - h * 0.5f)); W32(bp + 0x54, fbits(top - h * 0.5f));
    if (getenv("SMB3_STAGE_CAMLOG")) { extern uint64_t g_frames_presented; if (g_frames_presented % 30 == 0) rt_log("smb3", "vscroll: top %.1f (level %.1f, lowest %.1f) player y %d fly %d screen %.1f x %.1f", top, vs_top, lowest, pp[n].y, pm[n].fly, RF(bp + 64), h); }
}
static void native_dtor(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }
static void native_draw_opa(ppc_context *ctx, uint8_t *base) { proc_draw(ctx, base); }
static void native_draw_xlu(ppc_context *ctx, uint8_t *base) { sb_draw(ctx, base); }

/* from dAcPy_c::draw (rt_retro.c), each player each frame: the level is placed at player 1's
   first appearance; the draw proc is entered once a frame */
/* the level's draw proc, entered once a frame: from a player's draw, or - with no player drawn
   (a death, a bubble, the course's end) - from the status bar's draw (gm_d_gamedisplay.c), so the
   SMB3 level never drops out to the NSMBW course under it */
static void proc_enter(ppc_context *ctx, uint8_t *base) {
    extern uint64_t g_frames_presented; static uint64_t entered = ~0ull;
    if (entered == g_frames_presented) return;
    static int init;
    if (!init) {
        init = 1;
        rt_register_native(N_SM_DTOR, native_dtor); rt_register_native(N_SM_DRAW_OPA, native_draw_opa); rt_register_native(N_SM_DRAW_XLU, native_draw_xlu);
        const uint32_t vt[8] = {0, 0, N_SM_DTOR, A_LEAF_GETTYPE, A_LEAF_FREE, A_LEAF_ENTRY, N_SM_DRAW_OPA, N_SM_DRAW_XLU};
        for (int i = 0; i < 8; i++) W32(SM_VTABLE + i * 4, vt[i]);
    }
    static uint32_t proc_scene;
    if (proc_scene != R32(BG_GM)) {                                    /* (a new stage: a new proc) */
        W32(SM_PROC, SM_VTABLE); W32(SM_PROC + 4, 0);
        if (!gcall(ctx, base, A_PROC_SETUP, 3, SM_PROC, 0, 0)) { rt_log("smb3", "stage: draw proc setup failed"); return; }
        proc_scene = R32(BG_GM);
    }
    entered = g_frames_presented;
    gcall(ctx, base, A_LEAF_ENTRY, 1, SM_PROC);
}
void smb3_stage_draw_any(ppc_context *ctx, uint8_t *base) {
    if (restart_wait && music_death_left() <= 0 && R16(G_NOW_SCENE) == 5) { restart_wait = 0; smb3_stage_restart(ctx, base); }
    if (getenv("SMB3_STAGE_DRAWLOG")) { extern uint64_t g_frames_presented; rt_log("smb3", "drawlog f%llu gamedisplay scene %d mode %d placed %d", (unsigned long long)g_frames_presented, R16(G_NOW_SCENE), (int)R32(G_GAME_MODE), L.placed); }
    if (smb3_stage_on() && L.placed && !probe) proc_enter(ctx, base);
}
/* (rt_retro.c, after dAcPy_c::draw: the model's joints are this frame's now - a held shell to the hands) */
void smb3_stage_player_drawn(ppc_context *ctx, uint8_t *base, uint32_t pl) {
    if (smb3_stage_on() && L.placed && !probe && !map_on()) objs_carry_pos(ctx, base, pl);
}
void smb3_stage_player_draw(ppc_context *ctx, uint8_t *base, uint32_t pl) {
    if (getenv("SMB3_STAGE_DRAWLOG")) { extern uint64_t g_frames_presented; static uint64_t lf; if (g_frames_presented != lf) { lf = g_frames_presented;
        rt_log("smb3", "drawlog f%llu scene %d mode %d active %d placed %d", (unsigned long long)g_frames_presented, R16(G_NOW_SCENE), (int)R32(G_GAME_MODE), active, L.placed); } }
    if (!smb3_stage_on()) return;
    {   /* (a restart from inside the stage: the old one's players are drawn till its scene ends;
           the new stage's come after the course intro - a gap of frames without players) */
        extern uint64_t g_frames_presented; static uint64_t last_pl;
        if (g_frames_presented - last_pl > 30) { await_scene = 0; reload_now(); }   /* (a new stage's players: what it shows made ready for them, if a restart left it to now) */
        last_pl = g_frames_presented;
    }
    if (map_on()) {                                                      /* SMB3's map (smb3_map.inc) */
        extern uint64_t g_frames_presented; static uint64_t lastm;
        if (lastm != g_frames_presented) { lastm = g_frames_presented; pz = RF(pl + PL_POS + 8);
            if (!L.placed && !await_scene) map_place(RF(pl + PL_POS), RF(pl + PL_POS + 4)); }
        proc_enter(ctx, base);
        return;
    }
    {   extern uint64_t g_frames_presented; int ran = objs_exec_frame == g_frames_presented;   /* (paused or halted: SMB3's rules wait) */
        if (L.placed && !probe) { blk_ctx = ctx; blk_base = base; if (ran) player_blocks(pl); raccoon_anchor(ctx, base, pl); frog_anchor(ctx, base, pl); } }
    if (getenv("SMB3_STAGE_TEST_NSMBW_TILE") && L.placed && (int8_t)R8(pl + PL_PLR_NO) == 0) {   /* (testing: those cells' tiles now, on a change) */
        const char *e = getenv("SMB3_STAGE_TEST_NSMBW_TILE"); static uint16_t lastv[8]; int i = 0;
        for (int c, r, t, k; e && i < 8 && sscanf(e, "%d,%d,%x%n", &c, &r, &t, &k) == 3; e += k + (e[k] == ';'), i++) {
            uint32_t x = (uint32_t)(int)(L.lx + c * 16) & 0xFFF0, y = (uint32_t)(int)(L.ly + r * 16) & 0xFFF0;
            uint32_t p = gcall(ctx, base, 0x80077520u, 6, R32(BG_GM), x, y, 0, 0, 0);
            uint16_t v = p ? R16(p) : 0xFFFF;
            if (v != lastv[i]) { rt_log("smb3", "test: NSMBW tile at col %d row %d is now %04X", c, r, v); lastv[i] = v; }
        } }
    if (getenv("SMB3_STAGE_SPEEDDATA") && L.placed) {                  /* (testing: the player's speed tables) */
        static int once[8]; int n = (int8_t)R8(pl + PL_PLR_NO);
        if (n >= 0 && n < 8 && ++once[n] == 90) {
            uint32_t sd = R32(pl + atoi(getenv("SMB3_STAGE_SPEEDDATA")));
            char b[1200]; int o = 0; for (int i = 0; i < 60; i++) o += snprintf(b + o, sizeof b - o, "%.3g ", RF(sd + 4 * (uint32_t)i));
            rt_log("smb3", "speed data at %08X: %s", sd, b);
        }
    }
    if (getenv("SMB3_STAGE_TEST_CLEAR") && L.placed && (int8_t)R8(pl + PL_PLR_NO) == 0) {   /* (testing: the level counted cleared after that many frames, as the card's exit) */
        static int cnt; if (++cnt == atoi(getenv("SMB3_STAGE_TEST_CLEAR"))) {
            SG.cards[0] = 1; for (int i = 0; i < 8; i++) kept_rest[i] = (int)R32(MOD_PY_REST + 4 * (uint32_t)i);
            keep_rest = 1; rt_log("smb3", "test: the level cleared"); if (map_level_end(ctx, base, 0)) return; } }
    if (getenv("SMB3_STAGE_TEST_BIG") && L.placed) {                   /* (testing: Super a second in, as if from a mushroom) */
        static int cnt[8]; int n = (int8_t)R8(pl + PL_PLR_NO);
        if (n >= 0 && n < 8 && ++cnt[n] == (getenv("SMB3_STAGE_TEST_BIG_AT") ? atoi(getenv("SMB3_STAGE_TEST_BIG_AT")) : 60)) gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, atoi(getenv("SMB3_STAGE_TEST_BIG")));
    }
    if (getenv("SMB3_STAGE_TEST_RANIM") && L.placed && (int8_t)R8(pl + PL_PLR_NO) == 0 && rc[0].mdl) {   /* (testing: "k,k,..." the Raccoon animations, a second each) */
        static int cnt, last = -1; extern uint64_t g_frames_presented;
        int w = (++cnt - 30) / 60, id = -1, k = 0;
        for (const char *e = getenv("SMB3_STAGE_TEST_RANIM"); *e; k++) { int v = atoi(e); if (k == w) id = v; while (*e && *e != ',') e++; if (*e) e++; }
        if (cnt >= 30 && w != last) {
            last = w;
            if (id >= 0 && id < NRA) { ra_start(ctx, base, 0, id, 1.0f, 0.0f, 1); rt_log("smb3", "Raccoon anim %s at frame %llu (model anim %d)", RA_NAME[id], (unsigned long long)g_frames_presented, (int)R32(rc[0].mdl + 340)); }
            else rc[0].hold = -1;
        }
    }
    if (getenv("SMB3_STAGE_TEST_ANIM") && L.placed && (int8_t)R8(pl + PL_PLR_NO) == 0) {   /* (testing: "id,id,..." plays each NSMBW animation for a second) */
        static int cnt, last = -1; extern uint64_t g_frames_presented;
        int w = (++cnt - 60) / 60, id = -1, k = 0;
        for (const char *e = getenv("SMB3_STAGE_TEST_ANIM"); *e; k++) { int v = atoi(e); if (k == w) id = v; while (*e && *e != ',') e++; if (*e) e++; }
        if (cnt >= 60 && id >= 0 && w != last) {
            last = w; uint32_t mdl = R32(R32(pl + 3560) + 4);
            ctx->f[1].d = ctx->ps1[1] = 1.0; ctx->f[2].d = ctx->ps1[2] = 0.0; ctx->f[3].d = ctx->ps1[3] = 0.0;
            gcall(ctx, base, R32(R32(mdl) + 92), 2, mdl, (uint32_t)id);
            rt_log("smb3", "anim preview: %d at frame %llu", id, (unsigned long long)g_frames_presented);
        }
    }
    if (getenv("SMB3_STAGE_JOINTS") && L.placed) {                     /* (testing: the model's joints, relative to the player) */
        static int shown[8]; int n = (int8_t)R8(pl + PL_PLR_NO);
        if (n >= 0 && n < 8 && (++shown[n] % 90 == 0 && shown[n] <= 720)) {
            uint32_t mdl = R32(R32(pl + 3560) + 4), fn = R32(R32(mdl) + 80);
            rt_log("smb3", "joints: player %d model %08X getJointMtx %08X pos %.1f %.1f %.1f", n + 1, mdl, fn, RF(pl + PL_POS), RF(pl + PL_POS + 4), RF(pl + PL_POS + 8));
            {   uint32_t f84 = R32(R32(mdl) + 84); gcall(ctx, base, f84, 2, mdl, SM_JMTX);
                float m[12]; for (int k = 0; k < 12; k++) m[k] = RF(SM_JMTX + 4 * k);
                rt_log("smb3", "  head-top (vt 84 %08X): at %+6.1f %+6.1f %+6.1f | x %+.2f %+.2f %+.2f | y %+.2f %+.2f %+.2f | z %+.2f %+.2f %+.2f", f84,
                       m[3] - RF(pl + PL_POS), m[7] - RF(pl + PL_POS + 4), m[11] - RF(pl + PL_POS + 8), m[0], m[4], m[8], m[1], m[5], m[9], m[2], m[6], m[10]); }
            for (int j = 0; j < 17; j++) {
                for (int k = 0; k < 12; k++) W32(SM_JMTX + 4 * k, 0);
                gcall(ctx, base, fn, 3, mdl, SM_JMTX, j);
                float m[12]; for (int k = 0; k < 12; k++) m[k] = RF(SM_JMTX + 4 * k);
                rt_log("smb3", "  joint %2d: at %+6.1f %+6.1f %+6.1f | x %+.2f %+.2f %+.2f | y %+.2f %+.2f %+.2f | z %+.2f %+.2f %+.2f", j,
                       m[3] - RF(pl + PL_POS), m[7] - RF(pl + PL_POS + 4), m[11] - RF(pl + PL_POS + 8), m[0], m[4], m[8], m[1], m[5], m[9], m[2], m[6], m[10]);
            }
        }
    }
    {   /* each player, the first time it's drawn on the placed level: up onto it (SB_LIFT) */
        int n = (int8_t)R8(pl + PL_PLR_NO);
        if (L.placed && n >= 0 && n < 8 && !lifted[n]) { lifted[n] = 1; WF(pl + PL_POS + 4, RF(pl + PL_POS + 4) + SB_LIFT - L.dy); }   /* (- dy: on their ground, not above it - the grid's offset) */
    }
    if (getenv("SMB3_STAGE_CAMLOG") && L.placed && (int8_t)R8(pl + PL_PLR_NO) == 0) {   /* (testing: the screen against the level) */
        static int k; uint32_t bg = R32(BG_PARAM_P);
        if (bg && (k++ % 60) == 0) rt_log("smb3", "cam: screen top %.1f bottom %.1f (h %.1f) | player y %.1f | SMB3 ground top %.1f", RF(bg + 60), RF(bg + 60) - RF(bg + 68), RF(bg + 68), RF(pl + PL_POS + 4), -(L.ly + 26 * 16));
    }
    static uint64_t last; extern uint64_t g_frames_presented;
    if (last == g_frames_presented) return;
    last = g_frames_presented;
    blk_ctx = ctx; blk_base = base;                                      /* (the objects call the game: the platforms' lines) */
    music_sync(ctx, base);                                               /* (SMB3's sound: NSMBW's streams as it has them) */
    blocks_frame();
    {   int n = (int8_t)R8(pl + PL_PLR_NO); if (!pipe_hidden(n)) pz = RF(pl + PL_POS + 8); }   /* (one going into a pipe: its depth NSMBW's demo's) */
    if (!L.placed && !await_scene) {
        float px = RF(pl + PL_POS), py = RF(pl + PL_POS + 4);
        /* SMB3's start: its player's column, and the first thing to stand on at or below it
           (1-1's ground at column 2; 1-4 starts on a ledge high up) - SMB3_STAGE_TEST_X=column:
           elsewhere, testing */
        int col = (L.sx + 8) / 16; if (col < 0 || col >= L.w) col = 2;
        { const char *e = getenv("SMB3_STAGE_TEST_X"); static int used; if (e && atoi(e) > 0 && atoi(e) < L.w && !(getenv("SMB3_STAGE_TEST_X_ONCE") && used++)) col = atoi(e); }   /* (_ONCE: the first level only) */
        {   const char *e = getenv("SMB3_STAGE_TEST_TILES");             /* (testing: "col,row,tile;..." changes the level) */
            for (int c, r, t, k; e && sscanf(e, "%d,%d,%x%n", &c, &r, &t, &k) == 3; e += k + (e[k] == ';'))
                if (c >= 0 && c < L.w && r >= 0 && r < LH) { L.tile[r * L.w + c] = (uint8_t)t; nes_wram_ptr()[(c / 16) * 0x1B0 + r * 16 + c % 16] = (uint8_t)t; } }   /* (SMB3's Tile_Mem too) */
        int g = (L.sy + 8) / 16; if (g < 0) g = 0;                       /* its ground: the first tile below the player's own row */
        while (g < LH && tile_class(L.tile[g * L.w + col]) == 0) g++;
        if (g >= LH || getenv("SMB3_STAGE_TEST_X")) { g = LH - 1; while (g > 0 && tile_class(L.tile[(g - 1) * L.w + col]) != 0) g--; }   /* (none: the column's floor, from the bottom) */
        if (getenv("SMB3_STAGE_TEST_ROW") && getenv("SMB3_STAGE_TEST_X")) g = atoi(getenv("SMB3_STAGE_TEST_ROW"));   /* (testing: standing on that row) */
        L.lx = px - (col * 16 + 8); L.ly = -py - g * 16 - SB_LIFT;
        /* on NSMBW's 16-unit grid: its collision takes a solid unit's top (and sides) from its own
           cells, so an SMB3 tile off the grid had its floor 6 units from where NSMBW stood the
           players - pushed up out of it, then falling back onto it, a few units each frame (on
           every level; worst on the one-way floors of 1-2 / 1-4). The level up to 15 units lower,
           so the players start above their ground, not in it; across to the nearest */
        {   float raw = L.ly; L.lx = floorf(L.lx / 16.0f + 0.5f) * 16.0f; L.ly = ceilf(L.ly / 16.0f) * 16.0f; L.dy = L.ly - raw; }
        if (getenv("SMB3_STAGE_TEST_X") && getenv("SMB3_STAGE_TEST_XOFF") && col == atoi(getenv("SMB3_STAGE_TEST_X"))) WF(pl + PL_POS, px + (float)atoi(getenv("SMB3_STAGE_TEST_XOFF")));   /* (testing: that much further in the column) */
        L.placed = 1; music_level_placed(); pipe_exit_placed();
        { static int done; if (getenv("SMB3_TEST_PSWITCH") && !done++) { pswitch_swap(1); PS.cnt = 0x80; rt_log("smb3", "test: the P-switch on"); } }   /* (testing: a P-switch running from the start) */
        if (keep_rest) { keep_rest = 0; for (int i = 0; i < 8; i++) W32(MOD_PY_REST + 4 * (uint32_t)i, (uint32_t)kept_rest[i]); }   /* (lifted: the status bar under it) */
        rt_log("smb3", "stage: player 1 at (%.1f, %.1f, %.1f): the SMB3 level placed at (%.1f, %.1f): start column %d, ground row %d (SMB3's start %d, %d)", px, py, pz, L.lx, L.ly, col, g, L.sx, L.sy);
        if (getenv("SMB3_STAGE_SOLIDLOG")) { char b[900]; int k = 0;   /* (testing: walls - columns whose tile above the ground is solid) */
            for (int c = 0; c < L.w && k < 880; c++) for (int r = 1; r < LH; r++) if (tile_class(L.tile[r * L.w + c]) == 2 && tile_class(L.tile[(r - 1) * L.w + c]) != 2 && r < LH - 2) { k += snprintf(b + k, sizeof b - k, " %d:%d", c, r); break; }
            rt_log("smb3", "solid tops (column:row):%s", b); }
        if (getenv("SMB3_STAGE_SOLIDLOG")) { char b[900]; int k = 0;
            for (int c = 0; c < L.w && k < 880; c++) for (int r = 0; r < LH; r++) if (is_note(L.tile[r * L.w + c])) k += snprintf(b + k, sizeof b - k, " %d:%d=%02X", c, r, L.tile[r * L.w + c]);
            rt_log("smb3", "note blocks (column:row):%s", b); }
        if (probe) probe_tiles(ctx, base); else empty_course();
        {   const char *e = getenv("SMB3_STAGE_TEST_NSMBW_TILE");     /* (testing: "col,row,hex;...": an NSMBW tile of its own at an SMB3 cell) */
            for (int c, r, t, k; e && sscanf(e, "%d,%d,%x%n", &c, &r, &t, &k) == 3; e += k + (e[k] == ';')) {
                uint32_t x = (uint32_t)(int)(L.lx + c * 16) & 0xFFF0, y = (uint32_t)(int)(L.ly + r * 16) & 0xFFF0;
                gcall(ctx, base, 0x80077860u, 5, R32(BG_GM), x, y, 0, (uint32_t)t);
                rt_log("smb3", "test: NSMBW tile %04X at col %d row %d (%u, %u)", t, c, r, x, y);
            } }
    }
    proc_enter(ctx, base);
}

/* from dAcPy_c::executeMain (rt_retro.c): a player ran this frame */
void smb3_stage_player_exec(uint32_t pl) {
    extern uint64_t g_frames_presented;
    if (smb3_stage_on()) objs_exec_frame = g_frames_presented;
    if (smb3_stage_on() && !map_on() && L.placed) { int n = (int8_t)R8(pl + PL_PLR_NO); if (n >= 0 && n < 8) pipe_player_exec(pl, n); }
    if (smb3_stage_on() && !map_on() && th_halted()) { W16(pl + PL_KEY + 4, 0); W16(pl + PL_KEY + 6, 0); }   /* (a Toad House: Player_HaltTick - no buttons yet) */
    if (smb3_stage_on() && !map_on() && note_bouncing((int8_t)R8(pl + PL_PLR_NO))) {   /* (on a note block's bounce: no jump of NSMBW's own - its press makes the high launch) */
        int n = (int8_t)R8(pl + PL_PLR_NO); uint16_t k = R16(pl + PL_KEY + 4), kt = R16(pl + PL_KEY + 6);
        if (kt & 0x0900) nb[n].big = 1;
        W16(pl + PL_KEY + 4, k & ~0x0900); W16(pl + PL_KEY + 6, kt & ~0x0900); }
}

/* (rt_retro.c's dAcPy_c::draw: 1 - its model isn't drawn this frame, the poof hides it) */
int smb3_stage_player_hidden(uint32_t pl) {
    if (!smb3_stage_on()) return 0;
    if (map_on() && map_special()) return 1;                             /* (SMB3's own Mario plays its Toad House / bonus screen) */
    int n = (int8_t)R8(pl + PL_PLR_NO);
    return n >= 0 && n < 8 && poof.on[n];
}
/* (rt_retro.c, dAcPy_c::executeMain: 1 = done here, NSMBW's own not run) - on SMB3's map the
   players walk it (smb3_map.inc), not NSMBW's course */
int smb3_map_player_exec(ppc_context *ctx, uint8_t *base, uint32_t pl) {
    if (!smb3_stage_on() || !map_on()) return 0;
    if (L.placed) map_player(ctx, base, pl);
    return 1;
}
#include "smb3_map.inc"
#include "smb3_stage_music.inc"
#include "smb3_stage_pipes.inc"
