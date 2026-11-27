/* smb3_map.inc - SMB3's world map with the NSMBW players on it (included by smb3_stage.c).
 *
 * The map is SMB3's own: the recompiled game (one NES, kept running between levels) plays the map
 * - its paths, panels, Hammer Bros, items, completions, lives - fed player 1's buttons a frame at a
 * time. What it draws (its background and its sprites, the marker taken out) goes into the stage's
 * 3D scene as one textured plane, 1 NES pixel = 1 unit; the NSMBW players stand on it as their 3D
 * models: player 1 where SMB3's marker is, the others along the path behind (as NSMBW's own map
 * players follow the leader). Their own execute does not run on the map (rt_retro.c): no physics,
 * no inputs; their model's animation is played here (wait, walk).
 *
 * A panel entered: SMB3 loads its level (run on unseen until it is on screen), the stage takes it
 * as it takes 1-1 (level_load), and NSMBW's stage starts on it. The level's end goes back into
 * SMB3: Map_ReturnStatus (0 cleared, else a death: SMB3 takes the life and the panel stays), then
 * Level_ExitToMap, and SMB3 runs on to its map. SMB3's lives, score, coins and cards follow the
 * stage's (NSMBW's lives: rule 1 of CHARACTERS_AND_GAMES.md).
 *
 * settings.ini smb3_map = 0 (or SMB3_STAGE_NO_MAP=1): no map, 1-1 again after each end, as before.
 */
#define MAP_TEX         SM_TEX                   /* SMB3's picture: 256 x 240 RGB5A3 (120 KB), in the level atlas's place (the
                                                    renderer re-reads textures only in MEM1 / MEM2; a level loads its atlas again) */
#define MAP_TEXOBJ      (SM_MEM + 0x3FC00)       /* (its GXTexObj) */
#define MAP_RUN_MAX     1200                     /* (frames SMB3 may take to bring a level / the map up, unseen) */
static int map_enabled(void) { return !getenv("SMB3_STAGE_NO_MAP") && rt_setting("smb3_map", 1); }
static uint8_t S3(uint16_t a) { return a < 0x800 ? nes_ram_ptr()[a] : a >= 0x6000 ? nes_wram_ptr()[a - 0x6000] : 0; }
static void S3W(uint16_t a, uint8_t v) { if (a < 0x800) nes_ram_ptr()[a] = v; else if (a >= 0x6000) nes_wram_ptr()[a - 0x6000] = v; }
#include "smb3_syms.h"                         /* (out/: the disassembly's addresses) */
#define MAP_MARKER_OAM       0x0284              /* (Map_DrawPlayer: Sprite_RAM + $84..$93, the marker's four sprites) */
enum { MP_OFF, MP_MAP, MP_LEVEL };
static struct {
    int session;                                 /* the NES runs SMB3's game (from the file), map and levels */
    int ending;                                  /* (a level's end handed to SMB3: no second one until the next stage scene) */
    int special;                                 /* (SMB3 is on a Toad House / bonus game / card game screen: played by SMB3 itself, on the map plane) */
    int phase;                                   /* MP_MAP: on the map; MP_LEVEL: a stage on SMB3's level */
    int next;                                    /* (what the next stage scene is: MP_MAP / MP_LEVEL) */
    int shown;                                   /* (the stage scene now: MP_MAP / MP_LEVEL) */
    int tex_ok; uint64_t tick_frame;
    struct { float x, y; } trail[256]; int trail_n;   /* (player 1's path: the others follow it) */
    struct { int anim; float lx, ly; } pl[8];
    float fy;                                    /* (marker's feet below World_Map_Y) */
} MP;
uint8_t smb3_pad(uint32_t buttons);              /* smb3_main.c: the Wii Remote (sideways) as the NES pad */
int smb3_read_save(int file, smb3_save_t *s);    /* smb3_main.c */
int smb3_save_file(int file);                    /* smb3_main.c */
int rt_smb3_file(void);                          /* rt_gamesetup.c: the SMB3 file chosen */
extern uint32_t g_pad0_buttons;                  /* rt_menu.c: player 1's buttons this frame */
static uint32_t map_fb[256 * 240] RT_LOCAL;   /* (SMB3's map picture, as last drawn on the map) */
static int map_on(void) { return MP.shown == MP_MAP; }
static int map_special(void) { return MP.special; }
static int map_session_on(void) { return MP.session; }
static int map_shown_level(void) { return MP.session && MP.shown == MP_LEVEL; }
static void map_session_stop(void) { MP.session = 0; MP.next = MP.shown = MP_OFF; MP.phase = MP_OFF; }
/* (a stage scene begins: what it shows is what was asked for it) */
static void map_apply_next(void) {
    if (!MP.session) MP.next = MP_OFF;
    MP.shown = MP.next; MP.phase = MP.next;
    MP.tex_ok = 0; MP.trail_n = 0; MP.ending = 0; MP.special = 0;
}

