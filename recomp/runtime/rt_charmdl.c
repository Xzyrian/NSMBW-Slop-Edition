/* rt_charmdl.c - models for the characters that don't have one in the game (docs/CHARACTERS.md).
 *
 * The models come from mods the user put in game/mod/ (tools/import_char_mods.py extracts them
 * to game/mod/characters/<set>/<name>.brres). Each character is still one of the game's player types
 * (its "body", rt_chars.c); here the model a body shows is replaced:
 *
 *   toad/model.brres            all Toad bodies (blue, yellow, black): the Toad addon's Kinopio
 *                               model, whose Black Toad textures are Toadsworth's
 *   rosalina_daisy/model.brres  Daisy on the Orange Toad body, Rosalina on the Purple Toadette
 *   + P_rcha.brres, K_rcha.brres  body (made a Toad-type model): that mod's Kinopio model -
 *                               Daisy in the blue Toad's texture frames, Rosalina in the yellow
 *                               one's - with its own animations (dress / skirt bones)
 *
 * Hooks:
 *   mod_fn_800D6D10  dPyMdlMng_c::construct    - Purple Toadette's body gets a Toad-type model
 *   fn_800D32F0      dPlayerMdl_c::loadResources - its ResFiles (model, P_rcha, own anims) are
 *                                                 pointed at ours
 *   mod_fn_800BCEE0  dKinopioMdl_c::setColorType - texture frames as the mod expects them
 * The brres files are loaded once into guest memory at 0x81C00000+ (below the renderer's
 * texture limit), and when that is full, at the top of MEM2 (0x93700000+: above everything the
 * game and its IOS use - the MEM2 arena ends at 0x93600000, the IOS heap at 0x93620000; the
 * renderer reads MEM2 too); set up like the game's (ResFile::Init + Bind). (User, 2026-11-26:
 * with the Frog's own file loaded first, 0x81C00000-0x82000000 had no room left for
 * smb3/mario.brres, so Mario lost the Raccoon's open hands.) */
#include "rt.h"
#include "rt_powerup.h"
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */

#define MDL_MEM          0x81C00000u
#define MDL_MEM_END      0x82000000u
#define MM_SCRATCH       (MDL_MEM_END - 0x100)
#define MDL_MEM2         0x93700000u   /* (the overflow: MEM2's top, unused - see above) */
#define MDL_MEM2_END     0x94000000u
#define A_RESFILE_INIT   0x8023A590u   /* nw4r::g3d::ResFile::Init() */
#define A_RESFILE_BIND   0x8023A350u   /* nw4r::g3d::ResFile::Bind(ResFile) */
/* model types (dPyMdlMng_c::ModelType_e) */
enum { MT_MARIO, MT_LUIGI, MT_TOAD_BLUE, MT_TOAD_YELLOW, MT_TOAD_RED, MT_YOSHI, MT_TOADETTE, MT_TOADETTE_PURPLE,
       MT_TOAD_BLACK, MT_TOAD_ORANGE };
/* dPlayerMdl_c */
#define PM_CHARA_ID      0x151
#define PM_RES_MODEL     0x20C
#define PM_RES_COMMON    0x210         /* P_rcha */
#define PM_RES_ANIM      0x214         /* K_rcha (Toads) */
#define MNG_MODEL        0x004         /* dPyMdlMng_c::mModel */

#define gcall rt_gcall

typedef struct { const char *file; int state; uint32_t addr; } brres_t;   /* state 0 untried, 1 ok, -1 none */
enum { F_TOAD, F_RD_MODEL, F_RD_PRCHA, F_RD_KRCHA, F_SMB3_MARIO, F_SMB3_LUIGI, F_FROG_MARIO, F_COUNT };
static brres_t files[F_COUNT] = {
    {"toad/model.brres"}, {"rosalina_daisy/model.brres"}, {"rosalina_daisy/P_rcha.brres"}, {"rosalina_daisy/K_rcha.brres"},
    {"smb3/mario.brres"}, {"smb3/luigi.brres"}, {"smb3/frog_mario.brres"},
};
/* the SMB3 mode's model files, for Mario and Luigi while the SMB3 stage runs
   (SMB3Disassembly/port/smb3_stage_frog.inc; models/tools/build_smb3_brres.py --raccoon): the
   character's own file with the Raccoon's body, fists and open hands (NSMB2's, shown while it
   flies) in Super's body model - everything else, the Penguin too, as it is. The Frog has a file
   of its own (frog_mario.brres: a second player model, below) */
