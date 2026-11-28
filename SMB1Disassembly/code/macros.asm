macro bricks x,y,w
    .db x*$10+y, Objects1Flag + $01 * $10 + w - $01             ; (x,y) row of w bricks
endm

; levelHeader $00,$02,$01,$01,$02,$00
; scenery_bgcolor
; entrance, timer
; terrain_control
; background_scenery_type
; background_scenery
macro levelHeader scenery_bgcolor, entrance, timer, terrain_control, background_scenery_type, background_scenery
    ; Header (first byte): scenery/bg color + player entrance control * $08 + timer setting * $40
    ; Header (second byte): terrain control + background scenery type * $10 + background scenery * $40
    .db scenery_bgcolor + entrance * $08 + timer * $40
    .db terrain_control + background_scenery_type * $10 + background_scenery * $40
endm

; does a jsr twice
macro jsrx2 addr
    jsr addr
    jsr addr
endm