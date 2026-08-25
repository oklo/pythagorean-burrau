# Endgame handoff: a certified nonperiodic real interval and a working driver

Date: 2026-08-25.  From the independent second agent (branch
`fable/middle-terminal-escape`, worktree `pythagorean-burrau-fable-middle`).
Audience: the primary worker.  Everything here is committed on the branch;
no protected file was touched.  Cherry-pick list at the end.

## 1. The result

**Theorem (`PROVED BY COMPUTER-ASSISTED ARGUMENT`).**  Every real

\[
 u\in\left[\;\frac{29000000000}{10^{11}},\ \frac{29000000010}{10^{11}}\;\right]
 =\left[\,0.29,\ 0.29+10^{-10}\,\right]
\]

of the normalized tied family is **nonperiodic**: the classical solution
from the tied brake admits no second labelled brake at any collision-free
time.  The certificate is a single validated propagation carrying the
fiberwise brake-exclusion covering (Theorem C$'$ in the record) from the
exact tied launch through $t_\ast(u)\in[4.3014,4.3016]$ — through all
four deep binary passages (selected-pair pericenters down to
$4.4\times10^{-4}$) and through the exchange scattering at
$t\in[3.44,3.48]$ — terminating in the phase-robust binary–escaper
certificate with outward-rounded margins

\[
 \inf d\ge1.8679,\quad \inf\dot\rho\ge2.0477,\quad
 \inf E_\rho\ge0.8225,\quad \sup h\le-9.2745,\quad
 \inf(-\eta-h-\Delta)\ge5.0696\quad(\eta=4).
\]

The terminal conclusion is the escape theorem's dichotomy (later inner
$\{2,3\}$ collision ending the classical solution, or permanent escape
of body 1); both branches exclude every later brake.  Cross-verified by
the standalone interval checker (`middle_escape_terminal_capd
--phase-robust`) on the outward-rounded terminal box; the cross-check
output is archived beside the certificate log.  This is the program's
first real-interval nonperiodicity statement.  A tiling campaign of
adjacent $10^{-10}$ tiles toward $[0.29,\,0.29+10^{-8}]$ is in progress
in the second agent's scratch area (each tile one 7-minute run); tiles
will be archived into `data/fable/` once complete — at the time of
writing, only the nested widenings starting at $0.29$ are archived.

An independent adversarial review of the proof chain found no
invalidating error; its findings (a previously unstated Theorem C
variant, now stated and proved in the record; two CAPD-internals
assumptions, now resolved against the pinned source and hardened in the
driver; and the claim-hygiene items in this section) are documented with
their repairs in the record's "Review and repairs" section.

Full statement, proof structure, and soundness notes:
`docs/FABLE_MIDDLE_INTERVAL_NONPERIODICITY.md`.
Archived logs: `data/fable/middle_escape_endgame_{first_interval,3e11_interval,1e10_interval}.log`.

## 2. The driver you can reuse today

`src/fable/verification/middle_escape_endgame_capd.cpp`, mode
`run_endgame_c0` (default; the C1-graph pipeline survives under
`FABLE_ENDGAME_GRAPH=1` but see §4).  Design:

* one `MpC0TripletonSet` over the whole tile with **u as a frozen state
  variable** — the Lohner representation carries the parameter–state
  correlation step by step, which beats the per-leg mean-value graph
  through deep passages by orders of magnitude;
* **no Poincaré sections anywhere**: every accepted step's enclosure is
  audited (mutual separations positive; $\dot I\neq0\ \lor\ K>0\ \lor\
  U>U_0\ \lor$ residual excludes zero; launch window via $U<2U_0$ and
  the strict-decrease argument), and the terminal certificate is
  evaluated **fiberwise on a step enclosure** — each real $u$ needs only
  *some* collision-free certificate time, which any passing enclosure
  provides;
* chart schedule from the measured deep-encounter inventory:
  pair-13 $[0,1]$ → Form-A switch → pair-23 $[1,7/4]$ (covers the
  $\{2,3\}$ encounters at $1.047$ and $1.596$) → Form-A switch-back →
  pair-13 $[7/4,7/2]$ (covers $\{1,3\}$ at $1.92$, $2.33$, $2.92$, and
  the exchange) → **Form-B** switch → pair-23 escape leg;
* chart switches by a rigorous **mean-value set image**: for the
  tripleton $x+Cr_0+(Br\cap Qq)\subseteq H$,
  $F(p)\in F(x)+[DF](H)(p-x)$, rebuilt with point matrices and width
  spill.  Two implementation traps that both bite hard: the remainder
  must be the $Br\cap Qq$ **intersection** ($B$ alone is astronomically
  ill-conditioned after thousands of steps), and $[DF](H)\,C$ must be
  split into midpoint matrix plus spilled widths (interval matrices in
  the representation silently corrupt the set).

Run it:

```sh
sh scripts/fable_run_capd_middle_endgame.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-mp  P Q P2 Q2  80 1e-14 24
```

