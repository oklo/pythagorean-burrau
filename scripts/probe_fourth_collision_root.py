#!/usr/bin/env python3
"""Ordinary floating-point seed for the fourth restricted collision root.

This mirrors the chart chain in the CAPD verifier but uses floating-point
DOP853 integration. Its output is seed data only, never a certificate; its
terminal collision phase is known to be quantitatively inaccurate.
"""

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import root

from scripts.probe_planar_joint_shape import initial_state, shape_field
from scripts.probe_planar_light_collision_lc import BINARY_SCALE, heavy_binary_field

ZETA_START = 15.0
ZETA_ENTRY = 0.3


def reversed_lc_field(_clock: float, state: np.ndarray, primary: int) -> np.ndarray:
    u = complex(state[0], state[1])
    v = complex(state[2], state[3])
    energy = state[4]
    radial_time = state[5]
    separation = BINARY_SCALE * radial_time ** (2.0 / 3.0)
    relative = u * u
    other = relative + primary * separation
    forcing = primary / separation**2 - other / abs(other) ** 3
    v_forward = energy * u / 2.0 + abs(u) ** 2 * np.conj(u) * forcing / 2.0
    energy_forward = 2.0 * np.real(u * v * np.conj(forcing))
    return np.array(
        [
            -v.real,
            -v.imag,
            -v_forward.real,
            -v_forward.imag,
            -energy_forward,
            -(abs(u) ** 2),
        ]
    )


def integrate(field, span: float, state: np.ndarray, max_step: float) -> np.ndarray:
    solution = solve_ivp(
        field,
        (0.0, span),
        state,
        method="DOP853",
        rtol=2e-13,
        atol=2e-15,
        max_step=max_step,
    )
    if not solution.success:
        raise RuntimeError(solution.message)
    return solution.y[:, -1]


def first_positive_entry(kappa: float) -> np.ndarray:
    shape = solve_ivp(
        shape_field,
        (ZETA_START, ZETA_ENTRY),
        initial_state(kappa, ZETA_START, -1.0),
        method="DOP853",
        rtol=2e-13,
        atol=2e-15,
        max_step=0.002,
    )
    if not shape.success:
        raise RuntimeError(shape.message)
    x, y, vx, vy = shape.y[:, -1]
    radial_time = np.exp(0.3)
    separation = BINARY_SCALE * np.exp(0.2)
    velocity_scale = BINARY_SCALE / np.exp(0.1)
    q = separation * complex(x - 0.5, y)
    q_velocity = velocity_scale * complex(2.0 * (x - 0.5) / 3.0 + vx,
                                          2.0 * y / 3.0 + vy)
    u = np.sqrt(q)
    if u.real < 0.0:
        u = -u
    v = np.conj(u) * q_velocity / 2.0
    energy = abs(q_velocity) ** 2 / 2.0 - 1.0 / abs(q)
    return np.array([u.real, u.imag, v.real, v.imag, energy, radial_time])


def switch_primary(state: np.ndarray, selected_primary: int) -> np.ndarray:
    """Switch from ``selected_primary`` to the opposite LC chart."""
    u = complex(state[0], state[1])
    v = complex(state[2], state[3])
    radial_time = state[5]
    separation = BINARY_SCALE * radial_time ** (2.0 / 3.0)
    q = u * u
    q_velocity = 2.0 * u * v / abs(u) ** 2
    if selected_primary == 1:
        other_q = q + separation
        other_velocity = q_velocity + 2.0 * separation / (3.0 * radial_time)
        other_u = np.sqrt(other_q)
        if other_u.real < 0.0:
            other_u = -other_u
    else:
        other_q = q - separation
        other_velocity = q_velocity - 2.0 * separation / (3.0 * radial_time)
        norm = abs(other_q)
        other_ui = -np.sqrt((norm - other_q.real) / 2.0)
        other_ur = other_q.imag / (2.0 * other_ui)
        other_u = complex(other_ur, other_ui)
    other_v = np.conj(other_u) * other_velocity / 2.0
    other_energy = abs(other_velocity) ** 2 / 2.0 - 1.0 / abs(other_q)
    return np.array(
        [
            other_u.real,
            other_u.imag,
            other_v.real,
            other_v.imag,
            other_energy,
            radial_time,
        ]
    )


