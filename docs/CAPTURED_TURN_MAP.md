# The finite-turn map in the rectilinear restricted limit

The finite-turn side of the transverse restricted separatrix contains
infinitely many simultaneous zero-velocity resonances. They accumulate at the
parabolic phase. This is an exact statement about the collision-regularized,
equal-heavy-mass rectilinear restricted problem. It is not a classical
three-body periodic orbit: before a late outer turn, the prescribed heavy
binary has undergone regularized binary collisions.

## Conventions

At the center section $z=0$, let $V_u(\phi)$ be the speed of the orbit arriving
parabolically from $z=-\infty$, and let $V_s(\phi)$ be the outgoing parabolic
threshold.  As in `RESTRICTED_PHASE_WINDOWS.md`, put

\[
\Delta(\phi)=V_u(\phi)-V_s(\phi),
\qquad \Delta(0)=0,
\qquad \Delta'(0)\ne0.
\tag{1}
\]

Choose one fixed sufficiently small finite-turn phase $\phi_*$ and let
$I_{\rm ret}$ be the half-open segment from zero to $\phi_*$, excluding zero
and including $\phi_*$.  Thus $\Delta<0$ throughout $I_{\rm ret}$, and the
only noncompact end of this chosen local interval is the parabolic phase
$0$.  For $\phi\in I_{\rm ret}$, launch the outgoing restricted orbit from

\[
z(0)=0,\qquad z'(0)=V_u(\phi)>0.
\tag{2}
\]

The binary phase $\phi$ is normalized as lifted mean anomaly.  In the
equal-heavy restricted scaling it advances exactly as

\[
\Lambda(\theta)=\phi+4\theta.
\tag{3}
\]

Binary apocenters are the sections $\Lambda\in2\pi\mathbb Z$.  Formula (3)
is regular through binary collision. In eccentric anomaly put
$\ell(\psi)=2\psi+\sin2\psi$. If the center crossing has anomaly $\psi_0$,
choose the lift with $\ell(\psi_0)=\phi$; elapsed physical time then satisfies
$\ell(\psi)-\ell(\psi_0)=4\theta$, which is exactly (3).

## The first-turn map

For every $\phi\in I_{\rm ret}$, the escape/turn theorem gives a finite first
time $T(\phi)>0$ such that

\[
z'(T(\phi))=0,
\qquad z'(\theta)>0\quad(0\leq\theta<T(\phi)).
\tag{4}
\]

Define the turn height and the lifted turn phase

\[
Z_{\rm t}(\phi)=z(T(\phi)),
\qquad
\mathcal A(\phi)=\phi+4T(\phi).
\tag{5}
\]

The orbit has a nonsingular brake state of the collision-regularized
restricted flow at its first outer turn exactly when

\[
\boxed{\mathcal A(\phi)\in2\pi\mathbb Z.}
\tag{6}
\]

Indeed, $z'=0$ by definition of the turn, while (6) says that the heavy
binary is at apocenter and hence has zero velocity.

**Lemma 1 (continuity and divergence).**  The functions $T$, $Z_{\rm t}$,
and $\mathcal A$ are continuous on $I_{\rm ret}$, and

\[
T(\phi)\longrightarrow+\infty,
\qquad
Z_{\rm t}(\phi)\longrightarrow+\infty,
\qquad
\mathcal A(\phi)\longrightarrow+\infty
\tag{7}
\]

as $\phi\to0$ through the finite-turn side.

**Proof.**  While $z>0$,

\[
z''=-{2z\over(z^2+r^2/4)^{3/2}}<0.
\tag{8}
\]

Thus the first zero of $z'$ is unique and transverse in physical time.  The
regularized equations depend continuously on the center phase, including
through prescribed binary collisions, so the first-turn time and state are
continuous.

The initial data converge to the outgoing parabolic separatrix as
$\phi\to0$ in $I_{\rm ret}$.  On every finite regularized time interval the
corresponding solutions converge to that separatrix, whose velocity remains
positive at every finite time.  A bounded sequence of first-turn times would
therefore give a finite zero of the separatrix velocity, a contradiction.
Hence $T\to\infty$.

If $Z_{\rm t}$ remained bounded along a sequence, choose a small fixed
$h>0$.  Finite-time convergence to the separatrix shows that all nearby
orbits reach $h$ in uniformly bounded time, with uniformly bounded positive
velocity, and that their turn heights are bounded below by $h$.  If the turn
heights are also bounded above by $M$, then on $h\le z\le M$ equation (8)
has a uniform negative upper bound, independent of the binary phase.  The
remaining time to turn is therefore uniformly bounded.  This contradicts
$T\to\infty$, so $Z_{\rm t}\to\infty$.  Equation (3) now gives
$\mathcal A\to\infty$. \(\square\)

## Infinitely many restricted zero-velocity resonances

**Theorem 2 (apocenter-turn resonances).**  There is an integer $n_0$ such
that, for every integer $n\ge n_0$, at least one phase
$\phi_n\in I_{\rm ret}$ satisfies

\[
\mathcal A(\phi_n)=2\pi n.
\tag{9}
\]

Every such phase gives a nonsingular brake state of the
collision-regularized restricted flow at the first outer turn. Any choice of
solutions with $n\to\infty$ satisfies $\phi_n\to0$.

**Proof.**  By Lemma 1, the continuous function $\mathcal A$ takes
arbitrarily large values between $0$ and $\phi_*$ on the finite-turn side. For
every sufficiently large $n$ with $2\pi n>\mathcal A(\phi_*)$, choose a
phase closer to zero for which $\mathcal A>2\pi n$.  The intermediate-value
theorem between that phase and $\phi_*$ gives (9).

For every compact subinterval of $I_{\rm ret}$ separated from zero,
$\mathcal A$ is bounded.  Hence solutions of (9) with $n\to\infty$ must
accumulate at zero. \(\square\)

