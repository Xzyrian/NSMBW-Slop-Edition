/* gm_m3d_scene.c - mLib's 3D scene (m_3d.cpp): the g3d scene root and the allocator models are
 * made from, the per-scene EGG light / fog managers, the frame's calc-world / calc-view / draw
 * steps, and m3d::proc_c (a user draw procedure in the scene). Track B (gm.h, docs/DECOMP.md),
 * instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/mLib/m_3d.cpp) and checked against the recompiled
 * USA rev 2 code (0x80164500-0x801650C4). The non-volatile registers are mirrored around nested
 * calls (gm_nv.h). The globals are small-data words: the allocator, the scene root, the light
 * manager array and its size, the fog manager array and its size. */
#include "gm.h"
#include "gm_nv.h"

#define SDA 0x8042F680u
#define L_ALLOCATOR (SDA - 21176)        /* m3d::internal::l_allocator_p */
#define L_SCNROOT   (SDA - 21172)        /* m3d::internal::l_scnRoot_p */
#define L_LIGHTS    (SDA - 21164)        /* m3d::internal::l_lightMgr_pp */
#define L_NLIGHTS   (SDA - 21168)        /* m3d::internal::l_numLightMgr */
#define L_FOGS      (SDA - 21156)        /* m3d::internal::l_fogMgr_pp */
#define L_NFOGS     (SDA - 21160)        /* m3d::internal::l_numFogMgr */
#define RENDER_MODE (SDA - 20992)        /* (mVideo: the GXRenderModeObj pointer) */
#define TYPE_SCNPROC 0x802F9018u         /* nw4r::g3d::ScnProc's TypeObj name */
#define F_DRAW_PROC  0x80164FA0u         /* m3d::proc_c_drawProc */
#define F_NEW       0x802B9240u          /* operator new(size, heap, align) */
#define F_NEWA      0x802B9270u          /* operator new[] */
#define F_DELETE    0x802B9280u
#define F_DELETEA   0x802B9290u
#define F_MEMSET    0x800046B4u
#define F_SET_HEAP  0x8016E4F0u          /* mHeap::setCurrentHeap */
#define F_ALLOCATOR_CT 0x8016A5E0u       /* mAllocator_c::mAllocator_c */
#define F_ALLOCATOR_SETUP 0x8016A690u    /* mAllocator_c::attach */
#define F_G3D_INIT  0x8025EEB0u
#define F_G3D_RESET 0x8025EFA0u
#define F_SET_RENDER_MODE 0x8024D4F0u    /* G3DState::SetRenderModeObj */
#define F_ROOT_CONSTRUCT 0x802589E0u     /* ScnRoot::Construct */
#define F_GFX_CONFIG_CT 0x802C78F0u      /* EGG::GfxEngine::Configuration::Configuration */
#define F_STATEGX_INIT 0x802D2610u       /* EGG::StateGX::initialize */
#define F_SCREEN_INIT 0x802D0AE0u        /* EGG::Screen::Initialize */
#define F_SCREEN_TV 0x802D1B50u          /* EGG::Screen::SetTVModeDefault */
#define F_DRAWGX_INIT 0x802C1710u        /* EGG::DrawGX::Initialize */
#define F_LIGHTTEX_INIT 0x802CB930u      /* EGG::LightTexture::initialize */
#define F_LIGHTMGR_CT 0x802C81F0u        /* EGG::LightManager::LightManager */
#define F_FOGMGR_CT 0x802C6550u          /* EGG::FogManager::FogManager */
#define F_FOG_CALC  0x802C6640u          /* EGG::FogManager::Calc */
#define F_FOG_COPY  0x802C6660u          /* EGG::FogManager::CopyToG3D */
#define F_CAPTURE   0x802CD4B0u          /* EGG::LightTextureManager::drawAndCaptureTexture */
#define F_MODELEX_CT 0x802CDD00u         /* EGG::ModelEx::ModelEx */
#define F_TEX_INDEX 0x802CD2D0u          /* EGG::LightTextureManager::getTextureIndex */
#define F_REPLACE_TEX 0x802CD1F0u        /* EGG::LightTextureManager::replaceModelTexture */
#define F_GET_CAMERA 0x80258BD0u         /* ScnRoot::GetCamera */
#define F_CUR_CAMERA 0x80258C30u         /* ScnRoot::GetCurrentCamera */
#define F_SET_CAMERA 0x80258C70u         /* ScnRoot::SetCurrentCamera */
#define F_CAMERA_MTX 0x802540B0u         /* Camera::GetCameraMtx */
#define F_CALC_WORLD 0x802590A0u         /* ScnRoot::CalcWorld / CalcMaterial / CalcView / ... */
#define F_CALC_MAT  0x802590F0u
#define F_CALC_VIEW 0x80259110u
#define F_GATHER    0x80259190u
#define F_ZSORT     0x80259280u
#define F_DRAW_OPA  0x802592E0u
#define F_DRAW_XLU  0x80259360u
#define F_RESET_GX  0x802D2E50u          /* EGG::StateGX::resetGXCache */
#define F_GET_NODE  0x8023B200u          /* ResMdl::GetResNode(name) */
#define F_IND_STAGES 0x801C8110u         /* GXSetNumIndStages */
#define F_TEV_DIRECT 0x801C8130u         /* GXSetTevDirect */
#define F_PROC_CONSTRUCT 0x8025EFB0u     /* ScnProc::Construct */
#define F_PRIO_OPA  0x80257640u          /* ScnObj::SetPriorityDrawOpa */
#define F_PRIO_XLU  0x80257670u

