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


def triple_endpoint_joint_blowup_algebra() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, sp.Expr, sp.Expr, sp.Expr
]:
    """Return the two-mode projective exponents and equilateral odd offset."""
    skinny = sp.symbols("B", positive=True)
    heavy = sp.sqrt(1 - skinny**2)
    total_heavy = 1 + heavy
    longitudinal = (1 + sp.sqrt(19)) / 4
    transverse = (1 + sp.sqrt(7)) / 4
    ratio = sp.simplify(longitudinal / transverse)
    equilateral_odd_offset = sp.simplify(-skinny**2 / (2 * total_heavy**2))
    return (
        longitudinal,
        transverse,
        ratio,
        sp.simplify(ratio - 1),
        sp.simplify(2 - ratio),
        equilateral_odd_offset,
    )


def planar_joint_shape_identities() -> tuple[
    sp.Matrix, sp.Matrix, sp.Expr, sp.Expr, sp.Expr, sp.Expr, sp.Expr
]:
    """Exact damped-gradient and torque data for the planar joint limit."""
    horizontal, vertical = sp.symbols("x y", real=True)
    horizontal_velocity, vertical_velocity = sp.symbols("x_dot y_dot", real=True)
    plus_squared = (horizontal + sp.Rational(1, 2)) ** 2 + vertical**2
    minus_squared = (horizontal - sp.Rational(1, 2)) ** 2 + vertical**2
    potential = (
        horizontal**2
        + vertical**2
        + plus_squared ** -sp.Rational(1, 2)
        + minus_squared ** -sp.Rational(1, 2)
    ) / 9
    coordinates = sp.Matrix([horizontal, vertical])
    gradient = sp.Matrix([sp.diff(potential, coordinate) for coordinate in coordinates])
    equilateral = {horizontal: 0, vertical: sp.sqrt(3) / 2}
    rest_gradient = sp.simplify(gradient.subs(equilateral))
    rest_hessian = sp.simplify(gradient.jacobian(coordinates).subs(equilateral))
    rest_potential = sp.simplify(potential.subs(equilateral))
    velocity = sp.Matrix([horizontal_velocity, vertical_velocity])
    energy_derivative = sp.simplify(
        velocity.dot(gradient - velocity / 3) - gradient.dot(velocity)
    )
    torque = sp.simplify(horizontal * gradient[1] - vertical * gradient[0])
    expected_torque = sp.simplify(
        vertical
        / 18
        * (
            plus_squared ** -sp.Rational(3, 2)
            - minus_squared ** -sp.Rational(3, 2)
        )
    )
    convexity_constant = sp.simplify(
        (sp.Rational(7, 4) - 8 / (3 * sp.sqrt(3))) / 9
    )
    distance = sp.symbols("d", positive=True)
    distance_lower_bound_residual = sp.factor(
        distance**2 / 2
        + 1 / distance
        - sp.Rational(3, 2)
        - (distance - 1) ** 2 * (distance + 2) / (2 * distance)
    )
    return (
        rest_gradient,
        rest_hessian,
        rest_potential,
        energy_derivative,
        sp.simplify(torque - expected_torque),
        convexity_constant,
        distance_lower_bound_residual,
    )


def planar_joint_shape_quadratic_bending() -> tuple[
    sp.Expr, sp.Expr, sp.Expr, sp.Expr
]:
    """Quadratic inward bending of the zero-projective planar shape orbit."""
    transverse_rate = (1 + sp.sqrt(7)) / 6
    longitudinal_rate = (1 + sp.sqrt(19)) / 6
    transverse_source = sp.sqrt(3) / 24
    divisor = sp.simplify(
        4 * transverse_rate**2
        - 2 * transverse_rate / 3
        - sp.Rational(1, 2)
    )
    bending = sp.radsimp(transverse_source / divisor)
    return (
        transverse_source,
        divisor,
        bending,
        sp.simplify(2 * transverse_rate - longitudinal_rate),
    )


