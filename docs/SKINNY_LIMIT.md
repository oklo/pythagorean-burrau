# Skinny-limit program

Let $B=\varepsilon\to0$ and use the initially tight pair of bodies 1 and 3,
whose separation is

\[
X=q_3-q_1=B(B,A).
\]

For its specific angular momentum $h=X\times\dot X$, the internal pair force
has zero torque.  The perturbing acceleration from body 2 gives the exact
initial identity

\[
\boxed{\dot h(0)=-B^2(A^{-2}-A)<0.}
\]

In the Euclid parameter this is

\[
-{8u^4(u^4+3)\over(1-u)^2(1+u)^2(1+u^2)^3},
\]

so $\dot h(0)=-\tfrac32B^4+O(B^6)$.  Status: EXACT SYMBOLIC IDENTITY.

## First-encounter theorem

Freezing the outer Jacobi vector at leading order first suggested the following
coefficients. The full Levi--Civita calculation in SKINNY_REGULARIZATION.md
now proves them with uniform analytic remainders. The limiting binary falls
radially and gives tidal torque $\dot h\sim-(3/2)B^2r^2$.  With

\[
\ddot r=-{M\over r^2},\qquad r(0)=B,\quad\dot r(0)=0,\quad M\to2,
\]

the rescaling $r=BR$, $t=B^{3/2}\tau/\sqrt M$ and beta integral

\[
\int_0^{\tau_c}R^2d\tau={5\pi\over16\sqrt2}
\]

yield

\[
h_{enc}\sim-{15\pi\over64}B^{11/2},
\qquad
r_{min}\sim{225\pi^2\over16384}B^{11}.
\]

Status: **PROVED ANALYTICALLY** for the first encounter. There exists
$B_0>0$ such that every $0<B<B_0$ has a positive first heavy-pair miss with
the displayed asymptotics. These expressions explain why an
unregularized double-precision integration can mistake a positive-$u$ passage
for collision: at $B\approx0.1$ the predicted miss scale is already about
$10^{-12}$.

To obtain a Level-D nonperiodicity theorem, one must still control the
$O(B^{-3/2})$ tight-binary cycles before the outer body's order-one-time
plunge. The first-passage outer state is inward and strongly bound, so no
known escape criterion applies there. The exact conditional certificate in
ESCAPE_CRITERIA.md becomes useful only after a later phase-uniform
scattering analysis reaches an outgoing section.
