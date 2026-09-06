# Fable middle-escape run report

Date: 2026-08-25.  Branch `fable/middle-terminal-escape`, baseline
`da6c087`.  All work in new files; the two protected files were never
edited, staged, or formatted.

## 1. Were the displayed terminal formulas correct?

**Yes, exactly** — every mass factor, sign, and normalization of the
handoff's pair-{2,3} specialization matches the theorem of
`docs/ESCAPE_CRITERIA.md` with $(a,b,c)=(2,3,1)$.  Status:
`EXACT SYMBOLIC IDENTITY` for the mapping; the underlying theorem was
already `PROVED ANALYTICALLY`.  Clarifications recorded (no corrections):
$E_{23}$ is the specific relative energy (a reduced-mass weight would be
wrong and is rejected by a test); $P$ is exactly $\dot G$; the outer
gravitating mass is the full $\mathcal M$; the tidal allowance carries
the escaper mass $A$; all margins are invariant under $w\mapsto-w$ and
the binary label swap.

## 2. The proved chart-to-escape theorem

Theorem (T) of `docs/FABLE_MIDDLE_ESCAPE.md` §2: strict inequalities
$|w|^2>0$, $\rho>0$, $d>0$, $\dot\rho>0$, $E_\rho>0$,
$-\eta-E_{23}-\Delta>0$ on an interval box imply, for every real
parameter and state in the box, that $\{2,3\}$ stays a bound binary,
body 1 escapes permanently, the only possible future singularity is an
inner $\{2,3\}$ collision, and no later labelled brake exists in either
alternative.

**New mathematics of this run — phase-robust corollary** (§3a): with the
transported $h$ supplied, every $w,z$ condition can be dropped:
$r\le M/(-h)<M/\eta$ holds unconditionally for surviving solutions, and
box states at $w=0$ belong to the tolerated inner-collision alternative.
The terminal certificate therefore needs only $(h,G,P)$, which stay
tight while the inner phase decorrelates.  Proof in
`docs/FABLE_MIDDLE_ESCAPE.md`; status `PROVED ANALYTICALLY` (it is a
two-line consequence of the cited theorem plus the tested transport
identity).

## 3. Tests and reproduction

```sh
python -m pytest tests/test_middle_escape_symbolic.py -q       # 17 passed
sh scripts/fable_run_capd_middle_escape.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-native --demo                  # PASS margin 11.3
PYTHONPATH=. python scripts/probe_middle_escape_endgame.py     # full grid
PYTHONPATH=. python scripts/probe_middle_escape_box_tolerance.py \
  "$TMPDIR"/fable_middle_escape_terminal_capd
```

Key exact tests: LC field $=$ Newton, $h\equiv E_{23}$ transport,
$\ddot G$ mass factors, $jd'$ field, float-implementation agreement to
$10^{-12}$, corrupted-mass-factor rejection, fail-closed degenerate
guards.

## 4. Interval-checker status

`src/fable/verification/middle_escape_terminal_capd.cpp`: **built and
validated** against CAPD 6.1.0 NATIVE (pinned commit).  Pure
outward-rounded arithmetic, exact rational stdin parsing, fails closed
on every guard (all failure paths exercised).  Modes: strict (with
optional $h$ intersection and transport-consistency check),
`--phase-robust`, `--binary13` (mirrored labelling).  Enclosures verified
to contain exact symbolic point values.

## 5. Best chart-switch section

Switch pair-{1,3} $\to$ pair-{2,3} at $t\approx3.55$ (after the fourth
minimum at $3.469$).  **Trap found:** throughout $t\in[3.5,3.7]$ the
family $g_{23}$ lies near the negative real axis, where the committed
Form-A switch map degenerates; a Form-B variant
($w_i=\sqrt{(|g|-g_x)/2}$, $w_r=g_y/(2w_i)$) is required and is
well-conditioned there ($g_x<0$ uniformly across the tile at
$3.55$--$3.60$).

## 6. Best terminal section

Fixed physical time $T=9/2$ (or $T=5$), $\eta=4$, phase-robust mode with
$h$ supplied.  The $t_p=T$ coordinate section is parameter-independent
and unconditionally transversal ($dt_p/d\sigma=|w|^2$).

## 7. Numerical margins at the midpoint (ORDINARY NUMERICAL EVIDENCE)

