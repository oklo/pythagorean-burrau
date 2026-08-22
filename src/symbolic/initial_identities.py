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
