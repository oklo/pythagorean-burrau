#!/usr/bin/env python3
"""Audit the exact endpoint chain and archived logs of the Fable campaign."""

from __future__ import annotations

import argparse
import hashlib
import re
import tarfile
from dataclasses import dataclass
from fractions import Fraction
from pathlib import Path

CAPD_COMMIT = "731079217a9254ea2948d742df2b170895effe7f"
EXPECTED_START = Fraction(2_900_000_001, 10_000_000_000)
EXPECTED_END = Fraction(2_900_000_101, 10_000_000_000)
EXPECTED_WIDTH = Fraction(1, 10_000_000_000)
EXPECTED_TILES = 100

FRACTION = r"[0-9]+/[0-9]+"
SUMMARY_RE = re.compile(
    rf"^(?P<request_left>{FRACTION})\.\.(?P<request_right>{FRACTION}): "
    rf"PASS_MIDDLE_ESCAPE_ENDGAME u=\[(?P<pass_left>{FRACTION}),"
    rf"(?P<pass_right>{FRACTION})\].* steps=(?P<steps>[0-9]+) "
    rf"max_hull=(?P<hull>[^ ]+).* capd_commit=(?P<capd>[0-9a-f]+)$"
)
PASS_RE = re.compile(
    rf"^PASS_MIDDLE_ESCAPE_ENDGAME u=\[(?P<left>{FRACTION}),"
    rf"(?P<right>{FRACTION})\].* steps=(?P<steps>[0-9]+) "
    rf"max_hull=(?P<hull>[^ ]+).* capd_commit=(?P<capd>[0-9a-f]+)$",
    re.MULTILINE,
)


@dataclass(frozen=True, order=True)
class Tile:
    left: Fraction
    right: Fraction
    steps: int
    hull: float
    capd_commit: str


def sha256(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for block in iter(lambda: stream.read(1 << 20), b""):
            digest.update(block)
    return digest.hexdigest()


def parse_fraction(value: str) -> Fraction:
    numerator, denominator = value.split("/", maxsplit=1)
    return Fraction(int(numerator), int(denominator))


def tile_from_match(match: re.Match[str]) -> Tile:
    return Tile(
        left=parse_fraction(match.group("left")),
        right=parse_fraction(match.group("right")),
        steps=int(match.group("steps")),
        hull=float(match.group("hull")),
        capd_commit=match.group("capd"),
    )


def audit_chain(tiles: list[Tile], label: str) -> None:
    assert len(tiles) == EXPECTED_TILES, (
        f"{label}: expected {EXPECTED_TILES} tiles, found {len(tiles)}"
    )
    ordered = sorted(tiles)
    assert ordered[0].left == EXPECTED_START, f"{label}: wrong left endpoint"
    assert ordered[-1].right == EXPECTED_END, f"{label}: wrong right endpoint"
    assert len(set(ordered)) == EXPECTED_TILES, f"{label}: duplicate tile"
    for index, tile in enumerate(ordered):
        assert tile.right - tile.left == EXPECTED_WIDTH, (
            f"{label}: tile {index + 1} has wrong width"
        )
        assert tile.steps == 3537, f"{label}: tile {index + 1} step mismatch"
        assert tile.capd_commit == CAPD_COMMIT, f"{label}: tile {index + 1} CAPD pin mismatch"
        if index:
            assert ordered[index - 1].right == tile.left, (
                f"{label}: gap or overlap before tile {index + 1}"
            )


def audit_summary(path: Path) -> list[Tile]:
    tiles: list[Tile] = []
    for line_number, line in enumerate(path.read_text().splitlines(), start=1):
        match = SUMMARY_RE.match(line)
        if match is None:
            continue
        request_left = parse_fraction(match.group("request_left"))
        request_right = parse_fraction(match.group("request_right"))
        pass_left = parse_fraction(match.group("pass_left"))
        pass_right = parse_fraction(match.group("pass_right"))
        assert (request_left, request_right) == (pass_left, pass_right), (
            f"summary line {line_number}: requested/PASS interval mismatch"
        )
        renamed = {
            "left": match.group("pass_left"),
            "right": match.group("pass_right"),
            "steps": match.group("steps"),
            "hull": match.group("hull"),
            "capd": match.group("capd"),
        }
        # Keep one parsing path for summary and archived PASS records.
        tiles.append(
            Tile(
                left=parse_fraction(renamed["left"]),
                right=parse_fraction(renamed["right"]),
                steps=int(renamed["steps"]),
                hull=float(renamed["hull"]),
                capd_commit=renamed["capd"],
            )
        )
    audit_chain(tiles, "summary")
    return tiles


def audit_archive(path: Path) -> list[Tile]:
    tiles: list[Tile] = []
    with tarfile.open(path, mode="r:gz") as archive:
        members = [
            member
            for member in archive.getmembers()
            if member.isfile() and re.search(r"/slice_[0-9]{5}\.log$", member.name)
        ]
        assert len(members) == EXPECTED_TILES, (
            f"archive: expected {EXPECTED_TILES} logs, found {len(members)}"
        )
        assert len({member.name for member in members}) == EXPECTED_TILES, (
            "archive: duplicate member name"
        )
        for member in members:
            extracted = archive.extractfile(member)
            assert extracted is not None, f"archive: cannot read {member.name}"
            text = extracted.read().decode("utf-8")
            assert "FAIL" not in text, f"archive: FAIL marker in {member.name}"
            matches = list(PASS_RE.finditer(text))
            assert len(matches) == 1, (
                f"archive: expected one PASS in {member.name}, found {len(matches)}"
            )
            assert len(re.findall(r"^TERMINAL ", text, flags=re.MULTILINE)) == 1, (
                f"archive: expected one terminal record in {member.name}"
            )
            tiles.append(tile_from_match(matches[0]))
    audit_chain(tiles, "archive")
    return tiles


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--summary",
        type=Path,
        default=Path("data/fable/middle_escape_endgame_campaign_1e8.log"),
    )
    parser.add_argument(
        "--archive",
        type=Path,
        default=Path("data/fable/middle_escape_endgame_campaign_1e8_logs.tar.gz"),
    )
    args = parser.parse_args()

    summary_tiles = audit_summary(args.summary)
    archive_tiles = audit_archive(args.archive)
    assert sorted(summary_tiles) == sorted(archive_tiles), "summary and archive tile records differ"

    hulls = [tile.hull for tile in summary_tiles]
    print(
        "PASS_FABLE_MIDDLE_CAMPAIGN_AUDIT "
        f"tiles={len(summary_tiles)} start={EXPECTED_START} end={EXPECTED_END} "
        f"width={EXPECTED_WIDTH} min_hull={min(hulls):.17g} "
        f"max_hull={max(hulls):.17g} capd_commit={CAPD_COMMIT}"
    )
    print(f"summary_sha256={sha256(args.summary)}")
    print(f"archive_sha256={sha256(args.archive)}")


if __name__ == "__main__":
    main()
