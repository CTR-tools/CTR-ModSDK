                                   ABOUT

Nitros Oxide as a fully playable character in Crash Team Racing, compatible
with all modes of the game and selectable in the character select screen.
Also bundled with a modified version of AdvBosses to allow selecting Oxide in
Adventure mode. The culmination of years of work by Niko.

Works in USA Retail, and as of this version Europe Retail, Japan Retail, and
Japan Trial. As of this version Oxide now shows up in podiums after winning
Trophy Races or Grand Prix. This currently uses his lose animation from
Adventure mode.

                                KNOWN ISSUES

-Oxide's character preview in the character select screen is displayed with
the wheels that the other characters' karts have. These are to be removed in
a future version of the mod.
-Oxide's character icon in the character select screen flies into view from
the left side of the screen as opposed to the bottom. It is yet unknown why
this happens.
-Oxide's model in the character select screen displays erroneously in the
European version of the game. This is assumed to be due to how this
functionality was achieved by a manual edit of Oxide's character model, and
thus how model information may be read differently in the European version.
More research on the game's model formats may be required to fix this issue.

                          COMBINING WITH OTHER MODS

This module can be included with other modules that only compile to RDATA,
such as CharacterRandomizer, CustomCups, EngineSelect, etc. In order to do
that, the SaveRAM module needs to be included, or else Oxide will not fit in
the game's memory, and the optimized version of the game's LOAD_DriverMPK
function, which can be found in the Decompile section of this collection of
mods, is needed to prevent in-race CPU .mpk's from loading while in the main
menu; the game will crash otherwise.

You can also simply take a look at the OxideFix and CharacterRandomizer mod
included in this collection, in the ModPacks directory.

                               TECHNICAL DATA

Does not work in the September 3 prototype of CTR, but neither does the
more-simple SaveRAM, nor the optimized version of the LOAD_DriverMPK function
made for the decompile, so those parts of the mod will need to be made
functional in September 3 before attempting to make OxideFix compatible with
said version.

AdvBosses is appended to the end of 233 overlay, allows user to pick any
unlockable character in adventure mode, overwrites the JR RA in 233's Garage
UI MenuBox, jumps to the function in AdvBosses's C code.

MM_ByteArrays.c is appended to the end of 230 overlay, allows Oxide to draw
in the main menu. First three arrays are copied from 230, and modified to
have an extra icon, then other icons are adjusted to allow moving to Oxide's
icon. The array of bytes for Oxide's model was generated with an online "file
to hex" converter, the original bin for Oxide's unanimated model is in
assets, which was built by taking his animated model, and erasing animation
data by hand, then editing his scale to be 5/8 the size, so he fits on-screen.

MM_hookCallback230.s overwrites the EXE function callback to 230, which then
executes the MM_NewCallback230 function, in 230 file.

MM_NewCallback230.c initializes and patches the 230 file in ways that are
easier to do in C, than to do statically, such as patching oxide pointers,
and patching menu pointers.

MM_NewModelSearch.c overwrites the original SearchString function in 230. The
new function saves assembly by only checking the first 4 bytes of a name
instead of 16. This is only used in character selection, so no risk involved
with that. After saving assembly, we add code to check outside the LEV's
model array, to then check the Oxide model at the end of 230. Without this,
the original search can not find Oxide. Also, Oxide's pointer can not be
added to the end of the LEV's model array, because the first bytes after the
array is the LEV's mesh_info struct, overwriting that will break the game. 

PodiumFix_AppendQueue.c gets installed to RDATA at "s_asphalt2", a JMP to
this function is on the JR RA of LOAD_AppendQueue, constantly checking for
the PodiumsCallback parameter, signifying the last load in the queue for the
podium scene. If that is found, and if Oxide needs to be the 1st place
winner, then the last member of the queue is shifted to the next slot, and
the slot where the last member "was" will be taken by a request to load
Oxide's losing animation, so he can be on podiums 

PodiumFix_hookAppendQueue.s overwrites the JR RA of exe's LOAD_AppendQueue
function, jumps to a function in OxidePodium.c that manually adds Oxide's
"defeat" dance model, since the original game code will skip loading Oxide
entirely at podiums if he is in 1st place.