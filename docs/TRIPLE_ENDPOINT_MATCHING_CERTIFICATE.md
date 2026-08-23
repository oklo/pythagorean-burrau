# Finite matching problem for the triple-endpoint coefficient

This note turns the formerly open sign of the global coefficient $A_-$ into a
compact, square boundary-value problem.  It does **not** validate the zero or
its sign.  It identifies exactly what a CAPD/interval-Newton certificate must
enclose and separates the two analytic endpoint attachments from the compact
flow.

## Two regular endpoint charts

Write $psi$ for binary eccentric anomaly, so that

\[
 r=\cos ^2\psi,qquad {dt\over d\psi}=r.
\tag{1}
\]

At incoming parabolic infinity put

\[
 z=-{2\over x^2},qquad x>0,qquad v=\dot z.
\tag{2}
\]

Then the exact incoming base field is

\[
 x_\psi={r x^3v\over4},qquad
 v_\psi={r x^4\over2(1+r^2x^4/16)^{3/2}}.
\tag{3}
\]

It is analytic at $x=0$.  Its incoming parabolic branch has
$v=\sqrt2x+o(x)$ and is parameterized by the canonical phase intercept
$\chi$ of `RESTRICTED_PHASE_WINDOWS.md`.

The returned Jost field has

\[
 p=-\gamma z+\mathscr W_\infty\sqrt{-z}+o(\sqrt{-z}).
\tag{4}
\]

The raw field diverges at $x=0$, but

\[
 P=x^2p,qquad Q={\dot p\over x}
\tag{5}
\]

is regular.  Direct substitution gives

\[
 \begin{split}
 P_\psi&=r\left({x^2vP\over2}+x^3Q\right),\\
 Q_\psi&=-{r\over4}\left[
 x^3{1-r^2x^4/8\over(1+r^2x^4/16)^{5/2}}P+x^2vQ
 \right].
 \end{split}
\tag{6}
\]

In particular,

\[
 P=2\gamma+\sqrt2\mathscr W_\infty x+o(x),qquad
Q=-\sqrt2\gamma-{\mathscr W_\infty\over2}x+o(x).
\tag{7}
\]

The limiting point $(P,Q)=(2\gamma,-\sqrt2\gamma)$ does not by itself retain
$\mathscr W_\infty$; that coefficient is in the first derivative.  For a
validated attachment the safer second fiber variable is the Wronskian

\[
 \Omega=z\dot p-vp=-{2Q+(v/x)P\over x}.
\tag{7a}
\]

It obeys the even simpler exact system

\[
 P_\psi=-{r\over2}x^4\Omega,
 \qquad
 \Omega_\psi=-{3\over32}{r^3x^6P\over
 (1+r^2x^4/16)^{5/2}},
\tag{7b}
\]

with direct boundary values

\[
 (P,\Omega)\longrightarrow(2\gamma,-\mathscr W_\infty).
\tag{7c}
\]

At finite $x$ recover

\[
 p={P\over x^2},\qquad
 \dot p=-{vP+x^2\Omega\over2}.
\tag{7d}
\]

Equations (3), (6), and especially (7b) are analytic polynomial/radical
expressions on a small compact $x$-box.  They avoid propagating a quantity of
order $x^{-2}$ from infinity without losing the scattering Wronskian.

At the triple collision use the exact final-infall chart of
`TRIPLE_COLLISION_ENDPOINT.md`:

\[
 y={z\over r},qquad X=-\log r.
\tag{8}
\]

The admissible base family and canonical transverse modes have
derivative-strengthened asymptotics

\[
 \begin{split}
 y&=-{\sqrt3\over2}+a r^{\nu_+}+o(r^{\nu_+}),
 &ry_r&=a\nu_+r^{\nu_+}+o(r^{\nu_+}),\\
 P_\pm&=r^{\beta_\pm}(1+o(1)),
 &rP_{\pm,r}&=\beta_\pm r^{\beta_\pm}(1+o(1)),
 \end{split}
\tag{9}
\]