Exact-map and formula regressions: `tests/test_middle_escape_symbolic.py`
and `tests/test_middle_escape_endgame_maps.py` (22 exact tests).

## 3. Measured economics (what your reconditioning must beat)

All numbers measured on this itinerary at $u=0.29$:

| mechanism | measured value |
|---|---|
| selected-pair LC passage cost (incl. $r=4.4\times10^{-4}$) | hull $\times3$ per passage — $\sigma$-time synchronizes the pericenter, so deep selected passages are nearly free |
| exchange ($t\in[3.44,3.48]$, both pairs close) transient sensitivity | $10^{6}$–$10^{8}$ at any fixed integration clock |
| exchange curvature wrapping | needs incoming hull $\lesssim10^{-6}$; threshold behavior — collapses once below critical width |
| post-escape (ordinary) sensitivity at $t=4$–$4.5$ | $2\times10^{4}$ — the spike re-contracts dynamically, but interval hulls cannot |
| section-synchronized sensitivity through **all** passages (ordinary, `probe_middle_escape_endgame.py`) | $\sim1.2$–$4\times10^{3}$, roughly flat across passages |
| passing tile widths, this driver, fixed clock | $10^{-10}$ PASS · $3\times10^{-10}$ FAIL (post-exchange switch) · $10^{-9}$ FAIL (same) · $10^{-8}$ FAIL (exchange core) |
| C1 mean-value graph (per-leg Poincaré + tangent outer products) | du-independent slack floor $\sim10^{-2}$ at the deep passages — unusable for the endgame |

Interpretation: the exchange is the **only** obstruction between the
committed first-maximum theorem and full-tile nonperiodicity.  Your
geometric-section reconditioning attacks exactly the right quantity —
the $10^{3}$-vs-$10^{6\text{--}8}$ gap between synchronized and
fixed-clock sensitivity is the entire margin the full tile needs.

## 4. Engineering traps found (each cost a failed run)

1. **Unselected-pair step caps are mandatory.**  A $\sigma$-step sized
   for the selected pair sweeps a large fraction of a close unselected
   separation; the rough enclosure of its $1/r^3$ succeeds with garbage
   widths and **no exception**, silently poisoning the set (observed:
   hull $10^{12}$ passing the $J<0$ audit).  Cap physical time by
   $r_{\text{unsel}}^{3/2}/40$ and add a hull sanity guard.
2. **Form A vs Form B at the endgame switch**: in $t\in[3.5,3.7]$ the
   family $g_{23}$ hugs the negative real axis; the committed Form-A
   switch map degenerates there.  Use the Form-B lift
   ($w_i=\sqrt{(|g|-g_x)/2}$), valid on $g_x<0$, uniformly across the
   tile at $t=3.5$.
3. **The pair-23 excursion at $[1,7/4]$ is not optional** — the
   $\{2,3\}$ encounters at $1.047$ ($r\approx0.003$) and $1.596$
   ($r\approx4.4\times10^{-4}$) sit between the committed events, and
   the second is invisible to event-time sampling (my recon initially
   missed both; the depth at $1.596$ also varies non-monotonically
   in $u$).
4. Tolerance is not the binding constraint anywhere down to
   $10^{-12}$ tiles at 80-bit/1e-14/order 24; hulls are
   family-spread-driven.

## 5. The terminal edge (from the first phase of this run)

Independent of the driver, the terminal machinery is ready for your
correlated box whenever your propagation reaches the final leg:
`docs/FABLE_MIDDLE_ESCAPE.md` (chart-form theorem (T), fail-closed guard
order, **phase-robust corollary** — with $h$ certified, no $w,z$
condition is needed, so terminal-leg binary-phase wrapping is
irrelevant), `src/fable/verification/middle_escape_terminal_capd.cpp`
(`--phase-robust`, `--binary13` for the mirrored labelling below
$u\approx0.2896$ where the hierarchy flips and body 2 is ejected), and
the wrapping budgets (0.019/0.102/0.169 at $T=4,9/2,5$ over the full
committed tile).

## 6. Cherry-pick list (atomic, in order)

| commit | content |
|---|---|
| `128a459` | exact pair-{2,3} escape map + 17 symbolic tests |
| `7b13c27` | chart-form theorem doc |
| `5b6e695` | standalone interval terminal checker + wrapper |
| `5d48655` | phase-robust corollary + checker mode |
| `5827291` | endgame + box-tolerance recon scripts |
| `f759cc1` | `--binary13` mirrored labelling |
| `d6fe00a` | reusable terminal edge contract |
| `c1525c2` | endgame driver skeleton (C1 graph) + exact switch-map tests |
| `92bd587` | correlated-C0 architecture + chart schedule |
| `52d0f93` | **the interval certificate** + archived log |
| `368ae32` | theorem record |
| `dfb8fd3`, `bd3207a` | 3e-11 and 1e-10 widenings |
| `fe3dbf0` | run report / handoff updates |

Nothing here depends on your uncommitted work; the two protected files
were never modified.  The single highest-leverage merge is the driver +
theorem record; the single highest-leverage read is §3.
