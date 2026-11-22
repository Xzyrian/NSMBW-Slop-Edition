#!/usr/bin/env python3
"""gm_conv.py ADDR CNAME [ADDR CNAME ...]: a recompiled function (out/recomp_*.c) as a native body in
the natives' macros - the transliteration step of track B done by a program instead of by hand
(the review, the name and the comment stay with the author).

  * frameless leaf, or a leaf with a frame and no saved LR: R(n), GM_FRAME, GM_LOOP (as
    gm_leafconv.py did);
  * a function with a frame and calls: GM_FN(addr) + GM_NV_KEEP + GM_LR_KEEP (the prologue's saves
    are replayed by gm_prologue.c, so those stores are left out, as are the epilogue's reloads -
    the scan is tools/gm_prologues.py's own), calls as GM_CALLV(return address, target, 0),
    R(0) = lr where the epilogue reloads LR.
  The statements themselves (the floating point above all) are kept as the recompiler wrote them.

Refuses (exit 1, the reason on stderr) what wants a hand: code before the stwu, a tail call out
of a function with a frame, a callee whose address it cannot find, r1 used other than r1 + n.
Jump tables (switch on ctr) stay as they are, with rt_fatal for a target outside the table.
convert(..., raw=True) (gm_conv.py --raw): for a function whose frame size is computed (stwux,
alloca-like buffers): the whole body as it is - the stwu, the saves and reloads, r1 - with only
the calls changed (GM_CALLV); no GM_FN, no GM_NV_KEEP, the code restores what it saves itself.
On stdout the C; on stderr one line per function: "META addr hle_name size framed(0/1)"."""
import re, sys, glob

stwu = re.compile(r'\{ uint32_t ea_ = ctx->r\[1\] \+ -(\d+); st32\(base, ea_, ctx->r\[1\]\); ctx->r\[1\] = ea_; \}')
st32r1 = re.compile(r'^st32\(base, \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\), ctx->r\[(\d+)\]\);$')
st64 = re.compile(r'^\{ uint32_t ea_ = \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\); st64\(base, ea_, ctx->f\[(\d+)\]\.u\); \}$')
psqst = re.compile(r'^\{ uint32_t ea_ = \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\); psq_st\(ctx, base, (\d+), ea_, 0, 0\); \}$')
r11 = re.compile(r'^ctx->r\[11\] = \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\);$')
saveg = re.compile(r'__save_gpr(?:_entry)?_([0-9A-F]{8})\(ctx, base\);')
restg = re.compile(r'__restore_gpr(?:_entry)?_([0-9A-F]{8})\(ctx, base\);')
assign = re.compile(r'ctx->r\[(\d+)\] = ')
call = re.compile(r'^ctx->lr = (0x[0-9A-F]{8})u; (\w+)\(ctx, base\);$')
icall = re.compile(r'^\{ ctx->lr = (0x[0-9A-F]{8})u; ppc_call_indirect\(ctx, base, ctx->ctr\); \}$')
tail = re.compile(r'^(?:if \(.*\) \{ )?(\w+)\(ctx, base\); return;(?: \})?$')

_src = None
def source():
    global _src
    if _src is None: _src = ''.join(open(f).read() for f in sorted(glob.glob('out/recomp_*.c')))
    return _src
_syms = None
def sym_addr(name):
    global _syms
    if _syms is None:
        _syms = {}
        for l in open('config/symbols.txt'):
            m = re.match(r'(\S+) = \.\w+:0x([0-9A-F]{8});', l)
            if m: _syms[m.group(1)] = int(m.group(2), 16)
        for m in re.finditer(r'^/\* (\S+) @ ([0-9A-F]{8}) size', source(), re.M):   # (the RELs' fn_<module>_<offset>
            _syms.setdefault(m.group(1), int(m.group(2), 16))                          #  names: their linked address)
    n = name[4:] if name.startswith('hle_') else name
    m = re.search(r'_?(8[0-9A-F]{7})$', n)
    if m: return int(m.group(1), 16)
    return _syms.get(n)

class Refuse(Exception): pass

