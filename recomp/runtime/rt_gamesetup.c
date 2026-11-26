/* rt_gamesetup.c - the game setup scene (dScGameSetup_c), native.
 *
 * Flow from the title menu (Singleplayer / Multiplayer):
 *     Game Select -> File Select -> character select -> game
 * Back (1) goes the other way: character select -> File Select -> Game Select -> title.
 * Singleplayer character select: Start Game (alone, centred) shows only once the character is
 * chosen; 1 then takes the character back (the card returns on it), and 1 again goes back.
 *
 * Game Select and File Select are the game's file select screen (dFileSelect_c) shown two
 * ways: as Game Select it is a carousel of the games (NSMBW, SMB3, then the locked placeholder
 * games - "game portraits" below): the three cards show the
 * chosen game in the middle and its neighbours on either side, smaller and fainter, wrapping
 * round; left/right turns it (the cards slide along the arc to their new places). Both go the same way (File Select, character select); Start Game starts the chosen one.
 * SMB3 (../SMB3Disassembly/port) has its own three files: its File Select cards show them (the
 * NSMBW save is not touched), and it runs over the faded-out setup screen. + (or HOME) is its
 * pause menu (rt_menu.c); Quit goes to the title, as NSMBW's does.
 * The "Select Players" screen (dSelectPlayer_c) is gone: the character
 * select (dNumberOfPeopleChange_c) opens with 1 player (Singleplayer) or 8 (Multiplayer).
 * Every change of screen goes through black: the screen fades out with everything in place,
 * the next screen is set up while it is black, and it fades in already in place.
 *
 * This is also the first part of the 8-player module (MPL-2.0, THIRD_PARTY_NOTICES.md) moved to native
 * C: all of dScGameSetup_c, and the parts of the character select the menus need. The
 * recompiled originals stay available as orig_<name>() (see NATIVE_PORT.md).
 *
 * Guest functions are called with gcall(); state machines are driven through the state
 * manager's vtable (sStateMgr: +0x18 changeState, +0x28 getStateID). */
#include "rt.h"
#include "smb3.h"                               /* ../SMB3Disassembly/port */
#include "smb3_stage.h"
#include <math.h>
#include <ctype.h>
#include <dirent.h>
RT_STATE_FILE                                   /* (this file's variables are part of a save state: rt_state.c) */
extern uint64_t g_frames_presented;
int menu_singleplayer(void);                    /* rt_menu.c: 1 Singleplayer, 0 Multiplayer */
void menu_controls_open(void);                  /* rt_menu.c: the Controls screen (overlay) */
int menu_controls_is_open(void);

/* ---- guest addresses (USA rev 2) ---- */
#define G_NOW_SCENE       0x80428732u   /* dScene_c::m_nowScene */
#define SCENE_WORLD_MAP   3
#define SCENE_GAME_SETUP  10
#define G_FADER           0x8042A440u   /* dFader_c::mFader (vtable +0x10 getStatus) */
enum { FADER_OPAQUE = 0, FADER_HIDDEN = 1 };
#define A_SET_FADER       0x800B0DB0u   /* dFader_c::setFader(type) */
#define A_FADE_IN         0x800B0A20u   /* dFader_c::startFadeIn(frames) */
#define A_FADE_OUT        0x800B0A90u   /* dFader_c::startFadeOut(frames) */
#define A_START_TITLE     0x801017D0u   /* dScRestartCrsin_c::startTitle(u8, bool) */
#define A_INIT_LOAD_GAME  0x800E1840u   /* dSaveMng_c::initLoadGame(s8) */
#define A_LOAD_QUICK_SAVE 0x800E1940u   /* dSaveMng_c::loadQuickSaveData(u8) */
#define A_GET_SAVE_GAME   0x800E0380u   /* dSaveMng_c::getSaveGame(s8) */
#define G_SAVE_MNG        0x8042A040u   /* dSaveMng_c::m_instance */
#define SM_LAST_FILE      38            /* (s8) last save file played */
#define A_CHECK_BONUS_NOCAP 0x80060EF0u /* daPyMng_c::checkBonusNoCap() */
#define G_INFO            0x80429F7Cu   /* dInfo_c::m_instance */
#define G_GAME_FLAG       0x80429F80u   /* dInfo_c::mGameFlag */
enum { GF_MULTI_MODE = 0x10, GF_FREE_FOR_ALL = 0x20, GF_COIN_BATTLE = 0x40 };
#define G_SND_AUDIO_MGR   0x8042A488u   /* SndAudioMgr::sInstance */
#define A_START_SYSTEM_SE 0x80195380u   /* SndAudioMgr::startSystemSe(id, count) */
enum { SE_SYS_DECIDE = 121, SE_SYS_BACK = 122 };
#define G_SND_SCENE_MGR   0x8042A4A8u   /* SndSceneMgr::sInstance */
#define A_SET_SETUP_TRACK 0x8019BA20u   /* SndSceneMgr::setGameSetupTrack(track) */
#define A_CHK_CANCEL      0x800B53A0u   /* dGameCom::chkCancelButton(player) */
#define A_IS_ANIM_ON      0x800C9610u   /* m2d::EmbedLayout_c::isAnimOn(group; -1 any) */
#define A_CREATE_CHILD    0x80162B00u   /* fBase_c::createChild(profile, parent, param, group) */
#define A_CONSTRUCT_ACTOR 0x8006CBA0u   /* dBaseActor_c::construct(profile, parent, param, pos, angle) */
#define A_DO_SCENE_CHANGE 0x800E1E60u   /* dScene_c::setNextScene(profile, param, force) */
#define A_WMAP_BOOT_PARAM 0x80102A40u   /* dScWMap_c::CreateBootParam() */
#define A_DATEFILE_ANIME_OUT 0x80918460u /* dScGameSetup_c::executeDateFileAnimeOut() */
#define G_REMOCON_MNG     0x8042A028u   /* dRemoconMng_c::m_instance */
#define G_GAME_KEY        0x80429F50u   /* dGameKey_c::m_instance */
#define G_CUR_CORE        0x8042A464u   /* the player whose remote drives the menus */
#define G_SETUP_STATE_ID  0x80371870u   /* dRemoconMng_c::dConnect_c::StateID_Setup */
#define G_DISABLE_OPENING_MOVIE 0x8000678Au   /* fFeat::disable_opening_movie (settings.ini skip_opening_movie) */
/* data the 8-player module moved to its own area (8 players instead of 4) */
#define MOD_PY_TYPE       0x8185E93Cu   /* daPyMng_c::mPlayerType[8] */
#define MOD_PY_MODE       0x8185E95Cu   /* daPyMng_c::mPlayerMode[8] */
#define MOD_PY_CREATE_ITEM 0x8185E97Cu  /* daPyMng_c::mCreateItem[8] */
#define MOD_PY_REST       0x81851D8Cu   /* daPyMng_c::mRest[8] */
#define MOD_DEFAULT_TYPES 0x81849BE4u   /* dMj2dGame_c::scDefaultPlayerTypes[8] */
#define MOD_OVERLAY_RES   0x8185FA14u   /* mDvd overlay resource flag (setOverlayRes) */
#define MOD_GAME_VERSION  0x8185ED00u   /* region/revision: the profile table differs */
#define MFN_SET_EASY_PAIRING_WAIT 0x8181CCACu /* dNumberOfPeopleChange_c::setEasyPairingWait(bool) */
#define MFN_SPLIT_EXTENSION 0x81812EC4u /* dRemoconMng_c::dConnect_c::splitExtension() */

/* dScGameSetup_c */
#define GS_STATE        0x74
#define GS_2DPLAYER     0xC0            /* [4] */
#define GS_NUMPY        0xB8
#define GS_SELPLY       0xD0
#define GS_EASY_PAIRING 0xD4
#define GS_SEQUENCE_BG  0xD8
#define GS_DATEFILE     0xDC            /* [3] */
#define GS_FSEL         0xE8
#define GS_INFO_WINDOW  0xEC
#define GS_CREATE_IDX   0xF8
#define GS_IN_PLAYER_SELECT 0x108
#define ST_GS_FILE_SELECT    0x809A1548u
#define ST_GS_FADE_OUT       0x809A1588u
#define ST_GS_FADE_IN        0x809A15C8u
#define ST_GS_CONNECTION_CHECK 0x809A1648u
#define ST_GS_EASY_PAIRING_WAIT 0x809A1688u
#define ST_GS_LOW_BATTERY_CHECK 0x809A16C8u
#define ST_GS_NEXT_SCENE_WAIT 0x809A1788u
/* dFileSelect_c */
#define FS_STATE        0x20C
#define ST_FS_START_WAIT 0x80991F58u
#define FS_DATEFILE     0x24C           /* [3] */
#define FS_INFO_WINDOW  0x258
#define FS_CHOICE       0x2A4           /* 0-2 file, 3 Free-for-All, 4 Coin Battle */
#define FS_LAST_CHOICE  0x2CC
#define FS_ACTIVE       0x2D9
#define FS_CHOICE_DONE  0x2DB
#define FS_CHOICE_BACK  0x2DC
#define FS_CHOICE_TEMP  0x2DD
/* dDateFile_c (the file cards) */
#define DF_STATE        0xD9C
#define DF_REQUEST      0xDD8           /* 1 on, 2 picked, 5 reset, ... */
#define DF_ACTIVE       0xE49
#define ST_DF_INITIAL_SETUP 0x80991880u
/* dSelectPlayer_c */
#define SP_DECIDED      0x26B
#define SP_BUTTON       0x26C
#define SP_DIRECTION    0x270
#define SP_EASY_PAIRING_FLAG 0x279      /* (on dEasyPairing_c) */
/* dNumberOfPeopleChange_c (the character select) */
#define NP_LAYOUT       0x404
#define NP_STATE        0x59C
#define NP_ROOT         0x5D8
#define NP_ACTIVE       0x67E
#define NP_CANCEL_OK    0x680
#define NP_PLAYER_COUNT 0x6C4
#define NP_ON_BUTTON    0x6C8           /* 0 Start Game, 1 Back */
#define NP_CC_COUNT     0x710
#define NP_CC_BASE      0x714           /* [8] dCharacterChangeSelectBase_c */
#define NP_CC_CONTENTS  0x734
#define NP_CC_ARROW     0x754
#define NP_CC_INDICATOR 0x774
#define NP_2DPLAYER     0x794           /* [8] by player type */
#define ST_NP_NOW_ENTRANT_RECRUIT   0x809945B0u
#define ST_NP_INFO_WINDOW_EXIT_WAIT 0x80994630u
#define ST_NP_EXIT_ANIME_END_CHECK  0x80994770u
/* dCharacterChangeSelectBase_c */
#define CB_STATE        0x228
#define CB_BUSY         0x296
#define CB_DECIDED      0x29A
#define CB_EXIT         0x29B
#define CB_ENTER_COUNT  0x288           /* int*: how many players have chosen */
#define ST_CB_PLAYER_EXIT_WAIT 0x80990D80u
#define A_ANIM_RESET    0x800C93D0u     /* m2d::EmbedLayout_c::resetAnim(group, at the end) */
/* the character select layout's animation groups (createLayout): 2-5 inYesNoButtons (yes, no,
   guide, guide), 6-7 onYesNoButtons (yes, no) */
enum { NPA_IN_FIRST = 2, NPA_ON_LAST = 7 };
#define ST_CB_SELECT_START_WAIT    0x80990A80u
#define ST_CB_BUTTON_EXIT_ANIME    0x80990AC0u   /* (what 2 starts in SelectStartWait: the card comes back) */
#define NP_IND_PANES    0x21C           /* (on each indicator) two panes the buttons hide: +0x21C, +0x220 */
#define TDP_FLAG        0x266           /* (on each 2D player) set while the buttons show */
#define TDP_POS_X       0xAC            /* (on each 2D player) mPos.x: the figure above the card (layout units) */
#define NP_BUTTONS_FLAG 0x688

