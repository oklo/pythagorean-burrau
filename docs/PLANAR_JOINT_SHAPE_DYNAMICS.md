# Exact shape dynamics of the planar joint family

The joint endpoint reduction leaves a one-parameter massless planar problem.
This note puts that problem in an autonomous shape chart and extracts two
exact scalar identities: a strict Lyapunov function and a signed angular
torque. They do not yet classify every projective parameter, but they give a
concrete scalar obstruction on any branch that stays outside the equilateral
strip.

## Autonomous damped-gradient equation

On either collision-free half of the zero-energy radial heavy-binary orbit,
choose physical time distance $t>0$ from the binary collision and write

\[
 R(t)=C t^{2/3}e_x,\qquad C=9^{1/3}.
\tag{1}
\]

Put

\[
 Z(t)=C t^{2/3}w(\zeta),\qquad \zeta=\log t,\qquad
 w=(x,y).
\tag{2}
\]

On the incoming half $t=t_c-\theta$, whereas on the outgoing half
$t=\theta-t_c$. Thus increasing $\zeta$ is backward physical time on the
incoming half. In particular,
\[
 Z\times Z_\theta=
 \begin{cases}
  -C^2t^{1/3}\Lambda,&\theta<t_c,\\
  +C^2t^{1/3}\Lambda,&\theta>t_c.
 \end{cases}
\tag{2a}
\]
Every monotonicity and sign below is stated first in increasing-$\zeta$
orientation; (2a) must be applied when attaching it to physical scattering.

Substitution in the planar restricted equations gives the exact autonomous
system

\[
 w_{\zeta\zeta}+{1\over3}w_\zeta=\nabla W(w),
\tag{3}
\]

where

\[
 W(x,y)={1\over9}\left[
 x^2+y^2+
 {1\over\sqrt{(x+1/2)^2+y^2}}+
 {1\over\sqrt{(x-1/2)^2+y^2}}
 \right].
\tag{4}
\]

The two equilateral rest points are

\[
 e_\pm=(0,\pm\sqrt3/2),\qquad W(e_\pm)={11\over36}.
\tag{5}
\]

Their shape Hessian is

\[
 D^2W(e_\pm)=
 \begin{pmatrix}1/6&0\\0&1/2\end{pmatrix}.
\tag{6}
\]

Thus the four characteristic exponents in $\zeta$ are

\[
 {-1\pm\sqrt7\over6},\qquad
 {-1\pm\sqrt{19}\over6}.
\tag{7}
\]

The magnitudes of the two negative exponents have ratio
$(1+\sqrt{19})/(1+\sqrt7)$, exactly the projective exponent of the joint
blow-up. Explicitly,
$\ell=-\log|R|=\mathrm{const}-(2/3)\zeta$, so the negative
$\zeta$-exponents $-a_L,-a_T$ become the positive McGehee exponents
$\mu=(3/2)a_L$ and $\tau=(3/2)a_T$.

## Strict shape-energy identity

Define

\[
 \mathcal E={1\over2}|w_\zeta|^2-W(w).
\tag{8}
\]

Taking the scalar product of (3) with $w_\zeta$ gives

\[
 \boxed{\mathcal E_\zeta=-{1\over3}|w_\zeta|^2\le0.}
\tag{9}
\]

Consequently every nonhomothetic orbit on the stable manifold of $e_\pm$,
oriented so that $w(\zeta)\to e_\pm$ as $\zeta\to+\infty$, satisfies

\[
 \mathcal E(\zeta)+{11\over36}
 ={1\over3}\int_\zeta^\infty |w_\eta|^2\,d\eta>0.
\tag{10}
\]

This is a genuine global identity on every collision-free shape segment. It
does not rely on a Taylor truncation.

The shape potential has the sharp global lower bound

\[
 \boxed{W(w)\ge{11\over36},}
\tag{10a}
\]

with equality only at $e_\pm$. Indeed, if
$d_\pm=|w\pm e_x/2|$, then

