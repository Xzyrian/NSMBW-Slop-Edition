/* gm_m3d.c - mLib's 3D model layer (m3d): banm_c / fanm_c (animations), calcRatio_c (animation
 * blending), bmdl_c / smdl_c / mdl_c and its calc-world callback, scnLeaf_c - the wrappers every
 * model in the game goes through to nw4r g3d (which stays recompiled). Track B (gm.h,
 * docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_3d/{banm,bmdl,calc_ratio,fanm,mdl,scn_leaf,
 * smdl}.cpp) and checked against the recompiled USA rev 2 code (0x80168060-0x8016A440; the
 * slices' offsets drift here - matched by code). Not here: m_3d_capture (0x80169220-0x801694B0).
 * The non-volatile registers are mirrored around nested calls (gm_nv.h).
 *
 * scnLeaf_c: +0 vtable, +4 mpScn. bmdl_c: +8 mpAnm. mdl_c: +12 mCallback (mdlCallback_c: +4
 * mCalcRatio (32 bytes: +4 weight, +8 t, +12 time step, +16 scale from, +20 scale to,
 * +24 interpolate t, +28 active, +29 blending), +36 node count, +40 node results (ChrAnmResult,
 * 76 bytes each), +44 callback, +48 allocator). banm_c: +4 mpObj; fanm_c: +40 frame max,
 * +44 frame start, +48 current frame, +52 play mode. */
#include "gm.h"
#include "gm_nv.h"

#define SDA 0x8042F680u
#define L_ALLOCATOR   (SDA - 21176)      /* m3d::internal::l_allocator_p */
#define TYPE_SCNMDLSIMPLE 0x802F8FD8u    /* nw4r::g3d::ScnMdlSimple's TypeObj name */
#define TYPE_SCNMDL   0x802F8FF0u
#define VT_BMDL_DT    0x803295F0u        /* (the vtables the constructors / destructors set) */
#define VT_CALCRATIO  0x80329610u
#define VT_BANM       0x803295D8u
#define VT_FANM       0x80329620u
#define VT_MDLCB      0x80329658u
#define VT_MDL        0x80329638u
#define VT_SCNLEAF    0x80329670u
#define VT_BMDL       0x80329688u
#define F_TEST_ANM_FLAG 0x80249C90u      /* AnmObj::TestAnmFlag */
#define F_SCN_MTX_POS 0x8025B420u        /* ScnMdlSimple::GetScnMtxPos */
#define F_MULT_VEC_ZERO 0x8016F130u      /* mMtx_c::multVecZero */
#define F_GET_RES_MAT 0x8023B860u        /* ResMdl::GetResMat */
#define F_NUM_RES_MAT 0x8023B8C0u        /* ResMdl::GetResMatNumEntries */
#define F_NUM_RES_NODE 0x8023B360u       /* ResMdl::GetResNodeNumEntries */
#define F_CMA_CT      0x8025C660u        /* ScnMdl::CopiedMatAccess::CopiedMatAccess */
#define F_CMA_TEVCOLOR 0x8025C560u       /* ScnMdl::CopiedMatAccess::GetResMatTevColor */
#define F_SET_TEVCOLOR 0x8023D3C0u       /* ResMatTevColor::GXSetTevColor */
#define F_SET_TEVKCOLOR 0x8023D520u      /* ResMatTevColor::GXSetTevKColor */
#define F_DCSTORE     0x8023CA80u        /* ResMatTevColor::DCStore */
#define F_DELETE      0x802B9280u
#define F_ALLOCATOR_CT 0x8016A5E0u       /* mAllocator_c::mAllocator_c */
#define F_BANM_DT     0x80167EC0u        /* m3d::banm_c::~banm_c */
#define F_QUAT_MTX    0x801C1680u        /* C_QUATMtx */
#define F_QUAT_SLERP  0x801C1850u        /* C_QUATSlerp */
#define F_MTX_QUAT    0x801C0CF0u        /* PSMTXQuat */
#define F_MTX_IDENTITY 0x801C04D0u       /* PSMTXIdentity */
#define F_MEM_ALLOC   0x801D5540u        /* MEMAllocFromAllocator */
#define F_SCNMDL_CONSTRUCT 0x8025CA20u   /* ScnMdl::Construct */
#define F_SIMPLE_CONSTRUCT 0x8025A380u   /* ScnMdlSimple::Construct */
#define F_CB_TIMING   0x8025BEF0u        /* ScnMdlSimple::EnableScnMdlCallbackTiming */
#define F_DESTROY     0x80249AC0u        /* G3dObj::Destroy */
#define F_INSERT      0x80164E50u        /* m3d::pushBack */
#define F_SET_MTX     0x802574E0u        /* ScnObj::SetMtx */
#define F_GET_MTX     0x802575D0u        /* ScnObj::GetMtx */
#define F_PRIO_OPA    0x80257640u        /* ScnObj::SetPriorityDrawOpa */
#define F_PRIO_XLU    0x80257670u

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f      /* (gm.h: the PowerPC function's frame and prologue) */
/* a virtual call through the object's first word */
#define V(o, off) gm_u32(gm_u32(o) + (off))

/* G3dObj::DynamicCast: the object if it derives from the type, else 0 (the type name pointer
   goes through the stack at tmp) */
static gptr dyncast(GM_CTX, gptr obj, uint32_t type, gptr tmp) {
    if (!obj) return 0;
    gm_set_u32(tmp, type);
    return GM_CALL(V(obj, 8), 2, obj, tmp) ? obj : 0;
}

/* ================================================================== banm_c */
static uint32_t banm_is_bound(GM_CTX, gptr self) {
    gptr o = gm_u32(self + 4);
    if (!o) return 0;
    return GM_CALL(F_TEST_ANM_FLAG, 2, o, 4);                             /* FLAG_ANM_BOUND */
}
/* (getFrame / setFrameOnly / getRate / setRate: the float stays in f1) */
static void banm_vcall(GM_CTX, gptr self, uint32_t off) { gptr o = gm_u32(self + 4); GM_CALL(V(o, off), 1, o); }

