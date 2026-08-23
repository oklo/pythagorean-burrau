# Persistence of the planar collision boundary at positive light mass

The validated collision of `COMPUTER_ASSISTED_PLANAR_LIGHT_COLLISION_ROOT.md`
belongs to the massless projective limit.  This note proves the precise
finite-mass conclusion that follows from its transversality.  The collision
persists as a codimension-one boundary in a local constrained incoming-section
state family.  This does **not** prove that the one-dimensional tied
Pythagorean curve meets that boundary.  The separate differentiated
inclination theorem in `DIFFERENTIATED_JOINT_INCLINATION.md` now transports
this graph through the preceding long saddle dwell in normalized projective
coordinates, but it does not determine the tied curve's signed gap.

## Exact selected-pair equation

Use the late Jacobi equations of `FINITE_B_TRIPLE_ENDPOINT.md`, with

\[
 A=\sqrt{1-B^2},\qquad M=1+A,
\]

\[
 R_{\theta\theta}=-M\Phi(R)
 +B\left[\Phi\left(Z-{A\over M}R\right)
          -\Phi\left(Z+{1\over M}R\right)\right],
\tag{1}
\]

\[
 Z_{\theta\theta}=-{M+B\over M}\left[
 A\Phi\left(Z+{1\over M}R\right)
 +\Phi\left(Z-{A\over M}R\right)\right].
\tag{2}
\]

For the primary selected by the validated limiting collision put

\[
 q=Z-{A\over M}R.
\tag{3}
\]

Since the vector to the other primary is exactly

\[
 Z+{1\over M}R=q+R,
\]

subtraction of \(A/M\) times (1) from (2) gives

\[
 \boxed{
 q_{\theta\theta}=-(1+B)\Phi(q)
 +A\{\Phi(R)-\Phi(q+R)\}.}
\tag{4}
\]

The coefficient identities use only \(M=1+A\): the coefficient of
\(\Phi(q)\) is

\[
 -{M+B+AB\over M}=-(1+B),
\]

and those of \(\Phi(R)\) and \(\Phi(q+R)\) are \(A\) and \(-A\).
This calculation is regression-tested symbolically.

Equation (4) is a forced Kepler equation with gravitational parameter

\[
 \gamma_B=1+B
\]

and analytic external field

\[
 G_B(q,R)=A\{\Phi(R)-\Phi(q+R)\}.
\tag{5}
\]

It is analytic near the certified collision because the validation proves
that both \(R\) and \(q+R\) stay uniformly separated from zero there.

Regularizing \(q\) while retaining \(R\) is nevertheless insufficient:
equation (1) contains \(B\Phi(q)\).  Introduce instead the center of mass of
the colliding light--heavy pair relative to the third body,

\[
 \boxed{Q=R+{B\over1+B}q.}
\tag{5a}
\]

Then

\[
 R=Q-{B\over1+B}q,
 \qquad q+R=Q+{1\over1+B}q,
\tag{5b}
\]

and the singular pair force cancels exactly:

\[
 \boxed{
 Q_{\theta\theta}=-{M+B\over1+B}\left[
 \Phi\left(Q-{B\over1+B}q\right)
 +B\Phi\left(Q+{1\over1+B}q\right)
 \right].}
\tag{5c}
\]

Equations (4) and (5c), expressed with (5b), contain no \(\Phi(q)\) outside
the Kepler term in (4).  This cancellation is included in the exact symbolic
regression test.

## Finite-mass Levi--Civita chart

On the incoming half use the radial clock
\(t=\theta_c-\theta\), so that second derivatives in \(t\) and \(\theta\)
agree and the orientation matches the validated limiting shoot.  With complex
variables

\[
 q=u^2,\qquad dt=|u|^2d\sigma,
 \qquad h={|q_t|^2\over2}-{\gamma_B\over|q|},
\tag{6}
\]

the selected-pair block is

\[
 \begin{aligned}
 u_\sigma&=v,\\
 v_\sigma&={h\over2}u+{|u|^2\bar u\over2}G_B,\\
 h_\sigma&=2\operatorname{Re}(uv\overline{G_B}),
\end{aligned}
\tag{7}
\]

together with the collision-adapted outer equations

\[
 \begin{aligned}
 Q_\sigma&=|u|^2P,\\
 P_\sigma&=-|u|^2{M+B\over1+B}\left[
 \Phi\left(Q-{B\over1+B}u^2\right)
 +B\Phi\left(Q+{1\over1+B}u^2\right)
 \right]
 \end{aligned}
\tag{7a}
\]

