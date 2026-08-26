# Validated quadratic parameter graphs

Date: 2026-08-25

## Purpose and status

The middle-interval endgame certificate currently loses parameter correlation
after repeated Poincare maps.  At width $10^{-12}$ the ordinary
section-synchronized sensitivity remains of order $10^3$, whereas the
interval first-derivative product eventually contributes almost $0.9$ to the
state hull.  Midpoint splitting transfers the same width into the additive
defect.  The next representation must therefore retain curvature of the tied
one-parameter graph.

This note proves the abstract quadratic-graph propagation lemma and records
the coefficient convention in pinned CAPD.  Its application to the complete
Burrau itinerary is still **CONJECTURAL** until the C2 implementation, chart
rules, independent C0 containment audit, and terminal replay have all passed.

## CAPD's quadratic coefficient convention

For a $C^2$ map $P:\mathbb R^n\to\mathbb R^m$, write CAPD's quadratic
coefficient array as $\mathsf H(P)$.  Its entries have the convention

\[
 \mathsf H_{i,jj}=\frac12\,\partial_{jj}P_i,
 \qquad
 \mathsf H_{i,jk}=\partial_{jk}P_i\quad(j<k).
\]

Thus the homogeneous quadratic evaluation is

\[
 \mathcal Q_{\mathsf H}(v)_i
 =\sum_j\mathsf H_{i,jj}v_j^2
  +\sum_{j<k}\mathsf H_{i,jk}v_jv_k
 =\frac12D^2P[v,v]_i.
\]

The polarized cross term is

\[
 \begin{split}
 \mathcal C_{\mathsf H}(v,w)_i
  ={}&\sum_j2\mathsf H_{i,jj}v_jw_j\\
     &+\sum_{j<k}\mathsf H_{i,jk}
       (v_jw_k+w_jv_k),
 \end{split}
\]

so that

\[
 \mathcal Q_{\mathsf H}(v+w)
 =\mathcal Q_{\mathsf H}(v)
  +\mathcal C_{\mathsf H}(v,w)
  +\mathcal Q_{\mathsf H}(w).
\]

This is not the naive full double sum over a symmetric Hessian.  In
particular, inserting another factor $1/2$ in front of
$\mathcal Q_{\mathsf H}$ or evaluating both $(j,k)$ and $(k,j)$ is wrong.

### Source-level audit

The dependency is CAPD 6.1.0 at commit
`731079217a9254ea2948d742df2b170895effe7f`.

The decisive source facts are:

1. `capd/diffAlgebra/Hessian.hpp`, lines 63--89, composes a quadratic
   coefficient array with a matrix.  For a repeated input direction it uses
   `H(i,ss,r)*M(r,j)*M(ss,j)` with no factor two when `ss<r`; for two distinct
   input directions it uses the polarized expression.  This is exactly the
   factorial-normalized convention above.
2. `capd/poincare/AbstractSection.hpp`, lines 70--129, constructs `D2P`
   together with first and second derivatives of the return time.  Its
   diagonal and mixed formulas use the same normalized convention.
3. `capd/poincare/BasicPoincareMap.hpp`, lines 76--97, evaluates the vector
   field, its derivative, and the second time-Taylor coefficient at the
   return point before calling the section formula.  Hence `computeDP` for a
   C2 Poincare map includes the dependence of the return time on the initial
   state; it is not merely the fixed-time flow Hessian.

The public comment in `Hessian.h` calls the stored values second partial
derivatives, but the algebra in the implementation is authoritative and
shows the normalized diagonal convention.  A deterministic analytic probe is
required as a regression test before this convention is used in the Burrau
driver.

## Abstract enclosure lemma

Let $D=[-d,d]$, let $S=D^2=[0,d^2]$, and suppose a one-parameter set obeys

\[
 g(\delta)\in x+T\delta+Q\delta^2+E,
 \qquad \delta\in D,
\]

where $x,T$ are point vectors and $Q,E$ are interval vectors.  Assume
$0\in E$.  Let $X$ be a convex interval box containing every such
$g(\delta)$, and let $P$ be $C^2$ on a neighborhood of $X$.

Suppose the following outward-rounded enclosures are available:

