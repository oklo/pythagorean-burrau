# Nonperiodicity of the 3:4:5 Pythagorean Burrau problem

**Status: PROVED BY COMPUTER-ASSISTED ARGUMENT (2026-08-25).  The
certificate run recorded below completed with final marker
`PASS_BURRAU_LC`; the log is archived as
`data/fable/certificate_burrau_1_3.log`.**

## Statement

**Theorem.**  Let $u=1/3$, i.e. the
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
   at least one of: $0\notin\dot I$; $\inf K>0$; some Hopf-residual
   component excludes $0$; or the position-only bound $\inf U>U_0$
   (sound because $K=U-U_0$ on the true orbit).  Inside the Levi--Civita
   zones ($r_{13}<1/17<m_1m_3/U_0$) no scalar checks are needed: Theorem
   A's separation bound makes a brake impossible there, and the chart
   transport certifies $|w|^2>0$ per step, so the passage is rigorously
   collision-free.  Each condition excludes a brake on its step (trivial
   direction of the reduction).  The integration itself proves the
   solution exists and is collision-free on the covered range.

4. **Terminal certificate** (computer-assisted instance of the checkpoint
   theorem).  At the terminal step the state box satisfies the strict
   inequalities of the binary--escaper theorem with binary $\{3,1\}$
   (masses $1$ and $4/5$), escaper body 2 (mass $3/5$), $\eta=4$.  Its
   conclusion excludes every later classical brake on both dichotomy
   branches (escape, or a later inner binary collision, which also ends
   the classical solution).

## Certificate provenance

- Verifier: `src/fable/verification/burrau_lc_certificate_capd.cpp`
  (multi-passage Levi--Civita covering variant; the physical covering,
  chart entry/exit constructions, and zone conditions are documented in
  `FABLE_LC_COVERING_DESIGN.md` and in the source header) compiled with
  `-DFABLE_MP` against pinned CAPD 6.1.0
  (`731079217a9254ea2948d742df2b170895effe7f`) built with
  `-DCAPD_INTERVAL_TYPE=NATIVE -DCAPD_ENABLE_MULTIPRECISION=ON`;
  MPFR/GMP from the host toolchain.
- Arithmetic: MPFR intervals at 640 bits; Taylor order 150 (physical and
  LC phases; construction flows at order 170, tolerance $10^{-165}$);
  step-control tolerance $10^{-150}$; `MpC0TripletonSet`; LC zone
  thresholds $1/25$ (entry) and $1/17$ (exit); adaptive in-zone step cap
  $\max(1/4000,\min(|w|/20,1/100))$.
- Initial data: exact rationals $X=(1,0)$, $Y=(-12/175,12/25)$, zero
  velocities; masses $(4/5,3/5,1)$; all field coefficients exact
  rationals.
- Run record (`PASS_BURRAU_LC`): 5992 accepted covering steps; 18
  Levi--Civita passages through pair-$\{1,3\}$ encounters (each with a
  rigorous in-zone no-collision bound, e.g. the deep $t=3.166$ passage:
  165 sigma-steps with $\min|w|^2>0$ certified); 167 covering steps with
  $0\in\dot I$, all excluded with kinetic-energy lower bound
  $\ge0.01539$; terminal binary--escaper certificate (binary
  $\{3,1\}$, escaper body 2, $\eta=4$) fired at $t_p=12.13214\ldots$
  with inner-energy margin $\ge0.90661$; final hull width
  $2.0\times10^{-40}$.
- Replay:
  ```bash
  bash scripts/fable_run_capd_burrau_lc.sh \
    /private/tmp/fable-capd /private/tmp/fable-capd/build-mp \
    640 1e-150 150 25 17
  ```

## Scope notes

- This is a single-parameter (point) certificate.  It says nothing about
  neighboring real parameters; parameter transfer at late times is
  obstructed by exponential sensitivity (see `FABLE_TO_MAIN.md`).
- An independent adversarial audit and replay by the live agent is
  requested, per the repository's convention for major certificates.
- The historical numerical literature (Szebehely--Peters 1967; Yoshida's
  escape-criterion application) asserted escape for this orbit on ordinary
  numerical grounds; the present certificate is, to our knowledge, the
  first rigorous nonperiodicity proof for the exact Burrau initial
  condition, and the first proved instance of the Pythagorean--Burrau
  conjecture at a named primitive triple.
