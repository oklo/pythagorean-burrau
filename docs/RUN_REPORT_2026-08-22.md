# End-of-run report — 2026-08-22

## Outcome

**MAJOR PARTIAL THEOREM; CONJECTURE UNRESOLVED.** This run did not prove the rational Pythagorean--Burrau
nonperiodicity conjecture, prove the strong real conjecture, or produce a
rigorous counterexample. It produced exact structural reductions, proved
endpoint and first-near-collision theorems, a terminal analytic escape
certificate, a uniform computer-assisted Taylor-sign theorem, and bounded
numerical/family-intersection evidence.

## Strongest exact theorems proved

1. **First skinny-miss theorem.** There is $B_0>0$ such that every real
   Pythagorean--Burrau member with $0<B<B_0$ is collision-free through its
   first heavy-pair encounter. Levi--Civita analytic dependence gives
   \[
   r_{13,\min}={225\pi^2\over16384}B^{11}(1+O(B)),\qquad
   h_{13}=-{15\pi\over64}B^{11/2}+O(B^{13/2}).
   \]
   This treats the positive near-collision as an ordinary trajectory rather
   than substituting the collision limit.
2. **Terminal escape certificate.** Explicit strict inequalities in binary
   and outer Jacobi coordinates imply that the future solution either has a
   classical inner collision or escapes hyperbolic--elliptically, with no
   later brake. The proof uses a radial comparison energy and an integrated
   tidal-work bound. It is a conditional theorem, not yet a certificate for
   the skinny trajectory.
3. **Isosceles-right endpoint theorem.**  At the real endpoint
   $u=\sqrt2-1$, symmetry reduces the base half-separation to
   $x''<0$.  Hence $x'$ never vanishes again and a binary or triple collision
   occurs in finite time, no later than $2^{1/4}$.  Therefore this endpoint has
   no classical second brake.  The endpoint is irrational and is not an
   integer Pythagorean triple.
4. **Uniform fourth-jet theorem.**  The exact rational formula for
   $D^{(4)}(0)$ has degree-20 numerator $P_{20}$.  An exact Sturm sequence has
   10 sign variations at both $0$ and $83/200$, proving
   $D^{(4)}(0)<0$ throughout $0<u\le\sqrt2-1$.  Together with
   $D''(0)>0$, the first two nonzero defect-jet signs are uniformly $+,-$.
5. **Exact brake reduction.**  The derivative of three Hopf invariants of two
   Jacobi vectors vanishes exactly when every labelled inertial velocity
   vanishes, using zero linear and angular momentum.  This remains valid at
   syzygy, unlike mutual-distance derivatives.
6. **Primitive/rational equivalence.**  Simultaneous mass--length scaling,
   Euclid parametrization including the parity reduction, leg exchange, and
   the second-brake lemma were proved exactly.

## Conjecture status

- Full rational conjecture: **CONJECTURAL / unresolved**.
- Strong real conjecture: **CONJECTURAL / unresolved**.
- Exact real second-brake intersection found: **none**.
- Exact rational candidate found: **none**.
- Closest robust real near-brake in the bounded scan:
  $u\approx0.29256025$, $t\approx1.34345822$, with positive kinetic energy
  about $1.2231\times10^{-4}$; this is not a candidate counterexample.

## Exact identities and reductions obtained

- $I_0=abc$, and $I_0=AB$ after $c=1$.
- $U_0=ab/c+ac/b+bc/a$, and $U_0=AB+(AB)^{-1}$ after normalization.
- $H=-U_0$ and
  $\mu_0=(AB)^{3/2}+(AB)^{-1/2}$; $\mu_0$ decreases on the fundamental
  interval.  Its scale invariance applies at fixed masses, not under the
  simultaneous mass--length redundancy.
- The center of mass is initially the incenter, with inradius
  $ab/(a+b+c)=(a+b-c)/2$; this is not preserved.
- $D''(0)=2[(AB)^{-1}-AB(A+B)]>0$, and the exact original-scale formula is
  $2[c^2/(ab)-ab(a+b)/c^3]$.
- Exact degree-20 rational expression for $D^{(4)}(0)$ and the Sturm sign
  certificate described above.
- Universal zero-angular-momentum Routh-reduced kinetic energy and potential
  in three coordinates, with explicit Pythagorean brake curve
  $(R,X,Y)=(1,AB(B-A)/(A+B),AB)$.
- Exact squared-mutual-distance equations, including all velocity-square
  terms.
- Exact tight-pair initial torque
  $\dot h(0)=-B^2(A^{-2}-A)<0$.
- Exact tight-pair/outer Jacobi equations in the skinny scaling and their
  analytic Levi--Civita extension through the limiting collision.
- First transverse LC coefficient $-15\pi/128$, yielding the proved
  $B^{11}$ miss and $B^{11/2}$ specific-angular-momentum constants.
- A terminal escape certificate with tidal allowance
  $m_c\sqrt{2MR}/(v s_0^2)$.
- Exact late-plunge vector-field limit: a rectilinear equal-heavy-mass binary
  driving a massless outer particle.
