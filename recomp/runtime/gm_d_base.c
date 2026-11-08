/* gm_d_base.c - dBase_c (the game's base: d_base.cpp) and dBaseActor_c (the base of every actor:
 * d_base_actor.cpp). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_base.cpp, d_base_actor.cpp) and checked
 * against the recompiled USA rev 2 code. The 8-player module replaces dBase_c's constructor and
 * destructor (they stay guest calls here: GM_CALL to their addresses reaches the module's code).
 * Floating-point code uses the recompiler's own primitives (ldfs / stfs / frsp: single-precision
 * operations done in double, then rounded), so results match bit for bit.
 *
 * dBaseActor_c (after fBase_c's 0x64 and dBase_c's two strings):
 *   +0x70 the actor list node (cLineNd_c + 0x78 owner)   +0x7C the matrix
 *   +0xAC position, +0xB8 last position, +0xC4 position delta, +0xD0 centre offset, +0xDC scale
 *   +0xE8 speed, +0xF4 max speed, +0x100 angle (3 x s16), +0x106 3D angle, +0x10C forward speed,
 *   +0x110 max forward speed, +0x114 Y acceleration, +0x118 max fall speed, +0x11C forward
 *   acceleration, +0x120 actor properties (from the profile), +0x124 visible. */
#include "gm.h"
#include "gm_nv.h"

/* gm_f_base.c / gm_f_list.c / gm_c_list.c / gm_f_manager.c */
int  cLineMg_addLastLineNode(gptr self, gptr node);
int  cLineMg_removeLineNode(gptr self, gptr node);
int  fLiMgBa_countNodeByProfName(GM_CTX, gptr self, uint32_t prof);
void fBase_postCreate(GM_CTX, gptr self, uint32_t state);
int32_t fBase_preDelete(GM_CTX, gptr self);
void fBase_postDelete(GM_CTX, gptr self, uint32_t state);
int32_t fBase_preExecute(gptr self);
int32_t fBase_preDraw(gptr self);
void fBase_opDelete(GM_CTX, gptr p);
gptr fBase_make(GM_CTX, uint32_t prof, gptr parent, uint32_t param, uint32_t group);
gptr fManager_searchBaseByProfName(GM_CTX, uint32_t prof, gptr parent);
gptr fManager_searchBaseByGroupType(GM_CTX, uint32_t group, gptr parent);

#define SDA 0x8042F680u
#define PROF_TBL      (SDA - 0x52C8)     /* fProfListMg_c::m_data_p */
#define LOAD_CB       (SDA - 0x52D8)     /* fBase_c::sLoadAsyncCallback, sUnloadCallback */
#define UNLOAD_CB     (SDA - 0x52D4)
#define DRAW_SEED     (SDA - 0x58F0)     /* (the random seed dBase_c::preDraw writes) */
#define ACTOR_MANAGE  (SDA - 0x58E0)     /* dBaseActor_c::m_actorManage (fLiMgBa_c) */
#define TMP_POS       (SDA - 0x58E8)     /* dBaseActor_c::m_tmpCtPosP, m_tmpCtAngleP */
#define TMP_ANGLE     (SDA - 0x58E4)
#define NOW_SCENE     (SDA - 0x6F4E)     /* dScene_c::m_nowScene (u16) */
#define KIND_STRING   0x8030F1B8u        /* "dBase_c" kind string (getKindString) */
#define VT_BASEACTOR  0x8030F228u
#define F_DBASE_CT    0x8006C420u        /* (the module's) */
#define F_DBASE_DT    0x8006C490u
#define F_RANDOM_SEED 0x800B2EC0u        /* dGameCom::getRandomSeed */
#define F_RESET_INST  0x80107F10u        /* dReset::Manage_c::GetInstance */
#define F_LOAD_ASYNC  0x8006C670u
#define F_UNLOAD      0x8006C680u
enum { GROUP_ACTOR = 2 };

