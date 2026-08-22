# Universal zero-angular-momentum reduced system

Use unweighted Jacobi vectors

\[
x=q_2-q_1,\qquad
y=q_3-{m_1q_1+m_2q_2\over m_1+m_2}.
\]

In the center-of-mass frame their reduced masses are

\[
\mu_1={m_1m_2\over m_1+m_2},\qquad
\mu_2={m_3(m_1+m_2)\over m_1+m_2+m_3},
\]

and (K=(\mu_1|\dot x|^2+\mu_2|\dot y|^2)/2).  Before any 1--2
binary collision, rotate uniquely so that

\[
x=(R,0),\qquad y=(X,Y),\qquad R>0.
\]

If (\omega) is the eliminated frame angular velocity, the angular momentum
equation is

\[
0=L=I\omega+\mu_2(X\dot Y-Y\dot X),\qquad
I=\mu_1R^2+\mu_2(X^2+Y^2).
\]

Routh reduction at (L=0) gives

\[
K_{red}={\mu_1\dot R^2+\mu_2(\dot X^2+\dot Y^2)\over2}
-{\mu_2^2(X\dot Y-Y\dot X)^2\over2I}.
\]

The positive potential magnitude is

\[
U={m_1m_2\over R}
+{m_1m_3\over\sqrt{(X+{m_2\over m_1+m_2}R)^2+Y^2}}
+{m_2m_3\over\sqrt{(X-{m_1\over m_1+m_2}R)^2+Y^2}}.
\]

Thus the zero-momentum reduced Lagrangian is (K_{red}+U), with energy
(H=K_{red}-U).  All mass coefficients are rational functions of the Euclid
parameter after ((m_1,m_2,m_3)=(A(u),B(u),1)).  Mass-weighting the two
Jacobi vectors turns the unreduced kinetic metric Euclidean but introduces
square roots of those same rational coefficients; the unweighted form is more
convenient for exact arithmetic.

The Pythagorean brake curve is explicitly

\[
\Gamma(u):\quad
R=1,\quad X={AB(B-A)\over A+B},\quad Y=AB,\quad
\dot R=\dot X=\dot Y=0.
\]

On this curve (I=AB), (U=U_0=AB+(AB)^{-1}), and (K_{red}=0).
At the fixed energy (H(u)=-U_0(u)), the Hill region is (U\ge U_0), and
the brake boundary is (U=U_0).  Hence (\Gamma) is an explicit algebraic
curve on the varying-mass brake boundary.

Size can be separated by (\rho=\sqrt I) and a point on the mass-metric unit
shape sphere.  Homogeneity gives (U=V(\text{shape})/\rho).  This is the
starting point for the Jacobi--Maupertuis and brake-to-syzygy programs; no
global nonreturn theorem has yet been obtained from it.

