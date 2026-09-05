# Persistent research memory

> **Correction, 2026-09-05:** The one-switch scalar proof below omits a
> singular terminal integrating-factor limit. Its unconditional conclusion
> is withdrawn; the exact forced-lag identities remain valid. See
> [the endpoint correction](FORCED_LAG_ENDPOINT_CORRECTION.md) for an exact
> scalar counterexample and a corrected sufficient lemma. Separate interval
> and endpoint certificates are not withdrawn by this correction.

Last updated: 2026-09-05

## State in one paragraph

The Pythagorean--Burrau nonperiodicity conjecture is **unresolved**, as is the
stronger real-parameter conjecture. No exact real second-brake intersection
and no rational counterexample candidate are known. The strongest established
results remain Level D/E: infinitely many primitive triples are proved
nonperiodic in skinny and near-isosceles regimes; a positive-density subset of
the explicit family $(4n^2-1,4n,4n^2+1)$ is covered; and every real
$u\in[0.29,0.2900000101]$ has a committed, gap-free CAPD nonperiodicity
certificate. The wider affine-generator interval $[0.29,0.290002]$ remains a
**VALIDATED NUMERICAL RESULT / COMPUTER-ASSISTED THEOREM CANDIDATE** pending
independent audit of the affine inclusion algebra and its implementation. A
2026-09-05 construction campaign found no counterexample and no nearly
singular tied shooting root.

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

The former claim that one positive-to-negative sign switch of $E$ alone forces
$w>0$ before the terminal syzygy is **withdrawn**. The integrating factor is
singular at the terminal endpoint, so $w(S)=0$ does not imply that the weighted
quantity tends to zero. The corrected sufficient lemma additionally requires
the endpoint condition

\[
 \liminf_{s\uparrow S} M(s)w(s)\ge 0,
 \qquad
 M(s)=\exp\!\left(\int^s(\lambda+c)\,d\sigma\right).
\]

An exact scalar counterexample in `FORCED_LAG_ENDPOINT_CORRECTION.md` shows
that this is a real logical requirement, not a technical nicety. The current
analytic target is therefore a brake-generated history estimate proving this
terminal bound together with suitable forcing control, or a different global
obstruction that bypasses the singular endpoint.

Do not try to prove it from only static energy/sign constraints.  Exact
rational energy-compatible ambient witnesses disprove pointwise one-way
crossing of $E=0$ and invariance of the natural buffered contact barrier.
The witnesses are recorded in `EXACT_REDUCTIONS.md`, `FAILED_ROUTES.md`, and
symbolic regression tests. They are not asserted reachable from the brake.

## Counterexample-construction frontier

The pair-adaptive Levi--Civita shooting campaign in
`PERIODIC_CONSTRUCTION_REPORT_2026-09-05.md` completed the F1, F2, F3, F4, F5,
and F30 mass--side continuations. All six ordinary-numerical shooting matrices
were full rank, and all tied-right defects were nonzero. F30 remains the
closest selected periodic seed, with Pythagorean defect about
$-0.00335599726517$. Direct searches on the exact tied-right first-$I$-maximum
branches returned nonzero brake residuals. These computations exclude neither
later returns nor an undiscovered organizer; they provide no exact real or
rational candidate.

## Manuscript, figure, and public handoff

- `paper/main.pdf` is the reviewed 22-page main argument; the technical
  companion is about 50 pages. Read `MANUSCRIPT_REVIEW_2026-09-05.md` before
  relying on older theorem summaries.
- The review corrected the forced-lag endpoint gap, the launch-window logic in
  the finite-cover argument, escape-criterion ordering, and several stale or
  overbroad claims. The interval and endpoint certificates themselves were not
  withdrawn.
- The live Oklo post `https://oklo.org/2026/09/05/add-astra/` links the words
  “is here” to the deployed manuscript PDF at
  `https://oklo.org/wp-content/uploads/2026/09/pythagorean-burrau-interim-report.pdf`.
- The latest five-row blog visualization is
  `/Users/greglaughlin/Projects/burrau/plots/oklo_pythagorean_fan_trajectory_progression.png`;
  its generator and audit JSON are adjacent under `scripts/` and `data/`.
  It is an ordinary numerical illustration, not a certificate. The manuscript
  deliberately retains its separately inspected earlier snapshot and records
  both hashes in `paper/review-provenance.json`.

## Restart order

1. Read `MANUSCRIPT_REVIEW_2026-09-05.md` and
   `FORCED_LAG_ENDPOINT_CORRECTION.md` first.
2. Read `STATUS.md`, `PROOF_OBLIGATIONS.md`, and
   `PERIODIC_CONSTRUCTION_REPORT_2026-09-05.md`; use the August handoff only
   with its superseding correction notice.
3. Re-run the targeted exact/symbolic and periodic-atlas regression suites
   listed in those reports before changing theorem status.
4. On the analytic route, prove the missing terminal integrating-factor bound
   from brake-generated history, or replace that route with a genuinely global
   scalar obstruction.
5. On the construction route, seek an actual collision/symmetry organizer
   whose collision-free unfolding meets the tied-right curve. More unrelated
   isolated numerical roots are low leverage.
6. Do not make affine-tile widening the primary attack. Local width does not
   bridge the unresolved global parameter continuum.

## Honest completion estimate

The last calibrated estimate toward a full resolution was about **25%**, with
a credible range of **15--35%**.  This is not a fraction of lemmas completed;
it discounts heavily for the still-missing global bridge across the middle
parameter range.  Earlier estimates near 58% were retracted as too optimistic.
