# Raccoon (Super Leaf) Mario and Luigi, for editing

`Mario/Mario_Raccoon.glb` and `Luigi/Luigi_Raccoon.glb` are complete Raccoon models of their own,
built from NSMBW's Super Mario / Luigi with NSMB2's open hands, ears and tail. Open them in Blender
(**File > Import > glTF 2.0**) with the `textures` folder next to them. `preview.png` shows both
hand states.

**In the game** (since 2026-11-26), for the SMB3 levels: the `body`, `handsA` and `handsB` objects
are what a Raccoon Mario or Luigi shows - the open hands while flying, fluttering or running at full
P-speed, the fists
otherwise (see "In the game" below). The head, ears and tail in the game are still today's (the
Super head, with the tail and ears drawn by code).

## Parts (one object each)

| Object | What it is | Rig |
|---|---|---|
| `body` | NSMBW's Super body (`MB_model` / `LB_model`) **without its fists**, with the **torso made puffier** as NSMB2's Raccoon is (below). This is the one to reshape. | skinned, NSMBW's 17 bones |
| `handsA` | closed hands: NSMBW's own fists, cut off the body unchanged | rigid on `wrist_l1` / `wrist_r1` |
| `handsB` | open hands: NSMB2's Raccoon open hands (its `handsB`), fitted to NSMBW | rigid on `wrist_l1` / `wrist_r1` |
| `head` | NSMBW's Super head (`MH_model` / `LH_model`) | at `face_1` |
| `ears` | NSMB2's Raccoon ears (Luigi's are NSMB2's fox-style ones) | at `face_1` |
| `tail` | NSMB2's tail (`mr_tail` / `lg_tail`) | its own 5 bones, `tail_all_root` under `skl_root` |

Only one of `handsA` / `handsB` is meant to show at a time. Hide one in Blender while you work.

## How NSMB2 does the open hand

NSMB2's Raccoon body (`mr_tail_body` / `lg_tail_body`) is one model with three mesh groups that
can be shown or hidden: `player_body`, `handsA` (fists) and `handsB` (open hands). Its normal
Super model has no open hand at all, which is why only the Raccoon gets it here.

The game code chooses which group to show; none of NSMB2's animations switch the hands. The
only hint in the data is that NSMB2 ships two visibility animations, named after the **`T_fly`**
(flying) and **`T_fall`** (tail-flutter fall) animations. So the open hand most likely goes with
flying and fluttering, and the fists with everything else. That's an inference from the file
names, so the choice is ours when we set up the game side.

## Fitting

- NSMB2's player skeleton is NSMBW's, bone for bone, with the same rest pose (matches within
  0.0002), so the hands and ears sit in the same joint spaces in both games.
- **Open hand size:** NSMB2's fist was mapped onto NSMBW's fist in wrist space, and the open hand
  was given the same transform: Mario's ×0.93 and Luigi's ×0.87, shifted under 1 unit.
- **Open hand colour:** it uses one plain-white spot of NSMBW's glove texture, toned to the glove's
  average. Its shading comes from vertex colours, as in NSMB2. Fire and Ice body textures also
  have white gloves, so it fits those too.
- **Ears:** they're welded to NSMB2's own Raccoon cap. They were cut out as the Raccoon-only
  triangles that stand clear of NSMBW's head, plus two rings of triangles down into the cap so
  the bases sink in. Mario's ear bases keep a little of NSMB2's cap at the sides; trim it if
  you don't want it. `textures/raccoon_ears.png` is the part of NSMB2's texture they use. White
  is turned to the inner-ear tan the game uses now.
- **Tail:** `textures/player_tail.png` is NSMB2's 16×16 tail texture.

## The puffier torso

NSMB2's Raccoon body is its normal body with the torso pushed out: belly, back, sides and hips.
Its arms, lower legs and feet are unchanged. Mario's push averages 0.27 units (0.88 at most),
Luigi's 0.18 (0.90 at most).

That push was measured along NSMB2's torso surface and applied to NSMBW's torso. Each NSMBW torso
point (on `skl_root`, `spin`, `leg_l1`, `leg_r1`) moves outward along its own normal by the push
measured at the nearest NSMB2 points facing the same way. The offsets were then smoothed, and
they ease off where the torso joins the arms, neck and legs, so no seam opens.

