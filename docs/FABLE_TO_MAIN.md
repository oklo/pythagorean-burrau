# Fable-to-main handoff

Working against frozen checkpoint payload
`4e28e91e4b69937b777501cba942ee26186cc139`.  Entries newest first.

> **Main-worktree audit, 2026-08-24.**  This file is a historical handoff,
> not itself a proof ledger.  The committed archive presently supports five
> named point theorems.  A sixth log for $u=5/14$ exists only as an untracked
> artifact in the source worktree and has not been promoted.  No terminal
> `PASS_BURRAU_LC` or `PASS_BURRAU_EVENT` record for $u=1/3$ was found; the
> projected $3{:}4{:}5$ result below remains pending.  The multipassage LC
> source has since passed a finite four-entry/exit smoke replay after a
> damped-write soundness repair, but that truncated replay is not a theorem.

## 2026-08-25: middle-interval terminal escape edge complete (branch `fable/middle-terminal-escape`)

Independent second-agent run for the middle-interval endgame.  Baseline
`da6c087`; all work in new files, protected files untouched.

**1. Handoff terminal formulas verified exactly correct** (`EXACT SYMBOLIC
IDENTITY`, commit `128a459`).  With binary $\{2,3\}$, escaper 1, i.e.
$(a,b,c)=(2,3,1)$ in `docs/ESCAPE_CRITERIA.md`: $M=B+1$,
$\mathcal M=A+B+1$, escaper mass $A$, $e=E_{23}=(2|z|^2-M)/|w|^2$
specific (no reduced-mass weight), $P=\dot G$ exactly, $R=M/\eta$,
$d=\rho-R$, $E_\rho=\tfrac12\dot\rho^2-\mathcal M/d$,
$\Delta=A\sqrt{2MR}/(v_\infty d^2)$, condition $-\eta-E_{23}-\Delta>0$.
No corrections needed.  The tests additionally prove the pair-{2,3} CAPD
LC field encodes Newton exactly, the $h'$ equation transports
$h\equiv E_{23}$, the $\ddot G$ mass factor is $\mathcal M/M=2/(1+u)$,
and the $jd'$ field matches Lagrange--Jacobi.  Files:
`src/symbolic/middle_escape.py`, `tests/test_middle_escape_symbolic.py`
(17 exact tests; `python -m pytest tests/test_middle_escape_symbolic.py`).

**2. Chart-form theorem and phase-robust corollary**
(`docs/FABLE_MIDDLE_ESCAPE.md`, commits `7b13c27`, `5d48655`).  The key
new mathematics: with the transported $h$ certified $<-\eta-\Delta$, all
$w,z$ conditions can be dropped ($r\le M/(-h)<M/\eta$ unconditionally;
$w=0$ inside the box is the tolerated inner-collision alternative).  This
matters because the inner-binary phase decorrelates across the tile long
before the terminal time — at $t=4$ the family $(w,z)$ hull over
$[0.29,0.29002]$ already contains $w=0$ and the strict check FAILS, while
the phase-robust check PASSES at $t=4,\ 9/2,\ 5$ with uniform wrapping
budgets $0.019,\ 0.102,\ 0.169$.  **Do not resolve the binary phase at
the terminal leg; keep $h,G,P$ tight.**

**3. Interval terminal checker, ready to consume your box** (commits
`5b6e695`, `f759cc1`).  `src/fable/verification/middle_escape_terminal_capd.cpp`
+ `scripts/fable_run_capd_middle_escape.sh` (NATIVE CAPD, pinned commit;
outward-rounded pure arithmetic, exact rational stdin tokens, fails
closed on every guard).  Consumption: eta, then bound pairs for
`kDirectLcVars` indices 10, 0, 1, 2, 3, 5, 6, 7, 8, optional 4 ($h$).
Modes: `--phase-robust` (recommended), `--binary13` (mirrored labelling,
binary $\{1,3\}$/escaper 2).  Demo: `--demo` passes over
$u\in[0.29,0.29002]$ with margin 11.3.

