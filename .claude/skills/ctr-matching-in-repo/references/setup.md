# In-repo Matching Setup — Reference

A condensed setup guide for the CTR-in-C matching toolchain. The
authoritative source lives at `src/matching/README.md` in the repo
itself — this file exists so the skill bundle is self-contained for
when the repo isn't checked out yet.

---

## Layout this skill assumes

```
<repo>/src/matching/
├── README.md
├── General/
│   ├── COLL/        (COLL.h + COLL_*.c)
│   ├── INSTANCE/
│   ├── UI/
│   └── Vehicle/     (Vehicle.h + Veh*.c)
└── tools/
    ├── permuter/                  ← submodule
    ├── maspsx/                    ← submodule
    ├── windows-gcc-psx/           ← submodule
    ├── compile.sh.template        ← Git Bash compile template
    ├── compile.ps1.template       ← PowerShell compile template
    ├── gcc/                       ← Linux gcc (user-placed, gitignored)
    └── SCUS-94426.s               ← NTSC-U disassembly (user-placed, gitignored)
```

`<repo>` is typically `psx-modding-toolchain/games/CTR-in-C/`.

## Prerequisites

- **Python 3.8+**
- **Modern MIPS binutils** — provides `mipsel-{linux-gnu,none-elf}-as`
  and `mipsel-{linux-gnu,none-elf}-objdump`:
  - Linux: `apt install binutils-mipsel-linux-gnu`
  - macOS: `brew install mipsel-linux-gnu-binutils` (or the
    `mipsel-none-elf-binutils.rb` formula from
    `psx-modding-toolchain/tools/macos-mips/`)
  - Windows: `powershell -c "& { iwr -UseBasicParsing https://raw.githubusercontent.com/grumpycoders/pcsx-redux/main/mips.ps1 | iex }"`
    then `mips install 13.2.0`. Adds binaries to
    `%APPDATA%\mips\mips\bin\`.
- **Git Bash (Windows only)** — ships with git for Windows; needed if
  using `compile.sh.template`. PowerShell users only need PowerShell 5+
  and can use `compile.ps1.template` instead.

## One-time setup

1. **Clone with submodules**:
   ```
   git clone --recurse-submodules <ctr-in-c-repo>
   # or if you already cloned:
   git submodule update --init src/matching/tools/permuter src/matching/tools/maspsx src/matching/tools/windows-gcc-psx
   ```

2. **Install Python deps for the permuter**:
   ```
   pip install pycparser attrs toml Levenshtein pynacl
   ```
   (`pynacl` is optional; only needed for permuter@home networking.)

3. **Place the PSY-Q gcc 2.8.1 tree**:
   - **Windows (verified)**: `git submodule update --init` already
     pulls `windows-gcc-psx`. Its `gcc-2.8.1-psx/` subdir holds
     `gcc.exe`, `cc1.exe`, `cpp.exe`, `cccp.exe`. The compile
     templates point at it automatically.
   - **Linux**: extract the PSY-Q gcc 2.8.1 Linux tree from your
     `psx-modding-toolchain` install (or the `decompals/old-gcc`
     Docker image) to `src/matching/tools/gcc/`.

4. **Place the NTSC-U disassembly**:
   ```
   <repo>/src/matching/tools/SCUS-94426.s
   ```
   The file is ~8 MB. Source it from your splat output for the NTSC-U
   build (build id 926) or the copy bundled with psx-modding-toolchain.

5. **Windows support is already on the permuter submodule's branch.**
   The submodule pins
   [`TheUbMunster/decomp-permuter`](https://github.com/TheUbMunster/decomp-permuter)
   on the `windows-support` branch, which carries four small
   changes on top of upstream:
   - `src/main.py` — skip the exec-bit check on Windows
   - `src/main.py` — fall back to `compile.ps1` when `compile.sh` is
     missing
   - `src/compiler.py` — prefix `bash` for `.sh`, `powershell
     -NoProfile -File` for `.ps1`
   - `src/objdump.py` — add `mipsel-none-elf-objdump` and
     `mipsel-linux-gnu-objdump` to the MIPS executable list

   If a `submodule update` ever lands you on a different commit:
   ```
   cd src/matching/tools/permuter
   git fetch origin windows-support
   git checkout windows-support
   ```

## Per-function setup

For each function you want to score:

1. Create `src/matching/tools/<func_name>/` (e.g.
   `<func_name>` = `func_8001D944` or the
   `gcc-syms926.txt` name like `COLL_FIXED_PlayerSearch`).
2. Drop in:
   - `base.c` — the cleaned C source for the function. Use
     `#include "<Subdir>.h"` to pull shared typedefs from the matching
     subdir (e.g. `Vehicle.h`).
   - `target.o` — the original NTSC-U .o for this function, extracted
     from `SCUS-94426.s` (see "Extracting target.o" below).
   - Whichever per-subdir `.h` the `.c` includes (e.g. copy
     `src/matching/General/Vehicle/Vehicle.h`). It must live next to
     `base.c` because the permuter pre-preprocesses `base.c` with
     `cpp -nostdinc`.
   - `settings.toml`:
     ```toml
     func_name = "func_<ADDR>"   # or the gcc-syms-style name
     compiler_type = "gcc"
     ```
   - `compile.sh` — copy from `src/matching/tools/compile.sh.template`.
     Or `compile.ps1` from `compile.ps1.template`.

