/* gm_f_base.c - fBase_c, the base of everything the framework runs (actors, scenes, the world
 * map's pieces ...): its constructor / destructor, the create / execute / draw / delete steps
 * ("packs"), the connect step that moves it between the framework's lists, delete requests, its
 * heap, and making new bases from a profile (f_base.cpp). Track B (gm.h, docs/DECOMP.md),
 * instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/framework/f_base.cpp) and checked line by line
 * against the recompiled USA rev 2 code; this game's layout differs a little from the decomp's
 * headers (below).
 *
 * fBase_c (0x64 bytes):
 *   +0x00 unique ID   +0x04 param   +0x08 profile name (u16)
 *   +0x0A lifecycle state (u8: 0 creating, 1 active, 2 deleting)   +0x0B delete requested
 *   +0x0C execute deferred (to the connect step)   +0x0D create retry deferred
 *   +0x0E group type   +0x0F process control flags (1 / 2: execute off (root / own),
 *                                                   4 / 8: draw off (root / own))
 *   +0x10 the connect tree node (cTreeNd_c + 0x10 owner)
 *   +0x24 the main list node (create / execute / delete; + 0x2C owner, 0x30 order, 0x32 new order)
 *   +0x34 the draw list node (+ 0x3C owner, 0x40 order, 0x42 new order)
 *   +0x44 the search list node (+ 0x4C owner)
 *   +0x50 the arc list (dRes?)   +0x54 base links (cLineMg_c)   +0x5C its heap   +0x60 vtable
 * vtable: +0x38 deleteReady, +0x44 createHeap, +0x48 the deleting destructor. */
#include "gm.h"
#include "gm_nv.h"

/* gm_c_list.c / gm_f_list.c */
int  cLineMg_addTopLineNode(gptr self, gptr node);
int  cLineMg_addLastLineNode(gptr self, gptr node);
int  cLineMg_removeLineNode(gptr self, gptr node);
void cTreeNd_forcedClear(gptr self);
int  cTreeMg_addTreeNode(GM_CTX, gptr self, gptr node, gptr parent);
int  cTreeMg_removeTreeNode(gptr self, gptr node);
gptr cTreeNd_getTreeNext(GM_CTX, gptr self);
gptr cTreeNd_getTreeNextNotChild(GM_CTX, gptr self);
int  fLiMgBaFuPr_insertLineNodePriority(GM_CTX, gptr self, gptr node);
void fLiNdBaLink_clearData(gptr self);

#define SDA 0x8042F680u
/* fManager_c's lists (static) */
#define MG_CONNECT  0x80377A10u          /* fTrMgBaFu_c: the connect tree */
#define MG_CREATE   0x80377A20u          /* fLiMgBaFuPr_c ... */
#define MG_EXECUTE  0x80377A34u
#define MG_DRAW     0x80377A48u
#define MG_DELETE   0x80377A5Cu
#define MG_SEARCH   0x80377A70u          /* fLiMgBa_c [8], by unique ID & 7 */
#define NOW_LOOP    (SDA - 0x6228)       /* fManager_c::m_nowLoopProc: 1 connect 2 create 3 execute 4 delete 5 draw */
#define ROOT_ID     (SDA - 0x6230)       /* fBase_c::m_rootUniqueID */
#define TMP_PARAM   (SDA - 0x52E4)       /* fBase_c::m_tmpCt* */
#define TMP_PROF    (SDA - 0x52E8)
#define TMP_GROUP   (SDA - 0x52E0)
#define TMP_PARENT  (SDA - 0x52DC)
#define PROF_TBL    (SDA - 0x52C8)       /* fProfListMg_c::m_data_p: profile name -> fBaseProfile_c * */
#define GAME_HEAP   0x80377C48u          /* mHeap::g_gameHeaps[0] */
#define VTABLE      0x80329410u          /* fBase_c's vtable */
#define PACKS       0x80329350u          /* the packs' pointers to member functions: create, delete,
                                            execute, draw - each do / pre / post, 12 bytes apiece */
/* guest functions */
#define F_ARC_CHECK_DELETE 0x80161A70u
#define F_ARC_DELETE       0x80161920u
#define F_HEAP_ALLOC       0x802B8CC0u   /* EGG::Heap::alloc(size, align, heap) */
#define F_HEAP_FREE        0x802B8F70u   /* EGG::Heap::free(p, heap) */
#define F_MEMSET           0x800046B4u
#define F_FRMHEAP_CREATE   0x8016E9B0u   /* mHeap::createFrmHeapToCurrent(size, parent, name, align, opt) */
#define F_HEAP_RESTORE     0x8016E980u   /* mHeap::restoreCurrentHeap */
#define F_FRMHEAP_DESTROY  0x8016E740u
#define F_FRMHEAP_ADJUST   0x8016E760u
#define HEAP_NAME          0x803293E0u

