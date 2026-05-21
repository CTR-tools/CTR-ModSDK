#!/bin/bash
# check_scores.sh — survey every per-function directory under
# src/matching/tools/ and report each one's current base score.
#
# Run from the repo root (or anywhere; the path resolution is relative
# to the script). Optionally pass a glob to filter:
#   bash scripts/check_scores.sh '*Veh*'
#
# Output lines: "<func_name>: <score>"  or  "<func_name>: <score> best=<best>"
#  - "0 ✓"               — byte-perfect match
#  - "<n>"               — current base score (lower = closer to match)
#  - "<n> best=<m>"      — base+best (best is the lowest-scoring permuter
#                          output found in any output-*/ subdir)
#  - "FAIL"              — compile or score extraction failed

set -u

# Locate the repo root by walking up looking for src/matching/tools/.
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
REPO_ROOT="$SCRIPT_DIR"
while [ "$REPO_ROOT" != "/" ] && [ ! -d "$REPO_ROOT/src/matching/tools" ]; do
    REPO_ROOT="$(dirname "$REPO_ROOT")"
done
if [ ! -d "$REPO_ROOT/src/matching/tools" ]; then
    # Maybe the user is running from inside src/matching/tools already.
    if [ -d "tools/permuter" ] || [ -d "permuter" ]; then
        REPO_ROOT="$(pwd)"
    else
        echo "ERROR: couldn't find src/matching/tools/ above this script" >&2
        exit 1
    fi
fi

TOOLS="$REPO_ROOT/src/matching/tools"
PERMUTER="$TOOLS/permuter/permuter.py"

# Pick a Python: prefer Windows Python if present (Git Bash), else system python3.
if [ -n "${PYEXE:-}" ]; then
    PY="$PYEXE"
elif command -v python3 >/dev/null 2>&1; then
    PY="$(command -v python3)"
elif [ -f "$LOCALAPPDATA/Programs/Python/Python312/python.exe" ]; then
    PY="$(cygpath -m "$LOCALAPPDATA/Programs/Python/Python312/python.exe" 2>/dev/null || echo "$LOCALAPPDATA/Programs/Python/Python312/python.exe")"
else
    PY="python"
fi

filter="${1:-*}"

check_one() {
    local dir="$1"
    local name
    name="$(basename "$dir")"
    if [ ! -f "$dir/base.c" ]; then
        echo "$name: NO_BASE.C"
        return
    fi
    if [ ! -f "$dir/target.o" ]; then
        echo "$name: NO_TARGET.O"
        return
    fi

    local out score
    out="$("$PY" "$PERMUTER" "$dir" --debug 2>&1)"
    score="$(echo "$out" | grep -oP "base score = \K[0-9]+" | head -1)"
    if [ -z "$score" ]; then
        # Try to extract a hint about why
        local err
        err="$(echo "$out" | grep -iE "error|fail|undeclared|undefined|unable" | head -1 | tr '\n' ' ')"
        echo "$name: FAIL ${err:0:80}"
        return
    fi

    if [ "$score" -eq 0 ]; then
        echo "$name: 0 ✓"
        return
    fi

    # Look for permuter output dirs to also surface the best score reached.
    local best_dir best
    best_dir="$(ls -d "$dir"/output-*/ 2>/dev/null | sort -t- -k2 -n | head -1)"
    if [ -n "$best_dir" ]; then
        best="$(basename "$best_dir" | cut -d- -f2)"
        echo "$name: $score best=$best"
    else
        echo "$name: $score"
    fi
}

found=0
for d in "$TOOLS"/$filter/; do
    [ -d "$d" ] || continue
    # Skip the submodules and template files.
    case "$(basename "$d")" in
        permuter|maspsx|windows-gcc-psx|gcc) continue ;;
        compile.sh.template|compile.ps1.template) continue ;;
    esac
    found=$((found + 1))
    check_one "$d"
done

if [ "$found" -eq 0 ]; then
    echo "(no function dirs matched filter: $filter)" >&2
    exit 1
fi
