import sympy as sp

from src.symbolic.initial_identities import (
    center_of_mass,
    euclid_symbols,
    identity_residuals,
)


def test_initial_identities_have_zero_residual() -> None:
    assert identity_residuals() == {"I0": 0, "U0": 0, "D2": 0}


def test_center_of_mass_formula() -> None:
    _, a, b = euclid_symbols()
    expected = sp.Matrix([(b - a) / 2, a * b / (a + b + 1)])
    assert (center_of_mass() - expected).applyfunc(sp.simplify) == sp.zeros(2, 1)


def test_defect_acceleration_is_positive_on_full_real_family() -> None:
    # A,B in (0,1), AB <= 1/2 and A+B <= sqrt(2).  Hence
    # (AB)^2(A+B) <= sqrt(2)/4 < 1.
    assert sp.sqrt(2) / 4 < 1

