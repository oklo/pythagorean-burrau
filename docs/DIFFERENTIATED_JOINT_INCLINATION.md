# Differentiated inclination in the joint two-mode layer

`FINITE_B_TRIPLE_JOINT_BLOWUP.md` proves state convergence after translating
the logarithmically long saddle dwell.  The collision-boundary theorem in
`FINITE_MASS_PLANAR_COLLISION_PERSISTENCE.md` is deliberately formulated on a
fixed downstream section because state convergence alone does not imply
convergence of the derivative with respect to the projective amplitude.  This
note proves the missing differentiated inclination statement in intrinsic
unstable-amplitude coordinates.

The result is local to the saddle passage and its compact continuation.  It
does not prove that the exact tied Pythagorean curve crosses the resulting
collision graph.

## Normalized amplitude family

Use the parity-adapted nonlinear stable-foliation coordinates of
`FINITE_B_TRIPLE_JOINT_BLOWUP.md`.  The two unstable amplitudes are

\[
 H\quad\hbox{(longitudinal)},\qquad
 T\quad\hbox{(reflection odd)},
\]

with limiting exponents

\[
 \mu={1+\sqrt{19}\over4},\qquad
 \tau={1+\sqrt7\over4},\qquad
 p={\mu\over\tau}\in(1,2).
\tag{1}
\]

For \(T\ne0\), put

\[
 \rho_T=|T|^{1/\tau},\qquad
 L_T=-{1\over\tau}\log|T|,
\qquad H=\kappa|T|^p.
\tag{2}
\]

Their numerical values require a normalization.  Choose the simple
\(B\)-dependent eigenvectors and dual spectral covectors continuously so that
\(\pi_\alpha e_\beta=\delta_{\alpha\beta}\), retain the limiting
normalization used by the planar certificate, and orient the odd covector by
the certified sign.  The nonlinear stable foliation then defines \(H,T\) as
the corresponding asymptotic unstable coefficients.  A different oriented
normalization reparametrizes \(\kappa\); the collision zero set is unchanged,
but the numerical scalar is not coordinate-free.

The sign of \(T\) is fixed to the certified branch.  On a fixed saddle
entrance section, hold the stable-foliation coordinate \(S\) fixed while
varying \(\kappa\).  This defines a genuine local family, not a derivative of
the original Pythagorean parameter.

For the positive-mass endpoint problem the reduced vector field is \(C^2\)
in state and \(B\), its two exponents satisfy

\[
 \mu_B=\mu+O(B),\qquad \tau_B=\tau+O(B),
\tag{3}
\]

and the actual odd amplitude obeys \(T_B/B\to\Theta_*\ne0\).  Hence

\[
 B L_{T_B}\longrightarrow0.
\tag{4}
\]

## Differentiated two-mode inclination theorem

**Theorem.** Fix a compact interval \(K\subset\mathbb R\), a compact set of
stable entrance coordinates, one limiting value of the Newtonian-scaled
triangular coordinates, and a compact
translated-time interval
\([-L,L]\) on which the limiting orbits \(\mathscr U_\kappa\),
\(\kappa\in K\), lie in a common regular chart.  Let \(B_j\to0\),
\(T_j\to0\), with fixed sign, and suppose

\[
 B_j|\log|T_j||\to0.
\tag{5}
\]

At the saddle entrance choose the normalized family with amplitudes

\[
 T=T_j,\qquad H=\kappa|T_j|^p,\qquad \kappa\in K,
\tag{6}
\]

and with stable entrance coordinates in the fixed compact set, independent of
\(\kappa\).  Let \(\widehat\Xi_j\) collect the deviations of every scaled
triangular coordinate from its fixed limiting value, including energy and
clock, and assume

\[
\|\widehat\Xi_j\|\longrightarrow0.
\tag{6a}
\]

In particular, the energy component is \(\widehat E_j=\rho_{T_j}E_j\).

Work in the admissible saddle subbox on which the dilational clock
\(d\ell/dx=-\nu\) is uniformly bounded above and away from zero.  Include the
radial, energy, clock, fixed-axis reconstruction, and zero-angular-momentum
variables, together with their \(\kappa\)-tangents, among the stable or
triangular data.  Pull the \(B\)-dependent foliation charts and spectral
projectors back to the common normalized chart.  Their \(C^1\) convergence is
the parameter-dependent stable-foliation consequence of the proved uniform
\(C^2\) field bounds and uniform spectral gaps.

