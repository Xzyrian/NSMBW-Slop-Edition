/* smb1_mario.c - Retro Mario (SMB1): Super Mario Bros.' own player code (see smb1_mario.h). */
#include "smb1_mario.h"
#include "smb1_cpu.h"
#include "smb1_syms.h"                      /* out/: tools/smb1_embed.py */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void rt_log(const char *tag, const char *fmt, ...);
extern const uint8_t smb1_rom[]; extern const uint32_t smb1_rom_size;

#if SMB1_HAVE_ROM
#define A(name) SMB1_##name
#define BANK(name) SMB1_##name##_BANK

/* ------------------------------------------------------------------ the ROM */
static int nprg(void) { return smb1_rom_size >= 16 ? smb1_rom[4] : 0; }
static const uint8_t *prg(int b) { if (b < 0) b = nprg() - 1; return smb1_rom + 16 + (uint32_t)b * 16384u; }
static const uint8_t *chr(void) { return smb1_rom + 16 + (uint32_t)nprg() * 16384u; }
int smb1m_available(void) {
    static int ok = -1;
    if (ok < 0) {
        ok = smb1_rom_size >= 16 && !memcmp(smb1_rom, "NES\x1A", 4) && nprg() >= 4 && smb1_rom[5] >= 1 &&
             smb1_rom_size >= 16 + (uint32_t)nprg() * 16384u + 4096u;
        if (!ok) rt_log("smb1", "SMBBase.nes isn't a ROM SMB1 Mario can use");
    }
    return ok;
}
/* a byte of the ROM at a label (its bank's, or the fixed bank's) */
static uint8_t rom_at(uint16_t addr, int bank, int i) {
    if (addr >= 0xC000) return prg(-1)[addr - 0xC000 + i];
    return prg(bank)[addr - 0x8000 + i];
}

static int run(smb1_mario *m, uint16_t addr, int bank, void (*apu)(void *, uint16_t, uint8_t), void *user) {
    smb1_cpu c; memset(&c, 0, sizeof c);
    c.ram = m->ram; c.bank8 = prg(bank < 0 ? 0 : bank); c.bankC = prg(-1);
    c.s = 0xFD; c.p = 0x24; c.apu = apu; c.user = user;
    if (smb1_cpu_call(&c, addr, 200000) == 0) return 0;
    static int said; if (said++ < 8) rt_log("smb1", "the 6502 stopped at $%04X (%s $%02X) running $%04X", c.pc, c.error == 0x200 ? "too long" : "opcode", c.error & 0xFF, addr);
    return -1;
}
static void take_queues(smb1_mario *m) {
    uint8_t *r = m->ram;
    m->sfx[0] |= r[A(Square1SoundQueue)]; m->sfx[1] |= r[A(Square2SoundQueue)];
    m->sfx[2] |= r[A(NoiseSoundQueue)]; m->sfx[3] |= r[A(EventMusicQueue)];
    r[A(Square1SoundQueue)] = r[A(Square2SoundQueue)] = r[A(NoiseSoundQueue)] = r[A(EventMusicQueue)] = 0;
}

