# Fable run report

Date: 2026-08-23.  Checkpoint payload:
`4e28e91e4b69937b777501cba942ee26186cc139`.
Branch: `fable/global-brake-obstruction`.

**DRAFT — final outcomes of the in-flight $u=1/3$ and $u=5/13$
certificates and the $u=171/500$ high-precision probe are appended at the
end when they complete.**

## Strongest theorems proved in this run

1. **Event-reduction and certificate framework (PROVED ANALYTICALLY).**
   `FABLE_EVENT_REDUCTION.md`: away from $Y=0$ a labelled brake is
   exactly $\{\dot I=0,\ \zeta=0\}$,
   $\zeta=\mu_1\overline X\dot X-\mu_2\overline Y\dot Y\in\mathbb C$
   (only $L=0$ used).  Every brake is a strict $I$-maximum on
   $U=U_0$ with $r_{ij}\ge m_im_j/U_0$ — the brake-candidate event set is
   uniformly collision-free.  Non-maximum events carry the uniform
   kinetic margin $K\ge U_0$.  A sound finite covering certificate
   (per-step: $\dot I\ne0$ or $K>0$ or $\mathcal B\ne0$; terminal:
   checkpoint escape certificate) reduces the conjecture on any
   parameter set to a finite computation.  This is an Outcome-E-type
   structural reduction; it is **not** the full conjecture.

2. **Point theorems (PROVED BY COMPUTER-ASSISTED ARGUMENT).**  The
   Pythagorean--Burrau conjecture holds for the primitive triples
   - $(21,20,29)$ — $u=2/5$ (leg partner $3/7$);
   - $(5311,5280,7489)$ — $u=33/80$;
   - $(8319,8200,11681)$ — $u=41/100$;
   - $(33439,32400,46561)$ — $u=81/200$;
   with pinned-CAPD certificates archived in `data/fable/` and replay
   commands in `FABLE_TRIPLE_CERTIFICATES.md`.
   [PENDING AT DRAFT TIME: $u=1/3$, i.e. the classical $3{:}4{:}5$
   Burrau problem, at 768- and 1088-bit MPFR; $u=5/13$ $(72,65,97)$.]

## Status of the conjectures

- **Full rational conjecture: CONJECTURAL.**  Unchanged.  This run adds
  finitely many certified rationals and a factory for more; it also
  gives quantitative evidence (below) that no uniform computational
  covering can settle the compact middle interval.
- **Strong real conjecture: CONJECTURAL.**  No real second-brake
  candidate was found; the one apparent interior near-brake
  ($u\approx0.342$, $t\approx17.6$) was retracted as double-precision
  noise after two ordinary integrations at different tolerances
  disagreed at $O(1)$ there.

## Event-set classification obtained

Theorems A--B of `FABLE_EVENT_REDUCTION.md`: brakes only at strict
$I$-maxima on $U=U_0$; folds of the event curves exactly on $U=2U_0$
with kinetic margin $U_0$; regular maximum branches are analytic graphs
on which the conjecture is origin-avoidance of the planar analytic curve
$u\mapsto\zeta$; quantitative splitting
$|\zeta|^2\ge4K\min\{\mu_1|X|^2,\mu_2|Y|^2\}$ at events.  The angular
component ($\operatorname{Im}\zeta$, equivalently the pair angular
momentum) does not admit a global sign — consistent with the
checkpoint's `BRAKE_MAP.md` falsification — so the obstruction is
implemented as per-window covering rather than a sign theorem.

## Computer-assisted certificates produced

See `FABLE_TRIPLE_CERTIFICATES.md` (four complete; logs and replay
commands per entry).  All runs use pinned CAPD 6.1.0
(`731079217a9254ea2948d742df2b170895effe7f`) in a Fable-owned checkout
(`/private/tmp/fable-capd`, native and MP builds), exact rational initial
data, and the repaired verifiers
`src/fable/verification/{burrau,tied}_event_certificate_capd.cpp`.

## Negative results with measurements (new, load-bearing)

