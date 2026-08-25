#!/usr/bin/env python3
"""Ordinary LC probe of the isosceles base-pair collision unfolding.

The selected pair is (1,2), with ``g=q2-q1=w**2`` and
``G=q3-C12``.  This is a deterministic discovery calculation, not a
validated certificate.
"""

from __future__ import annotations

import numpy as np
from scipy.integrate import solve_ivp


def tied_data(v: float) -> tuple[float, float, np.ndarray]:
    u = (np.sqrt(2.0) - 1.0) * v
    mass_1 = (1.0 - u * u) / (1.0 + u * u)
    mass_2 = 2.0 * u / (1.0 + u * u)
    pair_mass = mass_1 + mass_2
    apex_x = (mass_2 * mass_2 - mass_1 * mass_1) / 2.0
    apex_y = mass_1 * mass_2
    pair_center_x = (mass_2 - mass_1) / (2.0 * pair_mass)
    initial = np.zeros(12)
    initial[0] = 1.0
    initial[4] = -pair_mass
    initial[5] = apex_x - pair_center_x
    initial[6] = apex_y
    initial[10] = mass_1
    initial[11] = mass_2
    return mass_1, mass_2, initial


def field(_sigma: float, state: np.ndarray) -> np.ndarray:
    wr, wi, zr, zi, pair_energy, gx_big, gy_big, px, py, _, mass_1, mass_2 = state
    radius = wr * wr + wi * wi
    gx = wr * wr - wi * wi
    gy = 2.0 * wr * wi
    pair_mass = mass_1 + mass_2
    total_mass = pair_mass + 1.0
    alpha = mass_1 / pair_mass
    beta = mass_2 / pair_mass
    d31 = np.array([gx_big + beta * gx, gy_big + beta * gy])
    d23 = np.array([gx_big - alpha * gx, gy_big - alpha * gy])
    r31_cubed = float(np.dot(d31, d31) ** 1.5)
    r23_cubed = float(np.dot(d23, d23) ** 1.5)
    forcing = d23 / r23_cubed - d31 / r31_cubed
    complement_acceleration = -total_mass / pair_mass * (
        mass_1 * d31 / r31_cubed + mass_2 * d23 / r23_cubed
    )
    force_projection = wr * forcing[0] + wi * forcing[1]
    force_rotation = wr * forcing[1] - wi * forcing[0]
    physical_half_velocity = np.array(
        [wr * zr - wi * zi, wr * zi + wi * zr]
    )
    derivative = np.zeros_like(state)
    derivative[0] = zr
    derivative[1] = zi
    derivative[2] = pair_energy * wr / 2.0 + radius * force_projection / 2.0
    derivative[3] = pair_energy * wi / 2.0 + radius * force_rotation / 2.0
    derivative[4] = 2.0 * float(np.dot(physical_half_velocity, forcing))
    derivative[5] = radius * px
    derivative[6] = radius * py
    derivative[7] = radius * complement_acceleration[0]
    derivative[8] = radius * complement_acceleration[1]
    derivative[9] = radius
    return derivative


def collision_section(_sigma: float, state: np.ndarray) -> float:
    return float(state[0])


collision_section.terminal = True
collision_section.direction = -1


def section_state(v: float) -> tuple[float, np.ndarray]:
    _, _, initial = tied_data(v)
    solution = solve_ivp(
        field,
        (0.0, 10.0),
        initial,
        events=collision_section,
        method="DOP853",
        rtol=2e-13,
        atol=2e-15,
        max_step=2e-4,
    )
    if not solution.success or not solution.t_events[0].size:
        raise RuntimeError("ordinary LC collision-section integration failed")
    return float(solution.t_events[0][0]), solution.y_events[0][0]


def main() -> None:
    sigma, center = section_state(1.0)
    print(
        "status=ORDINARY_NUMERICAL_EVIDENCE "
        f"sigma={sigma:.16g} physical_time={center[9]:.16g} "
        f"zr={center[2]:.16g} G=({center[5]:.16g},{center[6]:.16g})"
    )
    for epsilon in (1e-4, 3e-5, 1e-5, 3e-6, 1e-6, 3e-7, 1e-7):
        sigma_minus, minus = section_state(1.0 - epsilon)
        sigma_plus, plus = section_state(1.0 + epsilon)
        derivative = (plus - minus) / (2.0 * epsilon)
        print(
            f"epsilon={epsilon:.1e} sigma_v={(sigma_plus-sigma_minus)/(2*epsilon):.16g} "
            f"wi_v={derivative[1]:.16g} zi_v={derivative[3]:.16g} "
            f"Gx_v={derivative[5]:.16g} Px_v={derivative[7]:.16g}"
        )


if __name__ == "__main__":
    main()
