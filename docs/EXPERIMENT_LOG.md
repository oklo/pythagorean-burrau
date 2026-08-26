# Experiment log

## 2026-08-23: one scattering invariant controls all late turn coefficients

- For the incoming-normalized transverse restricted field $p$, derived the
  exact rotation-Wronskian identity
  \[
  W=zp'-z'p,\qquad W'={3r^2zp\over2d^5}.
  \]
- Proved with phase-uniform outgoing-tail bounds that every selection of late
  apocenter-turn resonances obeys
  \[
  Z_nC_n\longrightarrow-{\mathscr W_\infty\over2},\qquad
  \mathscr W_\infty=W(+\infty)
  \]
  on the centered parabolic separatrix. Thus one scalar validation replaces
  infinitely many separate $C_n\ne0$ tests.
- Ordinary finite-cutoff probes at $K=10,20,40,80,160$ gave respectively
  $W(K)=0.447762,0.446267,0.445875,0.445769,0.445741$. These are not interval
  enclosures.
- Time symmetry factors the invariant as
  $\mathscr W_\infty=2k_+(0)k_+'(0)$. Analytic outgoing-tail bounds and a
  pinned CAPD enclosure through eccentric anomaly $320\pi$ prove
  $k_+(0)>7/20$, $k_+'(0)>3/5$, hence
  $11/25<\mathscr W_\infty<9/20$. The verifier checks the upper bracketing launch
  on every accepted time step, rather than inferring first-leg escape from its
  endpoint alone.
- The exact symmetric outer-torque factorization was independently audited.
  It proves the extra cubic skinny cancellation through the early overlap,
  and the subsequent divided-LC-invariant bootstrap proves first-order
  quotient propagation through the full incoming tail.  An adversarial pass
  checked complete and partial collision blocks, the two-scale Volterra norm,
  the finite negative-energy correction, and fixed-segment propagation.
- Combining that theorem with $C_n<0$ proves a finite-$B$ no-brake
  neighborhood around every fixed sufficiently late restricted resonance.
  This compactness argument does not require radial-root simplicity.  It is
  not uniform as $n\to\infty$.
- Identified the exact crossover mode at a physical first-turn radius
  $R=BZ=O(1)$. The outgoing inner field has nonrotation term
  $-(\mathscr W_\infty)\sqrt z$, while the collision-normalized transverse
  Jacobi field on the macroscopic radial Kepler arc reaches apocenter with
  velocity $-1/R$. This gives the candidate signed expansion
  $\dot Y_x=-(\mathscr W_\infty/2R)B^{3/2}+o(B^{3/2})$ for fixed $R$.
- Replaced the nonuniform Cartesian remainder by normalized outer angular
  momentum. Exact torque, LC block, and radial-concavity estimates prove
  $(Y\times\dot Y)/B^{3/2}\to\mathscr W_\infty/2$ uniformly in first-turn
  height. Together with the validated sign, this excludes a full labelled
  brake at every first turn in the accumulating skinny parabolic layer.
- The orientation-reversed tail estimate carries the same sign back to a
  fixed section before the second central encounter. A bounded ordinary scan
  of that compact map found $\widetilde W>0$ at all 16 sampled captured
  phases, while both signs occur on scattering phases. The resulting target
  $\mathcal C_2(\psi)>0$ on captured components is conjectural, not a
  validated phase-continuum statement.
- The extended pinned transverse certificate proves
  $-1/100<\gamma<-1/250$. Evenness and determinant one give the exact
  second-encounter parabolic-endpoint value
  $\mathcal C_{2,\mathrm{par}}=-2\gamma\mathscr W_\infty>21/6250$.
  The remaining phase endpoint is the restricted triple-collision limit.
- At that singular endpoint, the exact restricted equilateral collision ray
  has transverse Euler coefficient $-1/(18\sigma^2)$ and indicial exponents
  $(3\pm\sqrt7)/6$. This supplies the correct fractional-power McGehee
  matching problem but does not yet determine the selected coefficient sign.
- A focused finite-cutoff probe near center phase $\phi=\pi$ stabilizes the
  predicted renormalizations: $z_t/(\pi-\phi)^{2/3}$ moves toward $0.39$,
  $p(0)/(\pi-\phi)^{\alpha_-}$ toward $0.50$, and
  $(\pi-\phi)^{(\sqrt7-1)/6}\mathcal C_2$ remains positive near $1$. This is
  ordinary evidence for a nonzero slow mode and positive universal transfer.
  Reproduce with
  `python -m scripts.probe_second_encounter --cutoff 40 --phases 8
  --phase-lower 2.72 --phase-upper 2.775 --phase-span 10000 --max-step 0.012`.
- Shooting the universal peel-off orbit from incoming cutoff $L=100,1000,
  10000$ gives $K_-=2.42248,2.43345,2.43456$, respectively, with a simple
  turn at $s\approx1.03207$ and $Z_t\approx0.95495$. This strongly isolates
  the magnitude but remains ordinary evidence. The sign $K_->0$ is now
  independently proved by the pinned full-box certificate. Use
  `python -m scripts.probe_triple_endpoint --cutoffs 100 1000 10000
  --shoot-center -4 -1 --max-step 0.5`.
- The exact final-infall $r$-Fuchsian projector, evaluated at finite-gap
  sections $r=0.2,0.1,0.05$, gives $0.31754,0.31427,0.31384$. This localizes
  the remaining global sign near $A_-\approx0.314>0$ but is ordinary evidence
  because the incoming cutoff and collision gap are not enclosed. Reproduce
  with `python -m scripts.probe_triple_jost_projection --cutoff 40 --phase
  2.77 --sections 0.2 0.1 0.05 0.02`.
- A complementary backward shoot from the collision-stable Fuchsian family
  used `scripts/probe_triple_stable_match.py`. At outer cutoff $K=20$ and
  local cutoff $X=24$, the frozen-zero-energy match gave
  $a=-0.24695456$ and $\widehat A_-=0.31103$. The local-cutoff result was
  stable from $X=20$ to $24$; the outer-cutoff drift remains unvalidated.
  The same linear solve decomposed the slow coefficient as
  $0.35064\gamma+0.69626\mathscr W_\infty$, exposing a large prospective
  sign margin but not enclosing it. The scalar frozen-section residual has
  ordinary derivative $-20.26$ with respect to $a$ at the matched point.
  This is **ORDINARY NUMERICAL EVIDENCE** and serves only to localize the
  interval-Newton box described in `TRIPLE_ENDPOINT_MATCHING_CERTIFICATE.md`.

Evidence level: EXACT SYMBOLIC IDENTITY for the Wronskian, binary tidal
coefficient, and macroscopic Kepler-transfer formulas; PROVED ANALYTICALLY for the restricted late-turn limit
and both fixed-resonance and uniform first-turn finite-$B$ transfer; PROVED BY
COMPUTER-ASSISTED ARGUMENT for $\mathscr W_\infty>21/50$, eventual $C_n<0$,
the resulting first-turn exclusions, and the universal triple-endpoint sign
$K_->0$. Reproduce the ordinary probe with:

```bash
uv run python -m scripts.probe_restricted_turn_map \
  --scattering-cutoffs 10 20 40 80 160 --max-step 0.04
```

Reproduce the proof certificate with:

```bash
bash scripts/run_capd_restricted_transverse_scattering.sh \
  /path/to/CAPD /path/to/CAPD/build-native
bash scripts/run_capd_triple_endpoint_turn.sh \
  /path/to/CAPD /path/to/CAPD/build-native
```

Reproduce the ordinary second-encounter probe with:

```bash
uv run python -m scripts.probe_second_encounter \
  --cutoff 40 --phases 21 --phase-span 10000 --max-step 0.04
```

## 2026-08-22: restricted finite-turn resonances

- Proved that the first-turn time on the finite-turn side diverges at the
  transverse parabolic boundary. Since the binary mean anomaly advances at
  rate four, the turn-phase map crosses every sufficiently large apocenter
  index and produces infinitely many restricted brake states.
