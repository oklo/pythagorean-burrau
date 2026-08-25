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

### Scalar torque-history comparison

The two torque integrals admit a useful dimensionless reduction.  On a
positive-area ordered segment put $R=r_{12}$, $p=r_{23}$, $q=r_{31}$ and

\[
 F=\Delta_2(q^{-3}-R^{-3}),\qquad
 G=\Delta_2(p^{-3}-R^{-3}),
\]

so $0<G<F$.  For ${\cal A}(t)=\int_0^tF\,ds$ and
${\cal C}(t)=\int_0^tG\,ds$, define

\[
 \eta={{\cal C}\over{\cal A}}
 ={m_1\over m_2}{-\ell_{31}\over\ell_{23}},
 \qquad
 k={G\over F}={p^{-3}-R^{-3}\over q^{-3}-R^{-3}}.
\]

Direct quotient differentiation gives the exact scalar equation

\[
 \boxed{\dot\eta={F\over{\cal A}}(k-\eta)}.
\]

Thus $\eta$ is a positively weighted history average of $k$.  In particular,
if $k$ is strictly decreasing, then
$k(t)<\eta(t)<k(0)$ for every $t>0$ on that ordered segment. This is an
**EXACT SYMBOLIC IDENTITY** and is the desired bridge from torque history to
current centrifugal terms.

In normalized side ratios $x=p/R$, $y=q/R$,

\[
k={y^3(1-x^3)\over x^3(1-y^3)},\qquad
{\dot k\over k}=3\left{{\dot y\over y(1-y^3)}
                    -{\dot x\over x(1-x^3)}\right\}.
\]

The first derivative itself has a sharper algebraic reduction.  Use shape
time $ds=dt/R^{3/2}$, put $W=\ell_{23}/\sqrt R>0$ and
$\delta=\Delta_2/R^2>0$, and retain $m=m_1$, $n=m_2$.  Define

\[
\begin{aligned}
 B={}&-nx^5-nx^3y^2+nx^3+nx^2+2ny^5-ny^2-n\\
    &+x^5y^2-x^3y^4+x^3y^2-x^2y^5+y^7+y^5-2y^2,\\
 N={}&2mx^5-mx^2y^3-mx^2-my^5+my^3+my^2-m\\
    &+x^7-x^5y^2+x^5-x^4y^3+x^2y^5+x^2y^3-2x^2,
\end{aligned}
\]

and

\[
 h={y^2N\over x^2B},\qquad
 \mathcal A={-3B\over
 2my^2(x-1)(y-1)(x^2+x+1)(y^2+y+1)}.
\]

Solving the three pair-angular-momentum constraints for normalized shape
velocity, with the homothetic rate left free, gives the exact cancellation
of that free rate:

\[
 \boxed{J_s={W\over\delta}\mathcal A(\eta-h)},
 \qquad J=\log k.
\]

This is an **EXACT SYMBOLIC IDENTITY**.  Moreover
$\mathcal A>0$ on the entire strict ordered triangle cone and strict
fundamental mass interval.  Indeed, after

\[
 x=1-{tw\over2},\qquad y=1-t+{tw\over2},\qquad
 u=(\sqrt2-1)v,
\]

the rational expression $-B$ has tensor degree $(7,6,2)$.  Its numerator has
168 exact $\mathbb Q(\sqrt2)$ Bernstein coefficients, 134 strictly negative
and 34 zero, while its denominator is

\[
 -16\{1+(3-2\sqrt2)v^2\}<0.
\]

Thus $-B>0$, hence $B<0$ and $\mathcal A>0$.  This is **PROVED BY
COMPUTER-ASSISTED ARGUMENT** using exact arithmetic.  Consequently

\[
 \boxed{J_s<0\quad\Longleftrightarrow\quad\eta<h(u,x,y)}.
\]

The threshold also lies strictly above the instantaneous ratio everywhere:

\[
 \boxed{h(u,x,y)>k(x,y)}.
\]

To prove this, take the numerator of $h-k$ before the ordered-cube
substitution above.  After substitution it has tensor degree $(11,11,2)$.
The numerator and its mass denominator have opposite strict signs: all 432
exact Bernstein coefficients of the former are nonpositive (317 negative,
115 zero), while the latter is

