"""Selected-pair LC shooting with propagated analytic first variations.

All integrations here are ordinary floating-point computations, not validated
enclosures. A selected-pair collision can be crossed by this coordinate field;
positive sampled distances must never be promoted to a collision certificate.
"""

from functools import lru_cache

import numpy as np
import sympy as sp
from scipy.integrate import solve_ivp

PAIRS = {"12": (0, 1, 2), "23": (1, 2, 0), "13": (0, 2, 1)}


@lru_cache(maxsize=3)
def algebra(pair):
    """Compile the exact real LC field and its state/mass derivatives."""
    state = sp.Matrix(sp.symbols("wr wi zr zi h Gx Gy Px Py t"))
    wr, wi, zr, zi, h, gx, gy, px, py, _ = state
    m1, m2, x, y = sp.symbols("m1 m2 x y", real=True)
    masses = [m1, m2, sp.Integer(1)]
    i, j, k = PAIRS[pair]
    mi, mj, mk = [masses[n] for n in (i, j, k)]
    total, mpair = sum(masses), mi + mj
    rho = wr**2 + wi**2
    g = sp.Matrix([wr**2 - wi**2, 2 * wr * wi])
    complement = sp.Matrix([gx, gy])
    di, dj = complement + mj / mpair * g, complement - mi / mpair * g

    def phi(d):
        return d / d.dot(d) ** sp.Rational(3, 2)

    external = mk * (phi(dj) - phi(di))
    acceleration = -total / mpair * (mi * phi(di) + mj * phi(dj))
    fx, fy = external
    field = sp.Matrix(
        [
            zr,
            zi,
            h * wr / 2 + rho * (wr * fx + wi * fy) / 2,
            h * wi / 2 + rho * (wr * fy - wi * fx) / 2,
            2 * ((wr * zr - wi * zi) * fx + (wr * zi + wi * zr) * fy),
            rho * px,
            rho * py,
            rho * acceleration[0],
            rho * acceleration[1],
            rho,
        ]
    )
    q = [sp.Matrix([-sp.Rational(1, 2), 0]), sp.Matrix([sp.Rational(1, 2), 0]), sp.Matrix([x, y])]
    g0 = q[j] - q[i]
    r0 = sp.sqrt(g0.dot(g0))
    w0r = sp.sqrt((r0 + g0[0]) / 2)
    w0i = g0[1] / (2 * w0r)
    c0 = q[k] - (mi * q[i] + mj * q[j]) / mpair
    initial = sp.Matrix([w0r, w0i, 0, 0, -mpair / r0, *c0, 0, 0, 0])
    inputs = [x, y, m1, m2]
    field_args = [*state, m1, m2]
    return (
        sp.lambdify(field_args, field, "numpy", cse=True),
        sp.lambdify(field_args, field.jacobian(field_args), "numpy", cse=True),
        sp.lambdify(inputs, initial, "numpy", cse=True),
        sp.lambdify(inputs, initial.jacobian(inputs), "numpy", cse=True),
    )


def initial_state(parameters, pair):
    x, y, _, m1, m2 = parameters
    return np.asarray(algebra(pair)[2](x, y, m1, m2), dtype=float).ravel()


def integrate(
    parameters,
    pair="23",
    *,
    variational=True,
    rtol=2e-12,
    atol=2e-14,
    max_step=0.005,
    method="DOP853",
    dense_output=False,
):
    """Parameters are (x,y,S,m1,m2); clock is sigma/S in [0,1]."""
    x, y, duration, m1, m2 = parameters
    if min(y, duration, m1, m2) <= 0:
        raise ValueError("positive height, duration and masses required")
    field, derivative, init, init_derivative = algebra(pair)
    state = np.asarray(init(x, y, m1, m2), dtype=float).ravel()
    if variational:
        tangent = np.zeros((10, 5))
        tangent[:, [0, 1, 3, 4]] = init_derivative(x, y, m1, m2)
        state = np.r_[state, tangent.ravel()]

    def rhs(_s, value):
        args = (*value[:10], m1, m2)
        f = np.asarray(field(*args)).ravel()
        if not variational:
            return duration * f
        jac = np.asarray(derivative(*args))
        tangent = value[10:].reshape(10, 5)
        dtangent = duration * jac[:, :10] @ tangent
        dtangent[:, 2] += f
        dtangent[:, 3:] += duration * jac[:, 10:]
        return np.r_[duration * f, dtangent.ravel()]

    sol = solve_ivp(
        rhs,
        (0.0, 1.0),
        state,
        method=method,
        rtol=rtol,
        atol=atol,
        max_step=max_step,
        dense_output=dense_output,
    )
    if not sol.success:
        raise RuntimeError(sol.message)
    return sol