and the physical clock.  Here \(P=Q_t\).  The force in (7) is obtained from
(5) by substituting (5b):

\[
 G_B(u,Q)=A\left[
 \Phi\left(Q-{B\over1+B}u^2\right)
 -\Phi\left(Q+{1\over1+B}u^2\right)
 \right].
\tag{7b}
\]

All right sides of (7)--(7b), including \(t_\sigma=|u|^2\), are real analytic
at \(u=0\) whenever \(Q\ne0\).  The preserved constraint is

\[
 \boxed{2|v|^2-(1+B)-h|u|^2=0.}
\tag{8}
\]

In particular,

\[
 |v|^2={1+B\over2}\quad\hbox{at }u=0.
\tag{9}
\]

Thus the binary collision remains a transverse crossing of the regularized
flow for every sufficiently small positive \(B\).  Equations (4), (8), and
(9) are exact symbolic identities, not limiting formulas.

## Parameter-dependent shooting map

Fix one regular incoming section \(\Sigma\) on the certified orbit before the
selected LC block, after all translation, rotation, time, and energy
constraints have been imposed.  The defining constraint, gauge, and section
functions have constant full rank at the certified collision-free base state:
the section is transverse to the flow, while the heavy radial and rotational
directions retain the energy and angular/gauge ranks at \(B=0\).  Thus
\(\Sigma\) is a smooth constrained section also at the massless boundary.
Equivalently, construct the chart for the analytic signed-\(B\) extension and
restrict the result to \(B\ge0\).  The limiting stable family meets this
section in a regular curve \(X_0(\kappa)\).  Its tangent at \(\kappa_c\) is
nonzero: otherwise propagation by the nonsingular pre-LC flow could not
produce the certified nonzero determinant
\(\det(\partial_\kappa u,v)\).

Choose a finite-dimensional \(C^1\) coordinate chart on the constrained
section with coordinates

\[
 (B,\widehat\kappa,\delta)\longmapsto
 X_{\mathrm{in}}(B,\widehat\kappa,\delta),
\tag{9a}
\]

such that

\[
 X_{\mathrm{in}}(0,\widehat\kappa,0)=X_0(\widehat\kappa).
\tag{9b}
\]

Here \(B\) is the positive light mass, \(\widehat\kappa\) extends the
limiting projective coordinate on this fixed section, and \(\delta\) consists
only of the remaining constraint- and gauge-compatible section coordinates.
This explicit local chart, rather than a claim of differentiated convergence
through the preceding logarithmic saddle dwell, is the parameter family used
below.

Propagation from \(\Sigma\) into the common selected-pair LC chart defines

\[
 \mathcal F(B,\widehat\kappa,\delta,\sigma)
 =\bigl(\operatorname{Re}u,
        \operatorname{Im}u\bigr).
\tag{10}
\]

Ordinary flow from \(\Sigma\) to LC entry and the coordinate lift are smooth.
Equations (7)--(7a) are smooth through the selected encounter.  At \(B=0\),
\(Q=R\).  The certificate proves strict primary-distance bounds on the whole
pre-LC chain, fixes the square-root deck by strict entry signs, and proves on
the LC block that

\[
 R>2,\qquad |q+R|>1
\tag{11}
\]

at \(B=0\).  Compactness and (5b) preserve all these chart inequalities,
including \(Q\ne0\), after shrinking the section neighborhood.  Consequently
\(\mathcal F\) is \(C^1\) jointly in its displayed variables and

\[
 \mathcal F(B,\cdot,\delta,\cdot)
 \longrightarrow\mathcal F(0,\cdot,0,\cdot)
 \quad\hbox{in }C^1_{(\widehat\kappa,\sigma)}
\tag{12}
\]

on a neighborhood of the certified root.  No physical continuation through
a positive-mass collision is used in this construction; only the smooth LC
shooting map is continued to locate its zero.

## Collision-boundary persistence theorem

**Theorem.** There are neighborhoods \(N\) of the certified limiting root
\((\kappa_c,\sigma_c)\), \(P\) of \(\delta=0\), and \(B_0>0\) such that,
for every \(0\le B<B_0\) and \(\delta\in P\), equation

\[
 \mathcal F(B,\widehat\kappa,\delta,\sigma)=0
\tag{13}
\]

