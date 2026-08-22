from fractions import Fraction

import pytest

from src.geometry.reductions import (
    PrimitiveTriple,
    euclid_parameter,
    normalized_masses,
    normalized_positions,
    primitive_triple,
    swap_legs,
)


@pytest.mark.parametrize(
    ("u", "expected"),
    [
        (Fraction(1, 2), PrimitiveTriple(3, 4, 5)),
        (Fraction(1, 3), PrimitiveTriple(4, 3, 5)),
        (Fraction(3, 5), PrimitiveTriple(8, 15, 17)),
        (Fraction(1, 5), PrimitiveTriple(12, 5, 13)),
    ],
)
def test_primitive_triple(u: Fraction, expected: PrimitiveTriple) -> None:
    triple = primitive_triple(u)
    assert triple == expected
    assert euclid_parameter(triple) == u


def test_normalized_geometry() -> None:
    u = Fraction(1, 2)
    a, b, c = normalized_masses(u)
    q1, q2, q3 = normalized_positions(u)

    def squared_distance(x: tuple[Fraction, Fraction], y: tuple[Fraction, Fraction]) -> Fraction:
        return (x[0] - y[0]) ** 2 + (x[1] - y[1]) ** 2

    assert a * a + b * b == 1
    assert squared_distance(q2, q3) == a * a
    assert squared_distance(q1, q3) == b * b
    assert squared_distance(q1, q2) == c * c


@pytest.mark.parametrize("u", [Fraction(1, 2), Fraction(1, 3), Fraction(3, 7)])
def test_leg_swap_is_involution_and_swaps_masses(u: Fraction) -> None:
    v = swap_legs(u)
    assert swap_legs(v) == u
    a, b, _ = normalized_masses(u)
    swapped_a, swapped_b, _ = normalized_masses(v)
    assert (swapped_a, swapped_b) == (b, a)

