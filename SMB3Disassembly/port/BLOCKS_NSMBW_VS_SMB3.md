# ? blocks, bricks and semi-solids: NSMBW vs SMB3

Proposal (user, 2026-11-22): run these three kinds of tile on NSMBW's own code, but draw them
with SMB3's graphics. This file lists where the two games behave differently, so each
difference can be decided before anything is built.

Sources:
- SMB3: the disassembly in `SMB3Disassembly`. Block hits are in `prg008` (`LATP_*`,
  `BlockBump_Init`). Items are in `prg001`. Floor and semi-solid detection is
  `Player_DetectSolids` in `prg008`.
- NSMBW: the recompiled runtime (`recomp/runtime`) and the `d_enemies` symbols.
- Marked *(unverified)*: points not yet confirmed in the code.

## Semi-solid platforms (the big coloured blocks, "solid on top" tiles)

| | SMB3 | NSMBW |
|---|---|---|
| Landing | Lands on the tile when falling or standing with the feet up to 6 px below its top (`PRG008_B59C`) | One-way platform at the tile's top edge |
| From below / the side | Passes through | Passes through |
| A stack of them | Only the top row counts (the rest is scenery) | Each tile is a platform, so only the top row should be given NSMBW's flag |
| Players bounced on top of each other | n/a (one player) | Handled by NSMBW's own collision |
| Duck on a white block for ~5 s to drop behind the scenery | Yes (1-3's secret) | No such mechanic |

**Verdict:** there are no major differences for 1-1. Today's bugs come from our own stand-in rules:
- the "upper 8 units" check and the "is this player rising" guess in `smb3_stage_unit`;
- the bounced-player clip into a platform;
- being sucked into the side of a block stack and pulled onto its top.

Switching to NSMBW's own semi-solid flag for each stack's top row removes those rules, and with
them these bugs. This is cheap.

**To decide:** keep SMB3's white-block drop-behind for when 1-3 is ported? (It's an SMB3 tile
mechanic, so by the guidelines it would stay.)

## ? blocks

| | SMB3 | NSMBW | Note |
|---|---|---|---|
| Hit from below | The block bounces up and back over 10 frames (`BOUNCER_VEL`) | The block bounces up and back, with a small squash and stretch (`daEnBlockMain_c` `upMove`, `updateScale`) | Visual only |
| Hit from above | No such hit (no ground pound) | Ground pound: the block moves **down** and the item comes out **underneath** (`downMove`) | You asked that the item always come out of the top. That changes NSMBW's behaviour. |
| Hit from the side | A kicked shell or the Raccoon's tail | A kicked shell (NSMBW has no tail) | The tail needs to be wired into NSMBW's side hit |
| Contents by power-up | "Flower" blocks: small → mushroom, else flower. "Leaf" blocks: small → mushroom, else leaf | Small → mushroom, else the block's item | Same rule. NSMBW has no leaf item, so the leaf must be added as a new item kind. |
| Multiplayer | One item | One power-up per player in the game | You asked for NSMBW's (rule 6 exception) |
| Item rising out | The mushroom and flower rise slowly from inside the block. The leaf pops up high, then sways down. | NSMBW's items rise out with their own timing | The leaf keeps SMB3's motion (it is a host item) |
| Mushroom's direction | Left or right by which half of a 32-px column the hitting player stands in (`Mushroom_SetXVel`, a quirk) | NSMBW's own choice *(unverified: likely away from the hitter)* | |
| Enemy standing on the block | Killed (`TILEA_BLOCKBUMP_CLEAR`) | Killed | Same |
| Coin sitting on top | Collected | Collected | Same |
| Coin block | One coin pops up and vanishes | One coin pops up and vanishes | NSMBW's coin is 3D and arcs differently |
| Points | SMB3 scoring (coins, brick 10) | NSMBW's own | The host keeps scoring: SMB3's status bar |
| Hits at once | Two bouncing blocks at most (`Level_BlkBump` has 2 slots) | Many | |
| Carried player / player stacks | n/a | The player on top hits the block | Today's "carrying a player can't hit blocks" bug goes away with NSMBW's rules |

## Brick blocks

