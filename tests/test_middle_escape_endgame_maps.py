"""Exact tests for the endgame chart-switch maps.

Mirrors the formulas of ``make_pair23_to_pair13_map`` and
``make_pair13_to_pair23_map_form_b`` in
``src/fable/verification/middle_escape_endgame_capd.cpp`` and verifies
them against direct physical reconstruction on arbitrary exact rational
states.

Strategy: the maps factor as (unlift to relative coordinates) -> (exact
linear change of relative frame) -> (Levi--Civita lift).  The two lift
identities are proved symbolically once, in full generality; the frame
changes are rational-linear and are compared exactly against the direct
physical chart, which keeps every comparison in rational arithmetic.
"""

from __future__ import annotations

import sympy as sp

from src.symbolic.middle_escape import mass_A, mass_B

R = sp.Rational

STATES = [
    (
        ((R(-7, 5), R(2, 3)), (R(1, 4), R(-3, 7)), (R(5, 6), R(9, 8))),
        ((R(1, 3), R(-2, 5)), (R(-1, 6), R(4, 9)), (R(3, 8), R(-5, 7))),
    ),
    (
        ((R(11, 9), R(-4, 5)), (R(-2, 7), R(5, 4)), (R(-13, 6), R(1, 10))),
        ((R(-3, 11), R(7, 6)), (R(2, 9), R(-8, 5)), (R(5, 12), R(6, 13))),
    ),
]

U = R(29, 100)


def pair13_chart_of(positions, velocities, u):
    """Direct pair-{1,3} relative data of a physical state."""
    (q1, q2, q3) = positions
    (v1, v2, v3) = velocities
    a = mass_A(u)
    m13 = a + 1
    g = (q3[0] - q1[0], q3[1] - q1[1])
    gdot = (v3[0] - v1[0], v3[1] - v1[1])
    big_g = (
        q2[0] - (a * q1[0] + q3[0]) / m13,
        q2[1] - (a * q1[1] + q3[1]) / m13,
    )
    p = (
        v2[0] - (a * v1[0] + v3[0]) / m13,
        v2[1] - (a * v1[1] + v3[1]) / m13,
    )
    return g, gdot, big_g, p


def pair23_chart_of(positions, velocities, u):
    """Direct pair-{2,3} relative data of a physical state."""
    (q1, q2, q3) = positions
    (v1, v2, v3) = velocities
    b = mass_B(u)
    m23 = b + 1
    g = (q3[0] - q2[0], q3[1] - q2[1])
    gdot = (v3[0] - v2[0], v3[1] - v2[1])
    big_g = (
        q1[0] - (b * q2[0] + q3[0]) / m23,
        q1[1] - (b * q2[1] + q3[1]) / m23,
    )
    p = (
        v1[0] - (b * v2[0] + v3[0]) / m23,
        v1[1] - (b * v2[1] + v3[1]) / m23,
    )
    return g, gdot, big_g, p


def switch_23_to_13_relative(u, g23, g23dot, big_g, p):
    """Rational core of make_pair23_to_pair13_map (before the lift)."""
    a, b = mass_A(u), mass_B(u)
    inv_m23 = 1 / (b + 1)
    inv_m13 = 1 / (a + 1)
    d13 = (big_g[0] + (inv_m23 - 1) * g23[0],
           big_g[1] + (inv_m23 - 1) * g23[1])
    d13dot = (p[0] + (inv_m23 - 1) * g23dot[0],
              p[1] + (inv_m23 - 1) * g23dot[1])
    g13 = (-d13[0], -d13[1])
    g13dot = (-d13dot[0], -d13dot[1])
    d12 = (big_g[0] + inv_m23 * g23[0], big_g[1] + inv_m23 * g23[1])
    d12dot = (p[0] + inv_m23 * g23dot[0], p[1] + inv_m23 * g23dot[1])
    new_g = (-d12[0] - inv_m13 * g13[0], -d12[1] - inv_m13 * g13[1])
    new_p = (-d12dot[0] - inv_m13 * g13dot[0],
             -d12dot[1] - inv_m13 * g13dot[1])
    return g13, g13dot, new_g, new_p