/* ---- guest calls (rt_gcall in rt.h) ---- */
uint32_t rt_gcall_(const char *file, int line, ppc_context *ctx, uint8_t *base, uint32_t fn, int n, ...) {
    uint32_t saved[13], lr = ctx->lr, ctr = ctx->ctr;
    if (fn < 0x80000000u) { static int bad; if (bad++ < 8) rt_log("gcall", "%s:%d: no function to call (%08X)", file, line, fn); return 0; }
    memcpy(saved, ctx->r, sizeof saved);
    va_list ap; va_start(ap, n);
    for (int i = 0; i < n && i < 8; i++) ctx->r[3 + i] = va_arg(ap, uint32_t);
    va_end(ap);
    ctx->lr = 0;
    ppc_call_indirect(ctx, base, fn);
    uint32_t ret = ctx->r[3];
    memcpy(ctx->r, saved, sizeof saved); ctx->lr = lr; ctx->ctr = ctr;
    return ret;
}
#define gcall rt_gcall
#define VFN(obj, off) R32(R32(obj) + (off))
static void change_state(ppc_context *ctx, uint8_t *base, uint32_t mgr, uint32_t state) { gcall(ctx, base, VFN(mgr, 0x18), 2, mgr, state); }
static uint32_t state_id(ppc_context *ctx, uint8_t *base, uint32_t mgr) { return gcall(ctx, base, VFN(mgr, 0x28), 1, mgr); }
/* a state object is [vtable][name][number]...; the name is "Class::StateID_Name" */
static int state_is(ppc_context *ctx, uint8_t *base, uint32_t mgr, const char *name) {
    uint32_t st = state_id(ctx, base, mgr), np = st ? R32(st + 4) : 0;
    if (np < 0x80000000u || np >= 0x81800000u) return 0;
    char s[96]; int i;
    for (i = 0; i < 95 && R8(np + i); i++) s[i] = (char)R8(np + i);
    s[i] = 0;
    const char *u = strstr(s, "StateID_");
    return u && !strcmp(u + 8, name);
}
static int fader_seen = FADER_HIDDEN;     /* last status read (input is held while the screen isn't fully shown) */
static int fader_status(ppc_context *ctx, uint8_t *base) { uint32_t f = R32(G_FADER); return fader_seen = f ? (int)gcall(ctx, base, VFN(f, 0x10), 1, f) : FADER_HIDDEN; }
static void fade_out(ppc_context *ctx, uint8_t *base) { gcall(ctx, base, A_SET_FADER, 1, 0); gcall(ctx, base, A_FADE_OUT, 1, 30); }
/* fading to black: 1 once black. The fader only starts a fade-out from fully shown, so one
   asked for during a fade-in doesn't happen: ask again once the fade-in is over. (Before,
   pressing a button during a fade-in left the screen waiting for black forever, input off.) */
static int screen_black(ppc_context *ctx, uint8_t *base) {
    int st = fader_status(ctx, base);
    if (st == FADER_OPAQUE) return 1;
    if (st == FADER_HIDDEN) fade_out(ctx, base);
    return 0;
}
static void fade_in(ppc_context *ctx, uint8_t *base) { gcall(ctx, base, A_SET_FADER, 1, 0); gcall(ctx, base, A_FADE_IN, 1, 30); }
static void play_se(ppc_context *ctx, uint8_t *base, uint32_t id) { gcall(ctx, base, A_START_SYSTEM_SE, 3, R32(G_SND_AUDIO_MGR), id, 1); }
/* dInfo_c::setPlyConnectStage: the first four players' entries are where the game had them */
static uint32_t connect_stage_addr(uint32_t player) { uint32_t info = R32(G_INFO); return player < 4 ? info + 900 + 4 * player : info + 2892 + 4 * player; }

/* ---- what the setup scene is showing ---- */
enum { PH_GAME, PH_FILE, PH_CHAR };
static const char *ph_name[] = {"Game Select", "File Select", "character select"};
static int phase = PH_GAME;              /* the screen in use */
static int pending = -1;                 /* the screen to set up once the screen is black */
static int fs_fade_in_wait;              /* file select set up behind black: fade in when it's ready */
static int char_fade_in_wait;            /* character select set up behind black: fade in when it's in place */
static uint64_t wait_start;
static int np_exit_wait;                 /* character select: leaving, fading out first */
static int np_back_wait;                 /* character select: 1 pressed, fading out first */
static uint32_t np_buttons;              /* singleplayer: the select whose Start Game button shows (0: none) */
static struct { uint8_t ind[8][2], tdp[8], flag; } np_snap;   /* what showing the button changed */
static uint32_t cb_rejoin;               /* singleplayer: the card whose character was taken back */
static uint32_t gs_scene;                /* the dScGameSetup_c, while the scene runs */
static int game_sel;                     /* Game Select: the game on the card (games[]) */
static uint32_t sp_visit;                /* counts the singleplayer character select's openings (rt_charsel.c) */
static float spin;                       /* (the carousel's turn still to show: below) */
static void cards_forget(void);          /* (game portraits: a scene's card pictures are gone with it) */
static int play_game;                    /* the game chosen there (what Start Game starts) */
static int smb3_started;                 /* Start Game started SMB3 (it runs until Quit) */
static int smb3_file;                    /* the SMB3 file chosen on the File Select */
int rt_smb3_file(void) { return smb3_file; }   /* (SMB3Disassembly/port/smb3_stage.c: its map's file) */
int menu_smb3_pause_input(uint32_t pressed);   /* rt_menu.c */
static int games_n(void);
static int cur_game(void);
static int game_locked(int g);
static void *game_portrait_any(int g);         /* (game_portrait, below) */
static const char *game_label(int g);
enum { GAME_NSMBW, GAME_SMB3 };

static int in_setup(void) { return R16(G_NOW_SCENE) == SCENE_GAME_SETUP; }
static int is_multi(void) { return !menu_singleplayer(); }
static void fs3_restore(void);
static void set_phase(int p) {
    if (p != phase) rt_log("setup", "%s", ph_name[p]);
    if (p != PH_FILE) fs3_restore();                                      /* (SMB3's File Select left: NSMBW's slots back) */
    phase = p;
}
static void reset_if_left(void) {
    if (!in_setup() && (gs_scene || phase != PH_GAME || pending >= 0)) {
        gs_scene = 0; phase = PH_GAME; pending = -1; fs_fade_in_wait = char_fade_in_wait = np_exit_wait = np_back_wait = 0;
        np_buttons = 0; cb_rejoin = 0; fs3_restore();
        if (smb3_active()) smb3_quit();                                   /* (if SMB3 was running) */
        smb3_take_quit(); smb3_started = 0;
        cards_forget(); spin = 0;
    }
}

/* ======================================================= dScGameSetup_c (8-player version, native) */

/* Phase_CreateLayoutManagers: the screens. Profile numbers differ between game revisions. */
void hle_mod_fn_2_1AA4E0(ppc_context *ctx, uint8_t *base) {
    uint32_t self = ctx->r[3];
    gs_scene = self; phase = PH_GAME; pending = -1;                       /* a new setup scene starts at Game Select */
    fs_fade_in_wait = char_fade_in_wait = np_exit_wait = np_back_wait = 0;
    rt_log("setup", "scene %08X: Game Select (%s)", self, is_multi() ? "multiplayer" : "singleplayer");
    int ver = (int)R32(MOD_GAME_VERSION), lt6 = ver < 6, lt8 = ver < 8, off = lt6 ? 0 : lt8 ? 2 : 4;
    uint32_t np = gcall(ctx, base, A_CREATE_CHILD, 4, lt8 ? 694u : 696u, self, 0, 0);
    W32(self + GS_NUMPY, np);
    for (uint32_t cc = 0; cc < R32(np + NP_CC_COUNT); cc++) {
        W32(np + NP_CC_BASE + 4 * cc, gcall(ctx, base, A_CREATE_CHILD, 4, 735u + off, self, cc, 0));
        W32(np + NP_CC_CONTENTS + 4 * cc, gcall(ctx, base, A_CREATE_CHILD, 4, 736u + off, self, cc, 0));
        W32(np + NP_CC_ARROW + 4 * cc, gcall(ctx, base, A_CREATE_CHILD, 4, 737u + off, self, cc, 0));
        W32(np + NP_CC_INDICATOR + 4 * cc, gcall(ctx, base, A_CREATE_CHILD, 4, 738u + off, self, cc, 0));
    }
    W32(self + GS_SELPLY, gcall(ctx, base, A_CREATE_CHILD, 4, lt8 ? 700u : 702u, self, 0, 0));
    W32(self + GS_EASY_PAIRING, gcall(ctx, base, A_CREATE_CHILD, 4, lt8 ? 697u : 699u, self, 0, 0));
    W32(self + GS_SEQUENCE_BG, gcall(ctx, base, A_CREATE_CHILD, 4, 721u + off, self, 0, 0));
    uint32_t fs = gcall(ctx, base, A_CREATE_CHILD, 4, 725u + off, self, R32(self + 4), 0);
    W32(self + GS_FSEL, fs);
    for (uint32_t i = 0; i < 3; i++) {
        uint32_t df = gcall(ctx, base, A_CREATE_CHILD, 4, 724u + off, self, i, 0);
        W32(self + GS_DATEFILE + 4 * i, df); W32(fs + FS_DATEFILE + 4 * i, df);
    }
    uint32_t iw = gcall(ctx, base, A_CREATE_CHILD, 4, 718u + off, self, 0, 0);
    W32(self + GS_INFO_WINDOW, iw); W32(fs + FS_INFO_WINDOW, iw);
    ctx->r[3] = 1;
}

/* Phase_Create2DPlayer: one character model per call, all eight */
void hle_mod_fn_2_1AA710(ppc_context *ctx, uint8_t *base) {
    uint32_t self = ctx->r[3], idx = R32(self + GS_CREATE_IDX);
    uint32_t pl = gcall(ctx, base, A_CONSTRUCT_ACTOR, 5, (int)R32(MOD_GAME_VERSION) < 8 ? 698u : 700u, self, idx, 0, 0);
    if (!pl) { ctx->r[3] = 0; return; }
    if (idx < 4) W32(self + GS_2DPLAYER + 4 * idx, pl);
    W32(R32(self + GS_NUMPY) + NP_2DPLAYER + 4 * idx, pl);
    if (++idx < 8) { W32(self + GS_CREATE_IDX, idx); ctx->r[3] = 0; return; }
    W32(self + GS_CREATE_IDX, 0); ctx->r[3] = 1;
}

/* the character select comes up behind black: as the module's "Select Players" answer did,
   minus that screen (1 player in Singleplayer, 8 in Multiplayer) */
static void char_select_open(ppc_context *ctx, uint8_t *base, uint32_t self) {
    uint32_t np = R32(self + GS_NUMPY);
    for (uint32_t i = 0; i < 8; i++) W32(connect_stage_addr(i), 0);       /* PlyConnectStage OFF */
    W8(np + NP_ACTIVE, 1);
    W32(np + NP_PLAYER_COUNT, is_multi() ? 8 : 1);
    if (!is_multi()) sp_visit++;                                          /* (a new visit for the grid) */
    change_state(ctx, base, self + GS_STATE, ST_GS_CONNECTION_CHECK);
    char_fade_in_wait = 1; wait_start = g_frames_presented;
}
/* ---- the singleplayer character grid (rt_charsel.c) ---- */
#define SP_CARD_DX (-170.0f)                    /* singleplayer: the card (the grid's preview) moves left by this (layout units) */
uint32_t gs_sp_select_visit(void) { return sp_visit; }
/* 0 not shown, 1 choosing, 2 chosen (Start Game shows) */
int gs_sp_select_state(void) {
    if (!in_setup() || !gs_scene || phase != PH_CHAR || is_multi() || pending >= 0) return 0;
    return np_buttons ? 2 : 1;
}
/* how much of the screen shows: 1 shown .. 0 black (mFaderBase_c: +4 status 0 opaque, 1 hidden,
   2 / 3 fading; mColorFader_c +19: its alpha) */
float gs_screen_alpha(void) {
    uint32_t f = R32(G_FADER);
    if (!(f >= 0x80000000u && f < 0x94000000u)) return 1;
    uint32_t st = R32(f + 4);
    if (st == 1) return 1;
    if (st == 0) return 0;
    return 1.0f - R8(f + 19) / 255.0f;
}
/* the card's middle on the overlay (640 x 480: a layout unit is 480 / 456 of it in 4:3; in 16:9 the
   overlay keeps 4:3 in the middle of the screen while the layout spreads over all of it) */
float gs_sp_preview_x(void) { return 320.0f + SP_CARD_DX * (480.0f / 456.0f) * (rt_widescreen() ? 4.0f / 3.0f : 1.0f); }

/* ---- SMB3's File Select: NSMBW's own cards, on SMB3's files ----
   While the File Select shows SMB3's files, the save manager's three slots (and quick saves) hold
   stand-ins made from SMB3's files - an SMB3 file is a slot with its world and lives, no file an
   empty one, no quick saves - so the game's own cards, Copy and Erase work on them as on NSMBW's.
   NSMBW's real slots are kept here and put back: around each NAND save (the NAND command copies
   the data at once: gm_d_nand.c nand_cmdSave), before a file is loaded, and when the File Select
   is left. Copy (saveGameCopy) and Erase (dMj2dGame_c::initialize on a slot) are also done on
   SMB3's files (smb3_main.c). */
