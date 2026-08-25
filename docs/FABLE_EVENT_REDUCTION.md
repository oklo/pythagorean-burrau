# Global brake-event reduction

This note proves the exact event-reduction theorems of the Fable route
(`FABLE_ROUTE_DECISION.md`).  Everything is stated for the normalized tied
family of `CONJECTURE.md`: masses $(A,B,1)$, energy $H=-U_0$ with
$U_0=AB+(AB)^{-1}$, zero linear and angular momentum, and the maximal
collision-free classical solution issued from the tied right triangle.
Except where noted, statements hold for every real parameter in the
fundamental interval and require no genericity.

Throughout, $q_i(t)$ is the center-of-mass-frame solution,
$X=q_2-q_1$, $Y=q_3-(m_1q_1+m_2q_2)/(m_1+m_2)$ the unweighted Jacobi
vectors, $\mu_1=m_1m_2/(m_1+m_2)$, $\mu_2=m_3(m_1+m_2)/M$ the reduced
masses, and $\mathbb R^2\cong\mathbb C$.  Standard Jacobi identities give

\[
 I=\sum_im_i|q_i|^2=\mu_1|X|^2+\mu_2|Y|^2,
 \qquad
 K={\mu_1|\dot X|^2+\mu_2|\dot Y|^2\over2},
 \qquad
 L=\operatorname{Im}\!\left(\mu_1\overline X\dot X+\mu_2\overline Y\dot Y\right).
\]

Define the two brake scalars

\[
 \sigma=\mu_1\overline X\dot X+\mu_2\overline Y\dot Y,
 \qquad
 \zeta=\mu_1\overline X\dot X-\mu_2\overline Y\dot Y .
\]

Then $\operatorname{Re}\sigma=\dot I/2$ and $\operatorname{Im}\sigma=L=0$
identically along the tied family, so $\sigma=\dot I/2$ is real.

## Lemma 1 (complex splitting)

*At any collision-free time with $Y\ne0$ (and automatically $X\ne0$), the
following are equivalent:*

1. every labelled inertial velocity vanishes (a labelled brake);
2. $\dot X=\dot Y=0$;
3. $\dot I=0$ and $\zeta=0$.

**Proof.**  (1)$\Leftrightarrow$(2) because the center-of-mass velocity is
zero and $(X,Y)\mapsto(q_1,q_2,q_3)$ is a linear isomorphism on the
center-of-mass subspace.  (2)$\Rightarrow$(3) is immediate.  For
(3)$\Rightarrow$(2): $\sigma=\dot I/2+iL=0$ and $\zeta=0$ give
$2\mu_1\overline X\dot X=\sigma+\zeta=0$ and
$2\mu_2\overline Y\dot Y=\sigma-\zeta=0$; since $\overline X\ne0\ne\overline Y$
and $\mu_1,\mu_2>0$, both velocities vanish.  $\blacksquare$

The determinant of the linear system $\{\dot I=0,\zeta=0,L=0\}$ in
$(\dot X,\dot Y)$ equals $4\mu_1^2\mu_2^2|X|^2|Y|^2$ (symbolically verified
in `tests/fable/test_event_reduction.py`), which restates the lemma and
shows exactly how the chart degenerates as $Y\to0$.  On the locus $Y=0$ the
three-component Hopf residual $\mathcal B$ of `CONJECTURE.md` remains a
complete brake residual (checkpoint interface lemma, verified there to hold
at syzygy and for $Y=0$); no statement below relies on the $\zeta$ chart at
$Y=0$.

The trivial direction — *a brake forces $\dot I=0$, $K=0$, $\zeta=0$, and
$\mathcal B=0$ simultaneously* — holds with no hypotheses at all, because
every scalar is a polynomial in the velocities with no constant term.  The
soundness of the exclusion certificate (Theorem C) uses only this direction.

## Lemma 1a (exact shape-speed factorization at an event)

Put

\[
 J_X=\mu_1|X|^2,\qquad J_Y=\mu_2|Y|^2,\qquad
 s={J_X\over I},\qquad \phi=\arg Y-\arg X.
\]

At every collision-free zero of $\dot I$ with $X,Y\ne0$ and $L=0$,

\[
 \boxed{\ \zeta=I\left(\dot s-2i,s(1-s)\dot\phi\right),\qquad
 |\zeta|^2=8KI\,s(1-s)={8KJ_XJ_Y\over I}.\ }
\]

