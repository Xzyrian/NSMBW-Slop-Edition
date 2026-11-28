/* smb3_stage_enemies.inc - SMB3's enemies in the stage (included by smb3_stage.c).
 *
 * The object core of prg000 (Object_Move, Object_WorldDetect4, Object_HitGround, the states
 * ObjState_Normal / Shelled / Held / Kicked / Killed / Squashed, Player_HitEnemy with its stomp /
 * kick / hold / hurt, Enemy_Kill for the tail, Object_HandleBumpUnderneath, the shell's
 * ObjectToObject_HitTest, Object_BumpOffOthers) and the walkers of prg004 (ObjNorm_GroundTroop:
 * Goomba, green Koopa Troopa, the hopping green Paratroopa; ObjNorm_RedTroopa; ObjNorm_ParaGoomba)
 * with their drawing (GroundTroop_Draw / Troopa_Draw / ParaGoomba_Draw), in SMB3's units: level
 * pixels, 4.4 fixed point velocities, its frame counters. SMB3 has one Player; here every NSMBW
 * player is one, each tested as SMB3 tests its Player (Player_X / Player_Y the top left of its
 * 16 x 32 box, Player_XVel / Player_YVel from the NSMBW speeds); "towards the Player" is towards
 * the nearest. The level's own object list (Level_ObjPtrOrig, bank 6) gives what appears where. */

enum { OBJ_ENDLEVELCARD = 0x41, OBJ_GREENTROOPA = 0x6C, OBJ_REDTROOPA = 0x6D, OBJ_PARATROOPAGREENHOP = 0x6E,
       OBJ_GOOMBA = 0x72, OBJ_PARAGOOMBA = 0x73, OBJ_GREENPIRANHA = 0xA0, OBJ_GREENPIRANHA_FIRE = 0xA4, OBJ_VENUSFIRETRAP = 0xA6 };
enum { OBJ_WOODENPLAT_RIDER = 0x26, OBJ_OSCILLATING_H = 0x27, OBJ_OSCILLATING_V = 0x28, OBJ_WOODENPLATFORM = 0x36,
       OBJ_OSCILLATING_HS = 0x37, OBJ_OSCILLATING_VS = 0x38, OBJ_WOODENPLATFORMFALL = 0x3C, OBJ_WOODENPLATUNSTABLE = 0x44 };
static int obj_inert(int id);
static int obj_platform(int id) {
    return id == OBJ_WOODENPLAT_RIDER || id == OBJ_OSCILLATING_H || id == OBJ_OSCILLATING_V || id == OBJ_WOODENPLATFORM ||
           id == OBJ_OSCILLATING_HS || id == OBJ_OSCILLATING_VS || id == OBJ_WOODENPLATFORMFALL || id == OBJ_WOODENPLATUNSTABLE;
}

static int obj_inert(int id) { return obj_platform(id) || id == 0x34 || id == 0x52; }   /* (the platforms, Toad, a treasure box: not enemies) */
enum { OS_DEAD, OS_INIT, OS_NORMAL, OS_SHELLED, OS_HELD, OS_KICKED, OS_KILLED, OS_SQUASHED, OS_POOF };
#define SPR_HFLIP 0x40
#define SPR_VFLIP 0x80
#define NOBJ 5                                   /* (SMB3's general object slots 0-4) */
typedef struct {
    int state, id, x, y, xvel, yvel, xfrac, yfrac, flip, frame, det, slope;   /* (slope: Objects_Slope) */
    int timer, timer2, timer3, timer4, var1, var2, var3, var4, var5, var7, target, hits, kills, spawn, holder, phs;
    int pal;                                     /* Objects_SprAttr's palette, set at init and kept (a Para-Goomba's stays when its wings go) */
    float hx, hy, hz; uint64_t hseen;            /* (held: where NSMBW holds a shell, as last drawn - dEn_c's calcCarryPos) */
} obj_t;
static obj_t ob[NOBJ];
static struct { int msg, phase, wait, kind, hold, music; } goal;   /* (hold: the clock stays stopped once the goal's run is over - into the map) */   /* (the goal's run, below) */
static int sb_first_player(void);
static int kept_rest[8], keep_rest;
static float pz;
#define NFIRE 4
static struct { int on, x, y, xvel, yvel, xfrac, yfrac, var1; } fire[NFIRE];   /* SOBJ_PIRANHAFIREBALL, special object slots 0-3 */
static struct { int n; uint8_t id[96], col[96], row[96], spawned[96]; } OL;   /* (Level_ObjectsSpawned) */
static int counter1;                             /* Counter_1 */
static int kill_tally[8];                        /* Kill_Tally, a player's */
/* the players as SMB3's Player: this frame's (from player_blocks) */
static struct { int on; uint32_t pl; int x, y, xvel, yvel, small, flip, dash, ground, star, noharm, cancarry, mdlcarry; uint64_t seen; } pp[8];
static uint64_t objs_exec_frame;                 /* (a player's executeMain ran this frame: the game isn't paused or stopped) */
static int objs_started;
static int held_by(int n);
static void carry_begin(int n);
static void plats_off(void);                     /* (smb3_stage_platforms.inc) */
static void th_reset(void);                      /* (smb3_stage_toadhouse.inc) */
static void th_frame(void);
static void bt_reset(void);                      /* (smb3_stage_battle.inc) */
static void mg_reset(void);                      /* (smb3_stage_micro.inc) */
static int obj_bro(int id);
static float cam_l_, cam_r_;                     /* (this frame's screen, level pixels) */
static int iabs(int v) { return v < 0 ? -v : v; }

/* the kinds handled; anything else in the list stays unspawned for now */
static int obj_piranha(int id) { return id == OBJ_GREENPIRANHA || id == OBJ_GREENPIRANHA_FIRE || id == OBJ_VENUSFIRETRAP; }
static int obj_known(int id) { return id == 0x34 /* OBJ_TOAD */ || id == 0x52 /* OBJ_TREASUREBOX: a level's chest (issue #3) */ || obj_bro(id) || id == 0x74 /* OBJ_PARAGOOMBAWITHMICROS */ || id == OBJ_ENDLEVELCARD || id == OBJ_GOOMBA || id == OBJ_PARAGOOMBA || id == OBJ_GREENTROOPA || id == OBJ_REDTROOPA || id == OBJ_PARATROOPAGREENHOP || obj_piranha(id); }
static int obj_dieshelled(int id) { return id == OBJ_GREENTROOPA || id == OBJ_REDTROOPA || id == OBJ_PARATROOPAGREENHOP; }   /* OA3_DIESHELLED */
static int obj_squash(int id) { return id == OBJ_GOOMBA || id == OBJ_PARAGOOMBA || id == 0x74; }           /* OA3_SQUASH (else OA3_DIESHELLED) */
static int obj_gndmod(int id) { return id == OBJ_GOOMBA || id == OBJ_GREENTROOPA || id == OBJ_REDTROOPA; }   /* OA2_GNDPLAYERMOD */
static int obj_killchange(int id) { return (id == OBJ_PARAGOOMBA || id == 0x74) ? OBJ_GOOMBA : id == OBJ_PARATROOPAGREENHOP ? OBJ_GREENTROOPA : 0; }   /* OCSPECIAL_KILLCHANGETO */
static int obj_bounce_others(int id) { return id != OBJ_PARAGOOMBA && id != 0x74 && !obj_piranha(id); }                       /* OAT_BOUNCEOFFOTHERS */

/* -- the object list: Level_ObjPtrOrig ($7EBB) into bank 6 at $C000; a byte, then (id, column,
      row) to $FF -- */
static void objs_load_list(const uint8_t *wram) {
    OL.n = 0;
    uint16_t p = (uint16_t)(wram[0x1EBB] | wram[0x1EBC] << 8);
    if (p < 0xC000 || p >= 0xE000) { rt_log("smb3", "enemies: object list at $%04X?", p); return; }
    const uint8_t *d = smb3_rom + 16 + 6 * 0x2000 + (p - 0xC000) + 1;
    for (int i = 0; d[0] != 0xFF && OL.n < 96 && i < 96; i++, d += 3) {
        OL.id[OL.n] = d[0]; OL.col[OL.n] = d[1]; OL.row[OL.n] = d[2]; OL.spawned[OL.n] = 0; OL.n++;
    }
    {   const char *e = getenv("SMB3_STAGE_TEST_OBJ"); int id, c, r;      /* (testing: "id,column,row" hex id - one more object in the list) */
        if (e && sscanf(e, "%x,%d,%d", &id, &c, &r) == 3 && OL.n < 96) { OL.id[OL.n] = id; OL.col[OL.n] = c; OL.row[OL.n] = r; OL.spawned[OL.n] = 0; OL.n++; } }
    {   char ids[400]; int k = 0; ids[0] = 0;
        for (int i = 0; i < OL.n && k < 380; i++) k += snprintf(ids + k, sizeof ids - k, " %02X@%d,%d%s", OL.id[i], OL.col[i], OL.row[i], obj_known(OL.id[i]) ? "" : "?");
        rt_log("smb3", "enemies: %d objects in the list:%s", OL.n, ids); }
}
static void objs_reset(void) {
    plats_off(); th_reset(); bt_reset(); mg_reset();
    memset(ob, 0, sizeof ob); memset(fire, 0, sizeof fire); memset(&goal, 0, sizeof goal); memset(kill_tally, 0, sizeof kill_tally); memset(pp, 0, sizeof pp); objs_started = 0;
    for (int i = 0; i < OL.n; i++) OL.spawned[i] = 0;
}

/* -- the Player nearest an object; Level_ObjCalcXDiffs: 0 = the Player is to its right -- */
static int near_pl(const obj_t *o) {
    extern uint64_t g_frames_presented; int best = -1, bd = 1 << 30;
    for (int n = 0; n < 8; n++) if (pp[n].on && g_frames_presented - pp[n].seen < 3) {
        int d = iabs(pp[n].x - o->x); if (d < bd) { bd = d; best = n; } }
    return best;
}
static int xdiff(const obj_t *o, int n) { return n < 0 ? 0 : (pp[n].x - o->x) >= 0 ? 0 : 1; }

/* -- Object_Move and its parts -- */
static void apply_xvel(obj_t *o) { int p = o->x * 16 + o->xfrac + o->xvel; o->x = p >> 4; o->xfrac = p & 15; }   /* Object_AddVelFrac */
static void apply_yvel(obj_t *o) { int p = o->y * 16 + o->yfrac + o->yvel; o->y = p >> 4; o->yfrac = p & 15; }
static int tile_at(int x, int y) {               /* (Object_DetectTile: none below $1B0) */
    if (y < 0 || y >= LH * 16 || x < 0 || x >= L.w * 16) return 0;
    return tile_class(L.tile[(y >> 4) * L.w + (x >> 4)]);
}
/* Object_WorldDetect4 (TDO group 1, no slopes): the feet ($10, $08) or, going up, the head ($00,
   $08); the wall ahead ($09, $00 / $0F) */
