# Late restricted resonance simplicity

This note reduces simplicity of the accumulating restricted turn resonances
to one differentiable parabolic-passage estimate. Simplicity is no longer
needed for the fixed-resonance finite-$B$ exclusion, but its asymptotics are a
natural route to estimates uniform when the resonance index diverges.

## Analytic transverse coordinate

On the center section the incoming and outgoing parabolic speed curves are
real analytic and meet transversely:

\[
 \Delta(\phi)=V_u(\phi)-V_s(\phi),\qquad
 \Delta(0)=0,\qquad \Delta'(0)\ne0.
\tag{1}
\]

Hence any analytic local coordinate $\varepsilon$ transverse to the outgoing
parabolic curve satisfies, after orienting the finite-turn side positively,

\[
 \varepsilon(\phi)=\lambda|\phi|+O(\phi^2),\qquad \lambda>0.
\tag{2}
\]

This is stronger than the formerly conditional existence of a signed energy
coordinate: analytic transversality supplies the coordinate and its nonzero
first derivative. What remains is differentiable control of the long passage
time in that coordinate.

## Parabolic map and the nearly conserved energy

Use the compactification and stroboscopic map from
PARABOLIC_MANIFOLD.md, with $y=w/\sqrt2$:

\[
\begin{aligned}
 x_1&=x-kx^3\bigl(y+R_1(x,y)\bigr),\\
 y_1&=y-kx^3\bigl(x+R_2(x,y)\bigr),
 \qquad k={\pi\sqrt2\over8},
\end{aligned}
\tag{3}
\]

where $R_1,R_2$ are analytic of order at least four. The Kepler energy in
these variables is

\[
 H=y^2-x^2={w^2\over2}-{2\over z}.
\tag{4}
\]

For the degree-four truncation of (3), exact expansion gives

\[
 \boxed{H_1-H=-k^2x^6H.}
\tag{5}
\]

Thus the leading map preserves $H$ through total degree seven, and even its
degree-eight drift vanishes on the parabolic cone $H=0$. The full analytic
map has $H_1-H=O((|x|+|y|)^8)$; a separatrix-adapted correction of $H$ should
absorb the phase-dependent degree-eight term. Equation (5) is an **EXACT
SYMBOLIC IDENTITY** with a regression test.

## Universal blown-up passage

Put $a=\sqrt\varepsilon$ and scale

\[
 x=aX,\qquad y=aY,\qquad s=a^3j,
\tag{6}
\]

where $j$ is the stroboscopic iterate. Formally, and uniformly on compact
sets in $(X,Y)$, (3) tends to

\[
 {dX\over ds}=-kX^3Y,\qquad
 {dY\over ds}=-kX^4,\qquad
 Y^2-X^2=-1
\tag{7}
\]

on the finite-turn branch. The turn is $(X,Y)=(1,0)$. The scaled number of
blocks from parabolic infinity to the turn is therefore

\[
 \int_1^\infty {dX\over kX^3\sqrt{X^2-1}}
 ={\pi\over4k}.
\tag{8}
\]

One stroboscopic block advances physical scaled time by $\pi/2$, so (8)
recovers the exact Kepler constant

\[
 T(\varepsilon)={\pi\over\sqrt2}\varepsilon^{-3/2}(1+o(1)).
\tag{9}
\]

The already proved $C^0$ turn-height theorem is consistent with (9), but it
does not permit differentiation.

## Missing differentiable passage lemma

The precise remaining statement is

\[
 \boxed{
 {dT\over d\varepsilon}
 =-{3\pi\over2\sqrt2}\varepsilon^{-5/2}\bigl(1+o(1)\bigr).
 }
\tag{10}
\]

A sufficient proof is a $C^1$ shadowing theorem for (3) under the blow-up
(6), including the entrance region $X\to\infty$. The derivative error must
be $o(\varepsilon^{-5/2})$; a merely uniform $o(1)$ relative error in (9) is
insufficient. The degree-eight energy drift (5), analytic stable graph, and
transversality (2) identify the inputs, but McGehee's stable-manifold theorem
alone does not state (10).

If (10) holds, then on the finite-turn side

\[
 T'(\phi)
 =-{3\pi\lambda\over2\sqrt2}
   \operatorname{sgn}(\phi)\,\varepsilon(\phi)^{-5/2}(1+o(1)),
\tag{11}
\]

so

\[
 \mathcal A'(\phi)=1+4T'(\phi)\ne0
\tag{12}
\]

for all sufficiently small nonzero finite-turn phases. Every sufficiently
late turn resonance would then be simple. More importantly, the same blow-up
is the natural scale on which to compare the shrinking transverse coefficient
$C_n\asymp Z_n^{-1}$ with finite-$B$ remainders.

Status: (1)--(5) and the constant calculation (8) are **PROVED
ANALYTICALLY** (with (1) importing the validated transversality theorem).
The scaled limit (7) and derivative estimate (10) are **CONJECTURAL** pending
uniform $C^1$ entrance and passage estimates. No simplicity conclusion is
claimed here.
