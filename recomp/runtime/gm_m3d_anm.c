/* gm_m3d_anm.c - mLib's model animations (m3d): the banm_c base (its own frame heap), anmChr_c
 * (skeletal), anmChrBlend_c, anmVis_c and the three per-material ones that keep several child
 * animations under an nw4r "override" object - anmMatClr_c, anmTexPat_c, anmTexSrt_c (the same
 * code but for their nw4r classes, so one implementation here takes a table of addresses).
 * Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_3d/{banm,anm_chr,anm_chr_blend,anm_vis,
 * anm_mat_clr,anm_tex_pat,anm_tex_srt}.cpp) and checked against the recompiled USA rev 2 code
 * (0x801650D0-0x80168060). anmTexSrt_c also checks its allocations for null (and frees the heap
 * block after destroying the heap when a child fails). The non-volatile registers are mirrored
 * around nested calls (gm_nv.h).
 *
 * banm_c: +0 vtable, +4 mpObj (an nw4r AnmObj), +8 mpHeap, +12 mAllocator (20 bytes); the fanm_c
 * fields follow (gm_m3d.c), and the override classes keep their children (child_c: an fanm_c,
 * 56 bytes) at +40. */
#include "gm.h"
#include "gm_nv.h"

#define SDA 0x8042F680u
#define L_ALLOCATOR (SDA - 21176)        /* m3d::internal::l_allocator_p */
#define BANM_OPT    (SDA - 21152)        /* m3d::banm_c::ms_DefaultAllocOptBit */
#define VT_BANM     0x803295D8u
#define BANM_HEAP_NAME 0x803295A8u
#define T_CHR_NODE  0x802F86A0u          /* (nw4r TypeObj names) AnmObjChrNode */
#define T_CHR_BLEND 0x802F86B4u          /* AnmObjChrBlend */
#define T_CHR_RES   0x802F86C8u          /* AnmObjChrRes */
#define F_CHR_CT    0x80248990u          /* AnmObjChrRes::Construct */
#define F_BLEND_CT  0x802481B0u          /* AnmObjChrBlend::Construct */
#define F_VIS_CT    0x80242C30u          /* AnmObjVisRes::Construct */
#define F_DETACH_PARENT 0x80249B40u      /* G3dObj::DetachFromParent */
#define F_DESTROY   0x80249AC0u          /* G3dObj::Destroy */
#define F_FRM_COST  0x8016E7D0u          /* mHeap::frmHeapCost */
#define F_CREATE_FRM 0x8016E630u         /* mHeap::createFrmHeap */
#define F_DESTROY_FRM 0x8016E740u        /* mHeap::destroyFrmHeap */
#define F_FRM_FREE  0x802B99C0u          /* EGG::FrmHeap::free */
#define F_HEAP_FREE 0x802B8F70u          /* EGG::Heap::free */
#define F_ALLOCATOR_SETUP 0x8016A690u    /* mAllocator_c::attach */
#define F_ALLOCATOR_DT 0x8016A630u
#define F_MEM_ALLOC 0x801D5540u          /* MEMAllocFromAllocator */
#define F_NEW_AT    0x802B9220u          /* operator new(size, void *) */
#define F_DELETE    0x802B9280u
#define F_BANM_DT   0x80167EC0u
#define F_BANM_REMOVE 0x80167F30u
#define F_BANM_ALLOC 0x80167FA0u         /* banm_c::createAllocator */
#define F_BANM_BOUND 0x80168060u         /* banm_c::IsBound */
#define F_BANM_FRAME 0x80168080u         /* banm_c::getFrame / getRate / setRate */
#define F_BANM_RATE 0x801680C0u
#define F_BANM_SET_RATE 0x801680E0u
#define F_GET_RES_MDL 0x80168400u        /* bmdl_c::getResMdl */
#define F_REMOVE_ANM 0x80168520u         /* bmdl_c::removeAnm */
#define F_FANM_CT   0x80168D10u
#define F_FANM_DT   0x80168D80u
#define F_FANM_SET  0x80168F10u          /* fanm_c::set(max, mode, rate, start) */
#define F_FANM_SET_FRAME 0x80168FE0u
#define F_FANM_IS_STOP 0x80169020u
#define F_FANM_CHECK_FRAME 0x801690E0u

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f
#define V(o, off) gm_u32(gm_u32(o) + (off))
#define TAIL(...) GM_RET(GM_CALLR(ctx->lr, __VA_ARGS__))      /* (LR stays the caller's) */

/* G3dObj::DynamicCast through the stack word at tmp; also hands back the "is it" flag the code
   keeps in a non-volatile register */
static gptr dyncast(GM_CTX, gptr obj, uint32_t type, gptr tmp, uint32_t *ok) {
    *ok = 0;
    if (!obj) return 0;
    gm_set_u32(tmp, type);
    if (GM_CALL(V(obj, 8), 2, obj, tmp)) *ok = 1;
    return *ok ? obj : 0;
}

/* setFrmCtrlDefault(anm, play mode): with mode 4 (inherit) the animation's policy picks once /
   loop; fanm_c::set(frame count, mode, 1, -1). The frame count goes through the stack as the
   compiler's int-to-float does. */
static void frm_default(GM_CTX, uint32_t addr, gptr self, gptr anm_p, uint32_t mode,
                        uint32_t pol_off, uint32_t nf_off, uint32_t k) {
    FN(addr);
    if (mode == 4) mode = (gm_u32(gm_u32(anm_p) + pol_off) == 0) ? 1 : 0;   /* (cntlzw >> 5) */
    gm_set_u32(f + 8, 0x43300000u);
    gm_set_u32(f + 12, gm_u16(gm_u32(anm_p) + nf_off) ^ 0x80000000u);
    uint64_t magic = ld64(base, ctx->r[2] - k);
    ctx->f[1].u = magic;
    double f2 = LF(ctx->r[2] - (k + 8)), f3 = LF(ctx->r[2] - (k + 4));
    ctx->f[2].d = ctx->ps1[2] = f2;
    ctx->f[0].u = ld64(base, f + 8);
    ctx->f[3].d = ctx->ps1[3] = f3;
    ctx->f[1].d = frsp(ctx->f[0].d - ctx->f[1].d);
    GM_CALL(F_FANM_SET, 2, self, mode);
}

