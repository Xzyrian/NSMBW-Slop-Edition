/* gm_f_list.c - the framework's lists and trees of bases: fLiMgBa_c / fLiMgBaFu_c /
 * fLiMgBaFuPr_c / fLiNdBaLink_c (f_line.cpp) and fTrMgBa_c / fTrMgBaFu_c (f_tree.cpp).
 * Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/framework/f_line.cpp, f_tree.cpp). The framework
 * (fManager_c) keeps every base (actor, scene, ...) in a connect tree and in execute / draw /
 * create / delete lists; these walk them.
 *
 * Layouts: fLiNdBaLink_c = cLineNd_c (+0 prev, +4 next) + 8 owner (fBase_c *);
 *          fLiNdBaPr_c = fLiNdBaLink_c + 0xC order (u16), 0xE new order;
 *          fTrNdBa_c = cTreeNd_c (+0..+C) + 0x10 owner;
 *          fLiMgBaFu_c = cLineMg_c + 8 the function to call (a pointer to member function, 12 bytes);
 *          fTrMgBaFu_c = cTreeMg_c + 4 the same.
 *          fBase_c: +0 unique ID, +8 profile name (u16), +0xE group type (u8), +0x54 its links. */
#include "gm.h"
#include "gm_nv.h"

int  cLineMg_insertLineNode(gptr self, gptr node, gptr prev);       /* gm_c_list.c */
int  cLineMg_addLastLineNode(gptr self, gptr node);
int  cLineMg_removeLineNode(gptr self, gptr node);
gptr cTreeNd_getTreeNext(GM_CTX, gptr self);

#define LN_NEXT   0x4
#define LNK_OWNER 0x8
#define PR_ORDER  0xC
#define TRN_OWNER 0x10
#define B_ID      0x0
#define B_PROF    0x8
#define B_GROUP   0xE
#define B_LINKS   0x54

/* a CodeWarrior pointer to member function: +0 this adjustment, +4 vtable entry (-1: not
   virtual), +8 the function, or for a virtual one the offset of the vtable pointer */
static int ptmf_set(gptr pm) { return gm_u32(pm) || gm_u32(pm + 4) || gm_u32(pm + 8); }
static void ptmf_call(GM_CTX, gptr pm, gptr obj) {
    gptr self = obj + gm_u32(pm);
    int32_t vofs = gm_s32(pm + 4); uint32_t fn = gm_u32(pm + 8);
    if (vofs >= 0) fn = gm_u32(gm_u32(self + fn) + (uint32_t)vofs);
    GM_CALL(fn, 1, self);
}

/* fLiMgBaFuPr_c::insertLineNodePriority: keep the list ordered by priority (lower first; after
   the nodes of the same priority) */
int fLiMgBaFuPr_insertLineNodePriority(GM_CTX, gptr self, gptr node) {
    gptr cur = gm_ptr(self);
    if (!node) return 0;
    if (!cur) return cLineMg_addLastLineNode(self, node);
    if (gm_u16(cur + PR_ORDER) > gm_u16(node + PR_ORDER)) return cLineMg_insertLineNode(self, node, 0);
    for (gptr next; (next = gm_ptr(cur + LN_NEXT)) && gm_u16(next + PR_ORDER) <= gm_u16(node + PR_ORDER); ) { GM_LOOP(); cur = next; }
    return cLineMg_insertLineNode(self, node, cur);
}
/* fLiMgBaFu_c::lineListProc: the manager's function on every node's base */
int fLiMgBaFu_lineListProc(GM_CTX, gptr self) { GM_FN(0x80162BB0);
    if (!ptmf_set(self + 8)) return 1;
    for (gptr cur = gm_ptr(self); cur; ) {
        GM_LOOP();
        gptr next = gm_ptr(cur + LN_NEXT);
        ptmf_call(GM_PASS, self + 8, gm_ptr(cur + LNK_OWNER));
        cur = next;
    }
    return 1;
}
gptr fLiMgBa_searchNodeByID(GM_CTX, gptr self, uint32_t id) {
    for (gptr cur = gm_ptr(self); cur; cur = gm_ptr(cur + LN_NEXT)) {
        GM_LOOP();
        if (gm_s32(gm_ptr(cur + LNK_OWNER) + B_ID) == (int32_t)id) return cur;
    }
    return 0;
}
int fLiMgBa_countNodeByProfName(GM_CTX, gptr self, uint32_t prof) {
    int n = 0;
    for (gptr cur = gm_ptr(self); cur; cur = gm_ptr(cur + LN_NEXT)) {
        GM_LOOP();
        if (gm_u16(gm_ptr(cur + LNK_OWNER) + B_PROF) == prof) n++;
    }
    return n;
}
void fLiNdBaLink_clearData(gptr self) {
    gptr owner = gm_ptr(self + LNK_OWNER);
    if (owner) { cLineMg_removeLineNode(owner + B_LINKS, self); gm_set_ptr(self + LNK_OWNER, 0); }
}

