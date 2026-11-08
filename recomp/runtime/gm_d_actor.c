/* gm_d_actor.c - dActor_c, the actor that lives in a stage (d_actor.cpp): the lifecycle steps,
 * construct, kinds, the loop-dependent function tables, deleteActor and the small helpers.
 * Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_actor.cpp) and checked against the
 * recompiled USA rev 2 code - where they differ the recompiled code wins (deleteActor). The
 * 8-player module patches some of this file's loops from 4 to 8 players (g_mod_on, as the
 * recompiled code does) and replaces three functions (left recompiled).
 *
 * dActor_c (after dBaseActor_c's 0x125 bytes):
 *   +0x134 combo count   +0x148 its collider (ActivePhysics / dCc_c)   +0x1EC dBc_c   +0x2DC dRc_c
 *   +0x310 (a 2D vector cleared after each execute)   +0x349 area number   +0x34C the spawn flags
 *   +0x350 the delete value   +0x366 block hit   +0x36C eat state   +0x370 the scale before eating
 *   +0x38C kind   +0x38E the execute stop mask.
 * vtable (+0x60): +0x4C getKindString, +0x60 ActorDrawCullCheck, +0x64 block_hit_init. */
#include "gm.h"
#include "gm_nv.h"

/* gm_d_base.c / gm_f_base.c */
int32_t dBaseActor_preExecute(GM_CTX, gptr self);
void dBaseActor_postExecute(GM_CTX, gptr self, uint32_t status);
int32_t dBaseActor_preDraw(GM_CTX, gptr self);
gptr dBaseActor_dtor(GM_CTX, gptr self, int32_t flags);
gptr dBaseActor_construct(GM_CTX, uint32_t prof, uint32_t param, gptr pos, gptr ang);
gptr dBaseActor_construct2(GM_CTX, uint32_t prof, gptr parent, uint32_t param, gptr pos, gptr ang);
int32_t dBase_preDelete(GM_CTX, gptr self);
void fBase_postCreate(GM_CTX, gptr self, uint32_t state);
void fBase_postDelete(GM_CTX, gptr self, uint32_t state);
void fBase_deleteRequest(GM_CTX, gptr self);
void fBase_opDelete(GM_CTX, gptr p);
extern int g_mod_on;

#define SDA 0x8042F680u
#define EXEC_STOP     (SDA - 0x5986)     /* dActor_c::mExecStop, mDrawStop */
#define DRAW_STOP     (SDA - 0x5985)
#define TMP_LAYER     (SDA - 0x5970)     /* dActor_c::m_tmpCtLayerNo */
#define SEARCH_FUNC   (SDA - 0x5984)     /* dActor_c::mSearchNearPlayerFunc, mGetTrgToSrcDirFunc */
#define TRGDIR_FUNC   (SDA - 0x5980)
#define ATTENTION     (SDA - 0x5930)     /* dAttention_c::mspInstance */
#define SEARCH_TABLE  0x802EF328u
#define TRGDIR_TABLE  0x802EF334u
#define KIND_STRING   0x80309F50u
#define VT_ACTOR      0x80309F6Cu
#define F_GAME_STOP   0x800B3B50u        /* dGameCom::isGameStop */
#define F_RC_CLRLINK  0x800D9AC0u
#define F_RC_CHKLINK  0x800D9AD0u
#define F_BC_CHKLINK  0x80075090u
#define F_CC_CLEAR    0x8008C2C0u
#define F_CC_REMOVE   0x8008C380u
#define F_CC_ADD      0x8008C330u
#define F_CC_DT       0x8008C260u
#define F_RC_DT       0x800D9880u
#define F_BC_DT       0x8006CFA0u
#define F_LOOP_POS_X  0x80101AA0u        /* dScStage_c::getLoopPosX(float) */
#define F_ATTN_ENTRY  0x80069240u
#define F_SET_CHANGE_POS 0x80101BC0u     /* dScStage_c::setChangePosFunc */
#define F_GET_PLAYER  0x8005F900u        /* daPyMng_c::getPlayer */

#define LF(a)    ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static uint32_t vcall1(GM_CTX, gptr self, uint32_t off) { return GM_CALL(gm_u32(gm_u32(self + 0x60) + off), 1, self); }
/* a guest function taking a float (f1) and returning one */
static double gcall_ff(GM_CTX, uint32_t fn, double x) { ctx->f[1].d = ctx->ps1[1] = x; GM_CALL(fn, 0); return ctx->f[1].d; }


/* a guest stack frame for locals passed to guest functions (as the PowerPC code makes one) */
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f      /* (gm.h: the PowerPC function's frame and prologue) */
void dBaseActor_getCenterPos(GM_CTX, gptr out, gptr self);
gptr dBaseActor_ctor(GM_CTX, gptr self);
#define F_CC_CT       0x8008C200u
#define F_BC_CT       0x8006CF40u
#define F_RC_CT       0x800D9860u
#define F_RC_SET      0x800D98C0u
#define F_GET_AREA_NO 0x8008E770u        /* dCdFile_c::getAreaNo(&pos) */
#define F_SOME_CHECK  0x800B55F0u        /* dGameCom::someCheck(pos, range): off screen? */
#define CHANGE_POS_FN (SDA - 0x5458)     /* dScStage_c's changePosAngle function */
#define STAGE         (SDA - 0x54B8)     /* dScStage_c::m_instance */
#define CD            (SDA - 0x57E8)     /* dCd_c::m_instance */

