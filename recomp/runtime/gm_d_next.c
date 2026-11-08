/* gm_d_next.c - dNext_c, the course's scene changes through its next-gotos (entrances / exits):
 * the instance, setting the next data (setChangeSceneNextDat / setOwnNextData, simpleChangeScene),
 * isNextDifferent, searchNextNum (the next-goto under a position) and changeScene (the fader, the
 * world map on a level exit, otherwise the BGM of the destination area and dScene_c::setNextScene
 * to STAGE). Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_next.cpp) and checked against the recompiled
 * USA rev 2 code (0x800CFBF0-0x800D026C). dNext_c::execute (0x800D0270) stays recompiled: the
 * 8-player module replaces it (instance 2). Written register-exact (R(n)); searchNextNum keeps the
 * PowerPC code's float temporaries and stack slots (its int -> float conversions go through
 * 0x43300000 doubles on the stack).
 *
 * dNext_c (36 bytes): +0 the next-goto data (20 bytes: +8 ID, +9 destination file, +10
 * destination ID, +13 area, +18 level exit), +20 the change type (0 another file, 1 another area,
 * 2 the same area), +24 data set, +25 start the change, +26 change done, +28 the multiplayer
 * delay (u16), +32 the fader type. A next-goto (20 bytes): +0 / +2 x / y (u16), +8 ID, +9
 * destination file (1-based, 0 = this one), +10 destination ID, +11 type, +13 area, +16 flags
 * (u16: 0x80 exit only). dCdFile_c (944 bytes per file, dCd_c at r13 - 22504): +12 the options
 * (+16 the initial next-goto), +32 the next-gotos, +44 has areas, +144 their count. */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d
#define LF(a) ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int rec0(ppc_context *ctx, uint32_t v) { cr_cmp_s(ctx, 0, (int32_t)v, 0); return v != 0; }

#define SDA(o) (R(13) - (o))
#define SDA_NEXT   22208          /* dNext_c::m_instance */
#define SDA_CD     22504          /* dCd_c::m_instance */
#define SDA_STAGE  21688          /* dScStage_c::m_instance (+4620 world, +4622 file, +4623 area) */
#define SDA_GAMEMODE 21628        /* dScStage_c::m_gameMode */
#define SDA_EXITMODE 26228        /* dScStage_c::m_exitMode */
#define SDA_EXECSTOP 22920        /* dActor_c::mExecStopReq */
#define SDA_WMAP_SCENE 21554      /* dScWMap_c::m_SceneNo */
#define SDA_SNDSCENE 20952        /* SndSceneMgr::sInstance */
#define F_GOTO_BY_ID 0x8008E3D0u  /* dCdFile_c::getNextGotoP(id) */

/* the course file (r3: dCd_c's file, null without areas) */
static inline void course_file(GM_CTX, uint32_t idx) {
    R(0) = (uint32_t)((int32_t)idx * 944);
    R(3) = gm_u32(SDA(SDA_CD)); R(3) = R(3) + R(0);
    R(0) = gm_u32(R(3) + 44);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(3) = 0;
}

