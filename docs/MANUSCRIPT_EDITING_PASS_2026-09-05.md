# Editorial consolidation — September 5, 2026

The current manuscript is [paper/main.pdf](../paper/main.pdf), built from
[paper/main.tex](../paper/main.tex) and its named section files. It is **29
pages including references**, at the existing 11-point size and one-inch
margins. This pass follows the earlier September 5 review archived in commit
`1518caaddd91c9459fbd30ea49ecb398da30a2a1`.

The manuscript was identified by its date, history, and scope after comparing
the main repository, both `pythagorean-burrau-fable*` directories, and the
papers and Astra handoff in `../burrau`. The main repository's September 5
history-and-proof manuscript supersedes its August draft; the newer files in
`burrau/paper` concern individual numerical or arithmetic questions. Git
records the project author's name rather than model-level authorship.

## Editorial changes

- Replaced the question-form title and its “dance” metaphor with **The
  Pythagorean Three-Body Problem: History, Exact Reductions, and Partial Results
  toward Nonperiodicity**. Removed the metaphor from the opening as well.
- Reduced the abstract from 168 to 76 whitespace-delimited words, a factor of
  2.21. It states the established interval and endpoint exclusions, the
  positive-lower-density primitive subfamily, the numerical near misses, and
  the unresolved universal conjecture.
- Retained the physical 3–4–5 opening, Meissel–Burrau history, subsequent
  numerical work, rational-parameter explanation, brake interpretation, and
  all three figures. Trimmed elementary instructions, rhetorical questions,
  repeated cautions, and prose responding to unstated drafting questions.
- Replaced conversational section titles and instructions to the writer with
  descriptions of the mathematical subject. Kept qualifications that affect
  the meaning of a theorem or numerical claim.

## Material incorporated from the technical companion

The companion was read through its mathematical sections. The consolidated
paper now carries the following argument structure, with direct references
to the detailed certificate notes rather than requiring a second manuscript
for the principal statements and reasoning.

| Main-paper location | Incorporated material |
| --- | --- |
| Exact problem and reductions | Formal integer and real conjectures; incenter/center-of-mass identity; exact initial inertia and potential; initial right-angle departure; reduced kinetic energy and rotation reconstruction; justification of the Hopf residual. |
| Finite certificates | Both terminal escape criteria, including the criterion for a possibly expanding inner pair needed at the zero-energy joint limit; bootstrap proofs; existing first-maximum and all-time middle-interval results. |
| Equal-leg endpoint | Analytic forced LC equations and exact tied launch tangent; first-syzygy variational sign and endpoint factorization; collision unfolding; four-collision continuation and terminal escape. |
| Thin triangles | First-miss coefficient and angular momentum; restricted plunge equations; parabolic speed bracket; full-state incoming matching with LC normal invariants and the order of limits; finite Jacobi certificate and compactified stable-manifold transversality; transfer and equidistribution proof. |
| Returning trajectories and collision boundaries | Uniform first-turn angular-momentum exclusion; second-encounter parabolic sign; triple-endpoint modes and finite-mass wedge; joint scaling and the one-parameter planar limit; stable-tail enclosure; four local collision-root enclosures; differentiated collision-graph persistence; collision-or-escape neighborhoods; exact real collision sampling. |
| Torque history | Explicit threshold polynomials; integral constraints; corrected conditional lag argument; centrifugal reduction to two history variables; contact and terminal amplitude thresholds; exact energy-compatible counterexample to a static barrier. |
| Global problem and reproducibility | Remaining encounter/arithmetic obligations, Jacobi–Maupertuis interpretation, and expanded source/certificate index. |

The former companion is retained as a research archive. Long coefficient
lists, intermediate enclosure widths, repeated static witnesses, and the
individual fourth/fifth-encounter chart-switch logs remain there or in the
linked proof notes. They have not been deleted. The numerical candidate
orbits remain explicitly uncertified. The wider affine-generator middle
cover has not been promoted beyond its recorded evidence status.

