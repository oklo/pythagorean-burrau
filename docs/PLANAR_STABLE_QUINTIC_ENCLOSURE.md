# Quintic sharpening of the planar stable-tail enclosure

Status: **PROVED ANALYTICALLY** for the homological reduction and remainder
bound; **EXACT SYMBOLIC IDENTITY** for the six displayed coefficients.

This note sharpens `PLANAR_STABLE_TAIL_ENCLOSURE.md` without changing the
stable family represented there.  Write its normalized stable graph as

\[
 P=P_4+E,\qquad E=E_5+E_{\ge6},
\]

where the subscript denotes total degree in the stable parameters \((p,\nu)\).
Reflection in the vertical axis makes the horizontal coordinate odd in
\(p\) and the vertical offset even in \(p\).  Consequently

\[
\begin{aligned}
 E_5^x&=M p^5+N p^3\nu^2+O p\nu^4,\\
 E_5^q&=P p^4\nu+Q p^2\nu^3+R\nu^5.
\end{aligned}
\tag{1}
\]

Let

\[
 a_T={1+\sqrt7\over6},\qquad a_L={1+\sqrt{19}\over6}.
\]

On a monomial \(p^i\nu^j\), the stable-tail derivative is multiplication by
\(-\lambda_{ij}\), where \(\lambda_{ij}=ia_T+ja_L\).  The two diagonal
homological divisors are

\[
 \lambda_{ij}^2-\frac13\lambda_{ij}-\frac16
 \quad\hbox{and}\quad
 \lambda_{ij}^2-\frac13\lambda_{ij}-\frac12.
\tag{2}
\]

Applying their exact inverses to the degree-five defect of \(P_4\) gives

\[
\begin{aligned}
M={}&{139388-52377\sqrt7\over22656},\\
N={}&{-774477456573583-138316082351786\sqrt{19}
 +233813248132331\sqrt7+65671343849527\sqrt{133}
 \over3414727782720},\\
O={}&{-12013435545841763\sqrt{133}-29654748827119993\sqrt7
 +11068114004318700\sqrt{19}+201875601915437169
 \over116407941497942400},\\
P={}&{-2922965759\sqrt{133}-12051945556\sqrt7+31581467405
 +7786167931\sqrt{19}\over360298368},\\
Q={}&{-69108245795306\sqrt7-4224822501153\sqrt{133}+57183552400781
 +40730719418703\sqrt{19}\over4898087246400},\\
R={}&{-2131571208+209218965\sqrt{19}\over35984892800}.
\end{aligned}
\tag{3}
\]

The exact signs are \((+,-,+,-,+,-)\).  Substitution of (3) into (2)
cancels all six degree-five defect coefficients exactly.  This calculation is
implemented by
`planar_joint_shape_stable_quintic_correction()` and regression-tested in
`tests/test_restricted_scattering.py`.

## Remainder bound

The earlier contraction theorem proves on the half polydisc

\[
 \|E\|<\frac1{4000000000},\qquad
 \|\mathcal DE\|<\frac1{800000000},
\tag{4}
\]

together with the corresponding parameter-tangent bounds
\(10^{-9}\) and \((2\cdot10^8)^{-1}\).  These are weighted coefficient
\(\ell^1\) norms.  Homogeneous degrees are disjoint summands in that norm, so
removing the exact degree-five part cannot increase any of the four norms.
Moreover, every monomial of \(E_{\ge6}\) has total degree at least six.
Therefore, at a point whose two normalized radii are at most \(\lambda<1\),

\[
\begin{aligned}
 |E_{\ge6}|&<\lambda^6/4000000000,\\
 |\mathcal D E_{\ge6}|&<\lambda^6/800000000,\\
 |\partial_\kappa E_{\ge6}|&<\lambda^6/1000000000,\\
 |\partial_\kappa\mathcal D E_{\ge6}|&<\lambda^6/200000000.
\end{aligned}
\tag{5}
\]

At \(\zeta=15\), the verifier uses

\[
 \lambda=\max\{400e^{-15a_T},6500e^{-15a_L}\}<0.04403.
\]

Thus (5) improves the independent stable-tail boxes by an additional factor
below \(0.04403\).  The CAPD verifier uses the quintic graph only in the new
fully correlated fifth-passage stage; all earlier pinned certificates retain
their original quartic initialization, and their pinned numerical interval
fields reproduce unchanged.

This sharpening is not itself a nonperiodicity theorem.  Its role is to make
the exact stable graph sufficiently thin for a long correlation-preserving
validated continuation.