\[
 -512\{1+(3-2\sqrt2)v^2\}<0.
\]

The original common denominator of $h-k$ is positive because it contains
the product $(y-1)B>0$ and otherwise positive factors.  Hence $h-k>0$ in
the open cube.  This is a second **PROVED BY COMPUTER-ASSISTED ARGUMENT**
exact certificate.

At the initial tied shape, $eta(0+)=k(0)$ and direct factorization gives

\[
 h(0)-k(0)=
 {8u(1+u^2)^3(u^2+2u-1)
 (2u^4-3u^3+3u^2+u+1)\over
 (u-1)^5(u+1)^4(u^3-u^2+3u+1)
 (u^4+2u^3+6u^2+2u+1)}>0
\]

for $0<u<\sqrt2-1$.  The two signed factors
$u^2+2u-1$ and $(u-1)^5$ are both negative and every other factor is
positive.  The launch therefore lies strictly on the decreasing side of the
threshold.  A first return of $J_s$ to zero is exactly the scalar contact
$\eta=h$, not merely a three-component velocity condition.  The exact
$u=2/5$ ambient first-return obstruction below satisfies this equality,
showing that the remaining task is to prove that the *brake-generated*
history never reaches the explicit graph $\eta=h$.

The derivative at a hypothetical contact has one further exact reduction.
Let $X=\delta x_s/W$ and $Y=\delta y_s/W$.  Direct elimination gives

\[
 X={-2\eta nx^2+\eta x^4-\eta x^2y^2-\eta x^2
       -mx^2-my^2+m-x^4+x^2y^2+x^2\over2mx},
\]

\[
 Y={-\eta nx^2-\eta ny^2+\eta n+\eta x^2y^2-\eta y^4+\eta y^2
       -2my^2-x^2y^2+y^4-y^2\over2my}.
\]

At $\eta=h$ define

\[
 S=h_xX(h)+h_yY(h),\qquad
 P=m\delta^2(y^{-3}-1)(k-h)<0.
\]

Combining the exact equations for $\eta_s,x_s,y_s$ yields

\[
 \boxed{W\delta(\eta-h)_s=P-ZS},\qquad Z=W^2.
\]

Thus a first contact is automatically inward when $S\ge0$.  On the only
dangerous region $S<0$, it is inward exactly when

\[
 \boxed{Z<Z_J:={P\over S}}.
\]

Both sign regions occur with a physically admissible contact value
$0<h<1$.  Exact rational evaluation gives $S>0$ at
$(u,x,y)=(1/100,199/200,3/200)$ and $S<0$ at
$(1/3,3/5,41/100)$.  Hence the partition is genuine rather than an artifact
of an unnecessarily broad domain.

This is an **EXACT SYMBOLIC IDENTITY** and a new Level-E reduction: global
monotonicity of $k$ follows from a single amplitude estimate only on the
explicit semialgebraic region $S<0$.  At the exact $u=2/5$ first-return
witness below, $P<0$, $S<0$, and the energy-normalized amplitude satisfies

\[
 {Z\over Z_J}=1.05745644351720\ldots>1.
\]

This exactly accounts for its outward contact and positive $J''$.  The
remaining trajectory theorem must keep $Z$ below $Z_J$ on reachable
dangerous contacts; total energy does not do so.

The torque-contact threshold $Z_J$ and the second-gap threshold
$Z_2=(\mathfrak g_{23}-\mathfrak g_{31})/(-C_2)$ have no global ordering,
even when both are relevant and $0<h<1$.  Exact rational evaluations give

\[
 {Z_J\over Z_2}=0.851103582895812\ldots<1
 \quad\hbox{at}\quad
 (u,x,y)=\left({1\over3},{3\over5},{41\over100}\right),
\]

but

\[
 {Z_J\over Z_2}=5.95447971227083\ldots>1
 \quad\hbox{at}\quad
 (u,x,y)=\left({1\over10},{19\over20},{1\over10}\right).
\]

The inequalities are checked by exact rational cross-multiplication.  Thus
neither amplitude condition subsumes the other; a common reachable theorem
must establish $Z<\min(Z_J,Z_2)$ on their respective dangerous regions, or
use a different invariant that implies both.

There is nevertheless an exact ordering on the terminal ordered-syzygy
face.  Continue $Z_J=P/S$ to that face after cancelling the common
twice-area-squared factor in $P$ and $S$.  With

