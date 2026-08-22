import sympy as sp

from src.symbolic.skinny_regularization import (
    encounter_symbols,
    initial_outer_monopole_energy_series,
    initial_outer_radius_squared,
    leading_scaled_force_coefficients,
    levi_civita_transverse_displacement_coefficient,
    physical_angular_momentum_coefficient,
    physical_miss_distance_coefficient,
)


def test_leading_scaled_tidal_force() -> None:
    _, radius = encounter_symbols()
    longitudinal, transverse = leading_scaled_force_coefficients()
    assert longitudinal == -radius / 2
    assert transverse == -3 * radius / 4


def test_regularized_crossing_and_physical_coefficients() -> None:
    assert levi_civita_transverse_displacement_coefficient() == -15 * sp.pi / 128
    assert physical_miss_distance_coefficient() == 225 * sp.pi**2 / 16384
    assert physical_angular_momentum_coefficient() == -15 * sp.pi / 64


def test_outer_state_is_deeply_bound_during_the_first_passage() -> None:
    epsilon, _ = encounter_symbols()
    a = sp.sqrt(1 - epsilon**2)
    assert sp.simplify(initial_outer_radius_squared() - 2 * a**2 / (1 + a)) == 0
    assert initial_outer_monopole_energy_series().subs(epsilon, 0) == -2
