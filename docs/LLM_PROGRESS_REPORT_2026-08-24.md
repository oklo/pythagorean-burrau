# Pythagorean--Burrau research progress report

Date: 2026-08-24
Repository: `/Users/greglaughlin/Projects/pythagorean-burrau`
Current outcome: **major partial theorem; full conjecture unresolved**

This report is written as a standalone handoff for another LLM. It combines
the main research line with the useful results imported from the parallel
Fable worktree. Evidence labels have their literal meanings from
`docs/PROOF_LEDGER.md`; pending computations are not promoted to theorems.

## 1. Exact problem and current answer

For a positive-integer Pythagorean triple

\[
 a^2+b^2=c^2,
\]

put masses \((m_1,m_2,m_3)=(a,b,c)\) at the vertices opposite sides of
length \((a,b,c)\), start all bodies at rest, and evolve the labelled planar
Newtonian three-body problem. The conjecture says that no resulting maximal
classical collision-free solution is periodic.

The full rational conjecture is **not proved**. The stronger assertion for
every real tied parameter is also **not proved**. No rational counterexample
and no real second-brake intersection have been found.

A difficulty-weighted completion estimate is currently about **46%**, with
rough uncertainty of plus or minus 15 percentage points. This measures
progress toward the universal theorem, not the amount of code or manuscript
already written.

### Later exact update: the ordered-syzygy face

The torque-history route has produced one further exact theorem.  If a tied
fundamental-mass orbit reaches a collision-free syzygy with body 3 between
bodies 1 and 2 while retaining the strict launch torque signs, then

\[
 (r_{12}-r_{23})''<0
\]

at that event.  Collinear momentum constraints determine the torque ratio
and the sharp transverse kinetic energy.  Combining them with $H=-U_0$
reduces the only adverse case to a bidegree $(20,6)$ polynomial on the
$(v,z)$ unit square.  Its 147 exact $\mathbb Q(\sqrt2)$ Bernstein
coefficients are 133 negative and 14 zero, so the margin is strictly negative
in the open square.  The test suite independently checks the positive
denominator, positive clearing factor, kinetic minimization, and every
coefficient sign.

This is a significant Level-E boundary theorem, not a global cone theorem.
It does not show that the ordered right/obtuse cone persists until syzygy or
that the first gap decreases throughout the preceding arc.  The two adverse
centrifugal terms are now expressed using a common amplitude
$Z=\ell_{23}^2/r_{12}$ and the single weighted history ratio $\eta$; the
highest-leverage missing lemma is a reachable barrier for $(Z,\eta)$ coupled
to the normalized shape.

The complementary static second-gap claim has now been disproved exactly.
At $u=1/3$ and the collision-free ordered syzygy

\[
 (r_{12},r_{23},r_{31})=\left(1,{697\over700},{3\over700}\right),
\]

there is an exact zero-radial, transverse state with Burrau energy, $P=L=0$,
all three launch torque signs, and $\dot\Delta_2<0$, but

\[
 (r_{23}-r_{31})''
 =-{96354167469624287\over1827657180810}<0.
\]

This state is not claimed reachable from the brake.  It rules out a static
second-face repair and localizes the necessary new theorem to
$Z<Z_*=(\mathfrak g_{23}-\mathfrak g_{31})/(-C_2)$ along reachable states.
The witness has $Z/Z_*=1.3724399581\ldots$, so the required history estimate
must improve the total-energy allowance by a definite amount.

The torque-rate monotonicity problem now has an exact first-order normal
form.  In Newtonian shape time,

\[
 (\log k)_s={W\over\delta}\mathcal A(u,x,y)
 [\eta-h(u,x,y)],qquad \mathcal A>0.
\]

Both $h$ and $\mathcal A$ are explicit rational functions.  Positivity of
$\mathcal A$ on the complete ordered shape--mass cube is certified by 168
exact $\mathbb Q(\sqrt2)$ Bernstein coefficients (134 strict, 34 zero) and
a denominator of the opposite strict sign.  At launch $h-k(0)>0$ by exact
factorization.  Thus $k$ decreases exactly while $\eta<h$; the former
velocity-curvature problem is now the scalar history noncontact problem of
preventing the weighted average $\eta$ from reaching the explicit graph
$h$.  The earlier $u=2/5$ ambient $J'=0$ witness exactly satisfies
$\eta=h$, confirming the reduction independently.

