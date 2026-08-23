# First-order transverse incoming matching

The fixed-resonance obstruction in `FINITE_B_TURN_RESONANCE.md` becomes a
finite-$B$ theorem only after differentiating the skinny incoming match with
respect to $B$.  The existing theorem gives $o(1)$ full-state convergence; it
does not give the required quotient by $B$.  This note records the exact extra
cancellation and isolates the remaining uniform estimate.

## Binary-axis geometry

Put $B=\epsilon$, $A=\sqrt{1-B^2}$, and $M=1+A$. In the fixed orthonormal
basis whose first vector is the initial tight-binary direction, the exact
outer Jacobi vector is
\[
Y(0)=\left({AB\over M},-A\right).
\tag{1}
\]
Its relative tilt from the perpendicular is
\[
\ell={1\over2}\arcsin B={B\over2}+O(B^3).
\tag{2}
\]
Thus at late scaled incoming infinity, with the binary axis kept horizontal,
the desired first variation is
\[
{Z_x\over B}\sim-{z\over2},\qquad
{Z_x'\over B}\sim-{z'\over2}.
\tag{3}
\]
A $B$-dependent common rotation would erase (3), but would rotate the binary
by the same amount. The relative tilt, and hence the final angular slip, is
gauge invariant.

## Extra transverse multipole cancellation

Let the physical binary vector be $X=BR e_x$, let the point-mass outer
reference ray have unit direction $v_B$, and let $t_B$ be its positive
quarter-turn. The exact mass-weighted outer field has zero dipole. Its second
moment, including the outer Jacobi prefactor except for total mass $N$, is
\[
{A\over M^2}X\otimes X.
\tag{4}
\]
For $\Phi(Y)=Y/|Y|^3$,
\[
t_B\mathbin\cdot D^2\Phi(\rho v_B)[X,X]
=-{6(t_B\mathbin\cdot X)(v_B\mathbin\cdot X)\over\rho^4}.
\tag{5}
\]
Now $t_B\cdot X=BR+O(B^3)$ while the exact tilt gives
$v_B\cdot X=B^2R/2+O(B^4)$. Since $N=2+O(B)$ and
$A/M^2=1/4+O(B)$, (4)--(5) yield
\[
\boxed{
t_B\mathbin\cdot(\ddot Y+N\Phi(Y))
={3\over4}{B^3R^2\over\rho^4}
+O\left({B^4\over\rho^4}+{B^4\over\rho^5}\right)
}
\tag{6}
\]
on the undeformed binary-axis/radial-ray reference, uniformly in the overlap
regime \(B\le c\rho\le c_0\) with bounded \(R\). The leading transverse
remainder is $B^3\rho^{-4}$, one power of $B$ smaller than the generic
$B^2\rho^{-4}$ outer multipole bound.

Equation (6) is an **EXACT SYMBOLIC IDENTITY** coefficient calculation. To
retain it on the deformed trajectory, use the exact torque factorization
\[
Y\mathbin\times\ddot Y
=-{NA\over M^2}(Y\mathbin\times X)\left(
|Y+X/M|^{-3}-|Y-AX/M|^{-3}
\right).
\tag{6a}
\]
The two offsets have exact separation one and midpoint
$(1-A)/(2M)=O(B^2)$. A symmetric mean-value estimate therefore gives
\[
|Y\mathbin\times\ddot Y|
\le {C|Y\times X|\over\rho^5}
\left(|Y\cdot X|+B^2|X|^2\right).
\tag{6b}
\]

## Early-overlap transverse theorem

The generic estimates already proved in PREPLUNGE_MATCHING.md give, at
radius $\rho$,
\[
|\widehat Y-\widehat{\bar Y}|\le CB^2\rho^{-2},
\qquad
\operatorname{dist}_{\rm LC,normal}(X,\mathcal C)
\le CB^{5/2}\rho^{-3}.
\tag{7}
\]
For $\rho\ge B^\alpha$, $0<\alpha<1/6$, both errors are $o(B)$.
Combining (2), (6b), and (7) gives
\[
|Y\times\ddot Y|
\le C\left(B^3\rho^{-3}+B^4\rho^{-5}
+B^{9/2}\rho^{-6}\right).
\tag{8}
\]
Using $dt\le C\rho^{1/2}|d\rho|$ and bootstrapping the outer angular momentum
from its zero initial value yields
\[
|Y\times\dot Y|\le CB^3\rho^{-3/2},
\qquad
|\widehat Y-\widehat{\bar Y}|\le CB^3\rho^{-2}.
\tag{9}
\]
The higher terms in (8) are smaller than the displayed leading terms because
$1-2\alpha>0$ and $3/2-3\alpha>0$. This improves the generic direction bound
by one power of $B$ without dividing by the binary separation at collision;
the LC normal estimate in (7) is uniform there.

