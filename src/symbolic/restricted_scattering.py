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


def time_shift_melnikov_identity() -> tuple[sp.Expr, sp.Expr]:
    """Show that the unnormalized phase Jacobi field gives a boundary term."""
    r, r_velocity, r_acceleration, z, z_velocity = sp.symbols(
        "r r_velocity r_acceleration z z_velocity", real=True
    )
    radius_squared = z**2 + r**2 / 4
    radius = sp.sqrt(radius_squared)
    integrand = (
        (r_velocity**2 + r * r_acceleration) / (2 * radius**3)
        - 3
        * r
        * r_velocity
        * (z * z_velocity + r * r_velocity / 4)
        / (2 * radius**5)
    )
    boundary_term = r * r_velocity / (2 * radius**3)
    derivative = (
        sp.diff(boundary_term, r) * r_velocity
        + sp.diff(boundary_term, r_velocity) * r_acceleration
        + sp.diff(boundary_term, z) * z_velocity
    )
    return sp.simplify(integrand), sp.simplify(derivative)


def phase_wronskian_identity() -> tuple[sp.Expr, sp.Expr]:
    """Wronskian evolution for the centered phase-transversality field."""
    h, h_velocity, z_velocity, z_acceleration = sp.symbols(
        "h h_velocity z_velocity z_acceleration", real=True
    )
    a, b, r_velocity = sp.symbols("a b r_velocity", real=True)
    derivative = (
        h_velocity * z_acceleration
        + h * (a * z_velocity + b * r_velocity)
        - a * h * z_velocity
        - h_velocity * z_acceleration
    )
    expected = h * b * r_velocity
    return sp.simplify(derivative), expected


def maximum_softened_vertical_force() -> tuple[sp.Expr, sp.Expr]:
    """Critical height and force maximum for fixed binary separation."""
    z, separation = sp.symbols("z separation", positive=True)
    force = 2 * z / (z**2 + separation**2 / 4) ** sp.Rational(3, 2)
    critical_height = separation / (2 * sp.sqrt(2))
    maximum = sp.simplify(force.subs(z, critical_height))
    return critical_height, maximum
