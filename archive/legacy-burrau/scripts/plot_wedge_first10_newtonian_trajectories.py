#!/usr/bin/env python3
"""Exaggerated 0.01-radian Pythagorean wedge plus ten Newtonian tracks.

The wedge contains the first ten primitive triples by hypotenuse.  Their
normalized, center-of-mass Newtonian trajectories are integrated with DOP853
to t=4 and overplotted.  This is an ordinary numerical visualization, not a
validated trajectory certificate.
"""

from __future__ import annotations

import csv
import math
import sys
from fractions import Fraction
from math import gcd
from pathlib import Path

import numpy as np
from scipy.integrate import solve_ivp


ROOT = Path(__file__).resolve().parents[1]
MAIN_REPO = Path("/Users/greglaughlin/Projects/pythagorean-burrau")
sys.path.insert(0, str(MAIN_REPO))

from src.dynamics.cartesian import (  # noqa: E402
    energy,
    initial_state_real,
    mutual_distances,
    right_hand_side,
)


U_LOWER = Fraction(29, 100)
PHYSICAL_WEDGE_WIDTH = 0.01
COUNT = 10
END_TIME = 8.0
SVG_PATH = ROOT / "plots" / "pythagorean_wedge_0p01_first10_trajectories_t8.svg"
CSV_PATH = ROOT / "data" / "pythagorean_wedge_0p01_first10_trajectories_t8.csv"

BODY_COLORS = ("#e63946", "#2a9d4b", "#2775c9")


def enumerate_triples() -> tuple[list[tuple[int, int, int, int, int, int]], float]:
    theta_lower = 2.0 * math.atan(float(U_LOWER))
    u_upper = math.tan((theta_lower + PHYSICAL_WEDGE_WIDTH) / 2.0)
    triples: list[tuple[int, int, int, int, int, int]] = []
    q = 1
    while True:
        for p in range(1, q):
            if gcd(p, q) != 1 or not float(U_LOWER) <= p / q <= u_upper:
                continue
            d = 2 if (p & 1 and q & 1) else 1
            short = 2 * p * q // d
            long = (q * q - p * p) // d
            c = (q * q + p * p) // d
            triples.append((c, min(short, long), max(short, long), p, q, d))
        if len(triples) >= COUNT:
            triples.sort()
            cutoff = triples[COUNT - 1][0]
            if (q + 1) * (q + 1) > 2 * cutoff:
                return triples[:COUNT], u_upper
        q += 1


def integrate(
    triples: list[tuple[int, int, int, int, int, int]],
) -> tuple[list[np.ndarray], list[dict[str, float | int | str]]]:
    tracks: list[np.ndarray] = []
    records: list[dict[str, float | int | str]] = []
    for index, (c, short, long, p, q, d) in enumerate(triples, start=1):
        u = p / q
        masses, state0 = initial_state_real(u)
        energy0 = energy(state0, masses)
        solution = solve_ivp(
            right_hand_side,
            (0.0, END_TIME),
            state0,
            args=(masses,),
            method="DOP853",
            rtol=2e-12,
            atol=2e-14,
            max_step=0.003,
            dense_output=True,
        )
        if not solution.success or solution.t[-1] < END_TIME:
            raise RuntimeError(f"integration {index} failed: {solution.message}")

        # Uniform samples make quiet arcs smooth; adaptive solver nodes resolve
        # the fast geometry at close passages.
        sample_times = np.unique(
            np.concatenate((np.linspace(0.0, END_TIME, 6001), solution.t))
        )
        states = solution.sol(sample_times)
        positions = states[:6].T.reshape(-1, 3, 2)
        tracks.append(positions)

        # Audit on the union above: the adaptive nodes are essential because
        # a uniform physical-time grid can step over a very narrow pericenter.
        min_separation = min(
            float(np.min(mutual_distances(states[:, column])))
            for column in range(states.shape[1])
        )
        max_relative_energy_error = max(
            abs((energy(states[:, column], masses) - energy0) / energy0)
            for column in range(states.shape[1])
        )
        records.append(
            {
                "index": index,
                "short_leg": short,
                "long_leg": long,
                "hypotenuse": c,
                "p": p,
                "q": q,
                "d": d,
                "u": f"{u:.16g}",
                "minimum_sampled_separation": f"{min_separation:.12g}",
                "maximum_sampled_relative_energy_error": f"{max_relative_energy_error:.12g}",
            }
        )
    return tracks, records


