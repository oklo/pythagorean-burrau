# Pair-{2,3} terminal escape map for the middle interval

This note maps the pair-{2,3} Levi--Civita chart of
`src/fable/verification/burrau_lc_certificate_capd.cpp`
(`make_pair23_lc_field`) onto the terminal binary--escaper theorem of
`docs/ESCAPE_CRITERIA.md`, specialized to binary $\{2,3\}$ with escaper
body $1$.  Every identity below is regression-tested exactly in
`tests/test_middle_escape_symbolic.py` against the implementation
`src/symbolic/middle_escape.py`.

Verdict on the handoff formulas: **all displayed mass factors, signs, and
normalizations are exactly correct.**  No correction was needed.  The
clarifications worth recording are items C1--C4 in §5.

## 1. Chart definitions

Masses $(m_1,m_2,m_3)=(A,B,1)$ with
$A=(1-u^2)/(1+u^2)$, $B=2u/(1+u^2)$.  Write

\[
M=B+1=\frac{(1+u)^2}{1+u^2},\qquad
\mathcal M=A+B+1=\frac{2(1+u)}{1+u^2} .
\]

The chart state is $(w_r,w_i,z_r,z_i,h,G_x,G_y,P_x,P_y,t,u,J)$ with,
identifying $\mathbb R^2\cong\mathbb C$:

* $g=q_3-q_2=w^2$ (complex square), so $r=|g|=|w|^2$;
* fictitious time $\sigma$ with $dt/d\sigma=|w|^2$ and $dw/d\sigma=z$,
  hence $\dot g=2wz/|w|^2$;
* $h=E_{23}=\tfrac12|\dot g|^2-M/r=(2|z|^2-M)/|w|^2$
  (`EXACT SYMBOLIC IDENTITY`, and the chart's $h'$ equation is exactly the
  $\sigma$-derivative of the algebraic form for every external force, so the
  identity is transported by the flow);
* $G=q_1-C_{23}$, $C_{23}=(Bq_2+q_3)/M$, and $P=\dot G$ exactly
  (the chart evolves $dG/d\sigma=|w|^2P$, $dP/d\sigma=|w|^2\ddot G$);
* $\rho=|G|$, $\dot\rho=G\cdot P/\rho$.

The CAPD field's auxiliary identities, all verified symbolically:

* $q_1-q_2=G+g/M$ and $q_1-q_3=G-(B/M)g$ (so the chart needs no absolute
  positions);
* $\ddot g=-Mg/r^3+f$ with $f=A\left(\frac{q_1-q_3}{r_{13}^3}
  -\frac{q_1-q_2}{r_{12}^3}\right)$; the LC equation
  $z'=(h/2)w+(|w|^2/2)\bar wf$ reproduces this Newton equation exactly;
* $\ddot G=-\frac{\mathcal M}{M}\left(B\frac{q_1-q_2}{r_{12}^3}
  +\frac{q_1-q_3}{r_{13}^3}\right)$, the internal $\{2,3\}$ force cancelling
  identically;
* $dJ/d\sigma=|w|^2(2U-4U_0)$ with the $\{2,3\}$ potential term
  regularized by $r_{23}=|w|^2$.

## 2. Specialization of the terminal theorem

The theorem of `docs/ESCAPE_CRITERIA.md` (status `PROVED ANALYTICALLY`)
takes a binary $(m_a,m_b)$ and escaper $m_c$, with inner vector
$x=q_b-q_a$, outer vector $y=q_c-(m_aq_a+m_bq_b)/(m_a+m_b)$, inner
specific energy $e=\tfrac12|\dot x|^2-(m_a+m_b)/|x|$.

Take $(a,b,c)=(2,3,1)$.  Then exactly:

| theorem quantity | chart quantity |
|---|---|
| $x$ | $g=w^2$ |
| $\dot x$ | $\dot g=2wz/|w|^2$ |
| $y$ | $G$ |
| $\dot y$ | $P$ |
| $M=m_a+m_b$ | $B+1$ |
| $\mathcal M$ | $A+B+1$ |
| $m_c$ | $A$ |
| $e$ | $E_{23}=(2|z|^2-M)/|w|^2$ |
| $\rho$, $\dot\rho$ | $|G|$, $G\cdot P/|G|$ |

