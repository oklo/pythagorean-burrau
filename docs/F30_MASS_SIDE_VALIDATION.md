# F30 mass--side validation audit

Date: 2026-08-24.

## Target statement

Normalize $m_3=r_{12}=1$, put

\[
 q_1=(-1/2,0),\qquad q_2=(1/2,0),\qquad q_3=(x,y),
\]

and start from rest. The local continuation of the Li--Liao $F_{30}$ orbit
suggests a zero of the shooting map

\[
 F=(\dot h_1,\dot h_2,\dot h_3,r_{23}(0)-m_1,r_{31}(0)-m_2).
\]

Here $h$ is the unweighted Jacobi Hopf map evaluated at the half-orbit
endpoint. Since total angular momentum is zero, its three derivatives vanish
exactly at a labelled brake away from triple collision. A validated interval
Newton inclusion for $F=0$, plus positive swept pair-separation enclosures,
would prove a nearby general mass--side-tied periodic brake orbit. If its
unique root also satisfies

\[
 m_1^2+m_2^2-1<0,
\]

the local orbit is rigorously separated from the Pythagorean locus. This
would not prove the main conjecture globally.

## Ordinary candidate

The original physical-coordinate DOP853 and Radau shooting calculations
locate

\[
 (x,y,T/2,m_1,m_2)\simeq
 (0.14452110646,0.47690214001,6.2892338233,
 0.59481164657,0.80177497331).
\]

Endpoint residuals there are noise-limited near $10^{-9}$. A finite-
difference Jacobian has smallest singular value about $0.199$. The mass
Pythagorean defect is stably about $-0.00335599728$.

The initial uniform physical-time sample reported minimum separation
$0.00263$; it was too coarse. Sampling the global regularized trajectory
resolves a deeper pair-$23$ miss of about $5.0009\times10^{-4}$ near
physical time $3.14746$. It is an ordinary positive miss, not a collision
certificate.

## Superseded direct Jacobi verifier

The first CAPD implementation used the eleven-state physical Jacobi system
$(X,Y,\dot X,\dot Y,m_1,m_2,T/2)$ on a fixed scaled interval. It crosses the
first close pair-$23$ passage but reaches CAPD's minimum step near physical
time $1.7626$. Increasing the order from 30 to 55 reproduces the same
failure. Because the point-center flow itself fails, parameter subdivision
cannot repair that representation.

## Global pair-23 Levi--Civita verifier

The current verifier uses

\[
 g=q_3-q_2=w^2,\qquad {dt\over d\sigma}=|w|^2
\]

over the whole half-orbit. Let $G=q_1-C_{23}$, $P=dG/dt$, and
$h=|\dot g|^2/2-(m_2+1)/|g|$. Then

\[
\begin{aligned}
 w_\sigma&=z,\\
 z_\sigma&={h\over2}w+{|w|^2\over2}\overline w F_{\rm ext},\\
 h_\sigma&=2\operatorname{Re}(\overline{wz}F_{\rm ext}),\\
 G_\sigma&=|w|^2P,\qquad P_\sigma=|w|^2\ddot G.
\end{aligned}
\]

The fifth shooting parameter is the regularized half-duration $S$; the
system is scaled to a fixed interval $s\in[0,1]$. This avoids repeated chart
overwrites and preserves one $C^1$ parameter graph. Exact SymPy tests check
the pair/complement equations, LC acceleration reconstruction, initial
parameter tangent, and side-residual derivatives.

Independent global-LC DOP853 and Radau roots agree to roughly $10^{-13}$ in
the five parameters:

\[
\begin{aligned}
 w_r(0)&\simeq0.34592828233768,&
 w_i(0)&\simeq0.68930781951891,\\
 S&\simeq21.091601754059,&
 m_1&\simeq0.59481164657101,\\
 &&m_2&\simeq0.80177497331788.
\end{aligned}
\]

The reconstructed physical half-period is about $6.2892338237914$ and the
defect is about $-0.0033559972648$. This remains **ORDINARY NUMERICAL
EVIDENCE**.

The intended proof uses a point $C^0$ flow for $F(p_0)$, a $C^1$ flow over
a parameter box for $DF$, and

\[
 N(p_0,P)=p_0-DF(P)^{-1}F(p_0).
\]

Strict inclusion $N(p_0,P)\subset\operatorname{int}P$ gives existence and
uniqueness. Every swept step separately audits all three mutual distances.

## Present obstruction

A 192-bit, tolerance-$10^{-16}$, order-30 point-center run passes the deepest
regularized encounter, with a swept squared-separation lower bound as small
as $1.22\times10^{-7}$, but later wraps and reaches the minimum step at
scaled time about $0.542$. This is substantially later than the direct-
Jacobi failure and occurs without a singular selected-pair force. A 256-bit,
order-50 replay is in progress.

No interval Newton inclusion has yet been obtained. If higher precision still
fails, the principled repair is a stronger Lohner representation or a
sectioned recentering that preserves all five parameter tangents.

## Reproduction

Global-LC ordinary shooting:

```bash
PYTHONPATH=. .venv/bin/python scripts/continue_f30.py \
  --solve-mass-side-global-lc --method DOP853 \
  --rtol 2e-13 --atol 2e-15 --max-step 0.0005 --root-tol 1e-11
```

Experimental interval verifier:

```bash
bash scripts/run_capd_f30_mass_side_newton.sh \
  /private/tmp/fable-capd /private/tmp/fable-capd/build-mp \
  256 1e-30 50 1e-9 0.0005
```

No `PASS_F30_MASS_SIDE_NONPYTHAGOREAN` marker has yet been obtained.
