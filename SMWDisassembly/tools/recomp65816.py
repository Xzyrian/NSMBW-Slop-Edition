#!/usr/bin/env python3
"""recomp65816.py - static recompiler: Super Mario World (65816, LoROM) -> C.

Input: the ROM assembled from the disassembly (tools/build_smw.py, with Asar) and Asar's WLA
symbol file, whose [addr-to-line mapping] gives, for every address that made bytes, the source
line that made them. A line whose first word is a 65816 instruction (65816 code: not the SPC700
engine between `arch spc700` and `arch 65816`) is code; so is whatever follows an instruction
that doesn't end the flow (`DEX #3` maps once and makes three). Nothing is guessed from bytes.

Output (out/):
  smw_bNN.c     one per ROM bank with code: `int smw_bNN(uint16_t pc)` - a switch over the
                bank's instruction addresses, then each instruction as C (port/snes_gen.h);
  smw_interp.c  the same instructions as an interpreter (code SMW builds in RAM; anything not
                recompiled), generated from the same table so both mean the same;
  smw_table.c   the bank table and the labels (for logs); smw_syms.h: SMW's RAM names.

Widths. An immediate's size is the assembled one (the source says .B / .W on every one); every
other width-dependent instruction tests the M / X flags as it runs (port/snes_gen.h), so no flag
state is guessed either.

Model (port/snes_cpu.c): the stack in WRAM is the truth; JSR / JSL push their return address and
are also a C call (snes_call) that expects the next instruction back. An RTS / RTL to another
address (SMW's ExecutePtr pulls its caller's address to read the table after it) unwinds or is a
jump, as in tools/recomp6502.py (SMB3).
"""
import re, sys, os, argparse

