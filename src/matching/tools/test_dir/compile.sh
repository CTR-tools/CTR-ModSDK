#!/bin/bash
# Windows-native compile.sh: gcc.exe + Windows Python maspsx + Windows
# mipsel-none-elf-as.exe. No WSL needed.
#
# This script is invoked by the permuter; arguments are:
#   $1 = path to .c file
#   $2 = -o (literal)
#   $3 = path to output .o file
set -e

# The pcsx-redux mips toolchain (in PATH) ships its own cygwin-style
# `cp`/`sed`/`mktemp` that interpret /c/... paths differently than Git
# Bash. Force Git Bash's utilities to be found first.
export PATH="/usr/bin:$PATH"

# Resolve relative paths via Git Bash. -W gives us Windows-style paths
# that survive the mixed-toolchain `cp` (whose path translation isn't
# always compatible with Git Bash's MSYS conventions).
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd -W)"
TOOLS_DIR="$(cd "$SCRIPT_DIR/.." && pwd -W)"
GCC_DIR="${TOOLS_DIR}/windows-gcc-psx/gcc-2.8.1-psx"
MASPSX="${TOOLS_DIR}/maspsx/maspsx.py"
MIPSAS_WIN="$(cygpath -m "$APPDATA/mips/mips/bin/mipsel-none-elf-as.exe")"
PYEXE="${PYEXE:-$(cygpath -m "$LOCALAPPDATA/Programs/Python/Python312/python.exe")}"

# Stage everything in a Windows-side temp dir so all of gcc.exe, Python,
# and mipsel-as.exe see the same paths.
WIN_TEMP="$(cygpath -u "$LOCALAPPDATA")/Temp"
TMPDIR=$(mktemp -d -p "$WIN_TEMP" matching-test.XXXXXX)
trap "rm -rf '$TMPDIR'" EXIT
TMP_WIN="$(cygpath -m "$TMPDIR")"

SRCDIR="$(cygpath -u "$(dirname "$(cygpath -w "$1")")")"
cp "$1" "$TMPDIR/input.c"
for h in "$SRCDIR"/*.h; do
    [ -f "$h" ] && cp "$h" "$TMPDIR/"
done

"$GCC_DIR/gcc.exe" "-B${GCC_DIR}/" -I "${TMP_WIN}" -DUSE_REAL_GTE=1 \
    -S -Wa,--aspsx-version=2.77 -mel -g -O2 \
    "${TMP_WIN}/input.c" -o "${TMP_WIN}/output.s"

[ -f "$TMPDIR/output.s" ] || exit 1
sed -i 's/\r$//' "$TMPDIR/output.s"

"$PYEXE" "$MASPSX" --aspsx-version=2.77 --expand-div --run-assembler \
    --gnu-as-path "$MIPSAS_WIN" -o "$3" < "$TMPDIR/output.s"
