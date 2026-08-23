# Matching toward the late skinny plunge

This note isolates the exact reference phase and incoming energy used by the
uniform matching theorem. The later PREPLUNGE_MATCHING.md and
INCOMING_TAIL.md notes prove full shadowing through the intervening binary
cycles and down to a fixed restricted section.

## Collapsed-pair reference fall

Put
\[
\epsilon=B,\quad A=\sqrt{1-\epsilon^2},\quad
M=1+A,\quad N=M+\epsilon.
\]
The exact initial outer Jacobi radius is
\[
\rho_0^2={2A^2\over M}.
\]
With the binary unit vector $e=(\epsilon,A)$ and its positive quarter-turn
$n=(-A,\epsilon)$, the exact initial data are
\[
X(0)=\epsilon e,\qquad
Y(0)={A\epsilon\over M}e-A n.
\]
Thus the product of the two direction cosines of $Y(0)$ is
\[
\sin\gamma\cos\gamma=-{\epsilon\over2},
\]
and its acute tilt from the perpendicular is
\[
\ell=\arctan{\epsilon\over1+A}
={1\over2}\arcsin\epsilon.
\]
Replace the tight binary by a point mass $M$ while retaining the exact outer
relative gravitational parameter $N$. Radial fall from rest has collision
time
\[
t_{\rm mono}
={\pi\rho_0^{3/2}\over2\sqrt{2N}}.
\tag{1}
\]
The unperturbed radial binary of apocenter $\epsilon$ has mean motion
\[
n_{\rm bin}={\sqrt{8M}\over\epsilon^{3/2}}.
\]
Consequently its reference mean anomaly at the monopole collision is
\[
\boxed{
\Phi_{\rm ref}(\epsilon)
={\pi\over\epsilon^{3/2}}
\sqrt{M\over N}\,\rho_0^{3/2}.
}
\tag{2}
\]
All statements in this section are **EXACT SYMBOLIC IDENTITY** for the
decoupled reference problem.

At an incoming radius $\rho\in(0,\rho_0)$, put
\[
\vartheta=\arccos\sqrt{\rho/\rho_0}.
\]
The exact reference section data are
\[
t_0(\rho)=\sqrt{\rho_0^3\over2N}
(\vartheta+\sin\vartheta\cos\vartheta),
\qquad
\dot\rho=-\sqrt{2N(\rho^{-1}-\rho_0^{-1})}.
\tag{2a}
\]
Moreover
\[
t_{\rm mono}-t_0(\rho)
={2\rho^{3/2}\over3\sqrt{2N}}
+{\rho^{5/2}\over5\sqrt{2N}\rho_0}+O(\rho^{7/2}).
\tag{2b}
\]
These formulas define the clock on a nonsingular matching section rather than
only at the point-mass collision.

Expansion at the skinny endpoint gives
\[
\boxed{
\Phi_{\rm ref}
=\pi\epsilon^{-3/2}
-{\pi\over4}\epsilon^{-1/2}
-{15\pi\over32}\epsilon^{1/2}
+O(\epsilon^{3/2}).
}
\tag{3}
\]
Thus two divergent terms, not just the leading
$\pi\epsilon^{-3/2}$ term, are required to know the binary phase modulo
$2\pi$ with an $o(1)$ error.

If $\mathcal N_{\rm ref}=\Phi_{\rm ref}/(2\pi)$ is the reference cycle count,
then
\[
\boxed{
\mathcal N_{\rm ref}^4
={A^6\over2MN^2\epsilon^6}.
}
\tag{4}
\]
For a rational Pythagorean parameter, $A$ and $\epsilon=B$ are rational, so
the fourth power is rational. This is not an arithmetic obstruction for the
true flow: (4) concerns only the decoupled clock.

The center clock also has the exact asymptotic derivative
\[
\Phi_{\rm ref}'(\epsilon)
=-{3\pi\over2}\epsilon^{-5/2}+O(\epsilon^{-3/2}).
\tag{4a}
\]
It is therefore strictly decreasing on some punctured endpoint interval and
tends to infinity there.

