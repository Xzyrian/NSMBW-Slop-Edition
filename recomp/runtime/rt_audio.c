/* rt_audio.c - audio, native (track A5 of docs/NATIVE_ROADMAP.md): the AI (audio interface) and
 * DSP libraries without the audio hardware.
 *
 * On the Wii the AX mixer runs on the DSP: the CPU's AX library sends it a command list each
 * audio frame (3 ms) through the DSP mailbox, the DSP mixes into a buffer in main memory, and the
 * audio DMA plays that buffer, raising an interrupt per block - whose callback starts the next AX
 * frame. Here:
 *   - the mailbox functions (DSPSendMailToDSP / DSPCheckMailToDSP / DSPCheckMailFromDSP /
 *     DSPReadMailFromDSP) talk to a native model of the DSP: its ROM task loader and the AX
 *     microcode, whose command lists are mixed by rt_ax.c (Dolphin's DSP-HLE semantics);
 *   - the DSP's "mail for you" interrupt is a native event that runs the DSP task manager's
 *     handler (__DSPHandler, decompiled below);
 *   - the audio DMA is a native timer: every block (AIInitDMA's length at 32 kHz) the samples go to
 *     the PC's audio output and the AI DMA callback runs as a native event (like __AIDHandler);
 *   - AIInit / DSPInit / __OSInitAudioSystem keep only their memory side: no registers.
 * The rest of the DSP library (DSPAddTask, the task list, __DSP_boot_task / __DSP_exec_task, which
 * only send mail) and the whole AX library stay recompiled. */
#include "rt.h"
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */

#define SDA 0x8042F680u
#define S(o) (SDA + (uint32_t)(int32_t)(o))
static uint32_t gcall(ppc_context *ctx, uint32_t fn, uint32_t a0) {
    uint32_t lr = ctx->lr; ctx->r[3] = a0; ppc_call_indirect(ctx, g_base, fn); ctx->lr = lr; return ctx->r[3];
}

/* ------------------------------------------------------------------ the DSP (a model of it) */
static uint32_t mail_out[16]; static int nmail_out;
static int dsp_ucode;                           /* 0 = ROM loader, 1 = AX microcode */
static uint32_t rom_cmd; static int ax_state; static uint16_t ax_cmdlist_size;
static uint64_t dsp_irq_at;                     /* when the DSP's "mail for you" interrupt is due */
#define DSP_HANDLER_FN 0x80001F40u              /* guest address of dsp_handler (rt_register_native) */
static void dsp_handler(ppc_context *ctx, uint8_t *base);
static void dsp_irq_now(void) {
    static int reg; if (!reg) { reg = 1; rt_register_native(DSP_HANDLER_FN, dsp_handler); }
    rt_post_callback(DSP_HANDLER_FN, 0, 0);
}
static void dsp_mail(uint32_t m) { if (nmail_out < 16) mail_out[nmail_out++] = m; }
static void dsp_mail_irq(uint32_t m, uint64_t delay_ns) {
    dsp_mail(m);
    if (!delay_ns) dsp_irq_now(); else dsp_irq_at = rt_emu_ns() + delay_ns;
}
void ax_run_list(uint32_t list);
static void dsp_receive(uint32_t m) {
    if (dsp_ucode == 0) {                        /* the ROM: a task upload, then its start vector */
        if (!rom_cmd) { rom_cmd = m; return; }
        uint32_t cmd = rom_cmd; rom_cmd = 0;
        if (cmd == 0x80F3D001) {
            LOG("dsp", "task boot (init vector %04X) -> AX", m);
            dsp_ucode = 1; ax_state = 0;
            dsp_mail_irq(0xDCD10000, 0);         /* DSP_INIT */
        }
        return;
    }
    switch (ax_state) {
    case 0:                                       /* the command list's size */
        if ((m & 0xFFFF0000) == 0xBABE0000) { ax_cmdlist_size = (uint16_t)m; ax_state = 1; }
        else LOG("dsp", "AX: unexpected mail %08X", m);
        return;
    case 1: {                                     /* its address: mix this frame */
        extern uint64_t g_perf_ax_ns; uint64_t t = rt_now_ns();
        ax_run_list(m);
        g_perf_ax_ns += rt_now_ns() - t;
        ax_state = 2;
        dsp_mail_irq(0xDCD10002, 50000);          /* DSP_YIELD, a moment later (the DSP takes its time) */
        return;
    }
    case 2:                                       /* the task manager's answer to the yield */
        switch (m | 0xCDD10000) {
        case 0xCDD10000: dsp_mail_irq(0xDCD10001, 0); ax_state = 0; return;   /* resume */
        case 0xCDD10001: ax_state = 0; return;                                 /* another task */
        case 0xCDD10002: dsp_ucode = 0; return;                                /* back to the ROM */
        case 0xCDD10003: ax_state = 0; return;                                 /* continue */
        }
        ax_state = 0;
        return;
    }
}

