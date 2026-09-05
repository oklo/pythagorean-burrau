#!/usr/bin/env python3
"""Construction campaign using pair-adaptive analytic-variational shooting."""

import argparse
import json
from pathlib import Path

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import brentq, minimize_scalar

from src.dynamics.brake_residual import hopf_velocity, jacobi_vectors
from src.dynamics.periodic_atlas import cartesian, change_chart, shooting_atlas
from src.dynamics.periodic_shooting import algebra, initial_state, physical_state


def refine(p, lam=1.0, **options):
    p = np.array(p, dtype=float)
    for _ in range(12):
        f, jac, atlas = shooting_atlas(p, lam, **options)
        if max(abs(f)) < 2e-11:
            return p, f, jac, atlas
        correction = np.linalg.solve(jac, -f)
        for fraction in (1.0, 0.5, 0.25, 0.125, 0.0625):
            trial = p + fraction * correction
            if min(trial[1:]) <= 0:
                continue
            ft, _, _ = shooting_atlas(trial, lam, variational=False, **options)
            if np.linalg.norm(ft) < np.linalg.norm(f):
                p = trial
                break
        else:
            raise RuntimeError(f"atlas Newton stalled: {f}")
    raise RuntimeError("atlas Newton iteration budget")


def diagnostics(p, atlas):
    masses = np.r_[p[3:], 1.0]
    minima = {pair: {"distance": float("inf")} for pair in ("12", "23", "13")}
    energies, angular, syzygies = [], [], []
    for pair, sol in atlas["segments"]:
        grid = np.unique(np.r_[sol.t, np.linspace(0, sol.t[-1], 4001)])
        states = sol.sol(grid)[:10]
        q, v = physical_state(states, masses, pair)
        energy = 0.5 * np.sum(masses[:, None] * abs(v) ** 2, axis=0)
        for i, j, name in ((0, 1, "12"), (1, 2, "23"), (0, 2, "13")):
            ds = abs(q[j] - q[i])
            energy -= masses[i] * masses[j] / ds
            candidates = [(float(ds[0]), 0.0), (float(ds[-1]), float(grid[-1]))]
            for k in np.where((ds[1:-1] < ds[:-2]) & (ds[1:-1] < ds[2:]))[0] + 1:

                def distance(s, sol=sol, pair=pair, i=i, j=j):
                    qs, _ = physical_state(sol.sol(s)[:10], masses, pair)
                    return abs(qs[j] - qs[i])

                fit = minimize_scalar(
                    distance,
                    bounds=(grid[k - 1], grid[k + 1]),
                    method="bounded",
                    options={"xatol": 1e-15},
                )
                candidates.append((float(fit.fun), float(fit.x)))
            d, s = min(candidates)
            if d < minima[name]["distance"]:
                minima[name] = {"distance": d, "time": float(sol.sol(s)[9]), "chart": pair}
        energies.extend(energy.tolist())
        angular.extend(np.sum(masses[:, None] * np.imag(np.conj(q) * v), axis=0).tolist())
        area = np.imag(np.conj(q[1] - q[0]) * (q[2] - q[0]))
        for k in np.where(area[:-1] * area[1:] < 0)[0]:

            def syzygy(s, sol=sol, pair=pair):
                qs, _ = physical_state(sol.sol(s)[:10], masses, pair)
                return np.imag(np.conj(qs[1] - qs[0]) * (qs[2] - qs[0]))

            s = brentq(syzygy, grid[k], grid[k + 1], xtol=5e-15)
            qs, _ = physical_state(sol.sol(s)[:10], masses, pair)
            projection = np.real((qs - qs[0]) * np.conj(qs[1] - qs[0]))
            syzygies.append(
                {"time": float(sol.sol(s)[9]), "middle_label": int(np.argsort(projection)[1] + 1)}
            )
    q, v = cartesian(atlas["state"], masses, atlas["pair"])
    X, Y = jacobi_vectors(q, masses)
    VX, VY = jacobi_vectors(v, masses)
    return {
        "half_period": float(p[2]),
        "endpoint_chart": atlas["pair"],
        "hopf_brake": hopf_velocity(X, Y, VX, VY).tolist(),
        "labelled_endpoint_velocities": v.tolist(),
        "minimum_separations_ordinary": minima,
        "maximum_sampled_relative_energy_error": float(
            max(abs(np.array(energies) / energies[0] - 1))
        ),
        "maximum_sampled_angular_momentum_error": float(max(abs(np.array(angular)))),
        "half_orbit_syzygies": syzygies,
        "chart_switches": atlas["switches"],
    }


