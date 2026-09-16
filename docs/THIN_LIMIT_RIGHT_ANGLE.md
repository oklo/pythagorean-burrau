# Why thin Pythagorean triples plunge deeper: the right angle and the eleventh power

Evidence scope: the exact identity of Section 1 is an **EXACT SYMBOLIC
IDENTITY** (verified in rational arithmetic for every tested `u`); the
asymptotic consequence of Section 2 is **PROVED ANALYTICALLY** at the level
of the existing thin-end expansion and reproduces the constant already
proved in `SKINNY_REGULARIZATION.md` and the paper; the comparison with
generic apex angles in Section 3 is **ORDINARY NUMERICAL EVIDENCE**.
Written 2026-09-15, prompted by a question from Richard Montgomery about
whether thin triples ("one side much smaller than the other two") can be
disposed of easily.

## 1. An exact identity at launch

Conventions of `CONJECTURE.md`: masses `(m1,m2,m3)=(A,B,1)` with
`A²+B²=1`, sides `r23=A`, `r31=B`, `r12=1`. Since `r23²+r31²=r12²`, the
right angle of the launch triangle sits at the vertex opposite the
hypotenuse, that is **at body 3**:

    (q1 − q3) · (q2 − q3) = 0     exactly, for every u.

Write `X = q3 − q1` for the pair `{1,3}`, `M13 = m1+m3 = A+1`,
`a = m1/M13 = A/(A+1)`, `C = (m1q1+m3q3)/M13`, and `G = q2 − C`. Since
`q2 − q3 = G − aX`, the right angle is equivalent to

    X · G = a |X|²       exactly, for every u.

Both identities were checked in exact rational arithmetic (`u = 1/3`,
`1/10`, `2/21`, `1/24`; ratio `X·G / (a|X|²) = 1` to all digits).

For a triangle whose apex angle is *not* a right angle, `X · G` is instead
of order `|X| |G|`.

## 2. Consequence in the thin limit

Let `ε = B → 0`, so bodies 1 and 3 start at separation `ε` and body 2 is at
distance `ρ ≈ 1`. Only body 2 exerts a torque on the pair, and expanding its
two attractions about `C`,

    d(ℓ13)/dt = X × Ẍ = 3 m2 (X×G)(X·G) / ρ⁵ · (1 + O(|X|/ρ)).

By the identity above, `X·G = ½ε² + O(ε³)` at launch, one order smaller than
the generic `O(ε)`. The pair falls nearly radially, so its direction is
frozen during the first plunge, and with `m2 = ε`, `X×G = ε + O(ε²)`:

    d(ℓ13)/dt = O(ε⁴)      (Pythagorean),
    d(ℓ13)/dt = O(ε³)      (generic apex angle).

The first plunge lasts `O(ε^{3/2})`, so

    ℓ13 = O(ε^{11/2})      (Pythagorean),
    ℓ13 = O(ε^{9/2})       (generic).

For a nearly radial Kepler arc the pericenter distance is
`r_min = ℓ13²/(2 M13) · (1+o(1))`. Hence the first encounter misses
collision by `O(ε¹¹)` for Pythagorean launches and by `O(ε⁹)` otherwise.
With the value `ℓ13 = −(15π/64) ε^{11/2}` already proved by the fifth-order
Green-function computation, this returns the known constant exactly:

    (15π/64)² / 4 = 225π² / 16384 = 0.135538…,

which is the coefficient in the paper's miss-distance formula. The two
derivations agree, and the present one explains *why* the first transverse
variation appears only at order five: it is the right angle.

## 3. Numerical confirmation of both laws

Double-precision Taylor integration (`scripts/landscape/ms3.c`), minimum
`r13` over the first encounter. The mass–side family is used with `m2 = ε`
and `m1` free, so `m1 = √(1−ε²)` is the Pythagorean case and fixed `m1`
gives a generic apex angle.

| ε | Pythagorean `r_min` | `r_min/ε¹¹` | generic (`m1=0.9`) `r_min` | `r_min/ε⁹` | generic `r_min/ε¹¹` |
| --- | --- | --- | --- | --- | --- |
| 0.26 | 5.90e-8 | 0.161 | 5.76e-7 | 0.106 | 1.6 |
| 0.22 | 8.92e-9 | 0.153 | 1.66e-7 | 0.138 | 2.8 |
| 0.19 | 1.73e-9 | 0.148 | 5.41e-8 | 0.168 | 4.6 |
| 0.16 | 2.54e-10 | 0.144 | 1.36e-8 | 0.198 | 7.7 |
| 0.14 | — | — | 4.30e-9 | 0.208 | 10.6 |

