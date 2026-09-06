#!/usr/bin/env python3
"""Minimally annotated Oklo figure: shrinking fans and their trajectories.

The complete fundamental Pythagorean fan hands off to an interval anchored at
u=0.29.  Four subsequent panels tighten by half a decade per row.  Each
current interval is expanded to a one-radian display fan; its child is drawn
inside it and becomes the full fan in the following row.  Radius in the left
panels is affine in log10(c), using one common scale.  Each right panel
overlays trajectories from the ten lowest-hypotenuse primitive triples in the
corresponding current interval.

The trajectory dots are uniform in physical time.  Their opacity is also
reduced as inertial speed increases, so close, fast passages remain visible
without dominating the slow brake neighborhoods.  This is an ordinary
numerical visualization, not a validated dynamical certificate.
"""

from __future__ import annotations

import json
import math
import sys
from decimal import Decimal, getcontext
from fractions import Fraction
from math import gcd
from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.colors as mcolors
import matplotlib.patheffects as path_effects
import matplotlib.pyplot as plt
import numpy as np
from scipy.integrate import solve_ivp
from scipy.interpolate import CubicHermiteSpline


ROOT = Path(__file__).resolve().parents[1]
MAIN_REPO = Path("/Users/greglaughlin/Projects/pythagorean-burrau")
sys.path.insert(0, str(MAIN_REPO))

from src.dynamics.cartesian import (  # noqa: E402
    initial_state_real,
    mutual_distances,
    right_hand_side,
)


OUTPUT = ROOT / "plots" / "oklo_pythagorean_fan_trajectory_progression.png"
AUDIT = ROOT / "data" / "oklo_pythagorean_fan_trajectory_progression.json"
CACHE_DIR = ROOT / "data" / "oklo_fan_trajectory_cache"

U_LOWER = Fraction(29, 100)
getcontext().prec = 50
HALF_DECADE = Decimal(10).sqrt()
DETAIL_WIDTHS = tuple(
    Fraction(Decimal("0.01") / HALF_DECADE**level) for level in range(6)
)
FUNDAMENTAL_UPPER = Fraction(Decimal(2).sqrt() - 1)
LEVEL_INTERVALS = ((Fraction(0), FUNDAMENTAL_UPPER),) + tuple(
    (U_LOWER, U_LOWER + width) for width in DETAIL_WIDTHS
)
DISPLAY_OPENING = 1.0
FAN_COUNT = 400
TRAJECTORY_COUNT = 10
END_TIME = 8.0
DISPLAY_END_TIME = 4.0
UNIFORM_SAMPLES = 8001
DISPLAY_SAMPLES = 16001
ORBIT_XLIM = (-0.65, 0.88)
ORBIT_YLIM = (-0.55, 0.55)

BACKGROUND = "#fbfaf7"
LEVEL_COLORS = (
    "#424950",
    "#d18f20",
    "#278f82",
    "#75599e",
    "#c9554b",
    "#3775ad",
    "#6f7b3b",
)
BODY_COLORS = ("#dc3f45", "#299765", "#2567b8")


Triple = tuple[int, int, int, int, int, int]


def ceil_fraction_times(value: Fraction, multiplier: int) -> int:
    numerator = value.numerator * multiplier
    return (numerator + value.denominator - 1) // value.denominator


def floor_fraction_times(value: Fraction, multiplier: int) -> int:
    return value.numerator * multiplier // value.denominator


def enumerate_first_triples(lower: Fraction, upper: Fraction, count: int) -> list[Triple]:
    """Enumerate the first primitive triples by hypotenuse in [lower, upper]."""
    triples: list[Triple] = []
    q = 2
    while True:
        p_min = max(1, ceil_fraction_times(lower, q))
        p_max = min(q - 1, floor_fraction_times(upper, q))
        for p in range(p_min, p_max + 1):
            if gcd(p, q) != 1:
                continue
            divisor = 2 if (p & 1 and q & 1) else 1
            leg_b = 2 * p * q // divisor
            leg_a = (q * q - p * p) // divisor
            hypotenuse = (q * q + p * p) // divisor
            triples.append(
                (
                    hypotenuse,
                    min(leg_a, leg_b),
                    max(leg_a, leg_b),
                    p,
                    q,
                    divisor,
                )
            )
        if len(triples) >= count:
            triples.sort()
            cutoff = triples[count - 1][0]
            # For all future denominators, c >= q_future^2/2.
            if (q + 1) * (q + 1) > 2 * cutoff:
                return triples[:count]
        q += 1


