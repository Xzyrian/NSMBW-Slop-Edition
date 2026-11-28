/* smb1_cpu.h - a small 6502 that runs Super Mario Bros.' own code from its ROM (smb1_mario.c).
 *
 * Retro Mario (SMB1) is not a port: his movement, his pictures and his sounds are SMB1's own
 * routines (PlayerMovementSubs, PlayerGfxHandler, SoundEngine), run here instruction by
 * instruction on the player's own copy of the NES's 2 KB of RAM. Memory: $0000-$07FF RAM
 * (mirrored to $1FFF), $4000-$4017 the APU (a hook), $8000-$BFFF one 16 KB PRG bank,
 * $C000-$FFFF the last (fixed) bank - the layout of SMB1Disassembly's MMC3 build (8 PRG banks of
 * 16 KB, the original game's second half fixed). Writes to the mapper are ignored (the routines
 * run here don't switch banks). Decimal mode isn't there (the NES's 6502 has none). */
#pragma once
#include <stdint.h>

typedef struct smb1_cpu {
    uint8_t a, x, y, s, p;
    uint16_t pc;
    uint8_t *ram;                                  /* 2 KB */
    const uint8_t *bank8, *bankC;                  /* 16 KB each, at $8000 and $C000 */
    void (*apu)(void *user, uint16_t addr, uint8_t v);   /* $4000-$4017 writes (or NULL) */
    void *user;
    uint64_t cycles;
    int error;                                     /* an opcode it doesn't know, or out of steps */
} smb1_cpu;

/* call the routine at addr (JSR) and run until it returns; 0 = ok */
int smb1_cpu_call(smb1_cpu *c, uint16_t addr, int max_steps);
