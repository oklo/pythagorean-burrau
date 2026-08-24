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
components and prove the phase-continuum sign on their compact interiors.
The certified local $\phi\to\pi$ branch and a finite-$B$ transfer wedge are
now closed; remote endpoint components and the shrinking finite-mass boundary
layer remain open.
The exact blow-up has Newtonian scale
$\theta=\varepsilon s$, $(r,z)=\varepsilon^{2/3}(R,Z)$ and an equilateral
collision ray whose transverse indicial exponents are
$(3\pm\sqrt7)/6$. The autonomous shape equation now has a proved unique
increasing peel-off branch modulo logarithmic-time translation. It crosses
the center with an explicit positive speed and has positive light--binary
separation at the prescribed binary collision. Both scalar signs and the
singular local selection mechanism are now proved. What remains is the compact
endpoint-localization statement showing that the finite-$\varepsilon$
returned family accumulates on the certified connection. Conditional on that
statement, the exact graph-transform and fibered-exchange theorem identifies
the returned Jost combination and its outgoing Wronskian. Precisely, with
$\delta=\pi-\phi$, the target is
\[
 \delta^{(\sqrt7-1)/6}\mathcal C_2(\phi)
 \longrightarrow \mathscr T
 =4^{(\sqrt7-1)/6}A_-K_->0,
\]
where $A_-$ is the slow Fuchsian Jost coefficient and $K_-$ is its universal
first-turn transfer. `TRIPLE_COLLISION_ENDPOINT.md` records the exact
reduction. The universal factor is now closed:

\[
 K_->0.
\]

An exact Riccati barrier supplies the signed center section, and a pinned
CAPD proof covers the whole analytic speed box, the prescribed binary
collision, and the first turn. Ordinary shooting gives the non-rigorous
magnitude $K_-\approx2.435$. The global factor is now also closed:

\[
 A_->0.
\]

Analytic collision-tail boxes and a pinned CAPD escape/return bracket trap a
parabolic collision connection in
$-0.24696\le a\le-0.24694$. A phase-uniform Volterra enclosure of the returned
Jost tail proves $W(J,P_+)<-1/2$, while
$W(P_-,P_+)=-\sqrt7$, giving the displayed sign. On the final binary infall,
exact use of $r$ as independent
variable now reduces $A_-$ to a Fuchsian projector with exponents
$(3\pm\sqrt7)/4$. The collision-stable base has one free coefficient with
shape exponent $(-1+\sqrt{19})/4$. Thus the next certificate is a scalar
intersection of that one-dimensional collision-stable family with the
incoming parabolic manifold, plus the sign of one propagated linear field.
Ordinary section projections stabilize near $0.314>0$.

`TRIPLE_ENDPOINT_MATCHING_CERTIFICATE.md` records the square formulation.
The completed coefficient proof uses an equivalent topological energy bracket.
The subsequent order, tangent, and exchange arguments prove uniqueness,
transversality, and a one-sided local captured branch with positive
renormalized coefficient. A full finite-mass McGehee/LC exchange transfers
this sign whenever

\[
 \omega_0(B)+B=o\!\left(\varepsilon^{(1+\sqrt{19})/6}\right).
\]

It excludes every local-branch gap above
$\Delta(B)=(\omega_0(B)+B)^{3/(1+\sqrt{19})}$ for sufficiently small $B$.
The remaining endpoint obligations are global classification of remote
captured components and the outgoing dynamics of the joint layer
$0<\varepsilon<\Delta(B)$; finite-$B$ transfer is no longer wholly open.
Energy separately proves that no brake occurs while the actual late-scaled
tight-pair separation satisfies
$|R|\le(1-B^2)/(1+B^2-B^4)$. Thus the joint blow-up is needed to recover
outgoing signed data and control later re-expanded motion, not to exclude a
brake inside the near-triple tube itself.

The joint two-mode blow-up now proves that this layer has only one new
projective degree of freedom. With intrinsic longitudinal and odd amplitudes
$H_B,T_B$,
\[
 \rho_T=|T_B|^{4/(1+\sqrt7)},\qquad
 \kappa_B={H_B\over
 |T_B|^{(1+\sqrt{19})/(1+\sqrt7)}}.
\]
Every endpoint sequence converges after rescaling either to the planar
massless restricted orbit $\mathscr U_\kappa$ for a finite real $\kappa$, or
to one of the two rectilinear exits as $\kappa\to\pm\infty$. The remaining
localized obligation is to classify this one-parameter family and prove a
nonvanishing outgoing scattering scalar uniformly in $\kappa$; this is
CONJECTURAL.

