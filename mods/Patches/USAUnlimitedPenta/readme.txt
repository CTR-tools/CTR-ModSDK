Changes Penta's stats to be maxed out as in the PAL and Japan versions.
Made by Niko and Superstarxalien.

Supports USA Retail only, does not support Sep3.

The bin was built manually, it contains the full collection of all MetaPhys
for all driver classes in the game. The bytes were copied off the PAL exe,
then by hand, the nullptr at the beginning was removed from each MetaPhys,
therefore returning the 0x20-byte struct back to 0x1c, fitting in NTSC.

Driver offsets are hard-coded to PAL, NTSC driver offsets = PAL offset - 4,
so that change was made in the code as well. In MetaPhys, due to nullptr
being removed from that, 4 bytes had to be subtracted from those offsets too