#define LF(a)    ldfs(base, (a))
#define R2F(off) LF(ctx->r[2] - (off))
#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f
#define V(o, off) gm_u32(gm_u32(o) + (off))
#define ROOT gm_u32(L_SCNROOT)
/* a tail call: the callee's r3 is the function's */
#define TAIL(...) GM_RET(GM_CALLR(ctx->lr, __VA_ARGS__))      /* (LR stays the caller's) */

/* ================================================================== the scene */
/* create(heap, max children, max scene objects, light objects, light sets): the allocator, g3d,
   the scene root */
static uint32_t m3d_create(GM_CTX, gptr heap, uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    FN(0x80164500); GM_NV_KEEP;
    NV_R(27, heap); NV_R(28, a); NV_R(29, b); NV_R(30, c); NV_R(31, d);
    gptr al = GM_CALLR(0x80164538u, F_NEW, 3, 28, heap, 4);
    if (al) al = GM_CALLR(0x80164544u, F_ALLOCATOR_CT, 1, al);
    gm_set_u32(L_ALLOCATOR, al);
    if (!al) return 0;
    GM_CALLR(0x80164564u, F_ALLOCATOR_SETUP, 3, al, heap, 32);
    GM_CALLR(0x8016456Cu, F_G3D_INIT, 1, 1);
    GM_CALLR(0x80164578u, F_SET_RENDER_MODE, 1, gm_u32(gm_u32(RENDER_MODE)));
    gptr root = GM_CALLR(0x80164594u, F_ROOT_CONSTRUCT, 6, gm_u32(L_ALLOCATOR), f + 8, a, b, c, d);
    gm_set_u32(L_SCNROOT, root);
    if (root) return 1;
    al = gm_u32(L_ALLOCATOR);
    if (al) GM_CALLR(0x801645C0u, gm_u32(gm_u32(al + 16) + 8), 2, al, 1);              /* (its destructor) */
    gm_set_u32(L_ALLOCATOR, 0);
    return 0;
}
/* create(heap, pixel format, clear colour, the four above, light managers, fog managers): EGG's
   screen / GX state / light textures, the manager arrays, then the scene */
