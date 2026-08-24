# Common-clock cover adjacent to the fourth planar collision

Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT**.  The single integrated cover
command below printed `PASS_COMMON_CLOCK_ESCAPE_COVER` on 2026-08-24.  This theorem concerns the
massless planar endpoint family.  It is not a Pythagorean orbit and does not
by itself settle any positive rational Euclid parameter.

## Theorem

Let \(X(\kappa)\) be the normalized stable-manifold member of the planar
massless restricted family used in the fourth-collision certificate.  For
every
\[
  1.264009099014\leq \kappa\leq1.264009099457,                 \tag{1}
\]
one of the following occurs:

1. the classical solution has already suffered a collision; or
2. its simultaneous two-centre continuation reaches the separated outgoing
   section \(\beta=-1\), crosses the isolated heavy-binary collision in the
   regularized bridge, and enters both the restricted and finite-mass-form
   strict terminal escape cones.

Consequently no collision-free member of (1) is a bounded periodic orbit.
The interval overlaps the current broad interval-Newton enclosure for the
positive-primary collision boundary \(\kappa_3\), but does not contain that
whole enclosure; no ordering relative to the exact root follows from the two
certificates.  Its lower endpoint remains about
\(8.07\times10^{-11}\) above \(\kappa_4\); the thin intervening band is not
covered by this certificate.

## A common fourth-LC clock

The fourth root and its regularized flight clock have the independent
MPFR-200 enclosures
\[
\begin{split}
 1.26400909893331527&\leq\kappa_4
       \leq1.26400909893331813,\\
 0.371840180067887265&\leq\tau_4
       \leq0.371840186320052546.
\end{split}                                                     \tag{2}
\]
Choose the rational clock
\[
 \bar\tau={37184019\over10^8},
\]
which lies strictly after the whole clock box in (2).  Propagating the
outward-widened MPFR collision-state hull for the interval
\(\bar\tau-[\tau_4]\) gives a reference enclosure \(X_*\) at this common
clock.

For a parameter tile \(K\), let \(H\) be the interval hull of \(K\) and the
root box in (2).  A persistent \(C^1\) CAPD propagation evaluates the complete
parameter tangent \(\partial_\kappa X(H,\bar\tau)\).  The one-variable mean
value theorem then gives the rigorous enclosure
\[
 X(K,\bar\tau)\subset
 X_*+\partial_\kappa X(H,\bar\tau)\,(K-[\kappa_4]).             \tag{3}
\]
Unlike the failed fifth-section restart, (3) never projects an implicitly
timed Poincare image to a componentwise box.  The only independent hull is
formed at a fixed regularized clock, and all parameter dependence entering
it is retained by the tangent enclosure.

## Exact negative-primary chart change

Write the negative-primary Levi--Civita variables as \(q=U^2\), momentum
\(V\), clock \(t>0\), and energy variable \(h\).  Put
\[
 R=9^{1/3}t^{2/3},\qquad C={U\over\sqrt R},\qquad
 S=\sqrt{1-C^2},
\]
on the positive-real square-root sheet selected by the common-clock boxes.
The negative focus is represented by \(W=-C\).  The simultaneous
two-centre momentum and energy are
\[
\begin{split}
 p={}&-{2\over3}\overline S V
      +{2\over9t}\overline S\,|U|^2U,\\
 E={}&{Rh\over9}-{4t\operatorname{Re}(U\overline V)\over3R^2}
      +{2|U|^4\over9R^2}
      -{1\over9}\left(\left|{U^2\over R}-{1\over2}\right|^2
                       +{1\over|S|^2}\right).                 \tag{4}
\end{split}
\]
These formulas are analytic at \(U=0\): there
\[
 p=-{2V\over3},\qquad E={Rh\over9}-{5\over36}.
\]
The exact symbolic regression
`test_negative_lc_two_centre_switch_is_regular_at_collision` verifies (4),
the identity \(R^{3/2}=3t\), the scaled shape relation, and the collision
limit.  No division by \(|U|\) occurs in the implemented map.

## Poincare and terminal chain

Each tile is propagated as follows.

1. Apply (3), (4), and the nonredundant elliptic map
   \(\xi=\alpha+i\beta\).
2. Use a directed Poincare map to \(\alpha=2\pi\).  Whole-step interval
   enclosures independently prove \(p_r<0\), hence
   \(\alpha_\sigma=-p_r>0\), up to the crossing.  At the focus the enclosure
   has \(\beta<0\), so the selected distance
   \(\sinh^2(\beta/2)\) is positive.
