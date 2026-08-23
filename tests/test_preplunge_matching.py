import sympy as sp

from src.symbolic.preplunge_matching import (
    lc_clock_identity,
    outer_multipole_moments,
)


def test_outer_dipole_cancels_exactly() -> None:
    a = sp.symbols("A", positive=True)
    zeroth, first, second = outer_multipole_moments()
    assert zeroth == 1
    assert first == 0
    assert second == a / (1 + a) ** 2


def test_lc_clock_identity_uses_energy_constraint() -> None:
    energy, radius_squared, forcing = sp.symbols("E r2 forcing", real=True)
    assert lc_clock_identity() == sp.Rational(1, 2) + energy * radius_squared + forcing

