#!/usr/bin/env python3
"""mod_class_funcs.py <class or substring>: the 8-player module's functions of a class (track B, docs/DECOMP.md) -
the recompiled name (for runtime/hle_funcs.txt), its module address and size, the game function
it replaces and its source name; [HLE] = already replaced."""
import json, re, sys, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
names = json.load(open(os.path.join(ROOT, 'linked', 'mod_source_names.json')))
info = json.load(open(os.path.join(ROOT, 'linked', 'mod.json')))
text = [x for x in info['sections'] if x['kind'] == 'text'][0]['addr']
dest2game = {d: g for g, d in json.load(open(os.path.join(ROOT, 'linked', 'mod_patches.json')))['replace']}
hle = set(l.split('#')[0].strip() for l in open(os.path.join(ROOT, 'runtime', 'hle_funcs.txt')))
for l in open(os.path.join(ROOT, 'config', 'd_project', 'symbols.txt')):
    m = re.match(r'(\S+) = \.text:0x([0-9A-Fa-f]+);.*size:0x([0-9A-Fa-f]+)', l)
    if not m: continue
    a = text + int(m.group(2), 16); g = dest2game.get(a)
    nm = names.get(f'{g:08X}', {}).get('name', '') if g is not None else ''
    if sys.argv[1] in nm or sys.argv[1] in m.group(1):
        print(f"{m.group(1):60s} mod@{a:08X} size {int(m.group(3),16):5d} game@{(g or 0):08X} {nm} {'[HLE]' if m.group(1) in hle else ''}")
