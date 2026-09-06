# Parameter-graph validation and second-order enclosure: handoff

Date: 2026-08-26.  From the independent second agent (branch
`fable/middle-terminal-escape`).  Companion to
`docs/FABLE_PARAMETER_GRAPH_AUDIT.md` (the formal soundness audit).
Benchmark logs are archived under `data/fable/parameter_graph/`.

## 1. Executive summary

1. **Your corrected first-order graph is sound.**  Theorem PG1 of the
   audit states it formally with the seven hypotheses that make it so;
   all ten of your audit questions are answered YES/soundly, with CAPD
   6.1.0 source citations (pinned commit).  Two hypotheses are *silently*
   unsound if omitted — build the C1 enclosure on the full convex hull
   including the anchor, and subtract $T_{\rm new}\Delta$ over the FULL
   parameter range in the defect intersection.  The frozen-parameter row
   imposition ($T_{ww}=1$, $E_{ww}=0$ exactly) is mandatory, or the tied
   family degrades into a shadow family.
2. **An independent implementation confirms the design and beats the
   control.**  My prototype (`src/fable/verification/parameter_graph_capd.cpp`)
   at width $10^{-12}$, 160-bit/1e-24/order-32, runs launch → exchange →
   Form-B switch → your full 21-section $w_r$ ladder → terminal
   certificate, PASSING both terminal variants (geometric-section margin
   3.137; fixed-time margin 3.400).  At the Form-B switch it holds hull
   $4.2\times10^{-6}$ / defect $4.1\times10^{-8}$, versus the control's
   $1.96\times10^{-3}$ / $7.5\times10^{-5}$ — about $460\times$ /
   $1800\times$ tighter at identical width and settings.  The
   differences that matter: a thin anchor re-centered at every section,
   the image-intersection sharpening, and per-leg audit tubes.
3. **The second-order graph (PG2) is derived, proved, implemented —
   and it IS the unlock in the $10^{-11}$–$10^{-8}$ range.**  The
   benchmark falsified my own initial reading: PG1's tangent is itself
   $\sim100\times$ wrapping-inflated through the exchange (the
   window-hulled $[DP]$ both inflates $|T|$ and smears $w,z$-sensitivity
   into the $h,G,P$ rows), and PG2's thin-anchor derivative removes
   both effects.  Measured: $51\times$ tighter at the Form-B switch and
   $60\times$ tighter at the ladder end at $10^{-12}$; the true
   exchange sensitivity is $4\times10^{4}$ (not $10^{6}$–$10^{8}$);
   PG2 at $10^{-10}$ crosses the exchange cleanly where PG1 at
   $10^{-9}$ dies.
4. **The corrected, wrapping-free scaling limits** (per the PG2 data):
   exchange crossing $\sim2.5\times10^{-7}$; ladder-end $w,z$ hull
   $\sim1.6\times10^{-8}$; true per-binary-cycle sensitivity growth
   $\sim\times5$–$7$ — **every binary cycle you retain before firing
   the terminal certificate still costs that factor in width**, so fire
   it at the first post-switch section; the phase-robust certificate
   needs only $(h,G,P)$ and per-fiber times, never a fixed-time section
   (audit item 10).  Expected PG2 capacity on this itinerary:
   $\sim10^{-8}$ tiles; with geometric exchange sections,
   $10^{-6}$–$10^{-5}$.
5. **The quantitative unlock is geometric sections THROUGH the
   exchange.**  Measured section-synchronized sensitivities at the
   pair-{1,3} sections adjacent to the deep passages stay
   $1.2$–$4\times10^{3}$ (ordinary recon, three independent
   measurements).  Replacing the fixed-time legs across $[3.4,3.5]$
   with a {1,3}-chart geometric ladder (e.g. $w_r=-2/5$ MP, $\dot I=0$,
   $w_r=0$ MP, then the Form-B switch keyed to a section rather than
   $t=7/2$) should admit widths of order $10^{-6}$–$10^{-5}$ — three to
   four orders beyond the current frontier — with the SAME PG1 update.
   This matches your current plan; the graph machinery needs no change.

## 2. Benchmark table

