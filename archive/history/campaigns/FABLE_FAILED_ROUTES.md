# Fable failed or blocked routes

## Uniform interval covering of a compact parameter interval

**Status: BLOCKED by measured through-encounter amplification; recorded
so the compact-middle program is not re-attempted in this naive form.**

The covering certificate (Theorem C of `FABLE_EVENT_REDUCTION.md`) is
sound for parameter boxes, and the verifier supports a $u$-interval mode
(`icert`) in which the Euclid parameter rides along as a frozen state
variable so that set representations track state--parameter correlations
affinely (the checkpoint's decorrelation lesson applied).  It still
cannot cover intervals at realistic cost:

- Every tied orbit in the middle range passes through at least one deep
  encounter early (the near-isosceles orbits pass near triple collision;
  by $t\approx0.72$ at $u=81/200$ a point box of width $10^{-16}$ exits
  at width $3.4\times10^{-8}$ — a factor $\sim3\times10^{8}$ of true
  local amplification times wrapping).
- Certifying a $u$-box therefore needs initial width
  $\lesssim\text{margin}/3\times10^{8}\approx10^{-10}$, i.e.
  $\sim10^{8}$ boxes for the two-hundredths-wide near-endpoint
  subinterval alone, growing exponentially with each further encounter
  crossed.  Direct experiments: width $10^{-4}$ fails at $t\approx0.48$;
  widths $10^{-6}$ and $10^{-8}$ blow up inside the first deep pass.
- At late times it is strictly worse: local amplification
  $\sim10^{10}$ by $t\approx17$ makes the still-alive set resolvable only
  at inverse-Lyapunov scales.

Consequence: computational certification is per-parameter (points are
cheap; a native point certificate near the endpoint takes seconds), and
the compact middle interval cannot be closed by uniform interval
covering.  Any full-interval theorem needs a structural mechanism
(regularized transfer, symbolic-dynamics shadowing with per-symbol
certificates, or an entirely different obstruction), not brute-force
boxes.

## Direct validated integration through skinny first encounters

**Status: BLOCKED for $u\lesssim1/5$; the Levi--Civita machinery of the
checkpoint is the correct tool there.**

The tied first tight-pair encounter has miss distance
$\sim(225\pi^2/16384)B^{11}$: already at $u=1/6$ this is
$\sim5\times10^{-7}$, and the ordinary $0.005$-grid atlas undersampled it
(reported $4\times10^{-3}$).  Native and multiprecision direct interval
integration both stall at the encounter ($u=1/6$: fixed-code run pinned
at $t\approx0.14677$ with collapsing step cap).  Certificates for
$u=1/5,1/6,1/7,\dots$ require LC-regularized charts; they are deferred to
the skinny program rather than fought with precision.

## Early observations kept for honesty

- The `(R_1,R_2,S)` universal-sign shortcut was already falsified in the
  checkpoint (`BRAKE_MAP.md`); the Fable complex-splitting version
  ($\zeta$ nonvanishing on maximum branches) inherits the same caveat: no
  single global sign exists, and the certified route is per-window
  covering, not a sign theorem.
- Double-precision late-time event scans (beyond $t\approx15$) carry
  $O(10^{-2})$ state noise and cannot classify near-brakes; only
  multiprecision enclosures count.
