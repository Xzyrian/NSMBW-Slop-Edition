/* nes_gen.h - what the recompiled SMB3 code (out/smb3_bNN.c, tools/recomp6502.py) needs: the
 * 6502's registers and flags, memory access, stack, flag arithmetic. */
#pragma once
#include <stdint.h>

typedef struct { uint8_t a, x, y, s, c, z, n, v, i, d; } nes_cpu;
extern nes_cpu nes_R;
#define R nes_R
extern uint8_t nes_ram[0x800], nes_wram[0x2000];
extern uint8_t nes_map[4];                          /* PRG bank in $8000 / $A000 / $C000 / $E000 */
extern uint64_t nes_cyc, nes_ev;                    /* CPU cycles; the next event */
typedef int (*nes_bank_fn)(uint16_t pc);
typedef struct { int bank; uint16_t addr; const char *name; } nes_label;
extern nes_bank_fn smb3_banks[32];
extern const uint16_t smb3_bank_base[32];
extern const nes_label smb3_labels[];

#define NES_RET(pc)  (0x10000 | (pc))               /* an RTS/RTI to an address a caller waits for */
#define NES_JUMP(pc) (0x20000 | (pc))               /* go on at pc, wherever it is mapped now */

uint8_t nes_rd(uint16_t a);
void nes_wr(uint16_t a, uint8_t v);
int nes_call(uint16_t target, uint16_t expect);
int nes_unwind(int pc_or_result);   /* (an address from RTS/RTI, or a result passed on) */
int nes_check(uint16_t pc, int win, int bank);
int nes_brk(uint16_t ret);
int nes_bad_pc(uint16_t pc, int bank);

static inline uint8_t RD(uint16_t a) {
    if (a < 0x2000) return nes_ram[a & 0x7FF];
    if (a >= 0x6000 && a < 0x8000) return nes_wram[a - 0x6000];
    return nes_rd(a);
}
static inline void WR(uint16_t a, uint8_t v) {
    if (a < 0x2000) nes_ram[a & 0x7FF] = v;
    else if (a >= 0x6000 && a < 0x8000) nes_wram[a - 0x6000] = v;
    else nes_wr(a, v);
}
#define ZP(a) nes_ram[(uint8_t)(a)]
#define ZPW(a, v) (nes_ram[(uint8_t)(a)] = (v))
static inline uint16_t ZP16(uint8_t a) { return (uint16_t)(nes_ram[a] | nes_ram[(uint8_t)(a + 1)] << 8); }
#define CYC(n) (nes_cyc += (n))
#define NZ(v) (R.z = (uint8_t)(v) == 0, R.n = (uint8_t)(v) >> 7)
#define CHECK(pc) do { if (nes_cyc >= nes_ev) { int r_ = nes_check((pc), MYWIN, BANKCHK ? MYBANK : -1); if (r_) return r_; } } while (0)
static inline void PUSH(uint8_t v) { nes_ram[0x100 | R.s] = v; R.s--; }
static inline uint8_t PULL(void) { R.s++; return nes_ram[0x100 | R.s]; }
#define PUSH16(v) (PUSH((uint8_t)((v) >> 8)), PUSH((uint8_t)(v)))
static inline uint16_t PULL16(void) { uint8_t lo = PULL(); return (uint16_t)(lo | PULL() << 8); }
static inline uint8_t GETP(void) { return (uint8_t)(R.n << 7 | R.v << 6 | R.d << 3 | R.i << 2 | R.z << 1 | R.c); }
static inline void SETP(uint8_t p) { R.n = p >> 7 & 1; R.v = p >> 6 & 1; R.d = p >> 3 & 1; R.i = p >> 2 & 1; R.z = p >> 1 & 1; R.c = p & 1; }
#define ADC(m) do { uint8_t m_ = (m); unsigned s_ = R.a + m_ + R.c; R.v = (~(R.a ^ m_) & (R.a ^ s_) & 0x80) != 0; R.c = s_ > 0xFF; R.a = (uint8_t)s_; NZ(R.a); } while (0)
#define SBC(m) ADC((uint8_t)~(m))
#define CMPR(r, m) do { uint8_t m_ = (m); R.c = (r) >= m_; NZ((uint8_t)((r) - m_)); } while (0)
#define BIT(m) do { uint8_t m_ = (m); R.z = (R.a & m_) == 0; R.n = m_ >> 7; R.v = (m_ >> 6) & 1; } while (0)
static inline uint8_t ASL(uint8_t v) { R.c = v >> 7; v = (uint8_t)(v << 1); NZ(v); return v; }
static inline uint8_t LSR(uint8_t v) { R.c = v & 1; v >>= 1; NZ(v); return v; }
static inline uint8_t ROL(uint8_t v) { uint8_t c = R.c; R.c = v >> 7; v = (uint8_t)(v << 1 | c); NZ(v); return v; }
static inline uint8_t ROR(uint8_t v) { uint8_t c = R.c; R.c = v & 1; v = (uint8_t)(v >> 1 | c << 7); NZ(v); return v; }
static inline uint8_t INC(uint8_t v) { v++; NZ(v); return v; }
static inline uint8_t DEC(uint8_t v) { v--; NZ(v); return v; }
/* in a hook (port/hooks.txt): leave the routine as its RTS would */
static inline int NES_RTS(void) { return nes_unwind((uint16_t)(PULL16() + 1)); }
