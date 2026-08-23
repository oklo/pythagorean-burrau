# End-of-run report — 2026-08-22

## Outcome

**MAJOR PARTIAL THEOREM (LEVEL D); FULL CONJECTURE UNRESOLVED.** This run did not prove the rational Pythagorean--Burrau
nonperiodicity conjecture, prove the strong real conjecture, or produce a
rigorous counterexample. It did prove nonperiodicity on infinitely many open
real skinny parameter intervals and hence for infinitely many primitive
Pythagorean triples. It also produced exact structural reductions, proved
endpoint and first-near-collision theorems, a terminal analytic escape
certificate, a uniform computer-assisted Taylor-sign theorem, and bounded
numerical/family-intersection evidence.

## Strongest exact theorems proved

1. **Incoming-tail and infinite-subfamily theorem.** For any fixed sufficiently
   large incoming scaled section, the exact skinny state either has already
   ended in a classical collision or converges uniformly to the restricted
   incoming parabolic state with intercept $\Phi_{\rm ref}(B)$. Exact LC normal
   invariants, radius-dependent energy/torque bounds, and weighted transverse
   uniqueness cover every collision-like binary passage. A compact restricted
   hyperbolic-escape arc therefore transfers to infinitely many open exact
   parameter intervals. Every such interval is nonperiodic, and rational
   density yields infinitely many distinct primitive Pythagorean triples.
2. **First skinny-miss theorem.** There is $B_0>0$ such that every real
   Pythagorean--Burrau member with $0<B<B_0$ is collision-free through its
   first heavy-pair encounter. Levi--Civita analytic dependence gives
   \[
   r_{13,\min}={225\pi^2\over16384}B^{11}(1+O(B)),\qquad
   h_{13}=-{15\pi\over64}B^{11/2}+O(B^{13/2}).
   \]
   This treats the positive near-collision as an ordinary trajectory rather
   than substituting the collision limit.
3. **Terminal escape certificate.** Explicit strict inequalities in binary
   and outer Jacobi coordinates imply that the future solution either has a
   classical inner collision or escapes hyperbolic--elliptically, with no
   later brake. The proof uses a radial comparison energy and an integrated
   tidal-work bound. Incoming-tail transfer now verifies its hypotheses on
   infinitely many skinny phase windows.
4. **Isosceles-right endpoint theorem.**  At the real endpoint
   $u=\sqrt2-1$, symmetry reduces the base half-separation to
   $x''<0$.  Hence $x'$ never vanishes again and a binary or triple collision
   occurs in finite time, no later than $2^{1/4}$.  Therefore this endpoint has
   no classical second brake.  The endpoint is irrational and is not an
   integer Pythagorean triple.
5. **Uniform fourth-jet theorem.**  The exact rational formula for
   $D^{(4)}(0)$ has degree-20 numerator $P_{20}$.  An exact Sturm sequence has
   10 sign variations at both $0$ and $83/200$, proving
   $D^{(4)}(0)<0$ throughout $0<u\le\sqrt2-1$.  Together with
   $D''(0)>0$, the first two nonzero defect-jet signs are uniformly $+,-$.
6. **Exact brake reduction.**  The derivative of three Hopf invariants of two
   Jacobi vectors vanishes exactly when every labelled inertial velocity
   vanishes, using zero linear and angular momentum.  This remains valid at
   syzygy, unlike mutual-distance derivatives.
7. **Primitive/rational equivalence.**  Simultaneous mass--length scaling,
   Euclid parametrization including the parity reduction, leg exchange, and
   the second-brake lemma were proved exactly.
8. **Validated restricted Jacobi sign.** In the collision-regularized
   rectilinear restricted limit, CAPD interval Taylor integration on 256
   overlapping launch-speed slabs proves
   \[
   h'(\pi/4)>14/625>0
   \]
   for the parabolic-separatrix Jacobi field. Compactification $z=2/x^2$ then
   puts the time-$\pi$ map under McGehee's degenerate stable-manifold theorem;
   stable tangents contract, contradicting the validated Jacobi growth under
   hypothetical tangency. Thus the restricted crossing is transverse.
9. **Restricted phase-window theorem.** The transverse splitting function has
   opposite signs on two one-sided apocenter phase arcs. One arc gives
   hyperbolic outer escape and the other a finite outer turn. The proved
   incoming-tail theorem and exact asymptotic-intercept clock produce
   infinitely many open terminal nonperiodicity intervals containing rational
   Euclid parameters.
10. **Pre-plunge matching theorem.** For every $0<\alpha<1/6$, either a prior
   inner collision occurs or the orbit reaches $\rho=B^\alpha$ after the full
   $O(B^{-3/2})$ early cycle train with matched outer state and
   $\chi_\alpha=\Phi_{\rm ref}+o(1)$. Independent audit repaired the
   regularized phase observable and a radius-weighted velocity estimate.
