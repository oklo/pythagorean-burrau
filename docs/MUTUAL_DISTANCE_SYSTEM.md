# Squared mutual-distance equations

Put

\[
x=r_{23}^2,\qquad y=r_{31}^2,\qquad z=r_{12}^2.
\]

Direct dot products of the relative Newton equations give, away from collision,

\[
\begin{aligned}
\ddot x={}&2|v_2-v_3|^2-{2(m_2+m_3)\over\sqrt x}\\
&-m_1\left[{x+z-y\over z^{3/2}}+{x+y-z\over y^{3/2}}\right],\\
\ddot y={}&2|v_3-v_1|^2-{2(m_3+m_1)\over\sqrt y}\\
&-m_2\left[{y+x-z\over x^{3/2}}+{y+z-x\over z^{3/2}}\right],\\
\ddot z={}&2|v_1-v_2|^2-{2(m_1+m_2)\over\sqrt z}\\
&-m_3\left[{z+y-x\over y^{3/2}}+{z+x-y\over x^{3/2}}\right].
\end{aligned}
\]

The velocity-square terms show why the three distances alone do not form a
closed second-order system without additional shape-velocity data.  At the
normalized brake, $(m_1,m_2,m_3)=(A,B,1)$ and
$(x,y,z)=(A^2,B^2,1)$, hence

\[
\ddot x(0)=-{2(B+1)\over A}-2A^3,
\]

\[
\ddot y(0)=-{2(A+1)\over B}-2B^3,
\qquad
\ddot z(0)=-2\left(A+B+{1\over A}+{1\over B}\right).
\]

Their combination $\ddot D=\ddot z-\ddot x-\ddot y$ gives the defect identity
in `EXACT_REDUCTIONS.md`.  The equations are exact but have not yielded an
invariant region; ordinary numerics explicitly falsify the simplest proposed
$D>0$ cone.