/* ================================================================== calcRatio_c */
static void ratio_reset(GM_CTX, gptr r) {
    double one = R2F(21460), zero = R2F(21464);
    SF(r + 4, zero); SF(r + 8, one); SF(r + 16, zero); SF(r + 20, one); SF(r + 24, one);
}
static void ratio_ctor(GM_CTX, gptr r) {
    double zero = R2F(21464), one = R2F(21460);
    gm_set_u32(r, VT_CALCRATIO);
    SF(r + 4, zero); SF(r + 8, one); SF(r + 12, zero); SF(r + 16, zero); SF(r + 20, one); SF(r + 24, one);
    gm_set_u8(r + 28, 0); gm_set_u8(r + 29, 0);
}
static void ratio_off_update(GM_CTX, gptr r) { gm_set_u8(r + 28, 1); gm_set_u8(r + 29, 0); }
static void ratio_set(GM_CTX, gptr r, double dur) {
    double zero = R2F(21464);
    if (zero == dur) { ratio_reset(GM_PASS, r); return; }
    double one = R2F(21460);
    SF(r + 4, one);
    double step = frsp(one / dur);
    SF(r + 8, zero); SF(r + 16, one); SF(r + 20, zero); SF(r + 24, zero);
    gm_set_u8(r + 29, 1);
    SF(r + 12, step);
}
static uint32_t ratio_is_end(GM_CTX, gptr r) { return R2F(21464) == LF(r + 4); }
/* calc: the weight falls as t^2; the blend factors through FInv (fres + one Newton step), as the
   recompiled code computes them */
static void ratio_calc(GM_CTX, gptr r) {
    double w = LF(r + 4);
    if (R2F(21464) == w) return;
    double one = R2F(21460);
    double t = frsp(LF(r + 8) + LF(r + 12));
    SF(r + 8, t);
    if (t >= one) { ratio_reset(GM_PASS, r); return; }
    double a0 = frsp(w * t);
    gm_set_u8(r + 29, 1);
    a0 = frsp(t * a0);
    double nw = frsp(w - a0);
    SF(r + 4, nw);
    double f5 = frsp(nw / w);
    double f6 = frsp(one - nw);
    double f0 = frsp(f5 + f6);
    double f1 = frsp(fres(f0)), f3 = frsp(fres(f0));
    double f2 = frsp(f1 + f1);
    f1 = frsp(f1 * f1);
    double f4 = frsp(f3 + f3);
    f3 = frsp(f3 * f3);
    f1 = frsp(-(f0 * f1 - f2));
    f3 = frsp(-(f0 * f3 - f4));
    SF(r + 16, frsp(f5 * f1)); SF(r + 20, frsp(f6 * f1)); SF(r + 24, frsp(f6 * f3));
}

/* ================================================================== fanm_c */
static gptr fanm_ctor(GM_CTX, gptr self) {
    FN(0x80168D10); GM_NV_KEEP;
    NV_R(31, 0); NV_R(30, self);
    gm_set_u32(self, VT_BANM); gm_set_u32(self + 4, 0); gm_set_u32(self + 8, 0);
    GM_CALLR(0x80168D48u, F_ALLOCATOR_CT, 1, self + 12);
    double z = R2F(21456);
    gm_set_u32(self, VT_FANM);
    SF(self + 40, z); SF(self + 48, z); gm_set_u8(self + 52, 0);
    return self;
}
/* play: one step forward or back, looping or stopping at the end */
static void fanm_play(GM_CTX, gptr self) {
    FN(0x80168DE0); GM_NV_KEEP;
    NV_R(31, self);
    gptr o = gm_u32(self + 4);
    GM_CALLR(0x80168E10u, V(o, 32), 1, o);                                              /* GetFrame */
    double frame = ctx->f[1].d;
    NV_F(31, frame);
    o = gm_u32(self + 4);
    GM_CALLR(0x80168E28u, V(o, 44), 1, o);                                              /* GetUpdateRate */
    double rate = ctx->f[1].d, z = R2F(21456), nf;
    int neg = rate < z;
    if (neg) rate = frsp(rate * R2F(21452));
    SF(self + 48, frame);
    if (neg || (gm_u8(self + 52) & 2)) {                                  /* backwards */
        if (frame >= rate) nf = frsp(frame - rate);
        else if (!(gm_u8(self + 52) & 1)) nf = frsp(frame + frsp(LF(self + 40) - rate));
        else nf = LF(self + 44);
    } else {
        nf = frsp(frame + rate);
        if (!(gm_u8(self + 52) & 1)) {
            double max = LF(self + 40);
            if (nf >= max) nf = frsp(nf - max);
        } else {
            double end = frsp(LF(self + 40) - R2F(21448));
            if (nf >= end) nf = end;
        }
    }
    o = gm_u32(self + 4);
    ctx->f[1].d = nf;
    GM_CALLR(0x80168EE8u, V(o, 28), 1, o);                                              /* SetFrame */
}
/* set(duration, mode, rate, start) */
static void fanm_set(GM_CTX, gptr self, double dur, uint32_t mode, double rate, double start) {
    FN(0x80168F10); GM_NV_KEEP;
    double frame = start;
    if (start < R2F(21456)) frame = (mode == 1) ? R2F(21456) : frsp(dur - R2F(21448));
    NV_F(31, frame); NV_F(30, rate); NV_R(31, mode); NV_R(30, self);
    SF(self + 40, dur); SF(self + 44, R2F(21456));
    gptr o = gm_u32(self + 4);
    ctx->f[1].d = frame;
    GM_CALLR(0x80168F8Cu, V(o, 28), 1, o);
    o = gm_u32(self + 4);
    ctx->f[1].d = rate;
    GM_CALLR(0x80168FA4u, V(o, 40), 1, o);                                              /* SetUpdateRate */
    gm_set_u8(self + 52, mode);
    SF(self + 48, frame);
}
static void fanm_set_frame(GM_CTX, gptr self, double fr) {
    FN(0x80168FE0); GM_NV_KEEP;
    NV_F(31, fr); NV_R(31, self);
    ctx->f[1].d = fr;
    ctx->lr = 0x80169000u;
    banm_vcall(GM_PASS, self, 28);                                        /* banm_c::setFrameOnly (a leaf: tail call) */
    SF(self + 48, fr);
}
static uint32_t fanm_is_stop(GM_CTX, gptr self) {
    FN(0x80169020); GM_NV_KEEP;
    NV_R(31, self);
    gptr o = gm_u32(self + 4);
    GM_CALLR(0x80169050u, V(o, 32), 1, o);
    double frame = ctx->f[1].d;
    NV_F(31, frame);
    o = gm_u32(self + 4);
    GM_CALLR(0x80169068u, V(o, 44), 1, o);
    double rate = ctx->f[1].d;
    uint32_t mode = gm_u8(self + 52);
    if (rate < R2F(21456) || mode == 3) return frame <= LF(self + 44);
    if (mode == 1) return frame >= frsp(LF(self + 40) - R2F(21448));
    return 0;
}
/* checkFrame(f): did the last step pass frame f? */
static uint32_t fanm_check_frame(GM_CTX, gptr self, double fr) {
    FN(0x801690E0); GM_NV_KEEP;
    NV_F(30, fr); NV_R(31, self);
    gptr o = gm_u32(self + 4);
    GM_CALLR(0x8016911Cu, V(o, 32), 1, o);
    double frame = ctx->f[1].d;
    NV_F(31, frame);
    if (LF(self + 48) == frame) return frame == fr;
    o = gm_u32(self + 4);
    GM_CALLR(0x80169150u, V(o, 44), 1, o);
    double cur = LF(self + 48);
    if (ctx->f[1].d < R2F(21456) || (gm_u8(self + 52) & 2)) {
        if (cur > frame) return cur > fr && frame <= fr;
        return fr < cur || fr >= frame;
    }
    if (cur < frame) return cur < fr && frame >= fr;
    return fr > cur || fr <= frame;
}