A second global exact certificate proves $h>k$ on the complete strict
ordered cone.  Its degree-$(11,11,2)$ numerator has 432 signed Bernstein
coefficients (317 strict, 115 zero) with the denominator sign handled
exactly.  At a contact $\eta=h$, define explicit rational functions $P,S$.
Then

\[
 W\delta(\eta-h)_s=P-ZS,qquad P<0.
\]

Contacts with $S\ge0$ are automatically safe.  The dangerous region is
exactly $S<0$, where the sharp condition is $Z<Z_J=P/S$.  The energy-normalized
$u=2/5$ ambient first-return witness has
$Z/Z_J=1.05745644351720\ldots$, explaining its positive curvature and proving
that total energy is about $5.75\%$ too weak there.  This reduces the compact
monotonicity route to a reachable amplitude theorem on one explicit contact
surface.

This does not collapse to the second-gap amplitude threshold: exact rational
examples show both $Z_J<Z_2$ and $Z_J>Z_2$.  Any unified history estimate
must control the appropriate minimum of the two, or replace them with a
stronger invariant.

There is now a sharp terminal exception to that interior nonordering.  On
the ordered syzygy $x+y=1$, the collinear momentum constraints and the
explicit torque threshold obey the exact identity

\[
 h=\eta={y(m+1-y)\over(1-y)(n+y)}.
\]

Both $P$ and $S$ vanish there, but each contains the same exact
area-squared factor, so $Z_J=P/S$ has a path-independent rational syzygy
extension.  Four complete bivariate tensor-Bernstein certificates, with
coefficient counts $71/1$, $71/7$, $39/9$, and $274/23$ for strict/zero
coefficients, prove

\[
 0<Z_J^{\rm syz}<Z_2
\]

on the entire tied torque-compatible ordered-syzygy face.  The certificates
also cover the equal-mass edge away from its torque-boundary endpoint.  This
changes the correct noncontact statement: one seeks $\eta<h$ throughout the
positive-area interior, followed by forced equality at terminal syzygy.
Only the sharper $Z_J$ amplitude obligation survives on that face.  The
actual brake-history inequality $Z<Z_J^{\rm syz}$ is still open, so this is
a structural boundary theorem rather than a proof of cone persistence.

The missing terminal amplitude inequality now has an exact kinetic form.
Writing $R=r_{12}$, $q=r_{31}/R$,
$D=mn+mq^2+n(1-q)^2$, and using shape time, one obtains

\[
 2K_\parallel R={R\dot I^2\over4I}+{mnq_s^2\over D},
 \qquad
 FZ+2K_\parallel R=2(U-U_0R).
\]

Consequently $Z<Z_J^{\rm syz}$ is equivalent to

\[
 2K_\parallel R>2U_0(R_J-R),qquad
 R_J={U-FZ_J^{\rm syz}/2\over U_0}.
\]

This is a materially smaller quantitative obligation, but it cannot be
replaced by velocity signs.  There is an explicit $\varepsilon$-scaled
longitudinal velocity ray for which $r_{31}$ decreases,
$r_{23}-r_{31}$ increases, and $\dot I<0$, all strictly, while
$2K_\parallel R=O(\varepsilon^2)\to0$.  Thus a proof must transport a
positive amount of radial/shape kinetic energy from the initial brake, or
prove the scale bound $R\ge R_J$; terminal monotonicity alone is inadequate.

A direct barrier for the second gap still fails even in first-contact form.
An exact $u=1/3$ strict ordered-obtuse state at
$(x,y,\eta)=(499/500,1/20,3/20)$ lies on $Z=Z_*$, has Burrau energy,
$P=L=0$, launch torque signs, decreasing area, and
$k<\eta<k(0)$, yet

