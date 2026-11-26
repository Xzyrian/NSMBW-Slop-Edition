/* smb3_stage_frog.inc - SMB3's Frog suit on the NSMBW players (included by smb3_stage.c).
 *
 * The suit: the Frog power-up state, PU_FROG (rt_powerup.h; POWERUPS.md) - got with NSMBW's own
 * change. Mario shows the Frog's own model: a second player model beside his own, built from
 * game/mod/characters/smb3/frog_mario.brres (models/tools/build_smb3_brres.py --frog), shown
 * while he is a Frog (runtime/rt_charmdl.c); his own model file and its Penguin are untouched.
 * Other characters show their Super look for now. Its idle: F_wait (the user's pose,
 * tools/nsmb2_anims.py from models/frog/frog_idle_pose.json) in place of the game's wait.
 * The item: SMB3's Starman object with frame 2 (PUp_StarOrSuitFrames: Star, Tanooki, Frog, Hammer)
 * - pattern $91 drawn mirrored (ObjP0C), palette SPR_PAL2 (Star_Palettes), from CHR bank $4C (the
 * suits' bank, which SMB3 loads for its big ? blocks: OPTS_SETPT5 | $4C); it moves as the star
 * (ObjNorm_StarOrSuit: bounces), and taking it is ObjHit_StarOrSuit's: the suit at once, whatever
 * the player's size (Player_QueueSuit, the poof).
 * The block (user, 2026-11-26): a ? block with the Frog suit in 1-1 (W101L, Level_LayPtrOrig
 * $BB82), 4 rows above the ground, the first free column 6 or more right of the start.
 * The Raccoon's flying hands are here too (hands_anchor, below): both use the SMB3 stage's own
 * model files.
 * Testing: SMB3_STAGE_FROG_BLOCK=col,row puts it there (in any level). Not yet: the Frog's moves
 * (SMB3's hops on land, its swimming), Luigi's and the Toads' Frog models. */
#define MDL_CUR_MODEL       0x770                /* dPlayerMdl_c: the model shown (0 big, 1 small, 2 propeller, 3 penguin) */
#define MDL_PLAYER_MODE     0x152                /* u8 dPlayerMdl_c::mPlayerMode */
#define MDL_RES_MODEL       0x20C                /* the model's ResFile */
#define MDLIDX_PENGUIN      3
#define VT_SET_PLAYER_MODE  0x30                 /* dPlayerMdl_c::setPlayerMode(mode) */
#define PMODE_PENGUIN       5
#define ANM_WAIT            0                    /* (the game's player animation table: wait; and waitL 135, waitR 136 / 144 - what the stage asks for, by the facing) */
static int anm_is_wait(uint32_t id) { return id == ANM_WAIT || id == 135 || id == 136 || id == 144; }
#define MDL_CUR_ANM         0x154                /* dPyMdlBase_c: the animation playing (setAnm's id) */
extern const int smb3_frog_wait_ok;              /* (tools/nsmb2_anims.py: F_wait is in the archive) */
uint32_t rt_charmdl_frog_res(void);              /* rt_charmdl.c: the Frog model file (0: none) */

static struct { int on, chg; uint32_t mdl; } fr[8];
static struct { int on, tx, ty; } fb;            /* (the Frog suit's ? block) */
static int frog_on(int n) { return n >= 0 && n < 8 && fr[n].on; }   /* (the player's power-up is PU_FROG: frog_anchor keeps fr[].on with it) */
static void frog_set(int n, int on) {
    if (n < 0 || n > 7 || fr[n].on == on) return;
    fr[n].on = on; rt_log("smb3", "player %d: Frog %s", n + 1, on ? "on" : "off");
}
static void frog_reset(void) { memset(fr, 0, sizeof fr); }
/* (rt_charmdl.c, dPlayerMdl_c::loadResources: Mario's model file is the Frog one while this is set) */
int smb3_stage_frog_model(void) { return active; }

