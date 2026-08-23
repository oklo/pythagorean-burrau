# The parabolic tangent lemma in the restricted limit

This note closes the analytic implication left after the validated finite
Jacobi sign. It applies only to the auxiliary rectilinear restricted system;
it does not supply the uniform finite-$B$ matching theorem needed for the
Pythagorean--Burrau conjecture.

## Analytic compactification through binary collision

In eccentric anomaly,
\[
r(\psi)=\cos^2\psi,
\qquad
{d\theta\over d\psi}=r,
\]
the outgoing light-particle equations are
\[
z_\psi=rw,
\qquad
w_\psi=-{2zr\over(z^2+r^2/4)^{3/2}}.
\tag{1}
\]
The coefficient is analytic at each regularized binary collision
$r=0$. Compactify $z=+\infty$ by
\[
z={2\over x^2},\qquad x>0.
\]
Equation (1) becomes
\[
x_\psi=-{r\over4}x^3w,
\qquad
w_\psi=-{r\over2}x^4
\left(1+{r^2x^4\over16}\right)^{-3/2}.
\tag{2}
\]
This vector field extends real analytically to a full neighborhood of
$(x,w)=(0,0)$ and is $\pi$-periodic in $\psi$. Thus its time-$\pi$ map $P$ is
an analytic local diffeomorphism. Binary collision causes no loss of
regularity in this map.

Since $\int_0^\pi r\,d\psi=\pi/2$, the degree-four homogeneous part of $P-I$
is
\[
x_1=x-\frac\pi8x^3w+O_7(x,w),
\qquad
w_1=w-\frac\pi4x^4+O_7(x,w).
\tag{3}
\]
Here $O_7$ denotes an analytic remainder whose Taylor monomials have total
degree at least seven. Indeed, (2) starts in degree four; the second Picard
iterate starts in degree seven, and the first omitted force term starts in
degree eight.

For exact comparison with McGehee's celestial-mechanics normal form, set
$y=w/\sqrt2$ and $k=\pi\sqrt2/8$. Analytic divisibility in the exact flow
gives
\[
x_1=x-kx^3\bigl(y+R_1(x,y)\bigr),\qquad
y_1=y-kx^3\bigl(x+R_2(x,y)\bigr),
\tag{3a}
\]
where $R_1,R_2$ are analytic of order at least four. For exact divisibility,
write $x(\psi)=x_0u(\psi)$. Then $u(0)=1$ and the first equation of (2) gives
an analytic equation $u'=x_0^2u^3f$; hence
$x(\pi)-x_0=x_0^3A(x_0,w_0)$. Substitution in the second equation gives
$w(\pi)-w_0=x_0^4B(x_0,w_0)$ with analytic $A,B$. The $O_7$ remainder in
(3), after division by $x^3$, starts in degree four. Thus (3a) is the exact
form used in McGehee's Proposition 11, not merely a formal truncation.

Put
\[
X=x,\qquad Y=w-\sqrt2x,
\qquad k={\pi\sqrt2\over8}.
\]
Then (3) becomes
\[
\begin{aligned}
X_1&=X-\frac\pi8X^3(Y+\sqrt2X)+O_7(X,Y),\\
Y_1&=Y+kX^3Y+O_7(X,Y).
\end{aligned}
\tag{4}
\]
For the degree-four polynomial $p=P-I-O_7$,
\[
p_1(X,0)=-kX^4<0,
\qquad
p_2(X,0)=0,
\qquad
\partial_Yp_2(X,0)=kX^3>0
\tag{5}
\]
for $X>0$. These are exactly the sector hypotheses of McGehee's degenerate
stable-manifold theorem.

## Parabolic curves

**Lemma 1.** At every fixed regularized binary phase, the outgoing parabolic
initial conditions form a differentiable curve through infinity. Away from
infinity it is real analytic. The incoming parabolic curve has the same
regularity.

**Proof.** Apply Theorem 1 and Proposition 11 of McGehee (1973) to
(3a)--(5).
The positive-$X$ branch asymptotic to $Y=0$ is a graph
\[
Y=\varphi(X),\qquad \varphi(0)=\varphi'(0)=0,
\tag{6}
\]
analytic for $X>0$. More precisely, Propositions 2 and 5 in McGehee's graph
construction give an arbitrarily small Lipschitz constant when the sector is
narrowed. Since the graph is analytic for $X>0$, this yields
$|\varphi(X)|\le\beta X$ and $|\varphi'(X)|\le\beta$ there, with arbitrarily
small $\beta>0$. Analytic flow between fixed phase sections preserves this
regularity. The inverse map gives the incoming curve.
\(\square\)

The fixed-phase maps are analytically conjugate by the regularized flow, so
their stable graphs depend analytically on phase away from infinity. The
center crossing $z=0$ has nonzero light-particle speed $v_*$; the implicit-
function theorem therefore transports the graphs to analytic speed curves
$V_s(\phi)$ and $V_u(\phi)$ near the reversible apocenter crossing. Here
$V_u(\phi)>0$ is the speed of a parabolic orbit arriving from $z=-\infty$ and
crossing toward positive $z$, while $V_s(\phi)>0$ is the speed of an orbit
crossing toward positive $z$ and escaping to $z=+\infty$.

