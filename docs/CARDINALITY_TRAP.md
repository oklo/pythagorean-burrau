# Cardinality insight and trap

The family of rational Euclid parameters is countable and dense, whereas the
irrational parameters are uncountable.  Together with the nominally
overdetermined equation $\mathcal B(u,t)=0\in\mathbb R^3$, this is useful
motivation for expecting an exact Pythagorean miss.  It is not an inference.

In particular:

- a countable or measure-zero periodic set can contain every rational;
- a discrete zero set can contain rational points;
- density of the rationals prevents topological separation based on
  countability alone;
- “almost every parameter is nonperiodic” says nothing about every rational;
- generic transversality does not decide one specified algebraic curve;
- analyticity of the return equations does not make their zeros irrational;
- a transcendental period is no obstruction (harmonic and Kepler periods are
  basic warnings);
- congruences of raw triples disappear under common mass--length scaling unless
  tied to a genuine scale-independent dynamical invariant.

After translations and rotations are removed at zero angular momentum, planar
three-body configuration space has three degrees of freedom.  A brake point
annuls three reduced velocity components, while this tied family offers only
the two variables $(u,t)$.  That dimension count is stronger guidance than
cardinality, but it still assumes independence which symmetry or an identity
may destroy.

The clue becomes a proof only through an exact bridge, such as: no real zero;
an explicit irrationality theorem for every real zero; a Diophantine necessary
condition with no rational solutions; a sign-definite scalar obstruction; an
intersection theorem forcing a disjoint symmetry locus; or a finite exact list
of possible intersections followed by exact exclusion.

No statement in this project may use “the rationals are too sparse” as a
logical step.

## A legitimate endpoint bridge

The collapsed-pair asymptotic-intercept clock now supplies one exact use of
rational density. It satisfies
\[
\Phi_{\rm ref}'(B)=-{3\pi\over2}B^{-5/2}(1+o(1)),
\]
so every nonempty open limiting phase arc pulls back to infinitely many open
parameter intervals accumulating at $u=0$. Each interval contains rational
Euclid parameters. This is a topological statement about an open condition,
not an assertion that an isolated zero is irrational.

The second ingredient is a genuinely open restricted hyperbolic-escape phase
arc with a robust finite-$B$ terminal consequence. The incoming-tail theorem
now proves the formerly missing exact bridge:

\[
\operatorname{dist}(S_B(Y_0),
\Gamma^-_{Y_0}(\Phi_{\rm ref}(B)))=o(1)
\]
holds whenever the solution reaches the fixed section collision-free; an
earlier classical collision already excludes periodicity. The proof controls
both the long $O(B^{-3/2})$ cycle train and propagation down the incoming
restricted tail.

Consequently infinitely many open endpoint intervals, and hence infinitely
many primitive rational Euclid parameters, are nonperiodic. This is a valid
use of rational density because the dynamical condition is open and has been
transferred exactly. It does not address every rational parameter. Landing on
the parabolic separatrix remains a point condition and receives no rational
exclusion from this interval argument.

There is now a quantitative arithmetic bridge on one explicit family. For
$u_n=1/(2n)$, the exact clock values
$\Phi_{\rm ref}(B(u_n))/(2\pi)$ are equidistributed modulo one by a
van-der-Corput/Weyl argument. Hence any compact open escape arc selects a
positive-density set of exact primitive triples
$(4n^2-1,4n,4n^2+1)$, and the incoming-tail theorem proves those selected
members nonperiodic for all sufficiently large $n$. This is legitimate
because equidistribution is applied to a proved explicit phase formula and
then passed through a robust open dynamical condition. It says nothing about
the complementary phase set and therefore does not prove the full conjecture.

## An exact real bridge which is not an arithmetic bridge

The normalized finite-mass collision graph gives a different exact use of the
same phase winding.  On each sufficiently late phase cycle, fixed opposite
signs of the longitudinal amplitude bracket a segment from \(H=0\) to
\(H=B^{p/2}\), while the collision graph lies at
\(H=|T|^p\kappa_c=O(B^p)\).  Since \(B^{p/2}\gg B^p\), the
intermediate-value theorem forces either an earlier classical collision or an
exact hit of the graph.  This proves infinitely many real tied collision
parameters.

Those roots are isolated point conditions.  Unlike the open escape windows,
they do not inherit rational points from density, and equidistribution of a
reference phase does not make an IVT root rational.  Thus
`REAL_COLLISION_SAMPLING.md` is a genuine dynamical existence theorem but no
arithmetic progress on the universal rational conjecture.
