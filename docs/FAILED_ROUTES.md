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

## Global oriented-area concavity

**Status:** DISPROVED by converged ORDINARY NUMERICAL EVIDENCE as a candidate
global lemma; the later positive acceleration is not yet interval validated.

Although the exact Bernstein argument proves $\ddot\Delta_2(0)<0$ for every
fundamental parameter, the sign does not persist even to first syzygy in the
middle interval.  For $u=1/3$, a DOP853 replay with tolerance refinement gives

\[
 \min_{[0,t_{\rm syz}]}\ddot\Delta_2\approx-4043.23,
 \qquad
 \max_{[0,t_{\rm syz}]}\ddot\Delta_2\approx50.0105,
\]

with $t_{\rm syz}\approx0.3756716785$. The expression for
$\ddot\Delta_2$ includes the exact velocity cross term, not merely the force
terms. This rules out global area concavity as the primary structural lemma
on ordinary evidence while preserving the analytic launch sign. Reproduce
the bounded probe with

```bash
.venv/bin/python -m scripts.probe_torque_ordering --u 1/3
```

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

**Status:** REPAIRED THROUGH THE FIFTH FOCUS BY A DIFFERENT INITIALIZATION;
the componentwise fifth-section restart itself still fails.

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
chart obstruction, not evidence of collision. Merely shrinking the time step
or the parameter tile does not address the overlapping singular charts.

The successful repair bypasses the wrapped fifth-section state. A
multiprecision interval-Newton localization evaluates the exact fourth
collision phase, and that collision state initializes the simultaneous
two-centre chart directly. The resulting focus certificate proves a positive
miss distance. Two further Poincare sections reach a well-separated focus.
A componentwise ordinary bridge restart there still wraps, but an auxiliary
graph ODE retaining all six two-centre generators repairs that final loss and
reaches the strict escape cone.

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
chart. They remain failed formulations of the fifth-section restart. The
successful focus proof instead initializes at the earlier exact collision,
where the chart map has no implicit section-time uncertainty. Reboxing or
adding redundant constraints without a constraint-preserving set
representation still does not solve the original restart problem. The later
two-centre-to-ordinary conversion succeeds only after it is embedded as a
correlation-preserving graph map.

## Correlated fifth-section projection into the two-centre focus map

**Status:** FAILED AS AN INTERVAL FORMULATION; repaired by a fixed-clock
mean-value enclosure.

Carrying the full stable-tail doubleton to the fifth outgoing Poincare section
is sufficient to prove that section is reached, but projecting its implicit
return-time image into the two-centre chart magnifies the decisive momentum
direction.  Moving the stable-tail start from \(\zeta=15\) to \(18\), adding
the exact octic graph, and shrinking to one-picounit parameter tiles did not
repair the focus propagation: the projected momentum hull still crossed the
singular denominator or lost Poincare transversality.  This is set wrapping,
not evidence of collision.

The successful replacement chooses the rational fourth-LC clock
\(\bar\tau=37184019/10^8\), propagates the independently certified collision
state to that clock, and encloses the parameter dependence with the rigorous
one-variable mean-value formula (3) of
`COMPUTER_ASSISTED_PLANAR_FOURTH_COMMON_CLOCK_COVER.md`.  It removes the
implicit section-time uncertainty before the chart change.  The resulting
131-tile cover reaches the terminal escape cone on an explicit continuum.
Encoding the common-clock mean-value term as a single affine doubleton
generator was also tested for the still-open lower multi-focus band.  It did
not improve the second-focus enclosure: the longer Poincare leg wrapped the
momentum set and even lost the independent whole-leg $p_r<0$ audit near
offset 90 pico.  The missing repair must preserve correlation through the
first Poincare return itself, not merely at the common-clock entrance.

The lower band also cannot be closed by naively inserting one additional
componentwise focus restart.  Radius-one tiles at offsets 45, 60, 75, and 90
pico rigorously reach the second focus with negative $\beta$ and pass the
whole-leg $p_r<0$ audit.  From that componentwise image, however, the third
focus map wraps by several orders of magnitude.  Switching instead to the
separated section $\beta=-1$ fails near the transition where that section and
the second focus exchange order.  This localizes the remaining chart problem:
a correlation-preserving first-to-second-focus Poincare graph, or two
overlapping section atlases, is required.

