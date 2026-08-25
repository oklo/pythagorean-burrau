"""Exact regression tests for the pair-{2,3} terminal escape map.

Every test works with exact rationals or free symbols; the single
floating-point test compares against the committed ordinary-precision
implementation in ``src/dynamics/escape_certificate.py``.
"""

from __future__ import annotations

import sympy as sp

from src.dynamics.escape_certificate import evaluate_escape_certificate
from src.symbolic.middle_escape import (
    chart_from_relative,
    escape_margins_chart,
    escape_margins_physical,
    inner_specific_energy_chart,
    inner_specific_energy_relative,
    mass_A,
    mass_B,
    pair23_relative,
    pair_mass,
    relative_from_chart,
    symbolic_margin_expressions,
    total_mass,
)

R = sp.Rational

# Three non-special exact rational physical states (positions, velocities).
# None of them lies on the tied trajectory; they exercise generic algebra.
RATIONAL_STATES = [
    (
        ((R(-7, 5), R(2, 3)), (R(1, 4), R(-3, 7)), (R(5, 6), R(9, 8))),
        ((R(1, 3), R(-2, 5)), (R(-1, 6), R(4, 9)), (R(3, 8), R(-5, 7))),
    ),
    (
        ((R(11, 9), R(-4, 5)), (R(-2, 7), R(5, 4)), (R(-13, 6), R(1, 10))),
        ((R(-3, 11), R(7, 6)), (R(2, 9), R(-8, 5)), (R(5, 12), R(6, 13))),
    ),
    (
        ((R(0), R(3, 2)), (R(-5, 8), R(-1, 9)), (R(7, 3), R(-11, 12))),
        ((R(9, 7), R(0)), (R(-4, 13), R(2, 11)), (R(-1, 2), R(10, 9))),
    ),
]

U_VALUES = [R(29, 100), R(3, 10), R(2, 7)]


def test_pair_relative_definitions():
    """g, gdot, G, P match their defining physical formulas exactly."""
    for u in U_VALUES:
        b = mass_B(u)
        m = pair_mass(u)
        for positions, velocities in RATIONAL_STATES:
            q1, q2, q3 = positions
            v1, v2, v3 = velocities
            g, gdot, big_g, p = pair23_relative(positions, velocities, u)
            for k in range(2):
                assert sp.simplify(g[k] - (q3[k] - q2[k])) == 0
                assert sp.simplify(gdot[k] - (v3[k] - v2[k])) == 0
                assert sp.simplify(
                    big_g[k] - (q1[k] - (b * q2[k] + q3[k]) / m)
                ) == 0
                assert sp.simplify(
                    p[k] - (v1[k] - (b * v2[k] + v3[k]) / m)
                ) == 0


def test_chart_roundtrip_recovers_relative():
    """physical -> chart -> relative recovers g and gdot exactly."""
    for positions, velocities in RATIONAL_STATES:
        g, gdot, _, _ = pair23_relative(positions, velocities, R(29, 100))
        wr, wi, zr, zi = chart_from_relative(g, gdot)
        g2, gdot2 = relative_from_chart(wr, wi, zr, zi)
        for k in range(2):
            assert sp.simplify(g2[k] - g[k]) == 0
            assert sp.simplify(gdot2[k] - gdot[k]) == 0


def test_energy_identity_chart_vs_relative_symbolic():
    """(2|z|^2 - M)/|w|^2 == |gdot|^2/2 - M/|g| as an exact identity."""
    u = sp.Symbol("u", positive=True)
    wr, wi, zr, zi = sp.symbols("wr wi zr zi", real=True)
    g, gdot = relative_from_chart(wr, wi, zr, zi)
    chart_energy = inner_specific_energy_chart(u, wr, wi, zr, zi)
    # |g| = |w|^2 exactly: substitute the positive root by hand.
    gx, gy = g
    relative_energy = (
        (gdot[0] ** 2 + gdot[1] ** 2) / 2
        - pair_mass(u) / sp.sqrt(gx**2 + gy**2)
    )
    w2 = wr**2 + wi**2
    absg = sp.sqrt(gx**2 + gy**2)
    difference = relative_energy.subs(absg, w2) - chart_energy
    assert sp.simplify(difference) == 0


