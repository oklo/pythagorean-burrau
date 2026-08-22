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