where

\[
 \nu_+={-1+\sqrt{19}\over4},qquad
 \beta_\pm={3\pm\sqrt7\over4}.
\tag{10}
\]

The excluded shape mode $r^{(-1-\sqrt{19})/4}$ is precisely the collision-
unstable mode.  Hence $a$ is the only collision-side base parameter.  Both
transverse modes vanish at collision, so their two coefficients must be kept;
the faster one is a nuisance coefficient, not another base parameter.

## A regular common section

Use the lift for which the target collision is at $\psi=3\pi/2$, and choose

\[
 \psi_m={5\pi\over4},qquad r_m={1\over2},qquad \dot r_m=-2.
\tag{11}
\]

This section is separated from triple collision, binary collision, and binary
apocenter.  On the collision side the conversion from $(y,y_r,p,p_r)$ is

\[
 z={y\over2},qquad
 \dot z=-2\left(y+{y_r\over2}\right),qquad
 \dot p=-2p_r=-4(rp_r).
\tag{12}
\]

Let

\[
 U(\chi)=(z_u(\chi),v_u(\chi)),qquad
 C(a)=(z_c(a),v_c(a))
\tag{13}
\]

be the incoming-parabolic and collision-stable base curves on this section.
Let $J(\chi)=(p_J,\dot p_J)$ be the returned Jost state propagated with
$U(\chi)$, and let $P_\pm(a)=(p_\pm,\dot p_\pm)$ be the two canonical
collision modes propagated with $C(a)$.

The full matching residual is

\[
 \mathcal F(\chi,a,A_-,A_+)=
 \begin{pmatrix}
 C(a)-U(\chi)\\
 A_-P_-(a)+A_+P_+(a)-J(\chi)
 \end{pmatrix}\in\mathbb R^4.
\tag{14}
\]

Thus the remaining endpoint connection is a square four-equation problem.
Equivalently, one may first solve the two base equations and then solve the
linear transverse system.  There is no uncounted scale, rotation, or
time-shift variable: the binary clock and the collision lift fix time, while
$\chi$ is the incoming asymptotic phase coordinate.

## Exact determinant reduction

Order the variables as $(\chi,a,A_-,A_+)$.  At a zero of (14), its Jacobian
has block form

\[
 D\mathcal F=
 \begin{pmatrix}
 -U_\chi&C_a&0&0\\
 *&*&P_-&P_+
 \end{pmatrix}.
\tag{15}
\]

For the normalization (9), the physical-time Wronskian is constant and its
collision limit is exact:

\[
 W(P_-,P_+)
 =\lim_{r\downarrow0}
 \left(P_-\dot P_+-\dot P_-P_+\right)
 =-2(\beta_+-\beta_-)=-\sqrt7.
\tag{16}
\]

Consequently

\[
 \det D\mathcal F
 =-\sqrt7\,\det[-U_\chi,C_a].
\tag{17}
\]

The transverse block can never cause degeneracy.  A validated simple match
requires only a nonzero oriented intersection of the two base curves.  Once
the base zero is enclosed,

\[
 \boxed{
 A_-={W(J,P_+)\over-\sqrt7}.}
\tag{18}
\]

This is the scalar sign to enclose.  Equation (18) also avoids the severe
conditioning of solving simultaneously for the fast coefficient $A_+$.

## Certificate architecture

A rigorous certificate can be split into four finite pieces.

1. **Incoming tail.**  At $x=x_0>0$, enclose the parabolic graph selected by
   $v\sim\sqrt2x$, uniformly for a small intercept interval $\chi$.  Attach
   the normalized Jost fiber (7b)--(7c), with joint validated enclosures for
   $\gamma$ and $\mathscr W_\infty$ and explicit tail remainders.  The current
   scattering certificate proves useful strict signs but does not yet output
   all four finite-section remainder bounds required here.