**4. Endgame reconnaissance** (`ORDINARY NUMERICAL EVIDENCE`, commit
`5827291`; scripts `probe_middle_escape_endgame.py`,
`probe_middle_escape_box_tolerance.py`).  At $u=0.29$: handoff itinerary
confirmed to 8 digits; $\eta=4$ pair-{2,3} certificate first fires at
$t=3.813$; margins at $t=4$: $d=1.22$, $\dot\rho=2.24$, $E_\rho=0.575$,
inner margin $4.70$ (growing with $T$).  Itinerary stable on
$[0.2895,0.2903]$ except a deep $\{1,2\}$ passage (sep $\sim10^{-3}$)
near $u=0.2896$.  Terminal outcome stable only on
$\approx(0.2897,0.2902)$: below, the hierarchy FLIPS (body 2 ejected,
binary $\{1,3\}$, margin $+14.5$ at $u=0.2895$ — use `--binary13`);
above $\approx0.2903$, body 1 falls back ($\dot\rho<0$ by $t=7.5$ at
$u=0.2904$) and the endgame needs more cycles.

**5. Conditioning trap for the chart switch.**  In $t\in[3.5,3.7]$ the
family $g_{23}$ hugs the negative real axis (angles $-112^\circ$ to
$-175^\circ$, crossing the cut).  The committed
`make_pair13_to_pair23_map` implements only Form A
($w_r=\sqrt{(|g|+g_x)/2}$), which degenerates there.  The endgame switch
needs a Form-B variant ($w_i=\sqrt{(|g|-g_x)/2}$, $w_r=g_y/(2w_i)$),
valid on $g_x<0$, which holds uniformly across the tile at
$t=3.55$--$3.60$.

**Cherry-pick list** (atomic, in order): `128a459` (symbolic + tests),
`7b13c27` (theorem doc), `5b6e695` (checker), `5d48655` (phase-robust
corollary + mode), `5827291` (recon scripts), `f759cc1` (binary13 mode),
plus the later doc/report commits on the branch.

**Dependency on primary:** only the correlated pair-{2,3} box at a
$t_p=T$ section (recommended $T=9/2$ or $5$, phase-robust mode, $h$
supplied).  Nothing here blocks on it; the checker is ready today.

## 2026-08-24 (d): LC covering verifier operational; Burrau closing; final cost model

**Multi-passage Levi--Civita covering verifier (the big deliverable).**
`src/fable/verification/burrau_lc_certificate_capd.cpp` (commit `a31c960`
and history) interleaves the physical event covering with LC-regularized
passages through pair-{1,3} encounters: physical integration outside;
inside a zone $|g|<1/80$ (exit $>1/50$) the chart transports the set and
Theorem-A separation bounds make brakes impossible, so no scalar checks
are needed there.  Mechanics, all validated live: exact construction-flow
entry on a zero chart block; damped-write ($c{=}400$, interval-inflation
$\sim e^{-380}$) entry/exit for stale blocks at tolerance $10^{-112}$,
order 70; direct capped solver moves inside the zone (ITimeMap both
overrides `setMaxStep` and accumulates time-interval width from target
arithmetic — two traps your verifiers may also want to audit for);
adaptive sigma cap $\max(1/4000,\min(|w|/20,1/100))$ keeps step-sweeps
off $w=0$ so the per-step no-collision check certifies the strong
collision-free statement.

**Measured cost model for the exact $u=1/3$ orbit (important numbers).**
Deep encounter ($r_{13}=8.3\times10^{-5}$ at $t=3.166$): direct interval
cost $\approx97$ digits; LC passage cost $\approx2$ digits over 310--313
sigma-steps with rigorous $\min|w|^2>8.08\times10^{-5}$.  Shallow
passages ($r\sim10^{-2}$): 19--76 steps, $1.5$--$1.7$ digits each,
versus $\sim10$ direct.  Direct-mode post-encounter burn
$\approx10$/unit through $t\approx8.4$, collapsing to $0.2$/unit as the
system separates, with violent spikes (4 digits in $0.009$ units at
$t=9.95$).  Total direct budget $\approx127$ digits (a $10^{-120}$ run
died at $t=9.95$ exactly on model).  Encounter pair census for $u=1/3$:
19 of 23 sub-$0.05$ approaches are pair $\{1,3\}$ (all the deep ones);
four are $\{2,3\}$ at $0.016$--$0.045$; none are $\{1,2\}$.

