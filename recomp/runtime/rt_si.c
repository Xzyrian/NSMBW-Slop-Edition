/* rt_si.c - the serial interface (SI, 0x0D006400): four GameCube controller ports.
 *
 * The 8-player module reads GameCube controllers as players (its CHAN_GC_0-3 channels, through
 * the SDK's PAD library). Players 5-8 of the port's Wii Remotes come in here (rt_remotes.c gives
 * each port's state); a port with nothing plugged in answers like an empty port.
 *
 * Registers (offsets from 0x6400), as on the hardware (Dolphin's SerialInterface):
 *   0x00/0x0C/0x18/0x24 SICnOUTBUF   the poll command (0x40 0x03 0x00: "standard poll, mode 3")
 *   +4 / +8             SICnINBUFH/L the last poll's 8 bytes (reading H clears the RDST bit)
 *   0x30 SIPOLL     EN bits 7..4 (port 0 = bit 7): which ports the hardware polls each field
 *   0x34 SICOMCSR   TSTART 0, CHANNEL 1-2, INLNGTH 8-14, OUTLNGTH 16-22, RDSTINTMSK 27,
 *                   RDSTINT 28 (read only), COMERR 29, TCINTMSK 30, TCINT 31
 *   0x38 SISR       per port 8 bits (port 0 = bits 24-31): NOREP +3, WRST +4, RDST +5
 *   0x80-0xFF       the transfer buffer
 * A transfer (TSTART) finishes at once: the command is the buffer's first byte - 0x00 / 0xFF
 * type (09 00 00: standard controller), 0x41 / 0x42 origin / recalibrate (10 bytes), 0x40 poll
 * (8 bytes). Polling runs once per video field (si_tick).
 *
 * Track A (docs/NATIVE_ROADMAP.md): the SDK's SI library is replaced by native functions at the
 * end of this file - the state above is now the library's own (what the controllers answered),
 * not registers: no SI register is read or written and no SI interrupt is raised. */
#include "rt.h"
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */

static uint32_t outbuf[4], inh[4], inl[4], sipoll, comcsr, sisr, exilk;
static uint8_t buf[128];

#define CSR_TSTART     (1u << 0)
#define CSR_RDSTINTMSK (1u << 27)
#define CSR_RDSTINT    (1u << 28)
#define CSR_COMERR     (1u << 29)
#define CSR_TCINTMSK   (1u << 30)
#define CSR_TCINT      (1u << 31)
#define SR_BIT(port, b) (1u << ((3 - (port)) * 8 + (b)))
enum { SR_NOREP = 3, SR_WRST = 4, SR_RDST = 5 };

static int any_rdst(void) { for (int p = 0; p < 4; p++) if (sisr & SR_BIT(p, SR_RDST)) return 1; return 0; }
static void update_irq(void) {
    /* (track A: the SI library is native - see the end of this file - and takes no interrupts) */
    (void)any_rdst;
}

/* a port's 8-byte poll answer: H = [flags | start y x b a][0x80 | l r z up down right left][stick x][stick y],
   L = [c-stick x][c-stick y][trigger l][trigger r] */
static int poll_port(int port, uint32_t *h, uint32_t *l) {
    uint8_t s[8];
    if (!remotes_gc_state(port, s)) return 0;
    *h = ((uint32_t)s[0] << 24) | ((uint32_t)(s[1] | 0x80) << 16) | ((uint32_t)s[2] << 8) | s[3];
    *l = ((uint32_t)s[4] << 24) | ((uint32_t)s[5] << 16) | ((uint32_t)s[6] << 8) | s[7];
    return 1;
}

static void transfer(void) {
    int port = (comcsr >> 1) & 3, inlen = (comcsr >> 8) & 0x7F;
    if (!inlen) inlen = 128;
    uint8_t cmd = buf[0];
    uint8_t s[8];

    int present = remotes_gc_state(port, s);
    comcsr &= ~(CSR_TSTART | CSR_COMERR);
    if (!present) {                                         /* nothing plugged in */
        sisr |= SR_BIT(port, SR_NOREP);
        comcsr |= CSR_COMERR;
    } else {
        sisr &= ~SR_BIT(port, SR_NOREP);
        uint8_t r[10]; int n = 0;
        switch (cmd) {
        case 0x00: case 0xFF: r[0] = 0x09; r[1] = 0x00; r[2] = 0x00; n = 3; break;            /* standard controller */
        case 0x41: case 0x42: {                                                               /* origin: centred, triggers low */
            static const uint8_t org[10] = {0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x1F, 0x1F, 0x00, 0x00};
            memcpy(r, org, 10); n = 10; break;
        }
        case 0x40: { uint32_t h, l; poll_port(port, &h, &l);
            r[0] = h >> 24; r[1] = h >> 16; r[2] = h >> 8; r[3] = h; r[4] = l >> 24; r[5] = l >> 16; r[6] = l >> 8; r[7] = l; n = 8; break; }
        default: rt_log("si", "port %d: unknown command %02X", port, cmd); break;
        }
        if (n > inlen) n = inlen;
        memcpy(buf, r, n);
    }
    comcsr |= CSR_TCINT;
    update_irq();
}

