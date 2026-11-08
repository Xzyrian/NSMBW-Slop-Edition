/* gm_d_actorcreate.c - dActorCreateMng_c, which creates the course's actors (sprites) as they come
 * into view: the first fill of a zone (MapActorInitialCreate), the per-frame check of the scroll
 * edge (MapActorScroolCreateCheck / MapActorScrollCreate), the spawn itself (mapActorSpawn: the Z
 * position counters, the event flags, dActor_c::construct) and the small helpers. Track B (gm.h,
 * docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_actorcreate_manager.cpp) and checked against
 * the recompiled USA rev 2 code (0x80068040-0x8006901C). Written register-exact
 * (RT_GM_VERIFY_REGS=1): the PowerPC registers are the variables here (R(n), named below per
 * function), so the non-volatile ones are what the callees save and the volatile ones end as the
 * original leaves them; the compiler's own order is kept where it shows (the stack slots of the
 * float-to-int conversions, the tile shifts' XER[CA]).
 *
 * dActorCreateMng_c: +0 / +4 / +8 / +12 the Z position counters (actors, layer 2, map objects,
 * map objects layer 2), +16 the delete values (u16 x 1000), +2016 the spawn flags (u8 x 1000,
 * bit 0 spawned), +3016 Yoshi colour, +3018 ending demo, +3019 goal pole demo, +3020 / +3024 the
 * screen's left / top, +3028 / +3032 the last scroll boundary tiles X / Y.
 * The actor info table (dActorData_c, 40 bytes per sprite ID at 0x8030A040): +0 profile, +4 / +8
 * spawn offset x / y, +12 / +16 range offset x / y, +20 / +24 range half width / height, +28 ..
 * +34 the four margins (u16), +36 flags (u16: 2 global, 8 map object, 0x10 groupable).
 * A map actor (16 bytes): +0 sprite ID, +2 x, +4 y, +6 event IDs, +8 parameter, +12 area, +13 layer. */
#include "gm.h"
#include "gm_nv.h"

#define R(n) ctx->r[n]
#define F(n) ctx->f[n].d
#define LF(a) ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
#define CTIW(dst, src) (ctx->f[dst].u = fctiw_bits(ctx->f[src].d, 1))      /* fctiwz (ps0) */
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int rec0(ppc_context *ctx, uint32_t v) { cr_cmp_s(ctx, 0, (int32_t)v, 0); return v != 0; }   /* andi. */
static inline uint32_t srawi(ppc_context *ctx, uint32_t v, int s) {      /* srawi: XER[CA] when a negative value loses 1 bits */
    int32_t x = (int32_t)v; ctx->xer_ca = x < 0 && (x & ((1 << s) - 1)) != 0; return (uint32_t)(x >> s);
}

#define SDA_GAME_FLAG 22272              /* (r13 - 22272: dInfo_c::mGameFlag, bit 0 no actor creation) */
#define SDA_BG_PARAM  22656              /* dBgParameter_c::ms_Instance_p (+56 / +60 pos, +64 / +68 size, +128 / +129 scroll directions) */
#define SDA_STAGE     21688              /* dScStage_c::m_instance (+4622 course file, +4623 area) */
#define SDA_CD        22504              /* dCd_c::m_instance (944 bytes per course file) */
#define SDA_BG        22704              /* dBg_c::m_bg_p (+0x90000 +12 / +20: the display scale now / before) */
#define SDA_GROUP_MNG 22864              /* dActorGroupIdMng_c::m_instance */
#define SDA_READ_KEEP 22892              /* dActor_c::m_read_p_keep; - 22888 m_flag_keep (2 bytes), - 22880 / - 22876 m_flagbit_keep (u64), - 22872 m_mbgchoice_keep */
#define ACTOR_INFO    (0x80310000u - 24512u)   /* dActorData_c's table (0x8030A040) */
#define GO_AHEAD_LIST 0x802EF388u        /* l_GoAheadEnemy (u16, 0xFFFF-terminated) */
#define F_ABS         0x802DE514u
#define F_SHL2I       0x802DD1ECu        /* __shl2i (64-bit shift) */
#define F_GROUP_PROC  0x800661C0u        /* dActorGroupIdMng_c::process */
#define F_AREA_NO_BOX 0x8008E800u        /* dCdFile_c::getAreaNo(sRangePosSize *) */
#define F_CONSTRUCT   0x80064610u        /* dActor_c::construct(profile, param, pos, angle, layer) */
#define DUMMY_ACTOR   0x2EB
#define MAC_DELETE    16
#define MAC_SPAWN     2016

/* the current course file (dCd_c::getFileP: null when it has no areas) - into rd */
static gptr course_file(GM_CTX, int rd, int rs, int rt) {
    R(rs) = gm_u32(R(13) - SDA_STAGE);
    R(rt) = gm_u32(R(13) - SDA_CD);
    R(0) = gm_u8(R(rs) + 4622) * 944u;
    R(rd) = R(rt) + R(0);
    R(0) = gm_u32(R(rd) + 44);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(rd) = 0;
    return R(rd);
}

/* ================================================================== the small ones */
/* ActorCreateInfoClear() */
static void acm_info_clear(GM_CTX, gptr m) {
    R(0) = 0;
    gm_set_u16(m + 3016, 0); gm_set_u8(m + 3018, 0); gm_set_u8(m + 3019, 0);
    for (int i = 0; i < 4; i++) gm_set_u32(m + 4 * i, 0);
}
/* ScroolAreaInCheck(boundsEdge, areaEdge, boundMin, boundMax, areaMin, areaMax): the same edge
   and the ranges overlap */
