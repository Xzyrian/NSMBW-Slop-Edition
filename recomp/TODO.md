# TODO

Shared list for the user and both Claude instances. Keep it current: when you start something,
put your name on it; when it's done, move it to "Done" with the date (details go in
`CHANGELOG.md`). The user decides priorities - ask before reordering "Next up".

Legend: `[ ]` open, `[~]` in progress (who), `[x]` done.

## Next up (user's list)

- [x] **SMB3 sound in NSMBW's sound archive** (user, 2026-11-27; Claude - this session): songs and sound effects made at build time, NSMBW's sound archive expanded with them (CHANGELOG 134, 136). A door / pipe keeps the song playing; the stage's sound effects (137). Open: an upward / sideways pipe exit not checked.
- [~] **GitHub issues** (user, 2026-11-27: "begin working on the GitHub issues", github.com/Xzyrian/NSMBW-Slop-Edition/issues) - claimed by **Claude instance 1**: #4, #16 and #15 fixed 2026-11-27 (CHANGELOG 135). Other sessions: please pick other numbers and add your claim here.
- [~] **SMW** (user, 2026-11-27: "lets begin implementing SMW ... make it playable to 1-1") - Claude: recompiled whole and playable from a new file through Yoshi's Island 1 (CHANGELOG 138, `SMWDisassembly/port/README.md`). NSMBW players in its levels begun (CHANGELOG 139: its tiles, slopes and background in an NSMBW stage; 140: Exit Course / side exits back to SMW's map, SMW's camera, Yoshi's House). Next: the goal and back to SMW's map, SMW's blocks / items / enemies, sound (SPC700 + DSP).
- [~] **Native port: from emulation to a decompiled PC port** (user, 2026-10-16: performance,
  modding and principle; online play may be taken apart) - `docs/NATIVE_ROADMAP.md`.
  Split (user, 2026-10-16): track A (platform: SDK libraries native, no emulated hardware)
  instance 1; track B (game code decompiled class by class) instance 2.
  - [~] A1 GX (FIFO/CP/PE/PI native: done; GX state functions + the pipe: next)  - [~] A2 OS (VI, interrupt controller, MI/PI/EXI native: done; threads/alarms/timing: next)
  - [x] A3 disc/saves (DVD reads + IOS client native)  - [x] A4 input (SI/GameCube pads native; WUD native: remotes talk HID to WPAD directly, Bluetooth stack gone)  - [x] A5 audio (AI + DSP native)
  - [x] A6 hardware layer deleted: rt_hw.c is the field clock + the GX write-gather pipe; any other register access is logged (RT_MMIO_STRICT=1: fatal)
  - [~] B (instance 2, `docs/DECOMP.md`): the game code decompiled class by class, checked by
    `RT_GM_VERIFY` / `RT_GM_SELFTEST` and A/B replays. Done: the module's save data and session
    info (`dMj2dGame_c`, `dMj2dHeader_c`, `dSaveMng_c` in part, `dInfo_c`: 67 functions) and
    the complete player manager (`daPyMng_c`: 39/39, parts 61 and 77), the complete demo manager
    (`daPyDemoMng_c`: 27/27, parts 72-74), the complete speech-bubble manager and child layout
    (`dfukidashiManager_c`: 9/9, part 77; `dfukidashiInfo_c`: 6/6, part 78), and the complete HUD
    (`dGameDisplay_c`: 29/29, parts 68-71, 75-76 and 79). The five safe goal methods in Part 72 passed
    669 strict live calls; world-changing methods passed isolated A/B. Part 73 fixed calcNotGoalPlayer's
    key-flag address and ported executeGoalDemo_Pole; both clear A/Bs match all 1,367 baseline gameplay /
    scene / test events, including the in-play coin deletion. Part 74 enabled the nine control-demo /
    toride methods. Directed live-player calls covered every method, strict query checks found no
    differences, and the native / PowerPC A/B matched all 1,129 events. Part 75 ported both goal
    settlement methods; normal and assist A/Bs each match all 1,367 events. Part 76 added the HUD's
    lifecycle, layout, lives display and per-frame visibility methods; all isolated A/Bs match 1,367 events.
    Part 77 completed player spawning and all nine speech-bubble manager methods; the full A/B matches
    1,367 events and directed calls covered the three otherwise unreached methods. Part 78 completed
    the six child-layout methods with directed register checks. Part 79 completed the HUD; its directed
    A/B matches all 1,371 ordinary / test events and the final clean A/B matches all 1,367 events.
    Part 80 completed dGameCom (6/6), and Part 81 completed dSaveMng_c (13/13). Part 82 completed
    dNandThread_c (5/5): directed asynchronous save / rename / delete A/B matched all 1,370 events,
    and the final clean A/B matched all 1,367 events. Part 83 completed dScWMap_c (4/4), including
    its world-dependent player layouts and saved course restoration; the clean A/B matched all
    1,367 events. Part 84 completed dWmSeManager_c (7/7): directed dispatch / voice / movement /
    destruction A/B matched all 1,387 events, and the final clean A/B matched all 1,367 events.
    Part 85 completed daWmSubPlayer_c (9/9): directed calls on all eight live companions matched
    all 1,400 ordinary / test events, and the final clean A/B matched all 1,367 events.
    Part 86 completed daWmMap_c (2/2): directed calls on the live map covered both route-override
    states, matched all 1,370 events and passed full-register checks; the clean A/B matched all 1,367.
    Parts 87-88 completed daWmPlayer_c (13/13), Part 89 completed dCourseSelectGuide_c (5/5),
    Part 90 completed dCourseSelectManager_c (11/11), Part 91 completed dSelectPlayer_c
    (11/11), Part 92 completed dContinue_c (13/13), Part 93 completed dStockItem_c (8/8),
    Part 94 completed dMultiCourseSelect_c (4/4), Part 95 completed dStaffCreditScore_c (9/9),
    and Part 96 completed dSmallScore_c (4/4). Part 94's three directed A/Bs each matched all
    1,029 retained events, including 14 directed results per run. Part 95's directed A/B matched
    all 1,432 retained events, including 16 directed results. Part 96's directed A/B matched all
    1,439 retained events, including 30 directed log events. Parts 94-96's final clean A/Bs
    matched all 1,409 retained events. Part 70's time-change and rest-coin animation call paths
    still need directed input. Part 102 (instance 2): the module's controller input
    (`gm_py_key.c`: dGameKey_c / dGameKeyCore_c / dAcPyKey_c, 9 on, 3 unreached and off) and its
    player overrides (`gm_py_player.c`: dAcPy_c / daPlBase_c, 16 on, 8 unreached and off); strict
    A/B 0 differ on five inputs including the 1-1 clear.
    Next: the 11 unreached player / key functions need directed input; then the game's own
    `dAcPy_c` / `daPlBase_c` (DOL), then camera / scroll. Part 103 (instance 2): the game's own
    player classes started - 254 small methods native (`gm_d_player_base.c` 150 + 4 off,
    `gm_d_player.c` 104); part 104: wave 2 (97-160 bytes, 103 more); part 109: the rest the seven inputs reach by `tools/gm_conv.py` (`gm_d_player_conv.c`, 243 - names owed); named and described in part 110; part 111: eight more A/B inputs picked by coverage (`tools/ab_inputs/` f1, p1-p5, s1, s2), 74 more on; part 114: the user's recorded play (`tools/record_play.bat`), 41 more (396 unreached left: swimming, vines, demos, Yoshi need inputs). Part 112: **the stage-objects module d_basesNP claimed by instance 2** (fn_2_*, 0x8076D8C0-0x80933800, `gm_bs_bases.c`: 2,327 on by the converter, 119 more in part 114 - everything the 15 inputs reach that no other file uses; names owed). Part 116: **the boss module d_en_bossNP claimed by instance 2** (fn_4_*, 0x80B1CA50-0x80B74000, `gm_eb_boss.c`: 380 on by the converter; names owed). Part 117: the 8-player module's reached functions by the converter (`gm_mj_conv.c`, 312). Part 118: **claimed by instance 2 - the player family and the world map in the DOL** (E2 0x8014A6F0-0x8015F4F0, 0x800D1500-0x800D8400, 0x800CAA10-0x800CCA40; 0x800F32F0-0x80106DF0 - `gm_pf_family.c` 430, `gm_wmc_worldmap.c` 268 on; names owed). Part 115: the end-to-end check against a build with no natives (instance 2's bench `wt_pure`): three bugs fixed in gm_d_gamedisplay.c / gm_d_sc_wmap.c; open: b / d / p3 / r_w8-7 still differ (CHANGELOG (115): fanm_c::set and two plain natives for instance 1). Part 110: **camera / scroll claimed by instance 2** - dBg_c / dBg_ctr_c / dBgParameter_c (E2 0x80076800-0x80084000, `gm_bg_scroll.c`: 157 on by the converter, 13 more in part 111; names owed)
  - [~] B (instance 1, from 2026-10-17, same method `docs/DECOMP.md`): the engine under the game -
    the framework (`fBase_c`, `fManager_c`, `fTree*`, `fLiMg*`, profiles), `cLib` / `sLib` (lists,
    trees, state machines, math, random), then the actor bases `dBase_c` / `dBaseActor_c` /
    `dActor_c` and the enemy base `dEn_c`. Files `runtime/gm_f_*.c`, `gm_c_*.c`, `gm_s_*.c`,
    `gm_d_base*.c`, `gm_d_actor.c`, `gm_d_enemy.c` (instance 2: not these classes). Done: the cLib lists and trees and the framework's lists of bases
    (`gm_c_list.c`, `gm_f_list.c`: 18 functions), `fBase_c` and `fManager_c` (`gm_f_base.c`,
    `gm_f_manager.c`: 33), the state machines (`gm_s_state.c`: 20), `dBase_c` / `dBaseActor_c` (`gm_d_base.c`:
    35), `dActor_c` (`gm_d_actor.c`: 42, plus 14 written but off), `dEn_c` (`gm_d_enemy.c`: 44, plus 28 written but off). Part 35: guest frames for all of them (`GM_FN`, prologues replayed from `gm_prologue.c`), strict A/B against a build without them, two bugs fixed (scrOutCheck deleted the wrong actors; the module's state functions were overridden). Part 36: the enemy death / states and dEnCombo_c (`gm_d_enemy_death.c`: 46 on, 44 written but off - a test run with power-ups / Yoshi would switch most of them on). Part 37: every state-ID template copy native (2946, generated), dEnemyCarry_c (written, off), the background tile lookups (`gm_bg.c`, picked by a call profile of the tests). Part 38: mLib m3d (`gm_m3d.c`, 68). Part 39: the rest of m3d (`gm_m3d_scene.c`, `gm_m3d_anm.c`: 101 on). Part 40: mMtx_c / mVec3_c, mHeap, the allocators, the faders (`gm_m_mtx.c`, `gm_m_heap.c`, `gm_m_allocator.c`, `gm_m_fader.c`: 70 on), and GM_CALLR (calls with the real return address). Part 41: dCc_c collision (`gm_d_cc.c`, 19 on), GM_CALLR in the older files (`tools/gm_callr.py`). Part 42: the 1-1 / 4-1 blips found (run-time bisect) and fixed (gm_s_state.c, gm_f_base.c, a gm_prologues.py bug). Part 43: mLib m2d and mFrustum_c (`gm_m_2d.c`, `gm_m_frustum.c`). Part 44: the sLib / cLib helpers (`gm_s_lib.c`, `gm_c_lib.c`: 29 on), register-exact, with the new `RT_GM_VERIFY_REGS=1` check. Part 46: mFrustum_c::set, dCdFile_c (`gm_d_cd.c`), dRail_c / mColor::lerp (written, mostly off). Part 47: dActorCreateMng_c (`gm_d_actorcreate.c`). Part 48: the framework / dBaseActor_c / dActor_c natives register-exact; the field-863 word fixed (f31's ps1 leaking through stfd / lfd: GM_NV_KEEP keeps ps1 only for psq_st prologues). Part 49: the layout wipes (`gm_d_wipe.c`), dCdFile_c's getters' frames. Part 50: the score pop-ups and the 2D GX state keeper (`gm_d_smallscore.c`). Part 51: dSys_c::execute (the frame) and dScene_c (`gm_d_scene.c`). Part 52: dNext_c (`gm_d_next.c`, a self-test for what no input reaches). Part 53: LytBase_c's animations (`gm_d_lytbase.c`). Part 54: the rest of fBase_c / dBase_c / dBaseActor_c (all native now but the module's). Part 56: the 2,946 state-ID natives register-exact, dEn_c::PlayerCarryCheck's poll count - the no-input A/B clean; the older natives' loops checked against their back-edges (part 57): no other poll mismatch. Part 57: the world map's dWmActor_c and dCsvData_c getters (`gm_d_wm.c`), dScStage_c::getLoopPosX (`gm_d_stage.c`); mFrustum_c::intersectSphere's temporaries were written into the caller's frame and changeStateMethod had no frame (prologue scanner) - fixed. Part 58: d2d (`gm_d_2d.c`). Part 59: dRes_c (`gm_d_res.c`). Part 60: info_c / dResMng_c; `<FILE>_COUNT` builds (first-call logs) found 12 unreached natives in parts 57-60 - off. Part 62: the rest of LytBase_c (`gm_d_lytbuild.c`) and LytTextBox_c (`gm_d_lyttextbox.c`). Part 63: dMessage_c / MsgRes_c (`gm_d_message.c`), dSelectCursor_c (`gm_d_selectcursor.c`), dSmallScoreManager_c's life. Part 64: dCoin_c / dCurtainMng_c / dDvd (`gm_d_misc.c`), Util::FrameCounter_c written but off (`gm_d_util.c`). Part 65: the first library natives - nw4r::ut lists (`gm_nw4r_ut.c`, 10), EGG::ColorFader (`gm_egg.c`, 5 on, 3 off), the hottest nw4r g3d / math leaves of the call profile (`gm_nw4r_g3d.c`, 99 on, 1 off: MSL strcmp / memcmp and some mTexture_c / EGG / 2D-state leaves too). Part 66: 31 more there (130 on) - MSL libm (sin / cos / tan and their kernels) / strncmp, the g3d camera's projection matrices, ScnObj::SetMtx, panes' global position / matrix. Part 98: 14 more (144 on) - the texture-buffer manager / allocator, mTexture_c init, the animation key / texture-entry lookups, scene change, ScnObj's world matrix; left: the hermite keyframe evaluator 0x80240100. Part 99: 23 more (167 on) - the small hot leaves, G3DState::Invalidate, node world matrices, the texture-matrix cache, mTexture_c's EFB copy; Part 100: 20 more (187 on) - those, the hermite keyframe evaluators, the material flush, lights; `tools/gm_leafconv.py` for paired-single leaves. Left in the profile: the snd functions under OSDisableInterrupts (0x80264220, 0x80263B90, 0x802638A0, 0x80261E70, 0x802628A0), 0x8022D5F0, 0x802C9C40, 0x80258430, 0x80248B80 (saves f31). Part 101: 11 more (198 on) - ScnRoot::GetCamera, GXSetTevColor, the 2D objects' scissor / draw state. Part 105: the library range by `tools/gm_conv.py` - 1,713 more (1,911 on: every convertible function the tests reach); all named and described (106). Part 107: 28 more (1,939 on), the jump-table and computed-frame shapes, two new A/B inputs (`tools/ab_inputs/`: HOME / pause menus, the world map). Left: ~1,240 unreached (a survey of 11 more inputs found 21: the rest is virtual methods of unused classes, the disc-error / HOME draw paths, debugger hooks, shutdown), 202 under the interrupt lock. Part 55: a no-input A/B (the attract demos) - dEn_c::posMove register-exact, 72 GM_CALLs given their return address; left: ~170 GM_CALLs with LR = 0 in the older natives (helpers, mismatched call counts: give them GM_CALLR by hand), (the one-field blips of the long runs are gone: part 101's strict A/B is identical on every frame of all four inputs, 42-47k frames each; the last one, the title demos' 29443, was dead stack left by `dActor_searchNearPlayer` not holding r31 - CHANGELOG (101) has the recipe). Next: test inputs that take a pipe, a door and a level end (dNext_c::changeScene, the wipes' pipe / Bowser variants); the rest of mLib (m_wipe_fader, mEf, mPad), dCc_c trapezoids, a test run with rail platforms (dRail_c), the older natives' NV / CR / volatile exactness (gm_d_actor.c, gm_d_enemy.c ...: `RT_GM_VERIFY_REGS=1` now lists what each leaves different)
  - [~] B (instance 1, from 2026-11-15, user's choice): **the enemy module `d_enemiesNP`** (`fn_3_*`,
    0x809A2EE0-0x80ACD1F8, 7,698 functions: the enemy classes on top of `dEn_c`) - the reached
    functions through `tools/gm_conv.py` (+ named and described), strict A/B on `tools/ab_inputs/`.
    File `runtime/gm_en_*.c`. Instance 2 / Kimi: not this module, please (tell me in CHANGELOG
    if you need one of its functions).
    Part 108: 855 on (`gm_en_enemies.c`: everything the seven inputs reach, named and described;
    classes named from their state-name strings). Next: inputs that meet the other worlds' enemies,
    the 104 the 8-player module wraps.
  - [x] online play may be paused while track A runs (user, 2026-10-16)
