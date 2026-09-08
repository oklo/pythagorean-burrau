# Proof obligations

The target is the exact [labelled classical conjecture](CONJECTURE.md).
This decision-level list supersedes the 1,151-line campaign accumulation,
preserved in `../archive/history/guides/PROOF_OBLIGATIONS.md`.

## What would finish the project

Either produce:

1. **A proof:** for every rational `0<u<sqrt(2)-1`, no positive second brake
   occurs before the first collision. A proof for every real parameter would
   suffice but is stronger than necessary.
2. **A counterexample:** an exact rational `u` with a positive second brake
   and a validated collision-free segment from launch to that brake. Time
   reversal then gives a labelled inertial periodic orbit.

An exact real periodic point alone would refute only the stronger conjecture.
No finite tolerance establishes rationality. Measure zero, countability,
isolated roots, and dimension counting cannot replace an arithmetic argument.

## P1. All-time obstruction on the remaining family

Show that every inertia-maximum branch has nonzero complete brake residual,
or find another structural obstruction that avoids enumerating branches.
Any proof must account for:

- arbitrarily many close encounters and potentially unbounded return times;
- branch creation/termination, degenerate events, collisions, and escape;
- changes of side ordering, orientation, and syzygy itinerary;
- the thin-end accumulation and every component not covered by current
  collision-or-escape neighborhoods;
- regular coordinate changes, including Jacobi degeneracies.

A finite-time scan, a collection of regular local branches, or a growing set
of isolated rational exclusions does not discharge P1. A covering strategy
needs a termination/compactness argument appropriate to its remaining domain.

### P1a. If pursuing torque history

**Update 2026-09-07.** The first-arc conclusion (no brake before the first
syzygy) is now a theorem for every real `u` and every mass triple, by time
reversal about a putative second brake and Montgomery's infinitely-many-
syzygies theorem; see [the reversal structure](SYZYGY_REVERSAL_STRUCTURE.md).
The forced-lag route is therefore no longer needed for P1a's stated goal;
its identities remain available for later arcs. The remaining obligation is
the bridge to all later arcs, now in the sharper form: exclude fixed points of
the involution `R∘P` on the syzygy section along the tied syzygy curves, i.e.
exclude brakes on stutter arcs.

On the first strict ordered positive-area arc, use the exact equation
`w_s + (lambda+c) w = q`, with `w=h-eta`. The corrected sufficient lemma
requires suitable forcing control **and**

\[
\liminf_{s\uparrow S} M(s)w(s)\ge0,
\qquad M(s)=\exp\!\left(\int_{s_0}^s(\lambda+c)\,d\sigma\right),\quad s_0>0.
\]

Derive this from the actual brake-generated history, or replace the argument.
Unweighted `w(S)=0` is insufficient. Exact ambient witnesses rule out the
tested static energy/sign shortcuts; they are not claimed brake-reachable.
Even a successful first-arc lemma still needs an explicit bridge to all later
arcs before it can settle the conjecture.

### P1b. If pursuing the thin return map

The local collision roots and uniform first-turn exclusion are available.
The missing result is a global return/collision/escape classification through
subsequent encounters, including the accumulating boundary layers. An exact
collision in the restricted limit is not by itself a rational collision or
a collision-free periodic positive-mass orbit.

## C1. Construct an exact tied-right second brake

The generic mass–side shooting problem already uses five equations in five
unknowns. Its six sampled nonsingular roots have nonzero right-angle defect.
More digits or radial projection do not supply a sixth tuning parameter.

A credible construction needs a specific mechanism: a rigorously controlled
organizing collision/symmetry, a proven dependency among constraints along an
actual itinerary, or an exact intersection argument on a verified connected
solution family. State and test that mechanism before launching continuation.
Rank four alone does not prove a branch; opposing defects at unrelated roots
do not bracket a zero.

For a numerical candidate, retain the complete labelled velocities, physical
clock, all pair separations, energy diagnostics, and independent replay.
Reflection shooting at a transverse syzygy is an alternative construction
section, but its two residuals remain two equations for the single tied-right
parameter. A reflection encounter need not be an inertia maximum.

## C2. Arithmetic and validation

Only after obtaining a credible exact-family candidate should rational
reconstruction be attempted. A final counterexample must include:

- an exact rational launch parameter and its primitive integer triple;
- a validated root/existence mechanism at that fixed rational parameter;
- a collision-free tube for the entire brake-to-brake interval;
- a complete brake condition, not just a reduced component or plotted return;
- a reproducible proof with pinned dependencies and independent checking.

If only an irrational real root is established, label its significance correctly
and retain the integer problem as open.

## Supporting audit gates, not substitute goals

- Audit the wider affine inclusion algebra before promoting `[0.29,0.290002]`.
- Resolve the recovered 3–4–5 log's relationship to the later damped-write
  correction before promoting it. An old PASS must not overwrite newer audits.
- Derive an effective near-isosceles cutoff only if the planned global argument
  needs it; the existential theorem already proves a genuine infinite family.

For each proposed campaign, specify which obligation above it addresses, the
new result sought, the evidence required, and a stopping condition. See the
[research plan](RESEARCH_PLAN.md). Runtime tuning without such a use is deferred.
