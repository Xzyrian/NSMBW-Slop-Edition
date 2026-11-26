# Your edited Frog Mario, head fixed

`Mario_Frog_fixed.glb` is your `Mario_Frog.glb` with only the head changed. Your file is left as it
is. The body, feet, hands, skeleton and nodes are byte-for-byte the same as yours.

Pictures:
- `preview_fixed.png` shows the whole model.
- `head_symmetry_before_after.png` compares your head (top row) with the fixed one (bottom row).
- `wireframe_compare.png` shows the hood's triangles in three versions: Nintendo's original
  Penguin hood, your edit, and the new hood.

## What changed in the head

- **Rebuilt on Nintendo's layout:** the hood is the original Penguin hood's own triangles, with
  nothing split anywhere, fitted onto your shape.
  - **Triangles:** 236. That's Nintendo's hood less the triangles that would have sat over your
    bigger face opening. The hood's edge follows yours.
  - **Top of the head:** it keeps the template's round top. Your sculpted bumps are replaced by the
    eye balls.
  - **Shading:** your baked vertex shading is carried over.
  - `wireframe_compare.png` shows Nintendo's hood, your edit and the new hood side by side.
- **Eyes as their own pieces:** each eye is a separate low ball set into the head, the same way
  Mario's nose is a separate ball set into his face. That's how the eyes stay round without
  splitting the hood's triangles.
  - **Size:** 70 triangles each, with edges about 1.4 long (the face's are 1.56). The part buried
    inside the head is left out.
  - **Position:** fitted to your bumps, centred at (2.84, −13.4, ±3.17) with radii about
    2.3 × 2.6 × 2.2.
  - **Gap:** a 2-unit gap runs between their inner edges.
  - **Layout:** each ball's rings circle a front pole that faces the way your white patches did, so
    the painted eye sits square on it.
- **Made symmetric:** in your edit, 21 hood points around the eye bumps and the top of the head
  had lost their mirror partner on the other side, by up to 0.6 units.
  - **The fix:** both sides were averaged, then everything was built on a symmetric layout. The
    right eye ball is the exact mirror of the left.
  - **Result:** every point on the head has an exact mirror. The left/right mismatch is 0.000 on
    the hood, eye balls and crack wall, and 0.001 or less on Nintendo's face pieces.
- **Cracks closed:** your edit moved the hood's front edge forward, opening see-through gaps to
  the face. The opening now has a thickness: a wall from the hood's edge inward until it's into
  the face, 0.6–1.7 units deep, seen from both sides (72 triangles). It shows as a slightly darker
  rim under the brim.
- **Frog eyes:** painted on the front of the eye balls (SMB3 style), on `textures/frog_hood_face.png`
  (256×256, new material `mat_frog_face`):
  - **Look:** each eye is a white oval with a thin dark outline and a black pupil (46% × 58% of the
    eye, a little toward the front).
  - **Placement:** the eye follows your white patches, moved onto the balls. The right eye is the
    exact mirror of the left.
  - **Old material:** the separate white faces (`mat_player_belly` on the head) aren't used any
    more.
- **Nostrils:** two dark ovals, 0.8 units across and 1.1 apart, low between the eyes on the
  snout, painted on the same texture.
- **Forehead strip:** its one triangle that faced the wrong way now faces out.

## Editing

- **Repaint:** edit `textures/frog_hood_face.png`. Its top part is the eye (used for both eyes,
  mirrored), and the bottom strip the nostrils. The `.glb` carries its own copy, so after changing
  the PNG, swap it into the material in Blender (or rerun the script).
- **Rerun on a new edit:**

  ```
  python models/tools/fix_frog_head.py models/frog/user_edited/Mario_Frog.glb models/frog/user_edited/Mario_Frog_fixed.glb models/frog/user_edited/textures [name=value ...]
  ```

  It needs Python 3 with numpy, scipy, matplotlib and Pillow, and `retopo_template.py` beside the
  script. The template is `models/frog/Mario/Mario_Frog.glb` (change it with `template=`).
  - **Eye shape:**
    - `eye_ball=x,y,z,rx,ry,rz` sets the left eye ball by hand (the default, `fit`, fits it to your
      bumps).
    - `eye_gap` sets the gap between the two eyes' inner edges (2.0).
    - `eye_seg` and `eye_rings` set the balls' segments round (8) and rings front to back (6).
  - **Joined eyes:** `eyes=joined` uses the previous version instead: eyes grown out of the hood,
    with the top of the hood split to hold them.
  - **Painting:** `eye_size`, `eye_pupil`, `outline`, `nostril`, `nostril_gap`, `round_eyes` and
    `green`.
  - **Eyes:** keep your eyes as faces with the `mat_player_belly` (white) material on the
    hood. That's how the script finds where to paint them.
