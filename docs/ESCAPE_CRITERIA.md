# A terminal binary--escaper certificate

This note proves a checkable sufficient condition that rules out every future
brake once an outgoing binary--single state has been reached. It is not a
claim that the initial Pythagorean--Burrau state satisfies the condition.

## Theorem

Let bodies of masses $m_a,m_b$ form a prospective binary and let $m_c$ be the
prospective escaper. Put

\[
M=m_a+m_b,\qquad \mathcal M=M+m_c,
\]

\[
x=q_b-q_a,\qquad
y=q_c-{m_aq_a+m_bq_b\over M},\qquad
r=|x|,\quad \rho=|y|,
\]

and define the inner specific energy

\[
e={1\over2}|\dot x|^2-{M\over r}.
\]

At a collision-free time $t_0$, choose $\eta>0$ and set

\[
R={M\over\eta},\qquad s_0=\rho_0-R.
\]

Assume the following strict inequalities:

\[
s_0>0,\qquad \dot\rho_0>0,
\]

\[
\delta={1\over2}\dot\rho_0^2-{\mathcal M\over s_0}>0,
\qquad v=\sqrt{2\delta},
\]

and

\[
e_0+{m_c\sqrt{2MR}\over v s_0^2}<-\eta.
\tag{E}
\]

Then the future maximal classical solution either ends in an inner binary
collision, or for every $t\ge t_0$ it satisfies

\[
e(t)<-\eta,\qquad r(t)<R,\qquad
\dot\rho(t)\ge v,\qquad
\rho(t)\ge\rho_0+v(t-t_0).
\]

In the second alternative body $c$ escapes to infinity. In either alternative
there is no later classical second brake.

Status: **PROVED ANALYTICALLY**.

## Proof

Write $\alpha=m_b/M$, $\beta=m_a/M$, and $g(z)=z/|z|^3$. The inner Jacobi
equation is

\[
\ddot x=-M{x\over r^3}
+m_c\{g(y-\beta x)-g(y+\alpha x)\}.
\]

When $\rho>r$, both outer separations are at least $\rho-r$. The exact outer
Jacobi equation is a positive mass-weighted sum of their fields, hence

\[
|\ddot y|\le {\mathcal M\over(\rho-r)^2}.
\tag{1}
\]

The eigenvalues of $Dg(z)$ are $|z|^{-3}$ in the transverse direction and
$-2|z|^{-3}$ in the radial direction. The mean-value formula along the
segment between $y-\beta x$ and $y+\alpha x$ therefore gives

\[
|\dot e|\le {2m_c r|\dot x|\over(\rho-r)^3}.
\tag{2}
\]

Bootstrap on $e<-\eta$. This inequality implies

\[
r<R,\qquad r|\dot x|<\sqrt{2MR}.
\tag{3}
\]

While $\dot\rho>0$, (1) and the radial acceleration identity give

\[
\ddot\rho\ge-{\mathcal M\over(\rho-R)^2}.
\]

Consequently

\[
J={1\over2}\dot\rho^2-{\mathcal M\over\rho-R}
\]

is nondecreasing. Its initial value is $\delta$, so
$\dot\rho\ge v$ and $\rho\ge\rho_0+v(t-t_0)$. Combining these bounds with
(2)--(3), the total possible future increase of $e$ is less than

\[
2m_c\sqrt{2MR}\int_0^\infty{dt\over(s_0+vt)^3}
={m_c\sqrt{2MR}\over v s_0^2}.
\]

The strict margin in (E) closes the bootstrap. It also maintains
$\rho>R>r$, excluding either outer binary collision. The only remaining
finite-time singularity is the inner collision already allowed in the
dichotomy. Since $\dot\rho$ stays positive, a later brake is impossible.

## Role in the skinny program

The certificate cannot fire during the first tight-pair passage. There
$r=O(B)$, $\rho=1+O(B^2)$, and the regularized equations give the physical
outer speed $O(B^{3/2})$. For every choice $R=O(B)$,

\[
{1\over2}\dot\rho^2-{A+B+1\over\rho-R}=-2+O(B)<0.
\]

Thus the proved $B^{11}$ first miss is a collision resolution, not an escape
argument. The outer light body falls inward on an order-one time scale while
the binary period is $\sim(\pi/2)B^{3/2}$, so the binary completes
$\sim(2B^{3/2})^{-1}$ cycles before the later close interaction. The missing
skinny theorem is a phase-uniform scattering or collision/escape dichotomy at
that later interaction. Once an outgoing section is enclosed, the theorem
above is designed to terminate the proof using strict interval inequalities.

## Relation to published criteria

Standish's [sufficient escape conditions](https://doi.org/10.1007/BF01230319)
and Yoshida's [improved hyperbolic--elliptic
criteria](https://doi.org/10.1093/pasj/24.3.391) are closely related global
inequality certificates. Yoshida applied his criterion to a numerically
reported $3{:}4{:}5$ trajectory, but that historical decimal application is
not an interval proof for the exact initial condition.

The sharper angular criteria of Marchal--Yoshida--Sun
([Part I](https://doi.org/10.1007/BF01230502),
[Part II](https://doi.org/10.1007/BF01235792)) require care: Part I says that a
key prolate-ellipsoid containment inequality was checked numerically. We do
not import that unproved numerical check.
