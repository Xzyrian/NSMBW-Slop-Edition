/* gm_i2.h - helpers for instance 2's register-exact natives (gm_py_mng.c, gm_mj2d_*.c,
 * gm_save_mng.c, gm_info.c; docs/DECOMP.md "Register-exact natives").
 *
 * The natives leave r0-r12, CR0, CTR and XER[CA] as the PowerPC code does, so the helpers below
 * write the registers the matching PowerPC instruction writes. A native calling another native
 * (or a recompiled function) does it as the PowerPC bl does: arguments in r3.., LR = the return
 * address, the callee's registers are the result (BL). */
#pragma once
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
/* compares into CR0 (cmpw / cmplw / cmpwi / cmplwi); returns -1 / 0 / 1 */
static inline int i2_cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int i2_cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }
#define CMPS(a, b) i2_cmps(ctx, (int32_t)(a), (int32_t)(b))
#define CMPU(a, b) i2_cmpu(ctx, (uint32_t)(a), (uint32_t)(b))
/* addic rT, rA, -1; subfe rD, rT, rA: rD = (rA != 0), CA = (rA != 0) */
static inline uint32_t i2_nonzero(ppc_context *ctx, int t, int d, uint32_t v) { ctx->r[t] = v - 1; ctx->r[d] = v != 0; ctx->xer_ca = v != 0; return v != 0; }
#define NONZERO(t, d, v) i2_nonzero(ctx, (t), (d), (v))
/* srawi rD, rS, 31 (the high word of a sign-extended value), with its CA */
static inline uint32_t i2_srawi31(ppc_context *ctx, uint32_t v) { ctx->xer_ca = (int32_t)v < 0 && (v & 0x7FFFFFFFu); return (uint32_t)((int32_t)v >> 31); }
#define SRAWI31(v) i2_srawi31(ctx, (v))
/* slw r, 1, n (n & 63 over 31: 0) */
static inline uint32_t i2_bit(uint32_t n) { n &= 63; return n > 31 ? 0 : 1u << n; }
static inline uint32_t i2_rotl(uint32_t v, uint32_t n) { n &= 31; return n ? v << n | v >> (32 - n) : v; }
/* a call as the PowerPC bl: LR = the return address */
#define BL(ra, fn) (ctx->lr = (ra), fn(ctx, base))
/* a virtual call through the actor's vtable (at +0x60): the function goes through register t
   into CTR, r3 = the object */
static inline void i2_vcall(ppc_context *ctx, uint8_t *base, uint32_t ra, gptr obj, uint32_t slot, int t) {
    ctx->r[t] = R32(R32(obj + 96) + slot); ctx->ctr = ctx->r[t]; ctx->r[3] = obj;
    ctx->lr = ra; ppc_call_indirect(ctx, base, ctx->ctr);
}
/* a framed native: the PowerPC frame (GM_FN, prologue replayed), the non-volatile registers back
   at the end, and r0 = LR = the return address as the epilogue leaves them */
typedef struct { ppc_context *c; uint32_t lr; } i2_epi_t;
static inline void i2_epi_end(i2_epi_t *e) { e->c->r[0] = e->lr; e->c->lr = e->lr; }
#define I2_FN(a) GM_FN(a); GM_NV_KEEP; i2_epi_t i2_epi_ __attribute__((cleanup(i2_epi_end))) = { ctx, ctx->lr }
