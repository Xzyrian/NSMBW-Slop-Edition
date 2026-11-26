"""The SMB3 mode's player model files: NSMBW's model file of a character (Mario.arc's or
Luigi.arc's g3d/model.brres) with the SMB3 suits' models put in, for the SMB3 stage only (the
runtime's rt_charmdl.c loads it as game/mod/characters/smb3/<character>.brres).

  build_smb3_brres.py <Character.arc> <out .brres> [--frog <frog .glb>] [--raccoon <raccoon .glb>]
                      [--check <out .glb>]

  --frog     the Frog suit (models/frog), for the Frog's own file (frog_mario.brres - never the
             character's own: user, 2026-11-26, nothing substituted between games): its Penguin body
             and head (PMB_model, PMH_model) made the Frog's. The runtime (rt_charmdl.c) builds a
             second player model from that file and shows it while the player is a Frog (PU_FROG),
             in that slot; the character's own file, and its Penguin, stay as they are.
               build_smb3_brres.py Mario.arc smb3/mario.brres --raccoon Mario_Raccoon.glb
               build_smb3_brres.py Mario.arc smb3/frog_mario.brres --frog head_type_2.glb
             The Penguin body takes Super Mario's skeleton and matrix
             numbering; its texture player_pbody becomes an atlas of frog_body, frog_belly and
             frog_feet, the head's player_phead one of frog_head and frog_hood_face.
  --raccoon  the Raccoon's parts (models/raccoon): Super's body model (MB_model / LB_model) gets
             three more objects beside its own - the Raccoon body (puffier torso, no fists), the
             fists and NSMB2's open hands - all on its own material (its texture: the open hand
             samples a white spot of the glove), each drawn under a node of its own so the runtime
             can show or hide it (the node's visible flag, 0x100): the Super body under leg_l1,
             the Raccoon body leg_l2, the fists leg_r1, the open hands leg_r2 (only Super's body
             shows until the runtime says otherwise).
  --check    export the result back to .glb (Frog: the Penguin slot; else the Super body).

How: the original file is kept byte for byte and the new parts are added at its end (arrays,
objects with their display lists, dictionaries, draw lists, textures); the original entries are
pointed at them. Materials, shaders, the node tree and the texture links stay Nintendo's.
Display lists load bone matrices as Nintendo's do: 8 at a time, each load with its word count
(12 for a position / texture matrix, 9 for a normal matrix) - see models/CUSTOM_PLAYER_MODELS.md.
"""
import io, json, os, struct, sys
import numpy as np
from PIL import Image

HERE = os.path.dirname(os.path.abspath(__file__))
for p in (HERE, os.path.join(HERE, '..', '..', 'recomp', 'tools')):
    if os.path.isdir(p): sys.path.insert(0, p)
import brres_read as br

u32 = br.u32; s32 = br.s32; u16 = br.u16


# ---------------------------------------------------------------- glb
def read_glb(path):
    d = open(path, 'rb').read()
    n = struct.unpack_from('<I', d, 12)[0]
    J = json.loads(d[20:20 + n]); binc = d[20 + n + 8:]
    CT = {5126: np.float32, 5123: np.uint16, 5125: np.uint32, 5121: np.uint8}
    NC = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}

    def acc(i):
        a = J['accessors'][i]; v = J['bufferViews'][a['bufferView']]
        dt = np.dtype(CT[a['componentType']]); nc = NC[a['type']]
        st = v.get('byteStride', dt.itemsize * nc); off = v.get('byteOffset', 0) + a.get('byteOffset', 0)
        raw = np.frombuffer(binc, np.uint8, count=st * (a['count'] - 1) + dt.itemsize * nc, offset=off)
        out = np.lib.stride_tricks.as_strided(raw.view(np.uint8), (a['count'], dt.itemsize * nc), (st, 1)).copy().view(dt).reshape(a['count'], nc)
        if a.get('normalized'): out = out.astype(np.float64) / np.iinfo(dt).max
        return out.astype(np.float64) if dt == np.float32 else out

    def image(i):
        im = J['images'][i]
        if 'uri' in im:                                                        # (a texture beside the file)
            return Image.open(os.path.join(os.path.dirname(os.path.abspath(path)), im['uri'])).convert('RGBA')
        v = J['bufferViews'][im['bufferView']]
        return Image.open(io.BytesIO(binc[v.get('byteOffset', 0):v.get('byteOffset', 0) + v['byteLength']])).convert('RGBA')
    return J, acc, image


