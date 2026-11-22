/* nes_apu.c - the NES sound (2A03 APU): two pulse channels, triangle, noise, DMC samples, the
 * frame sequencer and the 2A03's mixer. Register writes catch the sound up to the CPU's cycle
 * first, so notes land where the game wrote them; the output is resampled to the runtime's
 * 32 kHz (533 1/3 samples per NES frame - the NES frame is paced by the runtime's 60 frames) into
 * a ring the audio side pulls from (smb3_audio). */
#include "nes_apu.h"
#include "nes_gen.h"
#include <string.h>

static const uint8_t LEN[32] = {10,254,20,2,40,4,80,6,160,8,60,10,14,12,26,14,12,16,24,18,48,20,96,22,192,24,72,26,16,28,32,30};
static const uint8_t DUTY[4][8] = {{0,1,0,0,0,0,0,0},{0,1,1,0,0,0,0,0},{0,1,1,1,1,0,0,0},{1,0,0,1,1,1,1,1}};
static const uint8_t TRI[32] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
static const uint16_t NOISE_P[16] = {4,8,16,32,64,96,128,160,202,254,380,508,762,1016,2034,4068};
static const uint16_t DMC_P[16] = {428,380,340,320,286,254,226,214,190,160,142,128,106,84,72,54};

typedef struct { uint8_t start, div, decay, loop, constant, vol; } env_t;
static void env_clock(env_t *e) {
    if (e->start) { e->start = 0; e->decay = 15; e->div = e->vol; return; }
    if (e->div) { e->div--; return; }
    e->div = e->vol;
    if (e->decay) e->decay--; else if (e->loop) e->decay = 15;
}
static int env_out(const env_t *e) { return e->constant ? e->vol : e->decay; }

static struct { env_t env; uint8_t duty, step, len, sw_en, sw_div, sw_per, sw_neg, sw_shift, sw_reload; uint16_t period, timer; } pl[2];
static struct { uint8_t ctrl, lin, lin_reload_v, lin_reload, len, step; uint16_t period, timer; } tri;
static struct { env_t env; uint8_t mode, len; uint16_t period, timer, lfsr; } noi;
static struct { uint8_t irq, loop, level, buf, buf_full, shift, bits, silent; uint16_t rate, timer, addr0, len0, addr, left; } dmc;
static uint8_t enabled, fc_mode;
static uint32_t fc_cycle;
static uint64_t apu_cyc;                       /* the cycle the sound has been made up to */

/* resampling: 533 1/3 samples per frame of 29780.5 cycles */
#define STEP (29780.5 / (32000.0 / 60.0))
static double acc_t, acc_sum; static int acc_n;
static float hp_x, hp_y;
#define RING 16384
static int16_t ring[RING];
static volatile unsigned r_w, r_r;

