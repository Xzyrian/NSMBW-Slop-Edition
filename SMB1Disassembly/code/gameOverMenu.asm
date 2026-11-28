GameOverCursorData:
  ;.db $5b, $02, $48
  .db $75, $02, $48

GameOverCursorY:
  .db $77, $8f;, $a7, $bf, $d7

GameOverMenu:
            lda SavedJoypadBits          ;if player pressed the start button
            and #Start_Button            ;then either continue or start over
            bne ContinueOrRetry
            lda SavedJoypadBits
            and #Select_Button           ;if player pressed the select button
            beq ChgSel                   ;then branch to select "continue" or "retry"
            ldx SelectTimer              ;if select timer not expired while
            bne ChgSel                   ;pressing select, skip this
            lsr
            sta SelectTimer              ;otherwise set the select timer
            lda ContinueMenuSelect
            eor #$01                     ;and toggle between the two choices
            
;            inc ContinueMenuSelect
;            lda ContinueMenuSelect
;            and #$03
            
            sta ContinueMenuSelect
ChgSel:     ldy #$02
ChgSelLoop: lda GameOverCursorData,y     ;set up cursor sprite tile, attribute
            sta Sprite_Data+1,y          ;and X position in sprite OAM data
            dey
            bpl ChgSelLoop
            ldy ContinueMenuSelect
            lda GameOverCursorY,y        ;set Y position based on the selection
            sta Sprite_Data
            rts

ContinueOrRetry:
  lda ContinueMenuSelect       ;if player selected "continue"
  beq Continue                 ;then branch to continue
  ;lda #$00
  ;sta CompletedWorlds          ;otherwise init completed worlds flags
  jmp TerminateGame            ;and end the game

Continue:
        ldy #$02
        sty NumberofLives           ;give three lives
        sta LevelNumber
        sta AreaNumber              ;put at x-1 of the current world
        sta CoinTally
        ldy #$0b
ISCont: sta ScoreAndCoinDisplay,y   ;reset score
        dey
        bpl ISCont
        inc Hidden1UpFlag           ;allow 1-up to be found again
        jmp ContinueGame
