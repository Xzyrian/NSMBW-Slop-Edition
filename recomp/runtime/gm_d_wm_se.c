/* gm_d_wm_se.c - dWmSeManager_c: world-map sound actors, per-frame spatial updates,
 * sound-slot dispatch and player voice / movement sounds (track B, gm_i2.h).
 * The manager, sound records and nw4r objects remain in big-endian guest memory. */
#include "gm_i2.h"
RT_STATE_FILE

#define WMSE_SIZE          1628
#define WMSE_GLOBAL        (0x80430000u - 23940)
#define WMSE_SOUND_MANAGER (0x80430000u - 23416)
#define WMSE_ZERO          (0x80370000u + 32200)
#define WMSE_MANAGER_VT    (0x81850000u + 9416)
#define WMSE_PLAYER_VT     (0x81850000u + 7824)
#define WMSE_MAP_VT        (0x81850000u + 17108)
#define WMSE_UI_VT         (0x81850000u + 17172)
#define WMSE_FOOT_VT       (0x81850000u + 17224)

static void wmse_virtual(GM_CTX, gptr object, uint32_t slot, uint32_t ra) {
    R(12) = gm_u32(gm_u32(object) + slot); ctx->ctr = R(12); ctx->lr = ra;
    ppc_call_indirect(ctx, base, ctx->ctr);
}

/* One of execute's four copies of SndAudioMgr's 2-D spatial update. The return
 * addresses and SoundInfo scratch location differ at each inlined call site. */
static void wmse_updateActor(GM_CTX, gptr actor, int site) {
    static const uint16_t infoOffset[4] = {144, 112, 80, 48};
    static const uint32_t raCalc[4] = {0x81816628, 0x818167B8, 0x8181694C, 0x81816B08};
    static const uint32_t raFlag[4] = {0x81816658, 0x818167E8, 0x8181697C, 0x81816B38};
    static const uint32_t raVolume0[4] = {0x8181667C, 0x8181680C, 0x818169A0, 0x81816B5C};
    static const uint32_t raVolume1[4] = {0x818166BC, 0x8181684C, 0x818169E0, 0x81816B9C};
    static const uint32_t raInfo[4] = {0x818166EC, 0x8181687C, 0x81816A10, 0x81816BCC};
    static const uint32_t raPriority0[4] = {0x81816710, 0x818168A0, 0x81816A34, 0x81816BF0};
    static const uint32_t raPriority1[4] = {0x81816728, 0x818168B8, 0x81816A4C, 0x81816C08};
    static const uint32_t raPan[4] = {0x81816744, 0x818168D4, 0x81816A68, 0x81816C24};
    gptr scan = actor;
    uint32_t index = 0;
    R(3) = gm_u32(actor + 92); R(4) = actor + 100; R(5) = actor + 164; R(6) = 0;
    BL(raCalc[site], fn_8019ee20__9Snd2DCalcFRfRQ34nw4r4math4VEC2Ul_8019ECE0);
    while (index < gm_u32(actor + 84)) {
        R(4) = gm_u32(scan + 116);
        if (CMPS(R(4), 0) != 0) {
            R(3) = gm_u32(0x8042F680u - 20984);
            R(4) = R(4) ? gm_u32(R(4) + 156) : (uint32_t)-1;
            BL(raFlag[site], get3DCtrlFlag__11SndAudioMgrFUl_80196660);
            uint32_t flags = ~(R(3) | R(3));
            R(0) = flags & 1;
            if (R(0) != 0) {
                R(3) = gm_u32(scan + 116);
                ctx->f[1].d = ctx->ps1[1] = ldfs(base, actor + 100);
                if (R(3) != 0) { R(4) = 0; BL(raVolume0[site], SetVolume__Q44nw4r3snd6detail10BasicSoundFfi_80267420); }
            } else {
                R(3) = gm_u32(0x8042F680u - 20952); R(0) = gm_u32(R(3) + 20);
                int apply = R(0) == 3;
                if (!apply && R(0) == 2) apply = gm_u32(R(3) + 16) == 3;
                if (apply) {
                    R(3) = gm_u32(scan + 116);
                    ctx->f[1].d = ctx->ps1[1] = ldfs(base, actor + 100);
                    if (R(3) != 0) { R(4) = 0; BL(raVolume1[site], SetVolume__Q44nw4r3snd6detail10BasicSoundFfi_80267420); }
                }
            }
            R(0) = flags & 8;
            if (R(0) != 0) {
                R(4) = gm_u32(scan + 116); R(3) = gm_u32(0x8042F680u - 20984);
                R(3) = gm_u32(R(3) + 256); R(4) = R(4) ? gm_u32(R(4) + 156) : (uint32_t)-1;
                R(5) = R(1) + infoOffset[site];
                BL(raInfo[site], ReadSoundInfo__Q34nw4r3snd12SoundArchiveCFUlPQ44nw4r3snd12SoundArchive9SoundInfo_80275780);
                R(4) = gm_u32(actor + 104); R(3) = gm_u32(scan + 116);
                if ((int32_t)R(4) >= 0) {
                    R(4) += gm_u32(R(1) + infoOffset[site] + 12);
                    if (R(3) != 0) BL(raPriority0[site], SetPlayerPriority__Q44nw4r3snd6detail10BasicSoundFi_80267390);
                } else {
                    R(4) = gm_u32(R(1) + infoOffset[site] + 12);
                    if (R(3) != 0) BL(raPriority1[site], SetPlayerPriority__Q44nw4r3snd6detail10BasicSoundFi_80267390);
                }
            }
            R(0) = flags & 2;
            if (R(0) != 0) {
                R(3) = gm_u32(scan + 116); ctx->f[1].d = ctx->ps1[1] = ldfs(base, actor + 112);
                if (R(3) != 0) BL(raPan[site], SetPan__Q44nw4r3snd6detail10BasicSoundFf_802674C0);
            }
        }
        scan += 8; index++;
        if (index < gm_u32(actor + 84)) GM_LOOP();
    }
}

