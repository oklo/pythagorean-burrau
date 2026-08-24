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


def double_radial_slip_residual(
    x: ArrayLike, y: ArrayLike, x_velocity: ArrayLike, y_velocity: ArrayLike
) -> NDArray[np.float64]:
    """Return two radial rates and relative angular slip.

    This chart is equivalent to a brake residual only when both Jacobi vectors
    are nonzero and total angular momentum vanishes.
    """
    x_array = np.asarray(x, dtype=float)
    y_array = np.asarray(y, dtype=float)
    vx = np.asarray(x_velocity, dtype=float)
    vy = np.asarray(y_velocity, dtype=float)
    x_squared = float(np.dot(x_array, x_array))
    y_squared = float(np.dot(y_array, y_array))
    if x_squared == 0 or y_squared == 0:
        raise ValueError("double-radial chart requires two nonzero Jacobi vectors")
    return np.array(
        [
            np.dot(x_array, vx),
            np.dot(y_array, vy),
            cross2(x_array, vx) / x_squared - cross2(y_array, vy) / y_squared,
        ]
    )


def pair_angular_momentum_brake_residual(
    positions: ArrayLike, velocities: ArrayLike, masses: ArrayLike
) -> NDArray[np.float64]:
    """Return ``(ell_12, ell_23, I_dot)`` about the center of mass.

    At zero total linear and angular momentum this vanishes exactly at a
    labelled brake whenever the configuration is noncollinear. At syzygy the
    residual is degenerate and the Hopf residual must be used instead.
    """
    q = np.asarray(positions, dtype=float)
    v = np.asarray(velocities, dtype=float)
    m = np.asarray(masses, dtype=float)
    total_mass = float(np.sum(m))
    center = np.sum(m[:, None] * q, axis=0) / total_mass
    center_velocity = np.sum(m[:, None] * v, axis=0) / total_mass
    centered_positions = q - center
    centered_velocities = v - center_velocity
    ell_12 = cross2(q[1] - q[0], v[1] - v[0])
    ell_23 = cross2(q[2] - q[1], v[2] - v[1])
    inertia_derivative = 2 * float(
        np.sum(m[:, None] * centered_positions * centered_velocities)
    )
    return np.array([ell_12, ell_23, inertia_derivative])
