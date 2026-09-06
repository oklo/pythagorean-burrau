#!/usr/bin/env python3
"""Channel- and parity-colored hypotenuse-gap plot for a narrow u interval.

For a reduced Euclid parameter u=p/q, define the arithmetic channel

    k = 100*p - 29*q.

The interval [0.29, 0.290002] is equivalent to 0 <= k <= q/5000.
Each plotted global gap c[n+1]-c[n] is colored by the channel of the arriving
triple n+1.  Circles mark d=1 (opposite parity); diamonds mark d=2 (odd-odd).
"""

from __future__ import annotations

import csv
import math
from fractions import Fraction
from math import gcd
from pathlib import Path


LOWER = Fraction(29, 100)
UPPER = Fraction(145001, 500000)
COUNT = 5000
ROOT = Path(__file__).resolve().parents[1]
CSV_PATH = ROOT / "data" / "primitive_c_gaps_first_5000_colored_channels.csv"
SVG_PATH = ROOT / "plots" / "log10_primitive_c_gaps_first_5000_colored_channels.svg"

# A compact viridis approximation, specified as (position, R, G, B).
VIRIDIS = [
    (0.00, 68, 1, 84),
    (0.20, 64, 67, 135),
    (0.40, 42, 120, 142),
    (0.60, 34, 168, 132),
    (0.80, 122, 209, 81),
    (1.00, 253, 231, 37),
]


