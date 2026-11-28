/* snes_gen.h - what the recompiled SMW code (out/smw_bNN.c, out/smw_interp.c; tools/recomp65816.py)
 * needs: the 65816's registers and flags, the bus, the stack, and every instruction's meaning as
 * a macro. The recompiled banks and the interpreter (code in RAM: SMW builds its OAM-clearing
 * routine there) both use these, so an instruction means the same thing in both.
 *
 * Widths: R.mf = 1 when A is 8-bit (the M flag), R.xf = 1 when X / Y are 8-bit (the X flag; their
 * high bytes are then 0, as on the 65816). Width-dependent instructions test them as they run. */
#pragma once
#include <stdint.h>

typedef struct {
    uint16_t a, x, y, s, d;
    uint8_t db, pb;
    uint8_t c, z, n, v, i, dm, mf, xf, e;           /* (dm: decimal) */
} snes_cpu;
extern snes_cpu snes_R;
#define R snes_R
extern uint8_t snes_wram[0x20000];
extern const uint8_t *snes_rom; extern uint32_t snes_rom_mask;
extern uint64_t snes_cyc, snes_ev;                  /* CPU cycles; the next event */
typedef int (*snes_bank_fn)(uint16_t pc);
typedef struct { int bank; uint16_t addr; const char *name; } snes_label;
extern snes_bank_fn smw_banks[16];
extern const snes_label smw_labels[];

/* results: a plain 24-bit address (what a call expected), or one of these */
#define SNES_JUMP(pc)  (0x1000000 | ((pc) & 0xFFFFFF))   /* go on at pc */
#define SNES_RET(k)    (0x2000000 | (k))                  /* an RTS / RTL / RTI to the frame k waits for */
#define SNES_STALE(pc) (0x3000000 | ((pc) & 0xFFFFFF))
#define SNES_INTERP(pc) (0x4000000 | ((pc) & 0xFFFFFF))  /* (not recompiled here: interpret it) */

uint8_t snes_io_rd(uint32_t a);
void snes_io_wr(uint32_t a, uint8_t v);
int snes_call(uint32_t target, uint32_t expect);       /* (JSR: 2 bytes pushed) */
int snes_call_long(uint32_t target, uint32_t expect);  /* (JSL: 3) */
int snes_unwind(int v);
int snes_check(uint32_t pc);
int snes_brk(uint32_t ret, int cop);
int snes_wai(uint32_t pc);
int snes_stp(uint32_t pc);
int snes_interp(uint32_t pc);
extern int snes_trace_on; void snes_trace(uint32_t pc);   /* (testing: SNES_TRACE=pc,pc,... with SNES_INTERP_ALL) */

/* ---- the bus (LoROM: banks $00-$3F / $80-$BF: WRAM below $2000, I/O, ROM at $8000; $7E-$7F
   WRAM; $70-$7D below $8000 SRAM) */
static inline uint8_t RD8(uint32_t a) {
    uint8_t b = (uint8_t)(a >> 16); uint16_t o = (uint16_t)a;
    if ((b & 0xFE) == 0x7E) return snes_wram[a & 0x1FFFF];
    if (!(b & 0x40)) {
        if (o < 0x2000) return snes_wram[o];
        if (o >= 0x8000) return snes_rom[(((uint32_t)(b & 0x7F) << 15) | (o & 0x7FFF)) & snes_rom_mask];
    } else if (o >= 0x8000) return snes_rom[(((uint32_t)(b & 0x7F) << 15) | (o & 0x7FFF)) & snes_rom_mask];
    return snes_io_rd(a);
}
static inline void WR8(uint32_t a, uint8_t v) {
    uint8_t b = (uint8_t)(a >> 16); uint16_t o = (uint16_t)a;
    if ((b & 0xFE) == 0x7E) { snes_wram[a & 0x1FFFF] = v; return; }
    if (!(b & 0x40) && o < 0x2000) { snes_wram[o] = v; return; }
    snes_io_wr(a, v);
}
#define A24(x) ((uint32_t)(x) & 0xFFFFFF)
static inline uint16_t RD16(uint32_t a) { return (uint16_t)(RD8(a) | RD8(A24(a + 1)) << 8); }
static inline void WR16(uint32_t a, uint16_t v) { WR8(a, (uint8_t)v); WR8(A24(a + 1), (uint8_t)(v >> 8)); }
static inline uint16_t RD16_0(uint16_t a) { return (uint16_t)(RD8(a) | RD8((uint16_t)(a + 1)) << 8); }   /* (bank 0, wrapping) */
static inline uint32_t RD24_0(uint16_t a) { return RD8(a) | (uint32_t)RD8((uint16_t)(a + 1)) << 8 | (uint32_t)RD8((uint16_t)(a + 2)) << 16; }