def planar_joint_shape_stable_cubic_jet() -> tuple[
    tuple[sp.Expr, ...], tuple[sp.Expr, sp.Expr]
]:
    """Exact total-degree-three stable-manifold jet at the lower rest point.

    The coefficient order is ``(A, K, D, B, C, E, F)`` in

    ``x=p+A*p*h+B*p**3+C*p*h**2`` and
    ``q=h+K*p**2+D*h**2+E*p**2*h+F*h**3``.
    """
    transverse, longitudinal, bookkeeping = sp.symbols("p h epsilon", real=True)
    transverse_rate = (1 + sp.sqrt(7)) / 6
    longitudinal_rate = (1 + sp.sqrt(19)) / 6
    mixed_horizontal = (
        -5 * sp.sqrt(21)
        - sp.sqrt(399)
        + 12 * sp.sqrt(3)
        + 3 * sp.sqrt(57)
    ) / 6
    bending = (2 * sp.sqrt(21) - 5 * sp.sqrt(3)) / 4
    longitudinal_quadratic = (-2 * sp.sqrt(57) + 29 * sp.sqrt(3)) / 340
    transverse_cubic = -sp.Rational(67, 108) + 43 * sp.sqrt(7) / 216
    transverse_longitudinal_squared = (
        (-2819 * sp.sqrt(133) - 2314 * sp.sqrt(19) + 2498 * sp.sqrt(7))
        / 31620
        + sp.Rational(83681, 63240)
    )
    squared_transverse_longitudinal = (
        -sp.Rational(337, 248)
        + (6 * sp.sqrt(7) + 14 * sp.sqrt(19) + 11 * sp.sqrt(133)) / 124
    )
    longitudinal_cubic = sp.Rational(121, 5100) - 29 * sp.sqrt(19) / 10200
    horizontal = (
        transverse
        + mixed_horizontal * transverse * longitudinal
        + transverse_cubic * transverse**3
        + transverse_longitudinal_squared * transverse * longitudinal**2
    )
    vertical_offset = (
        longitudinal
        + bending * transverse**2
        + longitudinal_quadratic * longitudinal**2
        + squared_transverse_longitudinal * transverse**2 * longitudinal
        + longitudinal_cubic * longitudinal**3
    )
    vertical = -sp.sqrt(3) / 2 + vertical_offset

    def tail_derivative(expression: sp.Expr) -> sp.Expr:
        return sp.expand(
            -transverse_rate * transverse * sp.diff(expression, transverse)
            - longitudinal_rate * longitudinal * sp.diff(expression, longitudinal)
        )

    plus_squared = (horizontal + sp.Rational(1, 2)) ** 2 + vertical**2
    minus_squared = (horizontal - sp.Rational(1, 2)) ** 2 + vertical**2
    horizontal_force = (
        2 * horizontal
        - (horizontal + sp.Rational(1, 2)) / plus_squared ** sp.Rational(3, 2)
        - (horizontal - sp.Rational(1, 2)) / minus_squared ** sp.Rational(3, 2)
    ) / 9
    vertical_force = (
        2 * vertical
        - vertical / plus_squared ** sp.Rational(3, 2)
        - vertical / minus_squared ** sp.Rational(3, 2)
    ) / 9
    horizontal_residual = (
        tail_derivative(tail_derivative(horizontal))
        + tail_derivative(horizontal) / 3
        - horizontal_force
    )
    vertical_residual = (
        tail_derivative(tail_derivative(vertical_offset))
        + tail_derivative(vertical_offset) / 3
        - vertical_force
    )

    def through_cubic(expression: sp.Expr) -> sp.Expr:
        scaled = expression.subs(
            {
                transverse: bookkeeping * transverse,
                longitudinal: bookkeeping * longitudinal,
            }
        )
        return sp.simplify(
            sp.series(scaled, bookkeeping, 0, 4).removeO().expand()
        )

    coefficients = (
        mixed_horizontal,
        bending,
        longitudinal_quadratic,
        transverse_cubic,
        transverse_longitudinal_squared,
        squared_transverse_longitudinal,
        longitudinal_cubic,
    )
    return coefficients, (
        through_cubic(horizontal_residual),
        through_cubic(vertical_residual),
    )


