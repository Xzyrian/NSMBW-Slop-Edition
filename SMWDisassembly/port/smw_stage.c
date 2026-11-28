/* smw_stage.c - NSMBW players in SMW's levels (begun: user, 2026-11-27 "begin implementing NSMBW
 * characters"). The way SMB3's stage began (SMB3Disassembly/port/smb3_stage.c), and by
 * CHARACTERS_AND_GAMES.md: the characters are NSMBW's, the level is SMW's.
 *
 * SMW runs on its own screen (smw_main.c) through its menus and map. When it starts a level
 * (game mode $14 - not the intro), it is held there and the level is handed to an NSMBW stage:
 * NSMBW's course 1-1 as an empty shell (its actors not spawned, its tiles emptied), with
 *   - the level as SMW's own loader built it: Map16TilesLow / High ($7EC800 / $7FC800: 16 x 27
 *     tiles a screen, horizontal levels), each 16 x 16 tile's picture made from its four 8 x 8
 *     tiles (Map16Pointers, bank $0D) with the BG1 patterns and palette in VRAM / CGRAM;
 *   - collision as SMW's own (bank 0, the player's block interaction): page 0 passes, $100-$110
 *     are ledges (solid on top), $111-$16D solid, $16E-$1D7 slopes by SMW's slope table
 *     (SlopesPtr -> SlopeHeights) as NSMBW's slope units, $1D8-$1FA (slope assists) passed
 *     under a slope and solid elsewhere, $1FB-$1FF lava (passed for now);
 *   - layer 2 (the background) as SMW draws it from VRAM, scrolled at half the camera's speed;
 *   - the players where SMW puts Mario, at 80% (as in SMB3's stage); NSMBW's camera kept in the
 *     level as SMW's (no zoom out, not below SMW's lowest); a one-screen level (Yoshi's House)
 *     centred, still, its ground carried out to NSMBW's wider screen;
 *   - a death starts the level again; Exit Course or a side exit: SMW's map (smw_leave_level,
 *     NSMBW to the setup scene SMW runs over).
 * Not yet: SMW's objects, blocks, items, enemies, its status bar, the goal, vertical levels. */
#include "rt.h"
#include "smw.h"
#include "snes.h"
#include "snes_ppu.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
RT_STATE_FILE

extern const uint8_t smw_rom[]; extern const uint32_t smw_rom_size;

/* ---- guest (as smb3_stage.c's) ---- */
#define G_NOW_SCENE     0x80428732u
#define G_GAME_MODE     0x8042A204u
#define SDA             0x8042F680u
#define BG_GM           (SDA - 22704)            /* dBgGm_c::m_bg_p */
#define BG_TILEMAPS     (SDA - 22672)
#define BG_AREA         (SDA - 21688)
#define BG_PARAM_P      0x80429E00u              /* dBgParameter_c::ms_Instance_p (+56 / +60 the screen's top left, +64 / +68 its size) */
#define A_START_GAME    0x800BB780u
#define A_SET_FADER     0x800B0DB0u
#define A_CRSIN_DISP_OFF 0x8042A1B0u
#define G_DINFO         (0x80430000u - 24708)
#define PL_POS          0x0AC
#define PL_PLR_NO       0x38D
#define WP_ENTRY_TABLE  (0x81860000u - 6000)
#define MOD_PY_REST     0x81851D8Cu
#define WP_ACTIVE_TABLE (0x81860000u - 5828)
#define WP_SCENE_TABLE  (0x81860000u - 5796)
#define A_MDL_SCALES    0x80370DA8u
#define NSCALES         7
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
#define A_GXInvalidateTexAll 0x801C76C0u
#define gcall rt_gcall
/* memory of ours: past the SMB3 stage's merged animation files (smb3_stage.c MERGE_MEM, 16 MB) */
#define SW_MEM          0x83400000u
#define SW_PROC         (SW_MEM + 0x0000)
#define SW_VTABLE       (SW_MEM + 0x0040)
#define SW_CAMERA       (SW_MEM + 0x0080)
#define SW_MTX          (SW_MEM + 0x00A0)
#define SW_TEXOBJ       (SW_MEM + 0x0100)
#define SW_BGOBJ        (SW_MEM + 0x0120)
#define SW_START_INFO   (SW_MEM + 0x0140)
#define SW_TEX          (SW_MEM + 0x1000)        /* the tiles: 256 x up to 1024, RGB5A3 (512 KB) */
#define SW_BGTEX        (SW_MEM + 0x100000)      /* layer 2: up to 512 x 512, RGB5A3 (512 KB) */
#define N_SW_DTOR       0x80003F60u
#define N_SW_DRAW_OPA   0x80003F64u
#define N_SW_DRAW_XLU   0x80003F68u
#define PLAYER_SCALE    0.80f
static uint32_t fbits(float f) { uint32_t u; memcpy(&u, &f, 4); return u; }
static float RF(uint32_t a) { uint32_t u = R32(a); float f; memcpy(&f, &u, 4); return f; }
static void WF(uint32_t a, float f) { W32(a, fbits(f)); }
int retro_is_player(uint32_t pl);               /* rt_retro.c */

