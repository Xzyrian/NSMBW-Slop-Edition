/* rt_wiimote.c - the Wii Remotes the game sees (WPAD channels 0-3, players' remotes 1-4 in
 * rt_remotes.c's slots 0-3), connected to the SDK's WPAD library natively (track A4,
 * docs/NATIVE_ROADMAP.md).
 *
 * On a Wii, WPAD sits on WUD (the "Wii USB device" layer), which drives the Broadcom Bluetooth
 * stack (BTA/BTM/L2CAP/HCI) over the Bluetooth USB dongle in IOS. WPAD only needs three things
 * from all that: "a remote connected / went away" (WUD's HID connection callback), "this input
 * report arrived" (WUD's HID receive callback), and a way to send an output report
 * (BTA_HhSendData). So WUD is native here (the WUD API WPAD calls, decompiled against the
 * Twilight Princess SDK decompilation, minus the Bluetooth stack), and the remotes hand their HID
 * reports straight to WPAD - no Bluetooth, L2CAP, HCI or IOS USB device underneath.
 *
 * Each remote is driven by what its player slot holds (rt_remotes.c): a real remote (its HID
 * reports pass straight through, Dolphin's "Real Wii Remote"; the player lights are put in by
 * rt_remotes.c), the keyboard (an emulated remote answering like a real one), or nothing.
 * Remote 0 is always connected (the title needs a player 1); remotes 1-3 connect while their
 * slot has a real remote or the keyboard, one at a time in slot order. */
#include "rt.h"
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */

#define NWM 4
enum { ST_IDLE, ST_CONNECTED };

typedef struct {
    int idx; uint8_t addr[6];                               /* LSB-first (BD_ADDR reversed) */
    int state; uint64_t t_state;
    uint8_t leds, report_mode, continuous, ir_on, speaker_on;
    uint32_t last_btn; uint64_t t_last_report;
    struct { int active; uint32_t addr; int left; int space; } rd;   /* pending memory read */
    int dev;                                                /* real remote passed through (-1: none) */
    uint8_t saved_out[0x20][23]; int saved_len[0x20];      /* state-setting output reports, replayed on attach */
    uint8_t pend[64][23]; int pend_len[64], npend;          /* its input reports waiting to go to WPAD */
    uint32_t real_btn, game_btn;
    int announced, shake_phase, shake_left, shake_n;
    uint64_t in_frame;                                      /* frame it connected */
    int inflight; uint32_t rx_next;                         /* reports handed to WPAD, not yet delivered */
} wm_t;
static wm_t W[NWM];
static uint8_t eeprom[0x1700];
static int in_update;

/* ---- the emulated remote ---- */
static void eeprom_init(void) {
    static const uint8_t cal[10] = {0x80, 0x80, 0x80, 0x00, 0x9A, 0x9A, 0x9A, 0x00, 0x40, 0xE3};
    /* IR calibration (Dolphin defaults) at 0x00 and 0x0B */
    static const uint8_t ir[11] = {0x66, 0x6E, 0x77, 0xB8, 0x83, 0x71, 0x89, 0x88, 0x30, 0x00, 0x00};
    memcpy(eeprom + 0x00, ir, 11); memcpy(eeprom + 0x0B, ir, 11);
    memcpy(eeprom + 0x16, cal, 10); memcpy(eeprom + 0x20, cal, 10);
}
static void hid_send(wm_t *w, const uint8_t *d, int len);   /* an input report to WPAD (below) */
static void put_buttons(uint8_t *p, uint32_t btn) { p[0] = btn & 0x1F; p[1] = (btn >> 8) & 0x9F; }
static void send_ack(wm_t *w, uint8_t rpt, uint8_t err) {
    uint8_t r[5] = {0x22}; put_buttons(r + 1, w->game_btn); r[3] = rpt; r[4] = err; hid_send(w, r, 5);
}
static void send_status(wm_t *w) {
    uint8_t r[7] = {0x20};
    put_buttons(r + 1, w->game_btn);
    r[3] = (w->speaker_on ? 0x04 : 0) | (w->ir_on ? 0x08 : 0) | (w->leds << 4);
    r[6] = 0xC0;                                            /* battery */
    hid_send(w, r, 7);
}
/* shake (keyboard): a strong back-and-forth swing that flips every second report, so the game
   sees the motion change from one frame to the next whatever the report timing. A tap shakes
   for at least 16 reports (~160 ms) so short presses register. Returns 1 while shaking (and
   sets the accelerometer bytes). Called once per report sent. */
