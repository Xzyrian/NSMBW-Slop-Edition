/* gm_nw4r_g3d.c - nw4r g3d / math leaves that the scene code calls hundreds of thousands of times
 * a run: ResMdl's dictionary lookups (GetResNode by index / id, GetResMat by index / id, the
 * shape lookup, GetResNodeNumEntries), the material / texture-SRT flag checks and getters, a
 * 3x4 matrix copy through the paired-single loads, math::SinFIdx (the sine table with its
 * quantised index), and a setter; then the next of the call profile (batches 2-7): the
 * texture / BP / fog / z-compare state writes, display list calls, Camera::GetCameraMtx,
 * CosFIdx, SetScnObjOption, the effect lists' vfunc dispatches, ChangeColor/AlphaUpdate ... -
 * batch 8 the MSL strcmp / memcmp, mTexture_c, EGG::Vector3f::normalise, the 2D GX state
 * setters; batches 9-10 the MSL libm sin / cos / tan (op for op), strncmp, the camera's
 * projection matrices, ScnObj::SetMtx, lyt pane positions - 130 on (all reached by the tests:
 * first-call logs), EGG::Math<float>::sqrt written but off.
 * Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against the OGWS decomp (ext/ogws: src/nw4r/g3d/res, src/nw4r/math - the same
 * nw4r generation) and checked against the recompiled USA rev 2 code. Register-exact (R(n));
 * SinFIdx keeps the PowerPC code's quantised psq round trip through its stack frame (GQR3) and
 * its back-edge poll.
 *
 * A ResDic (from a ResMdl's data at +20 nodes / +48 materials / +56 shapes): +4 the count,
 * entries of 16 bytes from +16, an entry's +4 its offset from the dictionary. */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d
#define LF(a) ldfs(base, (a))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

/* the ResMdl's dictionary at +off, then its entry r4 (index: the root entry is 0) */
static void dic_entry(GM_CTX, uint32_t off) {
    R(3) = gm_u32(R(3));
    R(0) = gm_u32(R(3) + off);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(0) = 0; else R(0) = R(3) + R(0);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) { R(3) = 0; return; }
    R(3) = R(4) + 1;
    R(3) = R(3) << 4;
    R(3) = R(0) + R(3);
    R(3) = gm_u32(R(3) + 20);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; return; }
    R(3) = R(0) + R(3);
}
/* a flag word's bit r4 (0..7) as a bool */
static void flag_bit(GM_CTX) {
    R(5) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(5), 0) == 0 || cmpu(ctx, R(4), 7) > 0) { R(3) = 0; return; }
    R(3) = 1;
    R(0) = gm_u32(R(5));
    { uint32_t s_ = R(4) & 63; R(3) = s_ > 31 ? 0 : R(3) << s_; }
    R(3) = R(3) & R(0);
    R(0) = (uint32_t)-(int32_t)R(3); R(0) = R(0) | R(3);
    R(3) = R(0) >> 31;
}
/* nw4r::math::SinFIdx(fidx): |fidx| folded below 65536 / 256, the table entry and its slope */
static void sin_fidx(GM_CTX) {
    ctx->f[3].u = ctx->f[1].u & ~0x8000000000000000ull;                      /* fabs (ps0 only) */
    GM_FRAME(16); gptr f = gm_frame_sp;
    FB(0, LF(R(2) - 19424));                                                 /* 256.0f */
    goto test;
body:
    FB(3, frsp(F(3) - F(0)));
test:
    cr_fcmp(ctx, 0, F(3), F(0));
    if (CR_BIT(ctx, 1)) { GM_LOOP(); goto body; }
    R(3) = f + 12;
    psq_st(ctx, base, 3, R(3), 1, 3);                                        /* (the index as a u16, GQR3) */
    R(3) = f + 8;
    R(0) = gm_u16(f + 12);
    gm_set_u16(f + 8, (uint16_t)R(0));
    psq_l(ctx, base, 2, R(3), 1, 3);
    R(4) = 0x802F0000u;
    R(0) = (R(0) << 4) & 0xFF0u;
    FB(0, LF(R(2) - 19420));                                                 /* 0.0f */
    R(4) = R(4) + 29856;                                                     /* the sine table */
    FB(4, frsp(F(3) - F(2)));
    R(3) = R(4) + R(0);
    cr_fcmp(ctx, 0, F(1), F(0));
    FB(3, LF(R(3) + 8));
    FB(2, LF(R(4) + R(0)));
    FB(0, frsp(F(4) * F(3)));
    FB(1, frsp(F(2) + F(0)));
    if (CR_BIT(ctx, 0)) ctx->f[1].u ^= 0x8000000000000000ull;               /* fneg (ps0 only) */
}

/* (an object's callback dispatch for timing r4: the enable mask +204 bit r4 - 1 for r4 < 9; 5 the
   draw callback through r6's vtable, 6 / 7 the +236 callback after a G3DState::Invalidate,
   else the default) */
static void obj_callback(GM_CTX) {
    GM_FN(0x8025F0C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmpu(ctx, R(4), 9);
    R(31) = R(3);
    if (c < 0) {
        R(7) = R(4) - 1; R(8) = 1;
        R(0) = gm_u32(R(3) + 204);
        { uint32_t s_ = R(7) & 63; R(7) = s_ > 31 ? 0 : R(8) << s_; }
        R(0) = R(7) & R(0);
        R(0) = cmps(ctx, (int32_t)R(0), 0) != 0 ? 1 : 0;
    } else R(0) = 0;
    if (cmps(ctx, (int32_t)R(0), 0) != 0) goto out;
    if (cmpu(ctx, R(4), 5) == 0) {
        R(12) = gm_u32(R(6)); R(3) = R(6);
        R(0) = gm_u32(R(31) + 232); R(4) = R(31);
        R(12) = gm_u32(R(12) + 12);
        R(6) = (R(0) >> 1) & 1; R(5) = R(0) & 1;
        ctx->ctr = R(12);
        GM_CALLV(0x8025F148u, R(12), 0);
    } else if (cmpu(ctx, R(4), 6) == 0 || cmpu(ctx, R(4), 7) == 0) {
        int six = R(4) == 6;
        R(0) = gm_u32(R(3) + 236);
        if (cmps(ctx, (int32_t)R(0), 0) != 0) {
            R(3) = 2047;
            GM_CALLV(six ? 0x8025F160u : 0x8025F18Cu, 0x8024D5E0u, 0);       /* G3DState::Invalidate */
            R(12) = gm_u32(R(31) + 236); R(3) = R(31); R(4) = six ? 1 : 0;
            ctx->ctr = R(12);
            GM_CALLV(six ? 0x8025F174u : 0x8025F1A0u, R(12), 0);
        }
    } else {
        R(3) = R(31);
        GM_CALLV(0x8025F1ACu, 0x80257A40u, 0);
    }
out:
    R(0) = lr;
}
/* (the texture coordinate table entry for texmap r4 by its format: two 16-byte rows per map) */
static void texcoord_entry(GM_CTX) {
    GM_FN(0x8024A2D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(4); R(29) = R(3);
    GM_CALLV(0x8024A2F4u, 0x801C7220u, 0);                                   /* (its format) */
    R(31) = R(3); R(3) = R(29);
    GM_CALLV(0x8024A300u, 0x801C7250u, 0);
    R(0) = R(31) - 8;
    uint32_t lo, hi;
    if (cmpu(ctx, R(0), 2) <= 0) { lo = 256; hi = 384; }
    else if (cmps(ctx, (int32_t)R(31), 6) == 0) { lo = 512; hi = 640; }
    else { lo = 0; hi = 128; }
    R(0) = R(3) & 0xFF;
    int z = cmps(ctx, (int32_t)R(0), 0) == 0;
    R(3) = 0x803E0000u;
    R(0) = R(30) << 4;
    R(3) = R(3) - 5376;
    if (lo) { R(4) = R(3) + R(0); R(3) = R(4) + (z ? lo : hi); }
    else { R(3) = R(3) + R(0); if (!z) R(3) = R(3) + 128; }
    R(0) = lr;
}
/* (two BP registers 0x30 + 2 * r3 / 0x31 + 2 * r3 straight into the write-gather pipe: the
   texture coordinate scales) */
static void bp_texcoord_scale(GM_CTX) {
    R(10) = 0xCC010000u; R(11) = 97;
    st8(base, R(10) - 32768, R(11));
    R(12) = R(3) << 1;
    R(3) = 0xFE040000u;
    R(4) = R(4) - 1;
    R(0) = R(3) - 1;
    st32(base, R(10) - 32768, R(0));                                         /* the BP mask */
    R(3) = (R(5) << 16) & 0xFF0000u;
    R(5) = (R(6) << 17) & 0x1FE0000u;
    R(4) = R(4) | R(3);
    R(0) = R(12) + 48;
    R(3) = R(0) << 24;
    st8(base, R(10) - 32768, R(11));
    R(4) = R(5) | R(4);
    R(0) = R(12) + 49;
    R(3) = R(4) | R(3);
    st32(base, R(10) - 32768, R(3));
    R(4) = R(7) - 1;
    R(5) = (R(9) << 17) & 0x1FE0000u;
    R(3) = (R(8) << 16) & 0xFF0000u;
    st8(base, R(10) - 32768, R(11));
    R(3) = R(4) | R(3);
    R(0) = R(0) << 24;
    R(3) = R(5) | R(3);
    R(0) = R(3) | R(0);
    st32(base, R(10) - 32768, R(0));
}
/* (a 3x3 texture matrix loaded as 3x4 with a zero translation column: GXLoadTexMtxImm(id, 3x4)) */
static void load_texmtx33(GM_CTX) {
    GM_FN(0x8024A150); GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    FB(6, LF(R(2) - 18956));                                                 /* 0.0f */
    R(5) = 0;
    for (int i = 0; i < 9; i++) FB(9 - i - (i >= 3), LF(R(3) + 4 * i));
    R(3) = f + 8;
    stfs(base, f + 8, F(9)); stfs(base, f + 12, F(8)); stfs(base, f + 16, F(7)); stfs(base, f + 20, F(6));
    stfs(base, f + 24, F(5)); stfs(base, f + 28, F(4)); stfs(base, f + 32, F(3)); stfs(base, f + 36, F(6));
    stfs(base, f + 40, F(2)); stfs(base, f + 44, F(1)); stfs(base, f + 48, F(0)); stfs(base, f + 52, F(6));
    GM_CALLV(0x8024A1C0u, 0x801C9A80u, 0);                                   /* GXLoadTexMtxImm */
    R(0) = lr;
}

/* (a ResAnmChr result for node r5: none for a flagged node, the precomputed one (+48, 76 bytes
   each), else GetAnmResult at the current frame) */
static void anm_chr_result(GM_CTX) {
    GM_FN(0x802492E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(0) = R(5) << 1;
    R(31) = R(4);
    R(6) = gm_u32(R(3) + 20);
    R(5) = gm_u16(R(6) + R(0));
    R(0) = R(5) & 0xC000;
    if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(0) = 0; gm_set_u32(R(4), 0); R(3) = R(31); goto out; }
    R(6) = gm_u32(R(3) + 48);
    if (cmps(ctx, (int32_t)R(6), 0) != 0) { R(0) = (uint32_t)((int32_t)R(5) * 76); R(3) = R(6) + R(0); goto out; }
    FB(1, LF(R(3) + 24));
    R(3) = R(3) + 44;
    GM_CALLV(0x8024933Cu, 0x80241690u, 0);                                   /* ResAnmChr::GetAnmResult */
    R(3) = R(31);
out:
    R(0) = lr;
}
/* (the position / normal / colour arrays: remembered, and GXSetArray for each given) */
static void set_vtx_arrays(GM_CTX) {
    GM_FN(0x8024D0B0); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(7) = 0x803E0000u;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(6) = R(7) - 3728;
    gm_set_u32(R(7) - 3728, R(3)); gm_set_u32(R(6) + 4, R(4)); gm_set_u32(R(6) + 8, R(5));
    if (c != 0) { R(4) = R(3); R(3) = 21; R(5) = 48; GM_CALLV(0x8024D0E8u, 0x801C4780u, 0); }
    static const uint32_t ra[2] = { 0x8024D108u, 0x8024D128u };
    static const uint8_t attr[2] = { 22, 23 }, stride[2] = { 36, 48 };
    for (int i = 0; i < 2; i++) {
        R(3) = 0x803E0000u; R(3) = R(3) - 3728;
        R(4) = gm_u32(R(3) + 4 + 4 * i);
        if (cmps(ctx, (int32_t)R(4), 0) != 0) { R(3) = attr[i]; R(5) = stride[i]; GM_CALLV(ra[i], 0x801C4780u, 0); }
    }
    R(0) = lr;
}
/* (a display list (r: +4 size, +8 offset from r) - called, or its call put straight into the FIFO
   when r4 (or r5) says so; skip the first 32 bytes when asked) */
static inline uint32_t dl_ptr(GM_CTX, uint32_t d) {
    R(0) = gm_u32(d + 8);
    return cmps(ctx, (int32_t)R(0), 0) == 0 ? 0 : d + R(0);
}
static void dl_fifo(GM_CTX, uint32_t p, uint32_t n) {
    st8(base, 0xCC008000u, 64);
    st32(base, 0xCC008000u, p); st32(base, 0xCC008000u, n);
}

/* paired-single ops as the recompiled code does them */
static inline void ps_mul(GM_CTX, int d, int a, int c) {
    double x = frsp(ctx->f[a].d * ctx->f[c].d), y = frsp(ctx->ps1[a] * ctx->ps1[c]); ctx->f[d].d = x; ctx->ps1[d] = y;
}
static inline void ps_madd(GM_CTX, int d, int a, int c, int b) {
    double x = frsp(ctx->f[a].d * ctx->f[c].d + ctx->f[b].d), y = frsp(ctx->ps1[a] * ctx->ps1[c] + ctx->ps1[b]);
    ctx->f[d].d = x; ctx->ps1[d] = y;
}
static inline void ps_sum0(GM_CTX, int d, int a, int c) {                   /* d = (a0 + a1, c1) */
    double x = frsp(ctx->f[a].d + ctx->ps1[a]), y = frsp(ctx->ps1[c]); ctx->f[d].d = x; ctx->ps1[d] = y;
}
/* (dst = src with its translation column replaced by src x (v, 1): a local-space translate) */
static void mtx_trans_local(GM_CTX) {
    psq_l(ctx, base, 2, R(4), 0, 0);
    psq_l(ctx, base, 0, R(5), 0, 0);
    psq_l(ctx, base, 3, R(4) + 8, 0, 0);
    psq_l(ctx, base, 4, R(4) + 16, 0, 0);
    ps_mul(GM_PASS, 8, 2, 0);
    psq_l(ctx, base, 1, R(5) + 8, 1, 0);
    psq_l(ctx, base, 5, R(4) + 24, 0, 0);
    ps_madd(GM_PASS, 9, 3, 1, 8);
    psq_l(ctx, base, 6, R(4) + 32, 0, 0);
    ps_mul(GM_PASS, 8, 4, 0);
    psq_l(ctx, base, 7, R(4) + 40, 0, 0);
    psq_st(ctx, base, 3, R(3) + 8, 0, 0);
    ps_sum0(GM_PASS, 10, 9, 10);
    ps_madd(GM_PASS, 9, 5, 1, 8);
    psq_st(ctx, base, 5, R(3) + 24, 0, 0);
    ps_mul(GM_PASS, 8, 6, 0);
    psq_st(ctx, base, 10, R(3) + 12, 1, 0);
    ps_sum0(GM_PASS, 10, 9, 10);
    ps_madd(GM_PASS, 9, 7, 1, 8);
    psq_st(ctx, base, 7, R(3) + 40, 0, 0);
    psq_st(ctx, base, 10, R(3) + 28, 1, 0);
    ps_sum0(GM_PASS, 10, 9, 10);
    psq_st(ctx, base, 2, R(3), 0, 0);
    psq_st(ctx, base, 4, R(3) + 16, 0, 0);
    psq_st(ctx, base, 6, R(3) + 32, 0, 0);
    psq_st(ctx, base, 10, R(3) + 44, 1, 0);
}
/* (an animation's result: the node's anim entry, its type's function from the table at
   0x8002F... (r6 + type * 4), called with the frame) */
static void anm_chr_get_result(GM_CTX) {
    R(6) = gm_u32(R(3));
    R(0) = gm_u32(R(6) + 16);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(0) = 0; else R(0) = R(6) + R(0);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(5) = 0;
    else {
        R(5) = R(5) + 1; R(5) = R(5) << 4; R(5) = R(0) + R(5);
        R(5) = gm_u32(R(5) + 20);
        if (cmps(ctx, (int32_t)R(5), 0) == 0) R(5) = 0; else R(5) = R(0) + R(5);
    }
    R(8) = gm_u32(R(5) + 4);
    R(6) = 0x80300000u;
    R(7) = gm_u32(R(3));
    R(6) = R(6) - 31472;
    R(0) = (R(8) >> 20) & 0x1C;
    R(3) = R(8) & 0x1FFF;
    R(12) = gm_u32(R(6) + R(0));
    gm_set_u32(R(4), R(3));
    R(3) = R(4);
    R(4) = R(7) + 32;
    ctx->ctr = R(12);
    GM_TAIL(R(12), 0);
}
/* (a matrix cache slot r4 (< 32): skip when it already holds the same 48 bytes, else copy in) */
static void mtx_cache_set(GM_CTX) {
    GM_FN(0x8024D220); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(3) = gm_u32(R(3));
    int c = cmpu(ctx, R(4), 0x1F);
    R(30) = R(4);
    gm_set_u32(f + 8, R(3));
    if (c > 0) goto out;
    if (cmps(ctx, (int32_t)R(3), 0) == 0) goto out;
    R(31) = 0x803E0000u;
    R(6) = R(31) - 1664;
    R(0) = gm_u32(R(6) + 4);
    if (cmps(ctx, (int32_t)R(0), (int32_t)R(4)) == 0) {
        R(0) = (uint32_t)((int32_t)R(4) * 48);
        R(5) = 48;
        R(4) = R(6) + R(0); R(4) = R(4) + 8;
        GM_CALLV(0x8024D278u, 0x802DF098u, 0);                               /* memcmp */
        if (cmps(ctx, (int32_t)R(3), 0) == 0) goto out;
        R(0) = 0;
        gm_set_u32(R(31) - 1664, 0);
    }
    R(0) = (uint32_t)((int32_t)R(30) * 48);
    R(4) = 0x803E0000u;
    R(3) = f + 8;
    R(4) = R(4) - 1664; R(4) = R(4) + R(0); R(4) = R(4) + 8;
    GM_CALLV(0x8024D2A4u, 0x8025F330u, 0);
out:
    R(0) = lr;
}

/* (a display list of a fixed size n: called, or its call put straight into the FIFO) */
static void dl_fixed(GM_CTX, uint32_t n) {
    int c = cmps(ctx, (int32_t)R(4), 0);
    R(3) = gm_u32(R(3));
    if (c != 0) { R(4) = n; GM_TAIL(0x801C95E0u, 0); return; }
    R(4) = 0xCC010000u; R(0) = 64;
    st8(base, 0xCC008000u, 64);
    R(0) = n;
    st32(base, 0xCC008000u, R(3)); st32(base, 0xCC008000u, n);
}
/* (the texture setup when dirty: a lookup, then the cached texture state loaded once) */
static void tex_state_flush(GM_CTX) {
    GM_FN(0x8024C8D0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(0) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(0), 0) == 0) goto out;
    R(5) = gm_u8(R(13) - 18896);
    R(30) = 0x803E0000u;
    R(0) = 0;
    R(4) = gm_u8(R(30) - 4288);
    gm_set_u8(R(13) - 18896, 0);
    GM_CALLV(0x8024C908u, 0x8023DDD0u, 0);
    R(31) = R(30) - 4288;
    R(3) = gm_u32(R(31) + 8);
    R(0) = R(3) & 4;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) goto out;
    R(0) = R(3) & 3;
    if (cmpu(ctx, R(0), 3) == 0) goto out;
    R(3) = gm_u8(R(30) - 4288); R(4) = gm_u8(R(31) + 1); R(5) = gm_u8(R(31) + 2); R(6) = gm_u8(R(31) + 3);
    R(7) = gm_u32(R(31) + 4);
    GM_CALLV(0x8024C93Cu, 0x80249CB0u, 0);
    R(0) = gm_u32(R(31) + 8); R(0) = R(0) | 3; gm_set_u32(R(31) + 8, R(0));
out:
    R(0) = lr;
}
/* (a forwarder: the args shifted by one, the G3D state object 0x803DFF88 first) */
static void g3d_state_fwd(GM_CTX) {
    GM_FN(0x8024D3C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(12) = R(4); R(11) = R(5); R(10) = R(6); R(0) = R(7); R(9) = R(8);
    R(31) = R(3);
    R(3) = 0x803E0000u;
    R(5) = R(12); R(4) = R(31); R(6) = R(11); R(7) = R(10); R(8) = R(0);
    R(3) = R(3) - 120;
    GM_CALLV(0x8024D408u, 0x8024B1E0u, 0);
    R(0) = lr;
}

/* (the z-compare location: set (GXSetZCompLoc) when it changes; r13 - 18872 the cache) */
static void zcomp_loc(GM_CTX) {
    GM_FN(0x8024B6B0); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(0) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(0), 0) == 0) goto out;
    GM_CALLV(0x8024B6CCu, 0x8023D100u, 0);
    R(0) = gm_u32(R(13) - 18872);
    R(0) = R(0) & 1;
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(4) = R(13) - 18872;
        R(0) = R(3) & 0xFF;
        R(4) = gm_u8(R(4) + 4);
        if (cmpu(ctx, R(4), R(0)) == 0) goto out;
    }
    R(0) = gm_u32(R(13) - 18872);
    R(4) = R(13) - 18872;
    gm_set_u8(R(4) + 4, (uint8_t)R(3));
    R(3) = R(3) & 0xFF;
    R(0) = R(0) | 1;
    gm_set_u32(R(13) - 18872, R(0));
    GM_CALLV(0x8024B708u, 0x801C8EB0u, 0);                                   /* GXSetZCompLoc */
    R(0) = 1;
    gm_set_u8(R(13) - 18896, 1);