#define FS3_SLOT_SIZE  0x980
#define A_MJ2D_INIT    0x800CDED0u              /* dMj2dGame_c::initialize */
#define MJ2D_COMPLETION 0x002                   /* (u8: bit 0x01 the slot is empty) */
#define MJ2D_WORLD      0x003                   /* (u8: the world the file is on) */
#define MJ2D_LIFE       0x029                   /* (u8 [8]: lives, by player type) */
#define MJ2D_WORLD_OPEN 0x049                   /* (u8 [10]: bit 0x01 the world is open - the card shows the highest) */
#define DF_TB_WORLD    3580                     /* (dDateFile_c: the world number's text box, d_basesNP fn_2_10420 / 0x8077D9E0) */
#define DF_TB_LIVES    3588                     /* (the lives') */
#define SAVEMNG_GAME_   0x06C0                  /* (the save manager's slots and quick saves: gm_save_mng.c) */
#define SAVEMNG_TEMP_   0x2340
static uint8_t fs3_real[2][3 * FS3_SLOT_SIZE];  /* NSMBW's slots, quick saves - while the stand-ins are in */
static int fs3_swapped, fs3_building;
static int smb3_files_shown(void) { return in_setup() && gs_scene && phase == PH_FILE && play_game == GAME_SMB3; }
static void fs3_copy(uint32_t mng, int to_mng) {
    for (int r = 0; r < 2; r++) {
        uint32_t at = mng + (r ? SAVEMNG_TEMP_ : SAVEMNG_GAME_);
        for (uint32_t i = 0; i < 3 * FS3_SLOT_SIZE; i++) { if (to_mng) W8(at + i, fs3_real[r][i]); else fs3_real[r][i] = R8(at + i); }
    }
}
/* the stand-ins, from SMB3's files (the real slots kept first, the first time) */
static void fs3_put(ppc_context *ctx, uint8_t *base) {
    uint32_t mng = R32(G_SAVE_MNG);
    if (!mng) return;
    if (!fs3_swapped) { fs3_copy(mng, 0); fs3_swapped = 1; }
    fs3_building = 1;
    for (int k = 0; k < 3; k++) { gcall(ctx, base, A_MJ2D_INIT, 1, mng + SAVEMNG_GAME_ + (uint32_t)k * FS3_SLOT_SIZE); gcall(ctx, base, A_MJ2D_INIT, 1, mng + SAVEMNG_TEMP_ + (uint32_t)k * FS3_SLOT_SIZE); }
    fs3_building = 0;
    for (int k = 0; k < 3; k++) {
        uint32_t s = mng + SAVEMNG_GAME_ + (uint32_t)k * FS3_SLOT_SIZE; int world, lives;
        if (!smb3_file_info(k, &world, &lives)) continue;
        W8(s + MJ2D_COMPLETION, R8(s + MJ2D_COMPLETION) & ~1u);
        W8(s + MJ2D_WORLD, (uint8_t)world);
        for (int w = 0; w <= world && w < 10; w++) W8(s + MJ2D_WORLD_OPEN + (uint32_t)w, R8(s + MJ2D_WORLD_OPEN + (uint32_t)w) | 1u);
        for (int t = 0; t < 8; t++) W8(s + MJ2D_LIFE + (uint32_t)t, (uint8_t)(lives > 99 ? 99 : lives));
    }
    {   char b[120]; int o = 0; for (int k = 0; k < 3; k++) { uint32_t s = mng + SAVEMNG_GAME_ + (uint32_t)k * FS3_SLOT_SIZE;
            o += snprintf(b + o, sizeof b - o, " %d:%s", k + 1, R8(s + MJ2D_COMPLETION) & 1 ? "new" : "World"); if (!(R8(s + MJ2D_COMPLETION) & 1)) o += snprintf(b + o, sizeof b - o, " %d x%d", R8(s + MJ2D_WORLD) + 1, R8(s + MJ2D_LIFE)); }
        rt_log("setup", "SMB3 File Select: SMB3's files in the cards (NSMBW's slots kept):%s", b); }
}
/* NSMBW's real slots back */
static void fs3_restore(void) {
    if (!fs3_swapped) return;
    uint32_t mng = R32(G_SAVE_MNG);
    if (mng) fs3_copy(mng, 1);
    fs3_swapped = 0;
}
/* gm_save_mng.c, around each NAND save: NSMBW's own data is what's written */
static int fs3_saving;
void gs_smb3_save_begin(void) { fs3_saving = fs3_swapped; fs3_restore(); }
void gs_smb3_save_end(ppc_context *ctx, uint8_t *base) { if (fs3_saving && smb3_files_shown()) fs3_put(ctx, base); fs3_saving = 0; }
/* saveGameCopy(dst, src): also SMB3's files (the game copies the stand-ins) */
void gs_smb3_copy(int dst, int src) { if (fs3_swapped && smb3_files_shown()) smb3_file_copy(src, dst); }
/* dMj2dGame_c::initialize(at): Erase on a stand-in slot is the Erase of that SMB3 file */
void gs_smb3_init(uint32_t at) {
    if (fs3_building || !fs3_swapped || !smb3_files_shown()) return;
    uint32_t mng = R32(G_SAVE_MNG);
    if (mng && at >= mng + SAVEMNG_GAME_ && at < mng + SAVEMNG_GAME_ + 3 * FS3_SLOT_SIZE && (at - mng - SAVEMNG_GAME_) % FS3_SLOT_SIZE == 0)
        smb3_file_delete((int)((at - mng - SAVEMNG_GAME_) / FS3_SLOT_SIZE));
}

/* the file select comes up behind black (Game Select or File Select) */
static void file_select_open(ppc_context *ctx, uint8_t *base, uint32_t self) {
    uint32_t fs = R32(self + GS_FSEL);
    if (phase == PH_FILE && play_game == GAME_SMB3) fs3_put(ctx, base);  /* (SMB3's files in NSMBW's cards) */
    else fs3_restore();
    W8(self + GS_IN_PLAYER_SELECT, 0);
    change_state(ctx, base, self + GS_STATE, ST_GS_FILE_SELECT);          /* (switches it on again) */
    /* the cards start over (what their "reset" request does - asked for by the fade-out's end,
       but they only act on it while shown, which they no longer are) */
    for (int i = 0; i < 3; i++) {
        uint32_t df = R32(fs + FS_DATEFILE + 4 * i);
        change_state(ctx, base, df + DF_STATE, ST_DF_INITIAL_SETUP);
        W8(df + DF_ACTIVE, 0); W32(df + DF_REQUEST, 0);
    }
    change_state(ctx, base, fs + FS_STATE, ST_FS_START_WAIT);             /* (what its GameStartWait does after a fade; clears the choice) */
    int last = (int8_t)R8(R32(G_SAVE_MNG) + SM_LAST_FILE);               /* the cursor starts on the last file played (Game Select: the middle card) */
    int cur = phase == PH_GAME ? 1 : (last >= 0 && last < 3) ? last : 0;
    if (phase == PH_GAME) for (int g = 0; g < games_n(); g++) game_portrait_any(g);   /* (every game's picture, while it's black) */
    W32(fs + FS_CHOICE, (uint32_t)cur); W32(fs + FS_LAST_CHOICE, (uint32_t)cur);
    fs_fade_in_wait = 1; wait_start = g_frames_presented;
}

/* executeState_FileSelect */
void hle_mod_fn_2_1AAFE0(ppc_context *ctx, uint8_t *base) {
    uint32_t self = ctx->r[3], fs = R32(self + GS_FSEL);
    gs_scene = self;
    fader_status(ctx, base);
    if (phase == PH_GAME) W32(fs + FS_CHOICE, 1);                       /* Game Select: the one card is the middle one */
    gcall(ctx, base, A_DATEFILE_ANIME_OUT, 1, self);
    if (fs_fade_in_wait) {                                                /* set up behind black: show it once it's ready */
        if (state_is(ctx, base, fs + FS_STATE, "SelectWait") || g_frames_presented - wait_start > 120) {
            rt_log("setup", "%s ready after %llu frames (frame %llu)", ph_name[phase], (unsigned long long)(g_frames_presented - wait_start), (unsigned long long)g_frames_presented);
            fade_in(ctx, base); fs_fade_in_wait = 0;
        }
    }
    if (!R8(fs + FS_CHOICE_DONE)) return;
    int back = R8(fs + FS_CHOICE_BACK);
    if (phase == PH_GAME) {
        if (back) {                                                       /* Game Select -> title */
            gcall(ctx, base, A_START_TITLE, 2, 0, 0);
            change_state(ctx, base, self + GS_STATE, ST_GS_NEXT_SCENE_WAIT);
            return;
        }
        play_game = cur_game();
        rt_log("setup", "Game Select: %s", game_label(play_game));
        pending = PH_FILE;                                                /* (the same for every game) */
        W8(self + GS_IN_PLAYER_SELECT, 0);
        change_state(ctx, base, self + GS_STATE, ST_GS_FADE_OUT);
        return;
    }
    if (back) {                                                           /* File Select -> Game Select */
        pending = PH_GAME;
        W8(self + GS_IN_PLAYER_SELECT, 0);
        change_state(ctx, base, self + GS_STATE, ST_GS_FADE_OUT);
        return;
    }
    W32(R32(self + GS_SELPLY) + SP_BUTTON, 0);
    W8(self + GS_IN_PLAYER_SELECT, 1);
    int choice = (int)R32(fs + FS_CHOICE);
    if (choice < 3 && play_game == GAME_SMB3) {                           /* an SMB3 file (smb3_main.c keeps them) */
        fs3_restore();                                                    /* (NSMBW's own slot for the stage's players, below) */
        smb3_file = choice;
        if (rt_setting("smb3_stage", 1)) gcall(ctx, base, A_INIT_LOAD_GAME, 2, R32(G_SAVE_MNG), (uint32_t)(int8_t)choice);   /* (the stage prototype: NSMBW's player data, read only) */
        rt_log("setup", "SMB3 file %d (%s)", choice + 1, smb3_file_summary(choice) ? smb3_file_summary(choice) : "new");
    } else if (choice < 3) {                                              /* a save file */
        if (R8(fs + FS_CHOICE_TEMP)) gcall(ctx, base, A_LOAD_QUICK_SAVE, 2, R32(G_SAVE_MNG), (uint32_t)choice & 0xFF);
        gcall(ctx, base, A_INIT_LOAD_GAME, 2, R32(G_SAVE_MNG), (uint32_t)(int8_t)choice);
    } else {                                                              /* Free-for-All / Coin Battle */
        for (int i = 0; i < 8; i++) W32(MOD_PY_REST + 4 * i, 5);
        gcall(ctx, base, A_CHECK_BONUS_NOCAP, 0);
        uint32_t f = R32(G_GAME_FLAG) & ~(uint32_t)(GF_MULTI_MODE | GF_FREE_FOR_ALL | GF_COIN_BATTLE);
        W32(G_GAME_FLAG, f | GF_MULTI_MODE | (choice == 3 ? GF_FREE_FOR_ALL : GF_COIN_BATTLE));
        W8(MOD_OVERLAY_RES, 0);
    }
    pending = PH_CHAR;
    change_state(ctx, base, self + GS_STATE, ST_GS_FADE_OUT);
}

/* finalizeState_FileSelect: default characters */
void hle_mod_fn_2_1AB140(ppc_context *ctx, uint8_t *base) {
    (void)ctx; (void)base;
    for (int i = 0; i < 8; i++) W32(MOD_PY_TYPE + 4 * i, R32(MOD_DEFAULT_TYPES + 4 * i));
}

/* executeState_FadeOut: once black, set up the next screen */
void hle_fn_2_1AB1B0(ppc_context *ctx, uint8_t *base) {
    uint32_t self = ctx->r[3];
    gs_scene = self;
    if (!screen_black(ctx, base)) return;
    if (pending == PH_CHAR || (pending < 0 && R8(self + GS_IN_PLAYER_SELECT))) {
        pending = -1; set_phase(PH_CHAR);
        char_select_open(ctx, base, self);
        return;
    }
    if (pending >= 0) { set_phase(pending); pending = -1; }
    file_select_open(ctx, base, self);
}

/* executeState_FadeIn (no longer used by the flow above; kept equivalent) */
void hle_fn_2_1AB280(ppc_context *ctx, uint8_t *base) {
    uint32_t self = ctx->r[3];
    gs_scene = self;
    if (fader_status(ctx, base) != FADER_HIDDEN) return;
    if (R8(self + GS_IN_PLAYER_SELECT)) char_select_open(ctx, base, self);
    else change_state(ctx, base, self + GS_STATE, ST_GS_FILE_SELECT);
}

/* executeState_StartMember: answer of the old "Select Players" screen (not shown any more) */
void hle_mod_fn_2_1AB360(ppc_context *ctx, uint8_t *base) {
    uint32_t self = ctx->r[3], sp = R32(self + GS_SELPLY);
    if (!R8(sp + SP_DECIDED)) return;
    int dir = (int)R32(sp + SP_DIRECTION);
    if (dir == -1) { W8(self + GS_IN_PLAYER_SELECT, 0); change_state(ctx, base, self + GS_STATE, ST_GS_FADE_OUT); return; }
    if (dir != 1) return;
    uint32_t np = R32(self + GS_NUMPY);
    for (uint32_t i = 0; i < 8; i++) W32(connect_stage_addr(i), 0);
    W8(np + NP_ACTIVE, 1);
    W32(np + NP_PLAYER_COUNT, R32(sp + SP_BUTTON) + 1);
    change_state(ctx, base, self + GS_STATE, ST_GS_CONNECTION_CHECK);
}

