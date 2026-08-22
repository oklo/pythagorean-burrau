#!/usr/bin/env python3
"""Small ordinary-numerical probe; never a proof or catalog survey."""

from __future__ import annotations

import argparse
from fractions import Fraction

import numpy as np
from scipy.integrate import solve_ivp

from src.dynamics.brake_residual import hopf_velocity, jacobi_vectors
from src.dynamics.cartesian import (
    energy,
    initial_state,
    mutual_distances,
    pythagorean_defect,
    right_hand_side,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--u", type=Fraction, default=Fraction(1, 3))
    parser.add_argument("--t-end", type=float, default=20.0)
    parser.add_argument("--samples", type=int, default=10001)
    parser.add_argument("--rtol", type=float, default=1e-11)
    parser.add_argument("--atol", type=float, default=1e-13)
    parser.add_argument("--max-step", type=float, default=0.01)
    parser.add_argument("--brake-skip", type=float, default=0.5)
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    masses, state0 = initial_state(args.u)
    times = np.linspace(0, args.t_end, args.samples)
    solution = solve_ivp(
        right_hand_side,
        (0, args.t_end),
        state0,
        args=(masses,),
        method="DOP853",
        t_eval=times,
        rtol=args.rtol,
        atol=args.atol,
        max_step=args.max_step,
    )
    defects = np.array([pythagorean_defect(state) for state in solution.y.T])
    separations = np.array([mutual_distances(state) for state in solution.y.T])
    energies = np.array([energy(state, masses) for state in solution.y.T])
    residuals = []
    for state in solution.y.T:
        positions = state[:6].reshape(3, 2)
        velocities = state[6:].reshape(3, 2)
        x, y = jacobi_vectors(positions, masses)
        vx, vy = jacobi_vectors(velocities, masses)
        residuals.append(np.linalg.norm(hopf_velocity(x, y, vx, vy)))
    residuals_array = np.asarray(residuals)
    positive_time = solution.t > min(args.brake_skip, args.t_end / 2)
    print(f"success={solution.success} message={solution.message}")
    print(f"u={args.u} integrated_t={solution.t[-1]:.16g}")
    print(f"minimum_separation={np.min(separations):.16g}")
    print(f"defect_range=[{np.min(defects):.16g}, {np.max(defects):.16g}]")
    initially_positive = np.flatnonzero(defects > 1e-10)
    if initially_positive.size:
        negative_after_launch = np.flatnonzero(
            (np.arange(defects.size) > initially_positive[0]) & (defects < 0)
        )
        if negative_after_launch.size:
            crossing_index = negative_after_launch[0]
            prefix_energy_error = np.max(
                np.abs((energies[: crossing_index + 1] - energies[0]) / energies[0])
            )
            print(
                "first_sampled_negative_defect="
                f"{defects[crossing_index]:.16g} at t={solution.t[crossing_index]:.16g}; "
                f"prior_minimum_separation={np.min(separations[: crossing_index + 1]):.16g}; "
                f"prior_maximum_relative_energy_error={prefix_energy_error:.3e}"
            )
    if np.any(positive_time):
        selected = np.flatnonzero(positive_time)
        index = selected[np.argmin(residuals_array[positive_time])]
        print(
            "smallest_sampled_brake_residual="
            f"{residuals_array[index]:.16g} at t={solution.t[index]:.16g}"
        )
    relative_energy_error = np.max(np.abs((energies - energies[0]) / energies[0]))
    print(f"maximum_relative_energy_error={relative_energy_error:.3e}")


if __name__ == "__main__":
    main()
