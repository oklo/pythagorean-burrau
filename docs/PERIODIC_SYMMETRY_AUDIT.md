# Reflection shooting and rank-loss audit

Evidence scope: the identities and local dimension statements below are
**PROVED ANALYTICALLY**. This note establishes no periodic candidate, no
nonexistence theorem for the tied family, and no arithmetic conclusion. Its
conventions are those of `CONJECTURE.md` and `FABLE_EVENT_REDUCTION.md`.

## Exact reflection conditions

Fix positive labelled masses, remove center-of-mass position and velocity,
and use the unweighted Jacobi vectors

\[
X=q_2-q_1,\qquad Y=q_3-(m_1q_1+m_2q_2)/(m_1+m_2),
\]

with reduced masses \(\mu_1=m_1m_2/(m_1+m_2)\) and
\(\mu_2=m_3(m_1+m_2)/(m_1+m_2+m_3)\). Every classical state has
\(X\ne0\). Put \(e=X/r\), \(r=|X|>0\), \(n=Je\), and write the
**inertial** relative velocities in this instantaneous frame:

\[
Y=ae+bn,\quad \dot X=ve+wn,\quad \dot Y=ce+dn.
\]

In particular \(c\) is not generally \(\dot a\), because the frame moves.
The reflection in the line spanned by \(e\) is denoted \(R\). The
reversing involution \(K_R(q,\dot q)=(Rq,-R\dot q)\) fixes the state
exactly when

\[
\boxed{b=0,\qquad v=0,\qquad c=0.}
\]

An equivalent rotation-invariant residual is

\[
(X\times Y,\ X\cdot\dot X,\ X\cdot\dot Y)=0.
\]

These conditions remain complete when \(Y=0\). The axis passes through
the stationary center of mass; allowing an affine reflection axis creates
no additional freedom after translation reduction.

Angular momentum is

\[
L=\mu_1rw+\mu_2(ad-bc).
\]

Thus at syzygy \(b=0\), zero angular momentum restricts the **normal**
velocities, \(\mu_1rw+\mu_2ad=0\). It does not eliminate either
longitudinal condition \(v=0\) or \(c=0\).

## Codimension, including energy

The center-of-mass phase space has dimension eight. The regular level
\(L=0\) has dimension seven, and quotienting common rotations gives
dimension six. Coordinates on this quotient are
\((r,a,b,v,c,d)\): solve the preceding angular-momentum equation for
\(w\), whose coefficient \(\mu_1r\) never vanishes. In these coordinates
the moving-axis fixed-set union is simply \(b=v=c=0\). Its dimension is
three and its codimension is **exactly three**, independently of the
positive masses and including \(a=0\).

Before rotation reduction, the union over reflection axes has dimension
four in the seven-dimensional \(L=0\) manifold. A specified fixed axis
has dimension three there, hence codimension four. Confusing the fixed-axis
count with the moving-axis count incorrectly adds or removes an equation.

Fixing negative energy reduces both the reduced ambient space and this
fixed-set union by one dimension, preserving codimension three. To verify
regularity on the fixed set, scale positions by \(\lambda\) and normal
velocities by \(\lambda^{-1}\). This preserves the reflection conditions
and \(L=0\); energy becomes
\(H(\lambda)=K\lambda^{-2}-U\lambda^{-1}\). If a nonzero velocity is
present, varying its common amplitude provides another energy direction.
If all velocities vanish, position scaling alone has derivative \(U>0\).
Consequently energy has nonzero differential on the fixed set everywhere.

For normalized free-fall shooting with fixed masses, there are two initial
shape variables and one encounter time, hence three unknowns for these
three equations. Allowing two mass ratios gives five unknowns. Two side
ties then generically leave isolated roots. Imposing the tied-right curve
from the start leaves only \((u,t)\), still with three reflection equations.
Reflection alone therefore supplies no missing degree of freedom.

The equality \(m_1^2+m_2^2=m_3^2\) does not alter any rank in this
calculation. Initial mass-side matching is a restriction on launch data,
not an endpoint conservation law. The calculation rules out a redundancy
deduced solely from positive Pythagorean masses, momentum, angular momentum,
and energy. It does **not** rule out an additional identity along the actual
tied launch family or a special itinerary; such an identity would require
a separate proof.

## What reflection shooting actually constructs

