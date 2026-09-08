#!/usr/bin/env python3
"""Independent audit of a prompt-ejection window campaign.

Checks, from the stored tile logs alone (not from summary.json):
  * every PASS log names a tile [P/Q, P2/Q2] identical to its command line;
  * the union of PASS tiles is exactly the closed target interval, gap-free,
    with consecutive tiles sharing exact rational endpoints;
  * every PASS log reports positive margin, positive minimum separations,
    a launch window that ended, and the terminal line;
  * optionally replays a random sample of tiles with a different Taylor
    order and tolerance and requires PASS again.

Usage: audit_iso_window_campaign.py LOGDIR... --lo P/Q --hi P2/Q2 [--replay N --binary BIN]
"""
from __future__ import annotations

import argparse
import glob
import os
import random
import re
import subprocess
import sys
from fractions import Fraction


def parse_log(path: str):
    with open(path) as f:
        lines = f.read().splitlines()
    if not lines:
        return None
    cmd = lines[0].split()
    if len(cmd) < 5:
        return None
    p, q, p2, q2 = (int(x) for x in cmd[1:5])
    passed = None
    for line in lines[1:]:
        m = re.match(r"PASS_ISO_WINDOW_LC \[(\d+)/(\d+),(\d+)/(\d+)\] margin=([0-9.eE+-]+)", line)
        if m:
            pp, qq, pp2, qq2 = (int(x) for x in m.groups()[:4])
            if (pp, qq, pp2, qq2) != (p, q, p2, q2):
                raise RuntimeError(f"{path}: PASS tile does not match command line")
            passed = float(m.group(5))
    if passed is None:
        return {"a": Fraction(p, q), "b": Fraction(p2, q2), "pass": False, "path": path}
    text = "\n".join(lines)
    m1 = re.search(r"min_selected=([0-9.eE+-]+) min_unselected=([0-9.eE+-]+)", text)
    m2 = re.search(r"launch_window_end_tp=([0-9.eE+-]+)", text)
    ok = passed > 0 and m1 and float(m1.group(1)) > 0 and float(m1.group(2)) > 0 and m2 and float(m2.group(1)) > 0 and "TERMINAL" in text
    if not ok:
        raise RuntimeError(f"{path}: PASS log lacks required positive diagnostics")
    return {"a": Fraction(p, q), "b": Fraction(p2, q2), "pass": True, "margin": passed, "path": path, "cmd": cmd}


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("logdirs", nargs="+")
    ap.add_argument("--lo", required=True)
    ap.add_argument("--hi", required=True)
    ap.add_argument("--replay", type=int, default=0)
    ap.add_argument("--binary", default=None)
    args = ap.parse_args()
    lo, hi = Fraction(args.lo), Fraction(args.hi)
    recs = []
    for d in args.logdirs:
        for path in glob.glob(os.path.join(d, "tile_*.log")):
            r = parse_log(path)
            if r and r["pass"]:
                recs.append(r)
    # keep, for each left endpoint, the tile; verify chain coverage greedily
    recs.sort(key=lambda r: (r["a"], r["b"]))
    cover = []
    cur = lo
    by_left = {}
    for r in recs:
        by_left.setdefault(r["a"], []).append(r)
    while cur < hi:
        cands = [r for r in by_left.get(cur, []) if r["b"] <= hi]
        if not cands:
            print(f"GAP: no PASS tile starts at {cur} (= {float(cur):.9f})")
            sys.exit(1)
        r = max(cands, key=lambda r: r["b"])
        cover.append(r)
        cur = r["b"]
    print(f"COVERAGE OK: {len(cover)} PASS tiles cover [{lo}, {hi}] = [{float(lo):.7f}, {float(hi):.7f}] gap-free with shared rational endpoints")
    print(f"min margin {min(r['margin'] for r in cover):.4g}; narrowest tile {float(min(r['b']-r['a'] for r in cover)):.3g}; widest {float(max(r['b']-r['a'] for r in cover)):.3g}")
    if args.replay and args.binary:
        random.seed(20260907)
        sample = random.sample(cover, min(args.replay, len(cover)))
        bad = 0
        for r in sample:
            cmd = list(r["cmd"])
            cmd[0] = args.binary
            cmd[5], cmd[6] = "18", "1e-13"  # different order and tolerance
            out = subprocess.run(cmd, capture_output=True, text=True).stdout
            ok = any(l.startswith("PASS_ISO_WINDOW_LC") for l in out.splitlines())
            print(f"replay [{r['a']},{r['b']}] order 18 tol 1e-13: {'PASS' if ok else 'FAIL'}")
            bad += not ok
        if bad:
            sys.exit(1)
    print("AUDIT PASS")


if __name__ == "__main__":
    main()
