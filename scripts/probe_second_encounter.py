#!/usr/bin/env python3
"""Ordinary probe of the compact second restricted encounter.

This is diagnostic only.  It feeds the centered first-encounter transverse
scattering data back from positive infinity and scans the binary phase of the
next center passage.  No printed residual is a validated enclosure.
"""

from __future__ import annotations

import argparse

import numpy as np
from scipy.integrate import solve_ivp

from scripts.probe_restricted_turn_map import (
    center_event,
    section_event,
    separatrix_scattering,
    variational_rhs,
    velocity_zero_event,
)


def second_encounter(
    cutoff: float,
    incoming_phase: float,
    rotation_coefficient: float,
    scattering_wronskian: float,
    phase_span: float,
    max_step: float,
) -> tuple[str, float, float, float, float, float, float, float]:
    """Return outcome, phases, terminal height/W/p, and center p/p'.

    The input and returned phases are eccentric anomalies.  The center phase
    is the section coordinate relevant to the exact map; the input phase is
    only a finite-cutoff shooting coordinate.
    """
    separation = np.cos(incoming_phase) ** 2
    incoming_speed = np.sqrt(4 / np.sqrt(cutoff**2 + separation**2 / 4))
    root_cutoff = np.sqrt(cutoff)
    transverse = rotation_coefficient * cutoff + scattering_wronskian * root_cutoff
    transverse_velocity = (
        -rotation_coefficient - scattering_wronskian / (2 * root_cutoff)
    ) * incoming_speed
    solution = solve_ivp(
        variational_rhs,
        (incoming_phase, incoming_phase + phase_span),
        (-cutoff, incoming_speed, transverse, transverse_velocity),
        events=(section_event(cutoff), velocity_zero_event, center_event),
        rtol=3e-11,
        atol=3e-13,
        max_step=max_step,
    )
    if solution.t_events[2].size:
        center_phase = float(solution.t_events[2][0])
        _, _, center_p, center_p_velocity = solution.y_events[2][0]
    else:
        center_phase = float("nan")
        center_p = float("nan")
        center_p_velocity = float("nan")
    if solution.t_events[0].size:
        phase = float(solution.t_events[0][0])
        z, velocity, p, p_velocity = solution.y_events[0][0]
        wronskian = z * p_velocity - velocity * p
        # Reaching the positive cutoff does not prove escape: a captured
        # orbit may turn above the finite computational section.
        return (
            "exit",
            center_phase,
            phase,
            float(z),
            float(wronskian),
            float(p),
            float(center_p),
            float(center_p_velocity),
        )
    if solution.t_events[1].size:
        phase = float(solution.t_events[1][0])
        z, velocity, p, p_velocity = solution.y_events[1][0]
        wronskian = z * p_velocity - velocity * p
        return (
            "turn",
            center_phase,
            phase,
            float(z),
            float(wronskian),
            float(p),
            float(center_p),
            float(center_p_velocity),
        )
    return (
        "unresolved",
        center_phase,
        float(solution.t[-1]),
        float(solution.y[0, -1]),
        float("nan"),
        float(solution.y[2, -1]),
        float(center_p),
        float(center_p_velocity),
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--cutoff", type=float, default=80.0)
    parser.add_argument("--phases", type=int, default=41)
    parser.add_argument("--phase-lower", type=float, default=0.0)
    parser.add_argument("--phase-upper", type=float, default=float(np.pi))
    parser.add_argument("--phase-span", type=float, default=100000.0)
    parser.add_argument("--max-step", type=float, default=0.03)
    args = parser.parse_args()

    first = separatrix_scattering(args.cutoff, args.max_step)
    _, _, _, outgoing_p, _, wronskian, *_ = first
    rotation = outgoing_p / args.cutoff + wronskian / np.sqrt(args.cutoff)
    print(f"cutoff={args.cutoff:.1f} first_W={wronskian:.12e} rotation_estimate={rotation:.12e}")
    print(
        "cutoff_eccentric_anomaly_mod_pi outcome "
        "center_mean_anomaly_mod_2pi terminal_eccentric_anomaly_mod_pi "
        "height_or_section W terminal_p center_p center_p_velocity "
        "collision_phase_gap scaled_height renormalized_W "
        "scaled_center_p scaled_center_p_velocity"
    )
    for phase in np.linspace(args.phase_lower, args.phase_upper, args.phases, endpoint=False):
        (
            outcome,
            center_phase,
            terminal_phase,
            height,
            terminal_wronskian,
            terminal_p,
            center_p,
            center_p_velocity,
        ) = second_encounter(
            args.cutoff,
            float(phase),
            float(rotation),
            float(wronskian),
            args.phase_span,
            args.max_step,
        )
        center_mean_anomaly = 2 * center_phase + np.sin(2 * center_phase)
        center_mean_anomaly = np.remainder(center_mean_anomaly, 2 * np.pi)
        collision_gap = np.pi - center_mean_anomaly
        alpha_minus = (3 - np.sqrt(7)) / 6
        if outcome == "turn" and collision_gap > 0:
            scaled_height = height / collision_gap ** (2 / 3)
            renormalized_wronskian = (
                terminal_wronskian
                * collision_gap ** ((np.sqrt(7) - 1) / 6)
            )
            scaled_center_p = center_p / collision_gap**alpha_minus
            scaled_center_p_velocity = (
                center_p_velocity * collision_gap ** (1 - alpha_minus)
            )
        else:
            scaled_height = float("nan")
            renormalized_wronskian = float("nan")
            scaled_center_p = float("nan")
            scaled_center_p_velocity = float("nan")
        print(
            f"{phase:.12f} {outcome} "
            f"{center_mean_anomaly:.12f} "
            f"{np.remainder(terminal_phase, np.pi):.12f} "
            f"{height:.12e} {terminal_wronskian:.12e} {terminal_p:.12e} "
            f"{center_p:.12e} {center_p_velocity:.12e} "
            f"{collision_gap:.12e} {scaled_height:.12e} "
            f"{renormalized_wronskian:.12e} {scaled_center_p:.12e} "
            f"{scaled_center_p_velocity:.12e}"
        )


if __name__ == "__main__":
    main()