\[
 p\ni P(x),\qquad A\ni DP(x),\qquad
 \mathsf H\ni\mathsf H(P)(y)\quad\hbox{for every }y\in X.
\]

Set

\[
 R=QS+E,
 \qquad
 \widehat T=AT,
 \qquad
 \widehat Q=AQ+\mathcal Q_{\mathsf H}(T).
\]

Choose point or interval coefficients $\bar T,\bar Q$ and define the
recentering spills

\[
 E_T=(\widehat T-\bar T)D,
 \qquad E_Q=(\widehat Q-\bar Q)S.
\]

Then, for every $\delta\in D$,

\[
 P(g(\delta))
 \in \bar p+\bar T\delta+\bar Q\delta^2+E',
\]

provided

\[
 \boxed{
 E'\supset
 (p-\bar p)+AE+E_T+E_Q
 +\mathcal C_{\mathsf H}(TD,R)
 +\mathcal Q_{\mathsf H}(R).}
\]

Here every operation on the right is interval evaluation, and $\bar p$ is
any chosen anchor contained in $p$.

**Status: PROVED ANALYTICALLY.**

### Proof

For $h=g(\delta)-x$, Taylor's theorem with integral remainder gives

\[
 P(x+h)=P(x)+DP(x)h+
 \int_0^1(1-s)D^2P(x+sh)[h,h],ds.
\]

Convexity puts $x+sh$ in $X$.  Since $\mathsf H$ stores one-half of the
quadratic form on a repeated direction, the integral remainder is contained
in $\mathcal Q_{\mathsf H}(h)$.  Write
$h=T\delta+r$ with $r\in R$.  Polarization gives

\[
 \mathcal Q_{\mathsf H}(h)
 =\mathcal Q_{\mathsf H}(T)\delta^2
  +\mathcal C_{\mathsf H}(T\delta,r)
  +\mathcal Q_{\mathsf H}(r).
\]

The constant, linear, and quadratic terms are respectively enclosed by
$p$, $AT\delta$, and
$(AQ+\mathcal Q_{\mathsf H}(T))\delta^2$.  Replacing their selected
coefficients by $\bar p,\bar T,\bar Q$ produces exactly the displayed spill
terms.  The remaining terms lie in the displayed $E'$.  This proves the
claim.  Notice that no independence of $r$ and $\delta$ is assumed; replacing
their joint range by $R\times D$ only enlarges the enclosure.

## Exact section normalization

For a coordinate section $q_k=c$, the Poincare image satisfies that equation
identically for every parameter fiber.  After propagation one must therefore
set

\[
 \bar p_k=c,\qquad \bar T_k=0,\qquad
 \bar Q_k=0,\qquad E'_k=0.
\]

This is an exact geometric identity, not an intersection heuristic.  It is
valid only after the C2 Poincare map itself has included the parameter
dependence of the return time.

## Directional C2 lemma used by the implementation

The full Hessian version above is simple but computationally wasteful in a
12-dimensional flow.  The implemented graph uses a point quadratic
coefficient,

\[
 \gamma(\delta)=x+T\delta+Q\delta^2,
 \qquad
 g(\delta)\in\gamma(\delta)+E.
\]

Let $Y$ be a convex box containing both $\gamma(D)$ and
$\gamma(D)+E$.  Suppose

\[
 A_Y\supset DP(Y),
 \qquad
 K\supset {1\over2}{d^2\over d\delta^2}
                 P(\gamma(\delta))quad(\delta\in D).
\]

Let $A_0\ni DP(x)$ and $p\ni P(x)$.  Then

\[
 P(g(\delta))
 \in p+(A_0T)\delta+K\delta^2+A_YE.
\]

**Status: PROVED ANALYTICALLY.**

Indeed, scalar Taylor expansion of $P\circ\gamma$ supplies the first three
terms.  For each fixed $\delta$, the ordinary vector mean-value theorem on the
segment from $\gamma(\delta)$ to $g(\delta)$ supplies $A_YE$.  No smoothness
or parameter correlation of the set-valued defect $E$ is assumed.

The directional coefficient already contains both terms

\[
 {1\over2}(P\circ\gamma)''
 =DP(\gamma)Q+{1\over2}D^2P(\gamma)[\gamma',\gamma'].
\]

