# Adversarial audit: the parameterized Poincaré-section graph

Date: 2026-08-25.  Auditor: independent second agent (branch
`fable/middle-terminal-escape`).  Subject: the primary worker's corrected
first-order parameter graph

\[
 X(u)\;\in\;x + T\,\delta + E,\qquad \delta=u-u_c,
\]

with nominal point $x$, interval tangent $T$, centered interval defect
$E$, and its Poincaré-return update.  All CAPD citations are to the
pinned source tree, commit `731079217a9254ea2948d742df2b170895effe7f`
(CAPD 6.1.0), read directly for this audit; file paths are relative to
`capdDynSys/include/capd/`.

**Overall verdict: the first-order graph update, with the hypotheses
H1–H7 made explicit below, is SOUND.  No counterexample exists; every
failure mode I could construct is intercepted by a thrown exception
(fail closed) rather than by silent containment loss.  Two implementation
details must be stated as hypotheses because violating them would be
silently unsound (H2: the C1 enclosure must be built on the full convex
graph hull including the anchor; H6: the defect intersection must
subtract $T_{\rm new}\Delta$ over the full parameter range, not a
fiberwise $\delta$).  Several further items are tightness, not
soundness, concerns and are listed separately.**

## 1. Setting and notation

Fix the chart state space $\mathbb R^{12}$ (a Levi–Civita chart of the
tied family with the frozen Euclid parameter as coordinate $ww$ and
physical time as coordinate $t_p$).  Let $\Delta=[-r,r]$,
$u=u_c+\delta$, $\delta\in\Delta$.  A *graph* is a triple $(x,T,E)$ with
$x$ a point (or thin interval) vector, $T$ an interval vector, $E$ a
centered interval vector, representing the statement

\[
 (\forall u)\qquad X(u)\in x+T\delta+E ,
\]

where $X(u)$ is the true fiber state (on a section, the fiber's crossing
point).  The *graph hull* is $H(x,T,E)=x+T\Delta+E$ (a box).  Let $s$ be
a coordinate section $\{y_s=c\}$ with crossing direction $D$, and let
$P$ denote the associated return map: for a state $y$ off the section
(or leaving it), $P(y)$ is the state at the first transversal crossing
of $s$ in direction $D$ after leaving the section.

## 2. Theorem PG1 (first-order graph step)

**Hypotheses.**

* **H1 (input containment).**  $X(u)\in x+T\delta+E$ for all
  $u\in u_c+\Delta$, with the parameter row exact:
  $x_{ww}=u_c$, $T_{ww}=1$, $E_{ww}=0$.
* **H2 (derivative domain).**  The rigorous C1 propagation used to
  produce the interval matrix $[DP]$ is initialized on a convex set
  containing the full graph hull $H(x,T,E)$ *and* the anchor $x$
  (e.g. the box $\operatorname{hull}(H,x)$; if $x\in H$, $H$ itself).
* **H3 (successful crossing).**  The CAPD `PoincareMap` invocation on
  that C1 set returns without exception, with crossing direction $D$,
  producing the image enclosure $I$, the flow-derivative enclosure
  $[D\varphi]$, and the return-time enclosure; and the anchor's own
  (thin) invocation returns $P(x)\in\widehat{P(x)}$ (an interval
  enclosure) without exception.
* **H4 (correction well-defined).**  `computeDP` returns without
  exception (in particular the transversality denominator
  $\nabla s\cdot f$ evaluated on $I$ excludes zero), giving
  $[DP]$.
* **H5 (section is a coordinate section)** with exact rational value
  $c$.
* **H6 (defect intersection over the full range).**  The optional
  sharpening intersects the candidate defect with
  $I-x_{\rm new}-T_{\rm new}\Delta$, where $\Delta$ is the full
  parameter deviation range.
* **H7 (fiber well-definedness).**  Every fiber's trajectory on the leg
  is collision-free and the leg's audit tube (independent C0
  propagation through the latest return, with per-step separation and
  brake-cover checks) passes.

**Claim.**  Define

\[
 x_{\rm new}=\operatorname{mid}\widehat{P(x)},\qquad
 T_{\rm new}=[DP]\,T,\qquad
 E_{\rm new}=\bigl(\widehat{P(x)}-x_{\rm new}\bigr)+[DP]\,E ,
\]