\[
 p=1-q,\qquad
 \eta_{\rm col}={q(m+p)\over p(n+q)},\qquad
 0<q<{n\over m+n},
\]

direct substitution gives the two identities

\[
 \boxed{h(m,n,p,q)=\eta_{\rm col}},\qquad P=S=0.
\]

Thus the apparent $0/0$ in $Z_J$ is not a singular threshold.  Both $P$
and $S$ are exactly divisible by the squared twice-area
$\delta^2$, and cancelling that common factor gives the path-independent
rational extension

\[
 Z_J^{\rm syz}=
 {2m^2(n+q)^2(q-1)(q^2-q+2)N_J
  \over q\{mn+mq^2+n(1-q)^2\}D_J},
\]

where

\[
\begin{aligned}
N_J={}&mq^5-2mq^4+mq^3-mq^2+2mq-m\\
 &+nq^5-3nq^4+3nq^3+2q^3-3q^2+3q-1,\\
D_J={}&-2mnq^3+3mnq^2-7mnq+3mn\\
 &+2mq^5-5mq^4+5mq^3-5mq^2\\
 &+2nq^5-5nq^4+5nq^3-5nq+3n.
\end{aligned}
\]

On the same face write

\[
 C_2=p^{-3}-{n^2\eta_{\rm col}^2\over m^2q^3}
 ={-E_2\over m^2q(n+q)^2(q-1)^3},
\]

and factor the difference of the two critical amplitudes as

\[
 Z_2-Z_J^{\rm syz}=
 {-m^2(n+q)^2(q-1)(2q-1)Q\over
 q\{mn+mq^2+n(1-q)^2\}E_2D_J}.
\]

Here

\[
\begin{aligned}
E_2={}&2m^2n^2q-m^2n^2+2m^2nq^2+m^2q^3
       -2mn^2q^2+4mn^2q-2mn^2\\
     &+n^2q^3-3n^2q^2+3n^2q-n^2,
\end{aligned}
\]

and $Q$ has total mass degree five and $q$-degree ten; its deterministic
exact expression is generated by
`ordered_syzygy_torque_amplitude_sign_cores`.  Their signs, as well as those
of $N_J,D_J$, are
certified on the complete tied square

\[
 u=(\sqrt2-1)v,\qquad q={nz\over m+n},qquad
 0<v\le1,\quad0<z<1.
\]

After clearing only positive mass and mass-sum denominators, the four cores
have the following exact tensor-Bernstein certificates:

| core | bidegree | strict coefficients | zero coefficients | sign |
|---|---:|---:|---:|---:|
| $N_J$ | $(11,5)$ | 71 | 1 | negative |
| $D_J$ | $(12,5)$ | 71 | 7 | positive |
| $E_2$ | $(11,3)$ | 39 | 9 | negative |
| $Q$ | $(26,10)$ | 274 | 23 | positive |
| numerator of $Z_J^{\rm syz}-1$ | $(27,10)$ | 285 | 23 | positive |

Every Bernstein basis function is positive in the open square.  On the
equal-mass edge $v=1$, all edge coefficients have the displayed strict sign
except the single $z=1$ endpoint coefficient, so strictness also holds for
$0<z<1$.  Since $q<1/2$, all remaining factor signs in the displayed
formulas are manifest.  The already proved gravitational ordering gives
$G_2=\mathfrak g_{23}-\mathfrak g_{31}>0$.  Consequently

\[
 \boxed{1<Z_J^{\rm syz}<Z_2}
\]

throughout the torque-compatible ordered-syzygy face.  This is **PROVED BY
COMPUTER-ASSISTED ARGUMENT** in exact $\mathbb Q(\sqrt2)$ arithmetic.
Although the two thresholds cross in the interior shape cone, the torque
threshold is the unique stronger terminal amplitude obligation.  The result
does not prove that a brake-generated orbit satisfies $Z<Z_J^{\rm syz}$;
that remains a history/reachability theorem.

The critical scale is strictly ordered along every fixed-mass syzygy face:

\[
 \boxed{\partial_qR_J<0\qquad(0<q<n/(m+n)).}
\]

