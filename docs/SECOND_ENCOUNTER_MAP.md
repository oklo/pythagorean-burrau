# The compact second-encounter map

The uniform first-turn theorem and its returning-tail corollary reduce the
next skinny obstruction to one compact collision-regularized encounter. This
note fixes the signs, proves the centered parabolic endpoint is strictly
positive, and records a bounded numerical probe of the remaining phases.

## Returning asymptotic state

For the centered first encounter, write

\[
 p_-(z)=\gamma z-\mathscr W_\infty\sqrt z+o(\sqrt z)
 \qquad(z\to+\infty).
\tag{1}
\]

Here

\[
 \gamma=\lim_{z\to+\infty}{p_-\over z},\qquad
 \mathscr W_\infty>0.
\tag{2}
\]

The order-$z$ term is a rotation mode on the long outer Kepler excursion and
returns unchanged. The collision-scattering $\sqrt z$ mode changes sign
between the outgoing and incoming legs. Thus, at the same positive outer
section on the return,

\[
 p_{\rm ret}(z)=\gamma z+\mathscr W_\infty\sqrt z+o(\sqrt z).
\tag{3}
\]

To reuse the standard left-to-right restricted equations, put
$\widetilde z=-z$. Then the return starts at $\widetilde z=-\infty$ with

\[
 p_{\rm ret}
 =-\gamma\widetilde z+\mathscr W_\infty\sqrt{-\widetilde z}
 +o(\sqrt{-\widetilde z}),
\tag{4}
\]

and

\[
 \widetilde W
 =\widetilde z p_{\rm ret}'-\widetilde z'p_{\rm ret}
 \longrightarrow-\mathscr W_\infty.
\tag{5}
\]

The physical outer angular momentum has the opposite sign convention after
the vertical reflection:

\[
 {Y\times\dot Y\over B^{3/2}}
 =-{\widetilde W\over2}+o(1).
\tag{6}
\]

Equations (3)--(6) agree with the returning-tail theorem.

## Exact parabolic-endpoint value

The coefficient $\gamma$ is not merely a removable rotation once the orbit
passes through a second central encounter. It can nevertheless be handled
exactly at the centered parabolic endpoint. Let $(R_+,S_+)$ be the outgoing
Jost basis, normalized by

\[
 R_+\sim z,\qquad S_+\sim\sqrt z,
 \qquad W(R_+,S_+)=-1.
\tag{6a}
\]

One concrete choice is
$S_+=R_+\int_\theta^\infty R_+(s)^{-2}\,ds$. By evenness of the transverse
coefficient, the corresponding incoming basis is

\[
 R_-(\theta)=-R_+(-\theta),\qquad
 S_-(\theta)=S_+(-\theta).
\tag{6b}
\]

The definition of $\gamma$ and $\mathscr W_\infty$ gives the first connection
formula. Time reversal gives equal diagonal coefficients, and preservation
of the Wronskian fixes the remaining entry:

\[
 \begin{pmatrix}R_-&S_-\end{pmatrix}
 =\begin{pmatrix}R_+&S_+\end{pmatrix}
 \begin{pmatrix}
  \gamma&(1-\gamma^2)/\mathscr W_\infty\\
  -\mathscr W_\infty&\gamma
 \end{pmatrix}.
\tag{6c}
\]

The matrix has determinant one. The reflected returning field has incoming
coefficients $(-\gamma,\mathscr W_\infty)$ in the $(R_-,S_-)$ basis, hence
outgoing coefficients

\[
 \begin{pmatrix}1-2\gamma^2\\2\gamma\mathscr W_\infty\end{pmatrix}
\tag{6d}
\]

in the $(R_+,S_+)$ basis. Since $W(R_+,S_+)=-1$, its outgoing rotation
Wronskian is therefore

\[
 \boxed{\mathcal C_{2,\mathrm{par}}
 =-2\gamma\mathscr W_\infty.}
\tag{6e}
\]

The extended pinned CAPD certificate now proves

\[
 -{1\over100}<\gamma<-{1\over250},
 \qquad \mathscr W_\infty>{21\over50}.
\tag{6f}
\]

Consequently the centered parabolic endpoint has the strict validated margin

\[
\boxed{\mathcal C_{2,\mathrm{par}}>{21\over6250}>0.}
\tag{6g}
\]

For captured phases tending to this parabolic boundary, regularized
fixed-section convergence gives convergence of both the base orbit and this
transverse field on every compact segment, while the first-turn height tends
to infinity. The phase-uniform turn-Wronskian argument of
`RESTRICTED_TRANSVERSE_SCATTERING.md`, equations (8)--(10), uses only bounded
fixed-section $(p/z,W)$ data and therefore applies to the returned field as
well. Hence
\[
 \lim_{\psi\to\psi_{\rm par},\,\mathrm{captured}}
 \mathcal C_2(\psi)=\mathcal C_{2,\mathrm{par}}>{21\over6250}.
\tag{6h}
\]
Thus a zero of the captured second-turn coefficient cannot be born at this
parabolic endpoint. This closes one endpoint only; it neither classifies all
captured components nor treats the triple-collision limit.

## Phase-dependent compact map

Fix a large returning section $\widetilde z=-K$, put $\theta=0$ at its
incoming crossing, and let $\psi\in\mathbb R/\pi\mathbb Z$ be the binary
eccentric anomaly there. The exact base and transverse section states are
the ones selected by the zero-energy and (4) asymptotics as
$\theta\to-\infty$; an eccentric anomaly at infinity itself would not be
defined because the binary makes infinitely many turns. Let $\vartheta$ be
the running eccentric anomaly and define

