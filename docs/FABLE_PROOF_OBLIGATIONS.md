# Fable proof obligations

## Target theorem (event program)

For explicit compact parameter sets $\mathcal U\subset(0,\sqrt2-1]$, every
real $u\in\mathcal U$ satisfies the conjecture.  Instantiations planned:
first $\{1/3\}$ (the 3:4:5 Burrau problem), then intervals.

Outstanding obligations:

1. **Validated covering run for $u=1/3$.**  The certificate logic is
   implemented (`src/fable/verification/burrau_event_certificate_capd.cpp`)
   and its soundness is Theorem C.  Native-double interval integration
   wraps catastrophically at the deep encounters ($\sim10^3$ inflation at
   the $t\approx0.376$, separation $2.8\times10^{-3}$ encounter, against a
   true local amplification $\approx10$), so the run uses MPFR
   multiprecision.  OPEN until the MP run passes end to end.
   - Hypothesis check for the terminal interface lemma: the escape
     certificate of `ESCAPE_CRITERIA.md` is applied on a collision-free
     state box with the binary $\{3,1\}$, escaper body 2, $\eta=4$; its
     dichotomy covers later inner collisions, so no collision-free
     assumption is smuggled past $t_N$.
2. **Near-brake classification at $u\approx0.342$.**  Determine the local
   event-branch topology, the minimal distance of $\zeta$ to zero along
   the branch, and whether the near-miss corresponds to a nearby free-fall
   periodic family (Li--Liao type) crossing the tied curve transversally.
   A validated lower bound on $\min\lvert\mathcal B\rvert$ over an
   isolating $(u,t)$ box is the goal; a sign-changing pair with a
   persistent zero would trigger the counterexample protocol instead.
3. **Parameter-interval version.**  Extend the verifier from a point
   initial condition to a $u$-box (interval initial data plus the tied
   initial-state map), with adaptive bisection in $u$.  Needed for any
   covering theorem on a compact interval.
4. **Skinny-side terminal times.**  For $u\lesssim0.10$ the certificate
   did not fire by $t=40$ in ordinary runs; that range belongs to the live
   agent's program and is excluded from the Fable compact-interval claims.
5. **Isosceles-side sliver.**  For $u\gtrsim0.40$ ordinary runs certify
   quickly, but near the endpoint the collision unfolding is the
   checkpoint's open symmetry-breaking obligation; Fable interval claims
   stop below it.

## Standing cautions

- The event atlas is ordinary evidence only; no covering claim may cite it.
- A step enclosure satisfying none of the three conditions is not a
  disproof; it demands subdivision or more precision.  Only an isolated,
  validated zero of $(\dot I,\zeta)$ would be a counterexample candidate,
  and then the full protocol of the assignment applies.
