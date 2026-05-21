# Matching project

The goal of this project is to find C source that compiles, byte-for-byte, to
the original NTSC-U (9/26/99 build, id `926`) game executable. See
[../README.md](../README.md) for how `matching` fits next to `decompile` and
`rewrite`.

This README covers **how to set up and run the matching scorer** locally — i.e.
how to take a `.c` file under `General/*/` and compare its compiled output
against the original `.o`.

---

## Layout

```
src/matching/
├── README.md                ← you are here
├── General/
│   ├── COLL/
│   │   ├── COLL.h           ← shared typedefs + struct shapes
│   │   ├── COLL_*.c         ← one function per file
│   │   └── ...
│   ├── INSTANCE/
│   ├── UI/
│   └── Vehicle/
└── tools/
    ├── permuter/                  ← submodule: simonlindholm/decomp-permuter
    ├── maspsx/                    ← submodule: mkst/maspsx
    ├── windows-gcc-psx/           ← submodule: DataPlusProgram/windows-gcc-psx
    ├── compile.sh.template        ← Git Bash compile script template
    ├── compile.ps1.template       ← PowerShell compile script template
    ├── gcc/                       ← user-placed Linux gcc tree (gitignored)
    └── SCUS-94426.s               ← user-placed (gitignored)
```

`tools/permuter`, `tools/maspsx` and `tools/windows-gcc-psx` come down via git
submodules. `tools/gcc/` (Linux) and `tools/SCUS-94426.s` are external
artifacts the contributor places by hand — see the setup steps below.

---

## Prerequisites

- **WSL2** (Ubuntu) on Windows, or Linux/macOS natively. The PSY-Q gcc is a
  Linux binary; it cannot run from Windows directly. All `tools/` operations
  must happen inside WSL.
- **Python 3.8+** with `pip`
- **Binutils for MIPS little-endian**: any modern version is fine (no version
  pin). On Debian/Ubuntu:
  ```
  sudo apt install binutils-mipsel-linux-gnu
  ```
  Provides `mipsel-linux-gnu-as`, used by `maspsx` and the target extractor.

---

## One-time setup

### 1. Clone with submodules

```bash
git clone --recurse-submodules <repo-url>
# or, if you already cloned:
git submodule update --init src/matching/tools/permuter src/matching/tools/maspsx
```

### 2. Install permuter Python deps

```bash
cd src/matching/tools/permuter
pip install -r requirements.txt    # pycparser, attrs, toml, ...
```

### 3. Place the PSY-Q gcc 2.8.1 toolchain

The matching score is meaningful only when the C is compiled by the *same*
compiler Naughty Dog used — modern gcc emits different register choices and
instruction orderings. Place a working PSY-Q gcc 2.8.1 tree at:

```
src/matching/tools/gcc/
├── gcc        ← driver
├── cc1        ← C frontend
├── cpp        ← preprocessor
└── ...
```

The exact file set depends on which distribution you use; all four matching
test sweeps pass with each of these.

