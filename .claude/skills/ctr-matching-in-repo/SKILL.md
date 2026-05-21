---
name: CTR Matching (in-repo) Workflow
description: Step-by-step process for taking a CTR PS1 function from Ghidra/splat output to score 0 matching assembly using decomp-permuter. ONLY applies to work under src/matching/ in the CTR-in-C repo — do not invoke for src/decompile/ or src/rewrite/, those subprojects have different goals. Toolchain lives as submodules inside src/matching/tools/. Works on Windows native (PowerShell or Git Bash) and on Linux/WSL.
type: feedback
---

## Decomp-to-Matching Workflow (in-repo, CTR / PS1 / gcc 2.8.1-psx)

> **Scope.** This skill only applies when you're working inside
> `src/matching/`. The `decompile/` and `rewrite/` subprojects have
> different goals (rebuild a working game vs. unit-test correctness)
> and shouldn't use this workflow. If the user's request is about
> `decompile/` or `rewrite/`, don't invoke this skill — defer to the
> docs in those subdirs (`src/decompile/`, `src/rewrite/`).

This is the **in-repo** variant of the upstream `decomp-matching-workflow`
skill. The toolchain (permuter, maspsx, windows-gcc-psx) lives **inside**
the repo under `src/matching/tools/` as git submodules, and the compile
script is a per-function copy of `src/matching/tools/compile.sh.template`
(or `compile.ps1.template`). No `~/permuter/`, no `/opt/old-gcc/`, no
hardcoded absolute paths from anyone else's machine.

### When to use this skill vs. the upstream one

- **This skill** — when the user is working in a checkout of CTR-in-C that
  sits under `psx-modding-toolchain/games/CTR-in-C/`, with `tools/permuter`,
  `tools/maspsx`, and `tools/windows-gcc-psx` initialised as submodules.
  Either Windows-native or Linux/WSL.
- **`decomp-matching-workflow`** — when the user has the older
  `~/permuter/`-style setup with `/opt/old-gcc/` and hand-rolled
  `extract_func.sh`. The phases are the same; only the paths differ. If
  someone shows you `~/permuter/...` paths in a fresh chat, fall back to
  that skill.

### Companion reference

For first-time setup (placing `SCUS-94426.s`, installing the modern MIPS
binutils via the pcsx-redux `mips.ps1`, Python deps for the permuter), see
the in-repo [`src/matching/README.md`](../../../src/matching/README.md).
It covers prerequisites, both Windows and Linux paths, and notes the
Windows support that ships on the permuter submodule's branch.

### Bundled scripts

Two compile script templates ship in the repo, not in this skill:

- [`src/matching/tools/compile.sh.template`](../../../src/matching/tools/compile.sh.template)
  — Git Bash, works on Windows (no WSL) and Linux.
- [`src/matching/tools/compile.ps1.template`](../../../src/matching/tools/compile.ps1.template)
  — PowerShell, pure Windows.

Both honour `$GP_VALUE` / `$env:GP_VALUE` — when set, the script appends a
`patch_gprel.py` step that fixes GP-relative relocations. Two functions
currently need this: `VehPhysCrash_AI` and `VehPhysCrash_Attack`, both
`gp=0x8008CF6C`.

