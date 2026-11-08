/* gm_c_list.c - cLib's linked lists and trees: cLineMg_c / cLineNd_c (c_line.cpp) and
 * cTreeMg_c / cTreeNd_c (c_tree.cpp). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/cLib/c_line.cpp, c_tree.cpp); USA rev 2 addresses.
 * These are the containers under the whole actor framework (fBase_c's connect tree, the
 * execute / draw / search lists, the delete list), so they run thousands of times a frame.
 *
 * Layouts (checked against the recompiled code):
 *   cLineNd_c  +0 prev, +4 next                     cLineMg_c +0 first, +4 last
 *   cTreeNd_c  +0 parent, +4 child, +8 prev, +C next cTreeMg_c +0 root */
#include "gm.h"
#include "gm_nv.h"

/* ---- cLineNd_c / cLineMg_c ---- */
#define LN_PREV 0x0
#define LN_NEXT 0x4
#define LM_FIRST 0x0
#define LM_LAST  0x4
/* (part 48: register-exact - the PowerPC registers are the variables, R(n), so the volatile
   ones and CR0 end as the original leaves them: RT_GM_VERIFY_REGS=1) */
#define R(n) ctx->r[n]
static inline int z0(ppc_context *ctx, uint32_t v) { cr_cmp_s(ctx, 0, (int32_t)v, 0); return v == 0; }      /* cmpwi v, 0: zero? */
static inline int eqp(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return a == b; }  /* cmplw */

/* addTopLineNode(node) (self r3, node r4) */
uint32_t cLineMg_addTop(GM_CTX) {
    if (z0(ctx, R(4))) return 0;
    R(5) = gm_ptr(R(3) + LM_FIRST);
    if (!z0(ctx, R(5))) { gm_set_ptr(R(5) + LN_PREV, R(4)); R(0) = gm_ptr(R(3) + LM_FIRST); gm_set_ptr(R(4) + LN_NEXT, R(0)); }
    else gm_set_ptr(R(3) + LM_LAST, R(4));
    gm_set_ptr(R(3) + LM_FIRST, R(4));
    return 1;
}
/* addLastLineNode(node) */
uint32_t cLineMg_addLast(GM_CTX) {
    if (z0(ctx, R(4))) return 0;
    R(5) = gm_ptr(R(3) + LM_LAST);
    if (!z0(ctx, R(5))) { gm_set_ptr(R(5) + LN_NEXT, R(4)); R(0) = gm_ptr(R(3) + LM_LAST); gm_set_ptr(R(4) + LN_PREV, R(0)); }
    else gm_set_ptr(R(3) + LM_FIRST, R(4));
    gm_set_ptr(R(3) + LM_LAST, R(4));
    return 1;
}
/* insertLineNode(node, prev): after prev (none: at the front - a tail call to addTopLineNode) */
uint32_t cLineMg_insert(GM_CTX) {
    if (z0(ctx, R(5))) return cLineMg_addTop(GM_PASS);
    if (z0(ctx, R(4))) return 0;
    R(0) = gm_ptr(R(5) + LN_NEXT); gm_set_ptr(R(4) + LN_NEXT, R(0));
    gm_set_ptr(R(4) + LN_PREV, R(5));
    gm_set_ptr(R(5) + LN_NEXT, R(4));
    R(5) = gm_ptr(R(4) + LN_NEXT);
    if (!z0(ctx, R(5))) gm_set_ptr(R(5) + LN_PREV, R(4));
    else gm_set_ptr(R(3) + LM_LAST, R(4));
    return 1;
}
/* removeLineNode(node) */
uint32_t cLineMg_remove(GM_CTX) {
    if (z0(ctx, R(4))) return 0;
    R(5) = gm_ptr(R(4) + LN_PREV);
    if (!z0(ctx, R(5))) { R(0) = gm_ptr(R(4) + LN_NEXT); gm_set_ptr(R(5) + LN_NEXT, R(0)); }
    else { R(0) = gm_ptr(R(3) + LM_FIRST); if (eqp(ctx, R(4), R(0))) { R(0) = gm_ptr(R(4) + LN_NEXT); gm_set_ptr(R(3) + LM_FIRST, R(0)); } }
    R(5) = gm_ptr(R(4) + LN_NEXT);
    if (!z0(ctx, R(5))) { R(0) = gm_ptr(R(4) + LN_PREV); gm_set_ptr(R(5) + LN_PREV, R(0)); }
    else { R(0) = gm_ptr(R(3) + LM_LAST); if (eqp(ctx, R(4), R(0))) { R(0) = gm_ptr(R(4) + LN_PREV); gm_set_ptr(R(3) + LM_LAST, R(0)); } }
    R(0) = 0;
    gm_set_ptr(R(4) + LN_PREV, 0); gm_set_ptr(R(4) + LN_NEXT, 0);
    return 1;
}