3. Rebox the six-dimensional focus image and use a directed Poincare map to
   \(\beta=-1\).  A second whole-step audit proves simultaneously
   \(p_r<0\) and \(p_i>0\), so \(\alpha\) increases and \(\beta\) decreases.
   The crossing satisfies \(\alpha<3\pi\), excluding an intervening focus.
4. Apply the exact two-centre-to-heavy-binary bridge map.  Along the bridge
   \(\lambda'=-1\).  Both light-primary squared distances remain greater
   than \(10^{-3}\); hence the passage through \(\lambda=0\) is an isolated
   heavy-binary collision, which terminates the classical solution.  Its
   regularized continuation reaches \(-2.1<\lambda<-1.9\).
5. The terminal state satisfies the already proved restricted and
   finite-positive-mass hierarchical escape inequalities with strict positive
   margins.  This last step classifies the outgoing regularized scattering
   branch; it is not used to pretend that postcollision motion is classical.

Any earlier collision is already a nonperiodic classical outcome.  Conditional
on no earlier collision, uniqueness identifies every chart segment before
the isolated heavy-binary collision with the original Newtonian solution.

## Finite interval cover

With
\[
 \kappa(p,r)={1264009098895+p\over10^{12}}
             +[-r,r]10^{-12},
\]
the certificate uses the 131 overlapping tiles
\[
\begin{array}{c|c|c}
 p & r & \text{number of tiles}\\ \hline
 120,122,\ldots,198 & 1 & 40\\
 200,204,\ldots,560 & 2 & 91.
\end{array}
\]
Their union is exactly (1): the first row covers offsets \([119,199]\), the
second covers \([198,562]\).  Therefore no density, sampling, or genericity
inference enters the theorem.

## Reproduction

CAPD 6.1.0 must be checked out at
`731079217a9254ea2948d742df2b170895effe7f` and built with native outward
rounding.  Run

```bash
bash scripts/run_capd_planar_light_collision_newton.sh \
  /path/to/CAPD /path/to/CAPD/build-native \
  --fourth-common-clock-escape-cover
uv run pytest -q tests/test_restricted_scattering.py \
  -k negative_lc_two_centre
```

The first command succeeds only after all 131 tiles have passed and prints
the global worst-case margins.  The source also exposes
`--fourth-common-clock-escape-tile OFFSET_PICO RADIUS_PICO` for independent
replay of any member of the cover.

The integrated replay gave

```text
maximum_first_focus_beta=-0x1.b39eb216954ecp-7
minimum_first_focus_selected_norm=0x1.72a3bf88dde21p-15
minimum_third_focus_alpha_gap=0x1.24b0f6504812p-2
minimum_primary_squared=0x1.41d5cd78ce94ap-6
minimum_escape_margin=0x1.9c0a8a654238cp-1
minimum_finite_mass_margin=0x1.def99fc9b6edp-1
```

These are hexadecimal binary64 aggregate values assembled from directed
interval endpoints; every strict sign test is made on the interval inequality
before aggregation, not inferred from rounded display values.
The complete concise replay record is
`data/validated_planar_fourth_common_clock_cover_capd.txt`.

## Adversarial audit

The following failure modes were checked explicitly.

- Formula (3) is the scalar-parameter mean-value theorem applied
  coordinatewise on one interval hull.  It is not a mean-value theorem for a
  vector map in several independent variables.  The regularized flight clock
  is fixed; return time is not an additional free variable in (3).
- The cached root state is an outward rational hull of an independent
  MPFR-200 certificate.  Discarding its internal root correlation enlarges
  the reference set and cannot invalidate inclusion.  The whole root-clock
  box lies strictly before the rational common clock.
- The chart map (4) is evaluated away from its chosen square-root cut and is
  algebraically regular at the selected collision.  The symbolic test checks
  the cancellation; it does not infer exactness from floating-point agreement.
- The Poincare endpoints alone are not used to infer section order.  Separate
  whole-step time maps prove the signs of both coordinate derivatives through
  the full upper return-time bound.
- A zero encountered before a terminal section is never called a near miss or
  silently continued as a classical orbit.  It is the terminating collision
  branch of the theorem's dichotomy.  The continuation past the unavoidable
  heavy-binary zero is used only to classify the regularized scattering map.
- The 131 boxes overlap and their rational endpoints are evaluated with
  directed intervals.  Thus the conclusion applies to every real parameter
  in (1), not merely the tile centers and not merely rational parameters.
- The argument does not promote compact restricted convergence to a
  finite-positive-mass theorem.  That transfer remains a separately listed
  obligation.

## Scope

This is a new compact restricted-family classification and a useful uniform
input for the positive-mass cusp analysis.  It does **not** prove that the
exact tied Pythagorean curve enters (1), does not provide an effective
positive-mass threshold, and does not resolve the full rational or strong
real conjecture.
