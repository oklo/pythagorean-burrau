#!/usr/bin/env python3
"""Ordinary probe of the universal second-encounter triple endpoint.

The limiting heavy binary collides at ``s=1``.  Initial data at ``s=-L``
use the equilateral collision ray, its first relative-collision-time
correction, and the normalized slow transverse mode.  This is diagnostic,
not a validated stable-manifold construction.
"""

from __future__ import annotations

import argparse

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import brentq

BINARY_SCALE = 9 ** (1 / 3)
OUTER_SCALE = np.sqrt(3) * BINARY_SCALE / 2
ALPHA_MINUS = (3 - np.sqrt(7)) / 6
PHASE_CORRECTION = np.sqrt(3) * BINARY_SCALE / 3


def rhs(time: float, state: np.ndarray) -> list[float]:
    height, velocity, transverse, transverse_velocity = state
    separation = BINARY_SCALE * abs(1 - time) ** (2 / 3)
    radius_squared = height**2 + separation**2 / 4
    return [
        velocity,
        -2 * height / radius_squared**1.5,
        transverse_velocity,
        (separation**2 - 2 * height**2)
        * transverse
        / radius_squared**2.5,
    ]


def center_event(_time: float, state: np.ndarray) -> float:
    return float(state[0])


center_event.direction = 1.0
center_event.terminal = True


def turn_event(_time: float, state: np.ndarray) -> float:
    return float(state[1])


turn_event.direction = -1.0
turn_event.terminal = True


def probe(
    cutoff: float, phase_correction_scale: float, max_step: float
) -> tuple[str, tuple[float, ...]]:
    height = (
        -OUTER_SCALE * cutoff ** (2 / 3)
        - phase_correction_scale * PHASE_CORRECTION * cutoff ** (-1 / 3)
    )
    velocity = (
        2 * OUTER_SCALE * cutoff ** (-1 / 3) / 3
        - phase_correction_scale * PHASE_CORRECTION * cutoff ** (-4 / 3) / 3
    )
    transverse = cutoff**ALPHA_MINUS
    transverse_velocity = -ALPHA_MINUS * cutoff ** (ALPHA_MINUS - 1)
    incoming = solve_ivp(
        rhs,
        (-cutoff, 20.0),
        (height, velocity, transverse, transverse_velocity),
        events=center_event,
        rtol=2e-11,
        atol=2e-13,
        max_step=max_step,
    )
    if not incoming.t_events[0].size:
        raise RuntimeError("universal probe did not cross the center")
    center_time = float(incoming.t_events[0][0])
    center_state = incoming.y_events[0][0]
    _, center_speed, center_p, center_p_velocity = center_state
    outgoing = solve_ivp(
        rhs,
        (center_time, center_time + 20.0),
        center_state,
        events=turn_event,
        rtol=2e-11,
        atol=2e-13,
        max_step=max_step,
    )
    if not outgoing.t_events[0].size:
        return (
            "no_turn",
            (
                center_time,
                float(center_speed),
                float(center_p),
                float(center_p_velocity),
                float(outgoing.t[-1]),
                float(outgoing.y[0, -1]),
                float(outgoing.y[2, -1]),
                float("nan"),
            ),
        )
    turn_time = float(outgoing.t_events[0][0])
    turn_height, _, turn_p, turn_p_velocity = outgoing.y_events[0][0]
    turn_wronskian = turn_height * turn_p_velocity
    return (
        "turn",
        (
            center_time,
            float(center_speed),
            float(center_p),
            float(center_p_velocity),
            turn_time,
            float(turn_height),
            float(turn_p),
            float(turn_wronskian),
        ),
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--cutoffs", nargs="+", type=float, default=[100, 300, 1000])
    parser.add_argument("--phase-correction-scales", nargs="+", type=float, default=[1.0])
    parser.add_argument(
        "--shoot-center",
        nargs=2,
        type=float,
        metavar=("LOWER", "UPPER"),
        help="shoot the phase-correction scale so that the center crossing is s=0",
    )
    parser.add_argument("--max-step", type=float, default=0.05)
    args = parser.parse_args()
    print(
        "cutoff correction_scale outcome center_time center_speed center_p center_p_velocity "
        "turn_time turn_height turn_p K_minus"
    )
    for cutoff in args.cutoffs:
        correction_scales = args.phase_correction_scales
        if args.shoot_center:
            lower, upper = args.shoot_center

            def center_residual(
                correction_scale: float, selected_cutoff: float = cutoff
            ) -> float:
                return probe(selected_cutoff, correction_scale, args.max_step)[1][0]

            correction_scales = [
                brentq(center_residual, lower, upper, xtol=2e-11)
            ]
        for correction_scale in correction_scales:
            outcome, values = probe(cutoff, correction_scale, args.max_step)
            print(
                f"{cutoff:.1f} {correction_scale:.8f} {outcome} "
                + " ".join(f"{value:.12e}" for value in values)
            )


if __name__ == "__main__":
    main()
