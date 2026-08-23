"""Exact identities for the late-plunge rectilinear restricted limit."""

from __future__ import annotations

import sympy as sp


def outer_energy_exchange_identity() -> tuple[sp.Expr, sp.Expr]:
    """Return the derived and expected time derivative of outer energy."""
    z, velocity, separation, separation_velocity = sp.symbols(
        "z velocity separation separation_velocity", real=True
    )
    radius_squared = z**2 + separation**2 / 4
    acceleration = -2 * z / radius_squared ** sp.Rational(3, 2)
    energy = velocity**2 / 2 - 2 / sp.sqrt(radius_squared)
    derivative = (
        sp.diff(energy, z) * velocity
        + sp.diff(energy, velocity) * acceleration
        + sp.diff(energy, separation) * separation_velocity
    )
    expected = separation * separation_velocity / (2 * radius_squared ** sp.Rational(3, 2))
    return sp.simplify(derivative), expected


def transverse_variational_normal_form() -> sp.Expr:
    """Coefficient after removing the first derivative in the small-speed ODE."""
    phase = sp.symbols("phase", real=True)
    first_derivative_coefficient = 2 * sp.tan(phase)
    zeroth_order_coefficient = 16 * sp.sec(phase) ** 2
    normal_coefficient = (
        zeroth_order_coefficient
        - sp.diff(first_derivative_coefficient, phase) / 2
        - first_derivative_coefficient**2 / 4
    )
    return sp.trigsimp(normal_coefficient)


def time_shift_melnikov_identity() -> tuple[sp.Expr, sp.Expr]:
    """Show that the unnormalized phase Jacobi field gives a boundary term."""
    r, r_velocity, r_acceleration, z, z_velocity = sp.symbols(
        "r r_velocity r_acceleration z z_velocity", real=True
    )
    radius_squared = z**2 + r**2 / 4
    radius = sp.sqrt(radius_squared)
    integrand = (r_velocity**2 + r * r_acceleration) / (2 * radius**3) - 3 * r * r_velocity * (
        z * z_velocity + r * r_velocity / 4
    ) / (2 * radius**5)
    boundary_term = r * r_velocity / (2 * radius**3)
    derivative = (
        sp.diff(boundary_term, r) * r_velocity
        + sp.diff(boundary_term, r_velocity) * r_acceleration
        + sp.diff(boundary_term, z) * z_velocity
    )
    return sp.simplify(integrand), sp.simplify(derivative)


def phase_wronskian_identity() -> tuple[sp.Expr, sp.Expr]:
    """Wronskian evolution for the centered phase-transversality field."""
    h, h_velocity, z_velocity, z_acceleration = sp.symbols(
        "h h_velocity z_velocity z_acceleration", real=True
    )
    a, b, r_velocity = sp.symbols("a b r_velocity", real=True)
    derivative = (
        h_velocity * z_acceleration
        + h * (a * z_velocity + b * r_velocity)
        - a * h * z_velocity
        - h_velocity * z_acceleration
    )
    expected = h * b * r_velocity
    return sp.simplify(derivative), expected


def maximum_softened_vertical_force() -> tuple[sp.Expr, sp.Expr]:
    """Critical height and force maximum for fixed binary separation."""
    z, separation = sp.symbols("z separation", positive=True)
    force = 2 * z / (z**2 + separation**2 / 4) ** sp.Rational(3, 2)
    critical_height = separation / (2 * sp.sqrt(2))
    maximum = sp.simplify(force.subs(z, critical_height))
    return critical_height, maximum


def collision_regularized_jacobi_system() -> tuple[sp.Matrix, tuple[sp.Symbol, ...]]:
    """Return the finite CAPD system in eccentric anomaly.

    The state is ``(z,w,q,p)`` with ``w=dz/dtheta``, ``q=h/v`` and
    ``p=dq/dtheta``.  The independent variable is ``psi``, where
    ``r=cos(psi)^2`` and ``dtheta=r*dpsi``.
    """
    psi = sp.symbols("psi", real=True)
    z, w, q, p = sp.symbols("z w q p", real=True)
    separation = sp.cos(psi) ** 2
    radius_squared = z**2 + separation**2 / 4
    coefficient = (4 * z**2 - separation**2 / 2) / radius_squared ** sp.Rational(5, 2)
    system = sp.Matrix(
        [
            separation * w,
            -2 * z * separation / radius_squared ** sp.Rational(3, 2),
            separation * p,
            separation * coefficient * q,
        ]
    )
    return system, (psi, z, w, q, p)


