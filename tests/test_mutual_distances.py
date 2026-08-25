import numpy as np
import pytest
import sympy as sp

from src.dynamics.cartesian import right_hand_side
from src.symbolic.mutual_distances import (
    _generic_ordered_syzygy_first_gap_energy_margin,
    _generic_ordered_syzygy_torque_thresholds,
    _radial_gravity_gaps,
    first_gap_static_energy_obstruction,
    initial_log_torque_threshold_gap,
    log_torque_shape_rate_identity,
    log_torque_shape_threshold,
    log_torque_threshold_contact_terms,
    ordered_history_centrifugal_reduction,
    ordered_history_shape_time_rhs,
    ordered_obtuse_gravity_first_bernstein_coefficients,
    ordered_obtuse_gravity_first_gap,
    ordered_obtuse_log_torque_ratio_gravity_bernstein_coefficients,
    ordered_obtuse_log_torque_ratio_gravity_curvature,
    ordered_shape_gravity_bernstein_coefficients,
    ordered_shape_gravity_gap,
    ordered_shape_log_torque_kernel,
    ordered_shape_log_torque_kernel_bernstein_coefficients,
    ordered_shape_log_torque_threshold_gap_bernstein_coefficients,
    ordered_shape_log_torque_threshold_gap_core,
    ordered_syzygy_first_gap_energy_bernstein_coefficients,
    ordered_syzygy_first_gap_energy_numerator,
    ordered_syzygy_longitudinal_kinetic_decomposition,
    ordered_syzygy_second_gap_static_obstruction,
    ordered_syzygy_small_longitudinal_sign_witness,
    ordered_syzygy_torque_amplitude_bernstein_coefficients,
    ordered_syzygy_torque_amplitude_sign_cores,
    ordered_syzygy_torque_energy_threshold,
    pair_torque_kinetic_coefficient,
    second_gap_barrier_outward_contact_obstruction,
    squared_distance_accelerations,
    torque_history_ratio_identity,
    torque_rate_first_return_static_obstruction,
)


def test_squared_distance_equations_at_345_launch() -> None:
    expressions = squared_distance_accelerations()
    m1, m2, m3 = sp.symbols("m1 m2 m3", positive=True)
    x, y, z = sp.symbols("x y z", positive=True)
    v23, v31, v12 = sp.symbols("v23sq v31sq v12sq", nonnegative=True)
    a, b = sp.Rational(4, 5), sp.Rational(3, 5)
    substitution = {
        m1: a,
        m2: b,
        m3: 1,
        x: a**2,
        y: b**2,
        z: 1,
        v23: 0,
        v31: 0,
        v12: 0,
    }
    assert sp.simplify(expressions["x_second"].subs(substitution) + 2 * (b + 1) / a + 2 * a**3) == 0
    assert sp.simplify(expressions["y_second"].subs(substitution) + 2 * (a + 1) / b + 2 * b**3) == 0
    assert sp.simplify(
        expressions["z_second"].subs(substitution)
        + 2 * (a + b + 1 / a + 1 / b)
    ) == 0


def test_torque_history_ratio_scalar_ode() -> None:
    assert torque_history_ratio_identity() == 0