/* ------------------------------------------------------------------ movement */
void smb1m_init(smb1_mario *m, int small, int face_left) {
    memset(m, 0, sizeof *m);
    uint8_t *r = m->ram;
    r[A(OperMode)] = 1;                                     /* (the game) */
    r[A(GameEngineSubroutine)] = 8;                         /* PlayerCtrlRoutine */
    r[A(AreaType)] = 1;                                     /* ground */
    r[A(PlayerSize)] = small ? 1 : 0;
    r[A(PlayerStatus)] = small ? 0 : 1;
    r[A(PlayerFacingDir)] = r[A(Player_MovingDir)] = face_left ? SMB1_FACE_LEFT : SMB1_FACE_RIGHT;
    r[A(Player_Y_HighPos)] = 1; r[A(Player_Y_Position)] = 0x80;
    r[A(VerticalForceDown)] = 0x28;                         /* (Entrance_GameTimerSetup) */
    r[A(Player_CollisionBits)] = 0xFF;
    r[A(IntervalTimerControl)] = 0x14;
    r[A(Player_SprDataOffset)] = 0x10;
}
uint8_t *smb1m_ram(smb1_mario *m, const char *what) {
    static const struct { const char *n; uint16_t a; } T[] = {
        {"Player_State", A(Player_State)}, {"Player_X_Speed", A(Player_X_Speed)}, {"Player_Y_Speed", A(Player_Y_Speed)},
        {"Player_Y_MoveForce", A(Player_Y_MoveForce)}, {"PlayerFacingDir", A(PlayerFacingDir)}, {"Player_MovingDir", A(Player_MovingDir)},
        {"Player_XSpeedAbsolute", A(Player_XSpeedAbsolute)}, {"Player_X_MoveForce", A(Player_X_MoveForce)}, {"PlayerSize", A(PlayerSize)},
        {"SwimmingFlag", A(SwimmingFlag)}, {"CrouchingFlag", A(CrouchingFlag)}, {"PlayerGfxOffset", A(PlayerGfxOffset)},
        {"PlayerAnimCtrl", A(PlayerAnimCtrl)}, {"RunningSpeed", A(RunningSpeed)}, {"VerticalForce", A(VerticalForce)},
        {"Player_CollisionBits", A(Player_CollisionBits)}, {"FrameCounter", A(FrameCounter)}, {NULL, 0} };
    for (int i = 0; T[i].n; i++) if (!strcmp(T[i].n, what)) return &m->ram[T[i].a];
    return NULL;
}
/* NMI: DecTimers, then inc FrameCounter (TimerControl is never set here) */
void smb1m_timers(smb1_mario *m) {
    uint8_t *r = m->ram;
    int x = 0x14;
    if ((int8_t)--r[A(IntervalTimerControl)] < 0) { r[A(IntervalTimerControl)] = 0x14; x = 0x23; }
    for (; x >= 0; x--) if (r[A(Timers) + x]) r[A(Timers) + x]--;
    r[A(FrameCounter)]++;
}
static int32_t y_fine(const uint8_t *r) {                   /* the vertical position in 1/256 pixels */
    return ((int32_t)(int8_t)r[A(Player_Y_HighPos)] << 16) | r[A(Player_Y_Position)] << 8 | r[A(Player_YMF_Dummy)];
}
void smb1m_frame(smb1_mario *m, uint8_t buttons, int swimming, int water_top, smb1_motion *out) {
    uint8_t *r = m->ram;
    memset(out, 0, sizeof *out);
    if (!smb1m_available()) return;
    smb1m_timers(m);
    /* the last frame's SaveAB */
    r[A(PreviousA_B_Buttons)] = r[A(A_B_Buttons)];
    r[A(Left_Right_Buttons)] = 0;
    r[A(OperMode)] = 1; r[A(GameEngineSubroutine)] = 8; r[A(TimerControl)] = 0; r[A(CurrentPlayer)] = 0;
    r[A(PlayerChangeSizeFlag)] = 0;                         /* (the pictures' only: m->grow) */
    r[A(JumpspringAnimCtrl)] = 0;                           /* (NSMBW's springboards launch him: smb1m_spring) */
    r[A(Whirlpool_Flag)] = 0;
    r[A(SwimmingFlag)] = swimming ? 1 : 0;
    r[A(AreaType)] = swimming ? 0 : 1;                      /* (a water area while he swims) */
    /* the level is NSMBW's: his height is kept on the screen's playing field - the water's surface
       at the top ($14: can't swim higher) - with where he jumped from kept the same above him */
    uint8_t rel = (uint8_t)(r[A(JumpOrigin_Y_Position)] - r[A(Player_Y_Position)]);
    r[A(Player_Y_HighPos)] = 1;
    r[A(Player_Y_Position)] = water_top ? 0x10 : 0x80;
    r[A(JumpOrigin_Y_Position)] = (uint8_t)(r[A(Player_Y_Position)] + rel);
    /* PlayerCtrlRoutine: the controller */
    r[A(SavedJoypadBits)] = buttons;
    r[A(A_B_Buttons)] = buttons & 0xC0;
    r[A(Left_Right_Buttons)] = buttons & 0x03;
    r[A(Up_Down_Buttons)] = buttons & 0x0C;
    if ((buttons & 0x04) && r[A(Player_State)] == 0 && r[A(Left_Right_Buttons)]) r[A(Left_Right_Buttons)] = r[A(Up_Down_Buttons)] = 0;
    int32_t y0 = y_fine(r);
    run(m, A(PlayerMovementSubs), BANK(PlayerMovementSubs), NULL, NULL);
    /* ChkMoveDir */
    r[A(Player_BoundBoxCtrl)] = r[A(PlayerSize)] ? 1 : r[A(CrouchingFlag)] ? 2 : 0;
    if (r[A(Player_X_Speed)]) r[A(Player_MovingDir)] = (int8_t)r[A(Player_X_Speed)] > 0 ? 1 : 2;
    out->dy = (float)(y_fine(r) - y0) / 256.0f;
    out->vx = (int8_t)r[A(Player_X_Speed)] / 16.0f;
    out->jumped = r[A(JumpSwimTimer)] == 0x20;
    take_queues(m);
}
void smb1m_collide(smb1_mario *m, int foot, int head, int wall_right, int wall_left) {
    uint8_t *r = m->ram;
    if (r[A(SwimmingFlag)]) r[A(Player_State)] = 1;
    else if (r[A(Player_State)] == 0 || r[A(Player_State)] == 3) r[A(Player_State)] = 2;
    r[A(Player_CollisionBits)] = 0xFF;
    if (head && (int8_t)r[A(Player_Y_Speed)] < 0)             /* NYSpd */
        r[A(Player_Y_Speed)] = SMB1_CFG_WATER_SPEED_FIX && !r[A(AreaType)] ? 0 : 1;
    if (foot && (int8_t)r[A(Player_Y_Speed)] >= 0) {          /* LandPlyr */
        r[A(Player_Y_Position)] &= 0xF0;
        r[A(Player_Y_Speed)] = 0; r[A(Player_Y_MoveForce)] = 0; r[A(StompChainCounter)] = 0;
        r[A(Player_State)] = 0;
    }
    /* ImpedePlayerMove */
    if (wall_right) {
        if ((int8_t)r[A(Player_X_Speed)] >= 0) { r[A(SideCollisionTimer)] = 0x10; r[A(Player_X_Speed)] = 0; }
        r[A(Player_CollisionBits)] &= (uint8_t)~1;
    }
    if (wall_left) {
        if ((int8_t)r[A(Player_X_Speed)] < 1) { r[A(SideCollisionTimer)] = 0x10; r[A(Player_X_Speed)] = 0; }
        r[A(Player_CollisionBits)] &= (uint8_t)~2;
    }
}
void smb1m_stomp(smb1_mario *m, int high) {
    uint8_t *r = m->ram;
    r[A(Player_Y_Speed)] = SMB1_CFG_EXTRA_BOUNCE ? (high ? 0xF8 : 0xFA) : 0xFC;   /* SetBounce */
    if (r[A(Player_State)] == 0) r[A(Player_State)] = 2;
    m->sfx[0] |= 0x04;                                       /* Sfx_EnemyStomp */
}
void smb1m_spring(smb1_mario *m, int a_held) {
    uint8_t *r = m->ram;
    r[A(Player_Y_Speed)] = a_held ? 0xF4 : 0xF9;             /* JumpspringForce */
    r[A(Player_Y_MoveForce)] = 0;
    if (SMB1_CFG_JUMPSPRING_FIX) r[A(VerticalForce)] = 0x40;
    r[A(Player_State)] = 2;
}
void smb1m_fire(smb1_mario *m) {
    uint8_t *r = m->ram;
    uint8_t t = r[A(PlayerAnimTimerSet)];
    r[A(FireballThrowingTimer)] = t;
    r[A(PlayerAnimTimer)] = (uint8_t)(t - 1);
}
void smb1m_set_size(smb1_mario *m, int small, int animate) {
    uint8_t *r = m->ram;
    if (r[A(PlayerSize)] == (small ? 1 : 0)) return;
    r[A(PlayerSize)] = small ? 1 : 0;
    if (small) r[A(CrouchingFlag)] = 0;
    if (animate) { m->grow = 1; r[A(PlayerAnimCtrl)] = 0; }
}
void smb1m_fire_flash(smb1_mario *m) { m->flash = 0x40; }

