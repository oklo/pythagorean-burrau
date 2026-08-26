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

## Maximum-event branch route

The exact event reduction is complete: every brake is a strict maximum of
$I$, lies on $U=U_0$, and obeys an explicit pairwise collision-separation
bound (uniform on parameter compacts away from $u=0$). Folds and
minima carry the uniform kinetic margin $K\ge U_0$. On every regular maximum
branch $t=t_k(u)$, the remaining condition is the planar origin-avoidance
problem

\[
 u\longmapsto\zeta(u,t_k(u))\in\mathbb C\setminus\{0\}.
\]

Writing $s=\mu_1|X|^2/I$ and $\phi=\arg Y-\arg X$, the exact event identity
\[
 \zeta=I(\dot s-2is(1-s)\dot\phi),\qquad
 |\zeta|^2=8KI s(1-s)
\]
shows that the same condition is $K=U-U_0>0$ away from Jacobi degeneracy.
This scalar is nonnegative and has an even-order zero at a transverse brake,
so ordinary sign arguments and intermediate-value reasoning cannot exclude
or force a zero.

Five individual rational parameters have complete validated covers, but the
unresolved universal obligations are:

A first parameter-family certificate now covers the complete real interval

\[
 {29\over100}\le u\le {14501\over50000}.
\]

It proves collision-free propagation through the first positive $I$-maximum
and excludes a brake there by two strict regularized residual components.
This advances point certification to an open family, but it does not close
any later maximum branch.  See `MIDDLE_FIRST_MAXIMUM_INTERVAL.md`.

A correlated certificate and an exact gap-free tiling campaign close every
later branch on the smaller real interval

\[
 0.29\le u\le0.2900000101.
\]

Six validated $C^1$ Poincare images synchronize the exchange; independent
C0 tube covers verify collision separation and brake exclusion between
sections; a terminal analytic collision-or-escape alternative excludes all
future brakes on the initial width-$10^{-9}$ subinterval.  One hundred
adjacent width-$10^{-10}$ certificates extend the same theorem, with exact
shared endpoints, to the displayed upper endpoint.  Thus this smaller
interval is a full nonperiodicity theorem.
It does not reduce the global obligations below.  For the immediate widening
program, a width-$10^{-8}$ tile already crosses all six exchange sections;
an earlier Form-B switch and explicit defect graph now cross that chart on a
width-$10^{-12}$ control, and pair--23 geometric sections remove the next
fixed-clock phase spike.  A validated directional C2 graph has now closed the
old tangent obligation on the width-$10^{-12}$ control: it completes the
whole itinerary and terminal escape test, and its last-section tangent width
is $1.47\times10^{-8}$ rather than $0.90$.  The Form-B hull improves from
$1.9587\times10^{-3}$ to $8.0706\times10^{-5}$.  This control lies inside an
already-proved interval, so the result validates machinery but adds no new
nonperiodicity parameter.

The immediate widening obligation has moved again.  At the overlapping
pair--23/pair--13 exchange near $t=3.45$, the additive defect grows from
$3.67\times10^{-9}$ to $1.12\times10^{-6}$ and thereafter dominates every
section hull, reaching $0.0437$ at the terminal time.  The true quadratic
spread there is only $1.16\times10^{-16}$.  Thus second order retains the tied
parameter jet but the mean-value box for higher-order/numerical defect loses
the exchange correlation.  A scalable certificate now requires one of:

1. a rigorous reabsorption of the additive defect into a new parameter
   polynomial at or immediately before the fourth minimum;
2. a simultaneous-exchange regularized chart that controls both close pairs;
3. a higher-order Taylor model whose remainder remains correlated through the
   double passage; or
4. a proved width-scaling estimate showing that modest subdivision closes the
   defect economically.

Fixed-time projection, additional linear tripleton bases, and first-order
tangent splitting have all been excluded as repairs.  The width-$10^{-11}$
C2 scaling replay is pending.

1. bound or classify the number of maximum branches before the terminal
   collision/escape alternative, uniformly on a parameter component;