/* ---- the bonus rooms' Mario: the user's picture (ui/graphics/smb3/marioportrait.png) in place of
   SMB3's big Mario sprite - the Spade game's and N-Spade's intro (tilesets 15 / 16, not the
   roulette: Raster_Effect $60). His six sprites (Player_Draw: Sprite_RAM + Player_SprOff, 8 x 16
   each) are taken out of SMB3's picture before it is shown, and the picture is drawn over the box
   they made, standing on its bottom, as tall as it */
#define PORT_TEX    (SM_MEM + 0x1F000)           /* (64 x 96 RGB5A3, 12 KB: on the map, the atlas's room past SMB3's picture) */
#define PORT_TEXOBJ (SM_MEM + 0x3FE00)
#define PORT_W 64
#define PORT_H 96
static struct { int loaded, ok, on, found, logged, shade; float aspect; int x0, y0, x1, y1; } PT;
static uint32_t PT_img[PORT_W * PORT_H];          /* (the picture, 0xAARRGGBB, as loaded) */
uint8_t ppu_peek_pal(int i);
static void portrait_load(void) {
    if (PT.loaded) return;
    PT.loaded = 1;
    char path[1200]; snprintf(path, sizeof path, "%s/ui/graphics/smb3/marioportrait.png", g_root);
    int w = 0, h = 0; uint32_t *px = ui_load_png(path, &w, &h);
    if (!px || w < 1 || h < 1) { rt_log("smb3", "map: %s can't be read - SMB3's Mario stays in the bonus rooms", path); free(px); return; }
    /* fitted into 64 x 96 (its height, centred), each texel the average of the pixels it covers
       (colour weighted by alpha), then RGB5A3 in 4 x 4 blocks */
    float sc = (float)PORT_H / h; if (w * sc > PORT_W) sc = (float)PORT_W / w;
    float ox = (PORT_W - w * sc) * 0.5f, oy = PORT_H - h * sc;
    PT.aspect = (float)PORT_W / PORT_H;
    uint32_t *img = PT_img;
    for (int ty = 0; ty < PORT_H; ty++) for (int tx = 0; tx < PORT_W; tx++) {
        int sx0 = (int)((tx - ox) / sc), sx1 = (int)((tx + 1 - ox) / sc), sy0 = (int)((ty - oy) / sc), sy1 = (int)((ty + 1 - oy) / sc);
        double r = 0, g = 0, b = 0, a = 0; int n = 0;
        for (int y = sy0; y < sy1 || y == sy0; y++) for (int x = sx0; x < sx1 || x == sx0; x++) {
            n++; if (x < 0 || y < 0 || x >= w || y >= h) continue;
            uint32_t c = px[(size_t)y * w + x]; double al = (c >> 24) / 255.0;
            a += al; r += al * ((c >> 16) & 255); g += al * ((c >> 8) & 255); b += al * (c & 255);
        }
        uint32_t o = 0;
        if (a > 0 && n) { o = (uint32_t)(a / n * 255.0 + 0.5) << 24 | (uint32_t)(r / a) << 16 | (uint32_t)(g / a) << 8 | (uint32_t)(b / a); }
        img[ty * PORT_W + tx] = o;
    }
    free(px);
    PT.ok = 1; PT.shade = -1;
    rt_log("smb3", "map: the bonus rooms' Mario picture %dx%d, kept at %dx%d", w, h, PORT_W, PORT_H);
}
/* the picture into the texture at a shade of SMB3's palette fade (0 its colours ... 4 black) */
static void portrait_upload(int shade) {
    static const float k[5] = {1.0f, 0.70f, 0.45f, 0.22f, 0.0f};
    float m = k[shade < 0 ? 0 : shade > 4 ? 4 : shade];
    uint32_t at = PORT_TEX;
    for (int by = 0; by < PORT_H; by += 4) for (int bx = 0; bx < PORT_W; bx += 4)
        for (int y = 0; y < 4; y++) for (int x = 0; x < 4; x++) {
            uint32_t c0 = PT_img[(by + y) * PORT_W + bx + x]; int al = c0 >> 24;
            uint32_t c = (uint32_t)al << 24 | (uint32_t)(((c0 >> 16) & 255) * m) << 16 | (uint32_t)(((c0 >> 8) & 255) * m) << 8 | (uint32_t)((c0 & 255) * m);
            uint16_t v = al >= 0xF0 ? (uint16_t)(0x8000 | ((c >> 19) & 31) << 10 | ((c >> 11) & 31) << 5 | ((c >> 3) & 31))
                                    : (uint16_t)((al >> 5) << 12 | ((c >> 20) & 15) << 8 | ((c >> 12) & 15) << 4 | ((c >> 4) & 15));
            W16(at, v); at += 2;
        }
    gx_mark_dirty(PORT_TEX, PORT_W * PORT_H * 2);
    PT.shade = shade;
}
/* how far SMB3's fade has the picture (Palette_DoFadeIn / _DoFadeOut: $10 a step from Pal_Data,
   the target, down to black $0F): the most steps any bright colour is below its target, 0-4 */
