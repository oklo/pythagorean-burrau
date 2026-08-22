import sympy as sp

from src.symbolic.skinny_matching import (
    degenerate_binary_mean_square_separation,
    exact_incoming_tilt,
    exact_outer_direction_product,
    matching_symbols,
    reference_collision_phase,
    reference_collision_time_gap_coefficients,
    reference_cycle_count,
    reference_cycle_count_fourth_power,
    reference_fall_to_radius,
    reference_phase_asymptotic_coefficients,
    reference_phase_derivative_leading_coefficient,
    reference_radial_velocity,
    reference_section_phase,
    scaled_incoming_monopole_energy,
)


def test_reference_phase_coefficients() -> None:
    assert reference_phase_asymptotic_coefficients() == (
        sp.pi,
        -sp.pi / 4,
        -15 * sp.pi / 32,
    )


def test_cycle_count_fourth_power_is_rational_on_the_tied_curve() -> None:
    assert sp.simplify(
        reference_cycle_count() ** 4 - reference_cycle_count_fourth_power()
    ) == 0


def test_scaled_incoming_energy_starts_at_minus_two_epsilon() -> None:
    epsilon, _, _, _ = matching_symbols()
    energy = scaled_incoming_monopole_energy()
    assert sp.limit(energy / epsilon, epsilon, 0) == -2
    assert sp.limit((energy + 2 * epsilon) / epsilon**2, epsilon, 0) == -1


def test_phase_sweeps_at_epsilon_to_the_minus_five_halves() -> None:
    assert reference_phase_derivative_leading_coefficient() == -3 * sp.pi / 2


def test_exact_point_fall_section_formulas() -> None:
    epsilon, _, pair_mass, total_mass = matching_symbols()
    initial_radius = sp.sqrt(2 * (1 - epsilon**2) / pair_mass)
    time, radius = reference_fall_to_radius()
    phase, phase_radius = reference_section_phase()
    velocity, velocity_radius = reference_radial_velocity()
    assert phase_radius == radius == velocity_radius
    assert sp.simplify(time.subs(radius, initial_radius)) == 0
    limiting_phase = sp.limit(phase, radius, 0, dir="+")
    assert sp.simplify(limiting_phase**2 - reference_collision_phase() ** 2) == 0
    assert sp.simplify(
        velocity**2 / 2 - total_mass * (1 / radius - 1 / initial_radius)
    ) == 0
    first_gap, second_gap = reference_collision_time_gap_coefficients()
    assert sp.simplify(first_gap - 2 / (3 * sp.sqrt(2 * total_mass))) == 0
    assert sp.simplify(
        second_gap - 1 / (5 * sp.sqrt(2 * total_mass) * initial_radius)
    ) == 0


def test_exact_outer_tilt_and_binary_quadrupole_average() -> None:
    epsilon, a, _, _ = matching_symbols()
    assert exact_outer_direction_product() == -epsilon / 2
    tangent = sp.tan(exact_incoming_tilt())
    assert sp.simplify(2 * tangent / (1 + tangent**2) - epsilon) == 0
    assert sp.simplify((1 - tangent**2) / (1 + tangent**2) - a) == 0
    assert degenerate_binary_mean_square_separation() == 5 * epsilon**2 / 8