/* ================================================================== banm_c */
static void banm_remove(GM_CTX, gptr self) {
    FN(0x80167F30); GM_NV_KEEP;
    NV_R(31, self);
    gptr o = gm_u32(self + 4);
    if (o) {
        GM_CALLR(0x80167F58u, F_DETACH_PARENT, 1, o);
        GM_CALLR(0x80167F60u, F_DESTROY, 1, gm_u32(self + 4));
        gm_set_u32(self + 4, 0);
    }
    gptr h = gm_u32(self + 8);
    if (h) { GM_CALLR(0x80167F78u, F_DESTROY_FRM, 1, h); gm_set_u32(self + 8, 0); }
}
static gptr banm_dtor(GM_CTX, gptr self, int32_t flags) {
    FN(0x80167EC0); GM_NV_KEEP;
    NV_R(31, flags); NV_R(30, self);
    if (self) {
        gm_set_u32(self, VT_BANM);
        NCALL(0x80167EF4u, banm_remove(GM_PASS, self));
        GM_CALLR(0x80167F00u, F_ALLOCATOR_DT, 2, self + 12, (uint32_t)-1);
        if (flags > 0) GM_CALLR(0x80167F10u, F_DELETE, 1, self);
    }
    return self;
}
/* createAllocator(allocator, size in / out): a frame heap for the animation object */
static uint32_t banm_create_allocator(GM_CTX, gptr self, gptr alloc, gptr psize) {
    FN(0x80167FA0); GM_NV_KEEP;
    NV_R(30, psize); NV_R(29, alloc); NV_R(28, self);
    uint32_t a = GM_CALLR(0x80167FD4u, F_FRM_COST, 2, gm_u32(psize), 32);
    NV_R(31, a);
    uint32_t b = GM_CALLR(0x80167FE4u, F_FRM_COST, 2, 0, 32);
    uint32_t size = ((a + 31) & ~31u) - b;
    NV_R(31, size);
    uint32_t c = GM_CALLR(0x80167FFCu, F_FRM_COST, 2, size, 32);
    gm_set_u32(psize, (c + 31) & ~31u);
    gptr h = GM_CALLR(0x80168024u, F_CREATE_FRM, 5, size, gm_u32(alloc + 20), BANM_HEAP_NAME, gm_u32(BANM_OPT), 0);
    gm_set_u32(self + 8, h);
    GM_CALLR(0x80168038u, F_ALLOCATOR_SETUP, 3, self + 12, h, 32);
    return 1;
}

/* ================================================================== anmChr_c */
#define CHR_FRM(self, anm_p, mode) frm_default(GM_PASS, 0x801654B0u, (self), (anm_p), (mode), 36, 32, 21536)   /* FNADDR */
static uint32_t chr_create(GM_CTX, gptr self, gptr mdl_p, gptr anm_p, gptr alloc, gptr psize) {
    FN(0x801650D0); GM_NV_KEEP;
    if (!alloc) alloc = gm_u32(L_ALLOCATOR);
    if (!psize) psize = f + 28;
    NV_R(27, self); NV_R(28, mdl_p); NV_R(29, anm_p); NV_R(30, alloc); NV_R(31, psize);
    gm_set_u32(f + 20, gm_u32(mdl_p)); gm_set_u32(f + 24, gm_u32(anm_p));
    GM_CALLR(0x80165138u, F_CHR_CT, 5, 0, psize, f + 24, f + 20, 0);
    if (!GM_CALLR(0x80165148u, F_BANM_ALLOC, 3, self, alloc, psize)) return 0;
    gm_set_u32(f + 12, gm_u32(mdl_p)); gm_set_u32(f + 16, gm_u32(anm_p));
    gptr o = GM_CALLR(0x80165180u, F_CHR_CT, 5, self + 12, f + 28, f + 16, f + 12, 0);
    gm_set_u32(self + 4, o);
    gm_set_u32(f + 8, gm_u32(mdl_p));
    if (!GM_CALLR(0x801651A0u, V(o, 48), 2, o, f + 8)) { GM_CALLR(0x801651BCu, V(self, 16), 1, self); return 0; }   /* Bind, else remove */
    NCALL(0x801651D4u, CHR_FRM(self, anm_p, 4));
    return 1;
}
/* setAnmAfter(model, anm, mode): a new AnmObjChrRes in the frame heap, put back where the old one
   sat in its parent (a blend) with the same weight */
