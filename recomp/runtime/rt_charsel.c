/* rt_charsel.c - the singleplayer character select: a grid of the roster (docs/CHARACTERS.md).
 *
 * NSMBW's character select walks one card through the whole roster with left/right, which gets
 * slow as the roster grows. In singleplayer the card stays, on the left, as the preview (its
 * picture, lives and the 3D figure above it), and this grid, drawn over the screen on the right,
 * picks the character:
 *  - one tile per *family* (rt_chars.c ROSTER .family: Retro Mario SMB1 / SMW / SM64 are Mario's
 *    variants), COLS a row, scrolling by rows past ROWS_SHOWN;
 *  - the d-pad moves (left/right run on through the rows; up/down go by column), held: repeats;
 *    - (minus) steps through the hovered family's variants (the variant row under the preview);
 *  - a Recent row under the grid: the last RECENT characters chosen (settings.ini sp_pick_<id> =
 *    a counter, so it doesn't depend on the roster's order); the cursor starts on the latest;
 *  - 2 / A chooses: the card is moved to the grid's character (rt_chars.c grid_select: one slide)
 *    and chosen there, as its own 2 did. From there the game's flow is unchanged (Start Game; 1
 *    takes the choice back; 1 again goes back to the File Select; + Settings).
 * Input comes from rt_gamesetup.c (gs_filter_buttons) while the select waits for a choice; the
 * game sees no d-pad / - / 2 / A then. Drawn by rt_menu.c (menu_draw), faded with the screen. */
#include "rt.h"
#include <math.h>
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */
extern uint64_t g_frames_presented;

/* rt_chars.c */
int chars_count(void); const char *chars_name(int c); const char *chars_id(int c);
int chars_family(int c); const char *chars_variant(int c); int chars_tile_texture(int c); int chars_of_player(int n);
/* rt_menu.c: the game's font */
void menu_text(float x, float y, float size, const char *s, uint32_t rgba);
float menu_text_width(const char *s, float size);
/* rt_gamesetup.c */
int gs_sp_select_state(void);                   /* 0 not shown, 1 choosing, 2 chosen (Start Game) */
uint32_t gs_sp_select_visit(void);              /* counts the select's openings */
float gs_screen_alpha(void);                    /* 1 shown .. 0 black (the fader) */
float gs_sp_preview_x(void);                    /* the card's middle (overlay x) */

enum { B_LEFT = 0x0001, B_RIGHT = 0x0002, B_DOWN = 0x0004, B_UP = 0x0008, B_PLUS = 0x0010, B_2 = 0x0100, B_1 = 0x0200,
       B_B = 0x0400, B_A = 0x0800, B_MINUS = 0x1000, B_HOME = 0x8000 };
/* the remote held sideways: the d-pad's right is up on the screen */
#define NAV_UP B_RIGHT
#define NAV_DOWN B_LEFT
#define NAV_LEFT B_UP
#define NAV_RIGHT B_DOWN
#define NAV_ALL (B_LEFT | B_RIGHT | B_UP | B_DOWN)

#define COLS 6
#define ROWS_SHOWN 3
#define RECENT 3
#define MAXFAM 64
#define REPEAT_FIRST 18                         /* frames held before a direction repeats */
#define REPEAT_EVERY 5

static int fam[MAXFAM], nfam;                   /* each family's first character, roster order */
static int fam_pick[MAXFAM];                    /* the family's character the tile is on (its variant) */
static int cur;                                 /* the grid's tile */
static int in_recent, rec_sel;                  /* the cursor is on the Recent row: which */
static int recent[RECENT], nrecent;
static int top_row;                             /* (the grid scrolls by rows) */
static int decide_for = -1;                     /* 2 / A pressed for this character (-1 none) */
static uint32_t visit_seen;
static uint32_t held_dir; static uint64_t held_since, held_last;
static uint64_t moved_frame;                    /* (the cursor's little pop) */

static int nrows(void) { return (nfam + COLS - 1) / COLS; }
static int family_index(int c) { int f = chars_family(c); for (int i = 0; i < nfam; i++) if (fam[i] == f) return i; return -1; }
static int members(int f, int *out, int max) {
    int n = 0; for (int c = 0; c < chars_count() && n < max; c++) if (chars_family(c) == fam[f]) out[n++] = c;
    return n;
}
static int target(void) { return in_recent && rec_sel < nrecent ? recent[rec_sel] : fam_pick[cur]; }

