# Shifted-Fuchsian selection at the triple endpoint

The two scalar factors in the restricted triple-endpoint asymptotic are now
known to be positive. This note isolates the remaining selection issue. Its
main point is that the local singular perturbation is an ordinary hyperbolic
inclination problem after translating logarithmic radius. No transversality
of the incoming phase curve is needed for this local statement.

## Exact center-radius formulation

On the last heavy-binary infall let

\[
 r_c=\rho,
 \qquad x=-\log r,
 \qquad x_c=-\log\rho,
 \qquad \xi=x-x_c=-\log(r/\rho).
\tag{1}
\]

The light body crosses the binary center at \(r=\rho\), so \(y=z/r=0\)
at \(\xi=0\). If \(\varepsilon\) is the physical time from that crossing to
the prescribed binary collision, then exactly

\[
 \varepsilon={1\over2}\left[arcsin\sqrt\rho-
                   \sqrt{\rho(1-\rho)}\right],
 \qquad
 {\rho\over\varepsilon^{2/3}}\longrightarrow C=9^{1/3}.
\tag{2}
\]

Put

\[
 g(y)=y\left[(y^2+1/4)^{-3/2}-1\right],
 \qquad
 \widehat Q(y)={1-2y^2\over(y^2+1/4)^{5/2}}.
\]

The exact final-infall equations become

\[
 2(1-\rho e^{-\xi})y_{\xi\xi}
 +(-1+2\rho e^{-\xi})y_\xi+g(y)=0,
\tag{3}
\]

\[
 2(1-\rho e^{-\xi})p_{\xi\xi}
 +(3-2\rho e^{-\xi})p_\xi-\frac12\widehat Q(y)p=0.
\tag{4}
\]

Thus the small parameter disappears on every compact translated
\(\xi\)-interval. The limiting base equation is

\[
 2y_{\xi\xi}-y_\xi+g(y)=0.
\tag{5}
\]

With \(\tau=3\xi/2\), equation (5) is precisely the universal peel-off
equation in `TRIPLE_COLLISION_ENDPOINT.md`. The normalization \(y(0)=0\)
therefore fixes its logarithmic translation.

There is also an exact Lyapunov identity, not merely a limiting one. Define

\[
 \mathcal V(y)=-{1\over\sqrt{y^2+1/4}}-{y^2\over2},
 \qquad \mathcal V'(y)=g(y).
\]

Along (3), with \(r=\rho e^{-\xi}\),

\[
 {d\over d\xi}\left[(1-r)y_\xi^2+\mathcal V(y)\right]
 =(1-r)y_\xi^2.
\tag{6}
\]

This identity fixes the orientation of a captured first-center passage and
rules out a hidden conservative center at the limiting saddle.

## A local selection lemma

Let \(e=\sqrt3/2\) and

\[
 n={\sqrt{19}-1\over4},
 \qquad \mu={1+\sqrt{19}\over4}.
\]

The equilibrium \((-e,0)\) of (5) has eigenvalues \(-n\) and \(\mu\).

**Lemma (translated inclination).** Suppose \(\rho_j\downarrow0\), and let
\(y_j\) be captured arcs of (3) satisfying:

1. \(y_j(0)=0\), with this point their first center crossing on the final
   infall;
2. on one fixed regular section \(r=r_m>0\), their states converge to a
   collision-stable orbit with
   \(y=-e+a r^n+o(r^n)\), where \(a<0\);
3. between that section and the center crossing the arcs have no singularity.

Then on every compact \(\xi\)-interval on the pre-binary-collision side,
\(y_j\) and its first derivative converge to the unique increasing universal
peel-off orbit normalized by \(y(0)=0\). In physical inner time
\(s=t/\varepsilon_j\), the corresponding \(Z_j=\varepsilon_j^{-2/3}z_j\)
converges through the prescribed binary collision and up to the unique simple
first turn.

**Proof.** In first-order form, (3) converges in \(C^1\) on every compact
translated interval to the autonomous saddle field (5). Choose a small
isolating saddle box with fixed entrance and exit sections and use graph
coordinates \((S,U)\) in which the limiting local stable and unstable
manifolds are the coordinate axes. Variation of constants gives, uniformly
for small \(r\),

\[
 |S(\xi)|\le C e^{-n(\xi-\xi_0)}|S(\xi_0)|+C\eta^2+C r,
\]

and the analogous backward estimate

\[
 |U(\xi)|\le C e^{-\mu(\xi_1-\xi)}|U(\xi_1)|+C\eta^2+C r
\]

while \(|S|+|U|\le\eta\). More precisely, first propagate fixed-section
convergence to a fixed small radius \(r_0<1/2\). If \(T_j\) is the time spent
between the fixed saddle sections, the graph-transform form of these two
estimates gives

\[
 \operatorname{dist}(Y_j^{\rm exit},W^u_0\cap\Sigma_u)
 \le C\left(e^{-\kappa T_j}+r_0\right),
 \qquad \kappa=\min(n,\mu)>0.
\tag{6a}
\]