#define B_ID     0x00
#define B_PARAM  0x04
#define B_PROF   0x08
#define B_STATE  0x0A
#define B_DELREQ 0x0B
#define B_DEFEXE 0x0C
#define B_DEFCRT 0x0D
#define B_GROUP  0x0E
#define B_FLAGS  0x0F
#define B_CONN   0x10
#define B_MAIN   0x24
#define B_DRAW   0x34
#define B_SEARCH 0x44
#define B_ARC    0x50
#define B_LINKS  0x54
#define B_HEAP   0x5C
#define B_VT     0x60
enum { ST_CREATING = 0, ST_ACTIVE = 1, ST_DELETING = 2 };
enum { PS_CANCELED = 0, PS_ERROR = 1, PS_SUCCESS = 2, PS_WAITING = 3 };


/* a CodeWarrior pointer to member function (__ptmf_scall): +0 this adjustment, +4 vtable offset
   (< 0: not virtual), +8 the function, or for a virtual one the offset of the vtable pointer */
static uint32_t ptmf_call(GM_CTX, uint32_t ra, gptr pm, gptr obj, int n, uint32_t a1) {   /* (ra: the bl to __ptmf_scall's, a tail call) */
    gptr self = obj + gm_u32(pm);
    int32_t vofs = gm_s32(pm + 4); uint32_t fn = gm_u32(pm + 8);
    if (vofs >= 0) fn = gm_u32(gm_u32(self + fn) + (uint32_t)vofs);
    return n > 1 ? GM_CALLR(ra, fn, 2, self, a1) : GM_CALLR(ra, fn, 1, self);
}

/* ---- the tree ---- */
gptr fBase_getConnectParent(gptr self) { gptr n = gm_ptr(self + B_CONN + 0x0); return n ? gm_ptr(n + 0x10) : 0; }
gptr fBase_getConnectChild(gptr self)  { gptr n = gm_ptr(self + B_CONN + 0x4); return n ? gm_ptr(n + 0x10) : 0; }
gptr fBase_getConnectBrNext(gptr self) { gptr n = gm_ptr(self + B_CONN + 0xC); return n ? gm_ptr(n + 0x10) : 0; }
uint32_t fManager_getSearchTableNum(gptr connect_node) { return gm_u32(gm_ptr(connect_node + 0x3C)) & 7; }  /* (the search node's owner's ID) */

/* the process control flags follow the parent's: off if the parent's (either kind) is off */
static void follow_parent(gptr self, int clear) {
    gptr parent = fBase_getConnectParent(self);
    if (!parent) return;
    uint8_t f = gm_u8(parent + B_FLAGS);
    if (f & 3) gm_set_u8(self + B_FLAGS, gm_u8(self + B_FLAGS) | 2);
    else if (clear && (gm_u8(self + B_FLAGS) & 2)) gm_set_u8(self + B_FLAGS, gm_u8(self + B_FLAGS) & 0xFD);
    f = gm_u8(parent + B_FLAGS);
    if (f & 0xC) gm_set_u8(self + B_FLAGS, gm_u8(self + B_FLAGS) | 8);
    else if (clear && (gm_u8(self + B_FLAGS) & 8)) gm_set_u8(self + B_FLAGS, gm_u8(self + B_FLAGS) & 0xF7);
}

