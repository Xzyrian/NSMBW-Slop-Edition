/* gm_py_demo.c - daPyDemoMng_c, the players' demo manager (track B, gm.h, docs/DECOMP.md), instance 2.
 *
 * The 8-player module's version (nsmbw-project v0.6.5, wiimj2d/d_static/d_a_player/
 * d_a_player_demo_manager.cpp): the order players enter a course in (course-in list), leave it in
 * (course-out list) and touch the goal pole in (goal list), the stage-start "toride" wait, the
 * players under demo control. The module made the lists 8 long by adding a second block for
 * players 5-8 further into the class (index + 14 / + 26 words below).
 *
 * Register-exact (gm_i2.h). All 27 methods are on. The goal methods were verified by the genuine
 * 1-1 clear; the control and toride methods by directed live-player tests (strict comparison for
 * read-only methods, isolated native/PowerPC A/B for world-changing methods). */
#include "gm_i2.h"
RT_STATE_FILE                                   /* (game code: its variables are part of a save state) */

/* ---- daPyDemoMng_c (the module's layout) */
#define DM_TORIDE_STATE     8            /* s32: the stage-start wait (0 none, 1 waiting, 2 done) */
#define DM_GOAL_NUM         28           /* s32: players at the goal pole so far */
#define DM_GOAL_LIST        32           /* s32 [4] the goal order, players 1-4; 5-8 at index + 26 */
#define DM_NOT_GOAL_TIMER   60           /* s32: frames left before the players who missed the pole stop */
#define DM_COURSE_IN        96           /* s32 [4] the course-in order; 5-8 at index + 14 */
#define DM_COURSE_OUT       112          /* s32 [4] the course-out order; 5-8 at index + 14 */
#define DM_TORIDE_PLAYER    140          /* s32: the player the toride wait follows, -1 */
#define DM_SPLIT(i, ext)    ((i) < 4 ? (i) : (i) + (ext))   /* (a list index -> its word) */

#define PY_ACT_INFO         0x8185E888u
#define PY_ENTRY            0x8185E890u
#define PY_TYPE             0x8185E93Cu
#define PY_CREATE_ITEM      0x8185E97Cu
#define PY_COURSE_IN_LIST   0x8185E8F4u  /* daPyMng_c::mCourseInList[8] */
#define STACK_GUARD         0x8185FED4u
#define PY_NUM_             0x80429CA0u  /* daPyMng_c::mNum */
#define SND_SCENE_MGR_I     0x8042A4A8u  /* SndSceneMgr::sInstance (r13 - 20952) */
#define PLAYER_KEY_FLAGS    0x80429CF8u  /* (r13 - 22920: a byte of key flags the not-goal stop clears) */
#define FLAG_DEMO_LAND_STOP 95
#define VT_EXECUTE_NOT_GOAL 300          /* (virtual: a player that missed the pole stops) */
#define VT_YOSHI_PLR_NO     108

