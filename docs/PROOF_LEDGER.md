# Proof ledger

Allowed evidence labels are used verbatim.

| Claim | Status | Dependencies and scope |
|---|---|---|
| Simultaneous mass--length scaling and primitive reduction | PROVED ANALYTICALLY | Newton equations; preserves labelled return and collisions |
| Rational $u$ parametrizes exactly the ordered primitive family after reduction | PROVED ANALYTICALLY | Euclid theorem and parity/gcd lemma |
| Leg swap is $u\mapsto(1-u)/(1+u)$ | EXACT SYMBOLIC IDENTITY | Dynamically realized by reflection plus labels 1--2 exchanged |
| Second-brake equivalence | PROVED ANALYTICALLY | Classical uniqueness on a collision-free segment; $2\tau$ is a period, not automatically minimal |
| Hopf residual vanishes iff all inertial velocities vanish at $P=L=0$ | PROVED ANALYTICALLY | Away from triple collision; covers syzygy and every collision-free state |
| Initial COM equals incenter | PROVED ANALYTICALLY | Initial mass equals opposite side; not a preserved property |
| $I_0=abc$ and normalized $I_0=AB$ | EXACT SYMBOLIC IDENTITY | Convention $I=\sum m_i|q_i-q_{CM}|^2$ |
| $U_0=AB+(AB)^{-1}$ and $H=-U_0$ | EXACT SYMBOLIC IDENTITY | Normalized family |
| $\mu_0$ decreases on the fundamental interval | PROVED ANALYTICALLY | Fixed-mass configurational measure; not invariant under simultaneous mass--length scaling |
| $\ddot D(0)=2[(AB)^{-1}-AB(A+B)]>0$ | EXACT SYMBOLIC IDENTITY | Full real family; local in time only |
| Exact rational formula for $D^{(4)}(0)$ | EXACT SYMBOLIC IDENTITY | Derived by twice differentiating Newton's force |
| $D^{(4)}(0)<0$ on the fundamental interval | PROVED BY COMPUTER-ASSISTED ARGUMENT | Exact 21-term Sturm sequence; endpoint variations both 10 |
| Explicit zero-angular-momentum reduced Lagrangian and brake curve | EXACT SYMBOLIC IDENTITY | Valid before collision; gauge uses $r_{12}>0$ |
| Global inequality $D(t)>0$ | ORDINARY NUMERICAL EVIDENCE | Strongly falsified at $u=1/3$ near $t=0.376$; not used as a theorem |
| Isosceles-right endpoint has no second brake and reaches finite collision | PROVED ANALYTICALLY | Reflection-reduced half-base has $x''<0$; endpoint is irrational |
| No real second-brake intersection | CONJECTURAL | Strong real conjecture |
| No rational second-brake intersection | CONJECTURAL | Main conjecture |
| No exact counterexample in bounded published-catalog audit | ORDINARY NUMERICAL EVIDENCE | Catalog coverage is not exhaustive and entries are not validated existence proofs |
| Initial tight-pair torque $\dot h(0)=-B^2(A^{-2}-A)<0$ | EXACT SYMBOLIC IDENTITY | Skinny limit; does not by itself bound the full encounter |
| Skinny $B^{11/2}$ angular momentum and $B^{11}$ miss scale | CONJECTURAL | Formal frozen-tide asymptotics; uniform remainders absent |

## Dimension count (guidance only)

After translation and rotation reduction at zero angular momentum there are
three configuration degrees of freedom.  A brake requires three quotient
velocities to vanish.  The tied family and return time provide two continuous
unknowns $(u,t)$.  This nominal codimension-one miss is **CONJECTURAL** as an
obstruction because component dependence, symmetry, and singular limits can
change the rank.
