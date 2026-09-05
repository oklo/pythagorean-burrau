# Handoff prompt for Astra: engineer a periodic Pythagorean--Burrau triple

You are taking over a sustained, publication-oriented attack on the
Pythagorean--Burrau nonperiodicity conjecture, but with a deliberate change of
emphasis: **try to construct a counterexample by engineering a periodic brake
orbit whose exact masses and initial side lengths are a Pythagorean triple.**

Treat a proof of nonexistence as an acceptable outcome only if the attempted
construction exposes a rigorous structural obstruction.  Do not replace the
counterexample target by a numerical survey or by genericity/cardinality
heuristics.

## 1. Repository and first reads

Work in the persistent git repository

```text
/Users/greglaughlin/Projects/pythagorean-burrau
```

The repository was clean on branch `master` at this handoff.  Inspect it before
changing anything.  Begin by reading, in this order:

```text
docs/CONJECTURE.md
docs/STOPPING_POINT_HANDOFF_2026-08-26.md
docs/STATUS.md
docs/COUNTEREXAMPLE_AUDIT.md
docs/F30_MASS_SIDE_VALIDATION.md
docs/FABLE_EVENT_REDUCTION.md
docs/ENDPOINTS.md
docs/LITERATURE.md
docs/PROOF_LEDGER.md
docs/PROOF_OBLIGATIONS.md
```

Do not silently weaken labelled return, collision freedom, or exact
mass--geometry matching.  Maintain the evidence vocabulary already used in the
repository.

Useful auxiliary work from the immediately preceding session is in

```text
/Users/greglaughlin/Projects/burrau
```

That directory is not the main git repository.  Its relevant artifacts are
listed below.  Port only what you have audited and actually need.

## 2. Exact target

For a positive-integer Pythagorean triple

\[
 a^2+b^2=c^2,
\]

set the labelled masses to

\[
 (m_1,m_2,m_3)=(a,b,c),
\]

and put each mass opposite the side of the same length, with all initial
velocities zero.  In the normalization \(m_3=r_{12}=1\), write

\[
 A(u)=\frac{1-u^2}{1+u^2},\qquad
 B(u)=\frac{2u}{1+u^2},
\]

and

\[
 q_1=(-1/2,0),\quad q_2=(1/2,0),\quad
 q_3=\left(\frac{B^2-A^2}{2},AB\right).
\]

The rational counterexample target is

\[
 u\in\mathbb Q\cap(0,1),\qquad
 \mathcal B(u,\tau)=0
\]

for some \(\tau>0\) on a collision-free classical arc.  Here \(\mathcal B\)
is the three-component rotation-reduced brake residual defined and proved
equivalent to vanishing of all labelled inertial velocities in the repository.
A second brake at \(\tau\) gives a strict labelled period \(2\tau\) by time
reversal.

Because common integer multiples are dynamically redundant, any rational
\(u=p/q\) reduces to a primitive Pythagorean triple.  A real but irrational
root would disprove the strong real conjecture but would **not** disprove the
integer conjecture.

## 3. What is already proved, and what is not

The full rational conjecture is unresolved.  The stronger real conjecture is
unresolved.  No exact real second-brake intersection and no rational candidate
have been established.

Durable results include:

1. exact scaling reduction, Euclid parametrization, leg-swap involution,
   second-brake lemma, and reduced brake coordinates;
2. rigorous nonperiodicity for infinitely many skinny subfamilies;
3. a rigorous one-sided punctured neighborhood of the isosceles-right endpoint;
4. a rigorously certified real interval beginning at \(u=0.29\), plus a wider
   computer-assisted theorem candidate described in `STATUS.md`;
5. exact event reduction: every possible brake is a strict local maximum of
   the moment of inertia and can be checked on analytic maximum branches;
6. an exact general escape criterion that terminates later-brake searches once
   its strict hypotheses hold.

The most obvious equal-mass reflection construction is closed.  The leg-swap
fixed point is

\[
 u=\sqrt2-1,\qquad A=B=1/\sqrt2,
\]

which is irrational.  Its exact tied right-isosceles free-fall trajectory
reaches a finite collision and has no positive second brake.  A whole
one-sided punctured neighborhood is already proved collision-free through the
unfolded encounter and then nonperiodic.  Do not spend the run rediscovering
this endpoint.

