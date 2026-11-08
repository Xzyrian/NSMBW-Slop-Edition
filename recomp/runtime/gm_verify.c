/* gm_verify.c - track B testing: a decompiled function against its PowerPC version (gm.h).
 *
 * RT_GM_VERIFY=1 (or a comma-separated list of function names): on every call of a function
 * registered with GM_HLE_VERIFIED, the PowerPC version (orig_<name>) runs first on the same
 * registers, with interrupts held off (its polls still count); then the memory it may change is put
 * back and the decompiled version runs for real. Compared: r3 (the return value, GMV_RET), the memory
 * [lo, lo + len), and the number of polls (loop back-edges). A difference is logged ("gm" log) with
 * the arguments; RT_GM_VERIFY_FATAL=1 stops there. The run then goes on with the decompiled
 * version's result, so a replay with verification is a replay of the decompiled game.
 * GMV_IGNORE_POLLS is for a declared function whose nested calls mutate objects outside its saved
 * ranges: the second invocation can take a different loop path. Memory and register checks remain.
 *
 * RT_GM_VERIFY=orig: the PowerPC versions run instead of the decompiled ones (nothing compared) -
 * the "before" of a deterministic A/B run with one binary (docs/DECOMP.md).
 * RT_GM_VERIFY=orig:name,...: only the listed functions use their PowerPC versions. This isolates
 * world-changing functions for A/B without double-invoking them or changing any other native.
 *
 * RT_GM_VERIFY_REGS=1 (with RT_GM_VERIFY): also every register the two versions leave - r0-r31, the
 * FPRs and paired singles, CR, LR, CTR, XER - for the residue the game can see later (volatile
 * registers spilled by a variadic callee, a CR word saved by mfcr).
 *
 * RT_GM_SELFTEST=1 (or a list of class tags, "mj2d,..."): a class's file calls each of its
 * decompiled functions with random arguments and random object contents against the PowerPC
 * version (gm_selftest_call), once, the first time the game uses the class; the object is put back
 * afterwards. For the functions a test run doesn't reach. Not for deterministic runs. */
#include "gm.h"
#include <signal.h>

static int verify_mode = -1;                 /* -1 unknown, 0 off, 1 all, 2 listed, 3 all orig, 4 listed orig */
static char verify_list[16384];
static int verify_fatal, verify_regs;

int gm_verifying(void) {
    if (verify_mode < 0) {
        const char *e = getenv("RT_GM_VERIFY");
        verify_mode = !e || !*e || !strcmp(e, "0") ? 0 : !strcmp(e, "1") ? 1 : !strcmp(e, "orig") ? 3 : !strncmp(e, "orig:", 5) ? 4 : 2;
        if (verify_mode == 2 || verify_mode == 4) snprintf(verify_list, sizeof verify_list, ",%s,", e + (verify_mode == 4 ? 5 : 0));
        verify_fatal = getenv("RT_GM_VERIFY_FATAL") != NULL;
        verify_regs = getenv("RT_GM_VERIFY_REGS") != NULL;
        if (verify_mode == 3) rt_log("gm", "running the PowerPC versions of the decompiled functions");
        else if (verify_mode == 4) rt_log("gm", "running the listed PowerPC versions only (%s)", e + 5);
        else if (verify_mode) rt_log("gm", "verifying decompiled functions against their PowerPC versions (%s)", e);
    }
    return verify_mode != 0;
}

typedef struct { const char *name; uint64_t calls, bad; } vstat_t;
static vstat_t stats[512]; static int nstats;
static vstat_t *stat_of(const char *name) {
    for (int i = 0; i < nstats; i++) if (stats[i].name == name) return &stats[i];
    if (nstats == 512) return &stats[511];
    stats[nstats].name = name; return &stats[nstats++];
}
static void report(void);
static void on_signal(int sig) { report(); signal(sig, SIG_DFL); raise(sig); }   /* (a timeout's SIGTERM still reports) */
static void report(void) {
    for (int i = 0; i < nstats; i++)
        rt_log("gm", "verified %-40s %8llu calls, %llu different", stats[i].name, (unsigned long long)stats[i].calls, (unsigned long long)stats[i].bad);
}