A scalar $C^1$ mean-value restart was tested as a more targeted repair.  It
propagated the entrance tangent through the CAPD Poincare derivative and then
rebuilt each next-focus box from a center orbit plus that tangent times the
one-dimensional parameter displacement.  A radius-one tile at offset 45
pico reached two focuses, but its tangent widths had already grown to roughly
$2^{30}$--$2^{35}$.  At the third focus the state enclosure expanded to
momenta of order $3\times10^4$, and the directed section derivative enclosed
zero.  This is not a dynamical failure: the restart represented the current
state box and its tangent independently, so it still discarded the nonlinear
graph correlation it was meant to preserve.  The experimental command and
duplicate direct chart map were removed.  A successful repair must evolve an
actual one-generator state graph (or an equivalent augmented graph transform)
through the Poincare return, rather than reattaching an interval tangent to an
independent state hull.

CAPD's mutable set argument to `PoincareMap` was also continued directly,
without the componentwise restart.  The API explicitly leaves that object
just *after* the section, whereas the returned vector is the tight enclosure
of the Poincare image itself.  On the offset-45 radius-one tile, the retained
post-section set reached the attempted $\beta=-1$ leg with
$p_r\in[-2.60,0.032]$ and $p_i\in[-0.20,5.43]$; the section derivative then
enclosed zero.  Thus the mutable flow set is not a correlation-preserving
representation of the tight section image needed here.  The experimental
mode was removed.  A repair must construct a rigorous graph *on the section*,
not merely reuse the broader set after the crossing step.

Parameter subdivision alone does not repair the third-focus restart.  The
offset-45 experiment was repeated with radii $10^{-16}$ and $10^{-18}$ in
$\kappa$, respectively one tenth and one thousandth of the original
picounit radius.  Both third-focus maps still failed with momentum widths of
order $10^5$.  The irreducible componentwise width comes from the certified
reference-state and chart enclosures, then is amplified by the focus restart;
it is not dominated by the tile diameter.  Consequently an enormous finer
cover would not turn this formulation into a proof.

Replacing the MPFR collision-root reference by a direct rational tile-center
reference also fails.  Although it removes the root-box displacement, that
reference must traverse the entire stable-tail-to-fourth-chart chain as a
native-precision interval set.  At offset 45 its enclosure was already too
wide to prove $p_r<0$ over even the first focus leg.  The MPFR root anchor is
therefore not an incidental source of width: it is the sharpening that makes
the first two lower-band focuses certifiable.  A useful local anchor would
need its own multiprecision point certificate, not a repeated native long
propagation.

An independent MPFR-200 anchor at the exact rational center
$\kappa=1.264009098940$ and the fixed fourth-LC clock did pass.  Substituting
its outward state hull into the local radius-one tile sharpened the first
focus substantially and retained the two-focus proof, but the componentwise
third-focus restart still reached momentum widths of order $4\times10^4$ and
lost transversality.  Starting the octic tail at $\zeta=18$ instead of 15 made
every decisive anchor width larger: the extra interval flight outweighed the
smaller analytic tail remainder.  Thus neither roundoff, root-box uncertainty,
nor tail truncation alone is the dominant obstruction.  The remaining loss is
the repeated nonlinear chart/Poincare representation of the stable-tail
uncertainty, and it must be attacked before the section rebox.

## Double-precision fourth-root phase seed

**Status:** DISPROVED as a quantitative phase estimate.

The ordinary DOP853/SciPy chart chain in `probe_fourth_collision_root.py`
stalled at a collision residual of order \\(10^{-6}\\) and suggested
\\(v_i\\approx-7\\times10^{-6}\\). The validated 200-bit nested interval-Newton
calculation instead proves
\\(-3.83235\\times10^{-7}\\le v_i\\le-3.68194\\times10^{-7}\\). The ordinary seed
was useful only for locating the broad root neighborhood. Its terminal phase
must not be used in any proof or cached certificate.