/* ---- effective addresses (24-bit) */
#define EA_DP(o)    ((uint32_t)(uint16_t)(R.d + (o)))
#define EA_DPX(o)   ((uint32_t)(uint16_t)(R.d + (o) + R.x))
#define EA_DPY(o)   ((uint32_t)(uint16_t)(R.d + (o) + R.y))
#define EA_DPI(o)   ((uint32_t)R.db << 16 | RD16_0((uint16_t)(R.d + (o))))
#define EA_DPXI(o)  ((uint32_t)R.db << 16 | RD16_0((uint16_t)(R.d + (o) + R.x)))
#define EA_DPIY(o)  A24(((uint32_t)R.db << 16 | RD16_0((uint16_t)(R.d + (o)))) + R.y)
#define EA_DPIL(o)  RD24_0((uint16_t)(R.d + (o)))
#define EA_DPILY(o) A24(RD24_0((uint16_t)(R.d + (o))) + R.y)
#define EA_ABS(a)   ((uint32_t)R.db << 16 | (uint16_t)(a))
#define EA_ABSX(a)  A24(((uint32_t)R.db << 16 | (uint16_t)(a)) + R.x)
#define EA_ABSY(a)  A24(((uint32_t)R.db << 16 | (uint16_t)(a)) + R.y)
#define EA_LONG(l)  ((uint32_t)(l))
#define EA_LONGX(l) A24((uint32_t)(l) + R.x)
#define EA_SR(o)    ((uint32_t)(uint16_t)(R.s + (o)))
#define EA_SRIY(o)  A24(((uint32_t)R.db << 16 | RD16_0((uint16_t)(R.s + (o)))) + R.y)

/* ---- flags, stack, time */
#define CYC(n) (snes_cyc += (n))
#define NZ8(v)  (R.z = ((v) & 0xFF) == 0, R.n = ((v) >> 7) & 1)
#define NZ16(v) (R.z = ((v) & 0xFFFF) == 0, R.n = ((v) >> 15) & 1)
static inline void PUSH8(uint8_t v) { snes_wram[R.s] = v; R.s = R.e ? (uint16_t)(0x100 | (uint8_t)(R.s - 1)) : (uint16_t)(R.s - 1); }
static inline uint8_t PULL8(void) { R.s = R.e ? (uint16_t)(0x100 | (uint8_t)(R.s + 1)) : (uint16_t)(R.s + 1); return snes_wram[R.s]; }
static inline void PUSH16(uint16_t v) { PUSH8((uint8_t)(v >> 8)); PUSH8((uint8_t)v); }
static inline uint16_t PULL16(void) { uint8_t lo = PULL8(); return (uint16_t)(lo | PULL8() << 8); }
static inline uint8_t GETP(void) {
    return (uint8_t)(R.n << 7 | R.v << 6 | (R.e ? 0x20 : R.mf << 5) | (R.e ? 0x10 : R.xf << 4) | R.dm << 3 | R.i << 2 | R.z << 1 | R.c);
}
static inline void FIXW(void) { if (R.e) { R.mf = R.xf = 1; R.s = (uint16_t)(0x100 | (R.s & 0xFF)); } if (R.xf) { R.x &= 0xFF; R.y &= 0xFF; } }
static inline void SETP(uint8_t p) {
    R.n = p >> 7 & 1; R.v = p >> 6 & 1; R.mf = p >> 5 & 1; R.xf = p >> 4 & 1; R.dm = p >> 3 & 1; R.i = p >> 2 & 1; R.z = p >> 1 & 1; R.c = p & 1;
    FIXW();
}
#define OP_REP(v) SETP((uint8_t)(GETP() & ~(v)))
#define OP_SEP(v) SETP((uint8_t)(GETP() | (v)))
#define OP_XCE() do { uint8_t t_ = R.c; R.c = R.e; R.e = t_; FIXW(); } while (0)

