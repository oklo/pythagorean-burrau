# Experiment log

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

Evidence levels: EXACT SYMBOLIC IDENTITY and PROVED ANALYTICALLY for the
reference formulas and phase sweep; EXACT SYMBOLIC IDENTITY for the local
field and gauge cancellation; ORDINARY NUMERICAL EVIDENCE for transversality;
CONJECTURAL for true-orbit matching and the finite-$B$ splitting expansion.
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
incoming limiting data is CONJECTURAL. Reproduce the identities with:

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