/* In a slope level (Level_SlopeEn) the floor goes by the tile's slope shape (PRG000_C5BC-C67F):
   the object lands at the shape's depth at its middle (Object_SlopeHeight, added at
   Object_HitGround), the flat middle grounds lift it to a pixel above, a slope's tile walked off
   is followed down / up by Objects_Slope (its X speed's whole part, by the slope's way); the head
   meets anything from the slopes' base up */
static int obj_slope_h;                          /* Object_SlopeHeight */
static int obj_tile(int x, int y) { return (y < 0 || y >= LH * 16 || x < 0 || x >= L.w * 16) ? -1 : L.tile[(y >> 4) * L.w + (x >> 4)]; }
static void world_detect(obj_t *o, int depth) {
    o->det = 0; obj_slope_h = 0;
    int wall = tile_at(o->x + (o->xvel < 0 ? 0 : 15), o->y + 9);
    if (wall == 2) o->det |= o->xvel < 0 ? 2 : 1;
    if (o->yvel < 0) { if (tile_at(o->x + 8, o->y) >= (L.slopes ? 1 : 2)) o->det |= 8; return; }
    if (!L.slopes) { if (tile_at(o->x + 8, o->y + 16) && (o->y & 15) < depth) o->det |= 4; return; }   /* (PRG000_C649: no deeper than 4 into it) */
    int fx = o->x + 8, t = obj_tile(fx, o->y + 16), sh = t < 0 ? -1 : slope_shape((uint8_t)t);
    if (t >= 0 && tile_at(fx, o->y + 16)) {
        if (t == 0xA8 || t == 0xAA || t == 0xAB || t == 0xF9 || t == 0x37) {   /* (flat solid middles - TILE3_VERTGROUNDL/R, MIDGROUND, WMIDGROUND; TILE14_ABOVE_MIDGROUND) */
            if (o->state == OS_KILLED || o->state == OS_HELD) return;
            o->y = (o->y & ~15) - 1;                                     /* (a pixel above it, and again) */
            world_detect(o, 255); return;
        }
        if (sh >= 0 && sh <= 0x14 && Slope_ObjectVel_Effect[sh] != -128) {
            int h = Slope_LUT[sh][fx & 15] & 15, rel = o->y & 15;
            if (rel >= 12 || rel >= h) {
                obj_slope_h = h; o->det |= 4;
                int a = (o->xvel & 0xFF) >> 4; if (!a) a = 1; if (a >= 8) a |= ~15;   /* (the speed's whole part, signed - 1 at a stop) */
                int e = Slope_ObjectVel_Effect[sh];
                if (!e) a = 0; else if (e < 0) a = -a;
                o->slope = a;
                return;
            }
        }
    }
    if (o->slope) { o->y += o->slope; o->slope = 0; world_detect(o, 255); }   /* (PRG000_C65D: off a slope's edge - follow it) */
}
static void hit_ground(obj_t *o) { o->y = (o->y & ~15) + obj_slope_h; o->yvel = 0; }        /* Object_HitGround (with Object_SlopeHeight) */
static void obj_move2(obj_t *o) {                                                               /* Object_Move */
    apply_xvel(o); apply_yvel(o); world_detect(o, 4);
    o->yvel += 3; if (o->yvel >= 0 && o->yvel > 0x40) o->yvel = 0x40;   /* (OBJECT_FALLRATE, OBJECT_MAXFALL) */
}
static void flip_face(obj_t *o) { o->flip ^= SPR_HFLIP; }
static void about_face(obj_t *o) { o->xvel = -o->xvel; flip_face(o); }

/* -- bounding boxes (Object_BoundBox 1: troops; Player_BoundBox) and ObjectObject_Intersect -- */
typedef struct { int l, w, t, h; } box_t;
static box_t obj_box(const obj_t *o) {            /* (Object_BoundBox 1 troops, 2 Piranhas, $A the Venus Fire Trap) */
    box_t b = {o->x + 1, 13, o->y + 2, 8};
    if (o->id == OBJ_VENUSFIRETRAP) { b.l = o->x + 2; b.w = 12; b.t = o->y + 2; b.h = 20; }
    else if (obj_piranha(o->id) || obj_bro(o->id)) { b.l = o->x + 2; b.w = 12; b.t = o->y + 2; b.h = 24; }   /* (box 2: the Piranhas, the brothers) */
    return b;
}
static box_t pl_box(int n) { box_t b; if (pp[n].small) { b.l = pp[n].x + 4; b.w = 8; b.t = pp[n].y + 17; b.h = 13; } else { b.l = pp[n].x + 3; b.w = 10; b.t = pp[n].y + 5; b.h = 25; } return b; }
static int intersect(box_t p, box_t o) {        /* (the distance between the left edges within the left one's width; the same down) */
    int dx = p.l - o.l, dy = p.t - o.t;
    if (dx >= 0 ? dx > o.w : -dx > p.w) return 0;
    if (dy >= 0 ? dy > o.h : -dy > p.h) return 0;
    return 1;
}

/* -- scores: Score_Get100PlusPts (kill tally + 5: 100 ... 8000, then 1-ups) at the object -- */
static void obj_score(const obj_t *o, int tally, int who) { int v = tally + 5; if (v > 0x0D) v = 0x0D; score_pop(v, o->x, o->y - 16, who); }

/* -- the NSMBW side of SMB3's Player effects -- */
static void pl_bounce(int n) {                   /* Player_YVel = -$40: NSMBW's stomp jump (dEn_c::PlayerFumiJump) at 4 a frame */
    uint32_t pl = pp[n].pl, fn = R32(R32(pl + AC_VTABLE) + 0x3FC);
    blk_ctx->f[1].d = blk_ctx->ps1[1] = 4.0; blk_ctx->f[2].d = blk_ctx->ps1[2] = RF(pl + 0x10C);
    if (fn) gcall(blk_ctx, blk_base, fn, 4, pl, 1, 0, 2);
}
static void pl_hurt(int n) {                     /* Player_GetHurt: NSMBW's setDamage (its own invulnerability, power-down, death) */
    uint32_t pl = pp[n].pl, fn = R32(R32(pl + AC_VTABLE) + 0x3F4);
    if (fn && gcall(blk_ctx, blk_base, fn, 3, pl, pl, 0)) rt_log("smb3", "enemy: player %d hurt", n + 1);
}

/* -- states -- */
static void set_shell(obj_t *o) { o->state = OS_SHELLED; o->timer3 = 0xFF; }                    /* Object_SetShellState */
static void kill_by_shell(obj_t *o) { o->state = OS_KILLED; o->yvel = -0x30; }                  /* ObjectKill_SetShellKillVars */
/* Enemy_Kill (the tail: Temp_Var4 $0A - Y velocity -$50); troops shelled upside down, the rest killed for points */
static void enemy_kill(obj_t *o, int n, int bounced) {
    o->timer2 = 12; sfx_player(SFXP_KICK);       /* (Enemy_Kill: the kick sound) */
    if (!obj_dieshelled(o->id)) { obj_score(o, n >= 0 ? kill_tally[n] : 0, n); o->state = OS_KILLED; }
    else { int k = obj_killchange(o->id); if (k) o->id = k; o->timer3 = 0xFF; o->state = OS_SHELLED; }
    o->yvel = bounced ? -0x30 : -0x50;
    o->xvel = xdiff(o, n) ? 8 : -8;              /* (EnemyKill_XVels -$08, $08 by side) */
    o->flip |= SPR_VFLIP;
}
static void kick(obj_t *o, int n) {             /* Player_KickObject */
    o->timer2 = 0x10; o->kills = 0; sfx_player(SFXP_KICK);
    int y = o->state == OS_HELD ? (pp[n].flip ? 1 : 0) : xdiff(o, n);
    static const int kickv[2] = {-0x30, 0x30};   /* (ObjectKickXVelMoving) */
    o->xvel = kickv[y];
    if (!((o->xvel ^ pp[n].xvel) & 0x80) && pp[n].xvel) o->xvel = kickv[y] + (pp[n].xvel >> 1);   /* (half the Player's, the same way) */
    if (o->state != OS_KILLED) o->state = OS_KICKED;
    o->yvel = 0; o->holder = -1;
}
/* Player_HitEnemy for one player */
static void hit_player(obj_t *o, int n) {
    if (!intersect(pl_box(n), obj_box(o))) return;
    if (o->timer2) return;
    if (pp[n].star) {                            /* (Player_StarInv: the enemy dies) */
        enemy_kill(o, n, 1); if (obj_dieshelled(o->id)) { obj_score(o, kill_tally[n], n); o->state = OS_KILLED; }
        kill_tally[n]++; return;
    }
    int hurt = 0;
    if (obj_gndmod(o->id) && pp[n].ground && (o->yvel >= 0x0A || (o->det & 4))) hurt = 1;   /* (OA2_GNDPLAYERMOD: a Player on the ground) */
    else {
        /* stompable: the Player's top above the object's Y - 19 (16 bits) and going down (or a
           kill already) */
        if (pp[n].y > o->y - 19) hurt = 1;
        else if (pp[n].yvel < 0 && !kill_tally[n]) hurt = 1;
    }
    if (!hurt && obj_piranha(o->id)) hurt = 1;   /* (OA3_NOTSTOMPABLE: a stomp hurts) */
    if (hurt) {                                  /* Object_HoldKickOrHurtPlayer */
        if (o->state == OS_SHELLED) {
            if (held_by(n)) return;              /* (Player_ISHolding_OLD) */
            /* (picked up as NSMBW picks up: dAcPy_c::spinLiftUp's own conditions - nothing carried
               already (a player, say) - else kicked) */
            if (pp[n].dash && pp[n].cancarry) { o->state = OS_HELD; o->holder = n; carry_begin(n); }
            else { rt_log("smb3", "player %d kicks a shell (run %d, may carry %d, carry ID %08X)", n + 1, pp[n].dash, pp[n].cancarry, R32(pp[n].pl + 10872)); kick(o, n); }
            return;
        }
        /* PRG000_D355: nothing - no hurt, no turning - while the Player flashes from a hit (here:
           NSMBW's isNoDamage), is a statue or invincible, or the object's Timer2 runs */
        if (pp[n].noharm || pp[n].star || o->timer2) return;
        if (o->state == OS_KICKED && pp[n].xvel && !((pp[n].xvel ^ o->xvel) & 0x80)) {   /* (going with it, away from it: no harm) */
            if (xdiff(o, n) != (pp[n].xvel > 0 ? 0 : 1)) return;   /* (chasing it: no harm; it catching up: harm) */
        } else if (obj_bounce_others(o->id)) {
            o->flip = (o->flip & ~SPR_HFLIP) | (xdiff(o, n) == 0 ? SPR_HFLIP : 0);   /* (it turns towards the Player) */
        }
        if (o->state == OS_HELD) return;
        pl_hurt(n);
        return;
    }
    /* the stomp */
    if (o->state == OS_SHELLED) {                /* PRG000_D2A2: a kick, for points */
        obj_score(o, kill_tally[n], n); kill_tally[n]++; kick(o, n); return;
    }
    o->timer2 = 8; pl_bounce(n); sfx_player(SFXP_SQUISH);   /* PRG000_D2B4 (SND_PLAYERSWIM: the squish) */
    rt_log("smb3", "enemy: player %d stomps %02X (tally %d)", n + 1, o->id, kill_tally[n]);
    if (obj_bro(o->id)) {                       /* (OA2_NOSHELLORSQUASH: killed, halted; OCSPECIAL_HIGHSCORE: 1000 up) */
        nes_ram_ptr()[SMB3_Sound_QPlayer] = (uint8_t)((nes_ram_ptr()[SMB3_Sound_QPlayer] & ~SFXP_SQUISH) | SFXP_KICK);   /* (PRG000_D301: the kick sound, not the squish) */
        obj_score(o, kill_tally[n] + 4, n); kill_tally[n]++; o->state = OS_KILLED; o->xvel = o->yvel = 0; return;
    }
    int k = obj_killchange(o->id);
    obj_score(o, kill_tally[n], n); kill_tally[n]++;
    if (k) { o->id = k; o->yvel = 0; return; }   /* (OCSPECIAL_KILLCHANGETO: only the ID - the wings off, the palette kept) */
    if (obj_squash(o->id)) { o->state = OS_SHELLED; o->timer3 = 0xFF; } else set_shell(o);   /* (Object_SetShellState, the X velocity kept; a Goomba squashes next) */
    o->yvel = 0;
}
static int held_by(int n) { for (int i = 0; i < NOBJ; i++) if (ob[i].state == OS_HELD && ob[i].holder == n) return 1; return 0; }
/* -- holding, NSMBW's way (CHARACTERS_AND_GAMES.md: the carry is the character's): the model's
   carry flag and upper-body carry pose, as dAcPy_c::spinLiftUp sets them (m_17c | 2, +10208 = 1,
   the body anim 28, vfunc +1076 (18, 0)); isCarry (gm_d_player.c) reports the shell, so NSMBW's
   carry walk / wait / jump and its throw follow, with no NSMBW actor behind it -- */
