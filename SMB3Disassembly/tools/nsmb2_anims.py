#!/usr/bin/env python3
"""NSMB2 Raccoon animations -> an NSMBW brres of CHR0 animations (and a C array to link in); and
NSMB2's 3D Raccoon tail (model mr_tail: mesh, skeleton, texture; its T_tail_* animations) as C
tables for smb3_stage.c to draw.

NSMB2's player skeleton is NSMBW's, bone for bone, with the same rest pose, so its skeletal
animations play on NSMBW's player models as they are. This reads them from NSMB2's
Model/Player/Anim_Common.bcres (CTR CGFX, little-endian) and writes them as NW4R CHR0 (version 5,
big-endian) with every animated channel as FVS96 keys (frame, value, slope - floats): lossless.
Rotations go from radians to degrees; channels NSMB2 leaves at rest become constants (the rest
pose of NSMBW's big Mario, MB_model, given below).

  nsmb2_anims.py <NSMB2 RomFS dir> <out.brres> [<out.c>]

Without the RomFS (it is the user's own dump, not in the repository) it writes an empty archive,
and the game goes on without these animations.
"""
import math, os, struct, sys

# ------------------------------------------------------------------ CGFX (NSMB2)
SECTIONS = ['models', 'textures', 'luts', 'materials', 'shaders', 'cameras', 'lights', 'fogs', 'envs',
            'skelanims', 'texanims', 'visanims', 'camanims', 'lightanims', 'foganims', 'emitters']

class Cgfx:
    def __init__(self, data):
        self.d = data
        assert data[:4] == b'CGFX', 'not a CGFX file'
    def u8(self, o): return self.d[o]
    def u16(self, o): return struct.unpack_from('<H', self.d, o)[0]
    def s16(self, o): return struct.unpack_from('<h', self.d, o)[0]
    def u32(self, o): return struct.unpack_from('<I', self.d, o)[0]
    def i32(self, o): return struct.unpack_from('<i', self.d, o)[0]
    def f32(self, o): return struct.unpack_from('<f', self.d, o)[0]
    def rel(self, o):
        v = self.i32(o); return o + v if v else 0
    def cstr(self, o):
        return self.d[o:self.d.index(b'\0', o)].decode('latin1')
    def dict(self, o):
        if not o: return []
        assert self.d[o:o + 4] == b'DICT'
        return [(self.cstr(self.rel(o + 0x1C + i * 16 + 8)), self.rel(o + 0x1C + i * 16 + 12)) for i in range(self.u32(o + 8))]
    def sections(self):
        data = self.u16(6)
        assert self.d[data:data + 4] == b'DATA'
        return {nm: (self.dict(self.rel(data + 12 + i * 8)) if self.u32(data + 8 + i * 8) else []) for i, nm in enumerate(SECTIONS)}

    # a keyframe curve (GfxFloatKeyFrameGroup): one or more segments of Hermite keys
    def curve(self, o):
        keys = []
        nseg = self.u32(o + 16); segs = self.rel(o + 20)
        for s in range(nseg):
            sp = segs + s * 4 if nseg > 1 else segs
            if nseg > 1: sp = self.rel(segs + s * 4)
            flags, n = self.u32(sp + 8), self.u32(sp + 12)
            q = (flags >> 5) & 7                                         # the key encoding
            k = sp + 20
            if q in (1, 2, 4, 5, 7):                                     # quantized: value scale, offset, frame scale
                vs, vo, fs = self.f32(k), self.f32(k + 4), self.f32(k + 8); k += 12
            else:
                vs, vo, fs = 1.0, 0.0, 1.0
            for i in range(n):
                if q == 0:                                               # Hermite128: frame, value, in, out (floats)
                    f, v, si, so = struct.unpack_from('<4f', self.d, k); k += 16
                elif q == 1:                                             # Hermite64: frame 12 / value 20, in, out /256
                    w = self.u32(k); f = w & 0xFFF; v = (w >> 12) * vs + vo
                    si = self.s16(k + 4) / 256.0; so = self.s16(k + 6) / 256.0; k += 8
                elif q == 3:                                             # UnifiedHermite96: frame, value, slope (floats)
                    f, v, si = struct.unpack_from('<3f', self.d, k); so = si; k += 12
                elif q == 4:                                             # UnifiedHermite48: frame /32, value, slope /256
                    f = self.u16(k) / 32.0; v = self.u16(k + 2) * vs + vo; si = so = self.s16(k + 4) / 256.0; k += 6
                elif q == 5:                                             # UnifiedHermite32: frame 8, value 12, slope 12 (/32)
                    f = self.u8(k); t1 = self.u16(k + 1); t2 = self.u8(k + 3)
                    v = (t1 & 0xFFF) * vs + vo
                    sl = (t1 >> 12) | (t2 << 4); sl = sl - 0x1000 if sl & 0x800 else sl
                    si = so = sl / 32.0; k += 4
                else:
                    raise ValueError('key encoding %d' % q)
                keys.append((f * fs, v, si, so))
        return keys

    # a skeletal animation: {bone: [9 channels]} - each None (rest), a float (constant) or keys
    def skel_anim(self, o):
        frames, loop = self.f32(o + 0x14), self.u32(o + 0x10) & 1
        bones = {}
        for name, e in self.dict(self.rel(o + 0x1C)):
            if self.u32(e + 8) != 5: continue                            # (transform tracks only)
            flags, ch = self.u32(e), []
            for c in range(10):                                          # scale XYZ, rotation XYZW (W unused), translation XYZ
                if c == 6: continue
                if flags & (1 << (16 + c)): ch.append(None)
                elif flags & (1 << (6 + c)): ch.append(self.f32(e + 0xC + c * 4))
                else:
                    p = self.rel(e + 0xC + c * 4)
                    ch.append(self.curve(p) if p else None)
            bones[name] = ch                                             # (9: scale, rotation, translation)
        return frames, loop, bones

