"""Minimal NW4R BRRES reader: MDL0 (v8-v11) geometry/skeleton/materials and TEX0 images.
Written for exporting NSMBW player models; read-only."""
import struct
import numpy as np


def u8(d, o): return d[o]
def u16(d, o): return struct.unpack_from('>H', d, o)[0]
def s16(d, o): return struct.unpack_from('>h', d, o)[0]
def u32(d, o): return struct.unpack_from('>I', d, o)[0]
def s32(d, o): return struct.unpack_from('>i', d, o)[0]
def cstr(d, o): return d[o:d.index(b'\0', o)].decode('latin1')


def group(d, off):
    """NW4R resource group (patricia tree): [(name, data_offset_abs)]"""
    cnt = u32(d, off + 4)
    out = []
    for i in range(1, cnt + 1):
        e = off + 8 + i * 16
        no, do = s32(d, e + 8), s32(d, e + 12)                                # (signed, as NW4R's: entries added later point back)
        out.append((cstr(d, off + no), off + do))
    return out


def u8_find(d, suffix):
    """first file in a U8 archive whose name ends with suffix -> its bytes"""
    root = u32(d, 4); n = u32(d, root + 8); st = root + n * 12
    for i in range(1, n):
        e = root + i * 12
        if d[e] == 0 and cstr(d, st + (u32(d, e) & 0xFFFFFF)).endswith(suffix):
            return d[u32(d, e + 4):u32(d, e + 4) + u32(d, e + 8)]
    raise ValueError('no %s in the archive' % suffix)


class Brres:
    def __init__(self, path):
        self.d = d = open(path, 'rb').read()
        if d[:4] == b'\x55\xaa\x38\x2d':                      # a U8 .arc: its first .brres (g3d/model.brres)
            self.d = d = u8_find(d, '.brres')
        assert d[:4] == b'bres'
        root = u16(d, 0xC)
        self.folders = {name: dict(group(d, fo)) for name, fo in group(d, root + 8)}

    def models(self):
        return {n: Mdl0(self.d, o, n) for n, o in self.folders.get('3DModels(NW4R)', {}).items()}

    def textures(self):
        return {n: Tex0(self.d, o, n) for n, o in self.folders.get('Textures(NW4R)', {}).items()}


# ---------------------------------------------------------------- textures
def _rgb565(v):
    r = (v >> 11) & 31; g = (v >> 5) & 63; b = v & 31
    return (r << 3 | r >> 2, g << 2 | g >> 4, b << 3 | b >> 2, 255)


def _rgb5a3(v):
    if v & 0x8000:
        r = (v >> 10) & 31; g = (v >> 5) & 31; b = v & 31
        return (r << 3 | r >> 2, g << 3 | g >> 2, b << 3 | b >> 2, 255)
    a = (v >> 12) & 7; r = (v >> 8) & 15; g = (v >> 4) & 15; b = v & 15
    return (r * 17, g * 17, b * 17, a << 5 | a << 2 | a >> 1)


