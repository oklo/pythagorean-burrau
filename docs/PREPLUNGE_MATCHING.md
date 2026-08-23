# Uniform matching through the long skinny cycle train

This note proves the part of the skinny matching theorem that precedes the
late restricted plunge. The key device is to choose a deliberately early
overlap radius
\[
\rho_\epsilon=\epsilon^\alpha,
\qquad 0<\alpha<{1\over6}.
\tag{1}
\]
At this radius the tight binary has already completed
$O(\epsilon^{-3/2})$ collision-like cycles, but its regularized tidal forcing
is still small enough that an absolute long-time estimate closes. No
finite-eccentricity Delaunay estimate is used.

## Statement

Use the tight-pair Jacobi coordinates and masses of
`SKINNY_REGULARIZATION.md`:
\[
X=q_3-q_1,\qquad
Y=q_2-{Aq_1+q_3\over M},\qquad
A=\sqrt{1-\epsilon^2},\quad M=1+A,\quad N=M+\epsilon.
\]
Put $r=|X|$ and $\rho=|Y|$. Let $\bar Y$ be the point-mass reference fall
with the same initial outer position,
\[
\ddot{\bar Y}=-N{\bar Y\over|\bar Y|^3},\qquad
\bar Y(0)=Y(0),\quad \dot{\bar Y}(0)=0,
\]
and let $t_0(\rho)$ be its exact first arrival time at radius $\rho$.

The radial collision-ejection Kepler binary becomes a regular closed orbit
$\mathcal C$ after Levi--Civita regularization and the antipodal quotient.
Fix a genuine regularized phase coordinate $\Theta$ near $\mathcal C$ by
first setting
\[
\Theta(z_0(s),p_0(s))=\sqrt2s\pmod {2\pi}
\]
and then extending it with a tubular retraction. Define the smooth
mean-anomaly observable
\[
\Lambda=\Theta+\sin\Theta.
\]
On the reference orbit,
\[
\Lambda(z_0(s),p_0(s))=\sqrt8\,\tau_0(s)\pmod {2\pi},
\qquad
\tau_0(s)=\int_0^s|z_0(\sigma)|^2d\sigma.
\tag{2}
\]
The distinction matters: $\Lambda$ has a critical point at each prescribed
collision and is therefore not itself a phase coordinate. It is nevertheless
a smooth, uniformly Lipschitz observable there because $(z_0,p_0)$ never
vanishes as a phase-space pair.

**Theorem 1 (pre-plunge matching).** Fix $0<\alpha<1/6$. For every
sufficiently small $\epsilon>0$, either the classical solution has an inner
binary collision before reaching $\rho=\epsilon^\alpha$, or it reaches that
section collision-free at a time $t_\alpha$ and
\[
\sup_{0\le t\le t_\alpha}r(t)\le2\epsilon,
\qquad t_\alpha=O(1),
\tag{3}
\]
\[
t_\alpha-t_0(\epsilon^\alpha)
=O(\epsilon^{2-3\alpha}),
\tag{4}
\]
and
\[
\operatorname{dist}_{S^1}\!\left(
\Lambda(t_\alpha),
n_{\rm bin}t_0(\epsilon^\alpha)\right)
=O(\epsilon^{1/2-3\alpha})=o(1),
\qquad n_{\rm bin}={\sqrt{8M}\over\epsilon^{3/2}}.
\tag{5}
\]
Equivalently, define the renormalized incoming intercept at the overlap by
\[
\chi_\alpha
:=\Lambda(t_\alpha)
+n_{\rm bin}\bigl(t_{\rm mono}-t_0(\epsilon^\alpha)\bigr)
\pmod {2\pi}.
\tag{5a}
\]
Then
\[
\operatorname{dist}_{S^1}
(\chi_\alpha,\Phi_{\rm ref}(\epsilon))
=O(\epsilon^{1/2-3\alpha})=o(1).
\tag{5b}
\]
Here $t_{\rm mono}$ is the exact collapsed-pair collision time (1) of
`SKINNY_MATCHING.md`, and
$\Phi_{\rm ref}=n_{\rm bin}t_{\rm mono}$.
If $\mathcal C(\ell)$ denotes the antipodal-quotient LC state of the radial
Kepler binary with mean anomaly $\ell$, then the full regularized binary state
also satisfies
\[
\operatorname{dist}_{\rm LC}\!\left(
(z,p)(t_\alpha),
\mathcal C(n_{\rm bin}t_0(\epsilon^\alpha))\right)=o(1).
\tag{5c}
\]
Indeed, $\ell=\Theta+\sin\Theta$ is a homeomorphism of the phase circle; its
inverse is only Hölder at collision, but continuity is enough to combine
(21) and (25). No Lipschitz inverse is asserted.
More sharply, if $\mathcal J$ denotes the collection of LC variables
transverse to the Kepler phase circle, variation of constants before the
secular phase integration gives
\[
|\mathcal J(t_\alpha)|=O(\epsilon^{5/2-3\alpha}).
\tag{5d}
\]
The physical outer-energy error is (15), so its late-scaled value is
$O(\epsilon^{3-3\alpha})$.
The outer direction and velocity also obey
\[
\left|\widehat Y(t_\alpha)-\widehat Y(0)\right|
=O(\epsilon^{2-2\alpha}),
\tag{6}
\]
\[
\left|\dot Y(t_\alpha)-
\dot{\bar Y}\bigl(t_0(\epsilon^\alpha)\bigr)\right|
=O(\epsilon^{2-5\alpha/2}).
\tag{7}
\]
All constants may depend on $\alpha$ but not on the collision-free member of
the punctured endpoint family.

