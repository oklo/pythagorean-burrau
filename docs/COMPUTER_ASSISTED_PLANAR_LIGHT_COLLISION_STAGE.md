# Validated finite stage toward the planar light-collision zero

## Statement

For every

\[
 {126793\over100000}\le\kappa\le {126794\over100000},
\tag{1}
\]

start at $\zeta=10$ from the exact stable-manifold tail enclosed in
`PLANAR_STABLE_TAIL_ENCLOSURE.md`. CAPD interval Taylor integration validates:

1. the reversed logarithmic-shape flow from $\zeta=10$ to $\zeta=0.3$;
2. interval conversion to the selected-primary Levi--Civita chart;
3. the reversed LC flow for the exact rational duration
   $1071249/1000000$;
4. throughout the LC leg, radial clock $t>1$, heavy separation $R>2$, and
   distance to the other primary greater than $1$.

At the fixed final LC time, the regularized position is enclosed by

\[
 -0.017807<\operatorname{Re}u<0.016661,
 \qquad
 -0.003953<\operatorname{Im}u<0.004019.
\tag{2}
\]

The corresponding remaining state bounds include

\[
 0.02696<v_r<0.06642,qquad
 0.70010<v_i<0.71102,
\]

\[
 1.07650<t<1.07999,qquad
 2.18484<R<2.18959.
\]

Equation (2) encloses zero but does not prove a zero. This stage proves that
the rigorous tail box reaches the ordinary candidate neighborhood in one
analytic LC chart without any unresolved singular boundary. Correlation loss
at the shape-to-LC interval conversion is still too large for interval
Newton.

## Initial enclosure

The exact quartic parameterization is evaluated with outward-rounded algebraic
coefficients. The analytic theorem supplies componentwise errors

\[
 |E_x|,|E_q|<{1\over4000000000},qquad
 |(\mathcal DE)_x|,|(\mathcal DE)_q|<{1\over800000000}.
\]

Using independent component boxes is weaker than the proved vector
$\ell^1$ bound and therefore safe. The program then propagates the full
parameter interval (1), rather than a central decimal orbit.

At $\zeta=0.3$, the validated shape enclosure is

\[
 0.14678048<x<0.14717106,qquad
 0.04566819<y<0.04637352,
\]

\[
 -1.19017735<x_\zeta<-1.18913059,qquad
 0.15173343<y_\zeta<0.15302746.
\]

All physical-to-LC conversion formulas are evaluated by directed interval
arithmetic. The LC time map is stopped after every accepted Taylor step; on
each full step enclosure the three chart-domain inequalities in item 4 are
checked strictly.

## Reproduction

The verifier is
`src/verification/planar_light_collision_shape_capd.cpp`. The wrapper pins
CAPD 6.1.0 at commit
`731079217a9254ea2948d742df2b170895effe7f`, requires the native interval
backend and `-frounding-math`, and rejects a dirty CAPD source tree.

Run

    scripts/run_capd_planar_light_collision_shape.sh \
      /path/to/CAPD /path/to/CAPD/build-native

The successful output begins

    PASS_STAGE method=CAPD-6.1.0-native \
      stage=stable-tail-through-fixed-LC-time

and prints every enclosure in hexadecimal floating-point notation.

## Status

The finite propagation and chart-domain inequalities are **VALIDATED
NUMERICAL RESULT**. The existence, uniqueness, and transversality of a
collision zero remain **CONJECTURAL**. The next repair is correlation
preservation: retain $\kappa$ as an affine doubleton direction through the
coordinate change, propagate its tangent using (4a) of the analytic tail
theorem, and apply interval Newton to the square residual.
