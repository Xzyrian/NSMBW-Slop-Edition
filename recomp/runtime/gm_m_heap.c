/* gm_m_heap.c - mLib's heap helpers (mHeap): option flags, the current heap, exp / frame / unit
 * heaps made inside a parent heap (with their size costs), adjusting and destroying frame heaps,
 * the game / archive / command / dylink / assert heaps. Track B (gm.h, docs/DECOMP.md),
 * instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_heap.cpp) and checked against the
 * recompiled USA rev 2 code (0x8016E4B0-0x8016EB9C). The EGG heaps stay recompiled; a parent heap
 * is called through its vtable (+20 alloc, +24 free, +28 destroy, +40 getAllocatableSize,
 * +44 adjust). The non-volatile registers are mirrored around nested calls (gm_nv.h). */
#include "gm.h"
#include "gm_nv.h"

#define SDA 0x8042F680u
#define CURRENT_HEAP (SDA - 18544)       /* EGG::Heap::sCurrentHeap */
#define SAVED_HEAP  (SDA - 21048)        /* mHeap::s_SavedCurrentHeap */
#define ARCHIVE_HEAP (SDA - 21044)       /* mHeap::g_archiveHeap / g_commandHeap / g_dylinkHeap / g_assertHeap */
#define COMMAND_HEAP (SDA - 21040)
#define DYLINK_HEAP (SDA - 21036)
#define ASSERT_HEAP (SDA - 21032)
#define DEFAULT_GAME_HEAP (SDA - 25072)  /* mHeap::g_DefaultGameHeapId (a byte) */
#define GAME_HEAPS  0x80377C48u          /* mHeap::g_gameHeaps[3] */
#define GAME_HEAP_NAMES 0x802F5A40u      /* mHeap::s_GameHeapNames[3] */
#define ARCHIVE_NAME 0x80329B58u         /* (the heap names) */
#define COMMAND_NAME 0x80329B90u
#define DYLINK_NAME 0x80329BC0u
#define ASSERT_NAME 0x80329BF0u
#define F_BECOME_CURRENT 0x802B9170u     /* EGG::Heap::becomeCurrentHeap */
#define F_EXP_CREATE 0x802B9360u         /* EGG::ExpHeap::create(buffer, size, opt) */
#define F_EXP_CREATE2 0x802B9430u        /* EGG::ExpHeap::create(size, parent, opt) */
#define F_EXP_ALLOC_MODE 0x802B9650u     /* EGG::ExpHeap::setAllocMode */
#define F_FRM_CREATE 0x802B9840u         /* EGG::FrmHeap::create */
#define F_UNIT_CREATE 0x802B9B80u        /* EGG::UnitHeap::create */
#define F_UNIT_SIZE 0x802B9DF0u          /* EGG::UnitHeap::calcHeapSize */
#define F_HEAP_DUMP 0x802B9070u          /* EGG::Heap::dump */
#define F_ASSERT_MIN 0x802BA2B0u         /* EGG::AssertHeap::getMinSizeForCreate */
#define F_ASSERT_CREATE 0x802BA000u      /* EGG::AssertHeap::create */

#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f
#define V(o, off) gm_u32(gm_u32(o) + (off))

static uint32_t opt_flag(uint32_t o) {                                    /* GetOptFlag */
    uint32_t r = (o & 1) ? 1 : 0;
    if (o & 2) r |= 2;
    if (o & 4) r = (r | 4) & 0xFFFF;
    return r;
}
static uint32_t heap_cost(uint32_t size, uint32_t align, uint32_t head) { uint32_t m = align - 1; return size + ((m + head) & ~m); }

