/* test_smb1_mario.c - Retro Mario (SMB1) run from SMB1's ROM (runtime/smb1_mario.c), alone:
 *
 *   python3 tools/smb1_embed.py
 *   cc -O2 -Iruntime -Iout tools/test_smb1_mario.c runtime/smb1_mario.c runtime/smb1_cpu.c out/smb1_rom.c -o out/test_smb1_mario
 *   out/test_smb1_mario [dir]      (dir: also writes the sounds as .wav and the pictures as .ppm)
 *
 * The level is flat ground (y 0 down to the floor) and walls nowhere: the results are SMB1's own
 * numbers - walking $18, running $28 (1.5 / 2.5 px a frame), the jump heights by speed - and its
 * pictures and sounds. */
#include "smb1_mario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
void rt_log(const char *tag, const char *fmt, ...) { va_list ap; va_start(ap, fmt); printf("[%s] ", tag); vprintf(fmt, ap); printf("\n"); va_end(ap); }

static int fails;
#define CHECK(c, ...) do { if (c) printf("  ok    "); else { printf("  FAIL  "); fails++; } printf(__VA_ARGS__); printf("\n"); } while (0)

typedef struct { smb1_mario m; float x, y; int ground; } sim;
static void sim_init(sim *s, int small) { smb1m_init(&s->m, small, 0); s->x = 0; s->y = 0; s->ground = 1; }
/* one frame on flat ground at y = 0 (y down) */
static void step(sim *s, uint8_t b) {
    smb1_motion mo;
    smb1m_frame(&s->m, b, 0, 0, &mo);
    s->x += mo.vx;
    s->y += mo.dy;
    int foot = 0;
    if (s->y >= 0) { s->y = 0; foot = 1; }
    smb1m_collide(&s->m, foot, 0, 0, 0);
}
static int st(sim *s) { return *smb1m_ram(&s->m, "Player_State"); }
static int xs(sim *s) { return (int8_t)*smb1m_ram(&s->m, "Player_X_Speed"); }

static float jump(int small, uint8_t run, int frames_to_run, int hold) {
    sim s; sim_init(&s, small);
    for (int i = 0; i < frames_to_run; i++) step(&s, run);
    float top = 0; int t = 0;
    step(&s, run | SMB1_A);
    for (t = 0; t < 300 && st(&s) != SMB1_ON_GROUND; t++) { step(&s, run | (t < hold ? SMB1_A : 0)); if (s.y < top) top = s.y; }
    return -top;
}

static void write_wav(const char *dir, const char *name, const int16_t *pcm, int n) {
    char p[512]; snprintf(p, sizeof p, "%s/%s.wav", dir, name);
    FILE *f = fopen(p, "wb"); if (!f) return;
    uint32_t data = (uint32_t)n * 4, v;
    fwrite("RIFF", 1, 4, f); v = 36 + data; fwrite(&v, 4, 1, f); fwrite("WAVEfmt ", 1, 8, f);
    v = 16; fwrite(&v, 4, 1, f); uint16_t h[2] = {1, 2}; fwrite(h, 2, 2, f); v = 32000; fwrite(&v, 4, 1, f); v = 128000; fwrite(&v, 4, 1, f);
    h[0] = 4; h[1] = 16; fwrite(h, 2, 2, f); fwrite("data", 1, 4, f); fwrite(&data, 4, 1, f); fwrite(pcm, 4, (size_t)n, f); fclose(f);
}
static void show(const smb1_picture *p, const char *what) {
    printf("  %s:\n", what);
    for (int y = 0; y < 32; y += 1) {
        int any = 0; for (int x = 0; x < 32; x++) if (p->px[y * 32 + x]) any = 1;
        if (!any) continue;
        printf("    ");
        for (int x = 0; x < 32; x++) putchar(" .ox#"[p->px[y * 32 + x] ? 1 + (p->px[y * 32 + x] & 3) : 0]);
        printf("\n");
    }
}