/* ---- cTreeNd_c / cTreeMg_c ---- */
#define TN_PARENT 0x0
#define TN_CHILD  0x4
#define TN_PREV   0x8
#define TN_NEXT   0xC
#define TM_ROOT   0x0

/* forcedClear() (self r3) */
static void cTreeNd_clear(GM_CTX) {
    R(0) = 0;
    for (int i = 0; i < 4; i++) gm_set_ptr(R(3) + 4 * i, 0);
}
/* addTreeNode(node, parent): the last child of parent (none: the last top-level node) */
static uint32_t cTreeMg_add(GM_CTX) {
    if (z0(ctx, R(4))) return 0;
    int reg = 5;                                             /* (the walk runs in r3 under a parent, r5 at the top) */
    if (!z0(ctx, R(5))) {
        gm_set_ptr(R(4) + TN_PARENT, R(5));
        R(3) = gm_ptr(R(5) + TN_CHILD);
        if (z0(ctx, R(3))) { gm_set_ptr(R(5) + TN_CHILD, R(4)); return 1; }
        reg = 3;
    } else {
        R(5) = gm_ptr(R(3) + TM_ROOT);
        if (z0(ctx, R(5))) { gm_set_ptr(R(3) + TM_ROOT, R(4)); return 1; }
    }
    for (int first = 1;; first = 0) {                        /* to the last sibling */
        if (!first) R(reg) = R(0);
        R(0) = gm_ptr(R(reg) + TN_NEXT);
        if (z0(ctx, R(0))) break;
        GM_LOOP();
    }
    gm_set_ptr(R(reg) + TN_NEXT, R(4));
    gm_set_ptr(R(4) + TN_PREV, R(reg));
    return 1;
}
/* removeTreeNode(node): only a node without children */
static uint32_t cTreeMg_remove(GM_CTX) {
    if (z0(ctx, R(4))) return 0;
    R(0) = gm_ptr(R(4) + TN_CHILD);
    if (!z0(ctx, R(0))) return 0;
    R(5) = gm_ptr(R(4) + TN_PREV);
    if (!z0(ctx, R(5))) { R(0) = gm_ptr(R(4) + TN_NEXT); gm_set_ptr(R(5) + TN_NEXT, R(0)); }
    else {
        R(5) = gm_ptr(R(4) + TN_PARENT);
        if (!z0(ctx, R(5))) { R(0) = gm_ptr(R(4) + TN_NEXT); gm_set_ptr(R(5) + TN_CHILD, R(0)); }
        else { R(0) = gm_ptr(R(3) + TM_ROOT); if (eqp(ctx, R(4), R(0))) { R(0) = gm_ptr(R(4) + TN_NEXT); gm_set_ptr(R(3) + TM_ROOT, R(0)); } }
    }
    R(3) = gm_ptr(R(4) + TN_NEXT);
    if (!z0(ctx, R(3))) { R(0) = gm_ptr(R(4) + TN_PREV); gm_set_ptr(R(3) + TN_PREV, R(0)); }
    R(0) = 0;
    gm_set_ptr(R(4) + TN_PREV, 0); gm_set_ptr(R(4) + TN_NEXT, 0); gm_set_ptr(R(4) + TN_PARENT, 0);
    return 1;
}
/* getTreeNextNotChild(): the next node of a depth-first walk that doesn't go into the children */
uint32_t cTreeNd_nextNotChild(GM_CTX) {
    R(0) = gm_ptr(R(3) + TN_NEXT);
    if (!z0(ctx, R(0))) return R(0);
    R(4) = gm_ptr(R(3) + TN_PARENT);
    for (int first = 1;; first = 0) {
        if (!first) {
            R(3) = gm_ptr(R(4) + TN_NEXT);
            if (!z0(ctx, R(3))) return R(3);
            R(4) = gm_ptr(R(4) + TN_PARENT);
        }
        if (z0(ctx, R(4))) return 0;
        GM_LOOP();
    }
}
/* getTreeNext(): the first child, else the above (a 16-byte frame for the call) */
uint32_t cTreeNd_next(GM_CTX) {
    GM_FN(0x801616C0); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(0) = gm_ptr(R(3) + TN_CHILD);
    if (z0(ctx, R(0))) { ctx->lr = 0x801616E0u; R(0) = cTreeNd_nextNotChild(GM_PASS); }
    R(3) = R(0);
    R(0) = lr;
    return R(3);
}
/* the constructor: forcedClear, returns this */
static uint32_t cTreeNd_ct(GM_CTX) {
    GM_FN(0x80161530); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, R(3));
    ctx->lr = 0x80161548u;
    cTreeNd_clear(GM_PASS);
    R(3) = R(31);
    R(0) = lr;
    return R(3);
}
/* ---- the same, as plain functions for the other natives (no registers; they call these directly) ---- */
int cLineMg_addTopLineNode(gptr self, gptr node) {
    if (!node) return 0;
    gptr first = gm_ptr(self + LM_FIRST);
    if (first) { gm_set_ptr(first + LN_PREV, node); gm_set_ptr(node + LN_NEXT, gm_ptr(self + LM_FIRST)); }
    else gm_set_ptr(self + LM_LAST, node);
    gm_set_ptr(self + LM_FIRST, node);
    return 1;
}
int cLineMg_addLastLineNode(gptr self, gptr node) {
    if (!node) return 0;
    gptr last = gm_ptr(self + LM_LAST);
    if (last) { gm_set_ptr(last + LN_NEXT, node); gm_set_ptr(node + LN_PREV, gm_ptr(self + LM_LAST)); }
    else gm_set_ptr(self + LM_FIRST, node);
    gm_set_ptr(self + LM_LAST, node);
    return 1;
}
int cLineMg_insertLineNode(gptr self, gptr node, gptr prev) {
    if (!prev) return cLineMg_addTopLineNode(self, node);
    if (!node) return 0;
    gm_set_ptr(node + LN_NEXT, gm_ptr(prev + LN_NEXT));
    gm_set_ptr(node + LN_PREV, prev);
    gm_set_ptr(prev + LN_NEXT, node);
    gptr next = gm_ptr(node + LN_NEXT);
    if (next) gm_set_ptr(next + LN_PREV, node);
    else gm_set_ptr(self + LM_LAST, node);
    return 1;
}
int cLineMg_removeLineNode(gptr self, gptr node) {
    if (!node) return 0;
    gptr prev = gm_ptr(node + LN_PREV);
    if (prev) gm_set_ptr(prev + LN_NEXT, gm_ptr(node + LN_NEXT));
    else if (node == gm_ptr(self + LM_FIRST)) gm_set_ptr(self + LM_FIRST, gm_ptr(node + LN_NEXT));
    gptr next = gm_ptr(node + LN_NEXT);
    if (next) gm_set_ptr(next + LN_PREV, gm_ptr(node + LN_PREV));
    else if (node == gm_ptr(self + LM_LAST)) gm_set_ptr(self + LM_LAST, gm_ptr(node + LN_PREV));
    gm_set_ptr(node + LN_PREV, 0);
    gm_set_ptr(node + LN_NEXT, 0);
    return 1;
}
void cTreeNd_forcedClear(gptr self) {
    gm_set_ptr(self + TN_PARENT, 0); gm_set_ptr(self + TN_CHILD, 0);
    gm_set_ptr(self + TN_PREV, 0); gm_set_ptr(self + TN_NEXT, 0);
}
int cTreeMg_addTreeNode(GM_CTX, gptr self, gptr node, gptr parent) {
    if (!node) return 0;
    gptr c = parent ? gm_ptr(parent + TN_CHILD) : gm_ptr(self + TM_ROOT);
    if (parent) gm_set_ptr(node + TN_PARENT, parent);
    if (!c) { gm_set_ptr(parent ? parent + TN_CHILD : self + TM_ROOT, node); return 1; }
    while (gm_ptr(c + TN_NEXT)) { c = gm_ptr(c + TN_NEXT); GM_LOOP(); }
    gm_set_ptr(c + TN_NEXT, node);
    gm_set_ptr(node + TN_PREV, c);
    return 1;
}
int cTreeMg_removeTreeNode(gptr self, gptr node) {
    if (!node) return 0;
    if (gm_ptr(node + TN_CHILD)) return 0;
    gptr prev = gm_ptr(node + TN_PREV);
    if (prev) gm_set_ptr(prev + TN_NEXT, gm_ptr(node + TN_NEXT));
    else {
        gptr parent = gm_ptr(node + TN_PARENT);
        if (parent) gm_set_ptr(parent + TN_CHILD, gm_ptr(node + TN_NEXT));
        else if (node == gm_ptr(self + TM_ROOT)) gm_set_ptr(self + TM_ROOT, gm_ptr(node + TN_NEXT));
    }
    gptr next = gm_ptr(node + TN_NEXT);
    if (next) gm_set_ptr(next + TN_PREV, gm_ptr(node + TN_PREV));
    gm_set_ptr(node + TN_PREV, 0); gm_set_ptr(node + TN_NEXT, 0); gm_set_ptr(node + TN_PARENT, 0);
    return 1;
}
gptr cTreeNd_getTreeNextNotChild(GM_CTX, gptr self) {
    gptr next = gm_ptr(self + TN_NEXT);
    if (next) return next;
    for (gptr p = gm_ptr(self + TN_PARENT); p; p = gm_ptr(p + TN_PARENT)) {
        GM_LOOP();
        if (gm_ptr(p + TN_NEXT)) return gm_ptr(p + TN_NEXT);
    }
    return 0;
}
gptr cTreeNd_getTreeNext(GM_CTX, gptr self) {
    gptr child = gm_ptr(self + TN_CHILD);
    return child ? child : cTreeNd_getTreeNextNotChild(GM_PASS, self);
}

