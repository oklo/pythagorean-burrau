"""Exact finite-parameter expansions around the skinny plunge limit."""

from __future__ import annotations

import sympy as sp


def plunge_symbols() -> tuple[sp.Symbol, sp.Expr, sp.Expr, sp.Expr, sp.Symbol, sp.Symbol]:
    epsilon = sp.symbols("epsilon", positive=True)
    a = sp.sqrt(1 - epsilon**2)
    pair_mass = 1 + a
    total_mass = pair_mass + epsilon
    r, z = sp.symbols("r z", positive=True)
    return epsilon, a, pair_mass, total_mass, r, z


def exact_symmetric_accelerations() -> tuple[sp.Expr, sp.Expr, sp.Expr]:
    """Return (R_x'', Z_y'', Z_x'') on R=(r,0), Z=(0,z).

    These are the exact late-scaled Jacobi fields, evaluated on the symmetric
    limiting subspace.  That subspace is not invariant when epsilon is
    positive; the final component measures its longitudinal failure.
    """
    epsilon, a, pair_mass, total_mass, r, z = plunge_symbols()
    alpha = a / pair_mass
    beta = 1 / pair_mass
    prefactor = total_mass / pair_mass
    d_alpha_cubed = (z**2 + alpha**2 * r**2) ** sp.Rational(3, 2)
    d_beta_cubed = (z**2 + beta**2 * r**2) ** sp.Rational(3, 2)

    radial = (
        -pair_mass / r**2
        + epsilon
        * (-alpha * r / d_alpha_cubed - beta * r / d_beta_cubed)
    )
    outer_vertical = -prefactor * z * (
        a / d_beta_cubed + 1 / d_alpha_cubed
    )
    outer_longitudinal = (
        prefactor
        * alpha
        * r
        * (1 / d_alpha_cubed - 1 / d_beta_cubed)
    )
    return radial, outer_vertical, outer_longitudinal


def taylor_coefficients(expression: sp.Expr, order: int = 2) -> tuple[sp.Expr, ...]:
    """Taylor coefficients at epsilon=0, not derivatives."""
    epsilon, _, _, _, _, _ = plunge_symbols()
    return tuple(
        sp.simplify(
            sp.diff(expression, epsilon, degree).subs(epsilon, 0)
            / sp.factorial(degree)
        )
        for degree in range(order + 1)
    )


def exact_outer_potential() -> tuple[sp.Expr, sp.Symbol]:
    """Return the exact positive outer potential and longitudinal variable."""
    epsilon, a, pair_mass, total_mass, r, z = plunge_symbols()
    x = sp.symbols("x", real=True)
    plus = sp.sqrt((x + r / pair_mass) ** 2 + z**2)
    minus = sp.sqrt((x - a * r / pair_mass) ** 2 + z**2)
    potential = total_mass / pair_mass * (a / plus + 1 / minus)
    return potential, x


def exact_initial_scaled_outer_energy() -> sp.Expr:
    epsilon, a, pair_mass, total_mass, _, _ = plunge_symbols()
    return sp.simplify(
        -epsilon * total_mass / pair_mass * (a + 1 / a)
    )


def exact_initial_tilt() -> sp.Expr:
    epsilon, _, pair_mass, _, _, _ = plunge_symbols()
    return sp.atan(epsilon / pair_mass)
