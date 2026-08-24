#!/usr/bin/env python3
"""Bounded ordinary probe of the conjectural first-syzygy ordering cone.

This script is a falsification aid, not a proof or a parameter survey.
"""

from __future__ import annotations

import argparse
from fractions import Fraction

import numpy as np
from scipy.integrate import solve_ivp

from src.dynamics.cartesian import (
    initial_state_real,
    mutual_distances,
    right_hand_side,
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
            print(
                f"u={parameter} status=FAILED_OR_NO_SYZYGY "
                f"integrated_t={solution.t[-1]:.16g}"
            )
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
        print(
            f"u={parameter} status=ORDINARY_NUMERICAL_EVIDENCE "
            f"first_syzygy={syzygy_time:.16g} "
            f"min_r12_minus_r23={np.min(first_gap):.16g} "
            f"min_r23_minus_r31={np.min(second_gap):.16g} "
            f"max_first_gap_increment={np.max(first_increments):.3e} "
            f"min_second_gap_increment={np.min(second_increments):.3e} "
            f"area_second_range=[{np.min(area_accelerations):.8g},"
            f"{np.max(area_accelerations):.8g}]"
        )


if __name__ == "__main__":
    main()
