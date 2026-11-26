# SMB3 port

Goal: SMB3 inside the NSMBW runtime - its graphics, enemies, objects, levels, map and game logic -
with NSMBW players (1-8, multiplayer) instead of SMB3's player. Path (user, 2026-11-21): recompile
SMB3 first for a working game early, then move it piece by piece into native NSMBW-engine code.
SMB3 power-ups become real SMB3 suits on the NSMBW players (later). First milestone: World 1-1
playable with NSMBW players.

## Now

Game Select -> **SMB3** -> File Select -> character select -> **Start Game**: SMB3 starts on the
map of the chosen file (a new file: World 1; no title, no intro) and runs the whole game,
recompiled, with its own Mario for now, and its own music and sound (nes_apu.c; the menu music
stops).

- **Files**: SMB3 has three files of its own, `<game>/smb3/file1-3.sav` (smb3_save.h); the File
  Select shows them in NSMBW's own cards, as NSMBW's (World, lives, NEW!!; Copy and Erase work on
  them) - NSMBW's save is not touched (rt_gamesetup.c: stand-in slots while it's up). A file
  holds SMB3's progress as the game keeps it between map visits (8 KB work RAM: completions, map
  objects, inventory, cards, score, coins, positions; and world, lives, map power-ups). Loading
  re-enters the map the way SMB3 does after a level (PRG030_84D7). Saved on a map square: you
  come back on it; saved walking or in a level: on the last level's square.
- **Pause menu**: + (or HOME) - Continue / Save / Save & Quit / Quit (to the title), as NSMBW's
  world map menu. SMB3's own Start pause is replaced by it.
- **Discord**: "SMB3: World N map" / "SMB3: World N".
- **Volume**: settings.ini `smb3_volume` (percent, default 100).

Controls (Wii Remote sideways, as NSMBW): d-pad, 2 jump (NES A), 1 run (NES B), + menu,
- Select. Keyboard: arrows, X, Z, Enter (menu), Shift.

Not yet: NSMBW players (the next step), player 2, online play (the
runtime's save states, which online play uses, don't hold SMB3: the 6502 runs in a coroutine).

## Prototype: NSMBW players in SMB3's 1-1 (smb3_stage.c)

Start Game for SMB3 now opens an NSMBW stage (settings.ini `smb3_stage = 0`: the recompiled game's
own screen instead). It goes through NSMBW's own setup path (players, NSMBW's file of the same
number loaded read-only for their data) and, where NSMBW would go to its world map, starts course
1-1 as an empty shell (rt_gamesetup.c, finalizeState_VoiceEndWait):
- **level**: the recompiled SMB3 runs unseen into 1-1 (760 frames, ~0.1 s); its own loader gives
  the tile map (Tile_Mem), solidity (Tile_AttrTable) and the tile pictures (Tile_Layout_TS1 with
  the level's pattern banks, PatTable_BankSel, and palette);
- **collision**: gm_bg.c's unit lookups answer SMB3's tiles - solid = NSMBW unit `hi 0x01`,
  solid on top = `hi 0x20` (values read from the course's own tiles: `SMB3_STAGE_PROBE=1`);
- **picture**: a draw proc in the stage's 3D scene (as Retro Mario's): SMB3's sky, then the
  tiles as flat quads, 1 NES pixel = 1 unit; NSMBW's camera (widescreen), players, HUD;
- the shell course's actors are not spawned (gm_d_actorcreate.c), its tiles emptied.
Placed so SMB3's start (its Player_X / Player_Y, on the first floor below) stands where the course
puts player 1, on NSMBW's 16-unit grid (NSMBW takes a tile's top from its own cells: off the grid the
players bobbed on every floor).
- **players at 80%** (3D characters: their level model scales and, after each setBcData, their
  background sensors; Retro Mario keeps SMB1's size); SMB3's tiles stay on NSMBW's 16-unit grid,
  which NSMBW's collision snaps to (so the stage is not scaled instead);
- **solid on top** as SMB3 has it: only the top tile of a stack (SMB3's big blocks are solid on
  top all the way down), only its upper 8 units, and not for a player who is rising - one jumping
  up through it finishes the jump and lands on it coming down (NSMBW's own semisolids are one-way
  by its collision; it would pull a player onto any of these it touched);
- **animated tiles**: SMB3 turns the $0800 background bank through PT2_Anim ($60 $62 $64 $66, 8
  frames each); the tiles that change keep frames 1-3 below the 256 (35 in 1-1: ? blocks, coins..);
- **blocks**: coins are collected; a new head bump hits the block above - ? blocks turn into used
  blocks, bricks bump (break when big), with SMB3's bounce; coins pop out (SMB3's coin tile);
  SMB3's coin count is kept (for its status bar);