def test_energy_matches_direct_physical():
    """Chart energy equals the direct physical pair energy on rational states."""
    for u in U_VALUES:
        for positions, velocities in RATIONAL_STATES:
            g, gdot, _, _ = pair23_relative(positions, velocities, u)
            wr, wi, zr, zi = chart_from_relative(g, gdot)
            chart_energy = inner_specific_energy_chart(u, wr, wi, zr, zi)
            direct = inner_specific_energy_relative(u, g, gdot)
            assert sp.simplify(chart_energy - direct) == 0


def test_translation_invariance():
    """Shifting every position by a constant leaves all margins unchanged."""
    u, eta = R(29, 100), 4
    shift = (R(17, 3), R(-8, 11))
    positions, velocities = RATIONAL_STATES[0]
    shifted = tuple((q[0] + shift[0], q[1] + shift[1]) for q in positions)
    first = escape_margins_physical(positions, velocities, u, eta)
    second = escape_margins_physical(shifted, velocities, u, eta)
    assert first.failed == second.failed
    for name in ("inner_energy", "outer_distance", "radial_speed"):
        lhs, rhs = getattr(first, name), getattr(second, name)
        assert (lhs is None) == (rhs is None)
        if lhs is not None:
            assert sp.simplify(lhs - rhs) == 0


def test_boost_invariance():
    """Adding a constant velocity to every body leaves all margins unchanged."""
    u, eta = R(3, 10), 4
    boost = (R(-5, 9), R(13, 7))
    positions, velocities = RATIONAL_STATES[1]
    boosted = tuple((v[0] + boost[0], v[1] + boost[1]) for v in velocities)
    first = escape_margins_physical(positions, velocities, u, eta)
    second = escape_margins_physical(positions, boosted, u, eta)
    assert first.failed == second.failed
    for name in ("inner_energy", "outer_distance", "radial_speed"):
        lhs, rhs = getattr(first, name), getattr(second, name)
        assert (lhs is None) == (rhs is None)
        if lhs is not None:
            assert sp.simplify(lhs - rhs) == 0


def test_chart_sign_orientation_invariance():
    """w -> -w (same g) leaves every certificate quantity unchanged."""
    u, eta = R(29, 100), 4
    positions, velocities = RATIONAL_STATES[2]
    g, gdot, big_g, p = pair23_relative(positions, velocities, u)
    wr, wi, zr, zi = chart_from_relative(g, gdot)
    first = escape_margins_chart(
        u, wr, wi, zr, zi, big_g[0], big_g[1], p[0], p[1], eta
    )
    second = escape_margins_chart(
        u, -wr, -wi, -zr, -zi, big_g[0], big_g[1], p[0], p[1], eta
    )
    assert first.failed == second.failed
    for name in ("pair_distance", "inner_energy", "radial_speed"):
        lhs, rhs = getattr(first, name), getattr(second, name)
        assert (lhs is None) == (rhs is None)
        if lhs is not None:
            assert sp.simplify(lhs - rhs) == 0


def test_binary_label_swap_invariance():
    """Swapping the binary labels (g -> -g) preserves the certificate scalars.

    The theorem is symmetric in the binary bodies; only G's definition
    through the pair center of mass matters, and it is label-symmetric.
    """
    u, eta = R(29, 100), 4
    positions, velocities = RATIONAL_STATES[0]
    g, gdot, big_g, p = pair23_relative(positions, velocities, u)
    swapped_g = (-g[0], -g[1])
    swapped_gdot = (-gdot[0], -gdot[1])
    wr, wi, zr, zi = chart_from_relative(g, gdot)
    swr, swi, szr, szi = chart_from_relative(swapped_g, swapped_gdot)
    first = escape_margins_chart(
        u, wr, wi, zr, zi, big_g[0], big_g[1], p[0], p[1], eta
    )
    second = escape_margins_chart(
        u, swr, swi, szr, szi, big_g[0], big_g[1], p[0], p[1], eta
    )
    assert first.failed == second.failed
    assert sp.simplify(first.pair_distance - second.pair_distance) == 0
    assert sp.simplify(first.inner_energy - second.inner_energy) == 0