int smb3_stage_frog_model(void);
uint32_t rt_charmdl_frog_res(void) { return files[F_SMB3_MARIO].state > 0 ? files[F_SMB3_MARIO].addr : 0; }
static uint32_t mem_next = MDL_MEM;
static uint32_t mem2_next = MDL_MEM2;

static uint32_t brres(ppc_context *ctx, uint8_t *base, int i) {
    brres_t *f = &files[i];
    if (f->state) return f->state > 0 ? f->addr : 0;
    f->state = -1;
    char path[1200]; snprintf(path, sizeof path, "%s/mod/characters/%s", g_root, f->file);
    FILE *fp = fopen(path, "rb"); if (!fp) return 0;
    fseek(fp, 0, SEEK_END); long n = ftell(fp); fseek(fp, 0, SEEK_SET);
    uint32_t at = (mem_next + 31) & ~31u; int hi = 0;
    if (n > 16 && at + (uint32_t)n > MM_SCRATCH) { at = (mem2_next + 31) & ~31u; hi = 1; }   /* (MEM1's part full: MEM2's top) */
    if (n <= 16 || at + (uint32_t)n > (hi ? MDL_MEM2_END : MM_SCRATCH)) { fclose(fp); rt_log("chars", "%s: no room", path); return 0; }
    size_t got = rt_fread_guest(G(at), (size_t)n, fp); fclose(fp);
    if (got != (size_t)n || memcmp(G(at), "bres", 4)) { rt_log("chars", "%s: not a brres", path); return 0; }
    if (hi) mem2_next = at + (uint32_t)n; else mem_next = at + (uint32_t)n;
    /* as the game's resource loader does: ResFile::Init(), then Bind() to itself */
    W32(MM_SCRATCH, at); W32(MM_SCRATCH + 4, at);
    gcall(ctx, base, A_RESFILE_INIT, 1, MM_SCRATCH);
    gcall(ctx, base, A_RESFILE_BIND, 2, MM_SCRATCH, MM_SCRATCH + 4);
    f->addr = at; f->state = 1;
    rt_log("chars", "model file %s: %ld KB at %08X", f->file, n / 1024, at);
    return at;
}
static int have_rd(ppc_context *ctx, uint8_t *base) {
    return brres(ctx, base, F_RD_MODEL) && brres(ctx, base, F_RD_PRCHA) && brres(ctx, base, F_RD_KRCHA);
}

/* dPyMdlMng_c::construct(model type): Purple Toadette's body becomes a Toad-type model when
   Rosalina's model is there (it is built as an Orange Toad model, then given its own id) */
static void frog_construct(ppc_context *ctx, uint8_t *base, uint32_t mng, int type);
void hle_mod_fn_800D6D10(ppc_context *ctx, uint8_t *base) {
    uint32_t mng = ctx->r[3]; int type = (int)(ctx->r[4] & 0xFF);
    if (type != MT_TOADETTE_PURPLE || !have_rd(ctx, base)) { orig_mod_fn_800D6D10(ctx, base); frog_construct(ctx, base, mng, type); return; }
    ctx->r[4] = MT_TOAD_ORANGE;
    orig_mod_fn_800D6D10(ctx, base);
    uint32_t mdl = R32(mng + MNG_MODEL);
    if (mdl) W8(mdl + PM_CHARA_ID, MT_TOADETTE_PURPLE);
}

