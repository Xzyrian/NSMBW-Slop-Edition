/* nes.h - the NES under the recompiled SMB3 (port/nes_cpu.c, nes_ppu.c): what the rest of the
 * runtime uses. One NES; the recompiled 6502 code runs in its own coroutine, one frame per
 * nes_run_frame(). */
#pragma once
#include <stdint.h>

int  nes_load(const uint8_t *ines, uint32_t size);   /* an iNES image (copied); 0 = bad */
void nes_reset(void);
void nes_run_frame(void);                           /* to the next vblank: the frame is drawn */
const uint32_t *nes_framebuffer(void);              /* 256 x 240, 0xAARRGGBB */
enum { NES_A = 1, NES_B = 2, NES_SELECT = 4, NES_START = 8, NES_UP = 16, NES_DOWN = 32, NES_LEFT = 64, NES_RIGHT = 128 };
void nes_set_buttons(int pad, uint8_t buttons);
uint8_t *nes_ram_ptr(void);                         /* $0000-$07FF */
uint8_t *nes_wram_ptr(void);                        /* $6000-$7FFF */
const char *nes_error(void);                        /* why it stopped, or NULL */
uint64_t nes_frame_count(void);
/* the game held where it is, its sound engine run alone for that many CPU cycles (once a frame:
   the engine's banks at $A000 / $C000, as the NMI has them) - the APU's samples made meanwhile */
void nes_sound_run(uint16_t engine, uint8_t bank_a000, uint8_t bank_c000, uint64_t cycles);
void nes_set_log(void (*fn)(const char *msg));
/* the PPU as it is now (for building pictures outside the NES frame: smb3_stage.c) */
uint8_t ppu_peek_chr(uint16_t addr);                /* a byte of the pattern tables ($0000-$1FFF, as mapped now) */
uint8_t ppu_peek_pal(int i);                        /* palette RAM (0-31) */
uint8_t ppu_peek_ctrl(void);                        /* $2000 */
uint32_t ppu_rgb(int colour);                       /* an NES colour as 0xAARRGGBB */
void ppu_capture_at(int line);                      /* snapshot the pattern tables as mapped when drawing this line */
const uint8_t *ppu_captured_chr(void);              /* (8 KB, $0000-$1FFF) */
uint8_t ppu_captured_ctrl(void);                    /* $2000 then (bit 4: the background's table) */
uint8_t ppu_peek_nt(uint16_t addr);                 /* a name / attribute table byte ($2000-$2FFF, mirrored) */
