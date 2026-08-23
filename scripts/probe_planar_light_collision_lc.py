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


def postcollision_exit(
    collision: np.ndarray,
    sigma: float,
    primary: int,
    exit_distance: float,
    sigma_span: float,
    tolerance: float,
) -> tuple[float, np.ndarray] | None:
    """Continue the regularized collision-ejection branch to ``|q|=exit_distance``.

    Increasing physical time on the incoming branch corresponds to decreasing
    radial clock, hence to decreasing ``sigma`` in this probe's convention.
    This continuation is only a limiting diagnostic; a positive-mass physical
    collision would terminate.
    """

    def exit_event(_sigma: float, state: np.ndarray) -> float:
        return float(np.dot(state[:2], state[:2]) - exit_distance)

    exit_event.terminal = True
    exit_event.direction = 1
    solution = solve_ivp(
        lambda time, state: lc_field(time, state, primary),
        (sigma, sigma - sigma_span),
        collision,
        method="DOP853",
        rtol=tolerance,
        atol=tolerance / 100.0,
        max_step=0.001,
        events=exit_event,
    )
    if not solution.success:
        raise RuntimeError(solution.message)
    if not solution.t_events[0].size:
        return None
    return float(solution.t_events[0][0]), solution.y_events[0][0]


def outer_state_from_lc(state: np.ndarray, primary: int) -> np.ndarray:
    """Reconstruct ``(Z,Z_t)`` in the decreasing radial-clock convention."""
    u = complex(state[0], state[1])
    v = complex(state[2], state[3])
    radial_time = float(state[5])
    binary_separation = BINARY_SCALE * radial_time ** (2.0 / 3.0)
    binary_speed = (2.0 / 3.0) * BINARY_SCALE * radial_time ** (-1.0 / 3.0)
    relative_position = u * u
    relative_velocity = 2.0 * u * v / abs(u) ** 2
    outer_position = relative_position + primary * binary_separation / 2.0
    outer_velocity = relative_velocity + primary * binary_speed / 2.0
    return np.array(
        [
            outer_position.real,
            outer_position.imag,
            outer_velocity.real,
            outer_velocity.imag,
        ]
    )


def physical_exit_diagnostics(state: np.ndarray, primary: int) -> dict[str, float]:
    """Return radial-clock diagnostics reconstructed from an LC exit state."""
    u = complex(state[0], state[1])
    radial_time = float(state[5])
    binary_separation = BINARY_SCALE * radial_time ** (2.0 / 3.0)
    relative_position = u * u
    outer_state = outer_state_from_lc(state, primary)
    outer_position = complex(outer_state[0], outer_state[1])
    outer_velocity = complex(outer_state[2], outer_state[3])
    distance_plus = abs(outer_position - binary_separation / 2.0)
    distance_minus = abs(outer_position + binary_separation / 2.0)
    outer_energy = (
        abs(outer_velocity) ** 2 / 2.0
        - 1.0 / distance_plus
        - 1.0 / distance_minus
    )
    return {
        "exit_relative_distance": abs(relative_position),
        "exit_other_primary_distance": (
            distance_minus if primary == 1 else distance_plus
        ),
        "exit_outer_radius": abs(outer_position),
        "exit_outer_radial_clock_speed": (
            np.real(np.conj(outer_position) * outer_velocity) / abs(outer_position)
        ),
        "exit_outer_energy": outer_energy,
        "exit_radial_time": radial_time,
        "exit_binary_separation": binary_separation,
    }


def heavy_binary_field(binary_lc: float, state: np.ndarray) -> np.ndarray:
    """Restricted light flow through the prescribed heavy-binary collision."""
    outer_position = complex(state[0], state[1])
    outer_velocity = complex(state[2], state[3])
    binary_separation = BINARY_SCALE * binary_lc**2
    distance_plus = outer_position + binary_separation / 2.0
    distance_minus = outer_position - binary_separation / 2.0
    acceleration = (
        -distance_plus / abs(distance_plus) ** 3
        - distance_minus / abs(distance_minus) ** 3
    )
    clock_factor = 3.0 * binary_lc**2
    return np.array(
        [
            clock_factor * outer_velocity.real,
            clock_factor * outer_velocity.imag,
            clock_factor * acceleration.real,
            clock_factor * acceleration.imag,
        ]
    )


def postbinary_probe(
    lc_exit_state: np.ndarray,
    primary: int,
    lambda_end: float,
    tolerance: float,
) -> tuple[np.ndarray, float]:
    """Continue the limiting light state through the heavy-binary LC zero."""
    lambda_start = float(lc_exit_state[5]) ** (1.0 / 3.0)
    outer_state = outer_state_from_lc(lc_exit_state, primary)
    minimum_separation = np.inf

    def track_separation(_lambda: float, state: np.ndarray) -> float:
        nonlocal minimum_separation
        outer_position = complex(state[0], state[1])
        binary_separation = BINARY_SCALE * _lambda**2
        separation = min(
            abs(outer_position - binary_separation / 2.0),
            abs(outer_position + binary_separation / 2.0),
        )
        minimum_separation = min(minimum_separation, separation)
        return separation - 1e-6

    track_separation.terminal = True
    track_separation.direction = -1
    solution = solve_ivp(
        heavy_binary_field,
        (lambda_start, lambda_end),
        outer_state,
        method="DOP853",
        rtol=tolerance,
        atol=tolerance / 100.0,
        max_step=0.002,
        events=track_separation,
    )
    if not solution.success:
        raise RuntimeError(solution.message)
    if solution.t_events[0].size:
        raise RuntimeError("post-binary probe approached a light-heavy collision")
    return solution.y[:, -1], float(minimum_separation)


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
    parser.add_argument("--postcollision-exit", type=float, default=0.5)
    parser.add_argument("--postcollision-span", type=float, default=20.0)
    parser.add_argument("--postbinary-lambda", type=float)
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
    continuation = postcollision_exit(
        state,
        float(sigma),
        args.primary,
        args.postcollision_exit,
        args.postcollision_span,
        args.tolerance,
    )
    if continuation is None:
        print("postcollision_exit_found=false")
    else:
        exit_sigma, exit_state = continuation
        print("postcollision_exit_found=true")
        print(f"postcollision_exit_sigma={exit_sigma:.15g}")
        for key, value in physical_exit_diagnostics(exit_state, args.primary).items():
            print(f"{key}={value:.15g}")
        if args.postbinary_lambda is not None:
            outer_state, minimum_separation = postbinary_probe(
                exit_state,
                args.primary,
                args.postbinary_lambda,
                args.tolerance,
            )
            outer_position = complex(outer_state[0], outer_state[1])
            outer_velocity = complex(outer_state[2], outer_state[3])
            radial_speed = (
                np.real(np.conj(outer_position) * outer_velocity)
                / abs(outer_position)
            )
            print(f"postbinary_outer_radius={abs(outer_position):.15g}")
            print(f"postbinary_radial_clock_speed={radial_speed:.15g}")
            print(f"postbinary_speed={abs(outer_velocity):.15g}")
            print(f"postbinary_minimum_primary_distance={minimum_separation:.15g}")


if __name__ == "__main__":
    main()
