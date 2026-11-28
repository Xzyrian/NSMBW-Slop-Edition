PauseRoutine:
               lda OperMode           ;are we in victory mode?
               cmp #VictoryModeValue  ;if so, go ahead
               beq ChkPauseTimer
               cmp #GameModeValue     ;are we in game mode?
               bne ExitPause          ;if not, leave
               lda OperMode_Task      ;if we are in game mode, are we running game engine?
               cmp #$03
               bne ExitPause          ;if not, leave
ChkPauseTimer: 
;        lda GamePauseStatus
;        and #%00000001
;        beq +
;        lda #%11111110
;        sta PPU_CTRL_REG2
;+


               if CHEATS && CHEAT_LEVEL_SKIP
                   jsr cheatLevelSkip
               endif

               lda GamePauseTimer     ;check if pause timer is still counting down
               beq ChkStart
               dec GamePauseTimer     ;if so, decrement and leave
               rts
ChkStart:      lda SavedJoypad1Bits   ;check to see if start is pressed
               and #Start_Button      ;on controller 1
               beq ClrPauseTimer
               lda #$2b               ;set pause timer
               sta GamePauseTimer
               lda GamePauseStatus
               tay
               iny                    ;set pause sfx queue for next pause mode
               sty PauseSoundQueue
               eor #%00000001         ;invert d0 and set d7
               ora #%10000000
               bne SetPause           ;unconditional branch
ClrPauseTimer: lda GamePauseStatus    ;clear timer flag if timer is at zero and start button
               and #%01111111         ;is not pressed
SetPause:      sta GamePauseStatus
ExitPause:     rts

if CHEATS && CHEAT_LEVEL_SKIP
cheatLevelSkip:
;        lda GamePauseStatus
;        and #%00000001
;        bne ++
        
        lda SavedJoypad1Bits    ;check to see if select is pressed
        and #Select_Button      ;on controller 1
        beq ++


        ;jmp sndTest

        lda GameTimerSetting    ; check if timer setting is 0 to detect pipe intro
        bne +
        dec LevelNumber         ; decrement LevelNumber so we end up on the same level for next area
+

        lda #$01
        sta DisableIntermediate
        
        lda LevelNumber
        cmp #$03
        beq +

        inc LevelNumber
        jsr NextArea
        rts
+
        jsr PlayerEndWorld
++
        rts
endif


if DPCM
    SampleStart: ;sample start addresses LUT
      .db <(sample0 >> 6)

    SampleLength: ;sample lengths LUT
      .db <((sample0_end - sample0) >> 4)
endif

sndTest:
        
;        lda 
;        dpcm_sample_SD2ddx2002d909Snare
        
;        lda <dpcm_sample_SD2ddx2002d909Snare
;        lsr
;        lsr
;        lsr
;        lsr
;        lsr
;        lsr
;        sta $00
;        lda >dpcm_sample_SD2ddx2002d909Snare
;        asl
;        asl
;        clc
;        adc $00
;        sta $4012
        
;        lda #$8f
;        sta $4013
        
;        lda #$80
;        sta $4010
;        ldx #$00

;  ldx #$00
;  stx $2000
;  stx $2001
;  stx $4010


;SND_SQUARE1_REG       = $4000
;SND_SQUARE2_REG       = $4004
;SND_TRIANGLE_REG      = $4008
;SND_NOISE_REG         = $400c
;SND_DELTA_REG         = $4010
;SND_MASTERCTRL_REG    = $4015

;        ldx #$00                ;if end of sfx reached, clear buffer
;        stx Square1SoundBuffer  ;and stop making the sfx
;        ldx #$0e
;        stx SND_MASTERCTRL_REG
;        ldx #$0f
;        stx SND_MASTERCTRL_REG


;  lda #$fe
;  sta SND_MASTERCTRL_REG
;  lda #$ff
;  sta SND_MASTERCTRL_REG


if 0
      ldx #$00 ;load sample number into X
      ldy #$0F ;load pitch ($00-$0F) into Y
      ldy #$0c
      lda #$40 ;load starting level ($00-$7F) into a temp variable
      sta $7222

      lda #$0F
      sta $4015 ;DPCM disable
      sty $4010 ;Y = pitch
      lda $7222
      sta $4011 ;temp = starting sample level
      lda SampleStart,X
      sta $4012 ;X = sample number
      lda SampleLength,X
      sta $4013
      lda #$1F ;DPCM enable (plays sample)
      sta $4015
      
      
      ;- jmp -
      
    rts

endif