2. prove a sign, winding, Wronskian, or ordering invariant that keeps every
   branch image away from the origin;
3. classify branch creation at collision, escape, infinite return time, and
   degenerate $\dot I=\ddot I=0$ events;
4. if real zeros remain, locate them rigorously before attempting rational
   exclusion.

The exact torque-reversal lemma adds an independent event filter.  On every
strict fundamental parameter, a second brake forces all three cyclic torque
integrands to reverse their launch signs.  If it occurs before the first
syzygy, every pair of mutual distances must therefore exchange order at least
once.  A useful next lemma would show that one of these three order reversals
is impossible on each maximum branch, or else classify the syzygy at which
the common area factor changes sign.

Away from syzygy, the exact residual
$(\ell_{12},\ell_{23},\dot I)$ is equivalent to a labelled brake at
$P=L=0$.  Thus on every regular nonsyzygy maximum branch the origin-avoidance
problem can be written as

\[
 u\longmapsto(\ell_{12},\ell_{23})(u,t_k(u))\ne(0,0).
\]

Unlike $K$, these two components have signed torque evolution and begin in a
fixed quadrant.  The missing theorem is a winding/order or integral-comparison
argument preventing their simultaneous cancellation after syzygy.  Hopf
coordinates are still required on maximum branches that meet syzygy.
The exact determinant relating this torque pair to the $\zeta$ shape
velocity is a positive factor times $-(X\times Y)$, so no additional hidden
rank loss occurs away from syzygy.

The two initial side gaps point into the numerically observed ordering cone:
$(r_{12}-r_{23})''(0)<0$ and $(r_{23}-r_{31})''(0)>0$ analytically on the
strict fundamental interval.  A proposed first-syzygy ordering lemma is

\[
 r_{12}>r_{23}>r_{31}\quad\hbox{until }\Delta_2=0.
\]

It would fix the first syzygy type (body 3 in the middle) and preserve the
three launch torque signs up to that event.  It is presently CONJECTURAL;
local accelerations and finitely many ordinary trajectories do not prove it.

The gravitational part of the second gap is now closed globally on this
cone: exact tensor-Bernstein arithmetic proves
$\mathfrak g_{23}-\mathfrak g_{31}>0$. Therefore the remaining inequality is
precisely

\[
{\ell_{23}^2\over r_{23}^3}-{\ell_{31}^2\over r_{31}^3}
>-(\mathfrak g_{23}-\mathfrak g_{31}).
\]

The left side can be negative, so positivity of gravity alone does not prove
the cone.  A torque-integral estimate strong enough to dominate this negative
centrifugal contribution would prove $r_{23}-r_{31}$ is convex and increasing
until the first syzygy.

On the ordered right/obtuse subcone, the first gravitational gap is also
closed with the desired sign:
$\mathfrak g_{12}-\mathfrak g_{23}<0$.  Consequently a complete
first-syzygy cone theorem has been reduced to three coupled obligations:

1. preserve $D=r_{12}^2-r_{23}^2-r_{31}^2\ge0$ until first syzygy;
2. dominate the adverse part of
   $\ell_{12}^2/r_{12}^3-\ell_{23}^2/r_{23}^3$;
3. dominate the adverse part of
   $\ell_{23}^2/r_{23}^3-\ell_{31}^2/r_{31}^3$.

The two gravitational signs alone do not close any of these velocity
inequalities.

The strongest purely instantaneous total-energy repair has now been ruled
out exactly.  Minimizing kinetic energy at fixed
$(L,\ell_{23},\ell_{31})$ gives an optimal Gram-inverse bound, but an exact
interior ordered-right/obtuse state with the required torque signs makes the
resulting first-gap upper margin positive.  Therefore obligations 2 and 3
must use reachability from the brake.  The most direct missing estimates are
history-dependent comparisons for

\[
 { -\ell_{31}(t)\over\ell_{23}(t)}
 ={m_2\int_0^t\Delta_2(r_{23}^{-3}-r_{12}^{-3})\,ds
   \over
   m_1\int_0^t\Delta_2(r_{31}^{-3}-r_{12}^{-3})\,ds}
\]