| | SMB3 | NSMBW | Note |
|---|---|---|---|
| Small player from below | Bumps it (`LATP_Brick`) | Bumps it | Same |
| Big player from below | Breaks it: 4 debris pieces, 10 points | Breaks it: NSMBW's 3D shard effect | The debris look must be replaced with SMB3's 4 sprites |
| Ground pound | n/a | A big player breaks it from above; a small one bumps it | New for SMB3 levels; follows NSMBW |
| Raccoon tail | Breaks it from the side, even with the player small | n/a (no tail) | Needs wiring into NSMBW's side hit |
| 10-coin brick | First hit: a coin and a 200-frame (3.3 s) timer. One coin per hit up to 10; after the timer the next hit gives a coin and the block is used (`LATP_10Coin`) | NSMBW's multi-coin block, with its own timing and count *(unverified)* | **Decide:** SMB3's 3.3 s / 10 coins, or NSMBW's? |
| Brick with an item, vine, P-switch or 1-up | Yes | Yes | NSMBW's P-switch and vine are NSMBW actors. Retexturing them is extra work. |

## How the "duplicate NSMBW's and texture them with SMB3" route would work

Our SMB3 level is not an NSMBW tilemap. We draw it ourselves, and NSMBW's collision asks us about
each tile through `smb3_stage_unit`. That function can already answer with NSMBW's own flags:
`0x20` solid on top, `0x40` ? block with its item in the low byte, `0x04` breakable. So:

1. **Semi-solids:** answer with NSMBW's flag for the top rows. Done.
2. **? blocks and bricks, option A (real NSMBW blocks).** Answer with NSMBW's ? block and brick
   flags, and let NSMBW detect the hit and run its own block and item actors. Today we hold back
   every NSMBW actor in the stage; these would have to be let through. The tile actors are
   probably `EN_OBJ_HATENA_BLOCK` and `EN_OBJ_RENGA_BLOCK` *(unverified)*. Then:
   - mirror NSMBW's tile changes (used block, emptied brick) back into our level;
   - draw the bouncing block with SMB3's tile;
   - draw NSMBW's items as SMB3 sprites, or keep SMB3's items and translate NSMBW's spawn
     requests;
   - replace the brick debris effect.

   This gives the most faithful NSMBW behaviour (multiplayer drops, ground pounds, carried
   players, shells). It is also the most work, and NSMBW's 3D items would need flat SMB3 art.
3. **? blocks and bricks, option B (our SMB3 port, NSMBW's rules).** Keep today's block code and
   items, but change the rules where you choose NSMBW above: one item per player, NSMBW's
   head-hit detection (so stacked or carried players work), ground-pound hits with the item still
   going up. This is less work. The visuals stay exactly SMB3's.

**My recommendation:**
- semi-solids: NSMBW's flag now;
- blocks: option B, which matches what you've described (SMB3 look, NSMBW feel in the cases you
  named) for much less risk;
- option A stays open if you want NSMBW's exact block feel later.

## Decisions (user, 2026-11-22)

1. **Semi-solids:** NSMBW's one-way flag on each stack's top row. Done. The stand-in rules
   survive only behind `SMB3_STAGE_OLD_SEMI` for comparison.
2. **? blocks, bricks and the coin brick:** option A. These are NSMBW's own blocks, duplicated
   and wearing SMB3's textures, with unique functions where SMB3 differs: the Super Leaf, the
   10-coin brick's 200-frame / 10-coin rule, and SMB3's debris.
3. **Ground pound:** only a Super Leaf comes out of the top (not collectable until it falls).
   Every other item keeps NSMBW's downward exit.
4. **Coin brick:** SMB3's, built the same way as option A.
5. **White blocks' drop-behind:** kept for 1-3.

### Option A research so far

- An NSMBW tile can be written into the course's own tilemap
  (`BgGmBase::placeTile` 0x80077860). `smb3_stage_unit` returns 0 for that cell so NSMBW reads
  its own tile (test switch `SMB3_STAGE_TEST_NSMBW_TILE="col,row,hex;..."`).
- NSMBW 1-1's tilemap holds brick tiles `0x0030 / 0x0430 / 0x0830 / 0x1430` and the ? block
  `0x1C31`. The bits above the low 10 give the contents. The probe's unit flags are 0x10 for
  the brick and 0x05 for `0x1C31`.
- With a placed `0x0030` and `0x1C31`, a big player's head hit is blocked (the head-bump bit
  is set) but no block reaction happens and no actor is made (`RT_LOG_CREATE=1` logs every
  actor made). Read back, the cells show `0x4000` and `0x0092`, so `placeTile` takes a
  different encoding than the raw tilemap value. Next: write the raw tilemap word directly
  (`getPointerToTile` 0x80077520) and find which routine turns a head hit on a block unit
  into the bounce, item and tile change (it isn't an actor create, so likely the BG system's
  own block-hit list).