/* the block: placed when 1-1 is loaded (level_load) */
static void frog_level_loaded(const uint8_t *ram, const uint8_t *wram) {
    fb.on = 0;
    const char *e = getenv("SMB3_STAGE_FROG_BLOCK"); int tc, tr;
    if (e && sscanf(e, "%d,%d", &tc, &tr) == 2 && tc >= 0 && tc < L.w && tr >= 0 && tr < LH) {
        L.tile[tr * L.w + tc] = T_QSTAR; fb.on = 1; fb.tx = tc; fb.ty = tr;
        rt_log("smb3", "frog: the Frog suit block at column %d row %d (SMB3_STAGE_FROG_BLOCK)", tc, tr); return;
    }
    if (ram[0x70A] != 1 || ram[0x727] != 0 || wram[0x7EB9 - 0x6000] != 0x82 || wram[0x7EBA - 0x6000] != 0xBB) return;   /* (1-1: World 1, tileset 1, W101L) */
    int c0 = (L.sx + 8) / 16;
    for (int c = c0 + 6; c < c0 + 60 && c < L.w - 1; c++) {
        int g = -1;
        for (int r = 1; r < LH; r++) if (tile_class(L.tile[r * L.w + c]) == 2) { g = r; break; }   /* (the ground: the first solid tile from the top) */
        if (g < 7) continue;
        int ty = g - 4, ok = 1;
        for (int r = ty - 2; r < g && ok; r++)                           /* (free around it: room to jump and to stand under it) */
            for (int dc = -1; dc <= 1; dc++) { uint8_t t = L.tile[r * L.w + c + dc]; if (tile_class(t) || is_block(t) || is_note(t) || t == T_COIN) { ok = 0; break; } }
        if (!ok) continue;
        L.tile[ty * L.w + c] = T_QSTAR; fb.on = 1; fb.tx = c; fb.ty = ty;
        rt_log("smb3", "frog: the Frog suit block in 1-1 at column %d row %d (ground row %d; start column %d)", c, ty, g, c0);
        return;
    }
    rt_log("smb3", "frog: no room found for the Frog suit block in 1-1");
}
/* (hit_block) this block gives the Frog suit: once */
static int frog_block_take(int tx, int ty) {
    if (!fb.on || fb.tx != tx || fb.ty != ty) return 0;
    fb.on = 0; return 1;
}

/* ObjHit_StarOrSuit with the Frog: the suit at once, whatever the player's size - the Frog power-up state */
static void frog_touch(ppc_context *ctx, uint8_t *base, uint32_t pl, int n, int mode) {
    if (mode == PU_FROG) return;                                         /* (already Frog: PowerUp_PlaySound only) */
    if (retro_is_player(pl)) { set_powerup_now(ctx, base, pl, PU_FROG); poof_start(n, pl); }   /* (an NES character: SMB3's poof) */
    else gcall(ctx, base, A_CHANGE_POWERUP, 2, pl, PU_FROG);           /* (an NSMBW character: NSMBW's own change) */
}
static int frog_powerdown(uint32_t pl, uint32_t *powerup) { (void)pl; (void)powerup; return 0; }   /* (smb3_stage_powerdown: every suit) */
static int frog_shown(int n) { return fr[n].mdl && rt_pu_mdl_get(fr[n].mdl) != 0xFFFFFFFFu ? rt_pu_mdl_get(fr[n].mdl) == PU_FROG : fr[n].on; }
/* ---- the Raccoon's flying hands (user, 2026-11-26) ----
 * NSMB2 opens the Raccoon's hands while it flies and while its tail slows a fall. The SMB3 stage's
 * model files (game/mod/characters/smb3/mario.brres, luigi.brres; models/tools/build_smb3_brres.py
 * --raccoon, from models/raccoon/<who>/<who>_Raccoon.glb) give Super's body model (MB_model /
 * LB_model) three more objects, each drawn under a node of its own so that it can be shown on its
 * own: the Raccoon's body (leg_l2), its fists (leg_r1) and its open hands (leg_r2); Super's body
 * stays under leg_l1. The nodes only switch objects on and off (the parts are skinned to the arm
 * and body bones as the body is). Each frame: a Raccoon shows its body with the open hands while
 * it flies or flutters (RA_FLY / RA_FLY2 / RA_FLY_ST / RA_FALL; with something held, NSMB2's
 * _carry flight, the fists) and while it runs at full P-speed (the P-run, RA_PRUN = T_b_dash2,
 * playing; user, 2026-11-26), else with the fists; anyone else, Super's body. A node is shown by its
 * ResNode flag 0x100 (+0x14) and, when the model keeps copied visibility bytes (ScnMdl +328; one
 * byte a node), by its byte there too, with the model's +316 bit 1 set (what ScnMdl's own
 * CopiedVisAccess does, 0x8025C8E0). */