static void wmse_initialize(GM_CTX, gptr self) {
    I2_FN(0x81816380u);
    NV_R(30, self); R(6) = 30; R(4) = 0; R(3) = 121; R(5) = self - 16; ctx->ctr = R(6); R(6) = 1;
    do {
        R(5) += 52; gm_set_u32(R(5), R(3)); R(7) = WMSE_ZERO;
        gm_set_u32(R(5) + 4, 0); gm_set_u32(R(5) + 8, 0); gm_set_u32(R(5) + 12, 0);
        gm_set_u32(R(5) + 16, gm_u32(R(7))); gm_set_u32(R(5) + 20, gm_u32(R(7) + 4));
        gm_set_u32(R(5) + 24, gm_u32(R(7) + 8)); gm_set_u32(R(5) + 28, 0);
        gm_set_u32(R(5) + 32, 1); gm_set_u8(R(5) + 44, 0); gm_set_u32(R(5) + 48, 1);
        if (--ctx->ctr) GM_LOOP(); else break;
    } while (1);
    NV_R(28, self + 1592); NV_R(27, 8); NV_R(26, 0); NV_R(25, 0x80430000u);
    NV_R(24, 6); NV_R(23, WMSE_PLAYER_VT); NV_R(22, 0);
    do {
        R(3) = 184; BL(0x81816434u, mod___nw__FUl_818432E4); NV_R(29, R(3));
        R(3) = gm_u32(R(25) - 23416); R(4) = gm_u32(R(3) + 1468); R(3) = R(29);
        BL(0x81816448u, mfn_818161E8);
        R(28) += 4; gm_set_u32(R(28), R(29)); CMPU(R(22), 3);
        gm_set_u32(R(29) + 176, R(24)); gm_set_u8(R(29) + 180, R(26)); gm_set_u32(R(29), R(23));
        if (CR_BIT(ctx, 0)) gm_set_u32(R(28) - 1580, R(29));
        R(27)--; gm_set_u32(R(29) + 172, R(22)); CMPU(R(27), 0); R(22)++;
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
    R(3) = 184; BL(0x81816480u, mod___nw__FUl_818432E4); NV_R(28, 0x80430000u); NV_R(29, R(3));
    R(3) = gm_u32(R(28) - 23416); R(4) = gm_u32(R(3) + 1468); R(3) = R(29); BL(0x81816498u, mfn_818161E8);
    gm_set_u32(R(29) + 176, 6); gm_set_u32(R(29), WMSE_PLAYER_VT); gm_set_u32(self + 32, R(29));
    gm_set_u8(R(29) + 180, 0); gm_set_u32(R(29) + 172, 0);
    R(3) = 172; BL(0x818164C4u, mod___nw__FUl_818432E4); NV_R(29, R(3));
    R(3) = gm_u32(R(28) - 23416); R(4) = gm_u32(R(3) + 1468); R(3) = R(29); BL(0x818164D8u, mfn_818161E8);
    gm_set_u32(R(29), WMSE_MAP_VT); gm_set_u32(self + 4, R(29));
    R(3) = 380; BL(0x818164F0u, mod___nw__FUl_818432E4); NV_R(29, R(3));
    R(3) = gm_u32(R(28) - 23416); R(4) = gm_u32(R(3) + 1468); R(3) = R(29); BL(0x81816504u, mfn_81816284);
    gm_set_u32(R(29), WMSE_UI_VT); gm_set_u32(self + 8, R(29));
    R(3) = 380; BL(0x8181651Cu, mod___nw__FUl_818432E4); NV_R(29, R(3));
    R(3) = gm_u32(R(28) - 23416); R(4) = gm_u32(R(3) + 1468); R(3) = R(29); BL(0x81816530u, mfn_81816284);
    gm_set_u32(R(29), WMSE_FOOT_VT); gm_set_u32(self + 12, R(29));
}

static gptr wmse_construct(GM_CTX) {
    I2_FN(0x81816300u);
    R(3) = WMSE_SIZE; BL(0x81816320u, mod___nw__FUl_818432E4); NV_R(30, R(3));
    NV_R(29, R(30) + 36); NV_R(28, 30); gm_set_u32(R(30), WMSE_MANAGER_VT);
    do {
        R(3) = R(29); BL(0x81816340u, fn_80103EC0); R(28)--; CMPU(R(28), 0); R(29) += 52;
        if (CR_BIT(ctx, 1)) GM_LOOP(); else break;
    } while (1);
    ctx->lr = 0x81816358u; wmse_initialize(GM_PASS, R(30));
    gm_set_u32(WMSE_GLOBAL, R(30)); R(3) = R(30); return R(3);
}

static gptr wmse_destruct(GM_CTX, gptr self, int32_t flags) {
    I2_FN(0x81816574u);
    NV_R(30, self); CMPS(flags, 0); gm_set_u32(self, WMSE_MANAGER_VT);
    if (flags > 0) { R(3) = self; R(4) = WMSE_SIZE; BL(0x818165A8u, mfn_818434F4); }
    R(3) = self; return R(3);
}

static void wmse_playSlot(GM_CTX, gptr self, uint32_t index) {
    I2_FN(0x81816CE0u);
    NV_R(31, self); R(0) = index * 52; NV_R(30, self + R(0));
    ctx->f[0].d = ctx->ps1[0] = ldfs(base, 0x8042F680u - 9356);
    stfs(base, gm_frame_sp + 24, ctx->f[0].d); stfs(base, gm_frame_sp + 28, ctx->f[0].d);
    R(4) = gm_u32(R(30) + 40); R(5) = gm_u32(R(30) + 44);
    if (R(4) && R(5)) {
        R(3) = gm_frame_sp + 32; BL(0x81816D30u, fn_800FC4F0);
        ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 32); R(3) = gm_frame_sp + 16;
        stfs(base, R(30) + 52, ctx->f[0].d); R(4) = R(30) + 52;
        ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 36); stfs(base, R(30) + 56, ctx->f[0].d);
        ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 40); stfs(base, R(30) + 60, ctx->f[0].d);
        BL(0x81816D54u, fn_8006A5E0);
        ctx->f[1].d = ctx->ps1[1] = ldfs(base, gm_frame_sp + 16);
        ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 20);
        stfs(base, gm_frame_sp + 24, ctx->f[1].d); stfs(base, gm_frame_sp + 28, ctx->f[0].d);
    } else if (gm_u32(R(30) + 48)) {
        R(5) = gm_u32(R(30) + 48); ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(5)); R(3) = gm_frame_sp + 8;
        stfs(base, R(30) + 52, ctx->f[0].d); R(4) = R(30) + 52;
        ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(5) + 4); stfs(base, R(30) + 56, ctx->f[0].d);
        ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(5) + 8); stfs(base, R(30) + 60, ctx->f[0].d);
        BL(0x81816D98u, fn_8006A5E0);
        ctx->f[1].d = ctx->ps1[1] = ldfs(base, gm_frame_sp + 8);
        ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 12);
        stfs(base, gm_frame_sp + 24, ctx->f[1].d); stfs(base, gm_frame_sp + 28, ctx->f[0].d);
    }
    R(4) = gm_u32(R(30) + 36); R(3) = self; BL(0x81816DB4u, fn_801056C0);
    NV_R(29, R(3)); if (R(3) == 0) return;
    R(4) = gm_u32(R(30) + 36); R(3) = self; BL(0x81816DCCu, fn_80105A20);
    switch (R(3)) {
    case 0:
        R(4) = gm_u32(R(30) + 76); R(3) = self; BL(0x81816E4Cu, fn_80105B90);
        R(3) = gm_u32(R(30) + 72); BL(0x81816E54u, mfn_81806A30);
        R(0) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(4) = gm_u32(self + R(0) + 1596);
        gm_set_u32(R(4) + 176, R(3)); R(3) = gm_u32(R(30) + 64);
        if (R(3)) {
            R(5) = (uint32_t)(int16_t)gm_u16(R(3)); R(3) = R(4); R(4) = R(29); R(6) = 0;
            wmse_virtual(GM_PASS, R(3), 52, 0x81816E90u);
        } else {
            R(3) = R(4); R(4) = R(29); R(5) = 0; wmse_virtual(GM_PASS, R(3), 40, 0x81816EB0u);
        }
        break;
    case 1:
        if (gm_u32(R(30) + 36) == 12) {
            R(4) = gm_u32(R(30) + 76); R(3) = self; BL(0x81816E10u, fn_80105B90);
            R(5) = gm_u32(self + 32); gm_set_u32(R(5) + 176, R(3)); R(3) = R(5);
            R(5) = gm_u32(R(30) + 64); R(4) = R(29); R(6) = 0;
            R(5) = (uint32_t)(int16_t)gm_u16(R(5)); wmse_virtual(GM_PASS, R(3), 52, 0x81816E3Cu);
        } else {
            R(4) = gm_u32(R(30) + 76); R(3) = self; BL(0x81816E4Cu, fn_80105B90);
            R(3) = gm_u32(R(30) + 72); BL(0x81816E54u, mfn_81806A30);
            R(0) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(4) = gm_u32(self + R(0) + 1596);
            gm_set_u32(R(4) + 176, R(3)); R(3) = gm_u32(R(30) + 64);
            if (R(3)) {
                R(5) = (uint32_t)(int16_t)gm_u16(R(3)); R(3) = R(4); R(4) = R(29); R(6) = 0;
                wmse_virtual(GM_PASS, R(3), 52, 0x81816E90u);
            } else {
                R(3) = R(4); R(4) = R(29); R(5) = 0; wmse_virtual(GM_PASS, R(3), 40, 0x81816EB0u);
            }
        }
        break;
    case 2:
        R(3) = gm_u32(self + 12); R(4) = R(29); R(5) = 1; R(6) = gm_frame_sp + 24;
        if (gm_u32(R(30) + 64)) {
            R(5) = gm_u32(R(30) + 64); R(7) = (uint32_t)(int16_t)gm_u16(R(5)); R(5) = 1;
            R(8) = gm_u32(R(30) + 68); wmse_virtual(GM_PASS, R(3), 48, 0x81816EE8u);
        } else {
            R(7) = gm_u32(R(30) + 68); wmse_virtual(GM_PASS, R(3), 44, 0x81816F10u);
        }
        break;
    case 3:
        R(3) = gm_u32(self + 4); R(4) = R(29);
        if (gm_u32(R(30) + 64)) {
            R(5) = gm_u32(R(30) + 64); R(5) = (uint32_t)(int16_t)gm_u16(R(5));
            R(6) = gm_u32(R(30) + 68); wmse_virtual(GM_PASS, R(3), 52, 0x81816F40u);
        } else {
            R(5) = gm_u32(R(30) + 68); wmse_virtual(GM_PASS, R(3), 40, 0x81816F60u);
        }
        break;
    case 4:
        R(3) = gm_u32(self + 8); R(4) = R(29); R(6) = gm_frame_sp + 24;
        R(5) = gm_u32(R(30) + 84); R(7) = gm_u32(R(30) + 68);
        wmse_virtual(GM_PASS, R(3), 44, 0x81816F88u);
        break;
    case 5:
        R(3) = gm_u32(0x8042F680u - 20984); R(4) = R(29); R(5) = 1;
        BL(0x81816F9Cu, fn_80195390);
        break;
    default: break;
    }
}