def parabolic_infinity_compactification() -> tuple[sp.Matrix, tuple[sp.Symbol, ...]]:
    """Return the analytic compactified restricted field at parabolic infinity."""
    psi = sp.symbols("psi", real=True)
    x, velocity = sp.symbols("x velocity", real=True)
    separation = sp.cos(psi) ** 2
    field = sp.Matrix(
        [
            -separation * x**3 * velocity / 4,
            -separation * x**4 / (2 * (1 + separation**2 * x**4 / 16) ** sp.Rational(3, 2)),
        ]
    )
    return field, (psi, x, velocity)


def incoming_parabolic_infinity_compactification() -> tuple[
    sp.Matrix, tuple[sp.Symbol, ...]
]:
    """Analytic incoming chart ``z=-2/x**2`` at parabolic infinity."""
    psi = sp.symbols("psi", real=True)
    x, velocity = sp.symbols("x velocity", real=True)
    separation = sp.cos(psi) ** 2
    field = sp.Matrix(
        [
            separation * x**3 * velocity / 4,
            separation
            * x**4
            / (2 * (1 + separation**2 * x**4 / 16) ** sp.Rational(3, 2)),
        ]
    )
    return field, (psi, x, velocity)


def incoming_returned_jost_compactification() -> tuple[
    sp.Matrix, tuple[sp.Symbol, ...]
]:
    """Regular returned-Jost fiber over the incoming parabolic chart.

    Here ``z=-2/x**2``, ``P=x**2*p``, and ``Q=p_dot/x``.  The independent
    variable is binary eccentric anomaly and ``dt/dpsi=cos(psi)**2``.
    """
    psi = sp.symbols("psi", real=True)
    x, velocity, normalized_field, normalized_velocity = sp.symbols(
        "x velocity P Q", real=True
    )
    separation = sp.cos(psi) ** 2
    denominator = 1 + separation**2 * x**4 / 16
    coefficient_factor = (1 - separation**2 * x**4 / 8) / denominator ** sp.Rational(
        5, 2
    )
    field = sp.Matrix(
        [
            separation * x**3 * velocity / 4,
            separation * x**4 / (2 * denominator ** sp.Rational(3, 2)),
            separation
            * (x**2 * velocity * normalized_field / 2 + x**3 * normalized_velocity),
            -separation
            * (
                x**3 * coefficient_factor * normalized_field
                + x**2 * velocity * normalized_velocity
            )
            / 4,
        ]
    )
    return field, (psi, x, velocity, normalized_field, normalized_velocity)


def incoming_returned_jost_wronskian_compactification() -> tuple[
    sp.Matrix, tuple[sp.Symbol, ...]
]:
    """Regular incoming fiber in ``(P, Omega)`` variables.

    ``P=x**2*p`` and ``Omega=z*p_dot-z_dot*p`` retain both returned-Jost
    constants directly at the parabolic fixed circle.
    """
    psi = sp.symbols("psi", real=True)
    x, velocity, normalized_field, wronskian = sp.symbols(
        "x velocity P Omega", real=True
    )
    separation = sp.cos(psi) ** 2
    denominator = 1 + separation**2 * x**4 / 16
    field = sp.Matrix(
        [
            separation * x**3 * velocity / 4,
            separation * x**4 / (2 * denominator ** sp.Rational(3, 2)),
            -separation * x**4 * wronskian / 2,
            -sp.Rational(3, 32)
            * separation**3
            * x**6
            * normalized_field
            / denominator ** sp.Rational(5, 2),
        ]
    )
    return field, (psi, x, velocity, normalized_field, wronskian)


