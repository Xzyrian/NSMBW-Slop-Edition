/* gm_f_manager.c - fManager_c, the framework's main loop and its searches (f_manager.cpp).
 * Track B (gm.h, docs/DECOMP.md), instance 1. Lists and layout: gm_f_base.c.
 *
 * The main loop runs every frame: the delete list, the create list, the execute list, the draw
 * list (each calls its pack on every base in it), then the connect step over the whole tree. Bits
 * of m_StopProcInf skip a step. */
#include "gm.h"
#include "gm_nv.h"

int  fLiMgBaFu_lineListProc(GM_CTX, gptr self);                     /* gm_f_list.c */
int  fTrMgBaFu_treeListProc(GM_CTX, gptr self);
gptr fLiMgBa_searchNodeByID(GM_CTX, gptr self, uint32_t id);
gptr fTrMgBa_searchNodeByProfName(GM_CTX, gptr self, uint32_t prof, gptr parent);
gptr fTrMgBa_searchNodeByGroupType(GM_CTX, gptr self, uint32_t group, gptr parent);
uint32_t fManager_getSearchTableNum(gptr connect_node);             /* gm_f_base.c */

#define SDA 0x8042F680u
#define MG_CONNECT  0x80377A10u
#define MG_CREATE   0x80377A20u
#define MG_EXECUTE  0x80377A34u
#define MG_DRAW     0x80377A48u
#define MG_DELETE   0x80377A5Cu
#define MG_SEARCH   0x80377A70u
#define NOW_LOOP    (SDA - 0x6228)       /* m_nowLoopProc */
#define STOP_PROC   (SDA - 0x52D0)       /* m_StopProcInf: 1 connect, 2 create, 4 execute, 8 delete, 16 draw */

gptr fManager_searchBaseByID(GM_CTX, uint32_t id) { GM_FN(0x80162D00);
    gptr n = fLiMgBa_searchNodeByID(GM_PASS, MG_SEARCH + ((id << 3) & 0x38), id);
    return n ? gm_ptr(n + 8) : 0;
}
gptr fManager_searchBaseByProfName(GM_CTX, uint32_t prof, gptr parent) { GM_FN(0x80162D50);
    gptr n = fTrMgBa_searchNodeByProfName(GM_PASS, MG_CONNECT, prof, parent ? parent + 0x10 : 0);
    return n ? gm_ptr(n + 0x10) : 0;
}
gptr fManager_searchBaseByGroupType(GM_CTX, uint32_t group, gptr parent) { GM_FN(0x80162DB0);
    gptr n = fTrMgBa_searchNodeByGroupType(GM_PASS, MG_CONNECT, group, parent ? parent + 0x10 : 0);
    return n ? gm_ptr(n + 0x10) : 0;
}
void fManager_mainLoop(GM_CTX) { GM_FN(0x80162E10);
    if (!(gm_u32(STOP_PROC) & 8))  { gm_set_u32(NOW_LOOP, 4); fLiMgBaFu_lineListProc(GM_PASS, MG_DELETE); }
    if (!(gm_u32(STOP_PROC) & 2))  { gm_set_u32(NOW_LOOP, 2); fLiMgBaFu_lineListProc(GM_PASS, MG_CREATE); }
    if (!(gm_u32(STOP_PROC) & 4))  { gm_set_u32(NOW_LOOP, 3); fLiMgBaFu_lineListProc(GM_PASS, MG_EXECUTE); }
    if (!(gm_u32(STOP_PROC) & 16)) { gm_set_u32(NOW_LOOP, 5); fLiMgBaFu_lineListProc(GM_PASS, MG_DRAW); }
    if (!(gm_u32(STOP_PROC) & 1))  { gm_set_u32(NOW_LOOP, 1); fTrMgBaFu_treeListProc(GM_PASS, MG_CONNECT); }
    gm_set_u32(NOW_LOOP, 0);
}

