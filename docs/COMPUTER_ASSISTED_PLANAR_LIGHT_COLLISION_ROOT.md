# A validated transverse collision in the planar joint-limit family

## Theorem

Use the normalized lower-equilateral stable family
$\mathscr U_\kappa$ of `PLANAR_JOINT_SHAPE_DYNAMICS.md`, with transverse
amplitude $T=-1$, and select the heavy primary at $R/2$. There is a unique
zero of the forced Levi--Civita residual in the box

\[
 \begin{aligned}
  1.2679350755&\le\kappa\le1.2679352755,\\
  1.0712484057&\le S\le1.0712486057,
 \end{aligned}
\tag{1}
\]

where $S=-\sigma>0$ is reversed LC time from the fixed $\zeta=0.3$ entry.
Equivalently, exactly one member of this box reaches the selected
light--heavy collision. The interval-Newton image sharpens the root to

\[
 \boxed{
  1.2679351752<\kappa_c<1.2679351759,
  \qquad
  1.0712485051<S_c<1.0712485063.}
\tag{2}
\]

The zero is transverse. For the original increasing-$\sigma$ convention,

\[
 \boxed{
 -3.52212<
 D_c:=\det(\partial_\kappa u,v)
 <-3.38401<0.}
\tag{3}
\]

Thus this collision is a simple component boundary with a rigorously signed
impact parameter. The local normal form in `PLANAR_LIGHT_COLLISION_LC.md`
applies on both punctured sides.

This is a theorem about the massless planar joint limit. It is not a
Pythagorean three-body orbit, a second brake, or a counterexample to the
original conjecture. The classical limiting orbit stops at collision;
regularized continuation is used only to classify the adjacent limiting
scattering branches.

## Exact residual and orientation

Starting from the fixed shape section $\zeta=0.3$, use the positive square-root
lift

\[
 q=Z-R/2=u^2,
 \qquad
 u_r=\sqrt{(|q|+q_x)/2},
 \qquad
 u_i=\sqrt{(|q|-q_x)/2}.
\]

The validated entry box has $q_y>0$, so $u_r,u_i>0$ and
$2u_ru_i=q_y$; no LC deck or square-root branch is ambiguous. Define

\[
 F(\kappa,S)=
 \bigl(\operatorname{Re}u(\kappa,S),
       \operatorname{Im}u(\kappa,S)\bigr),
 \qquad S=-\sigma.
\tag{4}
\]

The second Jacobian column is therefore $\partial_Su=-v$. The determinant
printed by the verifier is

\[
 \det(\partial_\kappa u,-v)=-D_c
 \in[3.3840110561,3.5221124176],
\tag{5}
\]

which gives (3) after restoring the increasing-$\sigma$ orientation.
For the radial-clock angular momentum
$\ell_t=q\times q_t$, one has
$\partial_\kappa\ell_t=2D_c<0$. On the incoming physical-time branch
$dt/d\theta=-1$, so

\[
 6.76802<
 \partial_\kappa(q\times q_\theta)|_{\kappa_c}
 <7.04423.
\tag{5a}
\]

This last sign reversal is purely the incoming clock orientation; it does not
alter the Newton determinant or the collision-root enclosure.

## Analytic tail input at $\zeta=15$

The exact quartic stable jet and the analytic theorem in
`PLANAR_STABLE_TAIL_ENCLOSURE.md` initialize the proof. Relative to its
half-polydisc, put

\[
 \lambda=\max\left\{400e^{-15a_T},
                    6500e^{-15a_L}\right\}<0.04403.
\tag{6}
\]

Because every correction monomial has total degree at least five, restriction
to this smaller polydisc multiplies each state and parameter-tangent bound by
$\lambda^5<1.655\times10^{-7}$. In particular the componentwise boxes used by
the program are the rigorous consequences

\[
 |E_{x,q}|<\lambda^5/(4\times10^9),
 \qquad
 |(\mathcal DE)_{x,q}|<\lambda^5/(8\times10^8),
\]

