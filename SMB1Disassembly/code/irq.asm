IRQ:
    sei
    
    pha                         ; push a,x,y on to the stack
    txa
    pha
    tya
    pha

    ; Set skipNMI so it doesn't jump back into nmi in the middle of ppu stuff.
    ; Would this ever happen from here?  I think it wouldn't but not sure.
    lda #$01
    sta skipNMI

    sta $e000                   ; Acknowledge the IRQ and disable.
    
    
    bit PPU_STATUS              ; Reset address latch flip-flop

    lda HorizontalScroll        ; Set our scroll values here after the hud split.
    sta PPU_SCROLL_REG
    lda VerticalScroll
    sta PPU_SCROLL_REG
    lda #$00
    sta skipNMI
    
    pla                         ; pull y,x,a off the stack
    tay
    pla
    tax
    pla
    
    cli

    rti
