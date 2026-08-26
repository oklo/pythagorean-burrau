#!/usr/bin/env python3
"""Run resumable exact affine-generator tiles with fail-closed log audits."""

from __future__ import annotations

import argparse
import os
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

try:
    from scripts.audit_affine_endgame_log import audit_log
except ModuleNotFoundError:  # Direct execution puts scripts/ on sys.path.
    from audit_affine_endgame_log import audit_log

GRAPH_ENVIRONMENT = {
    "FABLE_ENDGAME_GRAPH": "1",
    "FABLE_ENDGAME_GRAPH_C2": "1",
    "FABLE_ENDGAME_GRAPH_PG2": "1",
    "FABLE_ENDGAME_GRAPH_AFFINE_REMAINDER": "1",
    "FABLE_ENDGAME_GRAPH_PAIR23_SYNC": "1",
}


@dataclass(frozen=True)
class ExactTile:
    index: int
    left_numerator: int
    right_numerator: int
    denominator: int

    @property
    def left(self) -> str:
        return f"{self.left_numerator}/{self.denominator}"

    @property
    def right(self) -> str:
        return f"{self.right_numerator}/{self.denominator}"

    @property
    def filename(self) -> str:
        return (
            f"affine_tile_{self.index:03d}_"
            f"{self.left_numerator}_{self.right_numerator}.log"
        )


def make_tile(index: int, base_numerator: int, denominator: int) -> ExactTile:
    if index < 0:
        raise ValueError("tile index must be nonnegative")
    if denominator <= 0:
        raise ValueError("denominator must be positive")
    left = base_numerator + index
    return ExactTile(index, left, left + 1, denominator)


def audit_existing(path: Path, tile: ExactTile) -> dict[str, float | int]:
    return audit_log(path.read_text(), tile.left, tile.right)


def run_tile(binary: Path, output_dir: Path, tile: ExactTile) -> bool:
    final_path = output_dir / tile.filename
    if final_path.exists():
        result = audit_existing(final_path, tile)
        print(
            f"SKIP_AUDITED_AFFINE_TILE index={tile.index} "
            f"u=[{tile.left},{tile.right}] margin={result['terminal_margin']}",
            flush=True,
        )
        return True

    partial_path = final_path.with_suffix(".partial")
    failed_path = final_path.with_suffix(".failed.log")
    if partial_path.exists():
        partial_path.replace(failed_path)

    command = [
        str(binary),
        str(tile.left_numerator),
        str(tile.denominator),
        str(tile.right_numerator),
        str(tile.denominator),
        "160",
        "1e-24",
        "32",
    ]
    environment = os.environ.copy()
    environment.update(GRAPH_ENVIRONMENT)
    print(
        f"START_AFFINE_TILE index={tile.index} u=[{tile.left},{tile.right}]",
        flush=True,
    )
    with partial_path.open("w") as stream:
        process = subprocess.Popen(
            command,
            env=environment,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            bufsize=1,
        )
        assert process.stdout is not None
        for line in process.stdout:
            stream.write(line)
            stream.flush()
            sys.stdout.write(line)
            sys.stdout.flush()
        return_code = process.wait()

    if return_code != 0:
        partial_path.replace(failed_path)
        print(
            f"FAIL_AFFINE_TILE index={tile.index} return_code={return_code} "
            f"artifact={failed_path}",
            file=sys.stderr,
            flush=True,
        )
        return False

    try:
        result = audit_log(partial_path.read_text(), tile.left, tile.right)
    except ValueError as exc:
        partial_path.replace(failed_path)
        print(
            f"FAIL_AFFINE_TILE_AUDIT index={tile.index} error={exc} "
            f"artifact={failed_path}",
            file=sys.stderr,
            flush=True,
        )
        return False

    partial_path.replace(final_path)
    print(
        f"PASS_AFFINE_TILE index={tile.index} u=[{tile.left},{tile.right}] "
        f"largest_hull={result['largest_hull']} "
        f"largest_defect={result['largest_defect']} "
        f"terminal_margin={result['terminal_margin']} artifact={final_path}",
        flush=True,
    )
    return True


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--binary", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--base-numerator", type=int, default=290_000)
    parser.add_argument("--denominator", type=int, default=1_000_000)
    parser.add_argument("--first-index", type=int, default=1)
    parser.add_argument("--last-index", type=int, default=19)
    parser.add_argument("--continue-on-failure", action="store_true")
    args = parser.parse_args()

    if not args.binary.is_file():
        parser.error(f"binary does not exist: {args.binary}")
    if args.first_index < 0 or args.last_index < args.first_index:
        parser.error("invalid inclusive tile-index range")
    args.output_dir.mkdir(parents=True, exist_ok=True)

    failures = 0
    for index in range(args.first_index, args.last_index + 1):
        tile = make_tile(index, args.base_numerator, args.denominator)
        if not run_tile(args.binary, args.output_dir, tile):
            failures += 1
            if not args.continue_on_failure:
                break
    if failures:
        print(f"FAIL_AFFINE_CAMPAIGN failed_tiles={failures}", file=sys.stderr)
        return 1
    print(
        f"PASS_AFFINE_CAMPAIGN first_index={args.first_index} "
        f"last_index={args.last_index}",
        flush=True,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
