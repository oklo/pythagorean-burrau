# Pythagorean--Burrau nonperiodicity project

This repository is a proof-oriented investigation of whether a Newtonian
three-body free-fall initial condition can be a collision-free labelled
periodic orbit when the masses and opposite side lengths are the same
Pythagorean triple.

The governing statement and conventions are in `docs/CONJECTURE.md`.  Claims
are assigned evidence levels in `docs/PROOF_LEDGER.md`; open logical gaps are
tracked separately in `docs/PROOF_OBLIGATIONS.md`.  Numerical experiments are
not promoted to universal conclusions.

## Reproduce the exact checks

```bash
uv sync --all-groups
uv run pytest
uv run python -m scripts.derive_exact_identities
uv run python -m scripts.derive_taylor_jet
uv run python -m scripts.derive_skinny_regularization
```