gptr dActor_dtor(GM_CTX, gptr self, int32_t flags) {
    FN(0x800642B0);
    if (!self) return self;
    gm_set_ptr(self + 0x60, VT_ACTOR);
    GM_CALLR(0x800642E8u, F_CC_REMOVE, 1, self + 0x148);
    GM_CALLR(0x800642F4u, F_RC_DT, 2, self + 0x2DC, (uint32_t)-1);
    GM_CALLR(0x80064300u, F_BC_DT, 2, self + 0x1EC, (uint32_t)-1);
    GM_CALLR(0x8006430Cu, F_CC_DT, 2, self + 0x148, (uint32_t)-1);
    dBaseActor_dtor(GM_PASS, self, 0);
    if (flags > 0) fBase_opDelete(GM_PASS, self);
    return self;
}
int32_t dActor_preDelete(GM_CTX, gptr self) {
    FN(0x80064390);
    if (!dBase_preDelete(GM_PASS, self)) return 0;
    gm_set_u32(self + 0x134, 0);                                    /* clrComboCnt */
    return 1;
}
int32_t dActor_preExecute(GM_CTX, gptr self) {
    FN(0x800643F0);
    if (!dBaseActor_preExecute(GM_PASS, self)) return 0;
    if (GM_CALLR(0x80064420u, F_GAME_STOP, 1, 0xFFFFFFFFu)) return 0;
    if (gm_u8(EXEC_STOP) & gm_u8(self + 0x38E)) return 0;
    GM_CALLR(0x80064450u, F_RC_CLRLINK, 1, self + 0x2DC);
    if (gm_u8(self + 0x366) == 1) { gm_set_u8(self + 0x366, 0); vcall1(GM_PASS, self, 0x64); }   /* block_hit_init */
    return 1;
}
void dActor_postExecute(GM_CTX, gptr self, uint32_t status) {
    FN(0x80064490);
    if (status == 2) {
        if (!(gm_u32(self + 0x120) & 0x400)) SF(self + 0xAC, gcall_ff(GM_PASS, F_LOOP_POS_X, LF(self + 0xAC)));
        GM_CALLR(0x800644D4u, F_CC_CLEAR, 1, self + 0x148);
        if (!gm_u8(self + 0xB)) { GM_CALLR(0x800644E8u, F_BC_CHKLINK, 1, self + 0x1EC); GM_CALLR(0x800644F0u, F_RC_CHKLINK, 1, self + 0x2DC); }
        if (gm_u32(self + 0x120) & 8) GM_CALLR(0x80064508u, F_ATTN_ENTRY, 2, gm_ptr(ATTENTION), gm_u32(self));
        double zero = LF(ctx->r[2] - 0x7554);
        SF(self + 0x310, zero); SF(self + 0x314, zero);
    }
    dBaseActor_postExecute(GM_PASS, self, status);
}
int32_t dActor_preDraw(GM_CTX, gptr self) {
    FN(0x80064540);
    if (!dBaseActor_preDraw(GM_PASS, self)) return 0;
    uint32_t sh = gm_u8(self + 0x38C);
    if (gm_u8(DRAW_STOP) & (uint8_t)(sh < 32 ? 1u << sh : 0)) return 0;
    if (gm_u8(self + 0x36C) == 2) return 0;                         /* (being eaten) */
    if ((gm_u32(self + 0x120) & 2) && vcall1(GM_PASS, self, 0x60)) return 0;   /* ActorDrawCullCheck */
    return 1;
}
void dActor_setKind(GM_CTX, gptr self, uint32_t kind) {
    FN(0x800646E0);
    gm_set_u8(self + 0x38C, (uint8_t)kind);
    gm_set_ptr(self + 0x68, vcall1(GM_PASS, self, 0x4C));
}
void dActor_setLoopFunc(GM_CTX, uint32_t type) {
    FN(0x80064B10);
    GM_CALL(F_SET_CHANGE_POS, 1, type);
    gm_set_u32(SEARCH_FUNC, gm_u32(SEARCH_TABLE + 4 * type));
    gm_set_u32(TRGDIR_FUNC, gm_u32(TRGDIR_TABLE + 4 * type));
}
/* is a player in this actor's area? */
int32_t dActor_checkAreaNo(GM_CTX, gptr self) {
    FN(0x80064B50);
    int32_t n = g_mod_on ? 8 : 4;
    for (int32_t i = 0; ; ) {
        gptr p = GM_CALLR(0x80064B74u, F_GET_PLAYER, 1, (uint32_t)i);
        if (p && gm_u8(p + 0x349) == gm_u8(self + 0x349)) return 1;
        if (++i >= n) break;
        GM_LOOP();
    }
    return 0;
}
void dActor_deleteActor(GM_CTX, gptr self, uint32_t forever) {
    FN(0x80064D10);
    fBase_deleteRequest(GM_PASS, self);
    gptr flags = gm_ptr(self + 0x34C), val = gm_ptr(self + 0x350);
    if (!flags || !val) return;
    if (!(forever & 0xFF)) { gm_set_u8(flags, gm_u8(flags) & 0xFE); return; }   /* (it may come back) */
    gm_set_u8(flags, gm_u8(flags) | 8);
    gm_set_u16(val, 300);
}

void dActor_setKind(GM_CTX, gptr self, uint32_t kind);
gptr dActor_ctor(GM_CTX, gptr self) {
    FN(0x80064110);
    dBaseActor_ctor(GM_PASS, self);
    double c = LF(ctx->r[2] - 0x7558);
    gm_set_ptr(self + 0x60, VT_ACTOR);
    gm_set_u8(self + 0x125, 0); gm_set_u32(self + 0x128, 0xFFFFFFFFu); gm_set_u32(self + 0x13C, 0); SF(self + 0x140, c);
    GM_CALLR(0x80064160u, F_CC_CT, 1, self + 0x148);
    GM_CALLR(0x80064168u, F_BC_CT, 1, self + 0x1EC);
    GM_CALLR(0x80064170u, F_RC_CT, 1, self + 0x2DC);
    double z = LF(ctx->r[2] - 0x7554);
    for (int i = 0; i < 8; i++) SF(self + 0x318 + 4 * i, z);
    gm_set_u32(self + 0x34C, 0); gm_set_u32(self + 0x350, 0); gm_set_u32(self + 0x368, 0); gm_set_u8(self + 0x36D, 2);
    gm_set_u32(self + 0x380, 0); gm_set_u8(self + 0x38D, 0xFF); gm_set_u8(self + 0x390, 0);
    dActor_setKind(GM_PASS, self, 0);
    double f1 = LF(ctx->r[2] - 0x7550), f0 = LF(ctx->r[2] - 0x754C);
    gm_set_u8(self + 0x38E, 1);
    SF(self + 0x328, LF(ctx->r[2] - 0x7578)); SF(self + 0x32C, LF(ctx->r[2] - 0x7574));
    SF(self + 0x330, LF(ctx->r[2] - 0x7570)); SF(self + 0x334, LF(ctx->r[2] - 0x756C));
    SF(self + 0x338, f1); SF(self + 0x33C, f1); SF(self + 0x340, f0); SF(self + 0x344, f0);
    gptr file = gm_ptr(CD) + 0x3B0u * gm_u8(gm_ptr(STAGE) + 0x120E);   /* dCd_c::getFileP(the current file) */
    if (!gm_u32(file + 0x2C)) file = 0;
    gm_set_u8(self + 0x349, (uint8_t)GM_CALLR(0x80064240u, F_GET_AREA_NO, 2, file, self + 0xAC));
    gm_set_ptr(self + 0x23C, self + 0x2DC);
    GM_CALLR(0x8006425Cu, F_RC_SET, 3, self + 0x2DC, self, 1);
    gm_set_ptr(self + 0x2F4, self + 0x1EC);
    gm_set_u8(self + 0x34A, 0); gm_set_u32(self + 0x134, 0);
    uint8_t layer = gm_u8(TMP_LAYER);
    gm_set_u8(self + 0x38F, layer); gm_set_u8(self + 0x1E8, layer); gm_set_u8(self + 0x2D8, layer); gm_set_u8(self + 0x30E, layer);
    gm_set_u32(self + 0x37C, 0); gm_set_u8(self + 0x366, 0);
    return self;
}
/* ActorDrawCullCheck: the visible area around the (loop-adjusted) position off screen? */
uint32_t dActor_drawCullCheck(GM_CTX, gptr self) {
    FN(0x80065080);
    double k = LF(ctx->r[2] - 0x7544);
    SF(f + 0x18, LF(self + 0x320)); SF(f + 0x1C, LF(self + 0x324));
    double c = LF(ctx->r[2] - 0x7530);
    SF(f + 0x20, frsp(k * LF(self + 0x318)));
    SF(f + 0x24, frsp(c + frsp(k * LF(self + 0x31C))));
    SF(f + 8, LF(self + 0xAC)); SF(f + 0xC, LF(self + 0xB0)); SF(f + 0x10, LF(self + 0xB4));
    GM_CALL(gm_u32(CHANGE_POS_FN), 3, f + 8, 0, 1);
    uint32_t r = GM_CALLR(0x800650F4u, F_SOME_CHECK, 2, f + 8, f + 0x18);
    return r;
}
/* searchNearPlayer: the nearest player to the centre (through the loop-dependent function) */
uint32_t dActor_searchNearPlayer(GM_CTX, gptr self, gptr delta) {
    FN(0x80064740);
    dBaseActor_getCenterPos(GM_PASS, f + 0x10, self);
    double y = LF(f + 0x14), x = LF(f + 0x10);
    SF(f + 8, x); SF(f + 0xC, y);
    uint32_t r = GM_CALL(gm_u32(SEARCH_FUNC), 2, delta, f + 8);
    return r;
}