optionally sharpened by
$E_{\rm new}\leftarrow E_{\rm new}\cap\bigl(I-x_{\rm new}-T_{\rm new}
\Delta\bigr)$, and then impose exactly
$(x_{\rm new})_s=c$, $(T_{\rm new})_s=0$, $(E_{\rm new})_s=0$ and
$(x_{\rm new})_{ww}=u_c$, $(T_{\rm new})_{ww}=1$, $(E_{\rm new})_{ww}=0$.
Then

\[
 (\forall u)\qquad P(X(u))\in x_{\rm new}+T_{\rm new}\delta+E_{\rm new}.
\]

**Proof.**  Fix $u$ and put $h=X(u)-x\in T\delta+E$.  By H2/H3 the flow
of every point of $\operatorname{hull}(H,x)$ is defined up to its
crossing, each fiber crosses the section exactly once, transversally, in
direction $D$ within the crossing window (§4, items 1 and 6), so $P$ is
well-defined and $C^1$ on the section-relevant convex domain, and the
segment $\{x+\sigma h:\sigma\in[0,1]\}$ lies in that domain.  By the
componentwise mean value theorem, for each component $i$ there is
$\xi_i$ on the segment with
$P_i(X(u))=P_i(x)+\nabla P_i(\xi_i)\cdot h$.  By §4 item 1, the matrix
$[DP]$ encloses $\nabla P(\xi)$ row-wise for every point $\xi$ of the
segment (the flow-derivative enclosure is hulled over the entire
crossing window and over the whole initial domain, and the correction
factors are interval-evaluated on the image enclosure $I\ni P(\xi)$).
Hence

\[
 P(X(u))\in \widehat{P(x)}+[DP]h
 \subseteq \widehat{P(x)}+[DP]T\delta+[DP]E ,
\]

the last step by subdistributivity of interval arithmetic (item 2).
Writing $\widehat{P(x)}=x_{\rm new}+(\widehat{P(x)}-x_{\rm new})$ gives
the un-sharpened claim (item 5).  For the sharpening: for this same $u$,
$P(X(u))\in I$ and $\delta\in\Delta$, so the fiber defect
$e(u)=P(X(u))-x_{\rm new}-T_{\rm new}\delta$ lies in
$I-x_{\rm new}-T_{\rm new}\Delta$; it also lies in the candidate
$E_{\rm new}$; hence in the intersection (item 3).  For the exact rows:
$P(X(u))_s=c$ exactly for every fiber (each crossing lies exactly on the
coordinate section), so the section row of the fiber defect with the
imposed representation is $c-c-0\cdot\delta=0$; likewise
$P(X(u))_{ww}=u=u_c+1\cdot\delta$ exactly (the flow and all chart maps
fix $ww$), so the parameter row is exact (item 4).  Row-wise
containment in the remaining rows is unaffected by replacing rows of a
valid enclosure by exact values of the enclosed quantity.
$\blacksquare$

Status: **PROVED ANALYTICALLY**, conditional on the CAPD semantics
established by source inspection in §4 (each such item carries its own
status below).

## 3. Theorem PG2 (second-order graph step)

Extend the representation to

\[
 X(u)\in x+T\delta+Q\delta^2+E ,
\]

$Q$ an interval vector, with the same exact $s$- and $ww$-rows
($Q_s=Q_{ww}=0$).

**Additional hypotheses.**  H2$'$: a rigorous **C2** propagation
(`C2DoubletonSet` / `MpC2Rect2Set` through `PoincareMap` over
`MpIC2OdeSolver`) is initialized on the convex hull as in H2 and
returns, via `computeDP`, interval enclosures $[DP]$, $[D2P]$ of the
first-order derivative and of the **second-order Taylor coefficients**
of $P$ (CAPD convention: $P(x+h)\in P(x)+DP\,h+\sum_{i\le j}
D2P(\cdot,i,j)h_ih_j$, no additional $\tfrac12$); H3$'$: the thin anchor
run additionally returns a tight $\widehat{DP(x)}$ (the anchor's own C1
derivative).

