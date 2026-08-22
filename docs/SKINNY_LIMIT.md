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

## Formal first-encounter asymptotics

Freezing the outer Jacobi vector at leading order makes the binary fall
radially and gives tidal torque $\dot h\sim-(3/2)B^2r^2$.  With

\[
\ddot r=-{M\over r^2},\qquad r(0)=B,\quad\dot r(0)=0,\quad M\to2,
\]

the rescaling $r=BR$, $t=B^{3/2}\tau/\sqrt M$ and beta integral

\[
\int_0^{\tau_c}R^2d\tau={5\pi\over16\sqrt2}
\]

formally yield

\[
h_{enc}\sim-{15\pi\over64}B^{11/2},
\qquad
r_{min}\sim{225\pi^2\over16384}B^{11}.
\]

Status: CONJECTURAL FORMAL ASYMPTOTICS.  These expressions explain why an
unregularized double-precision integration can mistake a positive-$u$ passage
for collision: at $B\approx0.1$ the predicted miss scale is already about
$10^{-12}$.

To obtain a Level-D theorem, Levi--Civita or algorithmic regularization must
turn these into uniform upper and lower bounds, prove the first encounter is
collision-free for all sufficiently small positive $u$, and continue the
outgoing state to a rigorous escape or one-way transition criterion.  The
nonzero initial torque alone does none of this.