/* ---- part 2: the near-player searches, culling, killing, eating, combo sounds ---- */
gptr fManager_searchBaseByID(GM_CTX, uint32_t id);
#define ACTIVE_PLAYERS (SDA - 0x59D8)    /* (u8 bit mask of the players in the game) */
#define NUM_PLAYERS    (SDA - 0x59E0)    /* (int) */
#define STAGE_LOOP     (SDA - 0x58B0)    /* (the stage's loop data: + 0x8FEA0 the loop width) */
#define SCORE_MNG      (SDA - 0x5630)    /* dScoreMng_c::m_instance */
#define SND_MNG        (SDA - 0x56D0)
#define SND_OBJ        (SDA - 0x5924)
#define COMBO_INIT     (SDA - 0x5957)    /* (s8: the combo sound table is set) */
#define COMBO_TABLE    0x80355E40u
#define F_AREA_DATA    0x8008E410u       /* dCdFile_c::getAreaP(area, 0) */
#define F_CHECK_RIDE   0x80070CA0u       /* dBc_c::checkRide */
#define F_IS_FOOT      0x80070CB0u       /* dBc_c::isFoot */
#define F_SCREEN_CULL  0x800B56E0u       /* dActor_c::screenCullCheck */
#define F_KILL_PLAYER_LINK 0x8012E510u
#define F_CREATE_EFFECT 0x8016C890u      /* mEf::createEffect */
#define F_SCORE_UNKNOWN 0x800E23C0u
#define F_SCORE_SET    0x800E20A0u
#define F_SMALL_SCORE  0x800B3540u       /* dGameCom::CreateSmallScore */
#define F_ADD_SCORE    0x80060690u       /* daPyMng_c::addScore */
#define F_EAT_SOUND    0x800CEA20u
#define F_COMBO_SOUND  0x800CE8C0u
#define F_REMOTE_PLAYER 0x80069530u      /* dAudio::getRemotePlayer */
#define F_CVT_SND_POS  0x8006A4B0u       /* dAudio::cvtSndObjctPos(mVec3_c) */
#define F_START_SOUND  0x80197F00u       /* SndObjctCmnEmy::startSound */
#define R2F(off) LF(ctx->r[2] - (off))
static int32_t players_max(void) { return g_mod_on ? 8 : 4; }
static int player_on(int i) { uint32_t s = (uint32_t)i & 63; return (gm_u8(ACTIVE_PLAYERS) & (s > 31 ? 0 : 1u << s)) != 0; }
static double cen_x(GM_CTX, gptr a) { return frsp(LF(a + 0xAC) + LF(a + 0xD0)); }
static double cen_y(GM_CTX, gptr a) { return frsp(LF(a + 0xB0) + LF(a + 0xD4)); }