/* ---- construction ---- */
gptr fBase_ctor(GM_CTX, gptr self) { GM_FN(0x80161AD0);
    gm_set_ptr(self + B_VT, VTABLE);
    gm_set_u32(self + B_ID, gm_u32(ROOT_ID));
    gm_set_u32(self + B_PARAM, gm_u32(TMP_PARAM));
    gm_set_u16(self + B_PROF, gm_u16(TMP_PROF));
    gm_set_u8(self + B_GROUP, gm_u8(TMP_GROUP));
    GM_NV_KEEP;
    NV_R(31, self);
    GM_CALLR(0x80161B18u, 0x80161530u, 1, self + B_CONN);                  /* cTreeNd_c::cTreeNd_c */
    gm_set_ptr(self + B_CONN + 0x10, self);
    gm_set_ptr(self + B_MAIN, 0); gm_set_ptr(self + B_MAIN + 4, 0); gm_set_ptr(self + B_MAIN + 8, self);
    gm_set_u16(self + B_MAIN + 0xC, 0); gm_set_u16(self + B_MAIN + 0xE, 0);
    gm_set_ptr(self + B_DRAW, 0); gm_set_ptr(self + B_DRAW + 4, 0); gm_set_ptr(self + B_DRAW + 8, self);
    gm_set_u16(self + B_DRAW + 0xC, 0); gm_set_u16(self + B_DRAW + 0xE, 0);
    gm_set_ptr(self + B_SEARCH, 0); gm_set_ptr(self + B_SEARCH + 4, 0); gm_set_ptr(self + B_SEARCH + 8, self);
    gm_set_ptr(self + B_LINKS, 0); gm_set_ptr(self + B_LINKS + 4, 0);
    uint32_t id = gm_u32(ROOT_ID) + 1;
    gm_set_u32(ROOT_ID, id);
    if (id == 0xFFFFFFFFu) for (;;) GM_LOOP();              /* (out of IDs: the game stops here) */
    cTreeMg_addTreeNode(GM_PASS, MG_CONNECT, self + B_CONN, gm_ptr(TMP_PARENT));
    cLineMg_addTopLineNode(MG_SEARCH + 8 * fManager_getSearchTableNum(self + B_CONN), self + B_SEARCH);
    gptr prof = gm_ptr(gm_ptr(PROF_TBL) + 4u * gm_u16(self + B_PROF));
    if (prof) {
        uint16_t ex = gm_u16(prof + 4), dr = gm_u16(prof + 6);
        gm_set_u16(self + B_MAIN + 0xC, ex); gm_set_u16(self + B_MAIN + 0xE, ex);
        gm_set_u16(self + B_DRAW + 0xC, dr); gm_set_u16(self + B_DRAW + 0xE, dr);
    }
    follow_parent(self, 0);
    return self;
}
void fBase_opDelete(GM_CTX, gptr p) { GM_CALLR(ctx->lr, F_HEAP_FREE, 2, p, gm_u32(GAME_HEAP)); }   /* (a tail call) */
gptr fBase_opNew(GM_CTX, uint32_t size) { GM_FN(0x801628C0); GM_NV_KEEP;
    NV_R(30, size);
    gptr p = GM_CALLR(0x801628E8u, F_HEAP_ALLOC, 3, size, (uint32_t)-4, gm_u32(GAME_HEAP));
    NV_R(31, p);
    if (p) GM_CALLR(0x80162900u, F_MEMSET, 3, p, 0, size);
    return p;
}
gptr fBase_dtor(GM_CTX, gptr self, int32_t flags) { GM_FN(0x80161C40); GM_NV_KEEP;
    NV_R(31, flags); NV_R(30, self);
    if (!self) return self;
    gm_set_ptr(self + B_VT, VTABLE);
    for (gptr n; (n = gm_ptr(self + B_LINKS)); ) { GM_LOOP(); GM_CALLR(0x80161C80u, 0x80162CA0u, 1, n); }   /* fLiNdBaLink_c::clearData */
    if (flags > 0) NCALL(0x80161C9Cu, fBase_opDelete(GM_PASS, self));
    return self;
}

/* ---- the packs ---- */
/* a call through __ptmf_scall as the PowerPC code makes it: r12 = the pointer to member, the
   trampoline's r0 / r11 / r12 / ctr, LR = the bl's return address, and the callee's volatile
   registers left as it leaves them (the next call inherits them, as in the PowerPC code) */
static uint32_t ptmf_scall(GM_CTX, uint32_t ra, gptr pm, gptr obj) {
    uint32_t adj = gm_u32(pm), vofs = gm_u32(pm + 4), fn = gm_u32(pm + 8);
    ctx->r[0] = adj; ctx->r[11] = vofs;
    ctx->r[3] = obj + adj;
    if ((int32_t)vofs >= 0) fn = gm_u32(gm_u32(ctx->r[3] + fn) + vofs);
    ctx->r[12] = fn; ctx->ctr = fn;
    ctx->lr = ra;
    ppc_call_indirect(ctx, base, fn);
    return ctx->r[3];
}
int32_t fBase_commonPack(GM_CTX, gptr self, gptr do_fn, gptr pre_fn, gptr post_fn) { GM_FN(0x80161CC0); GM_NV_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(30, post_fn); NV_R(29, do_fn); NV_R(28, self);
    int32_t r = (int32_t)ptmf_scall(GM_PASS, 0x80161CF0u, pre_fn, self);
    NV_R(31, r);
    cr_cmp_s(ctx, 0, r, 0);                                          /* (cr0 as the compares leave it: a callee may save CR) */
    uint32_t state;
    if (r) {
        r = (int32_t)ptmf_scall(GM_PASS, 0x80161D0Cu, do_fn, self);
        NV_R(31, r);
        cr_cmp_s(ctx, 0, r, 0);
        if (r) cr_cmp_s(ctx, 0, r, 1);
        state = r == 0 ? PS_WAITING : r == 1 ? PS_SUCCESS : PS_ERROR;
    } else state = PS_CANCELED;
    ctx->r[4] = state;
    ptmf_scall(GM_PASS, 0x80161D4Cu, post_fn, self);
    ctx->r[0] = lr; ctx->lr = lr;                                    /* (the epilogue reloads LR through r0) */
    return r;
}
/* a pack: the three pointers to member functions copied to the stack (do at +32, pre at +20,
   post at +8), the post one also left in r29-r31 */
