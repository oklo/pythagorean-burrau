# Convergence down the incoming parabolic tail

This note completes the finite-$B$ matching step left by
`PREPLUNGE_MATCHING.md`. It works by compactness at a fixed large scaled
section, not by comparing raw phases across a noncommuting double limit.

## The fixed-section theorem

Use late variables
\[
X=B R,\qquad Y=B Z,\qquad
t=t_{\rm mono}+B^{3/2}\theta,
\tag{1}
\]
where $t_{\rm mono}$ is the exact collapsed-pair reference collision time.
With primes denoting $d/d\theta$, the exact Jacobi equations are
\[
R''=-M{R\over|R|^3}
+B\left[\Phi\left(Z-{A\over M}R\right)
-\Phi\left(Z+{1\over M}R\right)\right],
\tag{1a}
\]
\[
Z''=-{N\over M}\left[
A\Phi\left(Z+{1\over M}R\right)
+\Phi\left(Z-{A\over M}R\right)
\right].
\tag{1b}
\]
Thus the binary backreaction is $O(B|Z|^{-3})$ on bounded LC sets, while
the exact cancellation of the first mass moment in (1b) leaves an outer
monopole remainder $O(|Z|^{-4})$.
For the limiting restricted problem, let
\[
\Gamma^-_K(\chi)
\]
denote the full regularized state on the incoming section
$\Sigma^-_K=\{z=-K,w>0\}$ of the parabolic orbit whose asymptotic binary-phase
intercept is
\[
\chi=\lim_{Y\to\infty}\left(\phi_Y+{4\over3}Y^{3/2}\right)
\pmod {2\pi}.
\tag{2}
\]
McGehee's parabolic-manifold theorem, applied as in
`PARABOLIC_MANIFOLD.md`, makes $\Gamma^-_K$ continuous in the asymptotic mean
anomaly. In a genuine LC phase chart it is analytic locally; no global
analyticity in mean anomaly is claimed at a binary-collision phase, where the
inverse phase map is only Hölder.

**Theorem 1 (incoming-tail convergence).** There is a sufficiently large
fixed $K$ such that, for every sufficiently small $B>0$, either the classical
Pythagorean--Burrau solution has a collision before reaching $\Sigma^-_K$, or
it reaches that section collision-free and its scaled state $S_B(K)$ obeys
\[
\boxed{
\operatorname{dist}\!\left(
S_B(K),\Gamma^-_K(\Phi_{\rm ref}(B))\right)=o(1)
}
\tag{3}
\]
uniformly as $B\to0$. The distance is taken in one fixed Levi--Civita section
chart and circular phase is understood modulo $2\pi$.

Together with the pre-plunge theorem, (3) controls the complete path from the
exact brake initial condition to a fixed incoming restricted section.

## Uniform tail bounds

Fix $0<\alpha<1/6$ and put
\[
Y_e=B^{\alpha-1}\longrightarrow\infty.
\]
The pre-plunge theorem supplies the state at $|Z|=Y_e$. Unless a prior
collision has already ended the classical solution, its heavy binary is
bounded in LC variables, its outer direction tends to the negative vertical
axis, its scaled outer energy tends to zero from below, and its exact
finite-$B$ intercept satisfies
\[
\operatorname{dist}_{S^1}(\chi_B,\Phi_{\rm ref}(B))=o(1).
\tag{4}
\]
More precisely, if $E_{\rm ref,B}=-BN/\rho_0$ is the exact late-scaled
monopole energy and $\perp$ denotes the coordinate transverse to the incoming
axis, the estimates in `PREPLUNGE_MATCHING.md` rescale to
\[
\begin{gathered}
|\mathscr H_N(Y_e)-E_{\rm ref,B}|=O(Y_e^{-3}),\qquad
|\mathscr L(Y_e)|=O(Y_e^{-3/2}),\\
|Z_\perp(Y_e)|=O(Y_e^{-1}),\qquad
|Z'_{\perp}(Y_e)|=O(Y_e^{-5/2}).
\end{gathered}
\tag{4a}
\]

