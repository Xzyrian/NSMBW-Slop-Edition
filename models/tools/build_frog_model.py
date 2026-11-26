"""Frog Mario base for editing: NSMBW's Super Mario with Penguin Mario's hood and flippers, NSMB2's open
hands, the trousers joined to the feet, and a green suit with a white belly circle, as one glTF (.glb).

  build_frog_model.py <NSMB2 RomFS dir> <NSMBW Mario.arc> <out_dir> [name=value ...]
  (from the project folder: python models/tools/build_frog_model.py NSMB2_RomFS extracted/files/Object/Mario.arc models/frog/Mario)

Options (defaults): toe_out=20 (degrees each foot turns toes-out), spread=0.2 (units each foot moves
out), thick=1.6 (the flippers' height, x), tuck=2.15, green=44,160,60, belly=4.0 (the circle's radius),
belly_y=14.5 (its centre height), lip=0.5 (the radius of the lip round the face's sides and bottom; 0: none),
lip_out=0.15, sole=0.8 (how far the soles are extended down; 0: not), sole_grow=0.3 (how much wider the sole slab is than
the foot, all round, top and bottom), sole_colour=242,232,160,
puff=1.0 (the NSMB2 Raccoon torso puff; 0: none), flat=1 (the suit one
plain green; flat=0: Super's shading lines kept, in green), smooth=6 (smoothing passes over the torso, which
take out the overalls' bib edge and straps modelled in the mesh; 0: none).

Parts (one object each):
  body   Super Mario's body (MB_model) without shoes, fists and the overalls' buttons, its torso puffier
         (as the Raccoon's), the bottom band of each trouser leg stretched down onto the flipper under
         it                                                          - skinned, NSMBW's 17 bones
  hands  NSMB2's open hands (its Raccoon body's handsB), fitted to the wrists as for the Raccoon
  feet   Penguin Mario's feet (PMB_model), on Super Mario's ankles, toes out, made thicker
  head   Penguin Mario's head (PMH_model) without the beak, at face_1
Textures (new files; the game's own are not changed): frog_body (Super's, green except the white
gloves), frog_belly (the torso's front, mapped flat from the front, with the white circle), frog_feet (the penguin feet, green), frog_head
(the hood green; face, hair and moustache as they are), player_eye.0-6 (the eyes, unchanged).
"""
import os, sys, colorsys
import numpy as np
from PIL import Image
HERE = os.path.dirname(os.path.abspath(__file__))
for d in (HERE, os.path.join(HERE, '..', '..', 'recomp', 'tools'), os.path.join(HERE, '..', '..', 'SMB3Disassembly', 'tools')):
    sys.path.insert(0, os.path.normpath(d))
import brres_read as br
from export_player_models import Glb, trs, build_prims, WRAP
from nsmb2_mesh import N2Model
import build_raccoon_models as rb


def hom(P): return np.c_[P, np.ones(len(P))]


def sample(tex, uv):
    h, w = tex.shape[:2]; uv = uv % 1.0
    return tex[np.clip((uv[..., 1] * h).astype(int), 0, h - 1), np.clip((uv[..., 0] * w).astype(int), 0, w - 1)]


# ---------------------------------------------------------------- colours
def classify(rgb):
    """per pixel: 'white' (gloves), 'skin', 'dark' (hair, moustache, black), or 'colour'"""
    f = rgb.astype(float) / 255
    hsv = np.array([colorsys.rgb_to_hsv(*p) for p in f.reshape(-1, 3)]).reshape(f.shape)
    h, s, v = hsv[..., 0] * 360, hsv[..., 1], hsv[..., 2]
    cls = np.full(rgb.shape[:2], 'colour', object)
    cls[(s < 0.2) & (v > 0.55)] = 'white'
    cls[(h >= 5) & (h <= 40) & (s > 0.15) & (s < 0.62) & (v > 0.55)] = 'skin'
    cls[v < 0.22] = 'dark'
    return cls, h, s, v


def recolour(rgba, mask, green):
    """the masked pixels made green, keeping their shading (each colour group's brightness around its median)"""
    out = rgba.copy()
    _, h, s, v = classify(rgba[..., :3])
    group = np.round(h / 30).astype(int) % 12
    for gi in np.unique(group[mask]):
        m = mask & (group == gi)
        ref = np.median(v[m])
        shade = np.clip(v[m] / max(ref, 1e-3), 0.35, 1.5)
        out[..., :3][m] = np.clip(np.array(green)[None, :] * shade[:, None], 0, 255).astype(np.uint8)
    return out


def raster_uv(tex_shape, uv3, ss=3, wrap=True):
    """texels covered by a UV triangle (3 x 2): yields (y, x, barycentric weights per subsample: n x 3, inside mask)
    wrap: UVs taken modulo 1 (a repeating texture); else texels outside the texture are skipped"""
    h, w = tex_shape[:2]
    if wrap:
        base = np.floor(uv3.min(0))
        P = (uv3 - base) * [w, h]
    else:
        P = uv3 * [w, h]
    x0, x1 = int(np.floor(P[:, 0].min())), int(np.ceil(P[:, 0].max()))
    y0, y1 = int(np.floor(P[:, 1].min())), int(np.ceil(P[:, 1].max()))
    (ax, ay), (bx, by), (cx, cy) = P
    den = (by - cy) * (ax - cx) + (cx - bx) * (ay - cy)
    if abs(den) < 1e-12: return
    o = (np.arange(ss) + 0.5) / ss
    for y in range(y0, y1):
        for x in range(x0, x1):
            sx, sy = np.meshgrid(x + o, y + o); sx, sy = sx.ravel(), sy.ravel()
            l1 = ((by - cy) * (sx - cx) + (cx - bx) * (sy - cy)) / den
            l2 = ((cy - ay) * (sx - cx) + (ax - cx) * (sy - cy)) / den
            l3 = 1 - l1 - l2
            ins = (l1 >= 0) & (l2 >= 0) & (l3 >= 0)
            if not ins.any(): continue
            if wrap: yield y % h, x % w, np.c_[l1, l2, l3], ins
            elif 0 <= y < h and 0 <= x < w: yield y, x, np.c_[l1, l2, l3], ins


