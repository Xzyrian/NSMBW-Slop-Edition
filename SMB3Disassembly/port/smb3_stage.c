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
#define A_UNIT_FLAGS    0x800774A0u              /* dBgGm_c: a tile number's flags (r3:r4) */
#define A_START_GAME    0x800BB780u              /* dInfo_c::startGame(StartGameInfo_s &) */
#define G_DINFO         (0x80430000u - 24708)    /* dInfo_c::m_instance */
#define PL_POS          0x0AC
/* the players a level starts with (as the world map's startGame sets them: gm_d_wm_player.c) */
#define WP_ENTRY_TABLE  (0x81860000u - 6000)     /* u32 x 8: in the level */
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
#define SM_TEX          (SM_MEM + 0x1000)        /* 256 x up to 448 RGB5A3: up to 224 KB */
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
} L RT_LOCAL;
/* the texture: 256 wide; tile t at ((t % 16) * 16, (t / 16) * 16); below the 256 tiles, slots of
   16 x 16 (slot s at ((s % 16) * 16, (s / 16) * 16), s >= 256): the animated tiles' other frames,
   then the item sprites. 0xAARRGGBB, alpha 0 = transparent. */
#define TEX_H_MAX 448
static uint32_t atlas[256 * TEX_H_MAX] RT_LOCAL;
static int tex_h;                                /* rows in use */
static int16_t anim_slot[256];                  /* first of a tile's 3 other frames, or -1 */
enum { SPR_MUSHROOM, SPR_1UP, SPR_STAR, SPR_FLOWER, SPR_LEAF, NSPR };
static int spr_slot0;                           /* slot of SPR_MUSHROOM */
/* single 8 x 16 sprites, two to a slot: the coin out of a block (CoinPUp_Patterns, palette 3),
   brick debris (BrickBust: $4B, palette 3), the score digits (Score_PatternLeft/Right, palette 1) */
enum { H_COIN0, H_COIN1, H_COIN2, H_COIN3, H_DEBRIS, H_S59, H_S5B, H_S61, H_S63, H_S69, H_S6B, H_S6D, H_S6F, NHALF };
static const uint8_t half_pat[NHALF] = {0x49, 0x4F, 0x4D, 0x4F, 0x4B, 0x59, 0x5B, 0x61, 0x63, 0x69, 0x6B, 0x6D, 0x6F};
static const uint8_t half_pal[NHALF] = {3, 3, 3, 3, 3, 1, 1, 1, 1, 1, 1, 1, 1};
static int half_slot0;
static int active, probe, tex_ready;

static int tile_class(uint8_t t) {               /* 2 solid, 1 solid on top, 0 nothing */
    int q = t >> 6;
    if (t >= L.attr[q + 4]) return 2;
    if (t >= L.attr[q]) return 1;
    return 0;
}
/* the recompiled SMB3, run unseen from a new game into 1-1 (the same buttons as its test: right,
   up onto 1-1's square, A) */
