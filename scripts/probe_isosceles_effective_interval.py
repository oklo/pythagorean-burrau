"""Scout how far the certified endpoint mechanism persists.

This is ordinary numerical evidence used only to choose parameter boxes for
subsequent validated continuation.  It does not prove an effective interval.
"""

from __future__ import annotations

import numpy as np
from scipy.integrate import solve_ivp

from scripts.probe_isosceles_base_collision import field, tied_data
from src.dynamics.escape_certificate import evaluate_escape_certificate


def probe_member(v: float, final_sigma: float = 7.0) -> None:
    _, _, initial = tied_data(v)
    solution = solve_ivp(
        field,
        (0.0, final_sigma),
        initial,
        method="DOP853",
        rtol=2e-12,
        atol=2e-14,
        max_step=2e-3,
    )
    if not solution.success:
        print(
            "status=ORDINARY_NUMERICAL_EVIDENCE "
            f"v={v:.12g} success=False sigma={solution.t[-1]:.12g} "
            f"message={solution.message!r}"
        )
        return

    states = solution.y
    wr, wi = states[0], states[1]
    gx = wr**2 - wi**2
    gy = 2 * wr * wi
    pair_mass = states[10] + states[11]
    d31x = states[5] + states[11] * gx / pair_mass
    d31y = states[6] + states[11] * gy / pair_mass
    d23x = states[5] - states[10] * gx / pair_mass
    d23y = states[6] - states[10] * gy / pair_mass
    selected_distance = wr**2 + wi**2
    r31_squared = d31x**2 + d31y**2
    r23_squared = d23x**2 + d23y**2
    brake_residual_squared = (
        states[2] ** 2
        + states[3] ** 2
        + states[7] ** 2
        + states[8] ** 2
    )
    post_interface = solution.t >= 0.5
    crossing_count = int(np.count_nonzero(wr[:-1] * wr[1:] < 0))

    final = states[:, -1]
    radius = final[0] ** 2 + final[1] ** 2
    inner = np.array(
        [final[0] ** 2 - final[1] ** 2, 2 * final[0] * final[1]]
    )
    inner_velocity = np.array(
        [
            2 * (final[0] * final[2] - final[1] * final[3]) / radius,
            2 * (final[0] * final[3] + final[1] * final[2]) / radius,
        ]
    )
    certificate = evaluate_escape_certificate(
        final[10],
        final[11],
        1.0,
        inner,
        inner_velocity,
        final[5:7],
        final[7:9],
        4.0,
    )
    print(
        "status=ORDINARY_NUMERICAL_EVIDENCE "
        f"v={v:.12g} u={(np.sqrt(2)-1)*v:.12g} success=True "
        f"crossings={crossing_count} "
        f"min_r12={np.min(selected_distance):.8g} "
        f"min_other_squared={min(np.min(r31_squared),np.min(r23_squared)):.8g} "
        f"min_brake_residual_squared="
        f"{np.min(brake_residual_squared[post_interface]):.8g} "
        f"escape_eta4={certificate.certified} "
        f"separation_margin={certificate.separation_margin:.8g} "
        f"radial_margin={certificate.radial_energy_margin:.8g} "
        f"inner_margin={certificate.inner_energy_margin:.8g}",
        flush=True,
    )


def main() -> None:
    for v in (0.999999, 0.99999, 0.9999, 0.999, 0.99):
        probe_member(v)


if __name__ == "__main__":
    main()