The planar shape reduction supplies the candidate scalar ingredients:
\[
 \mathcal E_\zeta=-{|w_\zeta|^2\over3},\qquad
 \Lambda_\zeta+{\Lambda\over3}=-xyK,\quad K>0.
\]
The torque sign is already global on each component where $xy$ has fixed
sign, and transverse convexity controls $|y|\ge\sqrt3/2$. The indispensable
remaining lemma is a classification of transitions through
$|y|<\sqrt3/2$, including light-heavy collision branches and the LC matching
of the physical angular sign. Global outer-strip invariance is false at
$\kappa=0$ and must not be assumed.
The sharp bound $W\ge11/36$ and LaSalle's argument now exclude every compact
collision-free backward-captured component, so the transition classification
needs only genuine collision-boundary approaches and unbounded shape/velocity
exits; recurrent compact trapping is no longer an open outcome.
Every isolated light-heavy encounter is regularized by the exact forced LC
system of PLANAR_LIGHT_COLLISION_LC.md. The square residual
\[
 \mathcal F(\kappa,\sigma)
 =(\operatorname{Re}u,\operatorname{Im}u)=0,
\]
has now been validated at one transverse selected-primary zero:

\[
 1.2679351752<\kappa_c<1.2679351759,
 \qquad
 -3.52212<\det(\partial_\kappa u,v)<-3.38401.
\]

The strict interval-Newton inclusion proves uniqueness inside its explicit
$10^{-7}$ parameter-time box. It locally partitions nearby continuations into
two impact sides. This classifies a limiting collision parameter; it does not
continue an actual classical collision.

The finite-tail truncation is no longer an obligation. The analytic stable
parameterization theorem proves, uniformly for
$5/4\le\kappa\le13/10$ at $\zeta\ge10$, explicit enclosures for the state and
its $\kappa$ tangent. Pinned CAPD propagation has also carried the full
$1.26793\le\kappa\le1.26794$ tail box through the nonsingular shape leg and a
fixed LC leg while proving the chart-domain inequalities. Its terminal
$u$-box contained zero but initially lost the decisive $\kappa$ correlation.
The repaired verifier keeps shape and LC variables in one persistent
`C1Rect2Set`, implements the nonlinear coordinate change as a unit-time
construction flow, propagates the parameter tangent, and closes interval
Newton. Thus tail truncation, finite propagation, correlation preservation,
root existence, local uniqueness, transversality, and chart safety are no
longer obligations for this root.

The remaining global obligations begin outside the newly certified local
cusp.  The nearest opposite-primary collision zero is now independently
certified near \(\kappa=1.2640119251\), but every remaining collision zero
must still be excluded or certified; collision safety is needed on each
intervening parameter component, followed by propagation to a terminal
escape, collision, or non-brake certificate.  Outgoing reconstruction inside
the first root box is no longer open.
The exact identity
\[
 \ell=q\times q_t=2\det(u,v),\qquad
 \partial_\kappa\ell|_{u=0}=2\det D\mathcal F
\]
turns the same determinant certificate into a signed impact-parameter
certificate; the incoming physical-time sign is reversed by
$dt/d\theta=-1$.
At a transverse zero it also gives the proved local normal form
\[
 r_{\min,\mathrm{local}}
 =2(\det D\mathcal F)^2(\kappa-\kappa_c)^2+O(|\kappa-\kappa_c|^3).
\]
Hence the root certificate settles local one-sided avoidance.  A distinct
opposite-primary collision is now certified in a disjoint box, but all other
times and every component between collision graphs remain global obligations.

Those obligations are now closed on the explicit interval
\(1.2679251755\le\kappa\le1.2679451755\) around this first root.  The full
correlated parameter interval propagates through the selected
collision--ejection LC block and a signed heavy-binary LC bridge to a strict
restricted escape cone.  The conservative limiting finite-mass
margin
\[
 \dot\rho_0-{2\over(3/2)(\rho_0-r_0)}
 -\sqrt{{4\over r_0}+{2\over100}}-{3\over2}>0.65
\]
feeds a full hierarchical-energy lemma: the inner pair grows at most
linearly while the light body outruns it, and its total future tidal work is
\(O(B)\).  Thus every sufficiently small compatible positive-mass member in
the local cusp either collides classically or escapes.  This closes outgoing
classification only near the certified root; excluding or certifying every
remaining collision boundary on a larger compact \(\kappa\)-range remains
open.