/* the mailbox */
void hle_DSPSendMailToDSP(ppc_context *ctx, uint8_t *base)    { (void)base; LOG("dsp", "mail to DSP %08X", ctx->r[3]); dsp_receive(ctx->r[3]); }
void hle_fn_801D56E0(ppc_context *ctx, uint8_t *base)         { (void)base; ctx->r[3] = 0; }               /* DSPCheckMailToDSP: always taken */
void hle_fn_801D56F0(ppc_context *ctx, uint8_t *base)         { (void)base; ctx->r[3] = nmail_out > 0; }   /* DSPCheckMailFromDSP */
void hle_DSPReadMailFromDSP(ppc_context *ctx, uint8_t *base) {
    (void)base;
    if (!nmail_out) { ctx->r[3] = 0; return; }
    ctx->r[3] = mail_out[0];
    memmove(mail_out, mail_out + 1, sizeof mail_out[0] * (size_t)--nmail_out);
}

/* DSPInit: the task list, empty; the DSP greets */
#define T_CUR (-0x4c4c)
#define T_FIRST (-0x4c50)
#define T_LAST (-0x4c54)
#define T_TMP (-0x4c58)
#define T_RUDE (-0x4c5c)
#define T_RUDE_PENDING (-0x4c60)
void hle_DSPInit(ppc_context *ctx, uint8_t *base) {
    (void)base;
    if (R32(S(-0x4c68)) == 1) return;
    gcall(ctx, 0x801AB1C0u, R32(S(-0x6028)));           /* OSRegisterVersion */
    nmail_out = 0; dsp_ucode = 0; rom_cmd = 0;
    dsp_mail(0x8071FEED);                               /* (out of reset: the ROM says hello) */
    W32(S(T_TMP), 0); W32(S(T_CUR), 0); W32(S(T_LAST), 0); W32(S(T_FIRST), 0);
    W32(S(-0x4c68), 1);
}
/* DSPAssertTask (fn_801D5880): make a task run next */
void hle_fn_801D5880(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t task = ctx->r[3], cur = R32(S(T_CUR));
    if (cur == task) { W32(S(T_RUDE), task); W32(S(T_RUDE_PENDING), 1); ctx->r[3] = task; return; }
    if (R32(task + 4) < R32(cur + 4)) {
        W32(S(T_RUDE), task); W32(S(T_RUDE_PENDING), 1);
        /* (a running task would be interrupted here to yield: the AX model yields every frame anyway) */
        ctx->r[3] = task; return;
    }
    ctx->r[3] = 0;
}

/* __DSPHandler: what the DSP's mail means for the task list (decompiled; task: +0 state, +4
   priority, +8 flags, +0x28 init_cb, +0x2C res_cb, +0x30 done_cb, +0x34 req_cb, +0x38 next, +0x3C prev) */