/* initializeState_ConnectionCheck: no star power left over from a versus game; music */
void hle_mod_fn_2_1AB470(ppc_context *ctx, uint8_t *base) {
    uint32_t self = ctx->r[3];
    if (R32(G_GAME_FLAG) & GF_MULTI_MODE) {
        uint32_t np = R32(self + GS_NUMPY);
        for (int i = 0; i < 8; i++) {
            uint32_t type = R32(MOD_PY_TYPE + 4 * i);
            W32(MOD_PY_MODE + 4 * type, 0);
            uint32_t mdl = R32(R32(R32(np + NP_2DPLAYER + 4 * type) + 296) + 4);   /* mp2DPlayer[type]->mModelMng->mModel */
            if (R32(mdl + 380) & 0x100) gcall(ctx, base, VFN(mdl, 68), 1, mdl);   /* offStarAnm */
            if (R32(mdl + 380) & 0x200) gcall(ctx, base, VFN(mdl, 76), 1, mdl);   /* offStarEffect */
            uint32_t ci = MOD_PY_CREATE_ITEM + 4 * type;
            if (R32(ci) & 1) W32(ci, R32(ci) & ~1u);                     /* no STAR_POWER */
        }
    }
    gcall(ctx, base, A_SET_SETUP_TRACK, 2, R32(G_SND_SCENE_MGR), 2);
}

/* the character select is up and settled (it came in behind black) */
static int char_select_settled(uint32_t np) {
    if (!R8(np + NP_CANCEL_OK)) return 0;
    for (uint32_t cc = 0; cc < R32(np + NP_PLAYER_COUNT) && cc < 8; cc++) if (R8(R32(np + NP_CC_BASE + 4 * cc) + CB_BUSY)) return 0;
    return 1;
}
static int plus_pressed(void) {
    uint32_t core = R32(R32(G_GAME_KEY) + 4 + 4 * R32(G_CUR_CORE));
    return core && (R32(core + 28) & 0x10);
}

/* executeState_ConnectionCheck: the character select is open */
void hle_fn_2_1AB570(ppc_context *ctx, uint8_t *base) {
    uint32_t self = ctx->r[3], np = R32(self + GS_NUMPY);
    gs_scene = self;
    fader_status(ctx, base);
    if (char_fade_in_wait) {
        if (char_select_settled(np) || g_frames_presented - wait_start > 240) {
            rt_log("setup", "character select (%u players) ready after %llu frames (frame %llu)", R32(np + NP_PLAYER_COUNT), (unsigned long long)(g_frames_presented - wait_start), (unsigned long long)g_frames_presented);
            fade_in(ctx, base); char_fade_in_wait = 0;
        }
        return;
    }
    if (R8(np + NP_CANCEL_OK)) {
        if (plus_pressed() && !menu_controls_is_open()) {                /* "Settings +": the Controls screen (was: pair a remote) */
            play_se(ctx, base, SE_SYS_DECIDE);
            menu_controls_open();
        }
        return;
    }
    if (R8(np + NP_ACTIVE)) return;
    if (R32(np + NP_ON_BUTTON) == 0) {                                     /* Start Game */
        if (play_game == GAME_SMB3 && !rt_setting("smb3_stage", 1)) {                                     /* SMB3: over the black screen, until HOME */
            if (!smb3_started) { smb3_started = 1; smb3_enter(smb3_file); }
            if (smb3_active()) return;
            smb3_started = 0;
            if (smb3_take_quit()) {                                       /* Quit: to the title (as Game Select's Back) */
                gcall(ctx, base, A_START_TITLE, 2, 0, 0);
                change_state(ctx, base, self + GS_STATE, ST_GS_NEXT_SCENE_WAIT);
                return;
            }
            set_phase(PH_FILE); file_select_open(ctx, base, self);        /* (otherwise: back to the File Select) */
            return;
        }
        change_state(ctx, base, self + GS_STATE, ST_GS_LOW_BATTERY_CHECK); return;
    }
    set_phase(PH_FILE);                                                   /* Back: the character select has gone (behind black) */
    file_select_open(ctx, base, self);
}

/* initializeState_EasyPairingWait / finalizeState_EasyPairingWait (pairing a remote; not reached from the menus now) */
void hle_mod_fn_2_1AB620(ppc_context *ctx, uint8_t *base) {
    uint32_t self = ctx->r[3];
    gcall(ctx, base, MFN_SET_EASY_PAIRING_WAIT, 2, R32(self + GS_NUMPY), 1);
    W8(R32(self + GS_EASY_PAIRING) + SP_EASY_PAIRING_FLAG, 1);
}
void hle_mod_fn_2_1AB6D0(ppc_context *ctx, uint8_t *base) {
    gcall(ctx, base, MFN_SET_EASY_PAIRING_WAIT, 2, R32(ctx->r[3] + GS_NUMPY), 0);
}

/* finalizeState_VoiceEndWait: on to the world map (or the opening movie for a new save) */
void hle_mod_fn_2_1AB9F0(ppc_context *ctx, uint8_t *base) {
    if (play_game == GAME_SMB3 && rt_setting("smb3_stage", 1) && smb3_stage_begin(ctx, base)) return;   /* SMB3 (prototype): its 1-1 in an NSMBW stage, not the world map (smb3_stage.c) */
    uint32_t save = gcall(ctx, base, A_GET_SAVE_GAME, 2, R32(G_SAVE_MNG), (uint32_t)-1);
    if ((R8(save + 2) & 1) && !R8(G_DISABLE_OPENING_MOVIE)) gcall(ctx, base, A_DO_SCENE_CHANGE, 3, 8, 0, 0);   /* MOVIE */
    else gcall(ctx, base, A_DO_SCENE_CHANGE, 3, 3, gcall(ctx, base, A_WMAP_BOOT_PARAM, 0), 0);                /* WORLD_MAP */
}

/* ======================================================= dNumberOfPeopleChange_c (in part) */

/* checkCancel (module version, unchanged) */
static int np_check_cancel(ppc_context *ctx, uint8_t *base, uint32_t np) {
    int p1 = R8(R32(np + NP_CC_BASE) + CB_DECIDED);
    if (R16(G_NOW_SCENE) == SCENE_WORLD_MAP) {
        if (!p1) return 0;
        uint32_t core = R32(R32(G_GAME_KEY) + 4 + 4 * R32(G_CUR_CORE));
        return gcall(ctx, base, VFN(core, 32), 2, core, 0x900) != 0;    /* checkMenuConfirm */
    }
    if (p1) return 0;                                                     /* 1 first takes back player 1's choice */
    return gcall(ctx, base, A_CHK_CANCEL, 1, 0) != 0;
}
static int base_joined(ppc_context *ctx, uint8_t *base, uint32_t b) { return !state_is(ctx, base, b + CB_STATE, "ConnectWait"); }
/* leave the character select: in the setup scene the screen fades out first, everything in place */
static int np_leave(ppc_context *ctx, uint8_t *base, uint32_t np, int on_button, uint32_t state) {
    if (in_setup()) {
        if (!np_exit_wait) { np_exit_wait = 1; fade_out(ctx, base); return 0; }
        if (!screen_black(ctx, base)) return 0;
        np_exit_wait = 0;
    }
    if (on_button >= 0) W32(np + NP_ON_BUTTON, (uint32_t)on_button);
    for (uint32_t cc = 0; cc < R32(np + NP_PLAYER_COUNT) && cc < 8; cc++) W8(R32(np + NP_CC_BASE + 4 * cc) + CB_EXIT, 1);
    change_state(ctx, base, np + NP_STATE, state);
    return 1;
}

/* executeState_NowEntrantRecruit: players pick their characters */
void hle_mod_fn_2_33DA0(ppc_context *ctx, uint8_t *base) {
    uint32_t np = ctx->r[3];
    /* a Classic Controller can be split from its remote with - (module feature) */
    uint32_t rm = R32(G_REMOCON_MNG);
    for (uint32_t plr = 0; plr < 8; plr++) {
        uint32_t con = R32(rm + 4 + 4 * plr), sm = R32(con + 144);
        if (!gcall(ctx, base, VFN(sm, 16), 2, sm, G_SETUP_STATE_ID)) continue;          /* isSetup */
        if ((R32(con + 12) & ~3u) == 8 || R32(con + 16) != 4) continue;                  /* split already / not Classic */
        uint32_t core = R32(R32(G_GAME_KEY) + 4 + 4 * plr);
        if (R8(core + 30) & 0x10) gcall(ctx, base, MFN_SPLIT_EXTENSION, 1, con);         /* - pressed */
    }
    if (np_back_wait) {                                                   /* Back pressed: fading out */
        if (np_leave(ctx, base, np, 1, ST_NP_EXIT_ANIME_END_CHECK)) np_back_wait = 0;
        return;
    }
    uint32_t count = R32(np + NP_PLAYER_COUNT); if (count > 8) count = 8;
    for (uint32_t cc = 0; cc < count; cc++) if (R8(R32(np + NP_CC_BASE + 4 * cc) + CB_BUSY)) return;
    int wmap = R16(G_NOW_SCENE) == SCENE_WORLD_MAP;
    if (np_check_cancel(ctx, base, np)) {
        play_se(ctx, base, wmap ? SE_SYS_DECIDE : SE_SYS_BACK);
        if (wmap) { np_leave(ctx, base, np, 0, ST_NP_EXIT_ANIME_END_CHECK); return; }
        np_back_wait = 1;
        if (np_leave(ctx, base, np, 1, ST_NP_EXIT_ANIME_END_CHECK)) np_back_wait = 0;
        return;
    }
    if (wmap) return;
    if (in_setup() && is_multi() && count == 8) {
        /* Multiplayer: Start Game once players 1 and 2 have chosen and nobody who joined is still choosing */
        for (uint32_t cc = 0; cc < count; cc++) {
            uint32_t b = R32(np + NP_CC_BASE + 4 * cc);
            if (R8(b + CB_DECIDED)) continue;
            if (cc < 2 || base_joined(ctx, base, b)) return;
        }
    } else {
        for (uint32_t cc = 0; cc < count; cc++) if (!R8(R32(np + NP_CC_BASE + 4 * cc) + CB_DECIDED)) return;
    }
    /* everyone chose: the Start Game button comes (remember what that changes, for taking a
       choice back - singleplayer, below) */
    for (uint32_t i = 0; i < 8; i++) {
        uint32_t ind = R32(np + NP_CC_INDICATOR + 4 * i), tdp = R32(np + NP_2DPLAYER + 4 * i);
        for (int k = 0; k < 2; k++) np_snap.ind[i][k] = ind && R32(ind + NP_IND_PANES + 4 * k) ? R8(R32(ind + NP_IND_PANES + 4 * k) + 0xBB) : 0;
        np_snap.tdp[i] = tdp ? R8(tdp + TDP_FLAG) : 0;
    }
    np_snap.flag = R8(np + NP_BUTTONS_FLAG);
    np_buttons = in_setup() && !is_multi() ? np : 0;
    for (uint32_t cc = 0; cc < count; cc++) W8(R32(np + NP_CC_BASE + 4 * cc) + CB_EXIT, 1);
    change_state(ctx, base, np + NP_STATE, ST_NP_INFO_WINDOW_EXIT_WAIT);
}

/* dCharacterChangeSelectBase_c::executeState_SelectStartWait ("Join": 2 brings the card): a
   card whose character was taken back (singleplayer, above) comes back by itself */
void hle_fn_2_2DF0(ppc_context *ctx, uint8_t *base) {
    uint32_t b = ctx->r[3];
    if (b == cb_rejoin && in_setup() && !is_multi()) {
        cb_rejoin = 0;
        change_state(ctx, base, b + CB_STATE, ST_CB_BUTTON_EXIT_ANIME);
        return;
    }
    orig_fn_2_2DF0(ctx, base);
}

/* executeState_ButtonSelect. Singleplayer: only Start Game (centred; the Back button is gone -
   "Back 1" shows instead, see gs_layout_draw), and 1 takes the character back: the select goes
   back to choosing (1 again: back to the File Select, NowEntrantRecruit). Multiplayer: the
   module's (Start Game / Back). */