\[
 {d\over ds}\log(Z/Z_*)=50.8829734688\ldots>0.
\]

The sign is proved in exact radical arithmetic.  Therefore the next theorem
must use a stronger correlation inherited from the entire brake-launched
history; current values plus the elementary weighted-average envelope are
insufficient.

## 2. Exact reductions already established

The following are proved and should be treated as settled interfaces.

1. Simultaneous mass--length scaling:

   \[
   \widetilde q_i(t)=kq_i(t/k).
   \]

   Hence a triple is periodic iff any common integer multiple is periodic,
   and only primitive triples matter. This is distinct from fixed-mass
   Newtonian spatial scaling.

2. Primitive Euclid parametrization:

   \[
   A(u)={1-u^2\over1+u^2},\qquad
   B(u)={2u\over1+u^2},\qquad u\in\mathbb Q\cap(0,1).
   \]

   The normalized masses are \((A,B,1)\). Leg exchange is

   \[
   u\mapsto {1-u\over1+u},
   \]

   permitting the fundamental interval
   \(0<u\le\sqrt2-1\).

3. Second-brake equivalence: a collision-free free-fall solution is periodic
   iff all labelled velocities vanish again at some \(\tau>0\). The doubled
   segment has strict labelled period \(2\tau\).

4. Initial exact identities:

   - the center of mass is the triangle incenter;
   - \(I_0=abc\), or \(I_0=AB\) after \(c=1\);
   - \(U_0=AB+(AB)^{-1}\), and \(H=-U_0\);
   - the initial Pythagorean defect has the verified strict departure sign
     recorded in `docs/EXACT_REDUCTIONS.md`.

5. The cardinality argument is explicitly rejected as a proof. Analyticity,
   genericity, countability, or measure zero do not exclude rational zeros.

Primary references: `docs/CONJECTURE.md`, `docs/EXACT_REDUCTIONS.md`, and
`docs/CARDINALITY_TRAP.md`.

## 3. Strongest main-line theorems

### 3.1 Infinite Pythagorean subfamilies

The project has proved substantially more than finitely many examples:

- infinitely many open skinny real parameter intervals contain primitive
  Pythagorean parameters whose tied solutions are nonperiodic;
- the explicit family

  \[
  (4n^2-1,\,4n,\,4n^2+1)
  \]

  contains a positive-lower-density set of nonperiodic members;
- for every fixed nonsquare \(d\), the family

  \[
  (4d^2m^4-1,\,4dm^2,\,4d^2m^4+1)
  \]

  contains a positive-lower-density set of nonperiodic members;
- no full labelled brake occurs at a first outer turn in the accumulating
  skinny parabolic layer;
- every fixed sufficiently late restricted resonance has a finite-positive-
  mass neighborhood containing no full labelled brake.

These are computer-assisted/analytic Level-D results, not a proof for all
primitive triples. See rows 116--123 of `docs/PROOF_LEDGER.md` and the skinny
analysis cited there.

### 3.2 Collision-boundary and escape structure

The massless planar endpoint family has several rigorously localized
transverse light--primary collision roots, analytic Levi--Civita normal forms,
and collision-or-escape continuations. Important consequences include:

- transverse collision boundaries persist under sufficiently small
  compatible positive mass;
- infinitely many real tied skinny parameters have terminating classical
  collisions;
- every member of several explicit limiting intervals either collides or
  reaches a strict terminal escape cone;
- regularized continuation is used only to classify branches. A true
  collision terminates the classical solution and is never treated as
  physical continuation.

These results organize the skinny scattering map but do not yet determine
the sign of the exact tied curve relative to every collision graph.

## 4. Correlation-preserving lower-band atlas

The latest main-line advance repairs a severe interval-wrapping problem near
the fourth planar collision root.

### Exact construction