#define F_EXEC_TASK   0x801D5DC0u
#define F_REMOVE_TASK 0x801D61A0u
static void send(uint32_t m) { dsp_receive(m); }
static void exec_task(ppc_context *ctx, uint32_t from, uint32_t to) {
    uint32_t lr = ctx->lr; ctx->r[3] = from; ctx->r[4] = to; ppc_call_indirect(ctx, g_base, F_EXEC_TASK); ctx->lr = lr;
}
static void cb(ppc_context *ctx, uint32_t task, int off) { uint32_t f = R32(task + (uint32_t)off); if (f) gcall(ctx, f, task); }
static void dsp_handler(ppc_context *ctx, uint8_t *base) {
    (void)base;
    if (!nmail_out) return;
    uint32_t mail = mail_out[0];
    memmove(mail_out, mail_out + 1, sizeof mail_out[0] * (size_t)--nmail_out);
    uint32_t task = R32(S(T_CUR));
    if (!task) return;
    if ((R32(task + 8) & 2) && mail == 0xDCD10002) mail = 0xDCD10003;
    int pending = R32(S(T_RUDE_PENDING)) != 0; uint32_t rude = R32(S(T_RUDE));
    switch (mail) {
    case 0xDCD10000: W32(task, 1); cb(ctx, R32(S(T_CUR)), 0x28); break;           /* INIT */
    case 0xDCD10001: W32(task, 1); cb(ctx, R32(S(T_CUR)), 0x2C); break;           /* RESUME */
    case 0xDCD10002:                                                               /* YIELD */
        if (pending) {
            if (task == rude) { send(0xCDD10003); W32(S(T_RUDE), 0); W32(S(T_RUDE_PENDING), 0); cb(ctx, R32(S(T_CUR)), 0x2C); }
            else { send(0xCDD10001); exec_task(ctx, R32(S(T_CUR)), R32(S(T_RUDE))); W32(R32(S(T_CUR)), 2);
                   W32(S(T_CUR), R32(S(T_RUDE))); W32(S(T_RUDE), 0); W32(S(T_RUDE_PENDING), 0); }
        } else if (!R32(task + 0x38)) {
            if (task == R32(S(T_FIRST))) { send(0xCDD10003); cb(ctx, R32(S(T_CUR)), 0x2C); }
            else { send(0xCDD10001); exec_task(ctx, R32(S(T_CUR)), R32(S(T_FIRST))); W32(R32(S(T_CUR)), 2); W32(S(T_CUR), R32(S(T_FIRST))); }
        } else {
            send(0xCDD10001); exec_task(ctx, R32(S(T_CUR)), R32(R32(S(T_CUR)) + 0x38)); W32(R32(S(T_CUR)), 2);
            W32(S(T_CUR), R32(R32(S(T_CUR)) + 0x38));
        }
        break;
    case 0xDCD10003:                                                               /* DONE */
        if (pending) {
            if (task != rude) {
                cb(ctx, task, 0x30);
                send(0xCDD10001); exec_task(ctx, 0, R32(S(T_RUDE)));
                gcall(ctx, F_REMOVE_TASK, R32(S(T_CUR)));
                W32(S(T_CUR), R32(S(T_RUDE))); W32(S(T_RUDE), 0); W32(S(T_RUDE_PENDING), 0);
                break;
            }
            W32(S(T_RUDE), 0); W32(S(T_RUDE_PENDING), 0);
        }
        if (!R32(task + 0x38)) {
            if (task == R32(S(T_FIRST))) {
                cb(ctx, task, 0x30); send(0xCDD10002); W32(R32(S(T_CUR)), 3); gcall(ctx, F_REMOVE_TASK, R32(S(T_CUR)));
            } else {
                cb(ctx, task, 0x30); send(0xCDD10001); W32(R32(S(T_CUR)), 3);
                exec_task(ctx, 0, R32(S(T_FIRST))); W32(S(T_CUR), R32(S(T_FIRST))); gcall(ctx, F_REMOVE_TASK, R32(S(T_LAST)));
            }
        } else {
            cb(ctx, task, 0x30); send(0xCDD10001); W32(R32(S(T_CUR)), 3);
            exec_task(ctx, 0, R32(R32(S(T_CUR)) + 0x38));
            uint32_t next = R32(R32(S(T_CUR)) + 0x38); W32(S(T_CUR), next);
            gcall(ctx, F_REMOVE_TASK, R32(next + 0x3C));
        }
        break;
    case 0xDCD10004: cb(ctx, task, 0x34); break;                                   /* REQUEST */
    }
}

/* the audio system's boot-time DSP check, the AI clock: hardware only */
void hle___OSInitAudioSystem(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }
void hle___OSStopAudioSystem(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }
void hle___AIClockInit(ppc_context *ctx, uint8_t *base)       { (void)ctx; (void)base; }

/* ------------------------------------------------------------------ the AI (audio DMA) */
static uint32_t ai_addr, ai_len, ai_on;
static uint64_t aidma_next_ns;
#define AI_CB      (-0x5190)
#define AI_STACK   (-0x5194)
#define AI_IN_CB   (-0x51c4)
#define AI_INIT    (-0x51c8)
#define AI_DMA_FN  0x80001F50u                    /* guest address of ai_dma_done (rt_register_native) */
void hle_AIInit(ppc_context *ctx, uint8_t *base) {
    (void)base;
    if (R32(S(AI_INIT)) == 1) return;
    uint32_t stack = ctx->r[3];
    gcall(ctx, 0x801AB1C0u, R32(S(-0x61e0)));             /* OSRegisterVersion */
    /* the sample-rate converter timings, in bus ticks (kept: nothing reads them here) */
    uint32_t t = (uint32_t)(((uint64_t)0x431BDE83u * (R32(0x800000F8) >> 2)) >> 32) >> 15;
#define US(k) (uint32_t)(((uint64_t)0x10624DD3u * (uint32_t)(t * (k))) >> 32) >> 9
    W32(S(-0x51a0), 0); W32(S(-0x51a8), 0); W32(S(-0x51b0), 0); W32(S(-0x51b8), 0); W32(S(-0x51c0), 0);
    W32(S(-0x519c), US(0x7B24u)); W32(S(-0x51a4), US(0xA428u)); W32(S(-0x51ac), US(0xA410u));
    W32(S(-0x51b4), US(0xF618u)); W32(S(-0x51bc), US(0x0BB8u));
#undef US
    W32(S(AI_CB), 0); W32(S(AI_STACK), stack);
    ai_on = 0; ai_addr = ai_len = 0; aidma_next_ns = 0;
    W32(S(AI_INIT), 1);
}
void hle_AIInitDMA(ppc_context *ctx, uint8_t *base) { (void)base; ai_addr = ctx->r[3] & 0x03FFFFE0u; ai_len = ctx->r[4] & ~31u; }
void hle_AIStartDMA(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; ai_on = 1; }
void hle___ARGetInterruptStatus(ppc_context *ctx, uint8_t *base) { (void)base; ctx->r[3] = 0; }   /* (really AIGetDMABytesLeft) */
void hle_fn_8019F1B0(ppc_context *ctx, uint8_t *base) { (void)base; ctx->r[3] = ai_addr; }        /* AIGetDMAStartAddr */
void hle_fn_8019F1D0(ppc_context *ctx, uint8_t *base) { (void)base; ctx->r[3] = ai_len; }         /* AIGetDMALength */
void hle_AIGetStreamPlayState(ppc_context *ctx, uint8_t *base) { (void)base; ctx->r[3] = 0; }     /* (GameCube disc streaming) */