static int portrait_fade(void) {
    int best = 0;
    for (int i = 0; i < 32; i++) {
        uint8_t t = S3((uint16_t)(SMB3_Pal_Data + i)), c = ppu_peek_pal(i);
        if (t < 0x10 || (t & 0x0F) >= 0x0D) continue;                  /* (dark targets say little) */
        int st = (c & 0x0F) >= 0x0D ? (t >> 4) + 1 : (t >> 4) - (c >> 4);
        if (st > best) best = st;
    }
    return best > 4 ? 4 : best;
}
/* (each frame SMB3 runs on a bonus screen) where its Mario is. He's no sprite there but a 3x4 block of
   16x16 BG tiles in the room's layout (LoadLevel_BonusPlayer, prg022: Player_BonusTiles_Big/Raccoon/
   Small, the top-left one always TILE15_BRICKBG): found by his head (HEADL $43, HEADM $44, HEADR $45 -
   or the small one's TILE15_PLAYERSM_TOP $4A) in Tile_Mem; on screen at his column*16 - Horz_Scroll
   and his row*16 - (Vert_Scroll + 1) (the room doesn't scroll: $EF, its bottom half) */
static void portrait_take_mario(void) {
    PT.on = 0; PT.found = 0;
    int ts = S3(SMB3_Level_Tileset);
    if (!(ts == 15 || ts == 16) || S3(SMB3_Raster_Effect) == 0x60) return;
    portrait_load(); if (!PT.ok) return;
    uint8_t *r = nes_wram_ptr(); int at = -1;                       /* (Tile_Mem: $6000-$794F, WRAM) */
    for (int i = 16; i + 2 < 0x1950 && at < 0; i++) {
        if (r[i] == 0x43 && r[i + 1] == 0x44 && r[i + 2] == 0x45) at = i - 16;           /* big / raccoon */
        else if (r[i] == 0x4A && r[i + 16] == 0x86 && i % 16 >= 1) at = i - 2 * 16 - 1;  /* small */
    }
    if (at < 0) return;
    int scr = at / 0x1B0, o = at % 0x1B0, row = o / 16, col = o % 16;
    int x = scr * 256 + col * 16 - S3(SMB3_Horz_Scroll), y = row * 16 - (S3(SMB3_Vert_Scroll) + 1);
    if (!PT.logged) { PT.logged = 1; rt_log("smb3", "map: the bonus room's Mario at Tile_Mem +%03X (row %d col %d) - on screen %d,%d (vscroll %02X/%02X)", at, row, col, x, y, S3(SMB3_Vert_Scroll), S3(SMB3_Level_VertScroll)); }
    PT.found = 1; PT.x0 = x; PT.y0 = y; PT.x1 = x + 48; PT.y1 = y + 64;
    /* shown as SMB3's picture is: not while the screen is off (PPU_CTL2's BG), shaded with its fade */
    int sh = (S3(SMB3_PPU_CTL2_Copy) & 0x08) ? portrait_fade() : 4;
    if (sh >= 4) return;
    if (sh != PT.shade) portrait_upload(sh);
    PT.on = 1;
}
/* (SMB3's picture) his tiles painted over with the brick wall behind him - his top-left tile */
static void portrait_hide_mario(uint32_t *fb) {
    if (!PT.found) return;
    for (int ty = 0; ty < 4; ty++) for (int tx = 0; tx < 3; tx++) {
        if (!tx && !ty) continue;
        for (int yy = 0; yy < 16; yy++) for (int xx = 0; xx < 16; xx++) {
            int sx = PT.x0 + xx, sy = PT.y0 + yy, dx = PT.x0 + tx * 16 + xx, dy = PT.y0 + ty * 16 + yy;
            if (sx < 0 || sy < 0 || sx > 255 || sy > 239 || dx < 0 || dy < 0 || dx > 255 || dy > 239) continue;
            fb[dy * 256 + dx] = fb[sy * 256 + sx];
        }
    }
}