Also note the group-theoretic constraint: a nondegenerate primitive
Pythagorean triple has three distinct masses.  A spatial symmetry that
permutes labelled bodies is therefore not a symmetry of its Newton equations.
Time reversal remains universal; spatial reflections that fix each label may
still be used as reversing symmetries at intermediate sections.

## 4. The best existing periodic near miss

The Li--Liao free-fall catalog contains a periodic orbit called \(F_{30}\) on
the mass slice \((0.6,0.8,1)\), close to the exact \(3{:}4{:}5\) Burrau
triangle.  A five-equation shooting solve promoted both mass ratios to
variables and imposed

\[
 \mathcal B=0,\qquad r_{23}=m_1,\qquad r_{31}=m_2.
\]

It converged to the ordinary-numerical, mass--side-tied periodic candidate

\[
 (m_1,m_2,m_3)\approx
 (0.594811646571005,\ 0.801774973317793,\ 1),
\]

with

\[
 (x,y,\tau)\approx
 (0.14452110646,\ 0.47690214001,\ 6.28923382379).
\]

The closest resolved separation is about

\[
 5.0001\times10^{-4}.
\]

The remaining mass Pythagorean defect is

\[
 D=m_1^2+m_2^2-1\approx-0.00335599726474.
\]

Thus it is a highly convincing ordinary-numerical **general Burrau periodic
orbit**, but it is not right and is not a Pythagorean counterexample.  A global
pair--23 Levi--Civita formulation removes the close-passage stiffness.  The
fixed candidate center has been propagated with validated enclosures, but a
full interval-Newton proof of the root remains open because the \(C^1\)
parameter box wraps.  See `F30_MASS_SIDE_VALIDATION.md`.

Reproduction:

```bash
cd /Users/greglaughlin/Projects/pythagorean-burrau
PYTHONPATH=. .venv/bin/python scripts/continue_f30.py \
  --solve-mass-side-global-lc --method DOP853 \
  --rtol 2e-13 --atol 2e-15 --max-step 0.0005 --root-tol 1e-11
```

The latest trajectory image and its reproducer are:

```text
/Users/greglaughlin/Projects/burrau/plots/f30_mass_side_periodic_candidate.png
/Users/greglaughlin/Projects/burrau/scripts/plot_f30_mass_side_periodic_candidate.py
/Users/greglaughlin/Projects/burrau/data/f30_mass_side_periodic_candidate_plot_audit.txt
```

The PNG is a high-time-resolution, physical-time-uniform point-density plot.
It contains no text or bounding box.  It is a visualization, not validation.

## 5. New two-sided defect evidence

The primary Li--Liao catalog is available at

```text
https://numericaltank.sjtu.edu.cn/three-body/free-fall-3b/free-fall-3b-movies.htm
```

The preceding session parsed all 30 catalog orbits on the exact
\((0.6,0.8,1)\) mass slice and attempted the same five-equation mass--side
solve.  Ten direct solves converged.  The raw record is

```text
/Users/greglaughlin/Projects/burrau/data/f30_all_mass_side_continuations.json
```

and its driver is

```text
/Users/greglaughlin/Projects/burrau/scripts/search_f30_mass_side_catalog.py
```

The most important result is that mass--side-tied periodic candidates occur on
**both sides** of the right locus:

| catalog seed | free-group word | \(m_1\) | \(m_2\) | \(\tau\) | \(D=m_1^2+m_2^2-1\) | sampled \(r_{\min}\) |
|---|---|---:|---:|---:|---:|---:|
| \(F_1\) | `BaAb` | 0.536940691118 | 0.839991650112 | 1.33797000897 | -0.006108721964 | 0.00161612 |
| \(F_2\) | `AbAaBa` | 0.485763526679 | 0.878297062331 | 1.41333001453 | +0.007371933551 | 0.00168456 |
| \(F_5\) | `BabbBBAb` | 0.474742618735 | 0.896107794576 | 1.54407624990 | +0.028389733543 | 0.00056098 |
| \(F_{30}\) | `AbAbBaBAbABaAbaBabAbBaBa` | 0.594811646571 | 0.801774973318 | 6.28923382379 | -0.003355997265 | 0.00050001 |

