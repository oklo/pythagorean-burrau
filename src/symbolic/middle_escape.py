"""Exact pair-{2,3} Levi--Civita terminal escape map for the middle interval.

This module gives pure, deterministic SymPy formulas mapping the pair-{2,3}
Levi--Civita chart of ``src/fable/verification/burrau_lc_certificate_capd.cpp``
(``make_pair23_lc_field``) onto the hypotheses of the terminal binary--escaper
theorem of ``docs/ESCAPE_CRITERIA.md``, specialized to binary ``{2,3}`` with
escaper body ``1``.

Chart conventions (matching the CAPD field exactly):

* normalized masses ``(m1, m2, m3) = (A, B, 1)`` with
  ``A = (1-u^2)/(1+u^2)`` and ``B = 2u/(1+u^2)``;
* ``g = q3 - q2 = w^2`` as a complex square, ``w = wr + i wi``;
* Levi--Civita fictitious time ``sigma`` with ``dt/dsigma = |w|^2`` and
  ``dw/dsigma = z``, hence the physical relative velocity is
  ``dg/dt = 2 w z / |w|^2``;
* pair energy ``hh = E23 = |dg/dt|^2/2 - M/|g| = (2|z|^2 - M)/|w|^2`` with
  the pair mass ``M = m2 + m3 = B + 1``;
* complement ``G = q1 - C23`` with ``C23 = (B q2 + q3)/M``, and ``P = dG/dt``
  exactly (the chart evolves ``dG/dsigma = |w|^2 P``).

Terminal theorem specialization (``docs/ESCAPE_CRITERIA.md`` with
``(a, b, c) = (2, 3, 1)``): the theorem's inner vector is
``x = q_b - q_a = q3 - q2 = g``, its outer vector is
``y = q_c - (m_a q_a + m_b q_b)/M = G``, its pair mass is ``M = B + 1``,
its total mass is ``Mtot = A + B + 1``, its escaper mass is ``m_c = A``,
and its inner specific energy is ``e = E23``.  All quantities are specific
(per unit reduced mass of the relative coordinate); no reduced-mass weight
appears anywhere in the theorem, and none is introduced here.

Nothing in this module is numerical; every function returns exact SymPy
expressions when given exact inputs.
"""

from __future__ import annotations

from dataclasses import dataclass

import sympy as sp

HYPOTHESES = (
    "pair_distance_positive",
    "outer_distance_positive",
    "separation_margin_positive",
    "radial_speed_positive",
    "radial_energy_positive",
    "inner_energy_margin_positive",
)


def mass_A(u):
    """Mass of body 1: A = (1-u^2)/(1+u^2)."""
    u = sp.sympify(u)
    return (1 - u**2) / (1 + u**2)


def mass_B(u):
    """Mass of body 2: B = 2u/(1+u^2)."""
    u = sp.sympify(u)
    return 2 * u / (1 + u**2)


def masses(u):
    """Normalized masses (m1, m2, m3) = (A, B, 1)."""
    return (mass_A(u), mass_B(u), sp.Integer(1))


def pair_mass(u):
    """M = m2 + m3 = B + 1 = (1+u)^2/(1+u^2)."""
    return sp.together(mass_B(u) + 1)


def total_mass(u):
    """Mtot = A + B + 1 = 2(1+u)/(1+u^2)."""
    return sp.together(mass_A(u) + mass_B(u) + 1)


