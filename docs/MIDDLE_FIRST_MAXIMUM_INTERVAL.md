# A validated middle-parameter first-maximum interval

Date: 2026-08-25

Evidence status: **PROVED BY COMPUTER-ASSISTED ARGUMENT**

## Theorem

Let the normalized Pythagorean--Burrau family have masses

\[
 (m_1,m_2,m_3)=(A(u),B(u),1),
 \qquad
 A={1-u^2\over1+u^2},\quad B={2u\over1+u^2},
\]

and start from its exact tied right-triangle brake configuration.  For every
real parameter

\[
 \boxed{{29\over100}\le u\le{14501\over50000}},
\]

the classical trajectory is collision-free through its first positive local
maximum of the center-of-mass moment of inertia.  There is one intervening
strict local minimum with

\[
 0.758038<t_{\min}<0.758045,
 \]

and the first subsequent maximum satisfies

\[
 1.32908<t_{\max}<1.33943.
\]

This maximum is not a labelled brake.  Consequently no positive brake occurs
on the trajectory segment through and including $t_{\max}$.

This is a uniform theorem for a closed interval of real parameters.  It is
not a finite collection of point integrations.

## Exact regularized formulation

Write $J=\dot I$.  At energy $H=-U_0$, the Lagrange--Jacobi identity is

\[
 \dot J=2U-4U_0.
\]

For a selected pair let $g=w^2$, introduce Levi--Civita time by
$dt=|w|^2d\sigma$, and use $z=dw/d\sigma$.  The augmented regularized
equation is

\[
 J_\sigma=|w|^2(2U-4U_0).
\]

The singular selected-pair potential cancels algebraically in this formula.
Both the pair--13 and pair--23 implementations are therefore regular at their
respective binary-collision faces.  Exact symbolic regressions verify:

- the tied pair--13 square-root launch and reconstruction of the original
  Jacobi brake configuration;
- both regularized Lagrange--Jacobi equations;
- the full pair--13 to pair--23 position and velocity transformation;
- reconstruction of physical selected-pair velocity from $(w,z)$;
- the reduced masses in the pair--23 Jacobi tree; and
- recovery of the former fixed $u=1/3$ chart coefficients.

The parameter is a frozen state variable.  Each event image is represented
by the mean-value graph

\[
 x(u)\in x(u_c)+D_ux([u_-,u_+])(u-u_c),
\]

with the derivative propagated by a validated $C^1$ Poincare map.  This
retains parameter--state correlation that a Cartesian interval box would
lose at the close encounters.

## Certified event topology

The proof uses physical-time sections before and after the two inertia
events.  On every complete connecting tube, not merely at its endpoint, CAPD
proves the prescribed strict sign of $J$ and proves all three mutual
separations positive.  The relevant enclosures are:

| Event or section | Certified enclosure |
|---|---:|
| $J(0.4)$ | $[-0.124830,-0.124818]$ |
| $J(0.7)$ | $[-0.270191,-0.270024]$ |
| first $J=0$, minus-to-plus | $t\in[0.758038,0.758045]$ |
| $U/U_0$ at the minimum | $[5.17942,5.18335]$ |
| $J(1.0)$ | $[0.524940,0.525407]$ |
| pair--13 to pair--23 switch | $t=1$, $J>0$ |
| $J(1.3)$ | $[0.161816,0.202691]$ |
| first later $J=0$, plus-to-minus | $t\in[1.32908,1.33943]$ |
| $U/U_0$ at the maximum | $[0.983016,1.01907]$ |

At the final event the pair--23 regularized residual obeys

\[
 \operatorname{Im}z\in[-0.0500738,-0.0113187],\qquad
 P_x\in[-0.0561842,-0.00917817].
\]

At a collision-free state, a labelled brake forces $z=0$ and $P=0$.
Either displayed strict inequality therefore excludes a brake independently.
Moreover $U<2U_0$ proves $\dot J<0$, so this event is a strict maximum.
The continuous $J$-sign audit from launch to the first minimum and from the
minimum to this maximum establishes that these are the first events of their
respective orientations.

## Reproduction

With CAPD 6.1.0 checked out at
`731079217a9254ea2948d742df2b170895effe7f` and an MPFR-enabled build:

```sh
scripts/run_tied_first_maximum_capd.sh \
  /private/tmp/pythagorean-capd \
  /private/tmp/pythagorean-capd/build-mp
```

The two abutting interval-tile replays are archived in
`data/tied_first_maximum_capd.log`.  The
wrapper checks the pinned CAPD tree and build flags before compiling the
certificate, and fails unless both terminal PASS markers are present.
An independent derivation-and-implementation review returned ACCEPT; its
checklist is `MIDDLE_FIRST_MAXIMUM_ADVERSARIAL_AUDIT.md`.

## Scope and remaining obligation

The theorem excludes the first possible positive brake on this parameter
interval, but it does **not** prove nonperiodicity there.  Later strict maxima
of $I$ have not been bounded or excluded.  The global obligation is still
to classify every later maximum branch or to reach a rigorous terminal
collision-or-escape region.  The small interval width reflects enclosure
growth through the pair--23 close passage, not a dynamical singularity in the
underlying family.
