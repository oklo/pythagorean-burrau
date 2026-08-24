# Computer-assisted continuation to a fifth outgoing section

Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** in the planar skinny-limit
model, conditional only on the already proved analytic stable-tail enclosure
and the pinned CAPD implementation described below.

## Statement

Let

\[
 K_4=[1.264009098500,\,1.264009099290].
\]

This is the full parameter box used by the certified fourth collision-root
calculation.  For every \(\kappa\in K_4\), follow the analytic planar stable
family through the regularized charts used in the first four encounter
stages.  Then one of the following holds:

1. an earlier binary collision occurs, so the corresponding classical
   Newtonian solution terminates; or
2. the collision-free trajectory enters the fifth positive-primary
   Levi--Civita chart and crosses the outgoing section

   \[
   c_i={1\over20}
   \]

   in the negative-to-positive direction.

At that crossing the validated enclosure satisfies

\[
 |c|^2>0.002166715533586436,
 \qquad r_{\rm other}^2>0.4599473198119462,
 \qquad {dc_i\over dS}=-d_i>0.740153775124572.
\tag{1}
\]

Thus the fifth selected pair and the other pair are both separated at the
section, and the crossing is uniformly transverse on the whole box.

This theorem includes the exact fourth collision parameter certified in
`COMPUTER_ASSISTED_PLANAR_THIRD_FOURTH_ROOTS.md`.  Its regularized image is
used only to obtain one enclosure for the family.  A member that actually
collides is already nonperiodic as a classical collision-free orbit; no
post-collision segment is interpreted as physical continuation.

## Why the earlier fixed-time continuation failed

The earlier verifier evaluated every nonlinear chart switch on an interval
vector and started the next chart from the resulting box.  Even a point
parameter then acquired large independent widths after several encounters.
A fixed fifth-chart time consequently enclosed both sides of the collision
sheet and could not prove an outgoing separation.

The successful verifier keeps one persistent CAPD doubleton representation
from the analytic stable tail.  If a coordinate change has the same source
and target dimension, the exact nonlinear map acts directly on that set.  If
the dimension changes, the verifier appends dormant target coordinates and
integrates the auxiliary system

\[
 x'=0,\qquad y'=F(x),\qquad y(0)=0
\]

for one auxiliary unit.  Hence \(y(1)=F(x)\) exactly.  No physical time is
assigned to this auxiliary step.  Crucially, the old coordinates and all
global doubleton generators remain in the expanded set, so the chart map
does not replace a correlated family by an interval product.

The dimensions along the certified chain are

\[
 13\longrightarrow19\longrightarrow24\longrightarrow30.
\]

The final 30-dimensional system freezes the first 24 coordinates and evolves
the fifth six-dimensional positive-primary LC state.  CAPD's rigorous
Poincare map then encloses each member at its own section time, rather than at
one common fictitious time.

The stable-tail initialization includes the exact quintic correction and the
degree-six remainder proved in `PLANAR_STABLE_QUINTIC_ENCLOSURE.md`.

## Validated output

The exact hexadecimal output is pinned in
`data/validated_planar_fourth_to_fifth_outgoing_capd.txt`.  Its principal
intervals are

```text
fifth_exit_selected_norm =
  [0x1.1bfee8b685b7ap-9, 0x1.c3394787c8b6ap-8]
fifth_exit_other_squared =
  [0x1.d6fc6e21e690dp-2, 0x1.e29dffc475ec4p-2]
fifth_section_derivative =
  [0x1.7af56f84578a1p-1, 0x1.875db205d253p-1]
```

The reported return-time interval includes auxiliary chart-map time labels;
it is internal bookkeeping and is not asserted to be a physical period or
flight time.

CAPD validates the ODE enclosure step by step.  Every ordinary denominator
and square-root chart expression is evaluated on an interval separated from
its forbidden domain; otherwise the run throws and produces no PASS token.
The explicit terminal bounds (1) provide the additional separation and
transversality needed at the outgoing section.

## Reproduction

Use CAPD 6.1.0 at commit
`731079217a9254ea2948d742df2b170895effe7f` with the NATIVE interval backend:

```bash
bash scripts/run_capd_planar_light_collision_newton.sh \
  /path/to/CAPD /path/to/CAPD/build-native --fourth-fifth-outgoing
```

The command must end with

```text
PASS_FOURTH_FIFTH_OUTGOING method=CAPD-6.1.0-native stage=planar-fourth-root-to-fifth-outgoing-section
```

## Scope

This is not a proof of the Pythagorean--Burrau conjecture and not yet a
uniform positive-\(u\) endpoint theorem.  It is a rigorous continuation
theorem for the planar endpoint collision component.  Immediately after the
certified section, the fifth and sixth close encounters overlap enough that
an ordinary bridge chart loses interval separation.  The next natural
coordinate system is a simultaneous two-centre regularization; forcing a
single-centre LC chart through that overlap is recorded as a failed route.
