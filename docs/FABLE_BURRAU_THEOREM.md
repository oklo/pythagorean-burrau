# Nonperiodicity of the 3:4:5 Pythagorean Burrau problem

**Status: PENDING VALIDATION — this document becomes a theorem record only
when the multiprecision certificate run recorded below has completed with
final marker `PASS_BURRAU_EVENT`.  Until then every claim here is
conditional on that run.**

## Statement

**Theorem (conditional on the certificate).**  Let $u=1/3$, i.e. the
normalized Burrau free-fall problem with masses $(4/5,3/5,1)$ started at
rest from the tied right triangle of `CONJECTURE.md` — equivalently, after
the exact mass--length scaling, the classical Burrau $3{:}4{:}5$ problem
with each mass equal to its opposite side length.  Then the maximal
classical collision-free solution has no positive time at which all three
labelled velocities vanish.  Consequently this solution is not a labelled
periodic orbit, and the Pythagorean--Burrau conjecture holds for the
primitive triple $\{3,4,5\}$ (in both leg orderings, by the exact
leg-swap symmetry $u\mapsto(1-u)/(1+u)$ identifying $u=1/3$ with
$u=1/2$).

## Proof structure

1. **Reduction** (`FABLE_EVENT_REDUCTION.md`, PROVED ANALYTICALLY).  A
   second labelled brake at a collision-free $\tau>0$ forces
   $\dot I(\tau)=0$, $K(\tau)=0$, and $\mathcal B(\tau)=0$
   simultaneously; moreover no classical brake can occur after a time at
   which the terminal binary--escaper certificate of
   `ESCAPE_CRITERIA.md` holds.

2. **Initial window** (Theorem C initial phase).  Interval integration
   proves $U<2U_0$ on every accepted-step enclosure until the first step
   ending after $t=1/4$; by $\ddot I=2U-4U_0$ and $\dot I(0)=0$ this
   yields $\dot I<0$ on the whole phase, so it contains no brake.

3. **Covering** (computer-assisted).  From the end of the initial phase
   to the terminal time, every accepted-step solution enclosure satisfies
   at least one of: $0\notin\dot I$, $\inf K>0$, or some Hopf-residual
   component excludes $0$.  Each condition excludes a brake on that step
   (trivial direction of the reduction).  The integration itself proves
   the solution exists and is collision-free on the covered range (the
   vector field's interval evaluation would fail otherwise, and the
   verifier's chart expressions require positive separations).

4. **Terminal certificate** (computer-assisted instance of the checkpoint
   theorem).  At the terminal step the state box satisfies the strict
   inequalities of the binary--escaper theorem with binary $\{3,1\}$
   (masses $1$ and $4/5$), escaper body 2 (mass $3/5$), $\eta=4$.  Its
   conclusion excludes every later classical brake on both dichotomy
   branches (escape, or a later inner binary collision, which also ends
   the classical solution).

## Certificate provenance

- Verifier: `src/fable/verification/burrau_event_certificate_capd.cpp`
  compiled with `-DFABLE_MP` against pinned CAPD 6.1.0
  (`731079217a9254ea2948d742df2b170895effe7f`) built with
  `-DCAPD_INTERVAL_TYPE=NATIVE -DCAPD_ENABLE_MULTIPRECISION=ON`;
  MPFR/GMP from the host toolchain.
- Arithmetic: MPFR intervals at 768 bits; Taylor order 60; step-control
  tolerances $10^{-80}$; `MpC0TripletonSet` representation.
- Initial data: exact rationals $X=(1,0)$, $Y=(-12/175,12/25)$, zero
  velocities; masses $(4/5,3/5,1)$; all field coefficients exact
  rationals.
- Replay:
  ```bash
  FABLE_MP=1 CAPD_VERBOSE=1 bash scripts/fable_run_capd_burrau_event.sh \
    /private/tmp/fable-capd /private/tmp/fable-capd/build-mp 768 1e-80 60
  ```
- Run record: to be completed with the final `PASS_BURRAU_EVENT` output
  (event-step count, minimal event kinetic lower bound, final box, and
  escape margin) when the run finishes.

## Scope notes

- This is a single-parameter (point) certificate.  It says nothing about
  neighboring real parameters; parameter transfer at late times is
  obstructed by exponential sensitivity (see `FABLE_TO_MAIN.md`).
- The historical numerical literature (Szebehely--Peters 1967; Yoshida's
  escape-criterion application) asserted escape for this orbit on ordinary
  numerical grounds; the present certificate is, to our knowledge, the
  first rigorous nonperiodicity proof for the exact Burrau initial
  condition, and the first proved instance of the Pythagorean--Burrau
  conjecture at a named primitive triple.
