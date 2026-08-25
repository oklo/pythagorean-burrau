#!/bin/sh
set -eu

if [ "$#" -ne 2 ]; then
  echo "usage: $0 CAPD_SOURCE_DIR CAPD_MP_BUILD_DIR" >&2
  exit 2
fi

REPOSITORY_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
LEFT_OUTPUT=$(
  "$REPOSITORY_DIR/scripts/fable_run_capd_burrau_lc.sh" \
    "$1" "$2" \
    ilcmax 29 100 29001 100000 0.1 80 1e-14 24
)
printf '%s\n' "$LEFT_OUTPUT"

case "$LEFT_OUTPUT" in
  *"PASS_TIED_FIRST_MAXIMUM_INTERVAL u=[29/100,29001/100000]"*) ;;
  *)
    echo "FAIL missing left tied first-maximum interval marker" >&2
    exit 1
    ;;
esac

RIGHT_OUTPUT=$(
  "$REPOSITORY_DIR/scripts/fable_run_capd_burrau_lc.sh" \
    "$1" "$2" \
    ilcmax 29001 100000 14501 50000 0.1 80 1e-14 24
)
printf '%s\n' "$RIGHT_OUTPUT"

case "$RIGHT_OUTPUT" in
  *"PASS_TIED_FIRST_MAXIMUM_INTERVAL u=[29001/100000,14501/50000]"*) ;;
  *)
    echo "FAIL missing right tied first-maximum interval marker" >&2
    exit 1
    ;;
esac
