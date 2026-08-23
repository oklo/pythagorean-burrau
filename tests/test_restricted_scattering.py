import sympy as sp

from src.symbolic.restricted_scattering import (
    binary_tidal_transverse_first_variation,
    collision_kepler_transverse_transfer,
    collision_regularized_jacobi_system,
    incoming_tilt_forcing_identity,
    maximum_softened_vertical_force,
    outer_energy_exchange_identity,
    parabolic_infinity_compactification,
    parabolic_stroboscopic_leading_map,
    parabolic_truncated_energy_drift,
    phase_wronskian_identity,
    restricted_equilateral_triple_collision,
    restricted_terminal_collision_r_chart,
    restricted_transverse_linearization,
    restricted_triple_collision_phase_mode,
    restricted_triple_collision_shape_energy,
    restricted_triple_collision_shape_spectrum,
    restricted_triple_collision_slow_field_barrier,
    restricted_universal_binary_lc_system,
    restricted_universal_binary_mu_system,
    second_encounter_endpoint_scattering,
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
    assert sp.trigsimp(transverse_variational_normal_form() - (1 + 14 * sp.sec(phase) ** 2)) == 0


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
    expected_x = sp.simplify((-(x**3) / 4) * separation * velocity)
    expected_velocity = sp.simplify(-2 * z * separation / radius_squared ** sp.Rational(3, 2))
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
    direct, via_turn_phase, via_apocenter_section = turn_resonance_radial_determinants()
    assert sp.simplify(direct - via_turn_phase) == 0
    assert sp.simplify(direct - via_apocenter_section) == 0


def test_restricted_transverse_linearization_contains_rotation_mode() -> None:
    r, z = sp.symbols("r z", real=True)
    outer_coefficient, binary_coefficient = restricted_transverse_linearization()
    distance = sp.sqrt(z**2 + r**2 / 4)
    assert sp.simplify(outer_coefficient - (r**2 - 2 * z**2) / distance**5) == 0
    assert sp.simplify(binary_coefficient - 3 * r * z / (2 * distance**5)) == 0
    rotated_outer_acceleration = sp.simplify(-z * outer_coefficient + r * binary_coefficient)
    assert sp.simplify(rotated_outer_acceleration - 2 * z / distance**3) == 0


def test_transverse_rotation_wronskian_has_quadrupole_source() -> None:
    derivative, expected = transverse_rotation_wronskian_identity()
    assert sp.simplify(derivative - expected) == 0


def test_second_encounter_parabolic_endpoint_wronskian() -> None:
    connection, determinant, outgoing, endpoint_wronskian = second_encounter_endpoint_scattering()
    gamma, scattering_wronskian = sp.symbols("gamma W", real=True, nonzero=True)
    assert determinant == 1
    assert outgoing == sp.Matrix([1 - 2 * gamma**2, 2 * gamma * scattering_wronskian])
    assert endpoint_wronskian == -2 * gamma * scattering_wronskian
    assert sp.simplify(connection.det() - 1) == 0


def test_restricted_equilateral_triple_collision_indicial_exponents() -> None:
    binary_residual, outer_residual, coefficient, exponents = (
        restricted_equilateral_triple_collision()
    )
    assert binary_residual == 0
    assert outer_residual == 0
    assert coefficient == -sp.Rational(1, 18)
    for exponent in exponents:
        assert sp.simplify(exponent * (exponent - 1) + sp.Rational(1, 18)) == 0


def test_restricted_triple_collision_relative_phase_mode() -> None:
    coefficient, forcing, residual = restricted_triple_collision_phase_mode()
    collision_time = next(iter(forcing.free_symbols))
    assert coefficient == sp.Rational(5, 18)
    assert sp.simplify(
        forcing + 3 ** sp.Rational(1, 6) / (6 * collision_time ** sp.Rational(7, 3))
    ) == 0
    assert residual == 0


def test_restricted_triple_collision_shape_spectrum() -> None:
    fixed_residual, linear_coefficient, eigenvalues = (
        restricted_triple_collision_shape_spectrum()
    )
    assert fixed_residual == 0
    assert linear_coefficient == -sp.Rational(1, 2)
    for eigenvalue in eigenvalues:
        assert sp.simplify(
            eigenvalue**2 - eigenvalue / 3 - sp.Rational(1, 2)
        ) == 0


def test_restricted_triple_collision_shape_energy_increases() -> None:
    derivative, expected, equilateral_value, center_value = (
        restricted_triple_collision_shape_energy()
    )
    assert sp.simplify(derivative - expected) == 0
    assert equilateral_value == -sp.Rational(11, 36)
    assert center_value == -sp.Rational(4, 9)
    assert equilateral_value - center_value == sp.Rational(5, 36)


def test_restricted_triple_collision_slow_field_barrier_constants() -> None:
    equilibrium, tangent, initial_gap, margin, center_lower = (
        restricted_triple_collision_slow_field_barrier()
    )
    assert equilibrium == -sp.Rational(1, 18)
    assert tangent == 1 / (4 * sp.sqrt(3))
    assert initial_gap > 0
    assert margin > 0
    assert center_lower > 0


def test_restricted_terminal_collision_r_chart_exponents() -> None:
    (
        shape_equation,
        transverse_equation,
        shape_residual,
        shape_linear,
        shape_exponents,
        transverse,
        exponents,
    ) = restricted_terminal_collision_r_chart()
    radius = sp.symbols("r", positive=True, real=True)
    shape = sp.symbols("y", real=True)
    shape_first, shape_second = sp.symbols("y_r y_rr", real=True)
    field, field_first, field_second = sp.symbols("p p_r p_rr", real=True)
    raw_coefficient = (1 - 2 * shape**2) / (
        shape**2 + sp.Rational(1, 4)
    ) ** sp.Rational(5, 2)
    expected_shape = (
        2 * radius**2 * (1 - radius) * shape_second
        + radius * (3 - 4 * radius) * shape_first
        + shape
        * ((shape**2 + sp.Rational(1, 4)) ** (-sp.Rational(3, 2)) - 1)
    )
    expected_transverse = (
        2 * radius**2 * (1 - radius) * field_second
        - radius * field_first
        - raw_coefficient * field / 2
    )
    assert sp.simplify(shape_equation - expected_shape) == 0
    assert sp.simplify(transverse_equation - expected_transverse) == 0
    assert shape_residual == 0
    assert shape_linear == -sp.Rational(9, 4)
    assert shape_exponents == (
        (-1 - sp.sqrt(19)) / 4,
        (-1 + sp.sqrt(19)) / 4,
    )
    assert transverse == -sp.Rational(1, 2)
    assert exponents == (
        (3 - sp.sqrt(7)) / 4,
        (3 + sp.sqrt(7)) / 4,
    )


def test_restricted_universal_binary_collision_is_lc_regular() -> None:
    field, variables = restricted_universal_binary_lc_system()
    lc, height, velocity, transverse, transverse_velocity = variables
    assert field.subs(lc, 0) == sp.zeros(4, 1)
    assert sp.simplify(field[0] + 3 * lc**2 * velocity) == 0
    assert sp.simplify(field[2] + 3 * lc**2 * transverse_velocity) == 0
    for entry in field:
        assert not entry.has(sp.Abs)
    assert height in field.free_symbols
    assert transverse in field.free_symbols


def test_restricted_universal_binary_mu_system_matches_verifier() -> None:
    field, variables = restricted_universal_binary_mu_system()
    lc, height, velocity, transverse, transverse_velocity = variables
    radius_squared = height**2 + lc**4 / 4
    expected = sp.Matrix(
        [
            -1,
            3 * lc**2 * velocity,
            -sp.Rational(2, 3)
            * lc**2
            * height
            / radius_squared ** sp.Rational(3, 2),
            3 * lc**2 * transverse_velocity,
            sp.Rational(1, 3)
            * lc**2
            * (lc**4 - 2 * height**2)
            * transverse
            / radius_squared ** sp.Rational(5, 2),
        ]
    )
    assert all(sp.simplify(component) == 0 for component in field - expected)


def test_incoming_tilt_has_integrable_quadrupole_source() -> None:
    source, expected = incoming_tilt_forcing_identity()
    assert sp.simplify(source - expected) == 0


def test_binary_tidal_transverse_source_gains_exterior_skinny_factor() -> None:
    coefficient, expected = binary_tidal_transverse_first_variation()
    assert sp.simplify(coefficient - expected) == 0


def test_parabolic_map_preserves_kepler_energy_through_degree_seven() -> None:
    drift, expected = parabolic_truncated_energy_drift()
    assert sp.expand(drift - expected) == 0


def test_collision_kepler_mode_transfers_to_nonzero_turn_velocity() -> None:
    residual, collision_normalization, turn_velocity = collision_kepler_transverse_transfer()
    (turn_radius,) = tuple(turn_velocity.free_symbols)
    assert sp.simplify(residual) == 0
    assert collision_normalization == 1
    assert sp.simplify(turn_velocity + 1 / turn_radius) == 0
