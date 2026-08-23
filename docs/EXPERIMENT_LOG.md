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
  validated base root.  The tied scalar gap
  \(\Delta_{\rm intr}(B)=\kappa_B-
  \kappa_c(B,T_B,S_B,\Xi_B)\) remains **CONJECTURAL**.
