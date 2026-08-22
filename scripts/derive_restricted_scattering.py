#!/usr/bin/env python3
"""Print exact identities for the late skinny plunge model."""

from src.symbolic.restricted_scattering import (
    outer_energy_exchange_identity,
    transverse_variational_normal_form,
)


def main() -> None:
    derivative, _ = outer_energy_exchange_identity()
    print(f"outer energy derivative = {derivative}")
    print(f"small-speed normal coefficient = {transverse_variational_normal_form()}")


if __name__ == "__main__":
    main()
