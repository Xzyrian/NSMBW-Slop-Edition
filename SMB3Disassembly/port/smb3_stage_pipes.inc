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
#define STATE_DEMO_IN_DOKAN 0x8035482Cu          /* daPlBase_c::StateID_DemoInDokanU; D, R, L follow it 0x40 apart */
/* the way out of the other area's pipe: SMB3's Mario as the exit begins (the junction's first frame
   with the other area up - Level_PipeExitDir: 1 up, 2 down, 3 right, 4 left, 5 an in-level transit) */
static struct { int jct, got, dir, x, y, big; } jx;
/* the players coming out of it (NSMBW's own: daPlBase_c's DemoInDokanU / D / R / L) - dir as jp's
   (the side of the pipe its body is on: 0 below the mouth, 1 above, 2 to its right, 3 to its left) */
static struct { int on, dir, lc, row; float sx, sy, ex, ey; int st[8], t[8]; } px;
static void pipes_reset(void) { memset(&jp, 0, sizeof jp); memset(&px, 0, sizeof px); }
static int pipe_top(uint8_t t) { return (t >= 0xAD && t <= 0xB0) || t == 0xB3 || t == 0xB4; }
static int pipe_left(uint8_t t) { return t == 0xAD || t == 0xAF || t == 0xB3; }
static uint8_t cell_tile(int c, int r) { return c >= 0 && c < L.w && r >= 0 && r < LH ? L.tile[r * L.w + c] : 0; }

/* (smb3_stage_unit) the pipe's cells while a player goes in: passable */
static int pipe_cells(int dir, int lc, int row, int tx, int ty) {
    if (dir <= 1) return (tx == lc || tx == lc + 1) && (dir == 0 ? ty >= row && ty < row + 3 : ty <= row && ty > row - 3);
    return (dir == 2 ? tx >= lc && tx < lc + 3 : tx <= lc && tx > lc - 3) && (ty == row || ty == row - 1);
}
static int pipe_exiting(int n) { return px.on && n >= 0 && n < 8 && px.st[n] >= 1 && px.st[n] <= 2; }
static int pipe_open_cell(int tx, int ty) {
    if (px.on) for (int n = 0; n < 8; n++) if (pipe_exiting(n) && pipe_cells(px.dir, px.lc, px.row, tx, ty)) return 1;
    if (!jp.on) return 0;
    if (jp.dir == 4) return 0;
    return pipe_cells(jp.dir, jp.lc, jp.row, tx, ty);
}
static int pipe_hidden(int n) { return (jp.on && jp.n == n) || pipe_exiting(n); }

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
    snd_unseen(1);                                                       /* (SMB3's Mario's pipe sound: NSMBW's player makes its own) */
    for (int i = 0; i < 24; i++) {
        if (i == 0 || jp.dir != 1 || S3(SMB3_Player_InAir) == 0) {      /* (up: jumping again until it hits) */
            S3W(SMB3_Player_XHi, (uint8_t)(x >> 8)); S3W(SMB3_Player_X, (uint8_t)x);
            S3W(SMB3_Player_YHi, (uint8_t)(y >> 8)); S3W(SMB3_Player_Y, (uint8_t)y);
            S3W(SMB3_Player_InAir, (uint8_t)air); S3W(SMB3_Player_YVel, (uint8_t)yvel); S3W(SMB3_Player_XVel, jp.dir == 2 ? 0x10 : jp.dir == 3 ? 0xF0 : 0);
        }
        if (i == 0) { S3W(SMB3_Player_Suit, (uint8_t)(big ? 1 : 0)); S3W(SMB3_Horz_Scroll_Hi, (uint8_t)(scr >> 8)); S3W(SMB3_Horz_Scroll, (uint8_t)scr); }
        S3W(SMB3_Player_FlashInv, 0x40);                                 /* (its objects can't hurt it meanwhile) */
        nes_set_buttons(0, (uint8_t)(jp.dir == 4 && !(i & 1) ? 0 : pad)); nes_run_frame();   /* (a door wants a new press: Pad_Input) */
        if (nes_error()) { snd_unseen(0); rt_log("smb3", "pipe: SMB3 stopped: %s", nes_error()); return 0; }
        if (jp.dir == 4 && S3(SMB3_Level_JctCtl)) { snd_unseen(0); return 0x100 | S3(SMB3_Level_JctCtl); }
        if (jp.dir != 4 && S3(SMB3_Level_PipeMove)) { snd_unseen(0); return S3(SMB3_Level_PipeMove); }
    }
    snd_unseen(0);
    return 0;
}
static int cond_jct_done(void) {
    if (S3(SMB3_Level_JctCtl)) jx.jct = 1;                               /* (the way out: the first frame of the other area) */
    else if (jx.jct && !jx.got && S3(SMB3_Level_Tileset) != 0) {
        jx.got = 1; jx.dir = S3(SMB3_Level_PipeExitDir) & 0x0F;
        jx.x = S3(SMB3_Player_XHi) << 8 | S3(SMB3_Player_X); jx.y = S3(SMB3_Player_YHi) << 8 | S3(SMB3_Player_Y);
        rt_log("smb3", "pipe: the other area up - SMB3's Mario at %d, %d, out of its pipe %s", jx.x, jx.y,
               jx.dir == 1 ? "upwards" : jx.dir == 2 ? "downwards" : jx.dir == 3 ? "to the right" : jx.dir == 4 ? "to the left" : "(none: a door / transit)");
    }
    if (getenv("SMB3_PIPE_LOG")) rt_log("smb3", "pipe: frame PipeMove %02X JctCtl %02X tileset %d ctl2 %02X X %d Y %d air %d", S3(SMB3_Level_PipeMove), S3(SMB3_Level_JctCtl), S3(SMB3_Level_Tileset), S3(SMB3_PPU_CTL2_Copy), S3(SMB3_Player_XHi) << 8 | S3(SMB3_Player_X), S3(SMB3_Player_YHi) << 8 | S3(SMB3_Player_Y), S3(SMB3_Player_InAir));
    if (S3(SMB3_Level_PipeMove) || S3(SMB3_Level_JctCtl) || S3(SMB3_Level_Tileset) == 0 || (S3(SMB3_PPU_CTL2_Copy) & 0x18) != 0x18) { lvl_frames = 0; return 0; }
    return ++lvl_frames > 40;                                           /* (its fade-in done: the palette read for the tiles - cond_in_level) */
}

