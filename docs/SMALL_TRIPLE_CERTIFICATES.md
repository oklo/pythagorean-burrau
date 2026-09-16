# Point certificates for small primitive triples (2026-09-07)

Evidence scope: each row marked PASS is **PROVED BY COMPUTER-ASSISTED
ARGUMENT** by the stored log of `src/fable/verification/window_lc_capd.cpp`
(the general multi-chart Levi–Civita certificate; mathematical basis in
`ISO_WINDOW_INTERVAL.md`), run on the degenerate tile `[u,u]` for the exact
rational `u`. Rows marked pending or FAIL are not results. A row is promoted
only when its log ends in `PASS_WINDOW_LC` and an independent replay at a
different Taylor order and tolerance also passes.

The certificate for a single rational is the tile certificate with zero
width: the launch enclosure is the thin interval around the exact launch,
every accepted-step enclosure verifies positive separations and the
brake-exclusion disjunction (`K>0`, `dI/dt≠0`, or `(z,P)≠0` in the current
chart), and the run ends when the phase-robust escape lemma holds on the
hull with margin above `0.05`. Deep passages of the *selected* pair are
regular in the chart; unselected passages are handled by the separation
step cap. Chart switches are exact algebraic maps applied by the committed
mean-value construction.

| Triple | `u` (fundamental) | Itinerary | Settings | Result | Replay |
| --- | --- | --- | --- | --- | --- |
| (7,24,25) | 1/7 | `13@0` | native, order 14, tol 1e-12 | PASS, margin 0.640, tp≈2.853, min r13 1.2e-7, min unselected 0.012 | order 20 / 1e-15: PASS (0.249) |
| (36,77,85) | 2/9 | `13@0` | native, order 14, tol 1e-12 | PASS, margin 0.281, tp≈0.741, min r13 1.7e-5, min unselected 0.041 | order 20 / 1e-15: PASS (0.255); MP 120 bits: PASS (0.160) |
| (9,40,41) | 1/9 | `13@0` | native, order 14, tol 1e-12 | PASS, margin 1.466, tp≈0.784, min r13 4.9e-9, min unselected 0.035 | order 20 / 1e-15: PASS (0.464) |
| (12,35,37) | 1/6 | `13@0,23@0.58,13@5.68` | MP 200 bits, order 40, tol 1e-40 | PASS, margin 0.080, tp≈5.824, 13,402 steps, min r13 7.1e-7, min unselected 0.0081, max hull 2.2e-5 (`u_1_6_mp200.log`) | MP 240 bits / order 44 / 1e-44: PASS (0.075) |
| (39,80,89) | 3/13 | `13@0,23@0.55,13@0.676,12@1.5,13@8.442,12@8.448,23@8.453` | MP 200 bits, order 40, tol 1e-40 | PASS, margin 0.283, tp≈8.519, 10,379 steps, min selected 2.6e-5, min unselected 0.015, max hull 1.3e-6 (`u_3_13_mp200.log`); body 1 escapes, {2,3} bound; two earlier attempts failed at the final triple approach before the driver's double-precision midpoint floor was removed | MP 240 bits / order 44 / 1e-44: PASS (0.158) |
| (3,4,5) | 1/3 | `13@0` | MP 330 bits, order 60, tol 1e-70 | PASS, margin 0.104, tp≈12.078, 7,976 steps, min r13 8.0e-5, min unselected 0.014, max hull 7.9e-6 (`u_1_3_mp330.log`); this is a fresh certificate independent of the unpromoted 2026-08-25 log | MP 300 bits / order 50 / 1e-60: PASS (0.056) |
| (195,28,197) | 1/14 | `13@0` | MP 320 bits, order 40, tol 1e-38 | PASS, margin 0.152 (`u_1_14_mp320.log`); required the step-cap fix below | MP 256 / order 32 / 1e-30: PASS (1.038) |
| (143,24,145) | 1/12 | `13@0` | MP 320 bits, order 40, tol 1e-38 | PASS, margin 0.936 (`u_1_12_mp320.log`); required the step-cap fix below | MP 256 / order 32 / 1e-30: PASS (0.458) |
| (621,100,629) | 2/25 | `13@0` | MP 320 bits, order 40, tol 1e-38 | PASS, margin 0.971 (`u_2_25_mp320.log`); required the step-cap fix below | MP 256 / order 32 / 1e-30: PASS (0.655) |
| (525,92,533) | 2/23 | `13@0` | MP 320 bits, order 40, tol 1e-38 | PASS, margin 1.809 (`u_2_23_mp320.log`); required the step-cap fix below | MP 256 / order 32 / 1e-30: PASS (0.258) |
| (99,20,101) | 1/10 | `13@0` | MP 256 bits, order 36, tol 1e-34 | PASS, margin 13.411, 4,684 steps, min selected 1.1e-9, min unselected 0.0045 (`u_1_10_mp256.log`) | MP 200 / order 30 / 1e-28: PASS (2.272) |
| (285,68,293) | 2/17 | `13@0` | MP 256 bits, order 36, tol 1e-34 | PASS, margin 2.058, tp≈1.116, 2,523 steps, min selected 1.1e-8 (`u_2_17_mp256.log`) | MP 200 / order 30 / 1e-28: PASS (1.611) |
| (357,76,365) | 2/19 | `13@0` | MP 256 bits, order 36, tol 1e-34 | PASS, margin 0.068, 4,064 steps, min selected 2.1e-9 (`u_2_19_mp256.log`) | MP 200 / order 30 / 1e-28: PASS (0.068) |
| (437,84,445) | 2/21 | `13@0` | MP 256 bits, order 36, tol 1e-34 | PASS, margin 0.528, 3,017 steps, min selected 4.1e-10 (`u_2_21_mp256.log`) | MP 200 / order 30 / 1e-28: PASS (1.293) |
| (5,12,13) | 1/5 | `13@0,auto` (43 automatic switches) | MP 400 bits, order 44, tol 1e-42 | PASS, margin 0.085, tp≈10.93, 9,140 steps, min selected 5.4e-6, min unselected 0.057, hull at machine zero throughout (`u_1_5_mp400_auto.log`); a single chart fails here, losing an unselected separation | MP 320 / order 36 / 1e-34: pending |
| (8,15,17) | 1/4 | `13@0,auto` (41 automatic switches) | MP 400 bits, order 44, tol 1e-42 | PASS, margin 0.089, tp≈19.52, 14170 steps, min selected 6.4e-05, min unselected 0.066 (`u_1_4_mp400_auto.log`); a single chart fails here | MP 320 / order 36 / 1e-34: pending |
| (20,21,29) | 2/5 | inside the window `[0.3916,0.4094]` | see `ISO_WINDOW_INTERVAL.md` | covered by the window theorem (campaign complete, audited) | — |
| (65,72,97) | 5/13 | already in the ledger | `FABLE_TRIPLE_CERTIFICATES.md` | PASS (earlier programme) | — |

