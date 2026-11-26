"""Raccoon (Super Leaf) Mario / Luigi for editing: NSMBW's Super body and head, with NSMB2's open hand,
ears and tail, as one glTF (.glb) per character.

  build_raccoon_models.py <NSMB2 RomFS dir> <NSMBW Character.arc> <Mario|Luigi> <out_dir>
  (from the project folder: python models/tools/build_raccoon_models.py NSMB2_RomFS extracted/files/Object/Mario.arc Mario models/raccoon/Mario)
Needs Python 3 with numpy, Pillow and scipy; uses recomp/tools (brres_read, export_player_models) and
SMB3Disassembly/tools/nsmb2_anims.py (NSMB2's CGFX reader).

Parts (one object each; body, hands and tail skinned to one skeleton):
  body    NSMBW's Super body (MB_model / LB_model) without its fists, its torso made puffier as NSMB2's
          Raccoon body is (puff_torso.py; PUFF=0 in the environment: unchanged, PUFF=1.5: more)
  handsA  NSMBW's fists (closed hands)                - visibility group handsA, as in NSMB2
  handsB  NSMB2's open hands (its Raccoon body's handsB), fitted to NSMBW's wrists and glove
  head    NSMBW's Super head (MH_model / LH_model), at face_1
  ears    NSMB2's Raccoon ears, at face_1
  tail    NSMB2's tail (mr_tail / lg_tail) and its 5 bones, under skl_root
NSMB2 swaps handsA / handsB by hiding one group (its models' mesh-node visibility); which hand is shown
is decided by its game code, not its animation files."""
import os, sys, struct
import numpy as np
from PIL import Image
HERE = os.path.dirname(os.path.abspath(__file__))
for d in (HERE, os.path.join(HERE, '..', '..', 'recomp', 'tools'), os.path.join(HERE, '..', '..', 'SMB3Disassembly', 'tools')):
    sys.path.insert(0, os.path.normpath(d))      # (brres_read / export_player_models: recomp/tools; nsmb2_anims: SMB3Disassembly/tools)
import brres_read as br
from export_player_models import Glb, trs, build_prims, WRAP
from nsmb2_mesh import N2Model, euler_mat
from nsmb2_anims import tail_data

CH = {'Mario': dict(body='MB_model', head='MH_model', n2file='Mario.bcres', n2body='mr_tail_body', n2tail='mr_tail', cap_top=-13.53),
      'Luigi': dict(body='LB_model', head='LH_model', n2file='Luigi.bcres', n2body='lg_tail_body', n2tail='lg_tail', cap_top=-15.48)}
EAR_INNER = (236, 196, 140)        # (the inner ear's tan, as the game draws it now: SMB3Disassembly/tools/nsmb2_anims.py)


def hom(P): return np.c_[P, np.ones(len(P))]


def white_texel(tex, uvs):
    """a UV on a flat white patch of the glove (the texels the fist uses), away from any edge"""
    h, w = tex.shape[:2]
    lum = tex[..., :3].min(-1).astype(int)
    best = None
    for u, v in uvs % 1.0:
        x, y = int(u * w), int(v * h)
        if 3 <= x < w - 3 and 3 <= y < h - 3:
            m = lum[y - 3:y + 4, x - 3:x + 4].min()
            if best is None or m > best[0]: best = (m, (x + 0.5) / w, (y + 0.5) / h)
    return best[1:], best[0]


def fit(src, dst):
    """similarity transform taking bounding box src (min, max) onto dst: uniform scale, centres matched"""
    s = float(np.mean((dst[1] - dst[0]) / (src[1] - src[0])))
    c0, c1 = (src[0] + src[1]) / 2, (dst[0] + dst[1]) / 2
    M = np.eye(4); M[:3, :3] *= s; M[:3, 3] = c1 - s * c0
    return M, s


def facing(pos, nrm, ix):
    """share of triangles whose winding agrees with their vertex normals"""
    t = ix.reshape(-1, 3); a, b, c = pos[t[:, 0]], pos[t[:, 1]], pos[t[:, 2]]
    fn = np.cross(b - a, c - a); vn = nrm[t].sum(1)
    return float(((fn * vn).sum(1) > 0).mean())


