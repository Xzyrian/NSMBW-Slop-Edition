"""Fix the user's edited Frog Mario head: the hood rebuilt on Nintendo's own layout (the original
Penguin hood's triangles, nothing split) and fitted to the user's shape; the eyes as two balls of
their own set into the head, like Mario's nose; the cracks between the hood's edge and the face
closed; and the frog eyes (SMB3 style) and nostril dots painted on a texture. Left and right are made
exactly the same. Everything else in the file is kept as it is.

  fix_frog_head.py <user's .glb> <out .glb> <out textures dir> [name=value ...]
  (from the project folder: python models/tools/fix_frog_head.py models/frog/user_edited/Mario_Frog.glb
   models/frog/user_edited/Mario_Frog_fixed.glb models/frog/user_edited/textures)
Needs Python 3 with numpy, scipy, matplotlib and Pillow, and retopo_template.py beside it.

Options:
  template=<.glb>   the model whose hood layout is used (default: models/frog/Mario/Mario_Frog.glb)
  eye_base=-12      the height where the user's eye bumps start (-Y is up): above it the head keeps
                    the template's round top, and the eyes are the balls
  eye_ball=fit      the left eye ball (centre x,y,z and radii x,y,z), or 'fit' to fit it to the
                    user's eye bump; eye_gap=2.0 the gap between the two eyes' inner edges
  eye_seg=8, eye_rings=6  the balls' segments round and rings front to back
  eyes=joined       the older way instead: the eyes grown out of the hood, its top split to hold
                    them (with split_below=-8, eye_blend=1.6, eye_split=1)
  eye_pupil=0.46,0.58 (pupil width, height as a share of each eye), round_eyes=1 (0: the patches'
  own shapes), eye_size=0.88 (the round eye's size, a share of its patch), outline=0.08 (the eyes'
  dark outline, units), nostril=0.4 (nostril radius), nostril_gap=0.55 (each nostril's distance
  from the middle), green=44,160,60.
"""
import os, sys, io, json, struct
import numpy as np
from PIL import Image, ImageDraw
HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import retopo_template as rt

CT = {5126: np.float32, 5123: np.uint16, 5125: np.uint32, 5121: np.uint8, 5122: np.int16, 5120: np.int8}
NC = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}


# ---------------------------------------------------------------- glb in / out (everything kept)
def read_glb(path):
    d = open(path, 'rb').read()
    jl = struct.unpack_from('<I', d, 12)[0]; J = json.loads(d[20:20 + jl]); B = d[20 + jl + 8:]
    accs = []
    for a in J['accessors']:
        bv = J['bufferViews'][a['bufferView']]; n = NC[a['type']]; dt = CT[a['componentType']]
        off = bv.get('byteOffset', 0) + a.get('byteOffset', 0); st = bv.get('byteStride')
        if st and st != np.dtype(dt).itemsize * n:
            arr = np.stack([np.frombuffer(B, dt, n, off + i * st) for i in range(a['count'])])
        else:
            arr = np.frombuffer(B, dt, a['count'] * n, off).reshape(a['count'], n).copy()
        accs.append(arr)
    imgs = []
    for im in J.get('images', []):
        if 'bufferView' in im:
            bv = J['bufferViews'][im['bufferView']]; imgs.append(B[bv.get('byteOffset', 0):bv.get('byteOffset', 0) + bv['byteLength']])
        else: imgs.append(None)
    return J, accs, imgs


def write_glb(J, accs, imgs, path):
    """J's accessors refer to accs by index (data as numpy, the accessor's own type); images to imgs (PNG bytes)"""
    binb = bytearray(); views = []
    def view(data, target=None):
        while len(binb) % 4: binb.append(0)
        v = {'buffer': 0, 'byteOffset': len(binb), 'byteLength': len(data)}
        if target: v['target'] = target
        binb.extend(data); views.append(v); return len(views) - 1
    used_as_index = {p['indices'] for m in J['meshes'] for p in m['primitives'] if 'indices' in p}
    used_as_attr = {i for m in J['meshes'] for p in m['primitives'] for i in p['attributes'].values()}
    for i, a in enumerate(J['accessors']):
        arr = np.ascontiguousarray(accs[i].astype(CT[a['componentType']]))
        a['bufferView'] = view(arr.tobytes(), 34963 if i in used_as_index else 34962 if i in used_as_attr else None)
        a.pop('byteOffset', None); a['count'] = int(arr.shape[0])
        if 'min' in a or i in used_as_attr and a['type'] == 'VEC3' and a['componentType'] == 5126:
            if a['type'] == 'VEC3' and a['componentType'] == 5126 and i in used_as_attr:
                a['min'] = arr.min(0).tolist(); a['max'] = arr.max(0).tolist()
    for im, data in zip(J.get('images', []), imgs):
        if data is not None:
            im['bufferView'] = view(data); im['mimeType'] = 'image/png'; im.pop('uri', None)
    J['bufferViews'] = views
    while len(binb) % 4: binb.append(0)
    J['buffers'] = [{'byteLength': len(binb)}]
    js = json.dumps(J, separators=(',', ':')).encode()
    while len(js) % 4: js += b' '
    out = struct.pack('<III', 0x46546C67, 2, 12 + 8 + len(js) + 8 + len(binb)) + struct.pack('<II', len(js), 0x4E4F534A) + js + struct.pack('<II', len(binb), 0x004E4942) + bytes(binb)
    open(path, 'wb').write(out)


def add_acc(J, accs, arr, typ, ct, normalized=False):
    J['accessors'].append({'componentType': ct, 'count': len(arr), 'type': typ, **({'normalized': True} if normalized else {})})
    accs.append(np.asarray(arr)); return len(J['accessors']) - 1


