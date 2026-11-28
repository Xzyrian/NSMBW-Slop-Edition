Tim:
   pha
   txa
   pha

  ldx #$00 ;load sample number into X

  lda #$0F
  sta $4015 ;DPCM disable
  lda #$0c  ; pitch ($00-$0F)
  sta $4010
  lda #$40   ;load starting level ($00-$7F)
  lda #$7f   ;load starting level ($00-$7F)
  sta $4011 ;temp = starting sample level
  lda SampleStart,X
  sta $4012 ;X = sample number
  lda SampleLength,X
  sta $4013
  lda #$1F ;DPCM enable (plays sample)
  sta $4015

  pla
  tax
  pla

rts