# Fixed-energy reconditioning at Levi--Civita chart switches

Date: 2026-08-26

## Purpose and status

The directional C2 graph remains sharp until the consecutive pair--23 and
pair--13 close passages.  A short pair--23 chart sandwich regularizes the
first passage, but the reverse static chart map turns a
$4.28\times10^{-7}$ input hull into a $4.78\times10^{-6}$ output hull.  The
genuine tied fibers occupy the exact energy leaf, whereas the ambient defect
box does not.  Direct velocity reconstruction of the target selected-pair
energy loses this correlation.

This note derives a smooth invariant reconstruction and proves that it may be
used as a rigorous graph reconditioning map.  The identities and enclosure
lemma are **PROVED ANALYTICALLY**.  Their symbolic regressions are **EXACT
SYMBOLIC IDENTITY**.  The opt-in CAPD implementation remains
**CONJECTURAL** as an enclosure improvement until a complete pinned replay.

## Jacobi energy identity

Take a selected pair with masses $m_i,m_j$, pair mass $M=m_i+m_j$, and
third mass $m_k$.  Put

\[
 g=q_j-q_i,
 \qquad
 C={m_iq_i+m_jq_j\over M},
 \qquad
 G=q_k-C.
\]

Let

\[
 \mu={m_im_j\over M},
 \qquad
 \mu_G={m_kM\over m_i+m_j+m_k}.
\]

Subtracting the center-of-mass velocity gives the exact orthogonal kinetic
decomposition

\[
 K={\mu\over2}|\dot g|^2+{\mu_G\over2}|\dot G|^2.
\]

Define the selected-pair specific energy coordinate used by the LC field,

\[
 h={|\dot g|^2\over2}-{M\over|g|}.
\]

Since $\mu M=m_im_j$, the selected kinetic and potential terms combine to
$\mu h$.  If $r_{ik},r_{jk}$ are the two unselected distances, the total
energy is therefore

\[
 H=\mu h+{\mu_G\over2}|\dot G|^2
   -{m_im_k\over r_{ik}}-{m_jm_k\over r_{jk}}.
\]

Solving for $h$ gives the nonsingular reconstruction

\[
 \boxed{
 h_E={H-\frac{\mu_G}{2}|\dot G|^2
        +\frac{m_im_k}{r_{ik}}+\frac{m_jm_k}{r_{jk}}
      \over\mu}.}
\]

It has no division by the selected distance $|g|$.  Its domain requires
positive masses and positive *unselected* distances.  In particular, it
extends smoothly to a selected binary collision so long as the third body
does not collide simultaneously.

**Status: PROVED ANALYTICALLY.**  The kinetic identity follows either by
direct expansion after subtracting the total center-of-mass velocity or from
the standard two-stage Jacobi transformation.  Substitution proves the
displayed energy identity and reconstruction.

## Pythagorean pair--13 and pair--23 formulas

For normalized masses $(A,B,1)$ and tied energy

\[
 H=-U_0(u),\qquad U_0=AB+{1\over AB},
\]

the pair--13 chart has

\[
 \mu_{13}={A\over A+1},
 \qquad
 \mu_{G,13}={B(A+1)\over A+B+1},
\]

and hence

\[
 \boxed{
 h_{13,E}=
 {-U_0-\frac{\mu_{G,13}}2|P_{13}|^2
       +\frac{AB}{r_{12}}+\frac{B}{r_{23}}
  \over\mu_{13}}.}
\]

The pair--23 chart has

\[
 \mu_{23}={B\over B+1},
 \qquad
 \mu_{G,23}={A(B+1)\over A+B+1},
\]

and

\[
 \boxed{
 h_{23,E}=
 {-U_0-\frac{\mu_{G,23}}2|P_{23}|^2
       +\frac{AB}{r_{12}}+\frac{A}{r_{13}}
  \over\mu_{23}}.}
\]

Here $P$ is the outer Jacobi velocity stored in coordinates 7 and 8 of the
direct LC state.  At a pair--23 to pair--13 switch, the implementation uses
$r_{23}=|w_{23}|^2$ and reconstructs $r_{12}$ from the old pair--23 Jacobi
variables.  At the reverse switch it uses $r_{13}=|w_{13}|^2$ and
$r_{12}=|X_{13}|$.  Thus neither formula reintroduces a target-pair small
denominator.

