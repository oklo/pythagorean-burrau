# The transverse scattering invariant at late restricted turns

The first transverse coefficient at every sufficiently late captured
resonance is governed by one number on the centered parabolic separatrix.
This replaces an infinite collection of unrelated sign tests by one scalar
validation problem.  It is a theorem about the collision-regularized
restricted limit; transfer to the finite-$B$ Pythagorean family still needs
the first-order incoming theorem in `FIRST_ORDER_INCOMING_MATCHING.md`.

## The incoming transverse field

Let $(r,z)$ be the centered restricted parabolic separatrix, with $r$ the
prescribed radial heavy-binary separation and

\[
 z''=-{2z\over d^3},\qquad d^2=z^2+{r^2\over4}.
\tag{1}
\]

There is a unique transverse field $p_-$ satisfying

\[
 p_-''=c p_-,\qquad
 c={r^2-2z^2\over d^5},
\tag{2}
\]

and the incoming conditions

\[
 p_--z=O(|z|^{-1}),\qquad
 p_-' -z'=O(|z|^{-5/2})
 \quad(z\to-\infty).
\tag{3}
\]

Existence follows by writing $p_-=z-2h$.  The equation for $h$ is the
inhomogeneous equation (13) of `FIRST_ORDER_INCOMING_MATCHING.md`.  In
$x=\log|z|$, its homogeneous limiting exponents are $1$ and $1/2$, while
the source is $O(e^{-x})$ in the displacement variable.  A Volterra
construction on the two exponentially weighted subspaces gives a unique
solution with $h=O(|z|^{-1})$ and $h'=O(|z|^{-5/2})$.  This is a statement
inside the exact restricted problem and does not assume differentiability of
the finite-$B$ family.

For later parameter dependence, this construction can be made uniform.  On
the incoming tail put \(Y=-z\), \(x=\log Y\), and
\(U=(h,h_x)\).  The parabolic estimates transform the equation into
\[
U_x=(A+E_\phi(x))U+f_\phi(x),
\qquad
\operatorname{spec}A=\{1,1/2\},
\tag{4a}
\]
where, uniformly for \(\phi\) near zero,
\[
\|E_\phi(x)\|\le Ce^{-2x},\qquad
\|f_\phi(x)\|\le Ce^{-x}.
\tag{4b}
\]
The coefficients depend continuously on \(\phi\) in these weighted
\(L^1\) norms.  On a sufficiently late tail the backward Volterra operator
\[
U(x)=-\int_x^\infty
e^{A(x-s)}\bigl(E_\phi(s)U(s)+f_\phi(s)\bigr)\,ds
\tag{4c}
\]
is a uniform contraction in the norm
\(\sup_{x\ge x_0}e^x|U(x)|\).  Its fixed point therefore exists uniquely and
depends continuously on \(\phi\).  Ordinary regularized continuous
dependence propagates that continuity from the tail to every fixed section.

Define the rotation Wronskian

\[
 W=z p_-' -z'p_-.
\tag{4}
\]

Direct substitution of (1)--(2) gives the exact identity

\[
 \boxed{
 W'={3\over2}{r^2zp_-\over d^5}.
 }
\tag{5}
\]

On either parabolic tail the two homogeneous transverse modes are
$|z|(1+o(1))$ and $|z|^{1/2}(1+o(1))$.  Hence $p_-=O(|z|)$, and (5) is
integrable in time because $d\theta\le C|z|^{1/2}d|z|$.  The incoming
conditions give $W(-\infty)=0$, so the finite scattering invariant

\[
 \boxed{
 \mathscr W_\infty:=W(+\infty)
 ={3\over2}\int_{-\infty}^{+\infty}
 {r^2zp_-\over d^5}\,d\theta
 }
\tag{6}
\]

is well defined.  Its integrand is not sign definite.

## Half-line factorization

The centered coefficient $c(\theta)$ is even. Let $k_+$ be the outgoing Jost
field characterized by

\[
k_+''=ck_+,\qquad
k_+-z=O(z^{-1}),\qquad k_+'-z'=O(z^{-5/2})
\quad(z\to+\infty).
\tag{6a}
\]

Time reversal and the oddness of $z$ give the exact identification

\[
p_-(\theta)=-k_+(-\theta).
\tag{6b}
\]

The ordinary Wronskian of the two solutions $k_+$ and $p_-$ is constant.
Evaluating it first at outgoing infinity, where $k_+$ may be replaced by $z$
in the limit, and then at the center gives

