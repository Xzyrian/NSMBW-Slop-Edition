MMC3Setup:
         lda #$00
         sta $8000
         sta $8001
         sta $a000
         sta $a001
         sta $c000
         sta $c001
         sta $e000
         ldx #$05
LoopMMC3Setup:
         stx $8000
         lda MMC3SetupTable,x
         sta $8001
         dex
         bpl LoopMMC3Setup
         rts
MMC3SetupTable:
      .db $00, $02, $04, $05, $06, $07

setMirroring:
    sta $a000
    rts
    
; setLeftCHR sets both left CHR banks
; setRightCHR sets all 4 right CHR banks
;
; The chr is divided like this (but it can be 
; inverted to switch which side gets 2 and which
; side gets 4 banks).
;
;______________________  ______________________
;| 0                  |  | 2                  |
;|                    |  |____________________|
;|                    |  | 3                  |
;|____________________|  |____________________|
;| 1                  |  | 4                  |
;|                    |  |____________________|
;|                    |  | 5                  |
;|____________________|  |____________________|

; The values used are as if they were all 2k banks.
; An example of the values is:
; CHR0: 0
; CHR1: 2
; CHR2: 4
; CHR3: 5
; CHR4: 6
; CHR5; 7

setCHR:
    lda #$00
    sta $8000
    lda CHR0
    sta $8001

    lda #$01
    sta $8000
    lda CHR1
    sta $8001
    
    lda #$02
    sta $8000
    lda CHR2
    sta $8001

    lda #$03
    sta $8000
    lda CHR3
    sta $8001

    lda #$04
    sta $8000
    lda CHR4
    sta $8001

    lda #$05
    sta $8000
    lda CHR5
    sta $8001
rts
    
setLeftCHR:
    tax
    stx CHR0
    inx
    inx
    stx CHR1
    jsr setCHR
rts
setRightCHR:
    tax
    stx CHR2
    inx
    stx CHR3
    inx
    stx CHR4
    inx
    stx CHR5
    jsr setCHR
rts
    
setLeftCHRDirect:
    tax
    lda #$00
    sta $8000
    stx $8001

    lda #$01
    sta $8000
    inx
    inx
    stx $8001
rts


setRightCHRDirect:
    tax
    lda #$02
    sta $8000
    stx $8001
    
    lda #$03
    sta $8000
    inx
    stx $8001
    
    lda #$04
    sta $8000
    inx
    stx $8001
    
    lda #$05
    sta $8000
    inx
    stx $8001
rts
