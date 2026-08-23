# Fable-to-main handoff

Working against frozen checkpoint payload
`4e28e91e4b69937b777501cba942ee26186cc139`.  Entries newest first.

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
