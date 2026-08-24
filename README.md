# Pythagorean--Burrau nonperiodicity project

This repository is a proof-oriented investigation of whether a Newtonian
three-body free-fall initial condition can be a collision-free labelled
periodic orbit when the masses and opposite side lengths are the same
Pythagorean triple.

The governing statement and conventions are in `docs/CONJECTURE.md`.  Claims
are assigned evidence levels in `docs/PROOF_LEDGER.md`; open logical gaps are
tracked separately in `docs/PROOF_OBLIGATIONS.md`.  Numerical experiments are
not promoted to universal conclusions.

Current strongest result: the full rational and strong real conjectures remain
open, but infinitely many open skinny Euclid-parameter intervals are proved
nonperiodic. Consequently infinitely many distinct primitive Pythagorean
triples satisfy the conjecture. More explicitly, the primitive family
$(4n^2-1,4n,4n^2+1)$ contains a positive-lower-density set of proved
nonperiodic members. See `docs/EXPLICIT_SKINNY_FAMILY.md` and
`docs/STATUS.md`.

At the singular triple-collision endpoint, the remaining finite-mass
boundary layer has now been reduced analytically to one projective parameter
in a universal planar restricted problem. An exact Hill barrier excludes a
brake throughout the near-triple tube, and the planar limit has a strict
shape Lyapunov function plus a factorized signed torque. These are structural
reductions, not a resolution of the later re-expanded dynamics.

## Reproduce the exact checks

```bash
uv sync --all-groups
uv run pytest
uv run python -m scripts.derive_exact_identities
uv run python -m scripts.derive_taylor_jet
uv run python -m scripts.derive_skinny_regularization
uv run python -m scripts.derive_skinny_matching
uv run python -m scripts.derive_restricted_scattering
uv run python -m scripts.derive_finite_plunge
uv run python -m scripts.probe_restricted_transversality --cutoffs 10 20 40
uv run python -m scripts.probe_restricted_turn_map \
  --resonances 2:0.3:0.5 3:0.2:0.3 7:0.12:0.15 \
  --phase-span 30000 --max-step 0.04
```

The rigorous finite restricted-transversality and transverse-scattering
certificates additionally use
CAPD 6.1.0 pinned at commit
`731079217a9254ea2948d742df2b170895effe7f`. After building CAPD with
`-DCAPD_INTERVAL_TYPE=NATIVE`, run:

```bash
sh scripts/run_capd_restricted_transversality.sh \
  /path/to/CAPD /path/to/CAPD/build-native
bash scripts/run_capd_restricted_transverse_scattering.sh \
  /path/to/CAPD /path/to/CAPD/build-native
bash scripts/run_capd_planar_light_collision_shape.sh \
  /path/to/CAPD /path/to/CAPD/build-native
bash scripts/run_capd_planar_light_collision_newton.sh \
  /path/to/CAPD /path/to/CAPD/build-native
bash scripts/run_capd_planar_light_collision_newton.sh \
  /path/to/CAPD /path/to/CAPD/build-native --second-root
bash scripts/run_capd_planar_light_collision_newton.sh \
  /path/to/CAPD /path/to/CAPD/build-native --second-escape
bash scripts/run_capd_planar_light_collision_newton.sh \
  /path/to/CAPD /path/to/CAPD/build-native --second-escape-wide
bash scripts/run_capd_planar_light_collision_newton.sh \
  /path/to/CAPD /path/to/CAPD/build-native --third-root
bash scripts/run_capd_planar_light_collision_newton.sh \
  /path/to/CAPD /path/to/CAPD/build-native --fourth-root
bash scripts/run_capd_planar_light_collision_newton.sh \
  /path/to/CAPD /path/to/CAPD/build-native --fourth-fifth-entry
```

Full derivation and trusted-computing-base details are in
`docs/COMPUTER_ASSISTED_TRANSVERSALITY.md` and
`docs/COMPUTER_ASSISTED_TRANSVERSE_SCATTERING.md`. The planar collision-shape
wrapper validates only the finite stable-tail-to-LC propagation stage; its
scope and the now-closed historical interval-Newton obligation are recorded in
`docs/COMPUTER_ASSISTED_PLANAR_LIGHT_COLLISION_STAGE.md`. The correlated
doubleton wrapper proves a unique transverse collision root in the planar
limiting family and now validates its regularized continuation to the escape
cone; see `docs/COMPUTER_ASSISTED_PLANAR_LIGHT_COLLISION_ROOT.md` and
`docs/COMPUTER_ASSISTED_PLANAR_COLLISION_ESCAPE.md`.
The same correlated verifier uses a second LC chart to certify a distinct
transverse collision with the opposite primary; see
`docs/COMPUTER_ASSISTED_PLANAR_SECOND_COLLISION_ROOT.md`.
Its regularized outgoing branch has an exact third, positive-primary LC chart
recorded in `docs/SECOND_COLLISION_OUTGOING.md`.  The corresponding interval
collision-or-escape enclosure and finite-mass transfer are proved in
`docs/COMPUTER_ASSISTED_PLANAR_SECOND_COLLISION_ESCAPE.md`.
The 195-tile certificate covers the contiguous interval
`[1.2640099161, 1.2640126461]`.
Immediately below it, two further pinned interval-Newton certificates prove
distinct, classically reached positive- and negative-primary collision roots;
their parameter projections are separated by more than
`1.2058e-11`.  See
`docs/COMPUTER_ASSISTED_PLANAR_THIRD_FOURTH_COLLISION_ROOTS.md`.
The fourth-root box is continued, with the classical collision alternative,
to a uniform fifth positive-primary LC chart in
`docs/COMPUTER_ASSISTED_PLANAR_FOURTH_TO_FIFTH_ENTRY.md`.
The exact positive-light-mass reduction and the resulting persistence theorem
for that collision boundary are in
`docs/FINITE_MASS_PLANAR_COLLISION_PERSISTENCE.md`.  The differentiated
two-mode inclination theorem and normalized finite-mass collision graph are
in `docs/DIFFERENTIATED_JOINT_INCLINATION.md`.  Combining that graph with
the exact skinny phase winding proves infinitely many exact real tied
collision parameters; see `docs/REAL_COLLISION_SAMPLING.md`.
The certified limiting collision has also been continued rigorously through
its collision--ejection branch and the subsequent heavy-binary LC passage.
It enters a strict escape cone.  A separate hierarchical-energy lemma absorbs
all future positive-light-mass tidal work, proving a local finite-mass
collision-or-escape cusp; see
`docs/COMPUTER_ASSISTED_PLANAR_COLLISION_ESCAPE.md`.
