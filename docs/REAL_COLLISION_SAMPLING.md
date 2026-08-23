# Infinitely many real tied collision parameters near the skinny endpoint

The differentiated collision graph can be combined with the exact rapidly
winding skinny clock.  The resulting theorem is about the full real
Pythagorean mass--shape curve, not merely the massless projective limit.
It produces classical collision parameters, and hence nonperiodic real
members.  It does not prove that any collision parameter has rational Euclid
parameter.

## Local endpoint coordinates

Let \(\Gamma^-(\chi)\) be the collision-regularized restricted incoming
parabolic curve in the asymptotic-intercept coordinate of
`INCOMING_TAIL.md`.  Let \(\chi_*\) label the certified transverse
intersection of this curve with the restricted collision-stable curve.
On a fixed saddle-entrance section, use the signed nonlinear longitudinal
unstable amplitude

\[
 H_0(\chi).
\tag{1}
\]

The transversality theorem says that the two curves genuinely cross.  The
asymptotic intercept is a one-to-one local parameter of the parabolic curve
(possibly only a Hölder phase chart at a regularized binary-collision phase).
Consequently there are compact intercept arcs \(J_-\) and \(J_+\), lying on
opposite sides of \(\chi_*\), and a number \(h_*>0\) such that, after fixing
the orientation of \(H\),

\[
 H_0\le-2h_*\quad\hbox{on }J_- ,\qquad
 H_0\ge 2h_*\quad\hbox{on }J_+ .
\tag{2}
\]

Choose one lifted compact intercept interval \(J\) containing
\(J_-\), \(\chi_*\), and \(J_+\), small enough that the limiting flow from
the incoming section to the saddle entrance uses one common regularized
chart chain and

\[
 H_0^{-1}(0)\cap J=\{\chi_*\}.
\tag{2a}
\]

No assertion that \(\chi\) is a differentiable coordinate at
every LC phase is needed below; only the local ordering and continuity of the
embedded parabolic curve are used.

For a positive-mass tied state which reaches the saddle entrance before a
classical collision, let

\[
 H_B,\quad T_B,\quad S_B,\quad \Xi_B
\tag{3}
\]

be the normalized data of `DIFFERENTIATED_JOINT_INCLINATION.md`.  They depend
continuously on \(B>0\) on every collision-free component of the common
section chain.  This follows from analytic ordinary and LC flow and
transversality of the fixed sections.  A true positive-mass collision ends
the classical branch and is retained as a theorem alternative, not crossed
physically.

## Phase-cycle brackets

The exact reference intercept satisfies

\[
 \Phi_{\rm ref}'(B)
 =-{3\pi\over2}B^{-5/2}(1+o(1)).
\tag{4}
\]

It is therefore strictly decreasing for small \(B\).  For every sufficiently
large winding index \(n\), choose a closed interval

\[
 I_n=[B_n^-,B_n^+],\qquad \sup I_n\longrightarrow0,
\tag{5}
\]

on which one lift of \(\Phi_{\rm ref}\) crosses \(J\), with its endpoint
values in the interiors of \(J_-\) and \(J_+\).  The intervals can be chosen
pairwise disjoint.  Their relative widths tend to zero because
\(|I_n|=O(B_n^{5/2})=o(B_n)\).

The incoming-tail theorem gives, uniformly on these intervals, the following
dichotomy: either a tied state has already suffered a classical collision, or
its state on the fixed incoming section is \(o(1)\) from
\(\Gamma^-(\Phi_{\rm ref}(B))\).  Compact regularized flow to the saddle
entrance preserves this uniform state convergence.  Hence, if no parameter
in \(I_n\) has an earlier collision, the endpoint signs in (2) transfer to

\[
 H_{B_n^-}<-h_*,\qquad H_{B_n^+}>h_*
\tag{6}
\]

after exchanging the endpoint labels if required by the decreasing clock.

## Collision-sampling theorem

**Theorem.** There are infinitely many distinct real normalized
Pythagorean--Burrau parameters \(B_n\downarrow0\) whose classical solution
has a binary or triple collision in finite time.  More precisely, for every
sufficiently large phase-cycle bracket \(I_n\), at least one of the following
holds:

1. some \(B\in I_n\) has a classical collision before the selected late
   collision chart, including during the passage from the fixed incoming
   section to the saddle entrance; or
2. some \(B\in I_n\) satisfies
   \[
    \kappa_B=\kappa_c(B,T_B,S_B,\Xi_B),
    \qquad \kappa_B={H_B\over|T_B|^{\mu/\tau}},
   \tag{7}
   \]
   and therefore has the selected light--heavy collision certified by the
   normalized collision graph.

