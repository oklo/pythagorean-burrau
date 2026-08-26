# Affine-generator remainder graph

## Purpose

The masked PG2 graph

\[
X(\delta)\in x+T\delta+Q\delta^2+E
\]

retains the true parameter jet but stores every accumulated numerical and
nonlinear error in a componentwise box $E$.  The middle exchange amplifies
that box by eleven orders more than its quadratic parameter term.  Adding
Hessian directions cannot recover correlation already discarded into $E$.

The replacement is a rectangular affine-generator remainder:

\[
X(\delta)\in
x+T\delta+Q\delta^2+G\Xi+E,
\qquad
\Xi=[-1,1]^k.
\tag{1}
\]

The columns of the point matrix $G$ are never inverted or converted back to
independent physical coordinates.  Their source coefficients are propagated
linearly through every Poincare and chart map.  Only derivative width and
genuinely nonlinear terms enter $E$.

## Theorem AGR (affine-remainder PG2 update)

Let $F:H\to\mathbb R^n$ be $C^2$ on a convex set $H$ containing the complete
hull of (1), and put

\[
R=G\Xi+E.
\]

Let $J_x$ enclose $DF(x)$ and let the six directional Taylor forms over $H$
be

\[
q_{TT}=\tfrac12D^2F[T,T],\quad
c_{TQ}=D^2F[T,Q],\quad
c_{TR}=D^2F[T,R],
\]

\[
q_{QQ}=\tfrac12D^2F[Q,Q],\quad
c_{QR}=D^2F[Q,R],\quad
q_{RR}=\tfrac12D^2F[R,R].
\]

Choose a point generator matrix $G'$ and an interval box $S_G$ satisfying

\[
J_xG\Xi\subseteq G'\Xi+S_G.
\tag{2}
\]

For example, evaluate each interval column $J_xg_j$, take its componentwise
midpoint as $g'_j$, and put

\[
S_G=\sum_j(J_xg_j-g'_j)[-1,1].
\]

If $\widehat {F(x)}$ encloses the anchor image and $x'$ is a point chosen
inside it, define

\[
\begin{aligned}
T' &=J_xT+c_{TR},\\
Q' &=J_xQ+q_{TT}+c_{QR},\\
E' &=(\widehat {F(x)}-x')+J_xE+S_G+q_{RR}
     +c_{TQ}D^3+q_{QQ}D^4,
\end{aligned}
\tag{3}
\]

where $D=[-d,d]$ is the parameter-deviation interval.  Then

\[
F(X(\delta))\in
x'+T'\delta+Q'\delta^2+G'\Xi+E'
\qquad(\delta\in D).
\tag{4}
\]

**Proof.**  Write $h=T\delta+Q\delta^2+r$ with
$r=G\xi+e\in R$.  Componentwise Taylor expansion about $x$ gives

\[
F(x+h)=F(x)+DF(x)h+\tfrac12D^2F(\zeta)[h,h]
\]

for componentwise $\zeta$ on the segment $[x,x+h]\subset H$.  Expanding the
quadratic term gives

\[
q_{TT}\delta^2+c_{TQ}\delta^3+c_{TR}\delta
+q_{QQ}\delta^4+c_{QR}\delta^2+q_{RR}.
\]

Split the linear remainder image as
$J_xr=J_xG\xi+J_xe$ and apply (2).  Grouping the coefficients of
$1,\delta,\delta^2$ gives (3)--(4).  Interval evaluation covers every
$\zeta,T,Q,r$ and every componentwise Taylor point. $\square$

Status: **PROVED ANALYTICALLY**.  The exact quadratic-map regression
`test_affine_remainder_generator_keeps_the_linear_image_exact` verifies the
complete decomposition and CAPD's factorial-normalized Hessian convention.

## Residual lifting

After each map the implementation enlarges every centered residual interval
$E'_i=[a_i,b_i]$, $a_i\le0\le b_i$, to

\[
[-r_i,r_i],\qquad r_i=\max(-a_i,b_i),
\]

appends the point column $r_i e_i$ to $G'$, and resets the residual coordinate
to zero.  This is an exact containment operation.  It increases the generator
count by at most $n$ per map while ensuring that every later *linear* image of
the error keeps its shared source coefficient.

