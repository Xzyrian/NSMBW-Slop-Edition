/* smb3_stage_music.inc - SMB3's music and sound effects in NSMBW's stage (included by smb3_stage.c).
 *
 * Native: SMB3's songs and sound effects are sounds of NSMBW's own sound archive, expanded with
 * them (smb3_sound.c: stream sounds for the songs, wave sounds in GROUP_SMB3 for the effects -
 * nothing of NSMBW's own changed or reused), and NSMBW's sound system plays them. No NES APU runs
 * for the SMB3 stage or its map: the sound engine's place (Sound_Engine_Begin, the NMI's call -
 * port/hooks.txt) is taken by smb3_hook_sound, which does what the engine does with the game's
 * sound queues, by its rules (PRG028, PRG031 Sound_PlayMusic):
 *   - Music Set 1 (the jingles) stops the Set 2 song, its song kept (Music2_Hold); the time warning
 *     ($40) over, that song again from its start, faster (Music_RestH_Off $10: its fast stream);
 *     any other jingle over: all music stops (Music_StopAll);
 *   - a Set 2 song queued under a jingle is only held; a Set 2A song other than the sky's / the
 *     star's ($09 / $0A) plays at its own speed again;
 *   - a sound effect: one at a time on each queue (the NES's one channel each - a new one stops
 *     the last); the map's "enter level" sound stops the song; the pause sound (Sound_QPause 1)
 *     pauses the music, 2 resumes it;
 *   - what's playing is written back where SMB3's code reads it - SndCur_Music1 / 2, SndCur_Player
 *     / Level1 / Level2 / Map / Pause - each for its sound's length (Level_MainLoop waits for the
 *     enter-level sound, GameOver_WaitOnBGM for the game over song, DoTimeBonus for the jingle).
 * Each sound frame (the NMI's - a frame SMB3 runs on its map, or a frame of the stage in a level,
 * where SMB3 is held) is one step of that. NSMBW's sounds follow it each frame the stage runs (in
 * the game's own code: music_sync), started through NSMBW's sound manager (SndAudioMgr's own
 * start, as NSMBW starts its music): the songs on its course BGM player (18) and fanfare player
 * (17), the effects on its sound effect players. Sound effects of frames SMB3 runs unseen (a
 * map's way into a level, a pipe's junction) are not played.
 *
 * What the stage queues, as SMB3's own code would:
 *   - the level's song: Level_MusicQueueRestore, from the level header (PRG030_98C8), with the
 *     stage (Sound_QMusic2);
 *   - NSMBW's music states, read from NSMBW's own sound scene (SndSceneMgr's flags: 4 the star,
 *     8 a P-switch): MUS2A_INVINCIBILITY / MUS2B_PSWITCH, and the level's song again after, as
 *     PRG008_A1FE restores it (the star first);
 *   - NSMBW's music requests (nw4r SoundStartable::detail_Start/Hold/PrepareSound, hooked in
 *     rt_retro.c / gm_nw4r_g3d.c): every BGM sound of NSMBW's is not played in the SMB3 stage; the
 *     ones with an SMB3 counterpart queue it - the miss (STRM_BGM_DOWN, MULTI_FAIL) MUS1_PLAYERDEATH,
 *     game over MUS1_GAMEOVER, the hurry-up at 100 (SE_SYS_HURRY_UP - NSMBW's timer is kept at SMB3's)
 *     MUS1_TIMEWARNING, a course / boss clear MUS1_COURSECLEAR / MUS1_BOSSVICTORY;
 *   - the goal card (smb3_stage_enemies.inc goal_take): MUS1_COURSECLEAR, a triple MUS1_BOSSVICTORY;
 *   - NSMBW's pause menu (dGameDisplay_c's ProcMainPause, gm_d_gamedisplay.c): Sound_QPause 1 / 2,
 *     SMB3's pause sound and its silence; NSMBW's SE_SYS_PAUSE is not played in a level then.
 * NSMBW's own sound effects stay. Sound IDs: the disc's sound archive (wii_mj2d_sound.brsar:
 * players 16-19 and 21 are NSMBW's BGM players; tools/brsar_sounds.py). */
#include "smb3_sound.h"
int smb3_nes_rts(void);                         /* (smb3_game.c: NES_RTS - the routine left as if it had returned) */
int smb3_hook_sound(void);

