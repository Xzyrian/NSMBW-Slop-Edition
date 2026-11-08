/* gm_s_state.c - sLib's state machines: sStateID_c, sStateMethod_c and sStateMethodUsr_FI_c
 * (s_StateID.cpp, s_StateMethod.cpp, s_StateMethodUsr_FI.cpp). Every actor with states (the
 * player, enemies, the world map ...) runs one of these each frame. Track B (gm.h,
 * docs/DECOMP.md), instance 1. (The per-class template parts - sFStateMgr_c<T>, sFState_c<T>,
 * sFStateFct_c<T>, sFStateID_c<T> - have one copy per class in the binary and stay recompiled.)
 *
 * Decompiled against NSMBW-Decomp (source/dol/sLib/) and checked against the recompiled code.
 *
 * sStateID_c (0xC): +0 vtable, +4 name, +8 number (0: the null state).
 *   vtable: +0xC isNull, +0x10 isEqual, +0x14 operator==, +0x18 operator!=, +0x1C isSameName,
 *           +0x20 name, +0x24 number.
 * sStateMethod_c (0x24): +0 vtable, +4 the checker, +8 the factory, +0xC init/finalize lock,
 *   +0xD execute lock, +0xE valid, +0xF state changed, +0x10 refresh, +0x14 the new state ID,
 *   +0x18 the old one, +0x1C the current one, +0x20 the state holder.
 *   vtable: +0xC initializeStateMethod, +0x10 execute.., +0x14 finalize.., +0x18 change..,
 *           +0x24 getNewStateID, +0x30 initializeStateLocalMethod, +0x34 execute.., +0x38
 *           finalize.., +0x3C changeStateLocalMethod.
 * The factory: +0xC build(id), +0x10 dispose(&holder). The holder: +0xC initialize,
 *   +0x10 execute, +0x14 finalize. */
#include "gm.h"
#include "gm_nv.h"

#define SDA 0x8042F680u
#define ID_COUNTER   (SDA - 0x5320)      /* sStateID_c::sm_numberMemo */
#define VT_STATEID   0x80328A18u
#define VT_METHOD    0x80328A40u
#define VT_METHOD_FI 0x80328A80u
#define NULL_ID      0x80377A04u         /* sStateID::null */
#define F_OP_DELETE  0x802B9280u         /* operator delete */
/* the 8-player module replaces three of these (its versions run when it is on): isSameName
   compares the names after the last ':', number gives a state made with -1 the next number,
   changeStateMethod can log the changes */
#define MOD_IS_SAME_NAME 0x8183832Cu
#define MOD_CHANGE_STATE 0x81838420u
#define MOD_GET_ID       0x818383A8u
extern int g_mod_on;

#define V(obj, off, n, ...) GM_VCALL((obj), (off), (n), (obj), ##__VA_ARGS__)
/* the same with the PowerPC return address (GM_CALLR, gm_nv.h) */
#define VR(ra, obj, off, n, ...) GM_CALLR((ra), gm_u32(gm_u32(obj) + (off)), (n), (obj), ##__VA_ARGS__)

/* ---- sStateID_c ---- */
gptr sStateID_ctor(gptr self, gptr name) {
    gm_set_ptr(self, VT_STATEID);
    gm_set_ptr(self + 4, name);
    uint32_t n = 0;
    if (name) { n = gm_u32(ID_COUNTER) + 1; gm_set_u32(ID_COUNTER, n); }
    gm_set_u32(self + 8, n);
    return self;
}
static gptr dtor_plain(GM_CTX, gptr self, int32_t flags, uint32_t addr) { GM_FN(addr); GM_NV_KEEP;      /* (the two classes' destructors: nothing to undo) */
    NV_R(31, self);
    if (self && flags > 0) GM_CALLR(addr + 0x28, F_OP_DELETE, 1, self);
    return self;
}
int sStateID_isEqual(GM_CTX, gptr self, gptr other) { GM_FN(0x8015F850); GM_NV_KEEP;
    NV_R(30, self);
    uint32_t a = VR(0x8015F87Cu, other, 0x24, 1);
    NV_R(31, a);
    uint32_t b = VR(0x8015F894u, self, 0x24, 1);
    return a == b;
}