The representation is therefore a growing zonotope plus the parameter
quadratic model.  No generator matrix need be square or nonsingular.  This is
the essential distinction from the failed two-tangent-arm reconstruction,
which inverted a rank-eleven Poincare image into independently boxed tangent
coordinates.

## Coordinate-section normalization

For a coordinate Poincare section $y_s=c$, the exact map has

\[
P_s\equiv c,qquad DP_s=0,qquad D^2P_s=0.
\]

After CAPD has included all return-time derivatives, the implementation sets

\[
x'_s=c,qquad T'_s=Q'_s=E'_s=0,qquad G'_{s,j}=0.
\]

The frozen Euclid-parameter row is similarly fixed to
$x'_{ww}=u_c$, $T'_{ww}=1$, with all other contributions zero.  These are
exact properties of the returned fibers, not numerical projections.

The optional direct-image sharpening intersects $E'$ with

\[
I-x'-T'D-Q'D^2-G'\Xi.
\]

This remains sound: the true image lies both in the Taylor representation and
in CAPD's independent image $I$; subtracting independent hulls only enlarges
the set of possible true residuals.

## CAPD interface and independent safety cover

The opt-in mode is

```text
FABLE_ENDGAME_GRAPH=1
FABLE_ENDGAME_GRAPH_C2=1
FABLE_ENDGAME_GRAPH_PG2=1
FABLE_ENDGAME_GRAPH_AFFINE_REMAINDER=1
```

The C2 Poincare pass uses the full coordinate hull of (1) as its independent
C0 domain.  Its three formal interval directions are $T,Q,R$; only
$TT,TQ,TR,QQ,QR,RR$ are retained at second order.  A separate thin-anchor C1
pass supplies $J_x$.  Each point generator is then multiplied by $J_x$ and
split according to (2).

Neither the collision proof nor the brake cover relies on the affine model.
For every leg, a separate C0 set built from the complete coordinate hull is
propagated through the upper return-time bound and checks every accepted-step
enclosure.  This separates continuous-time safety from section-graph
tightness, but it is not an automatic proof that the graph algebra is sound:
an incorrectly narrowed graph need not force an empty later intersection.
A headline theorem therefore still requires an independent implementation
audit.

## First control measurements

The exact interval

\[
[29/100,290000000001/10^{12}]
\]

was replayed end to end at 160 bits, tolerance $10^{-24}$, and order 32.  The
exchange measurements are:

| section | previous boxed $E$ | affine-generator remainder | reduction |
|---|---:|---:|---:|
| second minimum | $1.72024\,10^{-14}$ | $1.24515\,10^{-20}$ | $1.38\,10^6$ |
| $t=29/10$ | $3.08400\,10^{-11}$ | $2.20308\,10^{-20}$ | $1.40\,10^9$ |
| $t=17/5$ | $3.66876\,10^{-9}$ | $1.34206\,10^{-19}$ | $2.73\,10^{10}$ |
| $t=69/20$ | $1.12393\,10^{-6}$ | $1.29044\,10^{-17}$ | $8.71\,10^{10}$ |
| fourth minimum | $4.43187\,10^{-6}$ | $1.74964\,10^{-18}$ | $2.53\,10^{12}$ |
| Form-B switch | about $8.07\,10^{-5}$ | $1.16615\,10^{-18}$ | about $6.9\,10^{13}$ |

At $t=69/20$ the complete hull is $9.20483\,10^{-8}$ and at the fourth
minimum it is $1.93519\,10^{-8}$; both are now almost entirely the genuine
parameter tangent rather than wrapping.  All 21 post-switch sections stayed
between $1.44\,10^{-8}$ and $1.48\,10^{-8}$, while the affine remainder stayed
near $1.35\,10^{-18}$.

The terminal section $t=77/20$ passed with hull
$1.46064\,10^{-8}$, 852 generators, separation margin $0.8755439$, outward
radial-speed margin $2.4193181$, radial-energy margin $0.2084062$, and
post-tidal inner-energy margin $3.4218861$.  Every Poincare return, chart
domain, oriented section, and independent swept-tube collision/brake audit
passed.  The compact reproduction record is
`data/middle_affine_pg2_width_1e12_summary.log`.