/* searchNearPlayerNormal(delta, pos): the nearest player (squared distance) */
gptr dActor_searchNearPlayerNormal(GM_CTX, gptr delta, gptr pos) {
    FN(0x800647A0);
    double best = R2F(0x7548); gptr found = 0;
    for (int32_t i = 0; ; ) {
        gptr p = GM_CALLR(0x800647DCu, F_GET_PLAYER, 1, (uint32_t)i);
        if (p && player_on(i)) {
            double x = cen_x(GM_PASS, p), y = cen_y(GM_PASS, p);
            double dx = frsp(x - LF(pos)), dy = frsp(y - LF(pos + 4));
            double d = frsp(frsp(dx * dx) + frsp(dy * dy));
            if (best > d) { best = d; SF(delta, dx); found = p; SF(delta + 4, dy); }
        }
        if (++i >= players_max()) break;
        GM_LOOP();
    }
    return found;
}
/* searchNearPlayerLoop: the same in a looping stage (x distances wrap around) */
gptr dActor_searchNearPlayerLoop(GM_CTX, gptr delta, gptr pos) {
    FN(0x80064880);
    double w = LF(gm_ptr(STAGE_LOOP) + 0x8FEA0);
    double px = frsp(gcall_ff(GM_PASS, F_LOOP_POS_X, LF(pos))), py = LF(pos + 4);
    double best = R2F(0x7548), zero = R2F(0x7554), half = R2F(0x7544);
    gptr found = 0;
    for (int32_t i = 0; ; ) {
        gptr p = GM_CALLR(0x800648FCu, F_GET_PLAYER, 1, (uint32_t)i);
        if (p && player_on(i)) {
            double lx = frsp(gcall_ff(GM_PASS, F_LOOP_POS_X, cen_x(GM_PASS, p)));   /* (stored and reloaded as a float) */
            double y = cen_y(GM_PASS, p);
            double dx = frsp(lx - px);
            if (dx < zero) { if (dx < frsp(-w * half)) dx = frsp(frsp(dx + w)); }
            else if (dx > frsp(w * half)) dx = frsp(frsp(dx - w));
            double dy = frsp(y - py);
            double d = frsp(frsp(dx * dx) + frsp(dy * dy));
            if (best > d) { best = d; SF(delta, dx); found = p; SF(delta + 4, dy); }
        }
        if (++i >= players_max()) break;
        GM_LOOP();
    }
    return found;
}
/* getTrgToSrcDirLoop(trgX, srcX): is the target to the left (in a looping stage)? */
uint32_t dActor_getTrgToSrcDirLoop(GM_CTX, double trg, double src) {
    FN(0x80064A50);
    double a = gcall_ff(GM_PASS, F_LOOP_POS_X, trg), b = gcall_ff(GM_PASS, F_LOOP_POS_X, src);
    double d = frsp(a - b), h = frsp(LF(gm_ptr(STAGE_LOOP) + 0x8FEA0) * R2F(0x7544));
    if (d < R2F(0x7554)) return !(d < -h);
    return d > h;
}
/* HasamareBgCheck: squeezed between walls / floor and ceiling? */
uint32_t dActor_hasamareBgCheck(GM_CTX, gptr self) {
    GM_FN(0x80065110);
    uint8_t f = gm_u8(self + 0x34A);
    if (!f) return 0;
    if ((f & 1) && (gm_u32(self + 0x274) & 0x15)) return 1;
    if ((f & 2) && (gm_u32(self + 0x274) & 0x2A)) return 1;
    if ((f & 8) && GM_CALLR(0x80065178u, F_IS_FOOT, 1, self + 0x1EC)) return 1;
    if ((gm_u8(self + 0x34A) & 4) && (gm_u32(self + 0x274) & 0x3C000000u)) return 1;
    return 0;
}
static double u16f(uint32_t v) { return frsp((double)v); }      /* (the 0x43300000 conversion: exact) */
/* areaCullCheck(pos, bound, area): outside the area? */
uint32_t dActor_areaCullCheck(GM_CTX, gptr self, gptr pos, gptr b, uint32_t area) {
    FN(0x80064DA0);
    gptr file = gm_ptr(CD) + 0x3B0u * gm_u8(gm_ptr(STAGE) + 0x120E);
    if (!gm_u32(file + 0x2C)) file = 0;
    gptr a = GM_CALLR(0x80064E0Cu, F_AREA_DATA, 3, file, area, 0);
    if (!a) return 1;
    double x0 = frsp(frsp(LF(pos) + LF(b)) - LF(b + 8));
    double y0 = frsp(LF(pos + 4) + LF(b + 4));
    double c = R2F(0x7540);
    double hw = frsp(c * LF(b + 8)), hh = frsp(c * LF(b + 12));
    double y1 = frsp(LF(b + 12) + y0);
    int nox = gm_u16(gm_ptr(file + 12) + 8) & 1;
    double mx = LF(self + 0x330), my = LF(self + 0x334);
    double dx = frsp(x0 - u16f(gm_u16(a))), top = frsp(y1 + u16f(gm_u16(a + 2)));
    if (!nox) {
        if (frsp(dx + hw) < -mx) return 1;
        if (dx > frsp(u16f(gm_u16(a + 4)) + mx)) return 1;
    }
    if (frsp(top - hh) > my) return 1;
    if (top < -frsp(u16f(gm_u16(a + 6)) + my)) return 1;
    return 0;
}
/* ActorScrOutCheck(flags): off the area / screen? (flags 2: then delete it) */
uint32_t dActor_scrOutCheck(GM_CTX, gptr self, uint32_t flags) {
    FN(0x80064F50);
    if (gm_u8(self + 0x36C) == 2) return 0;
    if (!(flags & 8) && GM_CALLR(0x80064F94u, F_CHECK_RIDE, 1, self + 0x1EC)) return 0;
    double half = R2F(0x7544);
    SF(f + 24, LF(self + 0x320)); SF(f + 28, LF(self + 0x324));
    SF(f + 32, frsp(half * LF(self + 0x318))); SF(f + 36, frsp(half * LF(self + 0x31C)));
    uint32_t out = 0;
    if (dActor_areaCullCheck(GM_PASS, self, self + 0xAC, f + 24, gm_u8(self + 0x349))) out = 1;
    else if (!(flags & 4)) {
        for (int i = 0; i < 4; i++) SF(f + 8 + 4 * i, LF(self + 0x338 + 4 * i));
        if (GM_CALLR(0x80065034u, F_SCREEN_CULL, 4, self + 0xAC, f + 24, f + 8, gm_u8(self + 0x349))) out = 1;
    }
    if (out && !(flags & 2)) dActor_deleteActor(GM_PASS, self, gm_u8(self + 0x390));   /* (flag 2: keep it) */
    return out;
}
/* checkCarried(&playerNo): is a player carrying this actor? */
uint32_t dActor_checkCarried(GM_CTX, gptr self, gptr out) {
    FN(0x80065FC0);
    for (int32_t i = 0; ; ) {
        gptr p = GM_CALLR(0x80065FF0u, F_GET_PLAYER, 1, (uint32_t)i);
        if (p && fManager_searchBaseByID(GM_PASS, gm_u32(p + 0x2A78)) == self) {
            if (out) { gptr n = GM_CALLR(0x80066028u, gm_u32(gm_u32(p + 0x60) + 0x6C), 1, p); gm_set_u32(out, (uint32_t)(int32_t)gm_s8(n)); }
            return 1;
        }
        if (++i >= players_max()) break;
        GM_LOOP();
    }
    if (out) gm_set_u32(out, 0xFFFFFFFFu);
    return 0;
}
static void call_f12(GM_CTX, uint32_t fn, double f1, double f2, int n, uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    ctx->f[1].d = ctx->ps1[1] = f1; ctx->f[2].d = ctx->ps1[2] = f2;
    GM_CALL(fn, n, a, b, c, d);
}
/* killActor(playerNo, noScore): the death effect, delete, the score */
void dActor_killActor(GM_CTX, gptr self, uint32_t player, uint32_t noScore) {
    FN(0x800656C0);
    double px = LF(self + 0xAC), py = LF(self + 0xB0), pz = LF(self + 0xB4);
    double cx = LF(self + 0xD0), cy = LF(self + 0xD4), cz = LF(self + 0xD8);
    gm_set_u8(self + 0x390, 1);
    for (int32_t i = 0; i < gm_s32(NUM_PLAYERS); i++) {
        GM_LOOP();
        gptr p = GM_CALLR(0x80065728u, F_GET_PLAYER, 1, (uint32_t)i);
        if (p && fManager_searchBaseByID(GM_PASS, gm_u32(p + 0x2A78)) == self) GM_CALLR(0x80065750u, F_KILL_PLAYER_LINK, 2, p, self);
    }
    SF(f + 20, frsp(px + cx)); SF(f + 24, frsp(py + cy)); SF(f + 28, frsp(pz + cz));
    GM_CALLR(0x800657ACu, F_CREATE_EFFECT, 5, 0x80309F5Cu, 0, f + 20, 0, 0);
    dActor_deleteActor(GM_PASS, self, 1);
    if (noScore) return;
    uint32_t id = (uint32_t)(int32_t)(int8_t)player;
    call_f12(GM_PASS, (int32_t)id < 0 ? F_SCORE_UNKNOWN : F_SCORE_SET, R2F(25592), R2F(25588), 4, gm_ptr(SCORE_MNG), self, 1, id);
}
/* setEatGlupDown(eater): swallowed - the score at the eater, then delete */
uint32_t dActor_setEatGlupDown(GM_CTX, gptr self, gptr eater) {
    FN(0x80065880);
    if (gm_s32(self + 0x37C) != 2) {
        double y = frsp(LF(eater + 0xB0) + R2F(29976));
        SF(f + 8, LF(eater + 0xAC)); SF(f + 16, LF(eater + 0xB4)); SF(f + 12, y);
        gptr n = GM_CALLR(0x800658D8u, gm_u32(gm_u32(eater + 0x60) + 0x6C), 1, eater);
        int32_t pl = gm_s8(n);
        uint32_t pts = gm_u32(self + 0x37C);
        GM_CALLR(0x800658FCu, F_SMALL_SCORE, 4, f + 8, gm_u32(ctx->r[2] - 29992 + 4 * pts), (uint32_t)pl, 0);
        if (pl != -1) {
            GM_CALLR(0x8006591Cu, F_ADD_SCORE, 2, gm_u32(ctx->r[2] - 29984 + 4 * gm_u32(self + 0x37C)), (uint32_t)pl);
            GM_CALLR(0x80065928u, F_EAT_SOUND, 2, gm_ptr(SND_MNG), (uint32_t)pl);
        }
    }
    fBase_deleteRequest(GM_PASS, self);
    return 1;
}
/* slideComboSE(multiplier, shortCombo): the combo sound for this player */
void dActor_slideComboSE(GM_CTX, gptr self, uint32_t mult, uint32_t shortCombo) {
    FN(0x80065B80);
    if (!gm_s8(COMBO_INIT)) {
        static const uint32_t t[9] = { 406, 407, 408, 409, 410, 411, 412, 412, 412 };
        for (int i = 0; i < 9; i++) gm_set_u32(COMBO_TABLE + 4 * i, t[i]);
        gm_set_u8(COMBO_INIT, 1);
    }
    if (gm_u8(self + 0x38D) > (uint32_t)(g_mod_on ? 7 : 3)) return;
    uint32_t m = mult < 9 ? mult : 8;
    if ((int32_t)m >= (shortCombo ? 4 : 7)) GM_CALLR(0x80065C38u, F_COMBO_SOUND, 3, gm_ptr(SND_MNG), mult, shortCombo);
    SF(f + 16, cen_x(GM_PASS, self)); SF(f + 20, cen_y(GM_PASS, self)); SF(f + 24, frsp(LF(self + 0xB4) + LF(self + 0xD8)));
    uint32_t remote = GM_CALLR(0x80065C50u, F_REMOTE_PLAYER, 1, (uint32_t)(int32_t)gm_s8(self + 0x38D));
    gptr obj = gm_ptr(SND_OBJ);
    GM_CALLR(0x80065C64u, F_CVT_SND_POS, 2, f + 8, f + 16);
    GM_CALLR(0x80065C84u, F_START_SOUND, 4, obj, gm_u32(COMBO_TABLE + 4 * m), f + 8, remote);
}