static int32_t pack(GM_CTX, gptr self, int which) {
    static const uint32_t ra[4] = { 0x80161EC8u, 0x801620A8u, 0x801621A8u, 0x801622A8u };
    GM_FN((which == 0 ? 0x80161E40u : which == 1 ? 0x80162020u : which == 2 ? 0x80162120u : 0x80162220u)); GM_NV_KEEP;
    gptr f = gm_frame_sp, p = PACKS + 0x24u * which;
    for (int i = 0; i < 3; i++) {
        gm_set_u32(f + 8 + 4 * i, gm_u32(p + 24 + 4 * i));
        gm_set_u32(f + 20 + 4 * i, gm_u32(p + 12 + 4 * i));
        gm_set_u32(f + 32 + 4 * i, gm_u32(p + 4 * i));
    }
    NV_R(28, p); NV_R(29, gm_u32(p + 24)); NV_R(30, gm_u32(p + 28)); NV_R(31, gm_u32(p + 32));
    return NCALL(ra[which], fBase_commonPack(GM_PASS, self, f + 32, f + 20, f + 8));
}
int32_t fBase_createPack(GM_CTX, gptr self)  { return pack(GM_PASS, self, 0); }
int32_t fBase_deletePack(GM_CTX, gptr self)  { return pack(GM_PASS, self, 1); }
int32_t fBase_executePack(GM_CTX, gptr self) { return pack(GM_PASS, self, 2); }
int32_t fBase_drawPack(GM_CTX, gptr self)    { return pack(GM_PASS, self, 3); }

void fBase_deleteRequest(GM_CTX, gptr self) { GM_FN(0x80162510); GM_NV_KEEP;
    NV_R(31, self);
    if (gm_u8(self + B_DELREQ) || gm_u8(self + B_STATE) == ST_DELETING) return;
    gm_set_u8(self + B_DELREQ, 1);
    GM_CALLR(0x80162554u, gm_u32(gm_u32(self + B_VT) + 0x38), 1, self);   /* deleteReady */
    for (gptr c = gm_ptr(self + B_CONN + 4); c; c = gm_ptr(c + 0xC)) {
        GM_LOOP(); NV_R(31, c);
        NCALL(0x80162564u, fBase_deleteRequest(GM_PASS, gm_ptr(c + 0x10)));
    }
}
void fBase_postCreate(GM_CTX, gptr self, uint32_t state) { GM_FN(0x80161DA0); GM_NV_KEEP;
    NV_R(31, self);
    if (state == PS_SUCCESS) {
        cLineMg_removeLineNode(MG_CREATE, self + B_MAIN);
        if (gm_u32(NOW_LOOP) == 3) gm_set_u8(self + B_DEFEXE, 1);  /* (not while the execute list runs: at the connect step) */
        else {
            fLiMgBaFuPr_insertLineNodePriority(GM_PASS, MG_EXECUTE, self + B_MAIN);
            fLiMgBaFuPr_insertLineNodePriority(GM_PASS, MG_DRAW, self + B_DRAW);
            gm_set_u8(self + B_STATE, ST_ACTIVE);
        }
    } else if (state == PS_ERROR) NCALL(0x80161E1Cu, fBase_deleteRequest(GM_PASS, self));
}
int32_t fBase_preDelete(GM_CTX, gptr self) { GM_FN(0x80161EF0); GM_NV_KEEP;
    NV_R(31, self);
    gptr arc = gm_ptr(self + B_ARC);
    if (arc && !GM_CALLR(0x80161F18u, F_ARC_CHECK_DELETE, 1, arc)) return 0;
    if (fBase_getConnectChild(self)) return 0;
    return 1;
}
void fBase_postDelete(GM_CTX, gptr self, uint32_t state) { GM_FN(0x80161F60); GM_NV_KEEP;
    NV_R(31, self);
    if (state != PS_SUCCESS) return;
    cTreeMg_removeTreeNode(MG_CONNECT, self + B_CONN);
    cLineMg_removeLineNode(MG_SEARCH + 8 * fManager_getSearchTableNum(self + B_CONN), self + B_SEARCH);
    cLineMg_removeLineNode(MG_DELETE, self + B_MAIN);
    gptr heap = gm_ptr(self + B_HEAP);
    if (heap) GM_CALLR(0x80161FD8u, gm_u32(gm_u32(heap) + 0x1C), 1, heap);   /* EGG::Heap::destroy */
    gptr arc = gm_ptr(self + B_ARC);
    if (arc) GM_CALLR(0x80161FE8u, F_ARC_DELETE, 1, arc);
    if (self) GM_CALLR(0x80162008u, gm_u32(gm_u32(self + B_VT) + 0x48), 2, self, 1);   /* delete this */
}
int32_t fBase_preExecute(gptr self) { return !(gm_u8(self + B_DELREQ) || (gm_u8(self + B_FLAGS) & 2)); }
int32_t fBase_preDraw(gptr self)    { return !(gm_u8(self + B_DELREQ) || (gm_u8(self + B_FLAGS) & 8)); }

