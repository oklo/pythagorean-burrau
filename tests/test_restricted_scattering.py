import sympy as sp

from src.symbolic.restricted_scattering import (
    maximum_softened_vertical_force,
    outer_energy_exchange_identity,
    phase_wronskian_identity,
    time_shift_melnikov_identity,
    transverse_variational_normal_form,
)


def test_outer_energy_exchange_is_binary_expansion_work() -> None:
    derived, expected = outer_energy_exchange_identity()
    assert sp.simplify(derived - expected) == 0


def test_small_speed_normal_form_has_sturm_coefficient() -> None:
    phase = sp.symbols("phase", real=True)
    assert sp.trigsimp(
        transverse_variational_normal_form() - (1 + 14 * sp.sec(phase) ** 2)
    ) == 0


def test_naive_phase_melnikov_is_a_boundary_term() -> None:
    integrand, derivative = time_shift_melnikov_identity()
    assert sp.simplify(integrand - derivative) == 0


def test_phase_wronskian_and_force_maximum() -> None:
    derivative, expected = phase_wronskian_identity()
    assert sp.simplify(derivative - expected) == 0
    height, force = maximum_softened_vertical_force()
    separation = sp.symbols("separation", positive=True)
    assert height == separation / (2 * sp.sqrt(2))
    assert force == 16 / (3 * sp.sqrt(3) * separation**2)
