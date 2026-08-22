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


def collision_regularized_jacobi_system() -> tuple[sp.Matrix, tuple[sp.Symbol, ...]]:
    """Return the finite CAPD system in eccentric anomaly.

    The state is ``(z,w,q,p)`` with ``w=dz/dtheta``, ``q=h/v`` and
    ``p=dq/dtheta``.  The independent variable is ``psi``, where
    ``r=cos(psi)^2`` and ``dtheta=r*dpsi``.
    """
    psi = sp.symbols("psi", real=True)
    z, w, q, p = sp.symbols("z w q p", real=True)
    separation = sp.cos(psi) ** 2
    radius_squared = z**2 + separation**2 / 4
    coefficient = (4 * z**2 - separation**2 / 2) / radius_squared ** sp.Rational(5, 2)
    system = sp.Matrix(
        [
            separation * w,
            -2 * z * separation / radius_squared ** sp.Rational(3, 2),
            separation * p,
            separation * coefficient * q,
        ]
    )
    return system, (psi, z, w, q, p)


def parabolic_infinity_compactification() -> tuple[sp.Matrix, tuple[sp.Symbol, ...]]:
    """Return the analytic compactified restricted field at parabolic infinity."""
    psi = sp.symbols("psi", real=True)
    x, velocity = sp.symbols("x velocity", real=True)
    separation = sp.cos(psi) ** 2
    field = sp.Matrix(
        [
            -separation * x**3 * velocity / 4,
            -separation
            * x**4
            / (2 * (1 + separation**2 * x**4 / 16) ** sp.Rational(3, 2)),
        ]
    )
    return field, (psi, x, velocity)


def parabolic_stroboscopic_leading_map() -> tuple[sp.Matrix, sp.Matrix]:
    """Degree-four period-map term before and after the stable-ray shear."""
    x, velocity, transverse = sp.symbols("x velocity transverse", real=True)
    original = sp.Matrix([-sp.pi * x**3 * velocity / 8, -sp.pi * x**4 / 4])
    sheared = sp.expand(
        original.subs(velocity, transverse + sp.sqrt(2) * x)
    )
    transformed = sp.Matrix([sheared[0], sp.expand(sheared[1] - sp.sqrt(2) * sheared[0])])
    return original, transformed
