/* smw_main.c - SMW in the runtime: runs the recompiled game (snes_cpu.c) a frame at a time,
 * gives it player 1's buttons, draws its screen, keeps its save RAM. See smw.h.
 *
 * Starting a file. SMW chooses a file on its own title menus; Start Game has chosen already, so
 * those menus are passed unseen, by SMW's own code: the game runs (many frames to a drawn one,
 * the screen black) and is answered as a player would - B on the title, the file's line on the
 * file menu (BlinkCursorPos) and B, "1 PLAYER GAME" and B - until it leaves them (game mode $0B:
 * the fade to the map; a new file: the intro). Nothing of SMW is changed for it.
 *
 * Saving. SMW saves itself, into its save RAM, where it asks to (Yoshi's House, castles...): that
 * RAM is the file <game>/smw/smw.srm, written whenever it changes. */
#include "rt.h"
#include "smw.h"
#include "snes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <direct.h>
#define MKDIR(p) _mkdir(p)
#else
#include <sys/stat.h>
#define MKDIR(p) mkdir(p, 0755)
#endif

extern const uint8_t smw_rom[];                  /* out/smw_rom.c */
extern const uint32_t smw_rom_size;

#define SAVE_SIZE 143                            /* (!SaveFileSize: three files, then their copies) */
#define RAM_GAME_MODE 0x0100                     /* (GameMode) */
#define RAM_CURSOR    0x1B92                     /* (BlinkCursorPos) */
#define RAM_SUBMAP    0x1F11                     /* (OWPlayerSubmap) */


static int active, paused, quit_req, tex, cur_file, unseen, menus_seen;
static int held;                                 /* 1: at a level's start, for the NSMBW stage; 2: the stage left, back to the map once the setup scene is up */
static int dark;                                 /* (the screen black until SMW's map fades in: after its menus, after a level) */
static uint32_t remote;
static uint64_t frames;
static char status[200];
static uint8_t srm[0x800], srm_written[0x800];

static void on_log(const char *m) { rt_log("smw", "%s", m); }

/* ------------------------------------------------------------------ the save RAM: <game>/smw/smw.srm */
static void srm_path(char *out, int n) { snprintf(out, n, "%s/smw/smw.srm", g_root); }
static int srm_read(uint8_t *to) {
    char p[1200]; srm_path(p, sizeof p);
    FILE *fp = fopen(p, "rb"); if (!fp) return 0;
    int ok = fread(to, 1, 0x800, fp) == 0x800; fclose(fp);
    return ok;
}
static int srm_write(const uint8_t *from) {
    char dir[1100]; snprintf(dir, sizeof dir, "%s/smw", g_root); MKDIR(dir);
    char p[1200], tmp[1210]; srm_path(p, sizeof p); snprintf(tmp, sizeof tmp, "%s.new", p);
    FILE *fp = fopen(tmp, "wb");
    int ok = fp && fwrite(from, 1, 0x800, fp) == 0x800;
    if (fp) ok = !fclose(fp) && ok;
    if (ok) { remove(p); ok = !rename(tmp, p); }
    return ok;
}
/* a file's data, or NULL: the first of its two copies whose checksum holds (VerifySaveFile) */
static const uint8_t *file_data(const uint8_t *s, int f) {
    for (int copy = 0; copy < 2; copy++) {
        const uint8_t *d = s + (copy * 3 + f) * SAVE_SIZE;
        unsigned sum = (unsigned)(d[SAVE_SIZE - 2] | d[SAVE_SIZE - 1] << 8);
        for (int i = 0; i < SAVE_SIZE - 2; i++) sum = (sum + d[i]) & 0xFFFF;
        if (sum == 0x5A5A) return d;
    }
    return NULL;
}
/* (the card's "World": where the file's player is - Yoshi's Island 1, the Vanilla Dome 3, the Forest
   of Illusion 5, the Valley of Bowser 7, Star World 8, Special 9; the main map's lands as 2) */
