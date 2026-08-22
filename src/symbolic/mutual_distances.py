"""Exact squared-mutual-distance equations for the planar three-body problem."""

from __future__ import annotations

import sympy as sp


def squared_distance_accelerations() -> dict[str, sp.Expr]:
    m1, m2, m3 = sp.symbols("m1 m2 m3", positive=True)
    x, y, z = sp.symbols("x y z", positive=True)
    v23, v31, v12 = sp.symbols("v23sq v31sq v12sq", nonnegative=True)
    x_second = (
        2 * v23
        - 2 * (m2 + m3) / sp.sqrt(x)
        - m1 * ((x + z - y) / z ** sp.Rational(3, 2) + (x + y - z) / y ** sp.Rational(3, 2))
    )
    y_second = (
        2 * v31
        - 2 * (m3 + m1) / sp.sqrt(y)
        - m2 * ((y + x - z) / x ** sp.Rational(3, 2) + (y + z - x) / z ** sp.Rational(3, 2))
    )
    z_second = (
        2 * v12
        - 2 * (m1 + m2) / sp.sqrt(z)
        - m3 * ((z + y - x) / y ** sp.Rational(3, 2) + (z + x - y) / x ** sp.Rational(3, 2))
    )
    return {"x_second": x_second, "y_second": y_second, "z_second": z_second}

