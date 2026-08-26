# Independent audit handoff: affine-generator endgame certificates

## Decision requested

Decide **ACCEPT** or **REJECT** for the following proposed promotion:

> Every real $u\in[0.29,0.290002]$ is nonperiodic.

This is presently only a **VALIDATED NUMERICAL RESULT / COMPUTER-ASSISTED
THEOREM CANDIDATE**.  Do not accept it from the two successful runs alone.
Promotion requires an adversarial source-level audit of the affine-generator
inclusion invariant and its CAPD interface.

The already reviewed theorem on $[0.29,0.2900000101]$ is not under review and
must remain valid regardless of the decision here.

## Exact evidence under review

- Main source: `src/fable/verification/middle_escape_endgame_capd.cpp`.
- Analytic statement: `docs/AFFINE_REMAINDER_GRAPH.md`, Theorem AGR.
- Algebra regression: `tests/test_c2_parameter_graph.py`.
- Fail-closed log parser: `scripts/audit_affine_endgame_log.py`.
- Campaign driver: `scripts/run_affine_middle_campaign.py`.
- Exact certificate logs:
  - `data/middle_affine_pg2_width_1e6_full.log`, covering
    $[0.29,0.290001]$, SHA-256
    `c8944f75b495cbb9890c206e54c8710a6f600a8c0122498c3d0d68a59a84947d`;
  - `data/middle_affine_pg2_tile_290001_290002_full.log`, covering
    $[0.290001,0.290002]$, SHA-256
    `f2b75caae96fc1905f56c60a4c1b79445c3f4fbb870bb928ccb8a49d5dcf92d1`.
- Relevant main-branch commits, in construction order:
  `3581fc3`, `0c977ac`, `21cedf5`, `e9a254b`, `79294d3`, `91966bb`.
- Pinned CAPD 6.1.0 source commit:
  `731079217a9254ea2948d742df2b170895effe7f`.

The two logs independently pass the parser.  Their respective largest hulls
are $0.0914731$ and $0.0899364$; terminal escape margins are $3.0331061$ and
$2.9754959$.  The deterministic pinned-source probe reports
`PASS_CAPD_C2_SEMANTICS` at 160-bit precision; source inspection remains a
mandatory independent check.

## Representation invariant to prove

At each itinerary node and for every parameter deviation
$\delta=u-u_c$ in the exact tile, the genuine fiber must lie in

\[
 X(\delta)\in x+T\delta+Q\delta^2+G\Xi+E,
 \qquad \Xi=[-1,1]^k.
\]

The columns of the point matrix $G$ share their source coefficients across
all state coordinates.  The box $E$ covers interval derivative width and
nonlinear spill.  Every transition must preserve this inclusion before the
next collision/brake tube or terminal inequality is evaluated.

## Mandatory adversarial checks

1. **Initialization and hull.** Verify `DirectCorrelatedGraph::generator_hull`,
   `remainder_hull`, `lift_defect_to_generators`, and `c0_set`.  Lifting a
   centered coordinate residual to a new diagonal generator may enlarge but
   must never narrow the represented set.  The C0 set must contain the full
   quadratic graph and every generator coefficient simultaneously.

2. **Static chart maps.** Check `transform_graph_c2` against Theorem AGR,
   including all factors of two in the six Taylor forms, interval-midpoint
   spill in $J_xG$, the $\delta^3$ and $\delta^4$ terms, and use of the complete
   convex C0 hull for the Hessian enclosure.

3. **Poincare maps.** Check `project_graph_pg2` separately.  Confirm that the
   thin-anchor derivative multiplies every point generator; the C2 run on the
   complete hull supplies $TT,TQ,TR,QQ,QR,RR$; and CAPD's `computeDP` has
   already included first- and second-order return-time derivatives.

4. **CAPD custom directions.** Inspect the pinned CAPD source, not only our
   comments.  Establish that the custom C1 columns supplied by `pg2_c2_set`
   propagate as the intended $T,Q,R$ directions and that diagonal Hessian
   entries use CAPD's factorial-normalized convention.  The deterministic
   probe in `src/fable/verification/capd_c2_semantics_probe.cpp` is supporting
   evidence, not a substitute for reading the relevant CAPD implementation.

