# Stopping-point handoff — 2026-08-26

## Executive outcome

**Classification: MAJOR PARTIAL THEOREM / STRUCTURAL REDUCTION.**

The full rational Pythagorean--Burrau nonperiodicity conjecture is not
resolved.  The stronger real conjecture is also not resolved.  No exact real
second-brake intersection has been found, and no rational counterexample
candidate has been found.

This stopping point adds a genuine Level-E reduction.  The torque-history
noncontact problem is now an exact scalar forced linear equation, and a
one-switch theorem for one explicit rational forcing function would close the
pre-syzygy torque obstruction.  Exact witnesses simultaneously retire three
plausible but false pointwise invariant-region arguments.  The result is not a
universal nonperiodicity proof, but it materially narrows what such a proof
must use: trajectory history rather than additional static signs.

The calibrated completion estimate remains approximately **25%**, with a
credible range of **15--35%**.  The uncertainty is large because the missing
global bridge could yield to the new scalar reduction or could require a
substantially different idea.

## Exact conjecture status

| Question | Status at handoff |
|---|---|
| Full rational conjecture | CONJECTURAL |
| Strong real conjecture | CONJECTURAL |
| Exact real second-brake intersection found | No |
| Rational second-brake candidate found | No |
| Rigorous rational counterexample | No |
| Infinite rigorous subfamilies excluded | Yes |
| Nonempty rigorous real interval excluded | Yes |
| Global middle-parameter theorem | No |

All return statements in the repository are labelled, inertial, classical,
and collision-free.  Near-collisions are followed as smooth Newtonian
motion.  Levi--Civita regularization is used only as a mathematical chart; a
true classical collision remains terminal.

## Strongest existing partial results

The main durable results preceding this stopping point are:

1. The primitive scaling reduction, rational Euclid parametrization, leg-swap
   involution, second-brake equivalence, and coordinate-independent reduced
   brake residual are proved exactly.
2. Infinitely many open skinny real parameter intervals are proved
   nonperiodic.  Hence infinitely many primitive Pythagorean triples satisfy
   the conjecture.
3. A positive-lower-density subset of the primitive family
   $(4n^2-1,4n,4n^2+1)$ is proved nonperiodic, with extensions to fixed
   nonsquare-$d$ polynomial families.
4. Every sufficiently near-isosceles one-sided tied member is proved
   nonperiodic on an existential real neighborhood.  The symmetric endpoint
   collision is used only as a regularized comparison orbit; nearby members
   are treated classically through their noncolliding near passage.
5. A committed, adversarially reviewed CAPD theorem proves every real
   \[
   u\in[0.29,0.2900000101]
   \]
   nonperiodic.  This interval contains infinitely many rational Euclid
   parameters and therefore infinitely many primitive Pythagorean triples.
6. Affine-generator propagation has produced successful exact-endpoint
   certificate runs covering the gap-free candidate interval
   $[0.29,0.290002]$.  These remain **VALIDATED NUMERICAL RESULT /
   COMPUTER-ASSISTED THEOREM CANDIDATE**, not promoted theorem rows, because
   the independent audit of the affine-generator algebra and pinned-source
   semantics is still outstanding.

The detailed theorem inventory and evidence labels are in `PROOF_LEDGER.md`.

## New exact forced-lag reduction

Use the established ordered variables

\[
 R=r_{12},\qquad x={r_{23}\over R},\qquad y={r_{31}\over R},
 \qquad 1>x>y>0,qquad x+y>1,
\]

with normalized twice-area $\delta>0$, torque amplitude
$W=\ell_{23}/\sqrt R>0$, and $Z=W^2$.  The instantaneous torque ratio and
weighted history ratio are

\[
 k={x^{-3}-1\over y^{-3}-1},
 \qquad
 \eta={m\over n}{-\ell_{31}\over\ell_{23}}.
\]

Earlier exact work proved

\[
 \eta_s={f\over W}(k-\eta),
 \qquad
 (\log k)_s={W\over\delta}\mathcal A(\eta-h),
\]

where

\[
 f=m\delta(y^{-3}-1)>0,qquad \mathcal A>0,qquad h>k
\]

throughout the strict ordered cone.  Define