void hle_mod_fn_2_343F0(ppc_context *ctx, uint8_t *base) {
    uint32_t np = ctx->r[3];
    if (!in_setup() || is_multi() || np != np_buttons) { orig_mod_fn_2_343F0(ctx, base); return; }
    if (gcall(ctx, base, A_CHK_CANCEL, 1, 0)) {
        uint32_t count = R32(np + NP_PLAYER_COUNT); if (count > 8) count = 8;
        /* the button goes (its animations back to their first frame, as before it came in);
           what it hid comes back */
        for (uint32_t g = NPA_IN_FIRST; g <= NPA_ON_LAST; g++) gcall(ctx, base, A_ANIM_RESET, 3, np + NP_LAYOUT, g, 0);
        for (uint32_t i = 0; i < 8; i++) {
            uint32_t ind = R32(np + NP_CC_INDICATOR + 4 * i), tdp = R32(np + NP_2DPLAYER + 4 * i);
            for (int k = 0; k < 2; k++) if (ind && R32(ind + NP_IND_PANES + 4 * k)) W8(R32(ind + NP_IND_PANES + 4 * k) + 0xBB, np_snap.ind[i][k]);
            if (tdp) W8(tdp + TDP_FLAG, np_snap.tdp[i]);
        }
        W8(np + NP_BUTTONS_FLAG, np_snap.flag);
        /* player 1 takes the choice back, as the card does when 1 is pressed on it (PlayerDisp) */
        for (uint32_t cc = 0; cc < count; cc++) W8(R32(np + NP_CC_BASE + 4 * cc) + CB_EXIT, 0);
        uint32_t b = R32(np + NP_CC_BASE), ec = R32(b + CB_ENTER_COUNT);
        play_se(ctx, base, SE_SYS_BACK);
        if (ec) W32(ec, (int)R32(ec) > 1 ? R32(ec) - 1 : 0);
        chars_keep_choice(0);                                             /* the card comes back with it */
        cb_rejoin = b;
        change_state(ctx, base, b + CB_STATE, ST_CB_PLAYER_EXIT_WAIT);
        np_buttons = 0;
        change_state(ctx, base, np + NP_STATE, ST_NP_NOW_ENTRANT_RECRUIT);
        rt_log("setup", "character select: player 1 takes the character back");
        return;
    }
    /* left / right: nothing to move to */
    W32(np + NP_ON_BUTTON, 0);
    uint32_t core = R32(R32(G_GAME_KEY) + 4 + 4 * R32(G_CUR_CORE)), trig = core ? R32(core + 28) : 0;
    if (core) W32(core + 28, trig & ~0xCu);
    orig_mod_fn_2_343F0(ctx, base);
    if (core) W32(core + 28, R32(core + 28) | (trig & 0xCu));
}

/* executeState_ButtonDecision: Start Game / Back was pressed; after its animation the screen goes */
void hle_mod_fn_2_345C0(ppc_context *ctx, uint8_t *base) {
    uint32_t np = ctx->r[3];
    if (gcall(ctx, base, A_IS_ANIM_ON, 2, np + NP_LAYOUT, (uint32_t)-1)) return;
    if (in_setup()) {                                                     /* fade out with the screen in place */
        if (!np_exit_wait) { np_exit_wait = 1; fade_out(ctx, base); return; }
        if (!screen_black(ctx, base)) return;
        np_exit_wait = 0;
    }
    change_state(ctx, base, np + NP_STATE, ST_NP_EXIT_ANIME_END_CHECK);
}

/* ======================================================= input */
/* game input while the setup scene changes screens is dropped; Game Select takes only 2/A
   (choose) and 1/B (back) */
enum { B_LEFT = 0x0001, B_RIGHT = 0x0002, B_DOWN = 0x0004, B_UP = 0x0008, B_PLUS = 0x0010, B_2 = 0x0100, B_1 = 0x0200,
       B_B = 0x0400, B_A = 0x0800, B_MINUS = 0x1000, B_HOME = 0x8000 };
static int fs_screen_live;               /* the file select layout was drawn lately */
static int confirm_held;                 /* Game Select: 2/A went down on a locked game and are still held */
static uint64_t fs_drawn_frame;
uint32_t gs_filter_buttons(uint32_t b) {
    static uint32_t prev; uint32_t pressed = b & ~prev; prev = b;     /* (kept up to date on every screen: a held button is no new press) */
    reset_if_left();
    if (!in_setup() || !gs_scene) return b;
    if (smb3_active()) {                                                  /* SMB3 has the buttons; + (or HOME) pauses it */
        if (smb3_paused()) menu_smb3_pause_input(pressed);
        else { smb3_input(b); if (pressed & (B_PLUS | B_HOME)) smb3_set_paused(1); }
        return b & ~0xFFFFu;
    }
    if (pending >= 0 || fs_fade_in_wait || char_fade_in_wait || np_exit_wait || np_back_wait || fader_seen != FADER_HIDDEN) return b & ~0xFFFFu;
    fs_screen_live = g_frames_presented - fs_drawn_frame <= 3;
    if (phase == PH_CHAR && !is_multi()) { uint32_t charsel_input(uint32_t b, uint32_t pressed); b = charsel_input(b, pressed); }   /* the grid */
    if (phase != PH_GAME) confirm_held = 0;
    if (phase == PH_GAME && fs_screen_live) {
        /* left/right (the remote held sideways: up/down) picks the card's game */
        int dir = (pressed & B_UP) ? -1 : (pressed & B_DOWN) ? 1 : 0;
        if (dir) {                                                        /* (the carousel turns: rt carousel above) */
            game_sel = (game_sel + dir + games_n()) % games_n();
            spin += (float)dir; if (spin > 1.5f) spin = 1.5f; if (spin < -1.5f) spin = -1.5f;
            rt_log("setup", "Game Select: game %d of %d", game_sel + 1, games_n());
        }
        b &= ~(uint32_t)(B_LEFT | B_RIGHT | B_UP | B_DOWN | B_PLUS | B_MINUS);
        /* a placeholder game (locked) can't be chosen: 2/A are dropped there, and stay dropped
           while held (turning to a game with 2 held is no press of 2) */
        if (game_locked(game_sel) && (b & (B_2 | B_A))) confirm_held = 1;
        if (confirm_held) { if (b & (B_2 | B_A)) b &= ~(uint32_t)(B_2 | B_A); else confirm_held = 0; }
    }
    else if (phase == PH_FILE && fs_screen_live && menu_singleplayer()) b &= ~(uint32_t)B_LEFT;   /* (down, sideways: the hidden versus buttons) */
    return b;
}
/* the character select is up and settled (rt_menu.c: the host starts an online game here) */
int gs_char_select_ready(void) { return in_setup() && gs_scene && phase == PH_CHAR && pending < 0 && !char_fade_in_wait && !np_exit_wait && !np_back_wait; }
int gs_busy(void) { return in_setup() && (pending >= 0 || fs_fade_in_wait || char_fade_in_wait || np_exit_wait || np_back_wait); }

/* ======================================================= layouts */
static float rdf(uint32_t a) { uint32_t u = R32(a); float f; memcpy(&f, &u, 4); return f; }
static void wrf(uint32_t a, float f) { uint32_t u; memcpy(&u, &f, 4); W32(a, u); }

/* text boxes: +0xD8 buffer (UTF-16BE), +0xFC buffer bytes, +0xFE length. The game's text is
   kept so it can be put back (Game Select -> File Select). */
#define MAXSAVE 24
static struct { uint32_t tb; uint16_t text[80]; int n; uint32_t size[2]; } saved[MAXSAVE]; static int nsaved; static uint32_t saved_scene;
static int text_read(uint32_t tb, uint16_t *out, int max) {
    uint32_t buf = R32(tb + 0xD8); int n = R16(tb + 0xFE);
    if (!buf || n > max) n = buf ? max : 0;
    for (int i = 0; i < n; i++) out[i] = R16(buf + 2 * i);
    return n;
}
static void text_write(uint32_t tb, const uint16_t *s, int n) {
    uint32_t buf = R32(tb + 0xD8); int cap = R16(tb + 0xFC) / 2 - 1;
    if (!buf || cap <= 0) return;
    if (n > cap) n = cap;
    for (int i = 0; i < n; i++) W16(buf + 2 * i, s[i]);
    W16(buf + 2 * n, 0); W16(tb + 0xFE, (uint16_t)n);
}
static void saves_check_scene(void) { if (saved_scene != gs_scene) { nsaved = 0; saved_scene = gs_scene; } }
/* show s in the text box; keep_tail keeps the game's text from its first button glyph on;
   scale (if not 0) changes the font size from the game's */
static void text_set_scaled(uint32_t tb, const char *s, int keep_tail, float scale) {
    if (!tb) return;
    saves_check_scene();
    int k; for (k = 0; k < nsaved && saved[k].tb != tb; k++) ;
    if (k == nsaved) { if (nsaved == MAXSAVE) return; saved[k].tb = tb; saved[k].n = text_read(tb, saved[k].text, 80);
                       saved[k].size[0] = R32(tb + 0xE8); saved[k].size[1] = R32(tb + 0xEC); nsaved++; }
    if (scale > 0) { float f; memcpy(&f, &saved[k].size[0], 4); wrf(tb + 0xE8, f * scale); memcpy(&f, &saved[k].size[1], 4); wrf(tb + 0xEC, f * scale); }
    uint16_t t[96]; int n = 0;
    for (; *s && n < 80; s++) t[n++] = (uint8_t)*s;
    if (keep_tail) {
        int i; for (i = 0; i < saved[k].n && saved[k].text[i] >= 0x20 && saved[k].text[i] < 0x7F; i++) ;
        for (; i < saved[k].n && n < 95; i++) t[n++] = saved[k].text[i];
    }
    uint16_t cur[96]; int cn = text_read(tb, cur, 96);
    if (cn != n || memcmp(cur, t, 2 * n)) text_write(tb, t, n);
}
static void text_set(uint32_t tb, const char *s, int keep_tail) { text_set_scaled(tb, s, keep_tail, 0); }
static void text_restore(uint32_t tb) {
    if (!tb || saved_scene != gs_scene) return;
    for (int k = 0; k < nsaved; k++) if (saved[k].tb == tb) {
        text_write(tb, saved[k].text, saved[k].n); W32(tb + 0xE8, saved[k].size[0]); W32(tb + 0xEC, saved[k].size[1]);
        saved[k] = saved[--nsaved]; return;
    }
}
/* visibility changed from what the game set; put back when no longer wanted */
#define MAXVIS 32
static struct { uint32_t pane; uint8_t flags; } vsaved[MAXVIS]; static int nvsaved; static uint32_t vsaved_scene;
static void vis_set(uint32_t pane, int v) {
    if (!pane) return;
    if (vsaved_scene != gs_scene) { nvsaved = 0; vsaved_scene = gs_scene; }
    int k; for (k = 0; k < nvsaved && vsaved[k].pane != pane; k++) ;
    if (k == nvsaved) { if (nvsaved == MAXVIS) return; vsaved[k].pane = pane; vsaved[k].flags = R8(pane + 0xBB); nvsaved++; }
    lyt_set_visible(pane, v);
}
static void vis_restore(uint32_t pane) {
    if (!pane || vsaved_scene != gs_scene) return;
    for (int k = 0; k < nvsaved; k++) if (vsaved[k].pane == pane) { W8(pane + 0xBB, vsaved[k].flags); vsaved[k] = vsaved[--nvsaved]; return; }
}
/* hide (or show) a pane while cond holds, as the game had it otherwise */
static void show_if(uint32_t root, const char *name, int cond, int v) { uint32_t p = lyt_find_pane(root, name); if (cond) vis_set(p, v); else vis_restore(p); }

/* a pane moved from where the game put it (the game may set it again: then that is the new base) */
#define MAXSHIFT 32
static struct { uint32_t pane; int axis; float base, written; } shifts[MAXSHIFT]; static int nshift; static uint32_t shift_scene;
static void pane_shift(uint32_t pane, int axis, float d) {
    if (!pane) return;
    if (shift_scene != gs_scene) { nshift = 0; shift_scene = gs_scene; }
    uint32_t a = pane + 0x2C + 4 * axis;                                  /* mTranslate.x / .y */
    int k; for (k = 0; k < nshift && (shifts[k].pane != pane || shifts[k].axis != axis); k++) ;
    float v = rdf(a);
    if (k == nshift) { if (nshift == MAXSHIFT) return; nshift++; shifts[k].pane = pane; shifts[k].axis = axis; shifts[k].base = v; }
    else if (v != shifts[k].written) shifts[k].base = v;
    shifts[k].written = shifts[k].base + d;
    wrf(a, shifts[k].written);
}


/* a pane's scale / alpha changed from what the game set, as a factor of it (the game may set it
   again - its opening animation does: then that is the new base); factor 1 = the game's own */
