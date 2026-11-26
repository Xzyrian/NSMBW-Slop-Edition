"""The Frog hood rebuilt on Nintendo's own layout: the original (Penguin) hood's triangles, the top of
it split once (each triangle into four, like a Subdivide in Blender) so it can hold the eye bumps,
then fitted onto the user's sculpted shape. The hood's open edge (round the face) stays where
Nintendo had it, so it meets the face with no gaps."""
import numpy as np
from collections import defaultdict


def weld(P, T, nd=3):
    used = np.unique(T); key = {}; idx = np.full(len(P), -1); V = []
    for i in used:
        k = tuple(np.round(P[i], nd))
        if k not in key: key[k] = len(V); V.append(P[i])
        idx[i] = key[k]
    F = idx[T]
    F = F[(F[:, 0] != F[:, 1]) & (F[:, 1] != F[:, 2]) & (F[:, 0] != F[:, 2])]
    return np.array(V), F, idx


def edges_of(F):
    E = defaultdict(int)
    for t in F:
        for a, b in ((0, 1), (1, 2), (2, 0)):
            E[(min(t[a], t[b]), max(t[a], t[b]))] += 1
    return E


def neighbours(n, F):
    nb = [set() for _ in range(n)]
    for t in F:
        for a, b in ((0, 1), (1, 2), (2, 0)):
            nb[t[a]].add(t[b]); nb[t[b]].add(t[a])
    return [sorted(s) for s in nb]


def mirror_map(V, tol=0.01):
    M = V * [1, 1, -1]
    d = np.linalg.norm(V[:, None] - M[None], axis=2)
    j = d.argmin(1)
    assert d[np.arange(len(V)), j].max() < tol, 'the template is not symmetric'
    return j


def make_symmetric(V, mir):
    W = (V + V[mir] * [1, 1, -1]) / 2
    W[mir == np.arange(len(V)), 2] = 0.0
    return W


def subdivide_region(V, F, red, mir):
    """split the triangles marked red into four; their neighbours that share one split edge into two
    (any triangle with two split edges is split into four too, so the layout stays even and symmetric)"""
    red = red.copy()
    while True:
        split = set()
        for t in F[red]:
            for a, b in ((0, 1), (1, 2), (2, 0)): split.add((min(t[a], t[b]), max(t[a], t[b])))
        cnt = np.array([sum((min(t[a], t[b]), max(t[a], t[b])) in split for a, b in ((0, 1), (1, 2), (2, 0))) for t in F])
        more = (cnt >= 2) & ~red
        if not more.any(): break
        red |= more
    V = list(V); mid = {}
    for e in sorted(split):
        V.append((V[e[0]] + V[e[1]]) / 2); mid[e] = len(V) - 1
    m = lambda a, b: mid[(min(a, b), max(a, b))]
    out = []; level = []
    for k, t in enumerate(F):
        a, b, c = t
        if red[k]:
            ab, bc, ca = m(a, b), m(b, c), m(c, a)
            out += [[a, ab, ca], [ab, b, bc], [ca, bc, c], [ab, bc, ca]]; level += [1] * 4
            continue
        es = [(x, y) for x, y in ((a, b), (b, c), (c, a)) if (min(x, y), max(x, y)) in split]
        if not es:
            out.append([a, b, c]); level.append(0); continue
        x, y = es[0]; z = [v for v in (a, b, c) if v not in (x, y)][0]; mm = m(x, y)
        out += [[x, mm, z], [mm, y, z]]; level += [0, 0]
    V = np.array(V); F = np.array(out)
    return V, F, np.array(level), mirror_map(V)


def laplacian(n, nb):
    L = np.zeros((n, n))
    for i, s in enumerate(nb):
        if not s: continue
        L[i, i] = 1.0
        for j in s: L[i, j] -= 1.0 / len(s)
    return L