def test_log_torque_rate_has_an_exact_algebraic_history_threshold() -> None:
    assert log_torque_shape_rate_identity() == 0
    coefficient, threshold, variables = log_torque_shape_threshold()
    m, n, x, y = variables
    witness = torque_rate_first_return_static_obstruction()
    witness_values = {
        m: sp.Rational(21, 29),
        n: sp.Rational(20, 29),
        x: sp.Rational(39, 40),
        y: sp.Rational(1, 30),
    }
    witness_eta = sp.factor(
        (witness_values[m] / witness_values[n])
        * (-witness["ell_31"] / witness["ell_23"])
    )
    assert sp.factor(threshold.subs(witness_values) - witness_eta) == 0
    assert sp.sign(coefficient.subs(witness_values)) == 1

    kernel, cube_variables = ordered_shape_log_torque_kernel()
    numerator, denominator = sp.fraction(kernel)
    polynomial = sp.Poly(numerator, *cube_variables)
    assert tuple(
        polynomial.degree(variable) for variable in cube_variables
    ) == (7, 6, 2)
    coefficients = ordered_shape_log_torque_kernel_bernstein_coefficients()
    signs = tuple(sp.sign(value) for value in coefficients)
    assert len(coefficients) == 168
    assert signs.count(-1) == 134
    assert signs.count(0) == 34
    assert set(signs) == {-1, 0}
    _, _, parameter = cube_variables
    expected_denominator = 16 * (
        -1 - (3 - 2 * sp.sqrt(2)) * parameter**2
    )
    assert sp.factor(denominator - expected_denominator) == 0

    initial_gap, tied_parameter = initial_log_torque_threshold_gap()
    expected_gap = (
        8
        * tied_parameter
        * (1 + tied_parameter**2) ** 3
        * (tied_parameter**2 + 2 * tied_parameter - 1)
        * (
            2 * tied_parameter**4
            - 3 * tied_parameter**3
            + 3 * tied_parameter**2
            + tied_parameter
            + 1
        )
        / (
            (tied_parameter - 1) ** 5
            * (tied_parameter + 1) ** 4
            * (
                tied_parameter**3
                - tied_parameter**2
                + 3 * tied_parameter
                + 1
            )
            * (
                tied_parameter**4
                + 2 * tied_parameter**3
                + 6 * tied_parameter**2
                + 2 * tied_parameter
                + 1
            )
        )
    )
    assert sp.factor(initial_gap - expected_gap) == 0
    assert sp.sign(initial_gap.subs(tied_parameter, sp.Rational(1, 3))) == 1

    gap_core, gap_variables = ordered_shape_log_torque_threshold_gap_core()
    gap_numerator, gap_denominator = sp.fraction(gap_core)
    gap_polynomial = sp.Poly(gap_numerator, *gap_variables)
    assert tuple(
        gap_polynomial.degree(variable) for variable in gap_variables
    ) == (11, 11, 2)
    gap_coefficients = (
        ordered_shape_log_torque_threshold_gap_bernstein_coefficients()
    )
    gap_signs = tuple(sp.sign(value) for value in gap_coefficients)
    assert len(gap_coefficients) == 432
    assert gap_signs.count(-1) == 317
    assert gap_signs.count(0) == 115
    assert set(gap_signs) == {-1, 0}
    _, _, gap_parameter = gap_variables
    expected_gap_denominator = 512 * (
        -1 - (3 - 2 * sp.sqrt(2)) * gap_parameter**2
    )
    assert sp.factor(gap_denominator - expected_gap_denominator) == 0

    history_source, shape_source, contact_threshold, contact_variables = (
        log_torque_threshold_contact_terms()
    )
    cm, cn, cx, cy = contact_variables
    contact_values = {
        cm: sp.Rational(21, 29),
        cn: sp.Rational(20, 29),
        cx: sp.Rational(39, 40),
        cy: sp.Rational(1, 30),
    }
    assert sp.factor(
        contact_threshold.subs(contact_values) - witness_eta
    ) == 0
    contact_history = sp.factor(history_source.subs(contact_values))
    contact_shape = sp.factor(shape_source.subs(contact_values))
    assert sp.sign(contact_history) == -1
    assert sp.sign(contact_shape) == -1
    critical_amplitude = sp.factor(contact_history / contact_shape)
    witness_parameter = sp.Rational(2, 5)
    witness_mass_1 = (1 - witness_parameter**2) / (
        1 + witness_parameter**2
    )
    witness_mass_2 = 2 * witness_parameter / (
        1 + witness_parameter**2
    )
    witness_potential = (
        witness_mass_1 * witness_mass_2
        + witness_mass_2 / witness_values[x]
        + witness_mass_1 / witness_values[y]
    )
    witness_initial_potential = (
        witness_mass_1 * witness_mass_2
        + 1 / (witness_mass_1 * witness_mass_2)
    )
    witness_scale = sp.Rational(1, 2)
    witness_velocity_amplitude_squared = sp.factor(
        (
            witness_potential
            - witness_scale * witness_initial_potential
        )
        / witness["kinetic"]
    )
    witness_z = sp.factor(
        witness["ell_23"] ** 2 * witness_velocity_amplitude_squared
    )
    assert sp.sign(critical_amplitude) == 1
    assert sp.sign(witness_z - critical_amplitude) == 1
    assert float(witness_z / critical_amplitude) == pytest.approx(
        1.05745644351720, rel=2e-14
    )
    positive_s_parameter = sp.Rational(1, 100)
    positive_s_values = {
        cm: (1 - positive_s_parameter**2)
        / (1 + positive_s_parameter**2),
        cn: 2 * positive_s_parameter
        / (1 + positive_s_parameter**2),
        cx: sp.Rational(199, 200),
        cy: sp.Rational(3, 200),
    }
    positive_s_threshold = sp.factor(
        contact_threshold.subs(positive_s_values)
    )
    assert 0 < positive_s_threshold < 1
    assert sp.sign(shape_source.subs(positive_s_values)) == 1


def test_ordered_history_reduces_both_centrifugal_gaps_to_two_scalars() -> None:
    gaps, variables = ordered_history_centrifugal_reduction()
    m, n, x, y, z_value, eta = variables
    first_gap, second_gap = gaps
    assert sp.factor(
        first_gap
        - z_value * ((1 - eta) ** 2 / m**2 - x**-3)
    ) == 0
    assert sp.factor(
        second_gap
        - z_value * (x**-3 - n**2 * eta**2 / (m**2 * y**3))
    ) == 0

    rhs, rhs_variables = ordered_history_shape_time_rhs()
    m_rhs, y_rhs, delta, sigma, amplitude, eta_rhs, current = rhs_variables
    amplitude_rhs, eta_derivative = rhs
    source = m_rhs * delta * (y_rhs**-3 - 1)
    assert sp.factor(amplitude_rhs - source + sigma * amplitude / 2) == 0
    assert sp.factor(
        eta_derivative - source * (current - eta_rhs) / amplitude
    ) == 0


