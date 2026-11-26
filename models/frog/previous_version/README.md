# Frog Mario base, for editing

`Mario/Mario_Frog.glb` is NSMBW's Super Mario with Penguin Mario's head shape (the hood) and feet
(the flippers), as a starting point for the Frog suit. Open it in Blender with **File > Import >
glTF 2.0**, keeping the `textures` folder next to it.

| Object | What it is | Rig |
|---|---|---|
| `body` | Super Mario's body (`MB_model`) with the shoes taken off | skinned, NSMBW's 17 bones |
| `feet` | Penguin Mario's feet (from `PMB_model`): the flippers plus the short leg stubs that go up into the trouser legs | rigid on `ankle_l1` / `ankle_r1` |
| `head` | Penguin Mario's head (`PMH_model`): hood and face | at `face_1` |

The parts still carry their original textures, ready to repaint: `player_body.0` (Super),
`player_pbody` (the flippers) and `player_phead` (the hood). `player_eye.0`–`.6` are the eye
expression frames.

## How it was put together

- **Head:** Penguin Mario's head attaches at the same `face_1` joint, in the same place, so it
  sits on Super Mario's neck unchanged.
- **Shoes off:** the bottom band of NSMBW's trouser legs is skinned to the ankle bones too, so only
  the ankle triangles textured as shoe were removed (196). The 36 that are trouser stay, so the
  cuffs are whole.
- **Feet:** Penguin Mario has the same bones in a wider, lower rest pose, but his ankles point the
  same way, so each flipper was moved from his ankle onto Super Mario's ankle unchanged.
- **Splay:** Super Mario stands narrower, so as they were the flippers crossed by 3 units in the
  middle. Each foot is turned **20° toes-out** and moved **0.2 units** outward, which leaves a
  0.2-unit gap between the inner toes and suits a frog. The leg stubs stay centred under the
  trouser legs.
- **Checked:** no glTF errors, renders from all sides, and a walking pose with the flippers
  following the ankles (`preview.png`).

## Notes

- The small step at the back of each trouser cuff is the original trouser shape where the shoe's
  heel sat; Super Mario's shoe normally hides it.
- Keep the bone names and the T-pose. Units are the game's (Mario is about 30 tall), Y up,
  facing +Z.

## Rebuilding

```
python models/tools/build_frog_model.py extracted/files/Object/Mario.arc models/frog/Mario [toe-out degrees] [spread]
```

The defaults are 20 and 0.2; for example, `... 0 0` gives the feet exactly as Penguin Mario has
them. It needs Python 3 with numpy and Pillow, and uses `recomp/tools/brres_read.py` and
`export_player_models.py`. Rebuilding overwrites the `.glb`, so keep your edited copy under
another name.