#define A_POS    0xAC
#define A_LAST   0xB8
#define A_DELTA  0xC4
#define A_CENTER 0xD0
#define A_SCALE  0xDC
#define A_SPEED  0xE8
#define A_SMAX   0xF4
#define A_ANGLE  0x100
#define A_ANG3D  0x106
#define A_SPEEDF 0x10C
#define A_MAXSF  0x110
#define A_ACCY   0x114
#define A_MAXFALL 0x118
#define A_ACCF   0x11C
#define A_PROPS  0x120
#define A_VIS    0x124

#define LF(a)    ldfs(base, (a))             /* (float load / store / single rounding, as recompiled) */
#define SF(a, d) stfs(base, (a), (d))

/* ---- dBase_c ---- */
gptr dBase_searchBaseByProfName(GM_CTX, uint32_t prof, gptr parent) { GM_FN(0x8006C500); return fManager_searchBaseByProfName(GM_PASS, prof, parent ? parent : 0); }
int32_t dBase_preCreate(void) { return 1; }                                                  /* (fBase_c::preCreate: 1) != NOT_READY */
int32_t dBase_preDelete(GM_CTX, gptr self) { GM_FN(0x8006C580); return fBase_preDelete(GM_PASS, self) != 0; }
int32_t dBase_preExecute(GM_CTX, gptr self) { GM_FN(0x8006C5C0); GM_CALLR(0x8006C5E4u, gm_u32(gm_u32(self + 0x60) + 0x4C), 1, self); return fBase_preExecute(self); }   /* (getKindString) */
int32_t dBase_preDraw(GM_CTX, gptr self) { GM_FN(0x8006C610); gm_set_u32(DRAW_SEED, GM_CALLR(0x8006C628u, F_RANDOM_SEED, 0)); return fBase_preDraw(self); }
gptr dBase_createBase(GM_CTX, uint32_t prof, gptr parent, uint32_t param, uint32_t group) { return parent ? fBase_make(GM_PASS, prof, parent + 0x10, param, group) : 0; }