static uint32_t acm_area_in(GM_CTX) {
    if (cmps(ctx, (int32_t)R(4), (int32_t)R(5)) != 0) return R(3) = 0;
    int lt = cmps(ctx, (int32_t)R(7), (int32_t)R(8)) < 0;
    R(3) = 0;
    if (lt) return 0;
    if (cmps(ctx, (int32_t)R(6), (int32_t)R(9)) > 0) return 0;
    return R(3) = 1;
}
/* GlobalActorCheck(data): the sprite is one of l_GoAheadEnemy */
static uint32_t acm_global(GM_CTX, gptr data) {
       R(3) = GO_AHEAD_LIST; R(7) = 0;
    for (int first = 1;; first = 0) {
        if (!first) {
            R(0) = gm_u16(data);
            if (cmpu(ctx, R(0), R(6)) == 0) break;
            R(7)++;
        }
        R(5) = (R(7) << 1) & 0x1FFFEu;
        R(6) = gm_u16(R(3) + R(5));
        if (cmpu(ctx, R(6), 0xFFFFu) == 0) break;
        GM_LOOP();
    }
    R(3) = GO_AHEAD_LIST;
    R(0) = gm_u16(R(3) + R(5));
    return R(3) = cmpu(ctx, R(0), 0xFFFFu) != 0;
}
/* processGroupId(data, file, index): to dActorGroupIdMng_c::process(data, group ID, file, index) - a tail call */
static void acm_group(GM_CTX, gptr data, uint32_t file, uint32_t idx) {
       R(0) = gm_u32(data + 8);
    R(7) = idx; R(3) = gm_u32(R(13) - SDA_GROUP_MNG); R(6) = file;
    R(5) = R(0) >> 24;
    R(4) = data;
    ppc_call_indirect(ctx, base, F_GROUP_PROC);
}
/* GroupIdCheck(param): no group ID (the top byte) */
static uint32_t acm_no_group(GM_CTX, uint32_t param) {
       R(0) = param >> 24;
    R(0) = cntlzw(R(0));
    return R(3) = R(0) >> 5;
}
/* the Z position counters: inc (wrap at 30) and add (the position from the count, then inc) */
static void acm_zinc(GM_CTX, gptr m, int k) {
       R(4) = gm_u32(m + 4 * k);
    R(0) = R(4) + 1;
    gm_set_u32(m + 4 * k, R(0));
    if (cmps(ctx, (int32_t)R(0), 30) < 0) return;
    R(0) = 0;
    gm_set_u32(m + 4 * k, 0);
}
static double acm_zadd(GM_CTX, gptr m, int k) {
       static const uint32_t fn[4] = { 0x80068BC0u, 0x80068C50u, 0x80068CE0u, 0x80068D70u };   /* FNADDR */
    static const uint32_t ra[4] = { 0x80068C08u, 0x80068C98u, 0x80068D28u, 0x80068DB8u };
    static const int k_step[4] = { 29884, 29884, 29864, 29864 }, k_start[4] = { 29888, 29872, 29868, 29860 };
    GM_FN(fn[k]); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    gptr f = gm_frame_sp;
    R(4) = gm_u32(m + 4 * k);
    R(0) = 0x43300000u;
    gm_set_u32(f + 8, R(0));
    R(0) = R(4) ^ 0x80000000u;
    ctx->f[3].u = ld64(base, R(2) - 29880);
    gm_set_u32(f + 12, R(0));
    FB(1, LF(R(2) - k_step[k]));
    ctx->f[2].u = ld64(base, f + 8);
    FB(0, LF(R(2) - k_start[k]));
    FB(2, frsp(F(2) - F(3)));
    FB(1, frsp(F(1) * F(2)));
    FB(31, k == 1 ? frsp(F(0) + F(1)) : frsp(F(0) - F(1)));        /* 1900 - 16n, -2500 + 16n, 400 - 8n, -3100 - 8n */
    NCALL(ra[k], acm_zinc(GM_PASS, m, k));
    ctx->f[1].u = ctx->f[31].u;
    R(0) = lr;
    return F(1);
}

/* ================================================================== mapActorSpawn
   (data, info, spawn flag, delete value, area): the actor at its position, the event bits kept
   for its constructor, its fields set from the map data */
