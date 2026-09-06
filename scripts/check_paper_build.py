#!/usr/bin/env python3
"""Build the paper in scratch without replacing the reviewed PDF."""

from __future__ import annotations

import argparse
import hashlib
import subprocess
import tempfile
from pathlib import Path


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--tectonic", default="tectonic")
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[1]
    reviewed = root / "paper/main.pdf"
    original = hashlib.sha256(reviewed.read_bytes()).hexdigest()
    output = Path(tempfile.mkdtemp(prefix="burrau-paper-check-"))
    result = subprocess.run(
        [args.tectonic, "--keep-logs", "--outdir", str(output), "paper/main.tex"],
        cwd=root,
        check=False,
    )
    if hashlib.sha256(reviewed.read_bytes()).hexdigest() != original:
        raise SystemExit("FAIL: the reviewed PDF changed during the scratch build")
    if result.returncode:
        raise SystemExit(result.returncode)
    if not (output / "main.pdf").is_file():
        raise SystemExit("FAIL: Tectonic did not produce the scratch PDF")
    print(f"PASS_PAPER_BUILD reviewed_sha256={original}")
    print(f"Scratch PDF and build log retained at {output}")


if __name__ == "__main__":
    main()
