"""Exact squared-mutual-distance equations for the planar three-body problem."""

from __future__ import annotations

from functools import lru_cache

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


@lru_cache(maxsize=1)
def _radial_gravity_gaps() -> tuple[sp.Expr, sp.Expr, tuple[sp.Symbol, ...]]:
    """Return unscaled g12-g23 and g23-g31 for tied masses."""
    expressions = squared_distance_accelerations()
    m1, m2, m3 = sp.symbols("m1 m2 m3", positive=True)
    x, y, z = sp.symbols("x y z", positive=True)
    v23, v31, v12 = sp.symbols("v23sq v31sq v12sq", nonnegative=True)
    r23, r31, r12 = sp.symbols("a b c", positive=True)
    u = sp.symbols("u", positive=True)
    mass_a = (1 - u**2) / (1 + u**2)
    mass_b = 2 * u / (1 + u**2)
    substitution = {
        m1: mass_a,
        m2: mass_b,
        m3: 1,
        x: r23**2,
        y: r31**2,
        z: r12**2,
        v23: 0,
        v31: 0,
        v12: 0,
    }
    gravity_23 = expressions["x_second"].subs(substitution) / (2 * r23)
    gravity_31 = expressions["y_second"].subs(substitution) / (2 * r31)
    gravity_12 = expressions["z_second"].subs(substitution) / (2 * r12)
    return (
        gravity_12 - gravity_23,
        gravity_23 - gravity_31,
        (r23, r31, r12, u),
    )


@lru_cache(maxsize=1)
def ordered_shape_gravity_gap() -> tuple[sp.Expr, tuple[sp.Symbol, ...]]:
    """Return g_23-g_31 on the ordered-triangle/fundamental-parameter cube."""
    _, second_gap, physical_variables = _radial_gravity_gaps()
    r23, r31, r12, u = physical_variables
    triangle_scale, order_split, parameter = sp.symbols(
        "t w v", nonnegative=True
    )
    cube_substitution = {
        r23: 1 - triangle_scale * order_split / 2,
        r31: 1 - triangle_scale + triangle_scale * order_split / 2,
        r12: 1,
        u: (sp.sqrt(2) - 1) * parameter,
    }
    gap = sp.factor(
        sp.together(second_gap.subs(cube_substitution))
    )
    return gap, (triangle_scale, order_split, parameter)


def _tensor_bernstein_coefficients(
    numerator: sp.Expr, variables: tuple[sp.Symbol, ...]
) -> tuple[sp.Expr, ...]:
    polynomial = sp.Poly(numerator, *variables)
    degrees = tuple(polynomial.degree(variable) for variable in variables)
    power_coefficients = dict(polynomial.terms())
    result: list[sp.Expr] = []
    for i in range(degrees[0] + 1):
        for j in range(degrees[1] + 1):
            for k in range(degrees[2] + 1):
                order = (i, j, k)
                coefficient = sum(
                    value
                    * sp.binomial(order[0], exponent[0])
                    / sp.binomial(degrees[0], exponent[0])
                    * sp.binomial(order[1], exponent[1])
                    / sp.binomial(degrees[1], exponent[1])
                    * sp.binomial(order[2], exponent[2])
                    / sp.binomial(degrees[2], exponent[2])
                    for exponent, value in power_coefficients.items()
                    if all(
                        exponent[index] <= order[index] for index in range(3)
                    )
                )
                result.append(sp.simplify(coefficient))
    return tuple(result)


@lru_cache(maxsize=1)
def ordered_shape_gravity_bernstein_coefficients() -> tuple[sp.Expr, ...]:
    """Exact tensor Bernstein certificate for ``ordered_shape_gravity_gap``."""
    gap, variables = ordered_shape_gravity_gap()
    numerator, _ = sp.fraction(gap)
    return _tensor_bernstein_coefficients(numerator, variables)


@lru_cache(maxsize=1)
def ordered_obtuse_gravity_first_gap() -> tuple[sp.Expr, tuple[sp.Symbol, ...]]:
    """Return g_12-g_23 on a rectangle containing every ordered obtuse shape."""
    first_gap, _, physical_variables = _radial_gravity_gaps()
    r23, r31, r12, u = physical_variables
    depth, order_split, parameter = sp.symbols("s w v", nonnegative=True)
    lower_scale = 2 - sp.sqrt(2)
    triangle_scale = lower_scale + (1 - lower_scale) * depth
    cube_substitution = {
        r23: 1 - triangle_scale * order_split / 2,
        r31: 1 - triangle_scale + triangle_scale * order_split / 2,
        r12: 1,
        u: (sp.sqrt(2) - 1) * parameter,
    }
    gap = sp.factor(sp.together(first_gap.subs(cube_substitution)))
    return gap, (depth, order_split, parameter)


@lru_cache(maxsize=1)
def ordered_obtuse_gravity_first_bernstein_coefficients() -> tuple[sp.Expr, ...]:
    """Exact tensor Bernstein certificate for the first gravitational gap."""
    gap, variables = ordered_obtuse_gravity_first_gap()
    numerator, _ = sp.fraction(gap)
    return _tensor_bernstein_coefficients(numerator, variables)
