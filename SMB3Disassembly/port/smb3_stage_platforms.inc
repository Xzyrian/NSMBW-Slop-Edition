/* smb3_stage_platforms.inc - SMB3's platforms in the stage (included by smb3_stage_enemies.inc).
 *
 * The log / wooden platforms of prg002, ported from their routines: ObjInit_WoodenPlat /
 * _WoodenPlatform / _OscillatingShort / _WoodenFallingPlat / _FallingPlatform, ObjNorm_
 * WoodenPlatRider ($26), _OscillatingH ($27 long, $37 short; Platform_Oscillate), _OscillatingV
 * ($28, $38), _WoodenPlatform ($36: drifts left, falls once stood on - 1-4), _PathFollowPlat ($3C
 * moving from the start, $44 once stood on: along the level's path tiles, reversed by the
 * "platform puller", falling where the path ends - 1-6). Drawn as SMB3 draws them (LogPlat_Draw:
 * ObjP36's $8F $9D $9D $9D $9D $9F, 8 x 16 each, palette 3).
 *
 * SMB3's own collision (PlayerPlatform_Collide) is for its one Player; the NSMBW players stand on
 * the platform through NSMBW's own rideable line (RideableActorCollider, as NSMBW's lifts have
 * it): its top edge, moving with the platform, carrying whoever stands on it. "Stood on" for
 * SMB3's logic (the carry PlayerPlatform_Collide returns) is that line's riders. The line needs
 * an actor to belong to: one DUMMY_ACTOR (a dStageActor_c doing nothing), the lines placed in the
 * world about it. */

static void eh_quad(uint8_t pat, int pal, int x, int y, int hf, int vf, float z);
static float eh_fx, eh_fy;                      /* (smb3_stage_enemies.inc) */

/* -- NSMBW's side: the rideable lines -- */
#define A_ACTOR_CREATE    0x80064610u           /* dStageActor_c::create(profile, settings, pos, rot, layer) */
#define A_FBASE_SEARCH    0x80162D00u           /* fBase_c::search(id): the base, or 0 */
#define A_RIDE_CT         0x800DB450u           /* RideableActorCollider::RideableActorCollider() */
#define A_RIDE_INIT       0x800DB530u           /* RideableActorCollider::init(owner, x1, y1, x2, y2): relative to the owner */
#define A_RIDE_SETPOS     0x800DB5F0u           /* RideableActorCollider::setPosition(x1, y1, x2, y2) */
#define A_COL_ADD         0x800DAE80u           /* BasicCollider::addToList */
#define A_COL_REMOVE      0x800DAED0u           /* BasicCollider::removeFromList */
#define PROF_DUMMY_ACTOR  0x2EB
#define SM_PLAT_COL       (SM_MEM + 0x3FA00)    /* (NOBJ lines, 96 bytes each) */
#define SM_PLAT_POS       (SM_MEM + 0x3FD00)    /* (the host's position, angle; 0x3FC00 is the map's GXTexObj) */
#define PLAT_W            48                    /* (OA1_WIDTH48) */
static struct { int on; } pcol[NOBJ];
static uint32_t plat_host, plat_host_id;
static int plat_host_tries;

static void plat_col_off(int i) {
    if (!pcol[i].on) return;
    gcall(blk_ctx, blk_base, A_COL_REMOVE, 1, SM_PLAT_COL + 96u * (uint32_t)i);
    pcol[i].on = 0;
}
/* all lines out of NSMBW's list - a stage ending, the level starting again (the list isn't
   cleared between stages: a line left in it would be read with its stage gone) */