3. If the function uses GP-relative globals (`%lo(D_XXX)(gp)` in the
   target asm), set `GP_VALUE` in the compile script's environment.
   Currently known: `0x8008CF6C` (NTSC-U).

## Extracting target.o

The upstream `decomp-matching-workflow` skill ships an
`extract_func.sh` that:

1. Greps `SCUS-94426.s` for `glabel func_<ADDR>` / `endlabel`.
2. Wraps the asm block in a stub `.s` with PSYQ macros (`.set noat`,
   `.set noreorder`, `glabel`/`endlabel` defs).
3. Converts COP2 mnemonics that GNU as doesn't grok into `.word`
   directives.
4. Assembles with `mipsel-{linux-gnu,none-elf}-as -march=r3000 -mabi=32
   -o target.o target.s`.

The current repo doesn't ship this script yet. Either:
- Copy `extract_func.sh` from `~/permuter/` (upstream layout) and
  adjust the path to `SCUS-94426.s`.
- Or use the permuter's own `import.py`:
  ```
  python src/matching/tools/permuter/import.py base.c target.s
  ```
  if you can produce a self-contained `target.s` for the single
  function.
- Or extract by hand: find the label, copy the asm to a fresh `.s`,
  prepend the PSYQ macro defs, assemble.

## Sanity check

Once a function dir is set up, run:

```
python src/matching/tools/permuter/permuter.py src/matching/tools/<func> --debug
```

Expected outputs:
- `base score = 0` — byte-perfect, you're done.
- `base score = <n>` — current divergence; permuter will try to reduce it.
- `Unable to compile ...` — fix the compile errors before iterating.
- `must be marked executable` (Linux) — `chmod +x compile.sh`.
- `must be marked executable` (Windows) — your permuter is missing the
  Windows patch.

To sweep all function dirs, see `scripts/check_scores.sh` (or
`.ps1`) in this skill bundle.

## Troubleshooting

| Symptom | Cause / fix |
|---|---|
| `cpp: not found` | Add the gcc-psx dir to PATH (it ships `cpp.exe`). |
| `mipsel-*-as: not found` | Modern MIPS binutils not installed or not on PATH. |
| Empty diff but score nonzero | `patch_gprel.py` not applied to a GP-using function. Set `GP_VALUE`. |
| Score 0 sometimes, nonzero sometimes | One of the gcc-2.8.1 CSE quirks — see SKILL.md Phase 2. |
| `Invalid argument` calling `.exe` from WSL bash | cwd is in WSL filesystem. `cd` to a `/mnt/c/...` path first. |
| BOM in `.s` reaches the assembler (PowerShell) | Pipe via `cmd /c "py maspsx.py ... < file.s"` to avoid PS encoding. |
| Anonymous struct in union fails to compile | gcc 2.8.1 doesn't support C11 anonymous nested structs — name the inner struct. |