# ------------------------------------------------------------------ NSMBW's big Mario at rest (MB_model)
# (translation, rotation in degrees) by bone, in NSMBW's order
REST = [
    ('mario_all_root', (0, 0, 0), (0, 0, 0)),
    ('skl_root', (0, 11.06, -0.85), (90, 0, 90)),
    ('leg_l1', (0.19, 0.55, 2.60), (180, 0, 180)),
    ('leg_l2', (5.17, 0, 0), (180, 0, 0)),
    ('ankle_l1', (3.61, 0, 0), (0, 0, -90)),
    ('leg_r1', (0.19, 0.55, -2.60), (-180, 0, 180)),
    ('leg_r2', (5.17, 0, 0), (180, 0, 0)),
    ('ankle_r1', (3.61, 0, 0), (0, 0, -90)),
    ('spin', (1.75, 0, 0), (0, 0, 0)),
    ('arm_l1', (5.31, -0.06, 4.07), (-180, -90, 0)),
    ('arm_l2', (3.53, 0, 0), (-180, 0, 0)),
    ('wrist_l1', (3.38, 0, 0), (0, 0, 0)),
    ('arm_r1', (5.31, -0.06, -4.07), (180, 90, 0)),
    ('arm_r2', (3.53, 0, 0), (180, 0, 0)),
    ('wrist_r1', (3.38, 0, 0), (0, 0, 0)),
    ('CapPosition', (4.13, 0, 0), (0, 0, 0)),
    ('face_1', (7.70, 0, 0), (0, 0, 90)),
]

# the Frog suit's idle (smb3_stage_frog.inc: F_wait for the game's wait): the user's pose from
# models/frog (models/tools/frog_idle_pose.py writes it: each bone's rotation in degrees, X then Y
# then Z, and translation), held - a constant CHR0 of 2 frames, looping
FROG_POSE = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'models', 'frog', 'frog_idle_pose.json')

def frog_wait():
    import json
    bones = json.load(open(FROG_POSE))['bones']
    entries = []
    for bname, rest_t, rest_r in REST:
        b = bones.get(bname)
        entries.append((bname, [float(v) for v in (b['rotate_deg'] if b else rest_r)], [float(v) for v in (b['translate'] if b else rest_t)]))
    return ('F_wait', 2.0, 1, entries)

# the animations taken (NSMB2 name -> the name it has here)
BODY = ['T_attackL', 'T_attackR', 'T_b_dash', 'T_b_dash2', 'T_fall', 'T_fly', 'T_fly2', 'T_fly_st',
        'T_fly_carry', 'T_fly2_carry', 'T_fly_st_carry', 'T_run', 'T_waitL', 'T_waitR']

# ------------------------------------------------------------------ NW4R brres / CHR0 (NSMBW)
class Strings:
    def __init__(self): self.names = []
    def add(self, s):
        if s not in self.names: self.names.append(s)