def glb_parts(path):
    """-> {mesh name: [(material name, texture image name, pos, nrm, uv, clr, joint or None, idx)]}"""
    J, acc, image = read_glb(path)
    class Imgs(dict):                                                          # (textures read when asked for)
        def __missing__(self, k):
            for i, im in enumerate(J['images']):
                if im.get('name') == k: self[k] = image(i); return self[k]
            raise KeyError(k)
    imgs = Imgs()
    skin_names = [J['nodes'][n]['name'] for n in J['skins'][0]['joints']] if J.get('skins') else []
    out = {}
    for m in J['meshes']:
        lst = []
        for p in m['primitives']:
            at = p['attributes']; mat = J['materials'][p['material']]
            tex = mat.get('pbrMetallicRoughness', {}).get('baseColorTexture', {}).get('index')
            tname = J['images'][J['textures'][tex]['source']]['name'] if tex is not None else None
            clr = acc(at['COLOR_0']) if 'COLOR_0' in at else np.ones((len(acc(at['POSITION'])), 4))
            if clr.shape[1] == 3: clr = np.c_[clr, np.ones(len(clr))]
            j = None
            if 'JOINTS_0' in at:
                jj = acc(at['JOINTS_0']); ww = acc(at['WEIGHTS_0'])
                j = np.array([skin_names[k] for k in jj[np.arange(len(jj)), ww.argmax(1)].astype(int)])   # (rigid: the heaviest bone, by name)
            lst.append((mat['name'].split('.')[0], tname, acc(at['POSITION']), acc(at['NORMAL']), acc(at['TEXCOORD_0']), clr, j,
                        acc(p['indices']).reshape(-1, 3).astype(int)))
        out[m['name'].split('.')[0]] = lst
    return out, imgs, J


# ---------------------------------------------------------------- textures (CMPR)
def rgb565(c):
    c = np.clip(np.round(c), 0, 255).astype(int)
    return ((c[..., 0] >> 3) << 11) | ((c[..., 1] >> 2) << 5) | (c[..., 2] >> 3)


def from565(v):
    r = (v >> 11) & 31; g = (v >> 5) & 63; b = v & 31
    return np.stack([r << 3 | r >> 2, g << 2 | g >> 4, b << 3 | b >> 2], -1).astype(float)


def cmpr(img):
    """RGB(A) uint8 HxW (multiples of 8) -> GX CMPR bytes (opaque, 4-colour blocks)"""
    a = np.asarray(img, float)[..., :3]; h, w = a.shape[:2]
    out = bytearray()
    for by in range(0, h, 8):
        for bx in range(0, w, 8):
            for sub in range(4):
                blk = a[by + (sub >> 1) * 4: by + (sub >> 1) * 4 + 4, bx + (sub & 1) * 4: bx + (sub & 1) * 4 + 4].reshape(16, 3)
                mean = blk.mean(0); X = blk - mean
                ax = np.linalg.svd(X, full_matrices=False)[2][0] if np.abs(X).max() > 0.5 else np.array([1.0, 1, 1]) / np.sqrt(3)
                t = X @ ax
                c0 = int(rgb565(mean + ax * t.max())); c1 = int(rgb565(mean + ax * t.min()))
                if c0 < c1: c0, c1 = c1, c0
                if c0 == c1:
                    if c0 > 0: c1 = c0 - 1
                    else: c0 = 1
                p0, p1 = from565(np.array(c0)), from565(np.array(c1))
                pal = np.array([p0, p1, (2 * p0 + p1) / 3, (p0 + 2 * p1) / 3])
                ix = np.argmin(((blk[:, None] - pal[None]) ** 2).sum(2), 1)
                out += struct.pack('>HH', c0, c1)
                for y in range(4):
                    out.append(int(ix[y * 4] << 6 | ix[y * 4 + 1] << 4 | ix[y * 4 + 2] << 2 | ix[y * 4 + 3]))
    return bytes(out)


def pad_edges(img, l, t, r, b):
    a = np.asarray(img)
    return Image.fromarray(np.pad(a, ((t, b), (l, r), (0, 0)), mode='edge'))


def atlas_body(imgs):
    """256 x 256: frog_body (0,0), frog_belly (128,0), frog_feet (0,128), each 112 square with an 8 pixel
    border of its edge - so UVs a little past its edge (the belly's) and filtering stay on it"""
    A = Image.new('RGBA', (256, 256), (0, 0, 0, 255)); cells = {}
    for name, (cx, cy) in (('frog_body', (0, 0)), ('frog_belly', (128, 0)), ('frog_feet', (0, 128))):
        A.paste(pad_edges(imgs[name].resize((112, 112), Image.LANCZOS), 8, 8, 8, 8), (cx, cy))
        cells[name] = (cx + 8, cy + 8, 112, 112)
    A.paste(A.crop((0, 0, 128, 128)), (128, 128))
    return A, cells, (256, 256)


def atlas_head(imgs):
    """512 x 256: frog_head 128 square at (0,0) (its edges repeated below); frog_hood_face 256 square at
    (192,0) with 64 pixels of its edge either side (its UVs reach 0.25 past the sides)"""
    A = Image.new('RGBA', (512, 256), (0, 0, 0, 255))
    A.paste(pad_edges(imgs['frog_head'], 0, 0, 64, 128), (0, 0))
    A.paste(pad_edges(imgs['frog_hood_face'], 64, 0, 64, 0), (128, 0))
    return A, {'frog_head': (0, 0, 128, 128), 'frog_hood_face': (192, 0, 256, 256)}, (512, 256)


def remap_uv(uv, cell, size):
    x, y, w, h = cell
    return np.c_[(x + uv[:, 0] * w) / size[0], (y + uv[:, 1] * h) / size[1]]


# ---------------------------------------------------------------- the file
class Out:
    """the original file, with new parts added at its end"""
    def __init__(self, d): self.d = bytearray(d)
    def align(self, n=32):
        while len(self.d) % n: self.d.append(0)
    def add(self, b, align=32):
        self.align(align); at = len(self.d); self.d += b; return at
    def w32(self, o, v): struct.pack_into('>I', self.d, o, v & 0xFFFFFFFF)
    def ws32(self, o, v): struct.pack_into('>i', self.d, o, v)
    def w16(self, o, v): struct.pack_into('>H', self.d, o, v & 0xFFFF)


