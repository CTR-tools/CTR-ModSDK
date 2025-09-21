# Strategy
This folder is an ongoing decompilation project for the PSX game Crash Team Racing. This is a non byte matching decompilation, aiming for code quality while achieving the same functionality as the original game. This project adopts the [Ship of Theseus](https://en.wikipedia.org/wiki/Ship_of_Theseus) strategy. By taking advantage of [PCSX-Redux](https://github.com/grumpycoders/pcsx-redux/) 8MB memory expansion, we can re-write game functions and load them in memory, while the original game stays intact. Then, we can force the game to call each function we re-wrote, and compare the output of the decompiled function with the original game function.

# Folder Structure
`src/hooks/dll/`: boot loader for the decompile.

`src/exe/`: main executable decomp.

`src/tests/`: tests for each decompiled function.

`../include/ctr/`: decompile headers.

`../symbols/gcc-syms-rewrite.txt`: original function addresses.

`../symbols/gcc-extern-rewrite.txt`: extern global variable addresses.

# Tests
Each decompiled function must have an entry in `s_functions` table at `src/tests/test.c`. During boot, this entry is used to patch each original function so that the decompile version can be called. At the end of each decompiled function, a call to a `TEST` function should be made, which restores the state before the decompiled function was called, then patches the game to call the original function, and then compared the output of the original function with the decompiled function. For simple test functions that don't use any global variables, see `src/tests/test_math.c` and `src/exe/math.c`. For functions that change global variables, a call to a `BACKUP` function should be made to store the state upon function call. For examples, see `str/tests/test_rng.c` and `src/exe/rng.c`.

Note: the original function name must have the same name of the decompiled function + `ND_` prefix.