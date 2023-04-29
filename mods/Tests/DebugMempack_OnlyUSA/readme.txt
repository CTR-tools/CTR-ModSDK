Restores debug strings from beta builds, into USA Retail.
This code overwrites Torch functions, because RDATA holds
the original strings. In main.c, all strings go to top of file,
so the make the JR RA get emitted as the first bytes, "JunkFunc"
makes a fake-string that generates those bytes, so Torch_Main
can't execute.

This is USA Only, because of MEMPACK_Init's "mp->start",
to make this support other builds, just change that address
from 0x800ba9f0 to something else