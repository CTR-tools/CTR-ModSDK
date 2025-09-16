#include <ctr/nd.h>

void LoadDecomp()
{
    const u32 address = 0x80200000;
    char dummy;
    ND_LOAD_XnfFile("\\DECOMP.BIN;1", address, &dummy);
    ND_Music_SetIntro();
}