/* ================================================================== scnLeaf_c */
static void leaf_remove(GM_CTX, gptr self) {
    FN(0x8016A090); GM_NV_KEEP;
    NV_R(31, self);
    gptr s = gm_u32(self + 4);
    if (!s) return;
    GM_CALLR(0x8016A0B8u, F_DESTROY, 1, s);
    gm_set_u32(self + 4, 0);
}
static void leaf_ctor(GM_CTX, gptr self) { gm_set_u32(self, VT_SCNLEAF); gm_set_u32(self + 4, 0); }
static gptr leaf_dtor(GM_CTX, gptr self, int32_t flags) {
    FN(0x8016A030); GM_NV_KEEP;
    NV_R(31, flags); NV_R(30, self);
    if (self) {
        gm_set_u32(self, VT_SCNLEAF);
        NCALL(0x8016A064u, leaf_remove(GM_PASS, self));
        if (flags > 0) GM_CALLR(0x8016A074u, F_DELETE, 1, self);
    }
    return self;
}
/* setOption(opt, v): a tail call into the scene object's vtable (+32) - registers as the game's (part 48) */
static void leaf_set_option(GM_CTX, gptr self, uint32_t opt, uint32_t v) {
    ctx->r[4] = opt; ctx->r[5] = v;
    ctx->r[3] = gm_u32(self + 4);
    ctx->r[12] = ctx->ctr = gm_u32(gm_u32(ctx->r[3]) + 32);
    ppc_call_indirect(ctx, base, ctx->r[12]);
}
/* calc / calcVtx(keep enabled after) */
static void leaf_calc(GM_CTX, gptr self, uint32_t keep, int vtx) {
    FN(vtx ? 0x8016A220u : 0x8016A1A0u); GM_NV_KEEP;
    GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    ctx->r[0] = lr;                                                  /* (mflr r0: still there at the calls) */
    NV_R(31, keep); NV_R(30, self);
    uint32_t opt = vtx ? 4 : 2;
    ctx->r[5] = 0; ctx->r[4] = opt; ctx->r[3] = self;
    NCALL(vtx ? 0x8016A248u : 0x8016A1C8u, leaf_set_option(GM_PASS, self, opt, 0));
    gptr s = ctx->r[3] = gm_u32(self + 4);
    ctx->r[4] = vtx ? 3 : 1; ctx->r[5] = 0; ctx->r[6] = 0;
    ctx->r[12] = ctx->ctr = V(s, 12);
    GM_CALLV(vtx ? 0x8016A268u : 0x8016A1E8u, ctx->r[12], 0);          /* G3dProc(CALC_WORLD / CALC_VTX): its registers are the result (part 48) */
    cr_cmp_s(ctx, 0, (int32_t)keep, 0);
    if (!keep) { ctx->r[3] = self; NCALL(vtx ? 0x8016A280u : 0x8016A200u, leaf_set_option(GM_PASS, self, opt, 1)); }
    ctx->r[0] = lr;
}
static void leaf_set_priority(GM_CTX, gptr self, uint32_t opa, uint32_t xlu) {
    FN(0x8016A2A0); GM_NV_KEEP;
    NV_R(31, xlu); NV_R(30, self);
    GM_CALLR(0x8016A2C4u, F_PRIO_OPA, 2, gm_u32(self + 4), opa);
    GM_CALLR(0x8016A2D0u, F_PRIO_XLU, 2, gm_u32(self + 4), xlu);
}