def face_lip(D, t3, hood, huv, r, out_off, seg=2, ring=8):
    """a thicker lip round the sides and bottom of the face: a tube of radius r along the face's outline
    as seen from the front (where the face meets the hood: cheeks, sideburns, jaw, chin), from one end
    of the forehead strip round under the chin to the other, a little out from the face, its ends
    tapering. D: the head's vertices (head space: +X forward, -Y up), t3: its triangles, hood: which
    triangles are hood (not face). -> (vertex arrays, indices, report)"""
    P = D['pos']
    fv = np.unique(t3[~hood])
    fv = fv[P[fv, 0] > 0.5]                                                    # (the face's front half)
    zy0 = np.array([0.0, -4.0])                                               # (the face's middle, seen from the front: z, y)
    # the forehead strip's ends: the hood's edge corners in front, top
    hv = np.unique(t3[hood]); top = hv[(P[hv, 0] > 2.5) & (P[hv, 1] < -6.0)]
    end_ang = np.degrees(np.arctan2(np.abs(P[top, 2]).max(), -(P[top[np.argmax(np.abs(P[top, 2]))], 1] - zy0[1])))
    rel = np.c_[P[fv, 2] - zy0[0], P[fv, 1] - zy0[1]]
    ang = np.degrees(np.arctan2(rel[:, 0], -rel[:, 1])) % 360                # (0: straight up, 90: +z side, 180: down)
    rad = np.linalg.norm(rel, axis=1)
    path = []
    for a in np.linspace(end_ang, 360 - end_ang, 33):
        d = (ang - a + 180) % 360 - 180
        sel = np.abs(d) < 6
        if not sel.any(): continue
        path.append(P[fv[sel][np.argmax(rad[sel])]])
    path = np.array(path)
    # the outline's depth: the face's front surface there (seen from the front, the outline under the
    # chin is the jaw's underside, further back toward the neck: the lip follows the chin's front edge)
    # (only round the bottom: the sides stay at the outline itself, outside the sideburns - eased in
    # from 125 degrees off straight up to the chin at 180)
    proj = np.c_[P[fv, 2], P[fv, 1]]
    for i, q in enumerate(path):
        a_ = abs((np.degrees(np.arctan2(q[2] - zy0[0], -(q[1] - zy0[1]))) % 360) - 180)   # (0: straight down)
        w_ = np.clip((55 - a_) / 30, 0, 1)
        near = np.linalg.norm(proj - [q[2], q[1]], axis=1) < 1.2
        if near.any() and w_ > 0: path[i, 0] = (1 - w_) * q[0] + w_ * P[fv[near], 0].max()
    for _ in range(3):                                                        # (smoothed: the outline is jagged)
        path[1:-1] = (path[:-2] + 2 * path[1:-1] + path[2:]) / 4
    # (out from the face: pushed outward in the front view)
    rel = np.c_[path[:, 2] - zy0[0], path[:, 1] - zy0[1]]
    rel /= np.linalg.norm(rel, axis=1, keepdims=True)
    path[:, 2] += rel[:, 0] * out_off; path[:, 1] += rel[:, 1] * out_off
    # smoothed (Catmull-Rom), seg points a span
    G = np.vstack([path[0] * 2 - path[1], path, path[-1] * 2 - path[-2]])
    C = []
    for i in range(1, len(G) - 2):
        p0, p1, p2, p3 = G[i - 1], G[i], G[i + 1], G[i + 2]
        for t in np.linspace(0, 1, seg, endpoint=False):
            C.append(0.5 * ((2 * p1) + (-p0 + p2) * t + (2 * p0 - 5 * p1 + 4 * p2 - p3) * t * t + (-p0 + 3 * p1 - 3 * p2 + p3) * t ** 3))
    C.append(path[-1]); C = np.array(C)
    centre = np.array([0.0, -4.5, 0.0])                                       # (the head's middle, roughly)
    V = {'pos': [], 'nrm': [], 'uv': [], 'clr': []}; I = []
    n = len(C)
    for i in range(n):
        tng = C[min(i + 1, n - 1)] - C[max(i - 1, 0)]; tng /= np.linalg.norm(tng)
        f = C[i] - centre; f -= tng * (f @ tng); f /= np.linalg.norm(f)
        side = np.cross(tng, f)
        u = i / (n - 1); taper = min(1.0, min(u, 1 - u) / 0.08)                # (the ends tapered)
        rr = r * np.sqrt(max(taper, 0.0))
        c_ = C[i]
        for k in range(ring):
            a = 2 * np.pi * k / ring
            d = np.cos(a) * f + np.sin(a) * side
            V['pos'].append(c_ + d * rr); V['nrm'].append(d); V['uv'].append(huv); V['clr'].append([1.0, 1.0, 1.0, 1.0])
    for i in range(n - 1):
        for k in range(ring):
            a0, a1 = i * ring + k, i * ring + (k + 1) % ring
            b0, b1 = a0 + ring, a1 + ring
            I += [a0, b0, b1, a0, b1, a1]
    V = {k_: np.array(v, float) for k_, v in V.items()}; I = np.array(I, np.uint32)
    t_ = I.reshape(-1, 3); fn = np.cross(V['pos'][t_[:, 1]] - V['pos'][t_[:, 0]], V['pos'][t_[:, 2]] - V['pos'][t_[:, 0]])
    ok = np.linalg.norm(fn, axis=1) > 1e-10
    if ((fn[ok] * V['nrm'][t_[ok, 0]]).sum(1) > 0).mean() < 0.5: I = t_[:, ::-1].reshape(-1)
    return V, I, 'head: a lip round the sides and bottom of the face: a tube of radius %.2f along the face\'s outline (%d points, smoothed to %d), %.2f out, %d triangles' % (
        r, len(path), n, out_off, len(I) // 3)


def main():
    romfs, arc, out = sys.argv[1:4]
    opt = dict(a.split('=', 1) for a in sys.argv[4:])
    toe_out, spread, thick = float(opt.get('toe_out', 20)), float(opt.get('spread', 0.2)), float(opt.get('thick', 1.6))
    green = [int(x) for x in opt.get('green', '44,160,60').split(',')]
    belly_r, belly_y = float(opt.get('belly', 4.0)), float(opt.get('belly_y', 14.5))
    tuck_r = float(opt.get('tuck', 2.15))
    sole_e = float(opt.get('sole', 0.8))
    lip_r, lip_out = float(opt.get('lip', 0.9)), float(opt.get('lip_out', 0.45))
    sole_grow = float(opt.get('sole_grow', 0.3))
    sole_rgb = [int(x) for x in opt.get('sole_colour', '242,232,160').split(',')]
    puff = float(opt.get('puff', 1.0))
    flat = opt.get('flat', '1') != '0'
    smooth = int(opt.get('smooth', 6))
    os.makedirs(os.path.join(out, 'textures'), exist_ok=True)
    B = br.Brres(arc); ms = B.models(); texs = B.textures()
    mb, pb, ph = ms['MB_model'], ms['PMB_model'], ms['PMH_model']
    names = [b.name for b in mb.bones]; bw = {b.name: b.world for b in mb.bones}
    assert names == [b.name for b in pb.bones]
    report = []
    ankles = {names.index('ankle_l1'): +1, names.index('ankle_r1'): -1}
    wrists = [names.index('wrist_l1'), names.index('wrist_r1')]
    tex_body0 = texs['player_body.0'].decode()

    # ---- Super body: shoes and fists off
    (mi, A, idx, _), = build_prims(mb, True, {b.index: b.index for b in mb.bones})
    A = {k: np.array(v) for k, v in A.items()}
    tri = idx.reshape(-1, 3)
    col = sample(tex_body0, A['uv'][tri].mean(1))[:, :3].astype(int)
    on_ankle = np.isin(A['j'][:, 0], list(ankles))[tri].all(1)
    shoe = on_ankle & ~(col[:, 2] > col[:, 0] + 20)                   # (the trousers' bottom band is on the ankle bones too: kept)
    hand_tri = np.isin(A['j'][:, 0], wrists)[tri].all(1)
    keep = ~shoe & ~hand_tri
    # the overalls' separate pieces (the two buttons): every small loose piece of the body
    key0 = [tuple(np.round(p, 3)) for p in A['pos']]
    par = {}
    def find(a):
        while par.setdefault(a, a) != a: par[a] = par[par[a]]; a = par[a]
        return a
    for t in tri:
        r0 = find(key0[t[0]])
        for v in t[1:]: par[find(key0[v])] = r0
    pieces = {}
    for n_, t in enumerate(tri): pieces.setdefault(find(key0[t[0]]), []).append(n_)
    loose = [ii for ii in pieces.values() if len(ii) < 30]
    for ii in loose: keep[ii] = False
    report.append('body: %d triangles kept; shoes (%d), fists (%d) and the overalls\' buttons (%d loose pieces, %d triangles) off' % (
        keep.sum(), shoe.sum(), hand_tri.sum(), len(loose), sum(len(ii) for ii in loose)))
    # the torso puffier, as NSMB2's Raccoon body is (puff_torso.py, as on the Raccoon models)
    if puff:
        import puff_torso
        n2n = N2Model(os.path.join(romfs, 'Model', 'Player', 'Mario.bcres'), 'mr_normal')
        n2r = N2Model(os.path.join(romfs, 'Model', 'Player', 'Mario.bcres'), 'mr_tail_body')
        field = puff_torso.nsmb2_push(n2n.shape(0), n2r.shape(0))
        report.append('body: ' + puff_torso.puff_body(A, tri, names, field, strength=puff))
    if smooth:                                                                # (the overalls' bib edge and straps are ridges in the mesh)
        import puff_torso
        report.append('body: ' + puff_torso.smooth_region(A, tri[keep | shoe | hand_tri], names, iters=smooth))

    # ---- NSMB2's open hands
    n2 = N2Model(os.path.join(romfs, 'Model', 'Player', 'Mario.bcres'), 'mr_tail_body')
    n2w = {n: n2.world[i] for i, (n, _) in enumerate(n2.bones)}
    HB, hB_idx = rb.open_hands(n2, n2w, A, tri, hand_tri, names, bw, tex_body0, report)

    # ---- Penguin feet on Super's ankles: toes out, a little apart, flippers thicker
    (pmi, PA, pidx, _), = build_prims(pb, True, {b.index: b.index for b in pb.bones})
    ptri = pidx.reshape(-1, 3)
    pfoot = np.isin(PA['j'][:, 0], list(ankles))[ptri].all(1)
    fv = np.unique(ptri[pfoot]); fmap = {v: i for i, v in enumerate(fv)}
    F = {'pos': np.zeros((len(fv), 3)), 'nrm': np.zeros((len(fv), 3)), 'uv': PA['uv'][fv], 'clr': PA['clr'][fv], 'j': PA['j'][fv], 'w': PA['w'][fv]}
    for k, v in enumerate(fv):
        b = PA['j'][v, 0]
        M = bw[names[b]] @ np.linalg.inv(pb.bones[b].world)                 # Penguin's ankle -> Super's ankle
        a = np.radians(toe_out) * ankles[b]; c = bw[names[b]][:3, 3]
        T = np.eye(4); T[:3, :3] = [[np.cos(a), 0, np.sin(a)], [0, 1, 0], [-np.sin(a), 0, np.cos(a)]]
        T[:3, 3] = c - T[:3, :3] @ c; T[0, 3] += ankles[b] * spread
        M = T @ M
        F['pos'][k] = (M @ np.append(PA['pos'][v], 1))[:3]; F['nrm'][k] = M[:3, :3] @ PA['nrm'][v]
    f_idx = np.array([fmap[v] for v in ptri[pfoot].reshape(-1)], np.uint32)
    lift = -F['pos'][:, 1].min()                                             # (Super's ankles are 0.11 lower: soles back on the ground)
    F['pos'][:, 1] += lift
    tex_feet0 = texs['player_pbody'].decode()
    fcol = sample(tex_feet0, F['uv'][f_idx.reshape(-1, 3)].mean(1))[:, :3].astype(int)
    flipper_tri = (fcol[:, 0] > 200) & (fcol[:, 1] > 100) & (fcol[:, 2] < 80)     # (orange)
    top = F['pos'][np.unique(f_idx.reshape(-1, 3)[flipper_tri])][:, 1].max()    # the flippers' top; above it the leg stubs
    y = F['pos'][:, 1]; low = y <= top
    F['pos'][:, 1] = np.where(low, y * thick, y + top * (thick - 1))
    F['nrm'][low, 1] /= thick
    # the sole extended: the flat bottom (its triangles all on the ground) pushed down by sole_e - the
    # whole foot raised by sole_e, and a band of new wall from the sole's edge down to a new sole on the
    # ground. Band and sole get their own vertices (pale yellow, set with the textures below).
    sole_v = []
    if sole_e > 0:
        ft_ = f_idx.reshape(-1, 3)
        on_ground = (F['pos'][ft_][:, :, 1] < 0.05).all(1)
        F['pos'][:, 1] += sole_e
        edge_n = {}
        for t in ft_[on_ground]:
            for a_, b_ in ((t[0], t[1]), (t[1], t[2]), (t[2], t[0])):
                k_ = frozenset((tuple(np.round(F['pos'][a_], 3)), tuple(np.round(F['pos'][b_], 3))))
                edge_n.setdefault(k_, []).append((a_, b_))
        rim = [v[0] for v in edge_n.values() if len(v) == 1]
        new = {k_: [] for k_ in F}
        def addv(src, pos, nrm):
            for k_ in F: new[k_].append(F[k_][src].copy())
            new['pos'][-1] = pos; new['nrm'][-1] = nrm
            sole_v.append(len(F['pos']) + len(new['pos']) - 1); return sole_v[-1]
        # the sole's footprint a little bigger than the foot: its edge pushed out by sole_grow from the
        # middle of that foot's sole
        gv = np.unique(ft_[on_ground]); scen = {b_: F['pos'][gv[F['j'][gv, 0] == b_]].mean(0) for b_ in ankles}
        def wider(v, down):
            q = F['pos'][v] - [0, down, 0]; c_ = scen[F['j'][v, 0]]
            d_ = q - c_; d_[1] = 0; d_ /= np.linalg.norm(d_) + 1e-9
            return q + d_ * sole_grow
        low = lambda v: wider(v, sole_e)
        # the new sole: the bottom triangles moved onto copies of their vertices, on the ground
        smap = {}
        for t in ft_[on_ground]:
            for v in t:
                if v not in smap: smap[v] = addv(v, low(v), np.array([0, -1.0, 0]))
        ft_new = ft_.copy()
        for n_ in np.nonzero(on_ground)[0]: ft_new[n_] = [smap[v] for v in ft_[n_]]
        # the band, a slab wider than the foot top and bottom: for each edge of the sole's rim a straight
        # wall (out by sole_grow) from the ground up to the old rim's height, and a ledge on top from the
        # wall back in to the foot's old rim
        band = []; ledge = []
        for b_ in ankles:
            cen = F['pos'][F['j'][:, 0] == b_].mean(0)
            for a_, c_ in rim:
                if F['j'][a_, 0] != b_: continue
                out_ = (F['pos'][a_] + F['pos'][c_]) / 2 - cen; out_[1] = 0; out_ /= np.linalg.norm(out_) + 1e-9
                lo_a = addv(a_, low(a_), out_); lo_c = addv(c_, low(c_), out_)
                up_a = addv(a_, wider(a_, 0), out_); up_c = addv(c_, wider(c_, 0), out_)
                band += [[lo_a, lo_c, up_c], [lo_a, up_c, up_a]]
                upn = np.array([0, 1.0, 0])
                la = addv(a_, wider(a_, 0), upn); lc = addv(c_, wider(c_, 0), upn)
                ia = addv(a_, F['pos'][a_].copy(), upn); ic = addv(c_, F['pos'][c_].copy(), upn)
                ledge += [[ia, ic, lc], [ia, lc, la]]
        n_old = len(F['pos'])
        for k_ in F: F[k_] = np.concatenate([F[k_], np.array(new[k_])])
        # (the sole's own shading: light, a little darker underneath - the foot's ground-level shading
        # is dark and would turn the pale yellow brown)
        F['clr'][sole_v, :3] = np.where(F['nrm'][sole_v, 1:2] < -0.5, 0.8, np.where(F['nrm'][sole_v, 1:2] > 0.5, 1.0, 0.95))
        # (the walls shaded smoothly round the foot: each wall point's normal the average of its walls')
        wv = np.unique(np.array(band, np.int64))
        acc_ = {}
        for v in wv: acc_.setdefault(tuple(np.round(F['pos'][v], 3)), []).append(v)
        for vs in acc_.values():
            n_ = F['nrm'][vs].mean(0); n_ /= np.linalg.norm(n_) + 1e-9
            F['nrm'][vs] = n_
        band = np.array(band + ledge, np.int64)
        # (each facing the way its normals point: the walls out, the ledge up)
        fn = np.cross(F['pos'][band[:, 1]] - F['pos'][band[:, 0]], F['pos'][band[:, 2]] - F['pos'][band[:, 0]])
        flip = (fn * F['nrm'][band[:, 0]]).sum(1) < 0
        band[flip] = band[flip][:, ::-1]
        f_idx = np.concatenate([ft_new.reshape(-1), band.reshape(-1)]).astype(np.uint32)
        report.append('feet: soles extended down by %.2f (the feet raised as much), a slab %.2f wider than the foot all round: %d rim edges, walls %d and ledge %d triangles, a new sole of %d, pale yellow' % (
            sole_e, sole_grow, len(rim), len(band) - len(ledge), len(ledge), int(on_ground.sum())))
    # the foot's top above the flippers (the leg stub, and the heel's rim, which is wider than Super's
    # trouser legs) pulled in to stay inside the trousers
    tucked = 0
    for b, sgn in ankles.items():
        c = bw[names[b]][:3, 3]
        sel = (F['j'][:, 0] == b) & (F['pos'][:, 1] > top * thick + sole_e - 0.3)
        d = F['pos'][sel][:, [0, 2]] - c[[0, 2]]; r_ = np.linalg.norm(d, axis=1)
        k = np.minimum(1.0, tuck_r / np.maximum(r_, 1e-6))
        P_ = F['pos'][sel]; P_[:, [0, 2]] = c[[0, 2]] + d * k[:, None]; F['pos'][sel] = P_
        tucked += int((k < 1).sum())
    report.append('feet: %d points above the flippers pulled in to %.2f of the leg\'s middle (inside the trousers)' % (tucked, tuck_r))
    report.append('feet: %d triangles; toes out %.0f deg, %.2f apart each, lifted %.2f to the ground; flippers %.2f -> %.2f high (x%.2f), the leg stubs raised with them' % (
        len(f_idx) // 3, toe_out, spread, lift, top, top * thick, thick))

    # ---- the trousers joined to the feet. The trouser legs end in a band on the ankle bones (the shoe
    # covered its lower edge); that band is stretched down onto the flipper under it: each point's
    # target is the feet's surface straight below it (sunk in a little); the band's lower 70% goes all
    # the way, its top (where it meets the shin) stays, the points between go part of the way.
    ft = f_idx.reshape(-1, 3)
    FA, FB, FC = F['pos'][ft[:, 0]], F['pos'][ft[:, 1]], F['pos'][ft[:, 2]]

    def drop(p):
        """the highest point of the feet straight below p (a vertical ray down), or None"""
        e1, e2 = FB - FA, FC - FA
        d = np.array([0, -1.0, 0])
        h_ = np.cross(d, e2); det = (e1 * h_).sum(1)
        ok = np.abs(det) > 1e-9
        inv = np.where(ok, 1 / np.where(ok, det, 1), 0)
        s_ = p - FA; u = (s_ * h_).sum(1) * inv
        q = np.cross(s_, e1); v = (d * q).sum(1) * inv; t = (e2 * q).sum(1) * inv
        hit = ok & (u >= 0) & (v >= 0) & (u + v <= 1) & (t > -50)
        return p[1] - t[hit].min() if hit.any() else None
    sink = 0.08
    band_t = on_ankle & ~shoe
    key = [tuple(np.round(p, 4)) for p in A['pos']]
    bv = np.unique(tri[band_t])
    moved = {}; misses = 0; drops = []
    for side in ankles:
        vs = [v for v in bv if A['j'][v, 0] == side]
        ys = A['pos'][vs, 1]; y_top, y_min = ys.max(), ys.min()
        c = bw[names[side]][:3, 3]
        for v in vs:
            k_ = key[v]
            if k_ in moved: continue
            p = A['pos'][v].copy()
            target = None
            for f in np.linspace(1, 0, 11):                                       # (nothing below: look nearer the leg's middle)
                q = p.copy(); q[[0, 2]] = c[[0, 2]] + (p[[0, 2]] - c[[0, 2]]) * f
                target = drop(q)
                if target is not None: break
            if target is None: misses += 1; continue
            target -= sink
            t = np.clip((y_top - p[1]) / max(0.3 * (y_top - y_min), 1e-6), 0, 1)       # (the band's lower 70% all the way down)
            if target < p[1]:
                moved[k_] = p[1] + t * (target - p[1]); drops.append(p[1] - moved[k_])
    for i, k_ in enumerate(key):
        if k_ in moved: A['pos'][i, 1] = moved[k_]
    report.append('trousers to feet: %d points of the trouser bands stretched down onto the flippers (by up to %.2f)%s' % (
        len(moved), max(drops) if drops else 0, ', %d with no foot under them' % misses if misses else ''))
    band_idx = np.zeros(0, np.uint32); band = None

    # ---- the head without the beak
    tex_head0 = texs['player_phead'].decode()
    hprims = []
    allh = build_prims(ph, False, {0: 0})
    eye_pos = np.vstack([D['pos'] for m_, D, ix, on in allh if ph.mats[m_]['name'] == 'mat_player_eye'])
    for m_, D, ix, on in allh:
        if ph.mats[m_]['name'] == 'mat_player_phead':
            t3 = ix.reshape(-1, 3)
            c3 = sample(tex_head0, D['uv'][t3].mean(1))[:, :3].astype(int)
            beak = (c3[:, 0] > 200) & (c3[:, 1] > 100) & (c3[:, 2] < 30)      # (pure orange: the beak; the darker skin by the ears is not)
            t3, c3 = t3[~beak], c3[~beak]
            ix = t3.reshape(-1)
            report.append('head: beak off (%d triangles), %d left' % (beak.sum(), len(ix) // 3))
            # the beak covered the forehead between the hood's front edge and the eyebrows (the eye
            # piece): a strip of hood closes it, from each point of that edge down to the top of the
            # eyebrows below it (or the face's edge at the sides), tucked just under them
            P = D['pos']; key = [tuple(np.round(q, 3)) for q in P]
            from collections import Counter
            ec = Counter()
            for t in t3:
                for a_, b_ in ((t[0], t[1]), (t[1], t[2]), (t[2], t[0])): ec[frozenset((key[a_], key[b_]))] += 1
            bpts = {k for e, n in ec.items() if n == 1 for k in e}
            hood_v = {}
            for t, cc in zip(t3, c3):
                for v in t: hood_v.setdefault(key[v], []).append(cc[2] > cc[0])
            first = {}
            for i, k_ in enumerate(key): first.setdefault(k_, i)
            rim = sorted([k_ for k_ in bpts if all(hood_v.get(k_, [False])) and k_[0] > 2.5 and k_[1] < -6.0], key=lambda q: q[2])
            skin_edge = np.array([k_ for k_ in bpts if not all(hood_v.get(k_, [True])) and k_[0] > 2.0 and k_[1] < -4.5] or [[0, 0, 0]])
            low = []
            for r in rim:
                cand = np.vstack([eye_pos, skin_edge])
                cand = cand[(np.abs(cand[:, 2] - r[2]) < 0.9) & (cand[:, 1] > r[1])]
                q = cand[np.argmin(cand[:, 1])] if len(cand) else np.array(r) + [0, 2.0, 0]
                low.append(q + [-0.15, 0.15, 0])                                   # (tucked under the brows)
            hood_tri = t3[c3[:, 2] > c3[:, 0]][0]
            huv = D['uv'][hood_tri].mean(0)
            S = {'pos': [], 'nrm': [], 'uv': [], 'clr': []}; s_idx = []
            for r, q in zip(rim, low):
                v = first[r]
                for pos in (np.array(r), q):
                    S['pos'].append(pos); S['nrm'].append(D['nrm'][v]); S['uv'].append(huv); S['clr'].append(D['clr'][v])
            for i in range(len(rim) - 1):
                a0, a1, b0, b1 = 2 * i, 2 * i + 1, 2 * i + 2, 2 * i + 3
                s_idx += [a0, a1, b1, a0, b1, b0]
            S = {k: np.array(v, float) for k, v in S.items()}; s_idx = np.array(s_idx, np.uint32)
            # (facing forward, out of the face opening: head space +X is forward; it hangs under the
            # hood's edge like the beak did, so it faces forward and a little down)
            tt = s_idx.reshape(-1, 3); fn = np.cross(S['pos'][tt[:, 1]] - S['pos'][tt[:, 0]], S['pos'][tt[:, 2]] - S['pos'][tt[:, 0]])
            if (fn[:, 0] > 0).mean() < 0.5: s_idx = tt[:, ::-1].reshape(-1)
            fn = np.cross(S['pos'][s_idx.reshape(-1, 3)[:, 1]] - S['pos'][s_idx.reshape(-1, 3)[:, 0]], S['pos'][s_idx.reshape(-1, 3)[:, 2]] - S['pos'][s_idx.reshape(-1, 3)[:, 0]])
            S['nrm'] = np.zeros_like(S['pos'])
            for t, f in zip(s_idx.reshape(-1, 3), fn):
                for v in t: S['nrm'][v] += f
            report.append('head: forehead closed with a strip of hood (%d triangles) from the hood\'s edge (%d points) to the eyebrows' % (len(s_idx) // 3, len(rim)))
            hprims.append((m_, S, s_idx))
            if lip_r > 0:
                Lp, Li, rep_ = face_lip(D, t3, c3[:, 2] > c3[:, 0], huv, lip_r, lip_out)
                report.append(rep_); hprims.append((m_, Lp, Li))
        hprims.append((m_, D, ix))

    # ---- textures
    # body: Super's, 256 x 256, green but for the skin and the white (gloves); then the belly circle
    big = tex_body0.copy()
    # (kept: the gloves - the texels under the triangles that are glove-white, fists and cuffs; all else green)
    wc = classify(col[None, :, :].astype(np.uint8))[0][0]
    glove = np.zeros(big.shape[:2], bool)
    for t in tri[wc == 'white']:
        for yy, xx, L, ins in raster_uv(big.shape, A['uv'][t], ss=2): glove[yy, xx] = True
    for _ in range(2):
        pad = np.pad(glove, 1); glove = np.any([pad[1 + dy:pad.shape[0] - 1 + dy, 1 + dx:pad.shape[1] - 1 + dx] for dy in (-1, 0, 1) for dx in (-1, 0, 1)], axis=0)
    hs = big.shape[0]
    hu = np.array([int(HB['uv'][0][1] * hs), int(HB['uv'][0][0] * hs)])               # (the open hands' texel)
    assert glove[hu[0] % hs, hu[1] % hs]
    if flat:                                                                  # (one plain green: no trace of the overalls' seams, straps or pockets)
        fb = big.copy(); fb[..., :3][~glove] = green; fb[..., 3][~glove] = 255
    else:
        fb = recolour(big, ~glove, green)
    report.append('body texture: %d of %d texels kept as glove, the rest green' % (glove.sum(), glove.size))
    # triangles other than the gloves' that also read the glove's white texels (bits of the bib, the
    # waist hooks, the sleeve ends): given their own vertices on a plain green texel instead
    stray = []
    for n_, t in enumerate(tri):
        if not keep[n_] or wc[n_] == 'white': continue
        hits = tot = 0
        for yy, xx, L, ins in raster_uv(big.shape, A['uv'][t], ss=2):
            tot += 1; hits += glove[yy, xx]
        if tot == 0:
            u = (A['uv'][t].mean(0) % 1.0) * hs; hits, tot = int(glove[int(u[1]) % hs, int(u[0]) % hs]), 1
        if hits / tot > 0.25: stray.append(n_)
    back = [n_ for n_, t in enumerate(tri) if keep[n_] and np.isin(A['j'][t, 0], [names.index('spin')]).all() and A['nrm'][t][:, 2].mean() < -0.6]
    gu = None
    for n_ in back:
        u = A['uv'][tri[n_]].mean(0) % 1.0; yx = (int(u[1] * hs), int(u[0] * hs))
        if not glove[max(0, yx[0] - 3):yx[0] + 4, max(0, yx[1] - 3):yx[1] + 4].any(): gu = u; break
    if stray and gu is not None:
        for n_ in stray:
            for c_ in range(3):
                v = tri[n_, c_]
                for k_ in A: A[k_] = np.concatenate([A[k_], A[k_][v:v + 1]])
                A['uv'][-1] = gu; tri[n_, c_] = len(A['pos']) - 1
    if stray: report.append('%d stray triangles moved off the glove texels to a plain green one' % len(stray))
    # the belly: the torso's front gets its own texture (frog_belly, 128 x 128), mapped flat from the
    # front, so the circle is round and touches nothing else (Super's texture reuses the belly's
    # texels on the waist's sides and the back of the neck). Its picture: the green suit as the
    # triangles had it (copied through their old UVs), then the white circle.
    torso = [names.index(n) for n in ('spin', 'skl_root', 'leg_l1', 'leg_r1')]
    half = belly_r + 1.2
    cen = A['pos'][tri].mean(1); fz = A['nrm'][tri][:, :, 2].mean(1)
    belly = keep & np.isin(A['j'][tri][:, :, 0], torso).all(1) & (fz > 0.2) & (np.abs(cen[:, 0]) < half) & (np.abs(cen[:, 1] - belly_y) < half)
    BS = 128
    btex = np.zeros((BS, BS, 4), np.uint8); bcov = np.zeros((BS, BS)); have = np.zeros((BS, BS), bool)
    B_ = {k: [] for k in A}; b_idx = []
    for n_ in np.nonzero(belly)[0]:
        t = tri[n_]; P3 = A['pos'][t]
        new_uv = np.c_[(P3[:, 0] + half) / (2 * half), 1 - (P3[:, 1] - (belly_y - half)) / (2 * half)]
        for c_ in range(3):
            for k_ in A: B_[k_].append(A[k_][t[c_]])
            B_['uv'][-1] = new_uv[c_]; b_idx.append(len(B_['pos']) - 1)
        old_uv = A['uv'][t]
        for yy, xx, L, ins in raster_uv(btex.shape, new_uv, ss=3, wrap=False):
            ou = (L[ins] @ old_uv).mean(0)
            btex[yy, xx] = list(green) + [255] if flat else sample(fb, ou[None])[0]; have[yy, xx] = True
    for _ in range(4):                                                         # (the gutter: from its neighbours)
        pad = np.pad(btex.astype(int), ((1, 1), (1, 1), (0, 0))); hp = np.pad(have, 1)
        acc_ = np.zeros(btex.shape, int); cnt = np.zeros(have.shape, int)
        for dy in (-1, 0, 1):
            for dx in (-1, 0, 1):
                m = hp[1 + dy:hp.shape[0] - 1 + dy, 1 + dx:hp.shape[1] - 1 + dx]
                acc_ += pad[1 + dy:pad.shape[0] - 1 + dy, 1 + dx:pad.shape[1] - 1 + dx] * m[..., None]; cnt += m
        fill = ~have & (cnt > 0)
        btex[fill] = (acc_[fill] / cnt[fill][:, None]).astype(np.uint8); have |= fill
    # the circle, antialiased: its distance from the centre in the front view
    o = (np.arange(4) + 0.5) / 4
    yy, xx = np.mgrid[0:BS, 0:BS]
    for dy in o:
        for dx in o:
            X = (xx + dx) / BS * 2 * half - half; Y = (belly_y - half) + (1 - (yy + dy) / BS) * 2 * half
            bcov += (X ** 2 + (Y - belly_y) ** 2 < belly_r ** 2) / 16
    white = np.array([246, 246, 240])
    btex[..., :3] = (btex[..., :3] * (1 - bcov[..., None]) + white * bcov[..., None]).astype(np.uint8); btex[..., 3] = 255
    Image.fromarray(btex, 'RGBA').save(os.path.join(out, 'textures', 'frog_belly.png'))
    B_ = {k: np.array(v) for k, v in B_.items()}; b_idx = np.array(b_idx, np.uint32)
    keep = keep & ~belly
    report.append('belly: %d front triangles on their own texture (frog_belly), white circle radius %.1f at height %.1f' % (belly.sum(), belly_r, belly_y))
    Image.fromarray(fb, 'RGBA').save(os.path.join(out, 'textures', 'frog_body.png'))
    ff = recolour(tex_feet0, classify(tex_feet0[..., :3])[0] != 'white', green)
    if sole_v:                                                                # (a pale yellow patch where the feet's triangles don't reach)
        used = np.zeros(ff.shape[:2], bool)
        nonsole = [t for t in f_idx.reshape(-1, 3) if not set(t) & set(sole_v)]
        for t in nonsole:
            for yy, xx, L, ins in raster_uv(ff.shape, F['uv'][t], ss=2): used[yy, xx] = True
        hh, ww = ff.shape[:2]; m = 3; spot = None
        for y0 in range(m, hh - 6 - m):
            for x0 in range(m, ww - 6 - m):
                if not used[y0 - m:y0 + 6 + m, x0 - m:x0 + 6 + m].any(): spot = (y0, x0); break
            if spot: break
        assert spot, 'no free place in the feet texture for the sole colour'
        ff[spot[0]:spot[0] + 6, spot[1]:spot[1] + 6, :3] = sole_rgb; ff[spot[0]:spot[0] + 6, spot[1]:spot[1] + 6, 3] = 255
        F['uv'][sole_v] = [(spot[1] + 3) / ww, (spot[0] + 3) / hh]
        report.append('feet texture: sole colour %s at texels %d,%d (6 x 6, unused by the rest of the feet)' % (tuple(sole_rgb), spot[1], spot[0]))
    Image.fromarray(ff, 'RGBA').save(os.path.join(out, 'textures', 'frog_feet.png'))
    hc = classify(tex_head0[..., :3])
    hood = (hc[0] == 'white') | ((hc[0] == 'colour') & (hc[1] > 190) & (hc[1] < 260))   # (the blue hood and its pale rim)
    fh = recolour(tex_head0, hood, green)
    Image.fromarray(fh, 'RGBA').save(os.path.join(out, 'textures', 'frog_head.png'))
    for i in range(7):
        Image.fromarray(texs['player_eye.%d' % i].decode(), 'RGBA').save(os.path.join(out, 'textures', 'player_eye.%d.png' % i))

    # ---- glTF
    g = Glb(); J = g.j
    for b in mb.bones:
        pw = mb.bones[b.parent].world if b.parent >= 0 else np.eye(4)
        J['nodes'].append({'name': b.name, **trs(np.linalg.inv(pw) @ b.world)})
    for b in mb.bones:
        if b.parent >= 0: J['nodes'][b.parent].setdefault('children', []).append(b.index)
    J['skins'].append({'name': 'Mario_Frog_skeleton', 'joints': list(range(len(mb.bones))), 'skeleton': 0,
                       'inverseBindMatrices': g.acc(np.array([b.inv.T for b in mb.bones], np.float32).reshape(-1, 16), 'MAT4', target=None)})
    mats = {}

    def mat(name, tex, md):
        if name in mats: return mats[name]
        L0 = md['layers'][0]
        J['images'].append({'name': tex, 'uri': 'textures/%s.png' % tex})
        J['samplers'].append({'magFilter': 9729, 'minFilter': 9729, 'wrapS': WRAP[L0['wrap'][0]], 'wrapT': WRAP[L0['wrap'][1]]})
        J['textures'].append({'sampler': len(J['samplers']) - 1, 'source': len(J['images']) - 1})
        bt = {'index': len(J['textures']) - 1}
        sx, sy, rot, tx, ty = L0['srt']
        if (sx, sy, rot, tx, ty) != (1.0, 1.0, 0.0, 0.0, 0.0):
            bt['extensions'] = {'KHR_texture_transform': {'scale': [sx, sy], 'offset': [-sx * tx, sy * ty + 1 - sy]}}
            if 'KHR_texture_transform' not in J.setdefault('extensionsUsed', []): J['extensionsUsed'].append('KHR_texture_transform')
        J['materials'].append({'name': name, 'pbrMetallicRoughness': {'baseColorTexture': bt, 'metallicFactor': 0.0, 'roughnessFactor': 0.8},
                               'alphaMode': 'MASK', 'alphaCutoff': 0.5, 'extras': {'nw4r_layers': [tex] + [l['tex'] for l in md['layers'][1:]]}})
        mats[name] = len(J['materials']) - 1; return mats[name]

    def prim(D, ix, m, skin):
        nrm = np.asarray(D['nrm'], float)
        at = {'POSITION': g.acc(np.asarray(D['pos'], np.float32), 'VEC3', minmax=True),
              'NORMAL': g.acc((nrm / np.linalg.norm(nrm, axis=1, keepdims=True)).astype(np.float32), 'VEC3'),
              'TEXCOORD_0': g.acc(np.asarray(D['uv'], np.float32), 'VEC2'), 'COLOR_0': g.acc(np.asarray(D['clr'], np.float32), 'VEC4')}
        if skin:
            j = np.asarray(D['j']); j = j if j.ndim == 2 else np.c_[j, np.zeros((len(j), 3), int)]
            w = np.asarray(D['w']) if 'w' in D else np.tile([1.0, 0, 0, 0], (len(j), 1))
            at['JOINTS_0'] = g.acc(j.astype(np.uint16), 'VEC4', ctype=5123); at['WEIGHTS_0'] = g.acc(w.astype(np.float32), 'VEC4')
        return {'attributes': at, 'indices': g.acc(np.asarray(ix, np.uint32), 'SCALAR', ctype=5125, target=34963), 'material': m}

    def node(name, prims, skin, extras):
        J['meshes'].append({'name': name, 'primitives': prims})
        J['nodes'].append({'name': name, 'mesh': len(J['meshes']) - 1, **({'skin': 0} if skin else {}), 'extras': extras})
        return len(J['nodes']) - 1

    m_body = mat('mat_player_body', 'frog_body', mb.mats[mi])
    m_belly = dict(mb.mats[mi]); m_belly['layers'] = [dict(mb.mats[mi]['layers'][0], wrap=(0, 0))] + mb.mats[mi]['layers'][1:]
    body_prims = [prim(A, tri[keep].reshape(-1), m_body, True), prim(B_, b_idx, mat('mat_player_belly', 'frog_belly', m_belly), True)]
    roots = [0, node('body', body_prims, True, {'from': 'MB_model (Super Mario), shoes and fists off, trouser bottoms down to the feet'}),
             node('hands', [prim(HB, hB_idx, m_body, True)], True, {'from': "NSMB2 mr_tail_body handsB (open hands)"}),
             node('feet', [prim(F, f_idx, mat('mat_player_pbody', 'frog_feet', pb.mats[pmi]), True)], True, {'from': 'PMB_model (Penguin Mario) feet'})]
    hp = [prim(D, ix, mat(ph.mats[m_]['name'], 'frog_head' if ph.mats[m_]['name'] == 'mat_player_phead' else ph.mats[m_]['layers'][0]['tex'], ph.mats[m_]), False)
          for m_, D, ix in hprims]
    hn = node('head', hp, False, {'from': 'PMH_model (Penguin Mario), beak off', 'attached_to': 'face_1'})
    J['nodes'][hn].update(trs(ph.bones[0].world))
    J['nodes'][names.index('face_1')].setdefault('children', []).append(hn)
    J['scenes'][0]['nodes'] = roots
    path = os.path.join(out, 'Mario_Frog.glb'); g.save(path)
    print('wrote', path); print('\n'.join('  ' + r for r in report))


if __name__ == '__main__':
    main()
