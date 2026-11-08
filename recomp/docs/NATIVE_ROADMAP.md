# From emulation to a native PC port - roadmap

User, 2026-10-16: this should be a decompiled PC port, not an emulation - for performance,
for modding, and on principle. Online play may be taken apart if it stands in the way.

## Where we are

| layer | today | native goal |
|---|---|---|
| game code | 40k functions recompiled from PowerPC (`out/recomp_*.c`, `fn_XXXXXXXX`), ~130 hand-written (`hle_funcs.txt`, rt_gamesetup.c, rt_chars.c, ...) | readable C++, class by class |
| memory | one 88 MB guest address space, big-endian, every access byte-swapped | native structs, native pointers |
| graphics | the game writes GX commands into an emulated FIFO; `rt_gx.c` parses it, `rt_gxrender.c`/`rt_gxgl.inc` decode vertices and draw with GL | GX *API calls* go straight to the renderer |
| OS | the Revolution OS runs as recompiled code: threads, interrupts, alarms, decrementer; we deliver interrupts at poll points (`PPC_POLL`) | native threads / timers, no interrupts |
| disc / saves | DI and IOS (`/dev/di`, `/dev/fs`, ES) emulated at the IPC level (`rt_ios.c`, `rt_disc.c`) | `DVD*` / `NAND*` calls = host file calls |
| input | Bluetooth HCI + L2CAP + Wii Remote HID reports emulated (`rt_bt.c`, `rt_wiimote.c`); SI for GC pads (`rt_si.c`) | `WPAD*` / `KPAD*` / `PAD*` filled directly from host devices |
| audio | AX DSP microcode HLE + audio DMA (`rt_ax.c`, `rt_hw.c`) | AX API -> native mixer |
| hardware | MMIO registers (VI, PI, MI, DSP, AI, EXI, SI, DI) in `rt_hw.c` | gone |