- **items** (SMB3's sprites, from its sprite banks and palettes: ObjectGroup00_PatternSets /
  _Attributes): rise out of the block, then mushroom / 1-up walk at SMB3's 1 unit a frame and fall,
  the star bounces, the flower stays, the leaf pops up and sways down; a small player gets a
  mushroom from a flower / leaf block, as in SMB3. Touching one: mushroom Super, flower Fire,
  leaf Super (until the Raccoon suit), 1-up a life (NSMBW's rest count), star: not yet.
Testing: `SMB3_STAGE_TEST_X=column` (`SMB3_STAGE_TEST_X_ONCE=1`: the first level only) starts player 1 at an SMB3 column (left of the shell
course's camera limit the camera won't follow), `SMB3_STAGE_TRACE=1` logs the players' height,
speed and background bits each frame.
Not yet: the Raccoon suit, SMB3's status bar, enemies, the star, the end of the level; death goes
to NSMBW's world map. ROADMAP.md has the order. `SMB3_STAGE_ATLAS=file.ppm` writes the tile pictures (testing).

## Layout

```
SMB3Disassembly/
  smb3.asm, PRG/, CHR/       the disassembly: the source of everything (NESASM)
  nesasm.exe                 the assembler (Windows; elsewhere $NESASM)
  tools/
    build_smb3.py            assemble -> check against the original ROM -> recompile -> out/
    recomp6502.py            the static recompiler (6502 + MMC3 -> C)
    smb3_headless.c          runs it without the runtime, dumps frames (testing)
  port/
    smb3.h, smb3_main.c      the runtime's side: enter / input / frame / draw / leave
    smb3_game.c              native code inside SMB3 (hooks)
    smb3_stage.c, .h         prototype: SMB3's 1-1 as an NSMBW stage with NSMBW players
    hooks.txt                which SMB3 routines run native code first
    nes.h, nes_gen.h         the machine's interface; what generated code needs
    nes_cpu.c                memory map, MMC3, calls/returns, interrupts, timing, coroutine
    nes_ppu.c                the picture (scanline renderer)
    nes_apu.c                the sound (2A03: pulses, triangle, noise, DMC; 32 kHz)
    smb3_save.h              an SMB3 save file
  out/ (generated, not in git)
    smb3.nes, smb3.lst       the ROM and listing (byte-identical to SMB3 USA Rev A)
    smb3_bNN.c               the recompiled banks (30 code banks, 55k instructions)
    smb3_table.c, smb3_rom.c bank table + label names; the ROM image (data)
    smb3_hooks.h, smb3_syms.h hook prototypes; SMB3's RAM names as SMB3_<name>
```

recomp/build.py runs `tools/build_smb3.py` (skipped when nothing changed) and compiles `port/`
and `out/` with the runtime. Headless test (Linux):
`smb3_headless out/smb3.nes 900 "250:R,270:,330:U,350:,420:A,430:" shots/`

## How the recompiled code runs

- **Code vs data** comes from the assembler's listing, not from guessing; each instruction becomes
  C (a label per instruction, one function per bank, gotos within the bank).
- **Banks**: each bank is assembled for one CPU window ($A000 or $C000 swappable, $8000/$E000
  fixed). A jump to another window goes through the bank mapped there now; code whose own
  window is swapped under it (by a callee or an interrupt) continues in the new bank, as on the NES.
- **Calls**: JSR pushes its return address (the 6502 stack in RAM is the truth) and is a C call
  that expects to come back; RTS returns to the frame that waits for the pulled address. SMB3's
  tricks (DynJump pulls its return address to read a jump table; PLA PLA leaves two levels; RTS
  to a pushed address) need nothing special. Frames whose address was pulled are dropped, so the
  C stack never outgrows the 6502 one.
- **Time**: every instruction counts its cycles; at backward branches, jumps and after calls the
  code checks for events: a scanline (drawn; the MMC3 counter clocks; its IRQ draws the status
  bar), vblank (the frame is done: the coroutine yields to the runtime; then NMI).
- **Hooks** (`hooks.txt`): native code at any SMB3 label, before the original; it can leave the
  routine as its RTS would (`NES_RTS()`). The first: `Do_Title_Screen` -> what the title leaves
  for a 1-player game, so the game goes straight to the World 1 map. The NSMBW-player bridge will
  be built the same way.

## The stage (smb3_stage.c): NSMBW players in SMB3's 1-1

Start Game on an SMB3 file runs the NSMBW stage flow with NSMBW course 1-1 as the shell; its own
actors are suppressed. At load, the recompiled SMB3 runs headless to 1-1 and the stage takes
Tile_Mem, Tile_AttrTable and the pattern banks (PatTable_BankSel; the 4 frames of the animated
BG bank) into one RGB5A3 atlas. Collision is SMB3's tiles through gm_bg.c (`smb3_stage_unit`):
solid, and solid-on-top only for the top 8 units of a semisolid and never for a player moving up.
Players with 3D models are drawn at 80%. SMB3 assets keep their 2D sprites.

**Rule: SMB3 behaviour is ported from the disassembly, not imitated with NSMBW objects.** Each
piece names the routine it comes from, and keeps SMB3's units (pixels, 4.4 velocities, frame
counts). Ported so far:

- Hitting blocks: Level_DoBumpBlocks / LATP_HandleSpecialBounceTiles with SMB3's tables
  (LATP_QBlocks: what a block gives; LATR_QBlocks: what it leaves), 2 bump slots, one power-up
  slot (a new one replaces it). A bumping block is tile $F3 (solid, unseen) under its sprite.
