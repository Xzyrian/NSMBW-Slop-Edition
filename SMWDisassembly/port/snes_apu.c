/* snes_apu.c - the SNES sound side, for now only as far as the CPU talks to it.
 *
 * The SPC700 starts in its boot ROM (the IPL), which shows $AA / $BB on ports 0 / 1 and takes
 * blocks of bytes: the CPU writes $CC (then a block's address on ports 2-3, a non-zero port 1)
 * and waits for it back, then each byte on port 1 with its index on port 0, waiting for the index
 * back; a new block is a port-0 value that isn't the next index, and port 1 = 0 starts the code at
 * the address given. That protocol is done here as the IPL does it, into the 64 KB the SPC700
 * has (aram), so the game's uploads (SMW's engine, samples, music banks) go through and are kept.
 *
 * The uploaded sound engine doesn't run yet: once started, the ports read back what the CPU last
 * wrote, except that SMW's "upload more" request ($FF on port 1) puts the IPL back. The game is
 * silent. (Next: the SPC700 and DSP, then SMW's music as NSMBW streams as SMB3's.) */
#include "snes_ppu.h"
#include <string.h>

static uint8_t aram[0x10000];
static uint8_t in[4], out[4];               /* in: written by the CPU; out: what it reads */
static int state;                           /* 0 the IPL waiting for $CC, 1 the IPL taking bytes, 2 the engine */
static uint16_t addr; static uint8_t next_idx;
static uint32_t uploaded;

void sapu_reset(void) {
    memset(aram, 0, sizeof aram); memset(in, 0, sizeof in); memset(out, 0, sizeof out);
    state = 0; out[0] = 0xAA; out[1] = 0xBB; uploaded = 0;
}
uint8_t sapu_port_rd(int p) { return out[p & 3]; }
static void ipl_ready(void) { state = 0; out[0] = 0xAA; out[1] = 0xBB; }
void sapu_port_wr(int p, uint8_t v) {
    p &= 3; in[p] = v;
    if (state == 2) {                       /* the engine: an echo, and the IPL again on request */
        if (p == 1 && v == 0xFF) { ipl_ready(); snes_log("apu: the engine hands back to the IPL (%u bytes so far)", uploaded); }
        else out[p] = v;
        return;
    }
    if (p != 0) return;                     /* (the IPL acts on port 0) */
    if (state == 0) {
        if (v == 0xCC) { addr = (uint16_t)(in[2] | in[3] << 8); next_idx = 0; state = 1; out[0] = v; }
        return;
    }
    if (v == next_idx) {                    /* a byte */
        aram[addr++] = in[1]; next_idx++; uploaded++; out[0] = v; return;
    }
    /* a new block, or the start */
    out[0] = v;
    addr = (uint16_t)(in[2] | in[3] << 8); next_idx = 0;
    if (in[1] == 0) { state = 2; snes_log("apu: code started at $%04X (%u bytes uploaded)", addr, uploaded); }
}
