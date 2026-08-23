# Compact certificate for the global triple-endpoint coefficient

This note combines the analytic collision attachment, one compact CAPD
propagation, elementary parabolic-tail estimates, and the already certified
first-scattering constants. Its target is the remaining global factor
$A_-$ in

\[
 (\pi-\phi)^{(\sqrt7-1)/6}\mathcal C_2(\phi)
 \longrightarrow4^{(\sqrt7-1)/6}A_-K_-.
\tag{1}
\]

The universal factor $K_->0$ was certified separately.

## Reversed collision-stable family

Fix the terminal binary collision at $\psi=3\pi/2$. Reverse time and reflect
the outer coordinate:

\[
 Z(s)=-z(t_c-s),\qquad w={dZ\over ds}=\dot z(t_c-s).
\]

Then, while $Z>0$,

\[
 Z''=-{2Z\over(Z^2+r^2/4)^{3/2}},qquad r=\cos^2\psi.
\tag{2}
\]

`TRIPLE_ENDPOINT_COLLISION_TAIL.md` attaches the exact one-parameter
collision-stable family and its canonical fast transverse mode at
$\rho=2^{-32}$. The verifier propagates the whole amplitude interval

\[
 I_a=[-0.24696,-0.24694]
\tag{3}
\]

first to $r=1/5$ in the Fuchsian chart and then for exactly $19\pi$ in
reversed eccentric anomaly. The latter endpoint lies near $Z=20$.

## Exact parabolic bracket

For every unturned orbit of (2), define the monopole comparison energy

\[
 H_K={w^2\over2}-{2\over Z}.
\]

Direct differentiation with respect to $Z$ gives

\[
 {dH_K\over dZ}={2\over Z^2}
 \left[1-\left(1+{r^2\over4Z^2}\right)^{-3/2}\right].
\tag{4}
\]

Therefore

\[
 0\le H_K(\infty)-H_K(Z)\le {1\over4Z^3}.
\tag{5}
\]

The CAPD propagation proves

\[
 H_K>0\quad(a=-0.24696),
\tag{6}
\]

with positive velocity on every accepted step, and

\[
 H_K+{1\over4Z^3}<0\quad(a=-0.24694).
\tag{7}
\]

Thus the first endpoint escapes hyperbolically and the second must turn.
Turning and hyperbolic escape are open in $a$. They cannot cover the connected
interval (3) by two disjoint nonempty open sets. At a point in their common
complement, $w$ remains nonnegative. If $Z$ were bounded, its strictly
negative acceleration would force a turn; hence $Z\to\infty$. The complement
is therefore parabolic, with $w\to0$. This proves that (3) contains at least
one collision-stable/incoming-parabolic connection. Uniqueness is not needed
for the coefficient sign below.

## Uniqueness inside the bracket

The compact propagation also verifies, on every accepted step and for the
whole amplitude box,

\[
 Z>{r\over2\sqrt2}.
\tag{7a}
\]

On the initial collision tail the stronger inequality
$Z>(\sqrt3/2)r$ follows analytically from $a<0$; beyond the validated large
section, (7a) is automatic from $Z>10$ and $0\le r\le1$. Consequently the
scalar force

\[
 f(Z,r)=-{2Z\over(Z^2+r^2/4)^{3/2}}
\]

is strictly order preserving throughout every candidate path:

\[
 f_Z={4Z^2-r^2/2\over(Z^2+r^2/4)^{5/2}}>0.
\tag{7b}
\]

The derivative and its cone numerator are exact symbolic regression tests.

Put $b=-a$, and take $b_2>b_1$ in the certified interval. The collision
asymptotics give, at every sufficiently small positive section,

\[
 \Delta Z=Z(b_2)-Z(b_1)>0,
 \qquad \Delta w>0.
\]

While both paths remain candidates, the mean-value formula and (7b) give

\[
 \Delta Z''=c(s)\Delta Z,
 \qquad c(s)=\int_0^1 f_Z(Z(b_1)+t\Delta Z,r)\,dt>0.
\tag{7c}
\]

Thus $\Delta w$ is strictly increasing. Two distinct amplitudes cannot both
be parabolic, since both velocities would tend to zero while their difference
stays bounded below by a positive value after any fixed small section. The
connection supplied above is therefore unique in (3). Moreover, every larger
$b$ in the box escapes hyperbolically and every smaller $b$ turns. This is an
order theorem, not a numerical uniqueness inference.

## Returned-Jost tail without truncation

