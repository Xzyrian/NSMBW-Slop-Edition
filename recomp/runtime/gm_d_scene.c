/* gm_d_scene.c - the frame and the scenes: dSys_c (the per-frame driver execute(): begin the
 * frame, draw the graph / fader / HOME menu / reset / disc-error screens, run the managers, the
 * scene change and fManager's main loop, end the frame; its render / frame helpers, setBlack, the
 * clear colour and frame rate, the effect heaps, the dylink init phases) and dScene_c (the scene
 * base: ctor / dtor, the before / after create / delete / execute / draw steps with the fades, the
 * start / reset scenes, createNextScene, the fade lengths). Track B (gm.h, docs/DECOMP.md),
 * instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_system.cpp, d_scene.cpp) and checked
 * against the recompiled USA rev 2 code (0x800E45F0-0x800E4E10 and 0x800E4E40, 0x800E19B0-
 * 0x800E1F7C). dSys_c::create and the effect / font / message manager phases stay recompiled (once
 * at boot); dScene_c::setNextScene is the runtime's already (rt_lyt.c: DoSceneChange). Written
 * register-exact (R(n); the PowerPC registers as the variables).
 *
 * SDA (r13 -): 22004 EGG::TSystem::sConfiguration (+76 the display: +4 its vtable, +8 frame rate,
 * +9 screen state flags, +20 the clear colour), 18488 EGG::BaseSystem::mConfigData, 21480
 * dDvdErr_c::m_pInstance, 22312 dGraph_c::ms_Instance, 22320 dGameKey_c::m_instance, 21984 the
 * dylink init phase (sPhase_c), 21268 / 21272 cCounter_c::m_exeFrame / m_gameFrame; dScene_c:
 * 28496 / 28494 / 28492 the next / now / old scene (u16, 750 = none), 28490 m_otherSceneFlg,
 * 28488 / 28486 the fade-in / fade-out length, 28484 m_isAutoFadeIn, 22072 mPara, 21056 the
 * current fader (mFader_c::mFader: +16 getStatus - 0 opaque, 1 hidden). */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int rec0(ppc_context *ctx, uint32_t v) { cr_cmp_s(ctx, 0, (int32_t)v, 0); return v != 0; }   /* a record form's CR0 */
static inline uint32_t cntlzw32(uint32_t v) { return v ? (uint32_t)__builtin_clz(v) : 32u; }
static inline uint32_t sbool(ppc_context *ctx) { R(0) = (uint32_t)-(int32_t)R(3); R(0) |= R(3); return R(3) = R(0) >> 31; }   /* neg / or / srwi */
/* a virtual call through r3's vtable (r12 / CTR as the PowerPC code leaves them) */
static inline void vcall(GM_CTX, uint32_t ra, uint32_t slot) {
    R(12) = gm_u32(R(3)); R(12) = gm_u32(R(12) + slot); ctx->ctr = R(12); GM_CALLV(ra, R(12), 0);
}

#define SDA_CONFIG     22004
#define SDA_BASECONFIG 18488
#define SDA_DVDERR     21480
#define SDA_GRAPH      22312
#define SDA_GAMEKEY    22320
#define SDA_DYL_PHASE  21984
#define SDA_EXE_FRAME  21268
#define SDA_GAME_FRAME 21272
#define SDA_NEXT   28496
#define SDA_NOW    28494
#define SDA_OLD    28492
#define SDA_OTHER  28490
#define SDA_FADEIN 28488
#define SDA_FADEOUT 28486
#define SDA_AUTOFADE 28484
#define SDA_PARA   22072
#define SDA_FADER  21056
#define NO_SCENE   750
#define VT_SCENE   (0x80320000u - 20544u)

#define F_IS_DVD_ERR   0x80107850u
#define F_HBM_INST     0x80109340u
#define F_RESET_INST   0x80107F10u
#define SDA(o) (R(13) - (o))

