/* gm_nw4r_ut.c - nw4r::ut's lists: the intrusive List (List_Insert with the Append / Prepend
 * cases inlined, List_Remove, List_GetNext / List_GetPrev), detail::LinkListImpl (dtor, Clear,
 * Erase(it), Erase(first, last), Insert(it, node)) and IsValidBinaryFile. Track B (gm.h,
 * docs/DECOMP.md), instance 1. List_GetNext is called ~400,000 times per test run (g3d's scene
 * walks).
 *
 * Decompiled against NSMBW-Decomp (source/lib/nw4r/ut/ut_list.cpp; LinkListImpl / the binary
 * file check from the recompiled code) and checked against the recompiled USA rev 2 code
 * (0x80228E60-0x80229230). Register-exact (R(n)); the loops keep their back-edge polls.
 *
 * List: +0 head, +4 tail, +8 count (u16), +10 the link's offset in an object (u16); a Link: +0
 * prev, +4 next. LinkListImpl: +0 count, +4 the end node (+4 next / +0 prev ... a node: +0 next,
 * +4 prev). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

/* ================================================================== List */
/* the list was empty: obj is head and tail (r5 = obj) */
static inline void list_first(GM_CTX) {
    R(4) = gm_u16(R(3) + 10);
    R(0) = 0;
    R(4) = R(5) + R(4);
    gm_set_u32(R(4) + 4, 0); gm_set_u32(R(4), 0);
    R(4) = gm_u16(R(3) + 8);
    gm_set_u32(R(3), R(5));
    R(0) = R(4) + 1;
    gm_set_u32(R(3) + 4, R(5));
    gm_set_u16(R(3) + 8, (uint16_t)R(0));
}
/* List_Insert(list, target, obj): before target (null: append) */
static void list_insert(GM_CTX) {
    if (cmps(ctx, (int32_t)R(4), 0) == 0) {                                  /* append */
        R(0) = gm_u32(R(3));
        if (cmps(ctx, (int32_t)R(0), 0) == 0) { list_first(GM_PASS); return; }
        R(6) = gm_u16(R(3) + 10);
        R(0) = 0;
        R(4) = gm_u32(R(3) + 4);
        R(6) = R(6) + R(5); gm_set_u32(R(6), R(4));                          /* (stwux) prev = tail */
        gm_set_u32(R(6) + 4, 0);
        R(4) = gm_u32(R(3) + 4);
        R(0) = gm_u16(R(3) + 10);
        R(4) = R(4) + R(0);
        gm_set_u32(R(4) + 4, R(5));                                          /* tail->next = obj */
        R(4) = gm_u16(R(3) + 8);
        gm_set_u32(R(3) + 4, R(5));
        R(0) = R(4) + 1;
        gm_set_u16(R(3) + 8, (uint16_t)R(0));
        return;
    }
    R(0) = gm_u32(R(3));
    if (cmpu(ctx, R(4), R(0)) == 0) {                                        /* prepend */
        if (cmps(ctx, (int32_t)R(0), 0) == 0) { list_first(GM_PASS); return; }
        R(4) = gm_u16(R(3) + 10);
        R(0) = 0;
        R(4) = R(4) + R(5); gm_set_u32(R(4), 0);                             /* (stwux) prev = null */
        R(0) = gm_u32(R(3));
        gm_set_u32(R(4) + 4, R(0));                                          /* next = head */
        R(4) = gm_u32(R(3));
        R(0) = gm_u16(R(3) + 10);
        gm_set_u32(R(4) + R(0), R(5));                                       /* head->prev = obj */
        R(4) = gm_u16(R(3) + 8);
        gm_set_u32(R(3), R(5));
        R(0) = R(4) + 1;
        gm_set_u16(R(3) + 8, (uint16_t)R(0));
        return;
    }
    R(0) = gm_u16(R(3) + 10);
    R(6) = gm_u32(R(4) + R(0));                                              /* target's prev */
    R(7) = R(5) + R(0);
    gm_set_u32(R(5) + R(0), R(6));
    R(6) = R(6) + R(0);
    gm_set_u32(R(7) + 4, R(4));
    gm_set_u32(R(6) + 4, R(5));
    R(0) = gm_u16(R(3) + 10);
    gm_set_u32(R(4) + R(0), R(5));
    R(4) = gm_u16(R(3) + 8);
    R(0) = R(4) + 1;
    gm_set_u16(R(3) + 8, (uint16_t)R(0));
}
/* List_Remove(list, obj) */
static void list_remove(GM_CTX) {
    R(0) = gm_u16(R(3) + 10);
    R(6) = R(4) + R(0);
    R(4) = gm_u32(R(4) + R(0));
    if (cmps(ctx, (int32_t)R(4), 0) == 0) { R(0) = gm_u32(R(6) + 4); gm_set_u32(R(3), R(0)); }
    else { R(4) = R(4) + R(0); R(0) = gm_u32(R(6) + 4); gm_set_u32(R(4) + 4, R(0)); }
    R(5) = gm_u32(R(6) + 4);
    if (cmps(ctx, (int32_t)R(5), 0) == 0) { R(0) = gm_u32(R(6)); gm_set_u32(R(3) + 4, R(0)); }
    else { R(0) = gm_u16(R(3) + 10); R(4) = gm_u32(R(6)); gm_set_u32(R(5) + R(0), R(4)); }
    R(0) = 0;
    gm_set_u32(R(6), 0); gm_set_u32(R(6) + 4, 0);
    R(4) = gm_u16(R(3) + 8);
    R(0) = R(4) - 1;
    gm_set_u16(R(3) + 8, (uint16_t)R(0));
}