/* ---- Recent: settings.ini sp_pick_<id> = the pick's number (higher = later) ---- */
static void recent_load(void) {
    int n = chars_count(), best[RECENT], key[RECENT]; nrecent = 0;
    for (int c = 0; c < n; c++) {
        char k[64]; snprintf(k, sizeof k, "sp_pick_%s", chars_id(c));
        int v = rt_setting(k, 0); if (v <= 0) continue;
        int i = nrecent < RECENT ? nrecent++ : RECENT;                    /* insertion, latest first */
        if (i == RECENT) { if (v <= key[RECENT - 1]) continue; i = RECENT - 1; }
        while (i > 0 && key[i - 1] < v) { key[i] = key[i - 1]; best[i] = best[i - 1]; i--; }
        key[i] = v; best[i] = c;
    }
    for (int i = 0; i < nrecent; i++) recent[i] = best[i];
}
void charsel_note_pick(int c) {                 /* (rt_chars.c initDecidedCharacter, singleplayer) */
    if (c < 0 || c >= chars_count()) return;
    int n = rt_setting("sp_pick_count", 0) + 1;
    char k[64]; snprintf(k, sizeof k, "sp_pick_%s", chars_id(c));
    rt_setting_set("sp_pick_count", n); rt_setting_set(k, n);
}

static void keep_row_shown(void) {
    int r = cur / COLS;
    if (r < top_row) top_row = r;
    if (r >= top_row + ROWS_SHOWN) top_row = r - ROWS_SHOWN + 1;
    if (top_row < 0) top_row = 0;
}
/* a new visit to the select: the families, Recent, the cursor on the latest pick */
static void open_if_new(void) {
    uint32_t v = gs_sp_select_visit();
    if (v == visit_seen && nfam) return;
    visit_seen = v;
    nfam = 0;
    for (int c = 0; c < chars_count() && nfam < MAXFAM; c++) if (chars_family(c) == c) { fam[nfam] = c; fam_pick[nfam] = c; nfam++; }
    recent_load();
    for (int i = nrecent - 1; i >= 0; i--) { int f = family_index(recent[i]); if (f >= 0) fam_pick[f] = recent[i]; }   /* (each family on its latest variant) */
    int start = nrecent ? recent[0] : chars_of_player(0);
    cur = family_index(start); if (cur < 0) cur = 0;
    if (start >= 0) fam_pick[cur] = start;
    in_recent = 0; rec_sel = 0; top_row = 0; decide_for = -1; held_dir = 0;
    keep_row_shown();
    rt_log("charsel", "open: %d families, %d recent, on %s", nfam, nrecent, chars_name(target()));
}

/* the character the card should show (-1: the grid isn't up) - rt_chars.c */
int charsel_target(void) {
    if (!gs_sp_select_state()) return -1;
    open_if_new();
    return nfam ? target() : -1;
}
int charsel_take_decide(void) {
    if (decide_for < 0) return 0;
    int ok = decide_for == target(); decide_for = -1;
    return ok;
}

static void move(uint32_t dir) {
    int col = cur % COLS, r = cur / COLS, last = nrows() - 1;
    if (in_recent) {
        if (dir == NAV_LEFT) rec_sel = (rec_sel + nrecent - 1) % nrecent;
        else if (dir == NAV_RIGHT) rec_sel = (rec_sel + 1) % nrecent;
        else {
            in_recent = 0;
            cur = dir == NAV_UP ? last * COLS + rec_sel : rec_sel;           /* (the column under it, in the last / first row) */
            if (cur >= nfam) cur = nfam - 1;
        }
    } else if (dir == NAV_LEFT) cur = (cur + nfam - 1) % nfam;
    else if (dir == NAV_RIGHT) cur = (cur + 1) % nfam;
    else if (dir == NAV_UP) {
        if (r > 0) cur -= COLS;
        else if (nrecent) { in_recent = 1; rec_sel = col < nrecent ? col : nrecent - 1; }
        else { cur = last * COLS + col; if (cur >= nfam) cur = nfam - 1; }
    } else if (dir == NAV_DOWN) {
        if (r < last) { cur += COLS; if (cur >= nfam) cur = nfam - 1; }
        else if (nrecent) { in_recent = 1; rec_sel = col < nrecent ? col : nrecent - 1; }
        else cur = col;
    }
    if (in_recent) { int f = family_index(recent[rec_sel]); if (f >= 0) { cur = f; fam_pick[f] = recent[rec_sel]; } }
    keep_row_shown();
    decide_for = -1; moved_frame = g_frames_presented;
}
static void next_variant(void) {
    int m[16], n = members(cur, m, 16), i;
    if (n < 2) return;
    for (i = 0; i < n && m[i] != fam_pick[cur]; i++) ;
    fam_pick[cur] = m[(i + 1) % n];
    in_recent = 0; decide_for = -1; moved_frame = g_frames_presented;
}