static int kb_shake_accel(wm_t *w, uint32_t btn, uint8_t *ax, uint8_t *ay, uint8_t *az) {
    if (btn & 0x10000) { if (!w->shake_phase) { w->shake_phase = 1; w->shake_n = 0; } w->shake_left = 16; }
    else if (w->shake_phase && --w->shake_left <= 0) w->shake_phase = 0;
    if (!w->shake_phase) return 0;
    int ph = (w->shake_n++ >> 1) & 1;
    *ax = ph ? 0x10 : 0xF0; *ay = ph ? 0xF0 : 0x10; *az = ph ? 0x30 : 0xE0;
    return 1;
}
static void send_data_report(wm_t *w) {
    uint32_t btn = w->game_btn;
    uint8_t r[22]; memset(r, 0, sizeof r);
    r[0] = w->report_mode; put_buttons(r + 1, btn);
    uint8_t ax = 0x80, ay = 0x80, az = 0x9A;
    kb_shake_accel(w, btn, &ax, &ay, &az);
    int n;
    switch (w->report_mode) {
    case 0x30: n = 3; break;
    case 0x31: r[3] = ax; r[4] = ay; r[5] = az; n = 6; break;
    case 0x32: memset(r + 3, 0xFF, 8); n = 11; break;
    case 0x33: r[3] = ax; r[4] = ay; r[5] = az; memset(r + 6, 0xFF, 12); n = 18; break;
    case 0x34: memset(r + 3, 0xFF, 19); n = 22; break;
    case 0x35: r[3] = ax; r[4] = ay; r[5] = az; memset(r + 6, 0xFF, 16); n = 22; break;
    case 0x36: memset(r + 3, 0xFF, 19); n = 22; break;
    case 0x37: r[3] = ax; r[4] = ay; r[5] = az; memset(r + 6, 0xFF, 16); n = 22; break;
    case 0x3D: memset(r + 1, 0xFF, 21); n = 22; break;
    default: r[0] = 0x30; n = 3; break;
    }
    hid_send(w, r, n);
    w->last_btn = btn;
}
static void read_step(wm_t *w) {                             /* one 0x21 report of a pending read */
    uint8_t r[22]; memset(r, 0, sizeof r);
    r[0] = 0x21; put_buttons(r + 1, w->game_btn);
    int n = w->rd.left > 16 ? 16 : w->rd.left, err = 0;
    if (w->rd.space == 0) {                                 /* EEPROM */
        if (w->rd.addr + n > sizeof eeprom) err = 8;
        else memcpy(r + 6, eeprom + w->rd.addr, n);
    } else {                                                /* control registers */
        uint32_t reg = (w->rd.addr >> 16) & 0xFE;
        if (reg == 0xA4) err = 7;                           /* no extension connected */
    }
    r[3] = (uint8_t)(((n - 1) << 4) | err);
    r[4] = (w->rd.addr >> 8) & 0xFF; r[5] = w->rd.addr & 0xFF;
    hid_send(w, r, 22);
    if (err) { w->rd.active = 0; return; }
    w->rd.addr += n; w->rd.left -= n;
    if (w->rd.left <= 0) w->rd.active = 0;
}