\[
 |\partial_\kappa E_{x,q}|<\lambda^5/10^9,
 \qquad
 |\partial_\kappa\mathcal DE_{x,q}|<\lambda^5/(2\times10^8).
\tag{7}
\]

The tail before $\zeta=15$ stays in the collision-free equilateral
polydisc. The finite verifier begins at $\zeta=15$.

## Correlation-preserving finite flow

The verifier uses one 13-dimensional `C1Rect2Set` throughout three successive
analytic vector fields:

1. reversed logarithmic-shape flow from $\zeta=15$ to $\zeta=0.3$;
2. a unit-time construction field that holds the shape state fixed and writes
   the exact LC entry coordinates into initially zero variables;
3. reversed forced-LC flow to the time box in (1).

Keeping the same doubleton set is indispensable. Projecting the shape
enclosure to an independent LC interval box destroys the dominant affine
directions and makes the Jacobian enclosure singular. The construction field
computes exactly the nonlinear coordinate map because its right-hand side
depends only on the frozen shape variables.

The `C1` monodromy matrix is multiplied by the analytic initial
$\kappa$-tangent box (7). Since the LC flow is autonomous, its final vector
field gives the $S$ column. Every accepted shape step proves both primary
distance squares greater than $10^{-6}$. The entry box proves $y>0$ and
$u_r,u_i>0$. Every accepted LC step proves

\[
 t>1,
 \qquad R>2,
 \qquad |u^2+R|>1,
\tag{8}
\]

so the full finite segment stays in one analytic selected-primary chart.

## Interval Newton

The rational center is

\[
 x_0=(1.2679351755,1.0712485057).
\]

At that center, the validated residual satisfies approximately

\[
 |F_1(x_0)|<1.6\times10^{-9},
 \qquad
 |F_2(x_0)|<2.2\times10^{-10}.
\]

CAPD encloses $DF(X)$ on the full box (1). With rigorous interval Gaussian
elimination, the interval Newton operator

\[
 N(x_0,X)=x_0-[DF(X)]^{-1}F(x_0)
\tag{9}
\]

is contained strictly in the interior of $X$. Its hexadecimal enclosure is

\[
 \begin{aligned}
 N_\kappa={}&[
 \mathtt{0x1.4497664f166e9p+0},
 \mathtt{0x1.44976651a5c77p+0}],\\
 N_S={}&[
 \mathtt{0x1.123d578f971dap+0},
 \mathtt{0x1.123d579442d03p+0}].
 \end{aligned}
\tag{10}
\]

The interval Newton theorem proves existence and uniqueness in $X$; (5)
proves transversality.

## Reproduction and trusted computing base

The source is
`src/verification/planar_light_collision_newton_capd.cpp`. The wrapper pins
CAPD 6.1.0 at commit
`731079217a9254ea2948d742df2b170895effe7f`, rejects a dirty CAPD tree,
requires the native interval backend and `-frounding-math`, and prints all
certificate intervals in hexadecimal notation.
The exact successful replay is tracked in
`data/validated_planar_light_collision_root_capd.txt`.

Run

    scripts/run_capd_planar_light_collision_newton.sh \
      /path/to/CAPD /path/to/CAPD/build-native

Successful output ends with

    PASS_ROOT method=CAPD-6.1.0-native \
      stage=planar-light-collision-interval-newton

The trusted computing base consists of the analytic tail theorem and its exact
symbolic tests, the displayed C++ verifier, the pinned CAPD native interval
library, the C++ compiler and platform floating-point implementation, and the
standard interval-Newton theorem.

## Status and remaining scope

The theorem (1)--(3) is **PROVED BY COMPUTER-ASSISTED ARGUMENT**. It proves
uniqueness only inside the explicit box (1). Other collision parameters,
other collision times, and the outgoing angular sign on every collision-free
component remain open. Those are the next requirements for a global
classification of $\mathscr U_\kappa$.
