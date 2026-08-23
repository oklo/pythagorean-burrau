import sympy as sp

from src.arithmetic.explicit_skinny_family import (
    family_cycle_count_asymptotic,
    family_cycle_count_second_derivative_asymptotic,
    family_parameter,
    family_reference_cycle_count,
    family_triple,
    nonsquare_quartic_cycle_polynomial,
)


def test_explicit_family_is_pythagorean_and_tied_to_u() -> None:
    index = sp.symbols("index", positive=True)
    a, b, c = family_triple(index)
    u, normalized_a, normalized_b = family_parameter(index)
    assert sp.expand(a**2 + b**2 - c**2) == 0
    assert u == 1 / (2 * index)
    assert sp.simplify(normalized_a - a / c) == 0
    assert sp.simplify(normalized_b - b / c) == 0


def test_explicit_cycle_count_is_the_exact_reference_clock() -> None:
    index = sp.symbols("index", positive=True)
    _, normalized_a, normalized_b = family_parameter(index)
    pair_mass = 1 + normalized_a
    total_mass = pair_mass + normalized_b
    exact_fourth_power = normalized_a**6 / (
        2 * pair_mass * total_mass**2 * normalized_b**6
    )
    assert sp.factor(family_reference_cycle_count(index) ** 4 - exact_fourth_power) == 0


def test_cycle_count_and_curvature_asymptotics() -> None:
    index = sp.symbols("index", positive=True)
    assert family_cycle_count_asymptotic() == (
        index ** sp.Rational(3, 2) / 2
        - sp.sqrt(index) / 8
        - 3 / (64 * sp.sqrt(index))
        + 1 / (256 * index ** sp.Rational(3, 2))
    )
    assert family_cycle_count_second_derivative_asymptotic() == (
        3 / (8 * sp.sqrt(index))
        + 1 / (32 * index ** sp.Rational(3, 2))
        - 9 / (256 * index ** sp.Rational(5, 2))
        + 15 / (1024 * index ** sp.Rational(7, 2))
    )


def test_nonsquare_subfamily_has_irrational_cubic_polynomial() -> None:
    d, m = sp.symbols("d m", positive=True)
    polynomial, remainder_scale = nonsquare_quartic_cycle_polynomial()
    assert polynomial == d ** sp.Rational(3, 2) * m**3 / 2 - sp.sqrt(d) * m / 8
    assert remainder_scale == 1 / (sp.sqrt(d) * m)