def test_torque_contact_and_second_gap_thresholds_have_no_global_order() -> None:
    history_source, shape_source, threshold, variables = (
        log_torque_threshold_contact_terms()
    )
    m, n, x, y = variables
    _, gravity_second, gravity_variables = _radial_gravity_gaps()
    gx, gy, gscale, gu = gravity_variables
    examples = (
        (
            sp.Rational(1, 3),
            sp.Rational(3, 5),
            sp.Rational(41, 100),
            -1,
        ),
        (
            sp.Rational(1, 10),
            sp.Rational(19, 20),
            sp.Rational(1, 10),
            1,
        ),
    )
    for parameter, side_23, side_31, expected_order in examples:
        mass_1 = (1 - parameter**2) / (1 + parameter**2)
        mass_2 = 2 * parameter / (1 + parameter**2)
        values = {m: mass_1, n: mass_2, x: side_23, y: side_31}
        contact_eta = sp.factor(threshold.subs(values))
        assert 0 < contact_eta < 1
        contact_p = sp.factor(history_source.subs(values))
        contact_s = sp.factor(shape_source.subs(values))
        assert sp.sign(contact_p) == -1
        assert sp.sign(contact_s) == -1
        torque_threshold = sp.factor(contact_p / contact_s)
        gravity_gap = sp.factor(
            gravity_second.subs(
                {
                    gx: side_23,
                    gy: side_31,
                    gscale: 1,
                    gu: parameter,
                }
            )
        )
        second_coefficient = sp.factor(
            side_23**-3
            - mass_2**2
            * contact_eta**2
            / (mass_1**2 * side_31**3)
        )
        assert sp.sign(gravity_gap) == 1
        assert sp.sign(second_coefficient) == -1
        second_threshold = sp.factor(gravity_gap / (-second_coefficient))
        assert sp.sign(torque_threshold - second_threshold) == expected_order


def test_gravity_widens_second_gap_on_ordered_shape_cube() -> None:
    gap, variables = ordered_shape_gravity_gap()
    numerator, denominator = sp.fraction(gap)
    polynomial = sp.Poly(numerator, *variables)
    assert tuple(polynomial.degree(variable) for variable in variables) == (7, 6, 2)
    coefficients = ordered_shape_gravity_bernstein_coefficients()
    signs = tuple(sp.sign(coefficient) for coefficient in coefficients)
    assert len(coefficients) == 168
    assert signs.count(0) == 31
    assert signs.count(1) == 137
    assert set(signs) == {0, 1}

    t, w, v = variables
    expected_denominator = (
        (t * w - 2) ** 3
        * (-3 * v**2 + 2 * sp.sqrt(2) * v**2 - 1)
        * (t * w - 2 * t + 2) ** 3
    )
    assert sp.factor(denominator - expected_denominator) == 0


def test_gravity_compresses_first_gap_on_ordered_obtuse_rectangle() -> None:
    gap, variables = ordered_obtuse_gravity_first_gap()
    numerator, denominator = sp.fraction(gap)
    polynomial = sp.Poly(numerator, *variables)
    assert tuple(polynomial.degree(variable) for variable in variables) == (7, 6, 2)
    coefficients = ordered_obtuse_gravity_first_bernstein_coefficients()
    signs = tuple(sp.sign(coefficient) for coefficient in coefficients)
    assert len(coefficients) == 168
    assert signs.count(0) == 18
    assert signs.count(-1) == 150
    assert set(signs) == {-1, 0}

    s_value, w, v = variables
    first_denominator = -3 * v**2 + 2 * sp.sqrt(2) * v**2 - 1
    second_denominator = (
        -s_value * w
        + sp.sqrt(2) * s_value * w
        - sp.sqrt(2) * w
        + 2 * w
        - 2
    ) ** 3
    third_denominator = (
        -s_value * w
        + sp.sqrt(2) * s_value * w
        - 2 * sp.sqrt(2) * s_value
        + 2 * s_value
        - sp.sqrt(2) * w
        + 2 * w
        - 2
        + 2 * sp.sqrt(2)
    ) ** 3
    assert sp.factor(
        denominator
        - first_denominator * second_denominator * third_denominator
    ) == 0


def test_gravity_strictly_decreases_log_torque_rate_ratio() -> None:
    curvature, variables = ordered_obtuse_log_torque_ratio_gravity_curvature()
    numerator, denominator = sp.fraction(curvature)
    polynomial = sp.Poly(numerator, *variables)
    assert tuple(polynomial.degree(variable) for variable in variables) == (9, 9, 2)
    coefficients = (
        ordered_obtuse_log_torque_ratio_gravity_bernstein_coefficients()
    )
    signs = tuple(sp.sign(coefficient) for coefficient in coefficients)
    assert len(coefficients) == 300
    assert signs.count(0) == 32
    assert signs.count(1) == 268
    assert set(signs) == {0, 1}

    s_value, w, v = variables
    triangle_scale = 2 - sp.sqrt(2) + (sp.sqrt(2) - 1) * s_value
    side_23 = 1 - triangle_scale * w / 2
    side_31 = 1 - triangle_scale + triangle_scale * w / 2
    u = (sp.sqrt(2) - 1) * v
    expected_denominator = (
        -4096
        * (1 + u**2)
        * side_23**3
        * side_31**3
        * (1 - side_23**3)
        * (1 - side_31**3)
    )
    assert sp.factor(denominator - expected_denominator) == 0


