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
    restricted_triple_collision_phase_mode,
    restricted_triple_collision_shape_spectrum,
    second_encounter_endpoint_scattering,
    time_shift_melnikov_identity,
    transverse_variational_normal_form,
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
    print(f"restricted triple phase mode = {restricted_triple_collision_phase_mode()}")
    print(f"restricted triple shape spectrum = {restricted_triple_collision_shape_spectrum()}")


if __name__ == "__main__":
    main()
