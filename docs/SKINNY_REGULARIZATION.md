# Levi--Civita theorem for the first skinny encounter

This note upgrades the former frozen-tide calculation into an analytic
first-encounter theorem.  It does **not** yet prove eventual escape or exclude a
later second brake.

## Exact tight-pair Jacobi equations

Set

\[
\epsilon=B,\qquad A=\sqrt{1-\epsilon^2},\qquad M=A+1,
\]

and choose the inner and outer Jacobi vectors

\[
X=q_3-q_1,\qquad
Y=q_2-{Aq_1+q_3\over M}.
\]

Writing $\Phi(v)=v/|v|^3$, their exact relative equations are

\[
\ddot X=-M{X\over|X|^3}
+\epsilon\left[
\Phi\left(Y-{A\over M}X\right)
-\Phi\left(Y+{1\over M}X\right)
\right],
\]

\[
\ddot Y=-{M+\epsilon\over M}\left[
A\Phi\left(Y+{1\over M}X\right)
+\Phi\left(Y-{A\over M}X\right)
\right].
\]

Initially

\[
X=\epsilon(\epsilon,A),\qquad
Y=(A,-A\epsilon/M),\qquad \dot X=\dot Y=0.
\]

Rotate by the unit complex number $\epsilon-iA$, so that the scaled inner
vector starts on the positive real axis.  In this encounter frame the initial
outer vector is

\[
y_0=(A\epsilon/M,-A).
\]

Now set

\[
X=\epsilon x,\qquad
t={\epsilon^{3/2}\over\sqrt M}\tau.
\]

The inner equation becomes

\[
x_{\tau\tau}=-{x\over|x|^3}+F_\epsilon(x,y),
\]

where

\[
F_\epsilon={\epsilon^3\over M}\left[
\Phi\left(y-{A\epsilon\over M}x\right)
-\Phi\left(y+{\epsilon\over M}x\right)
\right].
\]

The outer acceleration in $\tau$-time is $O(\epsilon^3)$.  On a fixed first
encounter interval, $y-y_0=O(\epsilon^3)$.

## Levi--Civita system

Identify the plane with $\mathbb C$, put

\[
x=z^2,\qquad d\tau=|z|^2ds,
\]

and let $p=z_s$.  If

\[
E={1\over2}|x_\tau|^2-{1\over|x|}
\]

is the osculating inner Kepler energy, the exact regularized equations are

\[
z_s=p,
\]

\[
p_s={E\over2}z+{1\over2}|z|^2\bar z F_\epsilon(z^2,y),
\]

\[
E_s=2\operatorname{Re}(\bar z\,\bar p\,F_\epsilon),
\qquad
y_s=|z|^2w,
\]

and, for $w=y_\tau$,

\[
w_s=-|z|^2{\epsilon^3(M+\epsilon)\over M^2}
\left[
A\Phi\left(y+{\epsilon\over M}z^2\right)
+\Phi\left(y-{A\epsilon\over M}z^2\right)
\right].
\]

The outer denominators stay bounded away from zero near the limiting
encounter, so this is a real-analytic ODE in state and $\epsilon$ through
$z=0$.

At $\epsilon=0$,

\[
z_0(s)=\cos(s/\sqrt2),\qquad
p_0(s)=-{1\over\sqrt2}\sin(s/\sqrt2),\qquad E_0=-1.
\]

The regularized collision crossing is

\[
s_c={\pi\over\sqrt2},\qquad z_0(s_c)=0,
\qquad p_0(s_c)=-{1\over\sqrt2}.
\]

## First nonzero transverse variation

Along the limiting radial orbit, exact expansion of the frozen outer field
gives

\[
(F_\epsilon)_\parallel=-{1\over2}\epsilon^4R+O(\epsilon^5),
\qquad
(F_\epsilon)_\perp=-{3\over4}\epsilon^5R+O(\epsilon^6),
\]

where $R=|x|=z_0^2$.  Outer motion first affects the transverse coefficient at
higher order. Analyticity and invariance of the real subspace at
$\epsilon=0$ force all transverse parameter derivatives through order four
to vanish. Therefore, writing

\[
\operatorname{Im}z=\epsilon^5v+O(\epsilon^6),
\]

the order-five transverse variational equation is

\[
v_{ss}+{1\over2}v=-{3\over8}\cos^5(s/\sqrt2),
\qquad v(0)=v_s(0)=0.
\]

At the limiting crossing,

\[
v(s_c)=-{3\over4}\int_0^{\pi/2}\cos^6\theta\,d\theta
=\boxed{-{15\pi\over128}}.
\]

## Collision-exclusion theorem

Analytic dependence on $\epsilon$ gives

\[
\operatorname{Im}z(s_c,\epsilon)
=-{15\pi\over128}\epsilon^5+O(\epsilon^6).
\]

The real crossing is transverse because $p_0(s_c)=-1/\sqrt2$. Choose a fixed
neighborhood of $s_c$ on which $\partial_s\operatorname{Re}z<0$ for every
sufficiently small $\epsilon$. The analytic implicit-function theorem supplies
a unique
$s_*(\epsilon)=s_c+O(\epsilon^4)$ with
$\operatorname{Re}z(s_*,\epsilon)=0$, while

\[
\operatorname{Im}z(s_*,\epsilon)
=-{15\pi\over128}\epsilon^5+O(\epsilon^6)\ne0
\]

for every sufficiently small positive $\epsilon$.  Outside a fixed
neighborhood of $s_c$, the limiting $z_0$ is bounded away from zero and
ordinary continuous dependence excludes a zero. The outer separations remain
bounded away from zero. Hence no binary or triple collision occurs during
the first skinny encounter, defined here as the segment ending at any fixed
outgoing section $s_o=\sqrt2\theta_o$ with
$\pi/2<\theta_o<\pi$.

Moreover, minimizing $|z|^2$ near the transverse crossing gives

\[
\boxed{
r_{13,\min}
={225\pi^2\over16384}\epsilon^{11}(1+O(\epsilon)).
}
\]

The physical tight-pair angular momentum at closest passage satisfies

\[
\boxed{
h_{13}=-{15\pi\over64}\epsilon^{11/2}
+O(\epsilon^{13/2}).
}
\]

**Theorem.**  There exists $\epsilon_0>0$ such that every real
Pythagorean--Burrau member with $0<B<\epsilon_0$ is collision-free through its
first tight-pair encounter, with the two asymptotic formulas above.

Status: **PROVED ANALYTICALLY**. An independent adversarial derivation checked
the Jacobi equations, conjugations, time scaling, reduced-mass convention, and
both leading constants. This theorem covers near-collisions rather than
replacing them by collisions, but it does not control later returns.

## Why this is not yet a skinny nonperiodicity theorem

The binary remains strongly bound after the first passage. Its specific energy
is $-M/\epsilon+O(\epsilon^3)$, while the outer physical speed accumulated on a
fixed encounter section is only $O(\epsilon^{3/2})$. The terminal escape
criterion in ESCAPE_CRITERIA.md therefore fails with an order-one negative
margin immediately after this encounter.

On the later order-one outer fall time, the tight binary executes
$O(\epsilon^{-3/2})$ revolutions. Its phase at the subsequent close
three-body interaction has no limit as $\epsilon\to0$. The genuinely missing
lemma is a phase-uniform scattering or collision/escape dichotomy for that
interaction.