def pair23_relative(positions, velocities, u):
    """Exact physical -> pair-{2,3} relative coordinates.

    ``positions`` and ``velocities`` are sequences of three pairs
    ``(q1, q2, q3)`` and ``(v1, v2, v3)``.  Returns ``(g, gdot, G, P)``,
    each a 2-tuple of exact expressions:

        g = q3 - q2,          gdot = v3 - v2,
        G = q1 - (B q2 + q3)/M,   P = v1 - (B v2 + v3)/M.
    """
    (q1, q2, q3) = tuple(tuple(sp.sympify(c) for c in q) for q in positions)
    (v1, v2, v3) = tuple(tuple(sp.sympify(c) for c in v) for v in velocities)
    b = mass_B(u)
    m = pair_mass(u)
    g = (q3[0] - q2[0], q3[1] - q2[1])
    gdot = (v3[0] - v2[0], v3[1] - v2[1])
    big_g = (
        q1[0] - (b * q2[0] + q3[0]) / m,
        q1[1] - (b * q2[1] + q3[1]) / m,
    )
    p = (
        v1[0] - (b * v2[0] + v3[0]) / m,
        v1[1] - (b * v2[1] + v3[1]) / m,
    )
    return g, gdot, big_g, p


def chart_from_relative(g, gdot):
    """Exact Levi--Civita lift: (g, gdot) -> (w, z), positive-real branch.

    ``w`` is the principal complex square root of ``g`` (Form A of the CAPD
    entry map when ``g_x > 0``), and ``z = conj(w) gdot / 2`` so that
    ``dg/dt = 2 w z/|w|^2``.  Returns ``(wr, wi, zr, zi)``.
    """
    gx, gy = (sp.sympify(g[0]), sp.sympify(g[1]))
    gdx, gdy = (sp.sympify(gdot[0]), sp.sympify(gdot[1]))
    absg = sp.sqrt(gx**2 + gy**2)
    wr = sp.sqrt((absg + gx) / 2)
    wi = gy / (2 * wr)
    zr = (wr * gdx + wi * gdy) / 2
    zi = (wr * gdy - wi * gdx) / 2
    return wr, wi, zr, zi


def relative_from_chart(wr, wi, zr, zi):
    """Exact chart -> relative reconstruction: (w, z) -> (g, gdot).

    ``g = w^2`` and ``gdot = 2 w z / |w|^2`` (undefined at ``w = 0``).
    """
    wr, wi, zr, zi = (sp.sympify(v) for v in (wr, wi, zr, zi))
    w2 = wr**2 + wi**2
    g = (wr**2 - wi**2, 2 * wr * wi)
    gdot = (2 * (wr * zr - wi * zi) / w2, 2 * (wr * zi + wi * zr) / w2)
    return g, gdot


def pair_distance(wr, wi):
    """r = |g| = |w|^2."""
    wr, wi = sp.sympify(wr), sp.sympify(wi)
    return wr**2 + wi**2


def inner_specific_energy_chart(u, wr, wi, zr, zi):
    """E23 = (2|z|^2 - M)/|w|^2, the algebraic chart form of the pair energy.

    Exactly equal to |dg/dt|^2/2 - M/|g| whenever w != 0 (regression-tested
    identity); equals the transported chart variable ``hh`` along the flow.
    """
    wr, wi, zr, zi = (sp.sympify(v) for v in (wr, wi, zr, zi))
    m = pair_mass(u)
    return (2 * (zr**2 + zi**2) - m) / (wr**2 + wi**2)


def inner_specific_energy_relative(u, g, gdot):
    """E23 = |gdot|^2/2 - M/|g| from the relative coordinates directly."""
    gx, gy = sp.sympify(g[0]), sp.sympify(g[1])
    gdx, gdy = sp.sympify(gdot[0]), sp.sympify(gdot[1])
    m = pair_mass(u)
    return (gdx**2 + gdy**2) / 2 - m / sp.sqrt(gx**2 + gy**2)


def outer_distance(Gx, Gy):
    """rho = |G|."""
    Gx, Gy = sp.sympify(Gx), sp.sympify(Gy)
    return sp.sqrt(Gx**2 + Gy**2)


def outer_radial_speed(Gx, Gy, Px, Py):
    """rhodot = G . P / rho (undefined at G = 0)."""
    Gx, Gy, Px, Py = (sp.sympify(v) for v in (Gx, Gy, Px, Py))
    return (Gx * Px + Gy * Py) / outer_distance(Gx, Gy)


