"""Scout early maximum-event branch images in the complex brake plane.

The output is ordinary numerical evidence.  It is designed to locate a real
second-brake intersection, or to identify a branch separation suitable for a
later interval/analytic proof; it is not a finite-scan nonperiodicity claim.
Maxima are grouped by their time ordinal.  That ordinal is not a continued
branch label and can change when an event pair is created, so the broad scan
is only a scout.  The two refinements use brackets where the selected ordinal
was separately checked to persist.
"""

from __future__ import annotations

import sys
from dataclasses import dataclass
from pathlib import Path

import numpy as np
from scipy.optimize import minimize_scalar

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

from src.fable.atlas import run_atlas  # noqa: E402


@dataclass(frozen=True)
class BranchPoint:
    u: float
    time: float
    zeta: complex
    residual: float
    min_separation: float


def segment_origin_distance(left: complex, right: complex) -> tuple[float, float]:
    delta = right - left
    denominator = delta.real**2 + delta.imag**2
    if denominator == 0:
        return abs(left), 0.0
    parameter = -(
        left.real * delta.real + left.imag * delta.imag
    ) / denominator
    parameter = min(1.0, max(0.0, parameter))
    return abs(left + parameter * delta), parameter


def main() -> None:
    parameters = np.linspace(0.2, np.sqrt(2.0) - 1.0, 33)
    branches: dict[int, list[BranchPoint]] = {}
    for u in parameters:
        result = run_atlas(
            float(u),
            max_time=4.0,
            rtol=3e-12,
            atol=3e-14,
            max_step=0.003,
            certificate_interval=5.0,
        )
        maxima = [
            event
            for event in result.events
            if event.is_maximum and event.time > 1e-8
        ]
        print(
            "status=ORDINARY_NUMERICAL_EVIDENCE "
            f"u={u:.12g} maxima={len(maxima)} "
            f"end_time={result.end_time:.8g} "
            f"min_separation={result.min_separation:.8g}",
            flush=True,
        )
        for index, event in enumerate(maxima):
            branches.setdefault(index, []).append(
                BranchPoint(
                    u=float(u),
                    time=event.time,
                    zeta=complex(event.zeta_real, event.zeta_imag),
                    residual=event.residual_norm,
                    min_separation=event.min_separation,
                )
            )

    for index, points in sorted(branches.items()):
        closest_point = min(points, key=lambda point: abs(point.zeta))
        closest_segment: tuple[float, BranchPoint, BranchPoint, float] | None = None
        for left, right in zip(points, points[1:], strict=False):
            if right.u - left.u > 1.01 * (parameters[1] - parameters[0]):
                continue
            distance, parameter = segment_origin_distance(left.zeta, right.zeta)
            candidate = (distance, left, right, parameter)
            if closest_segment is None or candidate[0] < closest_segment[0]:
                closest_segment = candidate
        if closest_segment is None:
            continue
        distance, left, right, parameter = closest_segment
        interpolated_u = left.u + parameter * (right.u - left.u)
        print(
            "event_ordinal_summary=ORDINARY_NUMERICAL_EVIDENCE "
            f"event_ordinal={index + 1} samples={len(points)} "
            f"closest_sample_u={closest_point.u:.12g} "
            f"closest_sample_t={closest_point.time:.9g} "
            f"closest_sample_abs_zeta={abs(closest_point.zeta):.8g} "
            f"closest_segment_abs_zeta={distance:.8g} "
            f"closest_segment_u={interpolated_u:.12g} "
            f"segment=({left.u:.12g},{right.u:.12g})"
        )

    cache: dict[tuple[int, float], BranchPoint] = {}

    def evaluate_branch(index: int, u: float) -> BranchPoint:
        key = index, float(u)
        if key in cache:
            return cache[key]
        result = run_atlas(
            float(u),
            max_time=3.3,
            rtol=8e-13,
            atol=8e-15,
            max_step=0.0015,
            certificate_interval=5.0,
        )
        maxima = [
            event
            for event in result.events
            if event.is_maximum and event.time > 1e-8
        ]
        if len(maxima) <= index:
            raise RuntimeError(f"branch {index + 1} absent at u={u}")
        event = maxima[index]
        point = BranchPoint(
            u=float(u),
            time=event.time,
            zeta=complex(event.zeta_real, event.zeta_imag),
            residual=event.residual_norm,
            min_separation=event.min_separation,
        )
        cache[key] = point
        return point

    for index, bracket in ((0, (0.285, 0.300)), (1, (0.2915, 0.2938))):
        refinement = minimize_scalar(
            lambda u, branch=index: abs(
                evaluate_branch(branch, float(u)).zeta
            )
            ** 2,
            bounds=bracket,
            method="bounded",
            options={"xatol": 2e-10, "maxiter": 40},
        )
        point = evaluate_branch(index, float(refinement.x))
        print(
            "event_ordinal_refinement=ORDINARY_NUMERICAL_EVIDENCE "
            f"event_ordinal={index + 1} success={refinement.success} "
            f"u={point.u:.12g} t={point.time:.12g} "
            f"zeta=({point.zeta.real:.10g},{point.zeta.imag:.10g}) "
            f"abs_zeta={abs(point.zeta):.10g} "
            f"min_separation={point.min_separation:.10g}"
        )


if __name__ == "__main__":
    main()
