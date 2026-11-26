# Penguin Mario (NSMBW), for editing

`Mario/Mario_Penguin.glb` is NSMBW's Penguin Mario from `extracted/files/Object/Mario.arc`. Open it in
Blender with **File > Import > glTF 2.0**, keeping the `textures` folder next to it.

| Object | What it is |
|---|---|
| `PMB_model` | the penguin-suit body, skinned to NSMBW's 17-bone player skeleton (the same bones and T-pose as Super) |
| `PMH_model` | the hooded head, drawn by the game at the body's `face_1` joint |

- **Textures:** `player_pbody` (suit) and `player_phead` (hood and face). `player_eye.0`–`.6` are the
  eye expression frames; the eye material scales U by 2 with mirrored wrap, so one eye in the
  texture makes both. `lm_01p`, `lm_02p` and `star_env` are the game's light-map and Star layers.
- **Shading:** the grey vertex colours are baked shading that the game multiplies in.
- **Units:** the game's own (about 30 tall), Y up, facing +Z. Keep bone names and the rest pose.

Remade with:

```
python recomp/tools/export_player_models.py extracted/files/Object/Mario.arc models/nsmbw_penguin/Mario Mario_Penguin PMB_model PMH_model@face_1
```
