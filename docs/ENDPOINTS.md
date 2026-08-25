# Endpoint analysis

## Isosceles-right endpoint: an exact collision theorem

Let

\[
u_*=\sqrt2-1,\qquad A=B=m=1/\sqrt2,\qquad m_3=M=1.
\]

The normalized initial positions are

\[
q_1=(-1/2,0),\qquad q_2=(1/2,0),\qquad q_3=(0,1/2).
\]

Reflection through the vertical axis followed by exchange of the equal labels
1 and 2 fixes the initial state.  Uniqueness preserves this symmetry throughout
the maximal classical solution.  Write the two base positions as

\[
q_1=(-x,y_b),\qquad q_2=(x,y_b),
\]

the apex as $q_3=(0,y_a)$, and $h=y_a-y_b$.  Directly from Newton's equations,
as long as $x>0$,

\[
\ddot x=-{m\over4x^2}-{Mx\over(x^2+h^2)^{3/2}}<0,
\qquad
\ddot h=-{(2m+M)h\over(x^2+h^2)^{3/2}}.
\]

Since $x(0)=x_0=1/2$ and $\dot x(0)=0$, it follows that
$\dot x(t)<0$ at every positive classical time.  In particular, no second
brake can occur.

There is also a finite-time collision.  While $x>0$, monotonicity gives
$x\le x_0$ and therefore

\[
\ddot x\le-{m\over4x_0^2}.
\]

Twice integrating yields

\[
x(t)\le x_0-{m\over8x_0^2}t^2.
\]

Consequently the classical solution must encounter a collision no later than

\[
t=\sqrt{8x_0^3/m}=2^{1/4}.
\]

If $h\ne0$ then $x=0$ is the 1--2 binary collision; if $h=0$ it is triple
collision.  Either terminates the exact classical solution.

**Theorem (endpoint).**  The real isosceles-right Pythagorean--Burrau brake
trajectory has no positive second brake and ends in finite collision.

Status: PROVED ANALYTICALLY.  The endpoint is irrational and hence is not an
integer Pythagorean triple.  Extending the conclusion to a punctured
neighborhood is singular: after symmetry breaking, the endpoint collision can
unfold into a close collision-free encounter.  A regularized perturbation map
with uniform error bounds remains required.

There is now a rigorous result before that singular encounter.  A pinned
CAPD full-step cover proves that the symmetric trajectory's first syzygy is
unique, transverse, collision-free, and has terminal torque amplitude
$Z_*<1$.  Exact Bernstein arithmetic proves $Z_J^{\rm syz}>1$ on the full
torque-compatible tied syzygy face, while a $C^1$ Poincare certificate proves
that the continued event enters that face with normalized derivative
$z_v(1)>18$.  Consequently the continued first syzygy satisfies

\[
 Z<1<Z_J^{\rm syz}
\]

for every tied member in some one-sided near-isosceles neighborhood.  This
closes the terminal first-syzygy amplitude obligation.  A separate odd-
variation cover proves strict side ordering and $\eta<h$ on the complete
preceding arc, excluding every brake through the first syzygy.

The endpoint collision unfolding is now also locally classified.  Use the
pair--12 Jacobi coordinate $g=q_2-q_1=w^2$, the complementary coordinate
$G=q_3-C_{12}$, and Levi--Civita time

\[
 {dt\over d\sigma}=|w|^2.
\]

The exact endpoint binary is the section $\operatorname{Re}w=0$.  A pinned
$C^1$ Poincare enclosure proves

\[
 z_r={d\,\operatorname{Re}w\over d\sigma}<-{4\over5},\qquad
 r_{31}^2,r_{23}^2>{1\over500},
\]

and, for the tied parameter $v=u/(\sqrt2-1)$,

\[
 \boxed{\chi:={d\over dv}\operatorname{Im}w\bigg|_{v=1,
 \operatorname{Re}w=0}<-30.}
\]

Thus the Jacobian of $(\sigma,v)\mapsto
(\operatorname{Re}w,\operatorname{Im}w)$ is nonsingular at the endpoint
collision.  The inverse-function theorem makes this the only collision zero
in a product neighborhood.  Consequently every sufficiently near one-sided
tied member crosses the complete corresponding encounter classically and
collision-free.  Moreover

\[
 \min_{\rm enc} r_{12}(v)=\chi^2(1-v)^2+o((1-v)^2),
\]

so the near miss is quadratically small but strictly positive.  The pair
angular momentum satisfies

\[
 \ell_{12}=2(w_rz_i-w_iz_r),\qquad
 {d\ell_{12}\over dv}(1)=-2\chi z_r<0.
\]

Hence $\ell_{12}>0$ at the collision section for $v<1$ close to one: the
close encounter has already reversed its negative launch sign.  This is a
**PROVED BY COMPUTER-ASSISTED ARGUMENT** local scattering theorem, not a
post-collision continuation of the endpoint's terminated classical orbit.

The full punctured endpoint neighborhood is now closed.  The symmetric LC
comparison has exactly four selected collision zeros before $\sigma=7$ and
its fifth after that section.  Pinned $C^1$ maps prove a nonzero tied normal
derivative at every one of the first four; a 7000-step $C^0$ cover proves
the other squared separations exceed $1/500$ and the regularized brake
residual exceeds $2$.  At $\sigma=7$, fixed $\eta=4$ satisfies the terminal
binary--escaper criterion with radial margin $>1/20$ and future-tidal inner
margin $>2$.  IFT, compactness, and strict continuity therefore give an
existential $v_*<1$ for which every $v_*<v<1$ is a collision-free,
brake-free classical orbit to the terminal section and thereafter either
collides or escapes.  Thus all such tied members are nonperiodic.  No
effective value of $v_*$ is presently claimed.
See `ISOSCELES_SYZYGY_THRESHOLD.md` for the complete analytic transfer and
the hexadecimal interval replay.

## Skinny endpoint

As $u\to0$, $B\to0$, the 1--3 separation and mass $m_2$ degenerate in the
tied normalization.  The limiting initial condition is already collisional
and includes a vanishing mass, so ordinary continuous dependence across
$u=0$ is unavailable.  Infinitely many open collision-or-escape windows and
a positive-density explicit rational subfamily are proved, but no theorem
yet covers the complete interval $0<u<u_0$.