static gptr acm_spawn(GM_CTX, gptr m, gptr data, gptr info, gptr flag, gptr del, uint32_t area) {
       GM_FN(0x80068DE0); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    gptr f = gm_frame_sp, actor = 0;
    R(0) = gm_u16(data);
    R(10) = 0x43300000u; R(9) = ACTOR_INFO;
    gm_set_u32(f + 24, R(10));
    R(0) *= 40;
    NV_R(27, data);
    gm_set_u32(f + 32, R(10));
    NV_R(28, info);
    R(0) = gm_u16(R(9) + R(0));
    NV_R(29, flag); NV_R(30, del);
    int dummy = cmpu(ctx, R(0), DUMMY_ACTOR) == 0;
    NV_R(31, area);
    if (!dummy) {
        R(3) = m;
        R(0) = gm_u16(info + 36) & 8;
        int mapobj = rec0(ctx, R(0));
        R(0) = gm_u8(data + 13);
        int layer2 = cmps(ctx, (int32_t)R(0), 0) != 0;
        int k = mapobj ? (layer2 ? 3 : 2) : (layer2 ? 1 : 0);
        static const uint32_t ra[4] = { 0x80068E78u, 0x80068E70u, 0x80068E5Cu, 0x80068E54u };
        NCALL(ra[k], acm_zadd(GM_PASS, m, k));
        /* the position (x + spawn offset x, -(y - spawn offset y), z) at f+8 */
        R(7) = gm_u32(info + 8); R(3) = R(13) - 22888;
        R(6) = gm_u16(data + 4); R(0) = 0;
        R(5) = gm_u16(data + 2); R(4) = gm_u32(info + 4);
        R(6) = R(6) - R(7);
        R(6) = (uint32_t)-(int32_t)R(6);
        ctx->f[2].u = ld64(base, R(2) - 29880);
        R(4) = R(5) + R(4);
        SF(f + 16, F(1));
        R(5) = R(6) ^ 0x80000000u; gm_set_u32(f + 28, R(5));
        R(4) = R(4) ^ 0x80000000u; gm_set_u32(f + 36, R(4));
        ctx->f[1].u = ld64(base, f + 24);
        ctx->f[0].u = ld64(base, f + 32);
        FB(1, frsp(F(1) - F(2)));
        gm_set_u32(R(13) - SDA_READ_KEEP, flag);
        FB(0, frsp(F(0) - F(2)));
        SF(f + 12, F(1)); SF(f + 8, F(0));
        R(4) = gm_u16(data + 6); gm_set_u16(R(13) - 22888, (uint16_t)R(4));
        R(4) = gm_u8(data + 13);
        R(3) = gm_u8(R(3) + 1);
        gm_set_u8(R(13) - 22872, (uint8_t)R(4));
        int e1 = cmps(ctx, (int32_t)R(3), 0) != 0;
        NV_R(26, gm_u8(R(13) - 22888));
        gm_set_u32(R(13) - 22876, 0); gm_set_u32(R(13) - 22880, 0);
        if (e1) {                                            /* m_flagbit_keep = 1 << (event - 1) (__shl2i) */
            R(5) = R(3) - 1; R(4) = 1; R(3) = 0;
            GM_CALLV(0x80068F08u, F_SHL2I, 0);
            gm_set_u32(R(13) - 22876, R(4)); gm_set_u32(R(13) - 22880, R(3));
        }
        if (cmps(ctx, (int32_t)R(26), 0) != 0) {
            R(5) = R(26) - 1; R(4) = 1; R(3) = 0;
            GM_CALLV(0x80068F28u, F_SHL2I, 0);
            gm_set_u32(R(13) - 22876, R(4)); gm_set_u32(R(13) - 22880, R(3));
        }
        R(0) = gm_u16(data);
        R(3) = ACTOR_INFO;
        R(4) = gm_u32(data + 8);
        R(0) *= 40;
        R(7) = gm_u8(data + 13);
        R(5) = f + 8; R(6) = 0;
        R(3) = gm_u16(R(3) + R(0));
        actor = GM_CALLV(0x80068F58u, F_CONSTRUCT, 0);
        if (cmps(ctx, (int32_t)actor, 0) != 0) {
            R(0) = gm_u16(data);
            if (cmpu(ctx, R(0), 10) >= 0) {
                gm_set_u8(actor + 841, (uint8_t)area);
                R(0) = 0;
                FB(0, LF(R(2) - 29856));
                gm_set_u32(actor + 844, flag); gm_set_u32(actor + 848, del);
                R(4) = gm_u16(R(13) - 22888); gm_set_u16(actor + 852, (uint16_t)R(4));
                R(4) = gm_u32(R(13) - 22880); R(5) = gm_u32(R(13) - 22876);
                gm_set_u32(actor + 860, R(5)); gm_set_u32(actor + 856, R(4));
                gm_set_u8(actor + 870, 0);
                R(0) = gm_u16(info + 36); gm_set_u16(actor + 868, (uint16_t)R(0));
                FB(1, LF(actor + 792));
                cr_fcmp(ctx, 0, F(1), F(0));
                if (F(1) == F(0)) {
                    FB(1, LF(actor + 796));
                    cr_fcmp(ctx, 0, F(1), F(0));
                    if (F(1) == F(0)) {                      /* no visible area: the spawn range */
                        R(0) = gm_u32(info + 20); R(4) = gm_u32(info + 24);
                        R(0) ^= 0x80000000u; gm_set_u32(f + 36, R(0));
                        R(0) = R(4) ^ 0x80000000u;
                        ctx->f[3].u = ld64(base, R(2) - 29880);
                        gm_set_u32(f + 28, R(0));
                        ctx->f[0].u = ld64(base, f + 32);
                        ctx->f[2].u = ld64(base, f + 24);
                        FB(0, frsp(F(0) - F(3)));
                        FB(1, LF(R(2) - 29852));
                        FB(2, frsp(F(2) - F(3)));
                        FB(0, frsp(F(1) * F(0)));
                        FB(1, frsp(F(1) * F(2)));
                        SF(actor + 792, F(0)); SF(actor + 796, F(1));
                    }
                }
            }
            R(0) = gm_u8(flag) | 1;
            gm_set_u8(flag, (uint8_t)R(0));
        }
    }
    R(11) = f + 64;
    R(0) = lr;
    return R(3) = actor;
}

/* ================================================================== MapActorInitialCreate
   (data, delete values, spawn flags, count, zone reload): every actor of the list whose spawn
   range touches the screen (grown by 32-64) and whose area is the current one - on a zone
   reload, every ungrouped one */
