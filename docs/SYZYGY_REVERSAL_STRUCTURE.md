# Reversal structure of second brakes: syzygies, stutters, and the first arc

Evidence scope: the theorems in this note are **PROVED ANALYTICALLY**, using
one published theorem of Montgomery as input. The numerical statements at the
end are **ORDINARY NUMERICAL EVIDENCE** and are labelled as such. Conventions
follow `CONJECTURE.md`: planar three-body problem, zero total momentum and
angular momentum, the initial condition is a noncollinear brake (all
velocities zero) with initial potential value `U0`, and a *syzygy* is a
collinear instant. Binary collisions end the classical solution and are not
counted as syzygies here.

Written 2026-09-07. Relation to the existing programme: Theorem A closes the
first-arc objective of the forced-lag route (`PROOF_OBLIGATIONS.md`, P1a)
unconditionally; Theorems B and C reformulate every later brake as a fixed
point of an explicit involution on the syzygy section.

## Input from the literature

**Montgomery's syzygy theorem** (R. Montgomery, *Infinitely many syzygies*,
Arch. Rational Mech. Anal. 164 (2002) 311–340, Theorem 1): every bounded
zero-angular-momentum solution of the Newtonian three-body problem that has
no triple collision suffers infinitely many syzygies. The masses are
arbitrary. (Binary collisions count as syzygies in that paper; our orbits
are collision-free so the distinction is immaterial.)

The same paper (Theorem 2) proves that the normalized signed area
\[
 z=\frac{4\sqrt3\,\Delta}{r_{12}^2+r_{23}^2+r_{31}^2},\qquad
 \Delta=\tfrac12 (q_2-q_1)\times(q_3-q_1),
\]
satisfies along every zero-angular-momentum solution, away from triple
collision, the equation
\[
 \frac{d}{dt}\bigl(f\,\dot z\bigr)=-q\,z,\qquad f>0,\quad q\ge0,
\]
where `q` vanishes only on the tangent vectors of the Lagrange homothetic
solutions. Note `z` is mass independent; `|z|\le1` with equality exactly at
the equilateral shapes, and `z=0` exactly at syzygy.

Two facts already proved in this project are also used
(`PERIODIC_SYMMETRY_AUDIT.md`): every syzygy of a zero-angular-momentum
orbit launched from a noncollinear configuration is transverse, so syzygies
are isolated; and every brake of such an orbit is noncollinear.

## The reflection about a second brake

Let the orbit brake at `t=0` and, for contradiction or for analysis, again at
`t=\tau>0`, with the classical solution collision-free on `[0,\tau]`.
Uniqueness and time reversal give `q(\tau+s)=q(\tau-s)` and
`q(-s)=q(s)`, hence `q(2\tau+s)=q(s)`: the orbit is `2\tau`-periodic,
bounded, and collision-free for all time.

Write `0<s_1<\dots<s_n<\tau` for the syzygy times in `(0,\tau)` (finitely
many, by transversality and compactness; `n\ge0`). The reflection maps them
to the syzygies `2\tau-s_n<\dots<2\tau-s_1` of `(\tau,2\tau)`, with
\[
 q(2\tau-s_k)=q(s_k),\qquad \dot q(2\tau-s_k)=-\dot q(s_k).
\]

### Theorem A (no brake before the first syzygy)

For every real `u` in `(0,1)`, and indeed for every noncollinear brake initial
condition with any positive masses, the classical solution has no second
brake on `(0,\tau_1]`, where `\tau_1` is the first positive syzygy time
(or `\tau_1=\infty` if there is none).

*Proof.* Suppose a brake at `\tau\le\tau_1`. A brake is noncollinear, so
`\tau<\tau_1` and `n=0`. By the reflection there is no syzygy in
`(\tau,2\tau)` either, and `q(\tau)`, `q(0)=q(2\tau)` are noncollinear. The
`2\tau`-periodic orbit is bounded, collision-free, and has zero angular
momentum, so by Montgomery's theorem it has infinitely many syzygies. It has
none. ∎