static void map_hide_marker(void) { for (int i = 0; i < 16; i += 4) nes_ram_ptr()[MAP_MARKER_OAM + i] = 0xF8; }
/* SMB3 on, unseen, until cond() or MAP_RUN_MAX frames; 0 = it never got there (or stopped) */
static int map_run_until(int (*cond)(void), int extra, const char *what) {
    int i = 0;
    for (; i < MAP_RUN_MAX && !cond(); i++) {
        nes_set_buttons(0, 0); nes_run_frame();
        if (nes_error()) { rt_log("smb3", "map: SMB3 stopped (%s): %s", what, nes_error()); return 0; }
    }
    if (i >= MAP_RUN_MAX) { rt_log("smb3", "map: SMB3 didn't get to %s in %d frames (tileset %d, PPU_CTL2 %02X, Map_Operation %d, frames %llu)", what, MAP_RUN_MAX,
                                   S3(SMB3_Level_Tileset), S3(SMB3_PPU_CTL2_Copy), S3(SMB3_Map_Operation), (unsigned long long)nes_frame_count()); return 0; }
    for (int k = 0; k < extra; k++) { nes_set_buttons(0, 0); nes_run_frame(); }
    map_hide_marker();
    rt_log("smb3", "map: %s after %d frames", what, i + extra);
    return 1;
}
static int cond_on_map(void) { return S3(SMB3_Level_Tileset) == 0 && (S3(SMB3_PPU_CTL2_Copy) & 0x18) == 0x18; }
/* a level up: its tileset in, the screen on, the fade-in done (the palette read for the tiles) */
static int lvl_frames;
static int cond_in_level(void) {
    if (S3(SMB3_Level_Tileset) == 0 || (S3(SMB3_PPU_CTL2_Copy) & 0x18) != 0x18) { lvl_frames = 0; return 0; }
    return ++lvl_frames > 40;
}
/* the game from the file chosen (smb3_main.c's way: smb3_hook_title sets it up), on to its map */
static int map_session_start(void) {
    static smb3_save_t sv;
    if (!nes_load(smb3_rom, smb3_rom_size)) return 0;
    int f = rt_smb3_file();
    smb3_start_at_map = 1; smb3_load_from = smb3_read_save(f, &sv) ? &sv : NULL;
    nes_reset();
    rt_log("smb3", "map: SMB3 file %d, %s", f + 1, smb3_load_from ? "continuing" : "a new game (World 1)");
    MP.session = 1;
    if (!map_run_until(cond_on_map, 2, "the map")) { map_session_stop(); return 0; }
    MP.next = MP_MAP; memcpy(map_fb, nes_framebuffer(), sizeof map_fb);
    /* SMB3's lives: NSMBW's (player 1's rest count) */
    S3W(SMB3_Player_Lives, (uint8_t)R32(MOD_PY_REST));
    return 1;
}
/* the stage's counters <-> SMB3's (score in tens, 3 bytes; Mario's coins; the cards) */
static void map_counters_from_smb3(void) {
    SG.score = (uint32_t)S3(SMB3_Player_Score) << 16 | (uint32_t)S3(SMB3_Player_Score + 1) << 8 | S3(SMB3_Player_Score + 2);
    SG.coins = S3(SMB3_Inventory_Coins);
    for (int i = 0; i < 3; i++) SG.cards[i] = S3(SMB3_Inventory_Cards + i);
}
static void map_counters_to_smb3(void) {
    uint32_t s = SG.score > 999999 ? 999999 : SG.score;
    S3W(SMB3_Player_Score, (uint8_t)(s >> 16)); S3W(SMB3_Player_Score + 1, (uint8_t)(s >> 8)); S3W(SMB3_Player_Score + 2, (uint8_t)s);
    S3W(SMB3_Inventory_Coins, (uint8_t)(SG.coins % 100));
    for (int i = 0; i < 3; i++) S3W(SMB3_Inventory_Cards + i, (uint8_t)SG.cards[i]);
}
static int stage_start_game(ppc_context *ctx, uint8_t *base);
/* the level's end (died: 1 a death, 0 cleared): back into SMB3, out of its level to its map; then
   the next stage scene is the map. 0 = no map (1-1 again, the old way) */
static int map_level_end(ppc_context *ctx, uint8_t *base, int died) {
    if (!MP.session || MP.shown != MP_LEVEL) return 0;
    if (MP.ending) return 1;                                             /* (the end's on its way already: SMB3 was told once) */
    MP.ending = 1;
    map_counters_to_smb3();
    int rest = (int)R32(MOD_PY_REST); if (rest < 0) rest = 0;
    S3W(SMB3_Player_Lives, (uint8_t)(died ? rest + 1 : rest));            /* (a death: SMB3 takes one itself) */
    S3W(SMB3_Map_ReturnStatus, (uint8_t)(died ? 1 : 0));
    S3W(SMB3_Level_ExitToMap, 1);
    { extern uint64_t g_frames_presented; rt_log("smb3", "map: the level %s - back to SMB3's map (frame %llu)", died ? "lost" : "cleared", (unsigned long long)g_frames_presented); }
    if (!map_run_until(cond_on_map, 2, "the map again")) {                /* (SMB3 didn't get back: its map from the file - saved on the way in - not 1-1) */
        rt_log("smb3", "map: SMB3's map again from the file");
        if (!map_session_start()) { map_session_stop(); return 0; }
    }
    memcpy(map_fb, nes_framebuffer(), sizeof map_fb);
    S3W(SMB3_Player_Lives, (uint8_t)rest);
    if (!getenv("SMB3_MAP_NO_SAVE")) smb3_save_file(rt_smb3_file());   /* (the progress kept: NSMBW's pause menu in a stage has no Save) */
    MP.next = MP_MAP;
    return stage_start_game(ctx, base);
}
/* NSMBW's exit from a course asked on the map (its pause menu): the map again */
static int map_again(ppc_context *ctx, uint8_t *base) {
    if (!MP.session) return 0;
    for (int i = 0; i < 8; i++) kept_rest[i] = (int)R32(MOD_PY_REST + 4 * (uint32_t)i);
    keep_rest = 1; MP.next = MP_MAP;
    return stage_start_game(ctx, base);
}
/* a panel entered on the map: SMB3 brings its level up (unseen); the next stage is on it */
static void map_enter_level(ppc_context *ctx, uint8_t *base) {
    rt_log("smb3", "map: a panel entered (World %d, tileset %d)", S3(SMB3_World_Num) + 1, S3(SMB3_Level_Tileset));
    ppu_capture_at(212);                                                 /* (a line of the status bar: its pattern banks) */
    lvl_frames = 0;
    int ok = map_run_until(cond_in_level, 0, "the level");
    ppu_capture_at(-1);
    if (!ok) { map_session_stop(); return; }
    map_counters_from_smb3();
    for (int i = 0; i < 8; i++) kept_rest[i] = (int)R32(MOD_PY_REST + 4 * (uint32_t)i);   /* (going in costs no life) */
    keep_rest = 1;
    MP.next = MP_LEVEL;
    L.ok = 0;                                                            /* (level_load takes the level SMB3 has up) */
    stage_start_game(ctx, base);
}