static void acm_initial(GM_CTX) {
       GM_FN(0x80068320); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    gptr f = gm_frame_sp;
#define M       R(15)     /* this */
#define DATA    R(16)
#define DEL     R(17)
#define FLAG    R(18)
#define COUNT   R(19)
#define RELOAD  R(14)
#define I       R(22)
#define FILE_   R(21)
#define STAGE   R(27)
#define INFO    R(28)
#define AREA    R(29)
#define HALF_H  R(26)
#define HALF_W  R(25)
    int zero = cmps(ctx, (int32_t)R(7), 0) == 0;
    M = R(3); DATA = R(4); DEL = R(5); FLAG = R(6); COUNT = R(7); RELOAD = R(8);
    if (zero || cmps(ctx, (int32_t)R(4), 0) == 0) goto out;
    /* the screen box: top - 32 .. bottom + 48, left - 48 .. right + 64 */
    R(3) = gm_u32(R(13) - SDA_BG_PARAM);
    I = 0;
    STAGE = gm_u32(R(13) - SDA_STAGE);
    FB(0, LF(R(3) + 60)); FB(1, LF(R(3) + 68));
    CTIW(0, 0);
    FB(2, LF(R(3) + 56)); FB(3, LF(R(3) + 64));
    CTIW(1, 1);
    st64(base, f + 24, ctx->f[0].u);
    CTIW(2, 2);
    R(0) = gm_u8(STAGE + 4622);
    CTIW(0, 3);
    R(4) = gm_u32(f + 28);
    st64(base, f + 16, ctx->f[2].u);
    R(0) *= 944;
    R(3) = gm_u32(R(13) - SDA_CD);
    R(6) = (uint32_t)-(int32_t)R(4);                         /* screen top */
    st64(base, f + 32, ctx->f[1].u);
    FILE_ = R(3) + R(0);
    R(5) = gm_u32(f + 20);                                   /* screen left */
    st64(base, f + 40, ctx->f[0].u);
    R(7) = R(6) - 32;
    R(4) = gm_u32(f + 36);
    R(0) = gm_u32(FILE_ + 44);
    R(4) = R(6) + R(4);
    R(3) = gm_u32(f + 44);
    R(4) += 48;
    int no_areas = cmps(ctx, (int32_t)R(0), 0) == 0;
    R(6) = R(5) + R(3);
    R(5) -= 48;
    R(3) = R(4) - R(7);
    R(6) += 64;
    HALF_H = srawi(ctx, R(3), 1);
    R(0) = R(6) - R(5);
    HALF_W = srawi(ctx, R(0), 1);
    R(0) = R(7) + HALF_H; gm_set_u32(f + 52, R(0));          /* centre y */
    R(0) = R(5) + HALF_W; gm_set_u32(f + 48, R(0));          /* centre x */
    if (no_areas) FILE_ = 0;
    R(3) = gm_u32(R(13) - SDA_STAGE);
    R(30) = ACTOR_INFO;
    AREA = gm_u8(R(3) + 4623);
    while (cmpu(ctx, I, COUNT) != 0) {
        GM_LOOP();
        R(0) = gm_u8(FLAG) & 1;
        if (!rec0(ctx, R(0))) {
            R(0) = gm_u16(DATA);
            int reload = cmps(ctx, (int32_t)RELOAD, 0) != 0;
            R(20) = 0; R(23) = 0;                            /* r20: spawn it, r23: can spawn */
            R(0) *= 40;
            INFO = R(30) + R(0);
            if (!reload) {
                R(0) = gm_u16(INFO + 36);
                R(24) = 0;                                   /* grouped */
                R(0) &= 0x10;
                if (rec0(ctx, R(0))) {
                    R(4) = gm_u32(DATA + 8); R(3) = M;
                    if (cmps(ctx, (int32_t)NCALL(0x80068464u, acm_no_group(GM_PASS, R(4))), 0) == 0) {
                        R(5) = gm_u8(STAGE + 4622); R(3) = M; R(4) = DATA; R(6) = I;
                        NCALL(0x80068480u, acm_group(GM_PASS, DATA, R(5), I));
                        R(24) = 1;
                    }
                } else {
                    R(3) = M; R(4) = DATA;
                    if (cmps(ctx, (int32_t)NCALL(0x80068494u, acm_global(GM_PASS, DATA)), 0) != 0) R(20) = 1;
                }
                if (cmps(ctx, (int32_t)R(24), 0) == 0) {     /* the spawn range's area */
                    R(0) = gm_u16(DATA + 2); R(3) = FILE_;
                    gm_set_u16(f + 8, (uint16_t)R(0));
                    R(4) = f + 8;
                    R(5) = gm_u32(INFO + 20); R(6) = gm_u16(DATA + 4);
                    R(0) = gm_u32(INFO + 24);
                    R(5) = (R(5) << 1) & 0xFFFEu;
                    gm_set_u16(f + 10, (uint16_t)R(6));
                    R(0) = (R(0) << 1) & 0xFFFEu;
                    gm_set_u16(f + 12, (uint16_t)R(5)); gm_set_u16(f + 14, (uint16_t)R(0));
                    GM_CALLV(0x800684DCu, F_AREA_NO_BOX, 0);
                    R(0) = R(3) & 0xFFu;
                    if (cmpu(ctx, AREA, R(0)) == 0) R(23) = 1;
                }
            } else {
                R(0) = gm_u16(INFO + 36) & 0x10;
                if (rec0(ctx, R(0))) {
                    R(4) = gm_u32(DATA + 8); R(3) = M;
                    if (cmps(ctx, (int32_t)NCALL(0x80068508u, acm_no_group(GM_PASS, R(4))), 0) != 0) R(23) = 1;
                } else R(23) = 1;
            }
            if (cmps(ctx, (int32_t)R(20), 0) == 0 && cmps(ctx, (int32_t)R(23), 0) != 0) {
                R(0) = gm_u16(INFO + 36) & 2;
                if (rec0(ctx, R(0))) R(20) = 1;              /* global: always */
                else {                                       /* the boxes touch */
                    R(4) = gm_u16(INFO + 28); R(3) = gm_u16(INFO + 30);
                    R(0) = gm_u32(INFO + 20);
                    R(5) = R(4) + R(3);
                    R(4) = gm_u16(INFO + 32); R(3) = gm_u16(INFO + 34);
                    R(6) = srawi(ctx, R(5), 1);
                    R(7) = gm_u32(INFO + 24);
                    R(0) = HALF_W + R(0);
                    R(3) = R(4) + R(3);
                    R(5) = gm_u32(INFO + 16);
                    R(4) = gm_u16(DATA + 4);
                    R(3) = srawi(ctx, R(3), 1);
                    R(23) = R(7) + R(6);
                    R(24) = R(4) - R(5);
                    R(3) = R(3) + R(0);
                    GM_CALLV(0x80068584u, F_ABS, 0);
                    R(4) = gm_u16(DATA + 2);
                    R(31) = R(3);
                    R(0) = gm_u32(INFO + 12);
                    R(3) = R(4) + R(0);
                    R(0) = gm_u32(f + 48);
                    R(3) = R(0) - R(3);
                    GM_CALLV(0x800685A0u, F_ABS, 0);
                    if (cmps(ctx, (int32_t)R(3), (int32_t)R(31)) <= 0) {
                        R(3) = HALF_H + R(23);
                        GM_CALLV(0x800685B0u, F_ABS, 0);
                        R(0) = gm_u32(f + 52);
                        R(23) = R(3);
                        R(3) = R(0) - R(24);
                        GM_CALLV(0x800685C0u, F_ABS, 0);
                        if (cmps(ctx, (int32_t)R(3), (int32_t)R(23)) <= 0) R(20) = 1;
                    }
                }
            }
            if (cmps(ctx, (int32_t)R(20), 0) != 0) {
                R(3) = M; R(4) = DATA; R(5) = INFO; R(6) = FLAG; R(7) = DEL; R(8) = AREA;
                NCALL(0x800685F0u, acm_spawn(GM_PASS, M, DATA, INFO, FLAG, DEL, AREA));
            }
        }
        DATA += 16; FLAG += 1; DEL += 2; I += 1;
    }
out:
    R(11) = f + 128;
    R(0) = lr;
#undef M
#undef DATA
#undef DEL
#undef FLAG
#undef COUNT
#undef RELOAD
#undef I
#undef FILE_
#undef STAGE
#undef INFO
#undef AREA
#undef HALF_H
#undef HALF_W
}

