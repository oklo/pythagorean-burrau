#!/usr/bin/env python3
"""Print the exact skinny encounter coefficients."""

from src.symbolic.skinny_regularization import (
    leading_scaled_force_coefficients,
    levi_civita_transverse_displacement_coefficient,
    physical_angular_momentum_coefficient,
    physical_miss_distance_coefficient,
)


def main() -> None:
    longitudinal, transverse = leading_scaled_force_coefficients()
    displacement = levi_civita_transverse_displacement_coefficient()
    miss = physical_miss_distance_coefficient()
    angular_momentum = physical_angular_momentum_coefficient()
    print(f"scaled longitudinal force / epsilon^4 -> {longitudinal}")
    print(f"scaled transverse force / epsilon^5 -> {transverse}")
    print(f"Im(z_cross) / epsilon^5 -> {displacement}")
    print(f"r_min / epsilon^11 -> {miss}")
    print(f"h_enc / epsilon^(11/2) -> {angular_momentum}")


if __name__ == "__main__":
    main()

