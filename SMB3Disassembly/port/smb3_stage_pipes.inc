/* smb3_stage_pipes.inc - pipes into other areas (included by smb3_stage.c after smb3_map.inc).
 *
 * SMB3 (prg008 Player_DoSpecialTiles): standing on a pipe's top ($AD/$AE alternate area, $AF/$B0
 * the Big [?] area, $B3/$B4 in-level transit - $B1/$B2 are not enterable) holding down, in the
 * middle of it; jumping into a pipe's bottom (the same tiles) holding up; walking into a sideways
 * pipe's mouth ($B5, the bottom half) holding towards it. PipeEntryPrepare sets Level_PipeMove
 * (direction + what it does: exit the level, the Big [?] area, a junction, the exit area, a
 * transit), the Player slides in, and Level_JctCtl brings up the other area (Level_AltLayout /
 * Level_AltObjects), the Player coming out of its pipe.
 *
 * Here: the NSMBW player that meets those rules slides into the pipe (its cells let it through,
 * the tiles drawn over it - as behind the scenes), while SMB3 - unseen - is given its Mario at
 * that pipe with the same button held: SMB3 decides whether it's a pipe it takes. Once the
 * player is in, SMB3 runs the junction to the end (the other area up, its Mario out of the exit
 * pipe) and the stage starts again on SMB3's new area - the clock, counters and lives kept -
 * its players at SMB3's Mario: on the exit pipe. A pipe that leaves the level: the map, as a
 * cleared level.
 * Doors (prg008 PRG008_A827): up pressed on the ground with the head before TILEA_DOOR2 ($43), or
 * TILEA_DOOR1 ($42) in a fortress: Level_JctCtl 3 (or 1 - out to the map). SMB3's Mario at the door
 * with up pressed; the player waits at it a moment (drawn behind it) while SMB3 does the junction. */

static struct { int on, n, dir, t, lc, row, kind, demo, done; } jp;   /* (done: the junction made - kept hidden through the fade, till the stage starts again) */    /* dir: 0 down, 1 up, 2 right, 3 left (into the pipe) */
#define PL_WARP_POS       1020                   /* mWarpPos (x, y, z) */
#define PL_DOKAN_TYPE     1044                   /* (1 a pipe, 2 a rail, 3 a water tank) */
#define PL_DOKAN_OFS      1060                   /* (the slide's length, from mWarpPos.y) */
#define PL_DEMO_SUBSTATE  5208
#define VT_SET_Z_POS_F    1064                   /* setZPosition(float) */
#define A_CHANGE_DEMO_STATE 0x8004E290u          /* daPlBase_c::changeDemoState(const sStateIDIf_c &, int) */
#define A_DOKAN_OUT_STATES  0x80308450u          /* (StateID_DemoOutDokanU, D, ... - setDemoOutDokanAction's table) */
static void pipes_reset(void) { memset(&jp, 0, sizeof jp); }
static int pipe_top(uint8_t t) { return (t >= 0xAD && t <= 0xB0) || t == 0xB3 || t == 0xB4; }
static int pipe_left(uint8_t t) { return t == 0xAD || t == 0xAF || t == 0xB3; }
static uint8_t cell_tile(int c, int r) { return c >= 0 && c < L.w && r >= 0 && r < LH ? L.tile[r * L.w + c] : 0; }

/* (smb3_stage_unit) the pipe's cells while a player goes in: passable */
static int pipe_open_cell(int tx, int ty) {
    if (!jp.on) return 0;
    if (jp.dir == 4) return 0;
    if (jp.dir <= 1) return (tx == jp.lc || tx == jp.lc + 1) && (jp.dir == 0 ? ty >= jp.row && ty < jp.row + 3 : ty <= jp.row && ty > jp.row - 3);
    return (jp.dir == 2 ? tx >= jp.lc && tx < jp.lc + 3 : tx <= jp.lc && tx > jp.lc - 3) && (ty == jp.row || ty == jp.row - 1);
}
static int pipe_hidden(int n) { return jp.on && jp.n == n; }

