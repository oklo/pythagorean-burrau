# Validated attachment at the triple-collision end

This note supplies the analytic endpoint boxes used by the compact
triple-endpoint verifier.  Set

\[
 D=r{d\over dr},\quad
 n={\sqrt{19}-1\over4},\quad
 \beta_\pm={3\pm\sqrt7\over4},\quad
 \delta=\beta_+-\beta_-={\sqrt7\over2}.
\tag{1}
\]

The numerical certificate uses

\[
 \rho=2^{-32},\qquad
 -{3087\over12500}\le a\le-{12347\over50000}.
\tag{2}
\]

All estimates below are stated on the larger simple box $|a|\le1/4$.

## Collision-stable base graph

Put $y_e=-\sqrt3/2$, $\eta=y-y_e$, and

\[
 G(y)=y[(y^2+1/4)^{-3/2}-1],\qquad
 N(\eta)=G(y_e+\eta)+{9\over4}\eta.
\]

The exact shape equation is equivalent to

\[
 L_s\eta={r\over1-r}\left(D\eta+{9\over4}\eta\right)
 -{N(\eta)\over1-r},
 \qquad L_s=2D^2+D-{9\over4}.
\tag{3}
\]

Writing $m=(1+\sqrt{19})/4$, one has
$L_s=2(D-n)(D+m)$.  The collision-stable Green operator is

\[
 (\mathcal K_sf)(r)={1\over2(n+m)}\int_0^r
 \left[(r/s)^n-(s/r)^m\right]f(s){ds\over s}.
\tag{4}
\]

Thus the branch with coefficient $a$ is the fixed point

\[
 \eta=ar^n+\mathcal K_sH_s(\eta),
\tag{5}
\]

where $H_s$ is the right side of (3).

On the ball $|\eta|,|D\eta|\le r^n/3$, one has
$-9/10<y_e+\eta<-4/5$.  Direct differentiation gives

\[
 G''(y)=y(6y^2-9/4)(y^2+1/4)^{-7/2},qquad |G''|<4,
\]

and hence $|N(\eta)|\le2\eta^2$.  Since $r/(1-r)\le2r$,

\[
 |H_s(\eta)|\le {13\over6}r^{n+1}+{4\over9}r^{2n}.
\tag{6}
\]

For $|f|\le Fr^k$, (4) and its $D$ derivative are bounded by

\[
 C_{s,0}(k)={1\over2(n+m)}
 \left({1\over k-n}+{1\over k+m}\right),
\]

\[
 C_{s,1}(k)={1\over2(n+m)}
 \left({n\over k-n}+{m\over k+m}\right).
\tag{7}
\]

Both constants are less than one at $k=n+1$ and $k=2n$. Put
$w=\eta-ar^n$ and use the weighted norm

\[
 \|w\|_{2n}=\sup_{0<r\le\rho}r^{-2n}max(|w|,|Dw|).
\]

The ball $\|w\|_{2n}\le3$ lies inside the earlier tube because
$1/4+3\rho^n<1/3$. In this norm the Lipschitz constant is at
most

\[
 {13\over2}\rho+{8\over3}\rho^n<2^{-23}.
\tag{8}
\]

Equations (6)--(8) make this radius-three remainder ball invariant and
contractive:

\[
 \boxed{
 \begin{aligned}
 y(\rho)&=y_e+a\rho^n+[-3\rho^{2n},3\rho^{2n}],\\
 Dy(\rho)&=an\rho^n+[-3\rho^{2n},3\rho^{2n}].
 \end{aligned}}
\tag{9}
\]

Here $3\rho^{2n}<2.1\times10^{-16}$.  The compact verifier stores
$y_X=-Dy$ and uses the looser outward box $10^{-14}$ in both components.

The same contraction is differentiable in the amplitude. Put
$h=\partial_a\eta$ and differentiate (5). The differentiated fixed-point
equation is

