/* smb1_cpu.c - the 6502 under Retro Mario (SMB1): see smb1_cpu.h. All the official opcodes. */
#include "smb1_cpu.h"

enum { FC = 0x01, FZ = 0x02, FI = 0x04, FD = 0x08, FB = 0x10, FU = 0x20, FV = 0x40, FN = 0x80 };

static uint8_t rd(smb1_cpu *c, uint16_t a) {
    if (a < 0x2000) return c->ram[a & 0x7FF];
    if (a >= 0xC000) return c->bankC[a - 0xC000];
    if (a >= 0x8000) return c->bank8[a - 0x8000];
    return 0;                                      /* (PPU, APU status, joypads, cartridge RAM: nothing here) */
}
static void wr(smb1_cpu *c, uint16_t a, uint8_t v) {
    if (a < 0x2000) { c->ram[a & 0x7FF] = v; return; }
    if (a >= 0x4000 && a <= 0x4017 && a != 0x4014 && a != 0x4016 && c->apu) c->apu(c->user, a, v);
}
static uint16_t rd16(smb1_cpu *c, uint16_t a) { return (uint16_t)(rd(c, a) | rd(c, (uint16_t)(a + 1)) << 8); }
static uint16_t rd16zp(smb1_cpu *c, uint8_t a) { return (uint16_t)(rd(c, a) | rd(c, (uint8_t)(a + 1)) << 8); }
static void push(smb1_cpu *c, uint8_t v) { c->ram[0x100 | c->s] = v; c->s--; }
static uint8_t pull(smb1_cpu *c) { c->s++; return c->ram[0x100 | c->s]; }
static void nz(smb1_cpu *c, uint8_t v) { c->p = (uint8_t)((c->p & ~(FZ | FN)) | (v ? 0 : FZ) | (v & FN)); }
static void adc(smb1_cpu *c, uint8_t v) {
    unsigned s = c->a + v + (c->p & FC);
    c->p = (uint8_t)((c->p & ~(FC | FV)) | (s > 0xFF ? FC : 0) | ((~(c->a ^ v) & (c->a ^ s) & 0x80) ? FV : 0));
    c->a = (uint8_t)s; nz(c, c->a);
}
static void sbc(smb1_cpu *c, uint8_t v) { adc(c, (uint8_t)~v); }
static void cmp(smb1_cpu *c, uint8_t r, uint8_t v) { c->p = (uint8_t)((c->p & ~FC) | (r >= v ? FC : 0)); nz(c, (uint8_t)(r - v)); }