With $\eta>0$ set $R=M/\eta$, $d=\rho-R$,
$E_\rho=\tfrac12\dot\rho^2-\mathcal M/d$, $v_\infty=\sqrt{2E_\rho}$,
$\Delta=A\sqrt{2MR}/(v_\infty d^2)$.

**Theorem (chart form).**  Let a collision-free pair-{2,3} chart state at
physical time $t_0$ satisfy the strict inequalities

\[
|w|^2>0,\qquad \rho>0,\qquad d>0,\qquad \dot\rho>0,\qquad E_\rho>0,
\qquad -\eta-E_{23}-\Delta>0 .
\tag{T}
\]

Then the future maximal classical solution either ends in a $\{2,3\}$
binary collision, or exists for all $t\ge t_0$ with

\[
E_{23}(t)<-\eta,\qquad r_{23}(t)<R,\qquad \dot\rho(t)\ge v_\infty,
\qquad \rho(t)\ge\rho_0+v_\infty(t-t_0):
\]

bodies $2,3$ remain a bound binary of radius $<R$, body $1$ escapes with
$\rho\to\infty$ at linear rate, and no collision involving body $1$ can
occur ($\rho>R>r$ throughout).  **In either alternative there is no later
labelled brake** (`ESCAPE_CRITERIA.md`, final proof paragraph, plus
Theorem C of `docs/FABLE_EVENT_REDUCTION.md`, whose terminal alternative
cites exactly this certificate).

Proof: this is the cited theorem verbatim under the substitution table
above; the table itself is the content of the exact tests.  Status of the
mapping: `EXACT SYMBOLIC IDENTITY`; status of the theorem:
`PROVED ANALYTICALLY` (already in the ledger).

Uniformity: every inequality in (T) is strict and every map from
$(u,w,z,G,P)$ to the margins is continuous on the domain
$\{|w|^2>0,\ \rho>R,\ \dot\rho>0,\ E_\rho>0\}$; therefore (T) verified by
outward-rounded interval arithmetic over a box of chart states **and** a
parameter interval $u\in[\underline u,\overline u]$ certifies the
conclusion simultaneously for every real state and parameter in the box.
No per-point argument is used anywhere.

## 3. Domain conditions and fail-closed order

An interval verifier must establish, in this order, each from the interval
hull (outward rounded), failing closed if any cannot be proved:

1. $\inf|w|^2>0$ — chart nondegeneracy; needed before $E_{23}$'s
   denominator (a true $w=0$ is a $\{2,3\}$ collision, which the theorem's
   dichotomy tolerates *after* $t_0$ but which must not pollute the
   evaluation *at* $t_0$).
2. $\inf(G_x^2+G_y^2)>0$ — needed before $\rho=\sqrt{\cdot}$ and the
   division in $\dot\rho$.
3. $\inf d>0$ with $d=\rho-M/\eta$ — needed before the division in
   $E_\rho$.
4. $\inf\dot\rho>0$.
5. $\inf E_\rho>0$ — needed before $v_\infty=\sqrt{2E_\rho}$ and the
   division in $\Delta$.
6. $\inf(-\eta-E_{23}-\Delta)>0$.

Square-root arguments: $2MR=2M^2/\eta$ is positive for every
$u\in(0,1)$, $\eta>0$ (no hypothesis needed); $\rho^2$ and $2E_\rho$ are
guarded by conditions 2 and 5.  All divisions are guarded by 1, 2, 3, 5.

$E_{23}$ may be taken either as the transported chart variable $h$ or as
the algebraic form $(2|z|^2-M)/|w|^2$; they are equal along the flow.  A
checker consuming a *propagated* box should intersect the two enclosures
(both are rigorous; the intersection is sharper and detects transport
bugs as an empty intersection).

## 3a. Phase-robust corollary (inner phase not required)