At a rational common clock, the parameter dependence is stored as a shared
CAPD doubleton generator. To reach \(\alpha=A\), append the frozen defect
\(d=A-\alpha\) and multiply the complete two-centre vector field by
\(d/(-p_r)\). Then \(d\alpha/ds=d\), so artificial time one lands exactly
on the section while tracing the same physical orbit. The \(\beta=B\) map
uses \(d/(-p_i)\). Directed interval audits prove the denominators retain the
required signs. Exact symbolic regression tests verify both this
reparametrization and the anchored-graph recenter identity.

### Validated tile

The complete section/bridge chain is validated for

\[
1.264009098938900\le\kappa\le1.264009098939100.
\]

It follows the atlas

\[
\alpha=2\pi\longrightarrow\beta=-1
\longrightarrow\hbox{heavy-binary bridge}
\longrightarrow\hbox{strict terminal escape cones}.
\]

The minimum light--primary squared separation is greater than
`0x1.3d6bbd67dcbafp-5`, and the two terminal margins are strictly positive.
The exact record is
`data/validated_planar_fourth_common_clock_correlated_tile_capd.txt`.

Three independent code audits found and repaired:

- absolute versus relative Poincare-time diagnostics;
- omission of a selected anchor from the derivative hull below the anchor;
- an exactly 500-millisecond branch that skipped its propagation.

Microtiles approach to about \(2.2\times10^{-14}\) above the certified root
box, but no finite overlapping cover reaches the root. Broader trial tiles
still wrap. Thus this is one validated tile, not a new continuum theorem.

Details: `docs/CORRELATION_PRESERVING_SECTION_MAP.md`.

## 5. Fable result incorporated into the main route: brake-event reduction

The most valuable completed Fable contribution is the exact global event
reduction in `docs/FABLE_EVENT_REDUCTION.md`.

Use Jacobi vectors \(X,Y\), reduced masses \(\mu_1,\mu_2\), and

\[
\sigma=\mu_1\overline X\dot X+\mu_2\overline Y\dot Y,
\qquad
\zeta=\mu_1\overline X\dot X-\mu_2\overline Y\dot Y.
\]

Since angular momentum is zero, \(\sigma=\dot I/2\) is real. Away from
\(Y=0\), a labelled brake is equivalent to

\[
\dot I=0,\qquad \zeta=0.
\]

The determinant of this velocity splitting is

\[
4\mu_1^2\mu_2^2|X|^2|Y|^2.
\]

For certificate soundness only the unconditional direction is needed: every
brake forces \(\dot I=0\), \(K=0\), and every brake residual to vanish.

The Lagrange--Jacobi identity on the tied energy shell is

\[
\ddot I=2U-4U_0.
\]

Consequently every second brake has

\[
K=0,\quad U=U_0,\quad \ddot I=-2U_0<0,
\]

so it is a strict local maximum of \(I\), and every separation satisfies

\[
r_{ij}\ge {m_im_j\over U_0}.
\]

At a zero of \(\dot I\) with \(\ddot I\ge0\), one instead has
\(K\ge U_0>0\), uniformly excluding a brake. Folds lie at \(U=2U_0\)
and also carry this kinetic margin.

This yields a rigorous covering rule: on each validated time window it is
enough to prove any one of

\[
\dot I\ne0,\qquad K>0,\qquad \mathcal B\ne0,
\]

and then terminate with the already proved binary--escaper certificate. This
is a genuine Level-E structural reduction. It does not provide a uniform
bound on the number of event branches or the terminal time over the whole
parameter interval.

There is also an exact geometric sharpening. If
$s=\mu_1|X|^2/I$ and $\phi=\arg Y-\arg X$, then at every regular
$\dot I=0$ event
\[
 \zeta=I(\dot s-2is(1-s)\dot\phi),\qquad
 |\zeta|^2=8KI s(1-s).
\]
Thus the planar residual is precisely the shape velocity, and origin
avoidance is equivalently $K=U-U_0>0$. This does not finish the theorem:
$K\ge0$ and a genuine brake is an even-order zero, so no scalar
intermediate-value argument is available.

The exact event tests pass: `tests/fable` currently reports eight passing
tests.

## 6. Fable point certificates: what is and is not promoted

Five committed and archived Fable certificates prove nonperiodicity for the
following primitive triples, in both leg orderings:

