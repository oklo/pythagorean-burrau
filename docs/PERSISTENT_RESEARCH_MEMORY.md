# Persistent research memory

> **Correction, 2026-09-05:** The one-switch scalar proof below omits a
> singular terminal integrating-factor limit. Its unconditional conclusion
> is withdrawn; the exact forced-lag identities remain valid. See
> [the endpoint correction](FORCED_LAG_ENDPOINT_CORRECTION.md) for an exact
> scalar counterexample and a corrected sufficient lemma. Separate interval
> and endpoint certificates are not withdrawn by this correction.

Last updated: 2026-09-06

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

- The authoritative paper is `paper/main.tex`, its `paper/sections/` inputs,
  and `paper/main.pdf`: **The Pythagorean Three-Body Conjecture**, September 6,
  2026, **31 pages including references**, at 11-point type and one-inch margins.
  Principal technical-companion arguments have been folded into this paper;
  `paper/technical-details.tex/pdf` remains the roughly 50-page research archive.
  The old 22-page main draft and intermediate 29/30-page versions are superseded.
  Read `HANDOFF_MANUSCRIPT_2026-09-06.md` for the current restart prompt and
  `MANUSCRIPT_REVIEW_2026-09-05.md` before relying on older theorem summaries.
- The review corrected the forced-lag endpoint gap, the launch-window logic in
  the finite-cover argument, escape-criterion ordering, and several stale or
  overbroad claims. The interval and endpoint certificates themselves were not
  withdrawn.
- The live Oklo post `https://oklo.org/2026/09/05/add-astra/` links the words
  “is here” to the deployed manuscript PDF at
  `https://oklo.org/wp-content/uploads/2026/09/pythagorean-burrau-interim-report.pdf`.
  On September 6 that file was replaced, without changing the post, by the
  latest 31-page PDF. The public download, local manuscript, and staged upload
  all had SHA-256
  `d2b50b0152d37ee0f65c3aebb39dbd771d19439187783ad5cd9e9062868c9f79`.
  The old 22-page public PDF is preserved in
  `paper/archive/oklo-interim-report-2026-09-05.pdf`.
  See `OKLO_PUBLICATION_2026-09-06.md` for provenance and safe deployment steps.
- The latest five-row blog visualization is
  `/Users/greglaughlin/Projects/burrau/plots/oklo_pythagorean_fan_trajectory_progression.png`;
  its generator and audit JSON are adjacent under `scripts/` and `data/`.
  It is an ordinary numerical illustration, not a certificate. The manuscript
  deliberately retains its separately inspected earlier snapshot and records
  both hashes in `paper/review-provenance.json`.
- Figure 1's isosceles label is inside the arc with an endpoint arrow; both
  panel titles are aligned. Figure 3 is the continued F30 trajectory, not an
  exact Pythagorean solution. Its image is copied unchanged and its return half
  is constructed by reversing the first half, explicitly disclosed in the
  caption. Its plotting residual is 2.6e-11, distinct from the campaign's
  separately refined root. The redundant defect plot is archived; Table 1
  retains all six defects. Supporting notes and the F30 plotting script from
  the unversioned `../burrau` directory are preserved in
  `paper/archive/burrau-2026-09-06/`.

## Editorial preferences to preserve

- Richard Montgomery is the technical reader, but the historical/physical
  introduction must retain genuine interest for an informed lay audience.
  Do not erase that opening or reintroduce "dance," conversational Q&A prose,
  or generic LLM-style framing.
- Exact title: **The Pythagorean Three-Body Conjecture**. Section 1 is
  **A simple plan**. There is no "working research draft" author line.
- The abstract is 144 whitespace-delimited words. Its first two sentences
  were explicitly approved; preserve them unless asked otherwise. Following
  them are the certified interval, brake criterion, thin-family result,
  first-turn exclusion, numerical status, and the unresolved global conjecture.
- The Shaquille O'Neal epigraph remains below the abstract, left-aligned to
  the abstract's margin with an added baseline of vertical space; the black
  attribution links to the supplied BrainyQuote source.
- The initial under-30-page target was explicitly relaxed on September 6.
  Do not compress the technical explanation merely to force 29 pages.
- Section 1.5 distinguishes `P intersect Q = empty` from measure zero.
  Its analytic reversible oscillator example has periodic parameters exactly
  Q; its second example has the isolated rational periodic parameter 1/3.
  These are logical counterexamples to the inference, not gravitational ones.
- The final introductory paragraph gives a **subjective 10% probability that
  at least one integer Pythagorean counterexample exists**. The user explicitly
  requested the attribution **GPT-6 Astra**. This is not a calculated probability,
  a claim about successful finite search, or evidence that the conjecture is false.

## Verification and preservation

- The consolidation pass had 190 selected existing tests passing and a
  successful independent audit of all 100 archived middle-cover tiles.
- The September 6 rationality/F30 revision had 22 targeted tests passing,
  exact oscillator-identity checks, recalculated F30 geometry, and visual PDF
  inspection. No fresh CAPD integrations or interval root proof were performed.
- Keep the reviewed compiled main PDF in Git, together with its LaTeX inputs,
  figures, companion archive, and publication record. Rebuilding may change the
  PDF hash through metadata alone; compare the actual deployed bytes when publishing.
- `../oklo-org` has no configured GitHub remote and has unrelated dirty theme,
  application, and audio work. Do not stage or deploy that work as part of a
  manuscript update. This research repository is private and has the configured
  `oklo/pythagorean-burrau` GitHub remote.

## Restart order

1. Read `HANDOFF_MANUSCRIPT_2026-09-06.md`, then
   `MANUSCRIPT_REVIEW_2026-09-05.md` and `FORCED_LAG_ENDPOINT_CORRECTION.md`.
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

## Historical planning estimate

The earlier research-planning estimate of progress toward a full resolution
was about **25%**, with a subjective range of **15--35%**. It was not a
calibrated probability or a fraction of lemmas completed; it discounted the
missing global argument. Earlier estimates near 58% were retracted. This
historical planning estimate is different from the September 6 manuscript's
subjective **10% probability of an integer counterexample existing**.
