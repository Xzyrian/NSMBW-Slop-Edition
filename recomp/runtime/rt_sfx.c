/* rt_sfx.c - our own sound effects, mixed into the game's audio output.
 *
 * The retro characters' sounds - SMB1 Mario's rendered from SMB1's own sound engine ("@smb1":
 * smb1_mario.c), SMB3 Mario's the build's renders of SMB3's ("@smb3": <game>/sound/smb3/<name>.rwav),
 * or a .wav (ui/retro/<dir>/sfx/<name>.wav, any rate, 8/16-bit, mono or stereo) - are made or
 * loaded on first use, resampled to the game's 32 kHz stereo and mixed into each block
 * the game's audio DMA hands to the host (rt_hw.c -> sfx_mix -> plat_audio_push). A sound that is
 * started again while it plays restarts (like the NES's sound channels); up to 8 play at once.
 * settings.ini retro_sfx_volume (0-100, default 70). */
#include "rt.h"

#define MAXCLIP 64
#define VOICES 8
typedef struct { char key[96]; int16_t *pcm; int frames; int state; } clip_t;   /* state 0 untried, 1 ok, -1 missing */
static clip_t clips[MAXCLIP];
static int nclips;
static struct { int clip, pos; uint64_t started; } V[VOICES];
static uint64_t started_n;

static uint32_t le32(const uint8_t *p) { return p[0] | p[1] << 8 | p[2] << 16 | (uint32_t)p[3] << 24; }
static uint16_t le16(const uint8_t *p) { return (uint16_t)(p[0] | p[1] << 8); }

/* a PCM .wav -> 32 kHz stereo int16 (linear resampling); 0 = can't read it */
static int load_wav(const char *path, int16_t **out, int *out_frames) {
    FILE *f = fopen(path, "rb"); if (!f) return 0;
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
    uint8_t *d = malloc(n > 0 ? n : 1);
    if (n < 44 || fread(d, 1, n, f) != (size_t)n) { fclose(f); free(d); return 0; }
    fclose(f);
    if (memcmp(d, "RIFF", 4) || memcmp(d + 8, "WAVE", 4)) { free(d); return 0; }
    int ch = 0, rate = 0, bits = 0; const uint8_t *data = NULL; uint32_t dlen = 0;
    for (long p = 12; p + 8 <= n; ) {
        uint32_t len = le32(d + p + 4);
        if (!memcmp(d + p, "fmt ", 4) && len >= 16) {
            if (le16(d + p + 8) != 1) { free(d); return 0; }               /* PCM only */
            ch = le16(d + p + 10); rate = (int)le32(d + p + 12); bits = le16(d + p + 22);
        } else if (!memcmp(d + p, "data", 4)) { data = d + p + 8; dlen = len; if (p + 8 + (long)dlen > n) dlen = (uint32_t)(n - p - 8); }
        p += 8 + len + (len & 1);
    }
    if (!data || ch < 1 || ch > 2 || rate < 1000 || (bits != 8 && bits != 16)) { free(d); return 0; }
    int bps = bits / 8 * ch, in_frames = (int)(dlen / bps);
    int frames = (int)((int64_t)in_frames * 32000 / rate);
    int16_t *pcm = malloc(sizeof(int16_t) * 2 * (frames > 0 ? frames : 1));
    for (int i = 0; i < frames; i++) {
        double src = (double)i * rate / 32000.0; int a = (int)src; double t = src - a;
        int b = a + 1 < in_frames ? a + 1 : a;
        for (int c = 0; c < 2; c++) {
            int cc = ch == 2 ? c : 0; double va, vb;
            if (bits == 16) { va = (int16_t)le16(data + a * bps + cc * 2); vb = (int16_t)le16(data + b * bps + cc * 2); }
            else { va = (data[a * bps + cc] - 128) * 256.0; vb = (data[b * bps + cc] - 128) * 256.0; }
            pcm[2 * i + c] = (int16_t)(va + (vb - va) * t);
        }
    }
    free(d);
    *out = pcm; *out_frames = frames;
    return 1;
}

/* SMB3's sound effects as the build renders them (SMB3Disassembly/port/smb3_sound.c write_rwav):
   an RWAV, one channel of DSP-ADPCM (frames of 8 bytes: predictor / scale, 14 nibbles) -> 32 kHz
   stereo int16 */