| Euclid parameter | Primitive triple | Evidence |
|---|---|---|
| \(2/5\) | \((21,20,29)\) | MPFR CAPD event cover + terminal escape |
| \(33/80\) | \((5311,5280,7489)\) | MPFR CAPD event cover + terminal escape |
| \(41/100\) | \((8319,8200,11681)\) | MPFR CAPD event cover + terminal escape |
| \(81/200\) | \((33439,32400,46561)\) | native CAPD event cover + terminal escape |
| \(5/13\) | \((72,65,97)\) | MPFR CAPD event cover + terminal escape |

An independent main-worktree replay of \(u=2/5\) completed with
`PASS_TIED_EVENT p=2 q=5`, 613 accepted steps, escape time
\(0.80452270507812507\), escape margin greater than \(0.22715\), and final
hull width below \(1.46\times10^{-19}\). The current verifier's newer
position-only energy test excludes all candidate steps before scalar-event
counting, so it reports zero event steps instead of the older archived
diagnostic count four. This diagnostic change does not weaken the proof.

The Fable worktree also contains an untracked passing log for \(u=5/14\),
corresponding to \((171,140,221)\). It lacks a committed theorem record and
fully specified replay provenance, so the main ledger does **not yet promote
it**. The handoff says “seven point theorems,” but the available committed
records support five, plus this one untracked candidate. That count
discrepancy is recorded rather than guessed away.

Point certificates are valuable exact instances and test the machinery in
the compact middle, but finitely many points make little direct progress on
the universal quantifier.

## 7. Status of the classical 3:4:5 Burrau problem

The exact \(u=1/3\) orbit, equivalent by leg exchange to the historical
\(3{:}4{:}5\) ordering, is **not yet promoted to a theorem**.

Fable constructed a multipassage Levi--Civita covering verifier specialized
to its repeated deep pair-\(\{1,3\}\) encounters. The handoff reports several
high-precision runs in progress and predicts a pass, but no archived output
with a final `PASS_BURRAU_LC` or `PASS_BURRAU_EVENT` marker was found.
`docs/FABLE_BURRAU_THEOREM.md` correctly remains marked pending.

An audit of the LC architecture confirms the relative-coordinate algebra,
LC equations, brake-free close-encounter zone, per-step noncollision check,
and terminal escape interface. It also found two localized proof obligations
in the damped chart entry/exit write. First, the exponentially inflated
forcing interval was not checked at runtime to contain the exact overwrite
forcing for the actual state enclosure. The main worktree now computes the
exact admissible target-gap bound

\[
|T-y_0|\le
{\varepsilon(1-e^{-400\tau})\over400e^{-400\tau}}
\]

from a rigorous lower construction duration and rejects the run unless every
chart coordinate satisfies it. Second, an independent adversarial pass found
that CAPD target overlap did not certify the initially used nominal lower
duration. The final code audits after propagation with
$\tau_-=(t_{\rm end})_{\rm left}-(t_{\rm start})_{\rm right}>0$, applied to
the saved initial construction state. The repair compiles, has an exact
symbolic regression, and a fresh post-repair 256-bit smoke replay passed four
successive entry/exit cycles, including the deep $t\approx3.166$ encounter.
That run was stopped after physical time $3.1670113440$ and is only a
finite-segment validation; a terminal pass remains required. Therefore the
LC verifier is useful machinery, not yet a completed
\(3{:}4{:}5\) certificate.

A fresh 512-bit production replay is now beyond that smoke horizon. It
crossed the deep passage near $t=3.166$ in 141 LC steps, reconstructed the
physical state with hull width below $6.7\times10^{-61}$, and subsequently
crossed additional certified LC passages near $t=4.593$ and $t=5.555$.
The run remains active and has not yet reached the terminal escape marker, so
this is validated finite-segment progress, not a promoted theorem.

### 7.1 Nearby periodic-family intersection audit