#define VT_SCNMDL           0x8034E8F0u          /* nw4r::g3d::ScnMdl's vtable (ScnMdl::Construct, 0x8025D4E8) */
#define VT_SCNMDL_SIMPLE    0x8034E8A8u          /* ScnMdlSimple's (its constructor 0x8025C030) */
#define MDL_BODY0           0x468                /* dPlayerMdl_c: the big body's m3d::mdl_c (its ScnMdl at +4) */
#define SCN_RESMDL          0xE8                 /* ScnMdlSimple: the ResMdl */
#define SCN_VIS_DIRTY       316
#define SCN_VIS_BYTES       328
enum { HN_SUPER, HN_RACCOON, HN_FISTS, HN_OPEN, NHN };
static const char *const hand_node_name[NHN] = { "leg_l1", "leg_l2", "leg_r1", "leg_r2" };
static struct { uint32_t resmdl; int ok; uint32_t node[NHN]; int id[NHN]; } hand_res[4];

static int g_streq(uint32_t a, const char *s) { for (; *s; s++, a++) if (R8(a) != (uint8_t)*s) return 0; return R8(a) == 0; }
/* (a resource dictionary's entry by name: its data's address, 0 when none) */
static uint32_t g_dict_find(uint32_t dict, const char *name) {
    uint32_t n = R32(dict + 4); if (n > 512) return 0;
    for (uint32_t i = 1; i <= n; i++) {
        uint32_t e = dict + 8 + 16 * i;
        if (g_streq(dict + (uint32_t)(int32_t)R32(e + 8), name)) return dict + (uint32_t)(int32_t)R32(e + 12);
    }
    return 0;
}
/* this ResMdl's four nodes, when it has the Raccoon's parts (one of our files) */
static int hand_nodes(uint32_t resmdl) {
    int k, freei = -1;
    for (k = 0; k < 4; k++) { if (hand_res[k].resmdl == resmdl) return k; if (!hand_res[k].resmdl && freei < 0) freei = k; }
    if (freei < 0) { memset(hand_res, 0, sizeof hand_res); freei = 0; }
    k = freei; hand_res[k].resmdl = resmdl; hand_res[k].ok = 0;
    uint32_t bones = R32(resmdl + 0x10 + 4) ? resmdl + (uint32_t)(int32_t)R32(resmdl + 0x10 + 4) : 0;
    uint32_t objs = R32(resmdl + 0x10 + 4 * 10) ? resmdl + (uint32_t)(int32_t)R32(resmdl + 0x10 + 4 * 10) : 0;
    if (!bones || !objs || !g_dict_find(objs, "raccoon_open_hands")) return k;
    for (int i = 0; i < NHN; i++) {
        uint32_t nd = g_dict_find(bones, hand_node_name[i]); if (!nd) return k;
        hand_res[k].node[i] = nd; hand_res[k].id[i] = (int)R32(nd + 0x0C);
    }
    hand_res[k].ok = 1;
    rt_log("smb3", "hands: the Raccoon's parts in the model at %08X (nodes %d %d %d %d)", resmdl, hand_res[k].id[0], hand_res[k].id[1], hand_res[k].id[2], hand_res[k].id[3]);
    return k;
}
static void hand_vis(uint32_t scn, uint32_t vis, uint32_t node, int id, int on) {
    uint32_t f = R32(node + 0x14), nf = on ? (f | 0x100u) : (f & ~0x100u);
    if (nf != f) W32(node + 0x14, nf);
    if (vis && (R8(vis + (uint32_t)id) != 0) != on) { W8(vis + (uint32_t)id, on ? 1 : 0); W32(scn + SCN_VIS_DIRTY, R32(scn + SCN_VIS_DIRTY) | 1u); }
}
static void hands_anchor(int n, uint32_t mdl) {
    uint32_t scn = R32(mdl + MDL_BODY0 + 4); if (!scn) return;
    uint32_t vt = R32(scn); if (vt != VT_SCNMDL && vt != VT_SCNMDL_SIMPLE) return;
    uint32_t resmdl = R32(scn + SCN_RESMDL); if (!resmdl) return;
    int k = hand_nodes(resmdl); if (!hand_res[k].ok) return;
    uint32_t vis = vt == VT_SCNMDL ? R32(scn + SCN_VIS_BYTES) : 0;
    int raccoon = RC_SHOWN(n), h = rc[n].hold;
    int prun = ra_ready > 0 && R32(mdl + MDL_CUR_ANM) == ra_id0 + (uint32_t)RA_PRUN;   /* (the P-run, T_b_dash2: at full P-speed) */
    int open = raccoon && (h == RA_FLY || h == RA_FLY2 || h == RA_FLY_ST || h == RA_FALL || prun);
    int on[NHN] = { !raccoon, raccoon, raccoon && !open, open };
    for (int i = 0; i < NHN; i++) hand_vis(scn, vis, hand_res[k].node[i], hand_res[k].id[i], on[i]);
    static int was[8] = { -1, -1, -1, -1, -1, -1, -1, -1 }; int st = raccoon + open;
    if (st != was[n]) { was[n] = st; rt_log("smb3", "player %d: body %s", n + 1, open ? (prun && h < 0 ? "Raccoon, open hands (P-run)" : "Raccoon, open hands") : raccoon ? "Raccoon, fists" : "Super"); }
}
/* each player, each frame (with raccoon_anchor): the model's slot, the idle animation */
static void frog_anchor(ppc_context *ctx, uint8_t *base, uint32_t pl) {
    int n = (int8_t)R8(pl + PL_PLR_NO); if (n < 0 || n > 7) return;
    frog_set(n, R32(pl + PL_MODE) == PU_FROG);                           /* (the suit: the player's power-up) */
    fr[n].mdl = 0;
    if (retro_is_player(pl)) return;
    uint32_t mdl = R32(R32(pl + 3560) + 4); if (!mdl) return;
    hands_anchor(n, mdl);                                                /* (the Raccoon's body and hands: Super's body model's nodes) */
    /* (the Frog's model: its own, a model slot of its own - POWERUPS.md; until then the power-up's
       base model, Super's) */
    if (!fr[n].on) return;
    fr[n].mdl = mdl;
    raccoon_anims_init(ctx, base);
    if (ra_ready > 0 && !getenv("SMB3_STAGE_NO_MERGE")) { uint32_t f = R32(mdl + MDL_RES_ANIM), m = anm_merged(ctx, base, f); if (m && f != m) W32(mdl + MDL_RES_ANIM, m); }   /* (F_wait: the model's own now) */
    /* (the game's wait already playing - the suit put on while standing: setAnm only asks again
       on a change, so F_wait is started here) */
    if (ra_ready > 0 && smb3_frog_wait_ok && frog_shown(n) && anm_is_wait(R32(mdl + MDL_CUR_ANM))) {
        ppc_fpr f1 = ctx->f[1], f2 = ctx->f[2], f3 = ctx->f[3];
        ctx->f[1].d = ctx->ps1[1] = 1.0; ctx->f[2].d = ctx->ps1[2] = 6.0; ctx->f[3].d = ctx->ps1[3] = 0.0;
        gcall(ctx, base, A_START_ANIM, 2, mdl, ra_id0 + (uint32_t)RA_F_WAIT);
        ctx->f[1] = f1; ctx->f[2] = f2; ctx->f[3] = f3;
        static int logged; if (logged++ < 20) rt_log("smb3", "player %d: Frog idle (F_wait, id %u) - the game's wait was playing; now %u", n + 1, ra_id0 + (uint32_t)RA_F_WAIT, R32(mdl + MDL_CUR_ANM));
    }
}
/* (smb3_stage_anim) a Frog player's wait is F_wait; -1: not ours */
static int frog_anim(ppc_context *ctx, uint8_t *base) {
    uint32_t mdl = ctx->r[3], id = ctx->r[4];
    int n = -1; for (int i = 0; i < 8; i++) if (fr[i].on && fr[i].mdl == mdl) n = i;
    if (n >= 0) { static uint32_t last = 0xFFFFFFFFu; if (id != last) { last = id; rt_log("smb3", "player %d: Frog - the game asks for animation %u%s", n + 1, id, anm_is_wait(id) ? " (a wait: F_wait instead)" : ""); } }
    if (n < 0 || !anm_is_wait(id) || !smb3_frog_wait_ok) return -1;
    if (R32(mdl + MDL_CUR_ANM) == ra_id0 + (uint32_t)RA_F_WAIT) return 1;   /* (playing already: the stage asks every frame) */
    ctx->r[4] = ra_id0 + (uint32_t)RA_F_WAIT;
    { uint32_t f = R32(mdl + MDL_RES_ANIM); for (int i = 0; i < nmg; i++) if (mg[i].dst == f) return 0; }   /* (merged: the game plays it as its own) */
    ra_play(ctx, base); return 1;
}