- The exact comparison
  \[
  {d\over dz}\left({z'^2\over2}-{2\over z}\right)
  ={2\over z^2}\left[1-\left(1+{r^2\over4z^2}\right)^{-3/2}\right]
  \]
  gives $T\sim(\pi/4)Z_{\rm t}^{3/2}$ and
  $Z_{{\rm t},n}\sim(2n)^{2/3}$.
- An ordinary finite-cutoff probe at offsets $0.02,0.05,0.1$ on the numerical
  finite-turn side found turn heights about $41.11,16.60,8.42$ and rapidly
  winding turn phases, consistent with the theorem. These decimal values are
  not used in its proof.
- At cutoff $40$, roots where the turn is exactly at apocenter indices
  $n=1,2,3,4,7,10,18,34$ gave first relative-tilt velocity coefficients
  respectively about
  $0.2221,-0.00959,-0.02893,-0.03168,-0.02829,-0.02432,-0.01791,-0.01234$.
  This is ordinary evidence that $C_n$ is nonzero at the sampled roots, but
  also that its sign is not universal across all resonances.

Evidence level: PROVED BY COMPUTER-ASSISTED ARGUMENT for unconditional
resonance existence, through the validated transversality input; PROVED
ANALYTICALLY for the turn-map implication and height asymptotic; ORDINARY
NUMERICAL EVIDENCE for the displayed probe. Reproduce the latter with:

```bash
uv run python -m scripts.probe_restricted_turn_map \
  --resonances 1:1.5:2.0 2:0.3:0.5 3:0.2:0.3 4:0.2:0.3 \
  7:0.12:0.15 10:0.09:0.12 18:0.07:0.09 34:0.04:0.05 \
  --phase-span 30000 --max-step 0.03
```

## 2026-08-22: incoming-tail theorem and Level-D endpoint result

- Proved uniform propagation from the early overlap
  $Y_e=B^{\alpha-1}\to\infty$ to a fixed large incoming restricted section.
  The key radius-dependent bounds are
  \[
  |\mathscr H_N-E_{\rm ref,B}|\le CY^{-3},\qquad
  |\mathscr L|\le CY^{-3/2},
  \]
  which close $-Y_\theta\asymp Y^{-1/2}$ uniformly.
- Replaced informal collision-sensitive oscillator actions by the exact LC
  normal invariants
  \[
  \mathcal J=(E+1,L,K),\qquad
  K=p_xp_y-(E/2)z_xz_y.
  \]
  Their transverse Jacobian has determinant $-1/2$ on the radial circle, and
  their forced derivatives are uniformly $O(BY^{-3})$ through collision.
- Kept the exact finite-$B$ intercept subtraction until fixed radius and proved
  \[
  \operatorname{dist}_{S^1}
  \bigl(\Lambda_B(Y)+F_B(Y),\chi_B\bigr)
  \le CY^{-1/2}+o(1).
  \]
  Taking $B\to0$ first and then $Y\to\infty$ retains the restricted
  quadrupole flight-time correction and identifies the correct asymptotic
  intercept.
- Proved weighted transverse uniqueness from the exact reflection-odd
  mean-value equation. In log radius its coefficient matrix is an
  $L^1$ perturbation with growing modes $Y$ and $Y^{1/2}$; inherited
  $O(Y^{-1})$ decay forces rectilinearity.
- Independent adversarial passes found and forced repair of the constant
  energy, partial LC block, unspecified-action, phase-gauge, and nonlinear
  transverse gaps. Three final passes endorsed the repaired theorem.
- Combining matching with the restricted hyperbolic-escape window and terminal
  certificate proves infinitely many open real skinny intervals nonperiodic.
  Rational density then yields infinitely many distinct primitive
  Pythagorean triples. This is an unconditional Level-D theorem; the full
  rational and strong real conjectures remain unresolved.

## 2026-08-22: pre-plunge matching and phase-gauge audits

- Used restricted transversality to prove adjacent open hyperbolic-escape and
  finite-turn phase windows.
- The first independent adversarial pass verified stable-curve separation and
  found that the center/collision clock $\Phi_{\rm ref}$ had been compared
  directly with a raw incoming-section phase. The exact monopole correction is
  \[
  \Phi_{\rm sec,ref}=n_{\rm bin}t_0(BY_0)
  =\Phi_{\rm ref}-{4\over3}\sqrt{M/N}Y_0^{3/2}+O(B).
  \]
  A symbolic regression test verifies the limiting correction and that the
  derivative still has leading coefficient $-3\pi/2$ after multiplication by
  $B^{5/2}$.
- A deeper tail audit found that even this raw monopole section phase is not
  the invariant target at fixed $Y_0$: the restricted quadrupole produces a
  finite tail correction. The final formulation uses the incoming asymptotic
  intercept $\chi$ and the full restricted state
  $\Gamma^-_{Y_0}(\chi)$.
- Proved direct pre-plunge estimates for every $0<\alpha<1/6$. Unless a prior
  classical inner collision occurs, the orbit crosses $\rho=B^\alpha$ after
  the full $O(B^{-3/2})$ cycle train with
  $\chi_\alpha=\Phi_{\rm ref}+o(1)$ and matched outer state.
- A second independent audit found and repaired two localized proof defects:
  mean anomaly is a smooth observable $\Lambda=\Theta+\sin\Theta$, not a
  coordinate at collision, and the velocity comparison requires a radius-
  weighted angular-momentum estimate.
- Made collision-free section reach and convergence in one common
  regularized chart explicit hypotheses. Proved that a compact strict-escape
  arc transfers to the terminal escape inequalities by the physical scalings
  $e=-C/B+o(B^{-1})$ and $\dot\rho=sB^{-1/2}+o(B^{-1/2})$.
- The then-conjectural incoming-tail hypothesis was subsequently proved in the
  section above, promoting these terminal windows to an unconditional
  Level-D result.

## 2026-08-22: validated restricted Jacobi sign

- Reparameterized the restricted base/Jacobi equations by eccentric anomaly,
  making the first binary collision the regular endpoint $\psi=\pi/2$.
- Pinned CAPD 6.1.0 at commit
  `731079217a9254ea2948d742df2b170895effe7f` and built its native directed-
  rounding interval backend.
- Covered $v\in[14/5,4]$ by 256 independently integrated overlapping slabs.
  Every final normalized derivative enclosure satisfied
  $q'(\pi/4)>1/125$.
- Combined this with $\sqrt8<v_*<4$ to prove
  $h'(\pi/4)>14/625$.
- The smallest interval lower endpoint was about $0.00813572$, on the slab
  adjacent to $v=4$; this decimal records the certificate margin and is not
  used in place of the rational $1/125$ comparison.
- Closed the analytic implication by compactifying $z=2/x^2$. The resulting
  analytic time-$\pi$ map satisfies McGehee's degree-four sector hypotheses;
  tangents to its fixed-phase stable graph contract, while the validated field
  would keep the compact tangent bounded away from zero under tangency.

Evidence level: **PROVED BY COMPUTER-ASSISTED ARGUMENT** for the finite sign
and the resulting restricted stable/unstable transversality theorem. Reproduce
the computer-assisted part with:

```bash
sh scripts/run_capd_restricted_transversality.sh \
  /path/to/CAPD /path/to/CAPD/build-native
```

## 2026-08-22: reference clock and finite separatrix splitting

- Derived the exact point-mass outer fall to every nonsingular radius and the
  binary reference phase
  \[
  \Phi_{\rm ref}=\pi B^{-3/2}-{\pi\over4}B^{-1/2}
  -{15\pi\over32}B^{1/2}+O(B^{3/2}).
  \]
- Proved $\Phi_{\rm ref}'\sim-(3\pi/2)B^{-5/2}$, so every open limiting phase
  arc pulls back to infinitely many reference intervals containing rational
  Euclid parameters. This conclusion is not yet valid for the true flow.
- Identified a concrete overlap $1\ll Y\ll B^{-2/5}$ and isolated the missing
  uniform Levi--Civita averaging theorem across $O(B^{-3/2})$ binary cycles.
- Expanded the exact finite-$B$ local field through order $B^2$. Symmetric
  backreaction begins at $B$, but direct longitudinal bending begins at
  $3B^2r^3/(16d^5)$.
- Derived the formal energy-splitting functional and its centered parity
  cancellations. Found that the naive time-shift Jacobi field makes the phase
  integral a pure boundary term, requiring a fixed parabolic phase gauge.
- On the gauge-free $z=0$ section, ordinary finite-cutoff slopes for
  $L=10,20,40$ were respectively $-0.9060265,-0.9062323,-0.9062301$ for the
  incoming-minus-outgoing parabolic curves. This supports transverse
  splitting but is not interval validated.
- Proved the explicit bracket $\sqrt8<v_*<4$ and a Wronskian lemma keeping
  the even phase Jacobi field positive through the first binary collision.
  The only finite sign left for restricted transversality is
  $h'(\pi/4)>0$; ordinary cutoff values converge near $0.0378487$.

Evidence levels: EXACT SYMBOLIC IDENTITY and PROVED ANALYTICALLY for the
reference formulas and phase sweep; EXACT SYMBOLIC IDENTITY for the local
field and gauge cancellation; ORDINARY NUMERICAL EVIDENCE for transversality
at this stage; true-orbit matching and transversality were subsequently proved
above, while the finite-$B$ splitting expansion remains CONJECTURAL.
Reproduction commands:

```bash
.venv/bin/python -m scripts.derive_skinny_matching
.venv/bin/python -m scripts.derive_finite_plunge
.venv/bin/python -m scripts.derive_restricted_scattering
.venv/bin/python -m scripts.probe_restricted_transversality --cutoffs 10 20 40
```

## 2026-08-22: regularized first skinny encounter

- Derived the exact tight-pair/outer Jacobi system and its encounter scaling.
- Regularized the limiting heavy-pair collision with $x=z^2$ and
  $d\tau=|z|^2ds$.
- Computed the first transverse variation
  $v_{ss}+v/2=-(3/8)\cos^5(s/\sqrt2)$ and
  $v(\pi/\sqrt2)=-15\pi/128$.
- Proved a positive first-passage miss for every sufficiently small $B>0$:
  \[
  r_{13,\min}={225\pi^2\over16384}B^{11}(1+O(B)),
  \qquad
  h_{13}=-{15\pi\over64}B^{11/2}+O(B^{13/2}).
  \]
- Independently integrated the exact regularized equations at
  $B=0.2,0.1,0.05$; the rescaled transverse displacement, miss, and angular
  momentum converge to the exact coefficients.
- Proved a terminal binary--escaper inequality certificate and proved that its
  radial-energy condition fails by $-2+O(B)$ after the first passage.
- An independent adversarial derivation found no factor, sign, frame, or
  reduced-mass error in either theorem.

Evidence level: PROVED ANALYTICALLY for both conditional theorems; numerical
integration is a regression check only. Reproduction commands:

    .venv/bin/python -m scripts.derive_skinny_regularization
    .venv/bin/python -m scripts.probe_skinny_regularization --epsilon 0.05

## 2026-08-22: late-plunge restricted limit

- Derived the exact $X=B R$, $Y=B Z$, $t-t_*=B^{3/2}\theta$ local scaling.
  The vector field tends to a prescribed rectilinear equal-mass binary plus a
  massless outer particle.
- Verified symbolically the restricted energy exchange law
  \[
  \dot{\mathcal E}
  ={r\dot r\over2(z^2+r^2/4)^{3/2}}.
  \]
- Proved that small apocenter launch speeds turn by reducing the variational
  equation to
  \[
  w_{\psi\psi}+(1+14\sec^2\psi)w=0
  \]
  and applying Sturm comparison before the first binary collision.
- Proved quantitative large-speed escape and used the supremum of the open
  turning set to obtain an exact parabolic-to-parabolic separatrix.
- An independent adversarial pass checked the scaling, period, energy
  identity, Sturm coefficient, and topology of the separatrix proof.

Evidence level: PROVED ANALYTICALLY for the local limiting vector field and
the auxiliary separatrix theorem. Matching the exact finite-$B$ trajectory to
incoming limiting data was subsequently proved in the incoming-tail theorem.
Reproduce the identities with:

    .venv/bin/python -m scripts.derive_restricted_scattering

## 2026-08-22: exact foundation

- Initialized the repository and pinned Python 3.13 plus SymPy, NumPy, SciPy,
  mpmath, pytest, and Ruff.
- Derived accelerations directly from Newton's equations.
- Symbolically verified normalized $I_0$, $U_0$, and the corrected $D''(0)$.
- Encoded the Euclid map and leg-swap involution with exact rational arithmetic.
- Tested a Hopf residual example that defeats mutual-distance derivatives at
  syzygy.
- Encoded and tested the universal zero-angular-momentum reduced kinetic and
  potential expressions.

Evidence level: EXACT SYMBOLIC IDENTITY for algebraic checks; no global
dynamical conclusion.

## 2026-08-22: defect-barrier falsification

Three DOP853 runs at $u=1/3$, ending at $t=4$, used respectively

- $(rtol,atol,max\_step)=(10^{-11},10^{-13},0.005)$;
- $(10^{-13},10^{-15},0.001)$;
- $(2.22\times10^{-14},2\times10^{-16},0.0005)$.

All gave $D(0.376)=-0.004664128339$ to the shown digits.  The prior minimum
separation was $0.002791245371$; the first two prior relative energy drifts
were $5.3\times10^{-10}$ and $2.9\times10^{-12}$.  Thus the proposed global
$D>0$ cone fails after a close but numerically positive encounter.

Evidence level: ORDINARY NUMERICAL EVIDENCE.  Reproduce the middle run with:

```bash
.venv/bin/python -m scripts.probe_dynamics --u 1/3 --t-end 4 \
  --samples 20001 --rtol 1e-13 --atol 1e-15 --max-step 0.001
```

## 2026-08-22: exact fourth jet and brake-map factorization

- Derived $D^{(4)}(0)$ directly by differentiating Newton's pair force twice.
- Verified its degree-20 numerator symbolically.
- Produced an exact Sturm certificate: sequence length 21, with 10 variations
  at both 0 and $83/200$, proving uniform negativity on the fundamental
  interval.
- Factored the local brake condition into two Jacobi radial rates and one
  angular slip away from Jacobi-vector degeneracy.
- Independently refined a representative double-radial event to
  $(u,t)\approx(0.2928773969,1.3435972246)$ and found slip
  $-0.0562132956$, not a brake.
- Recorded exact initial skinny-pair torque and formal first-passage scaling.

Evidence levels: exact jet identity; PROVED BY COMPUTER-ASSISTED ARGUMENT for
the Sturm sign; ORDINARY NUMERICAL EVIDENCE for the event; CONJECTURAL for the
skinny asymptotics beyond initial torque.

## 2026-08-22: Li--Liao $F_{30}$ periodic-family continuation

Using the three Hopf brake components as a shooting residual, independently
refined the published $F_{30}$ point at $u=1/2$, then continued its
$(x,y,T/2)$ root over nearby $u$.  The two Pythagorean matching offsets crossed
zero at separated parameter values (roughly 0.494 and 0.50225).  The closest
sampled combined gap was $0.0036908$ near $u=0.5018$.  No local intersection
was found.

Evidence level: ORDINARY NUMERICAL EVIDENCE.  Reproduce the central point:

```bash
.venv/bin/python -m scripts.continue_f30
```

On 2026-08-24 the continuation was extended to both independent mass ratios.
A five-equation solve imposed the three Hopf brake residuals and the two
mass--opposite-side equalities. It located a nearby general Burrau periodic
candidate at $(m_1,m_2)\approx(0.594811646571,0.801774973308)$, but its
Pythagorean defect is $-0.003355997281$. A tighter replay gave relative energy
drift $1.91\times10^{-10}$ and a finite-difference shooting Jacobian with
smallest singular value $0.199$. An independent implicit Radau solve agreed
in the masses to $3.2\times10^{-11}$ and in the Pythagorean defect to
$4.9\times10^{-12}$. Status remains **ORDINARY NUMERICAL
EVIDENCE**; no validated periodic existence or local exclusion is claimed.
Reproduce with

```bash
uv run python -m scripts.continue_f30 --solve-mass-side \
  --diagnose-jacobian --rtol 2e-13 --atol 2e-15 --max-step 0.001
```

## 2026-08-23: certified global triple-endpoint coefficient

- Attached the exact collision-stable base family and canonical fast mode at
  $r=2^{-32}$ by analytic weighted fixed-point estimates, uniformly for
  $-0.24696\le a\le-0.24694$.
- Propagated the complete box with pinned CAPD 6.1.0. The left endpoint has
  $H_K>0$, the right endpoint has $H_K+1/(4Z^3)<0$, and every accepted
  candidate step has positive reversed velocity. Connectedness therefore
  gives at least one parabolic connection.
- Combined an analytic returned-Jost tail enclosure with the compact
  propagation to prove the uniform rational bound $W(J,P_+)<-1/2$ and hence
  $A_-=W(J,P_+)/(-\sqrt7)>0$ for every possible parabolic member.
- Two independent adversarial passes rederived the collision tails and global
  sign logic; one independently replayed the pinned wrapper. Exact hexadecimal
  output is stored in `data/triple_endpoint_global_capd_certificate.txt`.
- Strengthened the replay with the whole-path cone
  $Z>r/(2\sqrt2)$. Pairwise scalar comparison then proves the parabolic
  connection is unique in the amplitude bracket and orders its hyperbolic
  escape and finite-turn sides. This does not by itself prove differential
  transversality or finite-phase localization.

Evidence levels: **PROVED ANALYTICALLY** for the collision attachment and
tail estimates; **PROVED BY COMPUTER-ASSISTED ARGUMENT** for the compact
escape/return bracket and $A_->0$. Subsequent differentiated-tail,
transversality, and fibered-exchange arguments promote the one-sided local
finite-$\varepsilon$ branch to **PROVED BY COMPUTER-ASSISTED ARGUMENT**;
global captured-component classification remains **CONJECTURAL**.

## 2026-08-23: finite-mass triple-endpoint wedge

- Derived the exact joint scales
  $h\asymp\varepsilon^{(1+\sqrt{19})/6}$ and
  $\eta=B\varepsilon^{-(1+\sqrt7)/6}$; the first exponent is larger, so
  shape-branch preservation forces the inner transverse amplitude to vanish.
- Constructed the full homogeneous McGehee system and corrected the reduced
  spectrum to $(-n,\mu,1-\beta_-,1-\beta_+)$ after SO(2) reduction. The
  Sundman-time factor and the fixed-inertial zero-angular-momentum
  reconstruction are retained explicitly.
- Proved a simultaneous base/fiber exchange estimate through the diverging
  dwell. A first draft was rejected by two independent audits because it
  imported the restricted exchange without controlling finite-$B$ clock and
  stable-graph drift.
- Wrote the reflection/Hadamard-divided heavy-binary LC equation. Its direct
  source is $B/\eta=\varepsilon^{(1+\sqrt7)/6}\to0$, repairing the invalid
  inference from ordinary LC continuity to a divided limit.
- Proved that if
  $\omega_0(B)+B=o(\varepsilon^{(1+\sqrt{19})/6})$, then collision terminates
  the classical orbit or the transverse velocity is nonzero near the continued
  turn. The sign uses the pinned certificates $A_->0$ and $K_->0$.
- Reduced the unresolved local finite-mass set to
  $0<\varepsilon<\Delta(B)$, with
  $\Delta(B)=(\omega_0(B)+B)^{3/(1+\sqrt{19})}\to0$.

Evidence level: **PROVED ANALYTICALLY** for the coupled exchange and **PROVED
BY COMPUTER-ASSISTED ARGUMENT** for the final wedge exclusion. Both repaired
versions received independent adversarial endorsement. Reproduce exact
exponents with:

```bash
.venv/bin/python -m scripts.derive_restricted_scattering
```

The same run also verifies the exact tight-pair Hill threshold
\[
 R_{\rm H}(B)={1-B^2\over1+B^2-B^4}.
\]
At a brake $U=U_0$, whereas the heavy-pair term alone is $A/(B|R|)$;
positivity of the remaining pair terms forces $|R|>R_{\rm H}$. Two
independent label/normalization audits endorsed this analytic barrier. It
excludes brakes in every absolute near-triple tube but not after binary
re-expansion.

## 2026-08-23: joint two-mode triple-endpoint blow-up

- Replaced the unknown restricted phase gap by intrinsic nonlinear unstable
  amplitudes $H_B$ (longitudinal) and $T_B$ (reflection odd) relative to the
  exact finite-$B$ collision-stable manifold.
- Proved
  \[
   {T_B\over B}\to-{\widehat A_-\over2}\ne0.
  \]
  The essential subtraction uses the auxiliary equal-heavy family
  $(1,B,1)$: it retains exact exchange/reflection symmetry, while
  $A(B)-1=O(B^2)$. Hence the odd stable-foliation and projector correction is
  $O(B^2)$, not $O(B)$.
- Derived the two unstable exponents
  $\mu=(1+\sqrt{19})/4$, $\tau=(1+\sqrt7)/4$ and the strict inequality
  $1<\mu/\tau<2$. The latter makes the projective coordinate
  \[
   \kappa_B={H_B\over|T_B|^{\mu/\tau}}
  \]
  invariant up to $o(1)$ under quadratic nonlinear chart changes.
- Proved that every joint-layer sequence reduces to the one-parameter planar
  restricted family $\mathscr U_\kappa$, or to its two rectilinear endpoint
  exits. Exact finite-mass collisions still terminate the classical orbit;
  convergence through a separated limiting heavy-binary collision is only in
  LC variables.
- Three adversarial passes identified the stable-graph subtraction,
  nonlinear normalization, exponent drift, and collision semantics; all were
  repaired before analytic promotion.

Evidence level: **PROVED ANALYTICALLY** for the structural one-parameter
reduction. Global classification of $\mathscr U_\kappa$ and the sign of its
outgoing scattering scalar remain **CONJECTURAL**.

## 2026-08-23: exact planar shape and torque identities

- Put the radial zero-energy binary and light state in logarithmic shape
  variables. The universal planar family becomes
  $w_{\zeta\zeta}+w_\zeta/3=\nabla W(w)$.
- Proved the strict identity
  $\mathcal E_\zeta=-|w_\zeta|^2/3$, excluding nonconstant periodic shape
  orbits and equilateral-to-equilateral connections.
- Proved the sharp global minimum $W\ge11/36$. A nonhomothetic
  equilateral-stable orbit has no finite zero of $w_\zeta$, and a LaSalle
  alpha-limit argument excludes compact collision-free backward capture.
- Factored the angular equation exactly as
  $\Lambda_\zeta+\Lambda/3=-xyK(x,y)$ with $K>0$.
- Proved
  \[
  W_{xx}\ge {1\over9}\left({7\over4}-{8\over3\sqrt3}\right)>0
  \quad\hbox{on }|y|\ge\sqrt3/2,
  \]
  giving a rigorous signed-tail lemma.
- Falsified the tempting global outer-strip invariant exactly: the
  $\kappa=0$ stable orbit has inward quadratic coefficient
  $(2\sqrt{21}-5\sqrt3)/4>0$.
- Two independent audits rederived the shape equation, Lyapunov sign, torque
  factor, convexity bound, and first-zero argument. They required the explicit
  physical-time sign reversal on the incoming binary half, now recorded.

Evidence level: **PROVED ANALYTICALLY** for every identity and conditional
signed-tail theorem; global inner-strip transition classification remains
**CONJECTURAL**.

### Targeted inner-strip probe

The deterministic ordinary probe

    .venv/bin/python -m scripts.probe_planar_joint_shape

initializes the lower-equilateral stable asymptotics at $\zeta=22$, includes
the complete exact quartic stable-manifold jet, and integrates backward to
$|w|=20$. With transverse sign $T=-1$ it found:

| $\kappa$ | minimum light-heavy shape distance | outgoing $\Lambda$ | zeros of $\Lambda$ |
|---:|---:|---:|---:|
| $1.250$ | $3.51\times10^{-3}$ | $+1.71$ | 0 |
| $1.260$ | $6.90\times10^{-4}$ | $+2.07$ | 0 |
| $1.265$ | $9.43\times10^{-5}$ | $-3.15$ | 1 |
| $1.300$ | $1.04\times10^{-2}$ | $-2.62$ | 1 |

The abrupt sign switch occurs in a collision-scale region and suggests that
an isolated light-heavy collision helps organize the local transition. It also
shows
that instantaneous $\Lambda$ can cross zero after an extremely close but
numerically noncolliding passage. This is **ORDINARY NUMERICAL EVIDENCE**,
not a collision proof, validated root, or counterexample. Its analytic use is
only to focus the next theorem on collision-component transition rules rather
than a global pointwise sign.

The exact forced Levi--Civita replacement is now derived in
PLANAR_LIGHT_COLLISION_LC.md. For relative position
$q=Z-\epsilon R/2=u^2$ and $dt=|u|^2d\sigma$, it preserves
\[
 2|v|^2-1-h|u|^2=0
\]
and converts a collision candidate into the square residual
$u(\kappa,\sigma)=0$. Running the regularized ordinary shoot

    .venv/bin/python -m scripts.probe_planar_light_collision_lc

from the same truncated stable tail gives

\[
 \kappa_{\rm num}=1.26793517550,\qquad
 \sigma_{\rm num}=-1.07124850572,
\]

with $|u|=4.6\times10^{-12}$, finite-difference determinant about
$-3.45305779$, $|v|=0.707106781186543$, constraint residual about
$1.2\times10^{-14}$,
radial clock $t=1.07823523$, and other-primary distance $2.1872$. These are
**ORDINARY NUMERICAL EVIDENCE** from a finite tail truncation, not a validated
zero. The displacement from the unregularized scan is itself a warning not to
infer collision location from a close-passage minimum. All decimals are only
a seed box for a future interval-Newton proof; no ordinary close-passage
output is promoted.

The default shoot now starts at $\zeta=10$. Varying the finite tail section
with the quartic jet gives collision seeds

| $\zeta_0$ | $\kappa_{\rm num}$ |
|---:|---:|
| 6 | 1.26793486796 |
| 8 | 1.26793517243 |
| 10 | 1.26793517550 |
| 12 | 1.26793517552 |

This convergence is ordinary evidence consistent with an $O_5$ tail defect;
it is not a remainder proof.

## 2026-08-23: analytic tail enclosure and validated finite LC stage

- Completed the weighted analytic stable-parameterization argument around the
  lower equilateral rest point. On $|p|\le1/200$, $|\nu|\le1/2500$, the exact
  quartic polynomial has a unique normalized correction $E$ satisfying
  $\|E\|<1/125000000$. On half radii,
  $\|E\|<1/4000000000$ and
  $\|\mathcal DE\|<1/800000000$, with explicit $\kappa$-tangent bounds.
  Exact symbolic tests verify the algebraic coefficient bounds, homological
  gap, residual majorant, contraction constant, and exponential tail
  inclusion. Status: **PROVED ANALYTICALLY**.
- Propagated the full rigorous tail box for
  $1.26793\le\kappa\le1.26794$ with pinned CAPD 6.1.0 native intervals from
  $\zeta=10$ to $\zeta=0.3$, then through the analytic LC coordinate change
  and a reversed LC leg of exact duration $1071249/1000000$. Every accepted
  LC step satisfies $t>1$, $R>2$, and other-primary distance $>1$.
- The terminal LC enclosure is

  \[
  -0.017807<\operatorname{Re}u<0.016661,\qquad
  -0.003953<\operatorname{Im}u<0.004019.
  \]

  Status: **VALIDATED NUMERICAL RESULT** for finite propagation and chart
  safety, but not a collision root. Independent interval conversion loses
  the parameter correlation. The next implementation must preserve the
  affine $\kappa$ direction, propagate its tangent, and apply interval Newton.

## 2026-08-23: validated transverse planar collision root

- Replaced the lossy shape-to-LC interval projection by one persistent
  13-dimensional CAPD `C1Rect2Set`. It propagates the shape variables, writes
  the exact nonlinear LC entry through a unit-time construction field, and
  then evolves the LC variables without discarding affine directions.
- Moved the analytic tail start to $\zeta=15$. Since the stable correction and
  all required tangents begin in total degree five, the half-polydisc bounds
  gain the rigorous factor
  $\lambda^5$, where
  $\lambda=\max(400e^{-15a_T},6500e^{-15a_L})<0.04403$.
- Pinned CAPD interval Newton proves exactly one root in

  \[
  1.2679350755\le\kappa\le1.2679352755,
  \qquad
  1.0712484057\le-\sigma\le1.0712486057.
  \]

  The Newton image sharpens this to

  \[
  1.2679351752<\kappa_c<1.2679351759,
  \qquad
  -1.0712485063<\sigma_c<-1.0712485051.
  \]

- The increasing-$\sigma$ determinant satisfies
  $-3.52212<\det(\partial_\kappa u,v)<-3.38401$. Every accepted shape and LC
  step remains inside an explicitly checked analytic chart, and the square-root
  lift is fixed by $y>0$, $u_r,u_i>0$ at entry.
- Two independent adversarial audits rechecked the tail scaling, LC lift and
  orientation, current-time semantics across vector-field changes, $C^1$
  chain rule, interval Newton, and chart coverage. Both endorsed the result.
- Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** for a unique transverse
  collision in the massless planar limiting family. This is not a
  Pythagorean counterexample or a second brake.

## 2026-08-23: finite-mass persistence of the collision boundary

- Derived and symbolically regression-tested the exact selected-pair equation
  for positive light mass:
  \[
   q=Z-{A\over1+A}R,\qquad
   q''=-(1+B)\Phi(q)+A\{\Phi(R)-\Phi(q+R)\}.
  \]
- The forced LC constraint becomes
  \(2|v|^2-(1+B)-h|u|^2=0\), so
  \(|v|^2=(1+B)/2\) at collision.  An adversarial pass caught that retaining
  $R$ would leave a singular $B\Phi(q)$ term.  The repaired coordinate
  $Q=R+Bq/(1+B)$ cancels it exactly, and $Q=R$ at the validated limit.
- A $C^1$ coordinate chart on one fixed constrained incoming section and the
  collision-adapted LC flow prove a unique nearby collision root for every
  sufficiently small compatible section perturbation.  The finite-mass
  miss-distance coefficient is
  \(2D_B^2/(1+B)\).
- Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** for persistence of the
  local fixed-section collision boundary.  The exact Pythagorean state
  supplies only one selected section point; whether it meets the boundary is
  still conjectural.

## 2026-08-23: differentiated joint inclination and normalized collision graph

- Replaced the insufficient state-only joint inclination estimate by a
  parameter-tangent theorem for the normalized family
  \(H=\kappa|T|^{\mu/\tau}\).  A fixed weight
  \(\mu/2<\omega<\tau\) contains both finite-mass unstable modes and gives
  the uniform quadratic Green gap \(2\omega-\mu_B>0\).
- An adversarial audit caught that bounded stable entrance data cannot be put
  in the infinite-tail weighted ball.  The repaired proof constructs only
  the nonlinear unstable shadow there and compares the actual state and its
  \(\kappa\)-tangent at a fixed tail section using uniform \(C^1\) stable
  holonomy.  A second audit caught and repaired an unjustified \(C^2\)
  holonomy claim; the miss-distance remainder is therefore
  \(o((\kappa-\kappa_c)^2)\), which is the sharp conclusion from \(C^1\).
- Scaled \(Q\)-adapted LC variables carry both state and tangent through the
  selected limiting collision.  The certified root consequently defines a
  unique normalized finite-mass graph
  \(\kappa_c(B,T,S,\Xi)\) throughout the stated admissible cusp.
- Both independent final adversarial rereads endorse the repaired result.
  The differentiated inclination theorem is **PROVED ANALYTICALLY**; the
  collision graph inherits **PROVED BY COMPUTER-ASSISTED ARGUMENT** from the
  validated base root.  A componentwise classification of the tied scalar gap
  \(\Delta_{\rm intr}(B)=\kappa_B-
  \kappa_c(B,T_B,S_B,\Xi_B)\) remains **CONJECTURAL**.

## 2026-08-23: exact real collision sampling

- Chose fixed asymptotic-intercept arcs on opposite sides of the certified
  transverse restricted endpoint.  The exact monotone clock gives one
  disjoint real \(B\)-bracket per sufficiently late winding, of width
  \(O(B^{5/2})=o(B)\).  Uniform incoming-tail convergence transfers fixed
  opposite signs of the longitudinal unstable amplitude \(H\) to the bracket
  endpoints unless a prior classical collision has already occurred.
- On a no-prior-collision bracket, continuity supplies a shrinking positive
  segment from a last \(H=0\) point to \(H=B^{p/2}\), with
  \(p=\mu/\tau\in(1,2)\).  Every sequence in this segment approaches the
  unique certified endpoint, so sequential compactness uniformizes
  \(T/B\to\Theta_*\ne0\), \(\widehat\Xi\to0\), and the collision-graph cusp.
- The exact scalar
  \[
   G(B)=H_B-|T_B|^p\kappa_c(B,T_B,S_B,\Xi_B)
  \]
  is negative at \(H=0\) and positive at \(H=B^{p/2}\), because the graph
  term is only \(O(B^p)\).  Its IVT zero is an exact selected light--heavy
  collision of the tied positive-mass trajectory.  If continuity failed
  because an earlier collision occurred, that parameter already supplies the
  required collision.
- Both independent hostile rereads endorsed the proof.  Status:
  **PROVED BY COMPUTER-ASSISTED ARGUMENT** for infinitely many distinct real
  tied collision parameters accumulating at the skinny endpoint.  None is
  proved to have rational Euclid parameter.

## 2026-08-23: validated collision--ejection and finite-mass escape cusp

- Ordinary DOP853 continuation first indicated that the certified restricted
  collision root ejects, crosses the prescribed heavy-binary collision in a
  signed cube-root clock, and reaches large radius with outward physical
  speed about \(2.97\).  This diagnostic was not used as proof.
- The CAPD verifier was extended from the full explicit interval
  \(1.2679251755\le\kappa\le1.2679451755\), which contains the unique
  interval-Newton root, through the selected-pair LC collision--ejection
  branch to \(S=61/25\), then through a heavy-binary bridge with
  \(\lambda=\sqrt[3]t\).  Whole-step intervals keep both light--primary
  squared distances above \(0.89\).  The terminal restricted escape margin
  is \(>0.54\).
- An initial appeal to finite-time openness was rejected by adversarial
  audit: for \(B>0\), the light body perturbs the heavy pair for infinite
  future time.  The repair is a full Jacobi hierarchical lemma.  It bounds
  the heavy-pair radius by a linear envelope, forces the light body to outrun
  it, and controls all future tidal energy by a convergent integral times
  \(B\).
- The pinned verifier certifies the conservative limiting full-pair margin
  \[
   \dot\rho_0-{2\over(3/2)(\rho_0-r_0)}
   -\sqrt{{4\over r_0}+{2\over100}}-{3\over2}>0.65.
  \]
  Newtonian-scaled LC convergence and the \(O(B)\) tidal budget transfer the
  cone to sufficiently small positive mass.  Across the ten tiles the
  conservative finite-mass margin is \(>0.65\).
- Three independent audits endorsed the exact Jacobi constants, both LC
  time orientations, the simultaneous bootstrap, scaling, and the
  finite-mass conclusion.  Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT**
  that every sufficiently small compatible member of this local cusp either
  collides classically or escapes; every collision-free member is
  nonperiodic.
- On a late no-prior-collision phase bracket, the exact tied coordinate
  \(H/|T|^p\) runs continuously from \(0\) to
  \(\asymp B^{-p/2}\).  Its preimage of the explicit cusp interior is
  therefore nonempty and open and contains a tied nonperiodicity interval.
  Thus each late bracket contains either an earlier collision or such an open
  interval.
- An ordinary scan of the adjacent planar component exposed a different
  near-collision around \(\kappa=1.264012\).  Switching from the positive-
  primary LC chart to the negative-primary LC chart produced a square root
  with ordinary determinant about \(-93.36\).
- Pinned CAPD interval Newton then certified exactly one opposite-primary
  collision in
  \(1.2640119181\le\kappa\le1.2640119321\), with a strictly nonzero
  determinant.  Whole-step boxes exclude both earlier selected-primary
  collision and collision with the nonregularized primary.  This is a second
  limiting collision graph, not an outgoing classification of its sides.
- Three adversarial audits caught that the first draft had not excluded an
  earlier zero in the second regularized chart.  The repaired verifier proves
  \(\Re v_->1/2\) on every whole step, hence
  \((\Re u_-)_{S}<-1/2\); all three audits then endorsed the classical-safety
  conclusion.
- A nested interval-Newton replay tightened the root input box by more than an
  order of magnitude and sharpened the determinant to
  \([98.8377,99.2930]\).  The ordinary regularized outgoing continuation
  escapes but passes within about \(4.3\times10^{-4}\) of the other primary;
  this is evidence for a third LC chart, not a validated escape theorem.
- The third positive-primary LC chart has now been implemented with the
  cancellation-free lift $u_i=-\sqrt{(|q|-q_x)/2}$,
  $u_r=q_y/(2u_i)$.  Pinned CAPD propagates the current tight root box
  through both post-root LC blocks and the heavy-binary bridge.  The worst
  squared unregularized-primary separation is $>0.06558$; terminal
  restricted and hierarchical margins are $>3.1388$ and $>3.2680$.
  Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT**, with three independent
  adversarial endorsements.
- A 195-tile replay enlarged this second collision-or-escape component to the
  contiguous interval
  $1.2640099161\le\kappa\le1.2640126461$.  The aggregate worst squared
  primary separation is $>0.004936$, while the two escape margins retain the
  bounds $>2.7591$ and $>2.8882$.  A stable algebraically identical
  square-root lift prevents interval cancellation off the root tile.
- Targeted boxes below this component expose the next chart obstruction.  The
  radius-$7\times10^{-9}$ tile at offset $-2500\times10^{-9}$ no longer
  clears the deliberately imposed bridge bound $|Z-Q_i|^2>10^{-3}$ (its
  direct enclosure has lower endpoint about $9.32\times10^{-4}$), while
  offsets $-2800\times10^{-9}$ and $-5000\times10^{-9}$ no longer certify
  the square-root switch sheet.  These failed verifier assertions are chart
  obstructions consistent with another close encounter, not evidence of a
  collision.
- A fourth, negative-primary LC chart at the fixed heavy-bridge duration
  $97/5000$ resolves that obstruction.  Interval Newton then reveals two
  distinct roots in the very narrow transition layer.  The earlier
  positive-primary root has
  $1.2640090993171269\le\kappa_3\le1.2640090999643190$ and determinant
  $>5224.58$.  The later negative-primary root has
  $1.2640090985775962\le\kappa_4\le1.2640090992806481$ and determinant
  $>417669$.  A broader uniqueness box brackets every possible earlier
  positive collision and proves $\kappa_3-\kappa_4>1.2058\times10^{-11}$,
  so the fourth root is classically reached.  Status: **PROVED BY
  COMPUTER-ASSISTED ARGUMENT**.  Three independent adversarial reviews
  endorsed the coordinate maps, time orientations, $C^1$ chain, monotone
  first-zero arguments, and strict parameter-gap exclusion.  They also
  confirmed that no terminal escape claim is made for either new outgoing
  component.
- Starting at the full fourth-root parameter box and the fixed post-root clock
  $S_4=0.37284$, pinned CAPD propagates a further $0.42716$ in the negative-
  primary LC chart.  The positive-primary squared distance stays above
  $0.333865$; at exit $|u_-|^2>0.213057$, $q_{+,x}<-0.577809$, and
  $|q_+|^2>0.333864$.  The exact negative-to-positive switch therefore enters
  a uniform fifth LC chart with $u_{+,i}<-0.760137$ and $t>0.240640$.
  Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** as a collision-or-fifth-
  entry statement, not an escape theorem.
- Ordinary continuation of a representative fourth-root ejection finds a
  positive-primary passage near $t=0.18817$ with apparent miss distance
  $2.5\times10^{-7}$, then a negative-primary passage near $t=0.13873$ with
  apparent miss distance $0.00422$.  It later reaches restricted and
  hierarchical escape margins near $9.99$ and $10.13$.  These are
  **ORDINARY NUMERICAL EVIDENCE**.  A direct interval box restart at the fifth
  entry spans the collision sheet and loses impact-parameter correlation.
- The stable-tail graph was sharpened by solving all six total-degree-five
  homological equations exactly.  The coefficients have signs
  $(+,-,+,-,+,-)$, and the remaining weighted coefficient remainder starts in
  degree six.  At $\zeta=15$ this gains an additional factor below $0.04403$
  in every remainder and tangent box.  Status: **EXACT SYMBOLIC IDENTITY**
  for the coefficients and **PROVED ANALYTICALLY** for the degree-six
  enclosure.
- The lost impact-parameter correlation was repaired without parameter
  tiling.  A persistent CAPD $C^0$ doubleton is transported through
  dimension-preserving exact maps; dimension-changing maps are represented
  as auxiliary graph ODEs, preserving every earlier generator through
  dimensions $13\to19\to24\to30$.  A rigorous Poincare map carries the full
  fourth-root box to the outgoing fifth-LC section $c_i=1/20$.  There
  $|c|^2>0.0021667155$, the other-primary squared distance is
  $>0.4599473198$, and $-d_i>0.7401537751$.  Status: **PROVED BY
  COMPUTER-ASSISTED ARGUMENT** as a collision-or-fifth-outgoing-section
  theorem, not an escape theorem.
- Direct continuation beyond that section fails in every tested
  single-centre atlas because the fifth and sixth close passages overlap.  An
  immediate negative-primary LC switch leaves the positive-primary
  denominator enclosing zero, including on a one-picounit parameter tile and
  at smaller integration steps.  Moving the outgoing section farther from
  the fifth primary does not separate the overlap.  Status: **FAILED** as a
  chart strategy; the proposed repair is a simultaneous two-centre
  regularization.
- Derived that repair exactly.  The elliptic shape map
  $z=(c^2-s^2)/2$, $s^2+c^2=1$, has metric
  $g=|s|^2|c|^2=r_+r_-$.  With $p=g\xi_\zeta$ and
  $d\zeta/d\sigma=\eta g$, both Newtonian singular forces cancel into the
  polynomial term $(s\bar c-c\bar s)/9$.  The redundant half-angle field
  preserves both shape constraints and the regularized energy constraint;
  either collision has $|p|^2=2/9$.  Initialization from the existing fifth
  LC state is algebraic: $s=iu/\sqrt R$, $c=\sqrt{1-s^2}$.  Status:
  **EXACT SYMBOLIC IDENTITY**.
- Implemented the algebraic fifth-LC initialization, analytic inverse to the
  nonredundant \(\xi=\alpha+i\beta\) chart, and reversed two-centre field in
  the CAPD verifier.  A one-picounit \(\kappa\) tile propagates rigorously for
  \(0.7\) regularized-time units.  Longer propagation wraps in \(p,E\);
  redundant \((s,c)\) evolution drifts off its constraint, and restarting
  from a componentwise Poincare image fails sooner.  Status: **VALIDATED
  NUMERICAL RESULT** for this finite probe only; no terminal classification
  is claimed.
- Solved all 24 stable-graph homological equations in degrees six through
  eight exactly. Their substitution residuals simplify to zero, and the
  previously proved coefficient-norm remainder now starts in degree nine.
  Status: **EXACT SYMBOLIC IDENTITY** for the coefficients and **PROVED
  ANALYTICALLY** for the sharpened remainder.
- Compiled the full verifier against CAPD's MPFR types at 200-bit default
  precision. Merely changing arithmetic while retaining the native
  \(10^{-15}\) local tolerance did not materially improve the fourth-root
  phase enclosure. Tightening to \(10^{-20}\) contracted the first Newton
  image, but its direct state evaluation still enclosed \(v_i=0\). A
  \(10^{-22}\) replay gave nearly the same phase width. Status: these two
  subroutes are **DISPROVED** as sufficient sign arguments; they diagnosed
  root-box dependency as the remaining width.
- A second interval-Newton step centered inside the first image repairs that
  dependency. The refined box has \(\kappa\)-width below
  \(2.9\times10^{-15}\) and regularized-time width below
  \(6.26\times10^{-9}\). Re-evaluation proves
  \(-3.83235\times10^{-7}\le v_i\le-3.68194\times10^{-7}<0\).
  Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT**.
- Fed an outward-widened rational hull of that MP certificate directly into
  the simultaneous two-centre chart at the fourth collision. At the next
  positive focus, native CAPD proves
  \(-1.31081\times10^{-5}\le\beta\le-1.25935\times10^{-5}\) and
  \(\sinh^2(\beta/2)>3.96496\times10^{-11}\). Thus the regularized
  collision--ejection branch has a smooth fifth near-passage, not an
  additional collision. Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** for
  the planar massless boundary; its classical orbit already terminated at
  the fourth collision, and no finite-mass or Pythagorean claim is made.
- Continued the same branch through the sixth negative focus with selected
  distance \(>1.09816\times10^{-6}\) and the seventh positive focus with
  distance \(>0.0506366\). A componentwise ordinary restart failed by
  wrapping, but embedding the two-centre-to-bridge map as an auxiliary graph
  ODE retained all six Poincare generators. The resulting bridge has minimum
  light--primary squared distance \(>0.00262385\), restricted escape margin
  \(>10.2599\), and finite-mass-form comparison margin \(>10.3953\).
  Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** for the regularized
  massless boundary branch. Analytic continuity gives a local massless
  collision-or-escape theorem.
- Derived the exact finite-mass LC chart for the fourth root's opposite
  primary. With \(q=Z+R/(1+A)\), the Kepler parameter is \(A+B\), and
  \(Q=R-Bq/(A+B)\) cancels the singular pair force. Added exact symbolic
  regression tests. The native focus replay now also audits \(p_r<0\) on
  every whole-step enclosure, proving that the successive focus sections
  exhaust possible collisions. Compact convergence through this segment and
  the heavy-pair LC bridge transfers the strict \(>10.39\) hierarchical
  margin. Status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** that every
  sufficiently small compatible positive-mass member in a local fourth-root
  cusp either collides classically or escapes. The cusp size is non-effective
  and tied-family entry is not claimed.
- The direct correlated fifth-section-to-focus experiment failed even after
  moving the tail to $\zeta=18$ and using the octic stable graph: its
  componentwise section projection wrapped the two-centre momenta.  Replaced
  it by the rational common clock $37184019/10^8$ and a rigorous
  one-variable mean-value enclosure anchored at the MPFR fourth root.  The
  exact negative-LC chart map is regular at collision and now has symbolic
  regression coverage.  Forty radius-one and 91 radius-two overlapping
  pico-tiles all passed, proving a continuum collision-or-terminal-escape
  classification on
  $1.264009099014\le\kappa\le1.264009099457$.  Status: **PROVED BY
  COMPUTER-ASSISTED ARGUMENT** for the massless planar family; no tied or
  rational parameter is inferred.  An adversarial comparison with the third
  root certificate found that the two parameter enclosures overlap but the
  cover does not contain the root enclosure.  An ordinary DOP853 seed places
  that root near $1.264009099616$, above the cover, but this is only
  **ORDINARY NUMERICAL EVIDENCE**.  All claims that the cover crosses the
  exact third root were removed.
- Probed the residual lower band with validated directed focus maps.  At
  radius-one tiles centered 45, 60, 75, and 90 pico above the common base,
  the second focus is noncollisional and $p_r<0$ on every whole-step
  enclosure.  A third-focus continuation from the componentwise second-focus
  image wraps catastrophically, while the alternative $\beta=-1$ route loses
  its section atlas near the focus/section-order transition.  Status:
  **VALIDATED NUMERICAL RESULT** for the two-focus finite segments and
  **FAILED** for both terminal formulations.  This identifies the next chart
  repair; it is not a dynamical counterexample.
- Tested a scalar $C^1$ Poincare mean-value restart on the radius-one tile
  centered 45 pico above the common base.  It rigorously reached the second
  focus, but its parameter tangent widened to $2^{30}$--$2^{35}$; the
  third return then lost transversality with momentum widths of order
  $3\times10^4$.  The state doubleton and tangent doubleton were independent,
  so this formulation did not retain the nonlinear one-parameter graph.
  Status: **FAILED** as a lower-band repair; removed from the production
  verifier and retained here as an implementation obstruction.
- A DOP853 common-clock focus scout inherited the already documented
  floating fourth-chart phase error: at offset 120 pico its first-focus
  coordinate differed materially from the validated enclosure.  The scout
  was removed rather than retained as a quantitatively misleading predictor.
  Status: **DISPROVED** as a reliable focus locator; no certificate depended
  on it.
- Tested direct continuation of CAPD's mutable set after the first Poincare
  crossing.  The API preserves a set just after the section, but the tight
  section enclosure is returned separately.  At the offset-45 radius-one
  tile the post-section set already had $p_r\in[-2.60,0.032]$ and the next
  $\beta=-1$ crossing lost transversality.  Status: **FAILED** as a graph
  representation; this does not contradict the tight validated two-focus
  enclosure.
- Reduced the offset-45 tile radius from one pico to $10^{-16}$ and then
  $10^{-18}$ in $\kappa$.  The componentwise third-focus restart still
  expanded the momenta to order $10^5$ and failed.  Status: **VALIDATED
  NUMERICAL RESULT** that simple parameter subdivision does not address the
  dominant reference-state/restart width in this formulation.
- Re-anchored the exact scalar mean-value formula at the rational tile center
  instead of the MPFR collision root.  The required native long-chain point
  propagation was wider, not narrower, and lost the whole-leg $p_r<0$ audit
  before the first focus at offset 45.  Status: **FAILED**; a tile-centered
  repair would require an independent multiprecision point enclosure.
- Produced that independent MPFR-200 point enclosure at the exact rational
  center $\kappa=1.264009098940$ and fixed clock $0.37184019$.  A native
  local mean-value replay sharpened the first focus but still lost the third
  focus with momentum widths of order $4\times10^4$.  Repeating the MPFR
  anchor from $\zeta=18$ widened rather than narrowed every decisive state
  interval.  Status: **VALIDATED NUMERICAL RESULT** for the fixed anchor and
  **FAILED** as a lower-band repair.  The pinned anchor is archived in
  `data/validated_planar_fourth_common_clock_anchor_mp_capd.txt`.
- Replaced componentwise Poincare restarts by a one-generator common-clock
  graph and exact artificial-time section flows. The $\alpha$ flow appends
  $d=A-\alpha$ and scales the whole two-centre vector field by $d/(-p_r)$;
  the $\beta$ flow analogously uses $d/(-p_i)$. Directed whole-step audits
  prove that these are orientation-preserving reparametrizations of the same
  orbit. Exact symbolic regressions cover the section identity and anchored
  graph recentering. Status: **EXACT SYMBOLIC IDENTITY**.
- Generated MPFR-200 common-clock anchors at the exact rational parameters
  $1.264009098934$ and $1.264009098933320$. The latter is within
  $1.9\times10^{-15}$ of the certified fourth-root box, but its point hull
  still wraps in the terminal bridge. Status: **VALIDATED NUMERICAL RESULT**
  for both point anchors and **FAILED** as an effective root-overlap proof.
- Replayed the native tile
  $[1.264009098938900,1.264009098939100]$ through
  $\alpha=2\pi$, $\beta=-1$, a one-millisecond regularized leg, and the
  heavy-binary bridge. The minimum light--primary squared distance is above
  `0x1.3d6bbd67dcbafp-5`; the terminal restricted and finite-mass-form
  margins are above `0x1.3eb5b0e36f346p+2` and
  `0x1.474158b8aadc5p+2`. Status: **VALIDATED NUMERICAL RESULT** for this
  individual tile, not a continuum theorem.
- Independent audits caught and repaired three code defects: absolute versus
  relative Poincare time diagnostics; omission of a fixed anchor from the
  derivative hull for tiles below it; and an exactly 500-millisecond branch
  that skipped propagation. The state enclosures of the first bug were
  unaffected, no stored proof used the third branch, and all pre-repair
  lower-anchor experiments affected by the second bug were discarded.

## 2026-08-24: Fable event reduction and LC-verifier audit

- Imported and independently replayed the exact event-cover architecture.
  The $u=2/5$ command returned `PASS_TIED_EVENT` after 613 validated steps
  and a terminal escape margin above $0.2271$.  This independently supports
  the archived theorem for $(21,20,29)$.
- Audited the multipassage pair-$\{1,3\}$ Levi--Civita equations and found a
  localized proof gap in the damped entry/exit graph overwrite: an inflated
  forcing interval was used without checking that it contained the exact
  state-dependent constant forcing.  Added the exact scalar formula and a
  coordinatewise runtime inclusion gate.  An independent adversarial pass
  then found that CAPD target overlap did not justify the nominal duration
  lower bound.  The final gate uses the actual post-flow clock lower endpoint
  minus the saved start upper endpoint; it rejects nonpositive durations.
- At 256 bits, the post-adversarial-repair verifier completed four LC
  entry/exit cycles for
  exact $u=1/3$, including the deep encounter near physical time $3.166$.
  Every $|w|^2>0$ collision check and every overwrite gate passed.  The run
  was deliberately stopped at $t\simeq3.1670$, before any terminal escape
  certificate; it is therefore a finite validated smoke audit, not a proof
  for $(3,4,5)$.
- Extended the ordinary maximum-event records to retain signed
  $(\operatorname{Re}\zeta,\operatorname{Im}\zeta)$.  On the single
  $u=1/3$ orbit, maximum events occur in all four quadrants.  Three events at
  $t\simeq1.14722,2.25385,4.08765$ have the origin in their ordinary convex
  hull.  This disproves a fixed linear-projection sign architecture as a
  plausible universal obstruction, but is not a theorem about zeros of a
  particular event branch.
- Implemented an experimental five-variable CAPD interval-Newton verifier
  for the nearby general mass--side $F_{30}$ candidate in an exact
  eleven-state Jacobi field.  The 256-bit point-center flow crosses the first
  close pair-$23$ passage but fails at scaled time $0.280269$, physical
  time about $1.7626$, during the second close pair-$23$ passage.  The
  failure is present before the parameter-box $C^1$ flow, so subdivision
  is not a repair; pair-$23$ Levi--Civita propagation is required.
- Replaced that direct formulation by one global pair-$23$ Levi--Civita
  flow, using regularized half-duration as the fifth shooting parameter.
  Independent DOP853 and Radau roots agree to roughly $10^{-13}$ in the
  parameters and give defect $-0.0033559972648$. Regularized sampling
  resolves a previously missed minimum separation near
  $5.0009\times10^{-4}$. A 192-bit point-center enclosure passed that
  deepest encounter but wrapped at scaled time $0.542$; a 256-bit/order-50
  run is in progress. Exact symbolic tests pass for the global LC field and
  its parameter tangents. Evidence remains **ORDINARY NUMERICAL EVIDENCE**
  plus a finite validated segment; there is no interval Newton inclusion.
- Refined the strongest reliable early maximum-event near-brake around
  $u=1/4$. On the corresponding regular maximum branch, scalar minimization
  gives
  \[
  u\simeq0.25001393485,\qquad t\simeq3.23732434,
  \qquad K_{\min}\simeq1.4555186\times10^{-3},
  \]
  with $\zeta\simeq-0.0334600-0.00899615i$. Three tolerance/step refinements
  keep $K$ within $1.6\times10^{-10}$. Thus this branch has an ordinary
  positive local gap rather than an apparent zero. It is a candidate for a
  localized interval branch-gap theorem, not a global exclusion.
- The 512-bit multipassage $u=1/3$ verifier subsequently passed additional
  close passages through the LC exit at physical time about $8.24317$.
  Its physical enclosure then lost usefulness rapidly: the reported hull
  width grew to about $148$ by $t\simeq8.33807$.  The run was stopped without
  a terminal escape marker.  The earlier finite collision-free/brake-excluded
  cover remains valid, but there is still no theorem for $(3,4,5)$.
- Re-evaluated the global-LC $F_{30}$ center with the intrinsic residual
  $(z_r,z_i,G\cdot P)$.  At 256 bits/order 50/max step $5\times10^{-4}$ it
  traversed the full half-orbit in 2351 validated steps, proved
  $r_{\min}^2>1.22160\times10^{-7}$ over every swept enclosure, and enclosed
  the three endpoint residuals inside widths below $9.3\times10^{-10}$.
  The full $C^1$ Newton/Krawczyk box remains pending.
- Replaced the Sturm-only proofs of both $D^{(4)}(0)<0$ and
  $\ddot\Delta_2(0)<0$ by elementary analytic certificates: respectively all
  21 and all 11 exact rational Bernstein coefficients of their numerators on
  $0\le u\le1/2$ are negative. The exact Sturm sequences remain as
  independent regressions.
- Extended the exact Pythagorean-defect jet to sixth order.  The force-series
  recurrence gives $D^{(6)}(0)=-R_{30}/[8u^7(1-u)^7(1+u)^3(1+u^2)^5]$;
  all 31 rational Bernstein coefficients of $R_{30}$ on $[0,1/2]$ are
  positive. Hence $D^{(6)}(0)<0$ analytically on the full fundamental
  interval. This is local and supplies no Taylor-remainder bound.
- Derived the two initial side-order accelerations exactly. On the strict
  fundamental interval, $(r_{12}-r_{23})''(0)<0$ and
  $(r_{23}-r_{31})''(0)>0$; the first sign has a ten-coefficient positive
  Bernstein certificate on $[0,5/12]$, and the second factors elementarily.
  A bounded ordinary probe at seven middle parameters found
  $r_{12}>r_{23}>r_{31}$ up to first syzygy, with the first gap decreasing
  and the second increasing. Evidence beyond the launch derivatives is only
  **ORDINARY NUMERICAL EVIDENCE**; the skinny $u=0.05$ Cartesian probe failed
  at its unresolved close encounter and was not counted.
  The same $u=1/3$ probe gives
  $\ddot\Delta_2\in[-4043.23,50.0105]$ before first syzygy, ordinary evidence
  falsifying a global area-concavity route despite its proved negative launch
  sign.

  Reproduce the bounded middle-parameter probe with

  ```bash
  .venv/bin/python -m scripts.probe_torque_ordering
  ```
- Added $(\ell_{12},\ell_{23})$ to every ordinary $I$-event record.  The
  $u=1/3$ maxima visit all four torque quadrants. Three maxima at times
  $2.25385435$, $2.61592744$, and $4.08765262$ have the origin in their
  ordinary convex hull with positive weights
  $(0.36710,0.14670,0.48620)$. Hence a fixed linear half-plane cannot be the
  torque obstruction; a branch-wise winding or cancellation-time comparison
  is required.
- Proved one global component of the proposed first-syzygy ordering cone.
  Complete cube coordinates for strict ordered triangles and the strict
  fundamental mass interval reduce $\mathfrak g_{23}-\mathfrak g_{31}$ to a
  tensor-degree $(7,6,2)$ rational function. In exact
  $\mathbb Q(\sqrt2)$ arithmetic, all 168 numerator Bernstein coefficients
  are nonnegative and 137 are positive; the denominator is positive. Hence
  gravity always widens $r_{23}-r_{31}$ in that cone. The centrifugal
  difference remains the exact missing term.
- The complementary first gravitational gap is now certified on the complete
  ordered right/obtuse subcone.  A second exact cube map gives 168
  nonpositive Bernstein coefficients (150 negative) for
  $\mathfrak g_{12}-\mathfrak g_{23}$ and a positive denominator.
  Independent Cartesian-force evaluations agree with both symbolic gaps.
  The cone route is reduced to persistence of obtuseness and domination of
  two explicit centrifugal differences.
- The first full global-LC F30 $C^1$ run over a radius-$10^{-8}$ parameter
  box failed at scaled time $0.225958$. The fixed center is regular there,
  but the propagated pair-energy interval had widened to approximately
  $[-260,257]$ and CAPD reached its minimum step. This is a localized
  wrapping failure, not evidence against periodic existence. A 320-bit,
  order-60 half-step replay was stopped as needlessly expensive after 100
  steps; the active 256-bit/order-50 replay at maximum step
  $2.5\times10^{-4}$ tests whether a rigorously much smaller Newton box is
  viable.
- The maximum-step-$2.5\times10^{-4}$ F30 point-center replay completed in
  4233 validated steps and retained
  $r_{\min}^2\ge1.74907\times10^{-7}$, but accumulated endpoint residual
  radii of about $3.14\times10^{-7}$, $1.23\times10^{-6}$, and
  $1.86\times10^{-6}$.  This is worse than the earlier maximum-step
  $5\times10^{-4}$ center enclosure because twice as many interval steps
  accumulate more wrapping.  A radius-$10^{-10}$ one-piece $C^1$ run is
  therefore not justified.  The next F30 validation architecture must use
  sectioned multiple shooting or stronger reconditioning.
- Derived the exact minimum kinetic energy compatible with prescribed
  $(L,\ell_{23},\ell_{31})$ as a Jacobi Gram inverse.  This gives the optimal
  static total-energy bound on the first centrifugal gap while respecting
  the pre-syzygy torque signs.  The proposed global domination nevertheless
  fails at the exact interior cube point
  $(s,w,v,h)=(99/100,10^{-6},99/100,10^{-6})$, where exact
  $\mathbb Q(\sqrt2)$ arithmetic gives a positive margin
  $93.2280669052696\ldots$.  The obstruction is not claimed reachable; it
  proves that the cone argument requires integrated torque history rather
  than instantaneous energy and sign data.
- Normalized the two positive pre-syzygy torque integrals to
  $\eta=(m_1/m_2)(-\ell_{31}/\ell_{23})$.  Exact quotient differentiation
  gives $\dot\eta=(F/{\cal A})(k-\eta)$, where
  $k=(r_{23}^{-3}-r_{12}^{-3})/(r_{31}^{-3}-r_{12}^{-3})$. Thus monotonicity
  of one current-shape scalar would give a rigorous history bound.
- Proved an exact global component of that monotonicity. On the complete
  ordered right/obtuse shape--mass cube, the gravitational contribution to
  $(\log k)''$ has a tensor-degree $(9,9,2)$ numerator with 300 nonnegative
  $\mathbb Q(\sqrt2)$ Bernstein coefficients, 268 positive, over a strictly
  negative factored denominator. Hence it is strictly negative. At the
  launch, where the velocity term vanishes, the full curvature factors
  analytically and is negative for every strict fundamental parameter.
- A bounded ordinary replay at $u=0.1,0.2,0.25,1/3,0.38,0.4,0.41,0.414,$
  and $0.4142$ found no positive sampled increment of $k$ before first
  syzygy; $k$ fell from its launch value in every case.  The unresolved
  velocity-Hessian term prevents promotion to a global theorem.
- The static first-return version was then tested exactly and disproved. For
  $u=2/5$ and $(r_{12},r_{23},r_{31})=(1,39/40,1/30)$, exact linear
  elimination produces an $L=(\log k)'=0$ velocity with pair-torque signs
  $(-,+,-)$ but positive velocity curvature. At physical scale $1/2$, the
  energy-normalized full curvature remains positive with numerator
  $10682.0701224264\ldots$. This is an ambient state, not a reachable-orbit
  claim; it rules out discarding the integrated history even at a
  hypothetical first-return boundary.
- Restricted the optimal energy--torque calculation to a collision-free
  ordered syzygy with body 3 in the middle.  Collinear momentum constraints
  give the exact torque ratio
  $\eta=q(m+1-q)/[(1-q)(n+q)]$ and the sharp transverse coefficient
  $F=n[mn+mq^2+n(1-q)^2]/[m(1-q)^2(n+q)^2]$.  The strict torque signs are
  exactly $0<q<n/(m+n)$.  Parameterizing this interval by
  $q=nz/(m+n)$ and $u=(\sqrt2-1)v$ reduces the energy upper margin for
  $(r_{12}-r_{23})''$ to a bidegree $(20,6)$ polynomial.  Its 147 exact
  $\mathbb Q(\sqrt2)$ Bernstein coefficients consist of 133 negative and 14
  zero values, proving strict negativity in the open square.  This closes the
  first-gap acceleration on the ordered-syzygy face but not its interior
  history or the second gap.
- Re-expressed both centrifugal side-gap terms using only
  $Z=\ell_{23}^2/r_{12}$ and the weighted torque-history ratio $\eta$.
  Their exact shape-time evolution begins with
  $W_s=m_1\delta(y^{-3}-1)-\sigma W/2$ and
  $\eta_s=m_1\delta(y^{-3}-1)(k-\eta)/W$, $W=\sqrt Z$.
  Ordinary pre-syzygy probes put the adverse centrifugal/gravity ratio below
  about $0.018$ for the first gap and $0.60$ for the second over the sampled
  middle parameters.  These ratios are discovery evidence only; the exact
  next target is a reachable $(Z,\eta)$ barrier.
- Tested whether the successful first-gap syzygy-face argument extends to
  the second gap.  It does not.  At exact tied parameter $u=1/3$, choose the
  ordered collision-free syzygy
  $(r_{12},r_{23},r_{31})=(1,697/700,3/700)$, zero radial velocities, and the
  unique transverse amplitude giving $H=-U_0$.  Exact elimination gives
  $\eta=419/32759$, $\dot\Delta_2/\ell_{23}=-292607/131036$, all three
  launch torque signs, and
  $(r_{23}-r_{31})''=-96354167469624287/1827657180810<0$.  The state is not
  claimed reachable.  It disproves every proof of the second syzygy-face
  sign based only on tied masses, energy, $P=L=0$, torque signs, and crossing
  direction.  In the two-scalar variables it violates the exact required
  barrier by $Z/Z_*=1.3724399581\ldots$.
- Eliminated normalized shape velocity from the first derivative of
  $J=\log k$.  The exact result is
  $J_s=(W/\delta)\mathcal A(u,x,y)[\eta-h(u,x,y)]$.  A complete ordered-cone
  substitution reduces $\mathcal A>0$ to a degree-$(7,6,2)$ kernel with 168
  exact $\mathbb Q(\sqrt2)$ Bernstein coefficients: 134 strict signed and
  34 zero, with the opposite strict denominator sign.  At the tied launch,
  $h-k(0)>0$ factors analytically.  Hence global decrease of $k$ is exactly
  the scalar history noncontact problem $\eta<h$.  The earlier $u=2/5$
  static $J'=0$ obstruction was independently recovered as the exact equality
  $\eta=h$.
- Proved the global ordering $h>k$ with a second complete exact certificate:
  the degree-$(11,11,2)$ cube numerator has 432 signed Bernstein
  coefficients, 317 strict and 115 zero.  Differentiating the contact gap
  then gives $W\delta(\eta-h)_s=P-ZS$ with explicit rational $P<0$ and $S$.
  Hence only $S<0$ is dangerous, and there the exact missing bound is
  $Z<Z_J=P/S$.  The energy-normalized $u=2/5$ ambient contact has
  $Z/Z_J=1.05745644351720\ldots$, recovering its outward curvature and
  measuring the failure of total energy.
- Compared $Z_J$ with the second-gap critical amplitude $Z_2$ exactly.  They
  have no global order: the rational points
  $(u,x,y)=(1/3,3/5,41/100)$ and $(1/10,19/20,1/10)$ give respectively
  $Z_J/Z_2=0.8511035828\ldots<1$ and
  $5.9544797122\ldots>1$.  Both signs are exact rational comparisons, not
  sampled-roundoff claims.
- Tested the natural first-contact barrier for the remaining second gap.
  The exact strict ordered-obtuse state
  $u=1/3$, $(x,y,\eta)=(499/500,1/20,3/20)$ satisfies
  $k<\eta<k(0)$, lies on $Z=Z_*$, has energy $-U_0$, $P=L=0$, torque signs
  $(-,+,-)$, and decreasing area.  Yet exact radical arithmetic gives
  $d\log(Z/Z_*)/ds=50.8829734688\ldots>0$.  This disproves a pointwise
  inward-vector-field proof even after imposing the elementary
  weighted-history envelope.
- Resolved the relation between the two amplitude thresholds on the terminal
  ordered-syzygy face.  Exact substitution gives
  $h=\eta=q(m+1-q)/[(1-q)(n+q)]$.  Both contact terms $P,S$ contain the same
  twice-area-squared factor; cancelling it produces a path-independent
  rational extension $Z_J^{\rm syz}$.  After
  $u=(\sqrt2-1)v$, $q=nz/(m+n)$, the four sign cores needed for positivity of
  $Z_J$, negativity of $C_2$, and positivity of $Z_2-Z_J$ have degrees
  $(11,5),(12,5),(11,3),(26,10)$.  Their exact Bernstein signs are
  71 negative/1 zero, 71 positive/7 zero, 39 negative/9 zero, and
  274 positive/23 zero.  This proves $0<Z_J^{\rm syz}<Z_2$ on the complete
  torque-compatible tied face, including the equal-mass edge for $z<1$.
  The thresholds still cross in the interior cone.  The remaining theorem
  is therefore $\eta<h$ before syzygy with terminal equality, plus the single
  reachable limiting-amplitude bound $Z<Z_J^{\rm syz}$.
- Replayed the three previously localized Fable implementation repairs
  against the authoritative tree.  The exact lower atto tile
  `--fourth-common-clock-beta-atto-tile 44000000 100000 1` passed with the
  stored minimum-primary, escape, and finite-mass hexadecimal margins; its
  derivative hull includes the upper anchor.  Changing only the final
  duration to 500 milliseconds now genuinely advances the graph instead of
  leaving $\beta=-1$, but the propagated wide tile wraps and reaches CAPD's
  minimal-step failure near scaled time $18.3643$.  Thus the fixed-time repair
  is active, but 500 milliseconds is a failed enclosure rather than a
  certificate.  Independently reran the 256-bit damped-write smoke chain:
  all four entry/exit gates passed using
  $t_{\rm end,left}-t_{\rm start,right}$, all swept LC enclosures had
  $|w|^2>0$, and the deep passage reproduced exactly
  $t_{\rm exit}=3.1670113440018755$, 140 LC steps, and reconstructed physical
  hull width $4.971428028073183\times10^{-5}$.  The replay was deliberately
  interrupted at that finite horizon; it remains a validated chart-chain
  result, not a terminal $3{:}4{:}5$ theorem.
- Diagonalized the ordered-syzygy kinetic energy in scale and collinear shape
  speed.  With $D=mn+mq^2+n(1-q)^2$, the exact identity is
  $2K_\parallel R=R\dot I^2/(4I)+mnq_s^2/D$, while the transverse part is
  $FZ$.  Energy therefore makes $Z<Z_J^{\rm syz}$ equivalent to the explicit
  coercive bound $2K_\parallel R>2U_0(R_J-R)$.  Tested the natural terminal
  sign repair and disproved it analytically: choosing
  $\sigma=-\varepsilon$, $q_s=-c\varepsilon$ with
  $(1-2q)/2<c<D/[n-(m+n)q]$ makes $r_{31}$ decrease,
  $r_{23}-r_{31}$ increase, and $\dot I<0$, but the longitudinal energy is
  only $O(\varepsilon^2)$.  Hence the missing amplitude estimate must be
  quantitatively history-dependent.
- Strengthened the terminal torque threshold from positivity to the uniform
  exact gap $Z_J^{\rm syz}>1$.  The numerator of $Z_J^{\rm syz}-1$ pulls
  back to a bidegree-$(27,10)$ polynomial with 285 positive and 23 zero
  exact $\mathbb Q(\sqrt2)$ Bernstein coefficients.  The same calculation
  proved $\partial_qR_J<0$: its bidegree-$(30,12)$ numerator has 374
  negative and 29 zero coefficients.
- Resolved the singular equal-mass/torque-edge corner by first directional
  jets.  Both $Z_J$ and $R_J$ are exact Möbius functions of
  $\lambda=(1-z)/(1-v)$; the two sequential limits do not commute.  An
  ordinary augmented-variational probe found
  $\lambda_*=18.15375975649026$ and $Z_*=0.6364615228391086$ at the
  symmetric first syzygy.  These decimals were used only to design rational
  certificate margins.
- Ran the pinned native CAPD endpoint certificate.  A 4715-step full-curve
  cover proves positive separations and positive height before one unique
  transverse first syzygy, with $Z<1$.  A separate 14-dimensional $C^1$
  nonlinear-Poincare calculation propagates the exact tied mass/geometry
  tangent and proves $z_v(1)>18$.  Together with smooth event continuation
  and the exact unit gap, this proves $z<1$ and
  $Z<1<Z_J^{\rm syz}$ at the continued first syzygy throughout an
  existential one-sided near-isosceles neighborhood.  The hexadecimal replay
  is `data/isosceles_syzygy_capd.log`.  This first two-part replay alone made
  no claim about earlier interior contact or post-encounter recurrence; the
  next calculation resolves the former locally.
- Derived the reflection-odd endpoint variation in the relative coordinates
  $(c,b)$ and independently regressed it against the full Cartesian Newton
  force Jacobian.  Exact differentiation of the rational torque threshold
  gives
  $g=\partial_v(\eta-h)=-\sqrt2-2a_v/a-A(d)Y-B(d)$ and the analytic launch
  value $g(0)=(32+8\sqrt2)/7>0$.  A third pinned CAPD step cover proves
  $g>6$ on the launch layer, $g>4$ on the compact middle, and $g_t<-6$ on
  the terminal tail.  It also proves $d<1$ and $Y>0$ throughout.  The exact
  syzygy identity supplies $g(\tau)=0$; analytic division by $v-1$ and the
  event graph $t-\tau(v)$ then proves $\eta<h$ and strict side ordering on
  the complete pre-syzygy arc for every sufficiently near-isosceles member.
  Thus no second brake occurs on or before that first syzygy.  The result
  closes the previously open interior contact locally, but all post-syzygy
  recurrence remains open.
- Rewrote the subsequent endpoint base collision in a pair--12 forced
  Levi--Civita chart, with $q_2-q_1=w^2$ and $dt=|w|^2d\sigma$.  Exact
  symbolic regressions reconstruct both Jacobi accelerations from Cartesian
  Newton forces, verify the tied LC launch tangent, and recover
  $\ell_{12}=2(w_rz_i-w_iz_r)$.  An ordinary central-difference probe found
  $(w_i)_v\simeq-31.41826075$ at the endpoint collision section; this was
  used only to select rational validation margins.
- The pinned native-CAPD $C^1$ Poincare calculation then proved
  $z_r<-4/5$, $r_{31}^2,r_{23}^2>1/500$, and
  $\chi=(w_i)_v<-30$.  The inverse-function theorem isolates the collision
  zero in $(\sigma,v)$, proving that every sufficiently near one-sided member
  traverses the encounter collision-free with
  $\min_{\rm enc}r_{12}=\chi^2(1-v)^2+o((1-v)^2)$ and $\chi^2>900$.  It also gives
  $\partial_v\ell_{12}(1)=-2\chi z_r<0$, so $\ell_{12}>0$ for $v<1$ at the
  section, opposite its launch sign.  This closes the local collision
  unfolding.
- Continued the exact symmetric LC comparison orbit to $\sigma=7$.  Oriented
  $C^1$ Poincare maps isolate all four selected collision zeros before that
  section, place the fifth strictly after it, and prove $(w_i)_v\ne0$ at each
  of the first four.  A separate 7000-step $C^0$ full-tube cover proves
  $r_{31}^2,r_{23}^2>1/500$ throughout and
  $|z|^2+|P|^2>2$ from an overlapping pre-syzygy interface onward.  This
  closes both collision safety and the finite-arc brake gap after compact
  transfer to $v<1$.
- At $\sigma=7$, the fixed nonoptimized choice $\eta=4$ passes the terminal
  binary--escaper theorem with rational margins: separation $>1$, outward
  speed $>2$, radial energy $>1/20$, and post-tidal inner-energy margin $>2$.
  IFT plus compact continuity therefore proves a punctured one-sided
  near-isosceles real interval of nonperiodic tied members.  The endpoint
  comparison remains regularized only; every member to which the theorem is
  applied is an ordinary collision-free classical trajectory through the
  terminal section.
- Tested whether that same fixed $\sigma=7$, $\eta=4$ mechanism could bridge
  toward the middle interval.  Ordinary DOP853 probes pass at $v=0.9999$
  (radial margin $0.0904\ldots$) but fail at $v=0.999$
  (radial margin $-1.155\ldots$); by $v=0.99$ only two selected crossings
  occur before the section and an unselected squared distance falls near
  $1.9\times10^{-6}$.  This is a useful itinerary obstruction, not a theorem
  about nonperiodicity.  It shows that quantifying the endpoint neighborhood
  will not by itself bridge the compact middle range.

## 2026-08-25: tied first-maximum interval certificate

- Replaced the wrapping physical-coordinate family tube by a
  correlation-preserving $C^1$ mean-value graph with the Euclid parameter as
  a frozen state variable.
- Derived direct pair--13 and pair--23 Levi--Civita fields for arbitrary tied
  $u$, augmented by $J=\dot I$ through the exactly regularized equation
  $J_\sigma=|w|^2(2U-4U_0)$.
- Added the exact pair--13 to pair--23 Jacobi-tree transformation at physical
  time $t=1$, before the close pair--23 passage.
- Added whole-step audits on every graph leg for the three pair separations
  and the prescribed $J$ sign. The initial and post-minimum launch layers use
  strict Lagrange--Jacobi concavity/convexity until $J$ itself separates from
  zero.
- Twice ran the left pinned MPFR/CAPD tile on
  $[29/100,29001/100000]$, then certified the abutting right tile through
  $14501/50000$. All runs ended with
  `PASS_TIED_FIRST_MAXIMUM_INTERVAL`. On the union, the first minimum is
  enclosed in $[0.758038,0.758045]$ and the first later maximum in
  $[1.32908,1.33943]$. At the maximum,
  $\operatorname{Im}z\in[-0.0500738,-0.0113187]$ and
  $P_x\in[-0.0561842,-0.00917817]$.
- Seven exact SymPy chart regressions pass, including tied launch
  reconstruction, both regularized Lagrange--Jacobi fields, the chart switch,
  and physical velocity reconstruction. Ruff and `git diff --check` pass.
- Evidence status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** for absence of a
  brake through the first positive maximum on this real interval. Later
  maximum branches remain open.

## 2026-08-25: end-to-end middle real-interval certificate

- Imported and audited the independent endgame driver
  `middle_escape_endgame_capd.cpp`.  It propagates one C0 tripleton with the
  Euclid parameter frozen in the state, uses no Poincare projection, audits
  every accepted solver-step enclosure, and applies three exact chart maps
  by a rigorous mean-value set image.
- Replayed the widened tile
  $u\in[29000000000/10^{11},29000000010/10^{11}]
  =[0.29,0.2900000001]$ against pinned CAPD commit
  `731079217a9254ea2948d742df2b170895effe7f`, at 80-bit MPFR precision,
  tolerance $10^{-14}$, and Taylor order 24.  The main-worktree run exactly
  reproduced all archived phase endpoints and returned
  `PASS_MIDDLE_ESCAPE_ENDGAME` after 3537 accepted steps with maximum state
  hull width $0.00137340$.
- The terminal enclosure has
  $t_*\in[4.30147756370,4.30159216688]$, $d>1.86797758708$,
  $\dot\rho>2.04773008151$, $E_\rho>0.82257204218$,
  $h<-9.27458850157$, and the post-tidal inner-energy margin
  $>5.06969485075$.  A second native-interval checker run on deliberately
  outward-widened printed bounds independently returned
  `PASS_MIDDLE_ESCAPE_TERMINAL_PHASE_ROBUST` with margin
  $>5.06969485073$.
- All 32 selected exact symbolic regressions pass, including both LC fields,
  all chart transformations, the terminal map, and the independent
  total-energy-leaf identities developed in the main route.
- A fresh adversarial review accepted the theorem chain but required two
  implementation hardenings and a formal interface repair: the switch hull
  now explicitly includes its stored center, failed CAPD moves restore a
  complete set copy before retry, and Corollary C1 states the fiberwise,
  launch-window, and LC-residual cover actually checked.  The hardened driver
  independently replayed all 3537 steps with exactly unchanged enclosures and
  terminal margins.
- Evidence status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** for every real
  parameter in the displayed interval.  It includes infinitely many
  rational Euclid parameters and hence infinitely many primitive triples;
  $u=29/100$ gives $(9159,5800,10841)$.
- A superseded experimental route, which repeatedly projected onto LC
  sections and then attempted a common-$\sigma$ pair--23 leg, independently
  confirmed the wrapping diagnosis: after an exact chart switch its hull
  grew from $0.214655$ to $728.258$ by
  $t\in[1.99372,2.01752]$ and failed when an unselected-distance denominator
  enclosed zero.  The validated endgame driver avoids this representation
  failure; it is not a physical collision result.

## 2026-08-25: correlated exchange synchronization

- Added an opt-in FABLE_ENDGAME_SYNC=1 mode to the end-to-end driver.  At
  six pair--13 sections
  $w_r=-3/5,-1/2,-2/5,-3/10,-1/5,0$, CAPD encloses a common transverse
  Poincare image and its full derivative over a convex superset of the
  incoming tripleton.  A mean-value split preserves the distinguished
  Euclid-parameter generator.  A separate C0 copy covers every intervening
  trajectory tube through the latest return and checks separation and the
  complete brake-exclusion disjunction.
- On the already-proved width-$10^{-10}$ tile, the synchronized mode passed
  end to end with maximum hull $3.00087\times10^{-5}$, versus
  $1.37340\times10^{-3}$ for the common-clock representation: a rigorous
  sharpening by a factor about 46.
- A width-$10^{-8}$ stress test passed all six synchronized sections.  The
  section hulls were respectively
  $8.76\times10^{-5}$, $2.77\times10^{-4}$, $8.63\times10^{-3}$,
  $1.54\times10^{-2}$, $1.68\times10^{-2}$, and $1.76\times10^{-2}$.
  The Form-B switch then widened the hull to $0.315$ and the escape phase
  failed its hull guard at $t\approx3.65237$.  This is a localized
  representation failure, not dynamical evidence.
- The intermediate width-$10^{-9}$ tile
  $[0.29,0.290000001]$ passed all 3344 main-flow steps and every independent
  section audit.  Its maximum hull was $4.63549\times10^{-4}$.  The terminal
  phase-robust inequalities retained margin $5.06905197647$; a separately
  compiled interval checker passed an outward-widened terminal box with
  margin $5.06905197641$.
- A second full run at 96-bit MPFR precision, tolerance $10^{-16}$, and
  Taylor order 26 independently passed the same interval, all 3344 main-flow
  steps, and all six audits.  It returned maximum hull
  $4.63548711399\times10^{-4}$ and terminal margin $5.06905197647539$.
- Evidence status: **PROVED BY COMPUTER-ASSISTED ARGUMENT** for the complete
  displayed real interval.  The synchronized log and standalone terminal
  check are archived under data/fable/.

## 2026-08-25: Fable tiling import and post-switch synchronization test

- Independently audited Fable commit
  `6a169f24289973a89274d5b51cc82844cd044a12`.  Its campaign summary has 100
  requested tiles and 100 PASS intervals, each of exact width $10^{-10}$,
  running contiguously from $0.2900000001$ to $0.2900000101$.  Every requested
  interval equals the interval printed in its PASS line; all 99 internal
  endpoints match exactly.  The tar archive contains 100 unique complete
  logs, with one PASS and one terminal record per tile and no FAIL marker.
- Imported the campaign summary and full-log archive into the main history.
  Together with the reviewed base tile, this proves the gap-free widened
  theorem $0.29\le u\le0.2900000101$.  The synchronized width-$10^{-9}$
  one-set theorem independently overlaps the first nine campaign tiles.
- Corrected an economics inconsistency in the accompanying narrative.  At
  the handoff's quoted rate of seven CPU-minutes per width-$10^{-10}$ tile,
  covering the width-$2\times10^{-5}$ committed middle tile requires
  200,000 runs, or 1.4 million CPU-minutes: about 972 CPU-days (2.66
  CPU-years), not 23 CPU-days.  Eight-way parallelism would reduce wall time
  to about 122 days but not CPU cost.  The claimed 23 CPU-days would require
  roughly ten seconds per tile.  This arithmetic does not affect any
  certificate; it strengthens the case for scalable reconditioning rather
  than brute-force tiling.
- Tested a one-set width-$10^{-8}$ repair that projected the sixth exchange
  image onto physical time $t=3.5$, switched to the pair--23 Form-B chart,
  and then projected to $t=3.6$.  All Poincare legs and independent tube
  audits completed rigorously, but the hull widths were respectively
  $0.0449181$, $0.295749$, and $0.554197$.  The computation was stopped after
  the first post-switch image because the reconditioning made the enclosure
  worse and was computationally uneconomic.  This is an enclosure-route
  failure, not evidence for a physical brake or collision.
- A second test planned physical-time sections at $t=3.48,3.49,3.50$ before
  the Form-B map.  The first rigorous image already enlarged the sixth
  exchange-section hull from $0.0176403$ to $0.0266531$, so the run was
  stopped without paying for the later two sections.  Fixed-time projection
  itself is not the missing reconditioning.
- The active repair uses that certified $t=3.48$ image as the actual Form-B
  switch state, $0.02$ earlier than the old switch.  Ordinary reconnaissance
  puts the new selected pair farther from its next pericenter there; the
  interval chart image, not that ordinary observation, will decide whether
  the change is useful.
- The complete early-switch stress test reduced the Form-B image from the old
  $0.295749$ hull to $0.0537352$, a factor $5.50$.  This is a real enclosure
  improvement, but not enough: pair--23 propagation wrapped to hull $2.91259$
  on $t\in[3.6156,3.65514]$ and an interval denominator enclosed zero.  The
  run therefore returned no terminal certificate and makes no dynamical
  claim.
- Inspection of pinned CAPD source identified a stronger chart-map image.
  `DynSysMap` applies the algebraic map while retaining both tripleton
  remainder representations $Br$ and $Qq$, intersects them with the direct
  interval image, and reorganizes with point correlation matrices.  The
  reviewed manual image retained the distinguished $u$ generator but
  conservatively collapsed the remainder to one box.  An opt-in native-map
  width-$10^{-8}$ replay gave the same coordinate hull $0.0537352$ and then
  failed on $t\in[3.61552,3.65520]$ at hull $2.94349$.  The hidden remainder
  correlation did not survive the next binary phase strongly enough; this
  route is inactive.
- Dense ordinary Form-B reconnaissance identified a clean geometric-section
  itinerary for the pair--23 binary.  Starting from $t=3.48$, the branch
  crosses $w_r=0,1/10,3/20,1/10,0,-1/10,-3/20,-1/10,0,1/10$ with directions
  $+,+,+,-,-,-,-,+,+,+$ at approximate times
  $3.5276,3.5620,3.5987,3.6368,3.6472,3.6828,3.7205,3.7573,3.7677,3.8036$.
  These decimals choose sections only; the active CAPD mode must prove each
  common transverse return and independently cover every intervening tube.
- The first rigorous pair--23 return was computationally uneconomic under
  the exchange-era Poincare maximum step $1/2000$ and was interrupted after
  five minutes without a result.  That cap protected a simultaneously close
  unselected pair during the earlier exchange.  In the post-switch chart the
  two unselected pairs are separated, so the Poincare and center solvers now
  use $1/500$.  CAPD still validates every proposed step, while the independent
  C0 tube audit retains its stricter dynamic cap based on every pair
  separation.  This changes cost, not the covering argument.
- With the faster cap, the first direct jump from the switch state to the
  pair--23 section $w_r=0$ completed: CAPD enclosed a common return at
  $t\in[3.5266426,3.5285416]$ and the independent audit covered 125 steps.
  The image hull was nevertheless $0.170031$, too broad for the remaining
  cycles.  The itinerary now inserts every intermediate $1/20$ level around
  each pericenter; the long jump is retired, not cited as a dynamical failure.
- Reading the pinned CAPD Poincare implementation ruled out a hoped-for
  native shortcut: the input tripleton is retained only at a state just after
  the crossing, while the actual fiberwise section image is returned as an
  interval vector.  An opt-in structured reconstruction was therefore added.
  It maps both stored remainder arms through the validated Poincare derivative,
  installs independently invertible point bases tangent to the coordinate
  section, fixes the normal coordinates to zero exactly, and intersects each
  arm with the direct section image.  The existing independent C0 tube audit
  remains unchanged.
- On the already certified width-$10^{-10}$ tile, this reconstruction was
  decisively worse than the reviewed box reconstruction.  The first three
  exchange-section hulls were $4.43192\times10^{-7}$,
  $2.91617\times10^{-6}$, and $9.54454\times10^{-2}$; the run was stopped at
  the third section.  For comparison, the established synchronized driver
  completes this tile with maximum hull $3.00087\times10^{-5}$.  The failure
  localizes the lost information more sharply: after the rank-one Poincare
  projection, separately boxing coordinates in two tangent bases does not
  preserve the useful *shared* one-parameter/remainder dependence.  The code
  is retained behind `FABLE_ENDGAME_STRUCTURED_SECTION=1` as a reproducible
  failed experiment; it supports no new dynamical claim.

## 2026-08-25: explicit defect graph and post-exchange geometric sections

- Replaced the experimental C1 graph's interval anchor by the rigorous form
  $X(u)\subset x+T(u-u_c)+E$, with a nominal point $x$, interval parameter
  tangent $T$, and a separate centered defect $E$.  For every Poincare map,
  the code uses the full-domain derivative enclosure to apply
  $P(X)\subset P(x)+[DP]T(u-u_c)+[DP]E$, intersects the resulting defect with
  the direct Poincare image, and continues to audit the complete trajectory
  tube independently.  Exact section coordinates are imposed only after the
  validated return.  This is experimental machinery pending an independent
  soundness audit, not a promoted theorem.
- On a width-$10^{-12}$ control tile, 80-bit precision, tolerance $10^{-14}$,
  and order 24 delayed but did not remove the old numerical floor: the hull
  was $1.22\times10^{-2}$ at $t=2.3$, $5.08\times10^{-2}$ at the second
  maximum, and the next time-section map failed transversality after
  $t=2.85$.  Increasing to 160 bits, tolerance $10^{-24}$, and order 32
  changed the diagnosis completely.  At $t=0.4$ the defect was only
  $1.15\times10^{-22}$; the graph crossed the $r_{23}\simeq4.4\times10^{-4}$
  encounter, the previous $t=2.9$ failure with hull $1.01\times10^{-9}$,
  and the exchange minimum near $t=3.4685524$.  At the Form-B switch the
  hull was $1.95874\times10^{-3}$, including defect
  $7.51123\times10^{-5}$.  Thus the former early floor was precision-driven,
  not intrinsic to the separated-defect formula.
- Fixed physical-time projection then exposed a different problem: hulls
  stayed below $0.0118$ through $t=3.9$ but jumped to $2.11169$ at $t=4.0$;
  $2.03071$ came from the parameter tangent and only $0.08098$ from the
  defect.  Ordinary reconnaissance places a selected-binary phase turn in
  this window, so this is fixed-clock phase sensitivity rather than a
  numerical anchor floor.
- Added a 21-section pair--23 Form-B itinerary from $w_r=-3/20$ just after
  $t=3.5$ through the third $w_r=3/20$ outward crossing near $t=3.8416$.
  Every CAPD return retains the complete independent tube audit.  The first
  outbound half-cycle passed with hulls from $0.00205$ through $0.00438$,
  eliminating the fixed-clock spike.  Across the next two half-cycles the
  hulls nevertheless grew to $0.04975$, $0.09046$, $0.18085$, $0.41815$,
  and finally $0.93588$.  At the final section, $0.89999$ came from the
  interval tangent and $0.03589$ from the defect.  The run was stopped before
  the terminal time section because its time enclosure already straddled
  $77/20$.  No terminal certificate or new nonperiodicity theorem resulted.
- Tested the exact Lohner split
  $T\delta\subset\operatorname{mid}(T)\delta+
  (T-\operatorname{mid}T)\delta$.  By the Form-B switch it changed the
  decomposition from tangent/defect widths
  $0.0018836/0.0000751$ to approximately
  $1.22\times10^{-8}/0.00195865$, without reducing the total hull.  The first
  two pair--23 sections likewise retained total hulls $0.002048$ and
  $0.002092$ while almost all width lived in the defect box.  This replay was
  stopped: a point tangent plus uncorrelated defect discards the same shared
  parameter dependence in a different component.  The split remains
  reproducible behind `FABLE_ENDGAME_GRAPH_TANGENT_SPLIT=1` but is inactive.
- The active conclusion is now narrow and quantitative.  A scalable graph
  must retain derivative variation as $u$-dependent curvature, for example
  with a validated C2/Taylor form $x+T\delta+Q\delta^2+E$; neither repeated
  interval tangents nor midpoint-plus-box splitting can do so.  The ordinary
  probe now continues pair--23 branch tracking through the terminal window;
  its decimal crossings remain design data only.

## 2026-08-26: directional C2 parameter graph

- Audited CAPD 6.1.0 at pinned commit
  `731079217a9254ea2948d742df2b170895effe7f`.  Its `Hessian` algebra stores
  factorial-normalized quadratic Taylor coefficients: diagonal entries are
  one half of the ordinary second derivative, while mixed entries are the
  full mixed derivative.  The C2 Poincare `computeDP` formulas include both
  first and second derivatives of the fiber-dependent return time.
- Added a deterministic 160-bit analytic probe.  A static polynomial checks
  all diagonal/mixed conventions; the exactly solvable flow
  $x'=1,y'=y$ to the section $x=1$ checks every Poincare derivative; and a
  nonlinear formal initial jet checks custom C1/C2 composition.  The pinned
  replay prints `PASS_CAPD_C2_SEMANTICS` and is archived in
  `data/capd_c2_semantics_probe.log`.
- A full $12\times12\times12$ C2 flow was sound but uneconomic: it did not
  finish even the first $t=2/5$ section in several minutes.  CAPD's validated
  C2 doubleton accepts a sparse Hessian mask only if every first derivative is
  retained.  The working mask therefore keeps the 12 first multiindices and
  only the quadratic multiindex in formal direction 10.
- Direction 10 is not an arbitrary coordinate choice: it is the exact
  conserved state coordinate `ww=u`.  The formal C1 frame replaces column 10
  of the identity by $\gamma'(\delta)$ and has determinant one.  Its inverse
  is an explicit rank-one matrix, so the same masked C2 pass supplies both the
  directional curvature and a complete $DP$ enclosure for mean-value defect
  transport.  `docs/C2_PARAMETER_GRAPH.md` proves the enclosure lemma and
  frame identity.
- The first complete control run used
  $u\in[0.29,0.290000000001]$, 160 bits, tolerance $10^{-24}$, order 32, and
  all 21 post-exchange pair--23 sections.  It passed every collision/brake
  tube audit and every fiber-dependent event.  Selected checkpoints were:

  | checkpoint | total hull | $T\delta$ | $Q\delta^2$ | defect |
  |---|---:|---:|---:|---:|
  | $t=0.4$ | $1.3332\,10^{-11}$ | $1.3332\,10^{-11}$ | $1.8863\,10^{-23}$ | $1.2172\,10^{-22}$ |
  | second minimum | $1.1320\,10^{-10}$ | $1.1318\,10^{-10}$ | $3.8213\,10^{-20}$ | $1.7202\,10^{-14}$ |
  | $t=2.9$ | $2.9684\,10^{-10}$ | $2.6600\,10^{-10}$ | $2.0327\,10^{-19}$ | $3.0840\,10^{-11}$ |
  | fourth minimum | $4.4513\,10^{-6}$ | $1.9352\,10^{-8}$ | $2.0118\,10^{-16}$ | $4.4320\,10^{-6}$ |
  | Form-B switch | $8.0706\,10^{-5}$ | $1.2169\,10^{-8}$ | $1.3340\,10^{-16}$ | $8.0694\,10^{-5}$ |
  | section 14 | $1.8718\,10^{-3}$ | $1.4640\,10^{-8}$ | $1.2808\,10^{-16}$ | $1.8718\,10^{-3}$ |
  | section 21 | $1.9440\,10^{-2}$ | $1.4692\,10^{-8}$ | $1.2450\,10^{-16}$ | $1.9440\,10^{-2}$ |
  | $t=77/20$ | $4.3683\,10^{-2}$ | $1.4606\,10^{-8}$ | $1.1579\,10^{-16}$ | $4.3683\,10^{-2}$ |

- The terminal phase-robust escape test passed with separation margin
  $0.869282$, outward radial speed $2.39037$, outer radial energy $0.119202$,
  and post-tidal inner-energy margin $2.78859$.  Thus the experimental C2
  chain is end-to-end sound on the control interval, subject to independent
  audit.  This interval was already contained in the wider committed Fable
  theorem, so it does not enlarge the proved nonperiodicity set.
- The comparison is diagnostically positive but economically incomplete.
  The old first-order graph had hull $1.0136\,10^{-9}$ at $t=2.9$ and
  $1.9587\,10^{-3}$ at the Form-B switch; the directional C2 values are
  smaller by factors about $3.4$ and $24.3$.  At the final section the old
  tangent contribution was about $0.90$, whereas the new tangent contribution
  is only $1.47\,10^{-8}$.  Curvature therefore fixes the tangent pathology.
  But the new final hull is almost entirely additive defect.  The overlapping
  pair--23/pair--13 encounter near $t=3.45$ amplifies this defect from
  $3.67\,10^{-9}$ to $1.12\,10^{-6}$ before the fourth minimum.  The next
  repair is defect reabsorption or a simultaneous-exchange chart, not another
  tangent split.
- The width-$10^{-11}$ scaling replay completed successfully on
  $[0.29,0.29000000001]$ with the same 160-bit/order-32 settings and the full
  terminal audit.  At $t=0.4$, $t=2.9$, and $t=3.4$, the retained parameter
  spreads were respectively $1.3332\,10^{-10}$, $2.6600\,10^{-9}$, and
  $1.0651\,10^{-8}$--essentially ten times the width-$10^{-12}$ control.
  The corresponding additive defects were $1.22\,10^{-22}$,
  $3.0840\,10^{-11}$, and $3.6688\,10^{-9}$, essentially unchanged from the
  control.  At $t=3.45$ the parameter spread was $9.2048\,10^{-7}$ but the
  width-independent exchange defect was still $1.12394\,10^{-6}$.  The final
  hull was $0.0436841$, and the terminal margins remained positive:
  separation $0.8692823$, radial speed $2.3903656$, radial energy $0.1192007$,
  and post-tidal inner margin $2.7885770$.  The compact replay record is
  `data/middle_c2_width_1e11_summary.log`.
- This is a genuine scaling result for the graph machinery but not a new
  nonperiodicity interval: the closed control interval is already contained
  in Fable's wider theorem.  It localizes the current numerical obstruction
  more sharply.  C2 curvature scales correctly through the chain; the nearly
  width-independent defect injected by the overlapping exchange is now the
  first target.  An opt-in short pair--23 chart sandwich is under validation,
  while an independent Fable prompt asks for the complementary smooth
  fixed-energy reconstruction of the chart-switch `h` coordinate.

## 2026-08-26: exchange-chart sandwich localization

- Added ordinary diagnostics for both square-root lift margins and the
  continuous pair--23 LC root across $3.42\le t\le3.49$.  They identify the
  Form-B departure at $t=171/50$ with ordinary margin about $0.2088$ and the
  Form-A return at $t=173/50$ with margin about $0.1466$.  The continuous
  pair--23 coordinate also crosses $w_i=-1/5$ just before the return, providing
  a possible geometric section if fixed-time phase sensitivity later matters.
- Implemented the sandwich behind
  `FABLE_ENDGAME_GRAPH_EXCHANGE_SANDWICH=1`.  Exact rational tests show that
  pair--13 to pair--23 to pair--13 is the identity on labelled physical
  Jacobi data; the existing symbolic lift tests cover the Form-B and Form-A
  sheets.  All ten focused tests pass, the CAPD driver compiles, and an
  independent adversarial audit found no false analytic lemma.  It required a
  complete terminal replay only if the itinerary were to be promoted.
- The pinned 160-bit width-$10^{-12}$ diagnostic validated every leg through
  the first post-exchange pair--23 section.  The selected pair--23 chart
  improved the through-encounter hull to $4.2800\,10^{-7}$, but the reverse
  static map immediately produced hull $4.7850\,10^{-6}$ and defect
  $4.7456\,10^{-6}$.  The fourth minimum and later Form-B switch were worse
  than the no-sandwich control by factors about $1.59$ and $1.24$.
  Consequently the run was deliberately stopped and no terminal theorem is
  claimed.  This is a localized failed route, not a failure of the C2 graph or
  the chart identities.
- The defect has now been localized to the reverse chart's loss of the exact
  total-energy correlation.  The primary computational repair is a smooth
  fixed-energy reconstruction of target `h`, with an explicit proof that
  projecting off-leaf spurious box points cannot discard any genuine tied
  fiber.  The pair--23 geometric section remains a secondary phase-sensitivity
  repair, not the next primary experiment.

## 2026-08-26: fixed-energy LC reconditioning

- Derived the exact Jacobi identity
  $H=\mu h+\mu_G|P|^2/2-V_{\rm cross}$ and the smooth target-pair formulas
  in `docs/ENERGY_LEAF_RECONDITIONING.md`.  The accompanying fiberwise
  projection lemma proves that applying this map to an ambient graph box is
  rigorous even though it moves spurious off-energy points: every genuine
  tied fiber has $H=-U_0(u)$ and is unchanged.  Eight exact symbolic map and
  energy tests pass.  An independent adversarial audit rederived every
  reduced mass, distance, sign, and code convention and returned `ACCEPT`.
- On the width-$10^{-12}$ sandwich control, energy reconstruction reduced the
  first Form-B switch hull from $9.5085\,10^{-8}$ to $7.0917\,10^{-8}$ and
  the reverse Form-A switch from $4.7850\,10^{-6}$ to
  $2.3987\,10^{-6}$.  The complete pinned replay passed with explicit lift
  margins $0.2088278$ and $0.1466141$ and terminal escape margin $2.74103$.
  Thus the invariant projection is not merely formally sound; it gives a
  material local enclosure improvement.
- The combined itinerary is still not the economical winner.  Its fourth
  minimum hull was $4.6259\,10^{-6}$, slightly above the original
  $4.4513\,10^{-6}$, and later pair--23 cycles amplified the extra reverse-map
  defect.  The final hull was $0.0457664$, versus $0.0436833$ without the
  sandwich.  This is about $4.8\%$ worse despite the smaller switches.  The
  complete record is `data/middle_c2_energy_h_sandwich_summary.log`.
- The final-switch-only replay completed and is the best tested itinerary.  It
  retains the original no-sandwich prefix and applies fixed-energy
  reconditioning only at the established Form-B transition at $t=7/2$.  The
  switch hull fell from $8.0706\,10^{-5}$ to $5.9638\,10^{-5}$, section 14
  from $1.8718\,10^{-3}$ to $1.6812\,10^{-3}$, section 21 from
  $1.9440\,10^{-2}$ to $1.7347\,10^{-2}$, and the terminal hull from
  $0.0436841$ to $0.0386604$.  The terminal escape margin improved from
  $2.78859$ to $2.89149$.  The full compact record is
  `data/middle_c2_energy_h_final_only_width_1e12_summary.log`.
- This $11.5\%$ terminal reduction confirms that invariant reconditioning is
  useful when it replaces an existing chart transformation, while the extra
  sandwich remains uneconomic.

## 2026-08-26: width-$10^{-7}$ fixed-clock failure and exchange synchronization

- The proposed theorem-scale replay on the single closed interval
  $[0.29,0.2900001]$ validated every prefix tube through $t=3.45$ but did not
  reach the fourth minimum.  From $t=3.4$ to $3.45$, the hull increased from
  $1.20521\times10^{-3}$ to $0.547819$ and the additive defect from
  $1.09869\times10^{-3}$ to $0.538621$; the directional quadratic spread was
  still only $4.84\times10^{-7}$.  CAPD then failed closed at the `min4`
  Poincare leg with its minimum-step exception.  This is a localized
  computational failure, not a theorem or evidence for a brake.  The compact
  record is `data/middle_c2_energy_h_width_1e7_failure_summary.log`.
- Added an opt-in `FABLE_ENDGAME_GRAPH_EXCHANGE_SYNC=1` route.  It stops the
  common-clock itinerary at $t=167/50$, uniformly before the first section
  near $t=3.34213$, and projects the directional C2 graph
  through the six already reconnoitered pair--13 LC sections
  $w_r=-3/5,-1/2,-2/5,-3/10,-1/5,0$, before returning to the established
  fourth-minimum, Form-B, pair--23-section, and terminal chain.  Each section
  retains the independent complete-tube collision/brake audit.
- The graph Poincare solvers now inherit the validated synchronizer's strict
  geometric-section step caps, and the independent tube audit dynamically
  caps physical time using the closest unselected pair.  The source compiles
  against pinned CAPD and all focused exact tests pass.
- The first control attempt launched the first Poincare map from $t=13/4$.
  It validated the complete prefix but was deliberately interrupted after
  measuring the cost of a regularized return of length about $14.5$.  Moving
  the common-clock prefix to $167/50$ is a cost-only reconditioning: ordinary
  and prior interval timing put the first $w_r=-3/5$ crossing more than
  $2\times10^{-3}$ later, while the Poincare solver itself still fails closed
  unless every fiber reaches the oriented section.  The implementation also
  requires the complete entry graph to satisfy $w_r<-3/5$, ruling out an
  unintended later return branch before invoking the first map.
- The theorem-eligible width-$10^{-12}$ section control validated the first
  five oriented sections and every swept tube.  Sections 1--3 had hulls
  $6.07\times10^{-9}$, $2.84\times10^{-8}$, and $1.35\times10^{-6}$.
  Crossing the pair--23 encounter at section 4 enlarged the hull to
  $4.74\times10^{-6}$, and section 5 enlarged it again to
  $1.11\times10^{-5}$, almost entirely additive defect.  This is already
  $2.5$ times the no-sync fourth-minimum hull before section 6 or `min4`, so
  the run was deliberately stopped.  Geometric timing is sound but not by
  itself economical; see `data/middle_c2_exchange_sync_partial.log`.
- Added an opt-in in-chart fixed-energy projection after exchange sections
  4--6.  It replaces only `h13` by the exact total-energy formula using the
  two unselected radii, leaving every genuine tied fiber fixed and avoiding a
  selected-distance divisor.  The same fiberwise invariant-projection lemma
  already audited for chart switches proves containment.  A new exact test
  checks the pair--13 distance conventions; 13 focused tests pass.  Component
  diagnostics and relaxed $1/500$ caps away from the two hard sections make
  the next comparison localized and reproducible.  Its CAPD replay remains
  outstanding.
