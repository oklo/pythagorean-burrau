# Computer-assisted finite transversality sign

This note proves the finite sign left open in
`RESTRICTED_TRANSVERSALITY.md`. The analytic compactification and tangent
argument that turn this sign into restricted stable/unstable transversality
are proved in `PARABOLIC_MANIFOLD.md`.

## The regularized initial-value problem

Let
\[
r=\cos^2\psi,\qquad
\theta={\psi+\sin\psi\cos\psi\over2},
\qquad {d\theta\over d\psi}=r.
\]
The first binary collision is the regular endpoint $\psi=\pi/2$, corresponding
to $\theta=\pi/4$. For launch speed $v>0$, put $q=h/v$ and introduce
\[
w={dz\over d\theta},\qquad p={dq\over d\theta},\qquad
d^2=z^2+{r^2\over4}.
\]
Then the base orbit and normalized homogeneous Jacobi field solve
\[
\begin{aligned}
z_\psi&=rw,&
w_\psi&=-{2zr\over d^3},\\
q_\psi&=rp,&
p_\psi&=r{4z^2-r^2/2\over d^5}q,
\end{aligned}
\tag{1}
\]
with
\[
(z,w,q,p)(0)=(0,v,1,0).
\tag{2}
\]
Although $r=0$ at the endpoint, $z$ is strictly positive there, so (1) is
regular on the entire compact integration interval.

## Validated theorem

**Theorem (computer-assisted).** For every
\[
v\in[14/5,4],
\]
the solution of (1)--(2) exists through $\psi=\pi/2$ and satisfies
\[
\boxed{p(\pi/2)>\frac1{125}.}
\tag{3}
\]
Consequently, at the parabolic separatrix speed $v_*$,
\[
h'(\pi/4)=v_*p(\pi/2)>{14\over625}>0.
\tag{4}
\]

Here primes in (4) denote physical restricted time $\theta$. The previously
proved analytic bracket $\sqrt8<v_*<4$, together with
$14/5<\sqrt8$, places $v_*$ strictly inside the validated cover.

## Certificate

The verifier uses CAPD 6.1.0 native outward-rounded intervals and its rigorous
Taylor ODE solver with `C0Rect2Set` doubletons. It divides the rational cover
into 256 overlapping interval slabs. Each slab is propagated independently
at Taylor order 20, with relative and absolute local-error targets $10^{-14}$.
The overlap is constructed from interval-valued endpoints, so directed
rounding cannot leave a gap.

Every final interval had lower endpoint greater than $1/125$. The verifier
prints all interval endpoints in exact hexadecimal floating-point notation,
avoiding any inward rounding by decimal display. The global derivative
endpoints were
```
[0x1.0a9761ba17394p-7,0x1.b1c4b5182fa3ap-7]
```
and the smallest lower endpoint occurred on the final slab. Its velocity and
derivative endpoints were
```
[0x1.ff66666666665p+1,0x1.0000000000001p+2]
[0x1.0a9761ba17394p-7,0x1.0ebd12ea31746p-7]
```
The one-ulp extension beyond $4$ is deliberate outward rounding and only
strengthens the cover. The proof uses the exact rational comparison
$p>1/125$, not a printed decimal approximation.

The proof artifacts are:

- `src/verification/restricted_transversality_capd.cpp`: complete verifier;
- `scripts/run_capd_restricted_transversality.sh`: dependency-pin and build
  wrapper;
- `data/restricted_transversality_capd_certificate.txt`: machine, compiler,
  dependency, command, and concise output;
- `src/symbolic/restricted_scattering.py`: independently testable symbolic
  form of (1).

The pinned CAPD source is commit
`731079217a9254ea2948d742df2b170895effe7f`, which reports version 6.1.0.
CAPD documents its interval-set ODE facilities as rigorous enclosure methods;
the verifier uses the interval `IMap`, `IOdeSolver`, `ITimeMap`, and
`C0Rect2Set` interfaces, rather than the similarly named nonrigorous types.

## Reproduction

```bash
git clone https://github.com/CAPDGroup/CAPD.git /path/to/CAPD
git -C /path/to/CAPD checkout 731079217a9254ea2948d742df2b170895effe7f
cmake -S /path/to/CAPD -B /path/to/CAPD/build-native \
  -DCMAKE_BUILD_TYPE=Release -DCAPD_INTERVAL_TYPE=NATIVE
cmake --build /path/to/CAPD/build-native -j 4
sh scripts/run_capd_restricted_transversality.sh \
  /path/to/CAPD /path/to/CAPD/build-native
```

Setting `CAPD_VERBOSE=1` prints the velocity and derivative enclosure for all
256 slabs. The recorded run used Apple clang 21.0.0 on arm64 Darwin 25.5.0.

The trusted computing base consists of the verifier source, the pinned CAPD
implementation, the C++ compiler and standard library, the native directed-
rounding implementation, and the hardware floating-point behavior. A second
implementation would reduce this base but is not logically required for the
current evidence label. The wrapper verifies the CAPD source commit, tracked-
tree cleanliness, and required native-rounding compiler flags. It cannot
cryptographically prove that an arbitrary pre-existing build directory was
compiled from that tree; the recorded certificate used the clean configure-
and-build sequence shown above. A hermetic rebuild would strengthen provenance
without changing the mathematical enclosure.

## Analytic implication

The remaining implication is now closed in `PARABOLIC_MANIFOLD.md`.
After $z=2/x^2$, the eccentric-anomaly vector field is analytic at infinity
and through binary collision. Its time-$\pi$ map satisfies McGehee's explicit
degree-four sector hypotheses. Tangent vectors along the resulting parabolic
stable curve contract in $x$, whereas (4), positivity of $h$, and $a>0$ force
the fixed-phase tangent $\delta x=-x^3h/4$ to stay bounded away from zero.
This contradiction proves that the incoming and outgoing restricted
parabolic curves cross transversely.

Status of (3)--(4) and the resulting restricted transversality theorem:
**PROVED BY COMPUTER-ASSISTED ARGUMENT**. This remains an auxiliary limiting
theorem; finite-$B$ phase matching and second-brake exclusion are open.