def _certifying_state(u):
    """A synthetic exact state that satisfies the eta = 4 certificate."""
    m = pair_mass(u)
    b = mass_B(u)
    # Binary {2,3}: tight slow pair; body 1 far away, moving outward.
    q2, q3 = (R(0), R(0)), (R(1, 10), R(0))
    v2, v3 = (R(0), R(0)), (R(0), R(1, 5))
    center = (b * q2[0] + q3[0]) / m, (b * q2[1] + q3[1]) / m
    q1 = (center[0] + 20, center[1] + R(1, 3))
    v1 = (R(2), R(1, 30))
    return (q1, q2, q3), (v1, v2, v3)


def test_certifying_state_certifies():
    u, eta = R(29, 100), 4
    positions, velocities = _certifying_state(u)
    result = escape_margins_physical(positions, velocities, u, eta)
    assert result.certified, result.failed


def test_agreement_with_float_implementation():
    """Symbolic margins equal the committed float implementation to 1e-12."""
    for u in U_VALUES:
        positions, velocities = _certifying_state(u)
        g, gdot, big_g, p = pair23_relative(positions, velocities, u)
        symbolic = escape_margins_physical(positions, velocities, u, 4)
        a_val = float(mass_A(u))
        b_val = float(mass_B(u))
        numeric = evaluate_escape_certificate(
            b_val,  # mass_a = m2 = B
            1.0,  # mass_b = m3 = 1
            a_val,  # mass_c = m1 = A
            [float(g[0]), float(g[1])],
            [float(gdot[0]), float(gdot[1])],
            [float(big_g[0]), float(big_g[1])],
            [float(p[0]), float(p[1])],
            4.0,
        )
        assert numeric.certified == symbolic.certified
        pairs = [
            (numeric.inner_specific_energy, symbolic.inner_energy),
            (numeric.outer_distance, symbolic.outer_distance),
            (numeric.outward_radial_speed, symbolic.radial_speed),
            (numeric.separation_margin, symbolic.separation_margin),
            (numeric.radial_energy_margin, symbolic.radial_energy),
            (numeric.speed_floor, symbolic.speed_floor),
            (numeric.tidal_energy_allowance, symbolic.tidal_allowance),
            (numeric.inner_energy_margin, symbolic.inner_energy_margin),
        ]
        for float_value, exact_value in pairs:
            assert abs(float_value - float(exact_value)) < 1e-12


def test_corrupted_mass_factors_detected():
    """Deliberately wrong mass factors change the margins at a generic state."""
    u, eta = R(29, 100), sp.Integer(4)
    positions, velocities = _certifying_state(u)
    result = escape_margins_physical(positions, velocities, u, eta)
    b = mass_B(u)
    m = pair_mass(u)
    mtot = total_mass(u)
    radius = m / eta
    d = result.separation_margin
    v = result.speed_floor

    # Corruption 1: escaper mass B instead of A in the tidal allowance.
    wrong_delta = b * sp.sqrt(2 * m * radius) / (v * d**2)
    assert sp.simplify(wrong_delta - result.tidal_allowance) != 0

    # Corruption 2: pair mass M in place of Mtot in the radial energy.
    wrong_radial = result.radial_speed**2 / 2 - m / d
    assert sp.simplify(wrong_radial - result.radial_energy) != 0

    # Corruption 3: total mass in the inner energy.
    g, gdot, _, _ = pair23_relative(positions, velocities, u)
    wrong_inner = (
        (gdot[0] ** 2 + gdot[1] ** 2) / 2
        - mtot / sp.sqrt(g[0] ** 2 + g[1] ** 2)
    )
    assert sp.simplify(wrong_inner - result.inner_energy) != 0

    # Corruption 4: reduced-mass-weighted inner energy is NOT the theorem's e.
    mu = b * 1 / m
    weighted = mu * ((gdot[0] ** 2 + gdot[1] ** 2) / 2) - m / sp.sqrt(
        g[0] ** 2 + g[1] ** 2
    )
    assert sp.simplify(weighted - result.inner_energy) != 0