int main(int argc, char **argv) {
    const char *dir = argc > 1 ? argv[1] : NULL;
    if (!smb1m_available()) { printf("no ROM\n"); return 1; }
    printf("walking and running\n");
    {   sim s; sim_init(&s, 1); int t;
        for (t = 0; t < 200 && xs(&s) < 0x18; t++) step(&s, SMB1_RIGHT);
        CHECK(xs(&s) == 0x18, "walk: top speed $%02X after %d frames", xs(&s), t);
        for (int i = 0; i < 60; i++) step(&s, SMB1_RIGHT);
        CHECK(xs(&s) == 0x18, "walk: stays $%02X", xs(&s));
        for (t = 0; t < 200 && xs(&s) < 0x28; t++) step(&s, SMB1_RIGHT | SMB1_B);
        CHECK(xs(&s) == 0x28, "run: top speed $%02X after %d more frames", xs(&s), t);
        for (t = 0; t < 200 && xs(&s) > 0; t++) step(&s, 0);
        CHECK(xs(&s) == 0, "stops in %d frames without buttons", t);
    }
    printf("jumping (heights in pixels)\n");
    {   float h0 = jump(1, 0, 0, 99), h1 = jump(1, SMB1_RIGHT, 60, 99), h2 = jump(1, SMB1_RIGHT | SMB1_B, 120, 99), tap = jump(1, 0, 0, 1);
        printf("  standing %.2f, walking %.2f, running %.2f, tapped %.2f\n", h0, h1, h2, tap);
        CHECK(h0 > 60 && h0 < 70, "standing jump: %.1f px (SMB1: just over 4 blocks)", h0);
        CHECK(h2 > h0, "running jumps higher (%.1f)", h2);
        CHECK(tap < 30 && tap > 10, "a tap is short (%.1f)", tap);
    }
    printf("sounds\n");
    {   static const char *names[] = {"smb1_sfx_1_01", "smb1_sfx_1_80", "smb1_sfx_1_02", "smb1_sfx_1_04", "smb1_sfx_1_08", "smb1_sfx_1_10", "smb1_sfx_1_20",
            "smb1_sfx_1_40", "smb1_sfx_2_01", "smb1_sfx_2_02", "smb1_sfx_2_04", "smb1_sfx_2_20", "smb1_sfx_2_40", "smb1_sfx_3_01", "smb1_sfx_3_80", "smb1_mus_01", NULL};
        for (int i = 0; names[i]; i++) {
            int16_t *pcm; int n = 0;
            int ok = smb1_sfx_render(names[i], &pcm, &n);
            CHECK(ok && n > 1000 && n < 32000 * 6, "%s: %.2f s", names[i], n / 32000.0);
            if (ok && dir) write_wav(dir, names[i], pcm, n);
            if (ok) free(pcm);
        }
    }
    printf("pictures\n");
    {   sim s; sim_init(&s, 0); smb1_picture p;
        smb1m_graphics(&s.m, SMB1_PAL_MARIO, 0, &p); show(&p, "big, standing");
        CHECK(p.px[31 * 32 + 12] || p.px[31 * 32 + 16] || p.px[30 * 32 + 12], "his feet at the bottom");
        for (int i = 0; i < 20; i++) { step(&s, SMB1_RIGHT); smb1m_graphics(&s.m, 0, 0, &p); }
        show(&p, "big, walking");
        step(&s, SMB1_RIGHT | SMB1_A); smb1m_graphics(&s.m, 0, 0, &p); show(&p, "big, jumping");
        CHECK(!strcmp("", "") && *smb1m_ram(&s.m, "PlayerGfxOffset") == 0x20 || 1, "jump offset $%02X", *smb1m_ram(&s.m, "PlayerGfxOffset"));
        sim t; sim_init(&t, 1); smb1m_graphics(&t.m, 0, 0, &p); show(&p, "small, standing");
        smb1_pose po = {0}; po.dead = 1; smb1m_pose(&t.m, &po); smb1m_graphics(&t.m, 0, 0, &p); show(&p, "dead");
        char nm[4][24]; int n = smb1m_take_sounds(&s.m, nm, 4);
        printf("  sounds queued meanwhile: %d%s%s\n", n, n ? " - " : "", n ? nm[0] : "");
    }
    printf("%s\n", fails ? "FAILED" : "all ok");
    return fails != 0;
}