**Option A — Windows native binaries (verified):** the [DataPlusProgram/windows-gcc-psx](https://github.com/DataPlusProgram/windows-gcc-psx)
project ships `gcc.exe`, `cc1.exe`, `cpp.exe`, `cccp.exe` for several PSX gcc
versions. Drop the contents of its `gcc-2.8.1-psx/` directory directly into
`src/matching/tools/gcc/`. All twelve scorable functions in this repo match
identically against the original `target.o` using this build. Works on Windows
natively and on WSL via binfmt interop.

**Option B — Linux build:** the gcc-2.8.1 binary distributed with
[psx-modding-toolchain](https://github.com/mateusfavarin/psx-modding-toolchain),
or extracted from the `decompals/old-gcc` Docker image. Copy/symlink that
tree into `src/matching/tools/gcc/`.

This directory is `.gitignore`d.

### 4. Place the NTSC-U disassembly

The scorer extracts the original game's `target.o` for any function on demand,
by reading the full disassembly. Place the file at:

```
src/matching/tools/SCUS-94426.s
```

Common sources:
- The output of `splat` against the NTSC-U executable (build id 926)
- The copy bundled in your `psx-modding-toolchain` setup

This file is `.gitignore`d (it's ~8 MB and tracked separately by its upstream).

---

## Scoring a function

Two compile script templates are provided under `tools/`:

- [`tools/compile.sh.template`](tools/compile.sh.template) — Git Bash, works
  on Windows (no WSL needed) and on Linux.
- [`tools/compile.ps1.template`](tools/compile.ps1.template) — PowerShell,
  pure Windows.

Both drive the same pipeline (windows-gcc-psx → maspsx → mipsel-none-elf-as)
and both honour an optional `GP_VALUE` env var that, when set, runs
`patch_gprel.py` on the produced `.o` (required for the handful of functions
that touch GP-relative globals — currently `VehPhysCrash_AI` and
`VehPhysCrash_Attack`, both `gp=0x8008CF6C`).

### Setup a per-function test directory

1. Make a dir under `tools/`, e.g. `tools/VehPhysProc_SpinStop_Update/`.
2. Drop in `base.c` (the matching source), the relevant `<Subdir>.h` next to
   it, and `target.o` (produced separately from `SCUS-94426.s` — see [Manual
   flow](#manual-flow-works-today) below).
3. Write a one-line `settings.toml`:
   ```toml
   func_name = "VehPhysProc_SpinStop_Update"
   compiler_type = "gcc"
   ```
4. Copy one of the templates in as `compile.sh` or `compile.ps1`.

Then run the scorer (Windows examples):

```
# from Git Bash (compile.sh)
python src/matching/tools/permuter/permuter.py tools/<dir-name> --debug

# from PowerShell (compile.ps1)
python src\matching\tools\permuter\permuter.py tools\<dir-name> --debug
```

A `base score = 0` line means a byte-perfect match. The scripts themselves are
self-contained — running one of them manually (`./compile.sh base.c -o
candidate.o`) gives you a `.o` you can objdump-compare without going through
the permuter at all.

### Manual flow (works today)

From WSL, in this directory:

```bash
# extract target.o for one address from SCUS-94426.s
bash tools/permuter/path-to/extract_func.sh <ADDRESS> /tmp/work/<NAME>

# drop the cleaned source + per-subdir header alongside it
cp General/<SUBDIR>/<NAME>.c /tmp/work/<NAME>/base.c
cp General/<SUBDIR>/<SUBDIR>.h /tmp/work/<NAME>/

# write a compile.sh that gives gcc -I for the header dir,
# defines USE_REAL_GTE=1, and pipes through maspsx; then:
python3 tools/permuter/permuter.py /tmp/work/<NAME> --debug
```

The last line prints `base score = N`. **0 = byte-perfect match.** Higher
scores indicate progressive divergence (register diffs, instruction inserts/
deletes, etc.).

### Things to watch for

- **`USE_REAL_GTE=1`** must reach the preprocessor (not just gcc) — the
  permuter pre-processes `base.c` through `cpp` before invoking `compile.sh`,
  so flags passed to gcc come too late for `#if` conditionals. `Vehicle.h`
  works around this by `#define`ing `USE_REAL_GTE 1` itself when undefined.
- **`patch_gprel.py`** — a couple of functions (currently
  `VehPhysCrash_AI` / `VehPhysCrash_Attack`, both at `gp=0x8008CF6C`) need a
  post-assembly GP-relative relocation fix. Without it the score is non-zero
  due to `lo(D_XXX)(gp)` mismatches.

### Windows-specific gotchas when using Option A (Windows gcc)

If you're driving `gcc.exe` from a WSL bash compile script:

- **No UNC paths.** `gcc.exe` can't open files at `\\wsl.localhost\...`.
  Stage `input.c` (and any neighbour `.h`) into a directory under
  `C:\Users\<you>\AppData\Local\Temp\` (i.e. `/mnt/c/Users/<you>/AppData/Local/Temp/`
  from WSL) before invoking gcc, and pass `-I <that-temp-dir>` so includes
  resolve there too.
- **`cd` to a Windows filesystem cwd before launching `gcc.exe`.** Otherwise
  WSL binfmt interop occasionally fails with `Invalid argument` when the
  parent's cwd is in the WSL filesystem and the subprocess inherits it. A
  `cd "$TMPDIR"` where `$TMPDIR` is on `C:` is enough.
- **Strip CR from `.s` output.** Windows gcc writes CRLF line endings; pipe
  through `sed -i 's/\r$//'` before handing the file to `maspsx`.

See the workflow notes in
[scripts/check_scores.sh](../tools/permuter/scripts/check_scores.sh) and the
`anthropic-skills:decomp-matching-workflow` skill for the full iterative
permuter loop.

---

## Adding a new function to match

1. Find the function's address (e.g. via Ghidra or the gcc-syms file in
   `../decompile/symbols/`).
2. Create `General/<SUBDIR>/<NAME>.c` with the cleaned C source. Use
   `#include "<SUBDIR>.h"` for shared typedefs.
3. If the function reads or writes struct fields the header doesn't expose
   yet, add them to `<SUBDIR>.h` — see the existing headers for layout style
   (offsets in comments, partial structs with `char padXX[..]` filler).
4. Score it (see above). Iterate.

The headers exist for *organisation*, not isolation — each `.c` is still
compiled standalone by the permuter, so the header must be self-contained
(no nested includes).

---

## Why the matching project exists

`matching` is a reference, not a build target. Mods should pull from
`decompile/` or `rewrite/`. The point here is to *prove* a given C source
faithfully reproduces ND's original `.o`, so the `rewrite` project can lift
matched logic with confidence that no behavior was lost in translation.

If you're contributing, focus on getting a function to score 0 and don't worry
about whether the resulting C is "pretty" — readability cleanup is a Phase 5
pass once the match is locked in.