static void nx_ctor(GM_CTX) {
    R(4) = 0; R(0) = 180;
    gm_set_u8(R(3) + 24, 0); gm_set_u8(R(3) + 25, 0); gm_set_u8(R(3) + 26, 0);
    gm_set_u16(R(3) + 28, 180);
    gm_set_u32(SDA(SDA_NEXT), R(3));
}
static void nx_create(GM_CTX) {                              /* createInstance(heap) */
    GM_FN(0x800CFC10); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    GM_CALLV(0x800CFC24u, 0x8016E4F0u, 0);                   /* mHeap::setCurrentHeap */
    R(31) = R(3); R(3) = 36;
    GM_CALLV(0x800CFC30u, 0x802B9210u, 0);                   /* operator new */
    if (cmps(ctx, (int32_t)R(3), 0) != 0) GM_CALLV(0x800CFC3Cu, 0x800CFBF0u, 0);
    R(3) = R(31);
    GM_CALLV(0x800CFC44u, 0x8016E4F0u, 0);
    R(0) = lr;
}
static void nx_delete(GM_CTX) {
    R(3) = gm_u32(SDA(SDA_NEXT));
    if (cmps(ctx, (int32_t)R(3), 0) == 0) return;
    R(0) = 0; gm_set_u32(SDA(SDA_NEXT), 0);
    GM_TAIL(0x802B9280u, 0);                                 /* operator delete */
}
static void nx_init(GM_CTX) {
    R(4) = 0; R(0) = 180;
    gm_set_u8(R(3) + 24, 0); gm_set_u8(R(3) + 25, 0); gm_set_u8(R(3) + 26, 0);
    gm_set_u16(R(3) + 28, 180);
}
/* setOwnNextData(file, goto): copy the next-goto; its destination file (0 = this one) and ID
   (0xFF = the course's initial one) */
