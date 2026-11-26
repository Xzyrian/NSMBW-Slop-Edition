# NSMBW Super (big) player models, for editing

These are exported from the game's own archives (`extracted/files/Object/Mario.arc`, `Luigi.arc`,
`Kinopio.arc`, inside each `g3d/model.brres`) as a base for the SMB3 suits (Tanooki, Frog, Hammer...).

| File | What's in it |
|---|---|
| `Mario/Mario_Super.glb` | `MB_model` (body, skinned) + `MH_model` (head) + `MC_model` (loose cap) |
| `Luigi/Luigi_Super.glb` | `LB_model` + `LH_model` + `LC_model` |
| `Toad/BlueToad_Super.glb` | `KB_model` + `KH_model` (texture set `.0`) |
| `Toad/YellowToad_Super.glb` | the same meshes with texture set `.3` |
| `*/textures/*.png` | every texture these models use, plus the fire / ice variants |
| `preview.png` | what the exports look like |

Open the `.glb` files in Blender with **File > Import > glTF 2.0**, keeping each `.glb` next to
its `textures` folder. Images are linked rather than embedded, so you can edit a PNG and
re-import to see the change.

## How the game puts a player together

- **Body** (`MB_model` etc.) is skinned to a 17-bone skeleton: `mario_all_root > skl_root >
  legs / spin > arms, face_1, CapPosition`. Every vertex is tied to exactly one bone (no
  blended weights), as in the original. All of NSMBW's player animations drive these bones
  **by name**, so keep the bone names and the rest pose as they are; add new bones only
  for new parts (a tail, ears...).
- **Head** (`MH_model`) is a separate rigid model. The game draws it at the body's `face_1`
  joint, and that's where it's parented in the `.glb`. Its materials are `mat_player_face`,
  `mat_player_hair`, `mat_player_hat` and `mat_player_eye` (Toad: `hat` + `eye`).
- **Loose cap** (`MC_model` / `LC_model`) is the cap the game shows in the hand, parented at
  `CapPosition` (on the right wrist). The head already has its own hat, so this one isn't
  normally visible. Hide it in Blender if it's in the way.
- Small (`SMB`/`SMH`), propeller (`PLMB`...) and penguin (`PMB`...) are other models in the
  same archive and aren't included here.

## Textures

- `player_body.N` / `player_head.N`: **0** normal, **1** fire, **2** ice (Mario, Luigi).
  For Toad: **0-2** Blue Toad, **3-5** Yellow Toad, **6** a spare red-spotted set.
- `player_eye.0`-`.6` are **expression frames** (open, blinking, hurt...). The game's texture
  pattern animations (`PH_*`) switch between them. The eye texture holds **one** eye: the
  eye material scales U by 2 with mirrored wrap, so the second eye is the mirror image.
  In the `.glb` this is a `KHR_texture_transform` on that material, which Blender imports as
  a Mapping node.
- `lm_01p`, `lm_02p` (light maps) and `star_env` (the Star flash) are extra material layers the
  game blends over the base texture. They're listed under each material's custom properties
  (`nw4r_layers`) and don't need editing.
- The grey **vertex colours** (`Color` attribute) are baked shading that the game multiplies in.

## Notes

- Units are the game's own: Mario is about 30 units (30 m in Blender) tall, Y up, facing +Z.
  Don't rescale on import or export if the model is going back into the game.
- Mario's and Luigi's head meshes include the hair under the cap. In a couple of places it
  pokes through the hat; that's in the original data, not an export error.
- Each mesh's material and polygon names (`mat_player_body`, `polygon0`...) are kept as in the
  game, which makes it easier to put the models back into a BRRES later.

## Re-exporting

`recomp/tools/export_player_models.py` (with `recomp/tools/brres_read.py`) made these files:

```
python export_player_models.py <Character.arc or model.brres> <out_dir> <Name> <body> [<head>@face_1] [<cap>@CapPosition] [tex:.0=.3]
python export_player_models.py extracted/files/Object/Mario.arc models/nsmbw_super/Mario Mario_Super MB_model MH_model@face_1 MC_model@CapPosition
python export_player_models.py extracted/files/Object/Kinopio.arc models/nsmbw_super/Toad YellowToad_Super KB_model KH_model@face_1 tex:.0=.3
```

It needs Python 3 with numpy and Pillow. It works for any NSMBW-style
player BRRES, including the character mods in `game/mod/characters/`.