For sweeping the existing scored functions, copy one of the templates
into each per-function dir under `src/matching/tools/<func>/` and run the
permuter against it (see [Scoring a function](#scoring-a-function)).

### Important Rules

- **If a resource is missing, ASK — don't guess or proceed without it.** Path
  conventions in this skill assume `src/matching/tools/` is fully populated
  (submodules initialised, `SCUS-94426.s` placed). If a contributor has a
  different layout — e.g. their gcc lives outside the repo at
  `tools/gcc/`, or they've put `SCUS-94426.s` elsewhere — confirm before
  hardcoding paths.
- **Protect permuter progress at all times.** Each permuter run can take
  hours to climb out of a high-score plateau. Before making ANY manual
  edit to a permuter best-output file: (1) note the current best score,
  (2) make the edit, (3) immediately recompile and verify the score
  didn't regress. If it regressed, revert. The permuter strips macros
  and reformats; plan for a final cleanup pass (Phase 5).
- **Inline asm is ONLY permitted for GTE instructions** — to match patterns
  from the PSYQ SDK (INLINE_C.H, GTEMAC.H). No other asm hacks for
  matching purposes.
- **Exception: non-ABI-adherent functions** — Some CTR functions don't
  follow the standard MIPS calling convention. If a function shows
  impossible register usage (callee-saved $s regs trashed without a
  save/restore, return values in unusual registers, etc.), **notify the
  user** with the evidence. Try pure C first; ask before adding non-GTE
  asm hacks.
- **Compiler flags:** `-Wa,--aspsx-version=2.77 -mel -g -O2` (passed to
  the gcc-psx driver). The templates already set these.
- **`USE_REAL_GTE` must reach `cpp`, not just gcc.** The permuter pre-
  preprocesses `base.c` with bare `cpp` before invoking the compile
  script, so `-D` flags in the compile script come too late for `#if`
  conditionals. The repo's `Vehicle.h` works around this by
  `#define`ing `USE_REAL_GTE 1` itself when undefined — every matching
  `.c` file relying on real GTE asm must keep that pattern.
- **Cross-platform sanity: header conventions.** Each `General/<Subdir>/`
  has a `<Subdir>.h` (e.g. `Vehicle.h`, `COLL.h`) carrying shared types
  and struct layouts. Each `.c` file `#include "<Subdir>.h"` to pull
  those in. Don't introduce nested includes — each `.c` is compiled
  standalone by the permuter and headers must be self-contained.
- **Always search hex addresses case-insensitive.** Different sources use
  different casing (splat uppercase `8001D944`, gcc-syms lowercase
  `0x8001d944`, Ghidra `FUN_8001d0c4`).

### Key File Paths (relative to the repo root)

| What | Path |
|---|---|
| Assembly source | `src/matching/tools/SCUS-94426.s` *(user-placed, gitignored)* |
| Matching C sources | `src/matching/General/<COLL\|INSTANCE\|UI\|Vehicle>/` |
| Per-subdir headers | `src/matching/General/<Subdir>/<Subdir>.h` |
| Ghidra C reference | `reference/ghidra/` *(if present in this checkout)* |
| PSY-Q gcc 2.8.1 (Win) | `src/matching/tools/windows-gcc-psx/gcc-2.8.1-psx/{gcc,cc1,cpp}.exe` |
| PSY-Q gcc 2.8.1 (Linux) | `src/matching/tools/gcc/` *(user-placed)* |
| maspsx wrapper | `src/matching/tools/maspsx/maspsx.py` |
| permuter | `src/matching/tools/permuter/permuter.py` *(fork: `TheUbMunster/decomp-permuter@windows-support`)* |
| Compile script templates | `src/matching/tools/compile.{sh,ps1}.template` |
| GP-rel fixer | `src/matching/tools/permuter/patch_gprel.py` |
| Symbol file (NTSC-U/926) | `src/decompile/symbols/gcc-syms926.txt` |
| Modern MIPS binutils (Win) | `%APPDATA%\mips\mips\bin\mipsel-none-elf-as.exe` *(via pcsx-redux installer)* |
| Modern MIPS binutils (Linux) | apt `binutils-mipsel-linux-gnu` |

### Permuter Windows support

The permuter submodule pins
[`TheUbMunster/decomp-permuter`](https://github.com/TheUbMunster/decomp-permuter)
on the **`windows-support`** branch. That branch carries four small
changes on top of upstream that the in-repo workflow depends on:

1. `src/main.py` — skip the `os.stat().st_mode & 0o100` executable-bit
   check when `os.name == "nt"` (NTFS doesn't track POSIX exec bits).
2. `src/main.py` — when `compile.sh` is missing on Windows, fall back
   to `compile.ps1`.
3. `src/compiler.py` — prefix `["bash"]` for `.sh` and
   `["powershell", "-NoProfile", "-File"]` for `.ps1` on Windows so
   the kernel can launch the script.
4. `src/objdump.py` — add `mipsel-none-elf-objdump` and
   `mipsel-linux-gnu-objdump` to the MIPS executable list (matching
   the names shipped by pcsx-redux's Windows installer and apt).

If `git submodule update` ever pulls a SHA on a different branch (e.g.
after upstream rebases), `cd src/matching/tools/permuter && git
checkout windows-support && git pull` puts it back on the tracking
branch.

### Phase 0: Extract & Locate

1. **Extract target asm.** The repo doesn't yet ship an `extract_func.sh`
   wrapper. Use the permuter's upstream `import.py`, or extract by hand:
   - Open `src/matching/tools/SCUS-94426.s`
   - Find the `glabel func_<ADDR>` / `endlabel func_<ADDR>` block
   - Wrap it in a stub `target.s` with PSYQ macros, assemble with
     `mipsel-none-elf-as -march=r3000 -mabi=32 -o target.o target.s`
   - The reference `extract_func.sh` in upstream
     `decomp-matching-workflow` does this end-to-end; vendor it into
     the repo if you'll do this often.

2. **Find Ghidra C source.** Search `reference/ghidra/` for the address.
   If `reference/ghidra/` isn't in this checkout, ask the user where
   they keep it.

3. **Extract the function** from the ghidra `.c` into a new dir at
   `src/matching/tools/<FUNC_NAME>/base.c`, including any
   typedefs/externs/structs from the surrounding Ghidra file that the
   function references.

4. **Fix line endings.** `sed -i 's/\r$//' base.c` (or in PowerShell:
   `(Get-Content base.c -Raw) -replace "\r","" | Set-Content -NoNewline base.c`).

### Phase 0.5: Rename to human-readable name (optional, ask user)

Once a function is staged, ask if they want the directory renamed from
`func_<ADDR>` to the human-readable name from
`src/decompile/symbols/gcc-syms926.txt`:

- Format: `SYMBOL_NAME = 0xADDRESS;` (lowercase hex)
- e.g. `src/matching/tools/func_8001D944/` → `src/matching/tools/COLL_FIXED_PlayerSearch/`
- Update `settings.toml`'s `func_name` to match (or keep `func_<ADDR>` if
  the asm label is the address-style name — the permuter compares the
  `jal` target text, so it has to match what the rest of the .o emits).

### Phase 1: Make It Compile

1. Copy `src/matching/tools/compile.{sh,ps1}.template` into the
   per-function dir as `compile.sh` / `compile.ps1`.
2. Write a `settings.toml`:
   ```toml
   func_name = "func_<ADDR>"   # or the gcc-syms name
   compiler_type = "gcc"
   ```
3. If the function uses GP-relative globals (`%lo(D_XXX)(gp)` in the
   target asm), set `GP_VALUE` in `compile.sh` (Git Bash) or pass it via
   `$env:GP_VALUE` for PowerShell. Currently known: `0x8008CF6C` for the
   NTSC-U build.
4. Compile manually first: `bash compile.sh base.c -o test.o` (or
   `powershell -File compile.ps1 base.c -o test.o`).
5. Fix any errors:
   - Missing closing braces (Ghidra often truncates) — add them.
   - Missing symbols — check whether the function call pattern matches
     a callee in `gcc-syms926.txt`; add `extern` prototypes at the top
     of `base.c`. Don't pull in `decompile/` headers — keep `base.c`
     self-contained.
   - **Missing GTE macros** — define as inline asm matching PSYQ SDK
     patterns. Vehicle.h already exposes the standard set (`gte_ldVXY0`,
     `gte_ldVZ0`, `gte_rtv0`, `gte_stMAC{1,2,3}`, `gte_SetRotMatrix`).
     For other GTE ops, follow `Vehicle.h`'s `#if USE_REAL_GTE ... #else
     ... #endif` pattern.
   - **`SEXT24(x)`** — usually just `(x)` for short inputs.
   - **Ghidra `getCopReg(cop, reg)`** — decode register from encoding
     bits 15:11.
   - **pycparser quirks** — pre-compute expressions with `&`/`|` inside
     asm operands into temp vars; pycparser chokes on them otherwise.

### Phase 2: Structural Analysis (before permuting)

10. Run the scorer in debug mode:
    ```
    python src/matching/tools/permuter/permuter.py src/matching/tools/<FUNC_NAME> --debug
    ```
11. Look for problems the permuter **cannot** fix:

**Missing code blocks** — Ghidra often drops `else` clauses that set
defaults and return early. Compare target asm branch structure against
your C control flow.

**Wrong types** —
- `*(uint *)` storing where target has `sb` → use `*(char *)`
- `*(short *)` loading where target has `lhu` → use `*(ushort *)`
- A short field read with `lh` that you want as a u32 sentinel check
  (4-byte `lw`) → cast through `*(int *)` instead of the field.

**Division traps** — target has `break 7` / `break 6` around `div`?
`compile.{sh,ps1}.template` already passes `--expand-div`. Verify with
`grep -c break` on both objdumps.

**GTE pipeline hazards** —
- `gte_Lzc(r1,r2)` in GTEMAC.H needs 2× `gte_nop()` between ldlzc/stlzc.
- `mfc2` has a 1-instruction delay — usually the compiler handles, add
  `gte_nop()` if not.

**Redundant operations** —
- `>> (x & 0x1f)` — MIPS shifts use low 5 bits already; remove mask.
- `SEXT24()` on `short` values — generates extra sll/sra; use `(x)`.
- Intermediate `short` variables forcing `lhu + sll/sra` → inline the
  expression.

**Wrong constants** — compare immediates carefully (`0x19000000` vs
`0x190000`).

**gcc-2.8.1 CSE quirks (observed in this repo)** —
- Reading a struct member three times in adjacent statements doesn't
  always CSE the same way as the equivalent `*((T*)(p + 0xNN))`
  pattern. If you see the target hoist a load into a single register and
  your C version does three loads, try the cast form (kept as a comment
  in the cleaned source explaining why).
- Iterating over an array via `int* p[2]` vs typed `Struct* p; p[2]`
  also produces different intermediate-pointer CSE patterns. Stay on the
  form the upstream `.c` used if the score regresses.
- Anonymous structs inside unions are unsupported by gcc 2.8.1 — give
  every inner struct a name (see the `unk5bc.ai` pattern in
  `Vehicle.h`'s `BotData`).

**Non-ABI-adherent functions** — see the rule above; ask before adding
non-GTE asm hacks.

### Thread Budget

This machine has 32 threads (16 cores). Reserve 4 for the user/system —
**28 usable** split evenly across active permuter runs:

- 1 running: `-j28`
- 2 running: `-j14` each
- 3 running: `-j9 -j9 -j10`
- 4 running: `-j7` each

When starting or stopping a run, rebalance by killing and restarting the
others with updated `-j`.

### Phase 3: Permuter Iteration

12. Once Phase 2 issues are resolved, kick off:
    ```
    python src/matching/tools/permuter/permuter.py src/matching/tools/<FUNC_NAME> -j<N> --best-only
    ```
13. Monitor with the upstream `decomp-matching-workflow` skill's
    `check_scores.sh`, adapted to the in-repo path:
    ```
    cd src/matching/tools && ls -d <FUNC_NAME>/output-*/ | sort -t- -k2 -n | head -3
    ```
14. When plateaued, examine the best-output diff, apply as new base,
    make a manual fix, re-run.
15. For targeted randomisation, use `PERM_RANDOMIZE()` macros — if ANY
    perm macros are present, ONLY those regions get randomised.

### Phase 4: Endgame (register allocation)

16. Register diffs are the hardest. Influenced by statement order, temp
    variables, expression structure.
17. Moving computations earlier/later relative to stores can shift
    register assignment.
18. Variable declaration order does NOT help at -O2.
19. Let the permuter run for extended periods (hours) — it introduces
    temps that affect regalloc.

### Key Diff Reading

- `[0m]` = matching
- `[94m]` = same instruction, different registers
- `[91;1m]` = in target only (deletion — your `.o` is missing this)
- `[32;1m]` = in compiled only (insertion — your `.o` has extra)
- Same instruction in both columns as insert+delete = displaced
  (permuter territory)
- Different instructions = structural (manual fix needed)

### Callee Symbol Names

When `jal`-ing another function, the symbol name in the compiled `.o`
must match the target's exactly. Check `target.s` for the callee symbol
name (e.g. `jal func_8001D0C4`) and use that exact name in the
prototype and call site, not the Ghidra name (e.g. `FUN_8001d0c4`).
The permuter strips `<...>` comments after `jal` but the symbol name
itself is part of the instruction bytes.

### Phase 5: Cleanup (CRITICAL — do this before declaring done)

The permuter strips macros and reformats code. When score 0 (or the
target's best achievable score) is reached:

20. **Ask the user** before cleanup — they may want to see the raw
    output first.
21. **Restore GTE macros** — `gte_ldR11R12(x)` instead of the expanded
    `asm volatile("ctc2 %0, ..." : : "r"(x))`.
22. **Restore other macros** — `gte_mvmva(0,0,0,3,0)` instead of
    `gte_mvmva_core(0x0406012)`, `gte_nop()` instead of
    `asm volatile("nop")`.
23. **Remove permuter artifacts** — unnecessary temp variables, `new_var`
    aliases, redundant casts the permuter introduced.
24. **Restore readable formatting** — fix indentation, spacing, brace
    style to match the project conventions (4-space indent, Allman
    braces — see `src/coding-standards.md`).
25. **Verify the score is still 0** after each cleanup batch. Recompile
    and run `--debug`. If it regressed, revert that batch.
26. **Save** as the final deliverable in the per-function dir's
    `base.c`, and (if the user wants) copy it into
    `src/matching/General/<Subdir>/<Name>.c`.

The final file should look like human-written code: proper macro usage,
no `new_var3` temporaries, no expanded inline asm. Every cleanup change
must be verified against the score.

### One-shot scoring sweep

For checking the status of the existing 25 matching files, the in-repo
`tools/` directory and a small bash loop is enough:

```bash
for d in src/matching/tools/*/; do
    name=$(basename "$d")
    [ -f "$d/base.c" ] || continue
    score=$(python src/matching/tools/permuter/permuter.py "$d" --debug 2>&1 | \
            grep -oP "base score = \K[0-9]+" | head -1)
    echo "$name: ${score:-FAIL}"
done
```

For the current state (May 2026), the expected output is 23 functions at
0, `UI_Weapon_DrawBG` at 10, and `VehPhysGeneral_JumpAndFriction` at
1460. Any other non-zero score is a regression — investigate.

### How this differs from `decomp-matching-workflow`

| Topic | Upstream skill | This skill |
|---|---|---|
| Permuter location | `~/permuter/` | `<repo>/src/matching/tools/permuter/` (submodule) |
| gcc location | `/opt/old-gcc/` | `<repo>/src/matching/tools/windows-gcc-psx/gcc-2.8.1-psx/` (submodule, Windows) or `<repo>/src/matching/tools/gcc/` (Linux, user-placed) |
| maspsx | `~/maspsx/` | `<repo>/src/matching/tools/maspsx/` (submodule) |
| Assembly source | `~/permuter/SCUS-94426.s` | `<repo>/src/matching/tools/SCUS-94426.s` (user-placed, gitignored) |
| Compile script | Hand-rolled per function | Copy from `tools/compile.{sh,ps1}.template` |
| GP relocation | Bash patch line per script | `GP_VALUE` env var |
| Windows support | WSL required | Native Windows works (PowerShell or Git Bash) |
| `USE_REAL_GTE` | Pass `-D` in compile.sh | Auto via `Vehicle.h` `#define` |

**Why:** Derived after standing up Windows-native scoring with
`windows-gcc-psx` and the pcsx-redux mips toolchain. Phases and rules are
the same; only paths and OS portability changed.