static int level_load(void) {
    if (L.ok) return 1;
    if (!nes_load(smb3_rom, smb3_rom_size)) return 0;
    smb3_start_at_map = 1; smb3_load_from = NULL;
    nes_reset();
    for (int i = 0; i < 760; i++) {                                     /* (frame 760: 1-1 on screen, its pattern banks in) */
        uint8_t b = (i >= 250 && i < 270) ? NES_RIGHT : (i >= 330 && i < 350) ? NES_UP : (i >= 420 && i < 430) ? NES_A : 0;
        nes_set_buttons(0, b); nes_run_frame();
        if (nes_error()) { rt_log("smb3", "stage: SMB3 stopped while loading 1-1: %s", nes_error()); return 0; }
    }
    const uint8_t *ram = nes_ram_ptr(), *wram = nes_wram_ptr();
    if (ram[0x70A] != 1) { rt_log("smb3", "stage: not in 1-1 (tileset %d)", ram[0x70A]); return 0; }
    int screens = ram[0x22] + 1; if (screens > 15) screens = 15;
    L.w = screens * 16;
    for (int s = 0; s < screens; s++) for (int r = 0; r < LH; r++) for (int c = 0; c < 16; c++)
        L.tile[r * L.w + s * 16 + c] = wram[s * 0x1B0 + r * 16 + c];
    memcpy(L.attr, wram + 0x1E94, 8);                                    /* Tile_AttrTable ($7E94) */
    /* the tile pictures: Tile_Layout_TS1 (bank 15 at $A000): upper left, lower left, upper right,
       lower right; the background's patterns as the level has them: PatTable_BankSel ($0719: 2 KB
       banks for $0000 and $0800) - not the PPU's banks now, which at vblank are the status bar's
       (its IRQ swaps them in for the bottom of the screen). The $0800 bank animates: PT2_Anim
       ($60 $62 $64 $66, 8 frames each) - frames 1-3 kept for the tiles they change. */
    const uint8_t *lay = smb3_rom + 16 + 15 * 0x2000;
    const uint8_t *chr = smb3_rom + 16 + smb3_rom[4] * 0x4000u;
    uint32_t nchr = smb3_rom[5] * 8u;                                    /* 1 KB banks */
    uint8_t sel0 = ram[0x719];
    static const uint8_t anim_banks[4] = {0x60, 0x62, 0x64, 0x66};
    static uint32_t frame[4][256 * 256];
    static const int ox[4] = {0, 0, 8, 8}, oy[4] = {0, 8, 0, 8};
    for (int fr = 0; fr < 4; fr++) {
        uint8_t sel1 = anim_banks[fr];
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
                        frame[fr][((t / 16) * 16 + oy[k] + y) * 256 + (t % 16) * 16 + ox[k] + x] = ppu_rgb(ppu_peek_pal(p ? q * 4 + p : 0));
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
        if (!differs || slot + 3 > (TEX_H_MAX / 16) * 16 - 16) continue;
        anim_slot[t] = (int16_t)slot; nanim++;
        for (int fr = 1; fr < 4; fr++, slot++)
            for (int y = 0; y < 16; y++) memcpy(&atlas[((slot / 16) * 16 + y) * 256 + (slot % 16) * 16], &frame[fr][((t / 16) * 16 + y) * 256 + (t % 16) * 16], 64);
    }
    /* the item sprites (8 x 16 sprite patterns, ObjectGroup00_PatternSets / _Attributes): from the
       sprite banks PatTable_BankSel+2..5 ($1000-$1FFF) and the sprite palettes; a pair of the same
       pattern is drawn mirrored on the right */
    slot = (slot + 15) / 16 * 16; spr_slot0 = slot;
    static const uint8_t spr_pat[NSPR][2] = {{0x51, 0x51}, {0x51, 0x51}, {0x55, 0x55}, {0x53, 0x53}, {0x5D, 0x5F}};
    static const uint8_t spr_pal[NSPR] = {1, 2, 0, 2, 1};
    for (int i = 0; i < NSPR; i++, slot++)
        for (int half = 0; half < 2; half++) {
            uint8_t n = spr_pat[i][half]; int mirror = half == 1 && spr_pat[i][0] == spr_pat[i][1];
            for (int y = 0; y < 16; y++) {
                uint16_t a = (uint16_t)((n & 1) * 0x1000 + ((n & 0xFE) + (y >> 3)) * 16 + (y & 7));
                uint8_t bank = a >= 0x1000 ? ram[0x71B + ((a - 0x1000) >> 10)] : (uint8_t)((ram[0x719 + (a >> 11)] & 0xFE) | ((a >> 10) & 1));
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
    tex_h = (slot + 15) / 16 * 16;
    rt_log("smb3", "stage: %d animated tiles, texture 256 x %d", nanim, tex_h);
    if (getenv("SMB3_STAGE_BLOCKS"))                                     /* (testing: where the blocks are) */
        for (int r = 0; r < LH; r++) for (int c = 0; c < L.w; c++) { uint8_t t = L.tile[r * L.w + c]; if (t >= 0x60 && t <= 0x70) rt_log("smb3", "block %02X at %d,%d", t, c, r); }
    L.sky = ppu_rgb(ppu_peek_pal(0));
    L.ok = 1;
    {   const char *ap = getenv("SMB3_STAGE_ATLAS");                   /* (testing: the tile pictures as a PPM) */
        FILE *f = ap ? fopen(ap, "wb") : NULL;
        if (f) { fprintf(f, "P6 256 %d 255\n", tex_h); for (int i = 0; i < 256 * tex_h; i++) { uint8_t c[3] = {(uint8_t)(atlas[i] >> 16), (uint8_t)(atlas[i] >> 8), (uint8_t)atlas[i]}; fwrite(c, 1, 3, f); } fclose(f); } }
    rt_log("smb3", "stage: 1-1 loaded: %d x %d tiles, solidity %02X %02X %02X %02X / %02X %02X %02X %02X", L.w, LH,
           L.attr[0], L.attr[1], L.attr[2], L.attr[3], L.attr[4], L.attr[5], L.attr[6], L.attr[7]);
    return 1;
}

/* ---- the flow ---- */
static void player_scale(int on);
static void blocks_reset(void);
int retro_is_player(uint32_t pl);               /* rt_retro.c */
#define PLAYER_SCALE    0.80f                    /* (user, 2026-11-21: 80%; the 3D characters only, not Retro Mario) */
int smb3_stage_begin(ppc_context *ctx, uint8_t *base) {
    probe = getenv("SMB3_STAGE_PROBE") != NULL;
    if (!level_load()) return 0;
    active = 1; L.placed = 0; tex_ready = 0;
    L.ok = 0;                                                            /* (a fresh 1-1 each time: blocks back) */
    blocks_reset();
    player_scale(1);
    /* the players: everyone the character select took (dInfo +900 = 3; slots 4-7 the 8-player
       module's, 1992 further), small */
    uint32_t info = R32(G_DINFO); int n = 0;
    for (int i = 0; i < 8; i++) {
        uint32_t st = R32(info + (i >= 4 ? 1992 : 0) + 900 + 4 * (uint32_t)i);
        int on = st == 3;
        W32(WP_ENTRY_TABLE + 4 * (uint32_t)i, (uint32_t)on);
        if (on) { uint32_t k = R32(WP_ACTIVE_TABLE + 4 * (uint32_t)i); if (k < 8) W32(WP_SCENE_TABLE + 4 * k, 0); n++; }
    }
    if (!n) { W32(WP_ENTRY_TABLE, 1); n = 1; }
    W32(info + 80, 0); W32(info + 84, 0); W8(info + 109, 0);
    rt_log("smb3", "stage: %d player(s)", n);
    /* dInfo_c::startGame: course 1-1 (the shell), area 1, entrance 0 */
    for (int i = 0; i < 16; i += 4) W32(SM_START_INFO + i, 0);
    W8(SM_START_INFO + 12, 0); W8(SM_START_INFO + 13, 0); W8(SM_START_INFO + 14, 0); W8(SM_START_INFO + 15, 0);
    rt_log("smb3", "stage: starting (NSMBW course 1-1 as the shell)%s", probe ? " - probe: NSMBW's tiles kept, flags logged" : "");
    gcall(ctx, base, A_START_GAME, 2, R32(G_DINFO), SM_START_INFO);
    return 1;
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
    for (uint32_t k = 0; k < 3; k++) {                                   /* foot, head, wall: flags + three 1/4096 coordinates */
        uint32_t s = pl + 4244 + 16 * k;
        for (uint32_t j = 1; j < 4; j++) W32(s + 4 * j, (uint32_t)(int32_t)((float)(int32_t)R32(s + 4 * j) * PLAYER_SCALE));
    }
}
static int in_stage(void) { return R16(G_NOW_SCENE) == 5 && R32(G_GAME_MODE) != 2; }
int smb3_stage_on(void) {                        /* (on from Start Game through the course intro (scene 7) into the stage; off once elsewhere) */
    int sc = R16(G_NOW_SCENE);
    if (active && sc != 5 && sc != 7 && sc != 10) { active = 0; player_scale(0); }
    return active && in_stage();
}
int smb3_stage_suppress_actors(void) { return smb3_stage_on() && !probe; }

/* the players as last drawn (for solid-on-top: who is rising) */
static struct { int on; float x, y, vy; } rising[8];
/* NSMBW unit flags for SMB3's kinds (read from the course's own tiles: SMB3_STAGE_PROBE) */
/* (hi word: 0x01 solid, 0x20 solid on top, 0x40 ? block (low byte: its item), 0x04 breakable,
   0x10000 pipe; low word 0x000D0000: the course's ground kind - as the course's own tiles have them) */
static const uint64_t UNIT_SOLID = 0x0000000100000000ull, UNIT_TOP = 0x00000020000D000Aull;
int smb3_stage_unit(uint32_t x, uint32_t y, uint64_t *flags) {
    if (!smb3_stage_on() || probe) return 0;
    *flags = 0;
    if (!L.placed) return 1;
    int tx = (int)floorf(((float)(int32_t)(x & 0xFFFF) - L.lx) / 16.0f), ty = (int)floorf(((float)(int32_t)(y & 0xFFFF) - L.ly) / 16.0f);
    if (tx < 0 || tx >= L.w || ty >= LH) return 1;
    if (ty < 0) ty = 0;                                                  /* (above the level: as its top row - walls stay walls) */
    int c = tile_class(L.tile[ty * L.w + tx]);
    /* solid on top: only the top of it. SMB3 lands the player on such a tile's top edge only (its
       big blocks are solid on top all the way down); NSMBW's are one tile thick, and a stack of
       them lifts a player inside it row by row */
    if (c == 1 && ty > 0 && tile_class(L.tile[(ty - 1) * L.w + tx]) == 1) c = 0;
    /* and only as SMB3 lands on it: at its top edge (the upper 8 units), by a player who is not
       rising - one jumping up through it goes on with the jump (NSMBW's own semisolids are
       one-way by its collision; with these it would pull a player onto any it touches) */
    if (c == 1) {
        float ly_q = (float)(int32_t)(y & 0xFFFF);                       /* (y down) */
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
#define MOD_PY_REST      0x81851D8Cu            /* daPyMng_c::mRest[8] */
enum { T_SKY = 0x80, T_BUMPCLEAR = 0xF3, T_COIN = 0x40, T_USED = 0x5F, T_QFLOWER = 0x60, T_QLEAF, T_QSTAR, T_QCOIN, T_QCOINSTAR, T_QCOIN2,
       T_BRICK = 0x67, T_BFLOWER, T_BLEAF, T_BSTAR, T_BCOIN, T_BCOINSTAR, T_B10COIN, T_B1UP, T_BVINE, T_BPSWITCH };
#define A_IS_STAR        0x80022170u            /* daPlBase_c::isStar() const */
#define AC_VTABLE        96
#define VT_SET_STAR      984                    /* dAcPy_c::setStar(set, timer) */
static struct { int coins; uint32_t score; } SG;  /* SMB3's own counters, the score in tens (its status bar comes later) */
static int tick;                                 /* (Counter_1 / Level_NoStopCnt: +1 a frame) */
static int hit_who;                              /* (the player who hit a block: n) */
static void give_life(int n) { if (n >= 0 && n < 8) W32(MOD_PY_REST + 4 * (uint32_t)n, R32(MOD_PY_REST + 4 * (uint32_t)n) + 1); }
static float hit_x;                              /* (the player who hit a block) */
static ppc_context *blk_ctx; static uint8_t *blk_base;

/* -- the bounce (ObjNorm_BounceDU): 10 frames, Y velocity from Bouncer_PUpVel by position,
   negated (hit from below), applied the frame after; then the tile behind it goes in -- */
static const int8_t BOUNCER_VEL[11] = {0x00, -0x40, -0x40, -0x30, -0x20, -0x10, 0x00, 0x10, 0x20, 0x30, 0x40};
#define NBUMP 2
static struct { int on, tx, ty, pos, y16, vy; uint8_t shown, after; int item; } bumps[NBUMP];
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
typedef struct { int on, kind, x16, y16, xvel, yvel, xfrac, yfrac, timer, timer2, var1, var2, det, flip, block_y; } item_t;
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
    SG.coins++; if (SG.coins >= 100) { SG.coins -= 100; give_life(who); rt_log("smb3", "100 coins: 1-up for player %d", who + 1); }
}
static void pop_coin(int tx, int ty) {           /* LATP_CoinCommon -> PRG000_C49B: 4 slots, else the last */
    coin_get(hit_who);
    int i = 0; while (i < NPOP && pops[i].on) i++; if (i == NPOP) i = NPOP - 1;
    pops[i].on = 1; pops[i].x = (tx * 16) | 4; pops[i].y = ty * 16 - 24; pops[i].vy = -5; pops[i].counter = 0; pops[i].who = hit_who;
}
static void item_spawn(int kind, int tx, int ty) {
    for (int i = 0; i < NITEM; i++) {                                    /* (Level_PrepareNewObject on slot 5: replaces it) */
        item_t *it = &items[i]; memset(it, 0, sizeof *it);
        it->on = 1; it->kind = kind; it->x16 = tx * 16 * 16; it->y16 = ty * 16 * 16; it->block_y = ty * 16;
        it->timer2 = 0x10;                                               /* (no collecting for 16 frames) */
        /* Mushroom_SetFall: away from the player */
        mush_fall = (tx * 16 + 8) >= (hit_x - L.lx) ? 1 : 0;
        if (kind == SPR_LEAF) {                                          /* ObjInit_SuperLeaf (Player_BounceDir: up) */
            it->y16 += -0x0D * 16; it->timer = 0xFF; it->yvel = (int8_t)0xE0;
        } else {
            it->timer = 0x3D;                                            /* (out of the box: PowerUp_DoRaise) */
            if (kind == SPR_STAR) it->xvel = mush_fall ? 0x10 : -0x10;    /* (ObjInit_StarOrSuit: PowerUp_BounceXVel) */
        }
        rt_log("smb3", "item %d out of the block at %d,%d", kind, tx, ty);
        return;
    }
}
static int is_block(uint8_t v) { return v >= T_QFLOWER && v <= T_BPSWITCH; }   /* (Level_ActionTiles: TILEA_QBLOCKFLOWER + 17; up only) */
static void bump_start(int tx, int ty, uint8_t shown, uint8_t after, int item) {
    for (int i = 0; i < NBUMP; i++) if (!bumps[i].on) {                  /* (block bump slots: objects 6 and 7) */
        bumps[i].on = 1; bumps[i].tx = tx; bumps[i].ty = ty; bumps[i].pos = 10; bumps[i].y16 = 0; bumps[i].vy = 0;
        bumps[i].shown = shown; bumps[i].after = after; bumps[i].item = item;
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
static void hit_block(int tx, int ty, int big, int star) {
    uint8_t v = L.tile[ty * L.w + tx];
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
        if (big) { L.tile[ty * L.w + tx] = T_SKY; bust_start(tx, ty); SG.score += 1; return; }   /* (10 points) */
        break;
    case 7: rt_log("smb3", "vine block (not yet)"); break;
    case 9: item = SPR_1UP; break;                                       /* LATP_1up */
    case 0x0A: rt_log("smb3", "P-switch block (not yet)"); break;
    }
    bump_start(tx, ty, r == 0x20 ? T_USED : T_BRICK, r == 0x20 ? T_USED : r == 0x30 ? T_BRICK : T_BCOIN, item);
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
                if (it->timer < 0x2D) { if (--it->var1 < 0) { it->var1 = 2; it->y16 -= 16; } }
                continue;
            }
            if (it->kind == SPR_MUSHROOM || it->kind == SPR_1UP) {      /* ObjNorm_PUpMush */
                if ((it->det & 4) && it->xvel == 0) it->xvel = mush_fall ? 0x10 : -0x10;   /* (PowerUp_BounceXVel) */
                obj_move(it);
            } else if (it->kind == SPR_STAR) {                           /* ObjNorm_StarOrSuit */
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
    float lx = px - L.lx, lyb = -py - L.ly;                              /* (player's feet, level pixels) */
    for (int i = 0; i < NITEM; i++) {
        item_t *it = &items[i];
        if (!it->on || it->timer2 || (it->kind != SPR_LEAF && it->timer)) continue;   /* (PowerUp_DoHitTest: not while Timer2 / rising) */
        int x = it->x16 >> 4, y = it->y16 >> 4;
        if (lx + 6 < x + 2 || lx - 6 > x + 14 || lyb < y + 2 || lyb - h > y + 14) continue;
        int mode = (int)R32(pl + PL_MODE), small = mode == 0 || mode == 3;
        switch (it->kind) {
        case SPR_MUSHROOM:                                               /* ObjHit_PUpMush: small - Super */
            if (small) gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, 1);
            break;
        case SPR_FLOWER:                                                 /* ObjHit_FireFlower: small - as a mushroom; else Fire */
            if (small) gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, 1); else if (mode != 2) gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, 2);
            break;
        case SPR_LEAF:                                                   /* ObjHit_SuperLeaf: small - as a mushroom; else Raccoon */
            if (small) gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, 1); else rt_log("smb3", "leaf: the Raccoon suit (next)");
            break;
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
static void player_blocks(uint32_t pl) {
    int n = (int8_t)R8(pl + PL_PLR_NO); if (n < 0 || n > 7) return;
    int mode = (int)R32(pl + PL_MODE), big = mode != 0 && mode != 3;   /* (0 small, 3 mini) */
    float px = RF(pl + PL_POS), py = RF(pl + PL_POS + 4);
    float h = (big ? 28.0f : 16.0f) * (retro_is_player(pl) ? 1.0f : PLAYER_SCALE), hw = 5.0f;
    rising[n].on = 1; rising[n].x = px; rising[n].y = py; rising[n].vy = RF(pl + PL_SPEED + 4);
    { static int last_mode[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
      if (mode != last_mode[n]) { if (last_mode[n] >= 0) rt_log("smb3", "player %d: power-up %d -> %d", n + 1, last_mode[n], mode); last_mode[n] = mode; } }
    if (getenv("SMB3_STAGE_TRACE")) rt_log("smb3", "trace p%d y %.1f vy %.2f bg %08X", n + 1, py, rising[n].vy, R32(pl + PL_BG_CROSS1));
    hit_x = px;
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
            if (tile_of(px + dx[k], py + h + 4, &tx, &ty) && is_block(L.tile[ty * L.w + tx])) {
                hit_who = n; hit_block(tx, ty, big, gcall(blk_ctx, blk_base, A_IS_STAR, 1, pl) != 0); break;
            }
        }
    }
    head_was[n] = (uint8_t)head;
}
static void blocks_reset(void) {
    memset(items, 0, sizeof items); memset(rising, 0, sizeof rising); memset(bumps, 0, sizeof bumps); memset(pops, 0, sizeof pops);
    memset(scores, 0, sizeof scores); memset(busts, 0, sizeof busts); memset(&b10, 0, sizeof b10); b10.id = -1; SG.coins = 0; SG.score = 0;
}
static void blocks_frame(void) {                 /* (once a frame) */
    for (int i = 0; i < NBUMP; i++) {
        if (!bumps[i].on) continue;
        if (bumps[i].pos == 0) {                                         /* done: the tile behind it */
            L.tile[bumps[i].ty * L.w + bumps[i].tx] = bumps[i].after; bumps[i].on = 0; continue;
        }
        if (bumps[i].pos == 10 && bumps[i].item >= 0) item_spawn(bumps[i].item, bumps[i].tx, bumps[i].ty);
        bumps[i].y16 += bumps[i].vy;                                     /* (Object_ApplyYVel) */
        bumps[i].vy = -BOUNCER_VEL[bumps[i].pos];                        /* (hit from below: negated) */
        bumps[i].pos--;
    }
    tick++;
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
        if (scores[i].counter-- == 0x2A) { SG.score += SCORE_ADD[v - 1]; if (v == 0x0D) give_life(scores[i].who); }
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
}

/* ---- the picture ---- */
static void tex_upload(void) {                   /* the atlas as GX RGB5A3 (4 x 4 blocks) */
    uint32_t o = SM_TEX;
    for (int by = 0; by < tex_h; by += 4) for (int bx = 0; bx < 256; bx += 4)
        for (int y = 0; y < 4; y++) for (int x = 0; x < 4; x++) {
            uint32_t c = atlas[(by + y) * 256 + bx + x];
            uint16_t v = (c >> 24) ? (uint16_t)(0x8000 | ((c >> 19) & 31) << 10 | ((c >> 11) & 31) << 5 | ((c >> 3) & 31)) : 0;   /* (alpha 0: RGB5A3 transparent) */
            W16(o, v); o += 2;
        }
    tex_ready = 1;
}
static float pz;
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
    gcall(ctx, base, A_GXSetZCompLoc, 1, 1);
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
    const float q[4][5] = {{x0, y0, z, u0, v0}, {x1, y0, z, u1, v0}, {x1, y1, z, u1, v1}, {x0, y1, z, u0, v1}};
    for (int i = 0; i < 4; i++) for (int j = 0; j < 5; j++) gx_fifo_write(fbits(q[i][j]), 4);
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
    if (!smb3_stage_on() || probe || !L.placed) return;
    uint32_t cam = gcall(ctx, base, A_GET_CAMERA_BY_ID, 1, gcall(ctx, base, A_GET_CUR_CAMERA, 0));
    if (!cam) return;
    W32(SM_CAMERA, cam); gcall(ctx, base, A_GET_CAMERA_MTX, 2, SM_CAMERA, SM_MTX);
    if (!tex_ready) tex_upload();
    gx_setup(ctx, base);
    /* the tiles that show: from the camera's middle +- 2 screens */
    float zt = pz - 400.0f, zs = pz - 410.0f;
    int nx = 0; for (int i = 0; i < NPOP; i++) nx += pops[i].on; for (int i = 0; i < NITEM; i++) nx += items[i].on; for (int i = 0; i < NBUMP; i++) nx += bumps[i].on;
    for (int i = 0; i < NBUST; i++) nx += busts[i].on * 4; for (int i = 0; i < NSCORE; i++) nx += scores[i].value ? 2 : 0;
    int n = 1 + L.w * LH + nx;
    gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 4 * n);
    float su = 1.0f / 256, sv = 128.5f / (float)tex_h;
    extern uint64_t g_frames_presented; int af = (int)((g_frames_presented >> 3) & 3);   /* (SMB3: PT2_Anim, 8 frames each) */
    quad(L.lx - 4000, -(L.ly - 3000), L.lx + L.w * 16 + 4000, -(L.ly + LH * 16 + 3000), zs, su, sv, su, sv);
    #define SLOT_UV(sl, u0, v0) float u0 = ((sl) % 16) * 16 / 256.0f, v0 = ((sl) / 16) * 16 / (float)tex_h
    for (int r = 0; r < LH; r++) for (int c = 0; c < L.w; c++) {
        uint8_t t = L.tile[r * L.w + c];
        float x0 = L.lx + c * 16, y0 = -(L.ly + r * 16);
        int sl = af && anim_slot[t] >= 0 ? anim_slot[t] + af - 1 : t;
        SLOT_UV(sl, u0, v0);
        quad(x0, y0, x0 + 16, y0 - 16, zt, u0, v0, u0 + 16 / 256.0f, v0 + 16 / (float)tex_h);
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
        if (yb < y) yb = y;                                              /* (all inside the box: nothing shows; the quad still counts) */
        if (items[i].flip) { float tu = u0; u0 = u1; u1 = tu; }
        quad(L.lx + x, -(L.ly + y), L.lx + x + 16, -(L.ly + yb), zt + 2, u0, v0, u1, v1);
    }
    gcall(ctx, base, A_G3D_INVALIDATE, 1, 0x7FF);
}
static void native_dtor(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }
static void native_draw_opa(ppc_context *ctx, uint8_t *base) { proc_draw(ctx, base); }
static void native_draw_xlu(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }

/* from dAcPy_c::draw (rt_retro.c), each player each frame: the level is placed at player 1's
   first appearance; the draw proc is entered once a frame */
void smb3_stage_player_draw(ppc_context *ctx, uint8_t *base, uint32_t pl) {
    if (!smb3_stage_on()) return;
    if (L.placed && !probe) { blk_ctx = ctx; blk_base = base; player_blocks(pl); }
    static uint64_t last; extern uint64_t g_frames_presented;
    if (last == g_frames_presented) return;
    last = g_frames_presented;
    blocks_frame();
    pz = RF(pl + PL_POS + 8);
    if (!L.placed) {
        float px = RF(pl + PL_POS), py = RF(pl + PL_POS + 4);
        int col = 2;                                                     /* SMB3's start column (SMB3_STAGE_TEST_X=column: elsewhere, testing) */
        { const char *e = getenv("SMB3_STAGE_TEST_X"); if (e && atoi(e) > 0 && atoi(e) < L.w) col = atoi(e); }
        int g = LH - 1; while (g > 0 && tile_class(L.tile[(g - 1) * L.w + col]) != 0) g--;   /* its ground: the top of the column's floor */
        L.lx = px - (col * 16 + 8); L.ly = -py - g * 16; L.placed = 1;
        rt_log("smb3", "stage: player 1 at (%.1f, %.1f, %.1f): SMB3 1-1 placed at (%.1f, %.1f), ground row %d", px, py, pz, L.lx, L.ly, g);
        if (probe) probe_tiles(ctx, base); else empty_course();
        {   const char *e = getenv("SMB3_STAGE_TEST_TILES");             /* (testing: "col,row,tile;..." changes the level) */
            for (int c, r, t, k; e && sscanf(e, "%d,%d,%x%n", &c, &r, &t, &k) == 3; e += k + (e[k] == ';'))
                if (c >= 0 && c < L.w && r >= 0 && r < LH) L.tile[r * L.w + c] = (uint8_t)t; }
    }
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
    gcall(ctx, base, A_LEAF_ENTRY, 1, SM_PROC);
}