out:
    R(0) = lr;
}
/* (dst = src scaled by v per column: PSMTXScaleApply's shape) */
static void mtx_scale_cols(GM_CTX) {
    psq_l(ctx, base, 0, R(5), 0, 0);
    psq_l(ctx, base, 2, R(4), 0, 0);
    psq_l(ctx, base, 4, R(4) + 16, 0, 0);
    psq_l(ctx, base, 5, R(4) + 32, 0, 0);
    ps_mul(GM_PASS, 2, 2, 0);
    ps_mul(GM_PASS, 4, 4, 0);
    psq_l(ctx, base, 1, R(5) + 8, 1, 0);
    ps_mul(GM_PASS, 5, 5, 0);
    psq_l(ctx, base, 3, R(4) + 8, 0, 0);
    psq_l(ctx, base, 0, R(4) + 24, 0, 0);
    psq_l(ctx, base, 6, R(4) + 40, 0, 0);
    ps_mul(GM_PASS, 3, 3, 1);
    psq_st(ctx, base, 2, R(3), 0, 0);
    ps_mul(GM_PASS, 0, 0, 1);
    ps_mul(GM_PASS, 6, 6, 1);
    psq_st(ctx, base, 3, R(3) + 8, 0, 0);
    psq_st(ctx, base, 4, R(3) + 16, 0, 0);
    psq_st(ctx, base, 0, R(3) + 24, 0, 0);
    psq_st(ctx, base, 5, R(3) + 32, 0, 0);
    psq_st(ctx, base, 6, R(3) + 40, 0, 0);
}
/* (a virtual's u32 result split: its high half to +8 (u16), byte 1 to +10, returned as s8) */
static void split_result(GM_CTX) {
    GM_FN(0x8022BE10); GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 76); ctx->ctr = R(12);
    GM_CALLV(0x8022BE2Cu, R(12), 0);
    R(0) = R(3) >> 16;
    gm_set_u16(f + 8, (uint16_t)R(0));
    R(0) = (R(3) >> 8) & 0xFF;
    R(3) = R(0);
    gm_set_u8(f + 10, (uint8_t)R(0));
    R(0) = lr;
    R(3) = (uint32_t)(int8_t)R(3);
}
/* Camera::GetCameraMtx(out): recomputed when dirty (+112 bit 3), then copied */
static void camera_mtx(GM_CTX) {
    GM_FN(0x802540B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(4), 0);
    R(30) = R(4);
    if (c != 0) {
        R(31) = gm_u32(R(3));
        if (cmps(ctx, (int32_t)R(31), 0) != 0) {
            R(0) = gm_u32(R(31) + 112) & 8;
            if (cmps(ctx, (int32_t)R(0), 0) == 0) GM_CALLV(0x802540ECu, 0x802544F0u, 0);
            R(3) = R(31); R(4) = R(30);
            GM_CALLV(0x802540F8u, 0x801C0500u, 0);                           /* PSMTXCopy */
        }
    }
    R(0) = lr;
}
/* math::CosFIdx(fidx): as SinFIdx, the cosine column (+4 / +12) of the table */
static void cos_fidx(GM_CTX) {
    ctx->f[1].u = ctx->f[1].u & ~0x8000000000000000ull;
    GM_FRAME(16); gptr f = gm_frame_sp;
    FB(0, LF(R(2) - 19424));
    goto test;
body:
    FB(1, frsp(F(1) - F(0)));
test:
    cr_fcmp(ctx, 0, F(1), F(0));
    if (CR_BIT(ctx, 1)) { GM_LOOP(); goto body; }
    R(3) = f + 12;
    psq_st(ctx, base, 1, R(3), 1, 3);
    R(3) = f + 8;
    R(0) = gm_u16(f + 12);
    gm_set_u16(f + 8, (uint16_t)R(0));
    psq_l(ctx, base, 0, R(3), 1, 3);
    R(3) = 0x802F0000u;
    R(0) = (R(0) << 4) & 0xFF0u;
    R(3) = R(3) + 29856;
    FB(2, frsp(F(1) - F(0)));
    R(3) = R(3) + R(0);
    FB(1, LF(R(3) + 12));
    FB(0, LF(R(3) + 4));
    FB(1, frsp(F(2) * F(1)));
    FB(1, frsp(F(0) + F(1)));
}
/* (the camera's projection as a texture matrix: identity, scale / translate from +204..+216) */
static void camera_proj_texmtx(GM_CTX) {
    GM_FN(0x802542C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(4), 0);
    R(30) = R(4);
    if (c != 0) {
        R(31) = gm_u32(R(3));
        if (cmps(ctx, (int32_t)R(31), 0) != 0) {
            R(3) = R(30);
            GM_CALLV(0x802542F4u, 0x801C04D0u, 0);                           /* PSMTXIdentity */
            FB(0, LF(R(31) + 204)); stfs(base, R(30), F(0));
            FB(1, LF(R(2) - 18832));
            FB(0, LF(R(31) + 212)); stfs(base, R(30) + 12, F(0));
            FB(0, LF(R(2) - 18824));
            FB(2, LF(R(31) + 208)); ctx->f[2].u ^= 0x8000000000000000ull;    /* (fneg: ps0 only) */
            stfs(base, R(30) + 20, F(2));
            FB(2, LF(R(31) + 216)); stfs(base, R(30) + 28, F(2));
            stfs(base, R(30) + 40, F(1)); stfs(base, R(30) + 44, F(0));
        }
    }
    R(0) = lr;
}
/* (a SetScnObjOption override: option `opt` sets / clears `mask` in the word at +off; others go to
   the parent class's) */
static void scn_option(GM_CTX, uint32_t opt, uint32_t off, uint32_t mask, int set_on_true, uint32_t parent) {
    R(0) = R(4) - opt;
    if (cmpu(ctx, R(0), 1) != 0) { GM_TAIL(parent, 0); return; }
    int c = cmps(ctx, (int32_t)R(5), 0);
    R(0) = gm_u32(R(3) + off);
    if ((c != 0) == (set_on_true != 0)) R(0) = R(0) | mask; else R(0) = R(0) & ~mask;
    gm_set_u32(R(3) + off, R(0));
    R(3) = 1;
}

/* (ChangeColorUpdate / ChangeAlphaUpdate: set GX's colour / alpha update, returning the old one
   kept at 0x804248C0 + off) */
static void change_update(GM_CTX, uint32_t ret, uint32_t gxfn, uint32_t off) {
    GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = 0x80420000u + 18624;
    R(29) = R(3);
    R(3) = R(3) & 0xFF;
    R(30) = gm_u8(R(31) + off);
    GM_CALLV(ret, gxfn, 0);
    st8(base, R(31) + off, R(29));
    R(3) = R(30);
    R(0) = lr;
}
/* (a function-static object (0x80412BF0: a message queue, a thread queue, a mutex), its address) */
static void static_queue_obj(GM_CTX) {
    GM_FN(0x8027B5F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(0) = (uint32_t)(int8_t)gm_u8(R(13) - 18744);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(31) = 0x80410000u + 11248;
        R(0) = 0; R(5) = 4;
        R(7) = R(31) + 892;
        gm_set_u32(R(31) + 848, 0);
        R(6) = R(31) + 904;
        R(3) = R(31) + 800;
        gm_set_u32(R(31) + 876, 0);
        R(4) = R(31) + 832;
        gm_set_u32(R(31) + 880, 0); gm_set_u32(R(31) + 888, 0);
        gm_set_u32(R(31) + 892, R(7)); gm_set_u32(R(31) + 896, R(7));
        gm_set_u32(R(31) + 900, 0);
        gm_set_u32(R(31) + 904, R(6)); gm_set_u32(R(31) + 908, R(6));
        gm_set_u8(R(31) + 916, 0); gm_set_u8(R(31) + 917, 0);
        GM_CALLV(0x8027B65Cu, 0x801B2390u, 0);                               /* OSInitMessageQueue */
        R(3) = R(31) + 792;
        GM_CALLV(0x8027B664u, 0x801B4B20u, 0);                               /* OSInitThreadQueue */
        R(3) = R(31) + 852;
        GM_CALLV(0x8027B66Cu, 0x801B2E20u, 0);                               /* OSInitMutex */
        R(4) = 0x80280000u - 18768; R(5) = 0x80410000u + 11232;
        R(3) = R(31);
        GM_CALLV(0x8027B684u, 0x802DC780u, 0);                               /* __register_global_object */
        R(0) = 1;
        gm_set_u8(R(13) - 18744, 1);
    }
    R(3) = 0x80410000u + 11248;
    R(0) = lr;
}
/* EGG::Math<float>::sqrt: the double sqrt (0x802E8868), rounded */
static void egg_sqrt(GM_CTX) {
    GM_FN(0x802BE470); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(0x802BE480u, 0x802E8868u, 0);
    R(0) = lr;
    ctx->f[1].d = frsp(F(1));
}
/* (a node's world matrix from a scale (f1), a rotation (r5) and a translation: the rotation
   matrix built at +28, the translation stored into the column) */
