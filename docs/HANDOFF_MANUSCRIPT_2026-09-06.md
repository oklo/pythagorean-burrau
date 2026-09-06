# Handoff prompt — Pythagorean manuscript and Oklo publication

The following is a ready-to-use prompt for the next session.

---

You are continuing work with Greg Laughlin on *The Pythagorean Three-Body
Conjecture*. Work in `/Users/greglaughlin/Projects/pythagorean-burrau`, whose
private GitHub remote is `https://github.com/oklo/pythagorean-burrau.git`
(branch `master`). The manuscript and its publication update are complete;
continue with Greg's next requested edit or research task, not an unsolicited
new campaign. Inspect the worktree before changing anything.

Start by reading:

1. `docs/PERSISTENT_RESEARCH_MEMORY.md` — current findings and preferences.
2. `paper/README.md`, `paper/main.tex`, and the relevant `paper/sections/` files.
3. `docs/OKLO_PUBLICATION_2026-09-06.md` — deployed file and backup record.
4. For mathematical work, `docs/FORCED_LAG_ENDPOINT_CORRECTION.md`,
   `docs/STATUS.md`, `docs/PROOF_OBLIGATIONS.md`, and the September 5
   construction report. Older handoffs are subordinate to their correction notices.

## Current manuscript and preferences

The authoritative manuscript is `paper/main.pdf`, September 6, 2026,
**31 pages including references**, built from `paper/main.tex` and section
inputs. It now incorporates the important arguments from the former technical
companion; `paper/technical-details.tex/pdf` is an approximately 50-page archive,
not a second paper the reader must consult for the principal argument.

Richard Montgomery is the intended technical reader, but Greg explicitly
wants an engaging lay-accessible historical introduction. Retain the physical
experiment, Meissel–Burrau history, rational parameterization, and plain-language
motivation. Avoid “dance,” trivial exposition, conversational answers to unstated
questions, and generic LLM phrasing.

Preserve these specific approved choices:

- Title: **The Pythagorean Three-Body Conjecture**.
- Section 1: **A simple plan**.
- No “working research draft” author line.
- Abstract: 144 whitespace-delimited words, with its approved first two sentences
  unchanged. It states the current partial results and that the universal
  conjecture remains open.
- The full user-supplied Shaquille O'Neal epigraph follows the abstract. Its left
  edge matches the abstract body; there is an extra baseline of space above it.
  Attribution is roman, right-aligned, black, and linked to BrainyQuote.
- Figure 1 has aligned A/B headings and an isosceles-endpoint label inside the
  arc with a correctly directed arrow. Avoid regressing this layout.
- Greg relaxed the earlier under-30-page limit. Clarity takes precedence over
  squeezing the paper back to 29 pages.

Section 1.5 gives a compact, explicit answer to the measure-zero objection:
the desired statement is `P intersect Q = empty`, not `measure(P) = 0`.
The reversible analytic Hamiltonian
`H_u = (p_x^2 + x^2 + p_y^2 + u^2 y^2)/2`, launched at `(x,y)=(1,1)` with
zero momenta, has a second brake exactly when `u` is rational. Another
oscillator family has the isolated rational periodic parameter `1/3`.
Neither is a gravitational counterexample. Transversality is an unproved
condition on the actual family, not a conclusion of counting dimensions.

The final introductory paragraph gives a **subjective 10% chance that at
least one integer Pythagorean triangle has a collision-free periodic orbit**.
Greg explicitly requested the attribution **GPT-6 Astra**. This is an estimate
of existence somewhere in the entire family, not a calculated probability,
finite-search success rate, or theorem. The fan figure precedes this final
discussion in the compiled PDF.

## Section 2 and the near-3–4–5 candidate

Section 2 contains the six-candidate table and an expanded explanation of the
continued F30 orbit, with its trajectory as Figure 3. The previous defect plot
remains archived but is not in the current manuscript; all signed defects are
still in the table. The original Li–Liao catalogue is linked in the bibliography.

For the continued F30 candidate:

- Masses approximately `(0.594811646571, 0.801774973318, 1)`.
- Launch vertex approximately `(0.144521106471, 0.476902140016)`.
- Second-brake time approximately `6.289233824`.
- Right-angle defect approximately `-0.00335599726517`.
- Largest angle approximately `90.201596585` degrees.

