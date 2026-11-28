/* smb3_sound.c - SMB3's music and sound effects in NSMBW's own formats and NSMBW's own sound
 * archive.
 *
 * Built once, at build time (build.py: nsmbw.exe --smb3-render-sound <dir>, smb3_sound_render):
 * SMB3's sound engine (PRG028/029 and PRG031's music player, the recompiled 6502 code) runs
 * offline on the NES APU (nes_apu.c) for each song and each sound effect, alone, and what it makes
 * is written in NSMBW's formats - the game files <game>/sound/smb3/:
 *   - songs: NSMBW streams (.brstm, DSP-ADPCM, 32 kHz, two channels as NSMBW's own BGM streams -
 *     the NES's one sound in both). A song that loops is found looping by its engine's state (the
 *     engine's RAM the same as on an earlier frame: what follows is the same again) and its loop
 *     start is moved onto a stream block as NSMBW's are; a song that ends (the jingles, the Warp
 *     Whistle) has no loop. Each song that SMB3's "time warning" speeds up (Set 2B, $09, $0A -
 *     PRG031_E4E4: Music_RestH_Off $10) has a fast copy too, as NSMBW's _FAST streams;
 *   - sound effects: NSMBW waves (.rwav, mono DSP-ADPCM, 32 kHz - the layout of the waves in
 *     NSMBW's own wave archives), one per queue value.
 *
 * At start (rt_disc.c's disc_init), nothing is made: the songs are put on the disc in a folder of
 * their own, /smb3/, and NSMBW's sound archive (/Sound/wii_mj2d_sound.brsar - the file itself is
 * never changed) is given to the game expanded (smb3_brsar_expand): every sound, file, group and
 * byte of NSMBW's own as it was, and after them -
 *   - a stream sound per SMB3 song (its file /smb3/<song>.brstm; Set 2 on the course BGM player
 *     18, Set 1 on the fanfare player 17);
 *   - a wave sound per SMB3 sound effect (the player's on PLAYER_SE_PLY, the level's on
 *     PLAYER_SE_OBJ, the map's on PLAYER_SE_SYS, the pause sound on PLAYER_SE_SYS_GAME_PAUSE), in
 *     one wave sound file (RWSD) of a new group, GROUP_SMB3, with its wave archive (RWAR) of
 *     the effects' waves - loaded with GROUP_BOOT, into NSMBW's sound heap, by NSMBW's own loader
 *     (gm_nw4r_g3d.c: fn_802D3E90);
 *   - their names (SMB3_M1_40, SMB3_M2F_10, SMB3_SE_MAP_04, GROUP_SMB3 ...) in its string table.
 * smb3_snd_id gives their sound IDs (after NSMBW's own: from its sound count). */
#include "nes.h"
#include "nes_apu.h"
#include "smb3_syms.h"
#include "smb3_sound.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#define mkdir_(p) _mkdir(p)
#else
#define mkdir_(p) mkdir(p, 0755)
#endif
void rt_log(const char *tag, const char *fmt, ...);
uint64_t rt_now_ns(void);
extern const uint8_t smb3_rom[]; extern const uint32_t smb3_rom_size;

#define RENDER_VERSION  6                /* (songs: 5 and 6 the same) */
#define ENGINE          0xA000                   /* Sound_Engine_Begin (PRG028) */
#define BANK_A          28
#define BANK_C          29
#define RATE            32000
#define SPB             14336                    /* samples in a stream block (0x2000 bytes of DSP-ADPCM) */

int smb3_sound_rendering;                        /* (smb3_hook_sound: the engine runs as it is meanwhile) */

/* ------------------------------------------------------------------ the song and sound list */
static smb3_snd_t S[SMB3_SND_MAX]; static int nS;
static char dir_[1024];

static void add(int kind, int id, int fast) {
    smb3_snd_t *s = &S[nS++]; memset(s, 0, sizeof *s);
    s->kind = kind; s->id = id; s->fast = fast;
    static const char *const q[] = { "", "", "PLY", "LV1", "LV2", "MAP", "PAUSE" };
    if (kind == SND_M1) { snprintf(s->name, sizeof s->name, "smb3_m1_%02X.brstm", id); snprintf(s->label, sizeof s->label, "SMB3_M1_%02X", id); }
    else if (kind == SND_M2) { snprintf(s->name, sizeof s->name, "smb3_m2%s_%02X.brstm", fast ? "f" : "", id); snprintf(s->label, sizeof s->label, "SMB3_M2%s_%02X", fast ? "F" : "", id); }
    else { snprintf(s->name, sizeof s->name, "smb3_sfx_%d_%02X.rwav", kind, id); snprintf(s->label, sizeof s->label, "SMB3_SE_%s_%02X", q[kind], id); }
    s->sound_id = -1;
}
static void build_list(void) {
    nS = 0;
    for (int b = 0; b < 7; b++) add(SND_M1, 1 << b, 0);                         /* MUS1_PLAYERDEATH .. MUS1_TIMEWARNING */
    for (int i = 1; i <= 15; i++) add(SND_M2, i, 0);                            /* Set 2A: the worlds' maps, sky, star, warp whistle, ... */
    for (int i = 1; i <= 12; i++) add(SND_M2, i << 4, 0);                       /* Set 2B: the levels */
    add(SND_M2, 0x09, 1); add(SND_M2, 0x0A, 1);                                /* (the time warning's fast copies) */
    for (int i = 1; i <= 12; i++) add(SND_M2, i << 4, 1);
    for (int b = 0; b < 8; b++) add(SND_PLAYER, 1 << b, 0);
    for (int b = 0; b < 8; b++) add(SND_LEVEL1, 1 << b, 0);
    add(SND_LEVEL1, 0x90, 0); add(SND_LEVEL1, 0xA0, 0); add(SND_LEVEL1, 0xB0, 0);
    for (int b = 0; b < 8; b++) add(SND_LEVEL2, 1 << b, 0);
    for (int b = 0; b < 8; b++) add(SND_MAP, 1 << b, 0);
    add(SND_PAUSE, 1, 0);
}
const smb3_snd_t *smb3_snd_find(int kind, int id, int fast) {
    for (int i = 0; i < nS; i++) if (S[i].kind == kind && S[i].id == id && S[i].fast == fast) return S[i].ok ? &S[i] : NULL;
    return NULL;
}
int smb3_snd_id(int kind, int id, int fast) { const smb3_snd_t *s = smb3_snd_find(kind, id, fast); return s ? s->sound_id : -1; }
int smb3_snd_count(void) { return nS; }
const smb3_snd_t *smb3_snd_at(int i) { return i >= 0 && i < nS ? &S[i] : NULL; }
const char *smb3_snd_dir(void) { return dir_; }

