; Do not modify this default settings file.
; Instead, create a settings.asm with the 
; settings you want to change.

; Set starting world and level
; set START_WORLD to 0 to disable.
START_WORLD = 0
START_LEVEL = 1

; Skip the intermediate screen
SKIP_INTERMEDIATE = 0

; Skip title screen
SKIP_TITLE = 0

; Enable sound
SOUND = 1

; Enable dpcm sample support
; NOTE: needs work
DPCM = 0

; Add a battery
; High score is saved
; To erase save data, hold select+a+up while loading the game
; NOTE: Turning this off may cause issues.
BATTERY = 1

; Enable cheats.
;
; Settings starting with CHEAT require
; cheats to be enabled.
CHEATS = 0

; Infinite lives
INFINITE_LIVES = 0

; Can't be hurt
CHEAT_NO_INJURY = 1

; Skip level by pressing select in game
CHEAT_LEVEL_SKIP = 1

; World select always enabled
; NOTE: Currently not working
CHEAT_WORLD_SELECT = 1

; Remove game timer
CHEAT_REMOVE_TIMER = 1

CHEAT_START_FIERY = 0

; Enable some things that showcase features
; * Goomba graphics change when player is small
; * Display text message on intermediate screen
DEMO_FEATURES = 0

; Use IRQ, new scanline counter based hud, 
; other major changes.
USEIRQ = 0

; Import level from a nes file.  It must be a
; non-expanded rom with data in the same place as the original game.
IMPORT_LEVELS = 0

; File to use with IMPORT_LEVELS option.
;LEVEL_FILE equ "Super Mario Bros. (World).nes"
;LEVEL_FILE equ "Luigis_Turn.nes"
;LEVEL_FILE equ "SMB Annoyance.nes"
;LEVEL_FILE equ "Super_Drew_Bros_Nintendrew.nes"
;LEVEL_FILE equ "smbGreatEd2.nes"
;LEVEL_FILE equ "Super Mario Bros - Hi Episode 4.nes"
LEVEL_FILE equ "SMB_but_with_10_worlds_GE.nes"

; File to use when IMPORT_LEVELS is off
LEVEL_DATA equ code\levelData.asm
;LEVEL_DATA equ code\levelDataBowser.asm
;LEVEL_DATA equ code\levelDataj.asm
;LEVEL_DATA equ code\blah.asm
;LEVEL_DATA equ tools\output.txt



; Adds code to make the minus world work again.
MINUS_WORLD_FIX = 1

; Fix bug to enable unused spiny behaviour
SPINYFIX = 1

; jumpspring bug fixes from PAL version

; * Define vertical acceleration on springs (was undefined on NTSC)
JUMPSPRING_FIX = 1

; * Check whether there's a free enemy slot before placing spring. Avoids placing it in the special item slot.
; NOTE: Causes a crash.  Can't figure out why.
JUMPSPRING_FIX2 = 0

; Blooper vertical distance from player.  Default is #$10 (NTSC) or #$0c (PAL).
;BLOOPER_DISTANCE = #$10
BLOOPER_DISTANCE = $0c

; reworked movement function for Cheep Cheeps from PAL version
; NOTE: Not working.  Cheep Cheeps fly lower for some reason
CHEEPCHEEP_FIX = 0

; Collision fix taken from PAL version.
; Vertical difference deciding whether Mario stomped or got hit depends on the enemy
PLAYER_COLLISION_FIX = 1

; Set vertical speed to 0 in water stages.  Taken from PAL version.
; This makes you bounce less (or more consistant speed) when you hit 
; your head in water.  With turbofire it is a bit too easy to clip
; up through blocks though.
WATER_SPEED_FIX = 0

; Some enemies (Piranha, Bullet Bill, Goomba, Spiny, Blooper, Cheep Cheep) has larger hitbox
; Taken from PAL version.
BOUNDBOX_FIX = 1

; Allow display of up to 99 lives
LIVES_FIX = 1

; Luigi has smb2j physics
LUIGI_PHYSICS = 1

; Give Luigi his DX color palette
LUIGI_PALETTE_DX = 1

; Bounce higher off enemies as in SMB2J.
EXTRA_BOUNCE = 1

; Turn Mario into Luigi (mostly) for testing.
; Note: currently breaks time up message.
TEST_LUIGI = 0

; Same as above but for other players.
; Use 0 to turn off.
TEST_PLAYER = 0

; Add a game over menu (continue, retry)
GAME_OVER_MENU = 1

; Fix pipe pointer issue for world 9
WORLD9_PIPE_FIX = 0

; Enable "More Power" mode.  Needs DPCM enabled.
; NOTE: needs work
TIM_GRUNT = 0

; Enable skid sound effect as in SMB2J
SKID_SFX = 1

; Prevent blank tiles from being displayed.
BLANK_SPRITE_MOD = 0