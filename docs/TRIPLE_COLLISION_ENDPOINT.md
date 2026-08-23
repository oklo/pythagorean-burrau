# The second-encounter triple-collision endpoint

The ordinary center-phase probe suggests that the captured second-encounter
component ends when the light body crosses the binary center at the instant
of a prescribed heavy-binary collision. This is a triple collision of the
restricted limit. Binary Levi--Civita regularization alone does not regularize
it, and a finite-$B$ near-triple passage cannot be called a collision.

This note records the exact blow-up data. It does not yet prove the required
one-sided sign of the second-turn Wronskian.

## Exact clock and Newtonian scale

Let $\phi$ be the lifted binary mean anomaly at the light-body center
crossing. The next heavy-binary collision is at mean anomaly $\pi$, and mean
anomaly advances as $\phi+4\theta$. Hence its physical restricted-time gap is
exactly

\[
 \varepsilon={\pi-\phi\over4}.
\tag{1}
\]

In eccentric anomaly $\psi=\pi/2-h$,

\[
 \pi-(2\psi+\sin2\psi)={4\over3}h^3-{4\over15}h^5+O(h^7),
 \qquad r=\cos^2\psi=h^2-{1\over3}h^4+O(h^6).
\tag{2}
\]

Thus the collision scale is

\[
 \theta=\varepsilon s,qquad
 r=\varepsilon^{2/3}R,qquad
 z=\varepsilon^{2/3}Z.
\tag{3}
\]

The leading prescribed collision--ejection binary is

\[
 R_*(s)=9^{1/3}|1-s|^{2/3}.
\tag{4}
\]

Writing
$R_\varepsilon(s)=\varepsilon^{-2/3}r(\varepsilon s)$, the exact rescaled
light equation is

\[
 Z_{ss}=-{2Z\over(Z^2+R_\varepsilon^2/4)^{3/2}},
 \qquad R_\varepsilon\longrightarrow R_*.
\tag{5}
\]

Equation (1) and the rescaling in (5) are exact. Equations (2), (4), and the
limit in (5) are asymptotic consequences of the binary Kepler clock and
Newtonian homogeneity. The limiting light equation is obtained by replacing
$R_\varepsilon$ with $R_*$.

The relative collision-time perturbation is already visible on the incoming
equilateral ray. For
$r_\varepsilon=9^{1/3}(\sigma+\varepsilon)^{2/3}$, the longitudinal
linearization has coefficient $5/(18\sigma^2)$ and forcing

\[
 f_\varepsilon=-{3^{1/6}\over6\sigma^{7/3}}.
\tag{5a}
\]

It has the exact particular solution

\[
 \zeta_\varepsilon
 =- {\sqrt3\,9^{1/3}\over3}\sigma^{-1/3}.
\tag{5b}
\]

The perturbation becomes comparable with the base
$z_*=O(\sigma^{2/3})$ precisely when $\sigma=O(\varepsilon)$, independently
confirming the blow-up (3).

## Equilateral collision ray and transverse exponents

Writing $\sigma=-\theta>0$ before a simultaneous collision, the restricted
equilateral central-configuration ray is

\[
 r_*(\sigma)=9^{1/3}\sigma^{2/3},
 \qquad
 z_*(\sigma)=-{\sqrt3\over2}9^{1/3}\sigma^{2/3}.
\tag{6}
\]

Direct substitution proves both

\[
 r_*''=-{2\over r_*^2},
 \qquad
 z_*''=-{2z_*\over(z_*^2+r_*^2/4)^{3/2}}.
\tag{7}
\]

Along this ray, the transverse equation $p''=cp$ has the exact Euler
coefficient

\[
 c(\sigma)
 ={r_*^2-2z_*^2\over(z_*^2+r_*^2/4)^{5/2}}
 =-{1\over18\sigma^2}.
\tag{8}
\]

Its indicial exponents are therefore

\[
 \boxed{
 \alpha_-={3-\sqrt7\over6},
 \qquad
 \alpha_+={3+\sqrt7\over6}.}
\tag{9}
\]

