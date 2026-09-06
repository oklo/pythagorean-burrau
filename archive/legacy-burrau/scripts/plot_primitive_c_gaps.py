#!/usr/bin/env python3
"""Plot successive hypotenuse gaps for primitive triples in a u interval.

Uses only the Python standard library and writes both an SVG and the exact
underlying CSV data.  Here u = p/q is Euclid's parameter, and the primitive
triple is

    ((q^2-p^2)/d, 2pq/d, (q^2+p^2)/d),

where d=2 when p and q are both odd, and d=1 otherwise.
"""

from __future__ import annotations

import csv
import math
from fractions import Fraction
from math import gcd
from pathlib import Path


LOWER = Fraction(29, 100)
UPPER = Fraction(145001, 500000)  # 0.290002 exactly
COUNT = 5000
ROOT = Path(__file__).resolve().parents[1]
CSV_PATH = ROOT / "data" / "primitive_c_gaps_first_5000_u_0p29_0p290002.csv"
SVG_PATH = ROOT / "plots" / "log10_primitive_c_gaps_first_5000_u_0p29_0p290002.svg"


def ceil_fraction(value: Fraction) -> int:
    return -(-value.numerator // value.denominator)


def enumerate_first_triples(count: int) -> list[tuple[int, int, int]]:
    triples: list[tuple[int, int, int]] = []
    q = 1
    while True:
        p_min = ceil_fraction(LOWER * q)
        p_max = (UPPER * q).numerator // (UPPER * q).denominator
        for p in range(p_min, p_max + 1):
            if p <= 0 or p >= q or gcd(p, q) != 1:
                continue
            d = 2 if (p & 1 and q & 1) else 1
            a = (q * q - p * p) // d
            b = (2 * p * q) // d
            c = (q * q + p * p) // d
            triples.append((min(a, b), max(a, b), c))

        if len(triples) >= count:
            triples.sort(key=lambda triple: triple[2])
            cutoff = triples[count - 1][2]
            # Any later denominator q' gives c > q'^2/2.  Hence this proves
            # that no unseen parameter can enter the first `count` results.
            if (q + 1) * (q + 1) > 2 * cutoff:
                return triples[:count]
        q += 1


def write_csv(triples: list[tuple[int, int, int]]) -> list[int]:
    gaps = [triples[i + 1][2] - triples[i][2] for i in range(len(triples) - 1)]
    with CSV_PATH.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(
            [
                "gap_index_n",
                "c_n",
                "c_n_plus_1",
                "delta_c",
                "log10_delta_c",
            ]
        )
        for n, gap in enumerate(gaps, start=1):
            writer.writerow(
                [n, triples[n - 1][2], triples[n][2], gap, f"{math.log10(gap):.12f}"]
            )
    return gaps


def write_svg(gaps: list[int]) -> None:
    width, height = 1200, 720
    left, right, top, bottom = 110, 45, 100, 95
    plot_w = width - left - right
    plot_h = height - top - bottom
    values = [math.log10(gap) for gap in gaps]
    y_min = math.floor(min(values) * 2) / 2 - 0.1
    y_max = math.ceil(max(values) * 2) / 2 + 0.1

    def x_coord(n: int) -> float:
        return left + (n - 1) * plot_w / (len(gaps) - 1)

    def y_coord(value: float) -> float:
        return top + (y_max - value) * plot_h / (y_max - y_min)

    lines: list[str] = [
        '<?xml version="1.0" encoding="UTF-8"?>',
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}">',
        '<rect width="100%" height="100%" fill="#fbfaf7"/>',
        '<style>text{font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif;fill:#20242a}.tick{font-size:15px;fill:#555}.label{font-size:18px}.title{font-size:26px;font-weight:600}.subtitle{font-size:16px;fill:#555}</style>',
        f'<text x="{width / 2}" y="38" text-anchor="middle" class="title">Successive radial gaps between primitive Pythagorean triples</text>',
        f'<text x="{width / 2}" y="67" text-anchor="middle" class="subtitle">0.29 ≤ u ≤ 0.290002; radius c; {len(gaps)+1:,} triples and {len(gaps):,} successive gaps</text>',
    ]

    y_tick = math.ceil(y_min * 2) / 2
    while y_tick <= y_max + 1e-12:
        y = y_coord(y_tick)
        lines.append(
            f'<line x1="{left}" y1="{y:.2f}" x2="{width-right}" y2="{y:.2f}" stroke="#d9d9d6" stroke-width="1"/>'
        )
        lines.append(
            f'<text x="{left-14}" y="{y+5:.2f}" text-anchor="end" class="tick">{y_tick:.1f}</text>'
        )
        y_tick += 0.5

    tick_step = 500 if len(gaps) > 2000 else (100 if len(gaps) > 200 else 10)
    x_ticks = [1] + list(range(tick_step, len(gaps), tick_step)) + [len(gaps)]
    for n in x_ticks:
        x = x_coord(n)
        lines.append(
            f'<line x1="{x:.2f}" y1="{top}" x2="{x:.2f}" y2="{height-bottom}" stroke="#ecebe7" stroke-width="1"/>'
        )
        lines.append(
            f'<text x="{x:.2f}" y="{height-bottom+27}" text-anchor="middle" class="tick">{n}</text>'
        )

    lines.extend(
        [
            f'<line x1="{left}" y1="{top}" x2="{left}" y2="{height-bottom}" stroke="#333" stroke-width="1.5"/>',
            f'<line x1="{left}" y1="{height-bottom}" x2="{width-right}" y2="{height-bottom}" stroke="#333" stroke-width="1.5"/>',
            f'<text x="{left+plot_w/2}" y="{height-28}" text-anchor="middle" class="label">Gap index n (between triples n and n+1)</text>',
            f'<text x="27" y="{top+plot_h/2}" text-anchor="middle" class="label" transform="rotate(-90 27 {top+plot_h/2})">log₁₀(Δcₙ)</text>',
        ]
    )

    points = " ".join(
        f"{x_coord(n):.2f},{y_coord(value):.2f}"
        for n, value in enumerate(values, start=1)
    )
    line_width = 0.45 if len(gaps) > 2000 else (0.85 if len(gaps) > 200 else 1.6)
    lines.append(
        f'<polyline points="{points}" fill="none" stroke="#336c91" stroke-width="{line_width}" stroke-linejoin="round" opacity="0.68"/>'
    )
    for n, value in enumerate(values, start=1):
        color = "#b33a3a" if n == 1 else "#174f73"
        radius = 5.0 if n == 1 else (0.65 if len(gaps) > 2000 else (1.25 if len(gaps) > 200 else 3.1))
        lines.append(
            f'<circle cx="{x_coord(n):.2f}" cy="{y_coord(value):.2f}" r="{radius}" fill="{color}"/>'
        )

    first_x, first_y = x_coord(1), y_coord(values[0])
    lines.extend(
        [
            f'<line x1="{first_x+7:.2f}" y1="{first_y+3:.2f}" x2="{first_x+112:.2f}" y2="{first_y+35:.2f}" stroke="#8e3030"/>',
            f'<text x="{first_x+118:.2f}" y="{first_y+39:.2f}" class="tick" fill="#8e3030">endpoint outlier: Δc₁ = {gaps[0]:,}</text>',
            '</svg>',
        ]
    )
    SVG_PATH.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> None:
    triples = enumerate_first_triples(COUNT)
    gaps = write_csv(triples)
    write_svg(gaps)
    print(SVG_PATH)
    print(CSV_PATH)


if __name__ == "__main__":
    main()
