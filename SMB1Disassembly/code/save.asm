save_Validate = $7fff
save_Validate_value = $42
save_TopScore = $7f00


LoadBattery:
        jsr ReadJoypads
        lda SavedJoypad1Bits
        cmp #Select_Button+Up_Dir+A_Button
        bne +
        lda #$00
        sta save_Validate
+
        
        jsr InitBattery

        ldx #$05
-
        lda save_TopScore,x
        sta TopScoreDisplay,x
        dex
        bpl -

rts

InitBattery:
        lda save_Validate
        cmp #save_Validate_value
        beq +


        ldx #$05
        lda #$00
-
        ;lda TopScoreDisplay,x
        sta save_TopScore,x
        dex
        bpl -

        lda #save_Validate_value
        sta save_Validate
+
rts

SaveBattery:
        jsr InitBattery

        ldx #$05
-
        lda TopScoreDisplay,x
        sta save_TopScore,x
        dex
        bpl -
rts