Suppose the trajectory starts at a noncollinear brake at time zero, stays
classical and collision-free through time \(t_* >0\), and reaches
\(\operatorname{Fix}(K_R)\). Uniqueness gives

\[
q(t_*+s)=R q(t_*-s),\qquad 0\le s\le t_*.
\]

Thus \(q(2t_*)=Rq(0)\) and \(\dot q(2t_*)=0\). Time reversal about
this second brake gives a strict labelled period \(4t_*\). It need not
be minimal. Reflection preserves all separations, so the full constructed
period is collision-free whenever the initial segment is. No label
permutation is used.

A practical two-equation event formulation follows. At syzygy define

\[
\mathcal J=av-rc.
\]

There,

\[
\dot I/2=\mu_1rv+\mu_2ac,\qquad
\det\begin{pmatrix}\mu_1r&\mu_2a\\a&-r\end{pmatrix}
=-(\mu_1r^2+\mu_2a^2)=-I<0.
\]

Therefore the two residuals \((\dot I,\mathcal J)\) vanish on a syzygy
section exactly at reflection-brake encounters. Unlike a splitting that
divides by \(Y\), this formulation is valid for \(a=0\).

Every such encounter reached from a noncollinear launch is a transverse
syzygy. Indeed at the reflection fixed set,

\[
\frac{d}{dt}(X\times Y)=rd-aw
=\frac{I}{\mu_1r}d.
\]

If this vanished, \(d=w=0\), so all velocities would vanish at a
collinear configuration. The collinear phase subspace is invariant under
Newton's equations; uniqueness backwards would force the initial triangle
to be collinear, a contradiction. Thus the syzygy event time is locally a
regular implicit function near every sought reflection root.

Reflection-brake encounters also satisfy \(\dot I=0\), but have
\(K>0\) and need not be maxima of \(I\). The maximum-only theorem in
`FABLE_EVENT_REDUCTION.md` concerns actual brakes. A construction search
that checks only maxima can miss a reflection encounter at a minimum.
Searching transverse syzygies with residual \((\dot I,\mathcal J)\)
avoids that exclusion and retains two genuine equations for the single
tied-right launch parameter. It is a better section, not a square reduction.

## Other elementary reversing symmetries

For distinct labelled masses, a body permutation is unavailable as a
symmetry of the fixed Newton equations. In center-of-mass coordinates, a
spatial orthogonal map \(Q\) composed with velocity reversal has square
\((q,v)\mapsto(Q^2q,Q^2v)\). The orthogonal involutions of the plane are
identity, reflections, and \(-I\). Identity gives the ordinary brake
set. The \(-I\) reversing fixed set requires every position to be zero,
which is triple collision. Any other nonidentity rotation likewise has no
nonzero fixed position. Consequently these spatial reversors introduce
no additional collision-free fixed-set mechanism beyond brakes and
reflections.

An established relative return \(\Phi_T z=Qz\) with \(Q^N=I\) does
yield a strict labelled return after \(NT\), by equivariance and
iteration. A time shift by itself does not establish that matching
condition, and an arbitrary measured rotation angle does not prove finite
order. More general itinerary constructions are not excluded by this
elementary classification.

## Rank four is not a branch-existence theorem

Let \(F=(\mathcal B,S_1,S_2):\mathbb R^5\to\mathbb R^5\) be the
analytic shooting map in a collision-free neighborhood after all scale,
rotation, and phase conventions have been fixed. Suppose
\(F(z_*)=0\) and \(\operatorname{rank}DF(z_*)=4\). Choose a kernel
vector \(n\) and a cokernel vector \(\ell\). Lyapunov--Schmidt reduction
solves four equations for a transverse variable \(w=w(s)\), leaving

\[
g(s)=\ell^T F(z_*+sn+w(s))=0,\qquad g(0)=g'(0)=0.
\]

The zero may still be isolated: \(F(z)=(z_1,z_2,z_3,z_4,z_5^2)\) is
an explicit analytic example. More generally, if the first nonzero Taylor
coefficient of \(g\) has any finite order, zero is isolated locally. A
nontrivial local zero curve requires \(g\equiv0\), by analyticity.
Constant rank four in a neighborhood is one sufficient hypothesis, but
rank four at the root alone is not.

