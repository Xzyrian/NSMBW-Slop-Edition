/* smw_headless.c - runs the recompiled SMW without the NSMBW runtime: for testing.
 *   smw_headless <rom.sfc> <frames> [script] [outdir]
 * script: "frame:buttons,..." buttons from A B X Y L R s(elect) S(tart) U D < >, held from that
 * frame on ("120:S,130:,300:>"). Writes outdir/fNNNNN.ppm every 60 frames and at the end;
 * SMW_DUMP=from-to:step more; SMW_MEM=frame:file the WRAM (128 KB) then. */
#include "snes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void dump(const char *dir, unsigned long f) {
    char p[512]; snprintf(p, sizeof p, "%s/f%05lu.ppm", dir, f);
    FILE *o = fopen(p, "wb"); if (!o) return;
    fprintf(o, "P6 256 224 255\n");
    const uint32_t *fb = snes_framebuffer();
    for (int i = 0; i < 256 * 224; i++) { uint8_t c[3] = {(uint8_t)(fb[i] >> 16), (uint8_t)(fb[i] >> 8), (uint8_t)fb[i]}; fwrite(c, 1, 3, o); }
    fclose(o);
}
int main(int argc, char **argv) {
    if (argc < 3) { fprintf(stderr, "usage: %s rom.sfc frames [script] [outdir]\n", argv[0]); return 2; }
    FILE *f = fopen(argv[1], "rb"); if (!f) { perror(argv[1]); return 1; }
    static uint8_t buf[4 << 20]; size_t n = fread(buf, 1, sizeof buf, f); fclose(f);
    if (!snes_load(buf, (uint32_t)n)) { fprintf(stderr, "not a LoROM image\n"); return 1; }
    long frames = atol(argv[2]); const char *script = argc > 3 ? argv[3] : ""; const char *dir = argc > 4 ? argv[4] : ".";
    if (getenv("SMW_SRAM")) { FILE *sf = fopen(getenv("SMW_SRAM"), "rb"); if (sf) { fread(snes_sram_ptr(), 1, snes_sram_size(), sf); fclose(sf); } }
    snes_reset();
    uint16_t held = 0;
    for (long i = 0; i < frames; i++) {
        const char *s = script;
        while (*s) {
            long fr = strtol(s, (char **)&s, 10); if (*s == ':') s++;
            uint16_t b = 0;
            for (; *s && *s != ','; s++)
                b |= *s == 'A' ? SNES_A : *s == 'B' ? SNES_B : *s == 'X' ? SNES_X : *s == 'Y' ? SNES_Y : *s == 'L' ? SNES_L : *s == 'R' ? SNES_R :
                     *s == 's' ? SNES_SELECT : *s == 'S' ? SNES_START : *s == 'U' ? SNES_UP : *s == 'D' ? SNES_DOWN : *s == '<' ? SNES_LEFT : *s == '>' ? SNES_RIGHT : 0;
            if (*s == ',') s++;
            if (fr == i) held = b;
        }
        snes_set_buttons(0, held);
        if (getenv("SMW_FRAMES")) fprintf(stderr, "[frame %ld]\n", i);
        snes_run_frame();
        if (getenv("SMW_PPU") && atol(getenv("SMW_PPU")) == i) {      /* SMW_PPU=frame[:vram file]: the PPU's registers (and VRAM) */
            void sppu_debug(char *, int); const uint16_t *sppu_vram(void); char b[600]; sppu_debug(b, sizeof b); printf("ppu at %ld: %s\n", i, b);
            const char *c = strchr(getenv("SMW_PPU"), ':'); if (c) { FILE *vf = fopen(c + 1, "wb"); if (vf) { fwrite(sppu_vram(), 2, 0x8000, vf); fclose(vf); } }
        }
        if (getenv("SMW_SCROLL") && i >= atol(getenv("SMW_SCROLL"))) {   /* SMW_SCROLL=frame: Mario / the layers / the PPU each frame from then */
            void sppu_debug(char *, int); char b[600]; sppu_debug(b, sizeof b); const uint8_t *w = snes_wram_ptr();
            printf("f%ld mario x %d y %d  L1 %d,%d  L2 %d,%d  | %s\n", i, w[0x94] | w[0x95] << 8, w[0x96] | w[0x97] << 8, w[0x1A] | w[0x1B] << 8, w[0x1C] | w[0x1D] << 8,
                   w[0x1E] | w[0x1F] << 8, w[0x20] | w[0x21] << 8, strstr(b, "ofs"));
        }
        if (getenv("SMW_MEM") && atol(getenv("SMW_MEM")) == i) {
            FILE *mf = fopen(strchr(getenv("SMW_MEM"), ':') + 1, "wb");
            if (mf) { fwrite(snes_wram_ptr(), 1, 0x20000, mf); fclose(mf); }
        }
        if (snes_error()) { fprintf(stderr, "frame %ld: %s\n", i, snes_error()); dump(dir, (unsigned long)i); return 1; }
        {   static long d0 = -1, d1, ds = 1;
            if (d0 < 0) { const char *e = getenv("SMW_DUMP"); d0 = 1L << 40; if (e) { d0 = atol(e); const char *m = strchr(e, '-'); d1 = m ? atol(m + 1) : d0; const char *c = strchr(e, ':'); ds = c ? atol(c + 1) : 1; } }
            if (i % 60 == 0 || i == frames - 1 || (i >= d0 && i <= d1 && (i - d0) % ds == 0)) dump(dir, (unsigned long)i); }
    }
    if (getenv("SMW_SRAM_OUT")) { FILE *sf = fopen(getenv("SMW_SRAM_OUT"), "wb"); if (sf) { fwrite(snes_sram_ptr(), 1, snes_sram_size(), sf); fclose(sf); } }
    printf("ran %ld frames\n", frames);
    return 0;
}
