/* gm_d_message.c - dMessage_c, the game's message archive (Message/Message.arc's wii_mj2d.bmg,
 * localised): ctor / dtor, create / buildMsgRes, getMsg / getMesRes, numToString /
 * numToFullWidth / changetoFullSize; and MsgRes_c (an EGG::MsgRes): ctor / dtor, getScale /
 * getFont. Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_message.cpp, d_msg_res.cpp) and checked
 * against the recompiled USA rev 2 code (0x800CDA70-0x800CDE60, 0x800CE700-0x800CE7F0).
 * Register-exact (R(n)); numToString keeps the PowerPC code's power-of-ten loop (8 at a time
 * by 100000000, then by 10, with its CR1 compare and overflow guard) and the loops' back-edge
 * polls.
 *
 * l_dMessage_obj is 0x80359C9C (+20 the BMG data, +24 the MsgRes_c). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

#define MSG_OBJ          (0x80360000u - 25444u)
#define F_LOADER_CT      0x8008F140u    /* dDvd::loader_c::loader_c */
#define F_LOADER_DT      0x8008F170u
#define F_LOADER_REQ     0x8008F1B0u    /* dDvd::loader_c::request(path, dir, heap) */
#define F_AREA_LANG      0x800B4650u    /* dGameCom::AreaLanguageFolder */
#define F_ARC_MOUNT      0x802B75B0u    /* EGG::Archive::mount(buf, heap, align) */
#define F_ARC_GET_FILE   0x802B76C0u
#define F_NEW_HEAP       0x802B9240u    /* operator new(size, heap, align) */
#define F_OP_DELETE      0x802B9280u
#define F_EGG_MSG_CT     0x802D7680u    /* EGG::MsgRes::MsgRes(data) */
#define F_EGG_MSG_DT     0x802D77E0u
#define F_EGG_GET_MSG    0x802D7860u    /* EGG::MsgRes::getMsg */
#define F_EGG_MSG_ENTRY  0x802D79A0u    /* EGG::MsgRes::getMsgEntry */
#define F_WCSLEN         0x802E441Cu
#define F_BUILD_MSGRES   0x800CDBF0u
#define F_NUM_TO_STRING  0x800CDC70u
#define F_TO_FULL_SIZE   0x800CDDF0u
#define F_MSGRES_CT      0x800CE700u

