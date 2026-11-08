/* gm_m_allocator.c - mLib's allocators: mAllocatorDummyHeap_c (the heap every mAllocator_c
 * starts on: allocates nothing), mAllocator_c (an EGG::Allocator attached to a heap) and
 * mHeapAllocator_c (one that owns a frame heap), plus the mAng3_c unit vectors. Track B (gm.h,
 * docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_allocator.cpp) and checked against the
 * recompiled USA rev 2 code (0x8016A460-0x8016AA6C). EGG::Allocator: +16 vtable (the C++ part),
 * +20 the heap, +24 the alignment. The non-volatile registers are mirrored around nested calls
 * (gm_nv.h). */
#include "gm.h"
#include "gm_nv.h"

#define SDA 0x8042F680u
#define CURRENT_HEAP (SDA - 18544)       /* EGG::Heap::sCurrentHeap */
#define DUMMY_HEAP  (SDA - 21144)        /* mAllocatorDummyHeap_c::m_instance */
#define ANG3_UNITS  (SDA - 21136)        /* (mAng3_c: 0, x, y, z units - 8 bytes apart) */
#define VT_DUMMY_HEAP 0x803296D0u
#define VT_ALLOCATOR 0x803296BCu         /* (the vtables the constructors / destructors set) */
#define VT_HEAP_ALLOCATOR 0x803296A8u
#define F_HEAP_CT   0x802BA2D0u          /* EGG::Heap::Heap */
#define F_HEAP_DT   0x802B8C20u
#define F_EGG_ALLOCATOR_CT 0x802B8A70u   /* EGG::Allocator::Allocator(heap, align) */
#define F_EGG_ALLOCATOR_DT 0x802B8AD0u
#define F_EGG_ALLOC 0x802B8B10u          /* EGG::Allocator::alloc / free */
#define F_EGG_FREE  0x802B8B30u
#define F_NEW       0x802B9240u
#define F_DELETE    0x802B9280u
#define F_CREATE_FRM 0x8016E630u         /* mHeap::createFrmHeap / adjustFrmHeap / saveCurrentHeap ... */
#define F_ADJUST_FRM 0x8016E760u
#define F_SAVE_HEAP 0x8016E970u
#define F_RESTORE_HEAP 0x8016E980u
#define F_SET_HEAP  0x8016E4F0u

#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f
#define V(o, off) gm_u32(gm_u32(o) + (off))

static gptr dummy_ctor(GM_CTX, gptr self) {
    FN(0x8016A480); GM_NV_KEEP;
    NV_R(31, self);
    GM_CALLR(0x8016A498u, F_HEAP_CT, 1, self);                                           /* (r4 passed on as it came) */
    gm_set_u16(self + 28, 0);
    gm_set_u32(self, VT_DUMMY_HEAP);
    gm_set_u32(DUMMY_HEAP, self);
    return self;
}
/* a destructor: the base's, then delete when flags > 0 */
static gptr plain_dtor(GM_CTX, uint32_t addr, uint32_t base_dt, gptr self, int32_t flags) {
    uint32_t ra = addr == 0x8016A4D0u ? 0x8016A4FCu : 0x8016A65Cu;      /* (the base destructor's / delete's return addresses) */
    FN(addr); GM_NV_KEEP;
    NV_R(31, flags); NV_R(30, self);
    if (self) { GM_CALLR(ra, base_dt, 2, self, 0); if (flags > 0) GM_CALLR(ra + 0x10, F_DELETE, 1, self); }
    return self;
}
static gptr alloc_ctor(GM_CTX, gptr self) {
    FN(0x8016A5E0); GM_NV_KEEP;
    NV_R(31, self);
    GM_CALLR(0x8016A608u, F_EGG_ALLOCATOR_CT, 3, self, gm_u32(DUMMY_HEAP), 4);          /* (getInstance: a leaf) */
    gm_set_u32(self + 16, VT_ALLOCATOR);
    return self;
}
static uint32_t alloc_attach(GM_CTX, gptr self, gptr heap, uint32_t align) {
    FN(0x8016A690);
    if (!heap) heap = gm_u32(CURRENT_HEAP);
    gm_set_u32(self + 24, align);
    gm_set_u32(self + 20, heap);
    GM_CALLR(0x8016A6CCu, V(heap, 16), 3, heap, self, align);                            /* initAllocator */
    return 1;
}
static void destroy_heap(GM_CTX, gptr self) {
    FN(0x8016A880); GM_NV_KEEP;
    NV_R(30, self);
    gptr d = gm_u32(DUMMY_HEAP), h = gm_u32(self + 20);
    NV_R(31, d);
    if (h == d) return;
    GM_CALLR(0x8016A8C0u, V(h, 28), 1, h);                                 /* destroy */
    gm_set_u32(self + 20, d);
}
/* EGG::Heap::dynamicCastToFrm then mHeap::adjustFrmHeap */
static uint32_t adjust_cast(GM_CTX, gptr h, uint32_t ra) {               /* (ra: getHeapKind's, adjustFrmHeap's is +0x18) */
    NV_R(31, h);
    if (h && GM_CALLR(ra, V(h, 12), 1, h) != 2) h = 0;                         /* getHeapKind: frame */
    if (!h) NV_R(31, 0);
    return GM_CALLR(ra + 0x18, F_ADJUST_FRM, 1, h);
}
static uint32_t ha_create(GM_CTX, gptr self, uint32_t size, gptr parent, gptr name, uint32_t align, uint32_t opt) {
    FN(0x8016A7F0); GM_NV_KEEP;
    NV_R(26, self); NV_R(27, size); NV_R(28, parent); NV_R(29, name); NV_R(30, align); NV_R(31, opt);
    NCALL(0x8016A820u, destroy_heap(GM_PASS, self));
    gptr h = GM_CALLR(0x8016A838u, F_CREATE_FRM, 5, size, parent, name, align, opt);
    if (!h) return 0;
    NCALL(0x8016A858u, alloc_attach(GM_PASS, self, h, align));
    return 1;
}