class Tex0:
    BLOCK = {0: (8, 8, 4), 1: (8, 4, 8), 2: (8, 4, 8), 3: (4, 4, 16), 4: (4, 4, 16), 5: (4, 4, 16),
             6: (4, 4, 32), 14: (8, 8, 4)}
    NAMES = {0: 'I4', 1: 'I8', 2: 'IA4', 3: 'IA8', 4: 'RGB565', 5: 'RGB5A3', 6: 'RGBA8', 8: 'C4', 9: 'C8',
             10: 'C14X2', 14: 'CMPR'}

    def __init__(self, d, o, name):
        assert d[o:o + 4] == b'TEX0'
        self.name = name
        self.data_off = o + s32(d, o + 0x10)
        self.w, self.h = u16(d, o + 0x1C), u16(d, o + 0x1E)
        self.fmt = u32(d, o + 0x20)
        self.d = d

    def decode(self):
        """-> HxWx4 uint8 RGBA (mip 0)"""
        d, w, h, f = self.d, self.w, self.h, self.fmt
        bw, bh, bpp = self.BLOCK[f]
        out = np.zeros((h + bh, w + bw, 4), np.uint8)
        p = self.data_off
        if f == 14:
            for by in range(0, h, 8):
                for bx in range(0, w, 8):
                    for sub in range(4):
                        sx, sy = bx + (sub & 1) * 4, by + (sub >> 1) * 4
                        c0, c1 = u16(d, p), u16(d, p + 2)
                        a, b = _rgb565(c0), _rgb565(c1)
                        if c0 > c1:
                            pal = [a, b, tuple((2 * a[i] + b[i]) // 3 for i in range(3)) + (255,),
                                   tuple((a[i] + 2 * b[i]) // 3 for i in range(3)) + (255,)]
                        else:
                            pal = [a, b, tuple((a[i] + b[i]) // 2 for i in range(3)) + (255,), (0, 0, 0, 0)]
                        for y in range(4):
                            row = d[p + 4 + y]
                            for x in range(4):
                                out[sy + y, sx + x] = pal[(row >> (6 - 2 * x)) & 3]
                        p += 8
            return out[:h, :w]
        for by in range(0, h, bh):
            for bx in range(0, w, bw):
                if f == 6:
                    blk = d[p:p + 64]; p += 64
                    for i in range(16):
                        y, x = i // 4, i % 4
                        out[by + y, bx + x] = (blk[i * 2 + 1], blk[32 + i * 2], blk[32 + i * 2 + 1], blk[i * 2])
                    continue
                for y in range(bh):
                    for x in range(bw):
                        if f == 0:
                            v = d[p + (y * bw + x) // 2]; v = (v >> 4) if x % 2 == 0 else (v & 15); v *= 17
                            px = (v, v, v, 255)
                        elif f == 1:
                            v = d[p + y * bw + x]; px = (v, v, v, 255)
                        elif f == 2:
                            v = d[p + y * bw + x]; i_, a_ = (v & 15) * 17, (v >> 4) * 17; px = (i_, i_, i_, a_)
                        elif f == 3:
                            a_, i_ = d[p + (y * bw + x) * 2], d[p + (y * bw + x) * 2 + 1]; px = (i_, i_, i_, a_)
                        elif f == 4:
                            px = _rgb565(u16(d, p + (y * bw + x) * 2))
                        elif f == 5:
                            px = _rgb5a3(u16(d, p + (y * bw + x) * 2))
                        else:
                            raise NotImplementedError('texture format %s' % self.NAMES.get(f, f))
                        out[by + y, bx + x] = px
                p += bw * bh * bpp // 8
        return out[:h, :w]


# ---------------------------------------------------------------- models
class Bone:
    pass


class Mdl0:
    def __init__(self, d, o, name):
        assert d[o:o + 4] == b'MDL0'
        self.d, self.o, self.name = d, o, name
        self.version = ver = u32(d, o + 8)
        nsec = {8: 11, 9: 11, 10: 14, 11: 14}[ver]
        secs = [s32(d, o + 0x10 + i * 4) for i in range(nsec)]
        names = ['defs', 'bones', 'verts', 'norms', 'colors', 'uvs'] + (['furv', 'furl'] if ver >= 10 else []) + \
                ['mats', 'shaders', 'objs', 'texlinks', 'pallinks'] + (['user'] if ver >= 11 else [])
        self.sec = {n: (dict(group(d, o + s)) if s else {}) for n, s in zip(names, secs)}
        info = o + 0x10 + nsec * 4 + 4
        self.info = info
        bt = info + s32(d, info + 0x24)
        n = u32(d, bt)
        self.bone_table = [s32(d, bt + 4 + 4 * i) for i in range(n)]   # matrix id -> bone index (-1: envelope)
        self._bones(); self._defs(); self._arrays(); self._mats(); self._objs()

    def _bones(self):
        d = self.d
        offs = {}
        self.bones = []
        for nm, bo in self.sec['bones'].items():
            b = Bone(); b.name = nm; b.off = bo
            b.index, b.mtx_id, b.flags = u32(d, bo + 0xC), u32(d, bo + 0x10), u32(d, bo + 0x14)
            b.billboard = u32(d, bo + 0x18)
            b.scale = struct.unpack_from('>3f', d, bo + 0x20)
            b.rot = struct.unpack_from('>3f', d, bo + 0x2C)
            b.trans = struct.unpack_from('>3f', d, bo + 0x38)
            po = s32(d, bo + 0x5C); b.parent_off = bo + po if po else None
            b.world = np.vstack([np.array(struct.unpack_from('>12f', d, bo + 0x70)).reshape(3, 4), [0, 0, 0, 1]])
            b.inv = np.vstack([np.array(struct.unpack_from('>12f', d, bo + 0xA0)).reshape(3, 4), [0, 0, 0, 1]])
            offs[bo] = b
            self.bones.append(b)
        self.bones.sort(key=lambda b: b.index)
        for b in self.bones:
            b.parent = offs[b.parent_off].index if b.parent_off else -1

    def _defs(self):
        d = self.d
        self.mix = {}      # matrix id -> [(bone index, weight)]
        self.draw = []     # (mat, obj, bone, prio, xlu)
        for nm, p in self.sec['defs'].items():
            xlu = nm == 'DrawXlu'
            while True:
                c = d[p]; p += 1
                if c == 1: break
                elif c == 2: p += 4                                   # NodeTree: bone, parent mtx
                elif c == 3:                                          # NodeMix: weighted matrix
                    mid, cnt = u16(d, p), d[p + 2]; p += 3
                    ws = []
                    for _ in range(cnt):
                        nid, w = u16(d, p), struct.unpack_from('>f', d, p + 2)[0]; p += 6
                        ws.append((self.bone_table[nid] if nid < len(self.bone_table) and self.bone_table[nid] >= 0 else nid, w))
                    self.mix[mid] = ws
                elif c == 4:
                    self.draw.append((u16(d, p), u16(d, p + 2), u16(d, p + 4), d[p + 6], xlu)); p += 7
                elif c == 5: p += 4                                   # NodeMix: matrix -> one node
                elif c == 6: p += 4
                else: raise ValueError('definition cmd %d in %s' % (c, nm))

    def _arrays(self):
        d = self.d
        self.arr = {}
        for kind in ('verts', 'norms', 'uvs', 'colors'):
            lst = []
            for nm, ao in self.sec[kind].items():
                idx = u32(d, ao + 0x10)
                if kind == 'colors':
                    data_off = ao + s32(d, ao + 8); fmt = u32(d, ao + 0x18); stride = d[ao + 0x1C]; cnt = u16(d, ao + 0x1E)
                    vals = []
                    for i in range(cnt):
                        q = data_off + i * stride
                        if fmt == 0: c = _rgb565(u16(d, q))
                        elif fmt in (1, 2): c = (d[q], d[q + 1], d[q + 2], 255)
                        elif fmt == 3: v = u16(d, q); c = tuple(((v >> s) & 15) * 17 for s in (12, 8, 4, 0))
                        elif fmt == 4:
                            v = d[q] << 16 | d[q + 1] << 8 | d[q + 2]
                            c = tuple(((v >> s) & 63) * 255 // 63 for s in (18, 12, 6, 0))
                        else: c = tuple(d[q:q + 4])
                        vals.append(c)
                    lst.append((idx, nm, np.array(vals, np.float32) / 255.0))
                    continue
                data_off = ao + s32(d, ao + 8)
                comp, fmt, div, stride, cnt = u32(d, ao + 0x14), u32(d, ao + 0x18), d[ao + 0x1C], d[ao + 0x1D], u16(d, ao + 0x1E)
                if kind == 'verts': n = 3 if comp == 1 else 2
                elif kind == 'norms': n = 3 if comp == 0 else 9
                else: n = 2 if comp == 1 else 1
                ch, sz = {0: ('B', 1), 1: ('b', 1), 2: ('H', 2), 3: ('h', 2), 4: ('f', 4)}[fmt]
                vals = np.array([struct.unpack_from('>%d%s' % (n, ch), d, data_off + i * stride) for i in range(cnt)], np.float64)
                if fmt != 4: vals /= float(1 << div)
                lst.append((idx, nm, vals))
            lst.sort(key=lambda t: t[0])
            self.arr[kind] = [(nm, v) for _, nm, v in lst]

    def _mats(self):
        d = self.d
        self.mats = []
        for nm, mo in sorted(self.sec['mats'].items(), key=lambda kv: u32(d, kv[1] + 0xC)):
            m = {'name': nm, 'index': u32(d, mo + 0xC), 'xlu': bool(u32(d, mo + 0x10) >> 31),
                 'cull': u32(d, mo + 0x18), 'layers': []}
            nl, lo = s32(d, mo + 0x2C), s32(d, mo + 0x30)
            li = mo + 0x1A8                        # layer flags, texture matrix mode, then each layer's SRT (5 floats)
            m['texmtx_mode'] = u32(d, li + 4)
            for i in range(nl):
                lp = mo + lo + i * 0x34
                no = s32(d, lp)
                sx, sy, rot, tx, ty = struct.unpack_from('>5f', d, li + 8 + i * 20)
                m['layers'].append({'tex': cstr(d, lp + no) if no else '', 'wrap': (u32(d, lp + 0x18), u32(d, lp + 0x1C)),
                                    'srt': (sx, sy, rot, tx, ty)})
            self.mats.append(m)

    def _objs(self):
        d = self.d
        self.objs = []
        for nm, po in self.sec['objs'].items():
            o = {'name': nm}
            mtx = s32(d, po + 8)
            lo, hi = u32(d, po + 0xC), u32(d, po + 0x10)
            dl = po + 0x24 + s32(d, po + 0x2C); dl_size = u32(d, po + 0x28)
            o['index'] = u32(d, po + 0x3C)
            vg, ng = s16(d, po + 0x48), s16(d, po + 0x4A)
            cg = [s16(d, po + 0x4C + 2 * i) for i in range(2)]
            tg = [s16(d, po + 0x50 + 2 * i) for i in range(8)]
            # vertex attribute layout from CP VCD
            attrs = []
            if lo & 1: attrs.append(('pnmtx', 0))
            for i in range(8):
                if lo >> (1 + i) & 1: attrs.append(('texmtx%d' % i, 0))
            for nmA, sh in (('pos', 9), ('nrm', 11), ('clr0', 13), ('clr1', 15)):
                t = lo >> sh & 3
                if t: attrs.append((nmA, t))
            for i in range(8):
                t = hi >> (2 * i) & 3
                if t: attrs.append(('uv%d' % i, t))
            for a, t in attrs:
                if t == 1: raise NotImplementedError('direct vertex data in %s' % nm)
            # display list
            p, end = dl, dl + dl_size
            slots = {}
            prims = []            # list of triangles: each a list of 3 dicts {attr: idx, 'mtx': matrix id}
            while p < end:
                c = d[p]; p += 1
                if c == 0: continue
                if c == 0x08: p += 5; continue
                if c == 0x10: n = u16(d, p) + 1; p += 4 + 4 * n; continue
                if c in (0x20, 0x28, 0x30, 0x38):
                    idx, a = u16(d, p), u16(d, p + 2); p += 4
                    if c == 0x20: slots[(a & 0xFFF) // 12] = idx
                    continue
                if c == 0x40: p += 8; continue
                if c == 0x48: continue
                if c == 0x61: p += 4; continue
                if c & 0x80:
                    kind = c & 0xF8; cnt = u16(d, p); p += 2
                    vs = []
                    for _ in range(cnt):
                        v = {}
                        for a, t in attrs:
                            if t == 0: v[a] = d[p]; p += 1
                            elif t == 2: v[a] = d[p]; p += 1
                            else: v[a] = u16(d, p); p += 2
                        v['mtx'] = slots[v['pnmtx'] // 3] if 'pnmtx' in v else mtx
                        vs.append(v)
                    if kind == 0x90: tris = [vs[i:i + 3] for i in range(0, cnt - 2, 3)]
                    elif kind == 0x98: tris = [(vs[i], vs[i + 1], vs[i + 2]) if i % 2 == 0 else (vs[i + 1], vs[i], vs[i + 2]) for i in range(cnt - 2)]
                    elif kind == 0xA0: tris = [(vs[0], vs[i], vs[i + 1]) for i in range(1, cnt - 1)]
                    elif kind == 0x80: tris = [t for i in range(0, cnt, 4) for t in ((vs[i], vs[i + 1], vs[i + 2]), (vs[i], vs[i + 2], vs[i + 3]))]
                    else: tris = []          # lines / points
                    prims.extend(tris)
                    continue
                raise ValueError('display list cmd %02X in %s' % (c, nm))
            o['tris'] = prims
            o['vg'], o['ng'], o['cg'], o['tg'] = vg, ng, cg, tg
            o['single_mtx'] = mtx
            self.objs.append(o)
        self.objs.sort(key=lambda o: o['index'])

    def influence(self, mid):
        """matrix id -> [(bone index, weight)], rigid: True if the vertex data is in that bone's space"""
        if mid in self.mix:
            return self.mix[mid], False
        bi = self.bone_table[mid]
        return [(bi, 1.0)], True