## Mathematical corrections and clarifications in this pass

- The pair-separation lower bound is explicitly restricted to **brake events**.
  It is not a lower bound on all intervening close approaches.
- Replaced the imprecise “even-order zero at a transverse brake” with the
  actual time expansion of kinetic energy: a positive quadratic term, with
  an even remainder by time reversal.
- The near-isosceles angular-momentum result now states what its certificate
  proves: the launch sign has reversed **by the specified LC section**.
  It does not infer a sign change between unspecified sides of an encounter.
- Restricted the torque weighted-average argument to the ordered positive-area
  arc beginning at launch. Arbitrary later ordered arcs need not have the
  same integral history.
- Made the escape bootstraps explicit, including outer radial acceleration,
  total tidal allowance, and the remaining inner-collision alternative.
- Distinguished the physical and rotating-frame derivatives in the reduced
  kinetic energy, fixed the normalized planar parameter used by the collision
  table, and defined the asymptotic remainder in the parabolic map.
- Preserved the prior correction to the singular integrating-factor inference.
  The conditional lemma still requires a terminal weighted bound; the scalar
  counterexample and the open hypothesis remain in the main paper.
- Rephrased ordinary signed-event diagnostics as numerical evidence, with no
  promotion to an exact global sign theorem.
- Retained the distinction between real collision parameters and rational
  parameters, local root uniqueness and a global collision classification,
  and regularized comparison motion and classical positive-mass motion.

## Verification

**190 existing tests passed** in 88.99 seconds. These cover exact reductions,
reduced kinetic energy, brake residuals, mutual-distance and torque identities,
first-encounter regularization, explicit-family phase formulas, incoming-tail
invariants, restricted scattering and collision-chart algebra, near-isosceles
variation, the scalar endpoint counterexample, escape interfaces, and middle
event/chart/campaign checks. The command used was:

```sh
uv run pytest -q tests/test_reductions.py tests/test_reduced_system.py \
  tests/test_brake_residual.py tests/test_symbolic_brake_residual.py \
  tests/test_mutual_distances.py tests/test_symbolic_identities.py \
  tests/test_skinny_regularization.py tests/test_explicit_skinny_family.py \
  tests/test_incoming_tail.py tests/test_restricted_scattering.py \
  tests/test_isosceles_collision.py tests/test_forced_lag_endpoint.py \
  tests/test_escape_certificate.py tests/test_middle_escape_symbolic.py \
  tests/test_middle_escape_endgame_maps.py tests/test_fable_middle_campaign_audit.py \
  tests/fable/test_event_reduction.py tests/fable/test_tied_first_maximum_charts.py
```

An additional symbolic calculation checked that the newly regrouped torque
polynomials equal the companion's expanded forms and reproduce the collinear
threshold exactly. The separate archive auditor passed all 100 middle-cover
tiles, including exact requested/PASS endpoints, adjacent coverage, dependency
pin, and summary/archive consistency:

```sh
.venv/bin/python scripts/audit_fable_middle_campaign.py
```

The historical source audit was consulted and primary sources for the modern
brake/syzygy framework, catalogue counts, the 1967 solution, and McGehee's
stable-manifold theorem were checked. The latter's original article confirms
pages 70–88 despite inconsistent metadata on one author webpage; its DOI has
been added to the bibliography.

Tectonic builds the consolidated PDF with resolved citations and cross-references.
The final log has no overfull or underfull boxes; its remaining amsmath notice
concerns the pre-existing use of plain-TeX `\over`. Representative pages were
visually checked, including the opening, collision-root table, and expanded
reproducibility appendix.

This is a mathematical and editorial review of the manuscript, selected exact
derivations, and the assembly of its archived computer-assisted results. It
does **not** reconstruct every long-tail analytic estimate independently or
rerun every CAPD integration. The tests verify algebra and implementation
interfaces; the archive audit verifies recorded coverage, not a new interval
integration. These limits are also stated in the manuscript. The universal
nonperiodicity conjecture remains open.