static void node_srt(GM_CTX) {
    GM_FN(0x802413E0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    FB(0, LF(R(2) - 19172));
    R(7) = R(5) + 8;
    ctx->f[31].u = ctx->f[1].u;
    R(31) = R(5); R(5) = R(4); R(4) = R(3) + 16;
    R(30) = R(3); R(6) = R(31);
    stfs(base, R(3) + 4, F(0)); stfs(base, R(3) + 8, F(0)); stfs(base, R(3) + 12, F(0));
    R(3) = R(3) + 28;
    GM_CALLV(0x80241430u, 0x802405B0u, 0);
    R(0) = gm_u32(R(30));
    R(5) = R(3);
    ctx->f[1].u = ctx->f[31].u;
    R(4) = R(31);
    R(0) = R(0) | 0x80000000u;
    gm_set_u32(R(30), R(0));
    R(3) = gm_frame_sp + 8;
    GM_CALLV(0x80241450u, 0x80241020u, 0);
    gptr f = gm_frame_sp;
    FB(0, LF(f + 8));  stfs(base, R(30) + 40, F(0));
    FB(0, LF(f + 12)); stfs(base, R(30) + 56, F(0));
    FB(0, LF(f + 16)); stfs(base, R(30) + 72, F(0));
    R(0) = lr;
}
/* (call the vfunc at +28 of each enabled object on the list at +32 (with r28, r4), then of +40
   unless bit 0 of +187 is set and r4's bit 0 isn't) */
static void list_call28(GM_CTX) {
    GM_FN(0x802ABE90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3) + 32; R(29) = R(4); R(28) = R(3);
    R(31) = gm_u32(R(3) + 32);
    goto test;
body:
    R(0) = gm_u8(R(31) + 14);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(3) = gm_u32(R(31) + 8); R(5) = R(28); R(4) = gm_u16(R(31) + 12);
        R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 28); ctx->ctr = R(12);
        GM_CALLV(0x802ABEE8u, R(12), 0);
    }
    R(31) = gm_u32(R(31));
test:
    if (cmpu(ctx, R(31), R(30)) != 0) { GM_LOOP(); goto body; }
    R(0) = gm_u8(R(28) + 187) & 1;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(0) = R(29) & 1;
        if (cmps(ctx, (int32_t)R(0), 0) != 0) goto out;
    }
    R(3) = gm_u32(R(28) + 40);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 28); ctx->ctr = R(12);
        GM_CALLV(0x802ABF24u, R(12), 0);
    }
out:
    R(0) = lr;
}
/* (call the vfunc at +32 of this, then (as above) the vfunc at +28 of each object on the +20 list) */
static void list_call32(GM_CTX) {
    GM_FN(0x802ABE00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3); R(29) = R(4);
    R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 32); ctx->ctr = R(12);
    GM_CALLV(0x802ABE30u, R(12), 0);
    R(0) = gm_u8(R(30) + 187) & 1;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(0) = R(29) & 1;
        if (cmps(ctx, (int32_t)R(0), 0) != 0) goto out;
    }
    R(30) = R(30) + 20; R(31) = gm_u32(R(30));
    goto test;
body:
    R(12) = gm_u32(R(31) - 4);
    R(3) = R(31) - 4; R(4) = R(29);
    R(12) = gm_u32(R(12) + 28); ctx->ctr = R(12);
    GM_CALLV(0x802ABE64u, R(12), 0);
    R(31) = gm_u32(R(31));
test:
    if (cmpu(ctx, R(31), R(30)) != 0) { GM_LOOP(); goto body; }
out:
    R(0) = lr;
}
/* (a quad's colour (r4, when r5) or none, then its placement (+122 / +124 plus the screen offset
   at r13 - 18332), when +116 is 2) */
static void quad_color(GM_CTX) {
    GM_FN(0x802CC9F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    R(0) = gm_u8(R(3) + 116);
    if (cmpu(ctx, R(0), 2) != 0) goto out;
    if (cmps(ctx, (int32_t)R(5), 0) != 0) {
        R(0) = gm_u8(R(3) + 24); R(7) = gm_u8(R(4)); R(8) = R(0) | 3;
        R(6) = gm_u8(R(4) + 1); R(5) = gm_u8(R(4) + 2); R(0) = gm_u8(R(4) + 3);
        gm_set_u8(R(3) + 24, (uint8_t)R(8)); gm_set_u8(R(3) + 25, (uint8_t)R(7));
        gm_set_u8(R(3) + 26, (uint8_t)R(6)); gm_set_u8(R(3) + 27, (uint8_t)R(5));
        gm_set_u8(R(3) + 28, (uint8_t)R(0));
    } else {
        R(0) = gm_u8(R(3) + 24) & 0xFC;
        cmps(ctx, (int32_t)R(0), 0);                                          /* (rlwinm.) */
        gm_set_u8(R(3) + 24, (uint8_t)R(0));
    }
    R(8) = gm_u16(R(13) - 18332);
    R(3) = R(31);
    R(4) = gm_u16(R(31) + 122);
    R(6) = 0;
    R(5) = gm_u16(R(13) - 18330);
    R(7) = (uint32_t)-1;
    R(0) = gm_u16(R(31) + 124);
    R(4) = (R(8) + R(4)) & 0xFFFF;
    R(0) = R(5) + R(0);
    R(5) = R(0) & 0xFFFF;
    GM_CALLV(0x802CCA88u, 0x802C02C0u, 0);
    R(0) = 0;
    gm_set_u8(R(31) + 116, 0);
out:
    R(0) = lr;
}
/* (the pending texture-coordinate scale BP write (the cache at 0x803DEF40), then a tail call with
   the flag at r13 - 18896 (cleared) in r4 / r5) */
static void tc_scale_flush(GM_CTX) {
    R(10) = 0x803E0000u;
    R(9) = R(10) - 4288;
    R(4) = gm_u32(R(9) + 8);
    R(0) = R(4) & 4;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) return;
    R(0) = R(4) & 3;
    if (cmpu(ctx, R(0), 2) != 0) return;
    R(6) = gm_u32(R(9) + 4);
    R(4) = 0xFE080000u;
    R(8) = 0xCC010000u;
    R(5) = 97;
    st8(base, R(8) - 32768, R(5));
    R(0) = R(4) - 961;
    R(4) = R(2) - 18944;
    st32(base, R(8) - 32768, R(0));
    R(0) = gm_u8(R(4) + R(6));
    st8(base, R(8) - 32768, R(5));
    R(6) = R(0) << 14;
    R(4) = gm_u8(R(9) + 2);
    R(0) = gm_u8(R(9) + 1);
    R(5) = R(4) - 1;
    R(7) = gm_u8(R(9) + 3);
    R(4) = gm_u8(R(10) - 4288);
    R(0) = R(0) << 4;
    R(7) = R(7) << 16;
    R(5) = R(5) << 10;
    R(0) = R(4) | R(0);
    R(4) = R(7) | R(6);
    R(0) = R(5) | R(0);
    R(0) = R(4) | R(0);
    st32(base, R(8) - 32768, R(0));
    R(0) = gm_u32(R(9) + 8) | 1;
    gm_set_u32(R(9) + 8, R(0));
}
static void tc_scale_then(GM_CTX, uint32_t tail, int with_r5) {
    R(0) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(0), 0) == 0) return;
    tc_scale_flush(GM_PASS);
    if (with_r5) {
        R(4) = 0x803E0000u;
        R(5) = gm_u8(R(13) - 18896);
        R(4) = R(4) - 4288;
        R(0) = 0;
        gm_set_u8(R(13) - 18896, 0);
        R(4) = gm_u8(R(4) + 3);
    } else {
        R(4) = gm_u8(R(13) - 18896);
        R(0) = 0;
        gm_set_u8(R(13) - 18896, 0);
    }
    GM_TAIL(tail, 0);
}
/* (the fog: off for index >= 31 (GXSetFog), else the slot's (0x803DF980 + 48 i + 8) loaded;
   skipped when already set) */
static void fog_set(GM_CTX) {
    GM_FN(0x8024D2C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(4) = 0x803E0000u;
    R(31) = R(3);
    R(5) = gm_u32(R(4) - 1664);
    R(0) = R(5) & 1;
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        R(0) = R(5) & 2;
        if (cmps(ctx, (int32_t)R(0), 0) != 0) {
            R(4) = R(4) - 1664;
            R(0) = gm_u32(R(4) + 4);
            if (cmps(ctx, (int32_t)R(3), (int32_t)R(0)) == 0) goto out;
        }
    }
    if (cmpu(ctx, R(3), 0x1F) > 0) {
        FB(1, LF(R(2) - 18940));
        R(0) = 0;
        gm_set_u32(f + 8, 0);
        R(4) = f + 8;
        ctx->f[2].u = ctx->f[1].u;
        R(3) = 0;
        ctx->f[3].u = ctx->f[1].u;
        ctx->f[4].u = ctx->f[1].u;
        GM_CALLV(0x8024D328u, 0x801C8920u, 0);                               /* GXSetFog */
    } else {
        R(0) = (uint32_t)((int32_t)R(31) * 48);
        R(4) = 0x803E0000u;
        R(3) = f + 12;
        R(4) = R(4) - 1664;
        R(4) = R(4) + R(0);
        R(4) = R(4) + 8;
        GM_CALLV(0x8024D348u, 0x8025F2B0u, 0);
        GM_CALLV(0x8024D34Cu, 0x8025F3B0u, 0);
    }
    R(4) = 0x803E0000u;
    R(0) = gm_u32(R(4) - 1664);
    R(3) = R(4) - 1664;
    gm_set_u32(R(3) + 4, R(31));
    R(0) = R(0) | 3;
    gm_set_u32(R(4) - 1664, R(0));
out:
    R(0) = lr;
}
/* (find the entry (0x804238A8's list) whose +8 is r3; 0 if none) */
static void find_by_8(GM_CTX) {
    GM_FN(0x802BA5C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = 0x80420000u;
    R(30) = R(3);
    R(3) = 0;
    for (;;) {
        R(4) = R(3);
        R(3) = R(31) + 14504;
        GM_CALLV(0x802BA600u, 0x80228FF0u, 0);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; break; }
        GM_LOOP();
        R(0) = gm_u32(R(3) + 8);
        if (cmpu(ctx, R(0), R(30)) == 0) break;
    }
    R(0) = lr;
}
/* (a clamped table lookup: f1 clamped to [lo, hi], scaled, an index into table *r3, the value
   clamped too) */
static void clamp_lookup(GM_CTX) {
    FB(0, LF(R(2) - 17724));
    GM_FRAME(16); gptr f = gm_frame_sp;
    cr_fcmp(ctx, 0, F(1), F(0));
    if (!CR_BIT(ctx, 1)) {
        FB(0, LF(R(2) - 17696));
        cr_fcmp(ctx, 0, F(1), F(0));
        if (!CR_BIT(ctx, 0)) ctx->f[0].u = ctx->f[1].u;
    }
    FB(2, LF(R(2) - 17720));
    R(4) = 0x80350000u;
    R(0) = gm_u32(R(3));
    R(4) = R(4) - 3448;
    FB(1, frsp(F(0) * F(2)));
    FB(0, LF(R(2) - 17700));
    R(0) = R(0) << 2;
    FB(3, LF(R(2) - 17724));
    R(3) = gm_u32(R(4) + R(0));
    FB(0, frsp(F(0) * F(1)));
    FB(0, frsp(F(2) + F(0)));
    ctx->f[0].u = fctiw_bits(F(0), 1);
    st64(base, f + 8, ctx->f[0].u);
    R(0) = gm_u32(f + 12);
    R(0) = R(0) << 2;
    FB(0, LF(R(3) + R(0)));
    cr_fcmp(ctx, 0, F(0), F(3));
    if (!CR_BIT(ctx, 1)) {
        FB(3, LF(R(2) - 17696));
        cr_fcmp(ctx, 0, F(0), F(3));
        if (!CR_BIT(ctx, 0)) ctx->f[3].u = ctx->f[0].u;
    }
    ctx->f[1].u = ctx->f[3].u;
}
/* (call the vfunc at +32 of each enabled object on the list at +8, with this) */
static void list_call32b(GM_CTX) {
    GM_FN(0x802B4960); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3) + 8; R(29) = R(3);
    R(31) = gm_u32(R(3) + 8);
    goto test;
body:
    R(0) = gm_u8(R(31) + 14);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(3) = gm_u32(R(31) + 8); R(5) = R(29); R(4) = gm_u16(R(31) + 12);
        R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 32); ctx->ctr = R(12);
        GM_CALLV(0x802B49B0u, R(12), 0);
    }
    R(31) = gm_u32(R(31));
test:
    if (cmpu(ctx, R(31), R(30)) != 0) { GM_LOOP(); goto body; }
    R(0) = lr;
}

/* strcmp (MSL): bytes until both are word-aligned, then a word at a time while no word holds a
   zero byte ((w - 0x01010101) & ~w & 0x80808080 - the loop's own test drops the ~w), then bytes */
static void msl_strcmp(GM_CTX) {
    R(5) = gm_u8(R(3)); R(0) = gm_u8(R(4));
    R(0) = R(5) - R(0);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(3) = R(0); return; }
    R(0) = R(4) & 3; R(6) = R(3) & 3;
    if (cmpu(ctx, R(0), R(6)) != 0) goto bytes_tail;
    if (cmps(ctx, (int32_t)R(6), 0) != 0) {
        if (cmps(ctx, (int32_t)R(5), 0) == 0) { R(3) = 0; return; }
        { uint32_t a_ = R(6); R(0) = 3u - a_; ctx->xer_ca = 3u >= a_; }
        ctx->ctr = R(0);
        if (cmps(ctx, (int32_t)R(0), 0) != 0) {
            for (;;) {
                R(3) = R(3) + 1; R(5) = gm_u8(R(3));
                R(4) = R(4) + 1; R(0) = gm_u8(R(4));
                R(0) = R(5) - R(0);
                if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(3) = R(0); return; }
                if (cmps(ctx, (int32_t)R(5), 0) == 0) { R(3) = 0; return; }
                if (--ctx->ctr == 0) break;
                GM_LOOP();
            }
        }
        R(3) = R(3) + 1; R(4) = R(4) + 1;
    }
    R(7) = gm_u32(R(3));
    R(5) = 0x80810000u;
    R(6) = R(5) - 32640;
    R(8) = gm_u32(R(4));
    R(5) = R(7) + 0xFEFF0000u;
    R(5) = R(5) - 257;
    R(5) = R(5) & ~R(7);
    R(0) = R(5) & R(6);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        while (cmpu(ctx, R(7), R(8)) == 0) {
            GM_LOOP();
            R(3) = R(3) + 4; R(7) = gm_u32(R(3));
            R(4) = R(4) + 4; R(8) = gm_u32(R(4));
            R(5) = R(7) + 0xFEFF0000u;
            R(0) = R(5) - 257;
            R(0) = R(0) & R(6);
            if (cmps(ctx, (int32_t)R(0), 0) != 0) break;
        }
    }
    R(5) = gm_u8(R(3)); R(0) = gm_u8(R(4));
    R(0) = R(5) - R(0);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(3) = R(0); return; }
