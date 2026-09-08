# Proof ledger

Current claim-level index, reviewed September 6, 2026. The expanded historical
ledger is preserved in `../archive/history/guides/PROOF_LEDGER.md`; it contains
superseded statuses and must not be used as the current authority. Detailed
identities remain in their original proof notes and regression tests.

Evidence levels are distinct: **PROVED ANALYTICALLY**, **EXACT SYMBOLIC
IDENTITY**, **PROVED BY COMPUTER-ASSISTED ARGUMENT**, **COMPUTER-ASSISTED
THEOREM CANDIDATE**, **ORDINARY NUMERICAL EVIDENCE**, **OPEN**, and
**DISPROVED**. A conditional lemma is not a proof that its hypotheses hold.

| Claim | Evidence | Supporting record and limitation |
| --- | --- | --- |
| Integer and stronger real nonperiodicity conjectures | OPEN | [Conjecture](CONJECTURE.md), [obligations](PROOF_OBLIGATIONS.md). |
| Simultaneous mass/length scaling; primitive reduction; rational Euclid parameter and leg swap | PROVED ANALYTICALLY / EXACT SYMBOLIC IDENTITY | [Exact problem](CONJECTURE.md), `tests/test_reductions.py`. |
| Collision-free free fall is periodic iff it reaches a second brake | PROVED ANALYTICALLY | [Exact problem](CONJECTURE.md); labelled inertial return, no collision continuation. |
| Hopf residual is complete at zero total momentum/angular momentum | PROVED ANALYTICALLY | [Brake map](BRAKE_MAP.md); covers syzygy and Jacobi degeneracies away from collision. |
| Every brake has `K=0`, `U=U0`, `I''=-2U0<0`, and brake-event separation bounds | PROVED ANALYTICALLY | [Event reduction](FABLE_EVENT_REDUCTION.md). No all-time separation lower bound follows. |
| Reduced kinetic energy, torque identities, and shape/event factorizations | EXACT SYMBOLIC IDENTITY | [Reduced system](REDUCED_SYSTEM.md), [exact reductions](EXACT_REDUCTIONS.md); chart hypotheses apply. |
| Ordered-cone gravitational signs and threshold inequalities | PROVED BY COMPUTER-ASSISTED ARGUMENT | [Exact reductions](EXACT_REDUCTIONS.md); exact Bernstein algebra, not a theorem of trajectory confinement. |
| Conditional forced-lag positivity with a nonnegative terminal weighted liminf | PROVED ANALYTICALLY | [Corrected lemma](FORCED_LAG_ENDPOINT_CORRECTION.md); the terminal hypothesis remains OPEN for the full family, but the first-arc conclusion it was meant to deliver now follows unconditionally from Theorem A of the [reversal structure](SYZYGY_REVERSAL_STRUCTURE.md). |
| One forcing switch plus unweighted terminal `w=0` suffices | DISPROVED | Exact scalar counterexample in [the correction](FORCED_LAG_ENDPOINT_CORRECTION.md) and `tests/test_forced_lag_endpoint.py`. |
| No second brake at or before the first syzygy, for every real `u` and every noncollinear brake initial condition (any masses) | PROVED ANALYTICALLY (uses Montgomery 2002) | [Reversal structure](SYZYGY_REVERSAL_STRUCTURE.md), Theorem A; closes the first-arc objective of P1a unconditionally. |
| A second brake forces a stutter (equal adjacent syzygy letters), a palindromic itinerary, and sits at the unique `z`-extremum of its arc; brakes are the fixed points of the involution `R∘P` on the syzygy section | PROVED ANALYTICALLY | [Reversal structure](SYZYGY_REVERSAL_STRUCTURE.md), Theorems B–D; a necessary condition, not an exclusion of later brakes. |
| Global landscape scan, near-brake refinement, and mass–side periodic atlas (17 orbits, smallest right-angle defect `−3.3e-6`) | ORDINARY NUMERICAL EVIDENCE | [Reversal structure](SYZYGY_REVERSAL_STRUCTURE.md), `data/mass_side_periodic_atlas.json`, `scripts/landscape/`; no interval validation, all defects nonzero. |
| First positive inertia maximum is not a brake on `[0.29,0.29002]` | PROVED BY COMPUTER-ASSISTED ARGUMENT | [First-maximum certificate](MIDDLE_FIRST_MAXIMUM_INTERVAL.md); later maxima not covered. |
| All-time nonperiodicity on `[0.29,0.2900000101]` | PROVED BY COMPUTER-ASSISTED ARGUMENT | [Middle interval](FABLE_MIDDLE_INTERVAL_NONPERIODICITY.md); 100-tile archive plus initial tile and terminal theorem. |
| All-time nonperiodicity on the prompt-ejection window `[0.3916,0.4094]` and its leg-exchange mirror `[0.419044,0.437195]` (about 3.9% of all primitive triples by hypotenuse, incl. (20,21,29)) | PROVED BY COMPUTER-ASSISTED ARGUMENT | [Window record](ISO_WINDOW_INTERVAL.md); 25,900 gap-free tiles, audited and cross-replayed; `data/fable/iso_window/`. |
| Wider affine cover `[0.29,0.290002]` | COMPUTER-ASSISTED THEOREM CANDIDATE | [Affine graph](AFFINE_REMAINDER_GRAPH.md); independent inclusion-algebra review remains the promotion gate. |
| Punctured near-isosceles nonperiodicity | PROVED BY COMPUTER-ASSISTED ARGUMENT | [Endpoint analysis](ISOSCELES_SYZYGY_THRESHOLD.md); existential cutoff and classical collision alternative. |
| First thin-triangle encounter and full incoming matching | PROVED ANALYTICALLY / EXACT SYMBOLIC IDENTITY | [Regularization](SKINNY_REGULARIZATION.md), [incoming tail](INCOMING_TAIL.md); controlled asymptotics, not immediate escape. |
| Restricted transversality and escape arcs | PROVED BY COMPUTER-ASSISTED ARGUMENT | [Transversality](COMPUTER_ASSISTED_TRANSVERSALITY.md), [scattering](COMPUTER_ASSISTED_TRANSVERSE_SCATTERING.md). |
| Infinitely many thin windows; positive lower density within `(4n²−1,4n,4n²+1)` | PROVED ANALYTICALLY with computer-assisted ingredients | [Explicit family](EXPLICIT_SKINNY_FAMILY.md); density by `n`, not all primitive triples. |
| Uniform first-turn angular-momentum exclusion | PROVED ANALYTICALLY with computer-assisted ingredients | [Outgoing angular momentum](OUTGOING_ANGULAR_MOMENTUM.md); not all subsequent turns. |
| Local planar collision roots, joint scaling, finite-mass collision/escape neighborhoods | PROVED ANALYTICALLY / PROVED BY COMPUTER-ASSISTED ARGUMENT | [Joint scaling](FINITE_B_TRIPLE_JOINT_BLOWUP.md), [collision records](COMPUTER_ASSISTED_PLANAR_THIRD_FOURTH_COLLISION_ROOTS.md), paper Section 7. Local classification only. |
| Infinitely many exact real tied collision parameters | PROVED ANALYTICALLY with computer-assisted ingredients | [Real collision sampling](REAL_COLLISION_SAMPLING.md); rationality is not established. |
| Point certificates for (7,24,25), (9,40,41), (36,77,85) at `u=1/7, 1/9, 2/9` | PROVED BY COMPUTER-ASSISTED ARGUMENT | [Small triples](SMALL_TRIPLE_CERTIFICATES.md); `data/fable/point_certs/`; native CAPD, pair-{1,3} LC chart, replayed at a second order/tolerance. |
| Five named primitive point exclusions already in the main ledger | PROVED BY COMPUTER-ASSISTED ARGUMENT | [Point records](FABLE_TRIPLE_CERTIFICATES.md); preserve exact parameters and archived accepted logs. |
| Classical 3–4–5 problem `u=1/3` (fresh 2026-09-07 certificate), (12,35,37) `u=1/6`, and (39,80,89) `u=3/13` | PROVED BY COMPUTER-ASSISTED ARGUMENT | [Small triples](SMALL_TRIPLE_CERTIFICATES.md); multiprecision `window_lc_capd`, logs in `data/fable/point_certs/`; all three replayed at other precisions, orders, and tolerances. |
| Recovered historical `u=1/3` and `u=5/14` point-run claims | COMPUTER-ASSISTED THEOREM CANDIDATE (superseded for `u=1/3` by the row above) | [Recovered-record assessment](FABLE_BURRAU_THEOREM.md); terminal PASS is recorded, but audited provenance/replay is not completed. |
| Six mass–side periodic candidates, including F30 | ORDINARY NUMERICAL EVIDENCE | [Campaign](PERIODIC_CONSTRUCTION_REPORT_2026-09-05.md); no interval root proof, all right defects nonzero. |
| Exact tied-right second brake or integer periodic counterexample | OPEN; none found | [Construction campaign](PERIODIC_CONSTRUCTION_REPORT_2026-09-05.md). |
| Codimension, reflection conditions, rank-four caveat, and syzygy itinerary obstruction | PROVED ANALYTICALLY | [Symmetry audit](PERIODIC_SYMMETRY_AUDIT.md); does not establish transversality or a connecting periodic branch. |

## Promotion rule

A numerical root needs a complete residual, validated existence, collision-free
flow enclosure, and the exact launch constraints. An integer counterexample
also needs a rational parameter, not a decimal fit. An exclusion theorem needs
its quantified domain and control of all remaining times. A certificate log
needs an identified verifier, trusted rounding/dependencies, correct enclosure
and chart logic, and a reproducible output. Record the unresolved parts rather
than inferring them from a PASS token or a small numerical residual.
