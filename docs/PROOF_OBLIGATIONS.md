# Proof obligations

## Main theorem

**Statement.**  For every rational $u\in(0,1)$, the normalized classical
solution has no positive collision-free time with $\mathcal B(u,t)=0$.

**Status:** CONJECTURAL.

Indispensable unresolved obligations:

1. Produce a global dynamical obstruction, or classify every real zero of the
   brake residual.  Initial Taylor signs and catalog gaps do not suffice.
2. Cover arbitrarily close binary encounters without declaring them collisions.
3. Control both singular regimes: loss of uniformity as $u\to0$ and the
   symmetry rank change at $u=\sqrt2-1$.
4. If real zeros exist, establish an exact arithmetic bridge excluding rational
   parameters; analyticity alone is irrelevant.
5. If continuation/degree is used, classify every way zeros can enter through
   collision, escape, infinite return time, or the parameter endpoints.
6. If the integrated-force route is used, prove a genuine global projection or
   cancellation inequality; positivity only at the initial instant is local.

Smallest mandatory falsification tests: $u=1/3$ (exact $4{:}3{:}5$, near the
published Li--Liao $F_{30}$ orbit), $u=1/2$ in the opposite ordering, small
$u$, and perturbations from the real isosceles endpoint.

## Candidate invariant: Pythagorean defect

**Desired lemma.**  Starting at the tied right triangle, $D(t)>0$ at every
positive collision-free time.

**Status:** DISPROVED as a viable candidate by converged ORDINARY NUMERICAL
EVIDENCE at $u=1/3$.  Only $D''(0)>0$ is proved analytically.  A validated
enclosure of the later negative value would make the falsification rigorous,
but no main-theorem step depends on doing so.

## Brake-to-syzygy route

Needed lemmas: existence and regularity of the first-syzygy map uniformly on a
chosen parameter interval; a signed image separation from the classical
second-brake locus; endpoint limits; and proof that later evolution cannot
undo the separation.  Moeckel--Montgomery--Venturelli's regularized collision
orbit cannot itself settle this classical collision-free problem.

## Endpoint route

For $u\to0$, the first-encounter, pre-plunge, and incoming-tail matching
theorems are proved. A fixed-margin restricted escape arc transfers to
infinitely many open real parameter intervals on which every orbit either
collides classically before section reach or satisfies the terminal
escape-or-collision certificate. This proves an infinite primitive
Pythagorean subfamily. The remaining skinny obligation is to classify the
intervening captured phase windows and the separatrix phases; escape/capture
classification alone does not settle all sufficiently small $u$. At
$u=\sqrt2-1$, the exact
trajectory is now proved to have monotone shrinking half-base and finite
collision.  The remaining obligation is a regularized transverse analysis of
how that collision unfolds when $A\ne B$ and whether any second-brake branch
can emerge.

The full skinny matching obligation through a fixed incoming restricted
section is now closed. PREPLUNGE_MATCHING.md controls the
$O(B^{-3/2})$ early cycle train to $\rho=B^\alpha$ for every
$0<\alpha<1/6$. INCOMING_TAIL.md then proves, in one common LC section chart,
\[
\operatorname{dist}\!\left(S_B(Y_0),
\Gamma^-_{Y_0}(\Phi_{\rm ref}(B))\right)=o(1),
\]
or an earlier classical collision has already excluded periodicity. The proof
retains the exact finite-$B$ intercept until fixed radius, includes the
restricted quadrupole flight correction, and uses a weighted transverse
uniqueness lemma at parabolic infinity.

The gauge-free restricted construction proves
\[
V_u'(0)-V_s'(0)=2V_u'(0)\ne0.
\]
Together with the completed matching and terminal transfer, this gives the
Level-D open escape intervals. The remaining task is to exclude a second
brake for phases on the captured side and to classify exact separatrix phases.

Restricted transversality is closed. CAPD interval Taylor integration proves
$h'(\pi/4)>14/625$, while the compactified time-$\pi$ map satisfies
McGehee's sector hypotheses. Tangents to its fixed-phase stable curve contract;
under a hypothetical tangency, $h=z'-\eta_{\rm pin}$ would be such a tangent,
but the validated sign forces it to grow. Uniform matching and terminal
transfer are now closed, so infinitely many open terminal windows containing
rational Euclid parameters are an unconditional Level-D theorem. Remaining
finite-$B$ obligations are persistence and signed displacement of the exact
separatrix and exclusion of second brakes throughout the captured branches.

The endpoint arithmetic is now stronger than rational density: an exact
van-der-Corput/Weyl argument gives a positive-lower-density nonperiodic subset
of $(4n^2-1,4n,4n^2+1)$. It still cannot name the first certified member,
because the escape arc and the finite-$B$ threshold are non-effective. The
same equidistribution visits compact finite-turn arcs with positive density,
so phase sampling alone cannot close the remaining post-turn obligation.

## Adversarial checklist

Every promoted lemma must be checked for hidden genericity; vector-valued
mean-value misuse; rational-density fallacies; unlabelled/rotated returns;
near-collision substitution; nearby-orbit substitution; loss of endpoint
uniformity; extrapolation of a local sign; and conversion of finite computation
into an infinite claim.

The first-encounter and terminal-escape theorems received independent
adversarial derivations. The audit explicitly checked near-collision
interpretation, reduced-mass conventions, Levi--Civita conjugations, time
scaling, all leading constants, and the maximal-bootstrap closure. An
independent audit reproduced the CAPD field, time transformation, interval
cover, normalization, and sign. It found and prompted repair of an inward-
rounded decimal display; the proof now records exact hexadecimal endpoints
and uses only the rational lower bound $1/125$. A separate adversarial audit
rederived the compactification and $O_7$ map, checked McGehee's hypotheses and
the tangent contraction, and required three repairs now included in the proof:
exact time-map factorization, the explicit Lipschitz estimate, and the
three-component phase-gauge subtraction.

Three independent adversarial passes audited the incoming-tail theorem. They
found and forced repair of: a nonuniform constant-energy estimate; an invalid
partial-LC-block physical-time bound; unspecified oscillator “actions”; a
noncommuting phase/radius limit; and use of a linearized transverse equation
for a possibly nonaxis solution. The final proof uses the radius-dependent
energy defect $O(Y^{-3})$, exact LC invariants $(E+1,L,K)$, separate endpoint
blocks, the exact intercept subtraction, and reflection-odd mean-value
factorization. All three final passes endorsed the repaired theorem.
