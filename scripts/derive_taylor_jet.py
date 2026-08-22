#!/usr/bin/env python3
"""Derive the fourth defect jet and print its exact Sturm certificate."""

import sympy as sp

from src.symbolic.initial_identities import (
    defect_fourth_numerator,
    euclid_symbols,
    expected_defect_fourth_derivative,
    pythagorean_defect_fourth_derivative,
)


def sign_variations(values: list[sp.Expr]) -> int:
    signs = [sp.sign(value) for value in values if value != 0]
    if any(sign not in (-1, 1) for sign in signs):
        raise ValueError("Sturm endpoint signs were not decided exactly")
    return sum(left != right for left, right in zip(signs, signs[1:], strict=False))


def main() -> None:
    u, _, _ = euclid_symbols()
    actual = pythagorean_defect_fourth_derivative()
    expected = expected_defect_fourth_derivative()
    residual = sp.factor(sp.cancel(actual - expected))
    if residual != 0:
        raise SystemExit(f"fourth-derivative identity failed: {residual}")

    polynomial = defect_fourth_numerator()
    upper = sp.Rational(83, 200)
    sturm_sequence = sp.sturm(polynomial, u)
    variations_at_zero = sign_variations([item.subs(u, 0) for item in sturm_sequence])
    variations_at_upper = sign_variations([item.subs(u, upper) for item in sturm_sequence])
    root_count = variations_at_zero - variations_at_upper
    print(f"D4 = {expected}")
    print(f"Sturm sequence length = {len(sturm_sequence)}")
    print(f"variations at 0 = {variations_at_zero}")
    print(f"variations at 83/200 = {variations_at_upper}")
    print(f"roots in (0,83/200) = {root_count}")
    if root_count != 0 or polynomial.subs(u, 0) != -1:
        raise SystemExit("fourth-derivative sign certificate failed")


if __name__ == "__main__":
    main()

