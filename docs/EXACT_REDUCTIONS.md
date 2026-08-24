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

Again there is an elementary Bernstein certificate on a larger interval.
For $t=2u$, the degree-20 Bernstein coefficients of $P_{20}(t/2)$ are

\[
\begin{gathered}
-1,-{19\over20},-{86\over95},-{1313\over1520},-{63901\over77520},
-{3823\over4864},-{185677\over248064},-{1177527\over1653760},\\
-{1819581\over2687360},-{27715771\over42997760},
-{58252257\over94595072},-{101898611\over171991040},
-{24804157\over42997760},\\
-{181712839\over317521920},-{37060991\over63504384},
-{157122943\over254017536},-{219023483\over317521920},\\
-{10188109\over12451840},-{25856203\over24903680},
-{3686723\over2621440},-{2112047\over1048576}.
\end{gathered}
\]

They are all strictly negative, proving $P_{20}<0$ on $0\le u\le1/2$.
The exact length-21 Sturm sequence, retained independently, has 10 sign
variations both at $0$ and at $83/200$.  Since the denominator is positive,

\[
\boxed{D^{(4)}(0)<0\quad(0<u\le\sqrt2-1).}
\]

The derivative formula is an **EXACT SYMBOLIC IDENTITY** and the Bernstein
argument makes the uniform sign **PROVED ANALYTICALLY**.
The local series begins

\[
D(t)={\ddot D(0)\over2}t^2+{D^{(4)}(0)\over24}t^4
 +{D^{(6)}(0)\over720}t^6+O(t^8),
\]

The sixth derivative and its sign are established next.  Later numerical sign
changes show that this finite jet still does not imply a global barrier.

Carrying the even force recurrence through one more order gives the new exact
identity

\[
D^{(6)}(0)=-{R_{30}(u)\over
8u^7(1-u)^7(1+u)^3(1+u^2)^5}.
\]

The recurrence writes
$q=q_0+q_2t^2+q_4t^4+q_6t^6+O(t^8)$, expands each pair force through $t^4$,
and matches $q''=2q_2+12q_4t^2+30q_6t^4+O(t^6)$.  This is independently
regressed against the displayed rational function.  Explicitly, for
$R=R_0+R_2\epsilon+R_4\epsilon^2$ and $d=|R_0|$, the first two force
coefficients of $R/|R|^3$ are

\[
 {R_2\over d^3}-{3R_0(R_0\cdot R_2)\over d^5},
\]
\[
 {R_4\over d^3}-{3R_2(R_0\cdot R_2)\over d^5}
 +R_0\left[-{3R_0\cdot R_4+\frac32|R_2|^2\over d^5}
 +{15(R_0\cdot R_2)^2\over2d^7}\right].
\]

For $t=2u$, the
degree-30 Bernstein coefficients of $R_{30}(t/2)$ are

\[
\begin{gathered}
19,{266\over15},{28861\over1740},{63103\over4060},
{6395887\over438480},{7813165\over570024},{97995461\over7600320},\\
{395397937\over32572800},{1903835447\over166483200},
{822381181\over76304800},{44652539959\over4395156480},
{1062904231\over110988800},\\
{46339562047\over5134438400},{57924715549\over6813004800},
{73076017417\over9128755200},{34682896469\over4604067840},
{147143231691\over20763443200},\\
{13083275107261\over1962145382400},
{142418163589111\over22673679974400},
{4249318181351\over716010946560},
{177734203151437\over31504481648640},\\
{1849150776667\over340957593600},
{43499899224473\over8182982246400},
{3826743850991\over711563673600},
{18951324099991\over3320630476800},\\
{644065041443\over99618914304},
{14565220793867\over1839118417920},
{178980837823\over17028874240},
{1746818009353\over116769423360},\\
{2824577023\over125829120},{37475266287\over1073741824}.
\end{gathered}
\]

All are positive. Thus $R_{30}>0$ on $0\le u\le1/2$ and

\[
\boxed{D^{(6)}(0)<0\quad(0<u\le\sqrt2-1).}
\]

This is an **EXACT SYMBOLIC IDENTITY** plus an analytic Bernstein sign proof.
The now-proved local sign pattern $D^{(2)}>0,D^{(4)}<0,D^{(6)}<0$ still does
not control the Taylor remainder or the later close encounters.

For twice oriented area
$\Delta_2=(q_2-q_1)\times(q_3-q_1)$, the initial brake also has
$\dot\Delta_2(0)=0$ and

\[
 \ddot\Delta_2(0)=
 {Q_{10}(u)\over2u^2(u-1)^2(1+u^2)^3},
\]

where

\[
 Q_{10}=u^{10}-10u^9+19u^8-28u^7-14u^6+8u^5-2u^4
 -4u^3-3u^2+2u-1.
\]

