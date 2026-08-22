from fractions import Fraction

import numpy as np

from src.dynamics.cartesian import (
    energy,
    initial_state,
    pythagorean_defect,
    right_hand_side,
)


def test_initial_invariants_and_zero_momenta() -> None:
    masses, state = initial_state(Fraction(1, 3))
    positions = state[:6].reshape(3, 2)
    assert np.allclose(np.sum(masses[:, None] * positions, axis=0), 0)
    assert np.allclose(state[6:], 0)
    assert abs(pythagorean_defect(state)) < 1e-15
    p = masses[0] * masses[1]
    assert np.isclose(energy(state, masses), -(p + 1 / p))


def test_internal_forces_conserve_total_momentum_derivative() -> None:
    masses, state = initial_state(Fraction(2, 5))
    derivative = right_hand_side(0, state, masses)
    accelerations = derivative[6:].reshape(3, 2)
    assert np.allclose(np.sum(masses[:, None] * accelerations, axis=0), 0)

