;Start:
             sei                          ;pretty standard 6502 type init here
             cld
Start:
             lda #%00010000               ;init PPU control register 1 
             sta PPU_CTRL_REG1
             ldx #$ff                     ;reset stack pointer
             txs
VBlank1:     lda PPU_STATUS               ;wait two frames
             bpl VBlank1
VBlank2:     lda PPU_STATUS
             bpl VBlank2
             ldy #ColdBootOffset          ;load default cold boot pointer
             ldx #$05                     ;this is where we check for a warm boot
WBootCheck:  lda TopScoreDisplay,x        ;check each score digit in the top score
             cmp #10                      ;to see if we have a valid digit
             bcs ColdBoot                 ;if not, give up and proceed with cold boot
             dex                      
             bpl WBootCheck
             lda WarmBootValidation       ;second checkpoint, check to see if 
             cmp #$a5                     ;another location has a specific value
             bne ColdBoot   
             ldy #WarmBootOffset          ;if passed both, load warm boot pointer
ColdBoot:    jsr InitializeMemory         ;clear memory using pointer in Y
             sta SND_DELTA_REG+1          ;reset delta counter load register
             sta OperMode                 ;reset primary mode of operation
             lda #$a5                     ;set warm boot flag
             sta WarmBootValidation     
             sta PseudoRandomBitReg       ;set seed for pseudorandom register
             lda #%00001111
             sta SND_MASTERCTRL_REG       ;enable all sound channels except dmc
             lda #%00000110
             sta PPU_CTRL_REG2            ;turn off clipping for OAM and background
             jsr MoveAllSpritesOffscreen
             jsr InitializeNameTables     ;initialize both name tables
             inc DisableScreenFlag        ;set flag to disable screen output
             lda Mirror_PPU_CTRL_REG1
             ora #%10000000               ;enable NMIs
             jsr WritePPUReg1

            if USEIRQ == 1
                lda #$40                    ; disable frame counter to make irq work
                sta $4017
                
                cli                         ; Clear interrupt Disable Bit (so we can use irqs)
            endif

;EndlessLoop: jmp EndlessLoop              ;endless loop, need I say more?

mainLoop:
               jsr waitframe
               jsr ReadJoypads           ;read joypads
               jsr PauseRoutine          ;handle pause
               jsr RunCustomCode         ;run custom code
               
; RNG stuff
; ----------------------------------------------------------
               ldx #$00
               ldy #$07
               lda PseudoRandomBitReg    ;get first memory location of LSFR bytes
               and #%00000010            ;mask out all but d1
               sta $00                   ;save here
               lda PseudoRandomBitReg+1  ;get second memory location
               and #%00000010            ;mask out all but d1
               eor $00                   ;perform exclusive-OR on d1 from first and second bytes
               clc                       ;if neither or both are set, carry will be clear
               beq RotPRandomBit
               sec                       ;if one or the other is set, carry will be set
RotPRandomBit: ror PseudoRandomBitReg,x  ;rotate carry into d7, and rotate last bit into carry
               inx                       ;increment to next byte
               dey                       ;decrement for loop
               bne RotPRandomBit
; ----------------------------------------------------------
               
               jsr UpdateTopScore
               
               lda GamePauseStatus       ;check for pause status
               lsr
               bcs PauseSkip
               
; Timer stuff
; ----------------------------------------------------------
               lda TimerControl          ;if master timer control not set, decrement
               beq DecTimers             ;all frame and interval timers
               dec TimerControl
               bne NoDecTimers
DecTimers:     ldx #$14                  ;load end offset for end of frame timers
               dec IntervalTimerControl  ;decrement interval timer control,
               bpl DecTimersLoop         ;if not expired, only frame timers will decrement
               lda #$14
               sta IntervalTimerControl  ;if control for interval timers expired,
               ldx #$23                  ;interval timers will decrement along with frame timers
DecTimersLoop: lda Timers,x              ;check current timer
               beq SkipExpTimer          ;if current timer expired, branch to skip,
               dec Timers,x              ;otherwise decrement the current timer
SkipExpTimer:  dex                       ;move onto next timer
               bpl DecTimersLoop         ;do this until all timers are dealt with
NoDecTimers:   inc FrameCounter          ;increment frame counter
; ----------------------------------------------------------
               lda #$01
               sta skipNMI                 ; skip (most of) NMI code.

               jsr OperModeExecutionTree ; do one of many, many possible subroutines

               lda #$00
               sta skipNMI

PauseSkip:     
               jmp mainLoop
               
waitframe:
    lda #$00
    sta vblanked
waitloop:
    lda vblanked
    beq waitloop
    rts
