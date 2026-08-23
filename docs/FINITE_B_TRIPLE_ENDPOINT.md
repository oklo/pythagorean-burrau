# Finite-mass transfer near the restricted triple endpoint

The restricted endpoint theorem does not itself cover a positive light mass.
This note identifies the exact two-parameter scale and proves a wedge transfer
from the already established fixed-section matching moduli.  The point that
requires care is a coupled exchange estimate: ordinary continuous dependence
cannot be used over the logarithmically diverging dwell near the collision
saddle.  The result leaves a shrinking boundary layer where the phase gap is
too small relative to the finite-mass matching error.

## Exact double scaling

Write the light mass as $B>0$, put

\[
 A=\sqrt{1-B^2},\qquad M=1+A,
\]

and use the late skinny variables of `SKINNY_PLUNGE_MODEL.md`. Their exact
equations are

\[
 R_{\theta\theta}=-M\Phi(R)
 +B\left[\Phi\left(Z-{A\over M}R\right)
          -\Phi\left(Z+{1\over M}R\right)\right],
\tag{1}
\]

\[
 Z_{\theta\theta}=-{M+B\over M}\left[
 A\Phi\left(Z+{1\over M}R\right)
 +\Phi\left(Z-{A\over M}R\right)\right],
\tag{2}
\]

where $\Phi(v)=v/|v|^3$. Let $\varepsilon=(\pi-\phi)/4$ be the restricted
center-to-binary-collision gap on the local branch. Set

\[
 R=\varepsilon^{2/3}\mathcal R,qquad
 Z=\varepsilon^{2/3}\mathcal Z,qquad
 \theta=\theta_c+\varepsilon s.
\tag{3}
\]

Because $\Phi$ is homogeneous of degree $-2$, all powers of $\varepsilon$
cancel. Equations (1)--(2) retain exactly the same form in
$(\mathcal R,\mathcal Z,s)$. Thus the vector-field perturbation is $O(B)$,
not $O(B/\varepsilon)$.

## The two relevant exponents

Let

\[
 \mu={1+\sqrt{19}\over4},
 \qquad \alpha_-={3-\sqrt7\over6}.
\]

Transversality gives a signed unstable coordinate $h$ on the incoming
parabolic curve. The saddle exchange estimate implies

\[
 x_c=-{1\over\mu}\log h+O(1),qquad
 \rho=e^{-x_c}\asymp h^{1/\mu}.
\]

Since $\varepsilon\asymp\rho^{3/2}$,

\[
 \boxed{h\asymp\varepsilon^{\lambda_s},qquad
 \lambda_s={2\mu\over3}={1+\sqrt{19}\over6}.}
\tag{4}
\]

The restricted transverse field has position size
$p=O(\varepsilon^{\alpha_-})$. Hence its actual finite-$B$ displacement,
divided by the Newtonian position scale in (3), has size

\[
 \eta={B\varepsilon^{\alpha_-}\over\varepsilon^{2/3}}
 =B\varepsilon^{-\lambda_t},qquad
 \boxed{\lambda_t={2\over3}-\alpha_-={1+\sqrt7\over6}.}
\tag{5}
\]

The same parameter controls the velocity ratio because
$\mathcal Z_s=\varepsilon^{1/3}Z_\theta$. Exactly,

\[
 \lambda_s-\lambda_t={\sqrt{19}-\sqrt7\over6}>0.
\tag{6}
\]

Thus preserving the upper shape branch is the stronger requirement: if
$B=o(\varepsilon^{\lambda_s})$, then automatically $\eta\to0$.
Equations (4)--(6) are deterministic symbolic regression tests.

## Fixed-section matching moduli

Choose one regular final-infall section before the saddle neighborhood and
use the incoming-parabolic graph coordinate as the phase gauge. The proved
$C^0$ matching and divided transverse theorem supply moduli

\[
 \omega_0(B)\longrightarrow0,qquad \omega_1(B)\longrightarrow0
\tag{7}
\]

such that, uniformly on a small graph-coordinate neighborhood of the
certified connection:

