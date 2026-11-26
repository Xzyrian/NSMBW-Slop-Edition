"""Export NSMBW player models (BRRES MDL0) to glTF 2.0 (.glb) + PNG textures.
usage: export_player_models.py <Character.arc | model.brres> <out_dir> <Character> <body> [<head>@<joint>] [<extra>@<joint> ...] [tex:.0=.3]
The body is skinned to its skeleton; the other models are rigid and parented to the joint the game
draws them at (head at face_1, the cap at CapPosition)."""
import json, struct, sys, os
import numpy as np
from PIL import Image
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import brres_read as brres

WRAP = {0: 33071, 1: 10497, 2: 33648}


def quat_from_mat(m):
    m = np.asarray(m, float)
    t = m.trace()
    if t > 0:
        s = np.sqrt(t + 1.0) * 2; w = 0.25 * s
        x = (m[2, 1] - m[1, 2]) / s; y = (m[0, 2] - m[2, 0]) / s; z = (m[1, 0] - m[0, 1]) / s
    elif m[0, 0] > m[1, 1] and m[0, 0] > m[2, 2]:
        s = np.sqrt(1.0 + m[0, 0] - m[1, 1] - m[2, 2]) * 2
        w = (m[2, 1] - m[1, 2]) / s; x = 0.25 * s; y = (m[0, 1] + m[1, 0]) / s; z = (m[0, 2] + m[2, 0]) / s
    elif m[1, 1] > m[2, 2]:
        s = np.sqrt(1.0 + m[1, 1] - m[0, 0] - m[2, 2]) * 2
        w = (m[0, 2] - m[2, 0]) / s; x = (m[0, 1] + m[1, 0]) / s; y = 0.25 * s; z = (m[1, 2] + m[2, 1]) / s
    else:
        s = np.sqrt(1.0 + m[2, 2] - m[0, 0] - m[1, 1]) * 2
        w = (m[1, 0] - m[0, 1]) / s; x = (m[0, 2] + m[2, 0]) / s; y = (m[1, 2] + m[2, 1]) / s; z = 0.25 * s
    q = np.array([x, y, z, w]); return (q / np.linalg.norm(q)).tolist()


def trs(m):
    t = m[:3, 3]; s = np.linalg.norm(m[:3, :3], axis=0); r = m[:3, :3] / s
    if np.linalg.det(r) < 0: s[0] = -s[0]; r[:, 0] = -r[:, 0]
    out = {}
    if np.abs(t).max() > 1e-7: out['translation'] = t.tolist()
    q = quat_from_mat(r)
    if abs(q[3]) < 1 - 1e-9: out['rotation'] = q
    if np.abs(s - 1).max() > 1e-6: out['scale'] = s.tolist()
    return out


class Glb:
    def __init__(self):
        self.bin = bytearray(); self.j = {'asset': {'version': '2.0', 'generator': 'nsmbw export_players.py'},
                                          'scenes': [{'nodes': []}], 'scene': 0, 'nodes': [], 'meshes': [],
                                          'accessors': [], 'bufferViews': [], 'materials': [], 'textures': [],
                                          'images': [], 'samplers': [], 'skins': []}

    def view(self, data, target=None):
        while len(self.bin) % 4: self.bin.append(0)
        bv = {'buffer': 0, 'byteOffset': len(self.bin), 'byteLength': len(data)}
        if target: bv['target'] = target
        self.bin += data; self.j['bufferViews'].append(bv); return len(self.j['bufferViews']) - 1

    def acc(self, arr, typ, ctype=5126, target=34962, norm=False, minmax=False):
        arr = np.ascontiguousarray(arr)
        v = self.view(arr.tobytes(), target)
        a = {'bufferView': v, 'componentType': ctype, 'count': int(arr.shape[0]), 'type': typ}
        if norm: a['normalized'] = True
        if minmax: a['min'] = arr.min(0).tolist(); a['max'] = arr.max(0).tolist()
        self.j['accessors'].append(a); return len(self.j['accessors']) - 1

    def save(self, path):
        for k in [k for k, v in self.j.items() if v == []]: del self.j[k]
        while len(self.bin) % 4: self.bin.append(0)
        self.j['buffers'] = [{'byteLength': len(self.bin)}]
        js = json.dumps(self.j, separators=(',', ':')).encode()
        while len(js) % 4: js += b' '
        out = struct.pack('<III', 0x46546C67, 2, 12 + 8 + len(js) + 8 + len(self.bin))
        out += struct.pack('<II', len(js), 0x4E4F534A) + js + struct.pack('<II', len(self.bin), 0x004E4942) + bytes(self.bin)
        open(path, 'wb').write(out)


