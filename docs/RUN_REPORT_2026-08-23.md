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
- global invariance of the planar outer strip.

Each failure has an explicit counterexample, exact obstruction, or first
missing lemma in FAILED_ROUTES.md.

## Verification and reproduction

At commit f403704 and its immediate report update:

    .venv/bin/pytest -q -p no:cacheprovider
    .venv/bin/ruff check --no-cache .
    .venv/bin/python -m scripts.derive_restricted_scattering
    tectonic -o /private/tmp/pythagorean-paper-build paper/main.tex

Results before this report:

- 87 tests passed;
- lint passed;
- the paper built successfully;
- the only TeX diagnostic was the pre-existing 0.42 pt overfull box.

The pinned CAPD 6.1.0 certificates and replay commands are documented in the
computer-assisted proof notes and repository README.

## Highest-leverage next action

Construct a collision-regularized Poincare transition map for the planar
family across the finite inner strip $|y|<\sqrt3/2$, using the exact global
Lyapunov inequality, the factorized torque, and the signed outer-strip entry
data. The target is a rigorously defined scalar $\mathscr S(\kappa)$ with a
uniform nonzero sign on every collision-free component and certified endpoint
limits. This is now a one-parameter compact transition problem rather than an
uncontrolled two-scale boundary layer.
