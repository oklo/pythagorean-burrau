#!/usr/bin/env python3
"""Ordinary numerical probe of the one-parameter planar joint-limit family."""

import argparse

import numpy as np
from scipy.integrate import solve_ivp

EQUILATERAL_HEIGHT = np.sqrt(3.0) / 2.0
TRANSVERSE_RATE = (1.0 + np.sqrt(7.0)) / 6.0
LONGITUDINAL_RATE = (1.0 + np.sqrt(19.0)) / 6.0
QUADRATIC_BENDING = (2.0 * np.sqrt(21.0) - 5.0 * np.sqrt(3.0)) / 4.0
MIXED_HORIZONTAL = (
    -5.0 * np.sqrt(21.0)
    - np.sqrt(399.0)
    + 12.0 * np.sqrt(3.0)
    + 3.0 * np.sqrt(57.0)
) / 6.0
LONGITUDINAL_QUADRATIC = (-2.0 * np.sqrt(57.0) + 29.0 * np.sqrt(3.0)) / 340.0
TRANSVERSE_CUBIC = -67.0 / 108.0 + 43.0 * np.sqrt(7.0) / 216.0
TRANSVERSE_LONGITUDINAL_SQUARED = (
    (-2819.0 * np.sqrt(133.0) - 2314.0 * np.sqrt(19.0) + 2498.0 * np.sqrt(7.0))
    / 31620.0
    + 83681.0 / 63240.0
)
SQUARED_TRANSVERSE_LONGITUDINAL = (
    -337.0 / 248.0
    + (6.0 * np.sqrt(7.0) + 14.0 * np.sqrt(19.0) + 11.0 * np.sqrt(133.0))
    / 124.0
)
LONGITUDINAL_CUBIC = 121.0 / 5100.0 - 29.0 * np.sqrt(19.0) / 10200.0
TRANSVERSE_CUBIC_LONGITUDINAL = (
    -93651910.0 * np.sqrt(399.0)
    - 392572319.0 * np.sqrt(21.0)
    + 1018625929.0 * np.sqrt(3.0)
    + 250916714.0 * np.sqrt(57.0)
) / 45037296.0
TRANSVERSE_LONGITUDINAL_CUBIC = (
    -386571066.0 * np.sqrt(399.0)
    - 833244582.0 * np.sqrt(21.0)
    + 312559697.0 * np.sqrt(57.0)
    + 6447516829.0 * np.sqrt(3.0)
) / 8038436400.0
TRANSVERSE_QUARTIC = (-3671.0 * np.sqrt(3.0) + 187.0 * np.sqrt(21.0)) / 76464.0
TRANSVERSE_SQUARED_LONGITUDINAL_SQUARED = (
    -1022448154.0 * np.sqrt(21.0)
    - 213073373.0 * np.sqrt(399.0)
    + 2563820254.0 * np.sqrt(3.0)
    + 612798518.0 * np.sqrt(57.0)
) / 267947880.0
LONGITUDINAL_QUARTIC = (
    -4307297.0 * np.sqrt(3.0) + 308435.0 * np.sqrt(57.0)
) / 242413200.0


def shape_field(_zeta: float, state: np.ndarray) -> np.ndarray:
    """Damped-gradient planar shape field."""
    horizontal, vertical, horizontal_speed, vertical_speed = state
    plus_squared = (horizontal + 0.5) ** 2 + vertical**2
    minus_squared = (horizontal - 0.5) ** 2 + vertical**2
    horizontal_force = (
        2.0 * horizontal
        - (horizontal + 0.5) / plus_squared**1.5
        - (horizontal - 0.5) / minus_squared**1.5
    ) / 9.0
    vertical_force = (
        2.0 * vertical
        - vertical / plus_squared**1.5
        - vertical / minus_squared**1.5
    ) / 9.0
    return np.array(
        [
            horizontal_speed,
            vertical_speed,
            horizontal_force - horizontal_speed / 3.0,
            vertical_force - vertical_speed / 3.0,
        ]
    )