def write_csv(records: list[dict[str, float | int | str]]) -> None:
    with CSV_PATH.open("w", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fieldnames=list(records[0]))
        writer.writeheader()
        writer.writerows(records)


def write_svg(
    triples: list[tuple[int, int, int, int, int, int]],
    tracks: list[np.ndarray],
    records: list[dict[str, float | int | str]],
    u_upper: float,
) -> None:
    width, height = 1900, 1000
    lines: list[str] = [
        '<?xml version="1.0" encoding="UTF-8"?>',
        f'<svg xmlns="http://www.w3.org/2000/svg" width="{width}" height="{height}" viewBox="0 0 {width} {height}">',
        '<rect width="100%" height="100%" fill="#fbfaf7"/>',
        '<style>text{font-family:-apple-system,BlinkMacSystemFont,"Segoe UI",sans-serif;fill:#30343a}.tick{font-size:14px}.small{font-size:14px}</style>',
    ]

    # ---------- Left panel: logarithmic, angularly exaggerated wedge ----------
    wedge_origin = np.array([360.0, 900.0])
    display_low = math.radians(55.0)
    display_high = math.radians(125.0)
    inner_radius, outer_radius = 70.0, 430.0
    theta_lower = 2.0 * math.atan(float(U_LOWER))

    def wedge_point(radius: float, angle: float) -> tuple[float, float]:
        return (
            float(wedge_origin[0] + radius * math.cos(angle)),
            float(wedge_origin[1] - radius * math.sin(angle)),
        )

    def wedge_radius(c: float) -> float:
        return inner_radius + (math.log10(c) - 2.0) * (outer_radius - inner_radius) / 2.0

    def wedge_angle(p: int, q: int) -> float:
        fraction = (2.0 * math.atan(p / q) - theta_lower) / PHYSICAL_WEDGE_WIDTH
        return display_low + fraction * (display_high - display_low)

    for exponent in (2, 3, 4):
        radius = wedge_radius(10**exponent)
        points = []
        for step in range(101):
            angle = display_low + step * (display_high - display_low) / 100
            x, y = wedge_point(radius, angle)
            points.append(f"{x:.2f},{y:.2f}")
        lines.append(
            f'<polyline points="{" ".join(points)}" fill="none" stroke="#d4d5d2" stroke-width="1"/>'
        )
    for angle in (display_low, display_high):
        x1, y1 = wedge_point(inner_radius, angle)
        x2, y2 = wedge_point(outer_radius, angle)
        lines.append(
            f'<line x1="{x1:.2f}" y1="{y1:.2f}" x2="{x2:.2f}" y2="{y2:.2f}" stroke="#444" stroke-width="1.2"/>'
        )

    # Compact exact triple list.
    for row, (_c, short, long, p, q, _d) in enumerate(triples, start=1):
        column = 0 if row <= 5 else 1
        local_row = row if row <= 5 else row - 5
        tx = 54 + column * 330
        ty = 36 + (local_row - 1) * 29
        lines.append(
            f'<text x="{tx}" y="{ty}" class="small">{row}. ({short:,}, {long:,}, {_c:,})   u={p}/{q}</text>'
        )

    for index, (c, _short, _long, p, q, d) in enumerate(triples, start=1):
        x, y = wedge_point(wedge_radius(c), wedge_angle(p, q))
        if d == 1:
            lines.append(f'<circle cx="{x:.2f}" cy="{y:.2f}" r="5.2" fill="#222" fill-opacity="0.78"/>')
        else:
            radius = 7.0
            lines.append(
                f'<path d="M {x:.2f} {y-radius:.2f} L {x+radius:.2f} {y:.2f} L {x:.2f} {y+radius:.2f} L {x-radius:.2f} {y:.2f} Z" fill="#222" fill-opacity="0.78"/>'
            )
        lines.append(
            f'<text x="{x+8:.2f}" y="{y-7:.2f}" class="tick">{index}</text>'
        )

    # ---------- Right panel: overlaid physical trajectories ----------
    panel_left, panel_right, panel_top, panel_bottom = 760.0, 1880.0, 25.0, 975.0
    all_positions = np.concatenate(tracks, axis=0)
    xmin, ymin = np.min(all_positions, axis=(0, 1))
    xmax, ymax = np.max(all_positions, axis=(0, 1))
    xrange = xmax - xmin
    yrange = ymax - ymin
    xmin -= 0.07 * xrange
    xmax += 0.07 * xrange
    ymin -= 0.07 * yrange
    ymax += 0.07 * yrange
    scale = min((panel_right - panel_left) / (xmax - xmin), (panel_bottom - panel_top) / (ymax - ymin))
    xcenter = (xmin + xmax) / 2
    ycenter = (ymin + ymax) / 2
    screen_center_x = (panel_left + panel_right) / 2
    screen_center_y = (panel_top + panel_bottom) / 2

    def screen_point(position: np.ndarray) -> tuple[float, float]:
        return (
            screen_center_x + scale * (float(position[0]) - xcenter),
            screen_center_y - scale * (float(position[1]) - ycenter),
        )

    lines.append(
        f'<rect x="{panel_left}" y="{panel_top}" width="{panel_right-panel_left}" height="{panel_bottom-panel_top}" fill="#fff" fill-opacity="0.42" stroke="#999" stroke-width="0.8"/>'
    )
    # Zero axes when they lie in the view.
    zero_x, _ = screen_point(np.array([0.0, ycenter]))
    _, zero_y = screen_point(np.array([xcenter, 0.0]))
    if panel_left <= zero_x <= panel_right:
        lines.append(f'<line x1="{zero_x:.2f}" y1="{panel_top}" x2="{zero_x:.2f}" y2="{panel_bottom}" stroke="#d0d0cd" stroke-dasharray="5 5"/>')
    if panel_top <= zero_y <= panel_bottom:
        lines.append(f'<line x1="{panel_left}" y1="{zero_y:.2f}" x2="{panel_right}" y2="{zero_y:.2f}" stroke="#d0d0cd" stroke-dasharray="5 5"/>')

    # Initial triangles, followed by translucent trajectories.
    for track in tracks:
        initial = [screen_point(track[0, body]) for body in range(3)]
        initial.append(initial[0])
        lines.append(
            f'<polyline points="{" ".join(f"{x:.2f},{y:.2f}" for x,y in initial)}" fill="none" stroke="#555" stroke-width="0.8" opacity="0.13"/>'
        )
    for body, color in enumerate(BODY_COLORS):
        for track in tracks:
            points = " ".join(
                f"{x:.2f},{y:.2f}" for x, y in (screen_point(position) for position in track[:, body])
            )
            lines.append(
                f'<polyline points="{points}" fill="none" stroke="{color}" stroke-width="1.35" stroke-opacity="0.22" stroke-linecap="round" stroke-linejoin="round"/>'
            )

    # Start and terminal markers.
    for body, color in enumerate(BODY_COLORS):
        for track in tracks:
            sx, sy = screen_point(track[0, body])
            ex, ey = screen_point(track[-1, body])
            lines.append(f'<circle cx="{sx:.2f}" cy="{sy:.2f}" r="4.0" fill="{color}" fill-opacity="0.75"/>')
            lines.append(f'<circle cx="{ex:.2f}" cy="{ey:.2f}" r="2.7" fill="{color}" fill-opacity="0.45"/>')

    lines.append('</svg>')
    SVG_PATH.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> None:
    triples, u_upper = enumerate_triples()
    tracks, records = integrate(triples)
    write_csv(records)
    write_svg(triples, tracks, records, u_upper)
    print(SVG_PATH)
    print(CSV_PATH)


if __name__ == "__main__":
    main()
