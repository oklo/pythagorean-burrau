# Brake-map structural route

The globally safe residual remains the Hopf derivative in `CONJECTURE.md`.
Away from a zero Jacobi vector, a useful local factorization separates two
radial conditions from one angular condition.

Choose any Jacobi tree with nonzero vectors $X,Y$ and set

\[
R_1=X\mathbin\cdot\dot X,\qquad
R_2=Y\mathbin\cdot\dot Y,
\]

\[
S={X\mathbin\times\dot X\over|X|^2}
-{Y\mathbin\times\dot Y\over|Y|^2}.
\]

If $R_1=R_2=0$, then $\dot X=\omega_XJX$ and
$\dot Y=\omega_YJY$.  The equation $S=0$ makes the two angular rates equal.
Zero total angular momentum then forces the common rate to vanish.  Hence

\[
(R_1,R_2,S)=0
\quad\Longleftrightarrow\quad
\hbox{a labelled inertial brake}
\]

on that chart.  A different Jacobi tree must cover $Y=0$; $X=0$ is a binary
collision.  This chart condition and the Hopf condition agree on overlaps.

## Double-radial event reduction

A double-radial event is a zero of

\[
(u,t)\longmapsto(R_1(u,t),R_2(u,t)).
\]

Whenever its two-by-two Jacobian is nonsingular, it is an isolated event in
the $(u,t)$ plane.  The full conjecture then asks whether the remaining scalar
$S$ can vanish at any such event.  This isolates the overdetermined structure
without invoking genericity as proof.

The unresolved global tasks are substantial: classify all regular event
branches, cover singular double-radial zeros, change Jacobi charts at vector
degeneracy, and control events entering from collision, escape, infinite time,
or either parameter endpoint.

## Falsification results

An ordinary-numerical scan found many isolated double-radial events and angular
slips of both signs.  Therefore the tempting assertion “$S$ has one fixed sign
at every double-radial event” is false.  One representative event is

\[
u\approx0.29287740,\qquad t\approx1.34359722,\qquad
S\approx-0.0562133,
\]

which is clearly not a brake despite both radial rates vanishing numerically.
Other event slips ranged over both signs (examples include approximately
$+0.794,+0.414,-0.670,+0.166,-0.824,+1.437,-1.336$).  Evidence level:
ORDINARY NUMERICAL EVIDENCE.

The primary route is now an event-classification or index theorem, not a
universal sign theorem.

