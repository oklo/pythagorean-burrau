# Correction to the forced-lag sign-change argument

Reviewed 2026-09-05. The exact forced-lag identities remain valid. The
previously claimed implication from one sign change of the forcing and
`w(terminal) = 0` to interior positivity is **not established**. Its scalar
proof is invalid without an additional terminal bound.

## Two singular endpoints

Write `a = lambda + c`, so `w_s + a w = q`. In the ordered noncollinear
arc, `lambda,c > 0`. At launch, `W` has a simple zero and `lambda ~ 1/s`.
Consequently `exp(integral_0^s a)` is not a finite integrating factor.
Choose a fixed interior reference time `s0 > 0` instead:

\[
 M(s)=\exp\left(\int_{s_0}^s a(\xi)\,d\xi\right),\qquad (Mw)_s=Mq.
\]

At the first transverse ordered syzygy `s=S`, the normalized area
`delta` tends to zero. The coefficient `c=k W Acal/delta` can diverge.
This is a real issue for these formulas, not merely an arbitrary ODE
possibility: on the collinear face `x=1-y`, the threshold polynomial is

\[
 B=4y^2(n+y)(y-1)(y^2-y+2),
\]

which is nonzero for `0<y<1` and positive mass `n`. Thus `Acal` has a
finite positive nonzero limit there. With nonzero terminal pair angular
momentum and transverse area crossing, `c` has the order `1/(S-s)`.
The geometric identity `w(S)=0` does **not** imply `lim M(s)w(s)=0`.

## An exact counterexample to the scalar inference

For `0<s<1`, put

\[
 a(s)=\frac1s+\frac1{1-s},\quad
 w(s)=(1-s)(1+s-3s^2),\quad
 q(s)=(1-s)\left(\frac1s+2-9s\right).
\]

Then `w_s+a w=q` exactly, `w(0)=1`, and `w(1)=0`. The forcing is positive
before `(1+sqrt(10))/9` and negative afterward. Nevertheless `w` is
negative after `(1+sqrt(13))/6`. Up to a positive constant,
`M=s/(1-s)`, so `lim Mw=-1`.

This counterexample has the same types of singularity at both endpoints.
It disproves the unqualified scalar inference used in the old proof. It
is **not** a constructed Newtonian trajectory and does not disprove the
Pythagorean conjecture or the possible dynamical one-switch statement.

## A correct sufficient lemma

Suppose `w>0` near launch, `q>0` before one interior switch and `q<0`
afterward, and

\[
 \liminf_{s\uparrow S}M(s)w(s)\ge0.
\]

Then `w>0` in the interior: `Mw` starts positive, increases and then
strictly decreases toward a nonnegative limit. This additional endpoint
hypothesis is not proved for the whole tied family. A global approach must
establish it, replace it with another sufficient terminal estimate, or
supply a different argument.

The Volterra representation for `e` remains valid as an improper integral:
the kernel integrates from each positive `tau` to an interior `s`, and
the launch homogeneous contribution tends to zero. The exact symbolic
identities, static ambient witnesses, and separate near-isosceles
factorization/collision/escape arguments do not depend on the invalid
terminal inference. They are not withdrawn by this correction.

## Affected records

This correction supersedes the original one-switch lemma in
`EXACT_REDUCTIONS.md` and the conditional theorem in the
[archived August handoff](../archive/history/campaigns/STOPPING_POINT_HANDOFF_2026-08-26.md).
On September 6 the active reduction, ledger, obligations, status, and memory
were reconciled with the corrected lemma; superseded summaries remain only
as explicitly historical records. The current main paper and
technical companion contain the corrected statement and scalar example.
The old paper is retained only under `paper/archive/` as a historical copy.