The derivative denominator is
$q^2(1-q)^2(m^2n^2+1)D_J^2>0$.  After removing the positive factor $mn$
and applying the tied-square substitution, its numerator has bidegree
$(30,12)$.  Its 403 exact $\mathbb Q(\sqrt2)$ Bernstein coefficients are
374 negative and 29 zero; ten negative edge coefficients remain at $v=1$,
$0<z<1$.  This exact monotonicity organizes the scale deficit but does not
close it: reachable first syzygies can still have $R<R_J$.

The equal-mass torque edge is a singular corner.  Put

\[
 v=1-\varepsilon,
 \qquad z=1-\lambda\varepsilon,
 \qquad \kappa={28-3\sqrt2\over11}.
\]

First directional jets of the exact rational functions give

\[
 \lim Z_J^{\rm syz}
 ={Z_0+\kappa\lambda Z_\infty\over1+\kappa\lambda},
 \qquad
 \lim R_J
 ={R_0+\kappa\lambda R_\infty\over1+\kappa\lambda},
\]

where

\[
\begin{aligned}
 Z_0&={21(1+\sqrt2)\over22},&
 Z_\infty&={3836+2709\sqrt2\over6128},\\
 R_0&={11+2\sqrt2\over55},&
 R_\infty&={-361+2273\sqrt2\over3830}.
\end{aligned}
\]

Thus $Z_0>Z_\infty>1$ and $R_0<R_\infty$: taking equal masses first and
taking the torque edge first give different limits.  At the actual symmetric
first syzygy, a pinned CAPD enclosure proves $Z_*<1$.  A separate $C^1$
Poincare calculation for the tied launch tangent proves the dynamical corner
slope $\lambda_*=z_v(1)>18>0$.  Smooth event continuation therefore yields

\[
 \boxed{Z<1<Z_J^{\rm syz}}
\]

at the continued first syzygy for all $v<1$ in some one-sided neighborhood
of the isosceles endpoint.  This closes the terminal first-syzygy amplitude
obligation locally.

A third pinned interval calculation closes the preceding interior contact
in the same one-sided neighborhood.  For the odd tied tangent write

\[
 a=H\dot x-x\dot H,\qquad
 a_v=c\dot H+b\dot x-x\dot b-H\dot c,
\]

\[
 d={\sqrt{x^2+H^2}\over2x},\qquad
 Y={xc-Hb\over2x\sqrt{x^2+H^2}}.
\]

Exact differentiation of the torque threshold gives

\[
 g(t):=\partial_v(\eta-h)(1,t)
 =-\sqrt2-2{a_v\over a}-A(d)Y-B(d),
\]

where the explicit rational functions $A,B$ are recorded in
`ISOSCELES_SYZYGY_THRESHOLD.md`.  Full Cartesian variational regression
independently verifies the reduced eight-dimensional system and every
threshold coefficient.  The launch quotient extends analytically and

\[
 g(0)={32+8\sqrt2\over7}>0.
\]

CAPD step tubes prove $g>0$ on the complete open endpoint arc and
$g_t<0$ on a terminal neighborhood; the exact syzygy identity gives
$g(\tau(1))=0$.  The same cover proves $d<1$ and $Y>0$.  Analytic division
first by $v-1$ and then by the transverse event factor $t-\tau(v)$ yields

\[
 \boxed{\eta<h\quad(0<t<\tau(v))}
\]

for every $v<1$ sufficiently close to one.  It also gives the strict side
ordering $r_{12}>r_{23}>r_{31}$ and hence excludes every second brake on or
before this first-syzygy arc.  Thus both the pre-syzygy noncontact and the
terminal amplitude obligations are locally closed.  Post-encounter
recurrence remains open.  The complete certificate is in
`ISOSCELES_SYZYGY_THRESHOLD.md`.

The exact kinetic-energy decomposition identifies that history theorem more
sharply.  Restore the syzygy scale $R=r_{12}$ and put

\[
 D=mn+mq^2+n(1-q)^2,qquad E=(m+n)q-n,qquad M=m+n+1.
\]

In Newtonian shape time $ds=dt/R^{3/2}$, let
$\sigma=R_s/R$ and $Q=q_s$.  Longitudinal momentum reduction and completion
of squares give

