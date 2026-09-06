# Project review and consolidation — September 6, 2026

## Outcome and scope

The project now proceeds from one directory, `pythagorean-burrau`, and one
private GitHub repository, `oklo/pythagorean-burrau`. The working paper is the
primary interim product. Current navigation and research priorities concern
proving the conjecture or constructing an exact counterexample; historical
agent campaigns no longer supply the default task list.

This review covers repository histories, assets, the paper's stated scope,
claim/dependency records, known analytic gaps, verifier soundness notes,
numerical-construction reports, and reproducibility. It is not an independent
line-by-line proof audit of every asymptotic estimate or C++ interval routine.
No new gravitational theorem, periodic solution, or fresh CAPD flow certificate
is claimed. Existing accepted results retain their recorded status; unresolved
audit conditions remain explicit.

## Consolidation decisions

| Before | Disposition |
| --- | --- |
| `pythagorean-burrau` | Canonical working repository; all current source, tests, evidence, and manuscript remain here. |
| `pythagorean-burrau-fable` | Clean research worktree retired after its distinct history was tagged and pushed. Missing point logs and their original source records were recovered into the archive. |
| `pythagorean-burrau-fable-middle` | Clean research worktree retired after history preservation. Missing crosscheck and parameter-graph benchmarks were recovered. |
| Unversioned `burrau` | Meaningful original assets imported under `archive/legacy-burrau`; no longer a sibling working project. |
| `oklo-org` publication copies | Left in place as deployment artifacts, not a second research repository. Unrelated dirty site work was untouched. |

The exact before-inventory is
`../archive/reorganization-2026-09-06/before.json`. Both branch tips are
preserved by pushed archive tags; no branch merge replaced the main verifier
with older code. The active checkout is the only registered worktree.

The original 56 non-cache legacy records include four regenerable LaTeX logs
and one duplicate PNG. After retiring the logs and deduplicating the image,
51 distinct originals remain, byte-for-byte. Eleven selected copies from an
earlier paper archive were also byte-identical and removed as redundant.
The reviewed manuscript figure snapshots remain separate intentional inputs.

About 125 MiB of legacy caches, the four logs, and the duplicate image were
moved to `/private/tmp/burrau-reorganization-retired.3QondG`; this is a local
temporary recovery location, not a permanent archive. Redundant worktree
environments were removed with the worktrees and are regenerable from their
pinned project files. No scientific input or useful failed-lemma witness
was discarded as cache. See [the archive index](../archive/README.md).

Eighteen superseded handoffs, run reports, experiment diaries, and agent
plans now live under `archive/history/campaigns`. Long accumulated guides
were preserved before replacement by a compact current status, ledger,
obligations, failed-routes summary, and research flow. The detailed proof
notes, source, exact regression tests, and certificate evidence remain active.
Names such as `src/fable` remain to preserve code imports and provenance;
they do not denote another active project or team queue.

## Mathematical findings and dispositions

### 1. The old forced-lag inference was still present as a theorem

The earlier manuscript review had already identified the singular endpoint
gap. Nevertheless, the active reduction's body and expanded ledger still
claimed that one positive-to-negative forcing switch and `w(S)=0` imply
interior positivity. A correction banner was not enough: readers following
the lemma itself could still encounter the invalid proof.

The body of `EXACT_REDUCTIONS.md` now states the corrected sufficient lemma:
use a fixed interior reference point for the integrating factor and require
`liminf M(s)w(s) >= 0` at the terminal endpoint. The ledger explicitly labels
the weaker inference **DISPROVED**. The exact scalar regression is retained.
Neither the forcing control nor the weighted terminal condition is proved
for the full brake-generated family. Even a first-arc proof would not yet
control every later return.

### 2. Recovered success logs need source-aware review

The retired global branch contained an apparently completed 3–4–5 LC
certificate that had been absent from the main evidence directory. Its
original theorem note asserted a proof, whereas the main note still described
an unfinished direct-event run. The log, source, launcher, and original claim
have all been preserved.