1. the finite-$B$ late-scaled base state is within $\omega_0(B)$ of its
   restricted comparison state;
2. its divided transverse state is within $\omega_1(B)$ of the returned Jost
   field.

The first statement is the regularized state convergence of
`INCOMING_TAIL.md`; the second is Theorem 3 of
`FIRST_ORDER_INCOMING_MATCHING.md`. These theorems prove existence of the
moduli but do not currently give a convenient explicit common power of $B$.

For the actual Pythagorean trajectory the comparison intercept is not a free
parameter: it is

\[
 \chi_B=\Phi_{\rm ref}(B)\pmod {2\pi}.
\tag{7a}
\]

Suppose that this intercept lies on the one-sided local restricted branch of
`TRIPLE_ENDPOINT_SELECTION.md`.  Its center mean phase defines
$\varepsilon=(\pi-\phi(\chi_B))/4$.  Thus every occurrence of
$\varepsilon$ below refers to the restricted comparison selected by the same
$B$, not to an independently adjusted initial condition.

## Coupled exchange estimate

Let $h=h(\varepsilon)>0$ be the signed unstable graph coordinate of that
restricted comparison on the fixed final-infall section.  Transversality and
(4) give constants $0<c<C$ such that

\[
 c\varepsilon^{\lambda_s}\le h(\varepsilon)
 \le C\varepsilon^{\lambda_s}.
\tag{7b}
\]

Put $d_B=\omega_0(B)+B$ and

\[
 E(B,\varepsilon)
 ={d_B\over h}+\omega_1(B)+B|\log h|
   +B\varepsilon^{-\lambda_t}.
\tag{7c}
\]

**Lemma (coupled finite-mass exchange).**  If
$B\downarrow0$, $\varepsilon\downarrow0$, and $E(B,\varepsilon)\to0$,
then either the finite-mass orbit has a classical collision before leaving
the near-triple tube, or the following assertions hold.

1. It leaves the collision saddle on the same upper branch as the restricted
   comparison.  After translating to its center section, its longitudinal
   inner state converges to the universal peel-off state, through the
   prescribed heavy-binary encounter and up to the simple light-body turn.
