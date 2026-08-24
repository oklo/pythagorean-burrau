import numpy as np

from src.dynamics.brake_residual import (
    double_radial_slip_residual,
    hopf_velocity,
    jacobi_vectors,
    pair_angular_momentum_brake_residual,
)


def test_zero_hopf_velocity_for_rigid_rotation() -> None:
    x = np.array([2.0, -1.0])
    y = np.array([0.5, 3.0])
    quarter_turn = np.array([[0.0, -1.0], [1.0, 0.0]])
    assert np.allclose(hopf_velocity(x, y, quarter_turn @ x, quarter_turn @ y), 0)


def test_hopf_residual_detects_transverse_syzygy_velocity() -> None:
    # All mutual-distance derivatives vanish even though the middle body has
    # a nonzero transverse shape velocity.
    positions = np.array([[-1.0, 0.0], [1.0, 0.0], [0.0, 0.0]])
    velocities = np.array([[0.0, 0.0], [0.0, 0.0], [0.0, 1.0]])
    masses = np.ones(3)
    x, y = jacobi_vectors(positions, masses)
    vx, vy = jacobi_vectors(velocities, masses)

    for i, j in [(0, 1), (0, 2), (1, 2)]:
        relative_position = positions[j] - positions[i]
        relative_velocity = velocities[j] - velocities[i]
        assert np.dot(relative_position, relative_velocity) == 0

    assert not np.allclose(hopf_velocity(x, y, vx, vy), 0)


def test_double_radial_slip_vanishes_only_for_common_rotation() -> None:
    x = np.array([2.0, -1.0])
    y = np.array([0.5, 3.0])
    quarter_turn = np.array([[0.0, -1.0], [1.0, 0.0]])
    assert np.allclose(
        double_radial_slip_residual(x, y, quarter_turn @ x, quarter_turn @ y), 0
    )
    unequal_rotation = double_radial_slip_residual(
        x, y, quarter_turn @ x, 2 * quarter_turn @ y
    )
    assert np.allclose(unequal_rotation[:2], 0)
    assert unequal_rotation[2] != 0


def test_pair_angular_momentum_residual_kills_nonzero_homothety() -> None:
    positions = np.array([[-1.0, 0.0], [0.0, 1.0], [1.0, 0.0]])
    masses = np.ones(3)
    center = np.average(positions, axis=0, weights=masses)
    homothetic_velocities = 2.0 * (positions - center)
    residual = pair_angular_momentum_brake_residual(
        positions, homothetic_velocities, masses
    )
    assert np.allclose(residual[:2], 0)
    assert residual[2] > 0
    assert np.allclose(
        pair_angular_momentum_brake_residual(
            positions, np.zeros((3, 2)), masses
        ),
        0,
    )


def test_pair_angular_momentum_residual_is_degenerate_at_syzygy() -> None:
    positions = np.array([[-1.0, 0.0], [0.0, 0.0], [1.0, 0.0]])
    velocities = np.array([[1.0, 0.0], [-2.0, 0.0], [1.0, 0.0]])
    masses = np.ones(3)
    assert np.allclose(
        pair_angular_momentum_brake_residual(positions, velocities, masses), 0
    )
    assert not np.allclose(velocities, 0)