static uint16_t sweep_target(int i) {
    uint16_t c = (uint16_t)(pl[i].period >> pl[i].sw_shift);
    if (pl[i].sw_neg) return (uint16_t)(pl[i].period - c - (i == 0));
    return (uint16_t)(pl[i].period + c);
}
static void quarter(void) {
    env_clock(&pl[0].env); env_clock(&pl[1].env); env_clock(&noi.env);
    if (tri.lin_reload) tri.lin = tri.lin_reload_v; else if (tri.lin) tri.lin--;
    if (!(tri.ctrl & 0x80)) tri.lin_reload = 0;
}
static void half(void) {
    for (int i = 0; i < 2; i++) {
        if (!pl[i].env.loop && pl[i].len) pl[i].len--;
        if (pl[i].sw_div == 0 && pl[i].sw_en && pl[i].sw_shift && pl[i].period >= 8 && sweep_target(i) <= 0x7FF) pl[i].period = sweep_target(i);
        if (pl[i].sw_div == 0 || pl[i].sw_reload) { pl[i].sw_div = pl[i].sw_per; pl[i].sw_reload = 0; } else pl[i].sw_div--;
    }
    if (!(tri.ctrl & 0x80) && tri.len) tri.len--;
    if (!noi.env.loop && noi.len) noi.len--;
}
static float mix(void) {
    int p[2];
    for (int i = 0; i < 2; i++)
        p[i] = (pl[i].len && pl[i].period >= 8 && sweep_target(i) <= 0x7FF && DUTY[pl[i].duty][pl[i].step]) ? env_out(&pl[i].env) : 0;
    int t = TRI[tri.step];
    int n = (noi.len && !(noi.lfsr & 1)) ? env_out(&noi.env) : 0;
    int d = dmc.level;
    float po = (p[0] + p[1]) ? 95.88f / (8128.0f / (float)(p[0] + p[1]) + 100.0f) : 0;
    float td = t / 8227.0f + n / 12241.0f + d / 22638.0f;
    float to = td > 0 ? 159.79f / (1.0f / td + 100.0f) : 0;
    return po + to;
}
static void cycle(void) {
    /* frame sequencer (CPU cycles) */
    fc_cycle++;
    if (fc_mode == 0) {
        if (fc_cycle == 7457 || fc_cycle == 22371) quarter();
        else if (fc_cycle == 14913) { quarter(); half(); }
        else if (fc_cycle >= 29829) { quarter(); half(); fc_cycle = 0; }
    } else {
        if (fc_cycle == 7457 || fc_cycle == 22371) quarter();
        else if (fc_cycle == 14913) { quarter(); half(); }
        else if (fc_cycle >= 37281) { quarter(); half(); fc_cycle = 0; }
    }
    /* triangle: every CPU cycle (silent at ultrasonic periods: no pops) */
    if (tri.timer) tri.timer--;
    else { tri.timer = tri.period; if (tri.len && tri.lin && tri.period >= 2) tri.step = (tri.step + 1) & 31; }
    /* pulse / noise: every other cycle */
    if (apu_cyc & 1) {
        for (int i = 0; i < 2; i++) { if (pl[i].timer) pl[i].timer--; else { pl[i].timer = pl[i].period; pl[i].step = (pl[i].step + 1) & 7; } }
        if (noi.timer) noi.timer--;
        else { noi.timer = noi.period; uint16_t fb = (noi.lfsr ^ (noi.lfsr >> (noi.mode ? 6 : 1))) & 1; noi.lfsr = (uint16_t)(noi.lfsr >> 1 | fb << 14); }
    }
    /* DMC */
    if (dmc.timer) dmc.timer--;
    else {
        dmc.timer = (uint16_t)(dmc.rate - 1);
        if (!dmc.silent) { if (dmc.shift & 1) { if (dmc.level <= 125) dmc.level += 2; } else if (dmc.level >= 2) dmc.level -= 2; }
        dmc.shift >>= 1;
        if (dmc.bits) dmc.bits--;
        if (!dmc.bits) {
            dmc.bits = 8;
            if (dmc.buf_full) { dmc.shift = dmc.buf; dmc.buf_full = 0; dmc.silent = 0; } else dmc.silent = 1;
        }
    }
    if (!dmc.buf_full && dmc.left) {                    /* (the sample is read from the cartridge as it plays) */
        dmc.buf = nes_rd(dmc.addr); dmc.buf_full = 1;
        dmc.addr = dmc.addr == 0xFFFF ? 0x8000 : (uint16_t)(dmc.addr + 1);
        if (!--dmc.left && dmc.loop) { dmc.addr = dmc.addr0; dmc.left = dmc.len0; }
    }
    /* out: averaged over each sample's cycles, DC removed */
    acc_sum += mix(); acc_n++;
    acc_t += 1.0;
    if (acc_t >= STEP) {
        acc_t -= STEP;
        float x = (float)(acc_sum / acc_n); acc_sum = 0; acc_n = 0;
        float y = x - hp_x + 0.996f * hp_y; hp_x = x; hp_y = y;
        int v = (int)(y * 40000.0f); if (v > 32767) v = 32767; if (v < -32768) v = -32768;
        if (r_w - r_r < RING) { ring[r_w % RING] = (int16_t)v; r_w++; }
    }
}
void apu_catch_up(void) { while (apu_cyc < nes_cyc) { cycle(); apu_cyc++; } }