def planar_joint_shape_stable_quartic_correction() -> tuple[
    tuple[sp.Expr, ...], tuple[sp.Expr, sp.Expr], tuple[sp.Expr, sp.Expr]
]:
    """Exact degree-four correction to the lower stable-manifold jet.

    The coefficient order is ``(G, H, I, J, L)`` for the monomials
    ``(p**3*h, p*h**3, p**4, p**2*h**2, h**4)``.
    """
    cubic, _ = planar_joint_shape_stable_cubic_jet()
    (
        mixed,
        bending,
        long_squared,
        trans_cubic,
        trans_long_squared,
        trans_squared_long,
        long_cubic,
    ) = cubic
    transverse, longitudinal, bookkeeping = sp.symbols("p h epsilon", real=True)
    transverse_rate = (1 + sp.sqrt(7)) / 6
    longitudinal_rate = (1 + sp.sqrt(19)) / 6
    trans_cubic_long = (
        -93651910 * sp.sqrt(399)
        - 392572319 * sp.sqrt(21)
        + 1018625929 * sp.sqrt(3)
        + 250916714 * sp.sqrt(57)
    ) / 45037296
    trans_long_cubic = (
        -386571066 * sp.sqrt(399)
        - 833244582 * sp.sqrt(21)
        + 312559697 * sp.sqrt(57)
        + 6447516829 * sp.sqrt(3)
    ) / 8038436400
    trans_quartic = (-3671 * sp.sqrt(3) + 187 * sp.sqrt(21)) / 76464
    trans_squared_long_squared = (
        -1022448154 * sp.sqrt(21)
        - 213073373 * sp.sqrt(399)
        + 2563820254 * sp.sqrt(3)
        + 612798518 * sp.sqrt(57)
    ) / 267947880
    long_quartic = (-4307297 * sp.sqrt(3) + 308435 * sp.sqrt(57)) / 242413200
    horizontal = (
        transverse
        + mixed * transverse * longitudinal
        + trans_cubic * transverse**3
        + trans_long_squared * transverse * longitudinal**2
        + trans_cubic_long * transverse**3 * longitudinal
        + trans_long_cubic * transverse * longitudinal**3
    )
    vertical_offset = (
        longitudinal
        + bending * transverse**2
        + long_squared * longitudinal**2
        + trans_squared_long * transverse**2 * longitudinal
        + long_cubic * longitudinal**3
        + trans_quartic * transverse**4
        + trans_squared_long_squared * transverse**2 * longitudinal**2
        + long_quartic * longitudinal**4
    )
    vertical = -sp.sqrt(3) / 2 + vertical_offset

    def tail_derivative(expression: sp.Expr) -> sp.Expr:
        return sp.expand(
            -transverse_rate * transverse * sp.diff(expression, transverse)
            - longitudinal_rate * longitudinal * sp.diff(expression, longitudinal)
        )

    plus_squared = (horizontal + sp.Rational(1, 2)) ** 2 + vertical**2
    minus_squared = (horizontal - sp.Rational(1, 2)) ** 2 + vertical**2
    horizontal_force = (
        2 * horizontal
        - (horizontal + sp.Rational(1, 2)) / plus_squared ** sp.Rational(3, 2)
        - (horizontal - sp.Rational(1, 2)) / minus_squared ** sp.Rational(3, 2)
    ) / 9
    vertical_force = (
        2 * vertical
        - vertical / plus_squared ** sp.Rational(3, 2)
        - vertical / minus_squared ** sp.Rational(3, 2)
    ) / 9
    horizontal_residual = (
        tail_derivative(tail_derivative(horizontal))
        + tail_derivative(horizontal) / 3
        - horizontal_force
    )
    vertical_residual = (
        tail_derivative(tail_derivative(vertical_offset))
        + tail_derivative(vertical_offset) / 3
        - vertical_force
    )

    def through_quartic(expression: sp.Expr) -> sp.Expr:
        scaled = expression.subs(
            {
                transverse: bookkeeping * transverse,
                longitudinal: bookkeeping * longitudinal,
            }
        )
        return sp.simplify(
            sp.series(scaled, bookkeeping, 0, 5).removeO().expand()
        )

    def degree_five(expression: sp.Expr) -> sp.Expr:
        scaled = expression.subs(
            {
                transverse: bookkeeping * transverse,
                longitudinal: bookkeeping * longitudinal,
            }
        )
        return sp.factor(
            sp.series(scaled, bookkeeping, 0, 6)
            .removeO()
            .expand()
            .coeff(bookkeeping, 5)
        )

    corrections = (
        trans_cubic_long,
        trans_long_cubic,
        trans_quartic,
        trans_squared_long_squared,
        long_quartic,
    )
    return (
        corrections,
        (
            through_quartic(horizontal_residual),
            through_quartic(vertical_residual),
        ),
        (
            degree_five(horizontal_residual),
            degree_five(vertical_residual),
        ),
    )


