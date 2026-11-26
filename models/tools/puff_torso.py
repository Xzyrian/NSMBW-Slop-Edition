"""NSMB2's Raccoon torso "puff", carried over to an NSMBW body.

NSMB2's Raccoon body (mr_tail_body / lg_tail_body) is its normal body (mr_normal / lg_normal) with
the torso pushed out (belly, back, sides, hips); arms, lower legs and feet are untouched. This
measures that push along the normal body's surface (how far out the Raccoon surface lies along
each torso vertex's normal), and applies it to an NSMBW body: each torso vertex moves along its own
normal by the push measured at the nearest NSMB2 points facing the same way (the two games'
skeletons match, and their bodies are near the same size). The offsets are then smoothed over the
mesh, easing off toward the triangles that join the torso to the arms, neck and legs (those parts
don't move), so no seam opens."""
import numpy as np

TORSO = ('skl_root', 'spin', 'leg_l1', 'leg_r1')


def closest_on_tris(P, A, B, C):
    """closest point on each triangle (A, B, C: m x 3) to each point P (n x 3) -> n x m x 3 (Ericson's regions)"""
    P = P[:, None, :]
    ab, ac = B - A, C - A
    ap, bp, cp = P - A, P - B, P - C
    d1, d2 = (ab * ap).sum(-1), (ac * ap).sum(-1)
    d3, d4 = (ab * bp).sum(-1), (ac * bp).sum(-1)
    d5, d6 = (ab * cp).sum(-1), (ac * cp).sum(-1)
    va, vb, vc = d3 * d6 - d5 * d4, d5 * d2 - d1 * d6, d1 * d4 - d3 * d2
    sd = lambda x: np.where(np.abs(x) < 1e-12, 1e-12, x)
    den = sd(va + vb + vc)
    inside = A + ab * (vb / den)[..., None] + ac * (vc / den)[..., None]
    e_ab = A + ab * np.clip(d1 / sd(d1 - d3), 0, 1)[..., None]
    e_ac = A + ac * np.clip(d2 / sd(d2 - d6), 0, 1)[..., None]
    e_bc = B + (C - B) * np.clip((d4 - d3) / sd((d4 - d3) + (d5 - d6)), 0, 1)[..., None]
    conds = [(d1 <= 0) & (d2 <= 0), (d3 >= 0) & (d4 <= d3), (vc <= 0) & (d1 >= 0) & (d3 <= 0),
             (d6 >= 0) & (d5 <= d6), (vb <= 0) & (d2 >= 0) & (d6 <= 0), (va <= 0) & (d4 - d3 >= 0) & (d5 - d6 >= 0)]
    vals = [np.broadcast_to(A, inside.shape), np.broadcast_to(B, inside.shape), e_ab, np.broadcast_to(C, inside.shape), e_ac, e_bc]
    out = inside
    for c, v in reversed(list(zip(conds, vals))):      # (the first matching region wins)
        out = np.where(c[..., None], v, out)
    return out


def nsmb2_push(normal, raccoon):
    """normal, raccoon: N2Model shape(0) dicts. -> (points, normals, push along the normal) on the normal body's torso"""
    sel = np.array([b in TORSO for b in normal['bone']])
    P, N = normal['pos'][sel], normal['nrm'][sel]
    N = N / np.linalg.norm(N, axis=1, keepdims=True)
    t = raccoon['idx'].reshape(-1, 3)
    rt = np.array([b in TORSO or b.startswith('leg') or b.startswith('arm') for b in raccoon['bone']])
    t = t[rt[t].all(1)]
    A, B, C = raccoon['pos'][t[:, 0]], raccoon['pos'][t[:, 1]], raccoon['pos'][t[:, 2]]
    push = np.zeros(len(P))
    for i in range(0, len(P), 64):                                                 # (in blocks: n x m x 3)
        Q = closest_on_tris(P[i:i + 64], A, B, C)
        D = Q - P[i:i + 64, None, :]
        j = np.argmin((D ** 2).sum(-1), axis=1)
        d = D[np.arange(len(j)), j]
        push[i:i + 64] = (d * N[i:i + 64]).sum(-1)                                 # (signed: out along the normal)
    return P, N, push


def apply(pos, nrm, bone_of_vertex, tri, field, k=6, smooth=6, strength=1.0):
    """move an NSMBW body's torso vertices. pos, nrm: model space (v x 3); bone_of_vertex: names; tri: (t x 3).
    -> new positions, report"""
    FP, FN, push = field
    key = [tuple(np.round(p, 4)) for p in pos]
    uniq = {}
    for i, kk in enumerate(key): uniq.setdefault(kk, []).append(i)
    keys = list(uniq)
    up = np.array(keys)
    un = np.array([nrm[uniq[kk]].sum(0) for kk in keys]); un /= np.linalg.norm(un, axis=1, keepdims=True) + 1e-9
    torso = np.array([all(bone_of_vertex[i] in TORSO for i in uniq[kk]) for kk in keys])    # (shared with another part: pinned)
    # the push at each NSMBW point: nearest NSMB2 points facing the same way, inverse-distance weighted
    d = np.linalg.norm(up[:, None, :] - FP[None, :, :], axis=-1) + 3.0 * (1.0 - un @ FN.T).clip(0)
    nn = np.argsort(d, axis=1)[:, :k]
    w = 1.0 / (np.take_along_axis(d, nn, 1) + 0.05)
    off = (push[nn] * w).sum(1) / w.sum(1) * strength
    off[~torso] = 0.0
    # smoothed over the mesh (pinned points stay 0)
    ki = {kk: n for n, kk in enumerate(keys)}
    nb = [set() for _ in keys]
    for t in tri:
        a, b, c = (ki[key[v]] for v in t)
        nb[a] |= {b, c}; nb[b] |= {a, c}; nb[c] |= {a, b}
    for _ in range(smooth):
        off = np.array([0.0 if not torso[i] else 0.5 * off[i] + 0.5 * np.mean(off[list(nb[i])]) if nb[i] else off[i] for i in range(len(keys))])
    newp = pos.copy()
    for n, kk in enumerate(keys):
        for i in uniq[kk]: newp[i] = pos[i] + un[n] * off[n]
    edge = np.array([torso[i] and any(not torso[j] for j in nb[i]) for i in range(len(keys))])
    rep = 'torso push: %d torso points moved %.2f to %.2f units (mean %.2f), eased to %.2f mean where they meet the arms / neck / legs (%d points)' % (
        int(torso.sum()), off[torso].min(), off[torso].max(), off[torso].mean(), off[edge].mean() if edge.any() else 0, int(edge.sum()))
    return newp, rep