# ---- the 65816: opcode -> (mnemonic, mode)
T = """
00 BRK sig  01 ORA dpxi 02 COP sig  03 ORA sr   04 TSB dp   05 ORA dp   06 ASL dp   07 ORA dpil
08 PHP imp  09 ORA immm 0A ASL acc  0B PHD imp  0C TSB abs  0D ORA abs  0E ASL abs  0F ORA long
10 BPL rel  11 ORA dpiy 12 ORA dpi  13 ORA sriy 14 TRB dp   15 ORA dpx  16 ASL dpx  17 ORA dpily
18 CLC imp  19 ORA absy 1A INC acc  1B TCS imp  1C TRB abs  1D ORA absx 1E ASL absx 1F ORA longx
20 JSR abs  21 AND dpxi 22 JSL long 23 AND sr   24 BIT dp   25 AND dp   26 ROL dp   27 AND dpil
28 PLP imp  29 AND immm 2A ROL acc  2B PLD imp  2C BIT abs  2D AND abs  2E ROL abs  2F AND long
30 BMI rel  31 AND dpiy 32 AND dpi  33 AND sriy 34 BIT dpx  35 AND dpx  36 ROL dpx  37 AND dpily
38 SEC imp  39 AND absy 3A DEC acc  3B TSC imp  3C BIT absx 3D AND absx 3E ROL absx 3F AND longx
40 RTI imp  41 EOR dpxi 42 WDM sig  43 EOR sr   44 MVP blk  45 EOR dp   46 LSR dp   47 EOR dpil
48 PHA imp  49 EOR immm 4A LSR acc  4B PHK imp  4C JMP abs  4D EOR abs  4E LSR abs  4F EOR long
50 BVC rel  51 EOR dpiy 52 EOR dpi  53 EOR sriy 54 MVN blk  55 EOR dpx  56 LSR dpx  57 EOR dpily
58 CLI imp  59 EOR absy 5A PHY imp  5B TCD imp  5C JML long 5D EOR absx 5E LSR absx 5F EOR longx
60 RTS imp  61 ADC dpxi 62 PER rell 63 ADC sr   64 STZ dp   65 ADC dp   66 ROR dp   67 ADC dpil
68 PLA imp  69 ADC immm 6A ROR acc  6B RTL imp  6C JMP ind  6D ADC abs  6E ROR abs  6F ADC long
70 BVS rel  71 ADC dpiy 72 ADC dpi  73 ADC sriy 74 STZ dpx  75 ADC dpx  76 ROR dpx  77 ADC dpily
78 SEI imp  79 ADC absy 7A PLY imp  7B TDC imp  7C JMP indx 7D ADC absx 7E ROR absx 7F ADC longx
80 BRA rel  81 STA dpxi 82 BRL rell 83 STA sr   84 STY dp   85 STA dp   86 STX dp   87 STA dpil
88 DEY imp  89 BIT immm 8A TXA imp  8B PHB imp  8C STY abs  8D STA abs  8E STX abs  8F STA long
90 BCC rel  91 STA dpiy 92 STA dpi  93 STA sriy 94 STY dpx  95 STA dpx  96 STX dpy  97 STA dpily
98 TYA imp  99 STA absy 9A TXS imp  9B TXY imp  9C STZ abs  9D STA absx 9E STZ absx 9F STA longx
A0 LDY immx A1 LDA dpxi A2 LDX immx A3 LDA sr   A4 LDY dp   A5 LDA dp   A6 LDX dp   A7 LDA dpil
A8 TAY imp  A9 LDA immm AA TAX imp  AB PLB imp  AC LDY abs  AD LDA abs  AE LDX abs  AF LDA long
B0 BCS rel  B1 LDA dpiy B2 LDA dpi  B3 LDA sriy B4 LDY dpx  B5 LDA dpx  B6 LDX dpy  B7 LDA dpily
B8 CLV imp  B9 LDA absy BA TSX imp  BB TYX imp  BC LDY absx BD LDA absx BE LDX absy BF LDA longx
C0 CPY immx C1 CMP dpxi C2 REP imm8 C3 CMP sr   C4 CPY dp   C5 CMP dp   C6 DEC dp   C7 CMP dpil
C8 INY imp  C9 CMP immm CA DEX imp  CB WAI imp  CC CPY abs  CD CMP abs  CE DEC abs  CF CMP long
D0 BNE rel  D1 CMP dpiy D2 CMP dpi  D3 CMP sriy D4 PEI dp   D5 CMP dpx  D6 DEC dpx  D7 CMP dpily
D8 CLD imp  D9 CMP absy DA PHX imp  DB STP imp  DC JML indl DD CMP absx DE DEC absx DF CMP longx
E0 CPX immx E1 SBC dpxi E2 SEP imm8 E3 SBC sr   E4 CPX dp   E5 SBC dp   E6 INC dp   E7 SBC dpil
E8 INX imp  E9 SBC immm EA NOP imp  EB XBA imp  EC CPX abs  ED SBC abs  EE INC abs  EF SBC long
F0 BEQ rel  F1 SBC dpiy F2 SBC dpi  F3 SBC sriy F4 PEA abs  F5 SBC dpx  F6 INC dpx  F7 SBC dpily
F8 SED imp  F9 SBC absy FA PLX imp  FB XCE imp  FC JSR indx FD SBC absx FE INC absx FF SBC longx
"""
OPS = {}
for code, m, mode in re.findall(r'([0-9A-F]{2}) (\w{3}) (\w+)', T): OPS[int(code, 16)] = (m, mode)
assert len(OPS) == 256
SIZE = {'imp': 1, 'acc': 1, 'sig': 2, 'imm8': 2, 'dp': 2, 'dpx': 2, 'dpy': 2, 'dpi': 2, 'dpxi': 2, 'dpiy': 2, 'dpil': 2,
        'dpily': 2, 'sr': 2, 'sriy': 2, 'rel': 2, 'abs': 3, 'absx': 3, 'absy': 3, 'ind': 3, 'indx': 3, 'indl': 3, 'rell': 3,
        'blk': 3, 'long': 4, 'longx': 4}
MNEMS = {v[0] for v in OPS.values()}
# a rough cycle count (slow ROM): enough for the frame's time
CYC = {'imp': 2, 'acc': 2, 'sig': 7, 'imm8': 3, 'immm': 2, 'immx': 2, 'dp': 3, 'dpx': 4, 'dpy': 4, 'dpi': 5, 'dpxi': 6,
       'dpiy': 5, 'dpil': 6, 'dpily': 6, 'sr': 4, 'sriy': 7, 'rel': 2, 'abs': 4, 'absx': 4, 'absy': 4, 'ind': 5, 'indx': 6,
       'indl': 6, 'rell': 4, 'blk': 7, 'long': 5, 'longx': 5}
