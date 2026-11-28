; Convert the value in the A register to decimal digits
; $00 hundreds digit
; $01 tens digit
; $02 ones digit
convertNumber:
    ldx #$00
    ldy #$00
-
    stx $00,y
    iny
    cpy #$03
    bne -
    ldy #$02
-
    cmp decimalPlaceValues, y
    bcc +
    sbc decimalPlaceValues, y
    inc $00,x
    jmp -
+
    cpy #$00
    beq +
    dey
    inx
    jmp -
+
    ldy #$00
-
    ; replace digit with space if 0, starting from leftmost digit
    lda $00,y
    bne +           ; exit routine if not 0
    lda #$24
    sta $00,y
    
    iny
    cpy #$02
    bne -
+
rts

decimalPlaceValues:
    .db $01, $0a, $64

;hexTable:
;    .db $00, $01, $02, $03, $04, $05, $06, $07, $08, $09, $0a, $0b, $0c, $0d, $0e, $0f