At a fixed terminal physical time the inner-binary phase decorrelates
across a parameter tile much faster than the outer variables: ordinary
numerics at $t=4$ over $u\in[0.29,0.29002]$ show $(w,z)$ family spreads of
order $0.1$--$0.4$ (comparable to $|w|$ itself, so the correlated hull can
even contain $w=0$) while the $(G,P)$ spreads are $10^{-2}$ and the
transported $h$ spread is $\sim0.28$.  The following corollary removes
every $w,z$ condition from the terminal check.

**Corollary (phase-robust terminal box).**  Let a correlated interval box
at physical time $t_0$, produced by rigorous propagation of the pair-{2,3}
chart with the transported energy $h$ and with the outer separations
$r_{12},r_{13}$ verified positive throughout the propagation (the standard
guard of every graph leg, so the only collision a real solution can have
suffered is the regularized inner $\{2,3\}$ one), satisfy the strict
outward-rounded inequalities

\[
\rho>0,\qquad d=\rho-M/\eta>0,\qquad \dot\rho>0,\qquad E_\rho>0,\qquad
-\eta-h-\Delta>0,
\]

using $h$ in place of $E_{23}$ and no condition on $w,z$.  Then for every
real parameter $u$ in the tile: either the classical solution ended in an
inner $\{2,3\}$ collision at some time $\le t_0$, or the full conclusion
of the theorem in §2 holds at $t_0$.  In both alternatives no labelled
brake exists at any collision-free time $\ge$ the covered prefix.

*Proof.*  Fix a real $u$ in the tile.  If the classical solution ended in
a $\{2,3\}$ collision at or before $t_0$, the maximal interval $J_u$ is
contained in the covered prefix and there is nothing more to prove (the
regularized chart continues through $w=0$ in $\sigma$, so the box may
contain such post-collision states; they certify nothing and need not).
Otherwise the solution is collision-free at $t_0$ with $r=|w|^2>0$
pointwise, and its chart values lie in the box.  The transport identity
$h\equiv E_{23}$ (an exact identity of the flow, §1) gives
$e_0=h_0\le\sup h<-\eta-\Delta<-\eta$.  From
$e_0=\tfrac12|\dot g|^2-M/r$ and $\tfrac12|\dot g|^2\ge0$,

\[
r_0=\frac{M}{\tfrac12|\dot g|^2-e_0}\le\frac{M}{-e_0}<\frac M\eta=R,
\]

so $r_0<R$ holds unconditionally — this is the only place the theorem's
hypotheses touch the inner variables at $t_0$, and it needs no lower bound
on $r_0$.  All remaining hypotheses ($d>0$, $\dot\rho>0$, $E_\rho>0$, the
margin (E)) involve only $\rho_0,\dot\rho_0,e_0$ and are certified by the
box.  The theorem in §2 applies verbatim.  $\blacksquare$

Consequences for the interval program: the terminal leg does **not**
require resolving the binary phase.  Only $h$, $G$, $P$ (all slowly
varying) need tight enclosures at the terminal section, so the terminal
box tolerates the phase wrapping that accumulates after the fourth
minimum, and parameter subdivision driven by inner-phase decorrelation is
unnecessary for the terminal check itself.  The checker implements this as
`--phase-robust` (h required, no algebraic intersection, w/z guards
skipped, PASS line marked `PHASE_ROBUST`).

## 4. Collisions and close passages

* The theorem's dichotomy allows one exception: a future **inner**
  $\{2,3\}$ collision.  That alternative still ends the maximal classical
  solution, so no later labelled brake exists in either branch — the
  conclusion needed by Theorem C is unconditional.
* A close positive-separation $\{2,3\}$ passage is **not** a collision:
  as long as the interval box at $t_0$ proves $\inf|w|^2>0$, the
  certificate is being evaluated at a collision-free time and nothing
  else about earlier close passages matters.
* Collisions involving body 1 after $t_0$ are excluded outright by
  $\rho>R>r$ (maintained by the bootstrap), so the earlier legs of the
  orbit need only be collision-free up to $t_0$ — which is exactly what
  the covering certificate of Theorem C establishes window by window.