#define SND_SCENE_MGR       0x8042A4A8u           /* SndSceneMgr::sInstance */
#define SSM_FLAGS           28                    /* u16: what NSMBW's music is doing (onSoundFlag / offSoundFlag) */
#define SSM_STAR            0x0004
#define SSM_PSWITCH         0x0008
#define SND_AUDIO_MGR       (0x80430000u - 23416) /* SndAudioMgr::sInstance */
#define SAM_START_SOUND     180                   /* (its vtable: StartSound(handle, id) - as its BGM start, fn_801953B0, calls it) */
#define A_BS_STOP           0x80266250u           /* nw4r::snd::detail::BasicSound::Stop(int fadeFrames) */
#define A_BS_PAUSE          0x80266440u           /* BasicSound::Pause(bool, int fadeFrames) */
#define A_BS_SETVOL         0x80267420u           /* BasicSound::SetVolume(float, int frames) */
#define SM_SND_SONG         (SM_MEM + 0x0280)     /* nw4r::snd::SoundHandle (the BasicSound *) of the Set 2 song */
#define SM_SND_JINGLE       (SM_MEM + 0x0284)     /* (the Set 1 jingle's) */
#define SM_SND_SFX(k)       (SM_MEM + 0x0288 + 4 * ((k) - SND_PLAYER))   /* (each sound effect queue's: SND_PLAYER .. SND_PAUSE) */
/* NSMBW's sound IDs (the sound archive) */
enum { SE_SYS_PAUSE_ID = 124, SE_SYS_HURRY_UP_ID = 175, STRM_BGM_DUMMY_ID = 117, SE_BGM_CS_STAR_ID = 1647,
       STRM_BGM_FIRST = 1847, STRM_BGM_DOWN_ID = 1870, STRM_BGM_GAMEOVER_ID = 1871, STRM_BGM_COURSE_CLEAR_ID = 1872,
       STRM_BGM_COURSE_CLEAR_ZORO_ID = 1873, STRM_BGM_SHIRO_BOSS_CLEAR_ID = 1882, STRM_BGM_HIKOUSENBOSS_CREAR_ID = 1885,
       STRM_BGM_TORIDEBOSS_CREAR_ID = 1910, STRM_BGM_MULTI_FAIL_ID = 1928, SEQ_BGM_LAST = 1967 };
#define SND_FRAME_SAMPLES   (32000.0 / 60.0988)   /* (a sound frame: the NES's 60.0988 a second) */

static struct {
    int start;                                   /* (a level placed: its song from the top) */
    int pause_want, pause_is;
    int bg;                                      /* (the Music2 song asked for last: level / star / P-switch) */
    int star, ps, fresh;                         /* (the star / P-switch as last seen; fresh: a new level) */
    int died; uint64_t died_at;                  /* (the death song queued as the death began; that frame) */
} MU RT_LOCAL;
/* SMB3's sound, as its engine would have it (smb3_hook_sound / snd_step) */
static struct {
    int cur1, cur2, hold, fast, paused;          /* SndCur_Music1 / 2, Music2_Hold, Music_RestH_Off $10, Sound_IsPaused */
    int t1, t2;                                  /* (sound frames each has played) */
    int gen1, gen2;                              /* (each start of a jingle / song: a new one for the streams) */
    int sfx_cur[7], sfx_left[7];                 /* (SndCur_Player .. Map, Pause: what, and its frames to go) */
    int sfx_gen[7], sfx_want[7];                 /* (each queue's last effect to play: for the sounds) */
    int unseen;                                  /* (SMB3 running frames nobody sees: their sound effects not played) */
    uint64_t steps;
} SM RT_LOCAL;
/* the streams as they are (music_sync) */
static struct { int gen1, gen2, paused, own, sfx_gen[7]; uint64_t song_at; } SS RT_LOCAL;

static int music_level(void) { return active && !probe && in_stage() && !map_on() && L.placed && !MP.ending && !jct_restart; }   /* (jct_restart: a pipe's junction made - the level's sound over till the other area is placed) */
static void mus_q1(uint8_t v) { S3W(SMB3_Sound_QMusic1, (uint8_t)(S3(SMB3_Sound_QMusic1) | v)); }
static void mus_q2(uint8_t v) { S3W(SMB3_Sound_QMusic2, v); }
static void music_level_placed(void) { MU.start = 1; restart_wait = 0; }