/* ================================================================== hle entry points
 * The memory a call may change, for RT_GM_VERIFY: the manager, the node, and the nodes it links to
 * (worked out from the memory before the call). */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
static gptr nz(gptr p) { return p ? p : 0x80000000u; }      /* (a null link: an unchanged dummy range) */
static gptr last_sibling(gptr c) { while (c && gm_ptr(c + TN_NEXT)) c = gm_ptr(c + TN_NEXT); return c; }
static gptr tree_add_last(gptr mg, gptr parent) { return last_sibling(parent ? gm_ptr(parent + TN_CHILD) : gm_ptr(mg + TM_ROOT)); }

GM_HLE_INT(fn_80161020, SELF, 8, nz(A(1)), 8, nz(gm_ptr(SELF + LM_FIRST)), 8) { GM_RET(cLineMg_addTop(GM_PASS)); }       /* cLineMg_c::addTopLineNode */
GM_HLE_INT(fn_80160FE0, SELF, 8, nz(A(1)), 8, nz(gm_ptr(SELF + LM_LAST)), 8) { GM_RET(cLineMg_addLast(GM_PASS)); }       /* cLineMg_c::addLastLineNode */
GM_HLE_INT(fn_80160F10, SELF, 8, nz(A(1)), 8, nz(A(2)), 8, nz(A(2) ? gm_ptr(A(2) + LN_NEXT) : gm_ptr(SELF + LM_FIRST)), 8) {        /* cLineMg_c::insertLineNode */
    GM_RET(cLineMg_insert(GM_PASS));
}
GM_HLE_INT(fn_80160F60, SELF, 8, nz(A(1)), 8, nz(A(1) ? gm_ptr(A(1) + LN_PREV) : 0), 8, nz(A(1) ? gm_ptr(A(1) + LN_NEXT) : 0), 8) {   /* cLineMg_c::removeLineNode */
    GM_RET(cLineMg_remove(GM_PASS));
}
GM_HLE_VOID(fn_80161560, SELF, 16) { cTreeNd_clear(GM_PASS); }                                                                     /* cTreeNd_c::forcedClear */
GM_HLE_INT(fn_80161530, SELF, 16) { cTreeNd_ct(GM_PASS); }                                                       /* cTreeNd_c::cTreeNd_c */
GM_HLE_INT(fn_80161580, SELF, 4, nz(A(1)), 16, nz(A(2)), 16, nz(tree_add_last(SELF, A(2))), 16) {                                     /* cTreeMg_c::addTreeNode */
    GM_RET(cTreeMg_add(GM_PASS));
}
GM_HLE_INT(fn_80161620, SELF, 4, nz(A(1)), 16, nz(A(1) ? gm_ptr(A(1) + TN_PREV) : 0), 16, nz(A(1) ? gm_ptr(A(1) + TN_NEXT) : 0), 16,
           nz(A(1) ? gm_ptr(A(1) + TN_PARENT) : 0), 16) {                                                                             /* cTreeMg_c::removeTreeNode */
    GM_RET(cTreeMg_remove(GM_PASS));
}
GM_HLE_INT(fn_801616C0, SELF, 16) { GM_RET(cTreeNd_next(GM_PASS)); }                                                     /* cTreeNd_c::getTreeNext */
GM_HLE_INT(fn_80161700, SELF, 16) { GM_RET(cTreeNd_nextNotChild(GM_PASS)); }                                             /* cTreeNd_c::getTreeNextNotChild */
