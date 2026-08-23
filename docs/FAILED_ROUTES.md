# Failed or blocked routes

## Mutual-distance derivatives as a brake residual

**Status:** DISPROVED.

At a syzygy, a transverse shape velocity can leave all three mutual-distance
derivatives zero.  Example: positions $(-1,0),(1,0),(0,0)$ with only the
middle body's velocity equal to $(0,1)$.  Every pairwise distance has zero
first derivative, but the Hopf quotient residual detects the motion.  The
repair is the three-component Hopf residual documented in `CONJECTURE.md`.

## Preserved-incenter interpretation

**Status:** DISPROVED as a general invariant.

The center of mass is fixed and initially equals the incenter.  Were it to
remain the incenter, uniqueness of barycentric coordinates would force the
instantaneous side-length ratios to remain the mass ratios.  The proved
positive value of $D''(0)$ shows that the right-triangle side relation changes
immediately, so the initial coincidence is not preserved.

## Cardinality/genericity proof

**Status:** DISPROVED as an inference.

Countability, measure zero, analyticity, and the three-equations/two-unknowns
dimension count supply no exact exclusion of rational zeros.  This route is
inactive unless dynamics first produces an explicit arithmetic condition.

## Global Pythagorean-defect cone

**Status:** DISPROVED by converged ORDINARY NUMERICAL EVIDENCE as a candidate
global lemma; the numerical statement itself is not interval validated.

For $u=1/3$, DOP853 integrations with successively smaller steps and tolerances
agree that

\[
D(0.376)\approx-0.004664128339.
\]

The smallest prior separation is about $0.002791245371$, so this is a close
ordinary encounter, not a declared collision.  The best maximum relative
energy drift before the sampled sign change was $2.9\times10^{-12}$.  The
three runs agree in the displayed defect digits.  This is sufficient to stop
investing in $D>0$ as the primary route, but it is not cited as a rigorous
counterexample to that auxiliary lemma.

The exact local identity $D''(0)>0$ remains useful as a jet and as proof that
the incenter coincidence is not preserved.

## First skinny passage implies immediate escape

**Status:** DISPROVED analytically as an asymptotic route.

The Levi--Civita theorem proves a positive $B^{11}$ heavy-pair miss and a
nonzero $B^{11/2}$ angular momentum after the first passage. However the outer
body has $\rho=1+O(B^2)$ and physical radial speed only $O(B^{3/2})$. For
every binary radius bound $R=O(B)$,

\[
{1\over2}\dot\rho^2-{A+B+1\over\rho-R}=-2+O(B)<0.
\]

Thus neither the new terminal criterion nor the Standish--Yoshida criteria can
certify escape at that section. The outer body later plunges on an order-one
time scale, after roughly $(2B^{3/2})^{-1}$ binary cycles. A phase-uniform
later scattering theorem is required.

## Every late-plunge phase escapes with a uniform margin

**Status:** DISPROVED in the exact limiting restricted model.

The local $X=B R$, $Y=B Z$, $t-t_*=B^{3/2}\theta$ scaling tends to an
equal-heavy-mass rectilinear restricted problem. At the phase where the light
particle crosses the perpendicular bisector at binary apocenter, a rigorous
launch-speed boundary argument produces a parabolic-to-parabolic orbit with
zero outgoing energy. Thus no phase-uniform strict escape certificate can hold
in the limit.

This does not prove a bound orbit or second brake at positive $B$. The repair
is to compute the separatrix splitting caused by finite $B$, the incoming
energy $-2B+o(B)$ in scaled units, and the longitudinal symmetry breaking.

## Globally negative tight-pair torque

**Status:** DISPROVED by ORDINARY NUMERICAL EVIDENCE as a shortcut.

The exact initial torque is negative, and its first-encounter integral has a
negative leading coefficient. It is not sign-definite throughout the exact
motion. At $u=1/3$, ordinary integration and the exact torque formula give a
small positive value near $t=0.3757632445$. No theorem relies on this decimal
falsification; it records why initial torque cannot be extrapolated globally.

## Naive whole-line phase Melnikov integral

**Status:** DISPROVED as a well-posed transversality coefficient without an
asymptotic phase gauge.

The formal phase variational equation admits $\zeta=z'$, the Jacobi field that
translates the entire parabolic orbit in time. With that choice its proposed
Melnikov integrand is exactly
\[
{d\over d\theta}\left({rr'\over2(z^2+r^2/4)^{3/2}}\right),
\]
so the whole-line integral vanishes. Naive conditions $\zeta,\zeta'\to0$ at
parabolic infinity do not eliminate this mode: $z'=O(|\theta|^{-1/3})$ also
tends to zero.

The repair is to fix the coefficient of the parabolic time-translation mode,
or, more invariantly, compare incoming and outgoing parabolic curves on the
finite section $z=0$. Reversibility then gives
$V_s(\phi)=V_u(-\phi)$, and the genuine transversality condition is
$2V_u'(0)\ne0$. This condition is now proved by a finite interval Jacobi sign
plus a McGehee-map tangent contraction. The improper-integral route remains
ill posed without a gauge, but is no longer needed for nonvanishing.

## Raw monopole phase on a fixed restricted section

**Status:** DISPROVED as an exact gauge identification.

The first phase-window draft compared the true raw binary phase on
$\rho=BY_0$ with
\[
\Phi_{\rm sec,ref}=n_{\rm bin}t_0(BY_0).
\]
This correctly subtracts the divergent monopole flight phase from
$\Phi_{\rm ref}$, but it still omits the full restricted parabolic tail. At
fixed $Y_0$, the binary quadrupole contributes a finite $Y_0$-dependent tail
term that the monopole formula does not represent; the exact restricted field
is not the monopole field.

The repair is to label the incoming parabolic curve by its asymptotic phase
intercept $\chi$ and compare the full fixed-section state with
$\Gamma^-_{Y_0}(\chi)$. PREPLUNGE_MATCHING.md proves
$\chi=\Phi_{\rm ref}+o(1)$ at an early overlap. INCOMING_TAIL.md subsequently
proved uniform propagation down the restricted tail. Thus the raw-section
gauge remains a failed route, but its invariant-intercept repair is complete.
