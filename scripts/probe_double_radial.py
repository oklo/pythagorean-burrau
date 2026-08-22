#!/usr/bin/env python3
"""Refine one ordinary-numerical double-radial event and test angular slip."""

from __future__ import annotations

import argparse

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import root

from src.dynamics.brake_residual import double_radial_slip_residual
from src.dynamics.cartesian import (
    energy,
    initial_state_real,
    kinetic_energy,
    mutual_distances,
    right_hand_side,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--u", type=float, default=0.29287740)
    parser.add_argument("--time", type=float, default=1.34359722)
    parser.add_argument("--rtol", type=float, default=1e-12)
    parser.add_argument("--atol", type=float, default=1e-14)
    parser.add_argument("--max-step", type=float, default=0.002)
    return parser.parse_args()


def tight_pair_residual(state: np.ndarray, masses: np.ndarray) -> np.ndarray:
    positions = state[:6].reshape(3, 2)
    velocities = state[6:].reshape(3, 2)
    # Jacobi tree based on the tight initial pair (bodies 1 and 3).
    x = positions[2] - positions[0]
    vx = velocities[2] - velocities[0]
    pair_center = (masses[0] * positions[0] + masses[2] * positions[2]) / (
        masses[0] + masses[2]
    )
    pair_velocity = (masses[0] * velocities[0] + masses[2] * velocities[2]) / (
        masses[0] + masses[2]
    )
    y = positions[1] - pair_center
    vy = velocities[1] - pair_velocity
    return double_radial_slip_residual(x, y, vx, vy)


def integrate(u: float, time: float, args: argparse.Namespace, samples: int | None = None):
    masses, state0 = initial_state_real(u)
    evaluation_times = None if samples is None else np.linspace(0, time, samples)
    solution = solve_ivp(
        right_hand_side,
        (0, time),
        state0,
        args=(masses,),
        method="DOP853",
        t_eval=evaluation_times,
        rtol=args.rtol,
        atol=args.atol,
        max_step=args.max_step,
    )
    if not solution.success:
        raise RuntimeError(solution.message)
    return masses, state0, solution


def main() -> None:
    args = parse_args()

    def two_radial_rates(parameters: np.ndarray) -> np.ndarray:
        u, time = parameters
        masses, _, solution = integrate(float(u), float(time), args)
        return tight_pair_residual(solution.y[:, -1], masses)[:2]

    refined = root(two_radial_rates, np.array([args.u, args.time]), method="hybr", tol=1e-9)
    if not refined.success:
        raise SystemExit(refined.message)
    u, time = refined.x
    masses, state0, solution = integrate(float(u), float(time), args, samples=5001)
    final_state = solution.y[:, -1]
    residual = tight_pair_residual(final_state, masses)
    separations = np.array([mutual_distances(state) for state in solution.y.T])
    energies = np.array([energy(state, masses) for state in solution.y.T])
    print(f"u={u:.12g} t={time:.12g}")
    print(f"double_radial_residual={residual[:2]}")
    print(f"angular_slip={residual[2]:.12g}")
    print(f"kinetic_energy={kinetic_energy(final_state, masses):.12g}")
    print(f"prior_minimum_separation={np.min(separations):.12g}")
    relative_energy_error = np.max(np.abs((energies - energy(state0, masses)) / energies[0]))
    print(f"maximum_relative_energy_error={relative_energy_error:.3e}")


if __name__ == "__main__":
    main()

