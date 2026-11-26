# SMB3 native port - roadmap

Goal: SMB3 inside NSMBW - its levels, objects, enemies, items, map and rules - with NSMBW players
(1-8) instead of SMB3's player. Every SMB3 asset keeps its 2D sprite look (user, 2026-11-21: an
SMB3 Goomba is not an NSMBW Goomba). NSMBW gives the players, camera (widescreen), HUD, pause
menu, multiplayer.

## Where it stands (smb3_stage.c)

1-1's terrain in an NSMBW stage: tiles drawn from SMB3's graphics, collision from SMB3's tile
map and solidity, NSMBW players at 80% (3D characters; Retro Mario at his own size).
Done in 1-1: blocks and items, the Raccoon suit (NSMB2's model and animations, SMB3's
abilities), SMB3's status bar, the enemies (Goomba, Para-Goomba, Koopa / Paratroopa with shells,
Piranha, Venus Fire Trap), SMB3's vertical scroll, the goal card roulette, death and time-up
restarting the level. Step 1 is complete apart from sounds; next: step 2 (every level).

The recompiled SMB3 (out/, tools/recomp6502.py) stays as the reference and, for now, as the
level decoder: its own loader builds a level's tile map exactly. Everything that *plays* is
written natively: each SMB3 object becomes an NSMBW actor (dActor_c, native C) whose behaviour is
ported routine by routine from the disassembly (speeds, timers, hit boxes as SMB3 has them),
drawn as SMB3 sprites.

## Order

1. **1-1 complete**
   - blocks: ? blocks, bricks, coins, note blocks, the P-switch; the tile map changes (bumped,
     broken, collected) and the picture with it; NSMBW players hit them from below / break them
   - items: mushroom, fire flower, leaf, star, 1-up as SMB3 sprites
   - the **Raccoon suit** on NSMBW players (user, 2026-11-21: now, not with the other suits):
     tail swipe, flutter, P-meter flight
   - **SMB3's status bar** at the bottom (world, P-meter, score, coins, time, cards) in place of
     NSMBW's HUD (user, 2026-11-21)
   - enemies in 1-1: Goomba, Para-Goomba, Koopa Troopa (shell: kick, carry), Piranha / Venus Fire
     Trap; stomp, damage, shells and fireballs against every player
   - the goal: SMB3's card roulette; death and the timer: restart the level
2. **every level**: the other tilesets (their layouts, banks, palettes, animated tiles), pipes and
   doors (areas), vertical levels, autoscrolling, water
3. **the world map** (SMB3's maps, NSMBW players walking them), toad houses, spade games
   - first part done (2026-11-23, `smb3_map.inc`): SMB3's own map game - the recompiled game
     kept running between levels - drawn as a plane in the stage's 3D scene; the NSMBW players
     on it as 3D models (player 1 at the marker, the others following); panels enter their
     levels, the end of a level goes back to the map (cleared or lost), the file saved each
     time. Next: the map drawn from SMB3's tiles natively, its logic ported routine by routine,
     the course intro card, the other players' controls
   - 2026-11-25: SMB3's transitions - no NSMBW course intro; SMB3's palette fade (PRG026
     Palette_FadeIn / FadeOut) for entering a level, leaving it (clear, death, exit) and the map;
     toad houses, spade / card games played by SMB3 itself on its map
   - next (user, 2026-11-25): **a custom map scene** - SMB3's 2D map with NSMBW's 3D world-map
     player actors (not the stage's players, not NSMBW's world map scene: built from the
     disassembly first); non-NSMBW characters drawn their own way there (SMB3 Mario as in SMB3)
   - 2026-11-25: **SMB3's log platforms** (smb3_stage_platforms.inc): $26 $27 $28 $36 $37 $38
     $3C $44 - all of World 1's (1-4, 1-6). Next: the other platforms (clouds $24 $2C, the
     floating one $3E, the falling donut-like $3A, the invisible lift $2E), and SMB3's push from
     a platform's side / head bonk under it (NSMBW's line is top-only)
4. **the other SMB3 suits** on the NSMBW players: Tanooki, Frog, Hammer, P-Wing
   - 2026-11-26: **the Frog suit**, first part (smb3_stage_frog.inc): Mario's Frog model, its idle
     pose, the item (a ? block in 1-1). Next: its moves (SMB3's hops, swimming), the other
     characters' models
5. **the rest**: fortresses (Boom Boom), airships (Koopalings), Bowser, bonus games, saves

Each step is checked in the headless runtime (deterministic runs, frames dumped) before it goes
to the Windows build.