11. **Explicit positive-density primitive family.** For
   $(a_n,b_n,c_n)=(4n^2-1,4n,4n^2+1)$, the exact reference cycle count is an
   algebraic function $F(n)$ with $F''(x)\sim(3/8)x^{-1/2}$. Van der Corput's
   estimate and Weyl's criterion prove equidistribution modulo one. Every
   compact restricted escape arc therefore selects a set of indices of
   density $|J|/(2\pi)$, all sufficiently large members of which are
   nonperiodic. Thus the proved nonperiodic subset of this explicit primitive
   family has positive lower natural density. The dynamical conclusion
   inherits the validated restricted-transversality input.
12. **Restricted turn-resonance theorem.** On the finite-turn side of the
   restricted separatrix, continuity and the exact mean-anomaly clock produce
   a nonsingular brake state of the collision-regularized restricted flow for
   every sufficiently large binary-apocenter index. A phase-uniform
   Kepler-energy comparison proves
   $Z_{{\rm t},n}=(2n)^{2/3}(1+o(1))$ and
   $T_n=\pi n/2+o(1)$. These are not classical finite-$B$ counterexamples;
   intervening heavy-binary collisions are regularized in the limiting model.
   They disprove the proposed shortcut that the restricted finite-turn side
   has no brake states and reduce the next endpoint step to finite-$B$
   resonance splitting.

## Conjecture status

- Full rational conjecture: **CONJECTURAL / unresolved**.
- Strong real conjecture: **CONJECTURAL / unresolved**.
- Infinite primitive Pythagorean subfamily: **PROVED ANALYTICALLY** through
  infinitely many open skinny real parameter intervals.
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
  $r_{min}\sim(225\pi^2/16384)B^{11}$. The full $O(B^{-3/2})$ cycle train and
  incoming parabolic tail are now matched. Infinitely many open skinny
  intervals are proved nonperiodic by transfer of a restricted hyperbolic-
  escape window. The intervening finite-turn side contains infinitely many
  restricted brake-state resonances; their finite-$B$ splitting and the exact
  separatrix phases remain unresolved, so no punctured neighborhood theorem
  is claimed.

## Cardinality and arithmetic route

The cardinality argument was explicitly rejected as a proof. Exact endpoint
sampling is now active in a legitimate form: the reference phases on
$(4n^2-1,4n,4n^2+1)$ are equidistributed and select a positive-density
nonperiodic subset. No algebraic/Diophantine condition excluding rational
return parameters has been derived, so arithmetic exclusion of all remaining
members is still inactive.

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
5. Compute the finite-$B$ separatrix and turn-resonance splitting, then exclude
   second brakes after one or more outer turns; repeated-cycle and
   incoming-tail matching are proved.
6. Obtain a transverse regularized analysis of the isosceles endpoint
   collision.
7. If real brake intersections are found, derive and prove a genuine exact
   arithmetic exclusion—or validate a rational counterexample.
8. A validated continuation is needed to promote the local $F_{30}$ family
   separation from ordinary evidence.

## Continuation: matched clock and finite transversality reduction

The endpoint attack was continued beyond the local parabolic-separatrix
theorem.

1. The collapsed-pair outer fall is now exact on every nonsingular radius
   section. Its accumulated binary phase is
   \[
   \Phi_{\rm ref}
   =\pi B^{-3/2}-{\pi\over4}B^{-1/2}
   -{15\pi\over32}B^{1/2}+O(B^{3/2}),
   \]
   with $\Phi_{\rm ref}'\sim-(3\pi/2)B^{-5/2}$. Every open reference phase arc
   therefore has infinitely many parameter preimages containing rational
   Euclid parameters. The full $O(B^{-3/2})$ early cycle train is now matched
   at $\rho=B^\alpha$, $0<\alpha<1/6$, in the exact finite-$B$ intercept
   gauge. Propagation down the restricted incoming tail to fixed $Y_0$ is now
   proved using radius-dependent energy/torque estimates, exact LC normal
   invariants, and weighted transverse uniqueness.
2. The exact finite-$B$ local Jacobi field was expanded through order $B^2$:
   \[
   r''=-{2\over r^2}-B{r\over d^3}+{B^2\over2r^2}+O(B^3),
   \]
   \[
   Z_y''=-{2z\over d^3}-B{z\over d^3}
   +B^2{z\over2d^3}+O(B^3),\qquad
   Z_x''=B^2{3r^3\over16d^5}+O(B^3).
   \]
   Centered order-$B$ energy splitting cancels by parity; direct
   longitudinal bending starts at $B^2$.