def parabolic_stroboscopic_leading_map() -> tuple[sp.Matrix, sp.Matrix]:
    """Degree-four period-map term before and after the stable-ray shear."""
    x, velocity, transverse = sp.symbols("x velocity transverse", real=True)
    original = sp.Matrix([-sp.pi * x**3 * velocity / 8, -sp.pi * x**4 / 4])
    sheared = sp.expand(original.subs(velocity, transverse + sp.sqrt(2) * x))
    transformed = sp.Matrix([sheared[0], sp.expand(sheared[1] - sp.sqrt(2) * sheared[0])])
    return original, transformed


def parabolic_truncated_energy_drift() -> tuple[sp.Expr, sp.Expr]:
    """Energy drift of the degree-four parabolic normal-form map.

    In the normalized variables ``H=y**2-x**2`` is the Kepler energy. The
    degree-four map preserves it through degree seven; its first displayed
    drift is degree eight and is proportional to ``H`` itself.
    """
    x, y, coefficient = sp.symbols("x y k", real=True)
    energy = y**2 - x**2
    x_next = x - coefficient * x**3 * y
    y_next = y - coefficient * x**4
    drift = sp.expand(y_next**2 - x_next**2 - energy)
    expected = -(coefficient**2) * x**6 * energy
    return drift, expected


def collision_kepler_transverse_transfer() -> tuple[sp.Expr, sp.Expr, sp.Expr]:
    """Transverse Jacobi mode from a radial collision to apocenter.

    The radial Kepler arc is ``s=R*sin(psi)**2`` with
    ``dt/dpsi=R**(3/2)*sin(psi)**2``. The normalized collision mode tends to
    ``sqrt(s)`` and reaches apocenter with physical velocity ``-1/R``.
    """
    psi = sp.symbols("psi", positive=True)
    turn_radius = sp.symbols("R", positive=True)
    radius = turn_radius * sp.sin(psi) ** 2
    time_rate = turn_radius ** sp.Rational(3, 2) * sp.sin(psi) ** 2
    mode = sp.sqrt(turn_radius) * sp.sin(psi) * sp.cos(psi)
    velocity = sp.simplify(sp.diff(mode, psi) / time_rate)
    acceleration = sp.simplify(sp.diff(velocity, psi) / time_rate)
    equation_residual = sp.trigsimp(acceleration + 2 * mode / radius**3)
    collision_normalization = sp.limit(mode / sp.sqrt(radius), psi, 0, dir="+")
    turn_velocity = sp.simplify(velocity.subs(psi, sp.pi / 2))
    return equation_residual, collision_normalization, turn_velocity


def turn_resonance_radial_determinants() -> tuple[sp.Expr, sp.Expr, sp.Expr]:
    """Return the three equivalent radial Jacobians at a turn resonance."""
    height, acceleration, phase_velocity = sp.symbols("Z a b", real=True, nonzero=True)
    turn_derivative = -phase_velocity / acceleration
    turn_phase_derivative = 1 + 4 * turn_derivative
    direct = height * (2 * phase_velocity - acceleration / 2)
    via_turn_phase = -height * acceleration * turn_phase_derivative / 2
    via_apocenter_section = 2 * height * (phase_velocity - acceleration / 4)
    return tuple(sp.simplify(value) for value in (direct, via_turn_phase, via_apocenter_section))


def restricted_transverse_linearization() -> tuple[sp.Expr, sp.Expr]:
    """Linearize the restricted outer x-force in outer and binary tilts."""
    r, z, outer_tilt, binary_tilt = sp.symbols("r z xi eta", real=True)
    plus_squared = (outer_tilt + r / 2) ** 2 + (z + binary_tilt / 2) ** 2
    minus_squared = (outer_tilt - r / 2) ** 2 + (z - binary_tilt / 2) ** 2
    force = -(
        (outer_tilt + r / 2) / plus_squared ** sp.Rational(3, 2)
        + (outer_tilt - r / 2) / minus_squared ** sp.Rational(3, 2)
    )
    origin = {outer_tilt: 0, binary_tilt: 0}
    return (
        sp.simplify(sp.diff(force, outer_tilt).subs(origin)),
        sp.simplify(sp.diff(force, binary_tilt).subs(origin)),
    )


