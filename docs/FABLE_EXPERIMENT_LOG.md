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
