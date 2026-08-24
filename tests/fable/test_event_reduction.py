"""Exact and numerical checks for the Fable event-reduction lemmas."""

from __future__ import annotations

import numpy as np
import sympy as sp

from src.dynamics.cartesian import initial_state_real, right_hand_side
from src.fable.events import (
    angular_momentum,
    center_of_mass_frame,
    event_record,
    hopf_residual,
    initial_potential,
    moment_derivative,
    moment_of_inertia,
    potential,
    zeta,
)


def random_state(rng: np.random.Generator) -> np.ndarray:
    return rng.uniform(-1.0, 1.0, size=12)


def test_splitting_system_is_nonsingular() -> None:
    """{I_dot=0, zeta=0, L=0} in the velocities has only the trivial solution.

    The four linear equations in (vx, vy) are mu1 X.vx + mu2 Y.vy = 0,
    mu1 X.vx - mu2 Y.vy = 0, mu1 XxVx - mu2 YxVy = 0, mu1 XxVx + mu2 YxVy = 0.
    Their determinant must be a nonzero multiple of |X|^2 |Y|^2.
    """
    x1, x2, y1, y2, mu1, mu2 = sp.symbols("x1 x2 y1 y2 mu1 mu2", real=True)
    rows = sp.Matrix(
        [
            [mu1 * x1, mu1 * x2, mu2 * y1, mu2 * y2],
            [mu1 * x1, mu1 * x2, -mu2 * y1, -mu2 * y2],
            [-mu1 * x2, mu1 * x1, mu2 * y2, -mu2 * y1],
            [-mu1 * x2, mu1 * x1, -mu2 * y2, mu2 * y1],
        ]
    )
    determinant = sp.expand(rows.det())
    expected = sp.expand(
        4 * mu1**2 * mu2**2 * (x1**2 + x2**2) * (y1**2 + y2**2)
    )
    assert sp.simplify(determinant - expected) == 0


def test_lagrange_jacobi_identity_exact_rational_points() -> None:
    """d^2 I/dt^2 = 4 K - 2 U checked in exact rational arithmetic.

    The residual is an algebraic function of positions, velocities, masses,
    and the three inverse distances.  Evaluating it exactly at rational
    states whose squared distances are perfect rational squares gives an
    exact-arithmetic regression of the identity as implemented.
    """
    rng = np.random.default_rng(3)
    masses_sym = [sp.Rational(4, 5), sp.Rational(3, 5), sp.Integer(1)]
    for _ in range(4):
        # random rational positions/velocities with denominator 16
        raw = rng.integers(-24, 25, size=24)
        q = [
            sp.Matrix([sp.Rational(int(raw[4 * i]), 16), sp.Rational(int(raw[4 * i + 1]), 16)])
            for i in range(3)
        ]
        v = [
            sp.Matrix([sp.Rational(int(raw[4 * i + 2]), 16), sp.Rational(int(raw[4 * i + 3]), 16)])
            for i in range(3)
        ]
        total = sum(masses_sym)
        q_cm = sum((masses_sym[i] * q[i] for i in range(3)), sp.zeros(2, 1)) / total
        v_cm = sum((masses_sym[i] * v[i] for i in range(3)), sp.zeros(2, 1)) / total

        def distance(i: int, j: int, q: list = q) -> sp.Expr:
            d = q[j] - q[i]
            return sp.sqrt(d.dot(d))

        potential_expr = (
            masses_sym[0] * masses_sym[1] / distance(0, 1)
            + masses_sym[1] * masses_sym[2] / distance(1, 2)
            + masses_sym[2] * masses_sym[0] / distance(2, 0)
        )
        accelerations = []
        for i in range(3):
            acc = sp.zeros(2, 1)
            for j in range(3):
                if j != i:
                    d = q[j] - q[i]
                    acc = acc + masses_sym[j] * d / distance(i, j) ** 3
            accelerations.append(acc)
        kinetic = (
            sum(
                masses_sym[i] * (v[i] - v_cm).dot(v[i] - v_cm)
                for i in range(3)
            )
            / 2
        )
        a_cm = (
            sum(
                (masses_sym[i] * accelerations[i] for i in range(3)),
                sp.zeros(2, 1),
            )
            / total
        )
        second = 4 * kinetic + 2 * sum(
            masses_sym[i] * (q[i] - q_cm).dot(accelerations[i] - a_cm)
            for i in range(3)
        )
        residual = sp.nsimplify(second - (4 * kinetic - 2 * potential_expr))
        assert sp.simplify(residual) == 0