There is a shorter analytic sign certificate. Put $t=2u$.  In the degree-10
Bernstein basis $B_{k,10}(t)=\binom{10}{k}t^k(1-t)^{10-k}$,

\[
 Q_{10}(t/2)=\sum_{k=0}^{10}\beta_kB_{k,10}(t),
\]

where

\[
(\beta_0,\ldots,\beta_{10})=
\left(-1,-{9\over10},-{49\over60},-{181\over240},-{241\over336},
-{179\over252},-{991\over1344},-{3091\over3840},
-{10693\over11520},-{2919\over2560},-{1543\over1024}\right).
\]

Every coefficient is strictly negative, while the Bernstein basis is
nonnegative and sums to one on $0\le t\le1$. Therefore $Q_{10}<0$ on the
larger interval $0\le u\le1/2$.  As an independent exact regression, the
Sturm sequence has length $11$ and its signs at $0$ and $83/200$ are

\[
(-,+,+,-,-,+,+,+,-,+,+),\qquad
(-,-,+,-,-,+,+,+,-,-,+),
\]

respectively, with five variations in both strings. Hence

\[
 \boxed{\ddot\Delta_2(0)<0\qquad(0<u\le\sqrt2-1).}
\]

This is **PROVED ANALYTICALLY** uniform local motion toward the first syzygy,
not a proof that the
area is globally concave or that the first-syzygy type cannot change.

## Brake residual in a binary Levi--Civita chart

Select any pair, put $g=q_j-q_i=w^2$, $dt=|w|^2d\sigma$, and
$z=dw/d\sigma$. Let $G$ be the complementary Jacobi vector from the selected
pair's center of mass to the third body and $P=\dot G$. If $\mu_g$ and
$\mu_G$ are the two reduced masses, then

\[
 L=2\mu_g\operatorname{Im}(\overline w z)+\mu_G G\times P.
\]

Consequently, on every collision-free zero-angular-momentum segment with
$G\ne0$,

\[
 (z_r,z_i,G\cdot P)=0
 \quad\Longleftrightarrow\quad
 \hbox{all labelled inertial velocities vanish}.
\]

The forward implication uses $z=0\Rightarrow\dot g=0$, followed by
$L=0\Rightarrow G\times P=0$. The equations $G\times P=G\cdot P=0$ have
coefficient determinant $|G|^2$, so $P=0$. The converse is immediate, and
zero total momentum removes the common translational velocity. This is
**PROVED ANALYTICALLY**; exact regressions check angular-momentum conservation
in the pair/complement equations and the determinant. The chart remains
regular through arbitrarily close selected-pair encounters. At $G=0$ use a
different Jacobi tree or the global Hopf residual.

## Pair-angular-momentum torque factorization

Orient the cyclic relative vectors as

\[
 r_{12}=q_2-q_1,\qquad r_{23}=q_3-q_2,\qquad r_{31}=q_1-q_3,
\]

write $\Delta_2=(q_2-q_1)\times(q_3-q_1)$ for twice signed area, and put
$\ell_{ij}=r_{ij}\times\dot r_{ij}$. Direct cancellation of each pair's
central force gives

\[
\begin{aligned}
 \dot\ell_{12}&=m_3\Delta_2(r_{23}^{-3}-r_{31}^{-3}),\\
 \dot\ell_{23}&=m_1\Delta_2(r_{31}^{-3}-r_{12}^{-3}),\\
 \dot\ell_{31}&=m_2\Delta_2(r_{12}^{-3}-r_{23}^{-3}).
\end{aligned}
\]

This is an **EXACT SYMBOLIC IDENTITY** with a generic Cartesian regression.
For the normalized Pythagorean launch on the strict fundamental interval
$A>B$, $\Delta_2=AB>0$ and

\[
 (\dot\ell_{12}(0),\dot\ell_{23}(0),\dot\ell_{31}(0))
 \quad\hbox{has signs}\quad(-,+,-).
\]

At the isosceles endpoint the first component is zero. A hypothetical second
brake at $\tau$ must satisfy the three exact cancellation conditions obtained
by integrating the displayed equations from $0$ to $\tau$. They are not yet
a contradiction: syzygies reverse $\Delta_2$, and changes of distance order
reverse the other factors. The identity turns a torque-based proof into a
precise syzygy/order-transition problem.

There is nevertheless an immediate strict consequence on every
$0<u<\sqrt2-1$.  At both brakes all three $\ell_{ij}$ vanish.  Each torque
integrand is continuous before collision and has a strict initial sign.
Therefore an integral returning to zero must attain the opposite strict sign
somewhere.  Thus a second brake forces all three products

