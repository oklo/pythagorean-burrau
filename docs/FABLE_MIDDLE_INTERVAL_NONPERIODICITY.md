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
 \frac{29000001010}{100000000000}\;}
 \qquad\left(\,0.29\le u\le 0.29+1.01\times10^{-8}\,\right),
\]

the maximal classical solution admits **no second labelled brake at any
collision-free time**: the tied solution is nonperiodic.  The theorem is the
gap-free union of independently certified closed parameter tiles.  On the
initial width-$10^{-9}$ subinterval, one synchronized correlated-set
certificate proves that the solution is collision-free through a terminal
parameter-dependent time $t_\ast(u)\in[4.30030,4.30033]$, that every
collision-free time in $[0,t_\ast(u)]$ lies in a verified brake-exclusion
window, and that at $t_\ast(u)$ the terminal escape theorem applies with
certified margins

\[
 \inf d=1.8655,\quad \inf\dot\rho=2.0484,\quad \inf E_\rho=0.8223,\quad
 \sup h=-9.2745,\quad \inf(-\eta-h-\Delta)=5.0690\quad(\eta=4).
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

4. **Correlated Poincare synchronization** across the exchange, on the six
   pair-{1,3} sections
   $w_r=-3/5,-1/2,-2/5,-3/10,-1/5,0$.  Each return map carries the
   distinguished parameter generator through a rigorous $C^1$ mean-value
   image, while a separate $C^0$ integration covers the complete tube up to
   the latest return and verifies separation and brake exclusion there.

5. **Exact chart switches** at $t\approx1$, $7/4$, $7/2$
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

* **Mean-value Poincare image.**  Before each exchange section, the
  tripleton remainder is enclosed by its coordinatewise intersection box
  and extended to contain zero, producing a convex set that contains both
  the propagated family and its stored center.  CAPD proves a common
  transverse return branch and encloses its flow derivative; the standard
  section correction gives $[DP]$ on that complete convex set.  The ordinary
  mean-value theorem then encloses
  $P(x+Cr_0+e)$ by
  $P(x)+[DP]Cr_0+[DP]e$.  Midpoint splitting retains $r_0$ as the exact
  distinguished parameter coordinate, and the remainder is intersected
  with CAPD's independent enclosure of the complete section image.  The
  section-normal coordinate is set to its exact section value.  Resetting
  CAPD's solver-clock coordinate to zero after a section is harmless because
  the regularized vector fields are autonomous; physical time is a separate
  state coordinate and is not reset.

* **Inter-section tube covering.**  A section image alone does not cover the
  trajectory before it.  For every Poincare leg, a separate copy of the
  incoming C0 set is integrated beyond the upper endpoint of the validated
  return-time interval.  Every accepted full-step enclosure is checked for
  all collision separations and the Corollary C1 brake disjunction.  Only
  after this audit succeeds is the synchronized section image accepted.

* **Interval correlation matrices and retries.**  CAPD's tripleton move
  multiplies an interval correlation matrix by the validated flow Jacobian,
  then splits it to a midpoint matrix and spills the discarded widths into
  the remainder; the manual switch map mirrors this operation.  Before each
  attempted solver move the hardened driver copies the complete set and
  restores it after any exception, so a smaller-step retry never starts from
  a possibly partially mutated representation.

* **Fiberwise terminal time.**  The terminal certificate is evaluated on
  an accepted-step enclosure whose physical-time coordinate spans
  $[4.30030837364,4.30032429905]$.  Each real $u$ needs only *some* collision-free
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

## Quantitative effect of synchronization

The sensitivity estimates below are `ORDINARY NUMERICAL EVIDENCE`; the
reported interval pass/fail points are validated CAPD outcomes:

* selected-pair deep passages are cheap: the Levi–Civita $\sigma$-clock
  synchronizes the pericenter, and the $4.4\times10^{-4}$ passage costs
  only a factor $\sim3$ in hull width;
* the exchange scattering at $t\in[3.44,3.48]$ (both pairs
  simultaneously close) has a transient parameter sensitivity
  $\sim10^{6}$–$10^{8}$ at any fixed integration clock.  The old
  common-clock driver passed end to end at width $10^{-10}$ but was already
  near its wrapping limit;
* the ordinary post-escape sensitivity is only $\sim2\times10^{4}$: the
  transient spike re-contracts dynamically, but monotone interval
  enclosures cannot re-contract, so the spike sets the tile width;
* the six validated Poincare synchronizations reduce the maximum hull on the
  proved $10^{-10}$ tile by a factor about 46, and permit the present
  $10^{-9}$ tile to pass with maximum hull $4.64\times10^{-4}$;
* a width-$10^{-8}$ stress test passed all six sections but reached hull
  $0.315$ at the Form-B chart switch and then failed the driver's hull guard
  at $t\approx3.65237$.  This is a representation failure, not evidence of
  a physical collision or brake.  It localizes the next improvement to the
  post-exchange chart-switch/escape representation.

The proved width is therefore ten times the independently reviewed base
tile, while the same synchronized mechanism has rigorously crossed the
exchange on a tile one hundred times wider.

## Reproduction

```sh
FABLE_ENDGAME_SYNC=1 \
  sh scripts/fable_run_capd_middle_endgame.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-mp \
  29000000000 100000000000 29000000100 100000000000 80 1e-14 24
# expect:
# ENDGAME_PARAMS ... sync_exchange=1 driver=middle_escape_endgame_capd/v6-sync-2026-08-25
#         PASS_MIDDLE_ESCAPE_ENDGAME ... inf_margin=5.069...
```

Cross-check of the printed `TERMINAL_BOX` with the independent checker
(outward-round the 17-digit bounds to 15 digits first):

```sh
sh scripts/fable_run_capd_middle_escape.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-native --phase-robust < box.txt
# PASS_MIDDLE_ESCAPE_TERMINAL_PHASE_ROBUST ... (margin 5.06905)
```

Exact-map and exact-formula regressions:

```sh
python -m pytest tests/test_middle_escape_symbolic.py \
  tests/test_middle_escape_endgame_maps.py \
  tests/test_escape_certificate.py -q              # 25 tests
```

Archived synchronized log:
`data/fable/middle_escape_endgame_1e9_sync_interval.log`; the independent
96-bit, tolerance-$10^{-16}$, order-26 refinement is archived as
`data/fable/middle_escape_endgame_1e9_sync_interval_96bit.log`.  The
reviewed base log remains
`data/fable/middle_escape_endgame_1e10_interval.log`.  Dependency pin:
CAPD 6.1.0, commit
`731079217a9254ea2948d742df2b170895effe7f`, MPFR build.

## Widened statement (tiling campaign)

A campaign of 100 adjacent tiles of width $10^{-10}$, each certified by
an independent run of the same driver at the same parameters
(100/100 PASS, no failures, no subdivisions), extends the boxed theorem
contiguously:

\[
 \textbf{every real}\quad
 \frac{29}{100}\;\le\;u\;\le\;\frac{2900000101}{10^{10}}
 \qquad\left(\,0.29\le u\le 0.29+1.01\times10^{-8}\,\right)
\]

is nonperiodic.  The base tile and the campaign tiles share exact
rational endpoints, so the union is a closed interval with no gaps.
Per-tile PASS lines (with their exact rational intervals) are collected
in `data/fable/middle_escape_endgame_campaign_1e8.log`; the complete
per-tile logs are archived in
`data/fable/middle_escape_endgame_campaign_1e8_logs.tar.gz`.  Terminal
margins vary slightly per tile; each tile's log records its own
certified bounds.  (The campaign tiles ran the pre-hardening driver
build.  The subsequent hull-extension and copy-restore changes are
conservative-only hardening.  Their absence leaves two CAPD-internal
assumptions, both subsequently checked directly against the pinned CAPD
source; the hardened base tile was also replayed bit-identically.)

The synchronized one-set theorem independently covers
$[0.29,0.29+10^{-9}]$ and therefore overlaps the first nine campaign tiles.
The exact endpoint audit gives 100 requested/PASS interval matches, 100
width-$10^{-10}$ tiles, and 99 exact internal endpoint matches.  The campaign
artifact commit is `6a169f24289973a89274d5b51cc82844cd044a12`.
Reproduce the exact chain/archive audit with

```sh
python scripts/audit_fable_middle_campaign.py
# PASS_FABLE_MIDDLE_CAMPAIGN_AUDIT tiles=100 ...
```

The committed summary and archive SHA-256 digests are, respectively,
`57a28304c505e1fd30cf3fb1afbcbe811b6df69974266d00a17a0d358672fb4d` and
`61317af93e44ebe48825599f8cf6523dc13246190907b8b91fb1e2f22dee6b27`.

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
The synchronized extension preserves those repairs and adds the explicit
convex-domain and full-tube checks above.
The complete width-$10^{-9}$ interval was then replayed with 96-bit MPFR
precision, tolerance $10^{-16}$, and Taylor order 26.  It again passed all
3344 main-flow steps and six tube audits, with maximum hull
$0.0004635487114$ and terminal margin $5.06905197648$; the 80-bit run gives
$0.0004635487135$ and $5.06905197647$, respectively.

## Scope

This theorem does not resolve the conjecture on the full middle tile
$[0.29,0.29002]$; it closes a width-$1.01\times10^{-8}$ real subinterval and
supplies a
reusable, measured pipeline (architecture, step caps, switch maps,
terminal edge) for widening.  The exchange bottleneck is now crossed by a
rigorous correlated return map; the next localized engineering target is a
sharper pre-switch/Form-B image that prevents the final escape-chart hull
growth on wider single-set tiles.