def transverse_rotation_wronskian_identity() -> tuple[sp.Expr, sp.Expr]:
    """Return ``W'`` for the transverse field relative to the radial mode.

    Here ``p''=c*p`` and ``z''=-2*z/d**3``. The identity is the mechanism
    that turns all late-turn coefficients into one parabolic scattering
    invariant.
    """
    r, z, p = sp.symbols("r z p", real=True)
    radius_squared = z**2 + r**2 / 4
    coefficient = (r**2 - 2 * z**2) / radius_squared ** sp.Rational(5, 2)
    wronskian_derivative = sp.simplify(
        z * coefficient * p - (-2 * z / radius_squared ** sp.Rational(3, 2)) * p
    )
    expected = 3 * r**2 * z * p / (2 * radius_squared ** sp.Rational(5, 2))
    return wronskian_derivative, expected


def second_encounter_endpoint_scattering() -> tuple[sp.Matrix, sp.Expr, sp.Matrix, sp.Expr]:
    """Return the even-potential scattering matrix and returned endpoint W.

    Both Jost bases are oriented by ``W(R, S) = -1``.  If the incoming
    rotation Jost field has outgoing coefficients ``(gamma, -W)``, time
    reversal and determinant one force the displayed connection matrix.
    The returned outer field has incoming coefficients ``(-gamma, W)``.
    """
    gamma, scattering_wronskian = sp.symbols("gamma W", real=True, nonzero=True)
    connection = sp.Matrix(
        [
            [gamma, (1 - gamma**2) / scattering_wronskian],
            [-scattering_wronskian, gamma],
        ]
    )
    returned_incoming = sp.Matrix([-gamma, scattering_wronskian])
    returned_outgoing = sp.simplify(connection * returned_incoming)
    outgoing_wronskian = sp.simplify(-returned_outgoing[1])
    return connection, sp.simplify(connection.det()), returned_outgoing, outgoing_wronskian


def restricted_equilateral_triple_collision() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, tuple[sp.Expr, sp.Expr]
]:
    """Return residuals and transverse indicial data at restricted triple collision."""
    collision_time = sp.symbols("s", positive=True)
    binary_scale = sp.real_root(9, 3)
    outer_scale = sp.sqrt(3) * binary_scale / 2
    separation = binary_scale * collision_time ** sp.Rational(2, 3)
    height = -outer_scale * collision_time ** sp.Rational(2, 3)
    radius_squared = height**2 + separation**2 / 4
    binary_residual = sp.simplify(
        sp.diff(separation, collision_time, 2) + 2 / separation**2
    )
    outer_residual = sp.simplify(
        sp.diff(height, collision_time, 2)
        + 2 * height / radius_squared ** sp.Rational(3, 2)
    )
    transverse_coefficient = sp.simplify(
        collision_time**2
        * (separation**2 - 2 * height**2)
        / radius_squared ** sp.Rational(5, 2)
    )
    exponents = (
        (3 - sp.sqrt(7)) / 6,
        (3 + sp.sqrt(7)) / 6,
    )
    return binary_residual, outer_residual, transverse_coefficient, exponents


def restricted_triple_collision_phase_mode() -> tuple[sp.Expr, sp.Expr, sp.Expr]:
    """Return the forced collision-time mode about the equilateral ray."""
    collision_time = sp.symbols("s", positive=True)
    binary_scale = sp.real_root(9, 3)
    outer_scale = sp.sqrt(3) * binary_scale / 2
    separation = binary_scale * collision_time ** sp.Rational(2, 3)
    height = -outer_scale * collision_time ** sp.Rational(2, 3)
    radius_squared = height**2 + separation**2 / 4
    longitudinal_coefficient = sp.simplify(
        collision_time**2
        * (4 * height**2 - separation**2 / 2)
        / radius_squared ** sp.Rational(5, 2)
    )
    collision_shift = sp.diff(
        binary_scale
        * (collision_time + sp.symbols("epsilon")) ** sp.Rational(2, 3),
        sp.symbols("epsilon"),
    ).subs(sp.symbols("epsilon"), 0)
    binary_forcing_coefficient = 3 * height * separation / (
        2 * radius_squared ** sp.Rational(5, 2)
    )
    forcing = sp.simplify(binary_forcing_coefficient * collision_shift)
    particular = (
        -sp.sqrt(3)
        * binary_scale
        * collision_time ** (-sp.Rational(1, 3))
        / 3
    )
    residual = sp.simplify(
        sp.diff(particular, collision_time, 2)
        - longitudinal_coefficient * particular / collision_time**2
        - forcing
    )
    return longitudinal_coefficient, forcing, residual