#define MAXFMUL 16
static struct { uint32_t pane; int what; float base, written; } fmuls[MAXFMUL]; static int nfmul; static uint32_t fmul_scene;
static void pane_mul(uint32_t pane, int what, float m) {          /* what: 0 scale x, 2 scale y, 1 alpha */
    if (!pane) return;
    if (fmul_scene != gs_scene) { nfmul = 0; fmul_scene = gs_scene; }
    int k; for (k = 0; k < nfmul && (fmuls[k].pane != pane || fmuls[k].what != what); k++) ;
    uint32_t at = pane + (what == 2 ? 0x48 : 0x44);
    float v = what == 1 ? (float)lyt_get_alpha(pane) : rdf(at);
    if (k == nfmul) { if (nfmul == MAXFMUL) return; nfmul++; fmuls[k].pane = pane; fmuls[k].what = what; fmuls[k].base = v; }
    else if (v != fmuls[k].written) fmuls[k].base = v;
    float w = fmuls[k].base * m;
    if (what == 1) { int a = (int)(w + 0.5f); if (a < 0) a = 0; if (a > 255) a = 255; lyt_set_alpha(pane, (uint8_t)a); fmuls[k].written = (float)a; }
    else { wrf(at, w); fmuls[k].written = w; }
}

/* ======================================================= game portraits
 * Game Select: a card per game. NSMBW and SMB3 can be played; every other picture in
 * ui/graphics/gameportrait/ (.png / .jpg / .jpeg, except locked.png) is a placeholder game, after
 * them in name order: its card can be turned to (hovered) but not chosen, and shows locked.png
 * over its picture (centred, about half the picture's size, drawn into the texture when it is
 * made). Each card shows its game's picture (any size; transparent pixels stay transparent;
 * file names in any case). The card takes the picture's shape: as tall as before, as wide as the
 * picture (its white border stays 5 px all round), and the game's name shows only when there is
 * no picture. The pictures are GX CMPR (DXT1) textures in our guest memory (GP_MEM..GP_MEM_END,
 * 320 KB - the guest memory past MEM1 is all spoken for), each made small enough that all of
 * them fit: about 280 x 390 for a portrait with 6 games. */
typedef struct { char id[32], label[32], file[64]; int locked; } game_t;   /* file: in gameportrait/ ("" none) */
#define MAXGAMES 16
static game_t games[MAXGAMES]; static int ngames;                           /* (order: GAME_NSMBW, GAME_SMB3, placeholders) */
static char lock_file[64];                                                   /* locked.png (any case / extension) */
static int name_eq(const char *a, const char *b) {
    for (; *a && *b; a++, b++) if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) return 0;
    return *a == *b;
}
static int name_cmp(const void *x, const void *y) {
    const char *a = x, *b = y;
    for (; *a && tolower((unsigned char)*a) == tolower((unsigned char)*b); a++, b++) ;
    return tolower((unsigned char)*a) - tolower((unsigned char)*b);
}
static void games_scan(void) {                                               /* (once: the first time the list is wanted) */
    static const char *const play[][2] = { {"nsmbw", "NSMBW"}, {"smb3", "SMB3"} };
    ngames = 0; lock_file[0] = 0;
    for (int i = 0; i < 2; i++) { game_t *g = &games[ngames++]; memset(g, 0, sizeof *g); strcpy(g->id, play[i][0]); strcpy(g->label, play[i][1]); }
    char dir[1200]; snprintf(dir, sizeof dir, "%s/ui/graphics/gameportrait", g_root);
    static char names[64][64]; int nn = 0;
    DIR *d = opendir(dir);
    if (d) {
        struct dirent *de;
        while ((de = readdir(d)) && nn < 64) {
            const char *dot = strrchr(de->d_name, '.');
            if (!dot || dot == de->d_name || strlen(de->d_name) >= 64 || dot - de->d_name >= 32) continue;
            if (!name_eq(dot, ".png") && !name_eq(dot, ".jpg") && !name_eq(dot, ".jpeg")) continue;
            strcpy(names[nn++], de->d_name);
        }
        closedir(d);
    }
    qsort(names, (size_t)nn, sizeof names[0], name_cmp);
    for (int i = 0; i < nn; i++) {
        char stem[32]; size_t n = (size_t)(strrchr(names[i], '.') - names[i]); memcpy(stem, names[i], n); stem[n] = 0;
        if (name_eq(stem, "locked")) { if (!lock_file[0]) strcpy(lock_file, names[i]); continue; }
        int k; for (k = 0; k < ngames && !name_eq(games[k].id, stem); k++) ;
        if (k < ngames) { if (!games[k].file[0]) strcpy(games[k].file, names[i]); continue; }
        if (ngames == MAXGAMES) { rt_log("setup", "game pictures: more than %d games, %s left out", MAXGAMES, names[i]); continue; }
        game_t *g = &games[ngames++]; memset(g, 0, sizeof *g);
        strcpy(g->id, stem); strcpy(g->label, stem); strcpy(g->file, names[i]); g->locked = 1;
    }
    char list[512]; size_t o = 0; list[0] = 0;
    for (int i = 0; i < ngames && o < sizeof list - 48; i++) o += (size_t)snprintf(list + o, sizeof list - o, "%s%s%s", i ? ", " : "", games[i].label, games[i].locked ? " (locked)" : "");
    rt_log("setup", "games: %s%s", list, lock_file[0] ? "" : " - no locked.png");
}
static int games_n(void) { if (!ngames) games_scan(); return ngames; }
static int game_locked(int g) { return g >= 0 && g < games_n() && games[g].locked; }
static const char *game_label(int g) { return g >= 0 && g < games_n() ? games[g].label : "?"; }
#define GP_MEM      0x81870000u                             /* free: past the module's loader scratch, before rt_retro's */
#define GP_MEM_END  0x818C0000u                             /* (above: the SMB3 stage's, smb3_stage.c) */
#define GP_MAX      512
typedef struct { int state; uint32_t tex; int tw, th; float aspect; } gport_t;   /* state 0 untried, 1 ok, -1 none */
static gport_t gports[MAXGAMES];
/* texels per picture so that every game's picture fits (10% kept for the 8 x 8 rounding and alignment) */
static double gp_budget(void) {
    int n = 0; for (int i = 0; i < games_n(); i++) if (games[i].file[0]) n++;
    if (n < 1) n = 1;
    return (double)(GP_MEM_END - GP_MEM - 32u * (uint32_t)n) * 2.0 / n * 0.9;
}
static uint32_t gp_next = GP_MEM;
static int gp_borrowed;
void boot_screen_mem_lost(void);

/* area-average resample of 0xAARRGGBB to dw x dh (straight alpha: colour weighted by alpha) */
static float *gp_resample(const uint32_t *px, int w, int h, int dw, int dh) {
    float *row = calloc((size_t)dw * h * 4, sizeof(float)), *out = calloc((size_t)dw * dh * 4, sizeof(float));
    double sx = (double)w / dw, sy = (double)h / dh;
    for (int y = 0; y < h; y++) for (int x = 0; x < dw; x++) {      /* horizontal */
        double a0 = x * sx, a1 = a0 + sx, acc[4] = {0}, tw = 0;
        for (int i = (int)a0; i < w && i < a1; i++) {
            double wgt = (i + 1 < a1 ? i + 1 : a1) - (i > a0 ? i : a0); if (wgt <= 0) continue;
            uint32_t c = px[(size_t)y * w + i]; double al = (c >> 24) / 255.0;
            acc[0] += wgt * al * ((c >> 16) & 255); acc[1] += wgt * al * ((c >> 8) & 255); acc[2] += wgt * al * (c & 255); acc[3] += wgt * al; tw += wgt;
        }
        float *o = row + ((size_t)y * dw + x) * 4; for (int k = 0; k < 4; k++) o[k] = (float)(acc[k] / tw);
    }
    for (int x = 0; x < dw; x++) for (int y = 0; y < dh; y++) {     /* vertical */
        double a0 = y * sy, a1 = a0 + sy, acc[4] = {0}, tw = 0;
        for (int i = (int)a0; i < h && i < a1; i++) {
            double wgt = (i + 1 < a1 ? i + 1 : a1) - (i > a0 ? i : a0); if (wgt <= 0) continue;
            const float *r = row + ((size_t)i * dw + x) * 4; for (int k = 0; k < 4; k++) acc[k] += wgt * r[k]; tw += wgt;
        }
        float *o = out + ((size_t)y * dw + x) * 4;
        double al = acc[3] / tw;                                    /* back to straight colour */
        for (int k = 0; k < 3; k++) o[k] = al > 0 ? (float)(acc[k] / tw / al) : 0; o[3] = (float)(al * 255.0);
    }
    free(row); return out;
}
static uint16_t rgb565(const float c[3]) {
    int r = (int)(c[0] * 31 / 255 + 0.5f), g = (int)(c[1] * 63 / 255 + 0.5f), b = (int)(c[2] * 31 / 255 + 0.5f);
    r = r < 0 ? 0 : r > 31 ? 31 : r; g = g < 0 ? 0 : g > 63 ? 63 : g; b = b < 0 ? 0 : b > 31 ? 31 : b;
    return (uint16_t)(r << 11 | g << 5 | b);
}
static void from565(uint16_t v, float c[3]) { int r = v >> 11, g = (v >> 5) & 63, b = v & 31; c[0] = (float)(r << 3 | r >> 2); c[1] = (float)(g << 2 | g >> 4); c[2] = (float)(b << 3 | b >> 2); }
/* the indices for endpoints c0, c1 (opaque: 4 colours, c0 > c1; with holes: 3 + transparent, c0 <= c1); returns the error */
static double dxt_fit(const float px[16][4], uint16_t c0, uint16_t c1, uint8_t idx[16]) {
    float p[4][3], a[3], b[3]; from565(c0, a); from565(c1, b);
    int four = c0 > c1;
    for (int k = 0; k < 3; k++) { p[0][k] = a[k]; p[1][k] = b[k];
        if (four) { p[2][k] = (2 * a[k] + b[k]) / 3; p[3][k] = (a[k] + 2 * b[k]) / 3; } else { p[2][k] = (a[k] + b[k]) / 2; p[3][k] = 0; } }
    double err = 0;
    for (int i = 0; i < 16; i++) {
        if (px[i][3] < 128) { idx[i] = 3; continue; }               /* (only asked for with holes: 3-colour mode) */
        int best = 0; double bd = 1e30;
        for (int j = 0; j < (four ? 4 : 3); j++) { double d = 0; for (int k = 0; k < 3; k++) { double e = px[i][k] - p[j][k]; d += e * e; } if (d < bd) { bd = d; best = j; } }
        idx[i] = (uint8_t)best; err += bd;
    }
    return err;
}
/* one 4x4 block -> 8 bytes of GX CMPR (big-endian colours; a row per byte, left pixel in the top bits) */
static void dxt_block(const float px[16][4], uint8_t out[8]) {
    int holes = 0, n = 0; float mean[3] = {0};
    for (int i = 0; i < 16; i++) { if (px[i][3] < 128) holes = 1; else { n++; for (int k = 0; k < 3; k++) mean[k] += px[i][k]; } }
    uint16_t c0 = 0, c1 = 0; uint8_t idx[16];
    if (!n) { memset(idx, 3, 16); goto write; }
    for (int k = 0; k < 3; k++) mean[k] /= n;
    {   double cov[6] = {0};                                        /* principal axis (power iteration) */
        for (int i = 0; i < 16; i++) if (px[i][3] >= 128) { double d[3]; for (int k = 0; k < 3; k++) d[k] = px[i][k] - mean[k];
            cov[0] += d[0] * d[0]; cov[1] += d[0] * d[1]; cov[2] += d[0] * d[2]; cov[3] += d[1] * d[1]; cov[4] += d[1] * d[2]; cov[5] += d[2] * d[2]; }
        double v[3] = {0.577, 0.577, 0.577};
        for (int it = 0; it < 8; it++) {
            double nv[3] = {cov[0] * v[0] + cov[1] * v[1] + cov[2] * v[2], cov[1] * v[0] + cov[3] * v[1] + cov[4] * v[2], cov[2] * v[0] + cov[4] * v[1] + cov[5] * v[2]};
            double l = sqrt(nv[0] * nv[0] + nv[1] * nv[1] + nv[2] * nv[2]); if (l < 1e-9) break;
            for (int k = 0; k < 3; k++) v[k] = nv[k] / l;
        }
        double tmin = 1e30, tmax = -1e30;
        for (int i = 0; i < 16; i++) if (px[i][3] >= 128) { double t = 0; for (int k = 0; k < 3; k++) t += (px[i][k] - mean[k]) * v[k]; if (t < tmin) tmin = t; if (t > tmax) tmax = t; }
        float e0[3], e1[3]; for (int k = 0; k < 3; k++) { e0[k] = (float)(mean[k] + v[k] * tmax); e1[k] = (float)(mean[k] + v[k] * tmin); }
        c0 = rgb565(e0); c1 = rgb565(e1);
    }
    if (holes ? c0 > c1 : c0 < c1) { uint16_t t = c0; c0 = c1; c1 = t; }
    if (!holes && c0 == c1) { memset(idx, 0, 16); goto write; }
    double err = dxt_fit(px, c0, c1, idx);
    if (!holes) {                                                   /* least squares on these indices, once */
        static const float wa[4] = {1, 0, 2.0f / 3, 1.0f / 3};
        double aa = 0, ab = 0, bb = 0, ax[3] = {0}, bx[3] = {0};
        for (int i = 0; i < 16; i++) { double x = wa[idx[i]], y = 1 - x; aa += x * x; ab += x * y; bb += y * y;
            for (int k = 0; k < 3; k++) { ax[k] += x * px[i][k]; bx[k] += y * px[i][k]; } }
        double det = aa * bb - ab * ab;
        if (fabs(det) > 1e-6) {
            float e0[3], e1[3];
            for (int k = 0; k < 3; k++) { e0[k] = (float)((ax[k] * bb - bx[k] * ab) / det); e1[k] = (float)((bx[k] * aa - ax[k] * ab) / det); }
            uint16_t n0 = rgb565(e0), n1 = rgb565(e1); if (n0 < n1) { uint16_t t = n0; n0 = n1; n1 = t; }
            uint8_t idx2[16];
            if (n0 != n1 && dxt_fit(px, n0, n1, idx2) < err) { c0 = n0; c1 = n1; memcpy(idx, idx2, 16); }
        }
    }
write:
    out[0] = (uint8_t)(c0 >> 8); out[1] = (uint8_t)c0; out[2] = (uint8_t)(c1 >> 8); out[3] = (uint8_t)c1;
    for (int r = 0; r < 4; r++) out[4 + r] = (uint8_t)(idx[r * 4] << 6 | idx[r * 4 + 1] << 4 | idx[r * 4 + 2] << 2 | idx[r * 4 + 3]);
}
/* a placeholder's picture: locked.png over it, centred, fitted to half its width and height
   (straight alpha, as gp_resample gives it) */