def open_hands(n2, n2w, A, tri, hand_tri, names, bw, tex_body, report):
    """NSMB2's open hands (its Raccoon body's handsB), fitted to an NSMBW body's wrists and glove.
    n2: the NSMB2 Raccoon body (N2Model), n2w: its bone world matrices by name; A, tri: the NSMBW body
    (build_prims arrays, triangles), hand_tri: its fist triangles; bw: NSMBW bone world matrices by name;
    tex_body: the NSMBW body texture (RGBA). -> (HB: pos, nrm, clr, uv, j; triangle indices)"""
    # ---- NSMB2's open hand (handsB), fitted: NSMB2's fist (handsA) -> NSMBW's fist, per wrist, in wrist space
    hA, hB = n2.shape([m['shape'] for m in n2.meshes if m['node'] == 'handsA'][0]), n2.shape([m['shape'] for m in n2.meshes if m['node'] == 'handsB'][0])
    ob = {'pos': [], 'nrm': [], 'clr': [], 'j': []}
    for wname in ('wrist_l1', 'wrist_r1'):
        wi = names.index(wname)
        sel = A['j'][:, 0] == wi
        sel_v = np.unique(tri[hand_tri].reshape(-1)); sel_v = sel_v[sel[sel_v]]
        nsmbw_local = (np.linalg.inv(bw[wname]) @ hom(A['pos'][sel_v]).T).T[:, :3]
        a = [i for i, b in enumerate(hA['bone']) if b == wname]
        n2_local_A = (np.linalg.inv(n2w[wname]) @ hom(hA['pos'][a]).T).T[:, :3]
        M, s = fit((n2_local_A.min(0), n2_local_A.max(0)), (nsmbw_local.min(0), nsmbw_local.max(0)))
        report.append('%s: open hand scaled %.3f, moved %s' % (wname, s, np.round(M[:3, 3], 2).tolist()))
        b_ = [i for i, b in enumerate(hB['bone']) if b == wname]
        L = (np.linalg.inv(n2w[wname]) @ hom(hB['pos'][b_]).T).T
        Lr = (np.linalg.inv(n2w[wname])[:3, :3] @ hB['nrm'][b_].T).T
        P = (bw[wname] @ M @ L.T).T[:, :3]
        N = (bw[wname][:3, :3] @ Lr.T).T; N /= np.linalg.norm(N, axis=1, keepdims=True)
        ob['pos'].append(P); ob['nrm'].append(N); ob['clr'].append(hB['clr'][b_]); ob['j'] += [wi] * len(b_)
        ob.setdefault('map', {}).update({old: k for k, old in enumerate(b_, start=sum(len(x) for x in ob['pos'][:-1]))})
    # NSMB2 (OpenGL) faces are counter-clockwise like glTF's: kept as they are (checked against the normals below)
    hB_idx_ccw = np.array([ob['map'][v] for v in hB['idx']], np.uint32)
    HB = {k: np.concatenate(v) for k, v in ob.items() if k in ('pos', 'nrm', 'clr')}
    (wu, wv), wl = white_texel(tex_body, A['uv'][tri[hand_tri].reshape(-1)])
    HB['uv'] = np.tile([wu, wv], (len(HB['pos']), 1))
    # match the fist's overall brightness (NSMBW's glove texture carries some shading; this texel is plain white)
    fu = A['uv'][tri[hand_tri].reshape(-1)] % 1.0; th_, tw_t = tex_body.shape[:2]
    fist_tex = tex_body[np.clip((fu[:, 1] * th_).astype(int), 0, th_ - 1), np.clip((fu[:, 0] * tw_t).astype(int), 0, tw_t - 1), :3].mean(1).mean()
    k = min(1.0, fist_tex / wl); HB['clr'] = HB['clr'].copy(); HB['clr'][:, :3] *= k
    report.append('open hand tone x%.3f (the glove texture\'s average under the fist)' % k)
    report.append('open hand: %d triangles, glove texel (%.3f, %.3f) brightness %d' % (len(hB['idx']) // 3, wu, wv, wl))

    f_ccw = facing(HB['pos'], HB['nrm'], hB_idx_ccw)
    hB_idx = hB_idx_ccw if f_ccw > 0.5 else hB_idx_ccw.reshape(-1, 3)[:, ::-1].reshape(-1)
    report.append('open hand winding: %.0f%% of triangles agree with their normals as NSMB2 has them' % (100 * f_ccw))
    HB['j'] = ob['j']
    return HB, hB_idx


def main():
    romfs, arc, char, out = sys.argv[1:5]
    cfg = CH[char]
    os.makedirs(os.path.join(out, 'textures'), exist_ok=True)
    B = br.Brres(arc); models = B.models(); texs = B.textures()
    mb, mh = models[cfg['body']], models[cfg['head']]
    bones = mb.bones; names = [b.name for b in bones]
    bw = {b.name: b.world for b in bones}
    n2 = N2Model(os.path.join(romfs, 'Model', 'Player', cfg['n2file']), cfg['n2body'])
    n2w = {n: n2.world[i] for i, (n, _) in enumerate(n2.bones)}
    report = []

    # ---- NSMBW body, split: the fists are the triangles all on a wrist bone
    joint_of_bone = {b.index: b.index for b in bones}
    (mi, A, idx, _), = build_prims(mb, True, joint_of_bone)
    wrists = {names.index('wrist_l1'), names.index('wrist_r1')}
    tri = idx.reshape(-1, 3)
    on_wrist = np.isin(A['j'][:, 0], list(wrists))
    hand_tri = on_wrist[tri].all(1)
    body_idx, handA_idx = tri[~hand_tri].reshape(-1), tri[hand_tri].reshape(-1)
    report.append('body %d triangles, fists (handsA) %d' % (len(body_idx) // 3, len(handA_idx) // 3))

    # ---- the torso made puffier, as NSMB2's Raccoon body is (puff_torso.py)
    import puff_torso
    n2n = N2Model(os.path.join(romfs, 'Model', 'Player', cfg['n2file']), cfg['n2body'].replace('tail_body', 'normal'))
    field = puff_torso.nsmb2_push(n2n.shape(0), n2.shape(0))
    report.append('NSMB2 torso push: %.2f to %.2f units (mean %.2f) over %d points' % (field[2].min(), field[2].max(), field[2].mean(), len(field[2])))
    strength = float(os.environ.get('PUFF', 1.0))
    if strength:
        bone_of_v = [names[j] for j in A['j'][:, 0]]
        newp, rep = puff_torso.apply(A['pos'], A['nrm'], bone_of_v, idx.reshape(-1, 3), field, strength=strength)
        moved = np.abs(newp - A['pos']).sum(1) > 0
        # normals of the moved points: from their faces (welded by position)
        fn = np.cross(newp[tri[:, 1]] - newp[tri[:, 0]], newp[tri[:, 2]] - newp[tri[:, 0]])
        kp = [tuple(np.round(p, 4)) for p in A['pos']]
        acc = {}
        for t, f in zip(tri, fn):
            for v in t: acc[kp[v]] = acc.get(kp[v], 0) + f
        old_fn = np.cross(A['pos'][tri[:, 1]] - A['pos'][tri[:, 0]], A['pos'][tri[:, 2]] - A['pos'][tri[:, 0]])
        acc0 = {}
        for t, f in zip(tri, old_fn):
            for v in t: acc0[kp[v]] = acc0.get(kp[v], 0) + f
        N = A['nrm'] / np.linalg.norm(A['nrm'], axis=1, keepdims=True)
        rec0 = np.array([acc0[kp[i]] / np.linalg.norm(acc0[kp[i]]) for i in range(len(kp))])
        dev = np.degrees(np.arccos(np.clip((rec0[moved] * N[moved]).sum(1), -1, 1)))
        # the change of face-normal direction, put on the original normals (keeps NSMBW's own smoothing)
        A['nrm'] = A['nrm'].copy()
        for i in np.nonzero(moved)[0]:
            n0 = acc0[kp[i]] / np.linalg.norm(acc0[kp[i]]); n1 = acc[kp[i]] / np.linalg.norm(acc[kp[i]])
            v = N[i] + (n1 - n0); A['nrm'][i] = v / np.linalg.norm(v)
        A['pos'] = newp
        report.append(rep + ' (strength %.2f); normals adjusted on %d vertices (original vs face normals: median %.1f deg)' % (strength, int(moved.sum()), np.median(dev)))

    # ---- NSMB2's open hand (handsB)
    tex_body = texs[mb.mats[0]['layers'][0]['tex']].decode()
    HB, hB_idx = open_hands(n2, n2w, A, tri, hand_tri, names, bw, tex_body, report)
    ob = {'j': HB['j']}
    report.append('body winding check: %.0f%%' % (100 * facing(A['pos'], A['nrm'], idx)))

    # ---- ears: NSMB2's Raccoon head triangles high up and out to the sides (face_1 space)
    # The ears are welded to NSMB2's Raccoon cap, so: the head triangles NSMB2's normal head doesn't have
    # (the Raccoon cap and ears), those reaching out of NSMBW's head, and of them the two biggest pieces
    s0 = n2.shape([m['shape'] for m in n2.meshes if m['node'] == 'player_body' and m['mat'] == 'mat_player_body'][0])
    Lf = (np.linalg.inv(n2w['face_1']) @ hom(s0['pos']).T).T[:, :3]
    onf = np.array([b == 'face_1' for b in s0['bone']])
    nn = N2Model(os.path.join(romfs, 'Model', 'Player', cfg['n2file']), cfg['n2body'].replace('tail_body', 'normal'))
    sn = nn.shape(0); nnw = {n: nn.world[i] for i, (n, _) in enumerate(nn.bones)}
    Ln = (np.linalg.inv(nnw['face_1']) @ hom(sn['pos']).T).T[:, :3]
    normal_tris = {tuple(sorted(map(tuple, np.round(Ln[t], 2)))) for t in sn['idx'].reshape(-1, 3)}
    from scipy.spatial import ConvexHull
    hull = ConvexHull(np.vstack([v for nm, v in mh.arr['verts']]))
    dist = (hull.equations[:, :3] @ Lf.T + hull.equations[:, 3:4]).max(0)       # (> 0: outside NSMBW's head, by that much)
    et = s0['idx'].reshape(-1, 3)
    raccoon_only = np.array([onf[t].all() and tuple(sorted(map(tuple, np.round(Lf[t], 2)))) not in normal_tris for t in et])
    key = lambda v: tuple(np.round(Lf[v], 3))
    seed = raccoon_only & (dist[et].min(1) > 1.0)                               # the flaps: well clear of NSMBW's head
    par = {}
    def find(a):
        while par.setdefault(a, a) != a: par[a] = par[par[a]]; a = par[a]
        return a
    for t in et[seed]:
        r0 = find(key(t[0]))
        for v in t[1:]: par[find(key(v))] = r0
    pieces = {}
    for i in np.nonzero(seed)[0]: pieces.setdefault(find(key(et[i][0])), []).append(i)
    pieces = sorted(pieces.values(), key=len, reverse=True)
    report.append('ear pieces found: sizes %s (the two biggest kept)' % [len(p) for p in pieces][:6])
    cz = Lf[et].mean(1)[:, 2]
    keep = []
    for pc in pieces[:2]:                                                      # each ear grown down into the cap, its own side only
        sel = np.zeros(len(et), bool); sel[pc] = True
        side = np.sign(cz[pc].mean())
        for _ in range(int(os.environ.get('EAR_RINGS', 2))):
            vs = {key(v) for t in et[sel] for v in t}
            grow = raccoon_only & ~sel & (np.sign(cz) == side) & (np.abs(cz) > 2.0) & np.array([any(key(v) in vs for v in t) for t in et])
            if not grow.any(): break
            sel |= grow
        keep += list(np.nonzero(sel)[0])
    et = et[sorted(set(keep))]
    ev = np.unique(et); emap = {v: i for i, v in enumerate(ev)}
    EA = {'pos': Lf[ev], 'nrm': (np.linalg.inv(n2w['face_1'])[:3, :3] @ s0['nrm'][ev].T).T, 'clr': s0['clr'][ev], 'uv': s0['uv'][ev].copy()}
    e_idx = np.array([emap[v] for v in et.reshape(-1)], np.uint32)
    if facing(EA['pos'], EA['nrm'], e_idx) < 0.5: e_idx = e_idx.reshape(-1, 3)[:, ::-1].reshape(-1)
    # the ears' texture: NSMB2's texels under them (cropped), white made the inner-ear tan
    n2tex = n2.texture('player_body.0'); th, tw = n2tex.shape[:2]
    u0, v0 = np.floor(EA['uv'].min(0) * [tw, th]).astype(int) - 1; u1, v1 = np.ceil(EA['uv'].max(0) * [tw, th]).astype(int) + 1
    u0, v0 = max(u0, 0), max(v0, 0); u1, v1 = min(u1, tw), min(v1, th)
    crop = n2tex[v0:v1, u0:u1].copy()
    white = crop.min(-1) > 190; crop[white] = EAR_INNER
    ear_png = 'raccoon_ears.png'
    Image.fromarray(crop, 'RGB').save(os.path.join(out, 'textures', ear_png))
    EA['uv'] = (EA['uv'] * [tw, th] - [u0, v0]) / [u1 - u0, v1 - v0]
    report.append('ears: %d triangles, texture %dx%d (cut from NSMB2\'s)' % (len(e_idx) // 3, u1 - u0, v1 - v0))

    # ---- tail: NSMB2's, its bones under skl_root (the tail model's space is skl_root's)
    tb, tverts, tidx, ttexs, _ = tail_data(romfs, cfg['n2file'], cfg['n2tail'])
    tw_ = []
    for name, par, t, r in tb:
        M = np.eye(4); M[:3, :3] = euler_mat(r); M[:3, 3] = t
        tw_.append((tw_[par] if par >= 0 else np.eye(4)) @ M)
    skl = bw['skl_root']
    TA = {'pos': (skl @ hom(np.array([v[0] for v in tverts])).T).T[:, :3],
          'nrm': (skl[:3, :3] @ np.array([v[1] for v in tverts]).T).T,
          'uv': np.array([(v[2][0], 1.0 - v[2][1]) for v in tverts]),
          'jb': [v[3] for v in tverts], 'wb': [v[4] for v in tverts]}
    t_idx = np.array(tidx, np.uint32)
    if facing(TA['pos'], TA['nrm'], t_idx) < 0.5: t_idx = t_idx.reshape(-1, 3)[:, ::-1].reshape(-1)
    Image.fromarray(np.array(ttexs[0], np.uint8), 'RGB').save(os.path.join(out, 'textures', 'player_tail.png'))
    report.append('tail: %d triangles, %d bones' % (len(t_idx) // 3, len(tb)))

    # ---- textures of the NSMBW parts
    for n in ('player_body.0', 'player_head.0', 'player_eye.0'):
        Image.fromarray(texs[n].decode(), 'RGBA').save(os.path.join(out, 'textures', n + '.png'))

    # ---- glTF
    g = Glb(); J = g.j
    for b in bones:
        pw = bones[b.parent].world if b.parent >= 0 else np.eye(4)
        J['nodes'].append({'name': b.name, **trs(np.linalg.inv(pw) @ b.world)})
    for b in bones:
        if b.parent >= 0: J['nodes'][b.parent].setdefault('children', []).append(b.index)
    nb = len(bones)
    for i, (name, par, _, _) in enumerate(tb):
        pw = tw_[par] if par >= 0 else np.eye(4)
        J['nodes'].append({'name': name, **trs(np.linalg.inv(pw) @ tw_[i])})
        J['nodes'][nb + par if par >= 0 else names.index('skl_root')].setdefault('children', []).append(nb + i)
    joints = list(range(nb + len(tb)))
    ibm = [b.inv for b in bones] + [np.linalg.inv(skl @ w) for w in tw_]
    J['skins'].append({'name': char + '_Raccoon_skeleton', 'joints': joints, 'skeleton': 0,
                       'inverseBindMatrices': g.acc(np.array([m.T for m in ibm], np.float32).reshape(-1, 16), 'MAT4', target=None)})
    mats = {}

    def mat(name, tex, wrap=(2, 2), tt=None, nw4r=None):
        if name in mats: return mats[name]
        J['images'].append({'name': tex, 'uri': 'textures/%s.png' % tex if not tex.endswith('.png') else 'textures/' + tex})
        J['samplers'].append({'magFilter': 9729, 'minFilter': 9729, 'wrapS': WRAP[wrap[0]], 'wrapT': WRAP[wrap[1]]})
        J['textures'].append({'sampler': len(J['samplers']) - 1, 'source': len(J['images']) - 1})
        bt = {'index': len(J['textures']) - 1}
        if tt:
            bt['extensions'] = {'KHR_texture_transform': tt}
            if 'KHR_texture_transform' not in J.setdefault('extensionsUsed', []): J['extensionsUsed'].append('KHR_texture_transform')
        J['materials'].append({'name': name, 'pbrMetallicRoughness': {'baseColorTexture': bt, 'metallicFactor': 0.0, 'roughnessFactor': 0.8},
                               'alphaMode': 'MASK', 'alphaCutoff': 0.5, **({'extras': nw4r} if nw4r else {})})
        mats[name] = len(J['materials']) - 1; return mats[name]

    def prim(D, ix, m, joints4=None, weights4=None):
        at = {'POSITION': g.acc(np.asarray(D['pos'], np.float32), 'VEC3', minmax=True),
              'NORMAL': g.acc((np.asarray(D['nrm']) / np.linalg.norm(D['nrm'], axis=1, keepdims=True)).astype(np.float32), 'VEC3'),
              'TEXCOORD_0': g.acc(np.asarray(D['uv'], np.float32), 'VEC2')}
        if 'clr' in D: at['COLOR_0'] = g.acc(np.asarray(D['clr'], np.float32), 'VEC4')
        if joints4 is not None:
            at['JOINTS_0'] = g.acc(np.asarray(joints4, np.uint16), 'VEC4', ctype=5123)
            at['WEIGHTS_0'] = g.acc(np.asarray(weights4, np.float32), 'VEC4')
        return {'attributes': at, 'indices': g.acc(np.asarray(ix, np.uint32), 'SCALAR', ctype=5125, target=34963), 'material': m}

    def mesh_node(name, prims, skin=False, extras=None):
        J['meshes'].append({'name': name, 'primitives': prims})
        n = {'name': name, 'mesh': len(J['meshes']) - 1}
        if skin: n['skin'] = 0
        if extras: n['extras'] = extras
        J['nodes'].append(n); return len(J['nodes']) - 1

    m_body = mat('mat_player_body', 'player_body.0', mb.mats[0]['layers'][0]['wrap'], nw4r={'nw4r_layers': [l['tex'] for l in mb.mats[0]['layers']]})
    j4 = lambda js: np.array([[j, 0, 0, 0] for j in js]); w4 = lambda n: np.tile([1.0, 0, 0, 0], (n, 1))
    roots = [0]
    roots.append(mesh_node('body', [prim(A, body_idx, m_body, A['j'], A['w'])], True, {'from': cfg['body']}))
    roots.append(mesh_node('handsA', [prim(A, handA_idx, m_body, A['j'], A['w'])], True,
                           {'visibility_group': 'handsA', 'what': "closed hands (NSMBW's fists)"}))
    roots.append(mesh_node('handsB', [prim(HB, hB_idx, m_body, j4(ob['j']), w4(len(ob['j'])))], True,
                           {'visibility_group': 'handsB', 'what': "open hands (NSMB2's Raccoon handsB)"}))
    tj = np.array([[nb + a, nb + b if wb_[1] > 0 else 0, 0, 0] for (a, b), wb_ in zip(TA['jb'], TA['wb'])]); twt = np.array([[a, b, 0, 0] for a, b in TA['wb']], float)
    twt /= twt.sum(1, keepdims=True)
    m_tail = mat('mat_player_tail', 'player_tail.png', (1, 1))
    roots.append(mesh_node('tail', [prim(TA, t_idx, m_tail, tj, twt)], True, {'from': 'NSMB2 ' + cfg['n2tail']}))
    # head (rigid, at face_1)
    hp = []
    for mi_, D, ix, oname in build_prims(mh, False, {0: 0}):
        md = mh.mats[mi_]; L0 = md['layers'][0]
        tt = None
        if L0['srt'] != (1.0, 1.0, 0.0, 0.0, 0.0):
            sx, sy, rot, tx, ty = L0['srt']; tt = {'scale': [sx, sy], 'offset': [-sx * tx, sy * ty + 1 - sy]}
        D2 = {'pos': D['pos'], 'nrm': D['nrm'], 'uv': D['uv'], 'clr': D['clr']}
        hp.append(prim(D2, ix, mat(md['name'], L0['tex'], L0['wrap'], tt)))
    fi = names.index('face_1')
    J['nodes'][fi].setdefault('children', []).append(mesh_node('head', hp, extras={'from': cfg['head'], 'attached_to': 'face_1'}))
    J['nodes'][-1].update(trs(mh.bones[0].world))
    m_ear = mat('mat_player_ear', ear_png, (0, 0))
    J['nodes'][fi]['children'].append(mesh_node('ears', [prim(EA, e_idx, m_ear)], extras={'from': 'NSMB2 ' + cfg['n2body'], 'attached_to': 'face_1'}))
    J['scenes'][0]['nodes'] = roots
    path = os.path.join(out, '%s_Raccoon.glb' % char)
    g.save(path)
    print('wrote', path); print('\n'.join('  ' + r for r in report))


if __name__ == '__main__':
    main()
