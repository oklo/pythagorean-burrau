#!/usr/bin/env python3
"""Ordinary-numerical local continuation of the Li--Liao F30 brake orbit."""

from __future__ import annotations

import argparse

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import root

from src.dynamics.brake_residual import hopf_velocity, jacobi_vectors
from src.dynamics.cartesian import energy, mutual_distances, right_hand_side


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--u", type=float, default=0.5)
    parser.add_argument("--x", type=float, default=0.1446319096)
    parser.add_argument("--y", type=float, default=0.4773197126)
    parser.add_argument("--half-period", type=float, default=12.5809129586 / 2)
    parser.add_argument("--rtol", type=float, default=2e-12)
    parser.add_argument("--atol", type=float, default=2e-14)
    parser.add_argument("--max-step", type=float, default=0.003)
    return parser.parse_args()


def masses_from_u(u: float) -> np.ndarray:
    denominator = 1 + u * u
    return np.array([(1 - u * u) / denominator, 2 * u / denominator, 1.0])


def stop_state(x: float, y: float) -> np.ndarray:
    positions = np.array([[-0.5, 0.0], [0.5, 0.0], [x, y]])
    return np.concatenate([positions.ravel(), np.zeros(6)])


def integrate_endpoint(
    u: float, x: float, y: float, half_period: float, args: argparse.Namespace
):
    masses = masses_from_u(u)
    initial = stop_state(x, y)
    solution = solve_ivp(
        right_hand_side,
        (0, half_period),
        initial,
        args=(masses,),
        method="DOP853",
        rtol=args.rtol,
        atol=args.atol,
        max_step=args.max_step,
        dense_output=True,
    )
    if not solution.success:
        raise RuntimeError(solution.message)
    return masses, initial, solution


def brake_residual(
    u: float, x: float, y: float, half_period: float, args: argparse.Namespace
) -> np.ndarray:
    masses, _, solution = integrate_endpoint(u, x, y, half_period, args)
    endpoint = solution.y[:, -1]
    positions = endpoint[:6].reshape(3, 2)
    velocities = endpoint[6:].reshape(3, 2)
    jacobi_x, jacobi_y = jacobi_vectors(positions, masses)
    velocity_x, velocity_y = jacobi_vectors(velocities, masses)
    return hopf_velocity(jacobi_x, jacobi_y, velocity_x, velocity_y)


def tied_shape(u: float) -> tuple[float, float]:
    masses = masses_from_u(u)
    a, b = masses[:2]
    return (b * b - a * a) / 2, a * b


def main() -> None:
    args = parse_args()

    def residual(parameters: np.ndarray) -> np.ndarray:
        return brake_residual(
            args.u,
            float(parameters[0]),
            float(parameters[1]),
            float(parameters[2]),
            args,
        )

    seed = np.array([args.x, args.y, args.half_period])
    refined = root(residual, seed, method="hybr", tol=2e-9)
    x, y, half_period = refined.x
    masses, initial, solution = integrate_endpoint(args.u, x, y, half_period, args)
    final_residual = residual(refined.x)
    sample_times = np.linspace(0, half_period, 10001)
    sampled_states = solution.sol(sample_times).T
    separations = np.array([mutual_distances(state) for state in sampled_states])
    energies = np.array([energy(state, masses) for state in sampled_states])
    tied_x, tied_y = tied_shape(args.u)
    print(f"root_success={refined.success} message={refined.message}")
    print(f"u={args.u:.12g} masses={masses}")
    print(f"x={x:.12g} y={y:.12g} half_period={half_period:.12g}")
    print(f"brake_residual={final_residual}")
    print(f"tied_shape=({tied_x:.12g}, {tied_y:.12g})")
    print(f"shape_offset=({x - tied_x:.12g}, {y - tied_y:.12g})")
    print(f"shape_offset_norm={np.hypot(x - tied_x, y - tied_y):.12g}")
    print(f"minimum_sampled_separation={np.min(separations):.12g}")
    initial_energy = energy(initial, masses)
    relative_energy_error = np.max(
        np.abs((energies - initial_energy) / initial_energy)
    )
    print(f"maximum_relative_energy_error={relative_energy_error:.3e}")


if __name__ == "__main__":
    main()