/* ---- sStateMethod_c ---- */
gptr sStateMethod_ctor(gptr self, gptr chk, gptr fct, gptr initial) {
    gm_set_ptr(self + 4, chk);
    gm_set_ptr(self, VT_METHOD);
    gm_set_ptr(self + 8, fct);
    for (int i = 0xC; i <= 0x10; i++) gm_set_u8(self + i, 0);
    gm_set_ptr(self + 0x14, initial);
    gm_set_ptr(self + 0x18, NULL_ID);
    gm_set_ptr(self + 0x1C, initial);
    gm_set_ptr(self + 0x20, 0);
    return self;
}
void sStateMethod_initialize(GM_CTX, gptr self) { GM_FN(0x8015FA30); GM_NV_KEEP;
    NV_R(30, self);
    gptr id = gm_ptr(self + 0x14);
    if (VR(0x8015FA5Cu, id, 0xC, 1) || gm_u8(self + 0xC) || gm_u8(self + 0xE)) return;
    NV_R(31, 1);
    gm_set_u8(self + 0xC, 1);
    gm_set_ptr(self + 0x1C, gm_ptr(self + 0x14));
    gm_set_u8(self + 0xE, VR(0x8015FAA0u, self, 0x30, 1) ? 1 : 0);              /* initializeStateLocalMethod */
    gm_set_u8(self + 0xC, 0);
}
void sStateMethod_execute(GM_CTX, gptr self) { GM_FN(0x8015FAE0); GM_NV_KEEP;
    NV_R(29, self);
    if (gm_u8(self + 0xD)) return;
    NV_R(30, 1); NV_R(31, 0);
    for (;;) {
        gm_set_u8(self + 0x10, 0);
        gptr id = gm_ptr(self + 0x14);
        if (!VR(0x8015FB28u, id, 0xC, 1)) {
            gm_set_u8(self + 0xD, 1);
            VR(0x8015FB48u, self, 0x34, 1);                                       /* executeStateLocalMethod */
            gm_set_u8(self + 0xD, 0);
        }
        if (!gm_u8(self + 0x10) || !gm_u8(self + 0xF)) break;       /* (again if refreshed after a change) */
        GM_LOOP();
    }
}
void sStateMethod_finalize(GM_CTX, gptr self) { GM_FN(0x8015FB80); GM_NV_KEEP;
    NV_R(31, self);
    gptr id = gm_ptr(self + 0x14);
    if (VR(0x8015FBA8u, id, 0xC, 1) || !gm_u8(self + 0xE) || gm_u8(self + 0xC)) return;
    gm_set_u8(self + 0xC, 1);
    gm_set_ptr(self + 0x18, gm_ptr(self + 0x1C));
    VR(0x8015FBECu, self, 0x38, 1);                                               /* finalizeStateLocalMethod */
    gm_set_u8(self + 0xE, 0);
    gm_set_u8(self + 0xC, 0);
}
void sStateMethod_change(GM_CTX, gptr self, gptr id) { GM_FN(0x8015FC10); GM_NV_KEEP;
    NV_R(31, id); NV_R(30, self);
    if (VR(0x8015FC40u, id, 0xC, 1)) return;
    gm_set_ptr(self + 0x14, id);
    VR(0x8015FC64u, self, 0x3C, 2, id);                                           /* changeStateLocalMethod */
    gm_set_u8(self + 0xF, 1);
}