bytes_tail:
    if (cmps(ctx, (int32_t)R(5), 0) == 0) { R(3) = 0; return; }
    for (;;) {
        R(3) = R(3) + 1; R(5) = gm_u8(R(3));
        R(4) = R(4) + 1; R(0) = gm_u8(R(4));
        R(0) = R(5) - R(0);
        if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(3) = R(0); return; }
        if (cmps(ctx, (int32_t)R(5), 0) == 0) break;
        GM_LOOP();
    }
    R(3) = 0;
}
/* memcmp (MSL) */
static void msl_memcmp(GM_CTX) {
    R(7) = R(4) - 1; R(6) = R(3) - 1; R(4) = R(5) + 1;
    goto test;
body:
    R(6) = R(6) + 1; R(3) = gm_u8(R(6));
    R(7) = R(7) + 1; R(0) = gm_u8(R(7));
    if (cmpu(ctx, R(3), R(0)) != 0) {
        R(4) = gm_u8(R(6)); R(3) = 1; R(0) = gm_u8(R(7));
        if (cmpu(ctx, R(4), R(0)) < 0) R(3) = (uint32_t)-1;
        return;
    }
test:
    { uint32_t a_ = R(4); R(4) = a_ - 1; ctx->xer_ca = a_ != 0; }
    if (cmps(ctx, (int32_t)R(4), 0) != 0) { GM_LOOP(); goto body; }
    R(3) = 0;
}
/* (a GX call, then a dirty bit (r13 - 18222) of the 2D state keeper) */
static void gx_then_dirty(GM_CTX, uint32_t ret, uint32_t gxfn, uint32_t bit) {
    GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(ret, gxfn, 0);
    R(0) = gm_u16(R(13) - 18222) | bit;
    gm_set_u16(R(13) - 18222, (uint16_t)R(0));
    R(0) = lr;
}
/* mTexture_c: the GXTexObj from its fields (GXInitTexObj, then GXInitTexObjLOD) */
static void mtex_init_obj(GM_CTX) {
    GM_FN(0x802C0BA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(10) = 0;
    R(31) = R(4);
    R(4) = gm_u32(R(3) + 16);
    R(30) = R(3);
    R(5) = gm_u16(R(30) + 4); R(3) = R(31); R(6) = gm_u16(R(30) + 6);
    R(7) = gm_u8(R(30) + 9); R(8) = gm_u8(R(30) + 10); R(9) = gm_u8(R(30) + 11);
    GM_CALLV(0x802C0BE0u, 0x801C6D90u, 0);                                   /* GXInitTexObj */
    FB(1, LF(R(2) - 15984));
    R(3) = R(31);
    R(4) = gm_u8(R(30) + 12);
    R(6) = 0;
    ctx->f[2].u = ctx->f[1].u;
    R(5) = gm_u8(R(30) + 13);
    ctx->f[3].u = ctx->f[1].u;
    R(7) = 0; R(8) = 0;
    GM_CALLV(0x802C0C08u, 0x801C6FF0u, 0);                                   /* GXInitTexObjLOD */
    R(0) = lr;
}
/* mTexture_c::load(id): the GXTexObj built on the stack, loaded */
static void mtex_load(GM_CTX) {
    GM_FN(0x802C0B60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(4);
    R(4) = gm_frame_sp + 8;
    GM_CALLV(0x802C0B7Cu, 0x802C0BA0u, 0);
    R(4) = R(31);
    R(3) = gm_frame_sp + 8;
    GM_CALLV(0x802C0B88u, 0x801C74C0u, 0);                                   /* GXLoadTexObj */
    R(0) = lr;
}
/* (call the vfunc at +24 of this, then the vfunc at +20 of each object on the +20 list; only when
   bit 0 of +187) */
static void list_call24(GM_CTX) {
    GM_FN(0x802ABD60); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3); R(29) = R(4);
    R(0) = gm_u8(R(3) + 187) & 1;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) goto out;
    R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + 24); ctx->ctr = R(12);
    GM_CALLV(0x802ABD9Cu, R(12), 0);
    R(30) = R(30) + 20; R(31) = gm_u32(R(30));
    goto test;
body:
    R(12) = gm_u32(R(31) - 4);
    R(3) = R(31) - 4; R(4) = R(29);
    R(12) = gm_u32(R(12) + 20); ctx->ctr = R(12);
    GM_CALLV(0x802ABDBCu, R(12), 0);
    R(31) = gm_u32(R(31));
test:
    if (cmpu(ctx, R(31), R(30)) != 0) { GM_LOOP(); goto body; }
out:
    R(0) = lr;
}
/* EGG::Vector3f::normalise (in place, when the length is above epsilon) */
static void egg_normalise(GM_CTX) {
    GM_FN(0x802BE6B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    FB(1, LF(R(3))); FB(0, LF(R(3) + 4));
    FB(1, frsp(F(1) * F(1)));
    FB(2, LF(R(3) + 8));
    FB(0, frsp(F(0) * F(0)));
    FB(2, frsp(F(2) * F(2)));
    FB(0, frsp(F(1) + F(0)));
    FB(1, frsp(F(2) + F(0)));
    GM_CALLV(0x802BE6E8u, 0x802BE470u, 0);                                   /* EGG::Math<float>::sqrt */
    FB(0, LF(R(2) - 16104));
    cr_fcmp(ctx, 0, F(1), F(0));
    if (CR_BIT(ctx, 1)) {
        FB(0, LF(R(2) - 16100));
        FB(3, LF(R(31)));
        FB(4, frsp(F(0) / F(1)));
        FB(2, LF(R(31) + 4));
        FB(0, LF(R(31) + 8));
        FB(3, frsp(F(3) * F(4)));
        FB(2, frsp(F(2) * F(4)));
        FB(0, frsp(F(0) * F(4)));
        stfs(base, R(31), F(3)); stfs(base, R(31) + 4, F(2)); stfs(base, R(31) + 8, F(0));
    }
    R(0) = lr;
}
/* (a list-owning object's deleting dtor: LinkListImpl's dtor, then __dl when r4 > 0) */
static void list_obj_dtor(GM_CTX) {
    GM_FN(0x80277870); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(4) = 0;
        GM_CALLV(0x8027789Cu, 0x80229030u, 0);                               /* LinkListImpl::~LinkListImpl */
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x802778ACu, 0x802B9280u, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
/* (a clamped table lookup: f1 clamped, scaled, truncated - entry 904 + i of 0x802FABE0) */
static void clamp_lookup2(GM_CTX) {
    FB(2, LF(R(2) - 17716));
    GM_FRAME(16); gptr f = gm_frame_sp;
    cr_fcmp(ctx, 0, F(1), F(2));
    if (!CR_BIT(ctx, 1)) {
        FB(2, LF(R(2) - 17712));
        cr_fcmp(ctx, 0, F(1), F(2));
        if (!CR_BIT(ctx, 0)) ctx->f[2].u = ctx->f[1].u;
    }
    FB(0, LF(R(2) - 17708));
    R(3) = 0x80300000u - 21536;
    FB(0, frsp(F(0) * F(2)));
    ctx->f[0].u = fctiw_bits(F(0), 1);
    st64(base, f + 8, ctx->f[0].u);
    R(4) = gm_u32(f + 12);
    R(0) = R(4) + 904;
    R(0) = R(0) << 2;
    FB(1, LF(R(3) + R(0)));
}
/* (a 3D sound's position update: the vector (r5) copied to the frame, passed on unless off (+12)
   or r8 is 2) */
static void snd_pos(GM_CTX) {
    GM_FN(0x8026C210); GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(4) = R(3);
    R(0) = gm_u8(R(3) + 12);
    if (cmps(ctx, (int32_t)R(0), 0) != 0 && cmps(ctx, (int32_t)R(8), 2) != 0) {
        R(0) = gm_u32(R(5)); R(3) = f + 8; gm_set_u32(f + 8, R(0));
        R(4) = R(4) + 68;
        R(0) = gm_u32(R(5) + 4); gm_set_u32(f + 12, R(0));
        R(0) = gm_u32(R(5) + 8); gm_set_u32(f + 16, R(0));
        GM_CALLV(0x8026C258u, 0x801A3880u, 0);
    }
    R(0) = lr;
}
/* (a state change (1 / 2 / 3): the flags, the state word, then the callback set (tail)) */
static void sound_state(GM_CTX) {
    uint32_t cb, st, r4v;
    if (cmps(ctx, (int32_t)R(4), 1) == 0) {
        R(0) = 1; R(5) = 0x80270000u;
        gm_set_u8(R(3) + 4, 1);
        R(5) = R(5) + 1824; R(4) = 1;
        gm_set_u8(R(3) + 5, 1);
        gm_set_u32(R(3) + 8, 1);
        R(3) = gm_u32(R(3) + 52);
        GM_TAIL(0x801E1E20u, 0); return;
    }
    if (cmps(ctx, (int32_t)R(4), 2) == 0) { st = 3; cb = 2096; r4v = 4; }
    else if (cmps(ctx, (int32_t)R(4), 3) == 0) { st = 5; cb = 2336; r4v = 0; }
    else return;
    R(6) = 1; R(0) = st; R(5) = 0x80270000u;
    gm_set_u8(R(3) + 4, 1);
    R(5) = R(5) + cb; R(4) = r4v;
    gm_set_u8(R(3) + 5, 1);
    gm_set_u32(R(3) + 8, R(0));
    R(3) = gm_u32(R(3) + 52);
    GM_TAIL(0x801E1E20u, 0);
}
/* (wait for a resource (fn_801AC810), yielding; then unlock its mutex) */
static void wait_unlock(GM_CTX) {
    GM_FN(0x8022B380); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    for (;;) {
        GM_CALLV(0x8022B398u, 0x801AC810u, 0);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) break;
        GM_LOOP();
        GM_CALLV(0x8022B394u, 0x801B50F0u, 0);                               /* OSYieldThread */
    }
    R(3) = 0x803E0000u - 24360 + 4;
    GM_CALLV(0x8022B3B0u, 0x801B2F40u, 0);                                   /* OSUnlockMutex */
    R(0) = lr;
}

/* ---- MSL libm (fdlibm): the double kernels exactly as the PowerPC code computes them - one
   operation a statement (no contraction), ps1 untouched (double ops leave it) */
#define FD(n, v) (ctx->f[n].d = (v))
#define LD(n, a) (ctx->f[n].u = ld64(base, (a)))
/* __kernel_sin(x f1, y f2, iy r3) */
static void k_sin(GM_CTX) {
    GM_FRAME(32); gptr f = gm_frame_sp;
    R(0) = 0x3E400000u;
    st64(base, f + 8, ctx->f[1].u);
    R(4) = gm_u32(f + 8) & 0x7FFFFFFFu;
    if (cmps(ctx, (int32_t)R(4), (int32_t)R(0)) < 0) {
        ctx->f[0].u = fctiw_bits(F(1), 1);
        st64(base, f + 16, ctx->f[0].u);
        R(0) = gm_u32(f + 20);
        if (cmps(ctx, (int32_t)R(0), 0) == 0) return;            /* (|x| < 2^-27 and (int)x == 0: x) */
    }
    FD(7, F(1) * F(1));
    LD(0, R(2) - 13736); LD(5, R(2) - 13744);
    int iy0 = cmps(ctx, (int32_t)R(3), 0);
    LD(4, R(2) - 13752); LD(3, R(2) - 13760);
    FD(6, F(0) * F(7));
    LD(0, R(2) - 13768);
    FD(8, F(7) * F(1));
    FD(5, F(5) + F(6)); FD(5, F(7) * F(5));
    FD(4, F(4) + F(5)); FD(4, F(7) * F(4));
    FD(3, F(3) + F(4)); FD(3, F(7) * F(3));
    FD(0, F(0) + F(3));
    if (iy0 == 0) {
        FD(2, F(7) * F(0));
        LD(0, R(2) - 13728);
        FD(0, F(0) + F(2));
        FD(0, F(8) * F(0));
        FD(1, F(1) + F(0));
        return;
    }
    LD(4, R(2) - 13720);
    FD(3, F(8) * F(0));
    LD(0, R(2) - 13728);
    FD(4, F(4) * F(2));
    FD(0, F(0) * F(8));
    FD(3, F(4) - F(3));
    FD(3, F(7) * F(3));
    FD(2, F(3) - F(2));
    FD(0, F(2) - F(0));
    FD(1, F(1) - F(0));
}
/* __kernel_cos(x f1, y f2) */
static void k_cos(GM_CTX) {
    GM_FRAME(32); gptr f = gm_frame_sp;
    R(0) = 0x3E400000u;
    st64(base, f + 8, ctx->f[1].u);
    R(3) = gm_u32(f + 8);
    R(4) = R(3) & 0x7FFFFFFFu;
    if (cmps(ctx, (int32_t)R(4), (int32_t)R(0)) < 0) {
        ctx->f[0].u = fctiw_bits(F(1), 1);
        st64(base, f + 24, ctx->f[0].u);
        R(0) = gm_u32(f + 28);
        if (cmps(ctx, (int32_t)R(0), 0) == 0) { LD(1, R(2) - 13904); return; }   /* (1.0) */
    }
    FD(8, F(1) * F(1));
    LD(0, R(2) - 13856);
    R(3) = 0x3FD30000u;
    LD(6, R(2) - 13864);
    R(0) = R(3) + 13107;
    LD(5, R(2) - 13872);
    FD(7, F(0) * F(8));
    LD(4, R(2) - 13880); LD(3, R(2) - 13888);
    int c = cmps(ctx, (int32_t)R(4), (int32_t)R(0));
    LD(0, R(2) - 13896);
    FD(6, F(6) + F(7)); FD(6, F(8) * F(6));
    FD(5, F(5) + F(6)); FD(5, F(8) * F(5));
    FD(4, F(4) + F(5)); FD(4, F(8) * F(4));
    FD(3, F(3) + F(4)); FD(3, F(8) * F(3));
    FD(0, F(0) + F(3));
    FD(3, F(8) * F(0));
    if (c < 0) {                                                  /* (|x| < 0.3) */
        FD(3, F(8) * F(3));
        LD(4, R(2) - 13848); LD(0, R(2) - 13904);
        FD(1, F(1) * F(2));
        FD(2, F(4) * F(8));
        FD(1, F(3) - F(1));
        FD(1, F(2) - F(1));
        FD(1, F(0) - F(1));
        return;
    }
    R(0) = 0x3FE90000u;
    if (cmps(ctx, (int32_t)R(4), (int32_t)R(0)) > 0) {            /* (qx: 0.28125 above 0.78125, else x/4) */
        LD(0, R(2) - 13840);
        st64(base, f + 16, ctx->f[0].u);
    } else {
        R(3) = R(4) + 0xFFE00000u;
        R(0) = 0;
        gm_set_u32(f + 16, R(3)); gm_set_u32(f + 20, 0);
    }
    LD(0, R(2) - 13848);
    FD(3, F(8) * F(3));
    LD(5, f + 16);
    FD(6, F(0) * F(8));
    LD(4, R(2) - 13904);
    FD(0, F(1) * F(2));
    FD(2, F(6) - F(5));
    FD(1, F(4) - F(5));
    FD(0, F(3) - F(0));
    FD(0, F(2) - F(0));
    FD(1, F(1) - F(0));
}
/* sin / cos / tan: |x| <= pi/4 straight to the kernel; inf / NaN: x - x; else reduced
   (__ieee754_rem_pio2, 0x802E5DB8) and the kernel picked by the quadrant */
static void trig(GM_CTX, int which, uint32_t ra) {
    GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = ctx->r[1];                    /* (the frame GM_FN made) */
    R(3) = 0x3FE90000u;
    LD(2, R(2) - (which == 0 ? 13528 : which == 1 ? 13600 : 13520));   /* (0.0) */
    st64(base, f + 8, ctx->f[1].u);
    R(0) = R(3) + 8699;
    R(3) = gm_u32(f + 8) & 0x7FFFFFFFu;
    if (cmps(ctx, (int32_t)R(3), (int32_t)R(0)) <= 0) {
        if (which == 0) { R(3) = 0; GM_CALLV(ra + 0x34, 0x802E7904u, 0); }
        else if (which == 1) GM_CALLV(ra + 0x30, 0x802E613Cu, 0);
        else { R(3) = 1; GM_CALLV(ra + 0x34, 0x802E79C4u, 0); }
        goto out;
    }
    R(0) = 0x7FF00000u;
    if (cmps(ctx, (int32_t)R(3), (int32_t)R(0)) >= 0) { FD(1, F(1) - F(1)); goto out; }
    R(3) = f + 16;
    GM_CALLV(ra + (which == 1 ? 0x50 : 0x54), 0x802E5DB8u, 0);   /* __ieee754_rem_pio2 */
    if (which == 2) {
        R(0) = (R(3) << 1) & 2;
        LD(1, f + 16); LD(2, f + 24);
        { uint32_t a_ = R(0); R(3) = 1u - a_; ctx->xer_ca = 1u >= a_; }
        GM_CALLV(ra + 0x68, 0x802E79C4u, 0);                      /* __kernel_tan */
        goto out;
    }
    R(0) = R(3) & 3;
    int q;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) q = 0;
    else if (cmps(ctx, (int32_t)R(0), 1) == 0) q = 1;
    else if (cmps(ctx, (int32_t)R(0), 2) == 0) q = 2;
    else q = 3;
    int k = which == 0 ? q : (q + 1) & 3;                         /* (cos x = sin(x + pi/2)) */
    static const uint16_t ret_sin[4] = { 0x80, 0x90, 0xA4, 0xB8 }, ret_cos[4] = { 0x78, 0x8C, 0xA0, 0xB8 };
    uint32_t ret = ra + (which == 0 ? ret_sin[q] : ret_cos[q]);
    LD(1, f + 16);
    if (k == 0 || k == 2) { R(3) = 1; LD(2, f + 24); GM_CALLV(ret, 0x802E7904u, 0); }
    else { LD(2, f + 24); GM_CALLV(ret, 0x802E613Cu, 0); }
    if (k >= 2) ctx->f[1].u ^= 0x8000000000000000ull;
out:
    R(0) = lr;
}

