import numpy as np

from src.dynamics.skinny_regularized import (
    initial_regularized_state,
    regularized_right_hand_side,
)


def test_limiting_initial_regularized_vector_field() -> None:
    epsilon = 1e-8
    state = initial_regularized_state(epsilon)
    derivative = regularized_right_hand_side(0, state, epsilon)
    # z_s=p=0, p_s=-z/2, and tau_s=1 in the radial Kepler limit.
    assert np.allclose(derivative[:2], 0, atol=1e-20)
    assert np.allclose(derivative[2:4], [-0.5, 0], atol=1e-12)
    assert np.isclose(derivative[-1], 1)