- Exact restricted exchange law
  $\dot{\mathcal E}=r\dot r/[2(z^2+r^2/4)^{3/2}]$ and a proved
  parabolic-to-parabolic separatrix at the apocenter phase.
- Segment virial identities
  $\int_0^\tau Udt=2U_0\tau$ and
  $\int_0^\tau Kdt=U_0\tau$, integrated labelled force balance, and the
  initial-vector force-projection identity.

## Endpoint results

- $u=\sqrt2-1$: PROVED ANALYTICALLY to end in finite collision with no second
  brake.  Ordinary numerics place the collision near $0.5052876151$ and suggest
  it is binary; the time/type refinement is not validated.
- $u\to0$: exact negative initial tight-pair torque and a proved regularized
  first-encounter theorem:
  $h_{enc}\sim-(15\pi/64)B^{11/2}$ and
  $r_{min}\sim(225\pi^2/16384)B^{11}$. Thus an existential skinny interval is
  collision-free through this first encounter. It is not yet proved
  nonperiodic: the binary makes $O(B^{-3/2})$ cycles before the later outer
  plunge, and the scattering phase has no limit. The local plunge limit is
  proved and contains an exact zero-energy parabolic separatrix, preventing a
  phase-uniform strict-escape argument.

## Cardinality and arithmetic route

The cardinality argument was explicitly rejected as a proof.  No dynamical
real intersection has survived strongly enough to earn an arithmetic program,
and no algebraic/Diophantine necessary condition for a return parameter was
derived.  Arithmetic exclusion is therefore inactive rather than failed.

## Known periodic-family intersection results

- No exact match was found in the bounded primary-source/catalog audit.
- Li--Liao's $F_{30}$ orbit on masses $(0.6,0.8,1)$ is the closest published
  shape near miss, but not the exact tied point.
- Its three-equation brake shooting solution was independently refined and
  locally continued in mass parameter.  The two tied-shape offsets vanish at
  separated parameter values (roughly $0.494$ and $0.50225$), and the closest
  sampled combined gap was about $0.00369$ near $u=0.5018$.  This is ORDINARY
  NUMERICAL EVIDENCE, not validated local nonintersection.
- Equal-mass modern families cannot satisfy mass equals opposite side on a
  right triangle; they would force an equilateral triangle.

## Failed arguments and precise reasons

1. **Global $D>0$ cone:** ordinary high-accuracy integrations at rational
   $u=1/5$ and $1/3$ show later transverse zeros.  At $u=1/3$,
   $D(0.376)\approx-0.0046641$ after a close but positive-separation encounter.
2. **Fixed-sign angular slip:** isolated double-radial events have both slip
   signs.  A representative refined event has slip $-0.0562133$, so branch or
   index information is required.
3. **Mutual-distance derivatives as brake residual:** false at syzygy because
   transverse velocity is invisible to first distance derivatives.  Hopf
   coordinates repair this.
4. **Preserved incenter:** false; the side ratios depart immediately, as the
   positive $D''(0)$ demonstrates.
5. **Cardinality/genericity:** contains no rational-exclusion implication.
6. **Finite scans/catalog gaps:** cannot prove an infinite exact statement.

## Remaining proof obligations

1. Classify every double-radial event/branch and exclude zero angular slip, or
   find another global scalar/index obstruction.
2. Cover singular event zeros and Jacobi-chart degeneracies.
3. Control birth/death of events through collision, escape, infinite time, and
   both parameter endpoints.
4. Treat arbitrarily close but collision-free binary passages uniformly.
5. Match the exact trajectory through the $O(B^{-3/2})$ repeated binary cycles
   to the restricted incoming data, compute the finite-$B$ separatrix
   splitting, and exclude second brakes on its nonescaping side.
6. Obtain a transverse regularized analysis of the isosceles endpoint
   collision.
7. If real brake intersections are found, derive and prove a genuine exact
   arithmetic exclusion—or validate a rational counterexample.
8. A validated continuation is needed to promote the local $F_{30}$ family
   separation from ordinary evidence.

## Reproduction

```bash
cd /Users/greglaughlin/Projects/pythagorean-burrau
uv sync --all-groups
uv run pytest -q
uv run ruff check .
uv run python -m scripts.derive_exact_identities
uv run python -m scripts.derive_taylor_jet
uv run python -m scripts.derive_skinny_regularization
uv run python -m scripts.probe_skinny_regularization --epsilon 0.05
uv run python -m scripts.derive_restricted_scattering
uv run python -m scripts.probe_double_radial
uv run python -m scripts.continue_f30
uv run python -m scripts.probe_dynamics --u 1/3 --t-end 4 \
  --samples 20001 --rtol 1e-13 --atol 1e-15 --max-step 0.001
```

The repository contains pinned dependencies in `uv.lock` and 31 deterministic
tests.

## Single highest-leverage next action

Construct a matched asymptotic map from the exact skinny initial state to the
late restricted scattering problem, then calculate the finite-$B$ splitting
of its apocenter parabolic separatrix. The sign and zero set of that splitting
are now the highest-leverage route to a Level-D theorem or an exact arithmetic
condition on exceptional parameters.
