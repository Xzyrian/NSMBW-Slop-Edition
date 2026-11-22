#!/usr/bin/env python3
"""recomp6502.py - static recompiler: SMB3 (6502, MMC3) -> C.

Input: the ROM assembled from the disassembly and its NESASM listing (tools/build_smb3.py makes
both). The listing says exactly which bytes are instructions (no guessing code from data); the
instruction bytes themselves are decoded from the ROM.

Output (out/): one C file per PRG bank that holds code, smb3_bNN.c, each a single function
`int smb3_bNN(uint16_t pc)` that starts at pc (a switch over every instruction address in the
bank) and runs until control leaves it. Results (port/nes.h): 0 never; NES_RET(pc) an RTS/RTI to an
address some caller is waiting for; NES_JUMP(pc) continue at pc wherever it is mapped now.

Model (port/nes_cpu.c):
  - the 6502 stack in RAM ($0100) is the truth: JSR pushes, RTS pops, as on the NES. JSR is also a C
    call (nes_call) that expects to come back to the next instruction; if the popped address is
    another one (DynJump pulls its return address to read a table, PLA PLA leaves two levels...),
    the result unwinds to the frame that expects it, or continues as a jump.
  - every instruction adds its cycles; at backward branches, jumps and after calls the code checks
    for an event (scanline, MMC3 IRQ, vblank: NMI, end of frame) - interrupts are taken there.
  - a code window ($A000/$C000) whose bank changed under the running code (an NMI or a callee
    swapped it) is left: the code continues at the same address in the new bank, as on the NES.
"""
import re, sys, os, argparse

# ---- 6502 opcodes (official): opcode -> (mnemonic, mode, cycles)
OPS = {}
def op(m, mode, pairs):
    for code, cyc in pairs: OPS[code] = (m, mode, cyc)
for m, lst in {
    'ADC': [('imm',0x69,2),('zp',0x65,3),('zpx',0x75,4),('abs',0x6D,4),('absx',0x7D,4),('absy',0x79,4),('indx',0x61,6),('indy',0x71,5)],
    'AND': [('imm',0x29,2),('zp',0x25,3),('zpx',0x35,4),('abs',0x2D,4),('absx',0x3D,4),('absy',0x39,4),('indx',0x21,6),('indy',0x31,5)],
    'ASL': [('acc',0x0A,2),('zp',0x06,5),('zpx',0x16,6),('abs',0x0E,6),('absx',0x1E,7)],
    'BIT': [('zp',0x24,3),('abs',0x2C,4)],
    'CMP': [('imm',0xC9,2),('zp',0xC5,3),('zpx',0xD5,4),('abs',0xCD,4),('absx',0xDD,4),('absy',0xD9,4),('indx',0xC1,6),('indy',0xD1,5)],
    'CPX': [('imm',0xE0,2),('zp',0xE4,3),('abs',0xEC,4)],
    'CPY': [('imm',0xC0,2),('zp',0xC4,3),('abs',0xCC,4)],
    'DEC': [('zp',0xC6,5),('zpx',0xD6,6),('abs',0xCE,6),('absx',0xDE,7)],
    'EOR': [('imm',0x49,2),('zp',0x45,3),('zpx',0x55,4),('abs',0x4D,4),('absx',0x5D,4),('absy',0x59,4),('indx',0x41,6),('indy',0x51,5)],
    'INC': [('zp',0xE6,5),('zpx',0xF6,6),('abs',0xEE,6),('absx',0xFE,7)],
    'JMP': [('abs',0x4C,3),('ind',0x6C,5)],
    'JSR': [('abs',0x20,6)],
    'LDA': [('imm',0xA9,2),('zp',0xA5,3),('zpx',0xB5,4),('abs',0xAD,4),('absx',0xBD,4),('absy',0xB9,4),('indx',0xA1,6),('indy',0xB1,5)],
    'LDX': [('imm',0xA2,2),('zp',0xA6,3),('zpy',0xB6,4),('abs',0xAE,4),('absy',0xBE,4)],
    'LDY': [('imm',0xA0,2),('zp',0xA4,3),('zpx',0xB4,4),('abs',0xAC,4),('absx',0xBC,4)],
    'LSR': [('acc',0x4A,2),('zp',0x46,5),('zpx',0x56,6),('abs',0x4E,6),('absx',0x5E,7)],
    'ORA': [('imm',0x09,2),('zp',0x05,3),('zpx',0x15,4),('abs',0x0D,4),('absx',0x1D,4),('absy',0x19,4),('indx',0x01,6),('indy',0x11,5)],
    'ROL': [('acc',0x2A,2),('zp',0x26,5),('zpx',0x36,6),('abs',0x2E,6),('absx',0x3E,7)],
    'ROR': [('acc',0x6A,2),('zp',0x66,5),('zpx',0x76,6),('abs',0x6E,6),('absx',0x7E,7)],
    'SBC': [('imm',0xE9,2),('zp',0xE5,3),('zpx',0xF5,4),('abs',0xED,4),('absx',0xFD,4),('absy',0xF9,4),('indx',0xE1,6),('indy',0xF1,5)],
    'STA': [('zp',0x85,3),('zpx',0x95,4),('abs',0x8D,4),('absx',0x9D,5),('absy',0x99,5),('indx',0x81,6),('indy',0x91,6)],
    'STX': [('zp',0x86,3),('zpy',0x96,4),('abs',0x8E,4)],
    'STY': [('zp',0x84,3),('zpx',0x94,4),('abs',0x8C,4)],
}.items():
    op(m, None, [])
    for mode, code, cyc in lst: OPS[code] = (m, mode, cyc)