and the analogous ratio $-\ell_{12}/\ell_{23}$.  A viable proof must couple
these integrals to the evolving side ratios; no inequality depending only on
the current shape, $H$, $L$, and torque signs can close the cone.

For the first ratio this coupling is now scalar.  With

\[
 k={r_{23}^{-3}-r_{12}^{-3}\over
        r_{31}^{-3}-r_{12}^{-3}},qquad
 \eta={m_1\over m_2}{-\ell_{31}\over\ell_{23}},
\]

one has exactly $\dot\eta=(F/{\cal A})(k-\eta)$.  Proving $k$ decreases to
first syzygy would give $k<\eta<k(0)$ automatically.  The gravitational part
of $(\log k)''$ is now proved strictly negative over the full ordered
right/obtuse cube, and the full initial curvature is negative analytically.
The remaining sharp sub-obligation is

\[
 Q_J(q,\dot q)<-\ddot J_{\rm grav},
 \qquad J=\log k,
\]

only on states reachable from the brake while $J'<0$.  Ordinary ambient-state
tests show both signs for the velocity Hessian, so sign-definiteness must not
be assumed.  The weaker static first-return boundary version also fails
exactly: at $u=2/5$, shape $(R,p,q)=(1,39/40,1/30)$, there is an exact
$L=J'=0$ velocity with torque signs $(-,+,-)$ for which, after imposing
$H=-U_0$ at scale $R=1/2$, one has $J''>0$.  This state is not known
reachable.  Hence the indispensable missing hypothesis must retain the
integral origin of the pair angular momenta or an equivalent trajectory
history constraint.

There is now a first-order formulation of this same obstruction which is
sharper than the curvature inequality.  Exact elimination of the normalized
shape velocity gives an explicit rational graph $h(u,x,y)$ and a proved
positive coefficient $\mathcal A$ such that

\[
 (\log k)_s={W\over\delta}\mathcal A(\eta-h).
\]

The positivity proof is a complete 168-coefficient exact Bernstein
certificate on the ordered shape--mass cube.  At launch $h-k(0)>0$ by an
exact signed factorization.  Therefore the monotonicity obligation is now
equivalent to the scalar no-contact theorem

\[
 \eta(t)<h(u,x(t),y(t))
\]

on every brake-reachable ordered segment.  The exact $u=2/5$ static
first-return witness satisfies $\eta=h$, so current-state bounds including
$k<\eta<k(0)$ do not prove the inequality.  A successful argument must
compare the weighted history defining $\eta$ with the evolution of the
explicit threshold $h$.

A second exact cube certificate proves $h>k$ everywhere in the strict
ordered cone.  Consequently, at a contact $\eta=h$ the instantaneous
history rate satisfies $\eta_s<0$; loss of monotonicity can occur only if the
threshold $h$ falls still faster.  This comparison is now quantified
exactly.  With explicit rational functions $P<0$ and $S$,

\[
 W\delta(\eta-h)_s=P-ZS.
\]

Every contact with $S\ge0$ is automatically safe.  On $S<0$ the sharp
remaining condition is

\[
 Z<Z_J={P\over S}.
\]

The exact $u=2/5$ ambient contact has $Z/Z_J=1.05745644351720\ldots$, so
energy does not imply this bound.  The primary compact-shape obligation is
therefore a brake-reachable amplitude theorem on the explicit set
$\{\eta=h,S<0\}$, rather than unrestricted domination of the full curvature
throughout the cone.

This amplitude theorem cannot be reduced to only one of the two thresholds:
exact rational examples realize both $Z_J<Z_2$ and $Z_J>Z_2$.  A common
history estimate must therefore imply the appropriate bound against
$\min(Z_J,Z_2)$ where both contact mechanisms are dangerous, unless a new
quantity bypasses both barriers.

There is now an exact terminal simplification.  On an ordered syzygy with
body 3 in the middle, the collinear $P=L=0$ constraints force

\[
 \eta={q(m+1-q)\over(1-q)(n+q)}=h.
\]

