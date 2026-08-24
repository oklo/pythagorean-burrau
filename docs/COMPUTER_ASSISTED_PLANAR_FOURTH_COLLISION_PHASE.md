# Fourth-collision phase and the next two-centre focus

Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT**.

This note isolates the scalar obstruction immediately after the fourth
certified collision of the planar massless boundary orbit. It does **not**
assert a Pythagorean collision or a periodic orbit. Its strict limiting
margins feed the separate positive-mass transfer theorem in
FINITE_MASS_FOURTH_COLLISION_ESCAPE.md.

## Multiprecision fourth-root certificate

The native-double certificate proves existence and uniqueness of the fourth
negative-primary collision, but its terminal transverse Levi--Civita velocity
is too wide to classify the following positive-primary passage. The same
CAPD 6.1.0 verifier now compiles against the MPFR-backed CAPD types. At
200-bit default precision and validated local tolerance \(10^{-20}\), one
interval-Newton step gives

\[
  1.26400909893313121
  \leq \kappa_4 \leq
  1.26400909893350310.
\]

A second interval-Newton step, centered inside this first image, contracts to

\[
\begin{aligned}
1.26400909893331527
&\leq\kappa_4\leq1.26400909893331813,\\
0.371840180067887265
&\leq\tau_4\leq0.371840186320052546.
\end{aligned}
\]

Re-evaluation on this refined image proves

\[
 \boxed{
 -3.832349985449157\times10^{-7}
 \leq v_i \leq
 -3.681944345249734\times10^{-7}<0.}
\tag{1}
\]

The first Newton inclusion proves existence and uniqueness. The second is a
localization of that same root, not a second root-selection assumption.

## Exact two-centre reduction

At the fourth negative-primary collision, the simultaneous elliptic chart has

\[
  \alpha=\pi,\qquad \beta=0,\qquad
  p_r=-\frac23v_r,\qquad p_i=-\frac23v_i.
\]

The positive focus is the Poincare section \(\alpha=2\pi\). On that section
the selected normalized distance is

\[
 r_+ = \sinh^2(\beta/2).
\]

Consequently the next passage is a true collision exactly when \(\beta=0\).
The locus \(v_i=0\) is reflection invariant and stays rectilinear, so it
reaches that collision locus. For the actual nonsymmetric orbit a validated
focus map, not symmetry intuition, must decide the sign.

## Focus certificate

A deliberately widened rational hull of (1) was fed to the native
outward-rounded two-centre verifier. It proves on the section
\(\alpha=2\pi\) that

\[
 -1.310804394749059\times10^{-5}
 \leq\beta\leq
 -1.259358598132686\times10^{-5},
\]

and hence

\[
 \boxed{
 3.964960196340643\times10^{-11}
 \leq \sinh^2(\beta/2).}
\tag{2}
\]

Thus the regularized collision--ejection branch has a rigorously positive
distance at its next positive focus. This is a near-collision, not an
additional collision, and the two-centre trajectory continues smoothly.

The earlier three-tile experiment remains useful adversarial evidence: both
negative-phase tiles had \(\beta<0\), while only the tile containing the
reflection-symmetric phase \(v_i=0\) failed. The refined root (1) lies
strictly inside the negative middle tile.

## Sixth focus and terminal escape

The same two-centre Poincare chain reaches the following negative focus with

\[
 -0.002181489558789266
 \leq\beta\leq
 -0.002095867762413745,
\qquad
 r_->1.098165821369775\times10^{-6}.
\tag{3}
\]

At the next positive focus the selected distance already exceeds
\(0.0506366673765623\). The exact two-centre-to-ordinary transformation is
then embedded as an auxiliary graph ODE, retaining all six earlier doubleton
generators. The ordinary heavy-binary bridge crosses \(\lambda=0\) and
terminates near \(\lambda=-2\). Along it, both light--primary squared
distances exceed \(0.00262385439850217\). At the terminal section the
restricted escape margin exceeds \(10.2599662232953\), and the existing
finite-mass-form comparison expression exceeds \(10.3953509156741\).

Therefore the regularized fourth-collision ejection branch reaches the strict
hyperbolic escape cone without another collision.

## Classical scope

The exact root's classical Newtonian solution ends at the fourth collision.
Equations (2)--(3) and the terminal escape statement concern its mathematical
collision--ejection continuation; they are not a physical continuation of
that colliding orbit.

They do give a classical local scattering theorem. By transversality of the
fourth root, analytic regularized dependence, and the strict terminal
margins, there is a real parameter neighborhood in the planar massless family
such that every member either suffers a terminating classical collision or,
if collision-free, enters the escape cone. Hence no member of that local
neighborhood is a collision-free periodic orbit. No effective neighborhood
size is claimed here.

## Reproduction

The multiprecision CAPD source is pinned at commit
731079217a9254ea2948d742df2b170895effe7f, with MPFR 4.2.2 and GMP 6.3.0.
After configuring CAPD with CAPD_ENABLE_MULTIPRECISION=ON, run

~~~text
bash scripts/run_capd_planar_light_collision_newton_mp.sh \
  /private/tmp/pythagorean-capd /private/tmp/pythagorean-capd/build-mp
~~~

The independently composable native focus and terminal replay is

~~~text
bash scripts/run_capd_planar_light_collision_newton.sh \
  /private/tmp/pythagorean-capd /private/tmp/pythagorean-capd/build-native \
  --fourth-two-centre-terminal
~~~

The cached decimals in the verifier are outward-widened rational bounds, not
floating-point replacements for the root proof. The MP root command remains
an indispensable proof dependency. Both commands must pass for the composed
local collision-or-escape theorem.