It is ordinary numerical evidence, not an interval-certified periodic root,
and is not Pythagorean. There is no exact real tied-right brake candidate on
which rational reconstruction is warranted. The plotting replay has a roughly
`2.6e-11` shooting residual, distinct from the campaign's separately refined
root. The plotted return half is constructed by time reversal; the caption
explicitly warns that visual closure is not an independent periodicity test.
Selected close near misses and opposing defects at unrelated candidates are
not random trials or an intermediate-value bracket.

The unversioned `../burrau` notes used in this revision, plus the original F30
plotting script, image, and audit, are preserved in
`paper/archive/burrau-2026-09-06/`. Treat that directory as historical supporting
material, not as a replacement for the reviewed main paper.

## Mathematical status and guardrails

Both the integer conjecture and stronger real-parameter conjecture remain open.
Do not silently promote numerical evidence or historical draft claims.

- The all-time certified middle interval is `[0.29, 0.2900000101]`.
- The wider `[0.29, 0.29002]` result excludes only the first positive inertia
  maximum as a brake; it is not an all-time nonperiodicity theorem there.
- The wider affine-generator `[0.29, 0.290002]` result still awaits its independent
  inclusion-algebra audit before promotion.
- The punctured near-isosceles all-time neighborhood has an existential cutoff.
- Infinitely many thin windows contain a positive-lower-density subset of
  `(4n^2-1,4n,4n^2+1)`, with density measured by `n`, not all primitive triples.
- Uniform first-turn exclusion does not control every later return.
- The proved accumulating collision parameters are real, not known rational.
- The old unconditional one-switch forced-lag inference was withdrawn. The
  corrected lemma needs a terminal integrating-factor bound that is not proved
  for the full gravitational family. Preserve the exact scalar counterexample.

## Build and checks

From the repository root:

```sh
env TECTONIC_CACHE_DIR=/private/tmp/burrau-tectonic tectonic --keep-logs paper/main.tex
```

The temporary cache avoids sandbox restrictions on the default cache. The
mathematical environment is `.venv/bin/python`. The prior plotting environment
was `/private/tmp/burrau-paper-venv/bin/python` with NumPy/Matplotlib; temporary
environments are disposable. `paper/make_figures.py` rebuilds vector figures.
Do not regenerate the externally supplied fan/F30 images merely to build LaTeX.

The consolidation pass had 190 selected tests passing and all 100 archived
middle tiles passing the coverage auditor. The rationality/F30 revision had
22 targeted tests passing, symbolic oscillator checks, recomputed F30 geometry,
and visual inspection. These did not rerun CAPD integrations. A useful quick
regression command is:

```sh
.venv/bin/python -m pytest -q tests/test_f30_mass_side.py tests/test_brake_residual.py tests/test_symbolic_brake_residual.py tests/fable/test_event_reduction.py
.venv/bin/python scripts/audit_fable_middle_campaign.py
```

Before handing over a revised PDF, inspect its opening and changed figures,
check references/layout warnings, and run `git diff --check`. The pre-existing
amsmath notice about `\over` is not an unresolved reference or overflow.

## Publication and preservation

The post is `https://oklo.org/2026/09/05/add-astra/`. Its closing “is here” link
serves `https://oklo.org/wp-content/uploads/2026/09/pythagorean-burrau-interim-report.pdf`.
The latest local, staged, and publicly downloaded PDFs matched byte-for-byte:

`d2b50b0152d37ee0f65c3aebb39dbd771d19439187783ad5cd9e9062868c9f79`

Only that PDF was deployed; post wording, theme, and database were not changed.
The previous 22-page public PDF is in
`paper/archive/oklo-interim-report-2026-09-05.pdf` and the local Oklo publication
artifact directory. Preserve that backup. Rebuilds can change PDF metadata and
hashes without textual changes; use the actual served bytes when verifying.

`/Users/greglaughlin/Projects/oklo-org` is the local WordPress mirror. Read its
`HANDOFF.md` before deployment. Use its configured `ssh oklo` access and stage
changes locally, then deploy only the requested file with rsync. SSH required
an approved network escalation in this session. Do not expose credentials.

The Oklo mirror has no Git remote and has unrelated uncommitted theme, app,
audio, and mathematical-post work. Do not bundle it into this task. Publication
records and the old PDF are also preserved in the private research repository
so this handoff does not depend on creating or publishing a site repository.
The current main PDF, companion PDF, edited source, figures, memories, and
supporting archive are intended to be preserved together on `origin/master`.

---

End of handoff prompt.
