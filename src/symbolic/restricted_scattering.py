"""Exact identities for the late-plunge rectilinear restricted limit."""

from __future__ import annotations

import sympy as sp


def outer_energy_exchange_identity() -> tuple[sp.Expr, sp.Expr]:
    """Return the derived and expected time derivative of outer energy."""
    z, velocity, separation, separation_velocity = sp.symbols(
        "z velocity separation separation_velocity", real=True
    )
    radius_squared = z**2 + separation**2 / 4
    acceleration = -2 * z / radius_squared ** sp.Rational(3, 2)
    energy = velocity**2 / 2 - 2 / sp.sqrt(radius_squared)
    derivative = (
        sp.diff(energy, z) * velocity
        + sp.diff(energy, velocity) * acceleration
        + sp.diff(energy, separation) * separation_velocity
    )
    expected = (
        separation
        * separation_velocity
        / (2 * radius_squared ** sp.Rational(3, 2))
    )
    return sp.simplify(derivative), expected


def transverse_variational_normal_form() -> sp.Expr:
    """Coefficient after removing the first derivative in the small-speed ODE."""
    phase = sp.symbols("phase", real=True)
    first_derivative_coefficient = 2 * sp.tan(phase)
    zeroth_order_coefficient = 16 * sp.sec(phase) ** 2
    normal_coefficient = (
        zeroth_order_coefficient
        - sp.diff(first_derivative_coefficient, phase) / 2
        - first_derivative_coefficient**2 / 4
    )
    return sp.trigsimp(normal_coefficient)
