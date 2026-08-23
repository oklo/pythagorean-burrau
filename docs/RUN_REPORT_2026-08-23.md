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

Independently, infinitely many exact real tied parameters are now proved to
end in classical collision.  This second result concerns isolated real roots
and has no rationality conclusion.

The first certified planar collision boundary is now also globally classified
in a local normalized cusp: its regularized limiting continuation escapes,
and every sufficiently small compatible positive-mass member either collides
classically or escapes.  This closes both collision-free sides near that
boundary but does not yet cover the full projective parameter line.

This run additionally proved a Level-E structural theorem at the singular
triple-collision endpoint: the entire shrinking finite-mass boundary layer
reduces to a single projective parameter in a universal planar massless
restricted problem. It has now also located and rigorously validated one
transverse light--heavy collision parameter in that planar limiting family.
The exact phase winding and normalized collision graph further imply that
infinitely many distinct real tied parameters accumulating at the skinny
endpoint have a finite-time classical collision.  No sampled collision
parameter is proved rational.

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
displayed decimals were ordinary evidence at this stage. The correlated
certificate below subsequently validates existence and transversality; only
exclusion of other collision zeros remains open.
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

### Validated transverse planar collision root

That repair is now complete. A single 13-dimensional CAPD `C1Rect2Set`
retains the affine directions through the reversed shape flow, a unit-time
nonlinear LC construction flow, and the reversed forced-LC flow. Starting at
$\zeta=15$ gives the rigorous degree-five tail scaling factor

\[
 \lambda^5,
 \qquad
 \lambda=\max\{400e^{-15a_T},6500e^{-15a_L}\}<0.04403.
\]

Strict interval-Newton inclusion proves a unique root in the explicit box and
sharpens it to

\[
 1.2679351752<\kappa_c<1.2679351759,
 \qquad
 -1.0712485063<\sigma_c<-1.0712485051.
\]

The increasing-$\sigma$ determinant satisfies

\[
 -3.52212<\det(\partial_\kappa u,v)<-3.38401.
\]

Whole-step checks prove both shape-primary distances positive, fix the
square-root lift with $y>0$ and $u_r,u_i>0$, and retain $t>1$, $R>2$, and
other-primary distance greater than one throughout the LC segment. Two
independent adversarial audits replayed and endorsed the certificate. This is
**PROVED BY COMPUTER-ASSISTED ARGUMENT** for a collision in the massless
planar limit. It is not a real second-brake intersection, a finite-mass
Pythagorean orbit, or a counterexample.

### Positive-mass persistence of the collision boundary

For the selected primary, the exact finite-mass Jacobi coordinate

\[
 q=Z-{A\over1+A}R
\]

satisfies

\[
 q_{\theta\theta}=-(1+B)\Phi(q)
 +A\{\Phi(R)-\Phi(q+R)\}.
\]

The corresponding LC constraint is

\[
 2|v|^2-(1+B)-h|u|^2=0,
\]

so the regular collision speed is \(|v|^2=(1+B)/2\).  The heavy coordinate
must be adapted as well: the exact choice
\[
 Q=R+{B\over1+B}q
\]
cancels the singular $B\Phi(q)$ force in the $R$ equation.  At $B=0$, $Q=R$,
so the validated separation margins persist.  A $C^1$ chart on one fixed
constrained incoming section, the collision-adapted LC flow, and the certified
nonsingular limiting Jacobian prove that the root persists as a unique
transverse collision boundary for all sufficiently small positive masses and
compatible section-state perturbations.  At fixed perturbation,

\[
 r_{\min,\mathrm{local}}
 ={2D_{B,\delta}^2\over1+B}
  (\widehat\kappa-\widehat\kappa_c)^2
  +O(|\widehat\kappa-\widehat\kappa_c|^3).
\]

This is a structural persistence theorem, not a collision theorem for the
tied Pythagorean curve.

### Differentiated inclination and normalized collision graph

The missing parameter-tangent theorem is now proved.  For
\(H=\kappa|T|^{\mu/\tau}\), choose a common weighted-tail exponent