/* ---- arithmetic */
static inline void adc8(uint8_t m) {
    unsigned a = R.a & 0xFF, r;
    if (!R.dm) { r = a + m + R.c; R.v = (~(a ^ m) & (a ^ r) & 0x80) != 0; R.c = r > 0xFF; }
    else {
        r = (a & 0x0F) + (m & 0x0F) + R.c; if (r > 9) r += 6;
        r = (a & 0xF0) + (m & 0xF0) + (r > 0x0F ? 0x10 : 0) + (r & 0x0F);
        R.v = (~(a ^ m) & (a ^ r) & 0x80) != 0; if (r > 0x9F) r += 0x60; R.c = r > 0xFF;
    }
    R.a = (uint16_t)((R.a & 0xFF00) | (r & 0xFF)); NZ8(R.a);
}
static inline void adc16(uint16_t m) {
    unsigned a = R.a, r;
    if (!R.dm) { r = a + m + R.c; R.v = (~(a ^ m) & (a ^ r) & 0x8000) != 0; R.c = r > 0xFFFF; }
    else {
        unsigned c = R.c; r = 0;
        for (int k = 0; k < 16; k += 4) {
            unsigned d = ((a >> k) & 0xF) + ((m >> k) & 0xF) + c;
            c = d > 9; if (c) d += 6;
            r |= (d & 0xF) << k;
        }
        R.v = (~(a ^ m) & (a ^ r) & 0x8000) != 0; R.c = c;
    }
    R.a = (uint16_t)r; NZ16(R.a);
}
static inline void sbc8(uint8_t m) {
    if (!R.dm) { adc8((uint8_t)~m); return; }
    unsigned a = R.a & 0xFF; int r = (int)(a & 0x0F) - (m & 0x0F) - !R.c, hi;
    int lo = r; int borrow = lo < 0; if (borrow) lo -= 6;
    hi = (int)(a >> 4) - (m >> 4) - borrow; int c = hi >= 0; if (!c) hi -= 6;
    unsigned bin = a + (uint8_t)~m + R.c; R.v = (~(a ^ (uint8_t)~m) & (a ^ bin) & 0x80) != 0;
    R.c = (uint8_t)c; R.a = (uint16_t)((R.a & 0xFF00) | (((hi & 0xF) << 4) | (lo & 0xF))); NZ8(R.a);
}
static inline void sbc16(uint16_t m) {
    if (!R.dm) { adc16((uint16_t)~m); return; }
    unsigned a = R.a, r = 0; int b = !R.c;
    for (int k = 0; k < 16; k += 4) {
        int d = (int)((a >> k) & 0xF) - (int)((m >> k) & 0xF) - b;
        b = d < 0; if (b) d += 10;
        r |= (unsigned)(d & 0xF) << k;
    }
    unsigned bin = a + (uint16_t)~m + R.c; R.v = (~(a ^ (uint16_t)~m) & (a ^ bin) & 0x8000) != 0;
    R.c = !b; R.a = (uint16_t)r; NZ16(R.a);
}

