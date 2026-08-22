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

