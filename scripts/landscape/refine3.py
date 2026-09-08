#!/usr/bin/env python3
"""Multi-scale zoom refinement of local minima over u of the tied family's
minimal kinetic energy near a tracked K-minimum event.  Ordinary numerics.
Input lines: u0 t0 [K].  Output: refined u*, min K/U0, event data."""
import json, re, subprocess, sys
import numpy as np

EXE = "./tied3j"


def run(u, tmax):
    out = subprocess.run([EXE, f"{u:.17g}", f"{tmax}"], capture_output=True, text=True).stdout
    return json.loads(re.sub(r"-?(nan|inf)", "null", out))


def f_of_u(u, t_target, window=0.15):
    r = run(u, t_target + window + 0.2)
    best = None
    for ev in r["ev"]:
        t, arc, typ, KU, z, Idot, rmin = ev
        if typ != 1 or abs(t - t_target) > window:
            continue
        if best is None or KU < best[0]:
            best = (KU, t, arc, r["Herrmax"], r["rmin"], r["nstut"], r["stut"], r["nsyz"], r["syz"])
    return best


def zoom(u0, t0):
    best = f_of_u(u0, t0)
    if best is None:
        return None
    uc, tc = u0, best[1]
    du = 1e-5
    history = []
    while du > 2e-14:
        us = uc + du * np.linspace(-1, 1, 9)
        vals = []
        for u in us:
            b = f_of_u(u, tc)
            vals.append(b[0] if b is not None else np.inf)
        vals = np.array(vals)
        i = int(np.argmin(vals))
        if np.isfinite(vals[i]) and vals[i] <= best[0]:
            uc = us[i]
            best = f_of_u(uc, tc)
            tc = best[1]
        history.append((du, vals[i]))
        # if the minimum is interior and neighbours finite: parabolic refinement
        if 0 < i < 8 and np.isfinite(vals[i - 1]) and np.isfinite(vals[i + 1]):
            a, b_, c = vals[i - 1], vals[i], vals[i + 1]
            denom = a - 2 * b_ + c
            if denom > 0:
                shift = 0.5 * (a - c) / denom * (du / 4)
                utry = uc + shift
                bt = f_of_u(utry, tc)
                if bt is not None and bt[0] < best[0]:
                    uc, best, tc = utry, bt, bt[1]
        du /= 4
    return uc, best, history


if __name__ == "__main__":
    for line in sys.stdin:
        parts = line.split()
        if len(parts) < 2:
            continue
        u0, t0 = float(parts[0]), float(parts[1])
        try:
            out = zoom(u0, t0)
            if out is None:
                print(f"u0={u0:.6f} t0={t0:.3f}: unresolved", flush=True)
                continue
            uc, best, hist = out
            KU, t, arc, herr, rmin, nstut, stut, nsyz, syz = best
            print(f"u0={u0:.6f} t0={t0:.3f}: u*={uc:.15f} minK/U0={KU:.3e} v~{np.sqrt(2*KU*2.6):.2e} t={t:.6f} arc={arc} nsyz={nsyz} stut={stut} Herrmax={herr:.1e} rmin={rmin:.1e} hist={[(f'{d:.0e}',f'{v:.2e}') for d,v in hist[::2]]}", flush=True)
        except Exception as e:
            print(f"u0={u0} failed: {e}", flush=True)