Consequently it replaces the full-Hessian cross-term calculation and is
strictly cheaper.

### Exact formal frame

State coordinate 10 in the LC driver is the transported Euclid parameter
`ww`.  Every vector field has $\dot{ww}=0$, and every chart map copies `ww`
exactly.  The graph is normalized after every operation so that

\[
 x_{10}=u_0,\qquad T_{10}=1,\qquad Q_{10}=E_{10}=0.
\]

Let $e=e_{10}$ and $v(\delta)=\gamma'(\delta)=T+2Q\delta$.  CAPD's formal C1
frame is

\[
 V(\delta)=I+(v(\delta)-e)e^T,
\]

that is, column 10 of the identity is replaced by the parameter tangent.
Since $e^Tv=1$, this frame is invertible throughout the parameter interval,
with the exact rank-one inverse

\[
 V(\delta)^{-1}=I-(v(\delta)-e)e^T.
\]

If the propagated formal derivative is $M=DP\,V$, the complete derivative
needed for defect transport is recovered rigorously as

\[
 DP=M V^{-1}.
\]

CAPD is initialized with the sole nonzero formal quadratic direction
$H_{10,10}=Q$.  The returned Poincare coefficient in that same direction is
the interval $K$ above and includes the return-time derivatives.

### Validated mask constraint

The pinned validated `C2DoubletonSet` cannot be run with a mask containing
only the quadratic multiindex: its internal full matrix representation then
encounters incompatible dimensions.  The sound working mask retains

\[
 e_0,e_1,\ldots,e_{11},\quad 2e_{10};
\]

that is, every first derivative and only the one required second derivative.
The analytic probe reproduces the exact nonlinear composition with this mask.
Omitting any first formal coordinate is a regression failure, not a permitted
optimization.

Because the interval coefficient $K$ is recentered to a point $\bar Q$, its
discarded width is added to the defect as $(K-\bar Q)D^2$.  Thus every stored
quadratic coefficient remains a genuine fixed polynomial coefficient, as
required by the directional lemma.

## Launch rule

Let $L(u)$ be the exact regularized Burrau launch map and
$u=u_0+\delta$.  Apply the lemma directly to the static map $L$:

\[
 L(u_0+\delta)
 \in L(u_0)+L'(u_0)\delta
  +\mathsf H(L)(u_0+D)\delta^2.
\]

For a scalar input, `H(0,0)` is the coefficient
$\tfrac12L''$, so no extra factor is inserted.  The parameter-state
coordinate itself is normalized exactly as

\[
 x_u=u_0,\qquad T_u=1,\qquad Q_u=E_u=0.
\]

The implementation must use `D.sqr()` (or an equivalent outward-rounded
$[0,d^2]$ operation), never interval multiplication `D*D`, which would add
spurious negative values.

## Nonlinear chart maps

Every Form-A or Form-B Levi--Civita chart switch is an ordinary static C2 map,
so the same lemma applies without a return-time term.  Its derivative must be
evaluated at the point anchor, while its quadratic coefficient array must be
enclosed on the complete incoming graph hull.  Form A additionally requires a
strict lower bound on $|g|+g_x$; Form B requires a strict lower bound on
$|g|-g_x$.  Those chart-domain margins are proof obligations, not numerical
conveniences.

## Independent containment obligation

The quadratic graph is a correlation device, not the domain proof.  On each
flow or section leg, the complete hull

\[
 x+TD+QS+E
\]

must be contained in an independently propagated C0 tube.  That tube must
continue to prove collision separation and the complete Theorem C brake-
exclusion disjunction through the latest fiber return time.  The C2 map may
then use a convex box containing the graph as the derivative/Hessian domain.

## Adversarial regression obligations

Before any interval theorem is claimed, tests must fail under each of these
mutations:

1. multiply all diagonal quadratic coefficients by two;
2. divide all mixed coefficients by two;
3. evaluate a symmetric full double sum over the stored `Hessian`;
4. omit return-time derivatives from a Poincare map;
5. replace $S=[0,d^2]$ by `D*D`;
6. omit either polarized cross term;
7. omit a nonlinear chart remainder;
8. retain a nonzero coefficient in the exact section coordinate;
9. evaluate the terminal inequality on an anchor fiber rather than the
   complete graph hull.

