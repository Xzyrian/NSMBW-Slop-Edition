/* gm_d_rail.c - dRail_c, an actor moving along a course rail (platforms, lifts, enemies on
 * paths): finding the rail, set, the next point (loop / bounce / end), the target and its angle,
 * the speed (acceleration towards the node's speed, the direction re-aimed every 8 frames),
 * execute and the arrival test. Track B (gm.h, docs/DECOMP.md), instance 1.
 *
 * Decompiled against NSMBW-Decomp (source/dol/bases/d_rail.cpp) and checked against the recompiled
 * USA rev 2 code (0x800D90C0-0x800D9714). Register-exact (RT_GM_VERIFY_REGS=1) for the
 * verified entries: the s16 node coordinates go to float through the stack (0x43300000:value
 * ^ 0x80000000 at f+8 / f+16), the angle to nw4r's CosFIdx / SinFIdx as an s16 stack word read
 * back with psq_l (GQR 3), the counted rail search leaves CTR as bdnz does. set() and execute()
 * call calcSpeed through the vtable (+12), as the game does (subclasses may replace it).
 *
 * dRail_c: +0 vtable, +4 the nodes (16 bytes: x, y s16, speed, accel f32, delay u16 +12, flags
 * u16 +14), +8 target x / y, +16 the position, +20 the speed vector, +24 the speed (float), +28
 * node count, +30 current node, +32 next node (s16), +34 delay timer, +36 angle (s16), +38 rail
 * flags, +40 node flags (u16), +42 reverse (u8), +44 angle timer (s32), +48 bounce (u8).
 * A rail (8 bytes): +0 ID, +2 first node, +4 node count, +6 flags. */
#include "gm.h"
#include "gm_nv.h"

#define F_ATAN2S   0x801611C0u           /* cM::atan2s */
#define F_COS_IDX  0x80237C40u           /* nw4r::math::CosFIdx */
#define F_SIN_IDX  0x80237BD0u           /* nw4r::math::SinFIdx */
#define SDA_STAGE  21688                 /* (r13 - 21688: dScStage_c::m_instance, +4622 the course file) */
#define SDA_CD     22504                 /* (r13 - 22504: dCd_c::m_instance, 944 bytes per course file) */
#define K_S2F      25688                 /* (r2 - 25688: (double) 2^52 + 2^31, s32 to float) */
#define K_ZERO     25696                 /* (r2 - 25696: 0.0f) */
#define K_IDX      25680                 /* (r2 - 25680: 1/256, the angle's nw4r index scale) */

#define RL_NODES   4
#define RL_TARGET  8
#define RL_POS     16
#define RL_SPEEDV  20
#define RL_SPEEDF  24
#define RL_COUNT   28
#define RL_CUR     30
#define RL_NEXT    32
#define RL_DELAY   34
#define RL_ANGLE   36
#define RL_FLAGS   38
#define RL_NFLAGS  40
#define RL_REVERSE 42
#define RL_ATIMER  44
#define RL_BOUNCE  48
enum { RAIL_LOOP = 2, RAIL_DELAYING = 4, RAIL_DISABLED = 8, NODE_STOP = 1 };

