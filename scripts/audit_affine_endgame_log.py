#!/usr/bin/env python3
"""Fail-closed audit of an affine-generator middle-endgame certificate log."""

from __future__ import annotations

import argparse
import math
import re
from pathlib import Path

CAPD_COMMIT = "731079217a9254ea2948d742df2b170895effe7f"


def _time(num: int, den: int) -> str:
    return f"t={num}/{den}"


EXPECTED_LEGS = [
    *[_time(*pair) for pair in ((2, 5), (11, 20), (3, 5), (31, 50),
                                (16, 25), (33, 50), (17, 25), (7, 10))],
    "min1",
    *[_time(*pair) for pair in ((17, 20), (9, 10), (19, 20), (1, 1))],
    "switch13to23_formA",
    *[_time(*pair) for pair in ((21, 20), (11, 10), (23, 20), (6, 5),
                                (5, 4), (13, 10))],
    "max1",
    *[_time(*pair) for pair in ((27, 20), (7, 5), (29, 20), (3, 2),
                                (31, 20), (8, 5), (33, 20), (17, 10),
                                (7, 4))],
    "switch23to13_formA",
    *[_time(*pair) for pair in ((9, 5), (37, 20), (19, 10))],
    "min2",
    *[_time(*pair) for pair in ((39, 20), (2, 1), (21, 10), (11, 5),
                                (23, 10), (12, 5), (5, 2), (13, 5))],
    "max2",
    *[_time(*pair) for pair in ((27, 10), (14, 5), (57, 20), (29, 10))],
    "min3",
    *[_time(*pair) for pair in ((59, 20), (3, 1))],
    "max3",
    *[_time(*pair) for pair in ((31, 10), (63, 20), (16, 5), (13, 4),
                                (33, 10), (67, 20), (17, 5), (69, 20))],
    "min4",
    _time(7, 2),
    "switch13to23_formB",
    *[f"pair23_section_{index}" for index in range(1, 22)],
    _time(77, 20),
]


def _fields(line: str) -> dict[str, str]:
    return dict(re.findall(r"([A-Za-z_][A-Za-z0-9_]*)=([^ ]+)", line))


