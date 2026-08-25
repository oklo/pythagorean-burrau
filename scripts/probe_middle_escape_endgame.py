"""Ordinary-precision reconnaissance of the middle-interval escape endgame.

Maps the event/section topology of the tied trajectory for Euclid
parameters near u = 0.29 through the first firing of the pair-{2,3}
eta = 4 terminal escape certificate, to design the validated endgame of
the interval program.  Everything printed here is ORDINARY NUMERICAL
EVIDENCE for proof design; nothing is a proof, and no interval or
nonperiodicity claim may be inferred from it.

Usage:
    python scripts/probe_middle_escape_endgame.py [--fast]
"""

from __future__ import annotations

import argparse
from dataclasses import dataclass

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import brentq

from src.dynamics.cartesian import energy, initial_state_real, mutual_distances, right_hand_side
from src.dynamics.escape_certificate import evaluate_escape_certificate
from src.fable.events import (
    event_record,
    initial_potential,
    moment_derivative,
)

PAIR_LABELS = {0: "{1,2}", 1: "{2,3}", 2: "{1,3}"}
ETA = 4.0
T_MAX = 6.0
SCAN_STEP = 0.002
# Candidate rational section values for the pair-{1,3} outgoing leg.
WR_SECTION_VALUES = (0.0, -1 / 5, -3 / 10, -2 / 5, -1 / 2, -3 / 5)


def split(state: np.ndarray) -> tuple[np.ndarray, np.ndarray]:
    return state[:6].reshape(3, 2), state[6:].reshape(3, 2)


def pair23_jacobi(state: np.ndarray, masses: np.ndarray):
    """(g, gdot, G, P) for binary {2,3}, escaper 1 (0-indexed bodies 1,2)."""
    q, v = split(state)
    pair_mass = masses[1] + masses[2]
    g = q[2] - q[1]
    gdot = v[2] - v[1]
    center = (masses[1] * q[1] + masses[2] * q[2]) / pair_mass
    center_v = (masses[1] * v[1] + masses[2] * v[2]) / pair_mass
    return g, gdot, q[0] - center, v[0] - center_v


def pair13_relative(state: np.ndarray):
    """(g, gdot) for the pair-{1,3} chart: g = q3 - q1."""
    q, v = split(state)
    return q[2] - q[0], v[2] - v[0]


def pair23_certificate(state: np.ndarray, masses: np.ndarray):
    g, gdot, big_g, p = pair23_jacobi(state, masses)
    return evaluate_escape_certificate(
        masses[1], masses[2], masses[0], g, gdot, big_g, p, ETA
    )


@dataclass
class SectionCrossing:
    kind: str  # "wr" or "zr"
    value: float
    time: float
    sigma_speed: float  # d(section fn)/d sigma
    time_speed: float  # d(section fn)/dt
    w_norm_sq: float
    min_separation: float
    state: np.ndarray


def track_lc_branch(g_values: np.ndarray) -> np.ndarray:
    """Continuous complex square-root branch along a dense sampling."""
    w = np.empty(len(g_values), dtype=complex)
    w[0] = np.sqrt(g_values[0])
    for k in range(1, len(g_values)):
        candidate = np.sqrt(g_values[k])
        if abs(candidate - w[k - 1]) > abs(candidate + w[k - 1]):
            candidate = -candidate
        w[k] = candidate
    return w


