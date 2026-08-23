#!/usr/bin/env python3
"""Ordinary numerical probe of turns on the restricted captured side."""

from __future__ import annotations

import argparse

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import brentq

from scripts.probe_restricted_transversality import (
    outgoing_section_energy,
)


def variational_rhs(phase: float, state: np.ndarray) -> list[float]:
    """Restricted orbit plus the first relative-tilt field xi."""
    z, velocity, transverse, transverse_velocity = state
    separation = np.cos(phase) ** 2
    radius_squared = z**2 + separation**2 / 4
    transverse_coefficient = (
        separation**2 - 2 * z**2
    ) / radius_squared**2.5
    return [
        velocity * separation,
        -2 * z * separation / radius_squared**1.5,
        transverse_velocity * separation,
        transverse_coefficient * transverse * separation,
    ]


def velocity_zero_event(_phase: float, state: np.ndarray) -> float:
    return float(state[1])


velocity_zero_event.terminal = True
velocity_zero_event.direction = -1.0


def center_event(_phase: float, state: np.ndarray) -> float:
    return float(state[0])


center_event.terminal = False
center_event.direction = 1.0


def section_event(target: float):
    """Return an increasing outer-section event for ``solve_ivp``."""

    def event(_phase: float, state: np.ndarray) -> float:
        return float(state[0] - target)

    event.terminal = True
    event.direction = 1.0
    return event


def critical_cutoff_phase(cutoff: float) -> tuple[float, float]:
    """Return centered separatrix speed and its reversible incoming phase."""
    launch_speed = brentq(
        lambda speed: outgoing_section_energy(speed, cutoff)[0],
        2.905,
        2.906,
        xtol=2e-13,
    )
    _, outgoing_phase = outgoing_section_energy(launch_speed, cutoff)
    return float(launch_speed), float(-outgoing_phase)


def incoming_turn(
    cutoff: float,
    initial_phase: float,
    phase_span: float,
    max_step: float,
) -> tuple[float, float, float, float, float] | None:
    separation = np.cos(initial_phase) ** 2
    parabolic_speed = np.sqrt(4 / np.sqrt(cutoff**2 + separation**2 / 4))
    solution = solve_ivp(
        variational_rhs,
        (initial_phase, initial_phase + phase_span),
        (-cutoff, parabolic_speed, cutoff / 2, -parabolic_speed / 2),
        events=(center_event, velocity_zero_event),
        rtol=3e-11,
        atol=3e-13,
        max_step=max_step,
    )
    if not solution.t_events[1].size or not solution.t_events[0].size:
        return None
    center_phase = float(solution.t_events[0][0])
    center_speed = float(solution.y_events[0][0][1])
    turn_phase = float(solution.t_events[1][0])
    turn_height = float(solution.y_events[1][0][0])
    transverse_velocity = float(solution.y_events[1][0][3])
    return center_phase, center_speed, turn_phase, turn_height, transverse_velocity


