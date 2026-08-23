# An explicit positive-density Pythagorean subfamily

The open-window theorem in `INCOMING_TAIL.md` proves more than the existence
of unspecified rational parameters.  Its exact phase clock can be sampled on
one elementary primitive family and then combined with equidistribution.

## Exact family and clock

For every integer $n\ge1$, take Euclid data $(r,s)=(2n,1)$.  This gives
\[
(a_n,b_n,c_n)=(4n^2-1,4n,4n^2+1),\qquad u_n={1\over2n}.
\tag{1}
\]
The triple is primitive: any common divisor of $4n$ and $4n^2-1$ divides
$1$, and the first and third entries are odd.  Direct expansion gives the
Pythagorean identity.  On normalization,
\[
A_n={4n^2-1\over4n^2+1},\qquad
B_n={4n\over4n^2+1}.
\tag{2}
\]

Put $F(n)=\Phi_{\rm ref}(B_n)/(2\pi)$.  Substitution in the exact reference
clock gives, on the positive real branch,
\[
F(x)={
(2x-1)^{3/2}(2x+1)(4x^2+1)^{3/4}
\over32x^{5/2}},\qquad x>{1\over2}.
\tag{3}
\]
The exact identity is also checked branch-independently by raising both sides
to the fourth power.  Expansion of this algebraic function at infinity gives
\[
F(x)={1\over2}x^{3/2}-{1\over8}x^{1/2}
-{3\over64}x^{-1/2}+{1\over256}x^{-3/2}
+O(x^{-5/2}),
\tag{4}
\]
and hence
\[
F''(x)={3\over8}x^{-1/2}+{1\over32}x^{-3/2}
+O(x^{-5/2}).
\tag{5}
\]
Because (3), after removal of $x^{3/2}$, is analytic in $x^{-1}$ near zero,
the differentiated remainder in (5) is justified rather than merely formal.

## Equidistribution

**Theorem 1.** The sequence $F(n)$ is equidistributed modulo $1$.

**Proof.** Fix a nonzero integer $h$.  On every sufficiently large dyadic
interval $[N,2N]$, (5) gives
\[
c|h|N^{-1/2}\le |(hF)''(x)|\le C|h|N^{-1/2}.
\]
The van der Corput second-derivative estimate therefore yields
\[
\left|\sum_{N<n\le2N}e^{2\pi i hF(n)}\right|
\le C_hN^{3/4}.
\tag{6}
\]
Dyadic summation makes the complete exponential sum $o(X)$.  Weyl's
criterion proves the claim. $\square$

More precisely, the same estimate gives
\[
|S_h(X)|\ll |h|^{1/2}X^{3/4}+|h|^{-1/2}X^{1/4}+O(1).
\]
Erdos--Turan therefore gives
$D_X\ll H^{-1}+X^{-1/4}H^{1/2}+X^{-3/4}$; taking
$H=\lfloor X^{1/6}\rfloor$ yields discrepancy $O(X^{-1/6})$.  The
qualitative equidistribution theorem is all that is needed below.

## Dynamical consequence

Let $J\Subset J^\infty_{\rm esc}$ be any nonempty compact intercept arc
strictly inside a proved restricted hyperbolic-escape window.  Theorem 1 gives
\[
{1\over X}\#\{n\le X:
\Phi_{\rm ref}(B_n)\bmod2\pi\in J\}
\longrightarrow {|J|\over2\pi}.
\tag{7}
\]
The uniform incoming-tail and terminal-transfer theorems apply to every
sufficiently large member counted in (7).  It either suffers an earlier
classical collision, which already excludes a classical period, or enters the
terminal escape-or-collision region.  Thus:

**Corollary 2.** The explicit primitive quadratic family (1) contains a set
of proved nonperiodic members with lower natural density at least
$|J|/(2\pi)>0$.

This is an exact arithmetic strengthening of the Level-D theorem.  It does
not identify the first certified value of $n$: the present restricted escape
arc and the finite-$B$ matching threshold are existential, not effective.

There are also infinitely many self-contained quartic versions.  For a fixed
nonsquare integer $d\ge2$, put $n=dm^2$.  Then
\[
F(dm^2)={d^{3/2}\over2}m^3-{\sqrt d\over8}m+O_d(m^{-1}).
\tag{8}
\]
The polynomial part has an irrational nonconstant coefficient, so the
polynomial Weyl theorem, together with stability under an $o(1)$ perturbation,
again proves equidistribution.  Hence every family
\[
(4d^2m^4-1,4dm^2,4d^2m^4+1)
\]
has the same positive-density conclusion.