\[
 r_\psi(\theta)=\cos^2\vartheta(\theta),\qquad
 4\theta=\ell(\vartheta)-\ell(\psi),\qquad
 \ell(\vartheta)=2\vartheta+\sin2\vartheta.
\tag{7}
\]

Then integrate

\[
 \widetilde z''=-{2\widetilde z\over
  (\widetilde z^2+r_\psi^2/4)^{3/2}},
\tag{8}
\]

together with

\[
 p''={r_\psi^2-2\widetilde z^2\over
  (\widetilde z^2+r_\psi^2/4)^{5/2}}p
\tag{9}
\]

and the incoming data (4). Binary collisions are regular in eccentric
anomaly. For phases on the captured side, let
$T_2(\psi)$ be the first turn after this encounter and define

\[
 \mathcal C_2(\psi)
 =\widetilde z(T_2)p'(T_2)
 =\widetilde W(T_2).
\tag{10}
\]

A second outer brake in the finite-$B$ problem requires the leading physical
angular momentum to vanish, so the immediate target is

\[
 \boxed{\mathcal C_2(\psi)\ne0
 \quad\hbox{on every captured phase component}.}
\tag{11}
\]

The numerics below suggest the stronger sign $\mathcal C_2>0$. By (6), this
would make the physical outer angular momentum negative at the second turn:
the first encounter creates a positive sign and the captured second encounter
reverses it without passing through zero at a turn.

Changing $K$ only reparametrizes this exact section map by the regularized
flow. Equivalently, one may use the canonical incoming intercept $\chi$ of
`RESTRICTED_PHASE_WINDOWS.md` or the mean anomaly $\phi$ at a nonsingular
center crossing. The latter makes capture explicit:
$V_u(\phi)<V_s(\phi)$. A center crossing with $\phi=\pi$ is a simultaneous
heavy-binary/light-center collision in the restricted limit and must be
treated by a separate triple-collision blow-up, not by ordinary analytic
dependence.

## Bounded ordinary probe

The diagnostic script estimates $\gamma$ and $\mathscr W_\infty$ at a finite
cutoff, reflects the asymptotic modes as in (4), and scans the compact phase.
It also replaces the exact phase-dependent parabolic section state by the
instantaneous frozen-potential zero-energy speed and truncates the transverse
data to the two displayed asymptotic modes. Neither cutoff error is enclosed.
At cutoff $40$, representative output is

| cutoff eccentric anomaly | outcome | turn/exit height | $\widetilde W$ |
|---:|:---|---:|---:|
| $0.340$ | exit | $40$ | $-0.04794$ |
| $0.400$ | exit | $40$ | $-0.00283$ |
| $0.415$ | exit | $40$ | $+0.01108$ |
| $0.430$ | turn | $36.25$ | $+0.02822$ |
| $0.598$ | turn | $4.51$ | $+0.21321$ |
| $1.496$ | turn | $1.30$ | $+0.91023$ |
| $2.394$ | turn | $0.65$ | $+1.00477$ |
| $2.693$ | turn | $0.15$ | $+1.27874$ |
| $2.842$ | exit | $40$ | $-0.16901$ |

All 16 samples that turned before leaving the cutoff box in the coarse
full-period scan had $\widetilde W>0$. Both signs occur among section-exit
samples. An exit at $+K$ is not a proved scattering outcome: a captured orbit
may turn above the finite cutoff, so this scan neither classifies every exit
nor covers the full captured set near a parabolic boundary. These values are
**ORDINARY NUMERICAL EVIDENCE** only. The finite-cutoff estimate of $\gamma$
converges slowly and is not an enclosure.

Recording the mean anomaly at the center section puts all sampled turns in
$0<\phi<\pi$ and all sampled exits in the complementary half-period. This
suggests one captured component bounded by the centered parabolic phase at
$\phi=0$ and the triple-collision phase at $\phi=\pi$. It is still ordinary
evidence: global component classification has not been validated.

Reproduce with

~~~bash
uv run python -m scripts.probe_second_encounter \
  --cutoff 40 --phases 21 --phase-span 10000 --max-step 0.04
~~~

## Proof obligations for the second turn

A rigorous second-turn exclusion can now be split into:

1. classify every captured phase component and all of its parabolic or
   collision boundaries;
2. validate $\mathcal C_2(\psi)>0$ on the compact finite-turn interiors,
   regularizing every binary collision and covering the phase continuum;
3. complete the $\phi\to\pi$ triple-collision selection theorem. The exact
   collision ray, both Fuchsian charts, unique collision-safe universal base,
   and positive universal transfer $K_-$ are now proved in
   `TRIPLE_COLLISION_ENDPOINT.md`; the global projection $A_-$ and
   finite-$\varepsilon$ selection remain;
4. transfer the compact restricted sign to finite $B$ using divided LC
   variables, then repeat the uniform outgoing angular-momentum tail theorem.

The target is one scalar function on compact phase intervals, not a scan over
integer triples. A zero of $\mathcal C_2$ would be a genuine dynamical
bifurcation target and must be isolated rather than rounded away.

Status of (1)--(6), (6a)--(6e), and (6h): **PROVED ANALYTICALLY** from the outgoing
Wronskian asymptotics, radial Kepler transfer, and the even-potential
connection matrix. Status of (6f)--(6g): **PROVED BY COMPUTER-ASSISTED
ARGUMENT**. The definition (7)--(10) gives a
continuous collision-regularized section map on each captured component
after phases producing a triple collision are removed. It is real analytic
locally when the first turn does not coincide with a binary collision. At a
simultaneous binary-collision/outer-turn phase the turn event is degenerate in
eccentric anomaly ($d\theta/d\vartheta=0$), so analyticity there has not been
proved and is not claimed. Status of (11): **CONJECTURAL**. No rational or
real finite-$B$ brake candidate has been found.