2. In the fixed inertial basis whose first vector is the incoming heavy-binary
   axis, put $\xi_B=Z_{B,x}/B$.  On every compact pre-encounter translated
   interval,

   \[
    \varepsilon^{-\alpha_-}(\xi_B,\xi_{B,\xi})
    =-{A_-\over2}(P_-,P_{-,\xi})+O_L(E)+o_L(1).
   \tag{7d}
   \]

   In inner physical time this becomes

   \[
    \varepsilon^{-\alpha_-}
       (\xi_B,\varepsilon\xi_{B,\theta})
    =-{A_-\over2}(P_-,P_{-,s})+o(1),
   \tag{7d'}
   \]

   uniformly through the heavy-binary encounter and near the simple turn.

**Proof.**  The full saddle system can be constructed directly from (1)--(2),
so no restricted two-dimensional exchange theorem is being silently applied.
Write $\mathcal Q=(R,Z)$, choose a Euclidean size
$\varrho=|\mathcal Q|$ on a compact collision-free shape neighborhood, and
set

\[
 s={\mathcal Q\over\varrho},\qquad
 v=\varrho^{1/2}\mathcal Q_\theta,
 \qquad {dx\over d\theta}=\varrho^{-3/2}.
\tag{7e0}
\]

If $F_B$ is the right side of (1)--(2), its degree $-2$ homogeneity gives the
exact McGehee equations

\[
 \varrho_x=\varrho\nu,
 \qquad s_x=v-\nu s,
 \qquad v_x=F_B(s)+{\nu\over2}v,
 \qquad \nu=s\mathbin\cdot v.
\tag{7e1}
\]

They are analytic in $(s,v,B)$ wherever the normalized triangle has no
collision.  Along the incoming equilateral ray,

\[
 \nu_*=-2\left({\sqrt7\over2}\right)^{3/2}<0.
\tag{7e2}
\]

Consequently $\ell=-\log\varrho$ is a valid local time, with
$d\ell/dx=-\nu$ bounded above and away from zero.  Keep this absolute
log-size through the center-scale comparison below; translated estimates use
$\zeta=\ell-\ell_c$.  Translation in physical space has already been removed
by Jacobi coordinates.  On the saddle box, where $R\ne0$, quotient
the simultaneous rotation by imposing $\arg R=0$; zero angular momentum gives
the reconstruction equation, while the fixed incoming inertial binary axis
fixes its integration constant.  The homothetic/time direction is removed by
using $\ell$ and the center section.  The energy occurs in the reduced shape
equations only through an $O(e^{-\ell})$ triangular term and creates no center
mode.  Thus the binary energy and clock are included rather than frozen.

In this reduced $\ell$-system the equilateral collision ray is an equilibrium
at $B=0$.  Direct linearization gives longitudinal eigenvalues

\[
 -n,\quad \mu,
\]

and reduced transverse-shape eigenvalues

\[
 1-\beta_-,\quad 1-\beta_+.
\tag{7e3}
\]

The latter shift by one because McGehee shape uses $p/\varrho$, whereas the
Fuchsian field itself is $p\asymp\varrho^{\beta}$.  The missing exponent
$0$ is precisely the simultaneous-rotation mode just quotiented out.  Since
$n,\mu>0$, $1-\beta_->0$, and $1-\beta_+<0$, every remaining shape mode is
hyperbolic.  In the Sundman time $x$ of (7e0) these eigenvalues are multiplied
by the common positive factor $-\nu_*$; all ratios and stable/unstable
splittings are unchanged.

The reconstruction does not change the limiting fixed-inertial transverse
coefficient.  In the late variables, zero total angular momentum is exactly

\[
 {A\over M}R\mathbin\times R_\theta
 +{BM\over M+B}Z\mathbin\times Z_\theta=0.
\tag{7e3a}
\]

In the inner scale the outer angular momentum is
$O(B\varepsilon^{\alpha_--1/3})$.  Equation (7e3a) makes the binary angular
momentum $O(B^2\varepsilon^{\alpha_--1/3})$.  Dividing by
$|R|^2\asymp\varepsilon^{4/3}$ and integrating for an
$O(\varepsilon)$ passage gives a reconstructed rotation

\[
 O(B^2\varepsilon^{\alpha_--2/3})=O(B\eta).
\]

After division by the inner transverse size $\eta$ its contribution is
$O(B)$.  Thus reconstruction in the fixed inertial incoming-axis basis is
included in the error below and vanishes.  No moving rotation is used to
erase the Jost coefficient.

After separating the reflection-odd transverse block, put the longitudinal,
radial, energy, and clock variables in stable/unstable graph coordinates
$(S,U)$, with $U$ the one longitudinal unstable coordinate.  Their reduced
$\ell$-equations have the form

\[
 S_\ell=A_s(B)S+N_s(S,U)+E_s,
 \qquad
 U_\ell=\mu_B U+N_u(S,U)+E_u,
\tag{7e}
\]

where the semigroup of $A_s(B)$ decays at a uniform rate $\kappa>0$,
$\mu_B=\mu+O(B)>0$, and
$N_s,N_u=O((|S|+|U|)^2)$.  Equations (7e1) and the chart transitions have
uniform $C^2$ bounds in a fixed box.  The vector-field displacement is $O(B)$
and the entry-state displacement is $O(\omega_0(B))$.  Reflection at $B=0$
makes the feedback of the actual transverse state into the longitudinal
equations quadratic, apart from terms carrying an additional factor $B$.
Its inner relative size is
$\eta=B\varepsilon^{-\lambda_t}$.  Equivalently, the unstable transverse
shape amplitude at the longitudinal exit is

\[
 B\varrho^{\beta_--1}\asymp
 B\varepsilon^{-(2/3)(1-\beta_-)}=\eta,
\tag{7e4}
\]

where $(2/3)(1-\beta_-)=\lambda_t$.

The graph transform for (7e) gives a $B$-dependent local stable graph whose
$C^1$ distance from the restricted graph is $O(B)$.  Hence the actual signed
unstable distance $h_B$ at entry satisfies

\[
 |h_B-h|\le Cd_B,
 \qquad {h_B\over h}=1+O(d_B/h).
\tag{7f}
\]

Variation of constants on the stable and unstable axes now gives

\[
 \mathcal T_B=-{1\over\mu_B}\log h_B+O(1),
 \qquad \mu_B=\mu+O(B),
\tag{7g}
\]

for the saddle dwell, and convergence to the same upper exit after the
center translation.  More explicitly, flatten the local stable graph and put
$\zeta=\ell-\ell_{c,B}$.  The stable semigroup is bounded by
$Ce^{-\kappa(\ell-m)}$ and the backward unstable semigroup by
$Ce^{-\mu_B(m-\ell)}$.  Applying their two Green kernels on
$[-\mathcal T_B+L,L]$ gives

\[
 \sup_{|\zeta|\le L}|(S_B,U_B)-(S_*,U_*)|
 \le C_L\left(
   \left|{h_B\over h}-1\right|+B\mathcal T_B
   +\eta^2+B\eta+e^{-\kappa(\mathcal T_B-L)}
 \right).
\tag{7g'}
\]

The first term changes the logarithmic translation, the second includes the
parameter drift of the saddle and of its phase clock, the next two are the
even and mixed transverse feedback, and the last is the unmatched stable
tail.  Substituting (7f)--(7g) gives the compact translated-interval bound

\[
 \|X_B-X_*\|_{C^1([-L,L])}
 \le C_L\left({d_B\over h}+B|\log h|+\eta^2+B\eta\right)+o_L(1).
\tag{7h}
\]

The bounded term in (7g) is a smooth entry-to-exit flight function, not an
uncontrolled $O(1)$.  Comparing it with the restricted value gives

\[
 |\ell_{c,B}-\ell_c|
 \le C\left({d_B\over h}+B|\log h|+\eta^2+B\eta\right)+o(1).
\tag{7h0}
\]

Therefore the actual and restricted center scales and Newtonian clocks obey

\[
 {\varrho_{c,B}\over\varrho_c}\longrightarrow1,
 \qquad {\varepsilon_B\over\varepsilon}
 =\left({\varrho_{c,B}\over\varrho_c}\right)^{3/2}
   (1+O(B)+o(1))\longrightarrow1.
\tag{7h1}
\]

Here $\varepsilon_B$ is the finite-$B$ Newtonian inner clock; the final smooth
factor accounts for the mass-dependent normalized collision field.  This
justifies use of the restricted $\varepsilon$ in (3) and (7d').

This is the full parameter-dependent inclination estimate; a raw Gronwall
estimate over $\mathcal T_B$ is neither used nor uniform.

For the transverse state, divide the exact equations by $B$ before passing to
the limit.  Reflection gives zero transverse force at $B=0$ for every
longitudinal state, so no quotient of the longitudinal error occurs.  The
equation for $\xi_B$ is the restricted transverse cocycle plus a coefficient
error controlled by (7h), an initial slow/fast coefficient error
$O(\omega_1(B))$, an exponent drift $O(B|\log h|)$, and a nonlinear inner
error $O(\eta)$.  Projection onto the canonical slow and fast Fuchsian fibers
suppresses the fast error relative to the slow one by
$h^{(\beta_+-\beta_-)/\mu}$.  The same two Green-kernel calculation gives

\[
 \begin{split}
 &\left\|\varepsilon^{-\alpha_-}
       (\xi_B,\xi_{B,\xi})
       +{A_-\over2}(P_-,P_{-,\xi})\right\|_{C^0([-L,L])}\\
 &\qquad\le C_L\left[
 \omega_1(B)+{d_B\over h}+B|\log h|+\eta
 +h^{(\beta_+-\beta_-)/\mu}
 +e^{-\kappa(\mathcal T_B-L)}\right]+o_L(1).
 \end{split}
\tag{7h'}
\]

This is (7d).  In particular, $\omega_1(B)$ perturbs the slow coefficient
itself by $o(1)$; both reference and error acquire the same
$\varepsilon^{\alpha_-}$ factor, so no rate for $\omega_1$ relative to
$\varepsilon$ is required.  The factor $-1/2$ is the identity $p=-2\xi$.

For clarity, (7h) and (7h') are simultaneous, not a circular use of one
already-proved estimate inside the other.  In the stable/unstable dichotomy
norm let $\mathfrak X$ be the translated base error, let $\mathfrak Y$ be the
norm of the inner reflection-odd state divided by $\eta$ (equivalently the
collision-weighted $\varepsilon^{-\alpha_-}\xi_B$ norm), and let
$\mathfrak E_Y$ be its difference from the restricted slow field.  Before
closing the bootstrap,
the two Green-kernel estimates are

\[
 \begin{aligned}
 \mathfrak X
 &\le C_L\left[{d_B\over h}+B|\log h|
   +\eta^2(1+\mathfrak Y^2)+B\eta(1+\mathfrak Y)\right]+o_L(1),\\
 \mathfrak E_Y
 &\le C_L\left[\omega_1+\mathfrak X+B|\log h|
   +\eta(1+\mathfrak Y^2)
   +h^{(\beta_+-\beta_-)/\mu}\right]+o_L(1).
 \end{aligned}
\tag{7h''}
\]

Choose a fixed bootstrap radius larger than twice the norm of the universal
slow field.  When (7c) tends to zero, the first inequality makes
$\mathfrak X=o(1)$ inside that ball, and the second gives
$\mathfrak E_Y=o(1)$, strictly improving its boundary.  The usual
open-and-closed argument proves both estimates together.  Every $o_L(1)$ is
uniform over sequences satisfying (7c); it consists of the unmatched
restricted stable tail and the $O(e^{-\ell})$ geometric term.

After leaving the McGehee saddle box, ordinary compact inner flow reaches a
heavy-binary LC tube around the prescribed binary encounter.  The universal
light body is separated from both heavy bodies throughout this transition
and on that tube.  It remains to justify the divided passage, not just
ordinary state convergence.  In the common heavy-binary LC chart write
the regularized state as $(X,Y)$, where $X$ contains the longitudinal,
energy, and time-map variables and $Y$ is reflection-odd.  In inner variables
$Y=\eta\widehat Y$.  If the smooth LC field is $(G_X,G_Y)$, Hadamard's formula
and reflection give

\[
 \widehat Y'
 =\left[\int_0^1D_YG_Y(B,X,t\eta\widehat Y)\,dt\right]\widehat Y
 +{B\over\eta}
   \int_0^1\partial_BG_Y(tB,X,0)\,dt,
\tag{7i}
\]

and

\[
 X'=G_X(0,X,0)+O(B+\eta^2+B\eta).
\tag{7j}
\]

Here primes denote regularized LC time.  The direct divided source tends
uniformly to zero because

\[
 {B\over\eta}=\varepsilon^{\lambda_t}\longrightarrow0.
\tag{7k}
\]

The coefficients in (7i) converge by (7h), and Gronwall on the fixed LC tube
propagates the divided LC state through the encounter.  If the finite-$B$ LC
coordinate reaches zero, the physical heavy-binary collision terminates the
classical solution and the chart is not inverted beyond it.  In the
collision-free alternative the inverse chart is regular after the block.
No physical binary velocity is asserted to converge at the limiting
collision.  The outer $Z$-acceleration and its Hadamard-divided equation have
uniformly bounded coefficients because the light body remains separated, so
direct integration in inner physical time gives $C^1$ convergence of
$(Z,Z_s)$ across the block and on the separated post-block interval.  Finally
the universal light turn is simple, so its event and the divided outer state
on a whole time neighborhood converge in $C^1$. \(\square\)

## Wedge transfer theorem

**Theorem.** Consider any sequence of Pythagorean finite-mass trajectories
whose selected restricted intercepts (7a) lie on the upper local branch, with
$B_j\downarrow0$ and $\varepsilon_j\downarrow0$. Suppose

\[
 \boxed{\omega_0(B_j)+B_j=o(\varepsilon_j^{\lambda_s}).}
\tag{8}
\]

Then either the corresponding finite-$B_j$ classical solution has a collision
before completing the near-triple passage, or it has no full labelled brake
in a neighborhood of the continued restricted second turn. More precisely,
in the collision-free alternative the divided inner transverse state obeys

\[
 {1\over\eta_j}
 \left(\mathcal Z_{j,x},\mathcal Z_{j,x,s}\right)
 \longrightarrow-{A_-\over2}(P_-,P_{-,s})
\tag{9}
\]

through the prescribed binary encounter and at the simple first turn of the
universal light orbit. In particular its transverse velocity is nonzero there.

**Proof.** By (7b), condition (8) gives $d_{B_j}/h_j\to0$.  It also gives

\[
 B_j|\log h_j|\to0,
 \qquad
 \eta_j
 ={B_j\over\varepsilon_j^{\lambda_s}}
   \varepsilon_j^{\lambda_s-\lambda_t}\longrightarrow0,
\tag{8a}
\]

while $\omega_1(B_j)\to0$ without any rate relative to $\varepsilon_j$.
Thus every term in (7c) tends to zero, and the coupled exchange lemma gives
(9), including through the prescribed binary encounter.  If any actual
finite-$B$ collision occurs instead, the classical orbit has already
terminated.

To cover a brake time that is merely near, rather than exactly at, the
continued turn, argue by contradiction.  Longitudinal state convergence and
the simplicity and local uniqueness of the universal radial turn force any
sequence of such brake times to converge in inner time to $s_t$.  At a full
labelled brake both Jacobi velocities vanish, so in particular
$\mathcal Z_{j,x,s}=0$. At the limiting turn,

\[
 -{A_-\over2}P_{-,s}(s_t)\ne0
\]

because $A_->0$ and
$K_-=Z_*(s_t)P_{-,s}(s_t)>0$. This contradicts (9). \(\square\)

## Unconditional shrinking boundary layer

Although no explicit rate for $\omega_0$ is yet recorded, (7) implies an
existential uniform consequence. Put

\[
 \Delta(B)=\bigl(\omega_0(B)+B\bigr)^{1/(2\lambda_s)}.
\tag{10}
\]

After replacing the modulus by its monotone envelope, $\Delta(B)\downarrow0$.
For every local-branch gap satisfying

\[
 \Delta(B)\le\varepsilon\le\varepsilon_0,
\tag{11}
\]

one has
$(\omega_0(B)+B)/\varepsilon^{\lambda_s}\le
(\omega_0(B)+B)^{1/2}\to0$. Compactness away from
$\varepsilon=0$ covers the upper end of (11), while the theorem covers its
shrinking lower end. Consequently all sufficiently small finite masses are
excluded from a brake throughout the local restricted endpoint branch except
possibly in the boundary layer

\[
 0<\varepsilon<\Delta(B).
\tag{12}
\]

The signed transverse transfer is not yet a theorem about every exact
Pythagorean member: the unresolved boundary layer may contain infinitely many
values of the rapidly varying selected intercept. The highest-leverage repair
is an explicit algebraic rate for $\omega_0(B)$, followed by a direct analysis
of the complementary joint blow-up. Energy does independently exclude a full
brake while the actual trajectory remains in an absolute near-triple tube:
`TIGHT_BINARY_HILL_BARRIER.md` proves the necessary brake condition

\[
 |R|>{1-B^2\over1+B^2-B^4}=1-O(B^2).
\]

Thus the boundary layer is open for outgoing data and later re-expanded
motion, not for a brake during the close passage itself.

**Status:** equations (1)--(3) are **EXACT SYMBOLIC IDENTITY** or exact
homogeneity; (4) is a **PROVED ANALYTICALLY** asymptotic consequence of
transversality and saddle exchange; (5)--(6) are exact exponent algebra. The
coupled exchange estimate is **PROVED ANALYTICALLY**. The
wedge theorem and the existential boundary-layer reduction are **PROVED BY
COMPUTER-ASSISTED ARGUMENT**, because their nonzero limiting coefficient uses
the pinned certificates $A_->0$ and $K_->0$. No post-collision continuation
is used for a finite-$B$ classical orbit.