Choose $K$ so large that $|Z|\ge K$ keeps the light body a fixed distance from
the bounded regularized binary. On this tail the exact binary equation differs
from its unperturbed Kepler equation by
\[
O(B|Z|^{-3})
\tag{5}
\]
in the LC chart. The outer force is $O(|Z|^{-2})$, with its mass-weighted
dipole canceled exactly.

The outer radial comparison inherited from `PREPLUNGE_MATCHING.md` continues
on $K\le |Z|\le Y_e$:
\[
c|Z|^{-1/2}\le-{d|Z|\over d\theta}\le C|Z|^{-1/2}.
\tag{6}
\]
Here is the radius-dependent estimate that closes the bootstrap. Write
$Y=|Z|$ and define the monopole energy and angular momentum
\[
\mathscr H_N={1\over2}|Z_\theta|^2-{N\over Y},
\qquad \mathscr L=Z\mathbin\times Z_\theta.
\tag{6a}
\]
The exact mass-weighted dipole cancellation makes the nonmonopole outer force
$O(Y^{-4})$, not merely $O(Y^{-3})$. Starting with the pre-plunge data at
$Y_e$, a simultaneous bootstrap in the energy and torque identities gives
\[
|\mathscr H_N(Y)-E_{\rm ref,B}|\le C Y^{-3},
\qquad
|\mathscr L(Y)|\le C Y^{-3/2},
\qquad K\le Y\le Y_e.
\tag{6b}
\]
Indeed, under the radial-speed bootstrap,
$|d\mathscr H_N/dY|\le CY^{-4}$ and
$|d\mathscr L/dY|\le CY^{-5/2}$. The initial bounds at $Y_e$ have precisely
the same orders by (4a). Integration proves (6b), and in particular
$|\mathscr H_N|\le CB+CY^{-3}$.

The exact identity
\[
\left({dY\over d\theta}\right)^2
={2N\over Y}+2\mathscr H_N-{\mathscr L^2\over Y^2}
\tag{6c}
\]
then closes the assumed speed bounds, because
\[
{B+Y^{-3}\over Y^{-1}}\le C(BY+Y^{-2})
\le C(B^\alpha+K^{-2})
\]
and $\mathscr L^2/Y^2=O(Y^{-5})$. Choose $K$ large and then $B$ small.
The binary tube, energy, angular-momentum, and sign $dY/d\theta<0$
bootstraps close simultaneously; the lower speed bound prevents a change of
sign. This proves (6) by the usual open-and-closed argument. In
particular,
\[
d\theta\le C|Z|^{1/2}|d|Z||.
\tag{7}
\]

The binary estimate requires a regularized block argument, because a raw
mean anomaly is singular at collision.

**Lemma 2 (LC block clock).** In a fixed tubular neighborhood of the
antipodal-quotient radial Kepler circle there are smooth LC normal variables
$\mathcal J$ and the smooth mean-anomaly observable $\Lambda$ of
`PREPLUNGE_MATCHING.md` such that, for regularized forcing bounded by
$f_k$ on the $k$th complete or partial LC oscillator block,
\[
|\Delta\mathcal J_k|\le C f_k,
\qquad
|\Delta\Lambda-\Omega_B\Delta\theta|
\le C(|\mathcal J_k|+f_k),
\tag{7a}
\]
where $\Omega_B=\sqrt{8M}$. For a consecutive train of complete blocks,
their physical lengths are uniformly comparable to one, so the sum of the
right-hand sides is comparable to the corresponding physical-time integral.
The two incomplete endpoint blocks are retained separately as supremum
terms; they are not estimated by their possibly vanishing physical lengths.