/* ---- instructions: E = an effective address, V = an immediate */
#define MW(e8, e16) do { if (R.mf) { e8; } else { e16; } } while (0)
#define XW(e8, e16) do { if (R.xf) { e8; } else { e16; } } while (0)
#define OP_LDA(E)  do { uint32_t e_ = (E); MW((R.a = (uint16_t)((R.a & 0xFF00) | RD8(e_)), NZ8(R.a)), (R.a = RD16(e_), NZ16(R.a))); } while (0)
#define OP_LDX(E)  do { uint32_t e_ = (E); XW((R.x = RD8(e_), NZ8(R.x)), (R.x = RD16(e_), NZ16(R.x))); } while (0)
#define OP_LDY(E)  do { uint32_t e_ = (E); XW((R.y = RD8(e_), NZ8(R.y)), (R.y = RD16(e_), NZ16(R.y))); } while (0)
#define OP_LDA_I8(V)  do { R.a = (uint16_t)((R.a & 0xFF00) | (uint8_t)(V)); NZ8(R.a); } while (0)
#define OP_LDA_I16(V) do { R.a = (uint16_t)(V); NZ16(R.a); } while (0)
#define OP_LDX_I8(V)  do { R.x = (uint8_t)(V); NZ8(R.x); } while (0)
#define OP_LDX_I16(V) do { R.x = (uint16_t)(V); NZ16(R.x); } while (0)
#define OP_LDY_I8(V)  do { R.y = (uint8_t)(V); NZ8(R.y); } while (0)
#define OP_LDY_I16(V) do { R.y = (uint16_t)(V); NZ16(R.y); } while (0)
#define OP_STA(E)  do { uint32_t e_ = (E); MW(WR8(e_, (uint8_t)R.a), WR16(e_, R.a)); } while (0)
#define OP_STX(E)  do { uint32_t e_ = (E); XW(WR8(e_, (uint8_t)R.x), WR16(e_, R.x)); } while (0)
#define OP_STY(E)  do { uint32_t e_ = (E); XW(WR8(e_, (uint8_t)R.y), WR16(e_, R.y)); } while (0)
#define OP_STZ(E)  do { uint32_t e_ = (E); MW(WR8(e_, 0), WR16(e_, 0)); } while (0)
#define LOGIC8(op, v)  (R.a = (uint16_t)((R.a & 0xFF00) | ((R.a op (v)) & 0xFF)), NZ8(R.a))
#define LOGIC16(op, v) (R.a = (uint16_t)(R.a op (v)), NZ16(R.a))
#define OP_AND(E) do { uint32_t e_ = (E); MW(LOGIC8(&, RD8(e_)), LOGIC16(&, RD16(e_))); } while (0)
#define OP_ORA(E) do { uint32_t e_ = (E); MW(LOGIC8(|, RD8(e_)), LOGIC16(|, RD16(e_))); } while (0)
#define OP_EOR(E) do { uint32_t e_ = (E); MW(LOGIC8(^, RD8(e_)), LOGIC16(^, RD16(e_))); } while (0)
#define OP_AND_I8(V) LOGIC8(&, (uint8_t)(V))
#define OP_ORA_I8(V) LOGIC8(|, (uint8_t)(V))
#define OP_EOR_I8(V) LOGIC8(^, (uint8_t)(V))
#define OP_AND_I16(V) LOGIC16(&, (uint16_t)(V))
#define OP_ORA_I16(V) LOGIC16(|, (uint16_t)(V))
#define OP_EOR_I16(V) LOGIC16(^, (uint16_t)(V))
#define OP_ADC(E) do { uint32_t e_ = (E); MW(adc8(RD8(e_)), adc16(RD16(e_))); } while (0)
#define OP_SBC(E) do { uint32_t e_ = (E); MW(sbc8(RD8(e_)), sbc16(RD16(e_))); } while (0)
#define OP_ADC_I8(V) adc8((uint8_t)(V))
#define OP_ADC_I16(V) adc16((uint16_t)(V))
#define OP_SBC_I8(V) sbc8((uint8_t)(V))
#define OP_SBC_I16(V) sbc16((uint16_t)(V))
#define CMP8(r, v)  do { uint8_t r_ = (uint8_t)(r), v_ = (uint8_t)(v); R.c = r_ >= v_; NZ8((uint8_t)(r_ - v_)); } while (0)
#define CMP16(r, v) do { uint16_t r_ = (uint16_t)(r), v_ = (uint16_t)(v); R.c = r_ >= v_; NZ16((uint16_t)(r_ - v_)); } while (0)
#define OP_CMP(E) do { uint32_t e_ = (E); MW(CMP8(R.a, RD8(e_)), CMP16(R.a, RD16(e_))); } while (0)
#define OP_CPX(E) do { uint32_t e_ = (E); XW(CMP8(R.x, RD8(e_)), CMP16(R.x, RD16(e_))); } while (0)
#define OP_CPY(E) do { uint32_t e_ = (E); XW(CMP8(R.y, RD8(e_)), CMP16(R.y, RD16(e_))); } while (0)
#define OP_CMP_I8(V) CMP8(R.a, V)
#define OP_CMP_I16(V) CMP16(R.a, V)
#define OP_CPX_I8(V) CMP8(R.x, V)
#define OP_CPX_I16(V) CMP16(R.x, V)
#define OP_CPY_I8(V) CMP8(R.y, V)
#define OP_CPY_I16(V) CMP16(R.y, V)
#define BIT8(val)  do { uint8_t v_ = (uint8_t)(val); R.z = (R.a & v_) == 0; R.n = v_ >> 7; R.v = (v_ >> 6) & 1; } while (0)
#define BIT16(val) do { uint16_t v_ = (uint16_t)(val); R.z = (R.a & v_) == 0; R.n = v_ >> 15; R.v = (v_ >> 14) & 1; } while (0)
#define OP_BIT(E) do { uint32_t e_ = (E); MW(BIT8(RD8(e_)), BIT16(RD16(e_))); } while (0)
#define OP_BIT_I8(V)  (R.z = ((R.a & (uint8_t)(V)) & 0xFF) == 0)
#define OP_BIT_I16(V) (R.z = (R.a & (uint16_t)(V)) == 0)
#define OP_TSB(E) do { uint32_t e_ = (E); MW((R.z = (RD8(e_) & R.a & 0xFF) == 0, WR8(e_, (uint8_t)(RD8(e_) | R.a))), \
                                              (R.z = (RD16(e_) & R.a) == 0, WR16(e_, (uint16_t)(RD16(e_) | R.a)))); } while (0)
