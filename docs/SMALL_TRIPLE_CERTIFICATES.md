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
| (39,80,89) | 3/13 | `13@0,23@0.55,13@0.676,12@1.5,13@8.442,12@8.448,23@8.453` | MP 200 bits, order 40, tol 1e-40 | PASS, margin 0.283, tp≈8.519, 10,379 steps, min selected 2.6e-5, min unselected 0.015, max hull 1.3e-6 (`u_3_13_mp200.log`); body 1 escapes, {2,3} bound; two earlier attempts failed at the final triple approach before the driver's double-precision midpoint floor was removed | MP 240 bits / order 44 / 1e-44: pending |
| (3,4,5) | 1/3 | `13@0` | MP 330 bits, order 60, tol 1e-70 | PASS, margin 0.104, tp≈12.078, 7,976 steps, min r13 8.0e-5, min unselected 0.014, max hull 7.9e-6 (`u_1_3_mp330.log`); this is a fresh certificate independent of the unpromoted 2026-08-25 log | MP 300 bits / order 50 / 1e-60: PASS (0.056) |
| (5,12,13) | 1/5 | `13@0` (unselected passages down to 0.010) | MP, not yet run | pending | — |
| (8,15,17) | 1/4 | multi-switch (long {2,3} phase with pericentres 0.003) | not yet attempted | open | — |
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