There are several phase gauges, and they must not be confused. Fix a large
but finite restricted incoming section
\[
\Sigma^-_{Y_0}=\{z=-Y_0,\ w>0\},\qquad Y_0>0,
\]
and put $\rho=\epsilon Y_0$ in (2a). The raw reference binary phase on that
section is
\[
\Phi_{\rm sec,ref}(\epsilon;Y_0)
:=n_{\rm bin}t_0(\epsilon Y_0).
\tag{4b}
\]
It is not $\Phi_{\rm ref}$: by (2b),
\[
\Phi_{\rm sec,ref}
=\Phi_{\rm ref}
-{4\over3}\sqrt{M\over N}\,Y_0^{3/2}+O(\epsilon).
\tag{4c}
\]
For fixed $Y_0$, however,
\[
\Phi_{\rm sec,ref}'(\epsilon;Y_0)
=-{3\pi\over2}\epsilon^{-5/2}+O(\epsilon^{-3/2}),
\tag{4d}
\]
so the monopole section phase is also strictly decreasing and tends to
infinity. It is an exact reference identity, but it is not the final matching
coordinate. Between scaled infinity and fixed $Y_0$, the restricted binary
quadrupole produces a finite phase-dependent flight correction. Thus the raw
true phase at $\Sigma^-_{Y_0}$ need not differ from (4b) by $o(1)$.

The invariant coordinate is the **incoming asymptotic phase intercept**. If a
raw binary phase $\Phi_\rho$ is recorded at an early overlap radius
$\rho=\epsilon Y$ with $Y\to\infty$, define
\[
\chi_\rho
:=\Phi_\rho+n_{\rm bin}\bigl(t_{\rm mono}-t_0(\rho)\bigr)
\pmod {2\pi}.
\tag{4e}
\]
The added term is the exact monopole phase remaining to the collapsed center.
For a restricted incoming parabolic orbit, (4e) has a limit as
$Y\to\infty$; the difference between the restricted and monopole tails is
$O(Y^{-1/2})$. This limit $\chi$ labels the incoming restricted scattering
curve. The collapsed-pair reference has exactly
\[
\chi_{\rm ref}(\epsilon)=\Phi_{\rm ref}(\epsilon).
\tag{4f}
\]
The raw state on a fixed section is a nontrivial smooth function of $\chi$,
obtained by the full restricted incoming flow.

For every nonempty open intercept arc
$J\subset\mathbb R/(2\pi\mathbb Z)$, the set
\[
\{u>0:\Phi_{\rm ref}(B(u))\bmod2\pi\in J\}
\]
contains infinitely many open intervals accumulating at $u=0$, and every
such interval contains rational $u$. This exact theorem acquires dynamical
force only after full-state matching to the restricted incoming curve with
intercept $\Phi_{\rm ref}$, and only for an open scattering condition, not for
hitting one exact separatrix phase.

## Incoming local energy

Under the late scaling $Y=\epsilon Z$ and
$t-t_*=\epsilon^{3/2}\theta$, physical outer specific energy is
$\epsilon^{-1}$ times local scaled energy. The monopole reference value at
the initial rest state is
\[
\mathcal E_{\rm in,ref}
=-{\epsilon N\over\rho_0}
=-2\epsilon-\epsilon^2-\frac14\epsilon^3+O(\epsilon^4).
\tag{5}
\]
The limiting restricted orbit is therefore parabolic, but the first finite
parameter correction lies on the bound side and is order $\epsilon$.

For comparison, the exact full outer Jacobi potential at the original brake
point gives
\[
\mathcal E_{Y,0}
=-\epsilon{N\over M}\left(A+{1\over A}\right)
=-2\epsilon-\epsilon^2+O(\epsilon^4).
\tag{5a}
\]
It agrees with (5) through order $\epsilon^2$ but is not identical.
Transporting (5a) to the incoming plunge section with a controlled remainder
is part of the matching problem.

