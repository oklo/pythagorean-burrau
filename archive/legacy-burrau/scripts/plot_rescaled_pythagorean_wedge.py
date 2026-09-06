#!/usr/bin/env python3
"""Plot the narrow Pythagorean u interval as an exaggerated logarithmic wedge."""

from __future__ import annotations

import math

from plot_colored_primitive_c_gaps import (
    COUNT,
    LOWER,
    ROOT,
    UPPER,
    channel_color,
    enumerate_first_triples,
)


SVG_PATH = ROOT / "plots" / "rescaled_logarithmic_pythagorean_wedge_first_5000.svg"


def main() -> None:
    triples = enumerate_first_triples(COUNT)
    width, height = 1300, 900
    origin_x, origin_y = 650.0, 835.0
    inner_radius, outer_radius = 70.0, 680.0
    display_angle_low = math.radians(60.0)
    display_angle_high = math.radians(120.0)
    physical_angle_low = 2.0 * math.atan(float(LOWER))
    physical_angle_high = 2.0 * math.atan(float(UPPER))
    max_k = max(triple[6] for triple in triples)

    def physical_fraction(p: int, q: int) -> float:
        theta = 2.0 * math.atan(p / q)
        return (theta - physical_angle_low) / (physical_angle_high - physical_angle_low)

    def display_angle(fraction: float) -> float:
        return display_angle_low + fraction * (display_angle_high - display_angle_low)

    def radial_coordinate(c: int | float) -> float:
        # Fixed decade scale: c=10^4 at the inner ring and c=10^10 at outer.
        return inner_radius + (math.log10(c) - 4.0) * (outer_radius - inner_radius) / 6.0

    def point(radius: float, angle: float) -> tuple[float, float]:
        return origin_x + radius * math.cos(angle), origin_y - radius * math.sin(angle)

    lines = [
        '<?xml version="1.0" encoding="UTF-8"?>',
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}">',
        '<rect width="100%" height="100%" fill="#fbfaf7"/>',
        '<style>text{font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif;fill:#20242a}.head{font-size:20px;fill:#333}.sub{font-size:15px;fill:#555}.tick{font-size:14px;fill:#555}.legend{font-size:13px;fill:#444}</style>',
        f'<text x="{width/2}" y="31" text-anchor="middle" class="head">The interval 0.29 ≤ u ≤ 0.290002, with angle expanded and radius logarithmically compressed</text>',
        f'<text x="{width/2}" y="56" text-anchor="middle" class="sub">display angle = 60° × fractional physical-wedge position; radial coordinate = log₁₀(c)</text>',
    ]

    # Channel color strip.
    bar_x, bar_y, bar_w, bar_h = 440, 76, 420, 12
    cell_w = bar_w / (max_k + 1)
    for k in range(max_k + 1):
        lines.append(
            f'<rect x="{bar_x+k*cell_w:.2f}" y="{bar_y}" width="{cell_w+0.2:.2f}" height="{bar_h}" fill="{channel_color(k, max_k)}"/>'
        )
    lines.extend(
        [
            f'<text x="{bar_x-9}" y="{bar_y+11}" text-anchor="end" class="legend">channel k</text>',
            f'<text x="{bar_x}" y="{bar_y+29}" text-anchor="middle" class="legend">0</text>',
            f'<text x="{bar_x+bar_w/2}" y="{bar_y+29}" text-anchor="middle" class="legend">{max_k//2}</text>',
            f'<text x="{bar_x+bar_w}" y="{bar_y+29}" text-anchor="middle" class="legend">{max_k}</text>',
        ]
    )

    # Radial decade arcs and labels.
    for exponent in range(4, 11):
        radius = radial_coordinate(10**exponent)
        samples = []
        for step in range(81):
            angle = display_angle_low + step * (display_angle_high - display_angle_low) / 80
            x, y = point(radius, angle)
            samples.append(f"{x:.2f},{y:.2f}")
        lines.append(
            f'<polyline points="{" ".join(samples)}" fill="none" stroke="#d4d5d2" stroke-width="0.9"/>'
        )
        label_x, label_y = point(radius, display_angle_low)
        lines.append(
            f'<text x="{label_x+9:.2f}" y="{label_y+4:.2f}" class="tick">10<tspan baseline-shift="super" font-size="10">{exponent}</tspan></text>'
        )

    # Wedge boundaries and center guide.
    for fraction, stroke, dash in ((0.0, "#444", ""), (0.5, "#bfc2c0", ' stroke-dasharray="5 5"'), (1.0, "#444", "")):
        angle = display_angle(fraction)
        x1, y1 = point(inner_radius, angle)
        x2, y2 = point(outer_radius, angle)
        lines.append(
            f'<line x1="{x1:.2f}" y1="{y1:.2f}" x2="{x2:.2f}" y2="{y2:.2f}" stroke="{stroke}" stroke-width="1.1"{dash}/>'
        )

    low_x, low_y = point(outer_radius + 18, display_angle_low)
    high_x, high_y = point(outer_radius + 18, display_angle_high)
    lines.extend(
        [
            f'<text x="{low_x+4:.2f}" y="{low_y+8:.2f}" text-anchor="start" class="tick">u=0.29</text>',
            f'<text x="{high_x-4:.2f}" y="{high_y+8:.2f}" text-anchor="end" class="tick">u=0.290002</text>',
        ]
    )

    # Plot triangles; angle gives true fractional location in the wedge, while
    # the displayed opening angle is intentionally exaggerated to 60 degrees.
    for c, _short, _long, p, q, d, k in triples:
        fraction = min(1.0, max(0.0, physical_fraction(p, q)))
        x, y = point(radial_coordinate(c), display_angle(fraction))
        color = channel_color(k, max_k)
        if d == 1:
            lines.append(
                f'<circle cx="{x:.2f}" cy="{y:.2f}" r="2.0" fill="{color}" fill-opacity="0.68"/>'
            )
        else:
            radius = 2.7
            lines.append(
                f'<path d="M {x:.2f} {y-radius:.2f} L {x+radius:.2f} {y:.2f} L {x:.2f} {y+radius:.2f} L {x-radius:.2f} {y:.2f} Z" fill="{color}" fill-opacity="0.68"/>'
            )

    physical_width_deg = math.degrees(physical_angle_high - physical_angle_low)
    expansion = 60.0 / physical_width_deg
    lines.extend(
        [
            f'<text x="{width/2}" y="{height-36}" text-anchor="middle" class="sub">Actual physical angular width: {physical_width_deg:.9f}° ({physical_width_deg*3600:.3f} arcsec); display expansion: ×{expansion:,.0f}</text>',
            f'<circle cx="1025" cy="78" r="3" fill="#333"/><text x="1036" y="83" class="legend">d=1: opposite parity</text>',
            f'<path d="M 1025 93 L 1029 97 L 1025 101 L 1021 97 Z" fill="#333"/><text x="1036" y="102" class="legend">d=2: odd–odd</text>',
            '</svg>',
        ]
    )
    SVG_PATH.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(SVG_PATH)


if __name__ == "__main__":
    main()