static void chr_set_anm_after(GM_CTX, gptr self, gptr mdl, gptr anm_p, uint32_t mode) {
    FN(0x80165280); GM_NV_KEEP;
    gptr parent = gm_u32(gm_u32(self + 4) + 4);
    NV_R(24, self); NV_R(25, mdl); NV_R(26, anm_p); NV_R(31, parent); NV_R(27, mode);
    gptr node = 0; uint32_t idx = 0, ok;
    uint64_t w = 0;
    if (parent) {
        NV_R(30, 0);
        node = dyncast(GM_PASS, parent, T_CHR_NODE, f + 12, &ok);
        NV_R(30, ok); NV_R(29, node);
        int32_t n = (int32_t)gm_u32(node + 24);
        NV_R(28, 0);
        if (n > 0) {
            for (uint32_t c = (uint32_t)n, o4 = 0;;) {
                if (gm_u32(gm_u32(node + 28) + o4) == gm_u32(self + 4)) break;
                o4 += 4; idx++;
                if (--c == 0) break;
                GM_LOOP();
            }
        }
        NV_R(28, idx);
        GM_CALL(V(node, 76), 2, node, idx);                               /* GetWeight */
        w = ctx->f[1].u;
        ctx->f[31].u = w;
        GM_CALL(V(node, 64), 2, node, idx);                               /* Detach */
    }
    gptr o = gm_u32(self + 4);
    GM_CALL(V(o, 52), 1, o);                                              /* Release */
    GM_CALLR(0x80165394u, F_FRM_FREE, 2, gm_u32(self + 8), 3);
    gm_set_u32(f + 20, GM_CALLR(0x8016539Cu, F_GET_RES_MDL, 1, mdl));
    gm_set_u32(f + 24, gm_u32(anm_p));
    o = GM_CALLR(0x801653C0u, F_CHR_CT, 5, self + 12, f + 28, f + 24, f + 20, 0);
    gm_set_u32(self + 4, o);
    gm_set_u32(f + 16, GM_CALLR(0x801653CCu, F_GET_RES_MDL, 1, mdl));
    o = gm_u32(self + 4);
    GM_CALL(V(o, 48), 2, o, f + 16);                                      /* Bind */
    NCALL(0x801653F8u, CHR_FRM(self, anm_p, mode));
    if (!parent) return;
    o = gm_u32(self + 4);
    NV_R(31, o); NV_R(30, 0);
    o = dyncast(GM_PASS, o, T_CHR_RES, f + 8, &ok);
    NV_R(30, ok); NV_R(31, o);
    ctx->f[1].u = w;
    GM_CALL(V(node, 72), 2, node, idx);                                   /* SetWeight */
    GM_CALL(V(node, 60), 3, node, idx, o);                                /* Attach */
}
static void chr_set_anm(GM_CTX, gptr self, gptr mdl, gptr anm_p, uint32_t mode) {
    FN(0x801651F0); GM_NV_KEEP;
    NV_R(31, mode); NV_R(30, anm_p); NV_R(29, mdl); NV_R(28, self);
    uint32_t t = GM_CALLR(0x8016522Cu, V(self, 12), 1, self);                           /* getType */
    GM_CALLR(0x80165238u, F_REMOVE_ANM, 2, mdl, t);
    gm_set_u32(f + 8, gm_u32(anm_p));
    NCALL(0x80165254u, chr_set_anm_after(GM_PASS, self, mdl, f + 8, mode));
}

/* ================================================================== anmChrBlend_c */
static uint32_t blend_create(GM_CTX, gptr self, gptr mdl_p, uint32_t count, gptr alloc, gptr psize) {
    FN(0x80165520); GM_NV_KEEP;
    if (!alloc) alloc = gm_u32(L_ALLOCATOR);
    if (!psize) psize = f + 16;
    NV_R(27, self); NV_R(28, mdl_p); NV_R(29, count); NV_R(30, alloc); NV_R(31, psize);
    gm_set_u32(f + 12, gm_u32(mdl_p));
    GM_CALLR(0x8016557Cu, F_BLEND_CT, 4, 0, psize, f + 12, count);
    if (!GM_CALLR(0x8016558Cu, F_BANM_ALLOC, 3, self, alloc, psize)) return 0;
    gm_set_u32(f + 8, gm_u32(mdl_p));
    gm_set_u32(self + 4, GM_CALLR(0x801655B8u, F_BLEND_CT, 4, self + 12, f + 16, f + 8, count));
    return 1;
}
/* attach(index, AnmObjChrRes, weight) */
static void blend_attach(GM_CTX, gptr self, uint32_t idx, gptr res, double wt) {
    FN(0x801655E0); GM_NV_KEEP;
    uint32_t ok;
    gptr o = gm_u32(self + 4);
    NV_F(31, wt); NV_R(30, 0); NV_R(29, res); NV_R(28, idx); NV_R(31, o);
    o = dyncast(GM_PASS, o, T_CHR_BLEND, f + 8, &ok);
    NV_R(30, ok); NV_R(31, o);
    ctx->f[1].d = wt;
    GM_CALL(V(o, 72), 2, o, idx);                                         /* SetWeight */
    GM_CALL(V(o, 60), 3, o, idx, res);                                    /* Attach */
}

/* ================================================================== anmVis_c */
#define VIS_FRM(self, anm_p, mode) frm_default(GM_PASS, 0x80167E50u, (self), (anm_p), (mode), 36, 32, 21472)   /* FNADDR */
static uint32_t vis_create(GM_CTX, gptr self, gptr mdl_p, gptr anm_p, gptr alloc, gptr psize) {
    FN(0x80167C40); GM_NV_KEEP;
    if (!alloc) alloc = gm_u32(L_ALLOCATOR);
    if (!psize) psize = f + 28;
    NV_R(27, self); NV_R(28, mdl_p); NV_R(29, anm_p); NV_R(30, alloc); NV_R(31, psize);
    gm_set_u32(f + 20, gm_u32(mdl_p)); gm_set_u32(f + 24, gm_u32(anm_p));
    GM_CALLR(0x80167CA4u, F_VIS_CT, 4, 0, psize, f + 24, f + 20);
    if (!GM_CALLR(0x80167CB4u, F_BANM_ALLOC, 3, self, alloc, psize)) return 0;
    gm_set_u32(f + 12, gm_u32(mdl_p)); gm_set_u32(f + 16, gm_u32(anm_p));
    gptr o = GM_CALLR(0x80167CE8u, F_VIS_CT, 4, self + 12, f + 28, f + 16, f + 12);
    gm_set_u32(self + 4, o);
    gm_set_u32(f + 8, gm_u32(mdl_p));
    if (!GM_CALLR(0x80167D08u, V(o, 48), 2, o, f + 8)) { GM_CALLR(0x80167D24u, V(self, 16), 1, self); return 0; }
    NCALL(0x80167D3Cu, VIS_FRM(self, anm_p, 4));
    return 1;
}
static void vis_set_anm(GM_CTX, gptr self, gptr mdl, gptr anm_p, uint32_t mode) {
    FN(0x80167D60); GM_NV_KEEP;
    NV_R(31, mode); NV_R(30, anm_p); NV_R(29, mdl); NV_R(28, self);
    uint32_t t = GM_CALLR(0x80167D9Cu, V(self, 12), 1, self);
    GM_CALLR(0x80167DA8u, F_REMOVE_ANM, 2, mdl, t);
    gptr o = gm_u32(self + 4);
    GM_CALLR(0x80167DBCu, V(o, 52), 1, o);                                              /* Release */
    GM_CALLR(0x80167DC8u, F_FRM_FREE, 2, gm_u32(self + 8), 3);
    gm_set_u32(f + 12, GM_CALLR(0x80167DD0u, F_GET_RES_MDL, 1, mdl));
    gm_set_u32(f + 16, gm_u32(anm_p));
    o = GM_CALLR(0x80167DF0u, F_VIS_CT, 4, self + 12, f + 20, f + 16, f + 12);
    gm_set_u32(self + 4, o);
    gm_set_u32(f + 8, GM_CALLR(0x80167DFCu, F_GET_RES_MDL, 1, mdl));
    o = gm_u32(self + 4);
    GM_CALLR(0x80167E18u, V(o, 48), 2, o, f + 8);
    NCALL(0x80167E28u, VIS_FRM(self, anm_p, mode));
}