/* (a frame's value from an animation key table at r4 (+0 the first frame, +4 the kind, +12 the
   data): kind 0 the frame offset (u16), 1 a u16 table, 2 a binary search of {frame, value}
   pairs; 0xFFFF if none) */
static void anm_key_lookup(GM_CTX) {
    R(0) = gm_u16(R(4) + 4);
    R(3) = 0x10000u - 1;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(0) = gm_u16(R(4)); R(3) = gm_u16(R(4) + 12);
        R(0) = R(5) - R(0); R(0) = R(3) + R(0); R(3) = R(0) & 0xFFFF;
        return;
    }
    if (cmps(ctx, (int32_t)R(0), 1) == 0) {
        R(0) = gm_u16(R(4));
        R(0) = (R(5) - R(0)) << 1;
        R(3) = R(4) + R(0);
        R(3) = gm_u16(R(3) + 12);
        return;
    }
    if (cmps(ctx, (int32_t)R(0), 2) != 0) return;
    R(6) = R(4) + 12;
    R(4) = gm_u16(R(4) + 12);
    R(7) = R(6) + 2;
    R(0) = (R(4) - 1) << 2;
    R(4) = R(6) + R(0);
    R(6) = R(4) + 2;
    goto test;
    for (;;) {
        R(0) = R(6) - R(7);
        { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && (v_ & 3) != 0; R(0) = (uint32_t)(v_ >> 2); }
        { uint64_t t_ = (uint64_t)R(0) + ctx->xer_ca; R(4) = (uint32_t)t_; ctx->xer_ca = (uint32_t)(t_ >> 32); }
        R(0) = R(4) >> 31;
        R(0) = R(0) + R(4);
        R(0) = (R(0) << 1) & 0xFFFFFFFCu;
        R(4) = R(7) + R(0);
        R(0) = gm_u16(R(7) + R(0));
        if (cmpu(ctx, R(0), R(5)) < 0) R(7) = R(4) + 4;
        else if (cmpu(ctx, R(5), R(0)) < 0) R(6) = R(4) - 4;
        else { R(3) = gm_u16(R(4) + 2); return; }
test:
        if (cmpu(ctx, R(7), R(6)) > 0) return;
        GM_LOOP();
    }
}

/* (a display list (*r3, size by r4: 32 / 64 / 128 / 160) - through GXCallDisplayList when r5,
   else its call command written into the FIFO) */
static void dl_call_sized(GM_CTX) {
    if (cmps(ctx, (int32_t)R(4), 0) == 0) return;
    int c = cmps(ctx, (int32_t)R(5), 0);
    R(3) = gm_u32(R(3));
    uint32_t n;
    if (cmpu(ctx, R(4), 2) < 0) n = 32;
    else if (cmpu(ctx, R(4), 4) < 0) n = 64;
    else if (cmpu(ctx, R(4), 8) < 0) n = 128;
    else n = 160;
    if (c != 0) { R(4) = n; GM_TAIL(0x801C95E0u, 0); return; }            /* GXCallDisplayList */
    R(4) = 0xCC010000u;
    R(0) = 64;
    st8(base, R(4) - 32768, R(0));
    R(0) = n;
    st32(base, R(4) - 32768, R(3));
    st32(base, R(4) - 32768, R(0));
}
/* (as clamp_lookup: f1 clamped and offset, scaled, the entry divided by entry 128 when +4, the
   result clamped by +5) */
static void clamp_lookup3(GM_CTX) {
    FB(2, LF(R(2) - 17728));
    GM_FRAME(16); gptr f = gm_frame_sp;
    cr_fcmp(ctx, 0, F(1), F(2));
    if (!CR_BIT(ctx, 1)) {
        FB(2, LF(R(2) - 17704));
        cr_fcmp(ctx, 0, F(1), F(2));
        if (!CR_BIT(ctx, 0)) ctx->f[2].u = ctx->f[1].u;
    }
    FB(0, LF(R(2) - 17728));
    R(4) = 0x80350000u;
    R(0) = gm_u32(R(3));
    R(4) = R(4) - 3448;
    FB(1, frsp(F(0) + F(2)));
    FB(2, LF(R(2) - 17720));
    R(5) = R(0) << 2;
    R(0) = gm_u8(R(3) + 4);
    FB(0, LF(R(2) - 17700));
    FB(1, frsp(F(1) * F(2)));
    int c = cmps(ctx, (int32_t)R(0), 0);
    R(4) = gm_u32(R(4) + R(5));
    FB(0, frsp(F(0) * F(1)));
    FB(0, frsp(F(2) + F(0)));
    ctx->f[0].u = fctiw_bits(F(0), 1);
    st64(base, f + 8, ctx->f[0].u);
    R(0) = gm_u32(f + 12) << 2;
    FB(2, LF(R(4) + R(0)));
    if (c != 0) { FB(0, LF(R(4) + 512)); FB(2, frsp(F(2) / F(0))); }
    R(0) = gm_u8(R(3) + 5);
    uint32_t lo = cmps(ctx, (int32_t)R(0), 0) != 0 ? 17728 : 17724;
    FB(1, LF(R(2) - lo));
    cr_fcmp(ctx, 0, F(2), F(1));
    if (CR_BIT(ctx, 1)) return;
    FB(1, LF(R(2) - 17696));
    cr_fcmp(ctx, 0, F(2), F(1));
    if (CR_BIT(ctx, 0)) return;
    ctx->f[1].u = ctx->f[2].u;
}
/* (camera slot r4 (< 32) of the g3d state (0x803E29B4): its camera / projection / texture
   projection matrices taken from camera r3; with r5 the current slot) */
static void camera_slot_set(GM_CTX) {
    GM_FN(0x8024D420); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(11) = f + 32;
    int c = cmpu(ctx, R(4), 0x1F);
    R(26) = R(3); R(27) = R(4); R(28) = R(5);
    if (c <= 0) {
        R(29) = (uint32_t)((int32_t)R(4) * 48);
        R(30) = 0x803E0000u;
        R(31) = R(30) + 10676;
        R(4) = R(31) + R(29) + 52;
        GM_CALLV(0x8024D460u, 0x802540B0u, 0);                               /* Camera::GetCameraMtx */
        R(0) = R(27) << 6;
        R(3) = R(26);
        R(4) = R(31) + R(0) + 1588;
        GM_CALLV(0x8024D474u, 0x80254110u, 0);                               /* (the projection) */
        R(4) = R(31) + R(29);
        R(3) = R(26);
        R(4) = R(4) + 3636;
        GM_CALLV(0x8024D484u, 0x802541F0u, 0);                               /* (the projection texture matrix) */
        R(4) = R(31) + R(29);
        R(3) = R(26);
        R(4) = R(4) + 5172;
        GM_CALLV(0x8024D494u, 0x802542C0u, 0);
        if (cmps(ctx, (int32_t)R(28), 0) != 0) {
            R(0) = gm_u16(R(30) + 10676);
            gm_set_u16(R(31) + 2, (uint16_t)R(27));
            R(0) = R(0) & 0xFFFE;
            gm_set_u16(R(30) + 10676, (uint16_t)R(0));
        }
    }
    R(11) = f + 32;
    R(0) = lr;
}
/* Camera::GetProjectionMtx(out): rebuilt when dirty (+112 bit 7: ortho (bit 6), frustum (bit 4)
   or perspective), copied as a 4x4 */
static void camera_proj(GM_CTX) {
    GM_FN(0x80254110); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(4), 0);
    R(30) = R(4);
    if (c == 0) goto out;
    R(31) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(31), 0) == 0) goto out;
    R(0) = gm_u32(R(31) + 112) & 0x80;
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(3) = gm_u32(R(31) + 112);
        R(0) = R(3) & 0x40;
        if (cmps(ctx, (int32_t)R(0), 0) != 0 || (R(0) = R(3) & 0x10, cmps(ctx, (int32_t)R(0), 0) != 0)) {
            int ortho = (R(3) & 0x40) != 0;
            FB(1, LF(R(31) + 188)); R(3) = R(31) + 48;
            FB(2, LF(R(31) + 192)); FB(3, LF(R(31) + 196)); FB(4, LF(R(31) + 200));
            FB(5, LF(R(31) + 180)); FB(6, LF(R(31) + 184));
            if (ortho) GM_CALLV(0x80254174u, 0x801C1350u, 0);              /* C_MTXOrtho */
            else GM_CALLV(0x802541A0u, 0x801C11C0u, 0);                    /* C_MTXFrustum */
        } else {
            FB(1, LF(R(31) + 172)); R(3) = R(31) + 48;
            FB(2, LF(R(31) + 176)); FB(3, LF(R(31) + 180)); FB(4, LF(R(31) + 184));
            GM_CALLV(0x802541BCu, 0x801C1260u, 0);                         /* C_MTXPerspective */
        }
        R(0) = gm_u32(R(31) + 112) | 0x80;
        gm_set_u32(R(31) + 112, R(0));
    }
    R(3) = R(30); R(4) = R(31) + 48;
    GM_CALLV(0x802541D4u, 0x802384F0u, 0);                                   /* (4x4 copy) */
out:
    R(0) = lr;
}
/* Camera::GetProjectionTexMtx(out): the texture projection for ortho / frustum / perspective
   (the scale +208 negated, +212 / +216 the translation) */
static void camera_proj_tex(GM_CTX) {
    GM_FN(0x802541F0); GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    if (cmps(ctx, (int32_t)R(4), 0) == 0) goto out;
    R(5) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(5), 0) == 0) goto out;
    R(3) = gm_u32(R(5) + 112);
    R(0) = R(3) & 0x40;
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        FB(0, LF(R(5) + 208)); R(3) = R(4);
        FB(1, LF(R(5) + 188));
        ctx->f[6].u = ctx->f[0].u ^ 0x8000000000000000ull;
        FB(2, LF(R(5) + 192)); FB(3, LF(R(5) + 196)); FB(4, LF(R(5) + 200));
        FB(5, LF(R(5) + 204)); FB(7, LF(R(5) + 212)); FB(8, LF(R(5) + 216));
        GM_CALLV(0x80254248u, 0x801C10D0u, 0);                               /* C_MTXLightOrtho */
        goto out;
    }
    R(0) = R(3) & 0x10;
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        FB(0, LF(R(5) + 216)); R(3) = R(4);
        stfs(base, f + 8, F(0));
        FB(0, LF(R(5) + 208));
        FB(1, LF(R(5) + 188));
        ctx->f[7].u = ctx->f[0].u ^ 0x8000000000000000ull;
        FB(2, LF(R(5) + 192)); FB(3, LF(R(5) + 196)); FB(4, LF(R(5) + 200));
        FB(5, LF(R(5) + 180)); FB(6, LF(R(5) + 204)); FB(8, LF(R(5) + 212));
        GM_CALLV(0x80254288u, 0x801C0F20u, 0);                               /* C_MTXLightFrustum */
        goto out;
    }
    FB(0, LF(R(5) + 208)); R(3) = R(4);
    FB(1, LF(R(5) + 172));
    ctx->f[4].u = ctx->f[0].u ^ 0x8000000000000000ull;
    FB(2, LF(R(5) + 176)); FB(3, LF(R(5) + 204)); FB(5, LF(R(5) + 212)); FB(6, LF(R(5) + 216));
    GM_CALLV(0x802542B0u, 0x801C0FD0u, 0);                                   /* C_MTXLightPerspective */