/* ---- the map's pause menu: NSMBW's own world-map menu (dCourseSelectMenu_c, profile
   COURSE_SELECT_MENU - its layout corseSelectMenu.arc, its cursor, sounds and animations), made
   a child of the stage scene the map is drawn in and driven as dCourseSelectManager_c drives it:
   + opens it (+616 the cursor, +627 0, +625 1: "open", sound 124); it runs itself (up / down,
   2 / A to choose: +626 1, 1 / + to back out) and closes (+625 0). SMB3 waits while it's open.
   Its four: 0 Star Coins and 1 Add/Drop Players (none on SMB3's map yet: back to it), 2 Save
   (the file SMB3 came from), 3 Title Screen. (SMB3's own item window stays on B, as on its map) ---- */
#define PROF_TBL_P        0x8042A3B8u            /* fProfListMg_c::m_data_p */
#define G_PROF_CSMENU     0x809412D0u            /* g_profile_COURSE_SELECT_MENU (d_basesNP .data +3040) */
#define G_SC_STAGE        0x8042A1C8u            /* dScStage_c::m_instance */
#define A_CREATE_BASE     0x8006C6B0u            /* dBase_c::createBase(profile, parent, param, group) */
#define A_BASE_SEARCH     0x80162D00u            /* fBase_c::search(id) */
#define A_SYSTEM_SE       0x80195380u            /* SndAudioMgr::startSystemSe(id, n) */
#define G_SND_MGR         (0x80430000u - 23416)
static struct { uint32_t id, prof; int open, cursor, plus_was; } PM;
static uint32_t pm_menu(ppc_context *ctx, uint8_t *base) { return PM.id ? gcall(ctx, base, A_BASE_SEARCH, 1, PM.id) : 0; }
static int pm_frame(ppc_context *ctx, uint8_t *base) {                 /* 1: the menu's up - SMB3 waits */
    int plus = (g_pad0_buttons & 0x10) != 0, pressed = plus && !PM.plus_was; PM.plus_was = plus;
    uint32_t m = pm_menu(ctx, base);
    if (!m) {
        PM.open = 0;
        if (!PM.prof) { uint32_t t = R32(PROF_TBL_P); for (uint32_t i = 0; t && i < 1200; i++) if (R32(t + 4 * i) == G_PROF_CSMENU) { PM.prof = i; break; } }
        uint32_t sc = R32(G_SC_STAGE);
        if (!PM.prof || !sc) return 0;
        m = gcall(ctx, base, A_CREATE_BASE, 4, PM.prof, sc, 0, 0);
        PM.id = m ? R32(m) : 0;
        rt_log("smb3", "map: NSMBW's map menu (profile %u) %s", PM.prof, m ? "made" : "not made");
        return 0;
    }
    if (!R8(m + 624)) return 0;                                         /* (its layout still loading) */
    if (PM.open) {
        if (R8(m + 625)) return 1;
        PM.open = 0;                                                     /* (closed: chosen, or backed out of) */
        if (!R8(m + 626)) { rt_log("smb3", "map menu: back"); return 0; }
        PM.cursor = (int)R32(m + 616);
        rt_log("smb3", "map menu: %d chosen", PM.cursor);
        switch (PM.cursor) {
        case 2: rt_log("smb3", "map menu: save %s", smb3_save_file(rt_smb3_file()) ? "done" : "FAILED"); break;
        case 3: map_session_stop(); gcall(ctx, base, 0x801017D0u, 2, 0, 0)   /* dScRestartCrsin_c::startTitle */; return 1;
        }
        return 0;
    }
    if (pressed && !MP.special && S3(SMB3_Map_Operation) == 0x0D) {     /* (on the map, Mario standing: as SMB3 lets its own pause) */
        W32(m + 616, (uint32_t)PM.cursor); W8(m + 627, 0); W8(m + 626, 0); W8(m + 625, 1);
        gcall(ctx, base, A_SYSTEM_SE, 3, R32(G_SND_MGR), 124, 1);
        PM.open = 1; rt_log("smb3", "map menu: open");
        return 1;
    }
    return 0;
}

