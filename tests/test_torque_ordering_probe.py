import numpy as np
import pytest
import sympy as sp

from scripts.probe_torque_ordering import (
    first_syzygy,
    instantaneous_torque_rate_ratio,
    twice_area,
    twice_area_second_derivative,
)
from src.dynamics.cartesian import initial_state_real
from src.symbolic.initial_identities import (
    euclid_symbols,
    signed_area_second_derivative,
)


def test_initial_twice_area_and_syzygy_event_orientation() -> None:
    masses, state = initial_state_real(1 / 3)
    assert twice_area(state) == pytest.approx(12 / 25)
    u, _, _ = euclid_symbols()
    exact_area_second = signed_area_second_derivative().subs(u, sp.Rational(1, 3))
    assert twice_area_second_derivative(state, masses) == pytest.approx(
        float(exact_area_second)
    )
    assert first_syzygy.terminal is True
    assert first_syzygy.direction == -1


def test_initial_instantaneous_torque_rate_ratio() -> None:
    _, state = initial_state_real(1 / 3)
    positions = state[:6].reshape(3, 2)
    distances = np.array(
        [
            np.linalg.norm(positions[1] - positions[0]),
            np.linalg.norm(positions[2] - positions[1]),
            np.linalg.norm(positions[0] - positions[2]),
        ]
    )
    expected = ((4 / 5) ** -3 - 1) / ((3 / 5) ** -3 - 1)
    assert instantaneous_torque_rate_ratio(distances) == pytest.approx(expected)
