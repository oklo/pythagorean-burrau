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
 \pi-(2\psi+\sin2\psi)={4\over3}h^3+O(h^5),
 \qquad r=\cos^2\psi=h^2+O(h^4).
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

The rescaled light equation remains Newtonian:

\[
 Z_{ss}=-{2Z\over(Z^2+R_*^2/4)^{3/2}}.
\tag{5}
\]

Equations (1)--(5) are exact consequences of the binary Kepler clock and
Newtonian homogeneity, with (4) the leading collision law.

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
