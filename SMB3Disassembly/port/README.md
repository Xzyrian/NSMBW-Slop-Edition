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
    smb3_stage_music.inc     SMB3's sound in the stage: its engine's rules natively, songs on NSMBW's stream players
    smb3_sound.c, .h         SMB3's songs / sound effects in NSMBW's formats (build time) and NSMBW's sound archive expanded with them
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
  - **Sound.** SMB3's own map music plays (since 2026-11-27 (134) as NSMBW streams: see below).
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

### 2026-11-27: SMB3's music in the stage (smb3_stage_music.inc)

(Replaced in (134), below: SMB3's songs are NSMBW streams now and its engine no longer runs on
the APU in the stage. What plays when, and why, still holds.)

- **Levels play SMB3's music, from SMB3's own sound engine.** In a level the NES game is held
  where SMB3 brought the level up; `nes_sound_run` (nes_cpu.c) runs PRG028's
  `Sound_Engine_Begin` alone, as the NMI does (banks 28/29 in, a JSR, everything put back), once
  every 29780.5 CPU cycles, paced by the sound sent to the PC (`smb3_stage_audio`, called by
  `rt_audio.c` for each block). So the tempo is the NES's, rollback frames never run it twice,
  and the held game goes on unchanged when SMB3 takes over again (its frame timing moves on with
  the cycles). On the map nothing changed: SMB3's frames make its sound.
- **What plays** - SMB3's queues, set the way SMB3's code sets them:
  - the level's song (`Level_MusicQueueRestore`, from its header) from the top when the level is
    placed; a pipe into another area gets that area's;
  - NSMBW's star / P-switch music state (SndSceneMgr's flags 4 / 8, NSMBW's own) → Invincibility /
    P-Switch, and the level's song after (PRG008_A1FE);
  - NSMBW's requests, translated: the miss → Player death, game over → Game over, the hurry-up at
    100 → Time warning (NSMBW's timer is SMB3's), a course / boss clear → Course clear / Victory;
  - the goal card → "Got the Card" (`MUS1_COURSECLEAR`), three alike → the fanfare; the time
    bonus waits for it as DoTimeBonus waits for SndCur_Music1 - here by its length (192 / 240
    frames), so every machine counts the same;
  - NSMBW's pause menu → `Sound_QPause` 1 / 2: SMB3's pause sound, the music held.
- **NSMBW's music is not played in the SMB3 stage** (`smb3_music_sound`, from the nw4r
  detail_StartSound / HoldSound / PrepareSound hooks): its BGM players' sounds (16-19, 21 in the
  sound archive - `tools/brsar_sounds.py`) and, in a level, its pause sound. NSMBW's sound
  effects stay and are mixed with SMB3's sound (on the map too, where SMB3's sound used to replace
  everything).
- Testing: `SMB3_MUSIC_LOG=1` (the songs as they change, a second's samples and loudness, the
  NSMBW sounds not played); `SMB3_MUSIC_TEST_Q1=song,frame` queues a Music1 song that many sound
  frames into the level (song lengths).
- Checked headless (Mario, 1-1 from the map): World 1's level song (10) plays with full sound in
  the level; NSMBW's CHIJOU stream and its voice track are not started; a death plays SMB3's death
  song (01); the card plays Course clear (20) and the level ends back on the map; pause holds the
  music silent after SMB3's pause sound and resume continues it.
- Not yet: SMB3's sound effects (NSMBW's play); bosses' own songs and the Hammer Bro battle's win
  (their objects queue nothing yet).
