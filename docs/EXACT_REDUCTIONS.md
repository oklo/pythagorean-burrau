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

Before normalization the same scale-independent acceleration is

\[
\ddot D(0)=2\left({c^2\over ab}-{ab(a+b)\over c^3}\right).
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

## Planar endpoint stable jet and collision normal form

The massless planar joint endpoint has an autonomous logarithmic shape flow.
At its lower equilateral rest point, the complete stable-manifold jet through
total degree three is

\[
 x=p+Ap\nu+Bp^3+Cp\nu^2+O_4,
 \qquad
 q=\nu+Kp^2+D\nu^2+Ep^2\nu+F\nu^3+O_4,
\]

where $p=Te^{-a_T\zeta}$, $\nu=He^{-a_L\zeta}$ and all seven exact
coefficients are displayed in `PLANAR_JOINT_SHAPE_DYNAMICS.md`. The exact
degree-four correction has monomials $p^3\nu,p\nu^3$ in $x$ and
$p^4,p^2\nu^2,\nu^4$ in $q$. Symbolic substitution gives zero residual
through degree four. The analytic majorant theorem in
`PLANAR_STABLE_TAIL_ENCLOSURE.md` proves a unique normalized stable
parameterization $P=P_4+E$ with
$\|E\|_{1/200,1/2500}<1/125000000$ and, on half radii,
$\|E\|<1/4000000000$, $\|\mathcal DE\|<1/800000000$. This closes the
former $O_5$ tail obligation for $5/4\le\kappa\le13/10$, $\zeta\ge10$.

At a selected light-heavy encounter, the forced Levi--Civita chart has

\[
 q=u^2,\qquad t_\sigma=|u|^2,\qquad
 2|v|^2-1-h|u|^2=0,\qquad
 \ell=q\times q_t=2\det(u,v).
\]

For a transverse collision zero
$D_c=\det(\partial_\kappa u,v)\ne0$, the exact local normal form is

\[
 r_{\min,\mathrm{local}}
 =2D_c^2(\kappa-\kappa_c)^2+O(|\kappa-\kappa_c|^3),
 \qquad
 \ell=2D_c(\kappa-\kappa_c)+O(|\kappa-\kappa_c|^2).
\]

These are **EXACT SYMBOLIC IDENTITY** and **PROVED ANALYTICALLY**,
respectively. Existence of the ordinary numerical collision seed is not yet
validated.
