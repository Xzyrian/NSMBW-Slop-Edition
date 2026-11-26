# Frog Mario, for editing

`Mario/Mario_Frog.glb`: NSMBW's Super Mario in a plain green frog suit (no overalls), with a puffier
torso like the Raccoon's, Penguin Mario's hood (beak removed) and flippers, NSMB2's open hands, and
a white belly circle. Open it in Blender with
**File > Import > glTF 2.0**, keeping the `textures` folder next to it. `preview.png` shows it
plain and posed.

The first version (shoes swapped for flippers, nothing else changed) is kept in
`previous_version/`.

| Object | What it is | Rig |
|---|---|---|
| `body` | Super Mario's body (`MB_model`) without shoes, fists or the overalls' buttons. The torso is puffier and smoothed, and the trouser legs are stretched down onto the flippers. Two parts: the suit, and the belly (the torso's front) with its own texture. | skinned, NSMBW's 17 bones |
| `hands` | NSMB2's open hands (its Raccoon `handsB`), fitted to the wrists as on the Raccoon models | rigid on `wrist_l1` / `wrist_r1` |
| `feet` | Penguin Mario's flippers, thicker, on Super Mario's ankles, on a pale-yellow sole slab wider than the foot | rigid on `ankle_l1` / `ankle_r1` |
| `head` | Penguin Mario's hood and face, beak removed, with a strip of hood filling the forehead and a thick lip round the sides and bottom of the face | at `face_1` |

## What was done

- **No overalls:**
  - **Buttons:** the only separate overall pieces in Super Mario's body were the two buttons (8
    triangles each); they're removed. Every other loose piece was already gone (shoes, fists).
  - **Bib and straps:** these were modelled into the body mesh as small ridges, with dark lines
    baked into the vertex colours along them. Six passes of volume-keeping smoothing over the
    torso (Taubin) took them out; points meeting the arms, neck and legs were held, so no seam
    opens. The baked shading was smoothed with them and brought back to its original average
    brightness.
  - **Texture:** the suit is one plain green, with no seams, pockets or straps drawn in.
- **Puffier torso:** the same push as the Raccoon models: NSMB2's normal-to-Raccoon torso push,
  measured and moved onto this body (0.29 units on average, 0.65 at most), applied before the
  smoothing.
- **Ears:** the beak was first found by its orange texture, which also caught 8 triangles of the
  darker skin by the ears and left holes there. Now only the pure-orange beak (34 triangles) is
  removed, and the face by the ears is whole again.

- **Trousers joined to the feet:** each trouser leg ends in a band skinned to the ankle bone,
  which the shoe used to cover. Its lower 70% now sits on the flipper below it (sunk in
  0.08); the top of the band, where it meets the shin, stays, and the points between are
  blended. At the heels, Penguin Mario's foot top (the leg stub and the heel's rim) was wider
  than the trouser legs and poked out in points, so it was pulled in to 2.15 units from the
  leg's centre, inside the trousers.
- **Thicker feet:** the flippers are 1.6× as tall, measured from the sole (2.28 → 3.66 units),
  and the leg stubs above them are raised by the same amount. Toes still turn out 20°, each foot
  is 0.2 further out, and the soles sit on the ground.
- **Soles:** each flipper stands on a sole slab 0.8 units tall, and the foot is raised by the
  same amount, so the soles stay on the ground. The slab has its own vertices:
  - **Shape:** it sticks out 0.3 units past the foot all round, at the top and the bottom.
  - **Parts:** straight walls (80 triangles, smooth shading around the foot), a ledge on top from
    the wall back in to the foot (80), and a new bottom (36).
  - **Colour:** pale yellow (242, 232, 160), from a 6×6 patch painted into an unused corner of
    `frog_feet` (texels 3–8).
  - **Shading:** set light (1.0 on the ledge, 0.95 on the walls, 0.8 underneath), because the
    foot's ground-level shading is dark and turned the yellow brown.
  - **Green edge:** the green ends crisply where the foot meets the ledge.
- **Open hands:** the fists are gone and NSMB2's open hands replace them, sized to the wrists,
  pointed at a white glove texel, and toned to match the glove texture.
- **Green:** these are new texture files; the game's own textures aren't changed.
  - `frog_body`: plain green except the gloves.
  - `frog_feet`: the flippers and leg stubs, green.
  - `frog_head`: the hood and its rim green; face, hair and moustache unchanged.
  - The eyes (`player_eye.0`–`.6`) are unchanged.
- **Belly circle:** Super Mario's texture reuses the belly's texels on the sides of the waist and
  the back of the neck, so painting the circle there whitened those too. Instead, the torso's
  front (110 triangles) has its own texture, `frog_belly` (128 × 128):
  - **Layout:** mapped flat from the front, plain green.
  - **Circle:** white, radius 4.0 units, centred 14.5 units up, so it looks round from the front.
