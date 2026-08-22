# Experiment log

## 2026-08-22: exact foundation

- Initialized the repository and pinned Python 3.13 plus SymPy, NumPy, SciPy,
  mpmath, pytest, and Ruff.
- Derived accelerations directly from Newton's equations.
- Symbolically verified normalized $I_0$, $U_0$, and the corrected $D''(0)$.
- Encoded the Euclid map and leg-swap involution with exact rational arithmetic.
- Tested a Hopf residual example that defeats mutual-distance derivatives at
  syzygy.
- Encoded and tested the universal zero-angular-momentum reduced kinetic and
  potential expressions.

Evidence level: EXACT SYMBOLIC IDENTITY for algebraic checks; no global
dynamical conclusion.

## 2026-08-22: defect-barrier falsification

Three DOP853 runs at $u=1/3$, ending at $t=4$, used respectively

- $(rtol,atol,max\_step)=(10^{-11},10^{-13},0.005)$;
- $(10^{-13},10^{-15},0.001)$;
- $(2.22\times10^{-14},2\times10^{-16},0.0005)$.

All gave $D(0.376)=-0.004664128339$ to the shown digits.  The prior minimum
separation was $0.002791245371$; the first two prior relative energy drifts
were $5.3\times10^{-10}$ and $2.9\times10^{-12}$.  Thus the proposed global
$D>0$ cone fails after a close but numerically positive encounter.

Evidence level: ORDINARY NUMERICAL EVIDENCE.  Reproduce the middle run with:

```bash
.venv/bin/python -m scripts.probe_dynamics --u 1/3 --t-end 4 \
  --samples 20001 --rtol 1e-13 --atol 1e-15 --max-step 0.001
```

## 2026-08-22: exact fourth jet and brake-map factorization

- Derived $D^{(4)}(0)$ directly by differentiating Newton's pair force twice.
- Verified its degree-20 numerator symbolically.
- Produced an exact Sturm certificate: sequence length 21, with 10 variations
  at both 0 and $83/200$, proving uniform negativity on the fundamental
  interval.
- Factored the local brake condition into two Jacobi radial rates and one
  angular slip away from Jacobi-vector degeneracy.
- Independently refined a representative double-radial event to
  $(u,t)\approx(0.2928773969,1.3435972246)$ and found slip
  $-0.0562132956$, not a brake.
- Recorded exact initial skinny-pair torque and formal first-passage scaling.

Evidence levels: exact jet identity; PROVED BY COMPUTER-ASSISTED ARGUMENT for
the Sturm sign; ORDINARY NUMERICAL EVIDENCE for the event; CONJECTURAL for the
skinny asymptotics beyond initial torque.
