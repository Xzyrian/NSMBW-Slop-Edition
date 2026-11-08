#!/usr/bin/env python3
"""Generate runtime/gm_prologue.c: the stack prologue of each PowerPC function named in a GM_FN
(runtime/gm_*.c) in the given address ranges (frame size, saved LR, saved GPRs / FPRs / paired singles), read from the
recompiled code in out/. A decompiled function replays it with GM_FN(address) (gm.h), so the
stack ends up as the PowerPC code leaves it (the game copies stale stack words around)."""
import re, glob, sys
RANGES = [(0x80064000, 0x80066100), (0x8006C400, 0x8006D000), (0x80070B00, 0x80070D00), (0x80077400, 0x80077800), (0x80081800, 0x80081B00),
          (0x80083B00, 0x80084000), (0x80094E80, 0x800A2900), (0x800A7D00, 0x800A8300), (0x80167F00, 0x8016A600),
          (0x8015F700, 0x80163200), (0x80160F00, 0x80161800), (0x80164500, 0x80168060), (0x8016E4B0, 0x8016F200), (0x80170980, 0x80170C50), (0x8016A460, 0x8016AA70), (0x8016AB90, 0x8016AD30), (0x8016DAA0, 0x8016DE00), (0x8008C200, 0x8008CF80), (0x80163170, 0x80164500), (0x8016E230, 0x8016E4B0), (0x8015F100, 0x8015F740), (0x8015FE40, 0x8015FE50), (0x80160AD0, 0x80160F10), (0x80161060, 0x80161530), (0x80161740, 0x80161920), (0x8016DE00, 0x8016E230), (0x8016AA70, 0x8016AB90), (0x8008E300, 0x8008EB20), (0x800D9100, 0x800D9720), (0x80068040, 0x80069020), (0x8001B3A0, 0x8001CBB0), (0x80170C50, 0x80170F40), (0x80014330, 0x80015D00), (0x8010C380, 0x8010CE00), (0x800E45F0, 0x800E4FB0), (0x800E19B0, 0x800E1F80), (0x800CFBF0, 0x800D0270), (0x800C9270, 0x800C9680), (0x800F2700, 0x800F2A60), (0x80101AA0, 0x80101BC0), (0x800067A0, 0x80007610), (0x800DE940, 0x800DF840), (0x800C8950, 0x800C9270), (0x800C9680, 0x800C9A10), (0x800C9A60, 0x800C9F10), (0x800CDA70, 0x800CDE70), (0x800CE700, 0x800CE800), (0x8010C020, 0x8010C380), (0x800E8130, 0x800E8300), (0x8008F110, 0x8008F2B0), (0x80228E60, 0x80229240), (0x802BB030, 0x802BB540), (0x80237BD0, 0x80237C40), (0x8025F0C0, 0x8025F1C0), (0x8024A150, 0x8024A3A0), (0x802492E0, 0x80249360), (0x8024D0B0, 0x8024D140), (0x80260860, 0x802608D0), (0x8024D220, 0x8024D2C0), (0x8024C8D0, 0x8024C960), (0x8024D3C0, 0x8024D420), (0x8024B6B0, 0x8024B720), (0x8022BE10, 0x8022BE60), (0x802540B0, 0x80254110), (0x802542C0, 0x80254340), (0x8027B5F0, 0x8027B6B0), (0x802BE470, 0x802BE4A0), (0x802413E0, 0x80241490), (0x802ABD60, 0x802ABF50), (0x802CC9F0, 0x802CCAB0), (0x8024D2C0, 0x8024D380), (0x802BA5C0, 0x802BA630), (0x802B4960, 0x802B49E0), (0x802D2F20, 0x802D3260), (0x802C0B60, 0x802C0C20), (0x8022B380, 0x8022B3C0), (0x8026C210, 0x8026C270), (0x80277870, 0x802778D0), (0x802BE6B0, 0x802BE740), (0x802E7FBC, 0x802E8090), (0x802E84C4, 0x802E8610), (0x8024D420, 0x8024D4D0), (0x80254110, 0x802542C0), (0x802D19F0, 0x802D1AA0), (0x802585C0, 0x80258680), (0x802D17C0, 0x802D1820), (0x8023C950, 0x8023C9B0), (0x80262840, 0x802628A0), (0x80258C80, 0x80258CE0), (0x802574E0, 0x80257570), (0x8022B310, 0x8022B380), (0x80249BF0, 0x80249C60),
          # (instance 2: the 8-player module's daPyMng_c, dInfo_c, dMj2dGame_c, dSaveMng_c)
          (0x81803C00, 0x81807800), (0x8180C000, 0x8180D900), (0x81813B00, 0x81814600),
          (0x81831400, 0x81833000)]
fn_re = re.compile(r'/\* (\S+) @ ([0-9A-F]+) size 0x[0-9a-f]+ \*/\nvoid [^\n]*\{\n(.*?)\n}\n', re.S)
stwu = re.compile(r'\{ uint32_t ea_ = ctx->r\[1\] \+ -(\d+); st32\(base, ea_, ctx->r\[1\]\); ctx->r\[1\] = ea_; \}')
st32r1 = re.compile(r'st32\(base, \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\), ctx->r\[(\d+)\]\);')
st64 = re.compile(r'\{ uint32_t ea_ = \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\); st64\(base, ea_, ctx->f\[(\d+)\]\.u\); \}')
psqst = re.compile(r'\{ uint32_t ea_ = \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\); psq_st\(ctx, base, (\d+), ea_, 0, 0\); \}')
r11 = re.compile(r'ctx->r\[11\] = \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\);')
saveg = re.compile(r'__save_gpr_entry_([0-9A-F]{8})\(ctx, base\);')
assign = re.compile(r'ctx->r\[(\d+)\] = ')
# only the functions the decompiled code names in GM_FN / FN (the addresses in those lines)
USED = {0x8015F800, 0x8015F9F0}   # (gm_s_state.c: dtor_plain gets its address as a parameter)
for src in glob.glob('runtime/gm_*.c'):
    for line in open(src):
        if 'FNADDR' in line:          # (a line passing a function's address on to its GM_FN)
            for a in re.findall(r'0x(8[0-9A-Fa-f]{7})', line): USED.add(int(a, 16))
        elif 'FN(' in line and '#define' not in line:
            for a in re.findall(r'0x(8[0-9A-Fa-f]{7})', line[line.index('FN('):]): USED.add(int(a, 16))
