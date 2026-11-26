/* smb3_game.c - native code inside the recompiled SMB3 (hooks, port/hooks.txt). No runtime
 * dependencies: the headless test links it too. */
#include "nes_gen.h"
#include "smb3_syms.h"
#include "smb3_save.h"
#include <string.h>

int smb3_start_at_map = 1;          /* entered from the character select: the title is skipped */
const smb3_save_t *smb3_load_from;  /* a save file to continue from (smb3_main.c) */
static void snap_map_objects(uint8_t *w);
#define PRG030_84D7 0x84D7          /* (PRG030: the map is set up again from the progress in RAM - after a level, here after a load) */

/* Do_Title_Screen (PRG024): instead of the curtain, intro and 1P/2P menu, what the title leaves
   behind when "1 Player Game" is chosen; PRG030 then initializes the World 1 map as usual. */
int smb3_hook_title(void) {
    if (!smb3_start_at_map) return 0;
    for (int x = 0xF5; x > 0; x--) ZPW(x, 0);                                  /* RAM $01-$F5 */
    for (int x = 0; x <= SMB3_Title_ObjFrame - SMB3_Title_MLAccelCnt + 6; x++) WR((uint16_t)(SMB3_Title_MLAccelCnt + x), 0);
    WR(SMB3_Player_Lives, 4); WR(SMB3_Player_Lives + 1, 4);                    /* Mario and Luigi: 4 lives */
    WR(SMB3_Random_Pool, 0x88);                                                /* (the title's seed) */
    ZPW(SMB3_PPU_CTL1_Copy, 0xA8); ZPW(SMB3_PPU_CTL2_Copy, 0x1E);              /* (as the title had them: NMI on, 8x16 sprites; BG + sprites shown) */
    WR(SMB3_World_Map_Power, 0); WR(SMB3_World_Map_Power + 1, 0);              /* Title_PrepForWorldMap: small on the map */
    WR(SMB3_Total_Players, 1);                                                 /* one player */
    for (int x = 0x80; x >= 0; x--) ZPW(SMB3_World_Map_Y + x, 0);              /* the map's variables */
    if (!smb3_load_from) return NES_RTS();                                     /* new game: PRG030_84A0, World 1 */
    /* a save file: its progress back, then what PRG030_84A0 does before PRG030_84D7 (but not
       Map_Init or clearing the completions - those are the saved ones) */
    const smb3_save_t *sv = smb3_load_from;
    memcpy(nes_wram, sv->wram, sizeof nes_wram);
    snap_map_objects(nes_wram);                                                /* (a save from the middle of a march) */
    WR(SMB3_World_Num, sv->world);
    WR(SMB3_Player_Lives, sv->lives[0]); WR(SMB3_Player_Lives + 1, sv->lives[1]);
    WR(SMB3_World_Map_Power, sv->power[0]); WR(SMB3_World_Map_Power + 1, sv->power[1]);
    WR(SMB3_Total_Players, sv->players ? sv->players : 1);
    WR(SMB3_BigQBlock_GotIt, sv->bigq_got);
    WR(SMB3_Map_Operation, 0);                                                 /* ("World N" banner first) */
    ZPW(SMB3_Map_UnusedGOFlag, 0xF8);
    WR(0x2001, 0);                                                             /* (PPU_CTL2: hidden while it is drawn) */
    WR(SMB3_UpdSel_Disable, (uint8_t)(RD(SMB3_UpdSel_Disable) + 1));
    PULL16();                                                                  /* (not back to the reset code: on from PRG030_84D7) */
    return NES_JUMP(PRG030_84D7);
}

/* Map objects that march (the brothers, MAPOBJ_HAMMERBRO-$08, and the Coin Ship $0B) move 2 squares
   at a time over Map_March_Count's 32 frames (prg011 Map_Object_Do_All): saved in the middle of a
   march they'd be left between squares, the march counter (RAM) gone - never on a square the
   Player can stop on (PRG011_B6A1), and entered from there, a level looked up for no square
   (the battle never comes). Each is put on the square behind it on its way (it came from or went to
   it - both squares of its path): X and Y down to the 32-pixel grid (squares are 2 tiles apart:
   Y $20 + 32n, X 32n). */
static void snap_map_objects(uint8_t *w) {                                    /* (w: WRAM $6000) */
    for (int i = 0; i < 14; i++) {
        uint8_t id = w[SMB3_Map_Objects_IDs - 0x6000 + i];
        if (!((id >= 0x03 && id <= 0x08) || id == 0x0B)) continue;
        uint8_t *y = &w[SMB3_Map_Objects_Y - 0x6000 + i], *x = &w[SMB3_Map_Objects_XLo - 0x6000 + i];
        if (*y & 0x1F) *y &= 0xE0;
        if (*x & 0x1F) *x &= 0xE0;
    }
}

int smb3_on_map(void) { return RD(SMB3_Level_Tileset) == 0; }
int smb3_world(void) { return RD(SMB3_World_Num) + 1; }

void smb3_save_capture(smb3_save_t *s) {
    memset(s, 0, sizeof *s);
    memcpy(s->magic, SMB3_SAVE_MAGIC, 8);
    s->world = RD(SMB3_World_Num);
    s->lives[0] = RD(SMB3_Player_Lives); s->lives[1] = RD(SMB3_Player_Lives + 1);
    s->power[0] = RD(SMB3_World_Map_Power); s->power[1] = RD(SMB3_World_Map_Power + 1);
    s->players = RD(SMB3_Total_Players); s->bigq_got = RD(SMB3_BigQBlock_GotIt);
    memcpy(s->wram, nes_wram, sizeof s->wram);
    snap_map_objects(s->wram);                                                 /* (saved while the brothers march) */
    /* on the map, standing on a square: come back here, not to the last level entered */
    if (smb3_on_map()) {
        for (int p = 0; p < 2; p++) {
            uint8_t y = ZP(SMB3_World_Map_Y + p), xh = ZP(SMB3_World_Map_XHi + p), x = ZP(SMB3_World_Map_X + p);
            if ((y & 0x0F) || (x & 0x0F)) continue;                            /* (walking between squares) */
            s->wram[SMB3_Map_Entered_Y + p - 0x6000] = y;  s->wram[SMB3_Map_Previous_Y + p - 0x6000] = y;
            s->wram[SMB3_Map_Entered_XHi + p - 0x6000] = xh; s->wram[SMB3_Map_Previous_XHi + p - 0x6000] = xh;
            s->wram[SMB3_Map_Entered_X + p - 0x6000] = x;  s->wram[SMB3_Map_Previous_X + p - 0x6000] = x;
        }
    }
}