\[
 d=h-k>0,qquad e=\eta-k,qquad w=h-\eta=d-e,
\]

and

\[
 \lambda={f\over W}>0,qquad
 c={kW\mathcal A\over\delta}>0.
\]

Direct exact elimination gives

\[
 \boxed{e_s+(\lambda+c)e=cd},\qquad e(0)=0,
\]

so

\[
 \boxed{
 e(s)=\int_0^s c(\tau)d(\tau)
 \exp\!\left[-\int_\tau^s(\lambda+c)(\xi)\,d\xi\right]d\tau.}
\]

The desired gap obeys

\[
 \boxed{w_s+(\lambda+c)w=q},
 \qquad q=d_s+\lambda d.
\]

With

\[
 X={\delta x_s\over W},\qquad
 Y={\delta y_s\over W},\qquad
 D=d_xX+d_yY,
\]

the forcing sign is the sign of the explicit rational expression

\[
 \boxed{E:=W\delta q=ZD+m\delta^2(y^{-3}-1)d.}
\]

At a torque contact $\eta=h$, the prior contact formula is recovered exactly:

\[
 E=ZS-P.
\]

Therefore the safe contact-amplitude condition $Z<Z_J=P/S$ on the dangerous
region $S<0$ is precisely $E>0$.

## Conditional one-switch theorem

**Theorem (PROVED ANALYTICALLY, conditional on a reachable sign property).**
Let an ordered collision-free arc start with $w>0$ and end at its first
syzygy with the forced terminal equality $w=0$.  If $q$ changes sign at most
once and the change is strictly from positive to negative, then
$w>0$ at every interior time.

Proof: with $M(s)=\exp\int_0^s(\lambda+c)$,

\[
 (Mw)_s=Mq.
\]

Thus $Mw$ first increases and then decreases strictly to zero, and cannot
have an earlier zero.

This is the smallest current analytic target:

> Prove that $E$ has at most one positive-to-negative sign switch on every
> tied brake-reachable ordered pre-syzygy arc.

It is a statement about the two-dimensional family of reachable histories,
not the full ambient energy manifold.

## Exact falsifications that constrain the next proof

### Nonnegative forcing is too strong

Ordinary high-accuracy integrations at representative middle parameters show
$E$ becoming negative before the terminal syzygy.  Therefore $E\ge0$ on the
whole arc is not the right theorem.  For $u=1/4,1/3,19/50,2/5$, the observed
sign pattern was one block $(+,-)$, which is consistent with the one-switch
theorem.  The $u=1/5$ endpoint became numerically near-degenerate and showed
an unreliable extra terminal block; no universality is inferred from these
ordinary integrations.

### Pointwise one-way crossing of $E=0$ is false

There is an exact rational state

\[
 u={2\over5},\quad x={1957\over2000},\quad y={323\over2000},
 \quad\eta={3\over80},\quad\gamma=-{1\over100},
\]

where $\gamma=(\log R)_s\delta/W$.  It satisfies:

- strict ordered obtuse shape;
- $k<\eta<h$ and $D<0$;
- contraction, decreasing area, and decreasing total moment of inertia;
- pair-angular-momentum signs matching the launch signs $(-,+,-)$;
- exact Burrau energy after a positive common scale change;
- $E=0$;
- but $W\delta E_s>0$.

The normalized derivative is approximately $1.35064007$.  This state is not
claimed reachable from the initial brake.  It proves that the listed static
constraints do not make the $E=0$ surface one-way.

### Buffered torque-contact barrier is false

For $C=S/P=1/Z_J$, the natural buffer

\[
 b=h-\eta+y(1-ZC)
\]

encodes the sharp amplitude condition at contact.  It is not invariant.
The exact rational tied state

\[
 u={207\over500},\quad x={229\over320},\quad y={131\over320},
 \quad \eta=k+{3\over4}(h-k),\quad\gamma=-{1\over1000}
\]

is ordered, obtuse, contracting, energy-compatible, and has the launch torque
signs, but $b=0$ and $W\delta b_s<0$ (approximately $-6.0909585$).
It too is only an ambient obstruction.

### First contraction-threshold repair is not pointwise invariant

The exact normalized contraction equation is