/* HasamareBgCheck(), register-exact (part 48): squeezed between walls / ground and roof, by the
   flags at +842 against the collision flags at +628 (bc +492: isFoot) */
static uint32_t hasamare_r(GM_CTX) {
    GM_FN(0x80065110); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr, res = 0;
#define R(n) ctx->r[n]
#define REC(v) (R(0) = (v), cr_cmp_s(ctx, 0, (int32_t)R(0), 0), R(0) != 0)
    NV_R(31, R(3));
    R(4) = gm_u8(R(3) + 842);
    cr_cmp_s(ctx, 0, (int32_t)R(4), 0);
    if (R(4)) {
        if (REC(R(4) & 1) && REC(gm_u32(R(3) + 628) & 0x15)) res = 1;
        else if (REC(R(4) & 2) && REC(gm_u32(R(3) + 628) & 0x2A)) res = 1;
        else {
            int foot = 0;
            if (REC(R(4) & 8)) { R(3) += 492; GM_CALLV(0x80065178u, 0x80070CB0u, 0); cr_cmp_s(ctx, 0, (int32_t)R(3), 0); foot = R(3) != 0; }
            if (foot) res = 1;
            else if (REC(gm_u8(R(31) + 842) & 4) && REC(gm_u32(R(31) + 628) & 0x3C000000u)) res = 1;
        }
    }
#undef REC
#undef R
    ctx->r[0] = lr;
    return ctx->r[3] = res;
}

