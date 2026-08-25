"""Exact regressions for the tied first-maximum CAPD chart chain."""

from __future__ import annotations

import sympy as sp


def test_tied_pair13_launch_square_root_is_exact() -> None:
    u = sp.symbols("u", positive=True)
    q = 1 + u**2
    a = (1 - u**2) / q
    b = 2 * u / q
    gx = b**2
    gy = a * b
    wr = sp.sqrt(b * (1 + b) / 2)
    wi = gy / (2 * wr)

    assert sp.factor(sp.together(wr**2 - wi**2 - gx)) == 0
    assert sp.factor(sp.together(2 * wr * wi - gy)) == 0
    assert sp.factor(sp.together(wr**2 + wi**2 - b)) == 0


def test_tied_pair13_launch_chart_reconstructs_the_exact_brake() -> None:
    """The generated LC graph maps back to the normalized tied X,Y data."""
    u = sp.symbols("u", positive=True)
    q = 1 + u**2
    p = 1 + 2 * u - u**2
    a = (1 - u**2) / q
    b = 2 * u / q
    alpha = 2 * u / p
    inv_m13 = q / 2
    ag = 1 - u * q / p
    tied_yx = 2 * u * (1 - u**2) * (u**2 + 2 * u - 1) / (q**2 * p)
    tied_yy = 2 * u * (1 - u**2) / q**2
    gx = b**2
    gy = a * b
    complement_x = ag - inv_m13 * tied_yx
    complement_y = -inv_m13 * tied_yy

    reconstructed_x = sp.Matrix(
        [complement_x + inv_m13 * gx, complement_y + inv_m13 * gy]
    )
    reconstructed_y = sp.Matrix(
        [ag * gx - alpha * complement_x, ag * gy - alpha * complement_y]
    )
    expected_y = sp.Matrix([a * b * (b - a) / (a + b), a * b])

    for component in reconstructed_x - sp.Matrix([1, 0]):
        assert sp.factor(sp.together(component)) == 0
    for component in reconstructed_y - expected_y:
        assert sp.factor(sp.together(component)) == 0


def test_pair13_to_pair23_complement_map_is_exact() -> None:
    """The chart switch reconstructs q3-q2 and q1-C23 exactly."""
    a, b = sp.symbols("a b", positive=True)
    q1x, q1y, q2x, q2y, q3x, q3y = sp.symbols(
        "q1x q1y q2x q2y q3x q3y", real=True
    )
    v1x, v1y, v2x, v2y, v3x, v3y = sp.symbols(
        "v1x v1y v2x v2y v3x v3y", real=True
    )
    q1, q2, q3 = (
        sp.Matrix([q1x, q1y]),
        sp.Matrix([q2x, q2y]),
        sp.Matrix([q3x, q3y]),
    )
    v1, v2, v3 = (
        sp.Matrix([v1x, v1y]),
        sp.Matrix([v2x, v2y]),
        sp.Matrix([v3x, v3y]),
    )

    g13 = q3 - q1
    gd13 = v3 - v1
    big13 = q2 - (a * q1 + q3) / (a + 1)
    bigd13 = v2 - (a * v1 + v3) / (a + 1)
    x13 = big13 + g13 / (a + 1)
    xd13 = bigd13 + gd13 / (a + 1)

    implemented_g23 = g13 - x13
    implemented_gd23 = gd13 - xd13
    implemented_big23 = -x13 - implemented_g23 / (b + 1)
    implemented_bigd23 = -xd13 - implemented_gd23 / (b + 1)
    expected_big23 = q1 - (b * q2 + q3) / (b + 1)
    expected_bigd23 = v1 - (b * v2 + v3) / (b + 1)

    for component in implemented_g23 - (q3 - q2):
        assert sp.simplify(component) == 0
    for component in implemented_gd23 - (v3 - v2):
        assert sp.simplify(component) == 0
    for component in implemented_big23 - expected_big23:
        assert sp.simplify(component) == 0
    for component in implemented_bigd23 - expected_bigd23:
        assert sp.simplify(component) == 0


def test_pair23_to_pair13_complement_map_is_exact() -> None:
    """The inverse tree switch reconstructs q3-q1 and q2-C13 exactly."""
    a, b = sp.symbols("a b", positive=True)
    q1x, q1y, q2x, q2y, q3x, q3y = sp.symbols(
        "q1x q1y q2x q2y q3x q3y", real=True
    )
    v1x, v1y, v2x, v2y, v3x, v3y = sp.symbols(
        "v1x v1y v2x v2y v3x v3y", real=True
    )
    q1, q2, q3 = (
        sp.Matrix([q1x, q1y]),
        sp.Matrix([q2x, q2y]),
        sp.Matrix([q3x, q3y]),
    )
    v1, v2, v3 = (
        sp.Matrix([v1x, v1y]),
        sp.Matrix([v2x, v2y]),
        sp.Matrix([v3x, v3y]),
    )

    g23 = q3 - q2
    gd23 = v3 - v2
    big23 = q1 - (b * q2 + q3) / (b + 1)
    bigd23 = v1 - (b * v2 + v3) / (b + 1)
    d12 = big23 + g23 / (b + 1)
    d12d = bigd23 + gd23 / (b + 1)

    implemented_g13 = g23 - d12
    implemented_gd13 = gd23 - d12d
    implemented_big13 = -d12 - implemented_g13 / (a + 1)
    implemented_bigd13 = -d12d - implemented_gd13 / (a + 1)
    expected_big13 = q2 - (a * q1 + q3) / (a + 1)
    expected_bigd13 = v2 - (a * v1 + v3) / (a + 1)

    for component in implemented_g13 - (q3 - q1):
        assert sp.simplify(component) == 0
    for component in implemented_gd13 - (v3 - v1):
        assert sp.simplify(component) == 0
    for component in implemented_big13 - expected_big13:
        assert sp.simplify(component) == 0
    for component in implemented_bigd13 - expected_bigd13:
        assert sp.simplify(component) == 0