Thus the desired noncontact theorem must be stated as $\eta<h$ on the
positive-area interior, with forced equality allowed at terminal syzygy.
Both $P$ and $S$ contain the same area-squared factor, so $Z_J=P/S$ has a
path-independent rational extension there.  Five exact bivariate Bernstein
certificates prove

\[
 1<Z_J^{\rm syz}<Z_2
\]

for the complete tied torque-compatible face, including the equal-mass edge
away from its $z=1$ endpoint.  Therefore only the sharper torque-contact
amplitude bound $Z<Z_J^{\rm syz}$ remains at this terminal face, even though
both thresholds are needed in the interior.  This does **not** supply that
bound globally: total energy permits syzygy states above $Z_J^{\rm syz}$.
The new endpoint certificate supplies it only for the continued first
syzygy in a one-sided near-isosceles neighborhood.  A separate odd-variation
certificate now proves $\eta<h$ on the complete preceding arc in that same
existential neighborhood, with forced equality at the event.  The unresolved
lemma is therefore a brake-history estimate over the remaining parameter
range.  At the endpoint, all four comparison collisions before the terminal
escape section now unfold transversely, the intervening regularized brake
residual is uniformly positive, and strict escape inequalities close the
future motion.  Thus no local endpoint obligation remains except making the
existential neighborhood effective if an explicit cutoff is desired.

The terminal inequality now has an exact coercive formulation.  With
$D=mn+mq^2+n(1-q)^2$, shape-time variables $\sigma=R_s/R$, $Q=q_s$, and

\[
 \mathcal L={D\over m+n+1}\left(\sigma+{((m+n)q-n)Q\over D}\right)^2
             +{mnQ^2\over D},
\]

energy gives $FZ+\mathcal L=2(U-U_0R)$.  Therefore

\[
 Z<Z_J^{\rm syz}\quad\Longleftrightarrow\quad
 \mathcal L>2U_0(R_J-R),\qquad
 R_J={U-FZ_J^{\rm syz}/2\over U_0}.
\]

Globally, this is the smallest current terminal obligation.  The exact
syzygy threshold now has the stronger uniform gap $Z_J^{\rm syz}>1$, and a
pinned endpoint/C1 certificate proves that the continued first syzygy has
$z<1$ and $Z<1<Z_J^{\rm syz}$ throughout an existential one-sided
near-isosceles neighborhood.  Thus this terminal obligation is closed there,
and the preceding noncontact obligation is closed there as well.  Both remain
open over the rest of the parameter interval.  Neither side-gap rate
signs nor $\dot I<0$ can prove it: an explicit velocity ray makes all three
signs strict while $\mathcal L=O(\varepsilon^2)$.  A successful lemma must
give a *quantitative* lower bound inherited from the brake history (or prove
$R\ge R_J$), uniformly through close encounters; qualitative monotonicity
alone is insufficient.

One terminal face of this reachability problem is now closed.  At a
collision-free syzygy with body 3 between bodies 1 and 2, the collinear
momentum constraints determine the torque ratio and transverse kinetic
energy exactly.  Combining their sharp lower bound with $H=-U_0$ reduces the
first gap to a bidegree $(20,6)$ exact Bernstein certificate.  It proves

\[
 (r_{12}-r_{23})''<0
\]

whenever the strict pre-syzygy torque signs persist to that ordered syzygy.
Thus obligation 2 is closed *on the syzygy face*.  It remains open in the
interior, and obligations 1 and 3 remain fully open.  In particular this
endpoint concavity does not prove that $r_{12}-r_{23}$ decreased throughout
the preceding arc.

For the interior estimate, put $Z=\ell_{23}^2/R$ and retain the weighted
history variable $\eta$.  After multiplication by $R^2$ the two centrifugal
gaps are exactly

\[
Z\left({(1-\eta)^2\over m_1^2}-x^{-3}\right),\qquad
Z\left(x^{-3}-{m_2^2\eta^2\over m_1^2y^3}\right).
\]

This reduces the next search to a reachable barrier for the two scalars
$(Z,\eta)$ coupled to the normalized shape $(x,y)$, rather than three
independent pair angular momenta.