#define PY_MDL_MGR      10852
#define A_CANCEL_CARRY  0x8012E510u
#define A_GET_CARRY_POS 0x8012DE80u
#define SM_CARRYPOS     (SM_MEM + 0x02C0)       /* (SM_JMTX + 0x40 is a ResFile holder) */
#define A_CALC_CARRY_POS 0x80097A20u            /* dEn_c::calcCarryPos(out, enemy, offset): the hands' position, then the enemy's own offset turned with the player's model */
#define SM_FAKE_EN      (SM_MEM + 0x3F400)       /* (a stand-in enemy for it: only its player number, +0x38D, is read) */
#define SM_CARRYOFS     (SM_MEM + 0x3F800)
static void carry_begin(int n) {
    uint32_t pl = pp[n].pl, mdl = R32(pl + PY_MDL_MGR);
    W32(pl + 10208, 1);
    W32(mdl + 380, R32(mdl + 380) | 2);
    blk_ctx->f[1].d = blk_ctx->ps1[1] = RF(blk_ctx->r[2] - 22780); blk_ctx->f[2].d = blk_ctx->ps1[2] = 0.0; blk_ctx->f[3].d = blk_ctx->ps1[3] = 0.0;
    gcall(blk_ctx, blk_base, R32(R32(mdl) + 100), 2, mdl, 28);
    gcall(blk_ctx, blk_base, R32(R32(pl + 96) + 1076), 3, pl, 18, 0);
    pp[n].mdlcarry = 1;
    rt_log("smb3", "player %d picks up a shell (NSMBW carry)", n + 1);
}
int smb3_stage_carry(uint32_t pl) {
    if (!smb3_stage_on()) return 0;
    for (int n = 0; n < 8; n++) if (pp[n].pl == pl) return held_by(n);
    return 0;
}
void smb3_stage_carry_release(uint32_t pl) {     /* (NSMBW lets go - a hit, a pipe, a throw's end: the shell drops where it is) */
    for (int n = 0; n < 8; n++) if (pp[n].pl == pl)
        for (int i = 0; i < NOBJ; i++) if (ob[i].state == OS_HELD && ob[i].holder == n) { ob[i].state = OS_SHELLED; ob[i].holder = -1; ob[i].xvel = 0; ob[i].yvel = 0; }
}
/* (from each player's draw: the held shell to the hands, as NSMBW's carried actors place themselves) */
static void objs_carry_pos(ppc_context *ctx, uint8_t *base, uint32_t pl) {
    extern uint64_t g_frames_presented;
    for (int n = 0; n < 8; n++) if (pp[n].pl == pl)
        for (int i = 0; i < NOBJ; i++) if (ob[i].state == OS_HELD && ob[i].holder == n) {
            /* (as a carried NSMBW shell places itself - dEn_c's shell carry (fn_800389E0) sets its
               offset from three SDA2 constants, then calcCarryPos: in front of the player, at
               the hands. The shell's position is its bottom centre) */
            W8(SM_FAKE_EN + 0x38D, R8(pl + PL_PLR_NO));
            uint32_t r2 = ctx->r[2];
            W32(SM_CARRYOFS, R32(r2 - 31440)); W32(SM_CARRYOFS + 4, R32(r2 - 31416)); W32(SM_CARRYOFS + 8, R32(r2 - 31412));
            gcall(ctx, base, A_CALC_CARRY_POS, 3, SM_CARRYPOS, SM_FAKE_EN, SM_CARRYOFS);
            ob[i].hx = RF(SM_CARRYPOS) - L.lx - 8; ob[i].hy = -RF(SM_CARRYPOS + 4) - L.ly - 16; ob[i].hz = RF(SM_CARRYPOS + 8) + 8.0f; ob[i].hseen = g_frames_presented;
            if (getenv("SMB3_STAGE_TRACE")) rt_log("smb3", "trace carry f%llu: offset %.2f %.2f %.2f -> %.1f %.1f %.1f (player %.1f %.1f %.1f)", (unsigned long long)g_frames_presented, RF(SM_CARRYOFS), RF(SM_CARRYOFS + 4), RF(SM_CARRYOFS + 8),
                RF(SM_CARRYPOS), RF(SM_CARRYPOS + 4), RF(SM_CARRYPOS + 8), RF(pl + 0xAC), RF(pl + 0xB0), RF(pl + 0xB4));
        }
}
static void hit_players(obj_t *o) { for (int n = 0; n < 8; n++) if (pp[n].on && !wb_hidden(n) && !pipe_hidden(n) && o->state >= OS_NORMAL && o->state <= OS_KICKED) hit_player(o, n); }

/* Object_HandleBumpUnderneath: a block bumped under its feet (its feet at the block's top: a
   kicked shell bumping a brick from the side, partly in that row, isn't standing on it) */
static int bump_self = -1;                       /* (the object whose hit bumped it) */
static void obj_block_bumped(int tx, int ty) {
    for (int i = 0; i < NOBJ; i++) {
        obj_t *o = &ob[i];
        if (i == bump_self || o->state < OS_NORMAL || o->state > OS_KICKED || o->state == OS_HELD || obj_piranha(o->id) || obj_inert(o->id)) continue;
        if (((o->x + 8) >> 4) != tx || ((o->y + 16) >> 4) != ty || o->y + 16 - ty * 16 > 4) continue;
        int n = near_pl(o);
        o->yvel = -0x30; o->xvel = xdiff(o, n) ? 8 : -8; o->flip = SPR_VFLIP; sfx_player(SFXP_KICK);
        if (obj_squash(o->id)) { o->state = OS_KILLED; obj_score(o, 0, n); }
        else { int k = obj_killchange(o->id); if (k) { o->id = k; obj_score(o, 0, n); } set_shell(o); }
    }
}
/* the tail swipe (Object_RespondToTailAttack at counter $0C and $09): a box 10 wide on the tail's
   side (Player_TailAttackXOff $11 / -$0A, for the Player turned as SMB3's swipe has it then: here,
   ahead) at the Player's middle */
static void obj_tail(int n, int left) {
    if (!pp[n].on) return;
    box_t t = {pp[n].x + (left ? -0x0A : 0x11), 0x0A, pp[n].y + 0x10, 0x0F};
    for (int i = 0; i < NOBJ; i++) {
        obj_t *o = &ob[i];
        if (o->state < OS_NORMAL || o->state > OS_KICKED || obj_inert(o->id)) continue;   /* (OA3_TAILATKIMMUNE) */
        if (!intersect(t, obj_box(o))) continue;
        enemy_kill(o, n, 0);
    }
}
/* ObjectToObject_HitTest for a kicked or held shell: the other dies; both if the other is kicked or this one is held */
static void shell_hits(obj_t *o, int self) {
    box_t a = obj_box(o);
    for (int i = NOBJ - 1; i >= 0; i--) {
        obj_t *p = &ob[i];
        if (i == self || p->state < OS_NORMAL || p->state > OS_KICKED || obj_inert(p->id)) continue;   /* (the platforms, Toad: OAT_HITNOTKILL, ObjHit_DoNothing) */
        if (!intersect(a, obj_box(p))) continue;
        if (iabs(p->x - o->x) >= 0x80) continue;
        int who = o->holder >= 0 ? o->holder : near_pl(o);
        if (o->state == OS_HELD || p->state == OS_KICKED || p->state == OS_HELD) {
            obj_score(o, p->state == OS_KICKED ? p->kills : 0, who);
            kill_by_shell(o); o->xvel = p->xvel < 0 ? -0x10 : 0x10; o->holder = -1;
        }
        p->xvel = o->xvel < 0 ? -0x10 : 0x10; kill_by_shell(p); sfx_player(SFXP_KICK);   /* (PRG000_CCF7 / D8EB: the kick sound) */
        obj_score(p, o->kills, who); o->kills++;
        return;
    }
}
/* GroundTroop_BumpOffOthers / Object_BumpOffOthers: walkers turn from each other */
static void bump_off_others(obj_t *o, int self) {
    if ((self + counter1) & 1) return;
    for (int i = self - 1; i >= 0; i--) {
        obj_t *p = &ob[i];
        if (p->state != OS_NORMAL || !obj_bounce_others(p->id) || obj_inert(p->id)) continue;
        if (!intersect(obj_box(p), obj_box(o))) continue;
        p->flip = p->x < o->x ? 0 : SPR_HFLIP;
        o->flip = o->x < p->x ? 0 : SPR_HFLIP;
    }
}
/* Object_ShellDoWakeUp: timer 3 out - a held one that's against a wall dies, else it walks again, towards the Player */
static int shell_wake(obj_t *o) {
    if (o->timer3) return 0;
    if (o->state == OS_HELD) {
        world_detect(o, 0xFF);
        if (o->det & 3) { score_pop(5, o->x, o->y - 16, o->holder); o->state = OS_KILLED; o->yvel = -0x40; o->xvel = 0; o->holder = -1; return 1; }
    }
    o->state = OS_NORMAL; o->holder = -1;
    o->flip = xdiff(o, near_pl(o)) == 0 ? SPR_HFLIP : 0;   /* (ObjectHeld_WakeUpDir) */
    return 1;
}

