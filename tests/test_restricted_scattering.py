import sympy as sp

from src.symbolic.restricted_scattering import (
    binary_tidal_transverse_first_variation,
    collision_kepler_transverse_transfer,
    collision_regularized_jacobi_system,
    finite_mass_selected_collision_reduction,
    forced_planar_lc_angular_identity,
    forced_planar_light_collision_lc_constraint,
    incoming_parabolic_infinity_compactification,
    incoming_returned_jost_compactification,
    incoming_returned_jost_wronskian_compactification,
    incoming_tilt_forcing_identity,
    maximum_softened_vertical_force,
    outer_energy_exchange_identity,
    parabolic_infinity_compactification,
    parabolic_stroboscopic_leading_map,
    parabolic_truncated_energy_drift,
    phase_wronskian_identity,
    planar_joint_shape_identities,
    planar_joint_shape_quadratic_bending,
    planar_joint_shape_stable_cubic_jet,
    planar_joint_shape_stable_quartic_correction,
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
    tight_binary_brake_hill_threshold,
    time_shift_melnikov_identity,
    transverse_rotation_wronskian_identity,
    transverse_variational_normal_form,
    triple_endpoint_fast_frobenius_corrections,
    triple_endpoint_finite_mass_exponents,
    triple_endpoint_force_monotonicity_identity,
    triple_endpoint_joint_blowup_algebra,
    triple_endpoint_matching_determinant,
    triple_endpoint_mcgehee_shape_exponents,
    triple_endpoint_shifted_fuchsian_identities,
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


def test_incoming_parabolic_infinity_compactification() -> None:
    field, variables = incoming_parabolic_infinity_compactification()
    phase, x, velocity = variables
    separation = sp.cos(phase) ** 2
    z = -2 / x**2
    radius_squared = z**2 + separation**2 / 4
    expected_x = sp.simplify((x**3 / 4) * separation * velocity)
    expected_velocity = sp.simplify(
        -2 * z * separation / radius_squared ** sp.Rational(3, 2)
    )
    assert sp.simplify(field[0] - expected_x) == 0
    assert sp.simplify(field[1] - expected_velocity) == 0


def test_incoming_returned_jost_compactification() -> None:
    field, variables = incoming_returned_jost_compactification()
    phase, x, velocity, normalized_field, normalized_velocity = variables
    separation = sp.cos(phase) ** 2
    z = -2 / x**2
    p = normalized_field / x**2
    p_velocity = x * normalized_velocity
    radius_squared = z**2 + separation**2 / 4
    coefficient = (separation**2 - 2 * z**2) / radius_squared ** sp.Rational(5, 2)
    x_phase = separation * x**3 * velocity / 4
    expected_p_phase = separation * p_velocity
    expected_q_phase = separation * coefficient * p
    derived_p_phase = sp.diff(p, x) * x_phase + sp.diff(p, normalized_field) * field[2]
    derived_q_phase = (
        sp.diff(p_velocity, x) * x_phase
        + sp.diff(p_velocity, normalized_velocity) * field[3]
    )
    assert sp.simplify(derived_p_phase - expected_p_phase) == 0
    assert sp.simplify(derived_q_phase - expected_q_phase) == 0


def test_incoming_returned_jost_wronskian_compactification() -> None:
    field, variables = incoming_returned_jost_wronskian_compactification()
    phase, x, velocity, normalized_field, wronskian = variables
    separation = sp.cos(phase) ** 2
    z = -2 / x**2
    p = normalized_field / x**2
    p_velocity = -(x**2 * wronskian + velocity * normalized_field) / 2
    radius_squared = z**2 + separation**2 / 4
    coefficient = (separation**2 - 2 * z**2) / radius_squared ** sp.Rational(5, 2)
    z_acceleration = -2 * z / radius_squared ** sp.Rational(3, 2)
    expected_wronskian_phase = separation * (
        z * coefficient * p - z_acceleration * p
    )
    assert sp.simplify(z * p_velocity - velocity * p - wronskian) == 0
    assert sp.simplify(field[3] - expected_wronskian_phase) == 0
    assert sp.simplify(field[2] + separation * x**4 * wronskian / 2) == 0


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


def test_triple_endpoint_matching_transverse_block_is_invertible() -> None:
    wronskian, determinant = triple_endpoint_matching_determinant()
    base_determinant = sp.symbols("D_base", nonzero=True, real=True)
    assert wronskian == -sp.sqrt(7)
    assert determinant == -sp.sqrt(7) * base_determinant


def test_triple_endpoint_fast_mode_corrections_cancel_forcing() -> None:
    shape_correction, radius_correction, shape_residual, radius_residual = (
        triple_endpoint_fast_frobenius_corrections()
    )
    amplitude = sp.symbols("a", real=True)
    shape_exponent = (-1 + sp.sqrt(19)) / 4
    spectral_gap = sp.sqrt(7) / 2
    assert sp.simplify(
        shape_correction
        - 3 * sp.sqrt(3) * amplitude /
        (16 * shape_exponent * (shape_exponent + spectral_gap))
    ) == 0
    assert radius_correction == sp.Rational(1, 4)
    assert shape_residual == 0
    assert radius_residual == 0


def test_triple_endpoint_shifted_fuchsian_and_energy_identities() -> None:
    shape_eq, fiber_eq, energy_derivative, exponent_conversion, endpoint_power = (
        triple_endpoint_shifted_fuchsian_identities()
    )
    rho, xi = sp.symbols("rho xi", positive=True)
    radius = rho * sp.exp(-xi)
    y, y_x, y_xx = sp.symbols("y y_x y_xx", real=True)
    p, p_x, p_xx = sp.symbols("p p_x p_xx", real=True)
    defect = y * ((y**2 + sp.Rational(1, 4)) ** sp.Rational(-3, 2) - 1)
    tidal = (1 - 2 * y**2) / (y**2 + sp.Rational(1, 4)) ** sp.Rational(5, 2)
    assert sp.simplify(
        shape_eq - (2 * (1 - radius) * y_xx + (-1 + 2 * radius) * y_x + defect)
    ) == 0
    assert sp.simplify(
        fiber_eq
        - (2 * (1 - radius) * p_xx + (3 - 2 * radius) * p_x - tidal * p / 2)
    ) == 0
    assert sp.simplify(energy_derivative - (1 - radius) * y_x**2) == 0
    assert exponent_conversion == 0
    assert endpoint_power == (1 - sp.sqrt(7)) / 6


def test_triple_endpoint_force_is_monotone_in_certified_cone() -> None:
    derivative, residual = triple_endpoint_force_monotonicity_identity()
    height, radius = sp.symbols("Z r", positive=True)
    expected = (4 * height**2 - radius**2 / 2) / (
        height**2 + radius**2 / 4
    ) ** sp.Rational(5, 2)
    assert sp.simplify(derivative - expected) == 0
    assert residual == 0


def test_triple_endpoint_finite_mass_wedge_exponents() -> None:
    shape_power, transverse_power, shape_residual, transverse_residual = (
        triple_endpoint_finite_mass_exponents()
    )
    assert shape_residual == 0
    assert transverse_residual == 0
    assert float(shape_power) > float(transverse_power) > 0


def test_triple_endpoint_mcgehee_shape_exponents() -> None:
    radial_speed, long_stable, long_unstable, trans_unstable, trans_stable, ratio = (
        triple_endpoint_mcgehee_shape_exponents()
    )
    assert radial_speed < 0
    assert long_stable < 0 < long_unstable
    assert trans_stable < 0 < trans_unstable
    assert sp.simplify(ratio - (1 + sp.sqrt(7)) / 6) == 0


def test_triple_endpoint_joint_blowup_algebra() -> None:
    longitudinal, transverse, ratio, lower_gap, upper_gap, odd_offset = (
        triple_endpoint_joint_blowup_algebra()
    )
    skinny = sp.symbols("B", positive=True)
    heavy = sp.sqrt(1 - skinny**2)
    assert sp.simplify(longitudinal - (1 + sp.sqrt(19)) / 4) == 0
    assert sp.simplify(transverse - (1 + sp.sqrt(7)) / 4) == 0
    assert sp.simplify(ratio - longitudinal / transverse) == 0
    assert float(lower_gap) > 0
    assert float(upper_gap) > 0
    assert sp.simplify(odd_offset + skinny**2 / (2 * (1 + heavy) ** 2)) == 0


def test_planar_joint_shape_identities() -> None:
    (
        rest_gradient,
        rest_hessian,
        rest_potential,
        energy_dot,
        torque_gap,
        delta,
        distance_bound_gap,
    ) = planar_joint_shape_identities()
    horizontal_velocity, vertical_velocity = sp.symbols("x_dot y_dot", real=True)
    assert rest_gradient == sp.zeros(2, 1)
    assert rest_hessian == sp.diag(sp.Rational(1, 6), sp.Rational(1, 2))
    assert rest_potential == sp.Rational(11, 36)
    assert sp.simplify(
        energy_dot + (horizontal_velocity**2 + vertical_velocity**2) / 3
    ) == 0
    assert torque_gap == 0
    assert float(delta) > 0
    assert distance_bound_gap == 0


def test_planar_joint_shape_quadratic_bending() -> None:
    source, divisor, bending, rate_gap = planar_joint_shape_quadratic_bending()
    assert source == sp.sqrt(3) / 24
    assert sp.simplify(divisor - (sp.Rational(5, 18) + sp.sqrt(7) / 9)) == 0
    assert sp.simplify(bending - (2 * sp.sqrt(21) - 5 * sp.sqrt(3)) / 4) == 0
    assert float(bending) > 0
    assert float(rate_gap) > 0


def test_planar_joint_shape_stable_cubic_jet() -> None:
    coefficients, residuals = planar_joint_shape_stable_cubic_jet()
    mixed, bending, long_quadratic, trans_cubic, mixed_squared, squared_mixed, long_cubic = (
        coefficients
    )
    assert sp.simplify(bending - (2 * sp.sqrt(21) - 5 * sp.sqrt(3)) / 4) == 0
    assert float(mixed) > 0
    assert float(long_quadratic) > 0
    assert float(trans_cubic) < 0
    assert float(mixed_squared) > 0
    assert float(squared_mixed) > 0
    assert float(long_cubic) > 0
    assert residuals == (0, 0)


def test_planar_joint_shape_stable_quartic_correction() -> None:
    coefficients, residuals, fifth_defect = planar_joint_shape_stable_quartic_correction()
    trans_cubic_long, trans_long_cubic, trans_quartic, mixed_quartic, long_quartic = (
        coefficients
    )
    assert float(trans_cubic_long) < 0
    assert float(trans_long_cubic) > 0
    assert float(trans_quartic) < 0
    assert float(mixed_quartic) > 0
    assert float(long_quartic) < 0
    assert residuals == (0, 0)
    transverse, longitudinal = sp.symbols("p h", real=True)
    horizontal_defect, vertical_defect = fifth_defect
    assert horizontal_defect != 0
    assert vertical_defect != 0
    assert sp.Poly(horizontal_defect, transverse, longitudinal).total_degree() == 5
    assert sp.Poly(vertical_defect, transverse, longitudinal).total_degree() == 5

    cubic_coefficients, _ = planar_joint_shape_stable_cubic_jet()
    coefficient_bounds = (
        sp.Rational(1, 10),
        sp.Rational(13, 100),
        sp.Rational(11, 100),
        sp.Rational(1, 10),
        sp.Rational(1, 5),
        sp.Rational(29, 100),
        sp.Rational(3, 250),
        sp.Rational(1, 4),
        sp.Rational(1, 4),
        sp.Rational(2, 25),
        sp.Rational(47, 100),
        sp.Rational(11, 500),
    )
    for coefficient, bound in zip(
        cubic_coefficients + coefficients, coefficient_bounds, strict=True
    ):
        assert sp.ask(sp.Q.positive(bound - coefficient)) is True
        assert sp.ask(sp.Q.positive(bound + coefficient)) is True

    dilated_transverse = sp.Rational(2, 5)
    dilated_longitudinal = sp.Rational(4, 125)
    a, k, d, b, c, e, f, g, h, i, j, ell = coefficient_bounds
    def coordinate_majorants(
        transverse_radius: sp.Rational, longitudinal_radius: sp.Rational
    ) -> tuple[sp.Expr, sp.Expr]:
        horizontal = (
            transverse_radius
            + a * transverse_radius * longitudinal_radius
            + b * transverse_radius**3
            + c * transverse_radius * longitudinal_radius**2
            + g * transverse_radius**3 * longitudinal_radius
            + h * transverse_radius * longitudinal_radius**3
        )
        vertical = (
            longitudinal_radius
            + k * transverse_radius**2
            + d * longitudinal_radius**2
            + e * transverse_radius**2 * longitudinal_radius
            + f * longitudinal_radius**3
            + i * transverse_radius**4
            + j * transverse_radius**2 * longitudinal_radius**2
            + ell * longitudinal_radius**4
        )
        return horizontal, vertical

    dilated_horizontal, dilated_vertical = coordinate_majorants(
        dilated_transverse, dilated_longitudinal
    )
    assert dilated_horizontal < sp.Rational(41, 100)
    assert dilated_vertical < sp.Rational(3, 50)
    assert (
        sp.Rational(41, 100) ** 2
        + sp.Rational(3, 50) ** 2
        + sp.Rational(41, 100)
        + 2 * sp.Rational(3, 50)
        < sp.Rational(3, 4)
    )

    base_transverse = sp.Rational(1, 200)
    base_longitudinal = sp.Rational(1, 2500)
    base_horizontal, base_vertical = coordinate_majorants(
        base_transverse, base_longitudinal
    )
    majorant_radius = sp.Rational(271, 50000)
    assert base_horizontal + base_vertical < majorant_radius
    assert majorant_radius**2 + 2 * majorant_radius < sp.Rational(1, 80)
    assert sp.Rational(9, 16) * sp.Rational(80, 79) ** 5 < 1
    assert sp.Rational(225, 256) * sp.Rational(80, 79) ** 7 < 1

    homological_lower = sp.Rational(17, 30)
    exact_homological_gap = (5 + 2 * sp.sqrt(7)) / 18
    assert sp.ask(sp.Q.positive(exact_homological_gap - homological_lower)) is True
    contraction_upper = sp.Rational(30, 17) * 9 * majorant_radius
    assert contraction_upper < sp.Rational(1, 10)
    residual_upper = sp.Rational(13, 80**5)
    correction_upper = (
        sp.Rational(30, 17) * sp.Rational(10, 9) * residual_upper
    )
    assert correction_upper < sp.Rational(1, 125_000_000)

    exp_six_lower = sum(sp.Rational(6) ** n / sp.factorial(n) for n in range(14))
    exp_long_lower = sum(
        sp.Rational(80, 9) ** n / sp.factorial(n) for n in range(14)
    )
    assert exp_six_lower > 400
    assert exp_long_lower > 6500


def test_forced_planar_light_collision_lc_constraint() -> None:
    field, constraint_derivative, collision_speed_gap, collision_clock_cubic_gap = (
        forced_planar_light_collision_lc_constraint()
    )
    u_real, u_imag = sp.symbols("u_r u_i", real=True)
    assert constraint_derivative == 0
    assert collision_speed_gap == 0
    assert collision_clock_cubic_gap == 0
    assert sp.simplify(field[5] - (u_real**2 + u_imag**2)) == 0
    assert sp.simplify(field.subs({u_real: 0, u_imag: 0})[2]) == 0
    assert sp.simplify(field.subs({u_real: 0, u_imag: 0})[3]) == 0


def test_finite_mass_selected_collision_reduction() -> None:
    (
        equation_residual,
        pair_center_residual,
        constraint_derivative,
        collision_speed_gap,
    ) = finite_mass_selected_collision_reduction()
    assert equation_residual == sp.zeros(2, 1)
    assert pair_center_residual == sp.zeros(2, 1)
    assert constraint_derivative == 0
    assert collision_speed_gap == 0


def test_forced_planar_lc_angular_identity() -> None:
    angular_gap, collision_derivative_gap = forced_planar_lc_angular_identity()
    assert angular_gap == 0
    assert collision_derivative_gap == 0


def test_tight_binary_brake_hill_threshold() -> None:
    threshold, residual, gap = tight_binary_brake_hill_threshold()
    skinny = sp.symbols("B", positive=True)
    assert residual == 0
    assert sp.simplify(
        threshold - (1 - skinny**2) / (1 + skinny**2 - skinny**4)
    ) == 0
    assert sp.simplify(gap - skinny**2 * (2 - skinny**2) / (1 + skinny**2 - skinny**4)) == 0


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
