"""Pair-adaptive LC shooting on a fixed physical endpoint section.

Analytic field variations and complex-step differentiation of algebraic chart
maps are used; no trajectory is finite-differenced. Ordinary numerics only.
"""

import numpy as np
from scipy.integrate import solve_ivp

from src.dynamics.periodic_shooting import PAIRS, algebra, initial_state


def cartesian(state, masses, pair):
    """Real algebraic reconstruction, holomorphic in complexified inputs."""
    i, j, k = PAIRS[pair]
    mi, mj, mk = masses[[i, j, k]]
    wr, wi, zr, zi = state[:4]
    rho = wr * wr + wi * wi
    g = np.array([wr * wr - wi * wi, 2 * wr * wi])
    dv = 2 * np.array([wr * zr - wi * zi, wr * zi + wi * zr]) / rho
    q = np.empty((3, 2), dtype=np.result_type(state, masses))
    v = np.empty_like(q)
    for target, relative, outer in ((q, g, state[5:7]), (v, dv, state[7:9])):
        target[k] = (mi + mj) / sum(masses) * outer
        target[i] = -mk / sum(masses) * outer - mj / (mi + mj) * relative
        target[j] = -mk / sum(masses) * outer + mi / (mi + mj) * relative
    return q, v


def change_chart(inputs, old, new):
    state, masses = inputs[:10], np.r_[inputs[10:12], 1.0]
    q, v = cartesian(state, masses, old)
    i, j, k = PAIRS[new]
    mi, mj = masses[[i, j]]
    g, dv = q[j] - q[i], v[j] - v[i]
    rho = np.sqrt(g @ g)
    # Choose the numerically safe square-root formula using the real base.
    if np.real(g[0]) >= 0:
        wr = np.sqrt((rho + g[0]) / 2)
        wi = g[1] / (2 * wr)
    else:
        sign = 1 if np.real(g[1]) >= 0 else -1
        wi = sign * np.sqrt((rho - g[0]) / 2)
        wr = g[1] / (2 * wi)
    z = 0.5 * np.array([wr * dv[0] + wi * dv[1], wr * dv[1] - wi * dv[0]])
    h = 0.5 * (dv @ dv) - (mi + mj) / rho
    G = q[k] - (mi * q[i] + mj * q[j]) / (mi + mj)
    P = v[k] - (mi * v[i] + mj * v[j]) / (mi + mj)
    return np.r_[wr, wi, z, h, G, P, state[9]]


def local_jacobian(function, values):
    """Complex-step derivative of local analytic algebra (never the flow)."""
    values = np.asarray(values, dtype=complex)
    columns = []
    for column in range(len(values)):
        trial = values.copy()
        trial[column] += 1e-30j
        columns.append(np.imag(function(trial)) / 1e-30)
    return np.array(columns).T


def distances(inputs, pair):
    state, masses = inputs[:10], np.r_[inputs[10:12], 1.0]
    # No physical velocity reconstruction needed near selected collision.
    wr, wi = state[:2]
    rho = wr * wr + wi * wi
    g = np.array([wr * wr - wi * wi, 2 * wr * wi])
    i, j, k = PAIRS[pair]
    mi, mj = masses[[i, j]]
    di = state[5:7] + mj / (mi + mj) * g
    dj = state[5:7] - mi / (mi + mj) * g
    result = {pair: rho}
    result["".join(str(n + 1) for n in sorted((i, k)))] = np.sqrt(di @ di)
    result["".join(str(n + 1) for n in sorted((j, k)))] = np.sqrt(dj @ dj)
    return np.array([result[p] for p in PAIRS])


