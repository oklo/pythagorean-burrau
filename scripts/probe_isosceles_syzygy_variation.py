#!/usr/bin/env python3
"""Ordinary first-variation probe at the isosceles first syzygy.

This computes the dynamical corner slope used by the exact threshold blow-up.
It is a deterministic discovery calculation, not a validated certificate.
"""

from __future__ import annotations

import numpy as np
from scipy.integrate import solve_ivp


def cross(left: np.ndarray, right: np.ndarray) -> float:
    return float(left[0] * right[1] - left[1] * right[0])


def endpoint_initial_data() -> tuple[np.ndarray, np.ndarray, np.ndarray]:
    root_two = np.sqrt(2.0)
    mass = 1.0 / root_two
    masses = np.array([mass, mass, 1.0])
    mass_derivative = np.array([-0.5, 0.5, 0.0])
    positions = np.array([[-0.5, 0.0], [0.5, 0.0], [0.0, 0.5]])
    state = np.concatenate([positions.ravel(), np.zeros(6)])

    # v parametrizes u=(sqrt(2)-1)v.  At v=1 only q3_x changes at launch:
    # d(B^2-A^2)/2dv=A=1/sqrt(2), while d(AB)/dv=0.
    sensitivity = np.zeros(12)
    sensitivity[4] = mass
    return masses, mass_derivative, np.concatenate([state, sensitivity])


def augmented_field(
    _time: float,
    augmented: np.ndarray,
    masses: np.ndarray,
    mass_derivative: np.ndarray,
) -> np.ndarray:
    state = augmented[:12]
    sensitivity = augmented[12:]
    positions = state[:6].reshape(3, 2)
    velocities = state[6:].reshape(3, 2)
    position_sensitivity = sensitivity[:6].reshape(3, 2)
    velocity_sensitivity = sensitivity[6:].reshape(3, 2)
    accelerations = np.zeros((3, 2))
    acceleration_sensitivity = np.zeros((3, 2))

    for i in range(3):
        for j in range(3):
            if i == j:
                continue
            delta = positions[j] - positions[i]
            radius_squared = float(np.dot(delta, delta))
            inverse_cube = radius_squared ** -1.5
            inverse_five = radius_squared ** -2.5
            gravity_jacobian = (
                np.eye(2) * inverse_cube
                - 3.0 * np.outer(delta, delta) * inverse_five
            )
            accelerations[i] += masses[j] * delta * inverse_cube
            acceleration_sensitivity[i] += (
                masses[j]
                * gravity_jacobian
                @ (position_sensitivity[j] - position_sensitivity[i])
                + mass_derivative[j] * delta * inverse_cube
            )

    state_rate = np.concatenate([velocities.ravel(), accelerations.ravel()])
    sensitivity_rate = np.concatenate(
        [velocity_sensitivity.ravel(), acceleration_sensitivity.ravel()]
    )
    return np.concatenate([state_rate, sensitivity_rate])


def signed_twice_area(
    _time: float,
    augmented: np.ndarray,
    _masses: np.ndarray,
    _mass_derivative: np.ndarray,
) -> float:
    positions = augmented[:6].reshape(3, 2)
    return cross(positions[1] - positions[0], positions[2] - positions[0])


signed_twice_area.terminal = True
signed_twice_area.direction = -1


def main() -> None:
    masses, mass_derivative, initial = endpoint_initial_data()
    solution = solve_ivp(
        augmented_field,
        (0.0, 0.5),
        initial,
        args=(masses, mass_derivative),
        events=signed_twice_area,
        method="DOP853",
        rtol=2e-13,
        atol=2e-15,
        max_step=2e-5,
    )
    if not solution.success or not solution.t_events[0].size:
        raise RuntimeError("ordinary endpoint first-syzygy integration failed")

    augmented = solution.y_events[0][0]
    state = augmented[:12]
    sensitivity = augmented[12:]
    positions = state[:6].reshape(3, 2)
    velocities = state[6:].reshape(3, 2)
    position_sensitivity = sensitivity[:6].reshape(3, 2)

    base = positions[1] - positions[0]
    apex = positions[2] - positions[0]
    base_velocity = velocities[1] - velocities[0]
    apex_velocity = velocities[2] - velocities[0]
    base_sensitivity = position_sensitivity[1] - position_sensitivity[0]
    apex_sensitivity = position_sensitivity[2] - position_sensitivity[0]
    area_time = cross(base_velocity, apex) + cross(base, apex_velocity)
    area_parameter = cross(base_sensitivity, apex) + cross(
        base, apex_sensitivity
    )
    event_time_derivative = -area_parameter / area_time
    event_position_sensitivity = (
        position_sensitivity + velocities * event_time_derivative
    )

    r12_vector = positions[1] - positions[0]
    r31_vector = positions[0] - positions[2]
    r12_sensitivity = (
        event_position_sensitivity[1] - event_position_sensitivity[0]
    )
    r31_sensitivity = (
        event_position_sensitivity[0] - event_position_sensitivity[2]
    )
    r12 = float(np.linalg.norm(r12_vector))
    r31 = float(np.linalg.norm(r31_vector))
    r12_parameter = float(np.dot(r12_vector, r12_sensitivity) / r12)
    r31_parameter = float(np.dot(r31_vector, r31_sensitivity) / r31)
    q = r31 / r12
    q_parameter = (r31_parameter * r12 - r31 * r12_parameter) / r12**2

    # z=q(m+n)/n has z_v=2q_v-1/sqrt(2) at the equal-mass endpoint.
    corner_slope = 2.0 * q_parameter - 1.0 / np.sqrt(2.0)
    relative_23 = positions[2] - positions[1]
    velocity_23 = velocities[2] - velocities[1]
    ell_23 = cross(relative_23, velocity_23)
    amplitude = ell_23**2 / r12

    print(
        "status=ORDINARY_NUMERICAL_EVIDENCE "
        f"syzygy_time={solution.t_events[0][0]:.16g} "
        f"area_time={area_time:.16g} "
        f"event_time_derivative={event_time_derivative:.16g} "
        f"R={r12:.16g} q={q:.16g} q_v={q_parameter:.16g} "
        f"lambda={corner_slope:.16g} Z={amplitude:.16g}"
    )


if __name__ == "__main__":
    main()
