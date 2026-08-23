# Validated escape beyond the second planar collision boundary

This note certifies the regularized outgoing classification of the distinct
opposite-primary collision boundary from
`COMPUTER_ASSISTED_PLANAR_SECOND_COLLISION_ROOT.md`.  It never treats a
regularized continuation as the physical continuation of a classical
collision: a member that collides is already nonperiodic, while a member that
remains collision-free agrees with the regularized flow and reaches the
escape cone.

Put the narrow interval-Newton neighborhood

\[
 \mathcal N_2=[1.2640119181,1.2640119321]
\tag{1}
\]

and use the root-clock box

\[
 \mathcal S_2=[1.0275748704,1.0275749704].
\tag{2}
\]

The pinned interval-Newton image is strictly inside (1)--(2):

\[
 \begin{aligned}
  1.264011919130913&\le \kappa_2\le1.264011931052384,\\
  1.027574879669515&\le S_2\le1.027574961150769.
 \end{aligned}
\tag{3}
\]

Thus the outgoing product enclosure contains the exact transverse collision
root proved in the companion note.

The outgoing classification is validated on the much larger interval

\[
 \mathcal K_2=[1.2640112041,1.2640126461].
\tag{3a}
\]

## Three light--primary chart blocks

The incoming positive-primary LC block and the first negative-primary switch
are exactly those in the root certificate.  Starting from the whole narrow
box (1)--(2), or any tile in (3a) with the same clock box (2), continue the
negative-primary chart for

\[
 \Delta S_-={83687424\over10^8}.
\tag{4}
\]

Every accepted step keeps the positive primary separated.  At the exit set

\[
 q_+=q_--R e_x,
 \qquad
 \dot q_+={2u_-v_-\over|u_-|^2}-{2R\over3t}e_x.
\tag{5}
\]

The enclosure proves \(\operatorname{Im}q_+<0\).  The cancellation-free
square-root lift

\[
 u_{+,i}=-\sqrt{{|q_+|-q_{+,x}\over2}},
 \qquad
 u_{+,r}={q_{+,y}\over2u_{+,i}}
\tag{6}
\]

therefore has \(u_{+,r}>0\), \(u_{+,i}<0\), and squares exactly to \(q_+\).
Set

\[
 v_+={\overline{u_+}\dot q_+\over2},
 \qquad
 h_+={|\dot q_+|^2\over2}-{1\over|q_+|}.
\tag{7}
\]

The nonsingular positive-primary forcing is

\[
 g_+={e_x\over R^2}
     -{q_++Re_x\over|q_++Re_x|^3}.
\tag{8}
\]

With reversed clock \(S=-\sigma\), the forced LC field is

\[
 \begin{aligned}
 u_{+,S}&=-v_+,\\
 v_{+,S}&=-{h_+u_+\over2}
           -{|u_+|^2\over2}\overline{u_+}g_+,\\
 h_{+,S}&=-2\operatorname{Re}(u_+v_+\overline{g_+}),\\
 t_S&=-|u_+|^2.
 \end{aligned}
\tag{9}
\]

CAPD propagates (9) for the fixed duration

\[
 \Delta S_+={123106953\over10^8}.
\tag{10}
\]

The two post-root LC blocks have the whole-step lower bounds

\[
 \begin{aligned}
  \min |q_--Re_x|^2
   &>\mathtt{0x1.68853ef527d85p-3}>0.1760,\\
  \min |q_++Re_x|^2
   &>\mathtt{0x1.308462fe60958p-3}>0.1486.
 \end{aligned}
\tag{11}
\]

These are distances to the unregularized primary in the respective chart.
Selected-pair zeros are permitted in the regularized enclosure: for a
classical member such a zero is precisely the terminating collision
alternative.

## Heavy-binary bridge and escape cone

At every positive-chart exit the validated domain gives

\[
 t>{1\over5},
\tag{12}
\]

reconstruct

\[
 Z=q_++{R\over2}e_x,
 \qquad
 Z_t={2u_+v_+\over|u_+|^2}+{R\over3t}e_x.
\tag{13}
\]

