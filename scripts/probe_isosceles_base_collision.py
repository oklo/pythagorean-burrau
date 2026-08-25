#!/usr/bin/env python3
"""Ordinary LC probe of the isosceles base-pair collision unfolding.

The selected pair is (1,2), with ``g=q2-q1=w**2`` and
``G=q3-C12``.  This is a deterministic discovery calculation, not a
validated certificate.
"""

from __future__ import annotations

import numpy as np
from scipy.integrate import solve_ivp

from src.dynamics.escape_certificate import evaluate_escape_certificate


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


def outgoing_state(v: float, level: float = 0.1) -> tuple[float, np.ndarray]:
    _, _, initial = tied_data(v)

    def outgoing_section(_sigma: float, state: np.ndarray) -> float:
        return float(state[0] + level)

    outgoing_section.terminal = True
    outgoing_section.direction = -1
    solution = solve_ivp(
        field,
        (0.0, 10.0),
        initial,
        events=outgoing_section,
        method="DOP853",
        rtol=2e-13,
        atol=2e-15,
        max_step=2e-4,
    )
    if not solution.success or not solution.t_events[0].size:
        raise RuntimeError("ordinary LC outgoing-section integration failed")
    return float(solution.t_events[0][0]), solution.y_events[0][0]


def explore_regularized_base(final_sigma: float = 7.0) -> None:
    _, _, initial = tied_data(1.0)

    def pair_collision(_sigma: float, state: np.ndarray) -> float:
        return float(state[0])

    def pair_turn(_sigma: float, state: np.ndarray) -> float:
        return float(state[2])

    def central_syzygy(_sigma: float, state: np.ndarray) -> float:
        return float(state[6])

    solution = solve_ivp(
        field,
        (1e-9, final_sigma),
        initial,
        events=(pair_collision, pair_turn, central_syzygy),
        method="DOP853",
        rtol=2e-13,
        atol=2e-15,
        max_step=2e-4,
    )
    print(
        f"base_landscape_success={solution.success} "
        f"message={solution.message!r} final_sigma={solution.t[-1]:.16g}"
    )
    final = solution.y[:, -1]
    radius = final[0] ** 2 + final[1] ** 2
    inner = np.array(
        [final[0] ** 2 - final[1] ** 2, 2 * final[0] * final[1]]
    )
    inner_velocity = np.array(
        [
            2 * (final[0] * final[2] - final[1] * final[3]) / radius,
            2 * (final[0] * final[3] + final[1] * final[2]) / radius,
        ]
    )
    best_certificate = None
    best_eta = None
    for eta in np.geomspace(0.01, 100.0, 2000):
        certificate = evaluate_escape_certificate(
            final[10],
            final[11],
            1.0,
            inner,
            inner_velocity,
            final[5:7],
            final[7:9],
            float(eta),
        )
        if (
            best_certificate is None
            or certificate.inner_energy_margin
            > best_certificate.inner_energy_margin
        ):
            best_certificate = certificate
            best_eta = eta
    assert best_certificate is not None
    fixed_certificate = evaluate_escape_certificate(
        final[10],
        final[11],
        1.0,
        inner,
        inner_velocity,
        final[5:7],
        final[7:9],
        4.0,
    )
    print(
        f"base_final wr={final[0]:.16g} zr={final[2]:.16g} "
        f"Gy={final[6]:.16g} Py={final[8]:.16g} "
        f"pair_energy={final[4]:.16g} best_eta={best_eta:.16g} "
        f"escape_certified={best_certificate.certified} "
        f"separation_margin={best_certificate.separation_margin:.16g} "
        f"radial_margin={best_certificate.radial_energy_margin:.16g} "
        f"inner_margin={best_certificate.inner_energy_margin:.16g}"
    )
    print(
        "base_fixed_escape_eta=4 "
        f"escape_certified={fixed_certificate.certified} "
        f"outer_distance={fixed_certificate.outer_distance:.16g} "
        f"outward_speed={fixed_certificate.outward_radial_speed:.16g} "
        f"inner_energy={fixed_certificate.inner_specific_energy:.16g} "
        f"separation_margin={fixed_certificate.separation_margin:.16g} "
        f"radial_margin={fixed_certificate.radial_energy_margin:.16g} "
        f"tidal_allowance={fixed_certificate.tidal_energy_allowance:.16g} "
        f"inner_margin={fixed_certificate.inner_energy_margin:.16g}"
    )
    for label, times, states in zip(
        ("pair_collision", "pair_turn", "central_syzygy"),
        solution.t_events,
        solution.y_events,
        strict=True,
    ):
        for event_time, state in zip(times[:8], states[:8], strict=True):
            print(
                f"base_event={label} sigma={event_time:.16g} "
                f"physical_time={state[9]:.16g} wr={state[0]:.16g} "
                f"zr={state[2]:.16g} Gy={state[6]:.16g} Py={state[8]:.16g}"
            )


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

    for level in (0.05, 0.1, 0.2, 0.3, 0.5):
        try:
            outgoing_sigma, outgoing = outgoing_state(1.0, level)
        except RuntimeError:
            print(f"outgoing_level={level:.2f} status=NOT_REACHED")
            break
        pair_speed = 2.0 * outgoing[2] / outgoing[0]
        print(
            "outgoing_status=ORDINARY_NUMERICAL_EVIDENCE "
            f"level={level:.2f} sigma={outgoing_sigma:.16g} "
            f"physical_time={outgoing[9]:.16g} "
            f"pair_speed={pair_speed:.16g} pair_energy={outgoing[4]:.16g} "
            f"G=({outgoing[5]:.16g},{outgoing[6]:.16g}) "
            f"P=({outgoing[7]:.16g},{outgoing[8]:.16g})"
        )
    for epsilon in (1e-5, 3e-6, 1e-6, 3e-7):
        sigma_minus, minus = outgoing_state(1.0 - epsilon, 0.1)
        sigma_plus, plus = outgoing_state(1.0 + epsilon, 0.1)
        derivative = (plus - minus) / (2.0 * epsilon)
        print(
            f"outgoing_epsilon={epsilon:.1e} "
            f"sigma_v={(sigma_plus-sigma_minus)/(2*epsilon):.16g} "
            f"wi_v={derivative[1]:.16g} zi_v={derivative[3]:.16g} "
            f"Gx_v={derivative[5]:.16g} Px_v={derivative[7]:.16g}"
        )
    explore_regularized_base()


if __name__ == "__main__":
    main()
