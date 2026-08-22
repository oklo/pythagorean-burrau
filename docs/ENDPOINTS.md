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

## Skinny endpoint

As $u\to0$, $B\to0$, the 1--3 separation and mass $m_2$ degenerate in the
tied normalization.  The limiting initial condition is already collisional
and includes a vanishing mass, so ordinary continuous dependence across
$u=0$ is unavailable.  No uniform positive-$u$ theorem has yet been proved.