has exactly one solution in \(N\).  Write it as
\((\widehat\kappa_c(B,\delta),\sigma_c(B,\delta))\).  It converges to the
validated root as \((B,\delta)\to0\), and

\[
 D_{B,\delta}=
 \det\bigl(\partial_{\widehat\kappa}u,v\bigr)<0
\tag{14}
\]

after shrinking \(P\) and \(B_0\).

For fixed \((B,\delta)\), nearby punctured parameters have a unique local
closest passage, and

\[
 \boxed{
 \begin{aligned}
 r_{\min,\mathrm{local}}
 &= {2D_{B,\delta}^2\over1+B}
    (\widehat\kappa-\widehat\kappa_c(B,\delta))^2
    +O(|\widehat\kappa-\widehat\kappa_c(B,\delta)|^3),\\
 \ell&=2D_{B,\delta}
    (\widehat\kappa-\widehat\kappa_c(B,\delta))
    +O(|\widehat\kappa-\widehat\kappa_c(B,\delta)|^2),
 \end{aligned}}
\tag{15}
\]

where both quantities are evaluated at the local closest-passage time,
\(r_{\min,\mathrm{local}}=|q|\), and \(\ell=q\times q_t\).  The incoming
physical-time angular momentum is \(-\ell\).

**Proof.** The validated theorem gives one zero of
\(\mathcal F(0,\cdot,0,\cdot)\) and

\[
 -3.52212<\det D\mathcal F_0<-3.38401.
\tag{16}
\]

Equation (12) and the parameter-dependent implicit-function theorem give a
unique nearby zero and preserve the negative determinant.  At a collision,
(9) makes the LC-time column nonzero.  The equation \(u\cdot v=0\) therefore
selects a unique nearby closest-passage time.  At fixed \((B,\delta)\), the
component of \(\partial_{\widehat\kappa}u\) perpendicular to \(v\) has squared norm

\[
 {\det(\partial_{\widehat\kappa}u,v)^2\over|v|^2}
 ={2D_{B,\delta}^2\over1+B}.
\]

Since \(q=u^2\), this proves the first line of (15).  The exact identity
\(q\times q_t=2\det(u,v)\) proves the second. \(\square\)

For \(B>0\), the zero in (13) is a true light--heavy collision and therefore
terminates the corresponding classical solution.  Its LC continuation is
used only to prove the location and local organization of the collision
boundary.

## What this does and does not settle

The theorem upgrades the massless root from an isolated limiting curiosity
to a structurally stable collision boundary in the local constrained
incoming-section state space.  In particular, the boundary survives positive
light mass and every sufficiently small compatible section-state
perturbation.

If an exact Pythagorean trajectory reaches \(\Sigma\) inside this chart, it
supplies one point
\((\widehat\kappa_B,\delta_B)\) in this section chart.  The theorem does not
prove

\[
 \widehat\kappa_B=\widehat\kappa_c(B,\delta_B),
\]

nor even that the selected curve crosses from one side to the other.  The
remaining arithmetic/dynamical bridge is the scalar signed gap

\[
 \boxed{\widehat\Delta_c(B)=
 \widehat\kappa_B-\widehat\kappa_c(B,\delta_B).}
\tag{17}
\]

The differentiated inclination theorem now replaces this section-dependent
gap by a normalized intrinsic one.  With all stable and triangular entrance
coordinates displayed explicitly, it gives a unique local collision graph
\(\kappa_c(B,T,S,\Xi)\) and reduces the actual endpoint trajectory to

\[
 \Delta_{\rm intr}(B)
 =\kappa_B-\kappa_c(B,T_B,S_B,\Xi_B),
 \qquad \kappa_B={H_B\over|T_B|^{\mu/\tau}}.
\tag{18}
\]

Thus differentiated transport through the logarithmic dwell is closed.  No
sign, zero, or oscillation theorem for (18) has been proved.

Controlling the sign or zeros of (18), and excluding other encounters before
a common outgoing section, is the next finite-mass obligation.  Equality in
(18) would prove classical termination, not periodicity.  Nonzero sign would
select one local scattering side but would not by itself exclude a later
brake.

**Status:** equations (4), (5c), (8), (9), and (15) are **EXACT SYMBOLIC IDENTITY**
or **PROVED ANALYTICALLY**.  Existence of the base root is **PROVED BY
COMPUTER-ASSISTED ARGUMENT**; therefore the collision-boundary persistence
theorem has that same status.  The tied-curve gap (17) is **CONJECTURAL**.