def test_first_gap_acceleration_is_negative_at_every_ordered_syzygy() -> None:
    generic_margin, kinetic_coefficient, torque_ratio, generic_variables = (
        _generic_ordered_syzygy_first_gap_energy_margin()
    )
    m, n, y = generic_variables
    _, denominator = sp.fraction(generic_margin)
    positive_factor = m * n + m * y**2 + n * (1 - y) ** 2
    expected_denominator = (
        m * n * y**2 * (1 - y) ** 2 * positive_factor
    )
    assert sp.factor(denominator - expected_denominator) == 0
    side_23 = 1 - y
    potential = m * n + n / side_23 + m / y
    centrifugal_coefficient = (
        (1 - torque_ratio) ** 2 / m**2 - side_23**-3
    )
    gravity_gap = sp.factor(
        generic_margin
        - 2 * potential * centrifugal_coefficient / kinetic_coefficient
    )
    direct_collinear_gravity_gap = (
        -n - (m + 1) / y**2 + n / side_23**2
    )
    assert sp.factor(gravity_gap - direct_collinear_gravity_gap) == 0

    numerator, variables = ordered_syzygy_first_gap_energy_numerator()
    polynomial = sp.Poly(numerator, *variables)
    assert tuple(polynomial.degree(variable) for variable in variables) == (20, 6)
    coefficients = ordered_syzygy_first_gap_energy_bernstein_coefficients()
    signs = tuple(sp.sign(coefficient) for coefficient in coefficients)
    assert len(coefficients) == 147
    assert signs.count(-1) == 133
    assert signs.count(0) == 14
    assert set(signs) == {-1, 0}

    parameter, syzygy_fraction = variables
    cube_values = {
        parameter: sp.Rational(1, 2),
        syzygy_fraction: sp.Rational(1, 2),
    }
    tied_parameter = (sp.sqrt(2) - 1) * cube_values[parameter]
    mass_1 = (1 - tied_parameter**2) / (1 + tied_parameter**2)
    mass_2 = 2 * tied_parameter / (1 + tied_parameter**2)
    side_31 = (
        mass_2
        * cube_values[syzygy_fraction]
        / (mass_1 + mass_2)
    )
    generic_values = {m: mass_1, n: mass_2, y: side_31}
    generic_numerator, _ = sp.fraction(generic_margin)
    generic_polynomial = sp.Poly(generic_numerator, m, n, y)
    maximum_mass_degree = max(
        exponent[0] + exponent[1]
        for exponent, _ in generic_polynomial.terms()
    )
    maximum_side_degree = generic_polynomial.degree(y)
    mass_denominator = 1 + tied_parameter**2
    mass_sum_numerator = (
        1 - tied_parameter**2 + 2 * tied_parameter
    )
    clearing_factor = (
        mass_denominator**maximum_mass_degree
        * mass_sum_numerator**maximum_side_degree
    )
    assert sp.factor(
        numerator.subs(cube_values)
        - generic_numerator.subs(generic_values) * clearing_factor
    ) == 0
    assert sp.sign(generic_margin.subs(generic_values)) == -1
    assert sp.sign(kinetic_coefficient.subs(generic_values)) == 1
    assert 0 < torque_ratio.subs(generic_values) < 1
    assert float(generic_margin.subs(generic_values)) == pytest.approx(
        -98.52430370591595, rel=2e-14
    )


def test_ordered_syzygy_kinetic_coefficient_matches_transverse_minimum() -> None:
    _, kinetic_coefficient, torque_ratio, variables = (
        _generic_ordered_syzygy_first_gap_energy_margin()
    )
    m, n, y = variables
    values = {m: sp.Rational(4, 5), n: sp.Rational(3, 5), y: sp.Rational(1, 5)}
    x = 1 - values[y]
    velocity_1, velocity_2, velocity_3 = sp.symbols("v1 v2 v3")
    solution = sp.solve(
        [
            values[m] * velocity_1 + values[n] * velocity_2 + velocity_3,
            values[n] * velocity_2 + values[y] * velocity_3,
            x * (velocity_2 - velocity_3) - 1,
        ],
        [velocity_1, velocity_2, velocity_3],
        dict=True,
    )[0]
    twice_kinetic = (
        values[m] * solution[velocity_1] ** 2
        + values[n] * solution[velocity_2] ** 2
        + solution[velocity_3] ** 2
    )
    assert sp.factor(kinetic_coefficient.subs(values) - twice_kinetic) == 0
    expected_ratio = (
        values[y] * (values[m] + x) / (x * (values[n] + values[y]))
    )
    assert sp.factor(torque_ratio.subs(values) - expected_ratio) == 0