/* SMW's RAM (smw_u.sym) */
#define RAM_SCREEN_MODE   0x005B                 /* (ScreenMode: bit 0 a vertical level) */
#define RAM_LAST_SCREEN   0x005E                 /* (LastScreenHoriz) */
#define RAM_SLOPES_PTR    0x0082                 /* (SlopesPtr, 24-bit) */
#define RAM_PLAYER_X      0x0094
#define RAM_PLAYER_Y      0x0096
#define RAM_MAP16_PTRS    0x0FBE                 /* (Map16Pointers: 512 x 16-bit, in bank $0D for levels) */
#define RAM_OBJ_TILESET   0x1931
#define RAM_TRANSLEVEL    0x13BF
#define RAM_SIDE_EXIT     0x1B96                 /* (SideExitEnabled) */
#define MAP16_LOW         0x0C800                /* ($7EC800, in snes_wram) */
#define MAP16_HIGH        0x1C800                /* ($7FC800) */
#define ROM_SLOPE_HEIGHTS 0x00E632               /* (SlopeHeights: 16 bytes a slope id) */

/* ---- the level ---- */
#define LH 27
#define SMW_BOTTOM 416.0f                        /* (the lowest SMW shows of a horizontal level: layer 1 at $C0, 224 lines) */
#define MAXW (32 * 16)
static struct {
    int ok, w, level;                            /* tiles across; SMW's translevel */
    uint16_t tile[LH * MAXW];                    /* Map16 numbers */
    int16_t slot[512];                           /* a Map16 tile's place in the atlas, or -1 */
    uint8_t slope_id[0x6A];                      /* (tiles $16E-$1D7: SMW's slope id) */
    uint8_t heights[0x20][16];                   /* (SlopeHeights) */
    int sx, sy;                                  /* where SMW starts Mario (its $94 / $96) */
    int c0, c1;                                  /* the columns in play (a level SMW doesn't scroll: its screen) */
    int fixed, side_exit;                        /* one screen SMW doesn't scroll (Yoshi's House); SideExitEnabled: off its sides to the map */
    float edge0, edge1; int edges;               /* (a fixed level: the screen's sides, NSMBW's x - smw_stage_camera) */
    uint32_t scene;                              /* (the stage it was placed in: a restart places it again) */
    uint32_t backdrop;                           /* 0xAARRGGBB */
    int bg_w, bg_h; float bg_x0, bg_y0, l1_x0, l1_y0;   /* layer 2's picture; its and layer 1's scroll as SMW had them */
    int placed; float lx, ly;                    /* the level's top left in NSMBW's world (y down) */
} L RT_LOCAL;
#define TEX_H_MAX 1024
static uint32_t atlas[256 * TEX_H_MAX] RT_LOCAL;
static uint32_t bgpic[512 * 512] RT_LOCAL;
static int tex_h, tex_ready, active;
static float pz;
static float vs_top; static int vs_on;           /* (the camera's top in the level: smw_stage_camera) */
static struct { int on; float y; } p1;           /* (player 1 as last drawn: its feet, level y down) */

