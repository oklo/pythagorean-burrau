# Design: LC-regularized covering certificates

Status: DESIGN ONLY — nothing here is implemented or proved.  This is
the blueprint for removing the deep-encounter digit tax that currently
limits the point-certificate factory (measured: $\sim38$ digits through
the $r\approx8.3\times10^{-5}$ encounter of $u=1/3$; total budgets
$\gtrsim160$ digits for the full Burrau run; $u\le1/5$ unreachable).

## Architecture

Work in the 8-dimensional unweighted Jacobi system used by the Fable
verifiers.  Far from encounters, integrate the physical field as now.
When the smallest pair separation enters a threshold $r<\rho_{\rm in}$
with the third body separated ($\ge\rho_{\rm far}$), switch to a
Levi--Civita chart for that pair, integrate through the encounter, and
switch back at $r>\rho_{\rm out}$ ($\rho_{\rm out}<\rho_{\rm in}$ on
entry/exit to preclude chattering; thresholds fixed rationals).

The LC chart for the close pair with relative coordinate $q$ (one of
$X$, $d_1=Y+\alpha X$, $d_2=Y-\beta X$):

- $q=w^2$ (complex square), $dt=|w|^2\,d\sigma$;
- companion center-of-pair coordinate chosen as in the checkpoint's
  finite-mass reduction ($Q=R+\frac{B}{1+B}q$-style) so the second
  equation carries no singular force — the exact cancellation identities
  are already proved in `FINITE_MASS_PLANAR_COLLISION_PERSISTENCE.md`
  and only need the tied-family mass constants substituted;
- the pair's LC energy constraint provides an online consistency check
  (not a proof ingredient).

Chart transitions use the checkpoint's *unit-time construction flow*
idiom (`FAILED_ROUTES.md`, independent-box entry): keep old and new
coordinates in ONE doubleton/tripleton and flow the nonlinear change of
variables as an auxiliary vector field over unit time, so affine error
correlations survive the transition.  Never convert boxes componentwise.

## Covering conditions inside the chart

The event scalars are polynomial in the chart after multiplying by
$|w|^2>0$: with $t_\sigma=|w|^2$,
$\dot I\cdot|w|^2$, $K\cdot|w|^4$-type clearings keep all three
conditions polynomial; a brake in physical variables forces the cleared
scalars to vanish, so per-step covering remains sound verbatim.  (Best:
verify the conditions on the physical reconstruction $q=w^2$,
$\dot q=2\bar w w_\sigma/|w|^2$ — rational in chart variables away from
$w=0$; $w=0$ cannot occur on a certified segment because Theorem A puts
brakes at $r_{ij}\ge m_im_j/U_0$, so inside the chart the $K>0$/
$\dot I\ne0$ margins are enormous and cheap.)

Actually the decisive simplification: **inside the chart zone the
brake-candidate conditions are automatically satisfied** — by Theorem A
every brake has all separations $\ge m_im_j/U_0$, and the chart zone has
$r<\rho_{\rm in}\ll\min m_im_j/U_0$ if $\rho_{\rm in}$ is chosen below
the uniform brake separation bound.  So inside the chart NO covering
checks are needed at all; the chart's only job is transporting the set
rigorously.  Choose e.g. $\rho_{\rm in}=\tfrac12\min_{ij}m_im_j/(2U_0)$
(also below the $I$-max separation bound so no event checks are skipped:
events with $\dot I=0,\ \ddot I<0$ cannot occur in the zone either; and
$\dot I\ne0$ need not hold there — minima are excluded by the $K\ge U_0$
argument only at $\dot I=0$ points, which are fine because $U>2U_0$
throughout the zone makes $K=U-U_0>U_0>0$: even simpler, the $K>0$
condition holds on the whole zone with uniform margin $U_0$).

So the correct statement: on any step whose enclosure lies inside
$\{U>{3\over2}U_0\}$ (say), $K=U-U_0>{1\over2}U_0>0$ excludes brakes
with a parameter-uniform margin — no scalar evaluation beyond the zone
membership is needed, in any coordinates.

## Expected gains

The encounter's wrapping tax comes from thousands of tiny steps of a
near-singular field; in LC variables the flow through the encounter is
analytic with $O(1)$ coefficients, a handful of steps, and no domain
throws.  Expected budget for full Burrau: $\sim45$ digits pre/post
encounter losses only, i.e. tolerance $10^{-60}$ at 256--320 bits,
runtime well under an hour; $u=1/4,1/5,1/6,1/7$ (the named small
triples) become reachable the same way, using their $B^{11}$-deep first
encounters inside the chart where they are regular.

## Soundness obligations for the implementation

1. Exact algebra of the chart change and its inverse (regression-test
   symbolically as in `tests/fable/`).
2. Transition sections at rigorously verified $r$-values with
   transversality of the flow to the section (checked by enclosure of
   $dr/dt\ne0$ or by fixed-time transitions instead of section hits —
   fixed-time is simpler and sound: switch at the end of an accepted
   step whose enclosure lies inside the zone annulus).
3. Zone membership enclosures ($U>{3\over2}U_0$ etc.) evaluated on the
   step enclosure in whichever chart is active.
4. The classical-solution identification: LC segments must certify
   $|w|>0$ throughout (no collision), so the physical solution exists
   and matches the chart flow; a collision inside the chart would
   appear as $0\in|w|^2$ enclosure and must abort with FAIL (it would
   anyway be a classical termination, but the certificate should not
   silently regularize through it).
