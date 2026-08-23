# Third and fourth planar collision boundaries

This note validates the next two transverse light--primary collision roots of
the lower-equilateral planar massless limiting family.  They occur immediately
below the second collision-or-escape component certified in
`COMPUTER_ASSISTED_PLANAR_SECOND_COLLISION_ESCAPE.md`.  Neither root is a
Pythagorean orbit or a brake point.  Their role is to resolve two more exact
boundaries in the compact limiting scattering map.

All propagation uses the same analytic stable-tail enclosure and the same
pinned CAPD 6.1.0 native-interval backend as the first two roots.  A true
collision always remains classical termination.  Regularized continuation is
used only to construct and classify the limiting scattering map.

## Common incoming chain

Use the exact fixed second-chart clock

\[
 S_2={10275749204\over10^{10}}.
\tag{1}
\]

The persistent $C^1$ doubleton starts on the certified analytic tail, crosses
the first selected-primary chart with physical distance greater than
$10^{-8}$, switches to the negative-primary chart, and reaches (1).  On the
parameter boxes below, every whole-step enclosure in this second chart also
has selected physical distance greater than $10^{-8}$, so the very close
second encounter is rigorously a near-miss rather than a collision.

Continue the negative-primary LC field for

\[
 \Delta S_-={83687424\over10^8}.
\tag{2}
\]

The selected distance remains strictly positive, the positive-primary
squared distance remains greater than $0.1$, and the physical radial clock
stays above $0.4$.  The exact switch to the positive-primary chart is

\[
 q_+=q_--Re_x,\qquad
 \dot q_+={2u_-v_-\over|u_-|^2}-{2R\over3t}e_x,
\tag{3}
\]

with the cancellation-free sheet

\[
 u_{+,i}=-\sqrt{{|q_+|-q_{+,x}\over2}},\qquad
 u_{+,r}={q_{+,y}\over2u_{+,i}}.
\tag{4}
\]

Formula (4) stays analytic when $q_{+,y}$ changes sign because
$u_{+,i}$ remains strictly negative.  No sign condition on $u_{+,r}$ is
needed.

## The third collision root

Let $S_3$ be reversed regularized time in the positive-primary chart, measured
from (4), and put

\[
 \mathcal F_3(\kappa,S_3)
   =(\operatorname{Re}u_+,\operatorname{Im}u_+).
\tag{5}
\]

The time column of its Jacobian is exactly $-v_+$ because
$u_{+,S}=-v_+$.  Pinned interval Newton proves a unique zero in

\[
 \begin{aligned}
  1.2640090992&\le\kappa\le1.2640091000,\\
  0.588396&\le S_3\le0.588436.
 \end{aligned}
\tag{6}
\]

The Newton image is

\[
 \begin{aligned}
  1.2640090993171269&\le\kappa_3
     \le1.2640090999643190,\\
  0.5884119895288813&\le S_3
     \le0.5884197454438135,
 \end{aligned}
\tag{7}
\]

and

\[
 5224.5883<\det D\mathcal F_3<5227.2175.
\tag{8}
\]

The collision occurs at

\[
 0.39005742<t<0.39005870,
\tag{9}
\]

while the other primary remains separated.  On the whole positive LC path,
$\operatorname{Im}v_+<-1/2$, hence
$(\operatorname{Im}u_+)_{S}>1/2$.  The entry has
$\operatorname{Im}u_+<0$, so (7) is the first possible selected-pair zero.
Together with the strict earlier chart bounds, this proves that the exact
root in (7) is reached by a collision-free classical branch and then
terminates at its positive-primary collision.

## Exact fourth-chart switch

For the next negative-primary passage, first finish the positive LC block at

\[
 \Delta S_+={123106953\over10^8}.
\tag{10}
\]

Reconstruct the heavy-binary bridge variables

\[
 \lambda=t^{1/3},\quad R=9^{1/3}\lambda^2,\quad
 Z=q_+ +{R\over2}e_x,\quad
 V=\dot q_+ +{R\over3t}e_x,
\tag{11}
\]

and propagate the analytic signed-$\lambda$ bridge for the exact duration

\[
 \Delta\eta={97\over5000}.
\tag{12}
\]

Here $\lambda>0.6$ and both light--primary distances remain positive, so this
switch is strictly before the heavy-pair collision $\lambda=0$.  Put

\[
 q_-=Z+{R\over2}e_x,qquad
 \dot q_-=V+{9^{1/3}\over3\lambda}e_x.
\tag{13}
\]

On the certified $q_{-,x}>0.05$ sheet use

\[
 u_{-,r}=\sqrt{{|q_-|+q_{-,x}\over2}},\qquad
 u_{-,i}={q_{-,y}\over2u_{-,r}},\qquad
 v_-={\overline{u_-}\dot q_-\over2}.
\tag{14}
\]

