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
| Local $F_{30}$ periodic branch does not numerically hit the tied curve | ORDINARY NUMERICAL EVIDENCE | Coordinate offsets cross zero at separated $u$ values; not validated continuation |
| Initial tight-pair torque $\dot h(0)=-B^2(A^{-2}-A)<0$ | EXACT SYMBOLIC IDENTITY | Skinny limit; does not by itself bound the full encounter |
| Skinny first tight-pair encounter is collision-free for all sufficiently small $B>0$ | PROVED ANALYTICALLY | Levi--Civita analytic dependence on a fixed outgoing section; both outer separations are uniform; says nothing about later encounters |
| $h_{13}=-(15\pi/64)B^{11/2}+O(B^{13/2})$ and $r_{13,\min}=(225\pi^2/16384)B^{11}(1+O(B))$ | PROVED ANALYTICALLY | First encounter only; independently checked factors, frame, and time scaling |
| Terminal binary--escaper inequalities imply escape or classical collision and no later brake | PROVED ANALYTICALLY | Conditional theorem on a separated outgoing Jacobi section; strict inequalities can be interval checked |
| The first skinny outgoing section satisfies a terminal escape criterion | DISPROVED | Outer radial energy margin is $-2+O(B)$; a later slingshot is indispensable |
| Late-plunge scaling converges locally to the equal-heavy-mass rectilinear restricted system | PROVED ANALYTICALLY | Vector-field statement on compact nonsingular sets; extends across prescribed binary collisions after LC regularization when the light particle stays separate; global matching remains open |
| The restricted apocenter phase has a parabolic-to-parabolic light-particle separatrix | PROVED ANALYTICALLY | Sturm comparison, quantitative large-speed escape, and launch-speed boundary; the prescribed heavy binary is collision-regularized |
| Every limiting plunge phase has a strict positive escape margin | DISPROVED | The exact parabolic separatrix has zero outgoing energy; this does not decide any finite-$B$ orbit |
| Exact collapsed-pair fall, section clock, and $\Phi_{\rm ref}=\pi B^{-3/2}-(\pi/4)B^{-1/2}-(15\pi/32)B^{1/2}+O(B^{3/2})$ | EXACT SYMBOLIC IDENTITY | Decoupled reference problem only; not yet the phase of the true orbit |
| Every open reference phase arc pulls back to infinitely many intervals containing rational Euclid parameters | PROVED ANALYTICALLY | Uses $\Phi_{\rm ref}'\sim-(3\pi/2)B^{-5/2}$ and density of rational $u$; requires true $o(1)$ phase matching before it has dynamical force |
| True skinny phase satisfies $\Phi_{\rm true}=\Phi_{\rm ref}+o(1)$ on an incoming restricted section | CONJECTURAL | Requires uniform LC averaging across $O(B^{-3/2})$ collision-like binary cycles |
| Finite-$B$ late-plunge field has $Z_x''=3B^2r^3/(16d^5)+O(B^3)$ and the stated radial/vertical coefficients | EXACT SYMBOLIC IDENTITY | Taylor coefficients of the exact Jacobi field on the limiting symmetric orbit; does not make that orbit invariant at $B>0$ |
| Centered $O(B)$ backreaction has zero linear whole-line energy splitting | EXACT SYMBOLIC IDENTITY | Parity cancellation for a reversible two-sided variational solution; generic retarded boundary data require a phase gauge |
| Naive time-shift phase Melnikov integrand is a total derivative | EXACT SYMBOLIC IDENTITY | Shows zero-at-infinity conditions do not fix the parabolic time-translation mode |
| Incoming and outgoing restricted parabolic curves meet transversely at apocenter | ORDINARY NUMERICAL EVIDENCE | Finite-cutoff section slopes converge near $-0.90623$; no analytic or interval enclosure |
| Restricted separatrix speed obeys $\sqrt8<v_*<4$ | PROVED ANALYTICALLY | Fixed-softening comparison for turning and an explicit early-section escape estimate |
| The even transversality Jacobi field stays positive through the first binary collision, and $a>0$ after $\theta=\pi/8$ | PROVED ANALYTICALLY | Exact Wronskian identity; uses monotonicity of the proved separatrix and regularized collision |
| $h'(\pi/4)>0$ for the transversality Jacobi field | ORDINARY NUMERICAL EVIDENCE | Approximately $0.0378487$; a finite validated enclosure would imply growth of $h$ and, after parabolic-manifold regularity, transverse crossing |
| Finite-$B$ separatrix has phase displacement $\sigma_*(B)=2B/\kappa+o(B)$ | CONJECTURAL | Needs incoming-energy matching, gauge-fixed $\kappa\ne0$, and uniform remainder estimates |
| Segment virial and initial-vector force-projection identities | PROVED ANALYTICALLY | Necessary for a hypothetical collision-free second brake; no contradiction yet |

## Dimension count (guidance only)

After translation and rotation reduction at zero angular momentum there are
three configuration degrees of freedom.  A brake requires three quotient
velocities to vanish.  The tied family and return time provide two continuous
unknowns $(u,t)$.  This nominal codimension-one miss is **CONJECTURAL** as an
obstruction because component dependence, symmetry, and singular limits can
change the rank.
