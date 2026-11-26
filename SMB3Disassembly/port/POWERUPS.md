# New power-ups as native NSMBW power-up states

User, 2026-11-26: the new power-ups are real NSMBW power-up states, not flags on top of Super, and
they exist in every game mode (NSMBW, SMB3, ...), reachable in various ways. Nothing is
substituted between games (no SMB3 suit in a Propeller / Penguin slot, no Frog model in the
Penguin's place). Tanooki and P-Wing are variants of the Raccoon (P-Wing: permanent P-speed while
it is held).

## The values

NSMBW's `PLAYER_MODE_e` (dAcPy_c `mPlayerMode` +4240): 0 small, 1 Super, 2 Fire, 3 Mini,
4 Propeller, 5 Penguin, 6 Ice. New:

| value | power-up | notes |
|---|---|---|
| 7 | Raccoon | variant byte (ours, per player): 0 Raccoon, 1 Tanooki, 2 P-Wing |
| 8 | Frog | its own model (a 5th model in dPlayerMdl_c - not the Penguin's) |
| 9 | Hammer | reserved |

## Where the value lives

| where | what |
|---|---|
| dAcPy_c +4240 `mPlayerMode` | the player's power-up |
| dAcPy_c +5344 `mNextMode` | the change in progress (ChangePowerupWithAnimation) |
| daPyMng_c `mPlayerMode[8]` 0x8185E95C | kept between courses / areas, per character |
| daPyMng_c `mKinopioMode` 0x80429CC4 | the rescued Toad's |
| dMj2dGame_c +0x41 `u8[8]` | the save file's, per character |
| dPlayerMdl_c +0x152 `mPlayerMode` (u8) | the model's (which body / head models show) |
| the 8-player mod (`mod_*`, `mfn_*`) | its own copies of some of the above routines |

## The catalog (scratch scan of the recompiled game, `powerup_sites.txt`)

297 reads in 210 functions:

- **125 compares**, almost all `== K` (0 small, 1 Super, 2 Fire, 3 Mini, 4 Propeller, 5
  Penguin, 6 Ice): a new value takes the "none of those" path - a big player with nothing
  special, the right default for the Raccoon and the Frog. To read one by one anyway: the
  range checks `fn_3_F14C0` (> 4), `mod_fn_3_F14C0` (> 1), `fn_80022180` (4..6) and the
  unresolved `fn_800D57F0`, `fn_8013FF70`, `fn_2_B4A80`, `fn_3_2BB60`, `mod_fn_8013FF70`.
- **Tables indexed by the value** (7 entries each: a new value reads past the end - the next
  table's data). Each gets a hook: values 0-6 the game's own entry, 7+ ours.
  | function | table | element |
  |---|---|---|
  | fn_8004D5A0 | 0x802EEAF0 | u32 (to +3740) |
  | fn_80132530 | 0x802F4E64, 0x802F4E80 | float |
  | fn_80133CB0 | 0x802F4E9C | float (to +10864) |
  | fn_801386B0 | 0x802F4ED0 | float |
  | fn_80141E30 | 0x802F50A8 | u32 |
  | fn_801465D0 | (on the stack) | float |
  | fn_80146700 | 0x802F57D0 | u32 (x 240) |
  | fn_80146580 | (on the stack, 7 bytes) | u8 |
  | mod_fn_2_6DFA0, mfn_8183D9B0 | (the mod's) | float / u32 |
- **63 pass the value on** to another function (models, sounds, effects, Yoshi...): each callee
  is read the same way.
- **22 others** (getters and copies: `fn_80022180`, `fn_80088100`, `fn_8006C1C0`,
  `daEnItem_c::GetWhetherPlayerCanGetPowerupOrNot`, ...): their callers are read too.

## Read so far (2026-11-26, entry 130)

| site | what it is | done |
|---|---|---|
| fn_80142030 setCcData | table by mode | `pu_tab` (gm_d_player_conv.c) |
| fn_800B1A50 / mod_ (fukidashi setPosOffset) | 7 x 4 table row by mode | `pu_tab` (gm_d_fukidashi_info.c) |
| daEnItem_c::GetWhetherPlayerCanGetPowerupOrNot | 0 small / 1 big / 2 Mini - the item a block gives | new = big (hle, rt_powerup.c) |
| fn_80022180 | block: is the hitter big (breaks bricks) | new = big (hle, rt_powerup.c) |
| fn_80036AB0 | brick hit, the same list inline | the game's modes shown while it runs (`with_game_modes`, rt_powerup.c) |
| fn_3_F14C0 (mode-2 > 4 → 7) / mod_fn_3_F14C0 (> 1) | an index by mode | fine: a new value gets Super's |
| fn_80088100, fn_8006C1C0 | `== 0` (small) | fine |
| dAcPy vf3F4/vf3F8 (py_damage) | mode != mNextMode (changing) | fine |
| fn_80147BD0 | dAcPy's constructor: copies the value | fine |

Still to read: the remaining callees in `powerup_sites.txt` ("call/pass": the Yoshi mNextMode
functions, initKinopioPlayer fn_8005F570, the model's callees fn_2_16C7E0...), fn_800D57F0,
fn_8013FF70, fn_2_B4A80, the save's checks.

## Plan

1. **The catalog finished**: every callee and getter caller followed, each site marked "fine as
   it is" / "needs our entry" / "needs our code", in this file.
2. **The tables and callees**: a hook for each - the game's own for 0-6, ours for 7+ (first
   copied from Super's, then made the suit's).
3. **The models**: Raccoon - Super's body and head models with the Raccoon's parts shown by the
   value (the nodes switched as the flying hands are now); Frog - a 5th model in dPlayerMdl_c
   (its own memory, made at loadResources, chosen by setPlayerMode for 8) in Mario's (and later
   each character's) own model file, the Penguin left as it is.
4. **Getting it**: ChangePowerupWithAnimation(player, 7 / 8) - NSMBW's own change, its
   animation, sound and effect (their tables above). From any size, as any power-up.
5. **Keeping it**: daPyMng_c's mPlayerMode, the save (u8 - 7 and 8 fit; anything that clamps a
   saved value to 0-6 is found and changed), areas, pipes, doors, the map.
6. **Losing it**: the damage rules for 7 / 8 (SMB3's in the SMB3 mode: a suit drops to Super).
7. **The suit's own moves** keyed off the value (the Raccoon's tail, flight, P-meter; the Frog's
   hops and swimming), the flags in smb3_stage.c / smb3_stage_frog.inc removed.
8. **Everywhere**: the items reachable in the NSMBW mode too (ways to be decided with the user).