\[
 9W=\left({d_+^2\over2}+{1\over d_+}\right)
    +\left({d_-^2\over2}+{1\over d_-}\right)-{1\over4},
\]

and for every $d>0$,

\[
 {d^2\over2}+{1\over d}-{3\over2}
 ={(d-1)^2(d+2)\over2d}\ge0.
\]

Equality requires $d_+=d_-=1$, which gives the two equilateral points.

**Corollary.** System (3) has no nonconstant collision-free periodic orbit in
$\zeta$ and no nonconstant orbit asymptotic to either equilateral rest point
at both $\zeta\to-\infty$ and $\zeta\to+\infty$. Moreover, a nonhomothetic
stable-manifold orbit approaching $e_\pm$ has

\[
 \boxed{w_\zeta(\zeta)\ne0}
\tag{10b}
\]

at every finite collision-free point.

**Proof.** A periodic orbit would make the integral of (9) over a period
zero, forcing $w_\zeta\equiv0$. At either equilateral end the energy tends to
$-11/36$, so a two-ended equilateral connection would likewise force the
integral of $|w_\zeta|^2$ over the whole line to vanish. Finally (10) gives
$\mathcal E>-11/36$ at every finite point of a nonhomothetic stable orbit. If
$w_\zeta=0$, then $\mathcal E=-W\le-11/36$ by (10a), a contradiction.
\(\square\)

Statement (10b) concerns shape velocity. It does not by itself say that the
physical light velocity vanishes or not, because
$Z_t=Ct^{-1/3}(2w/3+w_\zeta)$.

## Exact torque factorization

Let

\[
 \Lambda=w\times w_\zeta=x y_\zeta-y x_\zeta
\tag{11}
\]

be the shape angular momentum. Put

\[
 d_\pm^2=(x\pm1/2)^2+y^2,\qquad
 Q=x^2+y^2+{1\over4}.
\]

Taking the cross product of (3) with $w$ gives

\[
 \Lambda_\zeta+{1\over3}\Lambda
 ={y\over18}\left(d_+^{-3}-d_-^{-3}\right).
\tag{12}
\]

The difference has the exact Hadamard factorization

\[
 \boxed{
 \Lambda_\zeta+{1\over3}\Lambda
 =-xy\,K(x,y),\qquad
 K={1\over12}\int_{-1}^{1}(Q+\sigma x)^{-5/2}\,d\sigma>0.}
\tag{13}
\]

The positivity is strict at every collision-free point. Therefore the torque
has sign $-\operatorname{sgn}(xy)$, with no small-parameter qualification.
For a stable-manifold orbit, the negative transverse exponent
$a_T=(1+\sqrt7)/6$ is larger than $1/3$, so
$e^{\zeta/3}\Lambda\to0$ at the equilateral end. Integration of (13) yields

\[
 \boxed{
 \Lambda(\zeta)=e^{-\zeta/3}
 \int_\zeta^\infty e^{\eta/3}x(\eta)y(\eta)
 K(x(\eta),y(\eta))\,d\eta.}
\tag{14}
\]

Thus a fixed sign of $xy$ on the increasing-$\zeta$ tail forces the same
nonzero sign of $\Lambda$ at every smaller-$\zeta$ point on that tail.

## A convex outer strip

The transverse derivative of $W$ has the sign of $x$ throughout the closed
outer strip

\[
 |y|\ge{\sqrt3\over2}.
\tag{15}
\]

More precisely,

\[
 W_{xx}(x,y)\ge\delta_*,
\qquad
 \delta_*={1\over9}\left({7\over4}-{8\over3\sqrt3}\right)>0.
\tag{16}
\]

To prove this, put $Y=y^2\ge3/4$ and

\[
 g_Y(q)={Y-2q\over(Y+q)^{5/2}}.
\]

Then

\[
 9W_{xx}=2-g_Y((x+1/2)^2)-g_Y((x-1/2)^2).
\]

At least one of the two squared arguments is at least $1/4$.
The elementary derivative

\[
 g_Y'(q)={3q-\frac92Y\over(Y+q)^{7/2}}
\]