#define FR(n) (ctx->f[n].d)
#define LF(a) ldfs(base, (a))
#define SF(a, d) stfs(base, (a), (d))
static inline double fb(ppc_context *ctx, int n, double v) { ctx->f[n].d = ctx->ps1[n] = v; return v; }
#define FB(n, v) fb(ctx, (n), (v))
#define S16X(v) ((uint32_t)(int32_t)(int16_t)(v))
static inline int cmps(ppc_context *ctx, int32_t a, int32_t b) { cr_cmp_s(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int cmpu(ppc_context *ctx, uint32_t a, uint32_t b) { cr_cmp_u(ctx, 0, a, b); return (a > b) - (a < b); }
static inline int rec0(ppc_context *ctx, uint32_t v) { cr_cmp_s(ctx, 0, (int32_t)v, 0); return v != 0; }   /* a record form (andi.) */

/* the current course file (dCd_c::getFileP: null when it has no areas) into r4 */
static gptr cur_file(GM_CTX) {
    ctx->r[4] = gm_u32(ctx->r[13] - SDA_STAGE);
    ctx->r[5] = gm_u32(ctx->r[13] - SDA_CD);
    ctx->r[0] = gm_u8(ctx->r[4] + 4622) * 944u;
    ctx->r[4] = ctx->r[5] + ctx->r[0];
    ctx->r[0] = gm_u32(ctx->r[4] + 44);
    if (cmps(ctx, (int32_t)ctx->r[0], 0) == 0) ctx->r[4] = 0;
    return ctx->r[4];
}

/* getRailInfoP(id): the rail with that ID in the current course file */
static gptr rail_find(GM_CTX, uint32_t id) {
    gptr file = cur_file(GM_PASS);
    ctx->r[0] = gm_u32(file + 168);
    gptr p = ctx->r[4] = gm_ptr(file + 56);
    ctx->ctr = ctx->r[0];
    if (!(cmpu(ctx, ctx->r[0], 0) > 0)) return 0;
    for (;;) {
        ctx->r[0] = gm_u8(p);
        if (cmpu(ctx, ctx->r[0], id) == 0) return p;
        p = ctx->r[4] = p + 8;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    return 0;
}

/* calcNextPoint(): the next node (reverse: back), wrapping (loop), turning (bounce) or stopping
   at the end - true when the end is reached */
static uint32_t rail_next_point(GM_CTX, gptr r) {
    ctx->r[5] = gm_u8(r + RL_REVERSE);
    ctx->r[7] = 0;
    if (cmps(ctx, (int32_t)ctx->r[5], 0) != 0) {             /* backwards */
        ctx->r[4] = S16X(gm_u16(r + RL_NEXT));
        ctx->r[0] = ctx->r[4] - 1;
        gm_set_u16(r + RL_NEXT, (uint16_t)ctx->r[0]);
        ctx->r[0] = S16X(ctx->r[0]);
        if (cmps(ctx, (int32_t)ctx->r[0], 0) < 0) {
            ctx->r[0] = gm_u16(r + RL_FLAGS) & RAIL_LOOP;
            if (rec0(ctx, ctx->r[0])) { ctx->r[4] = gm_u16(r + RL_COUNT); ctx->r[0] = ctx->r[4] - 1; gm_set_u16(r + RL_NEXT, (uint16_t)ctx->r[0]); }
            else {
                ctx->r[0] = gm_u8(r + RL_BOUNCE);
                if (cmps(ctx, (int32_t)ctx->r[0], 0) != 0) { ctx->r[4] = ctx->r[5] ^ 1; ctx->r[0] = 1; gm_set_u8(r + RL_REVERSE, (uint8_t)ctx->r[4]); gm_set_u16(r + RL_NEXT, 1); }
                else { ctx->r[0] = 0; gm_set_u16(r + RL_NEXT, 0); ctx->r[7] = 1; }
            }
        }
    } else {                                                 /* forwards */
        ctx->r[4] = S16X(gm_u16(r + RL_NEXT));
        ctx->r[6] = gm_u16(r + RL_COUNT);
        ctx->r[0] = ctx->r[4] + 1;
        gm_set_u16(r + RL_NEXT, (uint16_t)ctx->r[0]);
        ctx->r[0] = S16X(ctx->r[0]);
        if (cmps(ctx, (int32_t)ctx->r[0], (int32_t)ctx->r[6]) >= 0) {
            ctx->r[0] = gm_u16(r + RL_FLAGS) & RAIL_LOOP;
            if (rec0(ctx, ctx->r[0])) { ctx->r[0] = 0; gm_set_u16(r + RL_NEXT, 0); }
            else {
                ctx->r[0] = gm_u8(r + RL_BOUNCE);
                if (cmps(ctx, (int32_t)ctx->r[0], 0) != 0) { ctx->r[4] = ctx->r[5] ^ 1; ctx->r[0] = ctx->r[6] - 2; gm_set_u8(r + RL_REVERSE, (uint8_t)ctx->r[4]); gm_set_u16(r + RL_NEXT, (uint16_t)ctx->r[0]); }
                else { ctx->r[0] = ctx->r[6] - 1; gm_set_u16(r + RL_NEXT, (uint16_t)ctx->r[0]); ctx->r[7] = 1; }
            }
        }
    }
    return ctx->r[7];
}

/* a node's s16 coordinate to float through the stack word at w (0x43300000 at w - 4), minus 2^52 + 2^31 */
static double s16_to_f(GM_CTX, gptr w, uint32_t v) {
    gm_set_u32(w, v ^ 0x80000000u);
    ctx->f[0].u = ld64(base, w - 4);
    return frsp(FR(0) - FR(1));
}

/* calcTargetPos(): the next node's position (y flipped) and the angle towards it */
static void rail_target(GM_CTX, gptr r) {
    GM_FN(0x800D9370); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    gptr f = gm_frame_sp;
    NV_R(31, r);
    ctx->r[6] = gm_ptr(r + RL_NODES);
    if (cmps(ctx, (int32_t)ctx->r[6], 0) != 0) {
        ctx->r[4] = S16X(gm_u16(r + RL_NEXT));
        ctx->r[0] = 0x43300000u;
        gm_set_u32(f + 8, ctx->r[0]);
        ctx->r[4] <<= 4;
        ctx->f[1].u = ld64(base, ctx->r[2] - K_S2F);
        ctx->r[5] = S16X(gm_u16(ctx->r[6] + ctx->r[4]));
        ctx->r[4] = ctx->r[6] + ctx->r[4];
        gm_set_u32(f + 16, ctx->r[0]);
        ctx->r[0] = ctx->r[5] ^ 0x80000000u;
        ctx->r[5] = gm_ptr(r + RL_POS);
        SF(r + RL_TARGET, FB(3, s16_to_f(GM_PASS, f + 12, ctx->r[0] ^ 0x80000000u)));
        ctx->r[0] = (uint32_t)-(int32_t)S16X(gm_u16(ctx->r[4] + 2)) ^ 0x80000000u;
        SF(r + RL_TARGET + 4, FB(2, s16_to_f(GM_PASS, f + 20, ctx->r[0] ^ 0x80000000u)));
        FB(1, LF(ctx->r[5] + 4)); FB(0, LF(ctx->r[5]));
        FB(1, frsp(FR(2) - FR(1)));
        FB(2, frsp(FR(3) - FR(0)));
        ctx->r[3] = r;
        uint32_t a = GM_CALLV(0x800D93F8u, F_ATAN2S, 0);
        ctx->r[0] = 8;
        gm_set_u16(r + RL_ANGLE, (uint16_t)a);
        gm_set_u32(r + RL_ATIMER, 8);
    }
    ctx->r[0] = lr;
}

/* the angle at +36 to nw4r's index (an s16 on the stack at w, psq_l GQR 3, times 1/256) */
static void angle_arg(GM_CTX, gptr r, gptr w) {
    ctx->r[0] = S16X(gm_u16(r + RL_ANGLE));
    gm_set_u16(w, (uint16_t)ctx->r[0]);
    psq_l(ctx, base, 1, w, 1, 3);
    FB(0, LF(ctx->r[2] - K_IDX));
    FB(1, frsp(FR(0) * FR(1)));
}
/* calcSpeed(): the speed towards the current node's (by its acceleration; 0: at once), the
   direction re-aimed every 8 frames, the speed vector from the angle */
static void rail_speed(GM_CTX, gptr r) {
    GM_FN(0x800D9420); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr;
    gptr f = gm_frame_sp;
    FB(0, LF(ctx->r[2] - K_ZERO));
    NV_R(31, r);
    ctx->r[0] = S16X(gm_u16(r + RL_CUR)) << 4;
    ctx->r[4] = gm_ptr(r + RL_NODES);
    ctx->r[5] = gm_ptr(r + RL_SPEEDF);
    ctx->r[4] += ctx->r[0];
    double accel = FB(2, LF(ctx->r[4] + 8)), speed = FB(1, LF(ctx->r[4] + 4));
    cr_fcmp(ctx, 0, FR(0), accel);
    int no_accel = FR(0) == accel;
    double v = FB(0, LF(ctx->r[5]));
    if (no_accel) { ctx->f[0].u = ctx->f[1].u; }
    else {
        cr_fcmp(ctx, 0, v, speed);
        if (v < speed) { v = FB(0, frsp(v + accel)); cr_fcmp(ctx, 0, v, speed); if (v > speed) ctx->f[0].u = ctx->f[1].u; }
        else if (v > speed) { v = FB(0, frsp(v - accel)); cr_fcmp(ctx, 0, v, speed); if (v < speed) ctx->f[0].u = ctx->f[1].u; }
    }
    SF(ctx->r[5], FR(0));
    ctx->r[4] = gm_u32(r + RL_ATIMER);
    if (cmps(ctx, (int32_t)ctx->r[4], 0) > 0) { ctx->r[0] = ctx->r[4] - 1; gm_set_u32(r + RL_ATIMER, ctx->r[0]); }
    else {
        ctx->r[0] = 8;
        gm_set_u32(r + RL_ATIMER, 8);
        ctx->r[4] = gm_ptr(r + RL_POS);
        FB(3, LF(r + RL_TARGET + 4)); FB(1, LF(ctx->r[4] + 4)); FB(2, LF(r + RL_TARGET)); FB(0, LF(ctx->r[4]));
        FB(1, frsp(FR(3) - FR(1)));
        FB(2, frsp(FR(2) - FR(0)));
        uint32_t a = GM_CALLV(0x800D94DCu, F_ATAN2S, 0);
        gm_set_u16(r + RL_ANGLE, (uint16_t)a);
    }
    ctx->r[3] = f + 10;
    angle_arg(GM_PASS, r, f + 10);
    GM_CALLV(0x800D94FCu, F_COS_IDX, 0);
    ctx->r[4] = gm_ptr(r + RL_SPEEDF); ctx->r[5] = f + 8; ctx->r[3] = gm_ptr(r + RL_SPEEDV);
    FB(0, LF(ctx->r[4]));
    SF(ctx->r[3], FB(0, frsp(FR(0) * FR(1))));
    angle_arg(GM_PASS, r, f + 8);
    GM_CALLV(0x800D952Cu, F_SIN_IDX, 0);
    ctx->r[4] = gm_ptr(r + RL_SPEEDF); ctx->r[3] = gm_ptr(r + RL_SPEEDV);
    FB(2, LF(ctx->r[4]));
    FB(0, LF(ctx->r[2] - K_ZERO));
    SF(ctx->r[3] + 4, FB(1, frsp(FR(2) * FR(1))));
    ctx->r[3] = gm_ptr(r + RL_SPEEDV);
    SF(ctx->r[3] + 8, FR(0));
    ctx->r[0] = lr;
}

/* checkArrive(): closer to the target than one step */
static uint32_t rail_arrived(GM_CTX, gptr r) {
    ctx->r[4] = gm_ptr(r + RL_POS);
    FB(3, LF(r + RL_TARGET)); FB(0, LF(ctx->r[4])); FB(2, LF(r + RL_TARGET + 4)); FB(1, LF(ctx->r[4] + 4));
    FB(3, frsp(FR(3) - FR(0)));
    ctx->r[5] = gm_ptr(r + RL_SPEEDF);
    FB(2, frsp(FR(2) - FR(1)));
    FB(0, LF(ctx->r[5]));
    FB(1, frsp(FR(3) * FR(3)));
    FB(3, frsp(FR(0) * FR(0)));
    FB(0, frsp(FR(2) * FR(2)));
    FB(0, frsp(FR(1) + FR(0)));
    cr_fcmp(ctx, 0, FR(0), FR(3));
    return ctx->cr >> 31;
}

/* the virtual calcSpeed (vtable +12) */
static void rail_vcalc(GM_CTX, gptr r, uint32_t ra) {
    ctx->r[12] = gm_u32(gm_u32(r) + 12);
    ctx->r[3] = r;
    ctx->ctr = ctx->r[12];
    GM_CALLV(ra, ctx->r[12], 1, r);
}

/* set(id, pos, speed, speedF, start node, reverse): onto the rail at that node */
static uint32_t rail_set(GM_CTX, gptr r, uint32_t id, gptr pos, gptr speedv, gptr speedf, uint32_t start, uint32_t rev) {
    GM_FN(0x800D9130); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr, res = 0;
    gptr f = gm_frame_sp;
    NV_R(26, r); NV_R(25, 0);
    gm_set_u16(r + RL_COUNT, 0);
    NV_R(27, pos); NV_R(28, speedv);
    gm_set_u32(r + RL_NODES, 0);
    NV_R(29, speedf); NV_R(30, start); NV_R(31, rev);
    ctx->r[3] = id;
    gptr info = NCALL(0x800D9170u, rail_find(GM_PASS, id));
    ctx->r[3] = info;
    if (cmps(ctx, (int32_t)info, 0) != 0) {
        gptr file = cur_file(GM_PASS);
        ctx->r[5] = gm_u16(info + 4);
        ctx->r[0] = gm_u16(info + 2);
        int ok = cmpu(ctx, ctx->r[5], ctx->r[30]) > 0;
        ctx->r[4] = gm_ptr(file + 60);
        ctx->r[0] <<= 4;
        ctx->r[6] = ctx->r[4] + ctx->r[0];                   /* the rail's first node */
        if (!ok) NV_R(30, 0);
        gm_set_u16(r + RL_COUNT, (uint16_t)ctx->r[5]);
        ctx->r[0] = 0x43300000u;
        ctx->r[4] = (ctx->r[30] << 4) & 0xFFFF0u;
        ctx->f[1].u = ld64(base, ctx->r[2] - K_S2F);
        gm_set_u32(r + RL_POS, pos);
        ctx->r[5] = ctx->r[6] + ctx->r[4];                   /* the start node */
        ctx->r[4] = S16X(gm_u16(ctx->r[6] + ctx->r[4]));
        gm_set_u32(f + 8, ctx->r[0]);
        ctx->r[4] ^= 0x80000000u;
        gm_set_u32(f + 16, ctx->r[0]);
        SF(pos, FB(0, s16_to_f(GM_PASS, f + 12, ctx->r[4] ^ 0x80000000u)));
        ctx->r[0] = (uint32_t)-(int32_t)S16X(gm_u16(ctx->r[5] + 2)) ^ 0x80000000u;
        ctx->r[4] = gm_u32(r + RL_POS);
        SF(ctx->r[4] + 4, FB(0, s16_to_f(GM_PASS, f + 20, ctx->r[0] ^ 0x80000000u)));
        gm_set_u32(r + RL_SPEEDV, speedv); gm_set_u32(r + RL_SPEEDF, speedf);
        gm_set_u32(r + RL_NODES, ctx->r[6]);
        gm_set_u16(r + RL_CUR, (uint16_t)ctx->r[30]); gm_set_u16(r + RL_NEXT, (uint16_t)ctx->r[30]);
        ctx->r[0] = gm_u16(ctx->r[6] + 12); gm_set_u16(r + RL_DELAY, (uint16_t)ctx->r[0]);   /* (the first node's delay) */
        gm_set_u8(r + RL_REVERSE, (uint8_t)rev);
        ctx->r[0] = gm_u16(info + 6);
        ctx->r[3] = r;
        gm_set_u16(r + RL_FLAGS, (uint16_t)ctx->r[0]);
        ctx->r[0] = gm_u16(ctx->r[5] + 14); gm_set_u16(r + RL_NFLAGS, (uint16_t)ctx->r[0]);
        NCALL(0x800D9258u, rail_next_point(GM_PASS, r));
        ctx->r[3] = r;
        NCALL(0x800D9260u, rail_target(GM_PASS, r));
        rail_vcalc(GM_PASS, r, 0x800D9274u);
        res = 1;
    }
    ctx->r[11] = f + 64;                                     /* (__restore_gpr's pointer) */
    ctx->r[0] = lr;
    return res;
}

/* execute(): one frame along the rail - true when a node was reached */
static uint32_t rail_execute(GM_CTX, gptr r) {
    GM_FN(0x800D9560); GM_NV_KEEP; GM_LR_KEEP;
    uint32_t lr = ctx->lr, res = 0;
    ctx->r[4] = 0;
    NV_R(31, r);
    ctx->r[0] = gm_u32(r + RL_NODES);
    gm_set_u16(r + RL_NFLAGS, 0);
    if (cmps(ctx, (int32_t)ctx->r[0], 0) == 0) goto out;
    ctx->r[5] = gm_u16(r + RL_FLAGS);
    ctx->r[0] = ctx->r[5] & RAIL_DISABLED;
    if (rec0(ctx, ctx->r[0])) goto out;
    ctx->r[4] = gm_u16(r + RL_DELAY);
    if (cmps(ctx, (int32_t)ctx->r[4], 0) != 0) { ctx->r[0] = ctx->r[4] - 1; gm_set_u16(r + RL_DELAY, (uint16_t)ctx->r[0]); goto out; }
    ctx->r[0] = ctx->r[5] & 0xFFFBu;
    rec0(ctx, ctx->r[0]);
    ctx->r[5] = gm_ptr(r + RL_SPEEDV);
    ctx->r[4] = gm_ptr(r + RL_POS);
    NV_R(30, 0);
    gm_set_u16(r + RL_FLAGS, (uint16_t)ctx->r[0]);
    for (int k = 0; k < 3; k++) {                            /* *pos += *speed */
        FB(1, LF(ctx->r[4] + 4 * k)); FB(0, LF(ctx->r[5] + 4 * k));
        SF(ctx->r[4] + 4 * k, FB(0, frsp(FR(1) + FR(0))));
    }
    ctx->r[3] = r;
    ctx->r[3] = NCALL(0x800D960Cu, rail_arrived(GM_PASS, r));
    if (cmps(ctx, (int32_t)ctx->r[3], 0) != 0) {
        ctx->r[4] = S16X(gm_u16(r + RL_NEXT));
        ctx->r[3] = gm_ptr(r + RL_NODES);
        ctx->r[0] = ctx->r[4] << 4;
        ctx->r[3] += ctx->r[0];
        ctx->r[0] = gm_u16(ctx->r[3] + 14);
        gm_set_u16(r + RL_NFLAGS, (uint16_t)ctx->r[0]);
        ctx->r[0] &= NODE_STOP;
        if (rec0(ctx, ctx->r[0])) { ctx->r[0] = gm_u16(r + RL_FLAGS) | 0xCu; gm_set_u16(r + RL_FLAGS, (uint16_t)ctx->r[0]); }
        else {
            gm_set_u16(r + RL_CUR, (uint16_t)ctx->r[4]);
            ctx->r[3] = r;
            ctx->r[3] = NCALL(0x800D9650u, rail_next_point(GM_PASS, r));
            if (cmps(ctx, (int32_t)ctx->r[3], 0) != 0) { ctx->r[0] = gm_u16(r + RL_FLAGS) | 0xCu; gm_set_u16(r + RL_FLAGS, (uint16_t)ctx->r[0]); }
            else {
                ctx->r[3] = r;
                NCALL(0x800D9670u, rail_target(GM_PASS, r));
                ctx->r[0] = S16X(gm_u16(r + RL_CUR));
                ctx->r[4] = gm_ptr(r + RL_NODES);
                ctx->r[3] = ctx->r[0] << 4;
                ctx->r[0] = gm_u16(r + RL_FLAGS);
                ctx->r[3] = ctx->r[4] + ctx->r[3];
                ctx->r[3] = gm_u16(ctx->r[3] + 12);
                ctx->r[0] |= RAIL_DELAYING;
                gm_set_u16(r + RL_DELAY, (uint16_t)ctx->r[3]);
                gm_set_u16(r + RL_FLAGS, (uint16_t)ctx->r[0]);
            }
        }
        NV_R(30, 1);
    }
    rail_vcalc(GM_PASS, r, 0x800D96ACu);
    res = ctx->r[30];
out:
    ctx->r[0] = lr;
    return res;
}

/* ================================================================== hle entry points
   On: getRailInfoP (reached; register-exact verify: 0 differences). Written but off (no rail
   rides in the test runs): set, calcNextPoint, calcTargetPos, calcSpeed, execute, checkArrive. */
#define A(i) GM_ARG(i)
#define RAIL_MEM A(0), 0x34
GM_HLE_INT(GetRail, 0, 0) { GM_RET(rail_find(GM_PASS, A(0))); }                                     /* dRail_c::getRailInfoP */
GM_HLE(fn_800D9130) { GM_RET(rail_set(GM_PASS, A(0), A(1), A(2), A(3), A(4), A(5), A(6))); }        /* ::set */
GM_HLE(fn_800D9290) { GM_RET(rail_next_point(GM_PASS, A(0))); }                       /* ::calcNextPoint */
GM_HLE(fn_800D9370) { rail_target(GM_PASS, A(0)); }                                  /* ::calcTargetPos */
GM_HLE(fn_800D9420) { rail_speed(GM_PASS, A(0)); }   /* ::calcSpeed */
GM_HLE(fn_800D9560) { GM_RET(rail_execute(GM_PASS, A(0))); }                                        /* ::execute */
GM_HLE(fn_800D96D0) { GM_RET(rail_arrived(GM_PASS, A(0))); }                              /* ::checkArrive */
