# Local finite-\(B\) reduction at a restricted turn resonance

This note isolates the exact nondegeneracy needed to continue the two radial
zero-velocity conditions from a restricted first-turn resonance.  The
reduction is local at one fixed resonance index.  It does not establish
uniformity as the index tends to infinity, and it does not yet construct the
required differentiable finite-\(B\) incoming family.

## Regularized extended family

Put \(\epsilon=B\).  Fix a restricted resonance
\[
\mathcal A(\phi_n)=\phi_n+4T(\phi_n)=2\pi n,
\qquad Z_n=Z_{\rm t}(\phi_n).
\tag{1}
\]
Temporarily regard the incoming binary phase \(\phi\) as independent of
\(\epsilon\).  Assume that, in a common Levi--Civita chart, there is a
\(C^1\) family of scaled solutions
\[
(R,Z)(\epsilon,\phi,\theta)
\tag{2}
\]
through the fixed resonance segment, reducing at \(\epsilon=0\) to
\[
R=(r,0),\qquad Z=(0,z).
\tag{3}
\]
At the turn \(R\) and \(Z\) are nonzero.  Define the desingularized radial
residuals
\[
F_1=R\mathbin\cdot R_\theta,\qquad
F_2=Z\mathbin\cdot Z_\theta.
\tag{4}
\]
Their zeros are the same radial conditions as those of the physical Jacobi
vectors; the omitted powers of \(B\) and the common time factor are nonzero
for \(B>0\).

## Exact restricted Jacobian

Let
\[
a_n=z_{\theta\theta}(\phi_n,T_n)
=-{2Z_n\over(Z_n^2+1/4)^{3/2}}<0,
\qquad
b_n=\partial_\phi z_\theta(\phi_n,T_n),
\tag{5}
\]
where \(T_n=T(\phi_n)\) and the phase derivative in \(b_n\) is taken at fixed
\(\theta\).

The lifted mean anomaly is \(\Lambda=\phi+4\theta\).  At a binary apocenter,
\(r=1\), \(r_\theta=0\), and \(r_{\theta\theta}=-2\).  Equivalently,
\[
\partial_\phi(r r_\theta)=-{1\over2},
\qquad
\partial_\theta(r r_\theta)=-2.
\tag{6}
\]
At the outer turn, \(z_\theta=0\), so
\[
\partial_\phi(z z_\theta)=Z_n b_n,
\qquad
\partial_\theta(z z_\theta)=Z_n a_n.
\tag{7}
\]
Consequently the exact radial Jacobian, with columns \((\phi,\theta)\), is
\[
\boxed{
D_n:=
\det {\partial(F_1,F_2)\over\partial(\phi,\theta)}
=Z_n\left(2b_n-{a_n\over2}\right).
}
\tag{8}
\]

This determinant has two useful equivalent forms.  The outer-turn equation
\(z_\theta(\phi,T(\phi))=0\), together with \(a_n<0\), gives
\[
T'(\phi_n)=-{b_n\over a_n}.
\tag{9}
\]
Therefore
\[
\boxed{
D_n=-{Z_n a_n\over2}\,\mathcal A'(\phi_n),
\qquad
\mathcal A'(\phi_n)=1+4T'(\phi_n).
}
\tag{10}
\]
Alternatively, impose the \(n\)-th binary apocenter first:
\[
\theta_n^{\rm apo}(\phi)={2\pi n-\phi\over4},
\qquad
G_n(\phi)=z_\theta\!\left(\phi,\theta_n^{\rm apo}(\phi)\right).
\tag{11}
\]
Then
\[
G_n'(\phi_n)=b_n-{a_n\over4},
\qquad
D_n=2Z_nG_n'(\phi_n).
\tag{12}
\]
Thus all versions of the nondegeneracy condition are exactly equivalent:
\[
\boxed{
D_n\ne0
\quad\Longleftrightarrow\quad
\mathcal A'(\phi_n)\ne0
\quad\Longleftrightarrow\quad
G_n'(\phi_n)\ne0.
}
\tag{13}
\]
The strict transversality of the outer turn in time, \(a_n<0\), is automatic.
What is not automatic is simplicity in the phase direction.

## Reduction to the transverse scalar

If (2) is \(C^1\) and (13) holds, the implicit-function theorem gives unique
functions
\[
\phi=\phi_n(\epsilon),\qquad
\theta=\Theta_n(\epsilon)
\tag{14}
\]
near \((0,\phi_n,T_n)\) for which \(F_1=F_2=0\).

