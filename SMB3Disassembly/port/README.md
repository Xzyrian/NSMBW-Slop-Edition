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
  Select shows them ("World 3" / "New File") instead of NSMBW's, whose save is not touched. A file
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

Not yet: NSMBW players (the next step), player 2, copying/deleting SMB3 files, online play (the
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
Placed so SMB3's start column stands where the course puts player 1.
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
Testing: `SMB3_STAGE_TEST_X=column` starts player 1 at an SMB3 column (left of the shell
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
- Score pop-ups: Score_PopUp / Scores_GiveAndDraw (5 slots, counter $30, points at $2A, the rise
  slowing by Score_RiseCounterMask). 100 coins: a life.

Testing (Linux, headless): `SMB3_STAGE_TEST_X=<column>` starts the player at that column,
`SMB3_STAGE_TRACE=1` logs every item each frame, `SMB3_STAGE_PROBE=1` keeps the NSMBW actors, `SMB3_STAGE_BLOCKS=1` lists the blocks,
`SMB3_STAGE_TEST_TILES="col,row,tile;..."` changes tiles. Not yet: block sounds, vine and
P-switch blocks. Next (ROADMAP.md): the Raccoon suit, the SMB3 status bar, the 1-1 enemies.
