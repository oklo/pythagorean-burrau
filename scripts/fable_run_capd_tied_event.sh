#!/bin/sh
set -eu

PINNED_CAPD_COMMIT=731079217a9254ea2948d742df2b170895effe7f

if [ "$#" -lt 2 ]; then
  echo "usage: $0 CAPD_SOURCE_DIR CAPD_MP_BUILD_DIR [verifier args...]" >&2
  exit 2
fi

CAPD_SOURCE_DIR=$1
CAPD_BUILD_DIR=$2
shift 2

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
  echo "missing $CAPD_CONFIG; configure CAPD with -DCAPD_INTERVAL_TYPE=NATIVE -DCAPD_ENABLE_MULTIPRECISION=ON" >&2
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

MPFR_PREFIX=${MPFR_PREFIX:-/opt/homebrew}
REPOSITORY_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)

if [ "${FABLE_NATIVE:-0}" = "1" ]; then
  OUTPUT_BINARY=${TMPDIR:-/tmp}/fable_tied_event_certificate_capd_native
  # shellcheck disable=SC2046
  c++ -O2 \
    "$REPOSITORY_DIR/src/fable/verification/tied_event_certificate_capd.cpp" \
    $CAPD_FLAGS -o "$OUTPUT_BINARY"
else
  OUTPUT_BINARY=${TMPDIR:-/tmp}/fable_tied_event_certificate_capd
  # shellcheck disable=SC2046
  c++ -O2 -DFABLE_MP -Wno-deprecated-literal-operator \
    -I"$MPFR_PREFIX/include" \
    "$REPOSITORY_DIR/src/fable/verification/tied_event_certificate_capd.cpp" \
    $CAPD_FLAGS -L"$MPFR_PREFIX/lib" -lmpfr -lgmp -o "$OUTPUT_BINARY"
fi

"$OUTPUT_BINARY" "$@"
