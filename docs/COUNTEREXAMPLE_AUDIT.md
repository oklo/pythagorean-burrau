# Counterexample audit

## Exact matching conditions

In the catalog normalization

\[
q_1=(-1/2,0),\quad q_2=(1/2,0),\quad q_3=(x,y),
\]

the mass labeling $(m_1,m_2,m_3)=(0.6,0.8,1)$ is the normalized
$3{:}4{:}5$ problem with exact tied point

\[
(x,y)=((0.8^2-0.6^2)/2,0.6\cdot0.8)=(0.14,0.48).
\]

An entry is a counterexample only if its masses are proportional to the three
opposite sides by one common factor, its triangle is exactly right, its Euclid
parameter is rational, the trajectory is collision-free, and its reported
return is a simultaneous inertial second brake.  Decimal proximity does not
meet any exact equality.

## Li--Liao $3{:}4{:}5$ slice

The exact point $(0.14,0.48)$ is absent from the 30 published entries for this
mass labeling.  The closest tabulated entry is

\[
F_{30}:\quad (x,y)=(0.1446319096,0.4773197126),\qquad
T=12.5809129586.
\]

Direct recomputation gives

\[
\|(x,y)-(0.14,0.48)\|\approx0.00535150,
\]

\[
r_{23}\approx0.5950803204,\qquad
r_{13}\approx0.8021124653,
\]

and

\[
1-r_{23}^2-r_{13}^2\approx0.00249500538\ne0.
\]

These gaps are many orders larger than the last displayed coordinate digit.
Therefore $F_{30}$ is a nearby ordinary-numerical periodic brake orbit, not an
exact counterexample.  The older Standish point
$(0.2061730906,0.4463433325)$ is farther away.

## Local continuation of the $F_{30}$ family

A three-equation shooting solve used the Hopf brake residual with free
variables $(x,y,T/2)$.  At $u=1/2$ it independently refined the catalog entry
to

\[
(x,y,T/2)\approx
(0.144631909634,0.477319712517,6.29045647361),
\]

with sampled minimum separation about $0.00359$.  Continuing this same root as
the mass parameter varied gave the following representative shape offsets from
the exact tied point:

| $u$ | $x-x_{tied}$ | $y-y_{tied}$ | offset norm |
|---:|---:|---:|---:|
| 0.4925 | 0.0198617 | 0.0006781 | 0.0198732 |
| 0.4950 | 0.0148127 | -0.0003875 | 0.0148178 |
| 0.5000 | 0.0046319 | -0.0026803 | 0.0053515 |
| 0.5018 | 0.0009272 | -0.0035725 | 0.0036908 |
| 0.5020 | 0.0005137 | -0.0036744 | 0.0037101 |
| 0.5030 | -0.0015598 | -0.0041932 | 0.0044739 |
| 0.5050 | -0.0057459 | -0.0052863 | 0.0078077 |

The vertical matching equation changes sign near $u\approx0.494$, whereas the
horizontal equation changes sign near $u\approx0.50225$; they do not vanish
together on this sampled local branch.  The smallest sampled norm was about
$0.00369$ near $u=0.5018$, still nonzero.  Root residuals were typically
$10^{-9}$ or smaller and relative energy drift about $10^{-9}$; close
encounters make this strictly ORDINARY NUMERICAL EVIDENCE.

This is useful family-intersection evidence, not a proof of local
nonintersection.  A validated implicit-function continuation with an interval
lower bound on the two-component offset would be required for that theorem.

## Collision and symmetry exclusions

- The Szebehely--Peters almost-Pythagorean periodic construction has a binary
  collision and relies on regularized continuation; it is outside the exact
  classical statement.
- Equal-mass catalog orbits would require all three opposite sides equal under
  the mass--side coupling.  Their initial triangle would be equilateral, so
  they cannot lie on the right-triangle curve.
- A catalog orbit with the correct masses but a freely adjusted two-parameter
  stop triangle is relevant only if both shape equations hold exactly.

## Verdict

No exact counterexample was found in the bounded published audit.  Evidence
level: ORDINARY NUMERICAL EVIDENCE about catalog entries, not a proof of either
conjecture.
