# End-of-run report — 2026-08-23

## Outcome

**MAJOR PARTIAL THEOREM (LEVEL D + LEVEL E); FULL CONJECTURE UNRESOLVED.**

Neither the rational Pythagorean--Burrau conjecture nor the stronger real
conjecture has been proved. No exact real second-brake intersection and no
rational counterexample candidate were found.

The strongest theorem remains the unconditional skinny result: infinitely
many open real Euclid-parameter intervals are nonperiodic, hence infinitely
many primitive Pythagorean triples satisfy the conjecture. In the explicit
primitive family

\[
 (4n^2-1,4n,4n^2+1),
\]

a positive-lower-density subset is proved nonperiodic by a combination of
exact phase asymptotics, equidistribution, analytic matching, and validated
restricted transversality.

This run additionally proved a Level-E structural theorem at the singular
triple-collision endpoint: the entire shrinking finite-mass boundary layer
reduces to a single projective parameter in a universal planar massless
restricted problem.

## New exact theorems

### Tight-pair Hill barrier

At every full brake in the normalized skinny problem, the late-scaled heavy
pair separation must satisfy

\[
 |R|>{1-B^2\over1+B^2-B^4}=1-2B^2+O(B^4).
\]

This follows from energy conservation and positivity of the two remaining
pair potentials. It excludes a brake throughout every absolute near-triple
tube, including the previously unresolved endpoint boundary layer while the
orbit remains in that tube. It does not exclude a brake after re-expansion.

### Finite-mass joint blow-up

Let $H_B$ and $T_B$ be parity-adapted nonlinear unstable amplitudes relative
to the exact finite-$B$ collision-stable manifold. Then

\[
 {T_B\over B}\longrightarrow-{\widehat A_-\over2}\ne0.
\]

The two positive McGehee exponents are

\[
 \mu={1+\sqrt{19}\over4},\qquad
 \tau={1+\sqrt7\over4},\qquad
 1<{\mu\over\tau}<2.
\]

With

\[
 \rho_T=|T_B|^{1/\tau},\qquad
 \kappa_B={H_B\over|T_B|^{\mu/\tau}},
\]

every endpoint sequence has a subsequence with one of three limits:

1. finite $\kappa$, giving one orbit $\mathscr U_\kappa$ of the planar
   massless restricted system;
2. $\kappa=+\infty$, giving the upper rectilinear exit;
3. $\kappa=-\infty$, giving the lower rectilinear exit.

The finite limit satisfies

\[
 \mathcal R_{ss}=-2\Phi(\mathcal R),\qquad
 \mathcal Z_{ss}
 =-\Phi(\mathcal Z+\mathcal R/2)-\Phi(\mathcal Z-\mathcal R/2).
\]

The proof includes a parameter-uniform two-mode inclination estimate,
finite-exponent drift over the logarithmic dwell, zero-angular-momentum
reconstruction, and the classical-collision/Levi--Civita dichotomy.

The decisive parity repair compares with the auxiliary equal-heavy family
$(1,B,1)$. Since $A(B)-1=O(B^2)$, the odd stable-foliation and projector
correction is $O(B^2)$ rather than $O(B)$. The exact equilateral offset is

\[
 {Z_x\over R}=-{B^2\over2(1+A)^2}.
\]

Three independent adversarial passes endorsed the repaired theorem.

### Planar logarithmic shape flow

On a zero-energy radial-binary half, write

\[
 R=9^{1/3}t^{2/3}e_x,\qquad
 Z=9^{1/3}t^{2/3}w(\zeta),\qquad \zeta=\log t.
\]

Then

\[
 w_{\zeta\zeta}+{1\over3}w_\zeta=\nabla W(w),
\]

\[
 W(x,y)={1\over9}\left(
 x^2+y^2+{1\over|w+e_x/2|}+{1\over|w-e_x/2|}
 \right).
\]

The exact shape energy and angular torque are

\[
 \mathcal E_\zeta=-{|w_\zeta|^2\over3},
\]