void smb1m_pose(smb1_mario *m, const smb1_pose *p) {
    uint8_t *r = m->ram;
    r[A(GameEngineSubroutine)] = p->dead ? 0x0B : 8;
    r[A(SwimmingFlag)] = p->swimming ? 1 : 0;
    r[A(PlayerFacingDir)] = r[A(Player_MovingDir)] = p->face_left ? 2 : 1;
    r[A(CrouchingFlag)] = p->crouching && !r[A(PlayerSize)] ? 4 : 0;
    r[A(A_B_Buttons)] = 0;
    if (p->climbing) {                                      /* PlayerPhysicsSub, climbing: ProcClimb */
        r[A(Player_State)] = 3;
        r[A(Player_Y_Speed)] = p->climb_dir < 0 ? 0xFF : p->climb_dir > 0 ? 0x01 : 0x00;
        r[A(PlayerAnimTimerSet)] = (int8_t)r[A(Player_Y_Speed)] < 0 ? 8 : 4;
        r[A(Player_X_Speed)] = 0; r[A(Left_Right_Buttons)] = 0;
    } else if (p->in_air) {
        r[A(Player_State)] = 1;
        r[A(Player_X_Speed)] = (uint8_t)(int8_t)p->speed; r[A(Left_Right_Buttons)] = 0;
    } else {
        int a = p->speed < 0 ? -p->speed : p->speed; if (a > 0x7F) a = 0x7F;
        r[A(Player_State)] = 0;
        r[A(Player_X_Speed)] = (uint8_t)(int8_t)p->speed; r[A(Player_XSpeedAbsolute)] = (uint8_t)a;
        r[A(Left_Right_Buttons)] = p->speed ? (p->speed > 0 ? 1 : 2) : 0;
        r[A(PlayerAnimTimerSet)] = a >= 0x1C ? 2 : a >= 0x0E ? 4 : 7;   /* (GetPlayerAnimSpeed) */
    }
}