def name_abs(d, struct_at, name_field):
    return struct_at + s32(d, struct_at + name_field)


def group_entry(d, gabs, name):
    cnt = u32(d, gabs + 4)
    for i in range(1, cnt + 1):
        e = gabs + 8 + i * 16
        if br.cstr(d, gabs + u32(d, e + 8)) == name: return e
    raise KeyError(name)


def mdl0_section_group(d, mo, which):
    names = ['defs', 'bones', 'verts', 'norms', 'colors', 'uvs', 'furv', 'furl', 'mats', 'shaders', 'objs', 'texlinks', 'pallinks', 'user']
    return mo + s32(d, mo + 0x10 + 4 * names.index(which))


def new_array(O, mo, old, kind, data, div=None):
    """an array like the old one (header copied) with new data; -> its offset"""
    d = O.d
    hsize = 0x40 if kind in ('verts', 'uvs') else 0x20
    hdr = bytearray(d[old:old + hsize])
    fmt = u32(d, old + 0x18)
    if kind == 'colors':
        body = bytes(np.clip(np.round(data * 255), 0, 255).astype(np.uint8).reshape(-1))
        stride = 4; cnt = len(data)
    else:
        if div is None: div = d[old + 0x1C]
        ch = {2: '>u2', 3: '>i2'}[fmt]
        q = np.round(data * (1 << div)); lim = (0, 65535) if fmt == 2 else (-32768, 32767)
        assert q.min() >= lim[0] and q.max() <= lim[1], ('%s values out of range for %d fraction bits: %s %s' % (kind, div, data.min(), data.max()))
        body = q.astype(ch).tobytes(); stride = 2 * data.shape[1]; cnt = len(data)
        hdr[0x1C] = div; hdr[0x1D] = stride
    if kind == 'colors': hdr[0x1C] = 4
    struct.pack_into('>H', hdr, 0x1E, cnt)
    if kind == 'verts': struct.pack_into('>6f', hdr, 0x20, *data.min(0), *data.max(0))
    if kind == 'uvs': struct.pack_into('>4f', hdr, 0x20, *data.min(0), *data.max(0))
    data_off = hsize if kind in ('norms', 'colors') else 0x40
    blob = bytes(hdr) + b'\0' * (data_off - hsize) + body
    while len(blob) % 32: blob += b'\0'
    struct.pack_into('>I', bytearray(blob), 0, len(blob))
    blob = bytearray(blob); struct.pack_into('>I', blob, 0, len(blob)); struct.pack_into('>i', blob, 0x08, data_off)
    at = O.add(bytes(blob))
    O.ws32(at + 0x04, mo - at)                                                  # (the model's start)
    O.ws32(at + 0x0C, name_abs(d, old, 0x0C) - at)                              # (its name, where it was)
    return at


def patch_decl(decl, vcd_lo, vcd_hi, pos_frac=None):
    """the object's vertex declaration (CP writes): its VCD, and the position fraction bits in VAT A"""
    b = bytearray(decl); i = 0
    while i + 6 <= len(b):
        if b[i] == 0x08:
            reg = b[i + 1]; v = struct.unpack_from('>I', b, i + 2)[0]
            if reg == 0x50: v = vcd_lo
            elif reg == 0x60: v = vcd_hi
            elif reg == 0x70 and pos_frac is not None: v = (v & ~(0x1F << 4)) | (pos_frac << 4)
            struct.pack_into('>I', b, i + 2, v); i += 6; continue
        if b[i] == 0x10:
            n = struct.unpack_from('>H', b, i + 1)[0] + 1; i += 5 + 4 * n; continue
        if b[i] == 0x61: i += 5; continue
        i += 1
    return bytes(b)


