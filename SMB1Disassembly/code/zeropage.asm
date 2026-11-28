; Items that don't have .dsb are aliases for the definition below it.

_temp:                  .dsb 8  ; used for temporary stuff including indirect pointers
ObjectOffset:           .dsb 1
FrameCounter:           .dsb 1
A_B_Buttons:            .dsb 1
Up_Down_Buttons:        .dsb 1
Left_Right_Buttons:     .dsb 1
PreviousA_B_Buttons:    .dsb 1
GameEngineSubroutine:   .dsb 1
Enemy_Flag:             .dsb 7
Enemy_ID:               .dsb 7
Player_State:           .dsb 1
Enemy_State:            .dsb 6
Fireball_State:         .dsb 2
Block_State:            .dsb 4
Misc_State:             .dsb 9
PlayerFacingDir:        .dsb 1
FirebarSpinDirection:
DestinationPageLoc:     .dsb 1
VictoryWalkControl:     .dsb 1
;zp_unknown1:            .dsb 3
PowerUpType:            .dsb 1
FireballBouncingFlag:   .dsb 2
HammerBroJumpTimer:     .dsb 6
;zp_unknown2:            .dsb 3
Player_MovingDir:       .dsb 1
Enemy_MovingDir:        .dsb 7
;zp_unknown3:            .dsb 10
SprObject_X_Speed:
Player_X_Speed:         .dsb 1
Jumpspring_FixedYPos:
YPlatformCenterYPos:
RedPTroopaCenterYPos:
XMoveSecondaryCounter:
CheepCheepMoveMFlag:
LakituMoveSpeed:
BlooperMoveSpeed:
PiranhaPlant_Y_Speed:
FirebarSpinState_Low:
ExplosionGfxCounter:
Enemy_X_Speed:          .dsb 6
Fireball_X_Speed:       .dsb 2
Block_X_Speed:          .dsb 4
Misc_X_Speed:           .dsb 9
SprObject_PageLoc:
Player_PageLoc:         .dsb 1
Enemy_PageLoc:          .dsb 6
Fireball_PageLoc:       .dsb 2
Block_PageLoc:          .dsb 4
Misc_PageLoc:           .dsb 9
Bubble_PageLoc:         .dsb 3
SprObject_X_Position:
Player_X_Position:      .dsb 1
Enemy_X_Position:       .dsb 6
Fireball_X_Position:    .dsb 2
Block_X_Position:       .dsb 4
Misc_X_Position:        .dsb 9
Bubble_X_Position:      .dsb 3
SprObject_Y_Speed:
Player_Y_Speed:         .dsb 1
FirebarSpinState_High:
LakituMoveDirection:
PiranhaPlant_MoveFlag:
BlooperMoveCounter:
XMovePrimaryCounter:
ExplosionTimerCounter:
Enemy_Y_Speed:          .dsb 6
Fireball_Y_Speed:       .dsb 2
Block_Y_Speed:          .dsb 4
Misc_Y_Speed:           .dsb 9
SprObject_Y_HighPos:
Player_Y_HighPos:       .dsb 1
Enemy_Y_HighPos:        .dsb 6
Fireball_Y_HighPos:     .dsb 2
Block_Y_HighPos:        .dsb 4
Misc_Y_HighPos:         .dsb 9
Bubble_Y_HighPos:       .dsb 3
SprObject_Y_Position:
Player_Y_Position:      .dsb 1
Enemy_Y_Position:       .dsb 6
Fireball_Y_Position:    .dsb 2
Block_Y_Position:       .dsb 4
Misc_Y_Position:        .dsb 9
Bubble_Y_Position:      .dsb 3
AreaData:
AreaDataLow:            .dsb 1
AreaDataHigh:           .dsb 1
EnemyData:
EnemyDataLow:           .dsb 1
EnemyDataHigh:          .dsb 1
temp1:                  .dsb 1 ; originally used as $eb directly
temp2:                  .dsb 1 ; originally used as $ec directly
temp3:                  .dsb 1 ; originally used as $ed directly
;zp_unknown4:            .dsb 1
temp4:                  .dsb 1 ; originally used as $ef directly
NoteLenLookupTblOfs:    .dsb 1
Square1SoundBuffer:     .dsb 1
Square2SoundBuffer:     .dsb 1
NoiseSoundBuffer:       .dsb 1
AreaMusicBuffer:        .dsb 1
MusicData:
MusicDataLow:           .dsb 1
MusicDataHigh:          .dsb 1
MusicOffset_Square2:    .dsb 1
MusicOffset_Square1:    .dsb 1
MusicOffset_Triangle:   .dsb 1
PauseSoundQueue:        .dsb 1
AreaMusicQueue:         .dsb 1
EventMusicQueue:        .dsb 1
NoiseSoundQueue:        .dsb 1
Square2SoundQueue:      .dsb 1
Square1SoundQueue:      .dsb 1

skipNMI:                .dsb 1

