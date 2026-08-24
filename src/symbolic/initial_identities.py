"""Computer-algebra checks for the initial Pythagorean--Burrau identities."""

from __future__ import annotations

import sympy as sp


def _bernstein_coefficients_on_half_interval(
    expression: sp.Expr, degree: int, variable: sp.Symbol
) -> tuple[sp.Rational, ...]:
    """Return coefficients of expression(t/2) in a fixed Bernstein basis."""
    polynomial = sp.Poly(expression.subs(variable, variable / 2), variable)
    power_coefficients = [polynomial.nth(index) for index in range(degree + 1)]
    return tuple(
        sp.factor(
            sum(
                power_coefficients[index]
                * sp.binomial(order, index)
                / sp.binomial(degree, index)
                for index in range(order + 1)
            )
        )
        for order in range(degree + 1)
    )


def euclid_symbols() -> tuple[sp.Symbol, sp.Expr, sp.Expr]:
    u = sp.symbols("u", positive=True)
    a = (1 - u**2) / (1 + u**2)
    b = 2 * u / (1 + u**2)
    return u, a, b


def initial_data() -> tuple[list[sp.Expr], list[sp.Matrix]]:
    _, a, b = euclid_symbols()
    masses = [a, b, sp.Integer(1)]
    positions = [
        sp.Matrix([-sp.Rational(1, 2), 0]),
        sp.Matrix([sp.Rational(1, 2), 0]),
        sp.Matrix([(b**2 - a**2) / 2, a * b]),
    ]
    return masses, positions


def accelerations(
    masses: list[sp.Expr], positions: list[sp.Matrix]
) -> list[sp.Matrix]:
    _, a, b = euclid_symbols()
    known_distances = {(0, 1): sp.Integer(1), (0, 2): b, (1, 2): a}
    result: list[sp.Matrix] = []
    for i, qi in enumerate(positions):
        acceleration = sp.zeros(2, 1)
        for j, qj in enumerate(positions):
            if i == j:
                continue
            delta = qj - qi
            distance = known_distances[tuple(sorted((i, j)))]
            # These distances are independently checked from delta.dot(delta).
            acceleration += masses[j] * delta / distance**3
        result.append(acceleration.applyfunc(sp.factor))
    return result


def center_of_mass() -> sp.Matrix:
    masses, positions = initial_data()
    total_mass = sum(masses)
    weighted_sum = sum(
        (masses[i] * positions[i] for i in range(3)), sp.zeros(2, 1)
    )
    return sp.simplify(weighted_sum / total_mass)


def moment_of_inertia() -> sp.Expr:
    masses, positions = initial_data()
    center = center_of_mass()
    return sp.factor(
        sum(masses[i] * (positions[i] - center).dot(positions[i] - center) for i in range(3))
    )


def potential_magnitude() -> sp.Expr:
    masses, _ = initial_data()
    _, a, b = euclid_symbols()
    return sp.factor(masses[0] * masses[1] + masses[0] / b + masses[1] / a)


def pythagorean_defect_second_derivative() -> sp.Expr:
    """Return ``D''(0)`` from Newton's equations, not a preloaded formula."""
    masses, positions = initial_data()
    accels = accelerations(masses, positions)

    def squared_distance_second(i: int, j: int) -> sp.Expr:
        # Initial velocities vanish, so the usual 2|v_j-v_i|^2 term is zero.
        return 2 * (positions[j] - positions[i]).dot(accels[j] - accels[i])

    # r_c=r_12, r_a=r_23, r_b=r_31.
    value = (
        squared_distance_second(0, 1)
        - squared_distance_second(1, 2)
        - squared_distance_second(2, 0)
    )
    return sp.factor(sp.trigsimp(sp.powdenest(value, force=True)))