/* ================================================================== the same, register-exact (part 48) */
#define R(n) ctx->r[n]
uint32_t fTrMgBa_find_r(GM_CTX, int group);                          /* gm_f_list.c */
uint32_t fLiMgBa_searchID_r(GM_CTX);
uint32_t fLiMgBaFu_proc_r(GM_CTX);
uint32_t fTrMgBaFu_proc_r(GM_CTX);
static inline int z0(ppc_context *ctx, uint32_t v) { cr_cmp_s(ctx, 0, (int32_t)v, 0); return v == 0; }
/* searchBaseByID(id) */
static uint32_t search_id_r(GM_CTX) {
    GM_FN(0x80162D00); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(5) = MG_SEARCH; R(4) = R(3);
    R(0) = (R(3) << 3) & 0x38u;
    R(3) = R(5) + R(0);
    ctx->lr = 0x80162D24u; fLiMgBa_searchID_r(GM_PASS);
    if (!z0(ctx, R(3))) R(3) = gm_ptr(R(3) + 8); else R(3) = 0;
    R(0) = lr;
    return R(3);
}
/* searchBaseByProfName / searchBaseByGroupType(key, after) */
static uint32_t search_tree_r(GM_CTX, int group) {
    GM_FN(group ? 0x80162DB0u : 0x80162D50u); GM_LR_KEEP;           /* FNADDR */
    uint32_t lr = ctx->lr;
    R(5) = R(4);
    int none = z0(ctx, R(5));
    R(4) = R(3); R(3) = MG_CONNECT;
    R(5) = none ? 0 : R(5) + 0x10;
    ctx->lr = group ? 0x80162DE0u : 0x80162D80u; fTrMgBa_find_r(GM_PASS, group);
    if (!z0(ctx, R(3))) R(3) = gm_ptr(R(3) + 0x10); else R(3) = 0;
    R(0) = lr;
    return R(3);
}
/* mainLoop(): delete, create, execute, draw, connect - each unless its bit of m_StopProcInf is set */
static void main_loop_r(GM_CTX) {
    GM_FN(0x80162E10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    static const struct { uint32_t bit, loop, list, ra; int tree; } step[5] = {
        { 8, 4, MG_DELETE, 0x80162E44u, 0 }, { 2, 2, MG_CREATE, 0x80162E60u, 0 }, { 4, 3, MG_EXECUTE, 0x80162E7Cu, 0 },
        { 16, 5, MG_DRAW, 0x80162E98u, 0 }, { 1, 1, MG_CONNECT, 0x80162EB4u, 1 } };
    NV_R(31, MG_CONNECT);
    for (int i = 0; i < 5; i++) {
        R(0) = gm_u32(STOP_PROC) & step[i].bit;
        if (!z0(ctx, R(0))) continue;
        R(0) = step[i].loop; gm_set_u32(NOW_LOOP, R(0));
        R(3) = step[i].list;
        ctx->lr = step[i].ra;
        if (step[i].tree) fTrMgBaFu_proc_r(GM_PASS); else fLiMgBaFu_proc_r(GM_PASS);
    }
    R(0) = 0; gm_set_u32(NOW_LOOP, 0);
    R(0) = lr;
}

/* ================================================================== hle entry points */
#define A(i) GM_ARG(i)
GM_HLE_INT(fn_80162CF0, A(0), 0x40) { GM_RET(fManager_getSearchTableNum(A(0))); }                                    /* fManager_c::getSearchTableNum */
GM_HLE_INT(search__7fBase_cFUi, MG_SEARCH, 0x40) { GM_RET(search_id_r(GM_PASS)); }               /* fManager_c::searchBaseByID */
GM_HLE_INT(search__7fBase_cF6ActorsP7fBase_c, MG_CONNECT, 4) { GM_RET(search_tree_r(GM_PASS, 0)); }
GM_HLE_INT(searchByBaseType__7fBase_cFiP7fBase_c, MG_CONNECT, 4) { GM_RET(search_tree_r(GM_PASS, 1)); }
GM_HLE(fn_80162E10) { main_loop_r(GM_PASS); }                                                                 /* fManager_c::mainLoop */

/* (part 54) fManagerSearch / a two-word list head: cleared */
GM_HLE_VOID(fn_80162FF0, A(0), 8) { ctx->r[0] = 0; gm_set_u32(A(0), 0); gm_set_u32(A(0) + 4, 0); }
