#!/usr/bin/env bash
set -euo pipefail

PINNED_CAPD_COMMIT=731079217a9254ea2948d742df2b170895effe7f

if [ "$#" -lt 1 ] || [ "$#" -gt 5 ] || \
   { [ "$#" -eq 3 ] && [ "$3" != "--second-root" ] && \
     [ "$3" != "--second-escape" ] && \
     [ "$3" != "--second-escape-wide" ]; }; then
  echo "usage: $0 CAPD_SOURCE_DIR [CAPD_BUILD_DIR [--second-root | --second-escape | --second-escape-wide | FIRST_OFFSET COUNT [RADIUS]]]" >&2
  exit 2
fi

CAPD_SOURCE_DIR=$1
CAPD_BUILD_DIR=${2:-"$CAPD_SOURCE_DIR/build-native"}
ACTUAL_CAPD_COMMIT=$(git -C "$CAPD_SOURCE_DIR" rev-parse HEAD)

if [ "$ACTUAL_CAPD_COMMIT" != "$PINNED_CAPD_COMMIT" ]; then
  echo "CAPD commit mismatch: expected $PINNED_CAPD_COMMIT, got $ACTUAL_CAPD_COMMIT" >&2
  exit 2
fi
if ! git -C "$CAPD_SOURCE_DIR" diff --quiet || \
   ! git -C "$CAPD_SOURCE_DIR" diff --cached --quiet; then
  echo "CAPD tracked source tree has local modifications" >&2
  exit 2
fi
if [ -n "$(git -C "$CAPD_SOURCE_DIR" ls-files --others --exclude-standard)" ]; then
  echo "CAPD source tree has untracked non-ignored files" >&2
  exit 2
fi

CAPD_CONFIG="$CAPD_BUILD_DIR/bin/capd-config"
if [ ! -x "$CAPD_CONFIG" ]; then
  echo "missing $CAPD_CONFIG; configure CAPD with -DCAPD_INTERVAL_TYPE=NATIVE" >&2
  exit 2
fi

CAPD_FLAGS=$("$CAPD_CONFIG" --cflags --libs)
case " $CAPD_FLAGS " in
  *" -D__USE_NATIVE__ "*) ;;
  *) echo "CAPD build is not the required NATIVE interval build" >&2; exit 2 ;;
esac
case " $CAPD_FLAGS " in
  *" -frounding-math "*) ;;
  *) echo "CAPD build flags omit -frounding-math" >&2; exit 2 ;;
esac

REPOSITORY_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
OUTPUT_BINARY=${TMPDIR:-/tmp}/planar_light_collision_newton_capd
VERIFIER_ARGS=()
if [ "$#" -eq 3 ]; then
  VERIFIER_ARGS=("$3")
elif [ "$#" -eq 4 ]; then
  VERIFIER_ARGS=(--escape-tiles "$3" "$4")
elif [ "$#" -eq 5 ]; then
  VERIFIER_ARGS=(--escape-tiles "$3" "$4" "$5")
fi

# shellcheck disable=SC2086
c++ "$REPOSITORY_DIR/src/verification/planar_light_collision_newton_capd.cpp" \
  $CAPD_FLAGS -o "$OUTPUT_BINARY"
if [ "${#VERIFIER_ARGS[@]}" -eq 0 ]; then
  "$OUTPUT_BINARY"
else
  "$OUTPUT_BINARY" "${VERIFIER_ARGS[@]}"
fi