\[
W\delta\gamma_s=
 \gamma^2Z+\delta^2\left[
 Z{(1-\eta)^2\over m^2}+g_{12}
 -\gamma m(y^{-3}-1)\right]
 +{\gamma Z\over2\delta^2}
 \bigl[(\delta^2)_xX+(\delta^2)_yY\bigr],
\]

where

\[
g_{12}=-(m+n)-{1+y^2-x^2\over2y^3}
             -{1+x^2-y^2\over2x^3}.
\]

On $E=0$ the crossing orientation is affine in $\gamma$, defining a rational
threshold $\Gamma(x,y,\eta)$.  Bounded ordinary probes find both boundary
orientations for $\gamma-\Gamma$, even after imposing energy.  This rules out
the first naive pointwise contraction barrier, but not an integrated
contraction estimate from the brake.

## Exact static domain chart

The full tied ordered right/obtuse history strip now has a four-cube
parametrization over $\mathbb Q(\sqrt2)$.  Let

\[
u=(\sqrt2-1)v,\quad t=(\sqrt2-1)a,
\quad x_0={1-t^2\over1+t^2},\quad y_0={2t\over1+t^2},
\]

\[
r_*={1+\rho(x_0+y_0-1)\over x_0+y_0},
\quad x=r_*x_0,\quad y=r_*y_0,
\quad\eta=k+r(h-k),
\]

with $(v,a,\rho,r)\in[0,1]^4$.  The face $\rho=0$ is syzygy and
$\rho=1$ is the right-triangle boundary.  This chart is intended for future
Bernstein or interval certificates; no global sign claim for $E_s$ follows
from it.

## Incorporation of the Fable work

The useful Fable results have been incorporated into the main repository's
theorem architecture rather than treated as nearby numerical evidence.

- The event reduction proves that every brake is a strict $I$-maximum with
  $U=U_0$ and explicit collision separation.  A finite validated cover may
  exclude a brake on each step using $\dot I\ne0$, $K>0$, or a full brake
  residual before invoking the terminal escape-or-collision theorem.
- The committed theorem on $[0.29,0.2900000101]$ consists of a correlated
  base certificate and 100 exact-endpoint adjacent CAPD tiles.  It survived
  independent adversarial review and repairs.
- The affine-generator representation removes the former width-independent
  exchange floor.  Exact-endpoint runs through $[0.29,0.290002]$ pass the
  complete 85-image itinerary, all swept-tube audits, and the terminal
  certificate.  The independent affine algebra/source audit remains the
  promotion gate.
- Widening or tiling this tiny neighborhood is useful theorem production but
  is not the primary global proof strategy.  Increasing a $10^{-8}$ interval
  to $10^{-6}$ does not materially change the completion fraction toward a
  theorem over all rational $u$.

## Files added or materially changed at this stopping point

- `src/symbolic/mutual_distances.py`
  - forced-lag and Volterra reduction;
  - exact normalized kinetic quadratic;
  - exact lag-envelope crossing dynamics;
  - normalized contraction dynamics;
  - contraction-threshold algebra;
  - ordered-obtuse history cube;
  - two exact ambient obstruction constructors.
- `tests/test_mutual_distances.py`
  - exact forced-equation residual;
  - kinetic/Gram minimum identity;
  - normalized contraction chain rule;
  - envelope and buffered-barrier chain rules;
  - exact witness sign and energy checks;
  - four-cube boundary-face identities.
- `scripts/probe_torque_ordering.py`
  - reports envelope switches and contraction-threshold margins on ordinary
    first-syzygy arcs.
- `scripts/probe_history_buffer.py`
  - bounded falsification probe for the buffered contact barrier.
- `scripts/probe_history_envelope_switch.py`
  - bounded probe of $E=0$ orientation and energy compatibility.
- `scripts/probe_contraction_barrier.py`
  - bounded probe of the normalized contraction threshold.
- `docs/EXACT_REDUCTIONS.md`, `PROOF_LEDGER.md`, `PROOF_OBLIGATIONS.md`,
  `FAILED_ROUTES.md`, `EXPERIMENT_LOG.md`, and `STATUS.md`
  - exact statements, evidence labels, obligations, and retired routes.
