/* test_smb3_physics.c - the SMB3 player physics (runtime/smb3_physics.c) on a flat floor.
 * cc -Iruntime tools/test_smb3_physics.c runtime/smb3_physics.c -o /tmp/t3 && /tmp/t3 */
#include "smb3_physics.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int fails;
#define CHECK(c, ...) do { if (!(c)) { fails++; printf("FAIL: "); printf(__VA_ARGS__); printf("\n"); } else { printf("ok:   "); printf(__VA_ARGS__); printf("\n"); } } while (0)

typedef struct { smb3_player p; float x, y; int ground; } sim_t;
static void sim_init(sim_t *s, int suit) { smb3p_init(&s->p, suit, 0); s->x = 0; s->y = 0; s->ground = 1; }
/* one frame: y up is negative (SMB3); the floor at 0 */
static void step(sim_t *s, uint8_t b) {
    smb3_motion m; smb3p_frame(&s->p, b, &m);
    s->x += m.ix; s->y += m.iy;
    if (s->y >= 0 && !(s->p.Player_YVel & 0x80)) { s->y = 0; smb3p_land(&s->p); }
    smb3p_special_frames(&s->p);
}
int main(void) {
    sim_t s;
    /* walking: top speed $18 (1.5 px a frame) */
    sim_init(&s, SMB3_BIG);
    for (int i = 0; i < 120; i++) step(&s, SMB3_RIGHT);
    CHECK(s.p.Player_XVel == 0x18, "walk top speed $%02X (want $18)", s.p.Player_XVel);
    /* running: $28, then the P-meter fills (7 steps of 8 frames after reaching run speed) and $38 */
    sim_init(&s, SMB3_BIG);
    int t_run = -1, t_full = -1, t_p = -1;
    for (int i = 0; i < 400; i++) {
        step(&s, SMB3_RIGHT | SMB3_B);
        if (t_run < 0 && s.p.Player_XVel >= 0x28) t_run = i;
        if (t_full < 0 && s.p.Player_Power == 0x7F) t_full = i;
        if (t_p < 0 && s.p.Player_XVel >= 0x38) t_p = i;
    }
    CHECK(t_run > 0, "run speed $28 after %d frames", t_run);
    CHECK(t_full > t_run, "full power meter after %d frames", t_full);
    CHECK(s.p.Player_XVel == 0x38, "P-speed $%02X after %d frames (want $38)", s.p.Player_XVel, t_p);
    /* stopping: friction */
    int t_stop = -1;
    for (int i = 0; i < 200 && t_stop < 0; i++) { step(&s, 0); if (!s.p.Player_XVel) t_stop = i; }
    CHECK(t_stop > 0, "stops from P-speed in %d frames", t_stop);
    /* jumps: standing, A held all the way; A tapped; at run speed; at P-speed */
    float hs[4]; const char *nm[4] = {"standing, A held", "standing, A tapped", "at run speed, A held", "at P-speed, A held"};
    for (int k = 0; k < 4; k++) {
        sim_init(&s, SMB3_BIG);
        if (k >= 2) for (int i = 0; i < 300; i++) step(&s, SMB3_RIGHT | SMB3_B | (k == 2 && s.p.Player_XVel >= 0x28 ? 0 : 0));
        if (k == 2) { s.p.Player_Power = 0; s.p.Player_XVel = 0x28; }
        float top = 0; int t = 0;
        step(&s, (k >= 2 ? SMB3_RIGHT | SMB3_B : 0) | SMB3_A);
        do { step(&s, (k >= 2 ? SMB3_RIGHT | SMB3_B : 0) | (k == 1 ? 0 : SMB3_A)); if (s.y < top) top = s.y; t++; } while (s.p.Player_InAir && t < 400);
        hs[k] = -top;
        printf("      %s: %.0f px high, %d frames%s\n", nm[k], -top, t, s.p.Player_FlyTime ? " (flight time set)" : "");
    }
    CHECK(hs[0] > hs[1], "holding A jumps higher (%.0f vs %.0f)", hs[0], hs[1]);
    CHECK(hs[3] >= hs[2] && hs[2] >= hs[0], "faster jumps higher (%.0f, %.0f, %.0f)", hs[0], hs[2], hs[3]);
    /* fall speed: capped at $40 (4 px a frame) + the gravity of that frame */
    sim_init(&s, SMB3_BIG); s.p.Player_InAir = 1; s.y = -2000;
    for (int i = 0; i < 200; i++) step(&s, 0);
    CHECK(s.p.Player_YVel <= 0x45, "terminal fall $%02X", s.p.Player_YVel);
    /* raccoon: flight with a full meter - A tapped keeps it rising at -$18 */
    sim_init(&s, SMB3_LEAF);
    for (int i = 0; i < 300; i++) step(&s, SMB3_RIGHT | SMB3_B);
    CHECK(s.p.Player_Power == 0x7F, "raccoon: full meter");
    step(&s, SMB3_RIGHT | SMB3_B | SMB3_A);
    CHECK(s.p.Player_FlyTime >= 0x7F, "raccoon: flight time $%02X on the jump ($80, counting down every other frame)", s.p.Player_FlyTime);
    float y0 = s.y; int frames = 0;
    for (int i = 0; i < 400 && s.p.Player_InAir; i++) { step(&s, SMB3_RIGHT | SMB3_B | ((i & 7) == 0 ? SMB3_A : 0)); frames++; if (s.y < y0) y0 = s.y; }
    CHECK(-y0 > 150, "raccoon flight: %.0f px up, %d frames in the air", -y0, frames);
    /* raccoon flutter: falling at $10 while A is tapped */
    sim_init(&s, SMB3_LEAF); s.p.Player_InAir = 1; s.y = -1000;
    for (int i = 0; i < 100; i++) step(&s, (i & 7) == 0 ? SMB3_A : 0);
    CHECK(s.p.Player_YVel == 0x10 || s.p.Player_YVel == 0x15, "raccoon flutter fall $%02X", s.p.Player_YVel);
    printf("%s\n", fails ? "FAILED" : "all ok");
    return fails != 0;
}