void apu_reset(void) {
    memset(pl, 0, sizeof pl); memset(&tri, 0, sizeof tri); memset(&noi, 0, sizeof noi); memset(&dmc, 0, sizeof dmc);
    noi.lfsr = 1; noi.period = NOISE_P[0]; dmc.rate = DMC_P[0]; dmc.bits = 8; dmc.silent = 1;
    enabled = 0; fc_mode = 0; fc_cycle = 0; apu_cyc = nes_cyc;
    acc_t = acc_sum = 0; acc_n = 0; hp_x = hp_y = 0;
    r_r = r_w;
}
void apu_write(uint16_t a, uint8_t v) {
    apu_catch_up();
    int i = (a >> 2) & 1;
    switch (a) {
    case 0x4000: case 0x4004:
        pl[i].duty = v >> 6; pl[i].env.loop = (v >> 5) & 1; pl[i].env.constant = (v >> 4) & 1; pl[i].env.vol = v & 15; break;
    case 0x4001: case 0x4005:
        pl[i].sw_en = v >> 7; pl[i].sw_per = (v >> 4) & 7; pl[i].sw_neg = (v >> 3) & 1; pl[i].sw_shift = v & 7; pl[i].sw_reload = 1; break;
    case 0x4002: case 0x4006: pl[i].period = (uint16_t)((pl[i].period & 0x700) | v); break;
    case 0x4003: case 0x4007:
        pl[i].period = (uint16_t)((pl[i].period & 0xFF) | (v & 7) << 8);
        if (enabled & (1 << i)) pl[i].len = LEN[v >> 3];
        pl[i].step = 0; pl[i].env.start = 1; break;
    case 0x4008: tri.ctrl = v; tri.lin_reload_v = v & 0x7F; break;
    case 0x400A: tri.period = (uint16_t)((tri.period & 0x700) | v); break;
    case 0x400B:
        tri.period = (uint16_t)((tri.period & 0xFF) | (v & 7) << 8);
        if (enabled & 4) tri.len = LEN[v >> 3];
        tri.lin_reload = 1; break;
    case 0x400C: noi.env.loop = (v >> 5) & 1; noi.env.constant = (v >> 4) & 1; noi.env.vol = v & 15; break;
    case 0x400E: noi.mode = v >> 7; noi.period = NOISE_P[v & 15]; break;
    case 0x400F: if (enabled & 8) noi.len = LEN[v >> 3]; noi.env.start = 1; break;
    case 0x4010: dmc.irq = v >> 7; dmc.loop = (v >> 6) & 1; dmc.rate = DMC_P[v & 15]; break;
    case 0x4011: dmc.level = v & 0x7F; break;
    case 0x4012: dmc.addr0 = (uint16_t)(0xC000 | v << 6); break;
    case 0x4013: dmc.len0 = (uint16_t)(v << 4 | 1); break;
    case 0x4015:
        enabled = v & 0x1F;
        if (!(v & 1)) pl[0].len = 0;
        if (!(v & 2)) pl[1].len = 0;
        if (!(v & 4)) tri.len = 0;
        if (!(v & 8)) noi.len = 0;
        if (!(v & 16)) dmc.left = 0;
        else if (!dmc.left) { dmc.addr = dmc.addr0; dmc.left = dmc.len0; }
        break;
    case 0x4017:
        fc_mode = v >> 7; fc_cycle = 0;
        if (fc_mode) { quarter(); half(); }
        break;
    }
}
uint8_t apu_status(void) {
    apu_catch_up();
    return (uint8_t)((pl[0].len ? 1 : 0) | (pl[1].len ? 2 : 0) | (tri.len ? 4 : 0) | (noi.len ? 8 : 0) | (dmc.left ? 16 : 0));
}
/* the next n samples (32 kHz) as stereo; what isn't there yet is the last sample held */
int apu_pull(int16_t *lr, int n, int volume_pct) {
    static int16_t last; int got = 0;
    unsigned have = r_w - r_r;
    if (have > 4096) r_r = r_w - 2048;                  /* (fallen far behind: keep the latency small) */
    for (int i = 0; i < n; i++) {
        if (r_w != r_r) { last = ring[r_r % RING]; r_r++; got++; }
        int v = last * volume_pct / 100;
        lr[2 * i] = lr[2 * i + 1] = (int16_t)v;
    }
    return got;
}