On any such parabolic member put

\[
 z=-{2\over x^2},\qquad P=x^2p,qquad
 \Omega=z\dot p-\dot zp.
\]

The exact returned data at infinity are

\[
 P(0)=2\gamma,qquad \Omega(0)=-\mathscr W_\infty,
\tag{8}
\]

where the independent pinned scattering certificate proves

\[
 -{1\over100}<\gamma<-{1\over250},qquad
 {11\over25}<\mathscr W_\infty<{9\over20}.
\tag{9}
\]

The regular fiber equations imply, after division by $x_\psi$,

\[
 \left|{dP\over dx}\right|\le\sqrt2c|\Omega|,qquad
 \left|{d\Omega\over dx}\right|
 \le{3c\over8\sqrt2}x^2|P|,
\tag{10}
\]

uniformly for $0\le x\le X$, where

\[
 c=(1-X^4/32)^{-1/2}.
\]

Indeed, (5) on a parabolic orbit gives

\[
 \sqrt2x\sqrt{1-x^4/32}\le \dot z\le\sqrt2x.
\tag{11}
\]

Let

\[
 A=\sqrt2cX,qquad B={cX^3\over8\sqrt2}.
\]

The Volterra bootstrap

\[
 M_P\le {1\over50}+A M_\Omega,qquad
 M_\Omega\le {9\over20}+B M_P
\tag{12}
\]

closes because $1-AB>0$ on the validated $Z$ box. It also bounds
$|\Omega+\mathscr W_\infty|\le BM_P$. Since the resulting $\Omega$ remains
strictly negative, integration of $P_x=-2x\Omega/\dot z$ gives a positive
two-sided enclosure for $P$ at the finite section. Finally recover

\[
 p={P\over x^2},\qquad
 \dot p=-{\dot zP+x^2\Omega\over2}.
\tag{13}
\]

No two-term asymptotic truncation is used.

## Scalar sign

The same compact propagation encloses the canonical fast collision mode
$P_+=(p_+,\dot p_+)$. For every parabolic member in (3), outward-rounded
evaluation gives the strict rational margin

\[
 \boxed{W(J,P_+)<-{1\over2}.}
\tag{14}
\]

The exact collision-mode determinant is
$W(P_-,P_+)=-\sqrt7$. Consequently

\[
 \boxed{A_-={W(J,P_+)\over-\sqrt7}>0.}
\tag{15}
\]

The sign proof is uniform over the entire box and did not require uniqueness;
the separate order argument (7a)--(7c) now proves uniqueness in that box. It
does not alone prove differential transversality to the incoming parabolic
manifold; the differentiated tails and McGehee tangent contraction complete
that step in `TRIPLE_ENDPOINT_TRANSVERSALITY.md`.

## Reproduction and scope

The verifier is `src/verification/triple_endpoint_global_capd.cpp`. It uses
CAPD 6.1.0 at pinned commit
`731079217a9254ea2948d742df2b170895effe7f`, native outward-rounded
intervals, and exact rational input boxes. Reproduce with

~~~bash
bash scripts/run_capd_triple_endpoint_global.sh \
  /path/to/CAPD /path/to/CAPD/build-native
~~~

The exact hexadecimal output of a fresh replay is archived in
`data/triple_endpoint_global_capd_certificate.txt`.

The trusted base consists of the verifier and wrapper, pinned CAPD source,
host compiler, collision-tail fixed-point estimates, and analytic identities
(4)--(5) and (8)--(13).

Equation (15) settles the global coefficient. The companion transversality
and shifted-Fuchsian exchange theorems now construct a one-sided local
captured branch and prove its positive renormalized limit (1). Global
classification of remote captured components and finite-$B$ near-triple
transfer remain open. No finite-$B$ classical trajectory is continued through
a collision.

**Status of the collision attachment:** **PROVED ANALYTICALLY**.

**Status of the compact bracket, uniqueness, and (14)--(15):** **PROVED BY
COMPUTER-ASSISTED ARGUMENT**. Two independent adversarial passes rederived
the collision Green operators and the compact reversed-time/Jost logic. The
second pass independently replayed the pinned wrapper and reproduced the
stored hexadecimal certificate. A further adversarial pass verified the
pairwise uniqueness argument and initially rejected an unproved upgrade to
transversality. The repaired proof supplies derivative-strengthened collision
tails in a fixed gauge and invokes the already-proved $C^1$ McGehee parabolic
graph; re-audit endorsed the resulting transverse local-branch theorem.
