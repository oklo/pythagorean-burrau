# Point certificates for named primitive triples

Each entry below records a completed run of the parametric verifier
`src/fable/verification/tied_event_certificate_capd.cpp` in `certify`
mode.  By Theorems A--C of `FABLE_EVENT_REDUCTION.md` (soundness needs
only the trivial direction of the reduction plus the checkpoint terminal
escape certificate), a `PASS_TIED_EVENT` run proves:

*The normalized tied solution at the stated rational Euclid parameter is
collision-free on the covered range, admits no second labelled brake at
any positive collision-free time, and hence is not a labelled periodic
orbit.  The Pythagorean--Burrau conjecture holds for the corresponding
primitive triple, in both leg orderings (leg-swap symmetry).*

All runs use the pinned CAPD 6.1.0 multiprecision build
(commit `731079217a9254ea2948d742df2b170895effe7f`,
`-DCAPD_INTERVAL_TYPE=NATIVE -DCAPD_ENABLE_MULTIPRECISION=ON`), exact
rational initial data $X=(1,0)$, $Y=(AB(B-A)/(A+B),\,AB)$, zero
velocities, exact rational field coefficients, `MpC0TripletonSet`, and an
initial phase proving $U<2U_0$ through the first accepted step ending
past $t_1$.

Replay command template:

```bash
bash scripts/fable_run_capd_tied_event.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-mp certify P Q TEND PREC TOL ORDER \
  3 1 2 ETA 1 CHECK_START 1 10
```

## Certified triples

### u = 2/5 — triple (21, 20, 29)   [PROVED BY COMPUTER-ASSISTED ARGUMENT]

- Masses $(A,B,1)=(21/29,20/29,1)$; leg-swap partner $u=3/7$.
- Settings: 256 bits, tolerance $10^{-30}$, order 30, $t_1=1/10$,
  terminal check from $t=0.7$, $\eta=4$; binary $\{3,1\}$, escaper 2.
- Result: covering to $t=0.80452\ldots$ with 613 accepted steps; 4
  steps had $0\in\dot I$, all with kinetic-energy lower bound
  $\ge12.28$; escape certificate fired with inner-energy margin
  $\ge0.227$; final hull width $1.46\times10^{-19}$.
- Log: `data/fable/certificate_2_5.log`.

### u = 1/3 — triple (4, 3, 5)   [RUN IN PROGRESS]

The classical Burrau problem; see `FABLE_BURRAU_THEOREM.md`.  768 bits,
tolerance $10^{-80}$, order 60, terminal check from $t=11.5$.

### Queued

$u=1/6$ (35,12,37), $u=1/5$ (5,12,13), $u=1/7$ (7,24,25),
$u=1/4$ (15,8,17) — sequential chain, settings in
`FABLE_EXPERIMENT_LOG.md`.

## Failure semantics

A `FAIL` run proves nothing and certifies nothing; it is recorded only as
an engineering note.  In particular the deep-encounter
division-by-zero throws observed before the step-capping retry patch were
failed step attempts inside CAPD's rough-enclosure trial, thrown before
the set is modified; the retry logic halves a step cap and re-attempts,
which does not weaken soundness (every accepted step still carries its
verified enclosure conditions).
