# Octic stable-graph sharpening

Status: **PROVED ANALYTICALLY** for the remainder reduction;
**EXACT SYMBOLIC IDENTITY** for all homological cancellations through degree
eight.

This note extends `PLANAR_STABLE_QUINTIC_ENCLOSURE.md`. It changes no orbit
and no stable-family parameter convention. It removes the homogeneous
degrees six, seven, and eight from the already proved analytic remainder.

Let \(p\) be the transverse stable parameter and \(\nu\) the longitudinal one.
Reflection parity puts a monomial \(p^i\nu^j\) in the horizontal component
when \(i\) is odd and in the vertical component when \(i\) is even. For
\(i+j=d\), its homological divisor is

\[
 (i a_T+j a_L)^2-\frac13(i a_T+j a_L)-h,
 \qquad
 a_T={1+\sqrt7\over6},\quad a_L={1+\sqrt{19}\over6},
\]

where \(h=1/6\) horizontally and \(h=1/2\) vertically. These divisors are
strictly positive in the present degrees. Recursive exact inversion gives
the following numerical values; the verifier uses outward decimal intervals
strictly containing them.

| \(d\) | \(i\) | \(j\) | coefficient |
|---:|---:|---:|---:|
| 6 | 0 | 6 | -0.03554752308110341 |
| 6 | 1 | 5 | 0.2906160326693457 |
| 6 | 2 | 4 | 0.7646840239192993 |
| 6 | 3 | 3 | -0.5122119837097499 |
| 6 | 4 | 2 | -0.3255787974192629 |
| 6 | 5 | 1 | 0.09018289042047257 |
| 6 | 6 | 0 | 0.01521532442954047 |
| 7 | 0 | 7 | -0.02964819863976052 |
| 7 | 1 | 6 | 0.2600382727429195 |
| 7 | 2 | 5 | 0.7759047148743021 |
| 7 | 3 | 4 | -0.4073648753423703 |
| 7 | 4 | 3 | -0.2187679612531310 |
| 7 | 5 | 2 | 0.02807587277422613 |
| 7 | 6 | 1 | -0.0004043571445512920 |
| 7 | 7 | 0 | 0.0007082128321928575 |
| 8 | 0 | 8 | -0.01873149020245308 |
| 8 | 1 | 7 | 0.1918736731487998 |
| 8 | 2 | 6 | 0.6342982024406688 |
| 8 | 3 | 5 | 0.04852346039467548 |
| 8 | 4 | 4 | 0.4311777542055599 |
| 8 | 5 | 3 | -0.4538061636312410 |
| 8 | 6 | 2 | -0.2579769472856198 |
| 8 | 7 | 1 | 0.06829716549840600 |
| 8 | 8 | 0 | 0.008908225658082671 |

`planar_joint_shape_stable_high_order_corrections()` constructs every entry
as an exact algebraic SymPy expression and substitutes it back into the full
Newtonian shape equation. The 24 returned homological residuals simplify
exactly to zero. The calculation is deterministic; no floating-point fit is
used to obtain the coefficients.

## Remainder

The contraction theorem in `PLANAR_STABLE_TAIL_ENCLOSURE.md` bounds the full
correction \(E_{\ge5}\) in a weighted coefficient \(\ell^1\) norm. Homogeneous
degrees are disjoint summands in that norm. Removing the exact components of
degrees five through eight therefore cannot increase the remainder norm, and
the new remainder starts in degree nine. If the normalized stable radii are
bounded by \(\lambda<1\), the four bounds used by the verifier become

\[
\begin{aligned}
 |E_{\ge9}|&<\lambda^9/4000000000,\\
 |\mathcal D E_{\ge9}|&<\lambda^9/800000000,\\
 |\partial_\kappa E_{\ge9}|&<\lambda^9/1000000000,\\
 |\partial_\kappa\mathcal D E_{\ge9}|&<\lambda^9/200000000.
\end{aligned}
\]

This is the same coefficient-norm argument used for the quintic sharpening,
now applied three more times. Close encounters do not enter this local
stable-manifold estimate; they are handled later by regularized validated
flows.

The octic graph is currently used only by the fourth-root multiprecision
replay. Earlier published native-double certificates retain their previous
initialization and must replay unchanged.
