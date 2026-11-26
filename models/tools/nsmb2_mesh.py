"""NSMB2 (CTR CGFX) player model meshes -> numpy, in model (bind) space, with NSMBW bone names."""
import struct, sys, os
import numpy as np
HERE = os.path.dirname(os.path.abspath(__file__))
for d in (HERE, os.path.join(HERE, '..', '..', 'recomp', 'tools'), os.path.join(HERE, '..', '..', 'SMB3Disassembly', 'tools')):
    sys.path.insert(0, os.path.normpath(d))      # (brres_read / export_player_models: recomp/tools; nsmb2_anims: SMB3Disassembly/tools)
from nsmb2_anims import Cgfx, etc1


def euler_mat(r):
    x, y, z = r
    Rx = np.array([[1, 0, 0], [0, np.cos(x), -np.sin(x)], [0, np.sin(x), np.cos(x)]])
    Ry = np.array([[np.cos(y), 0, np.sin(y)], [0, 1, 0], [-np.sin(y), 0, np.cos(y)]])
    Rz = np.array([[np.cos(z), -np.sin(z), 0], [np.sin(z), np.cos(z), 0], [0, 0, 1]])
    return Rz @ Ry @ Rx


class N2Model:
    def __init__(self, path, model):
        self.g = g = Cgfx(open(path, 'rb').read())
        self.sec = sec = g.sections()
        mo = dict(sec['models'])[model]
        self.mo = mo
        sk = g.rel(mo + 0xE0)
        assert g.d[sk + 4:sk + 8] == b'SOBJ'
        self.bones = []
        world = []
        for name, bo in g.dict(g.rel(sk + 0x1C)):
            par = g.i32(bo + 0xC)
            M = np.eye(4); M[:3, :3] = euler_mat(struct.unpack_from('<3f', g.d, bo + 0x2C)) @ np.diag(struct.unpack_from('<3f', g.d, bo + 0x20))
            M[:3, 3] = struct.unpack_from('<3f', g.d, bo + 0x38)
            W = (world[par] if par >= 0 else np.eye(4)) @ M
            world.append(W); self.bones.append((name, par))
        self.world = world
        self.vis_nodes = [n for n, _ in g.dict(g.rel(mo + 0xD0))]
        self.mats = [n for n, _ in g.dict(g.rel(mo + 0xC0))]
        # meshes: shape, material, visibility node
        ma = g.rel(mo + 0xB8)
        self.meshes = []
        for i in range(g.u32(mo + 0xB4)):
            me = g.rel(ma + 4 * i)
            self.meshes.append({'shape': g.u32(me + 0x18), 'mat': self.mats[g.u32(me + 0x1C)],
                                'node': self.vis_nodes[g.s16(me + 0x26)]})

    def shape(self, si):
        """-> dict pos (model space), nrm, uv (NSMBW/GL-top convention: v flipped), clr (0-1), bone (names), idx"""
        g = self.g
        sh = g.rel(g.rel(self.mo + 0xC8) + 4 * si)
        vb = g.rel(g.rel(sh + 0x3C))
        assert g.u32(vb) == 0x40000002
        usages = [g.u32(g.rel(g.rel(vb + 0x2C) + 4 * a) + 4) for a in range(g.u32(vb + 0x28))]
        raw, size, stride = g.rel(vb + 0x18), g.u32(vb + 0x14), g.u32(vb + 0x24)
        assert usages[:4] == [0, 1, 4, 3], usages
        nv = size // stride
        out = {'pos': [], 'nrm': [], 'uv': [], 'clr': [], 'bone': [], 'idx': []}
        base = 0
        for j in range(g.u32(sh + 0x2C)):
            sm = g.rel(g.rel(sh + 0x30) + 4 * j)
            table = [g.u32(g.rel(sm + 4) + 4 * k) for k in range(g.u32(sm))]
            skin = g.u32(sm + 8)
            assert skin in (0, 1), 'smooth skinning'
            for fi in range(g.u32(sm + 0xC)):
                fc = g.rel(g.rel(sm + 0x10) + 4 * fi)
                for di in range(g.u32(fc)):
                    d = g.rel(g.rel(fc + 4) + 4 * di)
                    fmt, n = g.u32(d), g.u32(d + 8); ib = g.rel(d + 12)
                    out['idx'] += list(struct.unpack_from('<%dH' % (n // 2), g.d, ib)) if fmt == 0x1403 else list(g.d[ib:ib + n])
            sub_table = table
        for i in range(nv):
            o = raw + i * stride
            p = np.array(struct.unpack_from('<3f', g.d, o) + (1.0,)); nr = np.array(struct.unpack_from('<3f', g.d, o + 12))
            uv = struct.unpack_from('<2f', g.d, o + 24); c = g.d[o + 32:o + 36]
            b = sub_table[g.d[o + 36]] if 7 in usages else sub_table[0]
            W = self.world[b]                                  # (rigid / single bone: vertex in that bone's space)
            out['pos'].append((W @ p)[:3]); out['nrm'].append(W[:3, :3] @ nr)
            out['uv'].append((uv[0], 1.0 - uv[1])); out['clr'].append(tuple(x / 255 for x in c)); out['bone'].append(self.bones[b][0])
        r = {k: np.array(v) for k, v in out.items() if k != 'bone'}; r['bone'] = out['bone']
        return r

    def texture(self, name):
        g = self.g
        t = dict(self.sec['textures'])[name]; w, h, size = g.u32(t + 0x1C), g.u32(t + 0x18), g.u32(t + 0x44)
        fmt = g.u32(t + 0x34)
        assert fmt == 12, 'texture format %d' % fmt                 # ETC1
        return np.array(etc1(g.d[g.rel(t + 0x48):g.rel(t + 0x48) + size], w, h), np.uint8)