static void wmse_playPlyVoice(GM_CTX, gptr self, uint32_t character, uint32_t variant) {
    I2_FN(0x81816FB8u);
    NV_R(27, character); NV_R(28, self); NV_R(30, variant); BL(0x81816FE4u, fn_80105AB0);
    CMPU(R(3), 71); if (CR_BIT(ctx, 2)) return;
    NV_R(29, R(3)); R(3) = R(27); BL(0x81816FF8u, mfn_81806A30);
    R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; NV_R(27, gm_u32(self + R(3) + 1596));
    R(3) = self; R(4) = R(30); BL(0x81817010u, fn_80105B90); gm_set_u32(R(27) + 176, R(3));
    R(3) = R(27); R(4) = R(29); R(5) = 0; BL(0x81817024u, mod_fn_8019AAB0__11SndObjctPlyFUli_8183C888);
}

static void wmse_playPlySound(GM_CTX, gptr self, uint32_t id, uint32_t character,
                              uint32_t action, uint32_t variant) {
    I2_FN(0x81817044u);
    NV_R(26, id); NV_R(27, action); NV_R(29, self); NV_R(30, character); ctx->f[31].u = ctx->f[1].u;
    BL(0x81817080u, fn_801056C0); CMPU(R(3), 0); if (CR_BIT(ctx, 2)) return;
    NV_R(28, R(3)); R(3) = R(30); BL(0x81817094u, mfn_81806A30);
    R(3) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; NV_R(30, gm_u32(self + R(3) + 1596));
    R(3) = self; R(4) = R(27); BL(0x818170ACu, fn_80105B90); gm_set_u32(R(30) + 176, R(3));
    R(3) = self; R(4) = R(26); BL(0x818170BCu, fn_80105A20);
    if (R(3) == 1) {
        if (action < 5) { R(3) = self; R(4) = 24; BL(0x81817100u, fn_801056C0); NV_R(28, R(3)); }
        R(3) = R(30); R(4) = R(28); ctx->f[1].u = ctx->f[31].u; R(5) = 0;
        BL(0x81817118u, startFootSound__11SndObjctPlyFUlfUl_8019A6D0); return;
    }
    if (R(3) != 0) return;
    if (id == 1) {
        if (action == 0) { R(4) = 2; R(3) = self; BL(0x81817140u, fn_801056C0); NV_R(28, R(3)); }
        else if (action < 3) { R(4) = 3; R(3) = self; BL(0x81817140u, fn_801056C0); NV_R(28, R(3)); }
    } else if (id == 8 && action == 5) {
        R(4) = 13; R(3) = self; BL(0x81817140u, fn_801056C0); NV_R(28, R(3));
    }
    R(3) = R(30); R(4) = R(28); R(5) = 0; BL(0x81817154u, fn_801051B0);
}