The collision alternative already excludes a classical periodic orbit.
Equations (4)--(5) concern every member in the collision-free alternative and
are uniform in the rapidly varying binary phase.

## Multipole and energy estimates

Write $\Phi(v)=v/|v|^3$. The exact outer equation is
\[
\ddot Y=-{N\over M}\left[
A\Phi\left(Y+{X\over M}\right)
+\Phi\left(Y-{A X\over M}\right)
\right].
\tag{8}
\]
The first Taylor moment cancels exactly:
\[
A{X\over M}-{A X\over M}=0.
\tag{9}
\]
Since $\|D^2\Phi(v)\|\le C|v|^{-4}$, (8)--(9) give, whenever
$r\le\rho/2$,
\[
\ddot Y=-N\Phi(Y)+\mathcal R,
\qquad |\mathcal R|\le C{\epsilon^2\over\rho^4},
\tag{10}
\]
provided $r\le2\epsilon$.

For the inner specific energy
\[
e={1\over2}|\dot X|^2-{M\over r},
\]
the exact mean-value estimate is
\[
|\dot e|\le {2\epsilon r|\dot X|\over(\rho-r)^3}.
\tag{11}
\]
Bootstrap on $e<-M/(2\epsilon)$. Then $r<2\epsilon$ and
\[
r|\dot X|\le\sqrt{2Mr}\le C\sqrt\epsilon.
\]
Until the section (1), (11) is therefore bounded by
$C\epsilon^{3/2-3\alpha}$. The outer arrival time will be uniformly bounded
above, so over that interval
\[
e(t)=-{M\over\epsilon}+O(\epsilon^{3/2-3\alpha}).
\tag{12}
\]
Because $\alpha<1/2$, this closes the inner-energy and $r<2\epsilon$
bootstraps.

Let $L=Y\mathbin\times\dot Y$. From (10),
\[
|\dot L|\le C{\epsilon^2\over\rho^3},
\qquad
|L|\le C\epsilon^{2-3\alpha}
\tag{13}
\]
on any fixed time interval before the section. The exact radial equation is
\[
\ddot\rho={L^2\over\rho^3}-{N\over\rho^2}
+\widehat Y\cdot\mathcal R.
\tag{14}
\]
On the bootstrap region, the centrifugal and remainder terms divided by
$N/\rho^2$ are respectively
$O(\epsilon^{4-7\alpha})$ and
$O(\epsilon^{2-2\alpha})$. Thus $\ddot\rho<-c<0$ for small $\epsilon$.
Starting from rest, the solution reaches (1) in a time bounded independently
of $\epsilon$, unless an earlier collision ends the classical solution. This
also closes the time assumption used in (12)--(13). Outer collisions cannot
occur there because every outer separation is at least
$\rho-r>0$.