/* ================================================================== anmMatClr_c / anmTexPat_c / anmTexSrt_c */
typedef struct {
    uint32_t cc, ccr, csa, crl, cfd, cost, cr, dt, rm, sa, rl, play, play1, cdt;   /* the functions */
    uint32_t ra_ccr_cost, ra_ccr_frm, ra_csa_rel, ra_csa_frm, ra_cost_cc,             /* return addresses */
             ra_cr_cost, ra_cr_ccr, ra_cr_rel, ra_dt_rm, ra_sa_csa, ra_rl_crl, ra_play, ra_rm_banm;
    uint32_t res_ct, ovr_ct, t_ovr, t_res, vt_child, vt_self;                        /* nw4r classes */
    uint32_t pol_off, nf_off, k;                                                     /* setFrmCtrlDefault */
    int srt;                                                                         /* (anmTexSrt_c's null checks) */
} fam_t;
static const fam_t CLR = {
    0x80165820, 0x801658A0, 0x801659C0, 0x80165A80, 0x80165AE0, 0x80165B50, 0x80165C30, 0x80165E70,   /* FNADDR */
    0x80165EE0, 0x80165FD0, 0x80166110, 0x801661D0, 0x80166280, 0x801663B0,   /* FNADDR */
    0x80165900, 0x801659A0, 0x801659F0, 0x80165A54, 0x80165BD8, 0x80165CA0, 0x80165DB0, 0x80165E40,
    0x80165EA4, 0x80166084, 0x801661AC, 0x80166254, 0x80165FAC,
    0x80243D20, 0x80243B30, 0x802F8588, 0x802F85A8, 0x80329530, 0x80329518,
    36, 32, 21520, 0 };
static const fam_t PAT = {
    0x80166420, 0x801664A0, 0x801665C0, 0x80166680, 0x801666E0, 0x80166750, 0x80166830, 0x80166A70,   /* FNADDR */
    0x80166AE0, 0x80166BD0, 0x80166D10, 0x80166DD0, 0x80166E80, 0x80166F90,   /* FNADDR */
    0x80166500, 0x801665A0, 0x801665F0, 0x80166654, 0x801667D8, 0x801668A0, 0x801669B0, 0x80166A40,
    0x80166AA4, 0x80166C84, 0x80166DAC, 0x80166E54, 0x80166BAC,
    0x80245500, 0x80245300, 0x802F85F0, 0x802F8610, 0x80329560, 0x80329548,
    56, 48, 21504, 0 };
static const fam_t SRT = {
    0x80167000, 0x80167080, 0x801671B0, 0x80167270, 0x801672D0, 0x80167340, 0x80167420, 0x801676A0,   /* FNADDR */
    0x80167710, 0x80167800, 0x80167940, 0x80167A00, 0x80167AB0, 0x80167BD0,   /* FNADDR */
    0x801670E0, 0x80167190, 0x801671E0, 0x80167244, 0x801673C8, 0x80167490, 0x801675D4, 0x80167670,
    0x801676D4, 0x801678B4, 0x801679DC, 0x80167A84, 0x801677DC,
    0x80246B00, 0x80246900, 0x802F8658, 0x802F8678, 0x80329590, 0x80329578,
    40, 32, 21488, 1 };
#define CHILD(self, i) (gm_u32((self) + 40) + (uint32_t)((int32_t)(i) * 56))

