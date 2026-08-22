# The late skinny plunge and its parabolic separatrix

The first-passage theorem does not reach escape. This note identifies the
next singular model and proves that a phase-uniform strict escape margin is
impossible even in that limit.

## Exact local scaling

Let $\epsilon=B$, $A=\sqrt{1-\epsilon^2}$, and use the heavy-pair Jacobi
vector $X=q_3-q_1$ and the outer light-body vector
\[
Y=q_2-{Aq_1+q_3\over A+1}.
\]
Near the later outer plunge, put
\[
X=\epsilon R,\qquad Y=\epsilon Z,\qquad
t=t_*+\epsilon^{3/2}\theta.
\]
The exact Jacobi equations show, uniformly on compact collision-free subsets,
\[
R_{\theta\theta}
=-(A+1){R\over|R|^3}
+\epsilon\left[
g\left(Z-{A\over A+1}R\right)
-g\left(Z+{1\over A+1}R\right)\right],
\]
and
\[
Z_{\theta\theta}
=-{A+1+\epsilon\over A+1}
\left[
A g\left(Z+{1\over A+1}R\right)
+g\left(Z-{A\over A+1}R\right)
\right],
\]
where $g(w)=w/|w|^3$. Therefore the local vector field tends to
\[
R_{\theta\theta}=-2{R\over|R|^3},
\]
\[
Z_{\theta\theta}
=-\left[g(Z+R/2)+g(Z-R/2)\right].
\tag{L}
\]

After Levi--Civita regularization of the prescribed heavy binary, this
convergence also holds through its binary collisions whenever $Z\ne0$. Status:
**PROVED ANALYTICALLY** as a local vector-field limit. Matching the exact
Pythagorean initial state to an incoming condition at scaled infinity,
uniformly over its diverging binary phase, remains open.

## Symmetric rectilinear restricted problem

The limiting equations have the invariant subspace
\[
R=(r,0),\qquad Z=(0,z).
\]
The binary is the regularized periodic rectilinear solution with apocenter
\[
r(0)=1,\qquad \dot r(0)=0,
\]
and the light body obeys
\[
\ddot z=-{2z\over(z^2+r^2/4)^{3/2}}.
\tag{S}
\]
The binary apocenter-to-apocenter period in $\theta$ is $\pi/2$. Its
eccentric-anomaly phase $\psi$ satisfies
\[
r=\cos^2\psi,\qquad d\theta=\cos^2\psi\,d\psi.
\]

For the instantaneous outer energy
\[
\mathcal E={1\over2}\dot z^2-{2\over\sqrt{z^2+r^2/4}},
\]
direct differentiation gives the exact exchange law
\[
\boxed{
\dot{\mathcal E}
={r\dot r\over2(z^2+r^2/4)^{3/2}}.
}
\tag{1}
\]
The outer body loses energy while the binary contracts and gains energy while
it expands.

## Parabolic-separatrix theorem

**Theorem.** There is a speed $v_*>0$ for which the solution of (S) with
\[
z(0)=0,\qquad \dot z(0)=v_*
\]
has no light--heavy or simultaneous collision, is strictly increasing for
positive time, and satisfies
\[
z(\theta)\longrightarrow+\infty,\qquad
\dot z(\theta)\longrightarrow0
\quad(\theta\to+\infty).
\]
By time reversal and reflection, it is a parabolic-to-parabolic scattering
orbit arriving from $z=-\infty$ and departing to $z=+\infty$, with the binary
at apocenter when $z=0$.

The heavy binary in this limiting auxiliary model still undergoes its
prescribed regularized binary collisions. This theorem is not a
post-collision continuation of any positive-$\epsilon$ physical solution and
is not itself a counterexample or a nonperiodicity result.

Status: **PROVED ANALYTICALLY** for the limiting restricted model.

### Proof

For $z>0$, equation (S) gives $\ddot z<0$, so $\dot z$ decreases until a
possible first turn.

Small launch speeds turn. To see this without numerics, divide the solution by
its launch speed and let that speed tend to zero before the first binary
collision. In eccentric-anomaly phase, the linear variational equation is
\[
\zeta_{\psi\psi}+2\tan\psi\,\zeta_\psi
+16\sec^2\psi\,\zeta=0,
\qquad \zeta(0)=0,\quad\zeta_\psi(0)=1.
\]
Putting $\zeta=\cos\psi\,w$ gives
\[
w_{\psi\psi}+(1+14\sec^2\psi)w=0.
\]
Sturm comparison with $w''+15w=0$ forces a simple zero
$\psi_0\le\pi/\sqrt{15}<\pi/2$. Choose $\psi_1$ just beyond it with
$\zeta(\psi_1)<0$. Smooth dependence of the nonlinear solution divided by its
launch speed, on the nonsingular interval $[0,\psi_1]$, gives a turn for every
sufficiently small positive launch speed.

Large launch speeds escape with a positive limiting speed. Fix
$T<\pi/4$ and let $r_0=\min_{[0,T]}r>0$. On this interval
\[
|\ddot z|\le C={16\over3\sqrt3\,r_0^2}.
\]
For launch speed $v$ large enough that $2/v<T$, at $\theta=2/v$ one has
\[
z\ge2-{2C\over v^2}>1,\qquad
\dot z\ge v-{2C\over v}.
\]
Thus at the first $z=1$ section the comparison energy below is positive.
Thereafter
\[
\ddot z\ge-{2\over z^2},
\]
so the radial comparison energy $\dot z^2/2-2/z$ is nondecreasing while
$\dot z>0$.

Let $\mathcal T$ be the set of launch speeds having a finite turn. This set is
nonempty by the small-speed argument, open because every turn is transverse,
and bounded above by the large-speed estimate. Put
\[
v_*=\sup\mathcal T.
\]
Then $v_*\notin\mathcal T$. Hence $\dot z>0$ for all positive time. Its
decreasing limit cannot be positive: otherwise, at some finite $z\ge1$
section, $\dot z^2/2-2/z>0$, an open escape condition contradicting turning
speeds approaching $v_*$ from below. If $z$ were bounded by $L$, then after
$z\ge z_1>0$,
\[
\ddot z\le-{2z_1\over(L^2+1/4)^{3/2}}<0,
\]
which would force a turn. Therefore $z\to\infty$ and $\dot z\to0$. The binary
state is even and the outer state is odd about $\theta=0$, proving the
two-sided parabolic statement.

## Consequence for the proof program

No phase-uniform theorem can send every nonsingular light-body scattering
solution of the regularized limiting plunge into a strict positive-energy
escape cone: the apocenter phase has the parabolic separatrix above.

The next viable skinny target is narrower:

1. prove a matched asymptotic map from the exact initial state to the incoming
   restricted scattering data;
2. compute the separatrix splitting at finite $\epsilon$, including the
   longitudinal symmetry-breaking term;
3. show that parameters landing on the nonescaping side still cannot produce
   a second brake, or derive an exact arithmetic condition for separatrix
   landing.

The diverging phase is therefore not mere technical noise. It meets an actual
zero-energy limiting phase, and any proof must resolve that interaction.
