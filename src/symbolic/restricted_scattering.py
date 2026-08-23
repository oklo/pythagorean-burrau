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
    expected = (
        separation
        * separation_velocity
        / (2 * radius_squared ** sp.Rational(3, 2))
    )
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
    integrand = (
        (r_velocity**2 + r * r_acceleration) / (2 * radius**3)
        - 3
        * r
        * r_velocity
        * (z * z_velocity + r * r_velocity / 4)
        / (2 * radius**5)
    )
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
            -separation
            * x**4
            / (2 * (1 + separation**2 * x**4 / 16) ** sp.Rational(3, 2)),
        ]
    )
    return field, (psi, x, velocity)


def parabolic_stroboscopic_leading_map() -> tuple[sp.Matrix, sp.Matrix]:
    """Degree-four period-map term before and after the stable-ray shear."""
    x, velocity, transverse = sp.symbols("x velocity transverse", real=True)
    original = sp.Matrix([-sp.pi * x**3 * velocity / 8, -sp.pi * x**4 / 4])
    sheared = sp.expand(
        original.subs(velocity, transverse + sp.sqrt(2) * x)
    )
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
    expected = -coefficient**2 * x**6 * energy
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
    height, acceleration, phase_velocity = sp.symbols(
        "Z a b", real=True, nonzero=True
    )
    turn_derivative = -phase_velocity / acceleration
    turn_phase_derivative = 1 + 4 * turn_derivative
    direct = height * (2 * phase_velocity - acceleration / 2)
    via_turn_phase = -height * acceleration * turn_phase_derivative / 2
    via_apocenter_section = 2 * height * (
        phase_velocity - acceleration / 4
    )
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
        z * coefficient * p
        - (-2 * z / radius_squared ** sp.Rational(3, 2)) * p
    )
    expected = 3 * r**2 * z * p / (2 * radius_squared ** sp.Rational(5, 2))
    return wronskian_derivative, expected


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
    minus = sp.Matrix(
        [epsilon * outer_tilt - r / 2, z - epsilon * binary_tilt / 2]
    )
    plus = sp.Matrix(
        [epsilon * outer_tilt + r / 2, z + epsilon * binary_tilt / 2]
    )

    def vertical_force(vector: sp.Matrix) -> sp.Expr:
        return vector[1] / vector.dot(vector) ** sp.Rational(3, 2)

    coefficient = sp.simplify(
        sp.diff(vertical_force(minus) - vertical_force(plus), epsilon).subs(
            epsilon, 0
        )
    )
    radius_squared = z**2 + r**2 / 4
    expected = (
        3 * r * z * outer_tilt + (2 * z**2 - r**2 / 4) * binary_tilt
    ) / radius_squared ** sp.Rational(5, 2)
    return coefficient, expected