## Near-root correlation-preserving anchor

**Status:** FAILED as an effective root-overlap certificate.

The exact section-flow construction repairs the earlier componentwise
Poincare reboxing and validates lower-band tiles. It does not by itself make
the fixed-clock reference hull arbitrarily sharp. An independent MPFR-200
anchor at the exact rational parameter
$\kappa=1.264009098933320$, only about $1.9\times10^{-15}$ above the certified
root box, was inserted into the one-generator graph. Even the point-hull
replay then wrapped in the terminal bridge. The dominant width is the
certified anchor state and its independent coordinate remainders, not the
parameter radius. Hence subdivision around this anchor cannot prove overlap;
a tighter point certificate or a graph initialized directly on the
transverse collision section is required. No dynamical conclusion follows
from this enclosure failure.

Three adversarial implementation findings are also preserved: Poincare
return times had been summed as absolute rather than relative diagnostic
times; the tangent hull omitted an anchor lying above a lower tile; and the
exact 500-millisecond branch skipped its evolution. All three are repaired.
The first and third affected diagnostics or unused branches, while the
second invalidated pre-repair lower-anchor experiments. Every result retained
in the proof ledger was replayed after the relevant repair.  A fresh
post-repair replay of the formerly skipped 500-millisecond branch confirms
that it now advances the state, but the wide test tile then reaches CAPD's
minimal-step failure near scaled time $18.3643$; it is not a certificate and
no retained theorem cites it.  The archived 1-millisecond lower tile, whose
anchor-to-tile hull exercises the other repair, replays successfully with
the stored hexadecimal margins.

## Brute-force compact-middle parameter covering

**Status:** FAILED as a plausible universal proof architecture.

Validated point certificates are effective, but measured parameter
amplification through one compact-middle close encounter is about
$3\times10^8$ and later event horizons can amplify much more.  Escape times
also need not be uniformly bounded near boundaries of the escaping set.
Consequently a rectangular subdivision of the entire $u$ interval would
require uncontrolled refinement and supplies no finiteness theorem.  This
does not disprove the conjecture or validated covering on a prescribed
compact box.  It shows that the universal step must classify maximum-event
branches or provide a sign, winding, or ordering obstruction; isolated point
certificates cannot simply be extrapolated into a continuum proof.

## Nominal-duration damped LC overwrite audit

**Status:** DISPROVED as a rigorous duration bound; repaired.

The first runtime overwrite gate used
$\tau_-=t_{\rm target,left}-t_{\rm start,right}$.  CAPD's interval time map
may declare completion as soon as the current-time interval overlaps the
target, which does not prove that every trajectory advanced by that nominal
lower duration.  Because the admissible overwrite gap grows with duration,
this could accept an unjustifiably large gap.  The repaired verifier saves
the initial construction state, completes the interval flow, and audits with
$t_{\rm end,left}-t_{\rm start,right}$, rejecting a nonpositive result.  A
fresh four-passage deep-encounter replay passed.  The pre-repair smoke alone
must not be cited; the archived smoke summary records the post-repair replay.

## Fixed linear projection of maximum-event shape velocity

**Status:** DISPROVED as a universal sign architecture by converged
**ORDINARY NUMERICAL EVIDENCE**.

Recording both components of
$\zeta=\mu_1\overline X\dot X-\mu_2\overline Y\dot Y$ at strict maxima of
$I$ shows all four quadrants on the single $u=1/3$ trajectory.  More
decisively, the three ordinary event values

\[
\begin{array}{c|c}
t& (\operatorname{Re}\zeta,\operatorname{Im}\zeta)\\ \hline
1.1472220464&(0.06162387,-0.31306428)\\
2.2538543510&(-0.28476246,-0.15623215)\\
4.0876526251&(0.06391316,0.05609840)
\end{array}
\]

