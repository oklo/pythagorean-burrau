import sympy as sp

from src.symbolic.initial_identities import (
    center_of_mass,
    defect_fourth_bernstein_coefficients,
    defect_fourth_numerator,
    defect_sixth_bernstein_coefficients,
    defect_sixth_numerator,
    euclid_symbols,
    expected_defect_fourth_derivative,
    expected_defect_sixth_derivative,
    expected_initial_side_order_second_derivatives,
    expected_signed_area_second_derivative,
    identity_residuals,
    initial_side_order_second_derivatives,
    pythagorean_defect_fourth_derivative,
    pythagorean_defect_sixth_derivative,
    side_order_first_bernstein_coefficients,
    signed_area_second_bernstein_coefficients,
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


def test_fourth_derivative_has_negative_bernstein_certificate() -> None:
    expected = (
        sp.Rational(-1),
        sp.Rational(-19, 20),
        sp.Rational(-86, 95),
        sp.Rational(-1313, 1520),
        sp.Rational(-63901, 77520),
        sp.Rational(-3823, 4864),
        sp.Rational(-185677, 248064),
        sp.Rational(-1177527, 1653760),
        sp.Rational(-1819581, 2687360),
        sp.Rational(-27715771, 42997760),
        sp.Rational(-58252257, 94595072),
        sp.Rational(-101898611, 171991040),
        sp.Rational(-24804157, 42997760),
        sp.Rational(-181712839, 317521920),
        sp.Rational(-37060991, 63504384),
        sp.Rational(-157122943, 254017536),
        sp.Rational(-219023483, 317521920),
        sp.Rational(-10188109, 12451840),
        sp.Rational(-25856203, 24903680),
        sp.Rational(-3686723, 2621440),
        sp.Rational(-2112047, 1048576),
    )
    assert defect_fourth_bernstein_coefficients() == expected
    assert all(coefficient < 0 for coefficient in expected)


def test_defect_sixth_derivative_identity() -> None:
    residual = sp.cancel(
        pythagorean_defect_sixth_derivative() - expected_defect_sixth_derivative()
    )
    assert residual == 0


def test_sixth_derivative_has_positive_bernstein_certificate() -> None:
    expected = (
        sp.Rational(19),
        sp.Rational(266, 15),
        sp.Rational(28861, 1740),
        sp.Rational(63103, 4060),
        sp.Rational(6395887, 438480),
        sp.Rational(7813165, 570024),
        sp.Rational(97995461, 7600320),
        sp.Rational(395397937, 32572800),
        sp.Rational(1903835447, 166483200),
        sp.Rational(822381181, 76304800),
        sp.Rational(44652539959, 4395156480),
        sp.Rational(1062904231, 110988800),
        sp.Rational(46339562047, 5134438400),
        sp.Rational(57924715549, 6813004800),
        sp.Rational(73076017417, 9128755200),
        sp.Rational(34682896469, 4604067840),
        sp.Rational(147143231691, 20763443200),
        sp.Rational(13083275107261, 1962145382400),
        sp.Rational(142418163589111, 22673679974400),
        sp.Rational(4249318181351, 716010946560),
        sp.Rational(177734203151437, 31504481648640),
        sp.Rational(1849150776667, 340957593600),
        sp.Rational(43499899224473, 8182982246400),
        sp.Rational(3826743850991, 711563673600),
        sp.Rational(18951324099991, 3320630476800),
        sp.Rational(644065041443, 99618914304),
        sp.Rational(14565220793867, 1839118417920),
        sp.Rational(178980837823, 17028874240),
        sp.Rational(1746818009353, 116769423360),
        sp.Rational(2824577023, 125829120),
        sp.Rational(37475266287, 1073741824),
    )
    assert defect_sixth_numerator().subs(euclid_symbols()[0], 0) == 19
    assert defect_sixth_bernstein_coefficients() == expected
    assert all(coefficient > 0 for coefficient in expected)


def test_tight_pair_initial_torque_formula() -> None:
    u, _, _ = euclid_symbols()
    expected = -8 * u**4 * (u**4 + 3) / (
        (u - 1) ** 2 * (u + 1) ** 2 * (1 + u**2) ** 3
    )
    assert sp.factor(tight_pair_initial_specific_torque() - expected) == 0


def test_initial_side_order_accelerations_and_sign_certificates() -> None:
    actual = initial_side_order_second_derivatives()
    expected = expected_initial_side_order_second_derivatives()
    assert all(
        sp.factor(sp.cancel(left - right)) == 0
        for left, right in zip(actual, expected, strict=True)
    )
    bernstein = (
        sp.Rational(1),
        sp.Rational(103, 108),
        sp.Rational(2377, 2592),
        sp.Rational(64471, 72576),
        sp.Rational(5027, 5832),
        sp.Rational(3244279, 3919104),
        sp.Rational(96520723, 125411328),
        sp.Rational(428088589, 644972544),
        sp.Rational(615514573, 1289945088),
        sp.Rational(850511897, 5159780352),
    )
    assert side_order_first_bernstein_coefficients() == bernstein
    assert all(coefficient > 0 for coefficient in bernstein)


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


def test_signed_area_numerator_has_negative_bernstein_certificate() -> None:
    expected = (
        sp.Rational(-1),
        sp.Rational(-9, 10),
        sp.Rational(-49, 60),
        sp.Rational(-181, 240),
        sp.Rational(-241, 336),
        sp.Rational(-179, 252),
        sp.Rational(-991, 1344),
        sp.Rational(-3091, 3840),
        sp.Rational(-10693, 11520),
        sp.Rational(-2919, 2560),
        sp.Rational(-1543, 1024),
    )
    assert signed_area_second_bernstein_coefficients() == expected
    assert all(coefficient < 0 for coefficient in expected)


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


def test_pair_angular_momenta_reconstruct_total_angular_momentum() -> None:
    m1, m2, m3 = sp.symbols("m_1 m_2 m_3", positive=True)
    symbols = sp.symbols(
        "q1x q1y q2x q2y q3x q3y v1x v1y v2x v2y v3x v3y", real=True
    )
    q1 = sp.Matrix(symbols[0:2])
    q2 = sp.Matrix(symbols[2:4])
    q3 = sp.Matrix(symbols[4:6])
    v1 = sp.Matrix(symbols[6:8])
    v2 = sp.Matrix(symbols[8:10])
    v3 = sp.Matrix(symbols[10:12])

    def cross(left: sp.Matrix, right: sp.Matrix) -> sp.Expr:
        return left[0] * right[1] - left[1] * right[0]

    pair_sum = (
        m1 * m2 * cross(q2 - q1, v2 - v1)
        + m2 * m3 * cross(q3 - q2, v3 - v2)
        + m3 * m1 * cross(q1 - q3, v1 - v3)
    )
    total_mass = m1 + m2 + m3
    angular_momentum = (
        m1 * cross(q1, v1) + m2 * cross(q2, v2) + m3 * cross(q3, v3)
    )
    weighted_position = m1 * q1 + m2 * q2 + m3 * q3
    momentum = m1 * v1 + m2 * v2 + m3 * v3
    expected = total_mass * angular_momentum - cross(weighted_position, momentum)
    assert sp.expand(pair_sum - expected) == 0