These identities have deterministic symbolic regression tests. They show
that the triple endpoint has fractional-power, rather than analytic,
transverse matching. In particular, ordinary analytic continuation in the
center phase cannot cover this boundary.

The scale-invariant McGehee variables

\[
 \tau=-\log\sigma,qquad y={z\over r}
\tag{9a}
\]

give the limiting shape equation

\[
 y_{\tau\tau}-{1\over3}y_\tau
 +{2\over9}y\left[(y^2+1/4)^{-3/2}-1\right]=0.
\tag{9b}
\]

The equilateral fixed points $y=\pm\sqrt3/2$ have shape eigenvalues

\[
 \lambda_\pm={1\pm\sqrt{19}\over6}.
\tag{9c}
\]

The limiting base boundary-value problem can be classified globally. Put

\[
 F(y)={2\over9}y\left[(y^2+1/4)^{-3/2}-1\right],
 \qquad
 V(y)=-{2\over9\sqrt{y^2+1/4}}-{y^2\over9}.
\tag{9c1}
\]

Then $V'=F$, and along (9b)

\[
 {d\over d\tau}\left({y_\tau^2\over2}+V(y)\right)
 ={y_\tau^2\over3}>0
\tag{9c2}
\]

away from an equilibrium.

**Lemma (unique universal peel-off base).** There is one orbit, up to
translation of $\tau$, leaving
$(-\sqrt3/2,0)$ along the increasing branch of its positive-eigenvalue
unstable manifold. Normalize it by $y(0)=0$. It satisfies

\[
 y_\tau>0\quad\hbox{for all finite }\tau,
 \qquad
 y(\tau)\longrightarrow+\infty\quad(\tau\to+\infty),
\tag{9c3}
\]

and its physical center speed obeys

\[
 Z_s(0)=9^{1/3}y_\tau(0)
 >9^{1/3}\sqrt{5\over18}.
\tag{9c4}
\]

Moreover $y_\tau/y\to2/3$, so
$Z=9^{1/3}e^{-2\tau/3}y$ tends to a strictly positive limit as
$s\uparrow1$. Thus the universal light orbit does not join the prescribed
binary collision.

**Proof.** The unstable-manifold theorem gives one increasing branch modulo
time translation. On $(-\sqrt3/2,0)$ one has $F<0$, so a positive
$y_\tau$ cannot acquire a first zero and the branch moves toward the center.
It cannot approach $0$ asymptotically: the strictly increasing energy starts
at

\[
 V(-\sqrt3/2)=-{11\over36}>V(0)=-{4\over9}.
\]

Hence it crosses $0$ in finite $\tau$. The same energy inequality excludes a
zero of $y_\tau$ on $(0,\sqrt3/2)$, because there
$V(y)<V(\sqrt3/2)=-11/36$. Beyond $\sqrt3/2$, a first zero would have
$y_{\tau\tau}=-F(y)>0$, again impossible. Therefore $y_\tau>0$ globally.
A bounded limit would have to be an equilibrium and is incompatible with the
strict energy increase, so $y\to+\infty$. Finally

\[
 {F(y)\over y}\longrightarrow-{2\over9}.
\]

The Riccati equation for $y_\tau/y\ge0$ is asymptotically
\[
 w'=-(w-2/3)(w+1/3)
 -{2\over9}(y^2+1/4)^{-3/2}.
\]
Upper and lower barriers about $2/3$ give $w\to2/3$, and in particular
$w>1/2$ eventually. To prove a nonzero physical limit rather than only its
logarithmic growth rate, put
\[
 G(y)=F(y)+{2y\over9}
 ={2y\over9(y^2+1/4)^{3/2}},
 \qquad
 A(\tau)=e^{-2\tau/3}\left(y_\tau+{y\over3}\right).
\]
The factorization
$(D-2/3)(D+1/3)y=-G(y)$ gives
\[
 A'=-e^{-2\tau/3}G(y)<0.
\]
Thus $A\downarrow A_\infty\ge0$. Since $G(y)\le Cy^{-2}$ for large $y$ and
$y(s)\ge y(\tau)e^{(s-\tau)/2}$, one has
\[
 \int_\tau^\infty e^{-2s/3}G(y(s))\,ds
 \le Ce^{-2\tau/3}y(\tau)^{-2}.
\]
If $A_\infty=0$, this bound and
$A(\tau)\ge e^{-2\tau/3}y(\tau)/3$ would force $y(\tau)^3\le C$, contrary to
$y\to\infty$. Hence $A_\infty>0$. Finally, for
$Y=e^{-2\tau/3}y$, the equation $Y'+Y=A$ gives
$Y\to A_\infty>0$. This proves the collision limit. At $y=0$, (9c2) gives
$y_\tau(0)^2/2>V(-\sqrt3/2)-V(0)=5/36$, proving (9c4). $\square$

