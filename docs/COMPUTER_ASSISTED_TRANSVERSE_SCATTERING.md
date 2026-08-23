# Computer-assisted sign of the transverse scattering invariant

This note proves the one scalar inequality left by
`RESTRICTED_TRANSVERSE_SCATTERING.md`:

\[
\boxed{\mathscr W_\infty>{21\over50}>0.}
\tag{1}
\]

The calculation uses outward-rounded interval Taylor integration only on a
finite eccentric-anomaly interval.  Parabolic infinity is handled by explicit
analytic inequalities.

## Monotonicity of the centered launch family

The restricted centered solutions satisfy

\[
z''=-{2z\over(z^2+r^2/4)^{3/2}},\qquad z(0)=0,\quad z'(0)=v.
\tag{2}
\]

For $v\ge29/10$, they are strictly ordered in $v$ until a first turn.  To see
this, let $g=\partial_vz$.  Then

\[
g''=ag,\qquad g(0)=0,\quad g'(0)=1,
\qquad
a={4z^2-r^2/2\over(z^2+r^2/4)^{5/2}}.
\tag{3}
\]

On $0\le\theta\le1/5$, the eccentric-anomaly formula

\[
\theta={\psi+\sin\psi\cos\psi\over2},\qquad r=\cos^2\psi
\]

gives $\psi<1/4$ and hence $r>15/16$.  The exact maximum softened vertical
force then gives $|z''|<4$.  Consequently

\[
z(1/5)>{29\over50}-{2\over25}={1\over2},
\qquad z'(\theta)>0\quad(0\le\theta\le1/5).
\tag{4}
\]

At fixed $r$, the minimum of $a$ over $z\ge0$ is $-16/r^3$, so $a>-20$ on
this early interval. Sturm comparison with
$\sin(\sqrt{20}\theta)/\sqrt{20}$ shows $g>0$ there. This comparison is
applied in the standard first-zero bootstrap: before a hypothetical first
zero of either $z'$ or $g$, the preceding bounds hold and move that zero past
$1/5$. The Wronskian comparison also gives $g'(1/5)>0$, because
$\sqrt{20}/5<\pi/2$. By (4), $a>0$ after
$1/5$ as long as the orbit is outgoing: $r\le1$ and the increasing $z$ is
already greater than $1/2$. Thus $g''>0$, and both $g$ and $g'$ remain
positive. This proves the asserted launch-speed ordering.

It follows that once one launch escapes, every larger launch escapes. The
turning set is an initial open interval in this range, and its boundary is the
centered parabolic launch used below.

## A rigorous launch-speed bracket

For $z>0$, $w=z'>0$, put

\[
H_K={w^2\over2}-{2\over z}.
\]

The exact identity

\[
{dH_K\over dz}={2\over z^2}
\left[1-\left(1+{r^2\over4z^2}\right)^{-3/2}\right]
\tag{5}
\]

implies

\[
0\le H_K(\infty)-H_K(z)\le{1\over4z^3}
\tag{6}
\]

for every unturned outgoing orbit. Therefore $H_K>0$ certifies hyperbolic
escape, while $H_K+1/(4z^3)<0$ forces a later turn.

CAPD integration to the fixed endpoint $\psi=320\pi$ proves

\[
v={29051113\over10^7}:\quad H_K+{1\over4z^3}<0,
\]

and

\[
v={29051116\over10^7}:\quad H_K>0.
\]

For the upper launch, the verifier additionally encloses every accepted
Taylor step on $0\le\psi\le320\pi$ and proves $w>0$ on each complete step.
This path check rules out a prior outer turn and center recrossing; endpoint
positivity alone would not do so.

The lower certificate is sufficient: if that orbit turned before the
endpoint it is already in the turning set, while if it remained outgoing
then (6) forces a later turn. For the upper launch, the stepwise path
certificate followed by $H_K>0$ places it outside the first-turn set.
Monotonicity therefore gives the rigorous bracket

\[
\boxed{2.9051113<v_*<2.9051116.}
\tag{7}
\]

The exact hexadecimal output for the two decisive energy intervals is stored
in `data/restricted_transverse_scattering_capd_certificate.txt`.

## Analytic Jost enclosure at the finite endpoint

Let $k_+$ be the outgoing Jost field, $q=k_+/z$, and
$W_+=zk_+'-z'k_+$.  On the parabolic tail,

\[
z^2q'=W_+,\qquad
W_+'={3\over2}{r^2z^2\over d^5}q,\qquad
q(\infty)=1,\quad W_+(\infty)=0.
\tag{8}
\]

Equation (6) gives, for $z\ge K\ge1$,

\[
z'\ge\sqrt{7/2}\,z^{-1/2}.
\tag{9}
\]

Since the coefficient on the right of (8) is at most $(3/2)z^{-3}$,
the positive Volterra equation has operator norm at most

\[
L_K={1\over7K^2}.
\]

Consequently, at any endpoint with $z\ge K$,