/* SMB3's Mario at the pipe, the button held, until it takes it (Level_PipeMove set) */
static int pipe_smb3_try(int big) {
    int x, y, pad, air = 0, yvel = 0;
    switch (jp.dir) {
    case 0: x = jp.lc * 16 + 8; y = jp.row * 16 - 32; pad = NES_DOWN; break;                         /* (on the top, in the middle) */
    case 1: x = jp.lc * 16 + 8; y = (jp.row + 1) * 16 + (big ? 2 : -14); pad = NES_UP; air = 1; yvel = -0x30; break;   /* (just under the bottom, jumping) */
    case 2: x = jp.lc * 16 - 14; y = (jp.row + 1) * 16 - 32; pad = NES_RIGHT; break;               /* (on the ground before the mouth) */
    case 3: x = jp.lc * 16 + 14; y = (jp.row + 1) * 16 - 32; pad = NES_LEFT; break;
    default: x = jp.lc * 16; y = jp.row * 16 - 32; pad = NES_UP; break;                             /* (a door: in its column, up pressed) */
    }
    int scr = x - 0x70; if (scr < 0) scr = 0; if (scr > L.w * 16 - 256) scr = L.w * 16 - 256;
    for (int i = 0; i < 24; i++) {
        if (i == 0 || jp.dir != 1 || S3(SMB3_Player_InAir) == 0) {      /* (up: jumping again until it hits) */
            S3W(SMB3_Player_XHi, (uint8_t)(x >> 8)); S3W(SMB3_Player_X, (uint8_t)x);
            S3W(SMB3_Player_YHi, (uint8_t)(y >> 8)); S3W(SMB3_Player_Y, (uint8_t)y);
            S3W(SMB3_Player_InAir, (uint8_t)air); S3W(SMB3_Player_YVel, (uint8_t)yvel); S3W(SMB3_Player_XVel, jp.dir == 2 ? 0x10 : jp.dir == 3 ? 0xF0 : 0);
        }
        if (i == 0) { S3W(SMB3_Player_Suit, (uint8_t)(big ? 1 : 0)); S3W(SMB3_Horz_Scroll_Hi, (uint8_t)(scr >> 8)); S3W(SMB3_Horz_Scroll, (uint8_t)scr); }
        S3W(SMB3_Player_FlashInv, 0x40);                                 /* (its objects can't hurt it meanwhile) */
        nes_set_buttons(0, (uint8_t)(jp.dir == 4 && !(i & 1) ? 0 : pad)); nes_run_frame();   /* (a door wants a new press: Pad_Input) */
        if (nes_error()) { rt_log("smb3", "pipe: SMB3 stopped: %s", nes_error()); return 0; }
        if (jp.dir == 4 && S3(SMB3_Level_JctCtl)) return 0x100 | S3(SMB3_Level_JctCtl);
        if (jp.dir != 4 && S3(SMB3_Level_PipeMove)) return S3(SMB3_Level_PipeMove);
    }
    return 0;
}
static int cond_jct_done(void) {
    if (getenv("SMB3_PIPE_LOG")) rt_log("smb3", "pipe: frame PipeMove %02X JctCtl %02X tileset %d ctl2 %02X X %d Y %d air %d", S3(SMB3_Level_PipeMove), S3(SMB3_Level_JctCtl), S3(SMB3_Level_Tileset), S3(SMB3_PPU_CTL2_Copy), S3(SMB3_Player_XHi) << 8 | S3(SMB3_Player_X), S3(SMB3_Player_YHi) << 8 | S3(SMB3_Player_Y), S3(SMB3_Player_InAir));
    if (S3(SMB3_Level_PipeMove) || S3(SMB3_Level_JctCtl) || S3(SMB3_Level_Tileset) == 0 || (S3(SMB3_PPU_CTL2_Copy) & 0x18) != 0x18) { lvl_frames = 0; return 0; }
    return ++lvl_frames > 40;                                           /* (its fade-in done: the palette read for the tiles - cond_in_level) */
}