Here
\(T_j\ge x_{c,j}-x(r_0)-O(1)\to\infty\), and the \(O(r_0)\) term is
the integral of the nonautonomous perturbation over the hyperbolic Green
kernels. Taking \(j\to\infty\) first and then \(r_0\downarrow0\) proves the
parameter-dependent inclination statement; it is not an appeal to compact
convergence on a fixed interval.

The exit must be the increasing one. Indeed, for \(r<1/2\),

\[
 y<-e,\quad y_\xi<0
 \quad\Longrightarrow\quad
 y_{\xi\xi}={(1-2r)y_\xi-g(y)\over2(1-r)}<0,
\tag{6b}
\]

because \(g(y)>0\) below \(-e\). A lower peel can therefore never turn back
to the first center crossing. The stable coefficient \(a<0\) fixes the
incoming side, and item 1 selects the upper exit. The unique-peel-off lemma
identifies the entire translated limit and its center speed, so the full
sequence converges.

The exact binary clock gives

\[
 \varepsilon_j^{-2/3}r(\varepsilon_js)
 \longrightarrow C|1-s|^{2/3}
\]

in \(C^1\) away from \(s=1\) and uniformly in \(C^0\) across it. Choose one
fixed \(s_0<1\) after the center at which the universal height is already
positive. Compact translated convergence supplies the complete state at
\(s_0\). On a short interval containing \(s=1\), the force and its light-state
derivatives are uniformly regular on \(Z\ge Z_*(s_0)/2\), and the binary
coefficient \(R_j^2\) converges uniformly. Gronwall continuation therefore
keeps \(Z_j\) separated and propagates convergence through \(s=1\). Equivalently
one may use the analytic
\(\lambda=\operatorname{sgn}(1-s)|1-s|^{1/3}\) field. The limiting first turn
is simple, so its state and event time also converge. \(\square\)

This is the usual inclination lemma proved here in the exact variables of the
problem. It requires convergence to a collision-stable endpoint but not a
nonzero derivative of the phase curve across that stable manifold.

## Selection of the transverse slow mode

Put

\[
 \beta_\pm={3\pm\sqrt7\over4},
 \qquad \alpha_\pm={3\pm\sqrt7\over6}.
\tag{7}
\]

The limiting constant fiber at the saddle has modes
\((p,p_\xi)=e^{-\beta_\pm\xi}(1,-\beta_\pm)\). Suppose the fields on the fixed
regular section converge to a returned Jost field with collision expansion

\[
 p=\widehat A_-r^{\beta_-}(1+o(1))
   +\widehat A_+r^{\beta_+}(1+o(1)).
\tag{8}
\]

The fibered version of the preceding graph-transform argument gives, on
compact translated intervals,

\[
 \rho_j^{-\beta_-}
 (p_j,p_{j,\xi})(x_{c,j}+\xi)
 \longrightarrow
 \widehat A_-(P_-,P_{-,\xi})(\xi).
\tag{9}
\]

To make the long-time assertion explicit, let
\(d=\beta_+-\beta_-=\sqrt7/2\). In the canonical slow/fast fiber coordinates
over the saddle box, variation of constants and the exponential kernels give

\[
 \sup_{-L\le\xi\le0}
 \left\|\rho_j^{-\beta_-}(p_j,p_{j,\xi})
       -\widehat A_-(P_-,P_{-,\xi})\right\|
 \le C_L\left(o_j(1)+r_0^\omega+\rho_j^d\right)
      +Ce^{-\mu L},
\tag{9a}
\]

after matching at \(\xi=-L\), for some uniform \(\omega>0\). The terms have
separate origins: the collision-stable tail and the exact \(O(r)\) geometric
perturbation are integrable in \(x\); the departing base coordinate is
\(O(e^{\mu\xi})\), whose unmatched tail is \(O(e^{-\mu L})\); and the fast
fiber is suppressed relative to the slow one by \(\rho_j^d\). The Fuchsian
coefficients and their first derivatives are bounded uniformly over the
compact amplitude bracket. First let \(j\to\infty\), then \(r_0\downarrow0\)
and \(L\to\infty\). This proves (9) and closes long-time mode mixing; ordinary
coefficient convergence on compact translated intervals alone would not do
so.

The exponent identity

\[
 {2\beta_-\over3}=\alpha_-
\tag{10}
\]

and (2) convert (9) into physical inner normalization, first on compact
pre-collision \(s\)-intervals:

\[
 \left(
 \varepsilon_j^{-\alpha_-}p_j(\varepsilon_js),
 \varepsilon_j^{1-\alpha_-}\dot p_j(\varepsilon_js)
 \right)
 \longrightarrow A_-\left(P_-(s),P_{-,s}(s)\right),
 \qquad A_-=C^{\beta_-}\widehat A_-.
\tag{11}
\]

For the derivative component, use
\(d\xi/ds=-\varepsilon\dot r/r\to2/3\) at the center, together with
\(2\beta_-/3=\alpha_-\). This also fixes the time orientation in (11).