For the second certified collision boundary, the third positive-primary LC
chart, nonselected-primary separation, heavy-binary bridge, and finite-mass
transfer are now closed in
`COMPUTER_ASSISTED_PLANAR_SECOND_COLLISION_ESCAPE.md`.  The explicit narrow
box has been enlarged by 195 abutting tiles: every
$1.2640099161\le\kappa\le1.2640126461$ is collision-or-escape.
Immediately below this component, two further transverse collision boundaries
are now certified in
`COMPUTER_ASSISTED_PLANAR_THIRD_FOURTH_COLLISION_ROOTS.md`.  The third is a
positive-primary collision and the fourth is a negative-primary collision;
their exact root projections are disjoint by more than
$1.2058\times10^{-11}$.  The fourth verifier includes a broader uniqueness
strip proving that its exact branch misses the earlier collision.  The entire
fourth-root box is now continued rigorously to a fifth positive-primary LC
entry in `COMPUTER_ASSISTED_PLANAR_FOURTH_TO_FIFTH_ENTRY.md`.  The fifth
passage is extraordinarily sensitive: a fresh box restart loses the impact-
parameter correlation.  A correlation-preserving fifth-chart propagation,
the subsequent sixth negative-primary chart, and terminal escape enclosure
remain open, as does exclusion or location of additional boundaries.

The selected finite-mass relative coordinate now gives an exact perturbative
bridge:
\[
 q=Z-{A\over1+A}R,\qquad
 q''=-(1+B)\Phi(q)+A\{\Phi(R)-\Phi(q+R)\}.
\]
The $R$ equation itself is not LC-regular because it contains
\(B\Phi(q)\).  The collision-adapted complementary coordinate
\[
 Q=R+{B\over1+B}q
\]
cancels that singular force exactly; its acceleration contains only the
forces at \(Q-Bq/(1+B)\) and \(Q+q/(1+B)\).
The corresponding LC constraint is
\(2|v|^2-(1+B)-h|u|^2=0\).  A $C^1$ chart on one fixed constrained incoming
section and the certified nonsingular limiting Jacobian prove that the
collision root persists uniquely under positive mass and compatible local
section-state perturbations.  For the exact tied trajectory the remaining
scalar obligation can now be stated intrinsically.  The differentiated
two-mode inclination theorem transports the normalized projective-amplitude
family and its \(\kappa\)-tangent through the long saddle dwell and the
scaled \(Q\)-adapted LC chart.  It gives the local graph
\(\kappa_c(B,T,S,\Xi)\), so the tied gap is
\[
 \Delta_{\rm intr}(B)=
 \kappa_B-\kappa_c(B,T_B,S_B,\Xi_B),
 \qquad \kappa_B={H_B\over|T_B|^{\mu/\tau}}.
\]
The proof uses a common Lyapunov--Perron weight
\(\mu/2<\omega<\tau\), an unstable-manifold shadow on the infinite tail,
and \(C^1\) stable holonomy only at a fixed finite section; two independent
adversarial passes endorsed the repair.  No sign, zero, or oscillation theorem
for \(\Delta_{\rm intr}\) on every collision-free component has been proved.
There is now one exact partial substitute: the phase-cycle argument in
`REAL_COLLISION_SAMPLING.md` proves that every sufficiently late cycle either
already contains an earlier classical collision or contains a zero of
\(\Delta_{\rm intr}\).  Thus infinitely many real tied parameters collide.
The explicit cusp strengthens the second alternative to a nonempty open tied
interval all of whose members collide or escape.  It still does not
distinguish which alternative occurs in a given cycle and does not prove that
any isolated collision parameter from the first alternative is rational. Even
a nonzero sign controls only the local selected encounter; exclusion of other
collisions and a later brake still requires the global scattering map.

The singular local part of that implication is now isolated in
`TRIPLE_ENDPOINT_SELECTION.md`. Exact translation by the center radius turns
the base into a parameter-dependent saddle passage; a graph-transform and
fibered exchange estimate prove selection of the unique universal base and
slow field conditional on fixed-section localization to the certified
bracket. The compact verifier additionally proves the force-monotonicity cone
$Z>r/(2\sqrt2)$, which gives uniqueness of the parabolic connection inside
that bracket. The differentiated collision contraction and the existing
McGehee fixed-phase graph theorem then prove differential transversality.
Together these results construct an unconditional one-sided local captured
branch with positive renormalized coefficient. The remaining restricted
endpoint issue is global component classification, not local selection.

## Adversarial checklist

Every promoted lemma must be checked for hidden genericity; vector-valued
mean-value misuse; rational-density fallacies; unlabelled/rotated returns;
near-collision substitution; nearby-orbit substitution; loss of endpoint
uniformity; extrapolation of a local sign; and conversion of finite computation
into an infinite claim.