def new_object(O, mo, old, tris, mtx_list=None, vcd=None, pos_frac=None):
    """an object like the old one (header and vertex declaration copied) with a new display list.
    tris: list of triangles, each 3 vertices: dict attr -> index (and 'slot' for pnmtx lists);
    mtx_list: [(matrix ids of the batch, triangles)] for objects with a matrix per vertex"""
    d = O.d
    lo, hi = u32(d, old + 0x0C), u32(d, old + 0x10)
    if vcd: lo, hi = vcd
    attrs = []
    if lo & 1: attrs.append(('pnmtx', 1))
    for i in range(8):
        if lo >> (1 + i) & 1: attrs.append(('texmtx%d' % i, 1))
    for nm, sh in (('pos', 9), ('nrm', 11), ('clr0', 13), ('clr1', 15)):
        t = lo >> sh & 3
        if t: attrs.append((nm, t))
    for i in range(8):
        t = hi >> (2 * i) & 3
        if t: attrs.append(('uv%d' % i, t))
    dl = bytearray()

    def vert(v, slot):
        for a, t in attrs:
            if a == 'pnmtx': dl.append(slot * 3)
            elif a.startswith('texmtx'): dl.append(30 + slot * 3)
            elif t == 2:
                assert v[a] < 256, (a, v[a]); dl.append(v[a])
            else: dl.extend(struct.pack('>H', v[a]))
    nverts = 0
    if mtx_list is None:
        dl.append(0x90); dl.extend(struct.pack('>H', 3 * len(tris)))
        for t in tris:
            for v in t: vert(v, 0)
        nverts = 3 * len(tris)
    else:
        for ids, btris in mtx_list:
            # (indexed XF loads: the matrix id, then (words - 1) << 12 | XF address - 12 words for a
            # position / texture matrix, 9 for a normal matrix; as Nintendo's lists)
            for s, m in enumerate(ids): dl.extend(struct.pack('>BHH', 0x30, m, (11 << 12) | (0x78 + s * 12)))
            for s, m in enumerate(ids): dl.extend(struct.pack('>BHH', 0x20, m, (11 << 12) | (s * 12)))
            for s, m in enumerate(ids): dl.extend(struct.pack('>BHH', 0x28, m, (8 << 12) | (0x400 + s * 9)))
            dl.append(0x90); dl.extend(struct.pack('>H', 3 * len(btris)))
            for t in btris:
                for v in t: vert(v, ids.index(v['mtx']))
            nverts += 3 * len(btris)
    while len(dl) % 32: dl.append(0)
    # header 0x68 + matrix list (count, ids) + vertex declaration (0xE0, 32-aligned) + the list
    hdr = bytearray(d[old:old + 0x68])
    ids_all = sorted({m for ids, _ in mtx_list for m in ids}) if mtx_list else []
    ml = struct.pack('>I', len(ids_all)) + b''.join(struct.pack('>H', m) for m in ids_all)
    decl_at = 0x68 + len(ml)
    while decl_at % 32: decl_at += 1
    old_decl = old + 0x18 + u32(d, old + 0x20)
    decl = patch_decl(d[old_decl:old_decl + u32(d, old + 0x18)], lo, hi, pos_frac)
    prim_at = decl_at + len(decl)
    blob = bytearray(hdr) + ml + b'\0' * (decl_at - 0x68 - len(ml)) + decl + dl
    struct.pack_into('>I', blob, 0x00, len(blob))
    struct.pack_into('>II', blob, 0x0C, lo, hi)
    struct.pack_into('>I', blob, 0x20, decl_at - 0x18)
    struct.pack_into('>III', blob, 0x24, len(dl), len(dl), prim_at - 0x24)
    struct.pack_into('>II', blob, 0x40, nverts, len(tris))
    struct.pack_into('>i', blob, 0x64, 0x68)
    at = O.add(bytes(blob))
    O.ws32(at + 0x04, mo - at); O.ws32(at + 0x38, name_abs(d, old, 0x38) - at)
    return at


def new_tex0(O, brres_at, old, img):
    d = O.d
    w, h = img.size
    hdr = bytearray(d[old:old + 0x40])
    body = cmpr(np.asarray(img))
    struct.pack_into('>I', hdr, 0x04, 0x40 + len(body))
    struct.pack_into('>i', hdr, 0x10, 0x40)
    struct.pack_into('>HHI', hdr, 0x1C, w, h, 14)
    struct.pack_into('>I', hdr, 0x24, 1); struct.pack_into('>2f', hdr, 0x28, 0.0, 0.0)
    at = O.add(bytes(hdr) + body)
    O.ws32(at + 0x0C, brres_at - at); O.ws32(at + 0x14, name_abs(d, old, 0x14) - at)
    return at


def uniq(rows, nd=5):
    key = {}; idx = np.empty(len(rows), int); out = []
    for i, r in enumerate(np.round(rows, nd)):
        k = tuple(r)
        if k not in key: key[k] = len(out); out.append(rows[i])
        idx[i] = key[k]
    return np.array(out), idx


def dict_bytes(names_abs, datas_abs, at, name_len):
    """an NW4R resource dictionary (a Patricia tree, built as wszst / BrawlBox build it) placed at
    'at': names_abs / datas_abs the absolute offsets of the names' characters and the data"""
    n = len(names_abs)
    L = [{'id': 0xFFFF, 'left': 0, 'right': 0, 'name': b'', 'nabs': 0, 'dabs': 0}]
    for k in range(n): L.append({'name': name_len[k], 'nabs': names_abs[k], 'dabs': datas_abs[k]})

    def hibit(v):
        i = 7
        while i > 0 and not (v & 0x80): i -= 1; v = (v << 1) & 0xFF
        return i

    def bit(e, id_):
        c = id_ >> 3; nm = e['name']
        return len(nm) > c and (nm[c] >> (id_ & 7)) & 1

    def calc_id(o, sub):
        ol = len(o['name']) if o else 0; sl = len(sub['name'])
        if ol < sl: return (sl - 1) << 3 | hibit(sub['name'][sl - 1])
        while sl > 0:
            sl -= 1; ch = o['name'][sl] ^ sub['name'][sl]
            if ch: return sl << 3 | hibit(ch)
        return 0xFFFF
    for idx in range(1, n + 1):                                                # (wszst's calc_brres_entry)
        e = L[idx]; prev = L[0]; cur_i = L[0]['left']; cur = L[cur_i]
        e['id'] = calc_id(None, e); e['left'] = e['right'] = idx
        is_right = 0
        while e['id'] <= cur['id'] < prev['id']:
            if e['id'] == cur['id']:
                e['id'] = calc_id(cur, e)
                if bit(cur, e['id']): e['left'] = idx; e['right'] = cur_i
                else: e['left'] = cur_i; e['right'] = idx
            prev = cur
            is_right = bit(e, cur['id'])
            cur_i = cur['right'] if is_right else cur['left']; cur = L[cur_i]
        if bit(cur, e['id']): e['right'] = cur_i
        else: e['left'] = cur_i
        if is_right: prev['right'] = idx
        else: prev['left'] = idx
    size = 8 + 16 * (n + 1)
    out = bytearray(struct.pack('>II', size, n))
    for k, e in enumerate(L):
        out += struct.pack('>HHHHii', e['id'], 0, e['left'], e['right'], (e['nabs'] - at) if k else 0, (e['dabs'] - at) if k else 0)
    return bytes(out)