have the origin in their convex hull, with positive weights approximately
$(0.04671,0.182996,0.770296)$.  Hence no fixed homogeneous real linear
functional of $\zeta$ can be strictly positive at every maximum event.
This does not exclude a branch-dependent winding/order invariant, a nonlinear
barrier, or a state-dependent projection.  It prevents promoting a sampled
quadrant pattern into the missing global theorem.

The exact torque residual has the same limitation.  At $u=1/3$, the three
ordinary maximum-event values

\[
\begin{array}{c|c}
t&(\ell_{12},\ell_{23})\\ \hline
2.2538543510&(-0.227839,0.631627)\\
2.61592744&(0.299009,0.303293)\\
4.0876526251&(0.0818102,-0.568424)
\end{array}
\]

have the origin in their convex hull with positive weights approximately
$(0.36710,0.14670,0.48620)$. Thus no fixed homogeneous linear projection of
$(\ell_{12},\ell_{23})$ is positive at every maximum either.  The torque
residual remains useful because its components obey exact signed integral
equations; the viable target is branch-wise winding/order or comparison of
the two cancellation times, not a universal half-plane.

## Direct interval shooting of the F30 mass--side candidate

**Status:** FAILED in physical/Jacobi coordinates; localized chart repair
required.

The exact eleven-state Jacobi interval verifier crosses the first close
pair-$23$ passage. Its point-center flow reaches the minimum time step at
scaled time $s\simeq0.280269$, physical time $t\simeq1.7626$, at the
second close pair-$23$ passage. Because the failure already occurs for the
point center, parameter subdivision cannot fix it.

The pair-$23$ Levi--Civita repair is now implemented globally, using the
regularized half-duration as the shooting parameter. A 192-bit center run
passes its deepest selected-pair encounter but later wraps at scaled time
$0.542$. A 256-bit/order-50 point center subsequently traverses the whole
half-orbit, but the radius-$10^{-8}$ $C^1$ parameter box wraps at
$s\simeq0.225958$: its pair-energy enclosure has already grown to about
$[-260,257]$. Thus the singular denominator and point flow are repaired; the
remaining issue is parameter-set representation and amplification. No
interval Newton inclusion or periodic-orbit existence claim has been
obtained; see
`F30_MASS_SIDE_VALIDATION.md`.

Halving the center maximum step to $2.5\times10^{-4}$ does not repair this
architecture.  The center again completes collision-free, but 4233 interval
steps accumulate terminal residual radii between $3.1\times10^{-7}$ and
$1.9\times10^{-6}$, worse than the earlier center run.  Consequently a
one-piece radius-$10^{-10}$ $C^1$ retry is abandoned.  Sectioned multiple
shooting or explicit reconditioning is required.

## Static energy domination of the first centrifugal gap

**Status:** DISPROVED by an exact interior state; torque history is required.

On the pre-syzygy sign cone write

\[
 \ell_{23}=a>0,\qquad -\ell_{31}={m_2\over m_1}ha,
 \qquad 0<h<1.
\]

The zero-angular-momentum identity then gives
$-\ell_{12}=a(1-h)/m_1>0$.  For a fixed noncollinear shape, exact quadratic
minimization of kinetic energy gives

\[
 2K\ge {a^2\over R^2}F,
 \qquad
 F=y^T(CM_v^{-1}C^T)^{-1}y>0,
 \qquad y=(0,1,-m_2h/m_1)^T,
\]

where $R=r_{12}$, $M_v$ is the Jacobi mass metric, and the rows of $C$ are
total angular momentum, $\ell_{23}$, and $\ell_{31}$.  This is the optimal
instantaneous energy bound respecting all three torque signs.  If

\[
 C_1={(1-h)^2\over m_1^2}-{1\over p^3}>0,
 \qquad p={r_{23}\over r_{12}},
\]

then the strongest scale-independent bound obtainable from total energy is

\[
 \mathfrak g_{12}-\mathfrak g_{23}+{2U_{\rm sh}C_1\over F}.
\]

It is not sign-definite.  In the complete ordered-right/obtuse cube use
$t=2-\sqrt2+(\sqrt2-1)s$, $u=(\sqrt2-1)v$, and