static uint32_t m3d_create_all(GM_CTX, gptr heap, uint32_t fmt, gptr color, uint32_t a, uint32_t b,
                               uint32_t c, uint32_t d, uint32_t nl, uint32_t nf) {
    FN(0x801645F0); GM_NV_KEEP;
    NV_R(23, heap); NV_R(24, fmt); NV_R(25, color); NV_R(26, a); NV_R(27, b); NV_R(28, c); NV_R(29, d);
    NV_R(30, nl); NV_R(31, nf);
    if (gm_u32(L_LIGHTS) && gm_u32(L_FOGS)) return 0;
    GM_CALLR(0x80164650u, F_GFX_CONFIG_CT, 1, f + 24);
    uint32_t h = gm_u16(f + 26);
    gm_set_u16(f + 16, gm_u16(f + 44)); gm_set_u16(f + 18, gm_u16(f + 46));
    gm_set_u16(f + 12, h); gm_set_u16(f + 14, h);
    gm_set_u32(f + 8, gm_u32(color));
    GM_CALLR(0x80164684u, F_STATEGX_INIT, 4, gm_u16(f + 24), h, f + 8, fmt);
    GM_CALLR(0x80164694u, F_SCREEN_INIT, 3, f + 16, f + 12, 0);
    GM_CALLR(0x80164698u, F_SCREEN_TV, 0);
    GM_CALLR(0x801646A0u, F_DRAWGX_INIT, 1, heap);
    GM_CALLR(0x801646ACu, F_LIGHTTEX_INIT, 2, 32, heap);
    gptr p = GM_CALLR(0x801646BCu, F_NEWA, 3, nl << 2, heap, 4);
    gm_set_u32(L_LIGHTS, p);
    if (p) {
        gm_set_u32(L_NLIGHTS, nl);
        p = GM_CALLR(0x801646DCu, F_NEWA, 3, nf << 2, heap, 4);
        gm_set_u32(L_FOGS, p);
        if (p) {
            gm_set_u32(L_NFOGS, nf);
            GM_CALLR(0x801646FCu, F_MEMSET, 3, gm_u32(L_LIGHTS), 0, nl << 2);
            GM_CALLR(0x8016470Cu, F_MEMSET, 3, gm_u32(L_FOGS), 0, nf << 2);
            if (NCALL(0x80164724u, m3d_create(GM_PASS, heap, a, b, c, d))) return 1;
        }
    }
    GM_CALLR(0x8016473Cu, F_DELETEA, 1, gm_u32(L_LIGHTS));
    NV_R(31, 0);
    gm_set_u32(L_LIGHTS, 0);
    GM_CALLR(0x8016474Cu, F_DELETEA, 1, gm_u32(L_FOGS));
    gm_set_u32(L_FOGS, 0);
    return 0;
}

/* createFogMgr(heap, size, index) */
static uint32_t m3d_create_fog(GM_CTX, gptr heap, uint32_t n, int32_t idx) {
    FN(0x80164990); GM_NV_KEEP;
    NV_R(30, n);
    if (idx < 0 || (uint32_t)idx >= gm_u32(L_NFOGS)) return 0;
    uint32_t o4 = (uint32_t)idx << 2;
    if (gm_u32(gm_u32(L_FOGS) + o4)) return 0;
    NV_R(31, o4);
    gptr m = GM_CALLR(0x801649E8u, F_NEW, 3, 16, heap, 4);
    if (m) m = GM_CALLR(0x801649FCu, F_FOGMGR_CT, 2, m, n & 0xFFFF);
    if (!m) return 0;
    gm_set_u32(gm_u32(L_FOGS) + o4, m);
    return 1;
}
/* createLightMgr(heap, a, b, c, with a fog manager, index) */
static uint32_t m3d_create_light(GM_CTX, gptr heap, uint32_t a, uint32_t b, uint32_t c, uint32_t fog, int32_t idx) {
    FN(0x80164770); GM_NV_KEEP;
    NV_R(23, heap); NV_R(24, a); NV_R(25, b); NV_R(26, c); NV_R(27, fog); NV_R(28, idx);
    gptr arr = gm_u32(L_LIGHTS);
    if (!arr || idx < 0 || (uint32_t)idx >= gm_u32(L_NLIGHTS) || (uint32_t)idx >= gm_u32(L_NFOGS)) return 0;
    uint32_t o4 = (uint32_t)idx << 2;
    NV_R(30, o4);
    if (gm_u32(arr + o4) || gm_u32(gm_u32(L_FOGS) + o4)) return 0;
    gptr old = GM_CALLR(0x801647F4u, F_SET_HEAP, 1, heap);
    NV_R(29, old);
    gptr m = GM_CALLR(0x80164808u, F_NEW, 3, 40, heap, 4);
    NV_R(31, m);
    if (m) { m = GM_CALLR(0x80164824u, F_LIGHTMGR_CT, 4, m, a, b, c); NV_R(31, m); }
    GM_CALLR(0x80164830u, F_SET_HEAP, 1, old);
    if (m) {
        if (!fog || NCALL(0x80164850u, m3d_create_fog(GM_PASS, heap, 32, idx))) {
            gm_set_u32(gm_u32(L_LIGHTS) + o4, m);
            return 1;
        }
        GM_CALLR(0x80164888u, V(m, 24), 2, m, 1);                                       /* (its destructor) */
    }
    return 0;
}

/* removeLightMgr / removeFogMgr(index): delete that manager, or with index < 0 all of them and
   the array */
