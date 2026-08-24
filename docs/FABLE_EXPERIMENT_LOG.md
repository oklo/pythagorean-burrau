# Fable experiment log

All entries are ORDINARY NUMERICAL EVIDENCE unless marked otherwise.

## 2026-08-23

1. **Checkpoint reproduction.**  `uv sync --frozen` in the Fable worktree
   (separate venv and UV cache); `pytest -q` reproduced `92 passed`; ruff
   clean.

2. **Event atlas, $u=1/3$** (`scripts/fable_probe_event_atlas.py`).
   DOP853, rtol $10^{-12}$, max relative energy drift $4\times10^{-9}$.
   28 events (14 maxima incl. $t=0$) before the terminal escape
   certificate fires at $t=12.25$ (binary bodies $\{3,1\}$, escaper body
   2, $\eta=4$, margin $3.31$).  Deepest encounter separation
   $2.4\times10^{-4}$ at $t\approx3.166$ (an $I$-minimum with
   $K\approx3285$).  Worst maxima: $t=6.33$, $\lvert\mathcal B\rvert=0.41$;
   $t=10.64$, $K=0.0187$; minimal $\lvert\zeta\rvert$ over maxima $0.085$
   at $t=4.09$.  All maxima have min separation $\ge0.25$, matching the
   $U\le2U_0$ bound.

3. **Grid scan** of $u\in[0.03,0.414]$, step $0.008$, $t\le40$
   (scratch `grid_scan.txt`).  Middle interval: minimal event margins per
   parameter mostly $\lvert\mathcal B\rvert\in[0.1,1.5]$; terminal
   certificate fires by $t\le27$ where it fires.  No certificate by
   $t=40$: $u\in\{0.214, 0.246, 0.294, 0.350, 0.390\}$ and the skinny side
   $u\le0.102$.  Near-endpoint $u\ge0.398$: no interior maxima, quick
   ejection.  Outlier: $u=0.342$.

4. **Near-brake at $u=0.342$.**  Refined event: $t=17.6209336$,
   $K=1.357\times10^{-5}$, $\lvert\mathcal B\rvert=8.73\times10^{-3}$,
   $\lvert\zeta\rvert=3.43\times10^{-3}$, $U/U_0=1.0000053$, min
   separation $0.614$, $I=0.564$.  Neighboring $u\pm0.0015$ lose the
   branch inside the window $[16,19.5]$; fine mapping in progress.

5. **Sensitivity measurement, $u=1/3$.**  Direct perturbation
   ($10^{-11}$): amplification $11.6$ at $t=0.5$, $10.5$ at $t=1.0$,
   $4.7\times10^2$ at $t=2$, $4.7\times10^4$ at $t=4$.  CAPD
   C0HOTripletonSet native-interval hull widths nevertheless inflate to
   $8\times10^{-6}$ by $t=0.6$ (factor $\sim10^3$ at the $t=0.376$
   encounter alone) and the covering fails at $t\approx0.93$: wrapping,
   not true conditioning.  Conclusion: multiprecision required.

6. **MP feasibility** (scratch `debug_widths_mp.cpp`).  256-bit
   MpC0TripletonSet, order 40, tol $10^{-50}$: $t=1$ reached in 124 s,
   1314 steps, hull width $10^{-34.4}$ (initial $10^{-77}$); the two
   encounters cost $\approx43$ digits but MP absorbs the loss.
   MpC0HOTripletonSet does not compile against this CAPD commit on this
   platform (ambiguous `unsigned long long` conversion in `HOData.h`);
   MpC0TripletonSet is used instead.

7. **MP certificate run** launched: 768 bits, order 60, tol $10^{-80}$,
   detached (`mp_certificate_768.log` in the session scratchpad).

8. **Verifier engineering.**  Two defects found and fixed in the Fable
   verifiers (never affecting a recorded PASS): (i) CAPD's trial-step
   rough enclosure can sweep the collision set at deep encounters and
   throw a domain error; the fix catches it, halves a step cap, and
   retries.  (ii) A thrown step can leave `ITimeMap` in a spurious
   completed state that silently truncates the run; the fix rebuilds the
   time map (the set carries its own clock) and replaces the loop
   condition by an explicit time-target check.  The u=2/5 PASS predates
   both defects' triggering conditions (no exception occurred in it and
   its covering is complete up to its firing time).  The potential is now
   evaluated only in the initial phase, so main-phase scalar checks are
   polynomial and cannot throw.