Status of these measurements: **VALIDATED NUMERICAL RESULT**, not yet a new
theorem.  The control interval is already contained in the established Fable
theorem, and an independent implementation audit remains open.  The first
theorem-scale test is the single interval $[0.29,0.2900001]$, roughly ten
times wider than the current certified union.

## Theorem-scale replay

The exact closed interval

\[
 \left[{29\over100},{2900001\over10000000}\right]
 =[0.29,0.2900001]
\]

has now passed the complete pinned run at 160 bits, tolerance $10^{-24}$,
and order 32.  This is one correlated enclosure of the continuum, not a
finite point scan.  All 85 expected graph images, every independent C0
inter-section tube audit, four strict minima, three strict maxima, all three
chart-switch images, 21 post-switch sections, and the terminal
escape-or-inner-collision test passed.

The hard exchange bounds were

\[
 \operatorname{wid}X(3.45)<9.198\,10^{-3},\qquad
 \operatorname{wid}R(3.45)<1.443\,10^{-7},
\]

and the fourth-minimum hull was below $1.938\,10^{-3}$.  At the terminal
time $77/20$ the hull was below $1.462\,10^{-3}$ and the strict terminal
margin was

\[
 \inf(-4-h-\Delta)>3.4111236203.
\]

The complete stdout artifact is
`data/middle_affine_pg2_width_1e7_full.log`, with SHA-256
`8c92d90cae1cc94139085aa775f045efb2c83aee84d2be6557495aac4a29a9c9`.
The fail-closed audit

```text
python3 scripts/audit_affine_endgame_log.py \
  data/middle_affine_pg2_width_1e7_full.log \
  --expected-left 29/100 --expected-right 2900001/10000000
```

reports 85/85 itinerary rows, 852 terminal generators, maximum hull
$0.009197584103206032$, maximum affine remainder
$7.130267782501705\,10^{-7}$, and the terminal margin above.  It rejects
wrong endpoints, disabled graph modes, missing or reordered legs, decreasing
generator counts, any failure marker, and every non-strict terminal
inequality.

Status: **VALIDATED NUMERICAL RESULT / COMPUTER-ASSISTED THEOREM
CANDIDATE**.  The execution and certificate-record obligations are closed.
The only promotion gate is the independent adversarial source audit of the
affine-generator inclusion semantics.  Until that audit is complete, the
established theorem remains the previously reviewed interval
$[0.29,0.2900000101]$.

### Second widening: width $10^{-6}$

The exact interval $[0.29,0.290001]$ also completed the same 85-image
certificate.  This is 100 times the trial width above and about 99 times the
currently reviewed theorem width.  The hard-exchange hull was $0.0914731$.
The residual was still only $1.73\,10^{-4}$ at $t=3.45$, but nonlinear
amplification at the fourth minimum raised it to $0.01307$ and then
$0.01916$ at $t=3.5$.  Crucially, it did not grow secularly: all 21 final
section hulls stayed below $0.0264$, and the terminal margin remained
$3.033106146>0$.

The full output is `data/middle_affine_pg2_width_1e6_full.log` (SHA-256
`c8944f75b495cbb9890c206e54c8710a6f600a8c0122498c3d0d68a59a84947d`),
and the same fail-closed auditor reports 85/85 itinerary rows.  This remains
a theorem candidate under the same independent-audit gate.  It nevertheless
changes the campaign economics materially: if comparable translated tiles
work across $[0.29,0.29002]$, about twenty width-$10^{-6}$ certificates would
cover the committed block.  Uniform translatability has not been assumed or
proved; each tile must pass independently or be subdivided.

The resumable campaign driver is

```text
python3 scripts/run_affine_middle_campaign.py \
  --binary /private/tmp/fable_middle_affine_final \
  --output-dir /private/tmp/affine_middle_campaign \
  --first-index 1 --last-index 19
```

With the default base numerator and denominator, tile $j$ is exactly
$[(290000+j)/10^6,(290001+j)/10^6]$.  Thus adjacent files share the same
rational endpoint by construction.  A log is renamed from `.partial` to its
final name only after the executable returns zero and the complete 85-row
audit passes.  Interrupted and rejected artifacts are preserved as
`.failed.log`; an already completed tile is skipped only after being audited
again.  The driver stops at the first failure by default so that the interval
can be classified or subdivided rather than silently leaving a gap.