static void nx_set_own(GM_CTX) {
    GM_FN(0x800CFD00); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    R(30) = (uint32_t)((int32_t)R(4) * 944);
    R(29) = R(4);
    R(0) = gm_u32(SDA(SDA_CD)); R(3) = R(0) + R(30);
    R(0) = gm_u32(R(3) + 44);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(3) = 0;
    R(4) = R(5);
    GM_CALLV(0x800CFD48u, F_GOTO_BY_ID, 0);
    R(4) = gm_u32(R(3)); R(0) = gm_u32(R(3) + 4);
    gm_set_u32(R(31) + 4, R(0)); gm_set_u32(R(31), R(4));
    R(0) = gm_u32(R(3) + 12); R(4) = gm_u32(R(3) + 8);
    gm_set_u32(R(31) + 8, R(4));
    R(4) = gm_u8(R(31) + 9);
    gm_set_u32(R(31) + 12, R(0));
    R(0) = R(4) - 1; R(4) = R(0) & 0xFFu;
    R(0) = gm_u32(R(3) + 16);
    int c = cmpu(ctx, R(4), 0xFFu);
    gm_set_u32(R(31) + 16, R(0));
    if (c == 0) R(4) = R(29);
    R(0) = gm_u8(R(31) + 10);
    gm_set_u8(R(31) + 9, (uint8_t)R(4));
    if (cmpu(ctx, R(0), 0xFFu) == 0) {
        R(0) = gm_u32(SDA(SDA_CD)); R(3) = R(0) + R(30);
        R(0) = gm_u32(R(3) + 44);
        if (cmps(ctx, (int32_t)R(0), 0) == 0) R(3) = 0;
        R(3) = gm_u32(R(3) + 12); R(0) = gm_u8(R(3) + 16);
        gm_set_u8(R(31) + 10, (uint8_t)R(0));
    }
    R(0) = lr;
}
static void nx_set_change(GM_CTX) {                          /* setChangeSceneNextDat(file, goto, fader) */
    GM_FN(0x800CFCA0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(6); R(30) = R(3);
    R(0) = gm_u8(R(3) + 24);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        GM_CALLV(0x800CFCCCu, 0x800CFD00u, 0);               /* setOwnNextData(file, goto) */
        R(3) = 1; R(0) = 0;
        gm_set_u8(R(30) + 24, 1); gm_set_u8(R(30) + 26, 0); gm_set_u32(R(30) + 32, R(31));
    }
    R(0) = lr;
}
static void nx_is_different(GM_CTX) {
    GM_FN(0x800CFDE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(4); R(30) = R(3);
    R(0) = gm_u8(R(3) + 24);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) { R(3) = 0; goto out; }
    course_file(GM_PASS, R(4));
    R(4) = R(5);
    GM_CALLV(0x800CFE30u, F_GOTO_BY_ID, 0);
    R(4) = gm_u8(R(3) + 8); R(0) = gm_u8(R(30) + 8);
    if (cmpu(ctx, R(4), R(0)) != 0) { R(3) = 1; goto out; }
    R(3) = gm_u8(R(3) + 9); R(0) = R(3) - 1; R(3) = R(0) & 0xFFu;
    if (cmpu(ctx, R(3), 0xFFu) == 0) R(3) = R(31);
    R(0) = gm_u8(R(30) + 9); R(3) = R(3) & 0xFFu;
    R(3) = cmpu(ctx, R(3), R(0)) != 0 ? 1 : 0;
out:
    R(0) = lr;
}
/* searchNextNum(file, x, y, &num): the first enterable next-goto whose box holds (x, -y) */
static void nx_search(GM_CTX) {
    GM_FN(0x800CFEA0);
    gptr f = gm_frame_sp;
    R(0) = (uint32_t)((int32_t)R(4) * 944);
    R(3) = gm_u32(SDA(SDA_CD)); R(3) = R(3) + R(0);
    R(0) = gm_u32(R(3) + 44);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(3) = 0;
    ctx->f[0].u = ctx->f[2].u ^ 0x8000000000000000ull;      /* fneg: ps0 only */
    R(0) = gm_u32(R(3) + 144);
    R(6) = gm_u32(R(3) + 32);
    R(3) = 0x43300000u;
    SF(f + 16, F(1));
    FB(4, LF(R(2) - 26304));                                 /* 32.0f */
    SF(f + 20, F(0));
    FB(3, LF(R(2) - 26312));                                 /* 16.0f */
    FB(5, LF(R(2) - 26308));                                 /* 48.0f */
    ctx->f[2].u = ld64(base, R(2) - 26296);                  /* (the int -> double bias) */
    ctx->ctr = R(0);
    if (cmps(ctx, (int32_t)R(0), 0) > 0) {
        for (;;) {
            R(0) = gm_u16(R(6) + 16) & 0x80u;
            if (!rec0(ctx, R(0))) {
                R(4) = gm_u8(R(6) + 11);
                double w, h;                                 /* (f3 16 / f4 32 / f5 48) */
                R(0) = R(4) - 16;
                if (cmpu(ctx, R(0), 3) <= 0) { w = F(3); h = F(3); }
                else if (R(0) = R(4) - 5, cmpu(ctx, R(0), 1) <= 0) { w = F(3); h = F(4); }
                else if (cmps(ctx, (int32_t)R(4), 14) == 0) { w = F(3); h = F(3); }
                else if (cmps(ctx, (int32_t)R(4), 15) == 0) { w = F(5); h = F(3); }
                else if (cmps(ctx, (int32_t)R(4), 22) == 0) { w = F(4); h = F(4); }
                else { w = F(4); h = F(3); }
                SF(f + 8, w); SF(f + 12, h);
                R(0) = gm_u16(R(6)); gm_set_u32(f + 28, R(0));
                R(0) = gm_u16(R(6) + 2);
                gm_set_u32(f + 24, R(3));
                FB(1, LF(f + 16));
                ctx->f[0].u = ld64(base, f + 24);
                gm_set_u32(f + 36, R(0));
                FB(6, frsp(F(0) - F(2)));                    /* gdX */
                gm_set_u32(f + 32, R(3));
                ctx->f[0].u = ld64(base, f + 32);
                cr_fcmp(ctx, 0, F(6), F(1));
                FB(7, frsp(F(0) - F(2)));                    /* gdY */
                CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
                if (CR_BIT(ctx, 2)) {
                    FB(0, LF(f + 8)); FB(0, frsp(F(6) + F(0)));
                    cr_fcmp(ctx, 0, F(1), F(0));
                    if (CR_BIT(ctx, 0)) {
                        FB(1, LF(f + 20));
                        cr_fcmp(ctx, 0, F(7), F(1));
                        CR_SETBIT(ctx, 2, (CR_BIT(ctx, 0) | CR_BIT(ctx, 2)));
                        if (CR_BIT(ctx, 2)) {
                            FB(0, LF(f + 12)); FB(0, frsp(F(7) + F(0)));
                            cr_fcmp(ctx, 0, F(1), F(0));
                            if (CR_BIT(ctx, 0)) {
                                R(0) = gm_u8(R(6) + 8); R(3) = 1;
                                R(0) = (uint32_t)(int32_t)(int8_t)R(0);
                                gm_set_u32(R(5), R(0));
                                return;
                            }
                        }
                    }
                }
            }
            R(6) = R(6) + 20;
            if (--ctx->ctr == 0) break;
            GM_LOOP();
        }
    }
    R(3) = 0;
}
static void nx_simple(GM_CTX) {                              /* simpleChangeScene(file, goto, fader) */
    GM_FN(0x800D0030); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(6); R(30) = R(5); R(29) = R(4); R(28) = R(3);
    R(0) = gm_u8(R(3) + 24);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) {
        course_file(GM_PASS, R(4));
        R(4) = R(30);
        GM_CALLV(0x800D0090u, F_GOTO_BY_ID, 0);
        R(6) = gm_u32(R(3)); R(4) = 1; R(5) = gm_u32(R(3) + 4); R(0) = 0;
        gm_set_u32(R(28) + 4, R(5)); gm_set_u32(R(28), R(6));
        R(6) = gm_u32(R(3) + 8); R(5) = gm_u32(R(3) + 12);
        gm_set_u32(R(28) + 12, R(5)); gm_set_u32(R(28) + 8, R(6));
        R(3) = gm_u32(R(3) + 16); gm_set_u32(R(28) + 16, R(3));
        gm_set_u8(R(28) + 9, (uint8_t)R(29)); gm_set_u8(R(28) + 10, (uint8_t)R(30));
        gm_set_u8(R(28) + 24, 1); gm_set_u8(R(28) + 26, 0); gm_set_u8(R(28) + 25, 1);
        gm_set_u16(R(28) + 28, 0); gm_set_u32(R(28) + 32, R(31));
    }
    R(0) = lr;
}
static void nx_change(GM_CTX) {                              /* changeScene() */
    GM_FN(0x800D0100); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    R(31) = R(3);
    R(4) = gm_u8(SDA(SDA_EXECSTOP)); R(0) = gm_u32(SDA(SDA_GAMEMODE));
    R(4) |= 0xFu; gm_set_u8(SDA(SDA_EXECSTOP), (uint8_t)R(4));
    R(28) = gm_u32(SDA(SDA_STAGE));
    int c = cmps(ctx, (int32_t)R(0), 4);
    R(30) = gm_u8(R(28) + 4620);                             /* the world */
    if (c == 0) { R(3) = 1; GM_CALLV(0x800D0148u, 0x800B0DB0u, 0); }   /* (the hint movie: FADER_CIRCLE_MIDDLE) */
    else { R(3) = gm_u32(R(3) + 32); GM_CALLV(0x800D0154u, 0x800B0DB0u, 0); }   /* dFader_c::setFader */
    R(0) = gm_u8(R(31) + 18);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) {                  /* a level exit: the world map */
        R(0) = 0; gm_set_u32(SDA(SDA_EXITMODE), 0);
        R(4) = gm_u8(SDA(SDA_WMAP_SCENE)); R(3) = R(30); R(5) = 0;
        GM_CALLV(0x800D0178u, 0x80102690u, 0);               /* dScWMap_c::setNextWorldScene */
        goto out;
    }
    R(0) = gm_u8(R(31) + 9); R(3) = gm_u32(SDA(SDA_CD));
    R(0) = (uint32_t)((int32_t)R(0) * 944); R(29) = R(3) + R(0);
    R(0) = gm_u32(R(29) + 44);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(29) = 0;
    R(4) = gm_u8(R(31) + 10); R(3) = R(29);
    GM_CALLV(0x800D01ACu, F_GOTO_BY_ID, 0);
    R(4) = gm_u8(R(28) + 4622); R(30) = R(3); R(0) = gm_u8(R(31) + 9);
    if (cmpu(ctx, R(4), R(0)) != 0) { R(0) = 0; gm_set_u32(R(31) + 20, 0); }
    else {
        R(3) = gm_u8(R(3) + 13); R(0) = gm_u8(R(28) + 4623);
        if (cmpu(ctx, R(3), R(0)) != 0) { R(0) = 1; gm_set_u32(R(31) + 20, 1); }
        else { R(0) = 2; gm_set_u32(R(31) + 20, 2); }
    }
    R(4) = gm_u8(R(30) + 13); R(3) = R(29);
    GM_CALLV(0x800D01FCu, 0x8008E5C0u, 0);                   /* getAreaBgm */
    R(3) &= 0xFFu;
    GM_CALLV(0x800D0204u, 0x8006A240u, 0);                   /* dAudio::setMainBgmNo */
    R(4) = gm_u8(R(30) + 13); R(3) = R(29);
    GM_CALLV(0x800D0210u, 0x8008E5F0u, 0);                   /* getAreaBgmMode */
    R(28) = R(3) & 0xFFu; R(3) &= 0xFu;
    GM_CALLV(0x800D021Cu, 0x8006A260u, 0);                   /* dAudio::setBgmMode */
    R(3) = gm_u32(SDA(SDA_SNDSCENE)); R(4) = (R(28) >> 4) & 0xFu;
    GM_CALLV(0x800D0228u, 0x8019D470u, 0);
    R(5) = gm_u8(R(31) + 9); R(0) = 1; R(4) = gm_u8(R(31) + 10); R(3) = 5;
    gm_set_u8(R(31) + 26, 1);
    R(0) = 3;
    R(4) = ((R(5) << 8) & 0xF00u) | (R(4) & ~0xF00u);      /* the STAGE parameter: file << 8 | goto */
    R(5) = 0;
    gm_set_u32(SDA(SDA_EXITMODE), 3);
    GM_CALLV(0x800D0250u, 0x800E1E60u, 0);                   /* dScene_c::setNextScene(STAGE, param, false) */