/* fTrMgBaFu_c::treeListProc: the manager's function on every base in the tree, depth first */
int fTrMgBaFu_treeListProc(GM_CTX, gptr self) { GM_FN(0x80163000);
    if (!ptmf_set(self + 4)) return 1;
    for (gptr cur = gm_ptr(self); cur; ) {
        GM_LOOP();
        gptr next = cTreeNd_getTreeNext(GM_PASS, cur);
        ptmf_call(GM_PASS, self + 4, gm_ptr(cur + TRN_OWNER));
        cur = next;
    }
    return 1;
}
/* the first node (after parent, or from the root) whose base has this profile / group */
static gptr tree_search(GM_CTX, gptr self, gptr parent, int group, uint32_t want) {
    gptr cur = parent ? cTreeNd_getTreeNext(GM_PASS, parent) : gm_ptr(self);
    while (cur) {
        GM_LOOP();
        gptr owner = gm_ptr(cur + TRN_OWNER);
        if ((group ? gm_u8(owner + B_GROUP) : gm_u16(owner + B_PROF)) == want) return cur;
        cur = cTreeNd_getTreeNext(GM_PASS, cur);
    }
    return 0;
}
gptr fTrMgBa_searchNodeByProfName(GM_CTX, gptr self, uint32_t prof, gptr parent) { GM_FN(0x80163090); return tree_search(GM_PASS, self, parent, 0, prof); }
gptr fTrMgBa_searchNodeByGroupType(GM_CTX, gptr self, uint32_t group, gptr parent) { GM_FN(0x80163100); return tree_search(GM_PASS, self, parent, 1, group); }   /* (compared as the caller passed it, as the PowerPC code does) */

/* ================================================================== the same, register-exact (part 48)
   The PowerPC registers are the variables (R(n)), so the volatile ones, CR0 and the non-volatile
   ones the callees see end as the original leaves them (RT_GM_VERIFY_REGS=1). The pointer-to-
   member calls go through the runtime's own __ptmf_test / __ptmf_scall, as the game's do. */
#define R(n) ctx->r[n]
#define F_PTMF_TEST  0x802DCB90u
#define F_PTMF_SCALL 0x802DCBFCu
uint32_t cLineMg_addLast(GM_CTX);                                    /* gm_c_list.c */
uint32_t cLineMg_insert(GM_CTX);
uint32_t cLineMg_remove(GM_CTX);
uint32_t cTreeNd_next(GM_CTX);
static inline int z0(ppc_context *ctx, uint32_t v) { cr_cmp_s(ctx, 0, (int32_t)v, 0); return v == 0; }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

