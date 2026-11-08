# Decompiling the game code (track B)

Track B of `docs/NATIVE_ROADMAP.md`: the game's own code becomes readable C, class by class,
replacing the recompiled PowerPC translation (`fn_XXXXXXXX`, `mod_fn_...`). The goal is source
someone can read and change, that does exactly what the game did.

Files: `runtime/gm.h` (the conventions below), `runtime/gm_verify.c` (testing),
`runtime/gm_<class>.c` (one per class or close group of classes).

## How a function is replaced

1. Find its recompiled name. Game functions: `fn_<address>` (USA rev 2), or the symbol name.
   The 8-player module's: `mod_<name>` without the `_<module address>` suffix, e.g.
   `mod_fn_800CE060` for `mod_fn_800CE060_8180D094` (the module's replacement of the game's
   `800CE060`). `python3 tools/mod_class_funcs.py <class>` lists a class's module functions
   with their recompiled names, sizes and source names (from `linked/mod_source_names.json`).
   The recompiled bodies are in `out/recomp_*.c` (`grep -n "void mod_fn_800CE060_" out/*.c`).
2. List the name in `runtime/hle_funcs.txt` under a `# track B: <class> (<file>)` heading. The
   recompiler then calls `hle_<name>(ctx, base)` and keeps its translation as `orig_<name>()`.