Other converged negative-defect candidates include \(F_{16},F_{18},F_{20},
F_{22},F_{23},F_{24},F_{27}\).  See the JSON for values.

The \(F_5\) value came from a deformation that starts with the catalog's fixed
masses and continuously replaces the two mass constraints by the two
mass--side constraints.  The experimental driver and records are:

```text
/Users/greglaughlin/Projects/burrau/scripts/continue_freefall_mass_side_homotopy.py
/Users/greglaughlin/Projects/burrau/data/homotopy2_f03.json
/Users/greglaughlin/Projects/burrau/data/homotopy2_f04.json
/Users/greglaughlin/Projects/burrau/data/homotopy2_f05.json
/Users/greglaughlin/Projects/burrau/data/homotopy2_f06.json
```

The corrected homotopy constraints are

\[
 m_1-(1-\lambda)0.6-\lambda r_{23}=0,
 \qquad
 m_2-(1-\lambda)0.8-\lambda r_{31}=0.
\]

The \(F_5\) run reached \(\lambda=1\).  \(F_3\) reached about \(0.874\) and
\(F_4\) about \(0.606\) before the unregularized physical shooting became
noise-limited.  \(F_6\) stalled earlier.  These stalls are engineering
failures, not dynamical obstructions; the script needs pair-adaptive
Levi--Civita charts and pseudo-arclength continuation.

### Critical warning

The opposite signs for \(F_1\) and \(F_2\) are **not an intermediate-value
bracket**.  Their free-group words differ, so they are not presently points on
one proved connected curve of mass--side-tied periodic solutions.  Treating
them as a bracket would be a fatal error.  The new information is that the
right locus passes between known isolated tied-periodic solutions in the
ambient parameter space.  The task is to manufacture or prove a connected
branch on which the defect crosses zero, or to find an individual zero by a
different exact mechanism.

All values in this section are **ORDINARY NUMERICAL EVIDENCE**.  The displayed
minimum separations are sampled, not rigorous lower bounds.  Direct Cartesian
residuals near the close encounters are often noise-limited at \(10^{-8}\) to
\(10^{-6}\).  Port candidates to a global selected-pair Levi--Civita chart
before interpreting small differences.

## 6. Dimension count: the construction must earn one missing degree

Use normalized unknowns

\[
 z=(x,y,\tau,m_1,m_2)\in\mathbb R^5.
\]

The periodic-brake equations give three conditions,

\[
 \mathcal B(z)=0,
\]

so the regular general periodic-brake locus is nominally two-dimensional.  The
two side-tie equations

\[
 S_1=r_{23}-m_1=0,
 \qquad
 S_2=r_{31}-m_2=0
\]

generically cut it to isolated points.  The right equation

\[
 D=m_1^2+m_2^2-1=0
\]

is one further condition.  Thus a Pythagorean mass--side periodic orbit is
overdetermined even over the reals.  Rationality is an additional exact
requirement.

The construction program therefore needs a structural source for one missing
degree, such as:

1. a reversing symmetry that makes one component of \(\mathcal B\) automatic;
2. a rank-four point of the five-equation map \((\mathcal B,S_1,S_2)\), from
   which a one-dimensional tied-periodic branch bifurcates;
3. a collision-regularized or resonance family whose unfolding supplies a
   genuine continuous tied-periodic branch;
4. an exact identity on a special symbolic family that relates one brake
   condition to the side or right conditions;
5. an arithmetic construction that fixes a rational \(u\) and forces the
   remaining return conditions by an exact symmetry.

Merely cataloging more isolated roots with differently signed \(D\) does not
provide this degree.

## 7. Primary construction program: symmetry and rank loss

### 7.1 Classify usable reversing symmetries

Newtonian flow is equivariant under every plane reflection \(R\), and

\[
 K_R(q,v)=(Rq,-Rv)
\]

is a reversing involution.  If a trajectory reaches `Fix(K_R)`, then reflection
plus time reversal extends that segment to a symmetric orbit.  Derive the
fixed-set shooting conditions exactly in translation- and rotation-reduced
coordinates.

