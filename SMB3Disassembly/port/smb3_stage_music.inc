/* smb3_stage_music.inc - SMB3's music in NSMBW's stage (included by smb3_stage.c).
 *
 * SMB3's own sound engine plays it: the recompiled PRG028/029 code with its own song data, on the
 * NES APU (nes_apu.c), as on the map. On the map the NES runs whole frames and its NMI calls the
 * engine. In a level the game is held where SMB3 brought the level up, and the engine is run alone
 * (nes_sound_run: as the NMI would, 60.1 times a second of sound), paced by the sound sent to the
 * PC - so it is never run twice by a rollback's frames and the tempo is the NES's.
 *
 * What it plays comes from SMB3's queues, set as SMB3's own code sets them:
 *   - the level's song: Level_MusicQueueRestore, from the level header (PRG030_98C8: SMB3 has it
 *     by the time the stage takes the level), started with the stage (Sound_QMusic2);
 *   - NSMBW's music states, read from NSMBW's own sound scene (SndSceneMgr's flags: 4 the star,
 *     8 a P-switch): MUS2A_INVINCIBILITY / MUS2B_PSWITCH, and the level's song again after, as
 *     PRG008_A1FE restores it (the star first);
 *   - NSMBW's music requests (nw4r SoundStartable::detail_Start/Hold/PrepareSound, hooked in
 *     rt_retro.c / gm_nw4r_g3d.c): every BGM sound of NSMBW's is not played in the SMB3 stage; the
 *     ones with an SMB3 counterpart queue it - the miss (STRM_BGM_DOWN, MULTI_FAIL) MUS1_PLAYERDEATH,
 *     game over MUS1_GAMEOVER, the hurry-up at 100 (SE_SYS_HURRY_UP - NSMBW's timer is kept at SMB3's)
 *     MUS1_TIMEWARNING, a course / boss clear MUS1_COURSECLEAR / MUS1_BOSSVICTORY;
 *   - the goal card (smb3_stage_enemies.inc goal_take): MUS1_COURSECLEAR, a triple MUS1_BOSSVICTORY
 *     (prg002 PRG002_BF9F), and the time bonus waits for it (DoTimeBonus: no counting while
 *     SndCur_Music1 plays - here the song's length in frames, so the game stays deterministic);
 *   - NSMBW's pause menu (dGameDisplay_c's ProcMainPause, gm_d_gamedisplay.c): Sound_QPause 1 / 2,
 *     SMB3's pause sound and its silence; NSMBW's SE_SYS_PAUSE is not played in a level then.
 * NSMBW's sound effects stay, mixed with SMB3's sound. Sound IDs: the disc's sound archive
 * (wii_mj2d_sound.brsar: players 16-19 and 21 are NSMBW's BGM players; tools/brsar_sounds.py). */

#define SMB3_SOUND_ENGINE   0xA000                /* Sound_Engine_Begin (PRG028) */
#define SMB3_SOUND_BANK_A   28                    /* (PRG031_F567: page 28 at $A000, 29 at $C000) */
#define SMB3_SOUND_BANK_C   29
#define SND_SCENE_MGR       0x8042A4A8u           /* SndSceneMgr::sInstance */
#define SSM_FLAGS           28                    /* u16: what NSMBW's music is doing (onSoundFlag / offSoundFlag) */
#define SSM_STAR            0x0004
#define SSM_PSWITCH         0x0008
/* NSMBW's sound IDs (the sound archive) */
enum { SE_SYS_PAUSE_ID = 124, SE_SYS_HURRY_UP_ID = 175, STRM_BGM_DUMMY_ID = 117, SE_BGM_CS_STAR_ID = 1647,
       STRM_BGM_FIRST = 1847, STRM_BGM_DOWN_ID = 1870, STRM_BGM_GAMEOVER_ID = 1871, STRM_BGM_COURSE_CLEAR_ID = 1872,
       STRM_BGM_COURSE_CLEAR_ZORO_ID = 1873, STRM_BGM_SHIRO_BOSS_CLEAR_ID = 1882, STRM_BGM_HIKOUSENBOSS_CREAR_ID = 1885,
       STRM_BGM_TORIDEBOSS_CREAR_ID = 1910, STRM_BGM_MULTI_FAIL_ID = 1928, SEQ_BGM_LAST = 1967 };

static struct {
    int start;                                   /* (a level placed: its song from the top) */
    int pause_want, pause_is;
    int bg;                                      /* (the Music2 song asked for last: level / star / P-switch) */
    int star, ps, fresh;                         /* (the star / P-switch as last seen; fresh: a new level) */
    int died; uint64_t died_at;                  /* (the death song queued as the death began; that frame) */
    uint64_t tick_frame;
    double cyc;                                  /* (CPU cycles owed, fractions) */
} MU RT_LOCAL;