def forced_planar_light_collision_lc_constraint() -> tuple[
    sp.Matrix, sp.Expr, sp.Expr, sp.Expr
]:
    """Forced planar LC field, constraint, and collision-clock cubic."""
    u_real, u_imag, v_real, v_imag, energy = sp.symbols(
        "u_r u_i v_r v_i h", real=True
    )
    force_real, force_imag = sp.symbols("G_r G_i", real=True)
    radius_squared = u_real**2 + u_imag**2
    conjugate_u_times_force_real = u_real * force_real + u_imag * force_imag
    conjugate_u_times_force_imag = u_real * force_imag - u_imag * force_real
    u_times_v_real = u_real * v_real - u_imag * v_imag
    u_times_v_imag = u_real * v_imag + u_imag * v_real
    energy_derivative = 2 * (
        u_times_v_real * force_real + u_times_v_imag * force_imag
    )
    field = sp.Matrix(
        [
            v_real,
            v_imag,
            energy * u_real / 2
            + radius_squared * conjugate_u_times_force_real / 2,
            energy * u_imag / 2
            + radius_squared * conjugate_u_times_force_imag / 2,
            energy_derivative,
            radius_squared,
        ]
    )
    constraint = (
        2 * (v_real**2 + v_imag**2) - 1 - energy * radius_squared
    )
    variables = (u_real, u_imag, v_real, v_imag, energy)
    constraint_derivative = sp.simplify(
        sum(
            sp.diff(constraint, variable) * field[index]
            for index, variable in enumerate(variables)
        )
    )
    collision_speed_gap = sp.simplify(
        constraint.subs({u_real: 0, u_imag: 0})
        - (2 * (v_real**2 + v_imag**2) - 1)
    )
    clock_second_derivative = 2 * (u_real * v_real + u_imag * v_imag)
    clock_third_derivative = sp.simplify(
        sum(
            sp.diff(clock_second_derivative, variable) * field[index]
            for index, variable in enumerate(variables)
        )
    )
    collision_clock_cubic_gap = sp.simplify(
        clock_third_derivative.subs({u_real: 0, u_imag: 0})
        - 2 * (v_real**2 + v_imag**2)
    )
    return (
        field,
        constraint_derivative,
        collision_speed_gap,
        collision_clock_cubic_gap,
    )