/* createExpHeap / createFrmHeap(size or -1 for all, parent, name, align, opt) */
static gptr create_heap(GM_CTX, int frm, uint32_t size, gptr parent, gptr name, uint32_t align, uint32_t opt) {
    FN(frm ? 0x8016E630u : 0x8016E500u); GM_NV_KEEP;
    if (!parent) parent = gm_u32(CURRENT_HEAP);
    if (align < 0x20) align = 32;
    NV_R(26, parent); NV_R(27, name); NV_R(29, align); NV_R(28, opt);
    uint32_t n;
    if (size + 0x10000u != 0xFFFFu) n = heap_cost(size, align, frm ? 128 : 136);   /* (frmHeapCost / expHeapCost: leaves) */
    else n = GM_CALLR(frm ? 0x8016E6A0u : 0x8016E570u, V(parent, 40), 2, parent, align);                     /* getAllocatableSize */
    NV_R(31, n);
    gptr buf = GM_CALLR(frm ? 0x8016E6C0u : 0x8016E590u, V(parent, 20), 3, parent, n, align);
    NV_R(30, buf); NV_R(29, 0);
    if (!buf) return 0;
    gptr h = GM_CALLR(frm ? 0x8016E6ECu : 0x8016E5BCu, frm ? F_FRM_CREATE : F_EXP_CREATE, 3, buf, n, opt_flag(opt) & 0xFFFF);
    NV_R(29, h);
    if (!h) GM_CALLR(frm ? 0x8016E710u : 0x8016E5E0u, V(parent, 24), 2, parent, buf);
    else if (name) gm_set_u32(h + 52, name);
    return h;
}
/* createUntHeap(unit size, count, parent, name, align, opt) */
static gptr create_unit_heap(GM_CTX, uint32_t size, uint32_t count, gptr parent, gptr name, uint32_t align, uint32_t opt) {
    FN(0x8016E7F0); GM_NV_KEEP;
    if (!parent) parent = gm_u32(CURRENT_HEAP);
    if (align < 0x20) align = 32;
    NV_R(24, size); NV_R(25, parent); NV_R(26, name); NV_R(27, align); NV_R(28, opt);
    uint32_t n = GM_CALLR(0x8016E83Cu, F_UNIT_SIZE, 3, size, count, align);              /* (untHeapCost: a tail call) */
    NV_R(31, n); NV_R(30, 0);
    gptr buf = GM_CALLR(0x8016E860u, V(parent, 20), 3, parent, n, align);
    NV_R(29, buf);
    if (!buf) return 0;
    gptr h = GM_CALLR(0x8016E890u, F_UNIT_CREATE, 5, buf, n, size, align, opt_flag(opt) & 0xFFFF);
    NV_R(30, h);
    if (!h) GM_CALLR(0x8016E8B4u, V(parent, 24), 2, parent, buf);
    else if (name) gm_set_u32(h + 52, name);
    return h;
}
/* createHeap(size, parent, name): an exp heap (thread-safe, fast allocation) */
static gptr create_named_heap(GM_CTX, uint32_t size, gptr parent, gptr name) {
    FN(0x8016E8F0); GM_NV_KEEP;
    NV_R(30, name); NV_R(29, parent);
    gptr h = GM_CALLR(0x8016E918u, F_EXP_CREATE2, 3, size, parent, 4);
    NV_R(31, h);
    if (h) { GM_CALLR(0x8016E92Cu, F_EXP_ALLOC_MODE, 2, h, 0); if (name) gm_set_u32(h + 52, name); }
    else GM_CALLR(0x8016E944u, F_HEAP_DUMP, 1, parent);
    return h;
}
static uint32_t adjust_frm_heap(GM_CTX, gptr h) {
    FN(0x8016E760); GM_NV_KEEP;
    uint32_t r = 0;
    NV_R(30, 0);
    if (h) {
        uint32_t fr = GM_CALLR(0x8016E790u, V(h, 44), 1, h);                            /* adjust */
        NV_R(31, fr);
        uint32_t m = heap_cost(0, 4, 128);
        if (fr >= m) r = fr - m;
    }
    return r;
}
static gptr create_game_heap(GM_CTX, uint32_t idx, uint32_t size, gptr parent) {
    FN(0x8016E9F0); GM_NV_KEEP;
    NV_R(28, idx);
    if (idx < 1 || idx > 2) return 0;
    uint32_t o4 = idx << 2;
    NV_R(29, o4); NV_R(30, 0x80370000u); NV_R(31, GAME_HEAPS);
    gptr h = NCALL(0x8016EA60u, create_named_heap(GM_PASS, size, parent, gm_u32(GAME_HEAP_NAMES + o4)));
    gm_set_u32(GAME_HEAPS + o4, h);
    if ((int32_t)idx == (int32_t)gm_u8(DEFAULT_GAME_HEAP)) gm_set_u32(GAME_HEAPS, gm_u32(GAME_HEAPS + o4));
    return gm_u32(GAME_HEAPS + o4);
}
static gptr create_heap_to(GM_CTX, uint32_t addr, uint32_t ra, uint32_t size, gptr parent, gptr name, uint32_t at) {
    FN(addr);
    gptr h = NCALL(ra, create_named_heap(GM_PASS, size, parent, name));
    gm_set_u32(at, h);
    return h;
}

/* ================================================================== hle entry points
   On (19): reached by the test runs, or run inside them (GetOptFlag, expHeapCost, createHeap).
   Written but off (not reached): untHeapCost, createGameHeap. */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