- `paper/main.tex`
  - forced-lag reduction, one-switch lemma, and scope of the exact ambient
    witnesses.

The formatter touched the complete two large Python files containing the new
symbolic routines and tests, so their raw line diff is larger than the
semantic change.  Review with `git diff -w` when isolating mathematical edits.

## Verification at handoff

The complete mutual-distance symbolic regression passed:

```text
41 passed in 46.06s
```

Reproduction:

```bash
cd /Users/greglaughlin/Projects/pythagorean-burrau
env UV_CACHE_DIR=/private/tmp/pythagorean-uv-cache \
  PYTHONDONTWRITEBYTECODE=1 \
  uv run pytest -p no:cacheprovider tests/test_mutual_distances.py
```

The six changed Python files also pass Ruff lint.  For the diagnostic probes:

```bash
cd /Users/greglaughlin/Projects/pythagorean-burrau
PYTHONPATH=. uv run python scripts/probe_torque_ordering.py
PYTHONPATH=. uv run python scripts/probe_history_buffer.py
PYTHONPATH=. uv run python scripts/probe_history_envelope_switch.py
PYTHONPATH=. uv run python scripts/probe_contraction_barrier.py
```

These scripts produce **ORDINARY NUMERICAL EVIDENCE** only.  The exact witness
claims are checked by the SymPy tests, not established by the probes.

## Remaining proof obligations

1. Prove the reachable one-switch property for $E$, or derive a stronger
   integrated inequality that implies $h-\eta>0$ up to terminal syzygy.
2. Extend the consequence beyond first syzygy through every close encounter,
   or connect it to an escape/collision classification that precludes later
   brakes.
3. Bridge the compact middle interval not covered by the skinny and
   near-isosceles theorems.  A validated continuum cover is legitimate, but
   isolated tiny tiles are not a global bridge.
4. Maintain uniform control as $u\to0$ and through the rank-changing
   isosceles endpoint.  Existing endpoint theorems cover infinite
   subfamilies, not the entire open interval.
5. If a real second-brake intersection is ever located, prove its existence
   rigorously and then determine whether its parameter can be rational.  No
   arithmetic argument is currently earned by the dynamics.
6. Complete the independent audit before promoting the affine-generator
   candidate interval beyond $0.2900000101$.

## Highest-leverage next action

Derive a **trajectory-integrated contraction/amplitude estimate at the first
zero of $E$**.  At such a zero, the orientation condition can be written as
$\gamma<\Gamma(x,y,\eta)$.  Actual middle brake trajectories have ordinary
margins of order $1.5$--$3.8$, while exact ambient witnesses violate the
condition.  The needed discriminator must therefore arise from the initial
brake history—most plausibly by integrating dilational momentum or the
Lagrange--Jacobi/virial equation to the first $E$ crossing—rather than by
adding another pointwise sign assumption.

If an analytic inequality cannot be closed, the same scalar statement is a
well-conditioned target for a parameter-uniform validated first-arc cover:
certify the sign itinerary of $E$ and the terminal equality using geometric
sections, then combine it with the existing event and terminal escape
theorems.  This would be more strategically meaningful than merely widening
the existing $u\simeq0.29$ tile.

## Adversarial warnings

- The one-switch lemma is conditional; it does not prove that the switch
  property holds.
- The exact obstruction states are ambient and are not known reachable.
- Ordinary sign blocks do not establish a sign theorem.
- Energy compatibility after a positive scale change is not reachability.
- A terminal syzygy forces $h=\eta$; the desired theorem is strict only in
  the positive-area interior.
- Near-collision is not collision, and regularized continuation is not a
  classical physical continuation.
- The affine interval beyond $0.2900000101$ remains audit-gated.
- Countability, genericity, analyticity, and dimension count do not exclude
  rational return parameters.

## Recommended debrief framing

The honest summary is: the project has substantial exact structure and
several infinite rigorous subfamilies, but the central universal bridge is
still missing.  This final session did not raise the completion estimate; it
converted a vague “history constraint” into a precise scalar one-switch
obligation and proved, by exact counterexamples, why several simpler local
barriers cannot solve it.  That is useful research progress, not a resolution.
