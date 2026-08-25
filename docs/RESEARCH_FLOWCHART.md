# Pythagorean--Burrau research flow chart

Date: 2026-08-25

This is a physics-facing map of the project. It distinguishes proved results
from numerical scouting and from the remaining conjectural steps.

Status key:

- **[A]** proved analytically;
- **[CA]** proved by a computer-assisted argument using validated intervals;
- **[E]** exact symbolic identity;
- **[N]** ordinary numerical evidence, used only to design proofs;
- **[IN PROGRESS]** a rigorous calculation or proof architecture not yet
  promoted to the proof ledger;
- **[OPEN]** indispensable unresolved step; and
- **[FAILED]** a tempting route that has been disproved or shown inadequate.

## Main logical flow

```text
Exact labelled Newtonian free-fall problem
    |
    +--> [A] Simultaneous mass--length scaling
    |         (a,b,c) and (ka,kb,kc) are dynamically equivalent
    |         |
    |         +--> Only primitive Pythagorean triples matter
    |
    +--> [A] Euclid parametrization and normalization
    |         u=s/r,  A=(1-u^2)/(1+u^2),  B=2u/(1+u^2)
    |         masses=(A,B,1), exact tied right triangle
    |         |
    |         +--> Integer conjecture = rational u in (0,1)
    |         +--> Leg swap reduces study to 0<u<=sqrt(2)-1
    |
    +--> [A] Time reversal: periodicity <=> a positive second brake
    |         |
    |         +--> Find or exclude a later time when all labelled
    |             inertial velocities vanish simultaneously
    |
    +--> [A] Translation/rotation reduction and brake residual B(u,t)
    |         B=0 <=> all labelled inertial velocities vanish
    |         |
    |         +--> [A] Lagrange--Jacobi event reduction
    |                   every brake is a strict local maximum of I,
    |                   U=U0, and all pair separations have positive bounds
    |                   |
    |                   +--> Search only the maximum-event branches
    |                   +--> Validated time covers can exclude brakes
    |
    +====================== FOUR ACTIVE MATHEMATICAL ROUTES =================+
    |
    +--> Route 1: shape geometry and torque history
    |         |
    |         +--> [E/A] exact torque equations, launch signs, side ordering
    |         +--> [CA] gravitational signs on complete ordered shape cones
    |         +--> [E/CA] scalar history reduction eta<h and thresholds Z_J
    |         +--> [CA] complete one-sided near-isosceles analysis
    |                   |
    |                   +--> [CA] punctured real neighborhood is nonperiodic
    |                         (hence infinitely many primitive triples)
    |         |
    |         +--> [OPEN] global reachable-history inequality in the interior
    |                   Static energy/shape inequalities are insufficient.
    |
    +--> Route 2: skinny-triangle singular limit u->0
    |         |
    |         +--> [A/CA] Levi--Civita encounter asymptotics and scattering map
    |         +--> [A] exact phase clock plus equidistribution
    |         +--> [A/CA] positive-lower-density subset of
    |                   (4n^2-1,4n,4n^2+1) is nonperiodic
    |         +--> [A/CA] infinitely many open skinny nonperiodic intervals
    |         |
    |         +--> [OPEN] classify every phase and the thinnest boundary layer
    |
    +--> Route 3: validated middle-parameter maximum maps
    |         |
    |         +--> [CA] full nonperiodicity certificates for five named
    |         |         primitive triples
    |         +--> [CA] every real u in [0.29,0.29002] is collision-free
    |         |         through its first positive I-maximum, which is not a brake
    |         +--> [E] exact pair-13 <-> pair-23 Levi--Civita chart changes
    |         +--> [IN PROGRESS] a narrow validated trial reaches the second
    |                   minimum near t=1.934, but has not been committed as a theorem
    |         |
    |         +--> [OPEN] recondition the close-passage graph strongly enough
    |                   to certify the second and every later maximum
    |
    +--> Route 4: counterexample and periodic-family audit
              |
              +--> [N + exact comparisons] no catalogued orbit is an exact match
              +--> [N] nearby F30 periodic family is a serious threat locus
              +--> [N] its sampled tied candidate has nonzero Pythagorean defect
              |
              +--> [OPEN] validated family-intersection/nonintersection proof

                                    |
                                    v
Current resolution status
    Full rational conjecture: [OPEN]
    Strong real conjecture:   [OPEN]
    Exact rational candidate: none found
    Exact real second brake:  none established
    Difficulty-weighted completion estimate: about 58% +/- 15%
```

