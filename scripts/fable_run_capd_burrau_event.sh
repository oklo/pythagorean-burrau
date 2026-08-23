#!/bin/sh
set -eu

PINNED_CAPD_COMMIT=731079217a9254ea2948d742df2b170895effe7f

if [ "$#" -lt 1 ]; then
  echo "usage: $0 CAPD_SOURCE_DIR [CAPD_BUILD_DIR] [precision tol order]" >&2
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
OUTPUT_BINARY=${TMPDIR:-/tmp}/fable_burrau_event_certificate_capd

EXTRA_FLAGS=""
if [ "${FABLE_MP:-0}" = "1" ]; then
  # The multiprecision variant needs a CAPD build configured with
  # -DCAPD_ENABLE_MULTIPRECISION=ON and the MPFR/GMP headers/libraries.
  MPFR_PREFIX=${MPFR_PREFIX:-/opt/homebrew}
  EXTRA_FLAGS="-DFABLE_MP -Wno-deprecated-literal-operator \
    -I$MPFR_PREFIX/include -L$MPFR_PREFIX/lib -lmpfr -lgmp"
  OUTPUT_BINARY=${OUTPUT_BINARY}_mp
fi

# capd-config deliberately supplies -frounding-math and -D__USE_NATIVE__.
# shellcheck disable=SC2046
c++ -O2 "$REPOSITORY_DIR/src/fable/verification/burrau_event_certificate_capd.cpp" \
  $CAPD_FLAGS $EXTRA_FLAGS -o "$OUTPUT_BINARY"

shift $(( $# >= 2 ? 2 : 1 ))
if [ "${CAPD_VERBOSE:-0}" = "1" ]; then
  "$OUTPUT_BINARY" --verbose "$@"
else
  "$OUTPUT_BINARY" -- "$@"
fi
