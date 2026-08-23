# Validated escape of the planar collision--ejection continuation

The transverse planar root is a collision of the massless light particle with
one prescribed heavy primary.  This note follows its *regularized limiting
continuation* beyond that collision, through the subsequent prescribed
heavy--binary collision, and into a strict analytic escape cone.  It does not
physically continue any positive-mass classical collision.

The conclusion supplies the explicit collision-or-escape interval
\[
 \mathcal K=[1.2679251755,\,1.2679451755]
\tag{0}
\]
around the normalized projective root, together with a finite-mass
neighborhood of that interval.  It is stronger than a local impact-parameter
sign, but remains local in \(\kappa\); it does not classify the entire planar
scattering family.

## Selected light--heavy LC continuation

Use the certified branch and radial clock of
`COMPUTER_ASSISTED_PLANAR_LIGHT_COLLISION_ROOT.md`.  The verifier evolves in

\[
 S=-\sigma,
\]

so its selected-pair LC equations have

\[
 u_S=-v,\qquad t_S=-|u|^2.
\tag{1}
\]

At a section on the collision--ejection side where \(u\ne0\), reconstruct

\[
 q=u^2,\qquad
 q_t={2uv\over|u|^2},\qquad
 Z=q+{R\over2},\qquad
 Z_t=q_t+{R\over3t}e_x.
\tag{2}

The last term uses \(R_t=2R/(3t)\).  The pinned CAPD propagation starts from
the full explicit interval \(\mathcal K\), not merely the narrower
interval-Newton image of the root, and carries ten adjacent interval-boxed
selected-pair LC flows to the fixed duration

\[
 S={61\over25}.
\tag{3}

Every accepted LC step has

\[
 t>{3\over10},qquad R>1,qquad |q+R e_x|>{1\over10}.
\tag{4}

Thus the chosen primary is handled by LC and the other primary stays strictly
separated.  No ordinary coordinate is inverted at \(u=0\).

## Heavy-binary bridge

Put

\[
 \lambda=\sqrt[3]{t},qquad
 R=9^{1/3}\lambda^2,qquad
 \eta=\lambda_{\rm in}-\lambda.
\tag{5}
\]

The restricted outer state \((Z,V)\), with \(V=Z_t\), obeys the analytic
bridge

\[
 \begin{aligned}
 \lambda_\eta&=-1,\\
 Z_\eta&=-3\lambda^2V,\\
 V_\eta&=-3\lambda^2\left[
 -\Phi\left(Z+{9^{1/3}\lambda^2\over2}e_x\right)
 -\Phi\left(Z-{9^{1/3}\lambda^2\over2}e_x\right)
 \right].
 \end{aligned}
\tag{6}
\]

This field is analytic at the prescribed heavy-binary collision
\(\lambda=0\) whenever the light particle is separated.  Whole-step CAPD
enclosures prove both light--primary distances exceed \(1/2\) throughout the
bridge.  At the final section,

\[
 -2.1<\lambda<-1.9.
\tag{7}
\]

The ten hexadecimal tile enclosures are printed by the verifier.  Across
all tiles, the whole bridge has certified minimum squared light--primary
separation

\[
 d_{\min}^2>\mathtt{0x1.c9c24ac01ab44p-1}>0.89.
\tag{8}
\]

## Exact terminal escape lemma

After the heavy collision use increasing physical future time \(s=-t>0\).
The prescribed primaries lie at \(\pm a(s)e_x\), where

\[
 a(s)={9^{1/3}\over2}s^{2/3},qquad
 a'(s)={9^{1/3}\over3}s^{-1/3}.
\tag{9}

Let \(r=|Z|\), \(w=r-a\), and \(v=r_s=-r_t\).  Whenever \(w>0\), the
radial equation and the triangle inequality give

\[
 r_{ss}\ge-|\ddot Z|\ge-{2\over w^2}.
\tag{10}

Fix \(c>0\).  If at some \(s_0\)

\[
 \boxed{
 v_0-{2\over c w_0}>c+a'(s_0),
 }
\tag{11}

then \(w_s\ge c\) for every \(s\ge s_0\).  Indeed, on any maximal interval
where this holds,

\[
 w(s)\ge w_0+c(s-s_0)
\]

and (10) gives

\[
 v(s)\ge v_0-
 \int_{s_0}^s{2\,d\xi\over[w_0+c(\xi-s_0)]^2}
 >v_0-{2\over c w_0}>c+a'(s_0)\ge c+a'(s).
\tag{12}
\]

Hence \(w_s=v-a'>c\), closing the bootstrap strictly.  Both primary
distances tend to infinity and \(r_s\) stays bounded below by a positive
constant.  The light particle escapes hyperbolically.

The verifier applies (11) with \(c=2\).  It proves

\[
 w_0>10,qquad v_0>{5\over2},qquad
 v_0-{2\over2w_0}-2-a'(s_0)
 >\mathtt{0x1.186465d2c45b8p-1}>0.54.
\tag{13}

Thus the regularized collision--ejection continuation of the exact certified
root escapes.

## Positive-mass hierarchical escape lemma

Finite-time continuity by itself cannot transfer the preceding restricted
conclusion to positive light mass: the two heavy bodies then feel the light
body for all future time.  The following independent comparison controls
that accumulated backreaction.

Let \(m_a,m_b\) be the prospective inner pair, let \(m_c\) be the outer
mass, and use Jacobi variables

\[
 M=m_a+m_b,\qquad \mathcal M=M+m_c,\qquad
 x=q_b-q_a,\qquad
 y=q_c-{m_aq_a+m_bq_b\over M}.
\]

Put

\[
 r=|x|,\qquad \rho=|y|,\qquad w=\rho-r,\qquad
 e={1\over2}|\dot x|^2-{M\over r}.
\tag{14}
\]

Fix \(\epsilon>0\) and \(c>0\).  At a collision-free time \(t_0\), write
\(r_0,\rho_0,w_0,e_0\) for the corresponding values and define

\[
 v_b=\sqrt{{2M\over r_0}+2\epsilon},
\tag{15}
\]

\[
 K=\int_0^\infty
 {\sqrt{\,2M(r_0+v_bt)+2\epsilon(r_0+v_bt)^2\,}
  \over (w_0+ct)^3}\,dt.
\tag{16}
\]

The integral is finite.  Suppose

\[
 w_0>0,\qquad e_0<\epsilon,
\tag{17}
\]

\[
 \boxed{
 \dot\rho_0-{\mathcal M\over cw_0}>v_b+c,
 \qquad e_0+2m_cK<\epsilon.}
\tag{18}
\]

Then the future classical solution either has an inner collision or the
outer body escapes with

\[
 \dot\rho>v_b+c,\qquad
 \rho-r\ge w_0+c(t-t_0)
\tag{19}
\]

for all \(t>t_0\).  In particular it cannot have a later brake.

To prove the lemma, the exact Jacobi equations give, while \(\rho>r\),

\[
 |\ddot y|\le {\mathcal M\over(\rho-r)^2},\qquad
 |\dot e|\le {2m_c r|\dot x|\over(\rho-r)^3}.
\tag{20}
\]

Bootstrap on \(e<\epsilon\) and \(w\ge w_0+c(t-t_0)\).  The first inequality
implies

\[
 r(t)\le r_0+v_b(t-t_0).
\tag{21}
\]

Indeed, below \(r_0\) this is automatic, whereas at and above \(r_0\),
\(\dot r\le|\dot x|\le v_b\).  Radial acceleration and (20) give

\[
 \dot\rho(t)\ge\dot\rho_0-{\mathcal M\over cw_0}>v_b+c.
\tag{22}
\]

Integrating (22) and subtracting (21) closes the positional part of the
bootstrap.  Moreover

\[
 r|\dot x|
 \le\sqrt{2Mr+2\epsilon r^2},
\]

so (16), (20), and (21) give

\[
 e(t)\le e_0+2m_cK<\epsilon.
\tag{23}
\]

All inequalities close strictly.  The growing gap excludes either outer
collision; the only permitted finite-time collision is the inner one.  This
proves the dichotomy.

For the certified limiting terminal state, \(M=\mathcal M=2\), \(m_c=0\),
and the prescribed binary is parabolic, so \(e_0=0\).  CAPD additionally
proves, with \(\epsilon=1/100\) and \(c=3/2\),

\[
 \dot\rho_0-{2\over(3/2)(\rho_0-r_0)}
 -\sqrt{{4\over r_0}+{2\over100}}-{3\over2}
 >\mathtt{0x1.5104501c497c4p-1}>0.65.
\tag{24}
\]

For a finite-mass member the lemma is applied in its Newtonian-scaled
terminal coordinates
\[
 \widehat q={q\over\rho_T},\qquad
 \widehat t={t-t_*\over\rho_T^{3/2}},\qquad
 \widehat{\dot q}=\sqrt{\rho_T}\,\dot q,\qquad
 \widehat e=\rho_T e.
\tag{25}
\]
The masses are unchanged by this fixed-mass scaling, and both the lemma and
the escape conclusion are invariant under it.  The scaled terminal state,
its masses, and \(\widehat e_0\) converge through the common selected-pair and
heavy-binary LC charts.  On a fixed compact scaled terminal neighborhood,
\(K\) has a uniform finite upper bound.  Hence for all sufficiently small
\(m_c=B>0\), one has \(\widehat e_0\to0\), \(2m_cK\to0\), and the strict
inequalities (17)--(18) persist in hatted variables.  Equivalently, the
physical energy ceiling is \(\epsilon/\rho_T\).  This is the required
infinite-time finite-mass transfer; it does not follow from openness alone.

## Local collision-or-escape consequence

All flow segments before the terminal section are analytic in the common
selected-pair and heavy-binary LC charts, and every nonselected collision
boundary has a strict separation margin.  The terminal inequalities (13) are
strict.  Uniform interval propagation proves on the whole explicit interval
\(\mathcal K\) that:

* \(\kappa=\kappa_c\) is the unique selected collision in the narrower
  certified interval-Newton \((\kappa,S)\)-box;
* for every \(\kappa\in\mathcal K\), the classical forward branch either
  suffers a collision before the terminal section or agrees there with the
  regularized branch and reaches the strict escape cone; and
* after the differentiated finite-mass transfer, every sufficiently small
  compatible positive-mass member in a neighborhood of \(\mathcal K\) either
  has a true classical collision before the terminal section or satisfies
  the positive-mass escape lemma there.

In the last item a positive-mass collision terminates the classical solution.
LC is used only to make the parameter-dependent maps and the alternative
continuous.  Every collision-free member of this local cusp is nonperiodic by
escape.

## Certificate and trusted computing base

The source is
`src/verification/planar_light_collision_newton_capd.cpp`; the pinned wrapper
is `scripts/run_capd_planar_light_collision_newton.sh`.  It uses CAPD 6.1.0 at
commit `731079217a9254ea2948d742df2b170895effe7f`, the native interval backend,
and `-frounding-math`.  The ten-tile hexadecimal record is
`data/validated_planar_collision_escape_tiles_capd.txt`.  A successful replay
now ends with

    PASS_ROOT method=CAPD-6.1.0-native \
      stage=planar-light-collision-interval-newton
    PASS_ESCAPE method=CAPD-6.1.0-native \
      stage=planar-light-collision-ejection-escape \
      tiles=10

The trusted computing base consists of the analytic stable-tail theorem and
its exact tests, the displayed C++ verifier, pinned CAPD intervals, the C++
compiler and floating-point implementation, interval Newton, and the analytic
escape lemmas (10)--(12) and (14)--(23).

The root, its regularized escape continuation, and the strict limiting
margins are **PROVED BY COMPUTER-ASSISTED ARGUMENT**.  The terminal comparison
lemmas and the local finite-mass collision-or-escape transfer are **PROVED
ANALYTICALLY** once those validated margins are supplied.  No global
classification outside \(\mathcal K\) is claimed.
