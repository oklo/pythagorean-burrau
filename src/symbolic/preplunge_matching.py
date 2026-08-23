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
