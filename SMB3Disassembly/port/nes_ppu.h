/* nes_ppu.h - the PPU (nes_ppu.c), between nes_cpu.c and it */
#pragma once
#include <stdint.h>
extern const uint8_t *ppu_chr_slot[8];      /* the 1 KB pattern banks at $0000-$1FFF (MMC3) */
extern int ppu_mirror_h;                    /* 1 horizontal mirroring, 0 vertical */
extern uint32_t ppu_fb[256 * 240];
void ppu_reset(void);
uint8_t ppu_read(int reg);
void ppu_write(int reg, uint8_t v);
void ppu_oam_dma(const uint8_t *page);
void ppu_catch_up(int dot);                 /* draw the lines whose dot 260 has passed */
int ppu_next_line(void);
void ppu_vblank(void);
void ppu_prerender(void);
void ppu_frame_start(void);
int ppu_nmi_on(void);
/* nes_cpu.c */
void nes_mmc3_clock(void);
void nes_nmi_edge(void);
void ppu_catch_up_now(void);