/* ================================================================== detail::LinkListImpl */
/* unlink every node from r6 up to r5 (r0 = 0): the common loop of Clear / Erase(first, last) */
static inline void lli_unlink(GM_CTX, int t1, int t2) {
    goto test;
body:
    R(t1) = gm_u32(R(6)); R(t2) = gm_u32(R(6) + 4);
    gm_set_u32(R(t1) + 4, R(t2)); gm_set_u32(R(t2), R(t1));
    R(t2) = gm_u32(R(3)); R(t2) = R(t2) - 1; gm_set_u32(R(3), R(t2));
    gm_set_u32(R(6), 0); gm_set_u32(R(6) + 4, 0);
    R(6) = R(t1);
test:
    if (cmpu(ctx, R(6), R(5)) != 0) { GM_LOOP(); goto body; }
}
static void lli_dtor(GM_CTX) {
    GM_FN(0x80229030); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(3);
    if (c != 0) {
        R(7) = gm_u32(R(3) + 4); R(6) = R(3) + 4; R(0) = 0;
        goto test;
    body:
        R(8) = gm_u32(R(7)); R(5) = gm_u32(R(7) + 4);
        gm_set_u32(R(8) + 4, R(5)); gm_set_u32(R(5), R(8));
        R(5) = gm_u32(R(3)); R(5) = R(5) - 1; gm_set_u32(R(3), R(5));
        gm_set_u32(R(7), 0); gm_set_u32(R(7) + 4, 0);
        R(7) = R(8);
    test:
        if (cmpu(ctx, R(7), R(6)) != 0) { GM_LOOP(); goto body; }
        if (cmps(ctx, (int32_t)R(4), 0) > 0) { R(3) = R(31); GM_CALLV(0x8022909Cu, 0x802B9280u, 0); }
    }
    R(3) = R(31);
    R(0) = lr;
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#ifdef GM_UT_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_UT_COUNT)    /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_80228E60, 12) { list_insert(GM_PASS); }                                       /* nw4r::ut::List_Insert */
E(fn_80228F80, 12) { list_remove(GM_PASS); }                                       /* ::List_Remove */
E(fn_80228FF0, 12) {                                                               /* ::List_GetNext */
    if (cmps(ctx, (int32_t)R(4), 0) == 0) { R(3) = gm_u32(R(3)); return; }
    R(0) = gm_u16(R(3) + 10); R(3) = R(4) + R(0); R(3) = gm_u32(R(3) + 4);
}
E(fn_80229010, 12) {                                                               /* ::List_GetPrev */
    if (cmps(ctx, (int32_t)R(4), 0) == 0) { R(3) = gm_u32(R(3) + 4); return; }
    R(0) = gm_u16(R(3) + 10); R(3) = gm_u32(R(4) + R(0));
}
E(__dt__Q44nw4r2ut6detail12LinkListImplFv, 12) { lli_dtor(GM_PASS); }              /* detail::LinkListImpl::~LinkListImpl */
E(fn_802290C0, 12) {                                                               /* ::Erase(first, last) */
    R(6) = gm_u32(R(4)); R(0) = 0; R(5) = gm_u32(R(6));
    lli_unlink(GM_PASS, 7, 4);
    R(3) = R(5);
}
E(fn_80229110, 12) {                                                               /* ::Clear */
    R(6) = gm_u32(R(3) + 4); R(5) = R(3) + 4; R(0) = 0;
    lli_unlink(GM_PASS, 7, 4);
}
E(fn_80229160, 12) {                                                               /* ::Insert(it, node) */
    R(4) = gm_u32(R(4)); R(6) = gm_u32(R(4) + 4);
    gm_set_u32(R(5) + 4, R(6)); gm_set_u32(R(5), R(4));
    gm_set_u32(R(4) + 4, R(5)); gm_set_u32(R(6), R(5));
    R(4) = gm_u32(R(3)); R(0) = R(4) + 1; gm_set_u32(R(3), R(0));
    R(3) = R(5);
}
E(Erase__Q44nw4r2ut6detail12LinkListImplFPQ34nw4r2ut12LinkListNode, 12) {          /* ::Erase(node) */
    R(6) = gm_u32(R(4)); R(0) = 0; R(5) = gm_u32(R(4) + 4);
    gm_set_u32(R(6) + 4, R(5)); gm_set_u32(R(5), R(6));
    R(5) = gm_u32(R(3)); R(5) = R(5) - 1; gm_set_u32(R(3), R(5));
    R(3) = R(6);
    gm_set_u32(R(4), 0); gm_set_u32(R(4) + 4, 0);
}
E(fn_802291C0, 4) {                                                                /* nw4r::ut::IsValidBinaryFile(header, sig, version, minBlocks) */
    R(0) = gm_u32(R(3));
    if (cmpu(ctx, R(0), R(4)) != 0) { R(3) = 0; return; }
    R(0) = gm_u16(R(3) + 4);
    if (cmpu(ctx, R(0), 0xFEFF) != 0) { R(3) = 0; return; }                  /* the byte-order mark */
    R(0) = gm_u16(R(3) + 6);
    if (cmpu(ctx, R(0), R(5)) != 0) { R(3) = 0; return; }
    R(4) = (R(6) << 3) & 0x7FFF8u;
    R(5) = gm_u32(R(3) + 8);
    R(0) = R(4) + 16;
    if (cmpu(ctx, R(5), R(0)) < 0) { R(3) = 0; return; }
    R(3) = gm_u16(R(3) + 14);
    R(0) = R(3) - R(6);
    R(3) = R(3) | ~R(6);
    R(0) = (R(0) >> 1) & 0x7FFFFFFFu;
    R(0) = R(3) - R(0);
    R(3) = R(0) >> 31;                                                       /* blocks >= minBlocks (unsigned) */
}