- Block bump: ObjNorm_BounceDU (Bouncer_PUpVel, 10 frames; the item comes out at the top).
- Coin from a block: LATP_CoinCommon / CoinPUp_UpdateAndDraw (24 px above, -5 px/frame, +1 every
  4th frame; at +5 a "100" pop-up). A coin on top of a hit brick comes too (LATP_GetCoinAboveBlock).
- Bricks: small - bump; big - BrickBust (4 chunks of $4B, -6, +1 every 4th frame, the lower pair
  +2, parting 1 px a frame, flips turning) and 10 points.
- 10-coin brick: LATP_10Coin (200 frames, then it becomes a brick with one coin, then used).
- Coin/star block: a star if the player has star power (daPlBase_c::isStar), else a coin.
- Power-ups: PowerUp_DoRaise (still 16 frames, then 1 px every 3rd frame behind the block),
  Object_Move (4.4 velocities with fractions, gravity +3 to $40, floor/ceiling/wall detection),
  ObjNorm_PUpMush / PUp1UpMush (walks at $10 away from the player), ObjNorm_StarOrSuit (bounces
  at -$40), ObjNorm_FireFlower, ObjInit / ObjNorm_SuperLeaf (rise, then the sway tables).
- Getting them (ObjHit_*): mushroom - small to Super; flower - small to Super, else Fire; leaf -
  small to Super, else Raccoon (Super until the suit exists); star - NSMBW's setStar for $E0 x 2
  frames; each a 1000 pop-up; 1-up - a "1UP" pop-up that gives the life.
- Ground pound (NSMBW's, its fall: status 28): the block under the feet is hit from above, by
  SMB3's own path for that (note blocks): the block bounces down, the item comes out below
  (Y velocity $10, no rise; the leaf: Leaf_YVels / Leaf_TimerVals); a big player breaks bricks
  and falls on through.
- Raccoon suit: the leaf on a big player sets a Raccoon flag (NSMBW has no such form; the player
  stays Super); a hit to small ends it, a fire flower replaces it. Its look and motion are
  NSMB2's, whose player rig is NSMBW's bone for bone (tools/nsmb2_anims.py, run by
  build_smb3.py when ../NSMB2_RomFS - the user's own dump, git-ignored - is there; without it
  the 2D placeholder below stays):
  - body animations: 14 of NSMB2's T_* (tail swipe L/R, flutter fall, take-off, flight, P-dash,
    run, waits) converted losslessly to NSMBW CHR0 (FVS96 keys) in a brres linked in
    (out/smb3_raccoon_anm.c). They get ids past the game's animation table (entries in our
    memory where those ids land), and dPyMdlBase_c::setAnm (rt_menu.c's hle_StartAnimOrig asks
    smb3_stage_anim first) plays them from our archive; while one of ours holds, the game's own
    requests wait; for a Raccoon player the game's dash plays the Raccoon's.
  - the 3D tail: NSMB2's mr_tail (65 vertices skinned to a 5-bone chain, ETC1 texture whose
    repeat makes the stripes) with its T_tail_* animations, evaluated and skinned each frame and
    put on the hips (joint 1), drawn by the stage's own GX pass, lit simply.
  - the 3D ears: cut from NSMB2's Raccoon body (Mario's mr_tail_body; Luigi is NSMB2's Fox Luigi:
    lg_tail_body's fox ears, lg_tail's fox tail), on the head joint, coloured from the body
    texture (the near-white inner ear tinted light tan, as NSMB2's lighting shows it). (Toads keep
    the 2D ears and get the raccoon tail.)
  - placeholder (no NSMB2 dump): SMB3's own tail and ear pixels at the same tracking points.
- The P-meter (all players) and the Raccoon's abilities, SMB3's (prg008), on NSMBW's players:
  Player_PowerUpdate (run flag: the run button held on the ground at SMB3's top run speed $28;
  an arrow every 8 frames running, one off every $18 not), Player_JumpFlyFlutter (a jump at full
  P: flight time $80, -1 every 2nd frame; each jump press in the air: 16 frames rising at -$18,
  or without flight time, falling no faster than $10), Player_TailAttackAnim (the run button:
  an 18-frame swipe; Player_TailAttack_HitBlocks at 9: the block ahead at the feet + 4, a brick
  busts). SMB3's speeds are set as the speed NSMBW ends up moving at (its gravity counted).
  P-speed (PLAYER_TOPPOWERSPEED): at full P with run held the player's speed table is swapped for
  one whose dash tops out at 4.0 (NSMBW's dash 3.0 + SMB3's run-to-power step); moving at 3.5 or
  more on the ground is the P-speed state: the Raccoon's P-run animation plays, and only a jump
  out of it starts flight. A Raccoon hit: Super (gm_d_player.c's setNextPowerup asks
  smb3_stage_powerdown).
- Score pop-ups: Score_PopUp / Scores_GiveAndDraw (5 slots, counter $30, points at $2A, the rise
  slowing by Score_RiseCounterMask). 100 coins: a life.
