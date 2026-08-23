# Exact Hill barrier for the tight heavy pair

The finite-mass triple-endpoint exchange controls a signed transverse
coefficient, but energy alone gives a stronger and completely uniform answer
to a narrower question: no full brake can lie inside the near-triple tube.
This observation does not control what happens after the heavy pair has
re-expanded almost to its initial separation.

## Exact necessary separation at a brake

Use normalized Pythagorean masses

\[
 (m_1,m_2,m_3)=(A,B,1),
 \qquad A^2+B^2=1,
\]

with $B$ the skinny leg.  The heavy pair consists of masses $A$ and $1$;
its initial separation is the opposite side $B$.  Write its physical Jacobi
separation, without a mass-weighting square root, as

\[
 X=B R.
\tag{1}
\]

The two Jacobi reduced masses are $A/(A+1)$ and
$B(A+1)/(A+B+1)$, but neither enters the pair potential or the zero-kinetic
energy argument below.

The conserved energy is $H=-U_0$, where

\[
 U_0=AB+{1\over AB}.
\tag{2}
\]

At a full labelled brake all Jacobi velocities vanish. Since the conserved
total momentum is zero, no residual common translational velocity remains;
the kinetic energy is zero and necessarily

\[
 U(q)=U_0.
\tag{3}
\]

The heavy-pair term alone gives

\[
 U(q)\ge {A\over|X|}={A\over B|R|}.
\tag{4}
\]

Combining (2)--(4) proves the exact necessary condition

\[
 \boxed{
 |R|>R_{\rm H}(B)
 :={A\over BU_0}
 ={A^2\over1+A^2B^2}
 ={1-B^2\over1+B^2-B^4}.}
\tag{5}
\]

Equivalently,

\[
 1-R_{\rm H}(B)
 ={B^2(2-B^2)\over1+B^2-B^4}
 =2B^2+O(B^4).
\tag{6}
\]

Thus a skinny brake is possible only after the heavy pair has recovered its
initial scaled separation to within $O(B^2)$, or has expanded beyond it.

**Theorem (tight-pair Hill barrier).**  On every collision-free classical
Pythagorean--Burrau trajectory, a full labelled brake is impossible at every
time for which

\[
 |R|\le R_{\rm H}(B).
\tag{7}
\]

The inequality is strict because the two light-heavy potential terms are
positive at every finite collision-free configuration.

**Proof.**  If a brake existed under (7), the heavy-pair term would be at
least $U_0$ and the other two pair terms would be strictly positive. Thus
$U(q)>U_0$, contradicting (3).  No regularization or limiting argument is
used. \(\square\)

## Consequence for every near-triple scaling

Suppose $B_j\to0$ and a sequence of states lies in any absolute late-scaled
near-triple tube

\[
 |R_j|\le r_j,\qquad r_j\longrightarrow0.
\tag{8}
\]

Since $R_{\rm H}(B_j)\to1$, (7) excludes a full brake at every such state for
all sufficiently large $j$.  In particular this covers:

* the wedge regime of `FINITE_B_TRIPLE_ENDPOINT.md`;
* its complementary joint boundary layer, whenever the actual orbit is still
  inside the near-triple tube;
* arbitrarily close but collision-free heavy-binary passages.

This removes the possibility of a brake *during* a finite-mass near-triple
passage without needing transverse asymptotics.  It does not make the coupled
exchange theorem redundant: that theorem transfers the sign and scale of the
outgoing transverse state, data needed to study later motion.  Nor does (7)
exclude a later brake after the heavy pair has re-expanded to
$|R|>R_{\rm H}(B)$.

## Scope and evidence

The result is label-sensitive only through the identification of the initial
tight pair. It is invariant under the simultaneous mass--length scaling used
to reduce to primitive triples. A near-collision is not called a collision;
the proof applies at every smooth state with positive mutual separations.

Equations (2), (5), and (6) are **EXACT SYMBOLIC IDENTITY**.  The barrier
theorem is **PROVED ANALYTICALLY** from energy conservation and positivity of
the other two pair potentials.
