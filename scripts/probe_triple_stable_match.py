#!/usr/bin/env python3
"""Ordinary collision-stable/parabolic match at the triple endpoint.

This diagnostic shoots the one-parameter collision-stable base family
backward from the final equilateral triple collision.  It matches the base
to finite-cutoff incoming zero-energy data and resolves the returned Jost
field into the two collision Frobenius modes.  All cutoff and local-tail
errors are unvalidated; the output is a target for a later interval proof.
"""

from __future__ import annotations

import argparse

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import brentq

from scripts.probe_restricted_turn_map import separatrix_scattering

EQUILATERAL_SHAPE = -np.sqrt(3.0) / 2.0
SHAPE_EXPONENT = (-1.0 + np.sqrt(19.0)) / 4.0
BETA_MINUS = (3.0 - np.sqrt(7.0)) / 4.0
BETA_PLUS = (3.0 + np.sqrt(7.0)) / 4.0


def qhat(shape: float) -> float:
    return (1.0 - 2.0 * shape**2) / (shape**2 + 0.25) ** 2.5


def fuchsian_rhs(x: float, state: np.ndarray) -> np.ndarray:
    """Final-infall equations in x=-log(r), including two field modes."""
    radius = np.exp(-x)
    shape, shape_x, p_minus, p_minus_x, p_plus, p_plus_x = state
    shape_force = shape * ((shape**2 + 0.25) ** -1.5 - 1.0)
    denominator = 2.0 * (1.0 - radius)
    return np.array(
        [
            shape_x,
            ((1.0 - 2.0 * radius) * shape_x - shape_force) / denominator,
            p_minus_x,
            (0.5 * qhat(shape) * p_minus - (3.0 - 2.0 * radius) * p_minus_x)
            / denominator,
            p_plus_x,
            (0.5 * qhat(shape) * p_plus - (3.0 - 2.0 * radius) * p_plus_x)
            / denominator,
        ]
    )


