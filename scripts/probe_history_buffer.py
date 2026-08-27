#!/usr/bin/env python3
"""Falsify the conjectural buffered torque-history barrier.

This is a bounded ordinary-precision discovery probe, not a proof.  It scans
exactly parameterized ordered obtuse shapes and states on ``b=0``, where

    b = h - eta + y * (1 - Z*S/P).

The homothetic rate is parameterized by ``sigma = gamma*sqrt(Z)/delta``.
For rational inputs this makes ``chi=sigma*sqrt(Z)*delta=gamma*Z`` rational,
and it also makes the kinetic-energy test rational after squaring.  Any
reported candidate can therefore be promoted to an exact symbolic witness.
"""

from __future__ import annotations

import argparse

import numpy as np
import sympy as sp

from src.symbolic.mutual_distances import (
    ordered_history_buffered_barrier_reduction,
)


def normalized_kinetic(
    mass_1: float,
    mass_2: float,
    side_23: float,
    side_31: float,
    history_ratio: float,
    amplitude_squared: float,
    gamma: float,
) -> float:
    """Return kinetic energy at normalized scale ``r12=1``."""
    apex_x = (side_31**2 + 1 - side_23**2) / 2
    area_squared = side_31**2 - apex_x**2
    if area_squared <= 0 or amplitude_squared <= 0:
        return np.inf
    twice_area = np.sqrt(area_squared)
    amplitude = np.sqrt(amplitude_squared)
    scale_rate = gamma * amplitude / twice_area
    ell_23 = amplitude
    ell_31 = -(mass_2 / mass_1) * history_ratio * amplitude
    ell_12 = -(1 - history_ratio) * amplitude / mass_1
    relative_12 = np.array([scale_rate, ell_12])
    velocity_3_y = twice_area * scale_rate - (apex_x - 1) * ell_12 - ell_23 + ell_31
    velocity_3_x = (apex_x * velocity_3_y - ell_31) / twice_area
    relative_13 = np.array([velocity_3_x, velocity_3_y])
    total_mass = mass_1 + mass_2 + 1
    velocity_1 = -(mass_2 * relative_12 + relative_13) / total_mass
    velocity_2 = velocity_1 + relative_12
    velocity_3 = velocity_1 + relative_13
    return float(
        (
            mass_1 * np.dot(velocity_1, velocity_1)
            + mass_2 * np.dot(velocity_2, velocity_2)
            + np.dot(velocity_3, velocity_3)
        )
        / 2
    )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--grid", type=int, default=17)
    parser.add_argument("--gamma-min", type=float, default=-8.0)
    parser.add_argument("--gamma-max", type=float, default=2.0)
    parser.add_argument("--gamma-count", type=int, default=101)
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    data, variables = ordered_history_buffered_barrier_reduction()
    m, n, x, y, eta, z, chi = variables
    value_function = sp.lambdify(
        (m, n, x, y, eta, z, chi),
        (
            data["h"],
            data["k"],
            data["C"],
            data["boundary_Z"],
            data["normalized_rate"],
            data["normalized_forcing"],
        ),
        "numpy",
        cse=True,
    )

    parameters = np.linspace(0.03, np.sqrt(2) - 1 - 1e-4, args.grid)
    cube = np.linspace(0.05, 0.95, args.grid)
    alphas = (0.05, 0.25, 0.5, 0.75, 0.95)
    gammas = np.linspace(args.gamma_min, args.gamma_max, args.gamma_count)
    best: tuple[float, tuple[float, ...]] | None = None
    checked = 0
    for parameter in parameters:
        mass_1 = (1 - parameter**2) / (1 + parameter**2)
        mass_2 = 2 * parameter / (1 + parameter**2)
        initial_potential = mass_1 * mass_2 + 1 / (mass_1 * mass_2)
        for triangle_scale in cube:
            for order_split in cube:
                side_23 = 1 - triangle_scale * order_split / 2
                side_31 = 1 - triangle_scale + triangle_scale * order_split / 2
                defect = 1 - side_23**2 - side_31**2
                if defect < 0:
                    continue
                probe = value_function(mass_1, mass_2, side_23, side_31, 0.5, 1.0, 0.0)
                threshold = float(probe[0])
                current = float(probe[1])
                if not 0 < current < threshold < 1:
                    continue
                for alpha in alphas:
                    history_ratio = current + alpha * (threshold - current)
                    values = value_function(
                        mass_1,
                        mass_2,
                        side_23,
                        side_31,
                        history_ratio,
                        1.0,
                        0.0,
                    )
                    reciprocal_threshold = float(values[2])
                    boundary_z = float(values[3])
                    if reciprocal_threshold <= 0 or boundary_z <= 0:
                        continue
                    potential = mass_1 * mass_2 + mass_2 / side_23 + mass_1 / side_31
                    for gamma in gammas:
                        kinetic = normalized_kinetic(
                            mass_1,
                            mass_2,
                            side_23,
                            side_31,
                            history_ratio,
                            boundary_z,
                            gamma,
                        )
                        if not kinetic < potential:
                            continue
                        radial_flux = gamma * boundary_z
                        values = value_function(
                            mass_1,
                            mass_2,
                            side_23,
                            side_31,
                            history_ratio,
                            boundary_z,
                            radial_flux,
                        )
                        rate = float(values[4])
                        forcing = float(values[5])
                        checked += 1
                        score = min(rate, forcing)
                        record = (
                            parameter,
                            triangle_scale,
                            order_split,
                            alpha,
                            gamma,
                            side_23,
                            side_31,
                            history_ratio,
                            threshold,
                            current,
                            reciprocal_threshold,
                            boundary_z,
                            rate,
                            forcing,
                            kinetic,
                            potential,
                            (potential - kinetic) / initial_potential,
                        )
                        if best is None or score < best[0]:
                            best = (score, record)
    if best is None:
        print("status=NO_ADMISSIBLE_BOUNDARY_STATE")
        return
    labels = (
        "u",
        "t",
        "w",
        "alpha",
        "gamma",
        "x",
        "y",
        "eta",
        "h",
        "k",
        "C",
        "Z",
        "Wdelta_b_s",
        "normalized_forcing",
        "kinetic",
        "potential",
        "physical_scale",
    )
    print(f"status=ORDINARY_NUMERICAL_EVIDENCE checked={checked}")
    for label, value in zip(labels, best[1], strict=True):
        print(f"{label}={value:.17g}")


if __name__ == "__main__":
    main()