With \(w'(0)=0\) in the usual transverse parametrization, the first
obstruction is

\[
g''(0)=\ell^T D^2F(z_*)[n,n].
\]

A rigorously nonzero value excludes a local tied branch even though the
Jacobian is singular. Vanishing of this coefficient only moves the
obligation to higher order. External-parameter continuation of
\(F(z,\lambda)=0\) can produce folds or bifurcations without providing
any continuum on the exact \(\lambda=1\) side-tied slice.

Conversely, every smooth nonconstant zero curve has a singular Jacobian at
its regular points; full-rank tied roots are locally isolated. Small
singular values are useful diagnostics but depend on units and residual
scaling and do not certify exact rank loss. A defect sign change becomes
an intermediate-value argument only after a connected collision-free
zero curve has actually been established. Distinct isolated roots with
opposite signs do not suffice. Even a proved real tied-right root leaves
the exact rational Euclid-parameter obligation open.

## Full-loop words versus the syzygy itinerary

Under the standard convention that uppercase letters are inverses of their
lowercase partners, all four strings in the construction handoff freely
reduce to the empty word:

| Seed | Supplied string | Free reduction |
|---|---|---|
| F1 | `BaAb` | identity |
| F2 | `AbAaBa` | identity |
| F5 | `BabbBBAb` | identity |
| F30 | `AbAbBaBAbABaAbaBabAbBaBa` | identity |

The reductions follow by repeatedly deleting adjacent inverse pairs. This
is an **EXACT SYMBOLIC IDENTITY** conditional on that inverse convention;
the original catalog's coding definition has not been audited here.

There is also an unconditional geometric fact about the actual orbits. If
\(\gamma:[0,\tau]\to\mathcal Q\) is a collision-free labelled path
between two brakes, its constructed full loop is \(\gamma\) followed by
\(\gamma^{-1}\). It is nullhomotopic already in labelled configuration
space \(\mathcal Q\), and therefore in any continuous shape quotient.
An explicit contraction, with \(0\le t\le2\tau\), is

\[
H(s,t)=\gamma((1-s)\min\{t,2\tau-t\}),\qquad 0\le s\le1.
\]

Its image stays on the original collision-free arc. Thus differing raw
full-orbit strings do not establish different free-group classes or a
topological obstruction to connectedness. A half-orbit invariant with
specified endpoint or closure conventions would require a separate
definition and argument.

However, the **labelled syzygy itinerary** supplies a distinct dynamical
obstruction in this problem. In fact every syzygy of a zero-angular-momentum
trajectory launched noncollinearly is transverse, without imposing either
longitudinal reflection condition. At \(b=0\),

\[
L=\mu_1rw+\mu_2ad=0,\qquad
\frac{d}{dt}(X\times Y)=rd-aw.
\]

If the second expression were zero, the nonsingular two-equation system
would give \(w=d=0\). Positions and velocities would all lie on the same
line. Invariance of the collinear phase subspace and classical uniqueness
would then contradict the noncollinear launch. The same uniqueness argument
shows that every brake of such an orbit is noncollinear.

Consequently, on any compact classical segment between two brakes, there
are finitely many syzygies, all transverse, with no endpoint syzygy. Their
ordered middle-body labels are locally constant in a continuous family of
such segments with continuously varying finite brake time and positive
masses. To see this, simple zeros persist individually; compactness gives
a nonzero area margin outside their neighborhoods; and a change of the
middle body at a syzygy would require collision. Thus the itinerary is
constant on each connected family within this domain. It can change only
on leaving these hypotheses, for example through collision or an unbounded
time limit. These statements are **PROVED ANALYTICALLY**; they do not rely
on interpreting the catalog words.

The current ordinary shooting observations, supplied by the construction
run, are:

| Candidate | Reported half-orbit syzygy sequence | Count |
|---|---|---:|
| F1 | `3213213` | 7 |
| F2 | `321321313` | 9 |
| F5 | `32132131313` | 11 |
| F30 | `321323123132312313231321323123` | 30 |
| F3 | `323213213` | 9 |
| F4 | `32321321313` | 11 |

These particular counts and labels are **ORDINARY NUMERICAL EVIDENCE**,
not independently certified in this note. If established for exact
candidate roots, differing sequences would exclude membership in one
connected family of the finite collision-free brake segments just
described. In particular, correcting the full-loop free-group argument
does not make the opposite-defect candidates a connected branch or an
intermediate-value bracket. It identifies the precise dynamical invariant
that would have to replace the invalid distinction between freely trivial
full-loop words.