/* ================================================================== lists */
/* init: the game's init, then the module's list blocks emptied */
static void dm_init(GM_CTX, gptr self) {
    I2_FN(0x81803CFCu);
    NV_R(30, self);
    BL(0x81803D14u, ext_fn_8005B4A0_81845400);                          /* (the game's daPyDemoMng_c::init) */
    R(3) = (uint32_t)-1;
    static const uint32_t ext[8] = { 152, 184, 156, 188, 160, 192, 164, 196 };   /* (course-in / -out 5-8, as stored) */
    for (int i = 0; i < 8; i++) gm_set_u32(self + ext[i], R(3));
}
/* setGoalDemoList(player): the player is next at the pole; returns the place, -1 when full */
static void dm_setGoalDemoList(GM_CTX, gptr self, uint32_t plr) {
    R(5) = self; R(3) = 8; ctx->ctr = 8;
    for (uint32_t i = 0;; i++) {
        R(3) = i;
        R(6) = self + 4 * (CMPU(i, 4) < 0 ? i : i + 26);
        R(7) = gm_u32(R(6) + DM_GOAL_LIST);
        if (CMPS(R(7), -1) == 0) { gm_set_u32(R(6) + DM_GOAL_LIST, plr); return; }
        R(3) = i + 1;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    R(3) = (uint32_t)-1;
}
/* getPoleBelowPlayer(player): the player who reached the pole just before this one, -1 */
static void dm_getPoleBelowPlayer(GM_CTX, gptr self, uint32_t plr) {
    R(6) = gm_u32(self + DM_GOAL_NUM); R(5) = (uint32_t)-1;
    if (CMPS(R(6), 0) > 0) {
        R(7) = self + DM_GOAL_LIST; ctx->ctr = R(6);
        for (uint32_t i = 0;; i++) {
            R(6) = i;
            int lt4 = CMPU(i, 4) < 0;
            R(8) = lt4 ? i : i + 26;
            if (CMPU(i, 0) != 0) {
                R(8) = gm_u32(R(7) + (R(8) << 2));
                if (CMPU(R(8), plr) == 0) {
                    R(4) = CMPU(i, 5) < 0 ? i - 1 : i + 25;
                    R(4) <<= 2; R(3) = self + R(4); R(5) = gm_u32(R(3) + DM_GOAL_LIST);
                    break;
                }
            }
            R(6) = i + 1;
            if (--ctx->ctr == 0) break;
            GM_LOOP();
        }
    }
    R(3) = R(5);
}
/* setCourseOutList(player): the player is next to leave the course */
static void dm_setCourseOutList(GM_CTX, gptr self, uint32_t plr) {
    ctx->ctr = 8;
    for (uint32_t i = 0;; ) {
        R(5) = i;
        R(6) = self + 4 * (CMPU(i, 4) < 0 ? i : i + 14);
        R(7) = gm_u32(R(6) + DM_COURSE_OUT);
        if (CMPS(R(7), -1) == 0) { gm_set_u32(R(6) + DM_COURSE_OUT, plr); return; }
        GM_LOOP();                                                       /* (the branch back polls first) */
        R(5) = ++i;
        if (--ctx->ctr == 0) return;
    }
}
/* turnNextDemoNo: the course-in list moves up one; the last place empties */
static void dm_turnNextDemoNo(GM_CTX, gptr self) {
    R(4) = self + DM_COURSE_IN; ctx->ctr = 7;
    for (uint32_t i = 0;; ) {
        R(6) = i + 1;
        int c = CMPU(i, 3);
        R(7) = c < 0 ? R(6) : i + 15;
        if (c >= 0) c = CMPU(i, 3);
        R(5) = c > 0 ? i + 14 : i;
        R(7) = gm_u32(R(4) + (R(7) << 2));
        R(5) <<= 2; gm_set_u32(R(4) + R(5), R(7));
        R(5) = R(6); i = R(6);
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    R(4) = (uint32_t)-1; gm_set_u32(self + 180, R(4));                  /* (the 8th place) */
}
/* clearDemoNo(player): the player leaves the course-in list; the rest close up */
static void dm_clearDemoNo(GM_CTX, gptr self, uint32_t plr) {
    R(6) = 8; R(5) = 0; R(3) = self + DM_COURSE_IN; ctx->ctr = 8;
    for (uint32_t i = 0;; ) {
        R(6) = i;
        R(7) = gm_u32(R(3) + 4 * (CMPU(i, 4) < 0 ? i : i + 14));
        if (CMPS(R(7), -1) != 0 && CMPU(R(7), plr) != 0) {
            R(8) = CMPS(R(5), 4) < 0 ? R(5) : R(5) + 14;
            R(5)++; R(8) <<= 2; gm_set_u32(R(3) + R(8), R(7));
        }
        R(6) = ++i;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    if (CMPS(R(5), 7) > 0) return;
    ctx->xer_ca = 8 >= R(5); R(4) = 8 - R(5); ctx->ctr = R(4); R(4) = (uint32_t)-1;
    for (;;) {
        R(6) = CMPS(R(5), 4) < 0 ? R(5) : R(5) + 14;
        R(6) <<= 2; R(5)++; gm_set_u32(R(3) + R(6), R(4));
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
}

/* ================================================================== the players in play, one by one
   Most functions walk the players in play (daPyMng_c::mActPlayerInfo, the low word) and look at
   each one's controlled actor (daPyMng_c::getCtrlPlayer); the loops keep their state in r26-r30. */
/* the player p's actor if p is in play, else 0 (r3 = the bit, then the actor; CR0 of the null
   check, signed for the game-compiled functions) */
static gptr dm_ctrl(GM_CTX, uint32_t p, uint32_t ra, int signed_cmp) {
    R(3) = gm_u32(PY_ACT_INFO + 4);
    R(3) = (p > 31 ? 0 : R(3) >> p) & 1; CR0(ctx, R(3));
    if (!R(3)) return 0;
    R(3) = p; BL(ra, getCtrlPlayer__9daPyMng_cFi_8005FB90);
    int none = signed_cmp ? CMPS(R(3), 0) == 0 : CMPU(R(3), 0) == 0;
    return none ? 0 : R(3);
}
#define TESTFLAG(ra, pl, f) (R(3) = (pl), R(4) = (f), BL((ra), testFlag__10daPlBase_cFi_80056CF0), CMPU(R(3), 0) != 0)
#define SETFLAG(ra, f)      (R(4) = (f), BL((ra), setFlag__10daPlBase_cFi_80056C70))
#define FLAG_GOAL_DEMO      101          /* daPlBase_c flags of the goal demo */
#define FLAG_ON_POLE        102
#define FLAG_POLE_DOWN      103
#define FLAG_JUMP_READY     104
#define FLAG_GOAL_JUMP      105
#define FLAG_LANDED         106
#define FLAG_KIME           107
#define FLAG_KIME_DONE      108
#define FLAG_RUN_CASTLE     109
#define FLAG_GOAL_IN        110
#define FLAG_CONTROL_DEMO   114

/* calcNotGoalPlayer: after the not-goal timer, the players who missed the pole stop (and Yoshis
   without a rider) - game-compiled code (r12 for the virtual calls, signed null checks) */
static void dm_calcNotGoalPlayer(GM_CTX, gptr self) {
    I2_FN(0x81803D4Cu);
    R(0) = gm_u32(self + DM_NOT_GOAL_TIMER);
    if (CMPS(R(0), 0) == 0) return;
    ctx->xer_ca = R(0) != 0; R(0) -= 1; CR0(ctx, R(0));
    gm_set_u32(self + DM_NOT_GOAL_TIMER, R(0));
    if (R(0) != 0) return;
    R(0) = gm_u8(PLAYER_KEY_FLAGS) & 0xF0; NV_R(31, 0);
    gm_set_u8(PLAYER_KEY_FLAGS, (uint8_t)R(0));
    for (uint32_t p = 0;; ) {
        R(3) = p; BL(0x81803D90u, getCtrlPlayer__9daPyMng_cFi_8005FB90);
        if (CMPS(R(3), 0) != 0) {
            R(12) = gm_u32(gm_u32(R(3) + 96) + VT_EXECUTE_NOT_GOAL); ctx->ctr = R(12);
            ctx->lr = 0x81803DA8u; ppc_call_indirect(ctx, base, ctx->ctr);
        }
        NV_R(31, ++p);
        if (CMPS(p, 8) >= 0) break;
        GM_LOOP();
    }
    NV_R(30, 0);
    for (uint32_t p = 0;; ) {                                            /* Yoshis left alone */
        R(3) = p; BL(0x81803DC0u, fn_8005FB70);                         /* daPyMng_c::getYoshi */
        int none = CMPS(R(3), 0) == 0;
        NV_R(31, R(3));
        if (!none) {
            R(12) = gm_u32(gm_u32(R(3) + 96) + VT_YOSHI_PLR_NO); ctx->ctr = R(12);
            ctx->lr = 0x81803DDCu; ppc_call_indirect(ctx, base, ctx->ctr);
            R(0) = (uint32_t)(int32_t)(int8_t)gm_u8(R(3));
            if (CMPS(R(0), -1) == 0) {
                R(12) = gm_u32(R(31) + 96); R(3) = R(31);
                R(12) = gm_u32(R(12) + VT_EXECUTE_NOT_GOAL); ctx->ctr = R(12);
                ctx->lr = 0x81803E00u; ppc_call_indirect(ctx, base, ctx->ctr);
            }
        }
        NV_R(30, ++p);
        if (CMPS(p, 8) >= 0) break;
        GM_LOOP();
    }
}

/* executeGoalDemo_Pole: collect the players on the pole, insertion-sort them by height, then
   fill the goal list and set each player's landing height. The module's eight-entry lists use
   their second four-word block for players 5-8. */
static void dm_executeGoalDemo_Pole(GM_CTX, gptr self) {
    I2_FN(0x81803EF4u);
    gptr sp = gm_frame_sp;
    NV_R(26, self);

    /* First pass: player number by the pole slot stored in the actor. */
    R(0) = 8; ctx->ctr = R(0); R(5) = (uint32_t)-1; R(9) = sp;
    for (int i = 0;; ) {
        gm_set_u32(R(9) + 48, R(5)); R(9) += 4;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    NV_R(24, sp + 48); NV_R(30, 0); NV_R(25, 1);
    for (uint32_t p = 0;; ) {
        R(3) = 0x81860000u; R(3) = gm_u32(R(3) - 6004);                 /* daPyMng_c::mActPlayerInfo */
        R(0) = (p & 63) > 31 ? 0 : R(25) << (p & 63);
        R(0) = R(3) & R(0); CR0(ctx, R(0));
        if (R(0)) {
            R(3) = p; BL(0x81803F60u, getCtrlPlayer__9daPyMng_cFi_8005FB90);
            int none = CMPS(R(3), 0) == 0; NV_R(23, R(3));
            if (!none) {
                R(0) = gm_u32(self + 16) & 4; CR0(ctx, R(0));
                if (!R(0)) {
                    R(3) = R(23);
                    if (TESTFLAG(0x81803F80u, R(3), FLAG_GOAL_DEMO) &&
                        !TESTFLAG(0x81803F94u, R(23), FLAG_ON_POLE)) return;
                } else if (!TESTFLAG(0x81803FA8u, R(23), FLAG_ON_POLE)) return;
                if (TESTFLAG(0x81803FBCu, R(23), FLAG_ON_POLE)) {
                    R(0) = gm_u32(R(23) + 1072) << 2;
                    gm_set_u32(R(24) + R(0), p);
                }
            }
        }
        NV_R(30, ++p);
        if (CMPS(p, 8) >= 0) break;
        GM_LOOP();
    }

    /* Insertion sort: ascending actor Y, with -1 empty slots kept at the end. */
    R(0) = 8; ctx->ctr = R(0); R(5) = (uint32_t)-1; R(9) = sp;
    for (int i = 0;; ) {
        gm_set_u32(R(9) + 16, R(5)); R(9) += 4;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    NV_R(30, sp + 48); NV_R(25, sp + 16); NV_R(28, 0); NV_R(31, 0x80000000u);
    for (uint32_t n = 0;; ) {
        NV_R(29, gm_u32(R(30)));
        int empty = CMPS(R(29), -1) == 0;
        if (!empty) {
            R(3) = R(29); BL(0x8180401Cu, getCtrlPlayer__9daPyMng_cFi_8005FB90);
            int none = CMPS(R(3), 0) == 0; NV_R(24, R(3));
            if (!none) {
                R(0) = gm_u32(sp + 16);
                if (CMPS(R(0), -1) == 0) gm_set_u32(sp + 16, R(29));
                else {
                    NV_R(23, sp + 16); NV_R(27, 0);
                    for (uint32_t i = 0;; ) {
                        R(3) = gm_u32(R(23));
                        if (CMPS(R(3), -1) == 0) {
                            R(0) = i << 2; gm_set_u32(R(25) + R(0), R(29));
                            break;
                        }
                        BL(0x81804060u, getCtrlPlayer__9daPyMng_cFi_8005FB90);
                        ctx->f[1].d = ctx->ps1[1] = ldfs(base, R(24) + 176);
                        ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(3) + 176);
                        cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
                        CR_SETBIT(ctx, 2, CR_BIT(ctx, 0) | CR_BIT(ctx, 2));   /* current Y <= sorted Y */
                        if (CR_BIT(ctx, 2)) {
                            cr_cmp_s(ctx, 1, (int32_t)i, 7); R(3) = 7;
                            if (CR_BIT(ctx, 4)) {
                                R(8) = 7 - i; ctx->xer_ca = 7 >= i; R(4) = i + 8;
                                int many = CMPS(R(8), 8) > 0;
                                R(5) = 0; R(6) = 0; R(7) = 0;
                                if (many) {                                    /* (the game's unrolled large shift) */
                                    for (uint32_t j = 7; j > i + 7; j -= 8) {
                                        gptr dst = sp + 16 + 4 * j;
                                        for (int k = 0; k < 8; k++) {
                                            R(0) = gm_u32(dst - 4 * (k + 1));
                                            R(3)--;
                                            gm_set_u32(dst - 4 * k, R(0));
                                        }
                                        GM_LOOP();
                                    }
                                }
                                R(4) = R(3) << 2; R(5) = sp + 16 + R(4);
                                R(0) = R(3) - i; ctx->ctr = R(0);
                                if (CMPS(R(3), i) > 0) {
                                    for (;;) {
                                        R(0) = gm_u32(R(5) - 4); R(3)--;
                                        gm_set_u32(R(5), R(0)); R(5) -= 4;
                                        if (--ctx->ctr == 0) break;
                                        GM_LOOP();
                                    }
                                }
                            }
                            R(0) = i << 2; gm_set_u32(R(25) + R(0), R(29));
                            break;
                        }
                        NV_R(27, ++i); R(23) += 4;
                        if (CMPS(i, 8) >= 0) break;
                        GM_LOOP();
                    }
                }
            }
        }
        NV_R(28, ++n); R(30) += 4;
        if (CMPS(n, 8) >= 0) break;
        GM_LOOP();
    }

    /* The first (lowest) player finds the pole's ground height. */
    R(3) = gm_u32(sp + 16); R(0) = 0; gm_set_u32(self + 44, 0);
    ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(13) - 15464);
    int no_players = CMPS(R(3), -1) == 0;
    stfs(base, sp + 8, ctx->f[0].d);
    if (!no_players) {
        BL(0x818041E0u, getCtrlPlayer__9daPyMng_cFi_8005FB90);
        int none = CMPS(R(3), 0) == 0; NV_R(23, R(3));
        if (!none) {
            BL(0x818041F0u, fn_800510F0);
            R(5) = gm_u8(R(23) + 911); R(3) = R(23) + 172; R(4) = sp + 8;
            R(6) = 1; R(7) = (uint32_t)-1;
            BL(0x81804208u, checkGround__5dBc_cFPC7mVec3_cPfUcUcSc_800757B0);
            R(0) = gm_u8(R(23) + 908);
            if (CMPU(R(0), 2) == 0) {
                ctx->f[1].d = ctx->ps1[1] = ldfs(base, sp + 8);
                ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(13) - 15460);
                ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
                stfs(base, sp + 8, ctx->f[0].d);
            } else {
                R(0) = gm_u32(R(23) + 4240);
                if (CMPS(R(0), 3) != 0 && CMPS(R(0), 0) != 0) {
                    ctx->f[1].d = ctx->ps1[1] = ldfs(base, sp + 8);
                    ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(13) - 15456);
                    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d - ctx->f[0].d);
                    stfs(base, sp + 8, ctx->f[0].d);
                }
            }
        }
        NV_FL(30, ldfs(base, R(13) - 15452));
        NV_R(25, self);
        NV_FL(31, ldfs(base, R(13) - 15448));
        NV_R(24, sp + 16); NV_R(23, 0);
        for (uint32_t p = 0;; ) {
            R(3) = p; BL(0x81804268u, mfn_81803E24);
            R(3) <<= 2; NV_R(25, self + R(3)); R(3) = gm_u32(R(24));
            gm_set_u32(R(25) + DM_GOAL_LIST, R(3));
            if (CMPS(R(3), -1) != 0) {
                R(4) = gm_u32(self + DM_GOAL_NUM); R(0) = R(4) + 1;
                gm_set_u32(self + DM_GOAL_NUM, R(0));
                BL(0x81804290u, getCtrlPlayer__9daPyMng_cFi_8005FB90);
                if (CMPS(R(3), 0) != 0) {
                    ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(3) + 176);
                    ctx->f[1].d = ctx->ps1[1] = ldfs(base, sp + 8);
                    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d + ctx->f[0].d);
                    cr_fcmp(ctx, 0, ctx->f[1].d, ctx->f[0].d);
                    if (CR_BIT(ctx, 1)) {
                        ctx->f[1].u = ctx->f[0].u;
                        stfs(base, sp + 8, ctx->f[0].d);
                    }
                    ctx->f[0].d = frsp(ctx->f[1].d);
                    stfs(base, R(3) + 1080, ctx->f[0].d);
                    ctx->f[1].d = ctx->ps1[1] = ldfs(base, R(3) + 4144);
                    ctx->f[0].d = ctx->ps1[0] = ldfs(base, sp + 8);
                    ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[1].d);
                    ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[0].d + ctx->f[1].d);
                    stfs(base, sp + 8, ctx->f[0].d);
                }
            }
            NV_R(23, ++p); R(25) += 4;
            int done = CMPS(p, 8) >= 0; R(24) += 4;
            if (done) break;
            GM_LOOP();
        }
    }
    BL(0x818042E8u, fn_80102220);
    R(3) = gm_u32(R(13) - 23020);
    BL(0x818042F0u, stopBgmGoalDemo__13daPyDemoMng_cFv_8005B810);
    R(3) = 1; R(4) = 10; R(0) = 0;
    gm_set_u32(self + 8, 1); R(3) = self;
    gm_set_u32(self + 12, 10); gm_set_u32(self + 24, 0);
    BL(0x81804310u, fn_8005B690);
    R(3) = self; BL(0x81804318u, fn_8005C830);
}

