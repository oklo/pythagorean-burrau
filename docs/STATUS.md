# Current status

Reviewed September 6, 2026. This file supersedes the accumulated campaign
status narrative, preserved in `../archive/history/guides/STATUS.md`.

## The decision still to be made

The integer Pythagorean nonperiodicity conjecture and the stronger
real-parameter conjecture are **open**. No exact real second-brake point on
the tied-right family, and no rational counterexample candidate, is known.
The [working paper](../paper/main.pdf) is the primary interim product.

## Established partial results

| Result | Scope that must not be enlarged |
| --- | --- |
| Scaling, Euclid parameter, complete brake residual, and second-brake equivalence | Exact full-family reductions; all-time periodicity becomes exclusion of every positive brake before collision. |
| Lagrange–Jacobi reduction | Every brake is a strict inertia maximum. Separation bounds apply at brakes, not all intervening encounters. |
| First-maximum certificate | Every real `u` in `[0.29,0.29002]`; excludes only the first positive maximum as a brake. |
| All-time middle exclusion | Every real `u` in `[0.29,0.2900000101]`; finite validated cover plus a terminal collision-or-escape argument. |
| All-time prompt-ejection window (2026-09-07) | Every real `u` in `[0.3916,0.4094]` and, by leg exchange, in `[0.419044,0.437195]`: 25,900 audited tiles ([record](ISO_WINDOW_INTERVAL.md)). About 3.9% of all primitive triples by hypotenuse, including (20,21,29). |
| Point certificates (2026-09-07) | (7,24,25), (9,40,41), (36,77,85) in double precision; the classical (3,4,5) and (12,35,37) in multiprecision; see [small triples](SMALL_TRIPLE_CERTIFICATES.md). |
| Near-isosceles exclusion | An existential punctured one-sided real neighborhood; no effective cutoff is asserted. |
| Thin-triangle windows | Infinitely many open windows and a positive-lower-density subset of `(4n²−1,4n,4n²+1)`, measured by `n`. |
| Returning-region results | Uniform first-turn exclusion and local collision/escape structure; not classification of every later return. |
| Exact collision sampling | Infinitely many *real* collision parameters, not known rational. |
| Reversal structure of second brakes (2026-09-07) | No brake at or before the first syzygy for every real `u` (all masses); any later brake is a stutter at the `z`-extremum of its arc and a fixed point of `R∘P` on the syzygy section. Necessary conditions, not an all-time exclusion. |

See the [proof ledger](PROOF_LEDGER.md) for source records and dependencies.
“Established” here means the manuscript's recorded proof status, not that this
organizational review independently replayed every certificate.

## Numerical evidence and unresolved audits

- F1/F2/F3/F4/F5/F30 are six ordinary numerical periodic candidates in the
  larger mass–opposite-side family. All have nonzero right-angle defects and
  numerically nonsingular matching Jacobians. None is a counterexample.
- The continued F30 triangle has largest angle about `90.2015966°` and defect
  about `−0.00335599726517`. Its attractive trajectory plot is not a proof of
  periodicity or rationality.
- Searches on the exact tied-right family found no zero of the complete
  brake residual. F30 was noise/evaluation limited and F4 left the selected
  event branch; neither failure is an exclusion theorem.
- The wider affine-generator cover `[0.29,0.290002]` remains a computer-assisted
  theorem candidate pending its independent inclusion-algebra audit.
- Consolidation recovered a historical `PASS_BURRAU_LC` run at `u=1/3` and a
  further point log from an old worktree. They are preserved but **not promoted**:
  their source/version relationship to later soundness repairs needs audit and
  replay. See [the recovered-record assessment](FABLE_BURRAU_THEOREM.md).

## The principal mathematical gap

**Update 2026-09-07.** The first arc is closed: Theorem A of
[the reversal structure](SYZYGY_REVERSAL_STRUCTURE.md) excludes a second brake
at or before the first syzygy for every real parameter, so the forced-lag
terminal bound is no longer needed for that purpose. The global gap is
unchanged in substance and sharper in form: exclude brakes on stutter arcs
(fixed points of `R∘P` on the syzygy section) for all later arcs. A global
scan (`scripts/landscape/`) shows the family's closest approaches to a second
brake all lie on stutter arcs, the closest at `u≈0.2003099995`, `t≈7.91`,
with minimal kinetic energy `7e-9 U0` (then `8e-9` at `u≈0.2556321826`); the corresponding mass–side periodic
orbits (`data/mass_side_periodic_atlas.json`) have right-angle defects down
to `−3.3e-6`, all nonzero.

No current argument excludes every later brake across the full remaining
parameter family. The old scalar inference from one forcing sign change and
`w(terminal)=0` was invalid: its integrating factor is singular. The corrected
conditional lemma also needs a terminal weighted bound. Even closing that
lemma on a first ordered arc would leave later itineraries to control.
See [the exact correction](FORCED_LAG_ENDPOINT_CORRECTION.md).

The active priorities are an **all-time structural obstruction** and an
**exact counterexample construction**. Numerical infrastructure work needs a
specific mathematical use, not merely a better width or longer integration.
The [research plan](RESEARCH_PLAN.md) sets the next decision points.