/* ---- sStateMethodUsr_FI_c: the state holder comes from the factory ---- */
gptr sStateMethodUsrFI_ctor(gptr self, gptr chk, gptr fct, gptr initial) {
    sStateMethod_ctor(self, chk, fct, initial);
    gm_set_ptr(self, VT_METHOD_FI);
    return self;
}
int sStateMethodUsrFI_initializeLocal(GM_CTX, gptr self) { GM_FN(0x8015FCD0); GM_NV_KEEP;
    NV_R(31, self);
    gptr id = VR(0x8015FCF4u, self, 0x24, 1);                       /* getNewStateID */
    gptr fct = gm_ptr(self + 8);
    gptr st = VR(0x8015FD0Cu, fct, 0xC, 2, id);                     /* build */
    gm_set_ptr(self + 0x20, st);
    VR(0x8015FD20u, st, 0xC, 1);                                                  /* initialize */
    return 1;
}
void sStateMethodUsrFI_executeLocal(GM_CTX, gptr self) { GM_FN(0x8015FD40); GM_NV_KEEP;
    NV_R(31, self);
    VR(0x8015FD64u, self, 0xC, 1);                                  /* initializeStateMethod (if not yet) */
    gptr st = gm_ptr(self + 0x20);
    VR(0x8015FD78u, st, 0x10, 1);                                                 /* execute */
}
void sStateMethodUsrFI_finalizeLocal(GM_CTX, gptr self) { GM_FN(0x8015FD90); GM_NV_KEEP;
    NV_R(31, self);
    gptr st = gm_ptr(self + 0x20);
    VR(0x8015FDB8u, st, 0x14, 1);                                   /* finalize */
    gptr fct = gm_ptr(self + 8);
    VR(0x8015FDD0u, fct, 0x10, 2, self + 0x20);                                   /* dispose */
}
void sStateMethodUsrFI_changeLocal(GM_CTX, gptr self) { GM_FN(0x8015FDF0); GM_NV_KEEP;
    NV_R(31, self);
    VR(0x8015FE14u, self, 0x14, 1);                                 /* finalizeStateMethod */
    VR(0x8015FE28u, self, 0xC, 1);                                                /* initializeStateMethod */
}

/* ---- register-exact entries (part 48: RT_GM_VERIFY_REGS=1) ---- */
#define R(n) ctx->r[n]
static uint32_t stateid_ct_r(GM_CTX) {                 /* sStateID_c(name) (r3 self, r4 name) */
    R(5) = VT_STATEID;
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    gm_set_ptr(R(3), R(5)); gm_set_ptr(R(3) + 4, R(4));
    if (R(4)) { R(4) = gm_u32(ID_COUNTER); R(0) = R(4) + 1; gm_set_u32(ID_COUNTER, R(0)); }
    else R(0) = 0;
    gm_set_u32(R(3) + 8, R(0));
    return R(3);
}
static uint32_t stateid_isnull_r(GM_CTX) {             /* isNull() */
    R(0) = gm_u32(R(3) + 8);
    R(0) = cntlzw(R(0));
    return R(3) = R(0) >> 5;
}
static uint32_t method_ct_r(GM_CTX) {                  /* sStateMethod_c(chk, factory, initial) */
    R(8) = VT_METHOD; R(7) = 0x80370000u + 31236u; R(0) = 0;
    gm_set_ptr(R(3) + 4, R(4)); gm_set_ptr(R(3), R(8)); gm_set_ptr(R(3) + 8, R(5));
    for (int i = 0xC; i <= 0x10; i++) gm_set_u8(R(3) + i, 0);
    gm_set_ptr(R(3) + 20, R(6)); gm_set_ptr(R(3) + 24, R(7)); gm_set_ptr(R(3) + 28, R(6)); gm_set_u32(R(3) + 32, 0);
    return R(3);
}
static uint32_t method_fi_ct_r(GM_CTX) {               /* sStateMethodUsr_FI_c(...) */
    GM_FN(0x8015FC90); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, R(3));
    ctx->lr = 0x8015FCA8u; method_ct_r(GM_PASS);
    R(4) = VT_METHOD_FI; R(3) = R(31);
    gm_set_ptr(R(31), R(4));
    R(0) = lr;
    return R(3);
}

/* ================================================================== hle entry points
 * The state methods call virtual functions (the states themselves): checked by the A/B replay. */
