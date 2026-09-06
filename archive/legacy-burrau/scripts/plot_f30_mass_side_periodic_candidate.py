#!/usr/bin/env python3
"""Plot the ordinary-numerical F30 mass--side-tied periodic candidate.

The selected pair (2,3) is integrated in a global Levi--Civita chart.  The
candidate is collision-free and periodic to ordinary numerical precision, but
it is not Pythagorean: m1^2 + m2^2 - m3^2 is approximately -0.003356.
"""

from __future__ import annotations

from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.pyplot as plt
import numpy as np
from scipy.integrate import solve_ivp
from scipy.optimize import root


ROOT = Path(__file__).resolve().parents[1]
OUTPUT = ROOT / "plots" / "f30_mass_side_periodic_candidate.png"
AUDIT = ROOT / "data" / "f30_mass_side_periodic_candidate_plot_audit.txt"


def initial_state(parameters: np.ndarray) -> np.ndarray:
    wr, wi, _, _, m2 = map(float, parameters)
    radius = wr * wr + wi * wi
    gx = wr * wr - wi * wi
    gy = 2.0 * wr * wi
    pair_mass = m2 + 1.0
    return np.array(
        [
            wr,
            wi,
            0.0,
            0.0,
            -pair_mass / radius,
            (-m2 - 1.0 - gx) / pair_mass,
            -gy / pair_mass,
            0.0,
            0.0,
            0.0,
        ]
    )


def rhs(
    _scaled_time: float,
    state: np.ndarray,
    m1: float,
    m2: float,
    duration: float,
) -> np.ndarray:
    w = complex(state[0], state[1])
    z = complex(state[2], state[3])
    pair_energy = state[4]
    complement = complex(state[5], state[6])
    complement_velocity = complex(state[7], state[8])
    radius = abs(w) ** 2
    selected = w * w
    pair_mass = m2 + 1.0
    total_mass = m1 + m2 + 1.0
    d12 = complement + selected / pair_mass
    d13 = complement - m2 * selected / pair_mass
    external = m1 * (d13 / abs(d13) ** 3 - d12 / abs(d12) ** 3)
    complement_acceleration = -total_mass / pair_mass * (
        m2 * d12 / abs(d12) ** 3 + d13 / abs(d13) ** 3
    )
    z_derivative = pair_energy * w / 2.0 + radius * np.conj(w) * external / 2.0
    energy_derivative = 2.0 * np.real(np.conj(w * z) * external)
    return duration * np.array(
        [
            z.real,
            z.imag,
            z_derivative.real,
            z_derivative.imag,
            energy_derivative,
            (radius * complement_velocity).real,
            (radius * complement_velocity).imag,
            (radius * complement_acceleration).real,
            (radius * complement_acceleration).imag,
            radius,
        ]
    )


def integrate(parameters: np.ndarray, *, dense_output: bool) -> object:
    _, _, duration, m1, m2 = map(float, parameters)
    solution = solve_ivp(
        rhs,
        (0.0, 1.0),
        initial_state(parameters),
        args=(m1, m2, duration),
        method="DOP853",
        rtol=2e-13,
        atol=2e-15,
        max_step=2e-4,
        dense_output=dense_output,
    )
    if not solution.success:
        raise RuntimeError(solution.message)
    return solution