**Claim.**  With $h(u)=T\delta+Q\delta^2+E$ and the bilinear-form
notation $[D2P][a,b]$ for the interval evaluation of
$\sum_{i\le j}D2P(\cdot,i,j)(a_ib_j+\mathbb 1_{i\ne j}a_jb_i)/\,$(the
symmetrized substitution of $a,b$ into the stored coefficients),
define

\[
 x_{\rm new}=\operatorname{mid}\widehat{P(x)},
\]
\[
 T_{\rm new}=\widehat{DP(x)}\,T+2\,[D2P][T,E],
\]
\[
 Q_{\rm new}=\widehat{DP(x)}\,Q+[D2P][T,T]+2\,[D2P][Q,E],
\]
\[
 E_{\rm new}=\bigl(\widehat{P(x)}-x_{\rm new}\bigr)
  +\widehat{DP(x)}\,E+[D2P][E,E]
  +2\,[D2P][T,Q]\,\Delta^3+[D2P][Q,Q]\,\Delta^4 ,
\]

where $\Delta^3,\Delta^4$ are the interval powers of the centered
deviation range, followed by the same optional intersection sharpening
(against $I-x_{\rm new}-T_{\rm new}\Delta-Q_{\rm new}\Delta^2$) and the
same exact-row imposition.  Then
$P(X(u))\in x_{\rm new}+T_{\rm new}\delta+Q_{\rm new}\delta^2
+E_{\rm new}$ for every $u$.

**Proof.**  Componentwise Taylor's theorem with Lagrange remainder in
Taylor-coefficient form: for each $i$ there is $\xi_i$ on the segment
$[x,X(u)]$ with

\[
 P_i(X(u))=P_i(x)+\nabla P_i(x)\cdot h
 +\textstyle\sum_{j\le k}\,c^{(i)}_{jk}(\xi_i)\,h_jh_k ,
\]

where $c^{(i)}_{jk}(\xi)$ are the second-order Taylor coefficients of
$P_i$ at $\xi$.  This requires $P\in C^2$ on the segment, supplied by
the C2 propagation succeeding on the convex hull (H2$'$; the crossing
and transversality guarantees are those of §4 with the C2 set, whose
`updateEnclosure` hulls the flow Hessian over the entire crossing window
— `poincare/SectionDerivativesEnclosure.h`, `updateEnclosure(C2Set&,
C2Set&)`, which forms
$\;\text{hull}\bigl(D\varphi_{\rm step}\!\cdot\!H_{\rm prev}
+H_{\rm step}\!\cdot\!(D\varphi_{\rm prev}),\dots\bigr)$, the chain rule
for second-order Taylor coefficients).  $\nabla P_i(x)$ is enclosed by
the thin anchor's $\widehat{DP(x)}$; $c^{(i)}_{jk}(\xi_i)$ by
$[D2P]$.  Substituting $h=T\delta+Q\delta^2+E$ and expanding the
bilinear form by subdistributivity:

\[
 [h,h]\subseteq[T,T]\delta^2+2[T,Q]\delta^3+2[T,E]\delta
 +[Q,Q]\delta^4+2[Q,E]\delta^2+[E,E],
\]

then grouping by powers of $\delta$ (with $\delta^3\in\Delta^3$,
$\delta^4\in\Delta^4$ hulled into the defect) yields exactly the
displayed $T_{\rm new},Q_{\rm new},E_{\rm new}$.  Sharpening and exact
rows as in PG1.  $\blacksquare$

Status: **PROVED ANALYTICALLY** (same conditionality).  The decisive
structural difference from PG1: the $\delta$-linear term propagates
through the **thin anchor derivative** $\widehat{DP(x)}$ instead of the
window-hulled $[DP]$, so the tangent no longer absorbs the
derivative-enclosure width; that width now multiplies only the
quadratic and defect terms.  The parameter-linear part of the hull then
grows like the true fiber spread, and the graph's excess is
$O(r^2)$ plus measured integration error — the scaling the task
specifies.

Chart switches at second order use the identical formulas with $P$
replaced by the algebraic chart map and
(`map/Map.h:207`) `Map::operator()(x, df, hessian)` supplying the
point derivative (at the thin anchor) and the interval Hessian
coefficients (over the hull); the map must be constructed with degree
$\ge2$.  Status: **PROVED ANALYTICALLY** (Taylor with Lagrange
remainder; smoothness on the hull certified by the interval evaluation
of the Hessian succeeding, since every sub-expression — including
square-root radicands and divisors — is then verified sign-definite on
the hull).

