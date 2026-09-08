# Validated nonperiodicity on the prompt-ejection window [0.3916, 0.4094]

Evidence scope: **PROVED BY COMPUTER-ASSISTED ARGUMENT** (campaign completed
and audited 2026-09-07; summary below). Written 2026-09-07.

## Statement

For every real Euclid parameter
\[
 u\in\Big[\frac{3916}{10000},\frac{4094}{10000}\Big]
\]
the tied classical solution (masses `(A,B,1)`, released from rest on the right
triangle of `CONJECTURE.md`) has no second labelled brake at any collision-free
time and is therefore not a classical periodic solution. By leg exchange
`u\mapsto(1-u)/(1+u)` the same holds on `[0.419044\ldots,0.437195\ldots]`.

Consequently the Pythagorean–Burrau conjecture holds for every primitive
triple whose Euclid parameter `b/(a+c)` (either leg ordering) lies in these
intervals. These are a positive proportion of all primitive triples ordered
by hypotenuse: with `p/q=u`, primitive triples with hypotenuse at most `N`
correspond to coprime opposite-parity lattice points in the quarter disc
`p^2+q^2\le N`, `q>p>0`, whose angular distribution is asymptotically
uniform; the two intervals occupy an angular measure
`(\arctan0.4094-\arctan0.3916)+(\arctan0.437195-\arctan0.419044)\approx0.03068`
out of `\pi/4`, i.e. about **3.906 percent** of all primitive triples (empirically 12,433 of the 318,320 primitive triples with hypotenuse at most `2\times10^6`). The
interval includes `(20,21,29)` at `u=2/5` and is about `1.8\times10^{6}`
times wider than the previously certified all-time interval
`[0.29,0.2900000101]`.

## Dynamics on the window (why it is certifiable)

Numerically (`scripts/landscape/`, step `10^{-6}`), for every sampled `u` in
`[0.3915,0.4094]` the motion is: launch; a close passage of pair `{1,3}`
(minimum separation `0.02`–`0.05`) at `t\approx0.46`–`0.50`; a close passage
of pair `{2,3}` (`0.017`–`0.05`) at `t\approx0.515`–`0.54`; a second, milder
`{1,3}` approach; ejection of body 2 with the `{1,3}` binary left bound.
No kinetic-energy minimum after launch falls below `0.16\,U_0`, and the
escape lemma of the paper holds by `t\approx0.7` in the middle of the window
and by `t\approx4.7` at its left end, where body 2 leaves slowly. Below
`u\approx0.3914` body 2 is no longer promptly unbound; above
`u\approx0.40945` a chaotic sliver begins.

## Certificate

`src/fable/verification/iso_window_lc_capd.cpp` (CAPD 6.1.0, pinned commit,
NATIVE double intervals with `-frounding-math`). For a closed rational tile
`[P/Q,P2/Q2]`:

1. **Launch set.** The exact tied launch in the project's pair-`{1,3}`
   Levi–Civita chart (state `w,z,h,G,P,t_p,u,\dot I`; `g_{13}=w^2`,
   `dt=|w|^2d\sigma`) is enclosed as a correlated tripleton
   `x+Cr_0+r` by the mean value theorem over the tile, with `u` an exact
   affine coordinate.
2. **Itinerary.** Pair-`{1,3}` chart to physical time `t_p\ge T_1`
   (`T_1=0.5025`, or `0.505` for `u\ge0.406`); exact algebraic chart switch
   to the pair-`{2,3}` chart (Form A or Form B square-root lift chosen from
   the hull, image by the committed mean-value construction); pair-`{2,3}`
   chart to `t_p\ge T_2=0.575`; switch back to pair-`{1,3}`; continue until
   the terminal check passes on the whole hull. Every switch verifies
   positive separations.
3. **Per-step audit.** Steps are direct solver moves with the committed
   step cap (`min(|w|/24, r_{\rm unsel}^{3/2}/(40|w|^2), 1/100)` in
   `\sigma`). On every accepted-step enclosure: all three separations
   positive; while `U<2U_0` (launch window, `\dot I<0`), nothing else; after
   the launch window, at least one of `K>0`, `\dot I\ne0`, `(z,P)\ne0`.
   This is the validated-cover criterion of the paper; the launch window is
   the initial maximal run of steps on which `U<2U_0` holds.
4. **Terminal check.** Phase-robust escape lemma with binary `{1,3}`
   (`M=A+1`), escaper 2 (`m_c=B`), using the transported inner energy `h`
   and the outer variables `G,P` only, for `\eta\in\{1,1.5,2,3,4,6,8\}`,
   on the hull of the set (all fibers at one `\sigma`); accepted when the
   rigorous margin exceeds `0.05`. Every earlier `\sigma` of every fiber is
   covered by step 3, and the lemma excludes every later classical brake.

Fail-closed: any CAPD exception, lost separation, lost obstruction, or a
terminal check not passed before `t_p=6` is a FAIL.

Campaign driver: `scripts/run_iso_window_campaign.py` (consecutive closed
tiles with shared exact rational endpoints; failed tiles are retried with
alternative switch times and then bisected; PASS logs are resumable).
Independent audit: `scripts/audit_iso_window_campaign.py` (parses the logs
only, checks gap-free rational coverage and positive diagnostics, replays a
random sample with a different Taylor order and tolerance).

## Engineering record

* A fixed-clock Cartesian/Jacobi tripleton (`iso_window_capd.cpp`, kept for
  the record) blows up through the `{1,3}` passage for tiles wider than
  about `10^{-8}`: the interval Jacobian over the set through a passage at
  separation `r` with hull `\rho` costs roughly `\exp(3\times10^4\rho)`,
  although the true sensitivity peaks near `2\times10^3`. This is the same
  wrapping wall recorded in `FAILED_ROUTES.md`.
* The Levi–Civita chart of the passing pair removes the problem for that
  pair (regularized time synchronizes pericenter across the tile), and the
  two exact chart switches handle the second passage; `10^{-6}` tiles then
  pass on most of the window and `10^{-7}` tiles near its top, where the two
  passages are only `0.02` apart in time.
* Taylor order 12 with tolerance `10^{-11}` gives the same margins as order
  20 with `10^{-14}` at 2.5 times the speed; tiles take 3–40 s.

## Campaign summary (2026-09-07)

* `[391600/10^6, 408500/10^6]`: 16,900 closed tiles of width `10^{-6}`, all
  PASS on the first attempt (no retries, no bisection), gap-free, minimum
  margin `0.0500010`.
* `[4085000/10^7, 4094000/10^7]`: 9,000 closed tiles of width `10^{-7}`, all
  PASS on the first attempt, gap-free, minimum margin `0.0500032`.
* Integrator: Taylor order 12, tolerance `10^{-11}`, native double intervals;
  chart switches at `t_p=0.5025` (`0.505` for `u\ge0.406`) and `0.575`;
  every switch used the Form B lift into pair `{2,3}`; margin floor `0.05`.
* Independent audit (`scripts/audit_iso_window_campaign.py`, reading only
  the logs): 25,900 PASS tiles cover `[979/2500, 2047/5000]` gap-free with
  shared rational endpoints; 12 randomly chosen tiles replayed at order 18,
  tolerance `10^{-13}` all PASS; a separate 20-tile replay of the lower range
  also all PASS. Output in `data/fable/iso_window/audit.txt`.
* Records: `data/fable/iso_window/summary_lo.json`, `summary_hi.json`,
  and the complete tile logs in `tile_logs.tar.gz`.
* Wall time: about four hours on a heavily shared 14-core machine with
  9 + 4 concurrent tile processes; 3–40 s per tile.
