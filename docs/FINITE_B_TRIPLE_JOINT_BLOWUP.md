# Joint two-mode blow-up of the finite-mass triple endpoint

The wedge theorem uses a restricted longitudinal gap that dominates the
finite-mass displacement.  This note removes that artificial comparison and
identifies the universal object in the complementary layer.  After measuring
from the exact $B$-dependent collision-stable manifold, every endpoint
sequence reduces to one projective parameter on the two-dimensional unstable
manifold of the massless equilateral collision rest point.

This is a structural reduction of the outgoing-data problem.  It does not yet
classify the resulting one-parameter scattering family or exclude later
brakes after the heavy pair re-expands.

## Exact unstable exponents

Use the rotation-reduced McGehee coordinates and absolute log size
$\ell=-\log\varrho$ of `FINITE_B_TRIPLE_ENDPOINT.md`.  At $B=0$ the two
relevant reduced unstable eigenvalues are

\[
 \mu={1+\sqrt{19}\over4},
 \qquad
 \tau=1-\beta_-={1+\sqrt7\over4}.
\tag{1}
\]

The first is the longitudinal peel-off mode.  The second is the slow
reflection-odd field after division by the collision size: an unnormalized
field $p\asymp\varrho^{\beta_-}$ has shape size
$p/\varrho\asymp e^{\tau\ell}$.  Both are positive, and

\[
 1<{\mu\over\tau}={1+\sqrt{19}\over1+\sqrt7}<2.
\tag{2}
\]

The upper inequality is important: a quadratic transverse term has order
$T^2=o(|T|^{\mu/\tau})$ and therefore cannot change the normalized
longitudinal amplitude below.

## Intrinsic finite-mass coordinates

Fix the regular incoming section and graph/rotation gauge used in
`FINITE_B_TRIPLE_ENDPOINT.md`.  For every sufficiently small $B$, the
equilateral collision rest point and its local stable manifold persist
smoothly in the full reduced field.  Use the parity-adapted unstable foliation
to define $H_B,T_B$ as the nonlinear asymptotic amplitudes of the two unstable
modes, rather than as arbitrary coordinates on the section:

\[
 H_B\quad\hbox{(longitudinal)},
 \qquad T_B\quad\hbox{(reflection odd)}.
\tag{3}
\]

This definition absorbs the $O(B)$ displacement of the rest point and stable
graph.  It is therefore intrinsic; no unknown $\omega_0(B)$ is divided by a
restricted phase gap.

The transverse subtraction requires one additional observation. Introduce
the auxiliary analytic family obtained by putting $A=1$, $M=2$ in the exact
late equations while retaining the light mass $B$. Its two heavy masses are
equal for every $B$, so heavy exchange followed by reflection is an exact
$\mathbb Z_2$ symmetry. The rectilinear collision rest point and its
parity-even collision-stable branch are fixed by this symmetry; the full
stable foliation and its spectral projectors are equivariant and split into
even and odd blocks. Along the Pythagorean family

\[
 A(B)=\sqrt{1-B^2}=1+O(B^2),\qquad M(B)=2+O(B^2).
\tag{3a}
\]

For example, writing the equilateral ray as
$R=(r,0)$ and $Z=(xr,yr)$, equality of its two light-heavy sides gives

