"""Exact cancellations and clock identities in pre-plunge matching."""

from __future__ import annotations

import sympy as sp


def outer_multipole_moments() -> tuple[sp.Expr, sp.Expr, sp.Expr]:
    """Zeroth, first, and second weighted offset moments in the outer field."""
    a = sp.symbols("A", positive=True)
    pair_mass = 1 + a
    weights = (a, sp.Integer(1))
    offsets = (1 / pair_mass, -a / pair_mass)
    moments = tuple(
        sp.simplify(
            sum(
                weight * offset**degree
                for weight, offset in zip(weights, offsets, strict=True)
            )
            / pair_mass
        )
        for degree in range(3)
    )
    return moments


def lc_clock_identity() -> sp.Expr:
    """Reduce Q_s using the exact LC energy constraint."""
    energy, radius_squared, forcing = sp.symbols("E r2 forcing", real=True)
    momentum_squared = (1 + energy * radius_squared) / 2
    q_derivative = momentum_squared + energy * radius_squared / 2 + forcing
    return sp.simplify(q_derivative)


def transverse_quadrupole_coefficients() -> tuple[sp.Expr, sp.Expr, sp.Expr]:
    """Return early transverse force, averaged tail force, and tail displacement.

    Coefficients refer respectively to ``B**3 R**2/rho**4``, ``Y**-4``,
    and ``Y**-1`` in the binary-axis/outer-line difference.
    """
    binary_square_average = sp.Rational(5, 8)
    early_force = sp.Rational(3, 4)
    averaged_tail_force = sp.simplify(early_force * binary_square_average)
    tail_displacement = sp.simplify(averaged_tail_force / 12)
    return early_force, averaged_tail_force, tail_displacement


def exact_outer_torque_factorization() -> tuple[sp.Expr, sp.Expr]:
    """Return the exact outer Jacobi torque and its cancellation factorization.

    The two inverse-cube distance factors are represented by independent
    symbols.  The identity is polynomial in those factors; substituting their
    radical definitions afterwards recovers the Newtonian formula without
    asking SymPy to simplify nested fractional powers.
    """
    a, total_mass = sp.symbols("A N", positive=True)
    yx, yy, xx, xy = sp.symbols("Yx Yy Xx Xy", real=True)
    inverse_plus, inverse_minus = sp.symbols("p m", positive=True)
    pair_mass = 1 + a
    outer = sp.Matrix([yx, yy])
    binary = sp.Matrix([xx, xy])
    plus = outer + binary / pair_mass
    minus = outer - a * binary / pair_mass
    acceleration = -total_mass / pair_mass * (
        a * plus * inverse_plus + minus * inverse_minus
    )
    torque = sp.expand(outer[0] * acceleration[1] - outer[1] * acceleration[0])
    cross = outer[0] * binary[1] - outer[1] * binary[0]
    factored = (
        -total_mass
        * a
        / pair_mass**2
        * cross
        * (inverse_plus - inverse_minus)
    )
    return sp.expand(torque), sp.expand(factored)