A new two-mass continuation sharpens the $F_{30}$ audit. Solving the three
second-brake equations and both mass--opposite-side equations on that nearby
periodic family gives an ordinary-numerical general Burrau candidate with
\[
 (m_1,m_2,m_3)\approx(0.594811646571,0.801774973308,1),
\]
but, in a global pair-$23$ Levi--Civita shooting formulation,
\[
 m_1^2+m_2^2-1\approx-0.0033559972648.
\]
Its five-equation shooting Jacobian has ordinary smallest singular value
about $0.199$, so this intersection appears isolated and locally separated
from the Pythagorean circle. Independent regularized DOP853 and implicit
Radau solves agree to roughly $10^{-13}$ in the five shooting parameters.
The global chart also resolves a deeper ordinary minimum separation near
$5.0009\times10^{-4}$ which coarse physical-time sampling missed. Exact
symbolic tests verify the global LC equations and all initial/side parameter
tangents. A low-precision interval center run passed the deepest encounter
but wrapped later at scaled time $0.542$; a higher-precision replay is in
progress. This is not yet a validated periodic existence or nonintersection
theorem.

## 8. Why the universal theorem remains hard

The Fable event theorem sharpens the target but exposes the remaining global
problem. On regular maximum branches, the conjecture asks whether the planar
analytic curve

\[
u\mapsto\zeta(u,t_k(u))\in\mathbb C
\]

ever reaches the origin. There is one parameter and two scalar residual
components, matching the original overdetermined heuristic, but analyticity
and dimension count do not prove origin avoidance.

Validated computations can cover individual points and some open intervals.
They cannot plausibly cover the entire compact middle by brute force:
through-encounter parameter amplification reaches approximately
\(3\times10^8\), late-time Lyapunov amplification is around \(10^{10}\),
and terminal times diverge near escape boundaries. A universal proof needs a
structural event-branch obstruction, a global topological invariant, or an
exact arithmetic exclusion after real intersections are classified.

Signed maximum-event diagnostics also rule out one oversimplified structural
idea. On the single $u=1/3$ orbit, values of $\zeta$ at strict maxima occupy
all four quadrants, and three early values have the origin in their ordinary
convex hull. Consequently no fixed homogeneous real linear projection of
$\zeta$ can be sign-definite across all maxima. A viable theorem must be
branch-dependent, nonlinear, or topological rather than a fixed quadrant
rule.

Subsequent validation sharpened both live computational routes.  The
$u=1/3$ 512-bit multipassage run reached a certified LC exit near physical
time $8.24317$, but its physical hull later widened to about $148$ by
$t\simeq8.33807$ and was stopped without a terminal marker.  Separately, the
global pair-$23$ F30 point center completed its entire regularized half-orbit
in 2351 rigorous steps.  Its swept squared-separation lower bound is
$1.22160\times10^{-7}$ and its three intrinsic endpoint residual intervals
have widths below $9.3\times10^{-10}$.  This validates the fixed center
segment only; a $C^1$ interval-Newton/Krawczyk inclusion is still required.

The exact reduction has also gained a torque-reversal lemma.  On every strict
fundamental parameter, a hypothetical second brake forces all three cyclic
pair-torque integrands to reverse their initial signs $(-,+,-)$.  Before a
syzygy this requires all three pairwise mutual-distance orderings to reverse
at some (not necessarily common) times.  This is a new global necessary event
condition, not yet an exclusion theorem.

The uniform fourth-defect and initial area-acceleration signs no longer depend
on computer-assisted Sturm arguments.  After setting $t=2u$, respectively
all 21 and all 11 rational coefficients of their numerators in the Bernstein
basis on $[0,1]$ are strictly negative. Positivity and partition of unity of
that basis give elementary analytic proofs of $D^{(4)}(0)<0$ and
$\ddot\Delta_2(0)<0$ on the larger interval $0\le u\le1/2$.

The exact defect jet now extends to sixth order.  A direct even force-series
recurrence produces a degree-30 numerator $R_{30}$, and all 31 of its exact
rational Bernstein coefficients on $[0,1/2]$ are positive.  Because the
closed formula has an overall minus sign, $D^{(6)}(0)<0$ analytically on the
whole fundamental interval.  No global Taylor-remainder estimate is claimed.