def fit(V0, F, target, nearest, sample_pts, fixed, mir, schedule=(30, 15, 8, 4, 2, 1.2, 0.8, 0.6, 0.5, 0.5), rim_w=200.0, data_w=1.0, back_w=0.6, rim_to=None, skip=None):
    """V0 fitted onto the target surface (V, F) keeping its own layout: a Laplacian keeps each
    point's place among its neighbours (as in V0), points pull to their nearest place on the target,
    and the target's own points pull the nearest place on the fit (so bumps get filled); the fixed
    points stay; after every step both sides are made the same"""
    TV, TF = target
    n = len(V0); nb = neighbours(n, F)
    L = laplacian(n, nb); delta = L @ V0
    V = V0.copy()
    for alpha in schedule:
        rows = []; rhs = []
        rows.append(np.sqrt(alpha) * L); rhs.append(np.sqrt(alpha) * delta)
        Q, _, _ = nearest(V, TV, TF)
        w = np.full(n, np.sqrt(data_w)); w[fixed] = 0
        if skip is not None: w[skip(Q)] = 0                                    # (no pull where the target is left out)
        rows.append(np.diag(w)); rhs.append(w[:, None] * Q)
        # target samples -> the nearest place on the fit (as a mix of its triangle's corners)
        Qs, ti, bc = nearest(sample_pts, V, F)
        A = np.zeros((len(sample_pts), n))
        for r, (t, b) in enumerate(zip(ti, bc)):
            for k in range(3): A[r, F[t][k]] += b[k]
        rows.append(np.sqrt(back_w) * A); rhs.append(np.sqrt(back_w) * sample_pts)
        W = np.zeros((len(fixed), n)); W[np.arange(len(fixed)), fixed] = np.sqrt(rim_w)
        goal = V0[fixed] if rim_to is None else rim_to(V[fixed])
        rows.append(W); rhs.append(np.sqrt(rim_w) * goal)
        A_ = np.vstack(rows); b_ = np.vstack(rhs)
        V = np.linalg.lstsq(A_, b_, rcond=None)[0]
        V = make_symmetric(V, mir)
    return V


def sample_surface(V, F, spacing=0.5, seed=1):
    rng = np.random.default_rng(seed)
    A = V[F[:, 0]]; B = V[F[:, 1]]; C = V[F[:, 2]]
    area = np.linalg.norm(np.cross(B - A, C - A), axis=1) / 2
    k = max(1, int(area.sum() / spacing ** 2))
    t = rng.choice(len(F), k, p=area / area.sum())
    r1 = np.sqrt(rng.random(k)); r2 = rng.random(k)
    return (1 - r1)[:, None] * A[t] + (r1 * (1 - r2))[:, None] * B[t] + (r1 * r2)[:, None] * C[t]


def taubin(V, F, movable, mir, iters=10, lam=0.5, mu=-0.53):
    nb = neighbours(len(V), F); V = V.copy()
    for _ in range(iters):
        for f_ in (lam, mu):
            avg = np.array([V[s].mean(0) if s else V[i] for i, s in enumerate(nb)])
            V[movable] += f_ * (avg[movable] - V[movable])
        V = make_symmetric(V, mir)
    return V


def boundary_edges(F):
    E = edges_of(F)
    # (keep the direction the triangle gives the edge)
    out = []
    for t in F:
        for a, b in ((0, 1), (1, 2), (2, 0)):
            if E[(min(t[a], t[b]), max(t[a], t[b]))] == 1: out.append((t[a], t[b]))
    return out


def longest_loop(F):
    """the longest closed boundary loop (copes with points where the edge touches itself)"""
    be = boundary_edges(F)
    nxt = defaultdict(list)
    for a, b in be: nxt[a].append(b)
    used = set(); best = []
    for a, b in be:
        if (a, b) in used: continue
        loop = [a]; cur = (a, b)
        while cur not in used:
            used.add(cur); loop.append(cur[1])
            cands = [c for c in nxt[cur[1]] if (cur[1], c) not in used]
            if not cands: break
            cur = (cur[1], cands[0])
        if loop[-1] == loop[0]: loop = loop[:-1]
        if len(loop) > len(best): best = loop
    return best


def closest_on_segments(P, A, B):
    AB = B - A; L2 = np.maximum((AB ** 2).sum(1), 1e-12)
    t = np.clip(((P[:, None] - A[None]) * AB[None]).sum(2) / L2[None], 0, 1)
    Q = A[None] + t[..., None] * AB[None]
    d = np.linalg.norm(Q - P[:, None], axis=2); j = d.argmin(1)
    return Q[np.arange(len(P)), j], d[np.arange(len(P)), j]


def smin(a, b, k):
    h = np.clip(0.5 + 0.5 * (b - a) / k, 0, 1)
    return b * (1 - h) + a * h - k * h * (1 - h)