/* ================================================================== bmdl_c / smdl_c */
static gptr bmdl_ctor(GM_CTX, gptr self) {
    FN(0x8016A2F0); GM_NV_KEEP;
    NV_R(31, self);
    leaf_ctor(GM_PASS, self);
    gm_set_u32(self + 8, 0);
    gm_set_u32(self, VT_BMDL);
    return self;
}
/* ~bmdl_c: remove() through the vtable, then ~scnLeaf_c */
static gptr bmdl_dtor(GM_CTX, gptr self, int32_t flags) {
    FN(0x80168100); GM_NV_KEEP;
    NV_R(31, flags); NV_R(30, self);
    if (self) {
        gm_set_u32(self, VT_BMDL_DT);
        GM_CALLR(0x8016813Cu, gm_u32(VT_BMDL_DT + 16), 1, self);
        NCALL(0x80168148u, leaf_dtor(GM_PASS, self, 0));
        if (flags > 0) GM_CALLR(0x80168158u, F_DELETE, 1, self);
    }
    return self;
}
/* ~smdl_c */
static gptr smdl_dtor(GM_CTX, gptr self, int32_t flags) {
    FN(0x8016A340); GM_NV_KEEP;
    NV_R(31, flags); NV_R(30, self);
    if (self) {
        NCALL(0x8016A36Cu, bmdl_dtor(GM_PASS, self, 0));
        if (flags > 0) GM_CALLR(0x8016A37Cu, F_DELETE, 1, self);
    }
    return self;
}
static uint32_t bmdl_node_world_mtx(GM_CTX, gptr self, uint32_t idx, gptr mtx) {
    FN(0x80168180); GM_NV_KEEP;
    gptr o = gm_u32(self + 4);
    NV_R(31, o); NV_R(30, 0); NV_R(29, mtx); NV_R(28, idx);
    gptr m = dyncast(GM_PASS, o, TYPE_SCNMDLSIMPLE, f + 8);
    if (m) NV_R(30, 1);
    return GM_CALLR(0x80168208u, F_SCN_MTX_POS, 4, m, mtx, 1, idx);                     /* MTX_WORLD */
}
static uint32_t bmdl_node_world_pos(GM_CTX, gptr self, uint32_t idx, gptr vec) {
    FN(0x80168230); GM_NV_KEEP;
    NV_R(31, vec);
    if (!NCALL(0x8016824Cu, bmdl_node_world_mtx(GM_PASS, self, idx, f + 8))) return 0;
    GM_CALLR(0x80168268u, F_MULT_VEC_ZERO, 2, f + 8, vec);
    return 1;
}
/* setAnm(anm): a character animation becomes mpAnm (played by play()) */
static void bmdl_set_anm(GM_CTX, gptr self, gptr anm) {
    FN(0x80168280); GM_NV_KEEP;
    NV_R(29, anm); NV_R(28, self);
    if (GM_CALL(V(anm, 12), 1, anm) == 5) {                               /* TYPE_ANM_OTHER */
        gptr o = gm_u32(self + 4);
        NV_R(31, o); NV_R(30, 0);
        gptr m = dyncast(GM_PASS, o, TYPE_SCNMDL, f + 12);
        if (m) NV_R(30, 1);
        GM_CALL(V(m, 52), 3, m, gm_u32(anm + 4), 6);                      /* SetAnmObj(obj, NOT_SPECIFIED) */
        return;
    }
    gptr o = gm_u32(self + 4);
    NV_R(31, o); NV_R(30, 0);
    gptr m = dyncast(GM_PASS, o, TYPE_SCNMDLSIMPLE, f + 8);
    if (m) NV_R(30, 1); else NV_R(31, 0);
    if (GM_CALL(V(anm, 12), 1, anm) == 0) gm_set_u32(self + 8, anm);       /* TYPE_ANM_CHR */
    GM_CALL(V(m, 52), 3, m, gm_u32(anm + 4), 6);
}
static void bmdl_play(GM_CTX, gptr self) { gptr a = gm_u32(self + 8); if (a) GM_CALL(V(a, 20), 1, a); }
static uint32_t bmdl_res_mdl(GM_CTX, gptr self) {
    FN(0x80168400); GM_NV_KEEP;
    gptr o = gm_u32(self + 4);
    NV_R(31, o); NV_R(30, 0);
    gptr m = dyncast(GM_PASS, o, TYPE_SCNMDLSIMPLE, f + 8);
    return gm_u32(m + 232);
}
static uint32_t bmdl_res_mat(GM_CTX, gptr self, uint32_t idx) {
    FN(0x80168480); GM_NV_KEEP;
    gptr o = gm_u32(self + 4);
    NV_R(31, o); NV_R(30, 0); NV_R(29, idx);
    gptr m = dyncast(GM_PASS, o, TYPE_SCNMDLSIMPLE, f + 8);
    if (m) NV_R(30, 1); else NV_R(31, 0);
    gm_set_u32(f + 12, gm_u32(m + 232));
    return GM_CALLR(0x80168500u, F_GET_RES_MAT, 2, f + 12, idx);
}
static void bmdl_remove_anm(GM_CTX, gptr self, uint32_t type) {
    FN(0x80168520); GM_NV_KEEP;
    NV_R(30, 0); NV_R(29, type); NV_R(28, self);
    gptr o = gm_u32(self + 4);
    NV_R(31, o);
    gptr m = dyncast(GM_PASS, o, TYPE_SCNMDLSIMPLE, f + 8);
    if (m) NV_R(30, 1); else NV_R(31, 0);
    if (type == 0) gm_set_u32(self + 8, 0);                                /* ANMOBJTYPE_CHR */
    GM_CALL(V(m, 60), 2, m, type);                                         /* RemoveAnmObj */
}
/* setTevColor / setTevKColor(material, register, &color, mark dirty) */
static void bmdl_set_tev(GM_CTX, gptr self, uint32_t idx, uint32_t reg, gptr color, uint32_t dirty, int k) {
    FN(k ? 0x80168880u : 0x801685E0u); GM_NV_KEEP;
    uint32_t setc = k ? F_SET_TEVKCOLOR : F_SET_TEVCOLOR;
    gptr o = gm_u32(self + 4);
    NV_R(31, o); NV_R(25, self); NV_R(26, idx); NV_R(27, reg); NV_R(28, color); NV_R(29, dirty); NV_R(30, 0);
    gptr m = dyncast(GM_PASS, o, TYPE_SCNMDL, f + 8);
    if (m) NV_R(30, 1); else NV_R(31, 0);
    if (m) {
        GM_CALL(F_CMA_CT, 3, f + 28, m, idx);
        gm_set_u32(f + 24, GM_CALL(F_CMA_TEVCOLOR, 2, f + 28, dirty));
        gm_set_u32(f + 16, gm_u32(color));
        GM_CALL(setc, 3, f + 24, reg, f + 16);
        GM_CALL(F_DCSTORE, 2, f + 24, 0);
    } else {
        gptr mat = NCALL(k ? 0x80168954u : 0x801686B4u, bmdl_res_mat(GM_PASS, self, idx));
        uint32_t off = gm_u32(mat + 60);
        gm_set_u32(f + 20, (off ? mat + off : 0) + 32);
        gm_set_u32(f + 12, gm_u32(color));
        GM_CALL(setc, 3, f + 20, reg, f + 12);
        GM_CALL(F_DCSTORE, 2, f + 20, 0);
    }
}
/* setTevColorAll / setTevKColorAll(register, &color, mark dirty) */
static void bmdl_set_tev_all(GM_CTX, gptr self, uint32_t reg, gptr color, uint32_t dirty, int k) {
    FN(k ? 0x801689B0u : 0x80168710u); GM_NV_KEEP;
    uint32_t setc = k ? F_SET_TEVKCOLOR : F_SET_TEVCOLOR;
    NV_R(31, self); NV_R(27, reg); NV_R(28, color); NV_R(29, dirty);
    gm_set_u32(f + 28, NCALL(k ? 0x801689D8u : 0x80168738u, bmdl_res_mdl(GM_PASS, self)));
    gptr o = gm_u32(self + 4);
    NV_R(30, 0); NV_R(31, o);
    gptr m = dyncast(GM_PASS, o, TYPE_SCNMDL, f + 8);
    if (m) NV_R(30, 1); else NV_R(31, 0);
    uint32_t i = 0;
    NV_R(30, 0);
    if (m) {
        while (i < GM_CALL(F_NUM_RES_MAT, 1, f + 28)) {
            GM_LOOP();
            GM_CALL(F_CMA_CT, 3, f + 32, m, i);
            gm_set_u32(f + 24, GM_CALL(F_CMA_TEVCOLOR, 2, f + 32, dirty));
            gm_set_u32(f + 16, gm_u32(color));
            GM_CALL(setc, 3, f + 24, reg, f + 16);
            GM_CALL(F_DCSTORE, 2, f + 24, 0);
            NV_R(30, ++i);
        }
    } else {
        while (i < GM_CALL(F_NUM_RES_MAT, 1, f + 28)) {
            GM_LOOP();
            gptr mat = GM_CALL(F_GET_RES_MAT, 2, f + 28, i);
            uint32_t off = gm_u32(mat + 60);
            gm_set_u32(f + 20, (off ? mat + off : 0) + 32);
            gm_set_u32(f + 12, gm_u32(color));
            GM_CALL(setc, 3, f + 20, reg, f + 12);
            GM_CALL(F_DCSTORE, 2, f + 20, 0);
            NV_R(30, ++i);
        }
    }
}
static void bmdl_remove(GM_CTX, gptr self) { gm_set_u32(self + 8, 0); leaf_remove(GM_PASS, self); }
/* smdl_c::create(resMdl, allocator, buffer option, view count, &size) */
static uint32_t smdl_create(GM_CTX, gptr self, gptr res, gptr alloc, uint32_t opt, uint32_t views, gptr psize) {
    FN(0x8016A3A0); GM_NV_KEEP;
    NV_R(31, self);
    if (!alloc) alloc = gm_u32(L_ALLOCATOR);
    if (!psize) psize = f + 16;
    gptr s;
    if (opt) { gm_set_u32(f + 12, gm_u32(res)); s = GM_CALLR(0x8016A3ECu, F_SCNMDL_CONSTRUCT, 5, alloc, psize, f + 12, opt, views); }
    else { gm_set_u32(f + 8, gm_u32(res)); s = GM_CALLR(0x8016A410u, F_SIMPLE_CONSTRUCT, 4, alloc, psize, f + 8, views); }
    gm_set_u32(self + 4, s);
    if (!s) return 0;
    GM_CALLR(0x8016A430u, F_PRIO_OPA, 2, s, 127);
    GM_CALLR(0x8016A43Cu, F_PRIO_XLU, 2, gm_u32(self + 4), 127);
    return 1;
}