def restricted_triple_collision_shape_spectrum() -> tuple[
    sp.Expr, sp.Expr, tuple[sp.Expr, sp.Expr]
]:
    """Return fixed-point and linear data in the triple-collision shape chart."""
    shape = sp.symbols("y", real=True)
    equilateral_shape = -sp.sqrt(3) / 2
    shape_force = (
        sp.Rational(2, 9)
        * shape
        * ((shape**2 + sp.Rational(1, 4)) ** (-sp.Rational(3, 2)) - 1)
    )
    fixed_residual = sp.simplify(shape_force.subs(shape, equilateral_shape))
    linear_coefficient = sp.simplify(
        sp.diff(shape_force, shape).subs(shape, equilateral_shape)
    )
    eigenvalues = (
        (1 - sp.sqrt(19)) / 6,
        (1 + sp.sqrt(19)) / 6,
    )
    return fixed_residual, linear_coefficient, eigenvalues


def restricted_triple_collision_shape_energy() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, sp.Expr
]:
    """Return the anti-damped shape-energy identity and endpoint potentials."""
    shape, shape_velocity = sp.symbols("y y_tau", real=True)
    shape_force = (
        sp.Rational(2, 9)
        * shape
        * ((shape**2 + sp.Rational(1, 4)) ** (-sp.Rational(3, 2)) - 1)
    )
    potential = (
        -sp.Rational(2, 9) / sp.sqrt(shape**2 + sp.Rational(1, 4))
        - shape**2 / 9
    )
    shape_acceleration = shape_velocity / 3 - shape_force
    energy_derivative = sp.simplify(
        shape_velocity * shape_acceleration
        + sp.diff(potential, shape) * shape_velocity
    )
    equilateral_value = sp.simplify(potential.subs(shape, -sp.sqrt(3) / 2))
    center_value = sp.simplify(potential.subs(shape, 0))
    return energy_derivative, shape_velocity**2 / 3, equilateral_value, center_value


def restricted_triple_collision_slow_field_barrier() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, sp.Expr, sp.Expr
]:
    """Return exact constants in the incoming slow-field Riccati barrier."""
    shape = sp.symbols("y", real=True)
    equilateral_shape = -sp.sqrt(3) / 2
    transverse_coefficient = (1 - 2 * shape**2) / (
        9 * (shape**2 + sp.Rational(1, 4)) ** sp.Rational(5, 2)
    )
    alpha_minus = (3 - sp.sqrt(7)) / 6
    shape_eigenvalue = (1 + sp.sqrt(19)) / 6
    barrier_slope = sp.Rational(7, 100)
    tangent_slope = sp.simplify(
        sp.diff(transverse_coefficient, shape).subs(shape, equilateral_shape)
    )
    unstable_riccati_slope = sp.simplify(
        tangent_slope / (shape_eigenvalue + 1 - 2 * alpha_minus)
    )
    barrier_margin = sp.simplify(
        tangent_slope
        - 2 * barrier_slope * (1 - alpha_minus)
        - barrier_slope**2 * sp.sqrt(3) / 2
    )
    center_lower = sp.simplify(
        -alpha_minus + barrier_slope * sp.sqrt(3) / 2
    )
    return (
        sp.simplify(transverse_coefficient.subs(shape, equilateral_shape)),
        tangent_slope,
        unstable_riccati_slope - barrier_slope,
        barrier_margin,
        center_lower,
    )