/* gs_filter_buttons (rt_gamesetup.c), while the select waits for a choice: the grid takes the
   d-pad, - and 2 / A; the rest goes on to the game */
uint32_t charsel_input(uint32_t b, uint32_t pressed) {
    if (gs_sp_select_state() != 1) { held_dir = 0; return b; }
    open_if_new();
    if (!nfam) return b;
    uint32_t dirs = b & NAV_ALL, pdir = pressed & NAV_ALL;
    if (pdir) {                                                           /* a new press: at once */
        uint32_t d = pdir & NAV_LEFT ? NAV_LEFT : pdir & NAV_RIGHT ? NAV_RIGHT : pdir & NAV_UP ? NAV_UP : NAV_DOWN;
        move(d); held_dir = d; held_since = held_last = g_frames_presented;
    } else if (held_dir && (dirs & held_dir)) {                           /* held: repeats */
        if (g_frames_presented - held_since >= REPEAT_FIRST && g_frames_presented - held_last >= REPEAT_EVERY) { move(held_dir); held_last = g_frames_presented; }
    } else held_dir = 0;
    if (pressed & B_MINUS) next_variant();
    if (pressed & (B_2 | B_A)) { decide_for = target(); rt_log("charsel", "choose %s", chars_name(decide_for)); }
    return b & ~(uint32_t)(NAV_ALL | B_MINUS | B_2 | B_A);
}

/* ================================================================== drawing (640 x 480 overlay) */
static uint32_t rgba(uint32_t rgb, float a) { int v = (int)(a * 255); if (v < 0) v = 0; if (v > 255) v = 255; return (rgb << 8) | (uint32_t)v; }
static void frame(float x, float y, float w, float h, float t, uint32_t rgb, float a) {
    ui_rect(x - t, y - t, w + 2 * t, t, rgba(rgb, a)); ui_rect(x - t, y + h, w + 2 * t, t, rgba(rgb, a));
    ui_rect(x - t, y, t, h, rgba(rgb, a)); ui_rect(x + w, y, t, h, rgba(rgb, a));
}
static void text_fit(float cx, float y, float size, float maxw, const char *s, uint32_t col) {
    float w = menu_text_width(s, size); if (w > maxw && w > 0) { size *= maxw / w; w = maxw; }
    menu_text(cx - w / 2, y, size, s, col);
}
/* a character's picture in a tile (its name when it has none) */
static void tile(int c, float x, float y, float s, float a, int dim) {
    int tex = chars_tile_texture(c);
    ui_rect(x, y, s, s, rgba(0x1C2840, a * 0.95f));
    float k = dim ? 0.45f : 1.0f;
    uint32_t tint = ((uint32_t)(255 * k) << 24) | ((uint32_t)(255 * k) << 16) | ((uint32_t)(255 * k) << 8);
    if (tex) ui_image(tex, x + 2, y + 2, s - 4, s - 4, 0, 0, 1, 1, tint | (uint32_t)(a * 255));
    else text_fit(x + s / 2, y + s / 2 - 8, 14, s - 6, chars_name(c), rgba(dim ? 0x808890 : 0xE0E8F0, a));
}

#define GOLD 0xFFC830
#define WHITE 0xFFFFFF
#define GREY 0xA0A8B8
#define NAVY 0x101828
#define PX 252.0f                                /* the panel */
#define PY 122.0f                                /* (below "Settings +") */
#define PW 372.0f
#define TS 54.0f                                 /* tile size, gap */
#define TG 6.0f