def test_ordered_syzygy_longitudinal_energy_diagonalization() -> None:
    data, variables = ordered_syzygy_longitudinal_kinetic_decomposition()
    m, n, q, scale, sigma, shape_rate = variables
    assert data["diagonal_residual"] == 0
    assert data["dilational_residual"] == 0
    assert sp.factor(
        m * data["velocity_1"]
        + n * data["velocity_2"]
        + data["velocity_3"]
    ) == 0
    assert sp.factor(
        data["velocity_2"]
        - data["velocity_1"]
        - sigma / sp.sqrt(scale)
    ) == 0
    assert sp.factor(
        data["velocity_3"]
        - data["velocity_1"]
        - q * sigma / sp.sqrt(scale)
        - shape_rate / sp.sqrt(scale)
    ) == 0
    total_mass = m + n + 1
    expected_inertia_core = m * n + m * q**2 + n * (1 - q) ** 2
    assert sp.factor(data["inertia_core"] - expected_inertia_core) == 0
    assert sp.factor(
        data["inertia"] - scale**2 * expected_inertia_core / total_mass
    ) == 0

    values = {
        m: sp.Rational(4, 5),
        n: sp.Rational(3, 5),
        q: sp.Rational(1, 5),
        scale: sp.Rational(3, 4),
        sigma: sp.Rational(-2, 7),
        shape_rate: sp.Rational(5, 11),
    }
    assert sp.sign(data["scaled_longitudinal"].subs(values)) == 1
    assert sp.sign(data["inertia"].subs(values)) == 1


def test_syzygy_torque_amplitude_energy_deficit_is_exact() -> None:
    threshold, variables = ordered_syzygy_torque_energy_threshold()
    m, n, q, scale = variables
    assert threshold["deficit_residual"] == 0
    longitudinal = sp.symbols("L", nonnegative=True)
    energy_amplitude = sp.factor(
        (
            2 * (threshold["U"] - threshold["U0"] * scale)
            - longitudinal
        )
        / threshold["F"]
    )
    assert sp.factor(
        threshold["ZJ"]
        - energy_amplitude
        - (longitudinal - threshold["longitudinal_deficit"])
        / threshold["F"]
    ) == 0

    values = {
        m: sp.Rational(4, 5),
        n: sp.Rational(3, 5),
        q: sp.Rational(1, 5),
    }
    assert sp.sign(threshold["F"].subs(values)) == 1
    assert sp.sign(threshold["critical_scale"].subs(values)) == 1
    assert sp.factor(
        threshold["longitudinal_deficit"].subs(
            {**values, scale: threshold["critical_scale"].subs(values)}
        )
    ) == 0


def test_syzygy_strict_rate_signs_do_not_coerce_longitudinal_energy() -> None:
    witness, variables = ordered_syzygy_small_longitudinal_sign_witness()
    m, n, q, scale, epsilon = variables
    assert sp.factor(
        witness["slope_interval_numerator"]
        - (2 * m * n + m * q - n * q + n)
    ) == 0
    assert sp.factor(
        witness["second_gap_rate"]
        - 2 * epsilon * (witness["slope"] - witness["lower_slope"])
    ) == 0
    assert sp.factor(
        witness["dilation_core"]
        + epsilon
        * witness["torque_margin"]
        * (witness["upper_slope"] - witness["slope"])
    ) == 0
    assert sp.limit(witness["scaled_longitudinal"], epsilon, 0) == 0
    assert sp.factor(
        sp.diff(witness["scaled_longitudinal"], epsilon).subs(epsilon, 0)
    ) == 0

    values = {
        m: sp.Rational(4, 5),
        n: sp.Rational(3, 5),
        q: sp.Rational(1, 5),
        scale: sp.Rational(3, 4),
        epsilon: sp.Rational(1, 1000),
    }
    assert sp.sign(witness["torque_margin"].subs(values)) == 1
    assert sp.sign(witness["slope_interval_numerator"].subs(values)) == 1
    assert sp.sign(witness["side_31_rate"].subs(values)) == -1
    assert sp.sign(witness["second_gap_rate"].subs(values)) == 1
    assert sp.sign(witness["dilation_core"].subs(values)) == -1
    assert sp.sign(witness["scaled_longitudinal"].subs(values)) == 1


def test_torque_threshold_has_exact_ordered_syzygy_boundary_value() -> None:
    data, variables = _generic_ordered_syzygy_torque_thresholds()
    m, n, y = variables
    assert data["h_minus_eta"] == 0
    assert data["P"] == 0
    assert data["S"] == 0
    history_source, shape_source, _, physical_variables = (
        log_torque_threshold_contact_terms()
    )
    assert physical_variables == (m, n, sp.Symbol("x", positive=True), y)
    assert sp.factor(
        history_source - data["area_squared"] * data["P_reduced"]
    ) == 0
    assert sp.factor(
        shape_source - data["area_squared"] * data["S_reduced"]
    ) == 0
    assert sp.factor(
        (1 - data["eta"]) * (1 - y) * (n + y)
        - (n - (m + n) * y)
    ) == 0

    values = {
        m: sp.Rational(4, 5),
        n: sp.Rational(3, 5),
        y: sp.Rational(1, 5),
    }
    assert 0 < data["eta"].subs(values) < 1
    assert sp.sign(data["ZJ"].subs(values)) == 1
    assert sp.sign(data["C2"].subs(values)) == -1
    assert sp.sign(data["G2"].subs(values)) == 1
    assert sp.sign(data["Z2_minus_ZJ"].subs(values)) == 1