/* ================================================================== dSys_c */
/* the display (r3) of the system's configuration */
static inline void display(GM_CTX) { R(3) = gm_u32(SDA(SDA_CONFIG)); R(3) = gm_u32(R(3) + 76); }
static void sys_begin_render(GM_CTX) {                      /* mpDisplay->beginRender() (a tail call) */
    display(GM_PASS);
    R(12) = gm_u32(R(3) + 4); R(12) = gm_u32(R(12) + 12); ctx->ctr = R(12);
    GM_TAIL(R(12), 0);
}
static void sys_end_render(GM_CTX) {                        /* (three static guards), endRender() */
    for (uint32_t o = 21988; o >= 21986; o--) {
        R(0) = (uint32_t)(int32_t)(int8_t)gm_u8(SDA(o));
        if (!rec0(ctx, R(0))) { R(0) = 1; gm_set_u8(SDA(o), 1); }
    }
    display(GM_PASS);
    R(12) = gm_u32(R(3) + 4); R(12) = gm_u32(R(12) + 16); ctx->ctr = R(12);
    GM_TAIL(R(12), 0);
}
/* beginFrame() / endFrame(): the display's, then the configuration's onBeginFrame / onEndFrame */
static void sys_frame(GM_CTX, int end) {
    uint32_t a = end ? 0x800E4740u : 0x800E46E0u;   /* FNADDR */
    GM_FN(a); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    display(GM_PASS);
    R(12) = gm_u32(R(3) + 4); R(12) = gm_u32(R(12) + (end ? 20 : 8)); ctx->ctr = R(12);
    GM_CALLV(a + 0x24, R(12), 0);
    R(3) = gm_u32(SDA(SDA_CONFIG));
    vcall(GM_PASS, a + 0x38, end ? 40 : 36);
    R(0) = lr;
}
static void sys_set_black(GM_CTX) {
    GM_FN(0x800E47A0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3);
    R(3) = gm_u32(SDA(SDA_BASECONFIG));
    R(4) = gm_u32(SDA(SDA_CONFIG));
    R(12) = gm_u32(R(3));
    R(31) = gm_u32(R(4) + 76);
    R(12) = gm_u32(R(12) + 8); ctx->ctr = R(12);
    GM_CALLV(0x800E47D4u, R(12), 0);                         /* getVideo() */
    R(0) = gm_u8(R(3) + 4) & 1u;
    if (cmpu(ctx, R(30), R(0)) != 0 && !rec0(ctx, R(0) = gm_u8(R(31) + 9) & 1u)) {
        R(0) = gm_u8(R(31) + 9); R(3) = 1; R(0) |= 1; gm_set_u8(R(31) + 9, (uint8_t)R(0));
    } else R(3) = 0;
    R(0) = lr;
}
static void sys_effect_heaps(GM_CTX) {
    GM_FN(0x800E45F0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(5) = 0x802F2FD8u; R(6) = 32; R(0) = R(3); R(3) = 0x100000u; R(31) = R(4); R(4) = R(0); R(7) = 0;
    GM_CALLV(0x800E4624u, 0x8016E630u, 0);                   /* mHeap::createFrmHeap */
    gm_set_u32(SDA(22016), R(3));
    R(5) = 0x802F2FE8u; R(4) = R(31); R(3) = 0x280000u; R(6) = 32; R(7) = 4;
    GM_CALLV(0x800E4644u, 0x8016E630u, 0);
    gm_set_u32(SDA(22012), R(3));
    R(0) = lr;
}
static void sys_set_clear(GM_CTX) {                         /* (a frame without saves: the colour through it) */
    GM_FN(0x800E4850);
    gptr f = gm_frame_sp;
    R(4) = gm_u32(SDA(SDA_CONFIG)); R(4) = gm_u32(R(4) + 76);
    if (cmps(ctx, (int32_t)R(4), 0) != 0) {
        R(0) = gm_u32(R(3)); gm_set_u32(f + 8, R(0));
        for (int i = 0; i < 4; i++) { R(0) = gm_u8(f + 8 + i); gm_set_u8(R(4) + 20 + i, (uint8_t)R(0)); }
    }
}
/* the dylink init phases (sPhase_c methods): InitAsync, InitAsyncIsDone, dBase_c::initLoader */
static void sys_phase(GM_CTX, int k) {
    static const uint32_t fn[3] = { 0x800E4DB0u, 0x800E4DE0u, 0x800E4E10u };   /* FNADDR */
    static const uint32_t callee[3] = { 0x8008F760u, 0x8008F7B0u, 0x8006C690u };
    GM_FN(fn[k]); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(fn[k] + 0x10, callee[k], 0);
    if (k == 1) sbool(ctx); else R(3) = 1;
    R(0) = lr;
}
/* execute(): one frame */
static void sys_execute(GM_CTX) {
    GM_FN(0x800E4E40); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(3) = gm_u32(SDA(SDA_DVDERR));
    GM_CALLV(0x800E4E5Cu, F_IS_DVD_ERR, 0);
    R(30) = R(3);                                            /* the disc error before */
    GM_CALLV(0x800E4E64u, F_HBM_INST, 0);
    R(3) = gm_u32(R(3) + 464); R(0) = R(3) - 2; R(0) = cntlzw32(R(0)); R(31) = R(0) >> 5;   /* in the HOME menu */
    GM_CALLV(0x800E4E78u, 0x800E46E0u, 0);                   /* beginFrame() */
    GM_CALLV(0x800E4E7Cu, 0x80164D50u, 0);                   /* m3d::calcMaterial */
    GM_CALLV(0x800E4E80u, 0x800D0610u, 0);                   /* dPad::beginPad_BR */
    GM_CALLV(0x800E4E84u, 0x80164EC0u, 0);                   /* m3d::reset */
    GM_CALLV(0x800E4E88u, 0x800E4660u, 0);                   /* beginRender() */
    if (cmps(ctx, (int32_t)R(31), 0) == 0 && cmps(ctx, (int32_t)R(30), 0) == 0) {
        R(3) = gm_u32(SDA(SDA_GRAPH));
        GM_CALLV(0x800E4EA0u, 0x800B64E0u, 0);               /* dGraph_c::painter */
        GM_CALLV(0x800E4EA4u, 0x800B0B20u, 0);               /* dFader_c::draw */
    }
    GM_CALLV(0x800E4EA8u, F_HBM_INST, 0);
    GM_CALLV(0x800E4EACu, 0x80109730u, 0);                   /* dHbm::Manage_c::DrawMenu */
    GM_CALLV(0x800E4EB0u, F_RESET_INST, 0);
    GM_CALLV(0x800E4EB4u, 0x80108130u, 0);                   /* dReset::Manage_c::Draw */
    R(3) = gm_u32(SDA(SDA_DVDERR));
    GM_CALLV(0x800E4EBCu, 0x80107460u, 0);                   /* dDvdErr_c::draw */
    GM_CALLV(0x800E4EC0u, F_HBM_INST, 0);
    GM_CALLV(0x800E4EC4u, 0x801097F0u, 0);                   /* DrawIcon */
    GM_CALLV(0x800E4EC8u, 0x800E4680u, 0);                   /* endRender() */
    if (cmps(ctx, (int32_t)R(31), 0) == 0) {
        GM_CALLV(0x800E4ED4u, 0x80163170u, 0);               /* m2d::reset */
        GM_CALLV(0x800E4ED8u, 0x80164E70u, 0);               /* m3d::clear */
    }
    R(3) = gm_u32(SDA(SDA_DVDERR));
    GM_CALLV(0x800E4EE0u, 0x801076B0u, 0);                   /* dDvdErr_c::execute */
    R(3) = gm_u32(SDA(SDA_DVDERR));
    GM_CALLV(0x800E4EE8u, F_IS_DVD_ERR, 0);
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(3);                                            /* the disc error now */
    if (c != 0 && cmps(ctx, (int32_t)R(30), 0) == 0) { R(3) = 1; GM_CALLV(0x800E4F04u, 0x801BE2F0u, 0); }   /* VIEnableDimming */
    GM_CALLV(0x800E4F08u, F_HBM_INST, 0);
    GM_CALLV(0x800E4F0Cu, 0x80109660u, 0);                   /* dHbm::Manage_c::Calculate */
    GM_CALLV(0x800E4F10u, F_RESET_INST, 0);
    GM_CALLV(0x800E4F14u, 0x801080F0u, 0);                   /* dReset::Manage_c::Calculate */
    GM_CALLV(0x800E4F18u, F_HBM_INST, 0);
    R(3) = gm_u32(R(3) + 464); R(0) = R(3) - 2; R(0) = cntlzw32(R(0)); R(30) = R(0) >> 5;
    GM_CALLV(0x800E4F2Cu, 0x800DC480u, 0);                   /* dRemoconMng_c::execute */
    GM_CALLV(0x800E4F30u, 0x80102140u, 0);                   /* dScStage_c::play */
    R(3) = gm_u32(SDA(SDA_GAMEKEY));
    GM_CALLV(0x800E4F38u, 0x800B5AB0u, 0);                   /* dGameKey_c::read */
    GM_CALLV(0x800E4F3Cu, 0x8006A130u, 0);                   /* dAudio::updateBgmInfo */
    if (cmps(ctx, (int32_t)R(30), 0) == 0 && cmps(ctx, (int32_t)R(31), 0) == 0) {
        R(3) = SDA(SDA_DYL_PHASE); R(4) = 0;
        GM_CALLV(0x800E4F58u, 0x8015F620u, 0);               /* myDylinkInitPhase.callMethod */
        if (cmps(ctx, (int32_t)R(3), 2) == 0) {
            GM_CALLV(0x800E4F64u, 0x800E1DE0u, 0);           /* dScene_c::createNextScene */
            GM_CALLV(0x800E4F68u, 0x80162E10u, 0);           /* fManager_c::mainLoop */
            R(3) = gm_u32(SDA(SDA_EXE_FRAME)); R(0) = R(3) + 1; gm_set_u32(SDA(SDA_EXE_FRAME), R(0));
        }
        GM_CALLV(0x800E4F78u, 0x800B0B00u, 0);               /* dFader_c::calc */
    }
    GM_CALLV(0x800E4F7Cu, 0x800E4820u, 0);                   /* calcAudio() */
    GM_CALLV(0x800E4F80u, 0x800D08A0u, 0);                   /* dPad::endPad_BR */
    GM_CALLV(0x800E4F84u, 0x800E4740u, 0);                   /* endFrame() */
    R(3) = gm_u32(SDA(SDA_GAME_FRAME)); R(0) = R(3) + 1; gm_set_u32(SDA(SDA_GAME_FRAME), R(0));
    R(0) = lr;
}

/* ================================================================== dScene_c */
static void sc_ctor(GM_CTX) {
    GM_FN(0x800E19B0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(30) = R(3);
    GM_CALLV(0x800E19CCu, 0x8006C420u, 0);                   /* dBase_c::dBase_c */
    R(0) = gm_u8(R(30) + 15); R(3) = VT_SCENE; R(31) = 0; R(0) |= 5;
    gm_set_u32(R(30) + 96, R(3)); gm_set_u8(R(30) + 15, (uint8_t)R(0));   /* ROOT_DISABLE_EXECUTE / _DRAW */
    gm_set_u32(R(30) + 112, 0);                              /* mpPhase */
    gm_set_u8(SDA(22407), 0);                                /* EffectManager_c::m_firstCalc */
    GM_CALLV(0x800E19F4u, 0x800B3A20u, 0);                   /* dGameCom::clearGameStop */
    gm_set_u8(SDA(22920), 0); R(3) = R(30);                  /* dActor_c::mExecStopReq / mDrawStopReq / mExecStop / mDrawStop */
    gm_set_u8(SDA(22919), 0); gm_set_u8(SDA(22918), 0); gm_set_u8(SDA(22917), 0);
    R(0) = lr;
}
static void sc_dtor(GM_CTX) {
    GM_FN(0x800E1A20); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(3), 0);
    R(31) = R(4); R(30) = R(3);
    if (c != 0) {
        R(4) = VT_SCENE; gm_set_u32(R(3) + 96, R(4));
        R(3) = gm_u32(SDA(21408));                           /* dWarningManager_c::m_WarningForbid */
        if (cmps(ctx, (int32_t)R(3), 0) > 0) { R(0) = R(3) - 1; gm_set_u32(SDA(21408), R(0)); }
        GM_CALLV(0x800E1A68u, 0x80069C50u, 0);               /* dAudio::deleteSndObjctCmn */
        R(3) = R(30); R(4) = 0;
        GM_CALLV(0x800E1A74u, 0x8006C490u, 0);               /* ~dBase_c */
        if (cmps(ctx, (int32_t)R(31), 0) > 0) { R(3) = R(30); GM_CALLV(0x800E1A84u, 0x80162920u, 0); }   /* delete */
    }
    R(3) = R(30);
    R(0) = lr;
}
static void sc_before_create(GM_CTX) {
    GM_FN(0x800E1AA0); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(0x800E1AB0u, 0x8006C540u, 0);                   /* dBase_c::preCreate */
    if (cmps(ctx, (int32_t)R(3), 0) == 0) R(3) = 0;
    else { R(0) = 1; gm_set_u8(SDA(SDA_AUTOFADE), 1); R(3) = 1; }
    R(0) = lr;
}
/* postCreate / postDelete / postExecute: the reset manager on success, then dBase_c's */
static void sc_after(GM_CTX, int which) {
    static const uint32_t fn[3] = { 0x800E1AE0u, 0x800E1B80u, 0x800E1D20u };   /* FNADDR */
    uint32_t a = fn[which];
    GM_FN(a); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    int c = cmps(ctx, (int32_t)R(4), which == 2 ? 0 : 2);
    R(31) = R(4); R(30) = R(3);
    if (which == 0 && c == 0) {
        GM_CALLV(a + 0x28, F_RESET_INST, 0);
        GM_CALLV(a + 0x2C, 0x80108230u, 0);                  /* SetSoftResetFinish */
        GM_CALLV(a + 0x30, 0x80069820u, 0);                  /* dAudio::createSndObjctCmn */
        R(4) = R(30); R(3) = 749; R(5) = 0; R(6) = 0;
        GM_CALLV(a + 0x44, 0x80162B00u, 0);                  /* fBase_c::createChild(LASTACTOR, this, 0, OTHER) */
    } else if (which == 1 && c == 0) {
        R(0) = 0; gm_set_u8(SDA(SDA_OTHER), 0);
        GM_CALLV(a + 0x30, F_RESET_INST, 0);
        GM_CALLV(a + 0x34, 0x801082D0u, 0);                  /* PostDeleteScene */
    } else if (which == 2 && c != 0) {
        GM_CALLV(a + 0x28, F_RESET_INST, 0);
        GM_CALLV(a + 0x2C, 0x80108260u, 0);                  /* SetSoftResetScene */
    }
    R(3) = R(30); R(4) = R(31);
    static const uint32_t ra[3] = { 0x800E1B30u, 0x800E1BC0u, 0x800E1D58u }, base_fn[3] = { 0x8006C570u, 0x8006C5B0u, 0x8006C600u };
    GM_CALLV(ra[which], base_fn[which], 0);
    R(0) = lr;
}
/* preDelete / preDraw: dBase_c's, as a bool */
static void sc_before_bool(GM_CTX, int draw) {
    uint32_t a = draw ? 0x800E1D70u : 0x800E1B50u;   /* FNADDR */
    GM_FN(a); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(a + 0x10, draw ? 0x8006C610u : 0x8006C580u, 0);
    sbool(ctx);
    R(0) = lr;
}
/* the current fader's status (vtable +16) */
static inline void fader_status(GM_CTX, uint32_t ra) { R(3) = gm_u32(SDA(SDA_FADER)); vcall(GM_PASS, ra, 16); }
static void sc_before_execute(GM_CTX) {
    GM_FN(0x800E1BE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    GM_CALLV(0x800E1BF8u, 0x8006C5C0u, 0);                   /* dBase_c::preExecute */
    if (cmps(ctx, (int32_t)R(3), 0) == 0) { R(3) = 0; goto out; }
    R(3) = gm_u32(R(31) + 112);
    if (cmps(ctx, (int32_t)R(3), 0) != 0) {                  /* mpPhase->callMethod(this) */
        R(4) = R(31);
        GM_CALLV(0x800E1C1Cu, 0x8015F620u, 0);
        if (cmps(ctx, (int32_t)R(3), 2) != 0) { R(3) = 0; goto out; }
    }
    R(0) = gm_u16(SDA(SDA_NEXT));
    if (cmpu(ctx, R(0), NO_SCENE) != 0) {                    /* a next scene: fade out, then delete */
        fader_status(GM_PASS, 0x800E1C4Cu);
        R(0) = R(3) - 1; R(0) = cntlzw32(R(0)) >> 5;
        if (rec0(ctx, R(0))) { R(3) = gm_u16(SDA(SDA_FADEOUT)); GM_CALLV(0x800E1C64u, 0x800B0A90u, 0); }   /* startFadeOut */
        else {
            fader_status(GM_PASS, 0x800E1C7Cu);
            R(0) = cntlzw32(R(3)) >> 5;
            if (rec0(ctx, R(0))) { R(3) = R(31); GM_CALLV(0x800E1C90u, 0x80162510u, 0); }   /* deleteRequest */
        }
        R(3) = 0; goto out;
    }
    R(0) = gm_u8(R(31) + 15) & 1u;
    if (rec0(ctx, R(0))) {                                   /* ROOT_DISABLE_EXECUTE: until the children are created */
        R(3) = R(31);
        GM_CALLV(0x800E1CACu, 0x80162A20u, 0);
        if (cmps(ctx, (int32_t)R(3), 0) == 0) {
            R(0) = gm_u8(R(31) + 15) & 0xFEu; R(0) &= 0xFBu; rec0(ctx, R(0));
            gm_set_u8(R(31) + 15, (uint8_t)R(0));
        }
        R(3) = 0; goto out;
    }
    fader_status(GM_PASS, 0x800E1CE0u);
    R(0) = cntlzw32(R(3)) >> 5;
    if (rec0(ctx, R(0))) {
        R(0) = gm_u8(SDA(SDA_AUTOFADE));
        if (cmps(ctx, (int32_t)R(0), 0) != 0) {
            R(3) = gm_u16(SDA(SDA_FADEIN)); GM_CALLV(0x800E1D00u, 0x800B0A20u, 0);   /* startFadeIn */
            R(3) = gm_u16(SDA(SDA_NOW));    GM_CALLV(0x800E1D08u, 0x8006A2B0u, 0);   /* dAudio::requestStartScene */
        }
    }
    R(3) = 1;
out:
    R(0) = lr;
}
static void sc_create_next(GM_CTX) {
    GM_FN(0x800E1DE0); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(0) = gm_u8(SDA(SDA_OTHER));
    if (cmps(ctx, (int32_t)R(0), 0) != 0) R(3) = 0;
    else if (R(3) = gm_u16(SDA(SDA_NEXT)), cmpu(ctx, R(3), NO_SCENE) == 0) R(3) = 0;
    else {
        R(4) = gm_u32(SDA(SDA_PARA)); R(5) = 1;
        GM_CALLV(0x800E1E18u, 0x8006C6C0u, 0);               /* createRoot(next, mPara, SCENE) */
        if (cmps(ctx, (int32_t)R(3), 0) == 0) R(3) = 0;
        else {
            R(6) = gm_u16(SDA(SDA_NOW)); R(0) = 1; R(5) = gm_u16(SDA(SDA_NEXT)); R(4) = NO_SCENE;
            gm_set_u16(SDA(SDA_OLD), (uint16_t)R(6)); gm_set_u16(SDA(SDA_NOW), (uint16_t)R(5));
            gm_set_u16(SDA(SDA_NEXT), NO_SCENE); gm_set_u8(SDA(SDA_OTHER), 1);
        }
    }
    R(0) = lr;
}
static void sc_set_start(GM_CTX) {                          /* BOOT everywhere, then dAudio::setNextScene (a tail call) */
    R(0) = 0;
    gm_set_u16(SDA(SDA_NEXT), 0); R(3) = 0; R(4) = 0;
    gm_set_u16(SDA(SDA_NOW), 0); gm_set_u16(SDA(SDA_OLD), 0); gm_set_u8(SDA(SDA_OTHER), 0);
    GM_TAIL(0x8006A620u, 0);
}

/* ================================================================== entry points */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
E(fn_800E45F0) { sys_effect_heaps(GM_PASS); }                                  /* dSystem::createEffectManagerHeap */
E(fn_800E4660) { sys_begin_render(GM_PASS); }                                  /* dSys_c::beginRender */
E(fn_800E4680) { sys_end_render(GM_PASS); }                                    /* ::endRender */
E(fn_800E46E0) { sys_frame(GM_PASS, 0); }                                      /* ::beginFrame */
E(fn_800E4740) { sys_frame(GM_PASS, 1); }                                      /* ::endFrame */
E(fn_800E47A0) { sys_set_black(GM_PASS); }                                     /* ::setBlack */
E(fn_800E4820) { GM_TAIL(0x8006A320u, 0); }                                    /* ::calcAudio (dAudio::execute) */
E(fn_800E4830) { R(4) = gm_u32(SDA(SDA_CONFIG)); R(4) = gm_u32(R(4) + 76);     /* ::setFrameRate */
                 if (cmps(ctx, (int32_t)R(4), 0) != 0) gm_set_u8(R(4) + 8, (uint8_t)R(3)); }
E(fn_800E4850) { sys_set_clear(GM_PASS); }                                     /* ::setClearColor */
E(fn_800E48A0) { R(4) = gm_u32(SDA(SDA_CONFIG)); R(4) = gm_u32(R(4) + 76);     /* ::getClearColor (into r3) */
                 if (cmps(ctx, (int32_t)R(4), 0) != 0) { R(0) = gm_u32(R(4) + 20); gm_set_u32(R(3), R(0)); }
                 else { R(0) = 255; gm_set_u32(R(3), 255); } }
E(fn_800E4DB0) { sys_phase(GM_PASS, 0); }                                      /* myDylinkInitPhase_0 */
E(fn_800E4DE0) { sys_phase(GM_PASS, 1); }                                      /* myDylinkInitPhase_1 */
E(fn_800E4E10) { sys_phase(GM_PASS, 2); }                                      /* myDylinkInitPhase_4 */
E(fn_800E4E40) { sys_execute(GM_PASS); }                                       /* dSys_c::execute */

E(__ct__8dScene_cFv)       { sc_ctor(GM_PASS); }
E(__dt__8dScene_cFv)       { sc_dtor(GM_PASS); }
E(beforeCreate__8dScene_cFv) { sc_before_create(GM_PASS); }                    /* ::preCreate */
E(afterCreate__8dScene_cFi)  { sc_after(GM_PASS, 0); }                         /* ::postCreate */
E(beforeDelete__8dScene_cFv) { sc_before_bool(GM_PASS, 0); }                   /* ::preDelete */
E(afterDelete__8dScene_cFi)  { sc_after(GM_PASS, 1); }                         /* ::postDelete */
E(beforeExecute__8dScene_cFv) { sc_before_execute(GM_PASS); }                  /* ::preExecute */
E(afterExecute__8dScene_cFi) { sc_after(GM_PASS, 2); }                         /* ::postExecute */
E(beforeDraw__8dScene_cFv)   { sc_before_bool(GM_PASS, 1); }                   /* ::preDraw */
E(afterDraw__8dScene_cFi)    { GM_TAIL(0x8006C650u, 0); }                      /* ::postDraw (dBase_c's) */
E(fn_800E1DB0) { sc_set_start(GM_PASS); }                                      /* ::setStartScene */
E(fn_800E1DD0) { R(3) = 0; R(4) = 1; GM_TAIL(0x801017D0u, 0); }                /* ::setResetScene (dScRestartCrsin_c::startTitle) */
E(fn_800E1DE0) { sc_create_next(GM_PASS); }                                    /* ::createNextScene */
E(fn_800E1F60) { gm_set_u16(SDA(SDA_FADEOUT), (uint16_t)R(3)); }              /* ::setFadeOutFrame */
E(fn_800E1F70) { gm_set_u16(SDA(SDA_FADEIN), (uint16_t)R(3)); gm_set_u16(SDA(SDA_FADEOUT), (uint16_t)R(3)); }   /* ::setFadeInOutFrame */
