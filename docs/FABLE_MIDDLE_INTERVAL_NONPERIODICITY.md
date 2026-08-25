# A nonperiodic real interval in the middle parameter range

Date: 2026-08-25 (revised the same day after independent adversarial
review; see §"Review and repairs").

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
certificate proves that the solution is collision-free through a
parameter-dependent terminal time $t_\ast(u)\in[4.3014,4.3016]$, that
every collision-free time in $[0,t_\ast(u)]$ lies in a verified
brake-exclusion window, and that the state at $t_\ast(u)$ satisfies the
strict terminal escape inequalities with certified outward-rounded
margins

\[
 \inf d\ge1.8679,\quad \inf\dot\rho\ge2.0477,\quad
 \inf E_\rho\ge0.8225,\quad \sup h\le-9.2745,\quad
 \inf(-\eta-h-\Delta)\ge5.0696\quad(\eta=4).
\]

The terminal conclusion is the dichotomy of `ESCAPE_CRITERIA.md`: for
each such $u$, either a later inner $\{2,3\}$ collision ends the
classical solution, or bodies $\{2,3\}$ remain a bound binary and body 1
escapes to infinity; **both branches exclude every later labelled
brake**, which is all the theorem uses.

This is a uniform statement for a closed nonempty interval of real
parameters (a continuum), not a finite collection of point theorems.  It
is the program's first real-interval nonperiodicity result: the prior
committed interval theorem (`MIDDLE_FIRST_MAXIMUM_INTERVAL.md`) is a
finite-prefix statement, and the prior full nonperiodicity results are
single rational points.  Narrower tiles $[0.29,0.29+10^{-11}]$,
$[0.29,0.29+3\times10^{-11}]$, and $[0.29,0.29+10^{-12}]$ were certified
by identical runs (archived separately) and are subsumed by the boxed
statement.

## Proof structure

The certificate is `src/fable/verification/middle_escape_endgame_capd.cpp`
(mode `run_endgame_c0`), which combines four proved components:

1. **Event reduction** (`docs/FABLE_EVENT_REDUCTION.md`, Theorem C,
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

### Covering criteria actually used (Theorem C$'$)

Theorem C of `docs/FABLE_EVENT_REDUCTION.md` is stated with a single
partition, a common terminal time, and the window alternatives
$\dot I\neq0$ / $K>0$ / $|\mathcal B|>0$.  The certificate instantiates
the following fiberwise variant, whose proof is a direct extension.

**Theorem C$'$.**  *Fix $\mathcal U\subset(0,\sqrt2-1]$.  Suppose that
for every $u\in\mathcal U$ there is a finite partition
$0=t_0(u)<\dots<t_{N}(u)$ of $[0,t_N(u)]$ such that on each window at
least one of the following is verified:*

1. $\dot I\neq0$ *throughout;*
2. $K>0$ *throughout;*
3. $U>U_0$ *throughout;*
4. *some component of the chart velocities $(z,P)$ excludes zero
   throughout, on a window where the selected-pair radius $|w|^2$ and
   both unselected separations are verified positive;*
5. *(launch window only) the window has left endpoint $t=0$, the exact
   launch state is the tied brake with $\dot I(0)=0$ exactly, and
   $U<2U_0$ throughout the window;*

*and that at $t_N(u)$ the strict hypotheses of the terminal
binary--escaper certificate hold.  Then no $u\in\mathcal U$ admits a
second labelled brake at any collision-free time.*

*Proof.*  Fix $u$ and suppose a labelled brake occurs at a
collision-free $\tau>0$.  If $\tau>t_N(u)$, the terminal certificate's
dichotomy excludes it (`ESCAPE_CRITERIA.md`).  Otherwise $\tau$ lies in
some window.  A brake forces, simultaneously, $\dot I=0$, $K=0$
(equivalently $U=U_0$ on the tied shell, so criteria 2 and 3 are two
interval evaluations of the same margin), and — at a state with
$|w|^2>0$, where $\dot g=2wz/|w|^2$ and $\dot G=P$ reconstruct the
physical velocities — $z=0$ and $P=0$.  Criteria 1–4 each contradict one
of these necessary conditions (only the trivial direction of the
splitting is used, so no chart hypothesis beyond $|w|^2>0$ is needed for
4).  For criterion 5: by the Lagrange–Jacobi identity (Lemma 2 of the
event reduction), $U<2U_0$ gives $\ddot I<0$ throughout the window, so
$\dot I$ is strictly decreasing; since $\dot I(0)=0$ exactly at the
launch brake, $\dot I<0$ on the open window, and no further zero of
$\dot I$ — hence no brake — exists there.  The per-$u$ partitions and
terminal times are immaterial: the argument is pointwise in $u$.
$\blacksquare$

In the code, criterion 5 is the `initial_phase` check, criteria 1–4 are
the per-step disjunction, and the per-$u$ partition is furnished by the
accepted solver steps: on each step the enclosure contains the fiber's
arc, physical time is strictly increasing along the regularized flow
($dt/d\sigma=|w|^2$, with $|w|^2>0$ verified on every step enclosure),
so the step enclosures cut each fiber's time axis into consecutive
windows covering $[0,t_N(u)]$, where $t_N(u)$ is the fiber's time at the
terminal step.

### Soundness notes

* **Per-step covering.**  Every accepted solver step's enclosure is
  checked for positive mutual separations (the selected pair through its
  regularized radius $|w|^2$) and for one of the criteria of Theorem
  C$'$ above.  A step that cannot be covered aborts the run (fail
  closed).  Chart switches leave no gap: the switch is an instantaneous
  algebraic map applied at a common $\sigma$-instant, the physical time
  coordinate passes through unchanged, and the switch-instant state lies
  in both the last audited enclosure of the old chart and the first
  audited enclosure of the new one.

