#!/usr/bin/env python3
"""Print exact identities for the late skinny plunge model."""

from src.symbolic.restricted_scattering import (
    outer_energy_exchange_identity,
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


if __name__ == "__main__":
    main()
