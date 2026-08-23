#!/usr/bin/env python3
"""Ordinary regularized probe of the planar limiting light-heavy collision.

This is a deterministic seed generator for a later interval-Newton proof.  It
uses a finite equilateral-tail truncation and ordinary floating-point ODE
integration, so none of its output is a validated collision statement.
"""

import argparse

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import root

from scripts.probe_planar_joint_shape import initial_state, shape_field

BINARY_SCALE = 9.0 ** (1.0 / 3.0)


def lc_field(_sigma: float, state: np.ndarray, primary: int) -> np.ndarray:
    """Forced planar Levi--Civita field in the positive radial clock."""
    u = complex(state[0], state[1])
    v = complex(state[2], state[3])
    energy = state[4]
    radial_time = state[5]
    binary_separation = BINARY_SCALE * radial_time ** (2.0 / 3.0)
    relative_position = u * u
    other_relative = relative_position + primary * binary_separation
    forcing = (
        primary / binary_separation**2
        - other_relative / abs(other_relative) ** 3
    )
    v_derivative = (
        energy * u / 2.0
        + abs(u) ** 2 * np.conj(u) * forcing / 2.0
    )
    energy_derivative = 2.0 * np.real(u * v * np.conj(forcing))
    return np.array(
        [
            v.real,
            v.imag,
            v_derivative.real,
            v_derivative.imag,
            energy_derivative,
            abs(u) ** 2,
        ]
    )


def lc_entry_state(
    kappa: float,
    zeta_start: float,
    zeta_entry: float,
    transverse_sign: float,
    primary: int,
    tolerance: float,
) -> np.ndarray:
    """Propagate the truncated stable tail and lift one principal LC sheet."""
    shape_solution = solve_ivp(
        shape_field,
        (zeta_start, zeta_entry),
        initial_state(kappa, zeta_start, transverse_sign),
        method="DOP853",
        rtol=tolerance,
        atol=tolerance / 100.0,
        max_step=0.005,
    )
    if not shape_solution.success:
        raise RuntimeError(shape_solution.message)
    horizontal, vertical, horizontal_speed, vertical_speed = shape_solution.y[:, -1]
    radial_time = float(np.exp(zeta_entry))
    scale = BINARY_SCALE * radial_time ** (2.0 / 3.0)
    shape_relative = complex(horizontal - primary / 2.0, vertical)
    shape_relative_speed = complex(horizontal_speed, vertical_speed)
    relative_position = scale * shape_relative
    relative_velocity = BINARY_SCALE * radial_time ** (-1.0 / 3.0) * (
        2.0 * shape_relative / 3.0 + shape_relative_speed
    )
    u = np.sqrt(relative_position + 0.0j)
    v = np.conj(u) * relative_velocity / 2.0
    energy = abs(relative_velocity) ** 2 / 2.0 - 1.0 / abs(relative_position)
    return np.array([u.real, u.imag, v.real, v.imag, energy, radial_time])


def collision_state(
    kappa: float,
    sigma: float,
    args: argparse.Namespace,
) -> np.ndarray:
    """Return the LC state at a fixed regularized time."""
    entry = lc_entry_state(
        kappa,
        args.zeta_start,
        args.zeta_entry,
        args.transverse_sign,
        args.primary,
        args.tolerance,
    )
    solution = solve_ivp(
        lambda time, state: lc_field(time, state, args.primary),
        (0.0, sigma),
        entry,
        method="DOP853",
        rtol=args.tolerance,
        atol=args.tolerance / 100.0,
        max_step=0.001,
    )
    if not solution.success:
        raise RuntimeError(solution.message)
    return solution.y[:, -1]


def collision_residual(parameters: np.ndarray, args: argparse.Namespace) -> np.ndarray:
    """Square residual ``(Re u, Im u)`` for ``(kappa, sigma)``."""
    return collision_state(float(parameters[0]), float(parameters[1]), args)[:2]


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--kappa-seed", type=float, default=1.267935)
    parser.add_argument("--sigma-seed", type=float, default=-1.071249)
    parser.add_argument("--zeta-start", type=float, default=10.0)
    parser.add_argument("--zeta-entry", type=float, default=0.3)
    parser.add_argument("--transverse-sign", type=float, default=-1.0)
    parser.add_argument("--primary", choices=(-1, 1), type=int, default=1)
    parser.add_argument("--tolerance", type=float, default=2e-12)
    parser.add_argument("--difference-step", type=float, default=3e-4)
    args = parser.parse_args()

    solution = root(
        lambda parameters: collision_residual(parameters, args),
        np.array([args.kappa_seed, args.sigma_seed]),
        method="hybr",
        tol=1e-10,
    )
    kappa, sigma = solution.x
    state = collision_state(float(kappa), float(sigma), args)
    difference_step = args.difference_step
    upper = collision_state(float(kappa + difference_step), float(sigma), args)[:2]
    lower = collision_state(float(kappa - difference_step), float(sigma), args)[:2]
    parameter_column = (upper - lower) / (2.0 * difference_step)
    time_column = state[2:4]
    determinant = float(np.linalg.det(np.column_stack((parameter_column, time_column))))
    constraint = (
        2.0 * float(np.dot(state[2:4], state[2:4]))
        - 1.0
        - state[4] * float(np.dot(state[:2], state[:2]))
    )
    other_primary_distance = BINARY_SCALE * state[5] ** (2.0 / 3.0)

    print("status=ORDINARY_NUMERICAL_EVIDENCE")
    print(f"solver_success={solution.success}")
    print(f"kappa={kappa:.15g}")
    print(f"sigma={sigma:.15g}")
    print(f"residual_norm={np.linalg.norm(state[:2]):.15g}")
    print(f"determinant={determinant:.15g}")
    print(f"collision_speed={np.linalg.norm(state[2:4]):.15g}")
    print(f"constraint_residual={constraint:.15g}")
    print(f"radial_time={state[5]:.15g}")
    print(f"other_primary_distance={other_primary_distance:.15g}")


if __name__ == "__main__":
    main()