/* ------------------------------------------------------------------ rendering */
typedef struct { int16_t *p; int n, cap; } buf_t;
static void put(buf_t *b, int16_t v) { if (b->n == b->cap) { b->cap = b->cap ? b->cap * 2 : 1 << 16; b->p = realloc(b->p, sizeof *b->p * (size_t)b->cap); } b->p[b->n++] = v; }
static uint8_t *ram(uint16_t a) { return a >= 0x6000 ? nes_wram_ptr() + (a - 0x6000) : nes_ram_ptr() + (a & 0x7FF); }
static uint64_t state_hash(void) {                /* the engine's state: RAM (not the stack page) and its work RAM at $7Axx */
    uint64_t h = 1469598103934665603ull; const uint8_t *r = nes_ram_ptr(), *w = nes_wram_ptr();
    for (int i = 0; i < 0x800; i++) { if (i >= 0x100 && i < 0x200) continue; h = (h ^ r[i]) * 1099511628211ull; }
    for (int i = 0x1A00; i < 0x1B00; i++) h = (h ^ w[i]) * 1099511628211ull;
    return h;
}
/* one sound frame (29780.5 cycles: the NMI's rate) - the samples it made into b */
static void frame(buf_t *b, int f) {
    nes_sound_run(ENGINE, BANK_A, BANK_C, (f & 1) ? 29781 : 29780);
    int16_t t[2 * 1024]; int got;
    do { got = apu_pull(t, 1024, 100); for (int i = 0; i < got; i++) put(b, t[2 * i]); } while (got == 1024);
}
static uint16_t cur_of(int kind) {
    switch (kind) {
    case SND_PLAYER: return SMB3_SndCur_Player; case SND_LEVEL1: return SMB3_SndCur_Level1; case SND_LEVEL2: return SMB3_SndCur_Level2;
    case SND_MAP: return SMB3_SndCur_Map; case SND_PAUSE: return SMB3_SndCur_Pause; default: return 0;
    }
}
static uint16_t q_of(int kind) {
    switch (kind) {
    case SND_M1: return SMB3_Sound_QMusic1; case SND_M2: return SMB3_Sound_QMusic2; case SND_PLAYER: return SMB3_Sound_QPlayer;
    case SND_LEVEL1: return SMB3_Sound_QLevel1; case SND_LEVEL2: return SMB3_Sound_QLevel2; case SND_MAP: return SMB3_Sound_QMap; default: return SMB3_Sound_QPause;
    }
}
/* the sound alone, from a fresh NES: samples, and (a song) its loop - the start, or -1 */
static void render(smb3_snd_t *s, buf_t *b, int *loop) {
    b->n = 0; *loop = -1;
    nes_reset();
    apu_write(0x4015, 0x0F);
    { int16_t t[2048]; while (apu_pull(t, 1024, 100) == 1024) ; }
    if (s->fast) *ram(SMB3_Music_RestH_Off) = 0x10;
    *ram(q_of(s->kind)) = (uint8_t)s->id;
    int music = s->kind == SND_M1 || s->kind == SND_M2;
    int maxf = music ? 60 * 300 : 60 * 6;
    enum { NH = 60 * 300 + 8 };
    static uint64_t hs[NH]; static int at[NH];
    int found = -1, need = 0;
    for (int f = 0; f < maxf; f++) {
        at[f] = b->n;
        frame(b, f);
        if (music) {
            int on = *ram(SMB3_SndCur_Music1) || *ram(SMB3_SndCur_Music2);
            if (!on) { for (int k = 0; k < 15; k++) frame(b, ++f); break; }   /* (over: its notes' release) */
            if (found >= 0) { if (b->n >= need) break; continue; }
            if (s->kind == SND_M2) {
                uint64_t h = state_hash(); hs[f] = h;
                for (int j = 1; j < f; j++) if (hs[j] == h) {                    /* (frame 0: the queue still set) */
                    int len = b->n - at[j + 1] , ls = at[j + 1];                    /* (the state after frame j: the samples from frame j + 1) */
                    int ls2 = (ls + SPB - 1) / SPB * SPB;                           /* (onto a block, as NSMBW's loops) */
                    found = ls2; need = ls2 + len; s->loop_len = len; break;
                }
            }
        } else if (f > 2 && !*ram(cur_of(s->kind))) {
            for (int k = 0; k < 6; k++) frame(b, ++f);
            break;
        }
    }
    if (found >= 0) {
        if (b->n > need) b->n = need;
        *loop = found;
        /* the same music again, but not the same waves (the noise's shift register, the pulses'
           phase): the last 20 ms faded into what comes before the loop's start, so the end runs
           on into it without a click */
        int L = 640; if (L > found) L = found;
        for (int k = 1; k <= L; k++) { double t = 1.0 - (double)k / L; int i = b->n - k, j = found - k;
            b->p[i] = (int16_t)lround(b->p[i] * (1.0 - t) + b->p[j] * t); }
    }
    else { while (b->n > 1 && abs(b->p[b->n - 1]) < 48) b->n--; }   /* (the silence after the end) */
    if (b->n < 16) b->n = 0;
}

/* ------------------------------------------------------------------ DSP-ADPCM */
static int16_t clamp16(int v) { return (int16_t)(v > 32767 ? 32767 : v < -32768 ? -32768 : v); }
/* the 8 predictors: per 14-sample frame the best (a1, a2) by least squares, clustered (k-means on
   each frame's own prediction error), each cluster's by least squares of all its frames */