The lemma proves uniqueness and collision safety of the *candidate universal
base*. It does not yet prove that the finite-$\varepsilon$ returning
parabolic family converges to this unstable branch.

The incoming part of its canonical slow transverse field also has a rigorous
sign. Along the base put

\[
 Q(y)={1-2y^2\over9(y^2+1/4)^{5/2}}.
\tag{9c5}
\]

The transverse equation and slow normalization are

\[
 p_{\tau\tau}+p_\tau=Q(y)p,
 \qquad
 p(\tau)e^{\alpha_-\tau}\longrightarrow1
 \quad(\tau\to-\infty).
\tag{9c6}
\]

**Lemma (positive slow field at the center).** The field in (9c6) remains
positive up to the center crossing, and

\[
 {p_\tau(0)\over p(0)}
 \ge -\alpha_-+{7\sqrt3\over200}>0.
\tag{9c7}
\]

Since $s=0$ has $d\tau/ds=1$, this also proves $p_s(0)>0$.

**Proof.** Write $e=\sqrt3/2$, $x=y+e$, $v=y_\tau$, and
$r=p_\tau/p$. First, on $-e\le y\le0$,

\[
 0<v\le x.
\tag{9c8}
\]

Indeed $v/x\to(1+\sqrt{19})/6<1$ on the incoming unstable
manifold. For $t=-y$, direct one-variable calculus gives

\[
 -F(y)\le {2x\over3}.
\tag{9c9}
\]

To see this, (9c9) is equivalent to
$t(t^2+1/4)^{-3/2}+2t\le3e$. The derivative of the left side is

\[
 {1/4-2t^2\over(t^2+1/4)^{5/2}}+2>0;
\]

the first summand has minimum
$-(1/2)(8/5)^{5/2}>-2$. The value at $t=e$ is $3e$.
At a first crossing $v=x$, (9b) and (9c9) would give
$(v-x)_\tau=-2x/3-F(y)\le0$, proving (9c8).

Next, throughout the same interval,

\[
 Q(y)\ge-{1\over18}+{x\over4\sqrt3}.
\tag{9c10}
\]

On $[-e,-1/\sqrt2]$ this is the tangent-line bound at $-e$,
because $Q''>0$ there. On $[-1/\sqrt2,-1/2]$ one has $Q\ge0$
while the right side is negative. On $[-1/2,0]$, monotonicity gives
$Q\ge2\sqrt2/9>5/72$, whereas the right side is at most $5/72$.
These assertions also follow immediately from

\[
 Q'={256y(y-1)(y+1)\over3(4y^2+1)^{7/2}},
 \quad
 Q''=-{256(16y^4-27y^2+1)\over3(4y^2+1)^{9/2}}.
\]

Now $r$ obeys

\[
 r'=Q-r-r^2,qquad r\longrightarrow-\alpha_-
 \quad(\tau\to-\infty).
\tag{9c11}
\]

Choose $k=7/100$ and $g=-\alpha_-+kx$. The slope of the selected
Riccati orbit relative to $x$ at the equilateral equilibrium is

\[
 h={1/(4\sqrt3)\over(1+\sqrt{19})/6+1-2\alpha_-}
 ={\sqrt3\over2(1+\sqrt{19}+2\sqrt7)}>{1\over13}>k.
\tag{9c12}
\]

At a putative crossing $r=g$, (9c8)--(9c10) give