def pythagorean_defect_fourth_derivative() -> sp.Expr:
    """Return ``D''''(0)`` by twice differentiating Newton's force."""
    masses, positions = initial_data()
    accels = accelerations(masses, positions)
    _, a, b = euclid_symbols()
    known_distances = {(0, 1): sp.Integer(1), (0, 2): b, (1, 2): a}
    fourth_derivatives: list[sp.Matrix] = []
    for i, qi in enumerate(positions):
        value = sp.zeros(2, 1)
        for j, qj in enumerate(positions):
            if i == j:
                continue
            delta = qj - qi
            delta_acceleration = accels[j] - accels[i]
            distance = known_distances[tuple(sorted((i, j)))]
            value += masses[j] * (
                delta_acceleration / distance**3
                - 3
                * delta
                * delta.dot(delta_acceleration)
                / distance**5
            )
        fourth_derivatives.append(value.applyfunc(sp.factor))

    def squared_distance_fourth(i: int, j: int) -> sp.Expr:
        delta = positions[j] - positions[i]
        delta_acceleration = accels[j] - accels[i]
        delta_fourth = fourth_derivatives[j] - fourth_derivatives[i]
        return 6 * delta_acceleration.dot(delta_acceleration) + 2 * delta.dot(
            delta_fourth
        )

    value = (
        squared_distance_fourth(0, 1)
        - squared_distance_fourth(1, 2)
        - squared_distance_fourth(2, 0)
    )
    return sp.factor(sp.cancel(value))


def defect_fourth_numerator() -> sp.Expr:
    u, _, _ = euclid_symbols()
    return (
        u**20
        - 4 * u**19
        + 10 * u**18
        - 84 * u**17
        + 25 * u**16
        - 78 * u**15
        + 142 * u**14
        - 366 * u**13
        - 168 * u**12
        + 122 * u**11
        - 126 * u**10
        - 614 * u**9
        + 192 * u**8
        - 58 * u**7
        - 22 * u**6
        + 38 * u**5
        - 49 * u**4
        + 18 * u**3
        - 4 * u**2
        + 2 * u
        - 1
    )


def defect_fourth_bernstein_coefficients() -> tuple[sp.Rational, ...]:
    """Coefficients of P_20(t/2) in the degree-20 Bernstein basis."""
    u, _, _ = euclid_symbols()
    return _bernstein_coefficients_on_half_interval(
        defect_fourth_numerator(), 20, u
    )


def expected_defect_fourth_derivative() -> sp.Expr:
    u, _, _ = euclid_symbols()
    denominator = u**4 * (u - 1) ** 4 * (u + 1) ** 2 * (1 + u**2) ** 4
    return defect_fourth_numerator() / denominator


def pythagorean_defect_sixth_derivative() -> sp.Expr:
    """Return ``D^(6)(0)`` from an exact even force-series recurrence."""
    masses, positions = initial_data()
    initial_accelerations = accelerations(masses, positions)
    _, a, b = euclid_symbols()
    known_distances = {(0, 1): sp.Integer(1), (0, 2): b, (1, 2): a}
    position_two = [value / 2 for value in initial_accelerations]

    def force_coefficient(
        delta_zero: sp.Matrix,
        delta_two: sp.Matrix,
        delta_four: sp.Matrix,
        distance: sp.Expr,
        order: int,
    ) -> sp.Matrix:
        squared_one = 2 * delta_zero.dot(delta_two)
        if order == 1:
            return delta_two / distance**3 - (
                sp.Rational(3, 2)
                * delta_zero
                * squared_one
                / distance**5
            )
        squared_two = 2 * delta_zero.dot(delta_four) + delta_two.dot(delta_two)
        return (
            delta_four / distance**3
            - sp.Rational(3, 2) * delta_two * squared_one / distance**5
            + delta_zero
            * (
                -sp.Rational(3, 2) * squared_two / distance**5
                + sp.Rational(15, 8) * squared_one**2 / distance**7
            )
        )

    acceleration_two: list[sp.Matrix] = []
    for i in range(3):
        value = sp.zeros(2, 1)
        for j in range(3):
            if i == j:
                continue
            key = tuple(sorted((i, j)))
            value += masses[j] * force_coefficient(
                positions[j] - positions[i],
                position_two[j] - position_two[i],
                sp.zeros(2, 1),
                known_distances[key],
                1,
            )
        acceleration_two.append(value.applyfunc(sp.factor))
    position_four = [value / 12 for value in acceleration_two]

    acceleration_four: list[sp.Matrix] = []
    for i in range(3):
        value = sp.zeros(2, 1)
        for j in range(3):
            if i == j:
                continue
            key = tuple(sorted((i, j)))
            value += masses[j] * force_coefficient(
                positions[j] - positions[i],
                position_two[j] - position_two[i],
                position_four[j] - position_four[i],
                known_distances[key],
                2,
            )
        acceleration_four.append(
            value.applyfunc(lambda expression: sp.factor(sp.cancel(expression)))
        )
    position_six = [value / 30 for value in acceleration_four]

    def squared_distance_six_coefficient(i: int, j: int) -> sp.Expr:
        delta_zero = positions[j] - positions[i]
        delta_two = position_two[j] - position_two[i]
        delta_four = position_four[j] - position_four[i]
        delta_six = position_six[j] - position_six[i]
        return 2 * delta_zero.dot(delta_six) + 2 * delta_two.dot(delta_four)

    coefficient = (
        squared_distance_six_coefficient(0, 1)
        - squared_distance_six_coefficient(1, 2)
        - squared_distance_six_coefficient(2, 0)
    )
    return sp.factor(sp.cancel(sp.factorial(6) * coefficient))