For a reflection axis \(L\), `Fix(K_R)` means that every labelled position is
on \(L\) and every labelled velocity is perpendicular to \(L\).  A trajectory
starting from a brake and reaching this set returns later to the reflected
initial brake and hence has a labelled period after doubling again.  This is a
legitimate way to engineer periodicity without equal masses.

However, perform the codimension count honestly.  In a moving syzygy frame,
the fixed-set conditions generally consist of the syzygy equation plus two
independent longitudinal relative-velocity equations.  Zero total momentum
removes only the center-of-mass component; zero angular momentum constrains
normal rather than longitudinal velocities.  It is not yet known that the
tied-right family supplies enough variables.  Find an exact identity or a
special symbolic itinerary that makes one of these conditions automatic.  Do
not assert that “hitting syzygy” alone creates a periodic brake orbit.

Investigate other finite reversing symmetries, including reflection composed
with a half-period shift, but reject any operation that permutes distinct mass
labels.  Rotation-modulo-return is not the theorem, although a finite-order
relative symmetry may be doubled to a strict labelled period if proved.

### 7.2 Search for rank-deficient tied-periodic roots

For every well-refined mass--side candidate, compute a trustworthy Jacobian

\[
 D_z(\mathcal B,S_1,S_2).
\]

Use variational equations in a regularized chart, not finite differences
through a \(10^{-4}\)-scale encounter.  Record singular values and the null
vectors.  The existing rough values are:

- \(F_{30}\): smallest singular value about \(0.199\), apparently transverse;
- \(F_2\): direct finite-difference value about \(0.72\), also apparently
  transverse, but its residual is stiffness-limited and this must be repeated
  in pair--31 Levi--Civita coordinates.

A root where the smallest singular value tends to zero is much more valuable
than another small right defect.  At a verified rank-four root, use
Lyapunov--Schmidt or pseudo-arclength continuation to determine whether a
one-dimensional tied-periodic branch exists.  If \(D\) changes sign on one
connected branch, the intermediate-value theorem gives a real tied-right
periodic orbit.  Only after that should rationality become central.

Search especially near:

- collision-curve tangencies where a free-group word changes;
- period-doubling or symmetry-breaking points;
- folds encountered by the corrected \(\lambda\)-homotopy;
- high-word-length sequences accumulating on a regularized collision orbit;
- families related by reflection or word reversal.

### 7.3 Replace the exploratory homotopy by regularized pseudo-arclength

The current direct physical homotopy is only a seed generator.  Rebuild it
with:

1. an automatically selected global Levi--Civita pair chart;
2. exact reconstruction of all three side lengths and brake residuals;
3. propagated variational equations;
4. pseudo-arclength continuation through folds;
5. event tracking that prevents a silent change of symbolic word;
6. minimum-separation monitoring on the complete segment.

Finish the stalled \(F_3\) and \(F_4\) paths, but do not mistake completion of
the 30-orbit table for the goal.  Use it to locate rank loss or a connected
defect-crossing mechanism.

## 8. Strong fallback: direct tied-right event geometry

Enforce the exact tied-right curve from the beginning.  For each \(u\), every
possible brake is a strict \(I\)-maximum.  On a regular maximum branch
\(t=t_k(u)\), the conjecture is equivalent to origin avoidance by the complex
analytic curve

\[
 u\longmapsto\zeta(u,t_k(u)).
\]

Build a collision-regularized event atlas over the full fundamental interval

\[
 0<u\le\sqrt2-1.
\]

Instead of minimizing \(\lVert\mathcal B\rVert\) at arbitrary clock times,
continue each maximum branch and plot its two true residual components.  Locate
near-origin passages, folds, and branch endpoints.  A numerical near-zero is
only a candidate.  If a root appears, refine it with independent regularized
integrators and then use interval Newton or a validated Poincare map.

For rational construction, enumerate low-height \(u=p/q\) only around a
structurally identified near-zero branch.  A large blind scan is not proof
progress.  At an exact Pythagorean root,

\[
 (a,b,c)=(q^2-p^2,2pq,q^2+p^2)
\]

up to reduction and leg swap.

## 9. Collision-unfolding program

Classical collision orbits are not counterexamples, but a regularized
collision orbit may organize a nearby family of collision-free symmetric
periodic orbits.  This is a legitimate construction mechanism if the final
candidate has a rigorously positive minimum separation.

