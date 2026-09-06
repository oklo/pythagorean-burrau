# Supporting Burrau notes preserved September 6, 2026

These are unchanged snapshots from the unversioned sibling `burrau` directory,
selected because they supplied the arithmetic examples and F30 illustration
used in the September 6 manuscript revision. Their original relative directory
layout is retained so the F30 note can find its figure.

- `paper/`: four short LaTeX notes and their existing PDFs, covering measure
  zero versus rationality, an isolated rational periodic parameter, an engineered
  sparse-rational periodic family, and the continued F30 near miss.
- `scripts/plot_f30_mass_side_periodic_candidate.py`: original numerical
  shooting/plotting generator (NumPy, SciPy, Matplotlib).
- `plots/` and `data/`: the original F30 PNG and plotting audit, also copied
  to the current manuscript's figure directory.

These notes are historical supporting material, not additional certified
gravitational results. The reviewed main manuscript states the authoritative
qualifications, including the nonzero Pythagorean defect, unvalidated root,
plotting-versus-campaign residual distinction, and time-reversed construction
of the plotted return half. Do not silently promote an informal statement in
an archived note over the current paper.

The generator writes into its parent archive's `plots/` and `data/` paths.
Copy the archive to a scratch directory before rerunning it if the preserved
snapshot is to remain unchanged. No integrations were rerun during preservation.
Unrelated exploratory plots and regenerable trajectory caches were not imported.