## What is already a theorem

The main exact achievements are not merely numerical surveys:

1. The scaling, rational parametrization, leg-swap symmetry, second-brake
   equivalence, and coordinate-valid brake residual are proved for the full
   family.
2. Every possible brake is reduced to a collision-separated strict maximum of
   the moment of inertia. This supplies a rigorous event-cover criterion.
3. A complete punctured one-sided neighborhood of the isosceles endpoint is
   proved nonperiodic.
4. A positive-lower-density subset of an explicit infinite primitive
   Pythagorean family is proved nonperiodic in the skinny regime.
5. Five individual middle triples have full validated nonperiodicity
   certificates.
6. A continuum of real parameters, $0.29\le u\le0.29002$, is proved
   collision-free and brake-free through its first positive inertia maximum.

Items 3--6 are major partial theorems. None alone covers every rational
parameter and every possible later maximum.

## Why the remaining arrow is hard

The unresolved step is not the ability to integrate a close encounter. The
Levi--Civita charts do that rigorously. The problem is preserving a narrow,
parameter-correlated enclosure after many close passages and proving that no
later maximum can have all three reduced velocity components zero.

The current second-maximum experiment makes this precise. A validated graph
crosses the pair--23 passage near $t=1.60$, switches exactly to a pair--13
chart, and reaches the strict second minimum near $t=1.934$. Near the closest
part of that passage, the enclosure becomes too wide for efficient onward
propagation. This is an enclosure-geometry obstruction, not evidence for a
brake or collision. The next repair is a better local section/multiple-shooting
representation that recenters the center orbit without losing the common
$u$-dependence.

## Glossary

**Brake / brake point.** A time at which every labelled body's inertial
velocity is zero. The initial condition is a brake at $t=0$. A positive later
one is a second brake.

**Second-brake lemma.** Because Newton's equations are time reversible, a
collision-free free-fall orbit is periodic exactly when it reaches a second
brake. Reflecting the brake-to-brake segment in time produces the full labelled
periodic orbit.

**Labelled return.** Body 1 must return as body 1, and similarly for bodies 2
and 3. Returning only after permuting bodies, rotating the picture, or
regularizing through a collision does not satisfy this conjecture.

**Primitive Pythagorean triple.** A triple $(a,b,c)$ with
$a^2+b^2=c^2$ and no common integer factor. Common multiples are dynamically
redundant because this problem scales masses and lengths together.

**Tied family / mass--geometry coupling.** The mass at each vertex equals the
length of the opposite side. The word “tied” emphasizes that masses and shape
cannot be varied independently.

**Euclid parameter $u$.** The rational parameter $u=s/r$ in Euclid's formulas.
After normalization it gives masses $(A(u),B(u),1)$ and the exact initial
triangle. Rational $u$ corresponds precisely to a primitive integer problem
after removing a possible common factor.

**Strong real conjecture.** The stronger claim obtained by allowing every real
$u$, not just rational $u$. Proving it would immediately prove the integer
conjecture.

**Center-of-mass moment of inertia $I$.**
$I=\sum_i m_i|q_i-q_{CM}|^2$. Write $J=\dot I$. Zeros of $J$ are extrema or
folds of the system's overall size.

**Lagrange--Jacobi identity.** For this free-fall energy,
$\ddot I=2U-4U_0$, where $U$ is the positive magnitude of the Newtonian
potential and $U_0$ is its initial value. At a brake, $U=U_0$, so
$\ddot I=-2U_0<0$: every brake is a strict $I$-maximum.