def _turn_normals(A, tri, newp, moved):
    """NSMBW's normals turned by the change of face-normal direction at each moved point (keeps their smoothing)"""
    kp = [tuple(np.round(p, 4)) for p in A['pos']]
    def face_normals(P):
        fn = np.cross(P[tri[:, 1]] - P[tri[:, 0]], P[tri[:, 2]] - P[tri[:, 0]]); acc = {}
        for t, f in zip(tri, fn):
            for v in t: acc[kp[v]] = acc.get(kp[v], 0) + f
        return acc
    a0, a1 = face_normals(A['pos']), face_normals(newp)
    N = A['nrm'] / np.linalg.norm(A['nrm'], axis=1, keepdims=True)
    out = A['nrm'].copy()
    for i in np.nonzero(moved)[0]:
        if kp[i] not in a0: continue
        n0 = a0[kp[i]] / (np.linalg.norm(a0[kp[i]]) + 1e-12); n1 = a1[kp[i]] / (np.linalg.norm(a1[kp[i]]) + 1e-12)
        v = N[i] + (n1 - n0); out[i] = v / np.linalg.norm(v)
    return out


def smooth_region(A, tri, names, bones=TORSO, iters=6, lam=0.5, mu=-0.53, colours=True):
    """Taubin smoothing (no shrinking) of the surface on these bones: takes out small ridges and steps
    (the overalls' bib edge and straps) and the dark lines baked along them in the vertex colours.
    Points that meet other parts (arms, neck, legs) stay put. Changes A in place. -> report line"""
    key = [tuple(np.round(p, 4)) for p in A['pos']]
    uniq = {}
    for i, k in enumerate(key): uniq.setdefault(k, []).append(i)
    keys = list(uniq); ki = {k: n for n, k in enumerate(keys)}
    bone_of_v = [names[j] for j in A['j'][:, 0]]
    region = np.array([all(bone_of_v[i] in bones for i in uniq[k]) for k in keys])
    nb = [set() for _ in keys]
    for t in tri:
        a, b, c = (ki[key[v]] for v in t)
        nb[a] |= {b, c}; nb[b] |= {a, c}; nb[c] |= {a, b}
    free = region & np.array([all(region[j] for j in nb[i]) for i in range(len(keys))])   # (not at a seam)
    P = np.array(keys, float)
    C = np.array([A['clr'][uniq[k]].mean(0) for k in keys]) if colours else None
    nbl = [list(x) for x in nb]
    for _ in range(iters):
        for f in (lam, mu):
            L = np.array([P[nbl[i]].mean(0) - P[i] if nbl[i] else np.zeros(3) for i in range(len(keys))])
            P[free] += f * L[free]
        if colours:
            Lc = np.array([C[nbl[i]].mean(0) - C[i] if nbl[i] else np.zeros(4) for i in range(len(keys))])
            C[region] += 0.5 * Lc[region]
    if colours:                                                              # (brightness kept: averaging takes in the dark lines)
        C0 = np.array([A['clr'][uniq[k]].mean(0) for k in keys])
        k_ = C0[region, :3].mean() / max(C[region, :3].mean(), 1e-6)
        C[region, :3] = np.clip(C[region, :3] * k_, 0, 1)
    newp = A['pos'].copy(); moved = np.zeros(len(newp), bool)
    for n, k in enumerate(keys):
        if free[n]:
            for i in uniq[k]: newp[i] = P[n]; moved[i] = True
        if colours and region[n]:
            for i in uniq[k]: A['clr'][i] = C[n]
    shift = np.linalg.norm(P[free] - np.array(keys, float)[free], axis=1)
    A['nrm'] = _turn_normals(A, tri, newp, moved)
    A['pos'] = newp
    return 'smoothed %d torso points (%d iterations; moved %.2f on average, %.2f at most)%s' % (
        int(free.sum()), iters, shift.mean(), shift.max(), ', shading smoothed with them' if colours else '')


def puff_body(A, tri, names, field, strength=1.0):
    """apply() to a build_prims body (A: pos, nrm, j), its normals turned with the surface (the change of
    face-normal direction put on NSMBW's own normals, which keeps their smoothing). Changes A in place.
    -> report line"""
    bone_of_v = [names[j] for j in A['j'][:, 0]]
    newp, rep = apply(A['pos'], A['nrm'], bone_of_v, tri, field, strength=strength)
    moved = np.abs(newp - A['pos']).sum(1) > 0
    A['nrm'] = _turn_normals(A, tri, newp, moved)
    A['pos'] = newp
    return rep + ' (strength %.2f)' % strength