\[
 {\mu\over2}<\omega<\tau.
\]

The positive-mass nonlinear unstable shadow is a uniformly \(C^1_\kappa\)
Lyapunov--Perron fixed point in this space because
\(2\omega-\mu_B>0\).  The actual bounded stable entrance datum is not put in
that half-line norm; instead uniform \(C^1\) stable holonomy compares the
actual orbit and its tangent with the shadow at one fixed tail section.
Exponent drift costs \(O(B|\log|T||)\), and the scaled energy costs
\(O(\rho_T|E|)\).  Compact variational flow, fixed-axis reconstruction, and
the scaled \(Q\)-adapted LC chart then propagate state-and-tangent convergence
through the limiting selected collision.

The certified root therefore continues as a unique graph

\[
 \kappa_c(B,T,S,\Xi)
\]

through every admissible cusp with
\(B|\log|T||+B+|T|^{2-\mu/\tau}+e^{-cL_T}
+\|\widehat\Xi\|\to0\).  For the tied endpoint state the remaining local
condition is exactly

\[
 \boxed{\Delta_{\rm intr}(B)=
 \kappa_B-\kappa_c(B,T_B,S_B,\Xi_B).}
\]

Two independent adversarial rereads endorsed the repaired argument.  The
differentiated inclination theorem is **PROVED ANALYTICALLY** and the graph
is **PROVED BY COMPUTER-ASSISTED ARGUMENT** through its certified base root.
No componentwise sign or zero theorem for \(\Delta_{\rm intr}\) follows from
the local graph alone.

### Infinitely many exact real tied collisions

There is nevertheless a global phase-sampling consequence.  Let
\(H_0(\chi)\) be the signed longitudinal amplitude of the restricted incoming
parabolic curve near its certified transverse intersection with the
collision-stable curve.  Fixed compact intercept arcs on its two sides have
opposite strict \(H_0\)-signs.  The exact clock

\[
 \Phi_{\rm ref}'(B)=-{3\pi\over2}B^{-5/2}(1+o(1))
\]

produces a disjoint real parameter bracket crossing those arcs in every
sufficiently late winding.  If any parameter in a bracket collides before the
selected late chart, the bracket already contains a classical collision.
Otherwise uniform incoming-tail convergence transfers the endpoint signs and
continuity supplies a segment from \(H=0\) to
\(H=B^{p/2}\), \(p=\mu/\tau\).

Every sequence in that segment has \(H\to0\), so local uniqueness of the
restricted endpoint and the joint blow-up theorem give uniformly
\(T/B\to\Theta_*\ne0\) and entry into the normalized collision-graph cusp.
The continuous scalar

\[
 G(B)=H_B-|T_B|^p\kappa_c(B,T_B,S_B,\Xi_B)
\]

is negative at the zero endpoint and positive at the other because
\(B^{p/2}\gg B^p\).  Its IVT root is an exact collision of the actual tied
positive-mass trajectory.  Pairwise disjoint clock brackets therefore give
infinitely many distinct real collision parameters tending to zero.  Two
independent adversarial audits endorsed every compactness, continuity, and
classical-collision step.  This is **PROVED BY COMPUTER-ASSISTED ARGUMENT**
through the two certified transverse roots.  Isolated IVT roots need not be
rational, so this theorem does not enlarge the proved integer subfamily.

### Validated collision--ejection escape cusp

The exact interval-Newton root has now been followed beyond its limiting
light--heavy collision without assigning physical meaning to a
positive-mass collision continuation.  The selected-pair LC flow reaches
\(S=61/25\) with the other primary separated.  Reconstruction of the
restricted outer state and the signed bridge
\[
 \lambda=\sqrt[3]t,\qquad
 \lambda_\eta=-1,\qquad
 Z_\eta=-3\lambda^2Z_t
\]
cross the prescribed heavy-binary collision analytically.  CAPD proves both
light--primary squared distances exceed \(0.89\) throughout the bridge.  At
the outgoing section, the restricted escape comparison has strict margin
\(>0.58\).