def patricia(names):
    """NW4R ResDic nodes for these names: [(ref, left, right, name index or -1)], root first."""
    def bit(s, r):
        ci, bi = r >> 3, r & 7
        return (ord(s[ci]) >> bi) & 1 if ci < len(s) else 0     # (NW4R ResDic: character ci from the start, bit bi from the low end)
    nodes = [[0xFFFF, 0, 0, None]]
    for nm in names:
        p, c = 0, nodes[0][1]
        while nodes[p][0] > nodes[c][0]:
            p, c = c, (nodes[c][2] if bit(nm, nodes[c][0]) else nodes[c][1])
        other = nodes[c][3] or ''
        r = (max(len(nm), len(other)) << 3) - 1
        while r >= 0 and bit(nm, r) == bit(other, r): r -= 1
        p, c = 0, nodes[0][1]
        while nodes[p][0] > nodes[c][0] and nodes[c][0] > r:
            p, c = c, (nodes[c][2] if bit(nm, nodes[c][0]) else nodes[c][1])
        n = len(nodes)
        nodes.append([r, c, n, nm] if not bit(nm, r) else [r, n, c, nm])
        if bit(nm, r): nodes[n][1], nodes[n][2] = c, n
        else: nodes[n][1], nodes[n][2] = n, c
        if p == 0: nodes[0][1] = n
        elif bit(nm, nodes[p][0]): nodes[p][2] = n
        else: nodes[p][1] = n
    return nodes

def group(entries, at, str_at):
    """an index group at file offset `at`: entries [(name, data file offset)]; str_at(name) -> file offset"""
    nodes = patricia([n for n, _ in entries])
    data = dict(entries)
    out = struct.pack('>II', 8 + 16 * len(nodes), len(entries))
    for ref, l, r, nm in nodes:
        no = (str_at(nm) - at) if nm else 0
        do = (data[nm] - at) if nm else 0
        out += struct.pack('>HHHHii', ref, 0, l, r, no, do)
    return out

def hermite_to_fvs(keys, deg):
    """NSMB2 keys -> FVS96 keys (frame, value, slope); separate in / out slopes become two keys"""
    k = 180.0 / math.pi if deg else 1.0
    out = []
    for f, v, si, so in keys:
        if abs(si - so) > 1e-6: out.append((f, v * k, si * k)); out.append((f, v * k, so * k))
        else: out.append((f, v * k, so * k))
    return out

def chr0(name, frames, loop, bones):
    """the CHR0 body (offsets inside it; strings are patched in later): returns (bytes, fixups)"""
    entries = []
    for bname, rest_t, rest_r in REST:
        ch = bones.get(bname)
        rot, tra = [], []
        for c in range(3):
            v = ch[3 + c] if ch else None
            rot.append(rest_r[c] if v is None else (math.degrees(v) if isinstance(v, float) else hermite_to_fvs(v, True)))
            v = ch[6 + c] if ch else None
            tra.append(rest_t[c] if v is None else (v if isinstance(v, float) else hermite_to_fvs(v, False)))
        entries.append((bname, rot, tra))
    return frames, loop, entries

def build_brres(anims):
    """anims: [(name, frames, loop, entries)] -> brres bytes"""
    strs = []
    def s(x):
        if x not in strs: strs.append(x)
    s('AnmChr(NW4R)')
    for nm, fr, lp, ents in anims:
        s(nm)
        for b, _, _ in ents: s(b)
    # layout: header 0x10, root, folder group, anim group, CHR0s, strings
    root_at = 0x10
    folder_grp_at = root_at + 8
    folder_grp_len = 8 + 16 * 2
    anim_grp_at = folder_grp_at + folder_grp_len
    anim_grp_len = 8 + 16 * (len(anims) + 1)
    root_len = 8 + folder_grp_len + anim_grp_len
    pos = (root_at + root_len + 0x1F) & ~0x1F
    blobs = []                                                    # (file offset, builder)
    for a in anims:
        blobs.append(pos)
        pos += chr0_size(a)
        pos = (pos + 0x1F) & ~0x1F
    str_at = {}
    str_pos = pos
    sb = b''
    for x in strs:
        str_at[x] = str_pos + len(sb) + 4
        e = x.encode('latin1')
        rec = struct.pack('>I', len(e)) + e + b'\0'
        rec += b'\0' * (-len(rec) % 4)
        sb += rec
    total = str_pos + len(sb)
    out = bytearray(total)
    out[0:16] = b'bres' + struct.pack('>HHIHH', 0xFEFF, 0, total, root_at, 1 + len(anims))
    out[root_at:root_at + 8] = b'root' + struct.pack('>I', root_len)
    out[folder_grp_at:folder_grp_at + folder_grp_len] = group([('AnmChr(NW4R)', anim_grp_at)], folder_grp_at, lambda n: str_at[n])
    out[anim_grp_at:anim_grp_at + anim_grp_len] = group([(a[0], o) for a, o in zip(anims, blobs)], anim_grp_at, lambda n: str_at[n])
    for a, o in zip(anims, blobs):
        b = write_chr0(a, o, str_at)
        out[o:o + len(b)] = b
    out[str_pos:] = sb
    return bytes(out)