def shooting(parameters, pair="23", lam=1.0, **options):
    """Native brake plus mass-side homotopy; return F, analytic DF, flow.

    The brake equations z_r=z_i=G.P=0 are complete on L=0 when G!=0.
    lam=0 fixes the catalog masses; lam=1 ties masses to opposite sides.
    """
    sol = integrate(parameters, pair, **options)
    endpoint = sol.y[:10, -1]
    if np.dot(endpoint[5:7], endpoint[5:7]) < 1e-14:
        raise ValueError("native endpoint brake chart degenerates at G=0")
    x, y, _, m1, m2 = parameters
    a, b = np.hypot(x - 0.5, y), np.hypot(x + 0.5, y)
    residual = np.array(
        [
            endpoint[2],
            endpoint[3],
            endpoint[5:7] @ endpoint[7:9],
            m1 - (1 - lam) * 0.6 - lam * a,
            m2 - (1 - lam) * 0.8 - lam * b,
        ]
    )
    jac = np.zeros((5, 5))
    if sol.y.shape[0] > 10:
        tangent = sol.y[10:, -1].reshape(10, 5)
        jac[:2] = tangent[2:4]
        jac[2] = endpoint[5:7] @ tangent[7:9] + endpoint[7:9] @ tangent[5:7]
        jac[3] = [-lam * (x - 0.5) / a, -lam * y / a, 0, 1, 0]
        jac[4] = [-lam * (x + 0.5) / b, -lam * y / b, 0, 0, 1]
    else:
        jac = None
    return residual, jac, sol


def physical_state(states, masses, pair):
    """Reconstruct labelled COM Cartesian states from LC values (10,n)."""
    i, j, k = PAIRS[pair]
    mi, mj, mk = np.asarray(masses)[[i, j, k]]
    w, z = states[0] + 1j * states[1], states[2] + 1j * states[3]
    g, velocity = w**2, 2 * w * z / (states[0] ** 2 + states[1] ** 2)
    c, cv = states[5] + 1j * states[6], states[7] + 1j * states[8]
    q = np.empty((3, *np.shape(w)), dtype=complex)
    v = np.empty_like(q)
    for arr, relative, outer in ((q, g, c), (v, velocity, cv)):
        arr[k] = (mi + mj) / sum(masses) * outer
        arr[i] = -mk / sum(masses) * outer - mj / (mi + mj) * relative
        arr[j] = -mk / sum(masses) * outer + mi / (mi + mj) * relative
    return q, v


def seed_duration(x, y, tau, masses, pair, rtol=2e-12):
    """Locate the physical target time in a selected LC clock, for seeding."""
    m1, m2, _ = masses
    field = algebra(pair)[0]
    initial = initial_state([x, y, 1, m1, m2], pair)

    def event(_sigma, state):
        return state[9] - tau

    event.terminal = True
    event.direction = 1
    sol = solve_ivp(
        lambda _s, state: np.asarray(field(*state, m1, m2)).ravel(),
        (0.0, 1000.0),
        initial,
        events=event,
        rtol=rtol,
        atol=rtol * 0.01,
        method="DOP853",
        max_step=0.05,
    )
    if not sol.success or len(sol.t_events[0]) != 1:
        raise RuntimeError("physical target time not reached")
    return float(sol.t[-1])