def restricted_terminal_collision_r_chart() -> tuple[
    sp.Expr,
    sp.Expr,
    sp.Expr,
    sp.Expr,
    tuple[sp.Expr, sp.Expr],
    sp.Expr,
    tuple[sp.Expr, sp.Expr],
]:
    """Return exact Fuchsian data using binary separation as final-infall time."""
    radius = sp.symbols("r", positive=True, real=True)
    shape = sp.symbols("y", real=True)
    shape_first, shape_second = sp.symbols("y_r y_rr", real=True)
    transverse, transverse_first, transverse_second = sp.symbols(
        "p p_r p_rr", real=True
    )
    equilateral_shape = -sp.sqrt(3) / 2
    shape_force = shape * (
        (shape**2 + sp.Rational(1, 4)) ** (-sp.Rational(3, 2)) - 1
    )
    shape_equation = (
        2 * radius**2 * (1 - radius) * shape_second
        + radius * (3 - 4 * radius) * shape_first
        + shape_force
    )
    shape_residual = sp.simplify(shape_force.subs(shape, equilateral_shape))
    shape_linear_coefficient = sp.simplify(
        sp.diff(shape_force, shape).subs(shape, equilateral_shape)
    )
    shape_exponents = (
        (-1 - sp.sqrt(19)) / 4,
        (-1 + sp.sqrt(19)) / 4,
    )
    raw_transverse_coefficient = (1 - 2 * shape**2) / (
        shape**2 + sp.Rational(1, 4)
    ) ** sp.Rational(5, 2)
    transverse_equation = (
        2 * radius**2 * (1 - radius) * transverse_second
        - radius * transverse_first
        - raw_transverse_coefficient * transverse / 2
    )
    transverse_coefficient = sp.simplify(
        raw_transverse_coefficient.subs(shape, equilateral_shape)
    )
    transverse_exponents = (
        (3 - sp.sqrt(7)) / 4,
        (3 + sp.sqrt(7)) / 4,
    )
    return (
        shape_equation,
        transverse_equation,
        shape_residual,
        shape_linear_coefficient,
        shape_exponents,
        transverse_coefficient,
        transverse_exponents,
    )


def triple_endpoint_matching_determinant() -> tuple[sp.Expr, sp.Expr]:
    """Return the collision-mode Wronskian and block shooting determinant.

    The collision modes are normalized by ``P_± ~ r**beta_±``.  The first
    factor of the full four-dimensional determinant is the oriented base
    intersection determinant ``D_base``.
    """
    radius = sp.symbols("r", positive=True, real=True)
    base_determinant = sp.symbols("D_base", nonzero=True, real=True)
    beta_minus = (3 - sp.sqrt(7)) / 4
    beta_plus = (3 + sp.sqrt(7)) / 4
    radial_speed = -2 * sp.sqrt((1 - radius) / radius)
    mode_minus = radius**beta_minus
    mode_plus = radius**beta_plus
    velocity_minus = sp.diff(mode_minus, radius) * radial_speed
    velocity_plus = sp.diff(mode_plus, radius) * radial_speed
    wronskian_limit = sp.simplify(
        sp.limit(
            mode_minus * velocity_plus - velocity_minus * mode_plus,
            radius,
            0,
            dir="+",
        )
    )
    return wronskian_limit, sp.simplify(base_determinant * wronskian_limit)


def triple_endpoint_fast_frobenius_corrections() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, sp.Expr
]:
    """First two corrections of the canonical fast collision mode."""
    amplitude = sp.symbols("a", real=True)
    shape_exponent = (-1 + sp.sqrt(19)) / 4
    beta_minus = (3 - sp.sqrt(7)) / 4
    beta_plus = (3 + sp.sqrt(7)) / 4
    def indicial(exponent: sp.Expr) -> sp.Expr:
        return sp.expand(2 * (exponent - beta_minus) * (exponent - beta_plus))
    shape_forcing = 3 * sp.sqrt(3) * amplitude / 8
    shape_correction = sp.simplify(
        shape_forcing / indicial(beta_plus + shape_exponent)
    )
    radius_forcing = beta_plus - sp.Rational(1, 4)
    radius_correction = sp.simplify(radius_forcing / indicial(beta_plus + 1))
    return (
        shape_correction,
        radius_correction,
        sp.simplify(indicial(beta_plus + shape_exponent) * shape_correction - shape_forcing),
        sp.simplify(indicial(beta_plus + 1) * radius_correction - radius_forcing),
    )


