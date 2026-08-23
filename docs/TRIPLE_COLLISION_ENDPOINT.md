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

Thus selection of the negative incoming ray is a genuine stable/unstable-
manifold statement and is not contained in (6)--(9). For a transverse field
on a selected collision ray, the Fuchsian projectors are

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
 \beta_\pm=3\alpha_\pm={3\pm\sqrt7\over2}.
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

The prefactor is positive, so only the product sign matters. Neither factor
is presently certified.

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

## Missing selection theorem

To close the endpoint one must still prove:

1. the incoming parabolic manifold selected by the returning outer orbit
   converges, after (3), to the appropriate branch of the collision manifold;
2. the returned transverse Jost combination has a nonzero coefficient in
   the relevant $\sigma^{\alpha_-}$ or $\sigma^{\alpha_+}$ eigendirection;
3. its collision transition through the rescaled problem (5) gives a
   positive outgoing turn Wronskian, uniformly for $\phi<\pi$ close to
   $\pi$;
4. the conclusion transfers to finite $B$ through arbitrarily close but
   noncolliding triple encounters, while an actual collision is treated only
   as termination of the classical solution.

The exact exponents make this a finite-dimensional McGehee matching problem.
They do not by themselves determine the coefficient sign. Status of
(1)--(9): **EXACT SYMBOLIC IDENTITY** or direct asymptotic consequence of the
binary Kepler clock. Status of the four selection statements:
**CONJECTURAL**.
