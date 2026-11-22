/* smb3_save.h - an SMB3 save file (one per File Select card, smb3_main.c keeps them).
 * SMB3 itself has no saves: this is its progress as the game keeps it between visits to the
 * map - the 8 KB work RAM (map completions, map objects, inventory, cards, score, coins, where
 * each player stands) and the few values in internal RAM (world, lives, power-ups on the map,
 * players). Loading goes back to the map the way SMB3 does after a level (PRG030_84D7). */
#pragma once
#include <stdint.h>
#define SMB3_SAVE_MAGIC "SMB3SAV1"
typedef struct {
    char magic[8];
    uint8_t world, lives[2], power[2], players, bigq_got, reserved;
    uint8_t wram[0x2000];
} smb3_save_t;
void smb3_save_capture(smb3_save_t *s);         /* the running game's progress (between frames) */
extern const smb3_save_t *smb3_load_from;       /* set before nes_reset(): start from this, not World 1 */
int smb3_on_map(void);                          /* on the world map (not in a level) */
int smb3_world(void);                           /* 1-9 */