typedef struct { double r[3][3]; } acf_t;
static void acf_frame(const int16_t *x, int i0, int n, acf_t *a) {
    memset(a, 0, sizeof *a);
    for (int t = i0; t < i0 + 14 && t < n; t++) {
        double v[3] = { x[t], t >= 1 ? x[t - 1] : 0, t >= 2 ? x[t - 2] : 0 };
        for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) a->r[i][j] += v[i] * v[j];
    }
}
static double acf_err(const acf_t *a, double c1, double c2) {
    return a->r[0][0] - 2 * c1 * a->r[0][1] - 2 * c2 * a->r[0][2] + c1 * c1 * a->r[1][1] + 2 * c1 * c2 * a->r[1][2] + c2 * c2 * a->r[2][2];
}
static int acf_solve(const acf_t *a, double *c1, double *c2) {
    double r11 = a->r[1][1], r22 = a->r[2][2], r12 = a->r[1][2], eps = (r11 + r22) * 1e-6 + 1e-9;
    r11 += eps; r22 += eps;
    double det = r11 * r22 - r12 * r12; if (fabs(det) < 1e-9) return 0;
    *c1 = (a->r[0][1] * r22 - a->r[0][2] * r12) / det; *c2 = (a->r[0][2] * r11 - a->r[0][1] * r12) / det;
    if (*c1 > 15.9) *c1 = 15.9; if (*c1 < -15.9) *c1 = -15.9; if (*c2 > 15.9) *c2 = 15.9; if (*c2 < -15.9) *c2 = -15.9;
    return 1;
}
static void adpcm_coefs(const int16_t *x, int n, int16_t coef[16]) {
    static const double init[8][2] = {{0, 0}, {1, 0}, {2, -1}, {1.8, -0.85}, {1.5, -0.6}, {0.9, 0}, {1.95, -0.97}, {1.2, -0.3}};
    double c[8][2]; memcpy(c, init, sizeof c);
    int nf = (n + 13) / 14; acf_t *A = malloc(sizeof *A * (size_t)(nf > 0 ? nf : 1)); int *as = malloc(sizeof(int) * (size_t)(nf > 0 ? nf : 1));
    for (int f = 0; f < nf; f++) acf_frame(x, f * 14, n, &A[f]);
    for (int it = 0; it < 10; it++) {
        acf_t sum[8]; memset(sum, 0, sizeof sum);
        for (int f = 0; f < nf; f++) {
            int best = 0; double be = 1e300;
            for (int k = 0; k < 8; k++) { double e = acf_err(&A[f], c[k][0], c[k][1]); if (e < be) { be = e; best = k; } }
            as[f] = best;
            for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) sum[best].r[i][j] += A[f].r[i][j];
        }
        for (int k = 0; k < 8; k++) { double c1, c2; if (sum[k].r[1][1] > 0 && acf_solve(&sum[k], &c1, &c2)) { c[k][0] = c1; c[k][1] = c2; } }
    }
    for (int k = 0; k < 8; k++) for (int i = 0; i < 2; i++) { long v = lround(c[k][i] * 2048.0); coef[2 * k + i] = (int16_t)(v > 32767 ? 32767 : v < -32768 ? -32768 : v); }
    free(A); free(as);
}
/* one frame: the best predictor and scale, by trying them (the decoder's own arithmetic, from the
   decoded history) - its 8 bytes; the history moves on */
static void adpcm_frame(const int16_t *x, int cnt, const int16_t coef[16], int16_t *h1, int16_t *h2, uint8_t out[8], int16_t *dec) {
    int best_c = 0, best_s = 0; double best_e = 1e300; int8_t best_n[14]; int16_t best_d[14];
    for (int c = 0; c < 8; c++) {
        int c1 = coef[2 * c], c2 = coef[2 * c + 1];
        /* the scale the residuals need, by the ideal history; that one and one above */
        int mx = 0; { int a = *h1, b2 = *h2; for (int i = 0; i < cnt; i++) { int p = (c1 * a + c2 * b2 + 1024) >> 11; int r = x[i] - p; if (abs(r) > mx) mx = abs(r); b2 = a; a = x[i]; } }
        int s0 = 0; while (s0 < 12 && (7 << s0) < mx) s0++;
        for (int s = s0 > 0 ? s0 - 1 : 0; s <= s0 + 1 && s <= 12; s++) {
            int a = *h1, b2 = *h2; double e = 0; int8_t nn[14]; int16_t dd[14];
            for (int i = 0; i < cnt; i++) {
                int P = c1 * a + c2 * b2 + 1024;
                double q = ((double)x[i] * 2048.0 + 1023.5 - P) / (double)(1 << (s + 11));
                long v = lround(q); if (v > 7) v = 7; if (v < -8) v = -8;
                int d = clamp16((int)((((int)v << s) << 11) + P) >> 11);
                double er = (double)(d - x[i]); e += er * er; nn[i] = (int8_t)v; dd[i] = (int16_t)d;
                b2 = a; a = d;
                if (e >= best_e) break;
            }
            if (e < best_e) { best_e = e; best_c = c; best_s = s; memcpy(best_n, nn, sizeof nn); memcpy(best_d, dd, sizeof dd); }
        }
    }
    memset(out, 0, 8);
    out[0] = (uint8_t)(best_c << 4 | best_s);
    for (int i = 0; i < cnt; i++) out[1 + i / 2] |= (uint8_t)((best_n[i] & 15) << ((i & 1) ? 0 : 4));
    for (int i = 0; i < cnt; i++) dec[i] = best_d[i];
    if (cnt >= 2) { *h2 = best_d[cnt - 2]; *h1 = best_d[cnt - 1]; } else if (cnt == 1) { *h2 = *h1; *h1 = best_d[0]; }
}

/* ------------------------------------------------------------------ files */
static void be32w(uint8_t *p, uint32_t v) { p[0] = (uint8_t)(v >> 24); p[1] = (uint8_t)(v >> 16); p[2] = (uint8_t)(v >> 8); p[3] = (uint8_t)v; }
static void be16w(uint8_t *p, uint16_t v) { p[0] = (uint8_t)(v >> 8); p[1] = (uint8_t)v; }
static uint32_t be32r(const uint8_t *p) { return (uint32_t)p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]; }
/* a stream as NSMBW's own two-channel ones (couse_clear_lr.n.32.brstm - the layout its stream
   players read for the BGM sounds we start them as: two channels, one track of both): RSTM header,
   HEAD (stream info, the track, each channel's ADPCM info), ADPC (each block's history per
   channel), DATA (each block's channels one after the other). The NES is mono: both channels
   the same, encoded once */