\[
 h=r^n+\mathcal K_s\left[
 {r\over1-r}\left(Dh+{9\over4}h\right)
 -{N'(\eta)h\over1-r}\right].
\tag{9a}
\]

On the base ball, $|N'(\eta)|\le4|\eta|\le(4/3)r^n$. For
$q=h-r^n$ in the ball

\[
 \sup_{0<r\le\rho}r^{-2n}\max(|q|,|Dq|)\le16,
\]

one has $|h|,|Dh|<2r^n$. The inhomogeneity in (9a) is bounded by

\[
 13r^{n+1}+{16\over3}r^{2n}.
\]

The constants (7), together with
$r^{n+1}\le\rho^{1-n}r^{2n}$, put its Green image strictly inside the
radius-sixteen ball. The linearized contraction constant is at most

\[
 {13\over2}\rho+{8\over3}\rho^n<2^{-23}.
\]

The differentiable contraction theorem therefore gives the
derivative-strengthened enclosure

\[
 \boxed{
 |\partial_a y-r^n|\le16r^{2n},\qquad
 |D\partial_a y-nr^n|\le16r^{2n}.}
\tag{9b}
\]

In the reversed/reflected variables of the global certificate put $b=-a$ and
$Z=-ry$. Since $r$ is independent of $b$ in the fixed terminal-collision
phase gauge,

\[
 J=\partial_bZ=r\,\partial_a y>0,
 \qquad
 J_s=r_s(\partial_a y+D\partial_a y)>0
\tag{9c}
\]

on the dyadic attachment section. The signs follow from (9b),
$16\rho^n<2^{-22}$, and $1+n>1$. These are genuine parameter derivatives,
not consequences inferred from the statewise boxes in (9).

## Canonical fast transverse mode

Let

\[
 Q(y)={1-2y^2\over(y^2+1/4)^{5/2}},\qquad Q(y_e)=-{1\over2}.
\]

The transverse equation becomes

\[
 L_tp=A(r)Dp+B(r,\eta)p,qquad
 L_t=2(D-\beta_-)(D-\beta_+),
\tag{10}
\]

where

\[
 A={r\over1-r},\qquad
 B={1\over2}\left({Q(y_e+\eta)\over1-r}-Q(y_e)\right).
\]

Since $Q'(y_e)=3\sqrt3/4$,

\[
 B={3\sqrt3a\over8}r^n-{r\over4}+R_B,qquad
 |R_B|\le12r^{2n}.
\tag{11}
\]

The last bound follows on the same base ball from the elementary interval
bounds $|Q'|<3$, $|Q''|<100$.  The two leading inhomogeneous terms must be
subtracted explicitly.  Put

\[
 c_+(a)={3\sqrt3a\over16n(n+\delta)}
\]

and

\[
 p_{+,0}=r^{\beta_+}\left(1+c_+(a)r^n+{r\over4}\right).
\tag{12}
\]

The coefficient $1/4$ and $c_+$ cancel the orders
$r^{\beta_++1}$ and $r^{\beta_++n}$ exactly. These two cancellations are
symbolically regression-tested.  The remaining residual obeys

\[
 |A Dp_{+,0}+Bp_{+,0}-L_tp_{+,0}|
 \le32r^{\beta_++2n}.
\tag{13}
\]

For $k>\beta_+$, the fast Green operator has bounds

\[
 C_{t,0}(k)={1\over2\delta}
 \left({1\over k-\beta_+}-{1\over k-\beta_-}\right),
\]

\[
 C_{t,1}(k)={1\over2\delta}
 \left({\beta_+\over k-\beta_+}
 -{\beta_-\over k-\beta_-}\right).
\tag{14}
\]

At $k=\beta_++2n$, these are less than $1/10$ and $1/3$.
The inverse itself is

\[
 (\mathcal K_tf)(r)={1\over2\delta}\int_0^r
 \left[(r/s)^{\beta_+}-(r/s)^{\beta_-}\right]f(s){ds\over s}.
\tag{14a}
\]

Writing $p_+=p_{+,0}+w_+$, the exact fixed-point equation is

\[
 w_+=\mathcal K_t[R_++A Dw_++B w_+].
\tag{14b}
\]

The perturbation has contraction constant at most
$6\rho^n<2^{-22}$, so

\[
 \boxed{
 \begin{aligned}
 |p_+-p_{+,0}|&\le64r^{\beta_++2n},\\
 |D(p_+-p_{+,0})|&\le64r^{\beta_++2n}.
 \end{aligned}}
\tag{15}
\]

At $r=\rho$ the right side is less than $1.1\times10^{-28}$. Including the
two explicit corrections in (12), the errors relative to the uncorrected
data $(\rho^{\beta_+},\beta_+\rho^{\beta_+})$ are both less than
$10^{-22}$. The verifier uses the much larger box $10^{-20}$.

The slow mode requires analogous subtractions at exponents
$\beta_-+n$ and $\beta_-+1$, both below $\beta_+$. A raw slow-mode Volterra
integral therefore diverges. The global sign calculation avoids this gauge
issue entirely by propagating only $p_+$ and using
$A_-=W(J,p_+)/(-\sqrt7)$.

## Scope

Equations (9) and (15) attach the exact collision-stable family and canonical
fast bundle to a finite dyadic section. They cover the full amplitude box
(2), not merely its numerical midpoint, and are uniform through the limiting
triple collision. They do not establish that this family contains the
incoming parabolic connection; that is the separate compact energy bracket
checked by `triple_endpoint_global_capd.cpp`.

**Status:** **PROVED ANALYTICALLY**. An independent adversarial derivation
checked both Green kernels, evaluated all four operator constants, bounded
$G''$, $Q'$, and $Q''$ directly, expanded the fast residual term by term, and
confirmed that the verifier's $10^{-14}$ and $10^{-20}$ boxes strictly contain
the exact tails by margins of two and three orders, respectively. The
derivative enclosure (9b) follows from the same differentiated contraction;
it fixes the phase gauge explicitly and supplies the collision-side tangent
required by the transversality argument.
