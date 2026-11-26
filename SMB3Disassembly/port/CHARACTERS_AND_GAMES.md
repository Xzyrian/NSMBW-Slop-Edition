# Characters and alternate games

This port puts characters from one game into levels from another. Today that means NSMBW's
players (Mario, Luigi, the Toads) in SMB3's World 1-1. Later it could also mean an SMB3 or SMB1
Mario in an NSMBW level, or both kinds of player in the same level. These rules decide whose
behaviour applies when the two games meet.

## Terms

- **Character game**: the game a player character comes from. NSMBW for Mario, Luigi and the
  Toads today. SMB3 for a future NES Mario.
- **Host game**: the game the level, its tiles, its objects and its rules come from (SMB3 for 1-1).
- **Lineage**: the chain of games a character steps down through when its own game has no answer:
  - NSMBW → NSMB2 → NSMB DS → the host game
  - SMB3 → SMB1 → the host game

## The rules

1. **A character keeps its own game.** Its physics, controls, animations, sounds, power-up
   feedback, damage reaction, death and goal sequence come from the character game.
   NSMBW Mario runs, jumps, gets hurt and dies the way he does in NSMBW, even inside an SMB3 level.

2. **A level keeps its own game.** Tile layout, objects and enemies, what an enemy does when it is
   hit, scoring, the status bar, the timer, end-level cards and the time bonus come from the host
   game.

3. **Missing behaviour steps down the lineage.** When the character game has nothing for a host
   mechanic, use the nearest game in the character's lineage that does. The host game's version
   comes last. Example: NSMBW has no Super Leaf, so NSMBW characters use NSMB2's Super Leaf (its
   speed, flight and tail), not SMB3's.

4. **Contacts split at the boundary.** When a host object touches a character:
   - The host game decides what happens to the **object**. A Goomba is stomped, squashed and scored
     by SMB3's rules: stomp window, kill tally, shell kick.
   - The character game decides what happens to the **character**: the bounce height, damage,
     invulnerability frames, a bubble.
   - A character state that its own game treats as "not in play" (in a bubble, dying, in a demo,
     flashing after a hit) is also not in play for host objects.

5. **Effects belong to whoever owns them.**
   - Effects tied to a character belong to the character game: the power-up transformation, the
     smoke poof, the death and goal animations.
   - Effects tied to an object belong to the host game: the block bounce, an enemy flipping over,
     the goal card roulette, score pop-ups.

6. **Named exceptions.** Some host mechanics deliberately use the character game's behaviour.
   Each exception is listed below and needs the user's sign-off before it is added.

## Decided cases

| Situation | NSMBW character in an SMB3 level | NES (SMB3/SMB1) character |
|---|---|---|
| Super Leaf pickup | The same as any NSMBW power-up: NSMBW's power-up change, sound and invulnerability. No freeze, no poof. | SMB3: the game freezes for the smoke poof (`ObjHit_SuperLeaf`). |
| Losing the Raccoon suit | NSMBW's power-down (to Super) | SMB3: poof, `Player_SuitLost` |
| Running and P-speed | NSMBW's own acceleration and top speed. With the leaf the top speed is raised and the same ramp reaches it; the range above NSMBW's normal top speed is P-speed (the P-run animation, a P-jump, flight). | SMB3's power meter |
| Flight, tail wag, tail attack | NSMB2's Super Leaf | SMB3 |
| Hitting an SMB3 enemy | SMB3 decides the enemy's fate; NSMBW decides the player's bounce and damage | SMB3 |
| Holding and throwing a shell | NSMBW's carry: the carry pose, carry walk/wait/jump, the Throw state; can't pick up while carrying anything (a player). The shell sits where NSMBW's `getCarryPos` puts it. SMB3 decides the shell's speed. | SMB3 |
| Goal (end-level card) | Controls lock; the NSMBW goal animation plays; SMB3's card and time bonus play out | SMB3: walks right off screen |
| Death | NSMBW's death and its lives; back to SMB3's map (SMB3's rules for the panel: not cleared, the marker back on its square) | SMB3 |
| World map | SMB3's map and its rules; the NSMBW players walk it as their 3D models (player 1 at the marker, the others following, as on NSMBW's map); SMB3's lives show NSMBW's | SMB3 |
| Multiplayer item blocks | **Exception:** NSMBW's behaviour (an item per player) | — |
| Positions tied to the body (lift height, carry offsets) | Scaled with the 80% model | — |
| Player-to-player (carrying, stacking, bubbles) | NSMBW. Raccoon-specific animations (e.g. carrying a player while wearing the leaf) must be made new, since NSMB2 has no multiplayer. | — |

## Exceptions agreed (rule 6)

- Semi-solid platforms use NSMBW's collision (done).
- ? blocks, brick blocks and the coin brick are NSMBW's blocks duplicated with SMB3's textures,
  plus SMB3's unique functions (in progress; see `BLOCKS_NSMBW_VS_SMB3.md`).
- Power-up blocks give one item per player, as NSMBW does.
- A ground-pounded Super Leaf block sends the leaf out of the top.

## Where the code decides

- `smb3_stage.c`: the host level: tiles, blocks, items, the status bar, scrolling, the Raccoon
  abilities.
- `smb3_stage_enemies.inc`: the host objects: SMB3's object engine, enemies, the goal card.
- `recomp/runtime/*`: the NSMBW characters. Hooks into the player (`rt_retro.c`), the camera
  (`rt_menu.c`) and scene changes (`rt_lyt.c`) hand control to the stage code.
- Each place that branches on the character should ask what the character's game is. Today every
  player is an NSMBW character, so those branches only have their NSMBW side. When an NES
  character arrives, give the player a character-game field and branch on it. Do not branch on
  the level's game.

## Checklist for a new mechanic

1. Who owns it, the character or the level? (Rules 1, 2 and 5.)
2. If it is the character's: does the character game have it? If not, which game down the lineage
   does? (Rule 3.)
3. If it is a contact: split it. The object's fate follows the host; the character's reaction
   follows the character game. (Rule 4.)
4. If the host should borrow the character game's behaviour, add it to the exception list and get
   it agreed first. (Rule 6.)
5. Record the decision in the table above.
