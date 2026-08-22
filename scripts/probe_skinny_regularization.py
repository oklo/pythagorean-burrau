#!/usr/bin/env python3
"""Numerically check convergence to the exact skinny LC coefficients."""

from __future__ import annotations

import argparse
from math import pi, sqrt

from scipy.integrate import solve_ivp

from src.dynamics.skinny_regularized import (
    initial_regularized_state,
    regularized_right_hand_side,
    scaled_inner_angular_momentum,
)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--epsilon", type=float, default=0.1)
    parser.add_argument("--rtol", type=float, default=2.3e-14)
    parser.add_argument("--atol", type=float, default=2e-16)
    parser.add_argument("--max-step", type=float, default=0.002)
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    state0 = initial_regularized_state(args.epsilon)

    def real_crossing(_time: float, state, _epsilon: float) -> float:
        return float(state[0])

    real_crossing.direction = -1
    real_crossing.terminal = True
    solution = solve_ivp(
        regularized_right_hand_side,
        (0, 1.1 * pi / sqrt(2)),
        state0,
        args=(args.epsilon,),
        events=real_crossing,
        method="DOP853",
        rtol=args.rtol,
        atol=args.atol,
        max_step=args.max_step,
    )
    if not solution.success or solution.t_events[0].size != 1:
        raise SystemExit(solution.message)
    crossing = solution.y_events[0][0]
    imaginary_coefficient = crossing[1] / args.epsilon**5
    physical_distance = args.epsilon * (crossing[0] ** 2 + crossing[1] ** 2)
    miss_coefficient = physical_distance / args.epsilon**11
    a = sqrt(1 - args.epsilon**2)
    physical_angular_momentum = (
        sqrt(1 + a)
        * sqrt(args.epsilon)
        * scaled_inner_angular_momentum(crossing)
    )
    angular_coefficient = physical_angular_momentum / args.epsilon**5.5
    print(f"epsilon={args.epsilon:.12g}")
    print(f"s_cross={solution.t_events[0][0]:.16g}")
    print(f"Im(z_cross)/epsilon^5={imaginary_coefficient:.16g}")
    print(f"r_at_real_cross/epsilon^11={miss_coefficient:.16g}")
    print(f"h_at_real_cross/epsilon^(11/2)={angular_coefficient:.16g}")
    print(f"exact_Im_limit={-15 * pi / 128:.16g}")
    print(f"exact_r_limit={225 * pi * pi / 16384:.16g}")
    print(f"exact_h_limit={-15 * pi / 64:.16g}")


if __name__ == "__main__":
    main()