- [~] **Player profiles** (user, 2026-10-15) - `docs/PROFILES.md`. Player data moves from the
  characters to the people playing.
  - [x] step 1: profiles (ID, 4-letter username, preferred character, stats fields),
    Who's playing? per controller, preferred character preselected, online HELLO carries them
  - [ ] multiplayer save: lives / coins / power-up per profile ID instead of per character;
    per-save stats
  - [ ] count the stats (levels cleared, deaths, coins) for each PC's own players
  - [ ] usernames over the players in the game (multiplayer only)
  - [ ] delete a profile; show the profile on the character select card
  - [ ] maybe: a central account server (same profile on several PCs)
- [~] **Update check / auto-update** (user, 2026-10-15) - `docs/UPDATES.md`. Done: the update screen
  after "hold the Wii Remote sideways" (spinner, download bar, skip), a signed update list
  (Ed25519) + files by SHA-256 on the user's copyparty server, `tools/publish_update.py`
  (keygen / publish / upload), install by renaming the running exe + pending files at the next
  start, version in Options, online HELLO refuses a different version.
  - [ ] **first run on Windows** (WinHTTP, renaming the running exe, the restart)
  - [ ] the user's server address (`update_url.txt`) and key (`keygen`)
  - [ ] maybe: compress the files on the server (the exe is ~62 MB; it shrinks a lot)
  - [ ] maybe: show the update's notes on the screen; a "check for updates" in Options