static uint8_t romb(uint32_t a) { return smw_rom[(((a >> 16) & 0x7F) << 15 | (a & 0x7FFF)) % smw_rom_size]; }
static uint32_t rgb15(uint16_t c) {
    int r = c & 31, g = (c >> 5) & 31, b = (c >> 10) & 31;
    return 0xFF000000u | (uint32_t)(r << 3 | r >> 2) << 16 | (uint32_t)(g << 3 | g >> 2) << 8 | (uint32_t)(b << 3 | b >> 2);
}
/* an 8 x 8 tile (a BG tilemap entry) into out (stride) - 4bpp, from VRAM chr base (words) */
static void tile8(uint32_t *out, int stride, uint16_t e, uint16_t cbase, uint32_t transparent) {
    const uint16_t *vram = sppu_vram(), *cg = sppu_cgram();
    int t = e & 0x3FF, pal = (e >> 10) & 7;
    for (int y = 0; y < 8; y++) {
        int fy = (e & 0x8000) ? 7 - y : y;
        uint16_t a = (uint16_t)(cbase + t * 16 + fy), w0 = vram[a & 0x7FFF], w1 = vram[(a + 8) & 0x7FFF];
        for (int x = 0; x < 8; x++) {
            int bit = (e & 0x4000) ? x : 7 - x;
            int c = ((w0 >> bit) & 1) | ((w0 >> (bit + 8)) & 1) << 1 | ((w1 >> bit) & 1) << 2 | ((w1 >> (bit + 8)) & 1) << 3;
            out[y * stride + x] = c ? rgb15(cg[pal * 16 + c]) : transparent;
        }
    }
}
/* the level, from SMW held at its start (game mode $14) */
static int capture(void) {
    const uint8_t *w = snes_wram_ptr();
    if (w[RAM_SCREEN_MODE] & 1) { rt_log("smw", "stage: level %02X is vertical - not yet", w[RAM_TRANSLEVEL]); return 0; }
    int screens = w[RAM_LAST_SCREEN] + 1; if (screens < 1) screens = 1; if (screens > 32) screens = 32;
    L.w = screens * 16; L.level = w[RAM_TRANSLEVEL];
    for (int s = 0; s < screens; s++) for (int r = 0; r < LH; r++) for (int c = 0; c < 16; c++) {
        uint32_t i = (uint32_t)(s * 0x1B0 + r * 16 + c);
        L.tile[r * L.w + s * 16 + c] = (uint16_t)(w[MAP16_LOW + i] | (w[MAP16_HIGH + i] & 1) << 8);
    }
    L.sx = w[RAM_PLAYER_X] | w[RAM_PLAYER_X + 1] << 8; L.sy = w[RAM_PLAYER_Y] | w[RAM_PLAYER_Y + 1] << 8;
    L.c0 = 0; L.c1 = L.w;
    L.side_exit = w[RAM_SIDE_EXIT] != 0;
    L.fixed = !w[0x1411] || L.side_exit;                                 /* (HorzLayer1Setting 0, or off its sides to the map: SMW shows its one screen - Yoshi's House) */
    L.edges = 0;
    int l1x = w[0x1A] | w[0x1B] << 8;
    if (L.fixed) {
        /* its screen, with the ground carried out either side (NSMBW's screen is wider than SMW's):
           the screen's 16 columns at FIX_M, each side's outer column repeated outwards - its
           lowest unbroken run (the ground), the sky above it */
        enum { FIX_M = 16 };
        int c0 = l1x / 16; if (c0 > L.w - 16) c0 = L.w - 16; if (c0 < 0) c0 = 0;
        int n = L.w - c0 < 16 ? L.w - c0 : 16, nw = n + 2 * FIX_M;
        static uint16_t t2[LH * MAXW];
        for (int r = 0; r < LH; r++) for (int c = 0; c < nw; c++) t2[r * nw + c] = 0x25;
        for (int r = 0; r < LH; r++) for (int c = 0; c < n; c++) t2[r * nw + FIX_M + c] = L.tile[r * L.w + c0 + c];
        for (int side = 0; side < 2; side++) {
            int src = side ? FIX_M + n - 1 : FIX_M, top = LH;
            while (top > 0 && t2[(top - 1) * nw + src] != 0x25) top--;
            for (int r = top; r < LH; r++) for (int k = 1; k <= FIX_M; k++) t2[r * nw + (side ? src + k : src - k)] = t2[r * nw + src];
        }
        memcpy(L.tile, t2, sizeof(uint16_t) * (size_t)(LH * nw));
        L.w = nw; L.c0 = FIX_M; L.c1 = FIX_M + n;
        L.sx += (FIX_M - c0) * 16; l1x += (FIX_M - c0) * 16;
    }
    uint32_t sp = w[RAM_SLOPES_PTR] | w[RAM_SLOPES_PTR + 1] << 8 | (uint32_t)w[RAM_SLOPES_PTR + 2] << 16;
    for (int i = 0; i < 0x6A; i++) L.slope_id[i] = romb(sp + (uint32_t)i);
    for (int i = 0; i < 0x20; i++) for (int k = 0; k < 16; k++) L.heights[i][k] = romb(ROM_SLOPE_HEIGHTS + (uint32_t)(i * 16 + k));
    /* the tiles' pictures: each Map16 tile used, from its four 8 x 8 (upper left, lower left,
       upper right, lower right) with BG1's patterns */
    uint8_t sc, nba, mode; uint16_t h1, v1, h2, v2;
    sppu_bg(0, &sc, &nba, &h1, &v1, &mode);
    uint16_t cbase = (uint16_t)(nba << 12);
    uint8_t bank = w[RAM_OBJ_TILESET] < 0x10 ? 0x0D : 0x05;
    memset(L.slot, 0xFF, sizeof L.slot);
    int n = 0;
    for (int i = 0; i < L.w * LH; i++) {
        uint16_t t = L.tile[i];
        if (L.slot[t] >= 0) continue;
        if (n >= (TEX_H_MAX / 16) * 16) { L.tile[i] = 0x25; continue; }
        L.slot[t] = (int16_t)n;
        uint32_t ptr = (uint32_t)bank << 16 | (uint16_t)(w[RAM_MAP16_PTRS + t * 2] | w[RAM_MAP16_PTRS + t * 2 + 1] << 8);
        uint32_t *o = &atlas[((n / 16) * 16) * 256 + (n % 16) * 16];
        static const int ox[4] = {0, 0, 8, 8}, oy[4] = {0, 8, 0, 8};
        for (int k = 0; k < 4; k++) {
            uint16_t e = (uint16_t)(romb(ptr + (uint32_t)k * 2) | romb(ptr + (uint32_t)k * 2 + 1) << 8);
            tile8(o + oy[k] * 256 + ox[k], 256, e, cbase, 0);
        }
        n++;
    }
    tex_h = ((n + 15) / 16) * 16; if (tex_h < 16) tex_h = 16;
    L.backdrop = rgb15((uint16_t)(w[0x0701] | w[0x0702] << 8));       /* (BackgroundColor: SMW's NMI writes it to colour 0 each frame) */
    /* layer 2: its tilemap as SMW has it in VRAM, the empty pixels the backdrop */
    sppu_bg(1, &sc, &nba, &h2, &v2, &mode);
    int wide = sc & 1, tall = (sc >> 1) & 1; uint16_t base = (uint16_t)((sc & 0xFC) << 8), cb2 = (uint16_t)(nba << 12);
    L.bg_w = wide ? 512 : 256; L.bg_h = tall ? 512 : 256;
    const uint16_t *vram = sppu_vram();
    for (int my = 0; my < L.bg_h / 8; my++) for (int mx = 0; mx < L.bg_w / 8; mx++) {
        uint16_t scr = (uint16_t)(((mx >> 5) & wide ? 0x400 : 0) + ((my >> 5) & tall ? (wide ? 0x800 : 0x400) : 0));
        uint16_t e = vram[(uint16_t)(base + scr + (my & 31) * 32 + (mx & 31)) & 0x7FFF];
        tile8(&bgpic[my * 8 * 512 + mx * 8], 512, e, cb2, L.backdrop);
    }
    L.bg_x0 = h2; L.bg_y0 = v2; L.l1_x0 = h1 + (l1x - (w[0x1A] | w[0x1B] << 8)); L.l1_y0 = v1;   /* (layer 1's x as the columns are now) */
    L.ok = 1; L.placed = 0; tex_ready = 0;
    rt_log("smw", "stage: level %02X: %d screens, %d tiles drawn (texture 256 x %d), Mario at %d,%d, layer 2 %dx%d at %d,%d (layer 1 %d,%d)%s%s",
           L.level, screens, n, tex_h, L.sx, L.sy, L.bg_w, L.bg_h, h2, v2, h1, v1, L.fixed ? ", one screen (its ground carried out)" : "", L.side_exit ? ", off its sides to the map" : "");
    if (getenv("SMW_STAGE_MAP"))                                         /* (testing: the classes, rows 10-26) */
        for (int r = 10; r < LH; r++) { char line[MAXW + 1]; int c; for (c = 0; c < L.w; c++) { uint16_t t = L.tile[r * L.w + c];
            line[c] = t < 0x100 ? '.' : t <= 0x110 ? '=' : t <= 0x16D ? '#' : t <= 0x1D7 ? '/' : t <= 0x1FA ? '#' : '~'; } line[c] = 0; rt_log("smw", "map %2d %s", r, line); }
    return 1;
}

