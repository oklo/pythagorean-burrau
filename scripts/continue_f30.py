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
    parser.add_argument(
        "--method",
        choices=("DOP853", "Radau"),
        default="DOP853",
        help="SciPy integrator used for ordinary shooting",
    )
    parser.add_argument(
        "--solve-mass-side",
        action="store_true",
        help=(
            "continue F30 in both mass ratios and solve mass = opposite side; "
            "report the remaining right-triangle defect"
        ),
    )
    parser.add_argument(
        "--diagnose-jacobian",
        action="store_true",
        help="finite-difference the five-equation mass-side shooting map",
    )
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
        method=args.method,
        rtol=args.rtol,
        atol=args.atol,
        max_step=args.max_step,
        dense_output=True,
    )
    if not solution.success:
        raise RuntimeError(solution.message)
    return masses, initial, solution


def integrate_endpoint_for_masses(
    masses: np.ndarray,
    x: float,
    y: float,
    half_period: float,
    args: argparse.Namespace,
):
    initial = stop_state(x, y)
    solution = solve_ivp(
        right_hand_side,
        (0, half_period),
        initial,
        args=(masses,),
        method=args.method,
        rtol=args.rtol,
        atol=args.atol,
        max_step=args.max_step,
        dense_output=True,
    )
    if not solution.success:
        raise RuntimeError(solution.message)
    return initial, solution


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


def brake_residual_for_masses(
    masses: np.ndarray,
    x: float,
    y: float,
    half_period: float,
    args: argparse.Namespace,
) -> np.ndarray:
    _, solution = integrate_endpoint_for_masses(
        masses, x, y, half_period, args
    )
    endpoint = solution.y[:, -1]
    positions = endpoint[:6].reshape(3, 2)
    velocities = endpoint[6:].reshape(3, 2)
    jacobi_x, jacobi_y = jacobi_vectors(positions, masses)
    velocity_x, velocity_y = jacobi_vectors(velocities, masses)
    return hopf_velocity(jacobi_x, jacobi_y, velocity_x, velocity_y)


def solve_mass_side_member(args: argparse.Namespace) -> None:
    """Ordinary shooting for a nearby periodic mass--side-tied member.

    The base side and third mass are both normalized to one.  The five
    equations are the three second-brake residuals and
    ``r_23=m_1, r_31=m_2``.  The Pythagorean condition is deliberately not
    imposed; its residual is the diagnostic output.
    """

    def residual(parameters: np.ndarray) -> np.ndarray:
        x, y, half_period, m_1, m_2 = map(float, parameters)
        if min(y, half_period, m_1, m_2) <= 0:
            return np.full(5, 1e3)
        masses = np.array([m_1, m_2, 1.0])
        brake = brake_residual_for_masses(
            masses, x, y, half_period, args
        )
        initial = stop_state(x, y)
        _, r_23, r_31 = mutual_distances(initial)
        return np.concatenate([brake, [r_23 - m_1, r_31 - m_2]])

    seed = np.array(
        [args.x, args.y, args.half_period, 0.6, 0.8], dtype=float
    )
    refined = root(residual, seed, method="hybr", tol=2e-9)
    x, y, half_period, m_1, m_2 = refined.x
    masses = np.array([m_1, m_2, 1.0])
    initial, solution = integrate_endpoint_for_masses(
        masses, x, y, half_period, args
    )
    final_residual = residual(refined.x)
    sample_times = np.linspace(0, half_period, 10001)
    sampled_states = solution.sol(sample_times).T
    separations = np.array([mutual_distances(state) for state in sampled_states])
    energies = np.array([energy(state, masses) for state in sampled_states])
    initial_sides = mutual_distances(initial)
    initial_energy = energy(initial, masses)
    relative_energy_error = np.max(
        np.abs((energies - initial_energy) / initial_energy)
    )
    right_defect = m_1 * m_1 + m_2 * m_2 - 1
    geometric_defect = initial_sides[0] ** 2 - (
        initial_sides[1] ** 2 + initial_sides[2] ** 2
    )
    print(f"root_success={refined.success} message={refined.message}")
    print(f"m_1={m_1:.15g} m_2={m_2:.15g} m_3=1")
    print(f"x={x:.12g} y={y:.12g} half_period={half_period:.12g}")
    print(f"five_residual={final_residual}")
    print(f"initial_sides={initial_sides}")
    print(f"mass_pythagorean_defect={right_defect:.12g}")
    print(f"geometric_right_defect={geometric_defect:.12g}")
    print(f"minimum_sampled_separation={np.min(separations):.12g}")
    print(f"maximum_relative_energy_error={relative_energy_error:.3e}")
    if args.diagnose_jacobian:
        jacobian = np.empty((5, 5))
        for column in range(5):
            step = 1e-5 * max(1.0, abs(refined.x[column]))
            forward = refined.x.copy()
            backward = refined.x.copy()
            forward[column] += step
            backward[column] -= step
            jacobian[:, column] = (
                residual(forward) - residual(backward)
            ) / (2 * step)
        singular_values = np.linalg.svd(jacobian, compute_uv=False)
        print(f"shooting_jacobian_singular_values={singular_values}")
        print(f"shooting_jacobian_determinant={np.linalg.det(jacobian):.12g}")


def main() -> None:
    args = parse_args()

    if args.solve_mass_side:
        solve_mass_side_member(args)
        return

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