@dataclass(frozen=True)
class MiddleEscapeMargins:
    """Exact terminal-escape quantities and the list of failed hypotheses.

    Every field is an exact SymPy expression (or None where a guard failed
    earlier and the quantity is undefined).  ``failed`` lists the failed
    hypothesis names from ``HYPOTHESES`` in evaluation order; ``certified``
    is True iff every strict inequality of the terminal theorem holds.
    """

    u: object
    eta: object
    pair_mass: object
    total_mass: object
    escaper_mass: object
    pair_distance: object
    inner_energy: object
    outer_distance: object
    radial_speed: object
    radius_bound: object
    separation_margin: object
    radial_energy: object
    speed_floor: object
    tidal_allowance: object
    inner_energy_margin: object
    failed: tuple[str, ...]
    certified: bool


def _is_positive(expr) -> bool:
    """Decide strict positivity of an exact expression; fail closed."""
    verdict = sp.sympify(expr).is_positive
    if verdict is None:
        simplified = sp.simplify(expr)
        verdict = simplified.is_positive
        if verdict is None:
            try:
                verdict = bool(simplified > 0)
            except TypeError as exc:  # free symbols: undecidable
                raise ValueError(
                    f"cannot decide sign of {expr}; supply exact numbers"
                ) from exc
    return bool(verdict)


def escape_margins_chart(u, wr, wi, zr, zi, Gx, Gy, Px, Py, eta):
    """Evaluate the terminal escape hypotheses from a pair-{2,3} chart state.

    Implements the theorem of ``docs/ESCAPE_CRITERIA.md`` with
    ``(a, b, c) = (2, 3, 1)``:

        M = B + 1,  Mtot = A + B + 1,  R = M/eta,  d = rho - R,
        E23 = (2|z|^2 - M)/|w|^2,
        rho = |G|,  rhodot = G.P/rho,
        Erho = rhodot^2/2 - Mtot/d,  vinf = sqrt(2 Erho),
        Delta = A sqrt(2 M R) / (vinf d^2),

    and the strict hypotheses ``|w|^2 > 0``, ``rho > 0``, ``d > 0``,
    ``rhodot > 0``, ``Erho > 0``, ``-eta - E23 - Delta > 0``.

    Evaluation is fail-closed and sequential: once a guard fails, all
    later quantities that would divide by it or take its square root are
    left as None and their hypotheses are reported failed.
    """
    u, eta = sp.sympify(u), sp.sympify(eta)
    if not _is_positive(eta):
        raise ValueError("eta must be positive")
    a = mass_A(u)
    m = pair_mass(u)
    mtot = total_mass(u)
    r = pair_distance(wr, wi)
    radius_bound = m / eta
    failed: list[str] = []

    if not _is_positive(r):
        failed.append("pair_distance_positive")
        inner_energy = None
    else:
        inner_energy = inner_specific_energy_chart(u, wr, wi, zr, zi)

    rho_sq = sp.sympify(Gx) ** 2 + sp.sympify(Gy) ** 2
    if not _is_positive(rho_sq):
        failed.append("outer_distance_positive")
        rho = radial_speed = None
    else:
        rho = sp.sqrt(rho_sq)
        radial_speed = (sp.sympify(Gx) * sp.sympify(Px)
                        + sp.sympify(Gy) * sp.sympify(Py)) / rho

    separation_margin = None if rho is None else rho - radius_bound
    if separation_margin is None or not _is_positive(separation_margin):
        failed.append("separation_margin_positive")
        separation_margin_ok = False
    else:
        separation_margin_ok = True

    if radial_speed is None or not _is_positive(radial_speed):
        failed.append("radial_speed_positive")

    if separation_margin_ok:
        radial_energy = radial_speed_sq_half = None
        if radial_speed is not None:
            radial_speed_sq_half = radial_speed**2 / 2
        if radial_speed_sq_half is not None:
            radial_energy = radial_speed_sq_half - mtot / separation_margin
    else:
        radial_energy = None

    if radial_energy is None or not _is_positive(radial_energy):
        failed.append("radial_energy_positive")
        speed_floor = tidal_allowance = inner_energy_margin = None
    else:
        speed_floor = sp.sqrt(2 * radial_energy)
        tidal_allowance = (
            a * sp.sqrt(2 * m * radius_bound)
            / (speed_floor * separation_margin**2)
        )
        if inner_energy is None:
            inner_energy_margin = None
        else:
            inner_energy_margin = -eta - inner_energy - tidal_allowance

    if inner_energy_margin is None or not _is_positive(inner_energy_margin):
        failed.append("inner_energy_margin_positive")

    return MiddleEscapeMargins(
        u=u,
        eta=eta,
        pair_mass=m,
        total_mass=mtot,
        escaper_mass=a,
        pair_distance=r,
        inner_energy=inner_energy,
        outer_distance=rho,
        radial_speed=radial_speed,
        radius_bound=radius_bound,
        separation_margin=separation_margin,
        radial_energy=radial_energy,
        speed_floor=speed_floor if radial_energy is not None else None,
        tidal_allowance=tidal_allowance if radial_energy is not None else None,
        inner_energy_margin=inner_energy_margin,
        failed=tuple(failed),
        certified=not failed,
    )


