#!/bin/sh
set -eu

PINNED_CAPD_COMMIT=731079217a9254ea2948d742df2b170895effe7f

if [ "$#" -lt 1 ] || [ "$#" -gt 2 ]; then
  echo "usage: $0 CAPD_SOURCE_DIR [CAPD_BUILD_DIR]" >&2
  exit 2
fi

CAPD_SOURCE_DIR=$1
CAPD_BUILD_DIR=${2:-"$CAPD_SOURCE_DIR/build-native"}
ACTUAL_CAPD_COMMIT=$(git -C "$CAPD_SOURCE_DIR" rev-parse HEAD)

if [ "$ACTUAL_CAPD_COMMIT" != "$PINNED_CAPD_COMMIT" ]; then
  echo "CAPD commit mismatch: expected $PINNED_CAPD_COMMIT, got $ACTUAL_CAPD_COMMIT" >&2
  exit 2
fi

CAPD_CONFIG="$CAPD_BUILD_DIR/bin/capd-config"
if [ ! -x "$CAPD_CONFIG" ]; then
  echo "missing $CAPD_CONFIG; configure CAPD with -DCAPD_INTERVAL_TYPE=NATIVE" >&2
  exit 2
fi

REPOSITORY_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
OUTPUT_BINARY=${TMPDIR:-/tmp}/restricted_transversality_capd

# capd-config deliberately supplies -frounding-math and -D__USE_NATIVE__.
# shellcheck disable=SC2046
c++ "$REPOSITORY_DIR/src/verification/restricted_transversality_capd.cpp" \
  $("$CAPD_CONFIG" --cflags --libs) -o "$OUTPUT_BINARY"

"$OUTPUT_BINARY"