At the exactly symmetric apocenter phase, time reversal makes an incoming
negative-energy passage leave with the same negative energy. Escape windows
can only arise from phase-dependent energy transfer or from symmetry-breaking
corrections.

## Uniform shadowing target and resolution

Choose an intermediate radius
\[
\rho=\epsilon^\alpha,\qquad 0<\alpha<1.
\]
There the binary is still much smaller than the outer separation, while the
late scaled outer radius tends to infinity. Formal force estimates give:

- outer quadrupole acceleration relative to the monopole:
  $O(\epsilon^2/\rho^2)$;
- binary tidal acceleration relative to its Kepler acceleration:
  $O(\epsilon^4/\rho^3)$;
- accumulated reference-phase error from the outer quadrupole:
  $O(\epsilon^{1/2-\alpha/2})$;
- accumulated binary tidal phase error:
  $O(\epsilon^{5/2-3\alpha/2})$.

Both displayed phase errors tend to zero for every fixed $0<\alpha<1$.
Equivalently, put $\rho=\epsilon Y$. The exact relation between the center
and raw section clocks is
\[
\begin{split}
\Phi_\rho={}&\Phi_{\rm ref}
-{4\over3}\sqrt{M\over N}\,Y^{3/2}\\
&-{2\over5}{\epsilon\over\rho_0}\sqrt{M\over N}\,Y^{5/2}
+O(\epsilon^2Y^{7/2}).
\end{split}
\tag{5b}
\]
A convenient nonempty overlap is
$1\ll Y\ll\epsilon^{-2/5}$.  For the degenerate Kepler binary,
\[
\langle |X|^2\rangle={5\over8}\epsilon^2.
\]
Formal averaging suggests an outer-quadrupole arrival correction
$(5/32)\sqrt{\epsilon/\rho}$ and a direct binary tidal phase correction of
order $\epsilon^{5/2}\rho^{-3/2}$; this particular coefficient remains
**CONJECTURAL** and is not used. The uniform theorem below is instead proved
by direct LC block estimates.
Let $S_\epsilon(Y_0)$ be the full regularized state at the first
collision-free crossing of $\Sigma^-_{Y_0}$, and let
$\Gamma^-_{Y_0}(\chi)$ be the restricted incoming parabolic state on that
section with asymptotic intercept $\chi$. The gauge-consistent target is
\[
\operatorname{dist}\!\left(
S_\epsilon(Y_0),
\Gamma^-_{Y_0}(\Phi_{\rm ref}(\epsilon))\right)=o(1).
\tag{6}
\]
Circular intercept distance is sufficient; no integer-valued lift is required
for the open phase windows. PREPLUNGE_MATCHING.md proves the long-cycle
part: at every deliberately early overlap
$\rho=\epsilon^\alpha$, $0<\alpha<1/6$, the renormalized true intercept (4e)
has distance $o(1)$ from $\Phi_{\rm ref}$, unless an earlier classical
collision already excludes periodicity. INCOMING_TAIL.md proves the full
fixed-section statement (6) by uniform propagation from that overlap to fixed
$Y_0$ in the full restricted scaling. Status: **PROVED ANALYTICALLY**.

Equation (6), combined with strict terminal regions of the limiting scattering
map, gives infinitely many shrinking nonperiodicity windows accumulating at
$\epsilon=0$.

Féjoz's rigorous Levi--Civita averaging theorem shows that regularized and
unregularized averaged planar three-body Hamiltonians agree near inner
collisions. It provides the correct coordinate framework, but does not by
itself make (6) uniform in this singular regime. The elementary regularized
estimate in PREPLUNGE_MATCHING.md avoids finite-eccentricity averaging for
the long early cycle train. Féjoz's framework may still be useful for a
sharper expansion, but is no longer needed merely to reach the early overlap.
