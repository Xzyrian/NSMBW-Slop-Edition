/* snes.h - the SNES under the recompiled SMW (port/snes_cpu.c, snes_ppu.c, snes_apu.c): what the
 * rest of the runtime uses. One SNES; the recompiled 65816 code runs in its own coroutine, one
 * frame per snes_run_frame(). */
#pragma once
#include <stdint.h>

int  snes_load(const uint8_t *rom, uint32_t size);   /* a LoROM image (a copier header is skipped); 0 = bad */
void snes_reset(void);
void snes_run_frame(void);                           /* to the next vblank: the frame is drawn */
const uint32_t *snes_framebuffer(void);              /* 256 x 224, 0xAARRGGBB */
enum { SNES_R = 0x0010, SNES_L = 0x0020, SNES_X = 0x0040, SNES_A = 0x0080, SNES_RIGHT = 0x0100, SNES_LEFT = 0x0200,
       SNES_DOWN = 0x0400, SNES_UP = 0x0800, SNES_START = 0x1000, SNES_SELECT = 0x2000, SNES_Y = 0x4000, SNES_B = 0x8000 };
void snes_set_buttons(int pad, uint16_t buttons);    /* (as $4218/$4219 read them) */
uint8_t *snes_wram_ptr(void);                        /* $7E0000-$7FFFFF */
uint8_t *snes_sram_ptr(void);                        /* $700000 - 2 KB */
uint32_t snes_sram_size(void);
const char *snes_error(void);                        /* why it stopped, or NULL */
uint64_t snes_frame_count(void);
void snes_set_log(void (*fn)(const char *msg));