#define A(i) GM_ARG(i)
GM_HLE_INT(__ct__12dStateBase_cFPCc, A(0), 0xC, ID_COUNTER, 4) { GM_RET(stateid_ct_r(GM_PASS)); }        /* sStateID_c::sStateID_c */
GM_HLE(__dt__12dStateBase_cFv) { GM_RET(dtor_plain(GM_PASS, A(0), (int32_t)A(1), 0x8015F800u)); }                         /* sStateID_c::~sStateID_c */
GM_HLE_INT(isInvalid__12dStateBase_cFv, A(0), 0xC) { stateid_isnull_r(GM_PASS); }                        /* sStateID_c::isNull */
GM_HLE(isEqualNotUsedForSomeReason__12dStateBase_cFP12dStateBase_c) { GM_RET(sStateID_isEqual(GM_PASS, A(0), A(1))); }   /* sStateID_c::isEqual */
GM_HLE(isEqual__12dStateBase_cFP12dStateBase_c) { GM_RET(VR(ctx->lr, A(0), 0x10, 2, A(1))); }                          /* sStateID_c::operator== */
GM_HLE(isNotEqual__12dStateBase_cFP12dStateBase_c) { GM_FN(0x8015F8D0); GM_RET(VR(0x8015F8ECu, A(0), 0x10, 2, A(1)) == 0); }                  /* sStateID_c::operator!= */
GM_HLE(fn_8015F910) { GM_RET(g_mod_on ? GM_CALLR(ctx->lr, MOD_IS_SAME_NAME, 2, A(0), A(1)) : 0); }                                                            /* sStateID_c::isSameName */
GM_HLE_INT(getName__12dStateBase_cFv, A(0), 0xC) { GM_RET(gm_u32(A(0) + 4)); }                               /* sStateID_c::name */
GM_HLE(getID__12dStateBase_cFv) {                                                                            /* sStateID_c::number */
    if (g_mod_on) { GM_RET(GM_CALLR(ctx->lr, MOD_GET_ID, 1, A(0))); return; }   /* (the module's version: numbers its own states when first asked; a tail call) */
    GM_RET(gm_u32(A(0) + 8));
}                                 /* sStateID_c::number */
GM_HLE_INT(fn_8015F9A0, A(0), 0x24) { GM_RET(method_ct_r(GM_PASS)); }                   /* sStateMethod_c::sStateMethod_c */
GM_HLE(__dt__15dStateMgrBase_cFv) { GM_RET(dtor_plain(GM_PASS, A(0), (int32_t)A(1), 0x8015F9F0u)); }                      /* sStateMethod_c::~sStateMethod_c */
GM_HLE(fn_8015FA30) { sStateMethod_initialize(GM_PASS, A(0)); }                                              /* sStateMethod_c::initializeStateMethod */
GM_HLE(fn_8015FAE0) { sStateMethod_execute(GM_PASS, A(0)); }                                                 /* sStateMethod_c::executeStateMethod */
GM_HLE(fn_8015FB80) { sStateMethod_finalize(GM_PASS, A(0)); }                                                /* sStateMethod_c::finalizeStateMethod */
GM_HLE(fn_8015FC10) { if (g_mod_on) GM_CALLR(ctx->lr, MOD_CHANGE_STATE, 2, A(0), A(1)); else sStateMethod_change(GM_PASS, A(0), A(1)); }                                            /* sStateMethod_c::changeStateMethod */
GM_HLE_INT(__ct__11dStateMgr_cFP17dStatePointless_cP20dStateExecutorBase_cP12dStateBase_c, A(0), 0x24) {     /* sStateMethodUsr_FI_c::sStateMethodUsr_FI_c */
    GM_RET(method_fi_ct_r(GM_PASS));
}
GM_HLE(fn_8015FCD0) { GM_RET(sStateMethodUsrFI_initializeLocal(GM_PASS, A(0))); }                            /* sStateMethodUsr_FI_c::initializeStateLocalMethod */
GM_HLE(fn_8015FD40) { sStateMethodUsrFI_executeLocal(GM_PASS, A(0)); }                                       /* ::executeStateLocalMethod */
GM_HLE(fn_8015FD90) { sStateMethodUsrFI_finalizeLocal(GM_PASS, A(0)); }                                      /* ::finalizeStateLocalMethod */
GM_HLE(fn_8015FDF0) { sStateMethodUsrFI_changeLocal(GM_PASS, A(0)); }                                        /* ::changeStateLocalMethod */