def ceil_fraction(value: Fraction) -> int:
    return -(-value.numerator // value.denominator)


def enumerate_first_triples(count: int) -> list[tuple[int, int, int, int, int, int, int]]:
    """Return tuples (c, short_leg, long_leg, p, q, d, k), ordered by c."""
    triples: list[tuple[int, int, int, int, int, int, int]] = []
    q = 1
    while True:
        p_min = ceil_fraction(LOWER * q)
        uq = UPPER * q
        p_max = uq.numerator // uq.denominator
        for p in range(p_min, p_max + 1):
            if p <= 0 or p >= q or gcd(p, q) != 1:
                continue
            d = 2 if (p & 1 and q & 1) else 1
            leg_1 = (q * q - p * p) // d
            leg_2 = (2 * p * q) // d
            c = (q * q + p * p) // d
            k = 100 * p - 29 * q
            triples.append((c, min(leg_1, leg_2), max(leg_1, leg_2), p, q, d, k))

        if len(triples) >= count:
            triples.sort(key=lambda triple: triple[0])
            cutoff = triples[count - 1][0]
            if (q + 1) * (q + 1) > 2 * cutoff:
                return triples[:count]
        q += 1


def channel_color(k: int, max_k: int) -> str:
    position = 0.0 if max_k == 0 else k / max_k
    for left, right in zip(VIRIDIS, VIRIDIS[1:]):
        if position <= right[0]:
            fraction = (position - left[0]) / (right[0] - left[0])
            rgb = [round(left[i] + fraction * (right[i] - left[i])) for i in range(1, 4)]
            return "#" + "".join(f"{value:02x}" for value in rgb)
    return "#fde725"


def write_csv(triples: list[tuple[int, int, int, int, int, int, int]]) -> None:
    with CSV_PATH.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.writer(handle)
        writer.writerow(
            [
                "gap_index_n",
                "c_n",
                "c_n_plus_1",
                "delta_c",
                "log10_delta_c",
                "p_n",
                "q_n",
                "k_n",
                "d_n",
                "p_n_plus_1",
                "q_n_plus_1",
                "k_n_plus_1",
                "d_n_plus_1",
            ]
        )
        for index in range(len(triples) - 1):
            before, after = triples[index], triples[index + 1]
            gap = after[0] - before[0]
            if gap <= 0:
                raise ValueError(f"nonpositive radial gap at index {index + 1}: {gap}")
            writer.writerow(
                [
                    index + 1,
                    before[0],
                    after[0],
                    gap,
                    f"{math.log10(gap):.12f}",
                    before[3],
                    before[4],
                    before[6],
                    before[5],
                    after[3],
                    after[4],
                    after[6],
                    after[5],
                ]
            )


def write_svg(triples: list[tuple[int, int, int, int, int, int, int]]) -> None:
    width, height = 1400, 820
    left, right, top, bottom = 115, 55, 145, 100
    plot_w = width - left - right
    plot_h = height - top - bottom
    gaps = [triples[i + 1][0] - triples[i][0] for i in range(len(triples) - 1)]
    values = [math.log10(gap) for gap in gaps]
    max_k = max(triple[6] for triple in triples)
    y_min = math.floor(min(values) * 2) / 2 - 0.1
    y_max = math.ceil(max(values) * 2) / 2 + 0.1

    def x_coord(index: int) -> float:
        return left + (index - 1) * plot_w / (len(gaps) - 1)

    def y_coord(value: float) -> float:
        return top + (y_max - value) * plot_h / (y_max - y_min)

    lines = [
        '<?xml version="1.0" encoding="UTF-8"?>',
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}">',
        '<rect width="100%" height="100%" fill="#fbfaf7"/>',
        '<style>text{font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif;fill:#20242a}.tick{font-size:15px;fill:#555}.label{font-size:18px}.subtitle{font-size:16px;fill:#555}.legend{font-size:14px;fill:#444}.inset{font-size:12px;fill:#444}</style>',
        f'<text x="{width/2}" y="34" text-anchor="middle" class="subtitle">0.29 ≤ u ≤ 0.290002; color = arriving channel k=100p−29q; shape = parity class</text>',
    ]

    # Discrete channel color strip.
    bar_x, bar_y, bar_w, bar_h = 420, 57, 560, 13
    cell_w = bar_w / (max_k + 1)
    for k in range(max_k + 1):
        lines.append(
            f'<rect x="{bar_x+k*cell_w:.2f}" y="{bar_y}" width="{cell_w+0.25:.2f}" height="{bar_h}" fill="{channel_color(k, max_k)}"/>'
        )
    lines.extend(
        [
            f'<text x="{bar_x-10}" y="{bar_y+12}" text-anchor="end" class="legend">k</text>',
            f'<text x="{bar_x}" y="{bar_y+31}" text-anchor="middle" class="legend">0</text>',
            f'<text x="{bar_x+bar_w/2}" y="{bar_y+31}" text-anchor="middle" class="legend">{max_k//2}</text>',
            f'<text x="{bar_x+bar_w}" y="{bar_y+31}" text-anchor="middle" class="legend">{max_k}</text>',
            f'<circle cx="{1045}" cy="{bar_y+4}" r="3.2" fill="#333"/><text x="1055" y="{bar_y+9}" class="legend">d=1: opposite parity</text>',
            f'<path d="M 1045 {bar_y+20-4} L {1045+4} {bar_y+20} L 1045 {bar_y+20+4} L {1045-4} {bar_y+20} Z" fill="#333"/><text x="1055" y="{bar_y+25}" class="legend">d=2: odd–odd</text>',
        ]
    )

    y_tick = math.ceil(y_min * 2) / 2
    while y_tick <= y_max + 1e-12:
        y = y_coord(y_tick)
        lines.append(f'<line x1="{left}" y1="{y:.2f}" x2="{width-right}" y2="{y:.2f}" stroke="#d9d9d6"/>')
        lines.append(f'<text x="{left-14}" y="{y+5:.2f}" text-anchor="end" class="tick">{y_tick:.1f}</text>')
        y_tick += 0.5

    x_ticks = [1] + list(range(500, len(gaps), 500)) + [len(gaps)]
    for index in x_ticks:
        x = x_coord(index)
        lines.append(f'<line x1="{x:.2f}" y1="{top}" x2="{x:.2f}" y2="{height-bottom}" stroke="#ecebe7"/>')
        lines.append(f'<text x="{x:.2f}" y="{height-bottom+27}" text-anchor="middle" class="tick">{index}</text>')

    lines.extend(
        [
            f'<line x1="{left}" y1="{top}" x2="{left}" y2="{height-bottom}" stroke="#333" stroke-width="1.5"/>',
            f'<line x1="{left}" y1="{height-bottom}" x2="{width-right}" y2="{height-bottom}" stroke="#333" stroke-width="1.5"/>',
            f'<text x="{left+plot_w/2}" y="{height-28}" text-anchor="middle" class="label">Gap index n (between triples n and n+1)</text>',
            f'<text x="29" y="{top+plot_h/2}" text-anchor="middle" class="label" transform="rotate(-90 29 {top+plot_h/2})">log₁₀(Δcₙ)</text>',
        ]
    )

    # Preserve sequential geometry with a quiet neutral line.
    points = " ".join(
        f"{x_coord(index):.2f},{y_coord(value):.2f}"
        for index, value in enumerate(values, start=1)
    )
    lines.append(
        f'<polyline points="{points}" fill="none" stroke="#7e8790" stroke-width="0.40" opacity="0.28"/>'
    )

    # A point at gap n is encoded by the arriving (n+1)-st triple.
    for index, value in enumerate(values, start=1):
        arriving = triples[index]
        d, k = arriving[5], arriving[6]
        x, y = x_coord(index), y_coord(value)
        color = channel_color(k, max_k)
        if d == 1:
            lines.append(f'<circle cx="{x:.2f}" cy="{y:.2f}" r="2.50" fill="{color}" fill-opacity="0.70"/>')
        else:
            radius = 3.50
            lines.append(
                f'<path d="M {x:.2f} {y-radius:.2f} L {x+radius:.2f} {y:.2f} L {x:.2f} {y+radius:.2f} L {x-radius:.2f} {y:.2f} Z" fill="{color}" fill-opacity="0.70"/>'
            )

    # Inset: cumulative sum of the plotted ordinate.  Its near coincidence
    # with the endpoint chord makes the approximately linear growth explicit.
    cumulative: list[float] = []
    running = 0.0
    for value in values:
        running += value
        cumulative.append(running)
    inset_x, inset_y, inset_w, inset_h = 855, 490, 445, 175
    inset_left, inset_right, inset_top, inset_bottom = 48, 14, 30, 30
    inner_w = inset_w - inset_left - inset_right
    inner_h = inset_h - inset_top - inset_bottom

    def inset_x_coord(index: int) -> float:
        return inset_x + inset_left + (index - 1) * inner_w / (len(cumulative) - 1)

    def inset_y_coord(value: float) -> float:
        return inset_y + inset_top + (cumulative[-1] - value) * inner_h / cumulative[-1]

    lines.append(
        f'<rect x="{inset_x}" y="{inset_y}" width="{inset_w}" height="{inset_h}" rx="4" fill="#fff" fill-opacity="0.94" stroke="#777" stroke-width="0.8"/>'
    )
    lines.append(
        f'<text x="{inset_x+inset_w/2}" y="{inset_y+19}" text-anchor="middle" class="legend">Cumulative Sₙ (blue); endpoint chord (red dashed)</text>'
    )
    for fraction, label in ((0.0, "0"), (0.5, "15,000"), (1.0, "30,000")):
        value = fraction * cumulative[-1]
        y = inset_y_coord(value)
        lines.append(f'<line x1="{inset_x+inset_left}" y1="{y:.2f}" x2="{inset_x+inset_w-inset_right}" y2="{y:.2f}" stroke="#e1e1de" stroke-width="0.7"/>')
        lines.append(f'<text x="{inset_x+inset_left-6}" y="{y+4:.2f}" text-anchor="end" class="inset">{label}</text>')
    for index, label in ((1, "1"), ((len(cumulative)+1)//2, "2,500"), (len(cumulative), "4,999")):
        x = inset_x_coord(index)
        lines.append(f'<text x="{x:.2f}" y="{inset_y+inset_h-8}" text-anchor="middle" class="inset">{label}</text>')
    lines.append(
        f'<line x1="{inset_x_coord(1):.2f}" y1="{inset_y_coord(cumulative[0]):.2f}" x2="{inset_x_coord(len(cumulative)):.2f}" y2="{inset_y_coord(cumulative[-1]):.2f}" stroke="#b33a3a" stroke-width="1.1" stroke-dasharray="5 4" opacity="0.8"/>'
    )
    cumulative_points = " ".join(
        f"{inset_x_coord(index):.2f},{inset_y_coord(value):.2f}"
        for index, value in enumerate(cumulative, start=1)
    )
    lines.append(
        f'<polyline points="{cumulative_points}" fill="none" stroke="#174f73" stroke-width="1.8"/>'
    )

    lines.append('</svg>')
    SVG_PATH.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> None:
    triples = enumerate_first_triples(COUNT)
    write_csv(triples)
    write_svg(triples)
    print(SVG_PATH)
    print(CSV_PATH)
    print(f"channels: 0..{max(triple[6] for triple in triples)}")


if __name__ == "__main__":
    main()