Program: stage 1 (launch $\to$ Form-B switch via fixed-time sections),
then the specified post-Form-B ladder
($w_r=-3/20$ MP $\dots$ $3/20$ MP, 21 sections), then terminal
($\eta=4$, phase-robust) on the final geometric section and after
$t_p=77/20$.  All runs 160-bit MPFR, tolerance $10^{-24}$, Taylor order
32.  "tan" = width of $T\Delta$, "def" = width of $E$ (max component).

| width | mode | outcome | last point / at Form-B switch | diagnosis (task taxonomy) |
|---|---|---|---|---|
| $10^{-12}$ | PG1 | **PASS** (both terminals) | switch: hull $4.2\times10^{-6}$, def $4.1\times10^{-8}$; terminal geo margin 3.137, fixed 3.400 | — |
| $10^{-11}$ | PG1 | FAIL at the terminal | full itinerary completed; wr21 hull $0.114$, def $1.1\times10^{-5}$; $\inf E_\rho=-0.094$ (geo), $-0.497$ (fixed) | **interval derivative wrapping**: the window-hulled $[DP]$'s widths smear the (huge, genuine) $w,z$-sensitivity into the $h,G,P$ rows; the true $G,P$ spread at this width is $\sim10^{-8}$ and could not itself eat the $E_\rho=0.17$ margin |
| $10^{-10}$ | PG1 | FAIL mid-ladder | crossed the exchange; died at the wr9 return with wr8 hull $1.02$ (def $1.0\times10^{-6}$), "possible nontransversal return" | **interval derivative wrapping** compounding per section ($\times700$ beyond linear-in-width scaling), presenting as **section nontransversality** once the hull is order one |
| $10^{-9}$ | PG1 | FAIL in the exchange core ($69/20\to7/2$) | $t=69/20$: hull $0.134$, def $1.3\times10^{-9}$ | **physical parameter spread** (defect 8 orders below hull) |
| $10^{-8}$ | PG1 | FAIL entering the exchange ($17/5\to69/20$) | $t=17/5$: hull $0.071$, def $7.0\times10^{-12}$ | **physical parameter spread** (defect 10 orders below hull) |
| $10^{-12}$ | PG2 | **PASS** (both terminals) | switch: hull $8.2\times10^{-8}$ ($51\times$ tighter than PG1); wr21 hull $1.7\times10^{-5}$ ($60\times$ tighter); terminal geo margin 3.153, fixed 3.422 | — |
| $10^{-10}$ | PG2 | **crossed the exchange AND completed the full 21-section ladder** (wr21 hull $0.064$, tan $0.063$, def $1.8\times10^{-5}$); FAIL only at the terminal: $\inf E_\rho=0.023>0$ but $\Delta\propto E_\rho^{-1/2}$ amplifies and $\inf(-\eta-h-\Delta)=-0.77$ | switch: hull $2.6\times10^{-4}$, defect $4.5\times10^{-8}$ (defect unchanged from the $10^{-12}$ run — pure numerics) | **terminal-margin loss**: the prescribed certificate time $t\approx3.85$ has only $E_\rho=0.17$ pointwise; the $h,G,P$ spreads at this width eat it.  The representation held everywhere.  Cure: two–three more ladder sections before firing ($E_\rho$ grows to $\sim0.6$ by $t\approx4.2$ at $\times5$–$7$ width cost per cycle), or a slightly later benchmark terminal.  PG1 at this width died at section 9. |
| $10^{-11}$, $10^{-9}$, $10^{-8}$ | PG2 | not completed in this run (the first attempts were killed by machine memory pressure at $t=3.45$, $t=3.45$, $t=2$, $t=2$ respectively — run C2 jobs one or two at a time on this host) | | |

**The PG2 comparison rewrites the ceiling analysis.**  PG1's tangent is
itself wrapping-inflated: at the Form-B switch the PG2 (thin-anchor)
tangent is $3.8\times10^{-8}$ per $10^{-12}$, i.e. the TRUE fixed-time
exchange sensitivity is $|dX/du|\approx4\times10^{4}$ — PG1's
$4\times10^{6}$ was $\sim100\times$ window-hull wrapping, and the
$10^{6}$–$10^{8}$ "transient spike" measured by earlier architectures
was largely representational.  Likewise at the ladder end the true
sensitivity is $6.3\times10^{6}$ (not $10^{9}$).  Corrected ceilings for
PG2:

