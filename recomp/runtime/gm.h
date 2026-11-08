/* gm.h - track B (docs/NATIVE_ROADMAP.md): the game's code decompiled to C, class by class.
 *
 * A decompiled function replaces a recompiled one through the hle_ mechanism: its recompiled
 * name goes into runtime/hle_funcs.txt (under a "# track B: ..." heading), the recompiler then
 * calls hle_<name>() and keeps the PowerPC translation as orig_<name>() for comparison.
 *
 * The objects stay in guest memory, in the Wii's big-endian layout, as long as any recompiled
 * function still touches them. Decompiled code works on them through the typed accessors below
 * (gm_u8(self + OFFSET) ...), with each class's field offsets named in its own file - checked
 * against the recompiled code that reads them. Native structs come per subsystem once nothing
 * recompiled is left touching it.
 *
 * Exactness (what the deterministic replay checks, docs/DECOMP.md):
 *  - the same memory writes, the same return value (bit for bit: sign/zero extension as the
 *    PowerPC code leaves it), the same guest calls in the same order;
 *  - the same number of loop back-edges: the recompiled code polls (PPC_POLL) on every loop
 *    back-edge and the deterministic clock counts those polls, so a decompiled loop calls
 *    GM_LOOP() as often as the PowerPC loop branches back (a for loop the compiler turned into a
 *    count-down loop branches back n - 1 times for n iterations).
 * Decompiled functions take the guest context as their first two parameters (ctx, base): they
 * need it for guest calls and polls. */
#pragma once
#include "rt.h"

typedef uint32_t gptr;                      /* a guest address: an object, an array, a string */

/* ---- typed guest memory (big-endian) ---- */
static inline uint8_t  gm_u8 (gptr a) { return R8(a); }
static inline int8_t   gm_s8 (gptr a) { return (int8_t)R8(a); }
static inline uint16_t gm_u16(gptr a) { return R16(a); }
static inline int16_t  gm_s16(gptr a) { return (int16_t)R16(a); }
static inline uint32_t gm_u32(gptr a) { return R32(a); }
static inline int32_t  gm_s32(gptr a) { return (int32_t)R32(a); }
static inline gptr     gm_ptr(gptr a) { return R32(a); }
static inline float    gm_f32(gptr a) { uint32_t u = R32(a); float f; memcpy(&f, &u, 4); return f; }
static inline void gm_set_u8 (gptr a, uint8_t v)  { W8(a, v); }
static inline void gm_set_u16(gptr a, uint16_t v) { W16(a, v); }
static inline void gm_set_u32(gptr a, uint32_t v) { W32(a, v); }
static inline void gm_set_ptr(gptr a, gptr v)     { W32(a, v); }
static inline void gm_set_f32(gptr a, float f)    { uint32_t u; memcpy(&u, &f, 4); W32(a, u); }

/* ---- the guest context, in a decompiled function ---- */
#define GM_CTX     ppc_context *ctx, uint8_t *base         /* (parameters) */
#define GM_PASS    ctx, base                               /* (arguments) */
#define GM_LOOP()  PPC_POLL()                              /* a loop back-edge, as the PowerPC code has it */
/* calling a guest function (not decompiled yet): its address and up to 8 integer arguments */
#define GM_CALL(fn, n, ...) rt_gcall(ctx, base, (fn), (n), ##__VA_ARGS__)
#define GM_VCALL(obj, off, n, ...) rt_gcall(ctx, base, R32(R32(obj) + (off)), (n), ##__VA_ARGS__)   /* a virtual call */

/* the function's own guest stack frame, as big as the PowerPC function's (0 for a leaf): put
   GM_FRAME(n) first in a decompiled function, it is popped on every return. Callees' frames then
   land where they would, and so do stack addresses the game keeps (and uninitialised stack words
   it copies). `gm_frame_sp` is the frame (for locals passed by address). */
typedef struct { ppc_context *c; uint32_t n; } gm_frame_t;
static inline void gm_frame_end_(gm_frame_t *f) { f->c->r[1] += f->n; }
static inline uint32_t gm_frame_begin_(ppc_context *ctx, uint32_t n) { uint32_t sp = ctx->r[1]; if (n) { W32(sp - n, sp); ctx->r[1] = sp - n; } return n; }
#define GM_FRAME(n) gm_frame_t gm_frame_ __attribute__((cleanup(gm_frame_end_))) = { ctx, gm_frame_begin_(ctx, (n)) }; \
                    gptr gm_frame_sp = ctx->r[1]; (void)gm_frame_sp

/* GM_FN(address): the same, but the frame of the PowerPC function at that address, with its
   prologue replayed (the saved LR - the return address, right for an hle entry - and the saved
   registers, as the recompiled code stores them: gm_prologue.c). Then the stack holds what the
   PowerPC code leaves there, which the game sometimes copies (uninitialised locals). */