def escape_margins_physical(positions, velocities, u, eta):
    """Evaluate the same hypotheses from exact physical (q_i, v_i).

    Builds the pair-{2,3} relative coordinates, lifts to the chart, and
    delegates to ``escape_margins_chart``; by the tested identities the
    result equals the direct physical evaluation of the theorem.
    """
    g, gdot, big_g, p = pair23_relative(positions, velocities, u)
    wr, wi, zr, zi = chart_from_relative(g, gdot)
    return escape_margins_chart(
        u, wr, wi, zr, zi, big_g[0], big_g[1], p[0], p[1], eta
    )


def symbolic_margin_expressions(eta=None):
    """Free-symbol margin expressions for translation into CAPD intervals.

    Returns ``(symbols, expressions)`` where ``symbols`` is the tuple
    ``(u, wr, wi, zr, zi, Gx, Gy, Px, Py)`` and ``expressions`` maps each
    quantity name to an exact SymPy expression in those symbols.  Square
    roots appear only for quantities whose positivity is a hypothesis of
    the theorem (rho, vinf); a CAPD transcription must verify those
    hypotheses before evaluating the roots (fail closed).
    """
    u, wr, wi, zr, zi = sp.symbols("u w_r w_i z_r z_i", real=True)
    gx, gy, px, py = sp.symbols("G_x G_y P_x P_y", real=True)
    eta_expr = sp.Symbol("eta", positive=True) if eta is None else sp.sympify(eta)
    a = mass_A(u)
    m = pair_mass(u)
    mtot = total_mass(u)
    r = pair_distance(wr, wi)
    e23 = inner_specific_energy_chart(u, wr, wi, zr, zi)
    rho = sp.sqrt(gx**2 + gy**2)
    rhodot = (gx * px + gy * py) / rho
    radius = m / eta_expr
    d = rho - radius
    erho = rhodot**2 / 2 - mtot / d
    vinf = sp.sqrt(2 * erho)
    delta = a * sp.sqrt(2 * m * radius) / (vinf * d**2)
    margin = -eta_expr - e23 - delta
    symbols = (u, wr, wi, zr, zi, gx, gy, px, py)
    expressions = {
        "mass_A": a,
        "mass_B": mass_B(u),
        "pair_mass": m,
        "total_mass": mtot,
        "pair_distance": r,
        "inner_energy": e23,
        "outer_distance": rho,
        "radial_speed": rhodot,
        "radius_bound": radius,
        "separation_margin": d,
        "radial_energy": erho,
        "speed_floor": vinf,
        "tidal_allowance": delta,
        "inner_energy_margin": margin,
    }
    return symbols, expressions
