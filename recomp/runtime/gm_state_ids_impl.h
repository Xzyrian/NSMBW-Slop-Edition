/* gm_state_ids_impl.h - the native sFStateVirtualID_c<T> / sFStateID_c<T> functions for
 * gm_state_ids.c (generated). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * sFStateID_c<T> (after sStateID_c's 0xC bytes): +0x0C initialize, +0x18 execute, +0x24 finalize
 * - each a pointer to member function {this adjust, vtable offset (< 0: none), function or
 * vtable position}; sFStateVirtualID_c<T> adds +0x30 the base state (the state it overrides).
 * All copies make a 16-byte frame and save LR there (+20), some r31 (+12) and r30 (+8); the
 * natives do the same.
 *
 * Register-exact since part 56 (R(n): the PowerPC registers as the variables, the calls with
 * their real return addresses - every copy is the same code at its own address `a`, so a call's
 * return address is a + its offset - and the callees' volatile registers left as they leave
 * them). Before, the calls went through GM_CALL (LR = 0, r0-r12 put back): the state calls
 * (execute every frame for every actor with states) then left registers and dead stack words
 * different from the PowerPC code's, which nw4r's CalcWorld later copied into model data (the
 * no-input A/B's blips). */
#include "gm.h"
#include "gm_nv.h"

#define ST_STATE_GETID 0x8015F930u        /* sStateID_c::number */
#define ST_STATE_DT    0x8015F800u        /* sStateID_c::~sStateID_c */
#define ST_STRRCHR     0x802E1C40u
#define ST_STRCMP      0x802E1AB4u
#define ST_OP_DELETE   0x802B9280u
#define ST_PTMF_SCALL  0x802DCBFCu
#define SR(n) ctx->r[n]

/* the frame: 16 bytes, LR at +20, then r31 / r30 if saved (GM_NV_KEEP puts them back) */
static inline void st_frame(GM_CTX, gptr sp, int regs) {
    gm_set_u32(sp + 20, ctx->lr);
    if (regs > 0) gm_set_u32(sp + 12, ctx->r[31]);
    if (regs > 1) gm_set_u32(sp + 8, ctx->r[30]);
}
#define ST_FRAME(regs) GM_FRAME(16); GM_NV_KEEP; GM_LR_KEEP; uint32_t st_lr_ = ctx->lr; st_frame(GM_PASS, gm_frame_sp, (regs))
static inline int st_cmp(GM_CTX, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
/* r3's vtable +12 (isNull) - r12 / CTR as the PowerPC code leaves them */
static inline void st_isnull(GM_CTX, uint32_t ra) {
    SR(12) = gm_u32(SR(3)); SR(12) = gm_u32(SR(12) + 12); ctx->ctr = SR(12);
    GM_CALLV(ra, SR(12), 0);
}

/* initializeState / executeState / finalizeState (id, obj): __ptmf_scall of the member at off */
static void st_call(GM_CTX, uint32_t off, uint32_t a) {
    ST_FRAME(0);
    SR(0) = st_lr_;
    SR(5) = SR(3); SR(3) = SR(4);
    SR(12) = SR(5) + off;
    GM_CALLV(a + 0x1C, ST_PTMF_SCALL, 0);
    SR(0) = st_lr_;
}
/* the destructors (self, flags); the second kind tests self twice (the PowerPC code does) */
static gptr st_dtor(GM_CTX, uint32_t a, int kind2) {
    ST_FRAME(2);
    int c = st_cmp(GM_PASS, (int32_t)SR(3), 0);
    SR(31) = SR(4); SR(30) = SR(3);
    if (c != 0) {
        SR(4) = 0;
        GM_CALLV(a + (kind2 ? 0x30 : 0x2C), ST_STATE_DT, 0);
        if (st_cmp(GM_PASS, (int32_t)SR(31), 0) > 0) { SR(3) = SR(30); GM_CALLV(a + (kind2 ? 0x40 : 0x3C), ST_OP_DELETE, 0); }
    }
    SR(3) = SR(30);
    SR(0) = st_lr_;
    return SR(3);
}
/* the walk of getRootState / number: the base states down to the first whose base is null -
   unrolled 5 deep, then root_fn (this class's getRootState) on the next. r31 = the state;
   returns with r3 = the root */
static void st_walk(GM_CTX, uint32_t a, uint32_t root_fn) {
    SR(31) = SR(3);
    SR(3) = gm_u32(SR(3) + 48);
    st_isnull(GM_PASS, a + 0x28);
    if (st_cmp(GM_PASS, (int32_t)SR(3), 0) != 0) { SR(3) = SR(31); return; }
    for (int i = 1; i < 5; i++) {
        SR(31) = gm_u32(SR(31) + 48);
        SR(3) = gm_u32(SR(31) + 48);
        st_isnull(GM_PASS, a + 0x28 + 0x20 * (uint32_t)i);
        if (st_cmp(GM_PASS, (int32_t)SR(3), 0) != 0) { SR(3) = SR(31); return; }
    }
    SR(3) = gm_u32(SR(31) + 48);
    GM_CALLV(a + 0xBC, root_fn, 0);
    SR(31) = SR(3);
}
static gptr st_root(GM_CTX, uint32_t a, uint32_t root_fn) {
    ST_FRAME(1);
    st_walk(GM_PASS, a, root_fn);
    SR(3) = SR(31);
    SR(0) = st_lr_;
    return SR(3);
}
static uint32_t st_number(GM_CTX, uint32_t a, uint32_t root_fn) {
    ST_FRAME(1);
    st_walk(GM_PASS, a, root_fn);
    SR(3) = SR(31);
    GM_CALLV(a + 0xC8, ST_STATE_GETID, 0);
    SR(0) = st_lr_;
    return SR(3);
}
/* isSameName(name): compared after the last ':' of both */
static uint32_t st_same_name(GM_CTX, uint32_t a) {
    ST_FRAME(2);
    SR(31) = SR(4); SR(4) = 58; SR(30) = SR(3); SR(3) = SR(31);
    GM_CALLV(a + 0x28, ST_STRRCHR, 0);
    if (st_cmp(GM_PASS, (int32_t)SR(3), 0) != 0) SR(31) = SR(3) + 1;
    SR(12) = gm_u32(SR(30)); SR(3) = SR(30); SR(12) = gm_u32(SR(12) + 32); ctx->ctr = SR(12);
    GM_CALLV(a + 0x48, SR(12), 0);                                          /* name() */
    SR(4) = 58;
    GM_CALLV(a + 0x50, ST_STRRCHR, 0);
    SR(4) = SR(31); SR(3) = SR(3) + 1;
    GM_CALLV(a + 0x5C, ST_STRCMP, 0);
    SR(3) = st_cmp(GM_PASS, (int32_t)SR(3), 0) == 0 ? 1 : 0;
    SR(0) = st_lr_;
    return SR(3);
}