The monopole outer energy
\[
\mathscr E={1\over2}|\dot Y|^2-{N\over\rho}
\]
satisfies $\dot{\mathscr E}=\dot Y\cdot\mathcal R$. Since
$\dot\rho<0$ and
$|\dot Y|\le-\dot\rho+|L|/\rho$, integration of (10) and (13) yields
\[
\mathscr E(t)-\mathscr E(0)
=O(\epsilon^{2-3\alpha})
\tag{15}
\]
uniformly before the section. On a fixed initial radial subinterval ordinary
continuous dependence gives an $O(\epsilon^2)$ arrival-time error. Beyond
that subinterval the reference radial speed is bounded away from zero, and
\[
\dot\rho^2
=2N\left({1\over\rho}-{1\over\rho_0}\right)
+2(\mathscr E-\mathscr E(0))-{L^2\over\rho^2}.
\tag{16}
\]
The last two terms are uniformly $O(\epsilon^{2-3\alpha})$ on the section
range; the square-root mean-value estimate in the time-of-flight integral
gives (4).

For the vector estimates, retain the radius dependence instead of inserting
the final radius in (13). Once the fall has crossed a fixed initial
subinterval, (14)--(16) give
$-\dot\rho\asymp\rho^{-1/2}$ and hence
\[
|L(\rho)|\le C\epsilon^2\rho^{-3/2}.
\tag{16a}
\]
Integrating $\dot\vartheta=L/\rho^2$ with
$dt\le C\rho^{1/2}|d\rho|$ gives
$|\vartheta-\vartheta_0|=O(\epsilon^2\rho^{-2})$, which is (6).
At the final section the tangential speed is
$O(\epsilon^2\rho^{-5/2})$; the radial speed difference from (15)--(16) has
the same bound. This proves (7). A cruder use of the terminal value in (13)
would lose an erroneous extra power of $\rho$ in the direction contribution.

## Regularized binary phase estimate

Rotate the initial binary to the real axis and scale
\[
X=\epsilon x,
\qquad t={\epsilon^{3/2}\over\sqrt M}\tau.
\]
On the interval above, $|x|\le2$ and the exact scaled perturbation satisfies
\[
|F_\epsilon(x,Y)|\le C{\epsilon^4\over\rho^3}
\le C\epsilon^{4-3\alpha}=:\delta_\epsilon.
\tag{17}
\]
In Levi--Civita variables $x=z^2$, $d\tau=|z|^2ds$, $p=z_s$, and scaled
osculating energy $E=\epsilon e/M$, the exact equations are
\[
z_s=p,\qquad
p_s={E\over2}z+g,\qquad
E_s=2\operatorname{Re}(\bar z\,\bar p F_\epsilon),
\quad
g={1\over2}|z|^2\bar z F_\epsilon.
\tag{18}
\]
Initially $(z,p,E)=(1,0,-1)$. The unperturbed solution is
\[
z_0(s)=\cos(s/\sqrt2),\qquad
p_0(s)=-{1\over\sqrt2}\sin(s/\sqrt2).
\tag{19}
\]

Every fixed physical time interval has $s$-length
$S=O(\epsilon^{-3/2})$. To see this without dividing by $|z|$ at a binary
collision, integrate $\tau_s=|z|^2$ over fixed oscillator blocks and use a
bootstrap from (19); its unperturbed block average is positive. On such an
interval, (17)--(18) give
\[
\sup|E+1|=O(S\delta_\epsilon)
=O(\epsilon^{5/2-3\alpha}).
\tag{20}
\]
For later matching one needs the normal rate before allowing the frequency
shear to accumulate. Write $z=(z_x,z_y)$ and $p=(p_x,p_y)$ and define
\[
\mathcal J=(E+1,L,K),\qquad
L=z_xp_y-z_yp_x,\qquad
K=p_xp_y-{E\over2}z_xz_y.
\tag{20a}
\]
These are exact first integrals of the unforced LC oscillator. On the radial
circle,
\[
\det{\partial(L,K)\over\partial(z_y,p_y)}
=-p_x^2-{z_x^2\over2}=-{1\over2},
\tag{20b}
\]
so, together with $E+1$, they are uniform normal coordinates through both
collision and apocenter. Direct differentiation of (18) gives
\[
E_s=2\operatorname{Re}(\bar z\,\bar p F_\epsilon),\qquad
L_s=z_xg_y-z_yg_x,
\]
\[
K_s=g_xp_y+p_xg_y
-\operatorname{Re}(\bar z\,\bar p F_\epsilon)z_xz_y.
\tag{20c}
\]
The defining map is considered on the LC constraint manifold. Its components
are invariant under $(z,p)\mapsto(-z,-p)$ and therefore descend to the
antipodal quotient.
Thus $|\mathcal J_s|\le C\delta_\epsilon$ on the bounded LC tube, and
\[
\sup_{s\le S}|\mathcal J(s)|
\le C S\delta_\epsilon
=O(\epsilon^{5/2-3\alpha}).
\tag{20d}
\]
This is (5d). The larger state error below is the accumulated phase shear
$S\sup|\mathcal J|$, not a larger normal action.
Indeed, let $X_0$ be the unforced LC vector field and use a local lift of the
genuine regularized phase $\Theta$. The smooth scalar
$X_0\Theta-\sqrt2$ vanishes on the radial circle. Since $\mathcal J$ is a
uniform defining map, the normal-coordinate divisibility lemma gives
\[
|X_0\Theta-\sqrt2|\le C|\mathcal J|.
\]
The forcing changes $\Theta_s$ by $O(\delta_\epsilon)$, so integrating the
phase rate and using (20d) gives
\[
\sup_{s\le S}\bigl(|z-z_0|+|p-p_0|\bigr)
=O(S^2\delta_\epsilon)
=O(\epsilon^{1-3\alpha})=o(1).
\tag{21}
\]
This closes the block-average and bounded-state bootstraps when
$\alpha<1/3$.

