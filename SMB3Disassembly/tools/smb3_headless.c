/* smb3_headless.c - runs the recompiled SMB3 without the NSMBW runtime: for testing.
 *   smb3_headless <rom.nes> <frames> [script] [outdir]
 * script: "frame:buttons,..." buttons from A B s(elect) S(tart) U D L R, held from that frame
 * on ("120:S,130:,300:R"). Writes outdir/fNNNNN.ppm every 60 frames and at the end. */
#include "nes.h"
#include "nes_apu.h"
#include "smb3_save.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dump(const char *dir, unsigned long f) {
    char p[512]; snprintf(p, sizeof p, "%s/f%05lu.ppm", dir, f);
    FILE *o = fopen(p, "wb"); if (!o) return;
    fprintf(o, "P6 256 240 255\n");
    const uint32_t *fb = nes_framebuffer();
    for (int i = 0; i < 256 * 240; i++) { uint8_t c[3] = {(uint8_t)(fb[i] >> 16), (uint8_t)(fb[i] >> 8), (uint8_t)fb[i]}; fwrite(c, 1, 3, o); }
    fclose(o);
}
int main(int argc, char **argv) {
    if (argc < 3) { fprintf(stderr, "usage: %s rom.nes frames [script] [outdir]\n", argv[0]); return 2; }
    FILE *f = fopen(argv[1], "rb"); if (!f) { perror(argv[1]); return 1; }
    static uint8_t buf[1 << 20]; size_t n = fread(buf, 1, sizeof buf, f); fclose(f);
    if (!nes_load(buf, (uint32_t)n)) { fprintf(stderr, "not an MMC3 iNES image\n"); return 1; }
    long frames = atol(argv[2]); const char *script = argc > 3 ? argv[3] : ""; const char *dir = argc > 4 ? argv[4] : ".";
    static smb3_save_t sv;                               /* SMB3_LOAD=file: continue from a save; SMB3_SAVE=frame:file */
    if (getenv("SMB3_LOAD")) { FILE *lf = fopen(getenv("SMB3_LOAD"), "rb"); if (lf && fread(&sv, 1, sizeof sv, lf) == sizeof sv) smb3_load_from = &sv; if (lf) fclose(lf); }
    nes_reset();
    uint8_t held = 0;
    FILE *wav = getenv("SMB3_WAV") ? fopen(getenv("SMB3_WAV"), "wb") : NULL;   /* SMB3_WAV=out.wav: the sound, 32 kHz */
    long wav_n = 0; if (wav) fwrite("RIFF\0\0\0\0WAVEfmt \x10\0\0\0\x01\0\x02\0\0\x7D\0\0\0\xF4\x01\0\x04\0\x10\0data\0\0\0\0", 1, 44, wav);
    for (long i = 0; i < frames; i++) {
        const char *s = script;                          /* (tiny script parser: entries for this frame) */
        while (*s) {
            long fr = strtol(s, (char **)&s, 10); if (*s == ':') s++;
            uint8_t b = 0;
            for (; *s && *s != ','; s++) b |= *s == 'A' ? 1 : *s == 'B' ? 2 : *s == 's' ? 4 : *s == 'S' ? 8 : *s == 'U' ? 16 : *s == 'D' ? 32 : *s == 'L' ? 64 : *s == 'R' ? 128 : 0;
            if (*s == ',') s++;
            if (fr == i) held = b;
        }
        nes_set_buttons(0, held);
        nes_run_frame();
        if (wav) { static int16_t pcm[2 * 540]; int n = (int)((i + 1) * 32000 / 60 - i * 32000 / 60); apu_pull(pcm, n, 100); fwrite(pcm, 4, (size_t)n, wav); wav_n += n; }
        if (getenv("SMB3_SAVE") && atol(getenv("SMB3_SAVE")) == i) {
            static smb3_save_t o; smb3_save_capture(&o); FILE *sf = fopen(strchr(getenv("SMB3_SAVE"), ':') + 1, "wb");
            if (sf) { fwrite(&o, 1, sizeof o, sf); fclose(sf); printf("saved at frame %ld: World %d, on map %d\n", i, o.world + 1, smb3_on_map()); }
        }
        if (getenv("SMB3_MEM") && atol(getenv("SMB3_MEM")) == i) {     /* SMB3_MEM=frame:file: RAM (2 KB) + work RAM (8 KB) */
            FILE *mf = fopen(strchr(getenv("SMB3_MEM"), ':') + 1, "wb");
            if (mf) { fwrite(nes_ram_ptr(), 1, 0x800, mf); fwrite(nes_wram_ptr(), 1, 0x2000, mf); fclose(mf); }
        }
        if (nes_error()) { fprintf(stderr, "frame %ld: %s\n", i, nes_error()); dump(dir, (unsigned long)i); return 1; }
        {   static long d0 = -1, d1, ds = 1;                 /* SMB3_DUMP=from-to:step: more pictures */
            if (d0 < 0) { const char *e = getenv("SMB3_DUMP"); d0 = 1L << 40; if (e) { d0 = atol(e); const char *m = strchr(e, '-'); d1 = m ? atol(m + 1) : d0; const char *c = strchr(e, ':'); ds = c ? atol(c + 1) : 1; } }
            if (i % 60 == 0 || i == frames - 1 || (i >= d0 && i <= d1 && (i - d0) % ds == 0)) dump(dir, (unsigned long)i); }
    }
    if (wav) { uint32_t d = (uint32_t)wav_n * 4, r = d + 36; fseek(wav, 4, SEEK_SET); fwrite(&r, 4, 1, wav); fseek(wav, 40, SEEK_SET); fwrite(&d, 4, 1, wav); fclose(wav); }
    printf("ran %ld frames\n", frames);
    return 0;
}