def switch_13_to_23_relative(u, g13, g13dot, big_g, p):
    """Rational core of make_pair13_to_pair23_map_form_b (before the lift)."""
    a, b = mass_A(u), mass_B(u)
    inv_m13 = 1 / (a + 1)
    inv_m23 = 1 / (b + 1)
    x13 = (big_g[0] + inv_m13 * g13[0], big_g[1] + inv_m13 * g13[1])
    x13dot = (p[0] + inv_m13 * g13dot[0], p[1] + inv_m13 * g13dot[1])
    g23 = (g13[0] - x13[0], g13[1] - x13[1])
    g23dot = (g13dot[0] - x13dot[0], g13dot[1] - x13dot[1])
    new_g = (-x13[0] - inv_m23 * g23[0], -x13[1] - inv_m23 * g23[1])
    new_p = (-x13dot[0] - inv_m23 * g23dot[0],
             -x13dot[1] - inv_m23 * g23dot[1])
    return g23, g23dot, new_g, new_p


def _pair_equal(lhs, rhs):
    return all(sp.together(x - y) == 0 for x, y in zip(lhs, rhs, strict=True))


def _norm(pair):
    return sp.sqrt(pair[0] ** 2 + pair[1] ** 2)


def physical_energy(positions, velocities, u):
    """Translation-reduced Newtonian energy of an exact physical state."""
    a, b = mass_A(u), mass_B(u)
    masses = (a, b, sp.Integer(1))
    total = sum(masses)
    vcm = tuple(
        sum(m * velocity[k] for m, velocity in zip(masses, velocities, strict=True))
        / total
        for k in range(2)
    )
    kinetic = sum(
        m
        * sum((velocity[k] - vcm[k]) ** 2 for k in range(2))
        / 2
        for m, velocity in zip(masses, velocities, strict=True)
    )
    potential = sum(
        masses[i]
        * masses[j]
        / _norm(
            (
                positions[j][0] - positions[i][0],
                positions[j][1] - positions[i][1],
            )
        )
        for i, j in ((0, 1), (0, 2), (1, 2))
    )
    return sp.simplify(kinetic - potential)


def pair13_h_from_energy(u, total_energy, big_g_velocity, r12, r23):
    """Smooth target h13 reconstructed from the exact total-energy leaf."""
    a, b = mass_A(u), mass_B(u)
    mu13 = a / (a + 1)
    mu_g = b * (a + 1) / (a + b + 1)
    outer_kinetic = mu_g * sum(value**2 for value in big_g_velocity) / 2
    return sp.simplify(
        (total_energy - outer_kinetic + a * b / r12 + b / r23) / mu13
    )


def pair23_h_from_energy(u, total_energy, big_g_velocity, r12, r13):
    """Smooth target h23 reconstructed from the exact total-energy leaf."""
    a, b = mass_A(u), mass_B(u)
    mu23 = b / (b + 1)
    mu_g = a * (b + 1) / (a + b + 1)
    outer_kinetic = mu_g * sum(value**2 for value in big_g_velocity) / 2
    return sp.simplify(
        (total_energy - outer_kinetic + a * b / r12 + a / r13) / mu23
    )


def _dot(lhs, rhs):
    return sum(x * y for x, y in zip(lhs, rhs, strict=True))


def _cross(lhs, rhs):
    return lhs[0] * rhs[1] - lhs[1] * rhs[0]


def test_switch_23_to_13_rational_core():
    """The switch-back frame change reproduces the direct pair-{1,3} data."""
    for positions, velocities in STATES:
        g23, g23dot, big_g23, p23 = pair23_chart_of(positions, velocities, U)
        g13, g13dot, big_g13, p13 = pair13_chart_of(positions, velocities, U)
        got_g13, got_g13dot, got_g, got_p = switch_23_to_13_relative(
            U, g23, g23dot, big_g23, p23
        )
        assert _pair_equal(got_g13, g13)
        assert _pair_equal(got_g13dot, g13dot)
        assert _pair_equal(got_g, big_g13)
        assert _pair_equal(got_p, p13)