/* ------------------------------------------------------------------ pictures */
void smb1m_graphics(smb1_mario *m, int pal, int star_frames, smb1_picture *out) {
    uint8_t *r = m->ram;
    memset(out, 0, sizeof *out);
    if (!smb1m_available()) return;
    for (int i = 0; i < 256; i += 4) r[A(Sprite_Data) + i] = 0xF8;   /* (MoveAllSpritesOffscreen) */
    r[A(Player_Rel_XPos)] = 0x70; r[A(Player_Rel_YPos)] = 0x80;
    r[A(Player_SprDataOffset)] = 0x10; r[A(Player_OffscreenBits)] = 0;
    r[A(InjuryTimer)] = 0;                                  /* (NSMBW blinks the hurt player) */
    r[A(PlayerChangeSizeFlag)] = m->grow ? 1 : 0;
    /* palette bits: the star's cycling (CyclePlayerPalette: every other frame, every eighth near
       the end - StarInvincibleTimer < 8 of its 21-frame ticks), Fire Mario's flashing */
    uint8_t pb = 0;
    if (star_frames > 0) pb = (uint8_t)((star_frames >= 8 * 21 ? r[A(FrameCounter)] >> 1 : r[A(FrameCounter)] >> 3) & 3);
    else if (m->flash > 0) { m->flash--; pb = (uint8_t)((r[A(FrameCounter)] >> 2) & 3); }
    r[A(Player_SprAttrib)] = (uint8_t)((r[A(Player_SprAttrib)] & 0xDC) | pb);   /* (no background priority: NSMBW layers) */
    run(m, A(PlayerGfxHandler), 0, NULL, NULL);
    if (m->grow && !r[A(PlayerChangeSizeFlag)]) m->grow = 0;
    r[A(PlayerChangeSizeFlag)] = 0;
    take_queues(m);
    /* the 8 sprites -> the picture */
    const uint8_t *pt = chr();                              /* (sprites: pattern table $0000 - CHR0/CHR1, the first 4 KB) */
    int bx = 0x70 - 8, by = 0x80;
    uint8_t *spr = &r[A(Sprite_Data) + r[A(Player_SprDataOffset)]];
    for (int s = 0; s < 8; s++) {
        const uint8_t *o = spr + s * 4;
        if (o[0] >= 0xF0) continue;
        int x0 = o[3] - bx, y0 = o[0] - by, a = o[2], pl = a & 3;
        const uint8_t *t = pt + o[1] * 16;
        for (int yy = 0; yy < 8; yy++) for (int xx = 0; xx < 8; xx++) {
            int sy = (a & 0x80) ? 7 - yy : yy, sx = (a & 0x40) ? xx : 7 - xx;
            int v = ((t[sy] >> sx) & 1) | ((t[sy + 8] >> sx) & 1) << 1;
            int px = x0 + xx, py = y0 + yy;
            if (v && px >= 0 && px < 32 && py >= 0 && py < 32) out->px[py * 32 + px] = (uint8_t)(pl * 4 + v);
        }
    }
    /* colours: palette 0 Mario's (PlayerColors: Mario's, the fiery one), 1-3 the ground's sprite palettes */
    uint16_t pc = A(PlayerColors); int pcb = BANK(PlayerColors);
    for (int c = 1; c < 4; c++) out->colours[c] = rom_at(pc, pcb, (pal == SMB1_PAL_FIERY ? 8 : 0) + c);
    if (pal == SMB1_PAL_ICE) { out->colours[1] = 0x31; out->colours[3] = 0x11; }   /* (no Ice Flower in SMB1: light blue, blue) */
    for (int p = 1; p < 4; p++) for (int c = 1; c < 4; c++) out->colours[p * 4 + c] = rom_at(A(GroundPaletteData), BANK(GroundPaletteData), 3 + 16 + p * 4 + c);
    uint64_t h = 1469598103934665603ull;
    for (int i = 0; i < 32 * 32; i++) h = (h ^ out->px[i]) * 1099511628211ull;
    for (int i = 0; i < 16; i++) h = (h ^ out->colours[i]) * 1099511628211ull;
    out->hash = h;
}

