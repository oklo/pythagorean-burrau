# Persistent research memory

Last updated: 2026-08-26

## State in one paragraph

The Pythagorean--Burrau nonperiodicity conjecture is **unresolved**, as is the
stronger real-parameter conjecture.  No exact real second-brake intersection
and no rational counterexample candidate are known.  The repository contains
major Level-D/Level-E partial results: infinitely many primitive triples are
proved nonperiodic in skinny and near-isosceles regimes; a positive-density
subset of the explicit family $(4n^2-1,4n,4n^2+1)$ is covered; and every real
$u\in[0.29,0.2900000101]$ has a committed CAPD nonperiodicity certificate.
The wider affine-generator interval $[0.29,0.290002]$ is only a
**VALIDATED NUMERICAL RESULT / COMPUTER-ASSISTED THEOREM CANDIDATE** until its
independent algebra/source audit is complete.

## Current analytic frontier

On a strict ordered positive-area arc, put

\[
 d=h-k>0,\qquad e=\eta-k,\qquad w=h-\eta.
\]

The exact history dynamics are

\[
 e_s+(\lambda+c)e=cd,
 \qquad
 w_s+(\lambda+c)w=q,
 \qquad q=d_s+\lambda d,
 \qquad \lambda,c>0.
\]

Equivalently,

\[
 E:=W\delta q=Z(d_xX+d_yY)+m\delta^2(y^{-3}-1)d.
\]

If $E$ changes sign at most once, from positive to negative, before the first
terminal syzygy where $w=0$, then the integrating-factor equation proves
$w>0$ on the full interior.  This conditional one-switch lemma is
**PROVED ANALYTICALLY**.  Proving the one-switch property on brake-reachable
trajectories is the smallest current global analytic target.

Do not try to prove it from only static energy/sign constraints.  Exact
rational energy-compatible ambient witnesses disprove pointwise one-way
crossing of $E=0$ and invariance of the natural buffered contact barrier.
The witnesses are recorded in `EXACT_REDUCTIONS.md`, `FAILED_ROUTES.md`, and
symbolic regression tests.  They are not asserted reachable from the brake.

## Restart order

1. Read `STOPPING_POINT_HANDOFF_2026-08-26.md`.
2. Read the current `STATUS.md`, `PROOF_OBLIGATIONS.md`, and the torque-history
   portion of `EXACT_REDUCTIONS.md`.
3. Run the 41-test mutual-distance regression command in the handoff.
4. Work on an integrated brake-history contraction/amplitude estimate, or a
   uniform validated certificate for the reachable one-switch property.
5. Do not resume affine-tile widening as the primary analytic attack; it adds
   local width but does not address the global parameter continuum.

## Honest completion estimate

The last calibrated estimate toward a full resolution was about **25%**, with
a credible range of **15--35%**.  This is not a fraction of lemmas completed;
it discounts heavily for the still-missing global bridge across the middle
parameter range.  Earlier estimates near 58% were retracted as too optimistic.