/* each frame, each player (player_blocks): into a pipe */
static int pipe_exit_frame(uint32_t pl, int n, float h);
static void pipe_frame(uint32_t pl, int n, int big, float px, float py, float h) {
    if (!map_shown_level()) return;                                      /* (SMB3's map session only: its level is the one up) */
    uint16_t keys = R16(pl + PL_KEY + 4); int ground = (R32(pl + PL_BG_CROSS1) & 1) != 0;
    float lx = px - L.lx, feet = -py - L.ly;
    if (pipe_exit_frame(pl, n, h)) return;
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
        ppu_capture_at(212); lvl_frames = 0; memset(&jx, 0, sizeof jx); jx.big = big;
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
/* (the stage placed on the other area, smb3_stage.c) the exit pipe from where SMB3's Mario began
   its way out: its mouth - a pipe's end ($AD-$B4: the exit pipes are often $B1/$B2, not enterable)
   above / below it, a sideways mouth ($B5) beside it. Every player comes out of it (NSMBW: one
   after another, daPyDemoMng) */
static int pipe_end(uint8_t t) { return t >= 0xAD && t <= 0xB4; }
static void pipe_exit_placed(void) {
    if (!jx.got) return;
    jx.got = 0;
    int d = jx.dir, lc = -1, row = -1;
    if (d >= 1 && d <= 2) {                                              /* (in the pipe, the middle of it at X + 8) */
        int c = (jx.x + 8 - 16) >> 4, rb = (jx.y + 16) >> 4;
        for (int i = 0; i < 9 && row < 0; i++) {
            int r = rb + ((i & 1) ? (i + 1) / 2 : -(i / 2));
            for (int k = 0; k < 3 && row < 0; k++) { int cc = c + (k == 1 ? -1 : k == 2 ? 1 : 0);
                if (pipe_end(cell_tile(cc, r)) && pipe_end(cell_tile(cc + 1, r))) { lc = cc; row = r; } }
        }
    } else if (d == 3 || d == 4) {
        int rf = (jx.y + 31) >> 4, c0 = (jx.x + 8) >> 4;
        for (int i = 0; i < 7 && row < 0; i++) {
            int c = c0 + ((i & 1) ? (i + 1) / 2 : -(i / 2));
            for (int k = 0; k < 3 && row < 0; k++) { int r = rf + (k == 1 ? -1 : k == 2 ? 1 : 0); if (cell_tile(c, r) == 0xB5) { lc = c; row = r; } }
        }
    }
    if (row < 0) { if (d >= 1 && d <= 4) rt_log("smb3", "pipe: no exit pipe found by SMB3's Mario (%d, %d, way %d) - the players stand where it came out", jx.x, jx.y, d); return; }
    px.on = 1; px.lc = lc; px.row = row;
    switch (d) {
    case 1: px.dir = 0; px.sx = px.ex = L.lx + lc * 16 + 16; px.ey = -(L.ly + row * 16); px.sy = px.ey - 34.0f; break;          /* (up: from inside, below the top) */
    case 2: px.dir = 1; px.sx = px.ex = L.lx + lc * 16 + 16; px.sy = -(L.ly + (row + 1) * 16) + 2.0f; px.ey = px.sy - 36.0f; break;   /* (down: out of the bottom) */
    case 3: px.dir = 3; px.sy = px.ey = -(L.ly + (row + 1) * 16); px.sx = L.lx + lc * 16 + 16 - 12.0f; px.ex = L.lx + lc * 16 + 16 + 14.0f; break;   /* (to the right: the body to the left) */
    default: px.dir = 2; px.sy = px.ey = -(L.ly + (row + 1) * 16); px.sx = L.lx + lc * 16 + 12.0f; px.ex = L.lx + lc * 16 - 14.0f; break;
    }
    rt_log("smb3", "pipe: the players out of the pipe at column %d row %d (%s)", lc, row, d == 1 ? "up" : d == 2 ? "down" : d == 3 ? "right" : "left");
}
/* each player's way out: hidden in the pipe, then NSMBW's DemoInDokan (it waits for the fade and
   its turn, plays the pipe's sound, slides out to mWarpPos, back to play) - 1: the frame is its */
static int pipe_exit_frame(uint32_t pl, int n, float h) {
    if (!px.on || n < 0 || n > 7 || px.st[n] == 3) return 0;
    if (!lifted[n]) return 1;                                            /* (placed on its first drawing: then) */
    if (px.st[n] == 0) {
        static const int way[4] = {0, 1, 3, 2};                          /* (dir -> DemoInDokanU / D / L / R: daPlBase_c's order) */
        uint32_t st = STATE_DEMO_IN_DOKAN + 0x40u * (uint32_t)way[px.dir];
        float sy = px.sy, ey = px.ey;
        if (px.dir == 0) sy = px.ey - h - 4.0f;                          /* (all of it in: its height) */
        if (px.dir == 1) ey = px.sy - h - 4.0f;
        WF(pl + PL_POS, px.sx); WF(pl + PL_POS + 4, sy);
        W32(pl + PL_SPEED, 0); W32(pl + PL_SPEED + 4, 0); W32(pl + PL_SPEED_F, 0);
        W32(pl + PL_DOKAN_TYPE, 1);
        gcall(blk_ctx, blk_base, A_CHANGE_DEMO_STATE, 3, pl, st, 0);
        WF(pl + PL_POS, px.sx); WF(pl + PL_POS + 4, sy);                 /* (its init moved it by NSMBW's pipe's own sizes: ours) */
        WF(pl + PL_WARP_POS, px.ex); WF(pl + PL_WARP_POS + 4, ey); WF(pl + PL_WARP_POS + 8, RF(pl + PL_POS + 8));
        px.st[n] = 1; px.t[n] = 0;
        {   uint32_t nm = R32(st + 4); char b[48] = "?"; if (nm) { int i = 0; for (; i < 47 && R8(nm + (uint32_t)i); i++) b[i] = (char)R8(nm + (uint32_t)i); b[i] = 0; }
            rt_log("smb3", "pipe: player %d out of the pipe (%s): (%.1f, %.1f) to (%.1f, %.1f)", n + 1, b, px.sx, sy, px.ex, ey); }
        return 1;
    }
    px.t[n]++;
    uint32_t sub = R32(pl + PL_DEMO_SUBSTATE);
    if (getenv("SMB3_PIPE_LOG") && (px.t[n] % 10) == 1) rt_log("smb3", "pipe: out t %d substate %u pos (%.1f, %.1f) warp (%.1f, %.1f)", px.t[n], sub, RF(pl + PL_POS), RF(pl + PL_POS + 4), RF(pl + PL_WARP_POS), RF(pl + PL_WARP_POS + 4));
    if (sub >= 2) px.st[n] = 2;
    int out = px.st[n] == 2 && sub != 2 && sub != 1;                      /* (substate 3 or the demo over) */
    if (out || px.t[n] > 600) {
        px.st[n] = 3;
        rt_log("smb3", "pipe: player %d out%s", n + 1, out ? "" : " (gave up waiting)");
        int any = 0; for (int k = 0; k < 8; k++) any |= pipe_exiting(k); if (!any) px.on = 0;
        return 0;
    }
    return 1;
}
/* (smb3_stage_player_exec) the player in the pipe: no buttons, moving slowly in */
static void pipe_player_exec(uint32_t pl, int n) {
    if (pipe_exiting(n) || (px.on && n >= 0 && n < 8 && px.st[n] == 0)) { W16(pl + PL_KEY + 4, 0); W16(pl + PL_KEY + 6, 0); return; }
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
