/* gm_d_stage.c - dScStage_c (the course scene) natives. Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * getLoopPosX(x): on a looping course (dScStage_c::m_loopType, r13 - 21624: 0 none, 1 once), the x
 * moved by the loop's width (r2 - 24400 ... the bg's +0x90000 - 352) until it lies within the
 * screen's left / right edges (dBg_c's 0x800789A0 / 0x80078B40, instance 2's) widened by the
 * width; once moved, a looped type-1 course stops there, and so does world 1 course 0x17 file 0
 * (the PowerPC code's special case). The most called function of the course code (it is in every
 * position check): the native skips the recompiled frame / poll overhead on the no-loop path.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_s_stage.cpp) and checked against the
 * recompiled USA rev 2 code (0x80101AA0-0x80101BBC). Register-exact (R(n)), the PowerPC loop's
 * back-edge polls kept (two back-edges, one poll each). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define LF(a) ldfs(base, (a))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

#define SDA(o) (R(13) - (o))
#define SDA_LOOP_TYPE 21624       /* dScStage_c::m_loopType */
#define SDA_STAGE     21688       /* dScStage_c::m_instance (+4620 world, +4621 course, +4622 file) */
#define SDA_BG        22704       /* dBg_c::m_bg_p */
#define F_BG_LEFT     0x800789A0u /* dBg_c: the screen's left edge (f1) */
#define F_BG_RIGHT    0x80078B40u /* dBg_c: the screen's right edge (f1) */

static void st_loop_pos_x(GM_CTX) {
    GM_FN(0x80101AA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = 0;
    R(0) = gm_u32(SDA(SDA_LOOP_TYPE));
    R(31) = gm_u32(SDA(SDA_STAGE));
    if (cmps(ctx, (int32_t)R(0), 0) == 0) goto out;
    R(3) = gm_u32(SDA(SDA_BG));
    ctx->f[29].u = ctx->f[1].u;                                              /* fmr (ps0 only) */
    FB(31, LF(R(2) - 24400));
    R(3) = R(3) + 0x90000u;
    FB(30, LF(R(3) - 352));
    goto test;
body:
    R(3) = gm_u32(SDA(SDA_BG));
    GM_CALLV(0x80101B04u, F_BG_LEFT, 0);
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[1].d);
    if (CR_BIT(ctx, 0)) FB(29, frsp(ctx->f[29].d + ctx->f[30].d));
    else {
        R(3) = gm_u32(SDA(SDA_BG));
        GM_CALLV(0x80101B1Cu, F_BG_RIGHT, 0);
        cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[1].d);
        if (CR_BIT(ctx, 1)) FB(29, frsp(ctx->f[29].d - ctx->f[30].d));
    }
    R(30) = R(30) + 1;
    if (cmps(ctx, (int32_t)R(30), 1) > 0) {
        R(0) = gm_u32(SDA(SDA_LOOP_TYPE));
        if (cmps(ctx, (int32_t)R(0), 1) == 0) goto done;
        R(0) = gm_u8(R(31) + 4620);
        if (cmpu(ctx, R(0), 1) == 0) {
            R(0) = gm_u8(R(31) + 4621);
            if (cmpu(ctx, R(0), 0x17) == 0) {
                R(0) = gm_u8(R(31) + 4622);
                if (cmps(ctx, (int32_t)R(0), 0) == 0) goto done;
            }
        }
    }
test:
    R(3) = gm_u32(SDA(SDA_BG));
    GM_CALLV(0x80101B6Cu, F_BG_LEFT, 0);
    FB(0, frsp(ctx->f[1].d - ctx->f[31].d));
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[0].d);
    if (CR_BIT(ctx, 0)) { GM_LOOP(); goto body; }
    R(3) = gm_u32(SDA(SDA_BG));
    GM_CALLV(0x80101B80u, F_BG_RIGHT, 0);
    FB(0, frsp(ctx->f[31].d + ctx->f[1].d));
    cr_fcmp(ctx, 0, ctx->f[29].d, ctx->f[0].d);
    if (CR_BIT(ctx, 1)) { GM_LOOP(); goto body; }
done:
    ctx->f[1].u = ctx->f[29].u;
out:
    R(0) = lr;
}

#define A(i) GM_ARG(i)
#ifdef GM_STAGE_VERIFY
GM_HLE_INT(getLoopPosX__10dScStage_cFf, A(0), 4)
#else
GM_HLE(getLoopPosX__10dScStage_cFf)
#endif
{ st_loop_pos_x(GM_PASS); }
