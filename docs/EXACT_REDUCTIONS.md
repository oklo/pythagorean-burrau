# Exact reductions and initial identities

All formulas below use (I=\sum_i m_i|q_i-q_{CM}|^2) and positive potential
magnitude (U=\sum_{i<j}m_im_j/r_{ij}), so Hamiltonian energy is (H=K-U).
The symbolic regression is `scripts/derive_exact_identities.py`.

## Center of mass is the incenter

The incenter of a triangle has barycentric weights proportional to opposite
side lengths.  Since those are exactly the masses, its incenter is (q_{CM}).
In the displayed Cartesian coordinates,

\[
q_{CM}=((b-a)/2,\ ab/(a+b+c)).
\]

For a right triangle the inradius is

\[
\rho={ab\over a+b+c}={a+b-c\over2}.
\]

Thus the second displayed Cartesian coordinate is (\rho).  The often-used
statement that “both coordinates are (\rho)” refers instead to orthogonal
right-angle coordinates based at (q_3) along the two legs.  It is not true
for the original horizontal-axis coordinates.  At present the incenter fact
is an exact initial coincidence, not a preserved invariant: after motion the
masses remain fixed while the opposite side lengths do not.

## Moment, potential, and configurational measure

The pair-distance identity

\[
I={1\over M}\sum_{i<j}m_im_jr_{ij}^2
\]

gives

\[
I_0={ab c^2+ac b^2+bc a^2\over a+b+c}=abc.
\]

After (c=1), (I_0=AB).  Directly,

\[
U_0={ab\over c}+{ac\over b}+{bc\over a},\qquad
U_0|_{c=1}=AB+{A\over B}+{B\over A}=AB+{1\over AB},
\]

and (H=-U_0).  Therefore

\[
\mu_0=U_0\sqrt{I_0}=(AB)^{3/2}+(AB)^{-1/2}.
\]

This is invariant under fixed-mass spatial scaling, not under the
simultaneous mass--length redundancy.

On the fundamental interval let (p=AB).  Exact differentiation gives

\[
p'(u)={2(1-6u^2+u^4)\over(1+u^2)^3}>0
\quad(0<u<\sqrt2-1),
\]

with (p\uparrow1/2).  Moreover

\[
{d\over dp}(p^{3/2}+p^{-1/2})={3p^2-1\over2p^{3/2}}<0
\quad(0<p\le1/2).
\]

Thus (\mu_0) decreases strictly from infinity to
(5\sqrt2/4).  This monotonicity is exact but currently supplies no global
brake obstruction.  A noncollinear right triangle is not a central
configuration (the noncollinear three-body central configurations are
equilateral), so the launch is not homothetic.

## Immediate Pythagorean defect

Let

\[
D=r_{12}^2-r_{23}^2-r_{31}^2=r_c^2-r_a^2-r_b^2.
\]

At a brake, for every pair,

\[
{d^2\over dt^2}|q_j-q_i|^2\bigg|_0
=2(q_j-q_i)\mathbin\cdot(\ddot q_j-\ddot q_i).
\]

Substitution of Newton's accelerations and (A^2+B^2=1) yields the corrected
identity

\[
D(0)=\dot D(0)=0,\qquad
\boxed{\ddot D(0)=2\left({1\over AB}-AB(A+B)\right)}.
\]

It is positive on the full real family: (AB\le1/2) and
(A+B\le\sqrt2), so
((AB)^2(A+B)\le\sqrt2/4<1).  Every launch therefore enters (D>0)
for sufficiently small positive time.  This local statement does not imply
that (D) stays positive, and no such global invariant is claimed.

## Even jets

Analyticity away from collision and zero initial velocity imply
$q(t)=q_0+q_2t^2+q_4t^4+\cdots$ locally.  Twice differentiating Newton's force
and then the squared distances gives

\[
D^{(4)}(0)={P_{20}(u)\over
u^4(u-1)^4(u+1)^2(1+u^2)^4},
\]

where

\[
\begin{aligned}
P_{20}={}&u^{20}-4u^{19}+10u^{18}-84u^{17}+25u^{16}-78u^{15}
+142u^{14}-366u^{13}\\
&-168u^{12}+122u^{11}-126u^{10}-614u^9+192u^8-58u^7
-22u^6\\
&+38u^5-49u^4+18u^3-4u^2+2u-1.
\end{aligned}
\]

The exact Sturm sequence has length 21 and has 10 sign variations both at
$0$ and at $83/200$.  It follows that $P_{20}$ has no root in that interval.
Since $P_{20}(0)=-1$ and
$\sqrt2-1<83/200$, while the denominator is positive,

\[
\boxed{D^{(4)}(0)<0\quad(0<u\le\sqrt2-1).}
\]

The derivative formula is an EXACT SYMBOLIC IDENTITY; the uniform sign is
PROVED BY COMPUTER-ASSISTED ARGUMENT using exact rational Sturm arithmetic.
The local series begins

\[
D(t)={\ddot D(0)\over2}t^2+{D^{(4)}(0)\over24}t^4+O(t^6),
\]

with uniform signs $+,-$.  The later numerical sign changes show that this
finite jet still does not imply a global barrier.