- Status bar (prg026 StatusBar_*): SMB3's own bar, taken from the unseen SMB3 in 1-1 (name table
  rows 24-29 of $2800, their attributes, the pattern banks its IRQ maps for the bar - snapshotted
  as line 212 is drawn, nes_ppu.c `ppu_capture_at` - and the palette), drawn at the bottom of the
  screen, 48/240 of its height as in SMB3, black out to the widescreen edges and up to the
  level's last row. Its changing fields are written each frame by SMB3's rules
  (StatusBar_UpdTemplate positions): StatusBar_Fill_PowerMT (6 arrows $EF/$EE from the first
  player's P-meter, [P] $3C/$2C flashing on MaxPower_Tick bit 3), _Fill_Coins / _Fill_Lives
  (blank leading zero, lives NSMBW's rest count, capped at 99), _Fill_Score (6 digits of the score
  in tens), _Fill_Time (Level_TimerTick $28: a second every 41 frames, from the course header's
  hundreds; it stops with the game). NSMBW's HUD (dGameDisplay_c::draw) is not drawn in the stage.
  The level and the players are lifted 48 units so the bar covers nothing (the camera rests on
  the shell course's bottom).
- Platforms (smb3_stage_platforms.inc, 2026-11-25): the log / wooden platforms of prg002 in the
  same object slots - $26 rider, $27 / $37 horizontal and $28 / $38 vertical oscillating
  (Platform_Oscillate), $36 drifting left and dropping once stood on (1-4), $3C / $44 following
  the level's path tiles (WoodenPlat_* tables, reversed at the platform puller $D0, falling where
  the path ends; $44 starts once stood on - 1-6). Drawn by LogPlat_Draw's patterns from sprite
  bank $0E (their ObjectGroup_PatTableSel). The NSMBW players stand on them through NSMBW's
  RideableActorCollider (a line along the top, moved with the platform, carrying its riders),
  owned by one DUMMY_ACTOR (profile 0x2EB); its riders are SMB3's "stood on". The lines are taken
  out of NSMBW's collider list when the stage ends (the list is never cleared by the game).
- Enemies (smb3_stage_enemies.inc): the level's own object list (Level_ObjPtrOrig into bank 6),
  5 object slots, spawned as they come in at a screen edge (the NSMBW screen) and deleted off it
  (a deleted one can come back; a killed one can't). The prg000 core: Object_Move (4.4,
  gravity 3, max $40), Object_WorldDetect4 (feet / head / wall offsets of detection group 1),
  Object_HitGround, the timers (Timer3 slower above $60), the states Normal / Shelled (wake-up,
  shaking) / Held / Kicked (ObjShell_AnimFrame, blocks hit by the shell, other enemies killed for
  its kill tally) / Killed / Squashed / Poof; Player_HitEnemy for every player (the bounding
  boxes, the stomp window 19 above, OA2_GNDPLAYERMOD, Kill_Tally scores 100 ... 8000, 1-ups);
  Object_HoldKickOrHurtPlayer (run held: carry the shell, let go: kick; else hurt), Enemy_Kill
  for the tail swipe (counter $0C and $09), Object_HandleBumpUnderneath (a block bumped under
  one), GroundTroop_BumpOffOthers. The walkers of prg004: ObjNorm_GroundTroop (Goomba, green
  Troopa, hopping Paratroopa), ObjNorm_RedTroopa (turns at ledges), ObjNorm_ParaGoomba (three
  hops, then a high one), with KILLCHANGETO (stomped Para-: wings off). prg005 ObjNorm_Piranha:
  green, green fire and the Venus Fire Trap (hide - emerge - attack - retract; not out while a
  player is within 27; the fire ones face and look at the player and spit once at timer $28 in
  World 1: SOBJ_PIRANHAFIREBALL, near/far velocities), drawn clipped at the pipe; stomping one
  hurts. Drawn from SMB3's sprites (GroundTroop_Draw / Troopa_Draw with the head and feet,
  ParaGoomba_Draw wings, Object_Draw16x32Sprite, the poof). A hit on an NSMBW player is NSMBW's
  own damage (its invulnerability, power-down, death); a stomp is NSMBW's stomp jump at 4 a frame.