void gm_verify(const char *name, ppc_context *ctx, uint8_t *base, gm_native_fn native, gm_native_fn orig,
               const gptr *ranges, int nranges, int flags) {
    if (verify_mode == 3) { orig(ctx, base); return; }
    if (verify_mode == 2 || verify_mode == 4) {
        char k[96]; snprintf(k, sizeof k, ",%s,", name);
        int listed = strstr(verify_list, k) != NULL;
        if (verify_mode == 4 || !listed) { (verify_mode == 4 && listed ? orig : native)(ctx, base); return; }
    }
    static int registered; if (!registered) { registered = 1; atexit(report); signal(SIGTERM, on_signal); signal(SIGINT, on_signal); }
    vstat_t *st = stat_of(name); st->calls++;
    enum { BUF = 1 << 17 };
    static uint8_t bufs[4][2][BUF]; static int depth;        /* (a self-test may run inside a verified call) */
    if (depth == 4) { native(ctx, base); return; }
    uint8_t *before = bufs[depth][0], *after = bufs[depth][1]; depth++;
    /* the ranges [lo, lo + len) the call may change, one after another in the buffers */
    gptr lo[16]; uint32_t len[16], total = 0; int n = 0;
    for (int i = 0; i < nranges && n < 16; i++) {
        uint32_t l = ranges[2 * i + 1]; if (l > BUF - total) l = BUF - total;
        if (!l) continue;
        lo[n] = ranges[2 * i]; len[n] = l; memcpy(before + total, G(lo[n]), l); total += l; n++;
    }
    uint32_t polls0 = ppc_poll_counter;
    /* the PowerPC version, on a copy of the registers, interrupts held off */
    ppc_context c = *ctx; c.msr &= ~0x8000u;
    orig(&c, base);
    uint32_t polls_orig = ppc_poll_counter - polls0;
    /* (all of the result first, then put the memory back: the ranges may overlap) */
    for (int i = 0, o = 0; i < n; o += len[i], i++) memcpy(after + o, G(lo[i]), len[i]);
    for (int i = 0, o = 0; i < n; o += len[i], i++) memcpy(G(lo[i]), before + o, len[i]);
    ppc_poll_counter = polls0;
    /* the decompiled version, for real */
    uint32_t a[8]; for (int i = 0; i < 8; i++) a[i] = ctx->r[3 + i];
    extern uint32_t ppc_poll_foreign; uint32_t foreign0 = ppc_poll_foreign;
    native(ctx, base);
    depth--;
    uint32_t polls_native = ppc_poll_counter - polls0 - (ppc_poll_foreign - foreign0);   /* (not an interrupt's or another thread's) */
    int bad = 0; char why[256] = "";
    if ((flags & GMV_RET) && ctx->r[3] != c.r[3]) { bad = 1; snprintf(why, sizeof why, "r3 %08X (PowerPC %08X)", ctx->r[3], c.r[3]); }
    else if (!(flags & GMV_IGNORE_POLLS) && polls_native != polls_orig) { bad = 1; snprintf(why, sizeof why, "%u polls (PowerPC %u)", polls_native, polls_orig); }
    else for (int i = 0, o = 0; i < n && !bad; o += len[i], i++)
        if (memcmp(after + o, G(lo[i]), len[i])) {
            uint32_t j = 0; while (j < len[i] && after[o + j] == R8(lo[i] + j)) j++;
            bad = 1; snprintf(why, sizeof why, "memory at %08X (+0x%X): %02X (PowerPC %02X)", lo[i] + j, j, R8(lo[i] + j), after[o + j]);
        }
    if (!bad && verify_regs) {               /* RT_GM_VERIFY_REGS=1: every register the PowerPC version leaves */
        const char *w = 0; int k = 0;
        for (k = 0; k < 32 && !w; k++) if (ctx->r[k] != c.r[k]) w = "r";
        if (!w) for (k = 0; k < 32 && !w; k++) if (ctx->f[k].u != c.f[k].u) w = "f";
        if (!w) for (k = 0; k < 32 && !w; k++) if (memcmp(&ctx->ps1[k], &c.ps1[k], 8)) w = "ps1_";
        if (w) { k--; bad = 1; snprintf(why, sizeof why, "%s%d %016llX (PowerPC %016llX)", w, k,
                    *w == 'r' ? (unsigned long long)ctx->r[k] : *w == 'f' ? (unsigned long long)ctx->f[k].u : *(unsigned long long *)&ctx->ps1[k],
                    *w == 'r' ? (unsigned long long)c.r[k] : *w == 'f' ? (unsigned long long)c.f[k].u : *(unsigned long long *)&c.ps1[k]); }
        else if (ctx->cr != c.cr) { bad = 1; snprintf(why, sizeof why, "cr %08X (PowerPC %08X)", ctx->cr, c.cr); }
        else if (ctx->lr != c.lr || ctx->ctr != c.ctr) { bad = 1; snprintf(why, sizeof why, "lr/ctr %08X/%08X (PowerPC %08X/%08X)", ctx->lr, ctx->ctr, c.lr, c.ctr); }
        else if (ctx->xer_ca != c.xer_ca || ctx->xer_so != c.xer_so || ctx->xer_ov != c.xer_ov) { bad = 1; snprintf(why, sizeof why, "xer ca %u (PowerPC %u)", ctx->xer_ca, c.xer_ca); }
    }
    if (bad) {
        st->bad++;
        if (st->bad <= 10) rt_log("gm", "DIFFERENT %s(%08X, %08X, %08X, %08X, %08X): %s", name, a[0], a[1], a[2], a[3], a[4], why);
        if (verify_fatal) { report(); rt_fatal("gm: %s differs from its PowerPC version", name); }
    }
}

