# Adversarial audit: tied first-maximum interval

Date: 2026-08-25

Verdict: **ACCEPT**

The reviewer independently rederived the two selected-pair systems.

For pair 13, with $g=q_3-q_1$ and $G=q_2-C_{13}$, it recovered

\[
 X=G+{g\over A+1},\qquad
 F_{\rm ext}=B\left({d_{23}\over r_{23}^3}-{d_{21}\over r_{12}^3}\right),
\]

and the implemented complementary acceleration.  For pair 23, with
$g=q_3-q_2$ and $G=q_1-C_{23}$, it recovered

\[
 d_{12}=G+{g\over B+1},\qquad
 d_{13}=G+\left({1\over B+1}-1\right)g,
\]

together with the implemented force factors and signs.  The reviewer also
checked independently:

- the pair-energy variable $h$, $dt=|w|^2d\sigma$, and both exact
  cancellations in $J_\sigma=|w|^2(2U-4U_0)$;
- reconstruction of the exact tied $(X,Y)$ launch, zero velocities,
  $h=-(A+1)/B$, and $J=0$;
- the complete pair--13 to pair--23 position, velocity, complement, and
  positive-square-root transformation;
- the mean-value construction with frozen $u$, propagation of the CAPD
  variational flow, and one application of the Poincare section correction;
- CAPD's first directed-crossing and transversality behavior;
- whole-step collision separation and prescribed-$J$ audits on every leg;
  and
- the final inference from $U<2U_0$,
  $\operatorname{Im}z<0$, and $P_x<0$.

The audit found no fatal or localized mathematical gap.  Its only observation
was a harmless internal name: in the pair--23 evaluator the member named
`r23_squared` stores $r_{13}^2$.  It is used consistently as the second
unselected distance, and the selected distance plus both unselected distances
are all tested strictly positive.

This audit is independent of the successful MPFR/CAPD tile replays and of the
seven exact symbolic regression tests.