def build_prims(m, skinned, joint_of_bone):
    """-> list of (material index in m.mats, dict of numpy arrays, indices)"""
    by_obj = {o: mat for mat, o, _b, _p, _x in m.draw}
    prims = []
    for oi, o in enumerate(m.objs):
        P = m.arr['verts'][o['vg']][1]
        N = m.arr['norms'][o['ng']][1] if o['ng'] >= 0 else None
        C = m.arr['colors'][o['cg'][0]][1] if o['cg'][0] >= 0 else None
        T = m.arr['uvs'][o['tg'][0]][1] if o['tg'][0] >= 0 else None
        T1 = m.arr['uvs'][o['tg'][1]][1] if o['tg'][1] >= 0 else None
        uniq = {}; cols = {'pos': [], 'nrm': [], 'clr': [], 'uv': [], 'uv1': [], 'j': [], 'w': []}; idx = []
        for tri in o['tris']:
            for v in tri:
                key = (v.get('pos'), v.get('nrm'), v.get('clr0'), v.get('uv0'), v.get('uv1'), v['mtx'])
                if key not in uniq:
                    uniq[key] = len(uniq)
                    infl, rigid = m.influence(v['mtx'])
                    p = np.append(P[v['pos']], 1.0)
                    n = N[v['nrm']] if N is not None else np.array([0, 1, 0.])
                    if skinned and rigid:          # bone space -> model (bind) space
                        W = m.bones[infl[0][0]].world
                        p = W @ p; n = W[:3, :3] @ n
                    nl = np.linalg.norm(n); n = n / nl if nl > 0 else np.array([0, 1, 0.])
                    cols['pos'].append(p[:3]); cols['nrm'].append(n)
                    if C is not None: cols['clr'].append(C[v['clr0']])
                    if T is not None: cols['uv'].append(T[v['uv0']])
                    if T1 is not None: cols['uv1'].append(T1[v['uv1']])
                    infl = sorted(infl, key=lambda t: -t[1])[:4]
                    js = [joint_of_bone[b] for b, _ in infl] + [0] * (4 - len(infl))
                    ws = [w for _, w in infl] + [0] * (4 - len(infl)); s = sum(ws)
                    cols['j'].append(js); cols['w'].append([w / s for w in ws])
                idx.append(uniq[key])
        # GX winding is clockwise for front faces: flip to glTF's counter-clockwise
        idx = np.array(idx, np.uint32).reshape(-1, 3)[:, ::-1].reshape(-1)
        prims.append((by_obj.get(oi, 0), {k: np.array(v) for k, v in cols.items() if v}, idx, o['name']))
    return prims