\[
 (r-g)'
 \ge x\left[{1\over4\sqrt3}
 -2k(1-\alpha_-)-k^2e\right]>0.
\tag{9c13}
\]

For example, the bracket in (9c13) is strictly larger than

\[
 {7\over50}-{119\over900}-{343\over80000}
 ={2513\over720000}>0.
\]

Equation (9c12) starts the orbit above the barrier, and (9c13) prevents a
downward crossing. The normalized $p$ is positive on the incoming tail; the
lower bound on its logarithmic derivative prevents a finite first zero, so
$r$ remains legitimate. At $x=e$ this proves (9c7), whose final positivity
follows from $\sqrt3>12/7$ and $\sqrt7>66/25$. $\square$

This closes only the incoming-to-center sign. The binary-collision passage
and the short center-to-first-turn segment still have to be controlled to
prove $K_->0$.

For a transverse field on this selected collision ray, the Fuchsian
projectors are

\[
 A_-=lim_{\sigma\downarrow0}\sigma^{-\alpha_-}
 {\alpha_+p-\sigma p_\sigma\over\alpha_+-\alpha_-},
\qquad
 A_+=\lim_{\sigma\downarrow0}\sigma^{-\alpha_+}
 {\sigma p_\sigma-\alpha_-p\over\alpha_+-\alpha_-}.
\tag{9d}
\]

In binary Levi--Civita scale $u\asymp\sigma^{1/3}$, their exponents are

\[
 \kappa_\pm=3\alpha_\pm={3\pm\sqrt7\over2}.
\tag{9e}
\]

After the orbit peels away, the coordinate

\[
 \lambda=\operatorname{sgn}(1-s)|1-s|^{1/3},qquad
 R_*=9^{1/3}\lambda^2,qquad ds=-3\lambda^2d\lambda
\tag{9f}
\]

regularizes the prescribed binary collision whenever the limiting light
orbit has $Z(1)\ne0$.

Explicitly, with $V=Z_s$, $Q=P_s$, $C=9^{1/3}$, and
$D^2=Z^2+C^2\lambda^4/4$, the regular field is

\[
 {d\over d\lambda}
 \begin{pmatrix}Z\\V\\P\\Q\end{pmatrix}
 =
 \begin{pmatrix}
 -3\lambda^2V\\
 6\lambda^2Z/D^3\\
 -3\lambda^2Q\\
 -3\lambda^2(C^2\lambda^4-2Z^2)P/D^5
 \end{pmatrix}.
\tag{9g}
\]

It is analytic across $\lambda=0$ on every box with $Z>0$. This exact field
is generated symbolically and regression-tested, and is the finite
propagation core used by the $K_-$ interval certificate below.

## Exact final-infall chart for the global coefficient

The remaining coefficient $A_-$ belongs to the *global* orbit that arrives
from parabolic infinity and ends in equilateral triple collision. On the last
heavy-binary infall, its separation $r\in(0,1)$ is monotone and satisfies

\[
 \dot r^2={4(1-r)\over r},
 \qquad \ddot r=-{2\over r^2}.
\tag{9h}
\]

The exact remaining physical time is

\[
 \sigma(r)={1\over2}\left[\arcsin\sqrt r-\sqrt{r(1-r)}\right]
 ={r^{3/2}\over3}+O(r^{5/2}).
\tag{9h1}
\]

Thus $r$, rather than physical time, gives an exact Fuchsian chart. Put
$y=z/r$ and

\[
 \widehat Q(y)={1-2y^2\over(y^2+1/4)^{5/2}}.
\tag{9i}
\]

Direct substitution into the base and transverse equations gives

\[
 2r^2(1-r)y_{rr}+r(3-4r)y_r
 +y\left[(y^2+1/4)^{-3/2}-1\right]=0,
\tag{9j}
\]

\[
 2r^2(1-r)p_{rr}-rp_r-{\widehat Q(y)\over2}p=0.
\tag{9k}
\]

The equilateral solution $y=-\sqrt3/2$ is exact on the whole final infall,
not only asymptotically at collision. Linearizing (9j) there gives the shape
exponents

\[
 \nu_\pm={-1\pm\sqrt{19}\over4}.
\tag{9l}
\]