Translate log size by \(L_{T_j}\) and apply the Newtonian scale
\(\rho_{T_j}\).  On every compact translated interval which is collision-free
in the reduced physical chart, uniformly for \(\kappa\in K\),

\[
 \boxed{
 \|X_j^\kappa-\mathscr U_\kappa\|_{C^1_\zeta([-L,L])}
 +\|\partial_\kappa X_j^\kappa
       -\partial_\kappa\mathscr U_\kappa\|_{C^0_\zeta([-L,L])}
 \longrightarrow0.}
\tag{7}
\]

More quantitatively, the two norms in (7) are bounded by

\[
 C_L\left[
 B_j|\log|T_j||+B_j+|T_j|^{2-p}
 +e^{-cL_{T_j}}+\|\widehat\Xi_j\|
 \right]+r^{(1)}_{j,L},
\tag{7a}
\]

where \(r^{(1)}_{j,L}\to0\) after the common incoming tail is lengthened,
uniformly for \(\kappa\in K\) and for the bounded entrance coordinates.  The
\(|T|^{2-p}\) term makes the statement invariant under the
allowed quadratic change of longitudinal amplitude.

At a collision, (7) is replaced by convergence in scaled LC variables; no
claim about singular physical or log-time velocity is made.  For the selected
light--heavy chart put

\[
 \widehat u={u\over\sqrt{\rho_T}},\quad
 \widehat v=v,\quad
 \widehat h=\rho_T h,\quad
 \widehat Q={Q\over\rho_T},\quad
 \widehat P=\sqrt{\rho_T}P,\quad
 \widehat t={t\over\rho_T^{3/2}},\quad
 \widehat\sigma={\sigma\over\sqrt{\rho_T}}.
\tag{7b}
\]

Fix the LC-clock origin on one common entry section.  If \(K\) is contained
in the validated root neighborhood with its common collision-free pre-LC
chain and fixed deck, then on a compact \(\widehat\sigma\)-interval through
the limiting collision,

\[
 \|\widehat X_j^{\rm LC}-\widehat X_0^{\rm LC}\|_{C^1_{\widehat\sigma}}
 +\|\partial_\kappa\widehat X_j^{\rm LC}
      -\partial_\kappa\widehat X_0^{\rm LC}\|_{C^0_{\widehat\sigma}}
 \longrightarrow0.
\tag{7c}
\]

The analogous assertion holds through a separated limiting heavy-binary
collision in its common scaled LC chart.  For the selected light--heavy
collision replace the singular outer coordinate \(R\) by

\[
 Q=R+{B\over1+B}q
\tag{8}
\]

and use the selected-pair LC coordinate \(q=u^2\).  No physical positive-mass
collision is continued.

### Proof

In nonlinear stable-foliation coordinates the reduced saddle equations have
the form

\[
 \begin{aligned}
 S_\ell&=A_{s,B}S+N_{s,B}(S,U),\\
 (U_L)_\ell&=\mu_B U_L+N_{L,B}(S,U),\\
 (U_T)_\ell&=\tau_B U_T+N_{T,B}(S,U),
 \end{aligned}
\tag{9}
\]

where \(U=(U_L,U_T)\), the stable semigroup decays uniformly, the nonlinear
terms vanish quadratically, and the fields have uniform \(C^2\) bounds on a
fixed box.  The amplitudes \((H,T)\) are the coefficients supplied by the
nonlinear unstable foliation in the fixed spectral normalization above.

The linear modes specify asymptotic coefficients, not the full state at a
fixed translated time.  Let \(X^u_\kappa=\mathscr U_\kappa\) denote the full
limiting nonlinear unstable orbit.  For some \(\alpha>0\), uniformly for
\(\kappa\in K\), its unstable coordinates satisfy as
\(\zeta\to-\infty\)

\[
 \begin{aligned}
 U_T^u&=\operatorname{sgn}(T_j)e^{\tau\zeta}
       +O(e^{(\tau+\alpha)\zeta}),\\
 U_L^u&=\kappa e^{\mu\zeta}
       +O(e^{(\mu+\alpha)\zeta}+e^{2\tau\zeta}),
 \end{aligned}
\tag{10}
\]

and

