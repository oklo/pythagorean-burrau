#!/usr/bin/env python3
"""Bounded ordinary probe of the conjectural first-syzygy ordering cone.

This script is a falsification aid, not a proof or a parameter survey.
"""

from __future__ import annotations

import argparse
from fractions import Fraction

import numpy as np
import sympy as sp
from scipy.integrate import solve_ivp

from src.dynamics.cartesian import (
    initial_state_real,
    mutual_distances,
    right_hand_side,
)
from src.symbolic.mutual_distances import (
    envelope_switch_energy_separation,
    ordered_history_lag_reduction,
)


def twice_area(state: np.ndarray) -> float:
    positions = state[:6].reshape(3, 2)
    base = positions[1] - positions[0]
    apex = positions[2] - positions[0]
    return float(base[0] * apex[1] - base[1] * apex[0])


def twice_area_second_derivative(state: np.ndarray, masses: np.ndarray) -> float:
    positions = state[:6].reshape(3, 2)
    velocities = state[6:].reshape(3, 2)
    accelerations = right_hand_side(0.0, state, masses)[6:].reshape(3, 2)
    base = positions[1] - positions[0]
    apex = positions[2] - positions[0]
    base_velocity = velocities[1] - velocities[0]
    apex_velocity = velocities[2] - velocities[0]
    base_acceleration = accelerations[1] - accelerations[0]
    apex_acceleration = accelerations[2] - accelerations[0]

    def cross(left: np.ndarray, right: np.ndarray) -> float:
        return float(left[0] * right[1] - left[1] * right[0])

    return (
        cross(base_acceleration, apex)
        + cross(base, apex_acceleration)
        + 2 * cross(base_velocity, apex_velocity)
    )


def first_syzygy(_time: float, state: np.ndarray, _masses: np.ndarray) -> float:
    return twice_area(state)


first_syzygy.terminal = True
first_syzygy.direction = -1


def instantaneous_torque_rate_ratio(distances: np.ndarray) -> float:
    """Return k=(r23^-3-r12^-3)/(r31^-3-r12^-3)."""
    r12, r23, r31 = distances
    return float((r23**-3 - r12**-3) / (r31**-3 - r12**-3))


def pair_angular_momentum(state: np.ndarray, first: int, second: int) -> float:
    positions = state[:6].reshape(3, 2)
    velocities = state[6:].reshape(3, 2)
    relative_position = positions[second] - positions[first]
    relative_velocity = velocities[second] - velocities[first]
    return float(
        relative_position[0] * relative_velocity[1] - relative_position[1] * relative_velocity[0]
    )