The second-gap barrier is genuinely history-dependent even at syzygy.  The
exact $u=1/3$ ambient state

\[
 (R,r_{23},r_{31})=\left(1,{697\over700},{3\over700}\right)
\]

has energy $-U_0$, $P=L=0$, the strict launch torque signs, and
$\dot\Delta_2<0$, yet $(r_{23}-r_{31})''<0$.  Therefore obligation 3 cannot
be closed from local syzygy geometry and crossing orientation.  If

\[
 C_2=x^{-3}-{m_2^2\eta^2\over m_1^2y^3}<0,
 \qquad
 Z_*={\mathfrak g_{23}-\mathfrak g_{31}\over-C_2},
\]

the precise missing assertion is $Z<Z_*$ on every reachable ordered segment
(at least whenever the second gap could first lose monotonicity).  The exact
obstruction has $Z/Z_*=1.3724399581\ldots$; it quantifies how much sharper
than total energy the trajectory-history estimate must be.

Nor is the surface $Z=Z_*$ pointwise inward under the natural local
constraints.  An exact strict ordered-obtuse $u=1/3$ state with
$(x,y,\eta)=(499/500,1/20,3/20)$ has energy $-U_0$, $P=L=0$, decreasing
area, and $k<\eta<k(0)$, but

\[
 {d\over ds}\log(Z/Z_*)=50.8829734688\ldots>0.
\]

Thus the remaining invariant cannot be a scalar barrier depending only on
the current $(x,y,Z,\eta)$ through $Z/Z_*$.  It must encode a stronger
brake-generated correlation or use a different global mechanism.

Exhaustive compact-middle covering is not an acceptable substitute: measured
through-encounter parameter amplification is about $3\times10^8$ and grows
further at late events. The event reduction is a smaller exact problem, but
not by itself the missing global obstruction.

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
collision.  Its first syzygy is now also rigorously enclosed: $Z_*<1$, while
the tied symmetry-breaking Poincare derivative satisfies $z_v(1)>18$.  Exact
corner blow-up and $Z_J^{\rm syz}>1$ therefore close the terminal
first-syzygy amplitude inequality on a one-sided near-isosceles neighborhood.
The odd endpoint-variation certificate also closes the earlier interior
no-contact estimate throughout the complete first arc in that neighborhood.
A pair--12 $C^1$ LC certificate now proves that the subsequent binary
collision unfolds transversely, with
$\min_{\rm enc}r_{12}=\chi^2(1-v)^2+o((1-v)^2)$ and $\chi^2>900$, so every nearby
one-sided member traverses that encounter collision-free.  Four oriented
$C^1$ collision maps, a fifth-return delimiter, and a 7000-step $C^0$ cover
now close the complete comparison arc through $\sigma=7$: every selected
collision unfolds, the unselected squared separations stay above $1/500$,
and the regularized brake residual stays above $2$.  At the terminal section,
the fixed $\eta=4$ binary--escaper inequalities have strict rational margins.
Compact continuity therefore proves an existential punctured
near-isosceles real interval on which every tied orbit is collision-free and
brake-free to that section, then either collides classically or escapes.
The endpoint obligation is closed; making the interval effective is optional
for the universal theorem.  The remaining global obligation is the middle
parameter range.

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
fourth-root box is continued first to a fifth positive-primary LC entry in
`COMPUTER_ASSISTED_PLANAR_FOURTH_TO_FIFTH_ENTRY.md` and now through that close
passage to the transverse outgoing section $c_i=1/20$ in
`COMPUTER_ASSISTED_PLANAR_FOURTH_TO_FIFTH_OUTGOING.md`.  The latter retains a
single correlated doubleton through every nonlinear chart map. Immediately
after that section the fifth and sixth close passages overlap, so neither
ordinary coordinates nor either single-centre LC chart gives a uniform
interval domain. The exact simultaneous polynomial two-centre field is
derived in `PLANAR_TWO_CENTRE_REGULARIZATION.md`.