def trajectory_cache_path(p: int, q: int) -> Path:
    return CACHE_DIR / f"u_{p}_{q}_t8.npz"


def integrate_trajectory(p: int, q: int) -> dict[str, np.ndarray | float | bool | str]:
    cache_path = trajectory_cache_path(p, q)
    if cache_path.exists():
        with np.load(cache_path) as cached:
            return {
                "times": cached["times"],
                "positions": cached["positions"],
                "velocities": cached["velocities"],
                "minimum_sampled_separation": float(cached["minimum_sampled_separation"]),
                "success": bool(cached["success"]) if "success" in cached.files else True,
                "message": str(cached["message"]) if "message" in cached.files else "cached",
            }

    u = p / q
    masses, state0 = initial_state_real(u)
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
    # Uniform physical-time samples carry the velocity cue.  Adaptive nodes
    # are retained to prevent a fast close passage from becoming a chord.  If
    # the classical integration terminates at a collision singularity, retain
    # only its preterminal segment and never extrapolate through it.
    terminal_time = float(solution.t[-1])
    times = np.unique(
        np.concatenate([np.linspace(0.0, terminal_time, UNIFORM_SAMPLES), solution.t])
    )
    states = solution.sol(times).T
    positions = states[:, :6].reshape(-1, 3, 2)
    velocities = states[:, 6:12].reshape(-1, 3, 2)
    minimum_separation = min(
        float(np.min(mutual_distances(states[index])))
        for index in range(states.shape[0])
    )

    CACHE_DIR.mkdir(parents=True, exist_ok=True)
    np.savez_compressed(
        cache_path,
        times=times,
        positions=positions,
        velocities=velocities,
        minimum_sampled_separation=np.array(minimum_separation),
        success=np.array(solution.success),
        message=np.array(solution.message),
    )
    return {
        "times": times,
        "positions": positions,
        "velocities": velocities,
        "minimum_sampled_separation": minimum_separation,
        "success": True,
        "message": solution.message,
    }


def speed_rgba(color: str, speed: np.ndarray, reference_speed: float) -> np.ndarray:
    rgb = np.asarray(mcolors.to_rgb(color))
    ratio = speed / max(reference_speed, 1e-14)
    # A nonzero floor keeps fast passages legible.  The larger slow-speed term
    # still makes the brake neighborhoods visibly denser.
    alpha = 0.00250 + 0.0200 / (1.0 + ratio**1.70)
    rgba = np.empty((speed.size, 4))
    rgba[:, :3] = rgb
    rgba[:, 3] = alpha
    return rgba


def uniformly_resample(
    track: dict[str, np.ndarray | float | bool | str],
) -> dict[str, np.ndarray]:
    """Remove all adaptive-step density from a cached physical trajectory.

    A cubic Hermite interpolant uses both positions and inertial velocities at
    the accurately integrated cache nodes.  Every body is then evaluated at
    the same uniform physical times; the derivative of the same interpolant
    supplies the body-specific speed used for opacity.
    """
    source_times = np.asarray(track["times"])
    source_positions = np.asarray(track["positions"])
    source_velocities = np.asarray(track["velocities"])
    spline = CubicHermiteSpline(
        source_times,
        source_positions,
        source_velocities,
        axis=0,
    )
    display_end = min(DISPLAY_END_TIME, float(source_times[-1]))
    display_dt = DISPLAY_END_TIME / (DISPLAY_SAMPLES - 1)
    display_count = max(2, int(math.floor(display_end / display_dt)) + 1)
    display_times = np.linspace(0.0, display_end, display_count)
    return {
        "times": display_times,
        "positions": np.asarray(spline(display_times)),
        "velocities": np.asarray(spline(display_times, 1)),
    }


