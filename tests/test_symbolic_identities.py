import sympy as sp

from src.symbolic.initial_identities import (
    center_of_mass,
    defect_fourth_numerator,
    euclid_symbols,
    expected_defect_fourth_derivative,
    expected_signed_area_second_derivative,
    identity_residuals,
    pythagorean_defect_fourth_derivative,
    signed_area_second_derivative,
    signed_area_second_numerator,
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


def test_signed_area_initial_acceleration_is_negative() -> None:
    u, _, _ = euclid_symbols()
    residual = sp.cancel(
        signed_area_second_derivative() - expected_signed_area_second_derivative()
    )
    assert residual == 0
    numerator = signed_area_second_numerator()
    sturm_sequence = sp.sturm(numerator, u)
    assert len(sturm_sequence) == 11
    expected_signs = (
        (-1, 1, 1, -1, -1, 1, 1, 1, -1, 1, 1),
        (-1, -1, 1, -1, -1, 1, 1, 1, -1, -1, 1),
    )
    for endpoint, signs in zip(
        (sp.Integer(0), sp.Rational(83, 200)), expected_signs, strict=True
    ):
        assert tuple(sp.sign(poly.subs(u, endpoint)) for poly in sturm_sequence) == signs
    assert sp.count_roots(numerator, 0, sp.Rational(83, 200)) == 0
    assert numerator.subs(u, 0) == -1


def test_all_pair_angular_momentum_derivatives_factor_through_area() -> None:
    m1, m2, m3 = sp.symbols("m_1 m_2 m_3", positive=True)
    inv12, inv23, inv31 = sp.symbols("s_12 s_23 s_31", positive=True)
    q1x, q1y, q2x, q2y, q3x, q3y = sp.symbols(
        "q1x q1y q2x q2y q3x q3y", real=True
    )
    q1 = sp.Matrix([q1x, q1y])
    q2 = sp.Matrix([q2x, q2y])
    q3 = sp.Matrix([q3x, q3y])

    def cross(left: sp.Matrix, right: sp.Matrix) -> sp.Expr:
        return left[0] * right[1] - left[1] * right[0]

    a1 = m2 * (q2 - q1) * inv12 + m3 * (q3 - q1) * inv31
    a2 = m1 * (q1 - q2) * inv12 + m3 * (q3 - q2) * inv23
    a3 = m1 * (q1 - q3) * inv31 + m2 * (q2 - q3) * inv23
    twice_area = cross(q2 - q1, q3 - q1)
    actual = (
        cross(q2 - q1, a2 - a1),
        cross(q3 - q2, a3 - a2),
        cross(q1 - q3, a1 - a3),
    )
    expected = (
        m3 * twice_area * (inv23 - inv31),
        m1 * twice_area * (inv31 - inv12),
        m2 * twice_area * (inv12 - inv23),
    )
    assert all(
        sp.expand(left - right) == 0
        for left, right in zip(actual, expected, strict=True)
    )
