/* snes_ppu.h - between the SNES parts (snes_cpu.c, snes_ppu.c, snes_apu.c) */
#pragma once
#include <stdint.h>
/* the PPU (snes_ppu.c) */
void sppu_reset(void);
uint8_t sppu_read(uint8_t reg);              /* $21xx */
void sppu_write(uint8_t reg, uint8_t v);
void sppu_render_row(int row);               /* screen row 0-223 (V line row + 1), as the PPU is set now */
void sppu_frame_begin(void);
extern uint32_t sppu_fb[256 * 224];
extern int sppu_overscan;                    /* $2133 bit 2: 239 lines (SMW: 224) */
void sppu_latch_counters(int h, int v);      /* ($2137 / $4201) */
/* (for other code: the PPU's memory and a BG's settings - smw_stage.c) */
const uint16_t *sppu_vram(void);
const uint16_t *sppu_cgram(void);
void sppu_bg(int n, uint8_t *sc, uint8_t *nba, uint16_t *hofs, uint16_t *vofs, uint8_t *mode);
/* the sound side (snes_apu.c): only the boot ROM's upload protocol for now - the sound engine
   doesn't run yet, so the game is silent */
void sapu_reset(void);
uint8_t sapu_port_rd(int port);
void sapu_port_wr(int port, uint8_t v);
/* snes_cpu.c */
void snes_ppu_catch_up(void);               /* draw the rows whose time has passed, before a PPU change */
void snes_log(const char *fmt, ...);