def test_switch_13_to_23_rational_core():
    """The Form-B switch frame change reproduces the pair-{2,3} data."""
    for positions, velocities in STATES:
        g13, g13dot, big_g13, p13 = pair13_chart_of(positions, velocities, U)
        g23, g23dot, big_g23, p23 = pair23_chart_of(positions, velocities, U)
        got_g23, got_g23dot, got_g, got_p = switch_13_to_23_relative(
            U, g13, g13dot, big_g13, p13
        )
        assert _pair_equal(got_g23, g23)
        assert _pair_equal(got_g23dot, g23dot)
        assert _pair_equal(got_g, big_g23)
        assert _pair_equal(got_p, p23)


def test_exchange_sandwich_rational_round_trip():
    """The proposed 13 -> 23 -> 13 sandwich is the identity physically.

    This checks the rational frame changes independently of either
    Levi--Civita square-root branch.  The symbolic lift tests below then show
    that Form B on the outward switch and Form A on the return recover these
    same relative vectors and velocities wherever their denominators are
    nonzero.
    """
    for positions, velocities in STATES:
        g13, g13dot, big_g13, p13 = pair13_chart_of(positions, velocities, U)
        g23, g23dot, big_g23, p23 = switch_13_to_23_relative(
            U, g13, g13dot, big_g13, p13
        )
        back_g13, back_g13dot, back_big_g13, back_p13 = (
            switch_23_to_13_relative(U, g23, g23dot, big_g23, p23)
        )
        assert _pair_equal(back_g13, g13)
        assert _pair_equal(back_g13dot, g13dot)
        assert _pair_equal(back_big_g13, big_g13)
        assert _pair_equal(back_p13, p13)


def test_fixed_energy_h_reconstruction_on_exact_physical_states():
    """Both invariant formulas equal the velocity-defined pair energies."""
    a, b = mass_A(U), mass_B(U)
    for positions, velocities in STATES:
        energy = physical_energy(positions, velocities, U)
        g13, g13dot, _, p13 = pair13_chart_of(positions, velocities, U)
        g23, g23dot, _, p23 = pair23_chart_of(positions, velocities, U)
        r12 = _norm(
            (
                positions[1][0] - positions[0][0],
                positions[1][1] - positions[0][1],
            )
        )
        r13 = _norm(g13)
        r23 = _norm(g23)
        h13_velocity = sum(value**2 for value in g13dot) / 2 - (a + 1) / r13
        h23_velocity = sum(value**2 for value in g23dot) / 2 - (b + 1) / r23
        assert sp.simplify(
            pair13_h_from_energy(U, energy, p13, r12, r23) - h13_velocity
        ) == 0
        assert sp.simplify(
            pair23_h_from_energy(U, energy, p23, r12, r13) - h23_velocity
        ) == 0


def test_pair13_in_chart_energy_projection_distances():
    """The in-chart projection reconstructs exactly the two unselected radii."""
    a = mass_A(U)
    inv_m13 = 1 / (a + 1)
    for positions, velocities in STATES:
        g13, _, big_g13, p13 = pair13_chart_of(positions, velocities, U)
        d12 = (
            big_g13[0] + inv_m13 * g13[0],
            big_g13[1] + inv_m13 * g13[1],
        )
        d23 = (
            big_g13[0] + (inv_m13 - 1) * g13[0],
            big_g13[1] + (inv_m13 - 1) * g13[1],
        )
        physical_d12 = (
            positions[1][0] - positions[0][0],
            positions[1][1] - positions[0][1],
        )
        physical_d23 = (
            positions[1][0] - positions[2][0],
            positions[1][1] - positions[2][1],
        )
        assert _pair_equal(d12, physical_d12)
        assert _pair_equal(d23, physical_d23)

        energy = physical_energy(positions, velocities, U)
        projected_h = pair13_h_from_energy(
            U, energy, p13, _norm(d12), _norm(d23)
        )
        h_velocity = (
            sum(value**2 for value in pair13_chart_of(positions, velocities, U)[1])
            / 2
            - (a + 1) / _norm(g13)
        )
        assert sp.simplify(projected_h - h_velocity) == 0