def fvs96(keys, frames):
    """FVS96 data: count, pad, frame scale (1 / frame range), then (frame, value, slope)"""
    rng = keys[-1][0] - keys[0][0] if len(keys) > 1 else 1.0
    out = struct.pack('>HHf', len(keys), 0, 1.0 / rng if rng else 0.0)
    for f, v, sl in keys: out += struct.pack('>3f', f, v, sl)
    return out

def chr0_layout(a):
    name, frames, loop, ents = a
    hdr = 0x2C
    grp_len = 8 + 16 * (len(ents) + 1)
    pos = hdr + grp_len
    per = []
    for b, rot, tra in ents:
        n = 8 + 4 * 6                                              # name, flags, 3 rotation + 3 translation words
        per.append((pos, n)); pos += n
    curves = []
    for (eo, _), (b, rot, tra) in zip(per, ents):
        for c in rot + tra:
            if isinstance(c, list):
                curves.append((pos, c)); pos += len(fvs96(c, frames))
    return hdr, grp_len, per, curves, pos

def chr0_size(a): return chr0_layout(a)[4]

def write_chr0(a, at, str_at):
    name, frames, loop, ents = a
    hdr, grp_len, per, curves, size = chr0_layout(a)
    out = bytearray(size)
    out[0:4] = b'CHR0'
    struct.pack_into('>IIiiiiiHHII', out, 4, size, 5, -at, hdr, 0, str_at[name] - at, 0,
                     int(round(frames)), len(ents), loop, 0)
    out[hdr:hdr + grp_len] = group([(b, at + eo) for (b, _, _), (eo, _) in zip(ents, per)], at + hdr, lambda n: str_at[n])
    ci = 0
    for (eo, n), (b, rot, tra) in zip(per, ents):
        flags = 0x00000001 | 0x08 | 0x10 | 0xE000 | 0x00800000 | 0x01000000   # always, scale one / iso / const; has R, T
        words = []
        for i, c in enumerate(rot):
            if isinstance(c, list):
                words.append(('off', curves[ci][0])); ci += 1
            else:
                flags |= 1 << (16 + i); words.append(('f', c))
        rfmt = 3 if any(isinstance(c, list) for c in rot) else 0
        for i, c in enumerate(tra):
            if isinstance(c, list):
                words.append(('off', curves[ci][0])); ci += 1
            else:
                flags |= 1 << (19 + i); words.append(('f', c))
        tfmt = 3 if any(isinstance(c, list) for c in tra) else 0
        flags |= (rfmt << 27) | (tfmt << 30)
        struct.pack_into('>iI', out, eo, str_at[b] - (at + eo), flags)
        for k, (kind, v) in enumerate(words):
            if kind == 'f': struct.pack_into('>f', out, eo + 8 + 4 * k, v)
            else: struct.pack_into('>i', out, eo + 8 + 4 * k, v - eo)
    for o, keys in curves:
        b = fvs96(keys, frames); out[o:o + len(b)] = b
    return bytes(out)


# ------------------------------------------------------------------ the tail (NSMB2 mr_tail)
TAIL_ANIMS = ['T_tail_wait', 'T_tail_wait1', 'T_tail_b_dash', 'T_tail_fall', 'T_tail_flyA', 'T_tail_flyB',
              'T_tail_attackL', 'T_tail_attackR', 'T_tail_slip', 'T_tail_roll_jump', 'T_tail_firejmp']