# ---------------------------------------------------------------- geometry helpers
def closest_on_tris(P, A, B, C):
    """(n x m x 3) closest points, Ericson's regions"""
    P = P[:, None, :]; ab, ac = B - A, C - A; ap, bp, cp = P - A, P - B, P - C
    d1, d2 = (ab * ap).sum(-1), (ac * ap).sum(-1); d3, d4 = (ab * bp).sum(-1), (ac * bp).sum(-1); d5, d6 = (ab * cp).sum(-1), (ac * cp).sum(-1)
    va, vb, vc = d3 * d6 - d5 * d4, d5 * d2 - d1 * d6, d1 * d4 - d3 * d2
    sd = lambda x: np.where(np.abs(x) < 1e-12, 1e-12, x); den = sd(va + vb + vc)
    out = A + ab * (vb / den)[..., None] + ac * (vc / den)[..., None]
    cand = [((d1 <= 0) & (d2 <= 0), np.broadcast_to(A, out.shape)), ((d3 >= 0) & (d4 <= d3), np.broadcast_to(B, out.shape)),
            ((vc <= 0) & (d1 >= 0) & (d3 <= 0), A + ab * np.clip(d1 / sd(d1 - d3), 0, 1)[..., None]),
            ((d6 >= 0) & (d5 <= d6), np.broadcast_to(C, out.shape)),
            ((vb <= 0) & (d2 >= 0) & (d6 <= 0), A + ac * np.clip(d2 / sd(d2 - d6), 0, 1)[..., None]),
            ((va <= 0) & (d4 - d3 >= 0) & (d5 - d6 >= 0), B + (C - B) * np.clip((d4 - d3) / sd((d4 - d3) + (d5 - d6)), 0, 1)[..., None])]
    for c, v in reversed(cand): out = np.where(c[..., None], v, out)
    return out


def nearest(P, V, F):
    """for each point: (closest point on mesh V/F, triangle index, barycentric)"""
    A, B, C = V[F[:, 0]], V[F[:, 1]], V[F[:, 2]]
    Q = np.zeros_like(P); ti = np.zeros(len(P), int)
    for i in range(0, len(P), 128):
        R = closest_on_tris(P[i:i + 128], A, B, C); d = ((R - P[i:i + 128, None]) ** 2).sum(-1); j = d.argmin(1)
        Q[i:i + 128] = R[np.arange(len(j)), j]; ti[i:i + 128] = j
    a, b, c = A[ti], B[ti], C[ti]
    v0, v1, v2 = b - a, c - a, Q - a
    d00, d01, d11 = (v0 * v0).sum(1), (v0 * v1).sum(1), (v1 * v1).sum(1); d20, d21 = (v2 * v0).sum(1), (v2 * v1).sum(1)
    den = np.where(np.abs(d00 * d11 - d01 * d01) < 1e-12, 1e-12, d00 * d11 - d01 * d01)
    w1 = (d11 * d20 - d01 * d21) / den; w2 = (d00 * d21 - d01 * d20) / den
    return Q, ti, np.c_[1 - w1 - w2, w1, w2]


def vertex_normals(V, F):
    n = np.zeros_like(V)
    fn = np.cross(V[F[:, 1]] - V[F[:, 0]], V[F[:, 2]] - V[F[:, 0]])                # (area-weighted)
    for k in range(3): np.add.at(n, F[:, k], fn)
    return n / (np.linalg.norm(n, axis=1, keepdims=True) + 1e-12)


def symmetrise(P, idx, tol=0.8):
    """the points idx of P made mirror-symmetric across z = 0: each point and its mirror partner (the
    nearest point on the other side, mirrored) meet halfway; points near the middle with no partner
    go onto it. -> (P changed copy, number of points moved, largest move)"""
    P = P.copy(); U = np.unique(np.round(P[idx], 4), axis=0)
    M = U * [1, 1, -1]
    d = np.linalg.norm(U[:, None] - M[None], axis=2); j = d.argmin(1)
    target = {}
    for i, u in enumerate(U):
        if abs(u[2]) < 1e-4: target[tuple(u)] = u * [1, 1, 0]; continue
        if d[i, j[i]] < tol: target[tuple(u)] = (u + M[j[i]]) / 2
        elif abs(u[2]) < 0.2: target[tuple(u)] = u * [1, 1, 0]
        else: target[tuple(u)] = u
    moved = 0; most = 0.0
    for i in idx:
        k = tuple(np.round(P[i], 4)); t = target.get(k, P[i])
        dd = np.linalg.norm(t - P[i]); most = max(most, dd); moved += dd > 1e-4
        P[i] = t
    return P, moved, most


def clip_half(V, F):
    """the part of the mesh with z >= 0 (triangles cut along z = 0, new points exactly on it)"""
    V = [v for v in V]; cut = {}
    def mid(a, b):
        k = (min(a, b), max(a, b))
        if k not in cut:
            za, zb = V[a][2], V[b][2]; t = za / (za - zb)
            p = V[a] + (V[b] - V[a]) * t; p[2] = 0.0; V.append(p); cut[k] = len(V) - 1
        return cut[k]
    out = []
    for t in F:
        z = [V[i][2] for i in t]
        pos = [zz >= -1e-9 for zz in z]
        if all(pos): out.append(list(t)); continue
        if not any(pos): continue
        for r in range(3):                                                    # (rotate so the pattern starts at index 0)
            a, b, c = t[r], t[(r + 1) % 3], t[(r + 2) % 3]
            pa, pb, pc = pos[r], pos[(r + 1) % 3], pos[(r + 2) % 3]
            if pa and not pb and not pc:
                out.append([a, mid(a, b), mid(a, c)]); break
            if pa and pb and not pc:
                m1, m2 = mid(b, c), mid(a, c); out += [[a, b, m1], [a, m1, m2]]; break
    V = np.array(V); F = np.array(out)
    used = np.unique(F); re = -np.ones(len(V), int); re[used] = np.arange(len(used))
    return V[used], re[F]