EA = {'dp': 'EA_DP', 'dpx': 'EA_DPX', 'dpy': 'EA_DPY', 'dpi': 'EA_DPI', 'dpxi': 'EA_DPXI', 'dpiy': 'EA_DPIY', 'dpil': 'EA_DPIL',
      'dpily': 'EA_DPILY', 'sr': 'EA_SR', 'sriy': 'EA_SRIY', 'abs': 'EA_ABS', 'absx': 'EA_ABSX', 'absy': 'EA_ABSY',
      'long': 'EA_LONG', 'longx': 'EA_LONGX'}
MEMOPS = {'LDA', 'LDX', 'LDY', 'STA', 'STX', 'STY', 'STZ', 'AND', 'ORA', 'EOR', 'ADC', 'SBC', 'CMP', 'CPX', 'CPY', 'BIT', 'TSB', 'TRB'}
RMW = {'ASL': 'asl', 'LSR': 'lsr', 'ROL': 'rol', 'ROR': 'ror', 'INC': 'inc', 'DEC': 'dec'}
SIMPLE = {'INX': 'OP_INX();', 'INY': 'OP_INY();', 'DEX': 'OP_DEX();', 'DEY': 'OP_DEY();', 'TAX': 'OP_TAX();', 'TAY': 'OP_TAY();',
          'TXA': 'OP_TXA();', 'TYA': 'OP_TYA();', 'TXY': 'OP_TXY();', 'TYX': 'OP_TYX();', 'TSX': 'OP_TSX();', 'TXS': 'OP_TXS();',
          'TCD': 'OP_TCD();', 'TDC': 'OP_TDC();', 'TCS': 'OP_TCS();', 'TSC': 'OP_TSC();', 'XBA': 'OP_XBA();', 'PHA': 'OP_PHA();',
          'PHX': 'OP_PHX();', 'PHY': 'OP_PHY();', 'PLA': 'OP_PLA();', 'PLX': 'OP_PLX();', 'PLY': 'OP_PLY();', 'PHP': 'OP_PHP();',
          'PLP': 'OP_PLP();', 'PHB': 'OP_PHB();', 'PLB': 'OP_PLB();', 'PHD': 'OP_PHD();', 'PLD': 'OP_PLD();',
          'CLC': 'R.c = 0;', 'SEC': 'R.c = 1;', 'CLI': 'R.i = 0;', 'SEI': 'R.i = 1;', 'CLD': 'R.dm = 0;', 'SED': 'R.dm = 1;',
          'CLV': 'R.v = 0;', 'NOP': '', 'XCE': 'OP_XCE();'}
BRANCH = {'BPL': '!R.n', 'BMI': 'R.n', 'BVC': '!R.v', 'BVS': 'R.v', 'BCC': '!R.c', 'BCS': 'R.c', 'BNE': '!R.z', 'BEQ': 'R.z', 'BRA': '1'}
ENDS = {'JMP', 'JML', 'RTS', 'RTL', 'RTI', 'BRA', 'BRL', 'STP', 'BRK', 'COP'}

def data_op(m, mode, opnd, imm_bytes):
    """C for a non-control instruction. opnd: C expression for the operand (byte / word / long).
    imm_bytes: for immediates, 1 or 2 (the assembled width)."""
    if mode in ('immm', 'immx'):
        return 'OP_%s_I%d(%s);' % (m, 8 * imm_bytes, opnd)
    if m in MEMOPS: return 'OP_%s(%s(%s));' % (m, EA[mode], opnd)
    if m in RMW:
        if mode == 'acc': return 'RMW_A(%s);' % RMW[m]
        return 'RMW_M(%s, %s(%s));' % (RMW[m], EA[mode], opnd)
    if m in SIMPLE: return SIMPLE[m]
    if m == 'REP': return 'OP_REP(%s);' % opnd
    if m == 'SEP': return 'OP_SEP(%s);' % opnd
    if m == 'PEA': return 'OP_PEA(%s);' % opnd
    if m == 'PEI': return 'OP_PEI(%s);' % opnd
    if m == 'WDM': return ''
    raise ValueError(m + ' ' + mode)