T1 = [[2, 8, -2, -8], [5, 17, -5, -17], [9, 29, -9, -29], [13, 42, -13, -42], [18, 60, -18, -60], [24, 80, -24, -80], [33, 106, -33, -106], [47, 183, -47, -183]]
def etc1(data, w, h):
    """3DS ETC1 (8 x 8 tiles of 2 x 2 blocks, u64 little-endian) -> rows of (r, g, b), top first"""
    cl = lambda x: 0 if x < 0 else 255 if x > 255 else x
    px = [[(0, 0, 0)] * w for _ in range(h)]; o = 0
    for ty in range(0, h, 8):
        for tx in range(0, w, 8):
            for by, bx in ((0, 0), (0, 4), (4, 0), (4, 4)):
                q = struct.unpack_from('<Q', data, o)[0]; o += 8
                diff, flip = (q >> 33) & 1, (q >> 32) & 1
                if diff:
                    c5 = lambda sh: (q >> sh) & 31
                    d3 = lambda sh: ((q >> sh) & 7) - 8 if (q >> sh) & 4 else (q >> sh) & 7
                    e = lambda v: (v << 3) | (v >> 2)
                    a = (c5(59), c5(51), c5(43)); b = tuple((a[i] + d3(56 - 8 * i)) & 31 for i in range(3))
                    c1, c2 = tuple(map(e, a)), tuple(map(e, b))
                else:
                    e = lambda v: (v << 4) | v
                    c1 = (e((q >> 60) & 15), e((q >> 52) & 15), e((q >> 44) & 15)); c2 = (e((q >> 56) & 15), e((q >> 48) & 15), e((q >> 40) & 15))
                for x in range(4):
                    for y in range(4):
                        i = x * 4 + y; m = ((q >> (16 + i)) & 1) << 1 | ((q >> i) & 1)
                        sub = (y >= 2) if flip else (x >= 2)
                        tab = T1[((q >> 34) & 7) if sub else ((q >> 37) & 7)]
                        px[ty + by + y][tx + bx + x] = tuple(cl(c + tab[m]) for c in (c2 if sub else c1))
    return px