def test_torque_contact_amplitude_is_stronger_on_ordered_syzygy_face() -> None:
    data, physical_variables = _generic_ordered_syzygy_torque_thresholds()
    m, n, y = physical_variables
    contact_numerator, contact_denominator = sp.fraction(data["ZJ"])
    contact_numerator_core = sp.factor(
        contact_numerator
        / (
            2
            * m**2
            * (n + y) ** 2
            * (y - 1)
            * (y**2 - y + 2)
        )
    )
    positive_contact_denominator_factor = (
        y * (m * n + m * y**2 + n * (1 - y) ** 2)
    )
    contact_denominator_core = sp.factor(
        contact_denominator / positive_contact_denominator_factor
    )
    second_numerator, second_denominator = sp.fraction(data["C2"])
    second_coefficient_core = sp.factor(-second_numerator)
    assert sp.factor(
        second_denominator
        - m**2 * y * (n + y) ** 2 * (y - 1) ** 3
    ) == 0
    difference_numerator, difference_denominator = sp.fraction(
        data["Z2_minus_ZJ"]
    )
    difference_core = sp.factor(
        difference_numerator
        / (-m**2 * (n + y) ** 2 * (y - 1) * (2 * y - 1))
    )
    assert sp.factor(
        difference_denominator
        - positive_contact_denominator_factor
        * second_coefficient_core
        * contact_denominator_core
    ) == 0

    cores, variables = ordered_syzygy_torque_amplitude_sign_cores()
    expected = {
        "contact_numerator": ((11, 5), -1, 71, 1),
        "contact_denominator": ((12, 5), 1, 71, 7),
        "second_coefficient": ((11, 3), -1, 39, 9),
        "difference": ((26, 10), 1, 274, 23),
    }
    certificates = ordered_syzygy_torque_amplitude_bernstein_coefficients()
    for name, (degrees, strict_sign, strict_count, zero_count) in expected.items():
        polynomial = sp.Poly(cores[name], *variables)
        assert tuple(polynomial.degree(variable) for variable in variables) == degrees
        coefficients = certificates[name]
        signs = tuple(sp.sign(coefficient) for coefficient in coefficients)
        assert len(coefficients) == (degrees[0] + 1) * (degrees[1] + 1)
        assert signs.count(strict_sign) == strict_count
        assert signs.count(0) == zero_count
        assert set(signs) == {strict_sign, 0}

        # The equal-mass edge v=1 is strict for every 0<z<1: all its
        # Bernstein coefficients have the claimed sign except the z=1 end.
        edge = signs[degrees[0] * (degrees[1] + 1) :]
        assert edge[:-1] == (strict_sign,) * degrees[1]
        assert edge[-1] == 0

    # Regress every cleared core against its independently extracted physical
    # factor at an exact interior tied point.
    v, z = variables
    cube_values = {v: sp.Rational(2, 3), z: sp.Rational(3, 7)}
    u = (sp.sqrt(2) - 1) * cube_values[v]
    mass_denominator = 1 + u**2
    mass_1 = (1 - u**2) / mass_denominator
    mass_2 = 2 * u / mass_denominator
    side_31 = mass_2 * cube_values[z] / (mass_1 + mass_2)
    physical_values = {m: mass_1, n: mass_2, y: side_31}
    physical_cores = {
        "contact_numerator": contact_numerator_core,
        "contact_denominator": contact_denominator_core,
        "second_coefficient": second_coefficient_core,
        "difference": difference_core,
    }
    for name, physical_core in physical_cores.items():
        physical_polynomial = sp.Poly(physical_core, m, n, y)
        maximum_mass_degree = max(
            exponent[0] + exponent[1]
            for exponent, _ in physical_polynomial.terms()
        )
        maximum_side_degree = physical_polynomial.degree(y)
        clearing_factor = (
            mass_denominator**maximum_mass_degree
            * (1 - u**2 + 2 * u) ** maximum_side_degree
        )
        assert sp.factor(
            cores[name].subs(cube_values)
            - physical_core.subs(physical_values) * clearing_factor
        ) == 0


def test_second_gap_static_sign_fails_even_on_ordered_syzygy_face() -> None:
    obstruction = ordered_syzygy_second_gap_static_obstruction()
    assert obstruction["u"] == sp.Rational(1, 3)
    assert obstruction["m1"] == sp.Rational(4, 5)
    assert obstruction["m2"] == sp.Rational(3, 5)
    assert obstruction["r31"] == sp.Rational(3, 700)
    assert obstruction["r23"] == sp.Rational(697, 700)
    assert 0 < obstruction["eta"] < 1
    assert sp.sign(obstruction["kinetic_coefficient"]) == 1
    assert sp.sign(obstruction["potential"] - obstruction["initial_potential"]) == 1
    assert sp.factor(
        obstruction["amplitude"]
        * obstruction["kinetic_coefficient"]
        / 2
        - obstruction["potential"]
        + obstruction["initial_potential"]
    ) == 0
    assert sp.sign(obstruction["amplitude"]) == 1
    assert sp.sign(obstruction["centrifugal_coefficient"]) == -1
    assert sp.sign(obstruction["gravity_gap"]) == 1
    assert sp.sign(obstruction["crossing_coefficient"]) == -1
    assert sp.sign(obstruction["second_acceleration"]) == -1
    assert obstruction["second_acceleration"] == sp.Rational(
        -96354167469624287, 1827657180810
    )