/* ---- dBaseActor_c ---- */
gptr dBaseActor_ctor(GM_CTX, gptr self) { GM_FN(0x8006C6D0);
    GM_CALLR(0x8006C6E8u, F_DBASE_CT, 1, self);
    gm_set_ptr(self + 0x60, VT_BASEACTOR);
    gm_set_ptr(self + 0x70, 0); gm_set_ptr(self + 0x74, 0); gm_set_ptr(self + 0x78, self);
    cLineMg_addLastLineNode(ACTOR_MANAGE, self + 0x70);
    gptr p = gm_ptr(TMP_POS);
    if (p) {
        for (int i = 0; i < 3; i++) SF(self + A_POS + 4 * i, LF(p + 4 * i));
        p = gm_ptr(TMP_POS);
        for (int i = 0; i < 3; i++) SF(self + A_LAST + 4 * i, LF(p + 4 * i));
    }
    gptr a = gm_ptr(TMP_ANGLE);
    if (a) {
        for (int i = 0; i < 3; i++) gm_set_u16(self + A_ANGLE + 2 * i, gm_u16(a + 2 * i));
        a = gm_ptr(TMP_ANGLE);
        for (int i = 0; i < 3; i++) gm_set_u16(self + A_ANG3D + 2 * i, gm_u16(a + 2 * i));
    }
    double zero = LF(ctx->r[2] - 0x7450), one = LF(ctx->r[2] - 0x744C);
    gm_set_u8(self + A_VIS, 1);
    for (int i = 0; i < 3; i++) SF(self + A_CENTER + 4 * i, zero);
    for (int i = 0; i < 3; i++) SF(self + A_SCALE + 4 * i, one);
    gptr prof = gm_ptr(gm_ptr(PROF_TBL) + 4u * gm_u16(self + 8));
    gm_set_u32(self + A_PROPS, gm_u32(prof + 8));
    return self;
}
gptr dBaseActor_dtor(GM_CTX, gptr self, int32_t flags) { GM_FN(0x8006C7F0);
    if (!self) return self;
    gm_set_ptr(self + 0x60, VT_BASEACTOR);
    cLineMg_removeLineNode(ACTOR_MANAGE, self + 0x70);
    GM_CALLR(0x8006C838u, F_DBASE_DT, 2, self, 0);
    if (flags > 0) fBase_opDelete(GM_PASS, self);
    return self;
}
int32_t dBaseActor_preExecute(GM_CTX, gptr self) { GM_FN(0x8006C8F0);
    if (!dBase_preExecute(GM_PASS, self)) return 0;
    gptr m = GM_CALLR(0x8006C914u, F_RESET_INST, 0);
    int32_t init = gm_s32(m + 0xC), proc = gm_s32(m + 8);
    if (init == 1 || proc == 1) return 0;                           /* (a soft reset ...) */
    if (init == 5 || proc == 5) return 0;                           /* (... or waiting for safety) */
    return 1;
}
void dBaseActor_postExecute(GM_CTX, gptr self, uint32_t status) {
    if (status != 2) return;
    double x = LF(self + A_POS), y = LF(self + A_POS + 4), z = LF(self + A_POS + 8);
    double dz = frsp(z - LF(self + A_LAST + 8)), dy = frsp(y - LF(self + A_LAST + 4)), dx = frsp(x - LF(self + A_LAST));
    SF(self + A_DELTA, dx); SF(self + A_DELTA + 4, dy); SF(self + A_DELTA + 8, dz);
    SF(self + A_LAST, x); SF(self + A_LAST + 4, y); SF(self + A_LAST + 8, z);
}
int32_t dBaseActor_preDraw(GM_CTX, gptr self) { GM_FN(0x8006C9F0); return dBase_preDraw(GM_PASS, self) ? gm_u8(self + A_VIS) != 0 : 0; }
void dBaseActor_setTmpCtData(gptr pos, gptr ang) { gm_set_ptr(TMP_POS, pos); gm_set_ptr(TMP_ANGLE, ang); }
gptr dBaseActor_construct(GM_CTX, uint32_t prof, uint32_t param, gptr pos, gptr ang) { GM_FN(0x8006CA80);
    dBaseActor_setTmpCtData(pos, ang);
    gptr parent = dBase_searchBaseByProfName(GM_PASS, gm_u16(NOW_SCENE), 0);
    return dBase_createBase(GM_PASS, prof, parent, param, GROUP_ACTOR);
}
gptr dBaseActor_construct2(GM_CTX, uint32_t prof, gptr parent, uint32_t param, gptr pos, gptr ang) { GM_FN(0x8006CBA0);
    dBaseActor_setTmpCtData(pos, ang);
    return dBase_createBase(GM_PASS, prof, parent, param, GROUP_ACTOR);
}
/* every actor's draw2D (vtable +0x50) or draw2D_lyt2 (+0x54) */
static void draw2D_all(GM_CTX, uint32_t off) { GM_FN((off == 0x50 ? 0x8006CAE0u : 0x8006CB40u));
    for (gptr a = 0; (a = fManager_searchBaseByGroupType(GM_PASS, GROUP_ACTOR, a)); ) { GM_LOOP(); GM_CALL(gm_u32(gm_u32(a + 0x60) + off), 1, a); }
}
/* (part 48: register-exact - the float registers and CR0 as the PowerPC code leaves them) */
#define FB(n, v) (ctx->f[n].d = ctx->ps1[n] = (v))
#define FR(n) (ctx->f[n].d)
#define FMR(d_, s_) (ctx->f[d_].u = ctx->f[s_].u)
static inline int fcmp0(ppc_context *ctx, double a, double b) { cr_fcmp(ctx, 0, a, b); return (a > b) - (a < b); }
void dBaseActor_posMove(GM_CTX, gptr self, gptr d) {
    FB(1, LF(self + A_POS)); FB(0, LF(d)); FB(2, LF(self + A_POS + 4));
    FB(0, frsp(FR(1) + FR(0)));
    FB(1, LF(self + A_POS + 8));
    SF(self + A_POS, FR(0));
    FB(0, LF(d + 4)); FB(0, frsp(FR(2) + FR(0))); SF(self + A_POS + 4, FR(0));
    FB(0, LF(d + 8)); FB(0, frsp(FR(1) + FR(0))); SF(self + A_POS + 8, FR(0));
}
/* towards max by acc (the speed / max / acc at the offsets; up: + when below) - the shape of
   calcSpeedF / calcFallSpeed: f1 the value, f2 the target (stored when passed), f0 the step */