\[
 \partial_\kappa U_T=o(1),qquad
 \partial_\kappa U_L=e^{\mu\zeta}+o(1).
\tag{11}
\]

Here every remainder in (10)--(11) is a tail remainder as
\(\zeta\to-\infty\), uniformly in \(\kappa\), not a remainder as
\(j\to\infty\) at fixed translated time.  In particular one may sharpen
\(\partial_\kappa U_T^u=o(1)\) to
\(O(e^{(\tau+\alpha)\zeta})\), and the
\(e^{2\tau\zeta}\) term in (10) retains the surviving quadratic longitudinal
bending.

The exact coefficient normalizations give
\(|T_j|^p e^{\mu L_{T_j}}=1\) and
\(|T_j|e^{\tau L_{T_j}}=1\).  Replacing the finite exponents by
their limits costs \(O(B_jL_{T_j})\) in both (10) and (11), which vanishes by
(5).  The stable entrance state and its \(\kappa\)-derivative contribute
\(O(e^{-cL_{T_j}})\), uniformly on bounded translated intervals.  The
triangular energy/clock terms contribute
\(O(\|\widehat\Xi_j\|)\), which vanishes by (6a).  For the actual
Pythagorean energy, \(E_j=O(B_j^{-1})\) and
\(\rho_{T_j}\asymp B_j^{1/\tau}\), so this error is
\(O(B_j^{1/\tau-1})\to0\).

Here is the differentiated tail estimate explicitly.  Choose once and for all

\[
 {\mu\over2}<\omega<\tau.
\tag{11a}
\]

For all large \(j\), \(\mu_{B_j}/2<\omega<\tau_{B_j}\).  On the common
limiting half-line use

\[
 \|X\|_{\omega,A}
 =\sup_{\zeta\le-A}e^{-\omega\zeta}|X(\zeta)|.
\tag{11b}
\]

First construct the unstable-manifold shadow \(\widetilde X_j^u\), with its
finite-entrance stable coordinate set to zero and its dimensional triangular
parameters set to their scaled limiting values.  Put
\(A_{u,j}=\operatorname{diag}(\mu_{B_j},\tau_{B_j})\).  Translation by
\(L_{T_j}\) changes its normalized coefficient vector to

\[
 a_j(\kappa)=
 \left(\kappa e^{(\mu_{B_j}-\mu)L_{T_j}},
       \operatorname{sgn}(T_j)e^{(\tau_{B_j}-\tau)L_{T_j}}\right).
\tag{11c}
\]

Thus \(a_j\to a=(\kappa,\operatorname{sgn}T)\) in \(C^1_\kappa\), uniformly
on \(K\).  The Lyapunov--Perron equation for the shadow is

\[
 \begin{aligned}
 (\mathcal T_j X)_s(\zeta)
 &=\int_{-\infty}^{\zeta}
   e^{A_{s,j}(\zeta-r)}N_{s,j}(X(r))\,dr,\\
 (\mathcal T_j X)_u(\zeta)
 &=e^{A_{u,j}\zeta}a_j(\kappa)
   +\int_{-\infty}^{\zeta}
   e^{A_{u,j}(\zeta-r)}N_{u,j}(X(r))\,dr .
 \end{aligned}
\tag{11d}
\]

The pulled-back rest point is the origin and the nonlinear terms vanish
quadratically.  The common weight is legitimate because the critical Green
denominator satisfies

\[
 2\omega-\mu_{B_j}>{1\over2}(2\omega-\mu)>0
\tag{11e}
\]

for all large \(j\); all other stable/unstable denominators have a uniform
positive gap.  Since
\(|X(\zeta)|\le \|X\|_{\omega,A}e^{\omega\zeta}\), the quadratic
nonlinearity makes the Lipschitz constant of (11d) at most
\(Ce^{-\omega A}\).  Choose \(A\) once so this is below \(1/2\), uniformly
in \(j\) and \(\kappa\in K\).  Notice that the limiting weight \(\tau\)
would be invalid if \(\tau_{B_j}<\tau\).

Because the fields are uniformly \(C^2\), \(\mathcal T_j\) is \(C^1\) in
\(\kappa\).  Differentiation of the shadow fixed-point equation gives

\[
 (I-D_X\mathcal T_j)\partial_\kappa\widetilde X_j^u
 =\partial_\kappa\mathcal T_j.
\tag{12}
\]

