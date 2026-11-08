/* gm_nv.h - keeping the non-volatile registers as the PowerPC code would (track B, instance 1).
 *
 * A PowerPC function keeps its own values in r14-r31 / f14-f31 across the calls it makes, and
 * each callee saves the ones it uses into its stack frame. Those dead stack words can end up in
 * the heap later (the game copies uninitialised locals), so a native puts the same values into
 * ctx before a nested call (NV_R(n, v), NV_F(n, v)) and GM_NV_KEEP puts the entry values back
 * when it returns, as the PowerPC epilogue does. See docs/DECOMP.md ("Exactness"). */
#pragma once
#include "gm.h"

/* The second halves (ps1) of f14-f31: the PowerPC code saves an FPR with stfd and reloads it with
   lfd, which sets ps0 only - so ps1 comes back as the function (or its callees: an lfs sets both
   halves) left it, and that leaks out to the caller. Only a prologue's psq_st (and the epilogue's
   psq_l) keeps both halves; GM_NV_KEEP puts ps1 back for just those (gm_psq_: GM_FN, gm.h).
   (Part 48: a native putting every ps1 back made a g3d CalcWorld copy f31's second half - left
   at 1.0 by an lfs several callees back - as 0 into a model's world-matrix scale for a field.) */
typedef struct { ppc_context *c; uint32_t psq; uint32_t r[18]; uint64_t f[18]; double p[18]; } gm_nv_t;
static inline gm_nv_t gm_nv_begin_(ppc_context *ctx, uint32_t psq) {
    gm_nv_t n; n.c = ctx; n.psq = psq;
    for (int i = 0; i < 18; i++) { n.r[i] = ctx->r[14 + i]; n.f[i] = ctx->f[14 + i].u; n.p[i] = ctx->ps1[14 + i]; }
    return n;
}
static inline void gm_nv_end_(gm_nv_t *n) {
    for (int i = 0; i < 18; i++) { n->c->r[14 + i] = n->r[i]; n->c->f[14 + i].u = n->f[i]; if (n->psq >> (14 + i) & 1) n->c->ps1[14 + i] = n->p[i]; }
}
#define GM_NV_KEEP gm_nv_t gm_nv_ __attribute__((cleanup(gm_nv_end_))) = gm_nv_begin_(ctx, gm_psq_)
#define NV_R(n, v) (ctx->r[n] = (uint32_t)(v))
#define NV_F(n, v) (ctx->f[n].d = (v))                       /* (fmr, arithmetic: ps0 only) */
#define NV_FL(n, v) (ctx->f[n].d = ctx->ps1[n] = (v))        /* (lfs: both halves) */

/* an hle entry returns with LR = its return address (the PowerPC epilogue reloads it), also when
   it set ctx->lr for direct native calls on the way */
typedef struct { ppc_context *c; uint32_t lr; } gm_lr_t;
static inline void gm_lr_end_(gm_lr_t *k) { k->c->lr = k->lr; }
#define GM_LR_KEEP gm_lr_t gm_lr_ __attribute__((cleanup(gm_lr_end_))) = { ctx, ctx->lr }
/* call another native directly as the PowerPC code's bl would: LR = the return address */
#define NCALL(ra, call) (ctx->lr = (ra), (call))

/* GM_CALLR(ra, fn, n, ...): GM_CALL with LR = the PowerPC return address instead of 0, so a
   callee with a frame saves the same LR word as the original (a dead stack word the game can
   copy later: part 41 found one, a heap vtable call in mHeap::adjustFrmHeap) */
#include <stdarg.h>
#include <string.h>
static inline uint32_t gm_gcall_ra_(ppc_context *ctx, uint8_t *base, uint32_t ra, uint32_t fn, int n, ...) {
    uint32_t saved[13], lr = ctx->lr, ctr = ctx->ctr;
    if (fn < 0x80000000u) return 0;                                       /* (as rt_gcall) */
    memcpy(saved, ctx->r, sizeof saved);
    va_list ap; va_start(ap, n);
    for (int i = 0; i < n && i < 8; i++) ctx->r[3 + i] = va_arg(ap, uint32_t);
    va_end(ap);
    ctx->lr = ra;
    ppc_call_indirect(ctx, base, fn);
    uint32_t ret = ctx->r[3];
    memcpy(ctx->r, saved, sizeof saved); ctx->lr = lr; ctx->ctr = ctr;
    return ret;
}
#define GM_CALLR(ra, fn, n, ...) gm_gcall_ra_(ctx, base, (ra), (fn), (n), ##__VA_ARGS__)

/* GM_CALLV(ra, fn, n, ...): a call that leaves every register as the callee returns it (no
   volatile registers put back), as the PowerPC bl does - for a native whose volatile registers
   must end up as the original's (RT_GM_VERIFY_REGS). GM_TAIL(fn, n, ...): the PowerPC tail call
   (b fn): LR stays the caller's, the callee's registers are the result. */
static inline uint32_t gm_gcallv_(ppc_context *ctx, uint8_t *base, uint32_t ra, uint32_t fn, int n, ...) {
    if (fn < 0x80000000u) return 0;
    va_list ap; va_start(ap, n);
    for (int i = 0; i < n && i < 8; i++) ctx->r[3 + i] = va_arg(ap, uint32_t);
    va_end(ap);
    ctx->lr = ra;
    ppc_call_indirect(ctx, base, fn);
    return ctx->r[3];
}
#define GM_CALLV(ra, fn, n, ...) gm_gcallv_(ctx, base, (ra), (fn), (n), ##__VA_ARGS__)
#define GM_TAIL(fn, n, ...) gm_gcallv_(ctx, base, ctx->lr, (fn), (n), ##__VA_ARGS__)
