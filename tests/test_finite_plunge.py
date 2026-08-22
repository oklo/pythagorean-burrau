import sympy as sp

from src.symbolic.finite_plunge import (
    exact_initial_scaled_outer_energy,
    exact_initial_tilt,
    exact_outer_potential,
    exact_symmetric_accelerations,
    plunge_symbols,
    taylor_coefficients,
)


def test_symmetric_field_coefficients_through_second_order() -> None:
    _, _, _, _, r, z = plunge_symbols()
    d = sp.sqrt(z**2 + r**2 / 4)
    radial, vertical, longitudinal = exact_symmetric_accelerations()
    expected_radial = (
        -2 / r**2,
        -r / d**3,
        1 / (2 * r**2),
    )
    expected_vertical = (
        -2 * z / d**3,
        -z / d**3,
        z / (2 * d**3),
    )
    expected_longitudinal = (
        0,
        0,
        3 * r**3 / (16 * d**5),
    )
    for actual, expected in zip(
        taylor_coefficients(radial), expected_radial, strict=True
    ):
        assert sp.simplify(actual - expected) == 0
    for actual, expected in zip(
        taylor_coefficients(vertical), expected_vertical, strict=True
    ):
        assert sp.simplify(actual - expected) == 0
    for actual, expected in zip(
        taylor_coefficients(longitudinal), expected_longitudinal, strict=True
    ):
        assert sp.simplify(actual - expected) == 0


def test_potential_coefficients_and_symmetry_breaking_gradient() -> None:
    _, _, _, _, r, z = plunge_symbols()
    d = sp.sqrt(z**2 + r**2 / 4)
    potential, x = exact_outer_potential()
    coefficients = taylor_coefficients(potential)
    plus_squared = (x + r / 2) ** 2 + z**2
    minus_squared = (x - r / 2) ** 2 + z**2
    expected_second = (
        -1 / (2 * sp.sqrt(plus_squared))
        - r * (x + r / 2) / (8 * plus_squared ** sp.Rational(3, 2))
        - r * (x - r / 2) / (8 * minus_squared ** sp.Rational(3, 2))
    )
    assert sp.simplify(coefficients[2] - expected_second) == 0
    expected = (
        2 / d,
        1 / d,
        -1 / (2 * d),
    )
    for actual, target in zip(coefficients, expected, strict=True):
        assert sp.simplify(actual.subs(x, 0) - target) == 0
    gradient = sp.diff(coefficients[2], x).subs(x, 0)
    assert sp.simplify(gradient - 3 * r**3 / (16 * d**5)) == 0


def test_initial_energy_and_tilt_expansions() -> None:
    epsilon, a, _, _, _, _ = plunge_symbols()
    energy = exact_initial_scaled_outer_energy()
    assert sp.limit(energy / epsilon, epsilon, 0) == -2
    assert sp.limit((energy + 2 * epsilon) / epsilon**2, epsilon, 0) == -1
    assert sp.limit((energy + 2 * epsilon + epsilon**2) / epsilon**3, epsilon, 0) == 0

    tangent = sp.tan(exact_initial_tilt())
    assert sp.simplify(2 * tangent / (1 + tangent**2) - epsilon) == 0
    assert sp.simplify((1 - tangent**2) / (1 + tangent**2) - a) == 0