/* ---- each frame on the map: SMB3's frame (player 1's buttons), then the players placed ---- */
static void map_tick(ppc_context *ctx, uint8_t *base) {
    extern uint64_t g_frames_presented;
    if (MP.tick_frame == g_frames_presented || !MP.session || MP.phase != MP_MAP) return;
    MP.tick_frame = g_frames_presented;
    uint32_t tm = R32(0x8042A070u); if (tm) W32(tm + 4, 999u * 4096u);  /* (NSMBW's course timer: no time-up on the map) */
    if (pm_frame(ctx, base)) return;                                     /* (NSMBW's map menu up: SMB3 waits) */
    {   uint8_t pad = smb3_pad(g_pad0_buttons);                         /* (+ is the menu's: SMB3's Start isn't on the pad) */
        nes_set_buttons(0, pad); }
    nes_run_frame();
    if (nes_error()) { rt_log("smb3", "map: SMB3 stopped: %s", nes_error()); MP.session = 0; return; }
    /* Toad Houses (tileset 7), the bonus games (15 spade, 16 N-spade card game) and the 2P battle
       (17) are no levels to stand in: SMB3 plays them itself on its own screen - its Mario, its
       rules - shown on the map plane as the map is, until it's back on its map. (Taken as levels
       before, they couldn't be left: SMB3 never got back to its map and the session ended) */
    if (getenv("SMB3_MAP_TRACE")) {                                    /* (testing: the map's state as it changes) */
        static uint32_t last; uint32_t k = S3(SMB3_Map_Operation) | S3(SMB3_World_Map_Y) << 8 | S3(SMB3_World_Map_X) << 16 | (uint32_t)S3(SMB3_Map_EnterViaID) << 24;
        if (k != last) { last = k; rt_log("smb3", "map trace: op %02X  Y %02X X %02X  via %02X  ts %d  bro %02X,%02X", k & 0xFF, (k >> 8) & 0xFF, (k >> 16) & 0xFF, k >> 24,
                                          S3(SMB3_Level_Tileset), S3(0x7EEB + 2), S3(0x7EF9 + 2)); } }
    {   int ts = S3(SMB3_Level_Tileset);
        int sp = ts == 15 || ts == 16 || ts == 17 || (ts == 7 && getenv("SMB3_MAP_TH_NES"));   /* (a Toad House, 7, is a stage now: smb3_stage_toadhouse.inc - SMB3's own with the test switch) */
        if (sp != MP.special) { MP.special = sp; rt_log("smb3", "map: %s (tileset %d)", sp ? "SMB3 plays a Toad House / bonus screen itself" : "back on the map", ts); }
        if (!sp) map_hide_marker(); else portrait_take_mario();
        if (ts != 0 && !sp) { MP.phase = MP_LEVEL; map_enter_level(ctx, base); return; } }
    memcpy(map_fb, nes_framebuffer(), sizeof map_fb); MP.tex_ok = 0;   /* (the picture: the map's last, kept through the wipe into a level) */
    if (MP.special) portrait_hide_mario(map_fb);
    {   const char *d = getenv("SMB3_MAP_FBDUMP"); static int k;      /* (testing: SMB3's picture every 30 frames) */
        int ev = getenv("SMB3_MAP_FBDUMP_EVERY") ? atoi(getenv("SMB3_MAP_FBDUMP_EVERY")) : 30; if (ev < 1) ev = 1;
        if (d && (k++ % ev) == 0) { char fn[300]; snprintf(fn, sizeof fn, "%s/fb_%05d.ppm", d, k); FILE *f = fopen(fn, "wb");
            if (f) { fprintf(f, "P6 256 240 255\n"); for (int i = 0; i < 256 * 240; i++) { uint8_t c[3] = {(uint8_t)(map_fb[i] >> 16), (uint8_t)(map_fb[i] >> 8), (uint8_t)map_fb[i]}; fwrite(c, 1, 3, f); } fclose(f); } } }
}
/* where SMB3's marker stands (its feet), in the world */
static void map_marker_pos(float *x, float *y) {
    int p = S3(SMB3_Player_Current) & 1;
    int sx = (uint8_t)(S3(SMB3_World_Map_X + p) - S3(SMB3_Horz_Scroll)), sy = S3(SMB3_World_Map_Y + p);
    *x = L.lx + sx + 8; *y = -(L.ly + sy + MP.fy);
}
#define MAP_FOLLOW_GAP  14                       /* (trail points between the players in line) */
static void map_player(ppc_context *ctx, uint8_t *base, uint32_t pl) {
    int n = (int8_t)R8(pl + PL_PLR_NO); if (n < 0 || n > 7) return;
    int lead = sb_first_player(), k = 0;
    for (int i = 0; i < n; i++) if (R32(WP_ENTRY_TABLE + 4 * (uint32_t)i)) k++;   /* (place in line) */
    if (n == lead) k = 0;
    if (n == lead) map_tick(ctx, base);
    if (MP.phase != MP_MAP || MP.special) {                               /* (a level on its way - SMB3's map RAM is the level's now - or a
                                                                             Toad House / bonus game on SMB3's screen: they stay where they were) */
        if (MP.pl[n].lx != 0) { W32(pl + PL_POS, fbits(MP.pl[n].lx)); W32(pl + PL_POS + 4, fbits(MP.pl[n].ly)); }
        for (int i = 0; i < 3; i++) W32(pl + PL_SPEED + 4 * (uint32_t)i, 0);
        return;
    }
    float mx, my; map_marker_pos(&mx, &my);
    if (n == lead && (MP.trail_n == 0 || MP.trail[0].x != mx || MP.trail[0].y != my)) {   /* (the path: a point each time the marker moves) */
        memmove(&MP.trail[1], &MP.trail[0], sizeof MP.trail - sizeof MP.trail[0]);
        MP.trail[0].x = mx; MP.trail[0].y = my; if (MP.trail_n < 256) MP.trail_n++;
    }
    int ti = k * MAP_FOLLOW_GAP; if (ti >= MP.trail_n) ti = MP.trail_n - 1;
    float x = MP.trail_n ? MP.trail[ti].x : mx, y = MP.trail_n ? MP.trail[ti].y : my;
    if (k && ti == MP.trail_n - 1) x += (k & 1 ? -1.0f : 1.0f) * 6.0f * ((k + 1) / 2);   /* (not yet a path behind: beside the leader) */
    float dx = x - MP.pl[n].lx, dy = y - MP.pl[n].ly;
    int moving = MP.pl[n].lx != 0 && (fabsf(dx) > 0.01f || fabsf(dy) > 0.01f);
    MP.pl[n].lx = x; MP.pl[n].ly = y;
    W32(pl + PL_POS, fbits(x)); W32(pl + PL_POS + 4, fbits(y)); W32(pl + PL_POS + 8, fbits(pz + 20.0f * (float)k));
    for (int i = 0; i < 3; i++) W32(pl + PL_SPEED + 4 * (uint32_t)i, 0);
    W32(pl + PL_SPEED_F, 0);
    /* facing: along the way it walks; standing, to the front (SMB3's marker faces you) */
    int16_t ang = 0;
    if (moving) { if (fabsf(dx) >= fabsf(dy)) ang = dx > 0 ? 0x4000 : -0x4000; else ang = dy > 0 ? (int16_t)0x8000 : 0; }
    W16(pl + 0x102, (uint16_t)ang);
    /* (NSMBW's world map shows its Mario from its camera, above and in front: the model leans
       towards ours by that much - only the model; SMB3's map stays flat. SMB3_MAP_TILT: another angle) */
    {   static int tilt = 1; if (tilt == 1) tilt = getenv("SMB3_MAP_TILT") ? (int)strtol(getenv("SMB3_MAP_TILT"), NULL, 0) : -0x1400;
        W16(pl + 0x100, (uint16_t)tilt); }
    if (moving && fabsf(dx) > 0.01f) W8(pl + PL_DIRECTION, dx > 0 ? 0 : 1);   /* (an NES character: drawn by its facing) */
    /* the model: wait / walk (NSMBW's ids 0 and 1), its animation played on (dPyMdlMng_c::play) */
    int want = moving ? 1 : 0;
    uint32_t mdl = R32(R32(pl + 3560) + 4);
    if (mdl && MP.pl[n].anim != want + 1) {
        MP.pl[n].anim = want + 1;
        ctx->f[1].d = ctx->ps1[1] = 1.0; ctx->f[2].d = ctx->ps1[2] = 5.0; ctx->f[3].d = ctx->ps1[3] = 0.0;
        gcall(ctx, base, R32(R32(mdl) + 92), 2, mdl, (uint32_t)want);
    }
    gcall(ctx, base, 0x800D6E90u, 1, pl + 10848);
}