def residual(parameters: np.ndarray) -> np.ndarray:
    wr, wi, _, m1, m2 = map(float, parameters)
    solution = integrate(parameters, dense_output=False)
    endpoint = solution.y[:, -1]
    w = complex(endpoint[0], endpoint[1])
    z = complex(endpoint[2], endpoint[3])
    g = w * w
    g_velocity = 2.0 * w * z / abs(w) ** 2
    complement = complex(endpoint[5], endpoint[6])
    complement_velocity = complex(endpoint[7], endpoint[8])
    pair_mass = m2 + 1.0
    total_mass = m1 + m2 + 1.0
    mass12 = m1 + m2

    jacobi_x = -g / pair_mass - complement
    jacobi_x_velocity = -g_velocity / pair_mass - complement_velocity
    coefficient = m2 * total_mass / (pair_mass * mass12)
    fraction = m1 / mass12
    jacobi_y = coefficient * g - fraction * complement
    jacobi_y_velocity = coefficient * g_velocity - fraction * complement_velocity

    hopf_velocity = np.array(
        [
            np.real(np.conj(jacobi_x) * jacobi_x_velocity)
            - np.real(np.conj(jacobi_y) * jacobi_y_velocity),
            np.real(np.conj(jacobi_x_velocity) * jacobi_y)
            + np.real(np.conj(jacobi_x) * jacobi_y_velocity),
            np.imag(np.conj(jacobi_x_velocity) * jacobi_y)
            + np.imag(np.conj(jacobi_x) * jacobi_y_velocity),
        ]
    )
    gx = wr * wr - wi * wi
    gy = 2.0 * wr * wi
    side_residual = np.array(
        [wr * wr + wi * wi - m1, np.hypot(gx + 1.0, gy) - m2]
    )
    return np.concatenate([hopf_velocity, side_residual])


def centered_positions(samples: np.ndarray, m1: float, m2: float) -> np.ndarray:
    """Reconstruct q1,q2,q3 in the center-of-mass frame."""
    w = samples[:, 0] + 1j * samples[:, 1]
    g = w * w
    complement = samples[:, 5] + 1j * samples[:, 6]
    pair_mass = m2 + 1.0
    total_mass = m1 + pair_mass
    pair_center = -m1 * complement / total_mass
    q1 = pair_center + complement
    q2 = pair_center - g / pair_mass
    q3 = pair_center + m2 * g / pair_mass
    return np.stack(
        [
            np.column_stack([q1.real, q1.imag]),
            np.column_stack([q2.real, q2.imag]),
            np.column_stack([q3.real, q3.imag]),
        ],
        axis=1,
    )


def aligned_three_four_five(target: np.ndarray) -> tuple[np.ndarray, float, float]:
    """Least-squares align the labelled 3--4--5 triangle to ``target``.

    The fit permits translation, rotation, and one positive common scale, but
    not reflection.  Consequently the visible mismatch is purely a mismatch
    of triangle shape.
    """
    reference = np.array([[-0.5, 0.0], [0.5, 0.0], [0.14, 0.48]])
    reference_complex = reference[:, 0] + 1j * reference[:, 1]
    target_complex = target[:, 0] + 1j * target[:, 1]
    reference_centered = reference_complex - np.mean(reference_complex)
    target_centered = target_complex - np.mean(target_complex)
    multiplier = np.vdot(reference_centered, target_centered) / np.vdot(
        reference_centered,
        reference_centered,
    )
    aligned_complex = np.mean(target_complex) + multiplier * reference_centered
    aligned = np.column_stack([aligned_complex.real, aligned_complex.imag])
    rms_mismatch = float(np.sqrt(np.mean(np.sum((aligned - target) ** 2, axis=1))))
    return aligned, float(abs(multiplier)), rms_mismatch


