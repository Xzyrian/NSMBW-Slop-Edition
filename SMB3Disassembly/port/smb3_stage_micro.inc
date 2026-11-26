/* smb3_stage_micro.inc - the Para-Goomba that drops Micro-Goombas (OBJ_PARAGOOMBAWITHMICROS $74,
 * 1-3) and its Micro-Goombas (included by smb3_stage_enemies.inc, after smb3_stage_battle.inc).
 *
 * ObjNorm_ParaGoombaBomber (prg004), Var4:
 *  0 Paragoomba_FlutterDown: walks (+-8), falls slowly (Y velocity -2 a frame after Object_Move's
 *    3), on the floor faces the Player every 64 ticks; once its timer is out: on to 1
 *  1 Paragoomba_FlyAbovePlayer: up (-$10) until $38 or more above the Player, then eases down to
 *    a stop (Y velocity +1 to 0): Timer $80, on to 2
 *  2 Paragoomba_DropMicrogoombas: a Micro-Goomba every 32 ticks, bobbing (+-8 every 16); timer
 *    out: Timer $80, back to 0
 *  1 and 2 fly towards the Player: X velocity +-1 a frame to +-$14, facing it every 64 ticks.
 *  Frame by Var5 & 8; wings flap by Var3 (+3 / +2 a frame flying). Drawn as a Para-Goomba
 *  (ParaGoomba_Draw: a Goomba, PAL3, with wings). Stomped: a Goomba (OCSPECIAL_KILLCHANGETO).
 * SObj_Microgoomba (prg007): drops from it (+4, +4), falling to Y velocity $10, swaying (X
 *  velocity +-1 to +-$10 and back); touching a Player it sticks (Data 5): it rides on the Player,
 *  bobbing, and holds it to a walk (Player_UphillSpeedIdx 1: Player_UphillSpeedVals $16) - every
 *  new button press shakes it (-1), every 16 ticks it holds on (+1, to 5); shaken off (0) or a
 *  star: it flops off (-$20, +-8) and falls away. One 8 x 16 sprite ($FF, bank $4F, PAL3), turned
 *  every 8 ticks. */

#define OBJ_PARAGOOMBAWITHMICROS 0x74
#define NMG 6                                     /* (special object slots 0-5) */
static struct { int on, x, y, xvel, yvel, xfrac, yfrac, var1, data, who; uint16_t keys_was; } mgb[NMG];
static void mg_reset(void) { memset(mgb, 0, sizeof mgb); }

static void mg_spawn(const obj_t *o) {           /* Paragoomba_SpawnMicroGoomba */
    int k = NMG - 1; while (k >= 0 && mgb[k].on) k--;
    if (k < 0) return;
    memset(&mgb[k], 0, sizeof mgb[k]);
    mgb[k].on = 1; mgb[k].x = o->x + 4; mgb[k].y = o->y + 4; mgb[k].who = -1;
}
static void norm_pgbomber(obj_t *o) {            /* ObjNorm_ParaGoombaBomber */
    int n = near_pl(o);
    o->frame = (o->var5 & 0x08) ? 1 : 0;                                 /* (PRG004_B34E[LRBounce_Vel + 2]) */
    if (o->var4 == 0) {                                                  /* Paragoomba_FlutterDown */
        o->var5++;
        o->xvel = (o->flip & SPR_HFLIP) ? 8 : -8;
        obj_move2(o);
        o->yvel -= 2;
        int v3 = 8;
        if (o->det & 4) {
            if (!(o->var5 & 0x3F)) o->flip = xdiff(o, n) == 0 ? SPR_HFLIP : 0;
            hit_ground(o);
            v3 = 0;
            if (!o->timer) { o->var4++; goto walls; }
            if (o->timer < 0x20) v3 = 8;
        }
        o->var3 = v3;
    walls:
        if (o->det & 3) flip_face(o);
        return;
    }
    if (o->var4 == 1) {                                                  /* Paragoomba_FlyAbovePlayer */
        o->var3 += 3;
        int above = n >= 0 ? pp[n].y - o->y : 0;                         /* (Level_ObjCalcYDiffs) */
        if (n >= 0 && above >= 0x38) {
            o->yvel++;
            if (o->yvel == 0) { o->var4++; o->timer = 0x80; return; }
        } else o->yvel = -0x10;
        apply_yvel(o);
    } else {                                                             /* Paragoomba_DropMicrogoombas */
        if (!o->timer) { o->var4 = 0; o->timer = 0x80; }
        o->var3 += 2;
        o->var5++;
        if (!(o->var5 & 0x1F)) mg_spawn(o);
        o->yvel = (o->var5 & 0x10) ? -8 : 8;
    }
    {   int y = (o->flip & SPR_HFLIP) ? 0 : 1;                           /* (PRG004_B046: towards where it faces) */
        static const int lim[2] = {0x14, -0x14}, acc[2] = {1, -1};       /* Paragoomba_XVelLimit / _XVelAccel */
        if (o->xvel != lim[y]) o->xvel += acc[y];
        o->var2++;
        if (!(o->var2 & 0x3F)) o->flip = xdiff(o, n) == 0 ? SPR_HFLIP : 0;
        apply_xvel(o);
        apply_yvel(o);                                                   /* (Object_ApplyYVel_NoLimit - for 1 a second time, as SMB3 does) */
    }
}

