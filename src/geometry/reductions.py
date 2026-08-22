"""Exact Euclid-parameter and initial-configuration reductions.

The normalized convention fixes the hypotenuse and the third mass to one.
All arithmetic entry points in this module use :class:`fractions.Fraction`.
"""

from __future__ import annotations

from dataclasses import dataclass
from fractions import Fraction
from math import gcd


@dataclass(frozen=True)
class PrimitiveTriple:
    a: int
    b: int
    c: int

    def __post_init__(self) -> None:
        if min(self.a, self.b, self.c) <= 0:
            raise ValueError("a, b, c must be positive")
        if self.a * self.a + self.b * self.b != self.c * self.c:
            raise ValueError("not a Pythagorean triple")
        if gcd(gcd(self.a, self.b), self.c) != 1:
            raise ValueError("triple is not primitive")


def normalized_masses(u: Fraction) -> tuple[Fraction, Fraction, Fraction]:
    """Return ``(A(u), B(u), 1)`` exactly for rational ``0 < u < 1``."""
    if not 0 < u < 1:
        raise ValueError("u must lie in (0, 1)")
    den = 1 + u * u
    return (1 - u * u) / den, 2 * u / den, Fraction(1)


def primitive_triple(u: Fraction) -> PrimitiveTriple:
    """Return the primitive Euclid triple represented by rational ``u``.

    If ``u=p/q`` in lowest terms, the unreduced triple is
    ``(q^2-p^2, 2pq, q^2+p^2)``.  Its common divisor is exactly two when
    ``p,q`` are both odd and exactly one otherwise.
    """
    if not 0 < u < 1:
        raise ValueError("u must lie in (0, 1)")
    p, q = u.numerator, u.denominator
    divisor = 2 if p % 2 == q % 2 == 1 else 1
    return PrimitiveTriple(
        (q * q - p * p) // divisor,
        (2 * p * q) // divisor,
        (q * q + p * p) // divisor,
    )


def euclid_parameter(triple: PrimitiveTriple) -> Fraction:
    """Recover the unique ``u in (0,1)`` for the ordered Euclid legs.

    The formula ``u=b/(a+c)`` follows from ``b/c=B(u)`` and
    ``a/c=A(u)``.  Exchanging the legs gives the involuted parameter.
    """
    return Fraction(triple.b, triple.a + triple.c)


def swap_legs(u: Fraction) -> Fraction:
    """Euclid parameter corresponding to ``A <-> B``."""
    if not 0 < u < 1:
        raise ValueError("u must lie in (0, 1)")
    return (1 - u) / (1 + u)


def normalized_positions(
    u: Fraction,
) -> tuple[tuple[Fraction, Fraction], ...]:
    """Return the exact normalized labelled initial positions."""
    a, b, _ = normalized_masses(u)
    return (
        (Fraction(-1, 2), Fraction(0)),
        (Fraction(1, 2), Fraction(0)),
        ((b * b - a * a) / 2, a * b),
    )