/* dPlayerMdl_c::loadResources */
void hle_fn_800D32F0(ppc_context *ctx, uint8_t *base) {
    uint32_t mdl = ctx->r[3];
    orig_fn_800D32F0(ctx, base);
    int id = R8(mdl + PM_CHARA_ID);
    int frog_model_of(uint32_t mdl);
    if (frog_model_of(mdl) && brres(ctx, base, F_FROG_MARIO)) {          /* (the Frog's own model: see below) */
        W32(mdl + PM_RES_MODEL, files[F_FROG_MARIO].addr);
    } else if (id == MT_MARIO && smb3_stage_frog_model() && brres(ctx, base, F_SMB3_MARIO)) {
        W32(mdl + PM_RES_MODEL, files[F_SMB3_MARIO].addr);
    } else if (id == MT_LUIGI && smb3_stage_frog_model() && brres(ctx, base, F_SMB3_LUIGI)) {
        W32(mdl + PM_RES_MODEL, files[F_SMB3_LUIGI].addr);
    } else if ((id == MT_TOAD_ORANGE || id == MT_TOADETTE_PURPLE) && have_rd(ctx, base)) {
        /* (only Toad-type models get here as purple: see construct) */
        W32(mdl + PM_RES_MODEL, files[F_RD_MODEL].addr);
        W32(mdl + PM_RES_COMMON, files[F_RD_PRCHA].addr);
        W32(mdl + PM_RES_ANIM, files[F_RD_KRCHA].addr);
    } else if ((id == MT_TOAD_BLUE || id == MT_TOAD_YELLOW || id == MT_TOAD_BLACK) && brres(ctx, base, F_TOAD)) {
        W32(mdl + PM_RES_MODEL, files[F_TOAD].addr);
    }
}

/* dKinopioMdl_c::setColorType: the mod's texture frames are the blue Toad's (Daisy) and the
   yellow Toad's (Rosalina) */
void hle_mod_fn_800BCEE0(ppc_context *ctx, uint8_t *base) {
    uint32_t mdl = ctx->r[3];
    int id = R8(mdl + PM_CHARA_ID);
    if ((id == MT_TOAD_ORANGE || id == MT_TOADETTE_PURPLE) && files[F_RD_MODEL].state > 0
        && R32(mdl + PM_RES_MODEL) == files[F_RD_MODEL].addr) {
        W8(mdl + PM_CHARA_ID, id == MT_TOAD_ORANGE ? MT_TOAD_BLUE : MT_TOAD_YELLOW);
        orig_mod_fn_800BCEE0(ctx, base);
        W8(mdl + PM_CHARA_ID, (uint8_t)id);
        return;
    }
    orig_mod_fn_800BCEE0(ctx, base);
}

/* ---- the Frog's model (the Frog power-up, PU_FROG: rt_powerup.h; SMB3Disassembly/port/POWERUPS.md)
 * A player model (dPlayerMdl_c) has four models - Super, small, Propeller, Penguin - and no room
 * for a fifth. A character with a Frog model (Mario: game/mod/characters/smb3/frog_mario.brres,
 * models/frog) gets a second dPlayerMdl_c beside its own, made and created with it from that file
 * (in which the Frog's body and head are the slot it shows: the Penguin's - that file is the
 * Frog's alone; the character's own file and Penguin are untouched). The player's model manager
 * (dPyMdlMng_c::mModel) points at the Frog's while the model is asked to show the Frog
 * (setPlayerMode(PU_FROG) - NSMBW's change asks for the old and the new by turns), at its own
 * otherwise; the animation playing goes over with it. Both are freed with the manager. */
