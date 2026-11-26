- Scrolling (prg008 Player_DoScrolling): the vertical, SMB3's - the screen stays at its lowest
  (the level's last row just above the bar) unless the first player flies (Player_FlyTime); once
  up it follows ($30 / $58 from the screen's top, up at most 3 a frame) back down to the lowest.
  NSMBW's camera keeps the horizontal, held inside the level (Horz_Scroll 0 .. Level_Width); the
  level's ends are walls. Done after dBg_c's camera execute (rt_menu.c hle_fn_80154F60 calls
  `smb3_stage_camera`: dBgParameter_c +0x3C/+0x64/+0x4C/+0x54, dBg_c +0x900B0).
- Time: NSMBW's own timer (dStageTimer_c +4) is kept at SMB3's every frame, so its hurry-up and
  its time-up death (checkTimeOut / setTimeOverDemo) come when SMB3's clock says.
- Death and time-up: with lives left the level starts again (rt_lyt.c's DoSceneChange: the world
  map scene the stage asks for becomes `smb3_stage_restart`); SMB3's score, coins and cards stay.
  No lives left: NSMBW's game over.
- The goal (prg002 ObjNorm_EndLevelCard / ObjHit_EndLevelCard): the card turns mushroom /
  flower / star every 8 frames; taken, the enemies on screen go in a puff, the clock stops, the
  card flies up at -$28, "COURSE CLEAR!" and "YOU GOT A CARD" with the card come
  (Video_CourseClear / Video_YouGotCard, letters from BG bank $5E), the time left goes into the
  score (DoTimeBonus), the card goes into the status bar (StatusBar_Update_Cards: CardUL..LR);
  a third card gives lives (EndLevelCard_xUpByMatch 2 / 3 / 5 alike, else 1) and the cards
  clear. Then, with no SMB3 map yet, 1-1 starts again. Not ported: the players running off to
  the right, the giant card shape of a triple match, the course clear music.
