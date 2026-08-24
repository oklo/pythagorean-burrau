"""Brake-event scalars for the global event-topology program.

All functions act on the flat Cartesian state layout of
``src.dynamics.cartesian`` (six positions then six velocities) in the
center-of-mass frame.  The exact identities proved in
``docs/FABLE_EVENT_REDUCTION.md`` are:

* ``I_dot = 0`` and ``zeta = 0`` together are equivalent to a labelled brake
  away from the chart locus ``Y = 0`` (given zero total angular momentum and
  no binary collision);
* ``I_ddot = 2 U - 4 U_0`` on the tied energy shell ``H = -U_0``;
* at every zero of ``I_dot`` that is not a strict local maximum of ``I`` the
  kinetic energy is at least ``U_0``; at a brake ``U = U_0`` and every pair
  separation is at least ``m_i m_j / U_0``.
"""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np
from numpy.typing import ArrayLike, NDArray

from src.dynamics.brake_residual import (
    hopf_velocity,
    jacobi_vectors,
    pair_angular_momentum_brake_residual,
)
from src.dynamics.cartesian import kinetic_energy, mutual_distances


def split_state(
    state: ArrayLike,
) -> tuple[NDArray[np.float64], NDArray[np.float64]]:
    values = np.asarray(state, dtype=float)
    return values[:6].reshape(3, 2), values[6:].reshape(3, 2)


def center_of_mass_frame(
    state: ArrayLike, masses: ArrayLike
) -> NDArray[np.float64]:
    """Return the state translated to the center-of-mass frame."""
    positions, velocities = split_state(state)
    m = np.asarray(masses, dtype=float)
    total = float(np.sum(m))
    positions = positions - np.sum(m[:, None] * positions, axis=0) / total
    velocities = velocities - np.sum(m[:, None] * velocities, axis=0) / total
    return np.concatenate([positions.ravel(), velocities.ravel()])


def moment_of_inertia(state: ArrayLike, masses: ArrayLike) -> float:
    positions, _ = split_state(center_of_mass_frame(state, masses))
    m = np.asarray(masses, dtype=float)
    return float(np.sum(m[:, None] * positions**2))


def moment_derivative(state: ArrayLike, masses: ArrayLike) -> float:
    """d I / dt = 2 sum m_i q_i . v_i in the center-of-mass frame."""
    positions, velocities = split_state(center_of_mass_frame(state, masses))
    m = np.asarray(masses, dtype=float)
    return float(2 * np.sum(m[:, None] * positions * velocities))


def potential(state: ArrayLike, masses: ArrayLike) -> float:
    m = np.asarray(masses, dtype=float)
    r12, r23, r31 = mutual_distances(state)
    return float(m[0] * m[1] / r12 + m[1] * m[2] / r23 + m[2] * m[0] / r31)


def initial_potential(u: float) -> float:
    """U_0 = AB + 1/(AB) for the normalized tied family."""
    denominator = 1 + u * u
    ab = (1 - u * u) / denominator * (2 * u / denominator)
    return ab + 1 / ab


def reduced_masses(masses: ArrayLike) -> tuple[float, float]:
    m = np.asarray(masses, dtype=float)
    mu_1 = m[0] * m[1] / (m[0] + m[1])
    mu_2 = m[2] * (m[0] + m[1]) / np.sum(m)
    return float(mu_1), float(mu_2)


def jacobi_split(
    state: ArrayLike, masses: ArrayLike
) -> tuple[
    NDArray[np.float64],
    NDArray[np.float64],
    NDArray[np.float64],
    NDArray[np.float64],
]:
    positions, velocities = split_state(state)
    m = np.asarray(masses, dtype=float)
    x, y = jacobi_vectors(positions, m)
    vx, vy = jacobi_vectors(velocities, m)
    return x, y, vx, vy


def zeta(state: ArrayLike, masses: ArrayLike) -> complex:
    """The complex brake scalar mu_1 conj(X) X' - mu_2 conj(Y) Y'."""
    x, y, vx, vy = jacobi_split(state, masses)
    mu_1, mu_2 = reduced_masses(masses)
    x_c = complex(x[0], x[1])
    y_c = complex(y[0], y[1])
    vx_c = complex(vx[0], vx[1])
    vy_c = complex(vy[0], vy[1])
    return mu_1 * x_c.conjugate() * vx_c - mu_2 * y_c.conjugate() * vy_c


def hopf_residual(state: ArrayLike, masses: ArrayLike) -> NDArray[np.float64]:
    x, y, vx, vy = jacobi_split(state, masses)
    return hopf_velocity(x, y, vx, vy)


def angular_momentum(state: ArrayLike, masses: ArrayLike) -> float:
    positions, velocities = split_state(center_of_mass_frame(state, masses))
    m = np.asarray(masses, dtype=float)
    return float(
        np.sum(
            m
            * (
                positions[:, 0] * velocities[:, 1]
                - positions[:, 1] * velocities[:, 0]
            )
        )
    )


@dataclass(frozen=True)
class EventRecord:
    """One refined zero of ``I_dot`` along an orbit."""

    time: float
    i_value: float
    i_ddot: float
    kinetic: float
    potential_ratio: float
    residual_norm: float
    zeta_real: float
    zeta_imag: float
    zeta_abs: float
    ell_12: float
    ell_23: float
    min_separation: float
    is_maximum: bool


def event_record(
    time: float, state: ArrayLike, masses: ArrayLike, u_potential_0: float
) -> EventRecord:
    values = center_of_mass_frame(state, masses)
    u_value = potential(values, masses)
    kinetic = kinetic_energy(values, masses)
    i_ddot = 2 * u_value - 4 * u_potential_0
    zeta_value = zeta(values, masses)
    positions, velocities = split_state(values)
    torque_residual = pair_angular_momentum_brake_residual(
        positions, velocities, masses
    )
    return EventRecord(
        time=float(time),
        i_value=moment_of_inertia(values, masses),
        i_ddot=float(i_ddot),
        kinetic=float(kinetic),
        potential_ratio=float(u_value / u_potential_0),
        residual_norm=float(np.linalg.norm(hopf_residual(values, masses))),
        zeta_real=float(zeta_value.real),
        zeta_imag=float(zeta_value.imag),
        zeta_abs=float(abs(zeta_value)),
        ell_12=float(torque_residual[0]),
        ell_23=float(torque_residual[1]),
        min_separation=float(np.min(mutual_distances(values))),
        is_maximum=bool(i_ddot < 0),
    )