/* once per video field: the hardware polls the enabled ports */
void si_tick(void) {
    for (int p = 0; p < 4; p++) {
        if (!(sipoll & (0x80u >> p))) continue;
        uint32_t h, l;
        if (poll_port(p, &h, &l)) { inh[p] = h; inl[p] = l; sisr &= ~SR_BIT(p, SR_NOREP); sisr |= SR_BIT(p, SR_RDST); }
        else sisr |= SR_BIT(p, SR_NOREP);                                           /* no controller */
    }
    update_irq();
}

/* SITransfer: a port's first transfer is held until "the last transfer + the delay" (XferTime,
   0 at boot) - but the system time is negative early on here (0x800030D8 = -1 high word), so
   that time lies about a minute ahead and the type probes wait for it. A port that never
   transferred counts as long ago. */
#define SI_XFER_TIME 0x8038F850u        /* OSTime XferTime[4] */
void hle_SITransfer(ppc_context *ctx, uint8_t *base) {
    uint32_t chan = ctx->r[3] & 3, t = SI_XFER_TIME + 8 * chan;
    if (!R32(t) && !R32(t + 4)) W32(t, 0x80000000u);
    orig_SITransfer(ctx, base);
}

/* ------------------------------------------------------------------ the SI library, native (track A4)
 * Decompiled from the USA rev 2 SDK (si.c; the 8-player module carries its own copies of the
 * SIGetStatus / SISetCommand / SIEnablePolling / SIDisablePolling / SIGetResponse group), with the
 * registers replaced by the state above. A transfer is answered at once; its completion (callback,
 * queued packets, the type re-probe) runs "from an interrupt" as a native event. */
#define SI_SI        0x8033FF90u     /* Si: +0 chan (-1 idle), +4 poll, +8 inputBytes, +0xC input, +0x10 callback */
#define SI_TYPE      0x8033FFA8u     /* Type[4] */
#define SI_RATES     0x8033FFB8u     /* XY tables: NTSC (12 x {u16 line, u8 count}), PAL at +0x30 */
#define SI_PACKET    0x8038F7D0u     /* Packet[4] (0x20): chan, output, outputBytes, input, inputBytes, callback, fire time */
#define SI_ALARM     0x8038F890u     /* Alarm[4] (0x30) */
#define SI_XFERTIME  0x8038F850u     /* (OSTime[4]) */
#define SI_TYPETIME  0x8038F870u
#define SI_INBUF     0x8038F950u     /* InputBuffer[4][2] */
#define SI_INVALID   0x8038F970u     /* InputBufferValid[4] */
#define SDA          0x8042F680u
#define F_GetTypeCallback 0x801BB3C0u
#define F_OSGetSystemTime 0x801B5FB0u
#define F_OSCancelAlarm   0x801AB640u
#define F_OSRegisterVersion 0x801AB1C0u
#define F_SIGetType       0x801BB680u
#define F_SITransfer      0x801BB250u
#define F_VIGetTvFormat   0x801BE010u
#define F_OSReport        0x8015F730u
#define SI_TC_FN          0x80001F30u     /* guest address of si_complete (rt_register_native) */

static uint8_t tc_resp[128]; static int tc_n, tc_err;     /* the answer of the transfer in flight */

static uint32_t gcall(ppc_context *ctx, uint32_t fn, uint32_t a0, uint32_t a1, uint32_t a2, uint32_t a3, uint32_t a4, uint32_t a5) {
    uint32_t lr = ctx->lr;
    ctx->r[3] = a0; ctx->r[4] = a1; ctx->r[5] = a2; ctx->r[6] = a3; ctx->r[7] = a4; ctx->r[8] = a5;
    ppc_call_indirect(ctx, g_base, fn);
    ctx->lr = lr;
    return ctx->r[3];
}
static int64_t systime(ppc_context *ctx) {
    gcall(ctx, F_OSGetSystemTime, 0, 0, 0, 0, 0, 0);
    return (int64_t)(((uint64_t)ctx->r[3] << 32) | ctx->r[4]);
}
static void w64(uint32_t a, int64_t v) { W32(a, (uint32_t)((uint64_t)v >> 32)); W32(a + 4, (uint32_t)v); }
static int64_t r64(uint32_t a) { return (int64_t)(((uint64_t)R32(a) << 32) | R32(a + 4)); }
static void clear_errors(int chan) { sisr &= ~(0x0F000000u >> (chan * 8)); }