def defect_sixth_numerator() -> sp.Expr:
    u, _, _ = euclid_symbols()
    return (
        3 * u**30
        - 68 * u**29
        + 897 * u**28
        - 2712 * u**27
        + 12919 * u**26
        - 14924 * u**25
        + 16261 * u**24
        - 10376 * u**23
        + 147823 * u**22
        - 172284 * u**21
        + 36741 * u**20
        + 412240 * u**19
        - 202573 * u**18
        - 113044 * u**17
        + 445241 * u**16
        + 68720 * u**15
        - 160855 * u**14
        + 102884 * u**13
        + 24931 * u**12
        + 32008 * u**11
        + 15685 * u**10
        - 28244 * u**9
        + 15087 * u**8
        - 7784 * u**7
        + 6565 * u**6
        - 3620 * u**5
        + 1495 * u**4
        - 576 * u**3
        + 209 * u**2
        - 76 * u
        + 19
    )


def expected_defect_sixth_derivative() -> sp.Expr:
    u, _, _ = euclid_symbols()
    denominator = 8 * u**7 * (1 - u) ** 7 * (1 + u) ** 3 * (1 + u**2) ** 5
    return -defect_sixth_numerator() / denominator


def defect_sixth_bernstein_coefficients() -> tuple[sp.Rational, ...]:
    """Coefficients of R_30(t/2) in the degree-30 Bernstein basis."""
    u, _, _ = euclid_symbols()
    return _bernstein_coefficients_on_half_interval(
        defect_sixth_numerator(), 30, u
    )


def tight_pair_initial_specific_torque() -> sp.Expr:
    """Derive the initial tight-pair specific torque from Newton acceleration."""
    masses, positions = initial_data()
    newton_accelerations = accelerations(masses, positions)
    tight_vector = positions[2] - positions[0]
    tight_acceleration = newton_accelerations[2] - newton_accelerations[0]
    cross = tight_vector[0] * tight_acceleration[1] - tight_vector[1] * tight_acceleration[0]
    return sp.factor(sp.simplify(cross))


def initial_side_order_second_derivatives() -> tuple[sp.Expr, sp.Expr]:
    """Return second derivatives of r12-r23 and r23-r31 at the brake."""
    masses, positions = initial_data()
    newton_accelerations = accelerations(masses, positions)
    _, a, b = euclid_symbols()
    known_distances = {(0, 1): sp.Integer(1), (1, 2): a, (2, 0): b}

    def distance_second(i: int, j: int) -> sp.Expr:
        delta = positions[j] - positions[i]
        delta_acceleration = newton_accelerations[j] - newton_accelerations[i]
        return sp.factor(delta.dot(delta_acceleration) / known_distances[(i, j)])

    base_minus_long_leg = sp.factor(
        sp.cancel(distance_second(0, 1) - distance_second(1, 2))
    )
    long_minus_short_leg = sp.factor(
        sp.cancel(distance_second(1, 2) - distance_second(2, 0))
    )
    return base_minus_long_leg, long_minus_short_leg


