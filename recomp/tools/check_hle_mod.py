#!/usr/bin/env python3
"""List hle'd functions (runtime/hle_funcs.txt) whose recompiled body hands over to the 8-player
module (`if (g_mod_on) { mod_...(ctx, base); return; }` at the start): an hle version replaces
both, so it must do the module's work itself when g_mod_on (or call the module's function).
Run from recomp/ after tools/gen.sh."""
import re, glob
names = set(l.strip() for l in open('runtime/hle_funcs.txt') if l.strip() and not l.startswith('#'))
for f in sorted(glob.glob('out/recomp_*.c')):
    for m in re.finditer(r'/\* (\S+) @ ([0-9A-F]+) size 0x[0-9a-f]+ \*/\nvoid [^\n]*\n(.{0,400})', open(f).read(), re.S):
        if m.group(1) in names:
            h = re.search(r'if \(g_mod_on\) \{\n\s*(mod_\w+)\(ctx, base\); return;', m.group(3))
            if h: print('%s %s -> %s' % (m.group(2), m.group(1), h.group(1)))
