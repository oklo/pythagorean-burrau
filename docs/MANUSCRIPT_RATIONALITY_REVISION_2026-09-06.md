# Introduction and near-periodic-orbit revision — September 6, 2026

The manuscript is now 30 pages, including references. The user relaxed the
earlier under-30-page target for this revision; type size and margins are unchanged.

## Mathematical argument and assessment

Section 1.5 distinguishes the desired exact exclusion `P intersect Q = empty`
from a Lebesgue-measure statement. An explicitly solved analytic reversible
Hamiltonian family has periodic parameters exactly Q; a second oscillator
example has the sole periodic parameter 1/3. Neither is represented as a
Newtonian gravitational example. The dimension-count heuristic is stated
conditionally on transversality, not used as a proof for the actual family.

The final introductory paragraph gives a dated subjective 10% estimate for
the existence of at least one collision-free periodic integer Pythagorean
experiment. The attribution "GPT-6 Astra" was explicitly specified by the
user. The estimate is not a derived probability, a frequency inferred from
the selected candidate sample, or a forecast for a finite search. The fan
float precedes this closing discussion in the compiled manuscript.

## Section 2 and Figure 3

The F30 trajectory replaces the redundant defect plot; Table 1 retains all
six candidate defects. The text quantifies mass shifts, launch coordinates,
brake time, angle defect, and aligned vertex mismatch. It distinguishes the
parent catalogue orbit from the mass--side-matched continuation, explains
the selection effect, and states the remaining right-angle and arithmetic
obligations. The numerical Jacobian is not promoted to a validated rank bound.

Parent coordinates were checked against the
[Li–Liao author catalogue](https://numericaltank.sjtu.edu.cn/three-body/free-fall-3b/free-fall-3b-movies.htm),
now linked in the bibliography. The trajectory PNG is an unchanged copy of
the existing burrau image; SHA-256 hashes agree. Its archived plotting audit
is included alongside it. The caption discloses the time-reversed construction
of the plotted return half and the plotting replay's 2.6e-11 residual, distinct
from the campaign's separately refined root. No new orbit was constructed.

## Checks

- Exact symbolic checks of Hamilton's equations, the rational second-brake
  time, and the full-state return in the new oscillator example passed.
- Recalculation from the campaign JSON gives D = -0.00335599726517222,
  largest angle 90.201596585 degrees, and leg-mass changes of approximately
  -0.864725572% and +0.221871665%, agreeing with the manuscript.
- The F30, brake-residual, symbolic-brake, and event-reduction suites passed
  all 22 tests. No CAPD integrations or new interval-existence proof were run.
- Tectonic rebuilt the PDF successfully; no undefined references or overfull/
  underfull boxes were reported. The only warning is the pre-existing amsmath
  notice about the older `\over` notation. The new discussion and figure were
  visually inspected, and `git diff --check` passed.