The torque route now has a more focused ordering target. Exact Newton
formulas prove $(r_{12}-r_{23})''(0)<0$ and
$(r_{23}-r_{31})''(0)>0$ throughout the strict fundamental interval. A
bounded ordinary probe preserved $r_{12}>r_{23}>r_{31}$ to first syzygy at
seven middle parameters, which would fix the syzygy type if promoted
globally. That persistence is still conjectural and loses uniformity near the
skinny endpoint.

Away from syzygy the torque program now has its own exact brake residual.
At zero total momentum and angular momentum,
$(\ell_{12},\ell_{23},\dot I)=0$ is equivalent to all labelled velocities
vanishing. Thus a regular nonsyzygy maximum branch needs only avoid the origin
in the signed plane $(\ell_{12},\ell_{23})$. The proof explicitly fails at
syzygy, where unequal longitudinal velocities give a counterexample and the
global Hopf residual remains necessary.

The first falsification test is already informative: along the single
$u=1/3$ trajectory, maximum-event values of $(\ell_{12},\ell_{23})$ enter all
four quadrants, and three have the origin in their ordinary convex hull.
Therefore this exact residual does not resurrect a universal fixed-linear-sign
proof. Its remaining advantage is the exact torque integral evolution, which
supports branch-wise winding or comparison of the two cancellation times.

An exact determinant now relates the torque residual to the earlier complex
shape residual. On an $I$ event its configuration-dependent linear map has
determinant $-\alpha(X\times Y)(1+\kappa|X|^2/|Y|^2)$. Thus the two residuals
are invertible recharts away from syzygy and lose rank precisely there; the
torque formulation contributes evolution equations, not a different zero
set.

One global-in-shape inequality now supports the ordering route.  Exact
tensor-Bernstein arithmetic on a complete cube parameterization proves that
the gravitational radial contribution always satisfies
$\mathfrak g_{23}-\mathfrak g_{31}>0$ whenever
$r_{12}>r_{23}>r_{31}$ and $0<u<\sqrt2-1$. All 168 algebraic coefficients
are nonnegative and 137 are positive. The only remaining term in the second
gap acceleration is the signed centrifugal difference, which ordinary data
show can be negative but not large enough to overturn gravity before first
syzygy.

The complementary force inequality is also proved on the complete ordered
right/obtuse subcone: $\mathfrak g_{12}-\mathfrak g_{23}<0$. Its exact cube
certificate has 168 nonpositive Bernstein coefficients, 150 strictly
negative. Thus gravity points into both side-order faces. The remaining cone
problem is purely velocity-dependent plus persistence of obtuseness: two
centrifugal differences must be bounded by the certified force margins.

The strongest instantaneous energy repair has been derived and exactly
falsified.  A Jacobi Gram inverse gives the optimal minimum kinetic energy at
fixed $(L,\ell_{23},\ell_{31})$, hence the sharp total-energy bound compatible
with the pre-syzygy torque signs.  At the exact interior cube point
$(s,w,v,h)=(99/100,10^{-6},99/100,10^{-6})$, however, the resulting first-gap
upper margin is $93.2280669052696\ldots>0$.  This state is not claimed
reachable from the initial brake.  Its role is to prove that current shape,
energy, zero angular momentum, and torque signs do not suffice: the cone route
must exploit the integrated torque history or another reachability invariant.

That history has now been compressed to one scalar comparison.  With
$\eta=(m_1/m_2)(-\ell_{31}/\ell_{23})$ and
$k=(r_{23}^{-3}-r_{12}^{-3})/(r_{31}^{-3}-r_{12}^{-3})$, exact quotient
differentiation gives $\dot\eta=(F/{\cal A})(k-\eta)$. Thus a proof that $k$
decreases would automatically trap the nonlocal torque ratio between its
current and launch values.  A new exact cube certificate proves that gravity
contributes strictly negatively to $(\log k)''$: its degree-$(9,9,2)$
numerator has 300 nonnegative exact Bernstein coefficients, 268 positive,
over a negative denominator.  The full launch curvature is also negative by
an elementary factorization.  The unresolved term is now the velocity
Hessian along brake-reachable states; ordinary trajectories keep the full
curvature negative to first syzygy, but this has not been proved.

