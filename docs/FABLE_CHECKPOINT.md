# Fable WIP checkpoint

Date: 2026-08-23

## Git identity

- Branch: `master`
- Reproducible payload commit:
  `4e28e91e4b69937b777501cba942ee26186cc139`
- Payload subject: `Checkpoint finite-mass collision boundary`

This manifest is committed as the immediate child of the payload commit.  A
commit cannot contain its own hash, so the hash above deliberately identifies
the complete source, documentation, verifier, test, and tracked certificate
payload described here; the child commit adds only this manifest.

## Passing deterministic checks

The following commands passed from the repository root unless a `cd` is
shown.  The local environment reported Python 3.13.13, pytest 8.4.1, ruff
0.12.8, and Tectonic 0.16.9.

```bash
PYTHONDONTWRITEBYTECODE=1 .venv/bin/pytest -q -p no:cacheprovider
.venv/bin/ruff check --no-cache .
mkdir -p /private/tmp/fable-paper
cd paper
tectonic --outdir /private/tmp/fable-paper main.tex
```

The test result was `92 passed`.  Ruff reported `All checks passed!`.  The
paper build completed and wrote `/private/tmp/fable-paper/main.pdf`; it emitted
only the already recorded 0.42035pt overfull-box warning near line 435.

The virtual environment is reproducible from the tracked lockfile with:

```bash
uv sync --frozen
```

## Passing pinned certificates

All four commands below passed with CAPD 6.1.0 at pinned source commit
`731079217a9254ea2948d742df2b170895effe7f`, native intervals, and the existing
native build:

```bash
bash scripts/run_capd_restricted_transversality.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native

bash scripts/run_capd_restricted_transverse_scattering.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native

bash scripts/run_capd_planar_light_collision_shape.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native

bash scripts/run_capd_planar_light_collision_newton.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native
```

The wrappers check the CAPD source commit and tree cleanliness.  The final
markers were respectively `PASS`, `PASS`, `PASS_STAGE`, and `PASS_ROOT`.
Tracked verifier sources, wrapper scripts, and hexadecimal certificate outputs
are included in the payload commit.  Fresh CAPD checkout/build instructions
are in `COMPUTER_ASSISTED_TRANSVERSALITY.md` and the individual certificate
notes.

## Intentionally untracked material

No repository-essential source, proof script, certificate input, or
certificate output is intentionally untracked.

The following replaceable or disposable material is intentionally excluded:

- `.venv/`, `.pytest_cache/`, `.ruff_cache/`, Python bytecode, and `.DS_Store`;
- `/private/tmp/pythagorean-capd/` and its `build-native/` tree, because CAPD is
  an external dependency pinned by commit rather than vendored;
- `/private/tmp/fable-paper/main.pdf`, a disposable paper build product;
- compiler products emitted by the CAPD wrappers in the system temporary
  directory.

`paper/*.pdf` is now ignored so a local paper build cannot enter a future
source checkpoint accidentally.

## STATUS claims with non-committed dependencies

No claim in `STATUS.md` depends on omitted local source or an omitted local
certificate file.  The following non-vendored evidence or context should
nevertheless be distinguished from the committed payload:

- Every `PROVED BY COMPUTER-ASSISTED ARGUMENT` claim using CAPD depends on the
  external pinned CAPD source/build and host compiler.  The verifier sources,
  replay wrappers, proof notes, and recorded outputs are committed; CAPD
  itself is not.
- Statements that two independent adversarial audits endorsed major lemmas
  summarize agent audit transcripts.  The repaired mathematical statements
  and resulting proof obligations are committed, but the raw conversational
  transcripts are not repository artifacts.
- Literature and catalog-audit conclusions depend on cited external primary
  sources and published data.  The coverage table, URLs/DOIs, comparison
  calculations, and conclusions are committed; downloaded publisher PDFs are
  not vendored.
- The positive-mass collision-boundary theorem is only a local fixed-section
  persistence result.  `STATUS.md` explicitly leaves differentiated
  inclination through the long saddle dwell, intersection with the tied
  Pythagorean curve, exclusion of other collision zeros, and outgoing-sign
  control open.  No omitted computation upgrades any of those obligations.

## Checkpoint scope

The payload includes the latest projective-family shape dynamics, analytic
stable-tail enclosure, forced Levi--Civita collision map, correlated CAPD
interval-Newton root, exact finite-mass selected-pair reduction, the repaired
collision-pair center coordinate

\[
 Q=R+{B\over1+B}q,
\]

the local fixed-section persistence theorem, symbolic regression tests, and
the synchronized status, proof ledger, obligations, experiment log, run
report, README, and paper draft.