/* ================================================================== mdl_c::mdlCallback_c */
static gptr cb_ctor(GM_CTX, gptr self) {
    FN(0x80169560); GM_NV_KEEP;
    NV_R(31, self);
    gm_set_u32(self, VT_MDLCB);
    ratio_ctor(GM_PASS, self + 4);
    gm_set_u32(self + 36, 0); gm_set_u32(self + 40, 0); gm_set_u32(self + 44, 0); gm_set_u32(self + 48, 0);
    return self;
}
static gptr plain_dtor(GM_CTX, gptr self, int32_t flags, uint32_t addr) {
    FN(addr); GM_NV_KEEP;
    NV_R(31, self);
    if (self && flags > 0) GM_CALL(F_DELETE, 1, self);
    return self;
}
static void copy_result(GM_CTX, gptr dst, gptr src) { for (int i = 0; i < 19; i++) gm_set_u32(dst + 4 * i, gm_u32(src + 4 * i)); }
/* ExecCallbackA(anm result, resMdl, calc world): blend the node's result with the stored one
   while the ratio runs, store it, then the user callback's timingA */
static void cb_exec_a(GM_CTX, gptr self, gptr a, gptr res, gptr cw) {
    FN(0x80169600); GM_NV_KEEP;
    uint32_t node = gm_u16(cw + 6);
    gptr r = gm_u32(self + 40) + (uint32_t)((int32_t)node * 76);
    NV_R(31, node); NV_R(28, a); NV_R(27, self); NV_R(29, res); NV_R(30, r);
    if (gm_u8(self + 32) && !NCALL(0x8016965Cu, ratio_is_end(GM_PASS, self + 4))) {
        if (!gm_u8(self + 33)) copy_result(GM_PASS, a, r);
        else {
            uint32_t fl = gm_u32(a);
            double slerp = LF(self + 28), from = LF(self + 20), to = LF(self + 24);
            NV_R(26, fl); NV_FL(29, slerp); NV_FL(31, from); NV_FL(30, to);
            if (!(fl & 8)) {                                              /* FLAG_SCALE_ONE */
                double x = frsp(LF(a + 4) * to), y = frsp(LF(a + 8) * to), zz = frsp(LF(a + 12) * to);
                SF(a + 4, frsp(x + frsp(LF(r + 4) * from)));
                SF(a + 8, frsp(y + frsp(LF(r + 8) * from)));
                SF(a + 12, frsp(zz + frsp(LF(r + 12) * from)));
            } else {
                SF(a + 4, frsp(to + frsp(LF(r + 4) * from)));
                SF(a + 8, frsp(to + frsp(LF(r + 8) * from)));
                SF(a + 12, frsp(to + frsp(LF(r + 12) * from)));
            }
            GM_CALLR(0x801697ACu, F_QUAT_MTX, 2, f + 40, r + 28);
            if (!(fl & 0x20)) GM_CALLR(0x801697C0u, F_QUAT_MTX, 2, f + 24, a + 28);     /* FLAG_ROT_ZERO */
            else { double z = R2F(21432), o1 = R2F(21428); SF(f + 24, z); SF(f + 28, z); SF(f + 32, z); SF(f + 36, o1); }
            ctx->f[1].d = slerp;
            GM_CALLR(0x801697F0u, F_QUAT_SLERP, 3, f + 40, f + 24, f + 40);
            double cx = LF(a + 40), cy = LF(a + 56), cz = LF(a + 72);
            SF(f + 12, cx); SF(f + 16, cy); SF(f + 20, cz);
            GM_CALLR(0x80169814u, F_MTX_QUAT, 2, a + 28, f + 40);
            cx = LF(f + 12); cy = LF(f + 16); cz = LF(f + 20);
            SF(a + 40, cx); SF(a + 56, cy); SF(a + 72, cz);
            if (!(fl & 0x40)) {                                           /* FLAG_TRANS_ZERO */
                SF(a + 40, frsp(cx * to)); SF(a + 56, frsp(cy * to)); SF(a + 72, frsp(cz * to));
            }
            SF(a + 40, frsp(LF(a + 40) + frsp(LF(r + 40) * from)));
            SF(a + 56, frsp(LF(a + 56) + frsp(LF(r + 56) * from)));
            SF(a + 72, frsp(LF(a + 72) + frsp(LF(r + 72) * from)));
            gm_set_u32(a, gm_u32(a) & 0x7FFFFF97u);
            copy_result(GM_PASS, r, a);
        }
    } else copy_result(GM_PASS, r, a);
    gptr cb = gm_u32(self + 44);
    if (cb) {
        gm_set_u32(f + 8, gm_u32(res));
        GM_CALLR(0x801699FCu, V(cb, 12), 4, cb, node, a, f + 8);                         /* timingA */
    }
}
/* ExecCallbackB(world mtx manip, resMdl, calc world): timingB, then on to the next node */
static void cb_exec_b(GM_CTX, gptr self, gptr manip, gptr res, gptr cw) {
    FN(0x80169A30); GM_NV_KEEP;
    uint32_t node = gm_u16(cw + 6);
    NV_R(30, cw); NV_R(29, res); NV_R(31, node);
    gptr cb = gm_u32(self + 44);
    if (cb) {
        gm_set_u32(f + 8, gm_u32(res));
        GM_CALLR(0x80169A88u, V(cb, 16), 4, cb, node, manip, f + 8);                     /* timingB */
    }
    uint32_t n = GM_CALLR(0x80169A90u, F_NUM_RES_NODE, 1, res);
    uint32_t nx = node + 1;
    gm_set_u16(cw + 6, (uint16_t)(nx - divwu(nx, n) * n));
}
static void cb_exec_c(GM_CTX, gptr self, gptr mtx, gptr res) {
    FN(0x80169AC0); GM_NV_KEEP;
    NV_R(31, self);
    gptr cb = gm_u32(self + 44);
    if (cb) {
        gm_set_u32(f + 8, gm_u32(res));
        GM_CALLR(0x80169B00u, V(cb, 20), 3, cb, mtx, f + 8);                             /* timingC */
    }
    ratio_off_update(GM_PASS, self + 4);
}
/* create(resMdl, allocator, &size): a result per node, identity */
static uint32_t cb_create(GM_CTX, gptr self, gptr res, gptr alloc, gptr psize) {
    FN(0x80169B20); GM_NV_KEEP;
    NV_R(27, self);
    if (!alloc) alloc = gm_u32(L_ALLOCATOR);
    NV_R(28, alloc); NV_R(29, psize);
    gm_set_u32(f + 8, 0);
    if (!psize) { psize = f + 8; NV_R(29, psize); }
    uint32_t n = GM_CALLR(0x80169B70u, F_NUM_RES_NODE, 1, res);
    uint32_t sz = (uint32_t)((int32_t)n * 76);
    NV_R(31, sz);
    gm_set_u32(self + 36, n);
    gptr p = GM_CALLR(0x80169B84u, F_MEM_ALLOC, 2, alloc, sz);
    gm_set_u32(self + 40, p);
    if (!p) return 0;
    gm_set_u32(psize, (sz + ((gm_u32(psize) + 3) & ~3u) + 3) & ~3u);
    double one = R2F(21428);
    NV_FL(31, one); NV_R(30, 0);
    gptr cur = gm_u32(self + 40);
    NV_R(31, cur);
    for (int32_t i = 0; i < (int32_t)gm_u32(self + 36); ) {
        GM_LOOP();
        SF(cur + 4, one); SF(cur + 8, one); SF(cur + 12, one);
        GM_CALLR(0x80169BD8u, F_MTX_IDENTITY, 1, cur + 28);
        cur += 76; i++;
        NV_R(31, cur); NV_R(30, i);
    }
    gm_set_u32(self + 48, alloc);
    return 1;
}
static void cb_remove(GM_CTX, gptr self) {
    FN(0x80169C20); GM_NV_KEEP;
    NV_R(31, self);
    gm_set_u8(self + 4 + 28, 0);                                          /* calcRatio_c::remove */
    ratio_reset(GM_PASS, self + 4);
    gptr p = gm_u32(self + 40);
    if (p) { gptr a = gm_u32(self + 48); GM_CALLR(0x80169C5Cu, gm_u32(gm_u32(a + 16) + 16), 2, a, p); }   /* the allocator's free */
    gm_set_u32(self + 40, 0); gm_set_u32(self + 48, 0);
}
static void cb_calc_blend(GM_CTX, gptr self) {
    FN(0x80169C90); GM_NV_KEEP;
    NV_R(31, self);
    if (!ratio_is_end(GM_PASS, self + 4)) ratio_calc(GM_PASS, self + 4);
}