The Pythagorean quotient converges to the predicted `0.1355`; the generic
quotient against `ε¹¹` grows without bound, while against `ε⁹` it stays near
`0.2`. Local log-log slopes make the two exponents explicit. For the
Pythagorean family the measured slope over consecutive pairs is `11.31`,
`11.20`, `11.15`, settling on eleven. For the generic triangle it is `7.45`,
`7.65`, `8.03`, `8.63`, rising toward nine; the approach is slower because
the relative correction there is `O(ε)` against a leading term two orders
larger, so the asymptotic regime sets in later. Both are consistent with the
torque argument of Section 2 and inconsistent with the other exponent. The same law is visible directly in the tied family: predicted
`0.1355 B¹¹` against observed first-passage minima, e.g. `u=2/21`
(`1.47e-9` vs `1.6e-9`), `u=1/10` (`2.49e-9` vs `2.7e-9`), `u=2/17`
(`1.43e-8` vs `1.6e-8`), `u=1/6` (`5.66e-7` vs `7.5e-7`).

## 4. What this does and does not do for the thin end

It does explain that thin Pythagorean triples are a *degenerate* case of
thin triangles: the Pythagorean locus is exactly where the leading tidal
torque on the tight pair vanishes at launch. Their first encounters are two
orders deeper than generic, so the near-collision is cleaner and the
asymptotics sharper, but the passage is a passage of the *selected* pair and
is therefore regular in the Levi–Civita chart used by the certificates
(`SMALL_TRIPLE_CERTIFICATES.md`).

It does not by itself exclude thin triples. The first encounter, the full
incoming matching, the escape windows, and the uniform first-turn exclusion
are already proved (paper, Section on thin triangles). What remains is the
returning set: a positive-measure set of binary phases returns for a second
central encounter instead of escaping, and each return presents a fresh
phase. A uniform thin-end theorem therefore requires a classification of the
returning orbits of the restricted problem (rectilinear equal-mass binary
plus massless particle), excluding simultaneous vanishing of the particle
velocity and the binary velocity at every later turn. That is the same
obstruction as in the general case, in its cleanest available form.

## 5. A tested idea that does not close the thin end

Since a brake forces every pair angular momentum to vanish, and since zero
total angular momentum ties them together by
`mu1 l13 + mu2 (Y x Ydot) = 0`, it is enough to keep `l13` away from zero at
the outer turns, which are the only times the outer body is at rest. Two
scales compete. The central encounter leaves `l13` of order `eps^{5/2}`
(this is the uniform first-turn estimate, restated for the pair: the turn
value of `Y x Ydot` is of order `eps^{3/2}`), while between encounters the
tidal torque `3 m2 (X x G)(X . G)/rho^5` drifts `l13` by order `eps^3` over
an excursion. For small `eps` the kick beats the drift, which would exclude
a brake at every turn.

The idea fails at accessible parameters because the coefficient in front of
`eps^{5/2}` is not uniformly of order one. Direct integration of the first
outer turn (`scripts/landscape/thinturn.c`) gives

| `u` | `eps` | `l13 / eps^{5/2}` at the first turn | `(Y x Ydot)/eps^{3/2}` |
| --- | --- | --- | --- |
| 1/8 | 0.2462 | −0.074 | +0.041 |
| 2/13 | 0.3006 | −0.0068 | +0.0038 |

The value `W_inf/2 > 0.21` proved in the paper is the limit along the
*centered parabolic phase*; at a generic returning phase the turn value is
one to two orders smaller. With a coefficient `c ~ 10^{-2}`, the kick
`c eps^{5/2}` exceeds the drift `eps^3` only once `eps^{1/2} << c`, that is
for `eps` below about `10^{-4}`, far thinner than any accessible triple.
The separation of the two scales is therefore available only inside the
asymptotic regime the paper already exploits, and this route adds nothing
outside it.

The same probe records a practical fact for anyone building thin-end
certificates: after the first central encounter the pair labels generally
change, so a fixed `{1,3}` chart stops describing the tight pair and a
chart itinerary must follow the exchange.
