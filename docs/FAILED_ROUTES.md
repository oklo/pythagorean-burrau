# Failed or blocked routes

## Physical transverse-velocity quotient through every LC collision block

An attempted first-order incoming-tail proof tried to infer
$R_y'/B=o(1)$ uniformly from small divided LC normal invariants. This is
false. For the exact unforced LC ellipse
\[
w(s)=a\cos(s/\sqrt2)+i\delta\sin(s/\sqrt2),\qquad R=w^2,
\]
the smooth normal invariants are $O(\delta)$, while at closest approach
$|dR_y/d\tau|\asymp\delta^{-1}$. Taking $\delta=B^2$ makes the divided LC
normal data tend to zero but gives $(R_y'/B)\asymp B^{-3}$.

The failure is coordinate conversion, not loss of regularity of the LC flow.
The repair is now proved: propagate $(L/B,K/B)$ through complete and partial
blocks, use only the binary transverse position in the outer equation, and
convert to physical transverse velocity on a section uniformly separated from
binary collision. The exact cubic outer-torque cancellation, a two-scale
Volterra bootstrap, and reflection removal of longitudinal difference
quotients yield the first-order incoming theorem without resurrecting the
false physical-velocity bound.

## No brake state on the restricted finite-turn side

**Status:** DISPROVED.

The first-turn time tends to infinity as a finite-turn phase approaches the
transverse parabolic separatrix. Since the heavy binary's mean anomaly
advances exactly at rate four, continuity forces infinitely many phases where
the first outer turn coincides with a binary apocenter. All restricted
velocities vanish at those instants. The prescribed heavy binary has undergone
regularized collisions, so these are not classical finite-mass counterexamples.
They do show that the finite-$B$ proof must calculate a resonance splitting
rather than invoke a uniform restricted no-brake claim.

## Mutual-distance derivatives as a brake residual

**Status:** DISPROVED.

At a syzygy, a transverse shape velocity can leave all three mutual-distance
derivatives zero.  Example: positions $(-1,0),(1,0),(0,0)$ with only the
middle body's velocity equal to $(0,1)$.  Every pairwise distance has zero
first derivative, but the Hopf quotient residual detects the motion.  The
repair is the three-component Hopf residual documented in `CONJECTURE.md`.

## Preserved-incenter interpretation

**Status:** DISPROVED as a general invariant.

The center of mass is fixed and initially equals the incenter.  Were it to
remain the incenter, uniqueness of barycentric coordinates would force the
instantaneous side-length ratios to remain the mass ratios.  The proved
positive value of $D''(0)$ shows that the right-triangle side relation changes
immediately, so the initial coincidence is not preserved.

## Cardinality/genericity proof

**Status:** DISPROVED as an inference.

Countability, measure zero, analyticity, and the three-equations/two-unknowns
dimension count supply no exact exclusion of rational zeros.  This route is
inactive unless dynamics first produces an explicit arithmetic condition.

## Global Pythagorean-defect cone

**Status:** DISPROVED by converged ORDINARY NUMERICAL EVIDENCE as a candidate
global lemma; the numerical statement itself is not interval validated.

For $u=1/3$, DOP853 integrations with successively smaller steps and tolerances
agree that

\[
D(0.376)\approx-0.004664128339.
\]

The smallest prior separation is about $0.002791245371$, so this is a close
ordinary encounter, not a declared collision.  The best maximum relative
energy drift before the sampled sign change was $2.9\times10^{-12}$.  The
three runs agree in the displayed defect digits.  This is sufficient to stop
investing in $D>0$ as the primary route, but it is not cited as a rigorous
counterexample to that auxiliary lemma.

The exact local identity $D''(0)>0$ remains useful as a jet and as proof that
the incenter coincidence is not preserved.

## First skinny passage implies immediate escape

**Status:** DISPROVED analytically as an asymptotic route.

The Levi--Civita theorem proves a positive $B^{11}$ heavy-pair miss and a
nonzero $B^{11/2}$ angular momentum after the first passage. However the outer
body has $\rho=1+O(B^2)$ and physical radial speed only $O(B^{3/2})$. For
every binary radius bound $R=O(B)$,

\[
{1\over2}\dot\rho^2-{A+B+1\over\rho-R}=-2+O(B)<0.
\]

Thus neither the new terminal criterion nor the Standish--Yoshida criteria can
certify escape at that section. The outer body later plunges on an order-one
time scale, after roughly $(2B^{3/2})^{-1}$ binary cycles. A phase-uniform
later scattering theorem is required.

## Every late-plunge phase escapes with a uniform margin

**Status:** DISPROVED in the exact limiting restricted model.

The local $X=B R$, $Y=B Z$, $t-t_*=B^{3/2}\theta$ scaling tends to an
equal-heavy-mass rectilinear restricted problem. At the phase where the light
particle crosses the perpendicular bisector at binary apocenter, a rigorous
launch-speed boundary argument produces a parabolic-to-parabolic orbit with
zero outgoing energy. Thus no phase-uniform strict escape certificate can hold
in the limit.

This does not prove a bound orbit or second brake at positive $B$. The repair
is to compute the separatrix splitting caused by finite $B$, the incoming
energy $-2B+o(B)$ in scaled units, and the longitudinal symmetry breaking.

## Globally negative tight-pair torque

**Status:** DISPROVED by ORDINARY NUMERICAL EVIDENCE as a shortcut.

The exact initial torque is negative, and its first-encounter integral has a
negative leading coefficient. It is not sign-definite throughout the exact
motion. At $u=1/3$, ordinary integration and the exact torque formula give a
small positive value near $t=0.3757632445$. No theorem relies on this decimal
falsification; it records why initial torque cannot be extrapolated globally.

## Naive whole-line phase Melnikov integral

**Status:** DISPROVED as a well-posed transversality coefficient without an
asymptotic phase gauge.

The formal phase variational equation admits $\zeta=z'$, the Jacobi field that
translates the entire parabolic orbit in time. With that choice its proposed
Melnikov integrand is exactly
\[
{d\over d\theta}\left({rr'\over2(z^2+r^2/4)^{3/2}}\right),
\]
so the whole-line integral vanishes. Naive conditions $\zeta,\zeta'\to0$ at
parabolic infinity do not eliminate this mode: $z'=O(|\theta|^{-1/3})$ also
tends to zero.

The repair is to fix the coefficient of the parabolic time-translation mode,
or, more invariantly, compare incoming and outgoing parabolic curves on the
finite section $z=0$. Reversibility then gives
$V_s(\phi)=V_u(-\phi)$, and the genuine transversality condition is
$2V_u'(0)\ne0$. This condition is now proved by a finite interval Jacobi sign
plus a McGehee-map tangent contraction. The improper-integral route remains
ill posed without a gauge, but is no longer needed for nonvanishing.

## Raw monopole phase on a fixed restricted section

**Status:** DISPROVED as an exact gauge identification.

The first phase-window draft compared the true raw binary phase on
$\rho=BY_0$ with
\[
\Phi_{\rm sec,ref}=n_{\rm bin}t_0(BY_0).
\]
This correctly subtracts the divergent monopole flight phase from
$\Phi_{\rm ref}$, but it still omits the full restricted parabolic tail. At
fixed $Y_0$, the binary quadrupole contributes a finite $Y_0$-dependent tail
term that the monopole formula does not represent; the exact restricted field
is not the monopole field.

The repair is to label the incoming parabolic curve by its asymptotic phase
intercept $\chi$ and compare the full fixed-section state with
$\Gamma^-_{Y_0}(\chi)$. PREPLUNGE_MATCHING.md proves
$\chi=\Phi_{\rm ref}+o(1)$ at an early overlap. INCOMING_TAIL.md subsequently
proved uniform propagation down the restricted tail. Thus the raw-section
gauge remains a failed route, but its invariant-intercept repair is complete.

## Ordinary continuity through the finite-mass triple endpoint

**Status:** DISPROVED as a proof step; repaired by a coupled exchange theorem.

The first finite-$B$ endpoint draft observed correctly that Newtonian
homogeneity leaves an $O(B)$ vector-field perturbation after the joint inner
scaling. It then invoked the restricted shifted-Fuchsian exchange over a dwell
of length $O(|\log h|)$ and used ordinary LC continuity to propagate a state
after division by the shrinking transverse amplitude. Neither inference was
valid: fixed-section $C^0$ convergence does not control a diverging saddle
dwell, and unscaled LC convergence does not imply convergence after division.

The repair in `FINITE_B_TRIPLE_ENDPOINT.md` constructs the full homogeneous
McGehee system, includes stable-graph and exponent drift, closes the base and
fiber bounds simultaneously, and compares the actual and restricted center
clocks. In the heavy-binary LC chart, reflection and Hadamard division expose
the missing source explicitly as
$B/\eta=\varepsilon^{(1+\sqrt7)/6}\to0$. The repaired wedge theorem received
two independent adversarial endorsements. This failed shortcut is retained to
prevent future use of ordinary continuous dependence in a divided joint
limit.

## Universal outer-strip invariance

**Status:** DISPROVED by an EXACT SYMBOLIC IDENTITY.

The planar joint-limit shape system is strictly convex in the transverse
coordinate throughout $|y|\ge\sqrt3/2$, suggesting that every projective
orbit might remain in that strip and inherit a fixed angular-momentum sign.
The zero-projective orbit already violates this. At the lower equilateral
rest point its stable expansion is
\[
 x=T e^{-(1+\sqrt7)\zeta/6}+\cdots,\qquad
 y+{\sqrt3\over2}
 =kT^2e^{-(1+\sqrt7)\zeta/3}+\cdots,
\]
with
\[
 k={2\sqrt{21}-5\sqrt3\over4}>0.
\]
It therefore bends into $|y|<\sqrt3/2$. Positive projective parameters enter
the strip already at linear order. The convexity and exact torque identities
remain useful as conditional transition rules, but global strip invariance
cannot be the missing scalar obstruction.

## Global nonvanishing of planar shape angular momentum

**Status:** DISPROVED by ORDINARY NUMERICAL EVIDENCE as a shortcut.

The exact torque factorization gives a fixed sign while $xy$ does not change
sign, but it does not prevent cancellation after inner-strip transitions. In
the deterministic planar probe with transverse sign $T=-1$, the
$\kappa=1.265$ orbit passed within about $9.4\times10^{-5}$ of a light-heavy
collision and crossed $\Lambda=0$ before reaching $|w|=20$. Nearby
$\kappa=1.260$ retained positive $\Lambda$, while $\kappa=1.265$ exited with
negative $\Lambda$.

This is not a rigorous collision or zero certificate, and no theorem uses the
decimal values. It shows why the exact torque sign cannot be integrated
globally without classifying collision-separated components and every change
of sign of $xy$.

## Independent-box conversion at the planar shape-to-LC interface

**Status:** DISPROVED as an interval-Newton implementation; repaired by one
persistent $C^1$ doubleton.

The first validated collision stage propagated the stable-tail box to
$\zeta=0.3$, converted the terminal interval vector componentwise to LC
coordinates, and initialized a fresh doubleton. This safely proved finite
existence and chart-domain inequalities, but discarded the dominant affine
correlations. At the apparent root its final $u$ box had widths of order
$10^{-2}$, and a first $C^1$ version produced a Jacobian interval containing
singular matrices. Narrowing ordinary solver tolerances cannot restore
information already lost at the nonlinear coordinate projection.

The successful repair keeps shape and LC variables in one 13-dimensional
`C1Rect2Set`. A unit-time construction vector field freezes the shape state
and writes the exact nonlinear LC entry into initially zero variables. CAPD
therefore transports the same affine error directions through the coordinate
change and subsequent LC flow. With the analytic tail moved to $\zeta=15$,
the repaired interval Newton proves a unique transverse collision root. The
independent-box stage remains useful as a broader chart-domain certificate,
but it cannot certify the root by itself.

## Finite-time openness of restricted escape

**Status:** DISPROVED as a positive-mass proof step; repaired by a global
hierarchical-energy lemma.

The collision root's regularized restricted continuation reaches a terminal
state in a strict escape cone.  The first draft inferred that every nearby
small positive-light-mass trajectory also escapes from compact LC convergence
to that section.  This is insufficient: for \(B>0\), the heavy primaries no
longer follow the prescribed parabolic binary, and the light body's
backreaction accumulates over an infinite future interval.  No finite-time
openness theorem controls that accumulation.

The repair in `COMPUTER_ASSISTED_PLANAR_COLLISION_ESCAPE.md` uses full Jacobi
variables.  It bounds the inner separation by a linear envelope under a small
positive energy ceiling, forces the outer radius to outrun that envelope, and
bounds all future tidal energy by \(2BK\) with \(K<\infty\) uniformly on the
scaled terminal neighborhood.  A validated strict margin \(>0.69\) closes
the simultaneous bootstrap.  This failure is retained to prevent future
promotion of a restricted escape cone to finite mass by continuity alone.

## Ordinary-coordinate bridge after the second planar collision

**Status:** FAILED AS A VALIDATED IMPLEMENTATION; repaired by a third LC
chart.

The regularized continuation of the second collision root eventually enters
a large escape cone, but a direct ordinary-coordinate bridge passes within
about $4.3\times10^{-4}$ of the positive primary.  That is a smooth close
passage, not a collision, and it makes componentwise interval propagation
needlessly ill-conditioned.  Declaring it a collision would violate the
classical problem, while stopping before it would leave the outgoing
classification open.

The repair switches exactly from the negative-primary coordinate to
$q_+=q_--Re_x$, uses a cancellation-free square-root lift, and crosses the
passage in a positive-primary LC chart.  The resulting pinned certificate
keeps the unregularized primary separated and then reaches the heavy-binary
escape bridge.  See
`COMPUTER_ASSISTED_PLANAR_SECOND_COLLISION_ESCAPE.md`.

## Independent box restart at the fifth planar close encounter

**Status:** REPAIRED THROUGH THE FIFTH OUTGOING SECTION; direct continuation
through the overlapping fifth--sixth passages still fails.

The full fourth-root parameter box can be propagated rigorously through its
negative-primary ejection to a positive-primary LC entry with large chart
margins.  Ordinary continuation shows that the ensuing passage has miss
distance of order $10^{-7}$.  Restarting CAPD from the componentwise interval
image in the fifth chart discards the small impact-parameter correlation.
Near the outgoing section the hull of the LC coordinate still contains zero,
so division by $|u_+|^2$ cannot reconstruct an ordinary bridge state.  Longer
propagation makes the clock enclosure reach the heavy-collision boundary.

This failure did not prove a collision.  It was repaired by retaining one
persistent CAPD doubleton through every nonlinear chart map and by terminating
on the transverse fifth-LC section $c_i=1/20$.  The full fourth-root box now
reaches that outgoing section with both primary distances strictly positive;
see `COMPUTER_ASSISTED_PLANAR_FOURTH_TO_FIFTH_OUTGOING.md`.

A direct ordinary-coordinate bridge after that section still fails.  The
fifth positive-primary and sixth negative-primary encounters overlap: an
immediate switch to the negative-primary LC chart leaves the unregularized
positive-primary denominator enclosing zero, even on a one-picounit
$\kappa$ tile and with smaller solver steps.  Moving the fifth outgoing
section farther out improves its own selected-pair separation but does not
create a single-centre interval domain spanning the overlap.  This is again a
chart obstruction, not evidence of collision.  The next repair should use a
simultaneous two-centre regularization (or an equivalent correlated atlas)
before attempting the terminal escape bridge.  Merely shrinking the time
step or the parameter tile does not address the overlapping singular charts.

## Redundant two-centre variables and componentwise Poincare restart

**Status:** FAILED AS LONG-TIME ENCLOSURES; the exact two-centre field remains
valid.

The simultaneous elliptic regularization removes both physical force
singularities exactly. Evolving redundant half-angle variables \((s,c)\)
allows the doubleton hull to drift away from \(s^2+c^2=1\), after which the
polynomial momentum field wraps rapidly. Evolving the nonredundant coordinate
\(\xi=\alpha+i\beta\) avoids that defect and rigorously carries a
one-picounit parameter tile for \(0.7\) regularized-time units, but the current
set then wraps in momentum and shape energy. Replacing the correlated set by
the componentwise Poincare image narrows position but widens the decisive
momentum direction and fails sooner.

None of these failures indicates a collision or invalidates the analytic
chart. The next repair must preserve the implicit section-time correlation,
for example by a section-adapted Poincare doubleton or an interval-Newton time
correction onto the exact fifth section. Reboxing or adding redundant
constraints without a constraint-preserving set representation does not
solve that problem.
