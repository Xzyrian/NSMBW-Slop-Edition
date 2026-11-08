#!/usr/bin/env python3
"""Turn GM_CALL(...) into GM_CALLR(ra, ...) where the PowerPC return address can be read off the
recompiled code unambiguously (CHANGELOG 40: GM_CALL passes LR = 0, and a callee with a frame
saves that word on the stack, where the game may copy it later).

For each function in a runtime/gm_*.c file whose body has GM_FN(0x...) / FN(0x...) with a
literal address, the original function's calls are read from out/recomp_*.c
(`ctx->lr = 0x...u; name(ctx, base);` and `... ppc_call_indirect(...)`). A GM_CALL whose target
is a constant (a literal or a #define) gets the return address when that target is called exactly
once in the original function and once in the native - or n times in both, matched in order (part 55); a GM_CALL through a pointer
gets it when both have the same number of indirect calls (in order). Anything else is left alone and listed (-v).

Usage: python3 tools/gm_callr.py [-n] [-v] runtime/gm_x.c ...   (-n: report only)"""
import re, sys, glob, os
os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
args = [a for a in sys.argv[1:] if not a.startswith('-')]
dry, verbose = '-n' in sys.argv, '-v' in sys.argv

addr_of = {}
for a, n in re.findall(r'\{ 0x([0-9A-F]{8})u, 0x[0-9A-F]+u, "([^"]+)" \}', open('out/recomp_table.c').read()):
    addr_of[n] = int(a, 16)
calls = {}          # function address -> list of (ra, target address or None)
fn_re = re.compile(r'/\* (\S+) @ ([0-9A-F]+) size 0x[0-9a-f]+ \*/\nvoid [^\n]*\{\n(.*?)\n}\n', re.S)
for f in glob.glob('out/recomp_*.c'):
    for m in fn_re.finditer(open(f).read()):
        lst = []
        for line in m.group(3).split('\n'):
            c = re.search(r'ctx->lr = 0x([0-9A-F]+)u; (\w+)\(ctx, base\)', line)
            if c:
                name = c.group(2)
                if 'save_gpr' in name or 'restore_gpr' in name: continue
                t = None
                mm = re.search(r'_([0-9A-F]{8})$', name)
                if mm: t = int(mm.group(1), 16)
                elif name.startswith('hle_') and name[4:] in addr_of: t = addr_of[name[4:]]
                elif name in addr_of: t = addr_of[name]
                lst.append((int(c.group(1), 16), t, name))
            c = re.search(r'ctx->lr = 0x([0-9A-F]+)u; ppc_call_indirect', line)
            if c: lst.append((int(c.group(1), 16), None, '*'))
        calls[int(m.group(2), 16)] = lst

def split_calls(body):
    """GM_CALL( ... ) spans with their first argument (balanced parentheses)"""
    out = []
    for m in re.finditer(r'\bGM_CALL\(', body):
        i, depth, j = m.end(), 1, m.end()
        first = None
        while depth:
            ch = body[j]
            if ch == '(': depth += 1
            elif ch == ')': depth -= 1
            elif ch == ',' and depth == 1 and first is None: first = body[i:j].strip()
            j += 1
        out.append((m.start(), m.end(), first))
    return out

total = 0
for p in args:
    src = open(p).read()
    defs = {n: int(v, 16) for n, v in re.findall(r'#define (\w+)\s+\(?0x([0-9A-Fa-f]{8})u?\)?', src)}
    # function bodies: top-level "{ ... }" blocks after a signature
    out, pos, changed = [], 0, 0
    for m in re.finditer(r'^(?:(?:[A-Za-z_]\w*[ \t*]+)+\w+\([^;{}]*\)|E\(\w+\)|GM_HLE\(\w+\))\s*\{', src, re.M):
        if m.start() < pos: continue
        j, depth = m.end(), 1
        while depth:
            depth += {'{': 1, '}': -1}.get(src[j], 0); j += 1
        body = src[m.start():j]
        fa = re.findall(r'\b(?:GM_)?FN\(0x([0-9A-Fa-f]{8})u?\)', body)
        if len(fa) != 1 or int(fa[0], 16) not in calls:
            continue
        orig = calls[int(fa[0], 16)]
        mine = split_calls(body)
        if not mine: continue
        def tgt(first):
            if first in defs: return defs[first]
            mm = re.fullmatch(r'0x([0-9A-Fa-f]{8})u?', first)
            return int(mm.group(1), 16) if mm else None
        new, last = [], 0
        ind_o = [c for c in orig if c[1] is None]
        ind_m = [c for c in mine if tgt(c[2]) is None]
        for s, e, first in mine:
            t = tgt(first)
            ra = None
            if t is not None:
                o = [c for c in orig if c[1] == t]
                mt = [c for c in mine if tgt(c[2]) == t]
                if len(o) == len(mt): ra = o[[c[0] for c in mt].index(s)][0]   # (the same count: in order)
            elif len(ind_o) == len(ind_m): ra = ind_o[[c[0] for c in ind_m].index(s)][0]
            if ra is None:
                if verbose: print('%s: %s: left GM_CALL(%s' % (p, fa[0], first))
                continue
            new.append(body[last:s] + 'GM_CALLR(0x%08Xu, ' % ra)
            last = e
            changed += 1
        if new:
            body2 = ''.join(new) + body[last:]
            out.append(src[pos:m.start()] + body2); pos = j
    out.append(src[pos:])
    res = ''.join(out)
    if changed and '"gm_nv.h"' not in res:
        res = res.replace('#include "gm.h"\n', '#include "gm.h"\n#include "gm_nv.h"\n', 1)
    print('%s: %d call(s) given their return address' % (p, changed))
    total += changed
    if not dry and changed: open(p, 'w').write(res)
print('total', total)