Continuous dependence through the regular \(\lambda\)-chart propagates
(11) to the simple first turn. In the present convention

\[
 K_-=Z_*(s_t)P_{-,s}(s_t),
 \qquad Z_{*,s}(s_t)=0,
\]

is the turn Wronskian of the unit slow universal field. Then

\[
 \varepsilon_j^{(\sqrt7-1)/6}\mathcal C_2(\phi_j)
 \longrightarrow A_-K_-.
\tag{12}
\]

Since \(\delta_j=\pi-\phi_j=4\varepsilon_j\), this is equivalently

\[
 \delta_j^{(\sqrt7-1)/6}\mathcal C_2(\phi_j)
 \longrightarrow4^{(\sqrt7-1)/6}A_-K_-.
\tag{13}
\]

Equations (3)--(6), (10), and the power
\(\alpha_--1/3=(1-\sqrt7)/6\) are exact symbolic regression tests.

## What remains: endpoint localization

Define the following compact statement.

**Endpoint localization (L).** Every captured sequence
\(\phi_j\uparrow\pi\), when pulled back to one fixed regular final-infall
section, has a subsequence converging jointly in base and returned-Jost state
to a collision-stable/incoming-parabolic connection whose stable amplitude
lies in

\[
 -0.24696\le a\le-0.24694.
\tag{14}
\]

The local lemma and cocycle calculation prove the following exact reduction.

**Theorem (conditional endpoint exclusion).** If (L) holds, then there is a
\(\delta_0>0\) such that

\[
 \mathcal C_2(\phi)>0
 \qquad(0<\pi-\phi<\delta_0)
\tag{15}
\]

on the captured component. More strongly, the renormalized coefficient has
a strictly positive uniform lower limit.

**Proof.** The global certificate proves
\(W(J,P_+)<-1/2\) throughout (14), hence
\(\widehat A_->1/(2\sqrt7)\). The turn certificate proves \(K_->0\).
Apply (13) to an arbitrary sequence. If (15) failed, endpoint localization
would supply a subsequence converging to a certified connection, and (13)
would give a positive limiting renormalized coefficient, a contradiction.
Compactness of (14) and the strict Wronskian margin make the lower limit
uniform. \(\square\)

## Unconditional certified local branch

The transversality theorem removes hypothesis (L) for the branch born at the
certified connection itself.

**Corollary (restricted triple-endpoint branch).** In the
collision-regularized restricted problem there is a one-sided local captured
branch whose center mean phase satisfies \(\phi\uparrow\pi\). On this branch,

\[
 (\pi-\phi)^{(\sqrt7-1)/6}\mathcal C_2(\phi)
 \longrightarrow4^{(\sqrt7-1)/6}A_-K_->0.
\tag{16}
\]

Consequently \(\mathcal C_2(\phi)>0\) throughout a punctured one-sided
neighborhood of the endpoint on this branch.

**Proof.** On a fixed regular final-infall section, the incoming parabolic
curve crosses the collision-stable curve transversely at the unique certified
point; see `TRIPLE_ENDPOINT_TRANSVERSALITY.md`. In local stable/unstable saddle
coordinates, its signed unstable coordinate therefore has a simple zero. The
two sides exit the long saddle passage on opposite unstable branches. The
one-way cone (6b) prevents the lower branch from returning to a first center
crossing. The upper branch converges to the unique increasing peel, crosses
\(y=0\), stays separated through the prescribed binary collision, and reaches
the simple first turn. Hence it is captured, with \(\rho\downarrow0\).

Smoothness of the incoming parabolic curve makes fixed-section convergence to
the certified connection automatic. Phase-uniform Jost-tail attachment and
ordinary compact-flow dependence give the joint fiber convergence required
in (8). Equations (11)--(13) therefore apply. The center mean phase is a valid
local coordinate on this arc: at fixed phase the incoming parabolic graph has
a unique center state. Its image is consequently a one-sided interval with
\(\phi\uparrow\pi\). The certified signs \(A_->0\) and \(K_->0\) prove (16)
and the final strict sign. \(\square\)

Thus the fractional-power singular transition and the locally emanating
captured branch are closed. Hypothesis (L) is needed only for the global
assertion that every captured sequence or remotely continued component
approaching \(\phi=\pi\) localizes at this same connection. That question
should be attacked together with the global classification of captured
components.

**Status:** equations (1)--(13), the parameter-dependent translated
inclination estimate, the fibered exchange estimate, and the conditional
endpoint theorem are **PROVED ANALYTICALLY**. The unconditional local-branch
corollary is **PROVED BY COMPUTER-ASSISTED ARGUMENT** because it uses the
certified transverse endpoint match and the two certified scalar signs. An independent adversarial pass
rederived every clock and exponent and required the explicit long-dwell
estimate (9a), the one-way lower-exit cone (6b), and full-state convergence
(11); those repairs are incorporated above. Endpoint localization (L), and
therefore the unconditional endpoint sign (15), remain **CONJECTURAL**. No
inference about finite positive \(B\) is made here.