/* the connect step, every base every frame: a delete request moves it to the delete list; else
   its flags follow the parent's, a new execute / draw order re-sorts it, deferred steps happen */
int32_t fBase_connectProc(GM_CTX, gptr self) { GM_FN(0x801622E0); GM_NV_KEEP;
    NV_R(31, self);
    if (gm_u8(self + B_DELREQ)) {
        uint8_t st = gm_u8(self + B_STATE);
        gm_set_u8(self + B_DELREQ, 0);
        if (st == ST_ACTIVE) { cLineMg_removeLineNode(MG_EXECUTE, self + B_MAIN); cLineMg_removeLineNode(MG_DRAW, self + B_DRAW); }
        else cLineMg_removeLineNode(MG_CREATE, self + B_MAIN);
        cLineMg_addTopLineNode(MG_DELETE, self + B_MAIN);
        gm_set_u8(self + B_STATE, ST_DELETING);
        for (gptr c = gm_ptr(self + B_CONN + 4); c; c = gm_ptr(c + 0xC)) {
            GM_LOOP(); NV_R(30, c);
            NCALL(0x80162374u, fBase_deleteRequest(GM_PASS, gm_ptr(c + 0x10)));
        }
        return 1;
    }
    follow_parent(self, 1);
    uint8_t st = gm_u8(self + B_STATE);
    if (st == ST_ACTIVE) {
        if (gm_u16(self + B_MAIN + 0xE) != gm_u16(self + B_MAIN + 0xC)) {
            cLineMg_removeLineNode(MG_EXECUTE, self + B_MAIN);
            gm_set_u16(self + B_MAIN + 0xC, gm_u16(self + B_MAIN + 0xE));
            fLiMgBaFuPr_insertLineNodePriority(GM_PASS, MG_EXECUTE, self + B_MAIN);
        }
        if (gm_u16(self + B_DRAW + 0xE) != gm_u16(self + B_DRAW + 0xC)) {
            cLineMg_removeLineNode(MG_DRAW, self + B_DRAW);
            gm_set_u16(self + B_DRAW + 0xC, gm_u16(self + B_DRAW + 0xE));
            fLiMgBaFuPr_insertLineNodePriority(GM_PASS, MG_DRAW, self + B_DRAW);
        }
    } else if (st != ST_DELETING) {
        if (gm_u8(self + B_DEFCRT)) {
            gm_set_u8(self + B_DEFCRT, 0);
            cLineMg_addLastLineNode(MG_CREATE, self + B_MAIN);
        } else if (gm_u8(self + B_DEFEXE)) {
            gm_set_u8(self + B_DEFEXE, 0);
            fLiMgBaFuPr_insertLineNodePriority(GM_PASS, MG_EXECUTE, self + B_MAIN);
            fLiMgBaFuPr_insertLineNodePriority(GM_PASS, MG_DRAW, self + B_DRAW);
            gm_set_u8(self + B_STATE, ST_ACTIVE);
        }
    }
    return 1;
}

/* ---- the heap ---- */
/* mHeap::createFrmHeapToCurrent(size, parent, "fBase_c::mHeap", 32, 0) */
static uint32_t frmheap(GM_CTX, uint32_t ra, uint32_t size, gptr parent) { return GM_CALLR(ra, F_FRMHEAP_CREATE, 5, size, parent, HEAP_NAME, 0x20, 0); }
static uint32_t heap_cb(GM_CTX, uint32_t ra, gptr self) { return GM_CALLR(ra, gm_u32(gm_u32(self + B_VT) + 0x44), 1, self); }   /* createHeap() */
/* entryFrmHeap(size, parent): a frame heap of that size (or all that's left, then shrunk to what
   createHeap used), kept if createHeap() says yes; the lower of the two candidates in memory */