1. **Uniform $u$-interval covering is blocked.**  Through one endpoint
   deep encounter a point box inflates $10^{-16}\to3.4\times10^{-8}$;
   $u$-boxes would need width $\sim10^{-10}$, i.e. $\sim10^{8}$ boxes for
   a two-hundredths-wide subinterval, exponentially worse with each
   further encounter.  Direct experiments at widths
   $10^{-4},10^{-6},10^{-8}$ all fail, including with a $u$-correlated
   9-variable field (parameter as frozen state).  Full details in
   `FABLE_FAILED_ROUTES.md`.
2. **Skinny direct integration is impassable.**  First-encounter miss
   $\sim(225\pi^2/16384)B^{11}$ ($\approx5\times10^{-7}$ at $u=1/6$)
   stalls interval integration at every precision tried; the ordinary
   $0.005$-grid atlas undersampled these encounters.  LC charts (live
   agent's program) are the only route for $u\lesssim1/5$.
3. **Late-time double precision is meaningless.**  Local amplification
   $\sim10^{10}$ by $t\approx17$; measured interval digit-loss
   $\approx13$/time-unit for the $u=171/500$ orbit implies a
   $\sim250$-digit budget for a rigorous late-time event atlas there.
4. **Two apparent collision-adjacent rationals.**  $u=7/17$ and
   $u=103/250$ fail at $t\approx0.511$ between passing neighbors
   $41/100$ and $33/80$, bracketing an apparent collision parameter in
   $(0.41,0.4125)$.

## Failed routes recorded

`FABLE_FAILED_ROUTES.md`: uniform interval covering; skinny direct
integration; plus the standing checkpoint falsifications (no global
event sign) inherited and respected.

## Remaining proof obligations

`FABLE_PROOF_OBLIGATIONS.md`; headline items: complete the $u=1/3$
covering run; decide the $u=171/500$ late-time events rigorously
($\sim250$-digit budget, feasible offline); extend the certificate
factory to further named triples (each needs its orbit's encounter
depths within precision reach); and — for any full-interval statement —
a structural mechanism replacing brute-force boxes.

## Exact reproduction

```bash
uv sync --frozen
.venv/bin/pytest -q -p no:cacheprovider        # 98 passed
.venv/bin/ruff check --no-cache .              # clean
# certificates (CAPD checkout at pinned commit, native + MP builds):
bash scripts/fable_run_capd_tied_event.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-mp certify 2 5 1.8 256 1e-30 30 3 1 2 4 1 0.7 1 10
FABLE_NATIVE=1 bash scripts/fable_run_capd_tied_event.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-native certify 81 200 3.0 0 1e-14 26 3 1 2 4 1 0.5 1 40
bash scripts/fable_run_capd_tied_event.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-mp certify 33 80 1.6 320 1e-35 40 1 2 3 2 1 0.6 1 40
bash scripts/fable_run_capd_tied_event.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-mp certify 41 100 3.4 320 1e-35 40 2 3 1 4 1 2.5 1 40
FABLE_MP=1 bash scripts/fable_run_capd_burrau_event.sh /private/tmp/fable-capd \
  /private/tmp/fable-capd/build-mp 768 1e-80 60          # u = 1/3
```

## Cherry-pickable commits

`1961704` (event-reduction theorems, src/fable, tests),
`e17c0cd` (certificate infrastructure), `f41fa29` (parametric verifier),
`ffeced2` (2/5 certificate + retry), `2c625f5` (aberrant-completion fix,
blocked-route record), `84291bf` (33/80, 41/100 certificates),
`aa64231`, `ac07c37`, `3c90cd3` (logs/ledger/handoff).

## Single highest-leverage next action

Finish and audit the $u=1/3$ certificate (the historic Burrau problem —
first proved instance of the conjecture at the founding triple), then
port the covering verifier onto the live agent's LC-regularized charts so
the certificate factory reaches the deep-encounter rationals
($1/4,1/5,1/6,\dots$) — the only visible path by which finitely-many-at-a-time
becomes systematically-many.
