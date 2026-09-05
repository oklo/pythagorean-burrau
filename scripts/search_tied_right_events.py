#!/usr/bin/env python3
"""Seek second brakes on local I-maximum branches of the exact tied-right family.

The six mass-side periodic candidates supply local branch seeds. We solve I'=0
in time, then minimize the complete mass-weighted velocity on that event branch.
No rational reconstruction is warranted unless the real residual vanishes.
"""

import argparse
import json
from pathlib import Path

import numpy as np
from scipy.optimize import least_squares

from src.dynamics.periodic_atlas import cartesian, integrate_atlas, local_jacobian


def tied_parameters(u, tau):
    a, b = (1 - u * u) / (1 + u * u), 2 * u / (1 + u * u)
    da, db = -4 * u / (1 + u * u) ** 2, 2 * (1 - u * u) / (1 + u * u) ** 2
    p = np.array([(b * b - a * a) / 2, a * b, tau, a, b])
    derivative = np.array([b * db - a * da, da * b + a * db, 0, da, db])
    return p, derivative


def event_point(u, tau, reference_tau, options):
    """Newton solve of the nearby strict I maximum; reject lost branches."""
    for _ in range(12):
        p, pu = tied_parameters(u, tau)
        state, tangent, pair, segments, switches = integrate_atlas(p, **options)
        masses = np.r_[p[3:], 1.0]
        q, v = cartesian(state, masses, pair)
        kinetic = 0.5 * np.sum(masses[:, None] * v * v)
        potential = sum(
            masses[i] * masses[j] / np.linalg.norm(q[j] - q[i]) for i, j in ((0, 1), (1, 2), (0, 2))
        )
        iprime = 2 * np.sum(masses[:, None] * q * v)
        isecond = 4 * kinetic - 2 * potential
        if isecond >= 0:
            raise RuntimeError("left the strict I-maximum branch")
        if abs(iprime) < 2e-11:
            break
        correction = np.clip(iprime / isecond, -0.03, 0.03)
        tau -= correction
        if abs(tau - reference_tau) > 0.3 * reference_tau:
            raise RuntimeError("event time left the seeded local window")
    else:
        raise RuntimeError("I-maximum Newton iteration budget")
    inputs = np.r_[state, p[3:]]

    def observables(values):
        masses = np.r_[values[10:], 1.0]
        q, v = cartesian(values[:10], masses, pair)
        return np.r_[2 * np.sum(masses[:, None] * q * v), (np.sqrt(masses[:, None]) * v).ravel()]

    gradient = local_jacobian(observables, inputs)
    derivative = gradient[:, :10] @ tangent
    derivative[:, 3:] += gradient[:, 10:]
    partial_u = derivative @ pu
    dtdu = -partial_u[0] / isecond
    residual = (np.sqrt(masses[:, None]) * v).ravel()
    along = partial_u[1:] + derivative[1:, 2] * dtdu
    return (
        residual,
        along,
        {
            "u": float(u),
            "half_period": float(tau),
            "kinetic_energy": float(kinetic),
            "I_prime": float(iprime),
            "I_second": float(isecond),
            "dt_du": float(dtdu),
            "labelled_velocities": v.tolist(),
            "chart_switches": switches,
        },
    )


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--numbers", type=int, nargs="+", default=[1, 2, 5, 30, 3, 4])
    parser.add_argument("--output", type=Path, default=Path("data/tied_right_event_search.json"))
    args = parser.parse_args()
    seeds = json.loads(Path("data/periodic_atlas_campaign.json").read_text())["candidates"]
    result = {
        "evidence": "ORDINARY NUMERICAL EVIDENCE",
        "counterexample_found": False,
        "scope": "local I-maximum branches seeded by mass-side periodic candidates",
        "results": [],
    }
    for number in args.numbers:
        seed = next(s for s in seeds if s["number"] == number)
        _, _, tau, a, b = seed["parameters"]
        u0 = b / (np.hypot(a, b) + a)
        cache = {}
        history = []

        def evaluate(values, cache=cache, tau=tau, history=history):
            u = float(values[0])
            if u not in cache:
                f, j, row = event_point(u, tau, tau, dict(rtol=3e-13, atol=3e-15, max_step=0.03))
                cache[u] = (f, j, row)
                history.append(row)
            return cache[u]

        try:
            fit = least_squares(
                lambda u: evaluate(u)[0],
                [u0],
                jac=lambda u: evaluate(u)[1][:, None],
                bounds=([u0 - 0.02], [u0 + 0.02]),
                xtol=3e-12,
                ftol=3e-12,
                gtol=3e-12,
                max_nfev=30,
            )
            f, _, row = evaluate(fit.x)
            row = dict(row)
            row.update(
                {
                    "number": number,
                    "optimizer_success": bool(fit.success),
                    "optimizer_message": fit.message,
                    "weighted_speed_norm": float(np.linalg.norm(f)),
                    "seed_u": float(u0),
                    "history": history,
                    "real_brake_candidate": bool(np.linalg.norm(f) < 1e-8),
                    "rational_reconstruction": (
                        "requires high-precision investigation before rational reconstruction"
                        if np.linalg.norm(f) < 1e-8
                        else "not attempted: nonzero real brake residual"
                    ),
                }
            )
            # Tight independent replay at the frozen optimal real parameter.
            tight, _, tr = event_point(
                row["u"],
                row["half_period"],
                tau,
                dict(rtol=2.3e-14, atol=2e-16, max_step=0.015, start_pair="13"),
            )
            row["tight_replay"] = {
                **tr,
                "weighted_speed_norm": float(np.linalg.norm(tight)),
                "velocity_residual_difference": float(np.linalg.norm(tight - f)),
            }
            result["results"].append(row)
            print(
                f"F{number}: u={row['u']:.12g} K={row['kinetic_energy']:.8g} "
                f"speed={row['weighted_speed_norm']:.8g}",
                flush=True,
            )
        except (ValueError, RuntimeError) as error:
            result["results"].append({"number": number, "error": str(error), "history": history})
            print(f"F{number}: {error}", flush=True)
        args.output.write_text(json.dumps(result, indent=2) + "\n")


if __name__ == "__main__":
    main()