The main verifier contains later explicit damped-write soundness gates that
are absent from that historical source. In particular, interval-time target
overlap cannot substitute for a lower bound on actual elapsed construction
time. An existing post-repair smoke record stops well before the terminal
escape certificate. This is a provenance/audit gap, not evidence that the
3–4–5 orbit is periodic or that the old run necessarily violated the bound.

The current point note now describes the recovered run as a candidate and
states the full audit/replay gate. A recovered direct-event `u=5/14` PASS
is likewise preserved pending source/provenance review; it is not assigned
the LC-specific defect without evidence. The five previously recorded main
point exclusions have not been silently enlarged to seven.

### 3. Local results had been allowed to obscure the global gap

The all-time middle interval, first-maximum interval, and wider unaudited
affine candidate are now separated in every current overview. Likewise,
near-isosceles exclusion has an existential cutoff; thin-family density is
by its sequence index; first-turn exclusion is not all-return exclusion;
and exact collision sampling establishes real, not rational, parameters.

The manuscript already makes these principal distinctions, so its LaTeX and
reviewed PDF did not need an organizational rewrite. The central missing
argument is still all-time control across the remaining parameter family,
not merely a larger certified interval. Old progress percentages and obsolete
middle-transport bottlenecks were removed from active planning.

### 4. The nearby periodic figure is not a candidate integer solution

The F1/F2/F3/F4/F5/F30 continuations are ordinary numerical results in a
larger family. Their right-angle defects are nonzero, and no exact tied-right
second brake is known. The F30 plot's return half is constructed by time
reversal; its visual closure is not an independent test. Opposite defects at
unrelated isolated roots give no intermediate-value bracket.

The current construction plan therefore asks for an actual connecting
branch, justified symmetry reduction, or collision-boundary construction.
Its first deliverable is an exact real intersection; a rational parameter
and rigorous collision-free existence are further obligations before an
integer counterexample can be announced.

### 5. Negative results are useful; obsolete queues are not

Exact ambient witnesses disprove several proposed static barriers but are
not asserted reachable from the launch. The forced-lag scalar example refutes
an inference, not Newtonian nonperiodicity. Failed integrations reveal method
limits, not universal dynamical impossibility. These distinctions and the
regressions survive the cleanup. Old precision sweeps and agent queue prompts
remain recoverable in the archive but do not direct current work.

## Current research decision

The [research plan](RESEARCH_PLAN.md) has two active lines: an all-time
structural obstruction, and an exact counterexample mechanism. Each substantial
experiment must name the mathematical decision it serves, its quantified
domain, validation gate, and stopping criterion. Recovered-point and affine
audits are bounded supporting tasks. The paper and ledger must change together
when evidence genuinely changes a claim.

## Verification record

- `make check`: **251 tests passed** in 112.81 seconds, including six new
  integrity/navigation regressions. The full Python suite covers exact
  identities, reductions, dynamics, chart algebra, and certificate-log audits;
  it does not establish every analytic or interval-flow claim anew.
- Layout/preservation audit: 89 local guide links, ten paper source files,
  three figure inputs, 52 legacy inventory records (including the deduplicated
  image's retained equivalent), and all eighteen selected branch files pass.
- Middle-cover audit: all 100 stored tiles agree between summary and archive,
  including exact shared endpoints, requested/PASS domains, solver settings,
  and the pinned CAPD commit. This is an archive audit, not a new integration.
- `make paper-check`: successful Tectonic build, **31 pages**, with no
  undefined-reference or overfull-box warnings. The reviewed `paper/main.pdf`
  remains byte-identical, SHA-256
  `d2b50b0152d37ee0f65c3aebb39dbd771d19439187783ad5cd9e9062868c9f79`.
- Ruff lint/format checks pass for the added Python tools/tests and inventory
  utility. Git whitespace checks pass for active work; the immutable imported
  snapshots explicitly retain original CSV line endings and log whitespace
  through `.gitattributes`. No numerical verifier was modified.

The working-paper LaTeX, reviewed PDF, and public Oklo deployment are unchanged
by this organizational pass. A new project-level `AGENTS.md` records the same
scope and evidence rules for future work; it does not initiate research jobs.