\[
 \Lambda_\zeta+{\Lambda\over3}=-xyK(x,y),\qquad
 K={1\over12}\int_{-1}^{1}
 (x^2+y^2+1/4+\sigma x)^{-5/2}\,d\sigma>0.
\]

The potential has the sharp global minimum

\[
 W\ge{11\over36},
\]

with equality only at the two equilateral shapes. Consequently:

- there is no nonconstant periodic logarithmic shape orbit;
- there is no nonconstant equilateral-to-equilateral shape connection;
- a nonhomothetic equilateral-stable orbit has
  $w_\zeta\ne0$ at every finite collision-free point.

The last assertion concerns shape velocity, not physical velocity.
A LaSalle alpha-limit argument additionally proves that such an orbit cannot
remain in a compact collision-free region when continued away from its
equilateral end. It must approach a collision boundary or become unbounded in
shape/shape velocity; compact recurrent capture is excluded.

On the outer strip,

\[
 |y|\ge{\sqrt3\over2},
\]

one has the exact convexity bound

\[
 W_{xx}\ge {1\over9}\left({7\over4}-{8\over3\sqrt3}\right)>0.
\]

This yields a fixed sign for the transverse coordinate, its logarithmic
derivative, and the shape angular momentum on every stable tail contained in
the strip.

Global outer-strip invariance is false. At $\kappa=0$ the stable orbit bends
into the inner strip with exact coefficient

\[
 {2\sqrt{21}-5\sqrt3\over4}>0.
\]

This failed shortcut is recorded explicitly.

The complete lower-equilateral stable-manifold jet is now known through total
degree four. In tail variables $p=Te^{-a_T\zeta}$ and
$\nu=He^{-a_L\zeta}$ it is
\[
 x=p+Ap\nu+Bp^3+Cp\nu^2+O_4,
 \qquad
 q=\nu+Kp^2+D\nu^2+Ep^2\nu+F\nu^3+O_4,
\]
with all seven cubic coefficients explicit algebraic numbers, followed by
five explicit quartic coefficients. Exact symbolic substitution annihilates
the ODE residual through degree four.

The former $O_5$ obligation is now closed analytically. In the weighted
power-series norm, a contraction with homological gap $>17/30$, residual
bound $13/80^5$, and contraction factor $<1/10$ proves the unique normalized
stable graph $P=P_4+E$ on

\[
 |p|\le {1\over200},\qquad |\nu|\le {1\over2500},
 \qquad \|E\|<{1\over125000000}.
\]

At half radii, $\|E\|<1/4000000000$ and
$\|\mathcal DE\|<1/800000000$, with explicit $\kappa$-tangent bounds. These
estimates apply uniformly to $5/4\le\kappa\le13/10$ at $\zeta\ge10$ and
rigorously initialize the collision shoot.

### Forced light-heavy Levi--Civita chart

For either heavy primary, relative position
$q=Z-\epsilon R/2$ satisfies a forced Kepler equation with analytic external
field at $q=0$. Here $t=|\theta-t_c|$ is the radial clock, so
$dt/d\theta=-1$ on the incoming half and $+1$ on the outgoing half. The exact
complex regularization

\[
 q=u^2,\qquad dt=|u|^2d\sigma
\]

gives

\[
 u_\sigma=v,\qquad
 v_\sigma={h\over2}u+{|u|^2\bar u\over2}G,
\]

\[
 h_\sigma=2\operatorname{Re}(uv\bar G),\qquad
 t_\sigma=|u|^2.
\]

It preserves

\[
 2|v|^2-1-h|u|^2=0
\]

and makes an isolated collision the square shooting residual

\[
 (\operatorname{Re}u(\kappa,\sigma),
   \operatorname{Im}u(\kappa,\sigma))=0.
\]

