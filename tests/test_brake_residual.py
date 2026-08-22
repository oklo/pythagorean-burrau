import numpy as np

from src.dynamics.brake_residual import hopf_velocity, jacobi_vectors


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