def initial_state(kappa: float, zeta: float, transverse_sign: float) -> np.ndarray:
    """Stable-manifold state through exact total degree four."""
    transverse = transverse_sign * np.exp(-TRANSVERSE_RATE * zeta)
    longitudinal = kappa * np.exp(-LONGITUDINAL_RATE * zeta)
    horizontal = (
        transverse
        + MIXED_HORIZONTAL * transverse * longitudinal
        + TRANSVERSE_CUBIC * transverse**3
        + TRANSVERSE_LONGITUDINAL_SQUARED * transverse * longitudinal**2
        + TRANSVERSE_CUBIC_LONGITUDINAL * transverse**3 * longitudinal
        + TRANSVERSE_LONGITUDINAL_CUBIC * transverse * longitudinal**3
    )
    vertical_offset = (
        longitudinal
        + QUADRATIC_BENDING * transverse**2
        + LONGITUDINAL_QUADRATIC * longitudinal**2
        + SQUARED_TRANSVERSE_LONGITUDINAL * transverse**2 * longitudinal
        + LONGITUDINAL_CUBIC * longitudinal**3
        + TRANSVERSE_QUARTIC * transverse**4
        + TRANSVERSE_SQUARED_LONGITUDINAL_SQUARED * transverse**2 * longitudinal**2
        + LONGITUDINAL_QUARTIC * longitudinal**4
    )
    horizontal_speed = (
        -TRANSVERSE_RATE * transverse
        - (TRANSVERSE_RATE + LONGITUDINAL_RATE)
        * MIXED_HORIZONTAL
        * transverse
        * longitudinal
        - 3.0 * TRANSVERSE_RATE * TRANSVERSE_CUBIC * transverse**3
        - (TRANSVERSE_RATE + 2.0 * LONGITUDINAL_RATE)
        * TRANSVERSE_LONGITUDINAL_SQUARED
        * transverse
        * longitudinal**2
        - (3.0 * TRANSVERSE_RATE + LONGITUDINAL_RATE)
        * TRANSVERSE_CUBIC_LONGITUDINAL
        * transverse**3
        * longitudinal
        - (TRANSVERSE_RATE + 3.0 * LONGITUDINAL_RATE)
        * TRANSVERSE_LONGITUDINAL_CUBIC
        * transverse
        * longitudinal**3
    )
    vertical_speed = (
        -LONGITUDINAL_RATE * longitudinal
        - 2.0 * TRANSVERSE_RATE * QUADRATIC_BENDING * transverse**2
        - 2.0 * LONGITUDINAL_RATE * LONGITUDINAL_QUADRATIC * longitudinal**2
        - (2.0 * TRANSVERSE_RATE + LONGITUDINAL_RATE)
        * SQUARED_TRANSVERSE_LONGITUDINAL
        * transverse**2
        * longitudinal
        - 3.0 * LONGITUDINAL_RATE * LONGITUDINAL_CUBIC * longitudinal**3
        - 4.0 * TRANSVERSE_RATE * TRANSVERSE_QUARTIC * transverse**4
        - 2.0
        * (TRANSVERSE_RATE + LONGITUDINAL_RATE)
        * TRANSVERSE_SQUARED_LONGITUDINAL_SQUARED
        * transverse**2
        * longitudinal**2
        - 4.0 * LONGITUDINAL_RATE * LONGITUDINAL_QUARTIC * longitudinal**4
    )
    return np.array(
        [
            horizontal,
            -EQUILATERAL_HEIGHT + vertical_offset,
            horizontal_speed,
            vertical_speed,
        ]
    )


def probe(
    kappa: float,
    zeta_start: float,
    zeta_end: float,
    exit_radius: float,
    transverse_sign: float,
) -> tuple[str, float, float, float, float, float, int]:
    """Integrate backward to a large-shape section and return diagnostics."""

    def radius_event(_zeta: float, state: np.ndarray) -> float:
        return exit_radius - float(np.hypot(state[0], state[1]))

    radius_event.terminal = True
    radius_event.direction = -1
    solution = solve_ivp(
        shape_field,
        (zeta_start, zeta_end),
        initial_state(kappa, zeta_start, transverse_sign),
        method="DOP853",
        rtol=2e-11,
        atol=2e-13,
        max_step=0.01,
        events=radius_event,
    )
    horizontal, vertical, horizontal_speed, vertical_speed = solution.y
    plus = np.hypot(horizontal + 0.5, vertical)
    minus = np.hypot(horizontal - 0.5, vertical)
    minimum_separation = float(min(np.min(plus), np.min(minus)))
    angular = horizontal * vertical_speed - vertical * horizontal_speed
    angular_crossings = int(np.count_nonzero(angular[1:] * angular[:-1] < 0.0))
    outcome = "radius" if solution.t_events[0].size else "end"
    return (
        outcome,
        float(solution.t[-1]),
        minimum_separation,
        float(angular[-1]),
        float(horizontal[-1]),
        float(vertical[-1]),
        angular_crossings,
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--kappas",
        nargs="+",
        type=float,
        default=[-2.0, 0.0, 1.0, 1.25, 1.26, 1.265, 1.3, 2.0, 5.0],
    )
    parser.add_argument("--zeta-start", type=float, default=22.0)
    parser.add_argument("--zeta-end", type=float, default=-30.0)
    parser.add_argument("--exit-radius", type=float, default=20.0)
    parser.add_argument("--transverse-sign", type=float, default=-1.0)
    args = parser.parse_args()

    print("kappa,outcome,zeta,min_sep,lambda,x,y,lambda_crossings")
    for kappa in args.kappas:
        outcome, zeta, minimum, angular, horizontal, vertical, crossings = probe(
            kappa,
            args.zeta_start,
            args.zeta_end,
            args.exit_radius,
            args.transverse_sign,
        )
        print(
            f"{kappa:.12g},{outcome},{zeta:.12g},{minimum:.12g},"
            f"{angular:.12g},{horizontal:.12g},{vertical:.12g},{crossings}"
        )


if __name__ == "__main__":
    main()
