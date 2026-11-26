"""the Frog hood's retopology (fix_frog_head.py): weld, then pymeshlab's isotropic remeshing"""
import numpy as np
import pymeshlab

def weld(P, T, nd=3):
    used = np.unique(T); key = {}; idx = np.full(len(P), -1); V = []
    for i in used:
        q = np.round(P[i], nd)
        k = tuple(q)
        if k not in key: key[k] = len(V); V.append(P[i])
        idx[i] = key[k]
    F = idx[T]
    F = F[(F[:, 0] != F[:, 1]) & (F[:, 1] != F[:, 2]) & (F[:, 0] != F[:, 2])]
    return np.array(V), F, idx

def remesh(V, F, target, iters=15, feat=40, maxdist=0.05):
    ms = pymeshlab.MeshSet()
    ms.add_mesh(pymeshlab.Mesh(vertex_matrix=V, face_matrix=F))
    ms.meshing_isotropic_explicit_remeshing(iterations=iters, targetlen=pymeshlab.PureValue(target) if hasattr(pymeshlab, 'PureValue') else pymeshlab.AbsoluteValue(target),
                                             featuredeg=feat, maxsurfdist=pymeshlab.PureValue(maxdist) if hasattr(pymeshlab, 'PureValue') else pymeshlab.AbsoluteValue(maxdist))
    m = ms.current_mesh()
    return m.vertex_matrix().copy(), m.face_matrix().copy()