At the overlap $\rho=B^\alpha$, (9) and the tangential speed
$|Y\times\dot Y|/\rho$ give
\[
|\delta\dot Y_\perp|\le C B^{3-5\alpha/2},
\qquad
|\delta Y_\perp|\le C B^{3-\alpha}.
\tag{10}
\]
In late variables $Y=BZ$ and $t=t_{\rm mono}+B^{3/2}\theta$, this implies
\[
\left|{\delta Z_x\over B}\right|
=O(B^{1-\alpha})=o(1),\qquad
\left|{\delta Z_x'\over B}\right|
=O(B^{5/2-5\alpha/2})=o(1).
\tag{11}
\]
These exponents are compatible with the existing pre-plunge range.

Status of (6a)--(11): **PROVED ANALYTICALLY**. An independent adversarial
pass checked the exact torque prefactor and sign, the symmetric denominator
estimate, the conversion from LC normal variables through partial endpoint
blocks, and every exponent in (8)--(11). A prior classical collision is again
an immediate nonperiodic alternative.

## Incoming tail coefficient

After division by $B$, the exact late equations formally converge to
\[
\xi''=c\xi,\qquad
c={r^2-2z^2\over(z^2+r^2/4)^{5/2}}.
\tag{12}
\]
Writing $h=\xi+z/2$ gives
\[
h''-ch=-{3r^2z\over4(z^2+r^2/4)^{5/2}}.
\tag{13}
\]
On the incoming parabolic tail $z=-Y$, the physical-time average
$\langle r^2\rangle=5/8$ makes the leading right side $15/(32Y^4)$.
Since the parabolic Euler operator sends $CY^{-1}$ to $12CY^{-4}$, the formal
weighted boundary data are
\[
h={5\over128Y}+o(Y^{-1}),\qquad
h'={5\over64}Y^{-5/2}+o(Y^{-5/2}).
\tag{14}
\]
The coefficients $3/4$, $15/32$, and $5/128$ have exact symbolic regression
tests. Equation (14) is **CONJECTURAL** until the fast binary average and the
$B$-difference quotient are controlled uniformly.

## Precise remaining theorem

For any fixed sufficiently large incoming section and then through any fixed
restricted turn resonance, prove the following dichotomy as $B\to0$:

1. a prior classical collision already excludes periodicity; or
2. in one binary-axis LC chart,
   \[
   {(Z_{B,x},Z'_{B,x})\over B}\longrightarrow(\xi,\xi'),
   \tag{15}
   \]
   where $\xi$ is the unique solution of (12)--(14).

The proof should reuse the exact LC normal invariants from
`INCOMING_TAIL.md`, but for the $B$-difference quotient. Complete LC blocks
must again be separated from the two partial endpoint blocks. A successful
proof of (15), combined with a simple resonance and $C_n=\xi'(T_n)\ne0$,
would rigorously exclude every sufficiently small finite-$B$ brake in that
local resonance branch.

## Weighted tail propagation

The early estimate suggests a quotient tail argument, but the first version
below fails at collision phases. Recording it exposes the exact LC repair
still needed. The useful exact finite-$B$ variable is not
$Z_x/B+Z_y/2$, but

\[
h_B={Z_x\over B}+{Z_y\over M},\qquad M=1+A.
\tag{16}
\]

Indeed, the exact incoming reference ray has slope
$Z_x/(-Z_y)=B/M$. Thus (16) vanishes on that ray without leaving an
$O(B^2Y_e)$ angular remainder. Let also

\[
\eta_B={R_y\over B}
\tag{17}
\]

in the fixed incoming heavy-binary-axis gauge.

**Candidate Theorem 2 (first-order incoming tail).** Fix a sufficiently large incoming
section $z=-K$. As $B\to0$, either a prior classical collision has already
excluded periodicity, or, uniformly in the circular restricted intercept,

\[
(h_B,h_B',\eta_B,\eta_B')\longrightarrow(h,h',0,0)
\tag{18}
\]

in the common LC section chart. Here

\[
h''-ch=-{3r^2z\over4d^5},\qquad
h=O(|z|^{-1}),\quad h'=O(|z|^{-5/2})
\tag{19}
\]

on the incoming tail. Consequently (15) holds with
$\xi=h-z/2$.

**Proposed proof.** At the moving overlap $Y_e=B^{\alpha-1}$, equations (10)--(11)
and the exact ray definition (16) give

\[
h_B(Y_e)=o(1),\qquad h_B'(Y_e)=o(1).
\tag{20}
\]

The LC normal estimate (7), after the same late scaling and division by $B$,
gives $(\eta_B,\eta_B')=o(1)$ there. The exponent needed for the worst normal
component is $3/2-3\alpha>0$, which holds in the already fixed range
$0<\alpha<1/6$.

Differentiate no flow map here. Instead, divide the exact transverse
equations by $B$ before passing to the limit. Reflection makes the outer
transverse force vanish for every longitudinal pair $(r,z)$ at $B=0$; hence
unknown longitudinal difference quotients do not appear. Direct Taylor
expansion of the exact Jacobi equations gives, away from a prescribed binary
collision,

\[
\begin{aligned}
h_B''-c_Bh_B&=f_B+b_B\eta_B+e_B,\\
\eta_B''+{2\over r_B^3}\eta_B&=g_B,
\end{aligned}
\tag{21}
\]

where, on $K\le Y\le Y_e$,

\[
\begin{gathered}
|c_B|\le CY^{-3},\qquad |b_B|+|f_B|\le CY^{-4},\\
c_B\to c,\qquad
f_B\to-{3r^2z\over4d^5},\qquad b_B\to {3rz\over2d^5},
\tag{22}
\end{gathered}
\]

in the radius-weighted local $L^1$ topology, while

\[
|g_B|\le CBY^{-3}(1+|h_B|),\qquad
\int_K^{Y_e}|e_B|Y^{1/2}\,dY=o(1).
\tag{23}
\]

The zero direct source in the second equation is exact: at $B=0$ the
outer tidal difference is longitudinal when $R=(r,0)$ and $Z=(0,z)$, and the
late binary equation already carries one prefactor $B$. The limits in (22)
are the exact symbolic transverse linearization. Combining
$h=\xi+z/2$ with the equations for $\xi$ and $z$ gives the displayed source
in (19).

At a binary collision, use the LC variables rather than (21). After division
by $B$, the exact normal invariants $(L,K)$ of `INCOMING_TAIL.md` have forcing
bounded by the right side of the second equation in (23). Summation over
complete LC blocks, with the two partial endpoint blocks separate, gives

\[
\sup_{K\le Y\le Y_e}(|\eta_B|+|\eta_B'|)=o(1),
\tag{24}
\]

because
$B\int_K^{Y_e}Y^{-3}d\theta\le CBK^{-3/2}$ and each partial-block
supremum is $O(BK^{-3})$. No inverse binary separation occurs.

It remains to propagate $h_B$. With $x=\log Y$ and the parabolic radial
comparison, (21) becomes a first-order system

\[
U_{B,x}=(A_0+E_B(x))U_B+F_B(x),\qquad
\operatorname{spec}A_0=\{1,1/2\},
\tag{25}
\]

where $E_B=O(e^{-2x})$ uniformly and $F_B=O(e^{-x})$ in the norm
$\sup e^x|U_B|$. Equations (22)--(24) give weighted $L^1$ convergence to the
restricted system. The backward Volterra operator from $x_e=\log Y_e$ is a
uniform contraction after $K$ is chosen large. Its terminal-data term is
multiplied by $e^{A_0(x-x_e)}$ and therefore tends to zero by (20). Thus on
the fixed section it converges to the unique infinite-tail fixed point (19),
uniformly in the intercept. This proves (18). Since

\[
{Z_x\over B}=h_B-{Z_y\over M}\longrightarrow h-{z\over2}=\xi,
\]

and the same holds for the derivative, (15) follows. \(\square\)

Status of Candidate Theorem 2: **CONJECTURAL; the displayed proof is not
valid as written**.  The first false inference is the conversion of quotient
LC-normal control into uniform physical-time control of $\eta_B'$ at the
overlap and in (24).  This failure occurs already for the exact unforced LC
oscillator.  Put
\[
w(s)=a\cos(s/\sqrt2)+i\delta\sin(s/\sqrt2),
\qquad a^2+\delta^2=1,
\]
and let $R=w^2$, with physical time satisfying $d\tau=|w|^2ds$.  At the
reference collision phase,
\[
w=i\delta,\qquad w_s=-a/\sqrt2.
\]
The smooth LC normal invariants are $O(\delta)$, but
\[
\left|{dR_y\over d\tau}\right|\asymp\delta^{-1}.
\tag{26}
\]
Taking, for example, $\delta=B^2$ makes the quotient LC invariants tend to
zero after division by $B$, while
$|\eta_B'|=|R_y'|/B\asymp B^{-3}$ at closest approach.  Thus partial-block
LC estimates cannot imply the supremum in (24), and (18) is false in the
stated physical variables when uniformity includes a limiting binary-
collision phase.

A repair must retain the divided smooth LC invariants $(L/B,K/B)$ through
collision blocks and convert back to $(\eta_B,\eta_B')$ only on sections
uniformly separated from binary collision.  The outer equation uses
$\eta_B$ but does not require a physical-time $\eta_B'$ bound through the
block.  Two further estimates also remain unproved in the proposed argument:

1. direct Taylor expansion gives a transverse binary remainder containing a
   term $CBY^{-3}|\eta_B|$; the bound for $g_B$ in (23) therefore requires an
   explicit bootstrap rather than the displayed estimate with only
   $1+|h_B|$;
2. no formula or bootstrap bound is supplied for $e_B$ that proves its
   weighted $o(1)$ assertion.  Moreover, the log-radius terminal vector uses
   $h_{B,x}\asymp Y^{3/2}h_B'$, so the rates in (11), not merely the $o(1)$
   statement (20), are needed to make the terminal contribution in (25)
   vanish.

Reflection does justify the narrower claim that longitudinal difference
quotients do not enter the first transverse linearization: the transverse
force is identically zero at $B=0$ for every longitudinal pair $(r,z)$.
That cancellation and the formal limits in (22) do not supply the three
missing uniform estimates above.  The proof deliberately avoids assuming
differentiability of the rapid phase clock, but a quotient compactness theorem
has not yet been established.