static void wmse_execute(GM_CTX, gptr self) {
    I2_FN(0x818165C0u);
    R(11) = gm_frame_sp + 208; BL(0x818165D4u, __save_gpr_entry_802DCD70);
    NV_R(30, self); R(4) = gm_u32(0x8042F680u - 21728); NV_R(31, gm_u32(self + 1596));
    R(3) = gm_frame_sp + 24; R(4) += 172; BL(0x818165ECu, fn_8006A5E0);
    ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 24); stfs(base, R(31) + 164, ctx->f[0].d);
    ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 28); stfs(base, R(31) + 168, ctx->f[0].d);
    uint32_t outer = 0;
    do {
        R(3) = R(31); R(4) = outer; BL(0x8181660Cu, GetPlayingSoundCount__Q34nw4r3snd10SoundActorCFi_80275560);
        if ((int32_t)R(3) > 0) { wmse_updateActor(GM_PASS, R(31), 0); break; }
        outer++; if (outer < 8) GM_LOOP();
    } while (outer < 8);
    if ((int16_t)gm_u16(0x8042F680u - 21730) == 1) {
        NV_R(29, gm_u32(self + 32)); ctx->f[0].d = ctx->ps1[0] = ldfs(base, 0x8042F680u - 9356);
        stfs(base, R(29) + 164, ctx->f[0].d); stfs(base, gm_frame_sp + 40, ctx->f[0].d);
        stfs(base, gm_frame_sp + 44, ctx->f[0].d); stfs(base, R(29) + 168, ctx->f[0].d);
        outer = 0;
        do {
            R(3) = R(29); R(4) = outer; BL(0x8181679Cu, GetPlayingSoundCount__Q34nw4r3snd10SoundActorCFi_80275560);
            if ((int32_t)R(3) > 0) { wmse_updateActor(GM_PASS, R(29), 1); break; }
            outer++; if (outer < 4) GM_LOOP();
        } while (outer < 4);
    } else {
        R(4) = gm_u32(0x8042F680u - 21728); R(3) = gm_frame_sp + 16; NV_R(29, gm_u32(self + 32));
        R(4) += 172; BL(0x81816910u, fn_8006A5E0);
        ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 16); stfs(base, R(29) + 164, ctx->f[0].d);
        ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 20); stfs(base, R(29) + 168, ctx->f[0].d);
        outer = 0;
        do {
            R(3) = R(29); R(4) = outer; BL(0x81816930u, GetPlayingSoundCount__Q34nw4r3snd10SoundActorCFi_80275560);
            if ((int32_t)R(3) > 0) { wmse_updateActor(GM_PASS, R(29), 2); break; }
            outer++; if (outer < 4) GM_LOOP();
        } while (outer < 4);
    }
    R(3) = gm_u32(0x8042F680u - 21728); NV_R(31, gm_u32(R(3) + 388));
    while (R(31)) {
        if (gm_u8(R(31) + 292)) {
            R(5) = gm_u32(gm_u32(R(31) + 460) + 4); R(3) = gm_u8(R(5) + 337); BL(0x81816AB4u, mfn_81806A30);
            R(0) = i2_rotl(R(3), 2) & 0xFFFFFFFCu; R(5) = self + R(0); NV_R(29, gm_u32(R(5) + 1596));
            R(3) = gm_frame_sp + 8; R(4) = R(31) + 172; BL(0x81816ACCu, fn_8006A5E0);
            ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 8); stfs(base, R(29) + 164, ctx->f[0].d);
            ctx->f[0].d = ctx->ps1[0] = ldfs(base, gm_frame_sp + 12); stfs(base, R(29) + 168, ctx->f[0].d);
            outer = 0;
            do {
                R(3) = R(29); R(4) = outer; BL(0x81816AECu, GetPlayingSoundCount__Q34nw4r3snd10SoundActorCFi_80275560);
                if ((int32_t)R(3) > 0) { wmse_updateActor(GM_PASS, R(29), 3); break; }
                outer++; if (outer < 4) GM_LOOP();
            } while (outer < 4);
        }
        NV_R(31, gm_u32(R(31) + 388)); if (R(31)) GM_LOOP();
    }
    R(3) = gm_u8(0x8042F680u - 21555); BL(0x81816C5Cu, fn_800FD180); R(3) &= 0xFFFF; R(4) = 0;
    BL(0x81816C68u, hle_search__7fBase_cF6ActorsP7fBase_c);
    if (R(3)) {
        R(4) = R(3); R(3) = gm_frame_sp + 32; R(4) += 172; BL(0x81816C80u, fn_8006A5E0);
        R(3) = gm_u32(self + 4); R(4) = gm_frame_sp + 32; wmse_virtual(GM_PASS, R(3), 32, 0x81816C98u);
    }
    NV_R(28, self); NV_R(26, 0);
    do {
        if (gm_u8(R(28) + 80)) wmse_playSlot(GM_PASS, self, R(26));
        R(26)++; R(28) += 52; if (R(26) < 30) GM_LOOP();
    } while (R(26) < 30);
    R(11) = gm_frame_sp + 208; BL(0x81816CD0u, __restore_gpr_entry_802DCDBC);
}