/* ---------------------------------------------------------------- SMB3's sound engine's rules */
static int snd_frames(const smb3_snd_t *s) { return s ? (int)(s->samples / SND_FRAME_SAMPLES + 0.5) : 0; }
static int song_has_fast(int id) { return (id & 0xF0) || id == 0x09 || id == 0x0A; }
static int song_loops(int id, int fast) { const smb3_snd_t *s = smb3_snd_find(SND_M2, id, fast && song_has_fast(id)); return !s || s->loop >= 0; }
static void snd_song(int id) { SM.cur2 = id; SM.t2 = 0; SM.gen2++; }
static void snd_stop_all(void) { SM.cur1 = SM.cur2 = SM.hold = 0; SM.fast = 0; SM.gen1++; SM.gen2++; }
static int low_bit(int v) { for (int b = 0; b < 8; b++) if (v & (1 << b)) return 1 << b; return 0; }
static void snd_sfx(int k, int v) {               /* (k: SND_PLAYER .. SND_PAUSE) a sound effect: its sound, its SndCur_ for its length */
    const smb3_snd_t *s = smb3_snd_find(k, v, 0);
    int again = k == SND_PLAYER && v == 0x40 && SM.sfx_cur[k] == v && SM.sfx_left[k] > 0;   /* (SND_PLAYERPOWER: set every frame, it rings on) */
    SM.sfx_cur[k] = v; if (!again) SM.sfx_left[k] = s ? snd_frames(s) : 2;
    if (s && !SM.unseen && !again) { SM.sfx_want[k] = v; SM.sfx_gen[k]++; }
    if (getenv("SMB3_MUSIC_LOG") && !(k == SND_PLAYER && v == 0x40)) rt_log("smb3", "sound: effect %d:%02X%s", k, v, SM.unseen ? " (unseen)" : "");
}
static uint16_t snd_cur_addr(int k) {
    static const uint16_t a[7] = { 0, 0, SMB3_SndCur_Player, SMB3_SndCur_Level1, SMB3_SndCur_Level2, SMB3_SndCur_Map, SMB3_SndCur_Pause };
    return a[k];
}
/* one sound frame: the queues taken (and cleared), as Sound_Engine_Begin; SMB3's SndCur_ after */
static void snd_step(void) {
    uint8_t *r = nes_ram_ptr();
    SM.steps++;
    int qp = r[SMB3_Sound_QPause];
    if (qp) {                                                            /* SndPause */
        if (qp == 2) { SM.paused = 0; SM.sfx_cur[SND_PAUSE] = 0; SM.sfx_left[SND_PAUSE] = 0; }
        else { SM.paused = 1; for (int k = SND_PLAYER; k <= SND_LEVEL2; k++) SM.sfx_cur[k] = SM.sfx_left[k] = 0; snd_sfx(SND_PAUSE, 1); }
    } else if (!SM.paused) {                                             /* Sound_Process */
        int v;
        if ((v = r[SMB3_Sound_QLevel2])) snd_sfx(SND_LEVEL2, low_bit(v));
        if ((v = r[SMB3_Sound_QPlayer])) snd_sfx(SND_PLAYER, low_bit(v));
        if ((v = r[SMB3_Sound_QLevel1])) snd_sfx(SND_LEVEL1, v >= 0x90 && !(v & 0x0F) ? v : low_bit(v));
        if ((v = r[SMB3_Sound_QMap])) { if (low_bit(v) == 0x04) { SM.cur2 = 0; SM.gen2++; } snd_sfx(SND_MAP, low_bit(v)); }   /* (entering a level: the song halted) */
        int q1 = r[SMB3_Sound_QMusic1], q2 = r[SMB3_Sound_QMusic2];
        if (q1) {                                                        /* SndMus_Queue1 */
            if (q1 & 0x80) snd_stop_all();                               /* (MUS1_STOPMUSIC) */
            else { SM.hold = SM.cur2; SM.cur2 = 0; SM.fast = 0; SM.cur1 = low_bit(q1); SM.t1 = 0; SM.gen1++; SM.gen2++; }
        } else if (SM.cur1) { if (q2) SM.hold = q2; }                   /* (held till the jingle's over) */
        else if (q2) {
            if (q2 & 0xF0) snd_song(q2 & 0xF0);                          /* SndMus_QueueSet2B */
            else { if (q2 != 0x09 && q2 != 0x0A) SM.fast = 0; snd_song(q2); }   /* (Set 2A: the time warning's speed kept for the sky's / star's) */
        }
        r[SMB3_Sound_QMusic1] = r[SMB3_Sound_QMusic2] = 0;
        /* the music's time */
        if (SM.cur1) {
            const smb3_snd_t *s = smb3_snd_find(SND_M1, SM.cur1, 0);
            if (++SM.t1 >= (s ? snd_frames(s) : 60)) {                    /* Music_EndSegment */
                if (SM.cur1 == 0x40) {                                   /* (the time warning: the song again, faster) */
                    int h = SM.hold; SM.cur1 = 0; SM.gen1++; SM.fast = 1;
                    if (h) snd_song(h);
                    if (getenv("SMB3_MUSIC_LOG")) rt_log("smb3", "music: the time warning over - song %02X again, fast", h);
                } else snd_stop_all();
            }
        } else if (SM.cur2) {
            SM.t2++;
            if (!song_loops(SM.cur2, SM.fast)) { const smb3_snd_t *s = smb3_snd_find(SND_M2, SM.cur2, SM.fast && song_has_fast(SM.cur2)); if (SM.t2 >= snd_frames(s)) snd_stop_all(); }
        }
    }
    for (int k = SND_PLAYER; k <= SND_PAUSE; k++) {                       /* (each sound's time) */
        if (SM.sfx_left[k] > 0 && --SM.sfx_left[k] == 0) SM.sfx_cur[k] = 0;
        r[snd_cur_addr(k)] = (uint8_t)SM.sfx_cur[k];
    }
    r[SMB3_Sound_QPlayer] = r[SMB3_Sound_QLevel1] = r[SMB3_Sound_QLevel2] = r[SMB3_Sound_QMap] = r[SMB3_Sound_QPause] = 0;
    r[SMB3_SndCur_Music1] = (uint8_t)SM.cur1; r[SMB3_SndCur_Music2] = (uint8_t)SM.cur2;
    r[SMB3_Sound_IsPaused] = (uint8_t)SM.paused; r[SMB3_Music2_Hold] = (uint8_t)SM.hold;
    nes_wram_ptr()[SMB3_Music_RestH_Off - 0x6000] = (uint8_t)(SM.fast ? 0x10 : 0);
    if (getenv("SMB3_MUSIC_LOG")) {
        static int l1 = -1, l2 = -1, lf = -1; if (SM.cur1 != l1 || SM.cur2 != l2 || SM.fast != lf) { rt_log("smb3", "music: playing %02X / %02X%s (sound frame %llu)", SM.cur1, SM.cur2, SM.fast ? " fast" : "", (unsigned long long)SM.steps); l1 = SM.cur1; l2 = SM.cur2; lf = SM.fast; } }
}
static void snd_unseen(int on) { SM.unseen = on; }
/* Sound_Engine_Begin (port/hooks.txt): in the SMB3 stage, the engine's rules here and no APU */
int smb3_hook_sound(void) {
    if (smb3_sound_rendering || !active || probe) return 0;              /* (SMB3 by itself - smb3_main.c - or rendering: its own engine) */
    snd_step();
    return smb3_nes_rts();
}

