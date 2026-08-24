# Correlation-preserving section maps near the fourth planar collision

Status: **EXACT SYMBOLIC IDENTITY** for the section construction and
**VALIDATED NUMERICAL RESULT** for the individual parameter tiles listed
below.  A finite overlapping cover has not yet been replayed, so this note
does not promote the observations to a continuum theorem.

## Anchored one-parameter graph

Let (X(k)) denote the negative-primary LC state at the exact rational clock
\(37184019/10^8\).  For a rational anchor (a), an outward enclosure
(A\ni X(a)), a tile (K) with midpoint (m), and

\[
 T_i\supseteq X_i'(\operatorname{conv}(K\cup\{a\})),
\]

the coordinatewise scalar mean-value theorem gives

\[
 X_i(k)\in A_i+T_i(k-a).
\]

The verifier represents this as a CAPD doubleton with center

\[
 x_i=\bar A_i+\bar T_i(m-a),
\]

one shared generator (C_{i0}=T_i), radius (r_{0,0}=K-m), and independent
remainder

\[
 r_i=(A_i-\bar A_i)+(T_i-\bar T_i)(m-a).
\]

The identity

\[
 x_i+T_i(k-m)+r_i=A_i+T_i(k-a)
\]

is checked by `test_common_clock_graph_recenter_is_exact_algebraically`.
Different scalar MVT points may occur in different coordinates; the
independent remainder enlarges the set and therefore preserves inclusion.
“Correlation-preserving” here means that the dominant common parameter
generator is retained, not that later CAPD reorganizations represent the
exact graph.

An adversarial audit found that the first implementation formed the
derivative hull from (K) and the fourth-root box but omitted the fixed
anchor when (K<a).  The production helper now explicitly includes all
three of (K), the root box, and the selected anchor.  No replay made before
that repair is used as evidence.

## Flow projection onto a section

In nonredundant elliptic coordinates the reversed two-centre field has

\[
 \alpha'=-p_r,\qquad \beta'=-p_i.
\]

To project a correlated set to (alpha=A), append the frozen defect
(d=A-\alpha_0) without reboxing, then integrate for one artificial unit
with the whole vector field multiplied by (d/(-p_r)).  Thus

\[
 {d\alpha\over d\tau}=d,
 \qquad \alpha(1)=A.
\]

For \(\beta=B\), use \(d=B-\beta_0\) and the factor \(d/(-p_i)\). Directed
whole-step audits establish (p_r<0), and on the beta leg (p_i>0); the
time changes are orientation preserving and their denominators stay away
from zero.  Every other field component is multiplied by the same factor,
so the artificial curve is the original orbit with a changed clock.  The
suffix defects remain frozen, retaining their correlations through later
maps.  The exact algebra is checked by
`test_common_clock_section_projection_is_an_orbit_reparametrization`.

CAPD reports Poincare crossing times as absolute set times.  An independent
audit caught an initial diagnostic bug that summed those absolute values.
Both helpers now return the relative leg time.  The bug did not affect the
propagated sets or terminal inequalities, but all stored time diagnostics
predating the repair are discarded.

A second audit caught a boundary case in the fixed-duration continuation:
the old branch skipped a duration of exactly 500 milliseconds while still
adding it to the diagnostic clock. The production code now tests the exact
remaining interval rather than the integer branch label. No stored
certificate used that duration.

## Fixed anchors and current validated reach

Three independent MPFR-200 anchors are archived at

\[
 1.264009098940,\qquad
 1.264009098934,\qquad
 1.264009098933320.
\]

The first two sharpen useful portions of the lower band.  The near-root
anchor does not close the root boundary: even its point enclosure wraps in
the terminal bridge.  This is a failed quantitative formulation, not a
dynamical counterexample.

The robust tile

\[
 1.264009098938900\le k\le1.264009098939100
\]

passes the correlated chain

\[
 \alpha=2\pi\longrightarrow\beta=-1
 \longrightarrow\text{heavy-binary bridge}
 \longrightarrow\text{terminal escape cones}.
\]

Its bridge keeps both light-primary squared distances above
`0x1.3d6bbd67dcbafp-5`; the restricted and finite-mass-form terminal
margins have lower bounds `0x1.3eb5b0e36f346p+2` and
`0x1.474158b8aadc5p+2`, respectively. The exact replay is archived in
`data/validated_planar_fourth_common_clock_correlated_tile_capd.txt`.

Point and microtile experiments reached within roughly (2.2\times10^{-14})
of the certified fourth-root box, but they do not form an overlapping finite
cover.  They remain **ORDINARY NUMERICAL EVIDENCE** for atlas design.

## Remaining obligation

Construct and replay a deterministic finite list of overlapping rational
tiles joining the root-local theorem to the existing continuum beginning at
(1.264009099014).  Until exact overlap with an effective root neighborhood
is proved, the lower band remains open.  The most direct repair is a tighter
near-root fixed-clock graph or a parameter-correlated graph based at the
transverse fourth-collision section.