/* ---- a real remote passed through ---- */
static int is_data_report(uint8_t id) { return id >= 0x30 && id <= 0x3F; }
static int has_buttons(const uint8_t *r, int n) { return n >= 3 && ((r[0] >= 0x20 && r[0] <= 0x22) || (r[0] >= 0x30 && r[0] <= 0x37)); }
static void merge_buttons(wm_t *w, uint8_t *r, int n) {     /* the buttons the game may see (menus, keyboard) */
    if (!has_buttons(r, n)) return;
    r[1] = (r[1] & ~0x1F) | (w->game_btn & 0x1F); r[2] = (r[2] & ~0x9F) | ((w->game_btn >> 8) & 0x9F);
    uint8_t ax, ay, az;                                     /* keyboard shake overrides the remote's motion */
    if ((r[0] == 0x31 || r[0] == 0x33 || r[0] == 0x35 || r[0] == 0x37) && n >= 6 && kb_shake_accel(w, w->game_btn, &ax, &ay, &az)) { r[3] = ax; r[4] = ay; r[5] = az; }
}
static void real_pump(wm_t *w) {
    uint8_t r[23]; int n;
    while ((n = remotes_read(w->dev, r, sizeof r)) > 0) {
        if (w->npend && is_data_report(r[0]) && is_data_report(w->pend[w->npend - 1][0])) w->npend--;   /* keep only the newest data report */
        if (w->npend == 64) { memmove(w->pend, w->pend + 1, sizeof w->pend[0] * 63); memmove(w->pend_len, w->pend_len + 1, sizeof w->pend_len[0] * 63); w->npend--; }
        memcpy(w->pend[w->npend], r, n); w->pend_len[w->npend++] = n;
        if (has_buttons(r, n)) w->real_btn = (r[1] & 0x1F) | ((uint32_t)(r[2] & 0x9F) << 8);
    }
    w->game_btn = remotes_game_buttons(w->idx, w->real_btn);    /* (+ the keyboard if it's this player's; our menus) */
    while (w->npend && w->inflight <= 2) {
        merge_buttons(w, w->pend[0], w->pend_len[0]);
        hid_send(w, w->pend[0], w->pend_len[0]);
        memmove(w->pend, w->pend + 1, sizeof w->pend[0] * (w->npend - 1)); memmove(w->pend_len, w->pend_len + 1, sizeof w->pend_len[0] * (w->npend - 1)); w->npend--;
    }
}
static void real_attach(wm_t *w, int dev) {
    w->dev = dev; w->rd.active = 0; w->npend = 0; w->real_btn = 0;
    uint8_t r[23]; while (remotes_read(dev, r, sizeof r) > 0) {}      /* drop what arrived before */
    static const uint8_t order[] = {0x11, 0x13, 0x1A, 0x14, 0x19, 0x12};   /* LEDs, IR, speaker, then reporting mode */
    for (size_t i = 0; i < sizeof order; i++) if (w->saved_len[order[i]]) remotes_write(dev, w->saved_out[order[i]], w->saved_len[order[i]]);
    uint8_t st[2] = {0x15, 0}; remotes_write(dev, st, 2);           /* status report: tells the game about extensions/battery */
    rt_log("wm", "remote %d: a real Wii Remote", w->idx);
}

static void hid_output(wm_t *w, const uint8_t *d, int len) {     /* d[0] = report id */
    if (len < 2) return;
    uint8_t id = d[0];
    int ack = d[1] & 0x02;
    if (id == 0x11 || id == 0x12 || id == 0x13 || id == 0x14 || id == 0x19 || id == 0x1A) { memcpy(w->saved_out[id], d, len > 23 ? 23 : len); w->saved_len[id] = len > 23 ? 23 : len; }
    switch (id) {                                           /* our view of the state (keyboard / emulation) */
    case 0x11: w->leds = d[1] >> 4; break;
    case 0x12: {
        uint8_t m = len > 2 ? d[2] : 0x30, c = (d[1] & 0x04) != 0;
        if (m != w->report_mode || c != w->continuous) LOG("wm", "remote %d: reporting mode %02X%s", w->idx, m, c ? " (continuous)" : "");
        w->continuous = c; w->report_mode = m; break;
    }
    case 0x13: case 0x1A: w->ir_on = (d[1] & 0x04) != 0; break;
    case 0x14: w->speaker_on = (d[1] & 0x04) != 0; break;
    }
    if (w->dev >= 0) { remotes_write(w->dev, d, len); return; }
    LOG("wm", "remote %d: HID out %02X %02X len %d", w->idx, id, d[1], len);
    switch (id) {
    case 0x10: break;                                       /* rumble */
    case 0x11: if (ack) send_ack(w, id, 0); break;
    case 0x12:
        if (ack) send_ack(w, id, 0);
        send_data_report(w);
        break;
    case 0x13: case 0x1A: case 0x14: case 0x19: if (ack) send_ack(w, id, 0); break;
    case 0x15: send_status(w); break;
    case 0x16: {                                            /* write memory / registers */
        uint32_t addr = (d[2] << 16) | (d[3] << 8) | d[4]; int n = d[5];
        if (!(d[1] & 0x04) && addr + n <= sizeof eeprom && len >= 6 + n) memcpy(eeprom + addr, d + 6, n);
        send_ack(w, id, 0);
        break;
    }
    case 0x17: {                                            /* read memory / registers */
        w->rd.space = (d[1] & 0x04) ? 1 : 0;
        w->rd.addr = (d[2] << 16) | (d[3] << 8) | d[4];
        w->rd.left = (d[5] << 8) | d[6];
        w->rd.active = w->rd.left > 0;
        if (w->rd.space == 0) w->rd.addr &= 0xFFFF;
        break;
    }
    case 0x18: break;                                       /* speaker data */
    default: rt_log("wm", "unhandled HID output report %02X", id); break;
    }
}


