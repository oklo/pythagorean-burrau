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
Pythagorean subfamily. The restricted finite-turn side has infinitely many
exact first-turn brake-state resonances accumulating at the separatrix, so a
uniform limiting no-brake lemma is false. The fixed-resonance finite-$B$
splitting is now computed: every fixed sufficiently late restricted resonance
has a neighborhood free of full finite-$B$ brakes. The normalized angular-
momentum theorem further makes the first-turn exclusion uniform over the
accumulating resonance layer. The remaining skinny obligation is to control
later turns and classify the exact finite-$B$ separatrix phase. At
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
Level-D open escape intervals. The remaining task is to split the simultaneous
velocity conditions near the restricted resonance sequence and to classify
exact separatrix phases.

Restricted transversality is closed. CAPD interval Taylor integration proves
$h'(\pi/4)>14/625$, while the compactified time-$\pi$ map satisfies
McGehee's sector hypotheses. Tangents to its fixed-phase stable curve contract;
under a hypothetical tangency, $h=z'-\eta_{\rm pin}$ would be such a tangent,
but the validated sign forces it to grow. Uniform matching and terminal
transfer are now closed, so infinitely many open terminal windows containing
rational Euclid parameters are an unconditional Level-D theorem. Remaining
finite-$B$ obligations are persistence and signed displacement of the exact
separatrix, splitting near the restricted turn-resonance sequence, and
exclusion of second brakes after one or more outer turns.

The endpoint arithmetic is now stronger than rational density: an exact
van-der-Corput/Weyl argument gives a positive-lower-density nonperiodic subset
of $(4n^2-1,4n,4n^2+1)$. It still cannot name the first certified member,
because the escape arc and the finite-$B$ threshold are non-effective. The
same equidistribution visits compact finite-turn arcs with positive density,
so phase sampling alone cannot close the remaining post-turn obligation.

At a fixed restricted resonance, the two radial conditions have exact
Jacobian
\[
D_n=-{Z_nz_{\theta\theta}(T_n)\over2}\mathcal A'(\phi_n).
\]
Simplicity $\mathcal A'(\phi_n)\ne0$ remains open and is needed to
parameterize the double-radial branch by the implicit-function theorem, but it
is no longer needed for local brake exclusion. The proved first-order LC
matching theorem gives, at every fixed restricted brake,
$Z'_{B,x}/B\to C_n=\xi'(T_n)$. Therefore $C_n\ne0$ alone excludes a nearby
finite-$B$ full brake by compactness. Uniform large-$n$ control of the
restricted coefficient is reduced to one parabolic scattering invariant:
\[
Z_nC_n\longrightarrow-{\mathscr W_\infty\over2},\qquad
\mathscr W_\infty=\lim_{\theta\to+\infty}(zp_-'-z'p_-).
\]
The convergence is proved analytically, and a finite CAPD/Jost-tail
certificate now proves $\mathscr W_\infty>21/50$. Hence $C_n<0$ at every
sufficiently late restricted resonance. The exact cubic torque cancellation
and the LC tail bootstrap now prove the full first-order quotient match
through every fixed restricted segment. A failed intermediate formulation
remains instructive: divided LC normal invariants can tend to zero while
physical transverse binary velocity blows up at a near-collision phase. The
proof instead propagates the smooth divided LC invariants and converts to
physical derivatives only at a uniformly separated apocenter. The uniform
angular-momentum theorem removes the loss from
$C_n\asymp Z_n^{-1}\to0$. Exclusion of brakes after later outer turns remains.

The late-simplicity problem is now reduced more precisely in
`LATE_RESONANCE_SIMPLICITY.md`. In McGehee variables the degree-four map has
the exact drift $H_1-H=-k^2x^6H$. With transverse energy
$\varepsilon$ and $x,y=O(\sqrt\varepsilon)$, its formal blown-up passage gives
$T=(\pi/\sqrt2)\varepsilon^{-3/2}$. The missing lemma is the differentiated
estimate
\[
 {dT\over d\varepsilon}
 =-{3\pi\over2\sqrt2}\varepsilon^{-5/2}(1+o(1)),
\]
including the entrance region at parabolic infinity. A $C^0$ relative
asymptotic is insufficient.

The joint finite-$B$ crossover is now closed at the first outer turn. The
outgoing inner field satisfies
$p_-=\gamma z-\mathscr W_\infty\sqrt z+o(\sqrt z)$. On the macroscopic
radial Kepler arc turning at $R$, the normalized $\sqrt s$ transverse mode
reaches apocenter with velocity $-1/R$. More invariantly, the exact torque
bootstrap proves uniformly in turn height
\[
 {Y\times\dot Y\over B^{3/2}}(t_{\rm turn})
 \longrightarrow {\mathscr W_\infty\over2}>0.
\]
`OUTGOING_ANGULAR_MOMENTUM.md` records the proof. The highest-leverage
endpoint obligation is now to continue this signed scalar through the inward
leg after the first turn and classify its change across subsequent central
encounters; a second or later brake remains open. The inward far tail is now
closed as well: if the light body returns to a fixed large section, its
normalized angular momentum still tends to $\mathscr W_\infty/2$. Thus the
next unknown is a compact collision-regularized central-encounter map, not a
second infinite tail.

For the second encounter, reflect the returning vertical coordinate and let
$\mathcal C_2(\psi)$ be the outgoing transverse Wronskian at the next
captured turn. The returned incoming data are fixed by two first-scattering
constants $(\gamma,\mathscr W_\infty)$. The extended pinned certificate gives
$-1/100<\gamma<-1/250$, while the exact even-potential connection matrix gives
\[
 \mathcal C_{2,\mathrm{par}}
 =-2\gamma\mathscr W_\infty>{21\over6250}.
\]
Thus the centered parabolic endpoint is closed. Ordinary evidence gives
$\mathcal C_2>0$ on every sampled captured phase, all with center mean phase
in $(0,\pi)$. The precise next obligations are to classify all captured
components, prove the phase-continuum sign on their compact interiors, and
analyze the $\phi\to\pi$ triple-collision limit before finite-$B$ transfer.
The exact blow-up has Newtonian scale
$\theta=\varepsilon s$, $(r,z)=\varepsilon^{2/3}(R,Z)$ and an equilateral
collision ray whose transverse indicial exponents are
$(3\pm\sqrt7)/6$. The missing selection theorem is to identify the returned
Jost combination on this collision manifold and prove its one-sided outgoing
Wronskian sign; `TRIPLE_COLLISION_ENDPOINT.md` records the exact reduction.

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