def probe_one(u: float, rtol: float = 1e-12, atol: float = 1e-14) -> dict:
    masses, state0 = initial_state_real(u)
    u0 = initial_potential(u)
    e0 = energy(state0, masses)
    solution = solve_ivp(
        right_hand_side,
        (0.0, T_MAX),
        state0,
        args=(masses,),
        method="DOP853",
        dense_output=True,
        rtol=rtol,
        atol=atol,
        max_step=0.01,
    )

    def deriv(t: float) -> float:
        return moment_derivative(solution.sol(t), masses)

    # 1. Certificate firing time (earliest pair-{2,3} eta=4 firing).
    fire_time = None
    grid = np.arange(2.5, T_MAX, 0.005)
    for t in grid:
        if pair23_certificate(solution.sol(t), masses).certified:
            lo = t - 0.005
            hi = t
            for _ in range(40):
                mid = 0.5 * (lo + hi)
                if pair23_certificate(solution.sol(mid), masses).certified:
                    hi = mid
                else:
                    lo = mid
            fire_time = hi
            break
    horizon = fire_time if fire_time is not None else T_MAX

    # 2. Every zero of J = dI/dt before the certificate fires.
    events = []
    ts = np.arange(SCAN_STEP, horizon, SCAN_STEP)
    prev_t, prev_v = 0.0, deriv(1e-9)
    max_energy_error = 0.0
    for t in ts:
        state = solution.sol(t)
        max_energy_error = max(
            max_energy_error, abs((energy(state, masses) - e0) / e0)
        )
        value = deriv(t)
        if value * prev_v < 0:
            root = brentq(deriv, prev_t, t, xtol=1e-13)
            record = event_record(root, solution.sol(root), masses, u0)
            separations = mutual_distances(solution.sol(root))
            events.append((record, PAIR_LABELS[int(np.argmin(separations))]))
        prev_t, prev_v = t, value

    # 3. Pair-{1,3} LC section crossings on [1.5, horizon].
    dense_t = np.arange(1.5, horizon, SCAN_STEP)
    g13 = np.empty(len(dense_t), dtype=complex)
    g13dot = np.empty(len(dense_t), dtype=complex)
    for k, t in enumerate(dense_t):
        g, gdot = pair13_relative(solution.sol(t))
        g13[k] = complex(g[0], g[1])
        g13dot[k] = complex(gdot[0], gdot[1])
    w13 = track_lc_branch(g13)
    z13 = np.conj(w13) * g13dot / 2

    crossings: list[SectionCrossing] = []

    def refine(series: np.ndarray, target: float, kind: str) -> None:
        shifted = series - target
        for k in range(1, len(shifted)):
            if shifted[k - 1] * shifted[k] < 0:
                frac = shifted[k - 1] / (shifted[k - 1] - shifted[k])
                t_cross = dense_t[k - 1] + frac * SCAN_STEP
                state = solution.sol(t_cross)
                g, gdot = pair13_relative(state)
                gc = complex(g[0], g[1])
                w = np.sqrt(gc)
                ref = w13[k - 1] + frac * (w13[k] - w13[k - 1])
                if abs(w - ref) > abs(w + ref):
                    w = -w
                z = np.conj(w) * complex(gdot[0], gdot[1]) / 2
                w2 = abs(w) ** 2
                if kind == "wr":
                    sigma_speed = z.real
                else:  # zr section: z' = (h/2) wr + (|w|^2/2)(w conj f)_r
                    dt_local = 1e-6
                    zs = []
                    for t_eval in (t_cross - dt_local, t_cross + dt_local):
                        gg, gd = pair13_relative(solution.sol(t_eval))
                        wv = np.sqrt(complex(gg[0], gg[1]))
                        if abs(wv - w) > abs(wv + w):
                            wv = -wv
                        zs.append((np.conj(wv) * complex(gd[0], gd[1]) / 2).real)
                    sigma_speed = (zs[1] - zs[0]) / (2 * dt_local) * w2
                crossings.append(
                    SectionCrossing(
                        kind=kind,
                        value=target,
                        time=float(t_cross),
                        sigma_speed=float(sigma_speed),
                        time_speed=float(sigma_speed / w2),
                        w_norm_sq=float(w2),
                        min_separation=float(
                            np.min(mutual_distances(state))
                        ),
                        state=state,
                    )
                )

    for value in WR_SECTION_VALUES:
        refine(w13.real, value, "wr")
    refine(z13.real, 0.0, "zr")

    # 4. Pair-{2,3} certificate margins at simple rational times.
    rational_times = [
        (num, den)
        for den in (1, 2, 4)
        for num in range(int(3 * den), int(5 * den) + 1)
    ]
    margin_table = []
    for num, den in sorted(set(rational_times), key=lambda p: p[0] / p[1]):
        t = num / den
        if t >= T_MAX:
            continue
        cert = pair23_certificate(solution.sol(t), masses)
        margin_table.append((num, den, cert))

    # 5. Chart-switch window diagnostics: pair distances on [3.3, 3.9].
    switch = []
    for t in np.arange(3.3, min(3.95, horizon + 0.4), 0.05):
        state = solution.sol(t)
        separations = mutual_distances(state)
        g, gdot, big_g, p = pair23_jacobi(state, masses)
        switch.append(
            (
                t,
                separations,
                float(np.linalg.norm(g)),
                float(np.linalg.norm(big_g)),
                float(np.dot(big_g, p) / np.linalg.norm(big_g)),
            )
        )

    # 6. Form-B pair-{2,3} LC coordinates after the exchange.  This is
    # ordinary reconnaissance for choosing transverse geometric sections;
    # the validated driver must prove every crossing and cover its tube.
    pair23_lc = []
    previous_w: complex | None = None
    for t in (3.48, 3.50, 3.51, 3.517, 3.52, 3.54, 3.56, 3.58,
              3.60, 3.62, 3.64, 3.66, 3.68, 3.70, 3.75, 3.80):
        g, gdot, _, _ = pair23_jacobi(solution.sol(t), masses)
        gc = complex(g[0], g[1])
        root = np.sqrt(gc)
        if previous_w is None:
            if root.imag < 0:
                root = -root
        elif abs(root - previous_w) > abs(root + previous_w):
            root = -root
        previous_w = root
        z = np.conj(root) * complex(gdot[0], gdot[1]) / 2
        radius_sigma = 2 * (np.conj(root) * z).real
        pair23_lc.append((t, root, z, radius_sigma))

    dense_pair23_t = np.arange(3.48, 3.821, 0.0002)
    dense_pair23_w = np.empty(len(dense_pair23_t), dtype=complex)
    previous_w = None
    for index, t in enumerate(dense_pair23_t):
        g, _, _, _ = pair23_jacobi(solution.sol(t), masses)
        root = np.sqrt(complex(g[0], g[1]))
        if previous_w is None:
            if root.imag < 0:
                root = -root
        elif abs(root - previous_w) > abs(root + previous_w):
            root = -root
        dense_pair23_w[index] = root
        previous_w = root
    pair23_wr_crossings = []
    for level in (-0.15, -0.10, -0.05, 0.0, 0.05, 0.10, 0.15):
        shifted = dense_pair23_w.real - level
        for index in range(1, len(shifted)):
            if shifted[index - 1] * shifted[index] < 0:
                fraction = shifted[index - 1] / (shifted[index - 1] - shifted[index])
                crossing_time = dense_pair23_t[index - 1] + 0.0002 * fraction
                direction = "+" if shifted[index] > shifted[index - 1] else "-"
                pair23_wr_crossings.append((crossing_time, level, direction))
    pair23_wr_crossings.sort()

    itinerary = tuple(
        ("max" if record.is_maximum else "min", closest)
        for record, closest in events
    )
    return {
        "u": u,
        "events": events,
        "fire_time": fire_time,
        "margin_table": margin_table,
        "crossings": crossings,
        "switch": switch,
        "pair23_lc": pair23_lc,
        "pair23_wr_crossings": pair23_wr_crossings,
        "itinerary": itinerary,
        "max_energy_error": max_energy_error,
    }


