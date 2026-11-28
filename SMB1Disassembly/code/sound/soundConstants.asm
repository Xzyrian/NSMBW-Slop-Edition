;80: Dotted Quarter
;86: Quarter Note
;85: Dotted 8th
;84: 8th Note
;87: 8th Triplet
;82: 16th Note
;83: 16th Triplet
;81: 32nd Triplet

nDottedQuarter = $80
nQuarter = $86
nDotted8th = $85
n8th = $84
n8thTriplet = $87
n16th = $82
n16thTriplet = $83
n32ndTriplet = $81

G6 = $58
E6 = $56
D6 = $02 ; (In my opinion, 02 and 64 should have exchanged their pitch data in SMB1. See quote.)
C6 = $54
Bb5 = $52
Ab5 = $50 
G5 = $4E
; (Fs5 = No data)
F5 = $4C
E5 = $44
Eb5 = $4A
D5 = $48
Cs5 = $46
C5 = $64 
B4 = $42 
Bb4 = $3E ; (this breaks sequence, because of the LEVEL CLEAR music)
A4 = $40 ; (ditto)
Ab4 = $3C
G4 = $3A
Fs4 = $38
F4 = $36
E4 = $34
Eb4 = $32
D4 = $30
Cs4 = $2E
C4 = $2C ; [This is Middle C]
B3 = $2A
Bb3 = $28
A3 = $26
Ab3 = $24
G3 = $22
Fs3 = $20
F3 = $1E
E3 = $1C
Eb3 = $1A
D3 = $18
Cs3 = $16
C3 = $14
B2 = $12
Bb2 = $10
A2 = $62 ; (don't ask) 
Ab2 = $0E
G2 = $0C
Fs2 = $0A
F2 = $08
E2 = $06
Eb2 = $60
D2 = $5E
C2 = $5C
G2 = $5A
S = $04 ; Silence

G4Special = $00 ; (Only for Tri) = A note a little higher than G4.

; ---------------

; Dotted Quarter(Rhythm=80)
Bb4_DottedQuarter = $3e
Ab4_DottedQuarter = $3c
G4_DottedQuarter = $3a
Fs4_DottedQuarter = $38
F4_DottedQuarter = $36
E4_DottedQuarter = $34
Eb4_DottedQuarter = $32
D4_DottedQuarter = $30
Cs4_DottedQuarter = $2e
C4_DottedQuarter = $2c
B3_DottedQuarter = $2a
Bb3_DottedQuarter = $28
A3_DottedQuarter = $26
Ab3_DottedQuarter = $24
G3_DottedQuarter = $22
Fs3_DottedQuarter = $20
F3_DottedQuarter = $1e
E3_DottedQuarter = $1c
Eb3_DottedQuarter = $1a
D3_DottedQuarter = $18
Cs3_DottedQuarter = $16
C3_DottedQuarter = $14
B2_DottedQuarter = $12
Bb2_DottedQuarter = $10
Ab2_DottedQuarter = $0e
G2_DottedQuarter = $0c
Fs2_DottedQuarter = $0a
F2_DottedQuarter = $08
E2_DottedQuarter = $06
S_DottedQuarter = $04
D6_DottedQuarter = $02
Special_DottedQuarter = $00

; Quarter Note(86)
Bb4_Quarter = $bf
Ab4_Quarter = $bd
G4_Quarter = $bb
Fs4_Quarter = $b9
F4_Quarter = $b7
E4_Quarter = $b5
Eb4_Quarter = $b3
D4_Quarter = $b1
Cs4_Quarter = $af
C4_Quarter = $ad
B3_Quarter = $ab
Bb3_Quarter = $a9
A3_Quarter = $a7
Ab3_Quarter = $a5
G3_Quarter = $a3
Fs3_Quarter = $a1
F3_Quarter = $9f
E3_Quarter = $9d
Eb3_Quarter = $9b
D3_Quarter = $99
Cs3_Quarter = $97
C3_Quarter = $95
B2_Quarter = $93
Bb2_Quarter = $91
Ab2_Quarter = $8f
G2_Quarter = $8d
Fs2_Quarter = $8b
F2_Quarter = $89
E2_Quarter = $87
S_Quarter = $85
D6_Quarter = $83
Ab4_Quarter = $81 ; (Actually this is the note 'a little bit higher than G-4'.)

; Dotted 8th(85)
Bb4_Dotted8th = $7f
Ab4_Dotted8th = $7d
G4_Dotted8th = $7b
Fs4_Dotted8th = $79
F4_Dotted8th = $77
E4_Dotted8th = $75
Eb4_Dotted8th = $73
D4_Dotted8th = $71
Cs4_Dotted8th = $6f
C4_Dotted8th = $6d
B3_Dotted8th = $6b
Bb3_Dotted8th = $69
A3_Dotted8th = $67
Ab3_Dotted8th = $65
G3_Dotted8th = $63
Fs3_Dotted8th = $61
F3_Dotted8th = $5f
E3_Dotted8th = $5d
Eb3_Dotted8th = $5b
D3_Dotted8th = $59
Cs3_Dotted8th = $57
C3_Dotted8th = $55
B2_Dotted8th = $53
Bb2_Dotted8th = $51
Ab2_Dotted8th = $4f
G2_Dotted8th = $4d
Fs2_Dotted8th = $4b
F2_Dotted8th = $49
E2_Dotted8th = $47
S_Dotted8th = $45
D6_Dotted8th = $43
Ab4_Dotted8th = $41 ; (like last one, you know)

; 8th Note(84)
Bb4_8th = $3F
Ab4_8th = $3D
G4_8th = $3B
Fs4_8th = $39
F4_8th = $37
E4_8th = $35
Eb4_8th = $33
D4_8th = $31
Cs4_8th = $2F
C4_8th = $2D
B3_8th = $2B
Bb3_8th = $29
A3_8th = $27
Ab3_8th = $25
G3_8th = $23
Fs3_8th = $21
F3_8th = $1F
E3_8th = $1D
Eb3_8th = $1B
D3_8th = $19
Cs3_8th = $17
C3_8th = $15
B2_8th = $13
Bb2_8th = $11
Ab2_8th = $0F
G2_8th = $0D
Fs2_8th = $0B
F2_8th = $09
E2_8th = $07
Silence_8th = $05
D6_8th = $03
Ab4_8th = $01

; 8th Triplet(87)
Bb4_8thTriplet = $FF
Ab4_8thTriplet = $FD
G4_8thTriplet = $FB
Fs4_8thTriplet = $F9
F4_8thTriplet = $F7
E4_8thTriplet = $F5
Eb4_8thTriplet = $F3
D4_8thTriplet = $F1
Cs4_8thTriplet = $EF
C4_8thTriplet = $ED
B3_8thTriplet = $EB
Bb3_8thTriplet = $E9
A3_8thTriplet = $E7
Ab3_8thTriplet = $E5
G3_8thTriplet = $E3
Fs3_8thTriplet = $E1
F3_8thTriplet = $DF
E3_8thTriplet = $DD
Eb3_8thTriplet = $DB
D3_8thTriplet = $D9
Cs3_8thTriplet = $D7
C3_8thTriplet = $D5
B2_8thTriplet = $D3
Bb2_8thTriplet = $D1
Ab2_8thTriplet = $CF
G2_8thTriplet = $CD
Fs2_8thTriplet = $CB
F2_8thTriplet = $C9
E2_8thTriplet = $C7
Silence_8thTriplet = $C5
D6_8thTriplet = $C3
Ab4_8thTriplet = $C1

; 16th note(82)
Bb4_16th = $BE
Ab4_16th = $BC
G4_16th = $BA
Fs4_16th = $B8
F4_16th = $B6
E4_16th = $B4
Eb4_16th = $B2
D4_16th = $B0
Cs4_16th = $AE
C4_16th = $AC
B3_16th = $AA
Bb3_16th = $A8
A3_16th = $A6
Ab3_16th = $A4
G3_16th = $A2
Fs3_16th = $A0
F3_16th = $9E
E3_16th = $9C
Eb3_16th = $9A
D3_16th = $98
Cs3_16th = $96
C3_16th = $94
B2_16th = $92
Bb2_16th = $90
Ab2_16th = $8E
G2_16th = $8C
Fs2_16th = $8A
F2_16th = $88
E2_16th = $86
Silence_16th = $84
D6_16th = $82
Ab4_16th = $80

; 16th Triplet(83)
Bb4_16thTriplet = $FE
Ab4_16thTriplet = $FC
G4_16thTriplet = $FA
Fs4_16thTriplet = $F8
F4_16thTriplet = $F6
E4_16thTriplet = $F4
Eb4_16thTriplet = $F2
D4_16thTriplet = $F0
Cs4_16thTriplet = $EE
C4_16thTriplet = $EC
B3_16thTriplet = $EA
Bb3_16thTriplet = $E8
A3_16thTriplet = $E6
Ab3_16thTriplet = $E4
G3_16thTriplet = $E2
Fs3_16thTriplet = $E0
F3_16thTriplet = $DE
E3_16thTriplet = $DC
Eb3_16thTriplet = $DA
D3_16thTriplet = $D8
Cs3_16thTriplet = $D6
C3_16thTriplet = $D4
B2_16thTriplet = $D2
Bb2_16thTriplet = $D0
Ab2_16thTriplet = $CE
G2_16thTriplet = $CC
Fs2_16thTriplet = $CA
F2_16thTriplet = $C8
E2_16thTriplet = $C6
Silence_16thTriplet = $C4
D6_16thTriplet = $C2
Ab4_16thTriplet = $C0

; 32nd Triplet(81)
Bb4_3ndTriplet = $7E
Ab4_3ndTriplet = $7C
G4_3ndTriplet = $7A
Fs4_3ndTriplet = $78
F4_3ndTriplet = $76
E4_3ndTriplet = $74
Eb4_3ndTriplet = $72
D4_3ndTriplet = $70
Cs4_3ndTriplet = $6E
C4_3ndTriplet = $6C
B3_3ndTriplet = $6A
Bb3_3ndTriplet = $68
A3_3ndTriplet = $66
Ab3_3ndTriplet = $64
G3_3ndTriplet = $62
Fs3_3ndTriplet = $60
F3_3ndTriplet = $5E
E3_3ndTriplet = $5C
Eb3_3ndTriplet = $5A
D3_3ndTriplet = $58
Cs3_3ndTriplet = $56
C3_3ndTriplet = $54
B2_3ndTriplet = $52
Bb2_3ndTriplet = $50
Ab2_3ndTriplet = $4E
G2_3ndTriplet = $4C
Fs2_3ndTriplet = $4A
F2_3ndTriplet = $48
E2_3ndTriplet = $46
Silence_32ndTriplet = $44
D6_3ndTriplet = $42
Ab4_3ndTriplet = $40

; ----------------------

;Dotted Quarter(80)
Chee_DottedQuarter = $30
Ko_DottedQuarter = $20
Chi_DottedQuarter = $10

;Quarter Note(86)
Chee_Quarter = $B1
Ko_Quarter = $A1
Chi_Quarter = $91

;Dotted 8th(85)
Chee_Dotted8th = $71
Ko_Dotted8th = $61
Chi_Dotted8th = $51

;8th Note(84)
Chee_8th = $31
Ko_8th = $21
Chi_8th = $11

;8th Triplet(87)
Chee_8thTriplet = $F1
Ko_8thTriplet = $E1
Chi_8thTriplet = $D1

;16th Note(82)
Chee_16th = $B0
Ko_16th = $A0
Chi_16th = $90

;16th Triplet(83)
Chee_16thTriplet = $F0
Ko_16thTriplet = $E0
Chi_16thTriplet = $D0

;32nd Triplet(81)
Chee_32ndTriplet = $70
Ko_32ndTriplet = $60
Chi_32ndTriplet = $50

; ------------

;Dotted Quarter(80)
HiHat_DottedQuarter = $30
Kick_DottedQuarter = $20
Snare_DottedQuarter = $10

;Quarter Note(86)
HiHat_Quarter = $B1
Kick_Quarter = $A1
Snare_Quarter = $91

;Dotted 8th(85)
HiHat_Dotted8th = $71
Kick_Dotted8th = $61
Snare_Dotted8th = $51

;8th Note(84)
HiHat_8th = $31
Kick_8th = $21
Snare_8th = $11

;8th Triplet(87)
HiHat_8thTriplet = $F1
Kick_8thTriplet = $E1
Snare_8thTriplet = $D1

;16th Note(82)
HiHat_16th = $B0
Kick_16th = $A0
Snare_16th = $90

;16th Triplet(83)
HiHat_16thTriplet = $F0
Kick_16thTriplet = $E0
Snare_16thTriplet = $D0

;32nd Triplet(81)
HiHat_32ndTriplet = $70
Kick_32ndTriplet = $60
Snare_32ndTriplet = $50



; A lot of this stuff is missing notes and really pure garbage :(

Gs4_16th=Ab4_16th
A4_16th=A3_16th
As4_16th=Bb4_16th
Ds5_16th=A3_16th

Gs2=Ab2
Gs3=Ab3
Gs4=Ab4
Gs5=Ab5

Cs2=D2
Cs3=D3
Cs4=D4
Cs5=D5
Cs6=C6

Fs2=F2
Fs3=F3
Fs4=F4
Fs5=F5

Ds2=Eb2
Ds3=Eb3
Ds4=Eb4
Ds5=Eb5


As2=Bb2
As3=Bb3
As4=Bb4
As5=Bb5

A5=G5
Cs5_16th=Bb4_16th
C5_16th =Bb4_16th

F5_16th=F4_16th
Ds4_16th=S
As2_16th=S
Ds3_16th=S
As3_16th=S
Gs3_16th=S
Gs2_16th=S

E6_16th=E4_16th

Ds1_16th = S
Fs1_16th = S

As1_16th = S
A1_16th = S

Cs2_16th = S