def record(number, p, f, jac, atlas):
    left, sv, right = np.linalg.svd(jac)
    return {
        "number": number,
        "input_status": "decimal seed and ordinary floating-point root",
        "free_group_word": "not reconstructed; labelled syzygies recorded separately",
        "collision_free_certified": False,
        "parameters": p.tolist(),
        "initial_sides_12_23_13": [
            1.0,
            float(np.hypot(p[0] - 0.5, p[1])),
            float(np.hypot(p[0] + 0.5, p[1])),
        ],
        "native_residual": f.tolist(),
        "jacobian": jac.tolist(),
        "singular_values": sv.tolist(),
        "smallest_right_vector": right[-1].tolist(),
        "smallest_left_vector": left[:, -1].tolist(),
        "right_defect": float(p[3] ** 2 + p[4] ** 2 - 1),
        "connected_tied_branch_proved": False,
        "rational_reconstruction": "not attempted: nonzero right defect",
        **diagnostics(p, atlas),
    }


def independent_checks(p, atlas):
    """Implicit-method replay and reverse all regularized segments."""
    rf, _, ra = shooting_atlas(
        p, method="Radau", variational=False, rtol=3e-13, atol=3e-15, max_step=0.02
    )
    state, pair = atlas["state"].copy(), atlas["pair"]
    for segment_pair, forward in reversed(atlas["segments"]):
        state = change_chart(np.r_[state, p[3:]], pair, segment_pair)
        field = algebra(segment_pair)[0]
        reverse = solve_ivp(
            lambda _s, value, field=field: np.asarray(field(*value, *p[3:])).ravel(),
            (0.0, -forward.t[-1]),
            state,
            method="DOP853",
            rtol=2.3e-14,
            atol=2e-16,
            max_step=0.015,
        )
        if not reverse.success:
            raise RuntimeError(reverse.message)
        state, pair = reverse.y[:, -1], segment_pair
    masses = np.r_[p[3:], 1.0]
    q, v = cartesian(state, masses, pair)
    initial, _ = cartesian(initial_state(p, "12"), masses, "12")
    return {
        "Radau_native_residual": rf.tolist(),
        "Radau_labelled_velocities": cartesian(ra["state"], masses, ra["pair"])[1].tolist(),
        "reverse_position_error_inf": float(np.max(abs(q - initial))),
        "reverse_velocity_error_inf": float(np.max(abs(v))),
        "reverse_physical_clock_error": float(abs(state[9])),
    }


