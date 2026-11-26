/* rt_powerup.c - the new power-ups as NSMBW power-up states (rt_powerup.h; SMB3Disassembly/port/POWERUPS.md).
 *
 * Here: the places in the recompiled game (the ones not hand-converted in gm_*.c) that index one
 * of the game's 7-entry tables with a player's power-up, replaced for their indirect callers
 * (rt_override_func: these are reached through state tables / virtual calls only). Each runs the
 * game's own code with the player's value read as pu_tab() gives it, the value put back after.
 * The hand-converted ones use pu_tab() where they read (gm_d_player.c, gm_d_player_base.c,
 * gm_d_player_conv.c). */
#include "rt.h"
#include "rt_powerup.h"
RT_STATE_FILE

#define PL_MODE      4240                        /* dAcPy_c mPlayerMode */

/* the game's code run with a new power-up read as its base one (the tables only - nothing in
   these functions changes the value) */
#define PU_TABLE_HOOK(name, addr)                                                     \
    void name(ppc_context *ctx, uint8_t *base);                                       \
    static void hk_##name(ppc_context *ctx, uint8_t *base) {                          \
        uint32_t pl = ctx->r[3], m = R32(pl + PL_MODE);                               \
        if (!pu_is_new(m)) { name(ctx, base); return; }                               \
        W32(pl + PL_MODE, pu_tab(m)); name(ctx, base);                                 \
        if (R32(pl + PL_MODE) == pu_tab(m)) W32(pl + PL_MODE, m);                     \
    }
/* fn_80133CB0 (dAcPy_c: a state's init; +10864 from float[7] 0x802F4E9C) */
PU_TABLE_HOOK(fn_80133CB0, 0x80133CB0u)

/* the models' power-ups (rt_powerup.h) */
static struct { uint32_t mdl, mode; } mdl_mode[32];
void rt_pu_mdl_set(uint32_t mdl, uint32_t mode) {
    int fr = -1;
    for (int i = 0; i < 32; i++) { if (mdl_mode[i].mdl == mdl) { mdl_mode[i].mode = mode; return; } if (!mdl_mode[i].mdl && fr < 0) fr = i; }
    if (fr < 0) { static int rr; fr = rr++ & 31; }
    mdl_mode[fr].mdl = mdl; mdl_mode[fr].mode = mode;
}
uint32_t rt_pu_mdl_get(uint32_t mdl) {
    for (int i = 0; i < 32; i++) if (mdl_mode[i].mdl == mdl) return mdl_mode[i].mode;
    return 0xFFFFFFFFu;
}

/* daEnItem_c::GetWhetherPlayerCanGetPowerupOrNot (the item a block gives, by its player's
   power-up: 0 small - a mushroom, 1 big - a flower etc., 2 Mini): a new power-up is big */
void orig_daEnItem_c__GetWhetherPlayerCanGetPowerupOrNot(ppc_context *ctx, uint8_t *base);
void hle_daEnItem_c__GetWhetherPlayerCanGetPowerupOrNot(ppc_context *ctx, uint8_t *base) {
    uint32_t pl = rt_gcall(ctx, base, 0x8005F900u, 1, R32(ctx->r[3] + 3472));   /* (daPyMng_c::getPlayer(its player)) */
    uint32_t m = pl ? R32(pl + PL_MODE) : 0;
    if (!pu_is_new(m)) { orig_daEnItem_c__GetWhetherPlayerCanGetPowerupOrNot(ctx, base); return; }
    ctx->r[3] = 1;
}

/* fn_80022180 (daEnBlockMain_c: is the player who hit the block big - Super/Fire/Propeller/
   Penguin/Ice, not small or Mini - so it breaks a brick): a new power-up is big */
void orig_fn_80022180(ppc_context *ctx, uint8_t *base);
void hle_fn_80022180(ppc_context *ctx, uint8_t *base) {
    uint32_t pl = rt_gcall(ctx, base, 0x8005F900u, 1, (uint32_t)(int32_t)(int8_t)ctx->r[4]);
    if (pl && pu_is_new(R32(pl + PL_MODE))) { ctx->r[3] = 1; return; }
    orig_fn_80022180(ctx, base);
}

/* A block function that tests the power-up of the player it was hit by with a list of the
   game's modes inline: while it runs, every player shows the game the mode its tables use
   (rt_powerup.h), and gets its own back after (unless the function changed it). */
static void with_game_modes(ppc_context *ctx, uint8_t *base, ppc_func fn) {
    uint32_t pl[8], m[8]; uint32_t r3 = ctx->r[3], r4 = ctx->r[4];
    for (int i = 0; i < 8; i++) {
        pl[i] = rt_gcall(ctx, base, 0x8005F900u, 1, (uint32_t)i); m[i] = 0;
        if (pl[i]) { m[i] = R32(pl[i] + PL_MODE); if (pu_is_new(m[i])) W32(pl[i] + PL_MODE, pu_tab(m[i])); }
    }
    ctx->r[3] = r3; ctx->r[4] = r4;
    fn(ctx, base);
    for (int i = 0; i < 8; i++)
        if (pl[i] && pu_is_new(m[i]) && R32(pl[i] + PL_MODE) == pu_tab(m[i])) W32(pl[i] + PL_MODE, m[i]);
}
/* fn_80036AB0 (daEnBlockMain_c: a brick's hit - breaks for a big player) */
void orig_fn_80036AB0(ppc_context *ctx, uint8_t *base);
void hle_fn_80036AB0(ppc_context *ctx, uint8_t *base) { with_game_modes(ctx, base, orig_fn_80036AB0); }

void rt_powerup_init(void) {
    rt_override_func(0x80133CB0u, hk_fn_80133CB0);
}
