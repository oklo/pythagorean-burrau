"""Computer-algebra checks for the initial Pythagorean--Burrau identities."""

from __future__ import annotations

import sympy as sp


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


def expected_defect_fourth_derivative() -> sp.Expr:
    u, _, _ = euclid_symbols()
    denominator = u**4 * (u - 1) ** 4 * (u + 1) ** 2 * (1 + u**2) ** 4
    return defect_fourth_numerator() / denominator


def tight_pair_initial_specific_torque() -> sp.Expr:
    """Derive the initial tight-pair specific torque from Newton acceleration."""
    masses, positions = initial_data()
    newton_accelerations = accelerations(masses, positions)
    tight_vector = positions[2] - positions[0]
    tight_acceleration = newton_accelerations[2] - newton_accelerations[0]
    cross = tight_vector[0] * tight_acceleration[1] - tight_vector[1] * tight_acceleration[0]
    return sp.factor(sp.simplify(cross))


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