The signed bridge \(\lambda=\sqrt[3]t\),
\(\lambda_\eta=-1\), is the same analytic heavy-binary chart used for the
first collision boundary.  It crosses \(\lambda=0\) and reaches
\(-2.1<\lambda<-1.9\).  Whole-step enclosures give

\[
 \min_{\rm bridge}\min_i|Z-Q_i|^2
 >\mathtt{0x1.52ef2d666569dp-5}>0.04137.
\tag{14}
\]

The terminal state satisfies both comparison inequalities from
`COMPUTER_ASSISTED_PLANAR_COLLISION_ESCAPE.md`.  Their certified margins are

\[
 \begin{aligned}
  M_{\rm restricted}
   &>\mathtt{0x1.91c63466dfa12p+1}>3.1388,\\
  M_{\rm hierarchical}
   &>\mathtt{0x1.a250cb597073cp+1}>3.2680.
 \end{aligned}
\tag{15}
\]

The wide verifier partitions (3a) into 103 abutting closed tiles.  Their
centers are

\[
 \kappa_j=1.2640119251+14j\,10^{-9},
 \qquad -51\le j\le51,
\tag{16}
\]

and every radius is $7\times10^{-9}$.  Outward-rounded endpoint intervals
overlap, so their union covers all of (3a) without a gap.  Away from the root
tile the first square-root switch uses the exact stable identity

\[
 u_{-,i}={q_{-,y}\over2u_{-,r}},
 \qquad
 u_{-,r}=\sqrt{{|q_-|+q_{-,x}\over2}},
\tag{17}
\]

on the already certified $q_{-,y}<0$ sheet.  The root tile retains the
original correlated interval-Newton lift, and its replay is bit-for-bit
unchanged.  Every tile traverses the same later chart chain and contributes
to the aggregate worst bounds (11), (14), and (15).

Consequently every \(\kappa\in\mathcal K_2\) either has a classical
collision before this terminal section or, if collision-free, escapes and
cannot have a second brake.  In particular the exact root itself terminates
at its certified negative-primary collision; only its regularized
collision--ejection continuation is said to enter the cone.

## Positive-mass transfer

The finite chart chain consists of positive-primary LC, negative-primary LC,
the separated switch (5)--(7), a second positive-primary LC block, and the
heavy-pair LC bridge.  Pair-center-of-mass cancellation makes each selected
finite-mass LC field analytic in the light mass and compatible section data;
the strict bounds (11) and (14) keep every nonselected denominator uniformly
away from zero.  Therefore the Newtonian-scaled terminal state and inner-pair
energy converge uniformly through this finite chain.
The positive-mass hierarchical escape lemma is branch-independent.  The
strict second margin in (15), together with a uniform bound on its future
tidal integral, proves that every sufficiently small compatible
positive-light-mass member near \(\mathcal K_2\) either collides classically
or escapes.  No collision is physically continued, and no finite-time
openness argument is used for the infinite future.

## Certificate and adversarial audit

The source is
`src/verification/planar_light_collision_newton_capd.cpp`; replay with

```bash
bash scripts/run_capd_planar_light_collision_newton.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native \
  --second-escape
```

using CAPD 6.1.0 at commit
`731079217a9254ea2948d742df2b170895effe7f`, the native interval backend, and
`-frounding-math`.  The hexadecimal record is
`data/validated_planar_second_collision_escape_capd.txt`.

The contiguous enlargement is replayed by replacing `--second-escape` with
`--second-escape-wide`; its compact aggregate record is
`data/validated_planar_second_collision_escape_wide_capd.txt`.

Three independent adversarial passes checked root-box containment, both
reversed-time LC fields, the cancellation-free sheet, reconstruction,
signed-\(\lambda\) direction, classical-collision alternatives, both
clearances, and the finite-mass comparison.  All three endorsed the repaired
certificate.

The limiting collision-or-escape result is **PROVED BY COMPUTER-ASSISTED
ARGUMENT**.  The compact finite-mass chart transfer and hierarchical escape
consequence are **PROVED ANALYTICALLY** once the validated strict margins are
supplied.
