- Fixes from play-testing (2026-11-22):
  - Koopas: Troopa_Draw as SMB3 has it - the body pair's head side (sprite 0, or 1 when flipped)
    and the head's tip on PAL3, the other body sprite on the object's palette; the feet
    (Troopa_FootByEvenOddFrame[3 * odd + flipped], [+1]) left then right, the flip on both; the
    wing's frame by Var5 + 2 + carry. Shells: Object_DrawShelled's waking feet ($F9, PAL3, 10
    below / above, 3 out) when Timer3 < $50 hits PRG000_CAF1's bit; Object_ShakeAndCalcSprite's
    shake (X - 1 when Timer4's bit is clear).
  - Objects keep Objects_SprAttr from their init: OCSPECIAL_KILLCHANGETO changes only the ID, so a
    stomped Para-Goomba is a wingless Goomba on the Para-Goomba's palette.
  - The suit poof (Player_SuitLost $17, Player_SuitLost_DoPoof): a leaf on a big non-Raccoon
    player (ObjHit_SuperLeaf), and a Raccoon hit (Player_GetHurt from a super suit), halt the game
    for 23 frames (NSMBW's actor stop, dActor_c::mExecStopReq) with the player hidden behind the
    smoke ($47 $45 $43 $41, PAL1); the new suit is in place at once. A leaf on Fire: Super with the
    Raccoon underneath (no NSMBW change demo).
  - SMB3's rules run only on frames a player executed (dAcPy_c::executeMain): items, blocks,
    enemies, the clock and the P-meter wait while paused or halted.
  - The goal: DoTimeBonus as SMB3 - 10 seconds for 500 a frame while the hundreds or tens are
    left, then a second for 50; NSMBW's timer is held once the card is taken (no time-up).
  - A kicked shell's block hits use the kicker's suit (Object_BumpOffBlocks goes through
    Level_DoBumpBlocks, so LATP_Flower / LATP_Leaf read Player_Suit): progressive as a head hit.