**Proof.** Put $\tau=\sqrt M\,\theta$ and use the normalized LC variables of
(18) in `PREPLUNGE_MATCHING.md`.
\[
z_s=p,\qquad p_s={E\over2}z+g,\qquad E_s=h,\qquad
\tau_s=|z|^2,
\tag{7b}
\]
where $|g|\le C|z|^3f$ and $|h|\le C|z||p|f$. Write
$z=(z_x,z_y)$ and $p=(p_x,p_y)$. The following three functions are first
integrals of the unforced LC oscillator:
\[
\mathcal J=(E+1,L,K),\qquad
L=z_xp_y-z_yp_x,\qquad
K=p_xp_y-{E\over2}z_xz_y.
\tag{7c}
\]
They are genuine smooth normal coordinates around the radial phase circle.
Indeed, on that circle their Jacobian in the two transverse variables is
\[
{\partial(L,K)\over\partial(z_y,p_y)}
=
\begin{pmatrix}
-p_x&z_x\\
-(E/2)z_x&p_x
\end{pmatrix},
\qquad
\det=-p_x^2-{z_x^2\over2}=-{1\over2},
\tag{7d}
\]
where the last identity uses $E=-1$ and the LC constraint. The coordinate
$E+1$ supplies the third normal direction, so the rank is uniform through
both collision and apocenter.
Here $\mathcal J$ is considered on the four-dimensional LC constraint
manifold. Its components are invariant under
$(z,p)\mapsto(-z,-p)$, so the defining map descends to the antipodal
quotient.

Direct differentiation of (7b) gives the exact forced identities
\[
E_s=h,\qquad
L_s=z_xg_y-z_yg_x,\qquad
K_s=g_xp_y+p_xg_y-{h\over2}z_xz_y.
\tag{7e}
\]
Consequently $|\mathcal J_s|\le Cf$ throughout a fixed tube. For the clock,
let $X_0$ denote the unforced LC vector field and set, using a local lift of
the circular observable (equivalently its pulled-back angular one-form),
\[
\mathcal D=X_0\Lambda-\sqrt8\,|z|^2.
\tag{7f}
\]
The exact radial Kepler clock makes $\mathcal D=0$ on the phase circle.
Because (7c) are uniform transverse coordinates, smooth divisibility gives
$|\mathcal D|\le C|\mathcal J|$ in the tube. The forcing changes
$d\Lambda/ds$ by $O(f)$, and $\sqrt8\,\tau=\Omega_B\theta$. Hence
\[
|\mathcal J_s|\le Cf,\qquad
\left|{d\over ds}(\Lambda-\Omega_B\theta)\right|
\le C(|\mathcal J|+f).
\tag{7g}
\]

Define a complete LC block by one $2\pi$ advance of the genuine regularized
phase $\Theta$. In a sufficiently small tube, $\Theta_s$ is bounded above and
away from zero. Every complete block has physical length between two fixed
positive constants, even when it contains $z=0$, because
$\int_{\rm block}|z|^2ds$ has a positive uniform lower bound.

Let $f_k$ be the supremum of $f$ on the $k$th block. The outer radius changes
by only $O(Y^{-1/2})$ there, so $f_k$ is comparable to its value at either
endpoint once $K$ is large. Integrating (7g) gives the block recurrence
\[
|\mathcal J_{k+1}-\mathcal J_k|\le C f_k,
\qquad
|\delta_{k+1}-\delta_k|\le C(|\mathcal J_k|+f_k),
\tag{7h}
\]
where $\delta_k$ is a lift of
$\Lambda-\Omega_B\theta$. The energy-frequency Jordan shear is the
$E+1$ component of $\mathcal J$; it has not been hidden in a purported
orthogonal propagator.

The observable $\Lambda=\Theta+\sin\Theta$ has derivative zero at the
prescribed collision, exactly canceling the degeneracy of physical time
there. It is a smooth LC state observable, so the Duhamel bound remains valid
on collision blocks. Summing (7h) over complete blocks and using the uniform
comparison between their number and physical $\theta$-length proves the
integrated version used below. Each of the two partial blocks has bounded LC
length and therefore contributes directly
$C(|\mathcal J|+f_k)$. This distinction is necessary: near $z=0$ an energy
increment can be $O(f\,\delta^2)$ while the physical-time integral is only
$O(f\,\delta^3)$. No division by the binary separation is used. \(\square\)