def add_string(O, s):
    """a name as the file's strings are kept (its length, then the characters, 0-ended); -> the
    characters' offset"""
    O.align(4); b = s.encode()
    at = O.add(struct.pack('>I', len(b)) + b + b'\0', align=4)
    return at + 4


def read_dict(d, g):
    """a dictionary's entries: [(name, data offset)] (absolute)"""
    out = []
    for i in range(1, u32(d, g + 4) + 1):
        e = g + 8 + 16 * i
        out.append((br.cstr(d, g + u32(d, e + 8)), g + u32(d, e + 12)))
    return out


def set_section(O, mo, which, new_abs):
    names = ['defs', 'bones', 'verts', 'norms', 'colors', 'uvs', 'furv', 'furl', 'mats', 'shaders', 'objs', 'texlinks', 'pallinks', 'user']
    O.ws32(mo + 0x10 + 4 * names.index(which), new_abs - mo)


def add_frog(O, B, d0, glb, rep):
    d = O.d
    M = B.models()
    mb, pmb, pmh = M['MB_model'], M['PMB_model'], M['PMH_model']
    parts, imgs, J = glb_parts(glb)
    # ---- the body: the Penguin body's bones take Super Mario's rest pose (the Frog's skeleton)
    # (and its matrix numbering: each bone's matrix id, the matrix table and the node tree - the
    # game computes the first N matrices, N the model's count (info + 0x1C), and the Penguin body
    # lists only its 10 bones first; the Frog body is on 14, as Super Mario's)
    for b_new, b_mb in zip(pmb.bones, mb.bones):
        assert b_new.name == b_mb.name
        d[b_new.off + 0x10:b_new.off + 0x5C] = d0[b_mb.off + 0x10:b_mb.off + 0x5C]
        d[b_new.off + 0x70:b_new.off + 0xD0] = d0[b_mb.off + 0x70:b_mb.off + 0xD0]
    t_new = pmb.info + s32(d0, pmb.info + 0x24); t_mb = mb.info + s32(d0, mb.info + 0x24)
    n_t = u32(d0, t_mb); assert n_t == u32(d0, t_new)
    d[t_new:t_new + 4 + 4 * n_t] = d0[t_mb:t_mb + 4 + 4 * n_t]
    nt_new, nt_mb = pmb.sec['defs']['NodeTree'], mb.sec['defs']['NodeTree']
    ln = pmb.sec['defs']['DrawOpa'] - nt_new; assert ln == mb.sec['defs']['DrawOpa'] - nt_mb
    d[nt_new:nt_new + ln] = d0[nt_mb:nt_mb + ln]
    bones = mb.bones
    mtx_of_bone = {b: mb.bone_table.index(b) for b in range(len(bones)) if b in mb.bone_table}
    bidx = {b.name: k for k, b in enumerate(bones)}
    A_body, cells_b, size_b = atlas_body(imgs)
    P, N, UV, C, MT, TRI = [], [], [], [], [], []
    for mesh in ('body', 'feet', 'hands'):
        for mat, tex, pos, nrm, uv, clr, j, idx in parts[mesh]:
            inv = np.array([bones[bidx[k]].inv for k in j])                            # (each vertex into its bone's space)
            lp = np.einsum('nij,nj->ni', inv, np.c_[pos, np.ones(len(pos))])[:, :3]
            ln = np.einsum('nij,nj->ni', inv[:, :3, :3], nrm); ln /= np.linalg.norm(ln, axis=1, keepdims=True) + 1e-12
            o = sum(len(p) for p in P)
            P.append(lp); N.append(ln); UV.append(remap_uv(uv, cells_b[tex], size_b)); C.append(clr); MT.append([mtx_of_bone[bidx[k]] for k in j])
            TRI.append(idx[:, ::-1] + o)                                         # (glTF counter-clockwise -> GX clockwise)
    P, N, UV, C = map(np.vstack, (P, N, UV, C)); MT = np.concatenate(MT); TRI = np.vstack(TRI)
    up, ip = uniq(P); un, in_ = uniq(N, 4); uu, iu = uniq(UV); uc, ic = uniq(C, 3)
    rep.append('body: %d triangles, %d positions, %d normals, %d UVs, %d colours, %d bones' % (len(TRI), len(up), len(un), len(uu), len(uc), len(set(MT))))
    mo = pmb.o
    g = {k: mdl0_section_group(d, mo, k) for k in ('verts', 'norms', 'colors', 'uvs', 'objs')}
    pos_frac = 11 if np.abs(up).max() < 15.9 else 10
    new = {}
    for kind, arr, extra in (('verts', up, {'div': pos_frac}), ('norms', un, {}), ('colors', uc, {}), ('uvs', uu, {})):
        name, old = list(pmb.sec[kind].items())[0]
        new[kind] = new_array(O, mo, old, kind, arr, **extra)
        O.w32(group_entry(d, g[kind], name) + 12, new[kind] - g[kind])
    # (colour index: 8 bits if it fits, else 16; the rest as Nintendo's)
    old_obj = pmb.sec['objs']['polygon0']
    lo, hi = u32(d0, old_obj + 0x0C), u32(d0, old_obj + 0x10)
    if len(uc) > 255: lo = (lo & ~(3 << 13)) | (3 << 13)
    lo = (lo & ~(3 << 9)) | (3 << 9); lo = (lo & ~(3 << 11)) | (3 << 11); hi = (hi & ~3) | (3 if len(uu) > 255 else (hi & 3))
    verts = [[{'pos': ip[k], 'nrm': in_[k], 'clr0': ic[k], 'uv0': iu[k], 'mtx': MT[k]} for k in t] for t in TRI]
    batches = []; cur = []; ids = []
    for t in verts:
        need = sorted({v['mtx'] for v in t} - set(ids))
        if len(ids) + len(need) > 8: batches.append((ids, cur)); cur = []; ids = []; need = sorted({v['mtx'] for v in t})   # (8 at a time, as Super Mario's body)
        ids = ids + need; cur.append(t)
    if cur: batches.append((ids, cur))
    o_at = new_object(O, mo, old_obj, verts, mtx_list=batches, vcd=(lo, hi), pos_frac=pos_frac)
    O.w32(group_entry(d, g['objs'], 'polygon0') + 12, o_at - g['objs'])
    info = pmb.info
    O.w32(info + 0x10, len(up)); O.w32(info + 0x14, len(TRI))
    used = {m for ids, _ in batches for m in ids}
    O.w32(info + 0x1C, max(u32(d0, mb.info + 0x1C), max(used) + 1))      # (the matrices the game computes: all the ones drawn with)
    wp = np.einsum('nij,nj->ni', np.array([bones[mb.bone_table[m]].world for m in MT]), np.c_[P[np.arange(len(P))], np.ones(len(P))])[:, :3]
    struct.pack_into('>6f', d, info + 0x28, *wp.min(0), *wp.max(0))
    rep.append('body: %d matrix batches, positions with %d fraction bits' % (len(batches), pos_frac))

    # ---- the head (in its own space: the head bone's, the identity)
    A_head, cells_h, size_h = atlas_head(imgs)
    mo = pmh.o
    g = {k: mdl0_section_group(d, mo, k) for k in ('verts', 'norms', 'colors', 'uvs', 'objs')}
    groups = {'face': [], 'eye': []}
    for mat, tex, pos, nrm, uv, clr, j, idx in parts['head']:
        if mat == 'mat_player_eye': groups['eye'].append((pos, nrm, uv, clr, idx))
        else: groups['face'].append((pos, nrm, remap_uv(uv, cells_h[tex], size_h), clr, idx))
    pos_frac_h = {}
    for gi, (key, oname) in enumerate((('face', 'polygon0'), ('eye', 'polygon1'))):
        P = np.vstack([p for p, *_ in groups[key]]); N = np.vstack([n / (np.linalg.norm(n, axis=1, keepdims=True) + 1e-12) for _, n, *_ in groups[key]])
        UV = np.vstack([u for _, _, u, *_ in groups[key]]); C = np.vstack([c for *_, c, _ in groups[key]])
        offs = np.cumsum([0] + [len(p) for p, *_ in groups[key]])
        TRI = np.vstack([t[:, ::-1] + o for (*_, t), o in zip(groups[key], offs)])
        up, ip = uniq(P); un, in_ = uniq(N, 4); uu, iu = uniq(UV); uc, ic = uniq(C, 3)
        pf = 11 if np.abs(up).max() < 15.9 else 10
        old_obj = pmh.sec['objs'][oname]
        for kind, arr, extra in (('verts', up, {'div': pf}), ('norms', un, {}), ('colors', uc, {}), ('uvs', uu, {})):
            name, old = list(pmh.sec[kind].items())[gi]
            if kind == 'uvs' and gi == 0 and uu.max() >= 1.999: raise ValueError('head UVs')
            at = new_array(O, mo, old, kind, arr, **extra)
            O.w32(group_entry(d, g[kind], name) + 12, at - g[kind])
        lo, hi = u32(d0, old_obj + 0x0C), u32(d0, old_obj + 0x10)
        lo = (lo & ~(3 << 9)) | (3 << 9); lo = (lo & ~(3 << 11)) | (3 << 11)
        lo = (lo & ~(3 << 13)) | ((3 if len(uc) > 255 else 2) << 13)
        hi = (hi & ~3) | (3 if len(uu) > 255 else 2)
        verts = [[{'pos': ip[k], 'nrm': in_[k], 'clr0': ic[k], 'uv0': iu[k]} for k in t] for t in TRI]
        at = new_object(O, mo, old_obj, verts, vcd=(lo, hi), pos_frac=pf)
        O.w32(group_entry(d, g['objs'], oname) + 12, at - g['objs'])
        pos_frac_h[key] = (len(TRI), len(up), pf)
    info = pmh.info
    O.w32(info + 0x10, sum(v[1] for v in pos_frac_h.values())); O.w32(info + 0x14, sum(v[0] for v in pos_frac_h.values()))
    allp = np.vstack([p for k in groups for p, *_ in groups[k]])
    struct.pack_into('>6f', d, info + 0x28, *allp.min(0), *allp.max(0))
    rep.append('head: face %d triangles (%d positions, %d fraction bits), eyes %d triangles' % (pos_frac_h['face'][0], pos_frac_h['face'][1], pos_frac_h['face'][2], pos_frac_h['eye'][0]))

    # ---- the textures
    tg = B.folders['Textures(NW4R)']
    root = u16(d0, 0xC); tgroup = [fo for name, fo in br.group(d0, root + 8) if name == 'Textures(NW4R)'][0]
    for tname, img in (('player_pbody', A_body), ('player_phead', A_head)):
        at = new_tex0(O, 0, tg[tname], img.convert('RGB'))
        O.w32(group_entry(d, tgroup, tname) + 12, at - tgroup)
    rep.append('textures: player_pbody %dx%d, player_phead %dx%d (CMPR)' % (A_body.size + A_head.size))
    return A_body, A_head


