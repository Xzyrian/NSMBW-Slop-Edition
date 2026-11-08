/* rt_os.c - the OS's hardware side, native (track A2 of docs/NATIVE_ROADMAP.md).
 *
 * With every device library native (GX, IOS/DVD, VI, SI, EXI, audio), nothing raises a hardware
 * interrupt any more: completions arrive as native events (rt_core.c rt_post_callback /
 * rt_post_interrupt) in an interrupt-like frame. So the OS's interrupt controller programming has
 * nothing to program, and its boot-time hardware pokes are dropped:
 *   SetInterruptMask             - programs the per-device mask registers: nothing to do
 *   __OSInterruptInit            - the handler table and masks (memory), no PI registers
 *   __OSInitMemoryProtection     - the MEM handlers (memory), no MI registers
 *   OSGetResetCode               - a cold boot unless the OS's reboot block says otherwise
 *   IPCReadReg / IPCWriteReg     - the IPC registers (the IOS client is native: rt_ios.c)
 * The rest of the OS (threads, alarms, the interrupt bookkeeping in 0x800000C4/C8) stays recompiled. */
#include "rt.h"

#define SDA 0x8042F680u
static uint32_t gcall(ppc_context *ctx, uint32_t fn, uint32_t a0, uint32_t a1) {
    uint32_t lr = ctx->lr; ctx->r[3] = a0; ctx->r[4] = a1; ppc_call_indirect(ctx, g_base, fn); ctx->lr = lr; return ctx->r[3];
}
#define F_memset                 0x800046B4u
#define F_OSSetInterruptHandler  0x801B11B0u
#define F_OSSetExceptionHandler  0x801AB020u
#define F_OSMaskInterrupts       0x801B1510u
#define F_OSUnmaskInterrupts     0x801B1590u
#define F_OSRegisterShutdown     0x801B32D0u
#define F_BATConfig              0x801B2BE0u
#define F_ExternalInterrupt      0x801B18C0u     /* (__OSDispatchInterrupt's exception entry) */
#define F_MEMIntrruptHandler     0x801B2620u

void hle_SetInterruptMask(ppc_context *ctx, uint8_t *base) { (void)base; ctx->r[3] = 0; }   /* (all of it "programmed") */

void hle___OSInterruptInit(ppc_context *ctx, uint8_t *base) {
    (void)base;
    W32(SDA - 0x4fa8, 0x80003040u);                                     /* InterruptHandlerTable */
    uint32_t lr = ctx->lr;
    ctx->r[3] = 0x80003040u; ctx->r[4] = 0; ctx->r[5] = 0x80; ppc_call_indirect(ctx, g_base, F_memset); ctx->lr = lr;
    W32(0x800000C4, 0xFFFFFFF0u);                                       /* (all masked, as __OSInterruptInit leaves it) */
    W32(0x800000C8, 0);
    gcall(ctx, F_OSSetExceptionHandler, 4, F_ExternalInterrupt);
}

void hle___OSInitMemoryProtection(ppc_context *ctx, uint8_t *base) {
    (void)base;
    if (R32(SDA - 0x4fa0)) return;
    gcall(ctx, F_OSMaskInterrupts, 0xF0000000u, 0);
    for (uint32_t i = 0; i < 5; i++) gcall(ctx, F_OSSetInterruptHandler, i, F_MEMIntrruptHandler);
    gcall(ctx, F_OSRegisterShutdown, 0x80333AE8u, 0);
    gcall(ctx, F_BATConfig, 0x000BA2CFu, 0);
    gcall(ctx, F_OSUnmaskInterrupts, 0x08000000u, 0);
    W32(SDA - 0x4fa0, 1);
}

void hle_OSGetResetCode(ppc_context *ctx, uint8_t *base) {
    (void)base;
    uint32_t blk = 0x8038E520u;                                          /* __OSRebootParams */
    ctx->r[3] = R32(blk) ? (R32(blk + 4) | 0x80000000u) : 0;             /* (else: the PI reset register - a cold boot) */
}

void hle_IPCReadReg(ppc_context *ctx, uint8_t *base)  { (void)base; ctx->r[3] = 0; }
void hle_IPCWriteReg(ppc_context *ctx, uint8_t *base) { (void)ctx; (void)base; }