/* ================================================================== MapActorScrollCreate
   (bounds, screen scroll): the actors whose tile edge is the new scroll boundary and whose other
   axis overlaps the screen's (bounds: +0 / +4 boundary tiles X / Y, +8 left, +12 right, +16 top,
   +20 bottom, +24 / +28 scroll directions X / Y: -1, 0 (none: 1), 1) */
static void acm_scroll_create(GM_CTX) {
    GM_FN(0x80068850); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    gptr f = gm_frame_sp;
#define M      R(15)
#define DATA   R(30)
#define FLAG   R(29)
#define I      R(14)
#define INFO   R(31)
#define B_X    R(21)      /* bounds: the X / Y boundary tiles from the frame (f+20 / f+16), left .. bottom, the directions */
#define B_L    R(20)
#define B_R    R(19)
#define B_T    R(18)
#define B_B    R(17)
#define DIR_X  R(17)
#define DIR_Y  R(16)
    R(7) = gm_u32(R(13) - SDA_STAGE);
    M = R(3);
    gm_set_u32(f + 8, R(5));                                 /* screen scroll */
    R(5) = gm_u8(R(7) + 4622);
    R(0) = gm_u8(R(7) + 4623);
    gm_set_u8(f + 32, (uint8_t)R(0));                        /* the area */
    R(0) = R(5) * 944;
    R(6) = gm_u32(R(13) - SDA_CD);
    R(5) = R(6) + R(0);
    R(0) = gm_u32(R(5) + 44);
    if (cmps(ctx, (int32_t)R(0), 0) == 0) R(5) = 0;
    R(0) = (gm_u8(f + 32) << 2) & 0x3FCu;
    R(5) += R(0);
    R(0) = gm_u32(R(5) + 432);                               /* the area's actor count */
    gm_set_u32(f + 28, R(0));
    if (cmps(ctx, (int32_t)R(0), 0) == 0) goto out;
    DATA = gm_u32(R(5) + 176);
    if (cmps(ctx, (int32_t)DATA, 0) == 0) goto out;
    R(0) = 0x80310000u;
    gm_set_u32(f + 36, R(0));
    R(6) = gm_u32(R(5) + 688);                               /* the area's first index */
    I = 0;
    R(0) = gm_u32(R(4) + 0);
    R(5) = gm_u32(f + 36);
    gm_set_u32(f + 20, R(0));                                /* boundary tile X */
    R(0) = R(6) << 1;
    R(5) -= 24512;
    R(21) = gm_u32(R(4) + 8);
    gm_set_u32(f + 36, R(5));                                /* the actor info table */
    R(5) = R(3) + R(6);
    R(3) = R(3) + R(0);
    R(0) = gm_u32(R(4) + 4);
    gm_set_u32(f + 16, R(0));                                /* boundary tile Y */
    R(0) = R(3) + 16;
    R(20) = gm_u32(R(4) + 12);
    FLAG = R(5) + MAC_SPAWN;
    gm_set_u32(f + 24, R(0));                                /* the delete value */
    R(19) = gm_u32(R(4) + 16);
    R(18) = gm_u32(R(4) + 20);
    R(17) = gm_u32(R(4) + 24);
    R(16) = gm_u32(R(4) + 28);
    /* r21 left, r20 right, r19 top, r18 bottom, r17 / r16 directions X / Y */
    for (;;) {
        R(0) = gm_u32(f + 28);
        if (cmpu(ctx, I, R(0)) == 0) break;
        GM_LOOP();
        R(0) = gm_u8(FLAG) & 1;
        if (!rec0(ctx, R(0))) {
            /* the actor's tile box: centre (x + offset x, y - offset y), half sizes + margins, >> 4 */
            R(0) = gm_u16(DATA);
            int nodir_x = cmps(ctx, (int32_t)R(17), 0) == 0;
            R(3) = gm_u16(DATA + 2);
            R(28) = 0;
            R(4) = R(0) * 40;
            R(0) = gm_u32(f + 36);
            R(7) = gm_u16(DATA + 4);
            INFO = R(0) + R(4);
            R(0) = gm_u32(INFO + 12);
            R(6) = gm_u32(INFO + 20);
            R(3) = R(3) + R(0);
            R(8) = gm_u32(INFO + 16);
            R(0) = R(3) - R(6);
            R(4) = gm_u16(INFO + 32);
            R(3) = R(3) + R(6);
            R(5) = gm_u16(INFO + 34);
            R(6) = R(0) - R(4);
            R(9) = gm_u32(INFO + 24);
            R(7) = R(7) - R(8);
            R(5) = R(5) + R(3);
            R(26) = srawi(ctx, R(6), 4);                     /* left */
            R(4) = gm_u16(INFO + 28);
            R(0) = R(7) - R(9);
            R(25) = srawi(ctx, R(5), 4);                     /* right */
            R(4) = R(0) - R(4);
            R(3) = gm_u16(INFO + 30);
            R(0) = R(7) + R(9);
            R(27) = R(25);
            R(23) = srawi(ctx, R(4), 4);                     /* top */
            R(0) = R(3) + R(0);
            R(22) = srawi(ctx, R(0), 4);                     /* bottom */
            if (!nodir_x) R(27) = R(26);                     /* the edge facing the scroll */
            int nodir_y = cmps(ctx, (int32_t)R(16), 0) == 0;
            R(24) = R(22);
            if (!nodir_y) R(24) = R(23);
            R(3) = gm_u16(INFO + 36);
            R(0) = 0;
            gm_set_u8(f + 12, 0);                            /* grouped */
            R(0) = R(3) & 0x10;
            if (rec0(ctx, R(0))) {
                R(4) = gm_u32(DATA + 8); R(3) = M;
                if (cmps(ctx, (int32_t)NCALL(0x800689E4u, acm_no_group(GM_PASS, R(4))), 0) == 0) { R(0) = 1; gm_set_u8(f + 12, 1); }
            }
            R(0) = gm_u8(f + 12);
            if (cmps(ctx, (int32_t)R(0), 0) == 0) {
                R(0) = gm_u32(f + 8);
                if (cmps(ctx, (int32_t)R(0), 0) != 0) {      /* the screen scrolled: the edge it crossed */
                    R(0) = gm_u32(f + 20);
                    if (cmps(ctx, (int32_t)R(27), (int32_t)R(0)) == 0) {
                        if (cmps(ctx, (int32_t)R(17), 1) != 0) {
                            int left = cmps(ctx, (int32_t)R(17), 0) < 0;
                            R(3) = M; R(4) = left ? R(20) : R(21); R(5) = left ? R(26) : R(25);
                            R(6) = R(19); R(7) = R(18); R(8) = R(23); R(9) = R(22);
                            R(28) = NCALL(left ? 0x80068A48u : 0x80068A70u, acm_area_in(GM_PASS));
                        }
                    } else {
                        R(0) = gm_u32(f + 16);
                        if (cmps(ctx, (int32_t)R(24), (int32_t)R(0)) == 0 && cmps(ctx, (int32_t)R(16), 1) != 0) {
                            int up = cmps(ctx, (int32_t)R(16), 0) < 0;
                            R(3) = M; R(4) = up ? R(18) : R(19); R(5) = up ? R(23) : R(22);
                            R(6) = R(21); R(7) = R(20); R(8) = R(26); R(9) = R(25);
                            R(28) = NCALL(up ? 0x80068AB4u : 0x80068ADCu, acm_area_in(GM_PASS));
                        }
                    }
                } else {                                     /* both edges */
                    R(4) = gm_u32(f + 20); R(3) = M; R(5) = R(27);
                    R(6) = R(19); R(7) = R(18); R(8) = R(23); R(9) = R(22);
                    if (cmps(ctx, (int32_t)NCALL(0x80068B04u, acm_area_in(GM_PASS)), 0) != 0) R(28) = 1;
                    R(4) = gm_u32(f + 16); R(3) = M; R(5) = R(24);
                    R(6) = R(21); R(7) = R(20); R(8) = R(26); R(9) = R(25);
                    if (cmps(ctx, (int32_t)NCALL(0x80068B30u, acm_area_in(GM_PASS)), 0) != 0) R(28) = 1;
                }
            }
            if (cmps(ctx, (int32_t)R(28), 0) != 0) {
                R(7) = gm_u32(f + 24); R(3) = M; R(8) = gm_u8(f + 32);
                R(4) = DATA; R(5) = INFO; R(6) = FLAG;
                NCALL(0x80068B60u, acm_spawn(GM_PASS, M, DATA, INFO, FLAG, R(7), R(8)));
            }
        }
        R(3) = gm_u32(f + 24);
        DATA += 16; FLAG += 1; I += 1;
        R(3) += 2;
        gm_set_u32(f + 24, R(3));
    }
out:
    R(11) = f + 112;
    R(0) = lr;
#undef M
#undef DATA
#undef FLAG
#undef I
#undef INFO
#undef B_X
#undef B_L
#undef B_R
#undef B_T
#undef B_B
#undef DIR_X
#undef DIR_Y
}

