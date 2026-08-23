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

Status of the exact clock and equidistribution theorem: **PROVED
ANALYTICALLY**. Status of the nonperiodicity corollaries: **PROVED BY
COMPUTER-ASSISTED ARGUMENT**, because the existence of the restricted escape
arc uses the validated transversality sign. The exact identities have symbolic
regression tests in `tests/test_explicit_skinny_family.py`.
