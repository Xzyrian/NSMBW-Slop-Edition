/* smb3_main.c - SMB3 in the runtime: runs the recompiled game (nes_cpu.c) a frame at a time,
 * gives it player 1's buttons, draws its screen, keeps its save files. See smb3.h.
 * (Online play: SMB3 isn't part of the runtime's save states - the 6502 runs in a coroutine of
 * its own - so it can't be played online yet.) */
#include "rt.h"
#include "smb3.h"
#include "smb3_save.h"
#include "nes.h"
#include "nes_apu.h"
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#define MKDIR(p) _mkdir(p)
#else
#include <sys/stat.h>
#define MKDIR(p) mkdir(p, 0755)
#endif

extern const uint8_t smb3_rom[];                 /* out/smb3_rom.c */
extern const uint32_t smb3_rom_size;
extern int smb3_start_at_map;                    /* smb3_game.c */

static int active, paused, quit_req, tex, cur_file;
static uint32_t remote;
static uint64_t frames;
static char status[200];

static void on_log(const char *m) { rt_log("smb3", "%s", m); }

/* ------------------------------------------------------------------ save files: <game>/smb3/file<N>.sav */
static void file_path(int f, char *out, int n) { snprintf(out, n, "%s/smb3/file%d.sav", g_root, f + 1); }
static smb3_save_t loaded;
static struct { int known, has; char text[32]; } summary[3];
static int read_file(int f, smb3_save_t *s) {
    char p[1200]; file_path(f, p, sizeof p);
    FILE *fp = fopen(p, "rb"); if (!fp) return 0;
    int ok = fread(s, 1, sizeof *s, fp) == sizeof *s && !memcmp(s->magic, SMB3_SAVE_MAGIC, 8);
    fclose(fp);
    return ok;
}
const char *smb3_file_summary(int f) {
    if (f < 0 || f > 2) return NULL;
    if (!summary[f].known) {
        static smb3_save_t s;
        summary[f].known = 1; summary[f].has = read_file(f, &s);
        if (summary[f].has) snprintf(summary[f].text, sizeof summary[f].text, "World %d", s.world + 1);
    }
    return summary[f].has ? summary[f].text : NULL;
}
/* the File Select (rt_gamesetup.c): a file's world (0-8) and lives - 0 = no file; Copy and
   Delete on SMB3's files */
int smb3_file_info(int f, int *world, int *lives) {
    static smb3_save_t s;
    if (f < 0 || f > 2 || !read_file(f, &s)) return 0;
    *world = s.world; *lives = s.lives[0];
    return 1;
}
int smb3_file_copy(int from, int to) {
    static smb3_save_t s;
    if (from < 0 || from > 2 || to < 0 || to > 2 || from == to || !read_file(from, &s)) return 0;
    char dir[1100]; snprintf(dir, sizeof dir, "%s/smb3", g_root); MKDIR(dir);
    char p[1200], tmp[1210]; file_path(to, p, sizeof p); snprintf(tmp, sizeof tmp, "%s.new", p);
    FILE *fp = fopen(tmp, "wb");
    int ok = fp && fwrite(&s, 1, sizeof s, fp) == sizeof s;
    if (fp) ok = !fclose(fp) && ok;
    if (ok) { remove(p); ok = !rename(tmp, p); }
    summary[to].known = 0;
    rt_log("smb3", "file %d copied to file %d: %s", from + 1, to + 1, ok ? "ok" : "FAILED");
    return ok;
}
int smb3_file_delete(int f) {
    if (f < 0 || f > 2) return 0;
    char p[1200]; file_path(f, p, sizeof p);
    int ok = !remove(p);
    summary[f].known = 0;
    rt_log("smb3", "file %d deleted%s", f + 1, ok ? "" : " (there was none)");
    return ok;
}
static int save_to(int file);
int smb3_save(void) {
    if (!active || status[0]) return 0;
    return save_to(cur_file);
}
/* (smb3_stage.c's map: its game - the same NES - to the file it came from) */
int smb3_save_file(int file) { return file >= 0 && file < 3 && save_to(file); }
static int save_to(int cur_file) {
    static smb3_save_t s; smb3_save_capture(&s);
    char dir[1100]; snprintf(dir, sizeof dir, "%s/smb3", g_root); MKDIR(dir);
    char p[1200], tmp[1210]; file_path(cur_file, p, sizeof p); snprintf(tmp, sizeof tmp, "%s.new", p);
    FILE *fp = fopen(tmp, "wb");
    int ok = fp && fwrite(&s, 1, sizeof s, fp) == sizeof s;
    if (fp) ok = !fclose(fp) && ok;
    if (ok) { remove(p); ok = !rename(tmp, p); }
    summary[cur_file].known = 0;
    rt_log("smb3", "save file %d: %s (World %d%s)", cur_file + 1, ok ? "saved" : "FAILED", s.world + 1, smb3_on_map() ? ", map" : ", in a level: back on its square");
    return ok;
}