def test_second_gap_critical_barrier_is_not_pointwise_invariant() -> None:
    obstruction = second_gap_barrier_outward_contact_obstruction()
    assert obstruction["u"] == sp.Rational(1, 3)
    assert obstruction["m1"] == sp.Rational(4, 5)
    assert obstruction["m2"] == sp.Rational(3, 5)
    assert obstruction["r23_ratio"] == sp.Rational(499, 500)
    assert obstruction["r31_ratio"] == sp.Rational(1, 20)
    assert obstruction["eta"] == sp.Rational(3, 20)
    assert obstruction["pythagorean_defect"] == sp.Rational(187, 125000)
    assert obstruction["twice_area_ratio"] == 4 * sp.sqrt(37986) / 15625
    assert sp.sign(obstruction["gravity_gap"]) == 1
    assert sp.sign(obstruction["centrifugal_coefficient"]) == -1
    assert sp.sign(obstruction["amplitude"]) == 1
    assert sp.factor(
        obstruction["gravity_gap"]
        + obstruction["amplitude"]
        * obstruction["centrifugal_coefficient"]
    ) == 0
    assert tuple(
        sp.sign(obstruction[name])
        for name in ("ell_12", "ell_23", "ell_31")
    ) == (-1, 1, -1)
    assert sp.factor(
        sp.diff(obstruction["kinetic"], sp.symbols("sigma", real=True)).subs(
            sp.symbols("sigma", real=True), obstruction["scale_rate"]
        )
    ) == 0
    assert sp.sign(obstruction["kinetic_minimum"]) == 1
    assert sp.sign(obstruction["physical_scale"]) == 1
    assert sp.factor(
        obstruction["kinetic_minimum"]
        - obstruction["potential"]
        + obstruction["initial_potential"]
        * obstruction["physical_scale"]
    ) == 0
    assert (
        0
        < obstruction["current_ratio"]
        < obstruction["eta"]
        < obstruction["initial_ratio"]
        < 1
    )
    assert sp.sign(obstruction["history_rate"]) == -1
    assert sp.sign(obstruction["area_rate"]) == -1
    assert sp.sign(obstruction["log_barrier_rate"]) == 1


def test_pair_torque_kinetic_coefficient_matches_gram_inverse() -> None:
    coefficient, variables = pair_torque_kinetic_coefficient()
    m, n, p, q, z = variables
    values = {
        m: sp.Rational(4, 5),
        n: sp.Rational(3, 5),
        p: sp.Rational(4, 5),
        q: sp.Rational(3, 5),
        z: sp.Rational(1, 10),
    }
    mass_12 = values[m] + values[n]
    total_mass = mass_12 + 1
    alpha = values[m] / mass_12
    beta = values[n] / mass_12
    reduced_1 = values[m] * values[n] / mass_12
    reduced_2 = mass_12 / total_mass
    apex_x = (values[q] ** 2 + 1 - values[p] ** 2) / 2
    apex_y = sp.sqrt(values[q] ** 2 - apex_x**2)
    jacobi_x = apex_x - beta
    pair_23_x = jacobi_x - alpha
    pair_31_x = jacobi_x + beta
    inverse_mass_metric = sp.diag(
        1 / reduced_1, 1 / reduced_1, 1 / reduced_2, 1 / reduced_2
    )
    constraints = sp.Matrix(
        [
            [0, reduced_1, -reduced_2 * apex_y, reduced_2 * jacobi_x],
            [
                alpha * apex_y,
                -alpha * pair_23_x,
                -apex_y,
                pair_23_x,
            ],
            [
                -beta * apex_y,
                beta * pair_31_x,
                -apex_y,
                pair_31_x,
            ],
        ]
    )
    gram = constraints * inverse_mass_metric * constraints.T
    target = sp.Matrix([0, 1, -values[z]])
    direct = (target.T * gram.inv() * target)[0]
    assert sp.factor(coefficient.subs(values) - direct) == 0


def test_static_signed_torque_energy_bound_has_exact_obstruction() -> None:
    margin, cube_point = first_gap_static_energy_obstruction()
    assert all(0 < coordinate < 1 for coordinate in cube_point)
    assert sp.sign(margin) == 1
    assert float(margin) == pytest.approx(93.22806690526964, rel=2e-15)


def test_static_first_return_barrier_has_exact_obstruction() -> None:
    obstruction = torque_rate_first_return_static_obstruction()
    assert obstruction["angular_momentum"] == 0
    assert obstruction["log_ratio_rate"] == 0
    assert tuple(
        sp.sign(obstruction[name]) for name in ("ell_12", "ell_23", "ell_31")
    ) == (-1, 1, -1)
    assert sp.sign(obstruction["velocity_curvature"]) == 1
    assert sp.sign(obstruction["kinetic"]) == 1
    assert sp.sign(obstruction["gravity_curvature"]) == -1
    assert sp.sign(obstruction["scaled_curvature_numerator"]) == 1
    assert float(obstruction["scaled_curvature_numerator"]) == pytest.approx(
        10682.0701224264, rel=2e-14
    )