\[
\boxed{
\mathscr W_\infty
=k_+(0)p_-'(0)-k_+'(0)p_-(0)
=2k_+(0)k_+'(0).
}
\tag{6c}
\]

Moreover $k_+(0)>0$ analytically. Indeed, on $z>0$ put $q=k_+/z$ and
$W_+=zk_+'-z'k_+$. The outgoing normalization gives $q\to1$ and
$W_+\to0$, while

\[
z^2q'=W_+,\qquad
W_+'={3\over2}{r^2z^2\over d^5}q.
\tag{6d}
\]

A last-zero argument gives $q>0$: if $q$ had a last zero before its positive
tail, then $W_+$ at that zero would be the negative integral of a positive
quantity, hence $q'=W_+/z^2<0$, inconsistent with entry into the positive
region. Thus $W_+(\theta)<0$ for every finite $\theta>0$. Taking
$\theta\downarrow0$ gives
\[
W_+(0)=-\int_0^\infty
{3\over2}{r^2z^2\over d^5}q\,d\theta<0;
\]
strictness holds because the integrand is positive on a nonempty open
interval. Since also
\(W_+(0)=-z'(0)k_+(0)\) and \(z'(0)>0\), this proves \(k_+(0)>0\).

Consequently the unresolved sign has the finite-center equivalent

\[
\boxed{
\mathscr W_\infty>0
\quad\Longleftrightarrow\quad k_+'(0)>0.
}
\tag{6e}
\]

This removes the need to validate a two-sided infinite scattering integral.
One may enclose the outgoing Jost data at a large finite section, integrate
backward in the collision-regularized eccentric-anomaly system, and attach an
analytic tail enclosure.

## Convergence from captured turns

For a finite-turn phase $\phi$, let $(r_\phi,z_\phi)$ be the restricted
orbit arriving parabolically from $z=-\infty$, and let $p_\phi$ have the
same incoming normalization (3).  Denote its first turn by $T(\phi)$ and
$Z_{\rm t}(\phi)=z_\phi(T(\phi))$.

**Theorem 1 (turn-Wronskian limit).**  As $\phi\to0$ through the finite-turn
side,

\[
 \boxed{
 W_\phi(T(\phi))\longrightarrow\mathscr W_\infty.
 }
\tag{7}
\]

**Proof.** Fix a large outgoing section $z=K$.  Regularized continuous
dependence and the weighted construction at incoming infinity give
convergence of $(r_\phi,z_\phi,p_\phi)$ and their first derivatives to the
centered separatrix on the compact segment ending at that section.  Thus
$W_\phi(K)\to W(K)$.

It remains to make the outgoing tail uniform even though its length and turn
height diverge.  Put $q=p_\phi/z_\phi$ where \(z_\phi>0\).  Equations
(1)--(2) give

\[
 z_\phi^2q'=W_\phi,\qquad
 W_\phi'={3\over2}{r_\phi^2z_\phi^2\over d_\phi^5}q.
\tag{8}
\]

The phase-uniform radial comparison in `CAPTURED_TURN_MAP.md` implies

\[
 \int_{z=K}^{T(\phi)}{d\theta\over z_\phi^2}
 \le CK^{-1/2},\qquad
 \int_{z=K}^{T(\phi)}{d\theta\over z_\phi^3}
 \le CK^{-3/2}.
\tag{9}
\]

