#!/usr/bin/env python3
"""High-precision (mpmath) Taylor replay and Newton polish of a mass-side
periodic brake orbit.  Ordinary numerics at 30+ digits; not an interval
proof.  Usage: mp_replay.py m1 m2 tau [digits] [newton_iters]"""
from __future__ import annotations

import sys
import mpmath as mp


def taylor_step(q, v, m, N, h):
    """One Taylor step of order N for the planar 3-body problem (Cartesian)."""
    # coefficient arrays: Q[n][i][c], V[n][i][c]
    Q = [[[mp.mpf(0)] * 2 for _ in range(3)] for _ in range(N + 2)]
    V = [[[mp.mpf(0)] * 2 for _ in range(3)] for _ in range(N + 2)]
    for i in range(3):
        for c in range(2):
            Q[0][i][c] = q[i][c]
            V[0][i][c] = v[i][c]
    pairs = [(0, 1), (1, 2), (2, 0)]
    D = [[[mp.mpf(0)] * 2 for _ in range(3)] for _ in range(N + 1)]
    W = [[mp.mpf(0)] * 3 for _ in range(N + 1)]
    S = [[mp.mpf(0)] * 3 for _ in range(N + 1)]
    P = [[[mp.mpf(0)] * 2 for _ in range(3)] for _ in range(N + 1)]
    for n in range(N + 1):
        if n > 0:
            for i in range(3):
                for c in range(2):
                    Q[n][i][c] = V[n - 1][i][c] / n
        for p, (i, j) in enumerate(pairs):
            for c in range(2):
                D[n][p][c] = Q[n][j][c] - Q[n][i][c]
            W[n][p] = sum(D[k][p][0] * D[n - k][p][0] + D[k][p][1] * D[n - k][p][1] for k in range(n + 1))
            if n == 0:
                S[0][p] = W[0][p] ** mp.mpf(-1.5)
            else:
                S[n][p] = sum((mp.mpf(-1.5) * k - (n - k)) * W[k][p] * S[n - k][p] for k in range(1, n + 1)) / (n * W[0][p])
            for c in range(2):
                P[n][p][c] = sum(D[k][p][c] * S[n - k][p] for k in range(n + 1))
        acc = [[mp.mpf(0)] * 2 for _ in range(3)]
        for p, (i, j) in enumerate(pairs):
            for c in range(2):
                acc[i][c] += m[j] * P[n][p][c]
                acc[j][c] -= m[i] * P[n][p][c]
        for i in range(3):
            for c in range(2):
                V[n + 1][i][c] = acc[i][c] / (n + 1)
    # step size from the last coefficients (target 10^-(digits+2))
    tol = mp.mpf(10) ** (-(mp.mp.dps + 2))
    hmax = h
    for i in range(3):
        for c in range(2):
            a = abs(Q[N][i][c])
            if a > 0:
                hmax = min(hmax, (tol / a) ** (mp.mpf(1) / N))
    hh = hmax
    qn = [[mp.mpf(0)] * 2 for _ in range(3)]
    vn = [[mp.mpf(0)] * 2 for _ in range(3)]
    for i in range(3):
        for c in range(2):
            sq = Q[N][i][c]
            sv = V[N][i][c]
            for n in range(N - 1, -1, -1):
                sq = sq * hh + Q[n][i][c]
                sv = sv * hh + V[n][i][c]
            qn[i][c] = sq
            vn[i][c] = sv
    return qn, vn, hh


def integrate(m1, m2, tau, N=30):
    m = [m1, m2, mp.mpf(1)]
    x = (m2 ** 2 - m1 ** 2) / 2
    y = mp.sqrt(m2 ** 2 - (x + mp.mpf(1) / 2) ** 2)
    q = [[-mp.mpf(1) / 2, mp.mpf(0)], [mp.mpf(1) / 2, mp.mpf(0)], [x, y]]
    M = m1 + m2 + 1
    cx = sum(m[i] * q[i][0] for i in range(3)) / M
    cy = sum(m[i] * q[i][1] for i in range(3)) / M
    q = [[q[i][0] - cx, q[i][1] - cy] for i in range(3)]
    v = [[mp.mpf(0), mp.mpf(0)] for _ in range(3)]
    t = mp.mpf(0)
    while t < tau:
        h = min(mp.mpf('0.05'), tau - t)
        q, v, hh = taylor_step(q, v, m, N, h)
        t += hh
    return q, v


def hopf_residual(q, v, m1, m2):
    M12 = m1 + m2
    X = [q[1][c] - q[0][c] for c in range(2)]
    VX = [v[1][c] - v[0][c] for c in range(2)]
    Y = [q[2][c] - (m1 * q[0][c] + m2 * q[1][c]) / M12 for c in range(2)]
    VY = [v[2][c] - (m1 * v[0][c] + m2 * v[1][c]) / M12 for c in range(2)]
    B1 = X[0] * VX[0] + X[1] * VX[1] - Y[0] * VY[0] - Y[1] * VY[1]
    B2 = VX[0] * Y[0] + VX[1] * Y[1] + X[0] * VY[0] + X[1] * VY[1]
    B3 = VX[0] * Y[1] - VX[1] * Y[0] + X[0] * VY[1] - X[1] * VY[0]
    K = sum(mm * (vv[0] ** 2 + vv[1] ** 2) for mm, vv in zip([m1, m2, mp.mpf(1)], v)) / 2
    return [B1, B2, B3], K


def main():
    m1, m2, tau = (mp.mpf(a) for a in sys.argv[1:4])
    mp.mp.dps = int(sys.argv[4]) if len(sys.argv) > 4 else 30
    iters = int(sys.argv[5]) if len(sys.argv) > 5 else 4
    p = mp.matrix([m1, m2, tau])
    for it in range(iters + 1):
        q, v = integrate(p[0], p[1], p[2])
        B, K = hopf_residual(q, v, p[0], p[1])
        nB = mp.sqrt(sum(b ** 2 for b in B))
        D = p[0] ** 2 + p[1] ** 2 - 1
        print(f"iter {it}: m1={mp.nstr(p[0], 20)} m2={mp.nstr(p[1], 20)} tau={mp.nstr(p[2], 20)} |B|={mp.nstr(nB, 3)} K={mp.nstr(K, 3)} D={mp.nstr(D, 12)}", flush=True)
        if it == iters or nB < mp.mpf(10) ** (-(mp.mp.dps - 6)):
            break
        # finite-difference Jacobian at step 1e-(dps/2)
        hstep = mp.mpf(10) ** (-(mp.mp.dps // 2))
        J = mp.matrix(3, 3)
        for k in range(3):
            dp = mp.matrix([0, 0, 0]); dp[k] = hstep
            qp, vp = integrate(*(p + dp))
            qm, vm = integrate(*(p - dp))
            Bp, _ = hopf_residual(qp, vp, (p + dp)[0], (p + dp)[1])
            Bm, _ = hopf_residual(qm, vm, (p - dp)[0], (p - dp)[1])
            for r in range(3):
                J[r, k] = (Bp[r] - Bm[r]) / (2 * hstep)
        step = mp.lu_solve(J, -mp.matrix(B))
        p = p + step


if __name__ == "__main__":
    main()
