"""Exact algebra regressions for the directional C2 parameter graph."""

from __future__ import annotations

import sympy as sp


def test_capd_quadratic_polarization_convention():
    h00, h01, h11 = sp.symbols("h00 h01 h11")
    v0, v1, w0, w1 = sp.symbols("v0 v1 w0 w1")

    def q(x0, x1):
        return h00 * x0**2 + h01 * x0 * x1 + h11 * x1**2

    cross = (
        2 * h00 * v0 * w0
        + h01 * (v0 * w1 + w0 * v1)
        + 2 * h11 * v1 * w1
    )
    assert sp.expand(q(v0 + w0, v1 + w1) - q(v0, v1) - q(w0, w1) - cross) == 0

    # A forbidden symmetric full double sum would count h01 twice.
    assert sp.expand(q(v0, v1) - (h00 * v0**2 + 2 * h01 * v0 * v1 + h11 * v1**2)) != 0


def test_exact_parameter_frame_inverse():
    v0, v1, v3 = sp.symbols("v0 v1 v3")
    # Pivot coordinate 2 is exactly the transported Euclid parameter, so v2=1.
    v = sp.Matrix([v0, v1, 1, v3])
    e = sp.Matrix([0, 0, 1, 0])
    identity = sp.eye(4)
    frame = identity + (v - e) * e.T
    inverse = identity - (v - e) * e.T
    assert sp.simplify(frame * inverse - identity) == sp.zeros(4)
    assert sp.simplify(inverse * frame - identity) == sp.zeros(4)
    assert sp.factor(frame.det()) == 1


def test_directional_quadratic_chain_rule():
    delta = sp.symbols("delta")
    x0, x1, t0, t1, q0, q1 = sp.symbols("x0 x1 t0 t1 q0 q1")
    gamma0 = x0 + t0 * delta + q0 * delta**2
    gamma1 = x1 + t1 * delta + q1 * delta**2
    mapping = gamma0**2 + gamma0 * gamma1 + gamma1**3

    coefficient = sp.expand(mapping).coeff(delta, 2)
    p_x = 2 * x0 + x1
    p_y = x0 + 3 * x1**2
    # CAPD-normalized quadratic coefficients of P at x.
    h_xx = 1
    h_xy = 1
    h_yy = 3 * x1
    expected = (
        p_x * q0
        + p_y * q1
        + h_xx * t0**2
        + h_xy * t0 * t1
        + h_yy * t1**2
    )
    assert sp.expand(coefficient - expected) == 0


def test_symmetric_parameter_square_is_nonnegative():
    # This records the interval-arithmetic obligation: the image of
    # [-d,d] under delta -> delta^2 is [0,d^2], whereas independent interval
    # multiplication would yield [-d^2,d^2].
    d = sp.symbols("d", positive=True)
    exact_lower, exact_upper = 0, d**2
    independent_lower, independent_upper = -d**2, d**2
    assert exact_lower > independent_lower
    assert exact_upper == independent_upper


def test_pg2_six_directional_form_update_is_exact_for_quadratic_maps():
    """The six masked forms reproduce every term through a quadratic map."""
    delta = sp.symbols("delta")
    t0, t1, q0, q1, e0, e1 = sp.symbols("t0 t1 q0 q1 e0 e1")
    t = sp.Matrix([t0, t1])
    q = sp.Matrix([q0, q1])
    e = sp.Matrix([e0, e1])
    jac = sp.Matrix([[2, -3], [5, 7]])
    # Taylor-coefficient convention: diagonal entries already contain 1/2.
    hess = [
        (sp.Rational(2, 3), sp.Rational(-5, 7), sp.Rational(11, 13)),
        (sp.Rational(-3, 8), sp.Rational(7, 9), sp.Rational(4, 5)),
    ]

    def quad(row, left, right=None):
        h00, h01, h11 = hess[row]
        if right is None:
            return h00 * left[0] ** 2 + h01 * left[0] * left[1] + h11 * left[1] ** 2
        return (
            2 * h00 * left[0] * right[0]
            + h01 * (left[0] * right[1] + left[1] * right[0])
            + 2 * h11 * left[1] * right[1]
        )

    h = t * delta + q * delta**2 + e
    for row in range(2):
        exact = sp.expand((jac * h)[row] + quad(row, h))
        t_new = (jac * t)[row] + quad(row, t, e)
        q_new = (jac * q)[row] + quad(row, t) + quad(row, q, e)
        remainder = (
            (jac * e)[row]
            + quad(row, e)
            + quad(row, t, q) * delta**3
            + quad(row, q) * delta**4
        )
        assert sp.expand(exact - t_new * delta - q_new * delta**2 - remainder) == 0