static uint32_t be32(const uint8_t *p) { return (uint32_t)p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3]; }
static int load_rwav(const char *path, int16_t **out, int *out_frames) {
    FILE *f = fopen(path, "rb"); if (!f) return 0;
    fseek(f, 0, SEEK_END); long n = ftell(f); fseek(f, 0, SEEK_SET);
    uint8_t *d = malloc(n > 0 ? n : 1);
    if (n < 0xA8 || fread(d, 1, n, f) != (size_t)n) { fclose(f); free(d); return 0; }
    fclose(f);
    const uint8_t *w = d + 0x28;                                        /* (INFO's body) */
    if (memcmp(d, "RWAV", 4) || memcmp(d + 0x20, "INFO", 4) || w[0] != 2) { free(d); return 0; }   /* (DSP-ADPCM only) */
    int rate = w[4] << 8 | w[5];
    uint32_t e = be32(w + 0x0C);
    int samples = (int)((e - 2) / 16 * 14 + (e - 2) % 16) + 1;
    int16_t coef[16]; for (int k = 0; k < 16; k++) coef[k] = (int16_t)(w[0x3C + 2 * k] << 8 | w[0x3C + 2 * k + 1]);
    const uint8_t *data = d + 0xA8;
    int nf = (samples + 13) / 14;
    if (rate < 1000 || samples < 1 || 0xA8 + (long)nf * 8 > n) { free(d); return 0; }
    int16_t *mono = malloc(sizeof(int16_t) * (size_t)nf * 14);
    int h1 = 0, h2 = 0;
    for (int i = 0; i < nf; i++) {
        const uint8_t *fr = data + i * 8; int pred = (fr[0] >> 4) & 7, scale = 1 << (fr[0] & 15);
        for (int k = 0; k < 14; k++) {
            int nib = (fr[1 + k / 2] >> ((k & 1) ? 0 : 4)) & 15; if (nib >= 8) nib -= 16;
            int v = (coef[pred * 2] * h1 + coef[pred * 2 + 1] * h2 + ((nib * scale) << 11) + 1024) >> 11;
            v = v > 32767 ? 32767 : v < -32768 ? -32768 : v;
            mono[i * 14 + k] = (int16_t)v; h2 = h1; h1 = v;
        }
    }
    int frames = (int)((int64_t)samples * 32000 / rate);
    int16_t *pcm = malloc(sizeof(int16_t) * 2 * (frames > 0 ? frames : 1));
    for (int i = 0; i < frames; i++) {
        double src = (double)i * rate / 32000.0; int a = (int)src; double t = src - a; int b = a + 1 < samples ? a + 1 : a;
        int16_t v = (int16_t)(mono[a] + (mono[b] - mono[a]) * t); pcm[2 * i] = pcm[2 * i + 1] = v;
    }
    free(mono); free(d);
    *out = pcm; *out_frames = frames;
    return 1;
}
static int clip_of(const char *dir, const char *name) {
    char key[96]; snprintf(key, sizeof key, "%s/%s", dir, name);
    for (int i = 0; i < nclips; i++) if (!strcmp(clips[i].key, key)) return clips[i].state > 0 ? i : -1;
    if (nclips >= MAXCLIP) return -1;
    clip_t *c = &clips[nclips];
    snprintf(c->key, sizeof c->key, "%s", key);
    char path[1300];
    if (!strcmp(dir, "@smb1")) {                                        /* (SMB1's own: its SoundEngine run on the ROM, smb1_mario.c) */
        int smb1_sfx_render(const char *name, int16_t **pcm, int *frames);
        snprintf(path, sizeof path, "SMB1 SoundEngine: %s", name);
        c->state = smb1_sfx_render(name, &c->pcm, &c->frames) ? 1 : -1;
    } else if (!strcmp(dir, "@smb3")) {                                 /* (SMB3's own: <game>/sound/smb3/<name>.rwav) */
        snprintf(path, sizeof path, "%s/sound/smb3/%s.rwav", g_root, name);
        c->state = load_rwav(path, &c->pcm, &c->frames) ? 1 : -1;
    } else {
        snprintf(path, sizeof path, "%s/ui/retro/%s/sfx/%s.wav", g_root, dir, name);
        c->state = load_wav(path, &c->pcm, &c->frames) ? 1 : -1;
    }
    if (c->state < 0) rt_log("sfx", "no %s", path);
    else rt_log("sfx", "%s: %d frames", key, c->frames);
    return nclips++, c->state > 0 ? nclips - 1 : -1;
}

/* play ui/retro/<dir>/sfx/<name>.wav */
void sfx_play(const char *dir, const char *name) {
    if (g_resim) return;                            /* (fields run again after a rollback: heard the first time) */
    int c = clip_of(dir, name);
    if (c < 0) return;
    int v = -1;
    for (int i = 0; i < VOICES; i++) if (V[i].clip == c + 1) v = i;          /* (the same sound: restart it) */
    if (v < 0) for (int i = 0; i < VOICES; i++) if (!V[i].clip) { v = i; break; }
    if (v < 0) { v = 0; for (int i = 1; i < VOICES; i++) if (V[i].started < V[v].started) v = i; }   /* (all busy: the oldest) */
    V[v].clip = c + 1; V[v].pos = 0; V[v].started = ++started_n;
    { static int lg = -1; if (lg < 0) lg = getenv("RT_SFX_LOG") != NULL; if (lg) rt_log("sfx", "play %s/%s", dir, name); }
}
/* the same, unless that sound is still playing (a sound set every frame that rings on: SMB3's power meter) */
void sfx_play_ifidle(const char *dir, const char *name) {
    int c = clip_of(dir, name);
    if (c < 0) return;
    for (int i = 0; i < VOICES; i++) if (V[i].clip == c + 1) return;
    sfx_play(dir, name);
}
/* made / loaded now rather than when first played (SMB1's are rendered: a moment each) */
void sfx_preload(const char *dir, const char *name) { (void)clip_of(dir, name); }
void sfx_stop_all(void) { for (int i = 0; i < VOICES; i++) V[i].clip = 0; }

/* add the playing sounds to a block of 32 kHz stereo */
void sfx_mix(int16_t *pcm, int frames) {
    int any = 0; for (int i = 0; i < VOICES; i++) if (V[i].clip) any = 1;
    if (!any) return;
    static int vol = -1; if (vol < 0) { vol = rt_setting("retro_sfx_volume", 70); if (vol > 100) vol = 100; if (vol < 0) vol = 0; }
    for (int i = 0; i < VOICES; i++) {
        if (!V[i].clip) continue;
        clip_t *c = &clips[V[i].clip - 1];
        int n = c->frames - V[i].pos; if (n > frames) n = frames;
        const int16_t *s = c->pcm + 2 * V[i].pos;
        for (int k = 0; k < 2 * n; k++) {
            int v = pcm[k] + s[k] * vol / 100;
            pcm[k] = (int16_t)(v > 32767 ? 32767 : v < -32768 ? -32768 : v);
        }
        V[i].pos += n;
        if (V[i].pos >= c->frames) V[i].clip = 0;
    }
}
