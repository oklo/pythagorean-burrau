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
