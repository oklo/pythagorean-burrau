# Pythagorean--Burrau nonperiodicity project

This repository is a proof-oriented investigation of whether a Newtonian
three-body free-fall initial condition can be a collision-free labelled
periodic orbit when the masses and opposite side lengths are the same
Pythagorean triple.

The governing statement and conventions are in `docs/CONJECTURE.md`.  Claims
are assigned evidence levels in `docs/PROOF_LEDGER.md`; open logical gaps are
tracked separately in `docs/PROOF_OBLIGATIONS.md`.  Numerical experiments are
not promoted to universal conclusions.

Current strongest result: the full rational and strong real conjectures remain
open, but infinitely many open skinny Euclid-parameter intervals are proved
nonperiodic. Consequently infinitely many distinct primitive Pythagorean
triples satisfy the conjecture. More explicitly, the primitive family
$(4n^2-1,4n,4n^2+1)$ contains a positive-lower-density set of proved
nonperiodic members. See `docs/EXPLICIT_SKINNY_FAMILY.md` and
`docs/STATUS.md`.

## Reproduce the exact checks

```bash
uv sync --all-groups
uv run pytest
uv run python -m scripts.derive_exact_identities
uv run python -m scripts.derive_taylor_jet
uv run python -m scripts.derive_skinny_regularization
uv run python -m scripts.derive_skinny_matching
uv run python -m scripts.derive_restricted_scattering
uv run python -m scripts.derive_finite_plunge
uv run python -m scripts.probe_restricted_transversality --cutoffs 10 20 40
```

The rigorous finite restricted-transversality certificate additionally uses
CAPD 6.1.0 pinned at commit
`731079217a9254ea2948d742df2b170895effe7f`. After building CAPD with
`-DCAPD_INTERVAL_TYPE=NATIVE`, run:

```bash
sh scripts/run_capd_restricted_transversality.sh \
  /path/to/CAPD /path/to/CAPD/build-native
```

Full derivation and trusted-computing-base details are in
`docs/COMPUTER_ASSISTED_TRANSVERSALITY.md`.
