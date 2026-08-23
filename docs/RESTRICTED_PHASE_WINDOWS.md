# Phase windows around the restricted parabolic separatrix

Restricted transversality creates open escape and return windows. This is an
exact theorem for the auxiliary rectilinear restricted limit. The final
section states precisely what uniform finite-$B$ matching would transfer to
the Pythagorean--Burrau family.

## Section splitting function

Use the conventions of `PARABOLIC_MANIFOLD.md`. At the center section $z=0$,
let
\[
V_u(\phi)>0
\]
be the crossing speed of the orbit arriving parabolically from $z=-\infty$,
and let
\[
V_s(\phi)>0
\]
be the speed whose positive-$z$ future is parabolic. Define
\[
\Delta(\phi)=V_u(\phi)-V_s(\phi).
\tag{1}
\]
Both curves are analytic near the apocenter phase. Reversibility gives
\[
V_s(\phi)=V_u(-\phi),
\]
so $\Delta$ is odd. Restricted transversality proves
\[
\kappa:=\Delta'(0)=2V_u'(0)\ne0.
\tag{2}
\]

**Theorem 1 (two-sided phase windows).** There are $\delta,c>0$ such that
for $0<|\phi|<\delta$,
\[
|\Delta(\phi)|\ge c|\phi|,
\qquad
\operatorname{sgn}\Delta(\phi)=\operatorname{sgn}(\kappa\phi).
\tag{3}
\]
On the side $\Delta>0$, the parabolic incoming orbit leaves the center section
above the outgoing parabolic threshold and escapes to $z=+\infty$ with
strictly positive limiting speed. On the side $\Delta<0$, it turns at a finite
positive $z$.

**Proof.** Analyticity and (2) give (3), after reducing $\delta$. For $z>0$,
\[
w'=z''=-{2z\over(z^2+r^2/4)^{3/2}}<0,
\]
so until a turn $w$ decreases. If an unturned orbit has bounded $z$, then
after it is bounded away from zero the negative acceleration has a uniform
negative bound and forces a finite turn. Otherwise $z\to\infty$ and
$w\downarrow w_\infty\ge0$. The case $w_\infty=0$ is exactly McGehee's
unique local parabolic stable graph, while $w_\infty>0$ is hyperbolic escape.
Turning and strict hyperbolic escape are open. The two complementary
center-speed intervals are connected, and their common boundary can only be
the unique parabolic speed. The upper orientation follows from the exact
Kepler normal form $w=\sqrt2x+o(x)$ at $x=0$. Hence the upper interval escapes
and the lower interval turns in finite time. \(\square\)

The turn is not a three-body brake: the prescribed binary generally has
nonzero velocity. The theorem classifies escape versus return only.

## Robust compact subwindows

Choose compact arcs with nonempty relative interiors
\[
J_{\rm esc}\Subset\{0<|\phi|<\delta:\Delta(\phi)>0\},
\qquad
J_{\rm ret}\Subset\{0<|\phi|<\delta:\Delta(\phi)<0\}.
\tag{4}
\]
Continuous dependence gives a positive section margin on each arc. Therefore
the corresponding outcome persists under sufficiently small perturbations of
the incoming section state and the restricted vector field, up to the escape
certificate on $J_{\rm esc}$ and up to a transverse outer turn on
$J_{\rm ret}$.

This robustness is local on compact nonsingular sections. It does not itself
show that the true finite-$B$ orbit arrives inside either perturbed window.

## Incoming asymptotic phase gauge

The phase in (1) is recorded at the center section. Matching is more
convenient on a fixed large incoming restricted section
\[
\Sigma^-_{Y_0}=\{z=-Y_0,\ w>0\}.
\]
The restricted incoming parabolic curve has a canonical asymptotic binary-
phase intercept $\chi$. If the raw mean anomaly at $z=-Y$ is $\phi_Y$, the
normalization is
\[
\chi=\lim_{Y\to\infty}\left(\phi_Y+{4\over3}Y^{3/2}\right)
\pmod {2\pi}.
\tag{5}
\]
The limit exists because the binary is prescribed and the outer field differs
from its monopole tail by $O(Y^{-4})$; the induced flight-phase correction is
$O(Y^{-1/2})$. Let
\[
\Gamma^-_{Y_0}(\chi)
\tag{6}
\]
be the full regularized restricted state where that orbit crosses
$\Sigma^-_{Y_0}$. Propagating the compact center arcs in (4) backward gives
open **intercept** arcs $J^\infty_{\rm esc}$ and
$J^\infty_{\rm ret}$. The map (6) includes the entire restricted quadrupole
tail from infinity to the fixed section.