def triple_endpoint_shifted_fuchsian_identities() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, sp.Expr, sp.Expr
]:
    """Exact shifted equations, Lyapunov identity, and exponent conversions."""
    radius, center_radius, xi = sp.symbols("r rho xi", positive=True)
    shape, shape_x, shape_xx = sp.symbols("y y_x y_xx", real=True)
    fiber, fiber_x, fiber_xx = sp.symbols("p p_x p_xx", real=True)
    defect = shape * ((shape**2 + sp.Rational(1, 4)) ** sp.Rational(-3, 2) - 1)
    tidal = (1 - 2 * shape**2) / (shape**2 + sp.Rational(1, 4)) ** sp.Rational(5, 2)
    shifted_radius = center_radius * sp.exp(-xi)
    shape_equation = (
        2 * (1 - shifted_radius) * shape_xx
        + (-1 + 2 * shifted_radius) * shape_x
        + defect
    )
    fiber_equation = (
        2 * (1 - shifted_radius) * fiber_xx
        + (3 - 2 * shifted_radius) * fiber_x
        - tidal * fiber / 2
    )
    # Along the shape equation, d[(1-r)y_x^2+Integral(defect,y)]/dx.
    energy_derivative = sp.simplify(
        shifted_radius * shape_x**2
        + 2 * (1 - shifted_radius) * shape_x * shape_xx
        + defect * shape_x
    ).subs(
        shape_xx,
        ((1 - 2 * shifted_radius) * shape_x - defect)
        / (2 * (1 - shifted_radius)),
    )
    alpha_minus = (3 - sp.sqrt(7)) / 6
    beta_minus = (3 - sp.sqrt(7)) / 4
    exponent_conversion = sp.simplify(2 * beta_minus / 3 - alpha_minus)
    endpoint_power = sp.simplify(alpha_minus - sp.Rational(1, 3))
    return (
        shape_equation,
        fiber_equation,
        sp.simplify(energy_derivative),
        exponent_conversion,
        endpoint_power,
    )


def triple_endpoint_force_monotonicity_identity() -> tuple[sp.Expr, sp.Expr]:
    """Derivative of the reversed scalar force and its cone numerator."""
    height, radius = sp.symbols("Z r", positive=True)
    force = -2 * height / (height**2 + radius**2 / 4) ** sp.Rational(3, 2)
    derivative = sp.factor(sp.diff(force, height))
    cone_formula = (4 * height**2 - radius**2 / 2) / (
        height**2 + radius**2 / 4
    ) ** sp.Rational(5, 2)
    return derivative, sp.simplify(derivative - cone_formula)


def triple_endpoint_finite_mass_exponents() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, sp.Expr
]:
    """Shape-selection and transverse-size exponents in the finite-mass wedge."""
    shape_unstable = (1 + sp.sqrt(19)) / 4
    transverse_slow = (3 - sp.sqrt(7)) / 6
    shape_gap_power = sp.simplify(2 * shape_unstable / 3)
    transverse_ratio_power = sp.simplify(sp.Rational(2, 3) - transverse_slow)
    return (
        shape_gap_power,
        transverse_ratio_power,
        sp.simplify(shape_gap_power - (1 + sp.sqrt(19)) / 6),
        sp.simplify(transverse_ratio_power - (1 + sp.sqrt(7)) / 6),
    )