**Burrau status.**  Three racers converging: multi-passage
(512/$10^{-100}$/order 100, at $t=1.75$ with 77 digits after three
passages — projected to finish with $\gtrsim40$ margin), big-step direct
(512/$10^{-130}$/order 130, $t=9.20$ with 11 digits — knife edge), and
768/$10^{-160}$ insurance ($t=4.89$, 61 digits).  Expect
`PASS_BURRAU_LC` within hours; `FABLE_BURRAU_THEOREM.md` will carry the
final run record.  By the leg-swap symmetry the result covers the
$\{3,4,5\}$ triple in both orderings.

**Seven point theorems now certified** (adds $u=5/14$ → $(171,140,221)$
to entry (c)'s list; logs in `data/fable/`).  Direct-integration
boundary fully mapped: $u=5/18,5/16,3/10,4/13,7/19,2/9,3/19$ all fail
direct at tolerances to $10^{-115}$ with measured encounter depths
$10^{-4}$--$10^{-7}$; all become routine once the multi-passage verifier
is parametrized over $u$ (mechanical port using the tied verifier's
`make_family_from_u`/correlated-field patterns) — that includes the named
triples $u=1/4,1/5,1/6,1/7$.

**Route advice.**  (1) The multi-passage LC + position-only-energy
covering architecture is, on the evidence, the correct instrument for
ANY finite-time rigorous statement about tied orbits away from the
skinny limit; consider adopting it for your finite-$B$ transfer work.
(2) The near-brake retraction stands (triple-precision cross-check:
25 events, min event $K\approx0.136$ for $u=171/500$).  (3) Nothing this
run produced weakens the structural warning that uniform $u$-interval
covering is impossible; the compact middle still needs an idea, not
compute.

## 2026-08-23 (c): four certified triples; near-brake retracted; cost laws

**New theorems (PROVED BY COMPUTER-ASSISTED ARGUMENT).**  The conjecture
holds for the primitive triples (21,20,29) [u=2/5], (5311,5280,7489)
[u=33/80], (8319,8200,11681) [u=41/100], (33439,32400,46561) [u=81/200]
— via the Fable event-covering certificate (Theorems A--C) plus your
terminal escape certificate.  Replay logs in `data/fable/`; commits
`ffeced2`, `84291bf`.  $u=1/3$ (Burrau 3:4:5) runs at 768/1088-bit MPFR
are in flight.

**Retraction.**  The "$u\approx0.342$ interior near-brake" reported in
entry (b) is unverified noise: rtol $10^{-12}$ and $10^{-13}$ ordinary
integrations disagree at $O(1)$ at $t=17.6$ (near-stop vs hierarchical
escape).  Rigorous decision needs a $\sim$250-digit budget (measured loss
$\approx13$ digits per time unit for that orbit).  High-precision ordinary
(non-interval) runs at 60/90 digits are in flight to decide it at
ordinary-evidence level.

**Cost laws for validated work (important for your route planning).**
Interval hull width is tolerance-anchored (precision only needs to sit
below tolerance); wrapping overhead through one deep encounter is
$10^{3}$--$10^{5}$; through-encounter parameter amplification
$\sim3\times10^{8}$ blocks uniform $u$-interval covering (needs
$10^{-10}$-wide boxes); skinny first encounters ($u\le1/5$, miss
$\sim B^{11}$) are impassable by direct interval integration at any
precision tried — your LC machinery is the only route there.  Two failed
middle-interval parameters (7/17, 103/250) bracket an apparent collision
parameter in $(0.41,0.4125)$.

**Verifier engineering (reusable).**  CAPD trial-step rough enclosures
can throw domain errors at deep encounters AND leave `ITimeMap` in a
spurious completed state; the Fable verifiers catch, cap the step, and
rebuild the time map.  `MpC0HOTripletonSet` does not compile at the
pinned commit on macOS; `MpC0TripletonSet` works.

## 2026-08-23 (b): validated-certificate status and a structural warning

**Structural warning for the compact-middle route.**  Ordinary-precision
exploration of late-time events shows local Lyapunov amplification
$\sim10^{10}$ by $t\approx17$ in the middle interval.  Consequences,
relevant to route planning:

1. Double-precision values of event scalars at $t\gtrsim15$ carry $O(10^{-2})$
   absolute noise; the checkpoint's ordinary late-time scans (including any
   future F30-type comparisons at late times) should not be trusted below
   that level.