At $Y_e$, the pre-plunge variation-of-constants estimate gives
$|\mathcal J(Y_e)|=O(B^{5/2-3\alpha})$. Apply Lemma 2 with
$f=CBY^{-3}$. Equations (5) and (7) give, uniformly down to fixed $Y\ge K$,
\[
|\mathcal J(Y)-\mathcal J(Y_e)|
\le CB\int_Y^{Y_e}s^{-3}s^{1/2}ds
+CB(Y^{-3}+Y_e^{-3})
\le CBY^{-3/2}.
\tag{8}
\]
The phase part of the lemma gives the equal-$\theta$ binary-clock error
\[
\begin{split}
|\Delta_{\rm clk}(Y)|
&\le CY_e^{3/2}|\mathcal J(Y_e)|
+CB\int_Y^{Y_e}\left(s^{-3/2}+s^{-3}\right)s^{1/2}ds\\
&\quad+C\bigl(|\mathcal J(Y_e)|+|\mathcal J(Y)|
+B Y_e^{-3}+B Y^{-3}\bigr)\\
&\le C B^{1-3\alpha/2}+CB\log(Y_e/Y)+CBY^{-3/2}=o(1).
\end{split}
\tag{9}
\]
The logarithm is harmless because $B|\log B|\to0$. Replacing $\Omega_B$ by
its limiting value $4$ over the entire tail costs at most
$O(B^2Y_e^{3/2})=O(B^{1/2+3\alpha/2})=o(1)$. Thus the binary normal variables
tend to zero on every fixed section and its true mean-anomaly clock is
shadowed uniformly through every regularized close passage.

The pre-plunge outer-energy error becomes $O(B^{3-3\alpha})$ in late-scaled
units. Its worst time-of-flight effect down the tail is
\[
O(B^{3-3\alpha}Y_e^{5/2})=O(B^{1/2-\alpha/2})=o(1).
\tag{9a}
\]

The exact finite-$B$ intercept must be retained at $Y_e$. Replacing its
remaining phase there by $(4/3)Y_e^{3/2}$ is invalid because the coefficient
difference is $O(BY_e^{3/2})$ and need not vanish. Define instead
\[
F_B(Y):=n_{\rm bin}\bigl(t_{\rm mono}-t_0(BY)\bigr).
\tag{10}
\]
Since $n_{\rm bin}B^{3/2}=\Omega_B$, this is exactly the remaining binary
phase in the finite-$B$ monopole clock, not an asymptotic replacement.
By definition $\chi_B=\Lambda_B(Y_e)+F_B(Y_e)$. The exact reference radial
speed has energy $E_{\rm ref,B}$. Hence (6b)--(6c) and the square-root
mean-value identity give
\[
v_B=-{dY_B\over d\theta},\quad
v_{0,B}=-{dY_{0,B}\over d\theta},\qquad
\left|{1\over v_B}-{1\over v_{0,B}}\right|
\le CY^{-3/2}.
\tag{10a}
\]
With continuous lifts on the finite tail segment, the exact clock algebra is
\[
\begin{split}
&[\Lambda_B(Y)-\Lambda_B(Y_e)]+[F_B(Y)-F_B(Y_e)]\\
&\qquad=\Delta_{\rm clk}(Y)
+\Omega_B\int_Y^{Y_e}
\left({1\over v_B(s)}-{1\over v_{0,B}(s)}\right)ds.
\end{split}
\tag{10b}
\]
Integrating (10a) in (10b), and then returning to circular distance, yields
\[
\boxed{
\operatorname{dist}_{S^1}
\bigl(\Lambda_B(Y)+F_B(Y),\chi_B\bigr)
\le CY^{-1/2}+\eta_B,
\qquad \eta_B\longrightarrow0.
}
\tag{10c}
\]
At fixed $Y$,
\[
F_B(Y)={4\over3}Y^{3/2}+O(BY^{5/2}).
\tag{10d}
\]
The $CY^{-1/2}$ term in (10c) is essential: it is the restricted quadrupole
flight-time correction and is not set to zero on a fixed section.