## Tangents on the stable branch contract

Restrict the first component of (4) to (6), writing $F(X)=X_1$. For arbitrarily
small fixed $\beta$, followed by sufficiently small $X$, equations (4)--(6)
give constants $c_1,c_2,c_3>0$ such that
\[
c_1X^4\le X-F(X)\le c_2X^4,
\qquad
0<F'(X)\le1-c_3X^3.
\tag{7}
\]
The derivative estimate uses the analytic $O_7$ remainder:
\[
F'(X)=1-4kX^3
-{\pi\over8}\left(3X^2\varphi(X)+X^3\varphi'(X)\right)
+O(X^6).
\tag{8}
\]

Let $X_{n+1}=F(X_n)$. The mean-value theorem applied to $X^{-3}$ and (7)
shows
\[
C_1n\le X_n^{-3}\le C_2n
\tag{9}
\]
for all sufficiently large $n$. Hence $\sum_nX_n^3=\infty$. A tangent
variation $\delta X_n$ along the parabolic curve therefore satisfies
\[
|\delta X_n|
=|(F^n)'(X_0)\delta X_0|
\le |\delta X_0|\exp\left(-c_3\sum_{j<n}X_j^3\right)
\longrightarrow0.
\tag{10}
\]

This is the only asymptotic consequence needed below. It avoids assuming a
decay rate merely from the word ``parabolic.''

## Tangency contradiction

For these conventions, the reversor $\widetilde z(t)=-z(-t)$ preserves the
positive crossing speed and changes the binary phase from $\phi$ to $-\phi$.
Hence at the reversible apocenter crossing,
\[
V_s(\phi)=V_u(-\phi).
\tag{11}
\]
If the two curves were tangent at $\phi=0$, equality of their slopes and (11)
would force $V_s'(0)=V_u'(0)=0$.

Make the gauge explicit in the extended center-section variables
$(\delta z,\delta w,\delta\phi)$. The global time-translation tangent and the
pinned stable-curve phase tangent are, respectively,
\[
T_{\rm time}=(v_*,0,1),\qquad
T_{\rm pin}=(0,V_s'(0),1)=(0,0,1).
\tag{11a}
\]
Both are tangents to the outgoing parabolic manifold. Their difference is the
fixed-phase stable tangent $(v_*,0,0)$. Let $\eta_{\rm pin}$ denote the
$z$-component of the second variation. Direct differentiation of the equations
gives
\[
\eta_{\rm pin}''=a\eta_{\rm pin}+br',
\qquad
z'''=az'+br'.
\]
Thus
\[
h=z'-\eta_{\rm pin}
\tag{12}
\]
is the fixed-phase homogeneous field
\[
h''=ah,\qquad h(0)=v_*,\quad h'(0)=0.
\]
Equation (11a) shows directly that the phase components cancel in (12), so
$h$ is a tangent to the fixed-phase stable curve of Lemma 1.

On the other hand, the analytic Wronskian argument proves $h(\pi/4)>0$, the
validated interval theorem proves $h'(\pi/4)>14/625$, and $a>0$ after
$\theta=\pi/8$. Therefore for $\theta\ge\pi/4$,
\[
h(\theta)\ge h(\pi/4)+{14\over625}(\theta-\pi/4).
\tag{13}
\]
At a fixed-phase stroboscopic sequence, $z=2/X_n^2$ and hence
\[
\delta X_n=-{X_n^3\over4}h(\theta_n).
\tag{14}
\]
One period in $\psi$ advances physical time by $\pi/2$, so
$\theta_n=\theta_0+n\pi/2$. Equations (9), (13), and (14) imply
\[
\liminf_{n\to\infty}|\delta X_n|>0,
\]
contradicting the tangent contraction (10).

We have proved:

**Theorem 2 (restricted transversality).** The incoming and outgoing
parabolic curves of the rectilinear equal-heavy-mass restricted system cross
transversely at their reversible apocenter-centered orbit.

The analytic inputs are the exact regularized map calculation and McGehee's
published stable-manifold theorem. The one computer-assisted input is the
finite Jacobi sign. Accordingly the status of Theorem 2 is **PROVED BY
COMPUTER-ASSISTED ARGUMENT**.

## Scope

Theorem 2 classifies the zero-energy threshold in the universal skinny
late-plunge limit. Together with the subsequently proved incoming-tail and
terminal-transfer theorems, it yields infinitely many open finite-$B$
nonperiodicity intervals. The remaining indispensable steps are:

1. persistence and signed finite-$B$ displacement of the transverse
   separatrix;
2. exclusion of second brakes on every captured branch, not only
   escape/capture classification.

Primary source: R. McGehee, “A Stable Manifold Theorem for Degenerate Fixed
Points with Applications to Celestial Mechanics,” *Journal of Differential
Equations* **14** (1973), 70--88,
<https://doi.org/10.1016/0022-0396(73)90077-6>.