def triple_endpoint_mcgehee_shape_exponents() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, sp.Expr, sp.Expr, sp.Expr
]:
    """Reduced log-size exponents and the Euclidean Sundman clock factor."""
    shape_stable = (sp.sqrt(19) - 1) / 4
    shape_unstable = (sp.sqrt(19) + 1) / 4
    fiber_slow = (3 - sp.sqrt(7)) / 4
    fiber_fast = (3 + sp.sqrt(7)) / 4
    euclidean_ray_factor = sp.sqrt(7) / 2
    sundman_radial_speed = -2 * euclidean_ray_factor ** sp.Rational(3, 2)
    transverse_unstable = sp.simplify(1 - fiber_slow)
    transverse_stable = sp.simplify(1 - fiber_fast)
    return (
        sundman_radial_speed,
        -shape_stable,
        shape_unstable,
        transverse_unstable,
        transverse_stable,
        sp.simplify(sp.Rational(2, 3) * transverse_unstable),
    )


def restricted_universal_binary_lc_system() -> tuple[
    sp.Matrix, tuple[sp.Symbol, ...]
]:
    """Return the universal triple-endpoint field in binary LC coordinate."""
    lc = sp.symbols("lambda", real=True)
    height, velocity, transverse, transverse_velocity = sp.symbols(
        "Z V P Q", real=True
    )
    binary_scale = sp.real_root(9, 3)
    separation = binary_scale * lc**2
    radius_squared = height**2 + separation**2 / 4
    time_jacobian = -3 * lc**2
    field = sp.Matrix(
        [
            time_jacobian * velocity,
            time_jacobian
            * (-2 * height / radius_squared ** sp.Rational(3, 2)),
            time_jacobian * transverse_velocity,
            time_jacobian
            * (separation**2 - 2 * height**2)
            * transverse
            / radius_squared ** sp.Rational(5, 2),
        ]
    )
    return field, (lc, height, velocity, transverse, transverse_velocity)


def restricted_universal_binary_mu_system() -> tuple[
    sp.Matrix, tuple[sp.Symbol, ...]
]:
    """Return the dimensionless increasing-time field used by the verifier."""
    lc = sp.symbols("lambda", real=True)
    height, velocity, transverse, transverse_velocity = sp.symbols(
        "Y U P Q", real=True
    )
    radius_squared = height**2 + lc**4 / 4
    field = sp.Matrix(
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
    return field, (lc, height, velocity, transverse, transverse_velocity)


def incoming_tilt_forcing_identity() -> tuple[sp.Expr, sp.Expr]:
    """Return the equation source for ``h=xi+z/2`` on the incoming tail."""
    r, z = sp.symbols("r z", real=True)
    radius_squared = z**2 + r**2 / 4
    coefficient = (r**2 - 2 * z**2) / radius_squared ** sp.Rational(5, 2)
    z_acceleration = -2 * z / radius_squared ** sp.Rational(3, 2)
    source = sp.simplify(z_acceleration / 2 - coefficient * z / 2)
    expected = -3 * r**2 * z / (4 * radius_squared ** sp.Rational(5, 2))
    return source, expected


def binary_tidal_transverse_first_variation() -> tuple[sp.Expr, sp.Expr]:
    """First transverse term of the late binary tidal difference.

    The full binary equation has one additional exterior factor ``B``. Thus
    this coefficient proves that its transverse forcing is quadratic in the
    skinny parameter before division by ``B``.
    """
    epsilon = sp.symbols("epsilon", real=True)
    r, z, outer_tilt, binary_tilt = sp.symbols("r z U eta", real=True)
    minus = sp.Matrix([epsilon * outer_tilt - r / 2, z - epsilon * binary_tilt / 2])
    plus = sp.Matrix([epsilon * outer_tilt + r / 2, z + epsilon * binary_tilt / 2])

    def vertical_force(vector: sp.Matrix) -> sp.Expr:
        return vector[1] / vector.dot(vector) ** sp.Rational(3, 2)

    coefficient = sp.simplify(
        sp.diff(vertical_force(minus) - vertical_force(plus), epsilon).subs(epsilon, 0)
    )
    radius_squared = z**2 + r**2 / 4
    expected = (
        3 * r * z * outer_tilt + (2 * z**2 - r**2 / 4) * binary_tilt
    ) / radius_squared ** sp.Rational(5, 2)
    return coefficient, expected
