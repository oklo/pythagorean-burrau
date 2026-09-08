# Lessons from recent AI-assisted disproofs, and what they mean here

Evidence scope: this is a strategy note (analysis and ORDINARY NUMERICAL
EVIDENCE), not a theorem record. Written 2026-09-07 after the window and
point certificates; see `SYZYGY_REVERSAL_STRUCTURE.md` for the theorems it
relies on.

## 1. What the 2026 disproofs actually did

| Conjecture (age) | Who / system | How the counterexample was found | Why humans missed it |
| --- | --- | --- | --- |
| Erdős unit-distance upper bound (1946) | OpenAI model, May 2026; formalized by Sol | Construction in a number field with an infinite class-field tower (Golod–Shafarevich) projected to the plane; an existence argument, then explicit families | Belief in the bound after decades of failed attacks; the tools came from a distant field |
| Grothendieck's group-scheme conjecture (~60 y) | Fable / Sol, July 2026 | Explicit order-4 group scheme, found by searching small presentations; 1,076-line Lean proof | "Nobody had spent enough time on it" |
| Jacobian conjecture, n = 3 (1939) | Fable with L. Alpöge, July 2026 | Degree-7 polynomial map; Tao's digestion: the map is a product `L·Q` of linear and quadratic forms, locally but not globally injective, with a resultant normalization and a lucky affine chart; built on a 1998 construction | Assumed true; the obstruction is elementary in hindsight |
| Litvak's Gaussian-minima conjecture | AlphaEvolve black-box minimization | Numerical minimizer, then recognition of the exact optimizer (a cosine), then a proof | Numerical exploration had been shallow |
| Davies–Jenssen–Perkins–Roberts ratio conjecture | FAR pipeline, 2026 | Explicit graph family `C5 □ K_{m,m}`, ratio computed exactly | Nobody tested that family |
| Earlier: Wagner 2021, PatternBoost 2024, tree log-concavity 2025 | RL / transformer-guided search | Score = conjecture violation; search over discrete objects; the best ones were then understood by hand | Search spaces too large for hand exploration |

Common features. Every counterexample lived in a **discrete or algebraic
space with cheap exact verification**: a polynomial map, a finite group
scheme, a graph, a distribution with a closed form. The AI's contribution was
(i) *willingness to search where consensus said not to*, (ii) *recombining
distant tools* (class-field towers for a geometry problem), and (iii)
*volume*: many candidates evaluated exactly. In none of them did the AI
overturn a codimension count; in each there was a construction space of
positive dimension in which the sought object was an ordinary point once
the right space was chosen.

Human "surprising" counterexamples fit the same pattern: Elkies' fourth
powers (reduce to rational points on an elliptic curve, then search),
Gardam's unit conjecture (reduce to a finite SAT problem in one virtually
abelian group), Santos' Hirsch counterexample (a general reduction theorem
plus one special polytope), Kahn–Kalai's Borsuk counterexample (a
combinatorial construction in high dimension). The recipe is: **find a
reduction that turns an infinite search into a structured finite one, then
search hard**.

## 2. Why the Pythagorean problem resists that recipe

A second brake at parameter `u` is a codimension-two condition on a
one-parameter *transcendental* curve (`SYZYGY_REVERSAL_STRUCTURE.md`,
Theorem D: `σ_n(u)` must hit the two-dimensional fixed set of `R∘P` inside a
four-dimensional section). The only way a codimension count is beaten is
symmetry, and the tied family has exactly one point with an extra symmetry,
the isosceles endpoint `u=√2−1`, which is irrational and collides. There is
no algebraic construction space: the "objects" are rationals, and the
condition is an equality between transcendental quantities that no finite
computation can verify for a given rational unless a mechanism forces it.
This is the structural reason the consensus is probably right, and it is a
different situation from every 2026 disproof.

Two possible mechanisms were examined and excluded on the tied family:

* **Orthogonal syzygy crossings** (the Moeckel–Montgomery–Venturelli route to
  periodic brake orbits: the orbit meets the collinear set with `İ=0` and
  `𝒥=av−rc=0` at its `k`-th syzygy, giving a period-`4T_k` orbit). At the
  first syzygy this is excluded on the whole family since `İ<0` there (their
  Conjecture 1, verified numerically on 170,000 parameters); at later
  syzygies it is again two conditions on one parameter. The family-wide
  scan of the normalized residual `(İ_n, 𝒥_n)` at every syzygy is recorded
  below.
* **Restricted symmetric brakes at the thin end**: the light body at rest on
  the binary's axis at apocenter is a two-condition problem in the
  restricted limit, hence solvable, but the finite-mass transverse
  condition adds a third condition (the transverse Wronskian), so the count
  is unchanged.

## 3. What the recipe does suggest, and what was done

1. **Search with the right detector.** By Theorem B, a near-brake makes the
   syzygy itinerary retrace itself; the length of the palindrome centred on a
   stutter measures how long the mirrored motion tracks the original, i.e.
   `log(1/K_min)`. On the existing scans the longest palindromes are 188
   letters (`u≈0.330820`, the smallest kinetic-energy minimum found,
   `4×10^{-6}U_0`) and 182 letters (`u≈0.247032`). This is a cheap,
   integration-tolerant detector that needs no event refinement, and it
   ranks candidates the energy scan missed.
2. **Continue near-misses into the mass–side plane** (done:
   `data/mass_side_periodic_atlas.json`). The right-angle defect of the
   nearest periodic orbits is a *measurement* of how far the circle passes
   from each periodic point; the smallest is `−3.29×10^{-6}`, confirmed at
   30 digits. Under a generic model these distances shrink like
   `N^{-1/2}` with the number `N` of arcs examined and never vanish.
3. **Test rationality of every refined near-miss.** The sixteen deepest
   refined near-misses (minimal kinetic energy from `7×10^{-9}U_0` at
   `u^*=0.2003099994729`, `t=7.91`, and `8×10^{-9}U_0` at
   `u^*=0.2556321825840`, `t=4.79`, up to `1.5×10^{-6}U_0`) are located to
   about `10^{-13}` in `u`; the nearest rationals with denominator at most
   2000 lie at distances `2×10^{-8}` to `7×10^{-7}`, i.e. at the level
   expected by chance for sixteen random reals. A genuine rational
   counterexample would show as a residual that keeps decreasing with
   precision at a fixed rational, and none does. Scan of the normalized
   orthogonal-crossing residual `(İ_n,𝒥_n)` at every syzygy of 14,814
   trajectories: `İ_n<0` at every first syzygy (largest `−4.5×10^{-6}`,
   at the thin end); smallest residual at syzygies 2–7 between `0.59`
   and `0.015`; smallest overall `3.6×10^{-4}` (syzygy 91, `u≈0.26034`,
   `t≈13.1`).
4. **Look where the consensus has not looked**: the chaotic returning set
   near collision parameters (`REAL_COLLISION_SAMPLING.md`), where itineraries
   are longest and the near-miss density is highest. The scans at step
   `2×10^{-6}` already reach it; finer adaptive scans there are the only
   remaining numerical frontier, and they can lower the record near-miss
   but cannot certify a zero.

## 4. Honest verdict

The AI-disproof playbook works when a conjecture is a universal statement
over a rich space that nobody searched systematically. Here the space has
been searched (170,000 parameters, refinement to `10^{-13}` in `u`,
seventeen continued periodic orbits), the codimension is two, and the one
symmetric point is irrational. A counterexample would have to be a numerical
coincidence at a rational parameter, which no search can establish and no
known mechanism produces. The productive use of these tools on this problem
is the certification programme (now 3.9 percent of all primitive triples plus
named small triples) and the reversal reformulation, not counterexample
hunting.