\[
\begin{aligned}
 2K_\parallel R
 &= {D\over M}\left(\sigma+{E\over D}Q\right)^2
    +{mn\over D}Q^2\\
 &= {R\dot I^2\over4I}+{mn\over D}Q^2,
 \qquad I={R^2D\over M}.
\end{aligned}
\]

The transverse part is exactly $2K_\perp R=FZ$, with

\[
 F={nD\over m(1-q)^2(n+q)^2}>0.
\]

Hence the Burrau energy equation is

\[
 FZ+\mathcal L=2(U-U_0R),\qquad
 \mathcal L:={R\dot I^2\over4I}+{mn\over D}Q^2,
 \qquad U=mn+{n\over1-q}+{m\over q}.
\]

Define the critical physical scale

\[
 R_J={U-FZ_J^{\rm syz}/2\over U_0}.
\]

Then the remaining terminal amplitude condition is *exactly*

\[
 \boxed{Z<Z_J^{\rm syz}\quad\Longleftrightarrow\quad
 \mathcal L>2U_0(R_J-R)}.
\]

This is an **EXACT SYMBOLIC IDENTITY**.  It separates the missing theorem
into a scale deficit and a positive longitudinal kinetic form.  If
$R\ge R_J$, energy proves the amplitude bound automatically.  When
$R<R_J$, a quantitative lower bound on dilational or collinear shape speed
is indispensable.

Strict terminal signs do not provide such coercivity.  Put
$H=n-(m+n)q>0$ and

\[
 c_-={1-2q\over2},\qquad c_+={D\over H}.
\]

For tied fundamental masses $m\ge n$,

\[
 2D-H(1-2q)=2mn+(m-n)q+n>0,
\]

so $c_-<c_+$.  With $c=(c_-+c_+)/2$ and any $\varepsilon>0$, choose

\[
 \sigma=-\varepsilon,qquad Q=-c\varepsilon.
\]

Then, in scale-normalized form,

\[
 q\sigma+Q<0,qquad
 (1-2q)\sigma-2Q>0,qquad
 D\sigma+EQ<0.
\]

Thus $r_{31}$ decreases, $r_{23}-r_{31}$ increases, and $\dot I<0$, all
strictly, while $\mathcal L=O(\varepsilon^2)\to0$.  For every fixed
$R<R_J$, sufficiently small $\varepsilon$ and the energy-determined
transverse amplitude therefore give an ambient state with all these signs
but $Z>Z_J^{\rm syz}$.  This is **PROVED ANALYTICALLY** and disproves a
terminal-current-sign repair.  The state is not asserted brake-reachable;
the necessary lower bound must retain quantitative information accumulated
from the initial brake.

There is a new global sign in its second derivative.  Let
$J=\log k$.  The part of $\ddot J$ obtained by setting the instantaneous
velocity to zero while retaining Newton's acceleration satisfies

\[
 \boxed{\ddot J_{\rm grav}<0}
\]

throughout the strict ordered right/obtuse cone and strict fundamental mass
interval. In the $(s,w,v)$ cube above, its rational numerator has tensor
degree $(9,9,2)$.  All 300 exact $\mathbb Q(\sqrt2)$ Bernstein coefficients
are nonnegative, with 268 strictly positive.  The factored denominator is

\[
 -4096(1+u^2)p^3q^3(1-p^3)(1-q^3)<0.
\]

Independent Cartesian-force evaluations regress the formula. This is a
**PROVED BY COMPUTER-ASSISTED ARGUMENT** global curvature contribution,
including arbitrarily close positive separations.

At the initial brake the velocity contribution vanishes, and an independent
exact reduction gives

\[
 \ddot J(0)=
 {3(1+u^2)^4(u^2+2u-1)
 (2u^4-3u^3+3u^2+u+1)
 \over
 u^3(1-u)^3(u^4+3)(u^4+2u^3+6u^2+2u+1)}<0
\]

for $0<u<\sqrt2-1$.  The quartic is positive because it equals
$2u^4+3u^2(1-u)+u+1$; the only signed factor is
$u^2+2u-1$.  Hence $k$ initially decreases analytically, with equality only
at the symmetric endpoint.

The total curvature is
$\ddot J=\ddot J_{\rm grav}+Q_J(q,\dot q)$, where $Q_J$ is the velocity
Hessian term.  Its sign is not controlled by instantaneous constraints, even
on the first-return boundary $\dot J=0$.  An exact witness uses

