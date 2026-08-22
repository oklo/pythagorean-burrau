#!/usr/bin/env python3
"""Print exact formulas for the skinny matching reference problem."""

from src.symbolic.skinny_matching import (
    degenerate_binary_mean_square_separation,
    exact_incoming_tilt,
    reference_collision_phase,
    reference_collision_time_gap_coefficients,
    reference_cycle_count,
    reference_cycle_count_fourth_power,
    reference_phase_asymptotic_coefficients,
    reference_phase_derivative_leading_coefficient,
    scaled_incoming_monopole_energy,
)


def main() -> None:
    print(f"reference collision phase = {reference_collision_phase()}")
    print(f"reference cycle count = {reference_cycle_count()}")
    print(f"cycle count^4 = {reference_cycle_count_fourth_power()}")
    print(f"phase coefficients = {reference_phase_asymptotic_coefficients()}")
    print(
        "epsilon^(5/2) phase derivative -> "
        f"{reference_phase_derivative_leading_coefficient()}"
    )
    print(
        "collision-time gap coefficients = "
        f"{reference_collision_time_gap_coefficients()}"
    )
    print(f"scaled incoming energy = {scaled_incoming_monopole_energy()}")
    print(f"incoming tilt = {exact_incoming_tilt()}")
    print(
        "mean binary separation squared = "
        f"{degenerate_binary_mean_square_separation()}"
    )


if __name__ == "__main__":
    main()