def convert(addr, cname, raw=False):
    A = '%08X' % addr
    m = re.search(r'/\* (\S+) @ ' + A + r' size (0x[0-9a-f]+) \*/\nvoid [^\n]*\{\n(.*?)\n}\n', source(), re.S)
    if not m: raise Refuse('no function at ' + A)
    hname, fsize, body = m.group(1), int(m.group(2), 16), m.group(3)
    lines = [l for l in body.split('\n') if l.strip() and not l.strip().startswith('PPC_ENTER') and not l.strip().startswith('//')]
    if any('g_mod_on' in l for l in lines): raise Refuse('mod wrapper')
    # ---- the prologue (tools/gm_prologues.py's scan)
    size, ents, lr_reg, dirty, k11, drop, taken = 0, [], None, set(), None, set(), set()
    has_stwu = any(stwu.search(l) for l in lines)
    saves_lr = any(l.strip() == 'ctx->r[0] = ctx->lr;' for l in lines[:6])
    framed = has_stwu and saves_lr and not raw
    if raw and not any('ctx->r[1] = ea_;' in l for l in lines): raise Refuse('raw is for functions with a frame')
    if framed:
        for i, line in enumerate(lines):
            l = line.strip()
            if l.startswith('if') or l.startswith('L_') or 'goto' in l or 'return' in l: break
            if not size:
                s = stwu.search(l)
                if s: size = int(s.group(1)); drop.add(i); continue
                if l == 'ctx->r[0] = ctx->lr;': lr_reg = 0; continue
                raise Refuse('code before the stwu')
            if l == 'ctx->r[0] = ctx->lr;': lr_reg = 0; continue
            s = st32r1.search(l)
            if s:
                k, r = int(s.group(1)), int(s.group(2))
                if r == 0 and lr_reg == 0: ents.append((k, 'L', 0)); drop.add(i)
                elif r >= 13 and r not in dirty and ('G', r) not in taken: ents.append((k, 'G', r)); drop.add(i); taken.add(('G', r))
                continue
            s = st64.search(l)
            if s:                                           # (only f14-f31 are saved registers)
                if int(s.group(2)) >= 14 and ('F', int(s.group(2))) not in taken: ents.append((int(s.group(1)), 'F', int(s.group(2)))); drop.add(i); taken.add(('F', int(s.group(2))))
                continue
            s = psqst.search(l)
            if s:
                if int(s.group(2)) >= 14 and ('P', int(s.group(2))) not in taken: ents.append((int(s.group(1)), 'P', int(s.group(2)))); drop.add(i); taken.add(('P', int(s.group(2))))
                continue
            s = r11.search(l)
            if s: k11 = int(s.group(1)); continue
            s = saveg.search(l)
            if s and k11 is not None:
                f0 = 14 + (int(s.group(1), 16) - 0x802DCD40) // 4
                for r in range(f0, 32):
                    if r not in dirty and ('G', r) not in taken: ents.append((k11 - 4 * (32 - r), 'G', r)); taken.add(('G', r))
                drop.add(i); continue
            if l.startswith('ctx->lr = '): continue
            for a in re.finditer(r'ctx->r\[(\d+)\] = ', l):   # (every register the line writes, also inside { }: lwzu -
                dirty.add(int(a.group(1)))                  #  fn_80078EF0, a later store of the loaded r21 is data)
                if int(a.group(1)) == 0: lr_reg = None
            if 'ppc_call' in l or re.search(r'\w+_[0-9A-F]{8}\(ctx, base\)', l) or 'hle_' in l: break
        if not size: raise Refuse('no frame found')
        if not any(e[1] == 'L' for e in ents): raise Refuse('LR not saved in the prologue scan')
    G = {(k, r) for k, t, r in ents if t == 'G'}; F = {(k, r) for k, t, r in ents if t == 'F'}; P = {(k, r) for k, t, r in ents if t == 'P'}
    L = [k for k, t, r in ents if t == 'L']
    out = []
    frame_n = None
    for i, line in enumerate(lines):
        l = line.strip(); ind = line[:len(line) - len(line.lstrip())]
        if i in drop: continue
        if framed:
            if l == 'ctx->lr = ctx->r[0];': continue
            if l == 'ctx->r[1] = (uint32_t)(ctx->r[1] + %d);' % size: continue
            if restg.search(l): continue
            s = re.match(r'^ctx->r\[(\d+)\] = ld32\(base, \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\)\);$', l)
            if s:
                r, k = int(s.group(1)), int(s.group(2))
                if r == 0 and k in L: out.append(ind + 'R(0) = lr;'); continue
                if (k, r) in G: continue
            s = re.match(r'^\{ uint32_t ea_ = \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\); ctx->f\[(\d+)\]\.u = ld64\(base, ea_\); \}$', l)
            if s and (int(s.group(1)), int(s.group(2))) in F: continue
            s = re.match(r'^\{ uint32_t ea_ = \(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\); psq_l\(ctx, base, (\d+), ea_, 0, 0\); \}$', l)
            if s and (int(s.group(1)), int(s.group(2))) in P: continue
        elif raw:
            if tail.match(l) or re.match(r'^(if \(.*\) )?\{ ppc_call_indirect\(ctx, base, ctx->ctr\); return; \}$', l):
                raise Refuse('tail call out of a frame')
        else:
            s = stwu.search(l)
            if s:
                if frame_n is not None: raise Refuse('two stwu')
                frame_n = int(s.group(1)); out.append(ind + 'GM_FRAME(%d); gptr f = gm_frame_sp;' % frame_n); continue
            if frame_n is not None and l == 'ctx->r[1] = (uint32_t)(ctx->r[1] + %d);' % frame_n: continue
        s = call.match(l)
        if s:
            t = sym_addr(s.group(2))
            if t is None: raise Refuse('callee ' + s.group(2))
            out.append(ind + 'GM_CALLV(%su, 0x%08Xu, 0);' % (s.group(1), t)); continue
        s = icall.match(l)
        if s: out.append(ind + 'GM_CALLV(%su, ctx->ctr, 0);' % s.group(1)); continue
        s = re.match(r'^(if \(.*\) )?\{ ppc_call_indirect\(ctx, base, ctx->ctr\); return; \}$', l)
        if s:
            if framed or frame_n is not None: raise Refuse('tail call out of a frame')
            out.append(ind + (s.group(1) or '') + '{ GM_TAIL(ctx->ctr, 0); return; }'); continue
        s = re.match(r'^\{ switch \(ctx->ctr\) \{ (case 0x[0-9A-F]{8}u: goto L_[0-9A-F]{8}; )+default: ppc_call_indirect\(ctx, base, ctx->ctr\); return; \} \}$', l)
        if s:                                           # a jump table (bctr): the cases stay gotos; a target
            out.append(ind + l.replace('default: ppc_call_indirect(ctx, base, ctx->ctr); return;',   # outside the table cannot happen
                'default: rt_fatal("%s: jump table target %%08X", ctx->ctr); return;' % A)); continue
        if 'ppc_call_indirect' in l: raise Refuse('an indirect call I do not know: ' + l)
        s = tail.match(l)
        if s and s.group(1) not in ('if',):
            if framed or frame_n is not None: raise Refuse('tail call out of a frame')
            t = sym_addr(s.group(1))
            if t is None: raise Refuse('callee ' + s.group(1))
            l2 = l.replace(s.group(1) + '(ctx, base);', 'GM_TAIL(0x%08Xu, 0);' % t)
            out.append(ind + l2); continue
        if '(ctx, base)' in l and 'psq_' not in l and 'cr_' not in l: raise Refuse('a call I do not know: ' + l)
        out.append(line)
    txt = '\n'.join(out)
    if not raw:
        txt = re.sub(r'\(uint32_t\)\(ctx->r\[1\] \+ (-?\d+)\)', r'(f + \1)', txt)
        if 'ctx->r[1]' in txt: raise Refuse('r1 used other than r1 + n')
    txt = re.sub(r'ctx->r\[(\d+)\]', r'R(\1)', txt).replace('PPC_POLL()', 'GM_LOOP()').replace('(uint32_t)', '')
    tl = txt.split('\n')
    while tl and tl[-1].strip() == 'return;': tl.pop()
    txt = '\n'.join(tl)
    if raw:                                             # the frame is the code's own (its size is computed):
        head = '    /* (the stack frame as the PowerPC code makes it: its size is computed at run time) */\n'
    elif framed:
        head = '    GM_FN(0x%s); GM_NV_KEEP; GM_LR_KEEP;\n    uint32_t lr = ctx->lr; gptr f = gm_frame_sp; (void)lr; (void)f;\n' % A
    elif frame_n is None and '(f + ' in txt:
        head = "    gptr f = R(1);                                                           /* (the caller's frame: stack arguments) */\n"
    else: head = ''
    return hname, fsize, framed, 'static void %s(GM_CTX) {\n%s%s\n}\n' % (cname, head, txt)

if __name__ == '__main__':
    a = sys.argv[1:]; raw = '--raw' in a; a = [x for x in a if x != '--raw']
    for i in range(0, len(a), 2):
        try:
            hname, fsize, framed, txt = convert(int(a[i], 16), a[i + 1], raw)
        except Refuse as e:
            sys.stderr.write('REFUSED %s: %s\n' % (a[i], e)); sys.exit(1)
        sys.stdout.write(txt)
        sys.stderr.write('META %s %s %d %d\n' % (a[i], hname, fsize, int(framed)))
