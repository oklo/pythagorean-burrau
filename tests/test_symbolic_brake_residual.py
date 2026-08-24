import sympy as sp

from src.symbolic.brake_residual import (
    expected_torque_shape_determinant,
    torque_shape_map,
)


def test_torque_shape_map_degenerates_exactly_at_syzygy() -> None:
    linear_map, determinant = torque_shape_map()
    assert sp.factor(determinant - expected_torque_shape_determinant()) == 0
    radius, c_value, d_value = sp.symbols("R C D", real=True, nonzero=True)
    alpha, kappa = sp.symbols("alpha kappa", positive=True)
    assert linear_map.shape == (2, 2)
    expected = -alpha * radius * d_value * (
        1 + kappa * radius**2 / (c_value**2 + d_value**2)
    )
    assert sp.factor(determinant - expected) == 0