On this double-radial branch define the angular-slip residual
\[
\sigma_n(\epsilon)=
\left[
{R\times R_\theta\over |R|^2}
-{Z\times Z_\theta\over |Z|^2}
\right]_
{(\epsilon,\phi_n(\epsilon),\Theta_n(\epsilon))}.
\tag{15}
\]
Zero total angular momentum then gives
\[
\boxed{
\text{full labelled brake on the branch}
\quad\Longleftrightarrow\quad
\sigma_n(\epsilon)=0.
}
\tag{16}
\]
Reflection symmetry gives \(\sigma_n(0)=0\).  A punctured-neighborhood
exclusion therefore requires the first nonzero finite-\(B\) coefficient of
\(\sigma_n\), with a rigorous remainder estimate.

There is also an exact Schur-complement formula for the first coefficient.
Write \(q=(\phi,\theta)\), \(F=(F_1,F_2)\), and let
\(J_n=F_q(0,\phi_n,T_n)\).  Differentiating the radial branch gives
\[
q_n'(0)=-J_n^{-1}F_\epsilon(0,\phi_n,T_n),
\]
and hence
\[
\sigma_n'(0)
=S_\epsilon-S_qJ_n^{-1}F_\epsilon
\quad\hbox{at }(0,\phi_n,T_n),
\tag{17}
\]
where \(S\) is the angular slip in (15).  On the entire restricted
rectilinear subspace \(S(0,\phi,\theta)\equiv0\), so \(S_q=0\) and
\[
\boxed{\sigma_n'(0)=S_\epsilon(0,\phi_n,T_n).}
\tag{18}
\]
Thus radial branch displacement cannot alter a genuinely nonzero linear
transverse coefficient.  If symmetry or matching makes \(S_\epsilon=0\),
the quadratic calculation must include the branch displacement.

## Exact first-order transverse target

The local vector field determines $S_\epsilon$ explicitly once first-order
incoming matching is available. Work in the rotation gauge whose incoming
heavy-binary axis is horizontal and write
\[
R=(r,0)+\epsilon(\varrho,\eta)+o(\epsilon),\qquad
Z=(\epsilon\xi,z+\epsilon\zeta)+o(\epsilon).
\tag{19}
\]
Put $d^2=z^2+r^2/4$. Direct linearization of the exact late equations gives
\[
\eta''=-{2\over r^3}\eta,
\qquad
\xi''={r^2-2z^2\over d^5}\xi.
\tag{20}
\]
There is no direct order-$\epsilon$ transverse force. The binary-axis gauge
has zero incoming data for $\eta$, so $\eta=0$. The exact initial relative
tilt $\ell=\epsilon/2+O(\epsilon^3)$ predicts the incoming conditions
\[
\xi+{z\over2}=O(|z|^{-1}),\qquad
\xi'+{z'\over2}=O(|z|^{-5/2})
\quad(z\to-\infty).
\tag{21}
\]
These weighted orders must still be proved by a differentiable matching
theorem; ordinary $o(1)$ state matching does not imply them.

At the restricted turn $z'(T_n)=0$. Therefore the first scaled Cartesian
transverse velocity coefficient and the angular-slip coefficient are
\[
C_n:=\xi'(T_n),\qquad
S_\epsilon(0,\phi_n,T_n)={C_n\over Z_n}.
\tag{22}
\]
The corresponding physical Cartesian velocity is
$\epsilon^{1/2}C_n+o(\epsilon^{1/2})$, because physical velocity is
$\epsilon^{-1/2}Z'$. Division by $Z_n$ in (22) is an angular rate, not a
Cartesian velocity.

The coefficient has two exact one-dimensional representations. Set
$c=(r^2-2z^2)/d^5$. If
\[
q''=cq,\qquad q(T_n)=1,\qquad q'(T_n)=0,
\]
then the Wronskian identity for $h=\xi+z/2$ gives
\[
\boxed{
C_n=-{3\over4}\int_{-\infty}^{T_n}
q\,{r^2z\over d^5}\,d\theta .
}
\tag{23}
\]
Equivalently, $p=-2\xi$ solves
\[
p''=cp,\qquad p-z=O(|z|^{-1}),
\]
and outer angular-momentum balance gives
\[
\boxed{
C_n=-{1\over2}p'(T_n)
=-{3\over4Z_n}\int_{-\infty}^{T_n}{r^2zp\over d^5}\,d\theta .
}
\tag{24}
\]
Both equations are regular through prescribed binary collisions in eccentric
anomaly. The integrands have no manifest sign; ordinary cutoff experiments
suggest that the lowest resonance has the opposite sign from the sampled
higher resonances. No uniform sign is claimed.

For orientation only, a cutoff-$40$ ordinary integration of (20) gives