static void gp_lock(float *img, int tw, int th) {
    static uint32_t *lpx; static int lw, lh, tried;
    if (!tried) {
        tried = 1;
        if (lock_file[0]) { char path[1200]; snprintf(path, sizeof path, "%s/ui/graphics/gameportrait/%s", g_root, lock_file); lpx = ui_load_png(path, &lw, &lh); }
        if (!lpx) rt_log("setup", "locked.png missing: placeholder games show no lock");
    }
    if (!lpx) return;
    double s = 0.5 * tw / lw; if (0.5 * th / lh < s) s = 0.5 * th / lh;
    int dw = (int)(lw * s + 0.5), dh = (int)(lh * s + 0.5);
    if (dw < 1 || dh < 1) return;
    float *L = gp_resample(lpx, lw, lh, dw, dh);
    int ox = (tw - dw) / 2, oy = (th - dh) / 2;
    for (int y = 0; y < dh; y++) for (int x = 0; x < dw; x++) {
        const float *l = L + ((size_t)y * dw + x) * 4; float *o = img + ((size_t)(oy + y) * tw + ox + x) * 4;
        float la = l[3] / 255.0f, da = o[3] / 255.0f * (1 - la), oa = la + da;
        for (int k = 0; k < 3; k++) o[k] = oa > 0 ? (l[k] * la + o[k] * da) / oa : 0;
        o[3] = oa * 255.0f;
    }
    free(L);
}
static gport_t *game_portrait(int g) {
    if (g < 0 || g >= games_n()) return NULL;
    gport_t *p = &gports[g];
    if (p->state) return p->state > 0 ? p : NULL;
    p->state = -1;
    if (!games[g].file[0]) return NULL;
    char path[1200]; snprintf(path, sizeof path, "%s/ui/graphics/gameportrait/%s", g_root, games[g].file);
    int w, h; uint32_t *px = ui_load_png(path, &w, &h);
    if (!px) { rt_log("setup", "%s: can't be read", path); return NULL; }
    /* fit GP_MAX and the share of the memory (never bigger than it is), in whole 8x8 tiles */
    double sc = (double)GP_MAX / (w > h ? w : h), sa = sqrt(gp_budget() / ((double)w * h)); if (sa < sc) sc = sa; if (sc > 1) sc = 1;
    int tw = (int)(w * sc / 8 + 0.5) * 8, th = (int)(h * sc / 8 + 0.5) * 8;
    if (tw < 8) tw = 8; if (th < 8) th = 8;
    if (gp_borrowed) { gp_borrowed = 0; boot_screen_mem_lost(); }
    uint32_t bytes = (uint32_t)tw * th / 2, at = (gp_next + 31) & ~31u;
    if (at + bytes > GP_MEM_END) { free(px); rt_log("setup", "%s: no room for another game picture", path); return NULL; }
    float *img = gp_resample(px, w, h, tw, th); free(px);
    if (games[g].locked) gp_lock(img, tw, th);
    uint8_t *dst = G(at);
    for (int ty = 0; ty < th; ty += 8) for (int tx = 0; tx < tw; tx += 8)
        for (int sb = 0; sb < 4; sb++) {                            /* (an 8x8 tile: its four 4x4 blocks, row by row) */
            int bx = tx + (sb & 1) * 4, by = ty + (sb >> 1) * 4; float blk[16][4];
            for (int i = 0; i < 16; i++) memcpy(blk[i], img + ((size_t)(by + (i >> 2)) * tw + bx + (i & 3)) * 4, 4 * sizeof(float));
            dxt_block(blk, dst); dst += 8;
        }
    free(img);
    p->tex = at; p->tw = tw; p->th = th; p->aspect = (float)w / h; p->state = 1;
    gp_next = at + bytes;
    rt_log("setup", "game picture %s: %dx%d, kept at %dx%d (%u KB)%s", games[g].id, w, h, tw, th, bytes / 1024, games[g].locked ? ", locked" : "");
    return p;
}
/* the boot's keyboard picture (rt_bootscreen.c) borrows the whole region: it is shown long
   before Game Select; the first game picture after it takes the region back */
uint32_t gs_ui_mem_borrow(uint32_t bytes) {
    if (bytes > GP_MEM_END - GP_MEM) return 0;
    memset(gports, 0, sizeof gports); gp_next = GP_MEM; gp_borrowed = 1;
    return GP_MEM;
}
static void *game_portrait_any(int g) { return game_portrait(g); }
static int cur_game(void) { return game_sel >= 0 && game_sel < games_n() ? game_sel : 0; }

/* ---- the Game Select carousel ----
   Card slot 1 (the middle, where the cursor is) shows the chosen game, slots 0 / 2 the one before
   / after it (wrapping). A turn leaves `spin` (+1: just turned right), which runs down to 0: each
   card is drawn at position (slot - 1) + spin on the arc - so the new game slides in from the side
   it came from. Past 1.7 a card is gone (one coming in from beyond the edge fades in). */
#define CAR_DX 205.0f                                  /* the distance between neighbours */
#define CAR_SLOT_X 190.0f                              /* (where the file select puts its cards) */
static uint64_t spin_frame;
static int slot_game(int slot) { int n = games_n(); return ((game_sel + slot - 1) % n + n) % n; }
static float slot_pos(int slot) { return (float)(slot - 1) + spin; }
static void spin_step(void) {                          /* (once per frame) */
    if (spin_frame == g_frames_presented) return;
    spin_frame = g_frames_presented;
    spin *= 0.80f; if (fabsf(spin) < 0.005f) spin = 0;
}
static void carousel_place(uint32_t root, int slot) {  /* (before the matrices) */
    int on = phase == PH_GAME;
    float pos = on ? slot_pos(slot) : (float)(slot - 1), a = fabsf(pos), c = a < 1.6f ? a : 1.6f;
    pane_shift(root, 0, on ? pos * CAR_DX - (slot - 1) * CAR_SLOT_X : 0.0f);
    pane_shift(root, 1, on ? -9.0f * c * c : 0.0f);                       /* (an arc: the sides a little lower) */
    pane_mul(root, 0, on ? 1.0f - 0.27f * c : 1.0f); pane_mul(root, 2, on ? 1.0f - 0.27f * c : 1.0f);
    pane_mul(root, 1, !on ? 1.0f : a <= 1 ? 1.0f - 0.38f * a : a < 1.7f ? 0.62f * (1.7f - a) / 0.7f : 0.0f);
}

/* the card's picture pane shows the portrait: its texture and vertex colours (the card's
   blue-green gradient) are kept to put back, refreshed whenever they aren't ours (a new layout
   may reuse the pane's address) */
#define PIC_VTX      0xD8                                           /* nw4r::lyt::Picture: ut::Color[4] */
#define PANE_MAT     0x28
#define MAT_TEXMAP   0x40                                           /* the first TexMap: image, palette, u16 w, h, ..., u32 bits (format: top 4) */
static struct { uint32_t pane, texmap[7], vtx[4]; } gp_saved[3];   /* (one per card: the carousel pictures all three) */
static int gp_ours(uint32_t image) { return image >= GP_MEM && image < GP_MEM_END; }
static void cards_forget(void) { memset(gp_saved, 0, sizeof gp_saved); }
static void card_picture(uint32_t pane, gport_t *p) {
    uint32_t mat = pane ? R32(pane + PANE_MAT) : 0, tm = mat ? R32(mat + MAT_TEXMAP) : 0;
    if (!(tm >= 0x80000000u && tm < 0x94000000u)) return;
    int k; for (k = 0; k < 3 && gp_saved[k].pane != pane; k++) ;
    if (k == 3) {                                                   /* (not one of ours yet) */
        if (!p) return;                                             /* (nothing of ours there) */
        for (k = 0; k < 3 && gp_saved[k].pane; k++) ;
        if (k == 3) return;
        gp_saved[k].pane = pane;
    }
    if (!gp_ours(R32(tm))) { for (int i = 0; i < 7; i++) gp_saved[k].texmap[i] = R32(tm + 4 * i); for (int i = 0; i < 4; i++) gp_saved[k].vtx[i] = R32(pane + PIC_VTX + 4 * i); }
    if (p) {
        W32(tm, p->tex); W16(tm + 8, (uint16_t)p->tw); W16(tm + 10, (uint16_t)p->th);
        W32(tm + 0x18, (gp_saved[k].texmap[6] & 0x0FFFFFFFu) | (14u << 28));    /* GX_TF_CMPR */
        for (int i = 0; i < 4; i++) W32(pane + PIC_VTX + 4 * i, 0xFFFFFFFFu);
    } else {
        if (gp_ours(R32(tm))) {
            for (int i = 0; i < 7; i++) W32(tm + 4 * i, gp_saved[k].texmap[i]);
            for (int i = 0; i < 4; i++) W32(pane + PIC_VTX + 4 * i, gp_saved[k].vtx[i]);
        }
        gp_saved[k].pane = 0;                                       /* (back as the game had it) */
    }
}
/* the card's width changed from what the game set (the game may set it again: then that is the
   new base); d = 0 puts it back */
static void cursor_note(uint32_t pane, float wide, float narrow);
#define MAXWIDTH 32                                                 /* (Game Select: 3 cards x 7 card_panes) */
static struct { uint32_t pane; float base, written; } widths[MAXWIDTH]; static int nwidth; static uint32_t width_scene;
static void pane_narrow(uint32_t pane, float d) {
    if (!pane) return;
    if (width_scene != gs_scene) { nwidth = 0; width_scene = gs_scene; }
    int k; for (k = 0; k < nwidth && widths[k].pane != pane; k++) ;
    float v = rdf(pane + 0x4C);                                     /* mSize.width */
    if (d == 0) {
        if (k < nwidth) { if (v == widths[k].written) wrf(pane + 0x4C, widths[k].base); widths[k] = widths[--nwidth]; }
        return;
    }
    if (k == nwidth) { if (nwidth == MAXWIDTH) { rt_log("setup", "pane_narrow: table full (MAXWIDTH %d)", MAXWIDTH); return; } nwidth++; widths[k].pane = pane; widths[k].base = v; }
    else if (v != widths[k].written) widths[k].base = v;
    widths[k].written = widths[k].base - d;
    wrf(pane + 0x4C, widths[k].written);
    cursor_note(pane, widths[k].base, widths[k].written);
}
/* the select cursor (the four orange corners) took the card's size when it was set on it
   (dGameCom::SelectCursorSetup -> dSelectCursor_c: per cursor, 612 bytes from +0: +772 on,
   +773 the pane's name, +876 / +880 its width / height). A cursor on a card pane whose width
   we changed gets the width the card has now - both ways, as the game may set it up in the frame
   before our change or our putting back */