def test_degenerate_guards_fail_closed():
    u, eta = R(29, 100), 4
    # w = 0: pair distance zero; no division should be attempted.
    result = escape_margins_chart(u, 0, 0, 1, 1, 3, 0, 1, 0, eta)
    assert "pair_distance_positive" in result.failed
    assert not result.certified

    # G = 0: outer distance zero.
    result = escape_margins_chart(u, 1, 0, 0, 0, 0, 0, 1, 0, eta)
    assert "outer_distance_positive" in result.failed
    assert result.radial_speed is None

    # rho <= R: separation margin fails, later roots undefined.
    tiny = R(1, 100)
    result = escape_margins_chart(u, 1, 0, 0, 0, tiny, 0, 1, 0, eta)
    assert "separation_margin_positive" in result.failed
    assert result.radial_energy is None
    assert result.tidal_allowance is None

    # Inward radial motion: radial speed hypothesis fails.
    result = escape_margins_chart(u, 1, 0, 0, 0, 30, 0, -1, 0, eta)
    assert "radial_speed_positive" in result.failed


def test_outer_acceleration_identity():
    """Newton gives Gddot = -(Mtot/M)(B d12/r12^3 + d13/r13^3) exactly.

    Inverse cubes are abstracted as independent symbols, making the identity
    polynomial: it must hold coefficient-by-coefficient, so the internal
    {2,3} force must cancel identically from Gddot.
    """
    u = sp.Symbol("u", positive=True)
    a, b = mass_A(u), mass_B(u)
    m = pair_mass(u)
    mtot = total_mass(u)
    q = sp.Matrix(sp.symbols("q1x q1y q2x q2y q3x q3y")).reshape(3, 2)
    ic12, ic13, ic23 = sp.symbols("ic12 ic13 ic23")  # 1/r_ij^3
    masses = [a, b, sp.Integer(1)]
    inv_cubes = {(0, 1): ic12, (0, 2): ic13, (1, 2): ic23}
    acc = [sp.zeros(1, 2) for _ in range(3)]
    for i in range(3):
        for j in range(3):
            if i == j:
                continue
            key = (min(i, j), max(i, j))
            delta = q.row(j) - q.row(i)
            acc[i] += masses[j] * delta * inv_cubes[key]
    g_ddot = acc[0] - (b * acc[1] + acc[2]) / m
    d12 = q.row(0) - q.row(1)
    d13 = q.row(0) - q.row(2)
    claimed = -(mtot / m) * (b * d12 * ic12 + d13 * ic13)
    difference = (g_ddot - claimed).applyfunc(sp.cancel)
    assert difference == sp.zeros(1, 2)


def _sigma_derivative(expr, u, wr, wi, zr, zi, fx, fy):
    """d/dsigma along the pair-{2,3} LC field with abstract external force."""
    m = pair_mass(u)
    w2 = wr**2 + wi**2
    h = (2 * (zr**2 + zi**2) - m) / w2
    rates = {
        wr: zr,
        wi: zi,
        zr: h / 2 * wr + w2 / 2 * (wr * fx + wi * fy),
        zi: h / 2 * wi + w2 / 2 * (wr * fy - wi * fx),
    }
    return sum(sp.diff(expr, var) * rate for var, rate in rates.items())