## Compactness and identification of the limit

Suppose (3) fails. There is a sequence $B_n\to0$, collision-free through
$\Sigma^-_K$, for which the distance in (3) is bounded below. Passing to a
subsequence, compactness of the phase circle gives
\[
\Phi_{\rm ref}(B_n)\longrightarrow\chi\pmod {2\pi}.
\tag{11}
\]
The lower bound in (6) makes every fixed-$Y$ section uniformly transverse.
The LC state lies in a compact tube, and the equations with $Y$ as independent
variable are equicontinuous on each compact interval $[K,Y_1]$. Thus the
states on every fixed section are precompact, and a diagonal subsequence
converges consistently on all compact tail segments to a solution of the
limiting restricted system.

This limit is incoming parabolic before any transverse identification is
used. Indeed, (6b) gives
\[
|Z_\theta|^2\le {C\over|Z|}+o(1),
\tag{11a}
\]
and the finite-$B_n$ monopole-energy defect is bounded by
$CB_n+C|Z|^{-3}$. First taking the limit and then $|Z|\to\infty$ makes its
asymptotic energy zero. The inherited polar radial equations consequently give
\[
-Y'=2Y^{-1/2}(1+O(Y^{-2})),\qquad
Y''=-2Y^{-2}+O(Y^{-4})
\tag{11b}
\]
on the incoming tail.

The transverse boundary data are inherited independently of any uniqueness
claim. Combining (4a), (6b), and (7), integration of
$d\arg Z/d\theta=\mathscr L/Y^2$ from $Y_e$ gives
\[
|\arg Z-\arg Z_{\rm axis}|\le CY^{-2}.
\]
Together with the speed bound, this yields
$Z_\perp=O(Y^{-1})$ and $Z'_\perp=O(Y^{-5/2})$ in the diagonal limit.
Equation (8) makes the limiting binary radial. Thus $y=Y(1+o(1))$, and the
radial asymptotics (11b) apply to its axial component.

The remaining transverse conclusion uses a boundary condition at infinity,
not the crude torque bound alone.

**Lemma 3 (weighted transverse uniqueness).** Let the limiting binary be the
radial LC orbit and let a restricted incoming parabolic solution satisfy
\[
Z_\perp=O(Y^{-1}),\qquad Z'_\perp=O(Y^{-5/2})
\quad(Y\to\infty).
\tag{11c}
\]
Then $Z_\perp\equiv0$ on the incoming tail.

**Proof.** Put the limiting binary at
$R=(r,0)$ and write the outer coordinate as $Z=(\xi,-y)$. Its exact
transverse equation is $\xi''=-G(\xi,y,r)$, where
\[
G(\xi,y,r)=
{\xi+r/2\over((\xi+r/2)^2+y^2)^{3/2}}
+{\xi-r/2\over((\xi-r/2)^2+y^2)^{3/2}}.
\tag{11d}
\]
Reflection makes $G$ odd in $\xi$, so the mean-value identity, not a
linearization, gives
\[
G(\xi,y,r)=a(\theta)\xi,\qquad
a(\theta)=\int_0^1\partial_\xi G(t\xi,y,r)\,dt.
\tag{11e}
\]
The binary radius is bounded and (11c) gives $\xi=O(y^{-1})$; hence direct
expansion of (11e) gives
\[
a(\theta)={2\over y^3}+O(y^{-5}).
\tag{11f}
\]
The parabolic estimates are
$-y'=2y^{-1/2}(1+O(y^{-2}))$ and
$y''=-2y^{-2}+O(y^{-4})$. With $x=\log y$, the exact transverse equation
becomes
\[
\xi_{xx}-{3\over2}\xi_x+{1\over2}\xi
+O(e^{-2x})(\xi_x+\xi)=0.
\tag{11g}
\]
The associated first-order system is a constant matrix with eigenvalues
$1$ and $1/2$, plus an $L^1([x_0,\infty))$ matrix perturbation. Variation of
constants on the exponentially weighted eigenspaces is a contraction for
large $x_0$, giving a fundamental pair
\[
\xi_1(y)=y(1+o(1)),\qquad
\xi_2(y)=y^{1/2}(1+o(1)).
\tag{11h}
\]
Every nonzero solution has one of these growing leading modes. The
$O(y^{-1})$ condition in (11c) forces both coefficients to vanish. This first
proves $\xi=0$ on a sufficiently large tail; ordinary uniqueness extends it
down to the fixed section.
\(\square\)