**Brake residual.** A vector made from three independent reduced velocity
components. Its vanishing is equivalent to all labelled inertial velocities
vanishing. A strict nonzero component rigorously excludes a brake.

**Jacobi coordinates.** Two relative vectors that remove center-of-mass
translation: one describes a selected binary separation and the other the
third body relative to that binary's center of mass.

**Shape.** The triangle after separating out translation, overall rotation,
and usually overall size. Shape variables describe side ratios and orientation.

**Syzygy.** A collinear three-body configuration. Syzygy is not a collision;
all three bodies may be distinct and the Newtonian solution completely smooth.

**Coordinate chart.** A choice of nonsingular variables for one region of
state space. Different close pairs call for different Jacobi/Levi--Civita
charts, related by exact transformations.

**Levi--Civita regularization.** For a selected planar binary separation
$g\in\mathbb C$, write $g=w^2$ and rescale time by
$dt=|w|^2d\sigma$. This removes the $1/|g|$ force singularity from the
transformed differential equations. Here it is used only as a mathematical
coordinate system through close noncolliding passages; it does not turn a
physical collision into an allowed continuation.

**Poincare map.** A map that follows a trajectory from one specified section
of state space to its first directed crossing of another section. Examples
here are fixed physical-time sections and $J=0$ event sections.

**Transverse crossing.** A section crossing with nonzero normal velocity.
This prevents a grazing contact and permits smooth continuation of the event
time as a parameter changes.

**$C^1$ enclosure.** A validated enclosure of both the flow and its first
derivative with respect to initial data or a parameter. It controls how the
whole one-parameter family moves, rather than merely enclosing one orbit.

**Mean-value graph.** An interval representation
$x(u)\in x(u_c)+D_ux([u_-,u_+])(u-u_c)$. It keeps the dominant correlation
between the parameter and the state, avoiding much of the artificial widening
caused by replacing the family with an axis-aligned box.

**Interval arithmetic / outward rounding.** Every computed number is replaced
by a guaranteed enclosing interval, and rounding is directed outward. If the
resulting interval lies strictly above zero, the true mathematical quantity is
proved positive despite floating-point rounding.

**CAPD.** A library for rigorous integration of differential equations and
validated Poincare maps. It combines interval arithmetic, high-order Taylor
methods, and wrapping-control set representations.

**Computer-assisted proof.** A finite computation whose mathematical logic,
input domain, dependency versions, and outward-rounded enclosures establish a
theorem. Repeating an ordinary high-precision trajectory calculation is not a
computer-assisted proof.

**Ordinary numerical evidence.** A nonvalidated integration or shooting
calculation. It is valuable for discovering event sequences, counterexamples
to proposed lemmas, and candidate intersections, but it is not promoted to a
universal or exact theorem.

**Parameter tile.** A closed subinterval of $u$ treated by one validated
family enclosure. Abutting certified tiles can cover a larger interval without
assuming anything about values between sampled points.

**Escape certificate.** A set of inequalities proving that a binary and an
outgoing third body remain sufficiently separated and energetically arranged
that no future brake or return is possible.

**Existential neighborhood.** A theorem that some nonzero interval exists,
usually by continuity or the implicit-function theorem, even if the proof does
not provide a convenient numerical endpoint.

**Punctured neighborhood.** A neighborhood with its endpoint removed. At the
isosceles endpoint the comparison orbit has a true collision, while every
sufficiently close one-sided member covered by the theorem is collision-free
through the corresponding near miss.

**Bernstein certificate.** A polynomial sign proof obtained by expressing a
polynomial in the Bernstein basis on a box. If every exact coefficient has the
required sign, the polynomial has that sign everywhere on the box.

**Positive lower density.** An infinite subset containing at least a fixed
positive fraction of integers asymptotically along a specified sequence. It is
stronger than merely proving infinitely many examples, but weaker than proving
every member.

**Transversality / implicit-function theorem.** A nonzero derivative condition
showing that an event or intersection persists as a unique smooth local branch
when a parameter changes.