/* ------------------------------------------------------------------ WUD, native
 * WUD's control block _wcb (0x803A3120): +0x6EC HID receive callback, +0x6F0 HID connection
 * callback (set by WPAD through fn_801F3B90 / fn_801F3BF0), +0xC.. its state machines (WUDIsBusy: +0xC == 0, +0xD == 0, +0xF == 4, +0x10 == 6 = idle),
 * +0x6E8 sync running, +0x708 library status (3 = started, 4 = shutting down, 0 = off). */
#define WCB          0x803A3120u
#define SDA          0x8042F680u
#define WCB_RECV     (WCB + 0x6EC)
#define WCB_CONN     (WCB + 0x6F0)
#define WUD_INITED   (SDA - 0x4b50)
#define RX_BUF       0x82030000u                 /* report buffers handed to WPAD: 4 remotes x 32 x 0x20 */
#define DEVADDR_BUF  0x82031000u                 /* _WUDGetDevAddr: 6 bytes per handle */
#define GKI_BUF      0x82032000u                 /* GKI_getbuf: 64 x 0x80 */
#define DEVINFO_BUF  0x82034000u                 /* the device records the HID connection callback gets: 0x80 per handle */
#define WM_CONN_FN   0x80001F60u                 /* guest addresses of the native event functions */
#define WM_RECV_FN   0x80001F70u
static int wud_connectable;

static void call_guest(ppc_context *ctx, uint32_t fn, uint32_t a0, uint32_t a1, uint32_t a2) {
    uint32_t lr = ctx->lr; ctx->r[3] = a0; ctx->r[4] = a1; ctx->r[5] = a2; ppc_call_indirect(ctx, g_base, fn); ctx->lr = lr;
}
/* the HID callbacks, "from an interrupt" (native events) */
/* WUD hands the connection callback its device record, not the handle: WPAD (fn_801E0820) reads
   the handle from +86 (_dev_handle_index[handle] = the channel it picks) and compares the name at
   +0 with "Nintendo RVL-CNT" / "Nintendo RVL-WBC". (Until 2026-10-23 the handle itself was passed:
   WPAD then read both remotes' handles from low memory - 0 - so a second remote took over the
   first one's channel and player 1's input went to channel 2.) */