@pytest.mark.parametrize(
    ("triangle_scale", "order_split", "parameter"),
    ((0.2, 0.3, 0.25), (0.7, 0.4, 0.6), (0.95, 0.1, 0.9)),
)
def test_ordered_shape_gravity_gap_matches_cartesian_force(
    triangle_scale: float, order_split: float, parameter: float
) -> None:
    u = (np.sqrt(2.0) - 1.0) * parameter
    mass_a = (1 - u * u) / (1 + u * u)
    mass_b = 2 * u / (1 + u * u)
    masses = np.array([mass_a, mass_b, 1.0])
    r23 = 1 - triangle_scale * order_split / 2
    r31 = 1 - triangle_scale + triangle_scale * order_split / 2
    q3x = (r31 * r31 + 1 - r23 * r23) / 2
    q3y = np.sqrt(r31 * r31 - q3x * q3x)
    positions = np.array([[0.0, 0.0], [1.0, 0.0], [q3x, q3y]])
    state = np.concatenate([positions.ravel(), np.zeros(6)])
    accelerations = right_hand_side(0.0, state, masses)[6:].reshape(3, 2)
    radial_23 = np.dot(
        positions[2] - positions[1], accelerations[2] - accelerations[1]
    ) / r23
    radial_31 = np.dot(
        positions[0] - positions[2], accelerations[0] - accelerations[2]
    ) / r31

    gap, variables = ordered_shape_gravity_gap()
    evaluated = float(
        gap.subs(
            dict(
                zip(
                    variables,
                    (triangle_scale, order_split, parameter),
                    strict=True,
                )
            )
        )
    )
    assert radial_23 - radial_31 == pytest.approx(evaluated, rel=2e-12)
    assert evaluated > 0


@pytest.mark.parametrize(
    ("depth", "order_split", "parameter"),
    ((0.1, 0.2, 0.3), (0.5, 0.7, 0.6), (0.9, 0.1, 0.95)),
)
def test_ordered_obtuse_first_gap_matches_cartesian_force(
    depth: float, order_split: float, parameter: float
) -> None:
    u = (np.sqrt(2.0) - 1.0) * parameter
    masses = np.array(
        [(1 - u * u) / (1 + u * u), 2 * u / (1 + u * u), 1.0]
    )
    lower_scale = 2 - np.sqrt(2.0)
    triangle_scale = lower_scale + (1 - lower_scale) * depth
    r23 = 1 - triangle_scale * order_split / 2
    r31 = 1 - triangle_scale + triangle_scale * order_split / 2
    q3x = (r31 * r31 + 1 - r23 * r23) / 2
    q3y = np.sqrt(r31 * r31 - q3x * q3x)
    positions = np.array([[0.0, 0.0], [1.0, 0.0], [q3x, q3y]])
    state = np.concatenate([positions.ravel(), np.zeros(6)])
    accelerations = right_hand_side(0.0, state, masses)[6:].reshape(3, 2)
    radial_12 = np.dot(
        positions[1] - positions[0], accelerations[1] - accelerations[0]
    )
    radial_23 = np.dot(
        positions[2] - positions[1], accelerations[2] - accelerations[1]
    ) / r23

    gap, variables = ordered_obtuse_gravity_first_gap()
    evaluated = float(
        gap.subs(dict(zip(variables, (depth, order_split, parameter), strict=True)))
    )
    assert radial_12 - radial_23 == pytest.approx(evaluated, rel=5e-12)
    assert evaluated < 0


@pytest.mark.parametrize(
    ("depth", "order_split", "parameter"),
    ((0.15, 0.25, 0.2), (0.55, 0.65, 0.55), (0.9, 0.15, 0.9)),
)
def test_log_torque_ratio_gravity_curvature_matches_cartesian_force(
    depth: float, order_split: float, parameter: float
) -> None:
    u = (np.sqrt(2.0) - 1.0) * parameter
    masses = np.array(
        [(1 - u * u) / (1 + u * u), 2 * u / (1 + u * u), 1.0]
    )
    triangle_scale = 2 - np.sqrt(2.0) + (np.sqrt(2.0) - 1) * depth
    r23 = 1 - triangle_scale * order_split / 2
    r31 = 1 - triangle_scale + triangle_scale * order_split / 2
    q3x = (r31 * r31 + 1 - r23 * r23) / 2
    q3y = np.sqrt(r31 * r31 - q3x * q3x)
    positions = np.array([[0.0, 0.0], [1.0, 0.0], [q3x, q3y]])
    state = np.concatenate([positions.ravel(), np.zeros(6)])
    accelerations = right_hand_side(0.0, state, masses)[6:].reshape(3, 2)
    radial_12 = np.dot(
        positions[1] - positions[0], accelerations[1] - accelerations[0]
    )
    radial_23 = np.dot(
        positions[2] - positions[1], accelerations[2] - accelerations[1]
    ) / r23
    radial_31 = np.dot(
        positions[0] - positions[2], accelerations[0] - accelerations[2]
    ) / r31
    direct = (
        3 * (radial_31 - r31 * radial_12) / (r31 * (1 - r31**3))
        - 3 * (radial_23 - r23 * radial_12) / (r23 * (1 - r23**3))
    )

    curvature, variables = ordered_obtuse_log_torque_ratio_gravity_curvature()
    evaluated = float(
        curvature.subs(
            dict(zip(variables, (depth, order_split, parameter), strict=True))
        )
    )
    assert direct == pytest.approx(evaluated, rel=1e-9)
    assert evaluated < 0