The admissible collision-stable base family therefore has the
derivative-strengthened asymptotics

\[
 y=-{\sqrt3\over2}+a r^{\nu_+}+o(r^{\nu_+}),
 \qquad
 ry_r=a\nu_+r^{\nu_+}+o(r^{\nu_+});
\]

the scalar $a$ selects the global heteroclinic. Since
$\widehat Q(-\sqrt3/2)=-1/2$, equation (9k) has exponents

\[
 \beta_\pm={3\pm\sqrt7\over4}={3\over2}\alpha_\pm.
\tag{9m}
\]

In this chart the slow returned-Jost coefficient is the finite limit

\[
 \widehat A_-
 =\lim_{r\downarrow0}r^{-\beta_-}
 {\beta_+p-rp_r\over\beta_+-\beta_-}.
\tag{9n}
\]

This limit is not a merely formal Frobenius coefficient. With
$x=-\log r$, the first-order form of (9k) is its constant hyperbolic Euler
system plus a coefficient perturbation
$O(e^{-\min(1,\nu_+)x})$. Standard exponential-dichotomy/Volterra
asymptotic integration gives canonical modes $P_\pm$ satisfying

\[
 P_\pm=r^{\beta_\pm}(1+o(1)),
 \qquad rP_{\pm,r}=\beta_\pm r^{\beta_\pm}(1+o(1)),
\]

and a unique decomposition $p=\widehat A_-P_-+\widehat A_+P_+$. This proves
the limit (9n). The same argument gives the derivative-strengthened base
asymptotics used above and below.

The coefficient $A_-$ in the physical collision-time normalization differs
from $\widehat A_-$ by the positive factor $9^{\beta_-/3}$, so their signs
are identical. Equations (9j)--(9n) reduce the remaining global sign to a
one-dimensional stable-manifold/parabolic-manifold intersection, followed by
one scalar Fuchsian projection. They are exact and symbolically tested.

The sign of the base stable coefficient also has a global geometric meaning.
Let $q=-(\sqrt3/2)r$ be the exact equilateral comparator and $w=z-q$.

**Lemma (conditional final-infall cone).** If the collision-stable coefficient
$a$ in (9l) is negative, then throughout the entire last binary infall

\[
 z<-{\sqrt3\over2}r,
 \qquad {d\over dt}\left(z+{\sqrt3\over2}r\right)>0.
\tag{9o}
\]

**Proof.** Near collision,
$w=a r^{1+\nu_+}(1+o(1))<0$ and $\dot w\to0$ from above. For fixed $r$ the
scalar force

\[
 f_r(z)=-{2z\over(z^2+r^2/4)^{3/2}}
\]

has $\partial_zf_r>0$ whenever $z\le-\sqrt3r/2$. Since $q$ is itself an
exact solution, $w<0$ implies $\ddot w=f_r(z)-f_r(q)<0$. Working backward
from collision gives $\dot w(t)>\lim_{s\uparrow t_c}\dot w(s)=0$, and then
$w(t)=-\int_t^{t_c}\dot w(s)\,ds<0$. This continuation argument reaches the
previous apocenter. $\square$

Thus a validation of $a<0$ at one regular final-infall section certifies the
whole cone, not merely a sampled sign. The finite-gap shape proxies below
support $a<0$, but no validated heteroclinic match is yet available.

## Renormalized endpoint target

Put $\delta=\pi-\phi=4\varepsilon$ and suppose the incoming returned field
has a nonzero slow-mode coefficient. Equations (3) and (9) then predict

\[
 z_{\rm t}=O(\delta^{2/3}),
 \qquad
 p'_{\rm t}=O(\delta^{\alpha_--1}),
\tag{10}
\]

so

\[
 \mathcal C_2(\phi)
 =z_{\rm t}p'_{\rm t}
 =O(\delta^{\alpha_--1/3}).
\tag{11}
\]

The correct finite scalar is therefore

\[
 \boxed{
 \mathscr T=lim_{\phi\uparrow\pi}
 (\pi-\phi)^{(\sqrt7-1)/6}\mathcal C_2(\phi).}
\tag{12}
\]