/* ---- collision: SMW's tiles as NSMBW unit flags (the values smb3_stage.c read from the course) */
static const uint64_t UNIT_SOLID = 0x0000000100000000ull, UNIT_TOP = 0x00000020000D000Aull;
static uint64_t slope_floor(int code) { return 0x00000020000D0000ull | (uint64_t)code; }
static uint64_t slope_ceiling(int code) { return 0x0000004000000000ull | (uint64_t)code; }
/* a slope tile ($16E-$1D7) by its SlopeHeights row (the ground's depth below the tile's top at each
   pixel across; $10 none, $Fx a ceiling's): NSMBW's slopes are 45 degrees (0 /, 1 \) and 22.5
   (2 3 the two tiles of a /, low then high; 4 5 of a \, high then low) - SMW's 1:4 go to the
   nearer 22.5 half, its 2:1 are solid */
static int slope_flags(uint16_t t, uint64_t *f) {
    int id = L.slope_id[t - 0x16E] & 0x1F;
    const uint8_t *h = L.heights[id];
    int a = h[0], b = h[15];
    if (a >= 0x10 && a < 0xF0 && b >= 0x10 && b < 0xF0) { *f = UNIT_SOLID; return 1; }   /* (a 2:1's lower half: all ground) */
    int ceil = a >= 0xF0 || b >= 0xF0;
    if (ceil) { a = (a & 0x0F) ^ 0x0F; b = (b & 0x0F) ^ 0x0F; }
    int d = a - b, m = (a + b) / 2, code;
    if (d >= 13) code = 0; else if (d <= -13) code = 1;
    else if (d > 0) code = m >= 8 ? 2 : 3;
    else if (d < 0) code = m < 8 ? 4 : 5;
    else { *f = a < 8 ? UNIT_SOLID : 0; return 1; }
    *f = ceil ? slope_ceiling(code) : slope_floor(code);
    return 1;
}
static int tile_solid(uint16_t t) { return t >= 0x100 && t < 0x1FB; }
int smw_stage_on(void);
int smw_stage_unit(uint32_t x, uint32_t y, uint64_t *flags) {
    if (!smw_stage_on()) return 0;
    *flags = 0;
    if (!L.placed) return 1;
    int tx = (int)floorf(((float)(int32_t)(x & 0xFFFF) - L.lx) / 16.0f), ty = (int)floorf(((float)(int32_t)(y & 0xFFFF) - L.ly) / 16.0f);
    if (tx < 0 || tx >= L.w) { *flags = UNIT_SOLID; return 1; }
    if (L.fixed) {                                                       /* (one screen: walls at NSMBW's screen's sides - past them, off a side exit's) */
        float wx = (float)(int32_t)(x & 0xFFFF), pad = L.side_exit ? 48.0f : 0.0f;
        if (L.edges && (wx < L.edge0 - pad || wx >= L.edge1 + pad)) { *flags = UNIT_SOLID; return 1; }
    } else if (tx < L.c0 || tx >= L.c1) { *flags = UNIT_SOLID; return 1; }   /* (the level's ends: walls) */
    if (ty >= LH) return 1;
    if (ty < 0) ty = 0;
    uint16_t t = L.tile[ty * L.w + tx];
    if (t < 0x100) return 1;
    if (t <= 0x110) { *flags = UNIT_TOP; return 1; }
    if (t <= 0x16D) { *flags = UNIT_SOLID; return 1; }
    if (t <= 0x1D7) return slope_flags(t, flags);
    if (t <= 0x1FA) {                                                    /* (SMW's slope assists: under a slope, the slope above carried down for a foot in it - a hill's body passes; elsewhere ground) */
        uint16_t up = ty > 0 ? L.tile[(ty - 1) * L.w + tx] : 0x25;
        *flags = up >= 0x16E && up <= 0x1D7 ? 0 : UNIT_SOLID; return 1; }
    return 1;                                                            /* (lava: passed for now) */
}