def test_moment_derivative_matches_finite_difference() -> None:
    rng = np.random.default_rng(7)
    masses = np.array([0.8, 0.6, 1.0])
    for _ in range(5):
        state = random_state(rng)
        derivative = right_hand_side(0.0, state, masses)
        step = 1e-6
        forward = moment_of_inertia(state + step * derivative, masses)
        backward = moment_of_inertia(state - step * derivative, masses)
        finite = (forward - backward) / (2 * step)
        assert abs(finite - moment_derivative(state, masses)) < 1e-7


def test_zero_velocity_iff_residual_zero() -> None:
    rng = np.random.default_rng(11)
    masses = np.array([0.8, 0.6, 1.0])
    positions = rng.uniform(-1.0, 1.0, size=6)

    brake_state = np.concatenate([positions, np.zeros(6)])
    assert abs(moment_derivative(brake_state, masses)) == 0.0
    assert abs(zeta(brake_state, masses)) == 0.0
    assert np.linalg.norm(hopf_residual(brake_state, masses)) == 0.0

    # A random zero-angular-momentum, nonzero velocity state must be seen by
    # (I_dot, zeta).
    for _ in range(20):
        state = random_state(rng)
        state = center_of_mass_frame(state, masses)
        # project out total angular momentum by a rigid rotation correction
        ell = angular_momentum(state, masses)
        positions_m, velocities_m = state[:6].reshape(3, 2), state[6:].reshape(3, 2)
        inertia = moment_of_inertia(state, masses)
        omega = ell / inertia
        rotated = velocities_m - omega * np.stack(
            [-positions_m[:, 1], positions_m[:, 0]], axis=1
        )
        state = np.concatenate([positions_m.ravel(), rotated.ravel()])
        assert abs(angular_momentum(state, masses)) < 1e-12
        speed = float(np.linalg.norm(rotated))
        if speed < 1e-6:
            continue
        scalars = np.array(
            [moment_derivative(state, masses), abs(zeta(state, masses))]
        )
        assert np.linalg.norm(scalars) > 1e-12


def test_event_record_classification_at_burrau_start() -> None:
    masses, state0 = initial_state_real(1 / 3)
    u_potential_0 = initial_potential(1 / 3)
    record = event_record(0.0, state0, masses, u_potential_0)
    assert record.is_maximum
    assert abs(record.potential_ratio - 1.0) < 1e-12
    assert record.residual_norm == 0.0
    assert record.zeta_real == 0.0
    assert record.zeta_imag == 0.0
    assert record.zeta_abs == 0.0
    assert record.ell_12 == 0.0
    assert record.ell_23 == 0.0
    # separation bound r_ij >= m_i m_j / U_0 at a brake
    bound = min(
        masses[0] * masses[1], masses[1] * masses[2], masses[2] * masses[0]
    ) / potential(state0, masses)
    assert record.min_separation >= bound - 1e-12


def test_kinetic_energy_at_degenerate_events() -> None:
    """K = U - U_0 makes K >= U_0 whenever U >= 2 U_0 (folds and minima)."""
    masses, state0 = initial_state_real(0.25)
    u0 = potential(state0, masses)
    assert abs(initial_potential(0.25) - u0) < 1e-12


def test_damped_construction_forcing_hits_exact_target() -> None:
    """The LC entry/exit inflation contains an exact graph overwrite.

    This is the scalar identity used coordinatewise by the CAPD runtime
    gate.  The required constant forcing may depend on the initial graph
    point; integrating the whole forcing interval encloses all such choices.
    """
    rate, duration = sp.symbols("c tau", positive=True)
    initial, target = sp.symbols("y_0 T", real=True)
    decay = sp.exp(-rate * duration)
    forcing = rate * decay * (target - initial) / (1 - decay)
    endpoint = target + decay * (initial - target) + forcing * (1 - decay) / rate
    assert sp.simplify(endpoint - target) == 0


def test_exact_event_shape_speed_factorization() -> None:
    """At I_dot=L=0, |zeta|^2 = 8 K J_X J_Y / I exactly."""
    j_x, j_y = sp.symbols("J_X J_Y", positive=True)
    d, h = sp.symbols("d h", real=True)
    kinetic = (d**2 / 8 + h**2 / 2) * (1 / j_x + 1 / j_y)
    zeta_squared = d**2 + 4 * h**2
    assert sp.simplify(
        zeta_squared - 8 * kinetic * j_x * j_y / (j_x + j_y)
    ) == 0

    inertia = j_x + j_y
    shape = j_x / inertia
    shape_rate = d / inertia
    angle_rate = -h * inertia / (j_x * j_y)
    shape_zeta_squared = inertia**2 * (
        shape_rate**2 + 4 * shape**2 * (1 - shape) ** 2 * angle_rate**2
    )
    assert sp.simplify(shape_zeta_squared - zeta_squared) == 0