The universal peel-off lemma received an independent phase-plane audit. The
audit confirmed the energy signs, uniqueness, monotonicity, and center-speed
bound, but rejected the original inference from $y_\tau/y\to2/3$ to a
nonzero physical collision limit. The repaired proof uses the exact monotone
factor $e^{-2\tau/3}(y_\tau+y/3)$ and a tail contradiction to prove that the
limit is strictly positive. No finite-$\varepsilon$ selection is inferred
from this autonomous limiting lemma.

The $K_-$ certificate received an independent source audit and replay. The
audit rederived the $\mu$-field and every factor of $1/3$, checked CAPD's
one-accepted-step continuation and whole-step enclosure semantics against the
pinned source, verified the exact dyadic cover, and checked the first-turn
monotonicity argument. It also confirmed that the two propagated transverse
bases cover every center logarithmic derivative $r\ge1/1000$, so no hidden
upper cutoff on $r$ is present. The replay reproduced the stored hexadecimal
certificate. The audit explicitly rejected any inference from $K_->0$ to
finite-$\varepsilon$ selection or to the sign of $A_-$.

An independent audit rederived the exact final-infall equations, both
indicial pairs, the $r$-projector, and the positive conversion factor between
$\widehat A_-$ and $A_-$. It also checked that the projector limit follows
from a constant hyperbolic Euler system plus exponentially decaying
coefficients in $x=-\log r$. The conditional cone lemma's time orientation
and force comparison were verified. The audit treated the displayed
$0.314$ projection only as ordinary finite-gap evidence. It caught and
prompted repair of a collision-coordinate exponent-name collision and
required derivative-strengthened Fuchsian asymptotics for both the projector
and the limit $\dot w\to0^+$.

The finite matching reduction received a second independent dimension and
coordinate audit. It confirmed that one collision-stable base coefficient is
sufficient but that the incoming intercept and both transverse collision
modes must be retained. It also identified a subtle loss of
$\mathscr W_\infty$ if only the limiting values of
$(P,Q)=(x^2p,\dot p/x)$ are imposed. The repaired certificate uses
$(P,\Omega)$ with $\Omega=z\dot p-\dot zp$, for which the boundary data are
directly $(2\gamma,-\mathscr W_\infty)$. The audit independently derived the
$-\sqrt7$ transverse determinant and endorsed the regular $r=1/2$ section.

The completed global-coefficient certificate received two independent
adversarial passes. The first rederived both collision Green operators,
checked their weighted norms and the explicit Frobenius corrections, and
verified that the analytic remainder bounds fit strictly inside the dyadic
initial boxes. The second independently replayed the pinned CAPD wrapper and
checked the reversed-time signs, whole-step positivity of the candidate path,
the escape/return connectedness argument, the returned-Jost Volterra bounds,
and the Wronskian orientation. It confirmed that $W(J,P_+)<-1/2$ is uniform
over every possible parabolic connection in the bracket and does not rely on
uniqueness or generic transversality. Neither audit inferred the then-open
finite-$\varepsilon$ selection theorem.

A subsequent whole-path cone check and adversarial comparison audit prove
that the bracket contains a unique parabolic connection and orders its two
sides. The audit explicitly rejected treating pairwise order as differential
transversality. It required derivative-strengthened stable tails, a
differentiated incoming parabolic graph, and a fixed phase gauge. The repaired
proof supplies the first by differentiating the collision contraction and the
second from the already-proved McGehee fixed-phase graph; a re-audit endorsed
the resulting noncollinearity argument.

The conditional shifted-Fuchsian selection theorem received a separate
adversarial derivation. It confirmed the exact center clock, both translated
equations, the Lyapunov identity, all exponent conversions, the one-way lower
exit, and the full scaled $(p,\dot p)$ state. It initially rejected compact
coefficient convergence as insufficient over the diverging saddle dwell. The
repaired proof now contains the required parameter-dependent graph-transform
estimate and fibered exchange bound, including the
$\rho^{\sqrt7/2}$ fast-mode suppression. Combined with transversality, this
constructs the unconditional local captured branch. Only global endpoint
localization remains conjectural.

The finite-mass endpoint wedge received two further independent adversarial
passes. They rejected the first proof for importing the restricted exchange
over a diverging dwell and for propagating an unscaled LC limit after division
by the shrinking transverse amplitude. The repaired proof constructs the
full homogeneous McGehee system, uses the corrected reduced spectrum
$(-n,\mu,1-\beta_-,1-\beta_+)$ after quotienting rotation, closes the
longitudinal/transverse estimates simultaneously, and proves the center-scale
ratio. A reflection/Hadamard identity exposes the divided LC source as
$B/\eta=\varepsilon^{(1+\sqrt7)/6}\to0$. Both final audits endorsed the
analytic exchange and the sign-based computer-assisted wedge exclusion.

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