def side_order_first_numerator() -> sp.Expr:
    u, _, _ = euclid_symbols()
    return (
        u**9
        - 9 * u**8
        + 10 * u**7
        - 10 * u**6
        - 8 * u**5
        - 16 * u**4
        - 2 * u**3
        + 2 * u**2
        - u
        + 1
    )


def side_order_first_bernstein_coefficients() -> tuple[sp.Rational, ...]:
    """Coefficients on [0,5/12] of the numerator controlling r12-r23."""
    u, _, _ = euclid_symbols()
    degree = 9
    upper = sp.Rational(5, 12)
    polynomial = sp.Poly(side_order_first_numerator().subs(u, upper * u), u)
    power_coefficients = [polynomial.nth(index) for index in range(degree + 1)]
    return tuple(
        sp.factor(
            sum(
                power_coefficients[index]
                * sp.binomial(order, index)
                / sp.binomial(degree, index)
                for index in range(order + 1)
            )
        )
        for order in range(degree + 1)
    )


def expected_initial_side_order_second_derivatives() -> tuple[sp.Expr, sp.Expr]:
    u, _, _ = euclid_symbols()
    first = -side_order_first_numerator() / (
        2 * u * (u - 1) ** 2 * (u + 1) * (u**2 + 1) ** 2
    )
    second = -(
        (u**2 + 2 * u - 1)
        * (3 * u**2 - 2 * u + 1)
        * (u**2 * (u - 1) ** 2 + (u + 1) ** 2)
        / (2 * u**2 * (u - 1) ** 2 * (u**2 + 1) ** 2)
    )
    return first, second


def signed_area_second_derivative() -> sp.Expr:
    """Return the second derivative of twice oriented area at the brake."""
    masses, positions = initial_data()
    newton_accelerations = accelerations(masses, positions)
    base = positions[1] - positions[0]
    apex = positions[2] - positions[0]
    base_acceleration = newton_accelerations[1] - newton_accelerations[0]
    apex_acceleration = newton_accelerations[2] - newton_accelerations[0]

    def cross(left: sp.Matrix, right: sp.Matrix) -> sp.Expr:
        return left[0] * right[1] - left[1] * right[0]

    # The mixed 2 R' cross S' term vanishes because all initial velocities do.
    return sp.factor(
        sp.cancel(
            cross(base_acceleration, apex) + cross(base, apex_acceleration)
        )
    )


def signed_area_second_numerator() -> sp.Expr:
    u, _, _ = euclid_symbols()
    return (
        u**10
        - 10 * u**9
        + 19 * u**8
        - 28 * u**7
        - 14 * u**6
        + 8 * u**5
        - 2 * u**4
        - 4 * u**3
        - 3 * u**2
        + 2 * u
        - 1
    )


def expected_signed_area_second_derivative() -> sp.Expr:
    u, _, _ = euclid_symbols()
    denominator = 2 * u**2 * (u - 1) ** 2 * (1 + u**2) ** 3
    return signed_area_second_numerator() / denominator


def signed_area_second_bernstein_coefficients() -> tuple[sp.Rational, ...]:
    """Coefficients of Q_10(t/2) in the degree-10 Bernstein basis."""
    u, _, _ = euclid_symbols()
    return _bernstein_coefficients_on_half_interval(
        signed_area_second_numerator(), 10, u
    )


def expected_identities() -> dict[str, sp.Expr]:
    _, a, b = euclid_symbols()
    p = a * b
    return {
        "I0": sp.factor(p),
        "U0": sp.factor(p + 1 / p),
        "D2": sp.factor(2 * (1 / p - p * (a + b))),
    }


def identity_residuals() -> dict[str, sp.Expr]:
    expected = expected_identities()
    actual = {
        "I0": moment_of_inertia(),
        "U0": potential_magnitude(),
        "D2": pythagorean_defect_second_derivative(),
    }
    return {name: sp.factor(sp.simplify(actual[name] - expected[name])) for name in actual}