def sign_blocks(values: np.ndarray) -> tuple[int, ...]:
    """Return robust consecutive signs, discarding roundoff-scale values."""
    finite = values[np.isfinite(values)]
    if not finite.size:
        return ()
    tolerance = max(1e-12, 1e-9 * float(np.max(np.abs(finite))))
    signs = np.sign(finite[np.abs(finite) > tolerance]).astype(int)
    if not signs.size:
        return ()
    return tuple(signs[np.r_[True, signs[1:] != signs[:-1]]])


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--u",
        type=Fraction,
        action="append",
        default=None,
        help="repeat for multiple rational parameters",
    )
    parser.add_argument("--samples", type=int, default=2001)
    parser.add_argument("--rtol", type=float, default=2e-12)
    parser.add_argument("--atol", type=float, default=2e-14)
    parser.add_argument("--max-step", type=float, default=2e-4)
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    lag, lag_variables = ordered_history_lag_reduction()
    envelope_function = sp.lambdify(lag_variables, lag["envelope_margin"], "numpy", cse=True)
    separation, separation_variables = envelope_switch_energy_separation()
    gamma_threshold_function = sp.lambdify(
        separation_variables,
        separation["gamma_zero"],
        "numpy",
        cse=True,
    )
    parameters = args.u or [
        Fraction(1, 10),
        Fraction(1, 5),
        Fraction(1, 4),
        Fraction(1, 3),
        Fraction(19, 50),
        Fraction(2, 5),
        Fraction(207, 500),
    ]
    for parameter in parameters:
        u = float(parameter)
        masses, initial = initial_state_real(u)
        solution = solve_ivp(
            right_hand_side,
            (0.0, 2.0),
            initial,
            args=(masses,),
            events=first_syzygy,
            dense_output=True,
            method="DOP853",
            rtol=args.rtol,
            atol=args.atol,
            max_step=args.max_step,
        )
        if not solution.success or not solution.t_events[0].size:
            print(f"u={parameter} status=FAILED_OR_NO_SYZYGY integrated_t={solution.t[-1]:.16g}")
            continue
        syzygy_time = float(solution.t_events[0][0])
        times = np.linspace(0.0, syzygy_time, args.samples)
        states = solution.sol(times).T
        distances = np.array([mutual_distances(state) for state in states])
        first_gap = distances[:, 0] - distances[:, 1]
        second_gap = distances[:, 1] - distances[:, 2]
        first_increments = np.diff(first_gap)
        second_increments = np.diff(second_gap)
        area_accelerations = np.array(
            [twice_area_second_derivative(state, masses) for state in states]
        )
        torque_rate_ratios = np.array([instantaneous_torque_rate_ratio(row) for row in distances])
        torque_rate_increments = np.diff(torque_rate_ratios)
        envelope_margins = np.full(times.shape, np.nan)
        history_ratios = np.full(times.shape, np.nan)
        contraction_ratios = np.full(times.shape, np.nan)
        for index, (state, row) in enumerate(zip(states, distances, strict=True)):
            r12, r23, r31 = row
            ell_23 = pair_angular_momentum(state, 1, 2)
            if abs(ell_23) < 1e-13:
                continue
            ell_31 = pair_angular_momentum(state, 2, 0)
            history_ratio = (masses[0] / masses[1]) * (-ell_31 / ell_23)
            area_ratio = twice_area(state) / r12**2
            amplitude = ell_23 / np.sqrt(r12)
            positions = state[:6].reshape(3, 2)
            velocities = state[6:].reshape(3, 2)
            relative_12 = positions[1] - positions[0]
            velocity_12 = velocities[1] - velocities[0]
            radial_rate = float(np.dot(relative_12, velocity_12) / r12)
            scale_rate = radial_rate * np.sqrt(r12)
            history_ratios[index] = history_ratio
            contraction_ratios[index] = scale_rate * area_ratio / amplitude
            envelope_margins[index] = float(
                envelope_function(
                    masses[0],
                    masses[1],
                    r23 / r12,
                    r31 / r12,
                    history_ratio,
                    area_ratio,
                    amplitude,
                    amplitude**2,
                )
            )
        envelope_blocks = sign_blocks(envelope_margins)
        finite_envelope = envelope_margins[np.isfinite(envelope_margins)]
        switch_margin = np.nan
        for index in range(1, len(envelope_margins)):
            left = envelope_margins[index - 1]
            right = envelope_margins[index]
            if not np.isfinite(left + right) or not left > 0 >= right:
                continue
            fraction = left / (left - right)
            crossing_distances = distances[index - 1] + fraction * (
                distances[index] - distances[index - 1]
            )
            crossing_eta = history_ratios[index - 1] + fraction * (
                history_ratios[index] - history_ratios[index - 1]
            )
            crossing_gamma = contraction_ratios[index - 1] + fraction * (
                contraction_ratios[index] - contraction_ratios[index - 1]
            )
            crossing_r12, crossing_r23, crossing_r31 = crossing_distances
            gamma_threshold = float(
                gamma_threshold_function(
                    masses[0],
                    masses[1],
                    crossing_r23 / crossing_r12,
                    crossing_r31 / crossing_r12,
                    crossing_eta,
                )
            )
            switch_margin = gamma_threshold - crossing_gamma
            break
        print(
            f"u={parameter} status=ORDINARY_NUMERICAL_EVIDENCE "
            f"first_syzygy={syzygy_time:.16g} "
            f"min_r12_minus_r23={np.min(first_gap):.16g} "
            f"min_r23_minus_r31={np.min(second_gap):.16g} "
            f"max_first_gap_increment={np.max(first_increments):.3e} "
            f"min_second_gap_increment={np.min(second_increments):.3e} "
            f"max_torque_rate_ratio_increment="
            f"{np.max(torque_rate_increments):.3e} "
            f"envelope_sign_blocks={envelope_blocks} "
            f"envelope_range=[{np.min(finite_envelope):.8g},"
            f"{np.max(finite_envelope):.8g}] "
            f"envelope_switch_gamma_margin={switch_margin:.8g} "
            f"area_second_range=[{np.min(area_accelerations):.8g},"
            f"{np.max(area_accelerations):.8g}]"
        )


if __name__ == "__main__":
    main()
