# Point certificates for named primitive triples

The five accepted entries below record completed runs of the parametric verifier
`src/fable/verification/tied_event_certificate_capd.cpp` in `certify`
mode.  By Theorems A--C of `FABLE_EVENT_REDUCTION.md` (soundness needs
only the trivial direction of the reduction plus the checkpoint terminal
escape certificate), a `PASS_TIED_EVENT` run proves:

*The normalized tied solution at the stated rational Euclid parameter is
collision-free on the covered range, admits no second labelled brake at
any positive collision-free time, and hence is not a labelled periodic
orbit.  The Pythagorean--Burrau conjecture holds for the corresponding
primitive triple, in both leg orderings (leg-swap symmetry).*

The multiprecision runs use the pinned CAPD 6.1.0 build
(commit `731079217a9254ea2948d742df2b170895effe7f`,
`-DCAPD_INTERVAL_TYPE=NATIVE -DCAPD_ENABLE_MULTIPRECISION=ON`), exact
rational initial data $X=(1,0)$, $Y=(AB(B-A)/(A+B),\,AB)$, zero
velocities, exact rational field coefficients, `MpC0TripletonSet`, and an
initial phase proving $U<2U_0$ through the first accepted step ending
past $t_1$. The `81/200` entry uses native intervals, as specified below.
These are existing recorded proof statuses, not fresh integrations performed
by the September 6 consolidation. Failed and recovered runs are separate.

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

### u = 81/200 — triple (33439, 32400, 46561)   [PROVED BY COMPUTER-ASSISTED ARGUMENT]

- Native double intervals (shallow orbit): tolerance $10^{-14}$, order 26,
  $t_1=1/40$; binary $\{3,1\}$, escaper 2, $\eta=4$.
- Escape certificate fired at $t=0.71614$, margin $\ge0.377$;
  4 event steps, all with $K\ge16.3$; final hull width $3.4\times10^{-8}$.
- Log: `data/fable/certificate_81_200.log`.

### u = 33/80 — triple (5311, 5280, 7489)   [PROVED BY COMPUTER-ASSISTED ARGUMENT]

- 320-bit MPFR, tolerance $10^{-35}$, order 40; binary $\{1,2\}$,
  escaper 3, $\eta=2$; fired at $t=0.70596$, margin $\ge0.121$.
- Log: `data/fable/certificate_33_80.log`.

### u = 41/100 — triple (8319, 8200, 11681)   [PROVED BY COMPUTER-ASSISTED ARGUMENT]

- 320-bit MPFR, tolerance $10^{-35}$, order 40; binary $\{2,3\}$,
  escaper 1, $\eta=4$; fired at $t=2.73800$, margin $\ge0.067$.
- Log: `data/fable/certificate_41_100.log`.

### u = 5/13 — triple (72, 65, 97)   [PROVED BY COMPUTER-ASSISTED ARGUMENT]

- 512-bit MPFR, tolerance $10^{-50}$, order 50; binary $\{2,3\}$,
  escaper 1, $\eta=4$; see `data/fable/certificate_5_13.log`.

### Failed attempts (no certificate, recorded honestly)

$u=7/17$ and $u=103/250$ fail at $t\approx0.511$ with step-cap collapse
inside an exceptionally deep close approach — they bracket an apparent
collision parameter between $0.41$ and $0.4125$; higher precision or an
LC chart would be needed.  $u=1/5,1/6,1/7,1/4$ are deep-encounter cases
(see `../archive/history/campaigns/FABLE_FAILED_ROUTES.md`).
Measured deepest-encounter depths (high-precision Taylor, ordinary) and
final direct-integration outcomes: $u=5/18$ ($2.2\times10^{-4}$, failed
at $10^{-75}$), $u=5/16$ ($2.1\times10^{-4}$, failed at $10^{-75}$),
$u=3/10$ ($5.4\times10^{-4}$, failed at $10^{-80}$), $u=4/13$
($1.4\times10^{-5}$, failed at $10^{-100}$), $u=7/19$
($8.6\times10^{-6}$, failed at $10^{-115}$), $u=2/9$
($1.8\times10^{-5}$, failed at $10^{-90}$), $u=3/19$
($4.1\times10^{-7}$, not attempted deep).  All are LC-verifier targets:
the validated Levi--Civita passage costs $\sim$2 digits where direct
integration pays tens to $\sim$100, so a parametric-$u$ port of
`burrau_lc_certificate_capd.cpp` unlocks the entire list, including the
named small triples $u=1/4,1/5,1/6,1/7$.

### Recovered, not promoted: u = 1/3 and u = 5/14

The retired global branch contains `PASS_BURRAU_LC` for the classical
3–4–5 problem and `PASS_TIED_EVENT` for `(171,140,221)`. See the
[provenance and soundness assessment](FABLE_BURRAU_THEOREM.md).
Neither is added to the five accepted entries by recovering a log alone.

### Historical queue, not an active job list

The old campaign queued $u=1/6,1/5,1/7,1/4$; its settings and failed
attempts are retained in `../archive/history/campaigns/FABLE_EXPERIMENT_LOG.md`.
There is no live sequential chain to resume automatically. Any new point
run should serve an explicit obligation in [the research plan](RESEARCH_PLAN.md).

## Failure semantics

A `FAIL` run proves nothing and certifies nothing; it is recorded only as
an engineering note.  In particular the deep-encounter
division-by-zero throws observed before the step-capping retry patch were
failed step attempts inside CAPD's rough-enclosure trial, thrown before
the set is modified; the retry logic halves a step cap and re-attempts,
which does not weaken soundness (every accepted step still carries its
verified enclosure conditions).