\[
1\le q\le Q_K:={1\over1-L_K},\qquad
-{Q_K\over\sqrt{7/2}\,K^{3/2}}\le W_+\le0.
\tag{10}
\]

These formulas enclose the infinite Jost boundary without numerical
truncation.

## Finite interval propagation

Along the validated first-turn bracket (7), CAPD simultaneously integrates
(2) and
the two transverse fundamental solutions

\[
u(0)=1,\ u'(0)=0,\qquad v(0)=0,\ v'(0)=1
\tag{11}
\]

to $320\pi$. The endpoint satisfies $z>131$. The tail rectangle (10) is
applied only to the parabolic member proved to lie inside this propagated
launch box; the two bracketing endpoint orbits need not themselves be
parabolic. Applying (10) and

\[
k_+=zq,\qquad k_+'=z'q+{W_+\over z}
\tag{12}
\]

gives an interval box for the Jost state. The exact determinant of the
fundamental matrix is one, so inversion gives

\[
k_+(0)=v'k_+-v k_+',\qquad
k_+'(0)=-u'k_++u k_+'.
\tag{13}
\]

Outward-rounded interval evaluation proves the rational bounds

\[
\boxed{k_+(0)>{7\over20},\qquad k_+'(0)>{3\over5}.}
\tag{14}
\]

The half-line factorization
$\mathscr W_\infty=2k_+(0)k_+'(0)$ now proves (1).

## Validated rotation coefficient

The same finite propagation also encloses the order-$z$ coefficient in the
outgoing expansion

\[
p_-(z)=\gamma z-\mathscr W_\infty\sqrt z+o(\sqrt z).
\tag{15}
\]

At the center, evenness gives

\[
p_-(0)=-k_+(0),\qquad p_-'(0)=k_+'(0).
\tag{16}
\]

The already enclosed fundamental matrix therefore propagates $p_-$ to the
finite endpoint. Put $q=p_-/z$ and
$W=zp_-'-z'p_-$. Exactly,

\[
\gamma=q(L)+\int_L^\infty {W\over z^2}\,d\theta.
\tag{17}
\]

The radial energy bounds (5)--(6) sharpen the monopole integral to

\[
{1\over\sqrt K}\le
J_2:=\int_L^\infty {d\theta\over z^2}
\le {1\over\sqrt K}+{1\over40K^{5/2}}.
\tag{18}
\]

Indeed, write $\delta=-H_K$, so
$0\le\delta\le1/(4z^3)$ and
\[
 {1\over z'}={\sqrt z\over2}
 \left(1-{\delta z\over2}\right)^{-1/2}.
\]
Here $0\le x=\delta z/2\le1/(8z^2)\le1/8$, and the elementary inequality
$(1-x)^{-1/2}\le1+x$ on this interval gives
\[
 0\le J_2-K^{-1/2}
 \le {1\over16}\int_K^\infty z^{-7/2}\,dz
 ={1\over40K^{5/2}}.
\]

For completeness, let $Q=\sup|q|$ and $M=\sup|W|$ on the tail. From
$q'=W/z^2$, the Wronskian identity, and (9),

\[
Q\le |q(L)|+I_2M,
\qquad
M\le |W(L)|+{3\over2}I_3Q,
\tag{19}
\]

where

\[
I_2\le {2\over\sqrt{7/2}\sqrt K},
\qquad
I_3\le {2\over3\sqrt{7/2}K^{3/2}}.
\tag{20}
\]

The denominator $1-(3/2)I_2I_3$ is positive. Moreover

\[
|W(\theta)-\mathscr W_\infty|
\le {3\over2}I_3Q,
\tag{21}
\]

so replacing $W$ by $\mathscr W_\infty$ in (17) costs at most
$(3/2)I_2I_3Q$. Outward-rounded evaluation of (16)--(21) proves

\[
\boxed{-{1\over100}<\gamma<-{1\over250}<0.}
\tag{22}
\]

This is the sign needed at the parabolic endpoint of the compact second-
encounter map. It is not inferred from a decimal fit: both rational
inequalities are checked by the verifier.

## Reproduction and trusted base

The verifier is `src/verification/restricted_transverse_scattering_capd.cpp`.
It uses CAPD 6.1.0 at pinned commit
`731079217a9254ea2948d742df2b170895effe7f`, native outward-rounded intervals,
and `-frounding-math`. Reproduce with:

```bash
bash scripts/run_capd_restricted_transverse_scattering.sh \
  /path/to/CAPD /path/to/CAPD/build-native
```

The wrapper rejects the wrong CAPD commit, tracked CAPD source modifications,
untracked non-ignored CAPD files, a non-native interval build, or missing
rounding flags. The trusted computing base is the verifier source, the
wrapper, the pinned CAPD source, the host compiler, and the analytic
inequalities (3)--(10) and (16)--(21).

Status of the monotonicity and tail lemmas: **PROVED ANALYTICALLY**.

Status of (7), (14), (22), and (1): **PROVED BY COMPUTER-ASSISTED ARGUMENT**.