static int world_of(const uint8_t *d) {
    static const int W[7] = {2, 1, 3, 5, 7, 9, 8};
    int sub = d[0x1FB8 - 0x1F49] & 7;
    return W[sub < 7 ? sub : 0] - 1;
}
int smw_file_info(int f, int *world, int *lives) {
    static uint8_t s[0x800];
    if (f < 0 || f > 2 || !srm_read(s)) return 0;
    const uint8_t *d = file_data(s, f); if (!d) return 0;
    *world = world_of(d); *lives = 5;                       /* (SMW's files keep no lives: every game starts with 5) */
    return 1;
}
const char *smw_file_summary(int f) {
    static char t[3][40]; static uint8_t s[0x800];
    if (f < 0 || f > 2 || !srm_read(s)) return NULL;
    const uint8_t *d = file_data(s, f); if (!d) return NULL;
    snprintf(t[f], sizeof t[f], "%d exits", d[SAVE_SIZE - 3]);
    return t[f];
}
int smw_file_copy(int from, int to) {
    static uint8_t s[0x800];
    if (from < 0 || from > 2 || to < 0 || to > 2 || from == to || !srm_read(s)) return 0;
    const uint8_t *d = file_data(s, from); if (!d) return 0;
    uint8_t tmp[SAVE_SIZE]; memcpy(tmp, d, SAVE_SIZE);
    memcpy(s + to * SAVE_SIZE, tmp, SAVE_SIZE); memcpy(s + (3 + to) * SAVE_SIZE, tmp, SAVE_SIZE);
    int ok = srm_write(s);
    rt_log("smw", "file %d copied to file %d: %s", from + 1, to + 1, ok ? "ok" : "FAILED");
    return ok;
}
int smw_file_delete(int f) {
    static uint8_t s[0x800];
    if (f < 0 || f > 2 || !srm_read(s)) return 0;
    memset(s + f * SAVE_SIZE, 0, SAVE_SIZE); memset(s + (3 + f) * SAVE_SIZE, 0, SAVE_SIZE);   /* (no checksum holds: empty) */
    int ok = srm_write(s);
    rt_log("smw", "file %d deleted: %s", f + 1, ok ? "ok" : "FAILED");
    return ok;
}
int smw_save(void) {
    if (!active || status[0]) return 0;
    memcpy(srm, snes_sram_ptr(), sizeof srm);
    int ok = srm_write(srm);
    if (ok) memcpy(srm_written, srm, sizeof srm);
    rt_log("smw", "save RAM written: %s", ok ? "ok" : "FAILED");
    return ok;
}

/* ------------------------------------------------------------------ running */
/* the Wii Remote held sideways (as NSMBW): d-pad turned, 2 = B (jump), 1 = Y (run / throw),
   A = A (spin jump), B = X, - = Select. + is the pause menu (rt_gamesetup.c), not SMW's Start. */
static uint16_t pad_of(uint32_t b) {
    uint16_t p = 0;
    if (b & 0x0008) p |= SNES_LEFT;  if (b & 0x0004) p |= SNES_RIGHT;
    if (b & 0x0002) p |= SNES_UP;    if (b & 0x0001) p |= SNES_DOWN;
    if (b & 0x0100) p |= SNES_B;     if (b & 0x0200) p |= SNES_Y;
    if (b & 0x0800) p |= SNES_A;     if (b & 0x0400) p |= SNES_X;
    if (b & 0x1000) p |= SNES_SELECT;
    return p;
}
void smw_enter(int file) {
    status[0] = 0; paused = 0; quit_req = 0;
    cur_file = file >= 0 && file < 3 ? file : 0;
    if (!snes_load(smw_rom, smw_rom_size)) { snprintf(status, sizeof status, "The SMW ROM is not usable"); rt_log("smw", "%s", status); active = 1; return; }
    snes_set_log(on_log);
    if (!srm_read(srm)) memset(srm, 0, sizeof srm);
    memcpy(srm_written, srm, sizeof srm);
    memcpy(snes_sram_ptr(), srm, sizeof srm);
    snes_reset();
    active = 1; frames = 0; remote = 0; unseen = 1; menus_seen = 0; held = 0; dark = 0;
    rt_log("smw", "enter: file %d (%s)", cur_file + 1, file_data(srm, cur_file) ? "continuing" : "new");
}
void smw_input(uint32_t b) { remote = b; }
/* SMW's menus answered (unseen): one frame; 1 = still in them */
static int menus_step(void) {
    uint8_t *w = snes_wram_ptr();
    int gm = w[RAM_GAME_MODE];
    if (frames > 8 && gm >= 0x08 && gm <= 0x0A) menus_seen = 1;           /* (before its RAM is cleared, the game mode is noise) */
    if ((menus_seen && gm >= 0x0B) || frames > 3000) {
        dark = 1;                                            /* (its fade from the title to the map: not shown) */
        rt_log("smw", "menus passed after %llu frames (game mode %02X)", (unsigned long long)frames, gm);
        return 0;
    }
    if (gm == 0x08) w[RAM_CURSOR] = (uint8_t)cur_file;
    if (gm == 0x0A) w[RAM_CURSOR] = 0;                       /* (1 PLAYER GAME) */
    snes_set_buttons(0, (frames & 1) && frames > 8 && gm >= 0x04 && gm <= 0x0A ? SNES_B : 0);   /* (a press every other frame) */
    snes_run_frame(); frames++;
    return 1;
}
/* a level started (game mode $14; not the intro): held there for the NSMBW stage (smw_stage.c) */
int smw_level_held(void) { return active && held == 1 && !status[0]; }
/* the NSMBW stage left (smw_stage.c): SMW leaves its level as it would - exit_mode its
   OWLevelExitMode ($0DD5: $80 no event, as Start + Select or a death; 0 a side exit's), game mode
   $0B (the fade to the map) - from when the setup scene is up again (smw_resume) */
