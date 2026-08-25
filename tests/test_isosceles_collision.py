import sympy as sp


def test_pair12_jacobi_equations_match_cartesian_forces() -> None:
    mass_1, mass_2 = sp.symbols("m n", positive=True)
    gx, gy, big_x, big_y = sp.symbols("g_x g_y G_x G_y", real=True)
    pair_radius, radius_31, radius_23 = sp.symbols(
        "r12 r31 r23", positive=True
    )
    pair_mass = mass_1 + mass_2
    total_mass = pair_mass + 1
    g = sp.Matrix([gx, gy])
    big_g = sp.Matrix([big_x, big_y])
    d31 = big_g + mass_2 * g / pair_mass
    d23 = big_g - mass_1 * g / pair_mass

    pair_center = sp.zeros(2, 1)
    q1 = pair_center - mass_2 * g / pair_mass
    q2 = pair_center + mass_1 * g / pair_mass
    q3 = big_g

    def pair_force(source: sp.Matrix, target: sp.Matrix, radius: sp.Expr) -> sp.Matrix:
        return (target - source) / radius**3

    acceleration_1 = (
        mass_2 * pair_force(q1, q2, pair_radius)
        + pair_force(q1, q3, radius_31)
    )
    acceleration_2 = (
        mass_1 * pair_force(q2, q1, pair_radius)
        + pair_force(q2, q3, radius_23)
    )
    acceleration_3 = (
        mass_1 * pair_force(q3, q1, radius_31)
        + mass_2 * pair_force(q3, q2, radius_23)
    )
    center_acceleration = (
        mass_1 * acceleration_1 + mass_2 * acceleration_2
    ) / pair_mass

    expected_pair = (
        -pair_mass * g / pair_radius**3
        + d23 / radius_23**3
        - d31 / radius_31**3
    )
    expected_complement = -total_mass / pair_mass * (
        mass_1 * d31 / radius_31**3 + mass_2 * d23 / radius_23**3
    )
    assert all(
        sp.simplify(value) == 0
        for value in acceleration_2 - acceleration_1 - expected_pair
    )
    assert all(
        sp.simplify(value) == 0
        for value in acceleration_3 - center_acceleration - expected_complement
    )


def test_isosceles_pair12_lc_launch_tangent_is_exact() -> None:
    root_two = sp.sqrt(2)
    v = sp.symbols("v", real=True)
    u = (root_two - 1) * v
    mass_1 = (1 - u**2) / (1 + u**2)
    mass_2 = 2 * u / (1 + u**2)
    pair_mass = mass_1 + mass_2
    apex_x = (mass_2**2 - mass_1**2) / 2
    apex_y = mass_1 * mass_2
    center_x = (mass_2 - mass_1) / (2 * pair_mass)
    state = sp.Matrix(
        [
            1,
            0,
            0,
            0,
            -pair_mass,
            apex_x - center_x,
            apex_y,
            0,
            0,
            0,
            mass_1,
            mass_2,
        ]
    )
    endpoint = sp.simplify(state.subs(v, 1))
    tangent = sp.simplify(state.diff(v).subs(v, 1))
    expected_endpoint = sp.Matrix(
        [1, 0, 0, 0, -root_two, 0, sp.Rational(1, 2), 0, 0, 0,
         1 / root_two, 1 / root_two]
    )
    expected_tangent = sp.Matrix(
        [0, 0, 0, 0, 0, 1 / (2 * root_two), 0, 0, 0, 0,
         sp.Rational(-1, 2), sp.Rational(1, 2)]
    )
    assert all(sp.simplify(value) == 0 for value in endpoint - expected_endpoint)
    assert all(sp.simplify(value) == 0 for value in tangent - expected_tangent)


def test_lc_pair_angular_momentum_and_collision_normal() -> None:
    wr, wi, zr, zi = sp.symbols("w_r w_i z_r z_i", real=True)
    radius = wr**2 + wi**2
    pair_vector = sp.Matrix([wr**2 - wi**2, 2 * wr * wi])
    pair_velocity = sp.Matrix(
        [
            2 * (wr * zr - wi * zi) / radius,
            2 * (wr * zi + wi * zr) / radius,
        ]
    )
    angular_momentum = sp.factor(
        pair_vector[0] * pair_velocity[1]
        - pair_vector[1] * pair_velocity[0]
    )
    assert sp.expand(angular_momentum - 2 * (wr * zi - wi * zr)) == 0

    normal_variation, radial_speed, parameter = sp.symbols(
        "c z delta", real=True
    )
    section_momentum = angular_momentum.subs(
        {wr: 0, wi: parameter * normal_variation, zr: radial_speed}
    )
    assert sp.diff(section_momentum, parameter).subs(parameter, 0) == (
        -2 * normal_variation * radial_speed
    )
