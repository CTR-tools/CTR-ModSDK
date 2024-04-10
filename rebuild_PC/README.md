### Compiling

The following are required to successfully build CTR-PC:
- Target 32-bit artifacts;
- Use 32-bit libraries;
- Needs PsyCross built with `USE_EXTENDED_PRIM=0`;
- On MSVC use "Fixed Base Address", on GCC move `-Wl,-Ttext,0x0` to the earliest position that does not conflict.

For Windows open `CrashTeamRacingPC.c` with VisualStudio; for [Mingw](https://www.mingw-w64.org/)/Linux/Darwin use the `Makefile`; [Nix](https://nixos.org/download/#download-nix) users can use `./build-{native,mingw}-{gcc,clang}.nix` directly.