/* ------------------------------------------------------------------ running */
/* the Wii Remote held sideways (as NSMBW): d-pad turned, 2 = A (jump), 1 = B (run), - Select.
   + is the pause menu (rt_gamesetup.c), not SMB3's Start. */
static uint8_t pad_of(uint32_t b) {
    uint8_t p = 0;
    if (b & 0x0008) p |= NES_LEFT;  if (b & 0x0004) p |= NES_RIGHT;
    if (b & 0x0002) p |= NES_UP;    if (b & 0x0001) p |= NES_DOWN;
    if (b & (0x0100 | 0x0800)) p |= NES_A;
    if (b & (0x0200 | 0x0400)) p |= NES_B;
    if (b & 0x1000) p |= NES_SELECT;
    return p;
}
uint8_t smb3_pad(uint32_t b) { return pad_of(b); }                    /* (smb3_stage.c's map) */
int smb3_read_save(int f, smb3_save_t *s) { return f >= 0 && f < 3 && read_file(f, s); }
void smb3_enter(int file) {
    status[0] = 0; paused = 0; quit_req = 0;
    cur_file = file >= 0 && file < 3 ? file : 0;
    if (!nes_load(smb3_rom, smb3_rom_size)) { snprintf(status, sizeof status, "The SMB3 ROM is not usable"); rt_log("smb3", "%s", status); active = 1; return; }
    nes_set_log(on_log);
    smb3_start_at_map = 1;
    smb3_load_from = read_file(cur_file, &loaded) ? &loaded : NULL;
    nes_reset();
    active = 1; frames = 0; remote = 0;
    rt_log("smb3", "enter: file %d, %s", cur_file + 1, smb3_load_from ? "continuing" : "new game (World 1)");
    if (smb3_load_from) rt_log("smb3", "  World %d, lives %d", loaded.world + 1, loaded.lives[0]);
}
void smb3_input(uint32_t b) { remote = b; }
void smb3_frame(void) {
    if (!active || paused || status[0]) return;
    nes_set_buttons(0, pad_of(remote));
    nes_run_frame();
    frames++;
    if (nes_error()) { snprintf(status, sizeof status, "SMB3 stopped: %s", nes_error()); rt_log("smb3", "%s (frame %llu)", status, (unsigned long long)frames); }
}
void smb3_draw(void) {
    ui_rect(0, 0, 640, 480, 0x000000FFu);
    const uint32_t *fb = nes_framebuffer();
    if (!tex) tex = ui_register_texture(fb, 256, 240);
    if (tex) { ui_update_texture(tex, fb, 256, 240); ui_image(tex, 64, 0, 512, 480, 0, 0, 1, 1, paused ? 0x909090FFu : 0xFFFFFFFFu); }   /* (2x, square pixels; dimmed while paused) */
}
/* SMB3's sound instead of the game's (the menu music); silent while paused */
void smb3_audio(int16_t *lr, int n) {
    if (!active || paused || status[0]) { memset(lr, 0, (size_t)n * 4); return; }
    apu_pull(lr, n, rt_setting("smb3_volume", 100));
}
void smb3_set_paused(int on) { if (on != paused) rt_log("smb3", "%s", on ? "paused" : "continue"); paused = on; }
int smb3_paused(void) { return active && paused; }
void smb3_quit(void) {
    if (!active) return;
    active = 0; paused = 0; quit_req = 1;
    rt_log("smb3", "quit after %llu frames", (unsigned long long)frames);
}
int smb3_take_quit(void) { int q = quit_req; quit_req = 0; return q; }
int smb3_active(void) { return active; }
const char *smb3_status(void) { return status[0] ? status : NULL; }
void smb3_presence(char *out, int n) {
    if (status[0]) snprintf(out, n, "Super Mario Bros. 3");
    else if (smb3_on_map()) snprintf(out, n, "SMB3: World %d map", smb3_world());
    else snprintf(out, n, "SMB3: World %d", smb3_world());
}