The fifth-focus collision question is now closed by bypassing the wrapped
outgoing-section restart. The exact fourth collision initializes the
two-centre chart directly. A 200-bit CAPD replay with the octic stable graph
and two nested interval-Newton steps proves a strictly negative transverse
collision phase. The native rational-hull replay then proves a strictly
negative focus coordinate and positive selected distance. A second focus map
resolves the sixth close passage, and a correlation-preserving graph embedding
into the ordinary bridge reaches the strict escape cone; see
`COMPUTER_ASSISTED_PLANAR_FOURTH_COLLISION_PHASE.md`. The localized open
positive-mass transfer is now closed in
FINITE_MASS_FOURTH_COLLISION_ESCAPE.md: the exact opposite-primary LC block,
compact collision-free focus segment, heavy-pair LC bridge, and hierarchical
escape lemma give a local collision-or-escape cusp. The remaining localized
obligations are an effective tied-family bound for that neighborhood and
global continuation outside the new common-clock cover.  The fixed-clock
mean-value certificate in
`COMPUTER_ASSISTED_PLANAR_FOURTH_COMMON_CLOCK_COVER.md` now classifies every
limiting parameter in
\[
 1.264009099014\le\kappa\le1.264009099457
\]
as prior collision or terminal regularized escape.  Its 131 overlapping
tiles close an explicit adjacent continuum except for the thin lower band
between the existential fourth-root neighborhood and the displayed left
endpoint. A correlation-preserving exact-section graph now validates at least
one tile in that band and reaches with microtiles to about
$2.2\times10^{-14}$ above the certified root box, but no finite overlapping
atlas or effective overlap with the root-local theorem has been proved. An
effective positive-mass/tied-family entry estimate, completion of that atlas,
and continuation beyond the displayed right endpoint remain open. Exclusion or location of
further collision boundaries also remains open. In particular the cover only
overlaps the current broad projection for the third root and does not certify
which side contains its exact parameter.

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

The directional C2 parameter graph has now passed the complete brake-to-escape
chain at both widths $10^{-12}$ and $10^{-11}$.  The second replay proves that
the retained tangent scales correctly by a factor of ten while the dominant
post-exchange additive defect is nearly width independent.  This validates the
local C2 scaling diagnosis but does not extend the already-certified Fable
interval.  Before using the graph for economical wider coverage, discharge
one of the following localized obligations: certify the opt-in pair--23 chart
sandwich across the $t\simeq3.4515$ encounter, or prove that a fixed-energy
reconstruction of the selected-pair `h` coordinate encloses every genuine
energy-leaf fiber despite the graph box's off-leaf spurious points.  Either
repair must retain the independent whole-tube brake/collision audit.

The fixed-energy reconditioning lemma now discharges the analytic part of the
second alternative.  Exact Jacobi decomposition proves both target `h`
formulas, and a fiberwise projection argument proves that off-energy spurious
box points may be moved without losing any genuine tied orbit.  An independent
audit accepted the proof and implementation, and the complete width-$10^{-12}$
energy-reconditioned sandwich passed.  Its terminal enclosure was slightly
worse than the no-sandwich control, so it does not discharge the economic
coverage obligation.  The remaining computational question is narrower:
whether invariant reconditioning at the final established Form-B switch alone
reduces the terminal defect, and, if so, how far that improvement scales in
parameter width before true section sensitivity dominates.

