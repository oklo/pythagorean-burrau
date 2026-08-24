# Fourth collision boundary to the fifth LC chart

This note validates the first outgoing segment after the fourth planar
collision boundary.  It does **not** classify the outgoing branch to escape.
It proves that the entire fourth-root parameter box can be carried, with the
usual classical collision alternative, to a uniformly regular
positive-primary Levi--Civita chart for the next close encounter.

## Input and classical scope

Use the already certified parameter box

\[
 1.2640090985\leq\kappa\leq1.26400909929.
\tag{1}
\]

The fourth-root proof establishes that (1) misses the earlier
positive-primary collision and that every prior nonselected separation is
strict.  This is an indispensable imported dependency: the new verifier mode
does not repeat the broader third-root interval Newton.  In the fourth
negative-primary LC chart, evaluate the regularized flow at the fixed clock

\[
 S_4={37284\over100000}.
\tag{2}
\]

This is strictly after the validated collision-clock upper endpoint
(0.3726139177003617).  The exact collision member has already terminated as
a classical orbit; its regularized state is used only to construct a common
map.  Every collision-free member agrees with that map by uniqueness.

Continue the negative-primary chart for the exact additional duration

\[
 \Delta S_-={427160\over1000000}.
\tag{3}
\]

On every whole step, (t>0.05), and the squared distance to the positive
primary has lower bound

\[
 \mathtt{0x1.55e0ed43f2211p-2}>0.3338658.
\tag{4}
\]

At the terminal section, the negative-primary LC norm satisfies

\[
 |u_-|^2>\mathtt{0x1.b45787a389f58p-3}>0.2130575,
\tag{5}
\]

so reconstruction is uniformly nonsingular.

## Exact fifth-chart switch

As before, with (R=9^{1/3}t^{2/3}), set

\[
 q_+=u_-^2-Re_x,
 \qquad
 \dot q_+={2u_-v_-\over|u_-|^2}-{2R\over3t}e_x.
\tag{6}
\]

The interval image proves

\[
 -0.595428<q_{+,x}<-0.577809,
 \qquad |q_+|^2>0.3338640.
\tag{7}
\]

Hence the cancellation-free sheet

\[
 u_{+,i}=-\sqrt{{|q_+|-q_{+,x}\over2}},
 \qquad
 u_{+,r}={q_{+,y}\over2u_{+,i}},
 \qquad
 v_+={\overline{u_+}\dot q_+\over2}
\tag{8}
\]

is analytic on the whole box.  Pinned CAPD gives

\[
 -0.771642<u_{+,i}<-0.760137,
 \qquad
 0.2406407<t<0.2423149.
\tag{9}
\]

Thus every member of (1) either has suffered a terminating classical
collision by this point or, if collision-free, reaches the fifth LC chart on
the sheet (8).  This statement is **PROVED BY COMPUTER-ASSISTED ARGUMENT**.

## Replay and next obstruction

Replay with

```bash
bash scripts/run_capd_planar_light_collision_newton.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native --fourth-root
bash scripts/run_capd_planar_light_collision_newton.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native --fourth-fifth-entry
```

The exact hexadecimal record is
`data/validated_planar_fourth_to_fifth_entry_capd.txt`.  The trusted computing
base is CAPD commit `731079217a9254ea2948d742df2b170895effe7f`, its native
interval backend, `-frounding-math`, the verifier, compiler, and hardware.

Three independent adversarial audits replayed the certificate and endorsed
the clock orientation, imported earlier-collision exclusion, classical
collision alternative, denominator bounds, and square-root sheet.  A separate
fresh replay matched every stored hexadecimal field exactly.

Ordinary continuation indicates that the fifth passage is extremely close:
a representative miss distance is about (2.5\times10^{-7}).  A direct box
restart in (8) loses impact-parameter correlation before it can certify an
outgoing separated section.  This is a wrapping obstruction, not evidence of
collision and not an escape theorem.  Ordinary continuation then sees a
sixth, negative-primary passage with miss distance about (0.0042), followed
by large terminal escape margins.  These numbers are **ORDINARY NUMERICAL
EVIDENCE** only.

The next rigorous target is therefore a correlation-preserving propagation
through the fifth chart, followed by the exact positive-to-negative LC switch
for the sixth passage and the existing signed-
\(\lambda\) escape certificate.
