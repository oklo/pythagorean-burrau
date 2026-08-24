"""Exact squared-mutual-distance equations for the planar three-body problem."""

from __future__ import annotations

from collections import defaultdict
from functools import lru_cache
from itertools import product

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
    coefficients = dict(polynomial.terms())
    for axis, degree in enumerate(degrees):
        grouped: defaultdict[tuple[int, ...], dict[int, sp.Expr]] = defaultdict(
            dict
        )
        for exponent, value in coefficients.items():
            other = exponent[:axis] + exponent[axis + 1 :]
            grouped[other][exponent[axis]] = value
        transformed: dict[tuple[int, ...], sp.Expr] = {}
        for other, power_line in grouped.items():
            for order in range(degree + 1):
                value = sum(
                    coefficient
                    * sp.binomial(order, exponent)
                    / sp.binomial(degree, exponent)
                    for exponent, coefficient in power_line.items()
                    if exponent <= order
                )
                key = other[:axis] + (order,) + other[axis:]
                # Only rational binomial factors are introduced here.  An
                # expansion keeps coefficients in canonical Q(sqrt(2)) form
                # and is dramatically faster than general-purpose simplify
                # for the four-dimensional certificate below.
                transformed[key] = sp.expand(value)
        coefficients = transformed
    return tuple(
        coefficients[order]
        for order in product(*(range(degree + 1) for degree in degrees))
    )


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


@lru_cache(maxsize=1)
def _generic_first_gap_energy_margin() -> tuple[
    sp.Expr, sp.Expr, tuple[sp.Symbol, ...]
]:
    """Generic unit-``r12`` signed-torque energy margin."""
    m, n, p, q, z = sp.symbols("m n p q z", positive=True)
    expressions = squared_distance_accelerations()
    m1, m2, m3 = sp.symbols("m1 m2 m3", positive=True)
    x, y, r12_squared = sp.symbols("x y z", positive=True)
    v23, v31, v12 = sp.symbols("v23sq v31sq v12sq", nonnegative=True)
    substitution = {
        m1: m,
        m2: n,
        m3: 1,
        x: p**2,
        y: q**2,
        r12_squared: 1,
        v23: 0,
        v31: 0,
        v12: 0,
    }
    gravity = (
        expressions["z_second"].subs(substitution) / 2
        - expressions["x_second"].subs(substitution) / (2 * p)
    )
    kinetic = _pair_torque_kinetic_coefficient(m, n, p, q, z)
    potential = m * n + n / p + m / q
    centrifugal = (1 / m - z / n) ** 2 - 1 / p**3
    margin = sp.cancel(gravity + 2 * potential * centrifugal / kinetic)
    return margin, kinetic, (m, n, p, q, z)


@lru_cache(maxsize=1)
def _generic_signed_torque_first_gap_margin() -> tuple[
    sp.Expr, tuple[sp.Symbol, ...]
]:
    """Generic energy margin with the full pre-syzygy torque sign cone."""
    margin, _, variables = _generic_first_gap_energy_margin()
    m, n, p, q, z = variables
    h = sp.symbols("h", nonnegative=True)
    signed_margin = sp.cancel(margin.subs(z, n * h / m))
    return signed_margin, (m, n, p, q, h)


@lru_cache(maxsize=1)
def first_gap_static_energy_obstruction() -> tuple[
    sp.Expr, tuple[sp.Rational, ...]
]:
    """Exact interior point where the optimal static energy bound is positive.

    This disproves the proposed implication from ordered right/obtuse shape,
    the pre-syzygy torque signs, zero angular momentum, and total energy alone
    to ``(r12-r23)''<0``. It does not describe a reachable Burrau state.
    """
    depth = sp.Rational(99, 100)
    order_split = sp.Rational(1, 10**6)
    parameter = sp.Rational(99, 100)
    torque_ratio = sp.Rational(1, 10**6)
    root_two_minus_one = sp.sqrt(2) - 1
    triangle_scale = (
        2
        - sp.sqrt(2)
        + root_two_minus_one * depth
    )
    side_23 = 1 - triangle_scale * order_split / 2
    side_31 = 1 - triangle_scale + triangle_scale * order_split / 2
    tied_parameter = root_two_minus_one * parameter
    mass_1 = (1 - tied_parameter**2) / (1 + tied_parameter**2)
    mass_2 = 2 * tied_parameter / (1 + tied_parameter**2)
    margin, variables = _generic_signed_torque_first_gap_margin()
    m, n, p, q, h = variables
    value = sp.cancel(
        margin.subs(
            {
                m: mass_1,
                n: mass_2,
                p: side_23,
                q: side_31,
                h: torque_ratio,
            }
        )
    )
    return value, (depth, order_split, parameter, torque_ratio)


def _pair_torque_kinetic_coefficient(
    mass_1: sp.Expr,
    mass_2: sp.Expr,
    side_23: sp.Expr,
    side_31: sp.Expr,
    torque_ratio: sp.Expr,
) -> sp.Expr:
    """Closed Gram-inverse coefficient for ``ell23=1, ell31=-ratio``.

    The third mass and ``r12`` are one. This expression is the exact result
    of minimizing twice the kinetic energy over translation-reduced
    velocities subject to total angular momentum zero and the two stated
    pair angular momenta.
    """
    m = mass_1
    n = mass_2
    p = side_23
    q = side_31
    z = torque_ratio
    numerator = (
        m**2 * n**2 * z
        - m**2 * n**2 * p**2 * z**2
        - m**2 * n**2 * p**2 * z
        - m**2 * n**2 * q**2 * z
        - m**2 * n**2 * q**2
        - m**2 * n * p**2 * z**2
        + m**2 * n * q**2 * z
        + m * n**2 * p**2 * z
        - m * n**2 * q**2
        + m**2 * n * p**4 * z**2
        - m**2 * n * p**2 * q**2 * z**2
        + m**2 * n * p**2 * q**2 * z
        - m**2 * n * q**4 * z
        - m**2 * p**2 * q**2 * z**2
        - m * n**2 * p**4 * z
        + m * n**2 * p**2 * q**2 * z
        - m * n**2 * p**2 * q**2
        + m * n**2 * q**4
        + 2 * m * n * p**2 * q**2 * z
        - n**2 * p**2 * q**2
    )
    heron_product = (
        (-1 + p - q) * (-1 + p + q) * (1 + p - q) * (1 + p + q)
    )
    denominator = m * n * heron_product * (m * n + m * q**2 + n * p**2)
    return 4 * numerator / denominator


def pair_torque_kinetic_coefficient() -> tuple[
    sp.Expr, tuple[sp.Symbol, ...]
]:
    """Return the generic optimal kinetic coefficient and its variables."""
    m, n, p, q, z = sp.symbols("m n p q z", positive=True)
    return _pair_torque_kinetic_coefficient(m, n, p, q, z), (m, n, p, q, z)
