/* gm_bg.c - the background tile lookups: which unit (tile) is at a position and its 64-bit
 * flags - dBc_c::getUnitType / getUnitKind down through dBgGm_c to the area's tilemap. Among the
 * most called game functions (every collision check asks). Track B (gm.h, docs/DECOMP.md),
 * instance 1.
 *
 * No NSMBW-Decomp source for these yet: decompiled from the recompiled USA rev 2 code (names
 * partly from the symbol map). A unit's flags come back in r3:r4 (high, low word); the low byte
 * of the low word is its kind.
 *
 * Calls from one native here to another set ctx->lr to the PowerPC return address first, so the
 * callee's saved-LR word on the guest stack is the real one (GM_CALL saves 0). */
#include "gm.h"
#include "gm_nv.h"

#define SDA 0x8042F680u
#define BG_GM         (SDA - 22704)      /* dBgGm_c::m_bg_p */
#define BG_TILEMAPS   (SDA - 22672)      /* (the tilemaps by area / layer) */
#define BG_AREA       (SDA - 21688)      /* (+0x120E: the current area) */
#define SWITCH_MNG    (SDA - 22144)      /* (the on/off switch state) */
#define F_LOOP_POS_X  0x80101AA0u        /* dScStage_c::getLoopPosX(f1) */
#define F_SWITCH_ANY  0x800D87D0u
#define F_SWITCH_ON   0x800D87B0u        /* (switch, n) */

#define FN(a) GM_FN(a); gptr f = gm_frame_sp; (void)f      /* (gm.h: the PowerPC function's frame and prologue) */
#define PAIR(hi, lo) (((uint64_t)(uint32_t)(hi) << 32) | (uint32_t)(lo))
static double bits2d(uint64_t u) { double d; memcpy(&d, &u, 8); return d; }
static uint64_t ld64g(GM_CTX, gptr a) { return ((uint64_t)gm_u32(a) << 32) | gm_u32(a + 4); }
/* The non-volatile registers: the PowerPC code keeps values in r27-r31 across its calls, and the
   callees save them into their frames - dead stack words the game can copy into the heap later.
   So before a nested call the natives put the same values there, and NV_KEEP puts the entry
   values back on return (as the PowerPC epilogue does). */
typedef struct { ppc_context *c; uint32_t r[5]; } nv_t;
static inline void nv_end_(nv_t *n) { memcpy(&n->c->r[27], n->r, sizeof n->r); }
#define NV_KEEP nv_t nv_ __attribute__((cleanup(nv_end_))) = { ctx, { ctx->r[27], ctx->r[28], ctx->r[29], ctx->r[30], ctx->r[31] } }