static void m3d_remove_mgrs(GM_CTX, uint32_t arr_at, uint32_t n_at, int32_t idx, gptr *pr30, uint32_t *pr31) {
    gptr arr = gm_u32(arr_at);
    NV_R(30, arr); *pr30 = arr;
    if (!arr) return;
    uint32_t o4 = (uint32_t)idx << 2;
    NV_R(31, o4); *pr31 = o4;
    gptr m = gm_u32(arr + o4);
    if (!m) return;
    if (idx >= 0) {
        GM_CALL(V(m, 24), 2, m, 1);
        gm_set_u32(arr + o4, 0);
        return;
    }
    uint32_t i = 0; gptr p = arr;
    NV_R(31, 0);
    while (i < gm_u32(n_at)) {
        GM_LOOP();
        gptr o = gm_u32(p);
        if (o) GM_CALL(V(o, 24), 2, o, 1);
        p += 4; i++;
        NV_R(30, p); NV_R(31, i);
    }
    *pr30 = p; *pr31 = i;
    GM_CALL(F_DELETE, 1, gm_u32(arr_at));
    gm_set_u32(arr_at, 0);
}
static void m3d_remove_fog(GM_CTX, int32_t idx) {
    FN(0x80164A40); GM_NV_KEEP;
    gptr r30; uint32_t r31;
    m3d_remove_mgrs(GM_PASS, L_FOGS, L_NFOGS, idx, &r30, &r31);
}
static void m3d_remove_light(GM_CTX, int32_t idx) {
    FN(0x801648B0); GM_NV_KEEP;
    gptr r30; uint32_t r31;
    NV_R(29, idx);
    m3d_remove_mgrs(GM_PASS, L_LIGHTS, L_NLIGHTS, idx, &r30, &r31);
    NCALL(0x80164974u, m3d_remove_fog(GM_PASS, idx));
}

/* unlink / link the scene's light texture */
static void m3d_unlink(GM_CTX, int32_t idx) {
    FN(0x80164B90); GM_NV_KEEP;
    NV_R(31, idx);
    gptr arr = gm_u32(L_LIGHTS), m;
    if (arr && (m = gm_u32(arr + ((uint32_t)idx << 2)))) GM_CALLR(0x80164BD0u, V(m, 40), 1, m);
    arr = gm_u32(L_FOGS);
    if (arr && (m = gm_u32(arr + ((uint32_t)idx << 2)))) gm_set_u8(m + 4, gm_u8(m + 4) & 0xFB);
}
/* replace a model's light texture(name, model, index) */
static uint32_t m3d_replace_tex(GM_CTX, gptr name, gptr mdl, int32_t idx) {
    FN(0x80164C50); GM_NV_KEEP;
    NV_R(31, idx); NV_R(30, name);
    if (!gm_u32(L_LIGHTS)) return 0;
    GM_CALLR(0x80164C8Cu, F_MODELEX_CT, 2, f + 8, gm_u32(mdl + 4));
    gptr ltm = gm_u32(gm_u32(gm_u32(L_LIGHTS) + ((uint32_t)idx << 2)) + 20);
    NV_R(31, ltm);
    uint32_t i = GM_CALLR(0x80164CA8u, F_TEX_INDEX, 2, ltm, name);
    return GM_CALLR(0x80164CB8u, F_REPLACE_TEX, 3, ltm, i, f + 8);
}
static void m3d_calc_world(GM_CTX, int32_t idx) {
    FN(0x80164CD0); GM_NV_KEEP;
    NV_R(31, idx);
    gptr arr = gm_u32(L_LIGHTS), m;
    if (arr && (m = gm_u32(arr + ((uint32_t)idx << 2)))) GM_CALLR(0x80164D14u, V(m, 32), 2, m, ROOT);
    arr = gm_u32(L_FOGS);
    if (arr && (m = gm_u32(arr + ((uint32_t)idx << 2)))) GM_CALLR(0x80164D34u, F_FOG_CALC, 1, m);
    GM_CALLR(0x80164D3Cu, F_CALC_WORLD, 1, ROOT);
}
static void m3d_calc_view(GM_CTX, int32_t idx) {
    FN(0x80164D60); GM_NV_KEEP;
    NV_R(30, idx);
    gptr arr = gm_u32(L_LIGHTS);
    if (arr) {
        uint32_t o4 = (uint32_t)idx << 2;
        NV_R(31, o4);
        if (gm_u32(arr + o4)) {
            gptr cam = GM_CALL(F_CUR_CAMERA, 1, ROOT);                    /* (m3d::getCurrentCamera, a tail call) */
            gm_set_u32(f + 8, cam);
            GM_CALLR(0x80164DA8u, F_CAMERA_MTX, 2, f + 8, f + 16);
            uint32_t id = gm_u8(ROOT + 244);                              /* (m3d::getCurrentCameraID) */
            gptr m = gm_u32(gm_u32(L_LIGHTS) + o4);
            GM_CALLR(0x80164DD0u, V(m, 36), 4, m, f + 16, id & 0xFF, ROOT);
        }
    }
    gptr fa = gm_u32(L_FOGS), m;
    if (fa && (m = gm_u32(fa + ((uint32_t)idx << 2)))) GM_CALLR(0x80164DF4u, F_FOG_COPY, 2, m, ROOT);
    GM_CALLR(0x80164DFCu, F_CALC_VIEW, 1, ROOT);
    GM_CALLR(0x80164E04u, F_GATHER, 1, ROOT);
    GM_CALLR(0x80164E0Cu, F_ZSORT, 1, ROOT);
}
static void m3d_remove_all(GM_CTX) {
    FN(0x80164E70); GM_NV_KEEP;
    gptr root = ROOT;
    NV_R(31, root);
    uint32_t n;
    while ((n = gm_u32(root + 228))) { GM_LOOP(); GM_CALLR(0x80164EA0u, V(root, 56), 2, root, n - 1); }
}
static void m3d_reset(GM_CTX) {
    FN(0x80164EC0);
    GM_CALLR(0x80164ED0u, F_G3D_RESET, 0);
    if (gm_u32(L_LIGHTS) || gm_u32(L_FOGS)) GM_CALLR(0x80164EECu, F_RESET_GX, 0);
}
static int32_t m3d_node_id(GM_CTX, gptr mdl, gptr name) {
    FN(0x80164F00);
    if (!gm_u32(mdl)) return -1;
    gptr n = GM_CALLR(0x80164F1Cu, F_GET_NODE, 2, mdl, name);
    if (!n) return -1;
    return (int32_t)gm_u32(n + 12);
}
static void m3d_no_ind_tex(GM_CTX) {
    FN(0x80164F50); GM_NV_KEEP;
    GM_CALLR(0x80164F68u, F_IND_STAGES, 1, 0);
    for (uint32_t i = 0;;) {
        NV_R(31, i);
        GM_CALLR(0x80164F74u, F_TEV_DIRECT, 1, i);
        if (++i >= 16) break;
        GM_LOOP();
    }
}

