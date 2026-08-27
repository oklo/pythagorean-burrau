#!/usr/bin/env python3
"""Probe whether the lag-envelope forcing can recross zero outward.

This bounded ordinary-precision scan is a falsification aid, not a proof.
It evaluates ``W*delta*E_s`` on the exact surface ``E=0`` while retaining
the tied masses, ordered obtuse geometry, ``k<eta<h``, and compatibility
with the Burrau energy after a positive physical rescaling.
"""

from __future__ import annotations

import argparse

import numpy as np
import sympy as sp

from scripts.probe_history_buffer import normalized_kinetic
from src.symbolic.mutual_distances import (
    ordered_history_envelope_switch_reduction,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--grid", type=int, default=15)
    parser.add_argument("--gamma-min", type=float, default=-3.0)
    parser.add_argument("--gamma-max", type=float, default=3.0)
    parser.add_argument("--gamma-count", type=int, default=61)
    parser.add_argument("--include-acute", action="store_true")
    parser.add_argument("--triangle-scale-min", type=float, default=0.05)
    parser.add_argument("--full-eta", action="store_true")
    parser.add_argument("--initial-eta-bound", action="store_true")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    data, variables = ordered_history_envelope_switch_reduction()
    m, n, x, y, eta, z, chi = variables
    value_function = sp.lambdify(
        (m, n, x, y, eta, z, chi),
        (
            data["h"],
            data["k"],
            data["D"],
            data["boundary_Z"],
            data["E"],
            data["normalized_rate"],
        ),
        "numpy",
        cse=True,
    )
    parameters = np.linspace(0.03, np.sqrt(2) - 1 - 1e-4, args.grid)
    triangle_scales = np.linspace(args.triangle_scale_min, 0.95, args.grid)
    cube = np.linspace(0.05, 0.95, args.grid)
    alphas = (0.05, 0.25, 0.5, 0.75, 0.95)
    gammas = np.linspace(args.gamma_min, args.gamma_max, args.gamma_count)
    best: tuple[float, tuple[float, ...]] | None = None
    smallest_zero_energy_gap: tuple[float, tuple[float, ...]] | None = None
    checked = 0
    for parameter in parameters:
        mass_1 = (1 - parameter**2) / (1 + parameter**2)
        mass_2 = 2 * parameter / (1 + parameter**2)
        initial_potential = mass_1 * mass_2 + 1 / (mass_1 * mass_2)
        for triangle_scale in triangle_scales:
            for order_split in cube:
                side_23 = 1 - triangle_scale * order_split / 2
                side_31 = 1 - triangle_scale + triangle_scale * order_split / 2
                if not args.include_acute and 1 - side_23**2 - side_31**2 < 0:
                    continue
                probe = value_function(mass_1, mass_2, side_23, side_31, 0.5, 1.0, 0.0)
                threshold = float(probe[0])
                current = float(probe[1])
                if not 0 < current < threshold < 1:
                    continue
                for alpha in alphas:
                    if args.initial_eta_bound:
                        initial_x = mass_1
                        initial_y = mass_2
                        initial_ratio = (initial_x**-3 - 1) / (initial_y**-3 - 1)
                        history_ratio = alpha * initial_ratio
                    elif args.full_eta:
                        history_ratio = alpha
                    else:
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
                    direction = float(values[2])
                    boundary_z = float(values[3])
                    if direction >= 0 or boundary_z <= 0:
                        continue
                    potential = mass_1 * mass_2 + mass_2 / side_23 + mass_1 / side_31
                    rate_at_zero = float(
                        value_function(
                            mass_1,
                            mass_2,
                            side_23,
                            side_31,
                            history_ratio,
                            boundary_z,
                            0.0,
                        )[5]
                    )
                    rate_at_unit_gamma = float(
                        value_function(
                            mass_1,
                            mass_2,
                            side_23,
                            side_31,
                            history_ratio,
                            boundary_z,
                            boundary_z,
                        )[5]
                    )
                    rate_slope = rate_at_unit_gamma - rate_at_zero
                    if rate_slope > 0:
                        zero_gamma = -rate_at_zero / rate_slope
                        kinetic_minus = normalized_kinetic(
                            mass_1,
                            mass_2,
                            side_23,
                            side_31,
                            history_ratio,
                            boundary_z,
                            -1.0,
                        )
                        kinetic_zero = normalized_kinetic(
                            mass_1,
                            mass_2,
                            side_23,
                            side_31,
                            history_ratio,
                            boundary_z,
                            0.0,
                        )
                        kinetic_plus = normalized_kinetic(
                            mass_1,
                            mass_2,
                            side_23,
                            side_31,
                            history_ratio,
                            boundary_z,
                            1.0,
                        )
                        kinetic_quadratic = (kinetic_plus + kinetic_minus - 2 * kinetic_zero) / 2
                        kinetic_linear = (kinetic_plus - kinetic_minus) / 2
                        kinetic_at_rate_zero = (
                            kinetic_quadratic * zero_gamma**2
                            + kinetic_linear * zero_gamma
                            + kinetic_zero
                        )
                        energy_gap = kinetic_at_rate_zero - potential
                        kinetic_slope = 2 * kinetic_quadratic * zero_gamma + kinetic_linear
                        zero_record = (
                            parameter,
                            triangle_scale,
                            order_split,
                            alpha,
                            zero_gamma,
                            energy_gap,
                            kinetic_slope,
                            boundary_z,
                        )
                        if kinetic_slope > 0 and (
                            smallest_zero_energy_gap is None
                            or energy_gap < smallest_zero_energy_gap[0]
                        ):
                            smallest_zero_energy_gap = (
                                energy_gap,
                                zero_record,
                            )
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
                        envelope = float(values[4])
                        rate = float(values[5])
                        checked += 1
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
                            direction,
                            boundary_z,
                            envelope,
                            rate,
                            kinetic,
                            potential,
                            (potential - kinetic) / initial_potential,
                        )
                        if best is None or rate > best[0]:
                            best = (rate, record)
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
        "D",
        "Z",
        "E",
        "Wdelta_E_s",
        "kinetic",
        "potential",
        "physical_scale",
    )
    verdict = "OUTWARD_WITNESS" if best[0] > 0 else "NO_OUTWARD_WITNESS"
    print(f"status=ORDINARY_NUMERICAL_EVIDENCE verdict={verdict} checked={checked}")
    for label, value in zip(labels, best[1], strict=True):
        print(f"{label}={value:.17g}")
    if smallest_zero_energy_gap is not None:
        zero_labels = (
            "zero_u",
            "zero_t",
            "zero_w",
            "zero_alpha",
            "zero_gamma",
            "zero_energy_gap",
            "zero_kinetic_slope",
            "zero_Z",
        )
        for label, value in zip(zero_labels, smallest_zero_energy_gap[1], strict=True):
            print(f"{label}={value:.17g}")


if __name__ == "__main__":
    main()
