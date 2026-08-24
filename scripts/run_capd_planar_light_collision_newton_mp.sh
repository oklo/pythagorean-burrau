#!/usr/bin/env bash
set -euo pipefail

PINNED_CAPD_COMMIT=731079217a9254ea2948d742df2b170895effe7f
PINNED_MPFR_VERSION=4.2.2
PINNED_GMP_VERSION=6.3.0

if [ "$#" -lt 2 ] || [ "$#" -gt 3 ]; then
  echo "usage: $0 CAPD_SOURCE_DIR CAPD_MP_BUILD_DIR [--fourth-root-octic]" >&2
  exit 2
fi

CAPD_SOURCE_DIR=$1
CAPD_BUILD_DIR=$2
VERIFIER_MODE=${3:---fourth-root-octic}
if [ "$VERIFIER_MODE" != "--fourth-root-octic" ]; then
  echo "the multiprecision wrapper currently audits --fourth-root-octic only" >&2
  exit 2
fi

ACTUAL_CAPD_COMMIT=$(git -C "$CAPD_SOURCE_DIR" rev-parse HEAD)
if [ "$ACTUAL_CAPD_COMMIT" != "$PINNED_CAPD_COMMIT" ]; then
  echo "CAPD commit mismatch: expected $PINNED_CAPD_COMMIT, got $ACTUAL_CAPD_COMMIT" >&2
  exit 2
fi
if ! git -C "$CAPD_SOURCE_DIR" diff --quiet || \
   ! git -C "$CAPD_SOURCE_DIR" diff --cached --quiet || \
   [ -n "$(git -C "$CAPD_SOURCE_DIR" ls-files --others --exclude-standard)" ]; then
  echo "CAPD source tree must be clean" >&2
  exit 2
fi

CAPD_CONFIG="$CAPD_BUILD_DIR/bin/capd-config"
if [ ! -x "$CAPD_CONFIG" ]; then
  echo "missing $CAPD_CONFIG" >&2
  exit 2
fi
CAPD_FLAGS=$($CAPD_CONFIG --cflags --libs)
case " $CAPD_FLAGS " in
  *" -D__HAVE_MPFR__ "*) ;;
  *) echo "CAPD build does not advertise multiprecision support" >&2; exit 2 ;;
esac

MP_INCLUDE_DIR=${BURRAU_MP_INCLUDE_DIR:-/opt/homebrew/include}
MP_LIBRARY_DIR=${BURRAU_MP_LIBRARY_DIR:-/opt/homebrew/lib}
if [ ! -f "$MP_INCLUDE_DIR/mpfr.h" ] || [ ! -f "$MP_INCLUDE_DIR/gmp.h" ]; then
  echo "set BURRAU_MP_INCLUDE_DIR to the directory containing MPFR and GMP headers" >&2
  exit 2
fi
ACTUAL_MPFR_VERSION=$(pkg-config --modversion mpfr)
ACTUAL_GMP_VERSION=$(pkg-config --modversion gmp)
if [ "$ACTUAL_MPFR_VERSION" != "$PINNED_MPFR_VERSION" ] || \
   [ "$ACTUAL_GMP_VERSION" != "$PINNED_GMP_VERSION" ]; then
  echo "multiprecision dependency mismatch: expected MPFR $PINNED_MPFR_VERSION and GMP $PINNED_GMP_VERSION, got MPFR $ACTUAL_MPFR_VERSION and GMP $ACTUAL_GMP_VERSION" >&2
  exit 2
fi

REPOSITORY_DIR=$(CDPATH= cd -- "$(dirname -- "$0")/.." && pwd)
OUTPUT_BINARY=${TMPDIR:-/tmp}/planar_light_collision_newton_capd_mp

# shellcheck disable=SC2086
c++ "$REPOSITORY_DIR/src/verification/planar_light_collision_newton_capd.cpp" \
  $CAPD_FLAGS -DBURRAU_CAPD_MULTIPRECISION \
  -I"$MP_INCLUDE_DIR" -L"$MP_LIBRARY_DIR" -lmpfr -lgmpxx -lgmp \
  -o "$OUTPUT_BINARY"
"$OUTPUT_BINARY" "$VERIFIER_MODE"
