import sympy as sp

from src.symbolic.restricted_scattering import (
    outer_energy_exchange_identity,
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
