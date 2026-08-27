# Prompt for the next research run: wide-tile certification via the PG2 graph and geometric exchange sections

You are returning to active research on the Pythagorean–Burrau
nonperiodicity conjecture.  Work in the worktree

    /Users/greglaughlin/Projects/pythagorean-burrau-fable-middle

on branch `fable/middle-terminal-escape` (or a child branch).  Do not
modify the main worktree `/Users/greglaughlin/Projects/pythagorean-burrau`
(you may read it); do not modify
`src/fable/verification/burrau_lc_certificate_capd.cpp` or
`tests/fable/test_tied_first_maximum_charts.py`.  Commit verified
milestones atomically.

## State you inherit (read in this order)

1. `docs/FABLE_PARAMETER_GRAPH_HANDOFF.md` — benchmark results and the
   corrected scaling picture.  Headline: the second-order graph (PG2)
   is sound, implemented in
   `src/fable/verification/parameter_graph_capd.cpp`, passes the full
   launch→exchange→ladder→terminal benchmark at width $10^{-12}$, and
   crosses the exchange at $10^{-10}$; the first-order graph (PG1) is
   sound but wrapping-limited and dies by $10^{-11}$–$10^{-10}$.  True
   wrapping-free sensitivities: exchange $4\times10^{4}$, ladder-end
   $6.3\times10^{6}$, section-synchronized $\sim10^{3}$.
2. `docs/FABLE_PARAMETER_GRAPH_AUDIT.md` — Theorems PG1/PG2 with
   hypotheses H1–H7 and the CAPD source citations.  Follow the
   hypotheses exactly; two of them (full-convex-hull C1/C2 domain;
   full-range $\Delta$ in the defect intersection) are silently unsound
   to omit.
3. `docs/FABLE_MIDDLE_INTERVAL_NONPERIODICITY.md` — the certified
   nonperiodic interval $[0.29, 0.29+1.01\times10^{-8}]$, Theorem C$'$
   (fiberwise covering criteria), and the phase-robust terminal
   corollary; `docs/FABLE_MIDDLE_ENDGAME_HANDOFF.md` — the C0 endgame
   driver, chart schedule, and the engineering traps (unselected-pair
   step caps; tripleton remainder intersection; point matrices with
   width spill).
4. `data/fable/parameter_graph/` — archived benchmark logs (the
   `PGRAPH_PARAMS` line in each log records precision/tolerance/order).

Dependency pin: CAPD 6.1.0, commit
`731079217a9254ea2948d742df2b170895effe7f`, MP build at
`/private/tmp/fable-capd/build-mp`.  Machine constraint: at 160-bit,
PG2 (C2) runs use ~GB-scale working sets — run at most two
concurrently.

## Unfinished measurements (complete these first)

`pg2_w1e10.log` may already contain the finished $10^{-10}$ ladder
outcome; if not, re-run it, then PG2 at $10^{-11}$, $10^{-9}$,
$10^{-8}$, one at a time:

    ./parameter_graph_capd 2 P Q P2 Q2 160 1e-24 32

Fill the benchmark table in the handoff and archive the logs.  Stop at
the first PG2 failure and diagnose it in the task taxonomy (physical
spread / anchor error / derivative wrapping / quadratic curvature /
nontransversality / chart degeneration / separation loss / brake-cover
loss / terminal-margin loss).

## Primary task: geometric sections through the exchange

The measured obstruction to widths beyond $\sim10^{-8}$ is the
fixed-clock crossing of the exchange ($t\in[3.4,3.5]$).  The measured
cure is resynchronization: section-synchronized sensitivities stay
$\sim1.2$–$4\times10^{3}$ at pair-{1,3} geometric sections adjacent to
the deep passages (three independent measurements; see the endgame
handoff §3).  Replace the stage-1 fixed-time legs across $[3.3,3.5]$ in
`run_parameter_graph` with a pair-{1,3} geometric ladder, e.g.

    wr = -2/5 MP  (ordinary time ~3.447)
    jd = 0 MP     (the fourth minimum, ~3.4686)
    wr = 0  MP    (~3.4694)
    then the Form-B switch keyed to the wr = 0 section image
    (g23_x < 0 holds there; verify the hull stays off the branch cut),

with the audit tubes and covering checks unchanged (the Theorem C$'$
disjunction and the unselected-pair caps are mandatory through the
double encounter — the unselected $\{2,3\}$ pair dips to $r\approx0.0285$
at $t\approx3.4515$ inside these legs).  Re-run the benchmark ladder
at widths $10^{-8}$, $10^{-7}$, $10^{-6}$, $10^{-5}$; stop at first
failure and diagnose.  Fire the terminal certificate at the FIRST
post-switch section (per-fiber times; never a fixed-time terminal
section — audit item 10; every retained binary cycle costs $\times5$–$7$
in width).

## Secondary task: certify a wider real interval

If a width $w\ge10^{-8}$ passes the full launch→terminal chain with the
exact tied launch, complete per-step covering, rigorous switches, and
the validated terminal certificate, then that run IS a nonperiodicity
certificate for its tile (Theorem C$'$ + the terminal theorem — same
chain as `FABLE_MIDDLE_INTERVAL_NONPERIODICITY.md`).  Tile
$[0.29, 0.29+N\cdot w]$ with adjacent runs (exact rational shared
endpoints), archive per-tile logs, and update the theorem record's
widened statement.  Do not claim any interval whose chain is
incomplete; use the project's evidence statuses throughout
(`docs/FABLE_MIDDLE_INTERVAL_NONPERIODICITY.md` shows the required
form).

## Watch items (from the audits — each cost a failed run once)

* Build every mean-value/Taylor domain as hull(set, anchor); intersect
  defects against the image minus $T\Delta$ (+$Q\Delta^2$) over the
  FULL range; impose the $ww$-row ($T=1$, $Q=E=0$) after every leg.
* The tripleton remainder is $Br\cap Qq$; point matrices only, widths
  spilled.
* Unselected-pair step caps ($r^{3/2}/40$ physical) in every audit
  tube; hull sanity guard.
* CAPD Map Hessians store Taylor coefficients (runtime self-test in the
  prototype verifies this at startup); the flow-Hessian path is
  Taylor-coefficient by the `computeDP` documentation.
* Memory: at most two concurrent C2 runs.

## Deliverables

* Completed benchmark table (both modes, all widths) in
  `docs/FABLE_PARAMETER_GRAPH_HANDOFF.md`, with archived logs.
* The geometric-exchange itinerary, its width ladder, and diagnoses.
* If achieved: the widened theorem record + archived certificates +
  an updated `docs/FABLE_TO_MAIN.md` entry with a cherry-pick list.
* A run report stating what was proved, what failed, and the single
  highest-leverage next action.

The highest-value outcome is a certified real interval two or more
orders of magnitude wider than $1.01\times10^{-8}$, produced by the
audited graph machinery rather than by tiling thousands of narrow runs.
