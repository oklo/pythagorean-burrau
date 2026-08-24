# Fable proof ledger

Evidence labels are used verbatim as in `PROOF_LEDGER.md`.  This ledger
covers only results produced in the Fable parallel run; checkpoint results
remain in the main ledger.

| Claim | Status | Dependencies and scope |
|---|---|---|
| Complex splitting: away from $XY=0$, a labelled brake is equivalent to $\dot I=0$ and $\zeta=\mu_1\overline X\dot X-\mu_2\overline Y\dot Y=0$ | PROVED ANALYTICALLY | Uses only $L\equiv0$; determinant $4\mu_1^2\mu_2^2\lvert X\rvert^2\lvert Y\rvert^2$ symbolically verified; on $Y=0$ the Hopf residual (checkpoint lemma) remains the arbiter |
| Trivial direction: a brake forces $\dot I=0$, $K=0$, $\zeta=0$, $\mathcal B=0$ simultaneously | PROVED ANALYTICALLY | No hypotheses; underlies certificate soundness with no chart condition |
| Lagrange--Jacobi on tied shell: $\ddot I=2U-4U_0$ | PROVED ANALYTICALLY | Exact-rational-point regression in `tests/fable/test_event_reduction.py` |
| Every brake is a strict local max of $I$ with $U=U_0$ and $r_{ij}\ge m_im_j/U_0$ | PROVED ANALYTICALLY | Theorem A of `FABLE_EVENT_REDUCTION.md`; positive for fixed $u$ and uniform on parameter compacts away from $u=0$, but degenerating at the skinny endpoint |
| At every $\dot I$ zero with $\ddot I\ge0$ (minima, folds), $K=U-U_0\ge U_0>0$ | PROVED ANALYTICALLY | Parameter-uniform kinetic margin; folds lie on $U=2U_0$ |
| Quantitative splitting $\lvert\zeta\rvert^2\ge4K\min\{\mu_1\lvert X\rvert^2,\mu_2\lvert Y\rvert^2\}$ at events | PROVED ANALYTICALLY | Parallelogram law at $\sigma=0$ |
| Exact event shape-speed identity $\zeta=I(\dot s-2is(1-s)\dot\phi)$ and $|\zeta|^2=8KI s(1-s)$ | EXACT SYMBOLIC IDENTITY | $X,Y\ne0$ and $\dot I=L=0$; exact SymPy regression; scalar $K$ has even-order zeros and supplies no intermediate-value argument |
| Covering-certificate soundness (Theorem C) | PROVED ANALYTICALLY | Windows verified by $\dot I\ne0$, or $K>0$, or $\mathcal B\ne0$; terminal escape-or-collision alternative from the checkpoint escape certificate |
| Event atlas of the fundamental interval (margins, counts, terminal times) | ORDINARY NUMERICAL EVIDENCE | 49-point grid; healthy margins on the sampled middle interval; near-brake outlier at $u\approx0.342$; guides but proves nothing |
| $u=1/3$ orbit: 13 positive-time $I$-maxima before terminal certificate fires at $t\approx12.25$, minimal event margins $K\ge0.0187$, $\lvert\mathcal B\rvert\ge0.41$ | ORDINARY NUMERICAL EVIDENCE | DOP853, max relative energy drift $4\times10^{-9}$; target profile for the validated certificate |
| Near-brake at $u\approx0.342$, $t\approx17.62$ | DISPROVED as reliable data | Two ordinary integrations (rtol $10^{-12}$ vs $10^{-13}$) give incompatible states at that time (near-stop vs hierarchical escape with speeds $\gtrsim1.5$); late-time double-precision event scans carry $O(1)$ state noise; the rigorous MP atlas at $u=171/500$ is the arbiter |
| Conjecture holds for primitive triples $(21,20,29)$, $(72,65,97)$, $(5311,5280,7489)$, $(8319,8200,11681)$, $(33439,32400,46561)$ (both leg orderings each) | PROVED BY COMPUTER-ASSISTED ARGUMENT | Event-covering certificates + checkpoint escape certificate; pinned CAPD MP/native runs archived in `data/fable/`; see `FABLE_TRIPLE_CERTIFICATES.md` |
| $u=171/500$ has no event with $K<0.13$ and no events after $t\approx13.4$; the reported near-brake does not exist | ORDINARY NUMERICAL EVIDENCE | Cross-validated 50/60-digit (25 events each) high-precision Taylor integrations; 90-digit in flight; rigorous version would need $\sim$250 digits |
