"""Rotation-invariant Hopf coordinates and the reduced brake residual."""

from __future__ import annotations

import numpy as np
from numpy.typing import ArrayLike, NDArray


def cross2(x: NDArray[np.floating], y: NDArray[np.floating]) -> float:
    return float(x[0] * y[1] - x[1] * y[0])


def jacobi_vectors(
    positions: ArrayLike, masses: ArrayLike
) -> tuple[NDArray[np.float64], NDArray[np.float64]]:
    q = np.asarray(positions, dtype=float)
    m = np.asarray(masses, dtype=float)
    x = q[1] - q[0]
    y = q[2] - (m[0] * q[0] + m[1] * q[1]) / (m[0] + m[1])
    return x, y


def hopf_coordinates(x: ArrayLike, y: ArrayLike) -> NDArray[np.float64]:
    """A complete three-coordinate rotation quotient away from triple collision."""
    x_array = np.asarray(x, dtype=float)
    y_array = np.asarray(y, dtype=float)
    return np.array(
        [
            (np.dot(x_array, x_array) - np.dot(y_array, y_array)) / 2,
            np.dot(x_array, y_array),
            cross2(x_array, y_array),
        ]
    )


def hopf_velocity(
    x: ArrayLike, y: ArrayLike, x_velocity: ArrayLike, y_velocity: ArrayLike
) -> NDArray[np.float64]:
    """The three-component reduced brake residual ``d h / dt``."""
    x_array = np.asarray(x, dtype=float)
    y_array = np.asarray(y, dtype=float)
    vx = np.asarray(x_velocity, dtype=float)
    vy = np.asarray(y_velocity, dtype=float)
    return np.array(
        [
            np.dot(x_array, vx) - np.dot(y_array, vy),
            np.dot(vx, y_array) + np.dot(x_array, vy),
            cross2(vx, y_array) + cross2(x_array, vy),
        ]
    )