Finite-time openness is insufficient for positive light mass, because its
tidal work on the heavy pair accumulates forever.  A new exact Jacobi lemma
closes this gap.  With inner separation \(r\), outer radius \(\rho\), outer
gap \(w=\rho-r\), and inner specific energy \(e\),
\[
 |\ddot y|\le{\mathcal M\over w^2},\qquad
 |\dot e|\le{2m_c r|\dot x|\over w^3}.
\]
If \(e<\epsilon\), the inner pair lies below a linear envelope
\(r_0+v_bt\).  A strict terminal speed inequality makes \(\rho\) outrun this
envelope by \(ct\), while the remaining tidal-energy integral is finite and
uniform.  CAPD validates the limiting full-pair margin with
\(\epsilon=1/100\), \(c=3/2\) by more than \(0.69\); the energy correction is
\(O(B)\) in the Newtonian-scaled terminal coordinates.  Therefore every
sufficiently small compatible positive-mass member in this local cusp either
has a true classical collision or the light body escapes.  Every
collision-free member is nonperiodic.

The LC signs, heavy-binary bridge, exact mass constants, simultaneous
bootstrap, Newtonian scaling, and finite-mass transfer were independently
audited by three adversarial passes.  The restricted continuation and strict
margins are **PROVED BY COMPUTER-ASSISTED ARGUMENT**; the hierarchical escape
lemma is **PROVED ANALYTICALLY**.

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
- infinitely many distinct real tied parameters have an exact finite-time
  classical collision, although none is proved rational;
- the first certified planar collision boundary and both local
  collision-free sides satisfy a finite-mass collision-or-escape theorem;
- every first outer turn in the accumulating parabolic layer has nonzero
  normalized angular momentum;
- the certified triple-endpoint local branch has positive transverse transfer;
- the finite-mass wedge, Hill tube, and full joint two-mode scaling are
  structurally controlled.

Open:

- global classification of $\mathscr U_\kappa$ through the finite inner shape
  strip and all light-heavy collision branches;
- outgoing classification beyond the certified first-root neighborhood and
  across every additional collision boundary;
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
The new collision-sampling roots are isolated real points; rational density
and phase equidistribution do not imply that any one of them is rational.

## Remaining top-level proof obligations

1. Prove a global obstruction for every real parameter, or classify every
   real zero of the three-component brake residual.
2. Classify the one-parameter planar family $\mathscr U_\kappa$: use the first
   certified collision-or-escape cusp as the initial component, exclude or
   certify all other collision zeros, and construct terminal certificates on
   every remaining collision-free component. Compact collision-free backward
   capture is already excluded.  The phase-cycle theorem forces infinitely
   many real tied collisions but does not identify whether a particular cycle
   hits this selected graph or contains an earlier collision.
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
    bash scripts/run_capd_planar_light_collision_newton.sh \
      /private/tmp/pythagorean-capd \
      /private/tmp/pythagorean-capd/build-native

Results at this checkpoint:

- 92 tests passed;
- lint passed;
- the paper built successfully;
- the only TeX diagnostic was the pre-existing 0.42 pt overfull box.

The pinned CAPD 6.1.0 certificates and replay commands are documented in the
computer-assisted proof notes and repository README.

## Highest-leverage next action

Extend the new collision-or-escape certificate from its first narrow
\(\kappa\)-box across the adjacent compact planar components.  Locate and
certify every additional collision zero, propagate each collision-free
component to a common terminal section, and fire either the hierarchical
escape cone or a nonzero brake scalar.  The long-dwell derivative bridge and
the first boundary's infinite-time outgoing classification are now closed.
For the tied family, the parallel highest-leverage question remains a
componentwise sign/zero theorem for \(\Delta_{\rm intr}(B)\), upgrading the
cyclewise collision dichotomy to a classified root sequence.  This is a
one-parameter compact transition problem rather than an uncontrolled
two-scale boundary layer.