- **Face lip:** a big rounded green roll, radius 0.9 (1.8 units thick), frames the sides and
  bottom of the face.
  - **Path:** it follows the face's outline as seen from the front, from one end of the forehead
    strip round to the other, with the ends tapering. The hood's actual edge is tucked behind
    the face, so a lip there would hide.
  - **Sides:** it stays at that outline, outside the sideburns.
  - **Chin:** from the front, the outline under the chin is the underside of the jaw, which lies
    further back toward the neck. So round the bottom (easing in from 125° off straight up), each
    point is brought forward to the front of the face at that spot, and the lip runs along the
    chin's front edge.
  - **Making it:** the outline is the face's outermost point at every 7.5° around the face,
    smoothed and pushed 0.45 out, then run as a tube (61 rings of 8 points, 960 triangles, kept
    light for the Wii) on the hood's green.
- **Beak removed:** its 34 triangles are gone. The beak also covered an opening between the
  hood's front edge and the eyebrows (Penguin Mario has no forehead skin there), so a strip of
  hood now fills it: the hood comes down to the brows.
- **Checked:** no glTF errors; renders from every side and in a walking pose, with no gaps,
  cracks or stray colours.

## Notes

- The white rings at the ends of the sleeves are the gloves' cuffs (part of the body mesh). They
  stay white with the gloves.
- To repaint, edit the PNGs. `frog_belly` covers only the front of the torso, so changes to the
  circle won't reach anywhere else.
- Keep the bone and object names and the T-pose. Units are the game's (Mario is about 30 tall),
  Y up, facing +Z.

## Rebuilding

```
python models/tools/build_frog_model.py NSMB2_RomFS extracted/files/Object/Mario.arc models/frog/Mario [name=value ...]
```

| Option | Default | What it sets |
|---|---|---|
| `toe_out` | `20` | degrees each foot turns out |
| `spread` | `0.2` | units each foot moves outward |
| `thick` | `1.6` | how many times taller the flippers are |
| `tuck` | `2.15` | how far from the leg's centre the foot top may reach |
| `green` | `44,160,60` | the suit colour |
| `belly` | `4.0` | the circle's radius |
| `belly_y` | `14.5` | the circle's centre height |
| `lip` | `0.9` | the face lip's radius (`0` for none) |
| `lip_out` | `0.45` | how far the lip sits out from the face's outline |
| `sole` | `0.8` | the sole slab's height (`0` for none) |
| `sole_grow` | `0.3` | how far the slab sticks out past the foot, all round |
| `sole_colour` | `242,232,160` | the soles' colour |
| `puff` | `1.0` | strength of the torso puff (`0` for none) |
| `smooth` | `6` | torso smoothing passes (`0` keeps the overalls' ridges) |
| `flat` | `1` | `0` keeps Super Mario's shading lines, in green |

It needs Python 3 with numpy and Pillow, plus `models/tools/build_raccoon_models.py`,
`nsmb2_mesh.py` and `puff_torso.py`, `recomp/tools/` and `SMB3Disassembly/tools/nsmb2_anims.py`. Rebuilding overwrites
the `.glb`, so keep your edited copy under another name.

## In the game (SMB3 mode)

`user_edited/head_type_2.glb` is the model the game uses. Rebuild the game file after editing it:

```
python models/tools/build_frog_brres.py extracted/files/Object/Mario.arc models/frog/user_edited/head_type_2.glb game/mod/characters/smb3/frog_mario.brres
```

- **What it makes:** NSMBW's Mario model file with the Penguin body and head replaced by the
  Frog's. SMB3 has no Penguin, so the Frog suit uses that slot.
- **Textures:** each part's textures are packed into one per model (`*_body_atlas.png`,
  `*_head_atlas.png`, written beside it), with an edge border so filtering doesn't bleed.
- **Bones:** keep the T-pose and the bone names. The body is rigid on its bones, one bone per
  vertex (the heaviest is used).
- **Checking:** add `--check out/Frog_check.glb` to export the result back out to compare.

The idle pose: `frog_idle_pose.json`, from `user_edited/idle_pose_test.glb` (a one-frame
Blender action):

```
python models/tools/frog_idle_pose.py models/frog/user_edited/idle_pose_test.glb models/frog/frog_idle_pose.json [preview.glb]
```

- **Mirroring:** the side whose arm and leg were posed is mirrored onto the other side.
- **Middle bones:** `spin` and `face_1` keep their pose.
- **Using it:** the next build makes it the game's `F_wait` (`SMB3Disassembly/tools/nsmb2_anims.py`).
- **Preview:** `game/idle_pose_preview.png` shows the pose.