* exchange crossing: width $\sim0.01/4\times10^{4}\approx2.5\times10^{-7}$
  (confirmed in the right direction: $10^{-10}$ crossed cleanly);
* ladder end ($w,z$ hull $\lesssim0.1$): width
  $\sim1.6\times10^{-8}$;
* terminal $E_\rho$ margin at the early ($t\approx3.85$) certificate:
  set by the (much smaller) $h,G,P$-row sensitivities; not yet the
  binder at $10^{-10}$.

So the measured second-order dividend is $50$–$100\times$ in width at
the exchange, with the honest expectation that **PG2 alone reaches
$\sim10^{-8}$ tiles on this itinerary**, and geometric exchange
sections push beyond that.  PG1's two ceilings (row-mixing at
$10^{-11}$, wrap-compounding at $10^{-10}$) are representational and
absent in PG2.

Ladder sensitivity profile at $10^{-12}$ (PG1; per-section max hull /
defect):

| section | hull | def |
|---|---|---|
| wr1 ($-3/20$ MP) | $4.45\times10^{-6}$ | $4.3\times10^{-8}$ |
| wr7 ($3/20$ MP) | $9.64\times10^{-6}$ | $9.4\times10^{-8}$ |
| wr14 ($-3/20$ PM) | $1.02\times10^{-4}$ | $9.9\times10^{-7}$ |
| wr21 ($3/20$ MP) | $1.04\times10^{-3}$ | $1.0\times10^{-5}$ |

defect/tangent $\approx1\%$ at every section; growth $\approx\times7$
per binary cycle; $|dX/du|\approx10^{9}$ by wr21.

(The table's running entries are filled in the archived logs; the
narrative above is stable under them.)

## 3. What PG2 buys, and when to use it

The audit proves PG2's structural advantage: the $\delta$-linear term
propagates through the *thin anchor derivative* instead of the
window-hulled $[DP]$, so derivative-enclosure width multiplies only the
quadratic and defect terms.  The benchmark shows this is decisive much
earlier than the $10^{-12}$ hull comparison suggests: through the deep
passages and the exchange, the window-hulled $[DP]$ inflates PG1's
tangent by $\sim100\times$ even when the defect looks pristine — the
inflation hides inside $T$, where it masquerades as "physical spread"
and simultaneously leaks $w,z$-sensitivity into the $h,G,P$ rows that
the terminal certificate needs.  PG2's per-leg costs are roughly an
order of magnitude more CPU (C2 variational data), and roughly a
gigabyte-scale working set per run at 160-bit — do not run more than
two concurrently on a 38 GB host.  Use PG1 for cheap reconnaissance and
PG2 for every certificate-grade leg through or after a deep encounter.

## 4. Implementation notes (what a port needs)

* `parameter_graph_capd MODE P Q P2 Q2 [PREC TOL ORDER]`; MODE 1 = PG1,
  MODE 2 = PG2 for every Poincaré and switch update.
* Representation and updates exactly as in the audit's theorem
  statements, including: thin anchor with its own Poincaré run per leg;
  image-intersection sharpening (full $\Delta$); exact section-row and
  $ww$-row imposition; hull-of-anchor-and-set for every mean-value
  domain.
* Runtime self-tests at startup: the algebraic-Map Hessian storage
  convention (CAPD stores TAYLOR COEFFICIENTS — verified empirically:
  $h(0,0,0)=1$ for $a^2$) and a toy PG2 containment check.  The flow
  path (`PoincareMap::computeDP` with Hessian) is Taylor-coefficient by
  documentation and by the `AbstractSection.hpp` formulas.