for m, code, cyc in [('BPL',0x10,2),('BMI',0x30,2),('BVC',0x50,2),('BVS',0x70,2),('BCC',0x90,2),('BCS',0xB0,2),('BNE',0xD0,2),('BEQ',0xF0,2)]:
    OPS[code] = (m, 'rel', cyc + 1)
for m, code, cyc in [('BRK',0x00,7),('CLC',0x18,2),('CLD',0xD8,2),('CLI',0x58,2),('CLV',0xB8,2),('DEX',0xCA,2),('DEY',0x88,2),
                     ('INX',0xE8,2),('INY',0xC8,2),('NOP',0xEA,2),('PHA',0x48,3),('PHP',0x08,3),('PLA',0x68,4),('PLP',0x28,4),
                     ('RTI',0x40,6),('RTS',0x60,6),('SEC',0x38,2),('SED',0xF8,2),('SEI',0x78,2),('TAX',0xAA,2),('TAY',0xA8,2),
                     ('TSX',0xBA,2),('TXA',0x8A,2),('TXS',0x9A,2),('TYA',0x98,2)]:
    OPS[code] = (m, 'imp', cyc)
SIZE = {'imp':1,'acc':1,'imm':2,'zp':2,'zpx':2,'zpy':2,'rel':2,'indx':2,'indy':2,'abs':3,'absx':3,'absy':3,'ind':3}
MNEMS = {v[0] for v in OPS.values()}

# ---- the listing: "  1234  1F:FE99  0A        ASL A" (macro expansions: no line number)
LINE = re.compile(r'^\s*\d*\s+([0-9A-F]{2}):([0-9A-F]{4})\s\s((?:[0-9A-F]{2} ){1,3})\s*(.*)$')
LABEL = re.compile(r'^\s*\d*\s+([0-9A-F]{2}):([0-9A-F]{4})\s+([A-Za-z_][A-Za-z0-9_]*):')
def read_listing(path):
    insns, labels = {}, {}                      # (bank, addr) -> True ; (bank, addr) -> name
    for l in open(path, encoding='latin1'):
        m = LINE.match(l)
        if m:
            bank, addr, text = int(m.group(1), 16), int(m.group(2), 16), m.group(4)
            t = re.sub(r'^[A-Za-z_][A-Za-z0-9_]*:\s*', '', text).strip()
            word = t.split()[0].upper() if t else ''
            if word in MNEMS: insns[(bank, addr)] = True
        m = LABEL.match(l)
        if m:
            bank, addr = int(m.group(1), 16), int(m.group(2), 16)
            if bank < 32 and addr >= 0x8000: labels.setdefault((bank, addr), m.group(3))
    return insns, labels

def window_of(addr): return (addr >> 13) & 3          # 0 $8000, 1 $A000, 2 $C000, 3 $E000