/* ---- the flow ---- */
static float scale_saved[NSCALES]; static uint8_t scale_changed[NSCALES]; static int scaled;
static void player_scale(int on) {
    if (on == scaled) return;
    scaled = on;
    for (int i = 0; i < NSCALES; i++) {
        uint32_t a = A_MDL_SCALES + 4 * (uint32_t)i;
        if (on) { scale_saved[i] = RF(a); scale_changed[i] = scale_saved[i] > 0.2f && scale_saved[i] < 4.0f; if (scale_changed[i]) WF(a, scale_saved[i] * PLAYER_SCALE); }
        else if (scale_changed[i]) WF(a, scale_saved[i]);
    }
}
void smw_stage_player_sensors(uint32_t pl) {
    if (!smw_stage_on() || retro_is_player(pl)) return;
    for (uint32_t k = 0; k < 3; k++) {                                   /* foot, head, wall (as smb3_stage.c) */
        uint32_t s = pl + 4244 + 16 * k;
        for (uint32_t j = 1; j < 4; j++) {
            float v = (float)(int32_t)R32(s + 4 * j) * PLAYER_SCALE;
            if (k == 2) v = roundf(v / 4096.0f) * 4096.0f;
            W32(s + 4 * j, (uint32_t)(int32_t)v);
        }
    }
}
float smw_stage_player_scale(uint32_t pl) { return smw_stage_on() && !retro_is_player(pl) ? PLAYER_SCALE : 1.0f; }
static int in_stage(void) { return R16(G_NOW_SCENE) == 5 && R32(G_GAME_MODE) != 2; }
static int leaving;                              /* (the stage left for SMW's map: smw_stage_leave) */
static int stage_gen;                            /* (stages started: SMW_STAGE_TEST_EXIT) */
static int leave_mode = -1;                      /* (a side exit asked: its exit mode for SMW) */
int smw_stage_on(void) {
    int sc = R16(G_NOW_SCENE);
    if (active && sc != 5 && sc != 7 && (sc != 10 || leaving)) { active = 0; leaving = 0; player_scale(0); rt_log("smw", "stage: left"); }
    return active && in_stage();
}
int smw_stage_suppress_actors(void) { return smw_stage_on(); }
/* (smw_main.c: SMW has reached a level and is held there) */
int smw_level_held(void);
static int stage_start_game(ppc_context *ctx, uint8_t *base) {
    leaving = 0; leave_mode = -1; L.edges = 0; stage_gen++;
    { extern int rt_stage_exit_kind; rt_stage_exit_kind = -1; }
    tex_ready = 0; p1.on = 0; vs_on = 0;                                 /* (L.placed kept: the old stage draws on through NSMBW's wipe - placed again in the new one) */
    active = 1;
    player_scale(1);
    uint32_t info = R32(G_DINFO); int n = 0;
    for (int i = 0; i < 8; i++) {
        uint32_t st = R32(info + (i >= 4 ? 1992 : 0) + 900 + 4 * (uint32_t)i);
        int on = st == 3;
        W32(WP_ENTRY_TABLE + 4 * (uint32_t)i, (uint32_t)on);
        if (on) { uint32_t k = R32(WP_ACTIVE_TABLE + 4 * (uint32_t)i); if (k < 8) W32(WP_SCENE_TABLE + 4 * k, 0); n++; }
    }
    if (!n) { W32(WP_ENTRY_TABLE, 1); n = 1; }
    W32(info + 80, 0); W32(info + 84, 0); W8(info + 109, 0);
    for (int i = 0; i < 16; i += 4) W32(SW_START_INFO + i, 0);
    rt_log("smw", "stage: %d player(s), SMW level %02X in NSMBW's course 1-1 (the shell)", n, L.level);
    gcall(ctx, base, A_SET_FADER, 1, 0);
    W8(A_CRSIN_DISP_OFF, 1);                                             /* (no NSMBW course intro: SMW has its own) */
    gcall(ctx, base, A_START_GAME, 2, R32(G_DINFO), SW_START_INFO);
    return 1;
}
/* Start Game's end (rt_gamesetup.c, finalizeState_VoiceEndWait): the level SMW holds, in a stage */
int smw_stage_begin(ppc_context *ctx, uint8_t *base) {
    if (!smw_level_held()) return 0;
    if (!capture()) return 0;
    L.placed = 0;
    return stage_start_game(ctx, base);
}
/* leaving the stage for SMW's map: SMW out of its level (exit_mode: smw_leave_level), NSMBW to the
   setup scene SMW runs over (rt_gamesetup.c: smw_resume) in place of its world map */
#define A_DO_SCENE_CHANGE   0x800E1E60u          /* dScene_c::setNextScene(profile, param, force) */
#define A_STAGE_NEXT_SCENE  0x80102260u          /* dScStage_c::setNextScene(scene, param, Exit_e, fader) */
static int stage_leave(ppc_context *ctx, uint8_t *base, int exit_mode) {
    rt_log("smw", "stage: left for SMW's map (exit mode %02X)", exit_mode);
    smw_leave_level(exit_mode);
    leaving = 1; leave_mode = -1;
    gcall(ctx, base, A_DO_SCENE_CHANGE, 3, 10, 0, 0);                    /* (SCENE_GAME_SETUP) */
    return 1;
}
/* NSMBW leaving the course for its world map (rt_lyt.c): Exit Course from its pause menu, or a side
   exit (below) - SMW's map; a death with lives left - the level again */
int smw_stage_restart(ppc_context *ctx, uint8_t *base) {
    if (!smw_stage_on() || !L.ok) return 0;
    extern int rt_stage_exit_kind;                                       /* (rt_lyt.c: dScStage_c::Exit_e - 1 a death (the player's code), 0 the goal, 2 Exit Course) */
    if (leave_mode >= 0) return stage_leave(ctx, base, leave_mode);
    if (rt_stage_exit_kind != 1) return stage_leave(ctx, base, 0x80);   /* (not a death - Exit Course: as SMW's Start + Select, back on the level's tile, no event) */
    int any = 0; for (int i = 0; i < 8; i++) if (R32(WP_ENTRY_TABLE + 4 * (uint32_t)i) && (int)R32(MOD_PY_REST + 4 * (uint32_t)i) > 0) any = 1;
    if (!any) return 0;                                                  /* (game over: NSMBW's own) */
    rt_log("smw", "stage: a player down - the level again");
    return stage_start_game(ctx, base);
}