| apocenter index $n$ | $Z_n$ | $C_n$ | $C_n/Z_n$ |
|---:|---:|---:|---:|
| 1 | 1.169875 | $+2.22120\times10^{-1}$ | $+1.89867\times10^{-1}$ |
| 2 | 2.289656 | $-9.58918\times10^{-3}$ | $-4.18805\times10^{-3}$ |
| 3 | 3.132754 | $-2.89333\times10^{-2}$ | $-9.23573\times10^{-3}$ |
| 7 | 5.714926 | $-2.82857\times10^{-2}$ | $-4.94944\times10^{-3}$ |
| 34 | 16.622813 | $-1.23429\times10^{-2}$ | $-7.42529\times10^{-4}$ |

These are **ORDINARY NUMERICAL EVIDENCE**, not enclosures. The lowest root
also lies well outside the small local phase interval used in the existence
theorem, so its sign change is only a warning against extrapolation. The table
is reproduced by `scripts/probe_restricted_turn_map.py`.

Combining (18) and (22) gives the precise local obstruction:
\[
\boxed{
D_n\ne0,\quad C_n\ne0,\quad\hbox{and first-order incoming matching}
\ \Longrightarrow\ \hbox{no finite-$B$ brake near resonance }n.
}
\tag{25}
\]
This is presently a conditional implication, not a promoted endpoint theorem.
For a fixed $n$, $D_n$ and $C_n$ are finite regularized variational quantities
that can in principle be validated. Uniform exclusion as $n\to\infty$ would
require asymptotics for both.

## What the present turn-map theorem does and does not prove

The current turn-map theorem proves continuity, divergence, and existence of
at least one root of \(\mathcal A(\phi)=2\pi n\) for every sufficiently large
\(n\).  It explicitly uses no monotonicity.  It therefore does **not** prove
(13): an analytic or \(C^1\) level crossing may have odd multiplicity greater
than one, and the \(C^0\) large-turn asymptotic does not control derivatives.
The validated transversality
\(\Delta'(0)\ne0\) at the parabolic center-section crossing is also not, by
itself, the late-turn statement \(\mathcal A'(\phi_n)\ne0\).

A sufficient repair would be a differentiable signed-energy asymptotic,
uniform on the finite-turn side, of the form
\[
\varepsilon(\phi)=\lambda|\phi|+o_{C^1}(|\phi|),
\qquad
T(\phi)={\pi\over\sqrt2}\,
\varepsilon(\phi)^{-3/2}\bigl(1+o_{C^1}(1)\bigr),
\tag{26}
\]
with \(\lambda>0\).  It would make \(T'\), hence
\(\mathcal A'\), sign-definite and unbounded near the parabolic phase, proving
that every sufficiently late resonance is simple.  Neither the
\(o_{C^1}\) energy coordinate nor this derivative asymptotic is currently
proved.  For a fixed \(n\), a validated integration of the phase variational
equation through the turn could instead certify (13).

There is a second, logically separate regularity obligation.  The incoming
tail theorem supplies uniform \(C^0\) matching of the exact skinny orbit to
the restricted phase family.  Applying the above IFT to the actual finite-
\(B\) family requires a \(C^1\) regularized extension such as (2), or a
degree argument that replaces it.  Moreover, if \(\phi\) is introduced as an
independent auxiliary phase, the exact Pythagorean family must still be
matched to the resulting curve \(\phi_n(B)\).  Only after the physical phase
clock is used as a valid local parameter is (16) literally a one-scalar
reduction for the tied family rather than for the extended phase family.

Status of (5)--(13): **EXACT SYMBOLIC IDENTITY**, conditional only on the
stated phase and scaled-coordinate conventions.

Status of the IFT continuation (14)--(18): **CONJECTURAL**, pending
\(D_n\ne0\) and a \(C^1\) finite-\(B\) regularized incoming family.

Status of the coefficient equations (20) and the representations (22)--(24):
**EXACT SYMBOLIC IDENTITY** for a solution \(\xi\) having the stated weighted
boundary data.  Existence of the finite-\(B\) expansion (19), identification
of its coefficient with that \(\xi\), and the incoming limit (21) remain
**CONJECTURAL**.  Status of (25): **CONJECTURAL**, pending its three displayed
hypotheses.

For the infinite late-resonance sequence, the nonvanishing hypothesis is no
longer an unrelated test at every index. `RESTRICTED_TRANSVERSE_SCATTERING.md`
proves, for every selection of resonance roots,
\[
Z_nC_n\longrightarrow-{\mathscr W_\infty\over2},
\]
where $\mathscr W_\infty$ is one finite rotation-Wronskian invariant of the
centered parabolic separatrix. The analytic half-line reduction and CAPD
certificate in that note prove $\mathscr W_\infty>21/50$, and therefore
$C_n<0$ at all sufficiently late restricted resonances. This does not by
itself repair radial simplicity or the finite-$B$ first-order incoming
theorem.
