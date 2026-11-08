/* rt_exi.c - the EXI bus, native (track A of docs/NATIVE_ROADMAP.md).
 *
 * On the Wii the EXI bus (0x0D006800) carries the real-time clock and the SRAM (channel 0,
 * device 1: the "Macronix" chip) plus memory-card / debugger slots nobody uses here. The SDK's EXI
 * library (EXILock / EXISelect / EXIImm / EXIDma / EXISync / ...) drives the bus registers and
 * finishes transfers from the EXI interrupt. Here those library functions are native: a transfer
 * talks to the device directly and is done when the call returns; a completion callback, if any,
 * runs "from an interrupt" (rt_post_callback). No EXI register, no EXI interrupt.
 *
 * The RTC/SRAM chip protocol (what the OS's __OSGetRTC / __OSInitSram / __OSSyncSram /
 * __OSGetRTCFlags... send): a 4-byte command by immediate write, then data by immediate read/write
 * or DMA. Command: bit 31 = write, 0x20000000 + offset << 6 addresses the chip (bit 8 set: SRAM,
 * clear: the RTC counter), 0x21000000.. the RTC control/flags. */
#include "rt.h"
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */

#define SDA 0x8042F680u
static uint8_t sram[64];
static int sram_ready;
static struct { int sel, dev, have_cmd; uint32_t cmd; } ch[3];