/* __SITransfer (fn_801BAFB0): start a transfer if the bus is free */
static int si_start(ppc_context *ctx, uint32_t chan, uint32_t out, uint32_t out_n, uint32_t in, uint32_t in_n, uint32_t cb) {
    (void)ctx;
    if ((int32_t)R32(SI_SI) != -1) return 0;
    chan &= 3;
    clear_errors((int)chan);
    W32(SI_SI, chan); W32(SI_SI + 0x10, cb); W32(SI_SI + 8, in_n); W32(SI_SI + 0xC, in);
    for (uint32_t i = 0; i < out_n && i < 128; i++) buf[i] = R8(out + i);
    comcsr = (comcsr & ~(3u << 1) & ~(0x7Fu << 8)) | (chan << 1) | ((in_n & 0x7F) << 8);
    transfer();                                              /* (the answer, into buf; sisr / COMERR) */
    tc_n = (int)(in_n < 128 ? in_n : 128); memcpy(tc_resp, buf, (size_t)tc_n);
    tc_err = (comcsr & CSR_COMERR) != 0;
    comcsr &= ~CSR_TCINT;
    static int reg; if (!reg) { reg = 1; extern void si_complete(ppc_context *, uint8_t *); rt_register_native(SI_TC_FN, si_complete); }
    rt_post_callback(SI_TC_FN, 0, 0);
    return 1;
}
void hle_fn_801BAFB0(ppc_context *ctx, uint8_t *base) {
    (void)base;
    ctx->r[3] = (uint32_t)si_start(ctx, ctx->r[3], ctx->r[4], ctx->r[5], ctx->r[6], ctx->r[7], ctx->r[8]);
}
/* CompleteTransfer: the answer into the caller's buffer, the status */
static uint32_t si_finish(ppc_context *ctx) {
    uint32_t chan = R32(SI_SI);
    if ((int32_t)chan == -1) return 0;
    int64_t now = systime(ctx);
    w64(SI_XFERTIME + 8 * chan, now);
    uint32_t in = R32(SI_SI + 0xC), n = R32(SI_SI + 8);
    for (uint32_t i = 0; i < n && i < (uint32_t)tc_n; i++) W8(in + i, tc_resp[i]);
    uint32_t st;
    if (tc_err) {
        st = (sisr >> ((3 - chan) * 8)) & 0xF;
        if ((st & 8) && !(R32(SI_TYPE + 4 * chan) & 0x80)) W32(SI_TYPE + 4 * chan, 8);
        if (!st) st = 4;
    } else { w64(SI_TYPETIME + 8 * chan, now); st = 0; }
    W32(SI_SI, 0xFFFFFFFFu);
    return st;
}
/* the transfer-complete half of SIInterruptHandler */
void si_complete(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t chan = R32(SI_SI), cb = R32(SI_SI + 0x10);
    if ((int32_t)chan == -1) return;
    W32(SI_SI + 0x10, 0);
    uint32_t st = si_finish(ctx);
    for (int i = 1; i <= 4; i++) {                           /* a transfer queued for later whose time has come */
        uint32_t c = (chan + (uint32_t)i) & 3, P = SI_PACKET + 0x20 * c;
        if ((int32_t)R32(P) == -1) continue;
        if (systime(ctx) < r64(P + 0x18)) continue;
        if (si_start(ctx, R32(P), R32(P + 4), R32(P + 8), R32(P + 0xC), R32(P + 0x10), R32(P + 0x14))) {
            gcall(ctx, F_OSCancelAlarm, SI_ALARM + 0x30 * c, 0, 0, 0, 0, 0);
            W32(P, 0xFFFFFFFFu);
        }
        break;
    }
    if (cb) gcall(ctx, cb, chan, st, R32(0x800000D4), 0, 0, 0);   /* (running as a native event: the current context is the interrupted one) */
    clear_errors((int)chan);
    if (R32(SI_TYPE + 4 * chan) == 0x80 && (int32_t)R32(SI_PACKET + 0x20 * chan) == -1 && R32(SI_SI) != chan) {
        /* a type probe still running: ask again in 65 us */
        uint32_t t = (uint32_t)(((uint64_t)0x431BDE83u * (R32(0x800000F8) >> 2)) >> 32);
        uint32_t delay = (((t >> 9) & 0x007FFFC0u) + (t >> 15)) >> 3;
        uint32_t lr = ctx->lr;
        ctx->r[3] = chan; ctx->r[4] = SDA - 0x4ee0; ctx->r[5] = 1; ctx->r[6] = SI_TYPE + 4 * chan; ctx->r[7] = 3;
        ctx->r[8] = F_GetTypeCallback; ctx->r[9] = 0; ctx->r[10] = delay;
        ppc_call_indirect(ctx, g_base, F_SITransfer);
        ctx->lr = lr;
    }
}