/* ================================================================== mdl_c */
static gptr mdl_ctor(GM_CTX, gptr self) {
    FN(0x80169CD0); GM_NV_KEEP;
    NV_R(31, self);
    NCALL(0x80169CE8u, bmdl_ctor(GM_PASS, self));
    gm_set_u32(self, VT_MDL);
    NCALL(0x80169CFCu, cb_ctor(GM_PASS, self + 12));
    return self;
}
static gptr mdl_dtor(GM_CTX, gptr self, int32_t flags) {
    FN(0x80169D20); GM_NV_KEEP;
    NV_R(31, flags); NV_R(30, self);
    if (self) {
        NCALL(0x80169D50u, plain_dtor(GM_PASS, self + 12, -1, 0x801695C0u));
        NCALL(0x80169D5Cu, smdl_dtor(GM_PASS, self, 0));
        if (flags > 0) GM_CALLR(0x80169D6Cu, F_DELETE, 1, self);
    }
    return self;
}
/* create(resMdl, allocator, buffer option, view count, &size) */
static uint32_t mdl_create(GM_CTX, gptr self, gptr res, gptr alloc, uint32_t opt, uint32_t views, gptr psize) {
    FN(0x80169D90); GM_NV_KEEP;
    NV_R(27, self); NV_R(28, res);
    if (!alloc) alloc = gm_u32(L_ALLOCATOR);
    NV_R(29, alloc); NV_R(31, psize);
    gptr ps_mdl = psize ? f + 24 : 0, ps_cb = psize ? f + 20 : 0;
    NV_R(30, ps_cb);
    gm_set_u32(f + 16, gm_u32(res));
    if (!NCALL(0x80169DF0u, smdl_create(GM_PASS, self, f + 16, alloc, opt, views, ps_mdl))) return 0;
    gm_set_u32(f + 12, gm_u32(res));
    if (!NCALL(0x80169E1Cu, cb_create(GM_PASS, self + 12, f + 12, alloc, ps_cb))) {
        GM_CALL(V(self, 16), 1, self);                                    /* remove() */
        return 0;
    }
    if (psize) gm_set_u32(psize, gm_u32(f + 24) + gm_u32(f + 20));
    gptr o = gm_u32(self + 4);
    NV_R(31, o); NV_R(30, 0);
    gptr m = dyncast(GM_PASS, o, TYPE_SCNMDLSIMPLE, f + 8);
    if (m) NV_R(30, 1); else NV_R(31, 0);
    gm_set_u32(m + 284, self + 12);                                       /* SetScnMdlCallback */
    GM_CALLR(0x80169EBCu, F_CB_TIMING, 2, m, 7);                                        /* CALLBACK_TIMING_ALL */
    gm_set_u32(self + 56, 0);                                             /* setCallback(nullptr) */
    return 1;
}
static void mdl_remove(GM_CTX, gptr self) {
    FN(0x80169EF0); GM_NV_KEEP;
    NV_R(31, self);
    NCALL(0x80169F0Cu, cb_remove(GM_PASS, self + 12));
    ctx->lr = 0x80169F14u;
    bmdl_remove(GM_PASS, self);
}
/* setAnm(anm, blend frames): a character animation blends in */
static void mdl_set_anm(GM_CTX, gptr self, gptr anm, double blend) {
    FN(0x80169F80); GM_NV_KEEP;
    NV_F(31, blend); NV_R(31, anm); NV_R(30, self);
    if (GM_CALLR(0x80169FB8u, V(anm, 12), 1, anm) == 0) ratio_set(GM_PASS, self + 16, blend);   /* (mCallback + 4) */
    NCALL(0x80169FD8u, bmdl_set_anm(GM_PASS, self, anm));
}
static void mdl_play(GM_CTX, gptr self) {
    FN(0x80169F40); GM_NV_KEEP;
    NV_R(31, self);
    ctx->lr = 0x80169F58u;
    bmdl_play(GM_PASS, self);
    NCALL(0x80169F60u, cb_calc_blend(GM_PASS, self + 12));
}

