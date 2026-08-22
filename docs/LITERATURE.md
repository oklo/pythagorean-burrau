# Bounded literature review

Audit date: 2026-08-22.  This review is deliberately bounded: it establishes
the relevant landscape and catalog near misses, but it is not used as a proof
by exhaustion.

| Source/family | Mass ratios | Initial shape | Collision-free? | Rigorous or numerical? | Second brake? | Can it meet the Pythagorean curve? |
|---|---:|---|---|---|---|---|
| [Burrau (1913)](https://doi.org/10.1002/asna.19131950602); [Szebehely (1967)](https://doi.org/10.1073/pnas.58.1.60); [Szebehely--Peters (1967)](https://doi.org/10.1086/110355) | $3{:}4{:}5$ | Exact tied right triangle | Repeated close approaches were numerically followed | Numerical; reported elliptic--hyperbolic escape | No | It is the defining example, but one nonperiodic case cannot prove the family theorem |
| [Szebehely--Peters, “A New Periodic Solution” (1967)](https://adsabs.harvard.edu/pdf/1967AJ.....72.1187S) | $3{:}4{:}5$ | Perturbed, almost-Pythagorean stop triangle | No: binary collision occurs | Numerical periodic return after regularization | Not a classical second brake before collision | No: wrong initial triangle and collision continuation |
| [Tanikawa--Umehara--Abe (1995)](https://doi.org/10.1007/BF00692285); [Tanikawa (2000)](https://doi.org/10.1023/A:1008313912013); [Tanikawa--Mikkola (2015)](https://doi.org/10.1093/pasj/psv087) | Principally equal-mass free-fall domain | Collision curves; isosceles and collinear families | Many cataloged families contain binary/triple collision | Numerical symbolic/collision catalogs | Where applicable only after regularized continuation | Equal masses tied to opposite sides force equilateral, not right |
| [Moeckel--Montgomery--Venturelli (2012)](https://doi.org/10.1007/s00205-012-0502-y), [preprint](https://arxiv.org/abs/1109.1089) | $m_1=m_2=1$ and an open mass set | Isosceles brake-boundary constructions | The showcased periodic construction crosses binary collision | Rigorous variational/syzygy-map results | Periodic only in the regularized collision sense for that construction | Does not provide a classical tied-right counterexample |
| Standish 1970 / Yasko--Orlov entries reproduced by Li--Liao | includes $(0.6,0.8,1)$ and equal masses | General Agekyan--Anosova stop triangles | Reported collisionless numerically for relevant entries | Numerical | Yes | Correct mass slice but wrong shape, or equal-mass disjointness |
| [Li--Liao (2019)](https://doi.org/10.1016/j.newast.2019.01.003), [author PDF](https://sjliao.sjtu.edu.cn/__local/B/0D/48/5F829F37A0DCC8FAD972B6E698C_A0F02F89_1137C5.pdf?e=.pdf), [data site](https://numericaltank.sjtu.edu.cn/three-body/free-fall-3b/free-fall-3b.htm) | Nine listed ratios, including permutations of $3{:}4{:}5$ | General two-parameter stop triangles | “Collisionless” is a computed minimum-separation threshold | High-precision ordinary numerics; 316 entries | Yes: all velocities reported zero at $T/2$ | The Pythagorean mass slice contains a close but non-exact point; see audit |
| [Hristov et al. (2024)](https://doi.org/10.1007/s10569-023-10177-w), [preprint](https://arxiv.org/abs/2308.16159) | Equal masses | General free-fall domain | 12,409 reported collisionless distinct solutions | High-precision numerical, not interval validated | Yes | Equal masses cannot satisfy tied right-side lengths |
| [Hristov et al. (2025)](https://arxiv.org/abs/2503.00432) | Equal masses | Centrally symmetric free-fall subclass | 4,860 reported collisionless orbits | 100-digit numerical database, not validated existence | Symmetry imposes stop returns | Equal-mass family is disjoint from tied right triangles |
| [Bakker--Simmons (2015)](https://doi.org/10.1016/j.jde.2015.01.002), [preprint](https://arxiv.org/abs/1410.2636) | Restricted Sitnikov-like models | Massless body transverse to periodic primaries | Main theorem assumes nonsingular periodic primary motion | Rigorous separating surface in the nonsingular setting; collision case $e=1$ is numerical | Separates escape and return/capture data | Useful model for the skinny separatrix, but its theorem explicitly does not cover colliding rectilinear primaries and has no tied-mass condition |
| [McGehee (1973)](https://doi.org/10.1016/0022-0396(73)90077-6), [author PDF](https://www-users.cse.umn.edu/~mcgehee/publications/McGehee1973/McGehee1973JDiffEq14p70.pdf) | Restricted, collinear, and Sitnikov problems | Parabolic infinity after compactification | Present project verifies its sector hypotheses directly for the massless rectilinear collision-regularized map | Rigorous degenerate stable-manifold theorem | Not a brake-return theorem | Supplies the analytic parabolic curve used in the proved restricted transversality theorem, not the tied-family conclusion |
| [Standish (1971)](https://doi.org/10.1007/BF01230319); [Yoshida (1972)](https://doi.org/10.1093/pasj/24.3.391) | General masses | Separated binary--single states | Sufficient inequalities imply hyperbolic--elliptic escape | Analytic criteria; historical Burrau application uses decimal data | Excludes every later brake once certified | Useful only after an outgoing section; not satisfied after the first skinny passage |

## What the rigorous syzygy literature supplies

Moeckel--Montgomery--Venturelli define a continuous flow-induced map from a
brake boundary to first syzygy and extend it toward Lagrange triple collision
for an open mass set.  Their Jacobi--Maupertuis minimizers are collision-free
except possibly at endpoints.  This is a rigorous framework for the proposed
first-syzygy program, not a theorem that all free-fall trajectories return or
that the Pythagorean curve misses the return locus.

Modern free-fall catalogs decisively refute any general heuristic that brake
orbits do not recur.  The only viable issue is the simultaneous exact coupling
between mass ratios, opposite side ratios, and the right-angle equation.

Standish and Yoshida provide exact precedents for terminating a trajectory
once a separated outgoing state satisfies strict inequalities. The project
also proves a simpler self-contained Jacobi certificate in
ESCAPE_CRITERIA.md. Marchal--Yoshida--Sun's sharper angular boundary is not
imported wholesale because Part I describes a key containment inequality as
numerically checked rather than analytically proved.

Bakker--Simmons prove a genuine continuous separating surface for
Sitnikov-like problems with nonsingular periodic primaries. Their separate
rectilinear $e=1$ discussion is computational: the paper notes that the main
theorem does not apply when a primary collision makes the stated radius bound
vanish. It therefore supports the geometry of the present splitting program
but cannot supply the missing transversality theorem for the collision-
regularized skinny limit.

McGehee proves that parabolic asymptotic sets are analytic immersed manifolds
for several celestial-mechanics maps with identity linearization at infinity.
For the present restricted limit, the eccentric-anomaly system and the
compactification $z=2/x^2$ produce an analytic collision-regularized
stroboscopic map. Its leading homogeneous terms satisfy McGehee's sector
hypotheses exactly. The project additionally proves contraction of tangents
on the resulting fixed-phase stable graph, which is the ingredient needed to
turn the finite Jacobi growth sign into restricted transversality. This still
has no direct finite-$B$ or tied-mass conclusion.

## Audit conclusion

No inspected primary source reports an exact classical collision-free
Pythagorean--Burrau periodic orbit.  No inspected catalog gives a validated
real intersection with the tied curve.  Conversely, these finite and mostly
numerical sources do not prove nonintersection.  The strongest catalog warning
is the close $F_{30}$ near miss recorded in `COUNTEREXAMPLE_AUDIT.md`.  A local
ordinary-numerical continuation of that periodic family reduces its shape gap
but finds no tied-curve crossing; validated continuation remains open.