Measured cost of the emulation (user's profile, CHANGELOG 2026-10-13): 63 % of the game thread was
the emulated OS idle loop, 13 % reading the clock in polls, ~10 % our GX decode; recompiled game
code itself was 3 %.

## Two tracks

**Track A - remove the emulated Wii under the game** (the platform). The game code stays
recompiled, but every Nintendo SDK library it calls is replaced at the *function* level by our own
native implementation (the same `hle_` mechanism, applied to whole libraries), so nothing below
the game is a simulated Wii any more. This is what the modern "recomp" ports do. Biggest win for
performance and for the "principle"; each step is self-contained.

**Track B - decompile the game code** (readable source), class by class, replacing recompiled
functions with C++ that does the same. The 8-player module port (NATIVE_PORT.md) is already this.
The community decompilation (NSMBW-Decomp, PAL) and the module's source are references; addresses
port to USA rev 2 with the address map we already use.

Track A goes first for each subsystem it touches; track B runs alongside on game logic.

## Track A, in order

1. **GX at the API level** - hook the RVL SDK GX functions (`GXBegin`/`GXPosition*`/`GXSetTev*`/
   `GXLoadTexObj`/`GXSetArray`/`GXCopyDisp`/`GXCopyTex`/`GXSetViewport`/...; NW4R and EGG call these)
   and build GL state directly. No CP/PE registers, no token/finish interrupts, no general FIFO
   parser. Two things stay byte streams: the SDK's `GXPosition*`/`GXColor*`/`GXTexCoord*` are
   inline writes to the write-gather pipe (compiled into every caller), so after our `GXBegin`
   those writes are taken as plain vertex data for that draw; and display lists stored in model
   files (BRRES) are GX command bytes - a decoder for those stays. Textures stay in their GX
   formats (data files) - decoded once, cached.
2. **OS: threads, timing, interrupts** - `OSCreateThread`/`OSResumeThread`/`OSSleepThread`/
   `OSWakeupThread`/mutex/cond/message queues on our own scheduler (fibers exist already,
   rt_state.c), `OSAlarm` on a host timer, `VISetPostRetraceCallback` etc. driven by the frame
   pacer. Then no interrupts, no decrementer, no `PPC_POLL` polling, no idle spin. Removes the
   class of bug behind the 2026-10-13 freeze.
3. **Disc and saves** - `DVDOpen`/`DVDReadAsyncPrio`/`DVDFastOpen`/`ARCOpen` read host files;
   `NAND*` on the save folder. `/dev/di`, `/dev/fs`, ES, IPC go away.
4. **Input** - `WPADRead`/`KPADRead`/`WPADProbe`/`WPADControlMotor`/... and `PADRead` filled from
   our controller layer (rt_remotes.c: keyboard, real remotes over HID, later XInput pads).
   Bluetooth/L2CAP/report emulation goes away; real remotes are read as HID devices directly.
5. **Audio** - the AX API (`AXAcquireVoice`, `AXSetVoice*`, callbacks) on a native mixer thread;
   no DSP mail, no audio DMA.
6. **Hardware layer deleted** - `rt_hw.c` MMIO, `rt_bt.c`, the IOS emulation.

Before a step: name every SDK function it covers. Most GX/OS/DVD/NAND/WPAD/VI functions are named
in `config/symbols.txt` (GX 111, OS 87, DVD 21, ...); AX, PAD and parts of KPAD are not yet and
must be identified first (the decomp's symbol map, SDK code patterns).

Each step: done when the game no longer touches the hardware for it (an MMIO access to that block
is fatal in a test build) and the deterministic replay (below) matches.

## Track B, priorities

Ordered by what the user wants to change: players (dAcPy_c / daPlBase_c), camera (dBg / scroll -
needed for the 4:3 rework anyway), the 8-player module (in progress), menus and layouts, saves,
world map, then enemies/objects as needed.

**The memory catch:** as long as any recompiled function touches an object, that object must stay
in guest memory in the Wii's big-endian layout. So decompiled code first works on guest structs
through typed accessors (generated from the class layouts), which is readable but not yet native
memory. Native structs/pointers become possible per subsystem once nothing recompiled touches it -
the endgame, not the start.

## How changes are verified

The deterministic mode (`rt_det.c`: virtual clock, latched inputs, state hash) is the test bench
for both tracks: record a play session's inputs once, replay it with the old and the new
implementation, compare state hashes field by field. A native function that differs is found at
the field where it first differs. This is worth keeping even while online play is paused.

## Online play

Rollback and save states snapshot the whole game by copying guest memory and the runtime's state
sections. Track A moves state out of guest memory into native structures (threads, the renderer,
audio, I/O), and track B eventually does the same for game objects - each of those breaks
snapshots unless it is made serialisable. Decision (user): online play may be taken apart.
Proposal: online play is switched off (code kept, not maintained) while track A runs; it comes
back on the native base, rebuilt with explicit save/load of game state rather than memory copies.
Input recording/replay for testing stays.

## Who does what

Proposal: instance 1 takes track A (platform); instance 2 continues track B (the 8-player code,
then game classes). Both keep `hle_funcs.txt` / build lists in sync and note changes in CHANGELOG.

## Status (2026-10-16, instance 1)

| step | state |
|---|---|
| A1 GX | FIFO / CP / PE / PI native (rt_gx.c); draw-done / token are native events. The command stream itself stays (inline vertex writes, model display lists). |
| A2 OS | interrupt controller, MI, PI, IPC registers, VI native (rt_os.c, rt_vi.c). Threads / alarms still the recompiled OS on fibers (decrementer = a host deadline). |
| A3 disc / saves | DVD reads (rt_dvd.c) and the whole IOS client (rt_ios.c) native: no IPC hardware. |
| A4 input | SI / GameCube pads native (rt_si.c). WUD native (rt_wiimote.c): the Wii Remotes hand HID reports to the SDK's WPAD directly; the Bluetooth stack (BTA/BTM/L2CAP/HCI, rt_bt.c) no longer runs. |
| A5 audio | AI + DSP native (rt_audio.c): DSP model + AX mixing (rt_ax.c), audio DMA timer. |
| EXI | RTC / SRAM native (rt_exi.c). |
| A6 | Done: the register emulation (PI, VI, DSP/AI, EXI, SI, IPC, CP/PE) is deleted; `rt_hw.c` keeps the field clock and the GX write-gather pipe. `RT_MMIO_STRICT=1` makes any other register access fatal, `RT_MMIO_INVENTORY=file` lists them. Remaining "emulated" pieces: the GX command stream (vertices, model display lists) and the OS on fibers with a decrementer deadline. |

## Status, track B (2026-10-17, instance 2)

Method and tools in `docs/DECOMP.md`: `runtime/gm.h` (typed guest-memory accessors, objects stay
big-endian in guest memory; loop back-edges mirrored with `GM_LOOP()` so the deterministic clock
stays the same), `runtime/gm_verify.c` (`RT_GM_VERIFY=1` runs the PowerPC version alongside and
compares, `RT_GM_VERIFY=orig` is the "before" of an A/B replay with one binary, `RT_GM_SELFTEST`
calls every function with random inputs), `RT_DET_HASH_LIVE=1` in `rt_det.c` (the state hash
without thread stacks / saved contexts). Done: the module's save data and session info -
`dMj2dGame_c` (48), `dMj2dHeader_c` (8), `dSaveMng_c` (5 of 13), `dInfo_c` (6), in
`gm_mj2d_game.c`, `gm_mj2d_header.c`, `gm_save_mng.c`, `gm_info.c`; the player manager
`daPyMng_c` (38 of 39, `gm_py_mng.c`, 2026-10-28); the demo manager `daPyDemoMng_c` (7 on, 19
written but off until a test reaches a goal pole, `gm_py_demo.c`, 2026-11-04). All register-exact
with the PowerPC frames (`gm_i2.h`), strict A/B clean. Next: a level-end test input,
`dGameDisplay_c`, the rest of the module, then the player classes, then camera / scroll.
