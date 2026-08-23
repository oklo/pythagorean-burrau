# Fable proof ledger

Evidence labels are used verbatim as in `PROOF_LEDGER.md`.  This ledger
covers only results produced in the Fable parallel run; checkpoint results
remain in the main ledger.

| Claim | Status | Dependencies and scope |
|---|---|---|
| Complex splitting: away from $XY=0$, a labelled brake is equivalent to $\dot I=0$ and $\zeta=\mu_1\overline X\dot X-\mu_2\overline Y\dot Y=0$ | PROVED ANALYTICALLY | Uses only $L\equiv0$; determinant $4\mu_1^2\mu_2^2\lvert X\rvert^2\lvert Y\rvert^2$ symbolically verified; on $Y=0$ the Hopf residual (checkpoint lemma) remains the arbiter |
| Trivial direction: a brake forces $\dot I=0$, $K=0$, $\zeta=0$, $\mathcal B=0$ simultaneously | PROVED ANALYTICALLY | No hypotheses; underlies certificate soundness with no chart condition |
| Lagrange--Jacobi on tied shell: $\ddot I=2U-4U_0$ | PROVED ANALYTICALLY | Exact-rational-point regression in `tests/fable/test_event_reduction.py` |
| Every brake is a strict local max of $I$ with $U=U_0$ and $r_{ij}\ge m_im_j/U_0$ | PROVED ANALYTICALLY | Theorem A of `FABLE_EVENT_REDUCTION.md`; brake set uniformly separated from all collisions |
| At every $\dot I$ zero with $\ddot I\ge0$ (minima, folds), $K=U-U_0\ge U_0>0$ | PROVED ANALYTICALLY | Parameter-uniform kinetic margin; folds lie on $U=2U_0$ |
| Quantitative splitting $\lvert\zeta\rvert^2\ge4K\min\{\mu_1\lvert X\rvert^2,\mu_2\lvert Y\rvert^2\}$ at events | PROVED ANALYTICALLY | Parallelogram law at $\sigma=0$ |
| Covering-certificate soundness (Theorem C) | PROVED ANALYTICALLY | Windows verified by $\dot I\ne0$, or $K>0$, or $\mathcal B\ne0$; terminal escape-or-collision alternative from the checkpoint escape certificate |
| Event atlas of the fundamental interval (margins, counts, terminal times) | ORDINARY NUMERICAL EVIDENCE | 49-point grid; healthy margins on the sampled middle interval; near-brake outlier at $u\approx0.342$; guides but proves nothing |
| $u=1/3$ orbit: 13 positive-time $I$-maxima before terminal certificate fires at $t\approx12.25$, minimal event margins $K\ge0.0187$, $\lvert\mathcal B\rvert\ge0.41$ | ORDINARY NUMERICAL EVIDENCE | DOP853, max relative energy drift $4\times10^{-9}$; target profile for the validated certificate |
| Near-brake at $u\approx0.342$, $t\approx17.62$: $K\approx1.4\times10^{-5}$, $\lvert\mathcal B\rvert\approx8.7\times10^{-3}$, $U/U_0-1\approx5\times10^{-6}$ | ORDINARY NUMERICAL EVIDENCE | Closest interior approach to a second brake located so far; under active classification |
