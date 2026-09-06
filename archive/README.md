# Archive: provenance, not another working project

All active work proceeds from the repository root. This archive preserves
useful failed ideas, evidence, source provenance, and formerly unversioned
assets without treating them as current research instructions. A historical
claim or PASS marker never overrides `docs/PROOF_LEDGER.md`.

| Location | Contents and reason for preservation |
| --- | --- |
| `legacy-burrau/` | Original notes, source scripts, data, and illustrations from the former unversioned sibling. Arithmetic plots are historical outreach assets, not an active proof strategy. |
| `branch-snapshots/global/` | Recovered 3–4–5 LC and 5/14 logs, contemporaneous LC source/launcher, and original branch claims. Not newly accepted certificates. |
| `branch-snapshots/middle/` | Missing middle-cover crosscheck, parameter-graph benchmarks, source, and handoffs. These record why old representations were abandoned. |
| `history/campaigns/` | Eighteen retired handoffs, run reports, experiment diaries, and agent-specific plans. Their queues and instructions are inactive. |
| `history/guides/` | Original versions of rewritten project guides and certificate/design notes. Some contain withdrawn or overbroad proof claims. |
| `reorganization-2026-09-06/` | Before-inventory with checksums and Git identities, plus preservation/audit records. |

Earlier manuscripts remain in `../paper/archive/`; the expanded technical
companion remains `../paper/technical-details.tex/pdf`. The principal
mathematics is in the current working paper; these are not competing drafts.

## Recovering the retired worktree histories

Both retired worktrees were clean with respect to tracked and untracked
research files. Their distinct branch histories were preserved and pushed
before removal:

```text
archive/fable-global-2026-09-06  b306392598a7cdcb75c0a02bae95a1878ae0595c
archive/fable-middle-2026-09-06  4b58f4b57e3d08d721434eb93b128a637bc1ee92
```

Inspect without creating another project root:

```sh
git fetch origin --tags
git log --oneline archive/fable-global-2026-09-06
git show archive/fable-global-2026-09-06:docs/FABLE_BURRAU_THEOREM.md
```

Use `git archive` into a scratch directory for a historical replay. Do not
blindly merge an old verifier over later soundness fixes. Original relative
links and machine-local paths inside archived files describe their old
environment; they are not dependencies of the current paper build or tests.
Copy an archived experiment into scratch and adjust paths there if reopening it.

## What was removed from the working surface

The two redundant worktrees and their generated environments were retired.
Regenerable caches from the unversioned sibling (about 125 MiB), four LaTeX
logs, and one verified duplicate PNG were moved to
`/private/tmp/burrau-reorganization-retired.3QondG`. That temporary directory
is recoverable locally while it exists, but is not permanent preservation
and is not needed to recover source or evidence.

Eleven previously selected copies under `paper/archive/burrau-2026-09-06`
were byte-identical to the newly imported originals and removed as redundant.
Their old index is retained in `history/BURRAU_SUPPORTING_NOTES_2026-09-06.md`.
The current figure snapshots in `paper/figures/` remain intentional immutable
publication inputs; in particular, the inspected fan differs from a later
legacy regeneration. No scientific input was discarded merely because its
research route failed.

`make audit` checks the retained legacy hashes and selected branch snapshots
against the before-inventory, alongside the active layout and middle-cover
records. `.gitattributes` preserves their original line endings and exempts
their historical whitespace from style checks; normalizing imported CSVs or
logs would break their source hashes. It is an integrity check, not a proof
of the archived mathematics.
