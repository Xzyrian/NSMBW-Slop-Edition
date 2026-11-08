/* gm_m_color.c - mLib's mColor::lerp: a colour between two others, channel by channel
 * (c1 * (1 - t) + c2 * t, truncated to u8). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_color.cpp) and checked against the recompiled
 * USA rev 2 code (0x8016AA70-0x8016AB80). Register-exact (RT_GM_VERIFY_REGS=1): the compiler
 * interleaved the four channels, converting each u8 through the stack (0x43300000:value as a
 * double, minus 2^52) in two shared slots (f+8 for c1's channel, f+16 for c2's) and each result
 * through its own fctiwz slot (f+24, f+32, f+40, f+48); the steps below are in its order, so the
 * frame's dead words and every temporary register end up as the PowerPC code leaves them. */
#include "gm.h"
#include "gm_nv.h"

#define K_ONE   21408                    /* (r2 - 21408: 1.0f) */
#define K_I2F   21400                    /* (r2 - 21400: (double) 2^52, u32 to float) */

#define FR(n) (ctx->f[n].d)
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }   /* fsubs / fmuls ...: both halves */
#define FB(n, v) fb(ctx, (n), (v))
#define LFD(n, a) (ctx->f[n].u = ld64(base, (a)))                                   /* lfd: ps0 */

/* lerp(self, c1, c2, t): self (GXColor, r g b a) = c1 * (1 - t) + c2 * t */
static void mColor_lerp(GM_CTX, gptr self, gptr c1, gptr c2) {
    GM_FRAME(64);
    gptr f = gm_frame_sp;
    uint32_t mag = 0x43300000u;
    ctx->r[7] = mag;
    ctx->r[0] = gm_u8(c1 + 0); gm_set_u32(f + 12, ctx->r[0]);        /* c1.r */
    ctx->r[6] = gm_u8(c2 + 0); gm_set_u32(f + 8, mag);
    ctx->r[0] = gm_u8(c1 + 1);
    LFD(4, f + 8);                                                   /* (double) c1.r + 2^52 */
    gm_set_u32(f + 16, mag);
    FB(0, ldfs(base, ctx->r[2] - K_ONE));
    gm_set_u32(f + 20, ctx->r[6]);                                   /* c2.r */
    ctx->r[6] = gm_u8(c1 + 2);
    FB(9, frsp(FR(0) - FR(1)));                                      /* s = 1 - t */
    gm_set_u32(f + 12, ctx->r[0]);                                   /* c1.g */
    LFD(8, ctx->r[2] - K_I2F);
    LFD(0, f + 8); LFD(3, f + 16);
    FB(7, frsp(FR(4) - FR(8)));                                      /* c1.r */
    ctx->r[7] = gm_u8(c2 + 1);
    FB(6, frsp(FR(0) - FR(8)));                                      /* c1.g */
    gm_set_u32(f + 20, ctx->r[7]);                                   /* c2.g */
    FB(3, frsp(FR(3) - FR(8)));                                      /* c2.r */
    ctx->r[0] = gm_u8(c2 + 2);
    LFD(2, f + 16);
    FB(7, frsp(FR(7) * FR(9)));
    gm_set_u32(f + 12, ctx->r[6]);                                   /* c1.b */
    FB(6, frsp(FR(6) * FR(9)));
    FB(5, frsp(FR(2) - FR(8)));                                      /* c2.g */
    ctx->r[4] = gm_u8(c1 + 3);
    LFD(0, f + 8);
    gm_set_u32(f + 20, ctx->r[0]);                                   /* c2.b */
    FB(2, frsp(FR(3) * FR(1)));
    FB(4, frsp(FR(0) - FR(8)));                                      /* c1.b */
    LFD(0, f + 16);
    FB(5, frsp(FR(5) * FR(1)));
    ctx->r[0] = gm_u8(c2 + 3);
    FB(7, frsp(FR(7) + FR(2)));                                      /* r */
    gm_set_u32(f + 12, ctx->r[4]);                                   /* c1.a */
    FB(3, frsp(FR(0) - FR(8)));                                      /* c2.b */
    gm_set_u32(f + 20, ctx->r[0]);                                   /* c2.a */
    ctx->f[7].u = fctiw_bits(FR(7), 1);                              /* (fctiwz: ps0) */
    LFD(2, f + 8);
    FB(4, frsp(FR(4) * FR(9)));
    LFD(0, f + 16);
    FB(2, frsp(FR(2) - FR(8)));                                      /* c1.a */
    st64(base, f + 24, ctx->f[7].u);
    FB(0, frsp(FR(0) - FR(8)));                                      /* c2.a */
    ctx->r[0] = gm_u32(f + 28);
    FB(3, frsp(FR(3) * FR(1)));
    FB(2, frsp(FR(2) * FR(9)));
    FB(0, frsp(FR(0) * FR(1)));
    gm_set_u8(self + 0, (uint8_t)ctx->r[0]);
    FB(1, frsp(FR(4) + FR(3)));                                      /* b */
    FB(5, frsp(FR(6) + FR(5)));                                      /* g */
    FB(0, frsp(FR(2) + FR(0)));                                      /* a */
    ctx->f[1].u = fctiw_bits(FR(1), 1);
    ctx->f[3].u = fctiw_bits(FR(5), 1);
    ctx->f[0].u = fctiw_bits(FR(0), 1);
    st64(base, f + 40, ctx->f[1].u);
    st64(base, f + 32, ctx->f[3].u);
    ctx->r[4] = gm_u32(f + 44);
    st64(base, f + 48, ctx->f[0].u);
    ctx->r[5] = gm_u32(f + 36);
    ctx->r[0] = gm_u32(f + 52);
    gm_set_u8(self + 1, (uint8_t)ctx->r[5]);
    gm_set_u8(self + 2, (uint8_t)ctx->r[4]);
    gm_set_u8(self + 3, (uint8_t)ctx->r[0]);
}

/* ================================================================== hle entry point - written but off: not reached by the test runs (its callers are in the RELs) */
GM_HLE(fn_8016AA70) { mColor_lerp(GM_PASS, GM_ARG(0), GM_ARG(1), GM_ARG(2)); }   /* mColor::lerp */