\[
 r_{23}/r_{12}=1-tw/2,qquad
 r_{31}/r_{12}=1-t+tw/2.
\]

At the exact interior point

\[
 (s,w,v,h)=\left({99\over100},{1\over10^6},
 {99\over100},{1\over10^6}\right)
\]

exact $\mathbb Q(\sqrt2)$ arithmetic gives $C_1>0$ and

\[
 \mathfrak g_{12}-\mathfrak g_{23}+{2U_{\rm sh}C_1\over F}
 =93.2280669052696428\ldots>0.
\]

Taking the overall scale sufficiently small realizes this adverse sign with
the energy $H=-U_0$ and the minimizing velocity.  This is a legitimate
instantaneous state satisfying the ordered right/obtuse shape, $L=0$, total
energy, and torque-sign constraints; it is not asserted to be reachable from
the Burrau brake.  Therefore reachability information encoded in the torque
integrals, or an equivalent history-dependent invariant, is indispensable.
The exact Gram formula and obstruction are regressed in
`tests/test_mutual_distances.py`.

## Static first-return barrier for the torque-rate ratio

**Status:** DISPROVED by an exact ambient state; reachable history remains
essential.

Let

\[
 J=\log {r_{23}^{-3}-r_{12}^{-3}\over
              r_{31}^{-3}-r_{12}^{-3}}.
\]

Since gravity contributes strictly negatively to $J''$ on the ordered
right/obtuse cone, a natural first-return strategy is to suppose $J'$ first
returns to zero and prove $J''<0$ from the current state.  Even after adding
energy, zero angular momentum, and all three pre-syzygy torque signs, that
ambient implication is false.

Take the exact tied parameter $u=2/5$, masses
$(21/29,20/29,1)$, and the strict ordered obtuse shape

\[
 (r_{12},r_{23},r_{31})=\left(1,{39\over40},{1\over30}\right).
\]

In unit-$r_{12}$ Jacobi coordinates set the selected relative velocity
$U=(0,-1)$ and solve the two exact linear equations $L=J'=0$ for the
complementary velocity. Exact elimination gives pair angular momenta

\[
 \left(-1,
 {28914232361390649\over36366761131529200},
 -{122841961770469\over1818338056576460}\right),
\]

which have signs $(-,+,-)$, while the velocity curvature is
$Q_J=8951.51393211\ldots>0$.  At physical scale $r_{12}=1/2$, choosing the
amplitude so that $H=-U_0$ gives

\[
 r_{12}^3J''=10682.0701224264\ldots>0.
\]

All signs and both linear constraints are checked in exact algebraic
arithmetic.  This state is not asserted reachable from the Burrau brake.  It
shows precisely that a barrier proof at $J'=0$ must use the fact that the
velocity and pair angular momenta were accumulated from zero along the
trajectory; current-state inequalities do not suffice.

## Static second-gap sign on the ordered-syzygy face

**Status:** DISPROVED by an exact energy-compatible ambient state.

The first gap has a proved negative acceleration at every ordered syzygy with
the launch torque signs.  The tempting complementary claim

\[
 (r_{23}-r_{31})''>0
\]

is false under the same instantaneous hypotheses, even after imposing the
orientation of a first syzygy crossing.  At

\[
 u={1\over3},\quad(m_1,m_2)=\left({4\over5},{3\over5}\right),\quad
 (r_{12},r_{23},r_{31})=\left(1,{697\over700},{3\over700}\right),
\]

the collinear momentum equations give
$\eta=419/32759\in(0,1)$.  With zero radial velocities and

\[
 \ell_{23}^2={476958362267\over2867548600},
\]

the unique transverse velocities have $P=L=0$, exact energy $-U_0$, pair
angular-momentum signs $(-,+,-)$, and
$\dot\Delta_2/\ell_{23}=-292607/131036<0$.  Nevertheless

\[
 (r_{23}-r_{31})''
 =-{96354167469624287\over1827657180810}<0.
\]

