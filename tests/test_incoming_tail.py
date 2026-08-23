import sympy as sp

from src.symbolic.incoming_tail import (
    lc_normal_invariant_derivatives,
    lc_normal_jacobian_determinant,
    symmetric_transverse_coefficient_series,
    tail_exponents,
    transverse_euler_roots,
)


def test_lc_normal_invariants_have_only_forced_derivatives() -> None:
    zx, zy, px, py = sp.symbols("zx zy px py", real=True)
    gx, gy, energy_rate = sp.symbols("gx gy h", real=True)
    angular_rate, fradkin_rate = lc_normal_invariant_derivatives()
    assert angular_rate == gx * (-zy) + gy * zx
    assert fradkin_rate == gx * py + gy * px - energy_rate * zx * zy / 2


def test_lc_normal_coordinates_have_uniform_radial_rank() -> None:
    assert lc_normal_jacobian_determinant() == -sp.Rational(1, 2)


def test_overlap_error_exponents_are_positive_for_alpha_below_one_sixth() -> None:
    alpha = sp.symbols("alpha", real=True)
    exponents = tail_exponents()
    assert exponents == {
        "overlap_energy": 3 - 3 * alpha,
        "initial_action_phase": 1 - 3 * alpha / 2,
        "energy_time_of_flight": sp.Rational(1, 2) - alpha / 2,
        "mass_frequency_clock": sp.Rational(1, 2) + 3 * alpha / 2,
    }
    assert all(value.subs(alpha, sp.Rational(1, 6)) > 0 for value in exponents.values())


def test_transverse_euler_modes_both_grow_at_infinity() -> None:
    assert transverse_euler_roots() == (sp.Rational(1, 2), sp.Integer(1))


def test_symmetric_transverse_coefficient_has_integrable_correction() -> None:
    inverse_radius, half_binary = sp.symbols("x a", real=True)
    assert symmetric_transverse_coefficient_series() == (
        2 * inverse_radius**3 - 9 * half_binary**2 * inverse_radius**5
    )