**Proof.**  At such an event $\sigma=0$, hence
$\zeta=2\mu_1\overline X\dot X=-2\mu_2\overline Y\dot Y$.
Therefore $\operatorname{Re}\zeta=\dot J_X=I\dot s$ and
$\operatorname{Im}\zeta=2h_X$, where
$h_X=\mu_1X\times\dot X$ and $h_Y=-h_X$ by $L=0$.  Since
\[
 \dot\phi={h_Y\over J_Y}-{h_X\over J_X}
 =-{Ih_X\over J_XJ_Y},
\]
the first formula follows.  Radial--angular decomposition of the Jacobi
kinetic energy gives, with $d=\dot J_X=-\dot J_Y$ and $h=h_X=-h_Y$,
\[
 K={d^2\over8}\left({1\over J_X}+{1\over J_Y}\right)
   +{h^2\over2}\left({1\over J_X}+{1\over J_Y}\right)
   ={I(d^2+4h^2)\over8J_XJ_Y}.
\]
Here $d^2+4h^2=|\zeta|^2$.  $\blacksquare$

Thus, on a regular maximum branch away from a Jacobi degeneracy, the planar
origin-avoidance condition is equivalently the scalar strict inequality
$K=U-U_0>0$.  This is useful for validated enclosures but is not a sign
obstruction: $K\ge0$ identically, and a genuine brake is a quadratic (or
higher even-order) zero along a transverse one-parameter branch.

## Lemma 2 (Lagrange--Jacobi on the tied shell)

Along every collision-free arc of a tied solution,

\[
 \ddot I=4K-2U=4H+2U=2U-4U_0 .
\]

**Proof.**  $\dot I=2\sum_im_iq_i\cdot\dot q_i$, so
$\ddot I=2\sum_im_i|\dot q_i|^2+2\sum_iq_i\cdot m_i\ddot q_i
=4K+2\sum_iq_i\cdot F_i$ where $F_i$ is the Newton force.  Euler's theorem
for the degree $-1$ homogeneous potential gives $\sum_iq_i\cdot F_i=-U$.
Energy conservation $K-U=H=-U_0$ eliminates $K$.  The identity
$\ddot I=4K-2U$ is symbolically verified against the implementation in
`tests/fable/test_event_reduction.py`.  $\blacksquare$

## Theorem A (brake events)

*Suppose $\mathcal B(u,\tau)=0$ at a collision-free $\tau>0$.  Then*

1. $K(\tau)=0$ *and* $U(\tau)=U_0$;
2. $\dot I(\tau)=0$ *and* $\ddot I(\tau)=-2U_0<0$: *the brake is a strict
   local maximum of $I$;*
3. *every pair separation satisfies* $r_{ij}(\tau)\ge m_im_j/U_0$;
4. *the solution is even about $\tau$, so $2\tau$ is a labelled period
   (checkpoint second-brake lemma).*

**Proof.**  The checkpoint Hopf lemma converts $\mathcal B=0$ (with $L=0$)
into a labelled brake, so $K=0$ and $U=K+U_0=U_0$.  Lemma 2 gives
$\ddot I=2U_0-4U_0<0$.  Since every potential term is positive,
$m_im_j/r_{ij}\le U=U_0$.  $\blacksquare$

Consequently, for each fixed $u$, the brake locus never approaches a
collision: candidate events obey the explicit bounds
$r_{ij}\ge m_im_j/U_0$.  The bounds are uniform on compact parameter
intervals bounded away from $u=0$, but degenerate in the skinny limit as a
mass and its associated length tend to zero.  This is what makes interval
enclosures at events well conditioned for a fixed compact-middle parameter,
even when its orbit has deep intermediate encounters.

## Theorem B (structure of the event set)

*Let $J_u\subset(0,\infty)$ be the maximal collision-free interval.  Then:*

1. *(isolated events)* $t\mapsto\dot I(u,t)$ is real analytic on $J_u$ and
   not identically zero; its zeros are isolated with no accumulation inside
   $J_u$;
2. *(dichotomy with uniform margin)* at every zero of $\dot I$, either
   $\ddot I<0$ (a strict local maximum of $I$, with $U<2U_0$ and
   $r_{ij}>m_im_j/(2U_0)$ for all pairs), or $\ddot I\ge0$, in which case
   $K=U-U_0\ge U_0>0$ and the event has a parameter-uniform kinetic margin;
   only the first kind can be a brake;
