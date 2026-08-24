# Fable route decision

Date: 2026-08-23.
Checkpoint payload commit: `4e28e91e4b69937b777501cba942ee26186cc139`
(manifest child `ba9289f`).  Branch: `fable/global-brake-obstruction`.
Intake verification: `uv sync --frozen` rebuilt the environment in this
worktree with a separate UV cache; `pytest -q` reproduced `92 passed`.

## Chosen primary program

Global brake-event topology on the compact middle interval (Section 5 of the
assignment), organized by the following exact splitting, which is new relative
to the checkpoint's `(R_1,R_2,S)` chart in `BRAKE_MAP.md`.

Work in the center-of-mass frame with unweighted Jacobi vectors
$X=q_2-q_1$, $Y=q_3-(m_1q_1+m_2q_2)/(m_1+m_2)$, reduced masses
$\mu_1,\mu_2$, and identify $\mathbb R^2\cong\mathbb C$.  Total angular
momentum vanishes identically.  Define

\[
 \zeta=\mu_1\overline X\dot X-\mu_2\overline Y\dot Y\in\mathbb C .
\]

Because $L=\operatorname{Im}(\mu_1\overline X\dot X+\mu_2\overline Y\dot Y)=0$
and $\dot I/2=\operatorname{Re}(\mu_1\overline X\dot X+\mu_2\overline Y\dot Y)$,
the three-component Hopf residual of `CONJECTURE.md` is, away from $XY=0$,
exactly equivalent to the pair

\[
 \dot I=0
 \qquad\text{and}\qquad
 \zeta=0 .
\]

($X=0$ is a binary collision; $Y=0$ is an interior syzygy where the Hopf
residual itself remains the arbiter — the certificate below always tests the
full Hopf residual, so no chart gap enters the proof.)

## Exact theorem I intend to prove

**Theorem A (event reduction).**  For every real $u$ in the fundamental
interval and every collision-free $t>0$: a second labelled brake at $(u,t)$
occurs iff $\dot I(u,t)=0$ and $\zeta(u,t)=0$ (with the Hopf residual
replacing $\zeta$ on the measure-zero chart locus $Y=0$).  Every such brake
is a strict local maximum of $I$ in time ($\ddot I=-2U_0<0$), lies on the
energy shell $U=U_0$, and satisfies the separation bounds
$r_{ij}\ge m_im_j/U_0$ for all three pairs.  More generally every local
maximum of $I$ satisfies $U<2U_0$, hence $r_{ij}>m_im_j/(2U_0)$.

**Theorem B (event-set structure).**  The brake-candidate event set is the
union of the $I$-apocenter curves $\{\dot I=0,\ \ddot I<0\}$ in the $(u,t)$
strip.  Every degenerate event $\dot I=\ddot I=0$ lies on the
locus $U=2U_0$, which is disjoint from the brake shell $U=U_0$; therefore no
brake occurs at such an event, and on each regular branch the conjecture is exactly
the statement that the continuous planar curve
$u\mapsto\zeta(u,t_k(u))\in\mathbb C$ avoids the origin.  Collision and
near-collision boundaries never meet the event set (Theorem A's separation
bound); on a fixed compact parameter interval away from $u=0$, event
enclosures are therefore uniformly separated from collision.  The bound
degenerates at the skinny endpoint.

**Theorem C (certificate soundness).**  Fix a compact parameter interval
$[u_-,u_+]$ and for each covering box suppose validated computation produces
a finite time partition $0=t_0<t_1<\dots<t_N$ such that on each window at
least one of the following holds with interval margins:
(i) $\dot I\ne0$ on the window; (ii) the kinetic energy $K>0$ on the window;
(iii) $|\mathcal B|>0$ on the window; and at $t_N$ either the terminal
binary--escaper certificate of `ESCAPE_CRITERIA.md` fires or a rigorous
collision termination is established.  Then no $u$ in the covered interval
admits a second labelled brake, i.e. the conjecture holds for every real
(hence every rational) parameter in $[u_-,u_+]$.

Instantiating Theorem C on explicit compact intervals — first a validated
run at the historical Burrau parameter $u=1/3$ (the $3{:}4{:}5$ problem),
then an interval neighborhood — is the concrete computational goal.

## Why this combines with existing results

The checkpoint already owns both singular endpoints: the live agent's
skinny program controls $u\to0$ (Level-D open intervals, first-turn
exclusion, projective family), and the isosceles-right endpoint has a
finite-collision theorem.  What is missing is precisely a mechanism for the
compact middle range, where no asymptotic parameter exists.  Theorems A--C
convert that range into a finite covering problem whose event set is
uniformly separated from collisions, whose windows terminate in the already
proved escape-or-collision certificate, and whose per-window conditions are
strict inequalities checkable by interval arithmetic.  A completed covering
of $[u_-,u_+]$ plus the endpoint programs would assemble into Outcome D; the
reduction theorems alone are an Outcome-E structural theorem.  If a covering
fails persistently near some $(u^*,t^*)$, the same machinery rigorously
isolates a real second-brake candidate and the arithmetic protocol
(Section 8/9 of the assignment) takes over.

## First three indispensable lemmas

1. **L1 (splitting and separation).**  $\mathcal B=0\iff(\dot I,\zeta)=0$
   away from $XY=0$; $\ddot I=2U-4U_0$; $U<2U_0$ at every $I$-max;
   $U=U_0$ and $r_{ij}\ge m_im_j/U_0$ at every brake.
   *Smallest falsification test:* symbolic identity check of the splitting
   and of $\ddot I$ against the Cartesian dynamics; numerical sampling that
   $(\dot I,\zeta)$ zeros and Hopf-residual zeros coincide, and that sampled
   $I$-maxima satisfy the separation bound with margin.

2. **L2 (window covering soundness).**  If on a time window a validated
   enclosure gives $\dot I\ne0$, or $K>0$, or $|\mathcal B|>0$, then the
   window contains no brake; tangential $\dot I$ zeros (folds) are covered by
   (ii)/(iii) because $U=2U_0\ne U_0$ there forces $K=U-U_0\ge U_0>0$.
   *Smallest falsification test:* construct a synthetic near-brake state and
   confirm each condition individually detects or correctly fails to certify.

3. **L3 (terminal applicability).**  The checkpoint escape certificate's
   exact hypotheses (2D collision-free state, chosen binary/escaper Jacobi
   split, strict inequalities (E)) are satisfiable at a section actually
   reached by the $u=1/3$ orbit, and its conclusion "no later classical
   second brake" is unconditional on both dichotomy branches.
   *Smallest falsification test:* ordinary integration of $u=1/3$ to locate
   the first time the certificate fires; check both the inequalities and the
   identity of the escaping body.

## Fallback

The projective scattering-map program of Section 6 (global classification of
$\mathscr U_\kappa$), attacked through scalar ordering / rotation-number
architecture rather than re-running the live agent's interval boxes.  I
switch only if the event program hits a structural obstruction that cannot
be closed promptly (e.g. validated integration through the deep $u=1/3$
close encounter proves infeasible even with Levi--Civita chart switching and
multiple precision).

## Non-duplication

The live agent owns the skinny-limit continuation: second and later
encounter maps, $\mathscr U_\kappa$, captured-component localization,
scattering-sign certification, and the thin finite-$B$ boundary layer — all
asymptotic $u\to0$ machinery.  This program touches none of those objects;
it consumes them only as endpoint interface lemmas.  The compact middle
interval and the event-topology organization are unclaimed territory in the
checkpoint (`BRAKE_MAP.md` stops at an ordinary-numerical falsification of a
universal slip sign and explicitly requests an event-classification
theorem).