static void approach(GM_CTX, gptr self, uint32_t o_val, uint32_t o_max, uint32_t o_acc, int up_adds) {
    FB(1, LF(self + o_val)); FB(2, LF(self + o_max));
    int c = fcmp0(ctx, FR(1), FR(2));
    if (c < 0) { FB(0, LF(self + o_acc)); FB(0, up_adds ? frsp(FR(1) + FR(0)) : frsp(FR(1) - FR(0))); if (!(fcmp0(ctx, FR(0), FR(2)) > 0)) FMR(2, 0); }
    else if (c > 0) { FB(0, LF(self + o_acc)); FB(0, up_adds ? frsp(FR(1) - FR(0)) : frsp(FR(1) + FR(0))); if (!(fcmp0(ctx, FR(0), FR(2)) < 0)) FMR(2, 0); }
    else return;
    SF(self + o_val, FR(2));
}
void dBaseActor_calcSpeedF(GM_CTX, gptr self) { approach(GM_PASS, self, A_SPEEDF, A_MAXSF, A_ACCF, 1); }
void dBaseActor_calcFallSpeed(GM_CTX, gptr self) { approach(GM_PASS, self, A_SPEED + 4, A_MAXFALL, A_ACCY, 0); }
void dBaseActor_calcSpeedXY(GM_CTX, gptr self) {
    GM_FN(0x8006CD50); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    NV_R(31, self);
    ctx->lr = 0x8006CD68u; dBaseActor_calcSpeedF(GM_PASS, self);
    FB(0, LF(self + A_SPEEDF));
    ctx->r[3] = self;
    SF(self + A_SPEED, FR(0));
    ctx->lr = 0x8006CD78u; dBaseActor_calcFallSpeed(GM_PASS, self);
    ctx->r[0] = lr;
}
void dBaseActor_calcSpeedX(GM_CTX, gptr self) {
    FB(2, LF(self + A_SPEED)); FB(1, LF(self + A_SMAX));
    int c = fcmp0(ctx, FR(2), FR(1));
    if (c < 0) { FB(0, LF(self + A_ACCF)); FB(2, frsp(FR(2) + FR(0))); if (fcmp0(ctx, FR(2), FR(1)) > 0) FMR(2, 1); }
    else if (c > 0) { FB(0, LF(self + A_ACCF)); FB(2, frsp(FR(2) - FR(0))); if (fcmp0(ctx, FR(2), FR(1)) < 0) FMR(2, 1); }
    SF(self + A_SPEED, FR(2));
}
void dBaseActor_calcSpeedY(GM_CTX, gptr self) {
    FB(2, LF(self + A_SPEED + 4)); FB(1, LF(self + A_ACCY)); FB(0, LF(self + A_SMAX + 4));
    FB(1, frsp(FR(2) + FR(1)));
    if (fcmp0(ctx, FR(1), FR(0)) < 0) FMR(1, 0);
    SF(self + A_SPEED + 4, FR(1));
}
void dBaseActor_getCenterPos(GM_CTX, gptr out, gptr self) {
    FB(1, LF(self + A_POS + 8)); FB(0, LF(self + A_CENTER + 8)); FB(3, LF(self + A_POS + 4));
    FB(4, frsp(FR(1) + FR(0)));
    FB(2, LF(self + A_CENTER + 4)); FB(1, LF(self + A_POS)); FB(0, LF(self + A_CENTER));
    FB(2, frsp(FR(3) + FR(2)));
    SF(out + 8, FR(4));
    FB(0, frsp(FR(1) + FR(0)));
    SF(out + 4, FR(2)); SF(out, FR(0));
}
#undef FB
#undef FR
#undef FMR