This supplies a rigorous interval-Newton formulation for an apparent
collision zero. A deterministic regularized ordinary shoot gives
\[
 \kappa\approx1.2679351755,
 \quad \sigma\approx-1.07124851,
 \quad \det(\partial_\kappa u,v)\approx-3.45305779,
\]
with $|u|\approx4.6\times10^{-12}$ and the LC constraint at roundoff. The
displayed root decimals remain ordinary evidence only. A transverse validated
zero would separate the nearby continuations locally; existence,
transversality, and exclusion of other collision zeros are not yet validated.
All physical velocity and angular signs include the factor
$\eta=dt/d\theta$; in particular the incoming LC orientation is backward in
physical time.
The determinant is not merely numerical conditioning: exactly
\[
 q\times q_t=2\det(u,v),\qquad
 \partial_\kappa(q\times q_t)|_{u=0}=2\det D\mathcal F.
\]
Consequently a transverse validation would also certify a linearly changing
signed impact parameter across the local collision branch.
More precisely, the LC implicit-function theorem proves the conditional local
normal form
\[
 r_{\min,\mathrm{local}}
 =2(\det D\mathcal F)^2(\kappa-\kappa_c)^2
  +O(|\kappa-\kappa_c|^3).
\]
Thus validating one transverse root automatically proves local avoidance on
both punctured sides, while leaving other collision times as a separate
global obligation.

### Validated finite collision-shooting stage

For the full parameter interval

\[
 1.26793\le\kappa\le1.26794,
\]

pinned CAPD 6.1.0 native-interval integration carries the analytic tail box
from $\zeta=10$ to $\zeta=0.3$, converts it into the selected-primary LC
chart, and propagates the reversed LC flow for the exact duration
$1071249/1000000$. On every accepted LC step it proves $t>1$, $R>2$, and
distance to the other primary greater than one. At the terminal time,

\[
 -0.017807<\operatorname{Re}u<0.016661,
 \qquad
 -0.003953<\operatorname{Im}u<0.004019.
\]

This is a **VALIDATED NUMERICAL RESULT** showing that the rigorous tail reaches
the candidate neighborhood inside one analytic chart. It is not a collision
root certificate: the interval coordinate conversion discarded the
$\kappa$ correlation, making the final box too wide for interval Newton.
The remaining local repair is to retain $\kappa$ as an affine doubleton
direction through that conversion and propagate its tangent.

## Endpoint status

### Skinny endpoint $u\to0$

Proved:

- the first tight-pair encounter is collision-free for all sufficiently small
  positive $B$;
- its miss distance and angular momentum have exact leading orders
  $B^{11}$ and $B^{11/2}$;
- the early collision-like cycle train, incoming parabolic tail, and divided
  transverse state match the restricted problem;
- a fixed escape window transfers to infinitely many finite-$B$ intervals;
- a positive-lower-density subset of an explicit primitive family is
  nonperiodic;
- every first outer turn in the accumulating parabolic layer has nonzero
  normalized angular momentum;
- the certified triple-endpoint local branch has positive transverse transfer;
- the finite-mass wedge, Hill tube, and full joint two-mode scaling are
  structurally controlled.

Open:

- global classification of $\mathscr U_\kappa$ through the finite inner shape
  strip and all light-heavy collision branches;
- its outgoing scattering sign and attachment across the common LC section;
- later central encounters after the first outer return;
- the exact finite-$B$ separatrix phase and later-turn dynamics;
- remote captured components outside the certified local endpoint branch.

### Isosceles-right endpoint $u=\sqrt2-1$

The exact symmetric trajectory is proved to reach a finite collision and has
no second brake before it. The endpoint is irrational and therefore not an
integer counterexample. The transverse unfolding for $A\ne B$ remains open;
no theorem yet excludes a second-brake branch born under symmetry breaking.

## Counterexample and periodic-family audit

No exact catalog counterexample was found.

The closest threat remains the Li--Liao $F_{30}$ family on the
$3{:}4{:}5$ mass slice. Its published periodic point is not the tied right
triangle. Ordinary continuation found the horizontal and vertical matching
conditions crossing zero at different mass parameters; the smallest sampled
combined gap was about $0.00369$. This is ordinary numerical evidence only,
not validated nonintersection.