*Remark.* This makes the forced-lag first-arc programme unnecessary as a
means of excluding brakes before the first syzygy: the corrected conditional
lemma, its missing weighted terminal bound, and the ordering hypotheses are
not needed for that purpose. What remains open is exactly what was open
before for later arcs, now in the sharper form below.

### Theorem B (a second brake is a stutter)

If the orbit brakes at `\tau` with `n\ge1` syzygies before it, then the two
syzygies adjacent to `\tau`, at `s_n` and `s_{n+1}:=2\tau-s_n`, have the
same collinear configuration, `q(s_{n+1})=q(s_n)`, with opposite
velocities; in particular they have the same middle body. The syzygy
sequence of the period is the double palindrome
\[
 (\sigma_1\sigma_2\cdots\sigma_n)(\sigma_n\cdots\sigma_2\sigma_1),
\]
repeated. Hence the forward syzygy sequence of a periodic brake orbit
contains a stutter (`11`, `22` or `33`) at every brake, and the launch brake
is likewise flanked by `\sigma_1\sigma_1`.

*Proof.* Immediate from the reflection identities. ∎

The word *stutter* is Montgomery's (Moeckel–Montgomery–Venturelli, *From
brake to syzygy*, ARMA 204 (2012), Corollary 1, where an open set of
stuttering orbits is produced from brake orbits run backwards). Theorem B
is the converse direction relevant here: **no stutter, no brake**. On any
inter-syzygy arc whose two syzygies have different middle bodies there is
no brake, with no further computation.

### Theorem C (location of a brake inside its arc)

Between two consecutive syzygies, `z` has exactly one critical point, a
strict extremum. A second brake at `\tau` lies at that extremum of its
(stutter) arc, and `I` has a strict maximum there.

*Proof.* On an arc where `z>0`, `f\dot z` is nonincreasing by Montgomery's
equation, so `\dot z` changes sign at most once; `\dot z\equiv0` on a
subinterval would force `qz=0`, i.e. a Lagrange homothetic solution, which
the orbit is not. The same holds with reversed signs on `z<0`. At a brake all
velocities vanish, so `\dot z(\tau)=0`; the inertia statement is the
Lagrange–Jacobi identity. ∎

### Theorem D (brakes as fixed points on the syzygy section)

Let `\Sigma` be the set of transverse syzygy states, `P:\Sigma\to\Sigma`
the next-syzygy map where defined, and `R(q,v)=(q,-v)` the velocity
reversal, which preserves `\Sigma`. Then `RPR=P^{-1}` on the domain of
`P`, so `RP` is an involution, and

*an inter-syzygy arc starting at `\sigma\in\Sigma` contains a brake if and
only if `RP(\sigma)=\sigma`.*

*Proof.* Reversibility of Newton's equations gives `RPR=P^{-1}`. If
`P(\sigma)=R\sigma` on an arc of duration `T`, then `q(T)=q(0)` and
`v(T)=-v(0)`, and uniqueness applied to `t\mapsto q(T-t)` gives
`q(T/2+s)=q(T/2-s)`, hence `v(T/2)=0`. Conversely a brake at `T/2` gives
`P(\sigma)=R\sigma` by Theorem B. ∎

Consequently the fixed set of `RP` consists exactly of the syzygy states of
brake-to-syzygy arcs (run backwards), i.e. the image of the
Moeckel–Montgomery–Venturelli syzygy map with velocities. For the tied family
the second-brake problem is the intersection problem between the
one-parameter syzygy curves `u\mapsto\sigma_k(u)` (the `k`-th syzygy state
of the tied trajectory) and this fixed set, a two-dimensional submanifold of
the four-dimensional reduced section. The nominal codimension count is
unchanged (three conditions, two parameters); what changes is that the
brake-reachable states are now an explicit geometric object.

### Conditional Theorem E (if MMV Conjecture 1 holds)