## 5. Clarifications recorded (no corrections needed)

* **C1.** $E_{23}$ is the **specific** energy of the relative coordinate
  $g$ (per unit reduced mass): $e=\tfrac12|\dot g|^2-M/|g|$.  The
  reduced-mass-weighted energy $\mu_{23}\tfrac12|\dot g|^2-\dots$ would be
  wrong; the tests reject it explicitly.
* **C2.** $P$ is exactly the physical outer relative velocity $\dot G$:
  the chart evolves $G'=|w|^2P$, $P'=|w|^2\ddot G$ with $t'=|w|^2$.
  No mass weighting and no $\sigma$-rescaling residue.
* **C3.** The outer gravitating mass is the full $\mathcal M=A+B+1$,
  because $|\ddot y|\le\mathcal M/(\rho-r)^2$ uses the mass-weighted sum
  of both outer fields, and $\mathcal M/M\cdot(B\cdot 1+1\cdot 1)\cdot
  \max(r_{12},r_{13})^{-2}\le\mathcal M(\rho-r)^{-2}$; verified as the
  exact $\ddot G$ identity in §1.
* **C4.** The tidal allowance carries the **escaper** mass $m_c=A$ (not
  $B$, not $\mathcal M$): it bounds
  $|\dot e|\le 2m_cr|\dot x|/(\rho-r)^3$, a property of the perturbing
  body.  The orientation/labelling of the chart is immaterial: all
  margins are invariant under $w\mapsto-w$ and under the binary label
  swap $g\mapsto-g$ (tested).

## 6. CAPD-ready pseudocode (outward-rounded intervals)

Inputs: intervals `u ⊆ [u_lo,u_hi] ⊂ (0,1)`, chart box
`wr,wi,zr,zi,h,Gx,Gy,Px,Py`, rational `eta > 0`.  All operations in
directed-rounding interval arithmetic; `inf`/`sup` are proved bounds.

```text
q    = 1 + u^2                      # contains no zero on (0,1)
A    = (1 - u^2)/q
M    = (1 + u)^2/q                  # = B + 1
Mtot = 2*(1 + u)/q                  # = A + B + 1
r    = wr^2 + wi^2
REQUIRE inf(r) > 0                          # (1) chart nondegenerate
E23  = (2*(zr^2 + zi^2) - M)/r
if h supplied: E23 = intersect(E23, h); REQUIRE nonempty
rho2 = Gx^2 + Gy^2
REQUIRE inf(rho2) > 0                       # (2)
rho  = sqrt(rho2)
R    = M/eta
d    = rho - R
REQUIRE inf(d) > 0                          # (3)
rdot = (Gx*Px + Gy*Py)/rho
REQUIRE inf(rdot) > 0                       # (4)
Erho = rdot^2/2 - Mtot/d
REQUIRE inf(Erho) > 0                       # (5)
vinf  = sqrt(2*Erho)
Delta = A*sqrt(2*M*R)/(vinf*d^2)            # arg = 2M^2/eta > 0 always
margin = -eta - E23 - Delta
REQUIRE inf(margin) > 0                     # (6)
return PASS with margins (inf d, inf rdot, inf Erho, inf margin)
```

Any REQUIRE failure returns FAIL (fail closed); PASS proves theorem (T)
for **every** real $(u,\text{state})$ in the box.

## 7. Reusable terminal edge contract

The endgame is packaged as a graph edge, not a bespoke proof.  All
statements in this section other than the theorem citations are design
guidance; the numerical values are `ORDINARY NUMERICAL EVIDENCE`.

**Edge definition.**  A terminal edge is the triple
(terminal physical time $T$, labelling, $\eta$) applied to the correlated
interval box that the graph holds at the time section $t=T$.  The time
section is the coordinate section $t_p=T$ on chart coordinate 9 of
`kDirectLcVars`; it is parameter-independent and unconditionally
transversal because $dt_p/d\sigma=|w|^2>0$ on collision-free legs.  The
edge PASSes when `middle_escape_terminal_capd` certifies the box; by
Theorem C of `docs/FABLE_EVENT_REDUCTION.md` a PASS terminates the
nonperiodicity proof for every real parameter in the tile.