/* -- the walkers' normal states -- */
static void norm_groundtroop(obj_t *o, int self) {   /* ObjNorm_GroundTroop (Goomba, green Troopa, hopping Paratroopa) */
    o->xvel = (o->flip & SPR_HFLIP) ? 8 : -8;    /* (GroundTroop_XVel) */
    o->frame = (o->var5 >> 2) & 1;
    obj_move2(o);
    bump_off_others(o, self);
    o->var7 += 0x80; if (o->var7 > 0xFF) { o->var7 &= 0xFF; o->var5++; }
    if (!(o->det & 4)) {
        if (o->det & 8) o->yvel = 1;
        if (o->id == OBJ_PARATROOPAGREENHOP) o->yvel--;   /* (a float in its fall) */
        else o->var5 = 1;
    } else {
        hit_ground(o);
        if (o->id == OBJ_PARATROOPAGREENHOP) o->yvel = -0x30;   /* (the hop) */
    }
    if (o->det & 3) flip_face(o);
}
static void norm_redtroopa(obj_t *o, int self) {     /* ObjNorm_RedTroopa: it turns back at a ledge */
    o->frame = (o->var5 >> 3) & 1;
    o->var5++;
    bump_off_others(o, self);
    o->xvel = (o->flip & SPR_HFLIP) ? 8 : -8;
    obj_move2(o);
    if (o->det & 3) flip_face(o);
    if (!(o->det & 4)) {
        if (o->var4) return;
        o->var4++; about_face(o); apply_xvel(o); apply_xvel(o);
    } else o->var4 = 0;
    hit_ground(o);
}
static void norm_paragoomba(obj_t *o) {          /* ObjNorm_ParaGoomba: little hops, every 4th a big one */
    o->xvel = (o->flip & SPR_HFLIP) ? 8 : -8;
    obj_move2(o);
    o->yvel--;
    o->frame = (counter1 >> 3) & 1;
    o->var5++;
    if (!o->var4 && o->yvel < 0) o->var3 += 2;
    o->var3++;
    if (o->det & 8) o->yvel = 1;
    if (o->det & 4) {
        if (!(o->var5 & 0x3F)) o->flip = xdiff(o, near_pl(o)) == 0 ? SPR_HFLIP : 0;
        hit_ground(o);
        if (!o->var4) o->var3 = 0;
        if (!o->timer) {
            o->var4++; int v = -0x10;
            if (o->var4 == 4) { o->var4 = 0; o->timer = 0x50; v = -0x30; }
            o->yvel = v;
        }
    }
    if (o->det & 3) flip_face(o);
}

/* -- the Piranha Plants (ObjInit_GreenPiranha / _RedPiranha, ObjNorm_Piranha): in the pipe,
      emerging, attacking (the fire ones spit once, in World 1 at timer $28), retracting -- */
static void piranha_init(obj_t *o) {
    o->var5 = o->y; o->target = o->id == OBJ_VENUSFIRETRAP ? 33 : 25; o->var1 = o->target - 16;
    o->x += 8; o->var2 = o->id == OBJ_GREENPIRANHA ? 0x00 : 0x80; o->flip = 0;   /* (Piranha_Style) */
}
static void piranha_next(obj_t *o) { o->var4++; o->timer = o->id >= OBJ_GREENPIRANHA_FIRE ? 0x60 : 0x30; }   /* PRG005_A824 */
static void piranha_spit(obj_t *o) {             /* Piranha_SpitFire */
    int k = 0; while (k < NFIRE && fire[k].on) k++;
    int n = near_pl(o); if (k == NFIRE || n < 0) return;
    int dx = pp[n].x - o->x, close = dx >= -0x50 && dx < 0x50;
    static const int yv[2] = {0x0B, 0x05}, xv[2] = {0x0B, 0x0E};   /* (PiranhaFireball_YVel / _XVel: near, far) */
    fire[k].on = 1; fire[k].x = o->x + 3; fire[k].y = o->y; fire[k].xfrac = fire[k].yfrac = 0; fire[k].var1 = 0;
    fire[k].yvel = pp[n].y < o->y ? -yv[!close] : yv[!close];
    fire[k].xvel = xdiff(o, n) ? -xv[!close] : xv[!close];
}
static void norm_piranha(obj_t *o) {
    int st = o->var4 & 3, n = near_pl(o);
    if (st) {
        o->flip = (o->flip & ~SPR_HFLIP) | (xdiff(o, n) == 0 ? SPR_HFLIP : 0);   /* (Piranha_FacePlayerFlip) */
        o->frame = (o->var3 >> 3) & 1;
        if (o->var5 - o->y < 0x11) o->frame += 2;   /* (mostly in: no stem) */
        hit_players(o);
    }
    o->var3++;
    switch (st) {
    case 0:                                      /* Piranha_HideInPipe: out when the timer's done, unless a Player is near */
        if (o->timer) break;
        if (n >= 0 && pp[n].x - o->x >= -0x1B && pp[n].x - o->x < 0x1C) break;
        piranha_next(o); break;
    case 1:                                      /* Piranha_Emerge */
        if (o->y > o->var5 - o->target) { o->yvel = -0x10; apply_yvel(o); } else piranha_next(o);
        break;
    case 2:                                      /* Piranha_Attack */
        if (o->var2 & 0x80) { o->var3 = 0; if (o->timer == 0x28) piranha_spit(o); }
        if (!o->timer) piranha_next(o);
        break;
    case 3:                                      /* Piranha_Retract */
        if (o->y + 1 < o->var5) { o->yvel = 0x10; apply_yvel(o); } else piranha_next(o);
        break;
    }
}
/* SObj_Fireball (the Piranha's: straight, no gravity) and SObj_PlayerCollide, every other frame */
static void fires_frame(float cam_l, float cam_r) {
    for (int k = 0; k < NFIRE; k++) {
        if (!fire[k].on) continue;
        fire[k].var1++;
        int p = fire[k].x * 16 + fire[k].xfrac + fire[k].xvel; fire[k].x = p >> 4; fire[k].xfrac = p & 15;
        p = fire[k].y * 16 + fire[k].yfrac + fire[k].yvel; fire[k].y = p >> 4; fire[k].yfrac = p & 15;
        if (fire[k].x < cam_l - 16 || fire[k].x > cam_r + 16 || fire[k].y < -32 || fire[k].y > LH * 16 + 16) { fire[k].on = 0; continue; }
        if (!((k + counter1) & 1)) continue;
        for (int n = 0; n < 8; n++) {
            if (!pp[n].on || pp[n].star) continue;
            int dy = fire[k].y + 8 - pp[n].y - (pp[n].small ? 18 : 10), dx = fire[k].x + 6 - pp[n].x;
            if (dy >= 0 && dy < (pp[n].small ? 0x10 : 0x16) && dx >= 0 && dx < 16) pl_hurt(n);
        }
    }
}

/* -- the goal (prg002 ObjNorm_EndLevelCard / ObjHit_EndLevelCard): the card turns mushroom,
      flower, star every 8 frames; taken, every enemy on screen goes in a puff, the clock stops,
      the card flies up (-$28) and the messages come ($60 frames: "COURSE CLEAR!" at $1E, "YOU
      GOT A CARD" with it at 1), the time left goes into the score (DoTimeBonus, 50 a second), a
      third card gives lives (EndLevelCard_xUpByMatch: 2 / 3 / 5 for three alike, else 1) and
      the cards clear. Then - with no SMB3 map yet - the level again. -- */
static int goal_stop_timer(void) { return goal.phase != 0; }
/* The players at the goal (issue #15; CHARACTERS_AND_GAMES.md rule 1: the goal sequence is the
   character's): once the card is taken, every player in play comes under NSMBW's control demo
   (daPlBase_c::startControlDemo - StateID_DemoControl, or flag 113 until it can: in the air it
   lands first), so no one is steered any more; an NSMBW character then strikes NSMBW's goal pose
   (goal_pose, the pole's KimePose animation) once it is ready for a control action. NES
   characters only stop. The stage starting again (the map, or 1-1) ends the demo. */
#define A_START_CONTROL_DEMO 0x80051E70u         /* daPlBase_c::startControlDemo */
#define A_CONTROL_READY      0x80052030u         /* daPlBase_c::isReadyForDemoControlAction */
#define A_ANIME_PLAY_ID      0x80052170u         /* daPlBase_c::setAnimePlayWithAnimID(int) */
#define PL_ANM_GOAL_POSE     87                  /* (goal_pose: the 88th name of the animation table at 0x802F1350) */
static uint8_t goal_posed[8];
static void goal_players(int start) {
    for (int n = 0; n < 8; n++) {
        if (start) goal_posed[n] = 0;
        if (!pp[n].on || !pp[n].pl || goal_posed[n]) continue;
        uint32_t pl = pp[n].pl;
        gcall(blk_ctx, blk_base, A_START_CONTROL_DEMO, 1, pl);           /* (again each frame until it holds: harmless once in) */
        if (!gcall(blk_ctx, blk_base, A_CONTROL_READY, 1, pl)) continue;
        if (!retro_is_player(pl)) gcall(blk_ctx, blk_base, A_ANIME_PLAY_ID, 2, pl, PL_ANM_GOAL_POSE);
        goal_posed[n] = 1;
        rt_log("smb3", "goal: player %d stops%s", n + 1, retro_is_player(pl) ? "" : ", NSMBW's goal pose");
    }
}
/* DoTimeBonus (prg000): each frame, while a digit is left - 10 seconds off for 500 points while
   the hundreds or tens remain, then a second for 50 (TimeBonus_Score 50, 5: in tens). 1 while
   converting. SMB3 waits for the course clear music to end first (SndCur_Music1): here its
   length in frames (goal.music, from the card's touch), so it is the same on every machine. */
