# Exact conjecture and conventions

## Labelled classical statement

Let positive integers satisfy (a^2+b^2=c^2).  Body (i) has mass
((m_1,m_2,m_3)=(a,b,c)), and

\[
q_1=(-c/2,0),\quad q_2=(c/2,0),\quad
q_3=((b^2-a^2)/(2c),ab/c),\qquad \dot q_i=0.
\]

Thus (r_{23}=a,r_{31}=b,r_{12}=c): every mass is the length of its
opposite side.  With (G=1), the equations are

\[
\ddot q_i=\sum_{j\ne i}m_j{q_j-q_i\over |q_j-q_i|^3}.
\]

The conjecture says that no such initial condition has a (T>0) for which
the solution is classical and collision-free on ([0,T]) and
(q_i(T)=q_i(0),\dot q_i(T)=0) for every **labelled** body.  A return only
after a rotation or label permutation does not qualify.  Neither does a
regularized continuation through collision.  A positive, however small,
minimum separation is an ordinary collision-free encounter.

## The two scaling laws

If (q_i(t)) solves the problem with masses (m_i), then

\[
\widetilde m_i=km_i,\qquad \widetilde q_i(t)=kq_i(t/k)
\]

obeys

\[
\ddot{\widetilde q}_i(t)=k^{-1}\ddot q_i(t/k)
=\sum_{j\ne i} km_j{k(q_j-q_i)\over k^3|q_j-q_i|^3}.
\]

It preserves collision-freeness and converts a period (T) to (kT);
the converse uses (1/k).  Hence a triple and every common integer multiple
are periodic simultaneously.  Dividing by (gcd(a,b,c)) reduces the
problem exactly to primitive triples.

This is not the fixed-mass Newtonian similarity
(q(t)\mapsto\lambda q(t/\lambda^{3/2})).  Under simultaneous mass--length
scaling, (U\mapsto kU), (I\mapsto k^3I), and
(U\sqrt I\mapsto k^{5/2}U\sqrt I).  The usual statement that
(U\sqrt I) is scale-invariant refers only to spatial scaling at fixed
masses.

## Rational normalization

For (u=s/r\in(0,1)\), set

\[
A={1-u^2\over1+u^2},\qquad B={2u\over1+u^2}.
\]

After simultaneous division of all masses and distances by (c), the
masses are ((A,B,1)), and

\[
q_1=(-1/2,0),\ q_2=(1/2,0),\
q_3=((B^2-A^2)/2,AB).
\]

Here (A^2+B^2=1), the three side lengths are (A,B,1), and
(|q_3|=1/2).

Write a rational (u=p/q) in lowest terms.  It gives the integer triple

\[
(q^2-p^2,2pq,q^2+p^2).
\]

Its common divisor is exactly (2) if (p,q) are both odd, and exactly
(1) otherwise.  Division by that number gives a primitive triple and does
not change the normalized problem.  Conversely, Euclid's theorem says that
each primitive triple, after ordering the legs, is obtained uniquely from
coprime (q>p>0) of opposite parity.  The inverse for this ordered family is
(u=b/(a+c)).  Therefore primitive Pythagorean problems and rational
(u\in(0,1)) represent exactly the same normalized initial conditions,
up to exchanging the legs.

Leg exchange is

\[
S(u)={1-u\over1+u},\qquad A(Su)=B(u),\quad B(Su)=A(u),\quad S^2u=u.
\]

It is realized dynamically by reflecting the (x)-axis convention and
exchanging labels 1 and 2, so it preserves labelled-period existence after
the corresponding relabelling.  Its fixed point is
(u=\sqrt2-1).  Thus (0<u\le\sqrt2-1) is a fundamental interval.  The
(3{:}4{:}5) condition is (u=1/2), or (u=1/3) after leg exchange.

## Second-brake lemma

**Lemma.**  A free-fall solution, before its first collision, generates a
collision-free labelled periodic solution if and only if there is a
(\tau>0) at which every inertial velocity vanishes.

**Proof.**  Uniqueness and time reversal give (q(-t)=q(t)) at the initial
brake.  If (dot q(\tau)=0), uniqueness applied at (\tau) gives
(q(\tau+s)=q(\tau-s)).  Reflecting the collision-free segment
([0,\tau]) therefore yields (q(2\tau)=q(0)) and
(dot q(2\tau)=0), and periodic continuation is classical and labelled.
Thus (2\tau) is a period; it need not be the minimal period unless
(\tau) is the first positive brake.  Conversely, for any labelled period
(T), periodicity and evenness imply
(q(T/2+s)=q(-T/2+s)=q(T/2-s)), so (dot q(T/2)=0).  ∎

## A globally valid reduced brake residual

Work in the center-of-mass frame.  On the collision-free configuration space
put the unweighted Jacobi vectors

\[
X=q_2-q_1,\qquad
Y=q_3-{m_1q_1+m_2q_2\over m_1+m_2}.
\]

Define the rotation-invariant Hopf coordinates

\[
h(X,Y)=\left({|X|^2-|Y|^2\over2},\ X\mathbin\cdot Y,\
X\mathbin\times Y\right)\in\mathbb R^3,
\]

and along the normalized solution define

\[
\mathcal B(u,t)={d\over dt}h(X(u,t),Y(u,t))\in\mathbb R^3.
\]

The three gradients of $h$ are mutually orthogonal and each has squared norm
$|X|^2+|Y|^2$.  Away from triple collision, $Dh$ has rank three and its
kernel is the common-rotation direction $(JX,JY)$.  Thus if every inertial
velocity vanishes then $\mathcal B=0$, while conversely $\mathcal B=0$
says that all relative velocities form one rigid rotation with angular speed
$\omega$.  Center-of-mass velocity is zero, and the conserved angular
momentum is

\[
L=\omega(\mu_{12}|X|^2+\mu_{3,12}|Y|^2).
\]

The coefficient is positive away from triple collision.  Since $L=0$
initially, $\omega=0$, so every labelled inertial velocity is zero.  This
equivalence remains valid at syzygy.  Merely
using the three mutual-distance derivatives would fail there because a
transverse velocity can leave all three first derivatives zero at a collinear
configuration.

The conjecture is consequently the exact assertion

\[
\mathcal B(u,t)\ne0
\]

for every rational $u\in(0,1)$ and every positive time in the maximal
collision-free flow.  The strong real conjecture replaces “rational” by
“real.”
