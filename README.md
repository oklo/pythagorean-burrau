# The Pythagorean Three-Body Conjecture

**Prove the conjecture or construct an exact counterexample.** Every experiment,
lemma, and computational tool should address that decision. The conjecture
remains open; nearby periodic orbits and additional small exclusion intervals
are partial information, not its resolution.

The primary interim product is the [working paper](paper/main.pdf),
*The Pythagorean Three-Body Conjecture* (September 6, 2026; 31 pages).
Its [LaTeX source](paper/main.tex) includes the principal technical arguments,
the historical introduction, and the counterexample search. Richard Montgomery
is the intended technical reader; the opening also welcomes a lay audience.

This is the **single working directory and single repository** for the project:
`pythagorean-burrau`, mapped to the private
[oklo/pythagorean-burrau](https://github.com/oklo/pythagorean-burrau) repository.
The former `burrau` assets and two agent worktrees have been consolidated or
retired. Do not recreate separate agent-specific project directories.

## Start here

- [Current status](docs/STATUS.md): what is established, numerical, and open.
- [Research plan](docs/RESEARCH_PLAN.md): the two active lines of attack and
  the deliverables that would justify further work.
- [Exact problem](docs/CONJECTURE.md) and [proof obligations](docs/PROOF_OBLIGATIONS.md).
- [Proof ledger](docs/PROOF_LEDGER.md): claims linked to their supporting records.
- [Failed routes](docs/FAILED_ROUTES.md): mistakes and barriers not to rediscover.
- [Project review](docs/PROJECT_REVIEW_2026-09-06.md) and
  [handoff](docs/HANDOFF.md): consolidation findings and restart instructions.

No progress percentage measures distance to a proof. The paper's explicitly
subjective 10% assessment concerns the *existence of a counterexample*, not
research completion or a successful finite search.

## Working layout

```text
paper/      Working manuscript, figures, and earlier manuscript versions
docs/       Current research guides and detailed proof/certificate notes
src/        Exact reductions, numerical dynamics, and validated verifiers
scripts/    Reproduction, bounded searches, and audits
tests/      Algebra, dynamics, chart, and audit regressions
data/       Attributed seeds, numerical records, and certificate outputs
archive/    Superseded campaigns, legacy assets, and consolidation provenance
```

The [archive index](archive/README.md) explains what was retired and how to
recover it. Archived reports and PASS logs do not override the current ledger.
Keep certificate inputs and exact counterexamples to failed lemmas; discard
regenerable caches, duplicate environments, and redundant copies.

## Build and verify

Python 3.13 and the pinned environment are specified by `pyproject.toml` and
`uv.lock`. Tectonic builds the paper; the CAPD toolchain is only needed for
explicitly requested interval replays.

```sh
uv sync --all-groups
make check        # full Python tests and repository/certificate audits
make paper        # rebuild the working PDF
make help         # available targets and evidence limits
```

The full Python suite does not rerun all CAPD integrations or prove every
analytic estimate. The archived middle-cover auditor checks all 100 stored
tiles and exact shared endpoints; it is not a new flow integration. Detailed
replay commands remain in the proof notes and [paper guide](paper/README.md).
CAPD is pinned to 6.1.0, commit
`731079217a9254ea2948d742df2b170895effe7f`.

The [Oklo publication record](docs/OKLO_PUBLICATION_2026-09-06.md) identifies
the reviewed PDF linked from “Add Astra,” its checksum, and the prior-version
backup. Rebuilding locally does not authorize or perform a website deployment.