# ---- the source: which bytes are 65816 instructions
def read_sym(path):
    files, mp, labels, sec = {}, [], {}, None
    for l in open(path, encoding='latin1'):
        l = l.rstrip('\n')
        if l.startswith('['): sec = l; continue
        if not l.strip() or l.startswith(';'): continue
        if sec == '[source files]':
            p = l.split(None, 2); files[int(p[0], 16)] = p[2]
        elif sec == '[addr-to-line mapping]':
            a, b = l.split(); bk, ad = a.split(':'); f, ln = b.split(':')
            mp.append((int(bk, 16), int(ad, 16), int(f, 16), int(ln, 16)))
        elif sec == '[labels]':
            a, name = l.split(None, 1); bk, ad = a.split(':')
            if name.startswith(':'): continue                     # (asar's macro markers)
            labels.setdefault((int(bk, 16), int(ad, 16)), name)
    return files, mp, labels

def arch_map(lines):
    """per line (1-based): 1 if 65816, 0 if SPC700"""
    out, cur = [1], 1
    for l in lines:
        t = l.split(';')[0].strip().lower()
        if t.startswith('arch '): cur = 0 if 'spc700' in t else 1
        out.append(cur)
    return out

INSN = re.compile(r'^(?:[A-Za-z_][A-Za-z0-9_]*:|\.[A-Za-z0-9_]+:?|[-+]+)?\s*([A-Za-z<][A-Za-z0-9_>]*)(\.[bBwWlL])?\b')
def classify(root, files, mp):
    """(bank, addr) -> immediate width from the source ('.B' 1 / '.W' 2 / None) for each instruction"""
    src = {k: open(os.path.join(root, v), encoding='latin1').read().split('\n') for k, v in files.items()}
    arch = {k: arch_map(v) for k, v in src.items()}
    code = {}
    for bk, ad, f, ln in mp:
        if not arch[f][ln]: continue
        t = src[f][ln - 1].split(';')[0].strip()
        if files[f] == 'macros.asm' and re.match(r'^(if\b|else\b)', t, re.I):
            t = src[f][ln].split(';')[0].strip()           # (Asar maps an instruction made in a macro's if / else to that line)
        m = INSN.match(t)
        if not m: continue
        w = m.group(1).upper()
        if w not in MNEMS and not w.startswith('<'): continue
        suf = (m.group(2) or '').upper()
        code[(bk, ad)] = {'.B': 1, '.W': 2}.get(suf)
    return code

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('rom'); ap.add_argument('sym'); ap.add_argument('root'); ap.add_argument('outdir')
    ap.add_argument('--hooks')
    a = ap.parse_args()
    rom = open(a.rom, 'rb').read()
    if len(rom) % 0x8000 == 512: rom = rom[512:]
    files, mp, labels = read_sym(a.sym)
    code = classify(a.root, files, mp)
    def b(bk, ad): return rom[(bk & 0x7F) * 0x8000 + (ad & 0x7FFF)]
    def w(bk, ad): return b(bk, ad) | b(bk, ad + 1) << 8
    def l(bk, ad): return w(bk, ad) | b(bk, ad + 2) << 16
    insn = {}                                                  # (bank, addr) -> (m, mode, size, immbytes)
    work = sorted(k for k in code if k[1] >= 0x8000 and k[0] < 0x40)
    while work:
        bk, ad = k = work.pop()
        if k in insn: continue
        m, mode = OPS[b(bk, ad)]
        ib = None
        if mode in ('immm', 'immx'):
            ib = code.get(k)
            if ib is None: sys.exit('$%02X:%04X: %s # without .B / .W' % (bk, ad, m))
        size = SIZE[mode] if ib is None else 1 + ib
        insn[k] = (m, mode, size, ib)
        n = ad + size
        # (Asar's repeats - `DEX #3`, `LSR #4` - map once and make several: what follows an implied
        #  instruction is code too)
        if mode in ('imp', 'acc') and m not in ENDS and n <= 0xFFFF and (bk, n) not in insn and (bk, n) not in code:
            work.append((bk, n))
    os.makedirs(a.outdir, exist_ok=True)
    hooks = {}
    byname = {v: k for k, v in labels.items()}
    if a.hooks and os.path.exists(a.hooks):
        for ln in open(a.hooks):
            ln = ln.split('#')[0].split()
            if len(ln) < 2: continue
            if ln[0] not in byname: sys.exit('hooks: no label %s' % ln[0])
            hooks[byname[ln[0]]] = ln[1]
    h = ['/* generated by tools/recomp65816.py from port/hooks.txt - do not edit */', '#pragma once']
    h += ['int %s(void);' % fn for fn in sorted(set(hooks.values()))]
    open(os.path.join(a.outdir, 'smw_hooks.h'), 'w', newline='\n').write('\n'.join(h) + '\n')
    banks = {}
    for (bk, ad) in insn: banks.setdefault(bk, []).append(ad)
    for bk, addrs in sorted(banks.items()): gen_bank(bk, sorted(addrs), insn, labels, hooks, b, w, l, os.path.join(a.outdir, 'smw_b%02X.c' % bk))
    gen_interp(os.path.join(a.outdir, 'smw_interp.c'))
    t = ['/* generated by tools/recomp65816.py - do not edit */', '#include "snes_gen.h"']
    for bk in sorted(banks): t.append('int smw_b%02X(uint16_t pc);' % bk)
    t.append('snes_bank_fn smw_banks[16] = {')
    t.append(',\n'.join('    %s' % ('smw_b%02X' % i if i in banks else '0') for i in range(16)))
    t.append('};')
    t.append('const snes_label smw_labels[] = {')
    for (bk, ad), name in sorted(labels.items()):
        if ad >= 0x8000 and bk < 0x10: t.append('    {%d, 0x%04X, "%s"},' % (bk, ad, name))
    t.append('    {0, 0, 0}};')
    open(os.path.join(a.outdir, 'smw_table.c'), 'w', newline='\n').write('\n'.join(t) + '\n')
    # SMW's RAM names for native code: SMW_<name> (bank 0 below $2000, banks $7E-$7F)
    sy = ['/* generated by tools/recomp65816.py: SMW RAM names */', '#pragma once']
    seen = set()
    for (bk, ad), name in sorted(labels.items()):
        if not re.match(r'^[A-Za-z_][A-Za-z0-9_]*$', name) or name in seen: continue
        if (bk == 0 and ad < 0x2000) or bk in (0x7E, 0x7F):
            seen.add(name); sy.append('#define SMW_%s 0x%06X' % (name, (bk << 16 | ad) if bk else (0x7E0000 | ad)))
    open(os.path.join(a.outdir, 'smw_syms.h'), 'w', newline='\n').write('\n'.join(sy) + '\n')
    print('%d instructions in %d banks, %d labels -> %s' % (len(insn), len(banks), len(labels), a.outdir))