/* ---- the camera: in the level (SMW never shows past its ends), the bottom by default, up with
   player 1 when it climbs ---- */

void smw_stage_camera(void) {
    if (!smw_stage_on() || !L.placed) { vs_on = 0; return; }
    uint32_t bp = R32(BG_PARAM_P), bg = R32(0x80429DD0u);
    if (!bp || !bg) return;
    float h = RF(bp + 68), w = RF(bp + 64); if (h < 100 || h > 1000) return;
    {   float bw = RF(bp + 0x70), bh = RF(bp + 0x74);                   /* (NSMBW's camera doesn't zoom out: SMW's never does - dBgParameter_c +0x70 the unzoomed screen, dBg_c +0x8FE78.. its targets, as smb3_stage.c's Toad Houses) */
        if (bw > 100 && bh > 100) {
            W32(bp + 0x40, fbits(bw)); W32(bp + 0x44, fbits(bh));
            for (uint32_t o = 0x8FE78; o < 0x8FE88; o += 8) { W32(bg + o, fbits(bw)); W32(bg + o + 4, fbits(bh)); }
            w = bw; h = bh;
        } }
    float lowest = SMW_BOTTOM - h; if (lowest < 0) lowest = 0;           /* (SMW shows a level down to its layer 1 at $C0: 416) */
    if (!vs_on) { vs_on = 1; vs_top = lowest; }
    if (vs_top > lowest) vs_top = lowest;
    if (p1.on) {                                                         /* (player 1 kept between a third and three quarters down the screen) */
        float d = p1.y - vs_top;
        if (d < h * 0.33f) vs_top += fmaxf(d - h * 0.33f, -4.0f);
        else if (d > h * 0.75f) vs_top += fminf(d - h * 0.75f, 6.0f);
        if (vs_top > lowest) vs_top = lowest; if (vs_top < 0) vs_top = 0;
    }
    if (L.fixed) vs_top = lowest;                                         /* (one screen: still, as SMW's) */
    {   float x = RF(bp + 56), lo = L.lx + L.c0 * 16, hi = L.lx + L.c1 * 16 - w, nx = x < lo ? lo : x > hi ? hi : x;
        if (L.fixed || hi <= lo) { nx = L.lx + (L.c0 + L.c1) * 8 - w * 0.5f; lo = nx - 1; hi = nx + 1; }   /* (narrower than the screen: centred) */
        if (L.fixed) { L.edge0 = nx; L.edge1 = nx + w; L.edges = 1; }
        if (hi > lo && nx != x) { W32(bp + 0x38, fbits(nx)); W32(bp + 0x60, fbits(nx)); W32(bg + 0x900AC, fbits(nx)); W32(bp + 0x48, fbits(nx + w * 0.5f)); W32(bp + 0x50, fbits(nx + w * 0.5f)); }
    }
    float top = -(L.ly + vs_top);
    W32(bp + 0x3C, fbits(top)); W32(bp + 0x64, fbits(top)); W32(bg + 0x900B0, fbits(top));
    W32(bp + 0x4C, fbits(top - h * 0.5f)); W32(bp + 0x54, fbits(top - h * 0.5f));
}