/* the goal list, one by one: each player at the pole gets a demo flag */
static void dm_goal_list_flag(GM_CTX, gptr list, uint32_t flag, uint32_t ra_get, uint32_t ra_set, int r_i, int r_list, int r_left) {
    NV_R(r_i, 0); NV_R(r_list, list); NV_R(r_left, 8);
    for (uint32_t i = 0;; ) {
        R(3) = CMPU(i, 4) < 0 ? i : i + 26;
        R(3) = gm_u32(list + (R(3) << 2));
        if (CMPS(R(3), -1) != 0) {
            BL(ra_get, getCtrlPlayer__9daPyMng_cFi_8005FB90);
            if (CMPU(R(3), 0) != 0) SETFLAG(ra_set, flag);
        }
        NV_R(r_left, R(r_left) - 1);
        int more = CMPU(R(r_left), 0) > 0;
        NV_R(r_i, ++i);
        if (!more) break;
        GM_LOOP();
    }
}
/* executeGoalDemo_PoleDown: everyone at the pole slides down */
static void dm_executeGoalDemo_PoleDown(GM_CTX, gptr self) {
    I2_FN(0x81804340u);
    R(4) = 2;
    NV_R(28, 0); NV_R(29, self + DM_GOAL_LIST); NV_R(30, 8);
    gm_set_u32(self + 8, 2);                                             /* (the goal demo's step) */
    dm_goal_list_flag(GM_PASS, self + DM_GOAL_LIST, FLAG_POLE_DOWN, 0x81804390u, 0x818043A0u, 28, 29, 30);
}
/* setGoalDemoKimeAll: everyone at the pole strikes the pose */
static void dm_setGoalDemoKimeAll(GM_CTX, gptr self) {
    I2_FN(0x81804718u);
    dm_goal_list_flag(GM_PASS, self + DM_GOAL_LIST, FLAG_KIME, 0x81804760u, 0x81804770u, 28, 29, 30);
}
/* setGoalDemoRunCastle: the demo mode 0, everyone at the pole runs to the castle */
static void dm_setGoalDemoRunCastle(GM_CTX, gptr self) {
    I2_FN(0x8180479Cu);
    R(4) = 0; R(5) = 0; NV_R(29, 0); NV_R(30, self);
    R(3) = self; BL(0x818047C8u, setDemoMode__13daPyDemoMng_cFQ213daPyDemoMng_c6Mode_ei_8005B5C0);
    NV_R(30, self + DM_GOAL_LIST); NV_R(28, 8);
    dm_goal_list_flag(GM_PASS, self + DM_GOAL_LIST, FLAG_RUN_CASTLE, 0x818047F4u, 0x81804804u, 29, 30, 28);
}

