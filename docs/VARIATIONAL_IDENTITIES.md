# Variational and integral identities for a hypothetical second brake

These identities are necessary conditions, not contradictions.

Let the normalized energy be $H=-U_0$ and suppose a collision-free second
brake occurs at time $\tau$.  On $[0,\tau]$, both endpoint velocities vanish.

## Lagrange--Jacobi and virial identities

With

\[
I=\sum_i m_i|q_i-q_{CM}|^2,
\]

homogeneity of the Newton potential gives

\[
\ddot I=4K-2U=4H+2U=2U-4U_0.
\]

Every brake on this energy surface satisfies $U=U_0$ and

\[
\ddot I=-2U_0<0.
\]

Thus every brake is a strict local maximum of $I$ in physical time.  Since
$\dot I(0)=\dot I(\tau)=0$, integration on the brake segment yields

\[
\int_0^\tau U\,dt=2U_0\tau,
\qquad
\int_0^\tau K\,dt=U_0\tau.
\]

Doubling gives the usual periodic virial averages
$\langle U\rangle=2U_0$ and $\langle K\rangle=U_0$.  Consequently the
Lagrangian action and abbreviated action over a full period $T=2\tau$ obey

\[
\int_0^T(K+U)dt=3U_0T,
\qquad
\oint p\,dq=\int_0^T2Kdt=2U_0T.
\]

These values are compatible with known periodic brake orbits and alone yield
no contradiction.

## Integrated labelled force balance

The two brake endpoints imply, for each labelled body,

\[
0=\dot q_i(\tau)-\dot q_i(0)
=\int_0^\tau\sum_{j\ne i}m_j{q_j-q_i\over r_{ij}^3}\,dt.
\]

Thus each body's time-integrated gravitational acceleration must vanish.  On
the full doubled period, $\int_0^T\dot q_i,dt=0$ also follows from labelled
position return.

Multiplying the mass equations by the fixed initial positions, summing labels,
and pairing forces gives the scalar condition

\[
\boxed{
\int_0^\tau\sum_{i<j}m_im_j
{d_{ij}(0)\mathbin\cdot d_{ij}(t)\over r_{ij}(t)^3}\,dt=0,
}
\]

where $d_{ij}=q_j-q_i$.  In normalized Pythagorean data the three initial
vectors can be taken as

\[
d_{12}(0)=(1,0),\quad
d_{13}(0)=(B^2,AB),\quad
d_{23}(0)=(-A^2,AB),
\]

with pair weights $AB,A,B$, respectively.  The integrand is positive at
$t=0$, so a hypothetical second-brake segment must later accumulate enough
negative projection.  No invariant half-plane controlling all three current
pair vectors is known, and close encounters defeat naive projection bounds.

## Jacobi--Maupertuis chord

On the energy surface $H=-U_0$, the Hill region is $U\ge U_0$.  Away from its
boundary and collisions, physical trajectories reparametrize as geodesics of

\[
ds_{JM}^2=2(U-U_0)\,ds_m^2,
\]

where $ds_m^2=\sum_i m_i|dq_i|^2$ on the center-of-mass quotient.  A brake
point lies on the degenerate boundary $U=U_0$.  Its physical acceleration is
the mass-metric normal $M^{-1}\nabla U$, so a brake-to-brake solution is a
degenerate-boundary geodesic chord doubled by time reversal.

The missing variational theorem would have to exclude the chord launched from
the explicit Pythagorean curve, for example through a conjugate-point, Morse
index, or convex-separation argument that remains valid near binary collision.
No such global result is claimed here.