static int do_time_bonus(void) {
    if (goal.music > 0) return 1;
    if (SB.time <= 0) return 0;
    if (SB.time >= 10) { SB.time -= 10; SG.score += 50; } else { SB.time -= 1; SG.score += 5; }
    sfx_level1(SFX1_BLIP);                       /* (PRG000_C43C: the tick) */
    return 1;
}
static void goal_take(obj_t *o, int n) {
    extern uint64_t g_frames_presented; (void)g_frames_presented;
    uint32_t bg = R32(BG_PARAM_P); float l = bg ? RF(bg + 56) - L.lx : -1e9f, r = bg ? l + RF(bg + 64) : 1e9f;
    for (int i = 0; i < NOBJ; i++) {                                     /* (the enemies on screen: a puff) */
        obj_t *p = &ob[i]; if (p == o || p->state == OS_DEAD) continue;
        if (p->x + 16 >= l && p->x <= r) { p->state = OS_POOF; p->timer = 0x1F; } else p->state = OS_DEAD;
    }
    memset(fire, 0, sizeof fire);
    goal.kind = o->frame % 3 + 1; goal.phase = 1; goal.msg = 0;
    o->xvel = -1; o->yvel = -0x28; o->var4 = 4;
    int k = 0; while (k < 3 && SG.cards[k]) k++; if (k < 3) SG.cards[k] = goal.kind;   /* Player_GetCard */
    {   int triple = k == 2 && SG.cards[0] == SG.cards[1] && SG.cards[1] == SG.cards[2];   /* (PRG002_BF9F: "Got the Card", or the fanfare for three alike) */
        mus_q1(triple ? MUS1_BOSSVICTORY : MUS1_COURSECLEAR);
        goal.music = triple ? GOAL_FANFARE_FRAMES : GOAL_CLEAR_FRAMES; }
    rt_log("smb3", "goal: player %d takes the card (%d)", n + 1, goal.kind);
    goal_players(1);
}
static int goal_card(obj_t *o, int self) {      /* 1: the level starts over (stop here) */
    (void)self;
    if (goal.music > 0) goal.music--;
    if (o->var4 == 0) {                          /* EndLevelCard_Untouched */
        if (!(counter1 & 7)) o->frame = (o->frame + 1) % 3;
        for (int n = 0; n < 8; n++) if (pp[n].on && intersect(pl_box(n), obj_box(o))) { goal_take(o, n); break; }
        if (o->var4 == 0 && getenv("SMB3_STAGE_TEST_CARD") && pp[0].on) goal_take(o, 0);   /* (testing: player 1 takes the card as it comes) */
        return 0;
    }
    if (o->var4 >= 4 && o->var4 < 8) goal_players(0);   /* (the players: under demo control, posing) */
    if (o->var4 == 4) {                          /* EndLevelCard_WaitFlyAway */
        apply_yvel(o); apply_xvel(o);
        uint32_t bg = R32(BG_PARAM_P); float top = bg ? -RF(bg + 60) - L.ly : 0;
        if (o->y + 16 < top) { o->var4 = 5; o->timer = 0x60; }
        return 0;
    }
    if (o->var4 == 5) {                          /* EndLevelCard_MsgAndCard */
        if (o->timer == 0x1E) goal.msg = 1;
        if (o->timer == 1) goal.msg = 2;
        if (do_time_bonus() || o->timer) return 0;   /* (the clock into the score while the messages come; on when both are done) */
        if (SG.cards[2]) {                       /* EndLevelCard_DoXUPs */
            static const int xup[4] = {1, 2, 3, 5};
            int c = SG.cards[0], v = (SG.cards[1] == c && SG.cards[2] == c) ? xup[c] : xup[0];
            for (int i = 0; i < v; i++) give_life(sb_first_player());
            rt_log("smb3", "goal: three cards (%d %d %d): %d up", SG.cards[0], SG.cards[1], SG.cards[2], v);
            memset(SG.cards, 0, sizeof SG.cards);
        }
        o->var4 = 7; o->timer = 0x60;
        return 0;
    }
    if (o->var4 == 7 && !o->timer) {             /* EndLevelCard_Exit */
        o->var4 = 8;                             /* (once: the old stage runs on through NSMBW's wipe - its exit must not come again each frame) */
        goal.phase = 0; goal.msg = 0; goal.hold = 1;                   /* (the clock is at 0 now: NSMBW's must not run out while the wipe goes - a time-up death) */
        for (int i = 0; i < 8; i++) kept_rest[i] = (int)R32(MOD_PY_REST + 4 * (uint32_t)i);   /* (a clear costs no life: NSMBW's restart would) */
        keep_rest = 1;
        if (map_level_end(blk_ctx, blk_base, 0)) { rt_log("smb3", "goal: course clear - SMB3's map"); return 1; }
        rt_log("smb3", "goal: course clear - 1-1 again (no SMB3 map)");
        keep_counters = 1; smb3_stage_begin(blk_ctx, blk_base); keep_counters = 0;
        return 1;
    }
    return 0;
}

#include "smb3_stage_platforms.inc"
#include "smb3_stage_toadhouse.inc"
#include "smb3_stage_battle.inc"
#include "smb3_stage_micro.inc"