static uint32_t dev_record(uint32_t h) {
    uint32_t d = DEVINFO_BUF + h * 0x80;
    for (uint32_t i = 0; i < 0x80; i++) W8(d + i, 0);
    static const char name[] = "Nintendo RVL-CNT-01";
    for (uint32_t i = 0; i < sizeof name; i++) W8(d + i, (uint8_t)name[i]);
    W8(d + 86, (uint8_t)h);
    return d;
}
static void ev_conn(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t cb = R32(WCB_CONN), h = ctx->r[3], open = ctx->r[4];
    if (cb && h < NWM) call_guest(ctx, cb, dev_record(h), open, 0);
}
static void ev_recv(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t buf = ctx->r[3], h = ctx->r[4] >> 16, len = ctx->r[4] & 0xFFFF;
    if (h < NWM && W[h].inflight > 0) W[h].inflight--;
    uint32_t cb = R32(WCB_RECV);
    if (cb && h < NWM && W[h].state == ST_CONNECTED) call_guest(ctx, cb, h, buf, len);
}
static void reg_events(void) {
    static int done; if (done) return; done = 1;
    rt_register_native(WM_CONN_FN, ev_conn); rt_register_native(WM_RECV_FN, ev_recv);
}
static void hid_send(wm_t *w, const uint8_t *d, int len) {   /* an input report (d[0] = report id) to WPAD */
    if (w->state != ST_CONNECTED || len <= 0 || len > 0x20) return;
    reg_events();
    uint32_t buf = RX_BUF + (uint32_t)w->idx * 0x400 + (w->rx_next++ & 31) * 0x20;
    for (int i = 0; i < len; i++) W8(buf + (uint32_t)i, d[i]);
    w->inflight++;
    rt_post_callback(WM_RECV_FN, buf, ((uint32_t)w->idx << 16) | (uint32_t)len);
}
static void link_up(wm_t *w) {
    reg_events();
    for (int k = 0; k < 6; k++) W8(DEVADDR_BUF + (uint32_t)w->idx * 8 + (uint32_t)k, w->addr[5 - k]);
    w->state = ST_CONNECTED; w->t_state = rt_emu_ns();
    w->report_mode = 0x30; w->continuous = 0; w->rd.active = 0; w->last_btn = 0xFFFFFFFF; w->inflight = 0;
    w->announced = 1; w->in_frame = g_frames_presented;
    rt_log("wm", "remote %d connected", w->idx);
    rt_post_callback(WM_CONN_FN, (uint32_t)w->idx, 1);
}
static void link_down(wm_t *w) {
    w->state = ST_IDLE; w->t_state = rt_emu_ns(); w->announced = 0; w->npend = 0;
    rt_post_callback(WM_CONN_FN, (uint32_t)w->idx, 0);
}

