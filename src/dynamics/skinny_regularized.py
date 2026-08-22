"""Exact first-encounter Levi--Civita dynamics in scaled skinny variables."""

from __future__ import annotations

from math import sqrt

import numpy as np
from numpy.typing import ArrayLike, NDArray


def _field(vector: NDArray[np.float64]) -> NDArray[np.float64]:
    squared_norm = float(np.dot(vector, vector))
    return vector * squared_norm**-1.5


def initial_regularized_state(epsilon: float) -> NDArray[np.float64]:
    if not 0 < epsilon < 1:
        raise ValueError("epsilon must lie in (0,1)")
    a = sqrt(1 - epsilon * epsilon)
    pair_mass = 1 + a
    # (z, p, inner osculating energy, outer y, outer y_tau, physical tau)
    return np.array(
        [1.0, 0.0, 0.0, 0.0, -1.0, a * epsilon / pair_mass, -a, 0.0, 0.0, 0.0]
    )


def regularized_right_hand_side(
    _regularized_time: float, state: ArrayLike, epsilon: float
) -> NDArray[np.float64]:
    values = np.asarray(state, dtype=float)
    z = complex(values[0], values[1])
    p = complex(values[2], values[3])
    inner_energy = values[4]
    outer = np.array([values[5], values[6]])
    outer_velocity = np.array([values[7], values[8]])
    a = sqrt(1 - epsilon * epsilon)
    pair_mass = 1 + a
    total_mass = pair_mass + epsilon
    radius = abs(z) ** 2
    scaled_inner = np.array([z.real * z.real - z.imag * z.imag, 2 * z.real * z.imag])
    toward_body_3 = outer - a * epsilon * scaled_inner / pair_mass
    toward_body_1 = outer + epsilon * scaled_inner / pair_mass
    scaled_inner_force = epsilon**3 / pair_mass * (
        _field(toward_body_3) - _field(toward_body_1)
    )
    outer_acceleration = -epsilon**3 * total_mass / pair_mass**2 * (
        a * _field(toward_body_1) + _field(toward_body_3)
    )
    force = complex(scaled_inner_force[0], scaled_inner_force[1])
    p_derivative = inner_energy * z / 2 + radius * z.conjugate() * force / 2
    energy_derivative = 2 * (z.conjugate() * p.conjugate() * force).real
    return np.array(
        [
            p.real,
            p.imag,
            p_derivative.real,
            p_derivative.imag,
            energy_derivative,
            *(radius * outer_velocity),
            *(radius * outer_acceleration),
            radius,
        ]
    )


def scaled_inner_angular_momentum(state: ArrayLike) -> float:
    values = np.asarray(state, dtype=float)
    z = complex(values[0], values[1])
    p = complex(values[2], values[3])
    return float(2 * (z.conjugate() * p).imag)

