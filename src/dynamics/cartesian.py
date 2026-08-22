"""Deterministic ordinary-precision Cartesian dynamics for falsification probes."""

from __future__ import annotations

from fractions import Fraction

import numpy as np
from numpy.typing import ArrayLike, NDArray

from src.geometry.reductions import normalized_masses, normalized_positions


def initial_state(u: Fraction) -> tuple[NDArray[np.float64], NDArray[np.float64]]:
    masses = np.asarray(normalized_masses(u), dtype=float)
    positions = np.asarray(normalized_positions(u), dtype=float)
    return center_initial_state(masses, positions)


def initial_state_real(u: float) -> tuple[NDArray[np.float64], NDArray[np.float64]]:
    if not 0 < u < 1:
        raise ValueError("u must lie in (0,1)")
    denominator = 1 + u * u
    a = (1 - u * u) / denominator
    b = 2 * u / denominator
    masses = np.array([a, b, 1.0])
    positions = np.array(
        [[-0.5, 0.0], [0.5, 0.0], [(b * b - a * a) / 2, a * b]]
    )
    return center_initial_state(masses, positions)


def center_initial_state(
    masses: NDArray[np.float64], positions: NDArray[np.float64]
) -> tuple[NDArray[np.float64], NDArray[np.float64]]:
    center = np.sum(masses[:, None] * positions, axis=0) / np.sum(masses)
    positions = positions - center
    state = np.concatenate([positions.ravel(), np.zeros(6)])
    return masses, state


def kinetic_energy(state: ArrayLike, masses: ArrayLike) -> float:
    values = np.asarray(state, dtype=float)
    m = np.asarray(masses, dtype=float)
    velocities = values[6:].reshape(3, 2)
    return float(np.sum(m[:, None] * velocities**2) / 2)


def right_hand_side(
    _time: float, state: ArrayLike, masses: ArrayLike
) -> NDArray[np.float64]:
    values = np.asarray(state, dtype=float)
    m = np.asarray(masses, dtype=float)
    positions = values[:6].reshape(3, 2)
    velocities = values[6:].reshape(3, 2)
    accelerations = np.zeros((3, 2))
    for i in range(3):
        for j in range(i + 1, 3):
            delta = positions[j] - positions[i]
            inverse_cube = np.dot(delta, delta) ** -1.5
            accelerations[i] += m[j] * delta * inverse_cube
            accelerations[j] -= m[i] * delta * inverse_cube
    return np.concatenate([velocities.ravel(), accelerations.ravel()])


def mutual_distances(state: ArrayLike) -> NDArray[np.float64]:
    positions = np.asarray(state, dtype=float)[:6].reshape(3, 2)
    return np.array(
        [
            np.linalg.norm(positions[1] - positions[0]),
            np.linalg.norm(positions[2] - positions[1]),
            np.linalg.norm(positions[0] - positions[2]),
        ]
    )


def pythagorean_defect(state: ArrayLike) -> float:
    r12, r23, r31 = mutual_distances(state)
    return float(r12 * r12 - r23 * r23 - r31 * r31)


def energy(state: ArrayLike, masses: ArrayLike) -> float:
    values = np.asarray(state, dtype=float)
    m = np.asarray(masses, dtype=float)
    kinetic = kinetic_energy(values, m)
    r12, r23, r31 = mutual_distances(values)
    potential = m[0] * m[1] / r12 + m[1] * m[2] / r23 + m[2] * m[0] / r31
    return kinetic - potential