No monotonicity of the turn map is needed.  The theorem also permits more than
one brake phase for a given apocenter index.

## Kepler asymptotic of the turn map

The resonance heights have a universal leading asymptotic that does not
require a differentiable energy coordinate transverse to the parabolic
manifold.

**Lemma 3 (large-turn scaling).**  As $\phi\to0$ through $I_{\rm ret}$,

\[
\boxed{
T(\phi)={\pi\over4}Z_{\rm t}(\phi)^{3/2}\bigl(1+o(1)\bigr),
\qquad
\mathcal A(\phi)=\pi Z_{\rm t}(\phi)^{3/2}\bigl(1+o(1)\bigr).
}
\tag{10}
\]

**Proof.**  Put $Z=Z_{\rm t}(\phi)$ and measure backward scaled time from
the turn by

\[
s={T(\phi)-\theta\over Z^{3/2}},
\qquad q(s)={z(\theta)\over Z}.
\tag{11}
\]

There is a phase-independent energy comparison on the whole large-radius
outgoing leg.  With $w=z'>0$, define

\[
H_K={1\over2}w^2-{2\over z}.
\]

Using $z$ itself as the independent variable gives the exact identity

\[
{dH_K\over dz}
=z''+{2\over z^2}
={2\over z^2}\left[1-
 \left(1+{r^2\over4z^2}\right)^{-3/2}\right].
\]

Since $0\le r\le1$ and
$0\le1-(1+x)^{-3/2}\le(3/2)x$, integration backward from
$z=Z$, where $w=0$ and $H_K=-2/Z$, yields, uniformly in phase,

\[
H_K(z)=-{2\over Z}-\delta(z),
\qquad
0\le\delta(z)\le {1\over4z^3},
\tag{12}
\]

and hence

\[
w(z)^2=4\left({1\over z}-{1\over Z}\right)-2\delta(z).
\tag{13}
\]

On every region $q\ge\eta>0$, the exact equation becomes

\[
q_{ss}=-{2q\over(q^2+r^2/(4Z^2))^{3/2}}
       =-{2\over q^2}+O_\eta(Z^{-2}),
\tag{14}
\]

with $q(0)=1$ and $q_s(0)=0$.  Continuous dependence therefore gives the
zero-angular-momentum Kepler fall from apocenter on every compact region
$q\ge\eta$.  Its elapsed scaled time from $q=1$ to $q=0$ is

\[
\int_0^1 {dq\over2\sqrt{q^{-1}-1}}={\pi\over4}.
\tag{15}
\]

For completeness, (13) also supplies the comparison needed to pass from a
fixed $\eta$ to zero.  Choose $\eta<1/2$ and then $K$ large enough.  On
$K\le z\le\eta Z$, (12)--(13) imply $w(z)^2\ge c/z$ for an absolute
$c>0$.  Consequently

\[
\int_K^{\eta Z}{dz\over w(z)}\le C(\eta Z)^{3/2}.
\]

Finite-time convergence to the parabolic separatrix makes the time from
$z=0$ to $z=K$ uniformly bounded for fixed $K$, hence negligible after
division by $Z^{3/2}$.  Thus the omitted inner scaled time is at most
$C\eta^{3/2}+o(1)$.  Letting first $Z\to\infty$ and then $\eta\to0$
proves the first formula in (10).  The second follows from (5), since $\phi$
is bounded and the lifted binary mean anomaly advances at rate four.
\(\square\)

At an apocenter resonance (9), Lemma 3 gives

\[
\boxed{
Z_{\rm t}(\phi_n)=(2n)^{2/3}(1+o(1)),
\qquad
T(\phi_n)={\pi n\over2}+o(1).
}
\tag{16}

The second formula also follows exactly from
$T(\phi_n)=\pi n/2-\phi_n/4$ and $\phi_n\to0$.

A further parameter asymptotic would require a signed energy coordinate
$\varepsilon(\phi)$ transverse to the parabolic stable curve.  If one proves

\[
\varepsilon(\phi)=\lambda |\phi|+o(|\phi|),
\qquad \lambda>0,
\tag{17}
\]

then the Kepler relation $Z_{\rm t}=2/\varepsilon+o(\varepsilon^{-1})$
would give

\[
|\phi_n|={2^{1/3}\over\lambda}\,n^{-2/3}(1+o(1)).
\tag{18}

Equation (18) is **CONDITIONAL**; Theorem 2 and the height asymptotic (16)
do not depend on it.

## Consequences for the skinny program

The finite-turn side of the restricted phase window cannot be dismissed by a
uniform assertion that every returning trajectory has a moving binary at its
outer turn. There are infinitely many exact phase resonances where the first
outer turn is a nonsingular brake state of the collision-regularized
restricted flow.

These resonances do not disprove the Pythagorean--Burrau conjecture.  The
heavy binary has undergone regularized collisions before the turn, the
finite-$B$ problem avoids those collisions by a very small angular momentum,
and a restricted zero-velocity state need not persist as an exact finite-$B$
brake. Their role is instead a bifurcation warning: any finite-$B$ post-turn
proof must compute how the two zero-velocity conditions split near the
resonance sequence, or find a different obstruction that survives it.

Status of Lemma 1 and the turn-map/IVT step in Theorem 2:
**PROVED ANALYTICALLY**.  The unconditional existence of the finite-turn local
interval imports the validated transversality theorem, so the full resonance
existence result is **PROVED BY COMPUTER-ASSISTED ARGUMENT**.

Status of Lemma 3 and (16): **PROVED ANALYTICALLY**, using the uniform radial
comparison on the large-turn tail.

Status of (18): **CONJECTURAL pending construction of the transverse energy
coordinate**.