/* -- one frame of the objects (the object loop of prg000: timers, then the state) -- */
static void obj_spawn(int k, int slot) {
    if (getenv("SMB3_STAGE_TEST_NOENEMY")) return;                     /* (testing: no enemies) */
    if (getenv("SMB3_STAGE_TEST_ONLY") && OL.id[k] != (int)strtol(getenv("SMB3_STAGE_TEST_ONLY"), 0, 16)) return;   /* (testing: that enemy only) */
    obj_t *o = &ob[slot]; memset(o, 0, sizeof *o);
    o->id = OL.id[k]; o->x = OL.col[k] * 16; o->y = OL.row[k] * 16; o->spawn = k; o->holder = -1;
    o->state = OS_NORMAL; OL.spawned[k] = 1;
    if (obj_platform(o->id)) { platobj_init(o); return; }
    if (o->id == OBJ_TOAD) { toad_init(o); return; }
    if (obj_bro(o->id)) { bro_init(o); return; }
    if (o->id == OBJ_TREASUREBOX) { o->pal = 3; o->timer = 0x1F; return; }   /* (a chest in the level - World 1's tower, the Warp Whistle: ObjInit_TreasureBox, Level_TreasureItem's item; smb3_stage_battle.inc) */
    switch (o->id) {                             /* (ObjectGroup_Attributes: OA1_PAL*) */
    case OBJ_GREENTROOPA: case OBJ_PARATROOPAGREENHOP: case OBJ_GREENPIRANHA: case OBJ_GREENPIRANHA_FIRE: o->pal = 2; break;
    case OBJ_GOOMBA: case 0x74: o->pal = 3; break;                     /* (the Micro-Goomba dropper: OA1_PAL3) */
    default: o->pal = 1; break;                  /* (red Troopa, Para-Goomba, Venus Fire Trap) */
    }
    if (obj_piranha(o->id)) piranha_init(o);
    else o->flip = xdiff(o, near_pl(o)) == 0 ? SPR_HFLIP : 0;   /* ObjInit_GroundTroop: GroundTroop_FlipTowardsPlayer */
}
static void objs_spawn_delete(float cam_l, float cam_r) {   /* (Level_ObjectsSpawnByScroll / Object_DeleteOffScreen, about the NSMBW screen) */
    for (int i = 0; i < NOBJ; i++) {
        obj_t *o = &ob[i]; if (o->state == OS_DEAD || o->state == OS_HELD) continue;
        if (o->id == OBJ_ENDLEVELCARD && o->var4) continue;   /* (a taken card: its run is the goal's - kept wherever the camera goes; issue #16) */
        int w = obj_platform(o->id) ? PLAT_W : 16;
        if (o->x + w < cam_l - 48 || o->x > cam_r + 48 || o->y >= 0x200) {
            if (o->state != OS_KILLED && o->spawn >= 0) OL.spawned[o->spawn] = 0;   /* (Object_Delete: it can come back) */
            o->state = OS_DEAD;
        }
    }
    for (int k = 0; k < OL.n; k++) {
        if (OL.spawned[k] || !(obj_known(OL.id[k]) || obj_platform(OL.id[k]))) continue;
        int x = OL.col[k] * 16, w = obj_platform(OL.id[k]) ? PLAT_W : 16;
        if (x + w < cam_l - 16 || x > cam_r + 16) continue;
        if (x + w >= cam_l && x <= cam_r) continue;   /* (only as it comes in at an edge, as SMB3's scroll does) */
        int s = 0; while (s < NOBJ && ob[s].state != OS_DEAD) s++;
        if (s < NOBJ) obj_spawn(k, s);
    }
}
static void objs_first_spawn(float cam_l, float cam_r) {   /* (what's on screen when the level starts: Level_ObjectsInitialSpawn) */
    for (int k = 0; k < OL.n; k++) {
        if (OL.spawned[k] || !(obj_known(OL.id[k]) || obj_platform(OL.id[k]))) continue;
        int x = OL.col[k] * 16; if (x + (obj_platform(OL.id[k]) ? PLAT_W : 16) < cam_l - 16 || x > cam_r + 16) continue;
        int s = 0; while (s < NOBJ && ob[s].state != OS_DEAD) s++;
        if (s < NOBJ) obj_spawn(k, s);
    }
}
static void objs_frame(void) {
    extern uint64_t g_frames_presented;
    if (objs_exec_frame != g_frames_presented) return;   /* (paused) */
    counter1++;
    th_frame();                                                          /* (a Toad House's boxes and item - smb3_stage_toadhouse.inc) */
    uint32_t bg = R32(BG_PARAM_P);
    if (bg) {
        float l = RF(bg + 56) - L.lx, r = l + RF(bg + 64);
        cam_l_ = l; cam_r_ = r;
        if (objs_started < 30) { objs_started++; objs_first_spawn(l, r);   /* (Level_ObjectsInitialSpawn: what's on screen as the level starts - over its first frames, while NSMBW's camera comes to the player) */
}
        {   static int tshell; if (getenv("SMB3_STAGE_TEST_SHELL") && ++tshell == 90) {   /* (testing: a red Troopa's shell at column N on the ground, 1.5 s in) */
                obj_t *o = &ob[NOBJ - 1]; memset(o, 0, sizeof *o);
                o->id = 0x6D; o->x = atoi(getenv("SMB3_STAGE_TEST_SHELL")) * 16; { int c = o->x >> 4, g = 1; while (g < LH && tile_class(L.tile[g * L.w + c]) == 0) g++; o->y = g * 16 - 16; } o->holder = -1; o->spawn = -1; o->pal = 1;
                o->state = OS_SHELLED; o->timer3 = getenv("SMB3_STAGE_TEST_SHELL_T") ? (int)strtol(getenv("SMB3_STAGE_TEST_SHELL_T"), 0, 16) : 0xFF; o->frame = 2;
                rt_log("smb3", "test: a shell at (%d, %d), screen %.0f - %.0f", o->x, o->y, l, r);
            } }
        objs_spawn_delete(l, r);
        fires_frame(l, r);
        bt_frame(l, r);                                                  /* (a map brother's battle: the hammers, the treasure box) */
        mgs_frame(l, r);                                                 /* (Micro-Goombas) */
    }
    for (int n = 0; n < 8; n++) if (pp[n].on && pp[n].ground) kill_tally[n] = 0;   /* (Kill_Tally: back to 0 on the ground) */
    {   static int last[NOBJ], lid[NOBJ];             /* (the log: each slot's changes of state) */
        for (int i = 0; i < NOBJ; i++) if (ob[i].state != last[i] || ob[i].id != lid[i]) {
            rt_log("smb3", "enemy %d: %02X state %d -> %d at (%d, %d)%s", i, ob[i].id, last[i], ob[i].state, ob[i].x, ob[i].y, ob[i].state == OS_NORMAL && last[i] == OS_DEAD ? " (spawned)" : "");
            last[i] = ob[i].state; lid[i] = ob[i].id; } }
    if (getenv("SMB3_OBJ_TRACE"))                                        /* (testing: every live object, every frame) */
        for (int i = 0; i < NOBJ; i++) if (ob[i].state != OS_DEAD) rt_log("smb3", "trace obj %d %02X st %d x %d y %d xv %d yv %d det %X slope %d", i, ob[i].id, ob[i].state, ob[i].x, ob[i].y, ob[i].xvel, ob[i].yvel, ob[i].det, ob[i].slope);
    for (int i = 0; i < NOBJ; i++) {
        obj_t *o = &ob[i];
        if (pcol[i].on && (o->state != OS_NORMAL || !obj_platform(o->id))) plat_col_off(i);   /* (gone, or the slot something else's: its line out) */
        if (o->state == OS_DEAD) continue;
        if (o->timer) o->timer--;
        if (o->timer2) o->timer2--;
        if (o->timer4) o->timer4--;
        if (o->timer3) {
            int m = (o->timer3 >= 0x60 && o->state != OS_NORMAL) ? (o->state == OS_HELD ? 3 : 1) : 0;
            if (!(counter1 & m)) o->timer3--;
        }
        switch (o->state) {
        case OS_NORMAL:
            if (o->id == OBJ_ENDLEVELCARD) { if (goal_card(o, i)) return; break; }
            if (obj_platform(o->id)) { plat_frame(o, i); break; }            /* (smb3_stage_platforms.inc: no harm to players) */
            if (o->id == OBJ_TOAD) { toad_frame(o); break; }                 /* (smb3_stage_toadhouse.inc) */
            if (o->id == OBJ_TREASUREBOX) { box_frame(o); break; }           /* (smb3_stage_battle.inc) */
            if (obj_bro(o->id)) { if (o->id == OBJ_BOOMERANGBRO) norm_boomerangbro(o, i, cam_l_, cam_r_); else norm_hammerbro(o, i, cam_l_, cam_r_); hit_players(o); break; }
            if (obj_piranha(o->id)) norm_piranha(o);
            else if (o->id == OBJ_REDTROOPA) norm_redtroopa(o, i);
            else if (o->id == OBJ_PARAGOOMBA) norm_paragoomba(o);
            else if (o->id == OBJ_PARAGOOMBAWITHMICROS) norm_pgbomber(o);   /* (smb3_stage_micro.inc) */
            else norm_groundtroop(o, i);
            hit_players(o);
            break;
        case OS_SHELLED:                         /* ObjState_Shelled */
            if (obj_squash(o->id)) { o->timer3 = 0x10; o->state = OS_SQUASHED; break; }
            if (shell_wake(o)) break;
            obj_move2(o);
            if ((o->det & 4) && o->yvel >= 0) {
                int yv = o->yvel; hit_ground(o);
                o->xvel = o->xvel < 0 ? -((-o->xvel) >> 1) : o->xvel >> 1;   /* (halved on the ground) */
                int b = -((yv >> 2)); if (b < -2) o->yvel = b;   /* (a little bounce) */
            }
            if (o->det & 8) o->yvel = 0x10;
            if (o->det & 3) about_face(o);
            bump_off_others(o, i);
            o->frame = 2;
            if (o->timer3 < 0x60) o->timer4 = o->timer3 & 7;   /* (Object_SetShakeAwakeTimer) */
            hit_players(o);
            break;
        case OS_HELD: {                          /* ObjState_Held */
            int n = o->holder;
            if (n < 0 || !pp[n].on) { o->state = OS_SHELLED; o->holder = -1; break; }
            if (shell_wake(o)) break;
            if (!pp[n].dash) { kick(o, n); break; }
            static const int hold_x[2] = {-0x0B, 0x0B};   /* (ObjectHoldXOff: facing left, right) */
            extern uint64_t g_frames_presented;
            if (o->hseen + 2 >= g_frames_presented) { o->x = (int)floorf(o->hx + 0.5f); o->y = (int)floorf(o->hy + 0.5f); }   /* (in the hands: where NSMBW put them) */
            else { o->x = pp[n].x + hold_x[pp[n].flip ? 1 : 0]; o->y = pp[n].y + (pp[n].small ? 0x0F : 0x0D); }
            o->xvel = pp[n].xvel; o->yvel = pp[n].yvel;
            o->frame = 2;
            if (!o->timer2) shell_hits(o, i);
            break; }
        case OS_KICKED: {                        /* ObjState_Kicked */
            obj_move2(o);
            if (o->det & 4) { if (!o->xvel) o->xvel = xdiff(o, near_pl(o)) ? -0x18 : 0x18; hit_ground(o); o->yvel = 0x0C; }   /* (ObjKickXvel) */
            if (o->det & 3) {                    /* (a wall: the block there is hit, then back) */
                sfx_player(SFXP_BUMP);           /* (PRG000_CCE2: the bump sound) */
                int wx = o->x + (o->xvel < 0 ? 0 : 15), wy = o->y + 9, tx = wx >> 4, ty = wy >> 4;
                if (tx >= 0 && tx < L.w && ty >= 0 && ty < LH && is_block(L.tile[ty * L.w + tx])) { hit_who = near_pl(o) < 0 ? 0 : near_pl(o); hit_x = L.lx + o->x + 8; bump_self = i; hit_block(tx, ty, !pp[hit_who].small, 0, 0); bump_self = -1; }   /* (Object_BumpOffBlocks: Level_DoBumpBlocks - LATP by the Player's suit, a brick busted whatever it is) */
                about_face(o);
            }
            if (!((i + counter1) & 1)) shell_hits(o, i);   /* (semi-randomly, as SMB3) */
            static const uint8_t af[4] = {0, 0, 0, SPR_HFLIP}, fr[4] = {4, 6, 5, 6};   /* ObjShell_AnimFlipBits / _AnimFrame */
            int y = (counter1 >> 1) & 3;
            o->flip = (o->flip & ~SPR_HFLIP) | af[y]; o->frame = fr[y];
            hit_players(o);
            break; }
        case OS_KILLED:                          /* ObjState_Killed: upside down, falling away */
            if (obj_piranha(o->id)) { o->state = OS_POOF; o->timer = 0x1F; break; }   /* (KILLACT_POOFDEATH: Object_PoofDie) */
            o->flip |= SPR_VFLIP; if (!obj_bro(o->id)) o->frame = 2;     /* (a brother: KILLACT_JUSTDRAW16X32, its frame) */
            obj_move2(o); o->det = 0;
            break;
        case OS_POOF:                            /* ObjState_PoofDying */
            if (!o->timer) o->state = OS_DEAD;
            break;
        case OS_SQUASHED:                        /* ObjState_Squashed */
            if (!o->timer3) { o->state = OS_DEAD; break; }
            obj_move2(o);
            if (o->det & 4) { hit_ground(o); o->xvel = 0; }
            o->frame = 3;
            break;
        }
    }
}

/* -- the players, each frame (player_blocks): SMB3's Player fields -- */
static void objs_player(uint32_t pl, int n, int big, float px, float py) {
    extern uint64_t g_frames_presented;
    pp[n].pl = pl; pp[n].seen = g_frames_presented;
    pp[n].on = !gcall(blk_ctx, blk_base, A_TEST_FLAG, 2, pl, 4) && !gcall(blk_ctx, blk_base, A_TEST_FLAG, 2, pl, 53);  /* (out of play or in a balloon: not a Player to SMB3's objects) */
    pp[n].noharm = gcall(blk_ctx, blk_base, 0x80146060u, 1, pl) != 0;    /* (dAcPy_c::isNoDamage) */
    pp[n].x = (int)floorf(px - L.lx) - 8; pp[n].y = (int)floorf(-py - L.ly) - 32;
    if (getenv("SMB3_PLX_LOG") && n == 0 && !(counter1 & 1)) rt_log("smb3", "plx: x %.2f (level %.2f) y %.2f state %08X", px, px - L.lx, -py - L.ly, R32(pl + 0x1068));
    pp[n].xvel = (int)(RF(pl + PL_SPEED) * 16.0f); pp[n].yvel = (int)(-RF(pl + PL_SPEED + 4) * 16.0f);
    pp[n].small = !big; pp[n].flip = R8(pl + PL_DIRECTION) == 0;     /* (Player_FlipBits: set facing right) */
    pp[n].dash = gcall(blk_ctx, blk_base, A_KEY_DASH, 1, pl + PL_KEY) != 0;
    pp[n].ground = (R32(pl + PL_BG_CROSS1) & 1) != 0;
    pp[n].star = gcall(blk_ctx, blk_base, A_IS_STAR, 1, pl) != 0;
    pp[n].cancarry = !R32(pl + 10872);          /* (spinLiftUp: no carry ID - nothing NSMBW carries already, a player say) */
    if (pp[n].mdlcarry && !held_by(n)) { pp[n].mdlcarry = 0; gcall(blk_ctx, blk_base, A_CANCEL_CARRY, 2, pl, 0); }   /* (kicked, or woke up: the carry pose undone) */
}

