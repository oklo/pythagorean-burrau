#!/usr/bin/env python3
"""Continue all 30 Li--Liao (0.6,0.8,1) brake orbits to tied-side roots.

This is an ordinary-numerical candidate generator.  Each subprocess solves
three second-brake equations and two mass--opposite-side equations.  The
remaining diagnostic is m1^2+m2^2-1.  A value near zero would be a candidate
for a Pythagorean mass--side-tied periodic orbit, not a proof of one.
"""

from __future__ import annotations

import concurrent.futures
import json
import os
from pathlib import Path
import re
import subprocess


ROOT = Path(__file__).resolve().parents[1]
MAIN = Path("/Users/greglaughlin/Projects/pythagorean-burrau")
PYTHON = MAIN / ".venv" / "bin" / "python"
DRIVER = MAIN / "scripts" / "continue_f30.py"
OUTPUT = ROOT / "data" / "f30_all_mass_side_continuations.json"

CATALOG = (
    (1, 0.2061730906, 0.4463433325, 2.6925803371),
    (2, 0.2632585995, 0.4021064128, 2.8891085282),
    (3, 0.3087699287, 0.2817129610, 2.2526299455),
    (4, 0.3064570616, 0.2486099306, 2.3813615017),
    (5, 0.2810833582, 0.4016924931, 3.2814736858),
    (6, 0.3226484475, 0.1813773910, 1.9623770921),
    (7, 0.2687327027, 0.0903053982, 1.9434750648),
    (8, 0.3233959420, 0.1697487157, 2.1207316616),
    (9, 0.3271831808, 0.2547968571, 2.6280318900),
    (10, 0.2899252590, 0.4030770616, 3.6787912077),
    (11, 0.3426262070, 0.1830843562, 2.3182580914),
    (12, 0.3372214876, 0.2601345660, 2.9032413179),
    (13, 0.3339428510, 0.1166303462, 1.9513533175),
    (14, 0.3514438378, 0.1374554522, 2.1335770470),
    (15, 0.3541926333, 0.1912396242, 2.5272612515),
    (16, 0.2137677527, 0.4223425850, 5.8220417242),
    (17, 0.3635347723, 0.1483383694, 2.3025570478),
    (18, 0.0697898821, 0.3190727633, 6.2973444729),
    (19, 0.3326592654, 0.2979880796, 4.4551677666),
    (20, 0.0774214943, 0.2835443503, 5.9030069770),
    (21, 0.0779210325, 0.3163212877, 6.1187532147),
    (22, 0.1428136093, 0.1910273880, 5.3746485278),
    (23, 0.0894008417, 0.2215222207, 6.0165906664),
    (24, 0.0411868590, 0.1386939050, 5.7982241905),
    (25, 0.2645032395, 0.3738186198, 6.4584844333),
    (26, 0.0876902685, 0.1043044639, 5.9308332463),
    (27, 0.1201933414, 0.4542911576, 9.4434059349),
    (28, 0.3461730153, 0.2018360990, 4.1324912323),
    (29, 0.1715954664, 0.2463490645, 8.1331787201),
    (30, 0.1446319096, 0.4773197126, 12.5809129586),
)


def extract(pattern: str, text: str) -> float | None:
    match = re.search(pattern, text)
    return float(match.group(1)) if match else None


def run_one(row: tuple[int, float, float, float]) -> dict[str, object]:
    number, x, y, period = row
    command = [
        str(PYTHON),
        str(DRIVER),
        "--x",
        str(x),
        "--y",
        str(y),
        "--half-period",
        str(period / 2.0),
        "--solve-mass-side",
        "--rtol",
        "3e-11",
        "--atol",
        "3e-13",
        "--max-step",
        "0.003",
        "--root-tol",
        "1e-8",
    ]
    environment = os.environ.copy()
    environment["PYTHONPATH"] = str(MAIN)
    environment["PYTHONDONTWRITEBYTECODE"] = "1"
    try:
        completed = subprocess.run(
            command,
            cwd=MAIN,
            env=environment,
            text=True,
            capture_output=True,
            timeout=300,
            check=False,
        )
    except subprocess.TimeoutExpired as error:
        return {"number": number, "status": "timeout", "error": str(error)}
    output = completed.stdout + completed.stderr
    residual_match = re.search(r"five_residual=\[([^\]]+)\]", output, re.S)
    residual = None
    if residual_match:
        try:
            residual = [float(value) for value in residual_match.group(1).split()]
        except ValueError:
            residual = None
    return {
        "number": number,
        "catalog_x": x,
        "catalog_y": y,
        "catalog_period": period,
        "returncode": completed.returncode,
        "root_success": "root_success=True" in output,
        "m1": extract(r"m_1=([-+0-9.eE]+)", output),
        "m2": extract(r"m_2=([-+0-9.eE]+)", output),
        "x": extract(r"\nx=([-+0-9.eE]+)", output),
        "y": extract(r" y=([-+0-9.eE]+)", output),
        "half_period": extract(r"half_period=([-+0-9.eE]+)", output),
        "defect": extract(r"mass_pythagorean_defect=([-+0-9.eE]+)", output),
        "minimum_separation": extract(r"minimum_sampled_separation=([-+0-9.eE]+)", output),
        "maximum_relative_energy_error": extract(r"maximum_relative_energy_error=([-+0-9.eE]+)", output),
        "residual": residual,
        "raw_output": output,
    }


def main() -> None:
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    results: list[dict[str, object]] = []
    # Threads only supervise independent numerical subprocesses.  This avoids
    # platform semaphore limits while retaining four-way process parallelism.
    with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:
        futures = {pool.submit(run_one, row): row[0] for row in CATALOG}
        for future in concurrent.futures.as_completed(futures):
            result = future.result()
            results.append(result)
            print(
                f"F{result['number']:02d} success={result.get('root_success')} "
                f"defect={result.get('defect')} minsep={result.get('minimum_separation')}",
                flush=True,
            )
    results.sort(key=lambda item: int(item["number"]))
    OUTPUT.write_text(json.dumps(results, indent=2) + "\n", encoding="utf-8")
    converged = [row for row in results if row.get("root_success") and row.get("defect") is not None]
    print("\nConverged roots ordered by |right-angle defect|:")
    for row in sorted(converged, key=lambda item: abs(float(item["defect"]))):
        print(
            f"F{row['number']:02d} defect={float(row['defect']):+.12g} "
            f"m=({row['m1']},{row['m2']},1) minsep={row['minimum_separation']}"
        )
    print(OUTPUT)


if __name__ == "__main__":
    main()
