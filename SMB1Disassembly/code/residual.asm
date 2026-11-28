; These are here just to remove warnings due to unreferenced labels.
; This way, the warnings aren't cluttered up with anything known to be fine.

; Residual labels from the original disassembly
;dummy = ResidualHeaderData
dummy = ResidualMiscObjectCode
dummy = ResidualXSpdData

; Other labels
dummy = AwardGameTimerPoints

; Our mmc3 reset puts it just past Start label so this is unused.
dummy = Start

; Reserved or yet unused labels:
dummy = BankSwap1
dummy = setLeftCHR
dummy = setLeftCHRDirect
dummy = setMirroring
dummy = setRightCHR
dummy = setRightCHRDirect
dummy = skipCustomOperModeTask
dummy = _temp

; Lables that might be removed based on settings:
dummy = LoadCustomText
dummy = RunGameTimer
;dummy = HBlankDelay
;dummy = SkipSprite0
;dummy = Sprite0Clr
dummy = Sprite0Data