def gen_bank(bank, base, rom, addrs, labels, out, hooks={}):
    """C for one bank; addrs: its instruction addresses (sorted)"""
    aset = set(addrs)
    swappable = window_of(base) in (1, 2)
    def b(a): return rom[bank * 0x2000 + (a - base)]
    def w(a): return b(a) | b(a + 1) << 8
    o = []
    o.append('/* generated by tools/recomp6502.py from the SMB3 disassembly - do not edit */')
    o.append('#include "nes_gen.h"')
    o.append('#include "smb3_hooks.h"')
    o.append('#define MYBANK %d' % bank)
    o.append('#define MYWIN %d' % window_of(base))
    o.append('#define BANKCHK %d' % (1 if swappable else 0))
    o.append('int smb3_b%02d(uint16_t pc) {' % bank)
    o.append('    switch (pc) {')
    for a in addrs: o.append('    case 0x%04X: goto L_%04X;' % (a, a))
    o.append('    default: return nes_bad_pc(pc, MYBANK);')
    o.append('    }')
    def rd(mode, a):                                  # C expression: the operand's value
        if mode == 'imm': return '0x%02X' % b(a + 1)
        if mode == 'zp': return 'ZP(0x%02X)' % b(a + 1)
        if mode == 'zpx': return 'ZP((uint8_t)(0x%02X + R.x))' % b(a + 1)
        if mode == 'zpy': return 'ZP((uint8_t)(0x%02X + R.y))' % b(a + 1)
        if mode == 'abs': return 'RD(0x%04X)' % w(a + 1)
        if mode == 'absx': return 'RD((uint16_t)(0x%04X + R.x))' % w(a + 1)
        if mode == 'absy': return 'RD((uint16_t)(0x%04X + R.y))' % w(a + 1)
        if mode == 'indx': return 'RD(ZP16((uint8_t)(0x%02X + R.x)))' % b(a + 1)
        if mode == 'indy': return 'RD((uint16_t)(ZP16(0x%02X) + R.y))' % b(a + 1)
        raise ValueError(mode)
    def ea(mode, a):                                  # C expression: the operand's address
        if mode == 'zp': return '0x%02X' % b(a + 1)
        if mode == 'zpx': return '(uint8_t)(0x%02X + R.x)' % b(a + 1)
        if mode == 'zpy': return '(uint8_t)(0x%02X + R.y)' % b(a + 1)
        if mode == 'abs': return '0x%04X' % w(a + 1)
        if mode == 'absx': return '(uint16_t)(0x%04X + R.x)' % w(a + 1)
        if mode == 'absy': return '(uint16_t)(0x%04X + R.y)' % w(a + 1)
        if mode == 'indx': return 'ZP16((uint8_t)(0x%02X + R.x))' % b(a + 1)
        if mode == 'indy': return '(uint16_t)(ZP16(0x%02X) + R.y)' % b(a + 1)
        raise ValueError(mode)
    def goto(t, check):                               # continue at t
        s = ''
        if check: s += 'CHECK(0x%04X); ' % t
        if t in aset and window_of(t) == window_of(base): return s + 'goto L_%04X;' % t
        return s + 'return NES_JUMP(0x%04X);' % t
    for a in addrs:
        code = b(a)
        if code not in OPS: sys.exit('bank %d $%04X: unknown opcode %02X' % (bank, a, code))
        m, mode, cyc = OPS[code]
        n = a + SIZE[mode]
        lab = labels.get((bank, a))
        o.append('L_%04X:%s' % (a, '  /* %s */' % lab if lab else ''))
        if (bank, a) in hooks:                        # native code first (port/hooks.txt): 0 = go on with the original
            o.append('    { int h_ = %s(); if (h_) return h_; }' % hooks[(bank, a)])
        s = 'CYC(%d); ' % cyc
        if m in ('LDA', 'LDX', 'LDY'):
            r = m[2].lower(); s += 'R.%s = %s; NZ(R.%s);' % (r, rd(mode, a), r)
        elif m in ('STA', 'STX', 'STY'):
            r = m[2].lower()
            s += ('ZPW(%s, R.%s);' if mode in ('zp', 'zpx', 'zpy') else 'WR(%s, R.%s);') % (ea(mode, a), r)
            if mode == 'abs' and 0x8000 <= w(a + 1) < 0xA000 and swappable:    # an MMC3 write may swap our own bank
                s += ' if (BANKCHK && nes_map[MYWIN] != MYBANK) return NES_JUMP(0x%04X);' % n
        elif m in ('ADC', 'SBC'):
            s += '%s(%s);' % (m, rd(mode, a))
        elif m in ('AND', 'ORA', 'EOR'):
            s += 'R.a %s= %s; NZ(R.a);' % ({'AND': '&', 'ORA': '|', 'EOR': '^'}[m], rd(mode, a))
        elif m in ('CMP', 'CPX', 'CPY'):
            s += 'CMPR(R.%s, %s);' % ({'CMP': 'a', 'CPX': 'x', 'CPY': 'y'}[m], rd(mode, a))
        elif m == 'BIT':
            s += 'BIT(%s);' % rd(mode, a)
        elif m in ('ASL', 'LSR', 'ROL', 'ROR', 'INC', 'DEC'):
            if mode == 'acc': s += 'R.a = %s(R.a);' % m
            elif mode in ('zp', 'zpx'): s += '{ uint8_t e_ = %s; ZPW(e_, %s(ZP(e_))); }' % (ea(mode, a), m)
            else: s += '{ uint16_t e_ = %s; uint8_t v_ = RD(e_); WR(e_, %s(v_)); }' % (ea(mode, a), m)
        elif m in ('INX', 'INY', 'DEX', 'DEY'):
            r = m[2].lower(); s += 'R.%s%s; NZ(R.%s);' % (r, '++' if m[0] == 'I' else '--', r)
        elif m in ('TAX', 'TAY', 'TXA', 'TYA', 'TSX'):
            src, dst = {'TAX': ('a', 'x'), 'TAY': ('a', 'y'), 'TXA': ('x', 'a'), 'TYA': ('y', 'a'), 'TSX': ('s', 'x')}[m]
            s += 'R.%s = R.%s; NZ(R.%s);' % (dst, src, dst)
        elif m == 'TXS': s += 'R.s = R.x;'
        elif m == 'PHA': s += 'PUSH(R.a);'
        elif m == 'PHP': s += 'PUSH(GETP() | 0x30);'
        elif m == 'PLA': s += 'R.a = PULL(); NZ(R.a);'
        elif m == 'PLP': s += 'SETP(PULL());'
        elif m in ('CLC', 'SEC'): s += 'R.c = %d;' % (m == 'SEC')
        elif m in ('CLI', 'SEI'): s += 'R.i = %d;' % (m == 'SEI')
        elif m in ('CLD', 'SED'): s += 'R.d = %d;' % (m == 'SED')
        elif m == 'CLV': s += 'R.v = 0;'
        elif m == 'NOP': pass
        elif mode == 'rel':
            t = (n + (b(a + 1) ^ 0x80) - 0x80) & 0xFFFF
            cond = {'BPL': '!R.n', 'BMI': 'R.n', 'BVC': '!R.v', 'BVS': 'R.v', 'BCC': '!R.c', 'BCS': 'R.c', 'BNE': '!R.z', 'BEQ': 'R.z'}[m]
            s += 'if (%s) { %s }' % (cond, goto(t, t <= a))
        elif m == 'JMP':
            if mode == 'abs': s += goto(w(a + 1), True)
            else:
                p = w(a + 1)                          # (the 6502's page wrap of the pointer's high byte)
                s += 'CHECK(0x%04X); return NES_JUMP(RD(0x%04X) | RD(0x%04X) << 8);' % (a, p, (p & 0xFF00) | ((p + 1) & 0xFF))
        elif m == 'JSR':
            s += 'PUSH16(0x%04X); { int r_ = nes_call(0x%04X, 0x%04X); if (r_ != 0x%04X) return nes_unwind(r_); } CHECK(0x%04X); ' % (n - 1, w(a + 1), n, n, n)
            if swappable: s += 'if (BANKCHK && nes_map[MYWIN] != MYBANK) return NES_JUMP(0x%04X); ' % n
            s += goto(n, False)
        elif m == 'RTS': s += 'return nes_unwind((uint16_t)(PULL16() + 1));'
        elif m == 'RTI': s += '{ SETP(PULL()); return nes_unwind(PULL16()); }'
        elif m == 'BRK': s += 'return nes_brk(0x%04X);' % ((a + 2) & 0xFFFF)
        else: sys.exit('unhandled %s' % m)
        o.append('    ' + s)
        # falling through to the next address
        ends = m in ('JMP', 'RTS', 'RTI', 'BRK', 'JSR')
        if not ends and n not in aset: o.append('    return NES_JUMP(0x%04X);' % (n & 0xFFFF))
    o.append('}')
    open(out, 'w', newline='\n').write('\n'.join(o) + '\n')

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('rom'); ap.add_argument('listing'); ap.add_argument('outdir')
    ap.add_argument('--hooks'); ap.add_argument('--symbols')
    a = ap.parse_args()
    data = open(a.rom, 'rb').read()
    prg = data[16:16 + 32 * 0x2000]
    insns, labels = read_listing(a.listing)
    os.makedirs(a.outdir, exist_ok=True)
    # hooks: "<label> <native function>" per line (port/hooks.txt)
    hooks = {}
    byname = {}
    for k, v in labels.items(): byname.setdefault(v, []).append(k)
    if a.hooks and os.path.exists(a.hooks):
        for l in open(a.hooks):
            l = l.split('#')[0].split()
            if len(l) < 2: continue
            if l[0] not in byname: sys.exit('hooks: no label %s' % l[0])
            for k in byname[l[0]]: hooks[k] = l[1]
    h = ['/* generated by tools/recomp6502.py from port/hooks.txt - do not edit */', '#pragma once']
    h += ['int %s(void);' % fn for fn in sorted(set(hooks.values()))]
    open(os.path.join(a.outdir, 'smb3_hooks.h'), 'w', newline='\n').write('\n'.join(h) + '\n')
    # SMB3's RAM names (and constants) for native code: SMB3_<name>
    if a.symbols and os.path.exists(a.symbols):
        sy = ['/* generated by tools/recomp6502.py: SMB3 symbols below $8000 (RAM, registers, constants) */', '#pragma once']
        for l in open(a.symbols, encoding='latin1'):
            m = re.match(r'^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*\$([0-9A-F]+)', l)
            if m and int(m.group(2), 16) < 0x8000: sy.append('#define SMB3_%s 0x%s' % (m.group(1), m.group(2)))
        open(os.path.join(a.outdir, 'smb3_syms.h'), 'w', newline='\n').write('\n'.join(sy) + '\n')
    banks = {}
    for (bank, addr) in insns: banks.setdefault(bank, []).append(addr)
    bases = {}
    for bank, addrs in sorted(banks.items()):
        lo = min(addrs) & 0xE000
        if any((x & 0xE000) != lo for x in addrs): sys.exit('bank %d spans windows' % bank)
        bases[bank] = lo
        gen_bank(bank, lo, prg, sorted(addrs), labels, os.path.join(a.outdir, 'smb3_b%02d.c' % bank), hooks)
    t = ['/* generated by tools/recomp6502.py - do not edit */', '#include "nes_gen.h"']
    for bank in sorted(banks): t.append('int smb3_b%02d(uint16_t pc);' % bank)
    t.append('nes_bank_fn smb3_banks[32] = {')
    t.append(',\n'.join('    %s' % ('smb3_b%02d' % i if i in banks else '0') for i in range(32)))
    t.append('};')
    t.append('const uint16_t smb3_bank_base[32] = {%s};' % ', '.join('0x%04X' % bases.get(i, 0) for i in range(32)))
    # names of the labels, for logs
    t.append('const nes_label smb3_labels[] = {')
    for (bank, addr), name in sorted(labels.items()): t.append('    {%d, 0x%04X, "%s"},' % (bank, addr, name))
    t.append('    {0, 0, 0}};')
    open(os.path.join(a.outdir, 'smb3_table.c'), 'w', newline='\n').write('\n'.join(t) + '\n')
    print('%d instructions in %d banks, %d labels -> %s' % (len(insns), len(banks), len(labels), a.outdir))

if __name__ == '__main__': main()