#define A_MDL_CREATE     0x800D5580u   /* dPyMdlBase_c::create(chara, mode, scene) (fn_800D5580) */
#define A_START_ANIM     0x800D5DD0u   /* dPyMdlBase_c::setAnm(id; f1 rate, f2 blend, f3 frame) */
#define VT_SET_MODE      0x30          /* dPyMdlBase_c::setPlayerMode */
#define MDL_CUR_ANM      0x154         /* the animation playing */
#define FROG_MDL_SLOT    PU_PENGUIN    /* (the Frog file's slot that shows the Frog) */
typedef struct { uint32_t mng, own, frog, scratch; int ready; } frogpair_t;   /* (ready: the Frog's model created too) */
static frogpair_t fp[16];
static frogpair_t *fp_by(uint32_t mdl) { for (int i = 0; i < 16; i++) if (fp[i].mng && (fp[i].own == mdl || fp[i].frog == mdl)) return &fp[i]; return NULL; }
int frog_model_of(uint32_t mdl) { frogpair_t *p = fp_by(mdl); return p && p->frog == mdl; }
static void frog_construct(ppc_context *ctx, uint8_t *base, uint32_t mng, int type) {
    if ((type != MT_MARIO && !(getenv("RT_FROG_ANY") && type < MT_YOSHI)) || !brres(ctx, base, F_FROG_MARIO) || !R32(mng + MNG_MODEL)) return;   /* (RT_FROG_ANY: testing, any character with Mario's Frog) */
    frogpair_t *p = NULL;
    for (int i = 0; i < 16 && !p; i++) if (fp[i].mng == mng || !fp[i].mng) p = &fp[i];
    if (!p) { rt_log("chars", "Frog model: no room for another"); return; }
    if (!p->scratch) { p->scratch = (mem_next + 31) & ~31u; mem_next = p->scratch + 32; }   /* (a manager of our own to build it with) */
    W32(p->scratch, 0); W32(p->scratch + MNG_MODEL, 0);
    ppc_context save = *ctx;
    ctx->r[3] = p->scratch; ctx->r[4] = (uint32_t)type; orig_mod_fn_800D6D10(ctx, base);
    *ctx = save;
    p->mng = mng; p->own = R32(mng + MNG_MODEL); p->frog = R32(p->scratch + MNG_MODEL); p->ready = 0;
    rt_log("chars", "Frog model: %08X beside %08X (manager %08X)", p->frog, p->own, mng);
}
/* (gm_pf_family.c, after dPyMdlBase_c::create) the Frog's model created as its partner is */
void rt_charmdl_after_create(ppc_context *ctx, uint8_t *base, uint32_t mdl, uint32_t a4, uint32_t a5, uint32_t a6) {
    frogpair_t *p = fp_by(mdl); if (!p || p->own != mdl || !p->frog) return;
    rt_log("chars", "Frog model %08X: created with %08X (chara %u, mode %u, scene %u)", p->frog, mdl, a4, a5, a6);
    ppc_context save = *ctx;
    rt_gcall(ctx, base, A_MDL_CREATE, 4, p->frog, a4, a5, a6);
    p->ready = 1;
    if (a5 == PU_FROG) rt_gcall(ctx, base, R32(R32(mdl) + VT_SET_MODE), 2, mdl, a5);   /* (made a Frog: the Frog's model shown) */
    *ctx = save;
}
/* (gm_pf_family.c, dPlayerMdl_c::setPlayerMode) the model the manager shows; -1: asked of the
   other model (done), else the value this model sets */
int32_t rt_charmdl_set_mode(ppc_context *ctx, uint8_t *base, uint32_t mdl, uint32_t mode) {
    frogpair_t *p = fp_by(mdl); if (!p || !p->ready) return (int32_t)(mode == PU_FROG ? PU_SUPER : mode);
    uint32_t to = mode == PU_FROG ? p->frog : p->own;
    if (to != mdl) {                                                     /* (the other one shows this) */
        if (R32(p->mng + MNG_MODEL) == mdl) {
            W32(p->mng + MNG_MODEL, to);
            ppc_context save = *ctx;
            rt_gcall(ctx, base, R32(R32(to) + VT_SET_MODE), 2, to, mode);
            uint32_t anm = R32(mdl + MDL_CUR_ANM);                       /* (the animation goes over) */
            ctx->f[1].d = ctx->ps1[1] = 1.0; ctx->f[2].d = ctx->ps1[2] = 0.0; ctx->f[3].d = ctx->ps1[3] = 0.0;
            rt_gcall(ctx, base, A_START_ANIM, 2, to, anm);
            *ctx = save;
            rt_log("chars", "model %08X -> %08X (%s)", mdl, to, pu_name(mode));
            return -1;
        }
        return (int32_t)(mode == PU_FROG ? PU_SUPER : mode);            /* (not shown: kept plain) */
    }
    return (int32_t)(mdl == p->frog ? FROG_MDL_SLOT : mode);
}
/* (rt_retro.c, ~dPyMdlMng_c) the manager's own model back in place, the Frog's freed */
void rt_charmdl_mng_dtor(ppc_context *ctx, uint8_t *base, uint32_t mng) {
    for (int i = 0; i < 16; i++) if (fp[i].mng == mng) {
        W32(mng + MNG_MODEL, fp[i].own);
        if (fp[i].frog) { ppc_context save = *ctx; rt_gcall(ctx, base, R32(R32(fp[i].frog) + 8), 2, fp[i].frog, 1); *ctx = save; }
        fp[i].mng = fp[i].own = fp[i].frog = 0; fp[i].ready = 0;
    }
}