static void sram_init(void) {
    /* Dolphin's default SRAM, then the checksums over bytes 0x0C-0x13 */
    static const uint8_t def[64] = {
        0xFF, 0x6B, 0x00, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x2C, 0x44, 0x4F, 0x4C, 0x50, 0x48, 0x49, 0x4E, 0x53, 0x4C, 0x4F, 0x54, 0x41,
        0x44, 0x4F, 0x4C, 0x50, 0x48, 0x49, 0x4E, 0x53, 0x4C, 0x4F, 0x54, 0x42, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    memcpy(sram, def, 64);
    uint16_t c1 = 0, c2 = 0;
    for (int i = 0x0C; i < 0x14; i += 2) { uint16_t w = (uint16_t)((sram[i] << 8) | sram[i + 1]); c1 += w; c2 += (uint16_t)~w; }
    sram[0] = (uint8_t)(c1 >> 8); sram[1] = (uint8_t)c1; sram[2] = (uint8_t)(c2 >> 8); sram[3] = (uint8_t)c2;
    sram_ready = 1;
}
static uint32_t rtc_secs(void) {                 /* seconds since 2000-01-01 */
    return g_det ? det_rtc_secs() : (uint32_t)(rt_now_ns() / 1000000000ull) + 0x386D4380u;
}
static int is_chip(int c) { return c == 0 && ch[0].sel && ch[0].dev == 1; }

/* one transfer on channel c: type 0 read, 1 write, 2 read+write; buf = guest address */
static void xfer(int c, uint32_t buf, uint32_t len, uint32_t type, int dma) {
    if (!sram_ready) sram_init();
    if (!is_chip(c)) {                                       /* nothing attached: reads give 0 */
        if (type != 1) for (uint32_t i = 0; i < len; i++) W8(buf + i, 0);
        return;
    }
    if (!ch[c].have_cmd && type == 1 && !dma) {              /* the first immediate write: the command */
        uint32_t v = 0; for (uint32_t i = 0; i < len && i < 4; i++) v |= (uint32_t)R8(buf + i) << (24 - 8 * i);
        ch[c].cmd = v; ch[c].have_cmd = 1;
        return;
    }
    uint32_t cmd = ch[c].cmd, off = (cmd >> 6) & 0xFF;
    if (type == 0) {
        if ((cmd & 0x7FFFFF00u) == 0x20000000u && !(cmd & 0x100)) {            /* the RTC counter */
            uint32_t s = rtc_secs();
            for (uint32_t i = 0; i < len && i < 4; i++) W8(buf + i, (uint8_t)(s >> (24 - 8 * i)));
        } else if (dma) for (uint32_t i = 0; i < len; i++) W8(buf + i, i < 64 ? sram[i] : 0);
        else for (uint32_t i = 0; i < len && i < 4; i++) W8(buf + i, sram[(off + i) % 64]);
    } else if (type == 1 && dma) {
        for (uint32_t i = 0; i < len && i < 64; i++) sram[i] = R8(buf + i);
    }
    /* (RTC writes / flag writes: the PC's clock is the clock) */
}
static void done_cb(uint32_t cb, int c) { if (cb) rt_post_callback(cb, (uint32_t)c, 0xFFFFFFFFu); }   /* (chan, the context current then) */

#define A(n) ctx->r[n]
void hle_EXIInit(ppc_context *ctx, uint8_t *base) {
    (void)base;
    memset(ch, 0, sizeof ch);
    W32(SDA - 0x4ef8, 0);                                    /* (EXIGetID(0, 2): no USB Gecko / "barnacle") */
    if (R32(SDA - 0x5048)) { W32(0x800030C4, 0); W32(0x800030C0, 0); W32(0x8038F710u + 0x60, 0); W32(0x8038F710u + 0x20, 0); }
    uint32_t lr = ctx->lr; A(3) = R32(SDA - 0x6128); ppc_call_indirect(ctx, g_base, 0x801AB1C0u); ctx->lr = lr;   /* OSRegisterVersion */
}
void hle_EXILock(ppc_context *ctx, uint8_t *base)    { (void)base; A(3) = 1; }
void hle_EXIUnlock(ppc_context *ctx, uint8_t *base)  { (void)base; A(3) = 1; }
void hle_EXISelect(ppc_context *ctx, uint8_t *base) {
    (void)base;
    int c = (int)A(3); if (c < 0 || c > 2) { A(3) = 0; return; }
    ch[c].sel = 1; ch[c].dev = (int)A(4); ch[c].have_cmd = 0;
    A(3) = 1;
}
void hle_EXIDeselect(ppc_context *ctx, uint8_t *base) {
    (void)base;
    int c = (int)A(3); if (c < 0 || c > 2) { A(3) = 0; return; }
    ch[c].sel = 0; ch[c].have_cmd = 0;
    A(3) = 1;
}
void hle_EXIImm(ppc_context *ctx, uint8_t *base) {          /* (chan, buf, len, type, callback) */
    (void)base;
    int c = (int)A(3); if (c < 0 || c > 2) { A(3) = 0; return; }
    xfer(c, A(4), A(5), A(6), 0); done_cb(A(7), c);
    A(3) = 1;
}
void hle_EXIImmEx(ppc_context *ctx, uint8_t *base) {        /* (chan, buf, len, mode): in 4-byte pieces */
    (void)base;
    int c = (int)A(3); if (c < 0 || c > 2) { A(3) = 0; return; }
    uint32_t buf = A(4), len = A(5), type = A(6);
    while (len) { uint32_t n = len < 4 ? len : 4; xfer(c, buf, n, type, 0); buf += n; len -= n; }
    A(3) = 1;
}
void hle_EXIDma(ppc_context *ctx, uint8_t *base) {          /* (chan, buf, len, type, callback) */
    (void)base;
    int c = (int)A(3); if (c < 0 || c > 2) { A(3) = 0; return; }
    xfer(c, A(4), A(5), A(6), 1); done_cb(A(7), c);
    A(3) = 1;
}
void hle_EXISync(ppc_context *ctx, uint8_t *base)    { (void)base; A(3) = 1; }   /* (every transfer is already done) */
void hle___EXIProbe(ppc_context *ctx, uint8_t *base) { (void)base; A(3) = A(3) == 0; }   /* (channel 0: the RTC/SRAM chip) */
void hle_EXIAttach(ppc_context *ctx, uint8_t *base)  { (void)base; A(3) = 0; }   /* (no memory card) */
void hle_EXIDetach(ppc_context *ctx, uint8_t *base)  { (void)base; A(3) = 1; }
void hle_EXIGetID(ppc_context *ctx, uint8_t *base) {        /* (chan, dev, &id) */
    (void)base;
    W32(A(5), 0);
    A(3) = A(3) == 0 ? 1 : 0;
}
void hle_EXISetExiCallback(ppc_context *ctx, uint8_t *base) { (void)base; A(3) = 0; }
#undef A
