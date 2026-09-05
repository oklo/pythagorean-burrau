# Manuscript review and revision — 2026-09-05

The revised [main paper](../paper/main.pdf) is **22 pages**, with a new
accessible introduction, an early counterexample-construction section,
three figures, and a shorter presentation of the central proof arguments.
The [technical companion](../paper/technical-details.pdf) is **50 pages**
and retains detailed calculations and certificate arguments. Neither
claims a proof of the universal conjecture.

## Which document was current?

`paper/main.pdf` was the requested **35-page** document, generated August
24. Its `main.tex` source was last edited August 26 and had grown to 3,552
lines; the PDF did not contain all those later additions. Both original
files are preserved unmodified in `paper/archive/`. The main source now
loads named section files, so the smaller `main.tex` is an entry point,
not evidence that the manuscript's mathematics has been deleted.

## Findings requiring correction

### 1. The scalar one-switch proof has a substantive endpoint gap

The old argument inferred `w>0` in the interior from a positive-to-negative
forcing switch and the geometric terminal equality `w(S)=0`. It multiplied
by an integrating factor, then assumed that the product also ended at zero.
The coefficient is singular at syzygy; this implication is not justified.
Its integrating factor was also based at launch, where the integral diverges.

The review supplies an exact scalar counterexample with the same types of
endpoint singularity and replaces the old assertion by a sufficient lemma
with the additional hypothesis `liminf M(s)w(s) >= 0`. That bound is still
open for the full tied family. Details and the explicit example are in
[FORCED_LAG_ENDPOINT_CORRECTION.md](FORCED_LAG_ENDPOINT_CORRECTION.md), and
its algebra and sign structure are checked by a new symbolic regression.

The exact forced-lag equations remain correct. The counterexample is to
the scalar inference, **not** to the Newtonian conjecture. The independently
assembled middle-interval and near-isosceles arguments do not use this
unproved inference. Prominent correction notices were added to the six
active research records that advertised the old shortcut, including the
persistent research memory and August handoff. Their historical text is
retained under that superseding notice.

### 2. The initial brake cannot pass a nonvanishing cover test

At `t=0`, all three proposed disjuncts fail: `I'=0`, `K=0`, and the brake
residual is zero. The theorem now treats a launch interval separately:
`U<2U0` implies `I''<0`, hence `I'<0` for every positive time in that
window. Only subsequent enclosures use the nonvanishing disjunction.
The source certificate already contained this launch-concavity mechanism;
the manuscript's logical description omitted it. Both documents now state
it explicitly, including parameter-dependent terminal times and intervening
flow-tube coverage.

### 3. Escape quantities were used before a theorem defined them

The terminal escape lemma now precedes its first use. The middle-interval
proof explicitly defines its binary energy, outer radius, energy margin,
and tidal allowance and identifies them with the lemma's hypotheses.
The transported binary energy avoids division by a tiny separation when
checking the terminal enclosure. The collision-or-escape alternative is
kept distinct from guaranteed collision-free escape.

### 4. Numerical and exact conclusions needed sharper boundaries

The new counterexample section reports all six numerical candidates and
nonzero Pythagorean defects. It records the independent integrator checks,
smallest-singular-value evidence, and limitations of sampled separation
and physical energy reconstruction. It explicitly identifies the F30 and
F4 tied-right searches as incomplete. No numerical candidate is promoted
to an interval-certified periodic orbit or a rational counterexample.

Opposite defects at unrelated roots are not presented as a connected
branch or an intermediate-value bracket. Rank four of five shooting
equations does not establish a branch. Retracing brake loops do not carry
a nontrivial full-loop free-group invariant; labelled finite syzygy
itineraries require their own continuity hypotheses.

The proof overview distinguishes: a first-maximum exclusion on
`[.29,.29002]`; all-time exclusion on `[.29,.2900000101]`; an existential
near-isosceles cutoff; and thin-triangle escape windows rather than a
uniform thin-end theorem. Positive density is stated for the explicit
family's indices, not for all primitive triples ordered by size.

### 5. Notation, presentation, and stale statements

- Corrected missing backslashes in `qquad`, malformed `cal M`, and
  literal prose placeholders for mathematical symbols.
- Removed a duplicated equation tag and the obsolete assertion that a
  transversality result was not validated immediately before a theorem
  validating its sign.
- Distinguished pair angular-momentum signs from instantaneous torques,
  which vanish at collinearity.