\[
 u={2\over5},\quad(m_1,m_2)=\left({21\over29},{20\over29}\right),
 \quad(R,p,q)=\left(1,{39\over40},{1\over30}\right).
\]

In the unit-$R$ Jacobi gauge, set $U=(0,-1)$ and solve the two exact linear
conditions $L=\dot J=0$ for the complementary velocity. The solution has

\[
 (\ell_{12},\ell_{23},\ell_{31})
 =\left(-1,
 {28914232361390649\over36366761131529200},
 -{122841961770469\over1818338056576460}\right),
\]

so it has precisely the pre-syzygy torque signs.  Nevertheless
$Q_J=8951.51393211\ldots>0$.  Scale the shape to $R=1/2$ and choose the
velocity amplitude from $H=-U_0$. Exact arithmetic then gives

\[
 R^3\ddot J=10682.0701224264\ldots>0.
\]

This **DISPROVES** any first-return proof based only on current ordered
right/obtuse shape, energy, $L=0$, $\dot J=0$, and the three torque signs. The
witness is not claimed reachable from the brake. Ordinary probes find both
$k$ and $\dot J$ strictly decreasing/negative to first syzygy for all
resolved middle parameters, so the remaining theorem is specifically a
reachable-history inequality for $Q_J$, not an ambient cone inequality.

### Optimal instantaneous energy--torque reduction, and its obstruction

The first centrifugal domination problem can be reduced exactly, but not
solved from instantaneous invariants alone.  Normalize $r_{12}=1$, put
$q_1=(0,0)$, $q_2=(1,0)$, and use translation-reduced Jacobi velocity
$V_J=(U_x,U_y,V_x,V_y)^T$ with mass matrix

\[
 M_v=\operatorname{diag}(\mu_1,\mu_1,\mu_2,\mu_2).
\]

Let $C$ be the $3\times4$ matrix whose rows evaluate total angular momentum,
$\ell_{23}$, and $\ell_{31}$ on $V_J$.  On a noncollinear shape $C$ has full
row rank.  Prescribing

\[
 (L,\ell_{23},\ell_{31})=(0,a,-xa)
\]

and minimizing the positive quadratic form $2K=V_J^TM_vV_J$ gives the exact
Gram-inverse formula

\[
 2K_{\min}=a^2F,
 \qquad
 F=(0,1,-x)(CM_v^{-1}C^T)^{-1}(0,1,-x)^T>0.
\]

At physical scale $R$, the right side is $a^2F/R^2$.  This is an **EXACT
SYMBOLIC IDENTITY**, independently regressed against direct matrix inversion.
On the pre-syzygy torque-sign cone set $x=(m_2/m_1)h$, $0<h<1$.  The weighted
pair-angular-momentum identity gives

\[
 -\ell_{12}={a(1-h)\over m_1},
\]

so the first centrifugal coefficient is

\[
 C_1={(1-h)^2\over m_1^2}-{1\over p^3},
 \qquad p=r_{23}/r_{12}.
\]

When $C_1>0$, energy $K=U_{\rm sh}/R-U_0$ yields the sharp instantaneous
upper margin

\[
 \mathcal M_1=\mathfrak g_{12}-\mathfrak g_{23}
              +{2U_{\rm sh}C_1\over F};
\]

the omitted term $-2U_0RC_1/F$ only improves the inequality.  Unfortunately
$\mathcal M_1$ is not negative on the full cube. At the exact interior point

\[
 (s,w,v,h)=\left({99\over100},{1\over10^6},
 {99\over100},{1\over10^6}\right)
\]

in the preceding right/obtuse parameterization, exact
$\mathbb Q(\sqrt2)$ arithmetic gives $C_1>0$ and

\[
 \mathcal M_1=93.2280669052696428\ldots>0.
\]

Thus the optimal static implication from shape, $H=-U_0$, $L=0$, and the
three torque signs to $(r_{12}-r_{23})''<0$ is **DISPROVED**.  This point is
not claimed reachable from the brake.  A successful cone theorem must use
the integrated torque history or an equivalent reachability constraint.

### Exact first-gap concavity on the ordered-syzygy face