#define NCH 2
static int write_brstm(const char *path, const int16_t *x, int n, int loop) {
    int nb = (n + SPB - 1) / SPB, last = n - (nb - 1) * SPB;
    int lastfull = last / 14, lastrem = last % 14;
    uint32_t lastbs = (uint32_t)(lastfull * 8 + (lastrem ? 1 + (lastrem + 1) / 2 : 0)), lastpad = (lastbs + 31) & ~31u;
    uint32_t head = 0x40, headsz = 0x100, adpc = head + headsz, adpcsz = (8 + (uint32_t)nb * 4 * NCH + 31) & ~31u, data = adpc + adpcsz;
    uint32_t datasz = 0x20 + (uint32_t)(nb - 1) * 0x2000 * NCH + lastpad * NCH, total = data + datasz;
    uint8_t *f = calloc(1, total); if (!f) return 0;
    int16_t coef[16]; adpcm_coefs(x, n, coef);
    /* the data: each block encoded once, written for both channels */
    int16_t h1 = 0, h2 = 0, dec[14]; uint8_t ps0 = 0, lps = 0; int16_t lh1 = 0, lh2 = 0;
    uint8_t *blk = malloc(0x2000);
    uint8_t *o = f + data + 0x20;
    for (int b = 0; b < nb; b++) {
        for (int c = 0; c < NCH; c++) { be16w(f + adpc + 8 + (uint32_t)(b * NCH + c) * 4, (uint16_t)h1); be16w(f + adpc + 8 + (uint32_t)(b * NCH + c) * 4 + 2, (uint16_t)h2); }
        if (loop >= 0 && b * SPB == loop) { lh1 = h1; lh2 = h2; }
        int cnt = b == nb - 1 ? last : SPB; uint32_t bsz = b == nb - 1 ? lastpad : 0x2000;
        memset(blk, 0, 0x2000);
        for (int i = 0, k; i < cnt; i += 14) {
            k = cnt - i < 14 ? cnt - i : 14;
            uint8_t fr[8]; adpcm_frame(x + b * SPB + i, k, coef, &h1, &h2, fr, dec);
            if (b == 0 && i == 0) ps0 = fr[0];
            if (loop >= 0 && b * SPB + i == loop) lps = fr[0];
            memcpy(blk + i / 14 * 8, fr, k == 14 ? 8 : (size_t)(1 + (k + 1) / 2));
        }
        for (int c = 0; c < NCH; c++) { memcpy(o, blk, bsz); o += bsz; }
    }
    free(blk);
    memcpy(f, "RSTM", 4); be16w(f + 4, 0xFEFF); be16w(f + 6, 0x0100); be32w(f + 8, total); be16w(f + 12, 0x40); be16w(f + 14, 2);
    be32w(f + 0x10, head); be32w(f + 0x14, headsz); be32w(f + 0x18, adpc); be32w(f + 0x1C, adpcsz); be32w(f + 0x20, data); be32w(f + 0x24, datasz);
    uint8_t *h = f + head; memcpy(h, "HEAD", 4); be32w(h + 4, headsz);
    uint8_t *r = h + 8;
    be32w(r + 0x00, 0x01000000); be32w(r + 0x04, 0x18); be32w(r + 0x08, 0x01000000); be32w(r + 0x0C, 0x4C); be32w(r + 0x10, 0x01000000); be32w(r + 0x14, 0x64);
    uint8_t *i1 = r + 0x18;                                             /* the stream */
    i1[0] = 2; i1[1] = loop >= 0; i1[2] = NCH; be16w(i1 + 4, RATE);
    be32w(i1 + 0x08, (uint32_t)(loop >= 0 ? loop : 0)); be32w(i1 + 0x0C, (uint32_t)n); be32w(i1 + 0x10, data + 0x20); be32w(i1 + 0x14, (uint32_t)nb);
    be32w(i1 + 0x18, 0x2000); be32w(i1 + 0x1C, SPB); be32w(i1 + 0x20, lastbs); be32w(i1 + 0x24, (uint32_t)last); be32w(i1 + 0x28, lastpad);
    be32w(i1 + 0x2C, SPB); be32w(i1 + 0x30, 4);
    uint8_t *i2 = r + 0x4C;                                             /* one track (volume, pan; channels 0 and 1) */
    be32w(i2, 0x01010000); be32w(i2 + 4, 0x01010000); be32w(i2 + 8, 0x58);
    r[0x58] = 0x7F; r[0x59] = 0x40; r[0x60] = NCH; r[0x61] = 0; r[0x62] = 1;
    uint8_t *i3 = r + 0x64;                                             /* the channels */
    i3[0] = NCH;
    for (int c = 0; c < NCH; c++) {
        uint32_t ci_ref = 0x78 + 0x38u * (uint32_t)c, ad = ci_ref + 8;
        be32w(i3 + 4 + 8 * c, 0x01000000); be32w(i3 + 8 + 8 * c, ci_ref);
        be32w(r + ci_ref, 0x01000000); be32w(r + ci_ref + 4, ad);
        uint8_t *ci = r + ad;
        for (int k = 0; k < 16; k++) be16w(ci + 2 * k, (uint16_t)coef[k]);
        be16w(ci + 0x20, 0); be16w(ci + 0x22, ps0); be16w(ci + 0x24, 0); be16w(ci + 0x26, 0);
        be16w(ci + 0x28, lps); be16w(ci + 0x2A, (uint16_t)lh1); be16w(ci + 0x2C, (uint16_t)lh2);
    }
    memcpy(f + adpc, "ADPC", 4); be32w(f + adpc + 4, adpcsz);
    memcpy(f + data, "DATA", 4); be32w(f + data + 4, datasz); be32w(f + data + 8, 0x18);
    FILE *fp = fopen(path, "wb"); if (!fp) { free(f); return 0; }
    int ok = fwrite(f, 1, total, fp) == total; fclose(fp); free(f);
    return ok;
}
/* an NSMBW wave (RWAV, as the waves in NSMBW's wave archives): header, INFO (the wave: DSP-ADPCM,
   one channel, its rate, start / end as nibble addresses; the channel's ADPCM info), DATA */
