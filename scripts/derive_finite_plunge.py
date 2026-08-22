#!/usr/bin/env python3
"""Print exact finite-epsilon coefficients around the skinny plunge."""

from src.symbolic.finite_plunge import (
    exact_initial_scaled_outer_energy,
    exact_symmetric_accelerations,
    taylor_coefficients,
)


def main() -> None:
    labels = ("R_x''", "Z_y''", "Z_x''")
    for label, expression in zip(labels, exact_symmetric_accelerations(), strict=True):
        print(f"{label} coefficients = {taylor_coefficients(expression)}")
    print(f"initial scaled outer energy = {exact_initial_scaled_outer_energy()}")


if __name__ == "__main__":
    main()