def test_lc_field_encodes_newton():
    """The CAPD z' equation reproduces gddot = -M g/r^3 + f exactly."""
    u = sp.Symbol("u", positive=True)
    wr, wi, zr, zi = sp.symbols("wr wi zr zi", real=True)
    fx, fy = sp.symbols("fx fy", real=True)
    m = pair_mass(u)
    w2 = wr**2 + wi**2
    g = (wr**2 - wi**2, 2 * wr * wi)
    args = (u, wr, wi, zr, zi, fx, fy)
    # dg/dt = (dg/dsigma)/|w|^2; d2g/dt2 = (d/dsigma dg/dt)/|w|^2.
    for k in range(2):
        gdot_k = _sigma_derivative(g[k], *args) / w2
        gddot_k = _sigma_derivative(gdot_k, *args) / w2
        newton_k = -m * g[k] / w2**3 + (fx, fy)[k]
        assert sp.simplify(gddot_k - newton_k) == 0


def test_hh_transport_matches_algebraic_energy():
    """The CAPD hh' equation is exactly d/dsigma of (2|z|^2 - M)/|w|^2.

    Hence hh == E23 is invariant along the pair-{2,3} LC flow whenever it
    holds at entry, for every external force.
    """
    u = sp.Symbol("u", positive=True)
    wr, wi, zr, zi = sp.symbols("wr wi zr zi", real=True)
    fx, fy = sp.symbols("fx fy", real=True)
    m = pair_mass(u)
    w2 = wr**2 + wi**2
    h_algebraic = (2 * (zr**2 + zi**2) - m) / w2
    args = (u, wr, wi, zr, zi, fx, fy)
    lhs = _sigma_derivative(h_algebraic, *args)
    rhs = 2 * ((wr * zr - wi * zi) * fx + (wr * zi + wi * zr) * fy)
    assert sp.simplify(lhs - rhs) == 0


def test_pair23_moment_derivative_field():
    """The pair-{2,3} jd' field equals |w|^2 (2U - 4 U0) with r23 = |w|^2."""
    u = sp.Symbol("u", positive=True)
    wr, wi = sp.symbols("wr wi", real=True)
    r12, r13 = sp.symbols("r12 r13", positive=True)
    a, b = mass_A(u), mass_B(u)
    ab = a * b
    u0 = ab + 1 / ab
    w2 = wr**2 + wi**2
    potential = ab / r12 + b / w2 + a / r13  # r23 = |w|^2
    lagrange_jacobi = w2 * (2 * potential - 4 * u0)
    capd_jd_sigma = 2 * (ab * w2 / r12 + b + a * w2 / r13) - 4 * u0 * w2
    assert sp.simplify(lagrange_jacobi - capd_jd_sigma) == 0


def test_symbolic_margin_expressions_consistent():
    """Free-symbol expressions agree with the guarded evaluation path."""
    symbols, expressions = symbolic_margin_expressions(eta=4)
    u = R(29, 100)
    positions, velocities = _certifying_state(u)
    g, gdot, big_g, p = pair23_relative(positions, velocities, u)
    wr, wi, zr, zi = chart_from_relative(g, gdot)
    values = dict(zip(symbols, (u, wr, wi, zr, zi, *big_g, *p), strict=True))
    result = escape_margins_chart(
        u, wr, wi, zr, zi, big_g[0], big_g[1], p[0], p[1], 4
    )
    for name, field in [
        ("inner_energy", result.inner_energy),
        ("radial_speed", result.radial_speed),
        ("separation_margin", result.separation_margin),
        ("radial_energy", result.radial_energy),
        ("tidal_allowance", result.tidal_allowance),
        ("inner_energy_margin", result.inner_energy_margin),
    ]:
        substituted = expressions[name].subs(values)
        assert abs(float(substituted) - float(field)) < 1e-25
