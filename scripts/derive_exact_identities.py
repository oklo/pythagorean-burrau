#!/usr/bin/env python3
"""Print deterministic exact reductions and fail on any nonzero residual."""

from src.symbolic.initial_identities import (
    center_of_mass,
    expected_identities,
    identity_residuals,
)


def main() -> None:
    residuals = identity_residuals()
    print(f"normalized center of mass = {center_of_mass()}")
    for name, expression in expected_identities().items():
        print(f"{name} = {expression}")
    print(f"residuals = {residuals}")
    if any(value != 0 for value in residuals.values()):
        raise SystemExit("an exact symbolic identity failed")


if __name__ == "__main__":
    main()

