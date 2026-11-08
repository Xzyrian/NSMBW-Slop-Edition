#!/usr/bin/env python3
"""Flag address constants in the decompiled files (runtime/gm_*.c) that the recompiled code never
uses - usually an address worked out by hand from lis / addi and gotten wrong (CHANGELOG 38).

Known addresses: every function start, every 0x8xxxxxxx literal in out/recomp_*.c, and every
lis + addi / ori pair there (the recompiler writes them as `r = 0x80330000u;` then
`r = r + -27048`). Usage: python3 tools/gm_check_consts.py [files...] (default: runtime/gm_*.c)."""
import re, glob, sys, os
os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
known = set()
lis_re = re.compile(r'ctx->r\[(\d+)\] = \(uint32_t\)\(0 \+ (0x8[0-9A-F]{7})u\);')
add_re = re.compile(r'ctx->r\[(\d+)\] = \(uint32_t\)\(ctx->r\[(\d+)\] \+ (-?\d+)\);')
for f in glob.glob('out/recomp_*.c'):
    hi = {}
    for line in open(f):
        for a in re.findall(r'0x(8[0-9A-Fa-f]{7})u?', line): known.add(int(a, 16))
        m = lis_re.search(line)
        if m: hi[m.group(1)] = int(m.group(2), 16); continue
        m = add_re.search(line)
        if m and m.group(2) in hi:
            known.add((hi[m.group(2)] + int(m.group(3))) & 0xFFFFFFFF)
            if m.group(1) != m.group(2): pass
        if re.search(r'\b(ld|st)(8|16|32|64|fs|fd)\(base|ldfs\(base|stfs\(base|ea_ = ', line):     # (loads / stores off a lis base)
            for r, off in re.findall(r'\(ctx->r\[(\d+)\] \+ (-?\d+)\)', line):
                if r in hi: known.add((hi[r] + int(off)) & 0xFFFFFFFF)
files = sys.argv[1:] or sorted(glob.glob('runtime/gm_*.c'))
bad = 0
for p in files:
    incomment = False
    for n, line in enumerate(open(p), 1):
        code = line
        if incomment:
            if '*/' not in code: continue
            code = code.split('*/', 1)[1]; incomment = False
        if '/*' in code and '*/' not in code.split('/*', 1)[1]: incomment = True
        code = re.sub(r'/\*.*?\*/', '', code).split('/*')[0]
        for a in re.findall(r'\b0x(8[0-9A-Fa-f]{7})u?\b', code):
            v = int(a, 16)
            if v >= 0x81800000 or v in known or v == 0x8042F680: continue   # (the SDA base, r13)
            print('%s:%d: 0x%08X not used by the recompiled code: %s' % (p, n, v, line.strip()[:100])); bad += 1
print('%d suspicious constant(s)' % bad)