uint32_t gm_prologue_(ppc_context *ctx, uint8_t *base, uint32_t addr);
/* (and which of f14-f31 that prologue saves with psq_st - paired singles, both halves - for
   GM_NV_KEEP: gm_nv.h. Outside a GM_FN, none: the file-level gm_psq_ below) */
extern uint32_t gm_psq_last_;
static const uint32_t gm_psq_ __attribute__((unused)) = 0;
#define GM_FN(a) gm_frame_t gm_frame_ __attribute__((cleanup(gm_frame_end_))) = { ctx, gm_prologue_(ctx, base, (a)) }; \
                 const uint32_t gm_psq_ = gm_psq_last_; (void)gm_psq_; \
                 gptr gm_frame_sp = ctx->r[1]; (void)gm_frame_sp

/* ---- hle entry points: the PowerPC calling convention (r3..r10 integers, f1.. floats) ---- */
#define GM_HLE(name) void hle_##name(ppc_context *ctx, uint8_t *base)
#define GM_ARG(i)    (ctx->r[3 + (i)])                     /* integer argument i (0 = r3) */
#define GM_RET(v)    (ctx->r[3] = (uint32_t)(v))
#define GM_FARG(i)   (ctx->f[1 + (i)].d)                   /* float argument i (0 = f1) */
#define GM_FRET(v)   (ctx->f[1].d = ctx->ps1[1] = (double)(float)(v))

/* ---- testing (gm_verify.c) ----
 * RT_GM_VERIFY=1: every decompiled function registered with gm_verify() also runs its PowerPC
 * version on the same input first (with polls turned off, on a copy of the memory it may touch),
 * and the two must agree on the return value, the memory and the number of polls. */
typedef void (*gm_native_fn)(ppc_context *ctx, uint8_t *base);
enum { GMV_RET = 1, GMV_IGNORE_POLLS = 2 }; /* r3 result; non-idempotent nested-call poll counts */
int  gm_verifying(void);
/* ranges: nranges pairs (address, length) of the memory the call may change */
void gm_verify(const char *name, ppc_context *ctx, uint8_t *base, gm_native_fn native, gm_native_fn orig,
               const gptr *ranges, int nranges, int flags);
/* the self-test (RT_GM_SELFTEST): one call of the decompiled function against the PowerPC version,
   with these arguments (r3 ...) */
int  gm_selftest_wanted(const char *cls);
uint32_t gm_rand(void);
void gm_selftest_call(const char *name, ppc_context *ctx, uint8_t *base, gm_native_fn native, gm_native_fn orig,
                      const gptr *ranges, int nranges, int flags, int n, const uint32_t *args);
/* a class's self-test: its entry points (args: one letter per argument after r3 = the object,
   gm_selftest_arg; a leading '!' for a static function: the letters start at r3), the guest memory they work on (randomised before each call unless the class
   randomises it itself, compared, and put back at the end), how many rounds */
typedef struct { const char *name; gm_native_fn native, orig; int flags; const char *args; } gm_test_t;
typedef struct {
    const char *tag;                            /* RT_GM_SELFTEST=<tag> */
    const gm_test_t *tests; int ntests, rounds;
    const gptr *ranges; int nranges;            /* pairs lo, len; ranges[0] is the object (r3) */
    void (*randomize)(ppc_context *ctx, uint8_t *base, int round);   /* (optional) */
    uint32_t (*arg)(char kind);                 /* (optional) the class's own letters; 0xDEADBEEF = not mine */
} gm_selftest_t;
void gm_selftest(ppc_context *ctx, uint8_t *base, const gm_selftest_t *t);   /* once per class */
uint32_t gm_selftest_arg(char kind);
#define GM_TEST(name, flags, args) { #name, name##_native, orig_##name, (flags), (args) }
/* an hle entry point with verification: the native body follows as name##_native(ctx, base). After
   the name: the memory it may change, as pairs lo, len ([lo, lo + len); expressions of the
   arguments, GM_ARG(i)) - up to 16 ranges. */
#define GM_HLE_VERIFIED_(name, flags, ...) \
    static void name##_native(ppc_context *ctx, uint8_t *base); \
    GM_HLE(name) { if (gm_verifying()) { const gptr r_[] = { __VA_ARGS__ }; \
                       gm_verify(#name, ctx, base, name##_native, orig_##name, r_, (int)(sizeof r_ / sizeof *r_) / 2, (flags)); } \
                   else name##_native(ctx, base); } \
    static void name##_native(ppc_context *ctx, uint8_t *base)
#define GM_HLE_VOID(name, ...) GM_HLE_VERIFIED_(name, 0, __VA_ARGS__)         /* returns nothing */
#define GM_HLE_INT(name, ...)  GM_HLE_VERIFIED_(name, GMV_RET, __VA_ARGS__)   /* returns r3 */