def report(result: dict, verbose: bool) -> None:
    u = result["u"]
    print(f"\n=== u = {u:.6f} ===")
    print(f"max relative energy error: {result['max_energy_error']:.2e}")
    fire = result["fire_time"]
    print(f"pair-{{2,3}} eta=4 certificate first fires at t = "
          f"{fire:.6f}" if fire else "certificate did not fire before T_MAX")
    print("events (zeros of J = dI/dt) before firing:")
    for record, closest in result["events"]:
        kind = "max" if record.is_maximum else "min"
        print(
            f"  t={record.time:.8f} {kind}  U-2U0 sign="
            f"{'+' if record.potential_ratio > 2 else '-'}"
            f"  K={record.kinetic:.6f}  |zeta|={record.zeta_abs:.6f}"
            f"  |B|={record.residual_norm:.6f}"
            f"  min_sep={record.min_separation:.6f}  closest={closest}"
        )
    if verbose:
        print("pair-{1,3} LC section crossings:")
        for c in result["crossings"]:
            print(
                f"  {c.kind}={c.value:+.2f} at t={c.time:.6f}"
                f"  d/dsigma={c.sigma_speed:+.6f}  d/dt={c.time_speed:+.6f}"
                f"  |w|^2={c.w_norm_sq:.6f}  min_sep={c.min_separation:.6f}"
            )
        print("terminal margins at simple rational times:")
        for num, den, cert in result["margin_table"]:
            status = "PASS" if cert.certified else "fail"
            print(
                f"  t={num}/{den}={num / den:.3f} [{status}]"
                f" d={cert.separation_margin:+.4f}"
                f" rhodot={cert.outward_radial_speed:+.4f}"
                f" Erho={cert.radial_energy_margin:+.4f}"
                f" margin={cert.inner_energy_margin:+.4f}"
            )
        print("chart-switch window (t, r12, r23, r13, |g23|, rho, rhodot):")
        for t, seps, gnorm, rho, rhodot in result["switch"]:
            print(
                f"  t={t:.2f} r12={seps[0]:.4f} r23={seps[1]:.4f}"
                f" r13={seps[2]:.4f} |g23|={gnorm:.4f} rho={rho:.4f}"
                f" rhodot={rhodot:+.4f}"
            )
        print("pair-{2,3} Form-B LC reconnaissance (t, w, z, d|w|^2/dsigma):")
        for t, w, z, radius_sigma in result["pair23_lc"]:
            print(
                f"  t={t:.3f} w=({w.real:+.6f},{w.imag:+.6f})"
                f" z=({z.real:+.6f},{z.imag:+.6f})"
                f" r_sigma={radius_sigma:+.6f}"
            )
        print("pair-{2,3} candidate wr crossings (ordinary linear interpolation):")
        for t, level, direction in result["pair23_wr_crossings"]:
            print(f"  t={t:.6f} wr={level:+.2f} direction={direction}")


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--fast", action="store_true",
                        help="midpoint u = 0.29 only")
    args = parser.parse_args()

    print("ORDINARY NUMERICAL EVIDENCE (design only; not a proof)")

    if args.fast:
        grid = [0.29]
    else:
        grid = sorted(
            {round(0.2895 + k * 1e-4, 6) for k in range(11)} | {0.29}
        )

    results = []
    for u in grid:
        result = probe_one(u)
        results.append(result)
        report(result, verbose=abs(u - 0.29) < 1e-12 or args.fast)

    # Tolerance refinement check at the midpoint.
    midpoint = next(r for r in results if abs(r["u"] - 0.29) < 1e-12)
    refined = probe_one(0.29, rtol=1e-13, atol=1e-15)
    if midpoint["fire_time"] and refined["fire_time"]:
        drift = abs(midpoint["fire_time"] - refined["fire_time"])
        print(f"\nmidpoint tolerance refinement: firing-time drift {drift:.2e}")
    paired = zip(midpoint["events"], refined["events"], strict=False)
    event_drift = max(
        (abs(a[0].time - b[0].time) for a, b in paired), default=float("nan")
    )
    print(f"midpoint event-time drift under refinement: {event_drift:.2e}")

    if len(results) > 1:
        print("\nitinerary stability across the u grid:")
        reference = midpoint["itinerary"]
        stable = [r["u"] for r in results if r["itinerary"] == reference]
        for r in results:
            marker = "same" if r["itinerary"] == reference else "DIFFERS"
            fire = r["fire_time"]
            fire_text = f"{fire:.4f}" if fire else "none"
            print(
                f"  u={r['u']:.6f} events={len(r['itinerary'])}"
                f" fire={fire_text} [{marker}]"
            )
        if stable:
            print(
                f"widest same-itinerary subinterval observed: "
                f"[{min(stable):.6f}, {max(stable):.6f}]"
            )
        # Parameter amplification at the first wr=0 crossing.
        wr0 = {}
        for r in results:
            for c in r["crossings"]:
                if c.kind == "wr" and c.value == 0.0:
                    wr0[r["u"]] = c
                    break
        us = sorted(wr0)
        if len(us) >= 2:
            print("parameter amplification at first pair-{1,3} wr=0 crossing:")
            for u_lo, u_hi in zip(us, us[1:], strict=False):
                du = u_hi - u_lo
                dstate = np.linalg.norm(
                    wr0[u_hi].state - wr0[u_lo].state
                )
                dt_cross = abs(wr0[u_hi].time - wr0[u_lo].time)
                print(
                    f"  [{u_lo:.6f},{u_hi:.6f}] |dstate/du|={dstate / du:.3e}"
                    f" |dt/du|={dt_cross / du:.3e}"
                )

    print("\nORDINARY NUMERICAL EVIDENCE only; see docs/FABLE_MIDDLE_ESCAPE.md"
          " for what a proof requires.")


if __name__ == "__main__":
    main()