/* child_c::heapCost(model, anm, aligned) */
static uint32_t ch_cost(GM_CTX, const fam_t *F, gptr mdl_p, gptr anm_p, uint32_t aligned) {
    FN(F->cc); GM_NV_KEEP;
    NV_R(31, aligned);
    gm_set_u32(f + 16, 0); gm_set_u32(f + 8, gm_u32(mdl_p)); gm_set_u32(f + 12, gm_u32(anm_p));
    GM_CALL(F->res_ct, 5, 0, f + 16, f + 12, f + 8, 0);
    if (aligned) gm_set_u32(f + 16, (GM_CALL(F_FRM_COST, 2, gm_u32(f + 16), 32) + 31) & ~31u);
    return gm_u32(f + 16);
}
static void ch_release(GM_CTX, const fam_t *F, gptr self) {
    FN(F->crl); GM_NV_KEEP;
    NV_R(31, self);
    gptr o = gm_u32(self + 4);
    if (!o) return;
    GM_CALL(V(o, 52), 1, o);                                              /* Release */
    GM_CALL(F_FRM_FREE, 2, gm_u32(self + 8), 3);
    gm_set_u32(self + 4, 0);
}
#define CH_FRM(self, anm_p, mode) frm_default(GM_PASS, F->cfd, (self), (anm_p), (mode), F->pol_off, F->nf_off, F->k)
/* child_c::create(model, anm, allocator, size out) */
static uint32_t ch_create(GM_CTX, const fam_t *F, gptr self, gptr mdl_p, gptr anm_p, gptr alloc, gptr psize) {
    FN(F->ccr); GM_NV_KEEP;
    if (!alloc) alloc = gm_u32(L_ALLOCATOR);
    if (!psize) psize = f + 28;
    NV_R(27, self); NV_R(28, mdl_p); NV_R(29, anm_p); NV_R(30, alloc); NV_R(31, psize);
    gm_set_u32(f + 20, gm_u32(anm_p)); gm_set_u32(f + 24, gm_u32(mdl_p));
    gm_set_u32(psize, NCALL(F->ra_ccr_cost, ch_cost(GM_PASS, F, f + 24, f + 20, 0)));
    if (!GM_CALL(F_BANM_ALLOC, 3, self, alloc, psize)) return 0;
    gm_set_u32(f + 12, gm_u32(mdl_p)); gm_set_u32(f + 16, gm_u32(anm_p));
    gptr o = GM_CALL(F->res_ct, 5, self + 12, 0, f + 16, f + 12, 0);
    gm_set_u32(self + 4, o);
    if (F->srt && !o) return 0;
    gm_set_u32(f + 8, gm_u32(mdl_p));
    if (!GM_CALL(V(o, 48), 2, o, f + 8)) { GM_CALL(V(self, 16), 1, self); return 0; }
    NCALL(F->ra_ccr_frm, CH_FRM(self, anm_p, 4));
    return 1;
}
/* child_c::setAnm(model, anm, mode) */
static void ch_set_anm(GM_CTX, const fam_t *F, gptr self, gptr mdl, gptr anm_p, uint32_t mode) {
    FN(F->csa); GM_NV_KEEP;
    NV_R(31, mode); NV_R(30, anm_p); NV_R(29, mdl); NV_R(28, self);
    NCALL(F->ra_csa_rel, ch_release(GM_PASS, F, self));
    gm_set_u32(f + 12, GM_CALL(F_GET_RES_MDL, 1, mdl));
    gm_set_u32(f + 16, gm_u32(anm_p));
    gm_set_u32(self + 4, GM_CALL(F->res_ct, 5, self + 12, 0, f + 16, f + 12, 0));
    gm_set_u32(f + 8, GM_CALL(F_GET_RES_MDL, 1, mdl));
    gptr o = gm_u32(self + 4);
    GM_CALL(V(o, 48), 2, o, f + 8);
    NCALL(F->ra_csa_frm, CH_FRM(self, anm_p, mode));
}
static gptr ch_dtor(GM_CTX, const fam_t *F, gptr self, int32_t flags) {
    FN(F->cdt); GM_NV_KEEP;
    NV_R(31, flags); NV_R(30, self);
    if (self) { GM_CALL(F_FANM_DT, 2, self, 0); if (flags > 0) GM_CALL(F_DELETE, 1, self); }
    return self;
}
/* heapCost(model, anm, count, aligned) */
static uint32_t ovr_cost(GM_CTX, const fam_t *F, gptr mdl_p, gptr anm_p, int32_t count, uint32_t aligned) {
    FN(F->cost); GM_NV_KEEP;
    NV_R(31, aligned); NV_R(30, count); NV_R(29, anm_p); NV_R(28, mdl_p);
    gm_set_u32(f + 20, 0); gm_set_u32(f + 16, gm_u32(mdl_p));
    GM_CALL(F->ovr_ct, 4, 0, f + 20, f + 16, count);
    gm_set_u32(f + 20, gm_u32(f + 20) + (((uint32_t)(count * 56) + 31) & ~31u));
    gm_set_u32(f + 8, gm_u32(anm_p)); gm_set_u32(f + 12, gm_u32(mdl_p));
    uint32_t c = NCALL(F->ra_cost_cc, ch_cost(GM_PASS, F, f + 12, f + 8, 1));
    uint32_t s = gm_u32(f + 20) + (uint32_t)count * ((c + 31) & ~31u);
    gm_set_u32(f + 20, s);
    if (aligned) s = (GM_CALL(F_FRM_COST, 2, s, 32) + 31) & ~31u;
    return s;
}
/* create(model, anm, allocator, size out, count): the override object and its children, the
   first one attached */