/* a loop over the players in play with the goal demo flag: stop at the first one whose flag
   `wait` isn't set (returns 0), else 1 - JumpCheck / Land / KimeWait */
static int dm_all_goal_flag(GM_CTX, uint32_t wait, const uint32_t ra[4], int stop_when_set) {
    NV_R(26, PY_ACT_INFO); NV_R(27, 8); NV_R(29, 0);
    for (uint32_t p = 0;; ) {
        gptr pl = dm_ctrl(GM_PASS, p, ra[0], 0);
        if (pl) {
            NV_R(28, pl);
            if (TESTFLAG(ra[1], pl, FLAG_GOAL_DEMO)) {
                int set = TESTFLAG(ra[2], R(28), wait);
                if (set == stop_when_set) return 0;
            }
        }
        NV_R(27, R(27) - 1);
        int more = CMPU(R(27), 0) > 0;
        NV_R(29, ++p);
        if (!more) break;
        GM_LOOP();
    }
    return 1;
}
/* executeGoalDemo_JumpCheck: when everyone at the pole is ready, the jumps start from the last one */
static void dm_executeGoalDemo_JumpCheck(GM_CTX, gptr self) {
    I2_FN(0x818043CCu);
    NV_R(30, self);
    R(3) = gm_u8(self + 19) & 2; CR0(ctx, R(3));                         /* (the pole's bottom reached) */
    if (!R(3)) return;
    static const uint32_t ra[4] = { 0x81804424u, 0x81804438u, 0x8180444Cu, 0 };
    if (!dm_all_goal_flag(GM_PASS, FLAG_JUMP_READY, ra, 0)) return;
    R(3) = gm_u32(self + DM_GOAL_NUM); R(4) = 0;
    gm_set_u32(self + 84, 0);
    R(4) = 3; R(3) -= 1;
    gm_set_u32(self + 24, R(3));                                         /* (the next to jump: the last at the pole) */
    R(3) = 10;
    gm_set_u32(self + 8, R(4)); gm_set_u32(self + 12, R(3));             /* (step 3, a 10-frame wait) */
}
/* executeGoalDemo_Land: when everyone has landed, step 5 */
static void dm_executeGoalDemo_Land(GM_CTX, gptr self) {
    I2_FN(0x81804588u);
    NV_R(30, self);
    static const uint32_t ra[4] = { 0x818045D4u, 0x818045E8u, 0x818045FCu, 0 };
    if (!dm_all_goal_flag(GM_PASS, FLAG_LANDED, ra, 0)) return;
    R(3) = gm_u32(self + 16); R(4) = 5;
    gm_set_u32(self + 8, 5);
    R(3) |= 8; gm_set_u32(self + 16, R(3));
}
/* executeGoalDemo_KimeWait: bit 0x10 of the flags while anyone still poses */
static void dm_executeGoalDemo_KimeWait(GM_CTX, gptr self) {
    I2_FN(0x8180464Cu);
    NV_R(30, self);
    static const uint32_t ra[4] = { 0x81804698u, 0x818046ACu, 0x818046C0u, 0 };
    int done = dm_all_goal_flag(GM_PASS, FLAG_KIME_DONE, ra, 1);
    if (done) R(3) = 0;
    else { R(3) = 16; GM_LOOP(); }                                       /* (the jump back to the store) */
    R(4) = gm_u32(self + 16) & ~0x10u;
    R(3) = R(4) | R(3); gm_set_u32(self + 16, R(3));
}
/* executeGoalDemo_Jump: the players jump off the pole one by one, every 10 frames */
static void dm_executeGoalDemo_Jump(GM_CTX, gptr self) {
    I2_FN(0x818044ACu);
    NV_R(31, self);
    R(0) = gm_u32(self + 24);
    int c = CMPS(R(0), 0);
    if (c < 0) { R(0) = 4; gm_set_u32(self + 8, 4); return; }            /* (all jumped: step 4) */
    if (c == 0) {
        R(0) = gm_u32(self + 84);
        if (CMPS(R(0), 0) == 0) {                                        /* (the last jump: the fanfare) */
            R(0) = gm_u8(self + 64);
            int fast = CMPS(R(0), 0) != 0;
            R(3) = gm_u32(SND_SCENE_MGR_I);
            if (fast) { R(4) = 1; BL(0x81804500u, fn_8019C1E0); } else { R(4) = 0; BL(0x81804510u, fn_8019C1E0); }
            R(3) = gm_u32(self + 84); R(0) = R(3) + 1; gm_set_u32(self + 84, R(0));
        }
    }
    R(0) = gm_u32(self + 12);
    if (CMPS(R(0), 0) != 0) return;
    R(3) = gm_u32(self + 24); BL(0x81804530u, mfn_81803E24);            /* (the goal list's word index) */
    R(0) = R(3) << 2; R(3) = self + R(0); R(3) = gm_u32(R(3) + DM_GOAL_LIST);
    BL(0x81804540u, getCtrlPlayer__9daPyMng_cFi_8005FB90);
    R(6) = gm_u32(self + 24);
    int none = CMPS(R(3), 0) == 0;
    R(4) = gm_u32(self + DM_GOAL_NUM); R(0) = R(6) - 1; R(5) = R(6) + 1;
    gm_set_u32(self + 24, R(0));
    R(0) = R(4) - R(5);
    if (none) return;
    gm_set_u32(R(3) + 1076, R(0));                                       /* (how many jump after it) */
    SETFLAG(0x8180456Cu, FLAG_GOAL_JUMP);
    R(0) = 10; gm_set_u32(self + 12, 10);
}

