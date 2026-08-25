# Independent second-agent handoff

Date: 2026-08-25

## Purpose

The primary agent is building a correlated, interval-valued Levi--Civita
graph for a real parameter tile beginning at (u=0.29).  The committed
theorem already proves that every real

\[
  0.29\leq u\leq 0.29002
\]

is collision-free through the first positive maximum of the center-of-mass
moment of inertia (I), and that this maximum is not a labelled brake.  The
active, uncommitted extension has reached the second strict minimum and is
being reconditioned through two subsequent pair--13 scatterings.  Ordinary
numerics at (u=0.29) show a particularly short possible endgame:

| event | ordinary time | role |
|---|---:|---|
| first positive (I)-maximum | 1.33420284 | already interval-certified |
| second (I)-minimum | 1.93418004 | active interval proof reaches it |
| second (I)-maximum | 2.66963239 | active target |
| third (I)-minimum | 2.92484776 | strict, pair--13 close passage |
| third (I)-maximum | 3.03530039 | visibly non-brake |
| fourth (I)-minimum | 3.46855240 | strict, pair--13 close passage |
| binary--escaper certificate | about 4.0 | binary ({2,3}), escaper 1 |

This suggests that a validated continuation through (t\simeq4) could prove
genuine nonperiodicity on a nonempty real interval, rather than only a finite
prefix theorem.

## Noninterference rule

The primary agent currently has uncommitted changes in exactly these files:

- `src/fable/verification/burrau_lc_certificate_capd.cpp`
- `tests/fable/test_tied_first_maximum_charts.py`

Do **not** edit, format, stage, or commit either file.  Do not run a broad
formatter over the repository.  If sharing the same worktree, add only new
files and do not run `git add` or `git commit`; return a handoff report instead.
The cleanest arrangement is a separate git worktree and branch based on
commit `cade821` (which contains this handoff), for example an
`agent2-middle-escape` branch.  The primary agent will manually port useful
results.

## Highest-leverage task: exact terminal escape map

Derive and independently check the general-(u) terminal binary--escaper
certificate directly in the pair--23 Levi--Civita chart.  This is separate
from the primary agent's current propagation work and will be needed once the
validated graph reaches the final leg.

The normalized masses are

\[
 A=\frac{1-u^2}{1+u^2},\qquad
 B=\frac{2u}{1+u^2},\qquad
 (m_1,m_2,m_3)=(A,B,1).
\]

The pair--23 chart has state

\[
 (w_r,w_i,z_r,z_i,h,G_x,G_y,P_x,P_y,t,u,J).
\]

Its physical meanings are

\[
 g=q_3-q_2=w^2,qquad
 \dot g=\frac{2wz}{|w|^2},qquad
 G=q_1-C_{23},\qquad
 \dot G=P,
\]

where (C_{23}=(Bq_2+q_3)/(B+1)).  Thus the prospective escaping hierarchy
is already represented without reconstructing absolute positions:

\[
 M=B+1,quad M_{\rm tot}=A+B+1,quad
 r=|g|=|w|^2,quad \rho=|G|,
\]

\[
 \dot\rho=\frac{G\cdot P}{\rho},\qquad
 E_{23}=\frac12|\dot g|^2-\frac{M}{r}.
\]

For the repository's terminal theorem with (eta=4), check the following
general-mass specialization carefully against `docs/ESCAPE_CRITERIA.md` and
`src/dynamics/escape_certificate.py`:

\[
 R=\frac{M}{\eta},\qquad d=\rho-R,
\]

\[
 E_{\rho}=\frac12\dot\rho^2-\frac{M_{\rm tot}}{d},
 \qquad v_{\infty}=\sqrt{2E_{\rho}},
\]

\[
 \Delta=\frac{A\sqrt{2MR}}{v_{\infty}d^2},qquad
 -\eta-E_{23}-\Delta>0.
\]

