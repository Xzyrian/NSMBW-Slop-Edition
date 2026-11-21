#!/usr/bin/env python3
# gm_leafconv.py ADDR NAME < function text from out/*.c: a recompiled LEAF function as a native body
# in the natives' macros (R(n), GM_FRAME, GM_LOOP); its floating-point statements are kept as they are.
import sys, re
addr, name = sys.argv[1], sys.argv[2]
t = sys.stdin.read().split('\n')
out = []
frame = None
for l in t:
    s = l.strip()
    if not s or s.startswith('//') or s.startswith('/*') or s.startswith('void ') or s == '}': continue
    m = re.match(r'\{ uint32_t ea_ = ctx->r\[1\] \+ -(\d+); st32\(base, ea_, ctx->r\[1\]\); ctx->r\[1\] = ea_; \}', s)
    if m:
        frame = int(m.group(1)); out.append('    GM_FRAME(%d); gptr f = gm_frame_sp;' % frame); continue
    if frame is not None and s == 'ctx->r[1] = (uint32_t)(ctx->r[1] + %d);' % frame: continue
    if s == 'return;' : 
        out.append('    return;'); continue
    l = re.sub(r'\(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\)', r'(f + \1)', l)
    assert 'ctx->r[1]' not in l, l
    l = re.sub(r'ctx->r\[(\d+)\]', r'R(\1)', l)
    l = l.replace('PPC_POLL()', 'GM_LOOP()').replace('(uint32_t)', '')
    out.append(l)
while out and out[-1].strip() == 'return;': out.pop()
print('static void %s(GM_CTX) {' % name)
print('\n'.join(out))
print('}')
