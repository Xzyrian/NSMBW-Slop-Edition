- Status bar (prg026 StatusBar_*): SMB3's own bar, taken from the unseen SMB3 in 1-1 (name table
  rows 24-29 of $2800, their attributes, the pattern banks its IRQ maps for the bar - snapshotted
  as line 212 is drawn, nes_ppu.c `ppu_capture_at` - and the palette), drawn at the bottom of the
  screen, 48/240 of its height as in SMB3, black out to the widescreen edges and up to the
  level's last row. Its changing fields are written each frame by SMB3's rules
  (StatusBar_UpdTemplate positions): StatusBar_Fill_PowerMT (6 arrows $EF/$EE from the first
  player's P-meter, [P] $3C/$2C flashing on MaxPower_Tick bit 3), _Fill_Coins / _Fill_Lives
  (blank leading zero, lives NSMBW's rest count, capped at 99), _Fill_Score (6 digits of the score
  in tens), _Fill_Time (Level_TimerTick $28: a second every 41 frames, from the course header's
  hundreds; it stops with the game). NSMBW's HUD (dGameDisplay_c::draw) is not drawn in the stage.
  The level and the players are lifted 48 units so the bar covers nothing (the camera rests on
  the shell course's bottom).
- Enemies (smb3_stage_enemies.inc): the level's own object list (Level_ObjPtrOrig into bank 6),
  5 object slots, spawned as they come in at a screen edge (the NSMBW screen) and deleted off it
  (a deleted one can come back; a killed one can't). The prg000 core: Object_Move (4.4,
  gravity 3, max $40), Object_WorldDetect4 (feet / head / wall offsets of detection group 1),
  Object_HitGround, the timers (Timer3 slower above $60), the states Normal / Shelled (wake-up,
  shaking) / Held / Kicked (ObjShell_AnimFrame, blocks hit by the shell, other enemies killed for
  its kill tally) / Killed / Squashed / Poof; Player_HitEnemy for every player (the bounding
  boxes, the stomp window 19 above, OA2_GNDPLAYERMOD, Kill_Tally scores 100 ... 8000, 1-ups);
  Object_HoldKickOrHurtPlayer (run held: carry the shell, let go: kick; else hurt), Enemy_Kill
  for the tail swipe (counter $0C and $09), Object_HandleBumpUnderneath (a block bumped under
  one), GroundTroop_BumpOffOthers. The walkers of prg004: ObjNorm_GroundTroop (Goomba, green
  Troopa, hopping Paratroopa), ObjNorm_RedTroopa (turns at ledges), ObjNorm_ParaGoomba (three
  hops, then a high one), with KILLCHANGETO (stomped Para-: wings off). prg005 ObjNorm_Piranha:
  green, green fire and the Venus Fire Trap (hide - emerge - attack - retract; not out while a
  player is within 27; the fire ones face and look at the player and spit once at timer $28 in
  World 1: SOBJ_PIRANHAFIREBALL, near/far velocities), drawn clipped at the pipe; stomping one
  hurts. Drawn from SMB3's sprites (GroundTroop_Draw / Troopa_Draw with the head and feet,
  ParaGoomba_Draw wings, Object_Draw16x32Sprite, the poof). A hit on an NSMBW player is NSMBW's
  own damage (its invulnerability, power-down, death); a stomp is NSMBW's stomp jump at 4 a frame.
