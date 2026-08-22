# A finite transversality criterion for the restricted separatrix

The parabolic-manifold crossing in the rectilinear restricted limit can be
reduced to a scalar Jacobi field over a finite regularized half-cycle. This
does not yet prove transversality, but it removes the infinite-time numerical
tail from the decisive sign test.

## An explicit speed bracket

Let $r(\theta)$ be the collision--ejection binary with
\[
r(0)=1,\qquad r'(0)=0,\qquad r''=-{2\over r^2},
\]
and let $z$ be the symmetric parabolic separatrix,
\[
z''=-{2z\over(z^2+r^2/4)^{3/2}},\qquad
z(0)=0,\quad z'(0)=v_*.
\]
Its first regularized binary collision is at $\theta_c=\pi/4$.

**Lemma.** The launch speed satisfies
\[
\boxed{\sqrt8<v_*<4.}
\tag{1}
\]

**Proof.** Since $0\le r\le1$, while $z,z'>0$ the comparison energy
\[
E_1={1\over2}z'^2-{2\over\sqrt{z^2+1/4}}
\]
is nonincreasing. If $v\le\sqrt8$, it starts nonpositive and becomes
strictly negative once $z>0$ and $r<1$. Such a trajectory cannot tend to
infinity with zero speed; if it remained bounded and monotone, its acceleration
would be bounded above by a negative constant and force a turn. Hence every
$v\le\sqrt8$ turns, proving the lower bound.

For the upper bound, write
\[
r=\cos^2\psi,\qquad
\theta={\psi+\sin\psi\cos\psi\over2}.
\]
On $0\le\theta\le\pi/8$, one has $\psi<\pi/6$ and therefore $r>3/4$.
For fixed $r$, the vertical force magnitude has the exact maximum
\[
\max_{z\ge0}{2z\over(z^2+r^2/4)^{3/2}}
={16\over3\sqrt3\,r^2}<6.
\]
Using $\sqrt3>19/11$, the rational bound
$16/(3\sqrt3 r^2)<11/2$ holds on the same interval. Launch speed $4$ satisfies,
at $\theta=7/20<\pi/8$,
\[
z>{1701\over1600}>1,\qquad z'>{83\over40}>2.
\]
At the earlier first $z=1$ section,
$z'^2/2-2/z>0$. Thereafter this radial comparison energy is
nondecreasing because $z''\ge-2/z^2$. Thus speed $4$ escapes with positive
limiting speed, so the boundary speed $v_*$ is smaller than $4$. \(\square\)

## The phase Jacobi field

Along the centered separatrix put
\[
d^2=z^2+{r^2\over4},\qquad
a={4z^2-r^2/2\over d^5},\qquad
b={3zr\over2d^5}.
\]
Differentiating the light-particle equation in time gives
\[
z'''=az'+br'.
\tag{2}
\]
Let $h$ be the even homogeneous Jacobi field
\[
h''=ah,\qquad h(0)=v_*,\qquad h'(0)=0.
\tag{3}
\]
It is the homogeneous correction separating the global time-translation field
$z'$ from a phase variation pinned at the $z=0$ section.

**Lemma.** The field $h$ is strictly positive through the first binary
collision. Moreover $a>0$ for every $\theta\ge\pi/8$ along the outgoing
separatrix.

**Proof.** Define
\[
W=h z''-h'z'.
\]
Equations (2)--(3) give the exact identity
\[
W'=hbr'.
\tag{4}
\]
During the first contraction, $z>0$, $z'>0$, $b>0$, and $r'<0$. If $h$
were to have a first zero, then before that zero $W'<0$ and $W(0)=0$.
Consequently
\[
\left({h\over z'}\right)'=-{W\over z'^2}>0,
\]
contradicting $h/z'=1$ initially and $h=0$ at the proposed first zero.

It remains to locate the sign change of $a$. On $[0,\pi/8]$, the force bound
used above and $v_*>\sqrt8$ imply
\[
z(\pi/8)>
{\pi\sqrt2\over4}-{2\pi^2\over27\sqrt3}
>{1\over2\sqrt2}.
\tag{5}
\]
For a purely rational verification of the last inequality, use
$3<\pi<22/7$, $\sqrt2>7/5$, and $\sqrt3>5/3$; the left side is then greater
than $5389/8820>5/14>1/(2\sqrt2)$. Since $z$ thereafter increases and
$r\le1$, (5) gives $4z^2-r^2/2>0$. \(\square\)

## Finite sign theorem

The preceding lemmas yield the following sufficient condition:
\[
\boxed{h'(\theta_c)>0.}
\tag{6}
\]
Indeed, $h(\theta_c)>0$ and $a>0$ thereafter. If (6) holds, then both $h$
and $h'$ remain positive and $h$ grows.

The finite sign is now validated on a larger interval than necessary. In
eccentric anomaly $r=\cos^2\psi$, $d\theta=r\,d\psi$, normalize $q=h/v$ and
put $p=dq/d\theta$. CAPD interval Taylor integration on 256 overlapping
velocity slabs proves
\[
p(\pi/2)>\frac1{125}
\qquad\hbox{for every }v\in[14/5,4].
\tag{7}
\]
Since $14/5<\sqrt8<v_*<4$, this gives the rigorous bound
\[
\boxed{h'(\theta_c)>\frac{14}{625}>0.}
\tag{8}
\]
The equations, source pin, enclosure output, and reproduction commands are in
`COMPUTER_ASSISTED_TRANSVERSALITY.md`.

Status of (1), the Wronskian positivity lemma, and the growth implication from
(6): **PROVED ANALYTICALLY**. Status of (7)--(8): **PROVED BY
COMPUTER-ASSISTED ARGUMENT**. The analytic compactification, verification of
McGehee's sector hypotheses, and tangent-contraction contradiction are proved
in `PARABOLIC_MANIFOLD.md`. Together they give
\[
\boxed{V_u'(0)-V_s'(0)\ne0.}
\]
Thus restricted transversality is **PROVED BY COMPUTER-ASSISTED ARGUMENT**.
