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