def finite_mass_selected_collision_reduction() -> tuple[
    sp.Matrix, sp.Matrix, sp.Expr, sp.Expr
]:
    """Selected light--heavy equation and finite-mass LC invariants.

    The late Jacobi variables have ``A=sqrt(1-B**2)`` and ``M=1+A``.
    For ``q=Z-A*R/M``, the returned vector residual verifies

    ``q''=-(1+B) Phi(q)+A(Phi(R)-Phi(q+R))``.

    The second vector residual verifies cancellation of the singular pair
    force in ``Q=R+B*q/(1+B)``. The remaining two entries verify preservation
    of the forced-Kepler LC constraint and its collision-speed normalization.
    """
    skinny, heavy = sp.symbols("B A", real=True)
    total_heavy = 1 + heavy
    force_r_x, force_r_y = sp.symbols("F_Rx F_Ry", real=True)
    force_q_x, force_q_y = sp.symbols("F_qx F_qy", real=True)
    force_o_x, force_o_y = sp.symbols("F_ox F_oy", real=True)
    force_r = sp.Matrix([force_r_x, force_r_y])
    force_q = sp.Matrix([force_q_x, force_q_y])
    force_other = sp.Matrix([force_o_x, force_o_y])
    binary_acceleration = (
        -total_heavy * force_r
        + skinny * (force_q - force_other)
    )
    outer_acceleration = -(
        (total_heavy + skinny)
        / total_heavy
        * (heavy * force_other + force_q)
    )
    relative_acceleration = sp.simplify(
        outer_acceleration - heavy * binary_acceleration / total_heavy
    )
    expected = -(1 + skinny) * force_q + heavy * (force_r - force_other)
    equation_residual = sp.simplify(relative_acceleration - expected)
    collision_pair_center_acceleration = sp.simplify(
        binary_acceleration
        + skinny * relative_acceleration / (1 + skinny)
    )
    expected_pair_center_acceleration = -(
        (total_heavy + skinny)
        / (1 + skinny)
        * (force_r + skinny * force_other)
    )
    pair_center_residual = sp.simplify(
        collision_pair_center_acceleration - expected_pair_center_acceleration
    )

    u_real, u_imag, v_real, v_imag, energy = sp.symbols(
        "u_r u_i v_r v_i h", real=True
    )
    force_real, force_imag = sp.symbols("G_r G_i", real=True)
    radius_squared = u_real**2 + u_imag**2
    conjugate_u_times_force_real = u_real * force_real + u_imag * force_imag
    conjugate_u_times_force_imag = u_real * force_imag - u_imag * force_real
    u_times_v_real = u_real * v_real - u_imag * v_imag
    u_times_v_imag = u_real * v_imag + u_imag * v_real
    field = sp.Matrix(
        [
            v_real,
            v_imag,
            energy * u_real / 2
            + radius_squared * conjugate_u_times_force_real / 2,
            energy * u_imag / 2
            + radius_squared * conjugate_u_times_force_imag / 2,
            2 * (u_times_v_real * force_real + u_times_v_imag * force_imag),
        ]
    )
    gravitational_parameter = 1 + skinny
    constraint = (
        2 * (v_real**2 + v_imag**2)
        - gravitational_parameter
        - energy * radius_squared
    )
    variables = (u_real, u_imag, v_real, v_imag, energy)
    constraint_derivative = sp.simplify(
        sum(
            sp.diff(constraint, variable) * field[index]
            for index, variable in enumerate(variables)
        )
    )
    collision_speed_gap = sp.simplify(
        constraint.subs({u_real: 0, u_imag: 0})
        - (2 * (v_real**2 + v_imag**2) - gravitational_parameter)
    )
    return (
        equation_residual,
        pair_center_residual,
        constraint_derivative,
        collision_speed_gap,
    )


