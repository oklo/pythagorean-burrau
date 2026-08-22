#!/usr/bin/env python3
"""Print exact identities for the late skinny plunge model."""

from src.symbolic.restricted_scattering import (
    maximum_softened_vertical_force,
    outer_energy_exchange_identity,
    phase_wronskian_identity,
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


if __name__ == "__main__":
    main()
