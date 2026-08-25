# A nonperiodic real interval in the middle parameter range

Date: 2026-08-25 (revised after independent adversarial review)

Evidence status: **PROVED BY COMPUTER-ASSISTED ARGUMENT**

## Theorem

Let the normalized tied family of `CONJECTURE.md` have masses
$(m_1,m_2,m_3)=(A(u),B(u),1)$, $A=(1-u^2)/(1+u^2)$, $B=2u/(1+u^2)$, and
start from the exact tied right-triangle brake configuration.  For every
real parameter

\[
 \boxed{\;\frac{29000000000}{100000000000}\;\le\;u\;\le\;
 \frac{29000000010}{100000000000}\;}
 \qquad\left(\,0.29\le u\le 0.29+10^{-10}\,\right),
\]

the maximal classical solution admits **no second labelled brake at any
collision-free time**: the tied solution is nonperiodic.  Concretely, the
certificate proves that the solution is collision-free through a terminal
parameter-dependent time $t_\ast(u)\in[4.30147,4.30160]$, that every
collision-free time in $[0,t_\ast(u)]$ lies in a verified brake-exclusion
window, and that at $t_\ast(u)$ the terminal escape theorem applies with
certified margins

\[
 \inf d=1.8679,\quad \inf\dot\rho=2.0477,\quad \inf E_\rho=0.8225,\quad
 \sup h=-9.2745,\quad \inf(-\eta-h-\Delta)=5.0696\quad(\eta=4).
\]

The terminal conclusion is a dichotomy: either a later inner $\{2,3\}$
collision ends the classical solution, or that pair remains a bound binary
while body 1 escapes permanently.  Both branches exclude every later
classical labelled brake.

This is a uniform statement for a closed nonempty interval of real
parameters (a continuum), not a finite collection of point theorems.  It
is the program's first real-interval nonperiodicity result: the prior
committed interval theorem (`MIDDLE_FIRST_MAXIMUM_INTERVAL.md`) is a
finite-prefix statement, and the prior full nonperiodicity results are
single rational points.

In particular, the interval contains infinitely many rational Euclid
parameters and therefore proves the conjecture for infinitely many distinct
primitive Pythagorean triples.  Its left endpoint $u=29/100$ gives the
explicit primitive triple $(9159,5800,10841)$ in the displayed leg order.

## Proof structure

The certificate is `src/fable/verification/middle_escape_endgame_capd.cpp`
(mode `run_endgame_c0`), which combines four proved components:

1. **Event reduction** (`docs/FABLE_EVENT_REDUCTION.md`, Theorem C and its
   fiberwise-cover Corollary C1,
   `PROVED ANALYTICALLY`): a labelled brake at a collision-free time
   forces $\dot I=0$, $K=0$, and vanishing of the chart brake residual
   simultaneously, so per-window verification of
   $\dot I\neq0\ \lor\ K>0\ \lor\ U>U_0\ \lor\ (z,P)\not\ni0$
   excludes brakes on the window; a terminal escape certificate excludes
   all later brakes.  ($K=U-U_0$ on the tied shell, so the $U>U_0$ and
   $K>0$ disjuncts are two interval evaluations of the same margin.)

2. **Terminal escape theorem** (`docs/ESCAPE_CRITERIA.md`,
   `PROVED ANALYTICALLY`) in its pair-{2,3} chart form with the
   **phase-robust corollary** (`docs/FABLE_MIDDLE_ESCAPE.md` §2–§3a):
   only the transported pair energy $h$ and the outer variables $G,P$
   enter; no $w,z$ condition is required.