def ellipsoid_sdf(X, c, r):
    u = (X - c) / r; n = np.linalg.norm(u, axis=-1)
    return (n - 1) * r.min()


def union_balls(V, N, balls, k=1.0, tmax=8.0, D=None):
    """each point moved out (along its normal N, or along D if given) onto the smooth union of the
    surface and the balls (c, r): where the union's surface crosses that line"""
    out = V.copy()
    if D is None: D = N
    for i, (v, n, dd) in enumerate(zip(V, N, D)):
        cs = max(float(n @ dd), 0.2)
        def g(t):
            p = v + t * dd
            db = min(ellipsoid_sdf(p, c, r) for c, r in balls)                  # (the balls kept apart: no blend between them)
            return smin(t * cs, db, k)
        if g(0.0) >= 0: continue
        lo, hi = 0.0, tmax
        if g(hi) < 0: continue
        for _ in range(40):
            m = (lo + hi) / 2
            if g(m) < 0: lo = m
            else: hi = m
        out[i] = v + dd * (lo + hi) / 2
    return out


def lift_directions(V, N, balls, drop=3.0, reach=1.8):
    """the way each point is lifted: straight out (its normal) away from the balls, and near a ball
    out from a point inside the head below the ball's centre, so neighbouring paths never cross"""
    D = N.copy()
    for c, r in balls:
        c2 = c + np.array([0.0, drop, 0.0])
        u = V - c2; u /= np.linalg.norm(u, axis=1, keepdims=True)
        q = np.linalg.norm((V - c) / (r * reach), axis=1)
        w = np.clip(1.5 - q, 0, 1); w = w * w * (3 - 2 * w)
        D = D * (1 - w[:, None]) + u * w[:, None]
    return D / np.linalg.norm(D, axis=1, keepdims=True)


def relax_onto(V, F, target, nearest, fixed, mir, rim_to=None, iters=20, step=0.5):
    """the points spread evenly over the target: each moves part way to its neighbours' middle and
    back onto the target (the rim's points along the rim); the layout (who joins whom) is unchanged"""
    TV, TF = target
    nb = neighbours(len(V), F); V = V.copy()
    mov = np.setdiff1d(np.arange(len(V)), fixed)
    for _ in range(iters):
        avg = np.array([V[s].mean(0) if s else V[i] for i, s in enumerate(nb)])
        V[mov] += step * (avg[mov] - V[mov])
        V[mov] = nearest(V[mov], TV, TF)[0]
        if rim_to is not None: V[fixed] = rim_to(V[fixed])
        V = make_symmetric(V, mir)
    return V


def ball_mesh(c, r, axis, seg=10, rings=7):
    """a low ball (ellipsoid centre c, radii r) with its poles along axis: rings round the front
    pole, like Mario's nose. -> V, F (facing out)"""
    a = axis / np.linalg.norm(axis)
    t = np.array([0.0, -1.0, 0.0]) - a * (-a[1]); t /= np.linalg.norm(t); s = np.cross(a, t)
    V = [a.copy()]
    for k in range(1, rings):
        th = np.pi * k / rings
        for j in range(seg):
            ph = 2 * np.pi * (j + 0.5 * (k % 2)) / seg
            V.append(np.cos(th) * a + np.sin(th) * (np.cos(ph) * t + np.sin(ph) * s))
    V.append(-a); V = np.array(V)
    F = []
    ring = lambda k: 1 + (k - 1) * seg
    for j in range(seg): F.append([0, ring(1) + j, ring(1) + (j + 1) % seg])
    for k in range(1, rings - 1):
        A0, B0 = ring(k), ring(k + 1)
        for j in range(seg):
            j1 = (j + 1) % seg
            if k % 2 == 0: F += [[A0 + j, B0 + j, A0 + j1], [A0 + j1, B0 + j, B0 + j1]]
            else: F += [[A0 + j, B0 + j, B0 + j1], [A0 + j, B0 + j1, A0 + j1]]
    last = len(V) - 1; L = ring(rings - 1)
    for j in range(seg): F.append([last, L + (j + 1) % seg, L + j])
    F = np.array(F)
    # (facing out)
    n = np.cross(V[F[:, 1]] - V[F[:, 0]], V[F[:, 2]] - V[F[:, 0]])
    if (n * V[F].mean(1)).sum() < 0: F = F[:, ::-1]
    return c + V * r, F