- Scrolling (prg008 Player_DoScrolling): the vertical, SMB3's - the screen stays at its lowest
  (the level's last row just above the bar) unless the first player flies (Player_FlyTime); once
  up it follows ($30 / $58 from the screen's top, up at most 3 a frame) back down to the lowest.
  NSMBW's camera keeps the horizontal, held inside the level (Horz_Scroll 0 .. Level_Width); the
  level's ends are walls. Done after dBg_c's camera execute (rt_menu.c hle_fn_80154F60 calls
  `smb3_stage_camera`: dBgParameter_c +0x3C/+0x64/+0x4C/+0x54, dBg_c +0x900B0).
- Time: NSMBW's own timer (dStageTimer_c +4) is kept at SMB3's every frame, so its hurry-up and
  its time-up death (checkTimeOut / setTimeOverDemo) come when SMB3's clock says.
- Death and time-up: with lives left the level starts again (rt_lyt.c's DoSceneChange: the world
  map scene the stage asks for becomes `smb3_stage_restart`); SMB3's score, coins and cards stay.
  No lives left: NSMBW's game over.
- The goal (prg002 ObjNorm_EndLevelCard / ObjHit_EndLevelCard): the card turns mushroom /
  flower / star every 8 frames; taken, the enemies on screen go in a puff, the clock stops, the
  card flies up at -$28, "COURSE CLEAR!" and "YOU GOT A CARD" with the card come
  (Video_CourseClear / Video_YouGotCard, letters from BG bank $5E), the time left goes into the
  score (DoTimeBonus), the card goes into the status bar (StatusBar_Update_Cards: CardUL..LR);
  a third card gives lives (EndLevelCard_xUpByMatch 2 / 3 / 5 alike, else 1) and the cards
  clear. Then, with no SMB3 map yet, 1-1 starts again. Not ported: the players running off to
  the right, the giant card shape of a triple match, the course clear music.
- Fixes from play-testing (2026-11-22):
  - Koopas: Troopa_Draw as SMB3 has it - the body pair's head side (sprite 0, or 1 when flipped)
    and the head's tip on PAL3, the other body sprite on the object's palette; the feet
    (Troopa_FootByEvenOddFrame[3 * odd + flipped], [+1]) left then right, the flip on both; the
    wing's frame by Var5 + 2 + carry. Shells: Object_DrawShelled's waking feet ($F9, PAL3, 10
    below / above, 3 out) when Timer3 < $50 hits PRG000_CAF1's bit; Object_ShakeAndCalcSprite's
    shake (X - 1 when Timer4's bit is clear).
  - Objects keep Objects_SprAttr from their init: OCSPECIAL_KILLCHANGETO changes only the ID, so a
    stomped Para-Goomba is a wingless Goomba on the Para-Goomba's palette.
  - The suit poof (Player_SuitLost $17, Player_SuitLost_DoPoof): a leaf on a big non-Raccoon
    player (ObjHit_SuperLeaf), and a Raccoon hit (Player_GetHurt from a super suit), halt the game
    for 23 frames (NSMBW's actor stop, dActor_c::mExecStopReq) with the player hidden behind the
    smoke ($47 $45 $43 $41, PAL1); the new suit is in place at once. A leaf on Fire: Super with the
    Raccoon underneath (no NSMBW change demo).
  - SMB3's rules run only on frames a player executed (dAcPy_c::executeMain): items, blocks,
    enemies, the clock and the P-meter wait while paused or halted.
  - The goal: DoTimeBonus as SMB3 - 10 seconds for 500 a frame while the hundreds or tens are
    left, then a second for 50; NSMBW's timer is held once the card is taken (no time-up).
  - A kicked shell's block hits use the kicker's suit (Object_BumpOffBlocks goes through
    Level_DoBumpBlocks, so LATP_Flower / LATP_Leaf read Player_Suit): progressive as a head hit.

Testing (Linux, headless): `SMB3_STAGE_TEST_X=<column>` starts the player at that column,
`SMB3_STAGE_TRACE=1` logs every item each frame, `SMB3_STAGE_PROBE=1` keeps the NSMBW actors, `SMB3_STAGE_BLOCKS=1` lists the blocks,
`SMB3_STAGE_TEST_TILES="col,row,tile;..."` changes tiles, `SMB3_STAGE_TEST_RACCOON=1` shows the
placeholder on any player, `SMB3_STAGE_JOINTS=1` logs the model's joint matrices,
`SMB3_STAGE_TEST_BIG=1` makes player 1 Super a second in (`SMB3_STAGE_TEST_BIG_AT=frames`
sooner), `SMB3_STAGE_TEST_RANIM="k,..."` plays the Raccoon animations in turn,
`SMB3_STAGE_BAR=file.ppm` writes the status bar each time it changes, `SMB3_STAGE_CAMLOG=1` logs
the screen against the level, `SMB3_STAGE_MAP=1` logs the solidity map; enemies log their
changes of state. Test driving (Linux): `RT_AUTOPRESS_FILE=path` reads the buttons (hex) from a
file each frame, `RT_FRAME_FILE=path` writes the frame number (a driver script presses through
the menus by the log, then times its presses in game frames).
Not yet: block and enemy sounds, vine and P-switch blocks; SMB3's map (a cleared or lost 1-1
starts again).

### 2026-11-22: two worlds, round 1

Rules for which game's behaviour applies: `CHARACTERS_AND_GAMES.md`. The block and semi-solid
comparison (awaiting decisions): `BLOCKS_NSMBW_VS_SMB3.md`.

- **Enemies jittering inside a player:** SMB3's hurt path (`PRG000_D355`) does nothing while the
  player flashes from a hit. The port now uses NSMBW's `isNoDamage` for that, so an enemy no
  longer turns around every frame inside an invulnerable player.
- **Bubbled players:** a player in a bubble or out of play (status 53 / 4) no longer exists for
  SMB3's objects. They can't kick shells, take hits or grab the card.
- **Super Leaf for NSMBW characters:** NSMBW's power-up change, not SMB3's poof:
  - 30 frames with everything stopped;
  - old and new forms alternate every 6 frames;
  - sound 274, then 8 frames of invulnerability.

  Losing the suit to a hit plays the power-down version: sound 275, then 127 frames of
  invulnerability. The SMB3 poof is kept for NES characters (`retro_is_player`).
- **P-speed (NSMB2's leaf):** with the leaf, NSMBW's dash top (3.0) is raised to 4.0. Held at the
  top, the cap climbs so the run from a standstill takes about 180 frames. NSMBW's own climb to
  3.0 measured 80 frames. Above 3.0 is P-speed: P-run animation, [P] on the meter, a jump from it
  flies. The meter shows six arrows over NSMBW's own run speed. SMB3's power-meter rules are gone.
- **Ground pound on a block:** the item comes out of the top, as from a hit below. A leaf can't
  be picked up until it starts to fall.
- **Black lines:** texture coordinates are pulled 1/20 texel in from tile edges. Point sampling
  had picked up neighbouring atlas tiles. Shared tile edges are now computed the same way.
- **Item rising from a ? block:** drawn behind the bouncing block. Its top row (the black outline)
  had shown over the block.
- Test switches: `SMB3_STAGE_TEST_NOENEMY` (no enemies), `SMB3_STAGE_DRAWLOG` (draw-path log).

### 2026-11-22: two worlds, round 2

- **Semi-solids:** NSMBW's own one-way platform flag on each stack's top row. The "upper 8
  units" and "is this player rising" stand-ins are gone. Checked: jumping up through 1-1's
  platform from below, landing on it, and walking in front of the big blocks.
- **Shells are carried NSMBW's way:**
  - `isCarry` reports a held SMB3 shell, so the carry walk/wait/jump animations and the
    `Throw` state play.
  - The pickup sets the model's carry flag and body pose as `dAcPy_c::spinLiftUp` does.
  - `cancelCarry` / `releaseCarryActor` drop the shell.
  - A player already carrying (another player) kicks instead of picking up.
  - The held shell is drawn where `getCarryPos` puts the hands, read in the player's draw. That
    removes the one-frame lag (the jitter).
  - Checked headless: pick up, carry, throw.
- **Lift-up height** (one player carrying another) is scaled to the 80% models.
- **Ground pound:** only a Super Leaf comes out of the top. Other items go down as before.
- Test switches:
  - `SMB3_STAGE_TEST_SHELL=col`: a shell on the ground.
  - `SMB3_STAGE_TEST_NSMBW_TILE="col,row,hex;..."`: an NSMBW tile in the level.
  - `SMB3_STAGE_OLD_SEMI`: the old semi-solid rules.
  - `RT_LOG_CREATE=1`: logs every actor made.
- **Semi-solids, revised:** NSMBW's flag goes only to a player whose feet were at or above the
  platform's top edge last frame (NSMBW lands players on one-way platforms only from above).
  With the whole tile flagged, a short hop with the feet ending inside it floated the player up
  onto it. Checked: a short hop under the edge falls back down; a full jump rises through and
  lands on top.
- **Held shell, revised:** placed with NSMBW's own `dEn_c::calcCarryPos`, using the shell
  offset NSMBW's carried shells use (0, -5, 6), turned with the player's model. That puts it at
  the hands, in front, a little ahead. It is drawn at the 3D shell's front face, so it shows in
  front of the holder.
- **Held shell jitter:** the shell's place was read in the stage's hook before `dAcPy_c::draw`
  ran, so it used the model's hand joints from the frame before, a frame behind the body. It
  now reads them after the draw (`smb3_stage_player_drawn`, from `rt_retro.c`). It is also
  drawn at its exact fraction of a unit, not rounded. Measured on per-frame dumps: the shell's
  screen x had swung over about 5 px against a steady Mario; it now holds within 1 px.
- **T-pose after a Raccoon flutter with a shell held:** fixed. Our NSMB2 animations play by
  pointing the model's animation file at our archive for the length of the `setAnm` call.
  While the model carries, `setAnm` also re-sets the carry body animation by name
  (`fn_800D6460`), and it looked that name up in our archive. It wasn't there, so the arms went
  to their bind pose, straight out, and stayed that way. `ra_play` now clears the model's carry
  bits during the call. Reproduced headless (hold a shell, flutter), then checked with the fix.
  The tail swipe is also blocked while carrying, and flight with something held uses NSMB2's
  `_carry` animations.
- **NSMB2 animations ported into the player's animation file:** before, our NSMB2 Raccoon
  animations played by pointing the model at a separate archive for the length of each
  `setAnm` call. Now, once per model file, `anm_merged` builds a new BRRES at `0x82200000`. It
  holds NSMBW's own player animation file (P_rcha) and our 14 NSMB2 animations side by side,
  under a new root, with every group dictionary (NW4R Patricia trees, built the way wszst
  builds them) rebuilt to list both. Each sub-file's offset to its BRRES is fixed up. Then
  `ResFile::Init` runs and every name is checked through the game's own `GetResAnmChr`: all 276
  animations resolve, and none of the game's are mislooked. The model's animation file
  (`+0x210`) is then pointed at the merged file for good. So `setAnm`, the carry body animation
  and everything else find NSMB2's animations by name, like any of the model's own, and nothing
  is swapped during a call. The old swap (`ra_play`) is now only a fallback, used when the
  merge fails or with `SMB3_STAGE_NO_MERGE`.
- **P-speed animation now plays:** with the Super Leaf, the game's run (2) becomes NSMB2's
  `T_run`, its dashes (3, 4) become `T_b_dash`, and in P-speed they become `T_b_dash2` (the
  P-run, arms back). Checked headless with frame dumps: running from a standstill goes
  `T_run`, then `T_b_dash`, then `T_b_dash2` once the meter shows P. A P-jump flies with
  `T_fly`. Holding a shell and fluttering uses `T_fly_carry`, and after the throw Mario
  stands normally (no T-pose).
- Debug switches removed: `SMB3_STAGE_ANMSWAP`, `SMB3_STAGE_ANM35`, `SMB3_STAGE_ANMDBG`.
- `SM_CARRYPOS` moved to `SM_MEM + 0x2C0`. It overlapped `SM_JMTX + 0x40`, which is used as a
  ResFile holder.

### 2026-11-23: death background, SMB3's world map

- **Death background fixed.** NSMBW's course showed through on a death for two reasons. The
  level's draw proc was entered only from the players' draw, which stops once a player is gone
  (in a pit, or in the death demo). It is now also entered from NSMBW's own background draw
  (`dBgGm_c::draw`, `gm_pf_family.c`), every frame. Also, the restart reset the level as soon as
  the death asked for the next scene, so the course showed through the whole wipe. The reset now
  waits until the old stage has gone (`reload_pending`: done at the next stage's first players,
  or once the scene isn't the stage). Checked headless on a pit death: the Bowser wipe plays
  over SMB3's 1-1, and the restarted 1-1 loads and places as before.
- **SMB3's world map, with the NSMBW players on it** (`smb3_map.inc`; roadmap step 3, first
  part). Start Game now opens SMB3's map of the chosen SMB3 file (a new file: World 1) in an
  NSMBW stage scene.
  - **The map's game is SMB3's own.** The recompiled game keeps running between levels, fed
    player 1's buttons a frame at a time. Its paths, panels, Hammer Bros, items, completions and
    lives all come from it.
  - **The picture.** Its screen (background, map objects and its own status bar) is drawn as one
    plane in the stage's 3D scene, 1 NES pixel = 1 unit. The marker's four sprites are taken out
    (`Sprite_RAM` +$84..$93, `Map_DrawPlayer`). The camera is held on it.
  - **The players.** The NSMBW players stand on the map as their 3D models. Player 1 is where
    SMB3's marker is; the others follow along the path behind. Their own `executeMain` doesn't
    run on the map (`rt_retro.c`), so there are no physics or inputs. Their animation is played
    here: wait or walk, facing the way they go and facing front when they stand.
  - **Entering a panel.** SMB3 brings the level up unseen, and the stage takes it the way it
    took 1-1. Any panel can be entered; the tile layout bank comes from the tileset
    (`PAGE_A000_ByTileset`). Levels other than 1-1 use what's ported so far.
  - **Leaving a level.** The end goes back into SMB3 through `Map_ReturnStatus` (0 cleared,
    otherwise lost) and `Level_ExitToMap`. SMB3 runs on to its map: a cleared panel is marked
    and a lost one isn't. SMB3's lives follow NSMBW's player 1 rest count. The stage's score,
    coins and cards go back into SMB3 (`Player_Score`, `Inventory_Coins`, `Inventory_Cards`)
    and come out again for the next level.
  - **Saving.** The progress is saved to the SMB3 file each time the map comes back, because
    NSMBW's pause menu in a stage has no Save.
  - **Sound.** SMB3's own map music plays (`smb3_stage_audio`, `rt_audio.c`).
  - Checked headless:
    - walking from START, then entering 1;
    - losing 1-1: back on the map, a life down;
    - clearing 1-1: the panel is marked M, the card is in the bar, and walking on to 2 works.
  - Settings: `smb3_map = 0` in settings.ini (or `SMB3_STAGE_NO_MAP=1`) gives the old 1-1 loop.
  - Testing switches:
    - `SMB3_STAGE_TEST_CLEAR=frames` counts the level as cleared;
    - `SMB3_MAP_FEET=units` sets where the players stand on a square;
    - `SMB3_MAP_FBDUMP=dir` writes SMB3's picture;
    - `SMB3_MAP_NO_SAVE=1` turns off the save.
- **Not yet:**
  - NSMBW's course intro card ("World 1-1") still shows before the map and before every level,
    always reading 1-1.
  - The map is still SMB3's picture, not native tiles; the players are not scaled to the
    marker's size.
  - Only player 1 controls the map.
  - NSMBW's game over doesn't go to SMB3's.

### 2026-11-26: the Frog suit (smb3_stage_frog.inc)

- **Model:** Mario's Frog model (`models/frog/user_edited/head_type_2.glb`) is made into the
  game's format by `models/tools/build_smb3_brres.py --frog`, in `game/mod/characters/smb3/mario.brres`
  (until 2026-11-26's flying hands: `build_frog_brres.py`, `frog_mario.brres`, both still there).
  - **What it is:** NSMBW's own Mario model file with the Penguin body and head (unused in SMB3)
    made the Frog's. The Frog model's rest pose is Super Mario's, so the Penguin body takes those
    bones.
  - **Loading:** `rt_charmdl.c` loads it for Mario while the SMB3 stage runs.
  - **Switching:** a Frog player's model shows that slot, through
    `dPlayerMdl_c::setPlayerMode(Penguin)` with the player's own mode byte (`+0x152`) put back.
    `+0x770` is the model shown.
  - **Other characters:** Luigi and the Toads keep their Super look for now.
- **The suit:** as the Raccoon, the player stays Super underneath, and a flag says Frog.
  - **Taking it:** the suit comes at once, whatever the player's size (`ObjHit_StarOrSuit`). NSMBW
    characters get NSMBW's power-up change (the models by turns); NES characters get SMB3's poof.
  - **Losing it:** a hit drops to Super, like the Raccoon. A flower or a leaf replaces it.
- **Idle:** `F_wait`, the user's pose (`models/frog/frog_idle_pose.json`; the posed side mirrored
  onto the other), replaces the game's wait.
  - **Built:** by `tools/nsmb2_anims.py`, into the Raccoon animation archive (needs the NSMB2 RomFS,
    as the Raccoon's do).
  - **Fallback:** `smb3_frog_wait_ok` says whether it is there.
- **The item:** SMB3's Starman object, frame 2 (`PUp_StarOrSuitFrames`).
  - **Sprite:** pattern `$91` drawn mirrored (`ObjP0C`), palette 2 (`Star_Palettes`), from CHR bank
    `$4C` - the suits' bank, which SMB3 loads for its big ? blocks.
  - **Movement:** it bounces like the star (`ObjNorm_StarOrSuit`).
- **The block:** a ? block with the Frog suit in 1-1 (`W101L`, `Level_LayPtrOrig` `$BB82`), 4 rows above
  the ground in the first free column 6 or more right of the start. The log names its column and
  row. `SMB3_STAGE_FROG_BLOCK=col,row` puts it anywhere (any level), for testing.
- **Not yet:** the Frog's moves (SMB3's hops on land, its swimming), Luigi's and the Toads' Frog
  models.

### 2026-11-26: the Raccoon's flying hands (smb3_stage_frog.inc, hands_anchor)

- **What:** as in NSMB2, a Raccoon Mario or Luigi opens his hands while flying and while the tail
  slows a fall, and has fists otherwise. He also gets the Raccoon body of `models/raccoon` (NSMBW's
  body with NSMB2's puffier torso). Super, Fire and the Frog look as before.
- **Model files:** `game/mod/characters/smb3/mario.brres` (the Frog too) and `luigi.brres`, built by
  `models/tools/build_smb3_brres.py --raccoon models/raccoon/<who>/<who>_Raccoon.glb`. Super's body
  model (`MB_model` / `LB_model`) gets three more objects, each under a node of its own:

  | Node | Object |
  |---|---|
  | `leg_l1` | Super's body (`polygon0`, Nintendo's) |
  | `leg_l2` | `raccoon_body` |
  | `leg_r1` | `raccoon_fists` |
  | `leg_r2` | `raccoon_open_hands` |

  The nodes only switch the objects on and off; the parts are skinned to the arm and body bones
  like the body. Only Super's body shows until the runtime says otherwise.
- **Loading:** `rt_charmdl.c` loads `mario.brres` for Mario and `luigi.brres` for Luigi while the
  SMB3 stage runs.
- **Each frame** (`hands_anchor`, from `frog_anchor`): a Raccoon shown (`RC_SHOWN`) gets its body
  with the open hands while its NSMB2 animation is `RA_FLY`, `RA_FLY2`, `RA_FLY_ST` or `RA_FALL`
  (carrying something: `RA_FLY_C`, fists), or while the P-run (`RA_PRUN`, NSMB2's `T_b_dash2`, at
  full P-speed) is playing; else with the fists. Anyone else gets Super's body.
  - **How a node is hidden:** its ResNode flag `0x100` (`+0x14`); and when the model keeps copied
    visibility bytes (`ScnMdl` `+328`, vtable `0x8034E8F0`), its byte there too, with the model's
    `+316` bit 1 set, as `ScnMdl::CopiedVisAccess` (`0x8025C8E0`) does.
  - **Log:** `player N: body Raccoon, open hands` / `Raccoon, fists` / `Super` on each change, and
    `hands: the Raccoon's parts in the model at ...` once a model is found to have them.
- **Not yet:** the Toads' Raccoon parts (they keep Super's body).