The inverse on the left is uniformly bounded by the contraction margin.
The operator, its derivative, and the right side converge uniformly to those
for the full limiting nonlinear orbit \(X^u_\kappa\), because
\(B_jL_{T_j}\to0\) and the pulled-back fields converge in \(C^2\).

It remains to compare this shadow with the actual finite-entrance orbit.  Do
so only at the tail section \(\zeta=-A\), not in the half-line norm (11b).
An \(O(1)\) stable entrance coordinate would have unbounded weighted norm as
\(L_{T_j}\to\infty\).  Uniform \(C^1\) stable-foliation holonomy instead
gives, for the state and its \(\kappa\)-tangent at \(-A\),

\[
 C e^{-c(L_{T_j}-A)}
 +C_A\|\widehat\Xi_j\|+r^{(1)}_{j,A}.
\tag{12a}
\]

The last term is the unmatched nonlinear tail and tends to zero after the
common incoming tail is lengthened.  Holding the triangular entrance data
fixed makes their direct \(\kappa\)-derivative zero; the \(C^1\) holonomy
controls the induced tangent of the stable-fiber projection.  First let
\(j\to\infty\) at fixed \(A\), then let \(A\to\infty\).  Equations
(10)--(11) make the unmatched limiting tail tend uniformly to zero.  This is
the differentiated version of the \(r_{B,L}\) limit in equation (7a) of
`FINITE_B_TRIPLE_JOINT_BLOWUP.md`, and gives (7a).  Under a quadratic
coordinate change \(H\mapsto H+O(T^2)\), the normalized state changes by
\(O(|T|^{2-p})\), while its \(\kappa\)-derivative changes by only \(O(|T|)\);
both vanish because \(1<p<2\).

On the remaining compact saddle-exit interval, the state tangent

\[
 Y_j=\partial_\kappa X_j
\]

satisfies the variational equation

\[
 (Y_j)_\zeta=DF_{B_j}(X_j)Y_j.
\tag{13}
\]

The base states converge in \(C^1_\zeta\), the coefficients in (13) converge
uniformly by the \(C^2\) field bound, and the tangent data converge by (12).
Gronwall's inequality proves (7) until the first chart transition.
The fixed-axis rotation reconstruction is a smooth triangular equation on the
same subbox.  Zero total angular momentum fixes its source and the common
incoming axis fixes its integration constant.  Differentiating that equation
and applying the same coefficient convergence proves convergence of the
reconstructed angle and its \(\kappa\)-tangent; no moving rotation is used to
remove the odd mode.

Every ordinary collision-free transition map is \(C^2\), so it preserves the
same state-and-tangent convergence.  A separated limiting heavy-binary
collision is crossed in the common analytic LC chart already used in the
joint blow-up theorem.  At the selected light--heavy collision, retaining
\(R\) would leave a singular \(B\Phi(q)\) term.  The exact coordinate (8)
instead gives

\[
 Q_{tt}=-{1+A+B\over1+B}\left[
 \Phi\left(Q-{B\over1+B}q\right)
 +B\Phi\left(Q+{1\over1+B}q\right)
 \right],
\tag{14}
\]

while the selected relative equation is

\[
 q_{tt}=-(1+B)\Phi(q)+A\left[
 \Phi\left(Q-{B\over1+B}q\right)
 -\Phi\left(Q+{1\over1+B}q\right)
 \right].
\tag{15}
\]

With \(q=u^2\), \(dt=|u|^2d\sigma\), both the \((u,v,h)\) block and

\[
 Q_\sigma=|u|^2P,qquad P_\sigma=|u|^2Q_{tt}
\tag{16}
\]

are analytic at \(u=0\) whenever \(Q\ne0\).  The validated root has
\(Q=R>2\) at \(B=0\), and the other primary is separated.  In the scaled
variables (7b), compact analytic LC flow therefore propagates both the state
and its variational equation through the regularized zero and proves (7c).
For a positive-mass member which reaches \(u=0\), this continuation is used
only for the shooting map; its classical trajectory terminates.  This
completes the collision-free assertion (7) and the LC assertion (7c).
\(\square\)

## Normalized collision graph