/* -- the pictures: 8 x 16 sprite halves (pattern, palette) made at load -- */
static const uint8_t EH_PAT[] = {0xD9, 0xDB, 0xEB, 0xC1, 0xC7, 0xC9, 0xF9, 0xFB, 0xCB, 0xC3,             /* pal 3: Goomba; Troopa head, feet, lower head */
                                 0xD9, 0xDB, 0xEB, 0xCB, 0xC5, 0xC3, 0xFD, 0xD1, 0xD3, 0xD5, 0xCD, 0xCF,   /* pal 1: Para-Goomba; red Troopa; Paratroopa wings */
                                 0xCB, 0xC5, 0xC3, 0xFD, 0xD1, 0xD3, 0xD5, 0xCD, 0xCF,                   /* pal 2: green Troopa; Para-Goomba wings */
                                 0xE1, 0xE3, 0xE5, 0xF1, 0xF3, 0xF5, 0xF7,                               /* pal 2: Piranhas */
                                 0xF1, 0xF3, 0xF5, 0xF7, 0x65, 0x67, 0x41, 0x43, 0x45, 0x47,             /* pal 1: Venus' head; fireball; the poof */
                                 0x51, 0x53, 0x55,                                                       /* the goal card's mushroom (1), flower (2), star (1) */
                                 0x8F, 0x9D, 0x9F};                                                      /* pal 3: the log platforms (ObjP36) */
static const uint8_t EH_PAL[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  2, 2, 2, 2, 2, 2, 2, 2, 2,  2, 2, 2, 2, 2, 2, 2,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,  1, 2, 1,  3, 3, 3};
#define NEH ((int)sizeof EH_PAT)
static int eh_slot0;
static float eh_fx, eh_fy;                      /* (a fraction of a unit added to the sprites drawn: a held shell follows the hands smoothly) */
static int eh_of(uint8_t pat, int pal) { for (int i = 0; i < NEH; i++) if (EH_PAT[i] == pat && EH_PAL[i] == pal) return i; return -1; }
static void eh_quad(uint8_t pat, int pal, int x, int y, int hf, int vf, float z) {   /* (an 8 x 16 sprite at level pixel x, y) */
    int h = eh_of(pat, pal);
    if (h < 0) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); return; }
    int sl = eh_slot0 + (h >> 1);
    float u0 = (sl % 16) * 16 / 256.0f + (h & 1) * 8 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h, u1 = u0 + 8 / 256.0f, v1 = v0 + 16 / (float)tex_h;
    if (hf) { float t = u0; u0 = u1; u1 = t; }
    if (vf) { float t = v0; v0 = v1; v1 = t; }
    quad(L.lx + x + eh_fx, -(L.ly + y + eh_fy), L.lx + x + 8 + eh_fx, -(L.ly + y + 16 + eh_fy), z, u0, v0, u1, v1);
}
/* the same, only the rows above clip_y (a Piranha in its pipe) */
static void eh_quad_clip(uint8_t pat, int pal, int x, int y, int hf, int vf, float z, int clip_y) {
    int h = eh_of(pat, pal), rows = clip_y - y; if (rows > 16) rows = 16;
    if (h < 0 || pat == 0x71 || rows <= 0) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); return; }
    int sl = eh_slot0 + (h >> 1);
    float u0 = (sl % 16) * 16 / 256.0f + (h & 1) * 8 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h, u1 = u0 + 8 / 256.0f, v1 = v0 + 16 / (float)tex_h;
    if (hf) { float t = u0; u0 = u1; u1 = t; }
    if (vf) { v0 += (16 - rows) / (float)tex_h; float t = v0; v0 = v1; v1 = t; } else v1 = v0 + rows / (float)tex_h;
    quad(L.lx + x, -(L.ly + y), L.lx + x + 8, -(L.ly + y + rows), z, u0, v0, u1, v1);
}
/* a 16 x 16 pair (Object_ShakeAndDraw / ...Mirrored; GroundTroop_DrawNormal / _DrawMirrored):
   flipped, the pair's order swaps; mirrored, the right is the left's other half turned */
static void pair_quads(const uint8_t p[2], int pal, int x, int y, int flip, int mirrored, float z) {
    int hf = (flip & SPR_HFLIP) != 0, vf = (flip & SPR_VFLIP) != 0;
    uint8_t a = hf ? p[1] : p[0], b = hf ? p[0] : p[1];
    if (mirrored) { eh_quad(a, pal, x, y, 0, vf, z); eh_quad(b, pal, x + 8, y, 1, vf, z); }
    else { eh_quad(a, pal, x, y, hf, vf, z); eh_quad(b, pal, x + 8, y, hf, vf, z); }
}
#define OBJ_QUADS 6                              /* (each object: up to 6 sprites; unused ones empty) */
static int objs_quads(void) { int n = NFIRE; for (int i = 0; i < NOBJ; i++) if (ob[i].state != OS_DEAD) n += OBJ_QUADS; return n; }
static void objs_draw(float z_all) {
    static const uint8_t GOOMBA[4][2] = {{0xD9, 0xDB}, {0xDB, 0xD9}, {0xD9, 0xDB}, {0xEB, 0xEB}};   /* ObjP72 */
    static const uint8_t TROOPA[7][2] = {{0xCB, 0xC5}, {0xC3, 0xC5}, {0xFD, 0xFD}, {0xFD, 0xFD}, {0xFD, 0xFD}, {0xD1, 0xD1}, {0xD3, 0xD5}};   /* ObjP6C */
    for (int i = 0; i < NOBJ; i++) {
        obj_t *o = &ob[i]; if (o->state == OS_DEAD) continue;
        int used = 0, x = o->x, y = o->y; float z = z_all;
        eh_fx = eh_fy = 0;
        { extern uint64_t g_frames_presented; if (o->state == OS_HELD && o->hseen + 2 >= g_frames_presented) {
            x = (int)floorf(o->hx); y = (int)floorf(o->hy); eh_fx = o->hx - x; eh_fy = o->hy - y; z = o->hz; } }   /* (not rounded to whole units: the hands move by fractions, the shell with them) */   /* (this frame's hands, and their depth: a flat shell at its 3D model's front face, in front of the holder as NSMBW holds it) */
        if (o->timer4) {                         /* Object_ShakeAndCalcSprite: X - 1 when Timer4's low bit (bit 2 from $40) is clear - the shake as it wakes */
            int b = o->timer4 >= 0x40 ? (o->timer4 >> 2) & 1 : o->timer4 & 1;
            if (!b) x--;
        }
        #define EQ(...) do { eh_quad(__VA_ARGS__); used++; } while (0)
        if (obj_platform(o->id)) { plat_draw(o, z); used = OBJ_QUADS; }
        else if (o->id == OBJ_TOAD) { toad_draw(o, z); used = 4; }
        else if (o->id == OBJ_TREASUREBOX) { box_draw(o, z); used = 2; }
        else if (obj_bro(o->id)) { bro_draw(o, x, z); used = 4; }
        else if (o->state == OS_POOF) {               /* (PoofDeath_Pats by timer / 8; the flips turn) */
            static const uint8_t poof[4] = {0x47, 0x45, 0x41, 0x43};
            uint8_t pt = poof[(o->timer >> 3) & 3]; int vf = (counter1 >> 1) & 1;
            EQ(pt, 1, x, y, 0, vf, z); EQ(pt, 1, x + 8, y, 1, !vf, z);
        } else if (o->id == OBJ_ENDLEVELCARD) {  /* EndLevelCard_Draw: the frame's item, mirrored (mushroom, flower, star) */
            static const uint8_t cp[3] = {0x51, 0x53, 0x55}; static const int cpal[3] = {1, 2, 1};
            int f = o->var4 ? goal.kind - 1 : o->frame % 3; if (f < 0) f = 0;
            if (o->var4 < 5) { EQ(cp[f], cpal[f], x, y, 0, 0, z); EQ(cp[f], cpal[f], x + 8, y, 1, 0, z); }
        } else if (obj_piranha(o->id)) {         /* Object_Draw16x32Sprite: the head, the stem (green, mirrored); nothing while in the pipe */
            static const uint8_t PIR[2][16] = {{0xE1, 0xE1, 0xE3, 0xE3, 0xE5, 0xE5, 0xE3, 0xE3, 0xE1, 0xE1, 0x71, 0x71, 0xE5, 0xE5, 0x71, 0x71},   /* ObjPA0 */
                                               {0xF1, 0xF3, 0xE3, 0xE3, 0xF5, 0xF7, 0xE3, 0xE3, 0xF1, 0xF3, 0x71, 0x71, 0xF5, 0xF7, 0x71, 0x71}};  /* ObjPA4 */
            if (o->var4 & 3) {
                const uint8_t *pt = PIR[(o->var2 & 0x80) ? 1 : 0] + (o->frame & 3) * 4;
                int hf = (o->flip & SPR_HFLIP) != 0, pal = o->id == OBJ_VENUSFIRETRAP ? 1 : 2, clip = o->var5;
                if (o->var2 & 0x80) {            /* (the fire ones look at the Player: up when it's above) */
                    int n = near_pl(o), vf = n >= 0 && pp[n].y < o->y;
                    eh_quad_clip(hf ? pt[1] : pt[0], pal, x, y, hf, vf, z, clip); eh_quad_clip(hf ? pt[0] : pt[1], pal, x + 8, y, hf, vf, z, clip);
                } else { eh_quad_clip(pt[0], pal, x, y, 0, 0, z, clip); eh_quad_clip(pt[1], pal, x + 8, y, 1, 0, z, clip); }
                eh_quad_clip(pt[2], 2, x, y + 16, 0, 0, z, clip); eh_quad_clip(pt[3], 2, x + 8, y + 16, 1, 0, z, clip);
                used += 4;
            }
        } else if (o->id == OBJ_GOOMBA || o->id == OBJ_PARAGOOMBA || o->id == 0x74) {
            int pal = o->pal, f = o->frame & 3;
            pair_quads(GOOMBA[f], pal, x, y, o->flip, 1, z); used += 2;
            if ((o->id == OBJ_PARAGOOMBA || o->id == 0x74) && o->state == OS_NORMAL) {   /* ParaGoomba_Draw: wings 10 up, 2 out ($CD up / $CF down by Var3) */
                uint8_t w = (o->var3 & 8) ? 0xCD : 0xCF;
                EQ(w, 2, x - 2, y - 10, 1, 0, z); EQ(w, 2, x + 10, y - 10, 0, 0, z);
            }
        } else {
            int pal = o->pal, f = o->frame;
            if (o->state == OS_NORMAL && f < 2) {
                /* Troopa_Draw: GroundTroop_DrawOffsetInY (the pair 6 / 5 up; sprite 0 left, its
                   patterns swapped when flipped, both with the flip); the head's side - sprite 0, or 1
                   when flipped - gets the head's tip ($C1) 16 above and both on PAL3; feet 16 below
                   (Troopa_FootByEvenOddFrame[3 * odd + flipped], [.. + 1]; PAL3, the flip); a
                   Paratroopa's wing over the other side 8 up ($CD / $CF by Var5 + 2 + carry, PAL1) */
                static const uint8_t yoff[2] = {6, 5};
                int by = y - yoff[f], hf = (o->flip & SPR_HFLIP) != 0, vf = (o->flip & SPR_VFLIP) != 0;
                uint8_t p0 = hf ? TROOPA[f][1] : TROOPA[f][0], p1 = hf ? TROOPA[f][0] : TROOPA[f][1];
                EQ(p0, hf ? pal : 3, x, by, hf, vf, z); EQ(p1, hf ? 3 : pal, x + 8, by, hf, vf, z);
                int fx = hf ? x + 8 : x;
                EQ(0xC1, 3, fx, by - 16, hf, vf, z);
                static const uint8_t foot[6] = {0xC7, 0xC9, 0xC7, 0xF9, 0xFB, 0xF9};
                int fi = 3 * (f & 1) + hf;
                EQ(foot[fi], 3, x, by + 16, hf, vf, z); EQ(foot[fi + 1], 3, x + 8, by + 16, hf, vf, z);
                if (o->id == OBJ_PARATROOPAGREENHOP) EQ(((o->var5 + 3) & 4) ? 0xCF : 0xCD, 1, hf ? x : x + 8, by - 8, hf, vf, z);
            } else {                              /* the shell (Object_DrawShelled: frame 2 mirrored; kicked: frames 4-6, mirrored but for 6) */
                f = f < 2 ? 2 : f > 6 ? 6 : f;
                pair_quads(TROOPA[f], pal, x, y, o->flip, f != 6, z); used += 2;
                if ((o->state == OS_SHELLED || o->state == OS_HELD) && o->timer3 < 0x50) {
                    /* (waking: the feet out, $F9 PAL3, 10 below - above, upside down - 3 out each
                       side, when Timer3 hits PRG000_CAF1's bit for its sixteenth) */
                    static const uint8_t mask[6] = {2, 2, 4, 8, 16, 16};
                    if (o->timer3 & mask[o->timer3 >> 4]) {
                        int vf = (o->flip & SPR_VFLIP) != 0, fy = y + (vf ? -10 : 10);
                        EQ(0xF9, 3, x - 3, fy, 0, vf, z); EQ(0xF9, 3, x + 11, fy, 1, vf, z);
                    }
                }
            }
        }
        #undef EQ
        while (used < OBJ_QUADS) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); used++; }
    }
    eh_fx = eh_fy = 0;
    for (int k = 0; k < NFIRE; k++) {            /* the fireballs: $65 / $67, the 3rd and 4th turned; left by X velocity */
        if (!fire[k].on) { quad(0, 0, 0, 0, 0, 0, 0, 0, 0); continue; }
        int a = (fire[k].var1 >> 2) & 3, turn = a >= 2, hf = turn ^ (fire[k].xvel < 0);
        eh_quad(a & 1 ? 0x67 : 0x65, 1, fire[k].x, fire[k].y, hf, turn, z_all);
    }
}
/* (level_load) the halves into the atlas, two to a slot, from the sprite banks as 1-1 has them */
static void eh_render(int *slot, const uint8_t *chr, uint32_t nchr, const uint8_t *ram) {
    eh_slot0 = *slot;
    for (int f = 0; f < NEH; f++) {
        int sl = *slot + (f >> 1), xo = (f & 1) * 8; uint8_t n = EH_PAT[f];
        if (sl >= (TEX_H_MAX / 16) * 16) continue;                      /* (no room left in the texture) */
        for (int y = 0; y < 16; y++) {
            uint16_t a = (uint16_t)((n & 1) * 0x1000 + ((n & 0xFE) + (y >> 3)) * 16 + (y & 7));
            uint8_t bank = a >= 0x1000 ? ram[0x71B + ((a - 0x1000) >> 10)] : (uint8_t)((ram[0x719 + (a >> 11)] & 0xFE) | ((a >> 10) & 1));
            if (f >= NEH - 3 && a >= 0x1000 && ((a - 0x1000) >> 10) == 2) bank = 0x0E;   /* (the platforms: ObjectGroup_PatTableSel OPTS_SETPT5 | $0E - SMB3 sets PatTable_BankSel+4 for them as they run) */
            const uint8_t *c = chr + (size_t)(bank % nchr) * 0x400 + (a & 0x3FF);
            for (int x = 0; x < 8; x++) {
                int p = ((c[0] >> (7 - x)) & 1) | (((c[8] >> (7 - x)) & 1) << 1);
                atlas[((sl / 16) * 16 + y) * 256 + (sl % 16) * 16 + xo + x] = p ? ppu_rgb(ppu_peek_pal(16 + EH_PAL[f] * 4 + p)) : 0;
            }
        }
    }
    *slot += (NEH + 1) / 2;
}