The exact tests in `tests/test_middle_escape_endgame_maps.py` independently
compute the physical center-of-mass energy on arbitrary rational states and
prove that both formulas equal
$|\dot g|^2/2-M/|g|$.  A separate exact test proves
$H=-U_0(u)$ for the normalized tied brake family.

## Fiberwise invariant-projection lemma

Let $D$ be a parameter interval and let $x(u)$ be the genuine tied graph at a
chart-switch section.  Let $X$ be any ambient box or C2 graph enclosure with

\[
 x(u)\in X\qquad(u\in D).
\]

Assume every genuine fiber has total energy $H(u)=-U_0(u)$.  Let $F$ be the
ordinary exact chart transformation, and define $F_E$ by keeping every output
coordinate of $F$ except `h`, which is replaced by the appropriate formula
above evaluated from the output physical Jacobi data and the input parameter
$u$.

Then

\[
 \boxed{F(x(u))=F_E(x(u))\quad\hbox{for every }u\in D.}
\]

Consequently any rigorous enclosure of $F_E(X)$ contains every genuine chart
image $F(x(u))$, even though $F_E$ may move spurious off-energy points of
$X$.  No invertibility of $F_E$ on the ambient box is required.

**Status: PROVED ANALYTICALLY.**  Energy conservation and the Jacobi identity
give equality of the replaced coordinate on every genuine fiber; all other
coordinates agree by definition.  Set inclusion then gives
$F(x(u))=F_E(x(u))\in F_E(X)$.

This is a projection only in the validated-set representation.  It does not
alter the Newtonian trajectory.  Starting the target LC field with the
reconstructed `h` reproduces the same regularized equations on every genuine
fiber.  Spurious projected points merely enlarge the auxiliary enclosure.

### Same-chart corollary

The lemma does not require a change of Jacobi tree.  On any collision-free
pair--13 section define $R_{13,E}$ to leave
$(w,z,G,P,t,u,J)$ fixed and replace only `h` by $h_{13,E}$.  In the direct
chart,

\[
 g_{13}=w^2,\qquad
 q_2-q_1=G+{g_{13}\over A+1},\qquad
 q_2-q_3=G+\left({1\over A+1}-1\right)g_{13},
\]

so both required unselected radii are explicit and no division by
$|g_{13}|$ occurs.  Every genuine tied fiber satisfies

\[
 R_{13,E}(x(u))=x(u).
\]

Therefore a rigorous C1 or C2 enclosure of $R_{13,E}(X)$ is a valid
reconditioning of any ambient section graph $X$.  The same statement holds
with labels 13 and 23 exchanged.  This is exactly the invariant-projection
lemma with the ordinary map $F$ equal to the identity.

**Status: PROVED ANALYTICALLY.**  The displayed distance reconstruction is
the defining pair--13 Jacobi transformation.  The fixed-fiber conclusion is
the energy identity above.  Exact rational tests independently reconstruct
both distances and the velocity-defined pair energy.

## Joint angular-momentum and dilatational reconditioning

The energy leaf is not the only exact constraint available in the direct
pair--13 chart.  Put

\[
 \mu_{13}={A\over A+1},\qquad
 \mu_G={B(A+1)\over A+B+1},\qquad
 g=q_3-q_1=w^2,
\]

and let $G=q_2-C_{13}$ and $P=\dot G$.  The translation-reduced angular
momentum is

\[
 L=2\mu_{13}\operatorname{Im}(\overline w z)+\mu_G,G\mathbin\times P.
\]

For $G\ne0$, define

\[
 K=-{2\mu_{13}\over\mu_G}\operatorname{Im}(\overline w z),\qquad
 JG=(-G_y,G_x),
\]

and

\[
 \boxed{
 P^*=P+{K-G\mathbin\times P\over |G|^2},JG.}
\]

Then $G\times P^*=K$ and $G\cdot P^*=G\cdot P$.  Thus $P^*$ lies on the
zero-angular-momentum leaf, while every point already on that leaf is fixed.
The coordinate-free formula avoids choosing between $G_x$ and $G_y$; its
only domain obligation is a strict lower bound for $|G|^2$.

There is also an exact reconstruction of the auxiliary dilatational
coordinate.  Since

