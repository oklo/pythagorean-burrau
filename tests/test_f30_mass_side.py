"""Exact regressions for the validated F30 mass--side shooting system."""

from __future__ import annotations

import sympy as sp


def test_cartesian_mass_coefficients_preserve_total_momentum() -> None:
    """The three accelerations in the CAPD field have zero mass sum."""
    a, b = sp.symbols("a b", positive=True)
    q1x, q1y, q2x, q2y, q3x, q3y = sp.symbols(
        "q1x q1y q2x q2y q3x q3y", real=True
    )
    q1 = sp.Matrix([q1x, q1y])
    q2 = sp.Matrix([q2x, q2y])
    q3 = sp.Matrix([q3x, q3y])

    def force_vector(source: sp.Matrix, target: sp.Matrix) -> sp.Matrix:
        displacement = target - source
        return displacement / sp.Pow(displacement.dot(displacement), sp.Rational(3, 2))

    acceleration1 = b * force_vector(q1, q2) + force_vector(q1, q3)
    acceleration2 = a * force_vector(q2, q1) + force_vector(q2, q3)
    acceleration3 = a * force_vector(q3, q1) + b * force_vector(q3, q2)
    total_force = sp.simplify(
        a * acceleration1 + b * acceleration2 + acceleration3
    )
    assert all(sp.simplify(component) == 0 for component in total_force)


def test_mass_side_matching_defect_is_opposite_pythagorean_defect() -> None:
    """On r23=a, r31=b, r12=1, geometric and mass defects are opposite."""
    a, b = sp.symbols("a b", positive=True)
    geometric_right_defect = 1 - a**2 - b**2
    mass_pythagorean_defect = a**2 + b**2 - 1
    assert sp.expand(geometric_right_defect + mass_pythagorean_defect) == 0


def test_pythagorean_tied_shape_has_the_requested_opposite_sides() -> None:
    a, b = sp.symbols("a b", positive=True)
    x = (b**2 - a**2) / 2
    y = a * b
    r23_squared = sp.expand((x - sp.Rational(1, 2)) ** 2 + y**2)
    r31_squared = sp.expand((x + sp.Rational(1, 2)) ** 2 + y**2)
    _, remainder23 = sp.reduced(r23_squared - a**2, [a**2 + b**2 - 1], a, b)
    _, remainder31 = sp.reduced(r31_squared - b**2, [a**2 + b**2 - 1], a, b)
    assert sp.simplify(remainder23) == 0
    assert sp.simplify(remainder31) == 0


def test_global_pair23_complement_equations_match_cartesian_forces() -> None:
    """The globally regularized verifier uses the exact pair-23 split."""
    a, b = sp.symbols("a b", positive=True)
    gx, gy, big_x, big_y = sp.symbols("g_x g_y G_x G_y", real=True)
    inv12, inv13 = sp.symbols("R12 R13", positive=True)
    g = sp.Matrix([gx, gy])
    big_g = sp.Matrix([big_x, big_y])
    d12 = big_g + g / (b + 1)  # q1-q2
    d13 = big_g - b * g / (b + 1)  # q1-q3

    # Pair center C23 is set to zero; translations cancel from accelerations.
    q1 = big_g
    q2 = -g / (b + 1)
    q3 = b * g / (b + 1)
    acc1 = b * (q2 - q1) * inv12 + (q3 - q1) * inv13
    acc2 = a * (q1 - q2) * inv12 + (q3 - q2) / sp.Symbol("r23") ** 3
    acc3 = a * (q1 - q3) * inv13 + b * (q2 - q3) / sp.Symbol("r23") ** 3
    center_acc = (b * acc2 + acc3) / (b + 1)

    expected_gdd = -(b + 1) * g / sp.Symbol("r23") ** 3 + a * (
        d13 * inv13 - d12 * inv12
    )
    expected_big_gdd = -(a + b + 1) / (b + 1) * (
        b * d12 * inv12 + d13 * inv13
    )
    assert all(sp.simplify(value) == 0 for value in acc3 - acc2 - expected_gdd)
    assert all(sp.simplify(value) == 0 for value in acc1 - center_acc - expected_big_gdd)

    def cross(left: sp.Matrix, right: sp.Matrix) -> sp.Expr:
        return left[0] * right[1] - left[1] * right[0]

    external = a * (d13 * inv13 - d12 * inv12)
    pair_reduced_mass = b / (b + 1)
    complement_reduced_mass = a * (b + 1) / (a + b + 1)
    angular_derivative = (
        pair_reduced_mass * cross(g, external)
        + complement_reduced_mass * cross(big_g, expected_big_gdd)
    )
    assert sp.simplify(angular_derivative) == 0


