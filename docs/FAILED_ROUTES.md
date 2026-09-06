# Failed routes and negative results

These records prevent repeated mistakes. The detailed experimental history is
preserved in `../archive/history/guides/FAILED_ROUTES.md`; exact witnesses and
regression tests remain active. **A failed computation is not a theorem that
its mathematical objective is impossible.**

## Mathematical shortcuts that do not work

| Proposed shortcut | What is actually established | What would justify reopening it |
| --- | --- | --- |
| Rationals have measure zero, so none is periodic | Invalid inference; analytic reversible systems can have precisely the rationals as periodic parameters. | A proved arithmetic condition on the actual gravitational brake map. |
| More equations than parameters proves no intersection | Only a generic heuristic; transversality for this family is unproved. | A family-specific transversality or structural argument. |
| A forcing sign switch plus `w(S)=0` proves interior positivity | **DISPROVED** by the exact singular-endpoint scalar counterexample. | Prove the additional weighted terminal bound or replace the lemma. |
| Static energy, shape ordering, and torque signs force the needed history barriers | Several proposed barriers are **DISPROVED** by exact ambient witnesses. These witnesses need not be brake-reachable. | A genuine reachable-history restriction not included in the failed hypotheses. |
| Initial right-angle defect, oriented-area concavity, or torque sign persists globally | Ordinary dynamics exhibits violations of the proposed global signs. | A correctly restricted domain plus a proof that the trajectory stays there. |
| The first thin encounter forces immediate escape | The outer state is still deeply bound at that stage. | Full incoming matching, later scattering, and a terminal criterion. |
| All thin phases escape uniformly | Returning and collision regions remain; local escape arcs do not cover all phases. | A global return-map classification. |
| Local restricted escape automatically transfers for all future positive-mass time | Finite-time continuity alone is insufficient. | The existing hierarchical-energy/tidal bound or another all-time argument. |
| F1/F2 defects of opposite sign give a zero | No connected tied-periodic branch joins them; their sampled itineraries differ. | Establish a collision-free branch and continuity of the defect on it. |
| A rank-four five-equation root generates a curve | Lyapunov–Schmidt reduction can leave an isolated scalar zero such as `s²=0`. | Control the remaining scalar obstruction. |
| Free-group catalogue words distinguish full brake loops | Full brake paths retrace and are null-homotopic in collision-free shape space. | Use justified labelled half-orbit itineraries or another appropriate invariant. |
| Project F30 onto the right-triangle circle | Projection changes the IVP and need not preserve the brake. | Solve the exact tied-right problem and validate its root. |
| Decimal root digits prove rationality | They prove neither rationality nor irrationality. | An exact rational parameter and rigorous fixed-parameter existence argument. |

The [endpoint correction](FORCED_LAG_ENDPOINT_CORRECTION.md),
[exact reductions](EXACT_REDUCTIONS.md), and
[periodic symmetry audit](PERIODIC_SYMMETRY_AUDIT.md) give precise versions.

## Computational lessons, not universal impossibility results

- Independent boxes and repeated restarts destroy parameter correlation at
  close passages. The project already has better correlated chart/section tools.
- Nominal construction duration was not a valid lower bound for the damped
  exact-write gate. The repaired code uses the actual endpoint/start interval
  bounds; the old success log is not a substitute for a replay of that code.
- Low-precision long-time “near brakes” can disappear under independent replay.
- Tiny shooting residuals do not imply equally tiny reconstructed energy errors
  through a close encounter, nor do sampled separations certify collision freedom.
- Brute-force subdivision has no universal termination guarantee near unbounded
  return times. A wider validated tile is useful locally but is not the missing
  global argument.
- The archived PG1/PG2/projection benchmarks explain implementation choices.
  Repeating an already failed representation with another tolerance is not the
  default research task.

Reopen an archived experiment only when a new hypothesis, representation, or
mathematical use distinguishes it from the recorded failure. Preserve the
counterexample to the old claim when revising it.
