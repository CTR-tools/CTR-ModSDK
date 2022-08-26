Adds a menu for setting up a Trophy Race cup that you can
customize.

Supports all builds

The mod installer could not inject code directly into overlays
at the time this mod was made, so it hooks the callback of
loading 230 (main menu) then makes injections into RAM at runtime

Some 230 addresses are somewhat hard-coded for each build with
macro #if #else, that will be improved later when we have the
equivalent of common.h for overlays

This hook is overwriting a function pointer
and not overwriting a JAL or JMP

Made by Niko.