Finally, equidistribution also puts positive density of the exact reference
phases into every compact window on the finite-turn side.  Therefore a
positive density lies outside the present first-pass escape certificate and
requires analysis after the first turn.  This does not show that those
trajectories remain captured or are candidates for periodicity.

## A fixed-resonance shrinking target

The quantitative discrepancy estimate gives a limited shrinking-target
statement.  It applies to one fixed restricted resonance; it is not uniform
along the resonance sequence accumulating at the parabolic phase.

Fix a restricted first-turn resonance and let
$\chi_{\rm res}\in\mathbb R/(2\pi\mathbb Z)$ be its incoming asymptotic
intercept.  Thus the restricted incoming parabolic orbit labelled by
$\chi_{\rm res}$ reaches a finite first outer turn at which both the outer
particle and the collision-regularized heavy binary have zero velocity.

**Theorem 3 (dyadic approximation to a fixed resonance).**  There is a
constant $C_{\rm res}>0$ such that, for every sufficiently large $N$, some
integer $n$ with
\[
N<n\leq2N
\]
satisfies
\[
\operatorname{dist}_{S^1}
 \bigl(\Phi_{\rm ref}(B_n),\chi_{\rm res}\bigr)
 \leq C_{\rm res}N^{-1/6}
 \leq C'_{\rm res}B_n^{1/6}.
\tag{9}
\]
Consequently there is an infinite sequence of distinct primitive triples
from (1) whose exact reference phases converge to this fixed restricted
resonance intercept.

**Proof.**  Apply the exponential-sum estimate used above directly to the
$N$ points $F(n)$ with $N<n\leq2N$.  Erdos--Turan gives discrepancy
$O(N^{-1/6})$ on this dyadic block, uniformly over circular intervals.  An
interval centered at $\chi_{\rm res}/(2\pi)$ whose length is a sufficiently
large constant times $N^{-1/6}$ must therefore contain at least one of these
points.  Multiplication by $2\pi$ proves the first inequality.  On this block
$B_n=4n/(4n^2+1)\asymp N^{-1}$, which proves the second.  Taking successive
dyadic blocks gives distinct indices tending to infinity. $\square$

There is also a precise, but only qualitative, dynamical consequence.  Along
any sequence supplied by Theorem 3, the incoming-tail theorem gives the
following alternative:

1. a classical collision occurs before the relevant finite-time comparison,
   already excluding a classical periodic orbit; or
2. on the collision-free subsequence, the full scaled state on the fixed
   incoming section converges in the common LC chart to the restricted state
   labelled by $\chi_{\rm res}$.

In the second case, regularized continuous dependence propagates this
convergence over the fixed finite interval ending at the chosen restricted
first turn.  Transversality of that turn, $z''<0$, gives nearby outer-turn
sections, and the full **scaled** Jacobi velocity residual there tends to
zero.  This is a near-brake statement only.  It neither proves that a
finite-$B_n$ velocity residual vanishes nor produces a counterexample.
Indeed, in the late scaling
\[
X=B R,\qquad Y=B Z,\qquad
t=t_{\rm mono}+B^{3/2}\theta,
\]
the physical relative velocities are
\[
\dot X=B^{-1/2}R',\qquad \dot Y=B^{-1/2}Z'.
\tag{10}
\]
Thus an $o(1)$ scaled residual need not even tend to zero in physical units,
and it is never an exact brake without an additional finite-$B$ splitting
argument.  The current matching theorem also supplies only $o(1)$ fixed-
section convergence, not an $O(B^{1/6})$ state or velocity estimate.

The exponent in (9) marks the present arithmetic limit.  A phase target of
radius $B_n^\gamma\asymp n^{-\gamma}$ is forced by the proved discrepancy on
every large dyadic block only for $\gamma<1/6$ (and at $\gamma=1/6$ only with
a sufficiently large constant).  Equidistribution alone gives no hit for an
$O(B_n)$ resonance neighborhood and no exact equality with
$\chi_{\rm res}$.  Such conclusions require a stronger inhomogeneous
shrinking-target theorem as well as quantitative full-state matching and a
finite-$B$ vector-residual splitting calculation.

Status of the exact clock and equidistribution theorem: **PROVED
ANALYTICALLY**. Status of the nonperiodicity corollaries: **PROVED BY
COMPUTER-ASSISTED ARGUMENT**, because the existence of the restricted escape
arc uses the validated transversality sign.  Conditional on one fixed
restricted resonance intercept, the shrinking-target estimate and its
collision/LC-convergence alternative are **PROVED ANALYTICALLY**; the
unconditional existence of such resonances imports the same validated
transversality input.  The exact identities have symbolic regression tests in
`tests/test_explicit_skinny_family.py`.
