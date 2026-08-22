"""An exact-inequality terminal escape certificate in Jacobi coordinates."""

from __future__ import annotations

from dataclasses import dataclass
from math import inf, sqrt

import numpy as np
from numpy.typing import ArrayLike


@dataclass(frozen=True)
class EscapeCertificate:
    """Scalar margins for the binary-plus-escaper escape lemma.

    Positive ``separation_margin``, ``radial_energy_margin``, and
    ``inner_energy_margin``, together with positive outward radial speed,
    certify the theorem.  This floating-point helper locates candidate
    sections; a proof for a computed orbit still requires interval enclosures.
    """

    inner_distance: float
    outer_distance: float
    outward_radial_speed: float
    inner_specific_energy: float
    binary_radius_bound: float
    separation_margin: float
    radial_energy_margin: float
    speed_floor: float
    tidal_energy_allowance: float
    inner_energy_margin: float
    certified: bool


def evaluate_escape_certificate(
    mass_a: float,
    mass_b: float,
    mass_c: float,
    inner_vector: ArrayLike,
    inner_velocity: ArrayLike,
    outer_vector: ArrayLike,
    outer_velocity: ArrayLike,
    eta: float,
) -> EscapeCertificate:
    """Evaluate the strict inequalities of the terminal escape theorem."""
    if min(mass_a, mass_b, mass_c, eta) <= 0:
        raise ValueError("masses and eta must be positive")

    x = np.asarray(inner_vector, dtype=float)
    x_velocity = np.asarray(inner_velocity, dtype=float)
    y = np.asarray(outer_vector, dtype=float)
    y_velocity = np.asarray(outer_velocity, dtype=float)
    if any(vector.shape != (2,) for vector in (x, x_velocity, y, y_velocity)):
        raise ValueError("Jacobi vectors and velocities must have shape (2,)")

    inner_distance = float(np.linalg.norm(x))
    outer_distance = float(np.linalg.norm(y))
    if inner_distance == 0 or outer_distance == 0:
        raise ValueError("the certificate is defined only away from collision")

    pair_mass = mass_a + mass_b
    total_mass = pair_mass + mass_c
    radius_bound = pair_mass / eta
    separation_margin = outer_distance - radius_bound
    radial_speed = float(np.dot(y, y_velocity) / outer_distance)
    inner_energy = float(np.dot(x_velocity, x_velocity) / 2 - pair_mass / inner_distance)

    if separation_margin > 0:
        radial_margin = radial_speed**2 / 2 - total_mass / separation_margin
    else:
        radial_margin = -inf

    if radial_margin > 0 and radial_speed > 0:
        speed_floor = sqrt(2 * radial_margin)
        tidal_allowance = (
            mass_c
            * sqrt(2 * pair_mass * radius_bound)
            / (speed_floor * separation_margin**2)
        )
        inner_margin = -eta - inner_energy - tidal_allowance
    else:
        speed_floor = 0.0
        tidal_allowance = inf
        inner_margin = -inf

    certified = (
        separation_margin > 0
        and radial_speed > 0
        and radial_margin > 0
        and inner_margin > 0
    )
    return EscapeCertificate(
        inner_distance=inner_distance,
        outer_distance=outer_distance,
        outward_radial_speed=radial_speed,
        inner_specific_energy=inner_energy,
        binary_radius_bound=radius_bound,
        separation_margin=separation_margin,
        radial_energy_margin=radial_margin,
        speed_floor=speed_floor,
        tidal_energy_allowance=tidal_allowance,
        inner_energy_margin=inner_margin,
        certified=certified,
    )
