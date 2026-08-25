# Data

Only source-attributed catalog extracts and deterministic generated data belong
here.  Large caches are ignored.

`restricted_transversality_capd_certificate.txt` is the concise replay record
for the pinned interval proof in `docs/COMPUTER_ASSISTED_TRANSVERSALITY.md`.

`restricted_transverse_scattering_capd_certificate.txt` records the replayed
half-line scattering and rotation-coefficient certificate.

`triple_endpoint_turn_capd_certificate.txt` records the replayed positivity
certificate at the first turn of the universal triple-endpoint base.

`validated_planar_light_collision_root_capd.txt` records the correlated
interval-Newton collision root.

`validated_planar_collision_escape_tiles_capd.txt` records the stronger
ten-tile replay covering the explicit interval
`[1.2679251755, 1.2679451755]`, including the worst separation and escape
margins on every tile.

`validated_planar_second_light_collision_root_capd.txt` records the distinct
opposite-primary interval-Newton collision root.  Its three-chart regularized
continuation and terminal escape enclosure are recorded separately in
`validated_planar_second_collision_escape_capd.txt`.
The 195-tile contiguous enlargement is summarized in
`validated_planar_second_collision_escape_wide_capd.txt`.

`validated_planar_third_light_collision_root_capd.txt` and
`validated_planar_fourth_light_collision_root_capd.txt` record the next two
transverse collision roots.  The fourth record includes the separate
earlier-root uniqueness strip and strict parameter-gap exclusion needed to
prove classical reachability.

`validated_planar_fourth_to_fifth_entry_capd.txt` records the regularized
outgoing propagation of the whole fourth-root box to a uniformly analytic
fifth positive-primary LC chart.  Its scope is collision-or-fifth-entry, not
terminal escape.

`validated_planar_fourth_common_clock_cover_capd.txt` records the integrated
131-tile common-clock replay and its global worst-case margins on
`[1.264009099014, 1.264009099457]`.

`validated_planar_fourth_common_clock_anchor_mp_capd.txt` records the
MPFR-200 fixed-rational common-clock anchor used to diagnose the remaining
lower-band focus wrapping.

`validated_planar_fourth_common_clock_anchor_39_mp_capd.txt` and
`validated_planar_fourth_common_clock_anchor_near_root_mp_capd.txt` record
two additional MPFR-200 rational fixed-clock anchors used by the
correlation-preserving section graph.

`validated_planar_fourth_common_clock_correlated_tile_capd.txt` records one
native CAPD tile carried through the exact $\alpha=2\pi$ and $\beta=-1$
sections and the terminal bridge. It is an individual validated tile, not a
finite continuum cover.

The `fable/` subdirectory contains the imported point-certificate logs for
five named primitive triples. `fable/burrau_lc_damped_write_smoke.log`
records only a deliberately truncated finite-segment audit of the repaired
$u=1/3$ multipassage LC chart; it has no terminal PASS marker and is not a
$3{:}4{:}5$ theorem record.
`fable/middle_escape_endgame_1e9_sync_interval.log` records the correlated
exchange-section proof for every real $u\in[0.29,0.290000001]$.
`fable/middle_escape_endgame_1e9_sync_interval_96bit.log` is the independent
higher-precision and higher-order end-to-end replay.
`fable/middle_escape_terminal_1e9_sync_independent.log` is the separately
compiled phase-robust check of an outward-widened copy of its terminal box.

`f30_mass_side_periodic_candidate.txt` records an ordinary five-equation
shooting solution on the nearby Li--Liao $F_{30}$ family. Its masses match
the three opposite side lengths numerically, but its Pythagorean defect is
about $-3.356\times10^{-3}$. It is a counterexample-audit diagnostic, not a
validated periodic orbit or a Pythagorean counterexample.