static uint32_t nib(int s) { return (uint32_t)(s / 14 * 16 + 2 + s % 14); }   /* (a sample's nibble address) */
static int write_rwav(const char *path, const int16_t *x, int n) {
    int nf = (n + 13) / 14; uint32_t dbytes = (uint32_t)nf * 8, dsz = (8 + dbytes + 31) & ~31u, total = 0xA0 + dsz;
    uint8_t *f = calloc(1, total); if (!f) return 0;
    int16_t coef[16]; adpcm_coefs(x, n, coef);
    int16_t h1 = 0, h2 = 0, dec[14]; uint8_t ps0 = 0;
    for (int i = 0; i < nf; i++) {
        int k = n - i * 14 < 14 ? n - i * 14 : 14; uint8_t fr[8];
        adpcm_frame(x + i * 14, k, coef, &h1, &h2, fr, dec);
        if (!i) ps0 = fr[0];
        memcpy(f + 0xA8 + i * 8, fr, 8);
    }
    memcpy(f, "RWAV", 4); be16w(f + 4, 0xFEFF); be16w(f + 6, 0x0102); be32w(f + 8, total); be16w(f + 12, 0x20); be16w(f + 14, 2);
    be32w(f + 0x10, 0x20); be32w(f + 0x14, 0x80); be32w(f + 0x18, 0xA0); be32w(f + 0x1C, dsz);
    memcpy(f + 0x20, "INFO", 4); be32w(f + 0x24, 0x80);
    uint8_t *w = f + 0x28;
    w[0] = 2; w[1] = 0; w[2] = 1; w[3] = 0; be16w(w + 4, RATE);
    be32w(w + 0x08, 2); be32w(w + 0x0C, nib(n - 1)); be32w(w + 0x10, 0x1C); be32w(w + 0x14, 0x78);
    be32w(w + 0x1C, 0x20);                                              /* the channel table: one */
    uint8_t *c = w + 0x20;                                              /* its info: data +0, ADPCM info, volumes */
    be32w(c + 0, 0); be32w(c + 4, 0x3C); for (int k = 0; k < 4; k++) be32w(c + 8 + 4 * k, 0x01000000);
    uint8_t *ad = w + 0x3C;
    for (int k = 0; k < 16; k++) be16w(ad + 2 * k, (uint16_t)coef[k]);
    be16w(ad + 0x22, ps0); be16w(ad + 0x28, ps0);
    memcpy(f + 0xA0, "DATA", 4); be32w(f + 0xA4, dsz);
    FILE *fp = fopen(path, "wb"); if (!fp) { free(f); return 0; }
    int ok = fwrite(f, 1, total, fp) == total; fclose(fp); free(f);
    return ok;
}
/* a file's length and loop from its header */
static int read_meta(smb3_snd_t *s, const char *path) {
    FILE *fp = fopen(path, "rb"); if (!fp) return 0;
    uint8_t h[0x100]; size_t got = fread(h, 1, sizeof h, fp); fseek(fp, 0, SEEK_END); long sz = ftell(fp); fclose(fp);
    s->bytes = (uint32_t)sz;
    if (s->kind == SND_M1 || s->kind == SND_M2) {
        if (got < 0x100 || memcmp(h, "RSTM", 4)) return 0;
        const uint8_t *i1 = h + 0x60;
        s->samples = (int)be32r(i1 + 0x0C); s->loop = i1[1] ? (int)be32r(i1 + 0x08) : -1;
    } else {
        if (got < 0x40 || memcmp(h, "RWAV", 4)) return 0;
        uint32_t e = be32r(h + 0x28 + 0x0C); s->samples = (int)((e - 2) / 16 * 14 + (e - 2) % 16) + 1; s->loop = -1;
    }
    return s->samples > 0;
}

static uint64_t rom_hash(void) { uint64_t h = 1469598103934665603ull; for (uint32_t i = 0; i < smb3_rom_size; i++) h = (h ^ smb3_rom[i]) * 1099511628211ull; return h; }

static int file_size(const char *p) { FILE *f = fopen(p, "rb"); if (!f) return -1; fseek(f, 0, SEEK_END); long n = ftell(f); fclose(f); return (int)n; }

/* (build time: nsmbw.exe --smb3-render-sound <dir>) the files made into dir, if they aren't
   there already from this renderer and ROM (its stamp) - 0, or 1 when something failed */
int smb3_sound_render(const char *dir) {
    build_list();
    snprintf(dir_, sizeof dir_, "%s", dir); mkdir_(dir_);
    char stamp[64]; snprintf(stamp, sizeof stamp, "v%d rom %016llx\n", RENDER_VERSION, (unsigned long long)rom_hash());
    char sp[1100]; snprintf(sp, sizeof sp, "%s/stamp.txt", dir_);
    char old[64] = ""; { FILE *f = fopen(sp, "rb"); if (f) { size_t k = fread(old, 1, sizeof old - 1, f); old[k] = 0; fclose(f); } }
    int same = !strcmp(old, stamp), songs_ok = same || (!strncmp(old, "v5 ", 3) && !strcmp(old + 3, stamp + 3));   /* (v5's songs are v6's) */
    int all = 1;
    for (int i = 0; i < nS; i++) { char p[1200]; snprintf(p, sizeof p, "%s/%s", dir_, S[i].name); if (file_size(p) <= 0) all = 0; }
    if (same && all) { printf("SMB3 sound: up to date in %s\n", dir_); return 0; }
    printf("SMB3 sound: rendering SMB3's songs and sound effects into %s\n", dir_); fflush(stdout);
    uint64_t t0 = rt_now_ns();
    if (!nes_load(smb3_rom, smb3_rom_size)) { printf("SMB3 sound: the SMB3 ROM is not usable\n"); return 1; }
    smb3_sound_rendering = 1;
    buf_t b = {0}; int have = 0, fail = 0;
    for (int i = 0; i < nS; i++) {
        smb3_snd_t *s = &S[i]; int loop; char p[1200]; snprintf(p, sizeof p, "%s/%s", dir_, s->name);
        int music = s->kind == SND_M1 || s->kind == SND_M2;
        if (music && songs_ok && file_size(p) > 0) { have++; continue; }
        render(s, &b, &loop);
        if (b.n == 0) { remove(p); continue; }                          /* (a queue value that is no sound) */
        int ok = music ? write_brstm(p, b.p, b.n, loop) : write_rwav(p, b.p, b.n);
        have += ok; fail += !ok;
        printf("  %s %.2f s%s\n", s->name, b.n / (double)RATE, music ? (loop >= 0 ? " (loops)" : " (once)") : ""); fflush(stdout);
    }
    free(b.p);
    smb3_sound_rendering = 0;
    if (!fail) { FILE *f = fopen(sp, "wb"); if (f) { fputs(stamp, f); fclose(f); } }
    printf("SMB3 sound: %d files in %.1f s\n", have, (rt_now_ns() - t0) / 1e9);
    return fail != 0;
}

