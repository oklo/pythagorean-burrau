import sympy as sp

from src.symbolic.restricted_scattering import (
    collision_regularized_jacobi_system,
    maximum_softened_vertical_force,
    outer_energy_exchange_identity,
    parabolic_infinity_compactification,
    parabolic_stroboscopic_leading_map,
    phase_wronskian_identity,
    time_shift_melnikov_identity,
    transverse_variational_normal_form,
)


def test_outer_energy_exchange_is_binary_expansion_work() -> None:
    derived, expected = outer_energy_exchange_identity()
    assert sp.simplify(derived - expected) == 0


def test_small_speed_normal_form_has_sturm_coefficient() -> None:
    phase = sp.symbols("phase", real=True)
    assert sp.trigsimp(
        transverse_variational_normal_form() - (1 + 14 * sp.sec(phase) ** 2)
    ) == 0


def test_naive_phase_melnikov_is_a_boundary_term() -> None:
    integrand, derivative = time_shift_melnikov_identity()
    assert sp.simplify(integrand - derivative) == 0


def test_phase_wronskian_and_force_maximum() -> None:
    derivative, expected = phase_wronskian_identity()
    assert sp.simplify(derivative - expected) == 0
    height, force = maximum_softened_vertical_force()
    separation = sp.symbols("separation", positive=True)
    assert height == separation / (2 * sp.sqrt(2))
    assert force == 16 / (3 * sp.sqrt(3) * separation**2)


def test_collision_regularized_jacobi_system() -> None:
    system, variables = collision_regularized_jacobi_system()
    phase, z, velocity, jacobi, jacobi_velocity = variables
    separation = sp.cos(phase) ** 2
    radius_squared = z**2 + separation**2 / 4
    coefficient = (4 * z**2 - separation**2 / 2) / radius_squared ** sp.Rational(5, 2)
    expected = sp.Matrix(
        [
            separation * velocity,
            -2 * z * separation / radius_squared ** sp.Rational(3, 2),
            separation * jacobi_velocity,
            separation * coefficient * jacobi,
        ]
    )
    assert all(sp.simplify(entry) == 0 for entry in system - expected)


def test_parabolic_infinity_compactification_and_period_map() -> None:
    field, variables = parabolic_infinity_compactification()
    phase, x, velocity = variables
    separation = sp.cos(phase) ** 2
    z = 2 / x**2
    radius_squared = z**2 + separation**2 / 4
    expected_x = sp.simplify((-x**3 / 4) * separation * velocity)
    expected_velocity = sp.simplify(
        -2 * z * separation / radius_squared ** sp.Rational(3, 2)
    )
    assert sp.simplify(field[0] - expected_x) == 0
    assert sp.simplify(field[1] - expected_velocity) == 0

    original, transformed = parabolic_stroboscopic_leading_map()
    transverse = sp.symbols("transverse", real=True)
    assert original == sp.Matrix([-sp.pi * x**3 * velocity / 8, -sp.pi * x**4 / 4])
    expected_transformed = sp.Matrix(
        [
            -sp.pi * x**3 * (transverse + sp.sqrt(2) * x) / 8,
            sp.sqrt(2) * sp.pi * x**3 * transverse / 8,
        ]
    )
    assert all(sp.simplify(entry) == 0 for entry in transformed - expected_transformed)