/* ================================================================== hle entry points */
#define A(i) GM_ARG(i)
GM_HLE(__ct__13dStageActor_cFv) { GM_RET(dActor_ctor(GM_PASS, A(0))); }                                         /* dActor_c::dActor_c */
GM_HLE(isOutOfView__13dStageActor_cFv) { GM_RET(dActor_drawCullCheck(GM_PASS, A(0))); }                      /* ::ActorDrawCullCheck */
GM_HLE(CalculateDistanceFromActorsNextPosToFurthestPlayer) { GM_RET(dActor_searchNearPlayer(GM_PASS, A(0), A(1))); }   /* ::searchNearPlayer */
GM_HLE(__dt__13dStageActor_cFv) { GM_RET(dActor_dtor(GM_PASS, A(0), (int32_t)A(1))); }                    /* dActor_c::~dActor_c */
GM_HLE(beforeCreate__13dStageActor_cFv) { GM_RET(1); }                                                     /* dActor_c::preCreate */
GM_HLE(afterCreate__13dStageActor_cFi) { fBase_postCreate(GM_PASS, A(0), A(1)); }                          /* ::postCreate */
GM_HLE(beforeDelete__13dStageActor_cFv) { GM_RET(dActor_preDelete(GM_PASS, A(0))); }                       /* ::preDelete */
GM_HLE(afterDelete__13dStageActor_cFi) { fBase_postDelete(GM_PASS, A(0), A(1)); }                          /* ::postDelete */
GM_HLE(beforeExecute__13dStageActor_cFv) { GM_RET(dActor_preExecute(GM_PASS, A(0))); }                     /* ::preExecute */
GM_HLE(afterExecute__13dStageActor_cFi) { dActor_postExecute(GM_PASS, A(0), A(1)); }                       /* ::postExecute */
GM_HLE(AlwaysDrawFlag) { GM_RET(dActor_preDraw(GM_PASS, A(0))); }                                          /* ::preDraw */
GM_HLE_INT(GetExplanationString__13dStageActor_cFv, KIND_STRING, 4) { GM_RET(KIND_STRING); }              /* ::getKindString */
GM_HLE_VOID(bta_sys_set_trace_level, TMP_LAYER, 1) { gm_set_u8(TMP_LAYER, (uint8_t)A(0)); }               /* ::setTmpCtData */
GM_HLE(create__13dStageActor_cF6ActorsUiP7Point3dP6S16VecUc) { GM_FN(0x80064610);                                             /* ::construct (in the scene) */
    gm_set_u8(TMP_LAYER, (uint8_t)A(4));
    GM_RET(dBaseActor_construct(GM_PASS, A(0), A(1), A(2), A(3)));
}
GM_HLE(createChild__13dStageActor_cF6ActorsP13dStageActor_cUiP7Point3dP6S16VecUc) { GM_FN(0x80064680);                       /* ::construct (with a parent) */
    gm_set_u8(TMP_LAYER, (uint8_t)A(5));
    GM_RET(dBaseActor_construct2(GM_PASS, A(0), A(1), A(2), A(3), A(4)));
}
GM_HLE(fn_800646E0) { dActor_setKind(GM_PASS, A(0), A(1)); }                                               /* ::setKind */
GM_HLE_VOID(fn_80064720, SEARCH_FUNC, 4) { gm_set_u32(SEARCH_FUNC, gm_u32(SEARCH_TABLE + 4 * A(0))); }    /* ::setSearchNearPlayerFunc */
GM_HLE_VOID(fn_80064A10, TRGDIR_FUNC, 4) { gm_set_u32(TRGDIR_FUNC, gm_u32(TRGDIR_TABLE + 4 * A(0))); }    /* ::setGetTrgToSrcDirFunc */
GM_HLE(fn_80064B10) { dActor_setLoopFunc(GM_PASS, A(0)); }                                                 /* ::setLoopFunc */
GM_HLE_INT(fn_80064B50, A(0) + 0x349, 1) { GM_RET(dActor_checkAreaNo(GM_PASS, A(0))); }                   /* ::checkAreaNo */
GM_HLE(Delete__13dStageActor_cFUc) { dActor_deleteActor(GM_PASS, A(0), A(1)); }                            /* ::deleteActor */
GM_HLE_VOID(_vf70__13dStageActor_cFv, A(0), 8) {                                                           /* ::getLookatPos */
    ctx->f[3].d = ctx->ps1[3] = LF(A(1) + 0xB0); ctx->f[2].d = ctx->ps1[2] = LF(A(1) + 0xD4);   /* (register-exact) */
    ctx->f[1].d = ctx->ps1[1] = LF(A(1) + 0xAC); ctx->f[0].d = ctx->ps1[0] = LF(A(1) + 0xD0);
    ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[3].d + ctx->f[2].d);
    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d + ctx->f[0].d);
    SF(A(0) + 4, ctx->f[2].d); SF(A(0), ctx->f[0].d);
}
GM_HLE_VOID(eatIn__13dStageActor_cFv, A(0) + 0x370, 0xC) { for (int i = 0; i < 3; i++) SF(A(0) + 0x370 + 4 * i, LF(A(0) + 0xDC + 4 * i)); }   /* ::calcEatInScale start */
GM_HLE_VOID(returnRegularScale__13dStageActor_cFv, A(0) + 0xDC, 0xC) { for (int i = 0; i < 3; i++) SF(A(0) + 0xDC + 4 * i, LF(A(0) + 0x370 + 4 * i)); }   /* ::setAfterEatScale */
GM_HLE_VOID(fn_80065CB0, A(0) + 0x134, 4) { ctx->r[0] = 0; gm_set_u32(A(0) + 0x134, 0); }                                 /* ::clrComboCnt */
GM_HLE(removeMyActivePhysics__13dStageActor_cFv) { GM_CALL(F_CC_REMOVE, 1, A(0) + 0x148); }                /* ::removeCc */
GM_HLE(addMyActivePhysics__13dStageActor_cFv) { GM_CALL(F_CC_ADD, 1, A(0) + 0x148); }                      /* ::reviveCc */

/* part 2. Not in hle_funcs.txt yet (written and reviewed, but no test run reaches them: a looping
   stage, a kill by the level end / a star, Yoshi swallowing): fn_80064880 searchNearPlayerLoop,
   fn_80064A50 getTrgToSrcDirLoop, fn_800656C0 killActor, _vf90 setEatGlupDown. Enable them
   with a run that reaches them (A/B + memory compare). */
GM_HLE(fn_800647A0) { GM_RET(dActor_searchNearPlayerNormal(GM_PASS, A(0), A(1))); }                       /* ::searchNearPlayerNormal */
GM_HLE(fn_80064880) { GM_RET(dActor_searchNearPlayerLoop(GM_PASS, A(0), A(1))); }                         /* ::searchNearPlayerLoop */
GM_HLE_INT(fn_80064A40, KIND_STRING, 4) { cr_fcmp(ctx, 0, GM_FARG(0), GM_FARG(1)); GM_RET(ctx->cr >> 31); }                               /* ::getTrgToSrcDirNormal */
GM_HLE(fn_80064A50) { double t = GM_FARG(0), s = GM_FARG(1); GM_RET(dActor_getTrgToSrcDirLoop(GM_PASS, t, s)); }   /* ::getTrgToSrcDirLoop */
GM_HLE_INT(fn_80065110, A(0) + 0x34A, 1) { GM_RET(hasamare_r(GM_PASS)); }                /* ::HasamareBgCheck */
GM_HLE(outOfZone__13dStageActor_cF7Point3dPfUc) { GM_RET(dActor_areaCullCheck(GM_PASS, A(0), A(1), A(2), A(3))); }   /* ::areaCullCheck */
GM_HLE(checkZoneBoundaries__13dStageActor_cFUi) { GM_RET(dActor_scrOutCheck(GM_PASS, A(0), A(1))); }        /* ::ActorScrOutCheck */
GM_HLE(fn_80065FC0) { GM_RET(dActor_checkCarried(GM_PASS, A(0), A(1))); }                                  /* ::checkCarried */
GM_HLE(fn_800656C0) { dActor_killActor(GM_PASS, A(0), A(1), A(2)); }                                       /* ::killActor */
GM_HLE(_vf90__13dStageActor_cFP13dStageActor_c) { GM_RET(dActor_setEatGlupDown(GM_PASS, A(0), A(1))); }    /* ::setEatGlupDown */
GM_HLE(fn_80065B80) { dActor_slideComboSE(GM_PASS, A(0), A(1), A(2)); }                                    /* ::slideComboSE */