The isosceles-right endpoint has already been classified and locally excluded,
so seek other organizers:

- the Szebehely--Peters regularized near-\(3{:}4{:}5\) periodic collision
  orbit;
- Schubart-like orbits and their planar symmetry-breaking bifurcations;
- catalog collision curves where two collisionless brake branches meet;
- high-order binary-scattering resonances in the skinny limit.

Use regularization only as a chart.  Do not claim that a post-collision
continuation is a classical solution.  The desired output of the unfolding is
a positive impact parameter and an exact second brake before any collision.

## 10. Rationality gate

Even a rigorously validated real root \(D=0\) need not have rational Euclid
parameter

\[
 u=\frac{m_2}{1+m_1}
\]

for the displayed leg convention.  Decimal agreement with a rational is not
enough.  Once a real root is found:

1. compute it at several hundred digits with independent regularized methods;
2. attempt rational reconstruction with explicit height bounds;
3. derive an exact algebraic or symmetry condition for \(u\);
4. if proposing \(u=p/q\), rerun the shooting with that rational frozen
   exactly and validate the remaining equations;
5. prove positive pair separation over the full half-orbit;
6. prove simultaneous vanishing of all labelled inertial velocities at the
   second brake by interval Newton, CAPD, Taylor models, or an equivalent
   validated method.

An interval root containing both a nearby irrational \(u_*\) and a rational
approximation \(p/q\) does not prove that the rational point is periodic.

## 11. What would count as a breakthrough

In descending order:

1. a primitive integer triple and a validated collision-free second brake at
   its exact tied initial condition;
2. a rigorous real tied-right periodic orbit plus a proof that its parameter is
   rational;
3. a proved connected branch of mass--side-tied periodic orbits on which \(D\)
   changes sign;
4. a verified rank-four bifurcation with a local defect-crossing theorem;
5. a new reversing-symmetry reduction that makes the Pythagorean shooting
   problem square;
6. a sharply localized numerical candidate with stable hundreds-digit rational
   reconstruction and independent regularized agreement.

Opposite signs on disconnected roots, a finite residual at a rational triple,
or a regularized collision return does not count.

## 12. Immediate recommended sequence

1. Reproduce \(F_1,F_2,F_5,F_{30}\) and port each to its deepest-pair global
   Levi--Civita chart.
2. Compute variational Jacobians and singular vectors for the five-equation
   mass--side shooting map.
3. Classify the catalog words under reversal, reflection, cyclic conjugacy, and
   collision-curve adjacency.  Determine whether any negative- and
   positive-defect candidates lie on one genuine continuation surface or meet
   at a rank-deficient organizer.
4. Derive the reflection--time-reversal fixed-set equations in reduced Jacobi
   variables and prove the exact codimension.  Search for a Pythagorean
   mass/shape identity that cancels one condition.
5. Upgrade the homotopy to regularized pseudo-arclength and finish only the
   branches indicated by steps 2--4.
6. If a tied-right real root appears, freeze its inferred rational \(u=p/q\)
   immediately and start the validated counterexample protocol.

## 13. Reporting discipline

Maintain a separate counterexample ledger.  For every candidate record:

- exact or decimal input status;
- free-group word and labelled syzygy sequence;
- masses, initial side lengths, and right defect;
- half-period and all three brake residuals;
- selected regularization charts and chart transitions;
- minimum separation and whether sampled or validated;
- energy and time-reversal errors under precision refinement;
- shooting Jacobian singular values;
- whether the candidate belongs to a proved connected branch;
- rational reconstruction attempts and height bounds;
- evidence label.

Assign an adversarial pass before promoting any claim.  In particular, attack:

- the false intermediate-value inference between different words;
- accidental unlabelled or rotation-only return;
- numerical passage through a true binary collision;
- loss of uniformity in a close-encounter chart;
- rational approximation substituted for an exact rational parameter;
- finite-difference Jacobians corrupted by close-passage stiffness;
- a second brake inferred from only one or two reduced velocity components.

The user explicitly wants a deliberately engineered periodic triple.  Pursue
that target aggressively, but state immediately and unambiguously if the
construction instead yields only a non-Pythagorean tied orbit, an irrational
tied-right orbit, or a collision orbit.
