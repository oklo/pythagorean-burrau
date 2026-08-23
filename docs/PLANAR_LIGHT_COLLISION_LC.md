# Forced Levi--Civita chart for planar light-heavy collisions

The one-parameter planar shape family can pass arbitrarily close to either
heavy primary. Ordinary integration is not a reliable transition map there.
This note gives the exact analytic Levi--Civita chart and reduces an isolated
light-heavy collision to a square two-variable shooting equation.

The chart is a mathematical classification device. A true collision of an
actual positive-mass classical trajectory still terminates that trajectory;
the regularized continuation is not substituted for the conjecture.

## Relative forced Kepler equation

On one zero-energy heavy-binary half, let $\theta$ be physical time and use
the positive radial clock

\[
 t=|\theta-t_c|,
 \qquad \eta={dt\over d\theta}\in\{-1,+1\}.
\]

Thus $\eta=-1$ on the incoming half and $\eta=+1$ on the outgoing half.
Because $\eta$ is constant on either half, second derivatives in $t$ and
$\theta$ agree. Write

\[
 R(t)=9^{1/3}t^{2/3}e_x,\qquad R_{tt}=-2\Phi(R).
\tag{1}
\]

Let $\epsilon=+1$ for the heavy primary at $+R/2$ and $\epsilon=-1$ for the
one at $-R/2$. Put

\[
 q=Z-{\epsilon\over2}R.
\tag{2}
\]

The planar restricted equation gives

\[
 q_{tt}=-\Phi(q)+G_\epsilon(q,t),
\tag{3}
\]

\[
 \boxed{
 G_\epsilon(q,t)=\epsilon\Phi(R(t))
                 -\Phi(q+\epsilon R(t)).}
\tag{4}
\]

The full chart domain is

\[
 t>0,\qquad u^2+\epsilon R(t)\ne0.
\tag{4a}
\]

The second inequality excludes simultaneous contact with the other primary.
On this domain the forcing is real analytic. At the target $u=0$, it reduces
to $R(t)\ne0$, already implied by $t>0$. Thus each isolated light-heavy
collision away from the heavy collision is a forced Kepler collision with a
nonsingular external field.

## Complex Levi--Civita variables

Identify the plane with $\mathbb C$. Set

\[
 q=u^2,\qquad {dt\over d\sigma}=|u|^2,\qquad v={du\over d\sigma},
\tag{5}
\]

and introduce the relative Kepler energy

\[
 h={1\over2}|q_t|^2-{1\over|q|}.
\tag{6}
\]

Since, in radial-clock orientation,

\[
 q_t={2v\over\bar u},
\]

equation (6) is equivalent away from collision to the constraint

\[
 \boxed{2|v|^2-1-h|u|^2=0.}
\tag{7}
\]

Direct differentiation of (3)--(6) gives the exact regular field

\[
 \boxed{
 \begin{aligned}
 u_\sigma&=v,\\
 v_\sigma&={h\over2}u
  {}+{1\over2}|u|^2\bar u\,G_\epsilon(u^2,t),\\
 h_\sigma&=2\operatorname{Re}
  \left(u v\,\overline{G_\epsilon(u^2,t)}\right),\\
 t_\sigma&=|u|^2.
 \end{aligned}}
\tag{8}
\]

Every right side is real analytic (not complex holomorphic) at $u=0$ on
(4a). Symbolic differentiation proves that the left side of (7) has
derivative zero under (8). At collision,

\[
 |v|={1\over\sqrt2},
\tag{9}
\]

so the LC orbit crosses $u=0$ with nonzero regularized speed.
Moreover,

\[
 t_\sigma=0,\qquad t_{\sigma\sigma}=0,\qquad
 t_{\sigma\sigma\sigma}=2|v|^2=1
 \quad (u=0),
\tag{9a}
\]

and hence
$t(\sigma)-t(\sigma_c)
=(\sigma-\sigma_c)^3/6+O((\sigma-\sigma_c)^4)$.
The radial clock is monotone through the regularized collision even though
the reconstructed physical velocity is singular there.

## Collision residual and validation target

Let the parity-normalized stable family be indexed by $\kappa$, and propagate
it from one fixed equilateral-tail section into the appropriate LC chart. Fix
one of the two LC deck lifts at the entry section and fix the origin and
orientation of $\sigma$.
Write the resulting LC position as

\[
 u=u(\kappa,\sigma)\in\mathbb R^2.
\]

An isolated light-heavy collision is exactly a zero of the square residual

\[
 \boxed{\mathcal F(\kappa,\sigma)
 =(\operatorname{Re}u,\operatorname{Im}u)=0.}
\tag{10}
\]

Its Jacobian is

\[
 D\mathcal F=
 \begin{pmatrix}
 \partial_\kappa\operatorname{Re}u&
 \operatorname{Re}v\\
 \partial_\kappa\operatorname{Im}u&
 \operatorname{Im}v
 \end{pmatrix}.
\tag{11}
\]

