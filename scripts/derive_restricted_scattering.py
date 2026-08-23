#!/usr/bin/env python3
"""Print exact identities for the late skinny plunge model."""

from src.symbolic.restricted_scattering import (
    binary_tidal_transverse_first_variation,
    collision_kepler_transverse_transfer,
    maximum_softened_vertical_force,
    outer_energy_exchange_identity,
    parabolic_truncated_energy_drift,
    phase_wronskian_identity,
    restricted_equilateral_triple_collision,
    restricted_terminal_collision_r_chart,
    restricted_triple_collision_phase_mode,
    restricted_triple_collision_shape_energy,
    restricted_triple_collision_shape_spectrum,
    restricted_triple_collision_slow_field_barrier,
    restricted_universal_binary_lc_system,
    restricted_universal_binary_mu_system,
    second_encounter_endpoint_scattering,
    tight_binary_brake_hill_threshold,
    time_shift_melnikov_identity,
    transverse_variational_normal_form,
    triple_endpoint_finite_mass_exponents,
    triple_endpoint_mcgehee_shape_exponents,
)


def main() -> None:
    derivative, _ = outer_energy_exchange_identity()
    print(f"outer energy derivative = {derivative}")
    print(f"small-speed normal coefficient = {transverse_variational_normal_form()}")
    melnikov, boundary = time_shift_melnikov_identity()
    print(f"naive phase Melnikov integrand = {melnikov}")
    print(f"time-shift boundary derivative = {boundary}")
    wronskian, wronskian_expected = phase_wronskian_identity()
    print(f"phase Wronskian derivative = {wronskian}")
    print(f"phase Wronskian expected = {wronskian_expected}")
    print(f"softened force critical data = {maximum_softened_vertical_force()}")
    tidal_coefficient, tidal_expected = binary_tidal_transverse_first_variation()
    print(f"binary tidal transverse coefficient = {tidal_coefficient}")
    print(f"binary tidal transverse expected = {tidal_expected}")
    drift, drift_expected = parabolic_truncated_energy_drift()
    print(f"truncated parabolic energy drift = {drift}")
    print(f"truncated parabolic energy drift expected = {drift_expected}")
    print(f"collision-Kepler transverse transfer = {collision_kepler_transverse_transfer()}")
    print(f"second-encounter endpoint scattering = {second_encounter_endpoint_scattering()}")
    print(f"restricted triple collision = {restricted_equilateral_triple_collision()}")
    print(f"restricted terminal r chart = {restricted_terminal_collision_r_chart()}")
    print(f"restricted triple phase mode = {restricted_triple_collision_phase_mode()}")
    print(f"restricted triple shape energy = {restricted_triple_collision_shape_energy()}")
    print(
        "restricted triple slow-field barrier = "
        f"{restricted_triple_collision_slow_field_barrier()}"
    )
    print(f"restricted triple shape spectrum = {restricted_triple_collision_shape_spectrum()}")
    print(f"restricted universal binary LC system = {restricted_universal_binary_lc_system()}")
    print(f"restricted universal binary mu system = {restricted_universal_binary_mu_system()}")
    print(f"finite-mass endpoint exponents = {triple_endpoint_finite_mass_exponents()}")
    print(
        "McGehee endpoint shape exponents = "
        f"{triple_endpoint_mcgehee_shape_exponents()}"
    )
    print(f"tight-binary brake Hill threshold = {tight_binary_brake_hill_threshold()}")


if __name__ == "__main__":
    main()
