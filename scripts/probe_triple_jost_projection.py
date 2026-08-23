#!/usr/bin/env python3
"""Ordinary probe of the returned-Jost projection near triple collision.

This uses finite incoming-cutoff scattering data and a phase strictly below
the triple endpoint. It is diagnostic only; no displayed coefficient is a
validated enclosure or an exact endpoint value.
"""

from __future__ import annotations

import argparse

import numpy as np
from scipy.integrate import solve_ivp

from scripts.probe_restricted_turn_map import (
    separatrix_scattering,
    variational_rhs,
)


def center_event(_phase: float, state: np.ndarray) -> float:
    return float(state[0])


center_event.direction = 1.0
center_event.terminal = True


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--cutoff", type=float, default=40.0)
    parser.add_argument("--phase", type=float, default=2.77)
    parser.add_argument("--phase-span", type=float, default=10000.0)
    parser.add_argument("--max-step", type=float, default=0.02)
    parser.add_argument(
        "--sections", nargs="+", type=float, default=[0.2, 0.1, 0.05, 0.02]
    )
    args = parser.parse_args()

    first = separatrix_scattering(args.cutoff, args.max_step)
    outgoing_p = first[3]
    scattering_wronskian = first[5]
    rotation = outgoing_p / args.cutoff + scattering_wronskian / np.sqrt(
        args.cutoff
    )

    separation = np.cos(args.phase) ** 2
    incoming_speed = np.sqrt(
        4 / np.sqrt(args.cutoff**2 + separation**2 / 4)
    )
    root_cutoff = np.sqrt(args.cutoff)
    transverse = rotation * args.cutoff + scattering_wronskian * root_cutoff
    transverse_velocity = (
        -rotation - scattering_wronskian / (2 * root_cutoff)
    ) * incoming_speed
    solution = solve_ivp(
        variational_rhs,
        (args.phase, args.phase + args.phase_span),
        (-args.cutoff, incoming_speed, transverse, transverse_velocity),
        events=center_event,
        rtol=3e-11,
        atol=3e-13,
        max_step=args.max_step,
        dense_output=True,
    )
    if not solution.t_events[0].size:
        raise RuntimeError("probe did not reach the center")

    center_phase = float(solution.t_events[0][0])
    center_mean = np.remainder(
        2 * center_phase + np.sin(2 * center_phase), 2 * np.pi
    )
    collision_gap = np.pi - center_mean
    collision_phase = np.pi / 2 + np.ceil(
        (center_phase - np.pi / 2) / np.pi
    ) * np.pi
    shape_exponent = (np.sqrt(19) - 1) / 4
    beta_minus = (3 - np.sqrt(7)) / 4
    beta_plus = (3 + np.sqrt(7)) / 4
    equilateral_shape = -np.sqrt(3) / 2

    print(
        f"cutoff={args.cutoff:.1f} phase={args.phase:.12f} "
        f"center_collision_gap={collision_gap:.12e}"
    )
    print(
        "binary_separation shape shape_stable_proxy "
        "slow_jost_projector transverse transverse_velocity"
    )
    for radius in args.sections:
        if not 0 < radius < 1:
            raise ValueError("every section must lie in (0,1)")
        anomaly_gap = np.arcsin(np.sqrt(radius))
        target_phase = collision_phase - anomaly_gap
        if not args.phase <= target_phase <= center_phase:
            raise ValueError(f"section r={radius} is outside the integrated segment")
        height, _, field, field_velocity = solution.sol(target_phase)
        radial_velocity = -2 * np.sqrt((1 - radius) / radius)
        field_radius_derivative = field_velocity / radial_velocity
        projector = radius ** (-beta_minus) * (
            beta_plus * field - radius * field_radius_derivative
        ) / (beta_plus - beta_minus)
        shape = height / radius
        shape_proxy = (
            (shape - equilateral_shape) / radius**shape_exponent
        )
        print(
            f"{radius:.12e} {shape:.12e} {shape_proxy:.12e} "
            f"{projector:.12e} {field:.12e} {field_velocity:.12e}"
        )


if __name__ == "__main__":
    main()