/* the messages' letters (Video_CourseClear / Video_YouGotCard: tiles $80-$A8 of BG bank $5E, set
   at the goal as PatTable_BankSel+1), 8 x 8, a slot row of the atlas */
static const uint8_t GL_TILES[] = {0x80, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x89, 0x8A, 0x8B, 0x8D, 0x8E, 0x9B, 0xA0, 0xA1, 0xA2, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8};
#define NGL ((int)sizeof GL_TILES)
static int gl_row;
static void glyph_render(int *slot, const uint8_t *chr, uint32_t nchr) {
    *slot = (*slot + 15) / 16 * 16; gl_row = (*slot / 16) * 16;
    if (gl_row + 8 > TEX_H_MAX) { rt_log("smb3", "goal: no room for the letters"); gl_row = 0; return; }
    for (int g = 0; g < NGL; g++) for (int y = 0; y < 8; y++) {
        uint16_t a = (uint16_t)(GL_TILES[g] * 16 + y);
        uint8_t bank = (uint8_t)((0x5E & 0xFE) | ((a >> 10) & 1));
        const uint8_t *c = chr + (size_t)(bank % nchr) * 0x400 + (a & 0x3FF);
        for (int x = 0; x < 8; x++) {
            int p = ((c[0] >> (7 - x)) & 1) | (((c[8] >> (7 - x)) & 1) << 1);
            static const uint8_t col[4] = {0, 0x0F, 0x10, 0x30};   /* (black, grey, white over the sky) */
            atlas[(gl_row + y) * 256 + g * 8 + x] = p ? ppu_rgb(col[p]) : 0;
        }
    }
    *slot += 16;
}
static int gl_of(uint8_t t) { for (int g = 0; g < NGL; g++) if (GL_TILES[g] == t) return g; return -1; }
/* (from sb_draw: screen space - the bar's left bx, the screen's top y0, units per SMB3 pixel sc) */
static void goal_msg_draw(ppc_context *ctx, uint8_t *base, float bx, float y0, float sc) {
    if (!goal.msg) return;
    static const uint8_t L1[] = {0x85, 0x8E, 0x8A, 0x82, 0x83, 0x84, 0xFC, 0x85, 0x8B, 0x84, 0x80, 0x82, 0xFC, 0x9B};   /* COURSE CLEAR ! at $2889 */
    static const uint8_t L2[] = {0x8D, 0x8E, 0x8A, 0xFC, 0x86, 0x8E, 0x89, 0xFC, 0x80, 0xFC, 0x85, 0x80, 0x82, 0x87, 0xFC, 0xA6, 0xFE, 0xFE, 0xA7};   /* at $28E7 */
    static const uint8_t BOXT[] = {0xA0, 0xA1, 0xA1, 0xA2}, BOXM[] = {0xA6, 0xFE, 0xFE, 0xA7}, BOXB[] = {0xA8, 0xA4, 0xA4, 0xA5};
    struct { const uint8_t *t; int n, col, row; } line[5] = {{L1, 14, 9, 4}, {L2, goal.msg >= 2 ? 19 : 0, 7, 7}, {BOXT, goal.msg >= 2 ? 4 : 0, 22, 6}, {BOXM, goal.msg >= 2 ? 4 : 0, 22, 8}, {BOXB, goal.msg >= 2 ? 4 : 0, 22, 9}};
    int nq = 0; for (int k = 0; k < 5; k++) for (int i = 0; i < line[k].n; i++) nq += gl_of(line[k].t[i]) >= 0;
    if (goal.msg >= 2) nq += 2;
    gcall(ctx, base, A_GXLoadTexObj, 2, SM_TEXOBJ, 0);
    gcall(ctx, base, A_GXBegin, 3, 0x80, 0, 4 * nq);
    for (int k = 0; k < 5; k++) for (int i = 0; i < line[k].n; i++) {
        int g = gl_of(line[k].t[i]); if (g < 0) continue;
        float x = bx + (line[k].col + i) * 8 * sc, y = y0 - line[k].row * 8 * sc;
        float u0 = g * 8 / 256.0f, v0 = gl_row / (float)tex_h;
        quad(x, y, x + 8 * sc, y - 8 * sc, pz, u0, v0, u0 + 8 / 256.0f, v0 + 8 / (float)tex_h);
    }
    if (goal.msg >= 2) {                         /* (the card in the box: its picture) */
        static const uint8_t cp[3] = {0x51, 0x53, 0x55}; static const int cpal[3] = {1, 2, 1};
        int f = goal.kind - 1, h = eh_of(cp[f], cpal[f]), sl = eh_slot0 + (h >> 1);
        float u0 = (sl % 16) * 16 / 256.0f + (h & 1) * 8 / 256.0f, v0 = (sl / 16) * 16 / (float)tex_h, u1 = u0 + 8 / 256.0f, v1 = v0 + 16 / (float)tex_h;
        float x = bx + 23 * 8 * sc, y = y0 - 7 * 8 * sc;
        quad(x, y, x + 8 * sc, y - 16 * sc, pz, u0, v0, u1, v1);
        quad(x + 8 * sc, y, x + 16 * sc, y - 16 * sc, pz, u1, v0, u0, v1);
    }
}