## 4. The ten audit items

Statuses use the project's official scale.

**1. Does CAPD enclose $DP$ over the complete convex initial domain and
the fiberwise return-time variation?  YES — PROVED BY COMPUTER-ASSISTED
ARGUMENT (source inspection).**
The flow-derivative enclosure handed to `computeDP` is accumulated in
`poincare/SectionDerivativesEnclosure.h`: `saveEnclosure(C1Set&)`
stores $D\varphi$ at the last time strictly before the section-touching
window, and `updateEnclosure(C1Set& prev, C1Set& next)` hulls it with
`next.getLastMatrixEnclosure()*MatrixType(prev)` — the one-step
variational **rough enclosure** (valid for *every intermediate time of
the step*) composed with the accumulated derivative — on every step of
the touching window, including the final overshoot step
(`poincare/PoincareMap_templateMembers.h`, `crossSection`, the
`updateEnclosure` calls before and after the loop and after the final
`m_solver.setStep(stepMade.rightBound())` step).  Hence
$[D\varphi]\supseteq\{D\varphi(\tau,q)\}$ for every $q$ in the initial
set and every $\tau$ in the crossing window — in particular at each
fiber's own return time.  The section correction
(`poincare/AbstractSection.hpp:47–64`, first-order `computeDP`)
interval-evaluates $DP_{ij}=f_i(Px)\,dT_j+D\varphi_{ij}$ with
$dT=-(\nabla s\cdot D\varphi)/(\nabla s\cdot f)$, all factors evaluated
on the *image enclosure* `Px` $=I$ (which, by the hull construction in
`crossSection` with its per-coordinate monotonicity refinement,
contains every fiber's crossing point), and division by a
zero-containing denominator throws.  The C0 image `result` itself is
accumulated fiberwise (positions where the vector field component is
sign-definite; whole step enclosures otherwise).  Requirement: the C1
set must be built on the full convex domain — this is hypothesis H2,
and it is *silently unsound to omit* (a C1 set built on a smaller set
does not bound derivatives at segment points outside it).

**2. Is $[DP](T\delta+E)\subseteq[DP]T\delta+[DP]E$ sound despite the
same unknown derivative appearing twice?  YES — PROVED ANALYTICALLY.**
Subdistributivity: for any interval matrix $M$ and interval vectors
$a,b$, $\{M'(a'+b'):M'\in M,a'\in a,b'\in b\}\subseteq Ma+Mb$, because
each selection $M'a'+M'b'$ is one choice in $Ma$ plus one in $Mb$.
Decorrelating the two occurrences of the derivative only *enlarges* the
right-hand side.  This is a tightness loss (bounded by
$\operatorname{width}([DP])\cdot(|T|\,r+|E|)$), never a containment
loss.

**3. Does intersecting the defect with $I-x_{\rm new}-T_{\rm new}\Delta$
preserve containment despite lost dependencies?  YES — PROVED
ANALYTICALLY**, *provided* the subtraction uses the full range
$\Delta$ (hypothesis H6).  Both the mean-value candidate and the
image-based expression are outer bounds on the same pointwise object
$e(u)$, so their intersection contains every $e(u)$; dependencies lost
in either bound only widen that bound.  **Caveat (the one way to get
this wrong):** subtracting $T_{\rm new}\delta$ for a *sub*-range of
$\Delta$, or reusing the intersected defect for parameters outside the
range used in the subtraction, is unsound.  With H6 as stated, sound.

**4. Is imposing the exact section coordinate on $x,T,E$ justified for
every fiber?  YES — PROVED ANALYTICALLY** for coordinate sections with
exact (representable/rational) value $c$: every fiber's return lies
exactly on $\{y_s=c\}$, so the section row of the fiber defect under
the imposed representation is identically zero; replacing rows of a
valid row-wise enclosure by exact values of the enclosed quantity
preserves containment.  The same argument justifies the exact parameter
row ($ww$): the flow fixes $ww$ ($\dot{ww}=0$ in every chart field) and
all three switch maps carry `ww -> ww` literally, so
$P(X(u))_{ww}=u$ exactly.  **This does not extend to `NonlinearSection`
or `AffineSection` with non-representable coefficients**; the audit
covers `CoordinateSection` only.

**5. Can an interval nominal anchor be replaced by its midpoint with
width transferred to $E$?  YES — PROVED ANALYTICALLY** (trivial:
$\widehat{P(x)}=x_{\rm new}+(\widehat{P(x)}-x_{\rm new})$ and the
second term is a centered interval absorbed in $E_{\rm new}$).  The
only side condition: subsequent mean-value steps must use a hull
containing the *new* anchor — guaranteed if the hull is always taken as
$\operatorname{hull}(x+T\Delta+E,\,x)$, which is automatic since
$0\in T\Delta+E$ ($E$ centered, $\Delta$ centered).

**6. Is the per-fiber return-time and tube-cover argument gap-free
across consecutive sections?  YES — PROVED ANALYTICALLY, given the
audits.**  Three ingredients, all verified in source: (i) *unique
transversal crossing per call*: `checkTransversability`
(`PoincareMap_templateMembers.h:396–418`) requires, on every accepted
step whose enclosure touches the section, that $\nabla s\cdot f$
excludes zero over the whole step enclosure; mixed-direction motion
near the section within a step therefore throws, and a
cross-and-return within one step is exactly what the check intercepts;
combined with the set-level sign bracketing in `crossSection` (the loop
ends only when the entire set is strictly across), every fiber crosses
exactly once per call, all in the same direction.  (ii) *leaving a
section*: `integrateUntilSectionCrossing` steps with per-step
transversality checks until the set's sign is strictly compatible with
the requested direction, so legs that begin on a section (the
MP$\to$PM turnaround at the same $w_r$ value) are handled, and
wrong-direction crossings skipped during this phase are themselves
transversality-guarded, keeping the crossing count set-uniform.
(iii) *tube cover*: the independent C0 audit tube runs from the
previous on-section graph through the latest return time; physical time
is strictly increasing along the regularized flow
($dt/d\sigma=|w|^2>0$, positivity checked per step), so the union of
step enclosures covers each fiber's arc from its previous crossing
through (beyond) its next crossing; the next leg's graph is built at
the crossing, so consecutive covers overlap.  No gap.

**7. Do the C0/C1 constructors contain the represented set after every
centering?  YES — PROVED BY COMPUTER-ASSISTED ARGUMENT (source
inspection).**  Constructors initialize the current set by interval
evaluation of the representation
(`dynset/C0TripletonSet.hpp:60–80`: `SetType(x+C*r0+B*r,...)`,
`SetType(x+C*r0+intersection(B*r,Q*q),...)`; the C1DoubletonSet
constructors are analogous), and interval evaluation is
inclusion-monotone, so any redistribution of the same set into
$(x,C,r_0,B,r)$ pieces that fiberwise sums to a superset is contained.
Centering inside `move` splits interval matrices into midpoint plus
spilled widths (`C0TripletonSet.hpp:128,153–155`).  The one trap
(found and fixed in this repository earlier today) is *reading* the
representation externally: the stored remainder is
$Br\cap Qq$, and using $Br$ alone after long propagation is
astronomically wide though still sound.

**8. Can chart transformations use the same defect update by a mean
value theorem?  YES — PROVED ANALYTICALLY** (this is Theorem PG1 with
$P$ an algebraic map; the derivative enclosure is
`Map::derivative` over the hull, the smoothness certificate is the
interval evaluation succeeding, and square-root branch violations
throw).  Second order likewise via `Map::operator()(x,df,hf)`
(`map/Map.h:207`).  For the tied family's three switches the exact
frame-change cores and both lift branches are additionally covered by
the exact regression tests `tests/test_middle_escape_endgame_maps.py`.

**9. Does any convexity assumption fail near close encounters or
square-root branches?  NO SILENT FAILURE — PROVED ANALYTICALLY, with a
tightness warning.**  Every mean-value/Taylor argument above needs
smoothness on the *convex hull*, which may contain phase-space points
the actual fibers avoid (near a collision set, near $g_x>0$ for a
Form-B lift, near the section-tangency locus).  In every such case the
computation on the hull either succeeds — which itself certifies
sign-definite radicands/divisors and hence smoothness on the hull — or
throws (CAPD sqrt/division on invalid intervals;
`checkTransversability`; the HOE step failure), so unsoundness cannot
enter silently.  The genuine cost is width: near an encounter the hull
inflates the derivative enclosures; the cure is representation width,
not a different lemma.

**10. May the terminal certificate be evaluated on the final graph hull
at a common physical-time section?  YES — PROVED ANALYTICALLY**: the
graph at an exact $t_p=T$ section contains every fiber's state at the
common collision-free time $T$, which is precisely the hypothesis set
of the (phase-robust) terminal theorem applied fiberwise at $t_0=T$.
**However this is the tightness-worst choice**: a fixed-time slice
maximizes inner-binary phase decorrelation (the observed hull spike to
$2.11$ at $t=4.0$; the same mechanism measured throughout this
program).  The escape theorem needs only *some* collision-free
$t_0(u)$ per fiber (Theorem C$'$ in
`docs/FABLE_MIDDLE_INTERVAL_NONPERIODICITY.md`), so the certificate may
equally be evaluated on the graph at the **final geometric section**
(per-fiber crossing times) or on any audited step enclosure — both
already proved sound in that record — avoiding the fixed-time spike
entirely.  Recommendation: never pay the fixed-time slice at the
terminal leg.

## 5. Tightness (non-soundness) caveats, ranked

1. First-order tangent updates multiply $T$ by the window-hulled
   $[DP]$; its width scales with the hull size and the crossing-window
   length, and this product is what produced the old graph's
   width-independent defect floor.  PG2 removes exactly this term.
2. Subdistributivity (item 2) costs
   $O(\operatorname{width}[DP]\cdot(|T|r+|E|))$ — dominated by 1.
3. The image-intersection sharpening (item 3) is most effective when
   $T_{\rm new}\Delta$ dominates $E$; with H6's full-range subtraction
   it cannot sharpen below the genuine fiber spread.
4. Fixed-time sections during or after the binary capture (item 10).
5. Encounter-adjacent hulls inflate $[DP]$/$[D2P]$; section placement
   away from pericenters (the benchmark's $w_r$ ladder) is the correct
   mitigation and matches the measured $\sim10^3$ section-synchronized
   sensitivity.

## 6. Counterexample search

I attempted to break the lemma at: (a) a fiber crossing the section
twice in one call — intercepted by `checkTransversability` (mixed
directions in one step enclosure) or by the set-level sign bracketing;
(b) segments leaving the C1 domain — excluded by H2, and demonstrably
dangerous without it (this is the one hypothesis whose violation is
silent; it must be stated); (c) defect intersection with a fiberwise
$\delta$ — unsound as written in some shorthand notations, sound with
H6; (d) non-coordinate sections with unrepresentable constants —
excluded by H5; (e) an anchor outside the hull after midpointing —
excluded by centeredness (item 5); (f) the frozen parameter drifting
under interval propagation — repaired exactly by the $ww$-row
imposition (item 4), which should be considered mandatory, not
optional, since without it the family degrades into a shadow family
with $u$-width noise.  No construction produced silent containment
loss.

## 7. Statuses (summary table)

| claim | status |
|---|---|
| PG1 (first-order step) | PROVED ANALYTICALLY (on H1–H7) |
| PG2 (second-order step) | PROVED ANALYTICALLY (on H1–H7, H2$'$, H3$'$) |
| CAPD crossing/derivative semantics (items 1, 6, 7) | PROVED BY COMPUTER-ASSISTED ARGUMENT (direct source inspection, citations above) |
| items 2, 3, 4, 5, 8, 9, 10 | PROVED ANALYTICALLY |
| old C1 anchor-box graph has a width-independent defect floor | VALIDATED NUMERICAL RESULT (this repository's v3 ladder: hull $\approx0.013$–$0.014$ at the $t=7/4$ switch for $du=10^{-7}$ and $10^{-8}$ alike) |
| PG2 restores $O(r^2)$ excess over true spread | CONJECTURAL until benchmarked (see handoff) |

The companion document `docs/FABLE_PARAMETER_GRAPH_HANDOFF.md` carries
the implementation, benchmark, and verdicts on scaling.