Moeckel, Montgomery and Venturelli conjecture (their Conjecture 1) that
`\dot I<0` from any brake through its first syzygy. If so, then on the
stutter arc `[s_n,s_{n+1}]` of a second brake, `I` increases strictly on
`[s_n,\tau)` and decreases strictly on `(\tau,s_{n+1}]`; in particular
`\dot I(s_n)>0>\dot I(s_{n+1})` and the arc contains no inertia minimum.
*Proof.* Apply the conjecture to the brake at `\tau` forwards and (by
reflection) backwards. ∎

## Consequences for certificates

1. **First arc.** The launch-window argument (`U<2U_0` gives `\dot I<0`) is
   no longer needed for brake exclusion before the first syzygy; it remains
   useful because it also proves `\dot I<0`.
2. **Combinatorial exclusion.** A validated enclosure only needs to certify
   the sequence of middle bodies at the syzygy crossings (which requires
   positive separations and a determined ordering on the line at each
   crossing, both robust to moderately wide tubes) to exclude brakes on all
   complete inter-syzygy arcs without stutters. The classical disjunction
   `K>0`, `\dot I\ne0`, `(z,P)\ne0` is still needed on stutter arcs, on the
   last incomplete arc before an escape section, and it remains the simplest
   implementation when tubes are thin anyway.
3. **Search.** Near-brakes produce stutters by continuity, so the candidate
   arcs for a counterexample are the stutter arcs; see the numerical
   landscape below.

## Numerical landscape of the tied family (ORDINARY NUMERICAL EVIDENCE)

A double-precision Taylor-series integrator in pair-adapted Jacobi
coordinates with chart switching (`archive`d scratch code, energy conserved
to `10^{-12}` through passages of `10^{-6}`) was run on `u` grids of step
`2\times10^{-5}` on `[0.10,0.4142]`, `2\times10^{-6}` on `[0.16,0.36]`, and
`10^{-6}` on `[0.36,0.4142]`, recording syzygy letters, `z`-extrema,
inertia maxima, kinetic-energy minima, and the paper's escape lemma.

* On every run (about 170,000 trajectories) each inter-syzygy arc had
  exactly one `z`-extremum (Theorem C), and the first inertia minimum never
  preceded the first syzygy (MMV Conjecture 1 on the tied family).
* Roughly half of the escaping runs have no stutter at all before the escape
  lemma fires; the median number of stutters is at most one.
* Every one of the forty smallest values of `\min K/U_0` over
  kinetic-energy minima lies on a stutter arc, as Theorem B predicts for
  near-brakes. The `K`-minima on stutter arcs are typically twenty times
  smaller than those on non-stutter arcs.
* Refining the local minima over `u` (multi-scale zoom to about `10^{-13}`
  in `u`), the closest approaches of the tied curve to a second brake found
  are at `u^*\approx0.2003099995`, `t\approx7.91`, with
  `\min K/U_0\approx7\times10^{-9}` (residual velocities about
  `2\times10^{-4}`), and `u^*\approx0.2556321826`, `t\approx4.79`, with
  `8\times10^{-9}`; the next are `7\times10^{-8}` (`u\approx0.3184400049`,
  `t\approx8.96`) and `5\times10^{-7}`. None is a zero, none sits near a
  rational of denominator at most 2000 beyond chance level, and the
  distribution of local minima is consistent with the generic
  codimension-two heuristic (`COUNTEREXAMPLE_STRATEGY_2026-09-07.md`).
* Newton continuation of the near-brakes into the two-parameter mass–side
  family produces genuine periodic brake orbits (Hopf residual below
  `10^{-7}`, several below `10^{-10}`). The smallest right-angle defect
  found is `D=m_1^2+m_2^2-1\approx-3.3\times10^{-6}` (largest angle
  `90.0002^\circ`, masses `(0.80271,0.59637,1)`, half period `27.885`),
  a thousand times closer to the Pythagorean circle than `F_{30}`; the
  next are `-1.3\times10^{-5}` and `-1.5\times10^{-5}`. All defects are
  nonzero; none is a counterexample. See `data/mass_side_periodic_atlas.json`.
