# LC covering: implementation and soundness gate

The LC verifier is implemented in
`src/fable/verification/burrau_lc_certificate_capd.cpp`; this is no longer
an unimplemented design. The original proposal, estimates, and later audit
are retained in `../archive/history/guides/FABLE_LC_COVERING_DESIGN.md`.
This current note records the proof obligation relevant to the recovered
3–4–5 run; it does not certify that run.

## Chart and covering requirements

The verifier transports the correlated state through close encounters in
Levi–Civita charts. Every transition must enclose the exact graph of the
coordinate change. Each swept enclosure must retain positive pair
separations and a positive physical clock. Inside a sufficiently close
zone, a proved bound `U > U0` gives `K = U − U0 > 0`, excluding a brake;
elsewhere the complete event-covering tests apply. No chart passage may
silently continue through a classical collision.

## Damped exact-write audit

For a frozen target `T` and a scalar construction

\[
 y'=c(T-y)+f,\qquad c>0,
\]

the endpoint at duration `tau` equals `T` for

\[
 f_*={ce^{-c\tau}(T-y_0)\over1-e^{-c\tau}}.
\]

Thus the forcing interval `[-epsilon,epsilon]` contains an exact overwrite
if a rigorous positive lower duration `tau_minus` satisfies

\[
 |T-y_0|\le{\varepsilon(1-e^{-c\tau_-})\over ce^{-c\tau_-}}.
\]

The nominal target difference is insufficient: CAPD can report the target
reached when its current-time interval merely overlaps it. The implemented
gate uses

\[
 \tau_-=(t_{\rm end})_{\rm left}-(t_{\rm start})_{\rm right}>0
\]

and checks the inequality against the saved initial construction state.
The scalar identity has an exact regression in
`tests/fable/test_event_reduction.py`.

## Recorded validation and its limit

The existing post-repair 256-bit, tolerance-`1e-40`, order-50 smoke record
passed four stale-block entry/exit cycles through physical time
`3.1670113440`, including the close encounter near `3.166`. It reports
positive squared LC separation throughout and final physical hull width
below `4.98e-5`. It was intentionally stopped after that finite target.
It is not a completed 3–4–5 all-time certificate.

See [the recovered-record assessment](FABLE_BURRAU_THEOREM.md) for the
full replay/audit gate. No fresh CAPD integration was undertaken during
the September 6 project consolidation.
