import numpy as np
import pytest
import sympy as sp

from src.dynamics.cartesian import right_hand_side
from src.symbolic.mutual_distances import (
    first_gap_static_energy_obstruction,
    ordered_obtuse_gravity_first_bernstein_coefficients,
    ordered_obtuse_gravity_first_gap,
    ordered_obtuse_log_torque_ratio_gravity_bernstein_coefficients,
    ordered_obtuse_log_torque_ratio_gravity_curvature,
    ordered_shape_gravity_bernstein_coefficients,
    ordered_shape_gravity_gap,
    pair_torque_kinetic_coefficient,
    squared_distance_accelerations,
    torque_history_ratio_identity,
    torque_rate_first_return_static_obstruction,
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


def test_torque_history_ratio_scalar_ode() -> None:
    assert torque_history_ratio_identity() == 0


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


def test_gravity_strictly_decreases_log_torque_rate_ratio() -> None:
    curvature, variables = ordered_obtuse_log_torque_ratio_gravity_curvature()
    numerator, denominator = sp.fraction(curvature)
    polynomial = sp.Poly(numerator, *variables)
    assert tuple(polynomial.degree(variable) for variable in variables) == (9, 9, 2)
    coefficients = (
        ordered_obtuse_log_torque_ratio_gravity_bernstein_coefficients()
    )
    signs = tuple(sp.sign(coefficient) for coefficient in coefficients)
    assert len(coefficients) == 300
    assert signs.count(0) == 32
    assert signs.count(1) == 268
    assert set(signs) == {0, 1}

    s_value, w, v = variables
    triangle_scale = 2 - sp.sqrt(2) + (sp.sqrt(2) - 1) * s_value
    side_23 = 1 - triangle_scale * w / 2
    side_31 = 1 - triangle_scale + triangle_scale * w / 2
    u = (sp.sqrt(2) - 1) * v
    expected_denominator = (
        -4096
        * (1 + u**2)
        * side_23**3
        * side_31**3
        * (1 - side_23**3)
        * (1 - side_31**3)
    )
    assert sp.factor(denominator - expected_denominator) == 0


def test_pair_torque_kinetic_coefficient_matches_gram_inverse() -> None:
    coefficient, variables = pair_torque_kinetic_coefficient()
    m, n, p, q, z = variables
    values = {
        m: sp.Rational(4, 5),
        n: sp.Rational(3, 5),
        p: sp.Rational(4, 5),
        q: sp.Rational(3, 5),
        z: sp.Rational(1, 10),
    }
    mass_12 = values[m] + values[n]
    total_mass = mass_12 + 1
    alpha = values[m] / mass_12
    beta = values[n] / mass_12
    reduced_1 = values[m] * values[n] / mass_12
    reduced_2 = mass_12 / total_mass
    apex_x = (values[q] ** 2 + 1 - values[p] ** 2) / 2
    apex_y = sp.sqrt(values[q] ** 2 - apex_x**2)
    jacobi_x = apex_x - beta
    pair_23_x = jacobi_x - alpha
    pair_31_x = jacobi_x + beta
    inverse_mass_metric = sp.diag(
        1 / reduced_1, 1 / reduced_1, 1 / reduced_2, 1 / reduced_2
    )
    constraints = sp.Matrix(
        [
            [0, reduced_1, -reduced_2 * apex_y, reduced_2 * jacobi_x],
            [
                alpha * apex_y,
                -alpha * pair_23_x,
                -apex_y,
                pair_23_x,
            ],
            [
                -beta * apex_y,
                beta * pair_31_x,
                -apex_y,
                pair_31_x,
            ],
        ]
    )
    gram = constraints * inverse_mass_metric * constraints.T
    target = sp.Matrix([0, 1, -values[z]])
    direct = (target.T * gram.inv() * target)[0]
    assert sp.factor(coefficient.subs(values) - direct) == 0


def test_static_signed_torque_energy_bound_has_exact_obstruction() -> None:
    margin, cube_point = first_gap_static_energy_obstruction()
    assert all(0 < coordinate < 1 for coordinate in cube_point)
    assert sp.sign(margin) == 1
    assert float(margin) == pytest.approx(93.22806690526964, rel=2e-15)


def test_static_first_return_barrier_has_exact_obstruction() -> None:
    obstruction = torque_rate_first_return_static_obstruction()
    assert obstruction["angular_momentum"] == 0
    assert obstruction["log_ratio_rate"] == 0
    assert tuple(
        sp.sign(obstruction[name]) for name in ("ell_12", "ell_23", "ell_31")
    ) == (-1, 1, -1)
    assert sp.sign(obstruction["velocity_curvature"]) == 1
    assert sp.sign(obstruction["kinetic"]) == 1
    assert sp.sign(obstruction["gravity_curvature"]) == -1
    assert sp.sign(obstruction["scaled_curvature_numerator"]) == 1
    assert float(obstruction["scaled_curvature_numerator"]) == pytest.approx(
        10682.0701224264, rel=2e-14
    )


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


@pytest.mark.parametrize(
    ("depth", "order_split", "parameter"),
    ((0.15, 0.25, 0.2), (0.55, 0.65, 0.55), (0.9, 0.15, 0.9)),
)
def test_log_torque_ratio_gravity_curvature_matches_cartesian_force(
    depth: float, order_split: float, parameter: float
) -> None:
    u = (np.sqrt(2.0) - 1.0) * parameter
    masses = np.array(
        [(1 - u * u) / (1 + u * u), 2 * u / (1 + u * u), 1.0]
    )
    triangle_scale = 2 - np.sqrt(2.0) + (np.sqrt(2.0) - 1) * depth
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
    radial_31 = np.dot(
        positions[0] - positions[2], accelerations[0] - accelerations[2]
    ) / r31
    direct = (
        3 * (radial_31 - r31 * radial_12) / (r31 * (1 - r31**3))
        - 3 * (radial_23 - r23 * radial_12) / (r23 * (1 - r23**3))
    )

    curvature, variables = ordered_obtuse_log_torque_ratio_gravity_curvature()
    evaluated = float(
        curvature.subs(
            dict(zip(variables, (depth, order_split, parameter), strict=True))
        )
    )
    assert direct == pytest.approx(evaluated, rel=1e-9)
    assert evaluated < 0