void charsel_draw(void) {
    int st = gs_sp_select_state();
    if (!st || !nfam || visit_seen != gs_sp_select_visit()) return;
    float a = gs_screen_alpha();
    if (a <= 0.01f) return;
    int chosen = st == 2, tc = target();
    double pulse = 0.5 + 0.5 * sin(rt_now_ns() / 1e9 * 5.0);
    int rows = nrows(), shown = rows < ROWS_SHOWN ? rows : ROWS_SHOWN;
    float gx = PX + (PW - (COLS * TS + (COLS - 1) * TG)) / 2, gy = PY + 38;
    float ry = gy + shown * (TS + TG) + 8;                                /* the Recent row */
    float rs = 40, ph = (ry - PY) + (nrecent ? 22 + rs + 8 : 0) + 30;
    /* the panel */
    frame(PX, PY, PW, ph, 3, 0xF0C030, a);
    ui_rect(PX, PY, PW, ph, rgba(NAVY, a * 0.82f));
    menu_text(PX + 14, PY + 8, 20, "Characters", rgba(GOLD, a));
    { char n[32]; snprintf(n, sizeof n, "%d / %d", cur + 1, nfam); menu_text(PX + PW - 14 - menu_text_width(n, 16), PY + 11, 16, n, rgba(GREY, a)); }
    /* the grid */
    for (int i = top_row * COLS; i < nfam && i < (top_row + shown) * COLS; i++) {
        int r = i / COLS - top_row, col = i % COLS;
        float x = gx + col * (TS + TG), y = gy + r * (TS + TG);
        int on = i == cur && !in_recent;
        tile(fam_pick[i], x, y, TS, a, chosen && !on);
        int m[16], n = members(i, m, 16);
        for (int k = 0; k < n && n > 1; k++) {                            /* (variants: a dot each, the tile's lit) */
            float dx = x + TS - 6 - (n - 1 - k) * 6, dy = y + TS - 7;
            ui_rect(dx, dy, 4, 4, rgba(m[k] == fam_pick[i] ? GOLD : GREY, a));
        }
        if (on) {
            float pop = g_frames_presented - moved_frame < 6 ? 2.0f * (1 - (g_frames_presented - moved_frame) / 6.0f) : 0;
            frame(x - pop, y - pop, TS + 2 * pop, TS + 2 * pop, 3, chosen ? 0x60E070 : GOLD, a * (chosen ? 1.0f : 0.75f + 0.25f * (float)pulse));
        } else frame(x, y, TS, TS, 1, 0x506078, a);
    }
    if (top_row > 0) text_fit(PX + PW / 2, gy - 17, 14, 40, "^", rgba(GREY, a));
    if (top_row + shown < rows) text_fit(PX + PW / 2, gy + shown * (TS + TG) - 6, 14, 40, "v", rgba(GREY, a));
    /* Recent */
    if (nrecent) {
        menu_text(gx, ry, 16, "Recent", rgba(GREY, a));
        for (int i = 0; i < nrecent; i++) {
            float x = gx + i * (rs + TG), y = ry + 22;
            int on = in_recent && i == rec_sel;
            tile(recent[i], x, y, rs, a, chosen && !on);
            if (on) frame(x, y, rs, rs, 3, chosen ? 0x60E070 : GOLD, a * (chosen ? 1.0f : 0.75f + 0.25f * (float)pulse));
            else frame(x, y, rs, rs, 1, 0x506078, a);
        }
    }
    /* hints */
    text_fit(PX + PW / 2, PY + ph - 26, 16, PW - 20, chosen ? "2: Start Game    1: Change" : "D-pad: Move    -: Variant    2: Choose", rgba(WHITE, a));

    /* under the card: the name, and the family's variants */
    float cx = gs_sp_preview_x(), ny = 94;                                 /* (above the card) */
    text_fit(cx, ny, 26, 230, chars_name(tc), rgba(WHITE, a));
    int f = family_index(tc), m[16], n = f >= 0 ? members(f, m, 16) : 0;
    if (n > 1) {
        float cw[16], tw = 0, size = 15;
        for (int k = 0; k < n; k++) { cw[k] = menu_text_width(chars_variant(m[k]), size) + 14; tw += cw[k] + (k ? 5 : 0); }
        float x = cx - tw / 2, y = ny + 30;
        for (int k = 0; k < n; k++) {
            int on = m[k] == tc;
            ui_rect(x, y, cw[k], 22, rgba(on ? GOLD : NAVY, a * (on ? 1.0f : 0.8f)));
            if (!on) frame(x, y, cw[k], 22, 1, 0x506078, a);
            menu_text(x + 7, y + 3, size, chars_variant(m[k]), rgba(on ? 0x302000 : GREY, a));
            x += cw[k] + 5;
        }
    }
}
