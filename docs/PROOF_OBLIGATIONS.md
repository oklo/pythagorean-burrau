# Proof obligations

## Main theorem

**Statement.**  For every rational $u\in(0,1)$, the normalized classical
solution has no positive collision-free time with $\mathcal B(u,t)=0$.

**Status:** CONJECTURAL.

Indispensable unresolved obligations:

1. Produce a global dynamical obstruction, or classify every real zero of the
   brake residual.  Initial Taylor signs and catalog gaps do not suffice.
2. Cover arbitrarily close binary encounters without declaring them collisions.
3. Control both singular regimes: loss of uniformity as $u\to0$ and the
   symmetry rank change at $u=\sqrt2-1$.
4. If real zeros exist, establish an exact arithmetic bridge excluding rational
   parameters; analyticity alone is irrelevant.
5. If continuation/degree is used, classify every way zeros can enter through
   collision, escape, infinite return time, or the parameter endpoints.
6. If the integrated-force route is used, prove a genuine global projection or
   cancellation inequality; positivity only at the initial instant is local.

Smallest mandatory falsification tests: $u=1/3$ (exact $4{:}3{:}5$, near the
published Li--Liao $F_{30}$ orbit), $u=1/2$ in the opposite ordering, small
$u$, and perturbations from the real isosceles endpoint.

## Candidate invariant: Pythagorean defect

**Desired lemma.**  Starting at the tied right triangle, $D(t)>0$ at every
positive collision-free time.

**Status:** DISPROVED as a viable candidate by converged ORDINARY NUMERICAL
EVIDENCE at $u=1/3$.  Only $D''(0)>0$ is proved analytically.  A validated
enclosure of the later negative value would make the falsification rigorous,
but no main-theorem step depends on doing so.

## Brake-to-syzygy route

Needed lemmas: existence and regularity of the first-syzygy map uniformly on a
chosen parameter interval; a signed image separation from the classical
second-brake locus; endpoint limits; and proof that later evolution cannot
undo the separation.  Moeckel--Montgomery--Venturelli's regularized collision
orbit cannot itself settle this classical collision-free problem.

## Endpoint route

For $u\to0$, the regularized first-encounter map and a conditional terminal
escape criterion are proved. The first heavy-pair collision is replaced by a
positive miss of order $B^{11}$, but the first outgoing section is still
deeply bound. The remaining obligation is uniform control of
$O(B^{-3/2})$ binary cycles and the phase-sensitive later close interaction,
including a matched asymptotic derivation of the proved restricted limit. That
limit has an exact zero-energy parabolic phase, so a uniform strict-escape
claim is impossible. One must compute its finite-$B$ separatrix splitting and
exclude second brakes on the nonescaping side, or derive an exact condition
for landing on the separatrix. At $u=\sqrt2-1$, the exact
trajectory is now proved to have monotone shrinking half-base and finite
collision.  The remaining obligation is a regularized transverse analysis of
how that collision unfolds when $A\ne B$ and whether any second-brake branch
can emerge.

The skinny matching obligation is now localized more sharply. On a section
$|Y|=B^\alpha$, prove uniform convergence of the outer data and binary action,
including
\[
\Phi_{\rm true}-\Phi_{\rm ref}=o(1)\pmod{2\pi},
\]
through $O(B^{-3/2})$ regularized cycles. At parabolic infinity, explicitly
fix the $|\theta|^{-1/3}$ time-translation mode; otherwise the naive phase
Jacobi field makes the Melnikov integral a zero boundary term. A gauge-free
alternative is to construct the incoming and outgoing parabolic curves
$V_u(\phi),V_s(\phi)$ on $z=0$ and prove
\[
V_u'(0)-V_s'(0)=2V_u'(0)\ne0.
\]
Even after this, prove uniform finite-$B$ persistence and exclude a second
brake for phases on the captured side. Escape/capture classification alone is
not the conjecture.

The restricted transversality sign now has a finite sufficient certificate.
For the even homogeneous Jacobi field $h''=a h$ with
$h(0)=v_*$ and $h'(0)=0$, prove $h'(\pi/4)>0$. Exact comparison gives
$\sqrt8<v_*<4$, proves $h>0$ through the collision, and proves $a>0$ after
$\pi/8$; hence the one remaining sign forces $h$ to grow forever. A
computer-assisted proof needs only a validated enclosure of $v_*$ and this
regularized half-cycle, followed by a short McGehee differentiability argument
identifying growth with $V_u'(0)-V_s'(0)\ne0$.

## Adversarial checklist

Every promoted lemma must be checked for hidden genericity; vector-valued
mean-value misuse; rational-density fallacies; unlabelled/rotated returns;
near-collision substitution; nearby-orbit substitution; loss of endpoint
uniformity; extrapolation of a local sign; and conversion of finite computation
into an infinite claim.

The first-encounter and terminal-escape theorems received independent
adversarial derivations. The audit explicitly checked near-collision
interpretation, reduced-mass conventions, Levi--Civita conjugations, time
scaling, all leading constants, and the maximal-bootstrap closure.