static uint32_t ovr_create(GM_CTX, const fam_t *F, gptr self, gptr mdl_p, gptr anm_p, gptr alloc, gptr psize, int32_t count) {
    FN(F->cr); GM_NV_KEEP;
    if (!alloc) alloc = gm_u32(L_ALLOCATOR);
    gm_set_u32(f + 36, 0);
    if (!psize) psize = f + 36;
    NV_R(28, self); NV_R(29, mdl_p); NV_R(30, anm_p); NV_R(22, alloc); NV_R(21, psize); NV_R(31, count);
    gm_set_u32(f + 28, gm_u32(anm_p)); gm_set_u32(f + 32, gm_u32(mdl_p));
    gm_set_u32(psize, NCALL(F->ra_cr_cost, ovr_cost(GM_PASS, F, f + 32, f + 28, count, 0)));
    if (!GM_CALL(F_BANM_ALLOC, 3, self, alloc, psize)) return 0;
    gm_set_u32(f + 24, gm_u32(mdl_p));
    gptr o = GM_CALL(F->ovr_ct, 4, self + 12, 0, f + 24, count);
    gm_set_u32(self + 4, o);
    if (F->srt && !o) return 0;
    gptr ch = GM_CALL(F_MEM_ALLOC, 2, self + 12, ((uint32_t)(count * 56) + 31) & ~31u);
    gm_set_u32(self + 40, ch);
    if (F->srt && !ch) { GM_CALL(V(self, 16), 1, self); return 0; }
    uint32_t ok, r25;
    gptr ovr = gm_u32(self + 4);
    NV_R(23, ovr); NV_R(25, 0);
    ovr = dyncast(GM_PASS, ovr, F->t_ovr, f + 12, &ok);
    r25 = ok;
    NV_R(25, r25); NV_R(23, ovr);
    gptr c = gm_u32(self + 40);
    NV_R(27, F->t_res); NV_R(26, F->vt_child); NV_R(22, c); NV_R(21, 0);
    for (int32_t i = 0; i < count; ) {
        GM_LOOP();
        gptr p = GM_CALL(F_NEW_AT, 2, 56, c);
        NV_R(25, p);
        if (p) { GM_CALL(F_FANM_CT, 1, p); gm_set_u32(p, F->vt_child); }
        gm_set_u32(f + 16, gm_u32(anm_p)); gm_set_u32(f + 20, gm_u32(mdl_p));
        if (!NCALL(F->ra_cr_ccr, ch_create(GM_PASS, F, c, f + 20, f + 16, self + 12, 0))) {
            GM_CALL(F_DESTROY_FRM, 1, gm_u32(self + 8));
            if (F->srt) GM_CALL(F_HEAP_FREE, 2, gm_u32(self + 8), 0);
            return 0;
        }
        if (i == 0) {
            gptr r = gm_u32(c + 4);
            NV_R(25, r); NV_R(24, 0);
            r = dyncast(GM_PASS, r, F->t_res, f + 8, &ok);
            NV_R(24, ok);
            GM_CALL(V(ovr, 60), 3, ovr, (uint32_t)i, r);                  /* Attach */
        } else NCALL(F->ra_cr_rel, ch_release(GM_PASS, F, c));
        c += 56; i++;
        NV_R(22, c); NV_R(21, i);
    }
    return 1;
}
static void ovr_remove(GM_CTX, const fam_t *F, gptr self) {
    FN(F->rm); GM_NV_KEEP;
    uint32_t ok;
    gptr o = gm_u32(self + 4);
    NV_R(30, 0); NV_R(28, self); NV_R(31, o);
    o = dyncast(GM_PASS, o, F->t_ovr, f + 8, &ok);
    NV_R(30, ok); NV_R(31, o);
    if (o && gm_u32(self + 40)) {
        int32_t n = (int32_t)gm_u32(o + 24);
        NV_R(31, n); NV_R(29, 0); NV_R(30, 0);
        for (int32_t i = 0; i < n; i++) {
            GM_LOOP();
            gptr c = gm_u32(self + 40) + (uint32_t)(i * 56);
            GM_CALL(V(c, 16), 1, c);                                      /* child_c::remove */
            NV_R(30, (i + 1) * 56); NV_R(29, i + 1);
        }
        gm_set_u32(self + 40, 0);
    }
    NCALL(F->ra_rm_banm, banm_remove(GM_PASS, self));
}
static gptr ovr_dtor(GM_CTX, const fam_t *F, gptr self, int32_t flags) {
    FN(F->dt); GM_NV_KEEP;
    NV_R(31, flags); NV_R(30, self);
    if (self) {
        gm_set_u32(self, F->vt_self);
        NCALL(F->ra_dt_rm, ovr_remove(GM_PASS, F, self));
        GM_CALL(F_BANM_DT, 2, self, 0);
        if (flags > 0) GM_CALL(F_DELETE, 1, self);
    }
    return self;
}
/* setAnm(model, anm, index, mode) */
static void ovr_set_anm(GM_CTX, const fam_t *F, gptr self, gptr mdl, gptr anm_p, int32_t idx, uint32_t mode) {
    FN(F->sa); GM_NV_KEEP;
    uint32_t ok;
    gptr o = gm_u32(self + 4);
    NV_R(25, self); NV_R(26, mdl); NV_R(27, anm_p); NV_R(28, idx); NV_R(29, mode); NV_R(30, 0); NV_R(31, o);
    o = dyncast(GM_PASS, o, F->t_ovr, f + 12, &ok);
    NV_R(30, ok); NV_R(31, o);
    GM_CALL(V(o, 64), 2, o, (uint32_t)idx);                               /* Detach */
    gm_set_u32(f + 16, gm_u32(anm_p));
    uint32_t off = (uint32_t)(idx * 56);
    NV_R(30, off);
    NCALL(F->ra_sa_csa, ch_set_anm(GM_PASS, F, gm_u32(self + 40) + off, mdl, f + 16, mode));
    gptr r = gm_u32(gm_u32(self + 40) + off + 4);
    NV_R(29, 0); NV_R(30, r);
    r = dyncast(GM_PASS, r, F->t_res, f + 8, &ok);
    NV_R(29, ok);
    GM_CALL(V(o, 60), 3, o, (uint32_t)idx, r);                            /* Attach */
}
/* releaseAnm(index) */
static void ovr_release(GM_CTX, const fam_t *F, gptr self, int32_t idx) {
    FN(F->rl); GM_NV_KEEP;
    uint32_t ok;
    gptr o = gm_u32(self + 4);
    NV_R(30, 0); NV_R(29, idx); NV_R(28, self); NV_R(31, o);
    gptr p = dyncast(GM_PASS, o, F->t_ovr, f + 8, &ok);
    NV_R(30, ok);
    GM_CALL(V(p, 64), 2, p, (uint32_t)idx);                               /* Detach */
    NCALL(F->ra_rl_crl, ch_release(GM_PASS, F, CHILD(self, idx)));
}
static void ovr_play1(GM_CTX, const fam_t *F, gptr self, int32_t idx) {
    FN(F->play1); GM_NV_KEEP;
    uint32_t off = (uint32_t)(idx * 56);
    NV_R(31, off); NV_R(30, self);
    if (GM_CALL(F_BANM_BOUND, 1, gm_u32(self + 40) + off)) {
        gptr c = gm_u32(self + 40) + off;
        GM_CALL(V(c, 20), 1, c);                                          /* (fanm_c::play) */
    }
}
static void ovr_play(GM_CTX, const fam_t *F, gptr self) {
    FN(F->play); GM_NV_KEEP;
    uint32_t ok;
    gptr o = gm_u32(self + 4);
    NV_R(30, 0); NV_R(29, self); NV_R(31, o);
    o = dyncast(GM_PASS, o, F->t_ovr, f + 8, &ok);
    int32_t n = (int32_t)gm_u32(o + 24);
    NV_R(30, n);
    for (int32_t i = 0; i < n; i++) {
        GM_LOOP();
        NV_R(31, i);
        NCALL(F->ra_play, ovr_play1(GM_PASS, F, self, i));
    }
}

/* ================================================================== hle entry points
   On (73): 37 are reached by the test runs from recompiled code; the children's create / setAnm
   / release / heapCost / setFrmCtrlDefault, play(index), anmChr_c::setAnmAfter and the blend's
   attach(AnmObjChrRes) run inside them; the accessors share the reached ones' code but for the
   target, getType returns a constant. Written but off (not reached): anmVis_c (create, setAnm,
   setFrmCtrlDefault), the override classes' releaseAnm(index) and child destructors,
   getFrameMax / getFrameStart, anmTexSrt_c::setFrameStart. */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
