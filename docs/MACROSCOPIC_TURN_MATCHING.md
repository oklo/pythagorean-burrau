# Macroscopic first-turn matching

The fixed-resonance theorem treats restricted turn heights $Z=O(1)$ as
$B\to0$. Its constants are not uniform when $Z$ approaches the natural
finite-energy scale $B^{-1}$. This note identifies the exact transverse mode
in that crossover.

## Inner outgoing scattering data

On the centered restricted separatrix, let $p_-$ be the incoming-normalized
transverse field and

\[
 \mathscr W_\infty
 =\lim_{\theta\to+\infty}(zp_-'-z'p_-)>0.
\tag{1}
\]

The two outgoing monopole modes are $z$ and $\sqrt z$. Therefore, for one
real rotation coefficient $\gamma$,

\[
 p_-(\theta)=\gamma z-\mathscr W_\infty\sqrt z+o(\sqrt z).
\tag{2}
\]

The coefficient of $\sqrt z$ follows directly from (1): for the exact
parabolic monopole normalization $z'=2/\sqrt z$,

\[
 W(z,\sqrt z)=-1.
\tag{3}
\]

The quadrupole corrections are integrable and do not change this limiting
coefficient. The value of $\gamma$ is immaterial at a radial apocenter,
because it multiplies the infinitesimal rotation mode.

Since $\xi=-p_-/2$, $Y=BZ$, and $Z_x=B\xi$, the physical outer transverse
coordinate on an overlap

\[
 1\ll z={Y_y\over B}\ll B^{-1}
\tag{4}
\]

has the expansion

\[
 Y_x=-{\gamma B\over2}Y_y
 +{\mathscr W_\infty\over2}B^{3/2}\sqrt{Y_y}
 +o\!\left(B^{3/2}\sqrt{Y_y}\right).
\tag{5}
\]

Thus the order-$B$ part is a rotation of the macroscopic radial orbit, while
the first non-rotational displacement is the fractional-order
$B^{3/2}\sqrt{Y_y}$ scattering mode.

## Exact radial Kepler transfer

Let a radial outer Kepler arc leave collision and turn at radius $R>0$:

\[
 s=R\sin^2\psi,\qquad
 {dt\over d\psi}=R^{3/2}\sin^2\psi,\qquad
 0<\psi\le{\pi\over2}.
\tag{6}
\]

The transverse variational equation is

\[
 x''=-{2\over s^3}x.
\tag{7}
\]

Its rotation solution is $x=s$ and has zero velocity at apocenter. A second
solution normalized by $x/\sqrt s\to1$ at collision is

\[
 x_{\rm sc}(\psi)=\sqrt R\sin\psi\cos\psi.
\tag{8}
\]

Direct differentiation gives the exact endpoint data

\[
 \boxed{
 x_{\rm sc}'\!\left({\pi\over2}\right)=-{1\over R}.
 }
\tag{9}
\]

Equations (7)--(9) are an **EXACT SYMBOLIC IDENTITY** with a regression test.
Combining (5) and (9) predicts the physical transverse velocity at a
macroscopic first turn:

\[
 \boxed{
 \dot Y_x(t_{\rm turn})
 =-{\mathscr W_\infty\over2R}B^{3/2}+o(B^{3/2}).
 }
\tag{10}
\]

Because $\mathscr W_\infty>21/50$, the leading coefficient in (10) is
strictly negative for every $R>0$. This is exactly the continuation of the
restricted relation

\[
 C_n\sim-{\mathscr W_\infty\over2Z_n}
\tag{11}
\]

under $R=BZ_n$, since physical velocity is
$B^{-1/2}Z_x'=B^{1/2}C_n$ after including $Z_x=B\xi$.

## Uniform theorem via angular momentum

The needed uniform statement is now proved by avoiding a Cartesian
double-overlap remainder. Define

\[
 \Lambda_B={Y\times\dot Y\over B^{3/2}}
 ={Z\times Z'\over B}.
\tag{12}
\]

On a fixed outgoing section, first-order matching gives
$\Lambda_B\to W/2$. The exact torque factorization and a collision-safe
outgoing LC bootstrap give

\[
 |\Lambda_B(T_B)-\Lambda_B(K)|\le CK^{-3/2}
\tag{13}
\]

uniformly in the first-turn height. Consequently, for every sequence whose
intercepts tend to the centered parabolic phase through the finite-turn side,

\[
 \boxed{
 \Lambda_B(T_B)\longrightarrow{\mathscr W_\infty\over2}.
 }
\tag{14}
\]

See OUTGOING_ANGULAR_MOMENTUM.md for the proof. If the physical turn radius is
$R_B=|Y(T_B)|$, the radial-turn identity yields

\[
 \boxed{
 \dot Y_x(t_{\rm turn})
 =-{B^{3/2}\over R_B}
 \left({\mathscr W_\infty\over2}+o(1)\right).
 }
\tag{15}
\]

For $R_B\to R\in(0,\infty)$ this is precisely the former candidate expansion

\[
\dot Y_x(t_{\rm turn})
=-{\mathscr W_\infty\over2R}B^{3/2}+o(B^{3/2}),
\tag{16}
\]

and the exact Kepler calculation (9) independently checks its coefficient.
The angular-momentum proof is stronger because it remains uniform when
$R_B$ tends to zero or infinity. Since $\mathscr W_\infty>21/50$, a full
labelled brake is impossible at such a first turn.

Status: (7)--(9) are **EXACT SYMBOLIC IDENTITY**. Equations (12)--(15) are
**PROVED ANALYTICALLY**; their sign and the resulting first-turn exclusion
are **PROVED BY COMPUTER-ASSISTED ARGUMENT** through the validated inequality
$\mathscr W_\infty>21/50$. This is not yet a global nonperiodicity theorem,
because it does not exclude a brake after a later outer turn.
