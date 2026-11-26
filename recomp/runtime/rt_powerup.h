/* rt_powerup.h - the players' power-up states: NSMBW's seven and the new ones (SMB3Disassembly/port/POWERUPS.md).
 *
 * The new power-ups are real values of NSMBW's PLAYER_MODE_e (dAcPy_c mPlayerMode +4240, mNextMode
 * +5344, daPyMng_c::mPlayerMode[], the save's u8[8]) in every game mode (user, 2026-11-26).
 * The game's own tables have 7 entries (one a power-up): every place that indexes one with the
 * value goes through pu_tab(), which gives a new power-up the entry of the one it is built on
 * (pu_base) until it has an entry of its own - never a read past a table's end. */
#ifndef RT_POWERUP_H
#define RT_POWERUP_H
#include <stdint.h>

enum {
    PU_SMALL, PU_SUPER, PU_FIRE, PU_MINI, PU_PROPELLER, PU_PENGUIN, PU_ICE,   /* NSMBW's */
    PU_GAME_COUNT,                                                           /* (the game's tables: this many entries) */
    PU_RACCOON = PU_GAME_COUNT,       /* SMB3's Super Leaf (its variants - Tanooki, P-Wing - are the player's pu_variant) */
    PU_FROG,                          /* SMB3's Frog suit */
    PU_COUNT
};
enum { PUV_RACCOON, PUV_TANOOKI, PUV_PWING };   /* (PU_RACCOON's variants) */

/* the power-up a new one is built on: its size, its collision, its speeds - the game's tables' entry it reads */
static inline uint32_t pu_base(uint32_t m) {
    switch (m) {
    case PU_RACCOON: return PU_SUPER;
    case PU_FROG: return PU_SUPER;
    default: return m < PU_GAME_COUNT ? m : PU_SUPER;
    }
}
/* the index for one of the game's 7-entry tables */
static inline uint32_t pu_tab(uint32_t m) { return m < PU_GAME_COUNT ? m : pu_base(m); }
static inline int pu_is_new(uint32_t m) { return m >= PU_GAME_COUNT && m < PU_COUNT; }
static inline const char *pu_name(uint32_t m) {
    static const char *const n[PU_COUNT] = { "small", "Super", "Fire", "Mini", "Propeller", "Penguin", "Ice", "Raccoon", "Frog" };
    return m < PU_COUNT ? n[m] : "?";
}
/* the power-up a model shows (dPlayerMdl_c::setPlayerMode's argument - the model itself keeps
   the base value in its mPlayerMode for the game's tables; NSMBW's change animation alternates
   the old and the new): rt_powerup.c */
void rt_pu_mdl_set(uint32_t mdl, uint32_t mode);
uint32_t rt_pu_mdl_get(uint32_t mdl);   /* (0xFFFFFFFF: not known) */
#endif
