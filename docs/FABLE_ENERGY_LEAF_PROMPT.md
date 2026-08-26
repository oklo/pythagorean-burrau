# Prompt for Fable: energy-leaf chart-switch reconstruction

You are working as an independent auxiliary researcher on the
Pythagorean--Burrau nonperiodicity project.  Work in your own repository and
branch; do not modify the primary worker's repository.  Produce a
self-contained handoff with small, cherry-pickable commits.

## Exact bounded task

Audit, prove, and implement an **opt-in fixed-energy reconstruction of the
Levi--Civita selected-pair energy coordinate `h` at chart switches**.  The
purpose is to remove a removable interval singularity in the current
validated middle-interval propagation.  This is enclosure engineering on the
same exact Newtonian flow, not softening, regularized physical continuation,
or a new dynamical assumption.

The primary worker now propagates a directional validated C2 parameter graph

\[
 X(\delta)\subset x+T\delta+Q\delta^2+E,
 \qquad \delta=u-u_c,
\]

through pair--13 and pair--23 Levi--Civita charts.  It has already proved
CAPD's C2 coefficient conventions and passed the complete terminal escape
chain on the control interval

\[
 [0.29,0.290000000001].
\]

The remaining width is almost entirely the additive defect, especially near
the consecutive pair--23 and pair--13 close passages around physical times
3.4515 and 3.4695.  One suspected source is reconstructing

\[
 h={2|z|^2-M_{ij}\over |w|^2},
\]

which is exact away from collision but interval-ill-conditioned when
\(|w|\) is small.

## Formula to verify independently

Use normalized masses

\[
 A={1-u^2\over1+u^2},\qquad B={2u\over1+u^2},\qquad m_3=1,
 \qquad H=-U_0,
\]

where

\[
 U_0=AB+{1\over AB}.
\]

In the pair--13 Jacobi chart, let (g=q_3-q_1), let (G) be the vector from
the pair--13 center of mass to body 2, and let (P=\dot G).  With

\[
 \mu_{13}={A\over A+1},\qquad
 \mu_{G,13}={B(A+1)\over A+B+1},
\]

the energy leaf should give

\[
 h_{13,E}=
 { -U_0-\frac{\mu_{G,13}}2|P|^2
    +\frac{AB}{r_{12}}+\frac{B}{r_{23}}
  \over \mu_{13}}.
\]

In the pair--23 chart the symmetric formula should be

\[
 \mu_{23}={B\over B+1},\qquad
 \mu_{G,23}={A(B+1)\over A+B+1},
\]

\[
 h_{23,E}=
 { -U_0-\frac{\mu_{G,23}}2|P|^2
    +\frac{AB}{r_{12}}+\frac{A}{r_{13}}
  \over \mu_{23}}.
\]

Do not trust these formulas merely because they are supplied here.  Re-derive
the Jacobi kinetic energy and every sign and reduced-mass factor from the
physical positions and velocities.  Prove that (h_E) equals

\[
 |\dot g|^2/2-M_{ij}/|g|
\]

on the exact fixed-energy leaf.  Check both chart conventions used by the
code.

## Required work

1. Inspect the current main implementation at commit `03f2310`, especially
   `src/fable/verification/middle_escape_endgame_capd.cpp`,
   `docs/C2_PARAMETER_GRAPH.md`, and
   `tests/test_middle_escape_endgame_maps.py`.  If your repository does not
   contain that commit, use it only as a read-only reference or request the
   relevant files; do not silently recreate conventions from memory.

2. Give an exact symbolic derivation of both energy-leaf formulas.  State the
   domain precisely: the two *unselected* mutual distances must remain
   positive, while the formula should have no division by the selected
   ( |w|^2 ).

3. Add deterministic exact SymPy tests comparing the velocity formula and the
   energy-leaf formula on exact rational physical states constrained to the
   correct total energy.  Also test the pair--13/pair--23 frame changes and
   both Levi--Civita square-root lift forms.  A floating-point spot check is
   not enough.

4. Implement a narrowly scoped opt-in CAPD chart-switch map which computes
   all ordinary target-chart coordinates exactly as before but replaces only
   target `h` by (h_E).  Keep the old implementation available as a control.
   Preserve the exact conserved parameter coordinate (u), the physical-time
   coordinate, and the dilational coordinate.

5. Prove that substituting (h_E) does not project a general box onto the
   energy leaf illegitimately.  It may be used only because the propagated
   graph is known to consist of the tied initial conditions on the exact
   energy leaf.  Explain how this remains valid for the full C0 tube audit and
   for the directional C2 graph.  If the existing set representation includes
   spurious off-energy points, identify the exact enclosure lemma needed to
   reconstruct `h` fiberwise without losing any genuine orbit.

6. Benchmark old versus energy-leaf reconstruction at the switch immediately
   before the difficult exchange, reporting total hull, (T\delta),
   (Q\delta^2), and defect separately.  First use the already-proved control
   width (10^{-12}).  If it improves the enclosure, test width (10^{-11})
   and then only the largest width justified by the observed economics.  Do
   not launch a many-day tiling campaign.

7. Actively try to disprove the method.  In particular check:

   - hidden division by an unselected near-collision distance;
   - loss of the exact fixed-energy correlation after interval reboxing;
   - using energy equality for spurious points when only genuine fibers obey
     it;
   - an incorrect outer reduced mass or pair-potential assignment;
   - cancellation that looks good at one decimal center but is nonuniform in
     (u);
   - failure of C1/C2 derivative transport through the replacement;
   - accidental reliance on post-collision regularization.

## Success criterion

The strongest useful outcome is a proved graph-enclosure lemma plus a
validated replay showing materially smaller defect through the exchange.  A
clean rejection is also useful if you identify the first false lemma or show
that the energy substitution is not rigorous for the present graph
representation.

Do **not** claim a wider nonperiodicity theorem unless the complete existing
brake-exclusion tube audit and terminal escape inequalities pass on a closed,
gap-free interval with exact rational endpoints.  A smaller switch box alone
is an engineering result.

## Handoff

Commit:

- the exact derivation;
- exact tests and their reproduction command;
- the opt-in implementation, if sound;
- compact benchmark logs;
- an adversarial verdict (`ACCEPT`, `REJECT`, or `CONDITIONAL`);
- a short file `docs/FABLE_ENERGY_LEAF_HANDOFF.md` listing commits in
  cherry-pick order and separating theorem from numerical evidence.

End with one recommendation to the primary worker: adopt, repair, or abandon
this route.