/* ================================================================== part 3: the thin jumps, soft
   lights, the level-clear death effect, Yoshi eating and the splash effects.
   In hle_funcs.txt (reached by the test runs): searchNearPlayer_Main, getTrgToSrcDir_Main,
   changePosAngle, setSoftLight_Enemy / _Map / _MapObj / _Item, waterSplashEffect.
   Written but not in hle_funcs.txt (no test run reaches them): setChangePosAngleFunc,
   setSoftLight_Player / _Boss, allEnemyDeathEffSet (killedByLevelClear), calcSpitOutPos,
   calcEatScaleRate, calcEatInScale, eatMove (Yoshi), yoganSplashEffect, poisonSplashEffect
   (dEn_c has its own lava / poison splashes, so these are for the other actors). */
#define F_SOFT_PLAYER 0x800B3E50u        /* dGameCom::SetSoftLight_Player(mdl, 0) ... */
#define F_SOFT_ENEMY  0x800B4170u
#define F_SOFT_MAP    0x800B3F50u
#define F_SOFT_MAPOBJ 0x800B42B0u
#define F_SOFT_BOSS   0x800B4050u
#define F_GET_RESMDL  0x80168400u        /* m3d::bmdl_c::getResMdl */
#define F_REPLACE_LM  0x80164C50u        /* m3d::replaceLightMapTexture(name, mdl, 0) */
#define F_CMA_CT      0x8025C660u        /* ScnMdl::CopiedMatAccess::CopiedMatAccess(scn, i) */
#define F_CMA_MISC    0x8025C510u        /* ::GetResMatMisc(false) */
#define F_SET_LIGHTSET 0x8023D120u       /* ResMatMisc::SetLightSetIdx */
#define F_MAT_NUM     0x8023B8C0u        /* ResMdl::GetResMatNumEntries */
#define SCNMDL_TYPE   0x802F8FF0u        /* ScnMdl's TypeObj (for G3dObj::DynamicCast) */
#define F_MOUTH_MTX   0x80152520u        /* daYoshi_c::getMouthMtx */
#define F_TONGUE_MTX  0x80152480u        /* daYoshi_c::getTongueTipMtx */
#define F_MTX_TRANS   0x801C0BD0u
#define F_MTX_CONCAT  0x801C0540u
#define F_WATER_DEPTH 0x80076530u        /* dBc_c::checkWaterDepth(x, y, layer, line, 0) */
#define F_SPLASH_EFF  0x800929F0u        /* dEffActorMng_c::createWaterSplashEff */
#define F_SND_MAP     0x80198C30u        /* SndObjctCmnMap::startSound */
#define F_WATER_WAVE  0x80078410u        /* dBg_c::setWaterInWave(x, y, kind) */
#define EFF_ACTOR_MNG (SDA - 0x5798)
#define SND_OBJ_MAP   (SDA - 0x5920)
#define BG            (SDA - 0x58B0)