| | Average push | Largest push |
|---|---|---|
| Mario | 0.29 units | 0.65 units |
| Luigi | 0.20 units | 0.55 units |

Normals on the moved points were turned by the same amount as the surface, keeping NSMBW's own
smoothing. `torso_before_after.png` compares the two (head, tail and hands hidden). To make it
stronger or weaker, rebuild with `PUFF=1.5` or `PUFF=0.5` set in the environment; `PUFF=0` turns
it off.

## Editing notes

- Keep the bone names and the T-pose; NSMBW's animations (and NSMB2's Raccoon ones the game
  already uses) drive bones by name. Tail bones: `tail_all_root > tail_root > tail_1-3`.
- Keep the object names (`body`, `handsA`, `handsB`, `head`, `ears`, `tail`): converting back
  to the game's format will go by them.
- If you change the wrists or forearms of the body, check both hand objects against them.
- Units are the game's (Mario is about 30 tall), Y up, facing +Z. Don't rescale.

## In the game

`models/tools/build_smb3_brres.py` puts `body`, `handsA` and `handsB` into Super's body model
(`MB_model` / `LB_model`) of the SMB3 levels' own model files (`game/mod/characters/smb3/mario.brres`,
`luigi.brres`), as three objects beside Nintendo's, each under a node used only to show or hide it:
Super's body `leg_l1`, the Raccoon `body` `leg_l2`, `handsA` `leg_r1`, `handsB` `leg_r2`. Each frame
the SMB3 stage code (`hands_anchor` in `SMB3Disassembly/port/smb3_stage_frog.inc`) shows Super's
body, or the Raccoon body with one pair of hands: open while the Raccoon's NSMB2 flight or flutter
animation or its P-speed run plays (`T_fly`, `T_fly2`, `T_fly_st`, `T_fall`, `T_b_dash2`), fists
otherwise and when flying while carrying something.

After editing the `.glb`, rebuild the files (both commands also take `--check out.glb`, which
exports the result back out to look at):

```
python models/tools/build_smb3_brres.py extracted/files/Object/Mario.arc game/mod/characters/smb3/mario.brres --frog models/frog/user_edited/head_type_2.glb --raccoon models/raccoon/Mario/Mario_Raccoon.glb
python models/tools/build_smb3_brres.py extracted/files/Object/Luigi.arc game/mod/characters/smb3/luigi.brres --raccoon models/raccoon/Luigi/Luigi_Raccoon.glb
```

A restart is enough; no game build. Keep the object names and the rigid hands (each hand vertex on
one wrist bone); the body may be skinned to any of Super's 14 body bones.

## The first plan (before the above)

What was suggested before the game side was set up; the game does it with nodes of Super's body
model instead of a body model of its own:

The closest fit to how NSMBW already works:

- **Body:** a Raccoon body model of its own in `Mario.arc` / `Luigi.arc`, like the propeller
  (`PLMB_model`) and penguin (`PMB_model`) bodies. Its polygons would be `body`, `handsA` and
  `handsB`.
- **Hand switching:** two extra bones, `handsA` and `handsB`, as NSMB2 has. NSMBW's model format
  ties each polygon to a visibility bone, so showing a hand means turning that bone on (from code,
  or a VIS0 animation).
- **Head and tail:** a Raccoon head (`head` + `ears`), and the tail kept as its own model, which
  is how the game handles it today.

## Rebuilding

```
python models/tools/build_raccoon_models.py NSMB2_RomFS extracted/files/Object/Mario.arc Mario models/raccoon/Mario
python models/tools/build_raccoon_models.py NSMB2_RomFS extracted/files/Object/Luigi.arc Luigi models/raccoon/Luigi
```

It needs Python 3 with numpy, Pillow and scipy. Besides `models/tools/` (`build_raccoon_models.py`,
`nsmb2_mesh.py`, `puff_torso.py`), it uses `recomp/tools/brres_read.py`,
`recomp/tools/export_player_models.py` and `SMB3Disassembly/tools/nsmb2_anims.py` (read only).
Rebuilding overwrites the `.glb`, so keep your edited copy under another name.