out = []
FN = r'''
uint32_t gm_psq_last_;
uint32_t gm_prologue_(ppc_context *ctx, uint8_t *base, uint32_t addr) {
    gm_psq_last_ = 0;
    int lo = 0, hi = gm_prologue_count - 1;
    const gm_prologue_t *p = 0;
    while (lo <= hi) { int m = (lo + hi) / 2; if (gm_prologues[m].addr == addr) { p = &gm_prologues[m]; break; } if (gm_prologues[m].addr < addr) lo = m + 1; else hi = m - 1; }
    if (!p) { static int bad; if (bad++ < 8) rt_log("gm", "GM_FN: no prologue for %08X", addr); return 0; }
    if (!p->size) return 0;
    uint32_t sp = ctx->r[1], n = sp - p->size, psq = 0;
    for (int i = 0; i < p->n; i++) {
        uint32_t a = n + (uint32_t)(int32_t)p->e[2 * i], c = (uint16_t)p->e[2 * i + 1], r = c & 0xFF;
        switch (c & 0xF00) {
        case 0x400: st32(base, a, ctx->lr); break;
        case 0x100: st32(base, a, ctx->r[r]); break;
        case 0x200: st64(base, a, ctx->f[r].u); break;
        case 0x300: psq_st(ctx, base, (int)r, a, 0, 0); psq |= 1u << r; break;
        }
    }
    st32(base, n, sp);
    ctx->r[1] = n;
    gm_psq_last_ = psq;
    return p->size;
}
'''
for f in sorted(glob.glob('out/recomp_*.c')):
    for m in fn_re.finditer(open(f).read()):
        name, addr = m.group(1), int(m.group(2), 16)
        if not any(lo <= addr < hi for lo, hi in RANGES) or addr not in USED: continue
        size, ents, lr_reg, dirty, k11 = 0, [], None, set(), None
        modw = 0                                            # (the mod wrapper: if (g_mod_on) { mod } else { frame })
        for line in m.group(3).split('\n'):
            l = line.strip()
            if l.startswith('PPC_ENTER'): continue
            if not size and l == 'if (g_mod_on) {': modw = 1; continue
            if modw == 1:
                if l == '} else {': modw = 2
                continue
            if modw == 2 and l == '}': modw = 3; continue
            if l.startswith('if') or l.startswith('L_') or 'goto' in l or 'return' in l: break
            if not size:
                s = stwu.search(l)
                if s: size = int(s.group(1)); continue
                if l == 'ctx->r[0] = ctx->lr;': lr_reg = 0; continue
                break                                       # (code before the frame: leave it)
            if l == 'ctx->r[0] = ctx->lr;': lr_reg = 0; continue
            s = st32r1.search(l)
            if s:
                k, r = int(s.group(1)), int(s.group(2))
                if r == 0 and lr_reg == 0: ents.append((k, 'L', 0))
                elif r >= 13 and r not in dirty: ents.append((k, 'G', r))
                continue
            s = st64.search(l)
            if s: ents.append((int(s.group(1)), 'F', int(s.group(2)))); continue
            s = psqst.search(l)
            if s: ents.append((int(s.group(1)), 'P', int(s.group(2)))); continue
            s = r11.search(l)
            if s: k11 = int(s.group(1)); continue
            s = saveg.search(l)
            if s and k11 is not None:
                first = 14 + (int(s.group(1), 16) - 0x802DCD40) // 4
                for r in range(first, 32):
                    if r not in dirty: ents.append((k11 - 4 * (32 - r), 'G', r))
                continue
            if l.startswith('ctx->lr = '): continue
            a = assign.match(l)
            if a:
                dirty.add(int(a.group(1)))
                if int(a.group(1)) == 0: lr_reg = None      # (r0 no longer holds LR: a later store of it is data)
            if 'ppc_call' in l or re.search(r'\w+_[0-9A-F]{8}\(ctx, base\)', l) or 'hle_' in l: break
        out.append((addr, name, size, ents))
out.sort()
code = {'L': 0x400, 'G': 0x100, 'F': 0x200, 'P': 0x300}
w = ['/* gm_prologue.c - generated by tools/gm_prologues.py from the recompiled code: each PowerPC',
     ' * function\'s stack prologue (frame size, saved LR / GPRs / FPRs / paired singles), for GM_FN. */',
     '#include "gm.h"', '#include "gm_prologue.h"', '']
for addr, name, size, ents in out:
    if ents: w.append('static const int16_t e_%08X[] = { %s };' % (addr, ', '.join('%d, 0x%X' % (k, code[t] | r) for k, t, r in ents)))
w.append('const gm_prologue_t gm_prologues[] = {')
for addr, name, size, ents in out:
    w.append('    { 0x%08Xu, %d, %d, %s },   /* %s */' % (addr, size, len(ents), ('e_%08X' % addr) if ents else '0', name))
w.append('};')
w.append('const int gm_prologue_count = %d;' % len(out))
open('runtime/gm_prologue.c', 'w').write('\n'.join(w) + '\n' + FN)
print(len(out), 'functions')
