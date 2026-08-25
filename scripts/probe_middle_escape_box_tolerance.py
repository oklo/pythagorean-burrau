"""Box-width tolerance of the pair-{2,3} terminal checker at candidate times.

For each candidate terminal physical time, integrates the tied trajectory
at several parameters spanning the tile, forms the family hull of the
pair-{2,3} chart state, and bisects the largest uniform symmetric
inflation of that hull that the interval checker still certifies, in both
strict and phase-robust modes.  The inflation is the wrapping budget
available to the validated propagation at that section.

Everything here is ORDINARY NUMERICAL EVIDENCE for proof design.

Usage:
    python scripts/probe_middle_escape_box_tolerance.py CHECKER_BINARY
"""

from __future__ import annotations

import subprocess
import sys

import numpy as np
from scipy.integrate import solve_ivp

from src.dynamics.cartesian import initial_state_real, right_hand_side

U_VALUES = [0.29, 0.29001, 0.29002]
U_BOUNDS = ("29/100", "14501/50000")
TIMES = [4.0, 4.5, 5.0]
NAMES = ["wr", "wi", "zr", "zi", "h", "Gx", "Gy", "Px", "Py"]


def chart_state(t: float, sol, masses: np.ndarray) -> np.ndarray:
    state = sol(t)
    q = state[:6].reshape(3, 2)
    v = state[6:].reshape(3, 2)
    pair_mass = masses[1] + masses[2]
    g = q[2] - q[1]
    gdot = v[2] - v[1]
    center = (masses[1] * q[1] + masses[2] * q[2]) / pair_mass
    center_v = (masses[1] * v[1] + masses[2] * v[2]) / pair_mass
    big_g = q[0] - center
    p = v[0] - center_v
    g_complex = complex(*g)
    w = np.sqrt(g_complex)
    z = np.conj(w) * complex(*gdot) / 2
    h = abs(complex(*gdot)) ** 2 / 2 - pair_mass / abs(g_complex)
    return np.array(
        [w.real, w.imag, z.real, z.imag, h, big_g[0], big_g[1], p[0], p[1]]
    )


def run_checker(binary: str, lo: np.ndarray, hi: np.ndarray,
                use_h: bool = True, phase_robust: bool = False):
    tokens = ["4", *U_BOUNDS]
    for k in (0, 1, 2, 3, 5, 6, 7, 8):  # wr wi zr zi Gx Gy Px Py
        tokens += [f"{lo[k]:.12f}", f"{hi[k]:.12f}"]
    if use_h:
        tokens += [f"{lo[4]:.12f}", f"{hi[4]:.12f}"]
    args = [binary] + (["--phase-robust"] if phase_robust else [])
    proc = subprocess.run(
        args, input=" ".join(tokens), capture_output=True, text=True
    )
    return proc.returncode == 0, proc.stdout.strip().splitlines()[-1]


def main() -> None:
    if len(sys.argv) != 2:
        raise SystemExit(__doc__)
    binary = sys.argv[1]
    print("ORDINARY NUMERICAL EVIDENCE (design only; not a proof)")
    solutions = {}
    for u in U_VALUES:
        masses, state0 = initial_state_real(u)
        solutions[u] = (
            solve_ivp(
                right_hand_side, (0, max(TIMES) + 0.5), state0,
                args=(masses,), method="DOP853", dense_output=True,
                rtol=1e-12, atol=1e-14, max_step=0.01,
            ).sol,
            masses,
        )
    for t in TIMES:
        states = np.array([chart_state(t, *solutions[u]) for u in U_VALUES])
        lo, hi = states.min(axis=0), states.max(axis=0)
        print(f"\n-- terminal time t = {t} --")
        print("family spread over the tile:",
              {n: f"{s:.3e}" for n, s in zip(NAMES, hi - lo, strict=True)})
        for label, kwargs in (
            ("strict", {}),
            ("strict no h", {"use_h": False}),
            ("phase-robust", {"phase_robust": True}),
        ):
            ok, line = run_checker(binary, lo, hi, **kwargs)
            if not ok:
                print(f"  {label}: family hull already fails: {line}")
                continue
            eps_ok, eps_bad = 0.0, 4.0
            for _ in range(40):
                eps = 0.5 * (eps_ok + eps_bad)
                ok, _ = run_checker(binary, lo - eps, hi + eps, **kwargs)
                if ok:
                    eps_ok = eps
                else:
                    eps_bad = eps
            print(f"  {label}: hull passes; max uniform inflation "
                  f"{eps_ok:.4f}")


if __name__ == "__main__":
    main()
