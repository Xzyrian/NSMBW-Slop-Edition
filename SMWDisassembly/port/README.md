# SMW port

Goal: Super Mario World inside the NSMBW runtime, the way SMB3 went (user, 2026-11-27: "the same
path as SMB3"): first the whole game recompiled and playable with its own Mario, then moved piece
by piece into native NSMBW-engine code with NSMBW players. First milestone (user): a new file ->
the intro message -> Yoshi's House -> the map -> Yoshi's Island 1 or 2. Silent first; sound next.

## Now

Game Select -> **SMW** -> File Select (SMW's own three files, in NSMBW's cards) -> character
select -> **Start Game**: SMW runs whole, recompiled, over the faded-out setup screen. Its title
and file menus are passed unseen by its own code (the chosen file, 1 player), so a new file starts
at the intro message ("Welcome! This is Dinosaur Land..."), then Yoshi's House on the map; a file
with progress starts on the map where it was saved.

- **Controls** (Wii Remote sideways, as NSMBW): d-pad, 2 = B (jump), 1 = Y (run / throw),
  A = A (spin jump), B = X, - = Select. + (or HOME) is the pause menu (Continue / Save /
  Save & Quit / Quit), not SMW's Start.
- **Saving**: SMW saves itself where it asks to (Yoshi's House, castles, switch palaces...),
  into its save RAM; that RAM is `<game>/smw/smw.srm`, written whenever it changes (and Save in
  the menu writes it too). The File Select cards read it: a file's "World" is where its player is
  (Yoshi's Island 1, Vanilla Dome 3, Forest of Illusion 5, Valley of Bowser 7, Star World 8,
  Special 9, the main map's lands 2); lives show 5 (SMW's files keep none). Copy / Erase act on
  it too (not tried yet).
- **Sound**: none yet. The SPC700's boot ROM protocol is answered (snes_apu.c), so the game's
  uploads of its sound engine, samples and music go through and are kept (64 KB), but the engine
  doesn't run.
- **Discord**: "SMW: Yoshi's Island" / "SMW: in a level (...)".
- **Its levels with NSMBW's players** (`smw_stage.c`; settings.ini `smw_stage`, default 1; 0 =
  SMW's own Mario all the way): when SMW starts a level (game mode $14, not the intro) it is held
  there and the level goes to an NSMBW stage - NSMBW's course 1-1 as an empty shell, the chosen
  NSMBW character(s) at 80%, SMW's level in it:
  - tiles: Map16 as SMW's own loader built it ($7EC800 / $7FC800, 16 x 27 a screen), each 16 x 16
    picture from its four 8 x 8 tiles (Map16Pointers) in BG1's VRAM patterns and CGRAM palette;
    the sky BackgroundColor ($0701); layer 2 from VRAM at half the camera's speed;
  - collision as SMW's player block interaction: page 0 passes, $100-$110 ledges (one-way tops),
    $111-$16D solid, $16E-$1D7 slopes (SlopesPtr -> SlopeHeights as NSMBW's 45 / 22.5 degree
    slope units; SMW's 1:4 to the nearer 22.5 half), $1D8-$1FA (SMW's slope assists) passed
    under a slope (a hill's body - SMW carries the slope above down for a foot in it) and solid
    elsewhere, $1FB-$1FF lava (passed);
  - the camera as SMW's: it never zooms out (NSMBW's zoom held at its unzoomed size), never shows
    below SMW's lowest (layer 1 at $C0), follows player 1 up and down (between a third and three
    quarters down); the background kept to SMW's bottom (an NSMBW screen taller than SMW's
    shows more sky, not the tilemap below SMW's picture); the level's ends are walls;
  - a one-screen level (HorizLayer1Setting 0 or a side exit: Yoshi's House) is centred and still,
    its ground carried out either side as far as NSMBW's wider screen shows (16 columns each
    side: each edge column's lowest unbroken run), walls at the screen's sides; with
    SideExitEnabled a player at a side leaves it - as SMW's SubSideExit;
  - leaving: Exit Course in NSMBW's pause menu, or a side exit, takes NSMBW to the setup scene
    in place of its world map, and SMW out of the level as it would itself (OWLevelExitMode $80
    / 0, game mode $0B) - SMW's map fades in, over the setup scene (rt_gamesetup.c: smw_resume;
    its next level goes straight to a stage). A death with lives left starts the level again;
  - SMW's own loading of a level for a stage (game modes $10-$14) and its fade from the title to
    the map aren't shown: black until the stage's wipe or the map's fade-in.
  Not yet: SMW's objects (? blocks, coins, items), enemies, the goal, vertical levels, lava, its
  status bar; a game over goes NSMBW's way.

Checked (headless, tools/smw_headless.c, and in the runtime): Nintendo Presents, the title with its
circle wipe and the attract demo; the file and player menus; the intro message and its prompt; the
Yoshi's Island map (its layers, the border, the mosaic fades); Yoshi's House; Yoshi's Island 1 -
the status bar, Rexes, the Banzai Bill, coins, dying and back to the map.

## Layout

```
SMWDisassembly/
  smw.asm, bank_*.asm, ...     the disassembly (SMWDisX): the source of everything
  asar.exe, asar-LICENSE.txt   the assembler, Asar 1.91 (Windows; elsewhere $ASAR or asar on PATH)
  tools/
    build_smw.py               assemble (USA) -> check the ROM (= the original) -> recompile -> out/
    recomp65816.py             the 65816 recompiler (below)
    smw_headless.c             runs it without the runtime (testing)
  port/
    snes.h                     the SNES as the rest sees it
    snes_gen.h                 the 65816: registers, the bus, every instruction as a macro
    snes_cpu.c                 the bus (LoROM), $4200-$421F, DMA / HDMA, calls, interrupts, time
    snes_ppu.c                 the picture (a row at a time)
    snes_apu.c                 the SPC700's boot protocol (no sound yet)
    smw.h, smw_main.c          SMW in the runtime: files, input, screen, the pause menu's side
    smw_stage.c                its levels in an NSMBW stage with NSMBW's players
    hooks.txt                  native code before SMW routines (none yet)
  out/                         generated: smw_bNN.c, smw_interp.c, smw_table.c, smw_syms.h,
                               smw_rom.c, smw.sfc, smw.sym
```

`recomp/build.py` runs `tools/build_smw.py` ([1c]), compiles port/ with the runtime and out/ as
[3c]. Without Asar, a complete out/ is used as it is.

## The recompiler (tools/recomp65816.py)

- **Code from the source, not guessed.** Asar's WLA symbol file has an `[addr-to-line mapping]`:
  each address that made bytes, with the source line that made it. A line whose first word is a
  65816 instruction is code (the SPC700 engine, between `arch spc700` and `arch 65816`, is not;
  an instruction made inside an instruction macro, `%BorW(...)`, maps to the macro's if / else
  line: the line after it is the instruction). Asar's repeats (`DEX #3`) map once: what follows
  an implied instruction is code too. Checked: every instruction's decoded length is exactly the
  distance to the next mapped address (62,258 of them).
- **Widths at run time.** An immediate's size is the assembled one (the source says `.B` / `.W`
  on every one); every other instruction whose width depends on M / X tests the flags as it runs.
