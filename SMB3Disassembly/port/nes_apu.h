/* nes_apu.h - the NES sound (nes_apu.c) */
#pragma once
#include <stdint.h>
void apu_reset(void);
void apu_write(uint16_t addr, uint8_t v);        /* $4000-$4017 (not $4014 / $4016) */
uint8_t apu_status(void);                        /* $4015 */
void apu_catch_up(void);                         /* the sound up to now (nes_cyc) */
void apu_flush(void);                            /* the samples made so far dropped (a burst of held-back frames) */
int  apu_pull(int16_t *lr, int frames, int volume_pct);   /* 32 kHz stereo; returns samples that were there */
