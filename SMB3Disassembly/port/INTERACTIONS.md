# Interactions checklist

Every new object, tile, item, suit or mechanic is checked against this file before it is called
done, and again after any change to it. The checks come from NSMBW's own code: every attack type,
every enemy hook and every player state the engine has. The two holes that led to this file (a
ground-pounded Goomba bouncing the player, a player carrying a player not hitting blocks) are
only examples. Most of the rows below are things nobody has reported yet.

How an object passes:
1. Pick its **reference objects** (section 1) and read their hooks.
2. Go through every section that applies to its kind (sections 4-5). Each row gets an answer:
   what the reference does, what we do, and whether it has been tested.
3. Write the answers into the object's record (section 6), and list the IDs tested in the
   CHANGELOG entry ("Checked: E07 E13 E15-E18 with Mario and Luigi, big and small").

Row IDs (E07, B12...) are stable: new rows get new numbers, removed rows keep theirs, marked
*retired*.

---

## 1. Before building: the reference rule

Holes come from building an object from a description of what it does, not from the code of
the closest object that already does it. A port of SMB3's Goomba written from SMB3's routines
alone has no answer for anything SMB3 doesn't have (ground pounds, Yoshi, fireballs from eight
players). NSMBW's own Goomba answers all of them. So:

1. **Name two references**: the host game's original (SMB3's object in the disassembly) and the
   closest NSMBW object (the NSMBW Goomba for an SMB3 Goomba, NSMBW's ? block for an SMB3 ?
   block, the Koopa Troopa for an SMB3 Troopa).
2. **List the NSMBW reference's hooks**: every virtual function it overrides and every state it
   has. Where to read them:
   - Decompiled (names and source): NSMBW-Decomp (github.com/NSMBW-Community/NSMBW-Decomp).
     Useful references there: `daEnShell_c` (anything that becomes a shell), `daEnNoko_c` (Koopa
     Troopa), `daEnTogezoBase_c` (Spiny), `daIce_c` (frozen enemy), `daIceBall_c`, `daBullet_c`
     (what Yoshi spits), `dEnBoss_c`, `dEn_c` (`d_enemy.cpp`, `d_enemy_death.cpp`), `dActor_c`,
     `dAcPy_c` / `daPlBase_c` (players), `dCc_c` (collision).
   - Recompiled only (no names): `recomp/runtime/gm_en_enemies.c`, by address (the Goomba is
     `daEnKuribo_c`, from `kuribo_build_55f60`). Its vtable gives which `dEn_c` hooks it
     replaces.
3. **Build on the engine where you can.** An object that is a real `dEn_c` with a real `dCc_c`
   collider gets every row in section 4.1 handled by NSMBW's defaults, including rows nobody
   thought of. It then only needs the rows where the host game differs. An object that does its
   own collision (as `smb3_stage_enemies.inc` does today) gets none of them for free. Every row
   must then be written by hand, and its record must say so at the top.

## 2. Open decision: host objects and character-only actions

`CHARACTERS_AND_GAMES.md` rule 4 says the host game decides the object's fate and the character
game decides the character's. It doesn't say what happens when the character does something the
host game has no rule for: an NSMBW ground pound, spin jump, propeller drill, penguin slide,
fence punch, ice ball, Yoshi's tongue or a pipe-cannon shot against an SMB3 enemy. SMB3 has none
of these, so today they fall through to whatever the box test does (mostly a stomp or a hurt).