/* each frame, each player (player_blocks): into a pipe */
static void pipe_frame(uint32_t pl, int n, int big, float px, float py, float h) {
    if (!map_shown_level()) return;                                      /* (SMB3's map session only: its level is the one up) */
    uint16_t keys = R16(pl + PL_KEY + 4); int ground = (R32(pl + PL_BG_CROSS1) & 1) != 0;
    float lx = px - L.lx, feet = -py - L.ly;
    if (jp.on) {
        if (jp.n != n) return;
        jp.t++;
        if (jp.demo) {
            /* the slide in: NSMBW's (its mDemoSubstate 1 moves it to mWarpPos.y + the offset at
               +1060) - the offset pushed out of reach, so the end (its own scene change) never
               comes: SMB3's junction takes over. Its depth: NSMBW's -1800 (setZPosition, behind
               its own pipes) would be behind this level's sky - kept where it was */
            if (R32(pl + PL_DEMO_SUBSTATE) == 1) WF(pl + PL_DOKAN_OFS, jp.dir == 0 ? -400.0f : 400.0f);
            if (getenv("SMB3_PIPE_LOG")) rt_log("smb3", "pipe: t %d substate %u y %.1f warp y %.1f ofs %.1f z %.1f", jp.t, R32(pl + PL_DEMO_SUBSTATE), RF(pl + PL_POS + 4), RF(pl + PL_WARP_POS + 4), RF(pl + PL_DOKAN_OFS), RF(pl + PL_POS + 8));
            uint32_t fz = R32(R32(pl + AC_VTABLE) + VT_SET_Z_POS_F);
            if (fz) { blk_ctx->f[1].d = blk_ctx->ps1[1] = pz; gcall(blk_ctx, blk_base, fz, 1, pl); }   /* (its usual depth: the tiles about it are drawn again in front of it - proc_draw) */
        }
        if (jp.done) return;
        if (jp.dir == 4 ? jp.t < 12 : jp.demo ? fabsf(RF(pl + PL_POS + 4) - RF(pl + PL_WARP_POS + 4)) < 32.0f && jp.t < 90 : jp.t < 40) return;   /* (in: NSMBW's slide (0.75 a frame) 32 deep, or ours) */
        jp.done = 1;
        if (jp.kind & 0x100 ? (jp.kind & 0xFF) == 1 : ((jp.kind >> 2) & 7) == 1) { jp.on = 0; rt_log("smb3", "pipe: out of the level"); map_level_end(blk_ctx, blk_base, 0); return; }
        rt_log("smb3", "pipe: SMB3's junction (Level_PipeMove %02X)", jp.kind);
        ppu_capture_at(212); lvl_frames = 0;
        int ok = map_run_until(cond_jct_done, 0, "the other area");
        ppu_capture_at(-1);
        if (!ok) { jp.on = 0; map_session_stop(); return; }
        for (int i = 0; i < 8; i++) kept_rest[i] = (int)R32(MOD_PY_REST + 4 * (uint32_t)i);
        for (int k = 0; k < 8; k++) if (pp[k].on && pp[k].pl) {           /* (each player's power-up kept into the other area - daPyMng_c::mPlayerMode by character, as NSMBW's own area change keeps it) */
            uint32_t t = R32(pp[k].pl + 5332);
            if (t < 8) W32(0x8185E95Cu + 4 * t, R32(pp[k].pl + PL_MODE));
        }
        keep_rest = 1; jct_restart = 1; L.ok = 0;
        rt_log("smb3", "pipe: the other area (tileset %d) - SMB3's Mario at %d, %d", S3(SMB3_Level_Tileset), S3(SMB3_Player_XHi) << 8 | S3(SMB3_Player_X), S3(SMB3_Player_YHi) << 8 | S3(SMB3_Player_Y));
        int k = keep_counters; keep_counters = 1; keep_modes = 1; stage_start_game(blk_ctx, blk_base); keep_counters = k; keep_modes = 0;
        return;
    }
    if (poof.on[n] || wb[n].behind || goal.phase) return;
    int c = (int)floorf(lx / 16.0f), dir = -1, lc = 0, row = 0;
    if (ground && (R16(pl + PL_KEY + 6) & 2)) {                         /* (a door: up pressed, the head before it - prg008 PRG008_A827: TILEA_DOOR2, DOOR1 in fortresses) */
        uint8_t t = cell_tile(c, (int)floorf((feet - (big ? 22.0f : 12.0f)) / 16.0f));
        if (t == 0x43 || (t == 0x42 && nes_ram_ptr()[0x70A] == 2)) { dir = 4; lc = c; row = (int)floorf((feet + 1) / 16.0f); }
    }
    if (dir >= 0) ;
    else if (ground && (keys & 1)) {                                          /* (down into a top) */
        row = (int)floorf((feet + 1) / 16.0f); uint8_t t = cell_tile(c, row);
        if (pipe_top(t)) { lc = pipe_left(t) ? c : c - 1; if (fabsf(lx - (lc * 16 + 16)) <= 8.0f) dir = 0; }
    } else if (!ground && (keys & 2)) {                                  /* (up into a bottom: the head at it - Player_HitCeiling) */
        row = (int)floorf((feet - h - 6) / 16.0f); uint8_t t = cell_tile(c, row);
        if (pipe_top(t)) { lc = pipe_left(t) ? c : c - 1; if (fabsf(lx - (lc * 16 + 16)) <= 8.0f) dir = 1; }
    } else if (ground && (keys & 0xC)) {                                 /* (sideways into a mouth) */
        int right = (keys & 4) != 0; row = (int)floorf((feet - 8) / 16.0f);
        int cf = (int)floorf((lx + (right ? 9.0f : -9.0f)) / 16.0f);
        if (cell_tile(cf, row) == 0xB5) { lc = cf; dir = right ? 2 : 3; }
    }
    if (dir < 0) return;
    jp.dir = dir; jp.lc = lc; jp.row = row;
    jp.kind = pipe_smb3_try(big);
    if (!jp.kind) { rt_log("smb3", "pipe: SMB3 didn't take the pipe at column %d row %d (dir %d)", lc, row, dir); return; }
    jp.on = 1; jp.n = n; jp.t = 0; jp.demo = 0;
    if (dir <= 1) {                                                      /* NSMBW's own: daPlBase_c's DemoOutDokanD / U (setDemoOutDokanAction) */
        WF(pl + PL_WARP_POS, L.lx + lc * 16 + 16);                       /* (mWarpPos: the pipe's middle, its mouth) */
        WF(pl + PL_WARP_POS + 4, dir == 0 ? -(L.ly + row * 16) : -(L.ly + (row + 1) * 16));
        WF(pl + PL_WARP_POS + 8, RF(pl + PL_POS + 8));
        W32(pl + PL_DOKAN_TYPE, 1);                                      /* (a plain pipe) */
        uint32_t st = R32(A_DOKAN_OUT_STATES + 4 * (dir == 0 ? 1 : 0));  /* (StateID_DemoOutDokanD / U) */
        if (st) { gcall(blk_ctx, blk_base, A_CHANGE_DEMO_STATE, 3, pl, st, 0); jp.demo = 1; }
    }
    rt_log("smb3", "pipe: player %d into the %s at column %d row %d (dir %d, %s %02X)", n + 1, dir == 4 ? "door" : "pipe", lc, row, dir, dir == 4 ? "Level_JctCtl" : "Level_PipeMove", jp.kind & 0xFF);
}
/* (smb3_stage_player_exec) the player in the pipe: no buttons, moving slowly in */
static void pipe_player_exec(uint32_t pl, int n) {
    if (!jp.on || jp.n != n) return;
    W16(pl + PL_KEY + 4, 0); W16(pl + PL_KEY + 6, 0);
    if (jp.demo) return;                                                 /* (NSMBW's demo moves it) */
    if (jp.dir == 4) { W32(pl + PL_SPEED, 0); W32(pl + PL_SPEED_F, 0); return; }   /* (at a door: still) */
    float sx = 0, sy = 0;
    switch (jp.dir) { case 0: sy = -1.0f; break; case 1: sy = 1.0f; break; case 2: sx = 1.0f; break; default: sx = -1.0f; break; }
    if (jp.dir <= 1) WF(pl + PL_POS, L.lx + jp.lc * 16 + 16);
    W32(pl + PL_SPEED, fbits(sx)); W32(pl + PL_SPEED_F, fbits(sx)); W32(pl + PL_SPEED + 4, fbits(sy));
    if (jp.dir >= 2) WF(pl + PL_POS + 4, -(L.ly + (jp.row + 1) * 16));   /* (level with the mouth's bottom) */
}