/* ---- the picture ---- */
static void tex_upload_to(uint32_t o, const uint32_t *px, int stride, int w, int h, int opaque) {   /* GX RGB5A3, 4 x 4 blocks */
    for (int by = 0; by < h; by += 4) for (int bx = 0; bx < w; bx += 4)
        for (int y = 0; y < 4; y++) for (int x = 0; x < 4; x++) {
            uint32_t c = px[(by + y) * stride + bx + x];
            uint16_t v = (opaque || (c >> 24)) ? (uint16_t)(0x8000 | ((c >> 19) & 31) << 10 | ((c >> 11) & 31) << 5 | ((c >> 3) & 31)) : 0;
            W16(o, v); o += 2;
        }
}
static void tex_upload(void) {
    tex_upload_to(SW_TEX, atlas, 256, 256, tex_h, 0);
    tex_upload_to(SW_BGTEX, bgpic, 512, L.bg_w, L.bg_h, 1);
    tex_ready = 1;
}
static void gx_setup(ppc_context *ctx, uint8_t *base, uint32_t texobj, uint32_t tex, int w, int h, int wrap) {
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
    gcall(ctx, base, A_GXSetAlphaCompare, 5, 4, 0, 0, 7, 0);
    gcall(ctx, base, A_GXSetBlendMode, 4, 0, 1, 0, 0);
    gcall(ctx, base, A_GXSetZMode, 3, 1, 3, 1);
    gcall(ctx, base, A_GXSetZCompLoc, 1, 0);
    gcall(ctx, base, A_GXSetCullMode, 1, 0);
    gcall(ctx, base, A_GXSetColorUpdate, 1, 1);
    gcall(ctx, base, A_GXInitTexObj, 8, texobj, tex, (uint32_t)w, (uint32_t)h, 5, wrap, wrap, 0);   /* RGB5A3; 0 clamp, 1 repeat */
    ctx->f[1].d = 0.0; ctx->f[2].d = 0.0; ctx->f[3].d = 0.0;
    gcall(ctx, base, A_GXInitTexObjLOD, 8, texobj, 0, 0, 0, 0, 0, 0, 0);
    gcall(ctx, base, A_GXLoadTexObj, 2, texobj, 0);
    gcall(ctx, base, A_GXLoadPosMtxImm, 2, SW_MTX, 0);
    gcall(ctx, base, A_GXSetCurrentMtx, 1, 0);
}
static void quad(float x0, float y0, float x1, float y1, float z, float u0, float v0, float u1, float v1, float th) {
    float eu = 0.05f / 256.0f, ev = 0.05f / th;                         /* (as smb3_stage.c: off the atlas tiles' edges) */
    if (u1 > u0 + eu * 2) { u0 += eu; u1 -= eu; }
    if (v1 > v0 + ev * 2) { v0 += ev; v1 -= ev; }
    const float q[4][5] = {{x0, y0, z, u0, v0}, {x1, y0, z, u1, v0}, {x1, y1, z, u1, v1}, {x0, y1, z, u0, v1}};
    for (int i = 0; i < 4; i++) for (int j = 0; j < 5; j++) gx_fifo_write(fbits(q[i][j]), 4);
}
static void proc_draw(ppc_context *ctx, uint8_t *base) {
    if (!smw_stage_on() || !L.placed) return;
    uint32_t cam = gcall(ctx, base, A_GET_CAMERA_BY_ID, 1, gcall(ctx, base, A_GET_CUR_CAMERA, 0));
    if (!cam) return;
    W32(SW_CAMERA, cam); gcall(ctx, base, A_GET_CAMERA_MTX, 2, SW_CAMERA, SW_MTX);
    if (!tex_ready) { tex_upload(); gcall(ctx, base, A_GXInvalidateTexAll, 0); }   /* (the pictures are new at the same addresses: the texture cache told, as smb3_stage.c's status bar) */
    float zt = pz - 400.0f, zb = pz - 410.0f;
    /* layer 2, behind: at half the camera's speed from where SMW had it, repeated across */
    uint32_t bp = R32(BG_PARAM_P);
    float sw = bp ? RF(bp + 64) : 416, sh = bp ? RF(bp + 68) : 240, cx = bp ? RF(bp + 56) - L.lx : 0, cy = bp ? -RF(bp + 60) - L.ly : 0;
    gx_setup(ctx, base, SW_BGOBJ, SW_BGTEX, L.bg_w, L.bg_h, 1);
    {   /* (the background's pixel at the screen's top left: SMW's 224 lines kept to its bottom - an
           NSMBW screen taller than SMW's shows more above, not the tilemap below SMW's picture) */
        float bx = L.bg_x0 + (cx - L.l1_x0) * 0.5f, by = L.bg_y0 + (cy + sh - 224 - L.l1_y0) * 0.5f + 224 - sh;
        float wx0 = L.lx + cx - 64, wy0 = L.ly + cy - 64, wx1 = wx0 + sw + 128, wy1 = wy0 + sh + 128;   /* (a margin round the screen) */
        float u0 = (bx - 64) / L.bg_w, v0 = (by - 64) / L.bg_h, u1 = u0 + (sw + 128) / L.bg_w, v1 = v0 + (sh + 128) / L.bg_h;
        gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 4);
        const float q[4][5] = {{wx0, -wy0, zb, u0, v0}, {wx1, -wy0, zb, u1, v0}, {wx1, -wy1, zb, u1, v1}, {wx0, -wy1, zb, u0, v1}};
        for (int i = 0; i < 4; i++) for (int j = 0; j < 5; j++) gx_fifo_write(fbits(q[i][j]), 4);
    }
    /* layer 1: the tiles on screen (and a screen either side) */
    gx_setup(ctx, base, SW_TEXOBJ, SW_TEX, 256, tex_h, 0);
    int c0 = (int)floorf(cx / 16) - 16, c1 = (int)ceilf((cx + sw) / 16) + 16; if (c0 < 0) c0 = 0; if (c1 > L.w) c1 = L.w;
    int n = 0; for (int r = 0; r < LH; r++) for (int c = c0; c < c1; c++) n += L.tile[r * L.w + c] != 0x25;
    if (n) {
        gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 4 * n);
        for (int r = 0; r < LH; r++) for (int c = c0; c < c1; c++) {
            uint16_t t = L.tile[r * L.w + c]; if (t == 0x25) continue;      /* (SMW's empty tile) */
            int sl = L.slot[t] < 0 ? 0 : L.slot[t];
            float u0 = (sl % 16) * 16 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h;
            float x0 = L.lx + c * 16, y0 = -(L.ly + r * 16), x1 = x0 + 16, y1 = -(L.ly + r * 16 + 16);
            quad(x0, y0, x1, y1, zt, u0, v0, u0 + 16 / 256.0f, v0 + 16 / (float)tex_h, (float)tex_h);
        }
    }
    gcall(ctx, base, A_G3D_INVALIDATE, 1, 0x7FF);
}
static void native_dtor(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }
static void native_draw_opa(ppc_context *ctx, uint8_t *base) { proc_draw(ctx, base); }
static void native_draw_xlu(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }
static void proc_enter(ppc_context *ctx, uint8_t *base) {
    extern uint64_t g_frames_presented; static uint64_t entered = ~0ull;
    if (entered == g_frames_presented) return;
    static int init;
    if (!init) {
        init = 1;
        rt_register_native(N_SW_DTOR, native_dtor); rt_register_native(N_SW_DRAW_OPA, native_draw_opa); rt_register_native(N_SW_DRAW_XLU, native_draw_xlu);
        const uint32_t vt[8] = {0, 0, N_SW_DTOR, A_LEAF_GETTYPE, A_LEAF_FREE, A_LEAF_ENTRY, N_SW_DRAW_OPA, N_SW_DRAW_XLU};
        for (int i = 0; i < 8; i++) W32(SW_VTABLE + i * 4, vt[i]);
    }
    static uint32_t proc_scene;
    if (proc_scene != R32(BG_GM)) {
        W32(SW_PROC, SW_VTABLE); W32(SW_PROC + 4, 0);
        if (!gcall(ctx, base, A_PROC_SETUP, 3, SW_PROC, 0, 0)) { rt_log("smw", "stage: draw proc setup failed"); return; }
        proc_scene = R32(BG_GM);
    }
    entered = g_frames_presented;
    gcall(ctx, base, A_LEAF_ENTRY, 1, SW_PROC);
}
void smw_stage_draw_any(ppc_context *ctx, uint8_t *base) {
    if (smw_stage_on() && L.placed) proc_enter(ctx, base);
}
static void empty_course(void) {
    uint32_t tms = R32(BG_TILEMAPS), area = R8(R32(BG_AREA) + 4622);
    for (int layer = 0; layer < 3; layer++) {
        uint32_t tm = R32(tms + area * 12 + 4 * layer + 52);
        if (!tm) continue;
        for (int b = 0; b < 256; b++) { uint32_t p = R32(tm + 4 * b + 4); if (p >= 0x80000000u && p < 0x94000000u) for (int i = 0; i < 256; i++) W16(p + 2 * i, 0); }
    }
}
/* from dAcPy_c::draw (rt_retro.c), each player each frame: the level placed at player 1's first
   appearance, where SMW starts Mario - his column, on the first ground at or below him */
