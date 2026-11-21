# SMB3 port

Goal: SMB3 running inside the NSMBW runtime - its graphics, enemies, objects, levels and game
logic ported from the disassembly - with NSMBW players (1-8, multiplayer included) taking the
place of SMB3's player. Nothing else of SMB3 is changed.

## Layout

```
SMB3Disassembly/
  smb3.asm, PRG/, CHR/, ...   the disassembly (reference source, NESASM; not compiled)
  port/                       the C port, compiled into nsmbw.exe (build.py, build_linux_clang.sh)
    smb3.h                    the only interface the runtime uses
    smb3_main.c               lifecycle: enter / frame / leave            (stub)
    (later)
    core/                     game state machine, RAM layout, bank logic
    world/                    world maps, level loading, tiles
    objects/                  enemies, items, block objects
    gfx/                      CHR + palettes -> textures, drawing
    audio/                    music and sound
    bridge/                   NSMBW players <-> SMB3 world: collision, tile and object
                              interaction, damage, camera, player spawns
```

New .c files go in `SMB3` in `recomp/build.py` and in the SMB3 loop of
`recomp/build_linux_clang.sh`.

## Entry

Title screen: 2 -> Singleplayer / Multiplayer / **Game** / Options -> Game -> **SMB3**.
`smb3_enter()` runs, `smb3_frame()` every frame, 1/B calls `smb3_leave()` and returns to the
list. For testing, `RT_MENU_SMB3=1` goes straight in once the title is up. Log category: `smb3`.
