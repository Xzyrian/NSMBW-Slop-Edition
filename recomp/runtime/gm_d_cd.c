/* gm_d_cd.c - dCdFile_c, the course file's data blocks (old name dCourse_c): the lookups by ID
 * (scroll data, backgrounds, next-gotos, areas and their 14 field getters, ranges, scroll areas)
 * and the range checks that find the area a position or a box is in. Track B (gm.h,
 * docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_cd.cpp) and checked against the recompiled
 * USA rev 2 code (0x8008E310-0x8008EB14). Register-exact (RT_GM_VERIFY_REGS=1): the counted
 * loops leave CTR, r0 and CR0 as the mtctr / bdnz loops do, the area / range rectangles go
 * through the stack as the compiler converts u16 to float (0x43300000:value at f+8 / f+16), and
 * checkRange's last test is the compiler's branchless "y < bottom". Not here (still recompiled):
 * loadCourseData (once per course load), dCd_c's create / delete / setCourseArcName.
 *
 * dCdFile_c: +16 scroll data (24 bytes each, ID at +17), +24 / +28 backgrounds 2 / 3 (24 bytes,
 * ID at +0), +32 next-gotos (20 bytes, ID at +8), +44 areas (24 bytes: rectangle x y w h u16 at
 * +0, ID at +12, then the fields the getters read), +48 ranges (12 bytes: rectangle, ID at +8),
 * +52 scroll areas (20 bytes); their counts at +128 / +136 / +140 / +144 / +156 / +160 / +164. */
#include "gm.h"
#include "gm_nv.h"

#define F_LOOP_POS_X 0x80101AA0u         /* dScStage_c::getLoopPosX */
#define K_U2F   28760                    /* (r2 - 28760: (double) 2^52, u32 to float; - 28752: 2^52 + 2^31, s32) */
#define K_S2F   28752
#define CD_SCROLL    16
#define CD_BG2       24
#define CD_BG3       28
#define CD_NEXT_GOTO 32
#define CD_AREAS     44
#define CD_RANGES    48
#define CD_SCRL_AREA 52

#define FR(n) (ctx->f[n].d)
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }

/* a counted search (mtctr n; ...; bdnz) over n elements of `stride` bytes from p for the key:
   kind 0 the u8 at +off (cmplw), 1 the u16 at +off compared signed (cmpw), 2 the low byte of the
   u16 at +off (cmplw). Count test: cmpwi when count_signed, else cmplwi. r0 holds r0_init
   while the count is tested. *pp: where it stopped. Returns 1 when found. */