def audit_log(text: str, expected_left: str, expected_right: str) -> dict[str, float | int]:
    """Audit one complete stdout log, raising ValueError on any defect."""
    lines = [line.strip() for line in text.splitlines() if line.strip()]
    if any("FAIL" in line for line in lines):
        raise ValueError("log contains a failure marker")

    parameter_lines = [line for line in lines if line.startswith("ENDGAME_PARAMS ")]
    if len(parameter_lines) != 1:
        raise ValueError(f"expected one ENDGAME_PARAMS row, found {len(parameter_lines)}")
    params = _fields(parameter_lines[0])
    required_settings = {
        "precision_bits": "160",
        "tolerance": "1e-24",
        "order": "32",
        "sync_exchange": "0",
        "sync_preswitch": "0",
        "structured_form_b": "0",
        "sync_pair23": "0",
        "structured_section": "0",
        "graph_pair23_sync": "1",
        "graph_tangent_split": "0",
        "graph_c2": "1",
        "graph_pg2": "1",
        "graph_affine_remainder": "1",
        "graph_exchange_sandwich": "0",
        "graph_fixed_energy_h": "0",
        "graph_exchange_sync": "0",
        "graph_exchange_energy_project": "0",
        "graph_exchange_invariant_project": "0",
        "graph_exchange_velocity_project": "0",
    }
    for name, value in required_settings.items():
        if params.get(name) != value:
            raise ValueError(f"required setting {name}={value} is absent")
    if not params.get("driver", "").startswith(
        "middle_escape_endgame_capd/v26-affine-remainder-"
    ):
        raise ValueError("unexpected driver identity")

    leg_lines = [line for line in lines if line.startswith("ENDGAME_LEG ")]
    labels = [line.split()[1] for line in leg_lines]
    if labels != EXPECTED_LEGS:
        mismatch = next(
            (
                index
                for index, pair in enumerate(zip(labels, EXPECTED_LEGS, strict=False))
                if pair[0] != pair[1]
            ),
            min(len(labels), len(EXPECTED_LEGS)),
        )
        got = labels[mismatch] if mismatch < len(labels) else "<missing>"
        want = EXPECTED_LEGS[mismatch] if mismatch < len(EXPECTED_LEGS) else "<none>"
        raise ValueError(f"itinerary mismatch at row {mismatch + 1}: got {got}, expected {want}")

    previous_generators = -1
    largest_hull = 0.0
    largest_defect = 0.0
    for line in leg_lines:
        fields = _fields(line)
        for name in ("hull", "parameter_spread", "quadratic_spread", "defect"):
            try:
                value = float(fields[name])
            except (KeyError, ValueError) as exc:
                raise ValueError(f"invalid {name} field in {line}") from exc
            if not math.isfinite(value) or value < 0:
                raise ValueError(f"nonfinite or negative {name} in {line}")
        generators = int(fields["generators"])
        if generators < previous_generators:
            raise ValueError("generator count decreased")
        previous_generators = generators
        largest_hull = max(largest_hull, float(fields["hull"]))
        largest_defect = max(largest_defect, float(fields["defect"]))

    maximum_labels = [
        line.split()[1] for line in lines if line.startswith("ENDGAME_MAXIMUM ")
    ]
    if maximum_labels != ["max1", "max2", "max3"]:
        raise ValueError(f"missing strict-maximum audits: {maximum_labels}")

    terminal: dict[str, float] = {}
    for line in lines:
        if line.startswith("TERMINAL "):
            terminal.update({name: float(value) for name, value in _fields(line).items()})
    required_terminal = {
        "inf_d",
        "inf_rhodot",
        "inf_Erho",
        "sup_h",
        "sup_Delta",
        "inf_margin",
    }
    if set(terminal) != required_terminal:
        raise ValueError(f"terminal fields are incomplete: {sorted(terminal)}")
    for name in ("inf_d", "inf_rhodot", "inf_Erho", "inf_margin"):
        if not math.isfinite(terminal[name]) or terminal[name] <= 0:
            raise ValueError(f"terminal strict inequality failed: {name}")
    if not math.isfinite(terminal["sup_h"]) or terminal["sup_h"] >= 0:
        raise ValueError("terminal binary energy is not strictly negative")
    if not math.isfinite(terminal["sup_Delta"]) or terminal["sup_Delta"] < 0:
        raise ValueError("terminal tidal loss bound is invalid")

    pass_lines = [line for line in lines if line.startswith("PASS_MIDDLE_ESCAPE_ENDGAME ")]
    if len(pass_lines) != 1:
        raise ValueError(f"expected one PASS row, found {len(pass_lines)}")
    wanted_interval = f"u=[{expected_left},{expected_right}]"
    if wanted_interval not in pass_lines[0]:
        raise ValueError("PASS row has the wrong exact rational endpoints")
    if "t_terminal=77/20" not in pass_lines[0] or "eta=4" not in pass_lines[0]:
        raise ValueError("PASS row has the wrong terminal section or eta")
    if f"capd_commit={CAPD_COMMIT}" not in pass_lines[0]:
        raise ValueError("PASS row has the wrong CAPD dependency")

    return {
        "legs": len(leg_lines),
        "generators": previous_generators,
        "largest_hull": largest_hull,
        "largest_defect": largest_defect,
        "terminal_margin": terminal["inf_margin"],
    }


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("log", type=Path)
    parser.add_argument("--expected-left", required=True)
    parser.add_argument("--expected-right", required=True)
    args = parser.parse_args()
    result = audit_log(
        args.log.read_text(), args.expected_left, args.expected_right
    )
    print(
        "PASS_AFFINE_ENDGAME_LOG_AUDIT "
        + " ".join(f"{name}={value}" for name, value in result.items())
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
