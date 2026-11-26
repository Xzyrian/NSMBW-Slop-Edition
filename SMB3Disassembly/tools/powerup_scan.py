"""every load of a player power-up value (dAcPy_c +4240 mPowerup, +5344 mNextMode; dPlayerMdl_c +0x152;
daPyMng_c::mPlayerMode[] 0x8185E95C) in the recompiled game: what each does with it"""
import re, glob, collections, os
OFFS = {'4240': 'mPowerup', '5344': 'mNextMode', '338': 'mdl mPlayerMode'}
out = []
for fn in sorted(glob.glob(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'recomp', 'out', 'recomp_*.c'))):
    L = open(fn, errors='replace').read().split('\n'); cur = '?'
    for i, l in enumerate(L):
        m = re.match(r'/\* (\S+) @ ([0-9a-fA-F]+)', l)
        if m: cur = m.group(1) + '@' + m.group(2)
        m = re.search(r'ctx->r\[(\d+)\] = ld(32|8|16)\(base, \(uint32_t\)\(ctx->r\[(\d+)\] \+ (4240|5344|338)\)\)', l)
        if not m: continue
        if m.group(4) == '338' and m.group(2) != '8': continue
        reg = m.group(1); what = OFFS[m.group(4)]
        cmps = []; tables = []; hi = {}; shifted = set([reg]); calls = 0; derived = set()
        for l2 in L[i + 1:i + 16]:
            for mm in re.finditer(r'ctx->r\[(\d+)\] = \(uint32_t\)\(0 \+ (0x8[0-9A-F]+)u\)', l2): hi[mm.group(1)] = int(mm.group(2), 16)
            for mm in re.finditer(r'ctx->r\[(\d+)\] = \(uint32_t\)\(ctx->r\[(\d+)\] \+ (-?\d+)\)', l2):
                if mm.group(2) in hi: hi[mm.group(1)] = hi[mm.group(2)] + int(mm.group(3))
            for mm in re.finditer(r'ctx->r\[(\d+)\] = \(uint32_t\)\(?(?:\(int8_t\))?\(?ctx->r\[%s\]\)?(?: \+ -?\d+)?\)?;' % reg, l2): derived.add(mm.group(1))
            mm = re.search(r'ctx->r\[(\d+)\] = rotl32\(ctx->r\[%s\], (\d+)\)' % reg, l2)
            if mm: shifted.add(mm.group(1))
            mm = re.search(r'ctx->r\[(\d+)\] = \(uint32_t\)\(\(int32_t\)ctx->r\[%s\] \* (\d+)\)' % reg, l2)
            if mm: shifted.add(mm.group(1))
            for mm in re.finditer(r'(?:ld(32|16|8)\(base, \(uint32_t\)|ea_ = \(uint32_t\))\(ctx->r\[(\d+)\] \+ ctx->r\[(\d+)\]\)', l2):
                a, b = mm.group(2), mm.group(3)
                if b in shifted and a in hi: tables.append('%s[%08X]' % (mm.group(1) or 'f', hi[a]))
                elif a in shifted and b in hi: tables.append('%s[%08X]' % (mm.group(1) or 'f', hi[b]))
                elif a in shifted or b in shifted: tables.append('%s[?]' % (mm.group(1) or 'f'))
            mm = re.search(r'cr_cmp_[su]\(ctx, (\d), \(?\w*\)?\(?ctx->r\[(\d+)\]\)?, \(?\w*\)?([-0-9xA-Fa-f]+)u?\)', l2)
            if mm and (mm.group(2) in shifted or mm.group(2) == reg or mm.group(2) in derived):
                crf = mm.group(1); k = mm.group(3).rstrip('u'); bt = '?'
                for l3 in L[L.index(l2, i) + 1:L.index(l2, i) + 6] if False else []: pass
                j = L.index(l2, i)
                for l3 in L[j + 1:j + 6]:
                    m3 = re.search(r'CR_BIT\(ctx, (\d+)\)', l3)
                    if m3: b = int(m3.group(1)) - 4 * int(crf); bt = {0: 'lt', 1: 'gt', 2: 'eq', 3: 'so'}.get(b, '?'); break
                cmps.append(('' if mm.group(2) == reg else 'd') + bt + k)
            if 'ctx->lr = 0x' in l2: calls += 1; break
            if re.search(r'^\s*ctx->r\[%s\] = ' % reg, l2) and not re.search(r'ctx->r\[%s\] = .*ctx->r\[%s\]' % (reg, reg), l2): break
        out.append((cur, fn.split('/')[-1], i + 1, what, cmps, tables, calls))
by = collections.OrderedDict()
for o in out: by.setdefault(o[0], []).append(o)
print('# power-up reads: %d sites in %d functions' % (len(out), len(by)))
for f, os_ in by.items():
    w = sorted(set(o[3] for o in os_)); c = sorted(set(x for o in os_ for x in o[4])); t = sorted(set(x for o in os_ for x in o[5]))
    kind = 'TABLE' if t else ('cmp' if c else ('call/pass' if any(o[6] for o in os_) else 'other'))
    print('%-6s %-48s %-22s %s %s %s' % (kind, f, os_[0][1] + ':' + str(os_[0][2]), '/'.join(w), ('cmp ' + ','.join(c)) if c else '', ' '.join(t)))