3. A naive whole-line phase Melnikov integral is not well posed until the
   parabolic epoch is fixed. The global time-translation field $\zeta=z'$
   makes its integrand exactly
   \[
   {d\over d\theta}\left({rr'\over2d^3}\right).
   \]
   The correct invariant target is the transverse crossing of incoming and
   outgoing parabolic curves on $z=0$.
4. That restricted transversality problem now has a finite sufficient
   certificate. Exact comparison proves
   \[
   \sqrt8<v_*<4.
   \]
   For the even Jacobi field $h''=ah$, $h(0)=v_*$, $h'(0)=0$, an exact
   Wronskian argument proves $h>0$ through the first binary collision, and
   $a>0$ after $\theta=\pi/8$. Hence the single sign
   \[
   h'(\pi/4)>0
   \]
   forces $h$ to grow. CAPD interval integration now proves the stronger
   rational bound $h'(\pi/4)>14/625$. The analytic compactified-map argument
   then proves stable/unstable transversality. The slope difference near
   $-0.90623$ remains only an ordinary numerical estimate of its magnitude.
5. The finite-turn side contains a brake-state resonance at every sufficiently
   large apocenter index, with
   $Z_{{\rm t},n}=(2n)^{2/3}(1+o(1))$. At any fixed resonance, the exact radial
   Jacobian factors as
   $D_n=-(Z_nz_{\theta\theta}/2)\mathcal A'(\phi_n)$. Conditional on a simple
   root, the double-radial branch reduces to one scalar.  For exclusion alone,
   simplicity is unnecessary: first-order transverse compactness suffices.
6. The scalar's first formal coefficient is now explicit:
   \[
   C_n=-{3\over4Z_n}\int_{-\infty}^{T_n}{r^2zp\over d^5}\,d\theta,
   \qquad p''={(r^2-2z^2)\over d^5}p.
   \]
   Weighted first-order incoming matching is now proved in divided LC normal
   variables. A rotation-Wronskian theorem and half-line
   Jost factorization give
   \[
   Z_nC_n\to-\mathscr W_\infty/2,
   \qquad \mathscr W_\infty=2k_+(0)k_+'(0).
   \]
   Analytic tail bounds plus a pinned CAPD enclosure prove
   $k_+(0)>7/20$, $k_+'(0)>3/5$, and hence
   $\mathscr W_\infty>21/50$. Thus $C_n<0$ for every sufficiently late
   restricted resonance. Consequently every fixed sufficiently late resonance
   has a finite-$B$ neighborhood containing no full labelled brake, without a
   simplicity hypothesis. Exact outgoing torque and LC block estimates then
   strengthen this to a first-turn exclusion uniform along the entire
   accumulating resonance layer. Separately,
   the explicit family $(4n^2-1,4n,4n^2+1)$ is equidistributed in reference
   phase and has a positive-density nonperiodic subset.

These results strengthen the outcome to a major Level-D partial theorem, not a
proof of the full rational or strong real conjecture. No real or rational
second-brake candidate was found.

## Reproduction

```bash
cd /Users/greglaughlin/Projects/pythagorean-burrau
uv sync --all-groups
uv run pytest -q
uv run ruff check .
uv run python -m scripts.derive_exact_identities
uv run python -m scripts.derive_taylor_jet
uv run python -m scripts.derive_skinny_regularization
uv run python -m scripts.derive_skinny_matching
uv run python -m scripts.probe_skinny_regularization --epsilon 0.05
uv run python -m scripts.derive_restricted_scattering
uv run python -m scripts.derive_finite_plunge
uv run python -m scripts.probe_restricted_transversality --cutoffs 10 20 40
uv run python -m scripts.probe_restricted_turn_map \
  --offsets -0.1 -0.05 -0.02 0.02 0.05 0.1 \
  --phase-span 30000 --max-step 0.03
uv run python -m scripts.probe_double_radial
uv run python -m scripts.continue_f30
uv run python -m scripts.probe_dynamics --u 1/3 --t-end 4 \
  --samples 20001 --rtol 1e-13 --atol 1e-15 --max-step 0.001
uv run pytest tests/test_incoming_tail.py -q
mkdir -p /private/tmp/pythagorean-paper-build
tectonic -X compile paper/main.tex --outdir /private/tmp/pythagorean-paper-build

# after building pinned CAPD 6.1.0 with native intervals
sh scripts/run_capd_restricted_transversality.sh \
  /path/to/CAPD /path/to/CAPD/build-native
bash scripts/run_capd_restricted_transverse_scattering.sh \
  /path/to/CAPD /path/to/CAPD/build-native
```

The repository contains pinned Python dependencies in `uv.lock`, a pinned CAPD
commit in both verifier wrappers, and 67 deterministic symbolic/unit tests.

## Single highest-leverage next action

Construct the later-encounter transition law for normalized outer angular
momentum. The first-turn layer is now closed uniformly:
\[
 {Y\times\dot Y\over B^{3/2}}(t_{\rm first\ turn})
 \longrightarrow{\mathscr W_\infty\over2}>{21\over100}.
\]
The returning-tail theorem already propagates the sign back to a fixed large
incoming section. The centered parabolic boundary of the compact second-
encounter map is now closed exactly:
\[
 \mathcal C_{2,\mathrm{par}}=-2\gamma\mathscr W_\infty>{21\over6250},
 \qquad -{1\over100}<\gamma<-{1\over250}.
\]
The highest-leverage next action is to validate the captured-component
classification and $\mathcal C_2>0$ on its compact interior, then analyze the
$\phi\to\pi$ triple-collision endpoint in a McGehee chart. These are required
before excluding a second or later brake.