/* ================================================================== MapActorScroolCreateCheck
   (every frame): the screen's tile box; on a zoom change all three edges, otherwise the edge the
   screen scrolled to if the boundary tile moved */
static void acm_scroll_check(GM_CTX, gptr m) {
    GM_FN(0x80068620); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    gptr f = gm_frame_sp, b = f + 8;
    R(0) = gm_u32(R(13) - SDA_GAME_FLAG);
    NV_R(29, m);
    R(0) &= 1;
    if (rec0(ctx, R(0))) goto out;
    R(0) = gm_u8(m + 3019);
    if (cmpu(ctx, R(0), 1) == 0) goto out;
    R(7) = gm_u32(R(13) - SDA_BG_PARAM);
    R(8) = 0;
    R(4) = gm_u32(R(13) - SDA_BG);
    R(9) = 0;
    FB(0, LF(R(7) + 56)); FB(1, LF(R(7) + 64));
    R(4) += 0x90000u;
    FB(2, LF(R(7) + 60));
    CTIW(0, 0); CTIW(1, 1);
    FB(3, LF(R(7) + 68));
    st64(base, f + 40, ctx->f[0].u);
    CTIW(2, 2); CTIW(0, 3);
    st64(base, f + 56, ctx->f[1].u);
    NV_R(31, gm_u32(f + 44));                                /* screen left */
    st64(base, f + 48, ctx->f[2].u);
    R(5) = R(31) - 32;
    R(0) = gm_u32(f + 60);
    st64(base, f + 64, ctx->f[0].u);
    NV_R(30, srawi(ctx, R(5), 4));                           /* tile left */
    R(5) = R(31) + R(0);
    R(6) = gm_u32(f + 52);
    R(5) += 48;
    R(0) = gm_u32(f + 68);
    FB(0, LF(R(4) + 20));
    NV_R(26, (uint32_t)-(int32_t)R(6));                      /* screen top */
    FB(1, LF(R(4) + 12));
    R(4) = R(26) + R(0);
    NV_R(25, srawi(ctx, R(5), 4));                           /* tile right */
    R(0) = R(26) - 16;
    NV_R(24, srawi(ctx, R(0), 4));                           /* tile top */
    cr_fcmp(ctx, 0, F(1), F(0));
    int same_scale = F(1) == F(0);
    R(0) = R(4) + 32;
    NV_R(23, srawi(ctx, R(0), 4));                           /* tile bottom */
    if (!same_scale) {                                       /* the zoom changed: left / right edges going down, then right going up */
        NV_R(27, 0); NV_R(28, (uint32_t)-1);
        gm_set_u32(b + 0, R(30)); R(4) = b; R(5) = 0;
        gm_set_u32(b + 4, R(23)); gm_set_u32(b + 8, R(30)); gm_set_u32(b + 12, R(25)); gm_set_u32(b + 16, R(24)); gm_set_u32(b + 20, R(23));
        gm_set_u32(b + 24, R(27)); gm_set_u32(b + 28, R(28));
        NCALL(0x80068714u, acm_scroll_create(GM_PASS));
        gm_set_u32(b + 0, R(25)); R(3) = m; R(4) = b; R(5) = 0;
        gm_set_u32(b + 4, R(23)); gm_set_u32(b + 8, R(30)); gm_set_u32(b + 12, R(25)); gm_set_u32(b + 16, R(24)); gm_set_u32(b + 20, R(23));
        gm_set_u32(b + 24, R(28)); gm_set_u32(b + 28, R(28));
        NCALL(0x80068744u, acm_scroll_create(GM_PASS));
        gm_set_u32(m + 3020, R(31));
        NV_R(22, R(25)); NV_R(21, R(24));
        R(3) = m;
        gm_set_u32(m + 3024, R(26));
        R(4) = b; R(5) = 0;
        gm_set_u32(b + 0, R(25)); gm_set_u32(b + 4, R(24));
        gm_set_u32(b + 32 - 8, R(28)); gm_set_u32(b + 28, R(27));
        NCALL(0x80068774u, acm_scroll_create(GM_PASS));
    } else {
        R(4) = gm_u8(R(7) + 128);                            /* the background's scroll directions */
        R(0) = gm_u8(R(7) + 129);
        if (cmps(ctx, (int32_t)R(4), 0) == 0) { NV_R(22, gm_u32(R(3) + 3032)); R(8) = 1; }
        else if (cmps(ctx, (int32_t)R(4), 2) == 0) { NV_R(22, R(25)); R(8) = (uint32_t)-1; }
        else NV_R(22, R(30));
        if (cmps(ctx, (int32_t)R(0), 0) == 0) { NV_R(21, gm_u32(R(3) + 3032)); R(9) = 1; }
        else if (cmpu(ctx, R(0), 1) == 0) { NV_R(21, R(23)); R(9) = (uint32_t)-1; }
        else NV_R(21, R(24));
        R(0) = gm_u32(R(3) + 3028);
        int moved = cmps(ctx, (int32_t)R(0), (int32_t)R(22)) != 0;
        if (!moved) { R(0) = gm_u32(R(3) + 3032); moved = cmps(ctx, (int32_t)R(0), (int32_t)R(21)) != 0; }
        if (moved) {
            gm_set_u32(b + 0, R(22)); R(3) = m; R(4) = b; R(5) = 1;
            gm_set_u32(b + 4, R(21)); gm_set_u32(b + 8, R(30)); gm_set_u32(b + 12, R(25)); gm_set_u32(b + 16, R(24)); gm_set_u32(b + 20, R(23));
            gm_set_u32(b + 24, R(8)); gm_set_u32(b + 28, R(9));
            NCALL(0x80068820u, acm_scroll_create(GM_PASS));
        }
    }
    gm_set_u32(m + 3020, R(31)); gm_set_u32(m + 3024, R(26));
    gm_set_u32(m + 3028, R(22)); gm_set_u32(m + 3032, R(21));
out:
    R(11) = f + 128;
    R(0) = lr;
}