/* setSoftLight_Item(mdl): the item light maps, then light set 6 on every material */
void dActor_setSoftLightItem(GM_CTX, gptr mdl) {
    FN(0x80064C10);
    gm_set_u32(f + 16, GM_CALLR(0x80064C2Cu, F_GET_RESMDL, 1, mdl));
    GM_CALLR(0x80064C40u, F_REPLACE_LM, 3, SDA - 32112, mdl, 0);
    GM_CALLR(0x80064C50u, F_REPLACE_LM, 3, SDA - 32104, mdl, 0);
    for (uint32_t i = 0; i < GM_CALLR(0x80064CE8u, F_MAT_NUM, 1, f + 16); i++) {
        GM_LOOP();
        gptr scn = gm_u32(mdl + 4), cast = 0;
        if (scn) {
            gm_set_u32(f + 8, SCNMDL_TYPE);
            if (GM_CALLR(0x80064C8Cu, gm_u32(gm_u32(scn) + 8), 2, scn, f + 8)) cast = scn;
        }
        GM_CALLR(0x80064CB8u, F_CMA_CT, 3, f + 20, cast, i);
        uint32_t misc = GM_CALLR(0x80064CC4u, F_CMA_MISC, 2, f + 20, 0);
        gm_set_u32(f + 12, misc);
        if (misc) GM_CALLR(0x80064CDCu, F_SET_LIGHTSET, 2, f + 12, 6);
    }
}
/* allEnemyDeathEffSet (killedByLevelClear): the burst effect 4 above the centre */
uint32_t dActor_allEnemyDeathEffSet(GM_CTX, gptr self) {
    FN(0x80065660);
    dBaseActor_getCenterPos(GM_PASS, f + 8, self);
    SF(f + 12, frsp(LF(f + 12) + R2F(29996)));
    uint32_t r = GM_CALLR(0x800656A4u, F_CREATE_EFFECT, 5, 0x80309F5Cu, 0, f + 8, 0, 0);
    return r;
}
/* calcSpitOutPos(yoshi): at Yoshi's mouth, moved by (10, -7, 0) */
void dActor_calcSpitOutPos(GM_CTX, gptr self, gptr yoshi) {
    FN(0x80065970);
    GM_CALLR(0x80065990u, F_MOUTH_MTX, 2, yoshi, f + 80);
    ctx->f[1].d = ctx->ps1[1] = R2F(29972); ctx->f[2].d = ctx->ps1[2] = R2F(29968); ctx->f[3].d = ctx->ps1[3] = R2F(30036);
    GM_CALLR(0x800659A4u, F_MTX_TRANS, 1, f + 32);
    GM_CALLR(0x800659B4u, F_MTX_CONCAT, 3, f + 80, f + 32, f + 80);
    SF(self + 0xAC, LF(f + 92)); SF(self + 0xB0, LF(f + 108));
}
/* calcEatScaleRate(yoshi): 1, or Yoshi's eat timer / 1.25 while it is 0..1 */
double dActor_calcEatScaleRate(GM_CTX, gptr yoshi) {
    int32_t t = gm_s32(yoshi + 0x1530);
    if (t > 1) return R2F(30040);
    return frsp(frsp((double)t) / R2F(29964));
}
/* calcEatInScale(yoshi): the scale before eating times the (virtual) rate if below 1 */
void dActor_calcEatInScale(GM_CTX, gptr self, gptr yoshi) {
    FN(0x80065A40);
    for (int i = 0; i < 3; i++) SF(self + 0xDC + 4 * i, LF(self + 0x370 + 4 * i));
    GM_CALLR(0x80065A7Cu, gm_u32(gm_u32(self + 0x60) + 0xA8), 2, self, yoshi);
    double r = ctx->f[1].d;
    if (r < R2F(30040))
        for (int i = 0; i < 3; i++) SF(self + 0xDC + 4 * i, frsp(LF(self + 0xDC + 4 * i) * r));
}
/* eatMove(yoshi): follow the tongue tip */
void dActor_eatMove(GM_CTX, gptr self, gptr yoshi) {
    FN(0x80065AC0);
    GM_CALLR(0x80065AE0u, F_TONGUE_MTX, 2, yoshi, f + 32);
    SF(self + 0xAC, LF(f + 44));
    SF(self + 0xB0, frsp(LF(f + 60) - LF(self + 0xD4)));
}
/* water / lava / poison splash at pos (z 6500): the effect, the sound, the wave */
void dActor_splash(GM_CTX, gptr self, gptr pos, double size, int kind) {
    FN((kind == 0 ? 0x80065CC0u : kind == 1 ? 0x80065DC0u : 0x80065EC0u));
    static const uint32_t se[3] = { 642, 644, 643 };
    double x = LF(pos), y = LF(pos + 4);
    SF(f + 40, x); SF(f + 44, y); SF(f + 48, R2F(29952));
    uint32_t layer = gm_u8(self + 0x38F), info;
    if (kind == 0) {
        ctx->f[1].d = ctx->ps1[1] = x; ctx->f[2].d = ctx->ps1[2] = y;
        int32_t depth = (int32_t)GM_CALL(F_WATER_DEPTH, 3, layer, gm_u8(self + 0x2D1), 0);
        info = (depth < 3) | layer << 16;
        layer = gm_u8(self + 0x38F);
    } else info = (kind == 1 ? 4 : 6) | layer << 16;
    SF(f + 28, size); SF(f + 32, size); SF(f + 36, size);
    SF(f + 16, size); SF(f + 20, size); SF(f + 24, size);
    GM_CALL(F_SPLASH_EFF, 5, gm_u32(EFF_ACTOR_MNG), f + 40, info, 0xFFFFFFFFu, f + 16);
    gptr obj = gm_u32(SND_OBJ_MAP);
    GM_CALL(F_CVT_SND_POS, 2, f + 8, kind == 2 ? pos : f + 40);
    GM_CALL(F_SND_MAP, 4, obj, se[kind], f + 8, 0);
    static const uint8_t wave[3][2] = { { 6, 6 }, { 14, 16 }, { 21, 23 } };     /* [kind][size < 1] */
    ctx->f[1].d = ctx->ps1[1] = LF(pos); ctx->f[2].d = ctx->ps1[2] = LF(pos + 4);
    GM_CALL(F_WATER_WAVE, 2, gm_u32(BG), wave[kind][kind && size < R2F(30040)]);
}

GM_HLE(fn_80064790) { GM_RET(GM_CALL(gm_u32(SEARCH_FUNC), 2, A(0), A(1))); }                               /* ::searchNearPlayer_Main */
GM_HLE(fn_80064A30) { GM_RET(GM_CALL(gm_u32(TRGDIR_FUNC), 0)); }                                           /* ::getTrgToSrcDir_Main (f1, f2) */
GM_HLE(fn_80064AF0) { GM_RET(GM_CALL(gm_u32(SDA - 0x5458), 3, A(0), A(1), A(2))); }                        /* ::changePosAngle */
GM_HLE(fn_80064B00) { GM_RET(GM_CALL(F_SET_CHANGE_POS, 1, A(0))); }                                        /* ::setChangePosAngleFunc */
GM_HLE(fn_80064BC0) { GM_RET(GM_CALL(F_SOFT_PLAYER, 2, A(0), 0)); }                                        /* ::setSoftLight_Player */
GM_HLE(sub_80064BD0) { GM_RET(GM_CALL(F_SOFT_ENEMY, 2, A(0), 0)); }                                        /* ::setSoftLight_Enemy */
GM_HLE(fn_80064BE0) { GM_RET(GM_CALL(F_SOFT_MAP, 2, A(0), 0)); }                                           /* ::setSoftLight_Map */
GM_HLE(sub_80064BF0__Q23m3d5mdl_cFv) { GM_RET(GM_CALL(F_SOFT_MAPOBJ, 2, A(0), 0)); }                       /* ::setSoftLight_MapObj */
GM_HLE(fn_80064C00) { GM_RET(GM_CALL(F_SOFT_BOSS, 2, A(0), 0)); }                                          /* ::setSoftLight_Boss */
GM_HLE(oneSetupType__Q23m3d5mdl_cFv) { dActor_setSoftLightItem(GM_PASS, A(0)); }                           /* ::setSoftLight_Item */
GM_HLE(killedByLevelClear__13dStageActor_cFv) { GM_RET(dActor_allEnemyDeathEffSet(GM_PASS, A(0))); }       /* ::allEnemyDeathEffSet */
GM_HLE(_vfA4__13dStageActor_cFPv) { dActor_calcSpitOutPos(GM_PASS, A(0), A(1)); }                          /* ::calcSpitOutPos */
GM_HLE(_vfA8__13dStageActor_cFPv) { GM_FRET(dActor_calcEatScaleRate(GM_PASS, A(1))); }                     /* ::calcEatScaleRate */
GM_HLE(_vfAC__13dStageActor_cFPv) { dActor_calcEatInScale(GM_PASS, A(0), A(1)); }                          /* ::calcEatInScale */
GM_HLE(_vf94__13dStageActor_cFPv) { dActor_eatMove(GM_PASS, A(0), A(1)); }                                 /* ::eatMove */
GM_HLE(_vfC8__13dStageActor_cFP7Point2df) { dActor_splash(GM_PASS, A(0), A(1), GM_FARG(0), 0); }           /* ::waterSplashEffect */
GM_HLE(_vfCC__13dStageActor_cFP7Point2df) { dActor_splash(GM_PASS, A(0), A(1), GM_FARG(0), 1); }           /* ::yoganSplashEffect */
GM_HLE(_vfD0__13dStageActor_cFP7Point2df) { dActor_splash(GM_PASS, A(0), A(1), GM_FARG(0), 2); }           /* ::poisonSplashEffect */