# the Raccoon's parts: (glb mesh, object name, the node it is drawn under, shown at first)
RACCOON_PARTS = [('body', 'raccoon_body', 'leg_l2'), ('handsA', 'raccoon_fists', 'leg_r1'), ('handsB', 'raccoon_open_hands', 'leg_r2')]
SUPER_BODY_NODE = 'leg_l1'


def add_raccoon(O, B, d0, glb, rep):
    """Super's body model gets the Raccoon body, the fists and the open hands as objects of its own"""
    d = O.d
    M = B.models()
    sname = 'MB_model' if 'MB_model' in M else 'LB_model'
    m = M[sname]; mo = m.o
    bones = m.bones; bidx = {b.name: k for k, b in enumerate(bones)}
    mtx_of_bone = {b: m.bone_table.index(b) for b in range(len(bones)) if b in m.bone_table}
    parts, imgs, J = glb_parts(glb)
    # (all three parts' data in one new set of arrays, index 1 of each kind)
    P, N, UV, C, MT, OBJ, TRI = [], [], [], [], [], [], []
    for oi, (mesh, oname, node) in enumerate(RACCOON_PARTS):
        for mat, tex, pos, nrm, uv, clr, j, idx in parts[mesh]:
            inv = np.array([bones[bidx[k]].inv for k in j])
            lp = np.einsum('nij,nj->ni', inv, np.c_[pos, np.ones(len(pos))])[:, :3]
            ln = np.einsum('nij,nj->ni', inv[:, :3, :3], nrm); ln /= np.linalg.norm(ln, axis=1, keepdims=True) + 1e-12
            o = sum(len(p) for p in P)
            P.append(lp); N.append(ln); UV.append(uv); C.append(clr); MT.append([mtx_of_bone[bidx[k]] for k in j])
            TRI.append(idx[:, ::-1] + o); OBJ.append(np.full(len(idx), oi))
    P, N, UV, C = map(np.vstack, (P, N, UV, C)); MT = np.concatenate(MT); TRI = np.vstack(TRI); OBJ = np.concatenate(OBJ)
    world = np.vstack([q[2] for mesh, _, _ in RACCOON_PARTS for q in parts[mesh]])          # (for the bounding box)
    assert max(MT) < u32(d0, m.info + 0x1C), 'a part uses a matrix the game does not compute'
    up, ip = uniq(P); un, in_ = uniq(N, 4); uu, iu = uniq(UV); uc, ic = uniq(C, 3)
    pos_frac = d0[list(m.sec['verts'].values())[0] + 0x1C]
    if np.abs(up).max() >= (1 << (15 - pos_frac)) - 0.01: raise ValueError('positions out of range')
    new_arrays = {}
    for kind, arr in (('verts', up), ('norms', un), ('colors', uc), ('uvs', uu)):
        oname0, old = list(m.sec[kind].items())[0]
        nm = add_string(O, 'raccoon_parts')
        at = new_array(O, mo, old, kind, arr)
        O.w32(at + 0x10, 1); O.ws32(at + 0x0C, nm - at)                     # (index 1, its own name)
        g_old = mdl0_section_group(d, mo, kind)
        ents = read_dict(d0, mdl0_section_group(d0, mo, kind))
        names = ents + [('raccoon_parts', at)]
        nabs = [g_old + u32(d0, g_old + 8 + 16 * (k + 1) + 8) for k in range(len(ents))] + [nm]
        g_at = len(O.d) + (-len(O.d)) % 4
        blob = dict_bytes(nabs, [x[1] for x in names], g_at, [x[0].encode() for x in names])
        assert O.add(blob, align=4) == g_at
        set_section(O, mo, kind, g_at); new_arrays[kind] = at
    old_obj = list(m.sec['objs'].values())[0]
    lo, hi = u32(d0, old_obj + 0x0C), u32(d0, old_obj + 0x10)
    if len(uc) > 255: lo = (lo & ~(3 << 13)) | (3 << 13)
    lo = (lo & ~(3 << 9)) | (3 << 9); lo = (lo & ~(3 << 11)) | (3 << 11); hi = (hi & ~3) | 3
    obj_at = []
    for oi, (mesh, oname, node) in enumerate(RACCOON_PARTS):
        verts = [[{'pos': ip[k], 'nrm': in_[k], 'clr0': ic[k], 'uv0': iu[k], 'mtx': MT[k]} for k in t] for t in TRI[OBJ == oi]]
        batches = []; cur = []; ids = []
        for t in verts:
            need = sorted({v['mtx'] for v in t} - set(ids))
            if len(ids) + len(need) > 8: batches.append((ids, cur)); cur = []; ids = []; need = sorted({v['mtx'] for v in t})
            ids = ids + need; cur.append(t)
        if cur: batches.append((ids, cur))
        at = new_object(O, mo, old_obj, verts, mtx_list=batches, vcd=(lo, hi), pos_frac=pos_frac)
        nm = add_string(O, oname)
        O.ws32(at + 0x38, nm - at); O.w32(at + 0x3C, oi + 1)               # (its name, its index)
        struct.pack_into('>hh hh', O.d, at + 0x48, 1, 1, 1, -1)             # (arrays: positions, normals, colours 1 / none)
        struct.pack_into('>8h', O.d, at + 0x50, 1, -1, -1, -1, -1, -1, -1, -1)   # (UVs 1)
        obj_at.append((oname, at, nm))
        rep.append('raccoon: %s, %d triangles, %d matrix batches, drawn under %s' % (oname, len(verts), len(batches), node))
    # the objects' dictionary: Super's body and the three parts
    g_old = mdl0_section_group(d0, mo, 'objs'); ents = read_dict(d0, g_old)
    nabs = [g_old + u32(d0, g_old + 8 + 16 * (k + 1) + 8) for k in range(len(ents))] + [x[2] for x in obj_at]
    names = [x[0] for x in ents] + [x[0] for x in obj_at]; datas = [x[1] for x in ents] + [x[1] for x in obj_at]
    g_at = len(O.d) + (-len(O.d)) % 4
    assert O.add(dict_bytes(nabs, datas, g_at, [x.encode() for x in names]), align=4) == g_at
    set_section(O, mo, 'objs', g_at)
    # the draw list: each object under a node of its own (its visibility)
    mat = m.draw[0][0]
    dl = struct.pack('>BHHHB', 4, mat, 0, bidx[SUPER_BODY_NODE], 0)
    for oi, (mesh, oname, node) in enumerate(RACCOON_PARTS): dl += struct.pack('>BHHHB', 4, mat, oi + 1, bidx[node], 0)
    dl += b'\x01'
    da = O.add(dl, align=4)
    defs = mdl0_section_group(d0, mo, 'defs')
    O.w32(group_entry(d, defs, 'DrawOpa') + 12, da - defs)
    # (the parts hidden at first: only Super's body shows until the runtime says otherwise)
    for mesh, oname, node in RACCOON_PARTS:
        b = bones[bidx[node]].off
        O.w32(b + 0x14, u32(d, b + 0x14) & ~0x100)
    bb = np.array(struct.unpack_from('>6f', d0, m.info + 0x28)).reshape(2, 3)     # (the bounding box: the parts in it too)
    struct.pack_into('>6f', O.d, m.info + 0x28, *np.minimum(bb[0], world.min(0)), *np.maximum(bb[1], world.max(0)))
    rep.append('raccoon: bounding box %s -> %s' % (bb.round(2).tolist(), np.array(struct.unpack_from('>6f', O.d, m.info + 0x28)).round(2).tolist()))
    O.w32(m.info + 0x10, u32(d0, m.info + 0x10) + len(up)); O.w32(m.info + 0x14, u32(d0, m.info + 0x14) + len(TRI))
    rep.append('raccoon: in %s, %d positions, %d normals, %d UVs, %d colours' % (sname, len(up), len(un), len(uu), len(uc)))
    return sname