int32_t fBase_entryFrmHeap(GM_CTX, gptr self, uint32_t size, gptr parent) { GM_FN(0x801625F0); GM_NV_KEEP;
    NV_R(26, self); NV_R(27, size); NV_R(28, parent);
    if (gm_ptr(self + B_HEAP)) return 1;
    gptr h = 0; uint32_t got = 0;
    NV_R(30, 0); NV_R(29, 0);
    if (size) {
        h = frmheap(GM_PASS, 0x80162650u, size, parent);
        NV_R(29, h);
        if (h) {
            uint32_t ok = heap_cb(GM_PASS, 0x80162670u, self);
            NV_R(31, ok);
            GM_CALLR(0x80162678u, F_HEAP_RESTORE, 0);
            if (!ok) { GM_CALLR(0x80162688u, F_FRMHEAP_DESTROY, 1, h); h = 0; NV_R(29, 0); }
            else {
                got = GM_CALLR(0x80162698u, F_FRMHEAP_ADJUST, 1, h);
                NV_R(30, got);
                if (size == got) { gm_set_ptr(self + B_HEAP, h); return 1; }
            }
        }
    }
    if (!h) {
        h = frmheap(GM_PASS, 0x801626D4u, 0xFFFFFFFFu, parent);
        NV_R(29, h);
        if (h) {
            uint32_t ok = heap_cb(GM_PASS, 0x801626F4u, self);
            NV_R(31, ok);
            GM_CALLR(0x801626FCu, F_HEAP_RESTORE, 0);
            if (!ok) { GM_CALLR(0x8016270Cu, F_FRMHEAP_DESTROY, 1, h); h = 0; NV_R(29, 0); }
            else { got = GM_CALLR(0x8016271Cu, F_FRMHEAP_ADJUST, 1, h); NV_R(30, got); }
        }
    }
    if (h) {
        gptr h2 = frmheap(GM_PASS, 0x80162744u, got, parent);
        NV_R(30, h2);
        if (h2) {
            if (h2 < h) {
                GM_CALLR(0x80162760u, F_FRMHEAP_DESTROY, 1, h);
                h = 0; NV_R(29, 0);
                uint32_t ok = heap_cb(GM_PASS, 0x80162778u, self);
                NV_R(31, ok);
                GM_CALLR(0x80162780u, F_HEAP_RESTORE, 0);
                if (!ok) GM_CALLR(0x80162790u, F_FRMHEAP_DESTROY, 1, h2);
                else { GM_CALLR(0x8016279Cu, F_FRMHEAP_ADJUST, 1, h2); gm_set_ptr(self + B_HEAP, h2); return 1; }
            } else {
                GM_CALLR(0x801627ACu, F_HEAP_RESTORE, 0);
                GM_CALLR(0x801627B4u, F_FRMHEAP_DESTROY, 1, h2);
            }
        }
    }
    if (h) { gm_set_ptr(self + B_HEAP, h); return 1; }
    NCALL(0x801627D0u, fBase_deleteRequest(GM_PASS, self));
    return 0;
}
int32_t fBase_entryFrmHeapNonAdjust(GM_CTX, gptr self, uint32_t size, gptr parent) { GM_FN(0x801627F0); GM_NV_KEEP;
    NV_R(29, self);
    if (gm_ptr(self + B_HEAP)) return 1;
    gptr h = frmheap(GM_PASS, 0x80162840u, size, parent);
    NV_R(30, h);
    if (h) {
        uint32_t ok = heap_cb(GM_PASS, 0x80162860u, self);
        NV_R(31, ok);
        GM_CALLR(0x80162868u, F_HEAP_RESTORE, 0);
        if (ok) { gm_set_ptr(self + B_HEAP, h); return 1; }
        GM_CALLR(0x80162878u, F_FRMHEAP_DESTROY, 1, h);
    }
    NCALL(0x80162890u, fBase_deleteRequest(GM_PASS, self));
    return 0;
}

/* ---- making bases ---- */
void fBase_runCreate(GM_CTX, gptr self) { GM_FN(0x80162930); GM_NV_KEEP;
    NV_R(31, self);
    NCALL(0x80162948u, fBase_createPack(GM_PASS, self));
    if (!gm_u8(self + B_DELREQ) && !gm_u8(self + B_DEFEXE) && gm_u8(self + B_STATE) == ST_CREATING) {
        if (gm_u32(NOW_LOOP) == 2) gm_set_u8(self + B_DEFCRT, 1);  /* (not while the create list runs) */
        else cLineMg_addLastLineNode(MG_CREATE, self + B_MAIN);
    }
}
/* the first base below this one still being created */
gptr fBase_getChildProcessCreateState(GM_CTX, gptr self) { GM_FN(0x801629B0); GM_NV_KEEP;
    gptr node = self + B_CONN;
    NV_R(31, node);
    gptr end = cTreeNd_getTreeNextNotChild(GM_PASS, node);           /* (a leaf) */
    NV_R(31, end);
    for (gptr c = gm_ptr(node + 4); c && c != end; c = GM_CALLR(0x801629F4u, 0x801616C0u, 1, c)) {   /* cTreeNd_c::getTreeNext */
        GM_LOOP();
        gptr owner = gm_ptr(c + 0x10);
        if (gm_u8(owner + B_STATE) == ST_CREATING) return owner;
    }
    return 0;
}
void fBase_setTmpCtData(uint32_t prof, gptr parent, uint32_t param, uint32_t group) {
    gm_set_u32(TMP_PARAM, param); gm_set_u16(TMP_PROF, (uint16_t)prof); gm_set_u8(TMP_GROUP, (uint8_t)group); gm_set_ptr(TMP_PARENT, parent);
}
gptr fBase_make(GM_CTX, uint32_t prof, gptr parent, uint32_t param, uint32_t group) { GM_FN(0x80162A70); GM_NV_KEEP;
    uint32_t off = (prof << 2) & 0x3FFFC;
    NV_R(31, off);
    if (!gm_ptr(gm_ptr(PROF_TBL) + off)) return 0;
    fBase_setTmpCtData(prof, parent, param, group);
    gptr p = gm_ptr(gm_ptr(PROF_TBL) + off);
    gptr res = GM_CALLR(0x80162AB4u, gm_u32(p), 1, p);                    /* the profile's class init (r3: the profile, as left) */
    NV_R(31, res);
    fBase_setTmpCtData(0, 0, 0, 0);
    if (res) NCALL(0x80162ADCu, fBase_runCreate(GM_PASS, res));
    return res;
}

