#!/usr/bin/env python3
"""Replay the exact degree-six through degree-eight stable-graph derivation."""

import sympy as sp

from src.symbolic.restricted_scattering import (
    planar_joint_shape_stable_high_order_corrections,
)


def main() -> None:
    corrections, checks = planar_joint_shape_stable_high_order_corrections(8)
    for degree in range(6, 9):
        for transverse_degree, longitudinal_degree, coefficient in corrections[degree]:
            print(
                f"degree={degree} transverse={transverse_degree} "
                f"longitudinal={longitudinal_degree} "
                f"exact={sp.sstr(coefficient)} decimal={sp.N(coefficient, 30)}"
            )
    print(f"homological_checks={len(checks)}")
    print(f"all_exactly_zero={all(check == 0 for check in checks)}")


if __name__ == "__main__":
    main()