def continue_branch(seed, history, options):
    p, lam = np.array(seed["parameters"]), seed["lambda"]
    p, f, jac, atlas = refine(p, lam, **options)
    scale = np.array([1, 1, p[2], 1, 1, 1])
    v = np.r_[p, lam] / scale
    previous = np.array([0, 0, 0, 0, 0, 1.0])
    ds = 0.025

    def evaluate(v):
        p = v[:5] * scale[:5]
        f, j, atlas = shooting_atlas(p, v[5], **options)
        x, y = p[:2]
        dl = [0, 0, 0, 0.6 - np.hypot(x - 0.5, y), 0.8 - np.hypot(x + 0.5, y)]
        return f, np.c_[j, dl] * scale[None, :], atlas

    f, derivative, atlas = evaluate(v)
    prior_word = [e["middle_label"] for e in diagnostics(p, atlas)["half_orbit_syzygies"]]
    for step in range(100):
        tangent = np.linalg.svd(derivative, full_matrices=True)[2][-1]
        if tangent @ previous < 0:
            tangent *= -1
        predictor = v + ds * tangent
        trial = predictor.copy()
        accepted = False
        for _iteration in range(10):
            try:
                ft, jt, at = evaluate(trial)
            except (ValueError, RuntimeError):
                break
            aug = np.r_[ft, tangent @ (trial - predictor)]
            if max(abs(aug)) < 2e-11:
                accepted = True
                break
            correction = np.linalg.solve(np.vstack([jt, tangent]), -aug)
            if np.linalg.norm(correction) > 3 * ds:
                break
            trial += correction
        if not accepted:
            ds *= 0.5
            if ds < 2e-5:
                raise RuntimeError("arclength step floor")
            continue
        old = v
        v, f, derivative, atlas = trial, ft, jt, at
        p = v[:5] * scale[:5]
        audit = diagnostics(p, atlas)
        word = [e["middle_label"] for e in audit["half_orbit_syzygies"]]
        history.append(
            {
                "lambda": float(v[5]),
                "parameters": p.tolist(),
                "residual_inf": float(max(abs(f))),
                "lambda_tangent": float(tangent[5]),
                "fixed_lambda_scaled_singular_values": np.linalg.svd(
                    derivative[:, :5], compute_uv=False
                ).tolist(),
                "right_defect": float(p[3] ** 2 + p[4] ** 2 - 1),
                **audit,
            }
        )
        print(f"F{seed['number']} arc {step}: lambda={v[5]:.8f}", flush=True)
        if word != prior_word:
            raise RuntimeError("sampled syzygy itinerary changed")
        if min(e["distance"] for e in audit["minimum_separations_ordinary"].values()) < 1e-8:
            raise RuntimeError("unresolved close encounter")
        if (old[5] - 1) * (v[5] - 1) <= 0:
            fraction = (1 - old[5]) / (v[5] - old[5])
            return refine((old + fraction * (v - old))[:5] * scale[:5], **options)
        previous = tangent
        ds = min(0.05, ds * 1.25)
    raise RuntimeError("arclength step budget")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path, default=Path("data/periodic_atlas_campaign.json"))
    parser.add_argument("--numbers", type=int, nargs="+", default=[1, 2, 5, 30, 3, 4])
    args = parser.parse_args()
    seeds = json.loads(Path("data/periodic_construction_seeds.json").read_text())
    stalled = json.loads(Path("data/periodic_stalled_seeds.json").read_text())
    result = {
        "evidence": "ORDINARY NUMERICAL EVIDENCE",
        "counterexample_found": False,
        "parameters": ["x", "y", "physical half-period", "m1", "m2"],
        "residual": ["zr", "zi", "G dot P", "m1-r23", "m2-r31"],
        "candidates": [],
        "failures": [],
    }
    options = dict(rtol=3e-13, atol=3e-15, max_step=0.03)
    for number in args.numbers:
        history = []
        try:
            if number in (3, 4):
                seed = next(s for s in stalled if s["number"] == number)
                p, f, jac, atlas = continue_branch(seed, history, options)
            else:
                seed = next(s for s in seeds if s["number"] == number)
                p, f, jac, atlas = refine(seed["parameters"], **options)
            row = record(number, p, f, jac, atlas)
            row["continuation_history"] = history
            # Tight replay and a different start chart test the same physical root.
            pt, ft, jt, at = refine(p, rtol=2.3e-14, atol=2e-16, max_step=0.015, start_pair="13")
            row["tight_alternate_start_chart"] = {
                "parameters": pt.tolist(),
                "parameter_difference": (pt - p).tolist(),
                "native_residual": ft.tolist(),
                "relative_jacobian_difference": float(
                    np.linalg.norm(jt - jac) / np.linalg.norm(jac)
                ),
                "right_defect": float(pt[3] ** 2 + pt[4] ** 2 - 1),
            }
            row["independent_checks"] = independent_checks(p, atlas)
            result["candidates"].append(row)
            print(
                f"F{number}: D={row['right_defect']:.12g}, "
                f"smin={row['singular_values'][-1]:.8g}, residual={max(abs(f)):.3g}",
                flush=True,
            )
        except (ValueError, RuntimeError, np.linalg.LinAlgError) as error:
            result["failures"].append({"number": number, "error": str(error), "history": history})
            print(f"F{number}: {error}", flush=True)
        args.output.write_text(json.dumps(result, indent=2) + "\n")


if __name__ == "__main__":
    main()