5. **Exact rows.** At every coordinate section, justify setting the selected
   row of $T,Q,E,G$ to zero and the selected anchor coordinate to the exact
   section value.  Separately justify resetting the frozen `ww` row to
   $(x,T,Q,E,G)=(u_c,1,0,0,0)$ after every map.

6. **Direct-image intersection.** Prove that intersecting $E'$ with
   `direct_image - x' - T'D - Q'D^2 - G'Xi` cannot discard a genuine fiber,
   even though the subtracted interval hulls forget correlations.  Check the
   subsequent outward centering at zero.

7. **Residual relifting.** Verify that repeated coordinatewise relifting adds
   independent source variables and therefore only enlarges the zonotope;
   it must not silently reuse a coefficient whose correlation has changed.

8. **Safety and terminal use.** Confirm that each independent swept C0 tube
   begins from a hull containing the affine graph, covers through the latest
   fiber return time (including switch instants), and enforces collision and
   brake exclusion continuously.  Confirm that terminal inequalities are
   evaluated on a box containing every terminal fiber, not merely at an
   anchor or a fixed clock.

9. **Artifact-to-claim chain.** Audit exact requested and reported rational
   endpoints, the 85-row ordered itinerary, required mode flags, monotone
   generator counts, terminal inequalities, the PASS row, and the pinned CAPD
   identifier.  Verify that the two closed tiles share exactly the rational
   endpoint $290001/10^6$.

10. **Smallest attack tests.** Try to construct a scalar or two-dimensional
    quadratic map where a missing mixed term, wrong Hessian normalization,
    incorrect section-row reset, or direct-image subtraction loses a point.
    A rejection should identify the first invalid line and such a minimal
    counterexample whenever practical.

Do not accept based on genericity, ordinary numerical agreement, small
remainder size, or the independent C0 safety cover alone.  The cover proves
continuous-time safety only if the propagated graph itself still contains
every initial fiber.

## Reproduction commands

From the repository root:

```text
env UV_CACHE_DIR=/private/tmp/pythagorean-uv-cache \
  uv run pytest -p no:cacheprovider \
  tests/test_audit_affine_endgame_log.py \
  tests/test_run_affine_middle_campaign.py \
  tests/test_c2_parameter_graph.py \
  tests/test_middle_escape_endgame_maps.py \
  tests/test_middle_escape_symbolic.py

python3 scripts/audit_affine_endgame_log.py \
  data/middle_affine_pg2_width_1e6_full.log \
  --expected-left 29/100 --expected-right 290001/1000000

python3 scripts/audit_affine_endgame_log.py \
  data/middle_affine_pg2_tile_290001_290002_full.log \
  --expected-left 290001/1000000 --expected-right 290002/1000000

scripts/run_capd_c2_semantics_probe.sh \
  /private/tmp/pythagorean-capd /private/tmp/pythagorean-capd/build-mp 160
```

For a complete fresh replay of the second tile, set the four graph modes plus
pair-23 section synchronization and run the pinned wrapper:

```text
env FABLE_ENDGAME_GRAPH=1 \
  FABLE_ENDGAME_GRAPH_C2=1 \
  FABLE_ENDGAME_GRAPH_PG2=1 \
  FABLE_ENDGAME_GRAPH_AFFINE_REMAINDER=1 \
  FABLE_ENDGAME_GRAPH_PAIR23_SYNC=1 \
  scripts/fable_run_capd_middle_endgame.sh \
  /private/tmp/pythagorean-capd /private/tmp/pythagorean-capd/build-mp \
  290001 1000000 290002 1000000 160 1e-24 32
```

## Required response format

Return **ACCEPT** or **REJECT**, followed by findings ordered by severity.
For every finding give the exact source location, mathematical reason, and
smallest repair.  State separately whether the analytic AGR theorem, its C++
implementation, CAPD interface semantics, continuous-time cover, terminal
evaluation, parser, and the gap-free union each passed review.