- **One function per bank** (`smw_bNN(pc)`): a switch over its instruction addresses, then each
  instruction as C. A jump outside the bank, or to an address that isn't there, returns to the
  dispatcher (snes_cpu.c).
- **Calls** as SMB3's: the stack in WRAM is the truth; JSR / JSL push and are a C call expecting
  the next instruction back; a return to another address (ExecutePtr pulls its caller's address to
  read the table after the JSL) unwinds or is a jump.
- **The interpreter** (`smw_interp.c`), generated from the same table and the same macros: for
  code that isn't recompiled - SMW builds its OAM-clearing routine in RAM ($7F8000).

## The machine (snes_cpu.c, snes_ppu.c)

- Time: about 8 master clocks a cycle, 170 cycles a line, 262 lines. Line V is drawn as screen row
  V-1 at its hblank, with the PPU as set then; HDMA runs at each hblank for the next line; vblank
  at line 225 (the coroutine yields: the frame is done; then NMI); the V-IRQ when the beam reaches
  VTIME - after the setting changed, not at once (SMW sets VTIME in its NMI for the next frame's
  status bar split).
- PPU: modes 0, 1 and 7 (no EXTBG), 2 / 4 / 8 bpp, 8 and 16 pixel tiles, 32 / 64 maps, mosaic,
  sprites (sizes, both name tables, priority rotation, 32 a line), both windows with their logic,
  main / sub screens, colour math, brightness. Not yet: hi-res, offset-per-tile, interlace,
  direct colour.
- DMA (all modes, both directions), HDMA (direct / indirect, repeat), multiply / divide, the
  joypads (auto-read; $4016 serial), the WRAM port ($2180).

## Testing

- `tools/smw_headless.c`: `smw_headless rom frames "frame:buttons,..." outdir` (buttons
  A B X Y L R s S U D < >); `SMW_DUMP=from-to:step`, `SMW_MEM=frame:file` (WRAM),
  `SMW_PPU=frame[:vram]` (the PPU's registers, VRAM), `SMW_SRAM` / `SMW_SRAM_OUT`.
- `SNES_INTERP_ALL=1`: everything interpreted (recompiler or semantics?), `SNES_TRACE=pc,...`
  (with it: registers at those addresses), `SNES_INTERP_LOG`, `SNES_DMA_LOG`, `SNES_VRAM_LOG`,
  `SNES_IRQ_LOG`, `SNES_LAYERS=hex` (only those layers drawn).
- `SMW_SCROLL=frame` (headless): Mario, the layers' positions and the PPU's scroll each frame.
- In the runtime: `SMW_TEST_PAD="frame:hex,..."` (SNES buttons from SMW's first visible frame -
  e.g. `150:0200,170:0,400:8000,406:0` walks a file on Yoshi's House's map into Yoshi's Island
  1); for the stage `SMW_STAGE_MAP=1` (its tile classes in the log), `SMW_STAGE_TEST_X=column`
  (the players placed there), `SMW_STAGE_TRACE=1` (player 1's place every 10 frames),
  `SMW_STAGE_TEST_EXIT="frames:kind,..."` (that many frames into each stage, NSMBW's stage exit
  of that dScStage_c::Exit_e kind - 1 a death, 2 Exit Course).

## Next

1. Sound: the SPC700 and its DSP running SMW's own engine; then, as SMB3's, its music and
   effects as NSMBW's (streams, the expanded sound archive).
2. NSMBW players in SMW's levels - begun (above): next SMW's blocks and items (? blocks, coins,
   Yoshi coins, the midway and goal tapes) and the goal back to SMW's map; then its enemies as
   native actors; vertical levels.