def test_pair13_lc_angular_momentum_and_idot_identities_symbolic():
    """The LC angular-momentum and dI/dt factors include the correct 2."""
    wr, wi, zr, zi = sp.symbols("wr wi zr zi", real=True)
    radius = wr**2 + wi**2
    g = (wr**2 - wi**2, 2 * wr * wi)
    gdot = (
        2 * (wr * zr - wi * zi) / radius,
        2 * (wr * zi + wi * zr) / radius,
    )
    assert sp.cancel(_cross(g, gdot) - 2 * (wr * zi - wi * zr)) == 0
    assert sp.cancel(_dot(g, gdot) - 2 * (wr * zr + wi * zi)) == 0


def test_pair13_zero_angular_momentum_projection_exactly_fixes_leaf():
    """The coordinate-free P projection enforces L=0 and fixes L=0 points."""
    a, b = mass_A(U), mass_B(U)
    mu13 = a / (a + 1)
    mu_g = b * (a + 1) / (a + b + 1)
    samples = [
        (R(-3, 5), R(2, 7), R(4, 9), R(-5, 8),
         (R(7, 6), R(-2, 5)), (R(3, 11), R(-8, 13))),
        (R(5, 4), R(-1, 3), R(-7, 10), R(6, 11),
         (R(-4, 7), R(9, 5)), (R(-2, 9), R(5, 12))),
    ]
    for wr, wi, zr, zi, big_g, p in samples:
        spin = wr * zi - wi * zr
        target_cross = -2 * mu13 * spin / mu_g
        radius = _dot(big_g, big_g)
        j_big_g = (-big_g[1], big_g[0])
        correction = (target_cross - _cross(big_g, p)) / radius
        projected_p = tuple(
            p[k] + correction * j_big_g[k] for k in range(2)
        )
        assert sp.simplify(_cross(big_g, projected_p) - target_cross) == 0
        assert sp.simplify(_dot(big_g, projected_p) - _dot(big_g, p)) == 0
        assert sp.simplify(
            2 * mu13 * spin + mu_g * _cross(big_g, projected_p)
        ) == 0

        radial_rate = R(17, 19)
        leaf_p = tuple(
            (radial_rate * big_g[k] + target_cross * j_big_g[k]) / radius
            for k in range(2)
        )
        leaf_correction = (target_cross - _cross(big_g, leaf_p)) / radius
        fixed_p = tuple(
            leaf_p[k] + leaf_correction * j_big_g[k] for k in range(2)
        )
        assert _pair_equal(fixed_p, leaf_p)


def test_pair13_idot_reconstruction_is_unchanged_by_angular_projection():
    """Reconstructed jd is dI/dt and uses only the preserved radial P part."""
    a, b = mass_A(U), mass_B(U)
    mu13 = a / (a + 1)
    mu_g = b * (a + 1) / (a + b + 1)
    wr, wi, zr, zi = R(-3, 5), R(2, 7), R(4, 9), R(-5, 8)
    big_g, p = (R(7, 6), R(-2, 5)), (R(3, 11), R(-8, 13))
    spin = wr * zi - wi * zr
    target_cross = -2 * mu13 * spin / mu_g
    radius = _dot(big_g, big_g)
    j_big_g = (-big_g[1], big_g[0])
    correction = (target_cross - _cross(big_g, p)) / radius
    projected_p = tuple(p[k] + correction * j_big_g[k] for k in range(2))

    g = (wr**2 - wi**2, 2 * wr * wi)
    w2 = wr**2 + wi**2
    gdot = (
        2 * (wr * zr - wi * zi) / w2,
        2 * (wr * zi + wi * zr) / w2,
    )
    direct_idot = 2 * mu13 * _dot(g, gdot) + 2 * mu_g * _dot(big_g, p)
    projected_idot = (
        4 * mu13 * (wr * zr + wi * zi)
        + 2 * mu_g * _dot(big_g, projected_p)
    )
    assert sp.simplify(projected_idot - direct_idot) == 0