def integrate_atlas(
    parameters,
    *,
    rtol=3e-13,
    atol=3e-15,
    max_step=0.05,
    method="DOP853",
    variational=True,
    start_pair=None,
):
    """Parameters (x,y,tau,m1,m2); terminal tangents use fixed physical tau."""
    x, y, tau, m1, m2 = parameters
    if min(y, tau, m1, m2) <= 0:
        raise ValueError("positive height, time and masses required")
    pair = start_pair or min(
        PAIRS, key=lambda p: {"12": 1.0, "23": np.hypot(x - 0.5, y), "13": np.hypot(x + 0.5, y)}[p]
    )
    # Start in the nonsingular base-side chart, then use the stable square root
    # map; this avoids cancellation in sqrt((r+gx)/2) for skinny launch shapes.
    state = initial_state(parameters, "12")
    tangent = np.zeros((10, 5))
    tangent[:, [0, 1, 3, 4]] = algebra("12")[3](x, y, m1, m2)
    if pair != "12":
        inputs = np.r_[state, m1, m2]
        jac = local_jacobian(lambda values: change_chart(values, "12", pair), inputs)
        tangent = jac[:, :10] @ tangent
        tangent[:, 3:] += jac[:, 10:]
        state = change_chart(inputs, "12", pair)
    segments, switches = [], []
    for _ in range(200):
        field, derivative = algebra(pair)[:2]

        def rhs(_s, value, field=field, derivative=derivative):
            args = (*value[:10], m1, m2)
            f = np.asarray(field(*args)).ravel()
            if not variational:
                return f
            jac = np.asarray(derivative(*args))
            dt = jac[:, :10] @ value[10:].reshape(10, 5)
            dt[:, 3:] += jac[:, 10:]
            return np.r_[f, dt.ravel()]

        def terminal(_s, value):
            return value[9] - tau

        terminal.terminal, terminal.direction = True, 1
        others = [p for p in PAIRS if p != pair]
        current_index = list(PAIRS).index(pair)
        events = [terminal]
        for other in others:
            index = list(PAIRS).index(other)

            def switch_event(_s, value, index=index, pair=pair, current_index=current_index):
                ds = distances(np.r_[value[:10], m1, m2], pair)
                return max(ds[index] - 0.04, ds[index] - 0.5 * ds[current_index])

            switch_event.terminal, switch_event.direction = True, -1
            events.append(switch_event)
        initial = np.r_[state, tangent.ravel()] if variational else state
        sol = solve_ivp(
            rhs,
            (0.0, 1000.0),
            initial,
            method=method,
            rtol=rtol,
            atol=atol,
            max_step=max_step,
            dense_output=True,
            events=events,
        )
        if not sol.success:
            raise RuntimeError(sol.message)
        segments.append((pair, sol))
        state = sol.y[:10, -1]
        if variational:
            tangent = sol.y[10:, -1].reshape(10, 5)
        f = np.asarray(field(*state, m1, m2)).ravel()
        if len(sol.t_events[0]):
            if f[9] <= np.finfo(float).tiny:
                raise RuntimeError("zero selected radius at physical endpoint")
            if variational:
                target_derivative = np.array([0.0, 0.0, 1.0, 0.0, 0.0])
                tangent += np.outer(f, (target_derivative - tangent[9]) / f[9])
            # Fix the endpoint LC lift and residual chart independently of all
            # earlier switches before any root or Jacobian comparison.
            inputs = np.r_[state, m1, m2]
            jac = local_jacobian(lambda values, pair=pair: change_chart(values, pair, "23"), inputs)
            if variational:
                tangent = jac[:, :10] @ tangent
                tangent[:, 3:] += jac[:, 10:]
            state = change_chart(inputs, pair, "23")
            pair = "23"
            return state, tangent, pair, segments, switches
        event_index = next((n for n in (1, 2) if len(sol.t_events[n])), None)
        if event_index is None:
            raise RuntimeError("LC segment budget exhausted before section")
        new = others[event_index - 1]
        other_index = list(PAIRS).index(new)
        inputs = np.r_[state, m1, m2]
        ds = distances(inputs, pair)
        ratio_section = ds[other_index] - 0.5 * ds[current_index] > ds[other_index] - 0.04

        def section(
            values,
            pair=pair,
            other_index=other_index,
            current_index=current_index,
            ratio_section=ratio_section,
        ):
            ds = distances(values, pair)
            return np.array(
                [
                    ds[other_index] - 0.5 * ds[current_index]
                    if ratio_section
                    else ds[other_index] - 0.04
                ]
            )

        if variational:
            gradient = local_jacobian(section, inputs).ravel()
            dg = gradient[:10] @ tangent
            dg[3:] += gradient[10:]
            transverse = gradient[:10] @ f
            if abs(transverse) < 1e-12:
                raise RuntimeError("nontransverse chart-switch event")
            tangent -= np.outer(f, dg / transverse)
            jac = local_jacobian(
                lambda values, pair=pair, new=new: change_chart(values, pair, new), inputs
            )
            tangent = jac[:, :10] @ tangent
            tangent[:, 3:] += jac[:, 10:]
        state = change_chart(inputs, pair, new)
        switches.append({"time": float(state[9]), "old": pair, "new": new})
        pair = new
    raise RuntimeError("too many LC chart changes")


def shooting_atlas(parameters, lam=1.0, **options):
    state, tangent, pair, segments, switches = integrate_atlas(parameters, **options)
    x, y, _, m1, m2 = parameters
    a, b = np.hypot(x - 0.5, y), np.hypot(x + 0.5, y)
    f = np.array(
        [
            state[2],
            state[3],
            state[5:7] @ state[7:9],
            m1 - (1 - lam) * 0.6 - lam * a,
            m2 - (1 - lam) * 0.8 - lam * b,
        ]
    )
    if state[5:7] @ state[5:7] < 1e-14:
        raise RuntimeError("degenerate endpoint brake chart")
    jac = np.zeros((5, 5))
    jac[:2] = tangent[2:4]
    jac[2] = state[5:7] @ tangent[7:9] + state[7:9] @ tangent[5:7]
    jac[3] = [-lam * (x - 0.5) / a, -lam * y / a, 0, 1, 0]
    jac[4] = [-lam * (x + 0.5) / b, -lam * y / b, 0, 0, 1]
    if not options.get("variational", True):
        jac = None
    return f, jac, {"state": state, "pair": pair, "segments": segments, "switches": switches}
