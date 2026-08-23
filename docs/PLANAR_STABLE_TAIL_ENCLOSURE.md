# Analytic enclosure of the planar stable tail

This note turns the exact quartic stable-manifold jet into a rigorous tail
box for the collision shooting problem. No floating-point or interval ODE
claim is used.

## Weighted analytic space

At the lower equilateral rest point write

\[
 w=e_-+(x,q),\qquad
 a_T={1+\sqrt7\over6},\qquad
 a_L={1+\sqrt{19}\over6}.
\]

Use stable parameters $p,\nu$ with linear flow

\[
 p_\zeta=-a_Tp,\qquad \nu_\zeta=-a_L\nu,
\]

and define

\[
 \mathcal D=-a_Tp\partial_p-a_L\nu\partial_\nu.
\]

An invariant position parameterization $P=(x,q)$ obeys

\[
 \mathcal D^2P+{1\over3}\mathcal DP
 =\nabla W(e_-+P).
\tag{1}
\]

For a vector power series $F=\sum F_{ij}p^i\nu^j$, put

\[
 \|F\|_{r_T,r_L}
 =\sum_{i,j}\bigl(|F^x_{ij}|+|F^q_{ij}|\bigr)r_T^ir_L^j.
\tag{2}
\]

This is a Banach-algebra majorant norm. Let $P_4$ be the exact degree-four
polynomial in (17c)--(17f) of `PLANAR_JOINT_SHAPE_DYNAMICS.md`.

## Tail-enclosure theorem

**Theorem.** There is a unique normalized solution of (1), analytic on the
interior and represented by an absolutely convergent power series on the
closure of

\[
 \mathscr P=\left\{|p|\le {1\over200},\quad
                       |\nu|\le {1\over2500}\right\}
\]

of the form

\[
 P=P_4+E,
\]

where $E$ contains only monomials of total degree at least five and

\[
 \boxed{\|E\|_{1/200,1/2500}< {1\over125000000}.}
\tag{3}
\]

On the half polydisc,

\[
 \boxed{
\|E\|_{1/400,1/5000}< {1\over4000000000},\qquad
\|\mathcal DE\|_{1/400,1/5000}< {1\over800000000}.}
\tag{4}
\]

For every $5/4\le\kappa\le13/10$ and $\zeta\ge10$, the normalized real tail

\[
 p=-e^{-a_T\zeta},\qquad
 \nu=\kappa e^{-a_L\zeta}
\tag{5}
\]

lies in that half polydisc. Thus (4) is a rigorous enclosure of both shape
position and logarithmic shape velocity used to initialize the forced-LC
collision shoot.

At fixed $\zeta$, $\partial_\kappa=(\nu/\kappa)\partial_\nu$. Since
$\kappa\ge5/4$, the same estimate also gives

\[
 \boxed{
 \|\partial_\kappa E\|< {1\over1000000000},\qquad
 \|\partial_\kappa\mathcal DE\|< {1\over200000000}.}
\tag{4a}
\]

Thus the initial parameter tangent needed for the collision determinant is
enclosed as well.

## Homological inverse

The Hessian at $e_-$ is

\[
 H=\operatorname{diag}(1/6,1/2).
\]

On a monomial $p^i\nu^j$, let
$\lambda=ia_T+ja_L$. The two homological divisors are

\[
 d_T(\lambda)=\lambda^2-\lambda/3-1/6,
 \qquad
 d_L(\lambda)=\lambda^2-\lambda/3-1/2.
\]

For $i+j\ge2$, $\lambda\ge2a_T$, both divisors are increasing, and

\[
 d_T(\lambda)>d_L(\lambda)\ge d_L(2a_T)
 ={5+2\sqrt7\over18}>{17\over30}.
\tag{6}
\]

Consequently the coefficientwise inverse $\mathcal H^{-1}$ of

\[
 \mathcal H=\mathcal D^2+{1\over3}\mathcal D-H
\]

has norm less than $30/17$ on series of degree at least two.

## Exact residual majorant

The twelve algebraic coefficients of $P_4$, in the order used in the symbolic
regression test, have the strict rational absolute bounds

\[
 {1\over10},{13\over100},{11\over100},{1\over10},{1\over5},
 {29\over100},{3\over250},{1\over4},{1\over4},{2\over25},
 {47\over100},{11\over500}.
\tag{7}
\]

Dilate the radii of $\mathscr P$ by $80$. Then

\[
 |p|\le {2\over5},\qquad |\nu|\le {4\over125}.
\]

The coefficient majorants (7) give

\[
 \|P_4^x\|<{41\over100},\qquad
 \|P_4^q\|<{3\over50}.
\tag{8}
\]

For either primary-distance square, write

\[
 r_\pm^2=1+s_\pm,
 \qquad
 s_\pm=x^2+q^2\pm x-\sqrt3q.
\]

Using $\sqrt3<2$, (8) gives

\[
 \|s_\pm\|
 <{41^2\over100^2}+{3^2\over50^2}+{41\over100}
   +2{3\over50}
 ={7017\over10000}<{3\over4}.
\tag{9}
\]

