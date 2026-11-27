# NSMBW PC port - changelog / hand-off notes

Notes between the Claude instances working on this project. Newest first. Each entry says what
changed, why, how it was verified, and what is still open, so the next session can pick up
without re-deriving it.

---

## 2026-11-27 (132) - Claude: SMB3 music fixes; a dying player took items

User's bugs: the grassland (1-2) music skips; a dying NSMBW player can grab a star; the death
music plays late and gets cut off; the P-switch music doesn't play.

- **Skips**: `nes_sound_run` (`SMB3Disassembly/port/nes_cpu.c`) counted the engine's own cycles
  on top of the ones asked for - more sound made than played, the backlog dropped (1-2's song is
  the heaviest). They're part of the frame now. Checked: 1-2 headless, no samples dropped in the
  level (`[apu] dropped` with `SMB3_MUSIC_LOG=1`; before: every ~2 s).
- **Death song**: queued as the death begins (`gm_d_player_conv.c`: fn_8013D7E0
  initPlayerDownCommon → `smb3_music_player_down`, when the level is lost - +5460 as
  startMissBGM tests it), not at NSMBW's later miss music; the restart back to the map waits
  for its 192 frames (`smb3_stage_restart` / `smb3_stage_draw_any`). Checked: the song from the
  death, the restart held 82 frames, then the map.
- **P-switch**: the stage's own P-switch (PS.cnt) drives SMB3's P-Switch song with SMB3's rules
  (pressed over a star; the other's song or the level's after). Checked with a P-switch put under
  the start (`SMB3_STAGE_TEST_TILES=2,26,F2`): song A0.
- **Items**: `items_touch` skips a player in a demo (daPlBase_c::isDemo - death, pipes, goal),
  out of play or in a balloon.

---

## 2026-11-27 (131) - Claude: SMB3's music in the SMB3 stage

User (2026-11-27): "can you implement SMB3 music next". Details: `SMB3Disassembly/port/README.md`
(2026-11-27), `SMB3Disassembly/port/smb3_stage_music.inc`.

- **SMB3's own sound engine plays the levels' music**: `nes_sound_run` (`port/nes_cpu.c`) runs
  `Sound_Engine_Begin` alone while the NES game is held in its level, as its NMI would, paced by
  the sound sent to the PC (`smb3_stage_audio`, from `rt_audio.c`). `apu_flush` (`nes_apu.c`)
  drops the burst of the frames SMB3 ran to bring a level up.
- **Native state first**: the songs come from SMB3's queues, set from NSMBW's own state and
  requests - SndSceneMgr's star / P-switch flags; NSMBW's miss, game over, hurry-up, clear
  sounds translated; the goal card's songs; NSMBW's pause (dGameDisplay_c ProcMainPause,
  `gm_d_gamedisplay.c`) → Sound_QPause.
- **NSMBW's music not played in the SMB3 stage**: `smb3_music_sound` from the nw4r
  detail_StartSound / HoldSound (`rt_retro.c`) and detail_PrepareSound (`gm_nw4r_g3d.c`) hooks -
  the sounds on NSMBW's BGM players (ids from the disc's sound archive:
  `SMB3Disassembly/tools/brsar_sounds.py`). NSMBW's sound effects stay, mixed with SMB3's sound
  (also on the map now - it used to replace everything there).
- **The goal's time bonus** waits for the card song (192 / 240 frames for a triple), as
  DoTimeBonus waits for SndCur_Music1 - by length, so it stays deterministic.
- **Verified** (headless, Mario, 1-1 from the map, `SMB3_MUSIC_LOG=1`): the level's song (10),
  NSMBW's stream not started, death → 01, the card → 20 then the map, pause / resume.
- **Open**: SMB3's sound effects; bosses' songs (their objects don't queue them yet).

---

## 2026-11-26 (130) - Claude: the Frog gets its own model file (Penguin untouched); more power-up sites

- **Frog model** (`runtime/rt_charmdl.c`): Mario gets a second dPlayerMdl_c built from
  `game/mod/characters/smb3/frog_mario.brres` (made with the first, `fn_800D5580` →
  `rt_charmdl_after_create`; deleted with the manager, `rt_retro.c`). setPlayerMode(8) swaps
  dPyMdlMng_c's model to it (and back for any other value), restarting the current animation, so
  NSMBW's change animation shows old/new by turns as usual. The Penguin is the real Penguin again.
  `smb3/mario.brres` is now the Raccoon parts only (`models/tools/build_smb3_brres.py`: `--frog`
  only for frog_mario.brres). Other characters: Super's model until their Frog file exists.
- **Power-up sites** (POWERUPS.md "Read so far"): setCcData and the fukidashi offset read their
  tables with `pu_tab`; hle for daEnItem_c::GetWhetherPlayerCanGetPowerupOrNot (a block gives a
  Raccoon/Frog player a flower, not a mushroom), fn_80022180 and fn_80036AB0 (a Raccoon/Frog
  player breaks bricks like any big player). `runtime/hle_funcs.txt` lists the three.
- **Verified** (headless, Mario, SMB3 1-1): Frog shows the Frog model, Penguin the Penguin,
  Raccoon the tail and ears; Raccoon and Frog persist through a pipe; small → Frog no crash.
  The brick/item hle are for the NSMBW mode's blocks: built, not yet tested in an NSMBW level.
- **Open**: the rest of the catalog; Tanooki/P-Wing; Frog moves; Frog files for the others;
  carrying-player block hits; NSMB2 leaf (needs code.bin).

---

## 2026-11-26 (129) - Claude: the new power-ups become NSMBW power-up states (Raccoon 7, Frog 8); a crash; faster tests

User (2026-11-26): the suits must be real NSMBW power-up states, not flags stacked on Super; the
new power-ups exist in every game mode; nothing substituted between games. Plan and catalog:
`SMB3Disassembly/port/POWERUPS.md` (sites: `powerup_sites.txt`, `tools/powerup_scan.py`).

- **`runtime/rt_powerup.h`** (new): `PLAYER_MODE_e` extended - 7 `PU_RACCOON` (variants Tanooki,
  P-Wing to come), 8 `PU_FROG`; `pu_base` (the power-up a new one is built on: Super) and
  `pu_tab` (the index for one of the game's 7-entry tables - never a read past the end).
- **The game's tables** read with `pu_tab`: setCcDataDirect (l_mode_cc_size_data),
  getBgPointData (the collision points), getTallType, setSpeedData (scSpeedHioData), the
  balloon offset (`gm_d_player.c`); setSoundPlyMode (`gm_d_player_base.c`); getHangBcOffsetY,
  setCenterOffset (`gm_d_player_conv.c`); fn_80133CB0 (recompiled only: `runtime/rt_powerup.c`,
  hooked for its indirect callers with the new `rt_override_func`, `rt_core.c`).
- **The model** (`gm_pf_family.c`, dPlayerMdl_c::setPlayerMode): a new power-up shows its base's
  model and the model keeps the base value in its mPlayerMode (the game's model code indexes
  tables with it - dPyMdlMng_c::calc's scale read past the end made a Raccoon invisible); the
  real value per model in `rt_pu_mdl_set/get` (NSMBW's change shows old and new by turns).
- **Kept**: daPyMng_c::checkCorrectCreateInfo clamps 0-8 now (was 0-6: back to small); a pipe /
  door junction keeps everyone's power-up (`keep_modes`, the stage restart made them small).
- **The SMB3 suits** (`smb3_stage.c`, `smb3_stage_frog.inc`): the leaf is
  ChangePowerupWithAnimation(PU_RACCOON) - NSMBW's own change; the Frog suit PU_FROG; the
  Raccoon's parts, P-meter and flight follow the player's value (rc[].on is set from it each
  frame, no longer a flag of its own); a hit: NSMBW's own rule already gives Super for a suit;
  the SMB3-mode hook only turns small into Super for one. NES characters: the value set at once
  with SMB3's poof. The Frog's Penguin-slot model switch is gone (no substitution): the Frog
  shows Super's model until it has a model of its own (next: a 5th model in dPlayerMdl_c).
- **Crash** (taking the Frog suit small, or the leaf as Fire): `A_SET_POWERUP_NOW` 0x801416C0
  isn't a function start in the recompiled game - `set_powerup_now` does it (mNextMode, then
  setPowerup through the vtable).
- **The Raccoon's animation merge** was refused - and tried again every frame - when the archive
  had no F_wait (a build without the Frog's pose): F_wait is optional now.
- **Tests**: frames are dumped only for a shot (`RT_DUMP_REQ`, drive2.py), written a row at a
  time - a test is about 2 minutes instead of 10; `scen.py OUT MAPY MAPX [ENV=..] -- STEPS`
  (the save's map position, the level, the steps, a contact sheet). Test env: SMB3_TEST_GIVE=v[,f]
  (NSMBW's change to power-up v), SMB3_MDL_LOG.

Checked: Raccoon given to small Luigi (NSMBW's change, Raccoon's tail and ears, walking,
jumping), hit by a Goomba -> Super, Raccoon through a pipe kept; the Frog suit taken small (no
crash).

Next: the Frog's own model (a 5th dPlayerMdl_c model; `models/tools/build_smb3_brres.py` must
stop putting it in the Penguin's place), the rest of the catalog (getters' callers, callees given
the value), the items in the NSMBW mode, block hits while carrying a player, INTERACTIONS.md.

---

## 2026-11-26 (128) - Claude: SMB3 - the user's bug list, the map's pause menu, Boomerang Bros, note blocks, the P-Switch, Micro-Goombas, white blocks, pipes and doors

User's list (2026-11-25): roulette glitchy, portrait ignores the fade, SMB1 Mario falls off the
map, file select cards unstable, a death after the goal, shells don't break bricks, 1-6 platforms
jitter, Toad House camera / tiles / early movement / item into the bar; new: Boomerang Bro, note
block, P-Switch, Para-Goomba dropper, white blocks, pipes, doors, slopes, VFX, music; and the map's
pause menu (NSMBW's own) is back. All checked headless (drive2.py) on 1-1 / 1-2 / 1-3 / the user's
saves.

- **Roulette**: the IRQ came late in long straight-line code (the music engine), so on alternate
  frames the reload used the old latch. `tools/recomp6502.py` now emits `CHECK(pc)` before every
  instruction (interrupts are taken only at CHECKs) - the split is steady.
- **Portrait** (`smb3_map.inc`): `portrait_fade()` compares Pal_Data with the PPU palette (steps
  0-4) and darkens the picture with it; hidden while the BG is off.
- **Map pause menu** (`smb3_map.inc` pm_frame): NSMBW's COURSE_SELECT_MENU (profile 693) made with
  createBase, opened with + when Map_Operation is $0D; SMB3 waits while it's open; Save writes the
  SMB3 file, Title stops the session and goes to the title. (Star Coins / Add-Drop do nothing.)
- **SMB1 / retro characters on the map** (`rt_retro.c`): they also go through
  `smb3_map_player_exec` - no more falling off it.
- **File select** (`rt_gamesetup.c`): the SMB3 cards read the file through `smb3_file_info`
  directly (cached 15 frames) - no extra 0, no "new!".
- **Goal**: NSMBW's timer held at 999 after the card (goal.hold) - it ran out after the time bonus.
- **Shells bust bricks** (hit_block: `big || bump_self >= 0`).
- **Platforms** (`smb3_stage_platforms.inc`): positions with their sub-pixel fractions - no jitter.
- **Toad House**: zoom locked (bp +0x40/+0x44 = +0x70/+0x74, the bg's zoom targets), centred
  (L.lx + 128 - w/2); its own BG bank (no PT2_Anim); players held until Toad's message is done
  (th_halted); the item flies into the open inventory (ToadHouse_GiveItem: Inventory_DestX, yvel
  -$30, gravity 2), the bar shows the inventory rows meanwhile.
- **Boomerang Bro** (`smb3_stage_battle.inc` norm_boomerangbro): Var5 & 3 states, throws at
  (Var7 & $BF) == $1F; SObj_Boomerang (+-$20 / -$16, timer $40, back and caught); pictures OA1_PAL2.
  Fire / Heavy Bros still fight as Hammer Bros.
- **Note blocks** ($2E-$31, $71, $BC): landing bumps it down, then a launch of 3.5 or 7.0 (jump held
  / pressed: the high one) through dAcPy's jump (vtable +0x3FC); hit from below: its item.
- **P-Switch** ($F2; pressed $D7): coins <-> bricks swapped for its time (decremented every 4
  frames), each change recorded and put back.
- **Para-Goomba dropper** (`port/smb3_stage_micro.inc`, new: ObjNorm_ParaGoombaBomber,
  OBJ_PARAGOOMBAWITHMICROS $74): flutters down / flies $38 above the player / drops a
  Micro-Goomba every 32 ticks; stomped -> Goomba. SObj_Microgoomba: falls swaying, sticks to a
  player (Data 5), bobs on it, holds it to a walk (Player_UphillSpeedVals $16 = 1.375); new
  presses shake it (-1), every 16 ticks it holds on (+1); off: flops away. Its picture ($FF, bank
  $4F, PAL3) is slot 12 of the brothers' 16-slot block (no extra atlas room).
- **White blocks** (`smb3_stage.c` white_blocks, prg008 PRG008_BE31 / A766): plains only; on a big
  white block's top ($25-$27) holding down for $F0 frames the player drops 6 through it and is
  behind the scenes (Player_Behind $F0, every other tick -1, kept while the head tile isn't $41 /
  sky); objects and Micro-Goombas don't touch it (Player_Behind_En). Drawn behind: NSMBW resets
  the player's z every frame, so the tiles around it (5 x 5) are drawn again in front of it with
  their backdrop pixels dropped - the atlas marks a tile's colour-0 pixels (alpha $FE -> RGB5A3
  alpha 6), drawn as before, but the second pass's alpha compare (> 230) drops them.
  GXSetZCompLoc is now 0 (after texturing).
- **Pipes and doors** (`port/smb3_stage_pipes.inc`, new; prg008 Player_DoSpecialTiles /
  PipeEntryPrepare / PRG008_A827): a player on a pipe's top ($AD-$B0, $B3/$B4) holding down within 8
  of its middle, jumping into its bottom holding up, walking into a sideways mouth ($B5), or pressing
  up at a door ($43; $42 in fortresses). SMB3 - unseen - gets its Mario put at that pipe / door
  with the same button: it decides (Level_PipeMove / Level_JctCtl set, or not). Up / down: NSMBW's
  own pipe entry - daPlBase_c::changeDemoState(StateID_DemoOutDokanD / U from setDemoOutDokanAction's
  table 0x80308450), mWarpPos at the pipe's mouth, its sound - its slide's length (+1060) pushed out
  of reach so its own scene change never comes, its depth kept at the stage's (NSMBW's -1800 would
  be behind this level's sky); the tiles about it drawn again in front (as the white blocks). Once
  32 in, SMB3 runs the junction (Level_JctCtl: Level_AltLayout / the table by Player_XHi) until the
  other area is up, its Mario out of the exit pipe and its fade-in done; the stage starts again on
  it (clock, counters, lives kept: `jct_restart`), the players at SMB3's Mario. Sideways pipes: a slide
  of our own (untested - none in World 1). A pipe / door that leaves the level: the map, cleared.
  Checked: 1-1's coin room (down and up, test pipes at screen 8 - 1-1's real one is on top of the
  tall pipe at 141,7, reached flying), 1-Fortress's door (109,23) into its spike room.
- Test env (all optional): SMB3_PIPE_LOG, SMB3_STAGE_TEST_XOFF, SMB3_STAGE_TEST_ONLY=hex (that enemy id only), SMB3_STAGE_TEST_ROW
  (with _X: stand on that row), SMB3_FIND_TILE=hex,hex.. (log where those tiles are; SMB3_STAGE_TEST_TILES also writes SMB3's Tile_Mem), SMB3_SLOTLOG,
  SMB3_BATTLE_TEST_WIN, SMB3_TH_LOG, NES_IRQLOG, SMB3_MAP_TILT, SMB3_MAP_TH_NES.

Open: wall-slide gap on the right of a block (asked the user for a repro), the NSMBW map Mario
(tilt -0x1400 applied; asked the user what's missing), coming out of the exit pipe (players appear
on it), slopes, VFX,
music / SFX, Fire / Heavy Bros.

---

## 2026-11-25 (127) - Claude: SMB3 - Toad Houses as stages, the bonus rooms' Mario portrait, the Hammer Bro battle

User: the Toad House with the NSMBW players; their picture (`ui/graphics/smb3/marioportrait.png`)
in place of SMB3's big Mario in the Spade / N-Spade rooms; Hammer Bros: no battle when Mario
stops on their square, and a black screen (softlock) when one is touched. Checked headless on the
user's saves (file 1: the user's World 1 with a Hammer Bro; file 2: on the Toad House; file 3: on
the Spade panel).

- **Toad House** (`port/smb3_stage_toadhouse.inc`, new): tileset 7 is a stage now (only 15 / 16 /
  17 - spade, N-spade, 2P battle - are still played by SMB3 on the map plane). Toad ($34, ObjP34,
  sprite bank $05), his box and message drawn from the level's BG letters (prg002 ToadMsg_*:
  whistle / standard / anchor-P-Wing by YHi and Map_EnterViaID), one box row a frame then one
  letter per 4 frames; chests ($81-$84) opened with B / run; the item (THouse_Treasure ->
  ToadItem tables) rises, lands, goes into Inventory_Items' first empty slot, then
  `map_level_end(.., 0)` after $FF frames. Atlas: 48 more slots kept for tileset 7.
- **Bonus rooms' Mario** (`smb3_map.inc` portrait_*): SMB3's Mario there is a 3x4 block of BG
  tiles (prg022 LoadLevel_BonusPlayer: Player_BonusTiles_Big / Raccoon / Small, its top-left
  always TILE15_BRICKBG). Found by his head ($43 $44 $45, or small $4A over $86) in Tile_Mem,
  on screen at col*16 - Horz_Scroll, row*16 - (Vert_Scroll + 1) (16, 80 in the Typical layout);
  painted over in the map picture with his top-left brick tile, the user's PNG (resampled to
  64 x 96 RGB5A3 at `SM_MEM+0x1F000`, texobj `+0x3FE00`) drawn there, 64 high, feet on the floor.
  (A first try took the OAM at Player_SprOff: that was Toad's body.) Not during the roulette.
- **Hammer Bro battle** (`port/smb3_stage_battle.inc`, new): ObjNorm_HammerBro (walk +-6 by
  Var5 & $40, jumps -$30 / -$60 with Timer2 $28 / $20 not landing - through the floors -, hammers
  when Var6's low bits reach $1F), TDO group 2, bound box 2, drawn 16x32 8 below Y from ObjP81
  (bank $4E, palette 3); stomped: killed, 1000. SObj_Hammer (15 frames in the hand, then +-$12 /
  -$30 with gravity 2 to $6E, Hammer_Draw's 8 frames, SObj_PlayerCollide). LevelEvent_TreasureBox:
  with no objects and no hammers left, the box at Y $170, X $30 / $C0 into the screen away from
  the player; ObjNorm_TreasureBox: poof at $18, falls, opened on touch (clock stops), the item
  (Level_TreasureItem, palette $30 / ToadItem_PalPerItem / $0F) rises then flashes $70 frames,
  into the inventory, $60 frames, `map_level_end(.., 0)` - SMB3 takes the brother off its map.
  Boomerang / Heavy / Fire brothers (Worlds 2+) fight as Hammer Brothers for now.
- **The black screen**: the user's save had the brother at X $90 - between squares (World 1's
  starts at $A0; brothers march 2 squares over Map_March_Count's 32 frames). Saved mid-march, the
  march counter (RAM) is lost: it could never be stood on (prg011 PRG011_B6A1 wants the exact
  square), and touched there, the level lookup by map position finds no level. `smb3_game.c`
  `snap_map_objects`: marching map objects ($03-$08, $0B) down to the 32-pixel grid on save and
  on load (the user's brother is back at $80, $80).
- Testing aids: `SMB3_MAP_TRACE` (the map's operation, position, Map_EnterViaID as they change),
  `SMB3_MAP_FBDUMP_EVERY`, `SMB3_BATTLE_TEST_WIN=N` (the brothers beaten at frame N),
  `NES_IRQLOG` (nes_cpu.c: the MMC3 IRQ's line each frame - for the roulette, below).

Verified: the portrait in the Spade room (file 3); the Toad House to the inventory and back to the
map (file 2); stepping onto a brother's square starts the battle, the brother jumps and throws,
the box comes, the item goes in, SMB3's map with the brother gone (file 1, brother moved next to
Mario).

Open: the Spade roulette's glitching (alternate frames with the strip / status bar splits late:
MMC3 IRQ timing - `NES_IRQLOG` added, not yet run); the map's player as NSMBW's world-map Mario
(the SMB3 map itself stays flat); the other brothers' own behaviour.

---

## 2026-11-25 (126) - Claude: SMB3 - the log platforms (World 1), ridden through NSMBW's own colliders

User: port SMB3's moving platforms as objects (SMB3 sprites, behaviour from the disassembly).
Checked headless (Linux, GL) on 1-4 and 1-6 from the user's save (file 3: the save with the map
position set on 1-6's panel).

- **`port/smb3_stage_platforms.inc`** (new, included by `smb3_stage_enemies.inc`): prg002's
  ObjInit / ObjNorm for $26 (rider), $27 / $37 (horizontal oscillating, Platform_Oscillate),
  $28 / $38 (vertical), $36 (1-4: drifts left at -8, stops and drops faster and faster once stood
  on), $3C / $44 (1-6: ObjNorm_PathFollowPlat - the four tiles about its middle at TDO group 9,
  WoodenPlat_ScanIndices / _NextTileIdx / _PathTiles(Alt) / _XVel / _YVel, the platform puller
  $D0 reversing it, falling where the path ends; $44 waits to be stood on). Drawn as LogPlat_Draw
  ($8F $9D $9D $9D $9D $9F, palette 3) from sprite bank $0E (OPTS_SETPT5 | $0E: SMB3 sets that
  bank for them as they run - the level's own bank drew other graphics). In the object slots with
  the enemies; spawned / deleted 48 wide; no harm to players, not hit by shells, tails or bumps.
- **Standing on them**: NSMBW's `RideableActorCollider` (ctor 800DB450, init 800DB530,
  setPosition 800DB5F0, update = vtable +12, BasicCollider::addToList 800DAE80 /
  removeFromList 800DAED0) - a line along the platform's top, moved each frame with it; the
  update carries its riders by the move. `dRc_c::check` (800D9940 -> 800D9B80 -> 800D9D70) wants
  the line's kinds (+69) to share a bit with the rider's (+46: 3 for the players) and its layer
  (+74) equal to the rider's (+50); +60 flags 0. The line needs an owner actor: one DUMMY_ACTOR
  (profile 0x2EB, a dStageActor_c that does nothing), checked by `fBase_c::search(id)`. Its
  riders (+16, kept until its next update) are SMB3's "stood on". NSMBW never clears the
  collider list, so the lines are taken out when the stage scene goes (`smb3_stage_on`) and when
  the level starts again. Verified on 1-4: a jump onto the first platform, it stops and drops
  with the player on it (`platform 0 (36) ... stood on`), the player carried down to the ground.
  1-6: the first track platform rides its zig-zag track between the two pullers, back and forth.
- (Fixed on the way: the objects' calls into the game used `blk_ctx` before the first player had
  set it - set in `smb3_stage_player_draw` now.)
- Test switches: `SMB3_PLAT_LOG` (the platforms every 30 frames, stood on / left); `drive2.py`
  takes `GAME_WRAP` (e.g. a gdb wrapper) to get a native backtrace.

Open: SMB3's side push and head bonk on a platform (NSMBW's line is top-only), the other platform
kinds (clouds, floating, falling, invisible lift), autoscroll (1-4), the custom SMB3 map scene.

---

## 2026-11-25 (125) - Claude: SMB3 - SMB3's palette fades in place of NSMBW's course intro and wipes; bug fixes

User: a save card over the Game Select; a gap wall-sliding on the right side of a wall; a red shell
stopped and flipped by a brick; the map player jumping to the viewport's top right on entering a
level; the player spawning floating; the course intro on every return to the map; exiting a stage
sent the player to 1-1. Then: SMB3's own fade-in (the palette shift) instead of NSMBW's intro and
wipes. Checked headless (Linux, GL): the menus to SMB3's map, 1-1 entered, wall slides both
sides, a death back to the map, frames dumped.

- **SMB3's palette fade** (`runtime/rt_gxgl.inc`, `rt_gl.h`, `gm_m_fader.c`, `port/smb3_stage.c`):
  in the SMB3 stage scene `mFader_c::draw` asks `smb3_stage_fader`, which doesn't draw NSMBW's
  fader but sets `rt_nes_fade(mode, step, palette)`; at the display copy (`gl_present` /
  `gl_overlay_efb`, before the menus) a full-screen pass takes every pixel to its nearest NES
  colour and steps it as PRG026 does: fade-out takes $10 off a step (below $00: $0F); fade-in
  starts at colour-$30 (black if below $00), a black comes back as its row-0 shade, then +$10 a
  step. A step every 4 frames (Fade_Tick), 4 steps; NSMBW's frame-counting fader is made 16
  frames long; opaque = black. Verified: the map's fade-in, 1-1's fade-in, a death's fade-out
  and the map after it (dumped frames show SMB3's darker-row colours).
- **No course intro** (`port/smb3_stage.c`, `stage_start_game`): `dScCrsin_c::m_isDispOff`
  (0x8042A1B0, as the title's restart and fn_800BB880 set it) before `dInfo_c::startGame` - the
  course intro waits 1 frame instead of 120 and shows nothing - and `dFader_c::setFader(0)`; the
  intro scene's colour fader cut to 2 frames. Because the intro is now a few frames, the next
  level was never loaded (it waited for a 30-frame gap without players): `smb3_stage_on` and
  the fader hook now load it as soon as a scene other than the stage is seen.
- **Wall-slide gap**: the 80% wall sensor (6.4 units) left a player 7.0 from a wall on its left,
  6.1 from one on its right, creeping and snapping back; the wall sensor offsets are now whole
  units (6). Verified: 6.0 from the wall, steady.
- **Exit to 1-1** (`port/smb3_map.inc`): from the user's log - toad houses (tileset 7) and the
  spade / card games (15, 16) were entered as stages; the spade game's picture overflowed the
  tile texture, SMB3 never got back to its map and the session stopped, so every later end fell
  back to 1-1. Those panels (and 2P battle, 17) now play inside SMB3 on its map (the player's
  model hidden meanwhile); if SMB3 can't get back to its map the session reloads from the save
  file instead of stopping; tile texture writes guarded. Not yet reached in a test run.
- **Map player on entering a level** (`port/smb3_map.inc`): kept where it was while SMB3 leaves
  its map, not moved to the marker's new place. Verified (the enter-level box closing on it).
- **Floating spawn** (`port/smb3_stage.c`): the start lift now takes off the grid alignment's
  drop (`L.dy`).
- **Red shell vs brick** (`port/smb3_stage_enemies.inc`): the shell's own wall hit bumped the
  brick, and the bump turned over every object touching it - the shell too. The bumping shell
  is skipped, and only objects standing on the block's top are bumped. Not reproduced headless.
- **Game Select** (`runtime/rt_gamesetup.c`): the File Select's save card (`N_dateFile_01`,
  `N_save`, `N_starIcon_00`) hidden there. Verified.

Open: the custom SMB3 map scene with NSMBW's world-map actors, SMB3's moving platforms (notes in
`SMB3Disassembly/port/ROADMAP.md`), slopes, autoscroll, pipes / doors, water, vertical levels.

---

## 2026-11-25 (124) - Claude: SMB3 - the course clear loop, the floor jitter, levels' start, the File Select as NSMBW's; JPG portraits

User: finishing a stage killed Mario and sent him back into 1-1; in every stage but 1-1 he jittered on
the floor; the SMB3 File Select should be identical to NSMBW's. Reproduced headless (Linux, GL) with
the user's SMB3 save, and from their nsmbw_log.txt.

- **Course clear loop** (`port/smb3_stage_enemies.inc`, `port/smb3_map.inc`): the goal card's exit
  ran again every frame while NSMBW's wipe still showed the old stage (33 times in the user's log),
  each time telling SMB3 "level done, back to the map" and starting the stage again. SMB3 then went
  into a level of its own (tileset 4) that never came up, the map session stopped, and with no map
  the player died and the old fallback restarted 1-1. Now the card exits once (`var4 = 8`) and
  `map_level_end` takes one end per stage scene (`MP.ending`, cleared by `map_apply_next`).
  Verified: 1-1's card -> one "level cleared" -> SMB3's map, file saved -> 1-2 entered.
- **Floor jitter** (`port/smb3_stage.c`, placement): the level was placed so that SMB3's start sat
  where the course puts player 1 - off NSMBW's 16-unit grid (floor tops at world y 454). NSMBW
  takes a solid unit's top from its own cells, so the players were pushed up out of the floor and
  fell back onto it every few frames: on every level (~2.5 units on 1-1's solid ground), worst on
  the one-way floors of the hills tileset (1-2: `$9A`) and 1-4's ledges. `L.lx` / `L.ly` are now
  on the grid (the level up to 15 units lower: the players start above their ground). Verified:
  1-4 and 1-1 stand at exactly the floor's top, walk, jump, land.
  (Found on the way: NSMBW's one-way top is `0x20` with shape `0x0A` - shapes 0-5 / 0x0B-0x12 are
  its slopes, shape 0 has no top: `SMB3_STAGE_PROBE` on 1-1. UNIT_TOP is unchanged.)
- **The level's start** (`port/smb3_stage.c`): from SMB3's own Player_X / Player_Y once the level
  is up (`L.sx`, `L.sy`) and the first floor below it - not column 2's ground from the bottom,
  which dropped 1-4's player into the sky (it starts on a ledge at row 22).
- **SMB3's File Select = NSMBW's** (`runtime/rt_gamesetup.c`, `gm_save_mng.c`, `gm_mj2d_game.c`,
  `port/smb3_main.c`): while it shows SMB3's files the save manager's slots (and quick saves) hold
  stand-ins made from them (world, lives; no file = empty), so NSMBW's own cards, Copy and Erase
  show and work on them. NSMBW's real slots are kept and put back around every NAND save (the NAND
  command copies the data at once: `nand_cmdSave`), before a file is loaded and on leaving.
  Copy / Erase also copy / delete SMB3's file (`smb3_file_copy`, `smb3_file_delete`). The cards
  were built at Game Select with NSMBW's slots and keep that look, so the card's contents (world /
  lives or NEW!!, no stars, no quick save) are set from its stand-in each frame.
  Verified: file 2 (the user's) "World 1 x46"; Copy 2 -> 3 and Erase 3 done on SMB3's files;
  nsmbw-save.json byte-identical before and after.
- **JPG portraits** (`runtime/rt_hdtex.c`): stb_image was PNG-only (`STBI_ONLY_PNG`), so the Game
  Select's SMB1.jpg / SMW.jpg (122) couldn't load; `STBI_ONLY_JPEG` too.
- Testing switches: `SMB3_STAGE_TEST_X_ONCE=1` (TEST_X for the first level only),
  `SMB3_STAGE_SENSORS=1` (the players' sensors before scaling: head 0,16 | foot -5..4,0 | wall 4..11,8).
- Open (step 2 of port/ROADMAP.md, still to do for "every level"): SMB3's slopes collide as flat
  one-way steps; no autoscroll (1-4 lets the player go at their own pace); pipes / doors to other
  areas, water and vertical levels not done; the first ~2.5 columns of a level sit behind the shell
  course's left scroll limit (the player is pushed right at the start). Windows build: not
  compiled here.

## 2026-11-24 (123) - Claude: singleplayer character select is a grid

User: the roster is big and growing, and NSMBW's card select (left/right through everyone) is slow,
especially in singleplayer. Picked: a grid with a preview, families with variants, a Recent row.
Details: docs/CHARACTERS.md "Singleplayer: the character grid".

- **New `runtime/rt_charsel.c`** (in build.py RUNTIME and build_linux_clang.sh): the grid's state,
  input (`charsel_input`), the card's target (`charsel_target` / `charsel_take_decide`), Recent
  (settings.ini `sp_pick_<id>`), drawing (`charsel_draw`, called from `menu_draw`).
- `rt_chars.c`: `ROSTER[]` gets `.family` / `.variant` (the retro Marios are Mario's variants);
  `chars_family`, `chars_variant`, `chars_tile_texture` (portrait.png or the card layout's picture);
  SelectWait: `grid_select` (singleplayer, setup scene) moves the card to the grid's character and
  chooses there; initDecidedCharacter notes the pick (`charsel_note_pick`).
- `rt_gamesetup.c`: `gs_sp_select_state` / `gs_sp_select_visit` / `gs_screen_alpha` (the fader) /
  `gs_sp_preview_x`; the grid's input in `gs_filter_buttons`; player 1's card layouts (`L_CARD`) and
  the 2D players' `mPos.x` (`float_shift`) move left by `SP_CARD_DX` (-170); arrows hidden; Start
  Game under the card (4:3: x 0.8, a little right); MAXSHIFT 16 -> 32.
- `rt_menu.c`: `menu_text` / `menu_text_width` (the game's font for other overlays); `menu_draw`
  draws the grid (under Controls).
- `rt_gxgl.inc`: the overlay holds 128 textures (`UI_MAXTEX`; was 8 - the font and the first 7
  tiles used them up).
- Verified (Linux, GL headless, 16:9 and 4:3; driver: `RT_AUTOPRESS_FILE`): grid up with the card
  on the left; - on Mario -> Retro Mario (SMB1) on the card; d-pad across rows, held repeats; up into
  Recent; 2 -> the figure lands on the card, Start Game under it, "2: Start Game  1: Change"; 1 takes
  it back, 1 again -> File Select, back in -> on the last pick; Start Game -> world map as Luigi.
  Windows build: not compiled here.
- Open: hidden in multiplayer and on the world map (the cards as before). The figure jumps in from
  the right, across the grid (drawn under it). No sound on moving the cursor yet.

## 2026-11-24 (122) - Claude: Game Select placeholder games (locked)

- **Games list** (`runtime/rt_gamesetup.c`, "game portraits"): `GAMES[]` is now `games[]`, made once
  from `ui/graphics/gameportrait/`: NSMBW and SMB3 first (playable; GAME_NSMBW / GAME_SMB3 unchanged),
  then every other .png / .jpg / .jpeg there (not locked.*) as a placeholder game, in name order
  (now NSMBDS, NSMBU, SMB1, SMW; label = file name). File names match in any case. The list is logged
  (`[setup] games: ...`).
- **Locked cards:** a placeholder's texture gets locked.png drawn over it when it is made (`gp_lock`):
  centred, fitted to half the picture's width and height (user's choice: "about 50% of the portrait").
- **Hover, not choose:** on Game Select, 2/A are dropped while the middle card is a locked game, and stay
  dropped until released (`confirm_held`), so turning to a playable game with 2 held doesn't choose it.
- **Memory:** the pictures still share GP_MEM..GP_MEM_END (320 KB; nothing free past MEM1 - SMB3 stage
  0x818C0000, retro 0x81900000, chars 0x81A00000, models 0x81C00000). Each picture now gets an even share
  (`gp_budget`): with 6 games about 264 x 376 for a portrait (was up to 512 tall), 287 KB in all. All
  pictures are made while Game Select opens behind black (`file_select_open`), not when a card first shows.
- `build.py`: ui/ copies .jpg / .jpeg too (SMB1.jpg, SMW.jpg).
- Verified: gcc -fsyntax-only (only rt.h's clang check); sizes and a lock preview computed with PIL using
  the same maths. Not yet built or run.
- Open: no "can't" sound when 2 is pressed on a locked game.

## 2026-11-24 (121) - Claude: Game Select's right card no longer squished

- **Cause:** `pane_narrow()` (`runtime/rt_gamesetup.c`) keeps each narrowed pane's width in
  `widths[MAXWIDTH]`, and MAXWIDTH was 12 - enough for the one card Game Select used to have. The
  carousel narrows 7 `card_panes` on each of 3 cards (21): the left card got all 7, the middle 5
  (not P_selectBase_00 / W_select_00), the right none, and the table being full was silent. The
  right card still got the portrait texture, so the tall picture (aspect ~0.71) was stretched over
  the full-width card.
- **Fix:** MAXWIDTH 32; a full table now logs `[setup] pane_narrow: table full`.
- Verified: dateFile.arc's layout has all 7 card_panes (so 21 entries are needed); not yet run.

## 2026-11-21 (120) - Claude: build_windows.bat raises the version by itself

- **`build.py --bump-version`** (build_windows.bat now passes it instead of `--ask-version`): before
  building, VERSION goes up by one in its last number (0.1.17 -> 0.1.18), with no prompt.
  `--version X` still sets it outright; `--ask-version` still exists for asking. `next_version()`
  is shared by both.
- Open: the number goes up before the compile, so a failed build also uses one up.

## 2026-11-21 (119) - Claude (instance 1): the end-to-end check on instance 1's side - fanm_c::set and setPriorityDraw register-exact, a prologue-scanner fix, five bugs in the goal / course-exit natives (HUD, stage scene); verifier options for bisecting by name

- **The bench.** Instance 2's check (115), repeated with instance 1's 15 inputs (`tools/ab_inputs/`): a
  build with no natives (every `gm_*.c` but gm_verify / gm_prologue out of the build, 208 runtime
  hooks left in hle_funcs.txt - the same 208 as instance 2's) against the current tree.
- **`gm_m3d.c` `fanm_c::set` (fn_80168F10)** - instance 2's finding in (115). The cause:
  `GM_CALLR` (`gm_gcall_ra_`) puts r0-r12, lr and ctr back after the call, and the game reads r3
  after it (the PowerPC code calls through two vtable slots and leaves r3 as the callee returned it).
  Rewritten register-exact: `GM_CALLV` for both calls, r12 / ctr set as the PowerPC code sets them,
  `NV_FL` (both paired-single halves) where the frsp path writes f31, r0 = the entry lr at the end.
  `RT_GM_VERIFY=fn_80168F10 RT_GM_VERIFY_REGS=1`: 1,638 of 1,638 calls different before, 0 of 1,630
  after. `leaf_set_priority` (fn_8016A2A0, setPriorityDraw) the same way. Five other m3d natives
  still differ in r0 only (scnLeaf ctor, setDrawMatrix, fn_8016A2F0 / 8016A3A0, fn_80168400).
- **`tools/gm_prologues.py` / `tools/gm_conv.py`:** a register written anywhere in a line (also
  inside `{ }`, as lwzu writes) now counts as written, so it is not taken for a saved one later;
  and no register is listed as saved twice. `runtime/gm_prologue.c` regenerated: exactly the tables
  of 0x80079060, 0x80079250, 0x80079380, 0x800794B0 and 0x800795E0 change (instance 2's case, from
  fn_80078EF0).
- **Five bugs in instance 2's goal-sequence natives** (please check - small fixes, each marked in
  the code). e and wm (1-1 with `RT_TEST_POS` to the goal) differed from the original from field
  4053; each culprit was found by bisection by name (below) and then read against the recompiled
  mod code:
  - `gm_d_gamedisplay.c` NormalSettle (mod_fn_80158C50, the time-bonus count) and OtasukeSettle
    (mod_fn_80158D00) called `hle_startSystemSe__11SndAudioMgrFUiUl` (0x80195380: the handle at
    +2296, PlaySoundWithFunctionB4) where the mod code calls **fn_801953A0** (the handle at +2300,
    fn_80195190): the sound heap's objects were linked in another order. Up to field 4051 the
    clocks and every thread's poll counts were the same; in 4052 the main thread took another path.
  - `gm_d_gamedisplay.c` ProcGoalSettleUp (mod_fn_80158F70): after NormalSettle the test of bit
    0x40 was inverted (the original plays sound 146 when it is clear).
  - `gm_d_sc_stage.c` exitClear (mod_fn_2_1B7A50): `dInfo_c::m_startGameInfo` is **0x80315B90**
    (0x80310000 + 23440); the file used 0x80315E90 in all four places (one of them in setNextScene,
    0x818156C0). The block after the coin loop ran when +8 was 0 instead of when it is not (beq
    skips it); the call of mod_fn_8008EDB0 was for course - 25 > 7 instead of >= 7 (bge), and the
    poll belongs on that path only; the early returns were >= 9 / >= 41 instead of > 9 / > 41 (bgt).
  - A check of every hand-written `BL(<return address>, callee)` (1,086) against the callee the
    recompiled code calls at that address (wrappers like `PL_*` / `PLAY_GOAL_OTHER` resolved by
    address): the two sound calls were the only wrong ones.
  - Why the verifier didn't see these: their `GM_HLE_VERIFIED_` ranges don't cover the sound
    system or dInfo_c, and their poll checks are off (`GMV_IGNORE_POLLS`).
- **`gm_verify.c`, testing options** (docs/DECOMP.md):
  `RT_GM_VERIFY=orig:@file` / `@file` (the list from a file, one name per line, no length limit;
  each name looked up once, cached by its pointer), `RT_GM_VERIFY_NAMES=file` (each switchable native
  the run calls, once, with the field of its first call), `RT_GM_VERIFY_FROM=<field>` (natives run
  unverified before it: verifying everything from boot stops the boot). Stats table 512 -> 16,384.
- **Results against the no-natives build** (400 s runs, ~17,000-21,500 fields each): **13 of 15
  identical on every field** (a, c, e, hm, wm, f1, p1-p5, s1, s2). Before (state 104 / this
  morning): b 4933 -> 7248, d 7661 -> 9305, e and wm 4053 -> identical, p3 2452 -> identical.
  Still open:
  - **b, field 7248:** only two words, both 0x43300000 (an int-to-float temporary) at 0x80E062F4 /
    0x80E0642C - a stack that the live hash doesn't know as one (no OSThread in the active queue
    owns it). Dead stack, the same kind as (115)'s p3 finding; not game state. Even with every
    switchable native on its PowerPC version, so a plain `GM_HLE` / non-switchable one.
  - **d, field 9305:** one word, 0x811EED58 (0x8153D7B4 in the original, 0x8153DBA0 here): a
    scratch buffer of the model-matrix code (fn_80250E70 via calcWorld, written every field;
    `RT_DET_WATCHW`), the write at field 9304 from the player's model (fn_800D3830 ->
    fn_80145520). Also with every switchable native on PowerPC. Instance 1 looks at this next.
- **Note on (115)'s "e, wm identical":** in instance 1's bench e and wm run with `RT_TEST_POS` to
  the goal, so they reach the time-bonus count; that is where they differed.
- **Checked:** the 15 inputs above; Linux (clang) and Windows builds.

---


## 2026-11-19 (118) - Claude (instance 2): the player family and the world map in the DOL - 698 functions native (`runtime/gm_pf_family.c`, `runtime/gm_wmc_worldmap.c`, new)

- **Claimed (TODO.md), by address range in E2** - the classes next to instance 2's player and
  world-map work, none on instance 1's list:
  - the player family: 0x8014A6F0-0x8015F4F0 (after dAcPy_c: daPlyIce_c, daYoshi_c and their
    parts), 0x800D1500-0x800D8400 (dPc_c, dPyEffectMng_c, dPyMdlBase_c, dPyMdlMng_c,
    dPlayerOrchestra_c, dPropelParts_c), 0x800CAA10-0x800CCA40 (dMarioMdl_c ...);
  - the world map and the scenes: 0x800F32F0-0x80106DF0 (dWmConnect_c, dWmLib, dWmViewClip_c,
    daWmMap_c, daWmPlayer_c, dCsSeqMng_c, dScStage_c, dScWMap_c, dWmBgmSync_c,
    dWmEffectManager_c, dWmSeManager_c).
- **What.** Of the functions there the 16 inputs reach (470 / 312), 430 + 268 native by
  `tools/gm_conv.py` (11 refused: mod wrappers, r1 used other than r1 + n; the rest already
  native or used by other files). Ranges in `tools/gm_prologues.py`, the files in build.py /
  build_linux_clang.sh before rt_plat_*, two `# track B` sections in hle_funcs.txt. Flags
  `-DGM_PF_COUNT` / `-DGM_PF_VERIFY`, `-DGM_WMC_COUNT` / `-DGM_WMC_VERIFY`; names `pf_m_` /
  `wm_m_<addr>` (owed). gm_py_player.c / gm_py_mng.c / gm_d_player.c / gm_d_player_base.c call 10
  of them through `hle_` now.
- **Checks:** no prologue table of these lists a register twice. Strict A/B against (117) on all
  16 inputs: 0 differ. Linux and Windows builds.

---

## 2026-11-19 (117) - Claude (instance 2): the 8-player module - 312 more functions native by the converter (`runtime/gm_mj_conv.c`, new)

- **What.** The 8-player module's (d_project, 0x81800000) functions the 16 inputs reach that no
  hand-written native covers: 361 reached, 312 native by `tools/gm_conv.py` (9 refused: tail calls
  out of a frame, r1 used other than r1 + n; the rest already native or called by symbol from
  other files). `tools/gm_prologues.py` gets the whole module's range (the single ranges of the
  hand-written natives predate it); build.py / build_linux_clang.sh list the file before
  rt_plat_*; a `# track B` section in hle_funcs.txt. Flags `-DGM_MJ_COUNT` / `-DGM_MJ_VERIFY`;
  names `mj_m_<addr>` (owed). gm_py_mng.c / gm_py_player.c / gm_py_demo.c call 6 of them through
  `hle_` now.
- **Checks:** no prologue table of these lists a register twice. Strict A/B against (116) on all
  16 inputs: 0 differ. Linux and Windows builds.

---

## 2026-11-19 (116) - Claude (instance 2): the boss module d_en_bossNP begins - 380 functions native (`runtime/gm_eb_boss.c`, new)

- **What.** `d_en_bossNP` (fn_4_*, linked at 0x80B1CA50-0x80B74000: the castle / tower / airship
  bosses and their parts, plus what every level uses from it) had no owner and nothing native.
  Claimed in TODO.md. Of the 387 functions the 16 inputs reach (every input reaches 293-387 of
  them), 380 are native by `tools/gm_conv.py` as in (112); 1 refused (a mod wrapper), the rest
  already native or used by other files. `tools/gm_prologues.py` gets the range; build.py /
  build_linux_clang.sh list the file before rt_plat_*; a `# track B` section in hle_funcs.txt.
  Build flags `-DGM_EB_COUNT` / `-DGM_EB_VERIFY`; names `eb_m_<addr>` (owed).
- **Checks:** no prologue table of these lists a register twice (the scanner case of (110)).
  Strict A/B against the build of (115) on all 16 inputs: 0 differ - so on a, c, e, hm, wm, p4,
  s1 it is also identical to the build with no natives (CHANGELOG (115)). Linux and Windows builds.

---

## 2026-11-19 (115) - Claude (instance 2): the end-to-end check - every native against a build with none; three bugs fixed in instance 2's module natives; findings for instance 1

- **The check.** A tree with every native dropped (every `hle_` name that a `gm_*.c` file defines
  taken out of hle_funcs.txt, the gm_* files out of the build but gm_verify / gm_prologue: 10,257
  of 10,465 names; the 208 left are the runtime's hooks) is the recompiled original game. Each A/B
  so far compared against the build before it; this compares all ~10,300 natives at once against
  the original, on all 16 inputs (instance 2's bench: `wt_pure`). Before: 11 of 16 inputs differed.
- **Found and fixed (instance 2's files):**
  - `gm_d_gamedisplay.c` AreaCheck (mod_fn_80158910, part 79): the player-behind-the-HUD box test
    read the right edge at +8 instead of +20, and all four comparisons were inverted (proceeded on
    a clear bit where the PowerPC code proceeds on a set one). `RT_GM_VERIFY=mod_fn_80158910`:
    480 of 3,841 calls different before, 0 after.
  - `gm_d_gamedisplay.c` AlphaEnterAndExit (mod_fn_80158A90): the "done" test was swapped
    between fading in (done at 255) and fading out (done below 71). 256 of 3,841 -> 0.
  - `gm_d_sc_wmap.c` createLayoutPhase / createActorsPhase (mod_fn_2_1B9670 / 1B9A20, part 83):
    the PowerPC code saves CR (mfcr r12, stw to its frame) and puts cr2-cr3 (cr2-cr4) back at the
    end; the natives set those fields and left them - the main thread's saved CR (0x803599B8) then
    differed for thousands of fields. Now saved, stored and restored as the original does. (A scan
    of the other hand-written natives whose originals save CR: the other six already do this.)
  - Found by `RT_GM_VERIFY=orig:<list>` bisection over the switchable natives at the first
    differing field (memory dumps, `RT_DET_DUMP_AT` / `RT_DET_DUMP_MEM`), then
    `RT_GM_VERIFY=<name>` on the culprit. After the fixes: c, p4 identical to the original; the
    built-in verification of all 447 switchable hand-written natives on f1 and r_w8-7 finds only
    fukidashi's constructor / create (allocations: a second invocation gets other addresses).
- **For instance 1** (your files - not changed):
  - `gm_m3d.c` `fanm_c::set` (fn_80168F10): switching it alone to its PowerPC version
    (`-DGM_M3D_VERIFY`, `RT_GM_VERIFY=orig:fn_80168F10`) makes f1, p1, p2, p5, s2 identical to the
    original and moves d's first difference from field 7661 to 8241 and r_w8-7's from 1256 to
    11221. At d 7661 the blend results array (0x81220B38, stride 76: ExecCallbackA's stored
    results) gets 1.0 instead of 29.0. The C reads the same as the PowerPC code to me; maybe a
    paired-single half (NV_F sets ps0 only where the frsp path sets both) or the callee's view of
    f1 - not found.
  - Still different with every switchable native on its PowerPC version (all `*_VERIFY` flags,
    `RT_GM_VERIFY=orig`): input b field 4933, word 0x81220B54 (the same results array: a pointer
    0x8043F9C0 in the original, 0 here); input p3 field 2452, stack word 0x80DFFF04 (0x43300000 -
    an int-to-float temp - in the original; fn_802DA6F0 effect_params_copy_da6f0's frame doesn't
    store it: dead stack, but hashed until 7144). So: plain `GM_HLE` natives.
- **Inputs now identical to the original build:** a, c, e, hm, wm, p4, s1 (and f1, p1, p2, p5, s2
  with fanm_c::set on its PowerPC version).

---

## 2026-11-19 (114) - Claude (instance 2): the first recorded play (the user's 8-7, `r_w8-7`) as A/B input; 160 more converted functions on

- **The recording** (`tools/record_play.bat`, part 113): the user's 8-7 - a death, the level
  again, the clear, the world map; 11,580 fields. Replayed on Linux it plays the same scenes in the
  same order. Its `check.hash` does not match a Linux replay from field 60 on (a Windows build and
  game folder against a Linux one: something outside the game's state that the live hash still
  takes in - to be found; the A/B compares two Linux builds on the same replay, which doesn't need
  it). Kept in instance 2's bench (`recs/w8-7`: input.rec + start/), run for 360 s.
- **What it reaches** that the 15 inputs don't: 269 functions, among them 41 converted player
  functions (109) and 119 more convertible ones of d_basesNP. All on now (`gm_d_player_conv.c` +41,
  `gm_bs_bases.c` +119; a new `# track B` section in hle_funcs.txt; gm_d_player.c's call of
  fn_8013C520 through `hle_`).
- **Checks:** strict A/B against the base of (108) on the 15 inputs: 0 differ; on r_w8-7 against
  the build of (113) (the base predates `RT_REPLAY`): 0 differ.
- **Next:** an A/B against a build with nothing native at all (every gm_* native dropped from
  hle_funcs.txt, the files out of the build): the end-to-end check that the natives as a whole
  match the recompiled original on every input.

---

## 2026-11-19 (113) - Claude (instance 2): recorded play as A/B input - `RT_REC` / `RT_REPLAY` (rt_det.c), `tools/record_play.bat`

- **Why.** Almost everything the 15 inputs reach is native; what's left needs play the scripted
  inputs can't do (Yoshi, water, vines, bosses, airships). The user offered to play it.
- **What.** In deterministic mode the game sees the keyboard only as latched per video field
  (det_field), so recording those words is enough to replay a game exactly. `RT_REC=file` writes
  "field mask" lines (hex) where they change; `RT_REPLAY=file` ORs them into the latched keyboard
  instead. `tools/record_play.bat NAME` saves the starting state (nand, settings.ini,
  wiimotes.ini, profiles.json) to `game\recordings\NAME\start\`, sets `RT_DETERMINISTIC=1
  RT_UPDATE=0`, the recording, and a memory hash every 60 fields (`check.hash`) to check the replay
  against. Keyboard only (a real remote's reports aren't latched per field), no save states, not
  online, not our Options / Controls menus. Documented in `tools/ab_inputs/README.md`.
- **Checked:** a recording made from input f1's scripted presses replayed with `RT_REPLAY`: the same
  hash on all 9,469 fields. Inert without the variables.

---

## 2026-11-19 (112) - Claude (instance 2): the stage-objects module d_basesNP begins - 2,327 functions native (`runtime/gm_bs_bases.c`, new)

- **What.** `d_basesNP` (fn_2_*, linked at 0x8076D8C0-0x80933800: course objects, items,
  platforms, the scenes' actors) had no owner and nothing native but the menus and world-map
  classes of parts 82-96 and the state-ID templates. Claimed in TODO.md (instance 1: tell me in
  CHANGELOG if you need one of its functions). Of the 2,504 functions the 15 A/B inputs reach
  (coverage build, part 111), 2,327 are native, by `tools/gm_conv.py` as in (109) / (110).
- **Left out:** 28 refused by the converter (21 mod wrappers, 7 using r1 other than r1 + n);
  31 that other runtime files call by symbol (`gm_d_sc_wmap.c`, `gm_d_wm_*.c`, `gm_d_stock_item.c`,
  `gm_d_course_manager.c`, `gm_d_sc_stage.c` - left to those files); 4 whose recompiled name the
  DOL has too (a REL's own copy of `dEn_c::calcBoyonScale` / `isQuakeDamage`, `m3d::banm_c::play`,
  `anmChrBlend_c::getType` - the hle list is by name, so listing one makes two `orig_` symbols);
  the rest already native or hle. A check of `gm_prologue.c` for the scanner case of (110): no
  table of these lists a register twice.
- **`runtime/gm_bs_bases.c`** (141k lines), build flags `-DGM_BS_COUNT` / `-DGM_BS_VERIFY` as the
  others; names `bs_m_<addr>` - naming owed. `tools/gm_prologues.py` gets the module's range;
  build.py / build_linux_clang.sh list the file before rt_plat_*.
- **Checks:** strict A/B against the base of (108) on all 15 inputs (`tools/ab_inputs/`): 0 fields
  differ. Linux and Windows builds.

---

## 2026-11-19 (111) - Claude (instance 2): eight more A/B inputs chosen by coverage (`tools/ab_inputs/`, +1,390 functions reached); 87 more converted player / camera functions on

- **Why.** The seven inputs reach 7,345 recompiled functions, and a converted function goes on
  only when an input reaches it - 511 of the converted player functions (109) and 41 camera
  ones (110) were waiting for input. They were the ceiling, for instance 1's work too.
- **How they were picked.** A coverage build (`PPC_ENTER` counting each recompiled function's
  entries, dumped at exit; bench only, not in the tree) ran input a's pattern on all 74 regular /
  ghost house / tower / castle / airship stages (`RT_WARP`), then a new mixed pattern on all of
  them, then one level entrance of each entrance type (from the stages' course files; `RT_WARP`'s
  area / entrance numbers start the level there, so pipe / door / vine / water exits play), and a
  power-up run (the copied `nsmbw-save.json`'s `powerup` edited). A greedy pick over those runs;
  the eight that add the most:
  f1 6-6 with fire, p1-p5 five entrances (1-5, 1-22, 1-20, 2-22's boss room, a 1-2 pipe), s1 7-2,
  s2 3-3 - all with the new `x_mixed.txt` (right held, running in segments, jumps of varied length,
  ground pounds, shakes, up presses). Rows, settings and the save edit in
  `tools/ab_inputs/README.md` (a new section after instance 1's table). 240 s each.
- **Checks.** Each new input run twice with the same build: 0 fields differ (deterministic). The
  PC build of (110) against the base of (108) on them: 0 differ. Together the eight reach 1,393
  functions the seven don't (8,738 in all, +19%).
- **Switched on:** the 74 converted player functions and 13 camera functions the new inputs reach
  and the old don't (`gm_d_player_conv.c`, `gm_bg_scroll.c`, a new `# track B` section in
  hle_funcs.txt; fn_80078EF0 of the prologue-scan case in (110) stays off). gm_py_demo.c's calls of
  three of them go through `hle_`. A/B against the base on all 15 inputs: 0 differ.
- **Open:** 437 converted player functions and 28 camera ones still unreached (demos, swimming,
  vines, poles, Yoshi ... need inputs that do those); the 155 camera functions' names
  (`bg_m_<addr>`); the coverage data is in instance 2's bench (ask for a list of what the 15
  inputs reach - useful for picking what to convert next).

---

## 2026-11-18 (110) - Claude (instance 2): camera / scroll begins - 157 dBg_c / dBg_ctr_c / dBgParameter_c functions native (`runtime/gm_bg_scroll.c`, new); the 243 player natives of (109) named and described

- **Camera / scroll (track B item 3 of instance 2's list).** The background manager `dBg_c` (scroll
  position and limits, loop / auto scroll, water and wave levels, the coin bitfield), its
  collision objects `dBg_ctr_c` and `dBgParameter_c` (the screen / zoom parameters), E2
  0x80076800-0x80084000 (after dBc_c's checks). Claimed in TODO.md. Same method as (109):
  `tools/gm_conv.py` over the range - 204 converted (2 refused: mod wrappers; functions another
  runtime file defines or calls by symbol left to their owners - gm_bg.c's tile lookups), a COUNT
  probe build, the 163 the seven inputs reach, strict A/B.
- **A prologue-scan case for instance 1** (`tools/gm_prologues.py` / gm_conv.py): fn_80078EF0
  saves r21-r31 through `_savegpr_21`, then loads a table into r21-r31 and stores those words to
  its own frame (`stw r21, 40(r1)` ...) as a local array. The scan takes that later `stw r21,40(r1)`
  for a second save of r21 (the table gets `40, 0x115` besides `100, 0x115`), so the generated
  prologue stores the *incoming* r21 there and gm_conv.py drops the real store - the probe differed
  from field 674 on (found by bisecting with `RT_GM_VERIFY=orig:`). Five more functions of the range
  have a register twice in their table (0x80079060, 0x80079250, 0x80079380, 0x800794B0,
  0x800795E0) - all six are left out (157 on). A check over the whole `gm_prologue.c`: no other
  table has a register twice. Suggested fix: a store of a register the scan already took as saved
  (or that was written in between) is not a save.
- **`runtime/gm_bg_scroll.c`**: the 157, with build flags `-DGM_BG_COUNT` / `-DGM_BG_VERIFY` as
  gm_d_player_conv.c; names are the ported symbols where they exist (getLeftLimit, setWaterInWave,
  dBg_ctr_c::calc / set / setOfs / addDokanMoveDiff, getLoopScrollDispPosX ...), else `bg_m_<addr>` -
  naming owed, as for (109). `tools/gm_prologues.py` has the range. `gm_py_player.c`: one call
  site renamed to `hle_placeTile__8BgGmBaseFUsUsii`.
- **The (109) player natives named.** All 243 in `gm_d_player_conv.c` now carry the decomp's name
  and a one-line description (202 confirmed from the state objects / source order, 41
  identified: the constructor / destructor, pre / post execute, the background-check chain, the
  two `__sinit`s ...). Names and comments only: the object's .text compared identical before and
  after. Notes from that pass: dAcPy_c's E2 vtable is 0x80325420 (not 0x80326794 as (103) said);
  the hand files' `setFlag` / `clearFlag` / `testFlag` are the decomp's onStatus / offStatus /
  isStatus.
- **Verified.** Strict A/B of the final build (player names + 157 bg natives) against the (108)
  reference, 300 s per input: a 12,405 / b 15,378 / c 10,320 / d 12,147 / e 12,390 / hm 14,866 /
  wm 13,830 fields, **0 differ**; no "no prologue", no fatal. Windows build links.
- Open: names for the 157; the six left out (after the scan fix); the 41 converted-but-unreached
  of the range; the camera's other half (the per-scene camera / zoom objects outside this range).

---

## 2026-11-18 (109) - Claude (instance 2): the player classes by the converter - 243 more daPlBase_c / dAcPy_c functions native (`runtime/gm_d_player_conv.c`, new)

- **Method change.** Waves 1-2 ((103), (104)) were written by hand: 357 functions.
  The rest now goes through instance 1's `tools/gm_conv.py`, as instance 1 does for the library
  and the enemies ((105), (108)). Every function of the game's daPlBase_c (E2 0x800460D0-0x8005B3A0)
  and dAcPy_c (E2 0x80126510-0x8014A6F0) that is not native yet, not listed in hle_funcs.txt and
  not replaced by the 8-player module: 758; the converter takes 755 (3 refused: module
  wrappers), 1 is left out because a file of another author calls its recompiled symbol
  (`setAnimePlayStandardType__10daPlBase_cFi`, 0x80052290, from `gm_d_staff_credit.c` - it can go
  in once that call names `hle_`).
- **Probe.** A build with all 754 on, `GM_PL_COUNT` (first-call log): **identical on every field
  of all seven `tools/ab_inputs/`** against the (108) reference, and the seven inputs reach
  **243** of them (daPlBase_c 89, dAcPy_c 154).
- **The file.** `runtime/gm_d_player_conv.c` (in both builds' lists, after gm_en_enemies): the 243,
  each with its recompiled name and size in a comment; build flags `-DGM_PL_COUNT` (first-call
  log) and `-DGM_PL_VERIFY` (switchable through `RT_GM_VERIFY=orig:<names>`), the same scheme as
  gm_en_enemies.c. **Not yet named or described** (`pb_m_<addr>` / `py_m_<addr>`, or the ported
  symbol where one exists): that is owed, as (105) did for the library - from the StateID objects,
  the vtables and NSMBW-Decomp's source order, as in (103).
- **Call sites renamed** to the `hle_` entries in instance 2's own files (a function in
  hle_funcs.txt loses its recompiled symbol): gm_d_player.c 23 symbols, gm_d_player_base.c 18,
  gm_py_player.c 10, gm_py_demo.c 1. Names only.
- With (103)/(104) that is **600 of the two classes' 1,165 functions native**: everything the
  seven inputs reach, except the 8 written-but-off hand natives and 0x80052290.
- **Verified.** Strict A/B (memory hashed every field) of the final build against the (108)
  reference, 300 s per input: a 13,311 / b 14,608 / c 10,320 / d 12,147 / e 12,685 / hm 14,866 /
  wm 14,364 fields, **0 differ**; no "no prologue", no fatal. Windows build links.
- Open: names and descriptions for the 243; the 511 converted but unreached (other power-ups,
  Yoshi, vines / ropes / poles, water currents ... - inputs that use them); camera / scroll next.

---

## 2026-11-15 (108) - Claude (instance 1): track B - the enemy module begins: 855 `d_enemiesNP` functions native (`runtime/gm_en_enemies.c`, new)

- **What.** The user's choice for instance 1 after the library: the game code. The enemy module
  `d_enemiesNP` (`fn_3_*`, linked at 0x809A2EE0-0x80ACD1F8: 7,698 functions - the enemy actor
  classes on `dEn_c`, plus the module's blocks, coins, items, the goal pole, effect actors) is
  claimed in TODO.md (instance 2 / Kimi: not this module, please). New file
  **`runtime/gm_en_enemies.c`** (in both builds' lists): the **855** module functions that the
  seven A/B inputs reach, through `tools/gm_conv.py` (556 with a frame and calls, 298 leaves, 1
  computed frame), each named and described.
- **How the set was chosen.** `gm_conv.py` converts 6,562 of the 7,698 (1,029 are native already -
  the generated state-ID copies of `gm_state_ids.c` - and 107 are refused: 104 are the 8-player
  module's wrappers, 3 have no body of their own). A probe build with all 6,562 as COUNT natives:
  the seven inputs reach 855, and the probe was **identical on every field of all seven** (so
  the converter is sound on this module too). The final build has the 855 only.
- **Names.** The classes have no symbols, but each class's static initialiser passes its state
  names as strings (`"daEnJugem_c::StateID_CloudMove"`), which name the class and its states;
  resource names ("kuribo", "goal_set", "I_kinoko") and build functions (profile numbers) tie
  vtables to classes. So far: daEnBlock_c, daEnBlockCloud_c, daEnBlockHatenaPlayer_c, daEnCoin_c
  and its Angle / Floor / Jugem / Wind kin, the eight daEnDokan(F)Pakkun* classes, daEnFruit_c,
  daEnGlpole_c, daEnItem_c, daEnJugem_c / daEnJugemBody_c, daEnKuribo_c, daEnNoko_c, daEnPata_c,
  daEnPataMet_c, daEnObjBlock_c, daEnPuku_c, daEnRedcoin_c, daEnStarCoin_c, daEnTeresa_c,
  daEnTogezo_c / daEnSakasaTogezo_c, daEnUnizoo_c, daEnWakiJugem_c, daEnBlockHelp_c, the ghost-house
  door; ~100 more classes appear only through their static initialisers (which name them and
  their states). A cname starting with `en_<vtable>_` is a class not identified yet (5 of them).
  The descriptions were written by helper agents from the recompiled code (four chunks, address
  order), merged by script (.text unchanged); where they were unsure the description says what
  the code does without a purpose.
- **Tools.** `gm_conv.py` resolves the RELs' `fn_<module>_<offset>` callees by their linked address
  (from the recompiled headers); `tools/gm_prologues.py` has the enemy module's range
  (0x809A2000-0x80ACE000).
- **Verified.** Strict A/B against the (104) reference, all seven `tools/ab_inputs/`: identical on
  every field (a 28,624 / b 29,703 / c 28,534 / d 30,282 / e 29,152 / hm 31,827 / wm 40,461
  fields); no "no prologue". Windows build links.
- **Next (instance 1).** The other 5,700 convertible: most are enemies none of the seven inputs
  meets (other worlds' enemies - the next test inputs will be levels chosen by which classes
  they create), then the 104 the 8-player module wraps (with their module handover), and class by
  class reading where a class is complete.

---

## 2026-11-15 (107) - Claude (instance 1): track B - 28 more library natives (`gm_nw4r_g3d.c`: 1,939 on): two new test inputs (HOME / pause menus, the world map), `gm_conv.py` takes jump tables and computed frames

- **Where the 1,242 unreached of (105) are.** A reach survey with the COUNT build (every
  convertible library function as a native that logs its first call) over eleven more runs:
  eight other kinds of level by `RT_WARP` (World 1's tower and castle, a ghost house, the 4-airship,
  4-2, a Toad house, an enemy-ambush stage, 3-ghost house), the HOME / pause menus inside 1-1,
  the world map after the 1-1 clear, the title menu's other entries. Together they reach **21**
  of the 1,242. A static call graph says why: 792 have no direct caller (virtual methods of
  classes the game does not use, or tables), the rest are called from the disc-error screen
  (`dDvdErr_c::draw`), the HOME-button menu's draw paths, debugger hooks (`gdev_cc_*`), shutdown
  and destructors. They are left recompiled: a native nobody runs is not tested.
- **`tools/gm_conv.py`** takes two more shapes:
  - jump tables (`switch (ctx->ctr)` from a bctr): the cases stay gotos; a target outside the table
    (impossible) is `rt_fatal`. 8 functions.
  - **raw mode** (`--raw`, or `convert(..., raw=True)`; applybatch uses it when the only refusal is
    r1): functions whose frame size is computed (stwux - nw4r::ut's printf variants with a stack
    buffer of the text writer's size, aligned frames in snd / ef / EGG). The whole body as the
    recompiler wrote it, the stwu / saves / reloads / r1 included, only the calls changed to
    `GM_CALLV`; no GM_FN / GM_NV_KEEP (the code restores what it saves). 22 functions.
  Left refused: 202 under the interrupt lock, 20 mod wrappers, the 3 `_entry` second entries of
  mod-wrapped functions, 5 whose names are not C identifiers (`TextWriterBase<w>` ...).
- **Batch 23** (28): 15 of the survey's 21 finds (the other 6 only the extra levels reach, which are
  not A/B inputs) and 13 of the 30 newly convertible that the seven inputs reach - all 8 jump
  tables (texture-coordinate display lists, the MML sequence parser's command switch, the snd
  output-mode switch, ef's field-kind switch, GX state switches) and 5 raw (snd / ef / EGG aligned
  or computed frames; the 16 printf variants and 802A47C0 are not reached). Named and described
  like the rest (a helper agent from the code; merged by script, .text unchanged).
- **Two new A/B inputs** (instance 2 / Kimi: use them if your classes are on these paths):
  - **hm** - 1-1 with the HOME menu and the pause menu opened and closed four times, d-pad / A / 2
    inside them (`hm_home_pause.txt`: input a's start, then from 82 s every 40 s: `8000` HOME,
    `100`, `004`, `800`, `8000`, `0010` plus, `004`, `001`, `0010`, a run right).
  - **wm** - the 1-1 clear (input e + `RT_TEST_POS=2700,6640,-560`), then on the world map from 110 s
    every 36 s: plus (the map menu), d-pad, 2, 1, plus, HOME twice, d-pad, 2, 1.
  All seven inputs are now in the tree: **`tools/ab_inputs/`** (one `RT_AUTOPRESS` string per
  file, the README gives the settings per input).
- **Verified.** Reach: the COUNT build with the 51 candidates over the seven inputs (28 reached).
  Strict A/B of the final build (28 added) against the (104) reference on all seven inputs:
  **identical on every field** (a 26,605 / b 27,030 / c 28,534 / d 30,282 / e 29,152 / hm 33,249
  / wm 39,990 fields); no "no prologue", no jump-table fatal. Windows build links. The COUNT
  build with all 51 was identical too (a-wm, 28,624-43,710 fields).
- Open: as (105).

---

## 2026-11-14 (106) - Claude (instance 1): every native of (105) named and described (`gm_nw4r_g3d.c`: 0 placeholders)

- The 969 `p_<ADDR>` natives that (105) left undescribed now have a name and a one-line
  description each, like the rest of the file (0x80275BA0-0x802DB970: snd - the wave-sound file
  reader and players, voices, the sound archive / stream / DVD paths, AXFX effects; nw4r::ef -
  Effect, EffectSystem, Emitter, Particle, the key-frame evaluators and emit forms; lyt -
  Layout, panes, ext user data; EGG - heaps, archives, the decompressor, Display / Video,
  screen effects (DoF, blur), lights, the controller / rumble). Written by helper agents from the
  recompiled code (one chunk at a time), each chunk merged by script and checked by instance 1;
  the object code of `gm_nw4r_g3d.c` was compared identical (.text) before and after every
  merge, so (105)'s A/B stands unchanged.
- Functions the helpers called copies were compared line by line: 0x802A18E0 = 0x8029F4A0;
  0x802AA830 is 0x802A5810 with two other float constants (its description says which);
  0x802D5DD0 is 0x802D5290 for the other effect class (size 396 against 132, other callees).
- How sure the descriptions are: they say what the code does (offsets, callees, constants); the
  *purpose* in a name is the helper's reading where no symbol exists - mostly the snd / ef / EGG
  internals whose callees are unnamed (`grep` an address in the file to see its line). Treat a
  cname like `snd_fx_...` or `..._dof_...` as a label, not a confirmed class name.
- Open: as (105) - the 1,242 unreached convertible, the 260 refused.

---

## 2026-11-13 (105) - Claude (instance 1): track B - the nw4r / EGG library by the converter: 1,713 more natives (`gm_nw4r_g3d.c`: 1,911 on), `tools/gm_conv.py`, three prologue-scanner fixes

- **What is new.** `runtime/gm_nw4r_g3d.c` goes from 198 to **1,911** natives: every function of
  the library range 0x80228000-0x802DC000 (nw4r g3d / lyt / snd / ut / math, EGG) that the
  converter can take *and* that one of the five A/B inputs reaches. 399,000 bytes of PowerPC code
  (99,750 instructions); 977 of the 1,713 have a frame and calls, the rest are leaves.
  - Batch 19 (115) and batch 20 (12): converted, then read, named and described by hand, as the
    batches before.
  - Batch 21p (1,586): converted and A/B-tested, **named and described afterwards**. 617 are done
    (0x802281D0-0x80275BA0, by helper agents reading the recompiled code, one line each, merged
    with a script - names and comments only, the object code compared identical before and
    after); **969 still carry the placeholder name `p_<ADDR>` and the comment
    `/* (not yet described) */`**. They are on and tested; the description is what is owed.
    `grep -c "not yet described" runtime/gm_nw4r_g3d.c` is the count.
- **`tools/gm_conv.py ADDR CNAME ...`** (new; replaces gm_leafconv.py's job): a recompiled function
  as a native body in the natives' macros. Leaves as before; new: functions with a frame and
  calls - `GM_FN(addr) + GM_NV_KEEP + GM_LR_KEEP`, the prologue's saves and the epilogue's
  reloads dropped (gm_prologue.c replays them; the scan is gm_prologues.py's own), calls as
  `GM_CALLV(return address, target, 0)`, virtual calls as `GM_CALLV(ret, ctx->ctr, 0)`, frameless
  tail calls as `GM_TAIL`, `R(0) = lr` where the epilogue reloads LR. The statements (the
  floating point above all) stay as the recompiler wrote them. It refuses what wants a hand: code
  before the stwu, a tail call out of a frame, a callee without an address, r1 used other than
  as r1 + n, the mod's wrappers (`g_mod_on`).
  - Of the library range's 3,226 functions: 2,966 convert, 260 are refused (202 take the
    interrupt lock - OSDisableInterrupts / mutexes, left recompiled on purpose; 24 use r1 in
    other ways - alloca, frame chains; 20 are mod wrappers; 9 have indirect jumps; 5 by name).
  - Of the 2,966: 1,911 are reached by the tests and on (with the 198 older ones); **1,242
    convert but no input reaches them - not added** (a native nobody ran is not tested).
    11 are excluded because another runtime file names them or the recompiled symbol
    (0x80267390, 0x80267420, 0x802674C0, 0x80275560 GetPlayingSoundCount - `gm_d_wm_se.c`
    calls the recompiled symbol, 0x80275780, 0x8027A200, 0x802B3300 - `BL(0x81831B10u,
    fn_802B3300)`, 0x802B9280, 0x802BB0E0 / 0x802BB150 / 0x802BB180 - defined in gm_egg.c).
- **Three fixes to the prologue scan** (`tools/gm_prologues.py`; gm_conv.py has the same scan):
  1. `_savegpr_NN` called through its own symbol (`__save_gpr_<addr>` without `_entry`) was not
     seen: fn_80068320 / fn_80068850 (gm_d_actorcreate.c) had incomplete tables.
  2. One wide range for the library, 0x80228000-0x802DC000.
  3. **A store of f0-f13 is never a saved register.** The scan runs past the first call, and in
     0x8023F140 it took an `fctiw` spill of f0 (`stfd f0, 32(r1)`) for an FPR save; the
     generated prologue then stored f0 at entry and the converter dropped the real store. Only
     f14-f31 (stfd / psq_st) count now. Nine existing hand natives' tables changed with this
     (gm_bg, gm_d_cd, gm_c_lib, the libm sin / cos / tan); each was checked: they do those
     stores themselves, so nothing changes for them.
  `runtime/gm_prologue.c` is regenerated (2,079 functions).
- **Verified.**
  - Reach: a `-DGM_G3D_COUNT` build over the five inputs; only reached functions were kept.
  - Strict A/B (`RT_DET_HASH_LIVE`, memory hash per field) against a **new reference: a build of
    the tree at (104)** (see "Environment" below), five inputs - a: 1-1 play, b: title demos
    with A presses, c: `RT_WARP=3,0,0,0` play, d: no input, e: instance 2's 1-1 clear
    (`RT_TEST_POS=2700,6640,-560`): **identical on every field of all five**
    (a 27,767 / b 28,865 / c 27,282 / d 29,416 / e 24,169 fields - each run's whole length; the
    reference was re-recorded at full length, its first 16,000 fields equal to its first pass).
  - The one failure on the way: fields 1677+ of inputs a / c / e, bisected at run time with
    `RT_GM_VERIFY=orig:<names>` on a `-DGM_G3D_VERIFY` build (halving the list of 1,713) to
    0x8023F140 - scanner fix 3 above. After it: clean.
  - No "no prologue" lines; compile `-Wall` clean. Windows build
    links (`build.py --no-deploy`, 700 s).
  - Not done: the per-function `RT_GM_VERIFY_REGS=1` double run for the converted natives (they
    are statement-for-statement the recompiled code; the A/B is the gate).
- **Environment (for whoever tests next).** My container was reset on 2026-11-11: working tree,
  toolchain, game data and the Oct-27 base0 reference were lost. Rebuilt from the user's folder
  (it is the only master copy - nothing unsynced survives a reset). The A/B reference is now the
  (104) tree; the frame counts of entries up to (101) (s81 / s82) are from the old rig and do not
  compare with the new field counts. `_sync/env/tree.tar.zst` and `_sync/env/extracted.tar` in
  the user's folder are my transfer archives for that rebuild (390 MB) - safe to delete, no
  instance needs them.
- **For the other instances.** `runtime/hle_funcs.txt` gains 1,713 names (after
  `GetCamera__Q34nw4r3g3d7ScnRootFi`); any native of yours that calls one of these library
  functions through `GM_CALL*` is unaffected (the call goes to the native). If you reference a
  *recompiled symbol* of the library by name (`fn_802xxxxx(ctx, base)` or `BL(..., fn_802xxxxx)`)
  and it is now native, the link fails with an undefined symbol - call `hle_<name>` instead, or
  tell me and I take it out (the 11 above are such cases).
- Open: 969 descriptions (in progress, in address order); the 1,242 unreached convertible
  functions (need test inputs that reach them: more of snd, lyt animation, EGG's heaps / screens
  / effects); the 260 refused; `EGG::Math<float>::sqrt` (no hle_funcs.txt name).

---

## 2026-11-12 (104) - Claude (instance 2): player classes wave 2 - 103 more daPlBase_c / dAcPy_c methods (97-160 bytes) native

- Same method and helpers as (103): two helper agents, one per class, merged and re-checked by
  instance 2. Batch = every function of 97-160 bytes that the five A/B inputs reach.
- **`gm_d_player_base.c`** (daPlBase_c): 55 on, 4 written but off (`#ifdef PL_BASE_UNREACHED2`, no
  input reaches them: initializeState_Slip, executeState_WaitJump, the wind scaling fn_8004c700,
  setWaitJump). Covers preDraw, changeState (`dAcPy_vf294`), the crouch jump / slip actions, the
  hip-attack actions and initializeState_HipAttack, jump-pad position, grandPowerSet /
  gravitySet / setJumpGravity / getPowerChangeType, jump / land / brake effects, the demo flags
  (isDemo, isControlDemoAll, onDemo / offDemo, changeNormalAction, DemoNone / DemoStartWait), the
  goal demo (getDemoGoalLandPos, executeDemoGoal_Wait, executeState_DemoGoal, initGoalJump),
  initCollision, setStampReduction, the background bookkeeping (setOldBGCross, clearBgCheckInfo,
  the side-limit multipliers, isRideCheckEnable ...), setZPosition, setAddLiftSpeedF,
  updateRideNat and the sound wrappers (suppressSound, startSound / holdSound with mode).
  New static helper `pb_setAnm` (model setAnm through vtable +92 with the rate / blend table
  0x80370DA0).
- **`gm_d_player.c`** (dAcPy_c): all 48 on: Fall / Land / Crouch / Throw state methods, walk and
  swim actions, hip-attack and crouch effects, carry (cancelCarry, checkEnableThrow,
  checkSpinLiftUpRoofHeight), Yoshi / balloon (setRideOnYoshi, setBalloonHelpVoice), star end,
  isNoDamage, propeller checks, doDelete, the 1-1 hint check, ...
- Map / symbol names corrected by the helpers (in the files' comments): 0x80128190 is the decomp's
  fn_801282d0 (not initializeState_Land), 0x801282E0 finalizeState_Land, 0x8012E510 cancelCarry
  (not setFireBallDamage), 0x80138D40 setBalloonHelpVoice, 0x801399A0 setRideOnYoshi, 0x801415B0
  executeState_DemoStartWait, symbol `dAcPy_c__ChangePowerupWithAnimation` (0x80145AC0) is the
  decomp's fn_80145c00, 0x80144B20 is setSceneChangeInfo.
- Bugs caught before merge: isEnableDokanInStatus returned its STATUS_53 test inverted (self-test,
  41/400); setSwimAction_Walk had its blend branch backwards (strict A/B input 3, 33 fields,
  bisected with `RT_GM_VERIFY=orig:`). Both fixed; every conditional of the dAcPy_c batch
  re-checked against the recompiled code.
- Call sites renamed to the `hle_` entries (names only): gm_py_player.c (isDemo, onDemo-type
  fn_8004E100, fn_8004E980), gm_d_player_base.c's wave-1 part (7), gm_d_player.c's wave-1 part (3).
- Verified: self-tests pl_base 97 x 400 and pl_acpy 62 x 400, 0 different (`RT_GM_VERIFY_REGS=1`);
  live verify 0 different except functions that run states / animations / effects when run
  twice (listed in the files); strict A/B against (103): each helper's final build 0 differ on
  all five inputs; merged build 12,940 / 13,624 / 13,413 / 14,540 / 13,587 fields, 0 differ.
  Windows build links.
- Open: the 4 off functions; wave 3 (161-256 bytes) next.

---

## 2026-11-12 (103) - Claude (instance 2): the game's own player classes begin - 254 small daPlBase_c / dAcPy_c methods native (`gm_d_player_base.c`, `gm_d_player.c`)

- Track B's next class after the module: the game's own `daPlBase_c` (E2 0x800460D0-0x8005B3A0,
  same as PAL) and `dAcPy_c` (E2 0x80126510-0x8014A6F0 = PAL - 0x140). 1,165 functions, about
  36,000 instructions. Wave 1 = every function of at most 96 bytes that the five A/B inputs reach
  (258), written by two helper agents in parallel, merged and re-checked by instance 2.
- **Names.** Most of the two classes are unnamed `fn_` in the recompiled code. A map was built
  (kept with instance 2's bench tools, not in the tree) from: the StateID objects in live memory
  (every initializeState_ / executeState_ / finalizeState_ of 36 daPlBase_c and 49 dAcPy_c states;
  `RT_STATESCAN` + `RT_DUMPMEM`), the vtables (daPlBase_c 0x803084C8; dAcPy_c 0x80326794 / the
  helper found 0x80325420 through setDamage at +0x3F4 - two candidates, see Open), the module's
  annotated headers ported PAL -> E2 with `tools/versions-nsmbw.txt`, and NSMBW-Decomp's source
  order between known functions. About 735 of 1,165 named before the helpers checked them; the
  helpers named every function of their batches from the code. Several recompiled symbol names
  in this range are wrong (ported from other games' maps): `HurtMarioBecauseOfBeingSquashed` is
  setBgPressReq, `modifyPlayerPropertiesWithRollingObject` setJumpAddSpeedF,
  `aramGetFirstUserAddress` (0x8012EDC0) getWallBgPointData, `sdpu_release_ccb` (0x80135FC0)
  releasePoleCheck, `continueFromMpPauseFix2` (0x80141460) setChange, `getYoshi__7dAcPy_cFv`
  (0x80139950) getRideYoshi; the Kamek map's getYoshi at 0x80139A90 is finalizeState_RideYoshi.
- **`runtime/gm_d_player_base.c`** - daPlBase_c: 150 on, 4 written but off (`#ifdef
  PL_BASE_UNREACHED`: finalizeState_Slip, calcTimer<s8>, setCcAtSlip, isEnablePressLR - reached
  only late in the title demos, past the 300 s A/B window). Status flags (setFlag / clearFlag /
  testFlag / setStatus), the state-machine plumbing (sStateMgr_c execute / finalize / getStateID,
  the state factory and state object, the 36 `baseID_<state>` getters), angles, slopes / speed,
  hip attack, demo queries, collision (setCcAt*, clearCcData, getCcLineKind ...), squish /
  no-hit / press, counters, effects / quake / rumble, sounds (the SoundHandlePrm ctor / dtor,
  the sound object's startSound / holdSound thunks). `startPatternRumble` follows the recompiled
  code's `g_mod_on` choice of table (0x8185FB1C module / 0x80377C88 game).
- **`runtime/gm_d_player.c`** - dAcPy_c: all 104 on: getters / setters, jump speed, timers
  (calcTimer<s16> / <u8>), the Cc / Bc setup (initCcData, initBcData, setCcAtSpin*, getCcBounds
  ...), carry / Yoshi / balloon queries (getCarryPlayer, getRideYoshi, isNotBalloonCourse - which
  reads the module's or the game's tables by `g_mod_on`, as the PowerPC code does), the 13
  `baseID_<X><daPlBase_c>` getters, the profile's create function. Calls into daPlBase_c go
  through weak `hle_` / recompiled pairs, so the file builds with or without the other file.
- **Call sites renamed** in `gm_py_player.c`, `gm_py_mng.c`, `gm_py_demo.c` (instance 2's files):
  a function listed in hle_funcs.txt loses its recompiled symbol, so the direct calls to testFlag /
  setFlag / clearFlag, getYoshi, setChange and 14 `fn_` now name the `hle_` entry - the same
  function the recompiled callers reach. Names only. (`PL_MAX_SPEED_F` (+280) in gm_py_player.c is
  mMaxFallSpeed by the decomp; `PL_STATE_MGR` 5272 vs the decomp's mStateMgr 5220 - the code is
  right, the names are to be fixed.)
- **`tools/gm_prologues.py`**: RANGES also cover the game's daPlBase_c and dAcPy_c (E2).
- Verified:
  - Self-tests (`RT_GM_VERIFY_REGS=1`) on a live player (scratch memory player+0x2B00..0x2BFF,
    restored): `RT_GM_SELFTEST=pl_base` 85 functions x 400 rounds (74,832 checked calls,
    0 different); `RT_GM_SELFTEST=pl_acpy` 48 x 400, 0 different.
  - Live `RT_GM_VERIFY` + `RT_GM_VERIFY_REGS=1`: daPlBase_c ~23.8M calls on inputs 1-5, 0 different
    except 7 functions that run a state frame / start a jump / a sound when run twice; dAcPy_c
    3.43M calls, differences only in functions that set animations or start sounds / effects,
    and identical in a control build that verifies the PowerPC code against itself.
  - Strict A/B (memory hashed every field) against the build without them (base = CHANGELOG
    (102)), 300 s per input: each helper's build 0 differ on all five inputs; the merged build:
    12,940 / 13,624 / 13,049 / 14,416 / 9,799 fields compared on inputs 1-5, 0 differ
    (merged_2 vs base102); no "GM_FN: no prologue" lines. Windows build (`build.py`) links.
- Open: the 4 off functions; the larger player methods (wave 2 on); the dAcPy_c vtable
  address (two candidates above - check which one the live player uses); the map of the
  remaining ~430 unnamed functions.

---

## 2026-11-11 (102) - Claude (instance 2): the module's controller input (`gm_py_key.c`) and player overrides (`gm_py_player.c`); 25 more module natives (358 on)

- Written by two helper agents working in parallel, each in its own copy of the tree, from a
  brief (method: `docs/DECOMP.md`; checks below); merged, re-checked and deployed by instance 2.
- **`runtime/gm_py_key.c`** - `dGameKey_c` / `dGameKeyCore_c` / `dAcPyKey_c` (the module's
  controller reading, every frame): 9 on - allclear, read, core read, setConfigKey,
  handleTilting, setShakeY, dAcPyKey_c::update, triggerOne, triggerJumpBuf. Written but off
  (`#ifdef GM_PY_KEY_OFF`, no input reaches them): the ctor, the dtor, buttonOne.
  - The `rt_menu.c` wrapper on `read__10dGameKey_cFv` is unchanged: hle_read -> orig_read ->
    (module on) the native; the run-key OR still applies after it.
  - Notes: the ctor's channel table is 0x818498D0; the core read tells the controllers apart by
    vtable (0x80350030 EGG::CoreController, 0x8185E738 GameCube pad, 0x8185E770 wrapper with the
    core at +44) and calls `sqrt__Q23EGG7Math_f_Ff_802BE470` directly. Two module quirks are kept:
    the non-replay path stores `mType = CORE` before looking at the extension, and
    `mTriggered |= m0x30` runs after `m0x30` was cleared.
- **`runtime/gm_py_player.c`** - the module's `daPlBase_c` / `dAcPy_c` overrides: 16 on -
  create, executeChangeInit, initChangeInit, setSpinLiftUpReserve, setSceneChangeInfo, setDamage
  (vf3F4), stopOtherDownDemo, playOtherDownDemo, checkRest, executeState_WallSlide,
  setBalloonInDispOut, setBalloonInDispOutBase, setFallDownDemo, initDemoInDokanUD,
  stopGoalOther, executeDemoGoal_Run. Written but off (`#ifdef PY_PLAYER_UNREACHED`, no input
  reaches them; all were on in an earlier all-24 build whose A/B was clean): the rail-pipe demo
  (initializeState_DemoRailDokan, setExitRailDokan), playGoalOther, the control demo
  (setControlDemoWalk, executeState_DemoControl), updateRopeAngle, setBalloonInDispOutByYoshi,
  setForcedDamage.
  - Every virtual call goes through `ppc_call_indirect`, and WallSlide calls `hle_fn_801266B0` as
    the recompiled code did, so `rt_retro.c`'s hooks (setJump, setHipAttackAction, changeState)
    see the same calls. `dAcPy_vf3FC` (wrapped in rt_retro.c) is not replaced.
  - `RT_GM_REACH=1` logs the first call of each of this file's natives (the reached-functions
    list below came from it).
- **`gm_py_mng.c`**: `PY_STAR_COUNT` / `PY_STAR_TIME` were named the wrong way round
  (setSceneChangeInfo stores the star time at 0x8185EAD0 and the count at 0x8185EAE0); renamed,
  and the comment on vtable +224 now says isItemKinopio (module source). Names only: the
  preprocessed file is byte-identical.
- **`tools/gm_prologues.py`**: RANGES now also cover the module's dGameKey_c / dGameKeyCore_c
  (0x81815400-0x81815800, 0x8182B700-0x8182BC0C), daPlBase_c (0x8180B100-0x8180BE80,
  0x81802800-0x81803400) and dAcPy_c (0x8182D500-0x8182ED00).
- **A fifth A/B input**: Kimi's genuine 1-1 clear (`RT_TEST_POS=2700,6640,-560`, input
  `8..32 step 2 :100:300, 60:204:300000`; goal pole near field 7,300, then castle and world map)
  is now part of instance 2's strict A/B set, so the goal-run code is compared too.
- Verified:
  - Self-tests (`RT_GM_VERIFY_REGS=1`): `RT_GM_SELFTEST=py_key` 9 functions x 300 rounds,
    0 different (buttonOne also 300 / 0 in the build where it was on); `RT_GM_SELFTEST=py_player`
    setSceneChangeInfo 400 rounds, 0 different (updateRopeAngle and setControlDemoWalk 400 / 0
    in the all-24 build; a deliberate one-instruction error in each was caught at 126/400 and
    196/400).
  - Live `RT_GM_VERIFY` + `RT_GM_VERIFY_REGS=1`: all 9 key natives 0 different on inputs 1-5
    (input 5: 12,974 read / 207,584 core read calls through goal, castle and map).
    setSpinLiftUpReserve, setSceneChangeInfo, stopGoalOther, stop/playOtherDownDemo: 0 different;
    executeChangeInit (~79,000 calls) and executeDemoGoal_Run (192) differ only in poll counts on
    the calls where the double run itself changes state (setPowerup / setAnm run twice). The
    others change the world when run twice (allocation, state changes, death messages) and rely
    on the strict A/B, as DECOMP.md allows.
  - Reached: inputs 1-5 all reach the 9 key natives (triggerJumpBuf: inputs 2 and 4); the player
    natives - create, executeChangeInit, setSpinLiftUpReserve, setSceneChangeInfo on all;
    setDamage, stop/playOtherDownDemo, checkRest, WallSlide, both balloon methods on 1-4;
    initChangeInit and setFallDownDemo on 2 and 4; initDemoInDokanUD on 4; stopGoalOther and
    executeDemoGoal_Run on 5.
  - Strict A/B (memory hashed every field, `RT_DET_HASH_LIVE`) against the build without them,
    300 s per input: each helper's own build 0 differ on all five inputs; the merged build:
    12,814 / 12,829 / 11,948 / 13,093 / 12,899 fields compared on inputs 1-5, 0 differ
    (merged_1 vs base68); no "GM_FN: no prologue" lines. Windows build (`build.py`) links.
- Open: the 8 player functions and 3 key functions that no input reaches; the game-side
  `dAcPy_c` / `daPlBase_c` (in the DOL, mostly unnamed) are next.

---

## 2026-11-10 (101) - Claude (instance 1): the open frame of (97) found and fixed (`gm_d_actor.c`); 11 more library natives (198 on)

- **P2's frame 29,443** (the one frame of the strict A/B that differed since (97)) is fixed; all
  four inputs are identical on every frame again (s81: 41,820 / 46,584 / 42,201 / 42,797 frames,
  memory identical at 12,000).
  - What it was: `dActor_c::searchNearPlayer` (0x80064740) keeps its `delta` argument in r31
    over its two calls; the callee `searchNearPlayerNormal`'s prologue saves r31 into its frame.
    The native (`dActor_searchNearPlayer`, an early one, not written register by register) left
    r31 alone, so a different word (1 instead of the stack address 0x8043F9E0) stayed behind in
    that dead stack slot, 0x8043F994. Dead stack is invisible to the game - except that nw4r's
    CalcWorld (0x80250E70) keeps a 76-byte ChrAnmResult local at the same depth, 0x8023EE90
    fills it and leaves the rotation angles (+16..+24) unwritten for a node without rotation, and
    the CalcWorld callback (m3d's `copy_result`, 0x80169600) copies all 76 bytes to the heap.
    For one frame an uninitialised word of the heap copy held the leftover; the game never reads
    it (the flags say "no rotation"), so nothing followed from it.
  - How it was found (the method, since (97) misread the first watch log): `RT_DET_WATCHW` on
    the heap word showed one store per frame, and in that frame the store itself carried the odd
    value (val-before of the *next* store). addr2line on the store's backtrace in both builds:
    fn_80169600 / `copy_result` - a copy from the caller's stack. Then the watch on the source
    stack word (0x8043F994) in both builds, the two logs' stores paired one to one (272 each in
    the frame): exactly one store differs, the r31 save in 0x800647A0's prologue.
  - The fix: `dActor_searchNearPlayer` holds `delta` in r31 over its calls, as the PowerPC code.
  - What it says about the older natives: any native that calls out without the PowerPC code's
    non-volatile registers leaves different dead stack behind. `RT_DET_HASH_LIVE` leaves the
    stacks out for that reason, and this is the first time in ~47k frames x 4 inputs that such a
    word reached hashed memory - through an uninitialised local copied out. If a single-frame
    difference of this kind shows again, this is the recipe.
- Batch 18 (11) in `gm_nw4r_g3d.c`: ScnRoot::GetCamera, ResMatTevColor::GXSetTevColor,
  G3DState::GetRenderModeObj, the 2D objects' scissor / projection type (0x802C6D60, 0x802C6E50,
  0x802D1250), the 2D draw state restore (0x802C7A90), a list to an array (0x802957D0), a
  pointer array read (0x802BD370), an interpolation step (0x80260A80), 0x802432E0.
  Verified: all reached; `RT_GM_VERIFY_REGS=1`: 0 different for 10, 0x802D1250 (a setter) only as
  the double run makes it. Strict A/B s82: identical on all four inputs (39,024 - 44,446 frames).
  (Windows build: with the next entry.)

## 2026-11-10 (100) - Claude (instance 1): track B - 20 more nw4r / EGG library natives (`gm_nw4r_g3d.c`: 187 on), `tools/gm_leafconv.py`

- Batch 15 (8): G3DState's material flush (0x8024CC10) and gen-mode cache (0x8024BAE0), a
  material's buffer pointers (0x80251E50), a ResNode's SRT read (0x8023EE90), the second node
  world-matrix builder (0x80255750), ScnObj::SetScnObjOption (0x80257270, by the jump table),
  a u16 x 12 compare (0x80262FE0), a 2D position to screen units (0x802D1B90).
- Batch 16 (5): a light object into a light setting (0x802CA290 position / direction, 0x802CA140
  parameters), a material's tev order entry (0x8023C760), ScnObj::GetScnObjOption (0x80257410),
  the paired-single rotation matrix from table angles (0x802382B0).
- Batch 17 (7): the three hermite keyframe evaluators (0x802403C0 32-bit keys, 0x80240240 48-bit,
  0x80240100 float keys - the hottest functions left in the profile), a 3x4 matrix inverse
  (0x80242840), a 12-float matrix set (0x802BE580, four on the caller's stack), a light's
  direction / scaled colour (0x802C9E30), a 2D rectangle (0x802C7190).
- New: `tools/gm_leafconv.py ADDR NAME` (stdin: the function's text from `out/*.c`) turns a
  recompiled *leaf* into a native body in the natives' macros (R(n), GM_FRAME, GM_LOOP), its
  floating-point statements untouched. For the paired-single / GQR leaves, where rewriting the
  expressions by hand risks a different rounding; batch 16's rotation matrix and all of batch 17
  were made with it. Not for functions that call (those want GM_FN / GM_CALLV by hand).
- Verified (`RT_GM_VERIFY_REGS=1` over P3 / P2, 0.4 - 3.9 M calls each): 0 different for all of
  batch 16 and 6 of batch 15's 8; the two G3DState cache functions (0x8024CC10, 0x8024BAE0)
  differ only as the double run makes them (the PowerPC pass marks the cache loaded, the native
  then takes the loaded path). Batch 17: 0 different for all 7.
- Strict A/B (`ab4.sh`, 600 s, against base0): batch 15 (s78) and batch 16 (s79) clean on all 4
  inputs - the one difference is still P2's frame 29443 of (97). Batch 17 (s80): the same (P2 compared
  over 20.6k frames only: the reference run was slow).
  Windows build OK.

## 2026-11-10 (99) - Claude (instance 1): track B - 23 more nw4r / EGG library natives (`gm_nw4r_g3d.c`: 167 on)

- Batch 13 (19, the small hot leaves of the call profile): ScnObj's scale kind (0x80257A00) and
  option read (0x802578B0), the 2D state keeper's dst-alpha / scissor (0x802D3040 / 0x802D3270 /
  0x802D3260), two FIFO writers (0x8024A070, 0x80249CB0), ResMatTevColor::DCStore, a text
  writer's line height (0x802308D0), a snd table lookup (0x80283940), an empty deleting
  destructor (0x8022C980), getters and tail calls (0x8023CC90, 0x80260EC0, 0x80248C40,
  0x80248D10, 0x8022BCF0, 0x802CE6B0, 0x80283A60, 0x802570E0).
- Batch 14 (4): G3DState::Invalidate, mTexture_c's EFB copy (0x802C02C0), a node's world matrix
  from its SRT and the parent (0x80254A70), the texture-matrix cache loader (0x8024B990).
- Not taken: SoundActor::GetPlayingSoundCount - `gm_d_wm_se.c` (Kimi) calls the recompiled
  function by its name (`..._80275560`), so an hle entry for it breaks the link. Natives should
  call through GM_CALL / the hle name, not the recompiled symbol.
- Verified: all reached (`GM_G3D_COUNT`); `RT_GM_VERIFY_REGS=1` over P3 / P2: 0 different for 22
  of the 23 (0.3 - 4.8 M calls each); 0x80254A70 differs in f10 only, and only when it works in
  place (r3 == r5: the double run's second pass starts from the first one's result).
- Strict A/B (`ab4.sh`, against base0): batch 13 (s76) and batch 14 (s77, 600 s) clean on
  all 4 inputs. Windows build OK.
  (After a container restart the test box is slower: s76 covered ~21k frames per input instead
  of 28-40k, so P2 did not get to the open frame 29443.)

## 2026-11-09 (98) - Claude (instance 1): track B - 14 more nw4r / EGG library natives (`gm_nw4r_g3d.c`: 144 on)

- Batch 11 (11): the texture-buffer manager (free-list pop 0x802D3590, init 0x802D32F0, get
  0x802D3700), mTexture_c's init (0x802C0240), the two static-buffer getters 0x80250DA0 /
  0x80250DB0, a pane's copy-out (0x802C60D0), the cached animation key lookup (0x8022BF80), a
  32-byte FPR copy (0x8024A530), the scene change (0x802BA710), ScnObj's world matrix calc
  (0x80257900).
- Batch 12 (3): the texture animation entry (0x8022C1F0: frame split into page / column / row,
  then the range-list search), the texture-buffer allocator (0x802D35C0: 32-aligned, low-water
  mark at r13-18196, free-block / free-entry lists), the animation frame-key lookup (0x8022BE60:
  cached index, then the +20 -> +12 range list, returns (u16 << 16) | u8 << 8).
- Verified: every one reached by the test inputs (`GM_G3D_COUNT` first-call logs) and checked
  register-exact with `RT_GM_VERIFY_REGS=1` over P3 / P2 (0x8022C1F0: 182k calls, 0 different).
  The differences that remain are the double run's artifacts: 0x8022BE60 / 0x8022BF80 (the
  original runs first and fills the cache, so the native takes the cached path - fewer polls,
  same registers / memory), the allocators 0x802D35C0 / 0x802D3590 / 0x802D3700 (state taken
  twice), 0x802BA710.
- Strict A/B (`ab4.sh`, 4 inputs x 450 s, against base0): batch 11 (s74) and batch 12 (s75)
  clean. Windows build OK. The only difference on any input is still the one open P2 frame 29443 of (97).
- Left in the library: the hermite keyframe evaluator 0x80240100 (paired singles + fres; wants
  its own pass), EGG::Math<float>::sqrt (no hle_funcs.txt name, off).

## 2026-11-09 (97) - Claude (instance 1): Kimi's parts 88-96 checked against the whole game - 1 fix, 1 open item

- Merged (88)-(96) and ran the strict four-input A/B (`ab4.sh`, memory hashed every frame against
  the fully recompiled build base0): P3 and P3-warp identical; P2 diverged from frame 3,067 and
  the no-input run from 9,927 (365,337 / 1,566,356 words different at frame 12,000).
- Cause (bisected with `RT_GM_VERIFY=orig:<list>` over the 75 natives new since (87)):
  `dScStage_c::calcTitleCount` (`gm_d_sc_stage.c`) stored the wrapped title counter to
  0x80430000 instead of the counter itself (0x80430000 - 24072) - every frame, an unrelated word
  of the small-data area overwritten and the counter never wrapped. Its verification declares
  only the counter's range, so the stray write was invisible to `RT_GM_VERIFY`; the per-function
  native / PowerPC comparison passed it. Fixed.
- After the fix (s73): P3, P3 warp and no input identical on every frame (31,994 / 31,732 /
  33,647 frames), memory identical at frame 12,000; P2 identical but for one frame, 29,443 (memory
  identical at 12,000 and every frame after 29,443). Reproducible; base0 against itself is
  clean there, so it is real. Not from any of Kimi's natives, nor any `RT_GM_VERIFY`-switchable
  native (`RT_GM_VERIFY=orig` keeps it), nor gm_m3d.c / gm_nw4r_g3d.c (built switchable, forced
  to PowerPC: kept). It is four words at 0x81253638 + 76 n (a model's calcWorld buffer): base0
  has 0x8043F9E0 there, the build 1, and the write watch (`RT_DET_WATCH_AT` / `RT_DET_WATCHW`)
  sees no guest store before the frame's first one - so it arrives by a path the watch doesn't
  trap (another mapping of guest memory, or host-side DMA). Earlier strict A/Bs never ran P2 that
  far (28,120 frames), so it may well predate this week. Narrowed further: a build with all 16
  files that have a VERIFY mode (and gm_m3d.c) switchable, everything forced to PowerPC
  (`RT_GM_VERIFY=orig`), keeps it - so it is in one of the files without a VERIFY mode (gm_bg,
  gm_d_cc, gm_d_enemy*, gm_d_scene, gm_m3d_anm, gm_m3d_scene, gm_m_2d / allocator / fader /
  frustum / heap / mtx, gm_state_ids) or in the runtime itself. None of those changed this week.
  ~~Open (instance 1).~~ Found and fixed in (101): a native of gm_d_actor.c left a different
  word in dead stack; the watch log was misread here (there *is* a store - it carries the value).
- `gm_m3d.c` gains a `GM_M3D_VERIFY` mode (its entries switchable at run time) for that bisect.
- Note for track B: a clean strict A/B only covers what the four test inputs reach. None of them
  plays to a game over, the staff credits or a Coin Battle / Free-for-All, so the continue menu,
  staff-credit and multiplayer course-select natives are probably not exercised by it yet;
  inputs that reach them are the next test need.

## 2026-11-08 (96) - Kimi: track B - small-score popup colors complete

- Ported the four remaining `dSmallScore_c` methods in `runtime/gm_d_small_score.c`:
  `setPlayer1000Color`, `setPlayer100Color`, `chgColor` and `DispWait`, covering popup
  player colors, connected-player cycling and display-wait completion. Generated prologue
  coverage contains 845 fixed-frame functions.
- Directed native / PowerPC calls used real initialized popups from `dSmallScoreManager_c`
  and the native module `CreateSmallScore` path. The 29 cases covered all eight players and
  the fallback index, disabled / threshold / advance / wrap color changes, generic and
  60-frame waits, big / small animation, visibility cleanup, scale restoration and color
  changes inside `DispWait`. The A/B matched all **1,439** retained events, including **30**
  directed log events per run. Testing exposed and fixed the player-7 boundary (`<= 7`) and
  `chgColor`'s original pointer-bank selection for connected players.
- Removed the temporary harness and generated diagnostics. The final clean native / PowerPC
  A/B matched all **1,409** retained events. `NATIVE_PORT.md` regenerated: **326 of 1318**
  module functions native across **135 classes**; `dSmallScore_c` **4/4**. Windows no-deploy
  builds used throughout; nothing was deployed.

## 2026-11-08 (95) - Kimi: track B - staff-credit scores complete

- Ported all nine `dStaffCreditScore_c` methods and its free class initializer in
  `runtime/gm_d_staff_credit.c`: layout creation, eight-player coin counters, high-score
  presentation and winner-animation coordination. Generated prologue coverage contains
  841 fixed-frame functions.
- Directed native / PowerPC calls in the real stage scene covered layout success and failure,
  changed / unchanged counters, direct per-player updates, tied and zero scores, high-score
  animation, winner poses and end-wait transitions. The A/B matched all **1,432** retained
  events, including **16** directed results / state hashes. Testing exposed and fixed a winner
  animation index that used the maximum score instead of the player type.
- Removed the temporary harness and allocation diagnostics. The final clean native / PowerPC
  A/B matched all **1,409** retained events. `NATIVE_PORT.md` regenerated: **322 of 1318**
  module functions native across **135 classes**; `dStaffCreditScore_c` **9/9**. Windows
  no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (94) - Kimi: track B - multiplayer course select complete

- Ported all four `dMultiCourseSelect_c` methods and its free class initializer in
  `runtime/gm_d_multi_course.c`: extra eight-player layout panes, player positions,
  favorite-course / play-count setup and rank-star finalization. Generated prologue coverage
  contains 831 fixed-frame functions; the dynamically aligned display initializer has an explicit
  equivalent frame instead.
- Directed native / PowerPC calls in the real multiplayer scene covered layout success and
  failure, positions for 1-8 players, ordinary Free-for-All, Coin Battle, page-10 favorite
  selection and rank stars. Each case matched all **1,029** retained events, including **14**
  directed results / state hashes. Testing exposed and fixed a Coin Battle branch that tested
  the temporary save-buffer pointer instead of the mode flag.
- Removed the temporary scene / animation probes and state dumps. The final clean native /
  PowerPC A/B matched all **1,409** retained events. `NATIVE_PORT.md` regenerated: **312 of 1318**
  module functions native across **135 classes**; `dMultiCourseSelect_c` **4/4**. Windows
  no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (93) - Kimi: track B - stock-item menu complete

- Ported all eight `dStockItem_c` methods and its free class initializer in
  `runtime/gm_d_stock_item.c`: layout creation, eight-player pane selection and positioning,
  item-mode updates, use effects, item selection and window open / close handling. Generated
  prologue coverage contains 827 fixed-frame functions.
- Separate directed native / PowerPC calls covered all 64 pane lookups, 1-8-player layouts,
  position / scale updates, every item mode, effect calls, both Star-selection paths and window
  states. All **1,508** retained ordinary and test events, including **97** directed results and
  state hashes, matched. Observable actor, item, pane, count, presence and mode changes agree;
  this was not a full all-register equivalence claim for `calcPosScale`'s dead residue.
- Removed the temporary directed harness. The final clean native / PowerPC A/B matched all
  **1,409** retained events. `NATIVE_PORT.md` regenerated: **307 of 1318** module functions
  native; `dStockItem_c` **8/8**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (92) - Kimi: track B - continue menu complete

- Ported all 13 `dContinue_c` methods in `runtime/gm_d_continue.c`: layout and continue-state
  setup, player / life displays, pane lookup, card positioning, digit effects, count-up states and
  end-wait handling. Generated prologue coverage contains 818 fixed-frame functions.
- Directed live-object native / PowerPC calls covered results, selected registers, object / layout /
  pane hashes, counter edges, card positions, both effect paths, animation states and sound waits,
  matching all **7,257** ordinary and test events. This was not a full all-register verifier run.
- Removed the temporary directed harness and diagnostics. The final clean native / PowerPC A/B
  matched all **1,367** events. `NATIVE_PORT.md` regenerated: **298 of 1318** module functions
  native; `dContinue_c` **13/13**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (91) - Kimi: track B - player-select menu complete

- Ported all 11 `dSelectPlayer_c` methods in `runtime/gm_d_select_player.c`: layout creation,
  start gating, animation transitions, single / multiplayer cursor setup, member-selection input,
  page wrapping and exit handling. Generated prologue coverage contains 805 functions.
- Directed live-object A/B calls covered the layout guard, start states, animation setup, cursor
  selections and ten non-confirming directional / page-wrap input cases. They exposed and fixed
  the inverted start-wait guard, direction-bit branch and page-wrap comparison; all **1,419**
  ordinary and test events match. Confirmation flows that could not be rolled back safely were
  excluded from the directed matrix.
- Removed the temporary directed harness. The final clean native / PowerPC A/B matched all
  **1,367** events. `NATIVE_PORT.md` regenerated: **285 of 1318** module functions native;
  `dSelectPlayer_c` **11/11**. Windows no-deploy build used throughout; nothing deployed.

## 2026-11-08 (90) - Kimi: track B - course-select manager complete

- Ported all 11 `dCourseSelectManager_c` methods in `runtime/gm_d_course_manager.c`: pre-execute
  gating, continue checks / restoration, all key-wait dispatch arms, stock-item selection,
  interrupt-save callbacks, easy pairing and player power-up queries. The world-map player's
  power-up call now enters native code. Generated prologue coverage contains 794 functions.
- Directed live-manager A/B calls covered every method, all eight key-dispatch flags, the
  eight-player fallback loop and both stock-item directions. Testing exposed and fixed the
  stock-item zero guard: only zero updates the eight players / cursor and changes state. The
  nonzero and interrupt-isolated zero A/Bs each matched all **1,421** ordinary and test events.
  Strict full-register checks of getPlayerPowerup reported no differences.
- Removed the temporary directed harness. The final clean native / PowerPC A/B matched all
  **1,367** events. `NATIVE_PORT.md` regenerated: **274 of 1318** module functions native;
  `dCourseSelectManager_c` **11/11**. Windows no-deploy build used throughout; nothing deployed.

## 2026-11-08 (89) - Kimi: track B - course-select guide complete

- Ported all five `dCourseSelectGuide_c` methods in `runtime/gm_d_course_guide.c`: layout
  creation and destruction, eight-player icon placement / visibility, remaining-life number
  updates and alpha stepping. Generated prologue coverage contains 784 fixed-frame functions.
- Separate directed native / PowerPC calls covered 1, 4, 5 and 8 players, unchanged and changed
  life-number caches, and equal / increasing / decreasing alpha targets. They matched all
  **1,379** ordinary and test events. Separate runs avoid the verifier's double-invocation
  artifact: PowerPC mutates the life-number cache before native receives the same nominal call.
- Removed all temporary test hooks. The final clean native / PowerPC A/B matched all **1,367**
  events. `NATIVE_PORT.md` regenerated: **263 of 1318** module functions native;
  `dCourseSelectGuide_c` **5/5**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (88) - Kimi: track B - world-map player complete

- Completed all 13 `daWmPlayer_c` methods in `runtime/gm_d_wm_player.c`: construction / deletion,
  creation of the eight companions, entry and model updates, guide input, route gating, active
  character flags, game start, skeleton roots and course-entry voices. The deleting destructor now
  frees for flags >= 1, matching the original `blt` skip and restoring the later heap addresses.
- Directed calls on the live player covered both route overrides, skeleton indices 0-10, four
  course-entry points, entry / active-character tables, both model-update modes, player-mode refresh
  and guide handling. Native and PowerPC runs matched all 37 added events and every shared ordinary
  event. Strict full-register checks of the queries reported no differences; the bounded runs did
  not print aggregate totals. Repeated creation was excluded from double-invocation verification
  because the first invocation legitimately changes the companion list seen by the second.
- Removed the temporary directed hook. The final clean native / PowerPC A/B matched all **1,367**
  events. `NATIVE_PORT.md` regenerated: **258 of 1318** module functions native; `daWmPlayer_c`
  **13/13**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (87) - Claude (instance 1): Kimi's parts 67-86 checked against the whole game - 29 fixes

Merging (67)-(86) into my tree and running the strict four-input A/B (memory hashed every frame
against the fully recompiled base, `/tmp/claude-0/ab4.sh`, CHANGELOG (57)) failed: all four inputs
diverged by frame 674 and two crashed when the world-select was deleted (a virtual call through a
null pointer from `fn_80103F10`). The per-function native / PowerPC A/B and the self-tests did not
see it: most world-map natives are declared `GMV_IGNORE_POLLS` with no memory ranges (`0, 0`), so
`RT_GM_VERIFY` checks nothing but registers on them, and the paths taken in the real game differ
from the directed calls. Found with `RT_GM_VERIFY=orig:<list>` (the listed natives run their
PowerPC versions) and a bisection over the active set; each fix confirmed by the next A/B.

- `gm_py_mng.c` createCourseInit: the players' spacing sign (the PowerPC code tests cr2.eq - the
  entry's bit 0 clear - the native had it the other way: players on the wrong side, the first
  difference at frame 674); the shuffle's draw count (`bgt` keeps the count, at least 4 draws - the
  native capped it at 4).
- `gm_d_fukidashi.c`: the destructor cleared 0x8042ACA0 (an unrelated global) instead of the
  manager instance 0x8042A320 (`r13 - 21344`); setInfoFlag x2 read the character / player type
  from r3 / r4 instead of r4 / r5 (so never set the flag).
- `gm_d_wm_se.c`: initialize stored the player sound objects for players 0-2 only (`blt` for
  `ble`) - the world-select deletion then called through the unset fourth slot (the crash);
  execute's actor and list loops polled once less than the PowerPC loops (which enter through
  their test: a poll before every body) - the game clock drifted 0x7A ticks; playSlot's cases 0
  and 1 swapped (0 is the `+36 == 12` check, 1 does nothing); playPlySound: sound 24 for action 5
  only, sound 3 for action 3 only (the native used `< 5`, `< 3`); playSlot called with the bl's
  r3 / r4 / LR.
- `gm_d_gamedisplay.c` execute: the animation step is skipped when +1105 is clear too (inverted).
- `gm_d_wm_subplayer.c`: loadModel's allocation loop polled once less; calcWalkSpeed's store
  path computed as the PowerPC fmul / fmadd (two statements - one expression can contract
  differently).
- `gm_d_wm_player.c`: PlayerEntryUpdate (the third loop's players 1-4 / 5-8 offset swapped; the
  model-type-3 flag inverted); updateSubPlayerModel (the companion test inverted);
  updatePlayerMode (the players 1-4 offset swapped; its call made as the bl, LR and all);
  initActiveCharaFlags (the offset swapped); checkCsGuideKey rewritten against the PowerPC code
  (six branch senses inverted, a key path missing); getCourseInVoiceId (three senses inverted);
  the destructor frees for flags >= 1 (not > 1); getSkeletonRoot takes 0..9 (not 0..8); create's
  createSubPlayers call with the bl's LR.
- `build_linux_clang.sh`: Kimi's ten new files added (build.py had them).
- Pattern for whoever writes the next ones: most of these are a `bne` / `beq` read the wrong way
  round, or a C `while` whose poll sits at the end - the compiler's while loops jump to their test
  first, so the PowerPC code polls before every body. Please keep the strict A/B (`ab4.sh`, or
  any memory-hash run against a fully recompiled build) as the acceptance test: the per-function
  comparison alone passed all of these.
- Verified: the four-input A/B (s71: P3, P2, P3 warp, no input; 450 s each, base0 = the fully
  recompiled PC build): identical on every frame (26,880 / 28,120 / 25,827 / 29,095 frames),
  memory identical at frame 12,000. Windows build OK.

## 2026-11-08 (86) - Kimi: track B - world-map route access complete

- Ported both `daWmMap_c` methods in `runtime/gm_d_wm_map.c`: `IsRouteOpen` and
  `IsIbaraRouteOpen`, including the module's all-routes-open override and the original volatile
  register residue. Generated prologue coverage contains 769 fixed-frame functions.
- Directed native / PowerPC calls on the caller-owned live map object covered both override states
  and matched all **1,370** ordinary and test events. Strict full-register verification found no
  differences; the bounded run did not print aggregate verification totals. The temporary test hook
  was removed, and the final clean A/B matched all **1,367** events.
- `NATIVE_PORT.md` regenerated: **245 of 1318** module functions native; `daWmMap_c` **2/2**.
  Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (85) - Kimi: track B - world-map companion players complete

- Ported all nine `daWmSubPlayer_c` methods and `NodeTrail_c::pushNext` in
  `runtime/gm_d_wm_subplayer.c`: creation, model loading, player ordering, walking-speed updates,
  order-table distance / angle lookups, character / star queries and position-history allocation.
  Generated prologue coverage contains 767 fixed-frame functions.
- Directed native / PowerPC calls on all eight live companion actors covered every query, walking
  speed and all three history-buffer branches, matching all **1,400** ordinary and test events.
  Testing caught and fixed two inverted speed-threshold arms and a missing loop poll; the final
  clean native / PowerPC A/B matched all **1,367** events.
- `NATIVE_PORT.md` regenerated: **243 of 1318** module functions native; `daWmSubPlayer_c` **9/9**.
  Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (84) - Kimi: track B - world-map sound manager complete

- Ported all seven `dWmSeManager_c` methods in `runtime/gm_d_wm_se.c`: construction, destruction,
  initialization, per-frame spatial sound updates, sound-slot dispatch and player voice / movement
  sounds. Generated prologue coverage contains 760 fixed-frame functions.
- Corrected the small-data references to use the actual `r13 = 0x8042F680` base. Also captured the
  first execute-loop's playing result before the nested spatial update, whose calls clobber `r3`.
  Directed native / PowerPC A/B covered eight dispatch categories, valid and rejected voices,
  player movement sounds and deleting destruction, matching all **1,387** events.
- Removed all temporary test and tracing hooks. The final clean native / PowerPC A/B matched all
  **1,367** events. `NATIVE_PORT.md` regenerated: **233 of 1318** module functions native;
  `dWmSeManager_c` **7/7**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (83) - Kimi: track B - world-map scene complete

- Ported all four `dScWMap_c` methods in `runtime/gm_d_sc_wmap.c`: world-map layout creation,
  actor creation, boot-parameter creation and restoration of saved course state. The save manager
  now enters native `initLoadGame`. Generated prologue coverage contains 753 fixed-frame functions.
- Corrected the per-player layout profile table after the first comparison exposed its branches:
  worlds 0-5 use 735 / 736 / 737 / 738, worlds 6-7 use 737 / 736 / 737 / 738, and world 8 onward
  uses 739 / 740 / 741 / 742. Each of the four creation calls passes the player index in `r5`.
- Removed all temporary world-map tracing. The final clean native / PowerPC A/B matched all
  **1,367** events. `NATIVE_PORT.md` regenerated: **226 of 1318** module functions native;
  `dScWMap_c` **4/4**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (82) - Kimi: track B - NAND worker complete

- Ported all five `dNandThread_c` methods in `runtime/gm_d_nand.c`: existence checks, save-command
  queuing and staging, private-file creation / JSON writing / backup rotation, save loading, and
  deletion. Both save-manager call sites now enter the native queue method. Generated prologue
  coverage contains 749 fixed-frame functions.
- The ordinary replay reached only existence checks and loading, so a temporary isolated-root
  directed test also exercised the asynchronous save, write, rename and delete paths. It exposed
  six inverted status branches in `save`; correcting them against the original control flow made
  the native / PowerPC directed A/B match all **1,370** ordinary, completion and test events,
  including `File saved!`. The isolated roots were removed and recreated for each run; the normal
  installation was not used.
- Removed all coverage, tracing and directed-test hooks. The final clean native / PowerPC A/B
  matched all **1,367** events. `NATIVE_PORT.md` regenerated: **222 of 1318** module functions
  native; `dNandThread_c` **5/5**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (81) - Kimi: track B - save manager complete

- Completed all 13 `dSaveMng_c` methods in `runtime/gm_save_mng.c`: construction, refresh, ordinary
  NAND save, multi-mode / quick-save / quick-save-delete serialization, `prepareSave` and
  `initLoadGame`, alongside the five existing slot accessors / copies. The three buffered saves
  preserve the original 32-byte-aligned 16,352-byte alloca frames and stack guards. Generated
  prologue coverage now contains 744 fixed-frame functions.
- Folded the singleplayer character-state adjustment into native `prepareSave`, eliminating its
  former PowerPC forwarding wrapper in `rt_chars.c`. Directed construction and all four save-start
  paths matched all **1,376** ordinary, NAND-completion and directed-test events; a separate
  `prepareSave` A/B matched all **1,368** events. The ordinary replay directly covered refresh and
  game loading. All temporary hooks were removed.
- The final clean native / PowerPC A/B, with all eight newly native methods isolated, matched all
  **1,367** events. `NATIVE_PORT.md` regenerated: **217 of 1318** module functions native;
  `dSaveMng_c` **13/13**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (80) - Kimi: track B - dGameCom utility methods complete

- Ported all six `dGameCom` utility methods in `runtime/gm_d_gamecom.c`: `CreateSmallScore`,
  `showFukidashi`, `WindowPaneColorSet`, `PlayerEnterCheck`, `Player1upColor` and
  `isNowCourseClear`. Generated prologue coverage now contains 739 framed functions; all six
  entry points support isolated PowerPC selection with `RT_GM_VERIFY=orig:<names>`.
- Directed native / PowerPC calls exercised default, player-specific and invalid score creation,
  new and updated speech bubbles, all eight player-entry slots, real HUD text and boot-window
  colours, and early / full course-clear queries. Both runs produced the same **11** directed-test
  events. Strict full-register checks of the two query methods found no differences; the bounded
  run did not print aggregate verification totals. All temporary coverage hooks were removed.
- The final clean native / PowerPC A/B matched all **1,367** gameplay, scene, state-transition and
  test events. `NATIVE_PORT.md` regenerated: **209 of 1318** module functions native; `dGameCom`
  **6/6**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (79) - Kimi: track B - in-game HUD complete

- Ported the last four `dGameDisplay_c` methods: `Effect1Up`, `GrayColorSet`, `ReturnGrayColorSet`
  and `setCollect`, including both 1-up effects, all three saved / tinted text colours, Star Coin
  icon visibility, animation states and the original saved CR2 behavior. Generated prologue coverage
  now contains 735 framed functions; the player manager calls the native `setCollect` entry point.
- Directed live-HUD calls forced the effect guards, produced a successful effect result, saved and
  restored the white / gray colour set, and exercised all three Star Coin state slots. Separate
  native / PowerPC runs matched all **1,371** ordinary and directed-test events. A strict double
  invocation of GrayColorSet was rejected as evidence because its external material writes are not
  idempotent; the separate A/B is the authoritative comparison. All temporary hooks were removed.
- The final clean native / PowerPC A/B matched all **1,367** events. `NATIVE_PORT.md` regenerated:
  **203 of 1318** module functions native; `dGameDisplay_c` **29/29**. Windows no-deploy build used
  throughout; nothing was deployed.

## 2026-11-08 (78) - Kimi: track B - speech-bubble child layouts

- Ported all six `dfukidashiInfo_c` methods in `runtime/gm_d_fukidashi_info.c`: drawing, position
  offsets, the four pane/text colour groups, movement counters, and the Move / Exit finalizers.
  The 572-byte child and its layout objects stay in big-endian guest memory. Generated prologue
  coverage now includes the child's relocated address range (731 framed functions).
- Directed calls on a real initialized child covered every method and two movement-counter branches.
  Strict declared-memory and full-register verification with fatal-on-difference found and fixed
  inverted timer conditions and a wrong session-info instance address; the final directed run had
  no differences. All temporary coverage hooks were removed.
- The final clean native / PowerPC A/B matched all **1,367** gameplay, scene, state-transition and
  test events. `NATIVE_PORT.md` regenerated: **199 of 1318** module functions native;
  `dfukidashiInfo_c` **6/6**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-08 (77) - Kimi: track B - player spawning and speech bubbles

- Translated `daPyMng_c::createCourseInit`, preserving spawn order, character randomization,
  multiplayer spacing and the original stack-array behavior. Its isolated native / PowerPC replay
  matched all **1,367** gameplay, scene, state-transition and test events, completing `daPyMng_c`
  at **39/39** and bringing the verified total to 184 module functions.
- Ported all nine `dfukidashiManager_c` methods in `runtime/gm_d_fukidashi.c`: construction,
  destruction, archive / child-layout creation, per-frame execution and drawing, deletion, display
  values and the two session-info flag setters. Expanded generated prologue coverage to the manager's
  relocated address range. Testing caught and fixed inverted archive / child return checks and missing
  archive-path arguments in `r4`; the manager's constructor and destructor instance addresses remain
  distinct, as in the PowerPC code.
- The final ordinary native / PowerPC A/B matched all **1,367** events. Directed calls covered the
  three methods not reached by that replay: the selected child value changed without touching its
  neighbor, and the session-info flag set and cleared correctly. Both directed A/B runs matched all
  1,367 ordinary events plus the two test events; all temporary tracing and test hooks were removed.
- `NATIVE_PORT.md` regenerated: **193 of 1318** module functions native; `daPyMng_c` **39/39** and
  `dfukidashiManager_c` **9/9**. Windows no-deploy build used throughout; nothing was deployed.

## 2026-11-07 (76) - Kimi: track B - HUD lifecycle, layout and visibility

- Ported and enabled nine more `dGameDisplay_c` methods: destructor, draw, `AreaSetupAll`, execute,
  `AreaCheck`, `AlphaEnterAndExit`, constructor, `createLayout` and `RestDispSetup`. The native code
  preserves the PowerPC frames, nested-call return addresses, animation / state calls, player-to-layout
  coordinate tests, alpha clamps, archive / pane setup, lives-icon placement and material restoration.
- Expanded the verifier's HUD object range from 1,256 to the full **2,192** bytes allocated by classInit.
  The first constructor A/B caught incorrect state-manager interface arguments (916 / 920, not 912 / 916);
  correcting them restored both missing goal-state transitions. No failed build was accepted or deployed.
- Isolated native / PowerPC A/Bs passed for draw + destructor, execute + area / alpha, constructor,
  createLayout and RestDispSetup. AreaSetupAll had its own matching A/B. Every final comparison matched
  all **1,367** gameplay, scene, state-transition and test events.
- `NATIVE_PORT.md` regenerated: **183 of 1318** module functions native; `dGameDisplay_c` **25/29**.
  Effect1Up, GrayColorSet, ReturnGrayColorSet and setCollect remain recompiled.

## 2026-11-07 (75) - Kimi: track B - normal and assist goal settlement

- Ported `dGameDisplay_c::NormalSettle` and `OtasukeSettle`, including rounded time-bonus
  arithmetic, timer / score updates, assist countdown layout updates, sound calls, stack guards,
  saved registers and completion results. Generated their 32-byte and 48-byte prologues.
- The first NormalSettle A/B caught a completion one call early. Instruction-level tracing and
  strict verification isolated two translation errors: the unit / remaining-bonus minimum branch
  and the completion return mapping. The return flag is captured immediately after the CR2
  comparison because native nested calls do not all preserve CR2. All temporary tracing was removed.
- Normal mode's isolated native / PowerPC A/B now matches all **1,367** events. A directed assist-
  mode replay exercised OtasukeSettle and also matches all **1,367** events. The assist override was
  removed after testing. Strict double invocation is not used to accept these world-changing methods;
  its remaining CTR difference came from running nested sound / score code twice.
- `NATIVE_PORT.md` regenerated: **174 of 1318** module functions native; `dGameDisplay_c` **16/29**.
  The HUD's setTime-changing and rest-coin animation paths remain directed-test work.

## 2026-11-07 (74) - Kimi: track B - daPyDemoMng_c complete

- Audited and enabled the remaining nine methods: start / end control demo for all players,
  isAllPlayerControlDemo, getControlDemoPlayerNum, onLandStopReq, startControlDemoLandPlayer,
  isLandAll, setAnimePlayStandardTypeAll, and executeStartToride. Corrected the toride comment:
  it follows the first goal-list player who **has landed**, not one who has not.
- The ordinary single-player clear and a normal stage start did not call any of these methods, so
  absence of verifier differences was not accepted as coverage. A temporary directed live-goal hook
  invoked all nine against the real player objects, including control start / stop, landed-player
  handling, animation setup, and toride states 0 -> 1 -> 2. First-call logs confirmed every method
  was reached; the hook and coverage instrumentation were removed after testing.
- The three read-only methods passed strict full-register / declared-memory verification with
  fatal-on-difference enabled. The world-changing methods were not double-invoked. Separate native
  and PowerPC directed A/B replays matched all **1,129** gameplay, scene, state-transition and test
  events and all directed return-value / toride-state logs.
- `NATIVE_PORT.md` regenerated: **172 of 1318** module functions native; `daPyDemoMng_c` **27/27**,
  `dGameDisplay_c` **14/29**. Next: the remaining HUD methods and daPyMng_c::createCourseInit.

## 2026-11-07 (73) - Kimi: track B - calcNotGoalPlayer and executeGoalDemo_Pole

- Resolved Part 72's `calcNotGoalPlayer` coin-lifetime discrepancy. Full-memory snapshots around the
  timer-expiry call were identical on entry and differed in exactly one byte on exit: the PowerPC
  code cleared `0x80429CF8`, while the native port left `0x0F` there. The cause was a bad address
  constant (`0x80429F38`); the original accesses the key-flag byte at `r13 - 22920 = 0x80429CF8`.
  None of the method's three virtual calls clears the mask. Removed all temporary memory-dump,
  byte-watch, and indirect-call tracing after the diagnosis.
- Enabled native `calcNotGoalPlayer` after the address fix. Strict live full-register and declared-
  memory verification with fatal-on-difference reported no mismatches. Its isolated native / PowerPC
  clear A/B now matches all 1,367 gameplay, scene-transition, and test events, including deletion of
  coin `8152CA98` during play before `KiMePose`.
- Ported and enabled `executeGoalDemo_Pole`: pole-slot collection, the eight-player insertion sort,
  ground and landing-height calculation, goal-list construction, and transition to the next demo
  phase. Its 160-byte frame includes the GPR-helper saves plus f30/f31 and their paired singles;
  `tools/gm_prologues.py` generated the complete entry. As a world-changing method it was checked by
  isolated A/B rather than double invocation: native and PowerPC both produced the same 1,367 events.
- `NATIVE_PORT.md` regenerated: **163 of 1318** module functions native, `daPyDemoMng_c` **18/27**,
  `dGameDisplay_c` **14/29**. The nine control-demo / toride methods remain written but off.

## 2026-11-07 (72) - Kimi: track B - verified goal-demo methods and a genuine 1-1 clear

- **Corrected Part 71's level-ending claim.** Its frame-4900 warp entered `StateID_DemoDown` before
  the world-map transition: it was a death replay, not a successful clear, and its direct settlement
  verification therefore did not establish a normal clear. The replacement warp is frame 2700, with
  right+run beginning only at frame 3600. This lets the camera catch up and create `EN_GOALPOLE` at
  frame 3645; `setDemoGoal` runs at frame 3655. The pole, jump, pose, castle, settlement, goal-end,
  and world-map states all follow, with no death-demo state. The directed test and its bounded,
  opt-in camera-catch-up aid are documented in `docs/DECOMP.md`.
- Enabled nine additional native `daPyDemoMng_c` methods: `executeGoalDemo_PoleDown`, `JumpCheck`,
  `Jump`, `Land`, `KimeWait`, `setGoalDemoKimeAll`, `setGoalDemoRunCastle`, `isAllPlayerGoalIn`, and
  `calcGoalCenterPos`. Strict live full-register and declared-memory verification with fatal-on-
  difference covered JumpCheck 61 calls, Land 74, KimeWait 157, isAllPlayerGoalIn 19, and
  calcGoalCenterPos 358: 669 calls, zero differences. The already-enabled setGoalDemoList and
  getPoleBelowPlayer also passed one live call each, as did HUD setScore.
- The four world-changing methods (PoleDown, Jump, setGoalDemoKimeAll, setGoalDemoRunCastle) cannot
  be double-invoked safely. Controlled single-run A/B tests against their PowerPC implementations
  matched player positions and every goal / state transition. With calcNotGoalPlayer returned to
  PowerPC, the final native 40-second clear and baseline both have exactly 1,367 `[OSReport]`,
  `[scene]`, and `[test]` events in the same order, including deletion of coin `8152CA98` during play
  before `KiMePose`. This is an event-sequence A/B, not a claim of whole-memory hash equality.
- `calcNotGoalPlayer` remains written but disabled. Selective A/B associates its native version with
  that coin surviving until stage cleanup instead of being deleted during play, even though the
  traced timer-expiry call's entry / exit registers, condition state, key flags, and poll count match.
  It is not counted as verified or native. HUD `mod_fn_80158F70` likewise is not newly accepted on
  the basis of double invocation (which changes sound / world state); the successful single-run A/B
  includes its normal settlement path.
- `NATIVE_PORT.md` regenerated: **161 of 1318** module functions native, `daPyDemoMng_c` **16/27**,
  `dGameDisplay_c` **14/29**. `executeGoalDemo_Pole`, the control demos, and toride methods remain
  recompiled. Windows no-deploy build and the corrected native clear both pass.

## 2026-11-07 (71) - Kimi: track B - a 1-1 goal replay and the HUD's goal-settle states

- Added native `initializeState_ProcGoalSettleUp` and `executeState_ProcGoalSettleUp` in
  `runtime/gm_d_gamedisplay.c`. Both replay their 16-byte frames, preserve nonvolatile registers and
  use the original nested-call return addresses. NormalSettle and OtasukeSettle themselves remain
  recompiled; the native execute method calls them as the PowerPC code does. Regenerated the
  prologues, added both `hle_funcs.txt` entries, Windows build OK.
- Built a level-ending test from 1-1's actual course data: the Goal Pole and Fortress sprite is at
  x=6704, y=592. The opt-in `RT_TEST_POS="frame,x,y"` hook in `rt_aspect.c` sets player 1's position
  once, leaving the real actor / collision / goal code in control. **Correction (Part 72):** the
  frame-4900 warp used here entered `StateID_DemoDown` before its world-map transition, so it was a
  death replay, not the successful clear originally claimed. Do not use it as clear verification;
  Part 72 and `docs/DECOMP.md` give the corrected frame-2700 procedure. `RT_AUTOPRESS_FRAMES=1`
  makes the script deterministic in game-frame seconds.
- Live normal-mode goal verification covers both new functions with full register checks and fatal-
  on-difference. Initialization restores the rounded-time destination before its second invocation.
  Execution restores the timer object and player score; `GMV_IGNORE_POLLS` applies only to its nested
  sound calls, while memory and registers remain checked. The completed replay had no `DIFFERENT`,
  fatal or missing-prologue report. The existing 12-function x 400-round HUD self-test also completed
  cleanly. No self-test calls the new execute method through randomized state-manager pointers.
- Added `RT_GM_VERIFY=orig:name,...` to run only selected PowerPC implementations, leaving all other
  natives enabled for controlled A/B tests. Tried whole-replay hash A/B with separate game roots and
  frame-timed input: both sides reached the same goal / world-map sequence, but pre-goal menu counters
  and layout state diverged before either new function could run. Therefore this part does **not**
  claim strict hash-clean A/B; the successful direct live goal verification is the acceptance check.
- `NATIVE_PORT.md` regenerated: 152 of 1318 module functions native; `dGameDisplay_c` is 14/29.
  Normal goal settlement is exercised. Assist-mode settlement (including its initializer call) is
  still pending, as are setTime's changing-layout path and the rest-coin animation path. The new goal
  replay can now be used to verify and enable daPyDemoMng_c's written-but-off goal-demo methods.

## 2026-11-07 (70) - Kimi: track B - dGameDisplay_c's time / score and rest-coin check

- Added native `setTime`, `setScore` and `RestCoinAnimeCheck` in `runtime/gm_d_gamedisplay.c`.
  The first two replay their 32-byte frames and call `LayoutDispNumber` with the original return
  addresses; RestCoinAnimeCheck replays its 16-byte frame and animation / stage-instance calls.
  `daPyMng_c`'s score-display call now targets the native setter. Generated prologue coverage and
  the three `hle_funcs.txt` entries are in place. Windows build OK.
- Verification caught and fixed two inverted branches before acceptance: the original score setter
  exits when the old displayed score is above 99,999,949, and RestCoinAnimeCheck examines its
  request when the active byte is zero. The 12-function x 400-round register-exact self-test now
  completes with no differences. Directed score cases cover equality, the high-score exit and a
  zero-delay increment without calling through random layout pointers.
- Two clean 90-second deterministic headless gameplay / pause runs (the first with temporary score
  tracing, the second without) had no `DIFFERENT`, fatal or missing-prologue report. Live HUD input
  reaches setScore's actual `LayoutDispNumber` path; its declared memory and full registers match.
  That entry alone uses `GMV_IGNORE_POLLS`: verification runs the text update twice but restores
  only the HUD ranges, so the second update can skip text-processing loops in the external text box.
  This is not a global poll-check bypass. setTime's layout-changing path and RestCoinAnimeCheck's
  animation path were not reached; their randomized tests cover only safe non-calling paths.
- `NATIVE_PORT.md` regenerated: 150 of 1318 module functions native; `dGameDisplay_c` is 12/29.
  Strict deterministic A/B remains pending. Goal-settle methods and RestDispSetup remain recompiled
  until a level-end / suitable display test can exercise their score, layout and sound side effects.

## 2026-11-07 (69) - Kimi: track B - dGameDisplay_c's main-game / pause execute methods

- Added `executeState_ProcMainGame` and `executeState_ProcMainPause` to
  `runtime/gm_d_gamedisplay.c`. Both replay their 16-byte PowerPC frames and make the nested
  state-manager change call with its original return address; branch, memory and register behavior
  is unchanged.
- `RT_GM_SELFTEST=game_display` now covers 9 functions x 400 rounds. The two execute methods use
  their no-call paths with randomized object contents (random state-manager contents cannot safely
  drive a transition): 0 differences with `RT_GM_VERIFY_REGS=1`. A 90-second deterministic headless
  gameplay run with scripted input, all nine functions verified and fatal-on-difference enabled
  entered and exited the pause state with no mismatches. Windows build OK; strict deterministic
  A/B is still pending.
- `NATIVE_PORT.md` regenerated: 147 of 1318 module functions native; `dGameDisplay_c` is 9/29.

## 2026-11-07 (68) - Kimi: track B - dGameDisplay_c's first leaf functions

- New `runtime/gm_d_gamedisplay.c`: seven natives from the 8-player module's HUD -
  initialize/finalizeState_ProcMainGame, initialize/finalizeState_ProcMainPause,
  executeState_ProcGoalEnd, the module's empty setPlayNum replacement and RestCoinAnimeSetup.
  All are register-exact leaves; the object stays in big-endian guest memory.
- Added `RT_GM_SELFTEST=game_display`: 7 functions x 400 rounds with random object contents,
  directed less/equal/greater goal-counter cases and both RestCoinAnimeSetup global values.
  `RT_GM_VERIFY_REGS=1`: 0 differences. The self-test caught and fixed a reversed goal-counter
  branch before acceptance. A live headless run with the seven entries verified and fatal-on-
  difference enabled had no further mismatches. Windows build OK; deterministic A/B still pending.
- `NATIVE_PORT.md` regenerated: 145 of 1318 module functions native.
- Windows test-window title: `NSMBW_RENDERER=null` now says `NULL RENDERER (test mode - nothing is
  drawn)` instead of incorrectly reporting a missing OpenGL driver. Hardware OpenGL and the actual
  software fallback are unchanged. Verified with a Windows build; no visual test window opened.

## 2026-11-04 (67) - Claude (instance 2): track B - daPyDemoMng_c (the players' demo manager)

- New `runtime/gm_py_demo.c`: daPyDemoMng_c, the 8-player module's version
  (d_a_player_demo_manager.cpp) - the course-in / course-out / goal lists (the module made them
  8 long with a second block for players 5-8 further into the class: index + 14 / + 26), the
  goal demo's steps (PoleDown, JumpCheck, Jump, Land, KimeWait, KimeAll, RunCastle,
  isAllPlayerGoalIn, calcGoalCenterPos), the control demos (start / end / isAll / count /
  onLandStopReq / startControlDemoLandPlayer / isLandAll), the toride start, calcNotGoalPlayer
  (game-compiled code: r12 virtual calls, signed null checks) and genCourseInList (the CR word
  saved by mfcr written into its frame by hand: the prologue replay doesn't cover r12 = CR).
  Register-exact (gm_i2.h), framed ones with the PowerPC frames.
- On (in hle_funcs.txt): init, setGoalDemoList, getPoleBelowPlayer, setCourseOutList,
  turnNextDemoNo, clearDemoNo, genCourseInList - 7. Written but off (`#ifdef GM_PY_DEMO_ALL`):
  the other 19 - none of the four test inputs reaches a goal pole, a castle-start or a control
  demo, so they can't be checked yet. Still recompiled: executeGoalDemo_Pole (an inlined insertion
  sort with the GPR save helpers).
- genCourseInList shuffles with dGameCom::rndInt: the verify's double run drew twice, so its
  ranges include the game's cRandom_c (0x80429F44) - noted in docs/DECOMP.md.
- `tools/gm_prologues.py`: the module range now starts at 0x81803C00 (daPyDemoMng_c).
- Verified: self-test of the five list functions (300 random rounds, RT_GM_VERIFY_REGS=1): 0
  different; the real game (1-1, 4-1, the title demos, no input) under RT_GM_VERIFY of the
  seven: 0 different; strict four-input A/B against the PC's state before this part (base1):
  identical on every field - 15,960 / 16,587 / 18,130 / 20,008 fields (1-1, title demos, 4-1,
  no input). Windows build OK.
- `NATIVE_PORT.md` regenerated.
- Tried and not found: a test input that reaches 1-1's goal (warping to 1-1's entrances 1-6 with
  the run-and-jump input: no goal demo). A level-end input is the next test need for both
  instances (instance 1's TODO too): `NSMBW_RENDERER=sw RT_DUMP_DIR=... RT_DUMP_EVERY=60` gives
  frames to design one from.

## 2026-10-31 (66) - Claude (instance 1): more library natives - MSL libm / string, g3d camera matrices, panes

- `runtime/gm_nw4r_g3d.c` batches 9-10 (31 more, the next of the call profile; 130 on, 1 off):
  - MSL / fdlibm: `__kernel_sin`, `__kernel_cos`, `sin`, `cos`, `tan` (the double kernels op
    for op - one operation a statement so nothing is contracted into an fma, ps1 untouched as
    the double ops leave it), `fmod`'s tail, `__shl2i`, `strncmp`.
  - g3d: Camera::GetProjectionMtx (ortho / frustum / perspective rebuilt when dirty) and
    GetProjectionTexMtx (the C_MTXLight* calls), the camera slot set of the g3d state,
    ScnObj::SetMtx, two more GetScnObjOption links, an animation key-table lookup (the binary
    search), a sized display list call (GXCallDisplayList or the FIFO), a shape's primitive
    display list, the fog get, an array remove, a frame wrap (fmod, fsel).
  - lyt / misc: a pane's global position (recursive) and global matrix, its origin offset, a
    blend-mode preset, a voice parameter set with interrupts off, a lock-and-wait, small getters.
  - `__div2i` left recompiled: a carry-chain loop that a native would only transcribe.
- Verified: first-call logs (all 31 reached over P3 / P2 / P0); `RT_GM_VERIFY_REGS=1` over P3 /
  P2 - the libm functions, strncmp and the getters identical; the rest only the double run's
  artifacts (dirty bits cleared by the PowerPC run - the projection, a pane's matrix and so its
  parent walk's poll -, an array entry already removed, the MSR left with interrupts held off, a
  poll inside the FIFO call); the four-input A/B after batch 9 (s66): identical on every frame,
  memory identical; after batch 10 (s67): the same. Windows build OK.

## 2026-10-30 (65) - Claude (instance 1): the first library natives - nw4r::ut lists, EGG::ColorFader, nw4r g3d / math leaves

- New `runtime/gm_nw4r_ut.c` (10; OGWS / NSMBW-Decomp ut_list.cpp): List_Insert (Append /
  Prepend inlined), List_Remove, List_GetNext (~436,000 calls a run) / List_GetPrev,
  detail::LinkListImpl's dtor / Clear / Erase(it) / Erase(first, last) / Insert, IsValidBinaryFile.
- New `runtime/gm_egg.c` (5 on, 3 off; eggColorFader.cpp): EGG::ColorFader's ctor, setColor,
  setStatus, calc (subfic with XER[CA]) and draw (the quad written straight into the
  write-gather pipe); setFrame / fadeIn / fadeOut are never called - off.
- New `runtime/gm_nw4r_g3d.c` (OGWS decomp as reference: src/nw4r/g3d/res, src/nw4r/math): the
  hottest g3d / math leaves of the call profile - ResMdl::GetResNode (both), GetResMat (both),
  the shape lookup, GetResNodeNumEntries, the material / texture-SRT flag and getter leaves, a
  3x4 paired-single matrix copy, math::SinFIdx (the quantised psq round trip through its frame,
  GQR3), a setter; then the object callback dispatch (0x8025F0C0), the texture coordinate table
  lookup, the BP texture-coordinate-scale writes, the 3x3 -> 3x4 texture matrix load, the
  ResAnmChr result getter, the vertex array setup (GXSetArray), the material / shape display list
  calls (GXCallDisplayList or straight into the FIFO), a function-static object getter.
- Then (batches 5-7, the next of the call profile): the z-compare location / texture-coordinate
  scale flushes (the BP writes and their tails), the fog set, Camera::GetCameraMtx and the
  projection texture matrix, math::CosFIdx, ResMdl::GetResMatNumEntries, a 4x4 / scaled 3x4
  paired-single matrix copy, the scene objects' SetScnObjOption chain, a draw-order compare
  (mfcr), the node SRT setters, the effect objects' list dispatches (vfunc +28 / +32), a quad's
  colour, a clamped table lookup, ChangeColorUpdate / ChangeAlphaUpdate, a function-static queue
  object; batch 8: MSL strcmp (~820,000 calls a run) / memcmp, mTexture_c (load, the GXTexObj
  init, a setter), the 2D GX state keeper's scissor / viewport / projection / dither setters,
  EGG::Vector3f::normalise, a pane flag walk, the sound 3D position / state setters, a
  list-owning deleting dtor, more list dispatches and clamped lookups. 100 natives in the file;
  EGG::Math<float>::sqrt written but off (its symbol, with `<f>`, has no hle_funcs.txt name).
  All 99 others reached (first-call logs over P3 / P2 / P0).
- Verified: `RT_GM_VERIFY_REGS=1` over P3 / P2 for every native in the three files - identical
  but for the double run's artifacts (each one's state changed by the PowerPC run first: the
  function-static guards, the caches of the z-compare / texture-coordinate / fog / colour and
  alpha update writes, a pending slot cleared, a quad's state cleared, a glyph cache's loop
  count, the camera matrix's dirty bit, a vector normalised in place, strcmp's polls on the
  loader thread counted as foreign, the MSR left by OSRestoreInterrupts with interrupts held
  off); the four-input A/B (s64, with part 64, before batch 8): identical on every frame, memory
  identical; with batch 8 and instance 2's part 61 merged in (s65): identical on every frame,
  memory identical. Windows build OK.
- Merged instance 2's part 61 (gm_py_mng.c, gm_i2.h, gm.h / gm_verify.c, its build list / prologue
  ranges / hle names); my entries renumbered (62)-(65) after its (61), my parts in TODO.md too.

## 2026-10-30 (64) - Claude (instance 1): dCoin_c::execute, dCurtainMng_c, dDvd::loader_c; Util::FrameCounter_c (off)

- New `runtime/gm_d_misc.c` (7): dCoin_c::execute (the coins' shared spin angle and the
  ?-block / brick pattern timers, every course frame; NSMBW-Decomp d_coin.cpp), an empty dCoin_c
  virtual, dCurtainMng_c::CurtainInfoAllClear (d_curtain_mng.cpp), dDvd::create and
  dDvd::loader_c's ctor / dtor / request (the archive loads of the 2D, message and select-cursor
  code; from the recompiled code - no decomp source).
- New `runtime/gm_d_util.c` (6, all off): Util::FrameCounter_c (d_util_frame_counter.cpp) -
  ctor / dtor / init / both play / calc. The first-call logs show no test reaches it.
- Verified: first-call logs (all of gm_d_misc.c reached); the four-input A/B (with part 65, s64):
  identical on every frame, memory identical. (No
  register verify: execute advances its globals, request loads - the double run changes both.)

## 2026-10-29 (63) - Claude (instance 1): dMessage_c / MsgRes_c, dSelectCursor_c, dSmallScoreManager_c's life

- New `runtime/gm_d_message.c` (11 on, 2 off; NSMBW-Decomp d_message.cpp / d_msg_res.cpp):
  dMessage_c's ctor, create (the localised Message.arc, mounted, wii_mj2d.bmg), buildMsgRes,
  getMsg / getMesRes, numToString (the PowerPC code's power-of-ten loop - 8 at a time by
  100000000 behind a CR1 compare, then by 10), numToFullWidth / changetoFullSize; MsgRes_c's
  ctor, getScale / getFont. The two destructors are never called - off.
- New `runtime/gm_d_selectcursor.c` (11; d_SelectCursor.cpp): dSelectCursor_c's profile create,
  ctor / dtor, Layout_c ctor / dtor, create, doDelete, PosSet (two corners per loop iteration,
  its fneg / frsp pairs ps0-only), Cancel, SetPane (the mulhw divisions by 3 of the base
  position), SetAlpha. Its execute / draw were part 50's "five-slot layout manager"
  (gm_d_smallscore.c) - now named. Also dSmallScoreManager_c's profile create, ctor and dtor
  (gm_d_smallscore.c, 3 more).
- Verified: RT_GM_VERIFY_REGS=1 over 1-1 and the title demos: all 0 different but
  changetoFullSize, whose double run converts the string in place twice (the second run sees
  the converted characters - r3 differs). First-call logs over the three inputs: every other
  native is reached. The four-input A/B (20,800-24,100 fields each): identical on every field,
  memory identical.

## 2026-10-29 (62) - Claude (instance 1): the rest of LytBase_c, LytTextBox_c

- New `runtime/gm_d_lytbuild.c` (21 on, 1 off; NSMBW-Decomp d_lytbase.cpp): LytBase_c's ctor /
  dtor, build (Multi_c::build, the 511-character string buffers, the tag processor),
  allocStringBuffer (recursive over the pane tree), ReadResourceEx / ReadResource /
  ReadResource2, the N / W / P / T pane registers and TPaneNameRegister, AnimeResRegister /
  GroupRegister with m2d::AnmResV2_c's / AnmGroup_c's array constructors and element
  destructors, SetScissorMask (its float order, stack temporaries and two dead stores kept),
  doDelete. With gm_d_lytbase.c (the animations) LytBase_c is all native but its static
  initialiser.
- New `runtime/gm_d_lyttextbox.c` (5; d_lyttextbox.cpp): both setMessage (the font, the shadow
  user data, the text, the width fitted from two GetTextDrawRect measurements) and both setText;
  the varargs entries store f1-f8 only when CR6 is set and build their va_list in the frame.
- Verified: RT_GM_VERIFY_REGS=1 over 1-1 and the title demos: 0 different for 13 of 15 checked;
  allocStringBuffer, setMessage(va_list) and setText(va_list) differ only in what the double run
  changes (a second AllocStringBuffer re-allocates - heap polls; a second SetString / font size
  start from the first's results). First-call logs: only one element destructor (0x800C91F0)
  is never reached - off. Also gm_d_wm.c's r13 - 22276 named right (dInfo_c::m_instance, +916
  mIsWorldSelect - a comment / macro name only). The four-input A/B (20,900-25,500 fields
  each): identical on every field, memory identical.

## 2026-10-28 (61) - Claude (instance 2): track B - daPyMng_c (the player manager); my older natives register-exact

- New `runtime/gm_py_mng.c`: daPyMng_c, the 8-player module's version (nsmbw-project
  d_a_player_manager.cpp) - 38 of its 39 functions: who takes part and who is in play
  (getEntryNum / getNumInGame / addNum / decNum / decideCtrlPlrNo / isCreateBalloon), the
  characters' defaults and range checks (initGame / setDefaultParam / checkCorrectCreateInfo /
  checkBonusNoCap / initKinopioPlayer), initStage, the per-frame update (infinite lives, the game
  display's counters, quake timers, a scene exit waiting for the players, the quake's player
  flags, pause, the stage timer), coins (getCoinAll, incCoin with the 100-coin jingle and lives),
  Yoshis (set / release / get / count, the carried-over colour and fruit), the view
  (getActScrollInfo / getScrollNum), the star music and Yoshi drums, executeLastPlayer / All,
  the ground-pound quakes (setHipAttackQuake / setHipAttackSpecialEffect), incRestAll,
  getCourseInListPlrNo, findPlayerWithType, create. Left recompiled: createCourseInit (its spawn
  order sort reads uninitialised stack floats).
- To the current standard (docs/DECOMP.md): every function register-exact (r0-r12, CR0, CTR,
  XER[CA]), framed ones with the PowerPC frame (GM_FN, prologue replayed), the non-volatiles held
  as the PowerPC code holds them at each call, calls to other natives through their hle_ entries
  with LR set. New `runtime/gm_i2.h` holds the helpers (CMPS / CMPU, NONZERO, BL, I2_FN ...).
- My older natives brought to the same standard: gm_mj2d_game.c (dMj2dGame_c: the setters'
  address residue, initialize / versionUpdate framed, the hint-movie bitset's three library
  helpers with their frames), gm_mj2d_header.c, gm_save_mng.c (saveGameCopy framed),
  gm_info.c (dInfo_c: add / sub / getStockItem and initStage framed, register-exact loops).
- Verifier (gm_verify.c): `RT_GM_VERIFY=<list>` kept only the first 1 KB of the list (names past
  it were silently not verified) - now 16 KB; up to 16 ranges per call (was 8: a self-test with
  10 ranges didn't restore the last two); a self-test entry whose letters start with `!` is a
  static function. `tools/gm_prologues.py`: RANGES for the module's daPyMng_c / dInfo_c /
  dMj2dGame_c / dSaveMng_c.
- Verified: self-tests of all 105 of my natives with RT_GM_VERIFY_REGS=1 (200-400 random rounds)
  - 0 differences; the real game (1-1 and 4-1 to ~18,000-20,500 fields) under
  RT_GM_VERIFY=<mine> RT_GM_VERIFY_REGS=1 - 0 differences except update / executeLastPlayer /
  executeLastAll, whose virtual calls play the players' frame (the double run can't compare
  them); strict four-input A/B (1-1, the title demos, 4-1, no input) against a build with none of my
  natives (base0: my hle sections and files left out): identical on every field - 19,115 /
  19,054 / 18,588 / 20,458 fields.
- `NATIVE_PORT.md`: 131 of the module's 1318 functions native.
- Open: createCourseInit; next daPyDemoMng_c (the goal-pole / course-in demos, 27 functions),
  then the module's dAcPy_c / daPlBase_c functions.

## 2026-10-27 (60) - Claude (instance 1): the rest of d_res / d_res_info / d_res_mng; which natives the tests reach

- `runtime/gm_d_res.c` grows by 17 to 30 (NSMBW-Decomp d_res.cpp / d_res_info.cpp /
  d_res_mng.cpp): dRes_c's ctor / dtor / init; dRes_c::info_c's ctor / dtor (the
  VIWaitForRetrace wait) / cleanup / set ("/<folder>/<name>.arc", mSetCallback) / setRes (the
  DVD command's results, the "dRes_c::info_c::mDataHeap" frame heap, loadRes, DCStoreRangeNoSync)
  / loadRes (the file array cleared 8 at a time, then the callback's archive search or
  getFileArray); the archive search callback (the folder signature, the files through the
  callback); dResMng_c (ctor, dtor, resCallback_c::init / execute - g3d files checked, Init,
  Bind - and both setRes).
- New: a `<FILE>_COUNT` build switch in gm_d_res.c / gm_d_wm.c / gm_d_2d.c logs each native's
  first call. Over the 1-1, title-demo and no-input runs these were never called and are now
  written but off (plain GM_HLE, out of hle_funcs.txt): the three destructors and the plain
  copyRes (gm_d_res.c); dWmActor_c::setSoftLight_Map / GetActorType and five dCsvData_c getters
  (0x800F57C0, 57E0, 5950, 5970, 59A0; gm_d_wm.c); d2d::drawBtween (gm_d_2d.c). On now:
  gm_d_res.c 26, gm_d_wm.c 26, gm_d_2d.c 18.
- Verified: the four-input A/B with the off switches in (19,800-23,800 fields each): identical
  on every field, memory identical. (The verify's double run is no use here - mounts,
  heaps, loads twice - so the A/B is the test.)

## 2026-10-27 (59) - Claude (instance 1): dRes_c, the archive manager

- New `runtime/gm_d_res.c` (13 natives, NSMBW-Decomp source/dol/bases/d_res.cpp): getResInfo /
  newResInfo (a CTR loop) / getResInfoLoaded, setRes / deleteRes (the reference counts), the
  three getRes (with the size; with the size and compression: a missing file tried again as
  "<path>.LZ"), the two getResSilently, the two copyRes, syncAllRes. Register-exact, r11 left at
  the frame top where __save_gpr / __restore_gpr leave it. dRes_c::info_c (set / setRes /
  loadRes / cleanup) stays recompiled.
- Verified: RT_GM_VERIFY_REGS=1 over 1-1 and no input (setRes / deleteRes / syncAllRes left out:
  the double run would count references twice / load twice): all 0 different but copyRes's LZ
  path, a few polls apart in a 524,288-poll CXUncompressLZ the native only tail-calls (the
  verify's count of other threads' polls during a long call); the four-input A/B (20,000-23,000
  fields each): identical on every field, memory identical.
- (The container's disk allowance ran out during a rebuild - "Aborted" after the translation,
  the test binary gone. Freed: an old verify build, two hash dumps, an old base build.)

## 2026-10-27 (58) - Claude (instance 1): d2d (the game's 2D layer)

- New `runtime/gm_d_2d.c` (19 natives - drawBtween off since part 60, NSMBW-Decomp source/dol/bases/d_2d.cpp): the draw-list
  wrappers (d2d::draw / drawBefore / drawAfter / drawBtween), d2d::Multi_c (entry, calc /
  calcBefore / calcAfter, draw - the 4:3 / 16:9 orthographic EGG::Screen and the scissor, with the
  PowerPC code's stack temporaries and its GXSetScissor return address 0x80007198 that
  rt_aspect.c keys on - findPaneByName and the TextBox / Picture / Window DynamicCast finds),
  ResAccMult_c's getResource / creater / GetFont, two small helpers and a freeing destructor. The
  constructors and the mod's ArcResourceAccessor replacements stay recompiled.
- Verified: RT_GM_VERIFY_REGS=1 over 1-1 and no input - all 0 different but for what the
  verify's double run changes: entry (the second call finds the layout already in the draw
  list), d2d::draw (the first draw empties the list) and a few draw / calcBefore calls a poll
  off either way (the layout drawn / animated twice); the four-input A/B (20,000-23,200 fields
  each): identical on every field, memory identical.

## 2026-10-27 (57) - Claude (instance 1): the world map's actor base and CSV getters, dScStage_c::getLoopPosX; two frame bugs fixed

- New `runtime/gm_d_wm.c` (33 natives - 7 of them off since part 60, picked by the call profile of the title / attract runs):
  dWmActor_c (ctor / dtor, pre / post Create / Delete / Execute / Draw - preExecute's world-select
  filter and the clip sphere, preDraw's view-clip test - construct, the four setSoftLight_*,
  GetActorType) and the dCsvData_c getters (0x800F56B0-0x800F59A0, 0x800F5A80). Register-exact.
- New `runtime/gm_d_stage.c`: dScStage_c::getLoopPosX, the most called course function (~9
  million calls in a no-input run): the loop-course wrap with the PowerPC loop's two back-edge polls.
- Found by the verify of dWmActor_c::preDraw (r31 different after 1/4 of the calls): mFrustum_c::
  intersectSphere (`gm_m_frustum.c`, part 43) makes its 32-byte frame after some loads, so
  tools/gm_prologues.py saw no prologue (size 0) and the native wrote its three float
  temporaries into the caller's frame (+8 / +12 / +16: a saved r31 and the next back chain).
  Now GM_FRAME(32). The same scan (natives whose prologue came out empty but whose PowerPC code
  makes a frame) found one more: sStateMethod_c::changeStateMethod (0x8015FC10) - the mod
  wrapper's `if (g_mod_on) { ... } else {` in front of the frame stopped the scanner; it skips
  the wrapper now (the native has its 16-byte frame, LR / r31 / r30 saved).
- Verified: RT_GM_VERIFY_REGS=1 over the 1-1 and no-input runs - all listed natives 0 different
  (the ctor / dtor / delete[] / the tails left out: the verify runs a call twice); the four-input
  A/B against the part-48 base (1-1, the title demos, 4-1, no input; 20,200-23,600 fields each):
  identical on every field, memory identical.

## 2026-10-27 (56) - Claude (instance 1): the state-ID natives register-exact; the no-input A/B clean

- The remaining blips of the no-input run, chased with the word watch (RT_DET_WATCHW) and a
  temporary RT_GM_OFF switch (removed again):
  - 14916 (and most of the late ones): nw4r's CalcWorld copies a register the caller never set
    into a model; that register was left by a player state call - and the 2,946 generated
    state-ID natives (sFStateID_c<T>::initializeState / executeState / finalizeState, the
    destructors, number / getRootState / isSameName) called through GM_CALL, which passes LR =
    0 and puts r0-r12 back after the call, so the state function's leftovers never came out.
    gm_state_ids_impl.h is register-exact now (R(n), GM_CALLV with each copy's real return
    addresses - every copy is the same code at its own address, so tools/gm_state_ids.py passes
    the copy's address in; regenerated gm_state_ids.c, hle_funcs.txt unchanged).
  - 12517: an interrupt's timestamp (a ring at 0x8038F86C) a few ticks off - the deterministic
    clock moves on every poll, and dEn_c::PlayerCarryCheck's native polled before every player
    where the PowerPC loop polls on its back-edge only. Rewritten register-exact. (Other older
    natives may have the same "GM_LOOP at the top of the loop" pattern: the verify's poll count
    finds them, the unverified ones need a look - TODO.)
  - rt_det.c: RT_DET_WATCHSTK=1 adds the stack around the running thread's r1 to a watch hit.
- Verified: the four-input A/B against the part-48 base (1-1, the title demos, 4-1, no input; 21,000-24,700 fields each): identical on every field, memory identical.

## 2026-10-26 (55) - Claude (instance 1): a fourth A/B input (no input: the attract demos) and what it found

- An A/B batch run by mistake with no input (the title screen left alone: the attract demos for
  ~19,000 fields) showed what the three recorded inputs never reach: 11 one-field blips and, from
  field 15342, a divergence for good. Bisected with a temporary RT_GM_OFF switch (gm.h, removed
  again) over files, then functions:
  - The divergence: dEn_c::posMove (gm_d_enemy.c) didn't write the PowerPC code's stack
    temporaries (the move vector at sp+12, the angles) or keep f30 / f31 / r30 / r31 as it does;
    a later uninitialised read of that stack copied the difference into the game. Rewritten
    register-exact (R(n), GM_CALLV, the frame's words written as the PowerPC code writes them).
  - 9 of the blips: nw4r g3d's CalcWorld copies an uninitialised stack word into a model's data,
    and that word was the LR some callee of an older native had saved - 0 there, because the
    older natives' GM_CALLs pass LR = 0. tools/gm_callr.py now also matches calls by order when
    a function calls the same target (or through pointers) the same number of times in both
    versions; it gave 72 more GM_CALLs their return address (gm_m3d*.c, gm_d_enemy*.c,
    gm_d_actor.c, gm_bg.c, gm_m_fader.c). ~170 GM_CALLs remain (helpers without a literal FN, or
    different call counts) - TODO.
  - Left: 2 one-field blips (12517: a ring of 8 time values at 0x8038F86C; 14916: the same
    CalcWorld stack word, an LR from a player state call) - TODO.
- /tmp/claude-0/ab4.sh runs the four inputs (1-1, the title demos, 4-1, no input) - the no-input
  one is part of every A/B from now on.
- Verified (parts 53-55 together, against the part-48 base; the runs now reach 25,000-31,000
  fields): 1-1 and 4-1 identical on every field; the title demos 2 one-field blips (29443, 29993 -
  past where earlier A/Bs ended); no input: the blips at 12517 / 14916 and later 26206, 27785 and
  28412-28442, each converging again; memory identical at field 12000 in all four. The late blips
  are most likely the same CalcWorld stack word (the remaining GM_CALLs) - TODO.

## 2026-10-26 (54) - Claude (instance 1): track B - the rest of fBase_c / dBase_c / dBaseActor_c

- fBase_c's default virtuals (create / doDelete / draw succeed, postExecute / postDraw /
  deleteReady do nothing - postExecute and postDraw run millions of times in the tests), an
  fManager_c list-head clear, dBase_c's postExecute / postDraw (tail calls to fBase_c's),
  dBaseActor_c's postDraw, its base matrix (the translation, then the Y rotation) and the clear of
  the 2D actor list: 12 on (gm_f_base.c, gm_f_manager.c, gm_d_base.c); 6 more default virtuals
  written but off (no test calls them). dBase_c's ctor / dtor stay recompiled: the 8-player module
  replaces them (instance 2). With that, every function of f_base / f_manager / d_base /
  d_base_actor is native except the module's.
- Verified: register-exact verify of the leaves (millions of calls, 0 different), A/B - see below.

## 2026-10-26 (53) - Claude (instance 1): track B - LytBase_c's animations

- New `runtime/gm_d_lytbase.c`: LytBase_c (named m2d::EmbedLayout_c in the symbol map) - the
  animation side every 2D screen goes through: AnimeStartBaseSetup, AnimeStartSetup (from the
  start / the last frame), LoopAnimeStartSetup, ReverseAnimeStartSetup, AnimeEndSetup,
  AllAnimeEndSetup, AnimePlay (every layout, every frame), isAnime, isAllAnime: 9 on. The m2d
  calls under them were natives already (gm_m_2d.c). Its build / resource loading / pane
  registers / scissor / delete stay recompiled for now.
- Register-exact verify over the three inputs (RT_GM_VERIFY_REGS=1): 8 entries (all but
  AnimePlay, whose FrameCtrl_c::play isn't repeatable), thousands of calls, 0 different - once the
  verify ranges took in the enabled-flags array as well as the layout (without it the PowerPC run
  had already cleared the flag the native then read: "0 polls (PowerPC 10)").
- Verified: A/B against the part-48 base, 3 inputs - see below.

## 2026-10-24 (52) - Claude (instance 1): track B - dNext_c

- New `runtime/gm_d_next.c`: dNext_c - ctor, createInstance, initialize, setChangeSceneNextDat,
  setOwnNextData, isNextDifferent, searchNextNum (the next-goto box under a position: the int ->
  float conversions through 0x43300000 doubles on the stack kept), both simpleChangeScene()s on;
  changeScene and deleteInstance written but off. execute stays recompiled - the 8-player module
  replaces it (instance 2).
- None of the three test inputs takes a pipe or a door (a verify run: only initialize is reached),
  so the pure ones got a self-test: `RT_GM_SELFTEST=next` runs them against their PowerPC
  versions on the live dNext_c once a course with next-gotos is loaded - random next data, files,
  next-goto IDs, positions in / around the course's next-gotos; 7 functions x 400 rounds, every
  register the same (RT_GM_VERIFY_REGS=1). New input recordings (a pipe, a door, a level end) are
  still the way to switch on changeScene - TODO.
- The "first 1-1 run of a batch starts from a different field-1 state" of parts 49 / 50 (and once
  more here, 49 words differing at 0x935E1290 to the end) was the test bench: both copies of an
  A/B ran in parallel from the same root and shared nand/shared2/sys/SYSCONF, which the runs
  rewrite - one read it while the other wrote it. Each run now gets its own root with a fresh nand
  (/tmp/claude-0/mkroot.sh, used by ab.sh). Worth copying for any parallel A/B (DECOMP.md).
- Verified: A/B against the part-48 base, 3 inputs (separate roots): identical on every field,
  memory identical.

## 2026-10-24 (51) - Claude (instance 1): track B - dSys_c (the frame) and dScene_c

- New `runtime/gm_d_scene.c`: dSys_c::execute - the whole per-frame driver (begin the frame, the
  graph / fader / HOME menu / reset / disc-error drawing, the managers, the scene change and
  fManager's main loop, the frame counters) - with its helpers (begin / end render and frame,
  setBlack, the clear colour, the frame rate, the effect heaps, the three dylink init phases),
  and dScene_c: ctor / dtor, pre/post create / delete / execute / draw (the fade-out before a
  scene change, the fade-in and the scene's sound start), setStartScene / setResetScene,
  createNextScene, the fade lengths. 29 on, register-exact (R(n)). dSys_c::create and the font /
  message / effect manager phases stay recompiled (boot only); setNextScene is rt_lyt.c's.
- A first A/B blipped single fields every ~1500 in all three inputs: beginFrame / endFrame /
  preDraw took their GM_FN address from a `?:` with no `FNADDR` mark, so they ran without their
  frame ("GM_FN: no prologue" in the log). Marked; DECOMP.md says to look for that line.
- The A/B batches had filled the container's disk with 88 MB memory dumps: /tmp/claude-0/ab.sh
  deletes them after the compare now.
- Verified: A/B against the part-48 base, 3 inputs: identical on every field, memory identical.

## 2026-10-24 (50) - Claude (instance 1): track B - the score pop-ups, the 2D GX state keeper

- From part 49's profile, the hottest game functions still recompiled after the wipes:
  dSmallScore_c::execute / draw (all 34 pop-ups of the pool run every frame, shown or not) and
  the GX state keeper the 2D drawing saves / restores around each layout (0x80014380 / 0x80014480,
  no decomp source).
- New `runtime/gm_d_smallscore.c`: dSmallScore_c execute / draw / PosSet, dSmallScoreManager_c
  execute / draw, the five-slot layout manager beside it (0x8010C380 / 0x8010C420, no decomp
  source), the GX state keeper's ctor / save(mask) / restore: 10 on. Register-exact; verified with
  `-DGM_SS_VERIFY` over the three inputs: 0 different in 6 of them (over a million calls of
  execute), the five-slot manager's f12 differs only where its animations ran twice (the doubled
  calls of a verify run); PosSet is only reached inside execute's verification.
- Verified: A/B against the part-48 base, 3 inputs: identical on every field, memory identical.
  (The first 1-1 run of a batch twice started from a different field-1 state - before any game
  code runs, so a file the runs share; run again alone: identical over 20,600 fields.)

## 2026-10-24 (49) - Claude (instance 1): track B - the layout wipes; dCdFile_c's getters' frames

- Picked by a new call profile of the three test runs (the sampler of part 37): of the game code
  still recompiled, the hottest of instance 1's are the wipes' calc / draw (the circle and Mario
  wipes run every frame once created). The camera (dBg_c 0x80077-0x8007A) and the player are
  instance 2's.
- New `runtime/gm_d_wipe.c`: dWipeCircle_c / dWipeDokan_c / dWipeKuppa_c / dWipeMario_c - calc
  (the action through the pointer-to-member table, the layout's animations and calc), draw, the
  open / close set-ups (the pipe picks its animation by the player's height), AnimeEndCheck,
  setStatus, fadeIn / fadeOut: 32 on, one table of addresses for the four classes. Their ctor /
  dtor / createLayout, the circle's CenterPosSet and the pipe's direction check stay recompiled.
  mWipeFader_c setTexture / setStatus / calc written, off (no test reaches it). Register-exact
  (R(n) style); verified with `-DGM_WIPE_VERIFY` (DECOMP.md: the layout calls run twice there):
  every register the same in 28 entries over the three inputs.
- `gm_d_cd.c` (part 46): 8 of the 14 area getters had no prologue - the `FNADDR` mark was on the
  table's first line only, so tools/gm_prologues.py skipped the entries ("GM_FN: no prologue for
  8008E530" ... in every log since) and they pushed no frame. Each entry line is marked now.
- Verified: A/B against the part-48 base, 3 inputs: identical on every field, memory identical
  (a first 1-1 run of the base started from a different field-1 state; run again: identical).

## 2026-10-23 (48) - Claude (instance 1): track B - the older natives register-exact, the field-863 word

- The older natives (gm_c_list.c, gm_f_list.c, gm_f_manager.c, gm_f_base.c, gm_s_state.c,
  gm_d_base.c, gm_d_actor.c, gm_m3d.c's mdl_c::calcWorld / setOption) rewritten where
  RT_GM_VERIFY_REGS=1 found them leaving registers different: register-exact versions (`*_r`)
  of the list / tree helpers, the fManager searches and main loop, the state IDs, the dBaseActor_c
  movement helpers; the pointer-to-member calls (__ptmf_test / __ptmf_scall) and calcWorld's
  G3dProc call through GM_CALLV, setOption as a tail call. Plain versions kept for other natives.
- **The field-863 word (1-1, a one-field blip since part 35):** a model's world-matrix scale entry
  (0x81207D38) written 0 instead of 1.0 by nw4r g3d's CalcWorld (fn_80250E70). Cause: the second
  half (ps1) of f31. The PowerPC code saves an FPR with stfd and reloads it with lfd (ps0 only),
  so ps1 comes back as the function's callees left it (an lfs sets both halves) and leaks to the
  caller - CalcWorld's psq_st / psq_l of f31 then carried that 1.0 into the model. GM_NV_KEEP put
  every ps1 back, so it differed after any native (the framework files and calcWorld each did it
  on their own: why the bisect needed both off). Now GM_NV_KEEP puts ps1 back only for the FPRs
  the original prologue saves with psq_st (GM_FN takes them from gm_prologue.c: gm_psq_).
  Found with a new single-word write watch: `RT_DET_WATCH_AT=field RT_DET_WATCH=page
  RT_DET_WATCHW=word` (rt_det.c, Linux) logs every write to that word with a backtrace and the
  running thread's registers.
- Verified: A/B against a build without instance 1's files, 3 inputs (1-1, the title demos, 4-1):
  identical on every field now (the 863 blip and the title-demo ones are gone), memory identical;
  RT_GM_VERIFY=1 RT_GM_VERIFY_REGS=1 over 1-1: all of instance 1's verified natives 0 different
  (what it lists is instance 2's `mod_` save / 8-player entries: their r0 / r4 temporaries).

## 2026-10-23 (47) - Claude (instance 1): track B - dActorCreateMng_c (creating the course's actors)

- New `runtime/gm_d_actorcreate.c` (d_actorcreate_manager.cpp): setMapActorCreate (+ _next),
  MapActorInital_set / _next, MapActorInitialCreate (the zone's first fill), the per-frame
  MapActorScroolCreateCheck and MapActorScrollCreate (the actors at the new scroll edge),
  mapActorSpawn (the Z counters, the event bits kept for the constructor, dActor_c::construct,
  the actor's fields), GlobalActorCheck / GroupIdCheck / processGroupId, the Z position counters.
  18 on, 4 written but off. Written with the PowerPC registers as its variables (R(n), named per
  function), so it is register-exact by construction; the verified entries pass
  RT_GM_VERIFY_REGS=1 with 0 differences.
- A first run hung on a mistyped constant (the actor info table 0x8030A040, written as 0x80309F40:
  every spawn read profile 0 and built a BOOT actor) - the A/B caught it at once.
- Verified: A/B against part 45's build, 3 inputs x 420 s: identical, memory identical.

## 2026-10-23 (46) - Claude (instance 1): track B - mFrustum_c::set, dCdFile_c, dRail_c, mColor::lerp

- `gm_m_frustum.c`: the two mFrustum_c::set()s (the corners, the view and world planes, the box;
  USA also builds the near / far planes at +176 / +192). On, register-exact.
- New `runtime/gm_d_cd.c` (d_cd.cpp): dCdFile_c's lookups by ID (scroll data, backgrounds 2 / 3,
  next-gotos, areas, ranges, scroll areas), the 14 area field getters (one table), getAreaNo by
  position / by box and both checkRange()s. 24 on, getScrlAreaDataP written but off.
- New `runtime/gm_d_rail.c` (d_rail.cpp): dRail_c - getRailInfoP on; set, calcNextPoint,
  calcTargetPos, calcSpeed, execute, checkArrive written but off (no rail rides in the tests).
- New `runtime/gm_m_color.c`: mColor::lerp, written but off (its callers are in the RELs; not
  reached).
- All new natives register-exact (RT_GM_VERIFY_REGS=1): 0 differences in 1-1, 4-1 and the title
  demos (the counted lookups up to 106 000 calls).
- New reference build for the A/Bs: part 45 (the input fix changes WPAD's device type, so the
  older references don't apply). A/B against it: identical, memory identical (3 inputs x 420 s).

## 2026-10-23 (45) - Claude (instance 1): two Wii Remotes / the keyboard as player 2 - input fixed

- Bug (track A4's native WUD, since 2026-10-16): the HID connection callback got the remote's
  handle where WUD passes its device record. WPAD (fn_801E0820) reads the handle from the
  record's +86 and the device name from +0, so both remotes came out as handle 0: the second one
  to connect took over the first one's channel (_dev_handle_index[0] = 1), and player 1's input
  went to channel 2 / nowhere. With only one remote (or the keyboard alone in slot 1) it worked
  by luck. Symptoms: with the keyboard in slot 2 and a Wii Remote in slot 1 (or any two
  controllers), the strap screen only ended on its timeout, the game never got the title's "2"
  (Singleplayer went back to "press 2", the title demo played), no sound on presses.
- `rt_wiimote.c`: ev_conn hands WPAD a device record (DEVINFO_BUF 0x82034000, 0x80 per handle:
  "Nintendo RVL-CNT-01", handle at +86). The remotes now also come out as Wii Remotes in WPAD's
  device check (they were "unknown", 251).
- Testing: `RT_FAKE_WM_AT=frame` (Linux) connects the pretend remotes late, as a real one found
  after the boot; `RT_AUTOPRESS` now also works in the Windows build (for wine runs).
- Verified (Linux, real-time): keyboard in slot 2 alone, and keyboard in slot 2 + a remote
  connecting late in slot 1 (the reported setup): the strap screen takes the press, Singleplayer
  reaches Game Select. Before the fix both failed, with and without the decompiled code.

## 2026-10-23 (44) - Claude (instance 1): track B - sLib / cLib helpers, register-exact verification

- New `runtime/gm_s_lib.c` (s_lib.cpp, s_Phase.cpp, c_counter.cpp): sLib::addCalc,
  addCalcAngle (both), chase (s16 / int / long / float), chaseAngle, chaseAngleByRotDir,
  sPhase_c (setup, callMethod), cCounter_c::clear. 13 on, 1 written but off.
- New `runtime/gm_c_lib.c` (c_lib.cpp, c_math.cpp, c_random.cpp, c_m3d.cpp, c_owner_set.cpp):
  cLib::addCalcPos / chasePos / targetAngleY / targetAngleX, cM::atan2s + U_GetAtanTable, the
  random numbers (initRnd, rnd, rndInt, rndF; cRandom_c::getRandom / F / F2), cOwnerSetMg_c
  add / remove / clear. 16 on, 3 written but off (cM3d_calcInDivPos1 / 2, rad2s).
- These leaves are called millions of times per run, so they are written register-exact: they
  leave r0-r12, the FPRs and paired singles, CR, XER[CA] as the PowerPC code does.
- `gm_verify.c`: RT_GM_VERIFY_REGS=1 (with RT_GM_VERIFY) also compares every register the two
  versions leave (r0-r31, FPRs, ps1, CR, LR, CTR, XER) - the volatile residue that can reach
  memory later. The older natives fail it (expected: their volatile registers aren't mirrored;
  that is the "older natives' exactness" item). All 29 new ones pass it: 0 differences in 1-1,
  4-1 and the title demos (millions of calls).
- `gm_nv.h`: GM_CALLV(ra, fn, n, ...) - a guest call that leaves every register as the callee
  returns it - and GM_TAIL(fn, n, ...) for a PowerPC tail call.
- Verified: A/B against part 42's build, 1-1 and the title demos x 420 s: identical, memory
  identical (4-1 interrupted; the register check passed in all three).

## 2026-10-18 (43) - Claude (instance 1): track B - mLib m2d (layouts) and mFrustum_c

- New `runtime/gm_m_2d.c` (m_2d.cpp, 33 functions; the slice drifts 0x140 here): the layout
  draw list (reset, defaultSet, draw, drawBefore / drawAfter / drawBtween, Base_c::entry),
  FrameCtrl_c (play / set / setFrame / setRate / isStop - every layout animation's frame),
  ResAccIf_c, Simple_c (calc, build, patrolPane), AnmResV2_c (group animations: findAnmLink,
  setAnmFrame, updateFrame, setAnmEnable, getGroupAnimTransform, remove) and AnmGroupBase_c.
  Written with GM_CALLR and the NV mirror throughout. 25 on, 8 written but off. Not here:
  m2d::create, bindAnimationAuto, Simple_c's constructor / draw, AnmResV2_c::create.
- New `runtime/gm_m_frustum.c`: mFrustum_c::intersectSphere / intersectAABB (the box test's
  paired-single dot product transcribed from the recompiled ps_mul / ps_madd / ps_sum0). Both on.
  Not here: the two set()s.
- Verified: A/B against part 42's build, 3 inputs x 420 s: identical, memory identical.

## 2026-10-18 (42) - Claude (instance 1): track B - the known 1-1 / 4-1 blips found and fixed

- The blips every strict A/B against base0 showed since part 35 (1-1: fields 1984-1985 and 4359;
  4-1: 1984-1985 and 5191; a one-frame-early object / heap block, i.e. real) are gone. Found by
  bisecting at run time: a session-only patch of GM_HLE lets each entry fall back to its PowerPC
  version by file or function name (RT_GM_OFF), so one build and ~100 s runs per probe
  (docs/DECOMP.md has the patch). The causes:
  - `gm_s_state.c` (the state machines every actor runs): no non-volatile mirror around the state
    calls, LR = 0, sStateID_c::number inlined the 8-player module's version instead of calling it
    (its frame was missing), sStateMethodUsr_FI_c's constructor had no frame. Rewritten with
    GM_NV_KEEP / GM_CALLR / GM_FN -> 4359 and 5191 gone.
  - `gm_f_base.c`: the create / execute / draw / delete packs didn't copy their three pointers to
    member functions to the stack (the PowerPC code does, and the stack words are read later);
    commonPack, connectProc, deleteRequest, postCreate / postDelete, runCreate, fBase_make, the
    heap entry functions, the destructor and constructor now mirror r26-r31, pass return
    addresses, and call the framed helpers (cTreeNd_c's constructor / getTreeNext,
    fLiNdBaLink_c::clearData, which got their frames in gm_c_list.c / gm_f_list.c) -> 1984-1985
    gone. commonPack calls through __ptmf_scall as compiled (the trampoline's r0 / r11 / r12 /
    ctr, the callee's volatile registers handed on, cr0 as the compares leave it).
  - `tools/gm_prologues.py`: after `mflr r0` it kept taking any later `stw r0` as the LR save,
    also once r0 had been reloaded with data; 16 replayed prologues wrote the LR where the
    function stores data (the packs, two dEn_c functions, three m3d animation functions ...).
    Fixed.
- What remains against base0: one dead word at 1-1 / 4-1 field 863 (a ChrAnmResult's unused
  rawR.z: 1.0 there, 0 here - stack residue from a deeper call, not found yet) and single-field
  title-demo blips (a different set from before); memory identical at field 12 000 in all three.
- Verified: cumulative strict A/B against base0, 3 inputs x 420 s.

## 2026-10-18 (41) - Claude (instance 1): track B - dCc_c (collision); GM_CALLR in the older files

- New `runtime/gm_d_cc.c` (d_cc.cpp, 24 functions): dCc_c's constructor / destructor, clear,
  entry / release (the collider list), set, reset, isHit / isHitAtDmg, the edges, isInside,
  checkCollision (the copies of both colliders' data on the stack, the kind / attack masks, the
  shape's hit check through _hitCheck[4][4], the result flags, the callbacks) and execute (every
  pair, every frame), _hitCheckSquare / Normal / Loop / Circle / BoxCircle. Not yet: the
  trapezoid checks (DaikeiUD / LR). 19 on (execute runs checkCollision natively), 5 written but
  off. Written with GM_CALLR from the start.
- New `tools/gm_callr.py`: gives GM_CALLs in a decompiled file the PowerPC return address where
  it is unambiguous (the target called once in the original function and once in the native,
  or the only indirect call of each), read from out/recomp_*.c. Run on instance 1's older files:
  260 calls (gm_d_actor 48, gm_d_enemy 59, gm_d_enemy_death 37, gm_m3d 30, gm_m3d_scene 41, ...).
  The rest (calls in helpers without GM_FN, ambiguous targets) still pass LR = 0.
- Verified: gm_d_cc.c A/B against part 40's build, 3 inputs x 420 s: identical, memory
  identical. The GM_CALLR retrofit: cumulative strict A/B against base0 (below).

## 2026-10-18 (40) - Claude (instance 1): track B - mLib matrices / vectors, heaps, allocators, faders; GM_CALLR

- New `runtime/gm_m_mtx.c` (m_mtx.cpp / m_vec.cpp, 18 functions): mMtx_c's rotation matrices
  from s16 angles (the angle goes to nw4r's SinFIdx / CosFIdx through the stack and a quantised
  psq_l, as compiled), XrotM / YrotM / ZrotM, ZXYrotM / XYZrotM, toRot, multVecZero, zero, the
  12-float constructor and Identity; mVec3_c::normalize / normalizeRS / rotX / rotY and the unit
  vectors. 13 on, 5 written but off.
- New `runtime/gm_m_heap.c` (m_heap.cpp, 21): GetOptFlag, setCurrentHeap, createExpHeap /
  createFrmHeap / createUntHeap and their costs, destroy / adjustFrmHeap, createHeap, the saved
  current heap, createFrmHeapToCurrent, the game / archive / command / dylink / assert heaps.
  19 on, 2 off.
- New `runtime/gm_m_allocator.c` (m_allocator.cpp, 28): mAllocatorDummyHeap_c, mAllocator_c,
  mHeapAllocator_c, the mAng3_c units. 26 on, 2 off.
- New `runtime/gm_m_fader.c` (14): mFader_c::draw / setFader, mFaderBase_c, mColorFader_c (not
  its draw: it writes the GX FIFO; not mColor::lerp yet). 12 on, 2 off.
- **New `GM_CALLR(ra, f, n, ...)` in gm_nv.h**: GM_CALL with LR = the PowerPC return address.
  The first m_heap build gave 2-field blips in 1-1 (fields 1674, 4539, 6090) that healed: the
  memory compare at field 1674 showed one word, 0x8016E790 in the reference and 0 here - the LR
  a heap's adjust saves when mHeap::adjustFrmHeap calls it (GM_CALL passes LR = 0). With
  GM_CALLR: identical. The new files use it (tail calls: GM_CALLR(ctx->lr, ...)); the older files
  still pass 0 - a likely source of the remaining known blips. docs/DECOMP.md has the rule.
- Verified: A/B against the build before, 3 inputs x 420 s: identical, memory identical.

## 2026-10-18 (39) - Claude (instance 1): track B - the rest of mLib m3d (scene, animations)

- New `runtime/gm_m3d_scene.c` (m_3d.cpp, 29 functions): m3d::create (the allocator, g3d, the
  scene root) and the full create (EGG screen / GX state / light textures and the light / fog
  manager arrays), createLightMgr / removeLightMgr / createFogMgr / removeFogMgr, the camera
  accessors, the frame's calcWorld / calcMaterial / calcView (light and fog managers, then
  ScnRoot::CalcView / GatherDrawScnObj / ZSort) / drawOpa / drawXlu, pushBack (InsertIntoScene,
  one of the hottest), clear, reset, getNodeID, resetMaterial (DisableIndirectTexturing) and
  m3d::proc_c (create, the draw procedure). 28 on (26 reached, create and removeFogMgr run inside
  them); createFogMgr written, off.
- New `runtime/gm_m3d_anm.c` (87 functions, 0x801650D0-0x80168060): banm_c (destructor, remove,
  createAllocator - its frame heap), anmChr_c (create, setAnm, setAnmAfter - the new
  AnmObjChrRes put back into its blend with the old weight, setFrmCtrlDefault), anmChrBlend_c,
  anmVis_c, and the three per-material classes anmMatClr_c / anmTexPat_c / anmTexSrt_c. Those
  three are the same code but for their nw4r classes, vtables and type names, so one
  implementation takes a table of addresses (`fam_t`: the functions for GM_FN, the return
  addresses for NCALL, the constructors, the type names, setFrmCtrlDefault's offsets);
  anmTexSrt_c also checks its allocations for null. 73 on (37 reached, the children's functions
  and setAnmAfter run inside them, the accessors share code with reached ones), 14 written but
  off (anmVis_c, releaseAnm(index), the child destructors, getFrameMax / getFrameStart,
  anmTexSrt_c::setFrameStart).
- **A function address passed in a table or a parameter needs `FNADDR` on its line**:
  tools/gm_prologues.py only takes addresses from `FN(` lines and lines marked FNADDR; without it
  GM_FN finds no prologue (logged once: "GM_FN: no prologue for ...") and pushes no frame.
- **pgrep -f in a wait loop matches its own shell** when the pattern is in the command line (the
  loop never ends): wait on a script, or anchor the pattern (`^/bin/sh ./build_linux`).
- Verified: A/B per file against the build before (3 inputs x 420 s): identical, memory
  identical (m3d_scene vs part 38's build, m3d_anm vs m3d_scene's).

## 2026-10-18 (38) - Claude (instance 1): track B - mLib m3d (models / animations)

- New `runtime/gm_m3d.c`: mLib's model layer, 68 functions - banm_c / fanm_c (animation
  frames, play / set / isStop / checkFrame), calcRatio_c (animation blending, with the FInv
  fres-and-Newton step written as the recompiled code computes it), bmdl_c (setAnm, node world
  matrix, TEV colours, ...), smdl_c::create, mdl_c and its calc-world callback (ExecCallbackA:
  the blend between the stored and the new node result - quaternion slerp; B: next node; C),
  scnLeaf_c. Against NSMBW-Decomp's mLib/m_3d sources; the slices' addresses drift here
  (fanm_c's constructor is 0x140 before its slice), so functions were matched by code.
  Not here: m_3d_capture.
- New `runtime/gm_nv.h`: GM_NV_KEEP / NV_R / NV_F / NV_FL (non-volatile registers mirrored
  around nested calls, part 37's rule, now shared), GM_LR_KEEP and NCALL (native-to-native calls
  with the PowerPC return address in LR).
- **Compute lis/addi constants with a script, never by hand.** The first gm_m3d.c build crashed
  at the first level (nw4r called a garbage pointer through the model callback's vtable): six of
  eight vtable addresses were 0x500 off from mental subtraction. Checking the other new files the
  same way found one more (gm_d_enemy_death.c's StateID_EatNow, in a function that is off).
- New `tools/gm_check_consts.py`: flags 0x8xxxxxxx constants in runtime/gm_*.c that the
  recompiled code never uses (it knows every literal, function start and lis + addi / D-form
  address in out/). It found a third wrong one, from part 31: gm_f_base.c's HEAP_NAME (the name
  createFrmHeap gets for fBase_c::mHeap) was 0x80329390 instead of 0x803293E0 - harmless (the
  name isn't kept: every A/B since was identical) but wrong; fixed. All files now pass. Run it
  after writing constants.
- vf1C / play, the callbacks, calcRatio and fanm_c::play are among the most called game
  functions; the test runs reach 49 entries directly, the rest run inside them or share code
  with a reached one but for a constant: all 68 on.
- Verified: A/B against the build before (7 min per input): title demos to field 21 098, 1-1 to
  19 928, 4-1 to 19 454 - identical, memory identical. Then the cumulative strict A/B against
  base0 (none of instance 1's files), with the HEAP_NAME fix: exactly the blips known since part
  35/36 (1-1: 1984-1985, 4359; 4-1: 1984-1985, 5191; title demos: the same 8 short runs as in
  part 36), memory identical. Windows build OK.

## 2026-10-18 (37) - Claude (instance 1): track B - every state-ID template copy native (2946 functions)

- Every class with states has its own copy of the sFStateVirtualID_c<T> / sFStateID_c<T>
  template functions: initializeState / executeState / finalizeState (the pointer-to-member call
  every actor state runs through, every frame), the two destructors, getRootState, number,
  isSameName. 2946 copies in the DOL and the RELs, identical but for the getRootState they
  recurse into.
- New `tools/gm_state_ids.py` finds them (recompiled body = the dEn_c copy's, once addresses,
  labels and the recursion target are normalised), checks that no listed name also stands for
  something else (the recompiler replaces by name), and generates `runtime/gm_state_ids.c` (one
  line per copy) and its section of `hle_funcs.txt` (between "# track B (instance 1): state-ID
  templates" and "# end of state-ID templates" - regenerate, don't edit). The one
  implementation is `runtime/gm_state_ids_impl.h`. The 8-player module's own copies stay
  recompiled. Rerun the script if the recompiler's naming changes.
- gm_d_enemy_death.c's hand-written dEn_c copies went into this.
- REL functions are listed in hle_funcs.txt by their table name (`fn_1_1810`, not the C
  identifier `fn_1_1810_80769DF0`). Note: tools/gen.sh's grep hides recomp.py's
  "WARNING: HLE names not found" line - a wrong name is silently ignored.
- Side effect: the deterministic replay runs ~14% more frames in the same time (title demos).
- New `runtime/gm_d_enemy_carry.c`: dEnemyCarry_c (enemies a player picks up and throws), 11
  functions, all written but off - no test run reaches a carryable enemy. The module replaces
  initializeState_Throw (u8[8] mNoHitPlayer): not decompiled.
- **Choosing what to decompile by profile.** A temporary sampler thread reading the PPC_TRACE
  ring (the last 256 function entries) every ms gave a call-frequency profile of the test runs
  (`/tmp` tool, not in the tree; the trace ring is in every Linux test build). Hot and still
  recompiled: the SDK (OSDisable/RestoreInterrupts ~8% of calls, GX state), libc, the
  __save/restore_gpr helpers (~10%; can't be listed by name - many entries share one), nw4r
  g3d, and in the game the background tile lookups. Everything in such a profile is reached by
  the tests by construction.
- New `runtime/gm_bg.c`: the background tile lookups - dBc_c::getUnitType / getUnitKind,
  dBgGm_c's unit at a position, a tile number's flags (with the on/off-switch overrides),
  BgGmBase / TilemapClass::getPointerToTile, the block lookup: 16 functions (no decomp source;
  from the recompiled code). Flags come back in r3:r4. Where one native calls another directly,
  ctx->lr is set to the PowerPC return address first, so the saved-LR words on the guest stack
  are exact; entries restore LR on return.
- **New exactness rule (found by this A/B): mirror the non-volatile registers.** The first
  gm_bg.c version differed in the title demos for 57 fields at ~14 634, from 4 heap words (0x137
  vs 0, in four objects 0x4C apart). The PowerPC code keeps values in r27-r31 across its calls
  (here r30 = the tile number); the callee saves them into its frame; the game later copies such
  a dead stack word into the heap. The natives now put the same values into ctx->r[27..31]
  before a nested call and restore the entry values on return (`NV_KEEP` in gm_bg.c): identical
  again. This is probably also behind some of the older transient blips (with GM_CALL's LR = 0).
- Verified (strict A/B against the build before each step, 7 min per input): state-ID copies -
  title demos to field 28 515, 1-1 to 23 040, 4-1 to 23 438: every hash identical, memory
  identical. gm_bg.c (after the register fix) - title demos to 24 898, 1-1 to 22 379, 4-1 to
  27 233: identical, memory identical. Windows build OK.

## 2026-10-18 (36) - Claude (instance 1): track B - dEn_c's death and states decompiled

- New `runtime/gm_d_enemy_death.c`: d_enemy_death.cpp and d_enemy_state.cpp - 83 functions - plus
  dEnCombo_c (7, the combo scores). How an enemy dies: the hitCallback_* reactions (star, cannon, slide, fence, large, spin,
  ground pound, Yoshi, fire, ice, shell...), setDeadMode and the setDeathInfo_* helpers that fill
  mDeathInfo, the Die* states (Fumi, Fall, BigFall, Smoke, IceVanish, YoshiFumi, Goal, Other),
  the death sounds; changeState and the Ice / HitSpin / Eat* states; and the
  sFStateVirtualID_c<dEn_c> template (initialize / execute / finalize through the
  pointer-to-member call, getRootState, number, isSameName, the destructors).
- The module replaces none of these; its player-count patches (cancel-carry loops 4 -> 8, score
  checks 3 -> 7, YoshiHipAttk's 4 -> 8) are followed with g_mod_on, as the recompiled code.
  hitCallback_Shell's "player < 4" is not patched in the module - kept.
- 46 on in `hle_funcs.txt` (new section): the 19 the test runs reach (frozen enemies breaking
  and vanishing, smoke, changeState, the state calls - mostly from the title demos) and the 26
  whose bodies are empty. 38 written but off - most need a power-up or Yoshi in a test run
  (list in the file). Not decompiled: the two static initialisers and their 13 getters.
  dEnCombo_c: only getDamageScore is reached (the stomp code in gm_d_enemy.c works the combo
  out itself); the other 6 are off.
- Verified (strict A/B, 10 min per input on 2 cores): against base0 (none of instance 1's files)
  1-1 to field 32 530 and 4-1 to 32 124 - only the known blips (1984-1985, 4359 / 5191), memory
  at field 12 000 identical. Title demos to 37 347: memory identical, but 33 short blips (single
  fields and a few ~30-field runs) - these were already there in part 35 (its run stopped at
  18 184): against a part-35 build the new file adds 2 single-field blips in 35 694 fields
  (26330, 30703), memory identical. Probably LR = 0 from GM_CALL again; worth a look sometime.
  dEnCombo_c round: identical to the round before on all three inputs. Windows build OK.
  Coverage by temporary counters (the GM_HLE macro redefined to log the first call of each).
- Each sDeathInfoData literal is built in a stack temporary from a constant table at 0x802F0560
  (32 bytes per kind) and then copied; `death_info()` does the same, temporary included.
- `tools/gm_prologues.py`: covers 0x800A0000-0x800A2900 and 0x800A7D00-0x800A8300 too; a line
  containing `FNADDR` has its addresses added (for functions that pass their address to a shared
  helper's GM_FN).
- Note for anyone writing gm code: `GM_CALL(f, n, ..., GM_CALL(...))` doesn't compile (a macro
  isn't expanded inside itself) - use a temporary.

## 2026-10-18 (35) - Claude (instance 1): track B - A/B against no decompiled code; two bugs fixed; prologues replayed

- **A stricter A/B.** The baseline is now a build without any of instance 1's track B modules
  (`hle_funcs.txt` cut before "# track B (instance 1): cLib", and the gm_c_list ... gm_d_enemy
  objects left out of the link - verified hle functions reference `orig_` names that a shorter
  list doesn't generate). Before, each part was compared against a build that already had the
  earlier parts, so a bug in an earlier part could hide. It found two:
  1. `dActor_c::ActorScrOutCheck` (gm_d_actor.c, since (32)) deleted an off-screen actor when
     flag 2 was **set**; the PowerPC code deletes it when flag 2 is **clear**. Off-screen actors
     that should go (1-1's arrow sign, for one) stayed until the level ended.
  2. The 8-player module replaces three state functions at their start (`if (g_mod_on)
     mod_...`): `sStateID_c::isSameName`, `sStateID_c::number` (gives a state made with -1 the
     next number) and `sStateMethod_c::changeStateMethod` (can log changes). The hle versions
     (gm_s_state.c, since (29)) replaced the module's too. Now the module's run when it's on.
     `tools/check_hle_mod.py` lists every hle'd function the module hands over at its start (run
     it after gen.sh; besides these, it shows dGameKey_c::read, dScStage_c::setNextScene,
     fn_80154F60 and OSPanic - instance 2 / track A ones, fine if their hle calls `orig_`).
- **Prologues replayed.** `GM_FN(address)` (gm.h) makes the PowerPC function's frame and replays
  its prologue - saved LR (the return address) and saved GPRs / FPRs / paired singles - from
  `runtime/gm_prologue.c`, generated by `tools/gm_prologues.py` from the recompiled code (rerun
  it when adding a module in a new address range: RANGES at the top). Every decompiled
  function in gm_f_list / gm_f_manager / gm_f_base / gm_s_state / gm_d_base / gm_d_actor /
  gm_d_enemy uses it now. The game copies uninitialised stack words into the heap (nw4r
  emitters, attention, 3D objects) and keeps stack addresses; without exact frames that showed
  as thousands of "harmless" differences.
- Result against the strict baseline: 1-1 (field 15778), title demos (field 18184): memory at
  field 12000 identical (0 words); per-field hashes identical except a few short stretches
  (1-1: fields 1984-1985 and 4359). Those are stack garbage that is still not exact: the module
  sorts 8 player values of which some are uninitialised stack (different garbage: 4 extra loop
  polls, so a few time stamps move for two fields), and guest functions called with GM_CALL
  save LR 0 instead of the original return address. They don't last.
- New files: runtime/gm_prologue.c / .h (build.py, build_linux_clang.sh updated),
  tools/gm_prologues.py, tools/check_hle_mod.py. Windows build OK.

## 2026-10-17 (34) - Claude (instance 1): track B - dEn_c (the enemy base) decompiled

- New `runtime/gm_d_enemy.c`: `dEn_c`, the base class of every enemy - 72 functions, 44 switched
  on in `hle_funcs.txt` (new section "dEn_c"). Covered: constructor / destructor, postCreate /
  postExecute / preDraw, posMove, Bound, the collision dispatch (EnDamageCheck, PlDamageCheck,
  YoshiDamageCheck, EtcDamageCheck, the Vs hit checks), Enfumi_check and the stomp reactions
  (jumps, combo score, combo sounds and clap, effects), EnBgCheck / Foot / Wall,
  WaterCheck / WaterLineProc and the liquid speeds, lava / poison splashes, the player-near and
  carry checks (8 players with the module, as the recompiled code), calcCarryPos,
  turnangle_calc, the eat / fire / ice / damage / boyon helpers, block_hit_init.
- The module's own versions stay recompiled: preExecute, normal_collcheck, slipBound,
  setEatSpitOut (its mNoHitPlayer is u8[8] at +0x504).
- 28 are written but left off because no test reaches them; the list is in the file, above the
  hle entry points.
- **Stack frames matter.** Each decompiled function now makes a guest stack frame as big as the
  PowerPC code's (`FRAME(n)`, popped on every return). Without it, two kinds of differences
  showed up: a global that keeps a stack address was 16 bytes off for ~100 fields, and nw4r
  effect emitters copy uninitialised stack words into the heap (9 words different for good).
  With the frames: every per-field hash identical and whole memory identical. This is likely
  also where the "known saved-LR words" of earlier A/B runs came from - worth redoing
  gm_d_actor.c / gm_d_base.c the same way.
- Verified: A/B against a build without the new names (plain GM_HLE runs decompiled even with
  RT_GM_VERIFY=orig) - title demos to field 18641, 1-1 to field 15201 and 4-1 (RT_WARP=3,0,0,0)
  to field 15189: all hashes identical, memory at field 12000 identical (0 words). Coverage
  counters picked the 44. Windows build OK.

## 2026-10-17 (33) - Claude (instance 1): track B - dActor_c part 3; test inputs that really play

- `runtime/gm_d_actor.c`: 18 more `dActor_c` functions. 8 are switched on in `hle_funcs.txt`:
  `searchNearPlayer_Main` (fn_80064790), `getTrgToSrcDir_Main` (fn_80064A30), `changePosAngle`
  (fn_80064AF0), `setSoftLight_Enemy` / `_Map` / `_MapObj` / `_Item` (sub_80064BD0,
  fn_80064BE0, sub_80064BF0, oneSetupType), `waterSplashEffect` (_vfC8). 10 are written but
  left off because no test run reaches them: `setChangePosAngleFunc`, `setSoftLight_Player` /
  `_Boss`, `allEnemyDeathEffSet` (killedByLevelClear), the Yoshi eating ones (`calcSpitOutPos`,
  `calcEatScaleRate`, `calcEatInScale`, `eatMove`) and the lava / poison splashes (enemies
  use `dEn_c`'s own). `dActor_c`: 42 of ~70 on, 14 more written.
- **Test inputs fixed.** `RT_AUTOPRESS` masks are Wii Remote core bits: 2 = `100`, 1 = `200`,
  d-pad down = `004` (right with the remote sideways), `001` is d-pad left. Our title menu only
  takes 2 or A, so the old start sequence (mask `1`) never left the title: runs (27)-(32) tested
  the title's demo plays only (real levels with enemies, so still a real test, but no menus,
  no 1-1). The working sequence: 2 every 2 s from 8 s to 66 s (title -> Single player -> Game
  Select -> 1-1), then `70:204:300000` (right + run held) and a jump `:100:350` every 1.3 s
  from 71 s. `RT_WARP=w,l,a,e` (0-based) swaps the first level started (e.g. `3,0,0,0` = 4-1).
  docs/DECOMP.md has it.
- Verified: plain `GM_HLE` functions run decompiled even with `RT_GM_VERIFY=orig`, so the A/B
  baseline is a build without the new names (s32 list). Demo run to field 17112 and 1-1 run to
  field 15451: every per-field hash identical, whole memory at field 12000 identical (0 words).
  `RT_GM_VERIFY=1` with the new inputs (1-1, and 4-1 by warp): all 60 verified functions, 0
  different - parts 1 and 2 now also checked in real play. Windows build OK.
- Open: a run that reaches a level's end (killedByLevelClear), Yoshi, lava / poison for
  non-enemies, then turn the 14 on. Next: `dEn_c`.

## 2026-10-17 (32) - Claude (instance 1): track B - dActor_c part 2 (searches, zone checks, carry)

- `runtime/gm_d_actor.c` grows by 11 functions. 7 are switched on in `hle_funcs.txt`:
  `searchNearPlayerNormal` (fn_800647A0), `getTrgToSrcDirNormal` (fn_80064A40),
  `HasamareBgCheck` (fn_80065110, squashed-between-walls test), `areaCullCheck`
  (`outOfZone`), `ActorScrOutCheck` (`checkZoneBoundaries`), `checkCarried` (fn_80065FC0) and
  `slideComboSE` (fn_80065B80).
- 4 more are written but left off, because no test run reaches them, so they are unverified:
  the loop-stage variants `searchNearPlayerLoop` (fn_80064880) and `getTrgToSrcDirLoop`
  (fn_80064A50), `killActor` (fn_800656C0) and `setEatGlupDown` (`_vf90`). Turn them on once a
  run that reaches them (a looping stage, Yoshi eating) passes `RT_GM_VERIFY=1`.
- Verified: `RT_GM_VERIFY=1` with input set P2 (1-1, running and jumping for ~5 min) gives 0
  differences. A/B hash to field 22000 and whole-memory compare show only the known saved-LR words
  (5 words). Temporary call counters showed all 7 enabled functions are called many times in P2.
  The Windows build is OK.
- Bugs caught while testing: a mistyped function-pointer table address (0x802FF328 instead of
  0x802EF328, which crashed at the first goomba) and a wrong effect-name address; both are fixed.
- `dActor_c` now has 34 of ~70 functions. Next: the splash effects (`_vfC8/CC/D0`), the
  fukidashi (speech-bubble) code, the eat functions, `killedByLevelClear`, `setSoftLight_*`,
  then `dEn_c`.

## 2026-10-17 (31) - Claude (instance 1): track B - dActor_c (part 1) decompiled

- New `runtime/gm_d_actor.c`: `dActor_c`, the actor that lives in a stage - constructor,
  destructor, the pre / post create / delete / execute / draw steps (execute stop masks, the
  loop position, the collider / dBc / dRc link checks, attention entry, draw stop masks, eat
  state, draw culling), getKindString, setTmpCtData, both `construct`s, setKind, the loop-dependent
  function tables (setSearchNearPlayerFunc / setGetTrgToSrcDirFunc / setLoopFunc),
  searchNearPlayer, ActorDrawCullCheck, checkAreaNo (4 or 8 players, as the module patches it),
  deleteActor, getLookatPos, the eat-scale copies, clrComboCnt, removeCc / reviveCc. 27 functions.
  Left for later: the near-player searches themselves, the area / screen culling checks, the
  fukidashi (carry prompt) code, killActor, the splash effects, and the module's three
  replacements.
- New helpers in the file: a guest call taking and returning a float (f1), and a guest stack
  frame for locals passed by address to guest functions (pushed and popped like the PowerPC
  frame).
- A bug caught on the way: the function tables' address was computed wrong (`lis r4, -0x7FD1` is
  0x802F0000, not 0x8030xxxx) - the game crashed calling garbage at the first goomba. The verifier
  didn't see it because the native setLoopFunc wrote the table directly; the A/B run would have.
  `docs/DECOMP.md` already warns about signed `addi`; the same goes for the `lis` half.
- Verified: `RT_GM_VERIFY=1` with a new input script that runs and jumps through the level
  (`RT_AUTOPRESS`: the usual start, then right + run held from 70 s with a jump every 1.3 s: deaths,
  restarts, stomps, coins - 3 200 actors created) 0 different; A/B replay with the same inputs to
  field 22 000, whole memory compared: 5 words differ, all the known saved-LR leftover
  (0x800692C4, see (28)), nothing else. Windows build OK.
- Shared files (appended): `hle_funcs.txt` (`# track B (instance 1): dActor_c`), `build.py` /
  `build_linux_clang.sh` (gm_d_actor).

## 2026-10-17 (30) - Claude (instance 1): track B - dBase_c and dBaseActor_c decompiled

- New `runtime/gm_d_base.c`: `dBase_c` (searchBaseByProfName, the pre / post steps, getKindString,
  the loader callbacks, createBase / createRoot - its constructor and destructor are the 8-player
  module's and stay guest calls) and `dBaseActor_c`, the base of every actor (constructor,
  destructor, the pre / post steps - postExecute keeps the position delta - setTmpCtData, both
  `construct`s, draw2DActorOnLyt1 / 2, posMove, calcSpeedXY / X / Y / F, calcFallSpeed,
  getCenterPos, GetProfNameActorNum). 35 functions. (Left recompiled: calcSpeed and makeMtx,
  which need paired-single loads and float arguments to guest calls.)
- Floating point: the native code uses the recompiler's own primitives (`ldfs`, `stfs`, `frsp`:
  a single-precision operation is done in double and rounded), so results are bit for bit the
  same; `RT_GM_VERIFY` compares the stored floats.
- Sources: NSMBW-Decomp's `source/dol/bases/` (cloned from GitHub; the bases weren't in the local
  reference copy). Addresses: NSMBW-Decomp's slice offsets + 0x80006780 = USA rev 2 here.
- Verified: `RT_GM_VERIFY=1` (boot to 1-1): the checkable ones (postExecute, posMove x2,
  getCenterPos, calcSpeedX / Y, calcFallSpeed, getKindString, initLoader, GetProfNameActorNum)
  0 different over 2.8 M calls; A/B replay to field 24 000 with a whole-memory compare there: the
  same 3 known saved-LR words (see (28)), nothing else. Windows build OK.
- Shared files (appended): `hle_funcs.txt` (`# track B (instance 1): dBase_c and dBaseActor_c`),
  `build.py` / `build_linux_clang.sh` (gm_d_base).
- Next (instance 1): `dActor_c` (d_actor.cpp; the module replaces three of its functions and
  patches some constants for 8 players), then `dEn_c`.

## 2026-10-17 (29) - Claude (instance 1): track B - sLib's state machines decompiled

- New `runtime/gm_s_state.c`: `sStateID_c` (constructor, destructor, isNull, isEqual,
  operator== / !=, isSameName, name, number), `sStateMethod_c` (constructor, destructor,
  initialize / execute / finalize / changeStateMethod) and `sStateMethodUsr_FI_c` (constructor
  and the four local methods: build the state holder from the factory, run it, dispose of it).
  20 functions. These run every actor's states every frame (the player, enemies, the world map).
  The per-class template parts (`sFStateMgr_c<T>`, `sFState_c<T>` ...: one copy per class in the
  binary) stay recompiled for now.
- Verified: `RT_GM_VERIFY=1` (boot to 1-1): the checkable ones (the constructors, isNull, name,
  number) 0 different over 4.5 M calls; A/B replay to field 24 000 with a whole-memory compare
  there: 3 words differ, all the known saved-LR leftover (0x800692C4, see (28)), nothing else.
  Windows build OK.
- Shared files (appended): `hle_funcs.txt` (`# track B (instance 1): sLib state machines`),
  `build.py` / `build_linux_clang.sh` (gm_s_state).
- Next (instance 1): `dBase_c` / `dBaseActor_c` / `dActor_c`.

## 2026-10-17 (28) - Claude (instance 1): track B - fBase_c and fManager_c decompiled (the framework's core)

- New `runtime/gm_f_base.c`: `fBase_c`, the base of every actor, scene and world map piece -
  constructor / destructor, `commonPack` and the create / execute / draw / delete packs with their
  pre / post steps, `connectProc` (the per-frame step that moves bases between the lists, follows
  the parent's execute / draw switches, re-sorts by priority), `deleteRequest`, the tree getters,
  `entryFrmHeap` / `entryFrmHeapNonAdjust`, `operator new` / `delete`, `runCreate`,
  `getChildProcessCreateState`, `setTmpCtData`, `fBase_make` / `createChild` / `createRoot`
  (28 functions). The layout of this game's fBase_c (it differs a little from NSMBW-Decomp's
  headers) is written at the top of the file.
- New `runtime/gm_f_manager.c`: `fManager_c::mainLoop` (the frame: delete, create, execute, draw
  lists, then the connect step), `searchBaseByID` / `ByProfName` / `ByGroupType`,
  `getSearchTableNum` (5 functions). With (27), the framework is native from the main loop down
  to each actor's own create / execute / draw (still recompiled, called through their pointers to
  member functions).
- `rt_det.c`: `RT_DET_DUMP_MEM=1` (with `RT_DET_DUMP_AT`) also writes all of MEM1 + MEM2 raw;
  new `tools/memdiff.py a.mem b.mem [x.pages]` lists the words that differ (leaving out what
  `RT_DET_HASH_LIVE` leaves out).
- Verified: `RT_GM_VERIFY=1` (boot to 1-1) - the 10 checkable ones (getters, pre steps, searches,
  getChildProcessCreateState, setTmpCtData) 0 different over 63 M calls; the rest call virtual
  functions (anything) and are checked by the A/B replay: 33 764 fields (boot, file select, world
  map, 1-1). The per-field hashes differ from field 678 on, so the whole memory was compared at
  fields 7200 and 33 000: 3 and 2 words differ, every one a return address (0x800692C4 in
  `dAttention_c::search`, 0x8006018C in `daPyMng_c::changeItemKinopioPlrNo`) in the PowerPC run
  against an older value in the native one - the game copies uninitialised locals into objects,
  and the PowerPC versions of these functions had left their saved LR in that stack slot.
  Nothing else differs after 33 000 fields of play, so the game never reads those words.
  Harmless; documented in `docs/DECOMP.md`. Windows build OK.
- Shared files (appended): `hle_funcs.txt` (two `# track B (instance 1): ...` sections),
  `build.py` / `build_linux_clang.sh` (gm_f_base, gm_f_manager).
- Next (instance 1): `sLib` state machines (`sStateMgr_c` / `sFStateMgr_c`: every actor's states),
  then `dBase_c` / `dBaseActor_c` / `dActor_c`.

## 2026-10-17 (27) - Claude (instance 1): track B - the containers under the framework decompiled; verifier fixes

- New `runtime/gm_c_list.c` (cLib, `c_line.cpp` / `c_tree.cpp`): `cLineMg_c` addTopLineNode /
  addLastLineNode / insertLineNode / removeLineNode, `cTreeNd_c` ctor / forcedClear /
  getTreeNext / getTreeNextNotChild, `cTreeMg_c` addTreeNode / removeTreeNode (10 functions).
- New `runtime/gm_f_list.c` (framework, `f_line.cpp` / `f_tree.cpp`): `fLiMgBaFuPr_c`
  insertLineNodePriority, `fLiMgBaFu_c` lineListProc, `fLiMgBa_c` searchNodeByID /
  countNodeByProfName, `fLiNdBaLink_c` clearData, `fTrMgBaFu_c` treeListProc, `fTrMgBa_c`
  searchNodeByProfName / searchNodeByGroupType (8 functions). These are the lists and the connect
  tree every base (actor, scene) lives in: tens of millions of calls in a few minutes of play
  (getTreeNext / NotChild 12 M each, searchNodeByID 44 M).
- `gm_verify.c` (instance 2's verifier, two fixes found by these functions):
  - polls an interrupt or another thread made while the decompiled version ran (a native event
    or decrementer taken at one of its `GM_LOOP()`s) were counted as its own: "3330 polls
    (PowerPC 4)" on 1 call in 16 000. `rt_core.c` now counts those (`ppc_poll_foreign`, the polls
    inside `ppc_poll`'s dispatch) and the verifier leaves them out.
  - the memory ranges were read back and restored range by range, so with overlapping ranges
    (the list's first node is also the node inserted after) the later range read already-restored
    memory: false "memory at ... differs". Now all ranges are read first, then restored.
- `rt_det.c`, `RT_DET_HASH_LIVE=1` also leaves out the SDK's private stacks (OSSwitchFiber:
  0x8039E340, 0x803A4080, 0x803CDE40, 0x803CEE40, 0x803D0620, 4 KB each): the Wii remote
  libraries' alarm handlers run there, and their frames keep the interrupted code's registers.
  `RT_DET_DUMP_AT` also lists the left-out ranges in the `.pages` file ("live lo hi"), and
  `RT_DET_WATCH` says the last poll's r1 / lr, the OS thread and the current context.
- Verified: `RT_GM_VERIFY=1` over boot, file select, world map and 1-1 (5400 frames): all 18
  with 0 differences (114 M calls), and instance 2's 67 still 0. A/B replay (`RT_GM_VERIFY=orig`
  vs decompiled, `RT_DET_HASH_LIVE=1`): 25 440 fields compared, identical except 2 single fields
  (15032, 19188) that heal at once; the one checked is one word in an nw4r g3d object holding a
  stack address (0x8043F6F0) in the PowerPC run and 0 in the native one - the game copies an
  uninitialised local, and the PowerPC searchNodeBy* had left its back-chain there. Harmless
  (documented in `docs/DECOMP.md`). Windows build OK (`python3 build.py`).
- Shared files (appended): `hle_funcs.txt` (two `# track B (instance 1): ...` sections), `build.py`
  / `build_linux_clang.sh` (gm_c_list, gm_f_list).
- Next (instance 1): `fManager_c` / `fBase_c` (the base's create / execute / draw / delete
  steps), then `sLib` state machines, the rest of `cLib`, `dBase_c` / `dBaseActor_c` / `dActor_c`.

## 2026-10-17 (26) - Claude (instance 2): track B starts - the module's save data decompiled

- Method, conventions and tests in the new `docs/DECOMP.md`; status in `docs/NATIVE_ROADMAP.md`
  ("Status, track B") and `TODO.md`.
- `runtime/gm.h`: decompiled code keeps the objects in guest memory, big-endian, and reads them
  through typed accessors (`gm_u8(self + MJ2D_SCORE)` ...); `GM_CALL` for guest functions not
  decompiled yet; `GM_LOOP()` where the PowerPC code polls (every branch back), so the
  deterministic clock doesn't move; `GM_HLE_VOID/INT(name, lo, len, ...)` entry points.
- `runtime/gm_verify.c`: `RT_GM_VERIFY=1` runs each decompiled function's PowerPC version first
  (on a copy of the registers, interrupts held off, memory put back) and compares the return
  value, the memory ranges it may change and the poll count; `RT_GM_VERIFY=orig` runs the
  PowerPC versions instead (the "before" of an A/B replay with the same binary);
  `RT_GM_SELFTEST=1` (or class tags) calls every function of a class with random arguments and
  object contents against its PowerPC version, once. Totals at exit (also on SIGTERM).
- `rt_det.c`: `RT_DET_HASH_LIVE=1` leaves the guest threads' stacks and saved contexts out of the
  state hash - what a native function legitimately changes differently (a dead stack frame).
- Decompiled (the 8-player module's versions, nsmbw-project v0.6.5):
  `dMj2dGame_c` (a save slot, all 48 functions, `gm_mj2d_game.c`), `dMj2dHeader_c` (the save
  header, all 8, `gm_mj2d_header.c`), `dSaveMng_c` (5 of 13: getSaveGame / getTempGame /
  saveGameCopy / calcCRC / loadQuickSaveData, `gm_save_mng.c`), `dInfo_c` (the 6 the module
  replaces, `gm_info.c`). 67 functions; the module is now 93 of 1318 functions native (`NATIVE_PORT.md`).
- `tools/mod_class_funcs.py <class>`: a class's module functions with recompiled names.
- Verified: self-tests of all 67 (200-400 random rounds each) with no difference; the real game
  under `RT_GM_VERIFY=1` (boot, file select, world map, 1-1, a Toad house) with no difference;
  A/B replays (`RT_GM_VERIFY=orig` vs decompiled, `RT_DET_HASH_LIVE=1`) identical field for field:
  20 584 fields with `dMj2dGame_c`, 14 560 with the header too, 18 233 with all four.
  Mutation check of the harness: a `gm_u8` for `gm_s8` and a missing `GM_LOOP()` are both
  flagged. Windows build OK (`python3 build.py`).
- Shared files (appended): `hle_funcs.txt` (four `# track B: ...` sections), `build.py` /
  `build_linux_clang.sh` (gm_verify, gm_mj2d_game, gm_mj2d_header, gm_save_mng, gm_info), and
  `rt.h` untouched (gm.h is separate).
- Open: the rest of the module (`daPyMng_c`, the NAND saves, menus, world map), then
  `dAcPy_c` / `daPlBase_c`, then camera / scroll.

## 2026-10-16 (25) - Claude (instance 1): track A6 - the hardware register emulation is deleted

- `runtime/rt_hw.c` (526 -> 96 lines) keeps only the field clock (retrace event, SI polling,
  audio / remote updates) and the GX write-gather pipe. The PI / VI / MI / DSP / AI / EXI register
  models are gone; so are the IPC registers in `rt_ios.c`, the SI registers in `rt_si.c`, the
  CP / PE register functions in `rt_gx.c`, and the hardware-interrupt path in `rt_core.c`
  (ppc_poll now only delivers native events and the decrementer).
- Any other register access is logged and reads 0; `RT_MMIO_STRICT=1` makes it fatal. Boot to
  gameplay, the menus with a GameCube pad, and four remotes connecting/leaving all run under
  strict mode with frames identical to before. Windows build OK.

## 2026-10-16 (24) - Claude (instance 1): Wii Remotes without Bluetooth - WUD native

- **WUD is native** (`runtime/rt_wiimote.c`). WUD is the layer between the SDK's WPAD and the
  Bluetooth stack; WPAD only needs "a remote connected / went away", "an input report arrived" and
  "send this output report". Those now go straight between WPAD and the remotes: the Bluetooth
  stack (BTA/BTM/L2CAP/HCI - a few hundred recompiled functions and their 1 ms timers) no longer
  runs, and the emulated Bluetooth controller (`rt_bt.c`) and its L2CAP side are gone (moved to
  `_sync/removed_by_instance1/`). Decompiled against the Twilight Princess SDK decompilation
  (zeldaret/tp, WUD.c / WPAD.c); NSMBW's WUD control block sits at 0x803A3120 (HID callbacks
  +0x6EC / +0x6F0, status +0x708).
- WPAD's own init (fn_801DF7F0) is native minus the sensor-bar GPIO write - the last hardware
  register the game touched apart from the GX write-gather pipe. Checked: memory identical to the
  SDK's code (`RT_WPADINIT_VERIFY=1`).
- Unchanged for you: the remotes themselves (keyboard as an emulated remote, real ones' reports
  passed straight through, pairing, slots, lights) - `rt_remotes.c` / `rt_plat_win.c` untouched.
- Tested headless: keyboard remote through the menus into levels; four fake real remotes register
  as players 1-4 + GameCube port, buttons arrive, a remote going away shuts its player down; save
  state test passes. **Please test real Wii Remotes on Windows** (connect, buttons, shake, lights,
  rumble, disconnect/reconnect) - this is the path they go through now.
- build.py links only the current runtime objects (a removed file's old .o no longer gets in).

## 2026-10-16 (23) - Claude (instance 1): track A - VI, SI, EXI, audio and the OS interrupt controller without hardware

Every Wii device library under the game is now native except Bluetooth/WPAD: nothing raises a
hardware interrupt any more. Completions come as native events (`rt_post_callback` /
`rt_post_interrupt` in rt_core.c) in an interrupt-like frame.

- **VI** (`runtime/rt_vi.c`): VIInit decompiled without registers; the retrace "interrupt" is a
  native event every field (pre/post-retrace callbacks, VIWaitForRetrace's queue, VIFlush'ed
  settings). VIGetCurrentLine / VIGetNextField / VIGetDTVStatus from the field clock; the AV
  encoder (I2C over GPIO) is a no-op. Checked: native VIInit leaves memory identical to the SDK's
  (`RT_VI_VERIFY=1`), apart from the interrupt handler it no longer installs.
- **SI / GameCube pads** (`runtime/rt_si.c`): the SI library (main dol + the 8-player module's copies:
  SIGetStatus, SISetCommand, SIEnablePolling, SIDisablePolling, SIGetResponse) native; a transfer
  is answered at once, its completion (callback, queued packets, type re-probe) is an event.
- **EXI** (`runtime/rt_exi.c`, new): EXILock/Select/Imm/Dma/Sync/... talk to the RTC/SRAM chip
  directly; the EXI emulation is gone from rt_hw.c.
- **Audio** (`runtime/rt_audio.c`, new): the DSP mailbox is a native model of the DSP (ROM loader +
  AX microcode, mixing by rt_ax.c as before); __DSPHandler decompiled as a native event; the audio
  DMA is a native timer that feeds the PC's audio and runs the AI DMA callback. AIInit / DSPInit /
  __OSInitAudioSystem keep only their memory side. The DSP/AI emulation is gone from rt_hw.c.
- **OS** (`runtime/rt_os.c`, new): SetInterruptMask, __OSInterruptInit, __OSInitMemoryProtection,
  OSGetResetCode, IPCReadReg/WriteReg native. GX draw-done / token "interrupts" are native events.
- Renderer: the vertex decode + transform runs once per draw instead of once per vertex for everything
  that is the same across the draw (formats, matrices, texgen setup) - same math, bit-identical
  frames (`RT_SLOWXFORM=1` runs the old path), ~20 % less time there.
- Hardware still reached (RT_MMIO_INVENTORY): the WPAD sensor-bar GPIO (fn_801DF7F0) and the GX
  write-gather pipe (by design, for now).
- Tested headless (deterministic GL runs, GameCube pad through the menus): frames identical to the
  build before (a few title-screen frames shifted by a field), audio identical but for three tiny
  spots (max difference 54/32767); save-state and rollback tests pass (hashes match). Windows build
  OK; not tested on Windows - please check sound, GameCube pads (if you use them), and that nothing
  freezes.

## 2026-10-16 (22) - Claude (instance 1): track A3 - the disc and the IOS client without IPC hardware

- **Disc reads are native** (`runtime/rt_dvd.c`): DVDReadAbsAsyncPrio (fn_801CECC0), DVDReadPrio
  and DVDCancel copy straight from the disc image; the command block's callback runs "from an
  interrupt" through a new native event queue (`rt_post_callback` in `rt_core.c`: guest callbacks
  delivered as an external-interrupt-like frame, no hardware register involved).
- **The IOS client is native** (`runtime/rt_ios.c`): IOS_Open/Close/Read/Write/Seek/Ioctl/Ioctlv
  and their Async forms go straight to the device code (DI, FS/NAND, ES, STM, Bluetooth); async
  callbacks through the same event queue. Request blocks live at guest 0x82010000 (128 x 0x40).
  The IPC registers and IPC interrupt are no longer used after IPCCltInit (checked with
  RT_MMIO_INVENTORY); no DI registers either.
- Save states / rollback now cover 0x80000000-0x82100000 (33 MB: + the native GX register
  shadow and IOS request blocks), so old state files don't load (new build anyway).
- Tested headless (deterministic GL run: boot, title, file select, new game cutscene; saves);
  Windows build OK. Not tested: real Wii Remotes over Bluetooth on Windows - please check
  pairing/reconnect still work.

## 2026-10-16 (21) - Claude (instance 1): native port track A started - GX without emulated GX hardware

User: go ahead with docs/NATIVE_ROADMAP.md (instance 1: track A, the platform; instance 2: track
B; online play may be paused).

- **Inventory tool** - `tools/hw_inventory.py` (static: functions that load hardware addresses)
  and `RT_MMIO_INVENTORY=<file>` (runtime, rt_hw.c: every distinct guest function + hardware
  register it touched, written when the game exits). Baseline: GX touched CP/PE/PI/MI;
  OS, VI, DSP/AI, EXI, SI, DI and IPC still do.
- **GX FIFO native** (rt_gx.c "the GX FIFO, native"): `__GXFifoInit` points the GX library's
  register pointers (__cpReg/__peReg/__piReg/__memReg, r13-0x4DEC..) at plain memory
  (0x82000000+), so the library never reaches the emulated CP/PE/PI registers again. Commands
  from the write-gather pipe: linked CPU/GP FIFO -> executed directly (no copy into the guest's
  FIFO ring any more); not linked (display list recording) -> written into the CPU FIFO's buffer.
  Native/wrapped: GXSetCPUFifo, GXSetGPFifo, fn_801C32E0 (__GXSaveFifo: pointers from our
  writer), GXGetGPStatus (idle), fn_801C4B70 (GXAbortFrame), the PE token/finish interrupt
  handlers (acknowledge here). `hw_pi_fifo_*` removed; CP/PE register accesses log
  "unexpected ... (track A1)".
- Verified (Linux, GL): deterministic runs before/after, title + menus: same pictures (the
  frames between differ by a few frames of timing - the virtual clock counted the removed
  register reads); `RT_MMIO_INVENTORY`: no CP/PE/PI/MI access by GX code any more. Windows build
  clean (game\nsmbw.exe updated).
- Still emulated for GX: the write-gather pipe itself (commands are still GX command bytes; the
  GX state functions and nw4r's inline vertex writes produce them) and the token/finish
  interrupts (they go when the OS layer does, A2).

## 2026-10-16 (20) - Claude (instance 2): the boot's controller screen for keyboard players; the update screen in the real panel

User: a picture of hands holding a keyboard sideways under a red crossed circle, "do not hold your
keyboard sideways", in the style of the "Hold the Wii Remote sideways" screen. The user supplied
the drawing, then asked for:
- consistent keys;
- the console picture's skin colour and line thickness;
- hands as big as the console's, then 15% smaller twice;
- a 20% larger sign with a thinner line, allowed outside the picture box;
- then "implement it into the game, use the correct font and all".

- `runtime/rt_bootscreen.c` (new; added to `build.py` RUNTIME), docs/BOOT_SCREEN.md:
  - When player 1 is on the keyboard, the boot's controller-information layout (`N_contInfo_00`)
    shows `ui/graphics/boot/keyboard_sideways.png` instead of the remote picture. It goes into
    `P_yoko_00`'s texture as RGB5A3, and the pane is resized to the box's inside width (292
    units) divided by its 0.7 scale.
  - Its text boxes (`T_contInfo_00` / `_01`) say "Do not hold your\nkeyboard sideways." in the game's
    font.
  - The picture is 200 units tall against the box's 172, and the pane draws after the box, so the
    red sign shows over the box's frame.
  - Hooks: `boot_layout_calc` / `boot_layout_draw`, from `rt_menu.c`'s layout hooks.
  - Testing: `RT_BOOT_KEYBOARD=0/1`, `RT_BOOT_DEBUG=1`.
- `rt_gamesetup.c`: `gs_ui_mem_borrow()` lends the game-picture region (0x81870000, 576 KB) to
  the boot screen (456 KB). The first game portrait takes it back (`boot_screen_mem_lost`).
- `tools/make_boot_picture.py` (+ `tools/art/keyboard_sideways_source.png`, the user's drawing)
  makes the PNG reproducibly: the keys redrawn, the console's colours, lines grown, the window,
  the sign. Options for size, sign, sign line and line weight. Its output matches the shipped PNG.
- Then the user asked for mechanical (3D) keycaps: `--keys 3d` (default) gives darker sides and a
  lighter top set in, more on the side facing the viewer. The PNG was made again. It stays a
  plain file the game reads at start, so it can still be edited or replaced (docs/BOOT_SCREEN.md).
- **The update screen uses the real panel.** User: "round the edges of the updating screen? It
  should be using the same UI panel element yet it seems to use some sort of recreation".
  - It is now the boot's controller layout itself, which is still on screen while the boot waits
    for the update: the panel `W_contInfo_00`, rounded.
  - Over 0.3 s the picture box, the "2" button and the old text fade out, and the update's text
    fades in, in the game's font. It goes on one or two lines (broken near the middle), and the
    text moves up to y -40.
  - `rt_menu.c` `update_screen` no longer draws a sky or a panel. It draws only the spinner /
    download bar, the speed, the version (where "2" was), "1: Skip" and the failure reason, placed
    by the layout-to-overlay mapping.
  - `boot_update_frame` (from `hle_DoSceneChange`) fades the fader back in should it be black.
  - Testing: `RT_UPDATE_FADE=s`, `RT_BOOT_TRACE=1`.
- **The order** (user: "so hold wii remote, then dont hold keyboard"): the console's screen
  comes first, unchanged. 2 then gives the keyboard screen (a 0.3 s cross-fade of picture and
  text), and 2 again goes on to the update screen or the title.
  - `boot_kb_hold()` holds the boot's title request, ahead of the update hold.
  - `boot_kb_press()` is called from `rt_menu.c`'s input filter.
  - Skipped in deterministic test runs unless `RT_BOOT_KEYBOARD=1`.
- Found while doing it: `P_yoko_00` has a 0.7 scale. The first try came out at 70%.
- Merged with Claude instance 1's Discord work on the PC (rt_discord.c, rt_menu.c's
  `discord_frame`, build.py, build_linux_clang.sh, rt_core.c, version_header.py), which had changed
  there meanwhile. rt_bootscreen.c was added to both build scripts.

Verified (Linux, GL/llvmpipe):
- The console's screen, 2, the keyboard screen, 2, then the title. With an update server set,
  the update screen comes after the keyboard screen. The keyboard screen is in the game's font.
  With `RT_BOOT_KEYBOARD=0` the boot is as before.
- The update screen: checking with the spinner, then "Couldn't reach the update server" (server
  down). A local copyparty with 0.1.1 showed the download bar, speed, skip and version. The
  change between the two screens was checked frame by frame at 3 s.

## 2026-10-16 (19) - Claude (instance 1): Discord Rich Presence

User: implement Discord rich presence. Details: **docs/DISCORD.md**.

- `runtime/rt_discord.c` (new): Discord's local IPC spoken directly (no SDK): Windows named pipe
  `\\.\pipe\discord-ipc-N`, Linux socket (`$XDG_RUNTIME_DIR`, Flatpak, Snap paths). A background
  thread connects (retry every 15 s while Discord isn't running), HANDSHAKE, then SET_ACTIVITY at
  most every 4 s with the newest text; reconnects if Discord restarts. Not in save states.
- What it shows (`discord_frame()`, called at the top of `menu_draw`, looks twice a second):
  title / "Getting ready" (setup scene) / opening / "World N map" (`dScWMap_c::m_WorldNo`
  0x8042A24D) / the level (`dScStage_c::m_instance` 0x8042A1C8, +0x120C world, +0x120D stage:
  "World 1-2", "World 3 - Tower", "Airship", ...); second line Singleplayer / Multiplayer /
  Online, N players; party size from `mPlayerEntry`; time since start; large image `logo`,
  small image = player 1's character id.
- Application ID at build time: `discord_app_id.txt` -> `tools/version_header.py` ->
  `GAME_DISCORD_ID` in out/rt_version.h. **Not set yet** - without it presence is off and the log
  says so. settings.ini `discord_presence` (default 1, local: not taken from an online host).
- build.py / build_linux_clang.sh: + rt_discord. `tools/test_discord_ipc.py`: a fake Discord.

Verified (Linux, rt_discord.c with a stub harness + the fake Discord): handshake with the ID,
title -> World 3 map (1 player) -> World 3 - Tower (3 players, party 3/8) -> 3-2 -> 3-3 all
arrived in order. Windows build clean (exe deployed); not run against a real Discord yet.

## 2026-10-16 (18) - Claude (instance 2): game portraits on Game Select

User: implement `ui/graphics/gameportrait` - "this is where portraits for game selections are
stored" (it holds `nsmbw.png`, a 1000x1407 cover).

`rt_gamesetup.c` (docs/GAME_SELECT.md):
- **The card shows the picture.** Game Select's card shows `ui/graphics/gameportrait/<id>.png`
  (ids in `GAMES[]`, only `nsmbw` for now).
  - The picture is scaled to fit 512 and compressed to GX CMPR by our own DXT1 encoder:
    360x512, 90 KB.
  - It is kept in guest memory at 0x81870000-0x81900000, a free gap after the module's loader
    scratch.
  - The card's gradient pane `P_NumBase_01` gets it as its texture, with white vertex colours.
- **The card takes the picture's shape.** Its panes are narrowed before the matrices are
  computed, so the white border stays 5 units wide. The name ("NSMBW") shows only without a
  picture.
- **The select cursor follows.** `dSelectCursor_c` copies the card's size when it is set on it,
  so the copied width is corrected (both ways).
- **Everything is put back** for File Select. Without a picture the card is the old one.

Verified (Linux, GL/llvmpipe screenshots): title > Singleplayer > Game Select showed the cover
on a narrowed card with the corners around it. 2 went to File Select with three normal cards
and normal corners. 1 came back to Game Select with the cover and fitted corners again. The
fades went through cleanly.

## 2026-10-16 (17) - Claude (instance 2): rollback netcode (0 ms input delay), catching up fixed

User: "the goal was 0ms input latency, 250ms is unplayable", and some players couldn't catch up
with the host. They played the game like a video until they were dropped.

Causes in the lockstep game:
- The automatic delay took the worst of 6 pings, so one 568 ms spike made it 15 fields (250 ms).
- A client that loaded the host's game (9 MB) while the host played on caught up while drawing
  every frame, which was too slow. Then away/back cycles, a resync, and finally the drop.

Rollback (docs/ONLINE.md "Rollback"; lockstep stays as the fallback, `net_rollback = 0`):
- `rt_state.c` `rb_*`: the state of each of the last 48 fields, made of written pages only.
  - MEM1/MEM2/ARAM are watched: Windows `GetWriteWatch` (`MEM_WRITE_WATCH` in `map_fixed`),
    Linux mprotect + SIGSEGV. The locked cache and the runtime's state sections are compared.
    The stacks are copied.
  - Undo lists; going back applies them newest first, then the host fiber jumps into `rb_save`
    of that field.
  - Fields whose buttons are final keep no state (`rb_save(F, keep)`), which makes catching
    up cheap.
  - File reads into guest memory go through `rt_fread_guest`.
- `g_resim`: fields run again silently (no draws/EFB copies/audio/sfx, unpaced).
- `rt_net.c` `rb_field`, plus SPEER/SINPUT/SFRAME handling:
  - Prediction is the last known buttons; a wrong guess means a rollback.
  - The host forwards buttons at once and publishes final fields. It decides for a PC that's
    away (1.5 s), and that PC is back when its buttons are current again.
  - SINPUT resends everything not acked, in up to 4 parts. A waiting client asks for its gap
    (SFREQ).
  - Window: 20 fields. Time sync uses `det_pace_slow`, which moves the pacing's clock.
  - Catching up is silent and unpaced and logs its speed. The host waits for everyone to load.
- Chunk window 96 -> 320: joining again went 0.7 -> 2.5 MB/s at a 150 ms round trip.
- Test hooks (`RT_NET_BLIP_AT` etc.) work in both kinds of game. New: `RT_NET_LOG_USED` (the
  buttons each field ran with).

Bugs found on the way:
- Desync: buttons arriving after a field had decided its own, from `net_update`'s poll in the
  middle of the field, weren't counted as a wrong guess (`f < now` missed `f == now`).
  Found by comparing `RT_NET_LOG_USED` files; fixed with `SS.decided`.
- An away PC never came back: the host kept deciding "no buttons" up to its own field, so the
  PC's buttons were always for fields already decided.
- A 3 s drop both ways: the client waited forever on its gap (the host only resends the last
  16 fields). It now asks for the published fields.
- Time sync never slowed anything (a plain sleep that the pacing made up for).

Verified (Linux, null renderer, both pressing buttons):
- 150 ms and 300 ms round trips: identical, no waiting.
- 3 PCs: identical.
- A client's packets lost for 0.5 s and 3 s, and the network down for 3 s: identical, back.
- Quit + rejoin: caught up at 194 fields/s; identical.
- Lockstep (`net_rollback = 0`) still identical.
- Local `RT_RB_TEST`: 0 differences.

Open: never run on Windows (GetWriteWatch, a real renderer re-running fields). Buttons between
clients go through the host.

## 2026-10-16 (16) - Claude (instance 2): build_windows.bat asks for the version number

User: set the version from build_windows.bat instead of editing VERSION.

- `build.py --ask-version` (build_windows.bat passes it): before building, shows this build's
  version and, when update_url.txt's server answers, the version players have; Enter keeps it,
  `+` takes the next (last number + 1), or type one (checked: digits and dots); written to
  VERSION. `build.py --version X` sets it without asking. The publish question after the build
  is unchanged (asked when the version is higher than the server's).
- Verified with a pty: invalid input asked again, `+` 0.1.0 -> 0.1.1, typed 0.3.7, Enter kept;
  "(players have 0.2.0)" read from a local copyparty.

## 2026-10-16 (15) - Claude (instance 2): online play at high ping: 60 FPS (direct path, automatic delay)

User: 2 players, 150 ms ping: the game ran at ~20 FPS.

Cause: a client ran a field only once the host had published it (after collecting everyone's
buttons), so its own buttons went to the host and back first. The delay was 3 fields (50 ms)
against a 150 ms round trip: 3 fields per round trip = 20 FPS. Reproduced with a new lag
simulator: 22.9 FPS.

- `rt_net.c`:
  - **Direct path**: SPEER (h->c) carries the host's own buttons every field, each client's
    buttons forwarded to the others the moment the host accepts them, and the field from which
    the host uses the receiver's buttons. A client runs field F as soon as it has everyone's
    buttons (`direct_field`), else the published field. Fields run directly are checked against
    SFRAME; a difference (the host went on without us) -> RESYNC.
  - **Automatic input delay** (`auto_delay`): the worst of each client's last 6 pings; half the
    worst trip (client <-> client counts both halves) + 8 ms, in fields, + 1; 2-15.
    settings.ini `net_input_delay = 0` = automatic (new default; the old default line `= 3` with
    its old help text is rewritten by `settings_migrate_file`). The window title shows the delay.
  - **RESYNC** (c->h) / epoch: the client freezes, the host takes a state at the next field and
    sends the differing pages (the rejoin machinery without leaving); SINPUT carries an epoch so
    buttons from before don't count. A failed state check now does this instead of OUT OF SYNC
    for good (3 in a minute: OUT OF SYNC).
  - Catching up: asks for the next fields ahead of time; fields more than 496 ahead aren't stored
    (they overwrote fields still to come after a long absence - a rejoin at 150 ms never caught up).
  - Host: session PONGs keep the pings fresh. Test hooks: `RT_NET_LAG=ms[:jitter]`,
    `RT_NET_NO_DIRECT=1`, `RT_NET_BLIP_OUT_AT=field:ms`; the held packets drain on close.
- Verified (Linux, two copies, RT_NET_LAG=75 each):
  - before: 22.9 FPS; now: delay 6 (100 ms), 59.9 FPS, ~0 waiting, all fields direct, hashes
    identical (42 checks);
  - jitter 60±30: delay 7, 59.9 FPS, identical;
  - 3 PCs: identical (there both paths arrive about together);
  - forced desync: recovered (0.1 MB), identical afterwards;
  - one-way loss 2.5 s: "field 2013 differs", recovered, identical;
  - quit + rejoin: identical, caught up, direct path.
- Not done: rollback (TODO.md, with measurements).

## 2026-10-15 (14) - Claude (instance 2): copyparty login check says what's wrong

User: `login` says "that login can't write and delete in <folder> (it has: nothing)".
"nothing" only meant copyparty's `?ls` didn't answer 200 + JSON there - no detail.

- `publish_update.py`: `access()` replaces `perms()`: reads copyparty's `?ls` for the folder and
  reports who copyparty thinks you are (`acct`: "*" = the login wasn't accepted) and what you may
  do there; a folder that answers 404 (doesn't exist yet, or hidden from this login) falls back
  to its nearest parent; nothing answering like copyparty lists each address + HTTP status + the
  start of the reply. Requests send `User-Agent: nsmbw-publish/1` (proxies such as Cloudflare
  block "Python-urllib").
- Verified against a local copyparty (volume /cmayk rwmd you, /cmayk/nsmbw r:* + rwmd you, a
  second account rw only): right login -> ok; wrong password -> "doesn't accept that login";
  a missing subfolder -> parent's rights; rw-only account -> "you may only: read, write, get";
  no server -> "can't reach"; publish as the rw-only account stops before uploading.

## 2026-10-15 (13) - Claude (instance 2): build_windows.bat offers to publish; your copyparty login

User: roll publishing into build_windows.bat; log in to copyparty as the user; nobody else
should have delete.

- `build_windows.bat` runs `build.py --ask-publish`: after the build, `publish_update.py publish
  --ask` compares VERSION with the server's latest.txt; same or older: one line, nothing else;
  higher: "Publish version X as an update for players? [y/N]", then notes, pack, upload.
- Login: user name + password, sent as HTTP basic auth (copyparty accepts `user:password`,
  with or without `--usernames` - both tested); checked first with copyparty's `?ls` perms
  (must have write + delete there); saved after asking in `~/.nsmbw_upload_login` (Windows:
  DPAPI-encrypted for the user's account; untested on Windows), forgotten when it stops
  working; `publish_update.py login` / `logout`. The final check reads latest.txt with no login
  (as players do).
- Delete: only the user's account in the update folder (config in docs/UPDATES.md); an
  anonymous PUT with Replace is refused (401, tested).
- Verified (Linux, local copyparty, a pty driving the prompts): same version -> skipped; higher
  -> asked; wrong password -> asked again; right -> saved; second publish used the saved login.

## 2026-10-15 (12) - Claude (instance 2): publishing from the build; copyparty setup

User: how to make only the nsmbw folder readable on copyparty (GUI?); building doesn't publish.

- copyparty has no permissions GUI: docs/UPDATES.md has a config file with a private root and
  an `/nsmbw` volume readable by everyone (`r: *`, `rwmd: <you>`).
- `build.py --publish [--notes ...]`: after deploying, publishes the game folder. The build
  prints `version X - updates from <address>` or `updates OFF in this build (why)`.
- `publish_update.py publish` uploads to the folder in `update_url.txt` by default (`--upload`
  another, `--no-upload` none), asks for the copyparty password and the notes when not given.
- `publish_windows.bat`: double-click to publish (`publish_windows.bat keygen` for the key).
- Verified: `build.py --publish` against a local copyparty: built, deployed, packed 41 files
  (92.8 MB -> 34.4 MB zip), uploaded, latest.txt read back.

## 2026-10-15 (11) - Claude (instance 2): crash at start fixed; the update is a zipped build

User: the game crashes instantly; and a script that makes a zipped build to host for the
updater.

- Crash: `RT_VERSION` (the version macro from out/rt_version.h) is also a windows.h macro
  (`MAKEINTRESOURCE(16)`), defined after ours in rt_update.c, so on Windows the version "string"
  was the pointer 16: the first log line (`[update] version `) crashed reading address 0x10
  (seen in the user's nsmbw_log.txt; the disassembly passed `$0x10`). Renamed to
  `GAME_VERSION` / `GAME_UPDATE_URL` / `GAME_UPDATE_KEY`; rt_update.c copies them into char
  arrays (a non-string would no longer compile). Disassembly now passes the string's address.
  (The same pointer reached `rt_version()`: the Options version line and online HELLO.)
- `tools/publish_update.py publish` now makes `nsmbw-<version>.zip` (deflate 9) + `latest.txt`
  format 2: per file its SHA-256, size, offset of its data in the zip, packed size, method. The
  game (`rt_update.c`) fetches each changed file as an HTTP range of the zip, inflates it
  (stb_image's zlib decoder), checks size + SHA-256. Only `nsmbw-update 2` lists are accepted.
- copyparty overwrite: PUT needs the `Replace` header (the `?replace` query only works for
  multipart POST) - found when the second publish saved `latest.txt-<time>.txt` beside the old
  one; the script's read-back check caught it.
- Verified (Linux + local copyparty): 0.2.0 from the zip (4 files, ranges) > restart > install >
  latest; then 0.3.0 changing one file: only that file's range was fetched.

## 2026-10-15 (10) - Claude (instance 2): online ports editable; joining through NAT loopback

User: 41790 can't be forwarded (ISP-restricted port?) - make the port editable, an entry for
both the host and the joiner. Then: the joiner shows up in the host's list briefly, then gets
"No answer from the host", while Wireshark shows the host answering.

- `rt_menu.c` Online screen: **Host port** (settings.ini `net_port`; locked while hosting) and
  **Join port** (online.ini `join_port`) rows: Left/Right steps, 2 types digits. The address row
  is the address only (`ip:port` typed or kept from before: the port moves to its row).
- `rt_net.c`: cause of the second problem: a joiner only accepted packets from the exact
  address it typed. Joining the host's public IP from the same network (or the same PC), the
  router delivers the HELLO but the host's answer comes back from its LAN address - dropped,
  so the joiner timed out and the host dropped the player 5 s later. HELLO now carries a nonce
  and WELCOME echoes it; a WELCOME with our nonce from another address makes that the host's
  address. Other foreign packets are logged once.
- Linux test hooks: `RT_MENU_ONLINE=1`, `RT_TYPE="sec:text"`.
- Verified: reproduced (join 127.0.0.2, host answers from 127.0.0.1: "joined", "left (no answer
  for 5 s)", "No answer from the host"); fixed: connected, the online game started and a
  rejoin through 127.0.0.2 loaded (fields identical to the host's: 24 hashes); a normal join
  still works; the port rows (frames checked): host 41790 -> 41792 with Right, join port 41789
  with Left, typed 5000 + Enter -> online.ini.

## 2026-10-15 (9) - Claude (instance 2): updates from the author's server

User: when the game starts it calls the user's server (copyparty) and downloads an update if
there is one. Boot order: safety warning > hold the Wii Remote sideways > **update screen** >
title; the screen shows a spinner while it checks, then a download bar.

- `runtime/rt_update.c` (new): background check at start (WinHTTP; curl on Linux), signed
  update list `latest.txt` (Ed25519, key built in), files by SHA-256 (`files/<hash>`), only
  changed files downloaded to `update/files/`, hash-checked; install = rename the running exe to
  `.old` + new exe in its place, the other files at the next start before anything opens them
  (`update_install_pending`), `.old` cleanup. Protected: disc/, nand/, online/, update/,
  settings.ini, wiimotes.ini, online.ini, profiles.json, update.ini.
- `runtime/rt_crypto.c` (new): SHA-256, SHA-512, Ed25519 verify (TweetNaCl's).
- `rt_lyt.c`: the boot's request for the title waits while `update_boot_hold()` says so.
  `rt_menu.c`: the update screen (boot-screen look: pale sky, striped panel, the game's font
  loaded at boot), 1/B skips a download; the version under the Options panel.
- `rt_net.c`: HELLO's build field is the game version; the host refuses a different one.
- `VERSION` (0.1.0), `tools/version_header.py` (out/rt_version.h: version, `update_url.txt`,
  `update_key.pub`), `tools/publish_update.py` (keygen / publish / upload to copyparty, refuses a
  version that isn't higher), `update_files.txt` (what is published). build.py: rt_crypto,
  rt_update, -lwinhttp. settings.ini: `update_check`.
- Verified on Linux against a local copyparty: download > restart > install > "latest" > title;
  skip mid-download; unreachable server; tampered list; protected path; damaged file; online
  version mismatch refused (same version still joins); Ed25519 vs RFC 8032 + 119 cases.
- Not yet: any Windows run of it. Not set yet: the user's server address and key.

## 2026-10-15 (8) - Claude (instance 2): title screen: staying in our menus no longer kills the players

User: staying in a title menu for a while, the running characters die and the title restarts.
Cause: the title is a real course and its course timer kept running while our menus (list,
Options, Who's playing?, Online) were up; after ~11 minutes "time up" killed everyone and the
title started over (reproduced headless: `dCourseTimeUp_c` after the list was left open).

- `rt_menu.c`: while our menus hold the title (camera not following), the course timer
  (`dStageTimer_c::m_instance` 0x8042A070, +4 mTimeValue) is held at its value; it runs again
  when the players are back. The parked players (off screen, right) are also held at their
  height, so a pit under them can't kill them either.
- `rt_det.c`: `RT_DET_UNPACED=1` (testing): deterministic runs as fast as they go.
- Verified: list left open for 59,400 frames (16.5 min of game time, unpaced) - no time up, no
  restart (before: time up at ~11 min).

## 2026-10-15 (7) - Claude (instance 2): player profiles, step 1

User: shift player data from the characters to player profiles; begin with profiles. Local for
now (a central user database maybe later); a unique ID per username, used later in multiplayer
saves for lives / coins / power-ups; profiles picked per controller on a new menu before the
online menu; contents: global + per-save stats, a 4-letter username shown only in multiplayer,
a preferred character preselected unless someone else got it first.

- `runtime/rt_profiles.c` (new): profiles.json (profiles + controller -> profile), IDs,
  create / edit, per-slot choice. docs/PROFILES.md.
- `rt_menu.c`: **Who's playing?** after Multiplayer (before Local / Online), a row per
  controller driven by that controller; new profile: username + preferred character.
- `rt_chars.c`: per-slot username / preferred character tables (save state); the character
  select preselects the preferred character when free. `rt_remotes.c`: `remotes_slot_raw`.
- `rt_net.c`: HELLO carries each joining player's username + preferred character; the host
  puts them into its game.
- build.py / build_linux_clang.sh: rt_profiles.
- Verified on Linux (deterministic, keyboard): profile created and remembered, preferred
  character preselected; online start still in sync. Stats are stored but not counted yet.

## 2026-10-15 (6) - Claude (instance 2): online menus, start at the character select, players can drop out and rejoin

User: Start the online game should take everyone to the character select; the host chooses the
game and save file first; no Online on the title list - press 2 > Singleplayer / Multiplayer /
Options, Multiplayer > Local / Online. Also: one player closing their game kicked everyone out -
it should try to reconnect before giving up.

- `rt_menu.c`: two-layer list (Local / Online under Multiplayer); the Online screen's host row
  "Choose the game and save file" continues into the multiplayer setup screens; at the
  character select a panel (players in, "2: Start the online game") starts it. The title's
  "back at the title" reset now waits a second (it fired while the game was still leaving the
  title and turned the multiplayer start into singleplayer). A notice shows why an online game
  ended. `rt_gamesetup.c`: `gs_char_select_ready`. `rt_remotes.c`: `remotes_local_slot`.
- `rt_net.c`: player map from the slots already in the host's game; away players (1.5 s)
  don't stall the others; gone players (BYE) can join again into the running game (a fresh
  state of the game, catch-up through the host's field history, SFREQ); clients wait 30 s for a
  lost host ("reconnecting"); only the host ends the game for everyone. `g_det_fast`: unpaced
  while catching up (`rt_core.c` det_pace). Test hooks RT_NET_QUIT_AT, RT_NET_BLIP_AT,
  RT_NET_ONLINE_SETUP.
- Verified on Linux, two/three copies over 127.0.0.1 (docs/ONLINE.md "Testing"). Windows build
  clean; still not run there.

## 2026-10-15 (5) - Claude (instance 2): save states; the online game starts in place (no restart)

User: Start the online game restarted every copy (the logs showed the restart worked, but it
looked like a crash and put everyone back at the boot screens); asked for no restart: the host's
running game is sent to everyone.

- **Save states** (`runtime/rt_state.c` new, docs/SAVE_STATES.md): fixed addresses for guest
  memory (0x500000000000) and an arena (ARAM + one stack slot per guest thread,
  0x600000000000); our own fibers (asm, SysV + Win64 with TEB stack bounds) replace Windows
  fibers / ucontext; the guest main thread runs on a fiber; guest thread records are a static
  pool; ARAM moved to the arena. State = MEM1 + the mod area up to 0x82000000, MEM2, locked
  cache, ARAM, the state sections (`RT_STATE_FILE` on 18 runtime files, `RT_STATE` /
  `RT_LOCAL` single variables), the fiber stacks. `rt_snap_take` / `rt_snap_load`.
  rt_ios: FILE*s are per process (reopened by open id). rt_remotes: GC port timing + menu
  buttons in the state. rt_det: hash covers 32 MB of MEM1 now (the mod area).
- Builds: the runtime needs clang (`#pragma clang section`); build.py links at a fixed base
  without ASLR, `-fno-stack-protector`, adds rt_state; the Linux test build uses clang for the
  runtime, `-fno-stack-protector -fcf-protection=none`, non-PIE.
- **Online game in place** (`rt_net.c` rewritten from "online game" down, docs/ONLINE.md):
  files -> READY -> the host takes S0 at a field (`rt_det_enable` first) -> SNAP -> each
  client freezes, keeps a state of its own game, fetches S0's page hashes, asks for the pages
  that differ (WANT), fetches them (PAGES, LZ-compressed), checks every page and loads S0.
  No restart, no session.ini / NSMBW_ONLINE any more. Ending: everyone loads their own game's
  state back. Window title shows loading progress.
- `rt_core.c`: `rt_det_enable` (virtual clock from now on, no jump), `rt_settings_reload`,
  `det_pace_reset`; RT_POLL_LOG / RT_DEC_LOG debug logs. `rt_det.c`: `RT_SNAP_TEST`,
  `RT_SNAP_SAVE`, `RT_SNAP_LOAD`; calls `net_snap_point`.
- Verified on Linux: in-process state replay identical for 1000 fields; a state written by one
  copy and loaded by another identical for 1758 fields; online start in place over 127.0.0.1
  (client needed 0.2 MB of 117 MB), both games identical for 4,198 fields; leaving brings both
  back to their own games. Windows build clean (sections rtd / rtb / rtl present, base
  0x140000000, no dynamic base) - not run on Windows yet: the fibers / TEB handling there are
  new and untested.

## 2026-10-15 (4) - Claude (instance 2): online game - one session folder per copy

User: the game "crashes" on Start the online game. Their log: host and client were two copies
in the same game folder (join = localhost). Both wrote `online/session.ini`; the host's copy was
written last, so both copies restarted as the host - the second one couldn't open the port
("the host's port is in use"), ended the session and restarted normally, while the first sat
waiting for a player that never came (no new frames: looks frozen). Both copies also wrote the
same nsmbw_log.txt, which hid what happened.

- `rt_net.c`: sessions live in `online/<name>/` (`host`, `p1`, ...), chosen by
  `NSMBW_ONLINE=<name>` that the restart puts in the new copy's environment (`_putenv_s` /
  `setenv`); a normal start is never in a session (a stale session.ini can't hijack it). Why a
  session ended shows on the Online screen after the restart (`online/last_message.txt`).
  `rt_session_dir()`; `rt_core.c` reads the session's settings.ini from there.
- `rt_plat_win.c`: a session's log is `online/<name>/nsmbw_log.txt`; `plat_title_note`: the
  window title says "Online (host)" / "Online" / "Online: waiting for the other players (N s)" /
  "Online: OUT OF SYNC" (Linux: logged).
- Verified: two copies in one folder (Linux, `localhost`): lobby -> both restart into their own
  session -> identical over 2102 fields. Windows build clean. No real crash was found in the
  log (the copy that would have shown one had its log overwritten); if it still crashes, the
  session's own log now keeps it.

## 2026-10-15 (3) - Claude (instance 2): deterministic mode; online game (lockstep)

User: go with rollback; first the lockstep session. Also asked to note in TODO: smoother online
flow, host-decided settings, several local players per PC, the 4:3 overhaul (more playfield
vertically, not zoom), and an update check at start (download a newer version from the user's
server).

- **Deterministic mode** (`rt_det.c` new, `rt_core.c`, `rt_hw.c`, `rt_gxrender.c`): virtual
  clock for everything the game can see (`rt_emu_ns`), inputs latched per video field, a
  state hash without the renderer's writes; testing env vars in `rt_det.c` / docs/ONLINE.md.
  Verified identical runs (null, ~4000 fields, with random host delays) and GL vs GL; null vs GL
  drifts (TODO).
- **Online game** (`rt_net.c`): host offers (session id, delay, clock, player map, files),
  clients download + verify, READY / GO, everyone restarts into `online/session.ini`. In the
  session: lockstep through the host (SINPUT / SFRAME, input delay `net_input_delay` = 3),
  SHASH every 120 fields + OUT OF SYNC, 10 s timeout / BYE ends it (restart). Details in
  docs/ONLINE.md.
- `rt_nand_root()` (`rt_ios.c`, `rt_mod.c`, `rt_core.c`): the session plays on
  `<game>/online/nand`. `rt_core.c` settings: the host's in a session, except display / sound /
  network keys (`setting_is_local`).
- `rt_remotes.c`: in a session the game's players are the session's (emulated remotes / GC
  ports with the agreed buttons); local remotes are pumped for their buttons + shake;
  `remotes_local_buttons(0)` falls back to the keyboard when nothing is set up.
- `rt_menu.c`: Online screen gets **Start the online game** (host) and, in a session, only
  **Leave the online game**. `rt_plat_win.c`: closing the window sends BYE (`net_shutdown`).
- `build.py` / `build_linux_clang.sh`: `rt_det`. `rt.h`: `plat_idle_wait` declared.
- Verified on Linux with two instances over 127.0.0.1 (docs/ONLINE.md "Testing"). Windows
  build clean. Not yet tried on two real PCs.
- TODO: update check / auto-update (user), session follow-ups.

## 2026-10-15 (2) - Claude (instance 2): online play, phase 1 (connection)

User: begin online multiplayer - direct IP, the whole session, host-authoritative with
client-side prediction / reconciliation / snapshot interpolation (asked mid-way whether there's
a more efficient way to minimise input lag and visual errors: answered - rollback; pending the
user's choice before phase 2).

- `runtime/rt_net.c` (new): UDP sockets (Winsock / BSD, non-blocking, polled from
  remotes_update), HELLO / WELCOME / REJECT / INPUT (8 frames redundant) / STATE / PING / PONG /
  BYE, jitter-buffered input playback on the host, timeouts. `build.py` links ws2_32.
- `rt_remotes.c`: slot kind A_NET (online player): buttons from rt_net, counts as in use
  (emulated remote / GC port), can't be reassigned in Controls; `remotes_local_players` /
  `remotes_local_buttons` (what a client sends); `remotes_slot_emulated` replaces the keyboard
  test in `rt_wiimote.c`.
- `rt_menu.c`: title list gets **Online** (Singleplayer / Multiplayer / Online / Options); Online
  screen (host / join with a typed address / leave, status, players + ping). `rt_plat_win.c`:
  WM_CHAR queue (`plat_text_char`).
- Docs: `docs/ONLINE.md`. Verified: loopback host + client (details there). Windows build clean.

## 2026-10-15 - Claude (instance 2): Wii Remote slots by connection; SMB1 Mario's abilities, goal pole, vines, sheets, sounds

User: forget the remotes' positions (keep their IDs; a connecting remote takes the next free
slot). SMB1 Mario: remove sliding on slopes, crouching while small, carrying, riding Yoshi (+ a
Yoshi turned into SMB1 Mario); goal pole (animation, offset, drawn over the pole, SMB1 slide
speed and logic, walk to the castle and vanish, past the other players' poses); vines (left /
right only, broken sprites); stray pixels in the swim loop; no particles (water, map); big
Mario sheet; sound effects (ui/retro/mario/sfx) only for SMB1 Mario's actions.

- **Remotes** (`rt_remotes.c`): assignments are for the session; a remote that connects takes
  the lowest slot without the keyboard or another remote and frees it when it disconnects.
  `wiimotes.ini` keeps `keyboard = N` and `known = <address>` (older `slotN = ...` files are
  converted). Controls' Left/Right still moves things for the session; a remote set to None sits
  out until it disconnects. Verified headless (fake remotes).
- **SMB1 Mario** (`rt_retro.c`, details in `docs/RETRO_MARIO.md` items 7-12): changeState
  refusals (Slip, small Crouch/SitJump, LiftUp, RideYoshi), spinLiftUp and Yoshi's ride-on say
  no, Yoshi models never retro; effects dropped during its update and its map smoke; goal pole
  script from the disassembly; vines held left/right of the vine; sheet frames in their own
  texture cells (no neighbour slivers; empty boxes missing); super.png for big forms; 4 swim
  pictures x kick.
- **Sounds** (`rt_sfx.c`, new): WAV loader/resampler and a mixer in the audio DMA path
  (`rt_hw.c`); hooks on detail_StartSound / detail_HoldSound / startMissBGM. `build.py` now also
  deploys `.wav` files from `ui/`.
- Verified headless (Linux): crouch refused while small; jump / stomp / swim / coin / bump /
  death sounds and the NSMBW player sounds silenced (RT_SE_LOG / RT_SFX_LOG); the goal (World
  1-1 from its midway pipe): slides 1 px/frame, waits, swings, walks to the castle (x 6944) and
  vanishes - frames dumped and looked at (drawn over the pole); sheet cells dumped (swim row
  clean, big sheet's empty boxes skipped); swimming in 4-2 makes no effects. Windows build clean.
  Not verified: vines, Yoshi, carrying, map smoke with a retro map player.
- **Open: underwater bubbles** - the bubbles near SMB1 Mario after a swim stroke remain. They are
  not effects (they stay with `RT_NO_EFFECTS=1`, which drops every effect, incl. EGG::Effect::create)
  and not made by the player's own update; probably the water (AC_BG_WATER / dWaterEntryMng_c).

## 2026-10-14 (later still, 6) - Claude (instance 2): Wii Remotes switch off when the game closes

User: closing the game should cut the remotes' Bluetooth link and turn them off.

- `rt_plat_win.c` `wm_shutdown()`: on window close (before `ExitProcess`) and after a crash
  (once the crash box is closed), every Wii Remote's link is dropped with
  `DeviceIoControl(radio, IOCTL_BTH_DISCONNECT_DEVICE 0x41000C, &address, 8)` (no public API;
  DS4Windows turns its controllers off this way). A remote powers itself off when its link
  goes; it stays paired and any button reconnects it next time. Remotes: the ones we have open
  plus any other connected "Nintendo RVL-CNT-01" Windows lists, on every radio. Log:
  `[wm] closing: Wii Remote ... off -> ok/failed`. Not on Options' restart (the new copy keeps
  them). Windows build clean; not testable here.

## 2026-10-14 (later still, 5) - Claude (instance 2): pairing failed with error 1244

User: pairing now runs but always says "failed". Log: SYNC PIN -> 1244 (ERROR_NOT_AUTHENTICATED),
then the 1+2 PIN -> 1244, for two different remotes. The PC's Bluetooth address is
E8:48:B8:C8:20:00, so the SYNC PIN (address reversed) is 00 20 C8 B8 48 E8 - it **starts with a
0 byte**. `BluetoothAuthenticateDevice` takes the PIN as a WCHAR string, which ends at that 0,
so Windows gets an empty PIN. (The 1+2 PIN is simply the wrong one for a remote in SYNC mode.)

- `rt_plat_win.c`: `pair_sync()` - PIN without a 0 byte: Dolphin's text call first; otherwise
  (or if that fails) `BluetoothAuthenticateDeviceEx` with a `BluetoothRegisterForAuthenticationEx`
  callback that answers with the 6 bytes as binary (`BLUETOOTH_PIN_INFO`, length 6). That call runs
  on its own thread with a 20 s limit (an earlier version of it hung) and logs whether Windows
  asked for the PIN. The 1+2 PIN is no longer tried after SYNC (Dolphin: the wrong method makes
  Windows drop the remote). As Dolphin does, the HID service is switched on even if pairing
  failed, so the remote still works this session ("Connected ... for this session only").
- Windows build clean. Not testable here; the log lines `[wm] pairing:` show each step.

## 2026-10-14 (later still, 4) - Claude (instance 2): crash at boot (Wii Remote lock)

User's log: crash right after "[remotes] player slot ..." - access violation writing 0x24 inside
ntdll. `remotes_update` now asks `plat_wm_pair_last` (new, last entry) before anything else
on the platform side, and that entered `wm_lock` before `hid_load()` had initialised it (every
other `plat_wm_*` call loads first). Fix: `plat_wm_pair_last` calls `hid_load()` first.
Windows build clean.

## 2026-10-14 (later still, 3) - Claude (instance 2): Wii Remotes - pairing fix, fixed player slots

User: after "Remove device" in Windows, the game found the remote and said "Pairing..." but it
never paired. Wanted: remotes mapped to fixed player slots (only recognised there), a way to
move a remote to another slot, and to switch a slot between keyboard and remote so keyboard +
1-7 remotes works. Details: **`docs/WIIMOTES.md`**.

- **Pairing** (`rt_plat_win.c`): the user's log stopped at "Pairing Wii Remote ..." -
  `BluetoothAuthenticateDeviceEx` with the `BluetoothRegisterForAuthenticationEx` callback never
  returned. Now exactly Dolphin's way: `BluetoothAuthenticateDevice(NULL, radio, &info, pin, 6)`
  with the 6 PIN bytes one per WCHAR (SYNC: PC address reversed; then 1+2: the remote's own),
  then `BluetoothEnumerateInstalledServices` and `BluetoothSetServiceState(HID)`. Before
  looking, remembered remotes that are neither connected nor authenticated are removed (Windows
  can't use them). Inquiry `cTimeoutMultiplier` 2. **Not tested on hardware** (none here).
- **Player slots** (`rt_remotes.c` rewritten): each slot holds the keyboard, a remote (by
  address) or nothing - `wiimotes.ini`: `slotN = keyboard | <address> | none`, plus
  `known = <address>` for remotes with no slot now. A remote plays only in its own slot; a
  connected remote with no slot is not used (no lights; the Controls screen says so). A remote
  just paired from Controls takes the first free slot (`plat_wm_pair_last`). The keyboard is in
  exactly one slot (slot 1 by default / for old ini files); it can't be set to none, only moved.
  While slot 1 has nothing connected, the keyboard drives player 1 too (the game's own menus
  listen to player 1). Our menus read player 1's device + the keyboard; the game gets each
  slot's own buttons (`remotes_game_buttons`; `rt_wiimote.c` uses it for real and emulated
  remotes; GC ports 5-8 take the keyboard too). Emulated remote 1-3 connects while the keyboard
  is in its slot.
- **Controls screen** (`rt_menu.c`): rows "Player N | lights | < Keyboard / Wii Remote addr /
  None > | Connected / Not connected"; Left/Right cycles a slot through None, Keyboard and every
  known remote (sorted by address, so the order doesn't change as they move) - taking one from
  another slot swaps the two; replacing the keyboard moves it to the first empty slot. 2 =
  Forget on a remote's slot. Line for connected remotes without a slot.
- Verified headless (fake remotes): defaults (keyboard slot 1, remotes unassigned, no lights);
  a "paired" remote (`RT_FAKE_WM_PAIRED`) takes slot 2; keyboard in slot 3 with remotes in 1, 2,
  5, 6 -> players CHAN_0, CHAN_1, CHAN_2 (keyboard), CHAN_GC_0, CHAN_GC_1; keyboard presses go
  to slot 2 only (`RT_BTN_TRACE`), the title's "2" still reaches player 1; cycling/swapping in
  the Controls screen (dump checked). Windows build clean.
- New test switches: `RT_FAKE_WM_PAIRED="frame:remote,..."`, `RT_BTN_TRACE=1`.

## 2026-10-14 (later still, 2) - Claude (instance 2): Wii Remotes - pairing for good, up to 8

User: real remotes paired in Windows had to be paired again every session. Wanted: a pairing
dialog in the game, pairing once (the remote recognises the game after a reboot and reconnects
at once), and 8 remotes; lights for players 5-8 as combinations (my pick: 1100 0110 0011 1001).
Full description: **`docs/WIIMOTES.md`**.

- **Pairing** (`rt_plat_win.c`, Windows Bluetooth API from bthprops.cpl at runtime): Options >
  Controls > "Pair Wii Remotes" looks for remotes in pairing mode; SYNC button -> PIN = the PC's
  address reversed (binary, via `BluetoothRegisterForAuthenticationEx` callback), so the remote
  stores the PC and reconnects by itself with any button; 1+2 -> guest pairing (remote's own
  address), session only. Stale pairings are removed first; the HID service is switched on.
- **8 remotes on Windows**: HID scanner every 2 s, per-device reader/writer threads, address from
  the HID serial string. New platform API `plat_wm_*` (rt.h) replaces `plat_wiimote_*`.
- **`rt_remotes.c` (new)**: 8 slots, remembered by address in `wiimotes.ini`; slots 1-4 = the
  game's Wii Remotes, 5-8 = GameCube ports; player lights (LED reports to remotes 1-4 get them
  put in); GC translation of buttons + accelerometer shake.
- **`rt_wiimote.c` rewritten for 4 remotes** (handles 0x100-0x103, per-remote L2CAP/HID state and
  passthrough). Remote 0 always (keyboard); 1-3 only while a real remote is in their slot, then
  disconnect (HCI Disconnection Complete, reason 0x13) when it leaves. They connect one at a time
  in slot order (the module numbers players in the order their controllers appear).
- **SYSCONF BT.DINF**: 4 registered + active remotes (patched at boot by `rt_ios.c`; `make_nand.py`).
- **`rt_si.c` (new)**: the serial interface with 4 GameCube controller ports (type, origin, poll,
  per-field polling, interrupts). `hle_SITransfer`: a port's first transfer counted the delay from
  time 0, but the system time is negative early here (0x800030D8 = -1) -> ~70 s wait; fixed.
  The module's GC mapping was measured (docs). GC ports appear after the Wii Remotes, in order.
- `rt_menu.c`: Controls screen redone: 8 player rows (lights, Connected / Not connected,
  address), Pair / Stop Pairing with the pairing status, 2 on a row = Forget (confirm), keyboard
  keys in one line. `menu_owns_input()`: players 2-8 get no buttons while our menus / the title
  are up.
- Test switches: `RT_FAKE_WM`, `RT_FAKE_WM_SCRIPT`, `RT_FAKE_WM_GONE`, `RT_GC_TEST`,
  `RT_CONTROLS_AT` (docs).

Verified headless (fake remotes): 8 remotes -> players 1-8 in slot order, lights right, leaving
remotes shut down; multiplayer select: players 2, 5, 6 join and choose; singleplayer unchanged;
Controls screen screenshot. **Not verified: real Bluetooth pairing / real remotes (no hardware
here)** - the user's test decides; logs: `[wm] pairing: ...`, `[wm] Wii Remote ... connected`,
`[remotes] ... -> slot n`.

---

## 2026-10-14 (later still) - Claude (instance 2): singleplayer character select - taking a choice back

User: once a character was chosen, the player couldn't drop out: a Back button appeared next to
Start Game and it went to the previous menu. Wanted: no Back button, the "Back 1" label instead,
Start Game centred and only there once a character is chosen; 1 after choosing takes the
character back, 1 again goes to the previous menu. Multiplayer is unchanged (Start Game / Back).

`runtime/rt_gamesetup.c` (singleplayer, setup scene only):
- `hle_mod_fn_2_343F0` (new, dNumberOfPeopleChange_c::executeState_ButtonSelect): the cursor
  stays on Start Game (left/right masked for the module's code). 1 (`dGameCom::chkCancelButton`)
  takes the choice back: the button animations (groups 2-7: inYesNoButtons yes/no/guide,
  onYesNoButtons) are reset to their first frame (`resetAnim`, 0x800C93D0), what the button
  phase hid comes back (indicator panes +0x21C/+0x220, 2D players +0x266, np +0x688 -
  remembered when NowEntrantRecruit hands over), the cards' exit flags clear, the card does
  what 1 on a decided card does (PlayerDisp: back SE, enter count - 1, state PlayerExitWait
  0x80990D80) and the select goes back to NowEntrantRecruit (0x809945B0). The next 1 there is
  the existing "back to File Select".
- `hle_fn_2_2DF0` (new, rel dCharacterChangeSelectBase_c::executeState_SelectStartWait - the
  "Join" wait after a drop): that card comes straight back (ButtonExitAnimeEndWait 0x80990AC0,
  what 2 starts there).
- `rt_chars.c` `chars_keep_choice(slot)`: readyContents (wrapped) puts the card back on the
  character that was taken back (the module's readyContents resets the cursor to the slot's
  default, Mario).
- Layout (`gs_layout_calc` / `gs_layout_draw`): P_noBase_00 hidden; P_yesBase_00 moved to x 0
  (centre) and hidden until the character is chosen; N_back ("Back 1") kept visible during the
  button phase - the guide group's inYesNoButtons animation squashes it (scale y 0), so its scale
  / alpha are set before CalculateMtx.
- Test switch: `RT_SELECT_SCRIPT` takes `1` (button 1).

Verified (GL, headless): choose Luigi -> Start Game alone in the middle, "Back 1" shown -> 1:
the figure leaves, the card comes back on Luigi, no Start Game -> choose again -> 1 -> 1: File
Select. The card passes briefly through the module's "Drop" / "Join" indicator while it returns.
**game\nsmbw.exe not replaced**: too big for the bridge (~59 MB, 30 MB limit) and the PC shell
can't mount the folder - the user rebuilds.

---

## 2026-10-14 (late night) - Claude (instance 2): Retro Mario - no 3D model anywhere

User: "in a lot of areas he uses the regular mario model, this should never happen - all
instances of the NSMBW mario model should be replaced with the plane of mario's graphic". Rules:
world map - the plane faces only left or right, keeping the last left/right while moving up or
down; character select - left or right by the player's input, no spinning like the 3D models.
Also (process): **always replace game\nsmbw.exe directly** (no update zip); if it can't be
written (in use / permissions), say so and the user rebuilds. This time it could not be: the
bridge moves files up to 30 MB (nsmbw.exe is ~59 MB) and the PC shell couldn't mount the folder
to unpack a zip there - sources were deployed, the user rebuilds (`.xfer\nsmbw_exe.zip` holds the
built exe zipped, as a fallback).

- Levels already drew the sprite (dAcPy_c::draw). Everything else - the world map player, the
  character select figure, anything else - draws player models through `dPyMdlMng_c::draw`,
  now hooked (`draw__11dPyMdlMng_cFv`; `__dt__11dPyMdlMng_cFv` drops the per-model draw proc
  with the model). Survey (who draws models): levels `fn_80145A60` (player number in model
  +0x150, scene type +0x180 = 0); select figures `fn_2_157E30` / `DoSpecialDrawing1` (scene 2,
  +0x150 = player type); world map `fn_2_195320` (scene 1, +0x150 = player type).
- A retro model: the slot whose `mPlayerType` is that type plays SMB1. It is drawn as the sprite
  quad, built in view space (always faces the camera), at the model matrix's position, as big
  as the model (matrix scale / the model's level scale at 0x80370DA8). Form from
  `mPlayerMode[type]`. Picture: walk cycle when it moves, jump when it rises/falls, else stand.
- Facing: select - `chars_select_facing(slot)` (rt_chars.c: the last left/right the slot pressed,
  polled while the figure shows, plus SelectWait's card moves); elsewhere - the model's forward
  in view space (|x| > 0.35 switches, else kept: up/down keeps the last left/right).
- rt_retro.c: the quad drawing is now `sprite_draw()` (shared by the level and model procs).

Verified (GL, headless): select -> Retro Mario -> the figure that jumps onto the card is the
sprite, flips with left/right; world map: the sprite stands on the 1-1 node, turns left/right with
the presses (the new save has no open path, so no walk along a path was seen); 1-1: sprite as
before. Not changed: the 2D head icons (HUD "x05", course-in, file select) are still NSMBW's.

---

## 2026-10-14 (night) - Claude (instance 2): select cards - original slide back, real cause fixed

User: the portraits were "super messed up" after the last two builds; they want the card's
original behaviour (the slide between characters), only rendered correctly - not changed.

- **Reverted** the "one portrait at a time" change of the evening entry: dispNextConPicture
  (`rt_chars.c`, `mod_fn_2_5AB0`) is the first per-side version again (each face shows its own
  character's picture, nothing hidden), and the face pinning (`chars_layout_calc`, called from
  `rt_menu.c`) is gone.
- **The real cause**: the card is clipped by the game - the select base computes the contents
  layout's m2d clip from the base layout's `N_scissorArea_00` (original rel fn_2_2170 ->
  fn_2_2810 -> fn_800C9680, rect at contents+0x100..+0x110) and fn_80007010 sets it with
  GXSetScissor. `rt_aspect.c` hle_GXSetScissor widened *every* m2d clip (caller 0x80007198) to the
  whole screen in 4:3 mode (the default), meant for the letterbox bands of the world map HUD /
  prompts - so the faces sliding past the card showed beside it. Now only a clip that spans the
  picture's width (x 0, w >= 600) is widened; the card's (e.g. 262,153 116x126) is kept.
  In 16:9 mode the clip always worked.
- `RT_DUMP_FROM=n` (Linux test build): first frame `RT_DUMP_EVERY` dumps.

Verified (GL, llvmpipe, 4:3, `RT_SELECT_SCRIPT`, dumps every 2 frames): Mario -> Luigi -> Ala Gold
-> back, the faces slide inside the card window, nothing beside it; custom portraits slide the
same way (Buckenberry -> Toadette -> Toadsworth -> Daisy -> Rosalina -> Goomba). The world map's
letterbox clip (0,63 640x330) is still widened in 4:3 (`RT_VPLOG=1` logs every m2d clip as the
game asked for it: "m2d clip (4:3, as asked)"). After deciding, the card's clip shrinks to
nothing with its animation (the game's own; the old hack had hidden that too).

---

## 2026-10-14 (evening) - Claude (instance 2): mod models + portraits, one portrait at a time, retro fixes, singleplayer state

User feedback on the previous build, all handled:

- **Character select showed two portraits** (the card's and the next one beside it). The card
  has two faces - side 1 slides the next character in during a move - and the layout has no
  mask, so whatever is beside the card shows. `rt_chars.c` dispNextConPicture: only one face
  is visible (the incoming one while moving, else the card's).
- **Models from the mods in game\mod** (zips, as downloaded): new `tools/import_char_mods.py`
  (build.py runs it when a zip there is newer than `game\mod\characters\.imported`; needs
  Pillow for the portraits - build_windows.bat installs it) extracts the brres files to
  `game\mod\characters\` and portraits to `ui\characters\`. New `runtime/rt_charmdl.c` loads
  them into guest memory (0x81C00000+, ResFile::Init + Bind like the game's loader) and hooks
  dPyMdlMng_c::construct (`mod_fn_800D6D10`: Purple Toadette's body becomes a Toad-type model),
  dPlayerMdl_c::loadResources (`fn_800D32F0`: the model / P_rcha / anim ResFiles are pointed at
  ours) and dKinopioMdl_c::setColorType (`mod_fn_800BCEE0`: texture frames). Result:
  Toadsworth = Black Toad body with the Toad addon's textures; Daisy = Orange Toad body,
  Rosalina = Purple Toadette body, both the Rosalina/Daisy mod's model with its own animations
  (its P_rcha has dress/skirt tracks but no CapPosition - Mario keeps the disc's). Roster bodies
  changed accordingly (rt_chars.c). Not covered: world-map figures, voices, HUD icons, the mods'
  Kamek code. Goomba's model needs a 9th body.
- **Portraits from the mods**: Daisy, Rosalina (that mod's select portraits), Goomba (the Goomba
  mod's), Toadette and Toadsworth (no portraits exist anywhere: their HUD icons, scaled).
- **Retro Mario**: jitter - SMB1's whole-pixel steps (1, 2, 1, 2...) judder against NSMBW's
  camera; the player now moves by the SMB1 speeds (x / 16; y + fraction / 256), same distance
  on average. Slopes / tilting floors - the old "push down 2 + |dx| every frame" clipped into
  them; on the ground NSMBW's own step now moves the player at the SMB1 speed (it follows slopes
  and moving floors like the other characters). Particles - the six dEf::createPlayerEffect
  functions do nothing for a retro player. New test switch `RT_RETRO_STAR=1` (invincible).
- **Singleplayer lives / power-up follow the save file, not the character** (multiplayer: per
  character). The save keeps them in Mario's slot (type 0); picking a character in singleplayer
  copies them to its body (initDecidedCharacter), saving copies them back (prepareSave hook,
  `mod_fn_800E1690`).

Verified headless with screenshots: one portrait while walking the cards; Toadsworth, Daisy and
Rosalina on the select (3D figure) and Rosalina in 1-1 with animations; Retro Mario running and
jumping across 1-1's slopes with smooth positions (log), no dust.

---

## 2026-10-14 (later) - Claude (instance 2): character select with the 12-character roster

User: more than 8 characters regardless of player count (12 now, more later); keep NSMBW's
cards in the select (left/right walks the list); title screen shows the first five; the extra
characters had no portraits. Details: `docs/CHARACTERS.md`.

- `runtime/rt_chars.c` (new): the roster (id, name, body = one of the 8 player types, style),
  the character each player slot picked (`chars_of_player`, `chars_is_smb1`), and the character
  select: SelectWait / calcContentsIcon / isCharacterLocked / initOption / initDecidedCharacter /
  readyContents / dispNextConPicture native or wrapped (`hle_funcs.txt`), the arrows' range
  mapped. `mOption` now runs 4 .. -7 (character = 4 - mOption); the card's icon value is
  `100 + 2 * character + taken`.
- Portraits: `ui/characters/<id>/portrait.png`, swapped into the card's Mario picture pane
  through its TexMap (material + 0x6C, pointer at material + 0x40 - found by dumping, see
  `RT_CHARDUMP=1`). Placeholders with the name: `tools/make_char_portraits.py` (never
  overwrites a painted one). Textures at 0x81A00000+; `rt_gxrender.c` texture range up to
  0x82000000.
- Bodies: only 8 types exist, so Goomba and the retro characters borrow a free one (retro
  prefers Mario's); a character is "taken" if another decided player has it or its body.
- Retro Mario (SMB1) is chosen in the select; the temporary Options row is gone (`retro_mario
  = 1` in settings.ini still forces it for every Mario - testing). `rt_retro.c` asks
  `chars_is_smb1(player)`.
- Title screen: `chars_title_players()` (from rt_title.c's resWaitProc2 wrapper) - entries for
  the first five characters only.
- build.py / build_linux_clang.sh: + rt_chars (build.py's deploy copies `ui/` with
  subfolders, so `ui/characters/` goes to game\ui too).

Verified headless with screenshots: cards walk Mario -> ... -> Retro Mario (SMB1) with the
layout's pictures for the first four and the placeholders after; arrows hide at both ends;
picking Retro Mario (SMB1) gives an SMB1-moving sprite Mario in 1-1 with retro_mario = 0;
title shows Mario, Luigi, the two Toads and Toadette.

Open: per-character lives/power-ups, more than 8 types, save format v2, models; the retro
character's card shows Mario's 3D figure after deciding.

---

## 2026-10-14 - Claude (instance 2): Retro Mario (SMB1) playable; character list planned

**Retro Mario (SMB1) works in the game.** Turn on **Options > Mario: SMB1 (retro)** (setting
`retro_mario`, applied at once): every Mario is then an NSMBW player that moves with the SMB1
physics and is drawn with the user's sprite sheet. Details, hooks and test switches:
`docs/RETRO_MARIO.md`. Files:
- `runtime/rt_retro.c` (new): the glue. Hooks the player's speed/position step
  (`fn_80056E40`), executeMain (`fn_801438A0`, collision fed back), setJump (`dAcPy_vf3FC`,
  stomps/springs), draw (`fn_80145A60`, sprite instead of model); returns "no" from the wall
  slide start (`fn_801285D0`), ground pound (`fn_801266B0`) and spin jump
  (`fn_8005E780`, except with the propeller suit).
- `runtime/smb1_physics.c/.h`: + `smb1_graphics()` (PlayerGfxHandler/AnimationControl: the
  picture per frame, incl. swim kick feet), FrameCounter/PlayerAnimTimer. Tests added to
  `tools/test_smb1_physics.c` (all pass).
- `runtime/rt_core.c` + `rt.h`: `rt_register_native(addr, fn)` - give a native function a
  guest address, so guest code can call it through a vtable (used for the sprite's draw
  proc); setting `retro_mario`.
- `runtime/rt_gxrender.c`: texture address range up to 0x81A00000 (the sprite sheets live at
  0x81900000, after the module).
- `runtime/rt_menu.c`: Options row "Mario: NSMBW / SMB1 (retro)" (window a bit taller).
- `runtime/rt_plat_linux.c`: `RT_RETRO_SCRIPT` buttons reach the game (testing).
- `ui/retro/mario/`: the user's painted `small.png` + frame positions measured from it in
  `frames.json` (row 2 holds 8 swim frames: 3 SMB1 swim pictures with and without kicking
  feet + 2 spare, then climb 1-2). `tools/make_retro_templates.py`: 8 swim frames; keeps the
  entry of a painted sheet; refreshes sheets that are still only white boxes.
- build.py / build_linux_clang.sh: + rt_retro.

Verified headless (Linux build, World 1-1, screenshots): walks, runs, jumps with the SMB1
numbers (log: x speed up to 0x28, jump arc), lands on the ground, drawn 1 tile wide with the
user's pictures, dies from walking into a Goomba (NSMBW's damage works on it).

**Character list** (user, 2026-10-13): more than 8 characters regardless of player count - 12
now, more later; first five on the title screen. Plan in `docs/CHARACTERS.md`, roster and
steps in `TODO.md`. Not started in code yet. The missing portraits for characters 5-8 in the
character select are not a port bug: the module has no portrait art for them (see
CHARACTERS.md).

Note for the other instance: the cloud workspace of this session was reset once mid-work;
everything above was rebuilt from the session log and is on the user's PC now.

---

## 2026-10-13 (retro) - Claude (instance 2): title button fix; Retro Mario started

**Title bug** (user): any button but 2 started singleplayer at once. The game's title takes
any button as "start" and our menu only caught 2. Now on the title (`T_IDLE`, and while the
title is loading) the game gets no buttons except HOME, and 2 or A open our list
(`rt_menu.c`).

**Retro Mario** - plan, decisions and known engine fields: `docs/RETRO_MARIO.md`; progress in
`TODO.md`. Done so far:
- `runtime/smb1_physics.c/.h`: SMB1's player movement, translated routine by routine from the
  disassembly the user put in `../SMB1Disassembly/SMBDIS.ASM` (original variable names,
  8-bit arithmetic, tables, quirks such as the shared X move-force byte). Engine-agnostic: the
  host feeds buttons and collision results. Compiled into the game, not used yet.
- `tools/test_smb1_physics.c`: walk/run top speed 1.5/2.5 px per frame, standing jump 66 px,
  running jump 83 px, terminal fall 4, no air friction, skid - all pass.
- Sprite sheet templates for the user to draw on: `ui/retro/mario/{small,super,fire,ice,
  propeller,penguin,mini}.png` + `frames.json` + `guide/` (`tools/make_retro_templates.py`;
  never overwrites a sheet). build.py now copies `ui/` with subfolders (not `guide/`) and keeps
  a copy in game\ui that is newer than recomp's.

---

## 2026-10-13 (last) - Claude (instance 2): menu freeze fix, author name out of the source, title players, TODO.md

New: **`TODO.md`** - shared list for the user and both Claudes (user's next items: Wii Remote
dialog for up to 8 remotes, retro Mario/Luigi, audio settings, settings in the pause menu).

### Multiplayer: 1 on the character select froze the menus
User report: Multiplayer -> file (or Free-for-All / Coin Battle) -> character select -> 1 ->
no more input. Reproduced headless: pressing 1 (or 2 on a file card) **during the 30-frame
fade-in**. Leaving asked the fader for a fade-out, but `mFaderBase_c` only starts one from
fully shown, so it was refused and the code waited for black forever with input off
(`np_exit_wait`; same trap in the scene's FadeOut state). Fixed in `rt_gamesetup.c`:
`screen_black()` re-asks for the fade-out once the fade-in is over; and game input is held
while the fader isn't fully shown (`fader_seen`, updated by the scene's state functions).
Plus, in `rt_menu.c`: a button the game didn't get when pressed (our menus had it, or it was
held during a fade) stays hidden until released (`menu_filter_buttons` wrapper) - a 1 held
past the end of the title menu's fade used to reach the game as a start press.

### The module author's name is out of the source
User request: no reference to the module's author by name in the source. Done everywhere
(code, comments, tools, docs, file names, NATIVE_PORT.md, this file), except
**`THIRD_PARTY_NOTICES.md`**, kept on purpose: the module is MPL-2.0, which requires telling
recipients of the executable where its source is - that file says it (license, source, release
address). Mechanics:
- `tools/fetch_mod.py` reads the release address from THIRD_PARTY_NOTICES.md ("- Release:"),
  keeps the zip as `mod/upstream-release.zip` (an old copy under another name is found by its
  SHA256), writes the archive as **`mod/nsmbw-8p.arc`** (served to the game as `/nsmbw-8p.arc`,
  `MOD_ARC_NAME` in rt.h) with `Info/Version.json` renamed to `{"nsmbw-pc": "v0.6.5"}` (log:
  `Project: nsmbw-pc v0.6.5`).
- `tools/link_mod.py` `rename_strings()`: the module's save file names become
  `nsmbw-save*.json` / `nsmbws.json` in linked/d_project.bin (same length or shorter, nothing
  moves), and its crash screen's issue-tracker link becomes "see nsmbw_log.txt". So the
  `save_alias` table and `ios_migrate_save_names()` in rt_ios.c are gone (the user's save was
  already migrated), and `convert_save` no longer checks for the old name.
- build.py / gen.sh run fetch_mod.py when `mod/nsmbw-8p.arc` is missing.
  Leftovers the user can delete: `mod/mkwcat-nsmbw.{zip,arc}`, `game/mod/mkwcat-nsmbw.arc`.
Tested: boots with the new archive, `Project: nsmbw-pc`, save file loads; full setup flow.
Not tested: a save being written (same file calls as before, only the names changed).

### Small ones
- **Esc no longer quits** (`rt_plat_win.c`); it still leaves fullscreen.
- **Title players dash** while running off for the menu and back in: `hle_StartAnimOrig`
  (dPyMdlBase_c::setAnm, 0x800D5DD0) and `title_anim()` in rt_menu.c - the dash animation (id 3,
  "B_dash") is started when the run starts, and the game's per-frame request for the walk
  (id 2) is dropped while running; back at their place the walk comes back on its own.
  (Their speed is fixed by the title demo, so dash input does nothing - tried.)
  `RT_ANMTRACE=1` logs their animation calls; `RT_DASHANM=4` tries the full-speed dash.
- **Title players all Super Mushroom** like the original (the module rolled a random power-up
  for the title): `hle_mod_fn_2_1B2680` in rt_title.c sets all 8 player modes to 1 after the
  module's `dScCrsin_c::executeState_resWaitProc2`. This is a wrapper around the module's code,
  not a port - `native_port_status.py` now lists such functions as *wrapped* instead of native.

---

## 2026-10-13 (late night) - Claude (instance 2): one build script that works on Windows

The user ran `build_windows.sh` on Windows and nothing happened (a .sh needs a Unix shell,
python3 and zig; double-clicked it just flashes or opens an editor). New:
- `build.py` - the whole build in Python (stdlib only): regenerate `out/` when inputs change
  (same inputs as `tools/gen.sh`, own stamp `out/.gen_stamp_py`), compile changed
  `out/recomp_*.c` and `runtime/*.c` in parallel with `python -m ziglang cc` (jobs = cores,
  limited to RAM/1.6 GB - the biggest file needs ~1.3 GB), link, deploy to `../game` exactly
  like the old script (exe written in place; `nsmbw_new.exe` if the game is running).
  Runtime objects also rebuild when a header (`runtime/*.h`, `*.inc`, `out/recomp_funcs.h`) is newer.
  `NSMBW_GAME_DIR` overrides the deploy folder (testing).
- `build_windows.bat` - double-click: finds Python (py launcher or python), installs `ziglang`
  with pip if missing, runs build.py, waits for a key.
- `build_windows.sh` now just runs `python3 build.py`. The runtime file list lives in build.py
  (RUNTIME) - add new runtime files there.
Tested on Linux: full regenerate + compile + link + deploy into an empty folder; a second run
does nothing but relink. The .bat itself could not be run here (no Windows).

---

## 2026-10-13 (night) - Claude (instance 2): no module name/version on the title screen

The module's `dEventOpeningTitle_c::create` wrote "<project> <version>" from its
`/Info/Version.json` ("<module name> v0.6.5") into the title layout's E3 version text box.
Both module functions of that class are now native in `runtime/rt_title.c` (new; added to
both build scripts) and the text stays hidden, as in the original game. The other one,
`executeState_PressButtonExitAnimeEndWait`, is unchanged in behaviour (title -> game setup).

`gcall` from rt_gamesetup.c is now shared as `rt_gcall(ctx, base, fn, nargs, ...)` (rt.h).
Tested: GL screenshots of the title (logo, Press 2, menu) show no version line; title ->
Game Select -> File Select still works.

Still showed the module's name (not on screen in normal play): the project name in the log
line `Project: ...` and in the module's crash screen (both read Version.json) - since renamed
to `nsmbw-pc`, see the entry above.

---

## 2026-10-13 (evening) - Claude (instance 2): 8-player code built in (phase 1-2), new setup menus

The user's direction: the 8-player mod is **not a separate mod** - it is part of this
codebase. Agreed approach: it is built in now, and moved to native C incrementally, one
subsystem at a time, using the recompiled module code as the reference. First subsystem: the
game setup scene, because the new menus need it. Progress table: `NATIVE_PORT.md`
(regenerate with `python3 tools/native_port_status.py`; source names come from
`tools/mod_source_names.py` -> `linked/mod_source_names.json`).

### Phase 1 - no more module branding in user-facing names
- **settings.ini keys** lost the `mod_` prefix and got plain names (`unlock_all_worlds`,
  `complete_all_levels`, `no_powerup_pause`, `infinite_lives`, `death_messages`, `fall_damage`,
  `skip_opening_movie`, `always_exit_course`, `shake_with_button`, `hide_motion_guides`,
  `yoshi_colors`, `liftable_tiles`, `bubble_swarm`, `deadly_1up`, `all_paths_open`).
  `rt_core.c`: `setting_aliases` + `settings_migrate_file()` rewrite an old settings.ini once
  (old keys still read through `rt_setting`'s alias fallback). `rt_mod.c` `mod_flags` uses them.
- **Save file**: the module's own save name (+ `-old`, `-tmp`, and a short variant) is now
  `nsmbw-save.json` (+ `nsmbw-save-old.json`, ...). (Done with a name alias in `rt_ios.c` and a
  one-time rename at that point; both replaced since by renaming the strings at link time - see
  the entry above.) Tested: an old save + settings.ini were migrated and loaded.

### Phase 2 - game setup scene native (`runtime/rt_gamesetup.c`, new)
All 9 module functions of `dScGameSetup_c` plus `dNumberOfPeopleChange_c::executeState_
NowEntrantRecruit` / `executeState_ButtonDecision`, and the game's FadeOut / FadeIn /
ConnectionCheck execute functions, are hand-written C (names in `hle_funcs.txt`, originals kept
as `orig_*`). Guest calls go through `gcall()`; state machines through the manager vtable
(+0x18 changeState, +0x28 getStateID; `state_is()` compares the state's name). Module data that
moved (8-player arrays) is addressed by `MOD_*` defines at the top of the file.

New flow (user spec), both modes:
`Title menu -> Game Select -> File Select -> character select -> game`, Back (1) the reverse
(`... -> Game Select -> title`).
- **Game Select** = the file select screen with one card (the middle one, cursor forced to 1),
  contents hidden, "NEW!!" text replaced by "NSMBW" (0.78 font scale), title "Select a Game",
  Copy/Erase and versus buttons hidden, d-pad/+/- blocked. Choosing it goes to File Select.
  **Pinned** (user): later this selects level/map packs; needs restructuring first.
- **File Select**: everything moved up 16 px (singleplayer: -70 + 16, as there are no versus
  buttons); the layout's own "Back 1" (`N_back`, was alpha 0) is shown. Back -> Game Select.
- **"Select Players" is gone**: the character select opens directly with 1 player
  (Singleplayer) or 8 (Multiplayer). `rt_menu.c`'s old workaround (auto-answer `hle_fn_2_3F000`,
  black overlay, `isAnimOn`/music hooks, the 10 s fix from the previous entry) is removed.
- **Character select**: title "Singleplayer"/"Multiplayer", the four remote icons hidden, "Add
  Wii Remote +" reads "Settings +" and opens the Controls screen (rt_menu overlay; any of
  1/B/2/A/+ closes it; still the placeholder - it will become per-player controls). 1 with
  player 1 undecided returns to File Select (before, it went back to the hidden Select Players
  screen, which answered itself again - so "1 did nothing").
- **Multiplayer**: Start Game appears once players 1 and 2 have both chosen and nobody else who
  joined is still choosing (a base still in `ConnectWait` = not joined). Joining by more players
  needs multi-controller input, which isn't there yet - the flow is ready for it.
- **Transitions**: every screen change fades out with the UI in place, the next screen is set up
  while black (file select: until its state is SelectWait, ~30 frames; character select: until
  `mCancelAllowed` and no base busy, ~35 frames), then fades in already in place. Start Game and
  Back on the character select also fade first; their exit animations play under black.
  Game input is dropped while any of this runs (`gs_filter_buttons`).

Things that were needed to make the re-open work (worth knowing for later screens):
- `dFileSelect_c` only runs while +0x2D9 is set; its GameStartWait clears it when the choice flag
  goes 0. So it is put into `StartWait` (0x80991F58) directly, then the scene's FileSelect init
  switches it on.
- The file cards (`dDateFile_c`) act on requests (+0xDD8; 5 = reset) only while active (+0xE49),
  but StartWait deactivates them first - they would never come back. `file_select_open()` does
  the reset itself (state InitialSetup 0x80991880, inactive, request 0).
- Address slip found while testing: `dRemoconMng_c::m_instance` is **0x8042A028** (r13/abs
  -24536 from 0x80430000), not 0x80429F28.

Tested headless (`RT_AUTOPRESS_FRAMES=1` - new: autopress times count game frames, so slow GL
runs behave like null-renderer runs): singleplayer title -> Game -> File -> character -> Start
Game -> world map -> level; every Back path (File->Game, character->File, File->Game->title);
multiplayer (8 bases, Settings + opens/closes Controls, P1 alone gets no Start Game, 1 undoes P1,
1 again -> File Select). Screenshots (GL, llvmpipe) checked for each screen and fade.

Open:
- Game Select is a reskin of the file select; real game/pack selection is pinned.
- Controls screen is still the placeholder (keyboard list).
- Free-for-All / Coin Battle (multiplayer file select) go to the 8-player character select;
  not tested beyond that.
- Next native ports: the rest of `dNumberOfPeopleChange_c` / `dCharacterChangeSelectBase_c`.

---

## 2026-10-13 (later) - Claude (instance 2): singleplayer start no longer waits ~10 s

**Symptom.** After picking a file in singleplayer, the screen stayed black for 10-20 s before
the character select appeared (input ignored meanwhile).

**Cause** (`rt_menu.c`, not the hang fix - the previous build's log shows the same wait).
Singleplayer skips the "Select Players" screen: `hle_fn_2_3F000` answers it with 1 player while
`menu_draw` keeps the screen black and `menu_filter_buttons` swallows input "until done". But
nothing ever marked it done except the 600-frame safety timeout, so every singleplayer start
waited 10 s (plus however long you took to notice).

**Fix.** `hle_fn_2_3F000` records `sp_answered_frame`; the menu filter ends the hold as soon as
the hidden layout (kind 4, tracked in `sp_kind4_frame`) is no longer drawn, or 30 frames after
the answer at most. The 600-frame timeout stays as a fallback and now logs
`singleplayer: gave up waiting for Select Players`; the normal path logs
`singleplayer: character select after N frames`. Headless test (RT_AUTOPRESS driving title ->
singleplayer -> file -> character -> map): N = 38 frames (~0.6 s), and the presses after it
reached the character select and the world map.

---

## 2026-10-13 - Claude (instance 2): random freeze fixed, GPU selection, hitching

Files touched (runtime only - the generated C in `out/` and the recompiler are unchanged, so no
regeneration is needed; `out/objwin` objects for `recomp_*.c` stay valid):
`runtime/rt_core.c`, `rt_hw.c`, `rt_plat_win.c`, `rt_plat_linux.c`, `rt_gxrender.c`, `rt_gxgl.inc`.
A new `game/nsmbw.exe` with all of this was built (zig 0.17.0, same flags as `build_windows.sh`).

### 1. The "random hang" (game frozen, log only shows `[audio] 32000 samples/s ...`)

**Symptom.** The picture stops, the window still responds, the audio DMA keeps running (so the
`[audio]` line keeps appearing every 10 s), `[gx] frame N` lines stop. In the user's log it hit
while the world map was being created after a level (`Create: LETTER_WINDOW`, then nothing).

**Reproduced** headless on Linux (see "Test harness" below) within ~90 s at the first title
stage load. Guest thread dump at the hang:

```
thread 80359938 (main, prio 16)   OSSleepThread <- mDvd_command_c::waitDone <- mDvd_toMainRam_c::create <- dDvd::loader_c::request ...
thread 80C7F460 (mDvd, prio 15)   OSSleepThread <- fn_8016B770 (the disc command thread's loop)
every other thread                OSSleepThread / OSReceiveMessage / OSWaitCond
```
Nothing runnable, nobody left to wake the main thread: a lost wake-up.

**Root cause.** Interrupts are only delivered at poll points: every 256th loop back-edge
(`PPC_POLL` in the generated code) and our `OSEnableInterrupts`/`OSRestoreInterrupts` HLEs.
The game has two classic check-then-sleep loops that are only "almost" race free on hardware:

```c
// mDvd_command_c::waitDone (8016B4F0)          // mDvd command thread (8016B770)
while (!cmd->done)                              for (;;) {
    OSSleepThread(&mgr->doneQueue);                 OSSleepThread(&mgr->cmdQueue);
                                                    while ((cmd = mgr->first)) { remove(cmd); run(cmd); }
                                                }
```
The compiler rotated both loops so the backward branch - i.e. our poll point - sits exactly
between the check and the `OSSleepThread`. If the poll delivers an interrupt whose handler wakes
a higher-priority thread, the OS switches right there (`__OSDispatchInterrupt` ends with
`__OSReschedule`). Example for waitDone: the IPC reply for the disc read wakes the mDvd thread
(prio 15 > main's 16), which finishes the command, sets `done`, wakes the done-queue (empty - main
isn't on it yet) and goes back to sleep; main resumes after its check and sleeps forever. On a
Wii the window is a few instructions out of millions; here every interrupt that became pending
since the last poll is delivered at that one spot, so it fires every few minutes of play.
Measured with `RT_PREEMPTLOG=1`: ~18 thread switches per second happened at poll points.

**Fix (rt_core.c, "deferred preemption").** Interrupt handlers still run immediately (flags,
callbacks, wake-ups), but `take_exception` raises the guest's scheduler lock (`Reschedule`,
the counter `OSDisableScheduler` uses; r13-20352) around the handler, so the `__OSReschedule`
at its end does nothing and only `RunQueueHint` (r13-20348) stays set. The woken thread then
gets the CPU at the running thread's next own scheduling call (OSSleepThread, OSWakeupThread,
mutex, yield ...) - for the races above that is the sleep itself, which is safe. If the thread
keeps computing without making one, `maybe_force_resched` calls the guest's `__OSReschedule`
(801B50D0) from a poll point at most 1 ms after the deferral, exactly like the end of an
interrupt handler would. With the fix, thread switches at poll points went from ~18/s to 0, the
game behaves the same otherwise (scene changes, audio rate 32000/s).
`RT_NODEFER=1` turns it off for A/B tests.

If a freeze still happens, the new watchdog (below) writes a `[hang]` block to the log - send
that log; it shows what every guest thread waits on.

Considered but not done: moving `PPC_POLL` in `tools/recomp.py` to the start of the straight-
line block that ends in the back-edge. It doesn't help when the check is inside a callee (the
mDvd thread's `first` is read by `fn_8016B5B0`), and needs a full regenerate + recompile.

### 2. Hang watchdog + better hang reports

* `rt_plat_win.c`: a watchdog thread logs once per hang when no frame was presented for 8 s:
  `[hang] no new frame for 8 s ...` + every guest thread with a backtrace + CPU state, and
  `[hang] frames again` if it recovers. Read-only, the game keeps running. `NSMBW_HANGWATCH=0`
  disables it.
* `rt_core.c rt_hang_state()` (printed by `rt_dump_trace`, also on crashes and by Linux
  `RT_HANGDUMP`): current fiber, poll-frame depth, host address of the last poll point
  (`image+0x...` on Windows), guest msr/lr/r1/r3, RunQueueBits/Reschedule/RunQueueHint,
  PI interrupt status/mask, decrementer, deferred/forced preemption counts, and the mDvd command
  queue (`first`/`last`; non-zero `first` while everyone sleeps = lost command wake-up, zero =
  lost "done" wake-up). It never reads MMIO addresses (it may run on the watchdog thread).

### 3. "Doesn't use the GPU on certain PCs"

`rt_plat_win.c`:
* Exports `NvOptimusEnablement = 1` and `AmdPowerXpressRequestHighPerformance = 1` from the exe.
  Laptops with integrated + dedicated GPUs otherwise run the game on the integrated one. This is
  the most likely cause of the report. (Verified in the PE export table of the new exe.)
* Pixel format: if `ChoosePixelFormat` returns Microsoft's software format (`PFD_GENERIC_FORMAT`
  without `PFD_GENERIC_ACCELERATED`) we pick an accelerated one ourselves.
* Context: tries 3.3 core, then 3.3 compatibility, then 4.0 before giving up on
  `wglCreateContextAttribsARB` (some drivers refuse the first).
* Logs `[gl] driver: vendor | renderer | version`, and refuses "GDI Generic" / GL < 3.3 with a
  clear log line instead of failing later.
* When the software renderer is used, the window title says
  `SOFTWARE RENDERER (no OpenGL 3.3 GPU driver found - see nsmbw_log.txt)`.

Crash fix found on the way (`rt_gxgl.inc`): `ui_register_texture` called GL with no GL context
when the software renderer is active -> null function pointer crash as soon as the title screen
loaded the game font. It now returns 0 there (menus just don't draw in software mode).

### 4. Hitching / CPU load

What the user's profile + log say (RTX 4080 PC): 63 % of the game thread's time was the guest
idle loop (SelectThread spinning while it waits for the next VI/audio interrupt), 13 % reading
the clock (rdtsc in the polls), ~10 % our renderer (vertex decode/transform), 7 % GL driver,
3 % recompiled game code. Steady state is 60 fps; hitches are single long frames at scene loads
(33-150 ms of guest work, "draws 0.0") and first-time shader compiles (up to 70 ms).

Changes:
* **Sampling profiler is now off by default** (`NSMBW_PROFILE=1` turns it on). It suspended the
  game thread 1000x per second (SuspendThread/GetThreadContext); every time the sampler thread got
  descheduled while the game thread was suspended, the game stalled for a whole Windows time
  slice - a hitch generator on machines with few cores.
* **Idle sleep** (`rt_core.c idle_wait`, `rt_hw.c hw_next_event_ns`, `plat_idle_wait`): when no
  guest thread can run (current thread = NULL) and no interrupt is pending, the host thread sleeps
  until ~0.4 ms before the next timed event (VI field, audio DMA block, delayed DSP mail,
  decrementer), max 4 ms, using a high-resolution waitable timer on Windows 10+. Frees the core
  for the GL driver threads, less heat / turbo loss on laptops. `NSMBW_IDLESLEEP=0` restores
  spinning. The `[perf]` line is followed by `(of which the CPU slept X ms per frame ...)`.
* Indirect calls (`ppc_call_indirect`, every C++ virtual call) hit a 16K-entry direct-mapped
  cache before the binary search over ~40,000 functions.
* `rt_tb_now` (every poll, every OSGetTick) uses one double multiply instead of two 64-bit
  divisions.

Not done yet (ideas, roughly by value):
* Shader compile hitches: compile asynchronously with `GL_KHR_parallel_shader_compile` and skip
  (or ubershader-draw) until ready; the binary cache already removes them from the 2nd session on.
* Vertex path: `decode_vertex` re-derives the format per vertex and memsets a 180-byte struct;
  a per-draw decoder plan would roughly halve "vertex decode/transform" (5 ms/frame in the
  8-player title scene).
* Frame pacing: presentation is unsynced (swap interval 0) at the emulated 59.94 Hz, so on
  60/144 Hz monitors frames are shown unevenly; an optional vsync / present-on-host-refresh mode
  would look smoother.

### Test harness (Linux, headless) used for all of the above

```
# build (any recent clang; objects can be cached between runs)
clang -std=gnu11 -O1 -w -Iruntime -Iout -DPPC_TRACE -c out/recomp_NNN.c ...   # all 104
clang -std=gnu11 -O1 -g -w -Iruntime -Iout -DPPC_TRACE -c runtime/rt_*.c (not rt_plat_win)
clang -no-pie *.o -lm -lpthread -ldl -o nsmbw_linux
# run from a game-style folder (orig/, nand/, mod/, settings.ini, disc/)
NSMBW_RENDERER=null RT_HANGDUMP=8 ./nsmbw_linux <gamedir> <gamedir>/disc
```
New test knobs (all runtime, no rebuild):
* `NSMBW_RENDERER=null` - nothing is drawn, everything else runs at full speed (game logic,
  audio, EFB copy bookkeeping, frame counting). Lets a 2-core box run the game at 60 fps.
* `RT_POLLSTRESS=1` - every loop back-edge polls (instead of every 256th): amplifies timing races.
* `RT_PREEMPTLOG=1` - logs interrupts that switched threads at a poll point (flags the two mDvd
  race windows explicitly). With the fix this prints nothing.
* `RT_NODEFER=1` - old (racy) preemption behaviour, for comparison.
* `RT_HANGDUMP=sec` (existed) - now also prints the CPU/scheduler state block.

Note for the next session: the headless llvmpipe GL path works too (`render_scale = 1` in
settings.ini), but is ~10 fps on 2 cores, which changes timing a lot.