#define G_SELECT_CURSOR 0x8042A2C8u                                 /* dSelectCursor_c::m_instance (r13-21432) */
#define SC_STRIDE 612
#define SC_ON     772
#define SC_NAME   773
#define SC_WIDTH  876
static struct { char name[18]; float wide, narrow; } cfix[8]; static int ncfix;
static void cursor_note(uint32_t pane, float wide, float narrow) {
    char nm[18]; for (int i = 0; i < 17; i++) nm[i] = (char)R8(pane + 0xBC + i); nm[17] = 0;
    int k; for (k = 0; k < ncfix && strcmp(cfix[k].name, nm); k++) ;
    if (k == ncfix) { if (ncfix == 8) return; ncfix++; memcpy(cfix[k].name, nm, 18); }
    cfix[k].wide = wide; cfix[k].narrow = narrow;
}
static void cursor_fix(int narrowed) {
    uint32_t sc = R32(G_SELECT_CURSOR);
    if (!(sc >= 0x80000000u && sc < 0x94000000u)) return;
    for (int c = 0; c < 4; c++) {
        uint32_t e = sc + (uint32_t)c * SC_STRIDE;
        if (R8(e + SC_ON) != 1) continue;
        char nm[18]; for (int i = 0; i < 17; i++) nm[i] = (char)R8(e + SC_NAME + i); nm[17] = 0;
        for (int k = 0; k < ncfix; k++) if (!strcmp(cfix[k].name, nm)) {
            float w = rdf(e + SC_WIDTH), from = narrowed ? cfix[k].wide : cfix[k].narrow, to = narrowed ? cfix[k].narrow : cfix[k].wide;
            if (fabsf(w - from) < 0.01f && from != to) wrf(e + SC_WIDTH, to);
        }
    }
}
static const char *const card_panes[] = {"N_dateFile_00", "P_NumBase_01", "P_Shine_00", "W_dateFile_00", "W_shadow_00", "P_selectBase_00", "W_select_00"};

/* which of the setup scene's layouts this is */
enum { L_OTHER, L_FILE_SELECT, L_DATE_FILE, L_CHAR_SELECT, L_CARD };   /* L_CARD: player 1's card (slot: 0 base, 1 contents, 2 arrows, 3 indicator) */
static int which_layout(uint32_t layout, uint32_t root, int menu_kind, int *slot) {
    if (!in_setup() || !gs_scene) return L_OTHER;
    if (menu_kind == 2) return L_FILE_SELECT;
    uint32_t np = R32(gs_scene + GS_NUMPY);
    if (np && root == R32(np + NP_ROOT)) return L_CHAR_SELECT;
    if (np) {
        static const uint32_t parts[4] = {NP_CC_BASE, NP_CC_CONTENTS, NP_CC_ARROW, NP_CC_INDICATOR};
        for (int i = 0; i < 4; i++) { uint32_t o = R32(np + parts[i]); if (o && layout > o && layout - o < 0x1000) { *slot = i; return L_CARD; } }
    }
    for (int i = 0; i < 3; i++) {
        uint32_t df = R32(gs_scene + GS_DATEFILE + 4 * i);
        if (df && layout > df && layout - df < 0x1000) { *slot = i; return L_DATE_FILE; }
    }
    return L_OTHER;
}

/* singleplayer character select: the card on the left (the grid's preview, rt_charsel.c) */
static void card_calc(uint32_t root, int part) {
    int sp = phase == PH_CHAR && !is_multi() && part != 1;               /* (the contents follow the base) */
    pane_shift(root, 0, sp ? SP_CARD_DX : 0.0f);
}

/* a float the game sets, moved by d (the game may set it again: then that is the new base); d = 0
   puts it back */
#define MAXFSHIFT 16
static struct { uint32_t at; float base, written; } fshifts[MAXFSHIFT]; static int nfshift; static uint32_t fshift_scene;
static void float_shift(uint32_t at, float d) {
    if (fshift_scene != gs_scene) { nfshift = 0; fshift_scene = gs_scene; }
    int k; for (k = 0; k < nfshift && fshifts[k].at != at; k++) ;
    float v = rdf(at);
    if (d == 0) { if (k < nfshift) { if (v == fshifts[k].written) wrf(at, fshifts[k].base); fshifts[k] = fshifts[--nfshift]; } return; }
    if (k == nfshift) { if (nfshift == MAXFSHIFT) return; nfshift++; fshifts[k].at = at; fshifts[k].base = v; }
    else if (v != fshifts[k].written) fshifts[k].base = v;
    fshifts[k].written = fshifts[k].base + d;
    wrf(at, fshifts[k].written);
}
/* the figures (2D players, by body) stand above the card: singleplayer, it's on the left */
static void figures_place(int sp) {
    uint32_t np = R32(gs_scene + GS_NUMPY);
    if (!np) return;
    for (int t = 0; t < 8; t++) { uint32_t tdp = R32(np + NP_2DPLAYER + 4 * t); if (tdp) float_shift(tdp + TDP_POS_X, sp ? SP_CARD_DX : 0.0f); }
}

/* before the layout's matrices are computed: positions */
void gs_layout_calc(uint32_t layout, uint32_t root, int menu_kind) {
    int slot = -1, w = which_layout(layout, root, menu_kind, &slot);
    if (w == L_FILE_SELECT) {
        /* singleplayer / Game Select: no versus buttons, so the cards and title sit lower
           (70), then everything 16 up */
        float dy = (menu_singleplayer() || phase == PH_GAME) ? -70.0f + 16.0f : 0.0f;
        pane_shift(lyt_find_pane(root, "N_fileSelect_00"), 1, dy);
        pane_shift(lyt_find_pane(root, "N_titlePos_00"), 1, dy);
    } else if (w == L_DATE_FILE) {
        /* Game Select: the carousel; each card as wide as its game's picture (155 high) */
        int cur = (int)R32(R32(gs_scene + GS_FSEL) + FS_CHOICE);
        if (slot >= 0 && slot < 3) { if (slot == 1) spin_step(); carousel_place(root, slot); }
        gport_t *p = phase == PH_GAME && slot >= 0 ? game_portrait(slot_game(slot)) : NULL;
        float d = p ? 155.0f * (1.0f - p->aspect) : 0.0f;
        if (p && d == 0) d = -0.0001f;                              /* (a square picture: still ours) */
        for (unsigned i = 0; i < sizeof card_panes / sizeof card_panes[0]; i++) pane_narrow(lyt_find_pane(root, card_panes[i]), d);
        if (phase == PH_GAME ? slot == cur : slot == 0) cursor_fix(p != NULL);   /* (once per frame) */
    } else if (w == L_CARD) {
        card_calc(root, slot);
    } else if (w == L_CHAR_SELECT && is_multi()) {
        figures_place(0);
    } else if (w == L_CHAR_SELECT && !is_multi()) {
        figures_place(phase == PH_CHAR);
        /* singleplayer: Start Game alone, under the card */
        uint32_t yes = lyt_find_pane(root, "P_yesBase_00");
        /* (under the card: the grid is on the right; 4:3 has less room: a little smaller, and right of
           the card's middle to stay on the screen) */
        int narrow = phase == PH_CHAR && !rt_widescreen();
        if (yes) { pane_shift(yes, 0, -110.0f + (phase == PH_CHAR ? (narrow ? -158.0f : SP_CARD_DX) : 0.0f));
                   pane_mul(yes, 0, narrow ? 0.8f : 1.0f); pane_mul(yes, 2, narrow ? 0.8f : 1.0f); }
        /* "Back 1" stays while it shows (the button's animation squashes it to height 0;
           set before the matrices) */
        if (np_buttons) { uint32_t back = lyt_find_pane(root, "N_back");
            if (back) { lyt_set_visible(back, 1); lyt_set_alpha(back, 255); wrf(back + 0x44, 1.0f); wrf(back + 0x48, 1.0f); } }
    }
}

/* before the layout is drawn: what's shown, and the texts */
void gs_layout_draw(uint32_t layout, uint32_t root, int menu_kind) {
    int slot = -1, w = which_layout(layout, root, menu_kind, &slot);
    if (w == L_FILE_SELECT) {
        fs_drawn_frame = g_frames_presented;
        int game = phase == PH_GAME;
        uint32_t title = lyt_find_pane(root, "T_title_00");
        if (game) text_set(title, "Select a Game", 0); else text_restore(title);
        int smb3 = play_game == GAME_SMB3;                                /* (SMB3's files: no versus) */
        show_if(root, "P_copy_00", game, 0); show_if(root, "P_delete_00", game, 0);
        int no_vs = game || smb3 || menu_singleplayer();
        show_if(root, "N_Multi_00", no_vs, 0); show_if(root, "N_MultiCoin_00", no_vs, 0);
        uint32_t back = lyt_find_pane(root, "N_back");                   /* "Back 1", as on the character select */
        if (back) { lyt_set_visible(back, 1); lyt_set_alpha(back, 255); }
    } else if (w == L_DATE_FILE) {
        int cur = (int)R32(R32(gs_scene + GS_FSEL) + FS_CHOICE), game = phase == PH_GAME;
        if (game && fabsf(slot_pos(slot)) >= 1.7f) { vis_set(root, 0); return; }   /* (the carousel: off its ends) */
        vis_restore(root);
        int sg = game ? slot_game(slot) : 0;                              /* the game this card shows */
        static const char *contents[] = {"N_dateFile_01", "P_fileNumBase_02", "N_save"};
        uint32_t t1 = lyt_find_pane(root, "T_NewdateFile_00"), t2 = lyt_find_pane(root, "T_NewdateFileS");
        /* (File Select for SMB3: the game's own cards - they show SMB3's files: gs_smb3_slot below) */
        show_if(root, contents[0], game, 0); show_if(root, contents[1], game, 0); show_if(root, contents[2], game, 0);
        gport_t *p = game ? game_portrait(sg) : NULL;                   /* the game's picture, or its name on a blank card */
        card_picture(lyt_find_pane(root, "P_NumBase_01"), p);
        if (game && !p) { text_set_scaled(t1, games[sg].label, 0, 0.78f); text_set_scaled(t2, games[sg].label, 0, 0.78f); }
        else { text_restore(t1); text_restore(t2); }
        /* SMB3's File Select: what the card shows is its stand-in slot's (the cards were made with
           NSMBW's slots at Game Select and keep that look: Copy / Erase redo only the card they change) */
        /* (from SMB3's file itself, not the stand-in: once a file is chosen NSMBW's slots are back
           while the cards fade out - a card read from them showed "New!" or the old lives text) */
        uint32_t df = R32(gs_scene + GS_DATEFILE + 4 * (uint32_t)slot);
        int s3 = !game && play_game == GAME_SMB3 && in_setup() && gs_scene && (phase == PH_FILE || pending == PH_CHAR) && df && slot >= 0 && slot < 3;
        int f_world = 0, f_lives = 0;
        static struct { uint64_t at; int has, world, lives; } fc[3];      /* (read a few times a second, not each draw) */
        if (s3 && (!fc[slot].at || g_frames_presented - fc[slot].at > 15)) { fc[slot].at = g_frames_presented; fc[slot].has = smb3_file_info(slot, &fc[slot].world, &fc[slot].lives); }
        if (s3) { f_world = fc[slot].world; f_lives = fc[slot].lives; }
        int has = s3 && fc[slot].has;
        /* (only while it's SMB3's File Select: otherwise the lines above decide - "restoring" these
           here showed a save card's contents over the Game Select's portraits) */
        if (s3) { show_if(root, "N_dateFile_01", 1, has); show_if(root, "N_save", 1, 0); }
        show_if(root, "N_NewFile_00", s3 || game, game ? !p : !has);
        show_if(root, "N_starIcon_00", s3, 0);
        if (has) {
            char n[8];
            snprintf(n, sizeof n, "%d", f_world + 1 < 1 ? 1 : f_world + 1 > 9 ? 9 : f_world + 1); text_set(R32(df + DF_TB_WORLD), n, 0);
            snprintf(n, sizeof n, "%d", f_lives > 99 ? 99 : f_lives < 0 ? 0 : f_lives); text_set(R32(df + DF_TB_LIVES), n, 0);
        } else if (df) { text_restore(R32(df + DF_TB_WORLD)); text_restore(R32(df + DF_TB_LIVES)); }
    } else if (w == L_CARD) {
        if (slot == 2) { if (phase == PH_CHAR && !is_multi()) vis_set(root, 0); else vis_restore(root); }   /* (singleplayer: no arrows - the grid moves the card) */
    } else if (w == L_CHAR_SELECT) {
        text_set(lyt_find_pane(root, "T_titleNinzu_00"), is_multi() ? "Multiplayer" : "Singleplayer", 0);
        lyt_set_visible(lyt_find_pane(root, "N_remo_00"), 0);           /* (the four remotes) */
        text_set(lyt_find_pane(root, "T_guide_01"), "Settings ", 1);       /* was "Add Wii Remote +" */
        /* singleplayer: no Back button (1 takes the character back); "Back 1" stays */
        int single = !is_multi();
        show_if(root, "P_noBase_00", single, 0);
        show_if(root, "P_yesBase_00", single && !np_buttons, 0);         /* Start Game: only once the character is chosen */

    }
}