A theorem $\mathscr T>0$ would prove $\mathcal C_2>0$ throughout a one-sided
triple-collision neighborhood. It naturally splits into the product of:

1. the coefficient $A_-$ with which the returned global Jost field enters
   the $\sigma^{\alpha_-}$ collision eigendirection;
2. the Wronskian transfer $K_-$ of that normalized eigendirection through the
   universal rescaled encounter (5) to its first turn.

Both are finite scalar signs. In these conventions the desired asymptotic is

\[
 \mathcal C_2(\phi)
 =A_-K_-\varepsilon^{(1-\sqrt7)/6}(1+o(1)).
\tag{13}
\]

Since $\delta=4\varepsilon$, equation (12) would then satisfy

\[
 \mathscr T=4^{(\sqrt7-1)/6}A_-K_-.
\tag{14}
\]

The prefactor is positive, so only the product sign matters. The universal
factor $K_-$ is now certified positive below. The global factor $A_-$ and the
finite-$\varepsilon$ selection theorem remain open.

The finite-cutoff diagnostic gives the following consistency check:

| $\delta=\pi-\phi$ | $z_{\rm t}/\delta^{2/3}$ | $p(0)/\delta^{\alpha_-}$ | $p'(0)\delta^{1-\alpha_-}$ | $\delta^{(\sqrt7-1)/6}\mathcal C_2$ |
|---:|---:|---:|---:|---:|
| $4.75\times10^{-2}$ | $0.423$ | $0.479$ | $1.958$ | $0.906$ |
| $1.72\times10^{-2}$ | $0.404$ | $0.488$ | $1.993$ | $0.991$ |
| $3.76\times10^{-3}$ | $0.390$ | $0.496$ | $2.030$ | $1.080$ |

The simultaneous stabilization of all four renormalized quantities is
**ORDINARY NUMERICAL EVIDENCE** for the slow-mode scaling and a positive
$\mathscr T$. The probe uses finite-cutoff asymptotic data and supplies no
enclosure.

A second diagnostic shoots the universal base orbit from the equilateral
collision manifold so that its center crossing is $s=0$, initializes the
canonical slow field by $P_-\sim(-s)^{\alpha_-}$, regularizes the prescribed
binary collision at $s=1$, and records its first turn:

| incoming cutoff $L$ | $Z_s(0)$ | $P_-(0)$ | $P_{-,s}(0)$ | turn $s$ | turn $Z$ | $K_-$ |
|---:|---:|---:|---:|---:|---:|---:|
| $100$ | $1.472787$ | $1.654176$ | $1.698048$ | $1.032326$ | $0.955229$ | $2.422481$ |
| $1000$ | $1.472571$ | $1.660413$ | $1.704642$ | $1.032081$ | $0.954957$ | $2.433454$ |
| $10000$ | $1.472564$ | $1.661126$ | $1.705381$ | $1.032072$ | $0.954947$ | $2.434564$ |

This is ordinary evidence for the location and scale of the already unique
captured peel-off orbit, a simple first turn just after the binary collision,
and

\[
 K_-\approx2.435.
\tag{15}
\]

The sign is now rigorous. The energy identity and $0<v\le y+\sqrt3/2$
place the center speed in

\[
 \sqrt{5/18}<y_\tau(0)\le\sqrt{19}/6\subset[1/2,3/4].
\]

The Riccati barrier (9c7) gives
$p_s(0)/p(0)>1/1000$. A pinned CAPD interval proof propagates the entire
speed interval in 256 dyadic slabs through the regular field (9g). It
propagates two transverse basis fields and proves that both physical
derivatives remain positive until the unique first radial turn. Hence

\[
 \boxed{K_->0.}
\tag{16}
\]

The full argument, exact event logic, stored hexadecimal certificate, and
replay command are in `COMPUTER_ASSISTED_TRIPLE_ENDPOINT_TURN.md`.

Reproduce both diagnostics with

~~~bash
uv run python -m scripts.probe_second_encounter \
  --cutoff 40 --phases 8 --phase-lower 2.72 --phase-upper 2.775 \
  --phase-span 10000 --max-step 0.012