3. *(regular branches)* near any event with $\ddot I\ne0$, the set
   $\{\dot I=0\}$ in the $(u,t)$ strip is a real-analytic graph
   $t=t_k(u)$; on maximum branches the conjecture is exactly the statement
   that the planar analytic curve $u\mapsto\zeta(u,t_k(u))$ avoids
   $0\in\mathbb C$ (through points with $Y\neq0$; else the statement uses
   $\mathcal B\neq0$);
4. *(degenerate events)* events with $\dot I=\ddot I=0$ lie on the locus
   $U=2U_0$, where $K=U_0$; a full neighborhood of such an event in the
   $(u,t)$ strip is brake-free, with explicit margin $K\ge U_0/2$ on the
   neighborhood where $U\ge{3\over2}U_0$;
5. *(quantitative splitting)* at every zero of $\dot I$,
   \[
    |\zeta|^2=2\left(\mu_1^2|X|^2|\dot X|^2+\mu_2^2|Y|^2|\dot Y|^2\right)
    \ \ge\ 4K\min\{\mu_1|X|^2,\ \mu_2|Y|^2\},
   \]
   *so the $\zeta$ margin controls, and is controlled by, the kinetic
   margin and the local geometry.  When $X,Y\ne0$, Lemma 1a gives the
   stronger exact equality $|\zeta|^2=8KJ_XJ_Y/I$.*

**Proof.**  (1) Solutions of the Newton equations are real analytic in time
on collision-free intervals, and analytic in the parameter jointly, by
Cauchy--Kovalevskaya applied to the polynomial extended system with
$1/r_{ij}$ adjoined as dependent variables; $\dot I$ is a polynomial in the
state.  If $\dot I$ vanished identically on a subinterval, analyticity would
propagate $\dot I\equiv0$ to all of $J_u\cup\{0\}$, contradicting
$\ddot I(0)=-2U_0\ne0$.

(2) By Lemma 2, $\ddot I<0\iff U<2U_0$ and $\ddot I\ge0\iff U\ge2U_0$;
in the second case $K=U+H=U-U_0\ge U_0$.  A brake has $K=0$.
The separation bound follows term by term as in Theorem A.

(3) The implicit function theorem in the analytic category applies to
$\dot I(u,t)=0$ because $\partial_t\dot I=\ddot I\ne0$.  Lemma 1 converts
the residual on the branch.

(4) At $\dot I=\ddot I=0$, Lemma 2 forces $U=2U_0$, hence $K=U_0$.
$K$ is continuous, so $K\ge U_0/2$ on the neighborhood
$\{U\ge{3\over2}U_0\}$, which is open and contains the event.

(5) With $\sigma=\dot I/2=0$,
$|\zeta|^2+|\sigma|^2=2(|\mu_1\overline X\dot X|^2+|\mu_2\overline Y\dot Y|^2)$
by the parallelogram law, and
$\mu_1^2|X|^2|\dot X|^2\ge\min\{\mu_1|X|^2,\mu_2|Y|^2\}\,\mu_1|\dot X|^2$
(and similarly for $Y$) gives the bound with
$2(\mu_1|\dot X|^2+\mu_2|\dot Y|^2)=4K$.  $\blacksquare$

## Theorem C (covering-certificate soundness)

*Fix a parameter set $\mathcal U\subset(0,\sqrt2-1]$ and for each
$u\in\mathcal U$ let $J_u$ be the maximal collision-free interval.  Suppose
a computation establishes, with rigorously verified strict inequalities
holding for every $u\in\mathcal U$:*

1. *a finite partition $0=t_0<t_1<\dots<t_N$ and, on each window
   $[t_{j-1},t_j]\cap J_u$, at least one of:*
   *(i)* $\dot I\ne0$ *throughout;*
   *(ii)* $K>0$ *throughout;*
   *(iii)* $|\mathcal B|>0$ *throughout;*
2. *and a terminal alternative at $t_N$: either $J_u\subset(0,t_N)$ (the
   classical solution ends in a collision before $t_N$), or the state at
   $t_N$ satisfies the strict hypotheses of the terminal binary--escaper
   certificate of `ESCAPE_CRITERIA.md` for some labelling.*

*Then no $u\in\mathcal U$ admits a second labelled brake at any
collision-free time, i.e. the conjecture holds on $\mathcal U$.*