The preceding interior obstruction disappears on the collision-free syzygy
face.  Write $(m_1,m_2,m_3)=(m,n,1)$, scale $r_{12}=1$, and suppose body 3
lies between bodies 1 and 2.  Put

\[
 q=r_{31},\qquad p=r_{23}=1-q,
 \qquad a=\ell_{23}>0,
 \qquad \eta={m\over n}{-\ell_{31}\over\ell_{23}}.
\]

Total transverse momentum and zero total angular momentum determine all
three transverse velocities once $a$ is fixed.  Exact elimination gives

\[
 \eta={q(m+p)\over p(n+q)},\qquad
 -{\ell_{12}\over a}={1-\eta\over m},
\]

and

\[
 2K\ge a^2F,\qquad
 F={n\{mn+mq^2+np^2\}\over mp^2(n+q)^2}>0.
\]

The inequality allows arbitrary radial velocities; equality is the unique
transverse kinetic energy.  The strict launch torque signs are equivalent on
this face to

\[
 0<\eta<1\quad\Longleftrightarrow\quad
 0<q<{n\over m+n}.
\]

At energy $H=-U_0$, with
$U=mn+n/p+m/q$, one has $K=U-U_0<U$.  The first side-gap acceleration is

\[
 (r_{12}-r_{23})''=
 \mathfrak g_{12}-\mathfrak g_{23}+a^2C_1,
 \qquad
 C_1={(1-\eta)^2\over m^2}-{1\over p^3}.
\]

If $C_1\le0$, the already proved gravitational inequality makes this
strictly negative.  If $C_1>0$, the energy bound gives

\[
 (r_{12}-r_{23})''
 <\mathcal M_{\rm syz}:=
 \mathfrak g_{12}-\mathfrak g_{23}+{2UC_1\over F}.
\]

It remains only to determine the sign of this explicit rational function.
Set

\[
 u=(\sqrt2-1)v,\qquad
 m={1-u^2\over1+u^2},\qquad
 n={2u\over1+u^2},\qquad
 q={nz\over m+n},\qquad 0<v,z<1.
\]

Before this substitution the denominator of $\mathcal M_{\rm syz}$ is

\[
 mnq^2(1-q)^2\{mn+mq^2+n(1-q)^2\}>0.
\]

Clearing the additional positive mass and mass-sum denominators produces a
bidegree $(20,6)$ polynomial in $(v,z)$.  Its 147 exact
$\mathbb Q(\sqrt2)$ tensor-Bernstein coefficients are all nonpositive: 133
are strictly negative and 14 are zero.  Because every Bernstein basis
function is positive in the open square, the polynomial and hence
$\mathcal M_{\rm syz}$ are strictly negative there.  Therefore

\[
 \boxed{(r_{12}-r_{23})''<0}
\]

at every collision-free ordered syzygy with body 3 in the middle, strict
pre-syzygy torque signs, $P=L=0$, and the tied fundamental masses.  This is
**PROVED BY COMPUTER-ASSISTED ARGUMENT** in exact arithmetic.  The symbolic
test independently checks the denominator, the positive clearing factor,
the transverse kinetic minimization, and every Bernstein sign.

The result does not prove that the brake-launched orbit remains in the
ordered right/obtuse cone until syzygy, nor that the first gap is monotone
before it.  It does prove that the first adverse centrifugal term cannot
overturn the desired concavity at the terminal ordered-syzygy face.  The
second gap and the reachable-history interior remain open.

There is no analogous static theorem for the second gap, even on this face.
An exact ambient obstruction already occurs at the $3{:}4{:}5$ masses.  Take

\[
 u={1\over3},\quad (m,n)=\left({4\over5},{3\over5}\right),\quad
 R=1,\quad q={3\over700},\quad p={697\over700}.
\]

This is the syzygy parameter $z=1/100$ above, and
$\eta=419/32759\in(0,1)$.  Set radial velocities to zero and choose
$a=\ell_{23}>0$ by

\[
 a^2=Z={476958362267\over2867548600}.
\]

The unique transverse velocities at this $a$ have $P=L=0$ and
$2K=a^2F=2(U-U_0)$, so the total energy is exactly the Burrau energy.  The
pair angular momenta have signs $(-,+,-)$, and

\[
 {\dot\Delta_2\over a}=-{292607\over131036}<0,
\]