/* ================================================================== setMapActorCreate / _next */
/* the current file's actors (MapActorInital_set) / the current area's (MapActorInital_next) - tail calls */
static void acm_initial_set(GM_CTX, gptr m) {
    gptr file = course_file(GM_PASS, 5, 4, 5);
    R(4) = gm_u32(file + 36);
    R(6) = m + MAC_SPAWN;
    R(7) = gm_u32(file + 148);
    R(5) = m + MAC_DELETE;
    R(8) = 0;
    R(3) = m;
    acm_initial(GM_PASS);
}
static void acm_initial_next(GM_CTX, gptr m) {
    gptr file = course_file(GM_PASS, 5, 4, 5);
    R(4) = gm_u32(R(13) - SDA_STAGE);
    R(8) = 1;
    R(0) = gm_u8(R(4) + 4623) << 2;
    R(7) = file + R(0);
    R(5) = gm_u32(R(7) + 688);
    R(4) = gm_u32(R(7) + 176);
    R(0) = R(5) << 1;
    R(6) = m + R(5);
    R(5) = m + R(0);
    R(7) = gm_u32(R(7) + 432);
    R(5) += MAC_DELETE;
    R(6) += MAC_SPAWN;
    R(3) = m;
    acm_initial(GM_PASS);
}
/* setMapActorCreate(): every spawn flag and delete value cleared, the screen state reset, the file's actors */
static void acm_set(GM_CTX, gptr m) {
    R(0) = 125; R(5) = m; R(7) = 0; R(4) = 0;
    ctx->ctr = 125;
    for (;;) {
        R(6) = m + R(7); R(7) += 8;
        for (int k = 0; k < 8; k++) { gm_set_u8(R(6) + MAC_SPAWN + k, 0); gm_set_u16(R(5) + MAC_DELETE + 2 * k, 0); }
        R(5) += 16;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    R(0) = gm_u32(R(13) - SDA_GAME_FLAG) & 1;
    if (rec0(ctx, R(0))) return;
    R(0) = 0;
    for (int i = 0; i < 4; i++) gm_set_u32(m + 3020 + 4 * i, 0);
    acm_initial_set(GM_PASS, m);
}
/* setMapActorCreate_next(): the spawned bits cleared, the screen state reset, the area's actors */
static void acm_set_next(GM_CTX, gptr m) {
    R(0) = gm_u32(R(13) - SDA_GAME_FLAG) & 1;
    if (rec0(ctx, R(0))) return;
    R(0) = gm_u8(m + 3018);
    if (cmps(ctx, (int32_t)R(0), 0) != 0) return;
    R(0) = 125; R(5) = 0;
    ctx->ctr = 125;
    for (;;) {
        R(4) = m + R(5); R(5) += 8;
        for (int k = 0; k < 8; k++) { R(0) = gm_u8(R(4) + MAC_SPAWN + k) & 0xFEu; gm_set_u8(R(4) + MAC_SPAWN + k, (uint8_t)R(0)); }
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    R(0) = 0;
    for (int i = 0; i < 4; i++) gm_set_u32(m + 3020 + 4 * i, 0);
    acm_initial_next(GM_PASS, m);
}

/* ================================================================== hle entry points
   On (18): reached by the test runs (setMapActorCreate, MapActorInital_set / InitialCreate,
   ScroolCreateCheck / ScrollCreate, GlobalActorCheck, mapActorSpawn, the Z counters) or run
   inside them; ScroolAreaInCheck, ActorCreateInfoClear and the two scroll functions checked with
   RT_GM_VERIFY_REGS=1 (0 differences). Written but off (not reached): setMapActorCreate_next,
   MapActorInital_next, processGroupId, GroupIdCheck. */
#define A(i) GM_ARG(i)
#define ACM_MEM A(0), 3036
GM_HLE_VOID(fn_80068040, ACM_MEM) { acm_info_clear(GM_PASS, A(0)); }                           /* dActorCreateMng_c::ActorCreateInfoClear */
GM_HLE_INT(fn_80068070, 0, 0) { acm_area_in(GM_PASS); }                                           /* ::ScroolAreaInCheck */
GM_HLE_INT(fn_800680A0, 0, 0) { acm_area_in(GM_PASS); }                                           /* ::ScroolAreaInLoopCheck */
GM_HLE(fn_800680B0) { acm_set(GM_PASS, A(0)); }                                                   /* ::setMapActorCreate */
GM_HLE(fn_80068140) { acm_set_next(GM_PASS, A(0)); }                                              /* ::setMapActorCreate_next */
GM_HLE(fn_800681F0) { acm_initial_set(GM_PASS, A(0)); }                                           /* ::MapActorInital_set */
GM_HLE(fn_80068230) { acm_initial_next(GM_PASS, A(0)); }                                          /* ::MapActorInital_next */
GM_HLE_INT(fn_80068290, 0, 0) { acm_global(GM_PASS, A(1)); }                                      /* ::GlobalActorCheck */
GM_HLE(fn_800682F0) { acm_group(GM_PASS, A(1), A(2), A(3)); }                                     /* ::processGroupId */
GM_HLE(fn_80068310) { acm_no_group(GM_PASS, A(1)); }                                    /* ::GroupIdCheck */
GM_HLE(fn_80068320) { acm_initial(GM_PASS); }                                                     /* ::MapActorInitialCreate */
GM_HLE(fn_80068620) { acm_scroll_check(GM_PASS, A(0)); }                                          /* ::MapActorScroolCreateCheck */
GM_HLE(fn_80068850) { acm_scroll_create(GM_PASS); }                                               /* ::MapActorScrollCreate */
GM_HLE_VOID(fn_80068BA0, ACM_MEM) { acm_zinc(GM_PASS, A(0), 0); }                                 /* ::incZposCount */
GM_HLE_VOID(fn_80068BC0, ACM_MEM) { acm_zadd(GM_PASS, A(0), 0); }                                 /* ::addZposCount */
GM_HLE_VOID(fn_80068C30, ACM_MEM) { acm_zinc(GM_PASS, A(0), 1); }                                 /* ::incZposCount_layer2 */
GM_HLE_VOID(fn_80068C50, ACM_MEM) { acm_zadd(GM_PASS, A(0), 1); }                                 /* ::addZposCount_layer2 */
GM_HLE_VOID(fn_80068CC0, ACM_MEM) { acm_zinc(GM_PASS, A(0), 2); }                                 /* ::incMapObjZposCount */
GM_HLE_VOID(fn_80068CE0, ACM_MEM) { acm_zadd(GM_PASS, A(0), 2); }                                 /* ::addMapObjZposCount */
GM_HLE_VOID(fn_80068D50, ACM_MEM) { acm_zinc(GM_PASS, A(0), 3); }                                 /* ::incMapObjZposCount_layer2 */
GM_HLE_VOID(fn_80068D70, ACM_MEM) { acm_zadd(GM_PASS, A(0), 3); }                                 /* ::addMapObjZposCount_layer2 */
GM_HLE(fn_80068DE0) { acm_spawn(GM_PASS, A(0), A(1), A(2), A(3), A(4), A(5)); }                 /* ::mapActorSpawn */