def main() -> None:
    OUTPUT.parent.mkdir(parents=True, exist_ok=True)
    AUDIT.parent.mkdir(parents=True, exist_ok=True)
    seed = np.array(
        [
            0.34592828233749656,
            0.68930781951878970,
            21.091601754062015,
            0.59481164657071900,
            0.80177497331771010,
        ]
    )
    refined = root(residual, seed, method="hybr", tol=1e-10)
    parameters = refined.x
    final_residual = residual(parameters)
    solution = integrate(parameters, dense_output=True)
    wr, wi, duration, m1, m2 = parameters

    # Build a high-resolution sample uniform in *physical* time.  Uniform LC
    # time would overpopulate close passages and destroy the intended visual
    # velocity cue.  The physical clock is strictly increasing because
    # dt/dsigma=|w|^2>0 along this collision-free candidate.
    lookup_scaled_times = np.linspace(0.0, 1.0, 160001)
    lookup_samples = solution.sol(lookup_scaled_times).T
    half_period = float(lookup_samples[-1, 9])
    half_physical_times = np.linspace(0.0, half_period, 200001)
    half_scaled_times = np.interp(
        half_physical_times,
        lookup_samples[:, 9],
        lookup_scaled_times,
    )
    samples = solution.sol(half_scaled_times).T
    half_positions = centered_positions(samples, m1, m2)
    # The second half is the exact time reverse of the first.  Include it so
    # the point-density image represents one complete labelled period.
    positions = np.concatenate(
        [half_positions, half_positions[-2:0:-1]],
        axis=0,
    )

    w = samples[:, 0] + 1j * samples[:, 1]
    selected = w * w
    complement = samples[:, 5] + 1j * samples[:, 6]
    pair_mass = m2 + 1.0
    distances = np.column_stack(
        [
            np.abs(complement + selected / pair_mass),
            np.abs(selected),
            np.abs(complement - m2 * selected / pair_mass),
        ]
    )
    minimum_index = np.unravel_index(np.argmin(distances), distances.shape)
    minimum_separation = float(distances[minimum_index])
    defect = float(m1 * m1 + m2 * m2 - 1.0)

    colors = ("#d62728", "#2ca02c", "#1565c0")
    fig, ax = plt.subplots(figsize=(11.5, 9.2), dpi=220)
    for body, color in enumerate(colors):
        ax.scatter(
            positions[:, body, 0],
            positions[:, body, 1],
            color=color,
            s=2.4,
            alpha=0.007,
            edgecolors="none",
            linewidths=0,
            rasterized=True,
        )

    # Compare the actual launch triangle with the closest labelled, oriented
    # 3--4--5 triangle under a similarity transformation.  No legend or text
    # is added: the solid dark outline is the actual IC, while the dashed gold
    # outline with open vertices is the optimally aligned 3--4--5 reference.
    initial_triangle = half_positions[0]
    reference_triangle, reference_scale, reference_rms = aligned_three_four_five(
        initial_triangle
    )
    closed_actual = np.vstack([initial_triangle, initial_triangle[0]])
    closed_reference = np.vstack([reference_triangle, reference_triangle[0]])
    ax.plot(
        closed_actual[:, 0],
        closed_actual[:, 1],
        color="#202020",
        linewidth=1.65,
        alpha=0.92,
        zorder=20,
    )
    ax.plot(
        closed_reference[:, 0],
        closed_reference[:, 1],
        color="#f0a202",
        linewidth=2.0,
        linestyle=(0, (4.0, 3.0)),
        alpha=0.98,
        zorder=21,
    )
    ax.scatter(
        reference_triangle[:, 0],
        reference_triangle[:, 1],
        s=46,
        facecolors="white",
        edgecolors="#f0a202",
        linewidths=1.6,
        zorder=22,
    )

    ax.set_aspect("equal", adjustable="datalim")
    ax.set_axis_off()
    ax.margins(0.025)
    fig.subplots_adjust(left=0, right=1, bottom=0, top=1)
    fig.savefig(OUTPUT, bbox_inches="tight", pad_inches=0, facecolor="white")
    plt.close(fig)

    AUDIT.write_text(
        "\n".join(
            [
                "STATUS=ORDINARY_NUMERICAL_EVIDENCE",
                f"ROOT_SUCCESS={refined.success}",
                f"PARAMETERS={parameters.tolist()}",
                f"FIVE_RESIDUAL={final_residual.tolist()}",
                f"PHYSICAL_HALF_PERIOD={half_period:.17g}",
                f"MASS_PYTHAGOREAN_DEFECT={defect:.17g}",
                f"MINIMUM_SAMPLED_SEPARATION={minimum_separation:.17g}",
                f"MINIMUM_PAIR_INDEX={minimum_index[1]}",
                f"ALIGNED_345_SCALE={reference_scale:.17g}",
                f"ALIGNED_345_VERTEX_RMS={reference_rms:.17g}",
                f"ACTUAL_INITIAL_VERTICES={initial_triangle.tolist()}",
                f"ALIGNED_345_VERTICES={reference_triangle.tolist()}",
                "CAUTION=Candidate is mass-side-tied and periodic only to ordinary numerical precision; it is not Pythagorean.",
            ]
        )
        + "\n",
        encoding="utf-8",
    )
    print(OUTPUT)
    print(AUDIT)


if __name__ == "__main__":
    main()