/* ================================================================== proc_c */
/* proc_c::create(allocator, size out): a ScnProc drawing through the proc_c's drawOpa / drawXlu */
static uint32_t proc_create(GM_CTX, gptr self, gptr alloc, gptr psize) {
    FN(0x80164FD0); GM_NV_KEEP;
    NV_R(29, self);
    if (!alloc) alloc = gm_u32(L_ALLOCATOR);
    if (!psize) psize = f + 12;
    gptr s = GM_CALLR(0x80165028u, F_PROC_CONSTRUCT, 6, alloc, psize, F_DRAW_PROC, 1, 1, 0);
    gm_set_u32(self + 4, s);
    if (!s) return 0;
    GM_CALLR(0x80165044u, F_PRIO_OPA, 2, s, 127);
    GM_CALLR(0x80165050u, F_PRIO_XLU, 2, gm_u32(self + 4), 127);
    s = gm_u32(self + 4);
    uint32_t ok = 0;
    NV_R(31, s); NV_R(30, 0);
    if (s) {
        gm_set_u32(f + 8, TYPE_SCNPROC);
        if (GM_CALLR(0x80165084u, V(s, 8), 2, s, f + 8)) ok = 1;                       /* (G3dObj::DynamicCast) */
    }
    if (!ok) s = 0;
    gm_set_u32(s + 240, self);
    return 1;
}

/* ================================================================== hle entry points
   On: 26 are reached by the test runs from recompiled code, create and removeFogMgr run inside
   them. Written but off (not reached): createFogMgr (fn_80164990). */
