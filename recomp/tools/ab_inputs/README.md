# A/B test inputs (instance 1's set, 2026-11-15)

Each file is one `RT_AUTOPRESS` value (`seconds:mask:ms`, comma separated; with
`RT_AUTOPRESS_FRAMES=1` the seconds are game-frame seconds; masks are Wii Remote core bits in hex:
`100` 2, `200` 1, `800` A, `400` B, `0010` plus, `1000` minus, `8000` HOME, `004` / `001` the
d-pad, right / left with the remote sideways). Common environment:

    NSMBW_RENDERER=null RT_DETERMINISTIC=1 RT_DET_UNPACED=1 RT_BOOT_KEYBOARD=0 \
    RT_AUTOPRESS_FRAMES=1 RT_UPDATE=0 RT_DET_HASH_LIVE=1 RT_DET_HASH=<out>.hash \
    RT_AUTOPRESS="$(cat <file>)" ./nsmbw_clang . <extracted>

with a fresh copy of the pristine `nand/` per run. Extra settings per input:

| input | file | extra |
|---|---|---|
| a - 1-1 played (runs right, jumps every 1.3 s: deaths, restarts, stomps, coins) | `a_1-1.txt` | - |
| b - the title's demo plays (mask 1 never leaves the title) | `b_title_demos.txt` | - |
| c - 4-1 played | `a_1-1.txt` | `RT_WARP=3,0,0,0` |
| d - no input (the attract demos) | `d_no_input.txt` | - |
| e - the 1-1 clear (instance 2's) | `e_1-1_clear.txt` | `RT_TEST_POS=2700,6640,-560` |
| hm - 1-1 with the HOME menu and the pause menu opened four times | `hm_home_pause.txt` | - |
| wm - the 1-1 clear, then the world map's menu, HOME, d-pad | `wm_world_map.txt` | `RT_TEST_POS=2700,6640,-560` |

Compare two builds' `.hash` files line by line (field, -, hash) over the shorter length; any
differing field is a difference. A run of 640 s wall time gives about 28,000-55,000 fields.

## More inputs (instance 2's set, 2026-11-18)

Picked by function coverage: a coverage build (every recompiled function's entry counted) ran
every regular / tower / castle / airship stage with input a's pattern and with `x_mixed.txt`,
plus one level entrance of each type; these eight add the most functions the seven above don't
reach (about 1,440 more, +20%, including 72 of the converted-but-off player / camera functions).
`x_mixed.txt` holds right and runs in segments (run / fireball), jumps of varied length every
1.3 s, ground pounds (down in the air), shakes (spin, propeller) and presses up (doors, vines).
`RT_WARP` here starts at a given area and entrance (4th / 3rd number), so pipe / door / vine
exits are played from the start. "powerup" edits the copied `nsmbw-save.json` before the run:
`sed -i 's/"powerup":"[a-z]*"/"powerup":"fire"/g'` (all characters). Runs of 240 s.

| input | file | extra |
|---|---|---|
| f1 - 6-6 with fire | `x_mixed.txt` | `RT_WARP=5,5,0,0`, powerup fire |
| p1 - 1-5 from area 1, entrance 2 (type 21) | `x_mixed.txt` | `RT_WARP=0,4,1,2` |
| p2 - 1-tower (1-22) from area 1, entrance 1 (type 23) | `x_mixed.txt` | `RT_WARP=0,21,1,1` |
| p3 - 1-20 from area 2, entrance 8 (type 15) | `x_mixed.txt` | `RT_WARP=0,19,2,8` |
| p4 - 2-tower (2-22) from area 2, entrance 0 (type 27, the boss room) | `x_mixed.txt` | `RT_WARP=1,21,2,0` |
| p5 - 1-2 from area 1, entrance 1 (a pipe) | `x_mixed.txt` | `RT_WARP=0,1,1,1` |
| s1 - 7-2 | `x_mixed.txt` | `RT_WARP=6,1,0,0` |
| s2 - 3-3 | `x_mixed.txt` | `RT_WARP=2,2,0,0` |

## Recorded play (instance 2, 2026-11-19)

Inputs a person plays, for what the scripted ones can't do (Yoshi, water, vines, bosses ...):
`tools\record_play.bat NAME` copies the game's starting state (`nand`, `settings.ini`,
`wiimotes.ini`, `profiles.json`) to `game\recordings\NAME\start\` and starts the game in
deterministic mode with `RT_REC=game\recordings\NAME\input.rec` (the keyboard's buttons per video
field, "field mask" in hex where they change) and a memory hash every 60 fields (`check.hash`).
Keyboard only, no save states, not online, not the PC port's Options / Controls menus.

Replay: a fresh copy of `start\`, then the common environment with `RT_REPLAY=<input.rec>` in place
of `RT_AUTOPRESS`. A replay hashed with `RT_DET_HASH_EVERY=60 RT_DET_HASH_LIVE=1` gives the same
`check.hash` as the recording (field and hash columns) - that's the check that it plays the same
game; then it is an input like the others (instance 2's bench names them `r_NAME`).
