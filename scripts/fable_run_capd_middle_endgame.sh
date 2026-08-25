#!/bin/sh
# Build and run the middle-interval endgame certificate
# (src/fable/verification/middle_escape_endgame_capd.cpp).
#
# usage: fable_run_capd_middle_endgame.sh CAPD_SOURCE_DIR CAPD_MP_BUILD_DIR \
#          P Q P2 Q2 [PREC TOL ORDER]
# e.g.   ... 29 100 29001 100000 160 1e-24 32
set -eu

PINNED_CAPD_COMMIT=731079217a9254ea2948d742df2b170895effe7f

if [ "$#" -lt 6 ]; then
  echo "usage: $0 CAPD_SOURCE_DIR CAPD_MP_BUILD_DIR P Q P2 Q2 [PREC TOL ORDER]" >&2
  exit 2
fi

CAPD_SOURCE_DIR=$1
CAPD_BUILD_DIR=$2
shift 2

ACTUAL_CAPD_COMMIT=$(git -C "$CAPD_SOURCE_DIR" rev-parse HEAD)
if [ "$ACTUAL_CAPD_COMMIT" != "$PINNED_CAPD_COMMIT" ]; then
  echo "CAPD commit mismatch" >&2
  exit 2
fi
if ! git -C "$CAPD_SOURCE_DIR" diff --quiet || \
   ! git -C "$CAPD_SOURCE_DIR" diff --cached --quiet; then
  echo "CAPD tree has local modifications" >&2
  exit 2
fi

CAPD_CONFIG="$CAPD_BUILD_DIR/bin/capd-config"
CAPD_FLAGS=$("$CAPD_CONFIG" --cflags --libs)
case " $CAPD_FLAGS " in
  *" -D__USE_NATIVE__ "*) ;;
  *) echo "CAPD build is not NATIVE" >&2; exit 2 ;;
esac
case " $CAPD_FLAGS " in
  *" -frounding-math "*) ;;
  *) echo "missing -frounding-math" >&2; exit 2 ;;
esac
case " $CAPD_FLAGS " in
  *" -D__HAVE_MPFR__ "*) ;;
  *) echo "CAPD build lacks multiprecision (-D__HAVE_MPFR__)" >&2; exit 2 ;;
esac

MPFR_PREFIX=${MPFR_PREFIX:-/opt/homebrew}
REPOSITORY_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
OUTPUT_BINARY=${TMPDIR:-/tmp}/fable_middle_escape_endgame_capd

# shellcheck disable=SC2086
c++ -O2 -DFABLE_MP -Wno-deprecated-literal-operator \
  -I"$MPFR_PREFIX/include" \
  "$REPOSITORY_DIR/src/fable/verification/middle_escape_endgame_capd.cpp" \
  $CAPD_FLAGS -L"$MPFR_PREFIX/lib" -lmpfr -lgmp -o "$OUTPUT_BINARY"

"$OUTPUT_BINARY" "$@"
