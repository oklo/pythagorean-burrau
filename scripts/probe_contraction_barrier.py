#!/usr/bin/env python3
"""Falsify the contraction barrier associated with envelope crossings.

This ordinary-precision probe differentiates the exact rational threshold
``Gamma(x,y,eta)`` by centered finite differences.  It is only a discovery
tool.  Exact symbolic expressions for the same derivative are provided by
``envelope_switch_contraction_barrier_reduction``.
"""

from __future__ import annotations

import argparse

import numpy as np
import sympy as sp

from src.symbolic.mutual_distances import (
    envelope_switch_energy_separation,
    ordered_history_contraction_reduction,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--grid", type=int, default=17)
    parser.add_argument("--history-grid", type=int, default=17)
    parser.add_argument("--difference-step", type=float, default=2e-5)
    parser.add_argument("--u-min", type=float, default=0.03)
    parser.add_argument("--u-max", type=float, default=np.sqrt(2) - 1 - 1e-4)
    parser.add_argument("--negative-d-min", type=float, default=0.0)
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    separation, variables = envelope_switch_energy_separation()
    m, n, x, y, eta = variables
    contraction, contraction_variables = ordered_history_contraction_reduction()
    cm, cn, cx, cy, ceta, z, gamma = contraction_variables
    contraction_substitution = {cm: m, cn: n, cx: x, cy: y, ceta: eta}
    exact_functions = sp.lambdify(
        (m, n, x, y, eta),
        (
            separation["k"],
            separation["h"],
            separation["D"],
            separation["gamma_zero"],
            separation["eta_normalized_rate"],
            separation["potential"],
            contraction["X"].subs(contraction_substitution),
            contraction["Y"].subs(contraction_substitution),
        ),
        "numpy",
        cse=True,
    )
    contraction_rate = sp.lambdify(
        (m, n, x, y, eta, z, gamma),
        contraction["normalized_rate"].subs(contraction_substitution),
        "numpy",
        cse=True,
    )
    gamma_symbol = sp.symbols("gamma", real=True)
    kinetic_at_gamma = sp.lambdify(
        (m, n, x, y, eta, gamma_symbol),
        separation["kinetic"],
        "numpy",
        cse=True,
    )

    parameters = np.linspace(args.u_min, args.u_max, args.grid)
    cube = np.linspace(0.04, 0.96, args.grid)
    history_fractions = np.linspace(0.03, 0.97, args.history_grid)
    step = args.difference_step
    best: tuple[float, tuple[float, ...]] | None = None
    checked = 0
    for parameter in parameters:
        mass_1 = (1 - parameter**2) / (1 + parameter**2)
        mass_2 = 2 * parameter / (1 + parameter**2)
        for triangle_scale in cube:
            for order_split in cube:
                side_23 = 1 - triangle_scale * order_split / 2
                side_31 = 1 - triangle_scale + triangle_scale * order_split / 2
                if 1 - side_23**2 - side_31**2 < 0:
                    continue
                base = exact_functions(mass_1, mass_2, side_23, side_31, 0.5)
                current = float(base[0])
                threshold = float(base[1])
                if not 0 < current < threshold < 1:
                    continue
                for fraction in history_fractions:
                    history_ratio = current + fraction * (threshold - current)
                    values = exact_functions(
                        mass_1,
                        mass_2,
                        side_23,
                        side_31,
                        history_ratio,
                    )
                    direction = float(values[2])
                    gamma_threshold = float(values[3])
                    if not direction < -args.negative_d_min or not np.isfinite(gamma_threshold):
                        continue
                    gradient = []
                    point = [side_23, side_31, history_ratio]
                    for coordinate in range(3):
                        plus = point.copy()
                        minus = point.copy()
                        plus[coordinate] += step
                        minus[coordinate] -= step
                        gamma_plus = float(
                            exact_functions(mass_1, mass_2, plus[0], plus[1], plus[2])[3]
                        )
                        gamma_minus = float(
                            exact_functions(mass_1, mass_2, minus[0], minus[1], minus[2])[3]
                        )
                        gradient.append((gamma_plus - gamma_minus) / (2 * step))
                    eta_rate = float(values[4])
                    potential = float(values[5])
                    shape_direction = gradient[0] * float(values[6]) + gradient[1] * float(
                        values[7]
                    )
                    history_direction = gradient[2] * eta_rate
                    kinetic_coefficient = float(
                        kinetic_at_gamma(
                            mass_1,
                            mass_2,
                            side_23,
                            side_31,
                            history_ratio,
                            gamma_threshold,
                        )
                    )
                    if kinetic_coefficient <= 0:
                        continue
                    energy_edge = potential / kinetic_coefficient
                    rates = []
                    for amplitude_squared in (0.0, energy_edge):
                        gamma_rate = float(
                            contraction_rate(
                                mass_1,
                                mass_2,
                                side_23,
                                side_31,
                                history_ratio,
                                amplitude_squared,
                                gamma_threshold,
                            )
                        )
                        rates.append(
                            gamma_rate - amplitude_squared * shape_direction - history_direction
                        )
                    checked += 1
                    score = max(rates)
                    record = (
                        parameter,
                        triangle_scale,
                        order_split,
                        fraction,
                        side_23,
                        side_31,
                        history_ratio,
                        current,
                        threshold,
                        direction,
                        gamma_threshold,
                        rates[0],
                        rates[1],
                        energy_edge,
                    )
                    if best is None or score > best[0]:
                        best = (score, record)
    if best is None:
        print("status=NO_ADMISSIBLE_STATE")
        return
    labels = (
        "u",
        "t",
        "w",
        "history_fraction",
        "x",
        "y",
        "eta",
        "k",
        "h",
        "D",
        "Gamma",
        "barrier_rate_Z0",
        "barrier_rate_energy_edge",
        "energy_edge_Z",
    )
    verdict = "OUTWARD_WITNESS" if best[0] > 0 else "NO_OUTWARD_WITNESS"
    print(f"status=ORDINARY_NUMERICAL_EVIDENCE verdict={verdict} checked={checked}")
    for label, value in zip(labels, best[1], strict=True):
        print(f"{label}={value:.17g}")


if __name__ == "__main__":
    main()