enum { K_U8, K_U16S, K_U16LO };
static int ctr_find(GM_CTX, gptr *pp, uint32_t n, uint32_t stride, int kind, uint32_t off, uint32_t key, int count_signed, uint32_t r0_init) {
    gptr p = *pp;
    ctx->ctr = n; ctx->r[0] = r0_init;
    if (!((count_signed ? cmps(ctx, (int32_t)n, 0) : cmpu(ctx, n, 0)) > 0)) return 0;
    for (;;) {
        int eq;
        if (kind == K_U8) { ctx->r[0] = gm_u8(p + off); eq = cmpu(ctx, ctx->r[0], key) == 0; }
        else if (kind == K_U16S) { ctx->r[0] = gm_u16(p + off); eq = cmps(ctx, (int32_t)ctx->r[0], (int32_t)key) == 0; }
        else { ctx->r[0] = gm_u16(p + off) & 0xFFu; eq = cmpu(ctx, ctx->r[0], key) == 0; }
        if (eq) { *pp = p; return 1; }
        p += stride;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    *pp = p;
    return 0;
}

/* ================================================================== the lookups by ID */
/* getScrollDataP(id): the scroll data with that ID, else the first */
static gptr cd_scroll(GM_CTX, gptr cd, uint32_t id) {
    gptr first = gm_ptr(cd + CD_SCROLL), p = first;
    ctx->r[5] = first;
    if (ctr_find(GM_PASS, &p, gm_u32(cd + 128), 24, K_U16LO, 16, id, 0, gm_u32(cd + 128))) return p;
    return first;
}
/* getBg2DataP / getBg3DataP(id) */
static gptr cd_bg(GM_CTX, gptr cd, uint32_t list, uint32_t count, uint32_t id) {
    gptr p = gm_ptr(cd + list);
    uint32_t n = gm_u32(cd + count);
    return ctr_find(GM_PASS, &p, n, 24, K_U16S, 0, id, 0, n) ? p : 0;
}
/* getNextGotoP(id) */
static gptr cd_next_goto(GM_CTX, gptr cd, uint32_t id) {
    gptr p = gm_ptr(cd + CD_NEXT_GOTO);
    uint32_t n = gm_u32(cd + 144);
    return ctr_find(GM_PASS, &p, n, 20, K_U8, 8, id, 1, n) ? p : 0;
}
/* the rectangle (x, -y, w, h) as floats into bound: u16 to float through the stack */
static void rect_to_bound(GM_CTX, gptr f, gptr r, gptr bound) {
    ctx->r[0] = gm_u16(r + 0);
    gm_set_u32(f + 12, ctx->r[0]);
    ctx->f[2].u = ld64(base, ctx->r[2] - K_U2F);
    ctx->f[0].u = ld64(base, f + 8);
    ctx->f[1].u = ld64(base, ctx->r[2] - K_S2F);
    stfs(base, bound + 0, FB(0, frsp(FR(0) - FR(2))));
    ctx->r[0] = (uint32_t)-(int32_t)gm_u16(r + 2) ^ 0x80000000u;
    gm_set_u32(f + 20, ctx->r[0]);
    ctx->f[0].u = ld64(base, f + 16);
    stfs(base, bound + 4, FB(0, frsp(FR(0) - FR(1))));
    ctx->r[0] = gm_u16(r + 4);
    gm_set_u32(f + 12, ctx->r[0]);
    ctx->f[0].u = ld64(base, f + 8);
    stfs(base, bound + 8, FB(0, frsp(FR(0) - FR(2))));
    ctx->r[0] = gm_u16(r + 6);
    gm_set_u32(f + 20, ctx->r[0]);
    ctx->f[0].u = ld64(base, f + 16);
    stfs(base, bound + 12, FB(0, frsp(FR(0) - FR(2))));
}
/* getAreaDataP(id, bound) / getRangeDataP(id, bound): the area / range with that ID, its
   rectangle into bound (if any) */
static gptr cd_rect_find(GM_CTX, gptr cd, uint32_t list, uint32_t count, uint32_t stride, uint32_t id_off, uint32_t id, gptr bound) {
    GM_FRAME(32);
    gptr f = gm_frame_sp;
    uint32_t mag = 0x43300000u;
    ctx->r[6] = gm_u32(cd + count);
    gm_set_u32(f + 8, mag);
    gptr p = gm_ptr(cd + list);
    gm_set_u32(f + 16, mag);
    if (!ctr_find(GM_PASS, &p, ctx->r[6], stride, K_U8, id_off, id, 0, mag)) return 0;
    if (cmps(ctx, (int32_t)bound, 0) != 0) rect_to_bound(GM_PASS, f, p, bound);
    return p;
}
#define cd_area(cd, id, bound)  cd_rect_find(GM_PASS, (cd), CD_AREAS, 156, 24, 12, (id), (bound))
#define cd_range(cd, id, bound) cd_rect_find(GM_PASS, (cd), CD_RANGES, 160, 12, 8, (id), (bound))
/* getScrlAreaDataP(id) */
static gptr cd_scrl_area(GM_CTX, gptr cd, uint32_t id) {
    ctx->r[0] = gm_u32(cd + 164);
    if (!(cmpu(ctx, ctx->r[0], id) > 0)) return 0;
    ctx->r[0] = id * 20u;
    return gm_ptr(cd + CD_SCRL_AREA) + ctx->r[0];
}

/* the 14 area getters: getAreaDataP(id, 0)'s field (u8 or u16) - a null area reads low memory,
   as the game does */
static const struct { uint32_t fn, off, half; } area_getters[14] = {    /* FNADDR */
    { 0x8008E4D0u, 12, 0 },  /* getAreaID - FNADDR */
    { 0x8008E500u, 13, 0 },  /* getAreaScroll - FNADDR */
    { 0x8008E530u, 14, 0 },  /* getAreaZoomType - FNADDR */
    { 0x8008E560u, 15, 0 },  /* getAreaZoomID - FNADDR */
    { 0x8008E590u, 16, 0 },  /* getAreaZoomChange - FNADDR */
    { 0x8008E5C0u, 22, 0 },  /* getAreaBgm - FNADDR */
    { 0x8008E5F0u, 23, 0 },  /* getAreaBgmMode - FNADDR */
    { 0x8008E620u, 17, 0 },  /* getAreaMaskNo - FNADDR */
    { 0x8008E650u, 18, 0 },  /* getAreaBg2 - FNADDR */
    { 0x8008E680u, 19, 0 },  /* getAreaBg3 - FNADDR */
    { 0x8008E6B0u, 8, 1 },   /* getAreaColorOBJ - FNADDR */
    { 0x8008E6E0u, 10, 1 },  /* getAreaColorBG - FNADDR */
    { 0x8008E710u, 20, 0 },  /* getAreaDirection - FNADDR */
    { 0x8008E740u, 4, 1 },   /* getAreaSizeX - FNADDR */
};
static uint32_t cd_area_get(GM_CTX, int k, gptr cd, uint32_t id) {
    GM_FN(area_getters[k].fn); GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    ctx->r[5] = 0;
    gptr a = NCALL(area_getters[k].fn + 0x14, cd_area(cd, id, 0));
    ctx->r[0] = lr;
    return area_getters[k].half ? gm_u16(a + area_getters[k].off) : gm_u8(a + area_getters[k].off);
}

/* ================================================================== the range checks */
/* checkRange(pos, range): the position (x through the loop, -y) inside the rectangle grown by
   128 on every side */
static uint32_t cd_check_pos(GM_CTX, gptr pos, gptr r) {
    GM_FN(0x8008E950); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr, res;
    gptr f = gm_frame_sp;
    NV_R(31, r); NV_R(30, pos);
    FB(1, ldfs(base, pos));
    GM_CALLV(0x8008E974u, F_LOOP_POS_X, 0);
    FB(0, ldfs(base, pos + 4));
    ctx->f[1].u = fctiw_bits(FR(1), 1);
    ctx->r[3] = gm_u16(r + 0);
    ctx->f[0].u ^= 0x8000000000000000ull;
    st64(base, f + 8, ctx->f[1].u);
    ctx->r[0] = ctx->r[3] - 128;
    ctx->r[5] = gm_u32(f + 12);                              /* x */
    ctx->f[0].u = fctiw_bits(FR(0), 1);
    int lt = cmps(ctx, (int32_t)ctx->r[5], (int32_t)ctx->r[0]) < 0;
    st64(base, f + 16, ctx->f[0].u);
    ctx->r[6] = gm_u32(f + 20);                              /* y */
    if (lt) res = 0;
    else {
        ctx->r[4] = gm_u16(r + 2);
        ctx->r[0] = ctx->r[4] - 128;
        if (cmps(ctx, (int32_t)ctx->r[6], (int32_t)ctx->r[0]) < 0) res = 0;
        else {
            ctx->r[0] = gm_u16(r + 4);
            ctx->r[3] += ctx->r[0];
            ctx->r[0] = ctx->r[3] + 128;
            if (cmps(ctx, (int32_t)ctx->r[5], (int32_t)ctx->r[0]) >= 0) res = 0;
            else {                                           /* y < bottom + 128, branchless */
                ctx->r[0] = gm_u16(r + 6);
                ctx->r[3] = ctx->r[4] + ctx->r[0];
                ctx->r[4] = ctx->r[3] + 128;
                ctx->r[0] = ctx->r[4] ^ ctx->r[6];
                int32_t v = (int32_t)ctx->r[0];
                ctx->xer_ca = v < 0 && (v & 1);
                ctx->r[3] = (uint32_t)(v >> 1);
                ctx->r[0] &= ctx->r[4];
                ctx->r[0] = ctx->r[3] - ctx->r[0];
                res = ctx->r[3] = ctx->r[0] >> 31;
            }
        }
    }
    ctx->r[0] = lr;
    return res;
}
/* checkRange(a, b): two rectangles' centres closer than their half sizes + 128 on both axes */
static uint32_t cd_check_rect(GM_CTX, gptr a, gptr b) {
#define R ctx->r
    R[9] = gm_u16(b + 4); R[10] = gm_u16(a + 4); R[7] = gm_u16(b + 0);
    R[6] = R[9] >> 1;
    R[3] = gm_u16(a + 0);
    R[0] = R[10] >> 1;
    R[6] = R[7] + R[6];
    R[8] = gm_u16(a + 6);
    R[0] = R[3] + R[0];
    R[7] = gm_u16(b + 6);
    R[3] = (uint32_t)(int16_t)R[6];
    R[6] = gm_u16(a + 2);
    R[0] = (uint32_t)(int16_t)R[0];
    R[4] = R[8] >> 1;
    R[0] = R[0] - R[3];
    R[3] = gm_u16(b + 2);
    R[5] = (uint32_t)(int16_t)R[0];
    int neg = cmps(ctx, (int32_t)R[5], 0) < 0;
    R[4] = R[6] + R[4];
    R[0] = R[7] >> 1;
    R[0] = R[3] + R[0];
    R[3] = (uint32_t)(int16_t)R[4];
    R[4] = (uint32_t)(int16_t)R[0];
    if (neg) { R[0] = (uint32_t)-(int32_t)R[5]; R[5] = (uint32_t)(int16_t)R[0]; }
    R[0] = R[3] - R[4];
    R[6] = (uint32_t)(int16_t)R[0];
    if (cmps(ctx, (int32_t)R[6], 0) < 0) { R[0] = (uint32_t)-(int32_t)R[6]; R[6] = (uint32_t)(int16_t)R[0]; }
    R[4] = R[8] + R[7];
    R[3] = R[10] + R[9];
    R[0] = R[4] >> 31;
    R[4] = R[0] + R[4];
    R[0] = R[3] >> 31;
    { int32_t v = (int32_t)R[4]; ctx->xer_ca = v < 0 && (v & 1); R[4] = (uint32_t)(v >> 1); }
    R[0] = R[0] + R[3];
    { int32_t v = (int32_t)R[0]; ctx->xer_ca = v < 0 && (v & 1); R[0] = (uint32_t)(v >> 1); }
    R[4] = (uint32_t)(int16_t)R[4];
    R[3] = (uint32_t)(int16_t)R[0];
    R[0] = R[3] + 128;
    R[0] = R[5] - R[0];
    if (cmps(ctx, (int32_t)R[0], 0) < 0) {
        R[0] = R[4] + 128;
        R[0] = R[6] - R[0];
        if (cmps(ctx, (int32_t)R[0], 0) < 0) return 1;
    }
    return 0;
#undef R
}
/* getAreaNo(pos) / getAreaNo(box): the first area the position / box is in (255 / 0 if none) */
static uint32_t cd_area_no(GM_CTX, gptr cd, gptr what, int box) {
    GM_FN(box ? 0x8008E800u : 0x8008E770u); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr, res = box ? 0 : 255;
    NV_R(30, 0); NV_R(29, what); NV_R(28, cd); NV_R(31, gm_ptr(cd + CD_AREAS));
    for (;;) {
        ctx->r[0] = gm_u32(cd + 156);
        if (!(cmpu(ctx, ctx->r[30], ctx->r[0]) < 0)) break;
        GM_LOOP();
        ctx->r[3] = cd; ctx->r[4] = what; ctx->r[5] = ctx->r[31];
        uint32_t in = box ? NCALL(0x8008E840u, cd_check_rect(GM_PASS, what, ctx->r[31]))
                          : NCALL(0x8008E7B0u, cd_check_pos(GM_PASS, what, ctx->r[31]));
        ctx->r[3] = in;
        if (cmps(ctx, (int32_t)in, 0) != 0) { res = gm_u8(ctx->r[31] + 12); break; }
        NV_R(31, ctx->r[31] + 24); NV_R(30, ctx->r[30] + 1);
    }
    ctx->r[0] = lr;
    return res;
}

/* ================================================================== hle entry points
   On (24): all reached by the test runs, register-exact verify 0 differences in 1-1, 4-1 and the
   title demos. Written but off (not reached): getScrlAreaDataP. */
#define A(i) GM_ARG(i)
GM_HLE_INT(fn_8008E310, 0, 0) { GM_RET(cd_scroll(GM_PASS, A(0), A(1))); }                            /* dCdFile_c::getScrollDataP */
GM_HLE_INT(fn_8008E350, 0, 0) { GM_RET(cd_bg(GM_PASS, A(0), CD_BG2, 136, A(1))); }                   /* ::getBg2DataP */
GM_HLE_INT(fn_8008E390, 0, 0) { GM_RET(cd_bg(GM_PASS, A(0), CD_BG3, 140, A(1))); }                   /* ::getBg3DataP */
GM_HLE_INT(getNextGotoByID__9dCourse_cFUc, 0, 0) { GM_RET(cd_next_goto(GM_PASS, A(0), A(1))); }      /* ::getNextGotoP */
GM_HLE_INT(fn_8008E410, A(2), 16) { GM_RET(cd_area(A(0), A(1), A(2))); }                             /* ::getAreaDataP */
#define GETTER(name, k) GM_HLE_INT(name, 0, 0) { GM_RET(cd_area_get(GM_PASS, (k), A(0), A(1))); }
GETTER(fn_8008E4D0, 0) GETTER(fn_8008E500, 1) GETTER(fn_8008E530, 2) GETTER(fn_8008E560, 3)
GETTER(fn_8008E590, 4) GETTER(fn_8008E5C0, 5) GETTER(fn_8008E5F0, 6) GETTER(fn_8008E620, 7)
GETTER(fn_8008E650, 8) GETTER(fn_8008E680, 9) GETTER(fn_8008E6B0, 10) GETTER(fn_8008E6E0, 11)
GETTER(fn_8008E710, 12) GETTER(fn_8008E740, 13)
GM_HLE_INT(fn_8008E770, 0, 0) { GM_RET(cd_area_no(GM_PASS, A(0), A(1), 0)); }                        /* ::getAreaNo(pos) */
GM_HLE_INT(fn_8008E800, 0, 0) { GM_RET(cd_area_no(GM_PASS, A(0), A(1), 1)); }                        /* ::getAreaNo(box) */
GM_HLE_INT(getRectByID__9dCourse_cFUcP5mRect, A(2), 16) { GM_RET(cd_range(A(0), A(1), A(2))); }      /* ::getRangeDataP */
GM_HLE_INT(fn_8008E950, 0, 0) { GM_RET(cd_check_pos(GM_PASS, A(1), A(2))); }                         /* ::checkRange(pos) */
GM_HLE_INT(fn_8008EA20, 0, 0) { GM_RET(cd_check_rect(GM_PASS, A(1), A(2))); }                        /* ::checkRange(box) */
GM_HLE(fn_8008EAF0) { GM_RET(cd_scrl_area(GM_PASS, A(0), A(1))); }                         /* ::getScrlAreaDataP */