#define A(i) GM_ARG(i)
#define E(name) GM_HLE(name)
E(fn_80164500) { GM_RET(m3d_create(GM_PASS, A(0), A(1), A(2), A(3), A(4))); }                 /* m3d::create */
E(fn_801645F0) { GM_LR_KEEP; GM_RET(m3d_create_all(GM_PASS, A(0), A(1), A(2), A(3), A(4), A(5), A(6), A(7), gm_u32(ctx->r[1] + 8))); }   /* m3d::create (all) */
E(fn_80164770) { GM_LR_KEEP; GM_RET(m3d_create_light(GM_PASS, A(0), A(1), A(2), A(3), A(4), (int32_t)A(5))); }   /* ::createLightMgr */
E(_Z9FreeScenei) { GM_LR_KEEP; m3d_remove_light(GM_PASS, (int32_t)A(0)); }                     /* ::removeLightMgr */
E(fn_80164990) { GM_RET(m3d_create_fog(GM_PASS, A(0), A(1), (int32_t)A(2))); }                 /* ::createFogMgr */
E(fn_80164A40) { m3d_remove_fog(GM_PASS, (int32_t)A(0)); }                                     /* ::removeFogMgr */
E(fn_80164B10) { GM_RET(ROOT); }                                                               /* ::getScnRoot */
E(GetCameraByID__Fi) { TAIL(F_GET_CAMERA, 2, ROOT, A(0)); }                                    /* ::getCamera */
E(fn_80164B30) { TAIL(F_CUR_CAMERA, 1, ROOT); }                                                /* ::getCurrentCamera */
E(GetCurrentCameraID__Fv) { GM_RET(gm_u8(ROOT + 244)); }                                       /* ::getCurrentCameraID */
E(SetCurrentCameraID__Fi) { TAIL(F_SET_CAMERA, 2, ROOT, A(0)); }                               /* ::setCurrentCamera */
E(fn_80164B60) { GM_RET(ROOT + 10360); }                                                       /* ::getLightSetting */
E(GetSceneLightInfo) { GM_RET(gm_u32(gm_u32(L_LIGHTS) + (A(0) << 2))); }                       /* ::getLightMgr */
E(VMBASEGetVirtualAddrFromPageInMRAM) { GM_RET(gm_u32(gm_u32(L_FOGS) + (A(0) << 2))); }        /* ::getFogMgr */
E(UnlinkScene__Fi) { m3d_unlink(GM_PASS, (int32_t)A(0)); }
E(LinkScene__Fi) {                                                                             /* (draw and capture the light texture) */
    gptr arr = gm_u32(L_LIGHTS), m;
    if (!arr || !(m = gm_u32(arr + (A(0) << 2)))) return;
    double c = R2F(21552);
    ctx->f[1].d = c; ctx->ps1[1] = c;
    ctx->f[2].u = ctx->f[1].u; ctx->f[3].u = ctx->f[1].u; ctx->f[4].u = ctx->f[1].u;
    TAIL(F_CAPTURE, 1, gm_u32(m + 20));
}
E(fn_80164C50) { GM_RET(m3d_replace_tex(GM_PASS, A(0), A(1), (int32_t)A(2))); }
E(SceneCalcWorld__Fi) { m3d_calc_world(GM_PASS, (int32_t)A(0)); }                              /* ::calcWorld */
E(CalcMaterial__Fv) { TAIL(F_CALC_MAT, 1, ROOT); }                                             /* ::calcMaterial */
E(SceneCameraStuff__Fi) { m3d_calc_view(GM_PASS, (int32_t)A(0)); }                 /* ::calcView */
E(DrawOpa__Fv) { TAIL(F_DRAW_OPA, 1, ROOT); }                                                  /* ::drawOpa */
E(DrawXlu__Fv) { TAIL(F_DRAW_XLU, 1, ROOT); }                                                  /* ::drawXlu */
E(InsertIntoScene__Q24nw4r3g3dFPv) { gptr r = ROOT; TAIL(V(r, 52), 3, r, gm_u32(r + 228), A(0)); }   /* ::pushBack */
E(RemoveAllFromScnRoot__Fv) { m3d_remove_all(GM_PASS); }                                       /* ::clear */
E(Reset3DState__Fv) { m3d_reset(GM_PASS); }                                                    /* ::reset */
E(fn_80164F00) { GM_RET(m3d_node_id(GM_PASS, A(0), A(1))); }                                   /* ::getNodeID */
E(DisableIndirectTexturing__3m3dFv) { m3d_no_ind_tex(GM_PASS); }                               /* ::resetMaterial */
E(fn_80164FA0) { gptr p = gm_u32(A(0) + 240); TAIL(V(p, A(1) ? 24 : 28), 1, p); }              /* ::proc_c_drawProc */
E(setup__Q23m3d6proc_cFPvPUi) { GM_RET(proc_create(GM_PASS, A(0), A(1), A(2))); }              /* proc_c::create */