Every such real member is nonperiodic in the classical collision-free sense.

**Proof.** Fix a sufficiently large \(n\).  If an earlier collision occurs
for any parameter of \(I_n\), item 1 holds.  Suppose instead that the entire
common incoming and saddle-entrance chain is collision-free.  The data (3)
are then continuous in \(B\), and (6) holds.

Let

\[
 p={\mu\over\tau}\in(1,2).
\tag{8}
\]

Continuity gives a point \(b_n^0\in I_n\) with \(H_{b_n^0}=0\).  On the
positive-\(H\) side choose

\[
 h_n=B_n^{p/2},
\tag{9}
\]

where \(B_n\) is any point of \(I_n\).  Since the relative width of \(I_n\)
tends to zero, replacing \(B_n\) by any other point of the same interval
changes (9) by a factor tending to one.  For large \(n\), \(h_n<h_*\), so
there is a first point \(b_n^1\) after a last zero \(b_n^0\), in the chosen
orientation, such that

\[
 H_{b_n^1}=h_n,\qquad 0<H_B<h_n
 \quad(b_n^0<B<b_n^1).
\tag{10}
\]

The interval orientation is immaterial.

Every sequence chosen from \([b_n^0,b_n^1]\) has \(H_B\to0\).  Uniform
incoming-tail convergence and the local uniqueness of the transverse
intersection therefore force its limiting restricted state to be the
certified endpoint.  The parity-amplitude and joint blow-up theorems then
give, uniformly on this shrinking segment,

\[
 {T_B\over B}\longrightarrow\Theta_*\ne0,qquad
 B|\log|T_B||\longrightarrow0,qquad
 \|\widehat\Xi_B\|\longrightarrow0,
\tag{11}
\]

while \(S_B\) remains in the fixed compact saddle subbox.  The sequential
form of (11) is uniform: otherwise a violating choice of one point from each
segment would contradict the same endpoint theorem.

Thus the normalized collision graph is defined throughout
\([b_n^0,b_n^1]\) for all large \(n\).  Put

\[
 G_n(B)=H_B-
 |T_B|^p\kappa_c(B,T_B,S_B,\Xi_B).
\tag{12}
\]

The graph and the tied entrance data are continuous, and its limiting value
\(\kappa_c\) is strictly positive.  At the zero endpoint,

\[
 G_n(b_n^0)=-|T_{b_n^0}|^p
 \kappa_c(b_n^0,T_{b_n^0},S_{b_n^0},\Xi_{b_n^0})<0.
\tag{13}
\]

On the other endpoint, (9)--(11) and boundedness of the collision graph give

\[
 G_n(b_n^1)=B_n^{p/2}-O(B_n^p)>0.
\tag{14}
\]

The intermediate-value theorem supplies \(B_n^c\in(b_n^0,b_n^1)\) with
\(G_n(B_n^c)=0\).  Equation (7) follows because \(T_{B_n^c}\ne0\).
The normalized collision-graph theorem then gives an exact zero of the
selected LC position.  For positive light mass this is a true classical
light--heavy collision and terminates the solution.  Since the brackets
\(I_n\) are disjoint and tend to zero, the resulting collision parameters
are distinct and accumulate only at the skinny endpoint. \(\square\)

## Coordinate and arithmetic scope

For an oriented rescaling of the asymptotic eigenvectors,
\(H'=\alpha H\), \(T'=\beta T\) with \(\alpha,\beta>0\), both the tied
coordinate and collision graph are multiplied by
\(\alpha\beta^{-p}\).  Thus the zero equation (7) and the sign change in
(12) are invariant.  General admissible oriented \(C^1\) amplitude changes
preserve the same local zero set.  The numerical value of \(\kappa\) is not
coordinate-free.

The theorem is real, not arithmetic.  Every rational Euclid parameter gives
a rational \(B=2u/(1+u^2)\), but the intermediate-value roots above are
isolated and need not be rational.  Rational density cannot be applied to
them.  No new rational collision or second-brake candidate is claimed.

**Status:** the collision-sampling theorem is **PROVED BY COMPUTER-ASSISTED
ARGUMENT** because it uses the certified transverse restricted endpoint and
the certified base collision root.  Its phase winding, continuity,
intermediate-value step, and finite-mass transfer are **PROVED ANALYTICALLY**.
The assertion that any sampled collision parameter is rational is
**CONJECTURAL** and receives no support from cardinality.