/* isAllPlayerGoalIn / isAllPlayerControlDemo / isLandAll: every player in play (with the goal
   demo flag, for the first) has the flag; r27 / r28 = "reached player 8" */
static uint32_t dm_all_flag(GM_CTX, uint32_t flag, int with_goal_demo, const uint32_t ra[3], int r_act, int r_res, int r_left, int r_p, int r_pl) {
    NV_R(r_act, PY_ACT_INFO); NV_R(r_res, 0); NV_R(r_left, 8); NV_R(r_p, 0);
    for (uint32_t p = 0;; ) {
        gptr pl = dm_ctrl(GM_PASS, p, ra[0], 0);
        int fail = 0;
        if (pl) {
            if (with_goal_demo) {
                NV_R(r_pl, pl);
                if (TESTFLAG(ra[1], pl, FLAG_GOAL_DEMO)) fail = !TESTFLAG(ra[2], R(r_pl), flag);
            } else if (flag) fail = !TESTFLAG(ra[1], pl, flag);
            else { BL(ra[1], fn_80052470); fail = CMPU(R(3), 0) == 0; }  /* (isLand: daPlBase_c::isDemoLand) */
        }
        if (fail) break;
        NV_R(r_res, CMPU(p, 6) > 0 ? 1 : 0);
        NV_R(r_left, R(r_left) - 1);
        int more = CMPU(R(r_left), 0) > 0;
        NV_R(r_p, ++p);
        if (!more) break;
        GM_LOOP();
    }
    R(3) = R(r_res) & 1;
    return R(3);
}
static void dm_isAllPlayerGoalIn(GM_CTX) {
    I2_FN(0x81804830u);
    static const uint32_t ra[3] = { 0x8180487Cu, 0x81804890u, 0x818048A4u };
    dm_all_flag(GM_PASS, FLAG_GOAL_IN, 1, ra, 26, 27, 28, 30, 29);
}
static void dm_isAllPlayerControlDemo(GM_CTX) {
    I2_FN(0x81804AFCu);
    static const uint32_t ra[3] = { 0x81804B44u, 0x81804B54u, 0 };
    dm_all_flag(GM_PASS, FLAG_CONTROL_DEMO, 0, ra, 27, 28, 29, 30, 0);
}
static void dm_isLandAll(GM_CTX) {
    I2_FN(0x81804E2Cu);
    static const uint32_t ra[3] = { 0x81804E74u, 0x81804E80u, 0 };
    dm_all_flag(GM_PASS, 0, 0, ra, 27, 28, 29, 30, 0);
}