2. **Collision tail.**  At $r=\rho>0$, enclose the one-parameter stable graph
   (9) and both canonical transverse modes, including their derivatives.
   A contraction/parameterization argument for the asymptotically constant
   $X=-\log r$ system supplies explicit remainder radii.
3. **Compact core.**  Propagate both endpoint boxes to $\psi_m=5\pi/4$ with
   interval Taylor integration.  The candidate path from its last large
   negative section crosses one binary apocenter but no binary collision;
   the vector field is regular on the entire compact core.  The collision
   half remains in the exact cone of (9o) once $a<0$ is enclosed.
4. **Interval Newton.**  Apply a two-dimensional interval Newton or Krawczyk
   operator to $C(a)-U(\chi)$, prove existence and uniqueness in the candidate
   box, and enclose $\det[-U_\chi,C_a]$ away from zero.  Then evaluate (18)
   with the same validated orbit and prove $A_->0$.

Only the first two pieces concern infinite or singular endpoints.  Every
other operation is on one compact regular arc.  A proof of $A_->0$ by this
certificate would still leave the separate finite-$\varepsilon$ selection
theorem; it would not by itself prove the full Pythagorean--Burrau conjecture.

## Ordinary target localization

`scripts/probe_triple_stable_match.py` implements an unvalidated precursor.
It starts the collision family at finite $X$, replaces the exact incoming
parabolic graph by frozen zero-energy data at $z=-K$, and uses finite-cutoff
estimates of $(\gamma,\mathscr W_\infty)$.  At $K=20$, $X=24$ it gives

\[
 a\approx-0.24695456,\qquad \widehat A_-\approx0.31103.
\tag{19}
\]

At the same cutoff, linearity of the field gives the diagnostic decomposition

\[
\widehat A_-\approx0.35064\,\gamma+0.69626\,\mathscr W_\infty.
\tag{20}
\]

Both transfer coefficients are positive, and the certified input sizes
$|\gamma|<1/100$, $11/25<\mathscr W_\infty<9/20$ leave a large sign margin if
coarse validated bounds preserve (20). This observation does not replace
such bounds: (20) still uses a frozen finite-cutoff base and field.
The scalar frozen-section residual has derivative about $-20.26$ with respect
to $a$ at this root, giving a well-conditioned numerical target for the base
transversality enclosure. It is not the exact determinant in (17).

Changing the local cutoff from $X=20$ to $24$ changes the displayed
$\widehat A_-$ by less than $2\times10^{-8}$; changing the outer cutoff from
$K=20$ to $40$ moves it to about $0.3091$, consistent with the known slow
outer-tail convergence.  The independent forward finite-gap projector gives
values near $0.312$--$0.318$.  These computations localize the validation box
and strongly support $a<0$, $A_->0$, but are only **ORDINARY NUMERICAL
EVIDENCE**.

Reproduce the backward diagnostic with

~~~bash
uv run python -m scripts.probe_triple_stable_match \
  --cutoff 20 --x-start 24 --match-radius 0.2 \
  --amplitude-bracket -0.25 -0.245 --phase-span 3000 --max-step 0.04
~~~

The exact identities (3), (6), (7b), and (16)--(18) are generated or regression-
tested in `src/symbolic/restricted_scattering.py`.

**Status:** equations (1)--(18) and the dimension/determinant reduction are
**EXACT SYMBOLIC IDENTITY** or **PROVED ANALYTICALLY**.  The backward numerical
box (19)--(20) remains **ORDINARY NUMERICAL EVIDENCE**.  A separate topological
escape/return bracket, analytic collision attachment, compact CAPD propagation,
and exact Wronskian projection now prove $A_->0$ uniformly over every possible
parabolic match in the bracket; see
`COMPUTER_ASSISTED_TRIPLE_ENDPOINT_GLOBAL.md`.  Thus interval Newton and
uniqueness of the base match are no longer proof obligations for the sign.
