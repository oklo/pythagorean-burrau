# Uniform outgoing angular momentum

This note replaces the nonuniform Cartesian turn velocity by a scalar whose
leading coefficient does not shrink with the turn height. It treats a
sequence of exact skinny trajectories whose restricted intercept tends to
the centered parabolic phase through the finite-turn side.

## Normalized scalar

In late variables define the outer angular momentum quotient

\[
 \Lambda_B={Z\times Z'\over B}.
\tag{1}
\]

Since $Y=BZ$ and physical time is
$t=t_{\rm mono}+B^{3/2}\theta$,

\[
 {Y\times\dot Y\over B^{3/2}}=\Lambda_B.
\tag{2}
\]

For the first transverse restricted field $p=-2\xi$,

\[
 \xi z'-z\xi'={1\over2}(zp'-z'p)={W\over2}.
\tag{3}
\]

Thus Theorem 3 of FIRST_ORDER_INCOMING_MATCHING.md gives, on every fixed
outgoing section $z=K$,

\[
 \Lambda_B(K)\longrightarrow {W(K)\over2}
\tag{4}
\]

uniformly in intercept.

## Exact torque and the tail gain

The exact late outer equation gives

\[
 \boxed{
 \Lambda_B'
 =-{NA\over BM^2}(Z\times R)
 \left(
 |Z+R/M|^{-3}-|Z-AR/M|^{-3}
 \right).
 }
\tag{5}
\]

The two squared denominators differ by

\[
 |Z+R/M|^2-|Z-AR/M|^2
 =2Z\cdot R+{B^2\over M^2}|R|^2.
\tag{6}
\]

Consequently, on a bounded LC binary tube and $Y=|Z|\ge K$,

\[
 |\Lambda_B'|
 \le {C\over B}Y^{-4}
 \left(|Z\cdot R|+B^2\right).
\tag{7}
\]

The missing factor $B$ in (7) comes from near perpendicularity. At the fixed
outgoing section, first-order matching gives

\[
 {|Z_x|\over Y}=O(B),\qquad
 |\mathcal N_B|=o(1),
\tag{8}
\]

where $\mathcal N_B=(\mathcal L_B,\mathcal K_B)/B$ are the smooth binary LC
transverse normals. The following tail bootstrap is collision-safe:

\[
\begin{aligned}
 \sup {|\widehat Z_x|\over B}
 &\le C+C\int_K^{Y_{\rm t}}{|\Lambda_B|\over Y^2}\,d\theta,\\
 \sup|\mathcal N_B|
 &\le o(1)+CB\int_K^{Y_{\rm t}}Y^{-3}
       \bigl(1+\sup|\widehat Z_x|/B+\sup|\mathcal N_B|\bigr)\,d\theta,\\
 \sup|E_B+1|
 &\le o(1)+CB\int_K^{Y_{\rm t}}Y^{-3}\,d\theta,\\
 \sup|\Lambda_B|
 &\le C+C\int_K^{Y_{\rm t}}Y^{-3}
       \bigl(1+\sup|\widehat Z_x|/B+\sup|\mathcal N_B|\bigr)\,d\theta .
\end{aligned}
\tag{9}
\]

Here $\widehat Z_x$ is the angular deviation from the fixed vertical axis.
The first line is the exact direction identity
$|d\widehat Z/d\theta|=B|\Lambda_B|/Y^2$. For the second, use the exact
coefficient (31a) of the first-order incoming proof in angular form:
$|Z_x|/(BY)=O(|\widehat Z_x|/B)$ and $|R_y|/B=O(|\mathcal N_B|)$ give a
divided LC-normal increment $CBY^{-3}$ times the displayed bootstrap factor.
This sharper form avoids replacing $|h_B|=O(Y)$ by an unnecessary
$Y$-loss. Complete blocks are summed by physical time and the two endpoint
blocks remain separate. The added energy line is the exact LC identity
$E_s=O(BY^{-3})$; together with the endpoint contributions $O(BK^{-3})$ it
keeps the binary in the bounded oscillator tube assumed in (7). The last
line is (7) with

\[
 |Z\cdot R|\le CBY
 \bigl(1+|\widehat Z_x|/B+|\mathcal N_B|\bigr).
\tag{10}
\]

No physical binary velocity occurs.

The turn-based radial comparison can be made without dividing by the radial
velocity. The exact dipole cancellation and the polar identity give

\[
 Y''=-{N\over Y^2}
 +O\!\left(Y^{-4}+{B^2\Lambda_B^2\over Y^3}\right).
\tag{10a}
\]

Inside fixed bootstrap bounds for $\Lambda_B$ and the LC binary energy,
choose $K$ large and then $B$ small. On the whole outgoing tail,

\[
 -{C\over Y^2}\le Y''\le-{c\over Y^2}<0.
\tag{10b}
\]

Before the first radial turn $Y'>0$. On $K\le Y\le\eta Y_{\rm t}$, multiply
the upper inequality in (10b) by $dY$ and integrate to the turn; this gives
$Y'^2\ge c_\eta/Y$. On the terminal region
$\eta Y_{\rm t}\le Y\le Y_{\rm t}$, integrate
$Y''\le-c/Y_{\rm t}^2$ backward from $Y'(T_B)=0$. The time spent there is at
most $CY_{\rm t}^{3/2}$. Splitting the two regions yields

\[
 \int_K^{T_B}Y^{-2}\,d\theta\le CK^{-1/2},\qquad
 \int_K^{T_B}Y^{-3}\,d\theta\le CK^{-3/2},
\tag{11}
\]

uniformly in the turn height. Choose $K$ large. Equations (9)--(11) close by
the open-and-closed argument and give

\[
 \boxed{
 |\Lambda_B(T_B)-\Lambda_B(K)|\le CK^{-3/2}.
 }
\tag{12}
\]

The constants are uniform in $B$, the intercept, the number of prescribed
binary collisions, and the first-turn height.

## Uniform first-turn theorem

Let $B_j\to0$, let the exact incoming intercepts tend to the centered
parabolic phase through the finite-turn side, and suppose the exact solutions
reach first outer radial turns $T_{B_j}$ after passing a fixed outgoing
section. In fact $Y_{{\rm t},j}\to\infty$: for any fixed $K$, the centered
restricted separatrix and all sufficiently nearby finite-turn restricted
orbits cross $z=K$ outward, and fixed-segment convergence makes the exact
finite-$B_j$ trajectory cross the same section outward for all sufficiently
large $j$. It therefore cannot have had its first radial turn below $K$.
Equations (4) and (12), first with this fixed $K$, then $j\to\infty$, and
finally $K\to\infty$, give

\[
 \boxed{
 \Lambda_{B_j}(T_{B_j})\longrightarrow{\mathscr W_\infty\over2}.
 }
\tag{13}
\]

Since $\mathscr W_\infty>21/50$, (2) and (13) exclude a full labelled brake at
that first turn. The coefficient is independent of the turn height. More
precisely, if $\mathcal R_B=|Y(T_B)|=BY_{\rm t}$ is the physical turn radius,
the exact radial-turn identity and the direction bootstrap give

\[
 \dot Y_x=-{B^{3/2}\over\mathcal R_B}
 \left({\mathscr W_\infty\over2}+o(1)\right).
\tag{14}
\]

Status of (1)--(7): **EXACT SYMBOLIC IDENTITY** or direct exact consequence
of the late Jacobi equations. Status of (8): **PROVED ANALYTICALLY** by the
first-order incoming theorem. Status of the bootstrap (9)--(12) and hence
(13): **PROVED ANALYTICALLY**. The proof is uniform in the first-turn height
and in the number and phase of binary LC blocks; it assumes the light body
stays separate until the turn. Near-collision binary passages are covered
only in LC variables, and a prior classical collision remains an immediate
nonperiodic alternative.