3. **Levi–Civita propagation** with the committed pair-{1,3} and
   pair-{2,3} regularized fields (copied verbatim from the committed
   `burrau_lc_certificate_capd.cpp`; their exactness is
   regression-tested in `tests/test_middle_escape_symbolic.py`: the LC
   field encodes Newton, $h'$ transports $h\equiv E_{23}$, $\ddot G$ and
   $J'$ carry the exact mass factors).  The parameter $u$ is a state
   variable inside a single `MpC0TripletonSet`, whose Lohner
   representation carries the parameter–state correlation step by step.

4. **Exact chart switches** at $t\approx1$, $7/4$, $7/2$
   (pair-13 → pair-23 Form A, back Form A, pair-13 → pair-23 Form B;
   maps regression-tested exactly in
   `tests/test_middle_escape_endgame_maps.py`), applied to the set by a
   rigorous mean-value image (below).

### The itinerary

The chart schedule is dictated by the deep-encounter inventory at
$u=0.29$ (all separations are ordinary values for orientation; the
certificate itself never uses them):

| encounter | pair | $r_{\min}$ | chart window |
|---|---|---:|---|
| $t=0.315$, $0.767$ | $\{1,3\}$ | $0.0057$, $0.0155$ | pair-13 $[0,1]$ |
| $t=1.047$, $1.596$ | $\{2,3\}$ | $0.0031$, $0.00044$ | pair-23 $[1,7/4]$ |
| $t=1.92$, $2.33$, $2.92$ | $\{1,3\}$ | $0.0125$, $0.0034$, $0.00073$ | pair-13 $[7/4,7/2]$ |
| $t=3.4515$ + $3.4695$ (exchange) | $\{2,3\}$+$\{1,3\}$ | $0.0285$, $0.0149$ | pair-13 (still) |
| binary pericenters $t\ge3.5165$ | $\{2,3\}$ | $\sim0.012$ | pair-23 $[7/2,\,t_\ast]$ |

### Soundness notes

* **Per-step covering.**  Every accepted solver step's enclosure is
  checked for positive mutual separations (the selected pair through its
  regularized radius $|w|^2$) and for the brake-exclusion disjunction;
  the launch window instead verifies $U<2U_0$, under which
  $\ddot I<0$ makes $J$ strictly decreasing from its exact zero at the
  $t=0$ brake, so no second brake can occur inside the window.  A leg
  that cannot be covered aborts the run (fail closed).  The union of the
  accepted-step enclosures contains, for each real $u$ in the tile, the
  complete orbit segment from launch through that fiber's time at the
  final step, so Corollary C1's fiberwise covering hypothesis holds.

* **Launch containment.**  The initial tripleton is the mean-value form of
  the exact algebraic launch map $L(u)$.  Its center is $L(u_c)$, its
  correlation column encloses $DL$ on the complete parameter interval, and
  its distinguished deviation is $u-u_c$.  Hence the ordinary mean-value
  theorem puts every exact tied launch state in the propagated set.  The
  launch-map reconstruction is regression-tested independently.

* **Mean-value set switch.**  For an algebraic chart map $F$ and the
  tripleton $S=x+Cr_0+(Br\cap Qq)$, the implementation takes $H$ to be the
  interval hull of $S$ explicitly extended by the stored center $x$.  Thus
  every $p\in S$ satisfies
  $F(p)\in F(x)+[DF](H)\,(p-x)$ componentwise by the mean value theorem
  on the segment $[x,p]\subset H$.  Since
  $p-x\in Cr_0+(Br\cap Qq)$, the image is contained in the new tripleton
  with $C'=\operatorname{mid}([DF](H)\,C)$, $r_0'=r_0$, and remainder
  $[DF](H)(Br\cap Qq)+(F(x)-\operatorname{mid}F(x))+
  ([DF](H)C-C')\,r_0$.  The intersection form of the stored remainder is
  essential ($B$ alone is ill-conditioned after thousands of steps).
  Square-root domain violations in $F$ raise interval exceptions, so an
  invalid branch choice fails closed.

* **Interval correlation matrices and retries.**  CAPD's tripleton move
  multiplies an interval correlation matrix by the validated flow Jacobian,
  then splits it to a midpoint matrix and spills the discarded widths into
  the remainder; the manual switch map mirrors this operation.  Before each
  attempted solver move the hardened driver copies the complete set and
  restores it after any exception, so a smaller-step retry never starts from
  a possibly partially mutated representation.

* **Fiberwise terminal time.**  The terminal certificate is evaluated on
  an accepted-step enclosure whose physical-time coordinate spans
  $[4.30147756370,4.30159216688]$.  Each real $u$ needs only *some* collision-free
  certificate time: its own state at its own time inside that step lies
  in the checked enclosure, and its covering extends through that step.
  No common terminal section is needed.

* **Step resolution of unselected pairs.**  The $\sigma$-step cap
  honors, besides the selected-pair scale $|w|/24$, the free-fall budget
  $r^{3/2}/40$ of the closest *unselected* pair (converted by
  $dt=|w|^2d\sigma$).  Without this, steps near an unselected
  conjunction produce enclosures of $1/r^3$ that are wide but
  exception-free, silently poisoning the set (observed: hull
  $10^{12}$).  A hull sanity guard ($>10$) additionally converts any
  such poisoning into a clean failure.

## Why the interval is narrow, quantitatively

Measured on this itinerary (all `ORDINARY NUMERICAL EVIDENCE` from the
failed wider runs, archived in the run report):

* selected-pair deep passages are cheap: the Levi–Civita $\sigma$-clock
  synchronizes the pericenter, and the $4.4\times10^{-4}$ passage costs
  only a factor $\sim3$ in hull width;
* the exchange scattering at $t\in[3.44,3.48]$ (both pairs
  simultaneously close) has a transient parameter sensitivity
  $\sim10^{6}$–$10^{8}$ at any fixed integration clock, and its
  second-order (curvature) wrapping requires the incoming hull to be
  below $\sim10^{-6}$; the tile widths that survive it end-to-end are
  $\lesssim10^{-10}$ in $u$ (a $3\times10^{-10}$ tile passed the
  exchange but died at the Form-B switch; both $10^{-11}$ and $10^{-10}$
  tiles passed end to end);
* the ordinary post-escape sensitivity is only $\sim2\times10^{4}$: the
  transient spike re-contracts dynamically, but monotone interval
  enclosures cannot re-contract, so the spike sets the tile width.
  Wider tiles per run therefore need the exchange leg to be crossed in a
  synchronized frame (the primary worker's reconditioning program):
  measured section-synchronized sensitivities stay $\sim10^{3}$ across
  all passages.

Scaling the certified width up by uniform tiling costs one run
($\sim$7 minutes at 80-bit precision) per $10^{-11}$; the archived
campaign extends the interval by contiguous tiles.

## Reproduction

```sh
sh scripts/fable_run_capd_middle_endgame.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-mp \
  29000000000 100000000000 29000000010 100000000000 80 1e-14 24
# expect: ENDGAME_PARAMS ... driver=middle_escape_endgame_capd/v5-hardened-2026-08-25
#         PASS_MIDDLE_ESCAPE_ENDGAME ... inf_margin=5.069...
```

Cross-check of the printed `TERMINAL_BOX` with the independent checker
(outward-round the 17-digit bounds to 15 digits first):

```sh
sh scripts/fable_run_capd_middle_escape.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-native --phase-robust < box.txt
# PASS_MIDDLE_ESCAPE_TERMINAL_PHASE_ROBUST ... (margin 5.0693)
```

Exact-map and exact-formula regressions:

```sh
python -m pytest tests/test_middle_escape_symbolic.py \
  tests/test_middle_escape_endgame_maps.py -q      # 22 exact tests
```

Archived log: `data/fable/middle_escape_endgame_1e10_interval.log`
(source-branch commit `bd3207a`).  Dependency pin: CAPD 6.1.0, commit
`731079217a9254ea2948d742df2b170895effe7f`, MPFR build.

## Independent review and repairs

An independent adversarial review found no invalidating dynamical or
analytic error, but identified four proof-interface points that required an
explicit statement or implementation hardening:

1. the driver uses fiber-dependent solver windows, the special concave
   launch window, and an LC velocity residual; Corollary C1 now states and
   proves exactly those criteria;
2. the switch derivative box is explicitly extended by the stored center,
   rather than assuming CAPD's ordinary enclosure already contains it;
3. every failed solver move now restores a pre-move copy before retrying;
4. the terminal claim is the proved escape-or-inner-collision dichotomy, not
   unconditional collision-free escape.

The complete $10^{-10}$ interval was replayed after these repairs.  All 3537
validated steps, phase enclosures, terminal bounds, and the final margin
$5.06969485075\ldots$ were unchanged.

## Scope

This theorem does not resolve the conjecture on the full middle tile
$[0.29,0.29002]$; it closes a nonempty real subinterval and supplies a
reusable, measured pipeline (architecture, step caps, switch maps,
terminal edge) for widening.  The quantified exchange obstruction and
the section-synchronization data identify exactly what the primary
worker's reconditioning must supply for the full tile.
