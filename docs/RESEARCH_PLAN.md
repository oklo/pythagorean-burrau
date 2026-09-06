# Research plan: resolve the conjecture

The deliverable is a proof for every integer Pythagorean launch, or one
rigorously established collision-free periodic counterexample. The stronger
real-parameter conjecture is a useful target, not a substitute definition
of the integer question. The [working paper](../paper/main.pdf) is the
primary interim product: keep its claims synchronized with the ledger.

## 1. Seek an all-time obstruction

**Decision to reach:** can the existing reductions control every later brake,
not just the first ordered arc, first inertia maximum, or first thin turn?

Two concrete possibilities deserve mathematical work:

- Derive a restriction on brake-generated history that survives the singular
  syzygy endpoint. For the forced-lag route this means proving both forcing
  control and the missing weighted terminal bound, then specifying how the
  argument treats subsequent arcs. The scalar lemma is already corrected;
  another proof of that conditional lemma is not the missing result.
- Construct a return-map or itinerary obstruction with a quantified domain,
  collision-boundary treatment, and a rule excluding arbitrarily many
  returns. Use the existing thin matching, planar collision charts, and
  first-turn angular-momentum estimate as local ingredients. Do not assume
  they already classify all return sequences.

The next written deliverable should be a precise proposed global lemma and
its dependencies, or a decisive counterexample to that proposed lemma.
Targeted numerical probes can test its hypotheses; they cannot establish
the all-time quantifier. If only a first-arc statement emerges, record it
as such and identify the remaining extension, rather than relabelling it
a global strategy. See [P1](PROOF_OBLIGATIONS.md).

## 2. Seek an exact counterexample mechanism

**Decision to reach:** is there a collision-free second brake on the exact
tied-right family? Only after such a real intersection is established does
rationality become a concrete candidate-specific question.

The September 5 campaign found six non-Pythagorean mass–side candidates and
no tied-right root. F30 is a useful nearby orbit, not an unresolved numerical
zero. Repeating its refinement or collecting unrelated roots has low value
unless a new geometric connection is being tested.

The next useful construction should specify a continuous periodic branch,
a justified symmetry condition, or a collision-boundary unfolding whose
intersection with the exact tied-right curve can actually be tested.
Read [the symmetry audit](PERIODIC_SYMMETRY_AUDIT.md) first: reflection
does not automatically reduce two residuals to one, rank deficiency alone
does not produce a branch, and unrelated defect signs are not a bracket.
Reflection events need not be inertia maxima; do not conflate a reflected
velocity condition with an actual second brake.

For any candidate, report the complete residual, independent high-precision
replay, chart itinerary, collision margins, and exact launch constraints.
Promotion requires validated existence and collision-free flow. An integer
counterexample further requires an exact rational Euclid parameter; neither
a tiny defect nor rational reconstruction from floating-point digits suffices.
See [C1–C2](PROOF_OBLIGATIONS.md).

## Supporting audits, with bounded scope

1. **Recovered 3–4–5 record:** audit source provenance and replay the full
   repaired certificate if a rigorous classical example would strengthen
   the paper. This is a useful point result, not the universal proof.
2. **Affine inclusion algebra:** independently audit the wider candidate
   before promoting `[0.29,0.290002]`. Until then use the narrower accepted
   all-time interval. Do not make another width campaign the default task.
3. **Reproduction:** preserve exact inputs, source/version hashes, rounding
   assumptions, and outputs supporting a theorem. Keep the standard checks
   inexpensive enough to run after meaningful changes.

## Experiment contract

Before a substantial computation, record these six items in one short note:

1. The mathematical claim or construction being tested.
2. Which open obligation it would resolve or discriminate between.
3. Exact parameter domain, event/return scope, and numerical method.
4. The observable outcome that would change the research decision.
5. Validation needed before changing the paper's claim status.
6. A bounded stopping criterion and the result of stopping without success.

Use one named output record, not another agent-specific repository or a new
general experiment diary. Keep a negative result when it rules out a real
idea or documents a reproducibility failure. Archive superseded traces and
regenerate caches. A tolerance sweep without a mathematical decision is not
an active research priority.

## Completion standards

A universal proof must cover all rational parameters and every relevant
positive time before collision, with each exceptional set handled explicitly.
A real-family proof would imply it. An exact real periodic orbit alone
would refute only the stronger conjecture; an integer counterexample needs
rationality. A finite search with no result proves neither conjecture.
There is no meaningful percentage-of-proof metric for the remaining gap.