/* ---------------------------------------------------------------- the stage's music states */
/* the Music2 song now, as SMB3 changes it: a P-switch pressed (PRG008: Level_PSwitchCnt $80 -
   MUS2B_PSWITCH, over a star's song too) or a star got (MUS2A_INVINCIBILITY) start theirs; when one
   ends, the other's if it still runs, else the level's (PRG008_A1FE). The P-switch is the stage's
   own (smb3_stage.c PS.cnt - SMB3's Level_PSwitchCnt) or NSMBW's (its sound scene's flag 8); the
   star NSMBW's (flag 4: the star music NSMBW would play). */
static int music_bg_want(void) {
    uint32_t m = R32(SND_SCENE_MGR); unsigned f = m ? R16(m + SSM_FLAGS) : 0;
    int star = (f & SSM_STAR) != 0, ps = PS.cnt > 0 || (f & SSM_PSWITCH);
    int restore = S3(SMB3_Level_MusicQueueRestore), w = MU.bg;
    if (MU.fresh) w = star ? MUS2A_INVINCIBILITY : ps ? MUS2B_PSWITCH : restore;
    else if (ps && !MU.ps) w = MUS2B_PSWITCH;
    else if (star && !MU.star) w = MUS2A_INVINCIBILITY;
    else if ((!ps && MU.ps) || (!star && MU.star)) w = star ? MUS2A_INVINCIBILITY : ps ? MUS2B_PSWITCH : restore;
    MU.star = star; MU.ps = ps; MU.fresh = 0;
    return w;
}
/* (gm_d_player_conv.c: dAcPy_c::initPlayerDownCommon - every death, as it begins) SMB3 queues its
   death song in Player_Die, as the Player dies; NSMBW's miss music comes after a wait (DemoDown's
   +5212). Only a death that loses the level: +5460 set (no one left to go on - startMissBGM's own
   test); a player who goes into a balloon while the others play on has none. */