Apply the theorem on a compact \(\kappa\)-interval containing the validated
root.  Use the common LC deck.  Let \(S\) denote the bounded stable entrance
coordinates and let \(\Xi\) collect every triangular coordinate, including
energy and clock.  Write \(\widehat\Xi\) for the deviations of their
Newtonian-scaled values from the fixed limiting values; in particular,
\(\widehat E=\rho_T E\), while the LC clock origin is fixed at entry.  Define

\[
 \mathcal F_{B,T,S,\Xi}(\kappa,\widehat\sigma)
 =\bigl(\operatorname{Re}\widehat u,
        \operatorname{Im}\widehat u\bigr).
\tag{17}
\]

Put

\[
 \epsilon_{\rm cusp}=
 B|\log|T||+B+|T|^{2-p}+e^{-cL_T}
 +\|\widehat\Xi\|.
\tag{17a}
\]

Equations (7a) and (7c) give convergence of this square map in
\(C^1_{(\kappa,\widehat\sigma)}\), uniformly for \(S\) in its fixed compact
set, along every sequence for which \(T\ne0\), \(T\to0\), and
\(\epsilon_{\rm cusp}\to0\).  The certified limiting determinant excludes
zero.  Therefore the parameter-dependent implicit-function theorem gives:

**Corollary.** There are \(\epsilon_0,T_0>0\) such that every admissible tuple
with \(0<|T|<T_0\), \(\epsilon_{\rm cusp}<\epsilon_0\), and \(S\) in the
prescribed compact set has exactly one collision root in a fixed neighborhood
of \((\kappa_c,\sigma_c)\):

\[
 \kappa=\kappa_c(B,T,S,\Xi),\qquad
 \kappa_c(B,T,S,\Xi)\longrightarrow\kappa_c
\tag{18}
\]

along every admissible sequence with \(\epsilon_{\rm cusp}\to0\).  The
determinant
\[
 \widehat D_{B,T,S,\Xi}
 =\det(\partial_\kappa\widehat u,\widehat v)
\]
retains its validated negative sign.  For each fixed parameter tuple, the
normalized amplitude slice and analytic LC flow are at least \(C^1\) in
\((\kappa,\widehat\sigma)\).  This is exactly the regularity established by
the differentiated inclination theorem; no unproved \(C^2\) stable-holonomy
claim is used.  At fixed \((B,T,S,\Xi)\), the two
punctured \(\kappa\)-sides have the scaled local normal form

\[
 \widehat r_{\min,\mathrm{local}}
 ={2\widehat D_{B,T,S,\Xi}^2\over1+B}
  (\kappa-\kappa_c(B,T,S,\Xi))^2+o(|\kappa-\kappa_c|^2).
\tag{19}
\]

The corresponding late physical distance restores the Newtonian size:

\[
 r_{\min,\mathrm{local}}
 =\rho_T\,{2\widehat D_{B,T,S,\Xi}^2\over1+B}
  (\kappa-\kappa_c)^2
  +o(\rho_T|\kappa-\kappa_c|^2).
\tag{19a}
\]

For actual endpoint data, \(T_B/B\to\Theta_*\ne0\), so (5) is automatic;
the exact late-energy component has the scaling required in (6a).  If no
earlier classical collision
has occurred, the joint blow-up theorem puts its remaining dimensionless
saddle entrance coordinates in the prescribed compact subbox and gives
\(\|\widehat\Xi_B\|\to0\).  The tied trajectory has the normalized projective
value

\[
 \kappa_B={H_B\over|T_B|^p}.
\]

Thus the local collision question, in the fixed spectral normalization, is
reduced to the exact scalar gap

\[
 \boxed{\Delta_{\mathrm{intr}}(B)
 =\kappa_B-\kappa_c(B,T_B,S_B,\Xi_B).}
\tag{20}
\]

No sign or zero theorem for (20) is proved here.  Even a nonzero sign excludes
only this local encounter; other collisions and later brakes remain separate
global obligations.

**Status:** the differentiated inclination theorem is **PROVED
ANALYTICALLY**, conditional only on the already proved uniform \(C^2\) saddle
chart and normalized nonlinear amplitudes of
`FINITE_B_TRIPLE_JOINT_BLOWUP.md`.  The existence and nonsingularity of the
base collision root are **PROVED BY COMPUTER-ASSISTED ARGUMENT**, so the
normalized finite-mass collision-graph corollary has that same status.  The
tied gap (20) is **CONJECTURAL**.
