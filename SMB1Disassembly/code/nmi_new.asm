; todo:
;-------------------------------------------------------------------------------------
; fix nametable issue
; fix pause logic so sprites show when paused again
;   **fixed**
; make everything NMI safe.
;   * jsr might happen to wrong bank
;   * reading table data might happen from wrong bank
;   * need to make sure we don't swap out of a bank without
;     restoring it (and avoid corrupting RestoreBank)
;   * need to be careful things like address $0000 aren't clobbered
;
;   Not safe:
;     UpdateScreen (bank00)
;       **fixed** moved to fixed bank
;     UpdateTopScore (bank00)
;       **fixed** moved to main loop
;     MoveAllSpritesOffscreen (bank00)
;       **fixed** moved to fixed bank
;     SpriteShuffler (bank00)
;       **fixed** moved to fixed bank
;     handleSound (fixed bank but might corrupt bank/RestoreBank)

NonMaskableInterrupt:
            pha                         ; push a,x,y on to the stack
            txa
            pha
            tya
            pha
            
            lda $00
            pha
            lda $01
            pha
            lda $02
            pha
            lda $03
            pha
            lda $04
            pha
            lda $05
            pha
            lda $06
            pha
            lda $07
            pha
            
            lda temp1
            pha
            lda temp2
            pha
            lda temp3
            pha
            lda temp4
            pha
            
            lda skipNMI                 ; This is for when we want to skip most of
                                        ; the NMI, like when loading a lot of stuff.
            ora $8000                   ; Skip most nmi stuff if bank is swapped out for now
            beq dontSkipNMIStuff
            jmp skipNMIStuff
dontSkipNMIStuff:
    
            ; hud irq stuff
            lda #$1f                    ; This value only matters for $c000 and $c001
            sta $e000                   ; Acknowledge any pending interrupts
            sta $c000                   ; Set IRQ counter to number of scanlines to wait
            sta $c001                   ; Write it again to the IRQ counter latch
            sta $e001                   ; Enable IRQ

            bit PPU_STATUS              ; Reset address latch flip-flop
            lda #$00                    ; reset PPU address to avoid glitches.
            sta PPU_ADDRESS
            sta PPU_ADDRESS
            lda #$00                    ; Set the scroll to 0 for the HUD
            sta PPU_SCROLL_REG
            sta PPU_SCROLL_REG

            lda #$02                  ;perform spr-ram DMA access on $0200-$02ff
            sta SPR_DMA

            lda Mirror_PPU_CTRL_REG1  ;disable NMIs in mirror reg
;            and #%01111111            ;save all other bits
;            sta Mirror_PPU_CTRL_REG1
            and #%01111110            ;alter name table address to be $2800
            
            sta PPU_CTRL_REG1         ;(essentially $2000) but save other bits
            lda Mirror_PPU_CTRL_REG2  ;disable OAM and background display by default
            and #%11100110
            ldy DisableScreenFlag     ;get screen disable flag
            bne ScreenOff             ;if set, used bits as-is
            lda Mirror_PPU_CTRL_REG2  ;otherwise reenable bits and save them
            ora #%00011110
ScreenOff:  sta Mirror_PPU_CTRL_REG2  ;save bits for later but not in register at the moment
            and #%11100111            ;disable screen for now
            sta PPU_CTRL_REG2
            ldx PPU_STATUS            ;reset flip-flop and reset scroll registers to zero
            lda #$00
            ;jsr InitScroll
            sta PPU_SPR_ADDR          ;reset spr-ram address register

               ldx VRAM_Buffer_AddrCtrl  ;load control for pointer to buffer contents
               lda VRAM_AddrTable_Low,x  ;set indirect at $00 to pointer
               sta $00
               lda VRAM_AddrTable_High,x
               sta $01
               jsr UpdateScreen          ;update screen with buffer contents
               ldy #$00
               ldx VRAM_Buffer_AddrCtrl  ;check for usage of $0341
               cpx #$06
               bne InitBuffer
               iny                       ;get offset based on usage
InitBuffer:    ldx VRAM_Buffer_Offset,y
               lda #$00                  ;clear buffer header at last location
               sta VRAM_Buffer1_Offset,x        
               sta VRAM_Buffer1,x
               sta VRAM_Buffer_AddrCtrl  ;reinit address control to $0301
               lda Mirror_PPU_CTRL_REG2  ;copy mirror of $2001 to register
               sta PPU_CTRL_REG2
               
               ;jsr UpdateTopScore
               
               lda GamePauseStatus       ;if in pause mode, do not bother with sprites at all
               lsr
               bcs skipSpriteRemoval
               
               lda OperMode_Task       ; check OperMode_Task for ScreenRoutines
               cmp #$01
               bne doSpriteRemoval
               lda ScreenRoutineTask
               cmp #$07                ; check ScreenRoutineTask for DisplayIntermediate
               bne doSpriteRemoval
               jmp skipSpriteRemoval
doSpriteRemoval:
               jsr MoveAllSpritesOffscreen
               jsr SpriteShuffler
skipSpriteRemoval:
               lda Mirror_PPU_CTRL_REG1  ;load saved mirror of $2000
               pha
               sta PPU_CTRL_REG1
               
;               lda GamePauseStatus       ;if in pause mode, do not perform operation mode stuff
;               lsr
;               bcs SkipMainOper
;               jsr OperModeExecutionTree ;otherwise do one of many, many possible subroutines
;SkipMainOper:  
               lda PPU_STATUS            ;reset flip-flop
               pla
               ora #%10000000            ;reactivate NMIs
               sta PPU_CTRL_REG1
skipNMIStuff:
    if SOUND
        lda $8000
        bne +
        jsr handleSound           ;play sound
        +
    endif

    lda #$01
    sta vblanked

    pla
    sta temp4
    pla
    sta temp3
    pla
    sta temp2
    pla
    sta temp1

    pla
    sta $07
    pla
    sta $06
    pla
    sta $05
    pla
    sta $04
    pla
    sta $03
    pla
    sta $02
    pla
    sta $01
    pla
    sta $00

    pla                         ; pull y,x,a off the stack
    tay
    pla
    tax
    pla

    rti                       ;we are done until the next frame!

;-------------------------------------------------------------------------------------