void smb3_music_player_down(uint32_t pl) {
    if (!music_level() || !R32(pl + 5460)) return;
    extern uint64_t g_frames_presented;
    if (!MU.died) { mus_q1(MUS1_PLAYERDEATH); MU.died_at = g_frames_presented; }
    MU.died = 1;
    if (getenv("SMB3_MUSIC_LOG")) rt_log("smb3", "music: a player down - the death song");
}
/* frames of the death song still to come (SMB3 drops to its map as it ends: Player_Die_Dying's
   Event_Countdown - NSMBW's own death is over sooner; smb3_stage_restart waits for it) */
static int music_death_left(void) {
    extern uint64_t g_frames_presented;
    if (!MU.died || !MU.died_at) return 0;
    int64_t left = DEATH_SONG_FRAMES - (int64_t)(g_frames_presented - MU.died_at);
    return left > 0 ? (int)left : 0;
}
/* (gm_d_gamedisplay.c: NSMBW's pause menu up / down) */
void smb3_music_pause(int on) { MU.pause_want = on; }

/* NSMBW starts a sound (id): 1 = not played - its music, in the SMB3 stage */
int smb3_music_sound(uint32_t id) {
    if (!active || probe || !in_stage() || SS.own) return 0;            /* (SS.own: an SMB3 song started by music_sync) */
    int lvl = music_level();
    if (id == SE_SYS_PAUSE_ID) return lvl;                           /* (SMB3's pause sound instead: Sound_QPause) */
    int bgm = id == STRM_BGM_DUMMY_ID || id == SE_SYS_HURRY_UP_ID || id == SE_BGM_CS_STAR_ID || (id >= STRM_BGM_FIRST && id <= SEQ_BGM_LAST);
    if (!bgm) return 0;
    if (!lvl) return 1;
    switch (id) {
    case STRM_BGM_DOWN_ID: case STRM_BGM_MULTI_FAIL_ID: if (!MU.died) mus_q1(MUS1_PLAYERDEATH); MU.died = 1; break;   /* (Player_Die - already, as the death began) */
    case STRM_BGM_GAMEOVER_ID: mus_q1(MUS1_GAMEOVER); break;
    case SE_SYS_HURRY_UP_ID: mus_q1(MUS1_TIMEWARNING); break;                              /* (prg026: the clock at 100) */
    case STRM_BGM_COURSE_CLEAR_ID: case STRM_BGM_COURSE_CLEAR_ZORO_ID: mus_q1(MUS1_COURSECLEAR); break;
    case STRM_BGM_SHIRO_BOSS_CLEAR_ID: case STRM_BGM_HIKOUSENBOSS_CREAR_ID: case STRM_BGM_TORIDEBOSS_CREAR_ID: mus_q1(MUS1_BOSSVICTORY); break;
    default: break;                                                  /* (the area's song, the star's, the P-switch's: from the state - music_tick) */
    }
    if (getenv("SMB3_MUSIC_LOG")) rt_log("smb3", "music: NSMBW's sound %u not played (SMB3's music)", id);
    return 1;
}