- [ ] **4:3 overhaul** (user, 2026-10-15): 4:3 must show *more playfield vertically* instead of
  zooming in (the current implementation is wrong). Note for online play: the aspect mode
  changes the camera, so it changes what the game simulates (spawns, culling) - it must be the
  host's in a session (a host-decided setting).
- [~] **Online multiplayer** (Claude instance 2) - `docs/ONLINE.md`. Direct IP, whole session.
  - [x] phase 1: connection, host/join screen, online players in the host's slots
  - [x] model: deterministic lockstep, then rollback (user, 2026-10-15)
  - [x] deterministic mode: virtual clock, inputs latched per video field, state hash
    (`rt_det.c`); two runs with the same inputs identical (incl. random host delays)
  - [x] online session: host starts it, save + settings + player map sent, everyone restarts
    into lockstep (input delay), state-hash checks (loopback: identical over 2600 fields)
  - [ ] test on two real PCs (Windows, GL) over the internet
  - [ ] two copies on one PC share the real Wii Remotes (both read them): fine with the keyboard
    in one window; for one-PC tests a remote should belong to one copy
  - [ ] a client goes back to its own game and leaves the lobby when the game ends: maybe stay
    in the lobby
  - [ ] while waiting for the others, draw a message in the window (now only the title bar)
  - [ ] a client can't use our menus in the session (only player 1 drives them): a local
    "leave" for clients, and keep a PC that leaves from ending the game for everyone (its
    players could stand still)
  - [~] check the game version and `mod/` folder match before starting a session (the version: done, HELLO)
  - [x] save states (rt_state.c, docs/SAVE_STATES.md): in-process and across copies, verified
  - [x] the online game starts from the host's running game (no restart), back to your own game
    at the end (user, 2026-10-15)
  - [ ] Windows: first run of the new fibers / fixed addresses / save states (untested there)
  - [x] speed at high ping (user, 2026-10-16: 20 FPS at 150 ms): direct path (a client runs a
    field once it has everyone's buttons, not once the host published it), automatic input
    delay from the pings, automatic RESYNC instead of OUT OF SYNC
  - [x] rollback (user, 2026-10-16: "the goal was 0 ms input latency"; players who couldn't
    catch up watched the game like a video): the default now, input delay 0. States of the last
    48 fields from written pages only (Windows GetWriteWatch / Linux mprotect), undo lists,
    silent re-runs, the host forwards buttons and decides for a PC that's away, time sync,
    catching up without states, the host waits for everyone to load. Identical in every
    Linux test (150/300 ms, 3 PCs, drops, rejoin) - docs/ONLINE.md "Rollback"
  - [ ] rollback on Windows: GetWriteWatch, the speed of re-running fields with a real
    renderer, a game over the internet
  - [ ] rollback: a direct client-to-client path for buttons (now through the host: two trips)
  - [ ] a rollback can make another player jump: smoothing / showing them a little later is
    possible but not done
  - [x] user: smoother online flow: Multiplayer > Online, host chooses game + file, starts at
    the character select (2026-10-15)
  - [x] user: a player dropping out / closing doesn't end the game; reconnect, rejoin
  - [ ] a dropped player's characters just stand there: show them as disconnected in the game
  - [ ] two players rejoining at the same moment (the second one's state replaces the first's
    while it loads: it fails its page check and has to join again)
  - [~] user: settings follow the host, except local ones (volume, controllers, display) and
    character picking - done inside a session (the host's settings.ini, local keys kept); the
    lobby screens themselves still need it
  - [ ] user: several local players from one PC (the protocol has up to 4 per PC; needs UI and
    testing)
  - note: the null renderer and the GL renderer drift apart (from field ~2394 in 1-1: g3d
    matrices); GL vs GL is identical - all peers use GL. Find what the guest reads that depends
    on the renderer.
- [~] **Wii Remote handling** (Claude instance 2) - `docs/WIIMOTES.md`. Up to 8 real remotes,
  pairing for good from Options > Controls (SYNC button), a connecting remote takes the next
  free player slot (Controls can move things for the session), player lights.
  - [x] code: Windows pairing + 8 HID remotes, slots/memory/lights, 4 WPAD remotes, GC ports 5-8
  - [x] pairing hung (BluetoothAuthenticateDeviceEx + callback never returned): Dolphin's way now
  - [x] slots: next free slot on connect (2026-10-15; fixed slots before); Left/Right in
    Controls changes a slot's controller for the session; keyboard in any slot (kept)
  - [x] remotes switch off when the game closes
  - [ ] user: test pairing (after "Remove device" in Windows too), reconnecting, slot changes
    with real remotes on Windows (log lines `[wm]`, `[remotes]`)
- [~] **Character list: 12 characters, room for more** (Claude instance 2) - `docs/CHARACTERS.md`.
  Roster (in order; first five on the title screen): Mario, Luigi, Ala Gold, Buckenberry,
  Toadette | Toadsworth, Daisy, Rosalina, Goomba, Retro Mario (SMB1), Retro Mario (SMB3), Retro Mario (SMW), Retro
  Mario (SM64). Purple Toadette is dropped.
  - [x] character table (`runtime/rt_chars.c`); players remember the character they picked
  - [x] character select: NSMBW's cards walk all 12 (left/right); portraits from files
  - [x] title screen: first five only
  - [x] portraits: from the mods (Daisy, Rosalina, Goomba), HUD icons scaled (Toadette,
    Toadsworth), placeholders (retro characters) - [ ] user: better ones where wanted
  - [x] models from the mods: Toadsworth, Daisy, Rosalina (`runtime/rt_charmdl.c`)
  - [x] singleplayer: lives / power-up follow the save file whatever the character
  - [ ] world-map figures, voices, HUD icons for Toadsworth / Daisy / Rosalina
  - [ ] per-character lives / power-ups (today per body: Retro Mario shares Mario's)
  - [ ] more than 8 player types, so no two characters share a body (today Mario and Retro Mario
    can't play together if Retro took Mario's body first)
  - [ ] save format v2 (per character; remember each slot's character)
  - [ ] Goomba's model (from its mod) - needs a 9th body
- [~] **Retro Mario (SMB1)** (Claude instance 2) - `docs/RETRO_MARIO.md`.
  - [x] 2026-11-27: rebuilt - SMB1's own code run from the ROM (`runtime/smb1_mario.c`,
    `smb1_cpu.c`, `tools/smb1_embed.py`): movement, pictures, sounds (CHANGELOG 142); the port
    (`smb1_physics.c`) and the drawn sheets (`ui/retro/mario/`) are gone
  - [x] an NSMBW player driven by the SMB1 physics, collision fed back (`runtime/rt_retro.c`)
  - [x] drawn as a 1-tile sprite plane, SMB1 animation rules
  - [x] no 3D model anywhere: world map, select figure, ... are the sprite plane too
    (left/right only); [ ] HUD head icons (2D) for the retro characters
  - [x] selection: an entry in the character select (character 10)
  - [ ] more pictures in NSMBW states (carry, kick, pipes, victory; grow and throw: done), play-testing
  - [ ] the star's palette cycling in play (works on its own; NSMBW's star timer not found at +0x1070?)
- [~] **Retro Mario (SMB3)** (user, 2026-11-27: "add SMB3 Mario as a character / should have
  authentic SMB3 physics") - Claude: SMB3's player code ported (`runtime/smb3_physics.c`), SMB3's
  own sprites and sounds, small / Super / Fire / Raccoon / Frog (CHANGELOG 141, docs/RETRO_MARIO.md).
  Open: the tail swipe against NSMBW enemies, the Tanooki statue, SMB3's death song, portrait.
- [ ] **Retro Mario (SMW), Retro Mario (SM64)** - characters 12 and 13 of the roster: same
  approach as SMB1 (a movement port + sprites), designs to settle with the user.
- [~] **Discord Rich Presence** (Claude instance 1, 2026-10-15) - `docs/DISCORD.md`. What you're
  doing (title, world map, level, online) on your Discord profile, through Discord's local IPC
  (no SDK). Code done (2026-10-16).
  - [x] Discord application ID in `recomp/discord_app_id.txt` (2026-10-16)
  - [ ] user: art assets in the Discord application (`logo`, character ids) - docs/DISCORD.md
  - [ ] first run with the real Discord app (Windows)
- [ ] **Audio controls in the config** - music and sound-effect volume (master too?) in Options,
  saved to settings.ini, applied live.
- [ ] **Pause menu with settings** - the in-game pause menu gets access to some Options entries
  (which ones: to decide - e.g. audio, display, controls).

## Open (from earlier work)

- [ ] **Multiple controllers / players joining** - the multiplayer flow is built (8-player
  character select, Start Game once players 1 and 2 have chosen), but only one controller is
  read, so a second player can't join yet. Goes with "Wii Remote handling" (and keyboard /
  other pads per player).
- [ ] **Controls screen** - still a placeholder (keyboard list). Should become per-player
  control settings (rebinding, which device is which player).
- [x] **Boot: "Do not hold your keyboard sideways."** - the controller screen for a keyboard
  player 1, after the console's "Hold the Wii Remote sideways." (user's drawing, 3D keycaps,
  game font) - docs/BOOT_SCREEN.md (2026-10-16)
- [x] **Update screen in the boot's real panel** (rounded, game font for its text) (2026-10-16)
  - [ ] not run on Windows yet (the layout positions in widescreen modes, the fade)
- [ ] **Game Select** - pinned: currently one card. Meant for level and map packs;
  needs restructuring (where packs live, how a pack replaces stages/maps) before more entries.
  - [x] game portraits: `ui/graphics/gameportrait/<id>.png` on the card, which takes the
    picture's shape (user, 2026-10-16) - docs/GAME_SELECT.md
  - [ ] with several games: the cards side by side (the file select has three places), the
    game's name under / over its portrait
- [ ] **Free-for-All / Coin Battle** - reachable from the multiplayer File Select and go to the
  8-player character select; nothing past that has been tested.
- [ ] **Native port of the 8-player module** - 298 of 1318 functions are native (`NATIVE_PORT.md`,
  `python3 tools/native_port_status.py`). daPyDemoMng_c is 27/27, daPyMng_c is 39/39,
  dGameDisplay_c is 29/29, dfukidashiManager_c is 9/9, dfukidashiInfo_c is 6/6, dGameCom is 6/6,
  dSaveMng_c is 13/13, dNandThread_c is 5/5, dScWMap_c is 4/4, dWmSeManager_c is 7/7,
  daWmSubPlayer_c is 9/9, daWmMap_c is 2/2, daWmPlayer_c is 13/13, dCourseSelectGuide_c is 5/5,
  dCourseSelectManager_c is 11/11, dSelectPlayer_c is 11/11 and dContinue_c is 13/13.
  Next: dStockItem_c, then the remaining menus.
- [ ] **Module save names** - renamed at link time (`tools/link_mod.py`); goes away when the
  save code (`dNandThread_c`) is ported.

## Known issues

- Input is ignored during the ~0.5 s fades between setup screens (on purpose - a press during a
  fade used to freeze the menus).

## Done

- [x] 2026-10-15 - SMB1 Mario: no slope slide / small crouch / carrying / Yoshi (and the Yoshi
  model bug), SMB1 goal pole (slide, swing, walk into the castle), vines left/right only, clean
  swim frames, no particles (level, water, map), big Mario sheet, SMB1 sound effects.
- [x] 2026-10-15 - Wii Remotes take the next free slot when they connect (positions not kept).
- [x] 2026-10-14 - Wii Remotes: fixed player slots set in Controls (Left/Right: keyboard /
  remote / none, swapping), keyboard in any slot; pairing rewritten the way Dolphin does it.
- [x] 2026-10-14 - Wii Remotes: pairing dialog (SYNC, permanent), up to 8 real remotes
  (players 1-4 Wii Remote channels, 5-8 GameCube ports), remembered slots, player lights.

- [x] 2026-10-14 - Singleplayer character select: Start Game only once chosen, centred, no Back
  button; 1 takes the character back, 1 again goes back to the File Select.

- [x] 2026-10-14 - Retro Mario: the sprite plane replaces the 3D model everywhere (world map,
  character select figure, ...), left/right facing rules from the user.

- [x] 2026-10-14 - Select cards: the original slide is back (both faces show their character);
  the card window clips them again (a 4:3 scissor hack had removed the game's clip).

- [x] 2026-10-14 - Select: one portrait at a time; Toadsworth/Daisy/Rosalina models and mod portraits;
  Retro Mario smooth, follows slopes, no particles; singleplayer state follows the save file.
- [x] 2026-10-14 - Character select walks the 12-character roster; portraits for every character
  (the missing ones for characters 5-8 were a bug); title screen shows the first five.
- [x] 2026-10-14 - Retro Mario (SMB1) playable: SMB1 physics + sprite, picked in the character select.
- [x] 2026-10-13 - Title screen: buttons other than 2/A started singleplayer directly.

- [x] 2026-10-13 - Multiplayer: pressing 1 (or 2) while the character select was fading in
  froze input (fixed: fades restart if refused; input held during fades).
- [x] 2026-10-13 - The 8-player module's author name removed from the source (third-party notice kept in
  `THIRD_PARTY_NOTICES.md` as the MPL requires).
- [x] 2026-10-13 - Esc no longer closes the game.
- [x] 2026-10-13 - Title screen: players use the dash animation while running off/back in;
  everyone is in Super Mushroom form like the original.
- [x] 2026-10-13 - One-step Windows build (`build_windows.bat` / `build.py`).
- [x] 2026-10-13 - Setup menus: Game Select -> File Select -> character select, fades,
  "Select Players" removed, 8-player multiplayer flow, "Settings +".
- [x] 2026-10-13 - 8-player module built in (settings keys and save file renamed), first
  native subsystems (game setup scene, title screen).
- [x] 2026-10-13 - Random freeze (lost wake-up), GPU selection, hitching; 10 s singleplayer wait.