def mirror_join(V, F):
    """the half (z >= 0) and its mirror image, welded along z = 0"""
    on = np.abs(V[:, 2]) < 1e-6
    V = V.copy(); V[on, 2] = 0.0
    n = len(V); Vm = V * [1, 1, -1]
    idx = np.arange(n) + n; idx[on] = np.nonzero(on)[0]
    keep = ~on
    newV = np.vstack([V, Vm[keep]])
    remap = np.arange(n); remap_m = np.empty(n, int); remap_m[keep] = n + np.arange(keep.sum()); remap_m[on] = np.nonzero(on)[0]
    Fm = remap_m[F][:, ::-1]
    return newV, np.vstack([F, Fm]), remap_m


def pieces(P, T):
    """the mesh's connected pieces (triangle index lists, biggest first); points joined by position"""
    from collections import defaultdict
    key = [tuple(np.round(q, 3)) for q in P]; par = {}
    def find(a):
        while par.setdefault(a, a) != a: par[a] = par[par[a]]; a = par[a]
        return a
    for t in T:
        r0 = find(key[t[0]])
        for v in t[1:]: par[find(key[v])] = r0
    comp = defaultdict(list)
    for i, t in enumerate(T): comp[find(key[t[0]])].append(i)
    return sorted(comp.values(), key=len, reverse=True)


def boundary_loops(F):
    from collections import defaultdict, Counter
    c = Counter(); dirn = {}
    for t in F:
        for a, b in ((t[0], t[1]), (t[1], t[2]), (t[2], t[0])):
            c[frozenset((a, b))] += 1; dirn[frozenset((a, b))] = (a, b)
    nxt = {dirn[e][0]: dirn[e][1] for e, n in c.items() if n == 1}
    loops = []; seen = set()
    for s in nxt:
        if s in seen: continue
        L = [s]; seen.add(s)
        while nxt[L[-1]] != s:
            L.append(nxt[L[-1]]); seen.add(L[-1])
        loops.append(L)
    return loops


