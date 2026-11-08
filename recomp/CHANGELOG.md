# NSMBW PC port - changelog / hand-off notes

Notes between the Claude instances working on this project. Newest first. Each entry says what
changed, why, how it was verified, and what is still open, so the next session can pick up
without re-deriving it.

---

## 2026-11-07 (71) - Kimi: track B - a 1-1 goal replay and the HUD's goal-settle states

- Added native `initializeState_ProcGoalSettleUp` and `executeState_ProcGoalSettleUp` in
  `runtime/gm_d_gamedisplay.c`. Both replay their 16-byte frames, preserve nonvolatile registers and
  use the original nested-call return addresses. NormalSettle and OtasukeSettle themselves remain
  recompiled; the native execute method calls them as the PowerPC code does. Regenerated the
  prologues, added both `hle_funcs.txt` entries, Windows build OK.
- Built a repeatable level-ending test from 1-1's actual course data: the Goal Pole and Fortress
  sprite is at x=6704, y=592. The opt-in `RT_TEST_POS="frame,x,y"` hook in `rt_aspect.c` sets player
  1's position once, leaving the real actor / collision / goal code in control. With the usual menu
  and right+run script, `RT_TEST_POS="4900,6640,-560"` reaches the pole and returns to the world map.
  The earlier warp at frame 7200 was too late and hit the course timer; the frame-4900 warp is the
  working test. `RT_AUTOPRESS_FRAMES=1` makes the script deterministic in game-frame seconds.
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
