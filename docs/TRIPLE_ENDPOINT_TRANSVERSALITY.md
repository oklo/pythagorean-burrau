# Transversality of the certified triple-endpoint connection

The compact global certificate gives a parabolic connection between the
collision-stable curve and the incoming parabolic curve. Its whole-path cone,
together with two analytic endpoint tangent lemmas, makes that intersection
transverse.

## Fixed gauge and collision tangent

Fix the target binary collision at eccentric anomaly $3\pi/2$ and use reversed
time $s$ with

\[
 Z=-z,qquad w=Z_s.
\]

The prescribed binary schedule $r(s)$ is independent of the collision-stable
amplitude. Put $b=-a$. The differentiated contraction in
`TRIPLE_ENDPOINT_COLLISION_TAIL.md` proves, on a small positive collision
section,

\[
 J=\partial_bZ>0,
 \qquad J_s=\partial_bw>0.
\tag{1}
\]

No phase derivative is hidden in (1): the terminal collision lift is fixed,
so $r_b=0$.

## Monotone propagation of the collision tangent

The scalar force is

\[
 f(Z,r)=-{2Z\over(Z^2+r^2/4)^{3/2}},
 \qquad
 f_Z={4Z^2-r^2/2\over(Z^2+r^2/4)^{5/2}}.
\tag{2}
\]

On the analytic collision tail, $Z>(\sqrt3/2)r$. On the compact core, the
pinned CAPD replay proves $Z>r/(2\sqrt2)$ on every accepted step and for the
whole amplitude bracket. Beyond its last section, $Z>10$ and $0\le r\le1$.
Thus $f_Z>0$ along the complete certified parabolic connection.

Differentiating its equation in the fixed gauge gives exactly

\[
 J_{ss}=f_ZJ.
\tag{3}
\]

Equations (1)--(3) imply

\[
 J>0,qquad J_s(s)\ge J_s(s_0)>0
\tag{4}
\]

for every $s\ge s_0$. The derivative need not have a finite limit; the strict
lower bound is the relevant fact.

## Incoming parabolic tangent

At a fixed binary phase, compactify parabolic infinity by

\[
 Z={2\over X^2},qquad W=w-\sqrt2X.
\]

`PARABOLIC_MANIFOLD.md` proves that the outgoing parabolic states form a
differentiable graph

\[
 W=\varphi(X),qquad \varphi(0)=\varphi'(0)=0,
\tag{5}
\]

and that every tangent to this fixed-phase graph contracts under the
stroboscopic parabolic map:

\[
 \delta X_n\longrightarrow0.
\tag{6}
\]

Consequently

\[
 \delta w_n=(\sqrt2+\varphi'(X_n))\delta X_n\longrightarrow0.
\tag{7}
\]

The incoming parabolic curve on the regular match section becomes this
outgoing graph after the same reversed-time propagation used above.

## Transverse intersection

Let $C(b)$ be the collision-stable curve and $U(\eta)$ the incoming parabolic
curve on any fixed regular final-infall section, where $\eta$ is any regular
local graph coordinate. The global certificate and
the scalar order argument give their unique intersection in

\[
 -0.24696\le a\le-0.24694.
\tag{8}
\]

Suppose $C_b$ and $U_\eta$ were collinear there. Linearized flow would preserve
that collinearity. Along a fixed-phase stroboscopic sequence tending to
parabolic infinity, the velocity component propagated from $C_b$ is bounded
away from zero by (4), whereas the component propagated from $U_\chi$ tends to
zero by (7). This is impossible. Therefore

\[
 \boxed{\det[-U_\eta,C_b]\ne0.}
\tag{9}
\]

Since $b=-a$, the same conclusion holds with $C_a$. In the square matching
problem of `TRIPLE_ENDPOINT_MATCHING_CERTIFICATE.md`, use this regular graph
coordinate in place of the canonical intercept unless immersion of that
particular intercept has separately been established. The exact transverse
determinant is $-\sqrt7$, so the full four-dimensional matching zero is simple
in the regular local coordinates.

This theorem proves local isolation and a genuine crossing of the two base
curves. It does not identify every global captured component, and it does not
by itself transfer the result to finite light mass.

**Status:** the collision derivative and incoming graph/tangent statements
are **PROVED ANALYTICALLY**. The whole-path force cone and therefore (9) are
**PROVED BY COMPUTER-ASSISTED ARGUMENT**. The cone output is archived in
`data/triple_endpoint_global_capd_certificate.txt`.