static int music_level(void) { return active && !probe && in_stage() && !map_on() && L.placed && !MP.ending; }   /* (ending: SMB3 is on its map again - its own frames' sound) */
static void mus_q1(uint8_t v) { S3W(SMB3_Sound_QMusic1, (uint8_t)(S3(SMB3_Sound_QMusic1) | v)); }
static void mus_q2(uint8_t v) { S3W(SMB3_Sound_QMusic2, v); }
static void music_level_placed(void) { MU.start = 1; restart_wait = 0; }
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
    if (!active || probe || !in_stage()) return 0;
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

/* a level's sound: NSMBW's state into SMB3's queues, then SMB3's sound engine for n samples */
static void music_tick(int n) {
    if (MU.start) {                                                  /* (the level placed: its song, with the stage) */
        MU.start = 0; MU.pause_want = MU.pause_is = 0; MU.died = 0; MU.died_at = 0; MU.fresh = 1;
        apu_flush();                                                 /* (the frames SMB3 ran to bring it up) */
        S3W(SMB3_Sound_QPause, 0); S3W(SMB3_Sound_IsPaused, 0); S3W(SMB3_SndCur_Pause, 0);
        S3W(SMB3_Level_MusicQueue, 0);
        MU.bg = music_bg_want(); mus_q2((uint8_t)MU.bg);
        rt_log("smb3", "music: the level's song %02X%s", S3(SMB3_Level_MusicQueueRestore), MU.bg != S3(SMB3_Level_MusicQueueRestore) ? " (a star / P-switch on)" : "");
    }
    {   int w = music_bg_want();
        if (w != MU.bg) { MU.bg = w; if (w) mus_q2((uint8_t)w);
            if (getenv("SMB3_MUSIC_LOG")) rt_log("smb3", "music: song %02X", w); } }
    if (MU.pause_want != MU.pause_is) { MU.pause_is = MU.pause_want; S3W(SMB3_Sound_QPause, (uint8_t)(MU.pause_is ? 1 : 2));
        if (getenv("SMB3_MUSIC_LOG")) rt_log("smb3", "music: %s", MU.pause_is ? "paused" : "resumed"); }
    extern uint64_t g_frames_presented; MU.tick_frame = g_frames_presented;
    MU.cyc += n * (1789773.0 / 32000.0);                             /* (the NES's CPU clock; the PC's sound at 32 kHz) */
    uint64_t c = (uint64_t)MU.cyc; MU.cyc -= (double)c;
    nes_sound_run(SMB3_SOUND_ENGINE, SMB3_SOUND_BANK_A, SMB3_SOUND_BANK_C, c);
    static double sfr; sfr += (double)c / 29780.5;                   /* (testing: the sound's own frames) */
    if (getenv("SMB3_MUSIC_TEST_Q1")) {                              /* (testing: "song,frame" - a Music1 song queued that many sound frames into the level) */
        static int done; int song = 0, at = 0; sscanf(getenv("SMB3_MUSIC_TEST_Q1"), "%x,%d", &song, &at);
        if (!done && sfr >= at) { done = 1; mus_q1((uint8_t)song); rt_log("smb3", "music test: song %02X queued (sound frame %.0f)", song, sfr); } }
    if (getenv("SMB3_MUSIC_LOG")) {                                  /* (testing: SMB3's songs as they change) */
        static int l1 = -1, l2 = -1; int m1 = S3(SMB3_SndCur_Music1), m2 = S3(SMB3_SndCur_Music2);
        if (m1 != l1 || m2 != l2) { rt_log("smb3", "music: playing %02X / %02X (frame %llu, sound frame %.0f)", m1, m2, (unsigned long long)g_frames_presented, sfr); l1 = m1; l2 = m2; } }
}

/* SMB3's sound in the stage (rt_audio.c, each block of sound sent to the PC): on the map, SMB3's
   frames' sound; in a level, its engine alone. Mixed with NSMBW's (its music isn't played here) */
int smb3_stage_audio(int16_t *lr, int n) {
    if (!active) return 0;
    int lvl = music_level(), map = MP.session && map_on();
    if (!lvl && !map) return 0;
    if (lvl) music_tick(n);
    static int16_t s[2 * 4096] RT_LOCAL;
    if (n > 4096) n = 4096;
    int got = apu_pull(s, n, rt_setting("smb3_volume", 100));
    if (getenv("SMB3_MUSIC_LOG") && lvl) {                           /* (testing: the level's sound - made / asked, its loudness - a second at a time) */
        static int t_n, t_got; static double t_sq; t_n += n; t_got += got; for (int i = 0; i < n; i++) t_sq += (double)s[2 * i] * s[2 * i];
        if (t_n >= 32000) { rt_log("smb3", "music: a second of the level: %d of %d samples made, rms %.0f", t_got, t_n, sqrt(t_sq / t_n)); t_n = t_got = 0; t_sq = 0; } }
    for (int i = 0; i < 2 * n; i++) { int v = lr[i] + s[i]; lr[i] = (int16_t)(v > 32767 ? 32767 : v < -32768 ? -32768 : v); }
    return 1;
}