/* calcGoalCenterPos: the mean position of the players in the goal demo (only x when mode != 1) */
#define VEC3_ZERO           0x80377DC8u  /* (mVec3_c::Zero) */
#define F_I2F_MAGIC         0x818486C0u  /* (the int -> float conversion constant) */
#define F_ONE               0x818487B0u  /* 1.0f */
static void dm_calcGoalCenterPos(GM_CTX, gptr self) {
    I2_FN(0x818048F4u);
    gptr sp = gm_frame_sp;
    NV_R(30, self);
    R(3) = VEC3_ZERO;
    ctx->f[31].d = ctx->ps1[31] = ldfs(base, R(3));
    ctx->f[29].d = ctx->ps1[29] = ldfs(base, R(3) + 4);
    ctx->f[30].d = ctx->ps1[30] = ldfs(base, R(3) + 8);
    NV_R(25, PY_ACT_INFO); NV_R(26, 8); NV_R(27, 0); NV_R(29, 0);
    for (uint32_t p = 0;; ) {
        gptr pl = dm_ctrl(GM_PASS, p, 0x81804964u, 0);
        if (pl) {
            NV_R(28, pl);
            if (TESTFLAG(0x81804978u, pl, FLAG_GOAL_DEMO)) {
                ctx->f[0].d = ctx->ps1[0] = ldfs(base, R(28) + 172);
                NV_R(27, R(27) + 1);
                ctx->f[1].d = ctx->ps1[1] = ldfs(base, R(28) + 176);
                ctx->f[2].d = ctx->ps1[2] = ldfs(base, R(28) + 180);
                ctx->f[31].d = ctx->ps1[31] = frsp(ctx->f[31].d + ctx->f[0].d);
                ctx->f[29].d = ctx->ps1[29] = frsp(ctx->f[29].d + ctx->f[1].d);
                ctx->f[30].d = ctx->ps1[30] = frsp(ctx->f[30].d + ctx->f[2].d);
            }
        }
        NV_R(26, R(26) - 1);
        int more = CMPU(R(26), 0) > 0;
        NV_R(29, ++p);
        if (!more) break;
        GM_LOOP();
    }
    if (CMPU(R(27), 0) == 0) return;
    R(4) = 0x43300000u; R(3) = gm_u32(self + 4);
    gm_set_u32(sp + 16, R(4)); R(4) = R(27) ^ 0x80000000u; gm_set_u32(sp + 20, R(4));
    R(4) = 0x81850000u;
    ctx->f[0].d = ctx->ps1[0] = ldfs(base, F_I2F_MAGIC);
    int all = CMPU(R(3), 1) == 0;
    ctx->f[1].u = ld64(base, sp + 16);
    ctx->f[0].d = ctx->f[1].d - ctx->f[0].d;
    ctx->f[0].d = frsp(ctx->f[0].d);
    if (all) {
        R(3) = 0x81850000u;
        ctx->f[1].d = ctx->ps1[1] = ldfs(base, F_ONE);
        R(3) = 56;
        ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[1].d / ctx->f[0].d);
        ctx->f[1].d = ctx->ps1[1] = frsp(ctx->f[31].d * ctx->f[0].d);
        ctx->f[2].d = ctx->ps1[2] = frsp(ctx->f[29].d * ctx->f[0].d);
        stfs(base, self + 48, ctx->f[1].d);
        ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[30].d * ctx->f[0].d);
        stfs(base, self + 52, ctx->f[2].d);
    } else {
        ctx->f[0].d = ctx->ps1[0] = frsp(ctx->f[31].d / ctx->f[0].d);
        R(3) = 48;
    }
    stfs(base, self + R(3), ctx->f[0].d);
}

/* startControlDemoAll: every player in play comes under demo control; true when all were free
   (none already under it) */
static void dm_startControlDemoAll(GM_CTX) {
    I2_FN(0x81804A4Cu);
    R(3) = gm_u32(PY_NUM_);
    if (CMPU(R(3), 0) == 0) { R(3) = 0; return; }
    NV_R(29, 8); NV_R(28, 1); NV_R(30, 0); NV_R(27, PY_ACT_INFO);
    for (uint32_t p = 0;; ) {
        gptr pl = dm_ctrl(GM_PASS, p, 0x81804AA4u, 0);
        if (pl) { BL(0x81804AB0u, fn_80051E70); if (CMPU(R(3), 0) == 0) NV_R(28, 0); }   /* daPlBase_c::startControlDemo */
        NV_R(29, R(29) - 1);
        int more = CMPU(R(29), 0) > 0;
        NV_R(30, ++p);
        if (!more) break;
        GM_LOOP();
    }
    R(3) = cntlzw(R(28)) >> 5;
}
/* endControlDemoAll(arg) / UNDEF_8005CE50(type): each player in play: endControlDemo(arg) /
   setAnimePlayStandardType(type) */
static void dm_each_player(GM_CTX, uint32_t arg, uint32_t ra_get, uint32_t ra_call, void (*fn)(ppc_context *, uint8_t *)) {
    NV_R(27, PY_ACT_INFO); NV_R(28, 8); NV_R(29, 0); NV_R(30, arg);
    for (uint32_t p = 0;; ) {
        gptr pl = dm_ctrl(GM_PASS, p, ra_get, 0);
        if (pl) { R(4) = R(30); BL(ra_call, fn); }
        NV_R(28, R(28) - 1);
        int more = CMPU(R(28), 0) > 0;
        NV_R(29, ++p);
        if (!more) break;
        GM_LOOP();
    }
}
static void dm_endControlDemoAll(GM_CTX, uint32_t arg) {
    I2_FN(0x81804BA0u);
    dm_each_player(GM_PASS, arg, 0x81804BE8u, 0x81804BF8u, fn_80051EF0);
}
static void dm_setAnimePlayStandardTypeAll(GM_CTX, uint32_t type) {
    I2_FN(0x81804ECCu);
    dm_each_player(GM_PASS, type, 0x81804F14u, 0x81804F24u, setAnimePlayStandardType__10daPlBase_cFi_80052290);
}
/* getControlDemoPlayerNum: how many players in play are in control demo 4 */
static void dm_getControlDemoPlayerNum(GM_CTX) {
    I2_FN(0x81804C28u);
    uint32_t n = 0;
    NV_R(27, PY_ACT_INFO); NV_R(28, 8); NV_R(29, 0); NV_R(30, 0);
    for (uint32_t p = 0;; ) {
        gptr pl = dm_ctrl(GM_PASS, p, 0x81804C70u, 0);
        if (pl) { R(4) = 4; BL(0x81804C80u, fn_8004DB40); n += R(3); NV_R(30, n); }   /* daPlBase_c::isControlDemo(4) */
        NV_R(28, R(28) - 1);
        int more = CMPU(R(28), 0) > 0;
        NV_R(29, ++p);
        if (!more) break;
        GM_LOOP();
    }
    R(3) = n;
}
/* onLandStopReq: the players in control demo 4 get the land-stop flag */
static void dm_onLandStopReq(GM_CTX) {
    I2_FN(0x81804CB8u);
    NV_R(27, PY_ACT_INFO); NV_R(28, 8); NV_R(30, 0);
    for (uint32_t p = 0;; ) {
        gptr pl = dm_ctrl(GM_PASS, p, 0x81804CFCu, 0);
        if (pl) {
            R(4) = 4; NV_R(29, pl); BL(0x81804D10u, fn_8004DB40);
            if (CMPU(R(3), 0) != 0) { R(3) = R(29); SETFLAG(0x81804D24u, FLAG_DEMO_LAND_STOP); }
        }
        NV_R(28, R(28) - 1);
        int more = CMPU(R(28), 0) > 0;
        NV_R(30, ++p);
        if (!more) break;
        GM_LOOP();
    }
}
/* startControlDemoLandPlayer: the players that have landed and aren't in a demo yet start one;
   true when every player in play had landed */
static void dm_startControlDemoLandPlayer(GM_CTX) {
    I2_FN(0x81804D54u);
    R(3) = gm_u32(PY_NUM_);
    if (CMPU(R(3), 0) == 0) { R(3) = 0; return; }
    NV_R(28, 8); NV_R(26, 1); NV_R(30, 0); NV_R(27, PY_ACT_INFO);
    for (uint32_t p = 0;; ) {
        gptr pl = dm_ctrl(GM_PASS, p, 0x81804DB0u, 0);
        if (pl) {
            NV_R(29, pl); BL(0x81804DC0u, fn_80052470);                 /* daPlBase_c::isDemoLand */
            if (CMPU(R(3), 0) == 0) NV_R(26, 0);
            else {
                R(3) = R(29); R(4) = 4; BL(0x81804DD4u, fn_8004DB40);
                if (CMPU(R(3), 0) == 0) { R(3) = R(29); BL(0x81804DE4u, fn_80051E70); NV_R(26, 0); }
            }
        }
        NV_R(28, R(28) - 1);
        int more = CMPU(R(28), 0) > 0;
        NV_R(30, ++p);
        if (!more) break;
        GM_LOOP();
    }
    NONZERO(3, 3, R(26));
}