static void plats_off(void) {
    if (!blk_ctx) { memset(pcol, 0, sizeof pcol); plat_host = 0; return; }
    for (int i = 0; i < NOBJ; i++) plat_col_off(i);
    plat_host = 0; plat_host_tries = 0;
}
static int plat_host_ok(void) {
    if (plat_host && gcall(blk_ctx, blk_base, A_FBASE_SEARCH, 1, plat_host_id) == plat_host) return 1;
    if (plat_host) { rt_log("smb3", "platforms: the host actor went - its lines off"); for (int i = 0; i < NOBJ; i++) plat_col_off(i); plat_host = 0; }
    if (plat_host_tries >= 3) return 0;
    plat_host_tries++;
    WF(SM_PLAT_POS, L.lx); WF(SM_PLAT_POS + 4, -L.ly); WF(SM_PLAT_POS + 8, 0);
    W32(SM_PLAT_POS + 12, 0); W32(SM_PLAT_POS + 16, 0);
    plat_host = gcall(blk_ctx, blk_base, A_ACTOR_CREATE, 5, PROF_DUMMY_ACTOR, 0, SM_PLAT_POS, SM_PLAT_POS + 12, 0);
    if (!plat_host) { rt_log("smb3", "platforms: no host actor"); return 0; }
    plat_host_id = R32(plat_host);
    rt_log("smb3", "platforms: host actor %08X (id %u)", plat_host, plat_host_id);
    return 1;
}
/* the platform's top edge, in the world about the host (x level pixels, y its top) */
static void plat_col_place(int i, double x, double y, int init) {
    uint32_t c = SM_PLAT_COL + 96u * (uint32_t)i;
    float ox = RF(plat_host + PL_POS), oy = RF(plat_host + PL_POS + 4);
    double x1 = L.lx + x - ox, x2 = L.lx + x + PLAT_W - ox, y1 = -(L.ly + y) - oy;
    ppc_context *ctx = blk_ctx; ppc_fpr f1 = ctx->f[1], f2 = ctx->f[2], f3 = ctx->f[3], f4 = ctx->f[4];
    ctx->f[1].d = ctx->ps1[1] = x1; ctx->f[2].d = ctx->ps1[2] = y1; ctx->f[3].d = ctx->ps1[3] = x2; ctx->f[4].d = ctx->ps1[4] = y1;
    if (init) gcall(ctx, blk_base, A_RIDE_INIT, 2, c, plat_host);
    else gcall(ctx, blk_base, A_RIDE_SETPOS, 1, c);
    ctx->f[1] = f1; ctx->f[2] = f2; ctx->f[3] = f3; ctx->f[4] = f4;
}
static void plat_col_on(int i, obj_t *o) {
    if (pcol[i].on || !plat_host_ok()) return;
    uint32_t c = SM_PLAT_COL + 96u * (uint32_t)i;
    for (uint32_t k = 0; k < 96; k += 4) W32(c + k, 0);
    gcall(blk_ctx, blk_base, A_RIDE_CT, 1, c);
    /* (the layer: a rider's dRc_c (+50) must match it, +69 its kinds (+46) - NSMBW's own actors
       take a global's layer (0x80429D28) as they're created, which holds the layer of the actor being created; ours
       are made outside that, so the players' own: dAcPy_c's dRc_c at +732) */
    {   uint32_t pl = 0; for (int n = 0; n < 8 && !pl; n++) if (pp[n].on) pl = pp[n].pl;
        uint8_t layer = pl ? R8(pl + 732 + 50) : 0;
        W8(c + 74, layer); }
    W8(c + 69, 3);                                                       /* (as NSMBW's own lines: fn_3_13910's box) */
    plat_col_place(i, o->x + o->xfrac / 16.0, o->y + o->yfrac / 16.0, 1);
    gcall(blk_ctx, blk_base, A_COL_ADD, 1, c);
    pcol[i].on = 1;
}
/* "stood on" since the line last moved (its riders, cleared as it moves them) */
static int plat_ridden(int i) { return pcol[i].on && R32(SM_PLAT_COL + 96u * (uint32_t)i + 16) != 0; }
/* to where the platform is now: the line moves, and its riders with it (its update: vtable +12) */
static void plat_col_move(int i, obj_t *o) {
    if (!pcol[i].on) return;
    uint32_t c = SM_PLAT_COL + 96u * (uint32_t)i;
    plat_col_place(i, o->x + o->xfrac / 16.0, o->y + o->yfrac / 16.0, 0);   /* (with the fractions: moving 1/2 a pixel a frame on a slant, whole pixels jerked the riders and the camera) */
    gcall(blk_ctx, blk_base, R32(R32(c) + 12), 1, c);
    if (getenv("SMB3_PLAT_LOG") && !(counter1 % 30))
        rt_log("smb3", "plat %d (%02X): at (%d, %d) vel (%d, %d) var4 %d var5 %d | line (%.1f, %.1f)-(%.1f, %.1f)", i, o->id, o->x, o->y, o->xvel, o->yvel, o->var4, o->var5, RF(c + 28), RF(c + 32), RF(c + 20), RF(c + 24));
}

