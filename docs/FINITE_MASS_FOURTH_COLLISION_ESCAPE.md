# Positive-mass transfer of the fourth planar collision boundary

Status: **EXACT SYMBOLIC IDENTITY** for the opposite-primary reduction;
**PROVED ANALYTICALLY**, conditional only on the cited validated limiting
certificate, for the local positive-mass collision-or-escape transfer.
Together these give a **PROVED BY COMPUTER-ASSISTED ARGUMENT** local theorem.

This note transfers the local massless theorem of
COMPUTER_ASSISTED_PLANAR_FOURTH_COLLISION_PHASE.md to sufficiently small
positive light mass. It does not prove that the tied Pythagorean curve enters
this local section neighborhood.

## Opposite-primary finite-mass chart

Use the late Jacobi variables with

\[
 A=\sqrt{1-B^2},\qquad M=1+A,
\]

\[
 R_{\theta\theta}=-M\Phi(R)
 +B\{\Phi(Z-AR/M)-\Phi(Z+R/M)\},
\]

\[
 Z_{\theta\theta}=-{M+B\over M}
 \{A\Phi(Z+R/M)+\Phi(Z-AR/M)\}.
\]

The fourth limiting root is a collision with the negative primary, so put

\[
 q=Z+{R\over M},\qquad q-R=Z-{A\over M}R.
\]

Direct subtraction gives the exact opposite-pair equation

\[
 \boxed{
 q_{\theta\theta}=-(A+B)\Phi(q)-\Phi(R)-\Phi(q-R).}
\tag{1}
\]

The singular pair force in the \(R\) equation is cancelled by the
light--negative-primary center coordinate

\[
 \boxed{Q=R-{B\over A+B}q.}
\tag{2}
\]

Indeed, after

\[
 R=Q+{B\over A+B}q,\qquad
 q-R={A\over A+B}q-Q,
\]

one has

\[
 \boxed{
 Q_{\theta\theta}=-{M+B\over A+B}\left[
 A\Phi\left(Q+{B\over A+B}q\right)
 +B\Phi\left(Q-{A\over A+B}q\right)\right].}
\tag{3}
\]

Let

\[
 G_-(u,Q)=
 -\Phi\left(Q+{B\over A+B}u^2\right)
 +\Phi\left(Q-{A\over A+B}u^2\right).
\tag{4}
\]

With \(q=u^2\), \(dt=|u|^2d\sigma\), and

\[
 h={|q_t|^2\over2}-{A+B\over|q|},
\]

the collision block is

\[
\begin{aligned}
u_\sigma&=v,\\
v_\sigma&={h\over2}u+{|u|^2\bar u\over2}G_-(u,Q),\\
h_\sigma&=2\operatorname{Re}(uv\overline{G_-(u,Q)}),\\
Q_\sigma&=|u|^2P,\\
P_\sigma&=-|u|^2{M+B\over A+B}\left[
 A\Phi\left(Q+{B\over A+B}u^2\right)
 +B\Phi\left(Q-{A\over A+B}u^2\right)\right].
\end{aligned}
\tag{5}
\]

Every right side is real analytic at \(u=0\) while \(Q\ne0\). The exact
constraint is

\[
 \boxed{2|v|^2-(A+B)-h|u|^2=0,}
\tag{6}
\]

so \(|v|^2=(A+B)/2>0\) at collision. The symbolic function
finite_mass_opposite_collision_reduction() and its regression test verify
(1), (3), preservation of (6), and the collision-speed normalization
identically.

## Compact finite-time transfer

Fix a regular constrained incoming section before the fourth selected
encounter. Extend the limiting coordinate \(\kappa\) and the remaining
constraint-compatible section coordinates as

\[
 X_{\rm in}(B,\widehat\kappa,\delta),\qquad
 X_{\rm in}(0,\widehat\kappa,0)=X_0(\widehat\kappa).
\]