/* executeStartToride: the stage-start wait - follow the first player in the goal list who has
   landed; when all have, everyone stands (anim type 1) and the wait ends */
void hle_mod_fn_8005CDD0(ppc_context *ctx, uint8_t *base);
void hle_mod_fn_8005CE50(ppc_context *ctx, uint8_t *base);
static void dm_executeStartToride(GM_CTX, gptr self) {
    I2_FN(0x81804F54u);
    NV_R(30, self);
    R(3) = gm_u32(self + DM_TORIDE_STATE);
    if (CMPU(R(3), 1) != 0) {
        if (CMPU(R(3), 0) == 0) { R(3) = (uint32_t)-1; gm_set_u32(self + DM_TORIDE_PLAYER, R(3)); }
        return;
    }
    R(3) = gm_u32(self + DM_TORIDE_PLAYER);
    if (CMPS(R(3), -1) == 0) {
        NV_R(29, self + DM_GOAL_LIST); NV_R(27, 8); NV_R(28, 0);
        for (uint32_t i = 0;; ) {
            R(3) = CMPU(i, 4) < 0 ? i : i + 26;
            R(3) = gm_u32(R(29) + (R(3) << 2));
            if (CMPS(R(3), -1) != 0) {
                BL(0x81804FD0u, getCtrlPlayer__9daPyMng_cFi_8005FB90);
                if (CMPU(R(3), 0) != 0) {
                    BL(0x81804FDCu, fn_80052470);
                    if (CMPU(R(3), 0) != 0) { gm_set_u32(self + DM_TORIDE_PLAYER, i); break; }
                }
            }
            NV_R(27, R(27) - 1);
            int more = CMPU(R(27), 0) > 0;
            NV_R(28, ++i);
            if (!more) break;
            GM_LOOP();
        }
    }
    R(3) = self; BL(0x81805000u, hle_mod_fn_8005CDD0);                  /* isLandAll */
    if (CMPU(R(3), 0) == 0) return;
    R(3) = self; R(4) = 1; BL(0x81805010u, hle_mod_fn_8005CE50);        /* (everyone: anim type 1) */
    R(3) = 2; gm_set_u32(self + DM_TORIDE_STATE, 2);
}

/* genCourseInList: the course-in order - first the players in the course-out order (as they left
   the last course), then the rest of the players taking part (not in a bubble) in a random order;
   copied to daPyMng_c::mCourseInList, the course-out list emptied */