def tail_data(romfs, file='Mario.bcres', model='mr_tail'):
    mf = os.path.join(romfs, 'Model', 'Player', file); af = os.path.join(romfs, 'Model', 'Player', 'Anim_Common.bcres')
    if not (os.path.exists(mf) and os.path.exists(af)): return None
    g = Cgfx(open(mf, 'rb').read()); sec = g.sections()
    mo = dict(sec['models']).get(model)
    if mo is None: return None
    # the skeleton: a SOBJ of type 0x02000000 the model points at
    sk = None
    for k in range(0, 0x120, 4):
        t = g.rel(mo + k)
        if t and 0 < t < len(g.d) - 8 and g.d[t + 4:t + 8] == b'SOBJ' and g.u32(t) == 0x02000000: sk = t; break
    bones = []
    for name, bo in g.dict(g.rel(sk + 0x1C)):
        bones.append((name, g.i32(bo + 0xC), struct.unpack_from('<3f', g.d, bo + 0x38), struct.unpack_from('<3f', g.d, bo + 0x2C)))
    # the mesh: one shape, one sub-mesh, one interleaved buffer (position, normal, uv, colour, 2 bones, 2 weights)
    sh = g.rel(g.rel(mo + 0xC8)); sm = g.rel(g.rel(sh + 0x30)); vb = g.rel(g.rel(sh + 0x3C))
    table = [g.u32(g.rel(sm + 4) + 4 * k) for k in range(g.u32(sm))]
    raw, stride = g.rel(vb + 0x18), g.u32(vb + 0x24); nv = g.u32(vb + 0x14) // stride
    assert stride == 40
    verts = []
    for i in range(nv):
        o = raw + i * stride
        pos = struct.unpack_from('<3f', g.d, o); nrm = struct.unpack_from('<3f', g.d, o + 12); uv = struct.unpack_from('<2f', g.d, o + 24)
        bi = (table[g.d[o + 36]], table[g.d[o + 37]]); bw = (g.d[o + 38] / 100.0, g.d[o + 39] / 100.0)
        verts.append((pos, nrm, uv, bi, bw))
    fc = g.rel(g.rel(sm + 0x10)); d = g.rel(g.rel(fc + 4))
    fmt, n = g.u32(d), g.u32(d + 8); ib = g.rel(d + 12)
    idx = list(struct.unpack_from('<%dH' % (n // 2), g.d, ib)) if fmt == 0x1403 else list(g.d[ib:ib + n])
    texs = []
    for tn in ('player_tail.0', 'player_tail.1'):
        t = dict(sec['textures'])[tn]; w, h, size = g.u32(t + 0x1C), g.u32(t + 0x18), g.u32(t + 0x44)
        assert g.u32(t + 0x34) == 12 and w == 16 and h == 16          # (ETC1, 16 x 16)
        texs.append(etc1(g.d[g.rel(t + 0x48):g.rel(t + 0x48) + size], w, h))
    # the animations: per bone (in skeleton order) the 9 channels: None, constant, or keys
    a = Cgfx(open(af, 'rb').read()); sk2 = dict(a.sections()['skelanims'])
    anims = []
    for nm in TAIL_ANIMS:
        if nm not in sk2: continue
        frames, loop, tb = a.skel_anim(sk2[nm])
        anims.append((nm, frames, loop, [tb.get(b[0]) for b in bones]))
    return bones, verts, idx, texs, anims

def ff(x):
    t = '%.7g' % x
    return (t if ('.' in t or 'e' in t or 'n' in t) else t + '.0') + 'f'

def tail_c(td):
    """the tail as C tables"""
    if not td:                                                       # (none: empty tables, the 2D tail stays)
        return '\n'.join(['const int smb3_tail_ok = 0;', 'const int smb3_tail_nbones = 0, smb3_tail_nanims = 0;', 'const int smb3_tail_nverts[2], smb3_tail_nidx[2];',
            'const int8_t smb3_tail_parent[5]; const float smb3_tail_rest[5][6]; const float smb3_tail_vtx[1][8]; const uint8_t smb3_tail_vbone[1][2];',
            'const float smb3_tail_vweight[1][2]; const uint8_t smb3_tail_idx[3]; const uint8_t smb3_tail_tex[2][16][16][3];',
            'typedef struct { int16_t n; int16_t first; float c; } tail_chan_t;', 'const float smb3_tail_keys[1][3]; const tail_chan_t smb3_tail_chan[1][5][9];',
            'const float smb3_tail_frames[1]; const uint8_t smb3_tail_loop[1]; const char *const smb3_tail_anim_name[1];']) + '\n'
    var = [t for t in td if t]                                     # (Mario's raccoon tail, Luigi's fox tail: one skeleton, one set of animations)
    bones, verts, idx, texs, anims = var[0]
    nv = [len(t[1]) if t else 0 for t in td]; ni = [len(t[2]) if t else 0 for t in td]
    o = ['const int smb3_tail_ok = 1;', '#define T_NB %d' % len(bones)]
    o.append('const int smb3_tail_nbones = %d, smb3_tail_nanims = %d;' % (len(bones), len(anims)))
    o.append('const int smb3_tail_nverts[2] = {%d,%d}, smb3_tail_nidx[2] = {%d,%d};  /* Mario, Luigi (each its own vertex numbers) */' % (nv[0], nv[1], ni[0], ni[1]))
    verts = [v for t in var for v in t[1]]; idx = [i for t in var for i in t[2]]
    texs = [var[0][3][0], var[-1][3][0]]
    o.append('const int8_t smb3_tail_parent[%d] = {%s};' % (len(bones), ','.join(str(b[1]) for b in bones)))
    o.append('const float smb3_tail_rest[%d][6] = {%s};  /* translation, rotation (radians) */' % (len(bones), ','.join('{%s}' % ','.join(ff(x) for x in b[2] + b[3]) for b in bones)))
    o.append('const float smb3_tail_vtx[%d][8] = {%s};  /* position, normal, uv */' % (len(verts), ','.join('{%s}' % ','.join(ff(x) for x in v[0] + v[1] + v[2]) for v in verts)))
    o.append('const uint8_t smb3_tail_vbone[%d][2] = {%s};' % (len(verts), ','.join('{%d,%d}' % v[3] for v in verts)))
    o.append('const float smb3_tail_vweight[%d][2] = {%s};' % (len(verts), ','.join('{%s,%s}' % (ff(v[4][0]), ff(v[4][1])) for v in verts)))
    o.append('const uint8_t smb3_tail_idx[%d] = {%s};' % (len(idx), ','.join(map(str, idx))))
    o.append('const uint8_t smb3_tail_tex[2][16][16][3] = {%s};' % ','.join('{%s}' % ','.join('{%s}' % ','.join('{%d,%d,%d}' % c for c in row) for row in t) for t in texs))
    keys = []; chans = []
    for nm, frames, loop, tb in anims:
        for ch in tb:
            for c in range(9):
                v = ch[c] if ch else None
                if v is None: chans.append('{-1,0,0.0f}')
                elif isinstance(v, float): chans.append('{0,0,%s}' % ff(v))
                else:
                    ks = []
                    for f, val, si, so in v:
                        if abs(si - so) > 1e-6: ks += [(f, val, si), (f, val, so)]
                        else: ks.append((f, val, so))
                    chans.append('{%d,%d,0.0f}' % (len(ks), len(keys))); keys += ks
    o.append('typedef struct { int16_t n; int16_t first; float c; } tail_chan_t;  /* n -1: rest, 0: constant c, else keys */')
    o.append('const float smb3_tail_keys[%d][3] = {%s};  /* frame, value, slope */' % (max(1, len(keys)), ','.join('{%s,%s,%s}' % tuple(ff(x) for x in k) for k in keys) or '{0}'))
    o.append('const tail_chan_t smb3_tail_chan[%d][%d][9] = {%s};' % (len(anims), len(bones), ','.join('{%s}' % ','.join('{%s}' % ','.join(chans[(ai * len(bones) + bi) * 9:(ai * len(bones) + bi) * 9 + 9]) for bi in range(len(bones))) for ai in range(len(anims)))))
    o.append('const float smb3_tail_frames[%d] = {%s};' % (len(anims), ','.join(ff(a[1]) for a in anims)))
    o.append('const uint8_t smb3_tail_loop[%d] = {%s};' % (len(anims), ','.join(str(a[2]) for a in anims)))
    o.append('const char *const smb3_tail_anim_name[%d] = {%s};' % (len(anims), ','.join('"%s"' % a[0] for a in anims)))
    return '\n'.join(o) + '\n'


# ------------------------------------------------------------------ the ears (on the Raccoon body's head)
EAR_INNER = (236, 196, 140)                                          # (Tanooki Mario's lighter ear front, SM3DL / NSMB2)

def ears_data(romfs, file, model, cap_top):
    """the ears of NSMB2's Raccoon body (rigid on the head joint face_1, in its space): the head's
    triangles high up (local -Y is up) and out to the sides; colours from the body texture"""
    f = os.path.join(romfs, 'Model', 'Player', file)
    if not os.path.exists(f): return None
    g = Cgfx(open(f, 'rb').read()); sec = g.sections()
    mo = dict(sec['models']).get(model)
    if mo is None: return None
    sk = None
    for k in range(0, 0x120, 4):
        t = g.rel(mo + k)
        if t and 0 < t < len(g.d) - 8 and g.d[t + 4:t + 8] == b'SOBJ' and g.u32(t) == 0x02000000: sk = t; break
    bones = [n for n, _ in g.dict(g.rel(sk + 0x1C))]
    face = bones.index('face_1')
    sh = g.rel(g.rel(mo + 0xC8)); sm = g.rel(g.rel(sh + 0x30)); vb = g.rel(g.rel(sh + 0x3C))
    table = [g.u32(g.rel(sm + 4) + 4 * j) for j in range(g.u32(sm))]
    raw, stride = g.rel(vb + 0x18), g.u32(vb + 0x24); nv = g.u32(vb + 0x14) // stride
    V = []
    for i in range(nv):
        o = raw + i * stride
        V.append((struct.unpack_from('<3f', g.d, o), struct.unpack_from('<3f', g.d, o + 12), struct.unpack_from('<2f', g.d, o + 24),
                  tuple(g.d[o + 32:o + 36]), table[g.d[o + 36]] if stride == 40 else table[0]))
    fc = g.rel(g.rel(sm + 0x10)); d = g.rel(g.rel(fc + 4)); fmt, n = g.u32(d), g.u32(d + 8); ib = g.rel(d + 12)
    idx = list(struct.unpack_from('<%dH' % (n // 2), g.d, ib)) if fmt == 0x1403 else list(g.d[ib:ib + n])
    ear = lambda v: V[v][4] == face and V[v][0][1] < -8.0 and (abs(V[v][0][2]) > 3.2 or V[v][0][1] < cap_top - 0.3)   # (high, and out to the side or above the normal cap)
    tris = [idx[t:t + 3] for t in range(0, len(idx), 3) if all(ear(v) for v in idx[t:t + 3])]
    t = dict(sec['textures'])['player_body.0']; w, h, size = g.u32(t + 0x1C), g.u32(t + 0x18), g.u32(t + 0x44)
    tex = etc1(g.d[g.rel(t + 0x48):g.rel(t + 0x48) + w * h // 2], w, h)
    used = sorted({v for tr in tris for v in tr}); remap = {v: i for i, v in enumerate(used)}
    verts = []
    for v in used:
        pos, nrm, uv, vc, _ = V[v]
        tx = min(w - 1, max(0, int((uv[0] % 1.0) * w))); ty = min(h - 1, max(0, int((1.0 - (uv[1] % 1.0)) * h)))
        c = tex[ty][tx]
        if min(c) > 190: c = EAR_INNER                                  # (the inner ear: NSMB2 lights it to a light tan)
        c = tuple(int(c[i] * vc[i] / 255) for i in range(3))
        verts.append((pos, nrm, c))
    return verts, [remap[v] for tr in tris for v in tr]

def ears_c(ears):
    o = []
    have = [e for e in ears if e]
    nv = [len(e[0]) if e else 0 for e in ears]; ni = [len(e[1]) if e else 0 for e in ears]
    o.append('const int smb3_ears_nverts[2] = {%d,%d}, smb3_ears_nidx[2] = {%d,%d};  /* Mario, Luigi */' % (nv[0], nv[1], ni[0], ni[1]))
    allv = [v for e in ears if e for v in e[0]] or [((0, 0, 0), (0, 0, 1), (0, 0, 0))]
    alli = [i for e in ears if e for i in e[1]] or [0]
    o.append('const float smb3_ears_vtx[%d][6] = {%s};  /* position, normal (face_1 space) */' % (len(allv), ','.join('{%s}' % ','.join(ff(x) for x in v[0] + v[1]) for v in allv)))
    o.append('const uint8_t smb3_ears_rgb[%d][3] = {%s};' % (len(allv), ','.join('{%d,%d,%d}' % v[2] for v in allv)))
    o.append('const uint16_t smb3_ears_idx[%d] = {%s};' % (len(alli), ','.join(map(str, alli))))
    return '\n'.join(o) + '\n'

# ------------------------------------------------------------------
def main():
    romfs, out_brres = sys.argv[1], sys.argv[2]
    out_c = sys.argv[3] if len(sys.argv) > 3 else None
    src = os.path.join(romfs, 'Model', 'Player', 'Anim_Common.bcres')
    anims = []
    if os.path.exists(src):
        g = Cgfx(open(src, 'rb').read()); sk = dict(g.sections()['skelanims'])
        for nm in BODY:
            if nm not in sk: print('nsmb2_anims: no', nm); continue
            frames, loop, bones = g.skel_anim(sk[nm])
            anims.append((nm,) + chr0(nm, frames, loop, bones))
        if os.path.exists(FROG_POSE): anims.append(frog_wait())
        else: print('nsmb2_anims: no Frog idle pose at', FROG_POSE)
        data = build_brres(anims)
    else:
        print('nsmb2_anims: no NSMB2 RomFS at', romfs, '- no Raccoon animations')
        data = b''
    open(out_brres, 'wb').write(data)
    if out_c:
        with open(out_c, 'w') as f:
            f.write('/* generated by tools/nsmb2_anims.py: NSMB2 Raccoon animations as an NSMBW brres */\n')
            f.write('#include <stdint.h>\n#include <stddef.h>\n')
            f.write('const size_t smb3_raccoon_anm_size = %d;\n' % len(data))
            f.write('const int smb3_frog_wait_ok = %d;   /* (F_wait: the Frog\'s idle, in the archive) */\n' % int(any(a[0] == 'F_wait' for a in anims)))
            f.write('const uint8_t smb3_raccoon_anm[%d] __attribute__((aligned(32))) = {' % max(1, len(data)))
            for i, b in enumerate(data or b'\0'):
                if i % 24 == 0: f.write('\n')
                f.write('%d,' % b)
            f.write('\n};\n')
            td = tail_data(romfs)
            tl = tail_data(romfs, 'Luigi.bcres', 'lg_tail') if td else None
            f.write(tail_c([td, tl] if td else None))
            ears = [ears_data(romfs, 'Mario.bcres', 'mr_tail_body', -13.53), ears_data(romfs, 'Luigi.bcres', 'lg_tail_body', -15.48)]   # (cap tops: mr_normal / lg_normal's cap meshes)
            f.write(ears_c(ears))
            for nm, e in zip(('Mario', 'Luigi'), ears):
                if e: print('nsmb2_anims: %s\'s ears: %d vertices, %d triangles' % (nm, len(e[0]), len(e[1]) // 3))
            for nm, t in (('raccoon', td), ('fox (Luigi)', tl)):
                if t: print('nsmb2_anims: the %s tail: %d vertices, %d triangles, %d bones, %d animations' % (nm, len(t[1]), len(t[2]) // 3, len(t[0]), len(t[4])))
    print('nsmb2_anims: %d animations, %d bytes' % (len(anims), len(data)))

if __name__ == '__main__':
    main()