/* __AIDHandler: a block has been played - the game's DMA callback queues the next */
static void ai_dma_done(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t f = R32(S(AI_CB));
    if (!f || R32(S(AI_IN_CB))) return;
    W32(S(AI_IN_CB), 1);
    if (R32(S(AI_STACK))) gcall(ctx, 0x8019F420u, f);     /* __AICallbackStackSwitch */
    else gcall(ctx, f, 0);
    W32(S(AI_IN_CB), 0);
}
/* every poll: due DSP interrupts and audio blocks */
void audio_tick(void) {
    if (dsp_irq_at && rt_emu_ns() >= dsp_irq_at) { dsp_irq_at = 0; dsp_irq_now(); }
    /* the DMA runs continuously while on: the callback re-arming it only queues the next block, so
       timing is anchored once when it starts (re-anchoring every block lost the callback's latency) */
    if (!ai_on || !ai_len) { aidma_next_ns = 0; return; }
    uint32_t bytes = ai_len;
    uint64_t period = (uint64_t)bytes * 1000000000ull / (32000 * 4);
    uint64_t now = rt_emu_ns();
    if (!aidma_next_ns) aidma_next_ns = now + period;
    if (now < aidma_next_ns) return;
    /* one block played: to the PC. Fallen behind: deliver the missed blocks back to back (each runs
       an AX frame) rather than dropping them; give up only past 100 ms of backlog. */
    aidma_next_ns += period;
    if (now > aidma_next_ns + 100000000ull) aidma_next_ns = now + period;
    static int16_t pcm[2 * 4096];
    uint32_t frames = bytes / 4; if (frames > 4096) frames = 4096;
    for (uint32_t i = 0; i < frames; i++) {                  /* (right, left) pairs in the buffer */
        pcm[2 * i + 1] = (int16_t)R16(0x80000000u | (ai_addr + 4 * i));
        pcm[2 * i] = (int16_t)R16(0x80000000u | (ai_addr + 4 * i + 2));
    }
    if (!g_resim) {                                          /* (fields run again after a rollback: not heard twice) */
        sfx_mix(pcm, (int)frames);                           /* (our own sounds: rt_sfx.c) */
        plat_audio_push(pcm, (int)frames);
    }
    {   static uint64_t st_t0, st_frames, st_resets; st_frames += frames;      /* delivery rate, logged every 10 s */
        if (now > aidma_next_ns + 90000000ull) st_resets++;
        if (!st_t0) st_t0 = now;
        else if (now - st_t0 >= 10000000000ull) {
            rt_log("audio", "%.0f samples/s delivered (32000 = real time), DMA block %u frames, backlog resets %llu",
                   st_frames * 1e9 / (double)(now - st_t0), frames, (unsigned long long)st_resets);
            st_t0 = now; st_frames = 0; st_resets = 0; } }
    static int reg; if (!reg) { reg = 1; rt_register_native(AI_DMA_FN, ai_dma_done); }
    rt_post_callback(AI_DMA_FN, 0, 0);
}
/* the next timed audio event (the idle loop sleeps until then) */
uint64_t audio_next_event_ns(uint64_t next) {
    if (aidma_next_ns && aidma_next_ns < next) next = aidma_next_ns;
    if (dsp_irq_at && dsp_irq_at < next) next = dsp_irq_at;
    return next;
}
