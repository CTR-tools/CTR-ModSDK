Folder structure:
build - Paste your original CTR rom in this folder to build and play sample mods
decompile - Functions decompiled from CTR that can be rebuilt and modified
ghidra - Commented disassembler output of 90% of the game's source code
include - The project's includes: all the structs and globals in CTR and psn00bsdk.
mods - Finished code modifications for CTR
├── ModPacks - Combinations of other mods
├── Modules - Mods that you can combine with other mods
├── OnlineCTR - Stuff made for Niko's OnlineCTR
├── Patches - Original code modifications that can be included in any mod with relatively no risk of overlap
├── Standalones - Mods that are designed to be played without other mods
├── Tests - Programming tests and other miscellaneous mods
├── v2 - Early CTR mods
└── common.h - All of the structs and globals in CTR
plugins - Third-party programs and extensions added to the modding toolchain.
syms - Symbol tables for all game regions
tools - Miscellaneous tools for making mods
8bitnop.bin
config.json
disc.json
nop.s
readme.txt - You're here!

Code names for supported builds:
903 - September 03 - USA Prototype #3, henceforth referred to as SepReview
926 - September 26 - USA Retail
1006 - October 06 - Japan Taikenban Demo, henceforth referred to as JpnTrial
1020 - October 20 - Europe Retail
1111 - November 11 - Japan Retail

Rename your CTR iso in the build folder to the following:
-If retail NTSC-U, rename to "ctr-u.bin"
-If retail PAL, rename to "ctr-pal.bin"
-If retail NTSC-J, rename to "ctr-j.bin"
-If September 3 prototype, rename to "ctr-sep3.bin"
-If Taikenban demo, rename to "ctr-j-trial.bin"