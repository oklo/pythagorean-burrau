"""Exact coordinate changes between shape-velocity brake residuals."""

from __future__ import annotations

import sympy as sp


def torque_shape_map() -> tuple[sp.Matrix, sp.Expr]:
    """Return the maximum-event map U -> (ell_12, ell_23) and determinant.

    The rotation gauge is X=(R,0), Y=(C,D). The constraints I_dot=L=0
    determine V from U. ``alpha=m1/(m1+m2)`` and ``kappa=mu1/mu2``.
    """
    radius, c_value, d_value = sp.symbols("R C D", real=True, nonzero=True)
    alpha, kappa = sp.symbols("alpha kappa", positive=True)
    ux, uy = sp.symbols("u_x u_y", real=True)
    y_squared = c_value**2 + d_value**2
    vx = kappa * radius * (-c_value * ux + d_value * uy) / y_squared
    vy = -kappa * radius * (d_value * ux + c_value * uy) / y_squared
    x = sp.Matrix([radius, 0])
    y = sp.Matrix([c_value, d_value])
    u = sp.Matrix([ux, uy])
    v = sp.Matrix([vx, vy])

    def cross(left: sp.Matrix, right: sp.Matrix) -> sp.Expr:
        return left[0] * right[1] - left[1] * right[0]

    ell_12 = cross(x, u)
    ell_23 = cross(y - alpha * x, v - alpha * u)
    residual = sp.Matrix([ell_12, ell_23])
    linear_map = residual.jacobian([ux, uy]).applyfunc(sp.factor)
    return linear_map, sp.factor(linear_map.det())


def expected_torque_shape_determinant() -> sp.Expr:
    radius, c_value, d_value = sp.symbols("R C D", real=True, nonzero=True)
    alpha, kappa = sp.symbols("alpha kappa", positive=True)
    y_squared = c_value**2 + d_value**2
    return -alpha * radius * d_value * (
        1 + kappa * radius**2 / y_squared
    )