# ---------------------------------------------------------------- main
def main():
    src, dst, tdir = sys.argv[1:4]
    opt = dict(a.split('=', 1) for a in sys.argv[4:])
    split_below = float(opt.get('split_below', -8))
    eye_base = float(opt.get('eye_base', -12))
    eye_ball = opt.get('eye_ball', 'fit')
    eye_blend = float(opt.get('eye_blend', 1.6))
    eye_split = opt.get('eye_split', '1') != '0'
    eye_gap = float(opt.get('eye_gap', 2.0))
    eyes_joined = opt.get('eyes', 'separate') == 'joined'
    eye_seg = int(opt.get('eye_seg', 8)); eye_rings = int(opt.get('eye_rings', 6))
    pw, ph_ = [float(x) for x in opt.get('eye_pupil', '0.46,0.58').split(',')]
    nost_r = float(opt.get('nostril', 0.4))
    round_eyes = opt.get('round_eyes', '1') != '0'
    eye_fill = float(opt.get('eye_size', 0.88))
    nost_gap = float(opt.get('nostril_gap', 0.55))
    outline_w = float(opt.get('outline', 0.08))
    green = [int(x) for x in opt.get('green', '44,160,60').split(',')]
    os.makedirs(tdir, exist_ok=True)
    J, accs, imgs = read_glb(src)
    rep = []
    head_node = [n for n in J['nodes'] if n.get('name') == 'head'][0]
    mesh = J['meshes'][head_node['mesh']]
    mname = lambda p: J['materials'][p['material']]['name']
    # every head triangle together, to find the pieces
    prims = mesh['primitives']
    data = []
    for p in prims:
        A = p['attributes']
        clr = accs[A['COLOR_0']].astype(float) / (65535.0 if J['accessors'][A['COLOR_0']]['componentType'] == 5123 else 255.0 if J['accessors'][A['COLOR_0']]['componentType'] == 5121 else 1.0) if 'COLOR_0' in A else None
        data.append({'p': p, 'mat': mname(p), 'pos': accs[A['POSITION']].astype(float), 'nrm': accs[A['NORMAL']].astype(float),
                     'uv': accs[A['TEXCOORD_0']].astype(float), 'clr': clr, 'tri': accs[p['indices']].reshape(-1, 3).astype(int)})
    P = np.vstack([d['pos'] for d in data]); off = np.cumsum([0] + [len(d['pos']) for d in data])
    T = np.vstack([d['tri'] + o for d, o in zip(data, off)]); prim_of = np.concatenate([[k] * len(d['tri']) for k, d in enumerate(data)])
    pcs = pieces(P, T)
    hood = np.zeros(len(T), bool); hood[pcs[0]] = True
    eye_mat = 'mat_player_belly'                                               # (the user's white eye patches)
    eyes_t = hood & np.array([data[k]['mat'] == eye_mat for k in prim_of])
    rep.append('head: %d pieces; the hood %d triangles (%d of them the white eye patches)' % (len(pcs), hood.sum(), eyes_t.sum()))
    CLR = np.vstack([d['clr'] if d['clr'] is not None else np.ones((len(d['pos']), 4)) for d in data])

    # ---- 1. the hood rebuilt on Nintendo's layout. Its two sides are averaged first (each point and
    # its mirror partner meet halfway). Then the original Penguin hood (the template) is taken - less
    # what lies on the face pieces or over the user's face opening - and its top split once (each
    # triangle into four). It is fitted to the user's shape below the eyes, keeping the head round
    # under them; the eyes go on as clean balls (fitted to the user's bumps), joined smoothly, with the
    # triangles round them split once more and spread evenly. The hood's edge follows the user's.
    hv = np.unique(T[hood])
    P, nmoved, most = symmetrise(P, hv)
    rep.append('symmetry: %d hood points were off their mirror partner (by up to %.2f): averaged; the face, moustache and strip are symmetric already' % (nmoved, most * 2))
    V0, F0, wmap = rt.weld(P, T[hood])
    c0 = np.zeros((len(V0), 4)); n0 = np.zeros(len(V0))
    for i in np.unique(T[hood]): c0[wmap[i]] += CLR[i]; n0[wmap[i]] += 1
    c0 /= n0[:, None]
    nrm0 = vertex_normals(V0, F0)
    # the template's hood
    tpl = opt.get('template', os.path.join(HERE, '..', 'frog', 'Mario', 'Mario_Frog.glb'))
    tJ, taccs, _ = read_glb(tpl)
    th = [n for n in tJ['nodes'] if n.get('name') == 'head'][0]
    tP = []; tT = []; o_ = 0
    for p_ in tJ['meshes'][th['mesh']]['primitives']:
        pp = taccs[p_['attributes']['POSITION']].astype(float); tP.append(pp); tT.append(taccs[p_['indices']].reshape(-1, 3).astype(int) + o_); o_ += len(pp)
    tP = np.vstack(tP); tT = np.vstack(tT)
    others = T[~hood]
    best = None
    for pc in pieces(tP, tT):
        if len(pc) < 100: continue
        dd = np.linalg.norm(nearest(V0, tP, tT[pc])[0] - V0, axis=1)
        score = (dd < 1.5).mean()                                              # (the piece covering most of the user's hood)
        if best is None or score > best[0]: best = (score, pc)
    tt = tT[best[1]]
    X = tP[tt].reshape(-1, 3)
    onface = (np.linalg.norm(nearest(X, P, others)[0] - X, axis=1) < 0.05).reshape(-1, 3).all(1)
    TV, TF, _ = rt.weld(tP, tt[~onface])
    rim = rt.longest_loop(F0)
    from matplotlib.path import Path as _Path
    poly = _Path(V0[rim][:, [2, 1]])
    cen = TV[TF].mean(1)
    over = poly.contains_points(cen[:, [2, 1]]) & (cen[:, 0] > 0.5)
    TF = TF[~over]; TF = TF[np.array(pieces(TV, TF)[0])]                      # (stray bits left over: dropped)
    used = np.unique(TF); re_ = -np.ones(len(TV), int); re_[used] = np.arange(len(used)); TV = TV[used]; TF = re_[TF]
    mir = rt.mirror_map(TV)
    n_tpl = len(TF)
    if eyes_joined: V1, F1, _, mir1 = rt.subdivide_region(TV, TF, TV[TF].mean(1)[:, 1] < split_below, mir)
    else: V1, F1, mir1 = TV, TF, mir                                          # (Nintendo's triangles as they are: nothing split)
    b1 = np.array(sorted({x for e in rt.boundary_edges(F1) for x in e}))
    RA = V0[rim]; RB = V0[np.roll(rim, -1)]
    rim_to = lambda X: rt.closest_on_segments(X, RA, RB)[0]
    # the eye balls
    if eye_ball == 'fit':
        S_ = rt.sample_surface(V0, F0, 0.2)
        Lb = S_[(S_[:, 1] < eye_base - 1.0) & (S_[:, 2] > 0.4) & (S_[:, 0] > 0)]
        from scipy.optimize import least_squares
        def res_(p_):
            c_ = p_[:3]; r_ = np.abs(p_[3:6]); u_ = (Lb - c_) / r_; n_ = np.linalg.norm(u_, axis=1)
            return (n_ - 1) * np.linalg.norm(Lb - c_, axis=1) / n_
        sol = least_squares(res_, np.r_[Lb.mean(0) + [-1, 1, 0], 2, 2, 2])
        bc_, br_ = sol.x[:3], np.abs(sol.x[3:])
    else:
        vals = [float(x) for x in eye_ball.split(',')]; bc_, br_ = np.array(vals[:3]), np.array(vals[3:6])
    # (a gap between the eyes: the inner edges kept eye_gap apart, the outer edge where it was)
    if bc_[2] - br_[2] < eye_gap / 2:
        outer = bc_[2] + br_[2]; br_ = br_.copy(); bc_ = bc_.copy()
        br_[2] = (outer - eye_gap / 2) / 2; bc_[2] = outer - br_[2]
    balls = [(bc_, br_), (bc_ * [1, 1, -1], br_)]
    # the head without the eye bumps
    excl = lambda X: X[:, 1] < eye_base
    samples = rt.sample_surface(V0, F0, 0.45)
    Vb = rt.fit(V1, F1, (V0, F0), nearest, samples[~excl(samples)], b1, mir1, rim_to=rim_to, rim_w=50, skip=excl)
    if not eyes_joined:
        V, F = Vb.copy(), F1
        V[b1] = rim_to(V[b1]); V = rt.make_symmetric(V, mir1); mir2 = mir1
    if eyes_joined:
        # (a smooth, dense copy of it: for placing new points and for its facing)
        Vd, Fd, _, mird = rt.subdivide_region(Vb, F1, np.ones(len(F1), bool), mir1)
        Vd, Fd, _, mird = rt.subdivide_region(Vd, Fd, np.ones(len(Fd), bool), mird)
        bd = np.array(sorted({x for e in rt.boundary_edges(Fd) for x in e}))
        Vd = rt.taubin(Vd, Fd, np.setdiff1d(np.arange(len(Vd)), bd), mird, iters=15)
        Nd = vertex_normals(Vd, Fd)
        if (Nd * (Vd - [0, -5, 0])).sum(1).mean() < 0: Nd = -Nd
        # the triangles round the eyes split once more
        V2, F2, mir2 = Vb, F1, mir1
        cen = V2[F2].mean(1); near_ = np.zeros(len(F2), bool)
        for c_, r_ in balls: near_ |= np.linalg.norm((cen - c_) / (r_ * 1.5), axis=1) < 1
        if eye_split: V2, F2, _, mir2 = rt.subdivide_region(V2, F2, near_, mir2)
        b2 = np.array(sorted({x for e in rt.boundary_edges(F2) for x in e}))
        inner = np.setdiff1d(np.arange(len(V2)), b2)
        V2 = V2.copy(); V2[inner] = nearest(V2[inner], Vd, Fd)[0]
        def lift(X):
            Q_, ti_, bc2 = nearest(X, Vd, Fd)
            N_ = (Nd[Fd[ti_]] * bc2[..., None]).sum(1); N_ /= np.linalg.norm(N_, axis=1, keepdims=True)
            return rt.make_symmetric(rt.union_balls(X, N_, balls, k=eye_blend, D=rt.lift_directions(X, N_, balls, drop=6.0)), mir2)
        # (the points round the eyes spread so the lifted triangles come out even)
        nb2 = rt.neighbours(len(V2), F2)
        zone = np.zeros(len(V2), bool)
        for c_, r_ in balls: zone |= np.linalg.norm((V2 - c_) / (r_ * 2.1), axis=1) < 1
        zone[b2] = False
        for _ in range(12):
            Xl = lift(V2); new = V2.copy()
            for i in np.nonzero(zone)[0]:
                s_ = nb2[i]; w_ = np.linalg.norm(Xl[s_] - Xl[i], axis=1)
                new[i] = V2[i] + 0.5 * ((w_[:, None] * V2[s_]).sum(0) / w_.sum() - V2[i])
            V2 = nearest(new, Vd, Fd)[0]; V2[b2] = new[b2]; V2 = rt.make_symmetric(V2, mir2)
        V, F = lift(V2), F2
        V[b2] = rim_to(V[b2]); V = rt.make_symmetric(V, mir2)
    e = np.concatenate([np.linalg.norm(V[F[:, a]] - V[F[:, b]], axis=1) for a, b in ((0, 1), (1, 2), (2, 0))])
    # (facing as the old hood did)
    Q, ti, bc = nearest(V, V0, F0)
    N = vertex_normals(V, F)
    old_n = (nrm0[F0[ti]] * bc[..., None]).sum(1)
    if ((N * old_n).sum(1) > 0).mean() < 0.5: F = F[:, ::-1]; N = vertex_normals(V, F)
    CLRn = (c0[F0[ti]] * bc[..., None]).sum(1)                                  # (the old shading carried over)
    CLRn = (CLRn + CLRn[mir2]) / 2                                             # (the same on both sides)
    keyset = {tuple(np.round(v, 4)) for v in V}
    asym = sum(tuple(np.round(v * [1, 1, -1], 4)) not in keyset for v in V)
    if eyes_joined:
        rep.append('hood rebuilt on Nintendo\'s layout: the template\'s %d triangles (less those over the face opening), the top split once, round the eyes %s -> %d triangles; edge length median %.2f (10%%-90%%: %.2f-%.2f); points without an exact mirror: %d' % (
            n_tpl, 'twice' if eye_split else 'once', len(F), np.median(e), np.percentile(e, 10), np.percentile(e, 90), asym))
        rep.append('eyes: balls centred at %s (and its mirror), radii %s, joined to the head (blend %.1f)' % (np.round(bc_, 2).tolist(), np.round(br_, 2).tolist(), eye_blend))
    else:
        rep.append('hood rebuilt on Nintendo\'s layout: the template\'s %d triangles as they are (less those over the face opening), nothing split -> %d triangles; edge length median %.2f (10%%-90%%: %.2f-%.2f); points without an exact mirror: %d' % (
            n_tpl, len(F), np.median(e), np.percentile(e, 10), np.percentile(e, 90), asym))

    # ---- 2. the cracks closed: the hood's opening given a thickness - a wall from its open edge inward
    # (toward the head's middle) until it is well into the face, the same all along (no jumps), seen
    # from both sides
    rest_t = T[~hood]
    rim = rt.longest_loop(F)
    RP = V[rim]
    centre = np.array([0.0, -4.5, 0.0])
    dirs = centre - RP; dirs /= np.linalg.norm(dirs, axis=1, keepdims=True)
    A_, B_, C_ = P[rest_t[:, 0]], P[rest_t[:, 1]], P[rest_t[:, 2]]
    def ray(o, dv):
        e1, e2 = B_ - A_, C_ - A_; h_ = np.cross(dv, e2); det = (e1 * h_).sum(1)
        ok = np.abs(det) > 1e-9; inv = np.where(ok, 1 / np.where(ok, det, 1), 0)
        s_ = o - A_; u = (s_ * h_).sum(1) * inv; q = np.cross(s_, e1); v = (dv * q).sum(1) * inv; t = (e2 * q).sum(1) * inv
        hit = ok & (u >= 0) & (v >= 0) & (u + v <= 1) & (t > 0)
        return t[hit].min() if hit.any() else None
    depth = []
    Qf, _, _ = nearest(RP, P, rest_t)
    for o, dv, qf in zip(RP, dirs, Qf):
        t = ray(o, dv)
        depth.append((t if t is not None else np.linalg.norm(qf - o)) + 0.35)
    depth = np.clip(np.array(depth), 0.4, 3.5)
    for _ in range(3): depth = (np.roll(depth, 1) + 2 * depth + np.roll(depth, -1)) / 4
    mate = np.linalg.norm(RP[:, None] - (RP * [1, 1, -1])[None], axis=2).argmin(1)   # (each rim point's mirror partner)
    depth = (depth + depth[mate]) / 2                                          # (the same depth on both sides)
    ends = RP + dirs * depth[:, None]
    n = len(rim)
    GP = np.vstack([RP, ends]); GT = []
    for i in range(n):
        j = (i + 1) % n
        GT += [[i, j, n + j], [i, n + j, n + i]]
    GT = np.array(GT)
    GT = np.vstack([GT, GT[:, ::-1]])                                          # (both sides)
    GN = vertex_normals(GP, GT[:len(GT) // 2])
    GP2 = np.vstack([GP, GP]); GN2 = np.vstack([GN, -GN]); GT2 = np.vstack([GT[:len(GT) // 2], GT[len(GT) // 2:] + len(GP)])
    GP, GN, GT = GP2, GN2, GT2
    rep.append('cracks: the hood\'s opening given a wall %.2f-%.2f deep (into the face) along its open edge (%d points), %d triangles, both sides' % (
        depth.min(), depth.max(), n, len(GT)))

    # ---- 2b. the eyes as their own balls (like Mario's nose): rings round a front pole facing the
    # way the user's white patches face, set into the head; the part inside the head left out
    if not eyes_joined:
        ET0 = T[eyes_t]; tri_l = P[ET0][P[ET0].mean(1)[:, 2] > 0]
        fa = np.cross(tri_l[:, 1] - tri_l[:, 0], tri_l[:, 2] - tri_l[:, 0]).sum(0); fa /= np.linalg.norm(fa)
        BV, BF = rt.ball_mesh(bc_, br_, fa, seg=eye_seg, rings=eye_rings)
        Qh, tih, bch = nearest(BV, V, F)
        Nh = (N[F[tih]] * bch[..., None]).sum(1)
        inside_ = ((BV - Qh) * Nh).sum(1) < -0.15
        BF = BF[~inside_[BF].all(1)]
        used = np.unique(BF); re_ = -np.ones(len(BV), int); re_[used] = np.arange(len(used)); BV = BV[used]; BF = re_[BF]
        BVm = BV * [1, 1, -1]; BFm = BF[:, ::-1]
        nV = len(V)
        BN = vertex_normals(BV, BF)
        BC = CLRn[nearest(BV, V, F)[1]].mean(0) if False else np.tile(np.median(CLRn, axis=0), (len(BV), 1))
        V = np.vstack([V, BV, BVm]); F = np.vstack([F, BF + nV, BFm + nV + len(BV)])
        N = np.vstack([N, BN, BN * [1, 1, -1]]); CLRn = np.vstack([CLRn, BC, BC])
        eb = np.concatenate([np.linalg.norm(BV[BF[:, a]] - BV[BF[:, b]], axis=1) for a, b in ((0, 1), (1, 2), (2, 0))])
        rep.append('eyes: two balls of their own (like Mario\'s nose), %d triangles each (the part inside the head left out), centred at %s and its mirror, radii %s, facing %s; edge length median %.2f' % (
            len(BF), np.round(bc_, 2).tolist(), np.round(br_, 2).tolist(), np.round(fa, 2).tolist(), np.median(eb)))

    # ---- 3. the frog face: eyes (the user's patch shapes) and nostrils, painted on a texture; each eye
    # projected along its own facing (on the bumps an eye faces up and out), the nostrils along the
    # snout's. Atlas: left eye top-left, right eye top-right, nostrils along the bottom.
    ET = T[eyes_t]
    PE = P.copy()                                                              # (the user's eye patches moved onto the new eye balls)
    for i in np.unique(ET):
        c_, r_ = balls[0] if P[i, 2] >= 0 else balls[1]
        u_ = (P[i] - c_) / r_; PE[i] = c_ + (P[i] - c_) / np.linalg.norm(u_)
    ecen = PE[ET].mean(1)
    headup = np.array([0.0, -1.0, 0.0])
    regions = []
    S = 256
    from PIL import ImageFilter
    def basis(dv):
        up = headup - dv * (headup @ dv)
        if np.linalg.norm(up) < 0.2: up = np.array([1.0, 0, 0]) - dv * dv[0]
        up /= np.linalg.norm(up); return up, np.cross(dv, up)
    for sgn, box in ((1, (0.0, 0.0, 1.0, 0.62)),):                            # (the left eye; the right is its mirror, below)
        sel = ecen[:, 2] * sgn > 0
        if not sel.any(): continue
        tri3 = PE[ET[sel]]
        fn_ = np.cross(tri3[:, 1] - tri3[:, 0], tri3[:, 2] - tri3[:, 0]); dv = fn_.sum(0); dv /= np.linalg.norm(dv)
        up, sd = basis(dv)
        pr2 = lambda X, up=up, sd=sd: np.c_[X @ sd, X @ up]
        q = pr2(tri3.reshape(-1, 3)); lo, hi = q.min(0) - 0.7, q.max(0) + 0.7
        regions.append({'kind': 'eye', 'sgn': sgn, 'd': dv, 'pr': pr2, 'lo': lo, 'hi': hi, 'box': box, 'tris': tri3})
        # the right eye: the left's mirror image, the same picture (so the two eyes match exactly)
        mz = np.array([1.0, 1.0, -1.0])
        regions.append({'kind': 'eye', 'sgn': -sgn, 'd': dv * mz, 'pr': (lambda X, f=pr2: f(X * mz)), 'lo': lo, 'hi': hi, 'box': box, 'tris': tri3 * mz, 'mirror': True})
    # nostrils: between the eyes, low on the snout - on the hood's surface straight in from the front
    eyes_lo = PE[ET].reshape(-1, 3)
    y_n = np.percentile(eyes_lo[:, 1], 80)                                     # (toward the eyes' lower edge; +Y is down)
    nost3 = []
    for z in (-nost_gap, nost_gap):
        o = np.array([20.0, y_n, z]); hitp = None
        Fv = V[F]; e1, e2 = Fv[:, 1] - Fv[:, 0], Fv[:, 2] - Fv[:, 0]; dv_ = np.array([-1.0, 0, 0])
        h_ = np.cross(dv_, e2); det = (e1 * h_).sum(1); ok = np.abs(det) > 1e-9; inv = np.where(ok, 1 / np.where(ok, det, 1), 0)
        s_ = o - Fv[:, 0]; u = (s_ * h_).sum(1) * inv; qq = np.cross(s_, e1); v = (dv_ * qq).sum(1) * inv; t = (e2 * qq).sum(1) * inv
        hit = ok & (u >= 0) & (v >= 0) & (u + v <= 1) & (t > 0)
        nost3.append(o + dv_ * t[hit].min())
    nost3 = np.array(nost3)
    near = np.linalg.norm(V[:, None] - nost3[None], axis=2).min(1) < 1.0
    dn = N[near].sum(0); dn /= np.linalg.norm(dn)
    upn, sdn = basis(dn)
    prn = lambda X: np.c_[X @ sdn, X @ upn]
    qn = prn(nost3); lo_n, hi_n = qn.min(0) - nost_r - 0.9, qn.max(0) + nost_r + 0.9
    regions.append({'kind': 'nose', 'd': dn, 'pr': prn, 'lo': lo_n, 'hi': hi_n, 'box': (0.0, 0.64, 1.0, 1.0), 'pts': qn})
    def to_uv(reg, X2):
        b0, b1, b2, b3 = reg['box']; lo, hi = reg['lo'], reg['hi']
        return np.c_[b0 + (X2[:, 0] - lo[0]) / (hi[0] - lo[0]) * (b2 - b0), b1 + (1 - (X2[:, 1] - lo[1]) / (hi[1] - lo[1])) * (b3 - b1)]
    SS = 4
    big = Image.new('RGB', (S * SS, S * SS), tuple(green))
    px_per_unit = []
    for reg in regions:
        if reg.get('mirror'): continue                                         # (drawn once: the right eye shares the left's picture)
        if reg['kind'] == 'eye':
            mask = Image.new('L', big.size, 0); dm = ImageDraw.Draw(mask)
            if round_eyes:                                                     # (SMB3's eyes are round: an ellipse filling the patch)
                q = reg['pr'](reg['tris'].reshape(-1, 3)); elo, ehi = q.min(0), q.max(0); c_ = (elo + ehi) / 2; r_ = (ehi - elo) / 2 * eye_fill
                a_ = to_uv(reg, np.array([[c_[0] - r_[0], c_[1] + r_[1]]]))[0] * S * SS; b_ = to_uv(reg, np.array([[c_[0] + r_[0], c_[1] - r_[1]]]))[0] * S * SS
                dm.ellipse([a_[0], a_[1], b_[0], b_[1]], fill=255)
            else:
                for tri3 in reg['tris']:
                    uv = to_uv(reg, reg['pr'](tri3)) * S * SS
                    dm.polygon([tuple(q) for q in uv], fill=255)
            ppu = (reg['box'][2] - reg['box'][0]) * S * SS / (reg['hi'][0] - reg['lo'][0]); px_per_unit.append(ppu / SS)
            ow = max(1, int(round(outline_w * ppu)))
            big.paste((25, 45, 25), mask=mask.filter(ImageFilter.MaxFilter(2 * ow + 1)))
            big.paste((246, 246, 240), mask=mask)
            q = reg['pr'](reg['tris'].reshape(-1, 3)); elo, ehi = q.min(0), q.max(0)
            cx = (elo[0] + ehi[0]) / 2; cy = elo[1] + 0.42 * (ehi[1] - elo[1])
            rx, ry = pw * (ehi[0] - elo[0]) / 2, ph_ * (ehi[1] - elo[1]) / 2
            a_ = to_uv(reg, np.array([[cx - rx, cy + ry]]))[0] * S * SS; b_ = to_uv(reg, np.array([[cx + rx, cy - ry]]))[0] * S * SS
            pupil = Image.new('L', big.size, 0); ImageDraw.Draw(pupil).ellipse([a_[0], a_[1], b_[0], b_[1]], fill=255)
            big.paste((15, 15, 15), mask=Image.fromarray(np.minimum(np.asarray(pupil), np.asarray(mask))))
        else:
            dr = ImageDraw.Draw(big)
            for c_ in reg['pts']:
                a_ = to_uv(reg, np.array([[c_[0] - nost_r * 0.8, c_[1] + nost_r]]))[0] * S * SS; b_ = to_uv(reg, np.array([[c_[0] + nost_r * 0.8, c_[1] - nost_r]]))[0] * S * SS
                dr.ellipse([a_[0], a_[1], b_[0], b_[1]], fill=(20, 50, 22))
    face_tex = big.resize((S, S), Image.LANCZOS)
    face_tex.save(os.path.join(tdir, 'frog_hood_face.png'))
    # each hood triangle under one of the pictures (facing its way, inside it, on its side) takes its UVs
    fnew = np.cross(V[F[:, 1]] - V[F[:, 0]], V[F[:, 2]] - V[F[:, 0]]); fnew /= np.linalg.norm(fnew, axis=1, keepdims=True) + 1e-12
    cen3 = V[F].mean(1)
    which = np.full(len(F), -1)
    order = [k for k, r_ in enumerate(regions) if r_['kind'] == 'nose'] + [k for k, r_ in enumerate(regions) if r_['kind'] == 'eye']
    for k in order:                                                            # (the nostrils first: the eyes' areas reach over them)
        reg = regions[k]
        c2 = reg['pr'](cen3)
        ok = (c2 >= reg['lo']).all(1) & (c2 <= reg['hi']).all(1) & (fnew @ reg['d'] > (0.12 if reg['kind'] == 'eye' else 0.3)) & (which < 0)
        if reg['kind'] == 'eye': ok &= cen3[:, 2] * reg['sgn'] > -0.2
        else:
            ok &= np.abs(cen3[:, 2]) < nost_gap + nost_r + 0.5
            c2n = reg['pr'](cen3); ok &= (c2n >= reg['pts'].min(0) - nost_r - 0.5).all(1) & (c2n <= reg['pts'].max(0) + nost_r + 0.5).all(1)
        which[ok] = k
    inside = which >= 0
    rep.append('frog face: %d texture (eyes %s, each along its own facing; nostrils %.2f across, %.2f apart, along the snout\'s facing %s) over %d hood triangles (eyes %d, %d; nostrils %d)' % (
        S, ' and '.join(str(np.round(r_['d'], 2).tolist()) for r_ in regions if r_['kind'] == 'eye'), nost_r * 2, nost_gap * 2, np.round(dn, 2).tolist(),
        inside.sum(), *[int((which == k).sum()) for k in range(len(regions))]))

    # ---- 4. the new head primitives
    phead_mat = [p['material'] for p in prims if mname(p) == 'mat_player_phead'][0]
    # a hood texel for the green parts: the old hood's UV at its most common spot
    old_uv = np.vstack([dd['uv'] for dd in data]); huv = np.median(old_uv[np.unique(T[hood & ~eyes_t])], axis=0)
    J['images'].append({'name': 'frog_hood_face', 'mimeType': 'image/png'})
    buf = io.BytesIO(); face_tex.save(buf, 'PNG'); imgs.append(buf.getvalue())
    J.setdefault('samplers', []).append({'magFilter': 9729, 'minFilter': 9729, 'wrapS': 33071, 'wrapT': 33071})
    J['textures'].append({'sampler': len(J['samplers']) - 1, 'source': len(J['images']) - 1})
    J['materials'].append({'name': 'mat_frog_face', 'pbrMetallicRoughness': {'baseColorTexture': {'index': len(J['textures']) - 1}, 'metallicFactor': 0.0, 'roughnessFactor': 0.8},
                           'alphaMode': 'MASK', 'alphaCutoff': 0.5, 'extras': {'what': 'the frog eyes and nostrils, projected over the top of the hood'}})
    face_mat = len(J['materials']) - 1

    def new_prim(pos, nrm, uv, clr, tri, mat):
        return {'attributes': {'POSITION': add_acc(J, accs, np.asarray(pos, np.float32), 'VEC3', 5126),
                               'NORMAL': add_acc(J, accs, np.asarray(nrm, np.float32), 'VEC3', 5126),
                               'TEXCOORD_0': add_acc(J, accs, np.asarray(uv, np.float32), 'VEC2', 5126),
                               'COLOR_0': add_acc(J, accs, np.asarray(np.clip(clr, 0, 1), np.float32), 'VEC4', 5126)},
                'indices': add_acc(J, accs, np.asarray(tri, np.uint32).reshape(-1, 1), 'SCALAR', 5125), 'material': mat}

    newprims = []
    # the face pieces, the forehead strip, the moustache: the old primitives without the hood's triangles
    for k, dd in enumerate(data):
        keep = (prim_of == k) & ~hood
        if not keep.any(): continue
        tri = T[keep] - off[k]
        if dd['mat'] == 'mat_player_phead':
            # my forehead strip's one flipped triangle put right (only the strip: the six at the temples
            # that disagree with their normals are in Nintendo's own Penguin head, left as they are)
            strip = np.zeros(len(T), bool)
            for pc in pcs[1:]:
                if len(pc) <= 16 and np.all(P[np.unique(T[pc])][:, 1] < -4.5): strip[pc] = True
            fn_ = np.cross(dd['pos'][tri[:, 1]] - dd['pos'][tri[:, 0]], dd['pos'][tri[:, 2]] - dd['pos'][tri[:, 0]])
            bad = ((fn_ * dd['nrm'][tri].sum(1)).sum(1) < 0) & strip[keep]
            tri[bad] = tri[bad][:, ::-1]
            if bad.any(): rep.append('forehead strip: %d triangle turned to face the way its normals do' % bad.sum())
        p = dict(dd['p']); p['indices'] = add_acc(J, accs, tri.reshape(-1, 1).astype(np.uint32), 'SCALAR', 5125)
        newprims.append(p)
    green_t = ~inside
    newprims.append(new_prim(V, N, np.tile(huv, (len(V), 1)), CLRn, F[green_t], phead_mat))
    # (the projected part: its own vertices, UVs from the projection)
    # (the projected parts: their own vertices per region, UVs from that region's projection)
    fp, fn2, fu, fc, ft = [], [], [], [], []
    for k, reg in enumerate(regions):
        tk = F[which == k]
        if not len(tk): continue
        vs = np.unique(tk); mp = {v: i + len(fp) for i, v in enumerate(vs)}
        fp += list(V[vs]); fn2 += list(N[vs]); fc += list(CLRn[vs]); fu += list(to_uv(reg, reg['pr'](V[vs])))
        ft += [[mp[v] for v in t] for t in tk]
    newprims.append(new_prim(fp, fn2, fu, fc, ft, face_mat))
    newprims.append(new_prim(GP, GN, np.tile(huv, (len(GP), 1)), np.ones((len(GP), 4)) * [0.75, 0.75, 0.75, 1], GT, phead_mat))
    mesh['primitives'] = newprims
    # (accessors no longer used are left out)
    used = set()
    for m in J['meshes']:
        for p in m['primitives']:
            used |= set(p['attributes'].values()); used.add(p['indices'])
    for s_ in J.get('skins', []):
        if 'inverseBindMatrices' in s_: used.add(s_['inverseBindMatrices'])
    for an in J.get('animations', []):
        for smp in an['samplers']: used |= {smp['input'], smp['output']}
    remap = {}; nacc = []; nJ = []
    for i, a in enumerate(J['accessors']):
        if i in used: remap[i] = len(nJ); nJ.append(a); nacc.append(accs[i])
    for m in J['meshes']:
        for p in m['primitives']:
            p['attributes'] = {k: remap[v] for k, v in p['attributes'].items()}; p['indices'] = remap[p['indices']]
            for tgt in p.get('targets', []): pass
    for s_ in J.get('skins', []):
        if 'inverseBindMatrices' in s_: s_['inverseBindMatrices'] = remap[s_['inverseBindMatrices']]
    for an in J.get('animations', []):
        for smp in an['samplers']: smp['input'] = remap[smp['input']]; smp['output'] = remap[smp['output']]
    J['accessors'] = nJ
    for idx_a in {p['indices'] for m in J['meshes'] for p in m['primitives']}:
        nacc[idx_a] = nacc[idx_a].reshape(-1)
    nacc = [a.reshape(len(a), -1) if a.ndim == 1 and J['accessors'][i]['type'] != 'SCALAR' else a for i, a in enumerate(nacc)]
    write_glb(J, nacc, imgs, dst)
    print('wrote', dst); print('\n'.join('  ' + r for r in rep))


if __name__ == '__main__':
    main()