/* a level's sound frame (SMB3 is held: no NMI runs its engine): NSMBW's state into SMB3's queues, then a step */
static void music_tick(void) {
    if (MU.start) {                                                  /* (the level placed: its song, with the stage) */
        MU.start = 0; MU.pause_want = MU.pause_is = 0; MU.died = 0; MU.died_at = 0; MU.fresh = 1;
        SM.paused = 0; SM.cur1 = 0; SM.gen1++; SM.unseen = 0;
        for (int k = SND_PLAYER; k <= SND_PAUSE; k++) SM.sfx_cur[k] = SM.sfx_left[k] = 0;
        S3W(SMB3_Sound_QPause, 0); S3W(SMB3_Level_MusicQueue, 0);
        S3W(SMB3_Sound_QPlayer, 0); S3W(SMB3_Sound_QLevel1, 0); S3W(SMB3_Sound_QLevel2, 0);   /* (nothing left over from before) */
        /* (Level_MainLoop PRG030_8DE7: the song already playing is not queued again - a door or
           pipe into an area with the same song: it plays on) */
        MU.bg = music_bg_want(); int same = MU.bg && MU.bg == SM.cur2;
        if (!same) mus_q2((uint8_t)MU.bg);
        rt_log("smb3", "music: the level's song %02X%s%s", S3(SMB3_Level_MusicQueueRestore), MU.bg != S3(SMB3_Level_MusicQueueRestore) ? " (a star / P-switch on)" : "", same ? " (already playing: on)" : "");
    }
    {   int w = music_bg_want();
        if (w != MU.bg) { MU.bg = w; if (w) mus_q2((uint8_t)w);
            if (getenv("SMB3_MUSIC_LOG")) rt_log("smb3", "music: song %02X", w); } }
    if (MU.pause_want != MU.pause_is) { MU.pause_is = MU.pause_want; S3W(SMB3_Sound_QPause, (uint8_t)(MU.pause_is ? 1 : 2));
        if (getenv("SMB3_MUSIC_LOG")) rt_log("smb3", "music: %s", MU.pause_is ? "paused" : "resumed"); }
    if (getenv("SMB3_MUSIC_TEST_Q1")) {                              /* (testing: "song,frame" - a Music1 song queued that many sound frames into the level) */
        static int done; int song = 0, at = 0; sscanf(getenv("SMB3_MUSIC_TEST_Q1"), "%x,%d", &song, &at);
        if (!done && (int)SM.steps >= at) { done = 1; mus_q1((uint8_t)song); rt_log("smb3", "music test: song %02X queued (sound frame %llu)", song, (unsigned long long)SM.steps); } }
    snd_step();
}