def main():
    args = sys.argv[1:]
    def opt(k):
        if k in args: i = args.index(k); v = args[i + 1]; del args[i:i + 2]; return v
    frog, raccoon, check = opt('--frog'), opt('--raccoon'), opt('--check')
    arc, out = args[:2]
    B = br.Brres(arc); d0 = B.d
    O = Out(d0)
    rep = []
    atl = add_frog(O, B, d0, frog, rep) if frog else None
    body = add_raccoon(O, B, d0, raccoon, rep) if raccoon else None
    O.align(32)
    O.w32(0x08, len(O.d))                                                        # (the file's size)
    open(out, 'wb').write(bytes(O.d))
    if atl:
        atl[0].save(os.path.splitext(out)[0] + '_body_atlas.png'); atl[1].save(os.path.splitext(out)[0] + '_head_atlas.png')
    print('wrote %s (%d KB; the original %d KB)' % (out, len(O.d) // 1024, len(d0) // 1024))
    for r in rep: print('  ' + r)
    if check:
        import export_player_models as ex
        mdls = ['PMB_model', 'PMH_model@face_1'] if frog else [body]
        sys.argv = ['x', out, os.path.dirname(check) or '.', os.path.splitext(os.path.basename(check))[0]] + mdls
        ex.main()


if __name__ == '__main__':
    main()
