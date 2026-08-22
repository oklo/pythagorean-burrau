#!/usr/bin/env python3
"""Ordinary numerical probe of the restricted parabolic-curve crossing."""

from __future__ import annotations

import argparse
from collections.abc import Callable

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import brentq


def rhs(phase: float, state: np.ndarray) -> list[float]:
    z, velocity = state
    cosine_squared = np.cos(phase) ** 2
    radius_squared = z**2 + cosine_squared**2 / 4
    return [
        velocity * cosine_squared,
        -2 * z * cosine_squared / radius_squared**1.5,
    ]


def section_event(target: float, direction: float = 0.0) -> Callable:
    def event(_phase: float, state: np.ndarray) -> float:
        return float(state[0] - target)

    event.terminal = True
    event.direction = direction
    return event


def integrate_to_section(
    initial_phase: float,
    initial_state: tuple[float, float],
    target: float,
) -> tuple[float, float]:
    solution = solve_ivp(
        rhs,
        (initial_phase, initial_phase + 5000),
        initial_state,
        events=section_event(target, 1.0),
        rtol=3e-12,
        atol=3e-14,
        max_step=0.005,
    )
    if not solution.t_events[0].size:
        raise RuntimeError(f"trajectory did not reach z={target}")
    phase = float(solution.t_events[0][0])
    velocity = float(solution.y_events[0][0][1])
    return phase, velocity


def outgoing_section_energy(launch_speed: float, cutoff: float) -> tuple[float, float]:
    phase, velocity = integrate_to_section(0.0, (0.0, launch_speed), cutoff)
    separation = np.cos(phase) ** 2
    energy = velocity**2 / 2 - 2 / np.sqrt(cutoff**2 + separation**2 / 4)
    return float(energy), phase


def incoming_curve_at_center(initial_phase: float, cutoff: float) -> tuple[float, float]:
    separation = np.cos(initial_phase) ** 2
    parabolic_speed = np.sqrt(4 / np.sqrt(cutoff**2 + separation**2 / 4))
    return integrate_to_section(initial_phase, (-cutoff, parabolic_speed), 0.0)


def collision_jacobi_derivative(launch_speed: float) -> float:
    def variational_rhs(phase: float, state: np.ndarray) -> list[float]:
        z, velocity, jacobi, jacobi_velocity = state
        separation = np.cos(phase) ** 2
        radius_squared = z**2 + separation**2 / 4
        coefficient = (4 * z**2 - separation**2 / 2) / radius_squared**2.5
        return [
            velocity * separation,
            -2 * z * separation / radius_squared**1.5,
            jacobi_velocity * separation,
            coefficient * jacobi * separation,
        ]

    solution = solve_ivp(
        variational_rhs,
        (0.0, np.pi / 2),
        (0.0, launch_speed, launch_speed, 0.0),
        rtol=3e-12,
        atol=3e-14,
        max_step=0.002,
    )
    return float(solution.y[3, -1])


def probe_cutoff(cutoff: float, phase_step: float) -> tuple[float, float, float]:
    launch_speed = brentq(
        lambda speed: outgoing_section_energy(speed, cutoff)[0],
        2.905,
        2.906,
        xtol=2e-13,
    )
    _, outgoing_phase = outgoing_section_energy(launch_speed, cutoff)
    critical_incoming_phase = -outgoing_phase
    minus_phase, minus_speed = incoming_curve_at_center(
        critical_incoming_phase - phase_step, cutoff
    )
    plus_phase, plus_speed = incoming_curve_at_center(
        critical_incoming_phase + phase_step, cutoff
    )
    unstable_slope = (plus_speed - minus_speed) / (plus_phase - minus_phase)
    jacobi_derivative = collision_jacobi_derivative(launch_speed)
    return float(launch_speed), float(2 * unstable_slope), jacobi_derivative


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--cutoffs", nargs="+", type=float, default=[10.0, 20.0, 40.0])
    parser.add_argument("--phase-step", type=float, default=0.002)
    args = parser.parse_args()
    print("cutoff launch_speed unstable_minus_stable_slope collision_jacobi_derivative")
    for cutoff in args.cutoffs:
        speed, slope, derivative = probe_cutoff(cutoff, args.phase_step)
        print(f"{cutoff:.1f} {speed:.12f} {slope:.12f} {derivative:.12f}")


if __name__ == "__main__":
    main()