For the collapsed-pair reference fall, the exact intercept clock is
\[
\chi_{\rm ref}(B)=\Phi_{\rm ref}(B),
\qquad
\chi_{\rm ref}'(B)
=-{3\pi\over2}B^{-5/2}(1+o(1)).
\tag{7}
\]
This repairs two distinct gauge traps. A raw fixed-section phase cannot be
compared directly with $\Phi_{\rm ref}$ because of the divergent monopole
flight phase; it also cannot in general be compared with the raw monopole
section clock because the restricted quadrupole tail leaves a finite
$Y_0$-dependent correction. Equation (5) removes both ambiguities.

## Uniform terminal transfer

On a closed subarc of $J^-_{\rm esc}$, the restricted limiting speed has a
strict uniform positive lower bound. By a finite cover, there is one large
finite outgoing scaled section on which all these restricted trajectories
have a strict positive outer-energy margin. Continuous dependence transfers
the section inequalities to the finite-$B$ flow in the common regularized
chart.

Here is why this finite section implies terminal rather than merely local
escape. In physical Jacobi variables on that section,
\[
r=B\,O(1),\quad \rho=B\,O(1),\quad
e=-{C+o(1)\over B},\quad
\dot\rho={s+o(1)\over\sqrt B},
\tag{8}
\]
uniformly on the compact arc, with $C,s>0$. In the theorem of
`ESCAPE_CRITERIA.md`, choose $\eta=c/B$ with fixed sufficiently small $c>0$.
Then $R=M/\eta=O(B)$; choosing the common outgoing section sufficiently far
out makes
\[
\delta={C_1+o(1)\over B}>0.
\]
The tidal allowance in (E) is $O(1)$, whereas
$-\eta-e=(C-c+o(1))/B$. Thus all strict terminal-certificate inequalities
hold for small $B$. This proves a uniform terminal escape-or-classical-
collision alternative on the finite-$B$ perturbation of the compact
restricted arc. Either outcome excludes a later classical brake.

## Rational consequence

Every lift of an open subarc of $J^\infty_{\rm esc}$ has infinitely many disjoint
reference preimage intervals accumulating at $B=0$. Since
\[
B(u)={2u\over1+u^2}
\]
is a homeomorphism near zero and rational $u$ is dense, every such interval
contains rational Euclid parameters.

**Corollary 2.** The incoming-tail theorem proves that, unless an earlier
classical collision has already excluded periodicity, the true skinny
trajectory reaches $\Sigma^-_{Y_0}$ in one common regularized chart and
satisfies uniformly
\[
\operatorname{dist}\!\left(
S_B(Y_0),\Gamma^-_{Y_0}(\Phi_{\rm ref}(B))\right)=o(1).
\tag{9}
\]
Consequently infinitely many open parameter intervals containing rational $u$ satisfy
the terminal certificate and hence have no later classical brake. In
particular, infinitely many primitive Pythagorean triples are nonperiodic.

**Proof.** Shrink a compact escape arc inside $J^\infty_{\rm esc}$ by a fixed
positive intercept margin. Equations (7)--(9) put the true data in the robust
perturbed escape window throughout a nonempty subinterval of every sufficiently
small reference preimage
component. Each subinterval contains rational $u$. The uniform terminal
transfer (8) excludes every later brake. Reducing the Euclid triple preserves
the normalized dynamics. \(\square\)

No approximation rate relative to the shrinking $B$-width of a preimage
interval is needed: after shrinking the intercept arc by a fixed angular
margin, the uniform section error in (9) is eventually smaller than the
corresponding compact-state margin.

The collision alternative in the incoming-tail theorem needs no openness:
pointwise, either collision has already excluded a classical period or the
matched state transfers to the terminal window. Captured windows still
require a separate no-brake theorem.

Status of Theorem 1: **PROVED BY COMPUTER-ASSISTED ARGUMENT**, through the
restricted transversality input.

Status of Corollary 2: **PROVED ANALYTICALLY**.