/* SIInit */
void hle_SIInit(ppc_context *ctx, uint8_t *base) {
    (void)base;
    if (R32(SDA - 0x4edc)) return;
    gcall(ctx, F_OSRegisterVersion, R32(SDA - 0x6120), 0, 0, 0, 0, 0);
    for (int c = 0; c < 4; c++) W32(SI_PACKET + 0x20 * c, 0xFFFFFFFFu);
    W32(SI_SI + 4, 0);
    gcall(ctx, 0x801BB840u, 0, 0, 0, 0, 0, 0);              /* SISetSamplingRate(0) */
    comcsr = 0;                                              /* (no interrupt handler: completions are native events) */
    for (uint32_t c = 0; c < 4; c++) gcall(ctx, F_SIGetType, c, 0, 0, 0, 0, 0);
    W32(SDA - 0x4edc, 1);
}
/* SISetXY(line, count): the polling interval */
static uint32_t set_xy(uint32_t x, uint32_t y) {
    uint32_t v = (R32(SI_SI + 4) & 0xFC0000FFu) | (x << 16) | (y << 8);
    W32(SI_SI + 4, v); sipoll = v;
    return v;
}
void hle_SISetXY(ppc_context *ctx, uint8_t *base) { (void)base; ctx->r[3] = set_xy(ctx->r[3], ctx->r[4]); }
/* SISetSamplingRate(msec): the XY pair for the TV format; the VI "VISEL" doubling: progressive off */
void hle_SISetSamplingRate(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t rate = ctx->r[3] > 11 ? 11 : ctx->r[3];
    W32(SDA - 0x4ed0, rate);
    uint32_t tv = gcall(ctx, F_VIGetTvFormat, 0, 0, 0, 0, 0, 0), tab;
    if (tv == 0 || tv == 2 || tv == 5) tab = SI_RATES;
    else if (tv == 1) tab = SI_RATES + 0x30;
    else { gcall(ctx, F_OSReport, SI_RATES + 0x60, 0, 0, 0, 0, 0); rate = 0; tab = SI_RATES; }
    set_xy(1 * R16(tab + 4 * rate), R8(tab + 4 * rate + 2));
}
/* the module's group (8-player module, d_project.rel) */
static uint32_t get_status(uint32_t chan) {
    uint32_t st = sisr >> ((3 - chan) * 8);
    if ((st & 8) && !(R8(SI_TYPE + 4 * chan + 3) & 0x80)) W32(SI_TYPE + 4 * chan, 8);
    return st;
}
void hle_mfn_8184105C(ppc_context *ctx, uint8_t *base) { (void)base; ctx->r[3] = get_status(ctx->r[3] & 3); }  /* SIGetStatus */
void hle_mfn_818410D8(ppc_context *ctx, uint8_t *base) { (void)base; if (ctx->r[3] < 4) outbuf[ctx->r[3]] = ctx->r[4]; }   /* SISetCommand */
void hle_mfn_81841124(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }                                  /* SITransferCommands */
void hle_mfn_81841134(ppc_context *ctx, uint8_t *base) {                                                           /* SIEnablePolling */
    (void)base;
    uint32_t poll = ctx->r[3];
    if (poll) { uint32_t v = (R32(SI_SI + 4) & ~(poll >> 28)) | (poll >> 24); W32(SI_SI + 4, v); sipoll = v; }
    ctx->r[3] = R32(SI_SI + 4);
}
void hle_mfn_818411D8(ppc_context *ctx, uint8_t *base) {                                                           /* SIDisablePolling */
    (void)base;
    uint32_t poll = ctx->r[3];
    if (poll) { uint32_t v = R32(SI_SI + 4) & ~(poll >> 24); W32(SI_SI + 4, v); sipoll = v; }
    ctx->r[3] = R32(SI_SI + 4);
}
void hle_mfn_81841264(ppc_context *ctx, uint8_t *base) {                                                           /* SIGetResponse(chan, data) */
    (void)base;
    uint32_t chan = ctx->r[3] & 3, data = ctx->r[4], ok;
    if (get_status(chan) & 0x20) {                                       /* a fresh poll */
        W32(SI_INBUF + 8 * chan, inh[chan]); W32(SI_INBUF + 8 * chan + 4, inl[chan]);
        sisr &= ~SR_BIT(chan, SR_RDST);
        W32(SI_INVALID + 4 * chan, 0); ok = 1;
    } else { ok = R32(SI_INVALID + 4 * chan); W32(SI_INVALID + 4 * chan, 0); }
    if (ok) { W32(data, R32(SI_INBUF + 8 * chan)); W32(data + 4, R32(SI_INBUF + 8 * chan + 4)); }
    ctx->r[3] = ok;
}
