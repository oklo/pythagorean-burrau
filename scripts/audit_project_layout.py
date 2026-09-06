#!/usr/bin/env python3
"""Check active navigation, local paper inputs, and preserved source hashes.

This is a repository-integrity audit, not a mathematical certificate.
It needs neither a Git checkout nor the retired sibling directories.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path
from urllib.parse import unquote, urlsplit

ROOT = Path(__file__).resolve().parents[1]
GUIDES = (
    "README.md",
    "paper/README.md",
    "docs/STATUS.md",
    "docs/RESEARCH_PLAN.md",
    "docs/PROOF_LEDGER.md",
    "docs/PROOF_OBLIGATIONS.md",
    "docs/FAILED_ROUTES.md",
    "docs/RESEARCH_FLOWCHART.md",
    "docs/HANDOFF.md",
    "docs/PROJECT_REVIEW_2026-09-06.md",
    "docs/PERSISTENT_RESEARCH_MEMORY.md",
    "docs/FABLE_BURRAU_THEOREM.md",
    "docs/FABLE_LC_COVERING_DESIGN.md",
    "archive/README.md",
)
RETIRED_LATEX_LOGS = {
    "docs/arithmetic_channel_color_explanation.log",
    "paper/every_rational_parameter_is_a_periodic_brake.log",
    "paper/rational_parameters_in_measure_zero_periodic_sets.log",
    "paper/sparse_rational_dense_irrational_periodic_parameters.log",
}
DUPLICATE_IMAGE = "plots/log10_primitive_c_gaps_first_5000_colored_channels copy.png"
RETAINED_IMAGE = "plots/log10_primitive_c_gaps_first_5000_colored_channels.png"
SNAPSHOT_ROOTS = {
    "global": "pythagorean-burrau-fable",
    "middle": "pythagorean-burrau-fable-middle",
}
SNAPSHOT_FILES = {
    "global": (
        "data/fable/certificate_5_14.log",
        "data/fable/certificate_burrau_1_3.log",
        "docs/FABLE_BURRAU_THEOREM.md",
        "docs/FABLE_TRIPLE_CERTIFICATES.md",
        "scripts/fable_run_capd_burrau_lc.sh",
        "src/fable/verification/burrau_lc_certificate_capd.cpp",
    ),
    "middle": (
        "data/fable/middle_escape_endgame_1e10_crosscheck.log",
        "data/fable/parameter_graph/pg1_w1e10.log",
        "data/fable/parameter_graph/pg1_w1e11.log",
        "data/fable/parameter_graph/pg1_w1e12.log",
        "data/fable/parameter_graph/pg1_w1e8.log",
        "data/fable/parameter_graph/pg1_w1e9.log",
        "data/fable/parameter_graph/pg2_w1e10.log",
        "data/fable/parameter_graph/pg2_w1e12.log",
        "docs/FABLE_NEXT_RUN_PROMPT.md",
        "docs/FABLE_PARAMETER_GRAPH_AUDIT.md",
        "docs/FABLE_PARAMETER_GRAPH_HANDOFF.md",
        "src/fable/verification/parameter_graph_capd.cpp",
    ),
}


class AuditError(RuntimeError):
    """A required local input or preserved byte sequence is missing."""


def require(condition: bool, message: str) -> None:
    if not condition:
        raise AuditError(message)


def sha256(path: Path) -> str:
    require(path.is_file(), f"Missing file: {path}")
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def assert_unchanged(path: Path, expected: str) -> None:
    require(sha256(path) == expected, f"Preserved hash mismatch: {path}")


def audit_links(path: Path, root: Path) -> int:
    """Check simple inline Markdown links in current guides, not old snapshots."""
    require(path.is_file(), f"Missing guide: {path}")
    count = 0
    for target in re.findall(r"\[[^\]\n]+\]\(([^)\n]+)\)", path.read_text()):
        parsed = urlsplit(target.strip("<>"))
        if parsed.scheme or parsed.netloc or not parsed.path:
            continue
        destination = (path.parent / unquote(parsed.path)).resolve()
        require(destination.is_relative_to(root), f"Link leaves repository: {path}: {target}")
        require(destination.exists(), f"Broken local link: {path}: {target}")
        count += 1
    return count


def audit_paper(main: Path, root: Path) -> tuple[int, int]:
    """Resolve this manuscript's literal input/includegraphics dependencies."""
    base = main.parent
    pending, visited, graphics = [main], set(), set()
    while pending:
        source = pending.pop().resolve()
        if source in visited:
            continue
        require(source.is_relative_to(root), f"Paper input leaves repository: {source}")
        require(source.is_file(), f"Missing paper input: {source}")
        visited.add(source)
        content = source.read_text()
        for name in re.findall(r"\\(?:input|include)\{([^}]+)\}", content):
            target = base / name
            if not target.suffix:
                target = target.with_suffix(".tex")
            pending.append(target)
        for name in re.findall(r"\\includegraphics(?:\[[^\]]*\])?\{([^}]+)\}", content):
            target = (base / name).resolve()
            require(target.is_relative_to(root), f"Paper graphic leaves repository: {target}")
            require(target.is_file(), f"Missing paper graphic: {target}")
            graphics.add(target)
    return len(visited), len(graphics)


def audit_preservation(root: Path) -> tuple[int, int]:
    inventory = json.loads((root / "archive/reorganization-2026-09-06/before.json").read_text())[
        "roots"
    ]
    checked = 0
    for record in inventory["burrau"]["files"]:
        relative = record["path"]
        if relative in RETIRED_LATEX_LOGS:
            continue
        if relative == DUPLICATE_IMAGE:
            relative = RETAINED_IMAGE
        assert_unchanged(root / "archive/legacy-burrau" / relative, record["sha256"])
        checked += 1

    snapshots = 0
    for name, original in SNAPSHOT_ROOTS.items():
        originals = {record["path"]: record for record in inventory[original]["files"]}
        directory = root / "archive/branch-snapshots" / name
        require(directory.is_dir(), f"Missing branch snapshot: {directory}")
        for relative in SNAPSHOT_FILES[name]:
            path = directory / relative
            require(relative in originals, f"Unattributed branch snapshot: {path}")
            assert_unchanged(path, originals[relative]["sha256"])
            snapshots += 1
    return checked, snapshots


def audit(root: Path) -> dict[str, int]:
    root = root.resolve()
    links = sum(audit_links(root / name, root) for name in GUIDES)
    sources, figures = audit_paper(root / "paper/main.tex", root)
    for name in ("paper/main.pdf", "paper/technical-details.pdf", "uv.lock", "Makefile"):
        require((root / name).is_file(), f"Missing primary project asset: {name}")
    legacy, snapshots = audit_preservation(root)
    return {
        "local_links": links,
        "paper_sources": sources,
        "paper_figures": figures,
        "legacy_records": legacy,
        "branch_snapshot_files": snapshots,
    }


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=ROOT)
    args = parser.parse_args()
    try:
        result = audit(args.root)
    except (AuditError, OSError, KeyError, ValueError) as exc:
        raise SystemExit(f"FAIL_PROJECT_LAYOUT_AUDIT: {exc}") from exc
    print("PASS_PROJECT_LAYOUT_AUDIT " + " ".join(f"{k}={v}" for k, v in result.items()))


if __name__ == "__main__":
    main()