The pre-entry ordinary flow, its square-root lift, and (5) give a common
analytic chart through the fourth collision. The certified other-primary
separation keeps \(Q\ne0\). Hence the fourth transverse collision persists
as a local collision sheet by the parameter-dependent implicit-function
theorem.

On the reference collision--ejection branch, the simultaneous two-centre
coordinate is \(\xi=\alpha+i\beta\). Its two normalized primary distances
are

\[
 r_-=\cosh^2(\beta/2)-\sin^2(\alpha/2),\qquad
 r_+=\sinh^2(\beta/2)+\sin^2(\alpha/2),
\]

up to the interchange of focus labels. A collision can therefore occur only
at an integral-\(\pi\) focus with \(\beta=0\). The validated replay now
audits \(p_r<0\), hence \(\alpha_\sigma=-p_r>0\), on every whole-step
enclosure through the fifth, sixth, and seventh foci. The respective focus
separations are strictly positive:

\[
 r_5>3.964960196340643\times10^{-11},\qquad
 r_6>1.098165821369775\times10^{-6},\qquad
 r_7>0.0506366673765623.
\tag{7}
\]

Thus the reference segment after a small fixed fourth-LC exit and before a
fixed heavy-pair LC entry is a compact collision-free ordinary Newtonian
segment. Its minimum physical pair separation is positive. Ordinary
parameter dependence transfers this finite segment to a sufficiently small
neighborhood; the extremely small first margin affects the neighborhood
size, not the existence argument.

The limiting segment subsequently crosses the prescribed heavy-pair
collision. The collision-pair center cancellation and heavy-pair
Levi--Civita block already used for the first and second boundary transfers
give a common analytic chart there. The validated bridge keeps both
light--primary squared distances above

\[
 0.00262385439850217.
\tag{8}
\]

Consequently the Newtonian-scaled terminal state and the heavy-pair Jacobi
energy converge uniformly as \((B,\delta)\to(0,0)\), unless a true
positive-mass collision has already terminated the classical solution.

## Infinite-time escape

At the limiting terminal state, the full-pair hierarchical comparison with
\(\epsilon=1/100\) and \(c=3/2\) has strict margin

\[
 \dot\rho_0-{2\over(3/2)(\rho_0-r_0)}
 -\sqrt{{4\over r_0}+{2\over100}}-{3\over2}
 >10.3953509156741.
\tag{9}
\]

For positive mass the inner heavy pair has mass \(M=1+A\), the outer light
mass is \(m_c=B\), and the total mass is \(\mathcal M=M+B\). The exact
hierarchical lemma bounds

\[
 |\ddot y|\le{\mathcal M\over(\rho-r)^2},\qquad
 |\dot e|\le{2B\,r|\dot x|\over(\rho-r)^3}.
\]

On a compact terminal neighborhood its future comparison integral \(K\) is
uniformly finite. Scaled terminal convergence gives \(e_0\to0\), while
\(2BK\to0\). Therefore both strict hypotheses

\[
 \dot\rho_0-{\mathcal M\over c(\rho_0-r_0)}
 >\sqrt{{2M\over r_0}+2\epsilon}+c,
\qquad e_0+2BK<\epsilon
\]

hold for all sufficiently small compatible positive-mass data. The future
classical solution then either has an inner collision or the light body
escapes hyperbolically. In either case it cannot have a later brake.

## Theorem and scope

**Theorem.** There are \(B_0>0\) and a neighborhood \(N\) of the fourth
limiting collision state on the fixed constrained incoming section such that
every compatible member with \(0<B<B_0\) and section state in \(N\) either
suffers a finite classical collision or its light body escapes to infinity.
Every collision-free member of this local cusp is nonperiodic.

At a positive-mass collision, the classical orbit ends. Equations (5) and the
heavy-pair LC chart are used only to organize the collision boundary and to
prove the alternative for neighboring collision-free trajectories. No
postcollision path is assigned to a colliding physical orbit.

The theorem is existential: neither \(B_0\) nor the section-neighborhood
radius is presently effective. Connecting the exact tied Pythagorean family
to this cusp remains a separate matching and sampling problem.