\[
 \Delta_2(r_{23}^{-3}-r_{31}^{-3}),\quad
 \Delta_2(r_{31}^{-3}-r_{12}^{-3}),\quad
 \Delta_2(r_{12}^{-3}-r_{23}^{-3})
\]

to reverse their launch signs $(-,+,-)$ before the brake.  In particular, if
$\Delta_2$ stays positive, then each pairwise side ordering must reverse at
some time:

\[
 r_{23}<r_{31},\qquad r_{31}>r_{12},\qquad r_{12}<r_{23},
\]

respectively, whereas initially $r_{12}>r_{23}>r_{31}$.  Hence no second
brake can precede the first syzygy unless all three pairwise-equality surfaces
have been crossed.  This **PROVED ANALYTICALLY** torque-reversal lemma is a
necessary event condition, not an assertion that the three reversals cannot
occur at different times.

The same variables give a coordinate-independent reduced brake residual away
from syzygy.  For arbitrary origin, total mass $M$, weighted position
$Q=\sum m_iq_i$, momentum $P=\sum m_i\dot q_i$, and angular momentum $L$,

\[
 m_1m_2\ell_{12}+m_2m_3\ell_{23}+m_3m_1\ell_{31}
 =ML-Q\times P.
\]

Hence $P=L=0$ and $\ell_{12}=\ell_{23}=0$ imply $\ell_{31}=0$.  If the
configuration is noncollinear and collision-free, write
$\dot r_{ij}=\lambda_{ij}r_{ij}$.  The closure identities
$r_{12}+r_{23}+r_{31}=0$ and
$\dot r_{12}+\dot r_{23}+\dot r_{31}=0$ then force all three $\lambda_{ij}$
to be one common $\lambda$.  In the center-of-mass frame
$\dot q_i=\lambda q_i$, and therefore $\dot I=2\lambda I$.  Since $I>0$,

\[
 \boxed{(\ell_{12},\ell_{23},\dot I)=0
 \quad\Longleftrightarrow\quad\hbox{a labelled brake}}
\]

on the noncollinear $P=L=0$ domain.  At a regular nonsyzygy $I$-maximum, the
remaining residual is just $(\ell_{12},\ell_{23})\in\mathbb R^2$.  This is
**PROVED ANALYTICALLY**.  Noncollinearity is indispensable: at a syzygy,
three unequal longitudinal velocities can have $P=0$, all pair angular
momenta zero, and $\dot I=0$.  The Hopf residual must cover that locus.

The degeneracy is exactly the syzygy factor.  Rotate a noncollinear
configuration so that the unweighted Jacobi vectors are
$X=(R,0)$ and $Y=(C,D)$, write their velocities as $U,V$, and put
$\alpha=m_1/(m_1+m_2)$ and $\kappa=\mu_1/\mu_2$. On $\dot I=L=0$, the two
constraints solve $V$ linearly from $U=(u_x,u_y)$.  The resulting map

\[
 U\longmapsto(\ell_{12},\ell_{23})
\]

has determinant

\[
 -\alpha RD\left(1+{\kappa R^2\over C^2+D^2}\right).
\]

Here $RD=X\times Y$ is proportional to signed triangle area, and every other
factor is positive. Moreover the complex shape residual becomes
$\zeta=2\mu_1R(u_x+iu_y)$ under the same two constraints. Thus the torque
plane and the $\zeta$ plane are exact invertible recharts of the same shape
velocity at every nonsyzygy $I$ event.  The torque chart's advantage is its
integrated evolution law, not a new zero set; its determinant explains the
unavoidable loss at syzygy.

## Initial side-order acceleration

The side-order part of the preceding event condition has a uniform launch
direction. Directly from Newton's accelerations,

\[
 (r_{12}-r_{23})''(0)=-{S_9(u)\over
 2u(1-u)^2(1+u)(1+u^2)^2},
\]

where

\[
S_9=u^9-9u^8+10u^7-10u^6-8u^5-16u^4-2u^3+2u^2-u+1.
\]

On $0\le u\le5/12$, its degree-9 Bernstein coefficients are

\[
1,{103\over108},{2377\over2592},{64471\over72576},{5027\over5832},
{3244279\over3919104},{96520723\over125411328},
{428088589\over644972544},{615514573\over1289945088},
{850511897\over5159780352}.
\]

They are strictly positive. Since $\sqrt2-1<5/12$, the first side gap has
strictly negative initial acceleration on the full fundamental interval.
The other gap factors more simply:

\[
 (r_{23}-r_{31})''(0)=
 -{(u^2+2u-1)(3u^2-2u+1)
 [u^2(u-1)^2+(u+1)^2]\over
 2u^2(1-u)^2(1+u^2)^2}.
\]