/* ------------------------------------------------------------------ sounds */
static void name_of(char *dst, int q, int bit) {
    if (q == 3) snprintf(dst, 24, "smb1_mus_%02X", bit);
    else snprintf(dst, 24, "smb1_sfx_%d_%02X", q + 1, bit);
}
int smb1m_take_sounds(smb1_mario *m, char names[][24], int max) {
    int n = 0;
    for (int q = 0; q < 4 && n < max; q++) {
        uint8_t v = m->sfx[q]; m->sfx[q] = 0;
        if (!v) continue;
        int bit = (v & 0x80) ? 0x80 : (v & -v);             /* (the sound engine's order: d7 first, then d0 up) */
        name_of(names[n++], q, bit);
    }
    return n;
}

/* the 2A03's two pulses, triangle and noise (no samples: SMB1's sounds have none), stepped a
   CPU cycle at a time and averaged down to 32 kHz (as SMB3Disassembly/port/nes_apu.c) */
static const uint8_t LEN[32] = {10,254,20,2,40,4,80,6,160,8,60,10,14,12,26,14,12,16,24,18,48,20,96,22,192,24,72,26,16,28,32,30};
static const uint8_t DUTY[4][8] = {{0,1,0,0,0,0,0,0},{0,1,1,0,0,0,0,0},{0,1,1,1,1,0,0,0},{1,0,0,1,1,1,1,1}};
static const uint8_t TRI[32] = {15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
static const uint16_t NOISE_P[16] = {4,8,16,32,64,96,128,160,202,254,380,508,762,1016,2034,4068};
typedef struct { uint8_t start, div, decay, loop, constant, vol; } env_t;
typedef struct {
    struct { env_t env; uint8_t duty, step, len, sw_en, sw_div, sw_per, sw_neg, sw_shift, sw_reload; uint16_t period, timer; } pl[2];
    struct { uint8_t ctrl, lin, lin_reload_v, lin_reload, len, step; uint16_t period, timer; } tri;
    struct { env_t env; uint8_t mode, len; uint16_t period, timer, lfsr; } noi;
    uint8_t enabled, fc_mode; uint32_t fc_cycle; uint64_t cyc;
    double acc_t, acc_sum; int acc_n; float hp_x, hp_y;
    int16_t *out; int n, cap;
} apu_t;
static void env_clock(env_t *e) {
    if (e->start) { e->start = 0; e->decay = 15; e->div = e->vol; return; }
    if (e->div) { e->div--; return; }
    e->div = e->vol;
    if (e->decay) e->decay--; else if (e->loop) e->decay = 15;
}
static int env_out(const env_t *e) { return e->constant ? e->vol : e->decay; }
static uint16_t sweep_target(apu_t *u, int i) {
    uint16_t c = (uint16_t)(u->pl[i].period >> u->pl[i].sw_shift);
    return u->pl[i].sw_neg ? (uint16_t)(u->pl[i].period - c - (i == 0)) : (uint16_t)(u->pl[i].period + c);
}
static void quarter(apu_t *u) {
    env_clock(&u->pl[0].env); env_clock(&u->pl[1].env); env_clock(&u->noi.env);
    if (u->tri.lin_reload) u->tri.lin = u->tri.lin_reload_v; else if (u->tri.lin) u->tri.lin--;
    if (!(u->tri.ctrl & 0x80)) u->tri.lin_reload = 0;
}
static void half(apu_t *u) {
    for (int i = 0; i < 2; i++) {
        if (!u->pl[i].env.loop && u->pl[i].len) u->pl[i].len--;
        if (u->pl[i].sw_div == 0 && u->pl[i].sw_en && u->pl[i].sw_shift && u->pl[i].period >= 8 && sweep_target(u, i) <= 0x7FF) u->pl[i].period = sweep_target(u, i);
        if (u->pl[i].sw_div == 0 || u->pl[i].sw_reload) { u->pl[i].sw_div = u->pl[i].sw_per; u->pl[i].sw_reload = 0; } else u->pl[i].sw_div--;
    }
    if (!(u->tri.ctrl & 0x80) && u->tri.len) u->tri.len--;
    if (!u->noi.env.loop && u->noi.len) u->noi.len--;
}
static void apu_cycle(apu_t *u) {
    u->fc_cycle++;
    if (u->fc_cycle == 7457 || u->fc_cycle == 22371) quarter(u);
    else if (u->fc_cycle == 14913) { quarter(u); half(u); }
    else if (u->fc_cycle >= (u->fc_mode ? 37281u : 29829u)) { quarter(u); half(u); u->fc_cycle = 0; }
    if (u->tri.timer) u->tri.timer--;
    else { u->tri.timer = u->tri.period; if (u->tri.len && u->tri.lin && u->tri.period >= 2) u->tri.step = (u->tri.step + 1) & 31; }
    if (u->cyc & 1) {
        for (int i = 0; i < 2; i++) { if (u->pl[i].timer) u->pl[i].timer--; else { u->pl[i].timer = u->pl[i].period; u->pl[i].step = (u->pl[i].step + 1) & 7; } }
        if (u->noi.timer) u->noi.timer--;
        else { u->noi.timer = u->noi.period; uint16_t fb = (u->noi.lfsr ^ (u->noi.lfsr >> (u->noi.mode ? 6 : 1))) & 1; u->noi.lfsr = (uint16_t)(u->noi.lfsr >> 1 | fb << 14); }
    }
    u->cyc++;
    int p = 0;
    for (int i = 0; i < 2; i++)
        if (u->pl[i].len && u->pl[i].period >= 8 && sweep_target(u, i) <= 0x7FF && DUTY[u->pl[i].duty][u->pl[i].step]) p += env_out(&u->pl[i].env);
    int t = TRI[u->tri.step], nz = (u->noi.len && !(u->noi.lfsr & 1)) ? env_out(&u->noi.env) : 0;
    float po = p ? 95.88f / (8128.0f / (float)p + 100.0f) : 0;
    float td = t / 8227.0f + nz / 12241.0f;
    float to = td > 0 ? 159.79f / (1.0f / td + 100.0f) : 0;
    u->acc_sum += po + to; u->acc_n++;
    u->acc_t += 1.0;
    if (u->acc_t >= 29780.5 / (32000.0 / 60.0)) {
        u->acc_t -= 29780.5 / (32000.0 / 60.0);
        float x = (float)(u->acc_sum / u->acc_n); u->acc_sum = 0; u->acc_n = 0;
        float y = x - u->hp_x + 0.996f * u->hp_y; u->hp_x = x; u->hp_y = y;
        int v = (int)(y * 40000.0f); if (v > 32767) v = 32767; if (v < -32768) v = -32768;
        if (u->n == u->cap) { u->cap = u->cap ? u->cap * 2 : 1 << 15; u->out = realloc(u->out, sizeof *u->out * (size_t)u->cap); }
        u->out[u->n++] = (int16_t)v;
    }
}
static void apu_wr(void *user, uint16_t a, uint8_t v) {
    apu_t *u = user; int i = (a >> 2) & 1;
    switch (a) {
    case 0x4000: case 0x4004: u->pl[i].duty = v >> 6; u->pl[i].env.loop = (v >> 5) & 1; u->pl[i].env.constant = (v >> 4) & 1; u->pl[i].env.vol = v & 15; break;
    case 0x4001: case 0x4005: u->pl[i].sw_en = v >> 7; u->pl[i].sw_per = (v >> 4) & 7; u->pl[i].sw_neg = (v >> 3) & 1; u->pl[i].sw_shift = v & 7; u->pl[i].sw_reload = 1; break;
    case 0x4002: case 0x4006: u->pl[i].period = (uint16_t)((u->pl[i].period & 0x700) | v); break;
    case 0x4003: case 0x4007:
        u->pl[i].period = (uint16_t)((u->pl[i].period & 0xFF) | (v & 7) << 8);
        if (u->enabled & (1 << i)) u->pl[i].len = LEN[v >> 3];
        u->pl[i].step = 0; u->pl[i].env.start = 1; break;
    case 0x4008: u->tri.ctrl = v; u->tri.lin_reload_v = v & 0x7F; break;
    case 0x400A: u->tri.period = (uint16_t)((u->tri.period & 0x700) | v); break;
    case 0x400B: u->tri.period = (uint16_t)((u->tri.period & 0xFF) | (v & 7) << 8); if (u->enabled & 4) u->tri.len = LEN[v >> 3]; u->tri.lin_reload = 1; break;
    case 0x400C: u->noi.env.loop = (v >> 5) & 1; u->noi.env.constant = (v >> 4) & 1; u->noi.env.vol = v & 15; break;
    case 0x400E: u->noi.mode = v >> 7; u->noi.period = NOISE_P[v & 15]; break;
    case 0x400F: if (u->enabled & 8) u->noi.len = LEN[v >> 3]; u->noi.env.start = 1; break;
    case 0x4015:
        u->enabled = v & 0x1F;
        if (!(v & 1)) u->pl[0].len = 0;
        if (!(v & 2)) u->pl[1].len = 0;
        if (!(v & 4)) u->tri.len = 0;
        if (!(v & 8)) u->noi.len = 0;
        break;
    case 0x4017: u->fc_mode = v >> 7; u->fc_cycle = 0; if (u->fc_mode) { quarter(u); half(u); } break;
    }
}
/* SoundEngine (bank 2), alone from a fresh NES with one sound queued: a frame (29780.5 cycles)
   at a time until what it plays is over */
int smb1_sfx_render(const char *name, int16_t **pcm, int *frames) {
    int q = 0, bit = 0;
    if (sscanf(name, "smb1_sfx_%d_%x", &q, &bit) == 2 && q >= 1 && q <= 3) q--;
    else if (sscanf(name, "smb1_mus_%x", &bit) == 1) q = 3;
    else return 0;
    if (!smb1m_available() || !bit) return 0;
    static smb1_mario m; memset(&m, 0, sizeof m);
    uint8_t *r = m.ram;
    static const uint16_t queue[4] = {A(Square1SoundQueue), A(Square2SoundQueue), A(NoiseSoundQueue), A(EventMusicQueue)};
    static const uint16_t buffer[4] = {A(Square1SoundBuffer), A(Square2SoundBuffer), A(NoiseSoundBuffer), A(EventMusicBuffer)};
    apu_t *u = calloc(1, sizeof *u);
    u->noi.lfsr = 1; u->noi.period = NOISE_P[0];
    r[A(OperMode)] = 1;
    r[queue[q]] = (uint8_t)bit;
    int maxf = q == 3 ? 60 * 12 : 60 * 6, tail = -1;
    for (int f = 0; f < maxf; f++) {
        if (tail < 0) {
            if (run(&m, A(SoundEngine), BANK(SoundEngine), apu_wr, u)) break;
            if (f > 0 && !r[buffer[q]]) tail = 6;                /* (over: a little more for its release) */
        } else if (!tail--) break;
        uint64_t end = u->cyc + ((f & 1) ? 29781 : 29780);
        while (u->cyc < end) apu_cycle(u);
    }
    int n = u->n;
    while (n > 0 && u->out[n - 1] > -64 && u->out[n - 1] < 64) n--;   /* (trailing silence) */
    int16_t *st = malloc(sizeof *st * 2 * (size_t)(n > 0 ? n : 1));
    for (int i = 0; i < n; i++) st[2 * i] = st[2 * i + 1] = u->out[i];
    free(u->out); free(u);
    *pcm = st; *frames = n;
    rt_log("smb1", "%s: SoundEngine's, %d samples", name, n);
    return n > 0;
}

#else   /* no ROM (tools/smb1_embed.py found no ../SMB1Disassembly/SMBBase.nes): no SMB1 Mario */
int smb1m_available(void) { return 0; }
void smb1m_init(smb1_mario *m, int small, int face_left) { memset(m, 0, sizeof *m); (void)small; (void)face_left; }
uint8_t *smb1m_ram(smb1_mario *m, const char *what) { (void)what; return m->ram; }
void smb1m_timers(smb1_mario *m) { (void)m; }
void smb1m_frame(smb1_mario *m, uint8_t b, int s, int w, smb1_motion *o) { (void)m; (void)b; (void)s; (void)w; memset(o, 0, sizeof *o); }
void smb1m_collide(smb1_mario *m, int a, int b, int c, int d) { (void)m; (void)a; (void)b; (void)c; (void)d; }
void smb1m_stomp(smb1_mario *m, int h) { (void)m; (void)h; }
void smb1m_spring(smb1_mario *m, int a) { (void)m; (void)a; }
void smb1m_fire(smb1_mario *m) { (void)m; }
void smb1m_set_size(smb1_mario *m, int s, int a) { (void)m; (void)s; (void)a; }
void smb1m_fire_flash(smb1_mario *m) { (void)m; }
void smb1m_pose(smb1_mario *m, const smb1_pose *p) { (void)m; (void)p; }
void smb1m_graphics(smb1_mario *m, int pal, int star, smb1_picture *o) { (void)m; (void)pal; (void)star; memset(o, 0, sizeof *o); }
int smb1m_take_sounds(smb1_mario *m, char names[][24], int max) { (void)m; (void)names; (void)max; return 0; }
int smb1_sfx_render(const char *name, int16_t **pcm, int *frames) { (void)name; (void)pcm; (void)frames; return 0; }
#endif