All quantities are exact rationals apart from the harmless algebraic choice
of the positive square root for $\ell_{23}$.  The state is not asserted
brake-reachable.  It proves that the second syzygy-face inequality requires
an accumulated torque-amplitude bound, not merely energy, signs, and local
crossing data.  The sharp remaining form is
$Z<Z_*=(\mathfrak g_{23}-\mathfrak g_{31})/(-C_2)$ whenever $C_2<0$.

## Pointwise inwardness of the critical second-gap amplitude

**Status:** DISPROVED by an exact interior contact state.

It is natural to strengthen the preceding static sign attempt by declaring
$H=Z/Z_*$ and proving $H_s<0$ whenever $H=1$.  This also fails under every
obvious current-state constraint.  At $u=1/3$, take

\[
 (x,y,\eta)=\left({499\over500},{1\over20},{3\over20}\right).
\]

The shape is strict ordered obtuse, since
$1-x^2-y^2=187/125000>0$, and its current and initial torque-rate ratios
satisfy

\[
 {748501\over993887740501}=k<\eta<k(0)={1647\over6272}.
\]

Set $Z=Z_*$ exactly, solve the pair-angular-momentum constraints, choose the
remaining homothetic rate to minimize kinetic energy, and set the physical
scale to

\[
 {717603860876220132499755190629\over
  669041277379938998505911848960}.
\]

This gives exact energy $-U_0$, $P=L=0$, torque signs $(-,+,-)$, and
decreasing normalized area.  Direct exact differentiation of the Newton
vector field gives

\[
 {d\over ds}\log H=50.8829734688\ldots>0.
\]

The sign is an exact positive rational multiple of the square root of a
positive integer, not a floating-point inference.  Thus even the critical
surface points outward at a state satisfying the elementary weighted-history
envelope.  A valid invariant must use more of the brake-generated path than
the current values and inequalities for $(x,y,Z,\eta)$.

## Terminal side-rate signs imply the syzygy amplitude bound

**Status:** DISPROVED ANALYTICALLY as a current-state coercive argument.

At an ordered syzygy put
$D=mn+mq^2+n(1-q)^2$ and $H=n-(m+n)q>0$.  The exact energy decomposition
shows that $Z<Z_J^{\rm syz}$ requires a positive lower bound on

\[
 \mathcal L={R\dot I^2\over4I}+{mnq_s^2\over D}.
\]

One might hope that decreasing $r_{31}$, increasing $r_{23}-r_{31}$, and
$\dot I<0$ provide it.  They do not.  Since

\[
 2D-H(1-2q)=2mn+(m-n)q+n>0,
\]

choose $(1-2q)/2<c<D/H$ and set
$\sigma=-\varepsilon$, $q_s=-c\varepsilon$.  All three desired derivatives
then have strict sign, but $\mathcal L=O(\varepsilon^2)\to0$.  If $R<R_J$,
the energy-determined transverse amplitude consequently exceeds $Z_J$ for
small enough $\varepsilon$.  These are ambient states, not brake-reachable
ones.  The smallest viable repair must transport a quantitative velocity or
action bound from the initial brake; qualitative cone monotonicity cannot
close the terminal amplitude estimate.

## Sequential evaluation of the equal-mass syzygy threshold

**Status:** DISPROVED as an endpoint-continuity shortcut.

The corner $(v,z)=(1,1)$ of the tied syzygy square is a genuine $0/0$
singularity.  Taking $z\uparrow1$ at fixed $v<1$ and then
$v\uparrow1$ gives

\[
 R_J\longrightarrow {11+2\sqrt2\over55}=0.2514259\ldots,
\]

which lies below the endpoint first-syzygy scale
$R_*=0.3059891\ldots$.  It is tempting to infer that $R>R_J$ closes the
amplitude estimate near the endpoint.  This inference is false.  Along
$v=1-\varepsilon$, $z=1-\lambda\varepsilon$ the exact limit is

\[
 {R_0+\kappa\lambda R_\infty\over1+\kappa\lambda},
 \qquad \kappa={28-3\sqrt2\over11},
\]