Therefore the absolute binomial series for $(1+s_\pm)^{-3/2}$ has norm less
than $8$. Since $a_L<1$, the norm of
$(\mathcal D^2+\mathcal D/3)P_4$ is less than
$18(41/100+3/50)$. The two components of $\nabla W(e_-+P_4)$ are bounded by

\[
 {2(41/100)+16(41/100+1/2)\over9},
 \qquad 2(1+3/50),
\]

respectively. Hence the exact residual

\[
 \mathscr R_4=
 \mathcal D^2P_4+{1\over3}\mathcal DP_4-\nabla W(e_-+P_4)
\]

has norm less than $13$ on the dilated polydisc. Exact symbolic substitution
proves that its terms of degree zero through four vanish. Cauchy scaling then
gives

\[
 \boxed{
 \|\mathscr R_4\|_{1/200,1/2500}
 <{13\over80^5}.}
\tag{10}
\]

## Contraction estimate

The bounds (7) at the undilated radii give

\[
 \|P_4\|_{1/200,1/2500}<0.005404
 <R:={271\over50000}.
\tag{11}
\]

For $\|P\|\le R$, one has
$R^2+2R<1/80$. Put $f(s)=(1+s)^{-3/2}$. Exact rational inequalities imply

\[
 \|f'\|<2,\qquad \|f''\|<4.
\tag{12}
\]

Indeed, after squaring the positive quantities, (12) follows from

\[
 {9\over16}\left({80\over79}\right)^5<1,
 \qquad
 {225\over256}\left({80\over79}\right)^7<1.
\]

For a primary term $Vf(s)$, the product rule gives the second derivative
majorant

\[
 2\|f'\|\|Ds\|
 +(\|V\|)\bigl(\|f''\|\|Ds\|^2+\|f'\|\|D^2s\|\bigr).
\]

Here $\|Ds\|<2.03$, $\|D^2s\|\le2$, and $\|V\|<1.51$. Including both
primaries and the factor $1/9$ proves the convenient strict bound

\[
 \|D^2(\nabla W)\|<9.
\tag{13}
\]

Writing

\[
 N(P)=\nabla W(e_-+P)-HP,
\]

one has $DN(0)=0$, so (13) makes $N$ Lipschitz on the radius-$R$ ball with
constant less than $9R$. Combining with (6), the fixed-point map for $E$ has
contraction factor

\[
 q_*<{30\over17}\,9R={7317\over85000}<{1\over10}.
\tag{14}
\]

More explicitly, let $\mathcal A_{\ge5}$ be the closed subspace of the
weighted series space consisting of terms of total degree at least five, and
put

\[
 \mathcal T(E)=\mathcal H^{-1}
 \left[N(P_4+E)-N(P_4)-\mathscr R_4\right].
\tag{15}
\]

This subspace is invariant: $\mathscr R_4$ starts in degree five, and
$DN(0)=0$ makes $N(P_4+E)-N(P_4)$ start in degree at least six whenever
$E\in\mathcal A_{\ge5}$. The exact coefficient majorant used in (11) also
gives

\[
 \|P_4\|+{1\over125000000}<0.005404008<R,
\tag{16}
\]

so the whole correction ball lies inside the nonlinear-majorant ball.

Equations (6), (10), and (14) give

\[
 {30\over17}{10\over9}{13\over80^5}
 ={13\over1671168000}<{1\over125000000}.
\]

Thus the contraction maps the ball asserted in (3) strictly into itself and
proves existence and uniqueness in this bounded normalized class. Recursive
homological coefficient uniqueness, followed by the identity theorem, agrees
with the usual unique local stable-manifold parameterization. Since $E$
starts in degree five, restriction
to half radii multiplies its norm by at most $2^{-5}$, proving the first part
of (4). Applying $\mathcal D$ introduces a factor no larger than the total
degree; $n/2^n\le5/32$ for $n\ge5$, proving the second part.

For (4a), $\nu\partial_\nu$ introduces at most the same factor $n$, while
$\nu\partial_\nu\mathcal D$ introduces at most $n^2$.
Since $n^2/2^n\le25/32$ for $n\ge5$ and $1/\kappa\le4/5$, (4a) follows from
the radius $1/125000000$ in (3).

Finally, $\sqrt7>13/5$ gives $10a_T>6$, and the degree-13 Taylor lower bound
for $e^6$ is greater than $400$. Likewise $\sqrt{19}>13/3$ gives
$10a_L>80/9$, whose degree-13 exponential Taylor lower bound is greater than
$6500$. These exact rational inequalities prove (5).

## Status and scope

The tail enclosure (3)--(5) is **PROVED ANALYTICALLY**, with all algebraic and
rational inequalities covered by exact symbolic regression tests. It does
not validate the subsequent finite flow or the collision zero. It removes the
stable-manifold truncation from that validation problem: the remaining task
is a finite interval propagation from the explicit state box (4), followed by
interval Newton in $(\kappa,\sigma)$.
