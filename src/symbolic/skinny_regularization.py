"""Exact leading coefficients in the skinny Levi--Civita blow-up."""

from __future__ import annotations

import sympy as sp


def encounter_symbols() -> tuple[sp.Symbol, sp.Symbol]:
    epsilon, radius = sp.symbols("epsilon radius", positive=True)
    return epsilon, radius


def scaled_tidal_force_on_radial_orbit() -> tuple[sp.Expr, sp.Expr]:
    """Return the exact longitudinal/transverse scaled perturbing force.

    Coordinates are rotated so the scaled tight-pair vector is ``(radius, 0)``.
    The outer Jacobi vector is frozen at its exact initial value.  The returned
    expressions already include the encounter factor ``epsilon**3/(1+A)``.
    """
    epsilon, radius = encounter_symbols()
    a = sp.sqrt(1 - epsilon**2)
    pair_mass = 1 + a
    outer_x = a * epsilon / pair_mass
    outer_y = -a
    first_x = outer_x - a * epsilon * radius / pair_mass
    second_x = outer_x + epsilon * radius / pair_mass
    first_norm_squared = first_x**2 + outer_y**2
    second_norm_squared = second_x**2 + outer_y**2
    prefactor = epsilon**3 / pair_mass
    force_x = prefactor * (
        first_x / first_norm_squared ** sp.Rational(3, 2)
        - second_x / second_norm_squared ** sp.Rational(3, 2)
    )
    force_y = prefactor * (
        outer_y / first_norm_squared ** sp.Rational(3, 2)
        - outer_y / second_norm_squared ** sp.Rational(3, 2)
    )
    return force_x, force_y


def leading_scaled_force_coefficients() -> tuple[sp.Expr, sp.Expr]:
    epsilon, _ = encounter_symbols()
    force_x, force_y = scaled_tidal_force_on_radial_orbit()
    longitudinal = sp.simplify(sp.limit(force_x / epsilon**4, epsilon, 0))
    transverse = sp.simplify(sp.limit(force_y / epsilon**5, epsilon, 0))
    return longitudinal, transverse


def levi_civita_transverse_displacement_coefficient() -> sp.Expr:
    """Coefficient of ``epsilon**5`` in Im z at the regularized crossing."""
    theta = sp.symbols("theta", real=True)
    cosine_integral = sp.integrate(sp.cos(theta) ** 6, (theta, 0, sp.pi / 2))
    return sp.simplify(-sp.Rational(3, 4) * cosine_integral)


def physical_miss_distance_coefficient() -> sp.Expr:
    coefficient = levi_civita_transverse_displacement_coefficient()
    return sp.expand(coefficient**2)


def physical_angular_momentum_coefficient() -> sp.Expr:
    coefficient = levi_civita_transverse_displacement_coefficient()
    # At the unperturbed crossing p=-1/sqrt(2); conversion back to physical
    # variables contributes another limiting factor sqrt(2).
    return sp.simplify(2 * coefficient)


def initial_outer_radius_squared() -> sp.Expr:
    """Exact squared radius of the light body from the heavy-pair COM."""
    epsilon, _ = encounter_symbols()
    a = sp.sqrt(1 - epsilon**2)
    return sp.simplify(2 * a**2 / (1 + a))


def initial_outer_monopole_energy_series() -> sp.Expr:
    """Series of ``-(A+B+1)/rho`` through cubic order at B=0."""
    epsilon, _ = encounter_symbols()
    a = sp.sqrt(1 - epsilon**2)
    rho = sp.sqrt(initial_outer_radius_squared())
    return sp.series(-(1 + a + epsilon) / rho, epsilon, 0, 4).removeO()
