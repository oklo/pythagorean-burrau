#!/usr/bin/env python3
"""Ordinary event atlas: I-apocenter events and terminal certificate times."""

from __future__ import annotations

import argparse

from src.fable.atlas import run_atlas


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--u", type=float, nargs="+", default=[1 / 3])
    parser.add_argument("--max-time", type=float, default=40.0)
    parser.add_argument("--max-step", type=float, default=0.01)
    parser.add_argument("--rtol", type=float, default=1e-12)
    parser.add_argument("--atol", type=float, default=1e-14)
    parser.add_argument("--events", action="store_true", help="print every event")
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    for u in args.u:
        result = run_atlas(
            u,
            max_time=args.max_time,
            rtol=args.rtol,
            atol=args.atol,
            max_step=args.max_step,
        )
        maxima = [event for event in result.events if event.is_maximum]
        print(f"u={u:.12g}")
        print(
            f"  events={len(result.events)} maxima={len(maxima)}"
            f" end_time={result.end_time:.6g}"
        )
        if maxima:
            worst = min(maxima, key=lambda event: event.residual_norm)
            print(
                f"  worst_max: t={worst.time:.9g} |B|={worst.residual_norm:.6g}"
                f" K={worst.kinetic:.6g} U/U0={worst.potential_ratio:.6g}"
                f" minsep={worst.min_separation:.6g}"
            )
            smallest_kinetic = min(maxima, key=lambda event: event.kinetic)
            print(
                f"  min_K_max: t={smallest_kinetic.time:.9g} K={smallest_kinetic.kinetic:.6g}"
                f" |B|={smallest_kinetic.residual_norm:.6g}"
            )
        if result.certificate is not None:
            hit = result.certificate
            print(
                f"  certificate: t={hit.time:.6g} binary={hit.binary}"
                f" escaper={hit.escaper} eta={hit.eta}"
                f" margin={hit.inner_energy_margin:.6g}"
            )
        else:
            print("  certificate: none before end_time")
        print(
            f"  min_separation={result.min_separation:.6g}"
            f" max_rel_energy_err={result.max_relative_energy_error:.3e}"
        )
        if args.events:
            for event in result.events:
                kind = "max" if event.is_maximum else "min"
                print(
                    f"    t={event.time:.9g} {kind} I={event.i_value:.6g}"
                    f" K={event.kinetic:.6g} |B|={event.residual_norm:.6g}"
                    f" zeta=({event.zeta_real:.6g},{event.zeta_imag:.6g})"
                    f" |zeta|={event.zeta_abs:.6g}"
                    f" ell=({event.ell_12:.6g},{event.ell_23:.6g})"
                    f" U/U0={event.potential_ratio:.6g}"
                    f" minsep={event.min_separation:.6g}"
                )


if __name__ == "__main__":
    main()
