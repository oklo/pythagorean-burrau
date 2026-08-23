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

## Corrected LC target

The counterexample to (24) does not affect the outer transverse state. The
outer equation depends on the binary position, which is smooth in LC
coordinates, and never on the singular physical binary velocity. This leads
to the following corrected statement.

Let $\mathcal L_B,\mathcal K_B$ be the two smooth transverse LC invariants
from `INCOMING_TAIL.md`, and put

\[
\mathcal N_B={1\over B}(\mathcal L_B,\mathcal K_B).
\tag{27}
\]

**Theorem 3 (LC first-order tail).** Fix $K$ sufficiently large. For the
branch furnished by the early-overlap estimates, either a classical collision
has already occurred before the incoming outer section $z=-K$, or, in the
common LC chart and uniformly in the circular restricted intercept,

\[
\boxed{(h_B,h_B',\mathcal N_B)\longrightarrow(h,h',0).}
\tag{28}
\]

The same quotient convergence propagates across every fixed restricted
segment on which the light body stays separate from the prescribed binary.
In particular, at a fixed restricted apocenter-turn resonance,

\[
{(Z_{B,x},Z'_{B,x})\over B}\longrightarrow(\xi,\xi')
\tag{29}
\]

at the turn, where the binary is separated and $\xi=h-z/2$.

**Proof.** At the moving overlap, the rates already proved in (11) give

\[
|h_B|+|h_{B,x}|=O(B^{1-\alpha})=o(1),
\qquad |\mathcal N_B|=O(B^{3/2-3\alpha})=o(1).
\tag{30}
\]

The derivative conversion in (30) uses
$|dx/d\theta|\asymp Y^{-3/2}$ and the second rate in (11); it does not rely
on the insufficient unweighted statement (20).

The exact transverse cancellation has a stronger LC consequence. On a
complete or partial block at outer radius $Y$, direct expansion of the binary
tidal difference gives

\[
|\Delta\mathcal N_B|\le
CBY^{-3}\bigl(1+\|h_B\|_{\rm block}
                 +\|\mathcal N_B\|_{\rm block}\bigr).
\tag{31}
\]

The reason for the extra $B$ after division in (31) is exact. The late binary
equation already has an exterior prefactor $B$, and at $B=0$ its tidal
difference is longitudinal for every radial $(r,z)$. Its first transverse
variation is therefore $O(BY^{-3})$. The LC conversion multiplies by smooth
bounded functions on the oscillator tube, including on partial collision
blocks. Equation (31) concerns only smooth LC invariants, never physical
$R_y'$. The unregularized first transverse coefficient is checked exactly:
if $U=Z_x/B$ and $\eta=R_y/B$, the tidal-difference component is
\[
{3rzU+(2z^2-r^2/4)\eta\over(z^2+r^2/4)^{5/2}}.
\tag{31a}
\]
The exterior $B$ in the binary equation supplies the claimed remaining
skinny factor.

To pass (31a) through collision, write the normalized LC binary variables as
$w=(w_x,w_y)$ and $p=(p_x,p_y)$. Uniform invertibility of the transverse
coordinate map in (7d) of `INCOMING_TAIL.md` gives

\[
|w_y|+|p_y|\le CB|\mathcal N_B|.
\tag{31b}
\]

The full external binary acceleration has, by (31a),

\[
F_{{\rm bin},x}=O(BY^{-3}),\qquad
F_{{\rm bin},y}=O\!\left(B^2Y^{-3}
(1+|h_B|+|\mathcal N_B|)\right).
\tag{31c}
\]

In LC time its force term $g$ has the same skinny orders because $w$ stays in
a bounded oscillator tube. The exact identities

\[
\mathcal L_s=w_xg_y-w_yg_x,
\]

and

\[
\mathcal K_s=g_xp_y+p_xg_y-{E_s\over2}w_xw_y
\tag{31d}
\]

together with $E_s=O(BY^{-3})$ and (31b)--(31c) give

\[
|\mathcal L_s|+|\mathcal K_s|\le
CB^2Y^{-3}(1+|h_B|+|\mathcal N_B|).
\tag{31e}
\]

Dividing by $B$ and integrating over a bounded-$s$ complete or partial block
is exactly (31). This calculation uses the two endpoint-block suprema rather
than their possibly vanishing physical lengths.

Likewise, Taylor's formula with integral remainder applied to the exact outer
force gives

\[
h_B''-c_Bh_B=f_B+b_B\eta_B+e_B,
\tag{32}
\]

with the coefficient limits in (22), and

\[
|e_B|\le CBY^{-2}
 \bigl(1+|h_B|^2+|\mathcal N_B|^2\bigr)+\omega_B(Y)Y^{-4}.
\tag{33}
\]

Here $\eta_B=R_y/B$ is a binary position observable, so smooth LC normal
coordinates give $|\eta_B|\le C|\mathcal N_B|$. The modulus
$\omega_B(Y)$ is uniformly bounded, tends to zero on every fixed radius
interval, and comes only from the already proved $C^0$ convergence of the
longitudinal state. The $BY^{-2}$ term includes both the quadratic transverse
Taylor remainder (recall $Z_x=O(BY)$) and the $O(B)$ change of the outer
Jacobi prefactor.

For the longitudinal modulus in (33), take $Y=-Z_y$ as the independent
radius. The leading transverse coefficient $-2Y^{-3}$ is the common outer
monopole and is independent of binary phase. All binary/phase dependence in
$c_B$ is $O(Y^{-5})$, while $f_B$ and $b_B$ are $O(Y^{-4})$. Therefore $C^0$
longitudinal convergence on each fixed radius interval produces
$\omega_B(Y)Y^{-4}$ after multiplication by the bounded diamond-norm
variables; it does not leave a nonintegrable
$\omega_B(Y)Y^{-3}$ term. Taylor's integral remainder uses
$|D^2\Phi|\le CY^{-4}$ and the transverse sizes
$|Z_x|\le CBY$, $|R_y|\le CB|\mathcal N_B|$. After division by $B$ these
give precisely the first term of (33). The explicit $O(B)$ change in the
outer Jacobi prefactor is smaller and is included there.

Equations (31)--(33) do not close in the overly strong norm
$\sup Y|h_B|$: the $BY^{-2}$ remainder is resonant with the $Y$ homogeneous
mode and can produce $BY\log(Y_e/Y)$. It is nevertheless uniformly small in
the two-scale norm

\[
\|h_B\|_\diamond=
\sup_{K\le Y\le Y_e}
 \bigl(|h_B|+Y^{3/2}|h_B'|\bigr).
\tag{34}
\]

Indeed, the resonant contribution is bounded by
$CBY\log(Y_e/Y)$, whose supremum is $O(BY_e)=O(B^\alpha)$; its velocity part
has the same bound in (34). The backward Volterra estimate and the LC block
sum, first inside a bootstrap ball, therefore give the more precise
inequalities

\[
\begin{aligned}
\|h_B\|_\diamond
&\le C\bigl(1+\sup|\mathcal N_B|\bigr)
 +CB^\alpha\bigl(1+\|h_B\|_\diamond^2
                    +\sup|\mathcal N_B|^2\bigr)+o(1),\\
\sup|\mathcal N_B|&\le o(1)+CBK^{-3/2}
 \bigl(1+\|h_B\|_\diamond+\sup|\mathcal N_B|\bigr).
\end{aligned}
\tag{35}
\]

Choose a fixed bootstrap radius larger than twice the first constant in
(35).  For fixed large $K$ and then small $B$, the terms carrying $B^\alpha$
and $BK^{-3/2}$ are too small to reach that boundary.  This is the
open-and-closed bootstrap: it first bounds both variables, after which the
second line of (35) forces $\mathcal N_B\to0$. For the outer
remainder, split the radius integral at a fixed $L$. On $[K,L]$ dominated
convergence sends the $\omega_B$ term to zero. On $[L,Y_e]$ its contribution
to the global diamond norm is $O(L^{-1})$, uniformly in $B$, while its
contribution at the fixed section $Y=K$ is $O_K(L^{-3/2})$. The resonant
$BY^{-2}$ term contributes
\[
 O\!\left(B\sqrt{KY_e}+BK\log(Y_e/K)\right)=o(1)
\]
on the fixed section and $O(B^\alpha)$ in (34). The square-root term is the
possible excitation of the $Y^{1/2}$ homogeneous mode; retaining it avoids
an unjustified projection onto the resonant $Y$ mode alone. Thus the
finite-$B$ Volterra operator converges to the unique
restricted operator (19), proving (28).

The finite negative monopole energy also changes the log-radius coefficients
by $O(BY)$.  This is uniformly small because $BY\le BY_e=B^\alpha$, and its
$x$-integral is
\[
 \int_{\log K}^{\log Y_e}Be^x\,dx=O(BY_e)=O(B^\alpha).
\]
The remaining radial coefficient error is $O(Y^{-2})$ plus a term converging
to zero on every compact radius interval.  These are small perturbations of
the same backward Volterra operator and do not require a $Y|h_B|$ bound.

For completeness, no unrecorded first-order longitudinal estimate is needed
on a subsequent fixed segment. Write the smooth LC vector field in fixed
longitudinal and transverse coordinates as $F=(F_L,F_T)$, and put
$T_B=BQ_B$; the prime in (36) denotes regularized LC time. Reflection at the
restricted problem gives the exact identity
$F_T(0,L,0)=0$ for every longitudinal state $L$. Hence
\[
\begin{split}
 Q_B'={}&\left[\int_0^1D_TF_T(B,L_B,sT_B)\,ds\right]Q_B\\
 &+\int_0^1\partial_BF_T(sB,L_B,0)\,ds .
\end{split}
\tag{36}
\]
Only $L_B\to L_0$, already supplied by the zeroth-order incoming theorem, is
used here; $(L_B-L_0)/B$ never occurs. On a fixed segment on which the light
body stays separate, the coefficients in (36) converge uniformly, including
through prescribed binary collisions because the LC vector field is smooth.
Gronwall's inequality propagates the quotient convergence (28), uniformly in
the compact intercept circle. At a turn resonance the binary is at
apocenter, so the chart-to-physical conversion is nonsingular and gives
(29). \(\square\)

Status of Theorem 3: **PROVED ANALYTICALLY**. The statement is uniform in the
circular intercept and covers prescribed binary collisions in LC
coordinates, but it assumes the light body stays separate on the subsequent
fixed restricted segment. Physical binary velocity is used only at the final
separated apocenter. The constants may depend on that fixed segment (and
hence on a fixed resonance index); no uniformity as the resonance index tends
to infinity is asserted. A prior classical collision remains the separate
nonperiodic alternative.
