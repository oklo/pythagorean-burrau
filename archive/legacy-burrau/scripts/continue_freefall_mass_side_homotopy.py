#!/usr/bin/env python3
"""Continue one Li--Liao free-fall brake orbit onto the mass--side locus.

At homotopy lambda=0 the last two equations fix the catalog masses.  At
lambda=1 they impose r23=m1 and r31=m2.  The three other equations are the
rotation-reduced second-brake residual.  This is ordinary numerical candidate
generation only.
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
import sys

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import root


MAIN = Path("/Users/greglaughlin/Projects/pythagorean-burrau")
sys.path.insert(0, str(MAIN))

from src.dynamics.brake_residual import hopf_velocity, jacobi_vectors  # noqa: E402
from src.dynamics.cartesian import energy, mutual_distances, right_hand_side  # noqa: E402


CATALOG = {
    1: (0.2061730906, 0.4463433325, 2.6925803371),
    2: (0.2632585995, 0.4021064128, 2.8891085282),
    3: (0.3087699287, 0.2817129610, 2.2526299455),
    4: (0.3064570616, 0.2486099306, 2.3813615017),
    5: (0.2810833582, 0.4016924931, 3.2814736858),
    6: (0.3226484475, 0.1813773910, 1.9623770921),
    7: (0.2687327027, 0.0903053982, 1.9434750648),
    8: (0.3233959420, 0.1697487157, 2.1207316616),
    9: (0.3271831808, 0.2547968571, 2.6280318900),
    10: (0.2899252590, 0.4030770616, 3.6787912077),
    11: (0.3426262070, 0.1830843562, 2.3182580914),
    12: (0.3372214876, 0.2601345660, 2.9032413179),
    13: (0.3339428510, 0.1166303462, 1.9513533175),
    14: (0.3514438378, 0.1374554522, 2.1335770470),
    15: (0.3541926333, 0.1912396242, 2.5272612515),
    16: (0.2137677527, 0.4223425850, 5.8220417242),
    17: (0.3635347723, 0.1483383694, 2.3025570478),
    18: (0.0697898821, 0.3190727633, 6.2973444729),
    19: (0.3326592654, 0.2979880796, 4.4551677666),
    20: (0.0774214943, 0.2835443503, 5.9030069770),
    21: (0.0779210325, 0.3163212877, 6.1187532147),
    22: (0.1428136093, 0.1910273880, 5.3746485278),
    23: (0.0894008417, 0.2215222207, 6.0165906664),
    24: (0.0411868590, 0.1386939050, 5.7982241905),
    25: (0.2645032395, 0.3738186198, 6.4584844333),
    26: (0.0876902685, 0.1043044639, 5.9308332463),
    27: (0.1201933414, 0.4542911576, 9.4434059349),
    28: (0.3461730153, 0.2018360990, 4.1324912323),
    29: (0.1715954664, 0.2463490645, 8.1331787201),
    30: (0.1446319096, 0.4773197126, 12.5809129586),
}


def stop_state(x: float, y: float) -> np.ndarray:
    positions = np.array([[-0.5, 0.0], [0.5, 0.0], [x, y]])
    return np.concatenate([positions.ravel(), np.zeros(6)])


def collision_guard(_time: float, state: np.ndarray, _masses: np.ndarray) -> float:
    """Stop exploratory shooting before an effectively singular passage."""
    distances = mutual_distances(state)
    return float(np.min(distances) - 1e-7)


collision_guard.terminal = True
collision_guard.direction = -1


def integrate(parameters: np.ndarray, *, dense_output: bool = False) -> object:
    x, y, half_period, m1, m2 = map(float, parameters)
    if min(y, half_period, m1, m2) <= 0 or max(abs(x), y, m1, m2) > 5:
        raise ValueError("parameters left physical search box")
    masses = np.array([m1, m2, 1.0])
    solution = solve_ivp(
        right_hand_side,
        (0.0, half_period),
        stop_state(x, y),
        args=(masses,),
        method="DOP853",
        rtol=2e-11,
        atol=2e-13,
        max_step=0.003,
        dense_output=dense_output,
        events=collision_guard,
    )
    if not solution.success or solution.t[-1] < half_period * (1.0 - 1e-10):
        raise RuntimeError(solution.message)
    return solution


def brake(parameters: np.ndarray) -> np.ndarray:
    _, _, _, m1, m2 = map(float, parameters)
    masses = np.array([m1, m2, 1.0])
    endpoint = integrate(parameters).y[:, -1]
    positions = endpoint[:6].reshape(3, 2)
    velocities = endpoint[6:].reshape(3, 2)
    jacobi_x, jacobi_y = jacobi_vectors(positions, masses)
    velocity_x, velocity_y = jacobi_vectors(velocities, masses)
    return hopf_velocity(jacobi_x, jacobi_y, velocity_x, velocity_y)


def homotopy_residual(parameters: np.ndarray, lam: float) -> np.ndarray:
    try:
        brake_value = brake(parameters)
    except (ValueError, RuntimeError, FloatingPointError):
        return np.full(5, 1e4)
    x, y, _, m1, m2 = map(float, parameters)
    _, r23, r31 = mutual_distances(stop_state(x, y))
    constraints = np.array(
        [
            m1 - (1.0 - lam) * 0.6 - lam * r23,
            m2 - (1.0 - lam) * 0.8 - lam * r31,
        ]
    )
    return np.concatenate([brake_value, constraints])


def solve(number: int) -> dict[str, object]:
    x, y, period = CATALOG[number]
    parameters = np.array([x, y, period / 2.0, 0.6, 0.8])
    lam = 0.0
    step = 0.1
    history: list[dict[str, object]] = []

    # First refine the rounded catalog entry on its fixed-mass periodic
    # branch.  Starting the deformation before this correction can make the
    # side forcing dominate the ten-digit catalog shooting error.
    base_solution = root(
        lambda values: homotopy_residual(values, 0.0),
        parameters,
        method="hybr",
        tol=2e-9,
        options={"maxfev": 240, "eps": 1e-6, "factor": 0.2},
    )
    base_residual = homotopy_residual(base_solution.x, 0.0)
    base_norm = float(np.linalg.norm(base_residual, ord=np.inf))
    history.append(
        {
            "lambda": 0.0,
            "step": 0.0,
            "accepted": bool(base_norm < 2e-6),
            "root_success": bool(base_solution.success),
            "residual_inf": base_norm,
        }
    )
    if base_norm < 2e-6:
        parameters = base_solution.x

    while lam < 1.0 - 1e-14:
        target = min(1.0, lam + step)
        solution = root(
            lambda values: homotopy_residual(values, target),
            parameters,
            method="hybr",
            tol=2e-9,
            options={"maxfev": 240, "eps": 1e-6, "factor": 0.2},
        )
        residual = homotopy_residual(solution.x, target)
        norm = float(np.linalg.norm(residual, ord=np.inf))
        physical = min(solution.x[1:]) > 0 and max(abs(solution.x[0]), *solution.x[1:]) < 5
        accepted = bool(norm < 2e-6 and physical)
        history.append(
            {
                "lambda": target,
                "step": step,
                "accepted": accepted,
                "root_success": bool(solution.success),
                "residual_inf": norm,
            }
        )
        if accepted:
            parameters = solution.x
            lam = target
            step = min(0.15, step * 1.35)
        else:
            step *= 0.5
            if step < 0.001:
                break

    final_residual = homotopy_residual(parameters, 1.0)
    result: dict[str, object] = {
        "number": number,
        "lambda_reached": lam,
        "parameters": parameters.tolist(),
        "final_residual": final_residual.tolist(),
        "final_residual_inf": float(np.linalg.norm(final_residual, ord=np.inf)),
        "history": history,
    }
    if lam >= 1.0 - 1e-14:
        x, y, half_period, m1, m2 = parameters
        masses = np.array([m1, m2, 1.0])
        trajectory = integrate(parameters, dense_output=True)
        times = np.linspace(0.0, half_period, 10001)
        states = trajectory.sol(times).T
        separations = np.array([mutual_distances(state) for state in states])
        energies = np.array([energy(state, masses) for state in states])
        initial_energy = energies[0]
        result.update(
            {
                "mass_pythagorean_defect": float(m1 * m1 + m2 * m2 - 1.0),
                "minimum_sampled_separation": float(np.min(separations)),
                "maximum_relative_energy_error": float(
                    np.max(np.abs((energies - initial_energy) / initial_energy))
                ),
            }
        )
    return result


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("number", type=int, choices=sorted(CATALOG))
    parser.add_argument("--output", type=Path)
    args = parser.parse_args()
    result = solve(args.number)
    rendered = json.dumps(result, indent=2)
    print(rendered)
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(rendered + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()