def test_lc_momentum_reconstructs_the_selected_pair_velocity() -> None:
    wr, wi, gdx, gdy = sp.symbols("wr wi gdx gdy", real=True)
    radius = wr**2 + wi**2
    zr = (wr * gdx + wi * gdy) / 2
    zi = (wr * gdy - wi * gdx) / 2

    reconstructed = sp.Matrix(
        [
            2 * (wr * zr - wi * zi) / radius,
            2 * (wr * zi + wi * zr) / radius,
        ]
    )
    for component in reconstructed - sp.Matrix([gdx, gdy]):
        assert sp.factor(sp.together(component)) == 0


def test_lc_algebraic_energy_elimination_is_exact() -> None:
    """Eliminating the dependent LC energy preserves the physical field."""
    wr, wi, zr, zi, pair_mass = sp.symbols(
        "wr wi zr zi pair_mass", real=True
    )
    radius = wr**2 + wi**2
    gdx = 2 * (wr * zr - wi * zi) / radius
    gdy = 2 * (wr * zi + wi * zr) / radius
    physical_energy = (gdx**2 + gdy**2) / 2 - pair_mass / radius
    constrained_energy = (2 * (zr**2 + zi**2) - pair_mass) / radius
    assert sp.factor(sp.together(physical_energy - constrained_energy)) == 0


def test_total_energy_leaf_eliminations_are_exact() -> None:
    """The regular h reconstructions impose exactly H=-U0 in both trees."""
    a, b = sp.symbols("a b", positive=True)
    p2, r12, r13, r23 = sp.symbols(
        "p2 r12 r13 r23", positive=True
    )
    total = a + b + 1
    u0 = a * b + 1 / (a * b)

    mu13 = a / (a + 1)
    mu_g13 = b * (a + 1) / total
    h13 = (
        -u0
        - mu_g13 * p2 / 2
        + a * b / r12
        + b / r23
    ) / mu13
    total_energy13 = (
        mu13 * h13
        + mu_g13 * p2 / 2
        - a * b / r12
        - b / r23
    )
    assert sp.factor(sp.together(total_energy13 + u0)) == 0

    mu23 = b / (b + 1)
    mu_g23 = a * (b + 1) / total
    h23 = (
        -u0
        - mu_g23 * p2 / 2
        + a * b / r12
        + a / r13
    ) / mu23
    total_energy23 = (
        mu23 * h23
        + mu_g23 * p2 / 2
        - a * b / r12
        - a / r13
    )
    assert sp.factor(sp.together(total_energy23 + u0)) == 0


def test_regularized_lagrange_jacobi_fields_are_exact() -> None:
    """Both chart formulas equal |w|^2(2U-4U0) after cancellation."""
    a, b, radius, r12, r13 = sp.symbols(
        "a b radius r12 r13", positive=True
    )
    u0 = a * b + 1 / (a * b)

    # Selected pair 13: its physical distance is radius; the other
    # distances are r12 and r23 (named r13 here only as a dummy positive).
    potential13 = a * b / r12 + a / radius + b / r13
    implemented13 = 2 * (
        a * b * radius / r12 + a + b * radius / r13
    ) - 4 * u0 * radius
    assert sp.expand(implemented13 - radius * (2 * potential13 - 4 * u0)) == 0

    # Selected pair 23: the remaining distances are r12 and r13.
    potential23 = a * b / r12 + b / radius + a / r13
    implemented23 = 2 * (
        a * b * radius / r12 + b + a * radius / r13
    ) - 4 * u0 * radius
    assert sp.expand(implemented23 - radius * (2 * potential23 - 4 * u0)) == 0


def test_pair23_reduced_masses_match_jacobi_decomposition() -> None:
    a, b = sp.symbols("a b", positive=True)
    total = a + b + 1
    pair_reduced = b / (b + 1)
    complement_reduced = a * (b + 1) / total
    assert sp.simplify(1 / pair_reduced - (1 / b + 1)) == 0
    assert sp.simplify(
        1 / complement_reduced - (1 / a + 1 / (b + 1))
    ) == 0


def test_u_one_third_general_coefficients_recover_legacy_chart() -> None:
    u = sp.Rational(1, 3)
    q = 1 + u**2
    a = (1 - u**2) / q
    b = 2 * u / q
    m12 = a + b
    alpha = b / m12
    beta = a / m12
    m13 = a + 1
    ag = 1 - alpha / m13

    assert (a, b, m12) == (sp.Rational(4, 5), sp.Rational(3, 5), sp.Rational(7, 5))
    assert (alpha, beta) == (sp.Rational(3, 7), sp.Rational(4, 7))
    assert m13 == sp.Rational(9, 5)
    assert ag == sp.Rational(16, 21)