def gen_bank(bk, addrs, insn, labels, hooks, b, w, l, out):
    aset = set(addrs)
    o = ['/* generated by tools/recomp65816.py from the SMW disassembly - do not edit */',
         '#include "snes_gen.h"', '#include "smw_hooks.h"', '#define MYBANK 0x%02X' % bk,
         'int smw_b%02X(uint16_t pc) {' % bk, '    switch (pc) {']
    for ad in addrs: o.append('    case 0x%04X: goto L_%04X;' % (ad, ad))
    o.append('    default: return SNES_INTERP(MYBANK << 16 | pc);')
    o.append('    }')
    def goto(t, check):
        s = 'CHECK(0x%06X); ' % (bk << 16 | t) if check else ''
        if t in aset: return s + 'goto L_%04X;' % t
        return s + 'return SNES_JUMP(0x%06X);' % (bk << 16 | t)
    for ad in addrs:
        m, mode, size, ib = insn[(bk, ad)]
        n = (ad + size) & 0xFFFF
        lab = labels.get((bk, ad))
        o.append('L_%04X:%s' % (ad, '  /* %s */' % lab if lab else ''))
        if (bk, ad) in hooks: o.append('    { int h_ = %s(); if (h_) return h_; }' % hooks[(bk, ad)])
        s = 'CHECK(0x%06X); CYC(%d); ' % (bk << 16 | ad, CYC[mode] + (1 if mode in ('immm', 'immx') and ib == 2 else 0))
        if mode in ('immm', 'immx'): opnd = '0x%0*X' % (2 * ib, w(bk, ad + 1) if ib == 2 else b(bk, ad + 1))
        elif SIZE[mode] == 2: opnd = '0x%02X' % b(bk, ad + 1)
        elif SIZE[mode] == 3: opnd = '0x%04X' % w(bk, ad + 1)
        elif SIZE[mode] == 4: opnd = '0x%06X' % l(bk, ad + 1)
        else: opnd = None
        if m in BRANCH or m == 'BRL':
            if m == 'BRL': t = (n + (w(bk, ad + 1) ^ 0x8000) - 0x8000) & 0xFFFF
            else: t = (n + (b(bk, ad + 1) ^ 0x80) - 0x80) & 0xFFFF
            cond = BRANCH.get(m, '1')
            if cond == '1': s += goto(t, True)
            else: s += 'if (%s) { %s }' % (cond, goto(t, t <= ad))
        elif m == 'JMP':
            if mode == 'abs': s += goto(w(bk, ad + 1), True)
            elif mode == 'ind': s += 'return SNES_JUMP(MYBANK << 16 | RD16_0(0x%04X));' % w(bk, ad + 1)
            else: s += 'return SNES_JUMP(MYBANK << 16 | RD16(MYBANK << 16 | (uint16_t)(0x%04X + R.x)));' % w(bk, ad + 1)
        elif m == 'JML':
            if mode == 'long':
                t = l(bk, ad + 1)
                s += goto(t & 0xFFFF, True) if (t >> 16) == bk else 'return SNES_JUMP(0x%06X);' % t
            else: s += 'return SNES_JUMP(RD24_0(0x%04X));' % w(bk, ad + 1)
        elif m in ('JSR', 'JSL'):
            if m == 'JSL': s += 'OP_PHK(MYBANK); '; tgt = '0x%06X' % l(bk, ad + 1)
            elif mode == 'abs': tgt = '0x%06X' % (bk << 16 | w(bk, ad + 1))
            else: tgt = '(MYBANK << 16 | RD16(MYBANK << 16 | (uint16_t)(0x%04X + R.x)))' % w(bk, ad + 1)
            exp = bk << 16 | n
            s += 'PUSH16(0x%04X); { int r_ = snes_call%s(%s, 0x%06X); if (r_ != 0x%06X) return snes_unwind(r_); } ' % ((ad + size - 1) & 0xFFFF, '_long' if m == 'JSL' else '', tgt, exp, exp)
            s += goto(n, True)
        elif m == 'RTS': s += 'return SNES_RTS(MYBANK);'
        elif m == 'RTL': s += 'return SNES_RTL();'
        elif m == 'RTI': s += '{ OP_PLP(); uint16_t p_ = PULL16(); uint8_t k_ = R.e ? MYBANK : PULL8(); return snes_unwind(k_ << 16 | p_); }'
        elif m in ('BRK', 'COP'): s += 'return snes_brk(0x%06X, %d);' % (bk << 16 | ((ad + 2) & 0xFFFF), m == 'COP')
        elif m == 'WAI': s += '{ int r_ = snes_wai(0x%06X); if (r_) return r_; }' % (bk << 16 | n)
        elif m == 'STP': s += 'return snes_stp(0x%06X);' % (bk << 16 | ad)
        elif m == 'PHK': s += 'OP_PHK(MYBANK);'
        elif m == 'PER': s += 'OP_PER(0x%04X);' % ((n + w(bk, ad + 1)) & 0xFFFF)
        elif m in ('MVN', 'MVP'): s += 'OP_%s(0x%02X, 0x%02X);' % (m, b(bk, ad + 1), b(bk, ad + 2))
        else: s += data_op(m, mode, opnd, ib)
        o.append('    ' + s)
        ends = m in ENDS or m in ('JSR', 'JSL')
        if not ends and n not in aset: o.append('    return SNES_JUMP(0x%06X);' % (bk << 16 | n))
    o.append('}')
    open(out, 'w', newline='\n').write('\n'.join(o) + '\n')

