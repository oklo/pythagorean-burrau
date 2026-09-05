# Working paper

Read [main.pdf](main.pdf): the revised main argument, historical introduction,
counterexample campaign, and figures (22 pages in the September 5 build).
The global conjecture remains open.

`main.tex` loads the editable files in `sections/` and `references.tex`.
[technical-details.pdf](technical-details.pdf) retains the expanded
calculations and certificate arguments (50 pages), with the mathematical
corrections applied. The main paper provides a proof-dependency index.

The pre-review PDF was 35 pages, dated August 24. Its later August 26 LaTeX
source had grown substantially and was no longer represented by that PDF.
Both are preserved in `archive/`; they are historical, uncorrected versions.
See [the review](../docs/MANUSCRIPT_REVIEW_2026-09-05.md) and especially
[the forced-lag correction](../docs/FORCED_LAG_ENDPOINT_CORRECTION.md).

## Build

From the repository root, using Tectonic:

```sh
tectonic --keep-logs paper/main.tex
tectonic --keep-logs paper/technical-details.tex
```

In an environment that requires a writable temporary cache:

```sh
TECTONIC_CACHE_DIR=/private/tmp/burrau-tectonic tectonic --keep-logs paper/main.tex
TECTONIC_CACHE_DIR=/private/tmp/burrau-tectonic tectonic --keep-logs paper/technical-details.tex
```

Alternatively, run `pdflatex` twice on each document from `paper/`.
Tectonic was used for the reviewed build; pdfLaTeX was not available in
that environment. The PDF outputs are ignored by the repository's existing
`.gitignore`, but are generated and available locally.

## Figures

`make_figures.py` generates the two vector PDFs from formulas and
`data/periodic_atlas_campaign.json`. It needs NumPy and Matplotlib; these
are plotting dependencies, separate from the research environment's lock.
For example:

```sh
uv run --no-project --with numpy --with matplotlib python paper/make_figures.py
```

The reviewed figures used Python 3.13, NumPy 2.5.2, and Matplotlib 3.11.1
in an isolated temporary environment. The original fan image was copied
unchanged from `../burrau/plots/oklo_pythagorean_fan_trajectory_progression.png`.
Its adjacent metadata JSON is copied to `figures/fan-provenance.json`.
The caption records interval widths, sampling, opacity, and spatial clipping.
No displayed trajectory is represented as an interval certificate.

## Review artifacts

- `../docs/MANUSCRIPT_REVIEW_2026-09-05.md`: findings, edits, and validation scope.
- `../docs/PYTHAGOREAN_HISTORY_SOURCES.md`: original-source locations and remaining gaps.
- `../docs/FORCED_LAG_ENDPOINT_CORRECTION.md`: the substantive mathematical correction.
- `../tests/test_forced_lag_endpoint.py`: exact regression for the failed scalar inference.