static void dm_genCourseInList(GM_CTX, gptr self) {
    uint32_t cr_in = ctx->cr;
    I2_FN(0x81805168u);
    gptr sp = gm_frame_sp;
    R(12) = cr_in; gm_set_u32(sp + 64, cr_in);                           /* (mfcr: the CR the epilogue puts field 2 back from) */
    R(5) = 8; NV_R(28, 0); NV_R(30, self);
    R(3) = 0x81860000u; R(4) = gm_u32(STACK_GUARD); R(3) = 0;
    gm_set_u32(sp + 60, R(4)); R(4) = 1; ctx->ctr = 8;
    for (;;) {                                                           /* the course-out order first */
        R(5) = CMPU(R(28), 4) < 0 ? R(28) : R(28) + 14;
        R(5) = self + (R(5) << 2);
        R(6) = gm_u32(R(5) + DM_COURSE_OUT);
        if (CMPS(R(6), -1) == 0) break;
        gm_set_u32(R(5) + DM_COURSE_IN, R(6));
        R(5) = i2_bit(R(6)); R(3) |= R(5);                               /* (placed) */
        NV_R(28, R(28) + 1);
        if (--ctx->ctr == 0) { NV_R(28, 8); break; }
        GM_LOOP();
    }
    /* the others taking part, not in a bubble: candidates at sp + 28 */
    R(6) = PY_TYPE - 4; R(7) = PY_ENTRY - 4; R(5) = PY_CREATE_ITEM; R(4) = 0;
    NV_R(27, sp + 28); NV_R(29, 0); ctx->ctr = 8;
    for (;;) {
        R(8) = R(6);
        uint32_t placed = (R(4) & 63) > 31 ? 0 : (R(3) >> (R(4) & 63)) & 1;
        R(6) = placed; CR0(ctx, R(6));
        R(9) = R(7); R(6) = R(8) + 4; R(7) += 4;
        if (!placed) {
            R(9) = gm_u32(R(9) + 4);                                     /* (taking part) */
            if (CMPU(R(9), 0) != 0) {
                R(8) = gm_u32(R(8) + 4); R(8) <<= 2; R(8) = R(5) + R(8);
                R(8) = gm_u8(R(8) + 3) & 4; CR0(ctx, R(8));               /* (not in a bubble) */
                if (!R(8)) { R(8) = R(29) << 2; NV_R(29, R(29) + 1); gm_set_u32(R(27) + R(8), R(4)); }
            }
            GM_LOOP();                                                   /* (each of those paths jumps back once more) */
        }
        R(4)++;
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    cr_cmp_s(ctx, 2, (int32_t)R(29), 1);
    if (!CR_BIT(ctx, 8)) {                                               /* (two or more: shuffled) */
        NV_R(26, sp + 24); NV_R(25, R(29));
        for (;;) {
            R(3) = R(29); BL(0x8180529Cu, rndInt__8dGameComFUl_800B2EE0);
            R(3) <<= 2;
            NV_R(26, R(26) + 4); R(4) = gm_u32(R(26));
            NV_R(25, R(25) - 1);
            R(5) = gm_u32(R(27) + R(3));
            int more = CMPU(R(25), 0) > 0;
            gm_set_u32(R(26), R(5)); gm_set_u32(R(27) + R(3), R(4));
            if (!more) break;
            GM_LOOP();
        }
        R(3) = self + DM_COURSE_IN; R(4) = sp + 24; ctx->ctr = R(29);
        for (;;) {                                                       /* after the course-out ones */
            R(5) = CMPU(R(28), 4) < 0 ? R(28) : R(28) + 14;
            R(4) += 4; R(6) = gm_u32(R(4));
            R(5) <<= 2; NV_R(28, R(28) + 1);
            gm_set_u32(R(3) + R(5), R(6));
            if (--ctx->ctr == 0) break;
            GM_LOOP();
        }
    }
    R(4) = PY_COURSE_IN_LIST - 4; R(3) = 0; R(5) = (uint32_t)-1; ctx->ctr = 8;
    for (;;) {                                                           /* to daPyMng_c, the course-out list emptied */
        R(6) = CMPU(R(3), 4) < 0 ? R(3) : R(3) + 14;
        R(6) = self + (R(6) << 2);
        R(7) = gm_u32(R(6) + DM_COURSE_IN);
        R(3)++;
        gm_set_u32(R(6) + DM_COURSE_OUT, R(5));
        R(4) += 4; gm_set_u32(R(4), R(7));
        if (--ctx->ctr == 0) break;
        GM_LOOP();
    }
    R(3) = gm_u32(STACK_GUARD); R(4) = gm_u32(sp + 60);
    if (CMPU(R(3), R(4)) != 0) { BL(0x81805380u, mfn_81844FCC); return; }
    R(12) = gm_u32(sp + 64);
    ctx->cr = (ctx->cr & ~0xF00000u) | (R(12) & 0xF00000u);             /* (mtcrf: field 2 back) */
}

/* ================================================================== hle entry points */
#define SELF GM_ARG(0)
#define A(i) GM_ARG(i)
#define DM_SIZE 0xD0                     /* (as far as the module's fields go) */
#define DM_MEM SELF, DM_SIZE, PY_COURSE_IN_LIST, 32, PLAYER_KEY_FLAGS, 1
static void dm_selftest(GM_CTX, gptr self);
GM_HLE_VOID(mod_fn_8005B4A0, DM_MEM)                                  { dm_init(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_8005B6A0, DM_MEM)                                  { dm_calcNotGoalPlayer(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_8005B8A0, DM_MEM)                                  { dm_executeGoalDemo_Pole(GM_PASS, SELF); }
GM_HLE_INT (mod_setGoalDemoList__13daPyDemoMng_cFi, DM_MEM)           { dm_setGoalDemoList(GM_PASS, SELF, A(1)); }
GM_HLE_INT (mod_getPoleBelowPlayer__13daPyDemoMng_cFi, DM_MEM)        { dm_getPoleBelowPlayer(GM_PASS, SELF, A(1)); }
GM_HLE_VOID(mod_fn_8005BCF0, DM_MEM)                                  { dm_executeGoalDemo_PoleDown(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_8005BD60, DM_MEM)                                  { dm_executeGoalDemo_JumpCheck(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_8005BE30, DM_MEM)                                  { dm_executeGoalDemo_Jump(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_8005BF10, DM_MEM)                                  { dm_executeGoalDemo_Land(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_8005BFD0, DM_MEM)                                  { dm_executeGoalDemo_KimeWait(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_8005C130, DM_MEM)                                  { dm_setGoalDemoKimeAll(GM_PASS, SELF); }
GM_HLE_VOID(mod_fn_8005C1A0, DM_MEM)                                  { dm_setGoalDemoRunCastle(GM_PASS, SELF); }
GM_HLE_INT (mod_fn_8005C210, DM_MEM)                                  { dm_isAllPlayerGoalIn(GM_PASS); }
GM_HLE_VOID(mod_fn_8005C6D0, DM_MEM)                                  { dm_calcGoalCenterPos(GM_PASS, SELF); }
GM_HLE_INT (mod_demoControlAllPlayers__7WLClassFv, DM_MEM)            { dm_startControlDemoAll(GM_PASS); }
GM_HLE_INT (mod_fn_8005C9D0, DM_MEM)                                  { dm_isAllPlayerControlDemo(GM_PASS); }
GM_HLE_VOID(mod_disableDemoControl__7WLClassFb, DM_MEM)               { dm_endControlDemoAll(GM_PASS, A(1)); }
GM_HLE_INT (mod_getControlDemoPlayerNum__13daPyDemoMng_cCFv, DM_MEM)  { dm_getControlDemoPlayerNum(GM_PASS); }
GM_HLE_VOID(mod_fn_8005CB70, DM_MEM)                                  { dm_onLandStopReq(GM_PASS); }
GM_HLE_INT (mod_fn_8005CC00, DM_MEM)                                  { dm_startControlDemoLandPlayer(GM_PASS); }
GM_HLE_INT (mod_fn_8005CDD0, DM_MEM)                                  { dm_isLandAll(GM_PASS); }
GM_HLE_VOID(mod_fn_8005CE50, DM_MEM)                                  { dm_setAnimePlayStandardTypeAll(GM_PASS, A(1)); }
GM_HLE_VOID(mod_fn_8005CED0, DM_MEM)                                  { dm_executeStartToride(GM_PASS, SELF); }
GM_HLE_VOID(mod_setCourseOutList__13daPyDemoMng_cFSc, DM_MEM)         { dm_selftest(GM_PASS, SELF); dm_setCourseOutList(GM_PASS, SELF, A(1)); }
GM_HLE_VOID(mod_turnNextDemoNo__13daPyDemoMng_cFv, DM_MEM)            { dm_selftest(GM_PASS, SELF); dm_turnNextDemoNo(GM_PASS, SELF); }
GM_HLE_VOID(mod_clearDemoNo__13daPyDemoMng_cFSc, DM_MEM)              { dm_selftest(GM_PASS, SELF); dm_clearDemoNo(GM_PASS, SELF, A(1)); }
#define GAME_RANDOM 0x80429F44u          /* dGameCom's cRandom_c (r13 - 22332): the shuffle draws from it */
GM_HLE_VOID(mod_fn_8005D280, DM_MEM, GAME_RANDOM, 4)                  { dm_selftest(GM_PASS, SELF); dm_genCourseInList(GM_PASS, SELF); }

/* ================================================================== self-test (RT_GM_SELFTEST=py_demo)
   The list functions, with the lists random (players 0-7 or -1, the goal count 0-8) */
static const gm_test_t dm_tests[] = {
    GM_TEST(mod_setGoalDemoList__13daPyDemoMng_cFi, GMV_RET, "p"),
    GM_TEST(mod_getPoleBelowPlayer__13daPyDemoMng_cFi, GMV_RET, "p"),
    GM_TEST(mod_setCourseOutList__13daPyDemoMng_cFSc, 0, "p"),
    GM_TEST(mod_turnNextDemoNo__13daPyDemoMng_cFv, 0, ""),
    GM_TEST(mod_clearDemoNo__13daPyDemoMng_cFSc, 0, "p"),
};
static gptr dm_test_self;
static void dm_randomize(GM_CTX, int round) {
    (void)ctx; (void)base; (void)round;
    for (uint32_t a = 0; a < DM_SIZE; a += 4) gm_set_u32(dm_test_self + a, gm_rand() % 3 ? gm_rand() % 8 : (uint32_t)-1);
    gm_set_u32(dm_test_self + DM_GOAL_NUM, gm_rand() % 10);
}
static void dm_selftest(GM_CTX, gptr self) {
    if (!gm_selftest_wanted("py_demo")) return;
    dm_test_self = self;
    const gptr ranges[] = { self, DM_SIZE };
    const gm_selftest_t t = { "py_demo", dm_tests, (int)(sizeof dm_tests / sizeof *dm_tests), 300, ranges, 1, dm_randomize, NULL };
    gm_selftest(GM_PASS, &t);
}