\[
 I=\mu_{13}|g|^2+\mu_G|G|^2,
 \qquad
 g\cdot\dot g=2\operatorname{Re}(\overline w z),
\]

one has

\[
 \boxed{
 j_d=\dot I=
 4\mu_{13}\operatorname{Re}(\overline w z)+2\mu_G G\cdot P.}
\]

Consequently the composition

1. $P\mapsto P^*$;
2. reconstruction of `h` from $H=-U_0(u)$ using $P^*$;
3. reconstruction of `jd` from the last display,

fixes every genuine tied fiber and maps spurious enclosure points onto all
three exact identities.  The fiberwise invariant-projection lemma therefore
applies to the composition and to repeated uses of it.  No square root or
selected-pair distance divisor is introduced.

**Status: EXACT SYMBOLIC IDENTITY.**  Independent exact tests verify the two
Levi--Civita factors, enforcement and fixed-point behavior of the angular
projection, preservation of $G\cdot P$, and the $\dot I$ reconstruction.
The joint map has not yet been benchmarked or used in a certificate.  A
computer-assisted use must certify $|G|^2>0$, evaluate its complete C2 image,
and retain every tube, separation, brake, and transversality audit below.

## Domain and tube obligations

For a computer-assisted use of the lemma, every following item remains
mandatory.

1. CAPD must evaluate $F_E$, its first derivative, and its directional second
   derivative on a box where both unselected distances have positive lower
   bounds and all reduced masses are positive.
2. The square-root lift sheet must have its own strict interval margin.
3. The graph transformation must retain the conserved parameter coordinate
   $u$ exactly and use the proved C2 Taylor enclosure.
4. Every later Poincare leg must retain the independent C0 tube audit.  The
   projection lemma proves inclusion of genuine fibers; it does not replace
   collision, transversality, or brake-exclusion checks.
5. A classical collision claim is unchanged.  LC coordinates are an analytic
   device; a true selected collision still terminates the classical solution.

On $0<u<1$, $A,B,\mu_{13},\mu_{23}$ are positive.  The current switch-state
and swept-tube checks certify all three mutual distances, so the experimental
middle route supplies the remaining domain hypotheses.

## Implementation and reproduction

The opt-in flag is

```text
FABLE_ENDGAME_GRAPH_FIXED_ENERGY_H=1
```

It affects only the experimental Form-B pair--13 to pair--23 switches and the
experimental pair--23 to pair--13 return.  The established default itinerary
continues to use velocity reconstruction.

The same-chart experimental flag is

```text
FABLE_ENDGAME_GRAPH_EXCHANGE_ENERGY_PROJECT=1
```

It requires `FABLE_ENDGAME_GRAPH_EXCHANGE_SYNC=1` and applies $R_{13,E}$
after exchange sections 4--6.  It does not alter the default route.  Each
application is followed by the same full graph-domain, separation, and
$J<0$ checks used at chart switches.

The stronger joint-invariant experimental flag is

```text
FABLE_ENDGAME_GRAPH_EXCHANGE_INVARIANT_PROJECT=1
```

It is mutually exclusive with the energy-only flag, requires exchange
synchronization, and composes the zero-angular-momentum, fixed-energy, and
`jd` reconstructions above after sections 4--6.  Before each C2 map
evaluation the driver requires the complete graph enclosure to have
$|G|^2>0$; afterward it repeats the ordinary chart-domain, three-separation,
and $J<0$ checks.  This route is experimental until a complete pinned replay
passes.

Exact tests:

```sh
.venv/bin/pytest -q -p no:cacheprovider \
  tests/test_middle_escape_endgame_maps.py
```

The first validated benchmark should combine

```text
FABLE_ENDGAME_GRAPH=1
FABLE_ENDGAME_GRAPH_C2=1
FABLE_ENDGAME_GRAPH_PAIR23_SYNC=1
FABLE_ENDGAME_GRAPH_FIXED_ENERGY_H=1
FABLE_ENDGAME_GRAPH_EXCHANGE_SYNC=1
FABLE_ENDGAME_GRAPH_EXCHANGE_ENERGY_PROJECT=1
```

on the already-proved width-$10^{-12}$ control.  A local hull reduction is an
engineering result only.  A new nonperiodicity theorem requires the complete
brake/collision tube audit and terminal escape inequalities on a new closed
parameter interval.