Condition (9) makes the time column nonzero. A nonzero determinant in (11)
proves that the collision zero is locally isolated and that its nearby
continuations lie on two local sides of the collision parameter. Calling the
entire adjacent parameter intervals collision-free additionally requires
excluding every other collision zero on those intervals. Equations (8),
together with the stable-tail enclosure already used in the joint blow-up
theorem, are directly suited to interval Newton or a pinned CAPD shooting
certificate.

The determinant has a direct physical meaning. The light--selected-primary
relative angular momentum in radial-clock orientation is exactly

\[
 \ell=q\times q_t
 =2\operatorname{Im}(\bar u v)
 =2\det(u,v).
\tag{11a}
\]

At a collision zero, differentiation at fixed $\sigma=\sigma_c$ gives

\[
 \boxed{
 {\partial\ell\over\partial\kappa}
 =2\det(\partial_\kappa u,v)
 =2\det D\mathcal F.}
\tag{11b}
\]

With the clock $dt/d\sigma=|u|^2$ fixed, a $\kappa$-dependent translation of
the LC-time origin adds a multiple of $v$ to $\partial_\kappa u$ and does not
alter this determinant. A deck change negates all three columns and likewise
leaves it unchanged. Its sign does depend on the chosen orientation of
$\kappa$. Therefore a transverse interval-Newton zero automatically supplies
a signed, linearly changing physical impact parameter in the fixed parameter
orientation. On the incoming half the physical-time angular momentum is
$\eta\ell=-\ell$; on the outgoing half it is $+\ell$.

There is also a quantitative local miss-distance law. Write
$D_c=\det D\mathcal F(\kappa_c,\sigma_c)\ne0$. Since

\[
 {\partial\over\partial\sigma}(u\cdot v)
 =|v|^2+u\cdot v_\sigma={1\over2}
 \quad\hbox{at collision},
\]

the implicit-function theorem gives a unique nearby local closest-passage
time $\sigma_*(\kappa)$, characterized by $u\cdot v=0$. Orthogonal projection
of $\partial_\kappa u$ onto $v_c^\perp$ then yields

\[
 \boxed{
 \begin{aligned}
 |q(\kappa,\sigma_*(\kappa))|
   &=2D_c^2(\kappa-\kappa_c)^2
     +O(|\kappa-\kappa_c|^3),\\
 \ell(\kappa,\sigma_*(\kappa))
   &=2D_c(\kappa-\kappa_c)
     +O(|\kappa-\kappa_c|^2).
 \end{aligned}}
\tag{11c}
\]

Thus every sufficiently close nonzero parameter misses this selected
collision locally, on a side distinguished by the impact sign. This theorem
does not exclude a collision with either primary at another time.

The physical state away from $u=0$ is reconstructed by

\[
 q=u^2,\qquad q_t={2v\over\bar u},\qquad
 Z=q+{\epsilon\over2}R,\qquad
 q_\theta=\eta{2v\over\bar u},\qquad
 Z_\theta=\eta\left({2v\over\bar u}
                       +{\epsilon\over2}R_t\right).
\tag{12}
\]

In particular, increasing $\sigma$ runs backward in physical time on the
incoming half. This orientation factor must be applied before assigning an
incoming or outgoing angular sign.

For a noncolliding orbit, the LC variables and transition maps between
sections away from $u=0$ follow an arbitrarily close passage without loss of
derivatives. Reconstruction is made only on an exit section with $|u|$ bounded
away from zero; the physical velocity formula itself is singular at $u=0$.
For the exact zero (10), the regularized continuation can classify the local
branches, but the corresponding classical orbit stops.

## Relation to the ordinary probe

The unregularized deterministic probe indicates a collision-scale transition
near $\kappa\approx1.26$ for the chosen normalization, but its closest
reported distances are too small for trustworthy unregularized scattering.
The regularized ordinary shoot first refined a collision seed to
$\kappa\approx1.26793517$ with a finite-difference determinant about $-3.45$.
The analytic stable-tail theorem and a correlation-preserving CAPD
construction have now validated that seed. There is a unique zero in

\[
 1.2679350755\le\kappa\le1.2679352755,
 \qquad
 -1.0712486057\le\sigma\le-1.0712484057,
\]

and

\[
 -3.52212<\det(\partial_\kappa u,v)<-3.38401.
\]

The complete certificate is in
`COMPUTER_ASSISTED_PLANAR_LIGHT_COLLISION_ROOT.md`. It validates a collision
in the massless planar limiting family, not a finite-mass classical orbit or a
second brake.

The next computer-assisted tasks are:

1. exclude every other collision zero before naming global components;
2. propagate the signed local branches to common outgoing sections;
3. bound the outgoing angular scalar on every collision-free component.

## Status

Equations (1)--(9), constraint preservation, and the square residual
(10)--(11), including the impact identity (11a)--(11b), are **PROVED
ANALYTICALLY** or **EXACT SYMBOLIC IDENTITY**.
Existence, uniqueness inside the explicit root box, and transversality of the
selected collision parameter are **PROVED BY COMPUTER-ASSISTED ARGUMENT**.
Global uniqueness among all parameters and collision times is
**CONJECTURAL**.