/* ---------------------------------------------------------------- the streams (NSMBW's sound) */
static void snd_stop(ppc_context *ctx, uint8_t *base, uint32_t h) {
    uint32_t s = R32(h); if (s) { SS.own = 1; gcall(ctx, base, A_BS_STOP, 2, s, 0); SS.own = 0; }
}
/* an SMB3 sound (s, its ID in the expanded archive) started on handle h, through SndAudioMgr */
static void snd_start(ppc_context *ctx, uint8_t *base, uint32_t h, const smb3_snd_t *s, int log) {
    snd_stop(ctx, base, h);
    uint32_t mgr = R32(SND_AUDIO_MGR); if (!mgr || !s || s->sound_id < 0) return;
    SS.own = 1;
    uint32_t r = gcall(ctx, base, R32(R32(mgr) + SAM_START_SOUND), 3, mgr, h, (uint32_t)s->sound_id);
    SS.own = 0;
    uint32_t snd = R32(h);
    if (snd) { int v = rt_setting("smb3_volume", 100); ctx->f[1].d = ctx->ps1[1] = v / 100.0; gcall(ctx, base, A_BS_SETVOL, 2, snd, 0); }
    if (log || getenv("SMB3_MUSIC_LOG")) rt_log("smb3", "sound: %s (NSMBW sound %d: %u%s)", s->label, s->sound_id, r, snd ? "" : ", not started");
}
/* (gm_nw4r_g3d.c: nw4r BasicSound::Stop) testing - an SMB3 song stopped by NSMBW, and from where */
void smb3_music_stopping(uint32_t snd, uint32_t lr, uint32_t fade) {
    if (!snd || !getenv("SMB3_MUSIC_LOG") || SS.own) return;
    extern uint64_t g_frames_presented;
    if (snd == R32(SM_SND_SONG) || snd == R32(SM_SND_JINGLE))
        rt_log("smb3", "music: NSMBW stops the SMB3 %s (from %08X, fade %u, frame %llu)", snd == R32(SM_SND_SONG) ? "song" : "jingle", lr, fade, (unsigned long long)g_frames_presented);
}
/* each frame the stage runs (in the game's code): the streams as SMB3's sound has it */
static void music_sync(ppc_context *ctx, uint8_t *base) {
    extern uint64_t g_frames_presented; static uint64_t last;
    if (!active || probe || last == g_frames_presented) return;
    last = g_frames_presented;
    if (music_level()) music_tick();                                    /* (in a level SMB3 is held: its sound frame is ours) */
    int live = music_level() || (MP.session && map_on() && L.placed);
    if (SS.gen1 != SM.gen1) {
        SS.gen1 = SM.gen1;
        if (SM.cur1) snd_start(ctx, base, SM_SND_JINGLE, smb3_snd_find(SND_M1, SM.cur1, 0), 1); else snd_stop(ctx, base, SM_SND_JINGLE);
    }
    if (SS.gen2 != SM.gen2 || (live && SM.cur2 && !SM.cur1 && !R32(SM_SND_SONG) && song_loops(SM.cur2, SM.fast) && g_frames_presented > SS.song_at + 60)) {   /* (a looping song NSMBW stopped - a scene's change: again) */
        if (SS.gen2 == SM.gen2 && getenv("SMB3_MUSIC_LOG")) rt_log("smb3", "music: the song had stopped (frame %llu)", (unsigned long long)g_frames_presented);
        SS.gen2 = SM.gen2; SS.song_at = g_frames_presented;
        int f = SM.fast && song_has_fast(SM.cur2);
        if (SM.cur2) snd_start(ctx, base, SM_SND_SONG, smb3_snd_find(SND_M2, SM.cur2, f), 1); else snd_stop(ctx, base, SM_SND_SONG);
        if (SM.cur2 && SM.paused) { uint32_t snd = R32(SM_SND_SONG); if (snd) gcall(ctx, base, A_BS_PAUSE, 3, snd, 1, 0); }
    }
    for (int k = SND_PLAYER; k <= SND_PAUSE; k++)                       /* (the sound effects: one at a time on each queue) */
        if (SS.sfx_gen[k] != SM.sfx_gen[k]) { SS.sfx_gen[k] = SM.sfx_gen[k]; snd_start(ctx, base, SM_SND_SFX(k), smb3_snd_find(k, SM.sfx_want[k], 0), 0); }
    if (SS.paused != SM.paused) {
        SS.paused = SM.paused;
        for (int k = 0; k < 2; k++) { uint32_t s = R32(k ? SM_SND_JINGLE : SM_SND_SONG); if (s) gcall(ctx, base, A_BS_PAUSE, 3, s, (uint32_t)SS.paused, 0); }
    }
}
/* (gm_nw4r_g3d.c: EGG's loadGroup, fn_802D3E90, as NSMBW loads GROUP_BOOT at start) GROUP_SMB3,
   SMB3's sound effects, loaded after it the same way - into NSMBW's sound heap, to stay */
void smb3_sound_group_load(ppc_context *ctx, uint8_t *base, uint32_t mgr, uint32_t group, uint32_t heap, uint32_t block) {
    int g = smb3_snd_group();
    if (group != 0 || g < 0 || !ctx->r[3]) return;
    uint32_t r3 = ctx->r[3];
    if (getenv("SMB3_MUSIC_LOG")) {                                      /* (the heap: nw4r SoundHeap -> its frame heap, 'FRMH') */
        uint32_t sh = heap ? heap : R32(mgr + 1224);
        rt_log("smb3", "sound: mgr %08X state %u busy %u heap %08X block %u", mgr, R32(mgr + 1228), R8(mgr + 4), sh, block);
        for (int i = 0; i < 24; i++) { uint32_t v = R32(sh + 4 * (uint32_t)i);
            if (v >= 0x80000000u && v < 0x94000000u && R32(v) == 0x46524D48u) {
                rt_log("smb3", "sound: the sound heap's frame heap %08X: %08X - %08X, head %08X tail %08X (free %u)", v, R32(v + 0x18), R32(v + 0x1C), R32(v + 0x3C), R32(v + 0x40), R32(v + 0x40) - R32(v + 0x3C)); } }
    }
    uint32_t ok = gcall(ctx, base, 0x802D3E90u, 4, mgr, (uint32_t)g, heap, block);
    rt_log("smb3", "sound: GROUP_SMB3 (group %d, SMB3's sound effects) %s", g, ok ? "loaded with GROUP_BOOT" : "NOT loaded");
    ctx->r[3] = r3;
}
/* (rt_audio.c, each block of sound sent to the PC) nothing of SMB3's own: its sound is NSMBW's now */
int smb3_stage_audio(int16_t *lr, int n) { (void)lr; (void)n; return 0; }
