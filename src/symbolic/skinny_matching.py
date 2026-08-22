"""Exact reference formulas for matching the skinny outer plunge."""

from __future__ import annotations

import sympy as sp


def matching_symbols() -> tuple[sp.Symbol, sp.Expr, sp.Expr, sp.Expr]:
    epsilon = sp.symbols("epsilon", positive=True)
    a = sp.sqrt(1 - epsilon**2)
    pair_mass = 1 + a
    total_mass = pair_mass + epsilon
    return epsilon, a, pair_mass, total_mass


def initial_outer_radius_squared() -> sp.Expr:
    _, a, pair_mass, _ = matching_symbols()
    return sp.simplify(2 * a**2 / pair_mass)


def monopole_outer_collision_time() -> sp.Expr:
    """Radial fall time for the collapsed-pair reference problem."""
    _, _, _, total_mass = matching_symbols()
    radius = sp.sqrt(initial_outer_radius_squared())
    return sp.pi * radius ** sp.Rational(3, 2) / (2 * sp.sqrt(2 * total_mass))


def unperturbed_binary_mean_motion() -> sp.Expr:
    """Mean motion of the heavy radial binary of apocenter epsilon."""
    epsilon, _, pair_mass, _ = matching_symbols()
    return sp.sqrt(8 * pair_mass) / epsilon ** sp.Rational(3, 2)


def reference_collision_phase() -> sp.Expr:
    """Binary mean anomaly accumulated by the monopole collision time."""
    return sp.simplify(
        unperturbed_binary_mean_motion() * monopole_outer_collision_time()
    )


def reference_fall_to_radius() -> tuple[sp.Expr, sp.Symbol]:
    """Return point-mass fall time to an outer radius and that radius symbol."""
    _, _, _, total_mass = matching_symbols()
    radius = sp.symbols("rho", positive=True)
    initial_radius = sp.sqrt(initial_outer_radius_squared())
    angle = sp.acos(sp.sqrt(radius / initial_radius))
    time = sp.sqrt(initial_radius**3 / (2 * total_mass)) * (
        angle + sp.sin(angle) * sp.cos(angle)
    )
    return time, radius


def reference_radial_velocity() -> tuple[sp.Expr, sp.Symbol]:
    _, _, _, total_mass = matching_symbols()
    radius = sp.symbols("rho", positive=True)
    initial_radius = sp.sqrt(initial_outer_radius_squared())
    velocity = -sp.sqrt(2 * total_mass * (1 / radius - 1 / initial_radius))
    return velocity, radius


def reference_section_phase() -> tuple[sp.Expr, sp.Symbol]:
    time, radius = reference_fall_to_radius()
    return sp.simplify(unperturbed_binary_mean_motion() * time), radius


def reference_collision_time_gap_coefficients() -> tuple[sp.Expr, sp.Expr]:
    """Coefficients of rho^(3/2) and rho^(5/2) in the remaining fall time."""
    _, _, _, total_mass = matching_symbols()
    radius, generic_initial, generic_mass = sp.symbols(
        "rho generic_initial generic_mass", positive=True
    )
    angle = sp.acos(sp.sqrt(radius / generic_initial))
    time = sp.sqrt(generic_initial**3 / (2 * generic_mass)) * (
        angle + sp.sin(angle) * sp.cos(angle)
    )
    collision_time = sp.pi * generic_initial ** sp.Rational(3, 2) / (
        2 * sp.sqrt(2 * generic_mass)
    )
    gap = collision_time - time
    first = sp.limit(gap / radius ** sp.Rational(3, 2), radius, 0, dir="+")
    residual = gap - first * radius ** sp.Rational(3, 2)
    second = sp.limit(residual / radius ** sp.Rational(5, 2), radius, 0, dir="+")
    initial_radius = sp.sqrt(initial_outer_radius_squared())
    substitutions = {generic_initial: initial_radius, generic_mass: total_mass}
    return sp.simplify(first.subs(substitutions)), sp.simplify(
        second.subs(substitutions)
    )


def reference_cycle_count() -> sp.Expr:
    return sp.simplify(reference_collision_phase() / (2 * sp.pi))


def reference_cycle_count_fourth_power() -> sp.Expr:
    epsilon, a, pair_mass, total_mass = matching_symbols()
    return sp.simplify(a**6 / (2 * pair_mass * total_mass**2 * epsilon**6))


def scaled_incoming_monopole_energy() -> sp.Expr:
    """Local-scale outer energy inherited from the initial rest state."""
    epsilon, _, _, total_mass = matching_symbols()
    radius = sp.sqrt(initial_outer_radius_squared())
    return sp.simplify(-epsilon * total_mass / radius)


def reference_phase_asymptotic_coefficients() -> tuple[sp.Expr, sp.Expr, sp.Expr]:
    """Coefficients of epsilon^(-3/2), epsilon^(-1/2), epsilon^(1/2)."""
    epsilon, _, _, _ = matching_symbols()
    phase = reference_collision_phase()
    leading = sp.limit(epsilon ** sp.Rational(3, 2) * phase, epsilon, 0)
    residual = phase - leading / epsilon ** sp.Rational(3, 2)
    subleading = sp.limit(sp.sqrt(epsilon) * residual, epsilon, 0)
    residual -= subleading / sp.sqrt(epsilon)
    third = sp.limit(residual / sp.sqrt(epsilon), epsilon, 0)
    return tuple(sp.simplify(value) for value in (leading, subleading, third))


def reference_phase_derivative_leading_coefficient() -> sp.Expr:
    epsilon, _, _, _ = matching_symbols()
    derivative = sp.diff(reference_collision_phase(), epsilon)
    return sp.simplify(
        sp.limit(epsilon ** sp.Rational(5, 2) * derivative, epsilon, 0)
    )


def exact_outer_direction_product() -> sp.Expr:
    """Product of direction cosines relative to the initial binary line."""
    epsilon, a, pair_mass, _ = matching_symbols()
    along_binary = a * epsilon / pair_mass
    perpendicular = -a
    return sp.simplify(
        along_binary * perpendicular / initial_outer_radius_squared()
    )


def exact_incoming_tilt() -> sp.Expr:
    """Signed acute tilt from the perpendicular to the binary line."""
    epsilon, _, pair_mass, _ = matching_symbols()
    return sp.atan(epsilon / pair_mass)


def degenerate_binary_mean_square_separation() -> sp.Expr:
    """Time average of |X|^2 over one radial Kepler cycle."""
    epsilon, _, _, _ = matching_symbols()
    phase = sp.symbols("phase", real=True)
    numerator = sp.integrate(sp.cos(phase) ** 6, (phase, 0, sp.pi))
    denominator = sp.integrate(sp.cos(phase) ** 2, (phase, 0, sp.pi))
    return sp.simplify(epsilon**2 * numerator / denominator)