#define OP_TRB(E) do { uint32_t e_ = (E); MW((R.z = (RD8(e_) & R.a & 0xFF) == 0, WR8(e_, (uint8_t)(RD8(e_) & ~R.a))), \
                                              (R.z = (RD16(e_) & R.a) == 0, WR16(e_, (uint16_t)(RD16(e_) & ~R.a)))); } while (0)
/* shifts and steps: f8 / f16 on a value */
static inline uint8_t  asl8(uint8_t v)   { R.c = v >> 7; v = (uint8_t)(v << 1); NZ8(v); return v; }
static inline uint16_t asl16(uint16_t v) { R.c = v >> 15; v = (uint16_t)(v << 1); NZ16(v); return v; }
static inline uint8_t  lsr8(uint8_t v)   { R.c = v & 1; v >>= 1; NZ8(v); return v; }
static inline uint16_t lsr16(uint16_t v) { R.c = v & 1; v >>= 1; NZ16(v); return v; }
static inline uint8_t  rol8(uint8_t v)   { uint8_t c = R.c; R.c = v >> 7; v = (uint8_t)(v << 1 | c); NZ8(v); return v; }
static inline uint16_t rol16(uint16_t v) { uint16_t c = R.c; R.c = v >> 15; v = (uint16_t)(v << 1 | c); NZ16(v); return v; }
static inline uint8_t  ror8(uint8_t v)   { uint8_t c = R.c; R.c = v & 1; v = (uint8_t)(v >> 1 | c << 7); NZ8(v); return v; }
static inline uint16_t ror16(uint16_t v) { uint16_t c = R.c; R.c = v & 1; v = (uint16_t)(v >> 1 | c << 15); NZ16(v); return v; }
static inline uint8_t  inc8(uint8_t v)   { v++; NZ8(v); return v; }
static inline uint16_t inc16(uint16_t v) { v++; NZ16(v); return v; }
static inline uint8_t  dec8(uint8_t v)   { v--; NZ8(v); return v; }
static inline uint16_t dec16(uint16_t v) { v--; NZ16(v); return v; }
#define RMW_A(f)  MW(R.a = (uint16_t)((R.a & 0xFF00) | f##8((uint8_t)R.a)), R.a = f##16(R.a))
#define RMW_M(f, E) do { uint32_t e_ = (E); MW(WR8(e_, f##8(RD8(e_))), WR16(e_, f##16(RD16(e_)))); } while (0)
#define OP_INX() XW((R.x = (uint8_t)(R.x + 1), NZ8(R.x)), (R.x++, NZ16(R.x)))
#define OP_INY() XW((R.y = (uint8_t)(R.y + 1), NZ8(R.y)), (R.y++, NZ16(R.y)))
#define OP_DEX() XW((R.x = (uint8_t)(R.x - 1), NZ8(R.x)), (R.x--, NZ16(R.x)))
#define OP_DEY() XW((R.y = (uint8_t)(R.y - 1), NZ8(R.y)), (R.y--, NZ16(R.y)))
/* transfers */
#define OP_TAX() XW((R.x = R.a & 0xFF, NZ8(R.x)), (R.x = R.a, NZ16(R.x)))
#define OP_TAY() XW((R.y = R.a & 0xFF, NZ8(R.y)), (R.y = R.a, NZ16(R.y)))
#define OP_TXA() MW((R.a = (uint16_t)((R.a & 0xFF00) | (R.x & 0xFF)), NZ8(R.a)), (R.a = R.x, NZ16(R.a)))
#define OP_TYA() MW((R.a = (uint16_t)((R.a & 0xFF00) | (R.y & 0xFF)), NZ8(R.a)), (R.a = R.y, NZ16(R.a)))
#define OP_TXY() XW((R.y = R.x & 0xFF, NZ8(R.y)), (R.y = R.x, NZ16(R.y)))
#define OP_TYX() XW((R.x = R.y & 0xFF, NZ8(R.x)), (R.x = R.y, NZ16(R.x)))
#define OP_TSX() XW((R.x = R.s & 0xFF, NZ8(R.x)), (R.x = R.s, NZ16(R.x)))
#define OP_TXS() (R.s = R.e ? (uint16_t)(0x100 | (R.x & 0xFF)) : R.x)
#define OP_TCD() (R.d = R.a, NZ16(R.d))
#define OP_TDC() (R.a = R.d, NZ16(R.a))
#define OP_TCS() (R.s = R.e ? (uint16_t)(0x100 | (R.a & 0xFF)) : R.a)
#define OP_TSC() (R.a = R.s, NZ16(R.a))
#define OP_XBA() (R.a = (uint16_t)(R.a >> 8 | R.a << 8), NZ8(R.a))
/* stack */
#define OP_PHA() MW(PUSH8((uint8_t)R.a), PUSH16(R.a))
#define OP_PHX() XW(PUSH8((uint8_t)R.x), PUSH16(R.x))
#define OP_PHY() XW(PUSH8((uint8_t)R.y), PUSH16(R.y))
#define OP_PLA() MW((R.a = (uint16_t)((R.a & 0xFF00) | PULL8()), NZ8(R.a)), (R.a = PULL16(), NZ16(R.a)))
#define OP_PLX() XW((R.x = PULL8(), NZ8(R.x)), (R.x = PULL16(), NZ16(R.x)))
#define OP_PLY() XW((R.y = PULL8(), NZ8(R.y)), (R.y = PULL16(), NZ16(R.y)))
#define OP_PHP() PUSH8(GETP())
#define OP_PLP() SETP(PULL8())
#define OP_PHB() PUSH8(R.db)
#define OP_PLB() (R.db = PULL8(), NZ8(R.db))
#define OP_PHD() PUSH16(R.d)
#define OP_PLD() (R.d = PULL16(), NZ16(R.d))
#define OP_PHK(k) PUSH8((uint8_t)(k))
#define OP_PEA(v) PUSH16((uint16_t)(v))
#define OP_PEI(o) PUSH16(RD16_0((uint16_t)(R.d + (o))))
#define OP_PER(v) PUSH16((uint16_t)(v))
/* block moves: the whole move at once (A+1 bytes from X to Y), as the 65816 repeats the instruction */
static inline void op_mvn(uint8_t dst, uint8_t src) {
    R.db = dst;
    do { WR8((uint32_t)dst << 16 | R.y, RD8((uint32_t)src << 16 | R.x)); R.x++; R.y++;
         if (R.xf) { R.x &= 0xFF; R.y &= 0xFF; } snes_cyc += 7; } while (R.a-- != 0);
}
static inline void op_mvp(uint8_t dst, uint8_t src) {
    R.db = dst;
    do { WR8((uint32_t)dst << 16 | R.y, RD8((uint32_t)src << 16 | R.x)); R.x--; R.y--;
         if (R.xf) { R.x &= 0xFF; R.y &= 0xFF; } snes_cyc += 7; } while (R.a-- != 0);
}
#define OP_MVN(d, s) op_mvn((uint8_t)(d), (uint8_t)(s))
#define OP_MVP(d, s) op_mvp((uint8_t)(d), (uint8_t)(s))
/* in a hook: leave the routine as its RTS / RTL would (MYBANK: the routine's bank) */
#define SNES_RTS(bank) snes_unwind((int)((uint32_t)(bank) << 16 | (uint16_t)(PULL16() + 1)))
static inline int SNES_RTL(void) { uint16_t p = PULL16(); uint8_t b = PULL8(); return snes_unwind((int)((uint32_t)b << 16 | (uint16_t)(p + 1))); }
#define CHECK(pc) do { if (snes_cyc >= snes_ev) { int r_ = snes_check(pc); if (r_) return r_; } } while (0)