def main():
    src, out, char, body = sys.argv[1:5]
    remap = dict(a[4:].split('=') for a in sys.argv[5:] if a.startswith('tex:'))   # tex:.0=.3 - another colour set
    extras = [a.split('@') for a in sys.argv[5:] if not a.startswith('tex:')]
    os.makedirs(os.path.join(out, 'textures'), exist_ok=True)
    B = brres.Brres(src)
    models, texs = B.models(), B.textures()
    # textures: all of them as PNG (the variants too: .0 normal, .1 fire, .2 ice ...)
    for n, t in texs.items():
        Image.fromarray(t.decode(), 'RGBA').save(os.path.join(out, 'textures', n + '.png'))
    g = Glb(); J = g.j
    mb = models[body]
    # skeleton
    base = len(J['nodes'])
    for b in mb.bones:
        pw = mb.bones[b.parent].world if b.parent >= 0 else np.eye(4)
        node = {'name': b.name, **trs(np.linalg.inv(pw) @ b.world)}
        J['nodes'].append(node)
    for b in mb.bones:
        if b.parent >= 0: J['nodes'][base + b.parent].setdefault('children', []).append(base + b.index)
    root = base + [b.index for b in mb.bones if b.parent < 0][0]
    joint_of_bone = {b.index: i for i, b in enumerate(mb.bones)}
    ibm = np.array([b.inv.T for b in mb.bones], np.float32).reshape(-1, 16)
    J['skins'].append({'name': body + '_skeleton', 'joints': [base + b.index for b in mb.bones], 'skeleton': root,
                       'inverseBindMatrices': g.acc(ibm, 'MAT4', target=None)})
    img_of = {}; mat_of = {}

    def material(mname, mdef):
        key = (mname, mdef['layers'][0]['tex'] if mdef['layers'] else '')
        if key in mat_of: return mat_of[key]
        pbr = {'metallicFactor': 0.0, 'roughnessFactor': 0.8}
        if mdef['layers']:
            L = mdef['layers'][0]; tn = L['tex']
            for k, v in remap.items():          # (colour sets: body and head; player_eye.N are expressions)
                if tn.endswith(k) and not tn.startswith('player_eye'): tn = tn[:-len(k)] + v
            if tn not in img_of:
                J['images'].append({'name': tn, 'uri': 'textures/%s.png' % tn}); img_of[tn] = len(J['images']) - 1
            J['samplers'].append({'magFilter': 9729, 'minFilter': 9729, 'wrapS': WRAP.get(L['wrap'][0], 10497),
                                  'wrapT': WRAP.get(L['wrap'][1], 10497)})
            J['textures'].append({'sampler': len(J['samplers']) - 1, 'source': img_of[tn]})
            pbr['baseColorTexture'] = {'index': len(J['textures']) - 1}
            sx, sy, rot, tx, ty = L['srt']
            if (sx, sy, rot, tx, ty) != (1.0, 1.0, 0.0, 0.0, 0.0):
                # NW4R Maya-mode texture matrix: u' = sx*(u - tx), v' = sy*(v + ty) + 1 - sy (no rotation here)
                assert rot == 0 and mdef['texmtx_mode'] == 0, (mname, L)
                pbr['baseColorTexture']['extensions'] = {'KHR_texture_transform': {
                    'scale': [sx, sy], 'offset': [-sx * tx, sy * ty + 1 - sy]}}
                J.setdefault('extensionsUsed', []).append('KHR_texture_transform') if 'KHR_texture_transform' not in J.get('extensionsUsed', []) else None
        mat = {'name': mname, 'pbrMetallicRoughness': pbr,
               'extras': {'nw4r_layers': [{'texture': l['tex'], 'srt': l['srt']} for l in mdef['layers']], 'nw4r_cull': mdef['cull']}}
        if mdef['cull'] in (0,): mat['doubleSided'] = True
        if mdef['xlu']: mat['alphaMode'] = 'BLEND'
        else: mat['alphaMode'] = 'MASK'; mat['alphaCutoff'] = 0.5
        J['materials'].append(mat); mat_of[key] = len(J['materials']) - 1; return mat_of[key]

    def mesh(m, skinned):
        prims = []
        jb = joint_of_bone if skinned else {0: 0}
        for mi, a, idx, oname in build_prims(m, skinned, jb):
            attrs = {'POSITION': g.acc(a['pos'].astype(np.float32), 'VEC3', minmax=True),
                     'NORMAL': g.acc(a['nrm'].astype(np.float32), 'VEC3')}
            if 'uv' in a: attrs['TEXCOORD_0'] = g.acc(a['uv'].astype(np.float32), 'VEC2')
            if 'uv1' in a: attrs['TEXCOORD_1'] = g.acc(a['uv1'].astype(np.float32), 'VEC2')
            if 'clr' in a: attrs['COLOR_0'] = g.acc(a['clr'].astype(np.float32), 'VEC4')
            if skinned:
                attrs['JOINTS_0'] = g.acc(a['j'].astype(np.uint16), 'VEC4', ctype=5123)
                attrs['WEIGHTS_0'] = g.acc(a['w'].astype(np.float32), 'VEC4')
            prims.append({'attributes': attrs, 'indices': g.acc(idx, 'SCALAR', ctype=5125, target=34963),
                          'material': material(m.mats[mi]['name'], m.mats[mi]), 'extras': {'nw4r_object': oname}})
        J['meshes'].append({'name': m.name, 'primitives': prims}); return len(J['meshes']) - 1

    J['nodes'].append({'name': body, 'mesh': mesh(mb, True), 'skin': 0})
    body_node = len(J['nodes']) - 1
    for name, joint in extras:
        m = models[name]
        jn = base + [b.index for b in mb.bones if b.name == joint][0]
        # the model's root bone (player_head / mario_cap) is the model's own space; drawn at the joint
        node = {'name': name, 'mesh': mesh(m, False), **trs(m.bones[0].world), 'extras': {'attached_to': joint}}
        J['nodes'].append(node); J['nodes'][jn].setdefault('children', []).append(len(J['nodes']) - 1)
    J['scenes'][0]['nodes'] = [root, body_node]
    path = os.path.join(out, '%s.glb' % char)
    g.save(path)
    print('wrote', path)


if __name__ == '__main__':
    main()