def test_global_lc_initial_map_tangent_is_exact() -> None:
    """Differentiate every nonconstant initial-state formula used by CAPD."""
    wr, wi, regularized_time, a, b = sp.symbols("w_r w_i S a b", positive=True)
    parameters = (wr, wi, regularized_time, a, b)
    radius = wr**2 + wi**2
    gx = wr**2 - wi**2
    gy = 2 * wr * wi
    pair = b + 1
    state = sp.Matrix(
        [
            wr,
            wi,
            0,
            0,
            -pair / radius,
            (-b - 1 - gx) / pair,
            -gy / pair,
            0,
            0,
            0,
            a,
            b,
            regularized_time,
        ]
    )
    implemented = sp.zeros(13, 5)
    implemented[0, 0] = 1
    implemented[1, 1] = 1
    implemented[4, 0] = 2 * pair * wr / radius**2
    implemented[4, 1] = 2 * pair * wi / radius**2
    implemented[4, 4] = -1 / radius
    implemented[5, 0] = -2 * wr / pair
    implemented[5, 1] = 2 * wi / pair
    implemented[5, 4] = gx / pair**2
    implemented[6, 0] = -2 * wi / pair
    implemented[6, 1] = -2 * wr / pair
    implemented[6, 4] = gy / pair**2
    implemented[10, 3] = 1
    implemented[11, 4] = 1
    implemented[12, 2] = 1
    difference = state.jacobian(parameters) - implemented
    assert all(sp.simplify(value) == 0 for value in difference)


def test_global_lc_side_residual_derivatives_are_exact() -> None:
    wr, wi, a, b = sp.symbols("w_r w_i a b", real=True)
    gx = wr**2 - wi**2
    gy = 2 * wr * wi
    r31 = sp.sqrt((gx + 1) ** 2 + gy**2)
    side_residuals = sp.Matrix([wr**2 + wi**2 - a, r31 - b])
    variables = (wr, wi, sp.Symbol("S"), a, b)
    implemented = sp.Matrix(
        [
            [2 * wr, 2 * wi, 0, -1, 0],
            [
                ((gx + 1) * 2 * wr + gy * 2 * wi) / r31,
                (-(gx + 1) * 2 * wi + gy * 2 * wr) / r31,
                0,
                0,
                -1,
            ],
        ]
    )
    difference = side_residuals.jacobian(variables) - implemented
    assert all(sp.simplify(value) == 0 for value in difference)


def test_global_lc_field_reconstructs_selected_pair_acceleration() -> None:
    """The LC z-equation desingularizes g''=-M g/|g|^3+F exactly."""
    wr, wi, zr, zi, pair_mass = sp.symbols(
        "w_r w_i z_r z_i M", real=True, nonzero=True
    )
    fx, fy = sp.symbols("F_x F_y", real=True)
    radius = wr**2 + wi**2
    g = sp.Matrix([wr**2 - wi**2, 2 * wr * wi])
    g_velocity = sp.Matrix(
        [
            2 * (wr * zr - wi * zi) / radius,
            2 * (wr * zi + wi * zr) / radius,
        ]
    )
    pair_energy = sp.expand(g_velocity.dot(g_velocity) / 2 - pair_mass / radius)
    z_derivative = sp.Matrix(
        [
            pair_energy * wr / 2 + radius * (wr * fx + wi * fy) / 2,
            pair_energy * wi / 2 + radius * (wr * fy - wi * fx) / 2,
        ]
    )
    variables = sp.Matrix([wr, wi, zr, zi])
    sigma_field = sp.Matrix([zr, zi, z_derivative[0], z_derivative[1]])
    sigma_derivative = g_velocity.jacobian(variables) * sigma_field
    physical_acceleration = sp.simplify(sigma_derivative / radius)
    expected = -pair_mass * g / radius**3 + sp.Matrix([fx, fy])
    assert all(
        sp.factor(sp.together(value)) == 0
        for value in physical_acceleration - expected
    )


def test_chart_native_lc_brake_residual_is_complete() -> None:
    """At z=0 and L=0, (G dot P)=0 forces P=0 whenever G is nonzero."""
    gx, gy = sp.symbols("G_x G_y", real=True)
    coefficient_matrix = sp.Matrix([[gx, gy], [-gy, gx]])
    assert coefficient_matrix.det() == gx**2 + gy**2