def bridge_to_fourth_entry(state: np.ndarray) -> np.ndarray:
    u = complex(state[0], state[1])
    v = complex(state[2], state[3])
    radial_time = state[5]
    separation = BINARY_SCALE * radial_time ** (2.0 / 3.0)
    q = u * u
    q_velocity = 2.0 * u * v / abs(u) ** 2
    outer = q + separation / 2.0
    outer_velocity = q_velocity + separation / (3.0 * radial_time)
    lambda_start = radial_time ** (1.0 / 3.0)
    bridge = solve_ivp(
        heavy_binary_field,
        (lambda_start, lambda_start - 97.0 / 5000.0),
        np.array([outer.real, outer.imag, outer_velocity.real, outer_velocity.imag]),
        method="DOP853",
        rtol=2e-13,
        atol=2e-15,
        max_step=0.0001,
    )
    if not bridge.success:
        raise RuntimeError(bridge.message)
    lambda_end = bridge.t[-1]
    x, y, vx, vy = bridge.y[:, -1]
    radial_time = lambda_end**3
    separation = BINARY_SCALE * lambda_end**2
    q_minus = complex(x + separation / 2.0, y)
    q_minus_velocity = complex(vx + BINARY_SCALE / (3.0 * lambda_end), vy)
    u_minus = np.sqrt(q_minus)
    if u_minus.real < 0.0:
        u_minus = -u_minus
    v_minus = np.conj(u_minus) * q_minus_velocity / 2.0
    energy = abs(q_minus_velocity) ** 2 / 2.0 - 1.0 / abs(q_minus)
    return np.array(
        [
            u_minus.real,
            u_minus.imag,
            v_minus.real,
            v_minus.imag,
            energy,
            radial_time,
        ]
    )


def fourth_state(kappa: float, fourth_clock: float) -> np.ndarray:
    state = first_positive_entry(kappa)
    state = integrate(lambda t, y: reversed_lc_field(t, y, 1), 7.0 / 4.0,
                      state, 0.002)
    state = switch_primary(state, 1)
    state = integrate(lambda t, y: reversed_lc_field(t, y, -1),
                      10275749204.0 / 1e10 + 83687424.0 / 1e8,
                      state, 0.001)
    state = switch_primary(state, -1)
    state = integrate(lambda t, y: reversed_lc_field(t, y, 1),
                      123106953.0 / 1e8, state, 0.001)
    state = bridge_to_fourth_entry(state)
    return integrate(lambda t, y: reversed_lc_field(t, y, -1), fourth_clock,
                     state, 0.0002)


def main() -> None:
    kappa_base = 1.26400909899
    clock_base = 0.37184018
    kappa_scale = 1e-12
    clock_scale = 1e-6

    def scaled_residual(point: np.ndarray) -> np.ndarray:
        state = fourth_state(
            kappa_base + float(point[0]) * kappa_scale,
            clock_base + float(point[1]) * clock_scale,
        )
        return 1e6 * state[:2]

    solution = root(
        scaled_residual,
        np.zeros(2),
        method="hybr",
        tol=1e-9,
        options={"eps": 1e-5},
    )
    kappa = kappa_base + float(solution.x[0]) * kappa_scale
    fourth_clock = clock_base + float(solution.x[1]) * clock_scale
    state = fourth_state(kappa, fourth_clock)
    print("status=ORDINARY_NUMERICAL_EVIDENCE")
    print(f"solver_success={solution.success}")
    print(f"kappa={kappa:.17g}")
    print(f"fourth_clock={fourth_clock:.17g}")
    print(f"residual_norm={np.linalg.norm(state[:2]):.17g}")
    print("collision_state=" + ",".join(f"{value:.17g}" for value in state))
    lc_constraint = (
        2.0 * np.dot(state[2:4], state[2:4])
        - 1.0
        - state[4] * np.dot(state[:2], state[:2])
    )
    print(f"lc_constraint={lc_constraint:.17g}")


if __name__ == "__main__":
    main()
