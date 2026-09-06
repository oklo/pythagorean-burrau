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
2. **Near-brake classification at $u\approx0.342$: RESOLVED at ordinary
   level.**  Cross-validated high-precision (50/60/90-digit Taylor)
   non-interval integrations of $u=171/500$ show NO events after
   $t\approx15$ and minimum event kinetic energy $\approx0.136$ over the
   whole run — the double-precision "near-brake" was noise.  A fully
   rigorous late-time atlas needs a $\sim$250-digit budget (measured
   interval loss $\approx13$ digits/unit); optional, low priority now.
3. **Parameter-interval version: implemented and BLOCKED.**  The
   `icert` mode exists (u as frozen state variable, correlations kept),
   but measured through-encounter amplification $\sim3\times10^{8}$
   forces $10^{-10}$-wide boxes; see `FABLE_FAILED_ROUTES.md`.  Any
   compact-interval theorem needs a structural mechanism instead.
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