At $u=0.29$: certificate first fires $t=3.813$; at $t=4$: $d=1.22$,
$\dot\rho=2.24$, $E_\rho=0.58$, inner margin $4.70$; at $t=9/2$:
$d=2.27$, $\dot\rho=1.97$, $E_\rho=0.89$, margin $5.14$; at $t=5$:
$d=3.22$, $\dot\rho=1.85$, $E_\rho=0.96$, margin $5.21$.  Family-hull
wrapping budgets over $[0.29,0.29002]$ (phase-robust): $0.019$ at $T=4$,
$0.102$ at $T=9/2$, $0.169$ at $T=5$.  Strict mode fails the bare family
hull at $T=4$ and $T=5$ (the $w$ hull contains $0$): phase robustness is
necessary, not cosmetic.

## 8. Widest stable interval observed (ORDINARY NUMERICAL EVIDENCE)

Same 7-event labelled itinerary: $[0.2895,0.2903]$ except $u=0.2896$
(deep $\{1,2\}$ passage, separation $\sim1.2\times10^{-3}$).  Same
terminal outcome (pair-{2,3} binary, body 1 escapes): approximately
$(0.2897,0.2902)$, firing times $3.56\to4.34$.  Below: hierarchy flips,
body 2 ejected with binary $\{1,3\}$ (margin $+14.5$ at $0.2895$).
Above $\approx0.2903$: body 1 falls back; more cycles needed.

## 9. Independent full interval certificate

**COMPLETED for a nonempty real interval** (second phase of the run, at
the user's direction): `PASS_MIDDLE_ESCAPE_ENDGAME` proves every real
$u\in[0.29,\,0.29+10^{-11}]$ nonperiodic — full brake-exclusion covering
from the tied launch through $t_\ast\in[4.30022,4.30024]$, through all
four deep binary passages and the $t\approx3.44$–$3.48$ exchange
scattering, terminating in the phase-robust escape certificate with
margin $5.069$, independently cross-checked by the standalone interval
checker.  Statement, proof structure, soundness notes, and the measured
obstruction economics: `docs/FABLE_MIDDLE_INTERVAL_NONPERIODICITY.md`;
driver `src/fable/verification/middle_escape_endgame_capd.cpp`
(`run_endgame_c0`), log
`data/fable/middle_escape_endgame_first_interval.log`.

Architecture findings from the closing campaign (all measured):
the C1 mean-value graph has a du-independent slack floor at deep
passages and cannot reach the terminal leg; the correlated C0 tripleton
with u as a state variable traverses everything, with selected-pair
passages nearly free (LC sigma-time synchronizes the pericenter), and
the exchange scattering as the sole width-limiting obstruction
(transient sensitivity $10^6$–$10^8$ at fixed clock vs $\sim10^3$ at
synchronized sections and $2\times10^4$ after escape).  Unselected-pair
step caps are mandatory: without them, wide-but-exception-free
enclosures of $1/r^3$ silently poison the set.  The full committed tile
$[0.29,0.29002]$ remains open pending the primary's section-based
reconditioning (or $\sim2000$ tiled runs of this driver).

## 10. Reusability on adjacent tiles

Yes inside $(0.2897,0.2902)$ with the identical edge; below via the
mirrored `--binary13` edge; above via longer graphs (same mathematics,
more cycles).  The edge is a triple $(T,\text{labelling},\eta)$ plus the
checker; contract in `docs/FABLE_MIDDLE_ESCAPE.md` §7.

## 11. Files and commits

- `128a459` `src/symbolic/middle_escape.py`,
  `tests/test_middle_escape_symbolic.py`
- `7b13c27` `docs/FABLE_MIDDLE_ESCAPE.md`
- `5b6e695` `src/fable/verification/middle_escape_terminal_capd.cpp`,
  `scripts/fable_run_capd_middle_escape.sh`
- `5d48655` phase-robust corollary + checker mode
- `5827291` `scripts/probe_middle_escape_endgame.py`,
  `scripts/probe_middle_escape_box_tolerance.py`
- `f759cc1` `--binary13` mirrored labelling
- (this commit) `docs/FABLE_TO_MAIN.md` entry, this report

## 12. Single highest-leverage next action

Propagate the primary correlated graph from the fourth minimum through a
**Form-B chart switch at $t\approx3.55$** and a $t_p=9/2$ time section,
keeping $h,G,P$ tight and ignoring inner-phase wrapping, then run

```sh
sh scripts/fable_run_capd_middle_escape.sh <capd-src> <capd-build> \
  --phase-robust < box.txt
```

A PASS closes nonperiodicity for every real $u\in[0.29,0.29002]$ via
Theorem C.  The available wrapping budget beyond the family hull is
$\approx0.10$ in every coordinate — two orders of magnitude looser than
the enclosure widths the existing propagation machinery achieves.