out:
    R(0) = lr;
}

#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
#define NX_MEM A(0), 36

/* ---- the self-test (RT_GM_SELFTEST=next): no test input takes a pipe or a door, so the pure
   ones run against their PowerPC versions on the live dNext_c with the course loaded - random
   next data, files, next-gotos, and positions in / around the course's next-gotos ---- */
static void nx_selftest(GM_CTX);
GM_HLE_VOID(fn_800CFC80, NX_MEM) { nx_selftest(GM_PASS); nx_init(GM_PASS); }               /* ::initialize */
GM_HLE_VOID(fn_800CFCA0, NX_MEM) { nx_set_change(GM_PASS); }                               /* ::setChangeSceneNextDat */
GM_HLE_VOID(fn_800CFD00, NX_MEM) { nx_set_own(GM_PASS); }                                  /* ::setOwnNextData */
GM_HLE_INT(fn_800CFDE0, NX_MEM) { nx_is_different(GM_PASS); }                              /* ::isNextDifferent */
GM_HLE_INT(fn_800CFEA0, A(2), 4) { nx_search(GM_PASS); }                                    /* ::searchNextNum */
GM_HLE_VOID(fn_800D0010, NX_MEM) {                                                          /* ::simpleChangeScene(goto, fader): this file */
    R(7) = gm_u32(SDA(SDA_STAGE)); R(0) = R(4); R(6) = R(5); R(4) = gm_u8(R(7) + 4622); R(5) = R(0);
    GM_TAIL(0x800D0030u, 0);
}
GM_HLE_VOID(fn_800D0030, NX_MEM) { nx_simple(GM_PASS); }                                   /* ::simpleChangeScene(file, goto, fader) */
E(fn_800CFBF0) { nx_ctor(GM_PASS); }                         /* dNext_c::dNext_c */
E(fn_800CFC10) { nx_create(GM_PASS); }                       /* ::createInstance */
E(fn_800CFC60) { nx_delete(GM_PASS); }                       /* ::deleteInstance (off: not reached) */
E(fn_800D0100) { nx_change(GM_PASS); }                       /* ::changeScene (off: not reached) */