/* (byte) the bg's "switch blocks" flag */
static uint32_t bg_flag_2728(GM_CTX, gptr bg) { return gm_u8(bg + 0x90000 + 2728); }
/* the unit table entry */
static uint64_t unit_info(GM_CTX, gptr bg, uint32_t n) {
    gptr a = gm_u32(bg + 112) + ((n << 3) & 0x7FFF8);
    return PAIR(gm_u32(a), gm_u32(a + 4));
}
/* the flags changed by the on/off switches (tile: the tile number) */
static uint64_t switch_flags(GM_CTX, uint32_t hi, uint32_t lo, uint32_t tile) {
    FN(0x80081960); NV_KEEP;
    gptr sw = gm_u32(SWITCH_MNG);
    ctx->r[30] = sw; ctx->r[28] = hi; ctx->r[27] = lo; ctx->r[29] = tile;
    if (GM_CALLR(0x8008198Cu, F_SWITCH_ANY, 1, sw)) {
        uint32_t kind = lo & 0xFF;
        ctx->r[31] = kind;
        if (GM_CALLR(0x800819A4u, F_SWITCH_ON, 2, sw, 0)) {
            if ((hi & 2) && kind == 0) return PAIR(16, 0);
            if ((hi & 0x10) && kind == 0 && tile == 0x30) return PAIR(2, 0);
            if (hi == 0 && kind == 0x35) return PAIR(2, 4);
        }
        if (GM_CALLR(0x80081A14u, F_SWITCH_ON, 2, sw, 1) && hi == 0 && (kind == 0x36 || kind == 0x37)) return PAIR(8, 3);
    }
    ctx->lr = 0x80081A54u;
    if (bg_flag_2728(GM_PASS, gm_u32(BG_GM)) && hi == 0 && (tile == 0x3B || tile == 0x3C)) return PAIR(8, 3);
    return PAIR(hi, lo);
}
/* a tile number's flags (bits 10-15: the tileset) */
static uint64_t unit_flags(GM_CTX, gptr bg, uint32_t tile) {
    FN(0x800774A0); NV_KEEP;
    uint32_t n = tile & 0x3FF, set = (tile >> 10) & 0x3F;
    ctx->r[31] = set; ctx->r[30] = tile; ctx->r[29] = n;
    uint64_t u = unit_info(GM_PASS, bg, n);
    ctx->lr = 0x800774D4u;
    u = switch_flags(GM_PASS, (uint32_t)(u >> 32), (uint32_t)u, tile);
    if (n > 0x100 && ((u >> 32) & 0x400) && set != 0) u &= ~((uint64_t)0x400 << 32);
    return u;
}
/* the block number at (x, y) in a tilemap */
static uint32_t tm_block(GM_CTX, gptr tm, uint32_t x, uint32_t y) {
    int32_t i = (int32_t)(((x >> 8) & 0xFF) + ((y >> 2) & 0x3FC0));
    if (i > 2047) i = 0;
    return gm_u8(tm + 1032 + i);
}
/* TilemapClass::getPointerToTile(x, y, block out, _): the tile number's address, or 0 */
static gptr tm_tile_ptr(GM_CTX, gptr tm, uint32_t x, uint32_t y, gptr blk_out) {
    FN(0x80083B40); NV_KEEP;
    ctx->r[31] = blk_out; ctx->r[30] = y; ctx->r[29] = x; ctx->r[28] = tm;     /* (the block lookup is a leaf: kept for the epilogue) */
    uint32_t b = tm_block(GM_PASS, tm, x, y) & 0xFFFF;
    if (blk_out) gm_set_u32(blk_out, b);
    gptr p = gm_u32(tm + 4 * b + 4);
    if (!p) return 0;
    return p + ((x >> 3) & 0x1E) + ((y << 1) & 0x1E0);
}
/* BgGmBase::getPointerToTile(x, y, layer, block out, _): in the current area's tilemap */
static gptr bg_tile_ptr(GM_CTX, uint32_t x, uint32_t y, uint32_t layer, gptr blk_out, uint32_t flag) {
    FN(0x80077520); NV_KEEP;
    ctx->r[31] = flag; ctx->r[30] = blk_out; ctx->r[29] = y; ctx->r[28] = x;
    gptr tms = gm_u32(BG_TILEMAPS);
    uint32_t area = gm_u8(gm_u32(BG_AREA) + 4622);
    gptr tm = gm_u32(tms + (uint32_t)((int32_t)area * 12) + 4 * layer + 52);
    ctx->lr = 0x80077574u;
    return tm_tile_ptr(GM_PASS, tm, x, y, blk_out);
}
/* the unit at (x, y) in a layer: x wrapped for looping stages */
static uint64_t unit_at(GM_CTX, gptr bg, uint32_t x, uint32_t y, uint32_t layer) {
    FN(0x80077650); NV_KEEP;
    ctx->r[31] = layer; ctx->r[30] = y; ctx->r[29] = bg;
    gm_set_u32(f + 12, x); gm_set_u32(f + 8, 0x43300000u);
    ctx->f[1].d = ctx->ps1[1] = frsp(bits2d(ld64g(GM_PASS, f + 8)) - bits2d(ld64g(GM_PASS, ctx->r[2] - 29536)));
    GM_CALLR(0x80077690u, F_LOOP_POS_X, 1, bg);
    uint64_t w = fctiw_bits(ctx->f[1].d, 1);
    st64(base, f + 16, w);
    uint32_t lx = gm_u32(f + 20) & 0xFFFF;
    ctx->lr = 0x800776B8u;
    gptr p = bg_tile_ptr(GM_PASS, lx, y, layer, 0, 0);
    ctx->lr = 0x800776C8u;
    return unit_flags(GM_PASS, bg, gm_u16(p));
}
static uint32_t unit_kind_at(GM_CTX, gptr bg, uint32_t x, uint32_t y, uint32_t layer) {
    FN(0x80077700);
    ctx->lr = 0x80077710u;
    return (uint32_t)unit_at(GM_PASS, bg, x, y, layer);
}
/* dBc_c::getUnitType / getUnitKind(x, y, layer): world position (y up) to tile position */
static uint64_t bc_unit(GM_CTX, double x, double y, uint32_t layer, int kind) {
    FN(kind ? 0x80070BF0u : 0x80070BA0u);
    uint64_t wx = fctiw_bits(x, 1), wy = fctiw_bits(-y, 1);
    st64(base, f + 8, wx); st64(base, f + 16, wy);
    uint32_t tx = gm_u32(f + 12) & 0xFFFF, ty = gm_u32(f + 20) & 0xFFFF;
    ctx->lr = kind ? 0x80070C28u : 0x80070BD8u;
    gptr bg = gm_u32(BG_GM);
    if (kind) return unit_kind_at(GM_PASS, bg, tx, ty, layer);
    return unit_at(GM_PASS, bg, tx, ty, layer);
}

