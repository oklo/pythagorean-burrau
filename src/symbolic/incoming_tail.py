"""Exact algebra behind the incoming skinny-tail theorem."""

from __future__ import annotations

import sympy as sp


def lc_normal_invariant_derivatives() -> tuple[sp.Expr, sp.Expr]:
    """Return the exact forced derivatives of the LC invariants L and K."""
    zx, zy, px, py, energy = sp.symbols("zx zy px py E", real=True)
    gx, gy, energy_rate = sp.symbols("gx gy h", real=True)
    state = (zx, zy, px, py, energy)
    vector_field = (
        px,
        py,
        energy * zx / 2 + gx,
        energy * zy / 2 + gy,
        energy_rate,
    )
    angular_momentum = zx * py - zy * px
    fradkin_off_diagonal = px * py - energy * zx * zy / 2

    def lie_derivative(expr: sp.Expr) -> sp.Expr:
        return sp.expand(
            sum(
                sp.diff(expr, variable) * derivative
                for variable, derivative in zip(state, vector_field, strict=True)
            )
        )

    return (
        lie_derivative(angular_momentum),
        lie_derivative(fradkin_off_diagonal),
    )


def lc_normal_jacobian_determinant() -> sp.Expr:
    """Evaluate det d(L,K)/d(zy,py) on the normalized radial LC circle."""
    zx, px = sp.symbols("zx px", real=True)
    determinant = -px**2 - zx**2 / 2
    constraint_substitution = {px**2: (1 - zx**2) / 2}
    return sp.simplify(determinant.subs(constraint_substitution))


def tail_exponents() -> dict[str, sp.Expr]:
    """Return the B exponents of all nontrivial overlap error terms."""
    alpha = sp.symbols("alpha", real=True)
    return {
        "overlap_energy": 3 - 3 * alpha,
        "initial_action_phase": sp.simplify(
            (sp.Rational(5, 2) - 3 * alpha)
            + sp.Rational(3, 2) * (alpha - 1)
        ),
        "energy_time_of_flight": sp.simplify(
            (3 - 3 * alpha) + sp.Rational(5, 2) * (alpha - 1)
        ),
        "mass_frequency_clock": sp.simplify(
            2 + sp.Rational(3, 2) * (alpha - 1)
        ),
    }


def transverse_euler_roots() -> tuple[sp.Expr, ...]:
    """Return the two powers in the limiting transverse Euler equation."""
    exponent = sp.symbols("p")
    polynomial = exponent * (exponent - 1) - exponent / 2 + sp.Rational(1, 2)
    return tuple(sp.solve(polynomial, exponent))


def symmetric_transverse_coefficient_series() -> sp.Expr:
    """Expand the exact reflection-axis transverse coefficient at infinity."""
    inverse_radius, half_binary = sp.symbols("x a", real=True)
    radius = 1 / inverse_radius
    coefficient = (
        2
        * (radius**2 - 2 * half_binary**2)
        / (radius**2 + half_binary**2) ** sp.Rational(5, 2)
    )
    return sp.series(coefficient, inverse_radius, 0, 7).removeO().expand()