**Needs the user's decision** (once, for all host objects). Possible rules:
- (a) The NSMBW reference object's outcome for that action, drawn with the host's sprites (an
  SMB3 Goomba that is ground-pounded dies as NSMBW's Goomba does).
- (b) The nearest host action (a ground pound counts as SMB3's stomp, an ice ball as a
  fireball), listed per action.
- (c) Per object, case by case.

Until this is decided, each record marks these rows *open*, not *done*.

---

## 3. The axes

An interaction is one value from each axis that applies: who acts, how they act, what state
the object is in, what state the player is in, and where it happens. The thousands of
combinations are built from these lists; section 4 says which axes matter for each row.

### 3.1 Player states (from `dAcPy_c` and `daPlBase_c`)

Every state the player can be in when it touches the object:

| Group | States |
|---|---|
| On the ground | Walk, Turn, Crouch, Slip, RollSlip, Land, Kani (cliff walk), Funsui (on a water spout), Quake, ElecShock, IceDamage, FlyDamage |
| In the air | Jump, SitJump, WallJump, WallSlide, Fall, SpinJump, KaniJump, BlockJump, RideOffJump, CannonJump, JumpDai (spring), PlayerJumpDai (off another player), WaitJump, HipAttack, SpinHipAttack, Propel, PropelThrow |
| Water | Swim (and the Penguin's swim) |
| Climbing / hanging | Vine (vines, fences, rock walls), Hang, Pole, TarzanRope, Cloud |
| Carrying / carried | LiftUp, Throw, CarryPlayer, PlayerEat, RideYoshi |
| Attacks | Fire (shooting), PenguinSlide |
| Out of play | Balloon (bubble), DemoDown, DemoFallDown, DemoFireDown, DemoEatDie |
| Scripted (demos) | DemoInDokanU, DemoInDokanD, DemoInDokanL, DemoInDokanR, DemoOutDokanU, DemoOutDokanD, DemoOutDokanL, DemoOutDokanR, DemoOutDokanRoll, DemoRailDokan, DemoInWaterTank, DemoOutWaterTank, DemoInDoor, DemoOutDoor, DemoInJump, DemoInVine, DemoCannonWarp, DemoDokanCannon, DemoStartWait, DemoWait, DemoGoal, DemoNextGotoBlock, DemoControl, DemoNone, JrCrown, AnimePlay, None |

Statuses that change what a touch means even inside one state (`daPlBase_c` STATUS_*):
invincibility blink after a hit, star, STATUS_HIP_ATTACK_FALL / _LAND, the spin flags, propeller
up / slow fall, STATUS_SLIP_ACTIVE, penguin slide and its recoil, STATUS_RIDE_YOSHI, being in a
bubble or out of play, STATUS_DISPLAY_OUT_NO_DAMAGE, the quake hops, the goal-pole statuses,
STATUS_FOLLOW_MAME_KURIBO (Mini Goombas stuck on), climbing on the far side of a fence.

### 3.2 Power-ups

0 small, 1 Super, 2 Fire, 3 Mini, 4 Propeller, 5 Penguin, 6 Ice, 7 Raccoon (this project),
8 Frog (this project), and the star on top of any of them. New suits add a row here and a pass
through section 4.6.

### 3.3 Player-to-player relations

Alone, carrying a player, being carried, standing on a player's head, a stack of three or
more, riding Yoshi, Yoshi without a rider, carrying an object (shell, ice block, enemy, a player
through the spin lift).

### 3.4 Characters and games

Mario, Luigi, the two Toads; the NSMBW models at 80% in SMB3 stages; Retro Mario (SMB1 size);
NES characters with their own physics. Game mode: NSMBW mode, SMB3 mode. Host level: NSMBW or
SMB3.

### 3.5 Players and modes

1, 2, 4 and 8 players (the 8-player module changes several per-player arrays, e.g. `dEn_c`'s
`mNoHitPlayer` becomes u8[8]); Free Mode, Coin Battle, Super Guide; online play.

---

## 4. Checklists by kind

### 4.1 Enemies (and anything else with a `dCc_c` collider)

**How NSMBW dispatches a touch** (`dEn_c::normal_collcheck`, `d_enemy.cpp`): the toucher's kind
picks the path - another enemy → `EnDamageCheck`, else `Normal_VsEnHitCheck`; a player →
`PlDamageCheck`, else `Normal_VsPlHitCheck` (once per player per no-hit timer); Yoshi → the
tongue (`hitYoshiEat`), else `YoshiDamageCheck`, else `Normal_VsYoshiHitCheck`; anything else
(fireballs, shells, Yoshi's spit) → `EtcDamageCheck`. The checks look at the toucher's attack
type (`CC_ATTACK_*`) and, for some, the enemy's own vs-damage mask. NSMBW's walking enemies
accept every attack type except NONE, YOSHI_MOUTH, SPIN_LIFT_UP and SAND_PILLAR
(`d_a_en_noko.cpp`).

#### Receiving: stomps (`Normal_VsPlHitCheck` → `Enfumi_check`)

| ID | Check | NSMBW hook |
|---|---|---|
| E01 | Normal stomp: kill, squash, shell or change (wings off); the player's bounce | `Enfumi_check` result 1; `FumiJumpSet`, `FumiScoreSet`, `fumiSE`, `fumiEffect`; StateID_DieFumi |
| E02 | Mini Mario's stomp (most enemies survive it) | result 2; `MameFumiJumpSet`, `mamefumiSE`, `mamefumiEffect` |
| E03 | Spin-jump stomp | result 3; `SpinFumiJumpSet`, `SpinFumiScoreSet`, `spinfumiSE`, `spinfumiEffect`; `setDeathInfo_SpinFumi` |
| E04 | Yoshi's stomp (rider on Yoshi) | `YoshiFumiJumpSet`, `YoshiFumiScoreSet`, `yoshifumiSE`, `yoshifumiEffect`; StateID_DieYoshiFumi |
| E05 | Stomp combo: score steps per player, 1-up at the end, the clap sound | `setFumiComboScore`, `checkComboClap`, `dEnCombo_c` |
| E06 | Stomped while the enemy is above the top of the screen: no hit | `CeilCheck` |
| E07 | Stomped by two players on the same frame; by a player falling off another's head | per-player `mNoHitPlayer` timers |

#### Receiving: attack types (`PlDamageCheck`, `YoshiDamageCheck`, `EtcDamageCheck`, `EnDamageCheck`)

| ID | Attack | Sent by | Hook | `dEn_c` default |
|---|---|---|---|---|
| E10 | 1 FIREBALL | Fire player's fireball | `hitCallback_Fire` if the vs-damage bit is set, else `fireballInvalid` | DieFall, a coin pops out |
| E11 | 2 ICEBALL | Ice player's ice ball | `hitCallback_Ice` (bit), else `iceballInvalid` | StateID_Ice (frozen, see E40-E46); a player carrying it lets go |
| E12 | 3 STAR | star player, star Yoshi | `hitCallback_Star` | DieFall, star combo score |
| E13 | 4 ICE_BREAK | an ice block breaking (`daIce_c`) | (find the sender's effect) | - |
| E14 | 5 SLIP | player sliding down a slope | `hitCallback_Slip` (bit) | DieFall |
| E15 | 6 KOOPA_FIRE | Bowser's fire | (`daIceBall_c` reacts to it) | - |
| E16 | 7 HIP_ATTACK | ground pound (not Mini: `isMameAction` stops it); Yoshi's ground pound | `hitCallback_HipAttk`; Yoshi: `hitCallback_YoshiHipAttk` | DieFall with the ground-pound sound and effect, stomp combo score; Yoshi's: DieYoshiFumi |
| E17 | 8 WIRE_NET | punching through a fence | `hitCallback_WireNet` | DieFall |
| E18 | 9 SHELL | a kicked shell, a thrown object, from an enemy or a player | `hitCallback_Shell` (from `EnDamageCheck` and `EtcDamageCheck`) | DieFall, the thrower's shell combo |
| E19 | 10 PENGUIN_SLIDE | Penguin's belly slide | `hitCallback_PenguinSlide`; actor property 0x200: no hit, the player recoils (STATUS_PENGUIN_RECOIL) | as Slip |
| E20 | 11 SPIN | the spin jump's attack box | not dispatched to enemies (spin stomps are E03); against players: the spin lift | - |
| E21 | 12 UNK12 | unknown | (find) | - |
| E22 | 13 SPIN_FALL | the propeller's drill | `hitCallback_Spin` | DieFall with the spin sound and effect, stomp combo score |
| E23 | 14 FIRE_2 | (find the sender) | `hitCallback_Fire`, no bit check | as Fire |
| E24 | 15 YOSHI_EAT | Yoshi's tongue | `hitYoshiEat`, `setEatTongue`, `setEatTongueOff`; StateID_EatIn / EatNow / EatOut | does nothing: the class must opt in |
| E25 | 16 YOSHI_MOUTH | (find) | excluded by the walkers' mask | - |
| E26 | 17 CANNON | a player shot from a pipe cannon | `hitCallback_Cannon` | DieFall, combo score |
| E27 | 18 SPIN_LIFT_UP | picking up | `isSpinLiftUpEnable`, `setSpinLiftUpActor`, `carry_check` | not liftable unless the class says so |
| E28 | 19 YOSHI_BULLET | what Yoshi spits (`daBullet_c`) | `hitCallback_YoshiBullet` (bit) | DieFall, a coin pops out |
| E29 | 20 YOSHI_FIRE | Yoshi's fire | `hitCallback_YoshiFire` (bit) | DieFall, a coin, combo score |
| E30 | 21 ICE_2 | (find; players treat it with Yoshi's spit and fire) | `hitCallback_Ice` (bit) | frozen |
| E31 | 22 SAND_PILLAR | sand spout | excluded by the walkers' mask | - |
| E32 | `hitCallback_Large`, `hitCallback_Rolling`, `hitCallback_Screw` | not called by the dispatch | confirm nothing calls them in this build | - |

#### Receiving: everything else

| ID | Check | NSMBW hook |
|---|---|---|
| E35 | The block it stands on is hit from below | `block_hit_init` (default: DieFall) |
| E36 | A screen quake: small hops it, big kills it on screen | `isQuakeDamage`, `quakeAction`, `setDeathInfo_Quake` (`dQuake_c` flags) |
| E37 | The goal is reached: every enemy dies | `allEnemyDeathEffSet`, StateID_DieGoal |
| E38 | Lava, poison, falling out of the level | `EnLavaCheck`, `WaterLineProc`, `yoganSplashEffect`, `poisonSplashEffect`, `setDeathInfo_YoganFall` |
| E39 | Other deaths: DieSmoke, DieOther, DieBigFall; the right one for each cause | `setDeathInfo_Other`, `setDeathInfo_Smoke`, `setDeadMode` |
| E39a | StateID_HitSpin (empty in `dEn_c`): which enemies use it, and for what | `d_enemy_state.cpp` |

#### Frozen, carried, eaten

| ID | Check | NSMBW hook |
|---|---|---|
| E40 | Frozen: the ice block's size, the picture inside | `createIceActor`, `setIceAnm` |
| E41 | The ice block carried, thrown, kicked; it breaks on a wall or an enemy | `daIce_c` states Carry, Throw, Drop |
| E42 | The ice block in water (floats, sinks), on lava (dives), on a slope, melting | `daIce_c` states: Float, FloatWait, SmallFloat, ShakeFloat, TogeFloat, Sink, PushSink, Dive, YoganDive, Melt_Normal, Air, Hop, Land, Fall, Cover, Freeze |
| E43 | The ice block ground-pounded, hit by fire, Yoshi's fire or spit | `daIce_c` (ICE_BREAK, YOSHI_FIRE, YOSHI_BULLET) |
| E44 | Thawing: back to its state and animation | `returnState_Ice`, `returnAnm_Ice` |
| E45 | Frozen, then the screen quakes; frozen, then the goal | `daIce_c::isQuakeDamage`, `setDeathInfo_IceBreak`, `setDeathInfo_IceVanish`, StateID_DieIceVanish |
| E46 | A frozen enemy carried by a player who is then hit, enters a pipe, goes in a bubble | (player side) |
| E47 | Picked up (if it can be): the carry position, a turn, a throw, dropped when hit | `PlayerCarryCheck`, `calcCarryPos`, `setCarryFall` |
| E48 | Thrown into another enemy, a block, a wall, a player | (shell rows E18, B-section) |
| E49 | Eaten by Yoshi: swallowed, kept and spat, or turned into fire / ice | `mEatBehavior`: NONE, EAT, DRINK, DRINK_BIG (makes an egg), FIREBALL, ICEBALL; `setEatMouth`, `eatMove`, `setEatGlupDown`, `calcEatScaleRate`, `calcEatInScale` |
| E50 | Spat out: flies as a YOSHI_BULLET, hits what it meets | `setEatSpitOut`, `calcSpitOutPos`, `setAfterEatScale` |
| E51 | Yoshi hit or dismounted with the enemy in his mouth | EAT_STATE_SPIT |

#### Dealing damage

| ID | Check | NSMBW hook |
|---|---|---|
| E55 | Touching a player hurts: power-down, death, bubble; the damage type | `Normal_VsPlHitCheck` → `setDamage`; `DamageType_e` |
| E56 | Not while the player is invincible, blinking, in a bubble, in a demo, off screen | `isNoDamage`, STATUS_DISPLAY_OUT_NO_DAMAGE |
| E57 | On the far side of a fence: no hit | `LineBoundaryCheck` |
| E58 | Touching Yoshi: Yoshi runs off, the rider falls | `Normal_VsYoshiHitCheck` |
| E59 | A player stuck on its side or head bonking it from below | (reference) |
| E60 | Each of the 8 players separately: a hit on one doesn't block the others | `mNoHitPlayer` |

#### Movement and the world

| ID | Check | NSMBW hook |
|---|---|---|
| E65 | Walls, slopes, ledges (turn or walk off), ceilings | `EnBgCheck`, `EnBgCheckFoot`, `EnBgCheckWall`, `checkWallAndBg` |
| E66 | Moving platforms, falling platforms, rotating ones | ride checks (`dBc_c::checkRide`) |
| E67 | Water: enters, swims or sinks, splash, leaves | `WaterCheck`, `setWaterSpeed`, `EnWaterCheck`, `EnWaterFlagCheck`, `waterSplashEffect` |
| E68 | Ice floors, conveyors, quicksand, water spouts | `beginFunsui`, `endFunsui`, `isFunsui` |
| E69 | Meeting another enemy: turn, pass, push | `Normal_VsEnHitCheck` |
| E70 | Bouncing on landing, the jelly squash | `Bound`, `boyonBegin`, `calcBoyonScale` |
| E71 | Dancing to the music where NSMBW's enemies do | `canDance`, StateID_BgmDance |
| E72 | Facing the nearest of up to 8 players | `getPl_LRflag`, `getPl_UDflag`, `Area_X_check` |

### 4.2 Blocks and tiles

Cross every hitter with every block kind and every contents.

| ID | Hitter |
|---|---|
| B01 | A player's head, for each power-up (small bumps a brick, big breaks it, Mini) |
| B02 | A player's head while carrying a player, an object, or riding Yoshi |
| B03 | The top player of a stack (and the ones below it) |
| B04 | A player being thrown, or jumping off another player's head |
| B05 | Ground pound from above: small, big, Mini; the item comes out below, or above (decided: only the leaf goes up) |
| B06 | Propeller drill from above; propeller flight from below |
| B07 | Spin jump from below; the Raccoon's tail from the side |
| B08 | A kicked shell, a thrown ice block, a thrown enemy from the side |
| B09 | A shell or an enemy hitting it from below (kicked up) |
| B10 | A Yoshi head bump; a Yoshi ground pound; something Yoshi spat |
| B11 | Fireballs, ice balls (normally nothing) |
| B12 | Two players hitting it on the same frame; hitting it again while it still bounces |
| B13 | Hit while the player is in a pipe, a door, a bubble, a demo, dying (nothing) |

| ID | What's on or around the block |
|---|---|
| B20 | An enemy standing on it dies (`block_hit_init`), for every enemy kind |
| B21 | A coin on top is collected (by whom: the hitter) |
| B22 | An item on top bounces |
| B23 | A player standing on it is bounced; a player on its side |
| B24 | A shell, an ice block, a Mini Goomba on it |

| ID | Contents and results |
|---|---|
| B30 | Each item, by the hitter's power-up (small → mushroom); the item's direction |
| B31 | One item per player in the game (agreed exception), with 1, 2, 4, 8 players |
| B32 | Coins: single, multi-coin timer, 10-coin brick; who gets them |
| B33 | 1-up, star, vine, P-switch, leaf, frog suit, empty brick |
| B34 | Hidden blocks: only from below; not from above or the side |
| B35 | The tile change is kept: used block, broken brick, through a restart, a midpoint, a pipe and back |
| B36 | Score and the HUD's coin count |

### 4.3 Items and power-ups

| ID | Check |
|---|---|
| I01 | Picked up by each power-up: the change, the stored item, the score |
| I02 | Picked up by a player who is carrying a player, being carried, on Yoshi (Yoshi eats it?) |
| I03 | Picked up during a demo, in a bubble, by two players at once |
| I04 | Moving: walls, slopes, water, lava, falling out, platforms, conveyors |
| I05 | Hit from below by a block bump; caught by a shell |
| I06 | Coming out of a block hit from above; out of a block with something on top |
| I07 | Despawning off screen; not respawning after a restart if taken |
| I08 | The stock (stored) item and the world map's items |

### 4.4 Platforms and moving terrain

| ID | Check |
|---|---|
| T01 | Standing on it, for every player state in 3.1 that can stand; landing on it |
| T02 | Riding it while carrying, while carried, in a stack, on Yoshi |
| T03 | Its side and its underside: pushing, head bonks, being squashed against a wall (DAMAGE_SQUISH) |
| T04 | Enemies, items, shells, ice blocks riding it |
| T05 | Ground pounding it; a quake while on it |
| T06 | Jumping off it with its speed; it leaving the screen with a player on it |

### 4.5 Projectiles

| ID | Check |
|---|---|
| R01 | Against every enemy kind, block, wall, slope, water, lava |
| R02 | Against players (fireballs and ice balls hit other players; Yoshi's spit and fire) |
| R03 | Against frozen enemies, shells, items, coins |
| R04 | How many at once per player; despawn off screen |
| R05 | Its attack type and vs-damage mask are NSMBW's (section 4.1) |

### 4.6 New player suits and power-ups

| ID | Check |
|---|---|
| S01 | Every site that reads the power-up value (`POWERUPS.md`, `powerup_sites.txt`) |
| S02 | Its collider sizes and sensors (`setCcData`, `getBgPointData`) in every state of 3.1 |
| S03 | Its new attacks: which `CC_ATTACK_*` they send, and the 4.1 rows each one needs |
| S04 | Every enemy row in 4.1 with the suit on |
| S05 | Getting hit, the power-down, the change animation, the stored item |
| S06 | Keeping it through pipes, doors, restarts, the map, saves |
| S07 | Carrying, being carried, Yoshi, bubbles, swimming, climbing, the goal |
| S08 | Every character and model (the Frog's per-character model files) |

### 4.7 Level elements

| ID | Check |
|---|---|
| L01 | Pipes and doors: entering with each power-up, carrying, carried, on Yoshi, two at once |
| L02 | Vines, poles, ropes, fences: climbing with each power-up, punching, being hit |
| L03 | Springs, note blocks, P-switches: every player state, enemies and items on them |
| L04 | Water, lava, poison, quicksand, wind, ice floors, conveyors |
| L05 | The goal: each player state at the pole or card, players still in bubbles |
| L06 | Midpoints, restarts, game over, time up |

---

## 5. For every object

| ID | Check |
|---|---|
| G01 | Spawn and despawn by NSMBW's widescreen view, not the host's narrower one; respawn rules |
| G02 | Stops when NSMBW stops the world: the power-up change, the pause menu, a player dying, demos |
| G03 | Every player in the game, 1 to 8; players in bubbles, dead, finished |
| G04 | Drawn in the right layer: in front of or behind players, tiles, other objects; culled off screen as NSMBW culls (`ActorDrawCullCheck`) |
| G04a | Its collision is off while it can't be touched (carried, eaten, dying) and back on after (`removeCc`, `reviveCc`) |
| G05 | Its sounds and effects come from the right game (`CHARACTERS_AND_GAMES.md` rule 5) |
| G06 | Score, combo and lives through the right system |
| G07 | Save states and online play: its state is part of the saved state and runs the same every time (no host-clock or uninitialised reads) |
| G08 | Restart, midpoint, game over, coming back from the map: its state is reset or kept |
| G09 | NSMBW mode and SMB3 mode; every character in 3.4 |
| G10 | The headless test reaches it (a scenario for each row tested) |

---

## 6. Records

One record per object, in `SMB3Disassembly/port/interactions/<object>.md`:

```
# <Object> (host: <game> <name>; NSMBW reference: <class>)
Collision: NSMBW dCc_c / own (every row by hand)
| ID | Reference does | We do | Status | Tested in |
| E16 | NSMBW Goomba: ... | ... | done / missing / open (section 2) / n.a. | scenario, CHANGELOG entry |
```

Rows that don't apply are marked n.a. with a reason, so a missing row means it was never looked
at.

## 7. Worked example: the SMB3 Goomba (code as of 2026-11-26)

From `smb3_stage_enemies.inc` (`hit_player`): the Goomba does its own collision. It sees each
player as a box (`pl_box`) and the flags in `pp[]`: small, on the ground, running, star, can't
be hurt (`isNoDamage`), can carry. Without reading NSMBW's attack types:

- E16 ground pound, E22 propeller drill, E03 spin jump: the box test calls them a stomp. *missing*
- E02 Mini stomp: a stomp, as a big player's. *check against the reference*
- E04 Yoshi stomp, E24 the tongue, E28-E30 Yoshi's spit and fire: Yoshi isn't in `pp[]`.
  *missing*
- E10 fireballs, E11 ice balls (and E40-E46 frozen), E17 fence punch, E19 penguin slide, E26
  pipe cannon, E18 NSMBW shells and thrown objects: not seen. *missing*
- E12 star: kills it. *done*
- E36 quakes, E37 the goal, E35 block bump: E35 has SMB3's own (`obj_block_bumped`); the others
  are *not checked*.
- E55-E60: SMB3's stomp and hurt rules, NSMBW's damage; the per-player rows are *not checked*.

Each of these needs the section 2 decision before it can be marked *done*.

## 8. Where the lists come from

- Attack types, collider kinds: `CC_ATTACK_e`, `CC_KIND_e` in NSMBW-Decomp `include/game/bases/d_cc.hpp`.
- Enemy hooks and their dispatch: `d_enemy.hpp`, `d_enemy.cpp`, `d_enemy_death.cpp`.
- Actor hooks (carry, eat, splash, block hit): `d_actor.hpp`.
- Player states: the STATE_* declarations of `dAcPy_c` and `daPlBase_c`; statuses and damage
  types in `d_a_player_base.hpp`.
- When the decomp gains classes (more enemies, Yoshi, blocks, the BG system), add their hooks
  here as new rows.