/* ================================================================== dMessage_c */
static void ms_ctor(GM_CTX) {
    GM_FN(0x800CDA70); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x800CDA88u, F_LOADER_CT, 0);
    R(0) = 0;
    gm_set_u32(R(31) + 20, 0);
    R(3) = R(31);
    gm_set_u32(R(31) + 24, 0);
    R(0) = lr;
}
static void ms_dtor(GM_CTX) {
    GM_FN(0x800CDAB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(3) = gm_u32(R(3) + 24);
        if (cmps(ctx, (int32_t)R(3), 0) != 0) {
            R(12) = gm_u32(R(3) + 28); R(4) = 1;
            R(12) = gm_u32(R(12) + 8); ctx->ctr = R(12);
            GM_CALLV(0x800CDAF4u, R(12), 0);                                 /* delete mpMsgRes */
        }
        R(3) = R(30); R(4) = (uint32_t)-1;
        GM_CALLV(0x800CDB00u, F_LOADER_DT, 0);
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x800CDB10u, F_OP_DELETE, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
/* create(heap): once - the localised archive, mounted, its BMG, the MsgRes_c */
static void ms_create(GM_CTX) {
    GM_FN(0x800CDB30); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    R(31) = MSG_OBJ;
    R(30) = R(3);
    R(0) = gm_u32(R(31) + 20);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        R(3) = 0x80310000u + 31096;                                          /* "Message/Message.arc" */
        R(4) = f + 16;
        GM_CALLV(0x800CDB6Cu, F_AREA_LANG, 0);
        R(3) = R(31); R(6) = R(30); R(4) = f + 16; R(5) = 0;
        GM_CALLV(0x800CDB80u, F_LOADER_REQ, 0);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
        R(4) = R(30); R(5) = 4;
        GM_CALLV(0x800CDB9Cu, F_ARC_MOUNT, 0);
        R(0) = 0;
        R(4) = 0x80310000u;
        gm_set_u32(f + 8, 0);
        R(4) = R(4) + 31116;                                                 /* "wii_mj2d.bmg" */
        R(5) = f + 8;
        gm_set_u32(f + 12, 0);
        GM_CALLV(0x800CDBB8u, F_ARC_GET_FILE, 0);
        gm_set_u32(R(31) + 20, R(3));
        R(3) = R(31); R(4) = R(30);
        GM_CALLV(0x800CDBC8u, F_BUILD_MSGRES, 0);
    }
    R(3) = 1;
out:
    R(0) = lr;
}
/* buildMsgRes(heap): new (heap, 4) MsgRes_c(data) */
static void ms_build(GM_CTX) {
    GM_FN(0x800CDBF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(5) = 4;
    R(31) = R(3);
    R(3) = 32;
    GM_CALLV(0x800CDC10u, F_NEW_HEAP, 0);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {
        R(4) = gm_u32(R(31) + 20); R(5) = 0;
        GM_CALLV(0x800CDC24u, F_MSGRES_CT, 0);
    }
    gm_set_u32(R(31) + 24, R(3));
    R(0) = lr;
}
/* numToString(num, dst, limit, digits, suppressLeadingZero): digit by digit from the top */
static void ms_num_to_string(GM_CTX) {
    GM_FN(0x800CDC70); GM_NV_KEEP;
    R(0) = R(7) - 1;
    R(0) = cntlzw(R(0));
    R(11) = R(4);
    R(31) = R(6) - 1;                                                        /* digitPos */
    R(12) = 0;                                                               /* count */
    R(8) = 0x05F60000u;
    R(30) = R(0) >> 5;                                                       /* skipOverZeros */
    R(9) = 0x80000000u;
    R(6) = 32;
    goto test;
body:
    cr_cmp_s(ctx, 1, (int32_t)R(31), 0);
    R(29) = 1; R(28) = 0;                                                    /* pow10, exp */
    if (CR_BIT(ctx, 5)) {
        int c = cmps(ctx, (int32_t)R(31), 8);
        R(10) = R(31) - 8;
        if (c > 0) {
            R(7) = 0;
            if (!CR_BIT(ctx, 4)) {
                R(0) = R(9) - 2;
                if (cmps(ctx, (int32_t)R(31), (int32_t)R(0)) <= 0) R(7) = 1;
            }
            if (cmps(ctx, (int32_t)R(7), 0) != 0) {
                R(0) = R(10) + 7;
                R(7) = R(8) - 7936;                                          /* 100000000 */
                R(0) = R(0) >> 3;
                ctx->ctr = R(0);
                if (cmps(ctx, (int32_t)R(10), 0) > 0)
                    for (;;) {
                        R(29) = (uint32_t)((int32_t)R(29) * (int32_t)R(7));
                        R(28) = R(28) + 8;
                        if (--ctx->ctr == 0) break;
                        GM_LOOP();
                    }
            }
        }
        R(0) = R(31) - R(28);
        ctx->ctr = R(0);
        if (cmps(ctx, (int32_t)R(28), (int32_t)R(31)) < 0)
            for (;;) {
                R(29) = (uint32_t)((int32_t)R(29) * 10);
                R(28) = R(28) + 1;
                if (--ctx->ctr == 0) break;
                GM_LOOP();
            }
    }
    R(7) = (uint32_t)((int32_t)R(29) * 10);
    R(0) = divw((int32_t)R(3), (int32_t)R(7));
    R(0) = (uint32_t)((int32_t)R(0) * (int32_t)R(7));
    R(0) = R(3) - R(0);
    R(7) = divw((int32_t)R(0), (int32_t)R(29));                              /* the digit */
    CR0(ctx, R(7));
    if (CR_BIT(ctx, 2) && cmps(ctx, (int32_t)R(30), 0) != 0 && cmps(ctx, (int32_t)R(31), 0) != 0)
        gm_set_u16(R(11), (uint16_t)R(6));                                   /* ' ' */
    else {
        R(0) = R(7) + 48;
        gm_set_u16(R(11), (uint16_t)R(0));
        R(30) = 0;
    }
    R(12) = R(12) + 1;
    R(31) = R(31) - 1;
    {
        int c = cmpu(ctx, R(5), R(12));
        R(11) = R(11) + 2;
        if (c <= 0) goto done;
    }
test:
    if (cmps(ctx, (int32_t)R(31), 0) >= 0) { GM_LOOP(); goto body; }
done:
    R(0) = R(12) << 1;
    R(3) = 0;
    gm_set_u16(R(4) + R(0), 0);
}
/* numToFullWidth(...): numToString, then changetoFullSize */
static void ms_num_to_full(GM_CTX) {
    GM_FN(0x800CDDB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(4);
    GM_CALLV(0x800CDDC8u, F_NUM_TO_STRING, 0);
    R(3) = R(31);
    GM_CALLV(0x800CDDD0u, F_TO_FULL_SIZE, 0);
    R(0) = lr;
}
/* changetoFullSize(str): ' ' -> U+3000, '!'..'~' -> the full-width forms */
static void ms_to_full_size(GM_CTX) {
    GM_FN(0x800CDDF0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x800CDE08u, F_WCSLEN, 0);
    R(4) = 12288;
    ctx->ctr = R(3);
    if (cmpu(ctx, R(3), 0) > 0)
        for (;;) {
            R(3) = gm_u16(R(31));
            if (cmpu(ctx, R(3), 0x20) == 0) gm_set_u16(R(31), (uint16_t)R(4));
            else if (cmpu(ctx, R(3), 0x21) >= 0 && cmpu(ctx, R(3), 0x7E) <= 0) {
                R(3) = R(3) + 0x10000u;
                R(0) = R(3) - 288;
                gm_set_u16(R(31), (uint16_t)R(0));
            }
            R(31) = R(31) + 2;
            if (--ctx->ctr == 0) break;
            GM_LOOP();
        }
    R(0) = lr;
}

/* ================================================================== MsgRes_c */
static void mr_ctor(GM_CTX) {
    GM_FN(0x800CE700); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x800CE718u, F_EGG_MSG_CT, 0);
    R(4) = 0x80310000u;
    R(3) = R(31);
    R(4) = R(4) + 31136;
    gm_set_u32(R(31) + 28, R(4));                                            /* the vtable */
    R(0) = lr;
}
static void mr_dtor(GM_CTX) {
    GM_FN(0x800CE740); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(4) = 0;
        GM_CALLV(0x800CE76Cu, F_EGG_MSG_DT, 0);
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x800CE77Cu, F_OP_DELETE, 0); }
    }
    R(3) = R(30);
    R(0) = lr;
}
/* getScale / getFont(group, id): the message entry's +4 (u16) / +6 (u8) */
static void mr_entry_field(GM_CTX, uint32_t a, int off, int sz) {
    GM_FN(a); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(a + 0x10, F_EGG_MSG_ENTRY, 0);
    R(0) = lr;
    R(3) = sz == 2 ? gm_u16(R(3) + off) : gm_u8(R(3) + off);
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
/* (plain GM_HLE below: written but off - no test reaches it; not in hle_funcs.txt) */
#ifdef GM_MSG_VERIFY
#define E(name, len) GM_HLE_INT(name, A(0), len)
#elif defined(GM_MSG_COUNT)   /* (testing: log each native's first call - which ones the tests reach) */
#define E(name, len) static void body_##name(GM_CTX); \
    GM_HLE(name) { static int n_; if (!n_++) rt_log("gm", "first call: " #name); body_##name(GM_PASS); } \
    static void body_##name(GM_CTX)
#else
#define E(name, len) GM_HLE(name)
#endif
E(fn_800CDA70, 28) { ms_ctor(GM_PASS); }                                           /* dMessage_c::dMessage_c */
GM_HLE(fn_800CDAB0) { ms_dtor(GM_PASS); }                                           /* ::~dMessage_c */
E(create__10dMessage_cFPQ23EGG4Heap, 4) { ms_create(GM_PASS); }                    /* ::create */
E(fn_800CDBF0, 28) { ms_build(GM_PASS); }                                          /* ::buildMsgRes */
E(fn_800CDC40, 4)  { R(6) = MSG_OBJ; R(0) = R(3); R(5) = R(4);                     /* ::getMsg(group, id) */
                     R(3) = gm_u32(R(6) + 24); R(4) = R(0); GM_TAIL(F_EGG_GET_MSG, 0); }
E(getMesRes__10dMessage_cFv, 4) { R(3) = 0x80360000u; R(3) = R(3) - 25444; R(3) = gm_u32(R(3) + 24); }   /* ::getMesRes */
E(fn_800CDC70, 4)  { ms_num_to_string(GM_PASS); }                                  /* ::numToString */
E(fn_800CDDB0, 4)  { ms_num_to_full(GM_PASS); }                                    /* ::numToFullWidth */
E(fn_800CDDF0, 4)  { ms_to_full_size(GM_PASS); }                                   /* ::changetoFullSize */
E(fn_800CE700, 32) { mr_ctor(GM_PASS); }                                           /* MsgRes_c::MsgRes_c */
GM_HLE(fn_800CE740) { mr_dtor(GM_PASS); }                                           /* ::~MsgRes_c */
E(fn_800CE7A0, 4)  { mr_entry_field(GM_PASS, 0x800CE7A0u, 4, 2); }                 /* ::getScale   FNADDR */
E(fn_800CE7D0, 4)  { mr_entry_field(GM_PASS, 0x800CE7D0u, 6, 1); }                 /* ::getFont   FNADDR */