/* postExecute(status), register-exact (part 48): the frame's temporaries at f+8 .. f+16 as the
   PowerPC code leaves them, then dBase_c::postExecute (empty) */
static void postexec_r(GM_CTX, gptr self, uint32_t status) {
    GM_FN(0x8006C980); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    gptr f = gm_frame_sp;
    cr_cmp_s(ctx, 0, (int32_t)status, 2);
    if (status == 2) {
#define FB(n, v) (ctx->f[n].d = ctx->ps1[n] = (v))
        FB(4, LF(self + A_POS + 8)); FB(0, LF(self + A_LAST + 8)); FB(3, LF(self + A_POS + 4));
        FB(5, frsp(ctx->f[4].d - ctx->f[0].d));
        FB(2, LF(self + A_LAST + 4)); FB(1, LF(self + A_POS)); FB(0, LF(self + A_LAST));
        FB(2, frsp(ctx->f[3].d - ctx->f[2].d));
        SF(f + 16, ctx->f[5].d);
        FB(0, frsp(ctx->f[1].d - ctx->f[0].d));
        SF(f + 12, ctx->f[2].d); SF(f + 8, ctx->f[0].d);
        SF(self + A_DELTA, ctx->f[0].d); SF(self + A_DELTA + 4, ctx->f[2].d); SF(self + A_DELTA + 8, ctx->f[5].d);
        SF(self + A_LAST, ctx->f[1].d); SF(self + A_LAST + 4, ctx->f[3].d); SF(self + A_LAST + 8, ctx->f[4].d);
#undef FB
    }
    ctx->lr = 0x8006C9E0u;                                   /* (bl dBase_c::postExecute: a blr) */
    ctx->r[0] = lr;
}