E(fn_8016E4B0) { GM_RET(opt_flag(A(0))); }                                                     /* mHeap::GetOptFlag */
E(fn_8016E4F0) { GM_RET(GM_CALLR(ctx->lr, F_BECOME_CURRENT, 1, A(0))); }                                  /* ::setCurrentHeap */
E(fn_8016E500) { GM_RET(create_heap(GM_PASS, 0, A(0), A(1), A(2), A(3), A(4))); }               /* ::createExpHeap */
E(fn_8016E610) { GM_RET(heap_cost(A(0), A(1), 136)); }                                         /* ::expHeapCost */
E(fn_8016E630) { GM_RET(create_heap(GM_PASS, 1, A(0), A(1), A(2), A(3), A(4))); }               /* ::createFrmHeap */
E(fn_8016E740) { gptr h = A(0); if (h) GM_RET(GM_CALLR(ctx->lr, V(h, 28), 1, h)); }                       /* ::destroyFrmHeap */
E(fn_8016E760) { GM_RET(adjust_frm_heap(GM_PASS, A(0))); }                                     /* ::adjustFrmHeap */
E(fn_8016E7D0) { GM_RET(heap_cost(A(0), A(1), 128)); }                                         /* ::frmHeapCost */
E(fn_8016E7F0) { GM_RET(create_unit_heap(GM_PASS, A(0), A(1), A(2), A(3), A(4), A(5))); }       /* ::createUntHeap */
E(fn_8016E8E0) { GM_RET(GM_CALLR(ctx->lr, F_UNIT_SIZE, 3, A(0), A(1), A(2))); }                           /* ::untHeapCost */
E(fn_8016E8F0) { GM_RET(create_named_heap(GM_PASS, A(0), A(1), A(2))); }                       /* ::createHeap */
E(fn_8016E970) { gm_set_u32(SAVED_HEAP, gm_u32(CURRENT_HEAP)); }                                /* ::saveCurrentHeap */
E(fn_8016E980) {                                                                               /* ::restoreCurrentHeap */
    FN(0x8016E980);
    GM_CALLR(0x8016E994u, F_BECOME_CURRENT, 1, gm_u32(SAVED_HEAP));
    gm_set_u32(SAVED_HEAP, 0);
}
E(fn_8016E9B0) {                                                                               /* ::createFrmHeapToCurrent */
    GM_LR_KEEP; FN(0x8016E9B0); GM_NV_KEEP;
    gptr h = NCALL(0x8016E9C4u, create_heap(GM_PASS, 1, A(0), A(1), A(2), A(3), A(4)));
    NV_R(31, h);
    if (h) gm_set_u32(SAVED_HEAP, GM_CALLR(0x8016E9D4u, F_BECOME_CURRENT, 1, h));         /* (setCurrentHeap) */
    GM_RET(h);
}
E(fn_8016E9F0) { GM_LR_KEEP; GM_RET(create_game_heap(GM_PASS, A(0), A(1), A(2))); }             /* ::createGameHeap */
E(fn_8016EAA0) { GM_LR_KEEP; GM_RET(create_game_heap(GM_PASS, 1, A(0), A(1))); }                /* ::createGameHeap1 (a tail call) */
E(fn_8016EAB0) { GM_LR_KEEP; GM_RET(create_game_heap(GM_PASS, 2, A(0), A(1))); }                /* ::createGameHeap2 */
E(fn_8016EAC0) { GM_LR_KEEP; GM_RET(create_heap_to(GM_PASS, 0x8016EAC0u, 0x8016EAD8u, A(0), A(1), ARCHIVE_NAME, ARCHIVE_HEAP)); }   /* FNADDR ::createArchiveHeap */
E(fn_8016EAF0) { GM_LR_KEEP; GM_RET(create_heap_to(GM_PASS, 0x8016EAF0u, 0x8016EB08u, A(0), A(1), COMMAND_NAME, COMMAND_HEAP)); }   /* FNADDR ::createCommandHeap */
E(fn_8016EB20) { GM_LR_KEEP; GM_RET(create_heap_to(GM_PASS, 0x8016EB20u, 0x8016EB38u, A(0), A(1), DYLINK_NAME, DYLINK_HEAP)); }     /* FNADDR ::createDylinkHeap */
E(fn_8016EB50) {                                                                               /* ::createAssertHeap */
    FN(0x8016EB50); GM_NV_KEEP;
    gptr parent = A(0);
    NV_R(31, ASSERT_NAME); NV_R(30, parent);
    uint32_t sz = GM_CALLR(0x8016EB74u, F_ASSERT_MIN, 0);
    gptr h = GM_CALLR(0x8016EB7Cu, F_ASSERT_CREATE, 2, sz, parent);
    gm_set_u32(ASSERT_HEAP, h);
    gm_set_u32(h + 52, ASSERT_NAME);
    GM_RET(gm_u32(ASSERT_HEAP));
}