/* -- SMB3's side -- */
static void platobj_init(obj_t *o) {
    o->pal = 3;
    switch (o->id) {
    case OBJ_WOODENPLATFORM: o->xvel = -8; /* fall through */             /* ObjInit_WoodenPlatform: X velocity -8 */
    case OBJ_WOODENPLAT_RIDER: case OBJ_OSCILLATING_H: case OBJ_OSCILLATING_V:
    plat_up:
        o->y--; break;                                                     /* ObjInit_WoodenPlat: a pixel higher than placed */
    case OBJ_OSCILLATING_HS: case OBJ_OSCILLATING_VS: o->var4 = 1; goto plat_up;   /* ObjInit_OscillatingShort: the short timer */
    case OBJ_WOODENPLATFORMFALL: o->var4 = 1; /* fall through */          /* ObjInit_WoodenFallingPlat: moving from the start */
    case OBJ_WOODENPLATUNSTABLE: o->x |= 8; o->y |= 6; break;             /* ObjInit_FallingPlatform: centred */
    }
}
/* Platform_Oscillate (on X velocity): a step every other frame once the timer's out, to +-$10, then back */
static void plat_oscillate(obj_t *o) {
    static const int lim[2] = {-0x10, 0x10}, step[2] = {-1, 1}, tset[2] = {0x41, 0x23};   /* OscXVelLimit, OscXVel, OscTimerSets */
    if (o->timer || (counter1 & 1)) return;
    int y = o->var5 & 1;
    o->xvel += step[y];
    if (o->xvel == lim[y]) { o->var5 = y ^ 1; o->timer = tset[o->var4 & 1]; }
}
/* ObjNorm_PathFollowPlat: at a tile's middle, the four tiles about the platform's middle
   (Object_DetectTile, TDO group 9: (4, $14) (4, $1C) ($C, $14) ($C, $1C)); the next path tile from
   the way it goes, straight on first; none: it stops, then falls */