static gptr nx_t_self; static uint32_t nx_t_file;
static gptr nx_t_cfile(uint32_t i) { gptr c = gm_u32(0x8042F680u - SDA_CD) + i * 944; return gm_u32(c + 44) ? c : 0; }
static void nx_t_randomize(GM_CTX, int round) {
    (void)round;
    for (uint32_t i = 0; i < 36; i += 4) gm_set_u32(nx_t_self + i, gm_rand());
    gm_set_u8(nx_t_self + 24, gm_rand() & 1);
    gptr c = nx_t_cfile(nx_t_file); uint32_t n = c ? gm_u32(c + 144) : 0;
    float x = (float)(gm_rand() % 8000), y = (float)(gm_rand() % 2000);
    if (n && (gm_rand() & 1)) {                              /* (near one of the next-gotos) */
        gptr g = gm_u32(c + 32) + (gm_rand() % n) * 20;
        x = (float)gm_u16(g) + (float)((int)(gm_rand() % 72) - 8);
        y = (float)gm_u16(g + 2) + (float)((int)(gm_rand() % 56) - 8);
    }
    ctx->f[1].d = ctx->ps1[1] = x; ctx->f[2].d = ctx->ps1[2] = -y;
    if (c && n) { gptr g = gm_u32(c + 32) + (gm_rand() % n) * 20; gm_set_u8(nx_t_self + 8, gm_u8(g + 8)); gm_set_u8(nx_t_self + 9, gm_rand() % 3); }
}
static uint32_t nx_t_arg(char k) {
    gptr c = nx_t_cfile(nx_t_file); uint32_t n = c ? gm_u32(c + 144) : 0;
    if (k == 'F') return nx_t_file;
    if (k == 'G') return n ? gm_u8(gm_u32(c + 32) + (gm_rand() % n) * 20 + 8) : 0;   /* (an ID the file has) */
    if (k == 'O') return nx_t_self + 20;                    /* (the found number goes into the object) */
    if (k == 'D') return gm_rand() % 8;                     /* a fader type */
    return 0xDEADBEEFu;
}
static const gm_test_t nx_tests[] = {
    GM_TEST(fn_800CFC80, 0, ""),
    GM_TEST(fn_800CFCA0, 0, "FGD"),
    GM_TEST(fn_800CFD00, 0, "FG"),
    GM_TEST(fn_800CFDE0, GMV_RET, "FG"),
    GM_TEST(fn_800CFEA0, GMV_RET, "FO"),
    GM_TEST(fn_800D0010, 0, "GD"),
    GM_TEST(fn_800D0030, 0, "FGD"),
};
static void nx_selftest(GM_CTX) {
    if (!gm_selftest_wanted("next")) return;
    gptr st = gm_u32(SDA(SDA_STAGE));
    if (!st || !gm_u32(SDA(SDA_CD))) return;
    nx_t_file = gm_u8(st + 4622);
    if (!nx_t_cfile(nx_t_file) || !gm_u32(nx_t_cfile(nx_t_file) + 144)) return;      /* (a course with next-gotos) */
    nx_t_self = R(3);
    const gptr ranges[] = { nx_t_self, 36 };
    const gm_selftest_t t = { "next", nx_tests, (int)(sizeof nx_tests / sizeof *nx_tests), 400, ranges, 1, nx_t_randomize, nx_t_arg };
    gm_selftest(GM_PASS, &t);
}