/* ---- register-exact entries (part 48: RT_GM_VERIFY_REGS=1) ---- */
uint32_t cTreeNd_next(GM_CTX);                                       /* gm_c_list.c */
uint32_t cTreeNd_nextNotChild(GM_CTX);
/* findNextUninitialisedProcess(): the first base under this one (in the connect tree) whose
   create step hasn't run (+10 == 0) */
static uint32_t find_uninit_r(GM_CTX) {
    GM_FN(0x801629B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
#define R(n) ctx->r[n]
    NV_R(31, R(3) + B_CONN);
    R(3) = R(31);
    ctx->lr = 0x801629CCu; cTreeNd_nextNotChild(GM_PASS);
    R(4) = gm_ptr(R(31) + 4);
    NV_R(31, R(3));
    for (;;) {
        cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
        if (!R(4)) { R(3) = 0; break; }
        cr_cmp_u(ctx, 0, R(4), R(31));
        if (R(4) == R(31)) { R(3) = 0; break; }
        GM_LOOP();
        R(3) = gm_ptr(R(4) + 16);
        R(0) = gm_u8(R(3) + 10);
        cr_cmp_s(ctx, 0, (int32_t)R(0), 0);
        if (!R(0)) break;
        R(3) = R(4);
        ctx->lr = 0x801629F4u; cTreeNd_next(GM_PASS);
        R(4) = R(3);
    }
    R(0) = lr;
    return R(3);
}
static uint32_t has_uninit_r(GM_CTX) {
    GM_FN(0x80162A20); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    ctx->lr = 0x80162A30u; find_uninit_r(GM_PASS);
    R(0) = (uint32_t)-(int32_t)R(3);
    R(0) |= R(3);
    R(3) = R(0) >> 31;
    R(0) = lr;
    return R(3);
#undef R
}

/* ================================================================== hle entry points
 * Most of these call virtual functions (anything): not verified call by call, but by the A/B
 * replay (docs/DECOMP.md). The pure ones are verified. */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
GM_HLE(fn_80161AD0) { GM_RET(fBase_ctor(GM_PASS, SELF)); }                                           /* fBase_c::fBase_c */
GM_HLE(fn_80161C40) { GM_LR_KEEP; GM_RET(fBase_dtor(GM_PASS, SELF, (int32_t)A(1))); }                            /* fBase_c::~fBase_c */
GM_HLE(fn_80161CC0) { GM_RET(fBase_commonPack(GM_PASS, SELF, A(1), A(2), A(3))); }                   /* fBase_c::commonPack */
GM_HLE(fn_80161DA0) { GM_LR_KEEP; fBase_postCreate(GM_PASS, SELF, A(1)); }                                       /* fBase_c::postCreate */
GM_HLE(fn_80161E40) { GM_LR_KEEP; GM_RET(fBase_createPack(GM_PASS, SELF)); }                                     /* fBase_c::createPack */
GM_HLE(fn_80161EF0) { GM_RET(fBase_preDelete(GM_PASS, SELF)); }                                      /* fBase_c::preDelete */
GM_HLE(fn_80161F60) { fBase_postDelete(GM_PASS, SELF, A(1)); }                                       /* fBase_c::postDelete */
GM_HLE(fn_80162020) { GM_LR_KEEP; GM_RET(fBase_deletePack(GM_PASS, SELF)); }                                     /* fBase_c::deletePack */
GM_HLE_INT(fn_801620E0, SELF, 0x10) { GM_RET(fBase_preExecute(SELF)); }                              /* fBase_c::preExecute */
GM_HLE(fn_80162120) { GM_LR_KEEP; GM_RET(fBase_executePack(GM_PASS, SELF)); }                                    /* fBase_c::executePack */
GM_HLE_INT(fn_801621E0, SELF, 0x10) { GM_RET(fBase_preDraw(SELF)); }                                 /* fBase_c::preDraw */
GM_HLE(fn_80162220) { GM_LR_KEEP; GM_RET(fBase_drawPack(GM_PASS, SELF)); }                                       /* fBase_c::drawPack */
GM_HLE(fn_801622E0) { GM_LR_KEEP; GM_RET(fBase_connectProc(GM_PASS, SELF)); }                                    /* fBase_c::connectProc */
GM_HLE(Delete__7fBase_cFv) { GM_LR_KEEP; fBase_deleteRequest(GM_PASS, SELF); }                                  /* fBase_c::deleteRequest */
GM_HLE_INT(GetObjectParent, SELF, 0x20) { ctx->r[3] = gm_ptr(SELF + B_CONN + 0); cr_cmp_s(ctx, 0, (int32_t)ctx->r[3], 0); GM_RET(ctx->r[3] ? gm_ptr(ctx->r[3] + 0x10) : 0); }                    /* fBase_c::getConnectParent */
GM_HLE_INT(fn_801625B0, SELF, 0x20) { ctx->r[3] = gm_ptr(SELF + B_CONN + 4); cr_cmp_s(ctx, 0, (int32_t)ctx->r[3], 0); GM_RET(ctx->r[3] ? gm_ptr(ctx->r[3] + 0x10) : 0); }                         /* fBase_c::getConnectChild */
GM_HLE_INT(fn_801625D0, SELF, 0x20) { ctx->r[3] = gm_ptr(SELF + B_CONN + 12); cr_cmp_s(ctx, 0, (int32_t)ctx->r[3], 0); GM_RET(ctx->r[3] ? gm_ptr(ctx->r[3] + 0x10) : 0); }                        /* fBase_c::getConnectBrNext */
GM_HLE(moreHeapShit__7fBase_cFUiPv) { GM_LR_KEEP; GM_RET(fBase_entryFrmHeap(GM_PASS, SELF, A(1), A(2))); }      /* fBase_c::entryFrmHeap */
GM_HLE(createHeap__7fBase_cFUiPv) { GM_LR_KEEP; GM_RET(fBase_entryFrmHeapNonAdjust(GM_PASS, SELF, A(1), A(2))); }   /* fBase_c::entryFrmHeapNonAdjust */
GM_HLE(AllocateMemoryBlock) { GM_RET(fBase_opNew(GM_PASS, SELF)); }                                 /* fBase_c::operator new */
GM_HLE(_Z17FreeFromGameHeap1Pv) { fBase_opDelete(GM_PASS, SELF); }                                  /* fBase_c::operator delete */
GM_HLE(fn_80162930) { GM_LR_KEEP; fBase_runCreate(GM_PASS, SELF); }                                              /* fBase_c::runCreate */
GM_HLE_INT(findNextUninitialisedProcess__7fBase_cFv, SELF, 0x64) { GM_RET(find_uninit_r(GM_PASS)); }
GM_HLE_INT(hasUninitialisedProcesses__7fBase_cFv, SELF, 0x64) { GM_RET(has_uninit_r(GM_PASS)); }
GM_HLE_VOID(fn_80162A50, TMP_PROF, 0x10) { fBase_setTmpCtData(A(0), A(1), A(2), A(3)); }             /* fBase_c::setTmpCtData */
GM_HLE(fn_80162A70) { GM_LR_KEEP; GM_RET(fBase_make(GM_PASS, A(0), A(1), A(2), A(3))); }                         /* fBase_c::fBase_make */
GM_HLE(_Z20CreateParentedObjectsPvic) { GM_LR_KEEP; GM_RET(A(1) ? fBase_make(GM_PASS, A(0), A(1) + B_CONN, A(2), A(3)) : 0); }   /* fBase_c::createChild */
GM_HLE(ObjCreate2) { GM_LR_KEEP; GM_RET(fBase_make(GM_PASS, A(0), 0, A(1), A(2))); }                             /* fBase_c::createRoot */

/* fBase_c's default virtuals (part 54): the steps succeed / do nothing */
GM_HLE_INT(onCreate__7fBase_cFv, 0, 0)  { ctx->r[3] = 1; }                                          /* fBase_c::create */
GM_HLE(fn_80161D90)           { ctx->r[3] = 1; }                                          /* ::preCreate */
GM_HLE_INT(onDelete__7fBase_cFv, 0, 0)  { ctx->r[3] = 1; }                                          /* ::doDelete */
GM_HLE(onExecute__7fBase_cFv) { ctx->r[3] = 1; }                                          /* ::execute */
GM_HLE_VOID(fn_80162110, 0, 0)          { }                                                         /* ::postExecute */
GM_HLE_INT(onDraw__7fBase_cFv, 0, 0)    { ctx->r[3] = 1; }                                          /* ::draw */
GM_HLE_VOID(fn_80162210, 0, 0)          { }                                                         /* ::postDraw */
GM_HLE_VOID(willBeDeleted__7fBase_cFv, 0, 0) { }                                                    /* ::deleteReady */
GM_HLE(heapCreated__7fBase_cFv) { ctx->r[3] = 1; }                                        /* ::doDelete's heap check */