static void plat_pathfollow(obj_t *o, int ridden) {
    static const int8_t scan[13] = {-6, 6, -5, 5, -4, 4, -3, 3, -2, 2, -1, 1, 0};   /* WoodenPlat_ScanIndices */
    static const uint8_t next[16] = {3, 2, 2, 2, 2, 0, 0, 0, 1, 1, 1, 1, 3, 3, 3, 3};   /* WoodenPlat_NextTileIdx */
    static const uint8_t path[16] = {0xC9, 0xCF, 0xCE, 0xCB, 0xC8, 0xCA, 0xCD, 0xCC, 0xC9, 0xCE, 0xCF, 0xCB, 0xC8, 0xCA, 0xCC, 0xCD};   /* WoodenPlat_PathTiles (TILEA_PATH_*) */
    static const uint8_t path2[16] = {0x0A, 0x10, 0x0F, 0x0C, 0x09, 0x0B, 0x0E, 0x0D, 0x0A, 0x0F, 0x10, 0x0C, 0x09, 0x0B, 0x0D, 0x0E};   /* WoodenPlat_PathTilesAlt (TILE2_PATH_*) */
    static const int8_t yv[17] = {-0x10, -0x10, -0x10, -0x10, 0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0, -0x10, -0x10, -0x10, 0};   /* WoodenPlat_YVel */
    static const int8_t xv[17] = {0, 8, 8, 0x10, 0x10, 0x10, 8, 8, 0, -8, -8, -0x10, -0x10, -0x10, -8, -8, 0};                     /* WoodenPlat_XVel */
    if (o->var4 >= 2) o->yvel++;                                          /* (the path ended: falling) */
    else if (o->var4 == 1 && (o->yvel ? (o->y & 15) == 6 : (o->x & 15) == 8)) {
        int t[4];                                                          /* Temp_Var9..12 */
        static const int dy[4] = {0x0C, 0x0C, 0x04, 0x04}, dx[4] = {0x1C, 0x14, 0x1C, 0x14};
        for (int k = 0; k < 4; k++) {
            int tx = (o->x + dx[k]) >> 4, ty = (o->y + dy[k]) >> 4;
            t[k] = (tx >= 0 && tx < L.w && ty >= 0 && ty < LH) ? L.tile[ty * L.w + tx] : 0;
        }
        int dir = o->var5 & 15, got = -1;
        for (int s = 12; s >= 0 && got < 0; s--) {
            int y = (scan[s] + dir) & 15, tile = t[next[y]];
            if (tile == path[y] || tile == path2[y]) got = y;
            else if (y == dir && tile == 0xD0) got = y ^ 8;               /* (TILE4_PLATFORMPULLER straight ahead: back the other way) */
        }
        if (got < 0) { o->var4++; got = 16; }                             /* (no path: stop) */
        else o->var5 = got;
        o->xvel = xv[got]; o->yvel = yv[got];
    }
    apply_yvel(o); apply_xvel(o);
    if (ridden) o->var4 |= 1;                                             /* (stood on: it goes) */
}
static void plat_frame(obj_t *o, int i) {
    plat_col_on(i, o);
    int ridden = plat_ridden(i);
    {   static int was[NOBJ]; if (ridden != was[i] && getenv("SMB3_PLAT_LOG")) { was[i] = ridden; rt_log("smb3", "platform %d (%02X) at (%d, %d): %s", i, o->id, o->x, o->y, ridden ? "stood on" : "left"); } }
    switch (o->id) {
    case OBJ_WOODENPLAT_RIDER:                                            /* ObjNorm_WoodenPlatRider: speeds up to $10 every other frame once ridden */
        apply_xvel(o);
        if (o->xvel) { if (o->xvel != 0x10 && !(counter1 & 1)) o->xvel++; }
        else if (ridden) o->xvel++;
        break;
    case OBJ_OSCILLATING_H: case OBJ_OSCILLATING_HS:
        plat_oscillate(o); apply_xvel(o); break;
    case OBJ_OSCILLATING_V: case OBJ_OSCILLATING_VS: {                    /* (the horizontal one's code on its Y velocity) */
        int xv = o->xvel; o->xvel = o->yvel; plat_oscillate(o); o->yvel = o->xvel; o->xvel = xv;
        apply_yvel(o); break; }
    case OBJ_WOODENPLATFORM:                                              /* ObjNorm_WoodenPlatform: stood on, it stops and drops, faster and faster */
        apply_yvel(o); apply_xvel(o);
        if (o->yvel || ridden) { if (!o->yvel) o->xvel = 0; o->yvel++; }
        break;
    case OBJ_WOODENPLATFORMFALL: case OBJ_WOODENPLATUNSTABLE:
        plat_pathfollow(o, ridden); break;
    }
    if (o->yvel > 0x7F) o->yvel = 0x7F;                                   /* (a byte, as SMB3's) */
    plat_col_move(i, o);
}
static void plat_draw(obj_t *o, float z) {                               /* LogPlat_Draw */
    static const uint8_t pat[6] = {0x8F, 0x9D, 0x9D, 0x9D, 0x9D, 0x9F};
    float fx = eh_fx, fy = eh_fy; eh_fx += o->xfrac / 16.0f; eh_fy += o->yfrac / 16.0f;   /* (drawn where its line is: with the fractions) */
    for (int k = 0; k < 6; k++) eh_quad(pat[k], 3, o->x + 8 * k, o->y, 0, 0, z);
    eh_fx = fx; eh_fy = fy;
}