#define A(n) ctx->r[n]
/* WUDInit (fn_801F3190): the library is up at once - there is no Bluetooth stack to start */
void hle_fn_801F3190(ppc_context *ctx, uint8_t *base) {
    (void)base;
    if (R32(WUD_INITED)) { A(3) = 0; return; }
    W32(WCB_CONN, 0); W32(WCB_RECV, 0);
    W8(WCB + 0xC, 0); W8(WCB + 0xD, 0); W8(WCB + 0xE, 0); W8(WCB + 0xF, 4); W8(WCB + 0x10, 6);
    W8(WCB + 0x6E8, 0);
    W8(WCB + 0x708, 2);                                     /* (2: stack up - WPAD then installs its callbacks; 3 below) */
    call_guest(ctx, 0x801DB840u, 0, 0, 0);                  /* SCInit (WPAD reads the paired remotes from SYSCONF) */
    W32(WUD_INITED, 1);
    A(3) = 1;
}
/* WUDShutdown (fn_801F3310): off at once */
void hle_fn_801F3310(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; wud_connectable = 0; W8(WCB + 0x708, 0); W32(WUD_INITED, 0); }
void hle_WUDSetVisibility(ppc_context *ctx, uint8_t *base) { (void)base; wud_connectable = (A(4) & 0xFF) != 0; A(3) = 1; }
void hle_WUDSetSniffMode(ppc_context *ctx, uint8_t *base) { (void)base; A(3) = 1; }
void hle_WUDGetBufferStatus(ppc_context *ctx, uint8_t *base) { (void)base; A(3) = 10; }
void hle__WUDGetDevAddr(ppc_context *ctx, uint8_t *base) { (void)base; A(3) = (A(3) & 0xFF) < NWM ? DEVADDR_BUF + (A(3) & 0xFF) * 8 : 0; }
void hle_fn_801F61C0(ppc_context *ctx, uint8_t *base) { (void)base; A(3) = 0; }       /* _WUDGetQueuedSize */
void hle_fn_801F6220(ppc_context *ctx, uint8_t *base) { (void)base; A(3) = 0; }       /* _WUDGetNotAckedSize */
void hle__WUDGetLinkNumber(ppc_context *ctx, uint8_t *base) {
    (void)base; int n = 0; for (int i = 0; i < NWM; i++) n += W[i].state == ST_CONNECTED; A(3) = (uint32_t)n;
}
void hle_fn_801F3AA0(ppc_context *ctx, uint8_t *base) { (void)base; A(3) = 1; }       /* WUDSetDisableChannel (Wi-Fi channel hopping) */
void hle_fn_801F36F0(ppc_context *ctx, uint8_t *base) { (void)base; A(3) = 0; }       /* WUDStartSync...: pairing is the PC's (rt_plat_win.c) */
void hle_fn_801FD2A4(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }      /* (a Bluetooth stack message) */
void hle_BTA_HhGetAclQueueInfo(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }
/* GKI_getbuf (fn_801F6FB0): the buffer an output report is built in (used and dropped at once) */
void hle_fn_801F6FB0(ppc_context *ctx, uint8_t *base) {
    (void)base;
    static uint32_t next;
    uint32_t b = GKI_BUF + (next++ & 63) * 0x80;
    memset(G(b), 0, 0x80);
    A(3) = (A(3) & 0xFFFF) <= 0x80 ? b : 0;
}
/* BTA_HhSendData(handle, BT_HDR *): an output report to the remote (+2 length, +4 offset, data at +8+offset) */
static void hid_output(wm_t *w, const uint8_t *d, int len);
void hle_BTA_HhSendData(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t h = A(3) & 0xFF, p = A(4);
    if (!p || h >= NWM || W[h].state != ST_CONNECTED) return;
    int len = R16(p + 2); uint32_t d = p + 8 + R16(p + 4);
    uint8_t r[64]; if (len > 64) len = 64;
    for (int i = 0; i < len; i++) r[i] = R8(d + (uint32_t)i);
    hid_output(&W[h], r, len);
}
/* btm_remove_acl(BD_ADDR): WPAD disconnects a remote */
void hle_btm_remove_acl(ppc_context *ctx, uint8_t *base) {
    (void)base;
    for (int i = 0; i < NWM; i++) {
        int ok = 1; for (int k = 0; k < 6; k++) if (R8(A(3) + (uint32_t)k) != W[i].addr[5 - k]) ok = 0;
        if (ok && W[i].state == ST_CONNECTED) { rt_log("wm", "remote %d: the game disconnected it", i); link_down(&W[i]); }
    }
    A(3) = 0;
}
#undef A

/* ------------------------------------------------------------------ connecting */
static void init_all(void) {
    static int done; if (done) return; done = 1;
    eeprom_init();
    for (int i = 0; i < NWM; i++) {
        wm_t *w = &W[i]; memset(w, 0, sizeof *w);
        w->idx = i; w->dev = -1; w->report_mode = 0x30;
        static const uint8_t a[6] = {0x11, 0x02, 0x19, 0x79, 0x00, 0x00};
        memcpy(w->addr, a, 6); w->addr[5] = (uint8_t)i;
        w->t_state = rt_emu_ns(); w->last_btn = 0xFFFFFFFF;
    }
}
/* status for the menus: 0 no remote yet, 1 emulated (keyboard), 2 a real remote */
int wm_status(void) { return W[0].state != ST_CONNECTED ? 0 : W[0].dev >= 0 ? 2 : 1; }
/* is the game's remote `i` (WPAD channel) connected? */
int wiimote_connected(int i) { return i >= 0 && i < NWM && W[i].state == ST_CONNECTED; }