and the validated dynamical tangent has $\lambda_*>18$.  Its limiting
critical scale is about $0.733$, well above $R_*$.  Thus the scale-only
argument remains unavailable.  The repair is the independent exact bound
$Z_J^{\rm syz}>1$ together with the validated endpoint amplitude $Z_*<1$;
the order of limits must never be interchanged.

## Using the fixed endpoint escape section to bridge the middle interval

**Status:** DISPROVED as a broad continuation shortcut by ordinary numerical
evidence; the local theorem remains valid.

The punctured near-isosceles theorem reaches the strict binary--escaper cone
at the fixed comparison section (\sigma=7) with (\eta=4).  One might hope
that the same section and certificate persist far enough down the tied curve
to overlap the compact middle regime.  A deterministic DOP853 scout shows
that this mechanism loses its margin very rapidly:

| (v) | selected crossings before (\sigma=7) | radial margin | result |
|---:|---:|---:|---|
| (0.9999) | 4 | (0.0904\ldots) | fixed certificate passes |
| (0.999) | 4 | (-1.155\ldots) | fixed certificate fails |
| (0.99) | 2 | (-19.037\ldots) | different close-encounter regime |

At (v=0.999), all sampled finite-arc brake residuals remain positive; the
failure is specifically the terminal radial-energy inequality, not evidence
for a brake.  At (v=0.99), an unselected squared distance reaches about
(1.9\times10^{-6}), so the orbit has already reorganized before the fixed
section.  These are **ORDINARY NUMERICAL EVIDENCE**, not validated parameter
boundaries.

Thus an effective CAPD interval near (v=1) may quantify the existential
theorem, but it is unlikely to bridge the middle interval.  Beyond the local
window one must adapt the terminal section and encounter itinerary, or use a
global brake obstruction.  Failure of this particular fixed section does not
imply periodicity or failure of some later escape certificate.

## One physical-coordinate interval tube across the middle close encounters

**Status:** DISPROVED as a scalable validation architecture; the dynamical
claim itself is not disproved.

Direct Cartesian interval propagation of the tied family near $u=0.29$
retains acceptable widths early, but dependency growth becomes prohibitive at
the successive close encounters. A single direct pair--13 Levi--Civita box
improves the first passage, yet boxes of widths $10^{-4}$ and larger still
wrap during the close pair--23 passage near $t=1.05$. Reducing the parameter
width without retaining its correlation only postpones the same failure.

The successful repair is structural: represent the family by a $C^1$
mean-value graph, propagate its parameter tangent through oriented Poincare
maps, and switch exactly from the pair--13 to the pair--23 Levi--Civita tree
at $t=1$. This certifies the first maximum on a width-$10^{-5}$ interval.
It does not show that arbitrarily wide tiles will pass, nor does it control
later maxima. Future continuation should tile graph enclosures and adapt the
selected binary chart rather than return to one large physical box.

## One persistent doubleton after the pair--23 to pair--13 return switch

**Status:** DISPROVED as a complete middle-bridge architecture; the certified
partial tube remains valid.

On the real tile $u\in[0.29,0.2900001]$, retaining one CAPD $C^1$ doubleton
through the return switch at $t=1.75$ rigorously crosses the second close
passage and the second strict inertia minimum.  Eliminating the dependent
selected-pair energy through the exact identity

\[
 h={2|z|^2-M_{13}\over |w|^2}
\]

reduces the incoming pair--13 hull from about $0.08$ to $0.04$.  The tube
then crosses the outgoing sections $w_r=-0.1,-0.2,-0.3,-0.4$, with strict
collision separation and the required $J$ or convexity signs.  At the next
$w_r=-0.5$ leg, enclosure widths in $z$ and $P$ make the section speed
contain zero; the Poincare map therefore fails closed.  This occurs even on
a near-point parameter tile, so parameter subdivision alone is not the
repair.

The next architecture should rebuild a one-parameter mean-value graph at
transverse sections, keeping the exact algebraic energy elimination from the
moment of the chart switch.  A success must still audit every complete tube;
the returned section image by itself is not enough.