No real exact intersection and no rational candidate are known.

## Cardinality and arithmetic

The cardinality heuristic remains only a heuristic. No inference in the proof
uses countability, measure zero, generic transversality, or presumed
irrationality of analytic zeros.

Arithmetic has earned one genuine role: the explicit skinny phase clock is
equidistributed, which turns a proved open dynamical escape window into a
positive-density set of rational Euclid parameters. No arithmetic theorem
currently excludes all rational parameters. If a real periodic intersection
is eventually found, a new exact arithmetic bridge would still be required.

## Remaining top-level proof obligations

1. Prove a global obstruction for every real parameter, or classify every
   real zero of the three-component brake residual.
2. Classify the one-parameter planar family $\mathscr U_\kappa$, including
   inner-strip transitions, collision branches, and a common outgoing
   scattering scalar. Compact collision-free backward capture is already
   excluded.
3. Continue the proved nonzero skinny angular momentum through the compact
   second and later central-encounter maps.
4. Control the exact finite-$B$ separatrix displacement and the accumulating
   later-turn layer.
5. Classify remote captured components not attached to the certified local
   triple endpoint.
6. Prove a symmetry-breaking theorem near the isosceles-right collision
   endpoint.
7. Bridge the compact middle parameter interval, including arbitrarily close
   but noncolliding encounters.
8. If real periodic parameters survive, derive and prove an exact arithmetic
   condition excluding rational $u$.
9. If degree or continuation is used, classify entry of zeros through
   collision, escape, infinite return time, and both parameter endpoints.
10. Upgrade any claimed intersection with a known periodic family to
    validated continuation; decimal proximity is irrelevant.

The detailed lemma-level list is maintained in PROOF_OBLIGATIONS.md.

## Failed routes recorded

- global positivity of the Pythagorean defect;
- globally negative tight-pair torque;
- a uniform strict-escape statement in the restricted plunge limit;
- a naive whole-line phase Melnikov integral without a phase gauge;
- raw monopole phase as the exact fixed-section gauge;
- ordinary continuity through the logarithmically long finite-mass endpoint;
- global invariance of the planar outer strip;
- global pointwise nonvanishing of planar shape angular momentum (ordinary
  evidence shows a zero after a very close inner-strip passage).

Each failure has an explicit counterexample, exact obstruction, or first
missing lemma in FAILED_ROUTES.md.

## Verification and reproduction

At the end of this run:

    .venv/bin/pytest -q -p no:cacheprovider
    .venv/bin/ruff check --no-cache .
    .venv/bin/python -m scripts.derive_restricted_scattering
    .venv/bin/python -m scripts.probe_planar_joint_shape
    .venv/bin/python -m scripts.probe_planar_light_collision_lc
    tectonic -o /private/tmp/pythagorean-paper-build paper/main.tex
    bash scripts/run_capd_planar_light_collision_shape.sh \
      /private/tmp/pythagorean-capd \
      /private/tmp/pythagorean-capd/build-native

Results before this report:

- 91 tests passed;
- lint passed;
- the paper built successfully;
- the only TeX diagnostic was the pre-existing 0.42 pt overfull box.

The pinned CAPD 6.1.0 certificates and replay commands are documented in the
computer-assisted proof notes and repository README.

## Highest-leverage next action

Preserve the affine $\kappa$ direction from the analytic stable-tail box
through the shape-to-LC coordinate change, integrate the corresponding
variational state, and apply interval Newton to the square collision residual
near $\kappa=1.2679351755$. A transverse certificate would validate that
collision and its signed impact-parameter crossing. Then
exclude other collision zeros, define $\mathscr S(\kappa)$ componentwise, and prove nonvanishing
on each collision-free component with certified endpoint limits. This is now
a one-parameter compact transition problem rather than an uncontrolled
two-scale boundary layer.