void smw_stage_player_draw(ppc_context *ctx, uint8_t *base, uint32_t pl) {
    if (!smw_stage_on()) return;
    pz = RF(pl + PL_POS + 8);
    if (L.placed && L.scene != R32(BG_GM)) L.placed = 0;                 /* (a new stage scene: placed afresh) */
    if (L.placed && (int8_t)R8(pl + PL_PLR_NO) == 0) { p1.on = 1; p1.y = -RF(pl + PL_POS + 4) - L.ly; }
    {   const char *e = getenv("SMW_STAGE_TEST_EXIT");                 /* (testing: "frames:kind,..." - frames after each placing, NSMBW's stage exit of that kind, as its pause menu / a death ask it) */
        static int used, since, gen = -1;
        if (e && L.placed && (int8_t)R8(pl + PL_PLR_NO) == 0 && !leaving) {
            if (gen != stage_gen) { gen = stage_gen; since = 0; }
            const char *q = e; for (int i = 0; i < used && q; i++) { q = strchr(q, ','); if (q) q++; }
            int at, kind; if (q && sscanf(q, "%d:%d", &at, &kind) == 2 && ++since == at) {
                used++; rt_log("smw", "stage: test exit (kind %d)", kind);
                gcall(ctx, base, A_STAGE_NEXT_SCENE, 4, 3, 0, (uint32_t)kind, kind == 1 ? 2 : 1); } } }
    if (L.placed && L.side_exit && L.edges && leave_mode < 0 && !leaving) {   /* (a side exit: a player off the screen's side - SMW's map, as SubSideExit) */
        float x = RF(pl + PL_POS);
        if (x < L.edge0 + 22 || x > L.edge1 - 22) {                     /* (NSMBW keeps a player some 19 units inside its camera: at its side) */
            rt_log("smw", "stage: a player off the screen's side (x %.1f, screen %.1f-%.1f): the side exit", x, L.edge0, L.edge1);
            leave_mode = 0;
            gcall(ctx, base, A_STAGE_NEXT_SCENE, 4, 3, 0, 2, 5);             /* (NSMBW's own way out of a course: its wipe, then the hook above) */
        }
    }
    if (L.placed && (int8_t)R8(pl + PL_PLR_NO) == 0 && getenv("SMW_STAGE_TRACE")) {   /* (testing: player 1's place, each 10 frames) */
        static int n; if (++n % 10 == 0) { float x = RF(pl + PL_POS) - L.lx, y = -RF(pl + PL_POS + 4) - L.ly; rt_log("smw", "trace: player 1 at %.1f, %.1f (column %d, row %.2f)", x, y, (int)floorf(x / 16), y / 16); } }
    if (!L.placed) {
        float px = RF(pl + PL_POS), py = RF(pl + PL_POS + 4);
        int col = (L.sx + 8) / 16; if (col < 0 || col >= L.w) col = 2;
        { const char *e = getenv("SMW_STAGE_TEST_X"); if (e && atoi(e) > 0 && atoi(e) < L.w) col = atoi(e); }   /* (testing: that column) */
        int g = (L.sy + 16) / 16; if (g < 0) g = 0;
        while (g < LH && !tile_solid(L.tile[g * L.w + col])) g++;
        if (g >= LH) { g = LH - 1; while (g > 0 && tile_solid(L.tile[(g - 1) * L.w + col])) g--; }
        L.lx = px - (col * 16 + 8); L.ly = -py - g * 16;
        L.lx = floorf(L.lx / 16.0f + 0.5f) * 16.0f; L.ly = ceilf(L.ly / 16.0f) * 16.0f;   /* (on NSMBW's 16-unit grid: as smb3_stage.c) */
        L.placed = 1; L.scene = R32(BG_GM);
        empty_course();
        rt_log("smw", "stage: player 1 at (%.1f, %.1f): SMW level %02X placed at (%.1f, %.1f): column %d, ground row %d (SMW's start %d, %d)", px, py, L.level, L.lx, L.ly, col, g, L.sx, L.sy);
    }
    proc_enter(ctx, base);
}
