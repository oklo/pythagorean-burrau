# Finite-parameter splitting of the skinny separatrix

This note expands the exact late-scaled Jacobi field around the proved
equal-heavy restricted separatrix.  It identifies the first terms permitted
by symmetry.  The whole-line splitting functional below is formal until a
uniform incoming matching theorem and differentiability at parabolic infinity
are proved.

## Exact finite-$\epsilon$ field

Put
\[
\epsilon=B,qquad A=\sqrt{1-\epsilon^2},qquad M=1+A,qquad N=M+\epsilon,
\]
and evaluate the exact local field on
\[
R=(r,0),\qquad Z=(0,z),\qquad d^2=z^2+{r^2\over4}.
\]
Direct Taylor expansion gives
\[
\boxed{
r''=-{2\over r^2}-\epsilon{r\over d^3}
+{\epsilon^2\over2r^2}+O(\epsilon^3),
}
\tag{1}
\]
\[
\boxed{
Z_y''=-{2z\over d^3}-\epsilon{z\over d^3}
+\epsilon^2{z\over2d^3}+O(\epsilon^3),
}
\tag{2}
\]
and
\[
\boxed{
Z_x''=\epsilon^2{3r^3\over16d^5}+O(\epsilon^3).
}
\tag{3}
\]
Equations (1)--(3) are **EXACT SYMBOLIC IDENTITY** coefficient statements.
They show that outer-mass backreaction and symmetric potential rescaling begin
at order $\epsilon$, whereas the direct longitudinal failure of the limiting
perpendicular subspace begins only at order $\epsilon^2$.  In particular, the
perpendicular scalar subspace is not invariant for any $\epsilon>0$.

The exact positive outer potential is
\[
W_\epsilon={N\over M}\left[
{A\over|Z+R/M|}+{1\over|Z-AR/M|}
\right].
\tag{4}
\]
Writing $P=Z+R/2$ and $Q=Z-R/2$,
\[
W_\epsilon=W_0+\epsilon W_1+\epsilon^2W_2+O(\epsilon^3),
\]
where
\[
W_0={1\over|P|}+{1\over|Q|},\qquad W_1={1\over2}W_0,
\]
\[
W_2=-{1\over2|P|}-{P\mathbin\cdot R\over8|P|^3}
-{Q\mathbin\cdot R\over8|Q|^3}.
\tag{5}
\]
On $Z=(0,z)$ this reduces to
\[
W_0={2\over d},\quad W_1={1\over d},\quad W_2=-{1\over2d},
\quad
\partial_{Z_x}W_2={3r^3\over16d^5}.
\]

The exact initial scaled outer energy and geometric tilt are
\[
h_{Y,0}=-\epsilon{N\over M}\left(A+{1\over A}\right)
=-2\epsilon-\epsilon^2+O(\epsilon^4),
\tag{6}
\]
\[
\ell=\arctan{\epsilon\over1+A}
={1\over2}\arcsin\epsilon
={\epsilon\over2}+{\epsilon^3\over12}+O(\epsilon^5).
\tag{7}
\]
Only a matched statement of the form
$h_{\rm in}=-2\epsilon+o(\epsilon)$ is currently plausible at the incoming
restricted section; even that statement is not yet proved.  Equation (6)
alone does not control energy exchanged during the preceding
$O(\epsilon^{-3/2})$ binary cycles.

## Exact reversibility and its limitation

Let $S(x,y)=(x,-y)$.  Reflection followed by time reversal,
\[
(R,Z,\dot R,\dot Z)(\theta)
\longmapsto
(SR,SZ,-S\dot R,-S\dot Z)(-\theta),
\]
is an exact reversor for every mass choice.  Its fixed set at a crossing is
\[
R_y=Z_y=0,qquad \dot R_x=\dot Z_x=0.
\tag{8}
\]
A complete scattering orbit meeting this set has equal incoming and outgoing
asymptotic outer energies.  Reversibility does not prove that their common
value is zero, nor does it prove that a finite-$\epsilon$ parabolic orbit
exists.  Because of (3), any such orbit must bend longitudinally and will
generally require an additional impact-parameter shooting variable.

## Formal linear splitting functional