/* ---- self-test (RT_GM_SELFTEST) ---- */
int gm_selftest_wanted(const char *cls) {
    static int any = -1; static const char *e;
    if (any < 0) { e = getenv("RT_GM_SELFTEST"); any = e && *e && strcmp(e, "0"); }
    if (!any) return 0;
    char l[256], k[64]; snprintf(l, sizeof l, ",%s,", e); snprintf(k, sizeof k, ",%s,", cls);
    return !strcmp(e, "1") || strstr(l, k) != NULL;
}
uint32_t gm_rand(void) {                     /* xorshift32: the self-tests' arguments */
    static uint32_t x = 0x9E3779B9u;
    x ^= x << 13; x ^= x >> 17; x ^= x << 5; return x;
}
void gm_selftest_call(const char *name, ppc_context *ctx, uint8_t *base, gm_native_fn native, gm_native_fn orig,
                      const gptr *ranges, int nranges, int flags, int n, const uint32_t *args) {
    ppc_context c = *ctx; c.msr &= ~0x8000u;  /* (no interrupts: the game isn't running meanwhile) */
    for (int i = 0; i < n && i < 8; i++) c.r[3 + i] = args[i];
    int mode = verify_mode; verify_mode = 1;
    gm_verify(name, &c, base, native, orig, ranges, nranges, flags);
    verify_mode = mode;
}

/* the common argument kinds */
uint32_t gm_selftest_arg(char k) {
    uint32_t r = gm_rand();
    switch (k) {
    case 'p': return r % 8;                     /* a player */
    case 'w': return r % 10;                    /* a world */
    case 's': return r % 42;                    /* a stage */
    case 'e': return r % 4;                     /* an ambush enemy (world map) */
    case 'c': return r % 40;                    /* a bit number (past 31: none) */
    case 'f': return r % 48;                    /* a flag bit number */
    case 'm': return r % 70;                    /* a hint movie */
    case 'i': return r % 7;                     /* a stock item */
    case 'n': return (uint32_t)((int32_t)(r % 240) - 60);   /* a count, also negative / over 99 */
    case 'k': return r % 16;                    /* a small count */
    case 'b': return r & 1;
    case 'h': return r & 1 ? r & 0xFFFF : r;    /* 16 bits or more */
    case 'S': return r % 3;                     /* a save slot */
    default:  return r;                         /* 'v': any value */
    }
}
void gm_selftest(ppc_context *ctx, uint8_t *base, const gm_selftest_t *t) {
    static const char *done[64]; static int ndone;
    for (int i = 0; i < ndone; i++) if (!strcmp(done[i], t->tag)) return;
    if (ndone < 64) done[ndone++] = t->tag;
    if (!gm_selftest_wanted(t->tag)) return;
    uint32_t total = 0; for (int i = 0; i < t->nranges; i++) total += t->ranges[2 * i + 1];
    uint8_t *keep = malloc(total ? total : 1);
    for (int i = 0, o = 0; i < t->nranges; o += t->ranges[2 * i + 1], i++) memcpy(keep + o, G(t->ranges[2 * i]), t->ranges[2 * i + 1]);
    uint32_t polls = ppc_poll_counter;
    rt_log("gm", "self-test %s: %d functions x %d rounds", t->tag, t->ntests, t->rounds);
    for (int round = 0; round < t->rounds; round++)
        for (int k = 0; k < t->ntests; k++) {
            const gm_test_t *T = &t->tests[k];
            if (t->randomize) t->randomize(ctx, base, round);
            else for (int i = 0; i < t->nranges; i++)
                for (uint32_t a = 0; a + 4 <= t->ranges[2 * i + 1]; a += 4) W32(t->ranges[2 * i] + a, gm_rand() & gm_rand());
            uint32_t a[8] = { t->ranges[0] }; int n = 1;
            const char *c = T->args;
            if (*c == '!') { n = 0; c++; }      /* ("!...": no object - the first letter is r3: static functions) */
            for (; *c && n < 8; c++) {
                uint32_t v = t->arg ? t->arg(*c) : 0xDEADBEEFu;
                a[n++] = v != 0xDEADBEEFu ? v : gm_selftest_arg(*c);
            }
            gm_selftest_call(T->name, ctx, base, T->native, T->orig, t->ranges, t->nranges, T->flags, n, a);
        }
    for (int i = 0, o = 0; i < t->nranges; o += t->ranges[2 * i + 1], i++) memcpy(G(t->ranges[2 * i]), keep + o, t->ranges[2 * i + 1]);
    free(keep); ppc_poll_counter = polls;
    rt_log("gm", "self-test %s done (the totals are in the report at exit)", t->tag);
}