/* ================================================================== hle entry points
   On (26): reached by the test runs, run inside them (the dummy heap's constructor) or empty /
   return-0 bodies. Written but off (not reached): the dummy heap's destructor, mAllocator_c::alloc. */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
/* mAllocatorDummyHeap_c */
E(fn_8016A460) { GM_RET(0); }                                                                  /* AllocatorAllocForDummyHeap */
E(fn_8016A470) { }                                                                             /* AllocatorFreeForDummyHeap */
E(fn_8016A480) { GM_RET(dummy_ctor(GM_PASS, A(0))); }                                          /* ::mAllocatorDummyHeap_c */
E(fn_8016A4D0) { GM_RET(plain_dtor(GM_PASS, 0x8016A4D0u, F_HEAP_DT, A(0), (int32_t)A(1))); }  /* FNADDR ::~ */
E(fn_8016A530) { GM_RET(0); }                                                                  /* ::getHeapKind */
E(fn_8016A540) {                                                                               /* ::initAllocator(allocator, align) */
    gptr a = A(1);
    gm_set_u32(a + 0, ctx->r[2] - 21424);                                  /* (sAllocatorFunc, in sdata2) */
    uint32_t h = gm_u32(A(0) + 16);
    gm_set_u32(a + 4, h); gm_set_u32(a + 8, A(2)); gm_set_u32(a + 12, 0);
    GM_RET(h);
}
E(fn_8016A560) { GM_RET(0); }                                                                  /* ::alloc */
E(fn_8016A570) { }                                                                             /* ::free */
E(fn_8016A580) { }                                                                             /* ::destroy */
E(fn_8016A590) { GM_RET(0); }                                                                  /* ::resizeForMBlock */
E(fn_8016A5A0) { GM_RET(0); }                                                                  /* ::getTotalFreeSize */
E(fn_8016A5B0) { GM_RET(0); }                                                                  /* ::getAllocatableSize */
E(fn_8016A5C0) { GM_RET(0); }                                                                  /* ::adjust */
E(fn_8016A5D0) { GM_RET(gm_u32(DUMMY_HEAP)); }                                                 /* ::getInstance */
/* mAllocator_c */
E(__ct__12mAllocator_cFv) { GM_RET(alloc_ctor(GM_PASS, A(0))); }
E(__dt__12mAllocator_cFv) { GM_RET(plain_dtor(GM_PASS, 0x8016A630u, F_EGG_ALLOCATOR_DT, A(0), (int32_t)A(1))); }   /* FNADDR */
E(setup__12mAllocator_cFPvi) { GM_RET(alloc_attach(GM_PASS, A(0), A(1), A(2))); }             /* ::attach */
E(fn_8016A6E0) { GM_RET(GM_CALLR(ctx->lr, F_EGG_ALLOC, 2, A(0), A(1))); }                                 /* ::alloc */
E(fn_8016A6F0) { GM_RET(GM_CALLR(ctx->lr, F_EGG_FREE, 2, A(0), A(1))); }                                  /* ::free */
E(fn_8016A700) {                                                                               /* ::init(heap) */
    GM_LR_KEEP; FN(0x8016A700);
    gptr p = GM_CALLR(0x8016A71Cu, F_NEW, 3, 56, A(0), 4);
    if (p) p = NCALL(0x8016A728u, dummy_ctor(GM_PASS, p));
    GM_RET(p);
}
/* mHeapAllocator_c */
E(fn_8016A740) {                                                                               /* ::mHeapAllocator_c */
    GM_LR_KEEP; FN(0x8016A740); GM_NV_KEEP;
    gptr self = A(0);
    NV_R(31, self);
    NCALL(0x8016A758u, alloc_ctor(GM_PASS, self));
    gm_set_u32(self + 16, VT_HEAP_ALLOCATOR);
    GM_RET(self);
}
E(fn_8016A780) {                                                                               /* ::~mHeapAllocator_c */
    GM_LR_KEEP; FN(0x8016A780); GM_NV_KEEP;
    gptr self = A(0); int32_t flags = (int32_t)A(1);
    NV_R(31, flags); NV_R(30, self);
    if (self) {
        gm_set_u32(self + 16, VT_HEAP_ALLOCATOR);
        NCALL(0x8016A7B4u, destroy_heap(GM_PASS, self));
        NCALL(0x8016A7C0u, plain_dtor(GM_PASS, 0x8016A630u, F_EGG_ALLOCATOR_DT, self, 0));
        if (flags > 0) GM_CALLR(0x8016A7D0u, F_DELETE, 1, self);
    }
    GM_RET(self);
}
E(fn_8016A7F0) { GM_LR_KEEP; GM_RET(ha_create(GM_PASS, A(0), A(1), A(2), A(3), A(4), A(5))); } /* ::createFrmHeap */
E(fn_8016A880) { destroy_heap(GM_PASS, A(0)); }                                                /* ::destroyHeap */
E(fn_8016A8E0) {                                                                               /* ::adjustFrmHeap */
    FN(0x8016A8E0); GM_NV_KEEP;
    gptr self = A(0);
    NV_R(31, self);
    gptr h = gm_u32(self + 20);
    if (h == gm_u32(DUMMY_HEAP)) { NV_R(31, h); GM_RET(0); return; }
    GM_RET(adjust_cast(GM_PASS, h, 0x8016A928u));
}
E(fn_8016A960) {                                                                               /* ::createFrmHeapToCurrent */
    GM_LR_KEEP; FN(0x8016A960); GM_NV_KEEP;
    gptr self = A(0);
    NV_R(31, self);
    if (!NCALL(0x8016A978u, ha_create(GM_PASS, self, A(1), A(2), A(3), A(4), A(5)))) { GM_RET(0); return; }
    GM_CALLR(0x8016A98Cu, F_SAVE_HEAP, 0);
    GM_CALLR(0x8016A994u, F_SET_HEAP, 1, gm_u32(self + 20));
    GM_RET(1);
}
E(fn_8016A9B0) {                                                                               /* ::adjustFrmHeapRestoreCurrent */
    FN(0x8016A9B0); GM_NV_KEEP;
    gptr self = A(0);
    NV_R(31, self);
    GM_CALLR(0x8016A9C8u, F_RESTORE_HEAP, 0);
    GM_RET(adjust_cast(GM_PASS, gm_u32(self + 20), 0x8016A9E8u));
}
E(fn_8016AA20) {                                                                               /* (the mAng3_c units) */
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++) gm_set_u16(ANG3_UNITS + 8 * i + 2 * j, (i && j == i - 1) ? 1 : 0);
}