def test_tied_initial_state_has_prescribed_energy_leaf():
    """The normalized Pythagorean brake family has H=-U0(u) exactly."""
    a, b = mass_A(U), mass_B(U)
    positions = (
        (-R(1, 2), sp.Integer(0)),
        (R(1, 2), sp.Integer(0)),
        ((b**2 - a**2) / 2, a * b),
    )
    velocities = ((0, 0), (0, 0), (0, 0))
    u0 = a * b + 1 / (a * b)
    assert sp.simplify(physical_energy(positions, velocities, U) + u0) == 0


def test_form_a_lift_identities_symbolic():
    """Form A: w^2 = g and 2 w z / |w|^2 = gdot, symbolically on |g|+g_x>0."""
    gx = sp.Symbol("gx", positive=True)  # sufficient for Form A validity
    gy, gdx, gdy = sp.symbols("gy gdx gdy", real=True)
    absg = sp.sqrt(gx**2 + gy**2)
    wr = sp.sqrt((absg + gx) / 2)
    wi = gy / (2 * wr)
    zr = (wr * gdx + wi * gdy) / 2
    zi = (wr * gdy - wi * gdx) / 2
    w2 = wr**2 + wi**2
    assert sp.simplify(wr**2 - wi**2 - gx) == 0
    assert sp.simplify(2 * wr * wi - gy) == 0
    assert sp.simplify(2 * (wr * zr - wi * zi) / w2 - gdx) == 0
    assert sp.simplify(2 * (wr * zi + wi * zr) / w2 - gdy) == 0


def test_form_b_lift_identities_symbolic():
    """Form B: w^2 = g and 2 w z / |w|^2 = gdot, symbolically on g_x<0."""
    gx = sp.Symbol("gx", negative=True)
    gy = sp.Symbol("gy", real=True, nonzero=True)
    gdx, gdy = sp.symbols("gdx gdy", real=True)
    absg = sp.sqrt(gx**2 + gy**2)
    wi = sp.sqrt((absg - gx) / 2)
    wr = gy / (2 * wi)
    zr = (wr * gdx + wi * gdy) / 2
    zi = (wr * gdy - wi * gdx) / 2
    w2 = wr**2 + wi**2
    assert sp.simplify(wr**2 - wi**2 - gx) == 0
    assert sp.simplify(2 * wr * wi - gy) == 0
    assert sp.simplify(sp.together(2 * (wr * zr - wi * zi) / w2 - gdx)) == 0
    assert sp.simplify(sp.together(2 * (wr * zi + wi * zr) / w2 - gdy)) == 0


def test_transported_h_formulas():
    """new_h in both maps equals |gdot|^2/2 - M/|g| for the target pair."""
    a, b = mass_A(U), mass_B(U)
    for positions, velocities in STATES:
        g13, g13dot, _, _ = pair13_chart_of(positions, velocities, U)
        g23, g23dot, _, _ = pair23_chart_of(positions, velocities, U)
        h13 = ((g13dot[0] ** 2 + g13dot[1] ** 2) / 2
               - (a + 1) / sp.sqrt(g13[0] ** 2 + g13[1] ** 2))
        h23 = ((g23dot[0] ** 2 + g23dot[1] ** 2) / 2
               - (b + 1) / sp.sqrt(g23[0] ** 2 + g23[1] ** 2))
        # The rational cores were proved to reproduce (g, gdot); the h
        # formula in each map is literally this expression on those
        # outputs, so equality is immediate; assert it explicitly anyway.
        got13 = switch_23_to_13_relative(
            U, g23, g23dot, *pair23_chart_of(positions, velocities, U)[2:]
        )
        got23 = switch_13_to_23_relative(
            U, g13, g13dot, *pair13_chart_of(positions, velocities, U)[2:]
        )
        h13_mapped = ((got13[1][0] ** 2 + got13[1][1] ** 2) / 2
                      - (a + 1) / sp.sqrt(got13[0][0] ** 2
                                          + got13[0][1] ** 2))
        h23_mapped = ((got23[1][0] ** 2 + got23[1][1] ** 2) / 2
                      - (b + 1) / sp.sqrt(got23[0][0] ** 2
                                          + got23[0][1] ** 2))
        assert sp.simplify(h13_mapped - h13) == 0
        assert sp.simplify(h23_mapped - h23) == 0