int smb1_cpu_call(smb1_cpu *c, uint16_t addr, int max_steps) {
    /* a JSR from a sentinel return address ($0000 - 1): the routine's final RTS lands there */
    uint8_t s0 = c->s;
    push(c, 0xFF); push(c, 0xFF);
    c->pc = addr; c->error = 0;
    for (int n = 0; n < max_steps; n++) {
        if (c->pc == 0x0000 && c->s == s0) return 0;   /* (returned) */
        uint8_t op = rd(c, c->pc++);
        uint16_t ea = 0; uint8_t v;
        /* addressing */
        #define IMM   (ea = c->pc++)
        #define ZP    (ea = rd(c, c->pc++))
        #define ZPX   (ea = (uint8_t)(rd(c, c->pc++) + c->x))
        #define ZPY   (ea = (uint8_t)(rd(c, c->pc++) + c->y))
        #define ABS   (ea = rd16(c, c->pc), c->pc += 2)
        #define ABX   (ea = (uint16_t)(rd16(c, c->pc) + c->x), c->pc += 2)
        #define ABY   (ea = (uint16_t)(rd16(c, c->pc) + c->y), c->pc += 2)
        #define IZX   (ea = rd16zp(c, (uint8_t)(rd(c, c->pc++) + c->x)))
        #define IZY   (ea = (uint16_t)(rd16zp(c, rd(c, c->pc++)) + c->y))
        #define BR(cond) { int8_t d = (int8_t)rd(c, c->pc++); if (cond) c->pc = (uint16_t)(c->pc + d); c->cycles += 3; break; }
        #define LD(r, m) { m; r = rd(c, ea); nz(c, r); c->cycles += 3; break; }
        #define ST(r, m) { m; wr(c, ea, r); c->cycles += 3; break; }
        #define OPA(f, m) { m; f(c, rd(c, ea)); c->cycles += 3; break; }
        #define LOG(o, m) { m; c->a = (uint8_t)(c->a o rd(c, ea)); nz(c, c->a); c->cycles += 3; break; }
        #define RMW(m, body) { m; v = rd(c, ea); body; wr(c, ea, v); c->cycles += 5; break; }
        #define ASLv { c->p = (uint8_t)((c->p & ~FC) | (v >> 7)); v = (uint8_t)(v << 1); nz(c, v); }
        #define LSRv { c->p = (uint8_t)((c->p & ~FC) | (v & 1)); v >>= 1; nz(c, v); }
        #define ROLv { uint8_t cin = c->p & FC; c->p = (uint8_t)((c->p & ~FC) | (v >> 7)); v = (uint8_t)(v << 1 | cin); nz(c, v); }
        #define RORv { uint8_t cin = (uint8_t)((c->p & FC) << 7); c->p = (uint8_t)((c->p & ~FC) | (v & 1)); v = (uint8_t)(v >> 1 | cin); nz(c, v); }
        #define INCv { v++; nz(c, v); }
        #define DECv { v--; nz(c, v); }
        switch (op) {
        /* loads / stores */
        case 0xA9: LD(c->a, IMM) case 0xA5: LD(c->a, ZP) case 0xB5: LD(c->a, ZPX) case 0xAD: LD(c->a, ABS)
        case 0xBD: LD(c->a, ABX) case 0xB9: LD(c->a, ABY) case 0xA1: LD(c->a, IZX) case 0xB1: LD(c->a, IZY)
        case 0xA2: LD(c->x, IMM) case 0xA6: LD(c->x, ZP) case 0xB6: LD(c->x, ZPY) case 0xAE: LD(c->x, ABS) case 0xBE: LD(c->x, ABY)
        case 0xA0: LD(c->y, IMM) case 0xA4: LD(c->y, ZP) case 0xB4: LD(c->y, ZPX) case 0xAC: LD(c->y, ABS) case 0xBC: LD(c->y, ABX)
        case 0x85: ST(c->a, ZP) case 0x95: ST(c->a, ZPX) case 0x8D: ST(c->a, ABS) case 0x9D: ST(c->a, ABX)
        case 0x99: ST(c->a, ABY) case 0x81: ST(c->a, IZX) case 0x91: ST(c->a, IZY)
        case 0x86: ST(c->x, ZP) case 0x96: ST(c->x, ZPY) case 0x8E: ST(c->x, ABS)
        case 0x84: ST(c->y, ZP) case 0x94: ST(c->y, ZPX) case 0x8C: ST(c->y, ABS)
        /* transfers */
        case 0xAA: c->x = c->a; nz(c, c->x); c->cycles += 2; break;
        case 0xA8: c->y = c->a; nz(c, c->y); c->cycles += 2; break;
        case 0x8A: c->a = c->x; nz(c, c->a); c->cycles += 2; break;
        case 0x98: c->a = c->y; nz(c, c->a); c->cycles += 2; break;
        case 0xBA: c->x = c->s; nz(c, c->x); c->cycles += 2; break;
        case 0x9A: c->s = c->x; c->cycles += 2; break;
        /* stack */
        case 0x48: push(c, c->a); c->cycles += 3; break;
        case 0x68: c->a = pull(c); nz(c, c->a); c->cycles += 4; break;
        case 0x08: push(c, (uint8_t)(c->p | FB | FU)); c->cycles += 3; break;
        case 0x28: c->p = (uint8_t)((pull(c) & ~FB) | FU); c->cycles += 4; break;
        /* arithmetic, logic */
        case 0x69: OPA(adc, IMM) case 0x65: OPA(adc, ZP) case 0x75: OPA(adc, ZPX) case 0x6D: OPA(adc, ABS)
        case 0x7D: OPA(adc, ABX) case 0x79: OPA(adc, ABY) case 0x61: OPA(adc, IZX) case 0x71: OPA(adc, IZY)
        case 0xE9: OPA(sbc, IMM) case 0xE5: OPA(sbc, ZP) case 0xF5: OPA(sbc, ZPX) case 0xED: OPA(sbc, ABS)
        case 0xFD: OPA(sbc, ABX) case 0xF9: OPA(sbc, ABY) case 0xE1: OPA(sbc, IZX) case 0xF1: OPA(sbc, IZY)
        case 0x29: LOG(&, IMM) case 0x25: LOG(&, ZP) case 0x35: LOG(&, ZPX) case 0x2D: LOG(&, ABS)
        case 0x3D: LOG(&, ABX) case 0x39: LOG(&, ABY) case 0x21: LOG(&, IZX) case 0x31: LOG(&, IZY)
        case 0x09: LOG(|, IMM) case 0x05: LOG(|, ZP) case 0x15: LOG(|, ZPX) case 0x0D: LOG(|, ABS)
        case 0x1D: LOG(|, ABX) case 0x19: LOG(|, ABY) case 0x01: LOG(|, IZX) case 0x11: LOG(|, IZY)
        case 0x49: LOG(^, IMM) case 0x45: LOG(^, ZP) case 0x55: LOG(^, ZPX) case 0x4D: LOG(^, ABS)
        case 0x5D: LOG(^, ABX) case 0x59: LOG(^, ABY) case 0x41: LOG(^, IZX) case 0x51: LOG(^, IZY)
        case 0xC9: IMM; cmp(c, c->a, rd(c, ea)); c->cycles += 2; break;
        case 0xC5: ZP; cmp(c, c->a, rd(c, ea)); c->cycles += 3; break;
        case 0xD5: ZPX; cmp(c, c->a, rd(c, ea)); c->cycles += 4; break;
        case 0xCD: ABS; cmp(c, c->a, rd(c, ea)); c->cycles += 4; break;
        case 0xDD: ABX; cmp(c, c->a, rd(c, ea)); c->cycles += 4; break;
        case 0xD9: ABY; cmp(c, c->a, rd(c, ea)); c->cycles += 4; break;
        case 0xC1: IZX; cmp(c, c->a, rd(c, ea)); c->cycles += 6; break;
        case 0xD1: IZY; cmp(c, c->a, rd(c, ea)); c->cycles += 5; break;
        case 0xE0: IMM; cmp(c, c->x, rd(c, ea)); c->cycles += 2; break;
        case 0xE4: ZP; cmp(c, c->x, rd(c, ea)); c->cycles += 3; break;
        case 0xEC: ABS; cmp(c, c->x, rd(c, ea)); c->cycles += 4; break;
        case 0xC0: IMM; cmp(c, c->y, rd(c, ea)); c->cycles += 2; break;
        case 0xC4: ZP; cmp(c, c->y, rd(c, ea)); c->cycles += 3; break;
        case 0xCC: ABS; cmp(c, c->y, rd(c, ea)); c->cycles += 4; break;
        case 0x24: ZP; v = rd(c, ea); c->p = (uint8_t)((c->p & ~(FZ | FV | FN)) | ((c->a & v) ? 0 : FZ) | (v & (FV | FN))); c->cycles += 3; break;
        case 0x2C: ABS; v = rd(c, ea); c->p = (uint8_t)((c->p & ~(FZ | FV | FN)) | ((c->a & v) ? 0 : FZ) | (v & (FV | FN))); c->cycles += 4; break;
        /* increments / shifts */
        case 0xE6: RMW(ZP, INCv) case 0xF6: RMW(ZPX, INCv) case 0xEE: RMW(ABS, INCv) case 0xFE: RMW(ABX, INCv)
        case 0xC6: RMW(ZP, DECv) case 0xD6: RMW(ZPX, DECv) case 0xCE: RMW(ABS, DECv) case 0xDE: RMW(ABX, DECv)
        case 0xE8: c->x++; nz(c, c->x); c->cycles += 2; break;
        case 0xCA: c->x--; nz(c, c->x); c->cycles += 2; break;
        case 0xC8: c->y++; nz(c, c->y); c->cycles += 2; break;
        case 0x88: c->y--; nz(c, c->y); c->cycles += 2; break;
        case 0x0A: v = c->a; ASLv; c->a = v; c->cycles += 2; break;
        case 0x4A: v = c->a; LSRv; c->a = v; c->cycles += 2; break;
        case 0x2A: v = c->a; ROLv; c->a = v; c->cycles += 2; break;
        case 0x6A: v = c->a; RORv; c->a = v; c->cycles += 2; break;
        case 0x06: RMW(ZP, ASLv) case 0x16: RMW(ZPX, ASLv) case 0x0E: RMW(ABS, ASLv) case 0x1E: RMW(ABX, ASLv)
        case 0x46: RMW(ZP, LSRv) case 0x56: RMW(ZPX, LSRv) case 0x4E: RMW(ABS, LSRv) case 0x5E: RMW(ABX, LSRv)
        case 0x26: RMW(ZP, ROLv) case 0x36: RMW(ZPX, ROLv) case 0x2E: RMW(ABS, ROLv) case 0x3E: RMW(ABX, ROLv)
        case 0x66: RMW(ZP, RORv) case 0x76: RMW(ZPX, RORv) case 0x6E: RMW(ABS, RORv) case 0x7E: RMW(ABX, RORv)
        /* flow */
        case 0x4C: c->pc = rd16(c, c->pc); c->cycles += 3; break;
        case 0x6C: { uint16_t p = rd16(c, c->pc); c->pc = (uint16_t)(rd(c, p) | rd(c, (uint16_t)((p & 0xFF00) | ((p + 1) & 0xFF))) << 8); c->cycles += 5; break; }   /* (the page-wrap bug) */
        case 0x20: { uint16_t t = rd16(c, c->pc); uint16_t r = (uint16_t)(c->pc + 1); push(c, (uint8_t)(r >> 8)); push(c, (uint8_t)r); c->pc = t; c->cycles += 6; break; }
        case 0x60: { uint16_t r = pull(c); r |= (uint16_t)(pull(c) << 8); c->pc = (uint16_t)(r + 1); c->cycles += 6; break; }
        case 0x40: { c->p = (uint8_t)((pull(c) & ~FB) | FU); uint16_t r = pull(c); r |= (uint16_t)(pull(c) << 8); c->pc = r; c->cycles += 6; break; }
        case 0x10: BR(!(c->p & FN)) case 0x30: BR(c->p & FN) case 0x50: BR(!(c->p & FV)) case 0x70: BR(c->p & FV)
        case 0x90: BR(!(c->p & FC)) case 0xB0: BR(c->p & FC) case 0xD0: BR(!(c->p & FZ)) case 0xF0: BR(c->p & FZ)
        /* flags */
        case 0x18: c->p &= (uint8_t)~FC; c->cycles += 2; break;
        case 0x38: c->p |= FC; c->cycles += 2; break;
        case 0x58: c->p &= (uint8_t)~FI; c->cycles += 2; break;
        case 0x78: c->p |= FI; c->cycles += 2; break;
        case 0xB8: c->p &= (uint8_t)~FV; c->cycles += 2; break;
        case 0xD8: c->p &= (uint8_t)~FD; c->cycles += 2; break;
        case 0xF8: c->p |= FD; c->cycles += 2; break;
        case 0xEA: c->cycles += 2; break;
        default: c->error = op ? op : 0x100; c->pc--; return -1;      /* (BRK or an unofficial opcode: not in SMB1's player code) */
        }
    }
    c->error = 0x200;                                                    /* (ran out of steps) */
    return -1;
}