Let $(r,z)$ denote the centered parabolic solution of the restricted problem,
with $r$ even, $z$ odd, and binary apocenter at $\theta=0$.  Put
\[
F(r,z)=-{2z\over d^3},\qquad
a=F_z={4z^2-r^2/2\over d^5},\qquad
b=F_r={3zr\over2d^5}.
\]
For a binary perturbation $r\mapsto r+\delta\varrho$ and a direct vertical
acceleration $\delta f$, let
\[
\eta''=a\eta+b\varrho+f.
\tag{9}
\]
The base instantaneous outer energy
\[
E_0={1\over2}z'^2-{2\over d}
\]
satisfies $E_0'=rr'/(2d^3)$.  Formal differentiation of the total whole-line
energy gain gives
\[
\boxed{
\mathfrak M[\varrho,f]=
\int_{-\infty}^{\infty}\left[
{\varrho r'+r\varrho'\over2d^3}
-{3rr'\over2d^5}\left(z\eta+{r\varrho\over4}\right)
+z'f
\right]d\theta .
}
\tag{10}
\]

The order-$\epsilon$ centered deformation obeys
\[
\varrho''-{4\over r^3}\varrho=-{r\over d^3},
\qquad f=-{z\over d^3}.
\tag{11}
\]
For a reversible two-sided deformation, $\varrho$ is even and $\eta$ is odd;
every term in (10) is odd.  Therefore
\[
\mathfrak M[\varrho,-z/d^3]=0.
\tag{12}
\]
This is an **EXACT SYMBOLIC IDENTITY** parity cancellation conditional on the
existence of the indicated reversible variational solution.  It must not be
applied to a generic retarded incoming solution without proving the relevant
two-sided boundary conditions.

The mass-defect vertical forcing $z/(2d^3)$ is odd at order $\epsilon^2$, and
the longitudinal force (3) is perpendicular to the base vertical velocity.
Their direct linear energy-transfer terms also vanish on the centered
reversible orbit.  These cancellations deform the critical orbit; they do not
by themselves exclude a shifted finite-$\epsilon$ separatrix.

## Phase is the first symmetry-allowed splitting direction

Detune binary time phase by
\[
r_\sigma(\theta)=r(\theta+\sigma),
\]
so $\varrho=r'$.  If $\zeta$ is the incoming parabolic solution of
\[
\zeta''=a\zeta+br',
\tag{13}
\]
then the candidate phase coefficient is
\[
\boxed{
\kappa=\int_{-\infty}^{\infty}\left[
{r'^2+rr''\over2d^3}
-{3rr'\over2d^5}\left(z\zeta+{rr'\over4}\right)
\right]d\theta .
}
\tag{14}
\]
The phrase ``incoming parabolic solution'' needs an asymptotic gauge. Indeed,
$\zeta=z'$ solves (13), because it is the Jacobi field obtained by translating
the entire orbit in time. For that choice the integrand in (14) is exactly
\[
{d\over d\theta}\left({rr'\over2d^3}\right),
\tag{14a}
\]
so the whole-line integral is zero. Both $z'$ and its derivative tend to zero
at parabolic infinity, so naive zero boundary data there do not remove this
mode. One must fix the $|\theta|^{-1/3}$ parabolic time-origin coefficient or
use a finite Poincare section. This is an exact gauge obstruction, not a proof
that the physical phase coefficient vanishes.

A gauge-free formulation uses the section $z=0$. Let $V_u(\phi)$ be the
crossing speed of the incoming parabolic curve when the binary phase is
$\phi$, and let $V_s(\phi)$ be the outgoing parabolic curve. Reversibility
gives
\[
V_s(\phi)=V_u(-\phi).
\]
The centered separatrix is transverse precisely when
\[
\Delta'(0)=V_u'(0)-V_s'(0)=2V_u'(0)\ne0.
\tag{14b}
\]
Time reversal permits this linear term; it does not prove that the coefficient
is nonzero. In lifted mean anomaly, the convention used in
`SKINNY_MATCHING.md` gives $\delta\Phi=4\sigma$.

Finite-cutoff ordinary integrations, using zero instantaneous energy at
$z=\pm L$, give

| $L$ | centered launch speed | $V_u'(0)-V_s'(0)$ |
|---:|---:|---:|
| 10 | 2.905102038901 | -0.906026504100 |
| 20 | 2.905107715066 | -0.906232318112 |
| 40 | 2.905111335972 | -0.906230148693 |

This is **ORDINARY NUMERICAL EVIDENCE**, reproduced by
`scripts/probe_restricted_transversality.py`; it is not an enclosure of the
infinite-endpoint curves.

After fixing this gauge, denote the physical section coefficient by $\kappa$.
The resulting candidate expansion is
\[
\boxed{
\mathcal S(\epsilon,\sigma,\ell)
=h_{\rm in}(\epsilon)+\kappa\sigma+Q_\ell\ell^2
+O(\epsilon\sigma+\sigma^3+\hbox{matching remainders}).
}
\tag{15}
\]
Equal-heavy reflection makes scattering energy even in the tilt $\ell$, so
the geometric tilt first contributes at order $\epsilon^2$.  If
$h_{\rm in}=-2\epsilon+o(\epsilon)$ and $\kappa\ne0$, (15) predicts a shifted
separatrix
\[
\sigma_*(\epsilon)={2\over\kappa}\epsilon+o(\epsilon).
\tag{16}
\]
If $\kappa=0$, oddness permits a cubic phase term and changes the natural
balance to $\sigma=O(\epsilon^{1/3})$.

## Exact status and next theorem

The field, potential, initial-energy, tilt, and algebraic parity formulas are
exact.  The following indispensable steps remain **CONJECTURAL**:

1. uniform Levi--Civita matching through $O(\epsilon^{-3/2})$ preceding
   collision-like binary cycles, with $o(1)$ lifted phase error;
2. a function-space construction of the parabolic variational solutions in
   (9) and (13) and convergence of the improper integrals;
3. proof or validated enclosure of (14b), equivalently $\kappa\ne0$ in a
   fixed phase normalization;
4. control of the remainders in (15), uniformly in the $O(\epsilon)$ phase
   window;
5. exclusion of a second brake on the captured side of the shifted
   separatrix.

Even a proof of (16) would classify escape versus capture; it would not alone
prove nonperiodicity on the captured side.