GM_HLE_VERIFIED_(mod_fn_80103E40, GMV_IGNORE_POLLS, 0, 0) { R(3) = wmse_construct(GM_PASS); }
GM_HLE_VERIFIED_(mod_fn_801040D0, GMV_IGNORE_POLLS, 0, 0) { R(3) = wmse_destruct(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_80104140, GMV_IGNORE_POLLS, 0, 0) { wmse_initialize(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_801045A0, GMV_IGNORE_POLLS, 0, 0) { wmse_execute(GM_PASS, GM_ARG(0)); }
GM_HLE_VERIFIED_(mod_fn_80104CC0, GMV_IGNORE_POLLS, 0, 0) { wmse_playSlot(GM_PASS, GM_ARG(0), GM_ARG(1)); }
GM_HLE_VERIFIED_(mod_fn_80104FD0, GMV_IGNORE_POLLS, 0, 0) { wmse_playPlyVoice(GM_PASS, GM_ARG(0), GM_ARG(2), GM_ARG(3)); }
GM_HLE_VERIFIED_(mod_fn_80105060, GMV_IGNORE_POLLS, 0, 0) { wmse_playPlySound(GM_PASS, GM_ARG(0), GM_ARG(1), GM_ARG(2), GM_ARG(3), GM_ARG(4)); }