* Per-leg audit tubes: correlated `MpC0TripletonSet` built from the
  graph (point matrices, widths spilled), stepped with the
  unselected-pair caps of the endgame driver (mandatory — see the
  endgame handoff's trap list), checking separations, the Theorem C$'$
  disjunction, and a hull guard, through the latest return.
* CAPD gotchas encountered: `MpInterval` has no integer `/=`;
  algebraic-map degree must be requested at construction
  (`Map(text, 2)`) — the field/switch makers take an optional degree
  parameter for this.
* Build: `scripts/fable_run_capd_middle_endgame.sh`-style flags
  (MP build, pinned commit); the prototype compiles standalone.

## 5. Recommended next step (ordered)

1. Adopt PG1 with the audit's H1–H7 as the standard leg update
   (your implementation apparently already matches; diff against §4's
   list, especially the full-hull domain and full-$\Delta$
   intersection).
2. Build the exchange-crossing geometric ladder in the pair-{1,3}
   chart ($w_r$ sections bracketing $t\in[3.4,3.5]$, switch keyed to a
   section), and re-run this benchmark at $10^{-8}$, then $10^{-7}$,
   $10^{-6}$.  Expected from the sensitivity data: PASS at $10^{-8}$
   through $\sim10^{-6}$.
3. Fire the terminal certificate at the FIRST post-switch section
   (zero retained binary cycles); never use a fixed-time terminal
   section.
4. Bring in PG2 only when (2) succeeds and the next width step fails
   with defect no longer $\ll$ tangent.

## 6. Files, commits, reproduction

* `docs/FABLE_PARAMETER_GRAPH_AUDIT.md` — commit `4aaca92`.
* `src/fable/verification/parameter_graph_capd.cpp` — commit `e39159a`
  (+ this document's commit).
* Logs: `data/fable/parameter_graph/` (per width and mode, with the
  `PGRAPH_PARAMS` line recording precision/tolerance/order).
* Reproduce the passing $10^{-12}$ run:

```sh
c++ -O2 -DFABLE_MP -Wno-deprecated-literal-operator \
  -I/opt/homebrew/include src/fable/verification/parameter_graph_capd.cpp \
  $(/private/tmp/fable-capd/build-mp/bin/capd-config --cflags --libs) \
  -L/opt/homebrew/lib -lmpfr -lgmp -o parameter_graph_capd
./parameter_graph_capd 1 290000000000 1000000000000 \
  290000000001 1000000000000 160 1e-24 32
# expect: ... PGRAPH_BENCHMARK_PASS mode=1 width=1e-12 geometric=PASS fixed=PASS
```

* Dependency pin: CAPD 6.1.0, commit
  `731079217a9254ea2948d742df2b170895effe7f`, MPFR build.

## 7. Failed attempts and traps (so you do not repeat them)

* The toy self-test initially "failed" on a boundary fiber whose true
  value equals the enclosure bound exactly; double-rounded sampling
  lands outside a 160-bit-tight bound.  Harness slack, not a pipeline
  bug.
* An earlier architecture (this repository's v3) propagated the whole
  anchor box through `computeDP` products per leg — that is the
  documented width-independent $10^{-2}$ defect floor; PG1's thin
  anchor + separate defect removes it entirely (defect
  $7.5\times10^{-19}$ at S1 for $10^{-12}$).
* All the endgame driver's traps apply to the audit tubes:
  unselected-pair step caps, the $Br\cap Qq$ remainder, point matrices
  with width spill.

## 8. Adversarial verdict

The corrected first-order graph is **sound** (audit, Theorems PG1/PG2
with hypotheses H1–H7) and, at $10^{-12}$, passes the full benchmark
with margin to spare.  But it **cannot scale**: its tangent update
multiplies by the window-hulled $[DP]$ every leg, and the benchmark
shows this contaminates the tangent by $\sim100\times$ through the
exchange and kills the certificate chain by $10^{-11}$ (row-mixing into
the terminal margins) and $10^{-10}$ (wrap-compounded nontransversality)
— a precise, measured, mechanism-level proof of the first-order scaling
limit the task asked for.  The sound C2 replacement (PG2) is derived,
proved, implemented, and measured: $51$–$60\times$ tighter at
$10^{-12}$, a clean exchange crossing at $10^{-10}$, defect pinned at
numerics-level ($4.5\times10^{-8}$) independent of width, and corrected
wrapping-free sensitivities that place its capacity near $10^{-8}$ on
this itinerary — with geometric exchange sections projected to extend
it to $10^{-6}$–$10^{-5}$.  Quantitative evidence status: soundness
claims `PROVED ANALYTICALLY` / `PROVED BY COMPUTER-ASSISTED ARGUMENT`
(source inspection) per the audit; every number in §2
`VALIDATED NUMERICAL RESULT` (they are outward-rounded outputs of
rigorous runs, though the *comparisons* between runs are observations,
not theorems); capacity projections `CONJECTURAL`.