/* banm_c */
E(__dt__Q23m3d6banm_cFv) { GM_LR_KEEP; GM_RET(banm_dtor(GM_PASS, A(0), (int32_t)A(1))); }      /* banm_c::~banm_c */
E(detach__Q23m3d6banm_cFv) { banm_remove(GM_PASS, A(0)); }                                     /* ::remove */
E(setupHeap__Q23m3d6banm_cFv) { GM_RET(banm_create_allocator(GM_PASS, A(0), A(1), A(2))); }   /* ::createAllocator */
/* anmChr_c */
E(setup__Q23m3d8anmChr_cFQ34nw4r3g3d6ResMdlQ34nw4r3g3d9ResAnmChrP12mAllocator_cPUi) { GM_LR_KEEP; GM_RET(chr_create(GM_PASS, A(0), A(1), A(2), A(3), A(4))); }   /* ::create */
E(bind__Q23m3d8anmChr_cFPQ23m3d5mdl_cQ34nw4r3g3d9ResAnmChrb) { GM_LR_KEEP; chr_set_anm(GM_PASS, A(0), A(1), A(2), A(3)); }   /* ::setAnm */
E(internalBind__Q23m3d8anmChr_cFv) { GM_LR_KEEP; chr_set_anm_after(GM_PASS, A(0), A(1), A(2), A(3)); }   /* ::setAnmAfter */
E(fn_801654B0) { CHR_FRM(A(0), A(1), A(2)); }                                                  /* ::setFrmCtrlDefault */
/* anmChrBlend_c */
E(fn_80165520) { GM_RET(blend_create(GM_PASS, A(0), A(1), A(2), A(3), A(4))); }                /* ::create */
E(fn_801655E0) { blend_attach(GM_PASS, A(0), A(1), A(2), ctx->f[1].d); }                       /* ::attach(index, AnmObjChrRes, weight) */
E(fn_801656C0) {                                                                               /* ::attach(index, anmChr_c, weight) */
    GM_LR_KEEP; FN(0x801656C0); GM_NV_KEEP;
    gptr self = A(0); uint32_t idx = A(1), ok; double wt = ctx->f[1].d;
    gptr o = gm_u32(A(2) + 4);
    NV_F(31, wt); NV_R(30, 0); NV_R(29, idx); NV_R(28, self); NV_R(31, o);
    gptr r = dyncast(GM_PASS, o, T_CHR_RES, f + 8, &ok);
    NV_R(30, ok);
    ctx->f[1].d = wt;
    NCALL(0x80165750u, blend_attach(GM_PASS, self, idx, r, wt));
}
E(fn_80165780) {                                                                               /* ::detach(index) */
    FN(0x80165780); GM_NV_KEEP;
    uint32_t idx = A(1), ok;
    gptr o = gm_u32(A(0) + 4);
    NV_R(30, 0); NV_R(29, idx); NV_R(31, o);
    gptr p = dyncast(GM_PASS, o, T_CHR_BLEND, f + 8, &ok);
    NV_R(30, ok);
    GM_CALL(V(p, 64), 2, p, idx);
}
/* anmVis_c */
E(setup__Q23m3d8anmVis_cFQ34nw4r3g3d6ResMdlQ34nw4r3g3d9ResAnmVisP12mAllocator_cPUi) { GM_LR_KEEP; GM_RET(vis_create(GM_PASS, A(0), A(1), A(2), A(3), A(4))); }   /* ::create */
E(bind__Q23m3d8anmVis_cFPQ23m3d5mdl_cQ34nw4r3g3d9ResAnmVisb) { GM_LR_KEEP; vis_set_anm(GM_PASS, A(0), A(1), A(2), A(3)); }   /* ::setAnm */
E(internalBind__Q23m3d8anmVis_cFv) { VIS_FRM(A(0), A(1), A(2)); }                              /* ::setFrmCtrlDefault */

/* the override classes: one block per class */
#define OVR_ENTRIES(F, n_cc, n_ccr, n_csa, n_crl, n_cfd, n_cost, n_cr, n_dt, n_rm, n_sa, n_rl, n_play, n_play1, n_cdt, n_ctype) \
E(n_cc)    { GM_RET(ch_cost(GM_PASS, &F, A(0), A(1), A(2))); }                                     /* child_c::heapCost */ \
E(n_ccr)   { GM_LR_KEEP; GM_RET(ch_create(GM_PASS, &F, A(0), A(1), A(2), A(3), A(4))); }          /* child_c::create */ \
E(n_csa)   { GM_LR_KEEP; ch_set_anm(GM_PASS, &F, A(0), A(1), A(2), A(3)); }                       /* child_c::setAnm */ \
E(n_crl)   { ch_release(GM_PASS, &F, A(0)); }                                                      /* child_c::releaseAnm */ \
E(n_cfd)   { frm_default(GM_PASS, F.cfd, A(0), A(1), A(2), F.pol_off, F.nf_off, F.k); }            /* child_c::setFrmCtrlDefault */ \
E(n_cost)  { GM_LR_KEEP; GM_RET(ovr_cost(GM_PASS, &F, A(0), A(1), (int32_t)A(2), A(3))); }        /* ::heapCost */ \
E(n_cr)    { GM_LR_KEEP; GM_RET(ovr_create(GM_PASS, &F, A(0), A(1), A(2), A(3), A(4), (int32_t)A(5))); }   /* ::create */ \
E(n_dt)    { GM_LR_KEEP; GM_RET(ovr_dtor(GM_PASS, &F, A(0), (int32_t)A(1))); }                    /* ::~ */ \
E(n_rm)    { GM_LR_KEEP; ovr_remove(GM_PASS, &F, A(0)); }                                                      /* ::remove */ \
E(n_sa)    { GM_LR_KEEP; ovr_set_anm(GM_PASS, &F, A(0), A(1), A(2), (int32_t)A(3), A(4)); }       /* ::setAnm */ \
E(n_rl)    { GM_LR_KEEP; ovr_release(GM_PASS, &F, A(0), (int32_t)A(1)); }                         /* ::releaseAnm */ \
E(n_play)  { GM_LR_KEEP; ovr_play(GM_PASS, &F, A(0)); }                                           /* ::play */ \
E(n_play1) { ovr_play1(GM_PASS, &F, A(0), (int32_t)A(1)); }                                        /* ::play(index) */ \
E(n_cdt)   { GM_RET(ch_dtor(GM_PASS, &F, A(0), (int32_t)A(1))); }                                  /* child_c::~child_c */ \
E(n_ctype) { GM_RET(F.k == 21520 ? 2 : F.k == 21504 ? 3 : 4); }                                    /* child_c::getType */
OVR_ENTRIES(CLR, fn_80165820, fn_801658A0, fn_801659C0, fn_80165A80, fn_80165AE0, fn_80165B50,
            setup__Q23m3d8anmClr_cFQ34nw4r3g3d6ResMdlQ34nw4r3g3d9ResAnmClrP12mAllocator_cPUii,
            __dt__Q23m3d8anmClr_cFv, fn_80165EE0, bind__Q23m3d8anmClr_cFPQ23m3d5mdl_cQ34nw4r3g3d9ResAnmClrii,
            fn_80166110, fn_801661D0, fn_80166280, fn_801663B0, fn_80166410)