def separatrix_scattering(cutoff: float, max_step: float) -> tuple[float, ...]:
    """Probe transverse angular-momentum transfer on the separatrix.

    The finite-cutoff data use ``p=z`` and ``p'=z'``. The returned Wronskian
    is ``W=z*p'-z'*p`` at the outgoing ``z=cutoff`` section.
    """
    launch_speed, incoming_phase = critical_cutoff_phase(cutoff)
    separation = np.cos(incoming_phase) ** 2
    incoming_speed = np.sqrt(4 / np.sqrt(cutoff**2 + separation**2 / 4))
    solution = solve_ivp(
        variational_rhs,
        (incoming_phase, incoming_phase + 100000.0),
        (-cutoff, incoming_speed, -cutoff, incoming_speed),
        events=(center_event, section_event(cutoff)),
        rtol=3e-11,
        atol=3e-13,
        max_step=max_step,
    )
    if not solution.t_events[1].size or not solution.t_events[0].size:
        raise RuntimeError("separatrix probe did not reach outgoing cutoff")
    center_state = solution.y_events[0][0]
    center_wronskian = (
        center_state[0] * center_state[3]
        - center_state[1] * center_state[2]
    )
    phase = float(solution.t_events[1][0])
    z, velocity, transverse, transverse_velocity = solution.y_events[1][0]
    wronskian = z * transverse_velocity - velocity * transverse
    return (
        launch_speed,
        phase,
        float(velocity),
        float(transverse),
        float(transverse_velocity),
        float(wronskian),
        float(center_wronskian),
        float(center_state[2]),
        float(center_state[3]),
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--cutoff", type=float, default=40.0)
    parser.add_argument("--offsets", nargs="+", type=float, default=[])
    parser.add_argument(
        "--resonances",
        nargs="+",
        default=[],
        metavar="K:LO:HI",
        help="find turn_phase=K*pi in each supplied offset bracket",
    )
    parser.add_argument("--phase-span", type=float, default=100000.0)
    parser.add_argument("--max-step", type=float, default=0.02)
    parser.add_argument(
        "--scattering-cutoffs",
        nargs="+",
        type=float,
        default=[],
        help="probe the parabolic transverse Wronskian at these cutoffs",
    )
    args = parser.parse_args()

    launch_speed, critical_phase = critical_cutoff_phase(args.cutoff)
    print(f"cutoff={args.cutoff} centered_speed={launch_speed:.12f}")
    print(f"critical_initial_phase={critical_phase:.12f}")
    print(
        "offset center_phase_mod_pi center_speed turn_phase_mod_pi "
        "turn_height cycles transverse_velocity"
    )
    for offset in args.offsets:
        result = incoming_turn(
            args.cutoff,
            critical_phase + offset,
            args.phase_span,
            args.max_step,
        )
        if result is None:
            print(f"{offset:+.8g} no_turn")
            continue
        center_phase, center_speed, turn_phase, turn_height, transverse_velocity = result
        print(
            f"{offset:+.8g} "
            f"{np.remainder(center_phase, np.pi):.12f} "
            f"{center_speed:.12f} "
            f"{np.remainder(turn_phase, np.pi):.12f} "
            f"{turn_height:.12f} "
            f"{(turn_phase-center_phase)/np.pi:.6f} "
            f"{transverse_velocity:.12e}"
        )

    if args.resonances:
        print("resonance offset turn_height transverse_velocity angular_slip")
    for specification in args.resonances:
        resonance_text, lower_text, upper_text = specification.split(":")
        resonance = int(resonance_text)
        lower = float(lower_text)
        upper = float(upper_text)

        def phase_residual(offset: float, resonance_index: int = resonance) -> float:
            result = incoming_turn(
                args.cutoff,
                critical_phase + offset,
                args.phase_span,
                args.max_step,
            )
            if result is None:
                raise RuntimeError("resonance bracket entered the no-turn side")
            return result[2] / np.pi - resonance_index

        offset = brentq(phase_residual, lower, upper, xtol=2e-10)
        result = incoming_turn(
            args.cutoff,
            critical_phase + offset,
            args.phase_span,
            args.max_step,
        )
        if result is None:
            raise RuntimeError("resonance root unexpectedly has no turn")
        _, _, _, turn_height, transverse_velocity = result
        print(
            f"{resonance:d} {offset:.12f} {turn_height:.12f} "
            f"{transverse_velocity:.12e} "
            f"{transverse_velocity / turn_height:.12e}"
        )

    if args.scattering_cutoffs:
        print(
            "scattering_cutoff launch_speed outgoing_phase outgoing_speed "
            "p p_velocity wronskian center_wronskian center_p center_p_velocity"
        )
    for cutoff in args.scattering_cutoffs:
        result = separatrix_scattering(cutoff, args.max_step)
        print(f"{cutoff:.1f} " + " ".join(f"{value:.12e}" for value in result))


if __name__ == "__main__":
    main()
