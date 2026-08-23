"""Ordinary-precision event atlas for one tied trajectory.

For a given Euclid parameter this module integrates the normalized tied
free-fall problem, refines every zero of ``dI/dt``, records the brake-event
scalars there, and reports the first time at which the terminal
binary--escaper certificate of ``docs/ESCAPE_CRITERIA.md`` fires for some
labelling.  All output is ORDINARY NUMERICAL EVIDENCE used to design the
validated certificate; nothing here is a proof.
"""

from __future__ import annotations

from dataclasses import dataclass

import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import brentq

from src.dynamics.cartesian import (
    energy,
    initial_state_real,
    mutual_distances,
    right_hand_side,
)
from src.dynamics.escape_certificate import evaluate_escape_certificate
from src.fable.events import (
    EventRecord,
    event_record,
    initial_potential,
    moment_derivative,
)

PAIRINGS = ((0, 1, 2), (1, 2, 0), (2, 0, 1))


@dataclass(frozen=True)
class CertificateHit:
    time: float
    binary: tuple[int, int]
    escaper: int
    eta: float
    inner_energy_margin: float


@dataclass(frozen=True)
class AtlasResult:
    u: float
    events: list[EventRecord]
    certificate: CertificateHit | None
    end_time: float
    min_separation: float
    max_relative_energy_error: float


def certificate_scan(
    state: np.ndarray, masses: np.ndarray, etas: tuple[float, ...]
) -> CertificateHit | None:
    positions = state[:6].reshape(3, 2)
    velocities = state[6:].reshape(3, 2)
    for a, b, c in PAIRINGS:
        pair_mass = masses[a] + masses[b]
        inner = positions[b] - positions[a]
        inner_velocity = velocities[b] - velocities[a]
        center = (masses[a] * positions[a] + masses[b] * positions[b]) / pair_mass
        center_velocity = (
            masses[a] * velocities[a] + masses[b] * velocities[b]
        ) / pair_mass
        outer = positions[c] - center
        outer_velocity = velocities[c] - center_velocity
        for eta in etas:
            result = evaluate_escape_certificate(
                masses[a],
                masses[b],
                masses[c],
                inner,
                inner_velocity,
                outer,
                outer_velocity,
                eta,
            )
            if result.certified:
                return CertificateHit(
                    time=float("nan"),
                    binary=(a, b),
                    escaper=c,
                    eta=eta,
                    inner_energy_margin=result.inner_energy_margin,
                )
    return None


def run_atlas(
    u: float,
    max_time: float = 40.0,
    rtol: float = 1e-12,
    atol: float = 1e-14,
    max_step: float = 0.01,
    certificate_interval: float = 0.25,
    etas: tuple[float, ...] = (0.5, 1.0, 2.0, 4.0),
) -> AtlasResult:
    masses, state0 = initial_state_real(u)
    u_potential_0 = initial_potential(u)
    initial_energy = energy(state0, masses)

    solution = solve_ivp(
        right_hand_side,
        (0.0, max_time),
        state0,
        args=(masses,),
        method="DOP853",
        dense_output=True,
        rtol=rtol,
        atol=atol,
        max_step=max_step,
    )

    times = solution.t
    events: list[EventRecord] = []
    min_separation = float("inf")
    max_energy_error = 0.0
    certificate: CertificateHit | None = None
    next_certificate_time = certificate_interval

    def derivative(time: float) -> float:
        return moment_derivative(solution.sol(time), masses)

    previous_time = times[0]
    previous_value = derivative(previous_time)
    # Uniform scan grid finer than the shortest observed I-oscillation.
    scan_step = min(0.005, max_step)
    scan_times = np.arange(times[0] + scan_step, times[-1], scan_step)
    for time in scan_times:
        state = solution.sol(time)
        separations = mutual_distances(state)
        min_separation = min(min_separation, float(np.min(separations)))
        energy_error = abs(
            (energy(state, masses) - initial_energy) / initial_energy
        )
        max_energy_error = max(max_energy_error, float(energy_error))

        value = derivative(time)
        if previous_value == 0.0 or value * previous_value < 0:
            root = brentq(derivative, previous_time, time, xtol=1e-13)
            events.append(
                event_record(root, solution.sol(root), masses, u_potential_0)
            )
        previous_time, previous_value = time, value

        if certificate is None and time >= next_certificate_time:
            next_certificate_time += certificate_interval
            hit = certificate_scan(state, masses, etas)
            if hit is not None:
                certificate = CertificateHit(
                    time=float(time),
                    binary=hit.binary,
                    escaper=hit.escaper,
                    eta=hit.eta,
                    inner_energy_margin=hit.inner_energy_margin,
                )
                break

    return AtlasResult(
        u=u,
        events=events,
        certificate=certificate,
        end_time=float(previous_time),
        min_separation=min_separation,
        max_relative_energy_error=max_energy_error,
    )