\[
 x={A^2-1\over2M^2}=-{B^2\over2M^2},
\tag{3a'}
\]

so even the rest point's apparent odd offset in the fixed heavy-axis gauge is
quadratic, not linear, in $B$.

On a fixed collision-free shape neighborhood, the actual vector field and
the symmetric auxiliary field therefore differ by $O(B^2)$ in $C^2$.
Parameter-dependent stable-manifold and spectral-projection theorems give an
$O(B^2)$ odd displacement of the actual rest point, its parity-even stable
branch, and the even-to-odd block of the stable foliation. If
$\pi_{T,B}$ is normalized to the $B=0$ slow Fuchsian covector, parity gives

\[
 \pi_{T,B}=\pi_{T,0}+O(B)\quad\hbox{on the odd block},
 \qquad
 \pi_{T,B}=O(B^2)\quad\hbox{from even to odd}.
\tag{3b}
\]

Thus subtracting the moving graph and applying the moving projector changes
the divided odd coefficient only by $o(1)$ after division by $B$. This is the
finite-mass parity-amplitude lemma.

The full stable manifold also contains a fast odd stable direction; it is not
being declared pointwise even. Rather, the slow-amplitude functional $T_{A,B}$
is reflection odd, vanishes on the entire stable manifold, and its
differential annihilates the full stable tangent while selecting the slow odd
eigendirection. The $C^2$ field estimate gives
$\|T_{A(B),B}-T_{1,B}\|_{C^1}=O(B^2)$, which is the precise graph subtraction
used above.

Consider a sequence whose selected restricted intercept approaches the
certified triple endpoint.  Fixed-section state matching gives

\[
 H_B\longrightarrow0.
\tag{4}
\]

The divided transverse matching theorem, followed by (3a)--(3b) and the slow
Fuchsian projector at the endpoint, gives

\[
 {T_B\over B}\longrightarrow\Theta_*,
 \qquad
 \Theta_*=-{\widehat A_-\over2}\ne0.
\tag{5}
\]

Here $\widehat A_->0$ is the fixed-section slow coefficient certified in
`COMPUTER_ASSISTED_TRIPLE_ENDPOINT_GLOBAL.md`; the factor $-1/2$ is
$p=-2\xi$.  A change of eigenvector normalization multiplies $T_B$ and
$\Theta_*$ by the same nonzero constant and merely reparametrizes the scalar
below.

The finite-$B$ exponents satisfy
$\mu_B-\mu=O(B)$ and $\tau_B-\tau=O(B)$. Since (5) gives $T_B\asymp B$,

\[
 B|\log|T_B||\longrightarrow0.
\tag{5a}
\]

Consequently using the limiting exponents in the normalization below changes
each normalized amplitude by a factor tending to one.

Define the transverse exit scale and the projective longitudinal coordinate

\[
 \rho_T=|T_B|^{1/\tau},
 \qquad
 \boxed{\kappa_B={H_B\over\rho_T^\mu}
 ={H_B\over|T_B|^{\mu/\tau}}.}
\tag{6}
\]

Since $T_B\asymp B$, the joint layer is

\[
 H_B=O\!\left(B^{\mu/\tau}\right),
 \qquad {\mu\over\tau}
 ={1+\sqrt{19}\over1+\sqrt7}.
\tag{7}
\]

This is smaller than the $O(B)$ stable-graph displacement that forced the
earlier wedge condition.  Measuring from the persisted stable graph is what
reveals it.

## Uniform two-mode inclination lemma

The compact-convergence step used below is the following parameter-uniform
version of the inclination lemma.

**Lemma.** Let $F_B$ be the reduced $C^2$ McGehee fields in the
parity-adapted stable-foliation chart, and let $X_B$ enter one fixed saddle
box with bounded stable data and unstable amplitudes $H_B,T_B$. Suppose
$T_B\ne0$, $T_B\to0$, and $\kappa_B\to\kappa\in\mathbb R$. Put
\[
 L_B=-{1\over\tau}\log|T_B|.
\]
Then, on every fixed translated interval $[-L,L]$ contained in the common
saddle chart of the limiting orbit, $X_B(L_B+\zeta)$ converges in
$C^1([-L,L])$ to the unique orbit with asymptotics (10). More explicitly,
for some stable rate $c>0$,
\[
\begin{split}
 \|X_B-\mathscr U_\kappa\|_{C^1([-L,L])}
 \le C_L\big(&|\kappa_B-\kappa|
 +B|\log|T_B||+B\\
 &+|T_B|^{2-\mu/\tau}
 +e^{-cL_B}\big)+r_{B,L}.
\end{split}
\tag{7a}
\]
Here the left side uses the translated orbit, and the fixed-section matching
hypotheses give $r_{B,L}\to0$ after projection along the stable foliation.

**Proof.** Write the stable and unstable equations in exponential-dichotomy
form on the fixed box. The forward stable Green kernel bounds the transported
stable data by $Ce^{-cL_B}$; the backward unstable kernel is uniformly
integrable. Replacing $\mu_B,\tau_B$ by their limits over the dwell costs
$O(BL_B)$, and the $C^2$ coefficient perturbation costs $O(B)$. Normalize the
odd mode at $L_B$ and the longitudinal mode by (6). The remaining nonlinear
coordinate ambiguity is $O(T_B^2)$ and becomes
$O(|T_B|^{2-\mu/\tau})$ after longitudinal normalization. Variation of
constants gives (7a) first on the incoming linear tail. The uniform
unstable-manifold contraction propagates it to $[-L,L]$. Finally take a
longer fixed incoming tail and then let its length tend to infinity; this is
the displayed remainder $r_{B,L}$. \(\square\)

## Universal planar restricted family

At the scale $\varrho=\rho_T\widehat\varrho$, Newtonian homogeneity again
removes every power of $\rho_T$.  The remaining vector-field parameter is
$B\to0$.  Hence the physical inner equations converge to

\[
 \mathcal R_{ss}=-2\Phi(\mathcal R),
\tag{8}
\]

\[
 \mathcal Z_{ss}
 =-\Phi\left(\mathcal Z+{\mathcal R\over2}\right)
  -\Phi\left(\mathcal Z-{\mathcal R\over2}\right),
\tag{9}
\]

with $\Phi(v)=v/|v|^3$.  Equation (8) is the radial equal-heavy binary;
(9) is the *planar* massless restricted problem.  Unlike the rectilinear
endpoint orbit, $\mathcal Z$ is now genuinely two-dimensional.
The rescaled energy is $\rho_T$ times the fixed late energy and tends to zero;
zero angular momentum and the fixed-axis gauge select the radial binary
branch in (8).

In reduced McGehee shape coordinates, normalize the odd unstable amplitude to
the sign of $\Theta_*$.  For each $\kappa\in\mathbb R$, the unstable-manifold
theorem gives a unique orbit modulo the already fixed log-size translation
with asymptotic data

\[
 U_L(\zeta)=\kappa e^{\mu\zeta}+o(e^{\mu\zeta}),
 \qquad
 U_T(\zeta)=\operatorname{sgn}(\Theta_*)e^{\tau\zeta}
             +o(e^{\tau\zeta})
\tag{10}
\]

as $\zeta\to-\infty$.  Denote this one-parameter universal family by
$\mathscr U_\kappa$.

## Joint blow-up theorem

**Theorem.**  Let $B_j\downarrow0$ be any sequence of actual Pythagorean
states whose selected restricted intercepts approach the certified triple
endpoint, and suppose no earlier classical collision has occurred.  Define
$(H_{B_j},T_{B_j})$ by (3).  After a subsequence exactly one of the following
holds.

1. **Finite joint ratio.** If $\kappa_{B_j}\to\kappa\in\mathbb R$, then either
   an exact finite-$B_j$ collision terminates members of the sequence before
   the requested segment, or, on a collision-free subsequence, scaling size
   by $\rho_{T,j}$ and time by $\rho_{T,j}^{3/2}$ gives $C^1$ convergence in
   regular variables to $\mathscr U_\kappa$. A separated limiting
   heavy-binary collision may be crossed only in the common LC chart and
   clock; light-heavy and simultaneous limiting collisions stop the segment.
2. **Upper longitudinal dominance.** If $\kappa_{B_j}\to+\infty$, scaling
   instead by $|H_{B_j}|^{1/\mu}$ recovers the increasing rectilinear
   universal peel-off orbit. No normalized transverse-field limit is asserted
   in this longitudinally dominant regime.
3. **Lower longitudinal dominance.** If $\kappa_{B_j}\to-\infty$, the same
   longitudinal scaling selects the lower unstable exit.  The one-way cone of
   `TRIPLE_ENDPOINT_SELECTION.md` prevents the limiting rectilinear exit from
   returning
   to the certified first center crossing.

Thus the previously unresolved joint layer is not an arbitrary two-parameter
limit.  Its only new object is the one-parameter planar restricted scattering
family $\{\mathscr U_\kappa:\kappa\in\mathbb R\}$, together with its two
locally classified rectilinear exits.

**Proof.**  In the $B$-dependent stable-graph coordinates, the reduced field
has a hyperbolic splitting with two unstable equations

\[
 (U_L)_\ell=\mu_B U_L+O(|U|^2+|S||U|),
 \qquad
 (U_T)_\ell=\tau_B U_T+O(|U|^2+|S||U|),
\tag{11}
\]

where $\mu_B\to\mu$, $\tau_B\to\tau$, and every stable mode decays under the
forward Green kernel. The amplitudes are the coefficients furnished by the
nonlinear unstable foliation. Because $\mu<2\tau$, a permitted coordinate
change $H\mapsto H+O(T^2)$ changes $\kappa_B$ by
$O(|T_B|^{2-\mu/\tau})=o(1)$. Smooth coordinate dependence, the fixed-section
matching, and the parity-amplitude lemma prove (4)--(5).

Translate log size by $-\log\rho_T$.  At every fixed translated time, (6) and
variation of constants give

\[
 U_L\longrightarrow\kappa e^{\mu\zeta},
 \qquad U_T\longrightarrow
 \operatorname{sgn}(\Theta_*)e^{\tau\zeta}
\]

on the incoming linear tail; stable and fast modes vanish.  The usual
unstable-manifold contraction, quantified by the uniform two-mode inclination
lemma (7a), identifies the unique nonlinear limit (10). Equation (5a)
absorbs the $O(B)$ eigenvalue drift during the $O(|\log B|)$ dwell. The exact
homogeneous equations have $C^1$ coefficients converging to
(8)--(9) on every collision-free normalized-shape compact set.  Heavy-binary
collisions with separated light body are crossed in the common LC chart and
clock, by the same Hadamard argument as in `FINITE_B_TRIPLE_ENDPOINT.md`.
This is $C^1$ convergence of LC variables and of the separated outer physical
state, not convergence of physical binary velocity at the limiting collision.
Compact-flow continuation proves item 1 until a genuine finite-$B$ collision,
which is the classical-termination alternative.

If $|\kappa_B|\to\infty$, use
$\rho_L=|H_B|^{1/\mu}$ instead.  The transverse shape amplitude at that scale
is

\[
 |T_B|\rho_L^{-\tau}=|\kappa_B|^{-\tau/\mu}\longrightarrow0.
\tag{12}
\]

Moreover $T_B\asymp B$ and
$|H_B|/B^{\mu/\tau}\to\infty$. Hence eventually
$|H_B|\ge B^{\mu/\tau}$, so $B|\log|H_B||\to0$; also
$\rho_L E_{\rm late}\to0$. These are precisely the transverse, exponent-drift,
and energy hypotheses of the established one-mode inclination theorem.
The one-dimensional inclination theorem therefore gives the upper or lower
rectilinear exit according to the sign of $H_B$. This proves items 2--3.
Every real sequence $\kappa_B$ has a subsequence converging in the two-point
compactification
$[-\infty,+\infty]$, so the alternatives are exhaustive.
\(\square\)

## Exact next target

Choose one regular outgoing section of (8)--(9), stopping at any true
light-heavy collision.  Propagate the fixed-inertial angular/transverse state
and define the scalar scattering function

\[
 \mathscr S(\kappa).
\tag{13}
\]

The definition can be made as an outgoing Wronskian or angular momentum; it
must use the same normalization as the returning second-encounter map.  The
full boundary-layer transfer problem is reduced to:

1. classify the collision/exit outcome of $\mathscr U_\kappa$ for every real
   $\kappa$;
2. prove that the relevant outgoing section exists on each collision-free
   branch;
3. prove a sign or nonvanishing theorem for $\mathscr S(\kappa)$;
4. prove a separate fibered inclination estimate and attach the
   $\kappa\to\pm\infty$ limits to the certified rectilinear endpoint data.

This is one autonomous one-parameter restricted problem, with no rapidly
oscillating $B$-phase and no unknown matching modulus.  A brake during the
near-triple part is already excluded by `TIGHT_BINARY_HILL_BARRIER.md`; the
purpose of $\mathscr S$ is to control later motion after re-expansion.

The first exact scalar structure on this family is now available. On a radial
binary half-branch, logarithmic shape coordinates give
\[
 w_{\zeta\zeta}+{1\over3}w_\zeta=\nabla W(w),\qquad
 {d\over d\zeta}\left({|w_\zeta|^2\over2}-W(w)\right)
 =-{|w_\zeta|^2\over3}.
\]
The shape angular momentum satisfies
\[
 \Lambda_\zeta+{\Lambda\over3}=-xyK(x,y),\qquad K>0.
\]
Moreover $W_{xx}>0$ throughout $|y|\ge\sqrt3/2$, producing a rigorous signed
tail theorem there. The zero-projective orbit bends into the complementary
strip with the exact positive coefficient
$(2\sqrt{21}-5\sqrt3)/4$, so outer-strip invariance is not a global shortcut.
The full derivation is in PLANAR_JOINT_SHAPE_DYNAMICS.md.

**Status:** equations (1)--(2), (3a), (6)--(9), and (12) are **EXACT SYMBOLIC
IDENTITY** or exact homogeneity. The parity-amplitude lemma,
intrinsic-coordinate convergence (4)--(5), and the joint blow-up theorem are
**PROVED ANALYTICALLY** from the symmetric auxiliary family, the persisted
hyperbolic splitting, and the proved matching theorems. The global
classification and sign of $\mathscr S$ are **CONJECTURAL**.