/* ================================================================== hle entry points
   All on: 49 are reached by the test runs from recompiled code; the rest run inside them
   (calcRatio_c and the callback's create / remove through mdl_c) or share their code with a
   reached one but for a constant (setTevKColorAll, calcVtx). */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
/* banm_c */
E(testAnmFlag__Q23m3d6banm_cFv) { GM_RET(banm_is_bound(GM_PASS, A(0))); }                    /* banm_c::IsBound */
E(getCurrentFrame__Q23m3d6banm_cFv) { banm_vcall(GM_PASS, A(0), 32); }                       /* ::getFrame */
E(setCurrentFrame__Q23m3d6banm_cFf) { banm_vcall(GM_PASS, A(0), 28); }                       /* ::setFrameOnly */
E(getUpdateRate__Q23m3d6banm_cFv) { banm_vcall(GM_PASS, A(0), 44); }                         /* ::getRate */
E(setUpdateRate__Q23m3d6banm_cFf) { banm_vcall(GM_PASS, A(0), 40); }                         /* ::setRate */
/* bmdl_c */
E(fn_80168100) { GM_LR_KEEP; GM_RET(bmdl_dtor(GM_PASS, A(0), (int32_t)A(1))); }               /* bmdl_c::~bmdl_c */
E(getMatrixForNode__Q23m3d5mdl_cFUiPA3_A4_f) { GM_RET(bmdl_node_world_mtx(GM_PASS, A(0), A(1), A(2))); }   /* ::getNodeWorldMtx */
E(fn_80168230) { GM_LR_KEEP; GM_RET(bmdl_node_world_pos(GM_PASS, A(0), A(1), A(2))); }        /* ::getNodeWorldMtxMultVecZero */
E(fn_80168280) { bmdl_set_anm(GM_PASS, A(0), A(1)); }                                         /* ::setAnm */
E(fn_801683E0) { bmdl_play(GM_PASS, A(0)); }                                                  /* ::play */
E(fn_80168400) { GM_RET(bmdl_res_mdl(GM_PASS, A(0))); }                                       /* ::getResMdl */
E(fn_80168480) { GM_RET(bmdl_res_mat(GM_PASS, A(0), A(1))); }                                 /* ::getResMat */
E(fn_80168520) { bmdl_remove_anm(GM_PASS, A(0), A(1)); }                                      /* ::removeAnm */
E(fn_801685E0) { GM_LR_KEEP; bmdl_set_tev(GM_PASS, A(0), A(1), A(2), A(3), A(4), 0); }       /* ::setTevColor */
E(fn_80168710) { GM_LR_KEEP; bmdl_set_tev_all(GM_PASS, A(0), A(1), A(2), A(3), 0); }         /* ::setTevColorAll */
E(fn_80168880) { GM_LR_KEEP; bmdl_set_tev(GM_PASS, A(0), A(1), A(2), A(3), A(4), 1); }       /* ::setTevKColor */
E(fn_801689B0) { GM_LR_KEEP; bmdl_set_tev_all(GM_PASS, A(0), A(1), A(2), A(3), 1); }         /* ::setTevKColorAll */
E(fn_80168B20) { bmdl_remove(GM_PASS, A(0)); }                                                /* ::remove */
E(fn_80168B30) { GM_RET(0); }
E(fn_8016A2F0) { GM_RET(bmdl_ctor(GM_PASS, A(0))); }                                          /* bmdl_c::bmdl_c */
E(fn_8016A340) { GM_LR_KEEP; GM_RET(smdl_dtor(GM_PASS, A(0), (int32_t)A(1))); }               /* smdl_c::~smdl_c */
E(fn_8016A3A0) { GM_RET(smdl_create(GM_PASS, A(0), A(1), A(2), A(3), A(4), A(5))); }          /* smdl_c::create */
/* calcRatio_c */
E(fn_80168B40) { ratio_ctor(GM_PASS, A(0)); }                                                 /* calcRatio_c::calcRatio_c */
E(fn_80168B80) { gm_set_u8(A(0) + 28, 0); ratio_reset(GM_PASS, A(0)); }                       /* ::remove */
E(fn_80168B90) { ratio_reset(GM_PASS, A(0)); }                                                /* ::reset */
E(fn_80168BB0) { ratio_off_update(GM_PASS, A(0)); }                                           /* ::offUpdate */
E(fn_80168BD0) { ratio_set(GM_PASS, A(0), GM_FARG(0)); }                                      /* ::set */
E(fn_80168C10) { ratio_calc(GM_PASS, A(0)); }                                                 /* ::calc */
E(fn_80168CB0) { GM_RET(ratio_is_end(GM_PASS, A(0))); }                                       /* ::isEnd */
E(fn_80168CD0) { GM_RET(plain_dtor(GM_PASS, A(0), (int32_t)A(1), 0x80168CD0u)); }             /* FNADDR ::~calcRatio_c */
/* fanm_c */
E(__ct__Q23m3d6fanm_cFv) { GM_RET(fanm_ctor(GM_PASS, A(0))); }                                /* fanm_c::fanm_c */
E(__dt__Q23m3d6fanm_cFv) {                                                                    /* ::~fanm_c */
    FN(0x80168D80); GM_NV_KEEP;
    gptr s = A(0); int32_t fl = (int32_t)A(1);
    NV_R(31, fl); NV_R(30, s);
    if (s) { GM_CALLR(0x80168DACu, F_BANM_DT, 2, s, 0); if (fl > 0) GM_CALLR(0x80168DBCu, F_DELETE, 1, s); }
    GM_RET(s);
}
E(process__Q23m3d6fanm_cFv) { fanm_play(GM_PASS, A(0)); }                                     /* ::play */
E(fn_80168F10) { fanm_set(GM_PASS, A(0), GM_FARG(0), A(1), GM_FARG(1), GM_FARG(2)); }         /* ::set */
E(setCurrentFrame__Q23m3d6fanm_cFf) { GM_LR_KEEP; fanm_set_frame(GM_PASS, A(0), GM_FARG(0)); } /* ::setFrame */
E(isAnimationDone__Q23m3d6fanm_cFv) { GM_RET(fanm_is_stop(GM_PASS, A(0))); }                  /* ::isStop */
E(querySomething__Q23m3d6fanm_cFv) { GM_RET(fanm_check_frame(GM_PASS, A(0), GM_FARG(0))); }   /* ::checkFrame */
/* mdl_c::mdlCallback_c */
E(fn_80169560) { GM_RET(cb_ctor(GM_PASS, A(0))); }                                            /* mdlCallback_c::mdlCallback_c */
E(fn_801695C0) { GM_RET(plain_dtor(GM_PASS, A(0), (int32_t)A(1), 0x801695C0u)); }             /* FNADDR ::~mdlCallback_c */
E(fn_80169600) { GM_LR_KEEP; cb_exec_a(GM_PASS, A(0), A(1), A(2), A(3)); }                    /* ::ExecCallbackA */
E(fn_80169A30) { cb_exec_b(GM_PASS, A(0), A(1), A(2), A(3)); }                                /* ::ExecCallbackB */
E(fn_80169AC0) { cb_exec_c(GM_PASS, A(0), A(1), A(2)); }                                      /* ::ExecCallbackC */
E(fn_80169B20) { GM_RET(cb_create(GM_PASS, A(0), A(1), A(2), A(3))); }                        /* ::create */
E(fn_80169C20) { cb_remove(GM_PASS, A(0)); }                                                  /* ::remove */
E(fn_80169C80) { ratio_set(GM_PASS, A(0) + 4, GM_FARG(0)); }                                  /* ::setBlendFrame */
E(fn_80169C90) { cb_calc_blend(GM_PASS, A(0)); }                                              /* ::calcBlend */
/* mdl_c */
E(__ct__Q23m3d5mdl_cFv) { GM_LR_KEEP; GM_RET(mdl_ctor(GM_PASS, A(0))); }                      /* mdl_c::mdl_c */
E(__dt__Q23m3d5mdl_cFv) { GM_LR_KEEP; GM_RET(mdl_dtor(GM_PASS, A(0), (int32_t)A(1))); }        /* ::~mdl_c */
E(setup__Q23m3d5mdl_cFQ34nw4r3g3d6ResMdlPvUiiPUi) { GM_LR_KEEP; GM_RET(mdl_create(GM_PASS, A(0), A(1), A(2), A(3), A(4), A(5))); }   /* ::create */
E(fn_80169EF0) { GM_LR_KEEP; mdl_remove(GM_PASS, A(0)); }                                     /* ::remove */
E(fn_80169F30) { GM_LR_KEEP; mdl_set_anm(GM_PASS, A(0), A(1), R2F(21432)); }                              /* ::setAnm(anm) */
E(vf1C__Q3m3d5mdl_cFv) { GM_LR_KEEP; mdl_play(GM_PASS, A(0)); }                               /* ::play */
E(bindAnim__Q23m3d5mdl_cFPQ23m3d6banm_cf) { GM_LR_KEEP; mdl_set_anm(GM_PASS, A(0), A(1), GM_FARG(0)); }   /* ::setAnm(anm, blend) */
E(fn_8016A000) { gm_set_u32(A(0) + 56, A(1)); }                                               /* ::setCallback */
/* scnLeaf_c */
E(__ct__Q23m3d9scnLeaf_cFv) { leaf_ctor(GM_PASS, A(0)); }                                     /* scnLeaf_c::scnLeaf_c */
E(__dt__Q23m3d9scnLeaf_cFv) { GM_LR_KEEP; GM_RET(leaf_dtor(GM_PASS, A(0), (int32_t)A(1))); }   /* ::~scnLeaf_c */
E(free__Q23m3d9scnLeaf_cFv) { leaf_remove(GM_PASS, A(0)); }                                   /* ::remove */
E(scheduleForDrawing__Q23m3d9scnLeaf_cFv) { GM_RET(GM_CALL(F_INSERT, 1, gm_u32(A(0) + 4))); } /* ::entry */
E(fn_8016A0F0) { leaf_set_option(GM_PASS, A(0), A(1), A(2)); }                                /* ::setOption */
E(fn_8016A110) { gptr s = gm_u32(A(0) + 4); GM_RET(GM_CALL(V(s, 36), 3, s, A(1), A(2))); }    /* ::getOption */
E(setScale__Q23m3d5mdl_cFfff) { gptr s = gm_u32(A(0) + 4); SF(s + 220, GM_FARG(0)); SF(s + 224, GM_FARG(1)); SF(s + 228, GM_FARG(2)); }   /* ::setScale(x, y, z) */
E(setScale__Q23m3d5mdl_cFP7Point3d) { gptr s = gm_u32(A(0) + 4), v = A(1); SF(s + 220, LF(v)); SF(s + 224, LF(v + 4)); SF(s + 228, LF(v + 8)); }   /* ::setScale(vec) */
E(setDrawMatrix__Q23m3d5mdl_cFPA3_A4_Cf) { GM_RET(GM_CALL(F_SET_MTX, 3, gm_u32(A(0) + 4), 0, A(1))); }   /* ::setLocalMtx */
E(fn_8016A180) { GM_RET(GM_CALL(F_GET_MTX, 3, gm_u32(A(0) + 4), 0, A(1))); }                  /* ::getLocalMtx */
E(getViewMatrix__Q23m3d9scnLeaf_cFPA3_A4_f) { GM_RET(GM_CALL(F_GET_MTX, 3, gm_u32(A(0) + 4), 2, A(1))); }   /* ::getViewMtx */
E(calcWorld__Q23m3d5mdl_cFb) { GM_LR_KEEP; leaf_calc(GM_PASS, A(0), A(1), 0); }               /* ::calc */
E(fn_8016A220) { GM_LR_KEEP; leaf_calc(GM_PASS, A(0), A(1), 1); }                             /* ::calcVtx */
E(fn_8016A2A0) { leaf_set_priority(GM_PASS, A(0), A(1), A(2)); }                              /* ::setPriorityDraw */