static int wud_ready(void) { return R32(WUD_INITED) && R8(WCB + 0x708) == 3 && R32(WCB_CONN) && R32(WCB_RECV); }
static void update_one(wm_t *w, uint64_t now) {
    int dev = remotes_slot_dev(w->idx);                     /* the real remote in this slot (-1 none) */
    int wanted = w->idx == 0 || dev >= 0 || remotes_slot_emulated(w->idx);   /* (remote 1 always: the title needs a player 1) */
    switch (w->state) {
    case ST_IDLE: {
        /* one at a time, lowest slot first, each after the one before is in the game (the
           module registers a player a few frames after its remote connects): the game then
           numbers its players in slot order when several are there at once */
        int busy = 0;
        for (int i = 0; i < w->idx; i++) {
            int want_i = i == 0 || remotes_slot_dev(i) >= 0 || remotes_slot_emulated(i);
            if (!want_i) continue;
            if (W[i].state == ST_CONNECTED && g_frames_presented - W[i].in_frame < 30) busy = 1;
            else if (W[i].state == ST_IDLE && now - W[i].t_state < 5000000000ull) busy = 1;   /* (waiting for it, up to 5 s) */
        }
        if (wanted && !busy && wud_connectable && wud_ready() && now - w->t_state > 1000000000ull) link_up(w);
        break;
    }
    case ST_CONNECTED: {
        if (!wanted) {                                      /* its real remote went away */
            rt_log("wm", "remote %d disconnects", w->idx);
            if (w->dev >= 0) w->dev = -1;
            link_down(w);
            break;
        }
        if (now - w->t_state < 20000000ull) break;          /* (WPAD sets up first) */
        if (dev != w->dev) {                                /* real remote attached / changed / gone */
            if (dev >= 0) real_attach(w, dev);
            else { w->dev = -1; rt_log("wm", "remote %d: real Wii Remote gone", w->idx); send_status(w); }
        }
        if (w->dev >= 0) { real_pump(w); break; }
        w->game_btn = remotes_game_buttons(w->idx, 0);           /* the keyboard, if it's this player's */
        if (w->inflight > 2) break;                         /* (WPAD hasn't taken the last ones yet) */
        if (w->rd.active) { read_step(w); break; }
        uint32_t btn = w->game_btn;
        int periodic = w->continuous || w->report_mode != 0x30;
        if (btn != w->last_btn || (periodic && now - w->t_last_report >= 10000000ull)) {
            w->t_last_report = now;
            send_data_report(w);
        }
        break;
    }
    }
}

void wiimote_update(void) {
    init_all();
    if (in_update) return;
    in_update++;
    remotes_update();                                       /* rt_remotes.c: real remotes come and go */
    uint64_t now = rt_emu_ns();
    if (R32(WUD_INITED) && R8(WCB + 0x708) == 2 && R32(WCB_CONN) && R32(WCB_RECV)) W8(WCB + 0x708, 3);   /* WUD "started" */
    {   static uint64_t lt; if (getenv("RT_WUD_DEBUG") && now - lt > 1000000000ull) { lt = now;
            rt_log("wud", "inited %u status %u connectable %d conncb %08X recvcb %08X", R32(WUD_INITED), R8(WCB + 0x708), wud_connectable, R32(WCB_CONN), R32(WCB_RECV)); } }
    for (int i = 0; i < NWM; i++) update_one(&W[i], now);
    in_update--;
}

/* ------------------------------------------------------------------ WPAD's init (fn_801DF7F0, WPADiInitSub)
 * Decompiled: the same as the SDK's, except the first step - switching the sensor bar on through
 * the Hollywood GPIO - which has no meaning on a PC (the sensor bar is the player's own). */
