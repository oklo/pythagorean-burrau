import numpy as np
import pytest
import sympy as sp

from src.dynamics.cartesian import right_hand_side
from src.symbolic.mutual_distances import (
    ordered_obtuse_gravity_first_bernstein_coefficients,
    ordered_obtuse_gravity_first_gap,
    ordered_shape_gravity_bernstein_coefficients,
    ordered_shape_gravity_gap,
    squared_distance_accelerations,
)


def test_squared_distance_equations_at_345_launch() -> None:
    expressions = squared_distance_accelerations()
    m1, m2, m3 = sp.symbols("m1 m2 m3", positive=True)
    x, y, z = sp.symbols("x y z", positive=True)
    v23, v31, v12 = sp.symbols("v23sq v31sq v12sq", nonnegative=True)
    a, b = sp.Rational(4, 5), sp.Rational(3, 5)
    substitution = {
        m1: a,
        m2: b,
        m3: 1,
        x: a**2,
        y: b**2,
        z: 1,
        v23: 0,
        v31: 0,
        v12: 0,
    }
    assert sp.simplify(expressions["x_second"].subs(substitution) + 2 * (b + 1) / a + 2 * a**3) == 0
    assert sp.simplify(expressions["y_second"].subs(substitution) + 2 * (a + 1) / b + 2 * b**3) == 0
    assert sp.simplify(
        expressions["z_second"].subs(substitution)
        + 2 * (a + b + 1 / a + 1 / b)
    ) == 0


def test_gravity_widens_second_gap_on_ordered_shape_cube() -> None:
    gap, variables = ordered_shape_gravity_gap()
    numerator, denominator = sp.fraction(gap)
    polynomial = sp.Poly(numerator, *variables)
    assert tuple(polynomial.degree(variable) for variable in variables) == (7, 6, 2)
    coefficients = ordered_shape_gravity_bernstein_coefficients()
    signs = tuple(sp.sign(coefficient) for coefficient in coefficients)
    assert len(coefficients) == 168
    assert signs.count(0) == 31
    assert signs.count(1) == 137
    assert set(signs) == {0, 1}

    t, w, v = variables
    expected_denominator = (
        (t * w - 2) ** 3
        * (-3 * v**2 + 2 * sp.sqrt(2) * v**2 - 1)
        * (t * w - 2 * t + 2) ** 3
    )
    assert sp.factor(denominator - expected_denominator) == 0


def test_gravity_compresses_first_gap_on_ordered_obtuse_rectangle() -> None:
    gap, variables = ordered_obtuse_gravity_first_gap()
    numerator, denominator = sp.fraction(gap)
    polynomial = sp.Poly(numerator, *variables)
    assert tuple(polynomial.degree(variable) for variable in variables) == (7, 6, 2)
    coefficients = ordered_obtuse_gravity_first_bernstein_coefficients()
    signs = tuple(sp.sign(coefficient) for coefficient in coefficients)
    assert len(coefficients) == 168
    assert signs.count(0) == 18
    assert signs.count(-1) == 150
    assert set(signs) == {-1, 0}

    s_value, w, v = variables
    first_denominator = -3 * v**2 + 2 * sp.sqrt(2) * v**2 - 1
    second_denominator = (
        -s_value * w
        + sp.sqrt(2) * s_value * w
        - sp.sqrt(2) * w
        + 2 * w
        - 2
    ) ** 3
    third_denominator = (
        -s_value * w
        + sp.sqrt(2) * s_value * w
        - 2 * sp.sqrt(2) * s_value
        + 2 * s_value
        - sp.sqrt(2) * w
        + 2 * w
        - 2
        + 2 * sp.sqrt(2)
    ) ** 3
    assert sp.factor(
        denominator
        - first_denominator * second_denominator * third_denominator
    ) == 0


@pytest.mark.parametrize(
    ("triangle_scale", "order_split", "parameter"),
    ((0.2, 0.3, 0.25), (0.7, 0.4, 0.6), (0.95, 0.1, 0.9)),
)
def test_ordered_shape_gravity_gap_matches_cartesian_force(
    triangle_scale: float, order_split: float, parameter: float
) -> None:
    u = (np.sqrt(2.0) - 1.0) * parameter
    mass_a = (1 - u * u) / (1 + u * u)
    mass_b = 2 * u / (1 + u * u)
    masses = np.array([mass_a, mass_b, 1.0])
    r23 = 1 - triangle_scale * order_split / 2
    r31 = 1 - triangle_scale + triangle_scale * order_split / 2
    q3x = (r31 * r31 + 1 - r23 * r23) / 2
    q3y = np.sqrt(r31 * r31 - q3x * q3x)
    positions = np.array([[0.0, 0.0], [1.0, 0.0], [q3x, q3y]])
    state = np.concatenate([positions.ravel(), np.zeros(6)])
    accelerations = right_hand_side(0.0, state, masses)[6:].reshape(3, 2)
    radial_23 = np.dot(
        positions[2] - positions[1], accelerations[2] - accelerations[1]
    ) / r23
    radial_31 = np.dot(
        positions[0] - positions[2], accelerations[0] - accelerations[2]
    ) / r31

    gap, variables = ordered_shape_gravity_gap()
    evaluated = float(
        gap.subs(
            dict(
                zip(
                    variables,
                    (triangle_scale, order_split, parameter),
                    strict=True,
                )
            )
        )
    )
    assert radial_23 - radial_31 == pytest.approx(evaluated, rel=2e-12)
    assert evaluated > 0


@pytest.mark.parametrize(
    ("depth", "order_split", "parameter"),
    ((0.1, 0.2, 0.3), (0.5, 0.7, 0.6), (0.9, 0.1, 0.95)),
)
def test_ordered_obtuse_first_gap_matches_cartesian_force(
    depth: float, order_split: float, parameter: float
) -> None:
    u = (np.sqrt(2.0) - 1.0) * parameter
    masses = np.array(
        [(1 - u * u) / (1 + u * u), 2 * u / (1 + u * u), 1.0]
    )
    lower_scale = 2 - np.sqrt(2.0)
    triangle_scale = lower_scale + (1 - lower_scale) * depth
    r23 = 1 - triangle_scale * order_split / 2
    r31 = 1 - triangle_scale + triangle_scale * order_split / 2
    q3x = (r31 * r31 + 1 - r23 * r23) / 2
    q3y = np.sqrt(r31 * r31 - q3x * q3x)
    positions = np.array([[0.0, 0.0], [1.0, 0.0], [q3x, q3y]])
    state = np.concatenate([positions.ravel(), np.zeros(6)])
    accelerations = right_hand_side(0.0, state, masses)[6:].reshape(3, 2)
    radial_12 = np.dot(
        positions[1] - positions[0], accelerations[1] - accelerations[0]
    )
    radial_23 = np.dot(
        positions[2] - positions[1], accelerations[2] - accelerations[1]
    ) / r23

    gap, variables = ordered_obtuse_gravity_first_gap()
    evaluated = float(
        gap.subs(dict(zip(variables, (depth, order_split, parameter), strict=True)))
    )
    assert radial_12 - radial_23 == pytest.approx(evaluated, rel=5e-12)
    assert evaluated < 0
