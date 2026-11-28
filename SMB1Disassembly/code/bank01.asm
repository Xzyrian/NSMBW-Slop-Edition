include code\mmc3.asm


CustomText_AddrTable_Low:
      .db <CustomText0, <CustomText1, <CustomText2, <CustomText3, <CustomText4, <CustomText5, <CustomText6, <CustomText7, <CustomText8, <CustomText9
CustomText_AddrTable_High:
      .db >CustomText0, >CustomText1, >CustomText2, >CustomText3, >CustomText4, >CustomText5, >CustomText6, >CustomText7, >CustomText8, >CustomText9

CustomText0:
      .db $22, $26, "SMBBASE "
      include data\version.asm
      .db $00
CustomText1:
      .db $20, $c3, "TEST", $00
CustomText2:
      .db $20, $32, "SNOW", $00
CustomText3:
      .db $3f, $01, "%", $31, $20, $22, $22, $20, $21, $01, $00          ; the % is used to toggle ascii handling (since $20 would be a space)
CustomText4:
      .db $3f, $05, "%", $20, $21, $01, $00          ; the % is used to toggle ascii handling (since $20 would be a space)
CustomText5:
      .db $20, $80, "TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING TESTING  ", $00
CustomText6:
CustomText7:
CustomText8:
CustomText9:
      .db $20, $c3, "SORRY NOTHING", $00

; $00 - used to hold low byte of custom text address
; $01 - used to hold high byte of custom text address
; $03 - used to hold ascii handling state
LoadCustomText:
               tax                              ; The value for which text to write is in the A register.
               
               lda #$00                         
               sta $03
               
               lda CustomText_AddrTable_Low,x   ;set indirect at $00 to pointer
               sta $00
               lda CustomText_AddrTable_High,x
               sta $01
               
               ldx VRAM_Buffer1_Offset          ; load the buffer offset
               
               ldy #$00
               
               lda ($00),y                      ; load the first byte of our text (vram address high byte)
               sta VRAM_Buffer1,x               ; write to the buffer
               inx
               iny
               lda ($00),y                      ; load the second byte of our text (vram address low byte)
               sta VRAM_Buffer1,x               ; write to the buffer
               
               ldy #$02
               inx
               inx
CustomTextLoop:
               lda ($00),y
               beq CustomTextDone
               
               ; check for "%".  the "%" acts as an escape, toggling
               ; whether or not it handles ascii.
               cmp #$25
               bne NotACode
               
               lda $03
               eor #$01
               sta $03

               inc $00
               lda $00
               bne NoIncCustomTextAddr
               inc $01
NoIncCustomTextAddr:
NotACode:
               lda $03
               beq EscapeToggleIsOff
               
               lda ($00),y
               jmp NotANumber
EscapeToggleIsOff:
               lda ($00),y
               
               ; check for a space
               cmp #$20
               bne NotASpace
               clc
               adc #$04                         ; add 4 if it's a space
NotASpace:
               ; Check for letters A-Z
               cmp #$41
               bcc NotALetter                   ; Branch if it's less than $41
               cmp #$5b
               bcs NotALetter                   ; Branch if it's greater than or equal to $5b
               
               sec
               sbc #$37                         ; Subtract amount to convert A-Z from ascii.
NotALetter:
               ; Check for numbers 0-9
               cmp #$30
               bcc NotANumber                   ; Branch if it's less than $30
               cmp #$3a
               bcs NotANumber                   ; Branch if it's greater than or equal to $3a
               
               sec
               sbc #$30                         ; Subtract amount to convert 0-9 from ascii.
NotANumber:
               sta VRAM_Buffer1,x               ; Store the tile in the buffer
               inx                              ; increment x for the buffer
               iny                              ; increment y for the CustomText index
               
               bne CustomTextLoop               ; branch is unconditional due to earlier checking
CustomTextDone:
               sta VRAM_Buffer1,x               ; store the terminating $00 in the buffer
               
               dey                              ; subtract 2 from the CustomText index to get text length
               dey
               sty VRAM_Buffer1+2               ; store text length in the buffer
               stx VRAM_Buffer1_Offset          ; update the buffer offset
               
               rts

CustomCode:
        ; you can put a lot of custom code here.
        
;        lda GamePauseStatus
;        and #%00000001
;        beq +
;        lda #%11111110
;        sta PPU_CTRL_REG2
+
        
        ; Set title screen CHR
        if DEMO_FEATURES == 1
            ldy #$01           ; load #$01 by default
            lda OperMode       ; check if we're in title screen (OperMode == 0)
            bne +              ; branch ahead to "+" if not OperMode is not 0
            ldy #$00           ; load #$00 if in title
+
            clc
            tya
            asl
            adc #$01
            asl
            asl
            jsr setRightCHR
        endif
skipCustomOperModeTask:
         
         lda OperMode_Task
         cmp #$01
         bne skipCustomScreenRoutineTask
         
         lda ScreenRoutineTask                  ; load ScreenRoutineTask
         cmp $6011                              ; compare it to our stored ScreenRoutineTask
         sta $6011                              ; store ScreenRoutineTask
         beq skipCustomScreenRoutineTask        ; branch if they're the same
         
         ; here we run code when ScreenRoutineTask modes are initially set
         
        ; Display a message on intermediate screen
        if DEMO_FEATURES == 1
            cmp #$07                               ; check ScreenRoutineTask for DisplayIntermediate
            bne +                                  ; branch if not

            lda #$00                               ; load message
            jsr LoadCustomText                     ; display it
        endif
+
skipCustomScreenRoutineTask:
         
        ; Set CHR based on PlayerSize as an example of 
        ; CHR switching capabilities.  The goomba will
        ; have Pac-Man ghost eyes when you are small.
        
        if DEMO_FEATURES == 1
            lda PlayerSize
            asl
            asl
            asl
            jsr setLeftCHR
        endif
        
        jsr setCHR
rts