9. **Point certificates, first batch.**  PASS: u=2/5 (21,20,29) at 256
   bits; u=81/200 (33439,32400,46561) native doubles, escape margin
   0.377 at t=0.716, final width 3.4e-08.  Native mode fails beyond the
   shallowest orbits (uncovered steps from wrapping, e.g. u=41/100 at
   t=1.42); MP retries queued with per-case labellings measured from
   ordinary probes: binary/escaper and eta differ across the interval
   ((0,1|2) near the endpoint, (1,2|0) at u=41/100 and 5/13).

10. **Through-encounter amplification measurements** (basis of the
    blocked-route entry): point width 1e-16 -> 3.4e-8 through the
    u=81/200 endpoint deep pass; icert boxes of width 1e-4/1e-6/1e-8 all
    fail or blow up at the first deep pass even with the u-correlated
    9-variable field; u=1/6 first-encounter miss ~5e-7 (B^11 law) stalls
    direct integration in every precision tried.

11. **u=1/3 runs.**  768-bit/1e-80 main run and 1088-bit/1e-130
    insurance run in progress with the fixed code; 512-bit/1e-60 atlas
    for u=171/500 in progress.

12. **Near-brake reliability check.**  Re-integrating u=0.342 at rtol
    1e-13 gives, at the same t=17.6209, a hierarchical configuration
    (r13=0.075, both other distances ~9.6, speeds 1.5-3.5) — flatly
    inconsistent with the rtol 1e-12 near-stop.  Late-time
    double-precision events are pure noise at the O(1) level; the
    "closest interior near-brake" is unverified.  Decision deferred to
    the rigorous 512-bit atlas at u=171/500.

13. **171/500 resolution, cross-validated.**  Independent 50-, 60-, and
    90-digit order-40 Taylor integrations to t=18.2 all give exactly 25
    dI/dt-zero events, none after t≈13.4, minimum event kinetic energy
    ≈0.136, and no low-K event anywhere.  The u≈0.342 "near-brake" is
    conclusively double-precision noise.  (Integrator cross-checked
    against DOP853 to 2.5e-10 at t=2.)

14. **LC-chart verifier implemented and mechanics-validated.**  The
    burrau_lc_certificate_capd verifier interleaves the physical covering
    with one Levi–Civita passage (entry construction → LC flow → damped
    exit construction) exactly per FABLE_LC_COVERING_DESIGN.md.  Chart
    equations validated against direct integration to 1.7e-9 (Python);
    a live passage through the t=0.376 encounter took 5 sigma-steps with
    no measurable digit cost (hull −53.2 before and after), versus
    thousands of steps and ~10 digits direct.  The measured direct cost
    of the deep t=3.166 encounter is ~97 digits (deep run exited it at
    width 1.2e-3 from a 1e-140 budget), which dooms all direct u=1/3
    runs; the LC production run (512 bits, tol 1e-120, order 90) and a
    1e-60 pathfinder are in flight with zone thresholds 1/1000–1/500
    selecting only the deep encounter.

15. **LC pipeline validated in the real verifier.**  The 1e-60 pathfinder
    executed the full certificate pipeline: physical covering to t=3.166,
    exact chart entry, 313 capped sigma-steps through the deep encounter
    with rigorous no-collision bound (enclosure min |w|^2 = 8.1e-5 > 0)
    and total cost ~2 digits (hull 1.9e-15 -> 3.0e-13; direct cost was
    ~97 digits), exact exit reconstruction (hull 2.3e-14), resumed
    covering.  It then exhausted its deliberately small budget at t~5.6
    as predicted.  Debug history (all caught by rigorous checks): zone
    threshold catching the wrong encounter; fresh-ITimeMap clock; ITimeMap
    overriding setMaxStep; time-interval width compounding from target
    arithmetic — fixed by driving the zone with direct capped solver
    moves.  The 1e-120/order-90 production run carries the theorem.

16. **Burrau budget model (measured).**  The 512-bit/1e-120/order-90 LC
    production run calibrated the full digit budget: ~47 digits to reach
    the deep encounter (t=3.166), ~2 through the LC passage, then a
    post-encounter burn of ~10/unit through t~8.4 that collapses to
    ~0.2/unit as the system separates (t=8.4-9.3), with violent local
    spikes (4 digits in 0.009 units at t=9.95).  Total requirement
    ~127 digits; the 1e-120 run died at t~9.95 as this model predicts.
    In flight: 512/1e-130/order-130 (racer3, marginal, ~1.4 units/hour)
    and 768/1e-160/order-110 (insurance, comfortable, ~0.65 units/hour).
    Pre-encounter burn is nearly config-independent (~47-48 digits at
    orders 90-130), so step size does not dominate the wrapping there.