Together with (d>0), (dot\rho>0), and (E_\rho>0), this should imply
that body 1 escapes while the ({2,3}) binary remains bound, hence that no
later brake is possible.  Verify every mass factor and orientation rather
than accepting the displayed formulas on authority.

### Requested deliverables

Please add only new files, preferably:

- `src/symbolic/middle_escape.py`: exact SymPy reconstruction and margin
  formulas for the pair--23 chart;
- `tests/test_middle_escape_symbolic.py`: exact regression tests against
  arbitrary physical (q_i,v_i), including translation invariance and the
  reconstruction of (g,G,\dot g,P);
- `docs/AGENT2_MIDDLE_ESCAPE.md`: derivation, theorem mapping, all caveats,
  and CAPD-ready pseudocode using outward-rounded intervals.

The most valuable result is a short human-readable proof that the chart
variables feed the existing escape theorem with exactly the claimed mass
factors.  An exact symbolic identity is useful even if no validator is run.

## Second task: bounded ordinary reconnaissance of the endgame

If time remains, build a new diagnostic script, without modifying existing
scripts, that maps the event/section topology near (u=0.29).  Suggested
path:

- `scripts/probe_middle_escape_endgame.py`

This is design evidence only, never a proof.  On a modest grid, initially
(0.2895\le u\le0.2905), report:

1. all zeros of (J=\dot I) through the first firing of the binary--escaper
   certificate;
2. the sign of (U-2U_0) at every minimum and a full brake residual at every
   maximum;
3. which pair is closest at every close passage;
4. pair--13 and pair--23 LC coordinates at candidate geometric sections;
5. transversality margins for the proposed sections;
6. the earliest simple rational physical time at which the (eta=4)
   pair--23 escape certificate has comfortable margins;
7. the largest visibly stable (u)-subinterval with the same labelled event
   ordering.

The primary propagation currently uses, or is testing, these sections:

- pair--13 (w_r=0) near (t=1.919), with (w_r) decreasing;
- pair--13 (w_r=-2/5) on the subsequent outgoing leg;
- pair--13 (z_r=0) near (t=2.329), with (z_r) decreasing.

Please test whether better rational coordinate values give larger normal
speeds or larger collision margins.  After the second maximum, pay special
attention to the pair--13 passages near (t=2.925) and (t=3.469), and to a
safe pair--13-to-pair--23 chart switch around (t=3.6).  Use DOP853 with
precision/tolerance refinement, but label every conclusion **ORDINARY
NUMERICAL EVIDENCE**.

## Optional analytic fallback

If the terminal task is completed and a nonnumerical problem is preferred,
an independent attack on the scalar brake-history inequality is welcome.
The relevant reduction is summarized in `docs/STATUS.md`,
`docs/EXACT_REDUCTIONS.md`, and `docs/ISOSCELES_SYZYGY_THRESHOLD.md`:

\[
 (\log k)_s=\frac{W}{\delta}\,\mathcal A(u,x,y)(\eta-h),
 \qquad \mathcal A>0.
\]

The missing global interior statement is a reachable-history bound that
prevents a dangerous contact (eta=h), equivalently an amplitude estimate
(Z<Z_J=P/S) on the (S<0) region.  Static energy, torque signs, and
first-return signs have explicit counterexamples recorded in
`docs/FAILED_ROUTES.md`; any proposed proof must use correlation inherited
from the brake launch.  Work on this only after reading those counterexamples.
Do not offer genericity, countability, or finite scans as a proof.

## What to return

Return:

1. exact new identities and their proof status;
2. tests and reproduction commands;
3. any corrected mass factor or sign convention;
4. the best terminal section time and its numerical margins;
5. the widest endgame topology interval seen numerically;
6. failures or conditioning traps;
7. a list of files added, with no changes to the two protected files.

Do not claim resolution of the conjecture from ordinary integration.  A
useful handoff either supplies exact formulas/tests that can be inserted into
the validator, or materially improves the validated-section design.