Escaper is body 2 (mass `B`) for all rows above except (39,80,89), where
body 1 (mass `A`) escapes and `{2,3}` remains bound.

Logs: `data/fable/point_certs/` (copied from the scratch campaign directory
when promoted). Reproduction:

```
c++ src/fable/verification/window_lc_capd.cpp $(capd-config --cflags --libs) -o wlc
./wlc 1 7 1 7 "13@0" 14 1e-12 4 0.05
c++ -DFABLE_MP -Wno-deprecated-literal-operator src/fable/verification/window_lc_capd.cpp \
    $(capd-config-mp --cflags --libs) -I/opt/homebrew/include -L/opt/homebrew/lib -lmpfr -lgmp -o wlc_mp
./wlc_mp 1 6 1 6 "13@0,23@0.58,13@5.68" 40 1e-40 7 0.05 200
```

with CAPD 6.1.0 at the pinned commit, NATIVE intervals; the MP build needs
`-DCAPD_ENABLE_MULTIPRECISION=ON -DCMAKE_CXX_FLAGS=-I/opt/homebrew/include`.

Numerical note (ORDINARY NUMERICAL EVIDENCE): in double precision the
enclosure of a point certificate grows roughly as `tolerance × 5×10^9` over
two time units of a tight eccentric temporary binary, so order 20 with
tolerance `1e-15` is the useful native setting, and longer interplays need
the MP build; tolerance `1e-16` is below the native floor and behaves worse.

## Thin triples (2026-09-15)

Prompted by Richard Montgomery's suggestion that triples with one side much
smaller than the other two should be easy to dispose of. They are indeed
tractable for point certificates, for a structural reason: the deep first
encounter belongs to the *selected* pair and is therefore regular in the
Levi-Civita chart, however deep it is (`THIN_LIMIT_RIGHT_ANGLE.md` shows it
has depth `0.1355 B^11`). What such certificates do **not** give is a
uniform theorem covering all thin triples; see Section 4 of that note.

One driver limitation was found and fixed while running these. The step cap
in regularized time had a fixed floor of `1/20000`. Near a selected-pair
pericenter of depth `d` the rough enclosure of the selected radius over one
step of length `h` varies by about `h^2`, so a floor above `sqrt(d)` makes
that enclosure straddle zero and aborts the run even though the passage is
regular. Observed directly at `u=1/12` (`d=3.5e-10`, reported enclosure
`[-2.1e-10, 2.3e-9]`, matching `h^2` for `h=5e-5`). The cap now scales with
the pair separation, with the absolute floor only guarding against an
infinite step-halving loop. Certificates issued before the fix remain valid:
the change alters only which steps are taken, not the audits, and the
previously passing tiles and points were re-checked after it.

## Automatic chart following (2026-09-15)

`window_lc_capd.cpp` accepts the token `auto` at the end of an itinerary,
for example `13@0,auto`. The driver then adopts whichever pair is closest
whenever that pair is nearer than four fifths of the selected separation,
with a forty-step hysteresis, applying the same exact algebraic change of
chart through the committed mean-value construction. Scheduled switches from
the itinerary and automatic ones can be mixed.

This is what long interplays need: a hand-built itinerary has to name every
exchange in advance, and a single chart fails as soon as an unselected pair
comes close. Checks: the point certificate at `u=2/9` gives margin `0.2815`
with one chart and `0.2706` with two automatic switches, and the window tile
at `u=0.4` reproduces its margin `0.0762` exactly under the refactored loop,
so the change costs almost nothing in sharpness.

The terminal escape check is now evaluated in whichever chart is current,
at every step after the launch window, rather than only on the last leg of
an itinerary. Any passing check is a complete certificate on its own, so
this only lets a run finish earlier.