def forced_planar_lc_angular_identity() -> tuple[sp.Expr, sp.Expr]:
    """LC expression for relative angular momentum and its impact derivative."""
    u_real, u_imag, v_real, v_imag = sp.symbols(
        "u_r u_i v_r v_i", real=True
    )
    u_parameter_real, u_parameter_imag = sp.symbols(
        "u_k_r u_k_i", real=True
    )
    v_parameter_real, v_parameter_imag = sp.symbols(
        "v_k_r v_k_i", real=True
    )
    radius_squared = u_real**2 + u_imag**2
    position_real = u_real**2 - u_imag**2
    position_imag = 2 * u_real * u_imag
    velocity_real = 2 * (v_real * u_real - v_imag * u_imag) / radius_squared
    velocity_imag = 2 * (v_real * u_imag + v_imag * u_real) / radius_squared
    angular_momentum = sp.cancel(
        position_real * velocity_imag - position_imag * velocity_real
    )
    expected = 2 * (u_real * v_imag - u_imag * v_real)
    angular_gap = sp.simplify(angular_momentum - expected)
    parameter_derivative = (
        sp.diff(expected, u_real) * u_parameter_real
        + sp.diff(expected, u_imag) * u_parameter_imag
        + sp.diff(expected, v_real) * v_parameter_real
        + sp.diff(expected, v_imag) * v_parameter_imag
    )
    collision_derivative_gap = sp.simplify(
        parameter_derivative.subs({u_real: 0, u_imag: 0})
        - 2
        * (
            u_parameter_real * v_imag
            - u_parameter_imag * v_real
        )
    )
    return angular_gap, collision_derivative_gap


def tight_binary_brake_hill_threshold() -> tuple[sp.Expr, sp.Expr, sp.Expr]:
    """Exact late-scaled heavy-pair separation required at a skinny brake."""
    skinny = sp.symbols("B", positive=True)
    heavy_squared = 1 - skinny**2
    heavy = sp.sqrt(heavy_squared)
    initial_potential = heavy * skinny + 1 / (heavy * skinny)
    threshold = sp.simplify(heavy / (skinny * initial_potential))
    expected = heavy_squared / (1 + heavy_squared * skinny**2)
    gap = sp.factor(1 - expected)
    return threshold, sp.simplify(threshold - expected), gap


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


def heavy_bridge_negative_lc_switch_identities() -> tuple[sp.Matrix, sp.Matrix]:
    """Exact round trip and forcing at a bridge-to-negative-primary switch."""
    lc, scale = sp.symbols("lambda scale", positive=True)
    u_real, u_imag, outer_vx, outer_vy = sp.symbols(
        "u_r u_i V_x V_y", real=True
    )
    norm = u_real**2 + u_imag**2
    separation = scale * lc**2
    relative_x = u_real**2 - u_imag**2
    relative_y = 2 * u_real * u_imag
    relative_vx = outer_vx + scale / (3 * lc)
    relative_vy = outer_vy
    v_real = (u_real * relative_vx + u_imag * relative_vy) / 2
    v_imag = (u_real * relative_vy - u_imag * relative_vx) / 2
    reconstructed_outer = sp.Matrix(
        [
            relative_x - separation / 2,
            relative_y,
            2 * (u_real * v_real - u_imag * v_imag) / norm
            - scale / (3 * lc),
            2 * (u_real * v_imag + u_imag * v_real) / norm,
        ]
    )
    expected_outer = sp.Matrix(
        [
            relative_x - separation / 2,
            relative_y,
            outer_vx,
            outer_vy,
        ]
    )

    qx, qy, radius = sp.symbols("q_x q_y R", real=True, nonzero=True)
    selected_norm_cubed = (qx**2 + qy**2) ** sp.Rational(3, 2)
    other_norm_cubed = ((qx - radius) ** 2 + qy**2) ** sp.Rational(3, 2)
    outer_acceleration = sp.Matrix(
        [
            -qx / selected_norm_cubed
            - (qx - radius) / other_norm_cubed,
            -qy / selected_norm_cubed - qy / other_norm_cubed,
        ]
    )
    negative_primary_acceleration = sp.Matrix([1 / radius**2, 0])
    selected_kepler = sp.Matrix(
        [-qx / selected_norm_cubed, -qy / selected_norm_cubed]
    )
    forcing = sp.Matrix(
        [
            -1 / radius**2 - (qx - radius) / other_norm_cubed,
            -qy / other_norm_cubed,
        ]
    )
    forcing_gap = sp.simplify(
        outer_acceleration - negative_primary_acceleration
        - selected_kepler - forcing
    )
    return sp.simplify(reconstructed_outer - expected_outer), forcing_gap


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