Equations (11)--(14) are inverse on physical state: reconstructing from
$(u_-,v_-,t)$ gives

\[
 Z=u_-^2-{R\over2}e_x,qquad
 V={2u_-v_-\over|u_-|^2}
    -{9^{1/3}\over3\lambda}e_x.
\tag{15}
\]

The negative-primary forcing is exactly

\[
 g_-=-{e_x\over R^2}
     -{q_--Re_x\over|q_--Re_x|^3}.
\tag{16}
\]

The round trip (13)--(15) and the force reduction (16) are exact symbolic
regression identities.

## The fourth collision root and exclusion of the third

Let $S_4$ be reversed regularized time from (14) and define

\[
 \mathcal F_4(\kappa,S_4)
   =(\operatorname{Re}u_-,\operatorname{Im}u_-).
\tag{17}
\]

Pinned interval Newton proves a unique zero in

\[
 \begin{aligned}
  1.2640090985&\le\kappa\le1.26400909929,\\
 0.37084&\le S_4\le0.37284.
 \end{aligned}
\tag{18}
\]

The Newton image is

\[
 \begin{aligned}
  1.2640090985775962&\le\kappa_4
     \le1.2640090992806481,\\
 0.3710663877519410&\le S_4
     \le0.3726139177003617,
 \end{aligned}
\tag{19}
\]

with

\[
 417669.25<\det D\mathcal F_4<429486.31.
\tag{20}
\]

The collision clock satisfies

\[
 0.26436426<t<0.26448171,
\tag{21}
\]

so the light collision is strictly before the heavy-pair collision.  The
opposite primary has squared distance greater than $0.1$.  Moreover
$\operatorname{Re}v_->1/2$ on every fourth-chart step, so
$\operatorname{Re}u_-$ is strictly decreasing and the zero in (19) is the
first selected-pair zero after (14).

It remains essential to exclude the earlier positive-primary collision.
The fourth verifier therefore repeats interval Newton on the broader strip

\[
 \begin{aligned}
  1.2640090981&\le\kappa\le1.2640091001,\\
 0.588316&\le S_3\le0.588516.
 \end{aligned}
\tag{22}
\]

At the lower clock endpoint $\operatorname{Im}u_+<-5.84\times10^{-5}$;
at the upper endpoint $\operatorname{Im}u_+>5.86\times10^{-5}$.  Since
$\operatorname{Im}v_+<-1/2$ until $S_3=3/5$, every possible positive-primary
collision in this parameter strip lies inside (22).  Interval Newton proves
that (22) has exactly one zero and encloses its parameter by

\[
 1.2640090992927064\le\kappa_3
   \le1.2640090999346494.
\tag{23}
\]

The two exact projections are disjoint, with the outward-rounded gap

\[
 \kappa_3-\kappa_4
  >\mathtt{0x1.a844p-37}
  >1.2058\times10^{-11}.
\tag{24}

After $S_3=3/5$, the fourth-root box has
$\operatorname{Im}u_+>0$ on every remaining positive-chart step.  Thus its
exact member cannot have the third collision.  All still earlier selected
pairs have the strict direct distance bounds above.  Consequently the root
in (19) is reached by a classical collision-free branch and terminates at its
negative-primary collision.

## Certificate and scope

Replay with

```bash
bash scripts/run_capd_planar_light_collision_newton.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native --third-root
bash scripts/run_capd_planar_light_collision_newton.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-native --fourth-root
```

The hexadecimal records are
`data/validated_planar_third_light_collision_root_capd.txt` and
`data/validated_planar_fourth_light_collision_root_capd.txt`.  The trusted
computing base is CAPD commit
`731079217a9254ea2948d742df2b170895effe7f`, the native interval backend,
`-frounding-math`, the C++ verifier, the compiler, and ordinary hardware.

Existence, box uniqueness, transversality, chart-domain safety, and classical
first-collision status for both roots are **PROVED BY COMPUTER-ASSISTED
ARGUMENT**.  No rationality statement is made about either real parameter,
and neither result resolves the Pythagorean nonperiodicity conjecture.  The
new roots instead give two additional exact boundaries for the next
collision-or-escape continuation problem.  The ordinal names refer to the
successive encounter charts; uniqueness is asserted only in the displayed
boxes, not over the unvalidated parameter gaps between them.

Three independent adversarial passes replayed both pinned certificates and
endorsed the coordinate maps, reversed-time signs, full $C^1$ chain,
monotone first-zero arguments, strict parameter-gap exclusion, and classical
chronology.  One audit also replayed the legacy second-root and escape modes.
No audit attached an escape conclusion to either new outgoing side.