It remains to compare the regularized and physical clocks. The definition of
$E$ gives the exact LC constraint
\[
2|p|^2=1+E|z|^2.
\tag{22}
\]
With $Q=\operatorname{Re}(\bar z p)$, equations (18) and (22) imply
\[
Q_s={1\over2}+E|z|^2+\operatorname{Re}(\bar z g).
\tag{23}
\]
Writing $E=-1+(E+1)$ and integrating (23) yields
\[
\tau(s)={s\over2}-Q(s)+Q(0)
+\int_0^s(E+1)|z|^2d\sigma
+\int_0^s\operatorname{Re}(\bar z g)d\sigma.
\tag{24}
\]
The unperturbed identity is the same formula without the two integrals.
Equations (20)--(21) and (24) therefore prove
\[
\sup_{s\le S}|\tau(s)-\tau_0(s)|
=O(\epsilon^{1-3\alpha}).
\tag{25}
\]
The tubular coordinate $\Theta$, the Lipschitz observable $\Lambda$, and
(21), (25) show that at every physical time before the overlap section,
\[
\operatorname{dist}_{S^1}(\Lambda(t),n_{\rm bin}t)
=O(\epsilon^{1-3\alpha}).
\tag{26}
\]
Finally combine (4) with
$n_{\rm bin}=O(\epsilon^{-3/2})$ and (26). The arrival-time contribution is
$O(\epsilon^{1/2-3\alpha})$, which tends to zero precisely under the stated
safe restriction $\alpha<1/6$. This proves (5).
Since $\Phi_{\rm ref}=n_{\rm bin}t_{\rm mono}$ exactly, (5a)--(5b) follow at
once.

## What this closes and the subsequent completion

Theorem 1 proves uniform phase and outer-state matching across the entire
$O(\epsilon^{-3/2})$ train of early near-collision cycles. It replaces the
former conjectural repeated-cycle assertion on the deliberately early overlap
section (1), and matches the correct asymptotic intercept rather than a raw
phase on a fixed late section.

This theorem alone does not prove convergence on the fixed restricted section
$\Sigma^-_{Y_0}$. Between $\rho=\epsilon^\alpha$ and
$\rho=\epsilon Y_0$, the multipole perturbation is no longer uniformly small;
the correct comparison is the full restricted incoming parabolic tail, not
the point-mass monopole. INCOMING_TAIL.md supplies the required tail theorem
from the proved overlap data to fixed $Y_0$, followed by the phase-window
transfer.

The tail theorem retains the exact finite-$\epsilon$ subtraction in
(5a) throughout the early overlap. It cannot replace it there by the limiting
restricted correction $(4/3)Y^{3/2}$: at
$Y=\epsilon^{\alpha-1}$ their coefficient difference contributes
\[
{4\over3}\left(\sqrt{M/N}-1\right)Y^{3/2}
=O(\epsilon Y^{3/2}),
\]
which need not tend to zero for $\alpha<1/6$. The limiting restricted gauge is
introduced only after propagation to fixed $Y$. Its gauge-invariant
$O(Y^{-1/2})+o(1)$ estimate resolves this noncommuting-limit issue.

Status of Theorem 1: **PROVED ANALYTICALLY**.
