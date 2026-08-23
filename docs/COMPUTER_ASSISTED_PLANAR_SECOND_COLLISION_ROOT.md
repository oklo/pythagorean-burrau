# A second transverse collision in the planar limiting family

The first certified projective collision at
\(\kappa\simeq1.2679351755\) involves the selected positive primary.  A
different collision boundary occurs nearby but outside its local escape cusp.
This note certifies a transverse collision with the *opposite* primary at

\[
 \kappa_2\in
 [\mathtt{0x1.439648fe6be57p+0},
  \mathtt{0x1.439649319fb1p+0}]
 \subset(1.2640119191,1.2640119311).
\tag{1}
\]

This is a theorem about the massless planar restricted limiting family.  It is
not a positive-mass Pythagorean collision and is not a second brake.

## Two collision-adapted charts

Start from the analytic stable-tail enclosure at \(\zeta=15\).  Propagate in
the existing LC chart relative to the positive primary for the exact
regularized duration \(7/4\).  Whole-step enclosures prove throughout this
first leg that

\[
 t>1,\qquad R>2,\qquad |q+R e_x|^2>1,
 \qquad |q|>10^{-8}.
\tag{2}
\]

Thus neither primary is hit before the chart switch.  Here \(q\) is relative
to the positive primary; the last inequality is read from
\(|q|=|u|^2\) in its LC coordinate.

At the fixed switch put

\[
 q_-=q+R e_x,
 \qquad
 \dot q_-={2uv\over |u|^2}+{2R\over3t}e_x.
\tag{3}
\]

The switch enclosure proves \(\Im q_-<0\).  Its interval image has
\(\Re\sqrt{q_-}>1\), \(\Im\sqrt{q_-}<0\), and \(t>1\), so the negative
square-root sheet is the exact lift rather than an imposed sign convention,
and no branch boundary is crossed.  Set

\[
 u_-^2=q_-,\qquad
 v_-={\overline{u_-}\dot q_-\over2},\qquad
 h_-={|\dot q_-|^2\over2}-{1\over|q_-|}.
\tag{4}
\]

The second LC field regularizes collision with the negative primary.  Its
forcing by the positive primary uses

\[
 R(t)=9^{1/3}t^{2/3},\qquad
 g=-{e_x\over R^2}
   -{q_--R e_x\over|q_--R e_x|^3}.
\tag{5}
\]

In the decreasing-radial-time clock \(S\),

\[
 u_{-,S}=-v_-,\qquad t_S=-|u_-|^2,
\tag{6}
\]

with the standard forced LC equations for \(v_-\) and \(h_-\).  Whole-step
enclosures through the candidate root prove

\[
 \Re v_->{1\over2},\qquad
 t>{1\over2},\qquad |q_--R e_x|^2>{1\over100},
\tag{7}
\]

so the nonregularized primary remains separate.  Because
\((\Re u_-)_{S}=-\Re v_-<0\) and \(\Re u_->1\) at entry, \(\Re u_-\) has at
most one zero on the whole second leg.  The interval-Newton terminal collision
is therefore the first collision with the selected negative primary, not a
regularized recollision after classical termination.

## Interval Newton theorem

Let \(F_2(\kappa,S)=(\Re u_-,\Im u_-)\) at the end of the second LC leg.  The
verifier uses the rational box

\[
 X_2=\left({12640119251\over10^{10}}
              +[-7\mathbin{\cdot}10^{-9},7\mathbin{\cdot}10^{-9}]\right)
     \times
     \left({10275749204\over10^{10}}
              +[-5\mathbin{\cdot}10^{-8},5\mathbin{\cdot}10^{-8}]\right).
\tag{8}
\]

CAPD encloses

\[
 \det DF_2(X_2)
 \subset
 [\mathtt{0x1.8b59e556b0fadp+6},
  \mathtt{0x1.8d2bebcfbfa7cp+6}],
\tag{9}
\]

which is strictly positive, and the interval-Newton image is

\[
 N(X_2)\subset
 [\mathtt{0x1.439648fe6be57p+0},
  \mathtt{0x1.439649319fb1p+0}]
 \times
 [\mathtt{0x1.070f25b65f28p+0},
  \mathtt{0x1.070f271454be1p+0}]
 \Subset X_2.
\tag{10}
\]

Therefore \(F_2\) has exactly one zero in \(X_2\), it is transverse, and the
corresponding limiting classical branch reaches the negative primary without
an earlier collision.  At the collision the regularized speed satisfies

\[
 \Re v_-\in
 [\mathtt{0x1.6a097edbcbd6cp-1},
  \mathtt{0x1.6a09d38041eeep-1}],
\tag{11}
\]

while \(t\in(0.6152,0.6153)\); hence this occurs strictly before the prescribed
heavy-binary collision at \(t=0\).

## Scope and reproduction

The new root is distinct from the first root because the disjoint projective
boxes in (1) and the first certificate are separated by more than
\(3.9\times10^{-3}\).  Its nonsingular limiting Jacobian supplies the local
input for a future finite-mass persistence argument in the second collision
chart; that persistence is not promoted here.  No outgoing classification on
either side of this second limiting graph is claimed yet.

Run

    bash scripts/run_capd_planar_light_collision_newton.sh \
      /path/to/CAPD /path/to/CAPD/build-native --second-root

with CAPD 6.1.0 at commit
`731079217a9254ea2948d742df2b170895effe7f`, the native interval backend, and
`-frounding-math`.  The exact hexadecimal replay is stored in
`data/validated_planar_second_light_collision_root_capd.txt`.

The existence, uniqueness in (8), transversality, and collision safety before
the root are **PROVED BY COMPUTER-ASSISTED ARGUMENT**.  Three independent
adversarial audits rederived the chart and clock signs and endorsed the
repaired first-hit argument based on \(\Re v_->1/2\).  Global uniqueness
of collision parameters in the planar family is not claimed.
