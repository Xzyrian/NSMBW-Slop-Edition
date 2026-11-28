; $00
; $01
; use like this:
;    ; copy Hidden1UpFlag from on screen player to all offscreen players
;    lda Hidden1UpFlag-OnscreenPlayerInfo
;    jsr CopyToAllPlayers

_WipePlayerData:
        ldx #NumberOfCharacters * $10
        lda #$00
-
        sta save_playerData-1,x
        dex
        bne -
        
        ldx $10-1
-
        sta OnscreenPlayerInfo-1,x
        dex
        bne -
rts

_CopyToAllPlayers:
        ;tay
        
        txa
        pha
        
        
        ldx #$02
-
        txa
        asl
        asl
        asl
        asl
        sta $01
        
        clc
        lda <save_playerData
        adc $01 ; add stored offset
        sta $00
        lda >save_playerData
        sta $01 ; use this for the high byte now
        
        lda OnscreenPlayerInfo,y
        sta ($00),y
        
        dex
        bne -
        
        pla
        tax
rts

_SavePlayerData:
           lda CurrentPlayer
           asl
           asl
           asl
           asl
           tay
           
           ldx #$06
-
           lda OnscreenPlayerInfo,x
           sta save_playerData,y
           iny
           dex
           bne -
rts

_LoadPlayerData:
           lda CurrentPlayer
           asl
           asl
           asl
           asl
           tay
           
           ldx #$06
-
           lda save_playerData,y
           sta OnscreenPlayerInfo,x
           iny
           dex
           bne -
rts
