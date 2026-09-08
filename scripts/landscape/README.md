# Global landscape tools (ordinary numerics, 2026-09-07)

These are the double-precision tools used for the global scan of the tied
family and for the near-brake / mass-side periodic-orbit atlas described in
`docs/SYZYGY_REVERSAL_STRUCTURE.md`. Nothing here is a certificate.

- `tied3j.c` — Taylor-series integrator (order 26, local time scaling) in
  pair-adapted Jacobi coordinates with chart switching to the closest pair.
  Records the syzygy sequence (middle-body letters), Montgomery
  `z`-extrema, inertia maxima, kinetic-energy minima per inter-syzygy arc,
  stutters, minimum separations, and the paper's escape lemma verdict.
  `cc -O2 -o tied3j tied3j.c -lm; ./tied3j U [TMAX ORDER RCOLL]` prints one
  JSON line.
- `ms3.c` — same integrator for the general mass–side family
  `(m1, m2, 1)`; prints the Cartesian state, complete Hopf brake residual and
  nearest kinetic-energy minimum at a requested time.
- `analyze3.py` — summary statistics of a scan (`*.jsonl` of `tied3j` lines).
- `refine3.py` — multi-scale zoom on local minima over `u` of the minimal
  kinetic energy near a tracked event (stdin lines `u t`).
- `newton_ms.py` — Newton continuation of a tied near-brake into a periodic
  brake orbit of the mass–side family (stdin lines `u t`); produces the
  entries of `data/mass_side_periodic_atlas.json`.
- `sens.py` — finite-difference sensitivity of the state to `u`.

Scan grids used: step `2e-5` on `[0.005, 0.4142]`, `2e-6` on
`[0.16, 0.36]`, `1e-6` on `[0.36, 0.4142]`; runs take about ten
milliseconds each. Results below `u\approx0.12` are unreliable in double
precision because the first `{1,3}` encounter misses collision by
`\sim0.135\,B^{11}`.