/* (start: rt_disc.c) the game files there - <root>/sound/smb3: how many */
int smb3_sound_files(const char *root) {
    build_list();
    snprintf(dir_, sizeof dir_, "%s/sound/smb3", root);
    int have = 0;
    for (int i = 0; i < nS; i++) { char p[1200]; snprintf(p, sizeof p, "%s/%s", dir_, S[i].name); S[i].ok = read_meta(&S[i], p); have += S[i].ok; }
    rt_log("smb3", "sound: %d of SMB3's %d songs and sounds in %s%s", have, nS, dir_, have ? "" : " - none: build.py makes them (nsmbw.exe --smb3-render-sound)");
    return have;
}

/* ------------------------------------------------------------------ NSMBW's sound archive, expanded */
typedef struct { uint8_t *p; uint32_t n, cap; } bb_t;
static uint32_t bb_put(bb_t *b, const void *d, uint32_t n) {
    if (b->n + n > b->cap) { while (b->n + n > b->cap) b->cap = b->cap ? b->cap * 2 : 4096; b->p = realloc(b->p, b->cap); }
    uint32_t at = b->n; if (d) memcpy(b->p + at, d, n); else memset(b->p + at, 0, n); b->n += n; return at;
}
static uint32_t bb_pad(bb_t *b, uint32_t a) { while (b->n % a) bb_put(b, NULL, 1); return b->n; }
static uint32_t bb_u32(bb_t *b, uint32_t v) { uint8_t t[4]; be32w(t, v); return bb_put(b, t, 4); }
static uint32_t bb_ref(bb_t *b, uint32_t off) { bb_u32(b, off ? 0x01000000 : 0); return bb_u32(b, off); }   /* (a DataRef: an offset, or none) */
static uint8_t *read_all(const char *p, uint32_t *n) {
    FILE *f = fopen(p, "rb"); if (!f) return NULL;
    fseek(f, 0, SEEK_END); long z = ftell(f); fseek(f, 0, SEEK_SET);
    uint8_t *d = malloc(z > 0 ? (size_t)z : 1); if (d && fread(d, 1, (size_t)z, f) != (size_t)z) { free(d); d = NULL; }
    fclose(f); *n = (uint32_t)z; return d;
}
static int smb3_group = -1;
int smb3_snd_group(void) { return smb3_group; }

/* the wave sound file (RWSD, as NSMBW's own - Yoshi's voices: DATA only, its waves in the group's
   wave archive): per sound one track of one note at 0, of wave n */
static void make_rwsd(bb_t *r, int nw) {
    static const uint8_t info[0x20] = { 0x3F,0x80,0,0, 0x40,0,0,0, 0,0x7F,0,0 };        /* (pitch 1, pan centre, main send 127) */
    bb_put(r, "RWSD", 4); bb_u32(r, 0xFEFF0103); bb_u32(r, 0); bb_u32(r, 0x00200001); bb_u32(r, 0x20); bb_u32(r, 0); bb_pad(r, 0x20);
    uint32_t d0 = bb_put(r, "DATA", 4); bb_u32(r, 0);
    uint32_t base = d0 + 8, tab = 4 + 8 * (uint32_t)nw;
    bb_u32(r, (uint32_t)nw);
    for (int i = 0; i < nw; i++) bb_ref(r, tab + 0xA4u * (uint32_t)i);
    for (int i = 0; i < nw; i++) {
        uint32_t b = tab + 0xA4u * (uint32_t)i;
        bb_ref(r, b + 0x18); bb_ref(r, b + 0x38); bb_ref(r, b + 0x68);          /* the sound: info, tracks, notes */
        bb_put(r, info, 0x20);
        bb_u32(r, 1); bb_ref(r, b + 0x44);                                    /* one track */
        bb_ref(r, b + 0x4C);                                                  /* its events */
        bb_u32(r, 1); bb_ref(r, b + 0x58);
        bb_put(r, NULL, 16);                                                  /* (the note at 0, its whole length, note 0) */
        bb_u32(r, 1); bb_ref(r, b + 0x74);                                    /* one note */
        bb_u32(r, (uint32_t)i); bb_u32(r, 0x7F7F7F7F); bb_u32(r, 0); bb_u32(r, 0x3C7F4000); bb_u32(r, 0x3F800000);
        bb_put(r, NULL, 28);
    }
    (void)base;
    be32w(r->p + d0 + 4, r->n - d0);
    bb_pad(r, 0x20);
    be32w(r->p + d0 + 4, r->n - d0);
    be32w(r->p + 8, r->n); be32w(r->p + 0x14, r->n - 0x20);
}
/* the wave archive (RWAR, as NSMBW's): TABL (each wave's place in DATA, its size), DATA (the waves) */
static int make_rwar(bb_t *w, uint8_t **wav, uint32_t *wn, int nw) {
    bb_put(w, "RWAR", 4); bb_u32(w, 0xFEFF0100); bb_u32(w, 0); bb_u32(w, 0x00200002); bb_put(w, NULL, 16);
    uint32_t t0 = bb_put(w, "TABL", 4); bb_u32(w, 0); bb_u32(w, (uint32_t)nw);
    uint32_t ents = w->n; bb_put(w, NULL, 12u * (uint32_t)nw); bb_pad(w, 0x20);
    be32w(w->p + t0 + 4, w->n - t0);
    uint32_t d0 = bb_put(w, "DATA", 4); bb_u32(w, 0); bb_pad(w, 0x20);
    for (int i = 0; i < nw; i++) {
        uint32_t at = bb_put(w, wav[i], wn[i]); bb_pad(w, 0x20);
        be32w(w->p + ents + 12u * (uint32_t)i, 0x01000000); be32w(w->p + ents + 12u * (uint32_t)i + 4, at - d0); be32w(w->p + ents + 12u * (uint32_t)i + 8, wn[i]);
    }
    be32w(w->p + d0 + 4, w->n - d0);
    be32w(w->p + 8, w->n); be32w(w->p + 0x10, t0); be32w(w->p + 0x14, d0 - t0); be32w(w->p + 0x18, d0); be32w(w->p + 0x1C, w->n - d0);
    return 1;
}

