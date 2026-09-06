# Periodic-triple construction campaign — 2026-09-05

**No counterexample found.** No exact real tied-right brake, rational candidate,
rank-deficient tied root, or connected tied-periodic curve was established.
The integer and strong real conjectures remain unresolved.

The campaign followed the
[archived construction brief](../archive/history/campaigns/ASTRA_PERIODIC_TRIPLE_HANDOFF.md):
it refined the four
principal seeds, computed propagated variational Jacobians, completed the two
stalled mass-side homotopies, and tested nearby branches with the right and
mass-side constraints imposed at launch. This is construction work, not an
exhaustive survey or a nonperiodicity proof.

## Reproducible numerical advances

`src/dynamics/periodic_shooting.py` compiles the selected-pair Levi--Civita
field and its exact symbolic state/mass Jacobian. `periodic_atlas.py` changes
between all three pair charts, propagates five physical shooting tangents,
projects them onto switching sections and the final physical-time section,
and reconstructs a fixed pair-23 endpoint residual. Local chart derivatives
use complex-step differentiation of analytic algebra; no integrated
trajectory is finite-differenced to generate a shooting Jacobian.

A single deepest-pair chart was insufficient: F2 and F4 still had noisy
residuals when the other pair passed closely. Pair changes resolved that
failure. The new pseudo-arclength solver resumed F3 at lambda about 0.874 and
F4 at lambda about 0.606, and reached lambda=1 for both while preserving their
observed labelled syzygy sequences. No fold or rank loss appeared on these
resumed portions. The historical catalog-to-resume portions were not replayed;
the F3/F4 attribution retains that provenance limitation.

All results in the following table are **ORDINARY NUMERICAL EVIDENCE**.
Masses are `(m1,m2,1)` and each initial opposite side matches its mass to
ordinary shooting accuracy. D is `m1^2+m2^2-1`. Minima are numerically resolved
by dense interpolation and scalar minimization, not rigorous lower bounds.

| Seed | m1 | m2 | Physical half-period | D | Smallest singular value | Resolved minimum separation |
|---|---:|---:|---:|---:|---:|---:|
| F1 | 0.536940688528 | 0.839991651314 | 1.33797001373 | -0.00610872272625 | 0.679704 | 4.06034e-4 |
| F2 | 0.485763526196 | 0.878297062574 | 1.41333001523 | +0.00737193350930 | 0.675131 | 9.07434e-5 |
| F5 | 0.474742621620 | 0.896107794981 | 1.54407626195 | +0.02838973700849 | 0.625808 | 1.47411e-5 |
| F30 | 0.594811646571 | 0.801774973318 | 6.28923382379 | -0.00335599726517 | 0.198799 | 4.99935e-4 |
| F3 | 0.343754596668 | 0.887462425634 | 1.07486509682 | -0.09424322035777 | 0.869777 | 5.84016e-6 |
| F4 | 0.335421060084 | 0.903827720234 | 1.13347517446 | -0.07058816458879 | 0.809009 | 3.41252e-6 |

Singular values refer specifically to parameters `(x,y,tau,m1,m2)` and
residual `(zr,zi,G dot P,m1-r23,m2-r31)` in the canonical pair-23 endpoint
chart. They are coordinate-dependent diagnostics, not certified rank bounds.
The numerical matrices are full rank; none suggests the rank-four mechanism
sought in the handoff. Full matrices and smallest left/right singular vectors
are in `data/periodic_atlas_campaign.json`.

Several old sampled minima substantially underestimated encounter depth. F4,
for example, reaches about 3.4e-6 despite an initial triangle of order one.
No positive number in this table is a collision-freedom certificate.

## Independent agreement and numerical limits

The five native shooting residuals are below 4.1e-14 for the five shorter
candidates and below 1.2e-12 for F30. A tighter DOP853 replay with a different
initial chart reproduces the roots within the existing 2e-11 residual
acceptance criterion. Its unchanged parameter arrays mean that the original
point passed the tighter criterion without another Newton correction; they
are **not** evidence of exact agreement or extra decimal precision.

An implicit Radau replay at the same frozen decimal parameters gives complete
native brake residuals below 2.1e-12 across all six candidates. Reversing the
regularized segments gives maximum position error below 8.1e-13, maximum
velocity error below 2.1e-12, and physical-clock error below 1.3e-13. Full
labelled endpoint velocities, Hopf residuals, chart changes and pair minima
are recorded, so a small incomplete residual is not substituted for a brake.

Sampled physical energy errors range from about 1.3e-11 to 2.5e-7, the largest
occurring in the deepest encounters. Reconstructed physical kinetic/potential
terms are large there, and LC constraint errors are amplified by division by
the small separation. Endpoint agreement and reverse errors do not erase
these observed errors. No interval Newton inclusion, interval Jacobian bound,
or swept collision-free tube was attempted or obtained in this campaign.

## Search on the exact tied-right family

`scripts/search_tied_right_events.py` imposes