def main() -> None:
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    AUDIT.parent.mkdir(parents=True, exist_ok=True)

    level_triples = [
        enumerate_first_triples(lower, upper, FAN_COUNT)
        for lower, upper in LEVEL_INTERVALS
    ]
    fan_rows: list[dict[str, object]] = []
    unique_leads: dict[tuple[int, int], dict[str, np.ndarray | float | bool | str]] = {}
    # Five displayed rows: the fundamental overview plus four successive
    # half-decade magnifications.  The sixth interval is the final child only.
    for level in range(len(LEVEL_INTERVALS) - 2):
        lower, upper = LEVEL_INTERVALS[level]
        child_lower, child_upper = LEVEL_INTERVALS[level + 1]
        triples = level_triples[level]
        child_triples = level_triples[level + 1]
        leads = triples[:TRAJECTORY_COUNT]
        for _c, _a, _b, p, q, _divisor in leads:
            unique_leads.setdefault((p, q), integrate_trajectory(p, q))
        fan_rows.append(
            {
                "lower": lower,
                "upper": upper,
                "triples": triples,
                "child_lower": child_lower,
                "child_upper": child_upper,
                "child_triples": child_triples,
                "leads": leads,
                "level": level,
            }
        )

    rendered_tracks = {
        key: uniformly_resample(track) for key, track in unique_leads.items()
    }
    global_speed_reference = float(
        np.quantile(
            np.concatenate(
                [
                    np.linalg.norm(track["velocities"], axis=2).reshape(-1)
                    for track in rendered_tracks.values()
                ]
            ),
            0.52,
        )
    )

    all_c = [
        triple[0]
        for triples in level_triples
        for triple in triples
    ]
    log_c_min = math.floor(math.log10(min(all_c)))
    log_c_max = math.ceil(math.log10(max(all_c)))

    fig = plt.figure(
        figsize=(12.0, 2.6 * len(fan_rows)), dpi=240, facecolor=BACKGROUND
    )
    grid = fig.add_gridspec(
        len(fan_rows),
        2,
        width_ratios=(0.40, 0.60),
        left=0.010,
        right=0.996,
        bottom=0.006,
        top=0.994,
        wspace=-0.035,
        hspace=-0.015,
    )

    audit_rows: list[dict[str, object]] = []
    progression_labels: list[tuple[object, object]] = []
    radius_labels: list[object] = []
    for row_index, row in enumerate(fan_rows):
        lower = row["lower"]
        upper = row["upper"]
        triples = row["triples"]
        child_lower = row["child_lower"]
        child_upper = row["child_upper"]
        child_triples = row["child_triples"]
        leads = row["leads"]
        level = row["level"]
        assert isinstance(lower, Fraction)
        assert isinstance(upper, Fraction)
        assert isinstance(triples, list)
        assert isinstance(child_lower, Fraction)
        assert isinstance(child_upper, Fraction)
        assert isinstance(child_triples, list)
        assert isinstance(leads, list)
        assert isinstance(level, int)

        # -------- Left: nested one-radian display fan, opening right. --------
        fan_ax = fig.add_subplot(grid[row_index, 0])
        fan_ax.set_facecolor(BACKGROUND)
        fan_ax.set_aspect("equal", adjustable="box")
        fan_ax.set_anchor("E")
        fan_ax.set_xlim(-0.015, 1.015)
        fan_ax.set_ylim(-0.755, 0.525)
        fan_ax.axis("off")

        theta_lower = 2.0 * math.atan(float(lower))
        theta_upper = 2.0 * math.atan(float(upper))
        theta_child_lower = 2.0 * math.atan(float(child_lower))
        theta_child_upper = 2.0 * math.atan(float(child_upper))
        display_low = -0.5 * DISPLAY_OPENING
        display_high = +0.5 * DISPLAY_OPENING
        radial_inner, radial_outer = 0.040, 0.995
        current_color = LEVEL_COLORS[level]
        child_color = LEVEL_COLORS[level + 1]

        def display_angle(theta: float) -> float:
            return display_low + DISPLAY_OPENING * (
                (theta - theta_lower) / (theta_upper - theta_lower)
            )

        display_child_low = display_angle(theta_child_lower)
        display_child_high = display_angle(theta_child_upper)

        def radial_coordinate(c: int | float) -> float:
            return radial_inner + (
                (math.log10(c) - log_c_min)
                / max(1.0, log_c_max - log_c_min)
                * (radial_outer - radial_inner)
            )

        parent_angles = np.linspace(display_low, display_high, 181)
        child_angles = np.linspace(display_child_low, display_child_high, 91)
        fan_ax.fill(
            np.concatenate([[0.0], radial_outer * np.cos(parent_angles), [0.0]]),
            np.concatenate([[0.0], radial_outer * np.sin(parent_angles), [0.0]]),
            color=current_color,
            alpha=0.035,
            linewidth=0,
            zorder=0,
        )
        fan_ax.fill(
            np.concatenate([[0.0], radial_outer * np.cos(child_angles), [0.0]]),
            np.concatenate([[0.0], radial_outer * np.sin(child_angles), [0.0]]),
            color=child_color,
            alpha=0.105,
            linewidth=0,
            zorder=0,
        )
        for angle in (display_low, display_high):
            fan_ax.plot(
                [0.0, radial_outer * math.cos(angle)],
                [0.0, radial_outer * math.sin(angle)],
                color=current_color,
                linewidth=0.82,
                alpha=0.72,
                solid_capstyle="round",
                zorder=1,
            )
        for angle in (display_child_low, display_child_high):
            fan_ax.plot(
                [0.0, radial_outer * math.cos(angle)],
                [0.0, radial_outer * math.sin(angle)],
                color=child_color,
                linewidth=1.05,
                alpha=0.90,
                solid_capstyle="round",
                zorder=2,
            )
        fan_ax.plot(
            radial_outer * np.cos(parent_angles),
            radial_outer * np.sin(parent_angles),
            color=current_color,
            linewidth=0.70,
            alpha=0.50,
            zorder=1,
        )

        # Unlabelled shared logarithmic-decade arcs.
        for exponent in range(log_c_min, log_c_max + 1):
            radius = radial_coordinate(10**exponent)
            fan_ax.plot(
                radius * np.cos(parent_angles),
                radius * np.sin(parent_angles),
                color="#a8aaab",
                linewidth=0.42,
                alpha=0.25,
                zorder=1,
            )

        lead_keys = {(triple[3], triple[4]) for triple in leads}
        def plot_cloud(cloud: list[Triple], color: str, alpha: float, zorder: int) -> None:
            for divisor, marker, size in ((1, "o", 3.0), (2, "D", 4.1)):
                selected = [triple for triple in cloud if triple[5] == divisor]
                angles = np.array(
                    [display_angle(2.0 * math.atan(triple[3] / triple[4])) for triple in selected]
                )
                radii = np.array([radial_coordinate(triple[0]) for triple in selected])
                fan_ax.scatter(
                    radii * np.cos(angles),
                    radii * np.sin(angles),
                    s=size,
                    marker=marker,
                    color=color,
                    alpha=alpha,
                    linewidths=0,
                    zorder=zorder,
                )

        plot_cloud(triples, current_color, 0.36, 3)
        plot_cloud(child_triples, child_color, 0.58, 4)

        # The child's outermost sampled primitive triple is the radial handoff:
        # the child interval expands to the complete fan on the following row.
        handoff_c = child_triples[-1][0]
        handoff_radius = radial_coordinate(handoff_c)
        handoff_angles = np.linspace(display_low, display_high, 241)
        fan_ax.plot(
            handoff_radius * np.cos(handoff_angles),
            handoff_radius * np.sin(handoff_angles),
            color=child_color,
            linewidth=1.45,
            alpha=0.88,
            zorder=5,
        )
        # Label the handoff outside the fan: just above its upper edge and with
        # the text extending leftward from the marked radial arc.
        number_x = handoff_radius * math.cos(display_high) - 0.012
        number_y = handoff_radius * math.sin(display_high) + 0.018
        number = fan_ax.text(
            number_x,
            number_y,
            f"{handoff_c:,}",
            ha="right",
            va="bottom",
            fontsize=12.0,
            fontfamily="DejaVu Sans",
            fontweight="bold",
            color=child_color,
            clip_on=False,
            zorder=9,
        )
        number.set_path_effects(
            [path_effects.withStroke(linewidth=2.0, foreground=BACKGROUND)]
        )
        radius_labels.append(number)

        plotted = triples + child_triples
        lowest = min(plotted, key=lambda item: item[0])
        highest = max(plotted, key=lambda item: item[0])
        progression_text = (
            f"({lowest[1]}, {lowest[2]}, {lowest[0]})  \u27f6  "
            f"({highest[1]}, {highest[2]}, {highest[0]})"
        )

        lead_angles = np.array(
            [display_angle(2.0 * math.atan(triple[3] / triple[4])) for triple in leads]
        )
        lead_radii = np.array([radial_coordinate(triple[0]) for triple in leads])
        fan_ax.scatter(
            lead_radii * np.cos(lead_angles),
            lead_radii * np.sin(lead_angles),
            s=17,
            marker="o",
            facecolors=BACKGROUND,
            edgecolors=current_color,
            alpha=0.96,
            linewidths=0.9,
            zorder=5,
        )

        # -------- Right: ten corresponding Newtonian launch plots. --------
        orbit_ax = fig.add_subplot(grid[row_index, 1])
        orbit_ax.set_facecolor(BACKGROUND)
        orbit_ax.set_aspect("equal", adjustable="box")
        orbit_ax.set_anchor("W")
        orbit_ax.set_xlim(*ORBIT_XLIM)
        orbit_ax.set_ylim(*ORBIT_YLIM)
        orbit_ax.axis("off")

        row_records: list[dict[str, object]] = []
        for c, short, long, p, q, divisor in leads:
            track = unique_leads[(p, q)]
            rendered = rendered_tracks[(p, q)]
            positions = rendered["positions"]
            velocities = rendered["velocities"]

            for body, color in enumerate(BODY_COLORS):
                body_speed = np.linalg.norm(velocities[:, body], axis=1)
                orbit_ax.scatter(
                    positions[:, body, 0],
                    positions[:, body, 1],
                    s=0.46,
                    c=speed_rgba(color, body_speed, global_speed_reference),
                    edgecolors="none",
                    linewidths=0,
                    rasterized=True,
                    zorder=2,
                )

            initial = np.vstack([positions[0], positions[0, 0]])
            orbit_ax.plot(
                initial[:, 0],
                initial[:, 1],
                color=current_color,
                linewidth=0.88,
                alpha=0.18,
                solid_capstyle="round",
                zorder=6,
            )
            for body, color in enumerate(BODY_COLORS):
                orbit_ax.scatter(
                    positions[0, body, 0],
                    positions[0, body, 1],
                    s=8,
                    color=color,
                    alpha=0.20,
                    edgecolors="none",
                    zorder=7,
                )

            row_records.append(
                {
                    "triple": [short, long, c],
                    "u": f"{p}/{q}",
                    "u_decimal": p / q,
                    "parity_divisor": divisor,
                    "minimum_sampled_separation": track[
                        "minimum_sampled_separation"
                    ],
                    "integration_reached_t8": track["success"],
                    "integration_terminal_time": float(np.asarray(track["times"])[-1]),
                    "integration_message": track["message"],
                }
            )

        progression = orbit_ax.text(
            0.985,
            0.020,
            progression_text,
            transform=orbit_ax.transAxes,
            ha="right",
            va="bottom",
            fontsize=12.0,
            fontfamily="DejaVu Sans",
            fontweight="bold",
            color=current_color,
            clip_on=False,
            zorder=20,
        )
        progression.set_path_effects(
            [path_effects.withStroke(linewidth=1.8, foreground=BACKGROUND)]
        )
        progression_labels.append((progression, orbit_ax))

        audit_rows.append(
            {
                "u_lower": str(lower),
                "u_upper": str(upper),
                "delta_u": str(upper - lower),
                "child_u_lower": str(child_lower),
                "child_u_upper": str(child_upper),
                "child_delta_u": str(child_upper - child_lower),
                "physical_opening_radians": theta_upper - theta_lower,
                "physical_opening_degrees": math.degrees(theta_upper - theta_lower),
                "display_opening_radians": DISPLAY_OPENING,
                "display_child_lower_angle": display_child_low,
                "display_child_upper_angle": display_child_high,
                "display_child_opening_radians": display_child_high - display_child_low,
                "fan_count": FAN_COUNT,
                "trajectory_count": TRAJECTORY_COUNT,
                "first_fan_hypotenuse": triples[0][0],
                "last_fan_hypotenuse": triples[-1][0],
                "handoff_hypotenuse": handoff_c,
                "lowest_plotted_triple": [lowest[1], lowest[2], lowest[0]],
                "highest_plotted_triple": [highest[1], highest[2], highest[0]],
                "trajectories": row_records,
            }
        )

    # Select one uniform type size from the longest progression after the axes
    # have their final pixel dimensions.  The limiting line occupies 96.5% of
    # its orbit panel; all handoff-radius labels use exactly the same size.
    trial_font_size = 12.0
    fig.canvas.draw()
    renderer = fig.canvas.get_renderer()
    fit_scales = []
    for label, axis in progression_labels:
        label_width = label.get_window_extent(renderer=renderer).width
        axis_width = axis.get_window_extent(renderer=renderer).width
        fit_scales.append(0.965 * axis_width / max(label_width, 1.0))
    uniform_font_size = min(trial_font_size, trial_font_size * min(fit_scales))
    for label, _axis in progression_labels:
        label.set_fontsize(uniform_font_size)
    for label in radius_labels:
        label.set_fontsize(uniform_font_size)

    fig.savefig(
        OUTPUT,
        dpi=240,
        facecolor=BACKGROUND,
        bbox_inches="tight",
        pad_inches=0,
    )
    plt.close(fig)

    AUDIT.write_text(
        json.dumps(
            {
                "status": "ORDINARY_NUMERICAL_EVIDENCE",
                "output": str(OUTPUT),
                "end_time": END_TIME,
                "display_end_time": DISPLAY_END_TIME,
                "uniform_physical_time_samples": UNIFORM_SAMPLES,
                "display_physical_time_samples_per_body": DISPLAY_SAMPLES,
                "display_speed_reference": global_speed_reference,
                "uniform_annotation_font_size_points": uniform_font_size,
                "opacity_mapping": "alpha = 0.00250 + 0.0200/(1+(speed/reference)^1.70), evaluated independently for every labelled body at uniform physical times; adaptive integration nodes never enter the rendered cadence",
                "trajectory_window": {
                    "xlim": ORBIT_XLIM,
                    "ylim": ORBIT_YLIM,
                    "scale_policy": "identical physical scale in every row; outgoing trajectories are clipped",
                },
                "radial_coordinate": "common affine scale in log10(c)",
                "angular_coordinate": "the full 0-to-45-degree fundamental wedge and then each current theta interval are expanded to one display radian; the next child interval is shown at its exact fractional position and width",
                "log10_c_scale": [log_c_min, log_c_max],
                "rows": audit_rows,
            },
            indent=2,
        )
        + "\n",
        encoding="utf-8",
    )
    print(OUTPUT)
    print(AUDIT)


if __name__ == "__main__":
    main()