/* NSMBW's sound archive (o, n bytes) with SMB3's sounds after its own: a new buffer (its length
   in *out_n), NULL if it isn't the archive expected. Songs: /smb3/<file>. */
uint8_t *smb3_brsar_expand(const uint8_t *o, uint32_t n, uint32_t *out_n) {
    if (n < 0x40 || memcmp(o, "RSAR", 4)) return NULL;
    uint32_t so = be32r(o + 0x10), ss = be32r(o + 0x14), io = be32r(o + 0x18), is = be32r(o + 0x1C), fo = be32r(o + 0x20), fs = be32r(o + 0x24);
    if (so + ss > n || io + is > n || fo + fs > n) return NULL;
    const uint8_t *I0 = o + io + 8;                                     /* (INFO's offsets are from here) */
    #define IREF(p) (be32r((p) + 4))
    uint32_t snd_t = IREF(I0 + 0), file_t = IREF(I0 + 24), grp_t = IREF(I0 + 32);
    uint32_t nsnd = be32r(I0 + snd_t), nfile = be32r(I0 + file_t), ngrp = be32r(I0 + grp_t);
    const uint8_t *SY = o + so + 8; uint32_t str_t = be32r(SY), nstr = be32r(SY + str_t);
    /* the templates: NSMBW's own entries */
    #define SND(i) (I0 + IREF(I0 + snd_t + 4 + 8 * (i)))
    enum { T_SONG = 1915, T_JINGLE = 1899, T_WAVE = 189 };              /* STRM_BGM_MORI, STRM_BGM_LAST_CASTLE_APPEAR, SE_VOC_YS_GOKUN */
    if (nsnd <= T_SONG || SND(T_WAVE)[0x16] != 3 || SND(T_SONG)[0x16] != 2) return NULL;
    /* the waves (the effects' .rwav), their files */
    uint8_t *wav[SMB3_SND_MAX]; uint32_t wn[SMB3_SND_MAX]; int widx[SMB3_SND_MAX], nw = 0;
    for (int i = 0; i < nS; i++) {
        widx[i] = -1;
        if (!S[i].ok || S[i].kind < SND_PLAYER) continue;
        char p[1200]; snprintf(p, sizeof p, "%s/%s", dir_, S[i].name);
        if ((wav[nw] = read_all(p, &wn[nw]))) widx[i] = nw++;
    }
    bb_t rwsd = {0}, rwar = {0};
    if (nw) { make_rwsd(&rwsd, nw); make_rwar(&rwar, wav, wn, nw); }
    for (int i = 0; i < nw; i++) free(wav[i]);
    /* SYMB: NSMBW's, then a new string table (its strings and ours) and our strings */
    bb_t sy = {0}; bb_put(&sy, o + so, ss);
    int nnew = 0; uint32_t nstr0 = nstr;
    for (int i = 0; i < nS; i++) if (S[i].ok && (S[i].kind <= SND_M2 || widx[i] >= 0)) nnew++;
    bb_pad(&sy, 4); uint32_t st = sy.n - 8;
    bb_u32(&sy, nstr + (uint32_t)nnew + (nw ? 1 : 0));
    for (uint32_t i = 0; i < nstr; i++) bb_u32(&sy, be32r(SY + str_t + 4 + 4 * i));
    uint32_t strs = sy.n; bb_put(&sy, NULL, 4u * ((uint32_t)nnew + (nw ? 1 : 0)));
    uint32_t si = 0, lbl[SMB3_SND_MAX + 1];
    for (int i = 0; i < nS; i++) if (S[i].ok && (S[i].kind <= SND_M2 || widx[i] >= 0)) {
        lbl[i] = nstr0 + si; be32w(sy.p + strs + 4 * si, sy.n - 8); si++; bb_put(&sy, S[i].label, (uint32_t)strlen(S[i].label) + 1); }
    uint32_t grp_name = nstr0 + si;
    if (nw) { be32w(sy.p + strs + 4 * si, sy.n - 8); bb_put(&sy, "GROUP_SMB3", 11); }
    be32w(sy.p + 8, st);
    bb_pad(&sy, 0x20); be32w(sy.p + 4, sy.n);
    /* INFO: NSMBW's, then ours; new sound, file and group tables */
    bb_t in = {0}; bb_put(&in, o + io, is);
    #define IAT() (in.n - 8)
    uint32_t new_snd[SMB3_SND_MAX], new_file[SMB3_SND_MAX], nns = 0, nnf = 0;
    /* (nw4r's group count is the table's minus one: its last group - NSMBW's unnamed one, the
       files no other group has - is never loaded by number. GROUP_SMB3 goes before it, it after:
       the files that say they're in it say so with its new number) */
    uint32_t rwsd_file = nfile, gid = ngrp - 1, nsong = 0;
    static const int player_of[7] = { 17, 18, 2, 5, 5, 1, 0 };          /* (fanfare, course BGM; PLAYER_SE_PLY, _OBJ, _OBJ, _SYS, _SYS_GAME_PAUSE) */
    for (int i = 0; i < nS; i++) if (S[i].ok && S[i].kind <= SND_M2) nsong++;
    if (nw) rwsd_file = nfile + nsong;
    for (int i = 0; i < nS; i++) {
        smb3_snd_t *s = &S[i];
        if (!s->ok || (s->kind > SND_M2 && widx[i] < 0)) continue;
        int song = s->kind <= SND_M2;
        const uint8_t *t = SND(song ? (s->kind == SND_M1 ? T_JINGLE : T_SONG) : T_WAVE);
        uint32_t fid;
        if (song) {                                                     /* its file: external, /smb3/<name> */
            bb_pad(&in, 4); uint32_t path = IAT(); char p[64]; snprintf(p, sizeof p, "/smb3/%s", s->name); bb_put(&in, p, (uint32_t)strlen(p) + 1);
            bb_pad(&in, 4); uint32_t pos = IAT(); bb_u32(&in, 0);
            bb_pad(&in, 4); new_file[nnf] = IAT(); fid = nfile + nnf; nnf++;
            bb_u32(&in, s->bytes); bb_u32(&in, 0); bb_u32(&in, 0xFFFFFFFF); bb_ref(&in, path); bb_ref(&in, pos);
        } else fid = rwsd_file;
        bb_pad(&in, 4); uint32_t det = IAT();                           /* its details */
        const uint8_t *td = I0 + IREF(t + 0x18);
        if (song) bb_put(&in, td, 16);
        else { bb_u32(&in, (uint32_t)widx[i]); bb_u32(&in, 1); bb_u32(&in, 0x40000000); bb_u32(&in, 0); }
        uint32_t e = bb_put(&in, t, 0x2C); new_snd[nns++] = e - 8;      /* the sound: NSMBW's template's, ours where it differs */
        be32w(in.p + e + 0x00, lbl[i]); be32w(in.p + e + 0x04, fid); be32w(in.p + e + 0x08, (uint32_t)player_of[s->kind]);
        in.p[e + 0x14] = 0x7F; be32w(in.p + e + 0x1C, det);
        if (!song) { be32w(in.p + e + 0x20, 0); be32w(in.p + e + 0x24, 0); in.p[e + 0x2A] = 0; }
        s->sound_id = (int)(nsnd + nns - 1);
    }
    uint32_t grp_entry = 0;
    if (nw) {                                                           /* the wave sound file, its group */
        bb_pad(&in, 4); uint32_t pos = IAT(); bb_u32(&in, gid); bb_u32(&in, 0);
        uint32_t post = IAT(); bb_u32(&in, 1); bb_ref(&in, pos);
        new_file[nnf++] = IAT();
        bb_u32(&in, rwsd.n); bb_u32(&in, rwar.n); bb_u32(&in, 0xFFFFFFFF); bb_ref(&in, 0); bb_ref(&in, post);
        uint32_t item = IAT(); bb_u32(&in, rwsd_file); bb_u32(&in, 0); bb_u32(&in, rwsd.n); bb_u32(&in, 0); bb_u32(&in, rwar.n); bb_u32(&in, 0);
        uint32_t items = IAT(); bb_u32(&in, 1); bb_ref(&in, item);
        grp_entry = IAT();
        bb_u32(&in, grp_name); bb_u32(&in, 0xFFFFFFFF); bb_ref(&in, 0); bb_u32(&in, 0); bb_u32(&in, rwsd.n); bb_u32(&in, 0); bb_u32(&in, rwar.n); bb_ref(&in, items);
    }
    bb_pad(&in, 4);
    uint32_t nst = IAT(); bb_u32(&in, nsnd + nns);                       /* the tables */
    for (uint32_t i = 0; i < nsnd; i++) bb_put(&in, I0 + snd_t + 4 + 8 * i, 8);
    for (uint32_t i = 0; i < nns; i++) bb_ref(&in, new_snd[i]);
    uint32_t nft = IAT(); bb_u32(&in, nfile + nnf);
    for (uint32_t i = 0; i < nfile; i++) bb_put(&in, I0 + file_t + 4 + 8 * i, 8);
    for (uint32_t i = 0; i < nnf; i++) bb_ref(&in, new_file[i]);
    uint32_t ngt = IAT(); bb_u32(&in, ngrp + (nw ? 1 : 0));
    for (uint32_t i = 0; i + 1 < ngrp; i++) bb_put(&in, I0 + grp_t + 4 + 8 * i, 8);
    if (nw) bb_ref(&in, grp_entry);
    bb_put(&in, I0 + grp_t + 4 + 8 * (ngrp - 1), 8);
    if (nw) for (uint32_t i = 0; i < nfile; i++) {                     /* (the last group's files: its new number) */
        const uint8_t *fe = I0 + IREF(I0 + file_t + 4 + 8 * i);
        if (!be32r(fe + 0x18)) continue;
        uint32_t pt = be32r(fe + 0x18), np = be32r(I0 + pt);
        for (uint32_t k = 0; k < np; k++) { uint8_t *pos = in.p + 8 + IREF(I0 + pt + 4 + 8 * k); if (be32r(pos) == ngrp - 1) be32w(pos, ngrp); }
    }
    be32w(in.p + 8 + 4, nst); be32w(in.p + 8 + 28, nft); be32w(in.p + 8 + 36, ngt);
    bb_pad(&in, 0x20); be32w(in.p + 4, in.n);
    /* FILE: NSMBW's, then our group's data (the RWSD) and its waves (the RWAR) */
    bb_t fl = {0}; bb_put(&fl, o + fo, fs);
    uint32_t g_data = fl.n; if (nw) { bb_put(&fl, rwsd.p, rwsd.n); bb_pad(&fl, 0x20); }
    uint32_t g_wave = fl.n; if (nw) { bb_put(&fl, rwar.p, rwar.n); bb_pad(&fl, 0x20); }
    be32w(fl.p + 4, fl.n);
    /* the whole: header, SYMB, INFO, FILE - NSMBW's groups' places moved with FILE */
    uint32_t nso = 0x40, nio = nso + sy.n, nfo = nio + in.n, total = nfo + fl.n;
    int32_t delta = (int32_t)nfo - (int32_t)fo;
    for (uint32_t g = 0; g < ngrp; g++) {
        uint8_t *ge = in.p + 8 + IREF(I0 + grp_t + 4 + 8 * g);
        be32w(ge + 0x10, be32r(ge + 0x10) + (uint32_t)delta); be32w(ge + 0x18, be32r(ge + 0x18) + (uint32_t)delta);
    }
    if (nw) { uint8_t *ge = in.p + 8 + grp_entry; be32w(ge + 0x10, nfo + g_data); be32w(ge + 0x18, nfo + g_wave); smb3_group = (int)gid; }
    uint8_t *out = malloc(total); if (!out) return NULL;
    memcpy(out, o, 0x40);
    be32w(out + 8, total); be32w(out + 0x10, nso); be32w(out + 0x14, sy.n); be32w(out + 0x18, nio); be32w(out + 0x1C, in.n); be32w(out + 0x20, nfo); be32w(out + 0x24, fl.n);
    memcpy(out + nso, sy.p, sy.n); memcpy(out + nio, in.p, in.n); memcpy(out + nfo, fl.p, fl.n);
    rt_log("smb3", "sound: NSMBW's sound archive expanded - %u sounds after its %u (songs %u, effects %d: GROUP_SMB3 = group %u, %u + %u bytes), %u -> %u bytes",
           nns, nsnd, nsong, nw, gid, rwsd.n, rwar.n, n, total);
    free(sy.p); free(in.p); free(fl.p); free(rwsd.p); free(rwar.p);
    *out_n = total;
    return out;
    #undef IREF
    #undef SND
    #undef IAT
}