out:
    R(0) = lr;
}
/* (a pane's global position: its parent's (recursively, 0x802C6CE0 transforming the offset)
   plus its own (+64 / +68)) */
static void pane_global_pos(GM_CTX) {
    GM_FN(0x802D19F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(30) = R(5); R(29) = R(4); R(28) = R(3);
    R(31) = gm_u32(R(3) + 60);
    if (cmps(ctx, (int32_t)R(31), 0) != 0) {
        R(3) = R(31); R(4) = f + 12; R(5) = f + 8;
        GM_CALLV(0x802D1A34u, 0x802D19F0u, 0);
        FB(1, LF(R(28) + 64));
        R(3) = R(31);
        FB(2, LF(R(28) + 68));
        R(4) = R(29); R(5) = R(30);
        GM_CALLV(0x802D1A4Cu, 0x802C6CE0u, 0);
        FB(1, LF(R(29))); FB(0, LF(f + 12)); FB(0, frsp(F(1) + F(0))); stfs(base, R(29), F(0));
        FB(1, LF(R(30))); FB(0, LF(f + 8));  FB(0, frsp(F(1) + F(0))); stfs(base, R(30), F(0));
    } else {
        FB(0, LF(R(3) + 64)); stfs(base, R(4), F(0));
        FB(0, LF(R(3) + 68)); stfs(base, R(5), F(0));
    }
    R(0) = lr;
}
/* (remove entry r4 of the array at +220 (count +228): its vfunc +12 told (0x10003), the rest
   moved down; the entry, or 0 when out of range) */
static void array_remove(GM_CTX) {
    GM_FN(0x802585C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(29) = R(4); R(28) = R(3);
    R(0) = gm_u32(R(3) + 228);
    if (cmpu(ctx, R(4), R(0)) >= 0) { R(3) = 0; goto out; }
    R(5) = gm_u32(R(3) + 220);
    R(31) = R(4) << 2;
    R(3) = 0x10000u;
    R(6) = R(28);
    R(30) = gm_u32(R(5) + R(31));
    R(4) = R(3) + 3;
    R(5) = 0;
    R(12) = gm_u32(R(30));
    R(3) = R(30);
    R(12) = gm_u32(R(12) + 12); ctx->ctr = R(12);
    GM_CALLV(0x80258620u, R(12), 0);
    for (;;) {
        R(3) = gm_u32(R(28) + 228);
        R(0) = R(3) - 1;
        if (cmpu(ctx, R(29), R(0)) >= 0) break;
        GM_LOOP();
        R(0) = gm_u32(R(28) + 220);
        R(29) = R(29) + 1;
        R(3) = R(0) + R(31);
        R(31) = R(31) + 4;
        R(0) = gm_u32(R(3) + 4);
        gm_set_u32(R(3), R(0));
    }
    gm_set_u32(R(28) + 228, R(0));
    R(3) = R(30);
out:
    R(0) = lr;
}

/* (a pane's offset by its origin (+4: 1 as is, 0 shifted by half the size +8 / +12, y negated)) */
static void pane_origin_ofs(GM_CTX) {
    R(0) = gm_u32(R(3) + 4);
    if (cmps(ctx, (int32_t)R(0), 1) == 0) { stfs(base, R(4), F(1)); stfs(base, R(5), F(2)); return; }
    if (cmps(ctx, (int32_t)R(0), 0) != 0) return;
    FB(3, LF(R(2) - 15544));
    FB(0, LF(R(3) + 8)); FB(0, frsp(F(3) * F(0))); FB(0, frsp(F(1) + F(0)));
    stfs(base, R(4), F(0));
    FB(0, LF(R(3) + 12)); FB(0, frsp(F(3) * F(0))); FB(0, frsp(F(2) - F(0)));
    ctx->f[0].u ^= 0x8000000000000000ull;                                     /* (fneg: ps0 only) */
    stfs(base, R(5), F(0));
}
/* (a pane's global matrix, recalculated when it or a parent is dirty; the address of +88) */
static void pane_global_mtx(GM_CTX) {
    GM_FN(0x802D17C0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x802D17D8u, 0x802D1820u, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        R(3) = R(31);
        GM_CALLV(0x802D17E8u, 0x802D12E0u, 0);
        R(0) = gm_u16(R(31) + 52);
        FB(1, LF(R(2) - 15116)); FB(0, LF(R(2) - 15120));
        R(0) = R(0) & 0xFFFE;
        stfs(base, R(31) + 104, F(1)); stfs(base, R(31) + 108, F(0));
        gm_set_u16(R(31) + 52, (uint16_t)R(0));
    }
    R(3) = R(31) + 88;
    R(0) = lr;
}
/* (a shape's primitive display list (PPCSync first when r4), its size from the table at
   0x802F84D0 by its +12 byte) */
static void shp_dl_call(GM_CTX) {
    GM_FN(0x8023C950); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(4), 0);
    R(31) = R(3);
    if (c != 0) GM_CALLV(0x8023C970u, 0x801A9B90u, 0);                       /* PPCSync */
    R(3) = gm_u32(R(31));
    R(4) = 0x80300000u - 31536;
    R(5) = gm_u8(R(3) + 12);
    R(3) = R(3) + 32;
    R(0) = (R(5) - 1) << 2;
    R(4) = gm_u32(R(4) + R(0));
    GM_CALLV(0x8023C994u, 0x801C95E0u, 0);                                   /* GXCallDisplayList */
    R(0) = lr;
}
/* (with interrupts off: a voice's +254 set and its update flag (+4 bit 23)) */
static void voice_set_254(GM_CTX) {
    GM_FN(0x80262840); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(4); R(30) = R(3);
    GM_CALLV(0x80262860u, 0x801B1140u, 0);                                   /* OSDisableInterrupts */
    R(4) = gm_u32(R(30));
    if (cmps(ctx, (int32_t)R(4), 0) == 0) GM_CALLV(0x80262870u, 0x801B1180u, 0);
    else {
        gm_set_u16(R(4) + 254, (uint16_t)R(31));
        R(0) = gm_u32(R(30) + 4) | 0x800000u;
        gm_set_u32(R(30) + 4, R(0));
        GM_CALLV(0x80262888u, 0x801B1180u, 0);                               /* OSRestoreInterrupts */
    }
    R(0) = lr;
}
/* strncmp (MSL) */
static void msl_strncmp(GM_CTX) {
    R(3) = R(3) - 1; R(4) = R(4) - 1; R(6) = R(5) + 1;
    for (;;) {
        { uint32_t a_ = R(6); R(6) = a_ - 1; ctx->xer_ca = a_ != 0; }
        if (cmps(ctx, (int32_t)R(6), 0) == 0) break;
        GM_LOOP();
        R(3) = R(3) + 1; R(0) = gm_u8(R(3));
        R(4) = R(4) + 1; R(5) = gm_u8(R(4));
        if (cmpu(ctx, R(0), R(5)) != 0) { R(3) = R(0) - R(5); return; }
        if (cmps(ctx, (int32_t)R(0), 0) == 0) break;
    }
    R(3) = 0;
}
/* (the fog colour / parameters of slot r4 (0..31) or the default) */
static void fog_get(GM_CTX) {
    GM_FN(0x80258C80); GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    int c = cmps(ctx, (int32_t)R(4), 0);
    R(5) = R(3);
    if (c >= 0 && cmps(ctx, (int32_t)R(4), 32) < 0) {
        R(0) = (uint32_t)((int32_t)R(4) * 48);
        R(3) = f + 12;
        R(4) = R(5) + R(0) + 8824;
        GM_CALLV(0x80258CB4u, 0x8025F2B0u, 0);
    } else {
        R(3) = f + 8; R(4) = 0;
        GM_CALLV(0x80258CC8u, 0x8025F2B0u, 0);
    }
    R(3) = gm_u32(R(3));
    R(0) = lr;
}
/* ScnObj::SetMtx(type, mtx): types 0..2 (+12 + 48 type), identity when null; type 0 keeps +204's
   bit 31 (identity world) */
static void scnobj_set_mtx(GM_CTX) {
    GM_FN(0x802574E0); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmpu(ctx, R(4), 3);
    R(6) = R(3);
    if (c >= 0) { R(3) = 0; goto out; }
    if (cmps(ctx, (int32_t)R(5), 0) != 0) {
        if (cmps(ctx, (int32_t)R(4), 0) == 0) { R(0) = gm_u32(R(3) + 204) & 0x7FFFFFFFu; gm_set_u32(R(3) + 204, R(0)); }
        R(0) = (uint32_t)((int32_t)R(4) * 48);
        R(3) = R(5);
        R(4) = R(6) + R(0) + 12;
        GM_CALLV(0x80257528u, 0x801C0500u, 0);                               /* PSMTXCopy */
    } else {
        if (cmps(ctx, (int32_t)R(4), 0) == 0) { R(0) = gm_u32(R(3) + 204) | 0x80000000u; gm_set_u32(R(3) + 204, R(0)); }
        R(0) = (uint32_t)((int32_t)R(4) * 48);
        R(3) = R(3) + R(0) + 12;
        GM_CALLV(0x80257550u, 0x801C04D0u, 0);                               /* PSMTXIdentity */
    }
    R(3) = 1;
out:
    R(0) = lr;
}
/* (GetScnObjOption chain: option `opt` reads its bit into *r5; others to the parent's) */
static void scn_get_option(GM_CTX, uint32_t opt, uint32_t off, int kind, uint32_t parent) {
    if (cmps(ctx, (int32_t)R(5), 0) == 0) { R(3) = 0; return; }
    R(0) = R(4) - opt;
    if (cmpu(ctx, R(0), 1) != 0) { GM_TAIL(parent, 0); return; }
    R(0) = gm_u32(R(3) + off);
    if (kind == 0) R(0) = (R(0) >> 8) & 1;                                    /* (bit 8 set) */
    else { R(0) = R(0) & 2; R(0) = cntlzw(R(0)); R(0) = R(0) >> 5; }          /* (bit 1 clear) */
    gm_set_u32(R(5), R(0));
    R(3) = 1;
}
/* (take the lock (0x803DA0D8 + 4) and, when the resource is busy (its first byte), wait for it
   (yielding) and keep the lock: 1; else unlock: 0) */
static void lock_wait(GM_CTX) {
    GM_FN(0x8022B310); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = 0x803E0000u;
    R(31) = R(30) - 24360;
    R(3) = R(31) + 4;
    GM_CALLV(0x8022B334u, 0x801B2E60u, 0);                                   /* OSLockMutex */
    R(0) = gm_u8(R(30) - 24360);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {
        for (;;) {
            GM_CALLV(0x8022B34Cu, 0x801AC810u, 0);
            if (cmps(ctx, (int32_t)R(3), 0) == 0) break;
            GM_LOOP();
            GM_CALLV(0x8022B348u, 0x801B50F0u, 0);                           /* OSYieldThread */
        }
        R(3) = 1;
    } else {
        R(3) = R(31) + 4;
        GM_CALLV(0x8022B364u, 0x801B2F40u, 0);                               /* OSUnlockMutex */
        R(3) = 0;
    }
    R(0) = lr;
}
/* (a frame wrapped into [start f1, end f2): fmod by the length, negative ones moved up) */
static void frame_wrap(GM_CTX) {
    GM_FN(0x80249BF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    FB(0, LF(R(2) - 18984));
    FB(31, frsp(F(2) - F(1)));
    cr_fcmp(ctx, 0, F(3), F(0));
    CR_SETBIT(ctx, 2, (CR_BIT(ctx, 1) | CR_BIT(ctx, 2)));
    if (CR_BIT(ctx, 2)) {
        ctx->f[1].u = ctx->f[3].u; ctx->f[2].u = ctx->f[31].u;
        GM_CALLV(0x80249C24u, 0x802E8614u, 0);                               /* fmod */
        ctx->f[1].d = frsp(F(1));
    } else {
        ctx->f[2].u = ctx->f[31].u;
        FB(1, frsp(F(3) + F(31)));
        GM_CALLV(0x80249C38u, 0x802E8614u, 0);
        ctx->f[1].d = frsp(F(1));
        FB(0, LF(R(2) - 18984));
        ctx->f[0].d = (F(1) >= 0.0) ? F(0) : F(31);                           /* (fsel) */
        FB(1, frsp(F(1) + F(0)));
    }
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_G3D_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_G3D_COUNT)   /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(GetResNode__Q34nw4r3g3d6ResMdlCFi, 4)  { dic_entry(GM_PASS, 20); }                /* ResMdl::GetResNode(int) */
E(GetResNode__Q34nw4r3g3d6ResMdlCFUl, 4) { dic_entry(GM_PASS, 20); }                /* ResMdl::GetResNode(u32) */
E(fn_8023B800, 4) { dic_entry(GM_PASS, 48); }                                       /* ResMdl::GetResMat(int) */
E(GetResMat__Q34nw4r3g3d6ResMdlCFUl, 4) { dic_entry(GM_PASS, 48); }                 /* ResMdl::GetResMat(u32) */
E(fn_8023B950, 4) { dic_entry(GM_PASS, 56); }                                       /* ResMdl::GetResShp(u32) */
E(GetResNodeNumEntries__Q34nw4r3g3d6ResMdlCFv, 4) {                                 /* ResMdl::GetResNodeNumEntries */
    R(3) = gm_u32(R(3));
    R(0) = gm_u32(R(3) + 20);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(3) = 0; else R(3) = R(3) + R(0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; return; }
    R(3) = gm_u32(R(3) + 4);
}
E(fn_8023CC60, 4) {                                                                 /* (a material's texture SRT r4: +4 + 32 * r4) */
    R(3) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(3), 0) == 0 || cmpu(ctx, R(4), 7) > 0) { R(3) = 0; return; }
    R(0) = R(4) << 5;
    R(3) = R(3) + R(0);
    R(3) = R(3) + 4;
}
E(fn_8023CCC0, 4) { flag_bit(GM_PASS); }                                            /* (a texture-SRT flag) */
E(fn_8023CDF0, 4) { flag_bit(GM_PASS); }                                            /* (another flag word, same shape) */
E(fn_8023D1B0, 4) {                                                                 /* (per-stage bytes +3 / +7 into *r5 / *r6) */
    R(7) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(7), 0) == 0) return;
    R(0) = R(4) - 1;
    if (cmpu(ctx, R(0), 2) > 0) return;
    if (cmps(ctx, (int32_t)R(5), 0) != 0) { R(3) = R(4) + R(7); R(0) = gm_u8(R(3) + 3); gm_set_u32(R(5), R(0)); }
    if (cmps(ctx, (int32_t)R(6), 0) == 0) return;
    R(3) = R(4) + R(7); R(0) = gm_u8(R(3) + 7); gm_set_u8(R(6), (uint8_t)R(0));
}
E(fn_8023E370, 4) {                                                                 /* (the data's +52 block, null if none) */
    R(3) = gm_u32(R(3));
    R(0) = gm_u32(R(3) + 52);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) { R(3) = 0; return; }
    R(3) = R(3) + R(0);
}
E(fn_802380D0, 48) {                                                                /* (a 3x4 matrix copy, paired singles) */
    for (int i = 0; i < 6; i++) psq_l(ctx, base, i, R(4) + 8 * i, 0, 0);
    static const uint8_t off[6] = { 0, 8, 12, 20, 24, 32 };
    for (int i = 0; i < 6; i++) psq_st(ctx, base, i, R(3) + off[i], i & 1, 0);
}
E(SinFIdx__Q24nw4r4mathFf, 4) { sin_fidx(GM_PASS); }                                /* nw4r::math::SinFIdx */
E(fn_8025F2B0, 4) { gm_set_u32(R(3), R(4)); }                                       /* (a setter: *this = r4) */
E(fn_8025F0C0, 4) { obj_callback(GM_PASS); }
E(fn_8024A2D0, 4) { texcoord_entry(GM_PASS); }
E(fn_80249D60, 4) { bp_texcoord_scale(GM_PASS); }
E(fn_8024A150, 4) { load_texmtx33(GM_PASS); }
E(fn_802492E0, 4) { anm_chr_result(GM_PASS); }
E(fn_8024D0B0, 4) { set_vtx_arrays(GM_PASS); }
E(fn_8023C6F0, 4) {                                                                /* (a material's display list: call it / into the FIFO) */
    R(3) = gm_u32(R(3));
    int c = cmps(ctx, (int32_t)R(4), 0);
    R(4) = R(3) + 36;
    if (c != 0) { R(3) = dl_ptr(GM_PASS, R(4)); R(4) = gm_u32(R(4) + 4); GM_TAIL(0x801C95E0u, 0); return; }
    R(5) = dl_ptr(GM_PASS, R(4));
    R(4) = gm_u32(R(4) + 4);
    R(3) = 0xCC010000u; R(0) = 64;
    dl_fifo(GM_PASS, R(5), R(4));
}
E(fn_8023C610, 4) {                                                                /* (a shape's display list: r5 skip the first 32 bytes, r4 call / FIFO) */
    R(3) = gm_u32(R(3));
    int c5 = cmps(ctx, (int32_t)R(5), 0);
    R(5) = R(3) + 24;
    if (c5 != 0) {
        if (cmps(ctx, (int32_t)R(4), 0) != 0) {
            R(3) = dl_ptr(GM_PASS, R(5)); R(4) = gm_u32(R(5) + 4);
            R(3) = R(3) + 32; R(4) = R(4) - 32;
            GM_TAIL(0x801C95E0u, 0); return;
        }
        R(6) = dl_ptr(GM_PASS, R(5));
        R(5) = gm_u32(R(5) + 4);
        R(3) = 0xCC010000u; R(4) = 64;
        R(0) = R(6) + 32;
        st8(base, 0xCC008000u, 64);
        R(4) = R(5) - 32;
        st32(base, 0xCC008000u, R(0)); st32(base, 0xCC008000u, R(4));
        return;
    }
    if (cmps(ctx, (int32_t)R(4), 0) != 0) {
        R(3) = dl_ptr(GM_PASS, R(5)); R(4) = gm_u32(R(5) + 4);
        GM_TAIL(0x801C95E0u, 0); return;
    }
    R(4) = dl_ptr(GM_PASS, R(5));
    R(5) = gm_u32(R(5) + 4);
    R(3) = 0xCC010000u; R(0) = 64;
    dl_fifo(GM_PASS, R(4), R(5));
}
E(fn_80260860, 4) {                                                                /* (a function-static object: constructed once, its address) */
    GM_FN(0x80260860); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(0) = (uint32_t)(int8_t)gm_u8(R(13) - 18836);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(31) = 0x80400000u;
        R(3) = R(31) - 14320;
        GM_CALLV(0x80260888u, 0x802605D0u, 0);
        R(4) = 0x80260000u + 2256; R(5) = 0x80400000u - 14336;
        R(3) = R(31) - 14320;
        GM_CALLV(0x802608A0u, 0x802DC780u, 0);                               /* __register_global_object */
        R(0) = 1;
        gm_set_u8(R(13) - 18836, 1);
    }
    R(3) = 0x80400000u - 14320;
    R(0) = lr;
}
E(GetAnmResult__Q34nw4r3g3d9ResAnmChrCFPQ34nw4r3g3d12ChrAnmResultUlf, 4) { anm_chr_get_result(GM_PASS); }   /* ResAnmChr::GetAnmResult */
E(fn_802292C0, 4) {                                                                /* (read a u16 from a stream pointer, advance it) */
    R(5) = gm_u32(R(3)); R(6) = R(3); R(4) = gm_u32(R(3));
    R(3) = gm_u16(R(5)); R(0) = R(4) + 2; gm_set_u32(R(6), R(0));
}
E(fn_8024D220, 4) { mtx_cache_set(GM_PASS); }
E(fn_8025F330, 4) {                                                                /* (copy *src's 48-byte matrix to dst; null if either is) */
    if (cmps(ctx, (int32_t)R(4), 0) == 0) { R(3) = 0; return; }
    R(5) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(5), 0) == 0) { R(3) = 0; return; }
    ctx->f[0].u = ld64(base, R(5)); R(3) = R(4); st64(base, R(4), ctx->f[0].u);
    for (int i = 8; i < 48; i += 8) { ctx->f[0].u = ld64(base, R(5) + i); st64(base, R(4) + i, ctx->f[0].u); }
}
E(fn_802596E0, 4) {                                                                /* (a sort compare: by +208, then by the float +152) */
    R(0) = gm_u8(R(3) + 208); R(5) = gm_u8(R(4) + 208);
    if (cmps(ctx, (int32_t)R(0), (int32_t)R(5)) == 0) {
        FB(1, LF(R(3) + 152)); FB(0, LF(R(4) + 152));
        cr_fcmp(ctx, 0, F(1), F(0));
        R(3) = ctx->cr; R(3) = (R(3) >> 30) & 1;                               /* (mfcr: gt) */
        return;
    }
    R(0) = R(5) ^ R(0);
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && ((uint32_t)v_ & 1u) != 0; R(3) = (uint32_t)(v_ >> 1); }
    R(0) = R(0) & R(5);
    R(0) = R(3) - R(0);
    R(3) = R(0) >> 31;
}
E(__ct__Q34nw4r3g3d6CameraFPQ34nw4r3g3d10CameraData, 4) { gm_set_u32(R(3), R(4)); }   /* Camera::Camera(data) */
E(fn_80239980, 4) {                                                                /* (a BP command into a buffer: 0x61, the register's 4 bytes) */
    R(6) = (R(4) >> 24) & 0xFF; R(5) = (R(4) >> 16) & 0xFF; R(0) = (R(4) >> 8) & 0xFF;
    R(7) = 97;
    gm_set_u8(R(3), 97); gm_set_u8(R(3) + 1, (uint8_t)R(6)); gm_set_u8(R(3) + 2, (uint8_t)R(5));
    gm_set_u8(R(3) + 3, (uint8_t)R(0)); gm_set_u8(R(3) + 4, (uint8_t)R(4));
}
E(fn_8025EBB0, 4) {                                                                /* (is the object of one of five type infos) */
    static const uint16_t t[4] = { 28688, 28712, 28760, 28776 };
    for (int i = 0; i < 4; i++) {
        R(3) = 0x80300000u;
        if (i < 2) R(0) = gm_u32(R(4));
        R(3) = R(3) - t[i];
        if (cmpu(ctx, R(0), R(3)) == 0) { R(3) = 1; return; }
    }
    R(3) = 0x80300000u; R(3) = R(3) - 30992;
    R(0) = R(3) - R(0);
    R(0) = cntlzw(R(0));
    R(3) = R(0) >> 5;
}
E(fn_8024A0D0, 4) {                                                                /* (an XF block of two texture-coordinate generator words) */
    R(5) = 0xCC010000u; R(0) = 16;
    st8(base, R(5) - 32768, 16);
    R(4) = 1;
    R(7) = gm_u32(R(3)); R(0) = 4120; R(8) = gm_u32(R(3) + 8);
    st16(base, R(5) - 32768, 1);
    R(7) = R(7) << 6;
    R(6) = gm_u32(R(3) + 4);
    R(8) = R(8) << 18;
    R(9) = gm_u32(R(3) + 12);
    R(4) = R(6) << 12;
    R(6) = gm_u32(R(3) + 24);
    R(7) = R(7) | R(4);
    R(4) = gm_u32(R(3) + 20);
    R(8) = R(8) | R(7);
    R(7) = gm_u32(R(3) + 28);
    st16(base, R(5) - 32768, (uint16_t)R(0));
    R(9) = R(9) << 24;
    R(0) = R(4) << 6;
    R(3) = gm_u32(R(3) + 16);
    R(8) = R(9) | R(8);
    st32(base, R(5) - 32768, R(8));
    R(0) = R(3) | R(0);
    R(4) = R(6) << 12;
    R(3) = R(7) << 18;
    R(0) = R(4) | R(0);
    R(0) = R(3) | R(0);
    st32(base, R(5) - 32768, R(0));
}
E(fn_80238200, 48) { mtx_trans_local(GM_PASS); }
E(fn_8025BF30, 4) {                                                                /* (this frame's matrix buffer: +244 + index * align32(n * 48)) */
    R(0) = gm_u16(R(3) + 258); R(5) = gm_u8(R(3) + 257);
    R(4) = (uint32_t)((int32_t)R(0) * 48);
    R(3) = gm_u32(R(3) + 244);
    R(0) = R(4) + 31; R(0) = R(0) & 0xFFFFFFE0u;
    R(0) = (uint32_t)((int32_t)R(5) * (int32_t)R(0));
    R(3) = R(3) + R(0);
}
E(fn_8025BF60, 4) {                                                                /* (... +248, 36-byte matrices; null if none) */
    R(5) = gm_u32(R(3) + 248);
    if (cmps(ctx, (int32_t)R(5), 0) == 0) { R(3) = 0; return; }
    R(0) = gm_u16(R(3) + 258); R(4) = gm_u8(R(3) + 257);
    R(3) = (uint32_t)((int32_t)R(0) * 36);
    R(0) = R(3) + 31; R(0) = R(0) & 0xFFFFFFE0u;
    R(0) = (uint32_t)((int32_t)R(4) * (int32_t)R(0));
    R(3) = R(5) + R(0);
}
E(fn_8025BFA0, 4) {                                                                /* (... +252, 48-byte matrices; null if none) */
    R(5) = gm_u32(R(3) + 252);
    if (cmps(ctx, (int32_t)R(5), 0) == 0) { R(3) = 0; return; }
    R(0) = gm_u16(R(3) + 258); R(4) = gm_u8(R(3) + 257);
    R(3) = (uint32_t)((int32_t)R(0) * 48);
    R(0) = R(3) + 31; R(0) = R(0) & 0xFFFFFFE0u;
    R(0) = (uint32_t)((int32_t)R(4) * (int32_t)R(0));
    R(3) = R(5) + R(0);
}
E(fn_8024D3C0, 4) { g3d_state_fwd(GM_PASS); }
E(fn_8022B3D0, 4) { GM_TAIL(0x801AC740u, 0); }                                     /* (a tail call) */
E(fn_8023D150, 4) {                                                                /* (byte +1 as s8, -1 if none) */
    R(3) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = (uint32_t)-1; return; }
    R(3) = (uint32_t)(int8_t)gm_u8(R(3) + 1);
}
E(fn_8023D190, 4) {                                                                /* (byte +2 as s8, -1 if none) */
    R(3) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = (uint32_t)-1; return; }
    R(3) = (uint32_t)(int8_t)gm_u8(R(3) + 2);
}
E(fn_8023D100, 4) {                                                                /* (byte +0, 0 if none) */
    R(3) = gm_u32(R(3));
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; return; }
    R(3) = gm_u8(R(3));
}
E(fn_8023D5B0, 4) {                                                                /* (a 64-byte display list unless r4 is null) */
    if (cmps(ctx, (int32_t)R(4), 0) == 0) return;
    int c = cmps(ctx, (int32_t)R(5), 0);
    R(3) = gm_u32(R(3));
    if (c != 0) { R(4) = 64; GM_TAIL(0x801C95E0u, 0); return; }
    R(4) = 0xCC010000u; R(0) = 64;
    st8(base, 0xCC008000u, 64); st32(base, 0xCC008000u, R(3)); st32(base, 0xCC008000u, 64);
}
E(fn_8023CB30, 4) { dl_fixed(GM_PASS, 128); }                                      /* (a 128-byte display list) */
E(fn_8023CB00, 4) { dl_fixed(GM_PASS, 32); }                                       /* (a 32-byte display list) */
E(fn_8024C8D0, 4) { tex_state_flush(GM_PASS); }
E(fn_802610B0, 4) { R(3) = gm_u32(R(3)); }                                         /* (a getter: *this) */
E(fn_8023E350, 4) {                                                                /* (the data's +40 block, null if none) */
    R(3) = gm_u32(R(3));
    R(0) = gm_u32(R(3) + 40);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) { R(3) = 0; return; }
    R(3) = R(3) + R(0);
}
E(fn_80265FA0, 4) { R(0) = R(4) << 2; R(3) = R(3) + R(0); FB(1, LF(R(3) + 64)); }  /* (float r4 of the array at +64) */
E(fn_8024B6B0, 4) { zcomp_loc(GM_PASS); }
E(fn_802381A0, 48) { mtx_scale_cols(GM_PASS); }
E(fn_8022BE10, 4) { split_result(GM_PASS); }
E(GetCameraMtx__Q34nw4r3g3d6CameraCFPQ34nw4r4math5MTX34, 4) { camera_mtx(GM_PASS); }   /* Camera::GetCameraMtx */
E(fn_802384F0, 64) {                                                               /* (a 4x4 matrix copy, paired singles) */
    for (int i = 0; i < 8; i++) psq_l(ctx, base, i, R(4) + 8 * i, 0, 0);
    for (int i = 0; i < 8; i++) psq_st(ctx, base, i, R(3) + 8 * i, 0, 0);
}
E(CosFIdx__Q24nw4r4mathFf, 4) { cos_fidx(GM_PASS); }                                /* nw4r::math::CosFIdx */
E(fn_80270330, 4) {                                                                /* (if not busy: take the pending (+12, else +16) and clear both) */
    R(0) = gm_u8(R(3) + 5);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) return;
    R(4) = gm_u32(R(3) + 12);
    if (cmps(ctx, (int32_t)R(4), 0) == 0) R(4) = gm_u32(R(3) + 16);
    R(0) = 0;
    gm_set_u32(R(3) + 12, 0); gm_set_u32(R(3) + 16, 0);
    GM_TAIL(0x80270370u, 0);
}
E(fn_80259720, 4) {                                                                /* (a sort compare: by +209, then the float +152) */
    R(0) = gm_u8(R(3) + 209); R(5) = gm_u8(R(4) + 209);
    if (cmps(ctx, (int32_t)R(0), (int32_t)R(5)) == 0) {
        FB(1, LF(R(3) + 152)); FB(0, LF(R(4) + 152));
        cr_fcmp(ctx, 0, F(1), F(0));
        R(3) = ctx->cr; R(3) = R(3) >> 31;                                     /* (mfcr: lt) */
        return;
    }
    R(0) = R(5) ^ R(0);
    { int32_t v_ = (int32_t)R(0); ctx->xer_ca = v_ < 0 && ((uint32_t)v_ & 1u) != 0; R(3) = (uint32_t)(v_ >> 1); }
    R(0) = R(0) & R(5);
    R(0) = R(3) - R(0);
    R(3) = R(0) >> 31;
}
E(GetResMatNumEntries__Q34nw4r3g3d6ResMdlCFv, 4) {                                  /* ResMdl::GetResMatNumEntries */
    R(3) = gm_u32(R(3));
    R(0) = gm_u32(R(3) + 48);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(3) = 0; else R(3) = R(3) + R(0);
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; return; }
    R(3) = gm_u32(R(3) + 4);
}
E(fn_802542C0, 4) { camera_proj_texmtx(GM_PASS); }
E(fn_80257870, 4) { scn_option(GM_PASS, 0x10000u, 204, 0x60, 1, 0x80257270u); }  /* (SetScnObjOption: 0x10001) */
E(fn_8025B3A0, 4) { scn_option(GM_PASS, 0x20000u, 204, 0x100, 1, 0x80257870u); } /* (... 0x20001) */
E(fn_8025DFE0, 4) { scn_option(GM_PASS, 0x30000u, 316, 0x2, 0, 0x8025B3A0u); }   /* (... 0x30001: bit 1 cleared on true) */
E(ChangeColorUpdate__Fb, 4) { GM_FN(0x802D2F20); change_update(GM_PASS, 0x802D2F50u, 0x801C8E10u, 12); }   /* (GXSetColorUpdate) */
E(ChangeAlphaUpdate__Fb, 4) { GM_FN(0x802D2F80); change_update(GM_PASS, 0x802D2FB0u, 0x801C8E40u, 13); }   /* (GXSetAlphaUpdate) */
E(fn_8027B5F0, 4) { static_queue_obj(GM_PASS); }
E(fn_802E8868, 4) { GM_TAIL(0x802E8620u, 0); }                                     /* (sqrt: the libm body) */
GM_HLE(sqrt__Q23EGG7Math_f_Ff) { egg_sqrt(GM_PASS); }   /* EGG::Math<float>::sqrt - off: its symbol (with "<f>") has no hle_funcs.txt name */
E(fn_802413E0, 4) { node_srt(GM_PASS); }
E(fn_802ABE90, 4) { list_call28(GM_PASS); }
E(fn_802ABE00, 4) { list_call32(GM_PASS); }
E(fn_802CC9F0, 4) { quad_color(GM_PASS); }
E(fn_8024BEC0, 4) { tc_scale_then(GM_PASS, 0x8023CB00u, 0); }
E(fn_8024BF70, 4) { tc_scale_then(GM_PASS, 0x8023CB30u, 0); }
E(fn_8024C020, 4) { tc_scale_then(GM_PASS, 0x8023D5B0u, 1); }
E(fn_8024D2C0, 4) { fog_set(GM_PASS); }
E(fn_80241BE0, 4) {                                                                /* (set the translation (r4); the identity-translation flags in +0) */
    FB(1, LF(R(2) - 19176));
    FB(0, LF(R(4)));
    cr_fcmp(ctx, 0, F(1), F(0));
    int zero = CR_BIT(ctx, 2);
    if (zero) { FB(0, LF(R(4) + 4)); cr_fcmp(ctx, 0, F(1), F(0)); zero = CR_BIT(ctx, 2); }
    if (zero) { FB(0, LF(R(4) + 8)); cr_fcmp(ctx, 0, F(1), F(0)); zero = CR_BIT(ctx, 2); }
    if (zero) {
        R(5) = gm_u32(R(3));
        R(6) = 64;
        R(0) = R(5) & 0x20;
        if (cmps(ctx, (int32_t)R(0), 0) != 0) {
            R(0) = R(5) & 8;
            int c = cmps(ctx, (int32_t)R(0), 0);
            R(6) = R(6) | 4;
            if (c != 0) R(6) = R(6) | 2;
        }
        R(0) = gm_u32(R(3)) | R(6);
        gm_set_u32(R(3), R(0));
    } else {
        R(5) = gm_u32(R(3));
        R(0) = (uint32_t)-71;
        R(0) = R(5) & R(0);
        gm_set_u32(R(3), R(0));
    }
    FB(2, LF(R(4))); FB(1, LF(R(4) + 4)); FB(0, LF(R(4) + 8));
    stfs(base, R(3) + 40, F(2)); stfs(base, R(3) + 56, F(1)); stfs(base, R(3) + 72, F(0));
}
E(fn_802BA5C0, 4) { find_by_8(GM_PASS); }
E(fn_802838A0, 4) { clamp_lookup(GM_PASS); }
E(fn_802B4960, 4) { list_call32b(GM_PASS); }
E(fn_80281790, 4) {                                                                /* (set channel r4's float at +212 (min-clamped); mark +162 bit 4 when it changes) */
    FB(0, LF(R(2) - 17780));
    cr_fcmp(ctx, 0, F(1), F(0));
    if (CR_BIT(ctx, 0)) ctx->f[1].u = ctx->f[0].u;
    R(0) = R(4) << 2;
    R(4) = R(3) + R(0);
    FB(0, LF(R(4) + 212));
    cr_fcmp(ctx, 0, F(1), F(0));
    if (CR_BIT(ctx, 2)) return;
    stfs(base, R(4) + 212, F(1));
    R(0) = gm_u16(R(3) + 162) | 0x10;
    gm_set_u16(R(3) + 162, (uint16_t)R(0));
}
E(strcmp, 4) { msl_strcmp(GM_PASS); }                                              /* strcmp (MSL) */
E(memcmp__FPCvPCvUi, 4) { msl_memcmp(GM_PASS); }                                    /* memcmp (MSL) */
E(fn_802D3230, 4) { GM_FN(0x802D3230); gx_then_dirty(GM_PASS, 0x802D3240u, 0x801C9C60u, 4); }   /* (GXSetScissor) */
E(fn_802D3200, 4) { GM_FN(0x802D3200); gx_then_dirty(GM_PASS, 0x802D3210u, 0x801C9C10u, 2); }   /* (GXSetViewport) */
E(fn_802D31D0, 4) { GM_FN(0x802D31D0); gx_then_dirty(GM_PASS, 0x802D31E0u, 0x801C98B0u, 1); }   /* (GXSetProjectionv) */
E(fn_802D2FE0, 4) { GM_FN(0x802D2FE0); change_update(GM_PASS, 0x802D3010u, 0x801C8F90u, 14); }  /* ChangeDither (GXSetDither) */
E(fn_802D1820, 4) {                                                                /* (is this pane or a parent (+60) flagged (+52 bit 0)) */
    for (;;) {
        R(0) = gm_u16(R(3) + 52) & 1;
        if (cmps(ctx, (int32_t)R(0), 0) != 0) { R(3) = 1; return; }
        R(3) = gm_u32(R(3) + 60);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; return; }
        GM_LOOP();
    }
}
E(fn_802C0B40, 4) {                                                                /* mTexture_c (set the image (r4, when not null), clear bit 1 of +8) */
    if (cmps(ctx, (int32_t)R(4), 0) != 0) gm_set_u32(R(3) + 16, R(4));
    R(0) = gm_u8(R(3) + 8) & 0xFD;
    cmps(ctx, (int32_t)R(0), 0);
    gm_set_u8(R(3) + 8, (uint8_t)R(0));
}
E(load__10mTexture_cFUi, 4) { mtex_load(GM_PASS); }                                /* mTexture_c::load */
E(fn_802C0BA0, 4) { mtex_init_obj(GM_PASS); }
E(fn_80286630, 4) { R(3) = 0x80410000u + 28884; }                                   /* (a static object's address) */
E(fn_80265F60, 4) { R(0) = R(4) << 2; R(3) = R(3) + R(0); FB(1, LF(R(3) + 52)); }   /* (float r4 of the array at +52) */
E(fn_8022B380, 4) { wait_unlock(GM_PASS); }
E(fn_80281750, 4) {                                                                /* (as 0x80281790, the float at +200) */
    FB(0, LF(R(2) - 17780));
    cr_fcmp(ctx, 0, F(1), F(0));
    if (CR_BIT(ctx, 0)) ctx->f[1].u = ctx->f[0].u;
    R(0) = R(4) << 2;
    R(4) = R(3) + R(0);
    FB(0, LF(R(4) + 200));
    cr_fcmp(ctx, 0, F(1), F(0));
    if (CR_BIT(ctx, 2)) return;
    stfs(base, R(4) + 200, F(1));
    R(0) = gm_u16(R(3) + 162) | 0x10;
    gm_set_u16(R(3) + 162, (uint16_t)R(0));
}
E(fn_80283760, 4) { clamp_lookup2(GM_PASS); }
E(fn_8026C210, 4) { snd_pos(GM_PASS); }
E(fn_80277870, 4) { list_obj_dtor(GM_PASS); }
E(fn_802C9C00, 4) {                                                                /* (copy the position / colour at +32..+47 to +108..+123) */
    FB(2, LF(R(3) + 32)); FB(1, LF(R(3) + 36)); FB(0, LF(R(3) + 40));
    R(6) = gm_u8(R(3) + 44); R(5) = gm_u8(R(3) + 45); R(4) = gm_u8(R(3) + 46); R(0) = gm_u8(R(3) + 47);
    stfs(base, R(3) + 108, F(2)); stfs(base, R(3) + 112, F(1)); stfs(base, R(3) + 116, F(0));
    gm_set_u8(R(3) + 120, (uint8_t)R(6)); gm_set_u8(R(3) + 121, (uint8_t)R(5));
    gm_set_u8(R(3) + 122, (uint8_t)R(4)); gm_set_u8(R(3) + 123, (uint8_t)R(0));
}
E(fn_802BE6B0, 4) { egg_normalise(GM_PASS); }
E(fn_802ABD60, 4) { list_call24(GM_PASS); }
E(fn_80270370, 4) { sound_state(GM_PASS); }
E(__kernel_sin, 4) { k_sin(GM_PASS); }                                              /* __kernel_sin (MSL / fdlibm) */
E(__kernel_cos, 4) { k_cos(GM_PASS); }                                              /* __kernel_cos */
E(sin, 4) { GM_FN(0x802E84C4); trig(GM_PASS, 0, 0x802E84C4u); }                     /* sin */
E(cos, 4) { GM_FN(0x802E7FBC); trig(GM_PASS, 1, 0x802E7FBCu); }                     /* cos */
E(tan, 4) { GM_FN(0x802E8590); trig(GM_PASS, 2, 0x802E8590u); }                     /* tan */
E(__shl2i, 4) {                                                                    /* __shl2i (64-bit shift left: r3:r4 << r5) */
    { uint32_t a_ = R(5); R(8) = 0x20u - a_; ctx->xer_ca = 0x20u >= a_; }
    { uint32_t a_ = R(5); R(9) = a_ + 0xFFFFFFE0u; ctx->xer_ca = R(9) < a_; }
    { uint32_t s_ = R(5) & 63; R(3) = s_ > 31 ? 0 : R(3) << s_; }
    { uint32_t s_ = R(8) & 63; R(10) = s_ > 31 ? 0 : R(4) >> s_; }
    R(3) = R(3) | R(10);
    { uint32_t s_ = R(9) & 63; R(10) = s_ > 31 ? 0 : R(4) << s_; }
    R(3) = R(3) | R(10);
    { uint32_t s_ = R(5) & 63; R(4) = s_ > 31 ? 0 : R(4) << s_; }
}
E(fn_8022C120, 4) { anm_key_lookup(GM_PASS); }
E(fn_8023DDD0, 4) { dl_call_sized(GM_PASS); }
E(fn_802837C0, 4) { clamp_lookup3(GM_PASS); }
E(fn_8024D420, 4) { camera_slot_set(GM_PASS); }
E(fn_80254110, 4) { camera_proj(GM_PASS); }                                         /* Camera::GetProjectionMtx */
E(fn_802541F0, 4) { camera_proj_tex(GM_PASS); }                                     /* Camera::GetProjectionTexMtx */
E(fn_802D19F0, 4) { pane_global_pos(GM_PASS); }
E(fn_802585C0, 4) { array_remove(GM_PASS); }
E(fn_802C6CE0, 4) { pane_origin_ofs(GM_PASS); }
E(fn_802D17C0, 4) { pane_global_mtx(GM_PASS); }
E(fn_8023C950, 4) { shp_dl_call(GM_PASS); }
E(fn_80262840, 4) { voice_set_254(GM_PASS); }
E(strncmp, 4) { msl_strncmp(GM_PASS); }                                            /* strncmp (MSL) */
E(fn_80250DE0, 4) { R(3) = 0x803E0000u + 17664; }                                   /* (a static object's address) */
E(fn_802C3020, 4) {                                                                /* (blend mode preset r3 of the table at 0x802FD0A8) */
    R(4) = 0x80300000u;
    R(0) = R(3) << 4;
    R(4) = R(4) - 12120;
    R(6) = R(4) + R(0);
    R(3) = gm_u32(R(4) + R(0));
    R(4) = gm_u32(R(6) + 4); R(5) = gm_u32(R(6) + 8); R(6) = gm_u32(R(6) + 12);
    GM_TAIL(0x801C8DC0u, 0);                                                       /* GXSetBlendMode */
}
E(fn_8022BC80, 4) { R(3) = gm_u32(R(3) + 20); R(3) = gm_u32(R(3) + 8); R(3) = (uint32_t)(int8_t)gm_u8(R(3) + 2); }   /* (a font's s8 at +20 -> +8 -> +2) */
E(fn_80258C80, 4) { fog_get(GM_PASS); }
E(SetMtx__Q34nw4r3g3d6ScnObjFQ44nw4r3g3d6ScnObj13ScnObjMtxTypePCQ34nw4r4math5MTX34, 4) { scnobj_set_mtx(GM_PASS); }   /* ScnObj::SetMtx */
E(fn_8025B3E0, 4) { scn_get_option(GM_PASS, 0x20000u, 204, 0, 0x802578B0u); }     /* (GetScnObjOption: 0x20001) */
E(fn_8025E020, 4) { scn_get_option(GM_PASS, 0x30000u, 316, 1, 0x8025B3E0u); }     /* (... 0x30001) */
E(fn_8022B310, 4) { lock_wait(GM_PASS); }
E(fmod, 4) { GM_TAIL(0x802E4E5Cu, 0); }                                            /* fmod (-> __ieee754_fmod) */
E(fn_80249BF0, 4) { frame_wrap(GM_PASS); }
E(fn_802460B0, 4) {                                                                /* (entry r4's top two flag bits (+20 table) clear) */
    R(3) = gm_u32(R(3) + 20);
    R(0) = R(4) << 1;
    R(0) = gm_u16(R(3) + R(0)) & 0xC000;
    R(0) = cntlzw(R(0));
    R(3) = R(0) >> 5;
}
E(fn_802C0B30, 4) { R(0) = 1; gm_set_u8(R(3) + 8, 1); }                             /* (mTexture_c: mark +8) */