def gen_interp(out):
    """the interpreter: one instruction at a time from pc, until control goes elsewhere"""
    o = ['/* generated by tools/recomp65816.py - do not edit: the 65816 interpreted, for code that is',
         ' * not recompiled (SMW builds a routine in RAM). The same instructions as the recompiled banks. */',
         '#include "snes_gen.h"',
         '#define OPB RD8(A24(pc + 1))', '#define OPW RD16(A24(pc + 1))',
         '#define OPL (RD16(A24(pc + 1)) | (uint32_t)RD8(A24(pc + 3)) << 16)',
         'int snes_interp(uint32_t pc) {',
         '    for (;;) {',
         '        uint32_t K = pc & 0xFF0000; uint16_t n;',
         '        if (snes_trace_on) snes_trace(pc);',
         '        CHECK(pc);',
         '        switch (RD8(pc)) {']
    for code in range(256):
        m, mode = OPS[code]
        size = SIZE.get(mode)
        c = '        case 0x%02X: CYC(%d); ' % (code, CYC[mode])
        if mode in ('immm', 'immx'):
            f = 'R.mf' if mode == 'immm' else 'R.xf'
            c += 'if (%s) { %s n = 2; } else { %s n = 3; }' % (f, data_op(m, mode, 'OPB', 1), data_op(m, mode, 'OPW', 2))
            o.append(c + ' pc = K | (uint16_t)(pc + n); break;'); continue
        opnd = {2: 'OPB', 3: 'OPW', 4: 'OPL'}.get(size)
        nx = 'K | (uint16_t)(pc + %d)' % size
        if m in BRANCH or m == 'BRL':
            off = '(int16_t)OPW' if m == 'BRL' else '(int8_t)OPB'
            c += '{ uint32_t t_ = K | (uint16_t)(pc + %d + %s); if (%s) return SNES_JUMP(t_); pc = %s; break; }' % (size, off, BRANCH.get(m, '1'), nx)
        elif m == 'JMP':
            if mode == 'abs': c += 'return SNES_JUMP(K | OPW);'
            elif mode == 'ind': c += 'return SNES_JUMP(K | RD16_0(OPW));'
            else: c += 'return SNES_JUMP(K | RD16(K | (uint16_t)(OPW + R.x)));'
        elif m == 'JML':
            c += 'return SNES_JUMP(OPL);' if mode == 'long' else 'return SNES_JUMP(RD24_0(OPW));'
        elif m in ('JSR', 'JSL'):
            if m == 'JSL': tgt = 'OPL'; c += 'OP_PHK(K >> 16); '
            elif mode == 'abs': tgt = '(K | OPW)'
            else: tgt = '(K | RD16(K | (uint16_t)(OPW + R.x)))'
            c += '{ uint32_t t_ = %s, x_ = %s; PUSH16((uint16_t)(pc + %d)); int r_ = snes_call%s(t_, x_); if (r_ != (int)x_) return snes_unwind(r_); pc = x_; break; }' % (tgt, nx, size - 1, '_long' if m == 'JSL' else '')
        elif m == 'RTS': c += 'return snes_unwind((int)(K | (uint16_t)(PULL16() + 1)));'
        elif m == 'RTL': c += 'return SNES_RTL();'
        elif m == 'RTI': c += '{ OP_PLP(); uint16_t p_ = PULL16(); uint32_t k_ = R.e ? K : (uint32_t)PULL8() << 16; return snes_unwind((int)(k_ | p_)); }'
        elif m in ('BRK', 'COP'): c += 'return snes_brk(K | (uint16_t)(pc + 2), %d);' % (m == 'COP')
        elif m == 'WAI': c += '{ int r_ = snes_wai(%s); if (r_) return r_; pc = %s; break; }' % (nx, nx)
        elif m == 'STP': c += 'return snes_stp(pc);'
        elif m == 'PHK': c += 'OP_PHK(K >> 16); pc = %s; break;' % nx
        elif m == 'PER': c += 'OP_PER((uint16_t)(pc + 3 + OPW)); pc = %s; break;' % nx
        elif m in ('MVN', 'MVP'): c += 'OP_%s(RD8(A24(pc + 1)), RD8(A24(pc + 2))); pc = %s; break;' % (m, nx)
        else: c += '%s pc = %s; break;' % (data_op(m, mode, opnd, None), nx)
        o.append(c)
    o += ['        }', '    }', '}']
    open(out, 'w', newline='\n').write('\n'.join(o) + '\n')

if __name__ == '__main__': main()