/* (each frame, with the objects) SObj_Microgoomba */
static int mg_stuck_on(int n) { for (int k = 0; k < NMG; k++) if (mgb[k].on && mgb[k].data > 0 && mgb[k].who == n) return 1; return 0; }
static void mgs_frame(float cam_l, float cam_r) {
    for (int k = 0; k < NMG; k++) {
        if (!mgb[k].on) continue;
        if (mgb[k].data < 0) {                                            /* (flopped off: falling away) */
            int p = mgb[k].x * 16 + mgb[k].xfrac + mgb[k].xvel; mgb[k].x = p >> 4; mgb[k].xfrac = p & 15;
            p = mgb[k].y * 16 + mgb[k].yfrac + mgb[k].yvel; mgb[k].y = p >> 4; mgb[k].yfrac = p & 15;
            if (mgb[k].yvel < 0x6E) mgb[k].yvel += 2;
        } else if (mgb[k].data > 0) {                                     /* (stuck on a Player) */
            int n = mgb[k].who;
            if (n < 0 || n > 7 || !pp[n].on || pp[n].star) mgb[k].data = 0;
            else {
                if (mgb[k].data < 5 && !(counter1 & 0x0F)) mgb[k].data++;
                uint16_t keys = (uint16_t)(pp[n].pl ? R16(pp[n].pl + PL_KEY + 4) : 0), pressed = keys & ~mgb[k].keys_was;
                mgb[k].keys_was = keys;
                if (pressed) mgb[k].data--;                               /* (Pad_Input: a new press) */
            }
            if (mgb[k].data <= 0) {                                       /* (off: SpecialObj_Data $FF) */
                mgb[k].data = -1; mgb[k].yvel = -0x20; mgb[k].xvel = (bt_rand() & 0x80) ? -8 : 8;
                rt_log("smb3", "micro-goomba: shaken off player %d", mgb[k].who + 1);
                continue;
            }
            mgb[k].var1++;
            int a = (mgb[k].var1 >> 2) & 0x1F, ty = a & 0x0F; if (a >= 0x10) ty = (ty ^ 0x0F) + 1;   /* (bobbing: a triangle) */
            if (pp[n].small) ty = (ty >> 1) + 8;
            int b = mgb[k].var1 & 0x1F, tx = b & 0x0F; if (b >= 0x10) tx = (tx ^ 0x0F) + 1;
            mgb[k].y = pp[n].y + ty; mgb[k].x = pp[n].x + tx - 3;
            continue;
        } else {                                                         /* (dropping) */
            int p = mgb[k].x * 16 + mgb[k].xfrac + mgb[k].xvel; mgb[k].x = p >> 4; mgb[k].xfrac = p & 15;
            p = mgb[k].y * 16 + mgb[k].yfrac + mgb[k].yvel; mgb[k].y = p >> 4; mgb[k].yfrac = p & 15;
            if (mgb[k].yvel < 0x10) mgb[k].yvel++;
            int y = mgb[k].var1 & 1;
            mgb[k].xvel += y ? -1 : 1;                                    /* Microgoomba_XAccel */
            if (mgb[k].xvel == (y ? -0x10 : 0x10)) mgb[k].var1++;          /* Microgoomba_XLimit */
            if (!((k + counter1) & 1))                                   /* SObj_PlayerCollide: it sticks */
                for (int n = 0; n < 8; n++) {
                    if (!pp[n].on || pp[n].star || wb_hidden(n)) continue;   /* (Player_Behind_En: not touched) */
                    int dy = mgb[k].y + 8 - pp[n].y - (pp[n].small ? 18 : 10), dx = mgb[k].x + 6 - pp[n].x;
                    if (dy >= 0 && dy < (pp[n].small ? 0x10 : 0x16) && dx >= 0 && dx < 16) {
                        mgb[k].data = 5; mgb[k].who = n; mgb[k].keys_was = (uint16_t)(pp[n].pl ? R16(pp[n].pl + PL_KEY + 4) : 0);
                        rt_log("smb3", "micro-goomba: stuck on player %d", n + 1); break;
                    }
                }
        }
        if (mgb[k].x < cam_l - 48 || mgb[k].x > cam_r + 48 || mgb[k].y > LH * 16 + 16) mgb[k].on = 0;
    }
    /* stuck ones hold their Player to a walk (Player_UphillSpeedVals[1]: $16, 1.375 a frame) */
    for (int n = 0; n < 8; n++) if (pp[n].on && pp[n].pl && mg_stuck_on(n)) {
        uint32_t pl = pp[n].pl; float vx = RF(pl + PL_SPEED), lim = 1.375f;
        if (vx > lim) W32(pl + PL_SPEED, fbits(lim)); else if (vx < -lim) W32(pl + PL_SPEED, fbits(-lim));
        float f = RF(pl + PL_SPEED_F); if (f > lim) W32(pl + PL_SPEED_F, fbits(lim)); else if (f < -lim) W32(pl + PL_SPEED_F, fbits(-lim));
    }
}
#define MG_QUADS NMG
static int mg_quads(void) { return BT.mg_slot >= 0 ? MG_QUADS : 0; }
static void mg_draw(float z) {
    if (BT.mg_slot < 0) return;
    extern uint64_t g_frames_presented;
    for (int k = 0; k < NMG; k++) {
        if (!mgb[k].on) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); continue; }
        int sl = BT.mg_slot, hf = (tick & 8) != 0 && mgb[k].data >= 0, vf = mgb[k].data < 0;
        float u0 = (sl % 16) * 16 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h, u1 = u0 + 8 / 256.0f, v1 = v0 + 16 / (float)tex_h;
        if (hf) { float t = u0; u0 = u1; u1 = t; }
        if (vf) { float t = v0; v0 = v1; v1 = t; }
        quad(L.lx + mgb[k].x, -(L.ly + mgb[k].y), L.lx + mgb[k].x + 8, -(L.ly + mgb[k].y + 16), z, u0, v0, u1, v1);
    }
}
