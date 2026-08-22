"""Exact translation- and rotation-reduced three-body system at zero momentum."""

from __future__ import annotations

import sympy as sp


def symbols() -> dict[str, sp.Symbol]:
    names = "m1 m2 m3 R X Y dR dX dY"
    values = sp.symbols(names, positive=True)
    return dict(zip(names.split(), values, strict=True))


def reduced_expressions() -> dict[str, sp.Expr]:
    s = symbols()
    m1, m2, m3 = s["m1"], s["m2"], s["m3"]
    r, x, y = s["R"], s["X"], s["Y"]
    dr, dx, dy = s["dR"], s["dX"], s["dY"]
    m12 = m1 + m2
    total_mass = m12 + m3
    mu1 = m1 * m2 / m12
    mu2 = m3 * m12 / total_mass
    inertia = mu1 * r**2 + mu2 * (x**2 + y**2)
    shape_angular_momentum = mu2 * (x * dy - y * dx)
    kinetic = (
        mu1 * dr**2 / 2
        + mu2 * (dx**2 + dy**2) / 2
        - shape_angular_momentum**2 / (2 * inertia)
    )
    r13 = sp.sqrt((x + m2 * r / m12) ** 2 + y**2)
    r23 = sp.sqrt((x - m1 * r / m12) ** 2 + y**2)
    potential = m1 * m2 / r + m1 * m3 / r13 + m2 * m3 / r23
    return {
        "mu1": mu1,
        "mu2": mu2,
        "I": inertia,
        "K_reduced": kinetic,
        "U": potential,
        "r12": r,
        "r13": r13,
        "r23": r23,
    }


def normalized_initial_reduced_coordinates() -> dict[str, sp.Expr]:
    u = sp.symbols("u", positive=True)
    a = (1 - u**2) / (1 + u**2)
    b = 2 * u / (1 + u**2)
    return {
        "u": u,
        "m1": a,
        "m2": b,
        "m3": sp.Integer(1),
        "R": sp.Integer(1),
        "X": sp.factor(a * b * (b - a) / (a + b)),
        "Y": sp.factor(a * b),
        "dR": sp.Integer(0),
        "dX": sp.Integer(0),
        "dY": sp.Integer(0),
    }