## Immediate experimental gate

The first implementation gate is deliberately narrow:

1. reproduce an analytic two-dimensional Poincare map whose return time
   varies with the initial state and verify every DP/D2P entry (completed by
   `capd_c2_semantics_probe.cpp`);
2. propagate the exact tied launch through one static chart map and one
   Poincare section at width $10^{-12}$;
3. reproduce the 21 post-Form-B pair--23 sections;
4. report separately the widths of $T D$, $Q S$, and $E$;
5. attempt the terminal section at $t=77/20$ only if every independent C0
   audit remains valid.

Passing this gate is an engineering result, not yet a wider nonperiodicity
theorem.  A theorem is obtained only when the complete interval reaches the
existing phase-robust escape certificate with all covering obligations
closed.

## Masked PG2 update and the boxed-remainder obstruction

The first implementation of the quadratic graph transported the one-variable
jet of $x+T\delta+Q\delta^2$ and propagated $E$ with a domain-wide first
derivative.  A complementary formulation exposes exactly six second-order
forms and no ambient coordinate Hessian is mathematically needed.

### Theorem MP2 (six-form Taylor enclosure)

Let $F:H\to\mathbb R^n$ be $C^2$ on a convex set $H$, let
$D=[-d,d]$, and suppose

\[
 X(\delta)\in x+T\delta+Q\delta^2+E\subset H
 \qquad(\delta\in D).
\]

Here $T,Q,E$ may be interval vectors.  Let $J_x$ enclose $DF(x)$ and,
over all $z\in H$, let

\[
 q_{TT}=\tfrac12D^2F(z)[T,T],\quad
 c_{TQ}=D^2F(z)[T,Q],\quad
 c_{TE}=D^2F(z)[T,E],
\]

\[
 q_{QQ}=\tfrac12D^2F(z)[Q,Q],\quad
 c_{QE}=D^2F(z)[Q,E],\quad
 q_{EE}=\tfrac12D^2F(z)[E,E]
\]

be interval enclosures.  If $\widehat {F(x)}$ encloses the anchor image, set

\[
 \begin{aligned}
 T'&=J_xT+c_{TE},\\
 Q'&=J_xQ+q_{TT}+c_{QE},\\
 E'&=(\widehat {F(x)}-x')+J_xE+q_{EE}
      +c_{TQ}D^3+q_{QQ}D^4,
 \end{aligned}
\]

where $x'$ is any point in $\widehat {F(x)}$.  Then

\[
 F(X(\delta))\in x'+T'\delta+Q'\delta^2+E'
 \qquad(\delta\in D).
\]

**Proof.**  Fix a represented fiber and write
$h=T\delta+Q\delta^2+e$, $e\in E$.  Componentwise Taylor's theorem on the
segment from $x$ to $x+h$ gives

\[
 F(x+h)=F(x)+DF(x)h+\tfrac12D^2F(\xi)[h,h]
\]

for suitable componentwise points $\xi\in H$.  Expanding the quadratic form
gives

\[
 \begin{aligned}
 \tfrac12D^2F[h,h]
 ={}&q_{TT}\delta^2+c_{TQ}\delta^3+c_{TE}\delta
       +q_{QQ}\delta^4+c_{QE}\delta^2+q_{EE}.
 \end{aligned}
\]

Interval evaluation over $z\in H$, $T,Q$, and every $e\in E$ contains the
componentwise choices of $\xi$ and $e$.  Grouping the constant, linear, and
quadratic powers of $\delta$, and enclosing $\delta^3,\delta^4$ by $D^3,D^4$,
proves the inclusion. $\square$

Status: **PROVED ANALYTICALLY**.  The exact scalar polynomial regression is
`test_pg2_six_directional_form_update_is_exact_for_quadratic_maps`.

There is no extra factor two in the implemented mixed entries.  CAPD's
`Hessian` stores $D_{ii}^2F/2$ on a diagonal and $D_{ij}^2F$ for $i<j$.
Thus a formal C2 frame with columns $T,Q,E$ returns $q_{TT}$ in entry $(0,0)$
and $c_{TE}$ in entry $(0,2)$ directly.

### Correspondence with pinned CAPD