/* ================================================================== hle entry points
   All on: 11 entries are reached by the test runs from recompiled code; the other 5 run inside
   them (natives calling natives). */
#define A(i) GM_ARG(i)
/* (an entry returns with LR = its return address, as the PowerPC code leaves it) */
#define KEEP_LR(stmt) do { uint32_t lr0_ = ctx->lr; stmt; ctx->lr = lr0_; } while (0)
#define RET64(v) do { uint64_t v_ = (v); ctx->r[3] = (uint32_t)(v_ >> 32); ctx->r[4] = (uint32_t)v_; } while (0)
GM_HLE(getUnitType__5dBc_cFffUc) { KEEP_LR(RET64(bc_unit(GM_PASS, GM_FARG(0), GM_FARG(1), A(0), 0))); }        /* dBc_c::getUnitType */
GM_HLE(getUnitKind__5dBc_cFffUc) { KEEP_LR(uint32_t k = (uint32_t)bc_unit(GM_PASS, GM_FARG(0), GM_FARG(1), A(0), 1); ctx->r[3] = ctx->r[4] = k); }   /* dBc_c::getUnitKind */
GM_HLE(fn_80070C40) { KEEP_LR(RET64(unit_at(GM_PASS, gm_u32(BG_GM), A(0), A(1), A(2)))); }                     /* (static: unit at tile x, y, layer) */
GM_HLE(fn_80070C60) { KEEP_LR(ctx->r[3] = ctx->r[4] = unit_kind_at(GM_PASS, gm_u32(BG_GM), A(0), A(1), A(2))); }          /* (static: its kind) */
GM_HLE(fn_80070C80) { gptr p = gm_u32(A(0) + 4); GM_RET(p ? gm_u8(p + 908) : 0); }                    /* dBc_c: the owner's byte +0x38C */
GM_HLE(fn_80077470) { RET64(unit_info(GM_PASS, A(0), A(1))); }                                         /* dBgGm_c: the unit table entry */
GM_HLE(fn_800774A0) { KEEP_LR(RET64(unit_flags(GM_PASS, A(0), A(1)))); }                                        /* dBgGm_c: a tile number's flags */
GM_HLE(getPointerToTile__8BgGmBaseFiiiPib) { KEEP_LR(ctx->r[3] = (bg_tile_ptr(GM_PASS, A(1), A(2), A(3), A(4), A(5)))); }  /* BgGmBase::getPointerToTile */
GM_HLE(fn_80077650) { KEEP_LR(RET64(unit_at(GM_PASS, A(0), A(1), A(2), A(3)))); }                               /* dBgGm_c: the unit at (x, y, layer) */
GM_HLE(fn_800776F0) { KEEP_LR(RET64(unit_at(GM_PASS, A(0), A(1), A(2), A(3)))); }                               /* (the same, a tail call) */
GM_HLE(fn_80077700) { KEEP_LR(ctx->r[3] = ctx->r[4] = unit_kind_at(GM_PASS, A(0), A(1), A(2), A(3))); }                    /* dBgGm_c: its kind */
GM_HLE(fn_80078510) { GM_RET(bg_flag_2728(GM_PASS, A(0))); }
GM_HLE(fn_80081850) { GM_RET(gm_u32(A(0) + (uint32_t)((int32_t)A(1) * 12) + 4 * A(2) + 52)); }        /* (the tilemap of an area / layer) */
GM_HLE(fn_80081960) { KEEP_LR(RET64(switch_flags(GM_PASS, A(0), A(1), A(2)))); }                                /* (flags changed by the on/off switches) */
GM_HLE(getPointerToTile__12TilemapClassFiiPUib) { GM_RET(tm_tile_ptr(GM_PASS, A(0), A(1), A(2), A(3))); }   /* TilemapClass::getPointerToTile */
GM_HLE(fn_80083F90) { GM_RET(tm_block(GM_PASS, A(0), A(1), A(2))); }                                   /* TilemapClass: the block number */