Indeed, the exact comparison in the captured-turn note gives
\[
z_\phi'^2=4\left({1\over z_\phi}-{1\over Z_{\rm t}}\right)
-2\delta_\phi(z_\phi),
\qquad
0\le\delta_\phi(z)\le {1\over4z^3}.
\tag{9a}
\]
Fix \(\eta<1/2\) and then take \(K\) large.  On
\(K\le z\le\eta Z_{\rm t}\), (9a) gives
\(z_\phi'\ge c z_\phi^{-1/2}\).  On the terminal region
\(\eta Z_{\rm t}\le z\le Z_{\rm t}\), the rescaling
\(z=Z_{\rm t}s\) and the uniform Kepler convergence proved in the same note
give contributions \(O(Z_{\rm t}^{-1/2})\) and
\(O(Z_{\rm t}^{-3/2})\), respectively.  Since \(Z_{\rm t}\ge K\) for
phases sufficiently close to zero, this proves (9), including the terminal
layer.

For completeness, let \(I_j=\int_K^Tz_\phi^{-j}\,d\theta\),
\(Q=\sup|q|\), and \(M=\sup|W_\phi|\) on the outgoing tail.  Equation (8)
gives
\[
Q\le |q(K)|+I_2M,\qquad
M\le |W_\phi(K)|+{3\over2}I_3Q.
\tag{9b}
\]
The fixed-section convergence bounds \(q(K)\) and \(W_\phi(K)\), uniformly
for nearby phases.  Taking \(K\) large enough that
\((3/2)I_2I_3<1/2\) closes (9b).  Equations (8)--(9) therefore give

\[
 \sup_{K\le z\le Z_{\rm t}}|q|\le C,
 \qquad
 |W_\phi(T(\phi))-W_\phi(K)|\le CK^{-3/2},
\tag{10}
\]

uniformly for phases sufficiently close to zero.  The parabolic orbit obeys
the same tail estimate.  First let $\phi\to0$ at fixed $K$, and then let
$K\to\infty$.  This proves (7). \(\square\)

## Consequence for every late resonance

For any apocenter-turn resonance $\phi_n$ from
`CAPTURED_TURN_MAP.md`, let $Z_n=Z_{\rm t}(\phi_n)$ and let

\[
 C_n=-{1\over2}p_{\phi_n}'(T_n)
\tag{11}
\]

be the transverse coefficient of `FINITE_B_TURN_RESONANCE.md`.  At the turn,
$z'=0$ and therefore

\[
 W_{\phi_n}(T_n)=Z_n p_{\phi_n}'(T_n).
\tag{12}
\]

Every selection of resonance roots has $\phi_n\to0$.  Theorem 1 and (12)
prove the asymptotic

\[
 \boxed{
 Z_n C_n\longrightarrow-{\mathscr W_\infty\over2}.
 }
\tag{13}
\]

Consequently

\[
 \boxed{
 \mathscr W_\infty\ne0
 \quad\Longrightarrow\quad
 C_n\ne0\ \hbox{for every sufficiently late restricted resonance}.
 }
\tag{14}
\]

This conclusion is uniform over multiple roots of the same resonance level.
It does not require simplicity of the radial turn map.

## Validated sign

A finite-cutoff ordinary integration, initialized by $p=z$, $p'=z'$ on the
incoming section, gives

| cutoff $K$ | outgoing $p$ | outgoing $p'$ | $W(K)$ |
|---:|---:|---:|---:|
| 10 | $-1.259056$ | $-3.48157\times10^{-2}$ | $0.447762$ |
| 20 | $-1.978047$ | $-2.19103\times10^{-2}$ | $0.446267$ |
| 40 | $-2.987233$ | $-1.24686\times10^{-2}$ | $0.445875$ |
| 80 | $-4.465814$ | $-6.91010\times10^{-3}$ | $0.445769$ |
| 160 | $-6.697240$ | $-3.83241\times10^{-3}$ | $0.445741$ |

This is ordinary numerical evidence for
$\mathscr W_\infty\approx0.4457$. It is also
consistent with the independent late-turn data: for resonance $n=34$,
$-2Z_nC_n\approx0.4105$ and the convergence in (7) is expected to be slow.

The sign itself is now rigorous. The analytic Jost bounds and pinned CAPD
certificate in `COMPUTER_ASSISTED_TRANSVERSE_SCATTERING.md` prove

\[
 \boxed{
 k_+(0)>{7\over20},\qquad k_+'(0)>{3\over5},\qquad
 \mathscr W_\infty>{21\over50}>0.
 }
\tag{15}
\]

The verifier brackets the centered parabolic speed between a certified
first-turn launch and a certified first-leg hyperbolic launch, encloses the
transverse fundamental matrix to eccentric anomaly $80\pi$, and attaches the
infinite Jost tail with the explicit Volterra norm $1/(7K^2)$. Therefore (13)
now establishes $C_n<0$ for all sufficiently late restricted resonances.

Status of (5) and the factorization (6b)--(6c): **EXACT SYMBOLIC IDENTITY**.
Status of $k_+(0)>0$: **PROVED ANALYTICALLY**.

Status of Theorem 1 and (13)--(14): **PROVED ANALYTICALLY** for the exact
restricted family, using the cited phase-uniform large-turn comparison and
regularized continuous dependence.

Status of (15) and eventual $C_n<0$: **PROVED BY COMPUTER-ASSISTED
ARGUMENT**. The subsequently proved first-order LC incoming theorem transfers
this to a finite-$B$ no-brake neighborhood around every fixed sufficiently
late resonance. Radial simplicity is unnecessary for that compactness
argument. The outgoing angular-momentum theorem subsequently makes the
first-turn exclusion uniform as the resonance index tends to infinity. It
does not control later outer turns.