/* ---- the picture: SMB3's screen as a plane in the stage's 3D scene ---- */
static void map_tex_upload(void) {
    const uint32_t *fb = map_fb;
    uint32_t o = MAP_TEX;
    for (int by = 0; by < 240; by += 4) for (int bx = 0; bx < 256; bx += 4)
        for (int y = 0; y < 4; y++) for (int x = 0; x < 4; x++) {
            uint32_t c = fb[(by + y) * 256 + bx + x];
            W16(o, (uint16_t)(0x8000 | ((c >> 19) & 31) << 10 | ((c >> 11) & 31) << 5 | ((c >> 3) & 31))); o += 2;
        }
    gx_mark_dirty(MAP_TEX, 256 * 240 * 2);
    MP.tex_ok = 1; tex_ready = 0;
}
static void map_draw(ppc_context *ctx, uint8_t *base) {
    if (!L.placed) return;
    uint32_t cam = gcall(ctx, base, A_GET_CAMERA_BY_ID, 1, gcall(ctx, base, A_GET_CUR_CAMERA, 0));
    if (!cam) return;
    W32(SM_CAMERA, cam); gcall(ctx, base, A_GET_CAMERA_MTX, 2, SM_CAMERA, SM_MTX);
    if (!tex_h) tex_h = 16;
    gx_setup(ctx, base);
    if (!MP.tex_ok) { map_tex_upload(); gcall(ctx, base, A_GXInvalidateTexAll, 0); }
    gcall(ctx, base, A_GXInitTexObj, 8, MAP_TEXOBJ, MAP_TEX, 256, 240, 5, 0, 0, 0);
    ctx->f[1].d = 0.0; ctx->f[2].d = 0.0; ctx->f[3].d = 0.0;
    gcall(ctx, base, A_GXInitTexObjLOD, 8, MAP_TEXOBJ, 0, 0, 0, 0, 0, 0, 0);
    gcall(ctx, base, A_GXLoadTexObj, 2, MAP_TEXOBJ, 0);
    float z = pz - 400.0f, x0 = L.lx, y0 = -L.ly, x1 = L.lx + 256, y1 = -(L.ly + 240);
    float bu = 0.5f / 256.0f, bv = 0.5f / 240.0f;
    gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 4 * 2);
    /* (around it, out to the widescreen's sides: SMB3's black - the top left pixel's colour) */
    const float q0[4][5] = {{x0 - 4000, y0 + 3000, z - 10, bu, bv}, {x1 + 4000, y0 + 3000, z - 10, bu, bv}, {x1 + 4000, y1 - 3000, z - 10, bu, bv}, {x0 - 4000, y1 - 3000, z - 10, bu, bv}};
    for (int i = 0; i < 4; i++) for (int j = 0; j < 5; j++) gx_fifo_write(fbits(q0[i][j]), 4);
    const float q[4][5] = {{x0, y0, z, 0, 0}, {x1, y0, z, 1, 0}, {x1, y1, z, 1, 1}, {x0, y1, z, 0, 1}};
    for (int i = 0; i < 4; i++) for (int j = 0; j < 5; j++) gx_fifo_write(fbits(q[i][j]), 4);
    if (MP.special && PT.on && PT.ok) {                                  /* (a bonus room: the Mario picture where SMB3's Mario was) */
        gcall(ctx, base, A_GXInitTexObj, 8, PORT_TEXOBJ, PORT_TEX, PORT_W, PORT_H, 5, 0, 0, 0);   /* RGB5A3, clamp */
        ctx->f[1].d = 0.0; ctx->f[2].d = 0.0; ctx->f[3].d = 0.0;
        gcall(ctx, base, A_GXInitTexObjLOD, 8, PORT_TEXOBJ, 1, 1, 0, 0, 0, 0, 0);
        gcall(ctx, base, A_GXLoadTexObj, 2, PORT_TEXOBJ, 0);
        float h = (float)(PT.y1 - PT.y0), wd = h * PT.aspect, cx = (PT.x0 + PT.x1) * 0.5f;
        float px0 = L.lx + cx - wd * 0.5f, px1 = px0 + wd, py0 = -(L.ly + PT.y1 - h), py1 = -(L.ly + PT.y1), pz2 = z + 1.0f;
        gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 4);
        const float pq[4][5] = {{px0, py0, pz2, 0, 0}, {px1, py0, pz2, 1, 0}, {px1, py1, pz2, 1, 1}, {px0, py1, pz2, 0, 1}};
        for (int i = 0; i < 4; i++) for (int j = 0; j < 5; j++) gx_fifo_write(fbits(pq[i][j]), 4);
    }
    gcall(ctx, base, A_G3D_INVALIDATE, 1, 0x7FF);
}
/* the camera: still, on SMB3's screen (its middle; the playfield above the bar) */
static void map_camera(void) {
    uint32_t bp = R32(BG_PARAM_P), bg = R32(0x80429DD0u);
    if (!bp || !bg || !L.placed) return;
    float w = RF(bp + 64), h = RF(bp + 68); if (h < 100 || h > 1000) return;
    float left = L.lx + 128 - w * 0.5f, top = -(L.ly + 120) + h * 0.5f;
    W32(bp + 0x38, fbits(left)); W32(bp + 0x60, fbits(left)); W32(bg + 0x900AC, fbits(left));
    W32(bp + 0x48, fbits(left + w * 0.5f)); W32(bp + 0x50, fbits(left + w * 0.5f));
    W32(bp + 0x3C, fbits(top)); W32(bp + 0x64, fbits(top)); W32(bg + 0x900B0, fbits(top));
    W32(bp + 0x4C, fbits(top - h * 0.5f)); W32(bp + 0x54, fbits(top - h * 0.5f));
}
/* placed: SMB3's screen centred on where the course put player 1 */
static void map_place(float px, float py) {
    L.lx = px - 128; L.ly = -py - 120; L.placed = 1;
    MP.trail_n = 0; memset(MP.pl, 0, sizeof MP.pl);
    if (MP.fy == 0) MP.fy = getenv("SMB3_MAP_FEET") ? (float)atof(getenv("SMB3_MAP_FEET")) : 14.0f;
    empty_course();
    rt_log("smb3", "stage: SMB3 map placed at (%.1f, %.1f): World %d", L.lx, L.ly, S3(SMB3_World_Num) + 1);
}
