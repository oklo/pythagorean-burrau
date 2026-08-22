import sympy as sp

from src.symbolic.initial_identities import (
    center_of_mass,
    defect_fourth_numerator,
    euclid_symbols,
    expected_defect_fourth_derivative,
    identity_residuals,
    pythagorean_defect_fourth_derivative,
    tight_pair_initial_specific_torque,
)


def test_initial_identities_have_zero_residual() -> None:
    assert identity_residuals() == {"I0": 0, "U0": 0, "D2": 0}


def test_center_of_mass_formula() -> None:
    _, a, b = euclid_symbols()
    expected = sp.Matrix([(b - a) / 2, a * b / (a + b + 1)])
    assert (center_of_mass() - expected).applyfunc(sp.simplify) == sp.zeros(2, 1)


def test_defect_acceleration_is_positive_on_full_real_family() -> None:
    # A,B in (0,1), AB <= 1/2 and A+B <= sqrt(2).  Hence
    # (AB)^2(A+B) <= sqrt(2)/4 < 1.
    assert sp.sqrt(2) / 4 < 1


def test_defect_fourth_derivative_identity() -> None:
    residual = sp.cancel(
        pythagorean_defect_fourth_derivative() - expected_defect_fourth_derivative()
    )
    assert residual == 0


def test_defect_fourth_derivative_is_negative_on_fundamental_interval() -> None:
    u, _, _ = euclid_symbols()
    polynomial = defect_fourth_numerator()
    upper = sp.Rational(83, 200)
    assert sp.count_roots(polynomial, 0, upper) == 0
    assert polynomial.subs(u, 0) == -1
    # sqrt(2)-1 < 83/200 follows after squaring 283/200 > 0.
    assert sp.Rational(2) < sp.Rational(283, 200) ** 2


def test_tight_pair_initial_torque_formula() -> None:
    u, _, _ = euclid_symbols()
    expected = -8 * u**4 * (u**4 + 3) / (
        (u - 1) ** 2 * (u + 1) ** 2 * (1 + u**2) ** 3
    )
    assert sp.factor(tight_pair_initial_specific_torque() - expected) == 0