static void gcall8(ppc_context *ctx, uint32_t fn, const uint32_t *a, int n) {
    uint32_t lr = ctx->lr;
    for (int i = 0; i < n; i++) ctx->r[3 + i] = a[i];
    ppc_call_indirect(ctx, g_base, fn); ctx->lr = lr;
}
static uint32_t g1(ppc_context *ctx, uint32_t fn, uint32_t a0) { uint32_t a[1] = {a0}; gcall8(ctx, fn, a, 1); return ctx->r[3]; }
static void wpad_init_sub(ppc_context *ctx) {
    const uint32_t B = 0x8039E300u;                          /* the WPAD library's data block */
    for (int i = 0; i < 16; i++) W8(B + 0x1040 + (uint32_t)i, 0xFF);   /* _dev_handle_index[16] = -1 */
    for (uint32_t i = 0; i < 4; i++) {
        uint32_t wpd = B + 0x1060 + i * 0x9C0;
        W32(B + 0x30 + 4 * i, wpd);                          /* _wpdcb[i] = &_wpd[i] */
        W8(SDA - 0x4bd0 + i, 0);                             /* _chan_active_state[i] */
        W32(wpd + 0x8a4, 0);                                 /* connectCallback */
        g1(ctx, 0x801DF570u, i);                             /* __ClearControlBlock */
        g1(ctx, 0x801B4B20u, wpd + 0x8e4);                   /* OSInitThreadQueue */
        W8(SDA - 0x4c08 + i, 0); W8(SDA - 0x4c04 + i, 0);
    }
    W8(SDA - 0x4bc2, 5);                                     /* _sleepTime */
    W32(SDA - 0x4bc0, g1(ctx, 0x801AB1D0u, 0));              /* OSGetAppGamename */
    W8(SDA - 0x4bbc, (uint8_t)g1(ctx, 0x801AB260u, 0));      /* OSGetAppType */
    uint32_t v = g1(ctx, 0x801DD530u, 0) & 0xFF;             /* SCGetBtDpdSensibility, 1..5 */
    W8(SDA - 0x4bc3, (uint8_t)(v < 1 ? 1 : v > 5 ? 5 : v));
    W8(SDA - 0x4bc4, (g1(ctx, 0x801DD610u, 0) & 0xFF) == 1);
    W32(SDA - 0x4bc8, (g1(ctx, 0x801DD5A0u, 0) & 0xFF) == 1);
    uint32_t r = g1(ctx, 0x801DD670u, 0), sv = (r & 0xFF) ? r : 0;
    if ((r & 0xFF) >= 0x7F) sv = 0x7F;
    W8(SDA - 0x4bc9, (uint8_t)sv);
    W16(SDA - 0x4c0e, 0); W8(SDA - 0x4c0c, 0); W16(SDA - 0x4c0a, 0); W8(SDA - 0x4bcb, 0); W8(SDA - 0x4bca, 1);
    W8(SDA - 0x4bcc, 0xFF); W32(SDA - 0x4bd8, 0);
    g1(ctx, 0x801AB1C0u, R32(SDA - 0x5e90));                 /* OSRegisterVersion */
    for (int k = 0; k < 4; k++) { uint32_t f = R32(SDA - 0x4bf8 + 4 * (uint32_t)k); if (f) g1(ctx, f, 0); }
    g1(ctx, 0x801AB2E0u, B);                                 /* OSCreateAlarm(&_managerAlarm) */
    gcall8(ctx, 0x801B5F80u, NULL, 0);                       /* OSGetTime */
    uint32_t th = ctx->r[3], tl = ctx->r[4];
    uint32_t ms = (uint32_t)(((uint64_t)0x10624DD3u * (R32(0x800000F8) >> 2)) >> 32) >> 6;
    uint32_t a[7] = {B, 0, th, tl, 0, ms, 0x801DF550u};     /* (64-bit arguments in r5:r6, r7:r8) */
    gcall8(ctx, 0x801AB5B0u, a, 7);                          /* OSSetPeriodicAlarm(.., 1 ms, WPADiManageHandler0) */
}
void orig_fn_801DF7F0(ppc_context *ctx, uint8_t *base);
void hle_fn_801DF7F0(ppc_context *ctx, uint8_t *base) {
    if (getenv("RT_WPADINIT_VERIFY")) {                      /* testing: native vs the SDK's code, memory compared */
        size_t n = 0x01800000; uint8_t *a = malloc(n), *b = malloc(n); ppc_context c0 = *ctx;
        memcpy(a, base, n); wpad_init_sub(ctx); memcpy(b, base, n);
        memcpy(base, a, n); *ctx = c0; orig_fn_801DF7F0(ctx, base);
        int d = 0; for (size_t i = 0; i < n; i++) if (b[i] != base[i] && d++ < 30) rt_log("wm", "WPAD init verify: %08X native %02X sdk %02X", (uint32_t)(0x80000000u + i), b[i], base[i]);
        rt_log("wm", "WPAD init verify: %d bytes differ", d); free(a); free(b); return;
    }
    wpad_init_sub(ctx);
}