**Proof.**  Suppose $\mathcal B(u,\tau)=0$ with $\tau\in J_u$, $\tau>0$.
If $\tau\le t_N$, then $\tau$ lies in some window, and a brake forces
$\dot I(\tau)=0$, $K(\tau)=0$, $\mathcal B(\tau)=0$ simultaneously (trivial
direction of Lemma 1), contradicting whichever of (i)--(iii) was verified.
If $\tau>t_N$, then $J_u\not\subset(0,t_N)$, so the terminal certificate
holds at $t_N$; its conclusion (checkpoint interface theorem, both
dichotomy branches) excludes any later classical brake.  $\blacksquare$

Soundness uses only the trivial direction of the splitting, so no chart
hypothesis ($Y\ne0$) is needed anywhere in Theorem C.

### Corollary C1 (fiberwise LC covers, including the launch window)

The conclusion of Theorem C is unchanged if the common partition is replaced
by a rigorously verified finite fiberwise cover: for every
$u\in\mathcal U$ there are consecutive times

\[
 0=s_0(u)\le s_1(u)\le\cdots\le s_N(u)=t_*(u)
\]

such that the complete classical arc over every
$[s_{j-1}(u),s_j(u)]\cap J_u$ is contained in a verified enclosure on which
at least one of the following holds:

1. $\dot I\ne0$ throughout;
2. $K>0$ throughout;
3. $U>U_0$ throughout;
4. in a selected-pair Levi--Civita chart with $|w|^2>0$ and both
   unselected separations positive, at least one component of $(z,P)$
   excludes zero throughout;
5. for an initial window beginning at the exact tied brake $t=0$,
   $U<2U_0$ throughout.

The state at its own terminal time $t_*(u)$ must satisfy the same terminal
alternative as Theorem C.  The enclosures and terminal times need not lie on
common physical-time sections.

**Proof.**  Fix $u$ and a hypothetical second brake time $\tau$.  If
$\tau\le t_*(u)$, consecutiveness of the fiberwise arcs puts $\tau$ in at
least one verified enclosure.  A brake forces $\dot I=K=0$ and, on the
tied energy shell, $U=U_0$, contradicting alternatives 1--3.  In the LC
chart $\dot g=2wz/|w|^2$ and the complementary physical velocity is $P$;
positive selected radius makes the coordinate reconstruction regular, so a
brake forces $z=P=0$, contradicting alternative 4.  On alternative 5 the
Lagrange--Jacobi identity gives $\ddot I=2U-4U_0<0$.  Since
$\dot I(0)=0$ exactly, $\dot I$ is strictly negative on the open launch
window, excluding every second brake there.
If $\tau>t_*(u)$, the terminal alternative gives the same contradiction as
Theorem C.  This pointwise argument is uniform because every containment and
strict inequality was verified simultaneously over $\mathcal U$.
$\blacksquare$

This is the form used when a regularized integrator advances all parameters
by a common fictitious-time step.  The physical-time coordinate can then
have parameter-dependent endpoints.  Positivity of the selected radius on
the complete step enclosure makes physical time strictly increasing on every
surviving classical fiber, and the union of consecutive accepted-step
enclosures supplies exactly the cover above.

## Remarks on scope

* Theorems A--C hold for every real parameter in the fundamental interval;
  nothing restricts them to rationals.
* Theorem B organizes the local topology: regular brake candidates form
  analytic maximum branches, while degenerate events carry a uniform kinetic
  margin, and the
  event set obeys explicit collision-separation bounds (uniform on parameter
  compacts bounded away from $u=0$).  A finite uniform time cover would reduce
  the conjecture on its parameter box to finitely many certified
  origin-avoidance checks plus a terminal escape/collision alternative.  The
  event theorem alone supplies neither that cover nor global finiteness of
  branches.
* The reduction is exact and parameter-uniform, but it does not by itself
  bound $N$ or the integration time; those bounds are supplied per compact
  parameter set by the terminal certificate actually firing, which is a
  computational fact to be established case by case (first target:
  $u=1/3$).

Status: Lemmas 1--2, Theorems A--C, and Corollary C1 are **PROVED
ANALYTICALLY** (with the
two symbolic identities regression-tested); the checkpoint interface lemmas
used are the Hopf-residual equivalence, the second-brake lemma, and the
terminal escape certificate, each cited with hypotheses verified.