Even a static first-return repair is now excluded exactly.  At $u=2/5$ and
the strict ordered obtuse shape $(r_{12},r_{23},r_{31})=(1,39/40,1/30)$,
exact elimination gives an $L=(\log k)'=0$ velocity with torque signs
$(-,+,-)$ and positive velocity curvature.  After scaling to $r_{12}=1/2$
and imposing $H=-U_0$, the full curvature is still positive.  This state is
not claimed reachable from the Burrau brake.  It proves that the missing
monotonicity lemma must retain integrated trajectory history even at a
hypothetical first return of $(\log k)'$ to zero.

The first full F30 $C^1$ parameter-box run did not complete.  At radius
$10^{-8}$ it wrapped at scaled time $0.225958$, with pair-energy width already
about $517$, although the fixed center is regular and completes the whole
half-orbit.  This cleanly identifies a set-representation failure rather than
a dynamical singularity.  The proposed repair was to tighten the rigorous
point residual enough to use a radius-$10^{-10}$ box.  That test has resolved
negatively: halving the maximum step completed collision-free but accumulated residual radii up to
$1.86\times10^{-6}$, worse than the earlier run.  The next credible F30
calculation is therefore sectioned multiple shooting or equivalent
reconditioning, not another one-piece smaller-box replay.

## 9. Active routes and next actions

Primary route:

1. carry the now-audited multipassage LC verifier to a terminal
   \(3{:}4{:}5\) certificate or a localized failure;
2. validate the isolated non-Pythagorean $F_{30}$ mass--side intersection if
   it becomes relevant to ruling out the nearest known periodic family;
3. formulate maximum-event branches globally and search for a signed
   Wronskian, winding, or collision-order invariant forcing
   \(\zeta\ne0\);
4. combine that event obstruction with the existing skinny asymptotics and
   terminal escape certificate;
5. make the finite-positive-mass/tied-family transfer effective.

Fallback route:

1. finish a finite correlation-preserving atlas from the fourth planar
   collision root to the existing 131-tile common-clock continuum;
2. use it only where it supplies an effective tied-family entry estimate,
   rather than treating the massless cover itself as the goal.

## 10. Reproduction commands

Run the symbolic/unit tests:

```bash
cd /Users/greglaughlin/Projects/pythagorean-burrau
UV_CACHE_DIR=/private/tmp/pythagorean-uv-cache uv run pytest -q
```

Replay the correlation-preserving limiting tile:

```bash
bash scripts/run_capd_planar_light_collision_newton.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native \
  --fourth-common-clock-beta-atto-tile 44000000 100000 1
```

Replay the independently checked \(u=2/5\) point theorem:

```bash
bash scripts/fable_run_capd_tied_event.sh \
  /private/tmp/fable-capd /private/tmp/fable-capd/build-mp \
  certify 2 5 1.8 256 1e-30 30 3 1 2 4 1 0.7 1 10
```

Compile/run the pending LC Burrau verifier after committing the audited
damped-write repair:

```bash
bash scripts/fable_run_capd_burrau_lc.sh \
  /private/tmp/fable-capd /private/tmp/fable-capd/build-mp \
  512 1e-100 100
```

CAPD is pinned at commit
`731079217a9254ea2948d742df2b170895effe7f`.

## 11. Bottom line

The project has a substantial collection of exact reductions, rigorous
collision/escape geometry, infinite nonperiodic Pythagorean subfamilies, an
explicit lower-band validated tile, an exact global event-covering theorem,
and five committed named middle-parameter certificates. It has neither a
proof for every rational parameter nor a counterexample. The most promising
new formulation is now: prove that every analytic branch of strict
\(I\)-maxima along the tied curve avoids the origin in the complex
\(\zeta\)-plane, with close encounters handled by validated LC charts and
future motion terminated by the binary--escaper certificate.