/* insertLineNodePriority(node) (self r3, node r4) - the inserts are tail calls */
static uint32_t prio_insert(GM_CTX) {
    int none = z0(ctx, R(4));
    R(5) = gm_ptr(R(3));
    if (none) return 0;
    if (z0(ctx, R(5))) return cLineMg_addLast(GM_PASS);
    R(6) = gm_u16(R(5) + PR_ORDER); R(0) = gm_u16(R(4) + PR_ORDER);
    if (cmpu(ctx, R(6), R(0)) > 0) { R(5) = 0; return cLineMg_insert(GM_PASS); }
    for (int first = 1;; first = 0) {
        if (!first) R(5) = R(7);
        R(7) = gm_ptr(R(5) + LN_NEXT);
        if (z0(ctx, R(7))) break;
        R(6) = gm_u16(R(7) + PR_ORDER); R(0) = gm_u16(R(4) + PR_ORDER);
        if (cmpu(ctx, R(6), R(0)) > 0) break;
        GM_LOOP();
    }
    return cLineMg_insert(GM_PASS);
}
/* lineListProc() (self r3): the manager's function on every node's owner */
static uint32_t line_proc(GM_CTX) {
    GM_FN(0x80162BB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(30, R(3));
    R(3) += 8;
    if (z0(ctx, GM_CALLV(0x80162BD0u, F_PTMF_TEST, 0))) R(3) = 1;
    else {
        R(3) = gm_ptr(R(30));
        while (!z0(ctx, R(3))) {
            GM_LOOP();
            NV_R(31, gm_ptr(R(3) + LN_NEXT));
            R(12) = R(30) + 8;
            R(3) = gm_ptr(R(3) + LNK_OWNER);
            GM_CALLV(0x80162BF8u, F_PTMF_SCALL, 0);
            R(3) = R(31);
        }
        R(3) = 1;
    }
    R(0) = lr;
    return R(3);
}
/* searchNodeByID(id) */
static uint32_t search_id(GM_CTX) {
    R(3) = gm_ptr(R(3));
    for (int first = 1;; first = 0) {
        if (!first) {
            R(5) = gm_ptr(R(3) + LNK_OWNER); R(0) = gm_u32(R(5) + B_ID);
            cr_cmp_s(ctx, 0, (int32_t)R(0), (int32_t)R(4));
            if (R(0) == R(4)) return R(3);
            R(3) = gm_ptr(R(3) + LN_NEXT);
        }
        if (z0(ctx, R(3))) return 0;
        GM_LOOP();
    }
}
/* countNodeByProfName(profile) */
static uint32_t count_prof(GM_CTX) {
    R(6) = gm_ptr(R(3)); R(3) = 0;
    while (!z0(ctx, R(6))) {
        GM_LOOP();
        R(5) = gm_ptr(R(6) + LNK_OWNER); R(0) = gm_u16(R(5) + B_PROF);
        if (cmpu(ctx, R(0), R(4)) == 0) R(3)++;
        R(6) = gm_ptr(R(6) + LN_NEXT);
    }
    return R(3);
}
/* clearData() */
static void link_clear(GM_CTX) {
    GM_FN(0x80162CA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, R(3));
    R(5) = gm_ptr(R(3) + LNK_OWNER);
    if (!z0(ctx, R(5))) {
        R(4) = R(31); R(3) = R(5) + B_LINKS;
        ctx->lr = 0x80162CCCu; cLineMg_remove(GM_PASS);
        R(0) = 0; gm_set_ptr(R(31) + LNK_OWNER, 0);
    }
    R(0) = lr;
}
/* treeListProc() (self r3): the manager's function on every node's owner, depth first */
static uint32_t tree_proc(GM_CTX) {
    GM_FN(0x80163000); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(29, R(3));
    R(3) += 4;
    if (z0(ctx, GM_CALLV(0x80163024u, F_PTMF_TEST, 0))) R(3) = 1;
    else {
        NV_R(30, gm_ptr(R(29)));
        while (!z0(ctx, R(30))) {
            GM_LOOP();
            R(3) = R(30);
            ctx->lr = 0x80163044u; NV_R(31, cTreeNd_next(GM_PASS));
            R(3) = gm_ptr(R(30) + TRN_OWNER);
            R(12) = R(29) + 4;
            GM_CALLV(0x80163054u, F_PTMF_SCALL, 0);
            NV_R(30, R(31));
        }
        R(3) = 1;
    }
    R(0) = lr;
    return R(3);
}
/* searchNodeByProfName / searchNodeByGroupType(key, after) (self r3, key r4, after r5) */
static uint32_t tree_find(GM_CTX, int group) {
    GM_FN(group ? 0x80163100u : 0x80163090u); GM_NV_KEEP; GM_LR_KEEP;   /* FNADDR */
    uint32_t lr = ctx->lr, ra0 = group ? 0x80163124u : 0x801630B4u, ra1 = group ? 0x80163148u : 0x801630D8u;
    int after = !z0(ctx, R(5));
    NV_R(31, R(4));
    if (after) { R(3) = R(5); ctx->lr = ra0; cTreeNd_next(GM_PASS); }
    else R(3) = gm_ptr(R(3));
    for (;;) {
        if (z0(ctx, R(3))) { R(3) = 0; break; }
        GM_LOOP();
        R(4) = gm_ptr(R(3) + TRN_OWNER);
        R(0) = group ? gm_u8(R(4) + B_GROUP) : gm_u16(R(4) + B_PROF);
        if (cmpu(ctx, R(0), R(31)) == 0) break;
        ctx->lr = ra1; cTreeNd_next(GM_PASS);
    }
    R(0) = lr;
    return R(3);
}
uint32_t fTrMgBa_find_r(GM_CTX, int group) { return tree_find(GM_PASS, group); }   /* (gm_f_manager.c) */
uint32_t fLiMgBa_searchID_r(GM_CTX) { return search_id(GM_PASS); }
uint32_t fLiMgBaFu_proc_r(GM_CTX) { return line_proc(GM_PASS); }
uint32_t fTrMgBaFu_proc_r(GM_CTX) { return tree_proc(GM_PASS); }

/* ================================================================== hle entry points */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
static gptr nz(gptr p) { return p ? p : 0x80000000u; }
static gptr prio_after(gptr self, gptr node) {          /* (the node insertLineNodePriority links after) */
    gptr cur = gm_ptr(self);
    if (!node || !cur || gm_u16(cur + PR_ORDER) > gm_u16(node + PR_ORDER)) return 0;
    for (gptr next; (next = gm_ptr(cur + LN_NEXT)) && gm_u16(next + PR_ORDER) <= gm_u16(node + PR_ORDER); ) cur = next;
    return cur;
}
GM_HLE_INT(fn_80162B40, SELF, 8, nz(A(1)), 16, nz(prio_after(SELF, A(1))), 16, nz(gm_ptr(SELF)), 16, nz(gm_ptr(SELF + 4)), 16,
           nz(prio_after(SELF, A(1)) ? gm_ptr(prio_after(SELF, A(1)) + LN_NEXT) : 0), 16) {        /* fLiMgBaFuPr_c::insertLineNodePriority */
    GM_RET(prio_insert(GM_PASS));
}
GM_HLE(fn_80162BB0) { GM_RET(line_proc(GM_PASS)); }                               /* fLiMgBaFu_c::lineListProc (calls anything: no verify) */
GM_HLE_INT(fn_80162C30, SELF, 8) { GM_RET(search_id(GM_PASS)); }               /* fLiMgBa_c::searchNodeByID */
GM_HLE_INT(fn_80162C60, SELF, 8) { GM_RET(count_prof(GM_PASS)); } /* fLiMgBa_c::countNodeByProfName */
GM_HLE_VOID(fn_80162CA0, SELF, 12, nz(gm_ptr(SELF + LNK_OWNER)) + B_LINKS, 8, nz(gm_ptr(SELF)), 8, nz(gm_ptr(SELF + 4)), 8) {           /* fLiNdBaLink_c::clearData */
    link_clear(GM_PASS);
}
GM_HLE(fn_80163000) { GM_RET(tree_proc(GM_PASS)); }                               /* fTrMgBaFu_c::treeListProc (no verify) */
GM_HLE_INT(fn_80163090, SELF, 4) { GM_RET(tree_find(GM_PASS, 0)); } /* fTrMgBa_c::searchNodeByProfName */
GM_HLE_INT(fn_80163100, SELF, 4) { GM_RET(tree_find(GM_PASS, 1)); }/* fTrMgBa_c::searchNodeByGroupType */