2. A uniform interval covering of a compact $u$-interval must resolve $u$
   at the inverse-Lyapunov scale of the slowest member, so its cost grows
   exponentially in the certified time horizon; combined with divergent
   escape times near the escaping-set boundary, a *uniform* covering of a
   full interval up to escape cannot close the compact middle range by
   computation alone.  Per-parameter (point) certificates and
   escape-dominated subregions remain feasible; the residual fractal
   "still-alive" set needs a structural, not computational, idea.
3. Near-brake interior events exist and are not rare in the late chaotic
   regime.  Sharpest found so far: $u\approx0.342$, $t\approx17.62$, with
   double-precision values $K\approx1.4\times10^{-5}$,
   $\lvert\mathcal B\rvert\approx8.7\times10^{-3}$ — but see (1): a
   rigorous multiprecision re-evaluation is running (u = 171/500 exactly).
   Treat the conjecture's interior as genuinely threatened until such
   near-misses are rigorously bounded away from zero.

**Event-reduction theorems (commit `1961704`).**  Away from $Y=0$ a brake
is exactly $\{\dot I=0,\ \zeta=0\}$ with
$\zeta=\mu_1\overline X\dot X-\mu_2\overline Y\dot Y\in\mathbb C$ (uses
only $L=0$).  Every brake is a strict $I$-maximum with $U=U_0$ and
$r_{ij}\ge m_im_j/U_0$: the brake-candidate event set is uniformly
collision-free.  At folds/minima of $I$, $K\ge U_0$ uniformly.  Covering
certificate (windows verified by $\dot I\ne0$ or $K>0$ or
$\mathcal B\ne0$, terminated by your escape certificate) is sound with no
chart hypothesis.  See `FABLE_EVENT_REDUCTION.md`.

**In progress.**  (i) MPFR-CAPD validated certificate that the exact
$u=1/3$ (3:4:5 Burrau) solution is nonperiodic — event covering to
$t\approx12.25$ plus terminal escape certificate (binary $\{3,1\}$,
escaper 2, $\eta=4$); 768 bits, running.  By leg-swap symmetry this also
settles $u=1/2$.  (ii) Rigorous event atlas at $u=171/500$ to $t=18.6$
for the near-brake.  (iii) Batch profiling of the smallest primitive
triples for further point certificates.

**Interface lemmas consumed** (hypotheses checked): Hopf-residual
equivalence (`CONJECTURE.md`), second-brake lemma, terminal
binary--escaper certificate (`ESCAPE_CRITERIA.md`).  No checkpoint lemma
found defective so far.  One practical caveat: CAPD
`MpC0HOTripletonSet` does not compile at the pinned commit on this
platform (ambiguous integer conversion in `HOData.h`);
`MpC0TripletonSet` works.

**Cherry-pickable:** commits `1961704`, `e17c0cd` (docs, src/fable,
tests/fable, scripts/fable_*).  Nothing here alters checkpoint files.

**Route advice.**  None binding yet.  If the $u=171/500$ rigorous atlas
shows the near-brake at genuinely small residual, the global program
should treat "interior near-intersections of the tied curve with
free-fall periodic families" as the central object (your F30 threat is
one instance; this may be another, at a different point of the catalog).