That question is now answered.  Final-switch-only energy reconstruction
reduces the width-$10^{-12}$ terminal hull by $11.5\%$, but on the proposed
single interval $[0.29,0.2900001]$ the earlier fixed-clock exchange is already
fatal: the graph hull grows from $1.20521\times10^{-3}$ at $t=3.4$ to
$0.547819$ at $t=3.45$, and the next fourth-minimum map fails closed.  The
localized obligation is therefore no longer invariant reconstruction.  It is
to validate the directional C2 graph through a transverse exchange itinerary
before this phase spike.  The opt-in route now uses the six pair--13 LC
sections $w_r=-3/5,-1/2,-2/5,-3/10,-1/5,0$, with close-unselected-pair step
caps and independent whole-tube audits.  Its common-clock prefix now ends at
$t=167/50$, uniformly before the first oriented section and far before the
exchange spike; a strict graph check requires $w_r<-3/5$ there, and the
Poincare validation remains responsible for proving the actual fiberwise
crossings.  The first five sections and their tubes passed, but sections 4
and 5 enlarged the width-$10^{-12}$ hull to $4.74\times10^{-6}$ and
$1.11\times10^{-5}$, almost entirely additive defect.  Thus transverse timing
alone does not discharge the economic obligation.  The next localized gate
is the opt-in in-chart energy projection after sections 4--6.  The analytic
fiberwise projection lemma already applies; the remaining obligation is a
complete pinned replay proving that the projection actually reduces the
section defect without losing any domain, brake-covering, or collision
margin.

That energy-only replay answered the question negatively.  At section 4 the
hull was $4.73945\times10^{-6}$; energy reconstruction enlarged it to
$2.25401\times10^{-5}$ because uncertainty in the other energy terms was
returned to `h`.  The remaining localized experiment is the stronger joint
projection onto $L=0$, $H=-U_0$, and the defining identity $j_d=\dot I$.
Its fixed-fiber lemma and exact formulas are proved and the opt-in C2 code is
compiled and tested.  If its complete control also enlarges the defect, the
obligation is no longer another ambient-box invariant projection: it is an
intrinsic invariant-manifold graph representation or an exact-section atlas
that never frees these correlations.

The first joint control enlarged the same section hull further to
$2.75922\times10^{-5}$, again in `h`, so projecting $P$ onto $L=0$ before
solving for `h` does not discharge the gate.  The final ambient projection
worth testing is algebraically different: retain `h`, and solve $L=0$ and
$H=-U_0$ for $P$ using the strictly positive-radial square-root branch.  Its
exact fixed-fiber identity, branch checks, CAPD map, and regressions are now
in place.  Failure of that route would trigger the intrinsic-manifold/atlas
obligation described above.

The velocity reconstruction has now failed economically despite strict
branch margins.  Its section-4 image was $7.03178\times10^{-6}$; by section 5
the pre-reset hull was $1.27946\times10^{-5}$ and the second reset gave
$1.91255\times10^{-5}$, all worse than the unprojected control.  Thus the
ambient-projection decision tree is closed.  The active obligation is to
benchmark the audited PG2 one-parameter Poincare graph (thin-anchor
derivative plus explicit Hessian cross terms) across the exchange and final
escape atlas.  A wider theorem requires the same independent C0 tube audit
and terminal certificate; PG2 tightness alone is not a dynamical conclusion.

That PG2 benchmark is now closed negatively at the representation level.  A
masked implementation carrying all twelve first derivatives but only the six
$T,Q,E$ Hessian pairs is fast enough and has a proved Taylor update.  On the
exact width-$10^{-12}$ control it reproduces the same exchange defect:
$1.12393\times10^{-6}$ at $t=3.45$ and $4.43187\times10^{-6}$ at the fourth
minimum.  The active obligation is no longer another Taylor order.  Replace
the componentwise $E$ box by a correlation-bearing remainder--preferably the
existing two-arm CAPD tripleton geometry transported through the Poincare
section--and prove that the resulting graph still contains every parameter
fiber across switch instants.  The minimal gates are: an exact structured-
remainder update lemma, a polynomial/Poincare regression, and the same
width-$10^{-12}$ exchange comparison before any wider campaign.

Three independent adversarial passes audited the incoming-tail theorem. They
found and forced repair of: a nonuniform constant-energy estimate; an invalid
partial-LC-block physical-time bound; unspecified oscillator “actions”; a
noncommuting phase/radius limit; and use of a linearized transverse equation
for a possibly nonaxis solution. The final proof uses the radius-dependent
energy defect $O(Y^{-3})$, exact LC invariants $(E+1,L,K)$, separate endpoint
blocks, the exact intercept subtraction, and reflection-odd mean-value
factorization. All three final passes endorsed the repaired theorem.
