# Computer-assisted sign at the universal triple-endpoint turn

## The certified statement

Let the universal restricted base be normalized to cross the binary center at
$s=0$. Write $C=9^{1/3}$, $Y=Z/C$, and $U=Y_s$. Suppose

\[
 {1\over2}\le U(0)\le {3\over4},
 \qquad Y(0)=0.
\tag{1}
\]

For the transverse equation, normalize $P(0)=1$ and suppose

\[
 Q(0)=P_s(0)\ge {1\over1000}.
\tag{2}
\]

The pinned CAPD verifier proves that the base has a first radial turn before
$\mu=1.65$, remains at positive height through that turn, and satisfies

\[
 Q(t_{\rm turn})>0.
\tag{3}
\]

Consequently its turn Wronskian is positive:

\[
 K=Z(t_{\rm turn})P_s(t_{\rm turn})>0.
\tag{4}
\]

The analytic universal-base and Riccati lemmas place the canonical slow field
strictly inside (1)--(2). Therefore (4) proves

\[
 \boxed{K_->0.}
\tag{5}

This is a statement about the universal rescaled endpoint problem. It does
not prove that the finite-$\varepsilon$ second-encounter family selects this
base, and it does not determine the global returned-Jost coefficient $A_-$.

## Analytic enclosure of the center data

Put $e=\sqrt3/2$, $v=y_\tau$, and normalize the center by $y(0)=0$.
The exact increasing-energy identity gives

\[
 {v(0)^2\over2}
 ={5\over36}+{1\over3}\int_{-e}^0v(y)\,dy.
\tag{6}
\]

The analytic comparison $0<v\le y+e$ therefore yields

\[
 \sqrt{5\over18}<v(0)
 \le {\sqrt{19}\over6},
\tag{7}
\]

which lies in the dyadic cover (1). At $s=0$, $U=Y_s=v$.

For the canonical slow transverse field, the Riccati barrier proves

\[
 {P_s(0)\over P(0)}
 \ge-\alpha_-+{7\sqrt3\over200}>{1\over1000}.
\tag{8}

For the last rational comparison, one may use
$\sqrt3>433/250$ and $\sqrt7>529/200$; their difference gives
$109/75000>1/1000$.

## Collision-regularized field

Set

\[
 \lambda=\operatorname{sgn}(1-s)|1-s|^{1/3},
 \qquad \mu=1-\lambda.
\tag{9}

Then $\mu$ increases with physical time and $ds/d\mu=3\lambda^2$.
In the dimensionless variables the exact field is

\[
\begin{aligned}
 \lambda_\mu&=-1,
 &Y_\mu&=3\lambda^2U,\\
 U_\mu&=-{2\over3}{\lambda^2Y\over d^3},
 &P_\mu&=3\lambda^2Q,\\
 Q_\mu&={1\over3}{\lambda^2(\lambda^4-2Y^2)P\over d^5},
 &d^2&=Y^2+{\lambda^4\over4}.
\end{aligned}
\tag{10}
\]

Because the verifier proves $Y>0$ before and through the turn, (10) is
analytic at the prescribed binary collision $\lambda=0$. Moreover
$U_\mu<0$ away from the center and collision instants, so the certified zero
of $U$ is the unique first turn.

The transverse dependence on the center logarithmic derivative is exactly
linear. The verifier propagates

\[
 (P_0,Q_0)(0)=(1,1/1000),
 \qquad
 (P_1,Q_1)(0)=(0,1).
\tag{11}

For every $r\ge1/1000$,

\[
 (P,Q)=(P_0,Q_0)+(r-1/1000)(P_1,Q_1).
\tag{12}

Stepwise interval enclosures prove both $Q_0>0$ and $Q_1>0$ until each
speed slab has passed its first turn. Equation (12) proves (3) for the whole
half-line of admissible $r$ without subdividing it.

## Finite cover and event logic

The speed interval $[1/2,3/4]$ is divided into 256 exact dyadic slabs of
width $1/1024$. On each slab, a CAPD order-30 Taylor solver with relative and
absolute tolerances $10^{-15}$ advances one accepted step at a time toward
$\mu=1.65$. Every complete step enclosure is checked for positive $Q_0$ and
$Q_1$. After the first step, every complete step enclosure is also checked
for $Y>0$.

The first step starts at $Y=0$, with $U>0$; its complete enclosure is checked
for $U>0$ and its endpoint for $Y>0$. Thereafter (10) makes $U$ monotone
decreasing. A slab succeeds only when the interval endpoint satisfies
$\sup U<0$. Continuity and monotonicity then give one first turn inside the
last accepted step, where the whole-step $Y,Q_0,Q_1$ signs prove (3).

## Replay and trusted computing base

The verifier is
`src/verification/triple_endpoint_turn_capd.cpp`. The wrapper rejects a CAPD
source tree unless it is the clean pinned commit, uses native outward-rounded
intervals, and was compiled with `-frounding-math`.

~~~bash
bash scripts/run_capd_triple_endpoint_turn.sh \
  /path/to/CAPD /path/to/CAPD/build-native
~~~

The replayed output is stored in
`data/triple_endpoint_turn_capd_certificate.txt`. Its hexadecimal endpoints
are preserved exactly. The trusted computing base is the verifier and
wrapper source, CAPD 6.1.0 at commit
`731079217a9254ea2948d742df2b170895effe7f`, the native interval backend,
the host compiler, and the analytic reductions (6)--(12).