3. Write the class in `runtime/gm_<class>.c`:
   - readable functions (`dMj2dGame_getCoin(self, player)`), named after the class and its
     source names (NSMBW-Decomp for the game, PAL addresses ported with our address map;
     mkwcat's nsmbw-project for the module);
   - the field offsets as named constants, each checked against the recompiled code that reads it;
   - at the end, the entry points: `GM_HLE_VOID(name, lo, len) { ... }` or
     `GM_HLE_INT(name, lo, len) { GM_RET(...); }` that take the PowerPC arguments
     (`GM_ARG(0)` = r3 ...) and call the readable functions. `[lo, lo + len)` is the memory the
     call may change (for the verifier).
4. Add the file to `build.py` (`RUNTIME`) and `build_linux_clang.sh` (just before `rt_plat_*`).

## Objects stay in guest memory

As long as any recompiled function still touches an object, it stays where the game put it, in
the Wii's big-endian layout: decompiled code reads and writes it through `gm_u8/u16/u32/s8/...`
(`gm_u32(self + MJ2D_SCORE)`), never through a native struct. Native structs come per subsystem
once nothing recompiled is left touching it. Variables of our own go in guest memory or in an
`RT_STATE_FILE` file, so save states and rollback keep working.

## Exactness

The deterministic replay (`RT_DETERMINISTIC=1`) must stay identical, so a decompiled function
must do what the PowerPC code did, to the bit:

- **The same memory writes and return value.** Sign or zero extension as the PowerPC code leaves
  r3 (`lbz` -> zero-extended, `extsb` -> `gm_s8`), 32-bit wrap-around of `mulli` / `rlwinm`
  address arithmetic, signed vs unsigned compares as the code has them (`cmplw` vs `cmpw`).
  Bugs are kept: the module's `std::bitset<70>` sets a bit in all three words, so ours does too.
- **The same guest calls, in the same order.** A function not decompiled yet is called with
  `GM_CALL(address, n, args...)` (or `GM_VCALL` for a virtual call); it keeps its own polls.
- **The same number of loop back-edges.** The recompiled code polls (`PPC_POLL`) on every loop
  back-edge, and in deterministic mode every 256th poll advances the virtual clock and may
  deliver an interrupt. A decompiled loop calls `GM_LOOP()` as often as the PowerPC loop branches
  back: a counted loop (`mtctr` / `bdnz`) of n iterations branches back n - 1 times, so the loop
  ends `if (i < n - 1) GM_LOOP();`. Not only loops: *any* branch to a lower address polls - the
  compiler sometimes places an `if`'s other half above it, so a plain `goto` back polls once
  (`dInfo_c::initStage` has two). Read the recompiled body for where the `PPC_POLL()`s are.
- **Addresses from the code, computed by a script.** (`python3 -c "print(hex(0x80330000 - 27048))"` - CHANGELOG 38: six vtable addresses worked out by hand were wrong.) Then `python3 tools/gm_check_consts.py` flags any address constant the recompiled code never uses.
- **Addresses from the code, computed with care.** `lis r3, 0x8043; addi r3, r3, -24200` is
  `0x80430000 - 0x5E88 = 0x8042A178` (the `addi` is signed). Three of `dInfo_c`'s globals were
  first wrong this way, and one array offset: the self-test showed two, rechecking every
  constant found the third.

- **The same non-volatile registers at each call.** Before calling another function the PowerPC
  code often holds its own values in r14-r31 (the callee saves them into its frame). Those dead
  stack words can end up in the heap later (the game copies uninitialised locals), so a native
  should put the same values into `ctx->r[N]` before a nested call and restore the entry values
  on return - see `NV_KEEP` in gm_bg.c (CHANGELOG 37: 4 heap words differed without it). Also
  set `ctx->lr` to the PowerPC return address before calling another native directly.

What a native function changes differently, harmlessly: the guest stack below the stack pointer
(the PowerPC version's frame, dead after it returns) and volatile registers saved in a thread's
context at a switch. `RT_DET_HASH_LIVE=1` leaves both out of the state hash, and the SDK's private stacks
(OSSwitchFiber, 4 KB each: the Wii remote libraries' alarm handlers, `rt_det.c`).
One more, rarer: the game sometimes copies an uninitialised local into an object, so a dead
stack word the PowerPC version left (a back-chain pointer) can show up for a field in a heap
object, where the native version leaves 0. That is a single-field difference in the A/B hashes
that heals at once; check it with `RT_DET_DUMP_AT` / `RT_DET_PEEK` (a stack address vs 0) rather
than accept it blindly. Once many functions are native such words can persist (an object
lives on with the copied word), and then the hashes never match again: compare the whole memory
instead - `RT_DET_DUMP_AT=F RT_DET_DUMP_MEM=1` in both runs, then
`python3 tools/memdiff.py before.hash.mem after.hash.mem after.hash.pages`. A handful of words,
each a code address (a saved LR) in the PowerPC run, at a late field, means the game never read
them; anything else is a real difference.

## Testing

Two checks, both with the same binary:

- **Function by function:** `RT_GM_VERIFY=1` (or a comma list of names) runs the PowerPC version
  of each decompiled function first, on the same registers and memory, with interrupts held off;
  then puts the memory back and runs the decompiled one. Return value, memory `[lo, lo + len)`
  and poll count must agree; differences go to the `gm` log with the arguments (first 10 per
  function), and the totals are printed at exit:
  `gm: verified mod_fn_800CE0F0    1234 calls, 0 different`. `RT_GM_VERIFY_FATAL=1` stops at
  the first difference.
- **Every function, with random inputs:** `RT_GM_SELFTEST=1` (or class tags: `mj2d`) makes a
  class's file call each of its entry points with random arguments in range and random object
  contents, against the PowerPC version, once - the first time the game uses the class (the object,
  the options it reads and the poll counter are put back afterwards). This reaches the functions
  a test run doesn't: `dMj2dGame_c` runs 400 rounds of all 48. A self-test changes nothing the
  game sees, but it isn't meant for deterministic comparisons.
- **What a range must cover.** The PowerPC version runs first and its writes inside the ranges
  are put back; writes outside them stay. So the ranges have to cover everything the function and
  the guest functions it calls change (a guest call that sets a value is harmless twice, one that
  counts is not), and the self-test randomises those same ranges.
- **Inputs that play:** `RT_AUTOPRESS` masks are Wii Remote core bits: 2 = `100`, 1 = `200`,
  d-pad down = `004` (right with the remote sideways); `001` is d-pad left. Our title menu takes
  only 2 or A. Start: `100` (2) every 2 s from 8 s to 66 s (title -> Single player -> Game Select
  -> 1-1), then `70:204:300000` (right + run held) and a jump `:100:350` every 1.3 s from 71 s -
  deaths, restarts, stomps, coins. Add `RT_UPDATE=0`. `RT_WARP=w,l,a,e` (0-based) swaps the first
  level started (`3,0,0,0` = 4-1). The old sequence with mask `1` never leaves the title: it only
  runs the title's demo plays (real levels with enemies - a useful second test).
- **Stack frames:** a native function must leave the guest stack as the PowerPC code would:
  the game copies uninitialised stack words into the heap and keeps stack addresses. Start each
  decompiled function with `GM_FN(address)` (gm.h): it pushes the PowerPC frame and replays its
  prologue - the saved LR (`ctx->lr` at entry), saved GPRs / FPRs / `psq_st` - from the table in
  `runtime/gm_prologue.c`, and pops it on every return. That table is generated:
  `python3 tools/gm_prologues.py` reads the prologues from `out/recomp_*.c` for the addresses
  named in `FN(` / `GM_FN(` lines - rerun it after adding functions or a module (a missing address
  logs `GM_FN: no prologue for X`; extend `RANGES` in the script for a new address range).
  `GM_FRAME(n)` pushes a bare frame of n bytes. What is still not exact: a native's own locals,
  and a guest function called with `GM_CALL` saves LR = 0 instead of the real return address.
- **The 8-player module patches some functions at entry** (`if (g_mod_on) { mod_X(...); return; }`
  at the top of the recompiled body). Replacing such a function with `GM_HLE` silently turns the
  module's version off. `python3 tools/check_hle_mod.py` lists the hle'd functions whose body
  starts with that handover; each must call the module itself when `g_mod_on` (see
  `gm_s_state.c`: `fn_8015F910`, `fn_8015FC10`).
- **Which functions to switch on:** only those a test run reaches. To find them, redefine
  `GM_HLE` for a moment in the file so each entry logs its first call to a file (see CHANGELOG
  36), put all names in `hle_funcs.txt`, run the three inputs, keep the reached ones (and empty
  bodies), list the rest in the file as written but off.
- `GM_CALL(f, n, ..., GM_CALL(...))` doesn't compile: a macro isn't expanded inside itself.
- **Finding which native causes a blip** (part 42): patch `GM_HLE` in gm.h for the session
  (don't commit it) so each entry can fall back to its PowerPC version at run time:
  `#define GM_HLE(name) __attribute__((weak)) void orig_##name(ppc_context *, uint8_t *); static void gmb_##name(ppc_context *, uint8_t *); void hle_##name(ppc_context *ctx, uint8_t *base) { static int off_ = -1; if (off_ < 0) off_ = gm_off_(__FILE__, #name); if (off_ && orig_##name) { orig_##name(ctx, base); return; } gmb_##name(ctx, base); } static void gmb_##name(ppc_context *ctx, uint8_t *base)`
  with `gm_off_` matching `RT_GM_OFF` ("all", or a comma list of file and function names). One
  build, then bisect with ~100 s runs against base0 (`RT_DET_DUMP_AT` at the blip's field shows
  the words). Natives call each other directly, so turning an entry off only reroutes the calls
  from recompiled code: bisect by file first. Part 42 found this way: gm_s_state.c (no NV mirror,
  LR = 0, the module's sStateID_c::number inlined instead of called, a missing frame) behind the
  4359 / 5191 blips, gm_f_base.c (the packs didn't copy their pointers to member functions to the
  stack) behind 1984-1985, and a tools/gm_prologues.py bug (below).
- **gm_prologues.py and r0:** a prologue's `mflr r0; stw r0, ...` is the LR save; until part 42
  the scanner kept treating r0 as LR after it was reloaded, so a later store of r0 (data the
  function copies to its frame before its first call) was replayed as the LR: 16 functions had
  wrong words in their replayed frames. Fixed.
- **Volatile registers:** a callee can store a volatile register it never set (a variadic
  function spills r3-r10; nw4r's animation results copy uninitialised stack words), so in the
  hottest paths a native leaves the callee's volatile registers as they come back (no
  save / restore around the call) - see fBase_commonPack's ptmf_scall. GM_CALL / GM_CALLR restore
  r0-r12 after the call; the single-word blip left in 1-1 (field 863, a ChrAnmResult's unused
  rawR.z, 1.0 vs 0) is this kind of residue.
- **`GM_CALLR(ra, f, n, ...)`** (gm_nv.h) is GM_CALL with LR = the PowerPC return address (the
  `ctx->lr = 0x...` before the call in out/recomp_*.c) instead of 0: a callee with a frame saves
  LR, and that dead stack word can be copied later (part 41: a heap's adjust, called from
  mHeap::adjustFrmHeap, left 0 where the game had 0x8016E790 - a 2-field blip in 1-1). Tail
  calls: `GM_CALLR(ctx->lr, ...)`. Use it in new code; `tools/gm_callr.py file.c` converts the
  unambiguous GM_CALLs of a file (part 41 ran it on instance 1's older files).
- **Register-exact natives, `RT_GM_VERIFY_REGS=1`** (part 44): with `RT_GM_VERIFY=<list>` it also
  compares every register the PowerPC version leaves (r0-r31, FPRs, ps1, CR, LR, CTR, XER) and logs
  the first one that differs. New natives - leaves especially, they are called the most - pass it:
  mirror the last compare's CR field (cror bits included), the record forms' CR0, XER[CA] of
  addc / subfic, the temporaries in r0 / r4-r12 / f0-f13 and both paired-single halves (lfs and
  single arithmetic set both, fmr / fneg / fabs / frsp / lfd only ps0); a framed function ends with
  r0 = its entry LR (the epilogue's reload). Guest calls whose registers are the result:
  **`GM_CALLV(ra, f, n, ...)`** (no save / restore) and **`GM_TAIL(f, n, ...)`** (b f). See
  gm_s_lib.c / gm_c_lib.c. The older natives fail it (to be fixed: TODO).
- **Verifying a native whose calls change memory outside its ranges** (layout / animation calls):
  RT_GM_VERIFY runs the PowerPC version and then the native, so those calls happen twice - the
  memory compare is meaningless there, but the register compare still holds where the second run
  sees the same state. gm_d_wipe.c builds that way with `-DGM_WIPE_VERIFY` (compile that one file
  with it, link a separate test binary); its draws can't be verified at all (a layout entered
  twice stalls the game). Poll-count differences in such runs come from the doubled animation.
- **ps1 of f14-f31 leaks** (part 48): the PowerPC code saves an FPR with stfd / lfd (ps0 only), so
  the second half comes back as the callees left it and the caller sees that. GM_NV_KEEP restores
  ps1 only for the FPRs the original prologue saves with psq_st (needs GM_FN for that function);
  a native that loads an FPR it keeps must set both halves as lfs would (NV_FL). Finding a word
  written differently: `RT_DET_WATCH_AT=<field> RT_DET_WATCH=<page> RT_DET_WATCHW=<word>` (rt_det.c)
  logs each write to it with a backtrace and registers; compare base and build.
- **Instance 2's natives (`gm_i2.h`)**: the module classes (gm_mj2d_*.c, gm_save_mng.c, gm_info.c,
  gm_py_mng.c) are register-exact the same way, with a few helpers: `CMPS` / `CMPU` (compares into
  CR0), `NONZERO(t, d, v)` (addic / subfe), `SRAWI31`, `BL(ra, fn)` (a call as bl: LR = the return
  address, the callee's registers are the result - natives call other natives through their
  `hle_` entries with the registers set, so the callee's residue is the PowerPC one) and
  `I2_FN(addr)` (GM_FN + GM_NV_KEEP + r0 = LR at the end). Loops that keep their state in
  r25-r31 keep it there (`NV_R`) whenever they call out, so callees save the same words.
  `RT_GM_VERIFY=<list>` with long lists works (the list buffer is 16 KB; it was 1 KB, and names
  past it were silently not verified), a call may give up to 16 ranges, and a self-test entry
  whose letters start with `!` is a static function (the letters start at r3).
- **Guest calls that draw random numbers** (dGameCom::rnd / rndInt, cRandom_c at 0x80429F44) are
  state too: the verify's double run draws twice and the second draw differs, so a function that
  shuffles (daPyDemoMng_c::genCourseInList) lists the random state as one of its ranges.
- **Natives whose virtual calls change the world** (daPyMng_c::update, executeLastPlayer /
  executeLastAll: each player's frame) can't be verified call by call - the double run plays the
  players twice; their test is the A/B.
- **Test with no input too**: the attract demos (title left alone, ~19,000 fields) reach enemies and models the recorded inputs don't (part 55 found a divergence and 11 blips there). Run it in every A/B.
- **Parallel A/B runs need separate game roots**: the runs rewrite nand/shared2/sys/SYSCONF, so two copies started together from one root can boot from different SYSCONF contents (a difference from field 1, part 52). Give each its own root - links to recomp/'s files plus a fresh copy of nand/.
- **A computed `GM_FN` address** (`a = end ? 0x... : 0x...`) needs `/* FNADDR */` on the line holding the addresses too (part 51: three functions ran frameless and blipped 1-1 until marked). Check every A/B log for "GM_FN: no prologue".
- **`GM_FN(x)` with an address that isn't a literal on that line** (a table, a parameter): mark
  the line(s) holding the addresses `/* FNADDR */`, or tools/gm_prologues.py won't generate their
  prologues (the log says "GM_FN: no prologue for ..." and no frame is pushed).
- **Plain `GM_HLE`** functions run decompiled even with `RT_GM_VERIFY=orig`: their A/B baseline is
  a build without them in `hle_funcs.txt` (`BUILD_TMP=/tmp/base ./build_linux_clang.sh`).
- **The strict A/B (instance 1's files, 2026-10-18):** `RT_GM_VERIFY=orig` doesn't remove a
  native's side effects on the stack, so compare against a build with none of the files at all:
  cut `hle_funcs.txt` before the line `# track B (instance 1): cLib ...`, drop
  `gm_c_list gm_f_list gm_f_base gm_f_manager gm_s_state gm_d_base gm_d_actor gm_d_enemy gm_d_enemy_death gm_d_enemy_carry gm_bg gm_m3d gm_m3d_scene gm_m3d_anm gm_m_mtx gm_m_heap gm_m_allocator gm_m_fader gm_d_cc gm_m_2d gm_m_frustum gm_state_ids` from the
  runtime list (their `orig_` names don't exist without the hle entries), build it to another
  `BUILD_TMP`, then run both with the same inputs and compare the per-field hashes and the memory
  (`RT_DET_DUMP_AT`, `tools/memdiff.py`). Part 35's result (1-1 to field 15 778, title demos to
  18 184): memory identical at field 12 000, hashes identical but for a few single fields that
  heal (a module quicksort that reads uninitialised stack floats, and the LR = 0 above). This A/B
  found two real bugs the per-function verifier could not (see CHANGELOG 35).
- **The whole game:** a deterministic run with fixed inputs (`RT_AUTOPRESS`), once with
  `RT_GM_VERIFY=orig` (the PowerPC versions run instead: the "before") and once without (the
  decompiled versions), both with `RT_DET_HASH=file RT_DET_HASH_LIVE=1`. The per-field hashes must
  match field for field.

```sh
P="$(tr -d '\n ' < inputs.txt)"
env NSMBW_RENDERER=null RT_DETERMINISTIC=1 RT_DET_UNPACED=1 RT_UPDATE=0 RT_AUTOPRESS_FRAMES=1 \
    RT_AUTOPRESS="$P" RT_DET_HASH_LIVE=1 RT_DET_HASH=before.hash RT_GM_VERIFY=orig ./nsmbw_linux game
env ... RT_DET_HASH=after.hash ./nsmbw_linux game
cmp before.hash after.hash
```

`RT_GM_VERIFY=orig:name,...` instead runs only the listed PowerPC implementations and leaves every
other native enabled. Use this to isolate world-changing functions without double-invoking them.
`RT_AUTOPRESS_FRAMES=1` makes the autopress times count game-frame seconds (the usual `8`, `10`, ...
script stays in those units). **Part 71's frame-4900 replay was a false positive:** it entered
`StateID_DemoDown` before reaching the world map, so it tested death, not a clear. The corrected,
repeatable genuine 1-1 clear (from `recomp/`) is:

```sh
P=""
for t in $(seq 8 2 32); do P="${P}${P:+,}${t}:100:300"; done
P="${P},60:204:300000"
export NSMBW_RENDERER=null RT_DETERMINISTIC=1 RT_DET_UNPACED=1 RT_UPDATE=0
export RT_AUTOPRESS_FRAMES=1 RT_AUTOPRESS="$P"
export RT_TEST_POS="2700,6640,-560"
timeout 40s ./out/nsmbw.exe game
```

On Windows the game log is `nsmbw_log.txt` in the same directory. The warp leaves right+run unheld
until frame 3600 so the camera (initially around x=603) can catch up and load `EN_GOALPOLE` at frame
3645. `setDemoGoal` follows at frame 3655 with the player at `(6698.2, -592.0)` and the castle at
x=6944; pole, jump, pose, castle, `ProcGoalSettleUp`, `ProcGoalEnd`, and the world-map transition
from `8005C648` then occur without `StateID_DemoDown`. The opt-in position hook sets both current
and last positions. A bounded scroll-limit hold, active only for this test's frame window and only
before the goal demo starts, permits that camera catch-up; normal scrolling resumes at the goal or
after 1200 frames. Assist-mode settlement still needs a separate input.

The verifier catches what it should: a sign-extension slip in `getCoin` (`gm_u8` for `gm_s8`)
showed as 92 of 400 self-test calls different, a missing `GM_LOOP()` in
`getTotalWorldCollectCoin` as "83 polls (PowerPC 125)" on every call.

**Floating point.** Use the recompiler's primitives from `ppc_context.h`: `ldfs(base, a)` /
`stfs(base, a, d)` for float loads and stores and `frsp(x)` around each single-precision
operation (`fadds a, b` is `frsp(a + b)` on doubles; `fmadds` is `frsp(a * c + b)`, written as
one expression, as the recompiler writes it). Then the results match bit for bit. Comparisons
(`a < b`) behave like `fcmpu` (false with a NaN).

**Addresses from NSMBW-Decomp's slices** (`slices/wiimj2d.json`, `.text` offsets): add
0x80006780 for this game (USA rev 2) - e.g. d_base.cpp's 0x65CA0 is dBase_c's constructor at
0x8006C420. Then check against the recompiled names (`out/recomp_table.c`) and the module's replacements (`linked/mod_patches.json` "replace").

## Status

| Class | File | Functions | Verified |
|---|---|---|---|
| `dMj2dGame_c` (module: a save slot, 8 players) | `gm_mj2d_game.c` | all 48 | 2026-10-17; register-exact with frames 2026-10-28 |
| `dMj2dHeader_c` (module: the save file header) | `gm_mj2d_header.c` | all 8 | 2026-10-17; register-exact 2026-10-28 |
| `dSaveMng_c` (module: construction, slots, live-state serialization, ordinary / multi-mode / quick NAND saves and loading) | `gm_save_mng.c` | **all 13 on** | 2026-11-08: Part 81 completed the eight remaining methods and folded prepareSave's singleplayer adjustment into native code. Directed save-start A/B matched all 1,376 events, prepareSave A/B matched all 1,368, and final clean A/B matched all 1,367 |
| `dInfo_c` (module's functions: session info) | `gm_info.c` | all 6 the module replaces | 2026-10-17; register-exact with frames 2026-10-28 |
| `daPyMng_c` (module: the player manager - entries, characters, lives / coins, Yoshis, star music, update, incCoin, course spawning, the ground-pound quakes; instance 2) | `gm_py_mng.c` | **all 39 on** | 2026-11-08: Part 77's createCourseInit native / PowerPC A/B matched all 1,367 events; earlier methods used register-exact verification, self-tests and strict input A/Bs |
| `daPyDemoMng_c` (module: the players' demo manager - course-in / course-out / goal lists, goal / control demos and stage-start toride; instance 2) | `gm_py_demo.c` | **all 27 on** | 2026-11-07: Part 73 fixed calcNotGoalPlayer's key-flag address and ported executeGoalDemo_Pole; both clear A/Bs match all 1,367 events. Part 74 enabled the nine control-demo / toride methods. Directed live-player calls covered all nine; strict query checks found no differences, and the isolated native / PowerPC A/B matched all 1,129 gameplay / scene / state / test events |
| `dGameDisplay_c` (module: the in-game HUD; instance 2) | `gm_d_gamedisplay.c` | **all 29 on** | 2026-11-08: Part 79 completed 1-up effects, grayscale colours and Star Coin display. Directed native / PowerPC A/B matched all 1,371 ordinary and test events; final clean A/B matched all 1,367. Earlier methods used register-exact self-tests and isolated A/Bs; setTime / rest-coin call paths still need directed input |
| `dfukidashiManager_c` (module: the eight speech-bubble layouts and their session-info flags; instance 2) | `gm_d_fukidashi.c` | **all 9 on** | 2026-11-08: Part 77's ordinary native / PowerPC A/B matched all 1,367 events; directed value and flag calls covered the three otherwise unreached methods and matched on both implementations |
| `dfukidashiInfo_c` (module: one 572-byte speech-bubble child layout; instance 2) | `gm_d_fukidashi_info.c` | **all 6 on** | 2026-11-08: Part 78's final ordinary native / PowerPC A/B matched all 1,367 events; directed calls covered every method and two movement-counter branches with no declared-memory or full-register differences |
| `dGameCom` (module: score creation, speech bubbles, player colours / entry and course-clear queries; instance 2) | `gm_d_gamecom.c` | **all 6 on** | 2026-11-08: Part 80's directed native / PowerPC A/B matched all 11 test events, including all eight player slots and real HUD / window colouring; strict query register checks found no differences; final clean A/B matched all 1,367 events |
| `cLineMg_c` / `cTreeNd_c` / `cTreeMg_c` (cLib lists and trees; instance 1) | `gm_c_list.c` | 10 | 2026-10-17 |
| `fLiMgBa*` / `fLiNdBaLink_c` / `fTrMgBa*` (framework lists of bases; instance 1) | `gm_f_list.c` | 8 | 2026-10-17 |
| `fBase_c` (the base of every actor / scene; instance 1) | `gm_f_base.c` | 28 | 2026-10-17 (A/B + memory compare) |
| `fManager_c` (the main loop, searches; instance 1) | `gm_f_manager.c` | 5 | 2026-10-17 (A/B + memory compare) |
| `sStateID_c` / `sStateMethod_c` / `sStateMethodUsr_FI_c` (state machines; instance 1) | `gm_s_state.c` | 20 | 2026-10-17 (A/B + memory compare) |
| `dBase_c` / `dBaseActor_c` (the base of every actor; instance 1) | `gm_d_base.c` | 35 | 2026-10-17 (A/B + memory compare) |
| `dActor_c` (lifecycle, construct, kinds, tables, deleteActor, player search, zone checks, carry ...; instance 1) | `gm_d_actor.c` | 42 of ~70 (+14 written, off) | 2026-10-17 (A/B + memory compare) |
| `dEn_c` (the enemy base: movement, collision dispatch, stomps, ground / walls, liquids, carry ...; instance 1) | `gm_d_enemy.c` | 44 of 76 (+28 written, off; 4 are the module's) | 2026-10-17 (A/B + memory compare, 0 differences) |
| `dEn_c` death and states (hitCallback_*, setDeathInfo_*, Die* / Ice / Eat* states, the state-ID template, dEnCombo_c; instance 1) | `gm_d_enemy_death.c` | 42 of 82 (+40 written, off) | 2026-10-18 (strict A/B + memory compare) |
| sFStateVirtualID_c<T> / sFStateID_c<T> - every class's copy (state calls, root, number, isSameName, destructors; instance 1) | `gm_state_ids.c` (generated by `tools/gm_state_ids.py`) + `gm_state_ids_impl.h` | 2946 | 2026-10-18 (strict A/B + memory compare) |
| `dEnemyCarry_c` (carryable enemies; instance 1) | `gm_d_enemy_carry.c` | 0 of 11 (all written, off: not reached) | - |
| background tile lookups (dBc_c::getUnitType / Kind, dBgGm_c units, TilemapClass; instance 1) | `gm_bg.c` | 16 | 2026-10-18 (strict A/B + memory compare) |
| mLib m3d - banm_c / fanm_c, calcRatio_c, bmdl_c / smdl_c / mdl_c (+ its calc-world callback), scnLeaf_c (instance 1) | `gm_m3d.c` | 68 | 2026-10-18 (strict A/B + memory compare) |
| mLib m3d - the scene (m_3d.cpp: create, light / fog managers, calcWorld / calcView / draw, pushBack, proc_c; instance 1) | `gm_m3d_scene.c` | 28 of 29 (+1 written, off) | 2026-10-18 (A/B + memory compare) |
| mLib m3d - animations (banm_c base, anmChr_c, anmChrBlend_c, anmVis_c, anmMatClr_c / anmTexPat_c / anmTexSrt_c - one implementation for the three; instance 1) | `gm_m3d_anm.c` | 73 of 87 (+14 written, off) | 2026-10-18 (A/B + memory compare) |
| mLib mMtx_c / mVec3_c (rotations, toRot, normalize, rotX / rotY; instance 1) | `gm_m_mtx.c` | 13 of 18 (+5 written, off) | 2026-10-18 (A/B + memory compare) |
| mLib mHeap (exp / frame / unit heaps, costs, adjust, the game heaps; instance 1) | `gm_m_heap.c` | 19 of 21 (+2 written, off) | 2026-10-18 (A/B + memory compare) |
| mLib allocators (mAllocatorDummyHeap_c, mAllocator_c, mHeapAllocator_c; instance 1) | `gm_m_allocator.c` | 26 of 28 (+2 written, off) | 2026-10-18 (A/B + memory compare) |
| mLib faders (mFader_c, mFaderBase_c, mColorFader_c but its draw; instance 1) | `gm_m_fader.c` | 12 of 14 (+2 written, off) | 2026-10-18 (A/B + memory compare) |
| `dCc_c` collision (list, checkCollision / execute, the box / loop / circle / box-circle checks; instance 1) | `gm_d_cc.c` | 19 of 24 (+5 written, off; trapezoid checks still recompiled) | 2026-10-18 (A/B + memory compare) |
| mLib m2d (the layout draw list, FrameCtrl_c, ResAccIf_c, Simple_c, AnmResV2_c, AnmGroupBase_c; instance 1) | `gm_m_2d.c` | 25 of 33 (+8 written, off) | 2026-10-18 (A/B + memory compare) |
| mLib mFrustum_c (set x2, intersectSphere / intersectAABB; instance 1) | `gm_m_frustum.c` | 4 | 2026-10-23 (A/B + memory compare; the set()s register-exact) |
| mLib mColor::lerp (instance 1) | `gm_m_color.c` | 0 of 1 (written, off: not reached) | - |
| `dCdFile_c` course data lookups / range checks (instance 1) | `gm_d_cd.c` | 24 of 25 (+1 written, off) | 2026-10-23 (register-exact verify + A/B) |
| `dActorCreateMng_c` creating the course actors (instance 1) | `gm_d_actorcreate.c` | 18 of 22 (+4 written, off) | 2026-10-23 (A/B + memory compare; register-exact verify of 4) |
| The layout wipes dWipeCircle_c / Dokan / Kuppa / Mario (calc, draw, set-ups, end check, setStatus, fades) and mWipeFader_c (instance 1) | `gm_d_wipe.c` | 32 of 35 (+3 mWipeFader_c written, off: not reached) | 2026-10-24 (A/B + memory compare; register-exact verify of 28 with `-DGM_WIPE_VERIFY`) |
| Score pop-ups dSmallScore_c / dSmallScoreManager_c (execute, draw, PosSet), the five-slot layout manager (0x8010C380), the 2D GX state keeper (0x80014330; instance 1) | `gm_d_smallscore.c` | 10 | 2026-10-24 (A/B + memory compare; register-exact verify of 7 with `-DGM_SS_VERIFY`) |
| dSys_c (the frame driver execute(), render / frame helpers, setBlack, clear colour, frame rate, effect heaps, dylink phases) and dScene_c (the scene base, createNextScene, fades; instance 1) | `gm_d_scene.c` | 29 (create / manager phases / setNextScene not here) | 2026-10-24 (A/B + memory compare) |
| `dNext_c` scene changes through next-gotos (instance 1) | `gm_d_next.c` | 9 of 11 (+2 written, off: changeScene / deleteInstance; execute is the module's) | 2026-10-24 (A/B; register-exact self-test `RT_GM_SELFTEST=next` of 7: random next data / positions on the live course) |
| `LytBase_c` (m2d::EmbedLayout_c) layout animations: start / loop / reverse / end set-ups, AnimePlay, isAnime / isAllAnime (instance 1) | `gm_d_lytbase.c` | 9 (the rest: gm_d_lytbuild.c) | 2026-10-26 (register-exact verify of 8 + A/B) |
| `LytBase_c` - ctor / dtor, build, resources, pane registers, AnmResV2_c / AnmGroup_c array pieces, SetScissorMask, doDelete (instance 1) | `gm_d_lytbuild.c` | 21 (+ 1 element destructor off) | 2026-10-29 (register-exact verify + A/B) |
| `LytTextBox_c` - setMessage / setText (instance 1) | `gm_d_lyttextbox.c` | 5 | 2026-10-29 (register-exact verify + A/B) |
| `dMessage_c` / `MsgRes_c` - the message archive (instance 1) | `gm_d_message.c` | 11 (+ 2 destructors off) | 2026-10-29 (register-exact verify + A/B) |
| `dSelectCursor_c` - the menus' cursor (instance 1; execute / draw in `gm_d_smallscore.c`) | `gm_d_selectcursor.c` | 11 | 2026-10-29 (register-exact verify + A/B) |
| `dCoin_c::execute`, `dCurtainMng_c`, `dDvd` / `dDvd::loader_c` (instance 1) | `gm_d_misc.c` | 7 | 2026-10-30 (A/B) |
| `Util::FrameCounter_c` (instance 1) | `gm_d_util.c` | 0 (6 written but off: never called by the tests) | 2026-10-30 |
| nw4r::ut `List_*` / `detail::LinkListImpl`, `IsValidBinaryFile` (instance 1) | `gm_nw4r_ut.c` | 10 | 2026-10-30 (register-exact verify + A/B) |
| `EGG::ColorFader` (instance 1) | `gm_egg.c` | 5 (+3 written, off: setFrame / fadeIn / fadeOut never called) | 2026-10-30 (A/B) |
| nw4r g3d / math leaves from the call profile: ResMdl / ResMat / ResNode getters, Sin/CosFIdx, matrix copies, the texture / BP / fog / z-compare state writes, display list calls, Camera matrices, SetScnObjOption, list dispatches; MSL strcmp / memcmp / strncmp and libm sin / cos / tan, Camera projection matrices, ScnObj::SetMtx, lyt pane positions, mTexture_c, EGG::Vector3f::normalise, the 2D GX state setters (instance 1) | `gm_nw4r_g3d.c` | 130 (+1 written, off: EGG::Math<float>::sqrt, no hle_funcs.txt name) | 2026-10-30 (register-exact verify + A/B) |
| `dWmActor_c` (the world map actor base) and the `dCsvData_c` getters (instance 1) | `gm_d_wm.c` | 26 (+ 7 written but off: never called by the tests) | 2026-10-27 (register-exact verify + A/B) |
| `dScStage_c::getLoopPosX` (instance 1) | `gm_d_stage.c` | 1 | 2026-10-27 (register-exact verify + A/B) |
| `d2d` - the draw-list wrappers, `d2d::Multi_c`, `ResAccMult_c` (instance 1) | `gm_d_2d.c` | 18 (+ drawBtween off; constructors / the mod's ArcResourceAccessor pieces not) | 2026-10-27 (register-exact verify + A/B) |
| `dRes_c` - the archive manager, `dRes_c::info_c`, `dResMng_c` (instance 1) | `gm_d_res.c` | 26 (+ the 3 destructors / plain copyRes off) | 2026-10-27 (register-exact verify + A/B) |
| the rest of fBase_c / fManager_c / dBase_c / dBaseActor_c: default virtuals, post steps, the base matrix (instance 1) | `gm_f_base.c`, `gm_f_manager.c`, `gm_d_base.c` | 12 (+6 written, off) | 2026-10-26 (register-exact verify + A/B) |
| `dRail_c` rails (instance 1) | `gm_d_rail.c` | 1 of 7 (+6 written, off: no rail rides in the tests) | 2026-10-23 (register-exact verify + A/B) |
| sLib helpers (addCalc, addCalcAngle, chase*, chaseAngle*, sPhase_c, cCounter_c; instance 1) | `gm_s_lib.c` | 13 of 14 (+1 written, off) | 2026-10-23 (register-exact verify + A/B) |
| cLib helpers (addCalcPos, chasePos, targetAngle*, cM atan2s / random, cRandom_c, cOwnerSetMg_c; instance 1) | `gm_c_lib.c` | 16 of 19 (+3 written, off) | 2026-10-23 (register-exact verify + A/B) |

"Verified": the self-test (every function, 400 / 200 random rounds) with no difference, the real
game under `RT_GM_VERIFY=1` (boot, file select, world map, 1-1, a Toad house: 24 of the 48
`dMj2dGame_c` functions reached, about 32 000 calls) with no difference, and the A/B replay with
identical per-field hashes (20 584 fields for `dMj2dGame_c`). The containers (instance 1): `RT_GM_VERIFY=1` over 5400 frames
(boot to 1-1) with 0 of 114 M calls different; A/B replay 25 440 fields, identical but for two
single fields explained above (an uninitialised local).

The verifier's poll count leaves out polls an interrupt or another thread made during the call
(`ppc_poll_foreign`, `rt_core.c`), and it reads all ranges back before restoring any (ranges may
overlap).

The module's class list and what is native: `NATIVE_PORT.md` (`python3 tools/native_port_status.py`).
Next (roadmap order): the rest of the 8-player module - `daPyMng_c`, the rest of `dSaveMng_c`
(the NAND saves), then the menus' and world map's classes; then the player (`dAcPy_c` / `daPlBase_c`), then the
camera / scroll code.
