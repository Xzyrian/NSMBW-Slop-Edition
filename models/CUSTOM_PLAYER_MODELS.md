# Custom player models in the game: how Frog Mario was added

This covers how an edited player model (here Frog Mario, `frog/user_edited/head_type_2.glb`) gets
from Blender into the running game. It also covers the problems found on the way and how each was
fixed. It is written so the same path can be reused for other suits or characters (Luigi's Frog,
Tanooki, Hammer).

## The short version

1. **Model:** `tools/build_smb3_brres.py` turns the `.glb` into the game's model format. It takes
   NSMBW's own Mario model file and puts the Frog's body and head into the Penguin suit's slots,
   which SMB3 never uses. (It began as `tools/build_frog_brres.py`, still there; the new tool also
   adds the Raccoon's parts: see "Parts shown and hidden" at the end.)
2. **Loading:** the runtime (`recomp/runtime/rt_charmdl.c`) loads that file for Mario while the
   SMB3 stage runs.
3. **Showing the suit:** the SMB3 stage code (`SMB3Disassembly/port/smb3_stage_frog.inc`) switches
   a Frog player's model to the Penguin slot. The player stays Super Mario underneath, like the
   Raccoon.
4. **Idle pose:** `tools/frog_idle_pose.py` turns the Blender pose into a JSON file. The animation
   build (`SMB3Disassembly/tools/nsmb2_anims.py`) turns it into an animation named `F_wait`, and
   the stage code plays it in place of the game's standing animations.

To rebuild after editing the model or the pose:

```
python models/tools/build_smb3_brres.py extracted/files/Object/Mario.arc game/mod/characters/smb3/mario.brres --frog models/frog/user_edited/head_type_2.glb --raccoon models/raccoon/Mario/Mario_Raccoon.glb
python models/tools/build_smb3_brres.py extracted/files/Object/Luigi.arc game/mod/characters/smb3/luigi.brres --raccoon models/raccoon/Luigi/Luigi_Raccoon.glb
python models/tools/frog_idle_pose.py models/frog/user_edited/idle_pose_test.glb models/frog/frog_idle_pose.json
python recomp/build.py
```

The first command only replaces a model file, so a restart is enough. The pose needs the full
build.

## Why it is built this way

### A model slot, not a new model

NSMBW's player models live in one file per character (`Mario.arc`, its `g3d/model.brres`). Each
power-up uses a pair of models from that file, a body and a head:

| Slot | Body | Head | Used for |
|---|---|---|---|
| 0 | `MB_model` | `MH_model` | Super, Fire, Ice |
| 1 | `SMB_model` | `SMH_model` | Small, Mini |
| 2 | `PLMB_model` | `PLMH_model` | Propeller |
| 3 | `PMB_model` | `PMH_model` | Penguin |

The player model object (`dPlayerMdl_c`) builds all four slots when the player is created. It then
shows one of them: `+0x770` holds the slot shown, set through `setPlayerMode` (virtual function
`+0x30`). Its table at `0x802F1330` maps each power-up to a slot:

| Power-up | Small | Super | Fire | Mini | Propeller | Penguin | Ice |
|---|---|---|---|---|---|---|---|
| Slot | 1 | 0 | 0 | 1 | 2 | 3 | 0 |

Writing new code to draw an extra model would have meant changing the game's player drawing.
Instead, the Frog takes the Penguin's slot:

- **No new drawing code:** the game draws, lights, animates and flashes the Frog exactly as it
  does any of its own models. It also attaches the head at `face_1` the same way.
- **Safe:** the SMB3 levels have no Penguin suit, so nothing is lost there.
- **Normal NSMBW untouched:** the changed file is only loaded while the SMB3 stage runs.

### Super underneath, Frog on top

NSMBW has no Frog power-up, so the player stays Super Mario in gameplay terms and a per-player
flag says Frog, like the Raccoon suit:

- **Switching:** each frame, `frog_anchor` calls `setPlayerMode(Penguin)` so the Frog slot shows.
  It then puts back the model's own mode byte (`+0x152`), so the rest of the game still sees Super.
- **Why that matters:** if the game actually thought the player was a Penguin, he would get the
  Penguin's moves too (ice balls, belly slides).
- **Losing it:** when the suit goes, `setPlayerMode` is called with the real mode and Super Mario
  comes back.

### One file, edited in place

Writing a whole model file (MDL0) from scratch means rebuilding materials, shaders, texture links
and dictionaries, and any small error there is hard to find. `build_frog_brres.py` instead:

- **Keeps the original file byte for byte**, then appends the new parts at its end: vertex,
  normal, colour and UV arrays, the two models' display lists, and two textures.
- **Re-points** the original entries (the dictionaries' offsets) at the new parts.
- **Keeps Nintendo's** materials, shaders, draw lists and texture links, so the Frog gets the game's
  own lighting and effects.

## How the model is converted

| Part | What the converter does |
|---|---|
| **Body** (`PMB_model`) | Body, belly, feet and hands from the `.glb`, as one object. Each vertex is stored in its bone's own space (the game's player bodies are rigid: one bone per vertex), using the bone's inverse rest matrix. |
| **Head** (`PMH_model`) | Two objects, as Nintendo's: the hood, face and frog face in one (material `mat_player_phead`), Mario's eyes in the other (`mat_player_eye`, so blinking still works). Head vertices are in the head's own space. |
| **Textures** | The Frog uses several textures per model, but each slot's material has one. So they are packed into one atlas per model: `player_pbody` (256 x 256) and `player_phead` (512 x 256), stored in the game's compressed format (CMPR). Each picture gets a border of its own edge pixels so filtering and UVs slightly past an edge don't pick up the neighbouring picture. |
| **Bones** | The Penguin body's bones take Super Mario's (see the first problem below). |
| **Formats** | Arrays use Nintendo's formats: 16-bit positions with 11 fraction bits, which allows up to ±16 units (the head stays inside), 16-bit normals and UVs, and 8-bit colours. Where the Frog needs more than 255 colours or UVs, the object's vertex format is switched to 16-bit indices, both in the object header and in its vertex declaration. |

### Display lists

A body vertex's bone matrix has to be loaded into the graphics chip before that vertex is drawn.
The chip holds 10 position matrices at a time. The converter groups triangles into batches of at
most 8 bones, as Nintendo's Super Mario body does. Each batch is three sets of loads, then the
triangles:

- **Texture matrices:** command `0x30`, matrix id, then `(12 - 1) << 12 | 0x78 + slot * 12`.
- **Position matrices:** command `0x20`, matrix id, then `(12 - 1) << 12 | slot * 12`.
- **Normal matrices:** command `0x28`, matrix id, then `(9 - 1) << 12 | 0x400 + slot * 9`.
- **Triangles:** each vertex carries its slot (`slot * 3`) and its texture-matrix index
  (`30 + slot * 3`).

## Problems found, and the fixes

### 1. The body stretched across the screen (first fix: matrix numbering)

**What it looked like:** the head was right, but the arms and legs were stretched far away.

**Cause:** every body model numbers its bones' matrices, and the game only computes the first N of
them, where N is the count the model declares (info `+0x1C`).

- **The Penguin body** lists only its 10 skinned bones first (it has no skinned legs) and declares
  10.
- **The Frog body** is skinned to 14 bones, like Super Mario. Its leg matrices sat past number 10,
  were never computed, and held garbage.

**Fix:** the Penguin body takes Super Mario's matrix numbering whole:

- each bone's matrix id (bone `+0x10`);
- the matrix-to-bone table;
- the node tree;
- the declared count (14);
- the bones' rest pose and flags, since the Frog is built on Super Mario's skeleton (the Penguin's
  bone positions differ by up to 6 units).

### 2. Still stretching (real cause: the load commands)

**What it looked like:** the same stretching, with the hands and feet dragged off to one side.

**Cause:** each matrix load command says how many numbers to copy, in its top 4 bits ("words minus
one"):

| Load | Words | Top bits |
|---|---|---|
| Position or texture matrix | 12 | 11 |
| Normal matrix | 9 | 8 |

The converter first wrote 0, so only the first number of each matrix was loaded. The rest of each
slot kept whatever the previous draw had left there. Some parts landed nearly right by luck and
others flew off, differently each time. The head was fine because it uses one fixed matrix and no
loads.

**Fix:** the loads now carry the right counts. The converter's display list is compared against
Nintendo's Super Mario body: every load must copy the same number of words.

### Why the checks first missed both problems

The first check exported the converted file back to `.glb` with the project's own reader and
compared it with the source at rest. That check couldn't catch either problem:

- **Matrix count:** the reader doesn't model the game computing only N matrices.
- **Load counts:** the reader masks off the word-count bits.
- **Rest pose:** a model in its rest pose looks right even with vertices on the wrong bones.

The checks now used:

1. **Posed comparison:** the converted file is posed with the idle pose and compared with the
   posed source model (`frog/game/posed_check.png`). Vertices on the wrong bone show at once.
2. **Display-list comparison:** every load in the Frog body is decoded with its word count and
   compared against Nintendo's Super Mario body.
3. **Matrix count:** every matrix id the body draws with must be below the count the model
   declares.

### 3. The idle pose didn't export

**Cause:** the first `idle_pose_test.glb` had every bone at its rest angle. A pose made in Blender's
Pose Mode is not saved in a `.glb` unless it is keyed.

**Fix:** key the pose on a frame (Pose Mode, select all, **I**, Location & Rotation), then export with
**Animation** ticked. It then arrives as a one-frame action.

Only one side was posed, so `frog_idle_pose.py` mirrors it:

- **Which side:** the side whose arm and leg moved.
- **How:** it is mirrored across the model's middle (X = 0), with a correction for each bone pair's
  rest orientation.
- **Middle bones:** `spin` and `face_1` keep their own pose.

### 4. The idle pose didn't play

This took four rounds.

1. **Wrong request.** The code swapped in `F_wait` when the game asked for animation 0 (`wait`).
   But `setAnm` (`0x800D5DD0`) does nothing when the requested animation is the one already playing
   (`+0x154`), so a standing player is never asked about again. A frame-by-frame start was added as
   well.
2. **Different ids.** The new log showed the stage asks, every frame, for `waitL` (135), or `waitR`
   (136 or 144) depending on the facing, never `wait` (0). All four are now treated as a wait and
   replaced. Once `F_wait` is playing, the stage's request is answered without restarting it.
3. **Not rebuilt.** `recomp/build.py` only recompiled the SMB3 port when a `.c` or `.h` file changed,
   so a change to an included `.inc` file was ignored. It now counts the port's `.inc` files too
   (`src_mtime`).
4. **Stale copy.** A file sent back to the computer under the same name as an earlier version
   arrived as that older copy, so the game was rebuilt without the fix. Lesson for anyone using the
   same transfer tools: send each version under a new name, then read it back and compare.

The logging that found these stays in. The log (`game/nsmbw_log.txt`) shows:

- `Frog - the game asks for animation N`, each time the request changes;
- `Frog idle (F_wait ...)`, when the idle is started.

## Where everything is

| File | What it is |
|---|---|
| `models/tools/build_smb3_brres.py` | `.glb` to the game's model file: `--frog` makes the Penguin slot Frog, `--raccoon` adds the Raccoon's body and hands to Super's body. `--check out.glb` exports the result back out. |
| `models/tools/build_frog_brres.py` | the first version (Frog only), kept |
| `models/tools/frog_idle_pose.py` | posed `.glb` to `frog_idle_pose.json` (mirrored), with an optional posed `.glb` to look at |
| `models/frog/frog_idle_pose.json` | the idle pose, each bone's rotation (degrees, X then Y then Z) and translation |
| `models/frog/game/` | a copy of the built model file, its atlases, `idle_pose_preview.png`, `posed_check.png` |
| `game/mod/characters/smb3/mario.brres`, `luigi.brres` | the files the game loads (`frog_mario.brres`: the earlier Frog-only file, no longer loaded) |
| `recomp/runtime/rt_charmdl.c` | loads them for Mario and Luigi while the SMB3 stage runs (`F_SMB3_MARIO`, `F_SMB3_LUIGI`, `rt_charmdl_frog_res`) |
| `SMB3Disassembly/port/smb3_stage_frog.inc` | the suit: the flag, the model slot switch, the idle, the item, the ? block in 1-1 |
| `SMB3Disassembly/port/smb3_stage.c` | a few hook lines into the Frog code (item kind and sprite, block, pickup, hit, animation request) |
| `SMB3Disassembly/tools/nsmb2_anims.py` | builds `F_wait` from the JSON into the animation archive; `smb3_frog_wait_ok` says it's there |
| `recomp/build.py` | rebuilds the SMB3 port when one of its `.inc` files changes |

## Doing it again (another suit or character)

- **Pick a slot the mode never uses.** In SMB3 that's the Penguin slot. Propeller (slot 2) is also
  free there, which gives a second custom suit.
- **Each character has its own file:** Luigi needs `Luigi.arc`'s model file with his own Frog
  body and head; the Toads use `Kinopio.arc`. `rt_charmdl.c` decides which file a character loads.
- **Build on the matching skeleton.** If the body uses bones the slot's model didn't, take over the
  matrix numbering from the model whose skeleton you built on (as the Frog takes Super Mario's).
  Check the declared matrix count covers every bone drawn with.
- **Check posed, not just at rest.** Pose the converted file and compare it with the source posed;
  also compare the display list's loads against a Nintendo model.
- **Swapping in animations:** put them in the animation archive (`nsmb2_anims.py`), give them an id
  (the `RA_*` table in `smb3_stage.c`) and swap them in `smb3_stage_anim`. Find out which
  animation ids the game really asks for from the log first. The table at `0x802F1350` (36-byte
  entries, with names like `wait`, `waitL`) gives their names.

## Parts shown and hidden: the Raccoon's flying hands

The second use of the same file: NSMB2's Raccoon opens its hands in flight. That's a change of a
few parts, not of the whole model, so instead of a slot it uses **nodes that only switch parts on
and off**, the way NSMB2 does it (its Raccoon body has `handsA` and `handsB` groups).

### How a model hides a part

A model's draw list (`DrawOpa`) is a list of "draw object O with material M under node N". The
game draws an entry only while node N is visible:

- **The node's flag:** bit `0x100` of the node's flags (`+0x14`) in the file.
- **The model's copy:** a model built with its own visibility buffer (`ScnMdl`, not `ScnMdlSimple`)
  copies those flags at its creation into one byte per node (`ScnMdl +328`) and reads only the
  copy after that. Changing a byte means setting bit 1 of `+316` as well, as the game's own
  accessor does (`0x8025C8E0`).

The runtime writes both, so it works whichever kind of model the game made.

### What the converter does (`--raccoon`)

- **Objects:** Super's body model (`MB_model` / `LB_model`) keeps Nintendo's `polygon0` and gets
  three more: `raccoon_body`, `raccoon_fists`, `raccoon_open_hands`. Their vertices share one new
  set of arrays (index 1 of each kind, named `raccoon_parts`).
- **Nodes:** each object is drawn under a node nothing else is drawn under: Super's body under
  `leg_l1`, then `leg_l2`, `leg_r1`, `leg_r2`. The leg bones were chosen because they are always
  there and always animated; the node only decides visibility; the vertices' matrices come from
  the display lists as usual. The three new nodes are hidden in the file, so a game that knew
  nothing of them would draw Super's body only.
- **Same material:** all four use `mat_player_body`, so Fire's texture swap and the star's flashing
  apply to the parts too. The open hand samples one white spot of the glove texture and gets its
  shading from vertex colours.
- **Dictionaries:** adding objects and arrays means adding names to the model's dictionaries,
  which are search trees. The converter rebuilds each one it changes, the way the tools that write
  these files do, and checks that every name is found by the game's search.
- **Bounding box:** grown to fit the open hands.

### Problems on the way

- **Dictionary entries pointing backwards.** The rebuilt dictionaries sit at the file's end, past
  the names they point to, so their offsets are negative. The project's reader (`brres_read.py`)
  read them unsigned and failed. It now reads them signed, as the game does.
- **Joints by name.** The Raccoon `.glb` lists its skeleton in a different order from the game's
  model, so the converter matches bones by name, not by number.

- **The open hands gone after the Frog became a power-up of its own.** The Frog then got its own
  file (`frog_mario.brres`, a second player model), loaded first. Together with the Toad and
  Rosalina / Daisy files that filled the 4 MB the runtime keeps for model files
  (0x81C00000-0x82000000), so `smb3/mario.brres` - the file with the Raccoon's parts - was refused
  (`smb3/mario.brres: no room` in the log), and Mario showed the game's own model. Nothing in the
  model or the hand code was wrong. `rt_charmdl.c` now puts a file that doesn't fit there at the
  top of MEM2 (0x93700000-0x94000000, which neither the game nor the runtime uses; the renderer
  reads MEM2, and save states keep it). When parts don't show, look for `no room` first, then for
  the `hands: the Raccoon's parts in the model at ...` line.

### Checks used

- every dictionary name is looked up with the game's search and must land on its own entry;
- the result exported back out: each part's vertices match the source within 0.0005 units, and
  every vertex is on the same bone as in the source;
- every matrix load in the new display lists carries its word count, and every matrix used is
  below the model's declared count;
- the Frog parts of the new file are identical to the earlier Frog-only file's.