void smw_leave_level(int exit_mode) {
    if (!active || held != 1) return;
    uint8_t *w = snes_wram_ptr();
    w[0x0DD5] = (uint8_t)exit_mode;                          /* (OWLevelExitMode) */
    w[0x0109] = 0;                                           /* (OverworldOverride, as SubSideExit) */
    w[RAM_GAME_MODE] = 0x0B;
    held = 2; dark = 1;
    rt_log("smw", "level %02X left (exit mode %02X): SMW back to its map", w[0x13BF], exit_mode);
}
int smw_resume(void) {                                       /* (rt_gamesetup.c: the setup scene made - SMW on again over it) */
    if (!active || held != 2) return 0;
    held = 0; return 1;
}
/* (rt_menu.c) black over everything: SMW holds a level and NSMBW's stage isn't up yet */
int smw_cover(void) { return active && held && !status[0] && R16(0x80428732u) == 10; }
void smw_frame(void) {
    if (!active || paused || status[0] || held) return;
    if (unseen) {
        for (int i = 0; i < 64 && unseen; i++) { unseen = menus_step(); if (snes_error()) break; }
    } else {
        uint16_t pad = pad_of(remote);
        {   static long t0 = -1; const char *e = getenv("SMW_TEST_PAD");  /* (testing: "frame:hex,..." SNES buttons from that many frames after the menus) */
            if (e) { if (t0 < 0) t0 = (long)frames; long f = (long)frames - t0; uint16_t b = 0;
                for (const char *q = e; *q; ) { long at = strtol(q, (char **)&q, 10); if (*q == ':') q++; long v = strtol(q, (char **)&q, 16); if (*q == ',') q++; if (f >= at) b = (uint16_t)v; }
                pad = b; } }
        snes_set_buttons(0, pad);
        snes_run_frame();
        frames++;
        {   uint8_t *w = snes_wram_ptr();
            if (dark && w[RAM_GAME_MODE] >= 0x0D && w[RAM_GAME_MODE] <= 0x0E) dark = 0;   /* (the map fading in: shown) */
            if (w[RAM_GAME_MODE] == 0x14 && !w[0x0109] && rt_setting("smw_stage", 1)) {   /* (OverworldOverride: the intro stays SMW's) */
                held = 1; rt_log("smw", "level %02X started: held for the NSMBW stage", w[0x13BF]); } }
        if (memcmp(snes_sram_ptr(), srm_written, sizeof srm_written)) {   /* SMW saved: to its file */
            memcpy(srm, snes_sram_ptr(), sizeof srm);
            if (srm_write(srm)) { memcpy(srm_written, srm, sizeof srm); rt_log("smw", "SMW saved (file %d)", cur_file + 1); }
        }
    }
    if (snes_error()) { snprintf(status, sizeof status, "SMW stopped: %s", snes_error()); rt_log("smw", "%s (frame %llu)", status, (unsigned long long)frames); }
}
void smw_draw(void) {
    ui_rect(0, 0, 640, 480, 0x000000FFu);
    if (unseen || dark) return;                              /* (black while its menus are passed, and on to its map) */
    {   const uint8_t *w = snes_wram_ptr(); int gm = w[RAM_GAME_MODE];   /* (a level for the NSMBW stage: SMW's own loading of it not shown) */
        if (gm >= 0x10 && gm <= 0x14 && !w[0x0109] && rt_setting("smw_stage", 1)) return; }
    const uint32_t *fb = snes_framebuffer();
    if (!tex) tex = ui_register_texture(fb, 256, 224);
    /* (the SNES's 8:7 pixels: 224 lines to 480, 256 dots to 627) */
    if (tex) { ui_update_texture(tex, fb, 256, 224); ui_image(tex, 6.5f, 0, 627, 480, 0, 0, 1, 1, paused ? 0x909090FFu : 0xFFFFFFFFu); }
}
void smw_audio(int16_t *lr, int n) { memset(lr, 0, (size_t)n * 4); }   /* (silent: the SPC700 isn't run yet) */
void smw_set_paused(int on) { if (on != paused) rt_log("smw", "%s", on ? "paused" : "continue"); paused = on; }
int smw_paused(void) { return active && paused; }
void smw_quit(void) {
    if (!active) return;
    if (!status[0] && memcmp(snes_sram_ptr(), srm_written, sizeof srm_written)) smw_save();
    active = 0; paused = 0; quit_req = 1;
    rt_log("smw", "quit after %llu frames", (unsigned long long)frames);
}
int smw_take_quit(void) { int q = quit_req; quit_req = 0; return q; }
int smw_active(void) { return active && !held; }
const char *smw_status(void) { return status[0] ? status : NULL; }
void smw_presence(char *out, int n) {
    static const char *const SUB[7] = {"the map", "Yoshi's Island", "the Vanilla Dome", "the Forest of Illusion", "the Valley of Bowser", "Special World", "Star World"};
    if (status[0] || unseen) { snprintf(out, n, "Super Mario World"); return; }
    uint8_t *w = snes_wram_ptr(); int gm = w[RAM_GAME_MODE], sub = w[RAM_SUBMAP] & 7;
    if (gm == 0x0E) snprintf(out, n, "SMW: %s", SUB[sub < 7 ? sub : 0]);
    else if (gm >= 0x11 && gm <= 0x14) snprintf(out, n, "SMW: in a level (%s)", SUB[sub < 7 ? sub : 0]);
    else snprintf(out, n, "Super Mario World");
}