so the state even has the correct orientation for a first positive-to-negative
syzygy crossing.  Gravity alone gives
$\mathfrak g_{23}-\mathfrak g_{31}>0$, but the exact centrifugal coefficient
is negative and the full acceleration is

\[
 (r_{23}-r_{31})''
 =-{96354167469624287\over1827657180810}<0.
\]

This **DISPROVES** the implication from tied masses, Burrau energy,
$P=L=0$, strict launch torque signs, ordered collision-free syzygy geometry,
and crossing direction to $(r_{23}-r_{31})''>0$.  The state is not claimed
reachable from the brake.  In the two-scalar formulation below, its critical
amplitude is

\[
 Z_*={\mathfrak g_{23}-\mathfrak g_{31}\over-C_2}
 ={4764595771490855887\over39314226426562500},
 \qquad {Z\over Z_*}=1.3724399581\ldots>1.
\]

Thus the exact remaining second-face obligation is a reachability estimate
$Z<Z_*(x,y,\eta)$ wherever its centrifugal coefficient $C_2$ is negative.
Neither energy nor first-crossing kinematics supplies it.

For the latter, two exact dimensionless formulas isolate the remaining
history variable.  With $R=r_{12}$, $x=r_{23}/R$, $y=r_{31}/R$,
$Z=\ell_{23}^2/R$, and the same $\eta$, the centrifugal parts of the two gap
accelerations after multiplication by $R^2$ are

\[
 Z\left\{{(1-\eta)^2\over m^2}-x^{-3}\right\},\qquad
 Z\left\{x^{-3}-{n^2\eta^2\over m^2y^3}\right\}.
\]

If $ds=dt/R^{3/2}$, $W=\sqrt Z=\ell_{23}/\sqrt R$,
$\delta=\Delta_2/R^2$, and $\sigma=d\log R/ds$, then

\[
 W_s=m\delta(y^{-3}-1)-{\sigma W\over2},\qquad
 \eta_s={m\delta(y^{-3}-1)\over W}(k-\eta).
\]

Thus the two centrifugal gaps depend on the common amplitude $Z$ and the
single weighted-history ratio $\eta$; this is an **EXACT SYMBOLIC IDENTITY**,
not yet a closed invariant system because $(x,y,\delta,\sigma)$ also evolve.

The most direct critical-amplitude barrier is not pointwise invariant.  A
sharper exact ambient obstruction again uses $u=1/3$, but now at the strict
ordered obtuse shape

\[
 x={499\over500},\qquad y={1\over20},\qquad
 1-x^2-y^2={187\over125000}>0,qquad
 \eta={3\over20}.
\]

This value of $eta$ even satisfies the necessary monotone-history envelope

\[
 k={748501\over993887740501}<\eta<
 k(0)={1647\over6272}.
\]

Here

\[
 \mathfrak g_{23}-\mathfrak g_{31}
 ={1402530187533191\over1941429671875}>0,
 \qquad
 C_2=-{49821857095\over497005996}<0,
\]

so put the state exactly on the critical surface with

\[
 Z=Z_*=-{\mathfrak g_{23}-\mathfrak g_{31}\over C_2}
 ={5610120750132764\over778466517109375}.
\]

The pair-angular-momentum constraints leave one homothetic rate.  Choose its
exact kinetic-energy minimizer and then the physical scale

\[
 R={717603860876220132499755190629\over
       669041277379938998505911848960}>0.
\]

The resulting algebraic state has $P=L=0$, energy $-U_0$, torque signs
$(-,+,-)$, and decreasing normalized area
$\delta_s=-5.8202956316\ldots<0$.  Nevertheless exact radical arithmetic
gives

\[
 {d\over ds}\log{Z\over Z_*}
 =50.8829734688\ldots>0.
\]

Both displayed decimal signs are regressions of factorizations into a
strictly signed rational factor times the square root of a positive integer;
the exact expressions are returned by
`second_gap_barrier_outward_contact_obstruction`.  This **DISPROVES** a
pointwise inward-vector-field proof for $Z<Z_*$ based on current ordered
right/obtuse shape, energy, $P=L=0$, torque signs, decreasing area, and even
$k<\eta<k(0)$.  The brake-generated correlation among the full histories of
$(x,y,Z,\eta)$ remains indispensable.

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