/* ================================================================== hle entry points */
#define A(i) GM_ARG(i)
/* dBase_c */
GM_HLE_INT(fn_8006C500, NOW_SCENE, 4) {                                                                 /* dBase_c::searchBaseByProfName */
    GM_FN(0x8006C500); GM_LR_KEEP;                                  /* (register-exact: fBase_c's search through its entry) */
    uint32_t lr = ctx->lr;
    cr_cmp_s(ctx, 0, (int32_t)A(1), 0);
    GM_CALLV(0x8006C520u, 0x80162D50u, 0);
    cr_cmp_s(ctx, 0, (int32_t)A(0), 0);
    ctx->r[0] = lr;
}        /* dBase_c::searchBaseByProfName */
GM_HLE(beforeCreate__7dBase_cFv) { GM_RET(dBase_preCreate()); }                                        /* dBase_c::preCreate */
GM_HLE(afterCreate__7dBase_cFi) { fBase_postCreate(GM_PASS, A(0), A(1)); }                             /* dBase_c::postCreate */
GM_HLE(beforeDelete__7dBase_cFv) { GM_RET(dBase_preDelete(GM_PASS, A(0))); }                           /* dBase_c::preDelete */
GM_HLE(afterDelete__7dBase_cFi) { fBase_postDelete(GM_PASS, A(0), A(1)); }                             /* dBase_c::postDelete */
GM_HLE(beforeExecute__7dBase_cFv) { GM_RET(dBase_preExecute(GM_PASS, A(0))); }                         /* dBase_c::preExecute */
GM_HLE(beforeDraw__7dBase_cFv) { GM_RET(dBase_preDraw(GM_PASS, A(0))); }                               /* dBase_c::preDraw */
GM_HLE_INT(GetExplanationString__7dBase_cFv, KIND_STRING, 4) { GM_RET(KIND_STRING); }                         /* dBase_c::getKindString */
GM_HLE_INT(fn_8006C670, KIND_STRING, 4) { GM_RET(2); }                                                        /* dBase_c::loadAsyncCallback */
GM_HLE_VOID(fn_8006C690, LOAD_CB, 8) { ctx->r[4] = F_LOAD_ASYNC; gm_set_u32(LOAD_CB, F_LOAD_ASYNC); ctx->r[3] = F_UNLOAD; gm_set_u32(UNLOAD_CB, F_UNLOAD); }   /* dBase_c::initLoader */
GM_HLE(fn_8006C6B0) { GM_RET(dBase_createBase(GM_PASS, A(0), A(1), A(2), A(3))); }                     /* dBase_c::createBase */
GM_HLE(fn_8006C6C0) { GM_RET(fBase_make(GM_PASS, A(0), 0, A(1), A(2))); }                              /* dBase_c::createRoot */
/* dBaseActor_c */
GM_HLE(__ct__8dActor_cFv) { GM_RET(dBaseActor_ctor(GM_PASS, A(0))); }                                  /* dBaseActor_c::dBaseActor_c */
GM_HLE(__dt__8dActor_cFv) { GM_RET(dBaseActor_dtor(GM_PASS, A(0), (int32_t)A(1))); }                   /* dBaseActor_c::~dBaseActor_c */
GM_HLE(fn_8006C870) { GM_RET(dBase_preCreate()); }                                                     /* dBaseActor_c::preCreate */
GM_HLE(fn_8006C8A0) { fBase_postCreate(GM_PASS, A(0), A(1)); }                                         /* ::postCreate */
GM_HLE(fn_8006C8B0) { GM_FN(0x8006C8B0); GM_RET(dBase_preDelete(GM_PASS, A(0))); }                                        /* ::preDelete */
GM_HLE(fn_8006C8E0) { fBase_postDelete(GM_PASS, A(0), A(1)); }                                         /* ::postDelete */
GM_HLE(fn_8006C8F0) { GM_RET(dBaseActor_preExecute(GM_PASS, A(0))); }                                  /* ::preExecute */
GM_HLE_VOID(fn_8006C980, A(0) + A_LAST, 0x18) { postexec_r(GM_PASS, A(0), A(1)); }         /* ::postExecute */
GM_HLE(fn_8006C9F0) { GM_RET(dBaseActor_preDraw(GM_PASS, A(0))); }                                     /* ::preDraw */
GM_HLE_VOID(AXFXSetHooks, TMP_POS, 8) { dBaseActor_setTmpCtData(A(0), A(1)); }                         /* ::setTmpCtData */
GM_HLE(fn_8006CA80) { GM_RET(dBaseActor_construct(GM_PASS, A(0), A(1), A(2), A(3))); }                 /* ::construct (in the scene) */
GM_HLE(DoSpecialDrawing1__Fv) { draw2D_all(GM_PASS, 0x50); }                                           /* ::draw2DActorOnLyt1 */
GM_HLE(DoSpecialDrawing2__Fv) { draw2D_all(GM_PASS, 0x54); }                                           /* ::draw2DActorOnLyt2 */
GM_HLE(_Z17CreateChildObjectsPviii) { GM_RET(dBaseActor_construct2(GM_PASS, A(0), A(1), A(2), A(3), A(4))); }   /* ::construct (with a parent) */
GM_HLE_VOID(fn_8006CD00, A(0) + A_POS, 0xC) { dBaseActor_posMove(GM_PASS, A(0), A(1)); }               /* ::posMove(delta) */
GM_HLE_VOID(UpdateObjectPosBasedOnSpeedValues_real, A(0) + A_POS, 0xC) { ctx->r[4] = A(0) + A_SPEED; dBaseActor_posMove(GM_PASS, A(0), A(0) + A_SPEED); }   /* ::posMove() */
GM_HLE_VOID(fn_8006CD50, A(0) + A_SPEED, 0x30) { dBaseActor_calcSpeedXY(GM_PASS, A(0)); }              /* ::calcSpeedXY */
GM_HLE_VOID(HandleXSpeed, A(0) + A_SPEED, 0xC) { dBaseActor_calcSpeedX(GM_PASS, A(0)); }               /* ::calcSpeedX */
GM_HLE_VOID(HandleYSpeed, A(0) + A_SPEED, 0xC) { dBaseActor_calcSpeedY(GM_PASS, A(0)); }               /* ::calcSpeedY */
GM_HLE_VOID(fn_8006CE10, A(0) + A_SPEEDF, 4) { dBaseActor_calcSpeedF(GM_PASS, A(0)); }                 /* ::calcSpeedF */
GM_HLE_VOID(fn_8006CE70, A(0) + A_SPEED + 4, 4) { dBaseActor_calcFallSpeed(GM_PASS, A(0)); }           /* ::calcFallSpeed */
GM_HLE_VOID(Actor_GetVec3WithValuesAdded, A(0), 0xC) { dBaseActor_getCenterPos(GM_PASS, A(0), A(1)); } /* ::getCenterPos */
GM_HLE_INT(fn_8006CF10, ACTOR_MANAGE, 8) { GM_RET(fLiMgBa_countNodeByProfName(GM_PASS, ACTOR_MANAGE, A(1))); }   /* ::GetProfNameActorNum */