**Consumption contract.**  The propagated `kDirectLcVars` state
$(w_r,w_i,z_r,z_i,h,G_x,G_y,P_x,P_y,t_p,u,J)$ maps onto the checker's
stdin as: eta; pairs for indices 10 (u), 0, 1, 2, 3 (w, z), 5, 6, 7, 8
(G, P); optional pair for index 4 (h) — required with `--phase-robust`,
which is the recommended mode.

**Recommended endgame design for the tile $[0.29,0.29002]$:**

1. propagate the pair-{1,3} leg through the fourth minimum
   ($t\approx3.469$, the deepest passage, $r_{13}\approx0.017$ at
   $u=0.29$);
2. switch charts near $t\approx3.55$.  Caution: in the whole window
   $t\in[3.5,3.7]$ the vector $g_{23}$ lies near the **negative real
   axis** (family angles $-112^\circ$ to $-175^\circ$, crossing the cut),
   exactly where the committed Form-A switch map
   (`make_pair13_to_pair23_map`, $w_r=\sqrt{(|g|+g_x)/2}$) degenerates.
   The endgame switch needs the Form-B branch
   $w_i=\sqrt{(|g|-g_x)/2}$, $w_r=g_y/(2w_i)$, valid on $g_x<0$, which
   holds uniformly across the tile at $t=3.55$--$3.60$;
3. propagate the pair-{2,3} leg to the terminal time.  The covering on
   this leg is itself phase-robust: $K$ contains the outer kinetic term
   $\tfrac12\mu_{\text{out}}|P|^2$ whose interval stays positive under
   inner-phase wrapping (the inner contribution to the $K$ hull is a sum
   of squares, never negative), and ordinary numerics show $J=\dot I>0$
   throughout $t\in[3.5,6]$ dominated by the tight outer variables;
4. fire the phase-robust edge at $T=9/2$ or $T=5$ with $\eta=4$.
   Observed uniform wrapping budgets beyond the family hull:
   $0.019$ at $T=4$, $0.102$ at $T=9/2$, $0.169$ at $T=5$ — later
   sections are more tolerant because $d$ grows faster than the spreads.

**Adjacent tiles.**  The identical edge (same $T$, same inequalities)
works on nearby tiles inside $u\in(0.2897,0.2902)$, where the same
7-event itinerary and pair-{2,3}/escaper-1 hierarchy persist (firing
times drift $3.56\to4.34$).  Below $\approx0.2896$ the hierarchy flips:
body 2 is ejected with binary {1,3} (violently at $u=0.2895$: margin
$+14.5$, $\dot\rho\approx5.4$), served by the mirrored edge
(`--binary13`).  Near $u\approx0.2896$ sits a deep $\{1,2\}$ close
passage (separation $\sim10^{-3}$), and above $\approx0.2903$ body 1
falls back ($\dot\rho<0$ by $t=7.5$ at $u=0.2904$) and the endgame needs
at least one more cycle — those tiles need longer graphs, not different
mathematics.

## 8. Reproduction

```sh
python -m pytest tests/test_middle_escape_symbolic.py -q   # 17 exact tests

# Interval checker (CAPD NATIVE build), demo box over u in [0.29, 0.29002]:
sh scripts/fable_run_capd_middle_escape.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-native --demo

# Ordinary endgame reconnaissance and terminal wrapping budgets:
PYTHONPATH=. python scripts/probe_middle_escape_endgame.py
PYTHONPATH=. python scripts/probe_middle_escape_box_tolerance.py \
  "$TMPDIR"/fable_middle_escape_terminal_capd
```

Key tests: `test_lc_field_encodes_newton` (chart = Newton),
`test_hh_transport_matches_algebraic_energy` ($h\equiv E_{23}$),
`test_outer_acceleration_identity` ($\ddot G$ mass factors),
`test_agreement_with_float_implementation` (margins vs
`src/dynamics/escape_certificate.py`),
`test_corrupted_mass_factors_detected` (wrong factors rejected).