shows that $g_Y(q)\le g_Y(1/4)$ for $q\ge1/4$, while
$g_Y(q)\le Y^{-3/2}$ for every $q\ge0$. Hence their sum is at most

\[
 Y^{-3/2}+{Y-1/2\over(Y+1/4)^{5/2}}
 \le {8\over3\sqrt3}+{1\over4}<2,
\]

where the middle expression decreases for $Y\ge3/4$. This proves (16).
Indeed its derivative is
\[
 -{3\over2}Y^{-5/2}
 +{3\over2}{1-Y\over(Y+1/4)^{7/2}}<0:
\]
for $Y\ge1$ both terms are nonpositive, while for
$3/4\le Y\le1$ the positive term is at most $3/8$ and the negative term has
magnitude at least $3/2$.
Evenness of $W$ in $x$ now gives

\[
 xW_x(x,y)\ge\delta_*x^2.
\tag{17}
\]

## Quadratic bending at the zero projective parameter

The outer strip is not invariant for the whole projective family. This can be
seen exactly at $\kappa=0$. Near the lower equilateral rest point put

\[
 y=-{\sqrt3\over2}+q,\qquad
 a_T={1+\sqrt7\over6},\qquad
 a_L={1+\sqrt{19}\over6}.
\]

The stable expansion has the form

\[
 x=T e^{-a_T\zeta}+\cdots,\qquad
 q=H e^{-a_L\zeta}+kT^2e^{-2a_T\zeta}+\cdots.
\tag{17a}
\]

The exact quadratic transverse forcing in the $q$ equation is
$\sqrt3\,x^2/24$. Since

\[
 4a_T^2-{2a_T\over3}-{1\over2}
 ={5\over18}+{\sqrt7\over9}>0,
\]

coefficient matching gives

\[
 \boxed{
 k={\sqrt3/24\over
 4a_T^2-2a_T/3-1/2}
 ={2\sqrt{21}-5\sqrt3\over4}>0.}
\tag{17b}
\]

Moreover $a_L<2a_T$. Therefore $\kappa<0$ approaches $e_-$ from the outer
side $y<-\sqrt3/2$, $\kappa>0$ approaches from inside the strip, and
$\kappa=0$ also bends inside because of (17b). A proposed proof based on
outer-strip invariance for every $\kappa$ is consequently false; the convex
strip theorem must be used as a conditional transition rule.

## Signed-tail lemma

**Lemma.** Let a nonrectilinear stable-manifold orbit tend to $e_+$ or $e_-$
as $\zeta\to+\infty$, with nonzero signed transverse slow amplitude $T$.
On any tail on which (15) holds,

\[
 \operatorname{sgn}x=\operatorname{sgn}T,\qquad
 \operatorname{sgn}x_\zeta=-\operatorname{sgn}T.
\tag{18}
\]

**Proof.** Put $v=e^{\zeta/3}x_\zeta$. Equation (3) gives

\[
 v(\zeta)=-\int_\zeta^\infty e^{\eta/3}W_x(x(\eta),y(\eta))\,d\eta,
\tag{19}
\]

because $a_T>1/3$. On a tail where $x$ has the sign of $T$, (17) makes
$v$ have the opposite sign. A first zero of $x$ encountered while continuing
backward would contradict that monotonicity. The asymptotic slow mode starts
the argument, proving (18). \(\square\)

Combining (14) and (18), every such tail has a nonzero shape angular momentum
of sign $\operatorname{sgn}(xy)$. This is the first explicit scalar sign
theorem on the genuinely planar projective family. It remains conditional on
the orbit staying in the outer strip; a proof that every relevant
$\mathscr U_\kappa$ either remains there until an outgoing section or enters
a finite classified transition region would turn it into a global scattering
obstruction.

## Status

Equations (1)--(14), the convexity bound (16), and the signed-tail lemma are
**PROVED ANALYTICALLY**. Their symbolic components are covered by exact
regression tests. Global outer-strip invariance and global classification of
all $\mathscr U_\kappa$ are **CONJECTURAL**.