OVR_ENTRIES(PAT, fn_80166420, fn_801664A0, fn_801665C0, fn_80166680, fn_801666E0, fn_80166750,
            setup__Q23m3d11anmTexPat_cFQ34nw4r3g3d6ResMdlQ34nw4r3g3d12ResAnmTexPatP12mAllocator_cPUii,
            __dt__Q23m3d11anmTexPat_cFv, detach__Q23m3d11anmTexPat_cFv, bindEntry__Q23m3d11anmTexPat_cFv,
            fn_80166D10, process__Q23m3d11anmTexPat_cFv, processOneEntry__Q23m3d11anmTexPat_cFv, fn_80166F90, fn_80166FF0)
OVR_ENTRIES(SRT, fn_80167000, fn_80167080, fn_801671B0, fn_80167270, fn_801672D0, AllocSizeForAnmTexSrt,
            setup__Q23m3d11anmTexSrt_cFQ34nw4r3g3d6ResMdlQ34nw4r3g3d12ResAnmTexSrtP12mAllocator_cPUii,
            __dt__Q23m3d11anmTexSrt_cFv, detach__Q23m3d11anmTexSrt_cFv, bindEntry__Q23m3d11anmTexSrt_cFPQ23m3d5mdl_cQ34nw4r3g3d12ResAnmTexSrtii,
            sub80167a80__Q23m3d11anmTexSrt_cFv, process__Q23m3d11anmTexSrt_cFv, processOneEntry__Q23m3d11anmTexSrt_cFi, fn_80167BD0, fn_80167C30)

/* the per-index accessors: child idx (r4; r5 for setPlayMode) as a tail call */
#define ACC(name, fn) E(name) { TAIL(fn, 1, CHILD(A(0), A(1))); }
ACC(getFrameForEntry__Q23m3d8anmClrFv, F_BANM_FRAME)                                           /* anmMatClr_c::getFrame */
ACC(setFrameForEntry__Q23m3d8anmClrFfi, F_FANM_SET_FRAME)                                      /* ::setFrame */
ACC(getUpdateRateForEntry__Q23m3d8anmClrFv, F_BANM_RATE)                                       /* ::getRate */
ACC(setUpdateRateForEntry__Q23m3d8anmClrFfi, F_BANM_SET_RATE)                                  /* ::setRate */
ACC(isEntryAnimationDone__Q23m3d8anmClrFv, F_FANM_IS_STOP)                                     /* ::isStop */
ACC(queryEntrySomething__Q23m3d8anmClrFv, F_FANM_CHECK_FRAME)                                  /* ::checkFrame */
ACC(getFrameForEntry__Q23m3d11anmTexPat_cFi, F_BANM_FRAME)                                     /* anmTexPat_c */
ACC(setFrameForEntry__Q23m3d11anmTexPat_cFfi, F_FANM_SET_FRAME)
ACC(getUpdateRateForEntry__Q23m3d11anmTexPat_cFv, F_BANM_RATE)
ACC(setUpdateRateForEntry__Q23m3d11anmTexPat_cFfi, F_BANM_SET_RATE)
ACC(isEntryAnimationDone__Q23m3d11anmTexPat_cFv, F_FANM_IS_STOP)
ACC(queryEntrySomething__Q23m3d11anmTexPat_cFv, F_FANM_CHECK_FRAME)
ACC(getFrameForEntry__Q23m3d11anmTexSrt_cFi, F_BANM_FRAME)                                     /* anmTexSrt_c */
ACC(setFrameForEntry__Q23m3d11anmTexSrt_cFfi, F_FANM_SET_FRAME)
ACC(getUpdateRateForEntry__Q23m3d11anmTexSrt_cFi, F_BANM_RATE)
ACC(setUpdateRateForEntry__Q23m3d11anmTexSrt_cFfi, F_BANM_SET_RATE)
ACC(isEntryAnimationDone__Q23m3d11anmTexSrt_cFi, F_FANM_IS_STOP)
#define SET_MODE(name) E(name) { gm_set_u8(CHILD(A(0), A(2)) + 52, (uint8_t)A(1)); }            /* ::setPlayMode */
SET_MODE(setEntryByte34__Q23m3d8anmClrFUci)
SET_MODE(setEntryByte34__Q23m3d11anmTexPat_cFUci)
SET_MODE(setEntryByte34__Q23m3d11anmTexSrt_cFUci)
#define GET_F(name, off) E(name) { double v = LF(CHILD(A(0), A(1)) + (off)); ctx->f[1].d = ctx->ps1[1] = v; }
GET_F(getEntryField28__Q23m3d8anmClrFv, 40)                                                    /* ::getFrameMax */
GET_F(fn_80166380, 44)                                                                         /* ::getFrameStart */
GET_F(getEntryField28__Q23m3d11anmTexPat_cFv, 40)
GET_F(getEntryField28__Q23m3d11anmTexSrt_cFi, 40)
E(getEntryField2C__Q23m3d11anmTexSrt_cFi) { SF(CHILD(A(0), A(1)) + 44, ctx->f[1].d); }         /* anmTexSrt_c::setFrameStart */
E(vf0C__Q23m3d8anmClr_cFv) { GM_RET(2); }                                                      /* ::getType */
E(vf0C__Q23m3d11anmTexPat_cFv) { GM_RET(3); }
E(vf0C__Q23m3d11anmTexSrt_cFv) { GM_RET(4); }