uv run python -m scripts.probe_triple_endpoint \
  --cutoffs 100 1000 10000 --shoot-center -4 -1 --max-step 0.5
~~~

The validation deliberately covers the coarse analytic center box rather
than shooting the one-dimensional unstable collision manifold. It settles
the universal transfer sign $K_->0$. The separate global certificate described
below settles $A_->0$.

A finite-cutoff diagnostic of (9n), using incoming phase $2.77$ and center
collision gap $6.64\times10^{-4}$, gives

| final-infall section $r$ | $y=z/r$ | shape-stable proxy | slow Jost projector |
|---:|---:|---:|---:|
| $0.20$ | $-0.92825$ | $-0.24037$ | $0.31754$ |
| $0.10$ | $-0.88310$ | $-0.11808$ | $0.31427$ |
| $0.05$ | $-0.83477$ | $0.38676$ | $0.31384$ |
| $0.02$ | $-0.69639$ | $4.53101$ | $0.32528$ |

The first three projector values localize
$\widehat A_-\approx0.314>0$. The shape proxy reveals the expected
finite-gap boundary-layer contamination at the smaller sections. These are
**ORDINARY NUMERICAL EVIDENCE**, not an enclosure. Reproduce them with

~~~bash
uv run python -m scripts.probe_triple_jost_projection \
  --cutoff 40 --phase 2.77 --sections 0.2 0.1 0.05 0.02
~~~

The complementary collision-stable shoot and the exact finite-dimensional
target are
in `TRIPLE_ENDPOINT_MATCHING_CERTIFICATE.md`. On a regular $r=1/2$ section,
the match is a $4\times4$ system in $(\chi,a,A_-,A_+)$. Its transverse
determinant is the exact constant $-\sqrt7$, so only the two base curves need
a transversality enclosure. The returned Jost field is regularized at
parabolic infinity by
$P=x^2p$, $\Omega=z\dot p-\dot zp$, with boundary values
$(2\gamma,-\mathscr W_\infty)$. Ordinary backward shooting gives
$a\approx-0.24695$ and $\widehat A_-\approx0.31>0$.

The numerical localization has now been replaced by a rigorous sign proof.
Analytic collision-tail boxes attach the complete amplitude interval
$[-0.24696,-0.24694]$ at $r=2^{-32}$. A pinned CAPD propagation and the exact
monopole-energy tail bound put escape and return at opposite endpoints, so
connectedness supplies at least one parabolic connection. Uniform
returned-Jost tail bounds and the same propagation prove
\[
 W(J,P_+)<-\frac12,
 \qquad A_-={W(J,P_+)\over-\sqrt7}>0
\]
for every possible connection in the bracket. See
`COMPUTER_ASSISTED_TRIPLE_ENDPOINT_GLOBAL.md` and the stored hexadecimal
certificate. No uniqueness or generic transversality is assumed.

## Missing selection theorem

To close the endpoint one must still prove the finite-$\varepsilon$ selection
and transfer theorem:

1. the incoming parabolic manifold selected by the returning outer orbit
   converges, after (3), to one of the certified collision-stable/parabolic
   connections;
2. the normalized returned transverse field converges to its certified Jost
   combination, including the precise factor
   $4^{(\sqrt7-1)/6}(\pi-\phi)^{-(\sqrt7-1)/6}$;
3. the two proved limiting signs $A_->0$ and $K_->0$ transfer uniformly for
   $\phi<\pi$ close to $\pi$;
4. the resulting second-encounter conclusion transfers to finite $B$ through arbitrarily close but
   noncolliding triple encounters, while an actual collision is treated only
   as termination of the classical solution.

The exact exponents make this a finite-dimensional McGehee matching problem.
They do not by themselves prove selection. Status of (1)--(9): **EXACT
SYMBOLIC IDENTITY** or direct asymptotic consequence of the binary Kepler
clock. Status of both limiting scalar signs in item 3: **PROVED BY
COMPUTER-ASSISTED ARGUMENT**. Status of items 1, 2, the finite-$\varepsilon$
transfer in item 3, and item 4: **CONJECTURAL**.