- **Fixes (same day):**
  - *The music skipped* (worst in 1-2): the engine's own cycles were made into sound on top of
    the cycles asked for, so the sound piled up and the backlog was dropped every few seconds.
    They are part of the frame now (`nes_sound_run`: the next frame 29780.5 cycles after this one
    began; what it ran past is owed back).
  - *The death song came late and was cut*: it waited for NSMBW's miss music (after DemoDown's
    wait) and NSMBW's restart came before its end. Now it starts as the death begins
    (`dAcPy_c::initPlayerDownCommon`, when the level is lost: +5460, startMissBGM's own test), and
    the restart waits for it (`smb3_stage_restart` holds it; `smb3_stage_draw_any` does it once
    the 192 frames are over - as SMB3 drops to its map when the song ends).
  - *The P-switch's song*: from the stage's own P-switch (`PS.cnt`, SMB3's Level_PSwitchCnt) as
    SMB3 changes it - pressed: P-Switch (over a star's song too); a star got: Invincibility; one
    over: the other's if it still runs, else the level's.
  - *A dying player took a star*: SMB3's power-ups aren't touched by a player in a demo (death,
    pipes, the goal), out of play or in a balloon (`items_touch`).

### 2026-11-27: slopes (Hills, Underground)

- **Players on SMB3's slopes are on NSMBW's own slopes** (`smb3_stage.c`: `slope_shape`,
  `slope_unit`). In a slope level (`Level_SlopeEn`: tilesets 3 Hills and 14 Underground), each tile
  from its quad's base up (`Tile_AttrTable`'s first four: $25 $5F $99 $E2) has a shape from
  prg000's `Level_SlopeQuad00/40/80/C0`, and `Slope_LUT` gives the shape's floor and ceiling per
  pixel. `smb3_stage_unit` hands NSMBW a slope unit for a slope shape, so the player's own physics
  run on it: walking, running, standing, the crouch slide, jumps from it.
  - Floor slopes are hi `0x20`, low byte as follows: `$01` 45° up → `0`, `$02` 45° down → `1`,
    `$0C $0D` 22.5° up → `2 3`, `$0E $0F` 22.5° down → `4 5`.
  - Ceiling slopes are hi `0x40`. Each one is a floor shape upside down, with the same number:
    `$05 $06 $11 $12 $13 $14` → `0 1 2 3 4 5`.
  - Squares (`$03`), walls (`$04`) and flat ceilings (`$08`) are solid. Unsloped ground (`$07`)
    is NSMBW's one-way floor, as before.
  - How the codes were found: `SMB3_STAGE_PROBE` on the shell course gave NSMBW's slope tiles
    (`0x20` / `0x40` with shapes 0-5, `0x0A` flat, `0x0B-0x12` its 4-tile slopes). Walking across
    test cells (`SMB3_STAGE_TEST_UNIT`) showed each shape's direction.
- **SMB3's objects on slopes** (`smb3_stage_enemies.inc`: `world_detect`, `hit_ground`), ported
  from PRG000_C5BC-C67F.
  - An object lands at the shape's depth under its middle (`Object_SlopeHeight`, added by
    `Object_HitGround`). The depth rule is SMB3's: at or below the slope's height there, or 12
    down.
  - The flat middle grounds ($A8 $AA $AB $F9 $37) lift it to a pixel above.
  - Walking off a slope's tile, it follows the slope down or up (`Objects_Slope`).
  - In a slope level, anything from the base up is a ceiling to its head.
  - SMB3's ceiling shapes are no floor for objects.
  - Not ported yet: a slope's push on objects' speed (`LRBounce_Vel` / `Slope_ObjectVel_Effect`
    on kicked shells and the like).
- **Checked headless:**
  - 1-2: up the first hill's 22.5° slopes, then the next; over the top and down the 45° and
    22.5° sides; a crouch slide back down. The pictures match the slopes.
  - 1-2: the first Para-Goomba hops down the hill's side, landing on the slope.
  - 1-5: on its 45° floor; jumps up into the slanted ceilings.
- **New test switches:**
  - `SMB3_STAGE_TEST_UNIT="col,row,hi,lo;..."`: those cells get those NSMBW unit flags.
  - `SMB3_MAP_TEST_AT="Y,X"` (hex): player 1's map marker is put on that square, e.g. `20,80` for
    1-2, `A0,40` for 1-5.
  - `SMB3_OBJ_TRACE`: every object, every frame.
  - `SMB3_STAGE_MAP` now draws slopes as `/ \` and ceilings as `v`.

### 2026-11-27: pipes come out, the P-switch goes through, SMB3's sound as NSMBW's (134)

(The sound part is superseded by (136), below: no cache, no file swapped - NSMBW's sound
archive is expanded, and the sound effects are NSMBW wave sounds.)

User: "when mario enters a pipe he does not exit another / P-Switch state also doesn't carry over
through a pipe / When entering a pipe, for a brief moment, an audio track will keep playing /
... can we convert SMB3's audio to NSMBW natively?" (asked: pre-rendered streams).

- **Out of the other pipe** (`smb3_stage_pipes.inc`: `pipe_exit_placed`, `pipe_exit_frame`).
  While SMB3 runs the junction, its first frame with the other area up gives SMB3's Mario at the
  start of its way out and `Level_PipeExitDir` (1 up, 2 down, 3 right, 4 left; PRG026 / PRG008).
  With the stage placed on that area, the exit pipe is the pipe end ($AD-$B4 - exit pipes are
  often the unenterable $B1/$B2) above / below him, or the sideways mouth ($B5) beside him. Each
  player is then put inside it and NSMBW's own `daPlBase_c::StateID_DemoInDokanU / D / R / L`
  plays (`StateID_DemoInDokanU` 0x8035482C, the others 0x40 apart): it waits for the fade and its
  turn (daPyDemoMng), plays the pipe sound and slides out to mWarpPos, set to the mouth. The
  pipe's cells let the player through and the tiles about it are drawn over it, as on the way in.
  Doors and in-level transits: the players stand where SMB3's Mario is, as before.
- **The P-switch through a pipe** (`smb3_stage.c` `level_fresh`, `pswitch_resume`): SMB3's
  `Level_PSwitchCnt` belongs to the game, not the area. A junction's restart keeps the count, swaps
  the new area's coins and bricks, and keeps the P-switch song (`music_bg_want` reads `PS.cnt`).
- **SMB3's sound is NSMBW's now** (`smb3_sound.c`, `smb3_stage_music.inc`). The NES APU no longer
  runs for the SMB3 stage or its map (`smb3_stage_audio` makes nothing). That ends the leftover
  sound on a pipe: the junction's frames, run all at once, used to make a burst of APU sound
  that played on into the next area.
  - **Rendered once** (`smb3_sound_prepare`, from `rt_disc.c`'s `disc_init`). SMB3's own engine
    runs offline on the APU for every song (Music Set 1 $01-$40; Set 2A $01-$0F; Set 2B $10-$C0)
    and every sound effect (each queue's values).
    - A looping song is found looping when the engine's RAM (not the stack page) and its work RAM
      at $7Axx repeat an earlier frame. Its loop start is moved onto a stream block, as NSMBW's
      are, and the last 20 ms fade into what comes before the loop start (the noise and pulse
      phases differ), so the loop has no click.
    - Fast copies of the songs the time warning speeds up (Set 2B, $09, $0A: `Music_RestH_Off`
      $10, PRG031_E4E4), as NSMBW's _FAST streams.
    - Songs are written as DSP-ADPCM .brstm in NSMBW's two-channel layout
      (couse_clear_lr.n.32.brstm: two channels, one track of both, 32 kHz, 0x2000-byte blocks).
      The encoder's eight predictors come from per-frame least squares, clustered; each frame's
      predictor and scale are picked by trying them. Sound effects are written as .wav.
    - The files go to `<game>/cache/smb3_sound/` with a stamp (renderer version + ROM). They are
      made again only when that changes, or with `RT_SMB3_SOUND_RENDER=1`.
    - The first time takes about 30 s here (24 s engine + APU, 7 s encoding; 84 files, 30 MB).
      The window title shows the progress and the window is kept alive.
  - **On the disc**: the songs are root files `/smb3_m1_XX.brstm`, `/smb3_m2_XX.brstm`,
    `/smb3_m2f_XX.brstm` (fast), added to the FST after the mod's archive.
  - **Played by NSMBW** through `SndAudioMgr`'s own start (its vtable +180, as its BGM start
    `fn_801953B0` calls it), on two of its own BGM sounds:
    - `STRM_BGM_MORI` (1915; the course BGM player 18, volume 127, one track) for Set 2;
    - `STRM_BGM_LAST_CASTLE_APPEAR` (1899; the fanfare player 17, volume 127) for Set 1.
    As NSMBW opens their stream file, `DVDConvertPathToEntrynum` (`gm_mj_conv.c` →
    `smb3_strm_redirect`) is given the SMB3 song's file instead. Volume: `smb3_volume` (the
    handle's `SetVolume`). Pause: `BasicSound::Pause`. NSMBW's own stream player does the rest:
    ADPCM, loops, mixing with its sound effects.
  - **SMB3's engine's rules, natively** (`smb3_hook_sound` on `Sound_Engine_Begin`, `port/hooks.txt`;
    `snd_step`). In a level, one step each stage frame (SMB3 is held there); on the map, its
    NMI's call.
    - Set 1 stops the Set 2 song and holds it. The time warning over: that song again, fast. Any
      other jingle over: all music stops.
    - A Set 2 song queued under a jingle is only held.
    - A Set 2A song (not $09 / $0A) plays at its own speed again.
    - The map's enter-level sound halts the song.
    - Pause / resume (`Sound_QPause` 1 / 2).
    - `SndCur_Music1 / 2`, `SndCur_Player / Level1 / Level2 / Map / Pause`, `Sound_IsPaused`,
      `Music2_Hold` and `Music_RestH_Off` are kept as SMB3's code reads them, each for its sound's
      length in frames. `Level_MainLoop` waits for the enter-level sound, `GameOver_WaitOnBGM`
      for the game over song, `DoTimeBonus` for the jingle.
  - **Sound effects** (SMB3's map, the bonus screens) are the rendered clips, played by the
    runtime's mixer (`rt_sfx.c` `sfx_play_file`, at `smb3_volume`). NSMBW's sound archive has no
    room for new waves, so they don't go through nw4r. Effects of frames SMB3 runs unseen (a
    level being brought up, a junction, SMB3's Mario walked into a pipe) are not heard: NSMBW's
    player makes its own.
  - A song NSMBW stops on its own (a scene starting) is started again, at most once a second.
    Before the files were stereo they were dropped every few seconds: one channel against the
    carriers' two.
- **Checked headless** (Mario, 1-1 from the map):
  - a test pipe at screen 8 (`SMB3_STAGE_TEST_TILES=130,25,AD;131,25,AE`) into the coin room:
    the player comes down out of its ceiling pipe (column 8 row 16, `StateID_DemoInDokanD`),
    hidden inside it first, then falls;
  - a P-switch running (`SMB3_TEST_PSWITCH=1`) went through with 41 left, the coin room's tiles
    swapped, the P-switch song on; at its end, the coin room's song (20);
  - the output audio (`RT_AUDIO_WAV`) holds each song, matched by loudness envelope against the
    files decoded: World 1's map (0.98), 1-1 (0.98, 85 s through its loops), the time warning
    jingle (0.95), then 1-1's fast copy (0.98);
  - the rendered files decode (a separate decoder) to the APU's own loudness, and their
    loops line up with the music before the loop start (envelope 0.95-0.99, against 0.3 for any
    other place).
- **Test switches**:
  - `SMB3_TEST_PSWITCH=1`: a P-switch running from the first placement;
  - `SMB3_MUSIC_LOG=1` now also logs each stream started, the file swapped in, sound effects,
    and who stops an SMB3 song (`smb3_music_stopping`);
  - `SMB3_MUSIC_TEST_Q1=song,frame`: counted in sound frames from the session's start;
  - `RT_SMB3_SOUND_RENDER=1`: render again.
- **Not yet / open:**
  - a pipe coming out upwards, and sideways pipes, not checked headless (the same code path as
    down);
  - SMB3's sound effects are mixed by the runtime, not by nw4r;
  - the jingle's length is counted in game frames (as SMB3 does), so a slow machine hears
    silence after the jingle until the frames are done.

### 2026-11-27: SMB3's sound in NSMBW's sound archive, expanded (136)

User: "songs should not be cached they should be built into the executable / I have cached the
songs on my end, build them into the game files / we need to expand NSMBW's sound archive for the
new sfx so they can run natively / do not substitute any space from NSMBW's existing sound
archive, we must expand it / never substitute or replace anything from the original game".

- **Made at build time, kept as game files.** `build.py` runs the game it just linked as
  `nsmbw.exe --smb3-render-sound ../SMB3Disassembly/out/sound` (`smb3_sound_render`). That renders
  only what the stamp says is missing (v6 + the ROM; v5's songs are kept). Deploy copies the
  results to `game\sound\smb3\`. Nothing is rendered or cached when the game runs.
  - Songs: `.brstm` as before (two-channel DSP-ADPCM, loops on a block, fast copies).
  - Sound effects: `.rwav`, NSMBW's own wave format (mono DSP-ADPCM, 32 kHz - the layout of the
    waves in NSMBW's wave archives, 32 kHz like many of its own).
- **On the disc** (`rt_disc.c`): the songs go in a new folder, `/smb3/`, appended after the
  disc's own entries. Nothing of the disc's is moved.
- **NSMBW's sound archive, expanded** (`smb3_brsar_expand`). The file on the disc is never
  changed. At start it is read, and the expanded archive is kept in memory and placed on the
  disc after everything, where the archive's entry points. It holds every byte of NSMBW's own:
  - SYMB: NSMBW's, then a new string table (its strings and ours: `SMB3_M1_40`,
    `SMB3_M2F_10`, `SMB3_SE_MAP_04`, ..., `GROUP_SMB3`).
  - INFO: NSMBW's, then the new entries and new sound, file and group tables (NSMBW's entries
    first, ours after):
    - 48 **stream sounds**: file `/smb3/<song>.brstm` (nw4r takes a path starting with `/` as
      it is); Set 2 on the course BGM player 18, Set 1 on the fanfare player 17;
    - 36 **wave sounds**: SMB3's queues on NSMBW's players - the player's on
      PLAYER_SE_PLY, the level's on PLAYER_SE_OBJ, the map's on PLAYER_SE_SYS, the pause sound
      on PLAYER_SE_SYS_GAME_PAUSE;
    - **GROUP_SMB3**: one wave sound file (RWSD, laid out as NSMBW's own - Yoshi's voices,
      file 85: per sound one track of one note at 0) and its wave archive (RWAR) of the effects'
      waves. nw4r counts groups as the table's count minus one: the last group, NSMBW's unnamed
      one (the files no other group has), is never loaded by number. So GROUP_SMB3 is group 12,
      that one moves to 13, and the files listed in it say 13.
  - FILE: NSMBW's, then GROUP_SMB3's data and waves. NSMBW's groups' places move with the
    section; their bytes don't change.
  - Sound IDs: after NSMBW's 1978 - 1978..2025 the songs, 2026..2061 the effects
    (`smb3_snd_id`).
  - Checked against the original with a separate reader: all 1978 sound entries the same, every
    group's data and waves the same, the new entries and files read back.
- **GROUP_SMB3 loaded with GROUP_BOOT** (`gm_nw4r_g3d.c` E(fn_802D3E90) → `smb3_sound_group_load`).
  As NSMBW loads GROUP_BOOT at start (`SndAudioMgr` → EGG's loadGroup, fn_802D3E90 → nw4r
  `SoundArchivePlayer::LoadGroup`), GROUP_SMB3 is loaded the same way into the same heap, where
  it stays (315 KB of waves; the heap had 1.5 MB free).
- **Played by NSMBW** (`smb3_stage_music.inc`): every SMB3 sound starts through `SndAudioMgr`'s
  own start (its vtable +180) by its own ID.
  - Each SMB3 queue has its own handle (`SM_MEM` +0x288..), so on each queue a new effect stops
    the last, as on the NES's one channel.
  - The carrier sounds and the stream file swap (`smb3_strm_redirect`) are gone, and so are the
    runtime mixer clips; `rt_sfx.c`, `rt.h` and `gm_mj_conv.c` are back as they were.
- **Checked headless** (1-1 from the map, `RT_AUDIO_WAV`; each matched by loudness envelope
  against the files decoded):
  - World 1's map song (0.95), the map's enter-level sound (0.99), 1-1's song (0.99);
  - the pause sound (1.00) and the song silent while paused;
  - the time warning jingle (0.82), then 1-1's fast copy (0.98).
  - The log has each start with its ID, and none dropped.
- **Test switches**:
  - `RT_DUMP_BRSAR=file`: the expanded archive as the game gets it;
  - `RT_DVD_TRACE=bytes`: disc reads that big, with the guest's calls under them;
  - `SMB3_MUSIC_LOG=1`: also the sound heap's free space when GROUP_SMB3 loads.

### 2026-11-27: a door keeps the song; the stage's sound effects (137)

User: "entering a door incorrectly causes the music track to change (in the case of stages that
use doors, just restarting the track that is already playing)" / "there are no stage sfx, like
collecting coins, hitting blocks, stomping enemies, is that intentional?" (it wasn't).

- **The song through a door or pipe** (`smb3_stage_music.inc`, `music_tick`): the area's song is
  queued only when it isn't the one playing, as SMB3's `Level_MainLoop` does (PRG030_8DE7). The
  same song plays on through the junction; another one changes.
- **The stage's sound effects** (`smb3_stage.c` `sfx_player` / `sfx_level1` / `sfx_level2`):
  the port's coin, block, item, enemy and shell routines set SMB3's sound queues where SMB3's own
  routines set them, and SMB3's engine rules play them (from GROUP_SMB3, 136):
  - coins (COIN), a block that bounces (BUMP), a brick busted (CRUMBLE), a power-up rising
    (RISE), a power-up with no change of form (POWER), an NES character's leaf (POOF), 1-ups;
  - a stomp (the squish; a Bro's - KICK), a kick, a kill by star / tail / shell / a bump from
    below (KICK), a kicked shell against a wall (BUMP), the P-switch (BABOOM), the time bonus
    (BLIP), a boomerang (BOOMERANG).
  - The characters' own sounds stay NSMBW's (CHARACTERS_AND_GAMES.md rule 5): the jump, the
    stomp's jump, the ceiling bump, a change of form.
- **Checked headless**: 1-Fortress's door - the song plays on in phase; 1-1 - a coin block, a
  kicked shell, its wall and a stomped Goomba each start their SMB3 sound.