/* (part 54) the rest of dBase_c / dBaseActor_c: the post steps (fBase_c's, tail calls), the empty
   virtuals, calcBaseMtx-like (the translation, then the Y rotation into +124) and the clear of
   the 2D actor list head */
GM_HLE(afterExecute__7dBase_cFi) { GM_TAIL(0x80162110u, 0); }                                     /* dBase_c::postExecute */
GM_HLE(afterDraw__7dBase_cFi)    { GM_TAIL(0x80162210u, 0); }                                     /* dBase_c::postDraw */
GM_HLE(fn_8006C680) { }                                                                  /* dBaseActor_c::(an empty virtual) */
GM_HLE(fn_8006CA40) { GM_TAIL(0x8006C650u, 0); }                                                   /* dBaseActor_c::postDraw (dBase_c's) */
GM_HLE(specialDraw1__8dActor_cFv) { }                                                    /* dBaseActor_c::draw2D */
GM_HLE(specialDraw2__8dActor_cFv) { }                                                    /* dBaseActor_c::draw2D_lyt2 */
static void dba_calc_mtx(GM_CTX) {
    GM_FN(0x8006CCB0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr; gptr f = gm_frame_sp;
    ctx->r[31] = ctx->r[3];
    ctx->f[3].d = ctx->ps1[3] = ldfs(base, ctx->r[3] + 180);
    ctx->f[2].d = ctx->ps1[2] = ldfs(base, ctx->r[3] + 176);
    ctx->f[1].d = ctx->ps1[1] = ldfs(base, ctx->r[3] + 172);
    ctx->r[3] = ctx->r[3] + 124;
    GM_CALLV(0x8006CCD8u, 0x801C0BD0u, 0);                                                          /* PSMTXTrans(mMatrix, pos) */
    ctx->r[0] = gm_u16(ctx->r[31] + 258);
    ctx->r[3] = ctx->r[31] + 124;
    gm_set_u16(f + 8, (uint16_t)ctx->r[0]);
    ctx->r[4] = f + 8;
    GM_CALLV(0x8006CCECu, 0x8016EDD0u, 0);                                                          /* mMtx_c::YrotM(angle.y) */
    ctx->r[0] = lr;
}
GM_HLE(fn_8006CCB0) { dba_calc_mtx(GM_PASS); }
GM_HLE_VOID(fn_8006CF20, ctx->r[13] - 22752, 8) { ctx->r[3] = ctx->r[13] - 22752; ctx->r[0] = 0; gm_set_u32(ctx->r[3], 0); gm_set_u32(ctx->r[3] + 4, 0); }
