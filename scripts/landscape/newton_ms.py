#!/usr/bin/env python3
"""Newton continuation from a tied near-brake to a periodic brake orbit in the
two-parameter mass--side family (m1, m2) with brake time t.  Residual: the
complete Hopf brake residual B(m1,m2,t) in R^3 (zero iff labelled brake).
Finite-difference Jacobian.  Ordinary numerics, no validation.
Input lines: u t   (tied parameter and approximate event time)."""
import json, subprocess, sys
import numpy as np

EXE = "./ms3"


def run(m1, m2, t):
    out = subprocess.run([EXE, f"{m1:.17g}", f"{m2:.17g}", f"{t:.17g}"], capture_output=True, text=True).stdout
    return json.loads(out)


def resid(p):
    r = run(*p)
    if "error" in r:
        raise RuntimeError(r["error"])
    return np.array(r["B"]), r


def newton(p0, iters=25, hm=1e-9, ht=1e-9):
    p = np.array(p0, dtype=float)
    hist = []
    for it in range(iters):
        F, r = resid(p)
        nF = np.linalg.norm(F)
        hist.append(nF)
        if nF < 1e-13:
            break
        J = np.zeros((3, 3))
        for k, h in enumerate((hm, hm, ht)):
            dp = np.zeros(3); dp[k] = h
            Fp, _ = resid(p + dp); Fm, _ = resid(p - dp)
            J[:, k] = (Fp - Fm) / (2 * h)
        try:
            step = np.linalg.solve(J, -F)
        except np.linalg.LinAlgError:
            return None
        # damping
        lam = 1.0
        for _ in range(8):
            pn = p + lam * step
            try:
                Fn, _ = resid(pn)
            except RuntimeError:
                lam /= 2; continue
            if np.linalg.norm(Fn) < nF:
                break
            lam /= 2
        p = p + lam * step
    F, r = resid(p)
    return p, np.linalg.norm(F), r, hist, J


if __name__ == "__main__":
    for line in sys.stdin:
        parts = line.split()
        if len(parts) < 2:
            continue
        u, t = float(parts[0]), float(parts[1])
        den = 1 + u * u
        m1, m2 = (1 - u * u) / den, 2 * u / den
        # use the K-min time near t from ms3 as the starting brake time
        r0 = run(m1, m2, t + 0.3)
        t0 = r0["kmin_t"] if r0.get("kmin_t", -1) > 0 and abs(r0["kmin_t"] - t) < 0.3 else t
        try:
            out = newton((m1, m2, t0))
        except Exception as e:
            print(f"u={u:.9f} t={t:.4f}: failed {e}", flush=True); continue
        if out is None:
            print(f"u={u:.9f} t={t:.4f}: singular", flush=True); continue
        p, nF, r, hist, J = out
        D = p[0] ** 2 + p[1] ** 2 - 1
        dist = np.hypot(p[0] - m1, p[1] - m2)
        sv = np.linalg.svd(J, compute_uv=False)
        print(f"u={u:.9f} t0={t0:.4f}: PERIODIC m1={p[0]:.13f} m2={p[1]:.13f} tau={p[2]:.10f} |B|={nF:.1e} D={D:+.3e} dist_from_tied={dist:.2e} rmin={r['rmin']:.1e} u_equiv={p[1]/(1+p[0]):.10f} sigma_min={sv.min():.2e} iters={len(hist)} hist={[f'{h:.1e}' for h in hist[:6]]}", flush=True)