def shoot_to_cutoff(
    amplitude: float,
    cutoff: float,
    x_start: float,
    match_radius: float,
    phase_span: float,
    max_step: float,
) -> tuple[float, np.ndarray]:
    """Shoot one collision-stable state backward to z=-cutoff."""
    radius_start = np.exp(-x_start)
    perturbation = amplitude * radius_start**SHAPE_EXPONENT
    initial = np.array(
        [
            EQUILATERAL_SHAPE + perturbation,
            -SHAPE_EXPONENT * perturbation,
            radius_start**BETA_MINUS,
            -BETA_MINUS * radius_start**BETA_MINUS,
            radius_start**BETA_PLUS,
            -BETA_PLUS * radius_start**BETA_PLUS,
        ]
    )
    x_match = -np.log(match_radius)
    local = solve_ivp(
        fuchsian_rhs,
        (x_start, x_match),
        initial,
        rtol=2e-11,
        atol=2e-13,
        max_step=max_step,
    )
    if not local.success:
        raise RuntimeError(f"Fuchsian shoot failed: {local.message}")
    shape, shape_x, p_minus, p_minus_x, p_plus, p_plus_x = local.y[:, -1]
    phase_match = np.arccos(np.sqrt(match_radius))
    radial_velocity = -2.0 * np.sqrt((1.0 - match_radius) / match_radius)
    state_match = np.array(
        [
            match_radius * shape,
            radial_velocity * (shape - shape_x),
            p_minus,
            -radial_velocity * p_minus_x / match_radius,
            p_plus,
            -radial_velocity * p_plus_x / match_radius,
        ]
    )

    def rhs(phase: float, state: np.ndarray) -> np.ndarray:
        radius = np.cos(phase) ** 2
        z, velocity, pm, qm, pp, qp = state
        radius_squared = z**2 + radius**2 / 4.0
        coefficient = (radius**2 - 2.0 * z**2) / radius_squared**2.5
        return np.array(
            [
                velocity * radius,
                -2.0 * z * radius / radius_squared**1.5,
                qm * radius,
                coefficient * pm * radius,
                qp * radius,
                coefficient * pp * radius,
            ]
        )

    def cutoff_event(_phase: float, state: np.ndarray) -> float:
        return float(state[0] + cutoff)

    cutoff_event.terminal = True
    cutoff_event.direction = 0.0
    global_part = solve_ivp(
        rhs,
        (phase_match, phase_match - phase_span),
        state_match,
        events=cutoff_event,
        rtol=2e-11,
        atol=2e-13,
        max_step=max_step,
    )
    if not global_part.success or not global_part.t_events[0].size:
        raise RuntimeError("backward shoot did not reach the incoming cutoff")
    return float(global_part.t_events[0][0]), global_part.y_events[0][0]


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--cutoff", type=float, default=40.0)
    parser.add_argument("--x-start", type=float, default=24.0)
    parser.add_argument("--match-radius", type=float, default=0.2)
    parser.add_argument("--phase-span", type=float, default=10000.0)
    parser.add_argument("--max-step", type=float, default=0.02)
    parser.add_argument("--derivative-step", type=float, default=1e-6)
    parser.add_argument(
        "--amplitude-bracket",
        nargs=2,
        type=float,
        default=[-0.25, -0.245],
    )
    args = parser.parse_args()

    scattering = separatrix_scattering(args.cutoff, args.max_step)
    outgoing_p = scattering[3]
    scattering_wronskian = scattering[5]
    gamma = outgoing_p / args.cutoff + scattering_wronskian / np.sqrt(args.cutoff)

    def residual(amplitude: float) -> float:
        phase, state = shoot_to_cutoff(
            amplitude,
            args.cutoff,
            args.x_start,
            args.match_radius,
            args.phase_span,
            args.max_step,
        )
        radius = np.cos(phase) ** 2
        target_speed = np.sqrt(4.0 / np.sqrt(args.cutoff**2 + radius**2 / 4.0))
        return float(state[1] - target_speed)

    lower, upper = args.amplitude_bracket
    lower_residual = residual(lower)
    upper_residual = residual(upper)
    print(
        f"bracket=[{lower:.12e},{upper:.12e}] "
        f"residuals=[{lower_residual:.12e},{upper_residual:.12e}]"
    )
    amplitude = brentq(residual, lower, upper, xtol=2e-11)
    residual_derivative = (
        residual(amplitude + args.derivative_step)
        - residual(amplitude - args.derivative_step)
    ) / (2.0 * args.derivative_step)
    phase, state = shoot_to_cutoff(
        amplitude,
        args.cutoff,
        args.x_start,
        args.match_radius,
        args.phase_span,
        args.max_step,
    )
    z, velocity, p_minus, q_minus, p_plus, q_plus = state
    target_p = gamma * args.cutoff + scattering_wronskian * np.sqrt(args.cutoff)
    target_q = (
        -gamma - scattering_wronskian / (2.0 * np.sqrt(args.cutoff))
    ) * velocity
    connection = np.array([[p_minus, p_plus], [q_minus, q_plus]])
    coefficients = np.linalg.solve(connection, np.array([target_p, target_q]))
    response_columns = np.linalg.solve(
        connection,
        np.array(
            [
                [args.cutoff, np.sqrt(args.cutoff)],
                [-velocity, -velocity / (2.0 * np.sqrt(args.cutoff))],
            ]
        ),
    )
    print(
        f"amplitude={amplitude:.12e} phase_mod_pi={np.remainder(phase, np.pi):.12e} "
        f"z={z:.12e} velocity={velocity:.12e} "
        f"finite_cutoff_residual_derivative={residual_derivative:.12e}"
    )
    print(
        f"gamma={gamma:.12e} W={scattering_wronskian:.12e} "
        f"A_minus={coefficients[0]:.12e} A_plus={coefficients[1]:.12e}"
    )
    print(
        f"A_minus_gamma_response={response_columns[0, 0]:.12e} "
        f"A_minus_W_response={response_columns[0, 1]:.12e}"
    )
    print(
        "connection="
        f"[[{p_minus:.12e},{p_plus:.12e}],"
        f"[{q_minus:.12e},{q_plus:.12e}]]"
    )


if __name__ == "__main__":
    main()