The inherited estimates verify (11c), so Lemma 3 makes the limiting outer
motion rectilinear.

At each fixed $Y$, take $B_n\to0$ in (10c), using (4), (10d), and continuity
of the regularized observable. This gives
\[
\operatorname{dist}_{S^1}\left(
\Lambda_*(Y)+{4\over3}Y^{3/2},\chi\right)\le CY^{-1/2}.
\tag{13}
\]
Only now let $Y\to\infty$. We obtain
\[
\lim_{Y\to\infty}\left(\Lambda_*(Y)+{4\over3}Y^{3/2}\right)=\chi
\quad\hbox{in }S^1.
\tag{14}
\]
This retains the restricted quadrupole flight-time correction at every fixed
section and avoids interchanging the $B\to0$ and $Y\to\infty$ limits. The
uniqueness of McGehee's incoming parabolic graph therefore
identifies its state on $\Sigma^-_K$ as $\Gamma^-_K(\chi)$. This contradicts
the assumed positive distance from
$\Gamma^-_K(\Phi_{\rm ref}(B_n))$, since that curve is continuous. Every
subsequence has the same conclusion, proving the uniform statement (3).

## Arithmetic consequence

Let $J^\infty_{\rm esc}$ be a compact intercept arc strictly inside the
restricted hyperbolic-escape window of `RESTRICTED_PHASE_WINDOWS.md`.
The exact clock derivative
\[
\Phi_{\rm ref}'(B)=-{3\pi\over2}B^{-5/2}(1+o(1))
\]
gives infinitely many disjoint $B$-intervals on which
$\Phi_{\rm ref}(B)$ lies in a slightly smaller subarc. For every sufficiently
small such interval, Theorem 1 and robust terminal transfer give the following
dichotomy for every real parameter in the interval:

1. a prior classical collision has already excluded periodicity; or
2. the orbit reaches the outgoing terminal section and satisfies the strict
   escape-or-inner-collision certificate.

Thus every parameter in infinitely many open endpoint intervals is
nonperiodic. Since $B(u)=2u/(1+u^2)$ is a homeomorphism near zero and rationals
are dense, this proves:

**Corollary 2 (infinite Pythagorean subfamily).** Infinitely many primitive
Pythagorean triples satisfy the nonperiodicity conjecture. More strongly,
there are infinitely many open real Euclid-parameter intervals accumulating
at $u=0$ on which every classical Pythagorean--Burrau solution is nonperiodic.

This is a Level-D result. It does not exclude second brakes in the intervening
captured phase windows and therefore does not resolve the full rational or
strong real conjecture.

Status of Theorem 1: **PROVED ANALYTICALLY**. Status of Corollary 2:
**PROVED BY COMPUTER-ASSISTED ARGUMENT**, because its nonempty restricted
escape window uses the validated transversality theorem. The LC block-clock,
gauge, and transverse-uniqueness lemmas received independent adversarial
audits after the displayed repairs.