- Defined the reduced masses and energy convention before use in the
  main paper; retained the Jacobi-degeneracy guards on brake residuals.
- Replaced stale interval-width diagnostics with the exact scope of the
  archived theorem and an explicit warning that broader experimental
  covers are not included.
- Added numbered cross-references, a proof-dependency index, complete
  historical titles and links, and publication/preprint distinctions.

## Readability and culling

The introduction begins with the physical 3–4–5 experiment and explains
periodicity, simultaneous stops, exact integer data, scaling, the rational
parameter, and the meaning of the partial results before the technical
sections. It separates Meissel's original periodicity expectation from
the current all-integer nonperiodicity conjecture.

The main argument follows a proof-oriented sequence: precise experiment;
second brakes and finite certificates; equal-leg endpoint; thin-triangle
matching and density; torque-history obstruction; unresolved global task.
The near-isosceles all-time result is no longer buried inside pages of
torque coefficient bookkeeping.

Removed from the main reading path: long raw Bernstein coefficient lists,
repeated instantaneous ambient counterexamples, detailed fourth/fifth
collision transition boxes, intermediate unsuccessful enclosure widths,
and repeated descriptions of partially completed stages. Essential
computational details are preserved in the technical companion and linked
proof notes. One representative ambient witness remains in the main text
to show why a history constraint is needed. The obsolete catalogue-only
section is replaced by the current six-seed construction campaign.

The companion is deliberately a detailed research record rather than a
second polished introduction. Its lengthy local collision classifications
are retained for verification and future work; the main paper explains
why they do not yet give a global classification.

## Historical conclusions and their limits

The [source audit](PYTHAGOREAN_HISTORY_SOURCES.md) records original scans,
page locations, access scope, and unresolved questions. The introduction
uses Burrau's original account, Szebehely's PNAS paper and both 1967 AJ
papers, original intervening Strömgren/Zumkley material, and later author
or publisher sources.

The exact path by which Szebehely first encountered the problem remains
**unidentified**. The paper says so. The evidence supports a 1966 revival
and earlier awareness/related calculations, not complete dormancy and not
continuous recomputation of the exact 3–4–5 trajectory. No unsupported
attribution of the modern conjecture to Tanikawa or Montgomery was added.

## Figures

1. Exact initial geometry and unit-circle parameterization, generated as
   a vector PDF with masses, opposite lengths, and endpoint labels.
2. The requested fan PNG, copied without changing pixels and supplied
   with row-width labels and a detailed caption. Metadata verify the
   independent angular expansion, common logarithmic hypotenuse scale,
   finite display-time horizon, speed-opacity mapping, and clipped
   outgoing trajectories. Its smallest interval is about 9,901 times
   wider than the rigorous interval; the distinction is explicit.
3. All six numerical candidates relative to the exact mass circle, plus
   their signed defects. No branch-connecting lines are drawn between
   the candidates.

The plot source and metadata are stored with the paper. The fan is the
inspected snapshot copied during review; the adjacent project regenerated
its source image later in the session, so its current file need not have
the snapshot hash. The new vector
figures and representative PDF pages were visually inspected.

## Validation performed

- **101 tests passed**: 89 across the exact mutual-distance/torque algebra,
  brake residuals, middle escape field and chart maps, explicit skinny
  family, skinny regularization, isosceles collision, and the new scalar
  endpoint-counterexample test (44.70 seconds), plus 12 escape-certificate,
  event-reduction, and campaign-audit tests (0.30 seconds).
- The existing middle-campaign archive audit passed: **100** exact
  requested/PASS interval matches, common adjacent rational endpoints,
  pinned CAPD commit, and matching archived logs. This verifies archive
  consistency and coverage arithmetic; it is not a fresh integration.
- Both LaTeX documents compile with Tectonic. Cross-references and
  citations resolve; the main paper's layout was inspected, including
  its figures and proof-source table.
- Ruff checks pass for the new plotting script and symbolic regression.
- The old source/PDF and copied fan image were preserved; checksums are
  recorded in `paper/review-provenance.json`.

The review reads the full mathematical draft and assesses its proof
structure, selected derivations, and certificate interfaces. It **does
not** claim a fresh independent reconstruction of every long-tail estimate
or a replay of every CAPD certificate. A journal-level independent audit
of those computational components remains worthwhile. The concrete
corrections above have been applied; the universal conjecture is still open.