It is strictly positive for $0<u<\sqrt2-1$ and zero at the symmetric
endpoint. Thus the initial ordering $r_{12}>r_{23}>r_{31}$ begins by
compressing the first gap and widening the second. These are **PROVED
ANALYTICALLY** local statements. Ordinary bounded probes suggest both
monotonicities persist to first syzygy for middle parameters, but that global
ordering-cone statement remains **CONJECTURAL**, especially uniformly as
$u\to0$.

One full-shape component of that cone is nevertheless exact.  Write the
radial equation as

\[
 \ddot r_{ij}={\ell_{ij}^2\over r_{ij}^3}+\mathfrak g_{ij},
\]

where $\mathfrak g_{ij}$ is the radial projection of the Newton acceleration
and the first term is centrifugal.  Scale $r_{12}=1$. Every strict ordered
nondegenerate triangle $r_{12}>r_{23}>r_{31}$ is uniquely represented by

\[
 r_{23}=1-{tw\over2},\qquad
 r_{31}=1-t+{tw\over2},\qquad 0<t,w<1.
\]

Indeed $t=2(1-r_{23})+(r_{23}-r_{31})$, while $w=2(1-r_{23})/t$; the
triangle inequality is exactly $t<1$. Put
$u=(\sqrt2-1)v$, $0<v<1$. Exact substitution into the mutual-distance
equations expresses $\mathfrak g_{23}-\mathfrak g_{31}$ as a polynomial over

\[
(tw-2)^3[-1-(3-2\sqrt2)v^2](tw-2t+2)^3,
\]

whose denominator is positive in the open cube.  The numerator has tensor
degree $(7,6,2)$.  All 168 exact algebraic Bernstein coefficients on
$[0,1]^3$ are nonnegative: 31 are zero and 137 are strictly positive.
Every tensor Bernstein basis function is positive in the open cube, hence

\[
 \boxed{\mathfrak g_{23}-\mathfrak g_{31}>0}
\]

throughout the strict ordered shape cone and strict fundamental mass
interval. This is **PROVED BY COMPUTER-ASSISTED ARGUMENT** using exact
$\mathbb Q(\sqrt2)$ arithmetic; the coefficient count and denominator are
deterministically regressed. It covers arbitrarily close positive
separations, though its margin is not uniform at the cube boundary.

Consequently

\[
(r_{23}-r_{31})''=
{\ell_{23}^2\over r_{23}^3}-{\ell_{31}^2\over r_{31}^3}
+(\mathfrak g_{23}-\mathfrak g_{31}).
\]

The missing invariant-cone lemma is now localized to controlling the
centrifugal difference along the brake-launched orbit. It cannot simply be
dropped: ordinary trajectories show it can become negative near the first
close passage, while the proved gravitational margin remains larger.

The first gravitational gap has the complementary sign on the entire ordered
right/obtuse region.  In the same $(t,w)$ coordinates,

\[
r_{23}^2+r_{31}^2-1
={t^2w^2-2t^2w+2t^2-4t+2\over2}.
\]

For fixed $t$ its minimum on $0\le w\le1$ occurs at $w=1$.  If
$t\le2-\sqrt2$, that minimum is nonnegative. Therefore every ordered strict
right or obtuse triangle has $t>2-\sqrt2$, apart from the excluded symmetric
endpoint. Put

\[
t=2-\sqrt2+(\sqrt2-1)s,qquad0<s<1.
\]

After the same mass substitution $u=(\sqrt2-1)v$, the numerator of
$\mathfrak g_{12}-\mathfrak g_{23}$ again has tensor degree $(7,6,2)$ on the
$(s,w,v)$ cube. Its 168 exact Bernstein coefficients are all nonpositive: 18
are zero and 150 are strictly negative. The factored denominator is positive
in the open cube. Hence

\[
\boxed{\mathfrak g_{12}-\mathfrak g_{23}<0}
\]

throughout the strict ordered right/obtuse region. This is a second **PROVED
BY COMPUTER-ASSISTED ARGUMENT** exact-$\mathbb Q(\sqrt2)$ inequality, with
independent Cartesian force regressions. Thus gravity points strictly into
both side-gap faces in the candidate cone. To prove the full cone one must
still show that the orbit stays right/obtuse and that each possibly adverse
centrifugal difference is dominated by its gravitational margin.

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
respectively. The analytic tail enclosure and correlated CAPD interval Newton
prove a transverse selected-primary limiting collision with
$1.2679351752<\kappa_c<1.2679351759$ and
$-3.52212<D_c<-3.38401$. A second collision-adapted chart now proves a
distinct transverse opposite-primary collision with
$1.2640119191<\kappa_2<1.2640119311$. These are **PROVED BY
COMPUTER-ASSISTED ARGUMENT**; neither is a finite-mass Pythagorean collision or
brake.
