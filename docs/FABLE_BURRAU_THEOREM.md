# Classical 3–4–5 point: recovered certificate, audit pending

Reviewed September 6, 2026. **COMPUTER-ASSISTED THEOREM CANDIDATE**, not a
new theorem established by this consolidation. There is no run currently
in progress. The old pending direct-event draft is retained in
`../archive/history/guides/FABLE_BURRAU_THEOREM.md`.

## What was recovered

The retired global worktree contains a completed LC run for exact `u=1/3`,
equivalent by leg exchange to `u=1/2` and the classical 3–4–5 problem.
Its full history is preserved at tag `archive/fable-global-2026-09-06`
(commit `b306392598a7cdcb75c0a02bae95a1878ae0595c`). Selected records are
available without checking out that tag:

- [Original claim and settings](../archive/branch-snapshots/global/docs/FABLE_BURRAU_THEOREM.md).
- [Completed log](../archive/branch-snapshots/global/data/fable/certificate_burrau_1_3.log).
- [Contemporaneous LC source](../archive/branch-snapshots/global/src/fable/verification/burrau_lc_certificate_capd.cpp)
  and [launcher](../archive/branch-snapshots/global/scripts/fable_run_capd_burrau_lc.sh).

The log ends with `PASS_BURRAU_LC`: 5,992 steps, 167 event steps, reported
minimum event kinetic margin `0.015393650608031001`, and terminal escape
margin `0.90661749434155592` at physical time `12.132142197026601`.
These are reported outputs, not independently re-established bounds here.
The branch described 640-bit arithmetic, order 150, and tolerance `1e-150`.

## Why the PASS is not enough

The main verifier has additional chart machinery and explicit checks for
the damped graph overwrites. The [construction audit](FABLE_LC_COVERING_DESIGN.md)
identified a soundness issue: a nominal target duration is not necessarily
a rigorous lower integration duration when interval time bounds overlap
the target. The implemented gate uses the actual elapsed lower bound.
The recovered branch source does not include that gate.

This difference does not prove the old orbit claim false, or even show that
this particular run violates the sufficient inequality. It does prevent
using the historical PASS alone to establish the missing audit condition.
The existing post-repair record covers only a finite four-cycle smoke
test through time approximately `3.167`, not the entire escape certificate.

## Promotion gate

1. Identify the exact source, parameters, arithmetic mode, CAPD pin, and
   chart variants used by the recovered run. Compare the full dependency
   chain with the main verifier, not just its PASS marker.
2. Audit every chart change: exact algebra, damping inflation and actual
   duration, positive physical clock, positive pair separations, and no
   gap in the swept flow cover. Binary collision is not silently continued.
3. Replay the entire point certificate with the audited source, through the
   terminal escape-or-collision criterion. Save the command, source hashes,
   dependency version, output, and explicit theorem domain.
4. Only then update the main ledger and paper together.

If these obligations are discharged, the [event reduction](FABLE_EVENT_REDUCTION.md)
and [terminal theorem](ESCAPE_CRITERIA.md) yield no second classical brake
and hence nonperiodicity for this exact primitive triple. This remains a
single point result, not a proof on its neighborhood or the full family.

## Other recovered point log

The same tag contains a `PASS_TIED_EVENT p=5 q=14` record for the primitive
triple `(171,140,221)`, now at
`../archive/branch-snapshots/global/data/fable/certificate_5_14.log`.
This is a direct-event run, not the LC run discussed above. Its provenance
and source correspondence have not been audited in this consolidation;
it is preserved as a candidate, not added to the five accepted point records.
