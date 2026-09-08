#!/usr/bin/env python3
"""Tile campaign driver for the prompt-ejection window certificate
(src/fable/verification/iso_window_lc_capd.cpp).

Covers the closed interval [LO/DEN, HI/DEN] by consecutive closed tiles
[k/DEN, (k+1)/DEN] and runs the certificate on each.  A failing tile is
retried with alternative chart-switch times and then bisected (rational
endpoints are preserved by doubling the denominator).  Every tile log is
stored; the summary records gap-free coverage or the uncovered residue.

Usage: run_iso_window_campaign.py BINARY LO HI DEN OUTDIR [--jobs N] [--depth D]
"""
from __future__ import annotations

import argparse
import json
import os
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor, as_completed
from fractions import Fraction


def switch_times(u: float) -> list[tuple[float, float]]:
    base = (0.505, 0.575) if u >= 0.406 else (0.5025, 0.575)
    alts = [(0.50, 0.58), (0.505, 0.57), (0.5025, 0.585), (0.51, 0.575), (0.4975, 0.575)]
    return [base] + [a for a in alts if a != base]


ORDER = "12"
TOL = "1e-11"


def run_tile(binary: str, p: int, q: int, p2: int, q2: int, sw: tuple[float, float], outdir: str) -> tuple[bool, str, str]:
    args = [binary, str(p), str(q), str(p2), str(q2), ORDER, TOL, "6", f"{sw[0]}", f"{sw[1]}", "0.05"]
    name = f"tile_{p}_{q}_{p2}_{q2}_sw{sw[0]}_{sw[1]}.log"
    path = os.path.join(outdir, name)
    if os.path.exists(path):
        # resume: reuse a stored PASS log for the identical tile and switch times
        with open(path) as f:
            log = f.read()
        if any(line.startswith("PASS_ISO_WINDOW_LC") for line in log.splitlines()):
            return True, path, log
    res = subprocess.run(args, capture_output=True, text=True)
    log = res.stdout + res.stderr
    with open(path, "w") as f:
        f.write(" ".join(args) + "\n" + log)
    ok = any(line.startswith("PASS_ISO_WINDOW_LC") for line in log.splitlines()) and res.returncode == 0
    return ok, path, log


def certify(binary: str, a: Fraction, b: Fraction, outdir: str, depth: int) -> list[dict]:
    """Return a list of records covering [a,b] exactly (or marking failure)."""
    u_mid = float((a + b) / 2)
    for sw in switch_times(u_mid):
        ok, path, log = run_tile(binary, a.numerator, a.denominator, b.numerator, b.denominator, sw, outdir)
        if ok:
            margin = [l for l in log.splitlines() if l.startswith("PASS_ISO_WINDOW_LC")][0].split("margin=")[1]
            return [{"a": f"{a.numerator}/{a.denominator}", "b": f"{b.numerator}/{b.denominator}", "pass": True, "sw": sw, "margin": float(margin), "log": path}]
    if depth <= 0:
        return [{"a": f"{a.numerator}/{a.denominator}", "b": f"{b.numerator}/{b.denominator}", "pass": False, "log": path}]
    m = (a + b) / 2
    return certify(binary, a, m, outdir, depth - 1) + certify(binary, m, b, outdir, depth - 1)


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("binary")
    ap.add_argument("lo", type=int)
    ap.add_argument("hi", type=int)
    ap.add_argument("den", type=int)
    ap.add_argument("outdir")
    ap.add_argument("--jobs", type=int, default=12)
    ap.add_argument("--depth", type=int, default=3)
    ap.add_argument("--order", default="12")
    ap.add_argument("--tol", default="1e-11")
    args = ap.parse_args()
    global ORDER, TOL
    ORDER, TOL = args.order, args.tol
    os.makedirs(args.outdir, exist_ok=True)
    tiles = [(Fraction(k, args.den), Fraction(k + 1, args.den)) for k in range(args.lo, args.hi)]
    records: list[dict] = []
    with ThreadPoolExecutor(max_workers=args.jobs) as ex:
        futs = {ex.submit(certify, args.binary, a, b, args.outdir, args.depth): (a, b) for a, b in tiles}
        done = 0
        for fut in as_completed(futs):
            recs = fut.result()
            records.extend(recs)
            done += 1
            if done % 200 == 0:
                fails = sum(1 for r in records if not r["pass"])
                print(f"progress {done}/{len(tiles)} tiles, records={len(records)}, failures={fails}", flush=True)
    records.sort(key=lambda r: Fraction(r["a"]))
    # gap-free check
    gaps = []
    prev = Fraction(args.lo, args.den)
    for r in records:
        if Fraction(r["a"]) != prev:
            gaps.append((str(prev), r["a"]))
        prev = Fraction(r["b"])
    if prev != Fraction(args.hi, args.den):
        gaps.append((str(prev), f"{args.hi}/{args.den}"))
    fails = [r for r in records if not r["pass"]]
    summary = {
        "interval": [f"{args.lo}/{args.den}", f"{args.hi}/{args.den}"],
        "tiles": len(tiles), "records": len(records), "failures": len(fails), "gaps": gaps,
        "min_margin": min((r["margin"] for r in records if r["pass"]), default=None),
        "all_pass_gap_free": (not fails) and (not gaps),
    }
    with open(os.path.join(args.outdir, "summary.json"), "w") as f:
        json.dump({"summary": summary, "records": records}, f, indent=1)
    print(json.dumps(summary, indent=1))
    if fails:
        print("FAILED tiles:", [(r["a"], r["b"]) for r in fails][:50])
        sys.exit(1)


if __name__ == "__main__":
    main()
