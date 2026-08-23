import sympy as sp

from src.symbolic.restricted_scattering import (
    binary_tidal_transverse_first_variation,
    collision_regularized_jacobi_system,
    incoming_tilt_forcing_identity,
    maximum_softened_vertical_force,
    outer_energy_exchange_identity,
    parabolic_infinity_compactification,
    parabolic_stroboscopic_leading_map,
    parabolic_truncated_energy_drift,
    phase_wronskian_identity,
    restricted_transverse_linearization,
    time_shift_melnikov_identity,
    transverse_rotation_wronskian_identity,
    transverse_variational_normal_form,
    turn_resonance_radial_determinants,
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


def test_turn_resonance_determinant_factorizations() -> None:
    direct, via_turn_phase, via_apocenter_section = (
        turn_resonance_radial_determinants()
    )
    assert sp.simplify(direct - via_turn_phase) == 0
    assert sp.simplify(direct - via_apocenter_section) == 0


def test_restricted_transverse_linearization_contains_rotation_mode() -> None:
    r, z = sp.symbols("r z", real=True)
    outer_coefficient, binary_coefficient = restricted_transverse_linearization()
    distance = sp.sqrt(z**2 + r**2 / 4)
    assert sp.simplify(
        outer_coefficient - (r**2 - 2 * z**2) / distance**5
    ) == 0
    assert sp.simplify(
        binary_coefficient - 3 * r * z / (2 * distance**5)
    ) == 0
    rotated_outer_acceleration = sp.simplify(
        -z * outer_coefficient + r * binary_coefficient
    )
    assert sp.simplify(rotated_outer_acceleration - 2 * z / distance**3) == 0


def test_transverse_rotation_wronskian_has_quadrupole_source() -> None:
    derivative, expected = transverse_rotation_wronskian_identity()
    assert sp.simplify(derivative - expected) == 0


def test_incoming_tilt_has_integrable_quadrupole_source() -> None:
    source, expected = incoming_tilt_forcing_identity()
    assert sp.simplify(source - expected) == 0


def test_binary_tidal_transverse_source_gains_exterior_skinny_factor() -> None:
    coefficient, expected = binary_tidal_transverse_first_variation()
    assert sp.simplify(coefficient - expected) == 0


def test_parabolic_map_preserves_kepler_energy_through_degree_seven() -> None:
    drift, expected = parabolic_truncated_energy_drift()
    assert sp.expand(drift - expected) == 0