The implementation is opt-in through
`FABLE_ENDGAME_GRAPH_PG2=1`.  Its C0 part contains the complete graph hull.
Its initial C1 matrix has columns $0,1,2$ equal to the interval vectors
$T,Q,E$ and all other columns zero; the initial C2 tensor is zero.  An
interval $E$ column is sound: the C1 constructor splits every interval matrix
entry into midpoint plus centered remainder, so its represented matrix set
contains a column equal to every $e\in E$.  C2 propagation then encloses the
variational chain rule for every such initial matrix and every point in the
independent C0 domain.

This statement was checked against pinned CAPD commit
`731079217a9254ea2948d742df2b170895effe7f`:

- `C2DoubletonSet.hpp:185--213` installs the supplied C0, C1, and C2 parts;
- `C2DoubletonSet.hpp:233--267` composes the current C1 matrix and C2 tensor
  with the interval Jacobian and Hessian of every validated flow step;
- `SectionDerivativesEnclosure.h:113--123` hulls both derivatives over the
  complete section-touching window;
- `AbstractSection.hpp:83--129` applies the first- and second-return-time
  correction entrywise, so selected formal directions remain selected after
  the Poincare map;
- `DagIndexer.h:285--301,423--436` states and implements derivative masks,
  automatically adding dependencies and zeroing unrequested coefficients.

CAPD's C2 Lohner implementation nevertheless requires a square C1 algebra.
A mask containing only the first three first-order multiindices failed closed
before its first step with a $1\times1$ by $12\times12$ dimension exception.
The repaired mask retains all twelve first-order multiindices and only the six
second-order pairs $TT,TQ,TE,QQ,QE,EE$.  No physical enclosure was accepted
from the failed run.

Status of the source-to-formula correspondence:
**PROVED BY COMPUTER-ASSISTED ARGUMENT**, by pinned-source inspection, the
existing analytic Poincare C2 semantics probe, the exact polynomial test, a
successful compile, and fail-closed interval propagation.  An independent
adversarial implementation review remains desirable before this route could
support a new headline theorem.

### Decisive control result

The exact interval

\[
 [29/100,290000000001/10^{12}]
\]

was propagated at 160 bits, tolerance $10^{-24}$, and order 32 through the
fourth-minimum section.  Every completed independent swept-tube collision and
brake audit passed.  At the difficult exchange the results were

| section | total hull | $T D$ | $Q D^2$ | $E$ |
|---|---:|---:|---:|---:|
| $t=17/5$ | $4.73386\,10^{-9}$ | $1.06510\,10^{-9}$ | $4.29\,10^{-19}$ | $3.66876\,10^{-9}$ |
| $t=69/20$ | $1.21598\,10^{-6}$ | $9.20483\,10^{-8}$ | $2.79\,10^{-17}$ | $1.12393\,10^{-6}$ |
| fourth minimum | $4.45123\,10^{-6}$ | $1.93519\,10^{-8}$ | $1.94\,10^{-16}$ | $4.43187\,10^{-6}$ |

These values are essentially the same as the earlier directional-C2 control.
The run was stopped after this decisive comparison; it proves no new
nonperiodicity interval.  The compact record is
`data/middle_masked_pg2_width_1e12_failure_summary.log`.

Masked PG2 therefore solves the full-Hessian *runtime* problem, but not the
exchange-width problem.  It retains the one-dimensional $T,Q$ jet while $E$
remains a componentwise ambient box.  Once correlation has entered $E$, the
six interval forms must cover every vector in that box, and the close
encounter amplifies precisely that missing correlation.

This limitation is information-theoretic.  From the tuple $(x,T,Q,E)$ alone,
at $\delta=0$ every map $X_e$ with $X_e(0)=x+e$, $e\in E$, is consistent with
the representation.  Any update asserted sound for all represented graphs
must therefore contain $F(x+E)$ at that fiber.  No higher derivative formula
can reconstruct which subset of $E$ belongs to the actual parameterized
orbit.  The next useful object must refine the representation itself: a
structured doubleton/tripleton remainder, a second local parameter inside the
remainder with a proved dependence relation, or an intrinsic invariant-leaf
chart.

Status of that representation obstruction: **PROVED ANALYTICALLY**.  Status
of the observed exchange economics: **VALIDATED NUMERICAL RESULT**.
