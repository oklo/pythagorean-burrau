import sympy as sp

from src.symbolic.preplunge_matching import (
    exact_outer_torque_factorization,
    lc_clock_identity,
    outer_multipole_moments,
    transverse_quadrupole_coefficients,
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


def test_transverse_quadrupole_gains_one_skinny_power() -> None:
    early_force, averaged_tail_force, tail_displacement = (
        transverse_quadrupole_coefficients()
    )
    assert early_force == sp.Rational(3, 4)
    assert averaged_tail_force == sp.Rational(15, 32)
    assert tail_displacement == sp.Rational(5, 128)


def test_outer_torque_has_exact_perpendicular_cancellation() -> None:
    torque, factored = exact_outer_torque_factorization()
    assert sp.expand(torque - factored) == 0
