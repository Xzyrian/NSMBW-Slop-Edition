# SMB3 native port - roadmap

Goal: SMB3 inside NSMBW - its levels, objects, enemies, items, map and rules - with NSMBW players
(1-8) instead of SMB3's player. Every SMB3 asset keeps its 2D sprite look (user, 2026-11-21: an
SMB3 Goomba is not an NSMBW Goomba). NSMBW gives the players, camera (widescreen), HUD, pause
menu, multiplayer.

## Where it stands (smb3_stage.c)

1-1's terrain in an NSMBW stage: tiles drawn from SMB3's graphics, collision from SMB3's tile
map and solidity, NSMBW players at 80% (3D characters; Retro Mario at his own size).

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
4. **the other SMB3 suits** on the NSMBW players: Tanooki, Frog, Hammer, P-Wing
5. **the rest**: fortresses (Boom Boom), airships (Koopalings), Bowser, bonus games, saves

Each step is checked in the headless runtime (deterministic runs, frames dumped) before it goes
to the Windows build.
