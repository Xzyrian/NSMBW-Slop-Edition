"""The Frog's idle pose from a .glb posed in Blender (its one-frame action), the posed side mirrored
onto the other: -> per bone, the local scale / rotation (degrees, X then Y then Z, as NW4R's
CHR0) / translation, as JSON; and a .glb of the model in that pose to look at.

  frog_idle_pose.py <posed .glb> <out .json> [<out posed .glb>]

Which side: the side whose arm and leg moved (by rotation) is the pose; its mirror image (across
the model's middle, X = 0; the model faces +Z) replaces the other side. The middle bones (spin,
face_1, ...) keep their pose."""
import json, struct, sys
import numpy as np

PAIRS = [('leg_l1', 'leg_r1'), ('leg_l2', 'leg_r2'), ('ankle_l1', 'ankle_r1'),
         ('arm_l1', 'arm_r1'), ('arm_l2', 'arm_r2'), ('wrist_l1', 'wrist_r1')]


def read_glb(path):
    d = open(path, 'rb').read()
    n = struct.unpack_from('<I', d, 12)[0]
    J = json.loads(d[20:20 + n]); binc = d[20 + n + 8:]

    def acc(i):
        a = J['accessors'][i]; v = J['bufferViews'][a['bufferView']]
        nc = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}[a['type']]
        return np.frombuffer(binc, np.float32, count=a['count'] * nc, offset=v.get('byteOffset', 0) + a.get('byteOffset', 0)).reshape(a['count'], nc).astype(float)
    return J, acc, d


def q2m(q):
    x, y, z, w = q
    return np.array([[1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)],
                     [2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)],
                     [2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)]])


def trs_m(t, q, s):
    m = np.eye(4); m[:3, :3] = q2m(q) * s; m[:3, 3] = t; return m


def euler_xyz(r):
    """R = Rz Ry Rx -> (x, y, z) radians"""
    sy = -r[2, 0]
    if abs(sy) < 0.999999:
        y = np.arcsin(sy); x = np.arctan2(r[2, 1], r[2, 2]); z = np.arctan2(r[1, 0], r[0, 0])
    else:
        y = np.pi / 2 * np.sign(sy); x = np.arctan2(-r[1, 2], r[1, 1]); z = 0.0
    return np.array([x, y, z])


def main():
    src, out_json = sys.argv[1:3]
    out_glb = sys.argv[3] if len(sys.argv) > 3 else None
    J, acc, raw = read_glb(src)
    nodes = J['nodes']; idx = {n.get('name'): i for i, n in enumerate(nodes)}
    parent = {}
    for i, n in enumerate(nodes):
        for c in n.get('children', []): parent[c] = i
    rest = {i: (np.array(n.get('translation', [0, 0, 0])), np.array(n.get('rotation', [0, 0, 0, 1])), np.array(n.get('scale', [1, 1, 1]))) for i, n in enumerate(nodes)}
    posed = {i: list(v) for i, v in rest.items()}
    an = J['animations'][0]
    for ch in an['channels']:
        s = an['samplers'][ch['sampler']]; v = acc(s['output'])[0]; i = ch['target']['node']
        posed[i][{'translation': 0, 'rotation': 1, 'scale': 2}[ch['target']['path']]] = v
    skin_joints = J['skins'][0]['joints']

    def world(i, P):
        m = trs_m(*P[i][:3]) if len(P[i]) == 3 else np.block([[P[i][3] * P[i][2], np.array(P[i][0])[:, None]], [np.zeros((1, 3)), np.ones((1, 1))]])
        return world(parent[i], P) @ m if i in parent else m
    # which side was posed
    def moved(name):
        i = idx[name]; return abs(float(np.dot(posed[i][1], rest[i][1])))
    r_moved = sum(1 - moved(r) for _, r in PAIRS); l_moved = sum(1 - moved(l) for l, _ in PAIRS)
    src_side, dst_side = (1, 0) if r_moved > l_moved else (0, 1)
    S = np.diag([-1.0, 1, 1, 1])                                                # (the model's middle: X = 0)
    Wp = {i: world(i, posed) for i in skin_joints}
    Wr = {i: world(i, rest) for i in skin_joints}
    for pair in PAIRS:                                                          # (parents first: PAIRS is in order)
        a, b = idx[pair[src_side]], idx[pair[dst_side]]
        C = np.linalg.inv(S @ Wr[a]) @ Wr[b]
        Wb = S @ Wp[a] @ C
        pw = world(parent[b], posed)
        L = np.linalg.inv(pw) @ Wb
        sc = np.linalg.norm(L[:3, :3], axis=0); R = L[:3, :3] / sc
        from_m = R
        # back to a quaternion for the posed set (for the preview), and keep the matrix
        posed[b] = [L[:3, 3], None, sc, R]
        Wp[b] = Wb
    out = {'source_side': ['left (_l)', 'right (_r)'][src_side], 'bones': {}}
    for i in skin_joints:
        n = nodes[i]['name']; P = posed[i]
        if len(P) == 4: R, t, s = P[3], P[0], P[2]
        else: R, t, s = q2m(P[1]), P[0], P[2]
        out['bones'][n] = {'scale': list(map(float, s)), 'rotate_deg': list(map(float, np.degrees(euler_xyz(R)))), 'translate': list(map(float, t)),
                           'posed': bool(len(P) == 4 or any(abs(float(np.dot(P[1], rest[i][1]))) < 0.99999 for _ in [0]) or np.abs(np.array(P[0]) - rest[i][0]).max() > 1e-4)}
    json.dump(out, open(out_json, 'w'), indent=1)
    print('pose from the %s side, mirrored; %d bones posed' % (out['source_side'], sum(b['posed'] for b in out['bones'].values())))
    if out_glb:                                                                 # (the model, posed: the nodes' rest set to the pose)
        J2 = json.loads(json.dumps(J))
        for i in skin_joints:
            P = posed[i]
            R = P[3] if len(P) == 4 else q2m(P[1])
            m = np.eye(4); m[:3, :3] = R; from_q = m
            # quaternion from R
            t_ = np.trace(R)
            if t_ > 0:
                s_ = np.sqrt(t_ + 1) * 2; q = [(R[2, 1] - R[1, 2]) / s_, (R[0, 2] - R[2, 0]) / s_, (R[1, 0] - R[0, 1]) / s_, s_ / 4]
            else:
                k = int(np.argmax(np.diag(R))); a, b, c = k, (k + 1) % 3, (k + 2) % 3
                s_ = np.sqrt(1 + R[a, a] - R[b, b] - R[c, c]) * 2
                q = [0, 0, 0, 0]; q[a] = s_ / 4; q[b] = (R[b, a] + R[a, b]) / s_; q[c] = (R[c, a] + R[a, c]) / s_; q[3] = (R[c, b] - R[b, c]) / s_
            J2['nodes'][i]['rotation'] = [float(x) for x in q]; J2['nodes'][i]['translation'] = [float(x) for x in P[0]]
        J2.pop('animations', None)
        n = struct.unpack_from('<I', raw, 12)[0]
        js = json.dumps(J2, separators=(',', ':')).encode()
        while len(js) % 4: js += b' '
        rest_bin = raw[20 + n:]
        blob = struct.pack('<II', len(js), 0x4E4F534A) + js + rest_bin
        open(out_glb, 'wb').write(struct.pack('<III', 0x46546C67, 2, 12 + len(blob)) + blob)


if __name__ == '__main__':
    main()