```
a = (1-u^2)/(1+u^2), b = 2u/(1+u^2)
x = (b^2-a^2)/2, y = a*b, masses = (a,b,1).
```

These are the exact defining formulas evaluated in floating point; decimal
u is not a claim of an exact rational periodic parameter. For each seed the
solver locates a nearby strict I-maximum, then minimizes the complete
mass-weighted velocity along that event branch using propagated derivatives.
Its squared residual norm is `2K`, so zero would be a simultaneous labelled
brake, rather than a return of only one reduced component.

| Seeded event search | u in the displayed mass convention | K at reported event | Weighted speed norm | Outcome |
|---|---:|---:|---:|---|
| F1 | 0.547446309285 | 1.2837453e-4 | 0.0160234 | Local optimizer converged, nonzero |
| F2 | 0.590189453740 | 6.7095121e-4 | 0.0366320 | Local optimizer converged, nonzero |
| F5 | 0.603994286690 | 1.8746400e-2 | 0.193631 | Local optimizer converged, nonzero |
| F30 | 0.503800939956 | 2.8615033e-3 | 0.0756506 | Evaluation limit; last steps noise-limited |
| F3 | 0.691020919144 | 6.1488345e-2 | 0.350680 | Local optimizer converged, nonzero |
| F4 | — | — | — | Initial event iteration left the strict-maximum branch |

All displayed parameters can be brought to the fundamental interval by
`u -> (1-u)/(1+u)` with leg relabelling. The raw convention is retained to
make the records reproduce directly.

The five reported events were independently replayed with a tighter tolerance
and different initial chart. Their velocity residual differences are below
8.8e-13, far below the nonzero residuals. The F30 value is not promoted to a
converged minimum, and F4's failed local event initialization is not a
dynamical obstruction. These are local probes only: neither global origin
avoidance nor exclusion of later events follows. No real near-zero emerged,
so rational reconstruction and a fixed-rational validation were not warranted.
The full event histories are in `data/tied_right_event_search.json`.

## Exact symmetry and itinerary audit

The independent adversarial note `PERIODIC_SYMMETRY_AUDIT.md` establishes:

1. Reflection-time-reversal shooting has exactly three independent conditions,
   even after imposing zero momentum, zero angular momentum and fixed energy.
   The right mass identity alone removes none of them.
2. Rank four at one five-equation root does not establish a tied branch.
   Lyapunov--Schmidt reduction may leave an isolated scalar zero; its first
   further obstruction is `ell^T D^2F[n,n]`.
3. Full brake loops retrace and are nullhomotopic. The four supplied catalog
   strings all freely reduce to identity under the usual inverse convention;
   their differing unreduced strings alone are not differing free-group classes.
4. Nevertheless every syzygy of a noncollinear zero-angular-momentum orbit is
   transverse. The labelled syzygy sequence is locally constant in a continuous
   finite-time collision-free brake family. Different **certified** sequences
   therefore can obstruct such a connection.

The six ordinary half-orbit sequences are recorded in that note and the JSON.
They differ between the positive- and negative-defect candidates. Counts were
extracted from dense event brackets, not validated, and full catalog word
reconstruction was not performed. A free-group correction does not create an
intermediate-value bracket. Nor does the connected external-lambda homotopy
provide a continuum on its single tied slice lambda=1.

The code audit checked all six chart-transition identities independently,
including explicit mass derivatives and the time-rescaling pushforward. It
caught and prompted repair of a spurious Jacobian return when variations were
disabled. The implementation now also uses a stable launch square root and
a canonical endpoint chart. Actual selected collisions can still pass through
LC numerics: the evidence classification deliberately remains ordinary.

## Reproduction and verification

From the repository root:

```bash
PYTHONPATH=. .venv/bin/python scripts/search_periodic_atlas.py
PYTHONPATH=. .venv/bin/python scripts/search_tied_right_events.py
.venv/bin/python -m pytest -q tests/test_periodic_atlas.py tests/test_f30_mass_side.py tests/test_brake_residual.py tests/test_symbolic_brake_residual.py tests/fable/test_event_reduction.py
```

The targeted regression suite passed **34 tests**. The new tests compare
all initial pair charts with direct Cartesian flow, check physical vector-field
pushforward under all six chart changes, verify parameter derivatives before
an encounter, and compare physical derivatives through different switching
itineraries at F2. All five new Python files pass Ruff lint and formatting.

Seeds were audited and copied into `periodic_construction_seeds.json` and
`periodic_stalled_seeds.json`; the main programs do not depend on the auxiliary
`burrau` directory. Catalog normalization was checked against the
[Li--Liao author catalog](https://numericaltank.sjtu.edu.cn/three-body/free-fall-3b/free-fall-3b-movies.htm).

The next construction still needs an actual mechanism: for example, a
collision organizer with a rigorously controlled collision-free unfolding
that intersects the tied-right launch curve. Completing more unrelated
isolated roots, or finding another change of sign among them, would not supply
that missing mechanism. This campaign resolves the two named engineering
stalls and tests the proposed rank route at the six selected candidates; it
does not resolve the conjecture.