* **The launch set contains every fiber.**  The initial tripleton is the
  mean-value form of the exact algebraic launch map $L$: center
  $L(u_c)$, correlation column the interval derivative $[DL](\mathcal U)$,
  deviation $\mathcal U-u_c$.  By the mean value theorem,
  $L(u)\in L(u_c)+[DL](\mathcal U)(u-u_c)$ for every
  $u\in\mathcal U$, so the set contains every fiber's exact tied launch
  state (with $z=P=\dot I=0$ exactly).  The exactness of the launch map
  itself (tied $(X,Y)$ reconstruction, $h=-(A+1)/B$, $J=0$) is vouched
  for by the committed pipeline's independent adversarial audit
  (`MIDDLE_FIRST_MAXIMUM_ADVERSARIAL_AUDIT.md`); the 22 symbolic tests
  of this run cover the LC fields, transport identities, and switch
  maps, not the launch map.

* **Interval correlation matrices are sound in CAPD.**  The launch set
  (and the switch output before its first step) carries an interval
  correlation matrix $C$.  CAPD's tripleton `move` handles this
  soundly by construction: it forms `jacPhi*C` as an interval product
  and then renormalizes $C$ to its midpoint, spilling the discarded
  widths times $r_0$ into the remainder
  (`capd/dynset/C0TripletonSet.hpp`, the `result.m_C = data.jacPhi *
  set.m_C` and `split(result.m_C, data.deltaC)` lines).  The
  midpoint-plus-spill performed manually at chart switches mirrors this
  internal convention.

* **Mean-value set switch.**  For an algebraic chart map $F$ and the
  tripleton $S=x+Cr_0+(Br\cap Qq)$, let $H$ be the interval hull of
  $S$ *extended by the stored center $x$* (taken explicitly in the code,
  so the requirement $[x,p]\subset H$ holds by construction rather than
  by an assumption about CAPD's re-centering).  Every $p\in S$ satisfies
  $F(p)\in F(x)+[DF](H)\,(p-x)$ componentwise by the mean value theorem
  on the segment $[x,p]\subset H$.  Since
  $p-x\in Cr_0+(Br\cap Qq)$, the image is contained in the new tripleton
  with $C'=\operatorname{mid}([DF](H)\,C)$, $r_0'=r_0$, and remainder
  $[DF](H)(Br\cap Qq)+(F(x)-\operatorname{mid}F(x))+
  ([DF](H)C-C')\,r_0$.  The intersection form of the stored remainder is
  essential ($B$ alone is ill-conditioned after thousands of steps).
  Square-root domain violations in $F$ raise interval exceptions, so an
  invalid branch choice fails closed.

* **Exception-safe stepping.**  CAPD's `move` computes the step
  enclosure before mutating the set (the common High-Order-Enclosure and
  division throws leave it intact); the driver additionally copies the
  set before each attempted step and restores it on any exception, so
  retries never act on a possibly part-written representation (this also
  covers CAPD's internal empty-intersection `logic_error` path, which
  writes representation members before throwing).

* **Fiberwise terminal time.**  The terminal certificate is evaluated on
  an accepted-step enclosure whose physical-time coordinate spans
  $[4.30022,4.30024]$.  Each real $u$ needs only *some* collision-free
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
  exchange but died at the Form-B switch; $10^{-11}$ passed everything
  with two orders to spare);
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
# expect: ENDGAME_PARAMS precision_bits=80 tolerance=1e-14 order=24 ...
#         PASS_MIDDLE_ESCAPE_ENDGAME ... inf_margin=5.0696...
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

Archived log: `data/fable/middle_escape_endgame_first_interval.log`
(commit `52d0f93`).  Dependency pin: CAPD 6.1.0, commit
`731079217a9254ea2948d742df2b170895effe7f`, MPFR build.

## Review and repairs

An independent adversarial review (fresh agent, no involvement in the
construction) was commissioned on 2026-08-25.  It found **no
invalidating error** — the covering logic, switch algebra, terminal
corollary, and fiberwise bookkeeping survived — and identified the
following, all repaired the same day:

1. the covering criteria actually checked were a variant of Theorem C
   that had not been stated; Theorem C$'$ above now states and proves
   it (launch window, velocity-residual disjunct, per-parameter
   partitions and terminal times);
2. an apparent contradiction between the driver's "point matrices
   required" comment and the interval correlation matrix of the launch
   set; resolved by inspection of CAPD's tripleton `move` (interval $C$
   is handled soundly by midpoint-split-and-spill; the comment was a
   wrong diagnosis and has been corrected), plus the launch-set
   mean-value lemma above;
3. the mean-value hull did not provably contain the stored center;
   hardened by explicitly extending $H$ by $x$;
4. retry-in-place after a thrown step; hardened by copy-and-restore;
5. claim hygiene: the boxed theorem now matches the widest certified
   run, margins are outward-rounded from the archived log, the terminal
   time interval is corrected to $[4.3014,4.3016]$, and the escape
   conclusion is stated as the dichotomy.

The certificate for the boxed interval was re-run with the hardened
driver after repairs 3–4; the archived log is the hardened run, whose
`ENDGAME_PARAMS` line records precision, tolerance, order, and driver
version.

## Scope

This theorem does not resolve the conjecture on the full middle tile
$[0.29,0.29002]$; it closes a nonempty real subinterval and supplies a
reusable, measured pipeline (architecture, step caps, switch maps,
terminal edge) for widening.  The quantified exchange obstruction and
the section-synchronization data identify exactly what the primary
worker's reconditioning must supply for the full tile.
